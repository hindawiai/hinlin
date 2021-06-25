<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "radeonfb.h"

#समावेश <linux/slab.h>

#समावेश "../edid.h"

अटल स्थिर काष्ठा fb_var_screeninfo radeonfb_शेष_var = अणु
	.xres		= 640,
	.yres		= 480,
	.xres_भव	= 640,
	.yres_भव	= 480,
	.bits_per_pixel = 8,
	.red		= अणु .length = 8 पूर्ण,
	.green		= अणु .length = 8 पूर्ण,
	.blue		= अणु .length = 8 पूर्ण,
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.pixघड़ी	= 39721,
	.left_margin	= 40,
	.right_margin	= 24,
	.upper_margin	= 32,
	.lower_margin	= 11,
	.hsync_len	= 96,
	.vsync_len	= 2,
	.vmode		= FB_VMODE_NONINTERLACED
पूर्ण;

अटल अक्षर *radeon_get_mon_name(पूर्णांक type)
अणु
	अक्षर *pret = शून्य;

	चयन (type) अणु
		हाल MT_NONE:
			pret = "no";
			अवरोध;
		हाल MT_CRT:
			pret = "CRT";
			अवरोध;
		हाल MT_DFP:
			pret = "DFP";
			अवरोध;
		हाल MT_LCD:
			pret = "LCD";
			अवरोध;
		हाल MT_CTV:
			pret = "CTV";
			अवरोध;
		हाल MT_STV:
			pret = "STV";
			अवरोध;
	पूर्ण

	वापस pret;
पूर्ण


#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
/*
 * Try to find monitor inक्रमmations & EDID data out of the Open Firmware
 * device-tree. This also contains some "hacks" to work around a few machine
 * models with broken OF probing by hard-coding known EDIDs क्रम some Mac
 * laptops पूर्णांकernal LVDS panel. (XXX: not करोne yet)
 */
अटल पूर्णांक radeon_parse_montype_prop(काष्ठा device_node *dp, u8 **out_EDID,
				     पूर्णांक hdno)
