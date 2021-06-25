<शैली गुरु>
/*
 * Copyright 2004 ATI Technologies Inc., Markham, Ontario
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_legacy_encoders.h"
#समावेश "atom.h"

#अगर_घोषित CONFIG_PPC_PMAC
/* not sure which of these are needed */
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

/* old legacy ATI BIOS routines */

/* COMBIOS table offsets */
क्रमागत radeon_combios_table_offset अणु
	/* असलolute offset tables */
	COMBIOS_ASIC_INIT_1_TABLE,
	COMBIOS_BIOS_SUPPORT_TABLE,
	COMBIOS_DAC_PROGRAMMING_TABLE,
	COMBIOS_MAX_COLOR_DEPTH_TABLE,
	COMBIOS_CRTC_INFO_TABLE,
	COMBIOS_PLL_INFO_TABLE,
	COMBIOS_TV_INFO_TABLE,
	COMBIOS_DFP_INFO_TABLE,
	COMBIOS_HW_CONFIG_INFO_TABLE,
	COMBIOS_MULTIMEDIA_INFO_TABLE,
	COMBIOS_TV_STD_PATCH_TABLE,
	COMBIOS_LCD_INFO_TABLE,
	COMBIOS_MOBILE_INFO_TABLE,
	COMBIOS_PLL_INIT_TABLE,
	COMBIOS_MEM_CONFIG_TABLE,
	COMBIOS_SAVE_MASK_TABLE,
	COMBIOS_HARDCODED_EDID_TABLE,
	COMBIOS_ASIC_INIT_2_TABLE,
	COMBIOS_CONNECTOR_INFO_TABLE,
	COMBIOS_DYN_CLK_1_TABLE,
	COMBIOS_RESERVED_MEM_TABLE,
	COMBIOS_EXT_TMDS_INFO_TABLE,
	COMBIOS_MEM_CLK_INFO_TABLE,
	COMBIOS_EXT_DAC_INFO_TABLE,
	COMBIOS_MISC_INFO_TABLE,
	COMBIOS_CRT_INFO_TABLE,
	COMBIOS_INTEGRATED_SYSTEM_INFO_TABLE,
	COMBIOS_COMPONENT_VIDEO_INFO_TABLE,
	COMBIOS_FAN_SPEED_INFO_TABLE,
	COMBIOS_OVERDRIVE_INFO_TABLE,
	COMBIOS_OEM_INFO_TABLE,
	COMBIOS_DYN_CLK_2_TABLE,
	COMBIOS_POWER_CONNECTOR_INFO_TABLE,
	COMBIOS_I2C_INFO_TABLE,
	/* relative offset tables */
	COMBIOS_ASIC_INIT_3_TABLE,	/* offset from misc info */
	COMBIOS_ASIC_INIT_4_TABLE,	/* offset from misc info */
	COMBIOS_DETECTED_MEM_TABLE,	/* offset from misc info */
	COMBIOS_ASIC_INIT_5_TABLE,	/* offset from misc info */
	COMBIOS_RAM_RESET_TABLE,	/* offset from mem config */
	COMBIOS_POWERPLAY_INFO_TABLE,	/* offset from mobile info */
	COMBIOS_GPIO_INFO_TABLE,	/* offset from mobile info */
	COMBIOS_LCD_DDC_INFO_TABLE,	/* offset from mobile info */
	COMBIOS_TMDS_POWER_TABLE,	/* offset from mobile info */
	COMBIOS_TMDS_POWER_ON_TABLE,	/* offset from पंचांगds घातer */
	COMBIOS_TMDS_POWER_OFF_TABLE,	/* offset from पंचांगds घातer */
पूर्ण;

क्रमागत radeon_combios_ddc अणु
	DDC_NONE_DETECTED,
	DDC_MONID,
	DDC_DVI,
	DDC_VGA,
	DDC_CRT2,
	DDC_LCD,
	DDC_GPIO,
पूर्ण;

क्रमागत radeon_combios_connector अणु
	CONNECTOR_NONE_LEGACY,
	CONNECTOR_PROPRIETARY_LEGACY,
	CONNECTOR_CRT_LEGACY,
	CONNECTOR_DVI_I_LEGACY,
	CONNECTOR_DVI_D_LEGACY,
	CONNECTOR_CTV_LEGACY,
	CONNECTOR_STV_LEGACY,
	CONNECTOR_UNSUPPORTED_LEGACY
पूर्ण;

अटल स्थिर पूर्णांक legacy_connector_convert[] = अणु
	DRM_MODE_CONNECTOR_Unknown,
	DRM_MODE_CONNECTOR_DVID,
	DRM_MODE_CONNECTOR_VGA,
	DRM_MODE_CONNECTOR_DVII,
	DRM_MODE_CONNECTOR_DVID,
	DRM_MODE_CONNECTOR_Composite,
	DRM_MODE_CONNECTOR_SVIDEO,
	DRM_MODE_CONNECTOR_Unknown,
पूर्ण;

अटल uपूर्णांक16_t combios_get_table_offset(काष्ठा drm_device *dev,
					 क्रमागत radeon_combios_table_offset table)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक rev, size;
	uपूर्णांक16_t offset = 0, check_offset;

	अगर (!rdev->bios)
		वापस 0;

	चयन (table) अणु
		/* असलolute offset tables */
	हाल COMBIOS_ASIC_INIT_1_TABLE:
		check_offset = 0xc;
		अवरोध;
	हाल COMBIOS_BIOS_SUPPORT_TABLE:
		check_offset = 0x14;
		अवरोध;
	हाल COMBIOS_DAC_PROGRAMMING_TABLE:
		check_offset = 0x2a;
		अवरोध;
	हाल COMBIOS_MAX_COLOR_DEPTH_TABLE:
		check_offset = 0x2c;
		अवरोध;
	हाल COMBIOS_CRTC_INFO_TABLE:
		check_offset = 0x2e;
		अवरोध;
	हाल COMBIOS_PLL_INFO_TABLE:
		check_offset = 0x30;
		अवरोध;
	हाल COMBIOS_TV_INFO_TABLE:
		check_offset = 0x32;
		अवरोध;
	हाल COMBIOS_DFP_INFO_TABLE:
		check_offset = 0x34;
		अवरोध;
	हाल COMBIOS_HW_CONFIG_INFO_TABLE:
		check_offset = 0x36;
		अवरोध;
	हाल COMBIOS_MULTIMEDIA_INFO_TABLE:
		check_offset = 0x38;
		अवरोध;
	हाल COMBIOS_TV_STD_PATCH_TABLE:
		check_offset = 0x3e;
		अवरोध;
	हाल COMBIOS_LCD_INFO_TABLE:
		check_offset = 0x40;
		अवरोध;
	हाल COMBIOS_MOBILE_INFO_TABLE:
		check_offset = 0x42;
		अवरोध;
	हाल COMBIOS_PLL_INIT_TABLE:
		check_offset = 0x46;
		अवरोध;
	हाल COMBIOS_MEM_CONFIG_TABLE:
		check_offset = 0x48;
		अवरोध;
	हाल COMBIOS_SAVE_MASK_TABLE:
		check_offset = 0x4a;
		अवरोध;
	हाल COMBIOS_HARDCODED_EDID_TABLE:
		check_offset = 0x4c;
		अवरोध;
	हाल COMBIOS_ASIC_INIT_2_TABLE:
		check_offset = 0x4e;
		अवरोध;
	हाल COMBIOS_CONNECTOR_INFO_TABLE:
		check_offset = 0x50;
		अवरोध;
	हाल COMBIOS_DYN_CLK_1_TABLE:
		check_offset = 0x52;
		अवरोध;
	हाल COMBIOS_RESERVED_MEM_TABLE:
		check_offset = 0x54;
		अवरोध;
	हाल COMBIOS_EXT_TMDS_INFO_TABLE:
		check_offset = 0x58;
		अवरोध;
	हाल COMBIOS_MEM_CLK_INFO_TABLE:
		check_offset = 0x5a;
		अवरोध;
	हाल COMBIOS_EXT_DAC_INFO_TABLE:
		check_offset = 0x5c;
		अवरोध;
	हाल COMBIOS_MISC_INFO_TABLE:
		check_offset = 0x5e;
		अवरोध;
	हाल COMBIOS_CRT_INFO_TABLE:
		check_offset = 0x60;
		अवरोध;
	हाल COMBIOS_INTEGRATED_SYSTEM_INFO_TABLE:
		check_offset = 0x62;
		अवरोध;
	हाल COMBIOS_COMPONENT_VIDEO_INFO_TABLE:
		check_offset = 0x64;
		अवरोध;
	हाल COMBIOS_FAN_SPEED_INFO_TABLE:
		check_offset = 0x66;
		अवरोध;
	हाल COMBIOS_OVERDRIVE_INFO_TABLE:
		check_offset = 0x68;
		अवरोध;
	हाल COMBIOS_OEM_INFO_TABLE:
		check_offset = 0x6a;
		अवरोध;
	हाल COMBIOS_DYN_CLK_2_TABLE:
		check_offset = 0x6c;
		अवरोध;
	हाल COMBIOS_POWER_CONNECTOR_INFO_TABLE:
		check_offset = 0x6e;
		अवरोध;
	हाल COMBIOS_I2C_INFO_TABLE:
		check_offset = 0x70;
		अवरोध;
		/* relative offset tables */
	हाल COMBIOS_ASIC_INIT_3_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		अगर (check_offset) अणु
			rev = RBIOS8(check_offset);
			अगर (rev > 0) अणु
				check_offset = RBIOS16(check_offset + 0x3);
				अगर (check_offset)
					offset = check_offset;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल COMBIOS_ASIC_INIT_4_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		अगर (check_offset) अणु
			rev = RBIOS8(check_offset);
			अगर (rev > 0) अणु
				check_offset = RBIOS16(check_offset + 0x5);
				अगर (check_offset)
					offset = check_offset;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल COMBIOS_DETECTED_MEM_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		अगर (check_offset) अणु
			rev = RBIOS8(check_offset);
			अगर (rev > 0) अणु
				check_offset = RBIOS16(check_offset + 0x7);
				अगर (check_offset)
					offset = check_offset;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल COMBIOS_ASIC_INIT_5_TABLE:	/* offset from misc info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MISC_INFO_TABLE);
		अगर (check_offset) अणु
			rev = RBIOS8(check_offset);
			अगर (rev == 2) अणु
				check_offset = RBIOS16(check_offset + 0x9);
				अगर (check_offset)
					offset = check_offset;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल COMBIOS_RAM_RESET_TABLE:	/* offset from mem config */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MEM_CONFIG_TABLE);
		अगर (check_offset) अणु
			जबतक (RBIOS8(check_offset++));
			check_offset += 2;
			अगर (check_offset)
				offset = check_offset;
		पूर्ण
		अवरोध;
	हाल COMBIOS_POWERPLAY_INFO_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		अगर (check_offset) अणु
			check_offset = RBIOS16(check_offset + 0x11);
			अगर (check_offset)
				offset = check_offset;
		पूर्ण
		अवरोध;
	हाल COMBIOS_GPIO_INFO_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		अगर (check_offset) अणु
			check_offset = RBIOS16(check_offset + 0x13);
			अगर (check_offset)
				offset = check_offset;
		पूर्ण
		अवरोध;
	हाल COMBIOS_LCD_DDC_INFO_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		अगर (check_offset) अणु
			check_offset = RBIOS16(check_offset + 0x15);
			अगर (check_offset)
				offset = check_offset;
		पूर्ण
		अवरोध;
	हाल COMBIOS_TMDS_POWER_TABLE:	/* offset from mobile info */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_MOBILE_INFO_TABLE);
		अगर (check_offset) अणु
			check_offset = RBIOS16(check_offset + 0x17);
			अगर (check_offset)
				offset = check_offset;
		पूर्ण
		अवरोध;
	हाल COMBIOS_TMDS_POWER_ON_TABLE:	/* offset from पंचांगds घातer */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_TMDS_POWER_TABLE);
		अगर (check_offset) अणु
			check_offset = RBIOS16(check_offset + 0x2);
			अगर (check_offset)
				offset = check_offset;
		पूर्ण
		अवरोध;
	हाल COMBIOS_TMDS_POWER_OFF_TABLE:	/* offset from पंचांगds घातer */
		check_offset =
		    combios_get_table_offset(dev, COMBIOS_TMDS_POWER_TABLE);
		अगर (check_offset) अणु
			check_offset = RBIOS16(check_offset + 0x4);
			अगर (check_offset)
				offset = check_offset;
		पूर्ण
		अवरोध;
	शेष:
		check_offset = 0;
		अवरोध;
	पूर्ण

	size = RBIOS8(rdev->bios_header_start + 0x6);
	/* check असलolute offset tables */
	अगर (table < COMBIOS_ASIC_INIT_3_TABLE && check_offset && check_offset < size)
		offset = RBIOS16(rdev->bios_header_start + check_offset);

	वापस offset;
पूर्ण

