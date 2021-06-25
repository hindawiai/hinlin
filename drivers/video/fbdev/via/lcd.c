<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#समावेश <linux/via-core.h>
#समावेश <linux/via_i2c.h>
#समावेश "global.h"

#घोषणा viafb_compact_res(x, y) (((x)<<16)|(y))

/* CLE266 Software Power Sequence */
/* अणुMaskपूर्ण, अणुDataपूर्ण, अणुDelayपूर्ण */
अटल स्थिर पूर्णांक PowerSequenceOn[3][3] = अणु
	अणु0x10, 0x08, 0x06पूर्ण, अणु0x10, 0x08, 0x06पूर्ण,	अणु0x19, 0x1FE, 0x01पूर्ण
पूर्ण;
अटल स्थिर पूर्णांक PowerSequenceOff[3][3] = अणु
	अणु0x06, 0x08, 0x10पूर्ण, अणु0x00, 0x00, 0x00पूर्ण,	अणु0xD2, 0x19, 0x01पूर्ण
पूर्ण;

अटल काष्ठा _lcd_scaling_factor lcd_scaling_factor = अणु
	/* LCD Horizontal Scaling Factor Register */
	अणुLCD_HOR_SCALING_FACTOR_REG_NUM,
	 अणुअणुCR9F, 0, 1पूर्ण, अणुCR77, 0, 7पूर्ण, अणुCR79, 4, 5पूर्ण पूर्ण पूर्ण,
	/* LCD Vertical Scaling Factor Register */
	अणुLCD_VER_SCALING_FACTOR_REG_NUM,
	 अणुअणुCR79, 3, 3पूर्ण, अणुCR78, 0, 7पूर्ण, अणुCR79, 6, 7पूर्ण पूर्ण पूर्ण
पूर्ण;
अटल काष्ठा _lcd_scaling_factor lcd_scaling_factor_CLE = अणु
	/* LCD Horizontal Scaling Factor Register */
	अणुLCD_HOR_SCALING_FACTOR_REG_NUM_CLE, अणुअणुCR77, 0, 7पूर्ण, अणुCR79, 4, 5पूर्ण पूर्ण पूर्ण,
	/* LCD Vertical Scaling Factor Register */
	अणुLCD_VER_SCALING_FACTOR_REG_NUM_CLE, अणुअणुCR78, 0, 7पूर्ण, अणुCR79, 6, 7पूर्ण पूर्ण पूर्ण
पूर्ण;

अटल bool lvds_identअगरy_पूर्णांकegratedlvds(व्योम);
अटल व्योम fp_id_to_vindex(पूर्णांक panel_id);
अटल पूर्णांक lvds_रेजिस्टर_पढ़ो(पूर्णांक index);
अटल व्योम load_lcd_scaling(पूर्णांक set_hres, पूर्णांक set_vres, पूर्णांक panel_hres,
		      पूर्णांक panel_vres);
अटल व्योम lcd_patch_skew_dvp0(काष्ठा lvds_setting_inक्रमmation
			 *plvds_setting_info,
			 काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);
अटल व्योम lcd_patch_skew_dvp1(काष्ठा lvds_setting_inक्रमmation
			 *plvds_setting_info,
			 काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);
अटल व्योम lcd_patch_skew(काष्ठा lvds_setting_inक्रमmation
	*plvds_setting_info, काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);

अटल व्योम पूर्णांकegrated_lvds_disable(काष्ठा lvds_setting_inक्रमmation
			     *plvds_setting_info,
			     काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);
अटल व्योम पूर्णांकegrated_lvds_enable(काष्ठा lvds_setting_inक्रमmation
			    *plvds_setting_info,
			    काष्ठा lvds_chip_inक्रमmation *plvds_chip_info);
अटल व्योम lcd_घातersequence_off(व्योम);
अटल व्योम lcd_घातersequence_on(व्योम);
अटल व्योम fill_lcd_क्रमmat(व्योम);
अटल व्योम check_diport_of_पूर्णांकegrated_lvds(
	काष्ठा lvds_chip_inक्रमmation *plvds_chip_info,
				     काष्ठा lvds_setting_inक्रमmation
				     *plvds_setting_info);

अटल अंतरभूत bool check_lvds_chip(पूर्णांक device_id_subaddr, पूर्णांक device_id)
अणु
	वापस lvds_रेजिस्टर_पढ़ो(device_id_subaddr) == device_id;
पूर्ण

व्योम viafb_init_lcd_size(व्योम)
अणु
	DEBUG_MSG(KERN_INFO "viafb_init_lcd_size()\n");

	fp_id_to_vindex(viafb_lcd_panel_id);
	viaparinfo->lvds_setting_info2->lcd_panel_hres =
		viaparinfo->lvds_setting_info->lcd_panel_hres;
	viaparinfo->lvds_setting_info2->lcd_panel_vres =
		viaparinfo->lvds_setting_info->lcd_panel_vres;
	viaparinfo->lvds_setting_info2->device_lcd_dualedge =
	    viaparinfo->lvds_setting_info->device_lcd_dualedge;
	viaparinfo->lvds_setting_info2->LCDDithering =
		viaparinfo->lvds_setting_info->LCDDithering;
