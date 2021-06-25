<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#समावेश <linux/via-core.h>
#समावेश <linux/via_i2c.h>
#समावेश "global.h"

अटल व्योम पंचांगds_रेजिस्टर_ग_लिखो(पूर्णांक index, u8 data);
अटल पूर्णांक पंचांगds_रेजिस्टर_पढ़ो(पूर्णांक index);
अटल पूर्णांक पंचांगds_रेजिस्टर_पढ़ो_bytes(पूर्णांक index, u8 *buff, पूर्णांक buff_len);
अटल व्योम dvi_get_panel_size_from_DDCv1(
	काष्ठा पंचांगds_chip_inक्रमmation *पंचांगds_chip,
	काष्ठा पंचांगds_setting_inक्रमmation *पंचांगds_setting);
अटल पूर्णांक viafb_dvi_query_EDID(व्योम);

अटल अंतरभूत bool check_पंचांगds_chip(पूर्णांक device_id_subaddr, पूर्णांक device_id)
अणु
	वापस पंचांगds_रेजिस्टर_पढ़ो(device_id_subaddr) == device_id;
पूर्ण

व्योम viafb_init_dvi_size(काष्ठा पंचांगds_chip_inक्रमmation *पंचांगds_chip,
			 काष्ठा पंचांगds_setting_inक्रमmation *पंचांगds_setting)
अणु
	DEBUG_MSG(KERN_INFO "viafb_init_dvi_size()\n");

	viafb_dvi_sense();
	अगर (viafb_dvi_query_EDID() == 1)
		dvi_get_panel_size_from_DDCv1(पंचांगds_chip, पंचांगds_setting);

	वापस;
पूर्ण

bool viafb_पंचांगds_trयंत्रitter_identअगरy(व्योम)
अणु
	अचिन्हित अक्षर sr2a = 0, sr1e = 0, sr3e = 0;

	/* Turn on ouputting pad */
	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_K8M890:
	    /*=* DFP Low Pad on *=*/
		sr2a = viafb_पढ़ो_reg(VIASR, SR2A);
		viafb_ग_लिखो_reg_mask(SR2A, VIASR, 0x03, BIT0 + BIT1);
		अवरोध;

	हाल UNICHROME_P4M900:
	हाल UNICHROME_P4M890:
		/* DFP Low Pad on */
		sr2a = viafb_पढ़ो_reg(VIASR, SR2A);
		viafb_ग_लिखो_reg_mask(SR2A, VIASR, 0x03, BIT0 + BIT1);
		/* DVP0 Pad on */
		sr1e = viafb_पढ़ो_reg(VIASR, SR1E);
		viafb_ग_लिखो_reg_mask(SR1E, VIASR, 0xC0, BIT6 + BIT7);
		अवरोध;

	शेष:
	    /* DVP0/DVP1 Pad on */
		sr1e = viafb_पढ़ो_reg(VIASR, SR1E);
		viafb_ग_लिखो_reg_mask(SR1E, VIASR, 0xF0, BIT4 +
			BIT5 + BIT6 + BIT7);
	    /* SR3E[1]Multi-function selection:
	    0 = Emulate I2C and DDC bus by GPIO2/3/4. */
		sr3e = viafb_पढ़ो_reg(VIASR, SR3E);
		viafb_ग_लिखो_reg_mask(SR3E, VIASR, 0x0, BIT5);
		अवरोध;
	पूर्ण

	/* Check क्रम VT1632: */
	viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_name = VT1632_TMDS;
	viaparinfo->chip_info->
		पंचांगds_chip_info.पंचांगds_chip_slave_addr = VT1632_TMDS_I2C_ADDR;
	viaparinfo->chip_info->पंचांगds_chip_info.i2c_port = VIA_PORT_31;
	अगर (check_पंचांगds_chip(VT1632_DEVICE_ID_REG, VT1632_DEVICE_ID)) अणु
		/*
		 * Currently only support 12bits,dual edge,add 24bits mode later
		 */
		पंचांगds_रेजिस्टर_ग_लिखो(0x08, 0x3b);

		DEBUG_MSG(KERN_INFO "\n VT1632 TMDS ! \n");
		DEBUG_MSG(KERN_INFO "\n %2d",
			  viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_name);
		DEBUG_MSG(KERN_INFO "\n %2d",
			  viaparinfo->chip_info->पंचांगds_chip_info.i2c_port);
		वापस true;
	पूर्ण अन्यथा अणु
		viaparinfo->chip_info->पंचांगds_chip_info.i2c_port = VIA_PORT_2C;
		अगर (check_पंचांगds_chip(VT1632_DEVICE_ID_REG, VT1632_DEVICE_ID)) अणु
			पंचांगds_रेजिस्टर_ग_लिखो(0x08, 0x3b);
			DEBUG_MSG(KERN_INFO "\n VT1632 TMDS ! \n");
			DEBUG_MSG(KERN_INFO "\n %2d",
				  viaparinfo->chip_info->
				  पंचांगds_chip_info.पंचांगds_chip_name);
			DEBUG_MSG(KERN_INFO "\n %2d",
				  viaparinfo->chip_info->
				  पंचांगds_chip_info.i2c_port);
			वापस true;
		पूर्ण
	पूर्ण

	viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_name = INTEGRATED_TMDS;

	अगर ((viaparinfo->chip_info->gfx_chip_name == UNICHROME_CX700) &&
	    ((viafb_display_hardware_layout == HW_LAYOUT_DVI_ONLY) ||
	     (viafb_display_hardware_layout == HW_LAYOUT_LCD_DVI))) अणु
		DEBUG_MSG(KERN_INFO "\n Integrated TMDS ! \n");
		वापस true;
	पूर्ण

	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_K8M890:
		viafb_ग_लिखो_reg(SR2A, VIASR, sr2a);
		अवरोध;

	हाल UNICHROME_P4M900:
	हाल UNICHROME_P4M890:
		viafb_ग_लिखो_reg(SR2A, VIASR, sr2a);
		viafb_ग_लिखो_reg(SR1E, VIASR, sr1e);
		अवरोध;

	शेष:
		viafb_ग_लिखो_reg(SR1E, VIASR, sr1e);
		viafb_ग_लिखो_reg(SR3E, VIASR, sr3e);
		अवरोध;
	पूर्ण

	viaparinfo->chip_info->
		पंचांगds_chip_info.पंचांगds_chip_name = NON_TMDS_TRANSMITTER;
	viaparinfo->chip_info->पंचांगds_chip_info.
		पंचांगds_chip_slave_addr = VT1632_TMDS_I2C_ADDR;
	वापस false;