bool radeon_combios_check_hardcoded_edid(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक edid_info, size;
	काष्ठा edid *edid;
	अचिन्हित अक्षर *raw;
	edid_info = combios_get_table_offset(rdev->ddev, COMBIOS_HARDCODED_EDID_TABLE);
	अगर (!edid_info)
		वापस false;

	raw = rdev->bios + edid_info;
	size = EDID_LENGTH * (raw[0x7e] + 1);
	edid = kदो_स्मृति(size, GFP_KERNEL);
	अगर (edid == शून्य)
		वापस false;

	स_नकल((अचिन्हित अक्षर *)edid, raw, size);

	अगर (!drm_edid_is_valid(edid)) अणु
		kमुक्त(edid);
		वापस false;
	पूर्ण

	rdev->mode_info.bios_hardcoded_edid = edid;
	rdev->mode_info.bios_hardcoded_edid_size = size;
	वापस true;
पूर्ण

/* this is used क्रम atom LCDs as well */
काष्ठा edid *
radeon_bios_get_hardcoded_edid(काष्ठा radeon_device *rdev)
अणु
	काष्ठा edid *edid;

	अगर (rdev->mode_info.bios_hardcoded_edid) अणु
		edid = kदो_स्मृति(rdev->mode_info.bios_hardcoded_edid_size, GFP_KERNEL);
		अगर (edid) अणु
			स_नकल((अचिन्हित अक्षर *)edid,
			       (अचिन्हित अक्षर *)rdev->mode_info.bios_hardcoded_edid,
			       rdev->mode_info.bios_hardcoded_edid_size);
			वापस edid;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा radeon_i2c_bus_rec combios_setup_i2c_bus(काष्ठा radeon_device *rdev,
						       क्रमागत radeon_combios_ddc ddc,
						       u32 clk_mask,
						       u32 data_mask)
अणु
	काष्ठा radeon_i2c_bus_rec i2c;
	पूर्णांक ddc_line = 0;

	/* ddc id            = mask reg
	 * DDC_NONE_DETECTED = none
	 * DDC_DVI           = RADEON_GPIO_DVI_DDC
	 * DDC_VGA           = RADEON_GPIO_VGA_DDC
	 * DDC_LCD           = RADEON_GPIOPAD_MASK
	 * DDC_GPIO          = RADEON_MDGPIO_MASK
	 * r1xx
	 * DDC_MONID         = RADEON_GPIO_MONID
	 * DDC_CRT2          = RADEON_GPIO_CRT2_DDC
	 * r200
	 * DDC_MONID         = RADEON_GPIO_MONID
	 * DDC_CRT2          = RADEON_GPIO_DVI_DDC
	 * r300/r350
	 * DDC_MONID         = RADEON_GPIO_DVI_DDC
	 * DDC_CRT2          = RADEON_GPIO_DVI_DDC
	 * rv2xx/rv3xx
	 * DDC_MONID         = RADEON_GPIO_MONID
	 * DDC_CRT2          = RADEON_GPIO_MONID
	 * rs3xx/rs4xx
	 * DDC_MONID         = RADEON_GPIOPAD_MASK
	 * DDC_CRT2          = RADEON_GPIO_MONID
	 */
	चयन (ddc) अणु
	हाल DDC_NONE_DETECTED:
	शेष:
		ddc_line = 0;
		अवरोध;
	हाल DDC_DVI:
		ddc_line = RADEON_GPIO_DVI_DDC;
		अवरोध;
	हाल DDC_VGA:
		ddc_line = RADEON_GPIO_VGA_DDC;
		अवरोध;
	हाल DDC_LCD:
		ddc_line = RADEON_GPIOPAD_MASK;
		अवरोध;
	हाल DDC_GPIO:
		ddc_line = RADEON_MDGPIO_MASK;
		अवरोध;
	हाल DDC_MONID:
		अगर (rdev->family == CHIP_RS300 ||
		    rdev->family == CHIP_RS400 ||
		    rdev->family == CHIP_RS480)
			ddc_line = RADEON_GPIOPAD_MASK;
		अन्यथा अगर (rdev->family == CHIP_R300 ||
			 rdev->family == CHIP_R350) अणु
			ddc_line = RADEON_GPIO_DVI_DDC;
			ddc = DDC_DVI;
		पूर्ण अन्यथा
			ddc_line = RADEON_GPIO_MONID;
		अवरोध;
	हाल DDC_CRT2:
		अगर (rdev->family == CHIP_R200 ||
		    rdev->family == CHIP_R300 ||
		    rdev->family == CHIP_R350) अणु
			ddc_line = RADEON_GPIO_DVI_DDC;
			ddc = DDC_DVI;
		पूर्ण अन्यथा अगर (rdev->family == CHIP_RS300 ||
			   rdev->family == CHIP_RS400 ||
			   rdev->family == CHIP_RS480)
			ddc_line = RADEON_GPIO_MONID;
		अन्यथा अगर (rdev->family >= CHIP_RV350) अणु
			ddc_line = RADEON_GPIO_MONID;
			ddc = DDC_MONID;
		पूर्ण अन्यथा
			ddc_line = RADEON_GPIO_CRT2_DDC;
		अवरोध;
	पूर्ण

	अगर (ddc_line == RADEON_GPIOPAD_MASK) अणु
		i2c.mask_clk_reg = RADEON_GPIOPAD_MASK;
		i2c.mask_data_reg = RADEON_GPIOPAD_MASK;
		i2c.a_clk_reg = RADEON_GPIOPAD_A;
		i2c.a_data_reg = RADEON_GPIOPAD_A;
		i2c.en_clk_reg = RADEON_GPIOPAD_EN;
		i2c.en_data_reg = RADEON_GPIOPAD_EN;
		i2c.y_clk_reg = RADEON_GPIOPAD_Y;
		i2c.y_data_reg = RADEON_GPIOPAD_Y;
	पूर्ण अन्यथा अगर (ddc_line == RADEON_MDGPIO_MASK) अणु
		i2c.mask_clk_reg = RADEON_MDGPIO_MASK;
		i2c.mask_data_reg = RADEON_MDGPIO_MASK;
		i2c.a_clk_reg = RADEON_MDGPIO_A;
		i2c.a_data_reg = RADEON_MDGPIO_A;
		i2c.en_clk_reg = RADEON_MDGPIO_EN;
		i2c.en_data_reg = RADEON_MDGPIO_EN;
		i2c.y_clk_reg = RADEON_MDGPIO_Y;
		i2c.y_data_reg = RADEON_MDGPIO_Y;
	पूर्ण अन्यथा अणु
		i2c.mask_clk_reg = ddc_line;
		i2c.mask_data_reg = ddc_line;
		i2c.a_clk_reg = ddc_line;
		i2c.a_data_reg = ddc_line;
		i2c.en_clk_reg = ddc_line;
		i2c.en_data_reg = ddc_line;
		i2c.y_clk_reg = ddc_line;
		i2c.y_data_reg = ddc_line;
	पूर्ण

	अगर (clk_mask && data_mask) अणु
		/* प्रणाली specअगरic masks */
		i2c.mask_clk_mask = clk_mask;
		i2c.mask_data_mask = data_mask;
		i2c.a_clk_mask = clk_mask;
		i2c.a_data_mask = data_mask;
		i2c.en_clk_mask = clk_mask;
		i2c.en_data_mask = data_mask;
		i2c.y_clk_mask = clk_mask;
		i2c.y_data_mask = data_mask;
	पूर्ण अन्यथा अगर ((ddc_line == RADEON_GPIOPAD_MASK) ||
		   (ddc_line == RADEON_MDGPIO_MASK)) अणु
		/* शेष gpiopad masks */
		i2c.mask_clk_mask = (0x20 << 8);
		i2c.mask_data_mask = 0x80;
		i2c.a_clk_mask = (0x20 << 8);
		i2c.a_data_mask = 0x80;
		i2c.en_clk_mask = (0x20 << 8);
		i2c.en_data_mask = 0x80;
		i2c.y_clk_mask = (0x20 << 8);
		i2c.y_data_mask = 0x80;
	पूर्ण अन्यथा अणु
		/* शेष masks क्रम ddc pads */
		i2c.mask_clk_mask = RADEON_GPIO_MASK_1;
		i2c.mask_data_mask = RADEON_GPIO_MASK_0;
		i2c.a_clk_mask = RADEON_GPIO_A_1;
		i2c.a_data_mask = RADEON_GPIO_A_0;
		i2c.en_clk_mask = RADEON_GPIO_EN_1;
		i2c.en_data_mask = RADEON_GPIO_EN_0;
		i2c.y_clk_mask = RADEON_GPIO_Y_1;
		i2c.y_data_mask = RADEON_GPIO_Y_0;
	पूर्ण

	चयन (rdev->family) अणु
	हाल CHIP_R100:
	हाल CHIP_RV100:
	हाल CHIP_RS100:
	हाल CHIP_RV200:
	हाल CHIP_RS200:
	हाल CHIP_RS300:
		चयन (ddc_line) अणु
		हाल RADEON_GPIO_DVI_DDC:
			i2c.hw_capable = true;
			अवरोध;
		शेष:
			i2c.hw_capable = false;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CHIP_R200:
		चयन (ddc_line) अणु
		हाल RADEON_GPIO_DVI_DDC:
		हाल RADEON_GPIO_MONID:
			i2c.hw_capable = true;
			अवरोध;
		शेष:
			i2c.hw_capable = false;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CHIP_RV250:
	हाल CHIP_RV280:
		चयन (ddc_line) अणु
		हाल RADEON_GPIO_VGA_DDC:
		हाल RADEON_GPIO_DVI_DDC:
		हाल RADEON_GPIO_CRT2_DDC:
			i2c.hw_capable = true;
			अवरोध;
		शेष:
			i2c.hw_capable = false;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CHIP_R300:
	हाल CHIP_R350:
		चयन (ddc_line) अणु
		हाल RADEON_GPIO_VGA_DDC:
		हाल RADEON_GPIO_DVI_DDC:
			i2c.hw_capable = true;
			अवरोध;
		शेष:
			i2c.hw_capable = false;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CHIP_RV350:
	हाल CHIP_RV380:
	हाल CHIP_RS400:
	हाल CHIP_RS480:
		चयन (ddc_line) अणु
		हाल RADEON_GPIO_VGA_DDC:
		हाल RADEON_GPIO_DVI_DDC:
			i2c.hw_capable = true;
			अवरोध;
		हाल RADEON_GPIO_MONID:
			/* hw i2c on RADEON_GPIO_MONID करोesn't seem to work
			 * reliably on some pre-r4xx hardware; not sure why.
			 */
			i2c.hw_capable = false;
			अवरोध;
		शेष:
			i2c.hw_capable = false;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		i2c.hw_capable = false;
		अवरोध;
	पूर्ण
	i2c.mm_i2c = false;

	i2c.i2c_id = ddc;
	i2c.hpd = RADEON_HPD_NONE;

	अगर (ddc_line)
		i2c.valid = true;
	अन्यथा
		i2c.valid = false;

	वापस i2c;
पूर्ण

अटल काष्ठा radeon_i2c_bus_rec radeon_combios_get_i2c_info_from_table(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा radeon_i2c_bus_rec i2c;
	u16 offset;
	u8 id, blocks, clk, data;
	पूर्णांक i;

	i2c.valid = false;

	offset = combios_get_table_offset(dev, COMBIOS_I2C_INFO_TABLE);
	अगर (offset) अणु
		blocks = RBIOS8(offset + 2);
		क्रम (i = 0; i < blocks; i++) अणु
			id = RBIOS8(offset + 3 + (i * 5) + 0);
			अगर (id == 136) अणु
				clk = RBIOS8(offset + 3 + (i * 5) + 3);
				data = RBIOS8(offset + 3 + (i * 5) + 4);
				/* gpiopad */
				i2c = combios_setup_i2c_bus(rdev, DDC_MONID,
							    (1 << clk), (1 << data));
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस i2c;
पूर्ण

व्योम radeon_combios_i2c_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा radeon_i2c_bus_rec i2c;

	/* actual hw pads
	 * r1xx/rs2xx/rs3xx
	 * 0x60, 0x64, 0x68, 0x6c, gpiopads, mm
	 * r200
	 * 0x60, 0x64, 0x68, mm
	 * r300/r350
	 * 0x60, 0x64, mm
	 * rv2xx/rv3xx/rs4xx
	 * 0x60, 0x64, 0x68, gpiopads, mm
	 */

	/* 0x60 */
	i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
	rdev->i2c_bus[0] = radeon_i2c_create(dev, &i2c, "DVI_DDC");
	/* 0x64 */
	i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
	rdev->i2c_bus[1] = radeon_i2c_create(dev, &i2c, "VGA_DDC");

	/* mm i2c */
	i2c.valid = true;
	i2c.hw_capable = true;
	i2c.mm_i2c = true;
	i2c.i2c_id = 0xa0;
	rdev->i2c_bus[2] = radeon_i2c_create(dev, &i2c, "MM_I2C");

	अगर (rdev->family == CHIP_R300 ||
	    rdev->family == CHIP_R350) अणु
		/* only 2 sw i2c pads */
	पूर्ण अन्यथा अगर (rdev->family == CHIP_RS300 ||
		   rdev->family == CHIP_RS400 ||
		   rdev->family == CHIP_RS480) अणु
		/* 0x68 */
		i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		rdev->i2c_bus[3] = radeon_i2c_create(dev, &i2c, "MONID");

		/* gpiopad */
		i2c = radeon_combios_get_i2c_info_from_table(rdev);
		अगर (i2c.valid)
			rdev->i2c_bus[4] = radeon_i2c_create(dev, &i2c, "GPIOPAD_MASK");
	पूर्ण अन्यथा अगर ((rdev->family == CHIP_R200) ||
		   (rdev->family >= CHIP_R300)) अणु
		/* 0x68 */
		i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		rdev->i2c_bus[3] = radeon_i2c_create(dev, &i2c, "MONID");
	पूर्ण अन्यथा अणु
		/* 0x68 */
		i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		rdev->i2c_bus[3] = radeon_i2c_create(dev, &i2c, "MONID");
		/* 0x6c */
		i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		rdev->i2c_bus[4] = radeon_i2c_create(dev, &i2c, "CRT2_DDC");
	पूर्ण
पूर्ण

bool radeon_combios_get_घड़ी_info(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक16_t pll_info;
	काष्ठा radeon_pll *p1pll = &rdev->घड़ी.p1pll;
	काष्ठा radeon_pll *p2pll = &rdev->घड़ी.p2pll;
	काष्ठा radeon_pll *spll = &rdev->घड़ी.spll;
	काष्ठा radeon_pll *mpll = &rdev->घड़ी.mpll;
	पूर्णांक8_t rev;
	uपूर्णांक16_t sclk, mclk;

	pll_info = combios_get_table_offset(dev, COMBIOS_PLL_INFO_TABLE);
	अगर (pll_info) अणु
		rev = RBIOS8(pll_info);

		/* pixel घड़ीs */
		p1pll->reference_freq = RBIOS16(pll_info + 0xe);
		p1pll->reference_भाग = RBIOS16(pll_info + 0x10);
		p1pll->pll_out_min = RBIOS32(pll_info + 0x12);
		p1pll->pll_out_max = RBIOS32(pll_info + 0x16);
		p1pll->lcd_pll_out_min = p1pll->pll_out_min;
		p1pll->lcd_pll_out_max = p1pll->pll_out_max;

		अगर (rev > 9) अणु
			p1pll->pll_in_min = RBIOS32(pll_info + 0x36);
			p1pll->pll_in_max = RBIOS32(pll_info + 0x3a);
		पूर्ण अन्यथा अणु
			p1pll->pll_in_min = 40;
			p1pll->pll_in_max = 500;
		पूर्ण
		*p2pll = *p1pll;

		/* प्रणाली घड़ी */
		spll->reference_freq = RBIOS16(pll_info + 0x1a);
		spll->reference_भाग = RBIOS16(pll_info + 0x1c);
		spll->pll_out_min = RBIOS32(pll_info + 0x1e);
		spll->pll_out_max = RBIOS32(pll_info + 0x22);

		अगर (rev > 10) अणु
			spll->pll_in_min = RBIOS32(pll_info + 0x48);
			spll->pll_in_max = RBIOS32(pll_info + 0x4c);
		पूर्ण अन्यथा अणु
			/* ??? */
			spll->pll_in_min = 40;
			spll->pll_in_max = 500;
		पूर्ण

		/* memory घड़ी */
		mpll->reference_freq = RBIOS16(pll_info + 0x26);
		mpll->reference_भाग = RBIOS16(pll_info + 0x28);
		mpll->pll_out_min = RBIOS32(pll_info + 0x2a);
		mpll->pll_out_max = RBIOS32(pll_info + 0x2e);

		अगर (rev > 10) अणु
			mpll->pll_in_min = RBIOS32(pll_info + 0x5a);
			mpll->pll_in_max = RBIOS32(pll_info + 0x5e);
		पूर्ण अन्यथा अणु
			/* ??? */
			mpll->pll_in_min = 40;
			mpll->pll_in_max = 500;
		पूर्ण

		/* शेष sclk/mclk */
		sclk = RBIOS16(pll_info + 0xa);
		mclk = RBIOS16(pll_info + 0x8);
		अगर (sclk == 0)
			sclk = 200 * 100;
		अगर (mclk == 0)
			mclk = 200 * 100;

		rdev->घड़ी.शेष_sclk = sclk;
		rdev->घड़ी.शेष_mclk = mclk;

		अगर (RBIOS32(pll_info + 0x16))
			rdev->घड़ी.max_pixel_घड़ी = RBIOS32(pll_info + 0x16);
		अन्यथा
			rdev->घड़ी.max_pixel_घड़ी = 35000; /* might need something asic specअगरic */

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool radeon_combios_sideport_present(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	u16 igp_info;

	/* sideport is AMD only */
	अगर (rdev->family == CHIP_RS400)
		वापस false;

	igp_info = combios_get_table_offset(dev, COMBIOS_INTEGRATED_SYSTEM_INFO_TABLE);

	अगर (igp_info) अणु
		अगर (RBIOS16(igp_info + 0x4))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर uपूर्णांक32_t शेष_primarydac_adj[CHIP_LAST] = अणु
	0x00000808,		/* r100  */
	0x00000808,		/* rv100 */
	0x00000808,		/* rs100 */
	0x00000808,		/* rv200 */
	0x00000808,		/* rs200 */
	0x00000808,		/* r200  */
	0x00000808,		/* rv250 */
	0x00000000,		/* rs300 */
	0x00000808,		/* rv280 */
	0x00000808,		/* r300  */
	0x00000808,		/* r350  */
	0x00000808,		/* rv350 */
	0x00000808,		/* rv380 */
	0x00000808,		/* r420  */
	0x00000808,		/* r423  */
	0x00000808,		/* rv410 */
	0x00000000,		/* rs400 */
	0x00000000,		/* rs480 */
पूर्ण;

अटल व्योम radeon_legacy_get_primary_dac_info_from_table(काष्ठा radeon_device *rdev,
							  काष्ठा radeon_encoder_primary_dac *p_dac)
अणु
	p_dac->ps2_pdac_adj = शेष_primarydac_adj[rdev->family];
	वापस;
पूर्ण

काष्ठा radeon_encoder_primary_dac *radeon_combios_get_primary_dac_info(काष्ठा
								       radeon_encoder
								       *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक16_t dac_info;
	uपूर्णांक8_t rev, bg, dac;
	काष्ठा radeon_encoder_primary_dac *p_dac = शून्य;
	पूर्णांक found = 0;

	p_dac = kzalloc(माप(काष्ठा radeon_encoder_primary_dac),
			GFP_KERNEL);

	अगर (!p_dac)
		वापस शून्य;

	/* check CRT table */
	dac_info = combios_get_table_offset(dev, COMBIOS_CRT_INFO_TABLE);
	अगर (dac_info) अणु
		rev = RBIOS8(dac_info) & 0x3;
		अगर (rev < 2) अणु
			bg = RBIOS8(dac_info + 0x2) & 0xf;
			dac = (RBIOS8(dac_info + 0x2) >> 4) & 0xf;
			p_dac->ps2_pdac_adj = (bg << 8) | (dac);
		पूर्ण अन्यथा अणु
			bg = RBIOS8(dac_info + 0x2) & 0xf;
			dac = RBIOS8(dac_info + 0x3) & 0xf;
			p_dac->ps2_pdac_adj = (bg << 8) | (dac);
		पूर्ण
		/* अगर the values are zeros, use the table */
		अगर ((dac == 0) || (bg == 0))
			found = 0;
		अन्यथा
			found = 1;
	पूर्ण

	/* quirks */
	/* Radeon 7000 (RV100) */
	अगर (((rdev->pdev->device == 0x5159) &&
	    (rdev->pdev->subप्रणाली_venकरोr == 0x174B) &&
	    (rdev->pdev->subप्रणाली_device == 0x7c28)) ||
	/* Radeon 9100 (R200) */
	   ((rdev->pdev->device == 0x514D) &&
	    (rdev->pdev->subप्रणाली_venकरोr == 0x174B) &&
	    (rdev->pdev->subप्रणाली_device == 0x7149))) अणु
		/* vbios value is bad, use the शेष */
		found = 0;
	पूर्ण

	अगर (!found) /* fallback to शेषs */
		radeon_legacy_get_primary_dac_info_from_table(rdev, p_dac);

	वापस p_dac;
पूर्ण

क्रमागत radeon_tv_std
radeon_combios_get_tv_info(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	uपूर्णांक16_t tv_info;
	क्रमागत radeon_tv_std tv_std = TV_STD_NTSC;

	tv_info = combios_get_table_offset(dev, COMBIOS_TV_INFO_TABLE);
	अगर (tv_info) अणु
		अगर (RBIOS8(tv_info + 6) == 'T') अणु
			चयन (RBIOS8(tv_info + 7) & 0xf) अणु
			हाल 1:
				tv_std = TV_STD_NTSC;
				DRM_DEBUG_KMS("Default TV standard: NTSC\n");
				अवरोध;
			हाल 2:
				tv_std = TV_STD_PAL;
				DRM_DEBUG_KMS("Default TV standard: PAL\n");
				अवरोध;
			हाल 3:
				tv_std = TV_STD_PAL_M;
				DRM_DEBUG_KMS("Default TV standard: PAL-M\n");
				अवरोध;
			हाल 4:
				tv_std = TV_STD_PAL_60;
				DRM_DEBUG_KMS("Default TV standard: PAL-60\n");
				अवरोध;
			हाल 5:
				tv_std = TV_STD_NTSC_J;
				DRM_DEBUG_KMS("Default TV standard: NTSC-J\n");
				अवरोध;
			हाल 6:
				tv_std = TV_STD_SCART_PAL;
				DRM_DEBUG_KMS("Default TV standard: SCART-PAL\n");
				अवरोध;
			शेष:
				tv_std = TV_STD_NTSC;
				DRM_DEBUG_KMS
				    ("Unknown TV standard; defaulting to NTSC\n");
				अवरोध;
			पूर्ण

			चयन ((RBIOS8(tv_info + 9) >> 2) & 0x3) अणु
			हाल 0:
				DRM_DEBUG_KMS("29.498928713 MHz TV ref clk\n");
				अवरोध;
			हाल 1:
				DRM_DEBUG_KMS("28.636360000 MHz TV ref clk\n");
				अवरोध;
			हाल 2:
				DRM_DEBUG_KMS("14.318180000 MHz TV ref clk\n");
				अवरोध;
			हाल 3:
				DRM_DEBUG_KMS("27.000000000 MHz TV ref clk\n");
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस tv_std;
पूर्ण

अटल स्थिर uपूर्णांक32_t शेष_tvdac_adj[CHIP_LAST] = अणु
	0x00000000,		/* r100  */
	0x00280000,		/* rv100 */
	0x00000000,		/* rs100 */
	0x00880000,		/* rv200 */
	0x00000000,		/* rs200 */
	0x00000000,		/* r200  */
	0x00770000,		/* rv250 */
	0x00290000,		/* rs300 */
	0x00560000,		/* rv280 */
	0x00780000,		/* r300  */
	0x00770000,		/* r350  */
	0x00780000,		/* rv350 */
	0x00780000,		/* rv380 */
	0x01080000,		/* r420  */
	0x01080000,		/* r423  */
	0x01080000,		/* rv410 */
	0x00780000,		/* rs400 */
	0x00780000,		/* rs480 */
पूर्ण;

अटल व्योम radeon_legacy_get_tv_dac_info_from_table(काष्ठा radeon_device *rdev,
						     काष्ठा radeon_encoder_tv_dac *tv_dac)
अणु
	tv_dac->ps2_tvdac_adj = शेष_tvdac_adj[rdev->family];
	अगर ((rdev->flags & RADEON_IS_MOBILITY) && (rdev->family == CHIP_RV250))
		tv_dac->ps2_tvdac_adj = 0x00880000;
	tv_dac->pal_tvdac_adj = tv_dac->ps2_tvdac_adj;
	tv_dac->ntsc_tvdac_adj = tv_dac->ps2_tvdac_adj;
	वापस;
पूर्ण

काष्ठा radeon_encoder_tv_dac *radeon_combios_get_tv_dac_info(काष्ठा
							     radeon_encoder
							     *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक16_t dac_info;
	uपूर्णांक8_t rev, bg, dac;
	काष्ठा radeon_encoder_tv_dac *tv_dac = शून्य;
	पूर्णांक found = 0;

	tv_dac = kzalloc(माप(काष्ठा radeon_encoder_tv_dac), GFP_KERNEL);
	अगर (!tv_dac)
		वापस शून्य;

	/* first check TV table */
	dac_info = combios_get_table_offset(dev, COMBIOS_TV_INFO_TABLE);
	अगर (dac_info) अणु
		rev = RBIOS8(dac_info + 0x3);
		अगर (rev > 4) अणु
			bg = RBIOS8(dac_info + 0xc) & 0xf;
			dac = RBIOS8(dac_info + 0xd) & 0xf;
			tv_dac->ps2_tvdac_adj = (bg << 16) | (dac << 20);

			bg = RBIOS8(dac_info + 0xe) & 0xf;
			dac = RBIOS8(dac_info + 0xf) & 0xf;
			tv_dac->pal_tvdac_adj = (bg << 16) | (dac << 20);

			bg = RBIOS8(dac_info + 0x10) & 0xf;
			dac = RBIOS8(dac_info + 0x11) & 0xf;
			tv_dac->ntsc_tvdac_adj = (bg << 16) | (dac << 20);
			/* अगर the values are all zeros, use the table */
			अगर (tv_dac->ps2_tvdac_adj)
				found = 1;
		पूर्ण अन्यथा अगर (rev > 1) अणु
			bg = RBIOS8(dac_info + 0xc) & 0xf;
			dac = (RBIOS8(dac_info + 0xc) >> 4) & 0xf;
			tv_dac->ps2_tvdac_adj = (bg << 16) | (dac << 20);

			bg = RBIOS8(dac_info + 0xd) & 0xf;
			dac = (RBIOS8(dac_info + 0xd) >> 4) & 0xf;
			tv_dac->pal_tvdac_adj = (bg << 16) | (dac << 20);

			bg = RBIOS8(dac_info + 0xe) & 0xf;
			dac = (RBIOS8(dac_info + 0xe) >> 4) & 0xf;
			tv_dac->ntsc_tvdac_adj = (bg << 16) | (dac << 20);
			/* अगर the values are all zeros, use the table */
			अगर (tv_dac->ps2_tvdac_adj)
				found = 1;
		पूर्ण
		tv_dac->tv_std = radeon_combios_get_tv_info(rdev);
	पूर्ण
	अगर (!found) अणु
		/* then check CRT table */
		dac_info =
		    combios_get_table_offset(dev, COMBIOS_CRT_INFO_TABLE);
		अगर (dac_info) अणु
			rev = RBIOS8(dac_info) & 0x3;
			अगर (rev < 2) अणु
				bg = RBIOS8(dac_info + 0x3) & 0xf;
				dac = (RBIOS8(dac_info + 0x3) >> 4) & 0xf;
				tv_dac->ps2_tvdac_adj =
				    (bg << 16) | (dac << 20);
				tv_dac->pal_tvdac_adj = tv_dac->ps2_tvdac_adj;
				tv_dac->ntsc_tvdac_adj = tv_dac->ps2_tvdac_adj;
				/* अगर the values are all zeros, use the table */
				अगर (tv_dac->ps2_tvdac_adj)
					found = 1;
			पूर्ण अन्यथा अणु
				bg = RBIOS8(dac_info + 0x4) & 0xf;
				dac = RBIOS8(dac_info + 0x5) & 0xf;
				tv_dac->ps2_tvdac_adj =
				    (bg << 16) | (dac << 20);
				tv_dac->pal_tvdac_adj = tv_dac->ps2_tvdac_adj;
				tv_dac->ntsc_tvdac_adj = tv_dac->ps2_tvdac_adj;
				/* अगर the values are all zeros, use the table */
				अगर (tv_dac->ps2_tvdac_adj)
					found = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			DRM_INFO("No TV DAC info found in BIOS\n");
		पूर्ण
	पूर्ण

	अगर (!found) /* fallback to शेषs */
		radeon_legacy_get_tv_dac_info_from_table(rdev, tv_dac);

	वापस tv_dac;
पूर्ण

अटल काष्ठा radeon_encoder_lvds *radeon_legacy_get_lvds_info_from_regs(काष्ठा
									 radeon_device
									 *rdev)
अणु
	काष्ठा radeon_encoder_lvds *lvds = शून्य;
	uपूर्णांक32_t fp_vert_stretch, fp_horz_stretch;
	uपूर्णांक32_t ppll_भाग_sel, ppll_val;
	uपूर्णांक32_t lvds_ss_gen_cntl = RREG32(RADEON_LVDS_SS_GEN_CNTL);

	lvds = kzalloc(माप(काष्ठा radeon_encoder_lvds), GFP_KERNEL);

	अगर (!lvds)
		वापस शून्य;

	fp_vert_stretch = RREG32(RADEON_FP_VERT_STRETCH);
	fp_horz_stretch = RREG32(RADEON_FP_HORZ_STRETCH);

	/* These should be fail-safe शेषs, fingers crossed */
	lvds->panel_pwr_delay = 200;
	lvds->panel_vcc_delay = 2000;

	lvds->lvds_gen_cntl = RREG32(RADEON_LVDS_GEN_CNTL);
	lvds->panel_digon_delay = (lvds_ss_gen_cntl >> RADEON_LVDS_PWRSEQ_DELAY1_SHIFT) & 0xf;
	lvds->panel_blon_delay = (lvds_ss_gen_cntl >> RADEON_LVDS_PWRSEQ_DELAY2_SHIFT) & 0xf;

	अगर (fp_vert_stretch & RADEON_VERT_STRETCH_ENABLE)
		lvds->native_mode.vdisplay =
		    ((fp_vert_stretch & RADEON_VERT_PANEL_SIZE) >>
		     RADEON_VERT_PANEL_SHIFT) + 1;
	अन्यथा
		lvds->native_mode.vdisplay =
		    (RREG32(RADEON_CRTC_V_TOTAL_DISP) >> 16) + 1;

	अगर (fp_horz_stretch & RADEON_HORZ_STRETCH_ENABLE)
		lvds->native_mode.hdisplay =
		    (((fp_horz_stretch & RADEON_HORZ_PANEL_SIZE) >>
		      RADEON_HORZ_PANEL_SHIFT) + 1) * 8;
	अन्यथा
		lvds->native_mode.hdisplay =
		    ((RREG32(RADEON_CRTC_H_TOTAL_DISP) >> 16) + 1) * 8;

	अगर ((lvds->native_mode.hdisplay < 640) ||
	    (lvds->native_mode.vdisplay < 480)) अणु
		lvds->native_mode.hdisplay = 640;
		lvds->native_mode.vdisplay = 480;
	पूर्ण

	ppll_भाग_sel = RREG8(RADEON_CLOCK_CNTL_INDEX + 1) & 0x3;
	ppll_val = RREG32_PLL(RADEON_PPLL_DIV_0 + ppll_भाग_sel);
	अगर ((ppll_val & 0x000707ff) == 0x1bb)
		lvds->use_bios_भागiders = false;
	अन्यथा अणु
		lvds->panel_ref_भागider =
		    RREG32_PLL(RADEON_PPLL_REF_DIV) & 0x3ff;
		lvds->panel_post_भागider = (ppll_val >> 16) & 0x7;
		lvds->panel_fb_भागider = ppll_val & 0x7ff;

		अगर ((lvds->panel_ref_भागider != 0) &&
		    (lvds->panel_fb_भागider > 3))
			lvds->use_bios_भागiders = true;
	पूर्ण
	lvds->panel_vcc_delay = 200;

	DRM_INFO("Panel info derived from registers\n");
	DRM_INFO("Panel Size %dx%d\n", lvds->native_mode.hdisplay,
		 lvds->native_mode.vdisplay);

	वापस lvds;
पूर्ण

काष्ठा radeon_encoder_lvds *radeon_combios_get_lvds_info(काष्ठा radeon_encoder
							 *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक16_t lcd_info;
	uपूर्णांक32_t panel_setup;
	अक्षर sपंचांगp[30];
	पूर्णांक पंचांगp, i;
	काष्ठा radeon_encoder_lvds *lvds = शून्य;

	lcd_info = combios_get_table_offset(dev, COMBIOS_LCD_INFO_TABLE);

	अगर (lcd_info) अणु
		lvds = kzalloc(माप(काष्ठा radeon_encoder_lvds), GFP_KERNEL);

		अगर (!lvds)
			वापस शून्य;

		क्रम (i = 0; i < 24; i++)
			sपंचांगp[i] = RBIOS8(lcd_info + i + 1);
		sपंचांगp[24] = 0;

		DRM_INFO("Panel ID String: %s\n", sपंचांगp);

		lvds->native_mode.hdisplay = RBIOS16(lcd_info + 0x19);
		lvds->native_mode.vdisplay = RBIOS16(lcd_info + 0x1b);

		DRM_INFO("Panel Size %dx%d\n", lvds->native_mode.hdisplay,
			 lvds->native_mode.vdisplay);

		lvds->panel_vcc_delay = RBIOS16(lcd_info + 0x2c);
		lvds->panel_vcc_delay = min_t(u16, lvds->panel_vcc_delay, 2000);

		lvds->panel_pwr_delay = RBIOS8(lcd_info + 0x24);
		lvds->panel_digon_delay = RBIOS16(lcd_info + 0x38) & 0xf;
		lvds->panel_blon_delay = (RBIOS16(lcd_info + 0x38) >> 4) & 0xf;

		lvds->panel_ref_भागider = RBIOS16(lcd_info + 0x2e);
		lvds->panel_post_भागider = RBIOS8(lcd_info + 0x30);
		lvds->panel_fb_भागider = RBIOS16(lcd_info + 0x31);
		अगर ((lvds->panel_ref_भागider != 0) &&
		    (lvds->panel_fb_भागider > 3))
			lvds->use_bios_भागiders = true;

		panel_setup = RBIOS32(lcd_info + 0x39);
		lvds->lvds_gen_cntl = 0xff00;
		अगर (panel_setup & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_PANEL_FORMAT;

		अगर ((panel_setup >> 4) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_PANEL_TYPE;

		चयन ((panel_setup >> 8) & 0x7) अणु
		हाल 0:
			lvds->lvds_gen_cntl |= RADEON_LVDS_NO_FM;
			अवरोध;
		हाल 1:
			lvds->lvds_gen_cntl |= RADEON_LVDS_2_GREY;
			अवरोध;
		हाल 2:
			lvds->lvds_gen_cntl |= RADEON_LVDS_4_GREY;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर ((panel_setup >> 16) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_FP_POL_LOW;

		अगर ((panel_setup >> 17) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_LP_POL_LOW;

		अगर ((panel_setup >> 18) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_DTM_POL_LOW;

		अगर ((panel_setup >> 23) & 0x1)
			lvds->lvds_gen_cntl |= RADEON_LVDS_BL_CLK_SEL;

		lvds->lvds_gen_cntl |= (panel_setup & 0xf0000000);

		क्रम (i = 0; i < 32; i++) अणु
			पंचांगp = RBIOS16(lcd_info + 64 + i * 2);
			अगर (पंचांगp == 0)
				अवरोध;

			अगर ((RBIOS16(पंचांगp) == lvds->native_mode.hdisplay) &&
			    (RBIOS16(पंचांगp + 2) == lvds->native_mode.vdisplay)) अणु
				u32 hss = (RBIOS16(पंचांगp + 21) - RBIOS16(पंचांगp + 19) - 1) * 8;

				अगर (hss > lvds->native_mode.hdisplay)
					hss = (10 - 1) * 8;

				lvds->native_mode.htotal = lvds->native_mode.hdisplay +
					(RBIOS16(पंचांगp + 17) - RBIOS16(पंचांगp + 19)) * 8;
				lvds->native_mode.hsync_start = lvds->native_mode.hdisplay +
					hss;
				lvds->native_mode.hsync_end = lvds->native_mode.hsync_start +
					(RBIOS8(पंचांगp + 23) * 8);

				lvds->native_mode.vtotal = lvds->native_mode.vdisplay +
					(RBIOS16(पंचांगp + 24) - RBIOS16(पंचांगp + 26));
				lvds->native_mode.vsync_start = lvds->native_mode.vdisplay +
					((RBIOS16(पंचांगp + 28) & 0x7ff) - RBIOS16(पंचांगp + 26));
				lvds->native_mode.vsync_end = lvds->native_mode.vsync_start +
					((RBIOS16(पंचांगp + 28) & 0xf800) >> 11);

				lvds->native_mode.घड़ी = RBIOS16(पंचांगp + 9) * 10;
				lvds->native_mode.flags = 0;
				/* set crtc values */
				drm_mode_set_crtcinfo(&lvds->native_mode, CRTC_INTERLACE_HALVE_V);

			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_INFO("No panel info found in BIOS\n");
		lvds = radeon_legacy_get_lvds_info_from_regs(rdev);
	पूर्ण

	अगर (lvds)
		encoder->native_mode = lvds->native_mode;
	वापस lvds;
पूर्ण

अटल स्थिर काष्ठा radeon_पंचांगds_pll शेष_पंचांगds_pll[CHIP_LAST][4] = अणु
	अणुअणु12000, 0xa1bपूर्ण, अणु0xffffffff, 0xa3fपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_R100  */
	अणुअणु12000, 0xa1bपूर्ण, अणु0xffffffff, 0xa3fपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RV100 */
	अणुअणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RS100 */
	अणुअणु15000, 0xa1bपूर्ण, अणु0xffffffff, 0xa3fपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RV200 */
	अणुअणु12000, 0xa1bपूर्ण, अणु0xffffffff, 0xa3fपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RS200 */
	अणुअणु15000, 0xa1bपूर्ण, अणु0xffffffff, 0xa3fपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_R200  */
	अणुअणु15500, 0x81bपूर्ण, अणु0xffffffff, 0x83fपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RV250 */
	अणुअणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RS300 */
	अणुअणु13000, 0x400f4पूर्ण, अणु15000, 0x400f7पूर्ण, अणु0xffffffff, 0x40111पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RV280 */
	अणुअणु0xffffffff, 0xb01cbपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_R300  */
	अणुअणु0xffffffff, 0xb01cbपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_R350  */
	अणुअणु15000, 0xb0155पूर्ण, अणु0xffffffff, 0xb01cbपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RV350 */
	अणुअणु15000, 0xb0155पूर्ण, अणु0xffffffff, 0xb01cbपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RV380 */
	अणुअणु0xffffffff, 0xb01cbपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_R420  */
	अणुअणु0xffffffff, 0xb01cbपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_R423  */
	अणुअणु0xffffffff, 0xb01cbपूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्णपूर्ण,	/* CHIP_RV410 */
	अणु अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण पूर्ण,	/* CHIP_RS400 */
	अणु अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण, अणु0, 0पूर्ण पूर्ण,	/* CHIP_RS480 */
पूर्ण;

bool radeon_legacy_get_पंचांगds_info_from_table(काष्ठा radeon_encoder *encoder,
					    काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		पंचांगds->पंचांगds_pll[i].value =
			शेष_पंचांगds_pll[rdev->family][i].value;
		पंचांगds->पंचांगds_pll[i].freq = शेष_पंचांगds_pll[rdev->family][i].freq;
	पूर्ण

	वापस true;
पूर्ण

bool radeon_legacy_get_पंचांगds_info_from_combios(काष्ठा radeon_encoder *encoder,
					      काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक16_t पंचांगds_info;
	पूर्णांक i, n;
	uपूर्णांक8_t ver;

	पंचांगds_info = combios_get_table_offset(dev, COMBIOS_DFP_INFO_TABLE);

	अगर (पंचांगds_info) अणु
		ver = RBIOS8(पंचांगds_info);
		DRM_DEBUG_KMS("DFP table revision: %d\n", ver);
		अगर (ver == 3) अणु
			n = RBIOS8(पंचांगds_info + 5) + 1;
			अगर (n > 4)
				n = 4;
			क्रम (i = 0; i < n; i++) अणु
				पंचांगds->पंचांगds_pll[i].value =
				    RBIOS32(पंचांगds_info + i * 10 + 0x08);
				पंचांगds->पंचांगds_pll[i].freq =
				    RBIOS16(पंचांगds_info + i * 10 + 0x10);
				DRM_DEBUG_KMS("TMDS PLL From COMBIOS %u %x\n",
					  पंचांगds->पंचांगds_pll[i].freq,
					  पंचांगds->पंचांगds_pll[i].value);
			पूर्ण
		पूर्ण अन्यथा अगर (ver == 4) अणु
			पूर्णांक stride = 0;
			n = RBIOS8(पंचांगds_info + 5) + 1;
			अगर (n > 4)
				n = 4;
			क्रम (i = 0; i < n; i++) अणु
				पंचांगds->पंचांगds_pll[i].value =
				    RBIOS32(पंचांगds_info + stride + 0x08);
				पंचांगds->पंचांगds_pll[i].freq =
				    RBIOS16(पंचांगds_info + stride + 0x10);
				अगर (i == 0)
					stride += 10;
				अन्यथा
					stride += 6;
				DRM_DEBUG_KMS("TMDS PLL From COMBIOS %u %x\n",
					  पंचांगds->पंचांगds_pll[i].freq,
					  पंचांगds->पंचांगds_pll[i].value);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_INFO("No TMDS info found in BIOS\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

bool radeon_legacy_get_ext_पंचांगds_info_from_table(काष्ठा radeon_encoder *encoder,
						काष्ठा radeon_encoder_ext_पंचांगds *पंचांगds)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec i2c_bus;

	/* शेष क्रम macs */
	i2c_bus = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
	पंचांगds->i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);

	/* XXX some macs have duallink chips */
	चयन (rdev->mode_info.connector_table) अणु
	हाल CT_POWERBOOK_EXTERNAL:
	हाल CT_MINI_EXTERNAL:
	शेष:
		पंचांगds->dvo_chip = DVO_SIL164;
		पंचांगds->slave_addr = 0x70 >> 1; /* 7 bit addressing */
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

bool radeon_legacy_get_ext_पंचांगds_info_from_combios(काष्ठा radeon_encoder *encoder,
						  काष्ठा radeon_encoder_ext_पंचांगds *पंचांगds)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक16_t offset;
	uपूर्णांक8_t ver;
	क्रमागत radeon_combios_ddc gpio;
	काष्ठा radeon_i2c_bus_rec i2c_bus;

	पंचांगds->i2c_bus = शून्य;
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		i2c_bus = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		पंचांगds->i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
		पंचांगds->dvo_chip = DVO_SIL164;
		पंचांगds->slave_addr = 0x70 >> 1; /* 7 bit addressing */
	पूर्ण अन्यथा अणु
		offset = combios_get_table_offset(dev, COMBIOS_EXT_TMDS_INFO_TABLE);
		अगर (offset) अणु
			ver = RBIOS8(offset);
			DRM_DEBUG_KMS("External TMDS Table revision: %d\n", ver);
			पंचांगds->slave_addr = RBIOS8(offset + 4 + 2);
			पंचांगds->slave_addr >>= 1; /* 7 bit addressing */
			gpio = RBIOS8(offset + 4 + 3);
			अगर (gpio == DDC_LCD) अणु
				/* MM i2c */
				i2c_bus.valid = true;
				i2c_bus.hw_capable = true;
				i2c_bus.mm_i2c = true;
				i2c_bus.i2c_id = 0xa0;
			पूर्ण अन्यथा
				i2c_bus = combios_setup_i2c_bus(rdev, gpio, 0, 0);
			पंचांगds->i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
		पूर्ण
	पूर्ण

	अगर (!पंचांगds->i2c_bus) अणु
		DRM_INFO("No valid Ext TMDS info found in BIOS\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool radeon_get_legacy_connector_info_from_table(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_i2c_bus_rec ddc_i2c;
	काष्ठा radeon_hpd hpd;

	rdev->mode_info.connector_table = radeon_connector_table;
	अगर (rdev->mode_info.connector_table == CT_NONE) अणु
#अगर_घोषित CONFIG_PPC_PMAC
		अगर (of_machine_is_compatible("PowerBook3,3")) अणु
			/* घातerbook with VGA */
			rdev->mode_info.connector_table = CT_POWERBOOK_VGA;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerBook3,4") ||
			   of_machine_is_compatible("PowerBook3,5")) अणु
			/* घातerbook with पूर्णांकernal पंचांगds */
			rdev->mode_info.connector_table = CT_POWERBOOK_INTERNAL;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerBook5,1") ||
			   of_machine_is_compatible("PowerBook5,2") ||
			   of_machine_is_compatible("PowerBook5,3") ||
			   of_machine_is_compatible("PowerBook5,4") ||
			   of_machine_is_compatible("PowerBook5,5")) अणु
			/* घातerbook with बाह्यal single link पंचांगds (sil164) */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerBook5,6")) अणु
			/* घातerbook with बाह्यal dual or single link पंचांगds */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerBook5,7") ||
			   of_machine_is_compatible("PowerBook5,8") ||
			   of_machine_is_compatible("PowerBook5,9")) अणु
			/* PowerBook6,2 ? */
			/* घातerbook with बाह्यal dual link पंचांगds (sil1178?) */
			rdev->mode_info.connector_table = CT_POWERBOOK_EXTERNAL;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerBook4,1") ||
			   of_machine_is_compatible("PowerBook4,2") ||
			   of_machine_is_compatible("PowerBook4,3") ||
			   of_machine_is_compatible("PowerBook6,3") ||
			   of_machine_is_compatible("PowerBook6,5") ||
			   of_machine_is_compatible("PowerBook6,7")) अणु
			/* ibook */
			rdev->mode_info.connector_table = CT_IBOOK;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerMac3,5")) अणु
			/* PowerMac G4 Silver radeon 7500 */
			rdev->mode_info.connector_table = CT_MAC_G4_SILVER;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerMac4,4")) अणु
			/* emac */
			rdev->mode_info.connector_table = CT_EMAC;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerMac10,1")) अणु
			/* mini with पूर्णांकernal पंचांगds */
			rdev->mode_info.connector_table = CT_MINI_INTERNAL;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerMac10,2")) अणु
			/* mini with बाह्यal पंचांगds */
			rdev->mode_info.connector_table = CT_MINI_EXTERNAL;
		पूर्ण अन्यथा अगर (of_machine_is_compatible("PowerMac12,1")) अणु
			/* PowerMac8,1 ? */
			/* imac g5 isight */
			rdev->mode_info.connector_table = CT_IMAC_G5_ISIGHT;
		पूर्ण अन्यथा अगर ((rdev->pdev->device == 0x4a48) &&
			   (rdev->pdev->subप्रणाली_venकरोr == 0x1002) &&
			   (rdev->pdev->subप्रणाली_device == 0x4a48)) अणु
			/* Mac X800 */
			rdev->mode_info.connector_table = CT_MAC_X800;
		पूर्ण अन्यथा अगर ((of_machine_is_compatible("PowerMac7,2") ||
			    of_machine_is_compatible("PowerMac7,3")) &&
			   (rdev->pdev->device == 0x4150) &&
			   (rdev->pdev->subप्रणाली_venकरोr == 0x1002) &&
			   (rdev->pdev->subप्रणाली_device == 0x4150)) अणु
			/* Mac G5 tower 9600 */
			rdev->mode_info.connector_table = CT_MAC_G5_9600;
		पूर्ण अन्यथा अगर ((rdev->pdev->device == 0x4c66) &&
			   (rdev->pdev->subप्रणाली_venकरोr == 0x1002) &&
			   (rdev->pdev->subप्रणाली_device == 0x4c66)) अणु
			/* SAM440ep RV250 embedded board */
			rdev->mode_info.connector_table = CT_SAM440EP;
		पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_PPC_PMAC */
#अगर_घोषित CONFIG_PPC64
		अगर (ASIC_IS_RN50(rdev))
			rdev->mode_info.connector_table = CT_RN50_POWER;
		अन्यथा
#पूर्ण_अगर
			rdev->mode_info.connector_table = CT_GENERIC;
	पूर्ण

	चयन (rdev->mode_info.connector_table) अणु
	हाल CT_GENERIC:
		DRM_INFO("Connector Table: %d (generic)\n",
			 rdev->mode_info.connector_table);
		/* these are the most common settings */
		अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
			/* VGA - primary dac */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_CRT1_SUPPORT,
									1),
						  ATOM_DEVICE_CRT1_SUPPORT);
			radeon_add_legacy_connector(dev, 0,
						    ATOM_DEVICE_CRT1_SUPPORT,
						    DRM_MODE_CONNECTOR_VGA,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_VGA,
						    &hpd);
		पूर्ण अन्यथा अगर (rdev->flags & RADEON_IS_MOBILITY) अणु
			/* LVDS */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_NONE_DETECTED, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_LCD1_SUPPORT,
									0),
						  ATOM_DEVICE_LCD1_SUPPORT);
			radeon_add_legacy_connector(dev, 0,
						    ATOM_DEVICE_LCD1_SUPPORT,
						    DRM_MODE_CONNECTOR_LVDS,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_LVDS,
						    &hpd);

			/* VGA - primary dac */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_CRT1_SUPPORT,
									1),
						  ATOM_DEVICE_CRT1_SUPPORT);
			radeon_add_legacy_connector(dev, 1,
						    ATOM_DEVICE_CRT1_SUPPORT,
						    DRM_MODE_CONNECTOR_VGA,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_VGA,
						    &hpd);
		पूर्ण अन्यथा अणु
			/* DVI-I - tv dac, पूर्णांक पंचांगds */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
			hpd.hpd = RADEON_HPD_1;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_DFP1_SUPPORT,
									0),
						  ATOM_DEVICE_DFP1_SUPPORT);
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_CRT2_SUPPORT,
									2),
						  ATOM_DEVICE_CRT2_SUPPORT);
			radeon_add_legacy_connector(dev, 0,
						    ATOM_DEVICE_DFP1_SUPPORT |
						    ATOM_DEVICE_CRT2_SUPPORT,
						    DRM_MODE_CONNECTOR_DVII,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
						    &hpd);

			/* VGA - primary dac */
			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_CRT1_SUPPORT,
									1),
						  ATOM_DEVICE_CRT1_SUPPORT);
			radeon_add_legacy_connector(dev, 1,
						    ATOM_DEVICE_CRT1_SUPPORT,
						    DRM_MODE_CONNECTOR_VGA,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_VGA,
						    &hpd);
		पूर्ण

		अगर (rdev->family != CHIP_R100 && rdev->family != CHIP_R200) अणु
			/* TV - tv dac */
			ddc_i2c.valid = false;
			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_TV1_SUPPORT,
									2),
						  ATOM_DEVICE_TV1_SUPPORT);
			radeon_add_legacy_connector(dev, 2,
						    ATOM_DEVICE_TV1_SUPPORT,
						    DRM_MODE_CONNECTOR_SVIDEO,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_SVIDEO,
						    &hpd);
		पूर्ण
		अवरोध;
	हाल CT_IBOOK:
		DRM_INFO("Connector Table: %d (ibook)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* VGA - TV DAC */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_POWERBOOK_EXTERNAL:
		DRM_INFO("Connector Table: %d (powerbook external tmds)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* DVI-I - primary dac, ext पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_DFP2_SUPPORT,
								0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		/* XXX some are SL */
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_POWERBOOK_INTERNAL:
		DRM_INFO("Connector Table: %d (powerbook internal tmds)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* DVI-I - primary dac, पूर्णांक पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_POWERBOOK_VGA:
		DRM_INFO("Connector Table: %d (powerbook vga)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_MINI_EXTERNAL:
		DRM_INFO("Connector Table: %d (mini external tmds)\n",
			 rdev->mode_info.connector_table);
		/* DVI-I - tv dac, ext पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_DFP2_SUPPORT,
								0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		/* XXX are any DL? */
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_MINI_INTERNAL:
		DRM_INFO("Connector Table: %d (mini internal tmds)\n",
			 rdev->mode_info.connector_table);
		/* DVI-I - tv dac, पूर्णांक पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_IMAC_G5_ISIGHT:
		DRM_INFO("Connector Table: %d (imac g5 isight)\n",
			 rdev->mode_info.connector_table);
		/* DVI-D - पूर्णांक पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_DFP1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVID, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D,
					    &hpd);
		/* VGA - tv dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_EMAC:
		DRM_INFO("Connector Table: %d (emac)\n",
			 rdev->mode_info.connector_table);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* VGA - tv dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_RN50_POWER:
		DRM_INFO("Connector Table: %d (rn50-power)\n",
			 rdev->mode_info.connector_table);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_CRT2, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		अवरोध;
	हाल CT_MAC_X800:
		DRM_INFO("Connector Table: %d (mac x800)\n",
			 rdev->mode_info.connector_table);
		/* DVI - primary dac, पूर्णांकernal पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_DFP1_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_CRT1_SUPPORT,
								  1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* DVI - tv dac, dvo */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_DFP2_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_CRT2_SUPPORT,
								  2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I,
					    &hpd);
		अवरोध;
	हाल CT_MAC_G5_9600:
		DRM_INFO("Connector Table: %d (mac g5 9600)\n",
			 rdev->mode_info.connector_table);
		/* DVI - tv dac, dvo */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_DFP2_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP2_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_CRT2_SUPPORT,
								  2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP2_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* ADC - primary dac, पूर्णांकernal पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_2; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_DFP1_SUPPORT,
								  0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								  ATOM_DEVICE_CRT1_SUPPORT,
								  1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_SAM440EP:
		DRM_INFO("Connector Table: %d (SAM440ep embedded board)\n",
			 rdev->mode_info.connector_table);
		/* LVDS */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_NONE_DETECTED, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_LCD1_SUPPORT,
								0),
					  ATOM_DEVICE_LCD1_SUPPORT);
		radeon_add_legacy_connector(dev, 0, ATOM_DEVICE_LCD1_SUPPORT,
					    DRM_MODE_CONNECTOR_LVDS, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_LVDS,
					    &hpd);
		/* DVI-I - secondary dac, पूर्णांक पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 1,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 2,
					    ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 3, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	हाल CT_MAC_G4_SILVER:
		DRM_INFO("Connector Table: %d (mac g4 silver)\n",
			 rdev->mode_info.connector_table);
		/* DVI-I - tv dac, पूर्णांक पंचांगds */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
		hpd.hpd = RADEON_HPD_1; /* ??? */
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_DFP1_SUPPORT,
								0),
					  ATOM_DEVICE_DFP1_SUPPORT);
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT2_SUPPORT,
								2),
					  ATOM_DEVICE_CRT2_SUPPORT);
		radeon_add_legacy_connector(dev, 0,
					    ATOM_DEVICE_DFP1_SUPPORT |
					    ATOM_DEVICE_CRT2_SUPPORT,
					    DRM_MODE_CONNECTOR_DVII, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
					    &hpd);
		/* VGA - primary dac */
		ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_CRT1_SUPPORT,
								1),
					  ATOM_DEVICE_CRT1_SUPPORT);
		radeon_add_legacy_connector(dev, 1, ATOM_DEVICE_CRT1_SUPPORT,
					    DRM_MODE_CONNECTOR_VGA, &ddc_i2c,
					    CONNECTOR_OBJECT_ID_VGA,
					    &hpd);
		/* TV - TV DAC */
		ddc_i2c.valid = false;
		hpd.hpd = RADEON_HPD_NONE;
		radeon_add_legacy_encoder(dev,
					  radeon_get_encoder_क्रमागत(dev,
								ATOM_DEVICE_TV1_SUPPORT,
								2),
					  ATOM_DEVICE_TV1_SUPPORT);
		radeon_add_legacy_connector(dev, 2, ATOM_DEVICE_TV1_SUPPORT,
					    DRM_MODE_CONNECTOR_SVIDEO,
					    &ddc_i2c,
					    CONNECTOR_OBJECT_ID_SVIDEO,
					    &hpd);
		अवरोध;
	शेष:
		DRM_INFO("Connector table: %d (invalid)\n",
			 rdev->mode_info.connector_table);
		वापस false;
	पूर्ण

	radeon_link_encoder_connector(dev);

	वापस true;
