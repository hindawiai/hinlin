<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#समावेश <linux/via-core.h>
#समावेश <linux/via_i2c.h>
#समावेश "global.h"

अटल स्थिर काष्ठा IODATA common_init_data[] = अणु
/*  Index, Mask, Value */
	/* Set panel घातer sequence timing */
	अणु0x10, 0xC0, 0x00पूर्ण,
	/* T1: VDD on - Data on. Each increment is 1 ms. (50ms = 031h) */
	अणु0x0B, 0xFF, 0x40पूर्ण,
	/* T2: Data on - Backlight on. Each increment is 2 ms. (210ms = 068h) */
	अणु0x0C, 0xFF, 0x31पूर्ण,
	/* T3: Backlight off -Data off. Each increment is 2 ms. (210ms = 068h)*/
	अणु0x0D, 0xFF, 0x31पूर्ण,
	/* T4: Data off - VDD off. Each increment is 1 ms. (50ms = 031h) */
	अणु0x0E, 0xFF, 0x68पूर्ण,
	/* T5: VDD off - VDD on. Each increment is 100 ms. (500ms = 04h) */
	अणु0x0F, 0xFF, 0x68पूर्ण,
	/* LVDS output घातer up */
	अणु0x09, 0xA0, 0xA0पूर्ण,
	/* turn on back light */
	अणु0x10, 0x33, 0x13पूर्ण
पूर्ण;

/* Index, Mask, Value */
अटल स्थिर काष्ठा IODATA dual_channel_enable_data = अणु0x08, 0xF0, 0xE0पूर्ण;
अटल स्थिर काष्ठा IODATA single_channel_enable_data = अणु0x08, 0xF0, 0x00पूर्ण;
अटल स्थिर काष्ठा IODATA dithering_enable_data = अणु0x0A, 0x70, 0x50पूर्ण;
अटल स्थिर काष्ठा IODATA dithering_disable_data = अणु0x0A, 0x70, 0x00पूर्ण;
अटल स्थिर काष्ठा IODATA vdd_on_data = अणु0x10, 0x20, 0x20पूर्ण;
अटल स्थिर काष्ठा IODATA vdd_off_data = अणु0x10, 0x20, 0x00पूर्ण;

u8 viafb_gpio_i2c_पढ़ो_lvds(काष्ठा lvds_setting_inक्रमmation
	*plvds_setting_info, काष्ठा lvds_chip_inक्रमmation *plvds_chip_info,
	u8 index)
अणु
	u8 data;

	viafb_i2c_पढ़ोbyte(plvds_chip_info->i2c_port,
			   plvds_chip_info->lvds_chip_slave_addr, index, &data);
	वापस data;
पूर्ण

व्योम viafb_gpio_i2c_ग_लिखो_mask_lvds(काष्ठा lvds_setting_inक्रमmation
			      *plvds_setting_info, काष्ठा lvds_chip_inक्रमmation
			      *plvds_chip_info, काष्ठा IODATA io_data)
अणु
	पूर्णांक index, data;

	index = io_data.Index;
	data = viafb_gpio_i2c_पढ़ो_lvds(plvds_setting_info, plvds_chip_info,
		index);
	data = (data & (~io_data.Mask)) | io_data.Data;

	viafb_i2c_ग_लिखोbyte(plvds_chip_info->i2c_port,
			    plvds_chip_info->lvds_chip_slave_addr, index, data);
पूर्ण

व्योम viafb_init_lvds_vt1636(काष्ठा lvds_setting_inक्रमmation
	*plvds_setting_info, काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	पूर्णांक reg_num, i;

	/* Common settings: */
	reg_num = ARRAY_SIZE(common_init_data);
	क्रम (i = 0; i < reg_num; i++)
		viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info,
			plvds_chip_info, common_init_data[i]);

	/* Input Data Mode Select */
	अगर (plvds_setting_info->device_lcd_dualedge)
		viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info,
			plvds_chip_info, dual_channel_enable_data);
	अन्यथा
		viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info,
			plvds_chip_info, single_channel_enable_data);

	अगर (plvds_setting_info->LCDDithering)
		viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info,
			plvds_chip_info, dithering_enable_data);
	अन्यथा
		viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info,
			plvds_chip_info, dithering_disable_data);
पूर्ण

व्योम viafb_enable_lvds_vt1636(काष्ठा lvds_setting_inक्रमmation
			*plvds_setting_info,
			काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info, plvds_chip_info,
		vdd_on_data);
पूर्ण

व्योम viafb_disable_lvds_vt1636(काष्ठा lvds_setting_inक्रमmation
			 *plvds_setting_info,
			 काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info, plvds_chip_info,
		vdd_off_data);
पूर्ण