पूर्ण

अटल bool lvds_identअगरy_पूर्णांकegratedlvds(व्योम)
अणु
	अगर (viafb_display_hardware_layout == HW_LAYOUT_LCD_EXTERNAL_LCD2) अणु
		/* Two dual channel LCD (Internal LVDS + External LVDS): */
		/* If we have an बाह्यal LVDS, such as VT1636, we should
		   have its chip ID alपढ़ोy. */
		अगर (viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) अणु
			viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name =
			    INTEGRATED_LVDS;
			DEBUG_MSG(KERN_INFO "Support two dual channel LVDS! "
				  "(Internal LVDS + External LVDS)\n");
		पूर्ण अन्यथा अणु
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			    INTEGRATED_LVDS;
			DEBUG_MSG(KERN_INFO "Not found external LVDS, "
				  "so can't support two dual channel LVDS!\n");
		पूर्ण
	पूर्ण अन्यथा अगर (viafb_display_hardware_layout == HW_LAYOUT_LCD1_LCD2) अणु
		/* Two single channel LCD (Internal LVDS + Internal LVDS): */
		viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
		INTEGRATED_LVDS;
		viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name =
			INTEGRATED_LVDS;
		DEBUG_MSG(KERN_INFO "Support two single channel LVDS! "
			  "(Internal LVDS + Internal LVDS)\n");
	पूर्ण अन्यथा अगर (viafb_display_hardware_layout != HW_LAYOUT_DVI_ONLY) अणु
		/* If we have found बाह्यal LVDS, just use it,
		   otherwise, we will use पूर्णांकernal LVDS as शेष. */
		अगर (!viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) अणु
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			    INTEGRATED_LVDS;
			DEBUG_MSG(KERN_INFO "Found Integrated LVDS!\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
			NON_LVDS_TRANSMITTER;
		DEBUG_MSG(KERN_INFO "Do not support LVDS!\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool viafb_lvds_trयंत्रitter_identअगरy(व्योम)
अणु
	अगर (viafb_lvds_identअगरy_vt1636(VIA_PORT_31)) अणु
		viaparinfo->chip_info->lvds_chip_info.i2c_port = VIA_PORT_31;
		DEBUG_MSG(KERN_INFO
			  "Found VIA VT1636 LVDS on port i2c 0x31\n");
	पूर्ण अन्यथा अणु
		अगर (viafb_lvds_identअगरy_vt1636(VIA_PORT_2C)) अणु
			viaparinfo->chip_info->lvds_chip_info.i2c_port =
				VIA_PORT_2C;
			DEBUG_MSG(KERN_INFO
				  "Found VIA VT1636 LVDS on port gpio 0x2c\n");
		पूर्ण
	पूर्ण

	अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700)
		lvds_identअगरy_पूर्णांकegratedlvds();

	अगर (viaparinfo->chip_info->lvds_chip_info.lvds_chip_name)
		वापस true;
	/* Check क्रम VT1631: */
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_name = VT1631_LVDS;
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_slave_addr =
		VT1631_LVDS_I2C_ADDR;

	अगर (check_lvds_chip(VT1631_DEVICE_ID_REG, VT1631_DEVICE_ID)) अणु
		DEBUG_MSG(KERN_INFO "\n VT1631 LVDS ! \n");
		DEBUG_MSG(KERN_INFO "\n %2d",
			  viaparinfo->chip_info->lvds_chip_info.lvds_chip_name);
		DEBUG_MSG(KERN_INFO "\n %2d",
			  viaparinfo->chip_info->lvds_chip_info.lvds_chip_name);
		वापस true;
	पूर्ण

	viaparinfo->chip_info->lvds_chip_info.lvds_chip_name =
		NON_LVDS_TRANSMITTER;
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_slave_addr =
		VT1631_LVDS_I2C_ADDR;
	वापस false;
पूर्ण

अटल व्योम fp_id_to_vindex(पूर्णांक panel_id)
अणु
	DEBUG_MSG(KERN_INFO "fp_get_panel_id()\n");

	अगर (panel_id > LCD_PANEL_ID_MAXIMUM)
		viafb_lcd_panel_id = panel_id =
		viafb_पढ़ो_reg(VIACR, CR3F) & 0x0F;

	चयन (panel_id) अणु
	हाल 0x0:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 640;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 480;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x1:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 800;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 600;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x2:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1024;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x3:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1280;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x4:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1280;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 1024;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x5:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1400;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 1050;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x6:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1600;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 1200;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x8:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 800;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 480;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x9:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1024;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0xA:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1024;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0xB:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1024;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0xC:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1280;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0xD:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1280;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 1024;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0xE:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1400;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 1050;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0xF:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1600;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 1200;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0x10:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1366;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0x11:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1024;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 600;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x12:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1280;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x13:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1280;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 800;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x14:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1360;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0x15:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1280;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 768;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 1;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	हाल 0x16:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 480;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 640;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
		अवरोध;
	हाल 0x17:
		/* OLPC XO-1.5 panel */
		viaparinfo->lvds_setting_info->lcd_panel_hres = 1200;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 900;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 0;
		अवरोध;
	शेष:
		viaparinfo->lvds_setting_info->lcd_panel_hres = 800;
		viaparinfo->lvds_setting_info->lcd_panel_vres = 600;
		viaparinfo->lvds_setting_info->device_lcd_dualedge = 0;
		viaparinfo->lvds_setting_info->LCDDithering = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक lvds_रेजिस्टर_पढ़ो(पूर्णांक index)
अणु
	u8 data;

	viafb_i2c_पढ़ोbyte(VIA_PORT_2C,
			(u8) viaparinfo->chip_info->lvds_chip_info.lvds_chip_slave_addr,
			(u8) index, &data);
	वापस data;
पूर्ण

अटल व्योम load_lcd_scaling(पूर्णांक set_hres, पूर्णांक set_vres, पूर्णांक panel_hres,
		      पूर्णांक panel_vres)
अणु
	पूर्णांक reg_value = 0;
	पूर्णांक viafb_load_reg_num;
	काष्ठा io_रेजिस्टर *reg = शून्य;

	DEBUG_MSG(KERN_INFO "load_lcd_scaling()!!\n");

	/* LCD Scaling Enable */
	viafb_ग_लिखो_reg_mask(CR79, VIACR, 0x07, BIT0 + BIT1 + BIT2);

	/* Check अगर expansion क्रम horizontal */
	अगर (set_hres < panel_hres) अणु
		/* Load Horizontal Scaling Factor */
		चयन (viaparinfo->chip_info->gfx_chip_name) अणु
		हाल UNICHROME_CLE266:
		हाल UNICHROME_K400:
			reg_value =
			    CLE266_LCD_HOR_SCF_FORMULA(set_hres, panel_hres);
			viafb_load_reg_num =
			    lcd_scaling_factor_CLE.lcd_hor_scaling_factor.
			    reg_num;
			reg = lcd_scaling_factor_CLE.lcd_hor_scaling_factor.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
			अवरोध;
		हाल UNICHROME_K800:
		हाल UNICHROME_PM800:
		हाल UNICHROME_CN700:
		हाल UNICHROME_CX700:
		हाल UNICHROME_K8M890:
		हाल UNICHROME_P4M890:
		हाल UNICHROME_P4M900:
		हाल UNICHROME_CN750:
		हाल UNICHROME_VX800:
		हाल UNICHROME_VX855:
		हाल UNICHROME_VX900:
			reg_value =
			    K800_LCD_HOR_SCF_FORMULA(set_hres, panel_hres);
			/* Horizontal scaling enabled */
			viafb_ग_लिखो_reg_mask(CRA2, VIACR, 0xC0, BIT7 + BIT6);
			viafb_load_reg_num =
			    lcd_scaling_factor.lcd_hor_scaling_factor.reg_num;
			reg = lcd_scaling_factor.lcd_hor_scaling_factor.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
			अवरोध;
		पूर्ण

		DEBUG_MSG(KERN_INFO "Horizontal Scaling value = %d", reg_value);
	पूर्ण अन्यथा अणु
		/* Horizontal scaling disabled */
		viafb_ग_लिखो_reg_mask(CRA2, VIACR, 0x00, BIT7);
	पूर्ण

	/* Check अगर expansion क्रम vertical */
	अगर (set_vres < panel_vres) अणु
		/* Load Vertical Scaling Factor */
		चयन (viaparinfo->chip_info->gfx_chip_name) अणु
		हाल UNICHROME_CLE266:
		हाल UNICHROME_K400:
			reg_value =
			    CLE266_LCD_VER_SCF_FORMULA(set_vres, panel_vres);
			viafb_load_reg_num =
			    lcd_scaling_factor_CLE.lcd_ver_scaling_factor.
			    reg_num;
			reg = lcd_scaling_factor_CLE.lcd_ver_scaling_factor.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
			अवरोध;
		हाल UNICHROME_K800:
		हाल UNICHROME_PM800:
		हाल UNICHROME_CN700:
		हाल UNICHROME_CX700:
		हाल UNICHROME_K8M890:
		हाल UNICHROME_P4M890:
		हाल UNICHROME_P4M900:
		हाल UNICHROME_CN750:
		हाल UNICHROME_VX800:
		हाल UNICHROME_VX855:
		हाल UNICHROME_VX900:
			reg_value =
			    K800_LCD_VER_SCF_FORMULA(set_vres, panel_vres);
			/* Vertical scaling enabled */
			viafb_ग_लिखो_reg_mask(CRA2, VIACR, 0x08, BIT3);
			viafb_load_reg_num =
			    lcd_scaling_factor.lcd_ver_scaling_factor.reg_num;
			reg = lcd_scaling_factor.lcd_ver_scaling_factor.reg;
			viafb_load_reg(reg_value,
				viafb_load_reg_num, reg, VIACR);
			अवरोध;
		पूर्ण

		DEBUG_MSG(KERN_INFO "Vertical Scaling value = %d", reg_value);
	पूर्ण अन्यथा अणु
		/* Vertical scaling disabled */
		viafb_ग_लिखो_reg_mask(CRA2, VIACR, 0x00, BIT3);
	पूर्ण
पूर्ण

अटल व्योम via_pitch_alignment_patch_lcd(पूर्णांक iga_path, पूर्णांक hres, पूर्णांक bpp)
अणु
	अचिन्हित अक्षर cr13, cr35, cr65, cr66, cr67;
	अचिन्हित दीर्घ dwScreenPitch = 0;
	अचिन्हित दीर्घ dwPitch;

	dwPitch = hres * (bpp >> 3);
	अगर (dwPitch & 0x1F) अणु
		dwScreenPitch = ((dwPitch + 31) & ~31) >> 3;
		अगर (iga_path == IGA2) अणु
			अगर (bpp > 8) अणु
				cr66 = (अचिन्हित अक्षर)(dwScreenPitch & 0xFF);
				viafb_ग_लिखो_reg(CR66, VIACR, cr66);
				cr67 = viafb_पढ़ो_reg(VIACR, CR67) & 0xFC;
				cr67 |=
				    (अचिन्हित
				     अक्षर)((dwScreenPitch & 0x300) >> 8);
				viafb_ग_लिखो_reg(CR67, VIACR, cr67);
			पूर्ण

			/* Fetch Count */
			cr67 = viafb_पढ़ो_reg(VIACR, CR67) & 0xF3;
			cr67 |= (अचिन्हित अक्षर)((dwScreenPitch & 0x600) >> 7);
			viafb_ग_लिखो_reg(CR67, VIACR, cr67);
			cr65 = (अचिन्हित अक्षर)((dwScreenPitch >> 1) & 0xFF);
			cr65 += 2;
			viafb_ग_लिखो_reg(CR65, VIACR, cr65);
		पूर्ण अन्यथा अणु
			अगर (bpp > 8) अणु
				cr13 = (अचिन्हित अक्षर)(dwScreenPitch & 0xFF);
				viafb_ग_लिखो_reg(CR13, VIACR, cr13);
				cr35 = viafb_पढ़ो_reg(VIACR, CR35) & 0x1F;
				cr35 |=
				    (अचिन्हित
				     अक्षर)((dwScreenPitch & 0x700) >> 3);
				viafb_ग_लिखो_reg(CR35, VIACR, cr35);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
अटल व्योम lcd_patch_skew_dvp0(काष्ठा lvds_setting_inक्रमmation
			 *plvds_setting_info,
			 काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	अगर (VT1636_LVDS == plvds_chip_info->lvds_chip_name) अणु
		चयन (viaparinfo->chip_info->gfx_chip_name) अणु
		हाल UNICHROME_P4M900:
			viafb_vt1636_patch_skew_on_vt3364(plvds_setting_info,
						    plvds_chip_info);
			अवरोध;
		हाल UNICHROME_P4M890:
			viafb_vt1636_patch_skew_on_vt3327(plvds_setting_info,
						    plvds_chip_info);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
अटल व्योम lcd_patch_skew_dvp1(काष्ठा lvds_setting_inक्रमmation
			 *plvds_setting_info,
			 काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	अगर (VT1636_LVDS == plvds_chip_info->lvds_chip_name) अणु
		चयन (viaparinfo->chip_info->gfx_chip_name) अणु
		हाल UNICHROME_CX700:
			viafb_vt1636_patch_skew_on_vt3324(plvds_setting_info,
						    plvds_chip_info);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
अटल व्योम lcd_patch_skew(काष्ठा lvds_setting_inक्रमmation
	*plvds_setting_info, काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	DEBUG_MSG(KERN_INFO "lcd_patch_skew\n");
	चयन (plvds_chip_info->output_पूर्णांकerface) अणु
	हाल INTERFACE_DVP0:
		lcd_patch_skew_dvp0(plvds_setting_info, plvds_chip_info);
		अवरोध;
	हाल INTERFACE_DVP1:
		lcd_patch_skew_dvp1(plvds_setting_info, plvds_chip_info);
		अवरोध;
	हाल INTERFACE_DFP_LOW:
		अगर (UNICHROME_P4M900 == viaparinfo->chip_info->gfx_chip_name) अणु
			viafb_ग_लिखो_reg_mask(CR99, VIACR, 0x08,
				       BIT0 + BIT1 + BIT2 + BIT3);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/* LCD Set Mode */
व्योम viafb_lcd_set_mode(स्थिर काष्ठा fb_var_screeninfo *var, u16 cxres,
	u16 cyres, काष्ठा lvds_setting_inक्रमmation *plvds_setting_info,
	काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	पूर्णांक set_iga = plvds_setting_info->iga_path;
	पूर्णांक mode_bpp = var->bits_per_pixel;
	पूर्णांक set_hres = cxres ? cxres : var->xres;
	पूर्णांक set_vres = cyres ? cyres : var->yres;
	पूर्णांक panel_hres = plvds_setting_info->lcd_panel_hres;
	पूर्णांक panel_vres = plvds_setting_info->lcd_panel_vres;
	u32 घड़ी;
	काष्ठा via_display_timing timing;
	काष्ठा fb_var_screeninfo panel_var;
	स्थिर काष्ठा fb_videomode *panel_crt_table;

	DEBUG_MSG(KERN_INFO "viafb_lcd_set_mode!!\n");
	/* Get panel table Poपूर्णांकer */
	panel_crt_table = viafb_get_best_mode(panel_hres, panel_vres, 60);
	viafb_fill_var_timing_info(&panel_var, panel_crt_table);
	DEBUG_MSG(KERN_INFO "bellow viafb_lcd_set_mode!!\n");
	अगर (VT1636_LVDS == plvds_chip_info->lvds_chip_name)
		viafb_init_lvds_vt1636(plvds_setting_info, plvds_chip_info);
	घड़ी = PICOS2KHZ(panel_crt_table->pixघड़ी) * 1000;
	plvds_setting_info->vclk = घड़ी;

	अगर (set_iga == IGA2 && (set_hres < panel_hres || set_vres < panel_vres)
		&& plvds_setting_info->display_method == LCD_EXPANDSION) अणु
		timing = var_to_timing(&panel_var, panel_hres, panel_vres);
		load_lcd_scaling(set_hres, set_vres, panel_hres, panel_vres);
	पूर्ण अन्यथा अणु
		timing = var_to_timing(&panel_var, set_hres, set_vres);
		अगर (set_iga == IGA2)
			/* disable scaling */
			via_ग_लिखो_reg_mask(VIACR, 0x79, 0x00,
				BIT0 + BIT1 + BIT2);
	पूर्ण

	अगर (set_iga == IGA1)
		via_set_primary_timing(&timing);
	अन्यथा अगर (set_iga == IGA2)
		via_set_secondary_timing(&timing);

	/* Fetch count क्रम IGA2 only */
	viafb_load_fetch_count_reg(set_hres, mode_bpp / 8, set_iga);

	अगर ((viaparinfo->chip_info->gfx_chip_name != UNICHROME_CLE266)
		&& (viaparinfo->chip_info->gfx_chip_name != UNICHROME_K400))
		viafb_load_FIFO_reg(set_iga, set_hres, set_vres);

	fill_lcd_क्रमmat();
	viafb_set_vघड़ी(घड़ी, set_iga);
	lcd_patch_skew(plvds_setting_info, plvds_chip_info);

	/* If K8M800, enable LCD Prefetch Mode. */
	अगर ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_K800)
	    || (UNICHROME_K8M890 == viaparinfo->chip_info->gfx_chip_name))
		viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x01, BIT0);

	/* Patch क्रम non 32bit alignment mode */
	via_pitch_alignment_patch_lcd(plvds_setting_info->iga_path, set_hres,
		var->bits_per_pixel);
पूर्ण

अटल व्योम पूर्णांकegrated_lvds_disable(काष्ठा lvds_setting_inक्रमmation
			     *plvds_setting_info,
			     काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	bool turn_off_first_घातersequence = false;
	bool turn_off_second_घातersequence = false;
	अगर (INTERFACE_LVDS0LVDS1 == plvds_chip_info->output_पूर्णांकerface)
		turn_off_first_घातersequence = true;
	अगर (INTERFACE_LVDS0 == plvds_chip_info->output_पूर्णांकerface)
		turn_off_first_घातersequence = true;
	अगर (INTERFACE_LVDS1 == plvds_chip_info->output_पूर्णांकerface)
		turn_off_second_घातersequence = true;
	अगर (turn_off_second_घातersequence) अणु
		/* Use second घातer sequence control: */

		/* Turn off घातer sequence. */
		viafb_ग_लिखो_reg_mask(CRD4, VIACR, 0, BIT1);

		/* Turn off back light. */
		viafb_ग_लिखो_reg_mask(CRD3, VIACR, 0xC0, BIT6 + BIT7);
	पूर्ण
	अगर (turn_off_first_घातersequence) अणु
		/* Use first घातer sequence control: */

		/* Turn off घातer sequence. */
		viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0, BIT3);

		/* Turn off back light. */
		viafb_ग_लिखो_reg_mask(CR91, VIACR, 0xC0, BIT6 + BIT7);
	पूर्ण

	/* Power off LVDS channel. */
	चयन (plvds_chip_info->output_पूर्णांकerface) अणु
	हाल INTERFACE_LVDS0:
		अणु
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x80, BIT7);
			अवरोध;
		पूर्ण

	हाल INTERFACE_LVDS1:
		अणु
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x40, BIT6);
			अवरोध;
		पूर्ण

	हाल INTERFACE_LVDS0LVDS1:
		अणु
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0xC0, BIT6 + BIT7);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकegrated_lvds_enable(काष्ठा lvds_setting_inक्रमmation
			    *plvds_setting_info,
			    काष्ठा lvds_chip_inक्रमmation *plvds_chip_info)