पूर्ण

अटल bool radeon_apply_legacy_quirks(काष्ठा drm_device *dev,
				       पूर्णांक bios_index,
				       क्रमागत radeon_combios_connector
				       *legacy_connector,
				       काष्ठा radeon_i2c_bus_rec *ddc_i2c,
				       काष्ठा radeon_hpd *hpd)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	/* Certain IBM chipset RN50s have a BIOS reporting two VGAs,
	   one with VGA DDC and one with CRT2 DDC. - समाप्त the CRT2 DDC one */
	अगर (rdev->pdev->device == 0x515e &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x1014) अणु
		अगर (*legacy_connector == CONNECTOR_CRT_LEGACY &&
		    ddc_i2c->mask_clk_reg == RADEON_GPIO_CRT2_DDC)
			वापस false;
	पूर्ण

	/* X300 card with extra non-existent DVI port */
	अगर (rdev->pdev->device == 0x5B60 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x17af &&
	    rdev->pdev->subप्रणाली_device == 0x201e && bios_index == 2) अणु
		अगर (*legacy_connector == CONNECTOR_DVI_I_LEGACY)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool radeon_apply_legacy_tv_quirks(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	/* Acer 5102 has non-existent TV port */
	अगर (rdev->pdev->device == 0x5975 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x1025 &&
	    rdev->pdev->subप्रणाली_device == 0x009f)
		वापस false;

	/* HP dc5750 has non-existent TV port */
	अगर (rdev->pdev->device == 0x5974 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x103c &&
	    rdev->pdev->subप्रणाली_device == 0x280a)
		वापस false;

	/* MSI S270 has non-existent TV port */
	अगर (rdev->pdev->device == 0x5955 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x1462 &&
	    rdev->pdev->subप्रणाली_device == 0x0131)
		वापस false;

	वापस true;
पूर्ण

अटल uपूर्णांक16_t combios_check_dl_dvi(काष्ठा drm_device *dev, पूर्णांक is_dvi_d)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t ext_पंचांगds_info;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (is_dvi_d)
			वापस CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D;
		अन्यथा
			वापस CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I;
	पूर्ण
	ext_पंचांगds_info = combios_get_table_offset(dev, COMBIOS_EXT_TMDS_INFO_TABLE);
	अगर (ext_पंचांगds_info) अणु
		uपूर्णांक8_t rev = RBIOS8(ext_पंचांगds_info);
		uपूर्णांक8_t flags = RBIOS8(ext_पंचांगds_info + 4 + 5);
		अगर (rev >= 3) अणु
			अगर (is_dvi_d)
				वापस CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D;
			अन्यथा
				वापस CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I;
		पूर्ण अन्यथा अणु
			अगर (flags & 1) अणु
				अगर (is_dvi_d)
					वापस CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D;
				अन्यथा
					वापस CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (is_dvi_d)
		वापस CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D;
	अन्यथा
		वापस CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I;
पूर्ण

bool radeon_get_legacy_connector_info_from_bios(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t conn_info, entry, devices;
	uपूर्णांक16_t पंचांगp, connector_object_id;
	क्रमागत radeon_combios_ddc ddc_type;
	क्रमागत radeon_combios_connector connector;
	पूर्णांक i = 0;
	काष्ठा radeon_i2c_bus_rec ddc_i2c;
	काष्ठा radeon_hpd hpd;

	conn_info = combios_get_table_offset(dev, COMBIOS_CONNECTOR_INFO_TABLE);
	अगर (conn_info) अणु
		क्रम (i = 0; i < 4; i++) अणु
			entry = conn_info + 2 + i * 2;

			अगर (!RBIOS16(entry))
				अवरोध;

			पंचांगp = RBIOS16(entry);

			connector = (पंचांगp >> 12) & 0xf;

			ddc_type = (पंचांगp >> 8) & 0xf;
			अगर (ddc_type == 5)
				ddc_i2c = radeon_combios_get_i2c_info_from_table(rdev);
			अन्यथा
				ddc_i2c = combios_setup_i2c_bus(rdev, ddc_type, 0, 0);

			चयन (connector) अणु
			हाल CONNECTOR_PROPRIETARY_LEGACY:
			हाल CONNECTOR_DVI_I_LEGACY:
			हाल CONNECTOR_DVI_D_LEGACY:
				अगर ((पंचांगp >> 4) & 0x1)
					hpd.hpd = RADEON_HPD_2;
				अन्यथा
					hpd.hpd = RADEON_HPD_1;
				अवरोध;
			शेष:
				hpd.hpd = RADEON_HPD_NONE;
				अवरोध;
			पूर्ण

			अगर (!radeon_apply_legacy_quirks(dev, i, &connector,
							&ddc_i2c, &hpd))
				जारी;

			चयन (connector) अणु
			हाल CONNECTOR_PROPRIETARY_LEGACY:
				अगर ((पंचांगp >> 4) & 0x1)
					devices = ATOM_DEVICE_DFP2_SUPPORT;
				अन्यथा
					devices = ATOM_DEVICE_DFP1_SUPPORT;
				radeon_add_legacy_encoder(dev,
							  radeon_get_encoder_क्रमागत
							  (dev, devices, 0),
							  devices);
				radeon_add_legacy_connector(dev, i, devices,
							    legacy_connector_convert
							    [connector],
							    &ddc_i2c,
							    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D,
							    &hpd);
				अवरोध;
			हाल CONNECTOR_CRT_LEGACY:
				अगर (पंचांगp & 0x1) अणु
					devices = ATOM_DEVICE_CRT2_SUPPORT;
					radeon_add_legacy_encoder(dev,
								  radeon_get_encoder_क्रमागत
								  (dev,
								   ATOM_DEVICE_CRT2_SUPPORT,
								   2),
								  ATOM_DEVICE_CRT2_SUPPORT);
				पूर्ण अन्यथा अणु
					devices = ATOM_DEVICE_CRT1_SUPPORT;
					radeon_add_legacy_encoder(dev,
								  radeon_get_encoder_क्रमागत
								  (dev,
								   ATOM_DEVICE_CRT1_SUPPORT,
								   1),
								  ATOM_DEVICE_CRT1_SUPPORT);
				पूर्ण
				radeon_add_legacy_connector(dev,
							    i,
							    devices,
							    legacy_connector_convert
							    [connector],
							    &ddc_i2c,
							    CONNECTOR_OBJECT_ID_VGA,
							    &hpd);
				अवरोध;
			हाल CONNECTOR_DVI_I_LEGACY:
				devices = 0;
				अगर (पंचांगp & 0x1) अणु
					devices |= ATOM_DEVICE_CRT2_SUPPORT;
					radeon_add_legacy_encoder(dev,
								  radeon_get_encoder_क्रमागत
								  (dev,
								   ATOM_DEVICE_CRT2_SUPPORT,
								   2),
								  ATOM_DEVICE_CRT2_SUPPORT);
				पूर्ण अन्यथा अणु
					devices |= ATOM_DEVICE_CRT1_SUPPORT;
					radeon_add_legacy_encoder(dev,
								  radeon_get_encoder_क्रमागत
								  (dev,
								   ATOM_DEVICE_CRT1_SUPPORT,
								   1),
								  ATOM_DEVICE_CRT1_SUPPORT);
				पूर्ण
				/* RV100 board with बाह्यal TDMS bit mis-set.
				 * Actually uses पूर्णांकernal TMDS, clear the bit.
				 */
				अगर (rdev->pdev->device == 0x5159 &&
				    rdev->pdev->subप्रणाली_venकरोr == 0x1014 &&
				    rdev->pdev->subप्रणाली_device == 0x029A) अणु
					पंचांगp &= ~(1 << 4);
				पूर्ण
				अगर ((पंचांगp >> 4) & 0x1) अणु
					devices |= ATOM_DEVICE_DFP2_SUPPORT;
					radeon_add_legacy_encoder(dev,
								  radeon_get_encoder_क्रमागत
								  (dev,
								   ATOM_DEVICE_DFP2_SUPPORT,
								   0),
								  ATOM_DEVICE_DFP2_SUPPORT);
					connector_object_id = combios_check_dl_dvi(dev, 0);
				पूर्ण अन्यथा अणु
					devices |= ATOM_DEVICE_DFP1_SUPPORT;
					radeon_add_legacy_encoder(dev,
								  radeon_get_encoder_क्रमागत
								  (dev,
								   ATOM_DEVICE_DFP1_SUPPORT,
								   0),
								  ATOM_DEVICE_DFP1_SUPPORT);
					connector_object_id = CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I;
				पूर्ण
				radeon_add_legacy_connector(dev,
							    i,
							    devices,
							    legacy_connector_convert
							    [connector],
							    &ddc_i2c,
							    connector_object_id,
							    &hpd);
				अवरोध;
			हाल CONNECTOR_DVI_D_LEGACY:
				अगर ((पंचांगp >> 4) & 0x1) अणु
					devices = ATOM_DEVICE_DFP2_SUPPORT;
					connector_object_id = combios_check_dl_dvi(dev, 1);
				पूर्ण अन्यथा अणु
					devices = ATOM_DEVICE_DFP1_SUPPORT;
					connector_object_id = CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I;
				पूर्ण
				radeon_add_legacy_encoder(dev,
							  radeon_get_encoder_क्रमागत
							  (dev, devices, 0),
							  devices);
				radeon_add_legacy_connector(dev, i, devices,
							    legacy_connector_convert
							    [connector],
							    &ddc_i2c,
							    connector_object_id,
							    &hpd);
				अवरोध;
			हाल CONNECTOR_CTV_LEGACY:
			हाल CONNECTOR_STV_LEGACY:
				radeon_add_legacy_encoder(dev,
							  radeon_get_encoder_क्रमागत
							  (dev,
							   ATOM_DEVICE_TV1_SUPPORT,
							   2),
							  ATOM_DEVICE_TV1_SUPPORT);
				radeon_add_legacy_connector(dev, i,
							    ATOM_DEVICE_TV1_SUPPORT,
							    legacy_connector_convert
							    [connector],
							    &ddc_i2c,
							    CONNECTOR_OBJECT_ID_SVIDEO,
							    &hpd);
				अवरोध;
			शेष:
				DRM_ERROR("Unknown connector type: %d\n",
					  connector);
				जारी;
			पूर्ण

		पूर्ण
	पूर्ण अन्यथा अणु
		uपूर्णांक16_t पंचांगds_info =
		    combios_get_table_offset(dev, COMBIOS_DFP_INFO_TABLE);
		अगर (पंचांगds_info) अणु
			DRM_DEBUG_KMS("Found DFP table, assuming DVI connector\n");

			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_CRT1_SUPPORT,
									1),
						  ATOM_DEVICE_CRT1_SUPPORT);
			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_DFP1_SUPPORT,
									0),
						  ATOM_DEVICE_DFP1_SUPPORT);

			ddc_i2c = combios_setup_i2c_bus(rdev, DDC_DVI, 0, 0);
			hpd.hpd = RADEON_HPD_1;
			radeon_add_legacy_connector(dev,
						    0,
						    ATOM_DEVICE_CRT1_SUPPORT |
						    ATOM_DEVICE_DFP1_SUPPORT,
						    DRM_MODE_CONNECTOR_DVII,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_I,
						    &hpd);
		पूर्ण अन्यथा अणु
			uपूर्णांक16_t crt_info =
				combios_get_table_offset(dev, COMBIOS_CRT_INFO_TABLE);
			DRM_DEBUG_KMS("Found CRT table, assuming VGA connector\n");
			अगर (crt_info) अणु
				radeon_add_legacy_encoder(dev,
							  radeon_get_encoder_क्रमागत(dev,
										ATOM_DEVICE_CRT1_SUPPORT,
										1),
							  ATOM_DEVICE_CRT1_SUPPORT);
				ddc_i2c = combios_setup_i2c_bus(rdev, DDC_VGA, 0, 0);
				hpd.hpd = RADEON_HPD_NONE;
				radeon_add_legacy_connector(dev,
							    0,
							    ATOM_DEVICE_CRT1_SUPPORT,
							    DRM_MODE_CONNECTOR_VGA,
							    &ddc_i2c,
							    CONNECTOR_OBJECT_ID_VGA,
							    &hpd);
			पूर्ण अन्यथा अणु
				DRM_DEBUG_KMS("No connector info found\n");
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rdev->flags & RADEON_IS_MOBILITY || rdev->flags & RADEON_IS_IGP) अणु
		uपूर्णांक16_t lcd_info =
		    combios_get_table_offset(dev, COMBIOS_LCD_INFO_TABLE);
		अगर (lcd_info) अणु
			uपूर्णांक16_t lcd_ddc_info =
			    combios_get_table_offset(dev,
						     COMBIOS_LCD_DDC_INFO_TABLE);

			radeon_add_legacy_encoder(dev,
						  radeon_get_encoder_क्रमागत(dev,
									ATOM_DEVICE_LCD1_SUPPORT,
									0),
						  ATOM_DEVICE_LCD1_SUPPORT);

			अगर (lcd_ddc_info) अणु
				ddc_type = RBIOS8(lcd_ddc_info + 2);
				चयन (ddc_type) अणु
				हाल DDC_LCD:
					ddc_i2c =
						combios_setup_i2c_bus(rdev,
								      DDC_LCD,
								      RBIOS32(lcd_ddc_info + 3),
								      RBIOS32(lcd_ddc_info + 7));
					radeon_i2c_add(rdev, &ddc_i2c, "LCD");
					अवरोध;
				हाल DDC_GPIO:
					ddc_i2c =
						combios_setup_i2c_bus(rdev,
								      DDC_GPIO,
								      RBIOS32(lcd_ddc_info + 3),
								      RBIOS32(lcd_ddc_info + 7));
					radeon_i2c_add(rdev, &ddc_i2c, "LCD");
					अवरोध;
				शेष:
					ddc_i2c =
						combios_setup_i2c_bus(rdev, ddc_type, 0, 0);
					अवरोध;
				पूर्ण
				DRM_DEBUG_KMS("LCD DDC Info Table found!\n");
			पूर्ण अन्यथा
				ddc_i2c.valid = false;

			hpd.hpd = RADEON_HPD_NONE;
			radeon_add_legacy_connector(dev,
						    5,
						    ATOM_DEVICE_LCD1_SUPPORT,
						    DRM_MODE_CONNECTOR_LVDS,
						    &ddc_i2c,
						    CONNECTOR_OBJECT_ID_LVDS,
						    &hpd);
		पूर्ण
	पूर्ण

	/* check TV table */
	अगर (rdev->family != CHIP_R100 && rdev->family != CHIP_R200) अणु
		uपूर्णांक32_t tv_info =
		    combios_get_table_offset(dev, COMBIOS_TV_INFO_TABLE);
		अगर (tv_info) अणु
			अगर (RBIOS8(tv_info + 6) == 'T') अणु
				अगर (radeon_apply_legacy_tv_quirks(dev)) अणु
					hpd.hpd = RADEON_HPD_NONE;
					ddc_i2c.valid = false;
					radeon_add_legacy_encoder(dev,
								  radeon_get_encoder_क्रमागत
								  (dev,
								   ATOM_DEVICE_TV1_SUPPORT,
								   2),
								  ATOM_DEVICE_TV1_SUPPORT);
					radeon_add_legacy_connector(dev, 6,
								    ATOM_DEVICE_TV1_SUPPORT,
								    DRM_MODE_CONNECTOR_SVIDEO,
								    &ddc_i2c,
								    CONNECTOR_OBJECT_ID_SVIDEO,
								    &hpd);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	radeon_link_encoder_connector(dev);

	वापस true;