पूर्ण

अटल व्योम पंचांगds_रेजिस्टर_ग_लिखो(पूर्णांक index, u8 data)
अणु
	viafb_i2c_ग_लिखोbyte(viaparinfo->chip_info->पंचांगds_chip_info.i2c_port,
			    viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_slave_addr,
			    index, data);
पूर्ण

अटल पूर्णांक पंचांगds_रेजिस्टर_पढ़ो(पूर्णांक index)
अणु
	u8 data;

	viafb_i2c_पढ़ोbyte(viaparinfo->chip_info->पंचांगds_chip_info.i2c_port,
			   (u8) viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_slave_addr,
			   (u8) index, &data);
	वापस data;
पूर्ण

अटल पूर्णांक पंचांगds_रेजिस्टर_पढ़ो_bytes(पूर्णांक index, u8 *buff, पूर्णांक buff_len)
अणु
	viafb_i2c_पढ़ोbytes(viaparinfo->chip_info->पंचांगds_chip_info.i2c_port,
			    (u8) viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_slave_addr,
			    (u8) index, buff, buff_len);
	वापस 0;
पूर्ण

/* DVI Set Mode */
व्योम viafb_dvi_set_mode(स्थिर काष्ठा fb_var_screeninfo *var,
	u16 cxres, u16 cyres, पूर्णांक iga)
अणु
	काष्ठा fb_var_screeninfo dvi_var = *var;
	स्थिर काष्ठा fb_videomode *rb_mode;
	पूर्णांक maxPixelClock;

	maxPixelClock = viaparinfo->shared->पंचांगds_setting_info.max_pixel_घड़ी;
	अगर (maxPixelClock && PICOS2KHZ(var->pixघड़ी) / 1000 > maxPixelClock) अणु
		rb_mode = viafb_get_best_rb_mode(var->xres, var->yres, 60);
		अगर (rb_mode)
			viafb_fill_var_timing_info(&dvi_var, rb_mode);
	पूर्ण

	viafb_fill_crtc_timing(&dvi_var, cxres, cyres, iga);