अणु
	DEBUG_MSG(KERN_INFO "integrated_lvds_enable, out_interface:%d\n",
		  plvds_chip_info->output_पूर्णांकerface);
	अगर (plvds_setting_info->lcd_mode == LCD_SPWG)
		viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x00, BIT0 + BIT1);
	अन्यथा
		viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0x03, BIT0 + BIT1);

	चयन (plvds_chip_info->output_पूर्णांकerface) अणु
	हाल INTERFACE_LVDS0LVDS1:
	हाल INTERFACE_LVDS0:
		/* Use first घातer sequence control: */
		/* Use hardware control घातer sequence. */
		viafb_ग_लिखो_reg_mask(CR91, VIACR, 0, BIT0);
		/* Turn on back light. */
		viafb_ग_लिखो_reg_mask(CR91, VIACR, 0, BIT6 + BIT7);
		/* Turn on hardware घातer sequence. */
		viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x08, BIT3);
		अवरोध;
	हाल INTERFACE_LVDS1:
		/* Use second घातer sequence control: */
		/* Use hardware control घातer sequence. */
		viafb_ग_लिखो_reg_mask(CRD3, VIACR, 0, BIT0);
		/* Turn on back light. */
		viafb_ग_लिखो_reg_mask(CRD3, VIACR, 0, BIT6 + BIT7);
		/* Turn on hardware घातer sequence. */
		viafb_ग_लिखो_reg_mask(CRD4, VIACR, 0x02, BIT1);
		अवरोध;
	पूर्ण

	/* Power on LVDS channel. */
	चयन (plvds_chip_info->output_पूर्णांकerface) अणु
	हाल INTERFACE_LVDS0:
		अणु
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0, BIT7);
			अवरोध;
		पूर्ण

	हाल INTERFACE_LVDS1:
		अणु
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0, BIT6);
			अवरोध;
		पूर्ण

	हाल INTERFACE_LVDS0LVDS1:
		अणु
			viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0, BIT6 + BIT7);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम viafb_lcd_disable(व्योम)
