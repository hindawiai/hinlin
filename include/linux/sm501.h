<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/linux/sm501.h
 *
 * Copyright (c) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	Vincent Sanders <vince@simtec.co.uk>
*/

बाह्य पूर्णांक sm501_unit_घातer(काष्ठा device *dev,
			    अचिन्हित पूर्णांक unit, अचिन्हित पूर्णांक to);

बाह्य अचिन्हित दीर्घ sm501_set_घड़ी(काष्ठा device *dev,
				     पूर्णांक clksrc, अचिन्हित दीर्घ freq);

बाह्य अचिन्हित दीर्घ sm501_find_घड़ी(काष्ठा device *dev,
				      पूर्णांक clksrc, अचिन्हित दीर्घ req_freq);

/* sm501_misc_control
 *
 * Modअगरy the SM501's MISC_CONTROL रेजिस्टर
*/

बाह्य पूर्णांक sm501_misc_control(काष्ठा device *dev,
			      अचिन्हित दीर्घ set, अचिन्हित दीर्घ clear);

/* sm501_modअगरy_reg
 *
 * Modअगरy a रेजिस्टर in the SM501 which may be shared with other
 * drivers.
*/

बाह्य अचिन्हित दीर्घ sm501_modअगरy_reg(काष्ठा device *dev,
				      अचिन्हित दीर्घ reg,
				      अचिन्हित दीर्घ set,
				      अचिन्हित दीर्घ clear);


/* Platक्रमm data definitions */

#घोषणा SM501FB_FLAG_USE_INIT_MODE	(1<<0)
#घोषणा SM501FB_FLAG_DISABLE_AT_EXIT	(1<<1)
#घोषणा SM501FB_FLAG_USE_HWCURSOR	(1<<2)
#घोषणा SM501FB_FLAG_USE_HWACCEL	(1<<3)
#घोषणा SM501FB_FLAG_PANEL_NO_FPEN	(1<<4)
#घोषणा SM501FB_FLAG_PANEL_NO_VBIASEN	(1<<5)
#घोषणा SM501FB_FLAG_PANEL_INV_FPEN	(1<<6)
#घोषणा SM501FB_FLAG_PANEL_INV_VBIASEN	(1<<7)

काष्ठा sm501_platdata_fbsub अणु
	काष्ठा fb_videomode	*def_mode;
	अचिन्हित पूर्णांक		 def_bpp;
	अचिन्हित दीर्घ		 max_mem;
	अचिन्हित पूर्णांक		 flags;
पूर्ण;

क्रमागत sm501_fb_routing अणु
	SM501_FB_OWN		= 0,	/* CRT=>CRT, Panel=>Panel */
	SM501_FB_CRT_PANEL	= 1,	/* Panel=>CRT, Panel=>Panel */
पूर्ण;

/* sm501_platdata_fb flag field bit definitions */

#घोषणा SM501_FBPD_SWAP_FB_ENDIAN	(1<<0)	/* need to endian swap */

/* sm501_platdata_fb
 *
 * configuration data क्रम the framebuffer driver
*/

काष्ठा sm501_platdata_fb अणु
	क्रमागत sm501_fb_routing		 fb_route;
	अचिन्हित पूर्णांक			 flags;
	काष्ठा sm501_platdata_fbsub	*fb_crt;
	काष्ठा sm501_platdata_fbsub	*fb_pnl;
पूर्ण;

/* gpio i2c
 *
 * Note, we have to pass in the bus number, as the number used will be
 * passed to the i2c-gpio driver's platक्रमm_device.id, subsequently used
 * to रेजिस्टर the i2c bus.
*/

काष्ठा sm501_platdata_gpio_i2c अणु
	अचिन्हित पूर्णांक		bus_num;
	अचिन्हित पूर्णांक		pin_sda;
	अचिन्हित पूर्णांक		pin_scl;
	पूर्णांक			udelay;
	पूर्णांक			समयout;
पूर्ण;

/* sm501_initdata
 *
 * use क्रम initialising values that may not have been setup
 * beक्रमe the driver is loaded.
*/

काष्ठा sm501_reg_init अणु
	अचिन्हित दीर्घ		set;
	अचिन्हित दीर्घ		mask;
पूर्ण;

#घोषणा SM501_USE_USB_HOST	(1<<0)
#घोषणा SM501_USE_USB_SLAVE	(1<<1)
#घोषणा SM501_USE_SSP0		(1<<2)
#घोषणा SM501_USE_SSP1		(1<<3)
#घोषणा SM501_USE_UART0		(1<<4)
#घोषणा SM501_USE_UART1		(1<<5)
#घोषणा SM501_USE_FBACCEL	(1<<6)
#घोषणा SM501_USE_AC97		(1<<7)
#घोषणा SM501_USE_I2S		(1<<8)
#घोषणा SM501_USE_GPIO		(1<<9)

#घोषणा SM501_USE_ALL		(0xffffffff)

काष्ठा sm501_initdata अणु
	काष्ठा sm501_reg_init	gpio_low;
	काष्ठा sm501_reg_init	gpio_high;
	काष्ठा sm501_reg_init	misc_timing;
	काष्ठा sm501_reg_init	misc_control;

	अचिन्हित दीर्घ		devices;
	अचिन्हित दीर्घ		mclk;		/* non-zero to modअगरy */
	अचिन्हित दीर्घ		m1xclk;		/* non-zero to modअगरy */
पूर्ण;

/* sm501_init_gpio
 *
 * शेष gpio settings
*/

काष्ठा sm501_init_gpio अणु
	काष्ठा sm501_reg_init	gpio_data_low;
	काष्ठा sm501_reg_init	gpio_data_high;
	काष्ठा sm501_reg_init	gpio_ddr_low;
	काष्ठा sm501_reg_init	gpio_ddr_high;
पूर्ण;

#घोषणा SM501_FLAG_SUSPEND_OFF		(1<<4)

/* sm501_platdata
 *
 * This is passed with the platक्रमm device to allow the board
 * to control the behaviour of the SM501 driver(s) which attach
 * to the device.
 *
*/

काष्ठा sm501_platdata अणु
	काष्ठा sm501_initdata		*init;
	काष्ठा sm501_init_gpio		*init_gpiop;
	काष्ठा sm501_platdata_fb	*fb;

	पूर्णांक				 flags;
	पूर्णांक				 gpio_base;

	पूर्णांक	(*get_घातer)(काष्ठा device *dev);
	पूर्णांक	(*set_घातer)(काष्ठा device *dev, अचिन्हित पूर्णांक on);

	काष्ठा sm501_platdata_gpio_i2c	*gpio_i2c;
	अचिन्हित पूर्णांक			 gpio_i2c_nr;
पूर्ण;

#अगर defined(CONFIG_PPC32)
#घोषणा smc501_पढ़ोl(addr)		ioपढ़ो32be((addr))
#घोषणा smc501_ग_लिखोl(val, addr)	ioग_लिखो32be((val), (addr))
#अन्यथा
#घोषणा smc501_पढ़ोl(addr)		पढ़ोl(addr)
#घोषणा smc501_ग_लिखोl(val, addr)	ग_लिखोl(val, addr)
#पूर्ण_अगर