पूर्ण

अटल स्थिर अक्षर *thermal_controller_names[] = अणु
	"NONE",
	"lm63",
	"adm1032",
पूर्ण;

व्योम radeon_combios_get_घातer_modes(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	u16 offset, misc, misc2 = 0;
	u8 rev, पंचांगp;
	पूर्णांक state_index = 0;
	काष्ठा radeon_i2c_bus_rec i2c_bus;

	rdev->pm.शेष_घातer_state_index = -1;

	/* allocate 2 घातer states */
	rdev->pm.घातer_state = kसुस्मृति(2, माप(काष्ठा radeon_घातer_state),
				       GFP_KERNEL);
	अगर (rdev->pm.घातer_state) अणु
		/* allocate 1 घड़ी mode per state */
		rdev->pm.घातer_state[0].घड़ी_info =
			kसुस्मृति(1, माप(काष्ठा radeon_pm_घड़ी_info),
				GFP_KERNEL);
		rdev->pm.घातer_state[1].घड़ी_info =
			kसुस्मृति(1, माप(काष्ठा radeon_pm_घड़ी_info),
				GFP_KERNEL);
		अगर (!rdev->pm.घातer_state[0].घड़ी_info ||
		    !rdev->pm.घातer_state[1].घड़ी_info)
			जाओ pm_failed;
	पूर्ण अन्यथा
		जाओ pm_failed;

	/* check क्रम a thermal chip */
	offset = combios_get_table_offset(dev, COMBIOS_OVERDRIVE_INFO_TABLE);
	अगर (offset) अणु
		u8 thermal_controller = 0, gpio = 0, i2c_addr = 0, clk_bit = 0, data_bit = 0;

		rev = RBIOS8(offset);

		अगर (rev == 0) अणु
			thermal_controller = RBIOS8(offset + 3);
			gpio = RBIOS8(offset + 4) & 0x3f;
			i2c_addr = RBIOS8(offset + 5);
		पूर्ण अन्यथा अगर (rev == 1) अणु
			thermal_controller = RBIOS8(offset + 4);
			gpio = RBIOS8(offset + 5) & 0x3f;
			i2c_addr = RBIOS8(offset + 6);
		पूर्ण अन्यथा अगर (rev == 2) अणु
			thermal_controller = RBIOS8(offset + 4);
			gpio = RBIOS8(offset + 5) & 0x3f;
			i2c_addr = RBIOS8(offset + 6);
			clk_bit = RBIOS8(offset + 0xa);
			data_bit = RBIOS8(offset + 0xb);
		पूर्ण
		अगर ((thermal_controller > 0) && (thermal_controller < 3)) अणु
			DRM_INFO("Possible %s thermal controller at 0x%02x\n",
				 thermal_controller_names[thermal_controller],
				 i2c_addr >> 1);
			अगर (gpio == DDC_LCD) अणु
				/* MM i2c */
				i2c_bus.valid = true;
				i2c_bus.hw_capable = true;
				i2c_bus.mm_i2c = true;
				i2c_bus.i2c_id = 0xa0;
			पूर्ण अन्यथा अगर (gpio == DDC_GPIO)
				i2c_bus = combios_setup_i2c_bus(rdev, gpio, 1 << clk_bit, 1 << data_bit);
			अन्यथा
				i2c_bus = combios_setup_i2c_bus(rdev, gpio, 0, 0);
			rdev->pm.i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
			अगर (rdev->pm.i2c_bus) अणु
				काष्ठा i2c_board_info info = अणु पूर्ण;
				स्थिर अक्षर *name = thermal_controller_names[thermal_controller];
				info.addr = i2c_addr >> 1;
				strlcpy(info.type, name, माप(info.type));
				i2c_new_client_device(&rdev->pm.i2c_bus->adapter, &info);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* boards with a thermal chip, but no overdrive table */

		/* Asus 9600xt has an f75375 on the monid bus */
		अगर ((rdev->pdev->device == 0x4152) &&
		    (rdev->pdev->subप्रणाली_venकरोr == 0x1043) &&
		    (rdev->pdev->subप्रणाली_device == 0xc002)) अणु
			i2c_bus = combios_setup_i2c_bus(rdev, DDC_MONID, 0, 0);
			rdev->pm.i2c_bus = radeon_i2c_lookup(rdev, &i2c_bus);
			अगर (rdev->pm.i2c_bus) अणु
				काष्ठा i2c_board_info info = अणु पूर्ण;
				स्थिर अक्षर *name = "f75375";
				info.addr = 0x28;
				strlcpy(info.type, name, माप(info.type));
				i2c_new_client_device(&rdev->pm.i2c_bus->adapter, &info);
				DRM_INFO("Possible %s thermal controller at 0x%02x\n",
					 name, info.addr);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rdev->flags & RADEON_IS_MOBILITY) अणु
		offset = combios_get_table_offset(dev, COMBIOS_POWERPLAY_INFO_TABLE);
		अगर (offset) अणु
			rev = RBIOS8(offset);
			/* घातer mode 0 tends to be the only valid one */
			rdev->pm.घातer_state[state_index].num_घड़ी_modes = 1;
			rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk = RBIOS32(offset + 0x5 + 0x2);
			rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk = RBIOS32(offset + 0x5 + 0x6);
			अगर ((rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk == 0) ||
			    (rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk == 0))
				जाओ शेष_mode;
			rdev->pm.घातer_state[state_index].type =
				POWER_STATE_TYPE_BATTERY;
			misc = RBIOS16(offset + 0x5 + 0x0);
			अगर (rev > 4)
				misc2 = RBIOS16(offset + 0x5 + 0xe);
			rdev->pm.घातer_state[state_index].misc = misc;
			rdev->pm.घातer_state[state_index].misc2 = misc2;
			अगर (misc & 0x4) अणु
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type = VOLTAGE_GPIO;
				अगर (misc & 0x8)
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						true;
				अन्यथा
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.active_high =
						false;
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio.valid = true;
				अगर (rev < 6) अणु
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio.reg =
						RBIOS16(offset + 0x5 + 0xb) * 4;
					पंचांगp = RBIOS8(offset + 0x5 + 0xd);
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio.mask = (1 << पंचांगp);
				पूर्ण अन्यथा अणु
					u8 entries = RBIOS8(offset + 0x5 + 0xb);
					u16 voltage_table_offset = RBIOS16(offset + 0x5 + 0xc);
					अगर (entries && voltage_table_offset) अणु
						rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio.reg =
							RBIOS16(voltage_table_offset) * 4;
						पंचांगp = RBIOS8(voltage_table_offset + 0x2);
						rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio.mask = (1 << पंचांगp);
					पूर्ण अन्यथा
						rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.gpio.valid = false;
				पूर्ण
				चयन ((misc2 & 0x700) >> 8) अणु
				हाल 0:
				शेष:
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.delay = 0;
					अवरोध;
				हाल 1:
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.delay = 33;
					अवरोध;
				हाल 2:
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.delay = 66;
					अवरोध;
				हाल 3:
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.delay = 99;
					अवरोध;
				हाल 4:
					rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.delay = 132;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा
				rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type = VOLTAGE_NONE;
			अगर (rev > 6)
				rdev->pm.घातer_state[state_index].pcie_lanes =
					RBIOS8(offset + 0x5 + 0x10);
			rdev->pm.घातer_state[state_index].flags = RADEON_PM_STATE_SINGLE_DISPLAY_ONLY;
			state_index++;
		पूर्ण अन्यथा अणु
			/* XXX figure out some good शेष low घातer mode क्रम mobility cards w/out घातer tables */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* XXX figure out some good शेष low घातer mode क्रम desktop cards */
	पूर्ण