अणु

	अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) अणु
		lcd_घातersequence_off();
		/* DI1 pad off */
		viafb_ग_लिखो_reg_mask(SR1E, VIASR, 0x00, 0x30);
	पूर्ण अन्यथा अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) अणु
		अगर (viafb_LCD2_ON
		    && (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name))
			पूर्णांकegrated_lvds_disable(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info2);
		अगर (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name)
			पूर्णांकegrated_lvds_disable(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
		अगर (VT1636_LVDS == viaparinfo->chip_info->
			lvds_chip_info.lvds_chip_name)
			viafb_disable_lvds_vt1636(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
	पूर्ण अन्यथा अगर (VT1636_LVDS ==
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) अणु
		viafb_disable_lvds_vt1636(viaparinfo->lvds_setting_info,
				    &viaparinfo->chip_info->lvds_chip_info);
	पूर्ण अन्यथा अणु
		/* Backlight off           */
		viafb_ग_लिखो_reg_mask(SR3D, VIASR, 0x00, 0x20);
		/* 24 bit DI data paht off */
		viafb_ग_लिखो_reg_mask(CR91, VIACR, 0x80, 0x80);
	पूर्ण

	/* Disable expansion bit   */
	viafb_ग_लिखो_reg_mask(CR79, VIACR, 0x00, 0x01);
	/* Simultaneout disabled   */
	viafb_ग_लिखो_reg_mask(CR6B, VIACR, 0x00, 0x08);
पूर्ण

अटल व्योम set_lcd_output_path(पूर्णांक set_iga, पूर्णांक output_पूर्णांकerface)
अणु
	चयन (output_पूर्णांकerface) अणु
	हाल INTERFACE_DFP:
		अगर ((UNICHROME_K8M890 == viaparinfo->chip_info->gfx_chip_name)
		    || (UNICHROME_P4M890 ==
		    viaparinfo->chip_info->gfx_chip_name))
			viafb_ग_लिखो_reg_mask(CR97, VIACR, 0x84,
				       BIT7 + BIT2 + BIT1 + BIT0);
		fallthrough;
	हाल INTERFACE_DVP0:
	हाल INTERFACE_DVP1:
	हाल INTERFACE_DFP_HIGH:
	हाल INTERFACE_DFP_LOW:
		अगर (set_iga == IGA2)
			viafb_ग_लिखो_reg(CR91, VIACR, 0x00);
		अवरोध;
	पूर्ण
पूर्ण

व्योम viafb_lcd_enable(व्योम)
अणु
	viafb_ग_लिखो_reg_mask(CR6B, VIACR, 0x00, BIT3);
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x08, BIT3);
	set_lcd_output_path(viaparinfo->lvds_setting_info->iga_path,
		viaparinfo->chip_info->lvds_chip_info.output_पूर्णांकerface);
	अगर (viafb_LCD2_ON)
		set_lcd_output_path(viaparinfo->lvds_setting_info2->iga_path,
			viaparinfo->chip_info->
			lvds_chip_info2.output_पूर्णांकerface);

	अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) अणु
		/* DI1 pad on */
		viafb_ग_लिखो_reg_mask(SR1E, VIASR, 0x30, 0x30);
		lcd_घातersequence_on();
	पूर्ण अन्यथा अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) अणु
		अगर (viafb_LCD2_ON && (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info2.lvds_chip_name))
			पूर्णांकegrated_lvds_enable(viaparinfo->lvds_setting_info2, \
				&viaparinfo->chip_info->lvds_chip_info2);
		अगर (INTEGRATED_LVDS ==
			viaparinfo->chip_info->lvds_chip_info.lvds_chip_name)
			पूर्णांकegrated_lvds_enable(viaparinfo->lvds_setting_info,
				&viaparinfo->chip_info->lvds_chip_info);
		अगर (VT1636_LVDS == viaparinfo->chip_info->
			lvds_chip_info.lvds_chip_name)
			viafb_enable_lvds_vt1636(viaparinfo->
			lvds_setting_info, &viaparinfo->chip_info->
			lvds_chip_info);
	पूर्ण अन्यथा अगर (VT1636_LVDS ==
	viaparinfo->chip_info->lvds_chip_info.lvds_chip_name) अणु
		viafb_enable_lvds_vt1636(viaparinfo->lvds_setting_info,
				   &viaparinfo->chip_info->lvds_chip_info);
	पूर्ण अन्यथा अणु
		/* Backlight on            */
		viafb_ग_लिखो_reg_mask(SR3D, VIASR, 0x20, 0x20);
		/* 24 bit DI data paht on  */
		viafb_ग_लिखो_reg_mask(CR91, VIACR, 0x00, 0x80);
		/* LCD enabled             */
		viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x48, 0x48);
	पूर्ण