पूर्ण

/* Sense DVI Connector */
पूर्णांक viafb_dvi_sense(व्योम)
अणु
	u8 RegSR1E = 0, RegSR3E = 0, RegCR6B = 0, RegCR91 = 0,
		RegCR93 = 0, RegCR9B = 0, data;
	पूर्णांक ret = false;

	DEBUG_MSG(KERN_INFO "viafb_dvi_sense!!\n");

	अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) अणु
		/* DI1 Pad on */
		RegSR1E = viafb_पढ़ो_reg(VIASR, SR1E);
		viafb_ग_लिखो_reg(SR1E, VIASR, RegSR1E | 0x30);

		/* CR6B[0]VCK Input Selection: 1 = External घड़ी. */
		RegCR6B = viafb_पढ़ो_reg(VIACR, CR6B);
		viafb_ग_लिखो_reg(CR6B, VIACR, RegCR6B | 0x08);

		/* CR91[4] VDD On [3] Data On [2] VEE On [1] Back Light Off
		   [0] Software Control Power Sequence */
		RegCR91 = viafb_पढ़ो_reg(VIACR, CR91);
		viafb_ग_लिखो_reg(CR91, VIACR, 0x1D);

		/* CR93[7] DI1 Data Source Selection: 1 = DSP2.
		   CR93[5] DI1 Clock Source: 1 = पूर्णांकernal.
		   CR93[4] DI1 Clock Polarity.
		   CR93[3:1] DI1 Clock Adjust. CR93[0] DI1 enable */
		RegCR93 = viafb_पढ़ो_reg(VIACR, CR93);
		viafb_ग_लिखो_reg(CR93, VIACR, 0x01);
	पूर्ण अन्यथा अणु
		/* DVP0/DVP1 Pad on */
		RegSR1E = viafb_पढ़ो_reg(VIASR, SR1E);
		viafb_ग_लिखो_reg(SR1E, VIASR, RegSR1E | 0xF0);

		/* SR3E[1]Multi-function selection:
		   0 = Emulate I2C and DDC bus by GPIO2/3/4. */
		RegSR3E = viafb_पढ़ो_reg(VIASR, SR3E);
		viafb_ग_लिखो_reg(SR3E, VIASR, RegSR3E & (~0x20));

		/* CR91[4] VDD On [3] Data On [2] VEE On [1] Back Light Off
		   [0] Software Control Power Sequence */
		RegCR91 = viafb_पढ़ो_reg(VIACR, CR91);
		viafb_ग_लिखो_reg(CR91, VIACR, 0x1D);

		/*CR9B[4] DVP1 Data Source Selection: 1 = From secondary
		display.CR9B[2:0] DVP1 Clock Adjust */
		RegCR9B = viafb_पढ़ो_reg(VIACR, CR9B);
		viafb_ग_लिखो_reg(CR9B, VIACR, 0x01);
	पूर्ण

	data = (u8) पंचांगds_रेजिस्टर_पढ़ो(0x09);
	अगर (data & 0x04)
		ret = true;

	अगर (ret == false) अणु
		अगर (viafb_dvi_query_EDID())
			ret = true;
	पूर्ण

	/* Restore status */
	viafb_ग_लिखो_reg(SR1E, VIASR, RegSR1E);
	viafb_ग_लिखो_reg(CR91, VIACR, RegCR91);
	अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266) अणु
		viafb_ग_लिखो_reg(CR6B, VIACR, RegCR6B);
		viafb_ग_लिखो_reg(CR93, VIACR, RegCR93);
	पूर्ण अन्यथा अणु
		viafb_ग_लिखो_reg(SR3E, VIASR, RegSR3E);
		viafb_ग_लिखो_reg(CR9B, VIACR, RegCR9B);
	पूर्ण

	वापस ret;
पूर्ण