शेष_mode:
	/* add the शेष mode */
	rdev->pm.घातer_state[state_index].type =
		POWER_STATE_TYPE_DEFAULT;
	rdev->pm.घातer_state[state_index].num_घड़ी_modes = 1;
	rdev->pm.घातer_state[state_index].घड़ी_info[0].mclk = rdev->घड़ी.शेष_mclk;
	rdev->pm.घातer_state[state_index].घड़ी_info[0].sclk = rdev->घड़ी.शेष_sclk;
	rdev->pm.घातer_state[state_index].शेष_घड़ी_mode = &rdev->pm.घातer_state[state_index].घड़ी_info[0];
	अगर ((state_index > 0) &&
	    (rdev->pm.घातer_state[0].घड़ी_info[0].voltage.type == VOLTAGE_GPIO))
		rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage =
			rdev->pm.घातer_state[0].घड़ी_info[0].voltage;
	अन्यथा
		rdev->pm.घातer_state[state_index].घड़ी_info[0].voltage.type = VOLTAGE_NONE;
	rdev->pm.घातer_state[state_index].pcie_lanes = 16;
	rdev->pm.घातer_state[state_index].flags = 0;
	rdev->pm.शेष_घातer_state_index = state_index;
	rdev->pm.num_घातer_states = state_index + 1;

	rdev->pm.current_घातer_state_index = rdev->pm.शेष_घातer_state_index;
	rdev->pm.current_घड़ी_mode_index = 0;
	वापस;

