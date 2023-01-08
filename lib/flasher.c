#include "py/dynruntime.h"

// #define PAUSE 0x3169
#define BYTE_HIGH  0xF000
#define BYTE_LOW   0x0000

#define GPIO_BUS_ADDR   0x3FF44004
#define NOOP()          __asm__ volatile("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop")
#define DELAY400() ({NOOP(); NOOP(); NOOP(); NOOP(); NOOP(); NOOP(); NOOP(); NOOP();})
#define DELAY450() ({NOOP(); NOOP(); NOOP(); NOOP(); NOOP(); NOOP(); NOOP(); NOOP(); NOOP();})
#define READ_GPIO()     (*(volatile uint32_t *)GPIO_BUS_ADDR)
#define WRITE_GPIO(val) ((*(volatile uint32_t *)GPIO_BUS_ADDR) = (val))

STATIC mp_obj_t flash(mp_obj_t data) {
    // mask does not work, will need to fix in the future
    uint32_t mask = READ_GPIO() & 0xFFFF0FFF;

    mp_uint_t item_cnt;
    mp_obj_t *item_objs;
    mp_obj_get_array(data, &item_cnt, &item_objs);
    volatile uint32_t next;

    for (int i=0; i < item_cnt; ++i) {
        next = mp_obj_get_int(item_objs[i]);
        next = (next << 12) | mask;
        WRITE_GPIO(BYTE_HIGH);
        DELAY400();
        WRITE_GPIO(next);
        DELAY450();
        WRITE_GPIO(BYTE_LOW);
        DELAY400();
    }

    return mp_obj_new_int(0);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(flash_obj, flash);

// This is the entry point and is called when the module is imported
mp_obj_t mpy_init(mp_obj_fun_bc_t *self, size_t n_args, size_t n_kw, mp_obj_t *args) {
    // This must be first, it sets up the globals dict and other things
    MP_DYNRUNTIME_INIT_ENTRY

    // Make the function available in the module's namespace
    mp_store_global(MP_QSTR_flash, MP_OBJ_FROM_PTR(&flash_obj));

    // This must be last, it restores the globals dict
    MP_DYNRUNTIME_INIT_EXIT
}