पूर्ण

अटल व्योम lcd_घातersequence_off(व्योम)
अणु
	पूर्णांक i, mask, data;

	/* Software control घातer sequence */
	viafb_ग_लिखो_reg_mask(CR91, VIACR, 0x11, 0x11);

	क्रम (i = 0; i < 3; i++) अणु
		mask = PowerSequenceOff[0][i];
		data = PowerSequenceOff[1][i] & mask;
		viafb_ग_लिखो_reg_mask(CR91, VIACR, (u8) data, (u8) mask);
		udelay(PowerSequenceOff[2][i]);
	पूर्ण

	/* Disable LCD */
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x00, 0x08);
पूर्ण

अटल व्योम lcd_घातersequence_on(व्योम)
अणु
	पूर्णांक i, mask, data;

	/* Software control घातer sequence */
	viafb_ग_लिखो_reg_mask(CR91, VIACR, 0x11, 0x11);

	/* Enable LCD */
	viafb_ग_लिखो_reg_mask(CR6A, VIACR, 0x08, 0x08);

	क्रम (i = 0; i < 3; i++) अणु
		mask = PowerSequenceOn[0][i];
		data = PowerSequenceOn[1][i] & mask;
		viafb_ग_लिखो_reg_mask(CR91, VIACR, (u8) data, (u8) mask);
		udelay(PowerSequenceOn[2][i]);
	पूर्ण

	udelay(1);
