<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KFR2R09 LCD panel support
 *
 * Copyright (C) 2009 Magnus Damm
 *
 * Register settings based on the out-of-tree t33fb.c driver
 * Copyright (C) 2008 Lineo Solutions, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <video/sh_mobile_lcdc.h>
#समावेश <mach/kfr2r09.h>
#समावेश <cpu/sh7724.h>

/* The on-board LCD module is a Hitachi TX07D34VM0AAA. This module is made
 * up of a 240x400 LCD hooked up to a R61517 driver IC. The driver IC is
 * communicating with the मुख्य port of the LCDC using an 18-bit SYS पूर्णांकerface.
 *
 * The device code क्रम this LCD module is 0x01221517.
 */

अटल स्थिर अचिन्हित अक्षर data_frame_अगर[] = अणु
	0x02, /* WEMODE: 1=cont, 0=one-shot */
	0x00, 0x00,
	0x00, /* EPF, DFM */
	0x02, /* RIM[1] : 1 (18bpp) */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर data_panel[] = अणु
	0x0b,
	0x63, /* 400 lines */
	0x04, 0x00, 0x00, 0x04, 0x11, 0x00, 0x00,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर data_timing[] = अणु
	0x00, 0x00, 0x13, 0x08, 0x08,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर data_timing_src[] = अणु
	0x11, 0x01, 0x00, 0x01,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर data_gamma[] = अणु
	0x01, 0x02, 0x08, 0x23,	0x03, 0x0c, 0x00, 0x06,	0x00, 0x00,
	0x01, 0x00, 0x0c, 0x23, 0x03, 0x08, 0x02, 0x06, 0x00, 0x00,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर data_घातer[] = अणु
	0x07, 0xc5, 0xdc, 0x02,	0x33, 0x0a,
पूर्ण;

