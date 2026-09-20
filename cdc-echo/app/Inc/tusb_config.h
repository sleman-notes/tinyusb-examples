#ifndef TUSB_CONFIG_H_
#define TUSB_CONFIG_H_

// defined by compiler flags for flexibility
#ifndef CFG_TUSB_MCU
#error CFG_TUSB_MCU must be defined
#endif

#define CFG_TUSB_OS           OPT_OS_NONE
#define CFG_TUSB_DEBUG        0

#define CFG_TUD_ENABLED       1

#define CFG_TUD_CDC              1
#define CFG_TUD_CDC_NOTIFY       1

#endif /* TUSB_CONFIG_H_ */