पूर्ण

अटल व्योम fill_lcd_क्रमmat(व्योम)
अणु
	u8 bdithering = 0, bdual = 0;

	अगर (viaparinfo->lvds_setting_info->device_lcd_dualedge)
		bdual = BIT4;
	अगर (viaparinfo->lvds_setting_info->LCDDithering)
		bdithering = BIT0;
	/* Dual & Dithering */
	viafb_ग_लिखो_reg_mask(CR88, VIACR, (bdithering | bdual), BIT4 + BIT0);
पूर्ण

अटल व्योम check_diport_of_पूर्णांकegrated_lvds(
	काष्ठा lvds_chip_inक्रमmation *plvds_chip_info,
				     काष्ठा lvds_setting_inक्रमmation
				     *plvds_setting_info)
अणु
	/* Determine LCD DI Port by hardware layout. */
	चयन (viafb_display_hardware_layout) अणु
	हाल HW_LAYOUT_LCD_ONLY:
		अणु
			अगर (plvds_setting_info->device_lcd_dualedge) अणु
				plvds_chip_info->output_पूर्णांकerface =
				    INTERFACE_LVDS0LVDS1;
			पूर्ण अन्यथा अणु
				plvds_chip_info->output_पूर्णांकerface =
				    INTERFACE_LVDS0;
			पूर्ण

			अवरोध;
		पूर्ण

	हाल HW_LAYOUT_DVI_ONLY:
		अणु
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_NONE;
			अवरोध;
		पूर्ण

	हाल HW_LAYOUT_LCD1_LCD2:
	हाल HW_LAYOUT_LCD_EXTERNAL_LCD2:
		अणु
			plvds_chip_info->output_पूर्णांकerface =
			    INTERFACE_LVDS0LVDS1;
			अवरोध;
		पूर्ण

	हाल HW_LAYOUT_LCD_DVI:
		अणु
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_LVDS1;
			अवरोध;
		पूर्ण

	शेष:
		अणु
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_LVDS1;
			अवरोध;
		पूर्ण
	पूर्ण

	DEBUG_MSG(KERN_INFO
		  "Display Hardware Layout: 0x%x, LCD DI Port: 0x%x\n",
		  viafb_display_hardware_layout,
		  plvds_chip_info->output_पूर्णांकerface);
