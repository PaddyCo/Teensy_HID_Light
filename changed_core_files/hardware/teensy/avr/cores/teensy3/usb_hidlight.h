#ifndef USBhidlight_h_
#define USBhidlight_h_

#include "usb_desc.h"
#include "usb_dev.h"

#if defined(HIDLIGHT_INTERFACE)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
void usb_hidlight_on_update(void (*updateFunc)(int[]), void (*logFunc)(usb_packet_t));
#ifdef __cplusplus
}
#endif


// C++ interface
#ifdef __cplusplus
class usb_hidlight_class
{
public:
  void onUpdate(void (*updateFunc)(int[]), void (*logFunc)(usb_packet_t)) { usb_hidlight_on_update(updateFunc, logFunc); }
};

extern usb_hidlight_class HIDLight;

#endif // __cplusplus

#endif // HIDLIGHT_INTERFACE

#endif // USBhidlight_h_