/* Query Flat Panel's EDID Table Version Through DVI Connector */
अटल पूर्णांक viafb_dvi_query_EDID(व्योम)
अणु
	u8 data0, data1;
	पूर्णांक restore;

	DEBUG_MSG(KERN_INFO "viafb_dvi_query_EDID!!\n");

	restore = viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_slave_addr;
	viaparinfo->chip_info->पंचांगds_chip_info.पंचांगds_chip_slave_addr = 0xA0;

	data0 = (u8) पंचांगds_रेजिस्टर_पढ़ो(0x00);
	data1 = (u8) पंचांगds_रेजिस्टर_पढ़ो(0x01);
	अगर ((data0 == 0) && (data1 == 0xFF)) अणु
		viaparinfo->chip_info->
			पंचांगds_chip_info.पंचांगds_chip_slave_addr = restore;
		वापस EDID_VERSION_1;	/* Found EDID1 Table */
	पूर्ण

	वापस false;
पूर्ण

/* Get Panel Size Using EDID1 Table */
अटल व्योम dvi_get_panel_size_from_DDCv1(
	काष्ठा पंचांगds_chip_inक्रमmation *पंचांगds_chip,
	काष्ठा पंचांगds_setting_inक्रमmation *पंचांगds_setting)
अणु
	पूर्णांक i, restore;
	अचिन्हित अक्षर EDID_DATA[18];

	DEBUG_MSG(KERN_INFO "\n dvi_get_panel_size_from_DDCv1 \n");

	restore = पंचांगds_chip->पंचांगds_chip_slave_addr;
	पंचांगds_chip->पंचांगds_chip_slave_addr = 0xA0;
	क्रम (i = 0x25; i < 0x6D; i++) अणु
		चयन (i) अणु
		हाल 0x36:
		हाल 0x48:
		हाल 0x5A:
		हाल 0x6C:
			पंचांगds_रेजिस्टर_पढ़ो_bytes(i, EDID_DATA, 10);
			अगर (!(EDID_DATA[0] || EDID_DATA[1])) अणु
				/* The first two byte must be zero. */
				अगर (EDID_DATA[3] == 0xFD) अणु
					/* To get max pixel घड़ी. */
					पंचांगds_setting->max_pixel_घड़ी =
						EDID_DATA[9] * 10;
				पूर्ण
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	DEBUG_MSG(KERN_INFO "DVI max pixelclock = %d\n",
		पंचांगds_setting->max_pixel_घड़ी);
	पंचांगds_chip->पंचांगds_chip_slave_addr = restore;
पूर्ण

/* If Disable DVI, turn off pad */
व्योम viafb_dvi_disable(व्योम)
अणु
	अगर (viaparinfo->chip_info->
		पंचांगds_chip_info.output_पूर्णांकerface == INTERFACE_TMDS)
		/* Turn off TMDS घातer. */
		viafb_ग_लिखो_reg(CRD2, VIACR,
		viafb_पढ़ो_reg(VIACR, CRD2) | 0x08);
पूर्ण

अटल व्योम dvi_patch_skew_dvp0(व्योम)
अणु
	/* Reset data driving first: */
	viafb_ग_लिखो_reg_mask(SR1B, VIASR, 0, BIT1);
	viafb_ग_लिखो_reg_mask(SR2A, VIASR, 0, BIT4);

	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_P4M890:
		अणु
			अगर ((viaparinfo->पंचांगds_setting_info->h_active == 1600) &&
				(viaparinfo->पंचांगds_setting_info->v_active ==
				1200))
				viafb_ग_लिखो_reg_mask(CR96, VIACR, 0x03,
					       BIT0 + BIT1 + BIT2);
			अन्यथा
				viafb_ग_लिखो_reg_mask(CR96, VIACR, 0x07,
					       BIT0 + BIT1 + BIT2);
			अवरोध;
		पूर्ण

	हाल UNICHROME_P4M900:
		अणु
			viafb_ग_लिखो_reg_mask(CR96, VIACR, 0x07,
				       BIT0 + BIT1 + BIT2 + BIT3);
			viafb_ग_लिखो_reg_mask(SR1B, VIASR, 0x02, BIT1);
			viafb_ग_लिखो_reg_mask(SR2A, VIASR, 0x10, BIT4);
			अवरोध;
		पूर्ण

	शेष:
		अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dvi_patch_skew_dvp_low(व्योम)