पूर्ण

व्योम viafb_init_lvds_output_पूर्णांकerface(काष्ठा lvds_chip_inक्रमmation
				*plvds_chip_info,
				काष्ठा lvds_setting_inक्रमmation
				*plvds_setting_info)
अणु
	अगर (INTERFACE_NONE != plvds_chip_info->output_पूर्णांकerface) अणु
		/*Do nothing, lcd port is specअगरied by module parameter */
		वापस;
	पूर्ण

	चयन (plvds_chip_info->lvds_chip_name) अणु

	हाल VT1636_LVDS:
		चयन (viaparinfo->chip_info->gfx_chip_name) अणु
		हाल UNICHROME_CX700:
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_DVP1;
			अवरोध;
		हाल UNICHROME_CN700:
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_DFP_LOW;
			अवरोध;
		शेष:
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_DVP0;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल INTEGRATED_LVDS:
		check_diport_of_पूर्णांकegrated_lvds(plvds_chip_info,
						plvds_setting_info);
		अवरोध;

	शेष:
		चयन (viaparinfo->chip_info->gfx_chip_name) अणु
		हाल UNICHROME_K8M890:
		हाल UNICHROME_P4M900:
		हाल UNICHROME_P4M890:
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_DFP_LOW;
			अवरोध;
		शेष:
			plvds_chip_info->output_पूर्णांकerface = INTERFACE_DFP;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

