# Release Notes

--------------------------------------------------------------------------------

# Release v0.11.0
 -Backward compatinility issue:
     -systemStartUpCallback function pointer name corrected to match Nextion functionality/documentation new name: nextionReadyCallback
     
 -Error code list updated (NexHardware.cpp)
- nextionStartupCallback function added called when when Nextion has started or reset

# Release v0.10.0

  - version: v0.10.0
  - base: v0.9.0
## Brief
Enhanced and corrected Nextion library version for Arduino/Esp8266/NodeMcu, based on original Nextion Arduino library

- Added support for NodeMcu/esp8266, Software serial, Software serial can be used with arduino also
- Added support for global Nextion objects. (Optional page parameter added in the components)
- NexVariable corrected to use int32_t data type
- NextText corrected to return tru/false, and string length is returned in len parameter
- NextText String object support added
- other small bug fixes done
- Added to support global Nextion events like CurrentPageIdCallback,systemStartUpCallback,...

# Release v0.9.0

  - version: v0.9.0
  - base: v0.7.0
  
## Brief

Support all components in Nextion Editor v0.38. 

## Details

Added APIs of new attrubutes and components supported by Nextion Editor v0.38.


# Release v0.7.0

  - version: v0.7.0
  - base: no base version
  - author: Wu Pengfei <pengfei.wu@itead.cc>
  - date: 8/20/2015 13:17:20 

## Brief

Support all components in Nextion Editor v0.26. 

## Details

First release. 


--------------------------------------------------------------------------------

# The End!

--------------------------------------------------------------------------------