bool viafb_lvds_identअगरy_vt1636(u8 i2c_adapter)
अणु
	u8 Buffer[2];

	DEBUG_MSG(KERN_INFO "viafb_lvds_identify_vt1636.\n");

	/* Sense VT1636 LVDS Transmiter */
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_slave_addr =
		VT1636_LVDS_I2C_ADDR;

	/* Check venकरोr ID first: */
	अगर (viafb_i2c_पढ़ोbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR,
					0x00, &Buffer[0]))
		वापस false;
	viafb_i2c_पढ़ोbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR, 0x01, &Buffer[1]);

	अगर (!((Buffer[0] == 0x06) && (Buffer[1] == 0x11)))
		वापस false;

	/* Check Chip ID: */
	viafb_i2c_पढ़ोbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR, 0x02, &Buffer[0]);
	viafb_i2c_पढ़ोbyte(i2c_adapter, VT1636_LVDS_I2C_ADDR, 0x03, &Buffer[1]);
	अगर ((Buffer[0] == 0x45) && (Buffer[1] == 0x33)) अणु
		viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			VT1636_LVDS;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक get_clk_range_index(u32 Clk)
अणु
	अगर (Clk < DPA_CLK_30M)
		वापस DPA_CLK_RANGE_30M;
	अन्यथा अगर (Clk < DPA_CLK_50M)
		वापस DPA_CLK_RANGE_30_50M;
	अन्यथा अगर (Clk < DPA_CLK_70M)
		वापस DPA_CLK_RANGE_50_70M;
	अन्यथा अगर (Clk < DPA_CLK_100M)
		वापस DPA_CLK_RANGE_70_100M;
	अन्यथा अगर (Clk < DPA_CLK_150M)
		वापस DPA_CLK_RANGE_100_150M;
	अन्यथा
		वापस DPA_CLK_RANGE_150M;
पूर्ण

अटल व्योम set_dpa_vt1636(काष्ठा lvds_setting_inक्रमmation
	*plvds_setting_info, काष्ठा lvds_chip_inक्रमmation *plvds_chip_info,
		    काष्ठा VT1636_DPA_SETTING *p_vt1636_dpa_setting)
अणु
	काष्ठा IODATA io_data;

	io_data.Index = 0x09;
	io_data.Mask = 0x1F;
	io_data.Data = p_vt1636_dpa_setting->CLK_SEL_ST1;
	viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info,
		plvds_chip_info, io_data);

	io_data.Index = 0x08;
	io_data.Mask = 0x0F;
	io_data.Data = p_vt1636_dpa_setting->CLK_SEL_ST2;
	viafb_gpio_i2c_ग_लिखो_mask_lvds(plvds_setting_info, plvds_chip_info,
		io_data);
पूर्ण

व्योम viafb_vt1636_patch_skew_on_vt3324(
	काष्ठा lvds_setting_inक्रमmation *plvds_setting_info,
	काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	काष्ठा VT1636_DPA_SETTING dpa = अणु0x00, 0x00पूर्ण, dpa_16x12 = अणु0x0B, 0x03पूर्ण,
		*pdpa;
	पूर्णांक index;

	DEBUG_MSG(KERN_INFO "viafb_vt1636_patch_skew_on_vt3324.\n");

	/* Graphics DPA settings: */
	index = get_clk_range_index(plvds_setting_info->vclk);
	viafb_set_dpa_gfx(plvds_chip_info->output_पूर्णांकerface,
		    &GFX_DPA_SETTING_TBL_VT3324[index]);

	/* LVDS Transmitter DPA settings: */
	अगर (plvds_setting_info->lcd_panel_hres == 1600 &&
		plvds_setting_info->lcd_panel_vres == 1200)
		pdpa = &dpa_16x12;
	अन्यथा
		pdpa = &dpa;

	set_dpa_vt1636(plvds_setting_info, plvds_chip_info, pdpa);
पूर्ण

व्योम viafb_vt1636_patch_skew_on_vt3327(
	काष्ठा lvds_setting_inक्रमmation *plvds_setting_info,
	काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	काष्ठा VT1636_DPA_SETTING dpa = अणु0x00, 0x00पूर्ण;
	पूर्णांक index;

	DEBUG_MSG(KERN_INFO "viafb_vt1636_patch_skew_on_vt3327.\n");

	/* Graphics DPA settings: */
	index = get_clk_range_index(plvds_setting_info->vclk);
	viafb_set_dpa_gfx(plvds_chip_info->output_पूर्णांकerface,
		    &GFX_DPA_SETTING_TBL_VT3327[index]);

	/* LVDS Transmitter DPA settings: */
	set_dpa_vt1636(plvds_setting_info, plvds_chip_info, &dpa);
पूर्ण

व्योम viafb_vt1636_patch_skew_on_vt3364(
	काष्ठा lvds_setting_inक्रमmation *plvds_setting_info,
	काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	पूर्णांक index;

	DEBUG_MSG(KERN_INFO "viafb_vt1636_patch_skew_on_vt3364.\n");

	/* Graphics DPA settings: */
	index = get_clk_range_index(plvds_setting_info->vclk);
	viafb_set_dpa_gfx(plvds_chip_info->output_पूर्णांकerface,
		    &GFX_DPA_SETTING_TBL_VT3364[index]);
पूर्ण
