<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_GPIO_H__
#घोषणा __NVBIOS_GPIO_H__
क्रमागत dcb_gpio_func_name अणु
	DCB_GPIO_PANEL_POWER = 0x01,
	DCB_GPIO_FAN = 0x09,
	DCB_GPIO_TVDAC0 = 0x0c,
	DCB_GPIO_THERM_EXT_POWER_EVENT = 0x10,
	DCB_GPIO_TVDAC1 = 0x2d,
	DCB_GPIO_FAN_SENSE = 0x3d,
	DCB_GPIO_POWER_ALERT = 0x4c,
	DCB_GPIO_EXT_POWER_LOW = 0x79,
	DCB_GPIO_LOGO_LED_PWM = 0x84,
	DCB_GPIO_UNUSED = 0xff,
	DCB_GPIO_VID0 = 0x04,
	DCB_GPIO_VID1 = 0x05,
	DCB_GPIO_VID2 = 0x06,
	DCB_GPIO_VID3 = 0x1a,
	DCB_GPIO_VID4 = 0x73,
	DCB_GPIO_VID5 = 0x74,
	DCB_GPIO_VID6 = 0x75,
	DCB_GPIO_VID7 = 0x76,
	DCB_GPIO_VID_PWM = 0x81,
पूर्ण;

#घोषणा DCB_GPIO_LOG_सूची     0x02
#घोषणा DCB_GPIO_LOG_सूची_OUT 0x00
#घोषणा DCB_GPIO_LOG_सूची_IN  0x02
#घोषणा DCB_GPIO_LOG_VAL     0x01
#घोषणा DCB_GPIO_LOG_VAL_LO  0x00
#घोषणा DCB_GPIO_LOG_VAL_HI  0x01

काष्ठा dcb_gpio_func अणु
	u8 func;
	u8 line;
	u8 log[2];

	/* so far, "param" seems to only have an influence on PWM-related
	 * GPIOs such as FAN_CONTROL and PANEL_BACKLIGHT_LEVEL.
	 * अगर param equals 1, hardware PWM is available
	 * अगर param equals 0, the host should toggle the GPIO itself
	 */
	u8 param;
पूर्ण;

u16 dcb_gpio_table(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u16 dcb_gpio_entry(काष्ठा nvkm_bios *, पूर्णांक idx, पूर्णांक ent, u8 *ver, u8 *len);
u16 dcb_gpio_parse(काष्ठा nvkm_bios *, पूर्णांक idx, पूर्णांक ent, u8 *ver, u8 *len,
		   काष्ठा dcb_gpio_func *);
u16 dcb_gpio_match(काष्ठा nvkm_bios *, पूर्णांक idx, u8 func, u8 line,
		   u8 *ver, u8 *len, काष्ठा dcb_gpio_func *);
#पूर्ण_अगर