अटल अचिन्हित दीर्घ पढ़ो_reg(व्योम *sohandle,
			      काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	वापस so->पढ़ो_data(sohandle);
पूर्ण

अटल व्योम ग_लिखो_reg(व्योम *sohandle,
		      काष्ठा sh_mobile_lcdc_sys_bus_ops *so,
		      पूर्णांक i, अचिन्हित दीर्घ v)
अणु
	अगर (i)
		so->ग_लिखो_data(sohandle, v); /* PTH4/LCDRS High [param, 17:0] */
	अन्यथा
		so->ग_लिखो_index(sohandle, v); /* PTH4/LCDRS Low [cmd, 7:0] */
पूर्ण

अटल व्योम ग_लिखो_data(व्योम *sohandle,
		       काष्ठा sh_mobile_lcdc_sys_bus_ops *so,
		       अचिन्हित अक्षर स्थिर *data, पूर्णांक no_data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < no_data; i++)
		ग_लिखो_reg(sohandle, so, 1, data[i]);
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_device_code(व्योम *sohandle,
				      काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	अचिन्हित दीर्घ device_code;

	/* access protect OFF */
	ग_लिखो_reg(sohandle, so, 0, 0xb0);
	ग_लिखो_reg(sohandle, so, 1, 0x00);

	/* deep standby OFF */
	ग_लिखो_reg(sohandle, so, 0, 0xb1);
	ग_लिखो_reg(sohandle, so, 1, 0x00);

	/* device code command */
	ग_लिखो_reg(sohandle, so, 0, 0xbf);
	mdelay(50);

	/* dummy पढ़ो */
	पढ़ो_reg(sohandle, so);

	/* पढ़ो device code */
	device_code = ((पढ़ो_reg(sohandle, so) & 0xff) << 24);
	device_code |= ((पढ़ो_reg(sohandle, so) & 0xff) << 16);
	device_code |= ((पढ़ो_reg(sohandle, so) & 0xff) << 8);
	device_code |= (पढ़ो_reg(sohandle, so) & 0xff);

	वापस device_code;
पूर्ण

अटल व्योम ग_लिखो_memory_start(व्योम *sohandle,
			       काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	ग_लिखो_reg(sohandle, so, 0, 0x2c);
पूर्ण

अटल व्योम clear_memory(व्योम *sohandle,
			 काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	पूर्णांक i;

	/* ग_लिखो start */
	ग_लिखो_memory_start(sohandle, so);

	/* paपूर्णांक it black */
	क्रम (i = 0; i < (240 * 400); i++)
		ग_लिखो_reg(sohandle, so, 1, 0x00);
पूर्ण

अटल व्योम display_on(व्योम *sohandle,
		       काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	/* access protect off */
	ग_लिखो_reg(sohandle, so, 0, 0xb0);
	ग_लिखो_reg(sohandle, so, 1, 0x00);

	/* निकास deep standby mode */
	ग_लिखो_reg(sohandle, so, 0, 0xb1);
	ग_लिखो_reg(sohandle, so, 1, 0x00);

	/* frame memory I/F */
	ग_लिखो_reg(sohandle, so, 0, 0xb3);
	ग_लिखो_data(sohandle, so, data_frame_अगर, ARRAY_SIZE(data_frame_अगर));

	/* display mode and frame memory ग_लिखो mode */
	ग_लिखो_reg(sohandle, so, 0, 0xb4);
	ग_लिखो_reg(sohandle, so, 1, 0x00); /* DBI, पूर्णांकernal घड़ी */

	/* panel */
	ग_लिखो_reg(sohandle, so, 0, 0xc0);
	ग_लिखो_data(sohandle, so, data_panel, ARRAY_SIZE(data_panel));

	/* timing (normal) */
	ग_लिखो_reg(sohandle, so, 0, 0xc1);
	ग_लिखो_data(sohandle, so, data_timing, ARRAY_SIZE(data_timing));

	/* timing (partial) */
	ग_लिखो_reg(sohandle, so, 0, 0xc2);
	ग_लिखो_data(sohandle, so, data_timing, ARRAY_SIZE(data_timing));

	/* timing (idle) */
	ग_लिखो_reg(sohandle, so, 0, 0xc3);
	ग_लिखो_data(sohandle, so, data_timing, ARRAY_SIZE(data_timing));

	/* timing (source/VCOM/gate driving) */
	ग_लिखो_reg(sohandle, so, 0, 0xc4);
	ग_लिखो_data(sohandle, so, data_timing_src, ARRAY_SIZE(data_timing_src));

	/* gamma (red) */
	ग_लिखो_reg(sohandle, so, 0, 0xc8);
	ग_लिखो_data(sohandle, so, data_gamma, ARRAY_SIZE(data_gamma));

	/* gamma (green) */
	ग_लिखो_reg(sohandle, so, 0, 0xc9);
	ग_लिखो_data(sohandle, so, data_gamma, ARRAY_SIZE(data_gamma));

	/* gamma (blue) */
	ग_लिखो_reg(sohandle, so, 0, 0xca);
	ग_लिखो_data(sohandle, so, data_gamma, ARRAY_SIZE(data_gamma));

	/* घातer (common) */
	ग_लिखो_reg(sohandle, so, 0, 0xd0);
	ग_लिखो_data(sohandle, so, data_घातer, ARRAY_SIZE(data_घातer));

	/* VCOM */
	ग_लिखो_reg(sohandle, so, 0, 0xd1);
	ग_लिखो_reg(sohandle, so, 1, 0x00);
	ग_लिखो_reg(sohandle, so, 1, 0x0f);
	ग_लिखो_reg(sohandle, so, 1, 0x02);

	/* घातer (normal) */
	ग_लिखो_reg(sohandle, so, 0, 0xd2);
	ग_लिखो_reg(sohandle, so, 1, 0x63);
	ग_लिखो_reg(sohandle, so, 1, 0x24);

	/* घातer (partial) */
	ग_लिखो_reg(sohandle, so, 0, 0xd3);
	ग_लिखो_reg(sohandle, so, 1, 0x63);
	ग_लिखो_reg(sohandle, so, 1, 0x24);

	/* घातer (idle) */
	ग_लिखो_reg(sohandle, so, 0, 0xd4);
	ग_लिखो_reg(sohandle, so, 1, 0x63);
	ग_लिखो_reg(sohandle, so, 1, 0x24);

	ग_लिखो_reg(sohandle, so, 0, 0xd8);
	ग_लिखो_reg(sohandle, so, 1, 0x77);
	ग_लिखो_reg(sohandle, so, 1, 0x77);

	/* TE संकेत */
	ग_लिखो_reg(sohandle, so, 0, 0x35);
	ग_लिखो_reg(sohandle, so, 1, 0x00);

	/* TE संकेत line */
	ग_लिखो_reg(sohandle, so, 0, 0x44);
	ग_लिखो_reg(sohandle, so, 1, 0x00);
	ग_लिखो_reg(sohandle, so, 1, 0x00);

	/* column address */
	ग_लिखो_reg(sohandle, so, 0, 0x2a);
	ग_लिखो_reg(sohandle, so, 1, 0x00);
	ग_लिखो_reg(sohandle, so, 1, 0x00);
	ग_लिखो_reg(sohandle, so, 1, 0x00);
	ग_लिखो_reg(sohandle, so, 1, 0xef);

	/* page address */
	ग_लिखो_reg(sohandle, so, 0, 0x2b);
	ग_लिखो_reg(sohandle, so, 1, 0x00);
	ग_लिखो_reg(sohandle, so, 1, 0x00);
	ग_लिखो_reg(sohandle, so, 1, 0x01);
	ग_लिखो_reg(sohandle, so, 1, 0x8f);

	/* निकास sleep mode */
	ग_लिखो_reg(sohandle, so, 0, 0x11);

	mdelay(120);

	/* clear vram */
	clear_memory(sohandle, so);

	/* display ON */
	ग_लिखो_reg(sohandle, so, 0, 0x29);
	mdelay(1);

	ग_लिखो_memory_start(sohandle, so);
पूर्ण

पूर्णांक kfr2r09_lcd_setup(व्योम *sohandle, काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	/* घातer on */
	gpio_set_value(GPIO_PTF4, 0);  /* PROTECT/ -> L */
	gpio_set_value(GPIO_PTE4, 0);  /* LCD_RST/ -> L */
	gpio_set_value(GPIO_PTF4, 1);  /* PROTECT/ -> H */
	udelay(1100);
	gpio_set_value(GPIO_PTE4, 1);  /* LCD_RST/ -> H */
	udelay(10);
	gpio_set_value(GPIO_PTF4, 0);  /* PROTECT/ -> L */
	mdelay(20);

	अगर (पढ़ो_device_code(sohandle, so) != 0x01221517)
		वापस -ENODEV;

	pr_info("KFR2R09 WQVGA LCD Module detected.\n");

	display_on(sohandle, so);
	वापस 0;
पूर्ण

व्योम kfr2r09_lcd_start(व्योम *sohandle, काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	ग_लिखो_memory_start(sohandle, so);
पूर्ण
