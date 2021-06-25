<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#समावेश <linux/via-core.h>
#समावेश "global.h"

व्योम viafb_get_device_support_state(u32 *support_state)
अणु
	*support_state = CRT_Device;

	अगर (viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_name == VT1632_TMDS)
		*support_state |= DVI_Device;

	अगर (viaparinfo->chip_info->lvds_chip_info.lvds_chip_name == VT1631_LVDS)
		*support_state |= LCD_Device;
पूर्ण

व्योम viafb_get_device_connect_state(u32 *connect_state)
अणु
	bool mobile = false;

	*connect_state = CRT_Device;

	अगर (viafb_dvi_sense())
		*connect_state |= DVI_Device;

	viafb_lcd_get_mobile_state(&mobile);
	अगर (mobile)
		*connect_state |= LCD_Device;
पूर्ण

bool viafb_lcd_get_support_expand_state(u32 xres, u32 yres)
अणु
	अचिन्हित पूर्णांक support_state = 0;

	चयन (viafb_lcd_panel_id) अणु
	हाल LCD_PANEL_ID0_640X480:
		अगर ((xres < 640) && (yres < 480))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID1_800X600:
		अगर ((xres < 800) && (yres < 600))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID2_1024X768:
		अगर ((xres < 1024) && (yres < 768))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID3_1280X768:
		अगर ((xres < 1280) && (yres < 768))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID4_1280X1024:
		अगर ((xres < 1280) && (yres < 1024))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID5_1400X1050:
		अगर ((xres < 1400) && (yres < 1050))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID6_1600X1200:
		अगर ((xres < 1600) && (yres < 1200))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID7_1366X768:
		अगर ((xres < 1366) && (yres < 768))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID8_1024X600:
		अगर ((xres < 1024) && (yres < 600))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_ID9_1280X800:
		अगर ((xres < 1280) && (yres < 800))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_IDA_800X480:
		अगर ((xres < 800) && (yres < 480))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_IDB_1360X768:
		अगर ((xres < 1360) && (yres < 768))
			support_state = true;
		अवरोध;

	हाल LCD_PANEL_IDC_480X640:
		अगर ((xres < 480) && (yres < 640))
			support_state = true;
		अवरोध;

	शेष:
		support_state = false;
		अवरोध;
	पूर्ण

	वापस support_state;
पूर्ण

/*====================================================================*/
/*                      Gamma Function Implementation*/
/*====================================================================*/

व्योम viafb_set_gamma_table(पूर्णांक bpp, अचिन्हित पूर्णांक *gamma_table)
अणु
	पूर्णांक i, sr1a;
	पूर्णांक active_device_amount = 0;
	पूर्णांक device_status = viafb_DeviceStatus;

	क्रम (i = 0; i < माप(viafb_DeviceStatus) * 8; i++) अणु
		अगर (device_status & 1)
			active_device_amount++;
		device_status >>= 1;
	पूर्ण

	/* 8 bpp mode can't adjust gamma */
	अगर (bpp == 8)
		वापस ;

	/* Enable Gamma */
	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_CLE266:
	हाल UNICHROME_K400:
		viafb_ग_लिखो_reg_mask(SR16, VIASR, 0x80, BIT7);
		अवरोध;

	हाल UNICHROME_K800:
	हाल UNICHROME_PM800:
	हाल UNICHROME_CN700:
	हाल UNICHROME_CX700:
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M890:
	हाल UNICHROME_P4M900:
		viafb_ग_लिखो_reg_mask(CR33, VIACR, 0x80, BIT7);
		अवरोध;
	पूर्ण
	sr1a = (अचिन्हित पूर्णांक)viafb_पढ़ो_reg(VIASR, SR1A);
	viafb_ग_लिखो_reg_mask(SR1A, VIASR, 0x0, BIT0);

	/* Fill IGA1 Gamma Table */
	outb(0, LUT_INDEX_WRITE);
	क्रम (i = 0; i < 256; i++) अणु
		outb(gamma_table[i] >> 16, LUT_DATA);
		outb(gamma_table[i] >> 8 & 0xFF, LUT_DATA);
		outb(gamma_table[i] & 0xFF, LUT_DATA);
	पूर्ण

	/* If adjust Gamma value in SAMM, fill IGA1,
	   IGA2 Gamma table simultaneous. */
	/* Switch to IGA2 Gamma Table */
	अगर ((active_device_amount > 1) &&
		!((viaparinfo->chip_info->gfx_chip_name ==
		UNICHROME_CLE266) &&
		(viaparinfo->chip_info->gfx_chip_revision < 15))) अणु
		viafb_ग_लिखो_reg_mask(SR1A, VIASR, 0x01, BIT0);
		viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x02, BIT1);

		/* Fill IGA2 Gamma Table */
		outb(0, LUT_INDEX_WRITE);
		क्रम (i = 0; i < 256; i++) अणु
			outb(gamma_table[i] >> 16, LUT_DATA);
			outb(gamma_table[i] >> 8 & 0xFF, LUT_DATA);
			outb(gamma_table[i] & 0xFF, LUT_DATA);
		पूर्ण
	पूर्ण
	viafb_ग_लिखो_reg(SR1A, VIASR, sr1a);
पूर्ण

व्योम viafb_get_gamma_table(अचिन्हित पूर्णांक *gamma_table)
अणु
	अचिन्हित अक्षर color_r, color_g, color_b;
	अचिन्हित अक्षर sr1a = 0;
	पूर्णांक i;

	/* Enable Gamma */
	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_CLE266:
	हाल UNICHROME_K400:
		viafb_ग_लिखो_reg_mask(SR16, VIASR, 0x80, BIT7);
		अवरोध;

	हाल UNICHROME_K800:
	हाल UNICHROME_PM800:
	हाल UNICHROME_CN700:
	हाल UNICHROME_CX700:
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M890:
	हाल UNICHROME_P4M900:
		viafb_ग_लिखो_reg_mask(CR33, VIACR, 0x80, BIT7);
		अवरोध;
	पूर्ण
	sr1a = viafb_पढ़ो_reg(VIASR, SR1A);
	viafb_ग_लिखो_reg_mask(SR1A, VIASR, 0x0, BIT0);

	/* Reading gamma table to get color value */
	outb(0, LUT_INDEX_READ);
	क्रम (i = 0; i < 256; i++) अणु
		color_r = inb(LUT_DATA);
		color_g = inb(LUT_DATA);
		color_b = inb(LUT_DATA);
		gamma_table[i] =
		    ((((u32) color_r) << 16) |
		     (((u16) color_g) << 8)) | color_b;
	पूर्ण
	viafb_ग_लिखो_reg(SR1A, VIASR, sr1a);
पूर्ण

व्योम viafb_get_gamma_support_state(पूर्णांक bpp, अचिन्हित पूर्णांक *support_state)
अणु
	अगर (bpp == 8)
		*support_state = None_Device;
	अन्यथा
		*support_state = CRT_Device | DVI_Device | LCD_Device;
पूर्ण
