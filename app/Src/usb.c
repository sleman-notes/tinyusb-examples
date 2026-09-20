#include "config.h"
#include "tusb.h"

uint32_t tusb_time_millis_api(void)
{
    return (uint32_t)ticks_get();
}

void OTG_FS_IRQHandler(void)
{
    tud_int_handler(0);
}

void usb_init(void)
{
    const tusb_rhport_init_t dev_init = 
    {
        .role  = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_FULL
    };

    OTGFS_PCLK_EN();
    tusb_init(0, &dev_init);
}