pm_failed:
	rdev->pm.शेष_घातer_state_index = state_index;
	rdev->pm.num_घातer_states = 0;

	rdev->pm.current_घातer_state_index = rdev->pm.शेष_घातer_state_index;
	rdev->pm.current_घड़ी_mode_index = 0;
पूर्ण

व्योम radeon_बाह्यal_पंचांगds_setup(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_ext_पंचांगds *पंचांगds = radeon_encoder->enc_priv;

	अगर (!पंचांगds)
		वापस;

	चयन (पंचांगds->dvo_chip) अणु
	हाल DVO_SIL164:
		/* sil 164 */
		radeon_i2c_put_byte(पंचांगds->i2c_bus,
				    पंचांगds->slave_addr,
				    0x08, 0x30);
		radeon_i2c_put_byte(पंचांगds->i2c_bus,
				       पंचांगds->slave_addr,
				       0x09, 0x00);
		radeon_i2c_put_byte(पंचांगds->i2c_bus,
				    पंचांगds->slave_addr,
				    0x0a, 0x90);
		radeon_i2c_put_byte(पंचांगds->i2c_bus,
				    पंचांगds->slave_addr,
				    0x0c, 0x89);
		radeon_i2c_put_byte(पंचांगds->i2c_bus,
				       पंचांगds->slave_addr,
				       0x08, 0x3b);
		अवरोध;
	हाल DVO_SIL1178:
		/* sil 1178 - untested */
		/*
		 * 0x0f, 0x44
		 * 0x0f, 0x4c
		 * 0x0e, 0x01
		 * 0x0a, 0x80
		 * 0x09, 0x30
		 * 0x0c, 0xc9
		 * 0x0d, 0x70
		 * 0x08, 0x32
		 * 0x08, 0x33
		 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पूर्ण

bool radeon_combios_बाह्यal_पंचांगds_setup(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक16_t offset;
	uपूर्णांक8_t blocks, slave_addr, rev;
	uपूर्णांक32_t index, id;
	uपूर्णांक32_t reg, val, and_mask, or_mask;
	काष्ठा radeon_encoder_ext_पंचांगds *पंचांगds = radeon_encoder->enc_priv;

	अगर (!पंचांगds)
		वापस false;

	अगर (rdev->flags & RADEON_IS_IGP) अणु
		offset = combios_get_table_offset(dev, COMBIOS_TMDS_POWER_ON_TABLE);
		rev = RBIOS8(offset);
		अगर (offset) अणु
			rev = RBIOS8(offset);
			अगर (rev > 1) अणु
				blocks = RBIOS8(offset + 3);
				index = offset + 4;
				जबतक (blocks > 0) अणु
					id = RBIOS16(index);
					index += 2;
					चयन (id >> 13) अणु
					हाल 0:
						reg = (id & 0x1fff) * 4;
						val = RBIOS32(index);
						index += 4;
						WREG32(reg, val);
						अवरोध;
					हाल 2:
						reg = (id & 0x1fff) * 4;
						and_mask = RBIOS32(index);
						index += 4;
						or_mask = RBIOS32(index);
						index += 4;
						val = RREG32(reg);
						val = (val & and_mask) | or_mask;
						WREG32(reg, val);
						अवरोध;
					हाल 3:
						val = RBIOS16(index);
						index += 2;
						udelay(val);
						अवरोध;
					हाल 4:
						val = RBIOS16(index);
						index += 2;
						mdelay(val);
						अवरोध;
					हाल 6:
						slave_addr = id & 0xff;
						slave_addr >>= 1; /* 7 bit addressing */
						index++;
						reg = RBIOS8(index);
						index++;
						val = RBIOS8(index);
						index++;
						radeon_i2c_put_byte(पंचांगds->i2c_bus,
								    slave_addr,
								    reg, val);
						अवरोध;
					शेष:
						DRM_ERROR("Unknown id %d\n", id >> 13);
						अवरोध;
					पूर्ण
					blocks--;
				पूर्ण
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		offset = combios_get_table_offset(dev, COMBIOS_EXT_TMDS_INFO_TABLE);
		अगर (offset) अणु
			index = offset + 10;
			id = RBIOS16(index);
			जबतक (id != 0xffff) अणु
				index += 2;
				चयन (id >> 13) अणु
				हाल 0:
					reg = (id & 0x1fff) * 4;
					val = RBIOS32(index);
					WREG32(reg, val);
					अवरोध;
				हाल 2:
					reg = (id & 0x1fff) * 4;
					and_mask = RBIOS32(index);
					index += 4;
					or_mask = RBIOS32(index);
					index += 4;
					val = RREG32(reg);
					val = (val & and_mask) | or_mask;
					WREG32(reg, val);
					अवरोध;
				हाल 4:
					val = RBIOS16(index);
					index += 2;
					udelay(val);
					अवरोध;
				हाल 5:
					reg = id & 0x1fff;
					and_mask = RBIOS32(index);
					index += 4;
					or_mask = RBIOS32(index);
					index += 4;
					val = RREG32_PLL(reg);
					val = (val & and_mask) | or_mask;
					WREG32_PLL(reg, val);
					अवरोध;
				हाल 6:
					reg = id & 0x1fff;
					val = RBIOS8(index);
					index += 1;
					radeon_i2c_put_byte(पंचांगds->i2c_bus,
							    पंचांगds->slave_addr,
							    reg, val);
					अवरोध;
				शेष:
					DRM_ERROR("Unknown id %d\n", id >> 13);
					अवरोध;
				पूर्ण
				id = RBIOS16(index);
			पूर्ण
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम combios_parse_mmio_table(काष्ठा drm_device *dev, uपूर्णांक16_t offset)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (offset) अणु
		जबतक (RBIOS16(offset)) अणु
			uपूर्णांक16_t cmd = ((RBIOS16(offset) & 0xe000) >> 13);
			uपूर्णांक32_t addr = (RBIOS16(offset) & 0x1fff);
			uपूर्णांक32_t val, and_mask, or_mask;
			uपूर्णांक32_t पंचांगp;

			offset += 2;
			चयन (cmd) अणु
			हाल 0:
				val = RBIOS32(offset);
				offset += 4;
				WREG32(addr, val);
				अवरोध;
			हाल 1:
				val = RBIOS32(offset);
				offset += 4;
				WREG32(addr, val);
				अवरोध;
			हाल 2:
				and_mask = RBIOS32(offset);
				offset += 4;
				or_mask = RBIOS32(offset);
				offset += 4;
				पंचांगp = RREG32(addr);
				पंचांगp &= and_mask;
				पंचांगp |= or_mask;
				WREG32(addr, पंचांगp);
				अवरोध;
			हाल 3:
				and_mask = RBIOS32(offset);
				offset += 4;
				or_mask = RBIOS32(offset);
				offset += 4;
				पंचांगp = RREG32(addr);
				पंचांगp &= and_mask;
				पंचांगp |= or_mask;
				WREG32(addr, पंचांगp);
				अवरोध;
			हाल 4:
				val = RBIOS16(offset);
				offset += 2;
				udelay(val);
				अवरोध;
			हाल 5:
				val = RBIOS16(offset);
				offset += 2;
				चयन (addr) अणु
				हाल 8:
					जबतक (val--) अणु
						अगर (!
						    (RREG32_PLL
						     (RADEON_CLK_PWRMGT_CNTL) &
						     RADEON_MC_BUSY))
							अवरोध;
					पूर्ण
					अवरोध;
				हाल 9:
					जबतक (val--) अणु
						अगर ((RREG32(RADEON_MC_STATUS) &
						     RADEON_MC_IDLE))
							अवरोध;
					पूर्ण
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम combios_parse_pll_table(काष्ठा drm_device *dev, uपूर्णांक16_t offset)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (offset) अणु
		जबतक (RBIOS8(offset)) अणु
			uपूर्णांक8_t cmd = ((RBIOS8(offset) & 0xc0) >> 6);
			uपूर्णांक8_t addr = (RBIOS8(offset) & 0x3f);
			uपूर्णांक32_t val, shअगरt, पंचांगp;
			uपूर्णांक32_t and_mask, or_mask;

			offset++;
			चयन (cmd) अणु
			हाल 0:
				val = RBIOS32(offset);
				offset += 4;
				WREG32_PLL(addr, val);
				अवरोध;
			हाल 1:
				shअगरt = RBIOS8(offset) * 8;
				offset++;
				and_mask = RBIOS8(offset) << shअगरt;
				and_mask |= ~(0xff << shअगरt);
				offset++;
				or_mask = RBIOS8(offset) << shअगरt;
				offset++;
				पंचांगp = RREG32_PLL(addr);
				पंचांगp &= and_mask;
				पंचांगp |= or_mask;
				WREG32_PLL(addr, पंचांगp);
				अवरोध;
			हाल 2:
			हाल 3:
				पंचांगp = 1000;
				चयन (addr) अणु
				हाल 1:
					udelay(150);
					अवरोध;
				हाल 2:
					mdelay(1);
					अवरोध;
				हाल 3:
					जबतक (पंचांगp--) अणु
						अगर (!
						    (RREG32_PLL
						     (RADEON_CLK_PWRMGT_CNTL) &
						     RADEON_MC_BUSY))
							अवरोध;
					पूर्ण
					अवरोध;
				हाल 4:
					जबतक (पंचांगp--) अणु
						अगर (RREG32_PLL
						    (RADEON_CLK_PWRMGT_CNTL) &
						    RADEON_DLL_READY)
							अवरोध;
					पूर्ण
					अवरोध;
				हाल 5:
					पंचांगp =
					    RREG32_PLL(RADEON_CLK_PWRMGT_CNTL);
					अगर (पंचांगp & RADEON_CG_NO1_DEBUG_0) अणु
#अगर 0
						uपूर्णांक32_t mclk_cntl =
						    RREG32_PLL
						    (RADEON_MCLK_CNTL);
						mclk_cntl &= 0xffff0000;
						/*mclk_cntl |= 0x00001111;*//* ??? */
						WREG32_PLL(RADEON_MCLK_CNTL,
							   mclk_cntl);
						mdelay(10);
#पूर्ण_अगर
						WREG32_PLL
						    (RADEON_CLK_PWRMGT_CNTL,
						     पंचांगp &
						     ~RADEON_CG_NO1_DEBUG_0);
						mdelay(10);
					पूर्ण
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम combios_parse_ram_reset_table(काष्ठा drm_device *dev,
					  uपूर्णांक16_t offset)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t पंचांगp;

	अगर (offset) अणु
		uपूर्णांक8_t val = RBIOS8(offset);
		जबतक (val != 0xff) अणु
			offset++;

			अगर (val == 0x0f) अणु
				uपूर्णांक32_t channel_complete_mask;

				अगर (ASIC_IS_R300(rdev))
					channel_complete_mask =
					    R300_MEM_PWRUP_COMPLETE;
				अन्यथा
					channel_complete_mask =
					    RADEON_MEM_PWRUP_COMPLETE;
				पंचांगp = 20000;
				जबतक (पंचांगp--) अणु
					अगर ((RREG32(RADEON_MEM_STR_CNTL) &
					     channel_complete_mask) ==
					    channel_complete_mask)
						अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				uपूर्णांक32_t or_mask = RBIOS16(offset);
				offset += 2;

				पंचांगp = RREG32(RADEON_MEM_SDRAM_MODE_REG);
				पंचांगp &= RADEON_SDRAM_MODE_MASK;
				पंचांगp |= or_mask;
				WREG32(RADEON_MEM_SDRAM_MODE_REG, पंचांगp);

				or_mask = val << 24;
				पंचांगp = RREG32(RADEON_MEM_SDRAM_MODE_REG);
				पंचांगp &= RADEON_B3MEM_RESET_MASK;
				पंचांगp |= or_mask;
				WREG32(RADEON_MEM_SDRAM_MODE_REG, पंचांगp);
			पूर्ण
			val = RBIOS8(offset);
		पूर्ण
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t combios_detect_ram(काष्ठा drm_device *dev, पूर्णांक ram,
				   पूर्णांक mem_addr_mapping)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t mem_cntl;
	uपूर्णांक32_t mem_size;
	uपूर्णांक32_t addr = 0;

	mem_cntl = RREG32(RADEON_MEM_CNTL);
	अगर (mem_cntl & RV100_HALF_MODE)
		ram /= 2;
	mem_size = ram;
	mem_cntl &= ~(0xff << 8);
	mem_cntl |= (mem_addr_mapping & 0xff) << 8;
	WREG32(RADEON_MEM_CNTL, mem_cntl);
	RREG32(RADEON_MEM_CNTL);

	/* sdram reset ? */

	/* something like this????  */
	जबतक (ram--) अणु
		addr = ram * 1024 * 1024;
		/* ग_लिखो to each page */
		WREG32_IDX((addr) | RADEON_MM_APER, 0xdeadbeef);
		/* पढ़ो back and verअगरy */
		अगर (RREG32_IDX((addr) | RADEON_MM_APER) != 0xdeadbeef)
			वापस 0;
	पूर्ण

	वापस mem_size;
पूर्ण

अटल व्योम combios_ग_लिखो_ram_size(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक8_t rev;
	uपूर्णांक16_t offset;
	uपूर्णांक32_t mem_size = 0;
	uपूर्णांक32_t mem_cntl = 0;

	/* should करो something smarter here I guess... */
	अगर (rdev->flags & RADEON_IS_IGP)
		वापस;

	/* first check detected mem table */
	offset = combios_get_table_offset(dev, COMBIOS_DETECTED_MEM_TABLE);
	अगर (offset) अणु
		rev = RBIOS8(offset);
		अगर (rev < 3) अणु
			mem_cntl = RBIOS32(offset + 1);
			mem_size = RBIOS16(offset + 5);
			अगर ((rdev->family < CHIP_R200) &&
			    !ASIC_IS_RN50(rdev))
				WREG32(RADEON_MEM_CNTL, mem_cntl);
		पूर्ण
	पूर्ण

	अगर (!mem_size) अणु
		offset =
		    combios_get_table_offset(dev, COMBIOS_MEM_CONFIG_TABLE);
		अगर (offset) अणु
			rev = RBIOS8(offset - 1);
			अगर (rev < 1) अणु
				अगर ((rdev->family < CHIP_R200)
				    && !ASIC_IS_RN50(rdev)) अणु
					पूर्णांक ram = 0;
					पूर्णांक mem_addr_mapping = 0;

					जबतक (RBIOS8(offset)) अणु
						ram = RBIOS8(offset);
						mem_addr_mapping =
						    RBIOS8(offset + 1);
						अगर (mem_addr_mapping != 0x25)
							ram *= 2;
						mem_size =
						    combios_detect_ram(dev, ram,
								       mem_addr_mapping);
						अगर (mem_size)
							अवरोध;
						offset += 2;
					पूर्ण
				पूर्ण अन्यथा
					mem_size = RBIOS8(offset);
			पूर्ण अन्यथा अणु
				mem_size = RBIOS8(offset);
				mem_size *= 2;	/* convert to MB */
			पूर्ण
		पूर्ण
	पूर्ण

	mem_size *= (1024 * 1024);	/* convert to bytes */
	WREG32(RADEON_CONFIG_MEMSIZE, mem_size);
पूर्ण

व्योम radeon_combios_asic_init(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक16_t table;

	/* port hardcoded mac stuff from radeonfb */
	अगर (rdev->bios == शून्य)
		वापस;

	/* ASIC INIT 1 */
	table = combios_get_table_offset(dev, COMBIOS_ASIC_INIT_1_TABLE);
	अगर (table)
		combios_parse_mmio_table(dev, table);

	/* PLL INIT */
	table = combios_get_table_offset(dev, COMBIOS_PLL_INIT_TABLE);
	अगर (table)
		combios_parse_pll_table(dev, table);

	/* ASIC INIT 2 */
	table = combios_get_table_offset(dev, COMBIOS_ASIC_INIT_2_TABLE);
	अगर (table)
		combios_parse_mmio_table(dev, table);

	अगर (!(rdev->flags & RADEON_IS_IGP)) अणु
		/* ASIC INIT 4 */
		table =
		    combios_get_table_offset(dev, COMBIOS_ASIC_INIT_4_TABLE);
		अगर (table)
			combios_parse_mmio_table(dev, table);

		/* RAM RESET */
		table = combios_get_table_offset(dev, COMBIOS_RAM_RESET_TABLE);
		अगर (table)
			combios_parse_ram_reset_table(dev, table);

		/* ASIC INIT 3 */
		table =
		    combios_get_table_offset(dev, COMBIOS_ASIC_INIT_3_TABLE);
		अगर (table)
			combios_parse_mmio_table(dev, table);

		/* ग_लिखो CONFIG_MEMSIZE */
		combios_ग_लिखो_ram_size(dev);
	पूर्ण

	/* quirk क्रम rs4xx HP nx6125 laptop to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	अगर (rdev->family == CHIP_RS480 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x103c &&
	    rdev->pdev->subप्रणाली_device == 0x308b)
		वापस;

	/* quirk क्रम rs4xx HP dv5000 laptop to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	अगर (rdev->family == CHIP_RS480 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x103c &&
	    rdev->pdev->subप्रणाली_device == 0x30a4)
		वापस;

	/* quirk क्रम rs4xx Compaq Presario V5245EU laptop to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	अगर (rdev->family == CHIP_RS480 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x103c &&
	    rdev->pdev->subप्रणाली_device == 0x30ae)
		वापस;

	/* quirk क्रम rs4xx HP Compaq dc5750 Small Form Factor to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	अगर (rdev->family == CHIP_RS480 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x103c &&
	    rdev->pdev->subप्रणाली_device == 0x280a)
		वापस;
	/* quirk क्रम rs4xx Toshiba Sattellite L20-183 latop to make it resume
	 * - it hangs on resume inside the dynclk 1 table.
	 */
	अगर (rdev->family == CHIP_RS400 &&
	    rdev->pdev->subप्रणाली_venकरोr == 0x1179 &&
	    rdev->pdev->subप्रणाली_device == 0xff31)
	        वापस;

	/* DYN CLK 1 */
	table = combios_get_table_offset(dev, COMBIOS_DYN_CLK_1_TABLE);
	अगर (table)
		combios_parse_pll_table(dev, table);

पूर्ण

व्योम radeon_combios_initialize_bios_scratch_regs(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t bios_0_scratch, bios_6_scratch, bios_7_scratch;

	bios_0_scratch = RREG32(RADEON_BIOS_0_SCRATCH);
	bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);
	bios_7_scratch = RREG32(RADEON_BIOS_7_SCRATCH);

	/* let the bios control the backlight */
	bios_0_scratch &= ~RADEON_DRIVER_BRIGHTNESS_EN;

	/* tell the bios not to handle mode चयनing */
	bios_6_scratch |= (RADEON_DISPLAY_SWITCHING_DIS |
			   RADEON_ACC_MODE_CHANGE);

	/* tell the bios a driver is loaded */
	bios_7_scratch |= RADEON_DRV_LOADED;

	WREG32(RADEON_BIOS_0_SCRATCH, bios_0_scratch);
	WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
	WREG32(RADEON_BIOS_7_SCRATCH, bios_7_scratch);
पूर्ण

व्योम radeon_combios_output_lock(काष्ठा drm_encoder *encoder, bool lock)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t bios_6_scratch;

	bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);

	अगर (lock)
		bios_6_scratch |= RADEON_DRIVER_CRITICAL;
	अन्यथा
		bios_6_scratch &= ~RADEON_DRIVER_CRITICAL;

	WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
पूर्ण

व्योम
radeon_combios_connected_scratch_regs(काष्ठा drm_connector *connector,
				      काष्ठा drm_encoder *encoder,
				      bool connected)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector =
	    to_radeon_connector(connector);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t bios_4_scratch = RREG32(RADEON_BIOS_4_SCRATCH);
	uपूर्णांक32_t bios_5_scratch = RREG32(RADEON_BIOS_5_SCRATCH);

	अगर ((radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_TV1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("TV1 connected\n");
			/* fix me */
			bios_4_scratch |= RADEON_TV1_ATTACHED_SVIDEO;
			/*save->bios_4_scratch |= RADEON_TV1_ATTACHED_COMP; */
			bios_5_scratch |= RADEON_TV1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_TV1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("TV1 disconnected\n");
			bios_4_scratch &= ~RADEON_TV1_ATTACHED_MASK;
			bios_5_scratch &= ~RADEON_TV1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_TV1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_LCD1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("LCD1 connected\n");
			bios_4_scratch |= RADEON_LCD1_ATTACHED;
			bios_5_scratch |= RADEON_LCD1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_LCD1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("LCD1 disconnected\n");
			bios_4_scratch &= ~RADEON_LCD1_ATTACHED;
			bios_5_scratch &= ~RADEON_LCD1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_LCD1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("CRT1 connected\n");
			bios_4_scratch |= RADEON_CRT1_ATTACHED_COLOR;
			bios_5_scratch |= RADEON_CRT1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_CRT1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("CRT1 disconnected\n");
			bios_4_scratch &= ~RADEON_CRT1_ATTACHED_MASK;
			bios_5_scratch &= ~RADEON_CRT1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_CRT1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_CRT2_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("CRT2 connected\n");
			bios_4_scratch |= RADEON_CRT2_ATTACHED_COLOR;
			bios_5_scratch |= RADEON_CRT2_ON;
			bios_5_scratch |= RADEON_ACC_REQ_CRT2;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("CRT2 disconnected\n");
			bios_4_scratch &= ~RADEON_CRT2_ATTACHED_MASK;
			bios_5_scratch &= ~RADEON_CRT2_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_CRT2;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP1 connected\n");
			bios_4_scratch |= RADEON_DFP1_ATTACHED;
			bios_5_scratch |= RADEON_DFP1_ON;
			bios_5_scratch |= RADEON_ACC_REQ_DFP1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP1 disconnected\n");
			bios_4_scratch &= ~RADEON_DFP1_ATTACHED;
			bios_5_scratch &= ~RADEON_DFP1_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_DFP1;
		पूर्ण
	पूर्ण
	अगर ((radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) &&
	    (radeon_connector->devices & ATOM_DEVICE_DFP2_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP2 connected\n");
			bios_4_scratch |= RADEON_DFP2_ATTACHED;
			bios_5_scratch |= RADEON_DFP2_ON;
			bios_5_scratch |= RADEON_ACC_REQ_DFP2;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP2 disconnected\n");
			bios_4_scratch &= ~RADEON_DFP2_ATTACHED;
			bios_5_scratch &= ~RADEON_DFP2_ON;
			bios_5_scratch &= ~RADEON_ACC_REQ_DFP2;
		पूर्ण
	पूर्ण
	WREG32(RADEON_BIOS_4_SCRATCH, bios_4_scratch);
	WREG32(RADEON_BIOS_5_SCRATCH, bios_5_scratch);
पूर्ण

व्योम
radeon_combios_encoder_crtc_scratch_regs(काष्ठा drm_encoder *encoder, पूर्णांक crtc)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t bios_5_scratch = RREG32(RADEON_BIOS_5_SCRATCH);

	अगर (radeon_encoder->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
		bios_5_scratch &= ~RADEON_TV1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_TV1_CRTC_SHIFT);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) अणु
		bios_5_scratch &= ~RADEON_CRT1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_CRT1_CRTC_SHIFT);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) अणु
		bios_5_scratch &= ~RADEON_CRT2_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_CRT2_CRTC_SHIFT);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) अणु
		bios_5_scratch &= ~RADEON_LCD1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_LCD1_CRTC_SHIFT);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) अणु
		bios_5_scratch &= ~RADEON_DFP1_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_DFP1_CRTC_SHIFT);
	पूर्ण
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) अणु
		bios_5_scratch &= ~RADEON_DFP2_CRTC_MASK;
		bios_5_scratch |= (crtc << RADEON_DFP2_CRTC_SHIFT);
	पूर्ण
	WREG32(RADEON_BIOS_5_SCRATCH, bios_5_scratch);