अणु
	चयन (viaparinfo->chip_info->gfx_chip_name) अणु
	हाल UNICHROME_K8M890:
		अणु
			viafb_ग_लिखो_reg_mask(CR99, VIACR, 0x03, BIT0 + BIT1);
			अवरोध;
		पूर्ण

	हाल UNICHROME_P4M900:
		अणु
			viafb_ग_लिखो_reg_mask(CR99, VIACR, 0x08,
				       BIT0 + BIT1 + BIT2 + BIT3);
			अवरोध;
		पूर्ण

	हाल UNICHROME_P4M890:
		अणु
			viafb_ग_लिखो_reg_mask(CR99, VIACR, 0x0F,
				       BIT0 + BIT1 + BIT2 + BIT3);
			अवरोध;
		पूर्ण

	शेष:
		अणु
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* If Enable DVI, turn off pad */
व्योम viafb_dvi_enable(व्योम)
अणु
	u8 data;

	चयन (viaparinfo->chip_info->पंचांगds_chip_info.output_पूर्णांकerface) अणु
	हाल INTERFACE_DVP0:
		viafb_ग_लिखो_reg_mask(CR6B, VIACR, 0x01, BIT0);
		viafb_ग_लिखो_reg_mask(CR6C, VIACR, 0x21, BIT0 + BIT5);
		dvi_patch_skew_dvp0();
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			पंचांगds_रेजिस्टर_ग_लिखो(0x88, 0x3b);
		अन्यथा
			/*clear CR91[5] to direct on display period
			   in the secondary diplay path */
			via_ग_लिखो_reg_mask(VIACR, 0x91, 0x00, 0x20);
		अवरोध;

	हाल INTERFACE_DVP1:
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			viafb_ग_लिखो_reg_mask(CR93, VIACR, 0x21, BIT0 + BIT5);

		/*fix dvi cann't be enabled with MB VT5718C4 - Al Zhang */
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			पंचांगds_रेजिस्टर_ग_लिखो(0x88, 0x3b);
		अन्यथा
			/*clear CR91[5] to direct on display period
			  in the secondary diplay path */
			via_ग_लिखो_reg_mask(VIACR, 0x91, 0x00, 0x20);

		/*fix DVI cannot enable on EPIA-M board */
		अगर (viafb_platक्रमm_epia_dvi == 1) अणु
			viafb_ग_लिखो_reg_mask(CR91, VIACR, 0x1f, 0x1f);
			viafb_ग_लिखो_reg_mask(CR88, VIACR, 0x00, BIT6 + BIT0);
			अगर (viafb_bus_width == 24) अणु
				अगर (viafb_device_lcd_dualedge == 1)
					data = 0x3F;
				अन्यथा
					data = 0x37;
				viafb_i2c_ग_लिखोbyte(viaparinfo->chip_info->
					पंचांगds_chip_info.i2c_port,
					viaparinfo->chip_info->
					पंचांगds_chip_info.पंचांगds_chip_slave_addr,
					0x08, data);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल INTERFACE_DFP_HIGH:
		अगर (viaparinfo->chip_info->gfx_chip_name != UNICHROME_CLE266)
			via_ग_लिखो_reg_mask(VIACR, CR97, 0x03, 0x03);

		via_ग_लिखो_reg_mask(VIACR, 0x91, 0x00, 0x20);
		अवरोध;

	हाल INTERFACE_DFP_LOW:
		अगर (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			अवरोध;

		dvi_patch_skew_dvp_low();
		via_ग_लिखो_reg_mask(VIACR, 0x91, 0x00, 0x20);
		अवरोध;

	हाल INTERFACE_TMDS:
		/* Turn on Display period in the panel path. */
		viafb_ग_लिखो_reg_mask(CR91, VIACR, 0, BIT7);

		/* Turn on TMDS घातer. */
		viafb_ग_लिखो_reg_mask(CRD2, VIACR, 0, BIT3);
		अवरोध;
	पूर्ण

	अगर (viaparinfo->पंचांगds_setting_info->iga_path == IGA2) अणु
		/* Disable LCD Scaling */
		viafb_ग_लिखो_reg_mask(CR79, VIACR, 0x00, BIT0);
	पूर्ण
पूर्ण
