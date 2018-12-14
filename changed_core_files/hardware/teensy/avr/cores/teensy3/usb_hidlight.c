#include "usb_dev.h"
#include "usb_hidlight.h"
#include "core_pins.h" // for yield(), millis()
#include <string.h>    // for memcpy()
#include "HardwareSerial.h"

#ifdef HIDLIGHT_INTERFACE // defined by usb_dev.h -> usb_desc.h
#if F_CPU >= 20000000

static usb_packet_t *rx_packet=NULL;

void usb_hidlight_on_update(void (*updateFunc)(int[]), void (*logFunc)(usb_packet_t))
{
	int c[HIDLIGHT_NUMBER_OF_LEDS];
  unsigned int ci = 0;

  while (1) {
	  unsigned int i;

	  if (!rx_packet) {
	  	if (!usb_configuration) continue;
	  	rx_packet = usb_rx(HIDLIGHT_RX_ENDPOINT);
	  	if (!rx_packet) continue;
      logFunc(*rx_packet);
	  }
	  i = rx_packet->index;
	  c[ci] = rx_packet->buf[i++];

	  if (i >= rx_packet->len) {
	  	usb_free(rx_packet);
	  	rx_packet = NULL;
	  } else {
	  	rx_packet->index = i;
	  }

    if (ci >= HIDLIGHT_NUMBER_OF_LEDS-1) {
	    updateFunc(c);
      ci = 0;
    } else {
      ci++;
    }

    yield();
  }
}

#endif // F_CPU
#endif // HIDLIGHT_INTERFACE