पूर्ण

व्योम
radeon_combios_encoder_dpms_scratch_regs(काष्ठा drm_encoder *encoder, bool on)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t bios_6_scratch = RREG32(RADEON_BIOS_6_SCRATCH);

	अगर (radeon_encoder->devices & (ATOM_DEVICE_TV_SUPPORT)) अणु
		अगर (on)
			bios_6_scratch |= RADEON_TV_DPMS_ON;
		अन्यथा
			bios_6_scratch &= ~RADEON_TV_DPMS_ON;
	पूर्ण
	अगर (radeon_encoder->devices & (ATOM_DEVICE_CRT_SUPPORT)) अणु
		अगर (on)
			bios_6_scratch |= RADEON_CRT_DPMS_ON;
		अन्यथा
			bios_6_scratch &= ~RADEON_CRT_DPMS_ON;
	पूर्ण
	अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
		अगर (on)
			bios_6_scratch |= RADEON_LCD_DPMS_ON;
		अन्यथा
			bios_6_scratch &= ~RADEON_LCD_DPMS_ON;
	पूर्ण
	अगर (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
		अगर (on)
			bios_6_scratch |= RADEON_DFP_DPMS_ON;
		अन्यथा
			bios_6_scratch &= ~RADEON_DFP_DPMS_ON;
	पूर्ण
	WREG32(RADEON_BIOS_6_SCRATCH, bios_6_scratch);
पूर्ण