bool viafb_lcd_get_mobile_state(bool *mobile)
अणु
	अचिन्हित अक्षर __iomem *romptr, *tableptr, *biosptr;
	u8 core_base;
	/* Rom address */
	स्थिर u32 romaddr = 0x000C0000;
	u16 start_pattern;

	biosptr = ioremap(romaddr, 0x10000);
	start_pattern = पढ़ोw(biosptr);

	/* Compare pattern */
	अगर (start_pattern == 0xAA55) अणु
		/* Get the start of Table */
		/* 0x1B means BIOS offset position */
		romptr = biosptr + 0x1B;
		tableptr = biosptr + पढ़ोw(romptr);

		/* Get the start of biosver काष्ठाure */
		/* 18 means BIOS version position. */
		romptr = tableptr + 18;
		romptr = biosptr + पढ़ोw(romptr);

		/* The offset should be 44, but the
		   actual image is less three अक्षर. */
		/* pRom += 44; */
		romptr += 41;

		core_base = पढ़ोb(romptr);

		अगर (core_base & 0x8)
			*mobile = false;
		अन्यथा
			*mobile = true;
		/* release memory */
		iounmap(biosptr);

		वापस true;
	पूर्ण अन्यथा अणु
		iounmap(biosptr);
		वापस false;
	पूर्ण
पूर्ण