अणु
        अटल अक्षर *propnames[] = अणु "DFP,EDID", "LCD,EDID", "EDID",
				     "EDID1", "EDID2",  शून्य पूर्ण;
	स्थिर u8 *pedid = शून्य;
	स्थिर u8 *pmt = शून्य;
	u8 *पंचांगp;
        पूर्णांक i, mt = MT_NONE;  
	
	pr_debug("analyzing OF properties...\n");
	pmt = of_get_property(dp, "display-type", शून्य);
	अगर (!pmt)
		वापस MT_NONE;
	pr_debug("display-type: %s\n", pmt);
	/* OF says "LCD" क्रम DFP as well, we discriminate from the caller of this
	 * function
	 */
	अगर (!म_भेद(pmt, "LCD") || !म_भेद(pmt, "DFP"))
		mt = MT_DFP;
	अन्यथा अगर (!म_भेद(pmt, "CRT"))
		mt = MT_CRT;
	अन्यथा अणु
		अगर (म_भेद(pmt, "NONE") != 0)
			prपूर्णांकk(KERN_WARNING "radeonfb: Unknown OF display-type: %s\n",
			       pmt);
		वापस MT_NONE;
	पूर्ण

	क्रम (i = 0; propnames[i] != शून्य; ++i) अणु
		pedid = of_get_property(dp, propnames[i], शून्य);
		अगर (pedid != शून्य)
			अवरोध;
	पूर्ण
	/* We didn't find the EDID in the leaf node, some cards will actually
	 * put EDID1/EDID2 in the parent, look क्रम these (typically M6 tipb).
	 * single-head cards have hdno == -1 and skip this step
	 */
	अगर (pedid == शून्य && dp->parent && (hdno != -1))
		pedid = of_get_property(dp->parent,
				(hdno == 0) ? "EDID1" : "EDID2", शून्य);
	अगर (pedid == शून्य && dp->parent && (hdno == 0))
		pedid = of_get_property(dp->parent, "EDID", शून्य);
	अगर (pedid == शून्य)
		वापस mt;

	पंचांगp = kmemdup(pedid, EDID_LENGTH, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस mt;
	*out_EDID = पंचांगp;
	वापस mt;
पूर्ण

अटल पूर्णांक radeon_probe_OF_head(काष्ठा radeonfb_info *rinfo, पूर्णांक head_no,
				u8 **out_EDID)
अणु
        काष्ठा device_node *dp;

	pr_debug("radeon_probe_OF_head\n");

        dp = rinfo->of_node;
        जबतक (dp == शून्य)
		वापस MT_NONE;

	अगर (rinfo->has_CRTC2) अणु
		स्थिर अक्षर *pname;
		पूर्णांक len, second = 0;

		dp = dp->child;
		करो अणु
			अगर (!dp)
				वापस MT_NONE;
			pname = of_get_property(dp, "name", शून्य);
			अगर (!pname)
				वापस MT_NONE;
			len = म_माप(pname);
			pr_debug("head: %s (letter: %c, head_no: %d)\n",
			       pname, pname[len-1], head_no);
			अगर (pname[len-1] == 'A' && head_no == 0) अणु
				पूर्णांक mt = radeon_parse_montype_prop(dp, out_EDID, 0);
				/* Maybe check क्रम LVDS_GEN_CNTL here ? I need to check out
				 * what OF करोes when booting with lid बंदd
				 */
				अगर (mt == MT_DFP && rinfo->is_mobility)
					mt = MT_LCD;
				वापस mt;
			पूर्ण अन्यथा अगर (pname[len-1] == 'B' && head_no == 1)
				वापस radeon_parse_montype_prop(dp, out_EDID, 1);
			second = 1;
			dp = dp->sibling;
		पूर्ण जबतक(!second);
	पूर्ण अन्यथा अणु
		अगर (head_no > 0)
			वापस MT_NONE;
		वापस radeon_parse_montype_prop(dp, out_EDID, -1);
	पूर्ण
        वापस MT_NONE;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC || CONFIG_SPARC */


अटल पूर्णांक radeon_get_panel_info_BIOS(काष्ठा radeonfb_info *rinfo)
अणु
	अचिन्हित दीर्घ पंचांगp, पंचांगp0;
	अक्षर sपंचांगp[30];
	पूर्णांक i;

	अगर (!rinfo->bios_seg)
		वापस 0;

	अगर (!(पंचांगp = BIOS_IN16(rinfo->fp_bios_start + 0x40))) अणु
		prपूर्णांकk(KERN_ERR "radeonfb: Failed to detect DFP panel info using BIOS\n");
		rinfo->panel_info.pwr_delay = 200;
		वापस 0;
	पूर्ण

	क्रम(i=0; i<24; i++)
		sपंचांगp[i] = BIOS_IN8(पंचांगp+i+1);
	sपंचांगp[24] = 0;
	prपूर्णांकk("radeonfb: panel ID string: %s\n", sपंचांगp);
	rinfo->panel_info.xres = BIOS_IN16(पंचांगp + 25);
	rinfo->panel_info.yres = BIOS_IN16(पंचांगp + 27);
	prपूर्णांकk("radeonfb: detected LVDS panel size from BIOS: %dx%d\n",
		rinfo->panel_info.xres, rinfo->panel_info.yres);

	rinfo->panel_info.pwr_delay = BIOS_IN16(पंचांगp + 44);
	pr_debug("BIOS provided panel power delay: %d\n", rinfo->panel_info.pwr_delay);
	अगर (rinfo->panel_info.pwr_delay > 2000 || rinfo->panel_info.pwr_delay <= 0)
		rinfo->panel_info.pwr_delay = 2000;

	/*
	 * Some panels only work properly with some भागider combinations
	 */
	rinfo->panel_info.ref_भागider = BIOS_IN16(पंचांगp + 46);
	rinfo->panel_info.post_भागider = BIOS_IN8(पंचांगp + 48);
	rinfo->panel_info.fbk_भागider = BIOS_IN16(पंचांगp + 49);
	अगर (rinfo->panel_info.ref_भागider != 0 &&
	    rinfo->panel_info.fbk_भागider > 3) अणु
		rinfo->panel_info.use_bios_भागiders = 1;
		prपूर्णांकk(KERN_INFO "radeondb: BIOS provided dividers will be used\n");
		pr_debug("ref_divider = %x\n", rinfo->panel_info.ref_भागider);
		pr_debug("post_divider = %x\n", rinfo->panel_info.post_भागider);
		pr_debug("fbk_divider = %x\n", rinfo->panel_info.fbk_भागider);
	पूर्ण
	pr_debug("Scanning BIOS table ...\n");
	क्रम(i=0; i<32; i++) अणु
		पंचांगp0 = BIOS_IN16(पंचांगp+64+i*2);
		अगर (पंचांगp0 == 0)
			अवरोध;
		pr_debug(" %d x %d\n", BIOS_IN16(पंचांगp0), BIOS_IN16(पंचांगp0+2));
		अगर ((BIOS_IN16(पंचांगp0) == rinfo->panel_info.xres) &&
		    (BIOS_IN16(पंचांगp0+2) == rinfo->panel_info.yres)) अणु
			rinfo->panel_info.hblank = (BIOS_IN16(पंचांगp0+17) - BIOS_IN16(पंचांगp0+19)) * 8;
			rinfo->panel_info.hOver_plus = ((BIOS_IN16(पंचांगp0+21) -
							 BIOS_IN16(पंचांगp0+19) -1) * 8) & 0x7fff;
			rinfo->panel_info.hSync_width = BIOS_IN8(पंचांगp0+23) * 8;
			rinfo->panel_info.vblank = BIOS_IN16(पंचांगp0+24) - BIOS_IN16(पंचांगp0+26);
			rinfo->panel_info.vOver_plus = (BIOS_IN16(पंचांगp0+28) & 0x7ff) - BIOS_IN16(पंचांगp0+26);
			rinfo->panel_info.vSync_width = (BIOS_IN16(पंचांगp0+28) & 0xf800) >> 11;
			rinfo->panel_info.घड़ी = BIOS_IN16(पंचांगp0+9);
			/* Assume high active syncs क्रम now until ATI tells me more... maybe we
			 * can probe रेजिस्टर values here ?
			 */
			rinfo->panel_info.hAct_high = 1;
			rinfo->panel_info.vAct_high = 1;
			/* Mark panel infos valid */
			rinfo->panel_info.valid = 1;

			pr_debug("Found panel in BIOS table:\n");
			pr_debug("  hblank: %d\n", rinfo->panel_info.hblank);
			pr_debug("  hOver_plus: %d\n", rinfo->panel_info.hOver_plus);
			pr_debug("  hSync_width: %d\n", rinfo->panel_info.hSync_width);
			pr_debug("  vblank: %d\n", rinfo->panel_info.vblank);
			pr_debug("  vOver_plus: %d\n", rinfo->panel_info.vOver_plus);
			pr_debug("  vSync_width: %d\n", rinfo->panel_info.vSync_width);
			pr_debug("  clock: %d\n", rinfo->panel_info.घड़ी);
				
			वापस 1;
		पूर्ण
	पूर्ण
	pr_debug("Didn't find panel in BIOS table !\n");

	वापस 0;
पूर्ण

/* Try to extract the connector inक्रमmations from the BIOS. This
 * करोesn't quite work yet, but it's output is still useful क्रम
 * debugging
 */
अटल व्योम radeon_parse_connector_info(काष्ठा radeonfb_info *rinfo)
अणु
	पूर्णांक offset, chips, connectors, पंचांगp, i, conn, type;

	अटल अक्षर* __conn_type_table[16] = अणु
		"NONE", "Proprietary", "CRT", "DVI-I", "DVI-D", "Unknown", "Unknown",
		"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
		"Unknown", "Unknown", "Unknown"
	पूर्ण;

	अगर (!rinfo->bios_seg)
		वापस;

	offset = BIOS_IN16(rinfo->fp_bios_start + 0x50);
	अगर (offset == 0) अणु
		prपूर्णांकk(KERN_WARNING "radeonfb: No connector info table detected\n");
		वापस;
	पूर्ण

	/* Don't करो much more at this poपूर्णांक but displaying the data अगर
	 * DEBUG is enabled
	 */
	chips = BIOS_IN8(offset++) >> 4;
	pr_debug("%d chips in connector info\n", chips);
	क्रम (i = 0; i < chips; i++) अणु
		पंचांगp = BIOS_IN8(offset++);
		connectors = पंचांगp & 0x0f;
		pr_debug(" - chip %d has %d connectors\n", पंचांगp >> 4, connectors);
		क्रम (conn = 0; ; conn++) अणु
			पंचांगp = BIOS_IN16(offset);
			अगर (पंचांगp == 0)
				अवरोध;
			offset += 2;
			type = (पंचांगp >> 12) & 0x0f;
			pr_debug("  * connector %d of type %d (%s) : %04x\n",
			       conn, type, __conn_type_table[type], पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण


/*
 * Probe physical connection of a CRT. This code comes from XFree
 * as well and currently is only implemented क्रम the CRT DAC, the
 * code क्रम the TVDAC is commented out in XFree as "non working"
 */
अटल पूर्णांक radeon_crt_is_connected(काष्ठा radeonfb_info *rinfo, पूर्णांक is_crt_dac)
अणु
    पूर्णांक	          connected = 0;

    /* the monitor either wasn't connected or it is a non-DDC CRT.
     * try to probe it
     */
    अगर (is_crt_dac) अणु
	अचिन्हित दीर्घ ulOrigVCLK_ECP_CNTL;
	अचिन्हित दीर्घ ulOrigDAC_CNTL;
	अचिन्हित दीर्घ ulOrigDAC_EXT_CNTL;
	अचिन्हित दीर्घ ulOrigCRTC_EXT_CNTL;
	अचिन्हित दीर्घ ulData;
	अचिन्हित दीर्घ ulMask;

	ulOrigVCLK_ECP_CNTL = INPLL(VCLK_ECP_CNTL);

	ulData              = ulOrigVCLK_ECP_CNTL;
	ulData             &= ~(PIXCLK_ALWAYS_ONb
				| PIXCLK_DAC_ALWAYS_ONb);
	ulMask              = ~(PIXCLK_ALWAYS_ONb
				| PIXCLK_DAC_ALWAYS_ONb);
	OUTPLLP(VCLK_ECP_CNTL, ulData, ulMask);

	ulOrigCRTC_EXT_CNTL = INREG(CRTC_EXT_CNTL);
	ulData              = ulOrigCRTC_EXT_CNTL;
	ulData             |= CRTC_CRT_ON;
	OUTREG(CRTC_EXT_CNTL, ulData);
   
	ulOrigDAC_EXT_CNTL = INREG(DAC_EXT_CNTL);
	ulData             = ulOrigDAC_EXT_CNTL;
	ulData            &= ~DAC_FORCE_DATA_MASK;
	ulData            |=  (DAC_FORCE_BLANK_OFF_EN
			       |DAC_FORCE_DATA_EN
			       |DAC_FORCE_DATA_SEL_MASK);
	अगर ((rinfo->family == CHIP_FAMILY_RV250) ||
	    (rinfo->family == CHIP_FAMILY_RV280))
	    ulData |= (0x01b6 << DAC_FORCE_DATA_SHIFT);
	अन्यथा
	    ulData |= (0x01ac << DAC_FORCE_DATA_SHIFT);

	OUTREG(DAC_EXT_CNTL, ulData);

	ulOrigDAC_CNTL     = INREG(DAC_CNTL);
	ulData             = ulOrigDAC_CNTL;
	ulData            |= DAC_CMP_EN;
	ulData            &= ~(DAC_RANGE_CNTL_MASK
			       | DAC_PDWN);
	ulData            |= 0x2;
	OUTREG(DAC_CNTL, ulData);

	mdelay(1);

	ulData     = INREG(DAC_CNTL);
	connected =  (DAC_CMP_OUTPUT & ulData) ? 1 : 0;
  
	ulData    = ulOrigVCLK_ECP_CNTL;
	ulMask    = 0xFFFFFFFFL;
	OUTPLLP(VCLK_ECP_CNTL, ulData, ulMask);

	OUTREG(DAC_CNTL,      ulOrigDAC_CNTL     );
	OUTREG(DAC_EXT_CNTL,  ulOrigDAC_EXT_CNTL );
	OUTREG(CRTC_EXT_CNTL, ulOrigCRTC_EXT_CNTL);
    पूर्ण

    वापस connected ? MT_CRT : MT_NONE;
पूर्ण

/*
 * Parse the "monitor_layout" string अगर any. This code is mostly
 * copied from XFree's radeon driver
 */
अटल पूर्णांक radeon_parse_monitor_layout(काष्ठा radeonfb_info *rinfo,
				       स्थिर अक्षर *monitor_layout)
अणु
	अक्षर s1[5], s2[5];
	पूर्णांक i = 0, second = 0;
	स्थिर अक्षर *s;

	अगर (!monitor_layout)
		वापस 0;

	s = monitor_layout;
	करो अणु
		चयन(*s) अणु
		हाल ',':
			s1[i] = '\0';
			i = 0;
			second = 1;
			अवरोध;
		हाल ' ':
		हाल '\0':
			अवरोध;
		शेष:
			अगर (i > 4)
				अवरोध;
			अगर (second)
				s2[i] = *s;
			अन्यथा
				s1[i] = *s;
			i++;
		पूर्ण

		अगर (i > 4)
			i = 4;

	पूर्ण जबतक (*s++);
	अगर (second)
		s2[i] = 0;
	अन्यथा अणु
		s1[i] = 0;
		s2[0] = 0;
	पूर्ण
	अगर (म_भेद(s1, "CRT") == 0)
		rinfo->mon1_type = MT_CRT;
	अन्यथा अगर (म_भेद(s1, "TMDS") == 0)
		rinfo->mon1_type = MT_DFP;
	अन्यथा अगर (म_भेद(s1, "LVDS") == 0)
		rinfo->mon1_type = MT_LCD;

	अगर (म_भेद(s2, "CRT") == 0)
		rinfo->mon2_type = MT_CRT;
	अन्यथा अगर (म_भेद(s2, "TMDS") == 0)
		rinfo->mon2_type = MT_DFP;
	अन्यथा अगर (म_भेद(s2, "LVDS") == 0)
		rinfo->mon2_type = MT_LCD;

	वापस 1;
पूर्ण

/*
 * Probe display on both primary and secondary card's connector (अगर any)
 * by various available techniques (i2c, OF device tree, BIOS, ...) and
 * try to retrieve EDID. The algorithm here comes from XFree's radeon
 * driver
 */
व्योम radeon_probe_screens(काष्ठा radeonfb_info *rinfo,
			  स्थिर अक्षर *monitor_layout, पूर्णांक ignore_edid)
अणु
#अगर_घोषित CONFIG_FB_RADEON_I2C
	पूर्णांक ddc_crt2_used = 0;	
#पूर्ण_अगर
	पूर्णांक पंचांगp, i;

	radeon_parse_connector_info(rinfo);

	अगर (radeon_parse_monitor_layout(rinfo, monitor_layout)) अणु

		/*
		 * If user specअगरied a monitor_layout option, use it instead
		 * of स्वतः-detecting. Maybe we should only use this argument
		 * on the first radeon card probed or provide a way to specअगरy
		 * a layout क्रम each card ?
		 */

		pr_debug("Using specified monitor layout: %s", monitor_layout);
#अगर_घोषित CONFIG_FB_RADEON_I2C
		अगर (!ignore_edid) अणु
			अगर (rinfo->mon1_type != MT_NONE)
				अगर (!radeon_probe_i2c_connector(rinfo, ddc_dvi, &rinfo->mon1_EDID)) अणु
					radeon_probe_i2c_connector(rinfo, ddc_crt2, &rinfo->mon1_EDID);
					ddc_crt2_used = 1;
				पूर्ण
			अगर (rinfo->mon2_type != MT_NONE)
				अगर (!radeon_probe_i2c_connector(rinfo, ddc_vga, &rinfo->mon2_EDID) &&
				    !ddc_crt2_used)
					radeon_probe_i2c_connector(rinfo, ddc_crt2, &rinfo->mon2_EDID);
		पूर्ण
#पूर्ण_अगर /* CONFIG_FB_RADEON_I2C */
		अगर (rinfo->mon1_type == MT_NONE) अणु
			अगर (rinfo->mon2_type != MT_NONE) अणु
				rinfo->mon1_type = rinfo->mon2_type;
				rinfo->mon1_EDID = rinfo->mon2_EDID;
			पूर्ण अन्यथा अणु
				rinfo->mon1_type = MT_CRT;
				prपूर्णांकk(KERN_INFO "radeonfb: No valid monitor, assuming CRT on first port\n");
			पूर्ण
			rinfo->mon2_type = MT_NONE;
			rinfo->mon2_EDID = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Auto-detecting display type (well... trying to ...)
		 */
		
		pr_debug("Starting monitor auto detection...\n");

#अगर defined(DEBUG) && defined(CONFIG_FB_RADEON_I2C)
		अणु
			u8 *EDIDs[4] = अणु शून्य, शून्य, शून्य, शून्य पूर्ण;
			पूर्णांक i;

			क्रम (i = 0; i < 4; i++)
				radeon_probe_i2c_connector(rinfo, i + 1, &EDIDs[i]);
		पूर्ण
#पूर्ण_अगर /* DEBUG */
		/*
		 * Old single head cards
		 */
		अगर (!rinfo->has_CRTC2) अणु
#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
			अगर (rinfo->mon1_type == MT_NONE)
				rinfo->mon1_type = radeon_probe_OF_head(rinfo, 0,
									&rinfo->mon1_EDID);
#पूर्ण_अगर /* CONFIG_PPC || CONFIG_SPARC */
#अगर_घोषित CONFIG_FB_RADEON_I2C
			अगर (rinfo->mon1_type == MT_NONE)
				rinfo->mon1_type =
					radeon_probe_i2c_connector(rinfo, ddc_dvi,
								   &rinfo->mon1_EDID);
			अगर (rinfo->mon1_type == MT_NONE)
				rinfo->mon1_type =
					radeon_probe_i2c_connector(rinfo, ddc_vga,
								   &rinfo->mon1_EDID);
			अगर (rinfo->mon1_type == MT_NONE)
				rinfo->mon1_type =
					radeon_probe_i2c_connector(rinfo, ddc_crt2,
								   &rinfo->mon1_EDID);	
#पूर्ण_अगर /* CONFIG_FB_RADEON_I2C */
			अगर (rinfo->mon1_type == MT_NONE)
				rinfo->mon1_type = MT_CRT;
			जाओ bail;
		पूर्ण

		/*
		 * Check क्रम cards with reversed DACs or TMDS controllers using BIOS
		 */
		अगर (rinfo->bios_seg &&
		    (पंचांगp = BIOS_IN16(rinfo->fp_bios_start + 0x50))) अणु
			क्रम (i = 1; i < 4; i++) अणु
				अचिन्हित पूर्णांक पंचांगp0;

				अगर (!BIOS_IN8(पंचांगp + i*2) && i > 1)
					अवरोध;
				पंचांगp0 = BIOS_IN16(पंचांगp + i*2);
				अगर ((!(पंचांगp0 & 0x01)) && (((पंचांगp0 >> 8) & 0x0f) == ddc_dvi)) अणु
					rinfo->reversed_DAC = 1;
					prपूर्णांकk(KERN_INFO "radeonfb: Reversed DACs detected\n");
				पूर्ण
				अगर ((((पंचांगp0 >> 8) & 0x0f) == ddc_dvi) && ((पंचांगp0 >> 4) & 0x01)) अणु
					rinfo->reversed_TMDS = 1;
					prपूर्णांकk(KERN_INFO "radeonfb: Reversed TMDS detected\n");
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * Probe primary head (DVI or laptop पूर्णांकernal panel)
		 */
#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
		अगर (rinfo->mon1_type == MT_NONE)
			rinfo->mon1_type = radeon_probe_OF_head(rinfo, 0,
								&rinfo->mon1_EDID);
#पूर्ण_अगर /* CONFIG_PPC || CONFIG_SPARC */
#अगर_घोषित CONFIG_FB_RADEON_I2C
		अगर (rinfo->mon1_type == MT_NONE)
			rinfo->mon1_type = radeon_probe_i2c_connector(rinfo, ddc_dvi,
								      &rinfo->mon1_EDID);
		अगर (rinfo->mon1_type == MT_NONE) अणु
			rinfo->mon1_type = radeon_probe_i2c_connector(rinfo, ddc_crt2,
								      &rinfo->mon1_EDID);
			अगर (rinfo->mon1_type != MT_NONE)
				ddc_crt2_used = 1;
		पूर्ण
#पूर्ण_अगर /* CONFIG_FB_RADEON_I2C */
		अगर (rinfo->mon1_type == MT_NONE && rinfo->is_mobility &&
		    ((rinfo->bios_seg && (INREG(BIOS_4_SCRATCH) & 4))
		     || (INREG(LVDS_GEN_CNTL) & LVDS_ON))) अणु
			rinfo->mon1_type = MT_LCD;
			prपूर्णांकk("Non-DDC laptop panel detected\n");
		पूर्ण
		अगर (rinfo->mon1_type == MT_NONE)
			rinfo->mon1_type = radeon_crt_is_connected(rinfo, rinfo->reversed_DAC);

		/*
		 * Probe secondary head (mostly VGA, can be DVI)
		 */
#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
		अगर (rinfo->mon2_type == MT_NONE)
			rinfo->mon2_type = radeon_probe_OF_head(rinfo, 1,
								&rinfo->mon2_EDID);
#पूर्ण_अगर /* CONFIG_PPC || defined(CONFIG_SPARC) */
#अगर_घोषित CONFIG_FB_RADEON_I2C
		अगर (rinfo->mon2_type == MT_NONE)
			rinfo->mon2_type = radeon_probe_i2c_connector(rinfo, ddc_vga,
								      &rinfo->mon2_EDID);
		अगर (rinfo->mon2_type == MT_NONE && !ddc_crt2_used)
			rinfo->mon2_type = radeon_probe_i2c_connector(rinfo, ddc_crt2,
								      &rinfo->mon2_EDID);
#पूर्ण_अगर /* CONFIG_FB_RADEON_I2C */
		अगर (rinfo->mon2_type == MT_NONE)
			rinfo->mon2_type = radeon_crt_is_connected(rinfo, !rinfo->reversed_DAC);

		/*
		 * If we only detected port 2, we swap them, अगर none detected,
		 * assume CRT (maybe fallback to old BIOS_SCRATCH stuff ? or look
		 * at FP रेजिस्टरs ?)
		 */
		अगर (rinfo->mon1_type == MT_NONE) अणु
			अगर (rinfo->mon2_type != MT_NONE) अणु
				rinfo->mon1_type = rinfo->mon2_type;
				rinfo->mon1_EDID = rinfo->mon2_EDID;
			पूर्ण अन्यथा
				rinfo->mon1_type = MT_CRT;
			rinfo->mon2_type = MT_NONE;
			rinfo->mon2_EDID = शून्य;
		पूर्ण

		/*
		 * Deal with reversed TMDS
		 */
		अगर (rinfo->reversed_TMDS) अणु
			/* Always keep पूर्णांकernal TMDS as primary head */
			अगर (rinfo->mon1_type == MT_DFP || rinfo->mon2_type == MT_DFP) अणु
				पूर्णांक पंचांगp_type = rinfo->mon1_type;
				u8 *पंचांगp_EDID = rinfo->mon1_EDID;
				rinfo->mon1_type = rinfo->mon2_type;
				rinfo->mon1_EDID = rinfo->mon2_EDID;
				rinfo->mon2_type = पंचांगp_type;
				rinfo->mon2_EDID = पंचांगp_EDID;
				अगर (rinfo->mon1_type == MT_CRT || rinfo->mon2_type == MT_CRT)
					rinfo->reversed_DAC ^= 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ignore_edid) अणु
		kमुक्त(rinfo->mon1_EDID);
		rinfo->mon1_EDID = शून्य;
		kमुक्त(rinfo->mon2_EDID);
		rinfo->mon2_EDID = शून्य;
	पूर्ण

 bail:
	prपूर्णांकk(KERN_INFO "radeonfb: Monitor 1 type %s found\n",
	       radeon_get_mon_name(rinfo->mon1_type));
	अगर (rinfo->mon1_EDID)
		prपूर्णांकk(KERN_INFO "radeonfb: EDID probed\n");
	अगर (!rinfo->has_CRTC2)
		वापस;
	prपूर्णांकk(KERN_INFO "radeonfb: Monitor 2 type %s found\n",
	       radeon_get_mon_name(rinfo->mon2_type));
	अगर (rinfo->mon2_EDID)
		prपूर्णांकk(KERN_INFO "radeonfb: EDID probed\n");
पूर्ण


/*
 * This function applies any arch/model/machine specअगरic fixups
 * to the panel info. It may eventually alter EDID block as
 * well or whatever is specअगरic to a given model and not probed
 * properly by the शेष code
 */
अटल व्योम radeon_fixup_panel_info(काष्ठा radeonfb_info *rinfo)
अणु
#अगर_घोषित CONFIG_PPC
	/*
	 * LCD Flat panels should use fixed भागiders, we enक्रमe that on
	 * PPC only क्रम now...
	 */
	अगर (!rinfo->panel_info.use_bios_भागiders && rinfo->mon1_type == MT_LCD
	    && rinfo->is_mobility) अणु
		पूर्णांक ppll_भाग_sel;
		u32 ppll_भागn;
		ppll_भाग_sel = INREG8(CLOCK_CNTL_INDEX + 1) & 0x3;
		radeon_pll_errata_after_index(rinfo);
		ppll_भागn = INPLL(PPLL_DIV_0 + ppll_भाग_sel);
		rinfo->panel_info.ref_भागider = rinfo->pll.ref_भाग;
		rinfo->panel_info.fbk_भागider = ppll_भागn & 0x7ff;
		rinfo->panel_info.post_भागider = (ppll_भागn >> 16) & 0x7;
		rinfo->panel_info.use_bios_भागiders = 1;

		prपूर्णांकk(KERN_DEBUG "radeonfb: Using Firmware dividers 0x%08x "
		       "from PPLL %d\n",
		       rinfo->panel_info.fbk_भागider |
		       (rinfo->panel_info.post_भागider << 16),
		       ppll_भाग_sel);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC */
पूर्ण


/*
 * Fill up panel infos from a mode definition, either वापसed by the EDID
 * or from the शेष mode when we can't करो any better
 */
अटल व्योम radeon_var_to_panel_info(काष्ठा radeonfb_info *rinfo, काष्ठा fb_var_screeninfo *var)
अणु
	rinfo->panel_info.xres = var->xres;
	rinfo->panel_info.yres = var->yres;
	rinfo->panel_info.घड़ी = 100000000 / var->pixघड़ी;
	rinfo->panel_info.hOver_plus = var->right_margin;
	rinfo->panel_info.hSync_width = var->hsync_len;
       	rinfo->panel_info.hblank = var->left_margin +
		(var->right_margin + var->hsync_len);
	rinfo->panel_info.vOver_plus = var->lower_margin;
	rinfo->panel_info.vSync_width = var->vsync_len;
       	rinfo->panel_info.vblank = var->upper_margin +
		(var->lower_margin + var->vsync_len);
	rinfo->panel_info.hAct_high =
		(var->sync & FB_SYNC_HOR_HIGH_ACT) != 0;
	rinfo->panel_info.vAct_high =
		(var->sync & FB_SYNC_VERT_HIGH_ACT) != 0;
	rinfo->panel_info.valid = 1;
	/* We use a शेष of 200ms क्रम the panel घातer delay, 
	 * I need to have a real schedule() instead of mdelay's in the panel code.
	 * we might be possible to figure out a better घातer delay either from
	 * MacOS OF tree or from the EDID block (proprietary extensions ?)
	 */
	rinfo->panel_info.pwr_delay = 200;
पूर्ण

अटल व्योम radeon_videomode_to_var(काष्ठा fb_var_screeninfo *var,
				    स्थिर काष्ठा fb_videomode *mode)
अणु
	var->xres = mode->xres;
	var->yres = mode->yres;
	var->xres_भव = mode->xres;
	var->yres_भव = mode->yres;
	var->xoffset = 0;
	var->yoffset = 0;
	var->pixघड़ी = mode->pixघड़ी;
	var->left_margin = mode->left_margin;
	var->right_margin = mode->right_margin;
	var->upper_margin = mode->upper_margin;
	var->lower_margin = mode->lower_margin;
	var->hsync_len = mode->hsync_len;
	var->vsync_len = mode->vsync_len;
	var->sync = mode->sync;
	var->vmode = mode->vmode;
पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
अटल पूर्णांक is_घातerblade(स्थिर अक्षर *model)
अणु
	काष्ठा device_node *root;
	स्थिर अक्षर* cp;
	पूर्णांक len, l, rc = 0;

	root = of_find_node_by_path("/");
	अगर (root && model) अणु
		l = म_माप(model);
		cp = of_get_property(root, "model", &len);
		अगर (cp)
			rc = स_भेद(model, cp, min(len, l)) == 0;
		of_node_put(root);
	पूर्ण
	वापस rc;
पूर्ण
#पूर्ण_अगर

/*
 * Build the modedb क्रम head 1 (head 2 will come later), check panel infos
 * from either BIOS or EDID, and pick up the शेष mode
 */
व्योम radeon_check_modes(काष्ठा radeonfb_info *rinfo, स्थिर अक्षर *mode_option)
अणु
	काष्ठा fb_info * info = rinfo->info;
	पूर्णांक has_शेष_mode = 0;

	/*
	 * Fill शेष var first
	 */
	info->var = radeonfb_शेष_var;
	INIT_LIST_HEAD(&info->modelist);

	/*
	 * First check out what BIOS has to say
	 */
	अगर (rinfo->mon1_type == MT_LCD)
		radeon_get_panel_info_BIOS(rinfo);

	/*
	 * Parse EDID detailed timings and deduce panel infos अगर any. Right now
	 * we only deal with first entry वापसed by parse_EDID, we may करो better
	 * some day...
	 */
	अगर (!rinfo->panel_info.use_bios_भागiders && rinfo->mon1_type != MT_CRT
	    && rinfo->mon1_EDID) अणु
		काष्ठा fb_var_screeninfo var;
		pr_debug("Parsing EDID data for panel info\n");
		अगर (fb_parse_edid(rinfo->mon1_EDID, &var) == 0) अणु
			अगर (var.xres >= rinfo->panel_info.xres &&
			    var.yres >= rinfo->panel_info.yres)
				radeon_var_to_panel_info(rinfo, &var);
		पूर्ण
	पूर्ण

	/*
	 * Do any additional platक्रमm/arch fixups to the panel infos
	 */
	radeon_fixup_panel_info(rinfo);

	/*
	 * If we have some valid panel infos, we setup the शेष mode based on
	 * those
	 */
	अगर (rinfo->mon1_type != MT_CRT && rinfo->panel_info.valid) अणु
		काष्ठा fb_var_screeninfo *var = &info->var;

		pr_debug("Setting up default mode based on panel info\n");
		var->xres = rinfo->panel_info.xres;
		var->yres = rinfo->panel_info.yres;
		var->xres_भव = rinfo->panel_info.xres;
		var->yres_भव = rinfo->panel_info.yres;
		var->xoffset = var->yoffset = 0;
		var->bits_per_pixel = 8;
		var->pixघड़ी = 100000000 / rinfo->panel_info.घड़ी;
		var->left_margin = (rinfo->panel_info.hblank - rinfo->panel_info.hOver_plus
				    - rinfo->panel_info.hSync_width);
		var->right_margin = rinfo->panel_info.hOver_plus;
		var->upper_margin = (rinfo->panel_info.vblank - rinfo->panel_info.vOver_plus
				     - rinfo->panel_info.vSync_width);
		var->lower_margin = rinfo->panel_info.vOver_plus;
		var->hsync_len = rinfo->panel_info.hSync_width;
		var->vsync_len = rinfo->panel_info.vSync_width;
		var->sync = 0;
		अगर (rinfo->panel_info.hAct_high)
			var->sync |= FB_SYNC_HOR_HIGH_ACT;
		अगर (rinfo->panel_info.vAct_high)
			var->sync |= FB_SYNC_VERT_HIGH_ACT;
		var->vmode = 0;
		has_शेष_mode = 1;
	पूर्ण

	/*
	 * Now build modedb from EDID
	 */
	अगर (rinfo->mon1_EDID) अणु
		fb_edid_to_monspecs(rinfo->mon1_EDID, &info->monspecs);
		fb_videomode_to_modelist(info->monspecs.modedb,
					 info->monspecs.modedb_len,
					 &info->modelist);
		rinfo->mon1_modedb = info->monspecs.modedb;
		rinfo->mon1_dbsize = info->monspecs.modedb_len;
	पूर्ण

	
	/*
	 * Finally, अगर we करोn't have panel infos we need to figure some (or
	 * we try to पढ़ो it from card), we try to pick a शेष mode
	 * and create some panel infos. Whatever...
	 */
	अगर (rinfo->mon1_type != MT_CRT && !rinfo->panel_info.valid) अणु
		काष्ठा fb_videomode	*modedb;
		पूर्णांक			dbsize;
		अक्षर			modename[32];

		pr_debug("Guessing panel info...\n");
		अगर (rinfo->panel_info.xres == 0 || rinfo->panel_info.yres == 0) अणु
			u32 पंचांगp = INREG(FP_HORZ_STRETCH) & HORZ_PANEL_SIZE;
			rinfo->panel_info.xres = ((पंचांगp >> HORZ_PANEL_SHIFT) + 1) * 8;
			पंचांगp = INREG(FP_VERT_STRETCH) & VERT_PANEL_SIZE;
			rinfo->panel_info.yres = (पंचांगp >> VERT_PANEL_SHIFT) + 1;
		पूर्ण
		अगर (rinfo->panel_info.xres == 0 || rinfo->panel_info.yres == 0) अणु
			prपूर्णांकk(KERN_WARNING "radeonfb: Can't find panel size, going back to CRT\n");
			rinfo->mon1_type = MT_CRT;
			जाओ pickup_शेष;
		पूर्ण
		prपूर्णांकk(KERN_WARNING "radeonfb: Assuming panel size %dx%d\n",
		       rinfo->panel_info.xres, rinfo->panel_info.yres);
		modedb = rinfo->mon1_modedb;
		dbsize = rinfo->mon1_dbsize;
		snम_लिखो(modename, 31, "%dx%d", rinfo->panel_info.xres, rinfo->panel_info.yres);
		अगर (fb_find_mode(&info->var, info, modename,
				 modedb, dbsize, शून्य, 8) == 0) अणु
			prपूर्णांकk(KERN_WARNING "radeonfb: Can't find mode for panel size, going back to CRT\n");
			rinfo->mon1_type = MT_CRT;
			जाओ pickup_शेष;
		पूर्ण
		has_शेष_mode = 1;
		radeon_var_to_panel_info(rinfo, &info->var);
	पूर्ण

 pickup_शेष:
	/*
	 * Apply passed-in mode option अगर any
	 */
	अगर (mode_option) अणु
		अगर (fb_find_mode(&info->var, info, mode_option,
				 info->monspecs.modedb,
				 info->monspecs.modedb_len, शून्य, 8) != 0)
			has_शेष_mode = 1;
 	पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
	अगर (!has_शेष_mode && (
		is_घातerblade("IBM,8842") || /* JS20 */
		is_घातerblade("IBM,8844") || /* JS21 */
		is_घातerblade("IBM,7998") || /* JS12/JS21/JS22 */
		is_घातerblade("IBM,0792") || /* QS21 */
		is_घातerblade("IBM,0793")    /* QS22 */
	    )) अणु
		prपूर्णांकk("Falling back to 800x600 on JSxx hardware\n");
		अगर (fb_find_mode(&info->var, info, "800x600@60",
				 info->monspecs.modedb,
				 info->monspecs.modedb_len, शून्य, 8) != 0)
			has_शेष_mode = 1;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Still no mode, let's pick up a शेष from the db
	 */
	अगर (!has_शेष_mode && info->monspecs.modedb != शून्य) अणु
		काष्ठा fb_monspecs *specs = &info->monspecs;
		काष्ठा fb_videomode *modedb = शून्य;

		/* get preferred timing */
		अगर (specs->misc & FB_MISC_1ST_DETAIL) अणु
			पूर्णांक i;

			क्रम (i = 0; i < specs->modedb_len; i++) अणु
				अगर (specs->modedb[i].flag & FB_MODE_IS_FIRST) अणु
					modedb = &specs->modedb[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* otherwise, get first mode in database */
			modedb = &specs->modedb[0];
		पूर्ण
		अगर (modedb != शून्य) अणु
			info->var.bits_per_pixel = 8;
			radeon_videomode_to_var(&info->var, modedb);
			has_शेष_mode = 1;
		पूर्ण
	पूर्ण
	अगर (1) अणु
		काष्ठा fb_videomode mode;
		/* Make sure that whatever mode got selected is actually in the
		 * modelist or the kernel may die
		 */
		fb_var_to_videomode(&mode, &info->var);
		fb_add_videomode(&mode, &info->modelist);
	पूर्ण
पूर्ण

/*
 * The code below is used to pick up a mode in check_var and
 * set_var. It should be made generic
 */

/*
 * This is used when looking क्रम modes. We assign a "distance" value
 * to a mode in the modedb depending how "close" it is from what we
 * are looking क्रम.
 * Currently, we करोn't compare that much, we could करो better but
 * the current fbcon करोesn't quite mind ;)
 */
अटल पूर्णांक radeon_compare_modes(स्थिर काष्ठा fb_var_screeninfo *var,
				स्थिर काष्ठा fb_videomode *mode)
अणु
	पूर्णांक distance = 0;

	distance = mode->yres - var->yres;
	distance += (mode->xres - var->xres)/2;
	वापस distance;
पूर्ण

/*
 * This function is called by check_var, it माला_लो the passed in mode parameter, and
 * outमाला_दो a valid mode matching the passed-in one as बंदly as possible.
 * We need something better ultimately. Things like fbcon basically pass us out
 * current mode with xres/yres hacked, जबतक things like XFree will actually
 * produce a full timing that we should respect as much as possible.
 *
 * This is why I added the FB_ACTIVATE_FIND that is used by fbcon. Without this,
 * we करो a simple spec match, that's all. With it, we actually look क्रम a mode in
 * either our monitor modedb or the vesa one अगर none
 *
 */
पूर्णांक  radeon_match_mode(काष्ठा radeonfb_info *rinfo,
		       काष्ठा fb_var_screeninfo *dest,
		       स्थिर काष्ठा fb_var_screeninfo *src)
अणु
	स्थिर काष्ठा fb_videomode	*db = vesa_modes;
	पूर्णांक				i, dbsize = 34;
	पूर्णांक				has_rmx, native_db = 0;
	पूर्णांक				distance = पूर्णांक_उच्च;
	स्थिर काष्ठा fb_videomode	*candidate = शून्य;

	/* Start with a copy of the requested mode */
	स_नकल(dest, src, माप(काष्ठा fb_var_screeninfo));

	/* Check अगर we have a modedb built from EDID */
	अगर (rinfo->mon1_modedb) अणु
		db = rinfo->mon1_modedb;
		dbsize = rinfo->mon1_dbsize;
		native_db = 1;
	पूर्ण

	/* Check अगर we have a scaler allowing any fancy mode */
	has_rmx = rinfo->mon1_type == MT_LCD || rinfo->mon1_type == MT_DFP;

	/* If we have a scaler and are passed FB_ACTIVATE_TEST or
	 * FB_ACTIVATE_NOW, just करो basic checking and वापस अगर the
	 * mode match
	 */
	अगर ((src->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_TEST ||
	    (src->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW) अणु
		/* We करोn't have an RMX, validate timings. If we don't have
	 	 * monspecs, we should be paranoid and not let use go above
		 * 640x480-60, but I assume userland knows what it's करोing here
		 * (though I may be proven wrong...)
		 */
		अगर (has_rmx == 0 && rinfo->mon1_modedb)
			अगर (fb_validate_mode((काष्ठा fb_var_screeninfo *)src, rinfo->info))
				वापस -EINVAL;
		वापस 0;
	पूर्ण

	/* Now look क्रम a mode in the database */
	जबतक (db) अणु
		क्रम (i = 0; i < dbsize; i++) अणु
			पूर्णांक d;

			अगर (db[i].yres < src->yres)
				जारी;	
			अगर (db[i].xres < src->xres)
				जारी;
			d = radeon_compare_modes(src, &db[i]);
			/* If the new mode is at least as good as the previous one,
			 * then it's our new candidate
			 */
			अगर (d < distance) अणु
				candidate = &db[i];
				distance = d;
			पूर्ण
		पूर्ण
		db = शून्य;
		/* If we have a scaler, we allow any mode from the database */
		अगर (native_db && has_rmx) अणु
			db = vesa_modes;
			dbsize = 34;
			native_db = 0;
		पूर्ण
	पूर्ण

	/* If we have found a match, वापस it */
	अगर (candidate != शून्य) अणु
		radeon_videomode_to_var(dest, candidate);
		वापस 0;
	पूर्ण

	/* If we haven't and don't have a scaler, fail */
	अगर (!has_rmx)
		वापस -EINVAL;

	वापस 0;
पूर्ण
