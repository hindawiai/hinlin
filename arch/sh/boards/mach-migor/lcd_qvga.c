<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम SuperH MigoR Quarter VGA LCD Panel
 *
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on lcd_घातertip.c from Kenati Technologies Pvt Ltd.
 * Copyright (c) 2007 Ujjwal Pande <ujjwal@kenati.com>,
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <video/sh_mobile_lcdc.h>
#समावेश <cpu/sh7722.h>
#समावेश <mach/migor.h>

/* LCD Module is a PH240320T according to board schematics. This module
 * is made up of a 240x320 LCD hooked up to a R61505U (or HX8347-A01?)
 * Driver IC. This IC is connected to the SH7722 built-in LCDC using a
 * SYS-80 पूर्णांकerface configured in 16 bit mode.
 *
 * Index 0: "Device Code Read" वापसs 0x1505.
 */

अटल व्योम reset_lcd_module(व्योम)
अणु
	gpio_set_value(GPIO_PTH2, 0);
	mdelay(2);
	gpio_set_value(GPIO_PTH2, 1);
	mdelay(1);
पूर्ण

/* DB0-DB7 are connected to D1-D8, and DB8-DB15 to D10-D17 */

अटल अचिन्हित दीर्घ adjust_reg18(अचिन्हित लघु data)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	पंचांगp1 = (data<<1 | 0x00000001) & 0x000001FF;
	पंचांगp2 = (data<<2 | 0x00000200) & 0x0003FE00;
	वापस पंचांगp1 | पंचांगp2;
पूर्ण

अटल व्योम ग_लिखो_reg(व्योम *sys_ops_handle,
		       काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops,
		       अचिन्हित लघु reg, अचिन्हित लघु data)
अणु
	sys_ops->ग_लिखो_index(sys_ops_handle, adjust_reg18(reg << 8 | data));
पूर्ण

अटल व्योम ग_लिखो_reg16(व्योम *sys_ops_handle,
			काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops,
			अचिन्हित लघु reg, अचिन्हित लघु data)
अणु
	sys_ops->ग_लिखो_index(sys_ops_handle, adjust_reg18(reg));
	sys_ops->ग_लिखो_data(sys_ops_handle, adjust_reg18(data));
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_reg16(व्योम *sys_ops_handle,
				काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops,
				अचिन्हित लघु reg)
अणु
	अचिन्हित दीर्घ data;

	sys_ops->ग_लिखो_index(sys_ops_handle, adjust_reg18(reg));
	data = sys_ops->पढ़ो_data(sys_ops_handle);
	वापस ((data >> 1) & 0xff) | ((data >> 2) & 0xff00);
पूर्ण

अटल व्योम migor_lcd_qvga_seq(व्योम *sys_ops_handle,
			       काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops,
			       अचिन्हित लघु स्थिर *data, पूर्णांक no_data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < no_data; i += 2)
		ग_लिखो_reg16(sys_ops_handle, sys_ops, data[i], data[i + 1]);
पूर्ण

अटल स्थिर अचिन्हित लघु sync_data[] = अणु
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
पूर्ण;

अटल स्थिर अचिन्हित लघु magic0_data[] = अणु
	0x0060, 0x2700, 0x0008, 0x0808, 0x0090, 0x001A, 0x0007, 0x0001,
	0x0017, 0x0001, 0x0019, 0x0000, 0x0010, 0x17B0, 0x0011, 0x0116,
	0x0012, 0x0198, 0x0013, 0x1400, 0x0029, 0x000C, 0x0012, 0x01B8,
पूर्ण;

अटल स्थिर अचिन्हित लघु magic1_data[] = अणु
	0x0030, 0x0307, 0x0031, 0x0303, 0x0032, 0x0603, 0x0033, 0x0202,
	0x0034, 0x0202, 0x0035, 0x0202, 0x0036, 0x1F1F, 0x0037, 0x0303,
	0x0038, 0x0303, 0x0039, 0x0603, 0x003A, 0x0202, 0x003B, 0x0102,
	0x003C, 0x0204, 0x003D, 0x0000, 0x0001, 0x0100, 0x0002, 0x0300,
	0x0003, 0x5028, 0x0020, 0x00ef, 0x0021, 0x0000, 0x0004, 0x0000,
	0x0009, 0x0000, 0x000A, 0x0008, 0x000C, 0x0000, 0x000D, 0x0000,
	0x0015, 0x8000,
पूर्ण;

अटल स्थिर अचिन्हित लघु magic2_data[] = अणु
	0x0061, 0x0001, 0x0092, 0x0100, 0x0093, 0x0001, 0x0007, 0x0021,
पूर्ण;

अटल स्थिर अचिन्हित लघु magic3_data[] = अणु
	0x0010, 0x16B0, 0x0011, 0x0111, 0x0007, 0x0061,
पूर्ण;

पूर्णांक migor_lcd_qvga_setup(व्योम *sohandle, काष्ठा sh_mobile_lcdc_sys_bus_ops *so)
अणु
	अचिन्हित दीर्घ xres = 320;
	अचिन्हित दीर्घ yres = 240;
	पूर्णांक k;

	reset_lcd_module();
	migor_lcd_qvga_seq(sohandle, so, sync_data, ARRAY_SIZE(sync_data));

	अगर (पढ़ो_reg16(sohandle, so, 0) != 0x1505)
		वापस -ENODEV;

	pr_info("Migo-R QVGA LCD Module detected.\n");

	migor_lcd_qvga_seq(sohandle, so, sync_data, ARRAY_SIZE(sync_data));
	ग_लिखो_reg16(sohandle, so, 0x00A4, 0x0001);
	mdelay(10);

	migor_lcd_qvga_seq(sohandle, so, magic0_data, ARRAY_SIZE(magic0_data));
	mdelay(100);

	migor_lcd_qvga_seq(sohandle, so, magic1_data, ARRAY_SIZE(magic1_data));
	ग_लिखो_reg16(sohandle, so, 0x0050, 0xef - (yres - 1));
	ग_लिखो_reg16(sohandle, so, 0x0051, 0x00ef);
	ग_लिखो_reg16(sohandle, so, 0x0052, 0x0000);
	ग_लिखो_reg16(sohandle, so, 0x0053, xres - 1);

	migor_lcd_qvga_seq(sohandle, so, magic2_data, ARRAY_SIZE(magic2_data));
	mdelay(10);

	migor_lcd_qvga_seq(sohandle, so, magic3_data, ARRAY_SIZE(magic3_data));
	mdelay(40);

	/* clear GRAM to aव्योम displaying garbage */

	ग_लिखो_reg16(sohandle, so, 0x0020, 0x0000); /* horiz addr */
	ग_लिखो_reg16(sohandle, so, 0x0021, 0x0000); /* vert addr */

	क्रम (k = 0; k < (xres * 256); k++) /* yes, 256 words per line */
		ग_लिखो_reg16(sohandle, so, 0x0022, 0x0000);

	ग_लिखो_reg16(sohandle, so, 0x0020, 0x0000); /* reset horiz addr */
	ग_लिखो_reg16(sohandle, so, 0x0021, 0x0000); /* reset vert addr */
	ग_लिखो_reg16(sohandle, so, 0x0007, 0x0173);
	mdelay(40);

	/* enable display */
	ग_लिखो_reg(sohandle, so, 0x00, 0x22);
	mdelay(100);
	वापस 0;
पूर्ण
