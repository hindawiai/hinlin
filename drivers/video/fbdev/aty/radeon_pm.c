<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	drivers/video/aty/radeon_pm.c
 *
 *	Copyright 2003,2004 Ben. Herrenschmidt <benh@kernel.crashing.org>
 *	Copyright 2004 Paul Mackerras <paulus@samba.org>
 *
 *	This is the घातer management code क्रम ATI radeon chipsets. It contains
 *	some dynamic घड़ी PM enable/disable code similar to what X.org करोes,
 *	some D2-state (APM-style) sleep/wakeup code क्रम use on some PowerMacs,
 *	and the necessary bits to re-initialize from scratch a few chips found
 *	on PowerMacs as well. The later could be extended to more platक्रमms
 *	provided the memory controller configuration code be made more generic,
 *	and you can get the proper mode रेजिस्टर commands क्रम your RAMs.
 *	Those things may be found in the BIOS image...
 */

#समावेश "radeonfb.h"

#समावेश <linux/console.h>
#समावेश <linux/agp_backend.h>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmac_feature.h>
#पूर्ण_अगर

#समावेश "ati_ids.h"

/*
 * Workarounds क्रम bugs in PC laptops:
 * - enable D2 sleep in some IBM Thinkpads
 * - special हाल क्रम Samsung P35
 *
 * Whitelist by subप्रणाली venकरोr/device because
 * its the subप्रणाली venकरोr's fault!
 */

#अगर defined(CONFIG_PM) && defined(CONFIG_X86)
अटल व्योम radeon_reinitialize_M10(काष्ठा radeonfb_info *rinfo);

काष्ठा radeon_device_id अणु
        स्थिर अक्षर *ident;                     /* (arbitrary) Name */
        स्थिर अचिन्हित लघु subप्रणाली_venकरोr; /* Subप्रणाली Venकरोr ID */
        स्थिर अचिन्हित लघु subप्रणाली_device; /* Subप्रणाली Device ID */
	स्थिर क्रमागत radeon_pm_mode pm_mode_modअगरier; /* modअगरy pm_mode */
	स्थिर reinit_function_ptr new_reinit_func;   /* changed reinit_func */
पूर्ण;

#घोषणा BUGFIX(model, sv, sd, pm, fn) अणु \
	.ident = model, \
	.subप्रणाली_venकरोr = sv, \
	.subप्रणाली_device = sd, \
	.pm_mode_modअगरier = pm, \
	.new_reinit_func  = fn  \
पूर्ण

अटल काष्ठा radeon_device_id radeon_workaround_list[] = अणु
	BUGFIX("IBM Thinkpad R32",
	       PCI_VENDOR_ID_IBM, 0x1905,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad R40",
	       PCI_VENDOR_ID_IBM, 0x0526,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad R40",
	       PCI_VENDOR_ID_IBM, 0x0527,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad R50/R51/T40/T41",
	       PCI_VENDOR_ID_IBM, 0x0531,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad R51/T40/T41/T42",
	       PCI_VENDOR_ID_IBM, 0x0530,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad T30",
	       PCI_VENDOR_ID_IBM, 0x0517,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad T40p",
	       PCI_VENDOR_ID_IBM, 0x054d,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad T42",
	       PCI_VENDOR_ID_IBM, 0x0550,
	       radeon_pm_d2, शून्य),
	BUGFIX("IBM Thinkpad X31/X32",
	       PCI_VENDOR_ID_IBM, 0x052f,
	       radeon_pm_d2, शून्य),
	BUGFIX("Samsung P35",
	       PCI_VENDOR_ID_SAMSUNG, 0xc00c,
	       radeon_pm_off, radeon_reinitialize_M10),
	BUGFIX("Acer Aspire 2010",
	       PCI_VENDOR_ID_AI, 0x0061,
	       radeon_pm_off, radeon_reinitialize_M10),
	BUGFIX("Acer Travelmate 290D/292LMi",
	       PCI_VENDOR_ID_AI, 0x005a,
	       radeon_pm_off, radeon_reinitialize_M10),
	अणु .ident = शून्य पूर्ण
पूर्ण;

अटल पूर्णांक radeon_apply_workarounds(काष्ठा radeonfb_info *rinfo)
अणु
	काष्ठा radeon_device_id *id;

	क्रम (id = radeon_workaround_list; id->ident != शून्य; id++ )
		अगर ((id->subप्रणाली_venकरोr == rinfo->pdev->subप्रणाली_venकरोr ) &&
		    (id->subप्रणाली_device == rinfo->pdev->subप्रणाली_device )) अणु

			/* we found a device that requires workaround */
			prपूर्णांकk(KERN_DEBUG "radeonfb: %s detected"
			       ", enabling workaround\n", id->ident);

			rinfo->pm_mode |= id->pm_mode_modअगरier;

			अगर (id->new_reinit_func != शून्य)
				rinfo->reinit_func = id->new_reinit_func;

			वापस 1;
		पूर्ण
	वापस 0;  /* not found */
पूर्ण

#अन्यथा  /* defined(CONFIG_PM) && defined(CONFIG_X86) */
अटल अंतरभूत पूर्णांक radeon_apply_workarounds(काष्ठा radeonfb_info *rinfo)
अणु
        वापस 0;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_PM) && defined(CONFIG_X86) */



अटल व्योम radeon_pm_disable_dynamic_mode(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp;

	/* RV100 */
	अगर ((rinfo->family == CHIP_FAMILY_RV100) && (!rinfo->is_mobility)) अणु
		अगर (rinfo->has_CRTC2) अणु
			पंचांगp = INPLL(pllSCLK_CNTL);
			पंचांगp &= ~SCLK_CNTL__DYN_STOP_LAT_MASK;
			पंचांगp |= SCLK_CNTL__CP_MAX_DYN_STOP_LAT | SCLK_CNTL__FORCEON_MASK;
			OUTPLL(pllSCLK_CNTL, पंचांगp);
		पूर्ण
		पंचांगp = INPLL(pllMCLK_CNTL);
		पंचांगp |= (MCLK_CNTL__FORCE_MCLKA |
		        MCLK_CNTL__FORCE_MCLKB |
		        MCLK_CNTL__FORCE_YCLKA |
		        MCLK_CNTL__FORCE_YCLKB |
			MCLK_CNTL__FORCE_AIC |
			MCLK_CNTL__FORCE_MC);
                OUTPLL(pllMCLK_CNTL, पंचांगp);
		वापस;
	पूर्ण
	/* R100 */
	अगर (!rinfo->has_CRTC2) अणु
                पंचांगp = INPLL(pllSCLK_CNTL);
                पंचांगp |= (SCLK_CNTL__FORCE_CP	| SCLK_CNTL__FORCE_HDP	|
			SCLK_CNTL__FORCE_DISP1	| SCLK_CNTL__FORCE_TOP	|
                        SCLK_CNTL__FORCE_E2	| SCLK_CNTL__FORCE_SE 	|
			SCLK_CNTL__FORCE_IDCT	| SCLK_CNTL__FORCE_VIP	|
			SCLK_CNTL__FORCE_RE	| SCLK_CNTL__FORCE_PB 	|
			SCLK_CNTL__FORCE_TAM	| SCLK_CNTL__FORCE_TDM	|
                        SCLK_CNTL__FORCE_RB);
                OUTPLL(pllSCLK_CNTL, पंचांगp);
		वापस;
	पूर्ण
	/* RV350 (M10/M11) */
	अगर (rinfo->family == CHIP_FAMILY_RV350) अणु
                /* क्रम RV350/M10/M11, no delays are required. */
                पंचांगp = INPLL(pllSCLK_CNTL2);
                पंचांगp |= (SCLK_CNTL2__R300_FORCE_TCL |
                        SCLK_CNTL2__R300_FORCE_GA  |
			SCLK_CNTL2__R300_FORCE_CBA);
                OUTPLL(pllSCLK_CNTL2, पंचांगp);

                पंचांगp = INPLL(pllSCLK_CNTL);
                पंचांगp |= (SCLK_CNTL__FORCE_DISP2		| SCLK_CNTL__FORCE_CP		|
                        SCLK_CNTL__FORCE_HDP		| SCLK_CNTL__FORCE_DISP1	|
                        SCLK_CNTL__FORCE_TOP		| SCLK_CNTL__FORCE_E2		|
                        SCLK_CNTL__R300_FORCE_VAP	| SCLK_CNTL__FORCE_IDCT    	|
			SCLK_CNTL__FORCE_VIP		| SCLK_CNTL__R300_FORCE_SR	|
			SCLK_CNTL__R300_FORCE_PX	| SCLK_CNTL__R300_FORCE_TX	|
			SCLK_CNTL__R300_FORCE_US	| SCLK_CNTL__FORCE_TV_SCLK	|
                        SCLK_CNTL__R300_FORCE_SU	| SCLK_CNTL__FORCE_OV0);
                OUTPLL(pllSCLK_CNTL, पंचांगp);

                पंचांगp = INPLL(pllSCLK_MORE_CNTL);
		पंचांगp |= (SCLK_MORE_CNTL__FORCE_DISPREGS	| SCLK_MORE_CNTL__FORCE_MC_GUI	|
			SCLK_MORE_CNTL__FORCE_MC_HOST);
                OUTPLL(pllSCLK_MORE_CNTL, पंचांगp);

		पंचांगp = INPLL(pllMCLK_CNTL);
		पंचांगp |= (MCLK_CNTL__FORCE_MCLKA |
		        MCLK_CNTL__FORCE_MCLKB |
		        MCLK_CNTL__FORCE_YCLKA |
		        MCLK_CNTL__FORCE_YCLKB |
			MCLK_CNTL__FORCE_MC);
                OUTPLL(pllMCLK_CNTL, पंचांगp);

                पंचांगp = INPLL(pllVCLK_ECP_CNTL);
                पंचांगp &= ~(VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb  |
                         VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb |
			 VCLK_ECP_CNTL__R300_DISP_DAC_PIXCLK_DAC_BLANK_OFF);
                OUTPLL(pllVCLK_ECP_CNTL, पंचांगp);

                पंचांगp = INPLL(pllPIXCLKS_CNTL);
                पंचांगp &= ~(PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb		|
			 PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb	|
			 PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb		|
			 PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb	|
			 PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb		|
			 PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb		|
			 PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb	|
			 PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb	|
			 PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb		|
			 PIXCLKS_CNTL__R300_DISP_DAC_PIXCLK_DAC2_BLANK_OFF);
                OUTPLL(pllPIXCLKS_CNTL, पंचांगp);

		वापस;
	पूर्ण
	
	/* Default */

	/* Force Core Clocks */
	पंचांगp = INPLL(pllSCLK_CNTL);
	पंचांगp |= (SCLK_CNTL__FORCE_CP | SCLK_CNTL__FORCE_E2);

	/* XFree करोesn't करो that हाल, but we had this code from Apple and it
	 * seem necessary क्रम proper suspend/resume operations
	 */
	अगर (rinfo->is_mobility) अणु
		पंचांगp |= 	SCLK_CNTL__FORCE_HDP|
			SCLK_CNTL__FORCE_DISP1|
			SCLK_CNTL__FORCE_DISP2|
			SCLK_CNTL__FORCE_TOP|
			SCLK_CNTL__FORCE_SE|
			SCLK_CNTL__FORCE_IDCT|
			SCLK_CNTL__FORCE_VIP|
			SCLK_CNTL__FORCE_PB|
			SCLK_CNTL__FORCE_RE|
			SCLK_CNTL__FORCE_TAM|
			SCLK_CNTL__FORCE_TDM|
			SCLK_CNTL__FORCE_RB|
			SCLK_CNTL__FORCE_TV_SCLK|
			SCLK_CNTL__FORCE_SUBPIC|
			SCLK_CNTL__FORCE_OV0;
	पूर्ण
	अन्यथा अगर (rinfo->family == CHIP_FAMILY_R300 ||
		   rinfo->family == CHIP_FAMILY_R350) अणु
		पंचांगp |=  SCLK_CNTL__FORCE_HDP   |
			SCLK_CNTL__FORCE_DISP1 |
			SCLK_CNTL__FORCE_DISP2 |
			SCLK_CNTL__FORCE_TOP   |
			SCLK_CNTL__FORCE_IDCT  |
			SCLK_CNTL__FORCE_VIP;
	पूर्ण
    	OUTPLL(pllSCLK_CNTL, पंचांगp);
	radeon_msleep(16);

	अगर (rinfo->family == CHIP_FAMILY_R300 || rinfo->family == CHIP_FAMILY_R350) अणु
		पंचांगp = INPLL(pllSCLK_CNTL2);
		पंचांगp |=  SCLK_CNTL2__R300_FORCE_TCL |
			SCLK_CNTL2__R300_FORCE_GA  |
			SCLK_CNTL2__R300_FORCE_CBA;
		OUTPLL(pllSCLK_CNTL2, पंचांगp);
		radeon_msleep(16);
	पूर्ण

	पंचांगp = INPLL(pllCLK_PIN_CNTL);
	पंचांगp &= ~CLK_PIN_CNTL__SCLK_DYN_START_CNTL;
	OUTPLL(pllCLK_PIN_CNTL, पंचांगp);
	radeon_msleep(15);

	अगर (rinfo->is_IGP) अणु
		/* Weird  ... X is _un_ क्रमcing घड़ीs here, I think it's
		 * करोing backward. Imitate it क्रम now...
		 */
		पंचांगp = INPLL(pllMCLK_CNTL);
		पंचांगp &= ~(MCLK_CNTL__FORCE_MCLKA |
			 MCLK_CNTL__FORCE_YCLKA);
		OUTPLL(pllMCLK_CNTL, पंचांगp);
		radeon_msleep(16);
	पूर्ण
	/* Hrm... same shit, X करोesn't करो that but I have to */
	अन्यथा अगर (rinfo->is_mobility) अणु
		पंचांगp = INPLL(pllMCLK_CNTL);
		पंचांगp |= (MCLK_CNTL__FORCE_MCLKA |
			MCLK_CNTL__FORCE_MCLKB |
			MCLK_CNTL__FORCE_YCLKA |
			MCLK_CNTL__FORCE_YCLKB);
		OUTPLL(pllMCLK_CNTL, पंचांगp);
		radeon_msleep(16);

		पंचांगp = INPLL(pllMCLK_MISC);
		पंचांगp &= 	~(MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT|
			  MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT|
			  MCLK_MISC__MC_MCLK_DYN_ENABLE|
			  MCLK_MISC__IO_MCLK_DYN_ENABLE);
		OUTPLL(pllMCLK_MISC, पंचांगp);
		radeon_msleep(15);
	पूर्ण

	अगर (rinfo->is_mobility) अणु
		पंचांगp = INPLL(pllSCLK_MORE_CNTL);
		पंचांगp |= 	SCLK_MORE_CNTL__FORCE_DISPREGS|
			SCLK_MORE_CNTL__FORCE_MC_GUI|
			SCLK_MORE_CNTL__FORCE_MC_HOST;
		OUTPLL(pllSCLK_MORE_CNTL, पंचांगp);
		radeon_msleep(16);
	पूर्ण

	पंचांगp = INPLL(pllPIXCLKS_CNTL);
	पंचांगp &= ~(PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb |
		 PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb |
		 PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb|
		 PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb);
 	OUTPLL(pllPIXCLKS_CNTL, पंचांगp);
	radeon_msleep(16);

	पंचांगp = INPLL( pllVCLK_ECP_CNTL);
	पंचांगp &= ~(VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb |
		 VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb);
	OUTPLL( pllVCLK_ECP_CNTL, पंचांगp);
	radeon_msleep(16);
पूर्ण

अटल व्योम radeon_pm_enable_dynamic_mode(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp;

	/* R100 */
	अगर (!rinfo->has_CRTC2) अणु
                पंचांगp = INPLL(pllSCLK_CNTL);

		अगर ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) > CFG_ATI_REV_A13)
                    पंचांगp &= ~(SCLK_CNTL__FORCE_CP	| SCLK_CNTL__FORCE_RB);
                पंचांगp &= ~(SCLK_CNTL__FORCE_HDP		| SCLK_CNTL__FORCE_DISP1 |
			 SCLK_CNTL__FORCE_TOP		| SCLK_CNTL__FORCE_SE   |
			 SCLK_CNTL__FORCE_IDCT		| SCLK_CNTL__FORCE_RE   |
			 SCLK_CNTL__FORCE_PB		| SCLK_CNTL__FORCE_TAM  |
			 SCLK_CNTL__FORCE_TDM);
                OUTPLL(pllSCLK_CNTL, पंचांगp);
		वापस;
	पूर्ण

	/* M10/M11 */
	अगर (rinfo->family == CHIP_FAMILY_RV350) अणु
		पंचांगp = INPLL(pllSCLK_CNTL2);
		पंचांगp &= ~(SCLK_CNTL2__R300_FORCE_TCL |
			 SCLK_CNTL2__R300_FORCE_GA  |
			 SCLK_CNTL2__R300_FORCE_CBA);
		पंचांगp |=  (SCLK_CNTL2__R300_TCL_MAX_DYN_STOP_LAT |
			 SCLK_CNTL2__R300_GA_MAX_DYN_STOP_LAT  |
			 SCLK_CNTL2__R300_CBA_MAX_DYN_STOP_LAT);
		OUTPLL(pllSCLK_CNTL2, पंचांगp);

		पंचांगp = INPLL(pllSCLK_CNTL);
		पंचांगp &= ~(SCLK_CNTL__FORCE_DISP2 | SCLK_CNTL__FORCE_CP      |
			 SCLK_CNTL__FORCE_HDP   | SCLK_CNTL__FORCE_DISP1   |
			 SCLK_CNTL__FORCE_TOP   | SCLK_CNTL__FORCE_E2      |
			 SCLK_CNTL__R300_FORCE_VAP | SCLK_CNTL__FORCE_IDCT |
			 SCLK_CNTL__FORCE_VIP   | SCLK_CNTL__R300_FORCE_SR |
			 SCLK_CNTL__R300_FORCE_PX | SCLK_CNTL__R300_FORCE_TX |
			 SCLK_CNTL__R300_FORCE_US | SCLK_CNTL__FORCE_TV_SCLK |
			 SCLK_CNTL__R300_FORCE_SU | SCLK_CNTL__FORCE_OV0);
		पंचांगp |= SCLK_CNTL__DYN_STOP_LAT_MASK;
		OUTPLL(pllSCLK_CNTL, पंचांगp);

		पंचांगp = INPLL(pllSCLK_MORE_CNTL);
		पंचांगp &= ~SCLK_MORE_CNTL__FORCEON;
		पंचांगp |=  SCLK_MORE_CNTL__DISPREGS_MAX_DYN_STOP_LAT |
			SCLK_MORE_CNTL__MC_GUI_MAX_DYN_STOP_LAT |
			SCLK_MORE_CNTL__MC_HOST_MAX_DYN_STOP_LAT;
		OUTPLL(pllSCLK_MORE_CNTL, पंचांगp);

		पंचांगp = INPLL(pllVCLK_ECP_CNTL);
		पंचांगp |= (VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb |
			VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb);
		OUTPLL(pllVCLK_ECP_CNTL, पंचांगp);

		पंचांगp = INPLL(pllPIXCLKS_CNTL);
		पंचांगp |= (PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb         |
			PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb     |
			PIXCLKS_CNTL__DISP_TVOUT_PIXCLK_TV_ALWAYS_ONb |
			PIXCLKS_CNTL__R300_DVOCLK_ALWAYS_ONb            |
			PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb    |
			PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb       |
			PIXCLKS_CNTL__R300_PIXCLK_DVO_ALWAYS_ONb        |
			PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb     |
			PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb     |
			PIXCLKS_CNTL__R300_PIXCLK_TRANS_ALWAYS_ONb      |
			PIXCLKS_CNTL__R300_PIXCLK_TVO_ALWAYS_ONb        |
			PIXCLKS_CNTL__R300_P2G2CLK_ALWAYS_ONb           |
			PIXCLKS_CNTL__R300_P2G2CLK_DAC_ALWAYS_ONb);
		OUTPLL(pllPIXCLKS_CNTL, पंचांगp);

		पंचांगp = INPLL(pllMCLK_MISC);
		पंचांगp |= (MCLK_MISC__MC_MCLK_DYN_ENABLE |
			MCLK_MISC__IO_MCLK_DYN_ENABLE);
		OUTPLL(pllMCLK_MISC, पंचांगp);

		पंचांगp = INPLL(pllMCLK_CNTL);
		पंचांगp |= (MCLK_CNTL__FORCE_MCLKA | MCLK_CNTL__FORCE_MCLKB);
		पंचांगp &= ~(MCLK_CNTL__FORCE_YCLKA  |
			 MCLK_CNTL__FORCE_YCLKB  |
			 MCLK_CNTL__FORCE_MC);

		/* Some releases of vbios have set DISABLE_MC_MCLKA
		 * and DISABLE_MC_MCLKB bits in the vbios table.  Setting these
		 * bits will cause H/W hang when पढ़ोing video memory with dynamic
		 * घड़ीing enabled.
		 */
		अगर ((पंचांगp & MCLK_CNTL__R300_DISABLE_MC_MCLKA) &&
		    (पंचांगp & MCLK_CNTL__R300_DISABLE_MC_MCLKB)) अणु
			/* If both bits are set, then check the active channels */
			पंचांगp = INPLL(pllMCLK_CNTL);
			अगर (rinfo->vram_width == 64) अणु
			    अगर (INREG(MEM_CNTL) & R300_MEM_USE_CD_CH_ONLY)
				पंचांगp &= ~MCLK_CNTL__R300_DISABLE_MC_MCLKB;
			    अन्यथा
				पंचांगp &= ~MCLK_CNTL__R300_DISABLE_MC_MCLKA;
			पूर्ण अन्यथा अणु
			    पंचांगp &= ~(MCLK_CNTL__R300_DISABLE_MC_MCLKA |
				     MCLK_CNTL__R300_DISABLE_MC_MCLKB);
			पूर्ण
		पूर्ण
		OUTPLL(pllMCLK_CNTL, पंचांगp);
		वापस;
	पूर्ण

	/* R300 */
	अगर (rinfo->family == CHIP_FAMILY_R300 || rinfo->family == CHIP_FAMILY_R350) अणु
		पंचांगp = INPLL(pllSCLK_CNTL);
		पंचांगp &= ~(SCLK_CNTL__R300_FORCE_VAP);
		पंचांगp |= SCLK_CNTL__FORCE_CP;
		OUTPLL(pllSCLK_CNTL, पंचांगp);
		radeon_msleep(15);

		पंचांगp = INPLL(pllSCLK_CNTL2);
		पंचांगp &= ~(SCLK_CNTL2__R300_FORCE_TCL |
			 SCLK_CNTL2__R300_FORCE_GA  |
			 SCLK_CNTL2__R300_FORCE_CBA);
		OUTPLL(pllSCLK_CNTL2, पंचांगp);
	पूर्ण

	/* Others */

	पंचांगp = INPLL( pllCLK_PWRMGT_CNTL);
	पंचांगp &= ~(CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK|
		 CLK_PWRMGT_CNTL__DISP_DYN_STOP_LAT_MASK|
		 CLK_PWRMGT_CNTL__DYN_STOP_MODE_MASK);
	पंचांगp |= CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE_MASK |
	       (0x01 << CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT__SHIFT);
	OUTPLL( pllCLK_PWRMGT_CNTL, पंचांगp);
	radeon_msleep(15);

	पंचांगp = INPLL(pllCLK_PIN_CNTL);
	पंचांगp |= CLK_PIN_CNTL__SCLK_DYN_START_CNTL;
	OUTPLL(pllCLK_PIN_CNTL, पंचांगp);
	radeon_msleep(15);

	/* When DRI is enabled, setting DYN_STOP_LAT to zero can cause some R200
	 * to lockup अक्रमomly, leave them as set by BIOS.
	 */
	पंचांगp = INPLL(pllSCLK_CNTL);
	पंचांगp &= ~SCLK_CNTL__FORCEON_MASK;

	/*RAGE_6::A11 A12 A12N1 A13, RV250::A11 A12, R300*/
	अगर ((rinfo->family == CHIP_FAMILY_RV250 &&
	     ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) < CFG_ATI_REV_A13)) ||
	    ((rinfo->family == CHIP_FAMILY_RV100) &&
	     ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) <= CFG_ATI_REV_A13))) अणु
		पंचांगp |= SCLK_CNTL__FORCE_CP;
		पंचांगp |= SCLK_CNTL__FORCE_VIP;
	पूर्ण
	OUTPLL(pllSCLK_CNTL, पंचांगp);
	radeon_msleep(15);

	अगर ((rinfo->family == CHIP_FAMILY_RV200) ||
	    (rinfo->family == CHIP_FAMILY_RV250) ||
	    (rinfo->family == CHIP_FAMILY_RV280)) अणु
		पंचांगp = INPLL(pllSCLK_MORE_CNTL);
		पंचांगp &= ~SCLK_MORE_CNTL__FORCEON;

		/* RV200::A11 A12 RV250::A11 A12 */
		अगर (((rinfo->family == CHIP_FAMILY_RV200) ||
		     (rinfo->family == CHIP_FAMILY_RV250)) &&
		    ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) < CFG_ATI_REV_A13))
			पंचांगp |= SCLK_MORE_CNTL__FORCEON;

		OUTPLL(pllSCLK_MORE_CNTL, पंचांगp);
		radeon_msleep(15);
	पूर्ण
	

	/* RV200::A11 A12, RV250::A11 A12 */
	अगर (((rinfo->family == CHIP_FAMILY_RV200) ||
	     (rinfo->family == CHIP_FAMILY_RV250)) &&
	    ((INREG(CNFG_CNTL) & CFG_ATI_REV_ID_MASK) < CFG_ATI_REV_A13)) अणु
		पंचांगp = INPLL(pllPLL_PWRMGT_CNTL);
		पंचांगp |= PLL_PWRMGT_CNTL__TCL_BYPASS_DISABLE;
		OUTPLL(pllPLL_PWRMGT_CNTL, पंचांगp);
		radeon_msleep(15);
	पूर्ण

	पंचांगp = INPLL(pllPIXCLKS_CNTL);
	पंचांगp |=  PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb |
		PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb|
		PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb;
	OUTPLL(pllPIXCLKS_CNTL, पंचांगp);
	radeon_msleep(15);
		
	पंचांगp = INPLL(pllVCLK_ECP_CNTL);
	पंचांगp |=  VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb |
		VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb;
	OUTPLL(pllVCLK_ECP_CNTL, पंचांगp);

	/* X करोesn't करो that ... hrm, we करो on mobility && Macs */
#अगर_घोषित CONFIG_PPC
	अगर (rinfo->is_mobility) अणु
		पंचांगp  = INPLL(pllMCLK_CNTL);
		पंचांगp &= ~(MCLK_CNTL__FORCE_MCLKA |
			 MCLK_CNTL__FORCE_MCLKB |
			 MCLK_CNTL__FORCE_YCLKA |
			 MCLK_CNTL__FORCE_YCLKB);
		OUTPLL(pllMCLK_CNTL, पंचांगp);
		radeon_msleep(15);

		पंचांगp = INPLL(pllMCLK_MISC);
		पंचांगp |= 	MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT|
			MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT|
			MCLK_MISC__MC_MCLK_DYN_ENABLE|
			MCLK_MISC__IO_MCLK_DYN_ENABLE;
		OUTPLL(pllMCLK_MISC, पंचांगp);
		radeon_msleep(15);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC */
पूर्ण

#अगर_घोषित CONFIG_PM

अटल व्योम OUTMC( काष्ठा radeonfb_info *rinfo, u8 indx, u32 value)
अणु
	OUTREG( MC_IND_INDEX, indx | MC_IND_INDEX__MC_IND_WR_EN);	
	OUTREG( MC_IND_DATA, value);		
पूर्ण

अटल u32 INMC(काष्ठा radeonfb_info *rinfo, u8 indx)
अणु
	OUTREG( MC_IND_INDEX, indx);					
	वापस INREG( MC_IND_DATA);
पूर्ण

अटल व्योम radeon_pm_save_regs(काष्ठा radeonfb_info *rinfo, पूर्णांक saving_क्रम_d3)
अणु
	rinfo->save_regs[0] = INPLL(PLL_PWRMGT_CNTL);
	rinfo->save_regs[1] = INPLL(CLK_PWRMGT_CNTL);
	rinfo->save_regs[2] = INPLL(MCLK_CNTL);
	rinfo->save_regs[3] = INPLL(SCLK_CNTL);
	rinfo->save_regs[4] = INPLL(CLK_PIN_CNTL);
	rinfo->save_regs[5] = INPLL(VCLK_ECP_CNTL);
	rinfo->save_regs[6] = INPLL(PIXCLKS_CNTL);
	rinfo->save_regs[7] = INPLL(MCLK_MISC);
	rinfo->save_regs[8] = INPLL(P2PLL_CNTL);
	
	rinfo->save_regs[9] = INREG(DISP_MISC_CNTL);
	rinfo->save_regs[10] = INREG(DISP_PWR_MAN);
	rinfo->save_regs[11] = INREG(LVDS_GEN_CNTL);
	rinfo->save_regs[13] = INREG(TV_DAC_CNTL);
	rinfo->save_regs[14] = INREG(BUS_CNTL1);
	rinfo->save_regs[15] = INREG(CRTC_OFFSET_CNTL);
	rinfo->save_regs[16] = INREG(AGP_CNTL);
	rinfo->save_regs[17] = (INREG(CRTC_GEN_CNTL) & 0xfdffffff) | 0x04000000;
	rinfo->save_regs[18] = (INREG(CRTC2_GEN_CNTL) & 0xfdffffff) | 0x04000000;
	rinfo->save_regs[19] = INREG(GPIOPAD_A);
	rinfo->save_regs[20] = INREG(GPIOPAD_EN);
	rinfo->save_regs[21] = INREG(GPIOPAD_MASK);
	rinfo->save_regs[22] = INREG(ZV_LCDPAD_A);
	rinfo->save_regs[23] = INREG(ZV_LCDPAD_EN);
	rinfo->save_regs[24] = INREG(ZV_LCDPAD_MASK);
	rinfo->save_regs[25] = INREG(GPIO_VGA_DDC);
	rinfo->save_regs[26] = INREG(GPIO_DVI_DDC);
	rinfo->save_regs[27] = INREG(GPIO_MONID);
	rinfo->save_regs[28] = INREG(GPIO_CRT2_DDC);

	rinfo->save_regs[29] = INREG(SURFACE_CNTL);
	rinfo->save_regs[30] = INREG(MC_FB_LOCATION);
	rinfo->save_regs[31] = INREG(DISPLAY_BASE_ADDR);
	rinfo->save_regs[32] = INREG(MC_AGP_LOCATION);
	rinfo->save_regs[33] = INREG(CRTC2_DISPLAY_BASE_ADDR);

	rinfo->save_regs[34] = INPLL(SCLK_MORE_CNTL);
	rinfo->save_regs[35] = INREG(MEM_SDRAM_MODE_REG);
	rinfo->save_regs[36] = INREG(BUS_CNTL);
	rinfo->save_regs[39] = INREG(RBBM_CNTL);
	rinfo->save_regs[40] = INREG(DAC_CNTL);
	rinfo->save_regs[41] = INREG(HOST_PATH_CNTL);
	rinfo->save_regs[37] = INREG(MPP_TB_CONFIG);
	rinfo->save_regs[38] = INREG(FCP_CNTL);

	अगर (rinfo->is_mobility) अणु
		rinfo->save_regs[12] = INREG(LVDS_PLL_CNTL);
		rinfo->save_regs[43] = INPLL(pllSSPLL_CNTL);
		rinfo->save_regs[44] = INPLL(pllSSPLL_REF_DIV);
		rinfo->save_regs[45] = INPLL(pllSSPLL_DIV_0);
		rinfo->save_regs[90] = INPLL(pllSS_INT_CNTL);
		rinfo->save_regs[91] = INPLL(pllSS_TST_CNTL);
		rinfo->save_regs[81] = INREG(LVDS_GEN_CNTL);
	पूर्ण

	अगर (rinfo->family >= CHIP_FAMILY_RV200) अणु
		rinfo->save_regs[42] = INREG(MEM_REFRESH_CNTL);
		rinfo->save_regs[46] = INREG(MC_CNTL);
		rinfo->save_regs[47] = INREG(MC_INIT_GFX_LAT_TIMER);
		rinfo->save_regs[48] = INREG(MC_INIT_MISC_LAT_TIMER);
		rinfo->save_regs[49] = INREG(MC_TIMING_CNTL);
		rinfo->save_regs[50] = INREG(MC_READ_CNTL_AB);
		rinfo->save_regs[51] = INREG(MC_IOPAD_CNTL);
		rinfo->save_regs[52] = INREG(MC_CHIP_IO_OE_CNTL_AB);
		rinfo->save_regs[53] = INREG(MC_DEBUG);
	पूर्ण
	rinfo->save_regs[54] = INREG(PAMAC0_DLY_CNTL);
	rinfo->save_regs[55] = INREG(PAMAC1_DLY_CNTL);
	rinfo->save_regs[56] = INREG(PAD_CTLR_MISC);
	rinfo->save_regs[57] = INREG(FW_CNTL);

	अगर (rinfo->family >= CHIP_FAMILY_R300) अणु
		rinfo->save_regs[58] = INMC(rinfo, ixR300_MC_MC_INIT_WR_LAT_TIMER);
		rinfo->save_regs[59] = INMC(rinfo, ixR300_MC_IMP_CNTL);
		rinfo->save_regs[60] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_C0);
		rinfo->save_regs[61] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_C1);
		rinfo->save_regs[62] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_D0);
		rinfo->save_regs[63] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_D1);
		rinfo->save_regs[64] = INMC(rinfo, ixR300_MC_BIST_CNTL_3);
		rinfo->save_regs[65] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_A0);
		rinfo->save_regs[66] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_A1);
		rinfo->save_regs[67] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_B0);
		rinfo->save_regs[68] = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_B1);
		rinfo->save_regs[69] = INMC(rinfo, ixR300_MC_DEBUG_CNTL);
		rinfo->save_regs[70] = INMC(rinfo, ixR300_MC_DLL_CNTL);
		rinfo->save_regs[71] = INMC(rinfo, ixR300_MC_IMP_CNTL_0);
		rinfo->save_regs[72] = INMC(rinfo, ixR300_MC_ELPIDA_CNTL);
		rinfo->save_regs[96] = INMC(rinfo, ixR300_MC_READ_CNTL_CD);
	पूर्ण अन्यथा अणु
		rinfo->save_regs[59] = INMC(rinfo, ixMC_IMP_CNTL);
		rinfo->save_regs[65] = INMC(rinfo, ixMC_CHP_IO_CNTL_A0);
		rinfo->save_regs[66] = INMC(rinfo, ixMC_CHP_IO_CNTL_A1);
		rinfo->save_regs[67] = INMC(rinfo, ixMC_CHP_IO_CNTL_B0);
		rinfo->save_regs[68] = INMC(rinfo, ixMC_CHP_IO_CNTL_B1);
		rinfo->save_regs[71] = INMC(rinfo, ixMC_IMP_CNTL_0);
	पूर्ण

	rinfo->save_regs[73] = INPLL(pllMPLL_CNTL);
	rinfo->save_regs[74] = INPLL(pllSPLL_CNTL);
	rinfo->save_regs[75] = INPLL(pllMPLL_AUX_CNTL);
	rinfo->save_regs[76] = INPLL(pllSPLL_AUX_CNTL);
	rinfo->save_regs[77] = INPLL(pllM_SPLL_REF_FB_DIV);
	rinfo->save_regs[78] = INPLL(pllAGP_PLL_CNTL);
	rinfo->save_regs[79] = INREG(PAMAC2_DLY_CNTL);

	rinfo->save_regs[80] = INREG(OV0_BASE_ADDR);
	rinfo->save_regs[82] = INREG(FP_GEN_CNTL);
	rinfo->save_regs[83] = INREG(FP2_GEN_CNTL);
	rinfo->save_regs[84] = INREG(TMDS_CNTL);
	rinfo->save_regs[85] = INREG(TMDS_TRANSMITTER_CNTL);
	rinfo->save_regs[86] = INREG(DISP_OUTPUT_CNTL);
	rinfo->save_regs[87] = INREG(DISP_HW_DEBUG);
	rinfo->save_regs[88] = INREG(TV_MASTER_CNTL);
	rinfo->save_regs[89] = INPLL(pllP2PLL_REF_DIV);
	rinfo->save_regs[92] = INPLL(pllPPLL_DIV_0);
	rinfo->save_regs[93] = INPLL(pllPPLL_CNTL);
	rinfo->save_regs[94] = INREG(GRPH_BUFFER_CNTL);
	rinfo->save_regs[95] = INREG(GRPH2_BUFFER_CNTL);
	rinfo->save_regs[96] = INREG(HDP_DEBUG);
	rinfo->save_regs[97] = INPLL(pllMDLL_CKO);
	rinfo->save_regs[98] = INPLL(pllMDLL_RDCKA);
	rinfo->save_regs[99] = INPLL(pllMDLL_RDCKB);
पूर्ण

अटल व्योम radeon_pm_restore_regs(काष्ठा radeonfb_info *rinfo)
अणु
	OUTPLL(P2PLL_CNTL, rinfo->save_regs[8] & 0xFFFFFFFE); /* First */
	
	OUTPLL(PLL_PWRMGT_CNTL, rinfo->save_regs[0]);
	OUTPLL(CLK_PWRMGT_CNTL, rinfo->save_regs[1]);
	OUTPLL(MCLK_CNTL, rinfo->save_regs[2]);
	OUTPLL(SCLK_CNTL, rinfo->save_regs[3]);
	OUTPLL(CLK_PIN_CNTL, rinfo->save_regs[4]);
	OUTPLL(VCLK_ECP_CNTL, rinfo->save_regs[5]);
	OUTPLL(PIXCLKS_CNTL, rinfo->save_regs[6]);
	OUTPLL(MCLK_MISC, rinfo->save_regs[7]);
	अगर (rinfo->family == CHIP_FAMILY_RV350)
		OUTPLL(SCLK_MORE_CNTL, rinfo->save_regs[34]);

	OUTREG(SURFACE_CNTL, rinfo->save_regs[29]);
	OUTREG(MC_FB_LOCATION, rinfo->save_regs[30]);
	OUTREG(DISPLAY_BASE_ADDR, rinfo->save_regs[31]);
	OUTREG(MC_AGP_LOCATION, rinfo->save_regs[32]);
	OUTREG(CRTC2_DISPLAY_BASE_ADDR, rinfo->save_regs[33]);
	OUTREG(CNFG_MEMSIZE, rinfo->video_ram);

	OUTREG(DISP_MISC_CNTL, rinfo->save_regs[9]);
	OUTREG(DISP_PWR_MAN, rinfo->save_regs[10]);
	OUTREG(LVDS_GEN_CNTL, rinfo->save_regs[11]);
	OUTREG(LVDS_PLL_CNTL,rinfo->save_regs[12]);
	OUTREG(TV_DAC_CNTL, rinfo->save_regs[13]);
	OUTREG(BUS_CNTL1, rinfo->save_regs[14]);
	OUTREG(CRTC_OFFSET_CNTL, rinfo->save_regs[15]);
	OUTREG(AGP_CNTL, rinfo->save_regs[16]);
	OUTREG(CRTC_GEN_CNTL, rinfo->save_regs[17]);
	OUTREG(CRTC2_GEN_CNTL, rinfo->save_regs[18]);
	OUTPLL(P2PLL_CNTL, rinfo->save_regs[8]);

	OUTREG(GPIOPAD_A, rinfo->save_regs[19]);
	OUTREG(GPIOPAD_EN, rinfo->save_regs[20]);
	OUTREG(GPIOPAD_MASK, rinfo->save_regs[21]);
	OUTREG(ZV_LCDPAD_A, rinfo->save_regs[22]);
	OUTREG(ZV_LCDPAD_EN, rinfo->save_regs[23]);
	OUTREG(ZV_LCDPAD_MASK, rinfo->save_regs[24]);
	OUTREG(GPIO_VGA_DDC, rinfo->save_regs[25]);
	OUTREG(GPIO_DVI_DDC, rinfo->save_regs[26]);
	OUTREG(GPIO_MONID, rinfo->save_regs[27]);
	OUTREG(GPIO_CRT2_DDC, rinfo->save_regs[28]);
पूर्ण

अटल व्योम radeon_pm_disable_iopad(काष्ठा radeonfb_info *rinfo)
अणु		
	OUTREG(GPIOPAD_MASK, 0x0001ffff);
	OUTREG(GPIOPAD_EN, 0x00000400);
	OUTREG(GPIOPAD_A, 0x00000000);		
        OUTREG(ZV_LCDPAD_MASK, 0x00000000);
        OUTREG(ZV_LCDPAD_EN, 0x00000000);
      	OUTREG(ZV_LCDPAD_A, 0x00000000); 	
	OUTREG(GPIO_VGA_DDC, 0x00030000);
	OUTREG(GPIO_DVI_DDC, 0x00000000);
	OUTREG(GPIO_MONID, 0x00030000);
	OUTREG(GPIO_CRT2_DDC, 0x00000000);
पूर्ण

अटल व्योम radeon_pm_program_v2clk(काष्ठा radeonfb_info *rinfo)
अणु
	/* Set v2clk to 65MHz */
	अगर (rinfo->family <= CHIP_FAMILY_RV280) अणु
		OUTPLL(pllPIXCLKS_CNTL,
			 __INPLL(rinfo, pllPIXCLKS_CNTL)
			 & ~PIXCLKS_CNTL__PIX2CLK_SRC_SEL_MASK);
	 
		OUTPLL(pllP2PLL_REF_DIV, 0x0000000c);
		OUTPLL(pllP2PLL_CNTL, 0x0000bf00);
	पूर्ण अन्यथा अणु
		OUTPLL(pllP2PLL_REF_DIV, 0x0000000c);
		INPLL(pllP2PLL_REF_DIV);
		OUTPLL(pllP2PLL_CNTL, 0x0000a700);
	पूर्ण

	OUTPLL(pllP2PLL_DIV_0, 0x00020074 | P2PLL_DIV_0__P2PLL_ATOMIC_UPDATE_W);
	
	OUTPLL(pllP2PLL_CNTL, INPLL(pllP2PLL_CNTL) & ~P2PLL_CNTL__P2PLL_SLEEP);
	mdelay(1);

	OUTPLL(pllP2PLL_CNTL, INPLL(pllP2PLL_CNTL) & ~P2PLL_CNTL__P2PLL_RESET);
	mdelay( 1);

  	OUTPLL(pllPIXCLKS_CNTL,
  		(INPLL(pllPIXCLKS_CNTL) & ~PIXCLKS_CNTL__PIX2CLK_SRC_SEL_MASK)
  		| (0x03 << PIXCLKS_CNTL__PIX2CLK_SRC_SEL__SHIFT));
	mdelay( 1);	
पूर्ण

अटल व्योम radeon_pm_low_current(काष्ठा radeonfb_info *rinfo)
अणु
	u32 reg;

	reg  = INREG(BUS_CNTL1);
	अगर (rinfo->family <= CHIP_FAMILY_RV280) अणु
		reg &= ~BUS_CNTL1_MOBILE_PLATFORM_SEL_MASK;
		reg |= BUS_CNTL1_AGPCLK_VALID | (1<<BUS_CNTL1_MOBILE_PLATFORM_SEL_SHIFT);
	पूर्ण अन्यथा अणु
		reg |= 0x4080;
	पूर्ण
	OUTREG(BUS_CNTL1, reg);
	
	reg  = INPLL(PLL_PWRMGT_CNTL);
	reg |= PLL_PWRMGT_CNTL_SPLL_TURNOFF | PLL_PWRMGT_CNTL_PPLL_TURNOFF |
		PLL_PWRMGT_CNTL_P2PLL_TURNOFF | PLL_PWRMGT_CNTL_TVPLL_TURNOFF;
	reg &= ~PLL_PWRMGT_CNTL_SU_MCLK_USE_BCLK;
	reg &= ~PLL_PWRMGT_CNTL_MOBILE_SU;
	OUTPLL(PLL_PWRMGT_CNTL, reg);
	
	reg  = INREG(TV_DAC_CNTL);
	reg &= ~(TV_DAC_CNTL_BGADJ_MASK |TV_DAC_CNTL_DACADJ_MASK);
	reg |=TV_DAC_CNTL_BGSLEEP | TV_DAC_CNTL_RDACPD | TV_DAC_CNTL_GDACPD |
		TV_DAC_CNTL_BDACPD |
		(8<<TV_DAC_CNTL_BGADJ__SHIFT) | (8<<TV_DAC_CNTL_DACADJ__SHIFT);
	OUTREG(TV_DAC_CNTL, reg);
	
	reg  = INREG(TMDS_TRANSMITTER_CNTL);
	reg &= ~(TMDS_PLL_EN | TMDS_PLLRST);
	OUTREG(TMDS_TRANSMITTER_CNTL, reg);

	reg = INREG(DAC_CNTL);
	reg &= ~DAC_CMP_EN;
	OUTREG(DAC_CNTL, reg);

	reg = INREG(DAC_CNTL2);
	reg &= ~DAC2_CMP_EN;
	OUTREG(DAC_CNTL2, reg);
	
	reg  = INREG(TV_DAC_CNTL);
	reg &= ~TV_DAC_CNTL_DETECT;
	OUTREG(TV_DAC_CNTL, reg);
पूर्ण

अटल व्योम radeon_pm_setup_क्रम_suspend(काष्ठा radeonfb_info *rinfo)
अणु

	u32 sclk_cntl, mclk_cntl, sclk_more_cntl;

	u32 pll_pwrmgt_cntl;
	u32 clk_pwrmgt_cntl;
	u32 clk_pin_cntl;
	u32 vclk_ecp_cntl; 
	u32 pixclks_cntl;
	u32 disp_mis_cntl;
	u32 disp_pwr_man;
	u32 पंचांगp;
	
	/* Force Core Clocks */
	sclk_cntl = INPLL( pllSCLK_CNTL);
	sclk_cntl |= 	SCLK_CNTL__IDCT_MAX_DYN_STOP_LAT|
			SCLK_CNTL__VIP_MAX_DYN_STOP_LAT|
			SCLK_CNTL__RE_MAX_DYN_STOP_LAT|
			SCLK_CNTL__PB_MAX_DYN_STOP_LAT|
			SCLK_CNTL__TAM_MAX_DYN_STOP_LAT|
			SCLK_CNTL__TDM_MAX_DYN_STOP_LAT|
			SCLK_CNTL__RB_MAX_DYN_STOP_LAT|
			
			SCLK_CNTL__FORCE_DISP2|
			SCLK_CNTL__FORCE_CP|
			SCLK_CNTL__FORCE_HDP|
			SCLK_CNTL__FORCE_DISP1|
			SCLK_CNTL__FORCE_TOP|
			SCLK_CNTL__FORCE_E2|
			SCLK_CNTL__FORCE_SE|
			SCLK_CNTL__FORCE_IDCT|
			SCLK_CNTL__FORCE_VIP|
			
			SCLK_CNTL__FORCE_PB|
			SCLK_CNTL__FORCE_TAM|
			SCLK_CNTL__FORCE_TDM|
			SCLK_CNTL__FORCE_RB|
			SCLK_CNTL__FORCE_TV_SCLK|
			SCLK_CNTL__FORCE_SUBPIC|
			SCLK_CNTL__FORCE_OV0;
	अगर (rinfo->family <= CHIP_FAMILY_RV280)
		sclk_cntl |= SCLK_CNTL__FORCE_RE;
	अन्यथा
		sclk_cntl |= SCLK_CNTL__SE_MAX_DYN_STOP_LAT |
			SCLK_CNTL__E2_MAX_DYN_STOP_LAT |
			SCLK_CNTL__TV_MAX_DYN_STOP_LAT |
			SCLK_CNTL__HDP_MAX_DYN_STOP_LAT |
			SCLK_CNTL__CP_MAX_DYN_STOP_LAT;

	OUTPLL( pllSCLK_CNTL, sclk_cntl);

	sclk_more_cntl = INPLL(pllSCLK_MORE_CNTL);
	sclk_more_cntl |= 	SCLK_MORE_CNTL__FORCE_DISPREGS |
				SCLK_MORE_CNTL__FORCE_MC_GUI |
				SCLK_MORE_CNTL__FORCE_MC_HOST;

	OUTPLL(pllSCLK_MORE_CNTL, sclk_more_cntl);		

	
	mclk_cntl = INPLL( pllMCLK_CNTL);
	mclk_cntl &= ~(	MCLK_CNTL__FORCE_MCLKA |
			MCLK_CNTL__FORCE_MCLKB |
			MCLK_CNTL__FORCE_YCLKA |
			MCLK_CNTL__FORCE_YCLKB |
			MCLK_CNTL__FORCE_MC
		      );	
    	OUTPLL( pllMCLK_CNTL, mclk_cntl);
	
	/* Force Display घड़ीs	*/
	vclk_ecp_cntl = INPLL( pllVCLK_ECP_CNTL);
	vclk_ecp_cntl &= ~(VCLK_ECP_CNTL__PIXCLK_ALWAYS_ONb
			   | VCLK_ECP_CNTL__PIXCLK_DAC_ALWAYS_ONb);
	vclk_ecp_cntl |= VCLK_ECP_CNTL__ECP_FORCE_ON;
	OUTPLL( pllVCLK_ECP_CNTL, vclk_ecp_cntl);
	
	
	pixclks_cntl = INPLL( pllPIXCLKS_CNTL);
	pixclks_cntl &= ~(	PIXCLKS_CNTL__PIXCLK_GV_ALWAYS_ONb | 
				PIXCLKS_CNTL__PIXCLK_BLEND_ALWAYS_ONb|
				PIXCLKS_CNTL__PIXCLK_DIG_TMDS_ALWAYS_ONb |
				PIXCLKS_CNTL__PIXCLK_LVDS_ALWAYS_ONb|
				PIXCLKS_CNTL__PIXCLK_TMDS_ALWAYS_ONb|
				PIXCLKS_CNTL__PIX2CLK_ALWAYS_ONb|
				PIXCLKS_CNTL__PIX2CLK_DAC_ALWAYS_ONb);
						
 	OUTPLL( pllPIXCLKS_CNTL, pixclks_cntl);

	/* Switch off LVDS पूर्णांकerface */
	OUTREG(LVDS_GEN_CNTL, INREG(LVDS_GEN_CNTL) &
	       ~(LVDS_BLON | LVDS_EN | LVDS_ON | LVDS_DIGON));

	/* Enable System घातer management */
	pll_pwrmgt_cntl = INPLL( pllPLL_PWRMGT_CNTL);
	
	pll_pwrmgt_cntl |= 	PLL_PWRMGT_CNTL__SPLL_TURNOFF |
				PLL_PWRMGT_CNTL__MPLL_TURNOFF|
				PLL_PWRMGT_CNTL__PPLL_TURNOFF|
				PLL_PWRMGT_CNTL__P2PLL_TURNOFF|
				PLL_PWRMGT_CNTL__TVPLL_TURNOFF;
						
	OUTPLL( pllPLL_PWRMGT_CNTL, pll_pwrmgt_cntl);
	
	clk_pwrmgt_cntl	 = INPLL( pllCLK_PWRMGT_CNTL);
	
	clk_pwrmgt_cntl &= ~(	CLK_PWRMGT_CNTL__MPLL_PWRMGT_OFF|
				CLK_PWRMGT_CNTL__SPLL_PWRMGT_OFF|
				CLK_PWRMGT_CNTL__PPLL_PWRMGT_OFF|
				CLK_PWRMGT_CNTL__P2PLL_PWRMGT_OFF|
				CLK_PWRMGT_CNTL__MCLK_TURNOFF|
				CLK_PWRMGT_CNTL__SCLK_TURNOFF|
				CLK_PWRMGT_CNTL__PCLK_TURNOFF|
				CLK_PWRMGT_CNTL__P2CLK_TURNOFF|
				CLK_PWRMGT_CNTL__TVPLL_PWRMGT_OFF|
				CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN|
				CLK_PWRMGT_CNTL__ENGINE_DYNCLK_MODE|
				CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK|
				CLK_PWRMGT_CNTL__CG_NO1_DEBUG_MASK
			);
						
	clk_pwrmgt_cntl |= CLK_PWRMGT_CNTL__GLOBAL_PMAN_EN
		| CLK_PWRMGT_CNTL__DISP_PM;
	
	OUTPLL( pllCLK_PWRMGT_CNTL, clk_pwrmgt_cntl);
	
	clk_pin_cntl = INPLL( pllCLK_PIN_CNTL);
	
	clk_pin_cntl &= ~CLK_PIN_CNTL__ACCESS_REGS_IN_SUSPEND;

	/* because both INPLL and OUTPLL take the same lock, that's why. */
	पंचांगp = INPLL( pllMCLK_MISC) | MCLK_MISC__EN_MCLK_TRISTATE_IN_SUSPEND;
	OUTPLL( pllMCLK_MISC, पंचांगp);

	/* BUS_CNTL1__MOBILE_PLATORM_SEL setting is northbridge chipset
	 * and radeon chip dependent. Thus we only enable it on Mac क्रम
	 * now (until we get more info on how to compute the correct
	 * value क्रम various X86 bridges).
	 */
#अगर_घोषित CONFIG_PPC_PMAC
	अगर (machine_is(घातermac)) अणु
		/* AGP PLL control */
		अगर (rinfo->family <= CHIP_FAMILY_RV280) अणु
			OUTREG(BUS_CNTL1, INREG(BUS_CNTL1) |  BUS_CNTL1__AGPCLK_VALID);
			OUTREG(BUS_CNTL1,
			       (INREG(BUS_CNTL1) & ~BUS_CNTL1__MOBILE_PLATFORM_SEL_MASK)
			       | (2<<BUS_CNTL1__MOBILE_PLATFORM_SEL__SHIFT));	// 440BX
		पूर्ण अन्यथा अणु
			OUTREG(BUS_CNTL1, INREG(BUS_CNTL1));
			OUTREG(BUS_CNTL1, (INREG(BUS_CNTL1) & ~0x4000) | 0x8000);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	OUTREG(CRTC_OFFSET_CNTL, (INREG(CRTC_OFFSET_CNTL)
				  & ~CRTC_OFFSET_CNTL__CRTC_STEREO_SYNC_OUT_EN));
	
	clk_pin_cntl &= ~CLK_PIN_CNTL__CG_CLK_TO_OUTPIN;
	clk_pin_cntl |= CLK_PIN_CNTL__XTALIN_ALWAYS_ONb;	
	OUTPLL( pllCLK_PIN_CNTL, clk_pin_cntl);

	/* Solano2M */
	OUTREG(AGP_CNTL,
		(INREG(AGP_CNTL) & ~(AGP_CNTL__MAX_IDLE_CLK_MASK))
		| (0x20<<AGP_CNTL__MAX_IDLE_CLK__SHIFT));

	/* ACPI mode */
	/* because both INPLL and OUTPLL take the same lock, that's why. */
	पंचांगp = INPLL( pllPLL_PWRMGT_CNTL) & ~PLL_PWRMGT_CNTL__PM_MODE_SEL;
	OUTPLL( pllPLL_PWRMGT_CNTL, पंचांगp);


	disp_mis_cntl = INREG(DISP_MISC_CNTL);
	
	disp_mis_cntl &= ~(	DISP_MISC_CNTL__SOFT_RESET_GRPH_PP | 
				DISP_MISC_CNTL__SOFT_RESET_SUBPIC_PP | 
				DISP_MISC_CNTL__SOFT_RESET_OV0_PP |
				DISP_MISC_CNTL__SOFT_RESET_GRPH_SCLK|
				DISP_MISC_CNTL__SOFT_RESET_SUBPIC_SCLK|
				DISP_MISC_CNTL__SOFT_RESET_OV0_SCLK|
				DISP_MISC_CNTL__SOFT_RESET_GRPH2_PP|
				DISP_MISC_CNTL__SOFT_RESET_GRPH2_SCLK|
				DISP_MISC_CNTL__SOFT_RESET_LVDS|
				DISP_MISC_CNTL__SOFT_RESET_TMDS|
				DISP_MISC_CNTL__SOFT_RESET_DIG_TMDS|
				DISP_MISC_CNTL__SOFT_RESET_TV);
	
	OUTREG(DISP_MISC_CNTL, disp_mis_cntl);
						
	disp_pwr_man = INREG(DISP_PWR_MAN);
	
	disp_pwr_man &= ~(	DISP_PWR_MAN__DISP_PWR_MAN_D3_CRTC_EN	| 
				DISP_PWR_MAN__DISP2_PWR_MAN_D3_CRTC2_EN |
				DISP_PWR_MAN__DISP_PWR_MAN_DPMS_MASK|
				DISP_PWR_MAN__DISP_D3_RST|
				DISP_PWR_MAN__DISP_D3_REG_RST
				);
	
	disp_pwr_man |= DISP_PWR_MAN__DISP_D3_GRPH_RST|
					DISP_PWR_MAN__DISP_D3_SUBPIC_RST|
					DISP_PWR_MAN__DISP_D3_OV0_RST|
					DISP_PWR_MAN__DISP_D1D2_GRPH_RST|
					DISP_PWR_MAN__DISP_D1D2_SUBPIC_RST|
					DISP_PWR_MAN__DISP_D1D2_OV0_RST|
					DISP_PWR_MAN__DIG_TMDS_ENABLE_RST|
					DISP_PWR_MAN__TV_ENABLE_RST| 
//					DISP_PWR_MAN__AUTO_PWRUP_EN|
					0;
	
	OUTREG(DISP_PWR_MAN, disp_pwr_man);					
							
	clk_pwrmgt_cntl = INPLL( pllCLK_PWRMGT_CNTL);
	pll_pwrmgt_cntl = INPLL( pllPLL_PWRMGT_CNTL) ;
	clk_pin_cntl 	= INPLL( pllCLK_PIN_CNTL);
	disp_pwr_man	= INREG(DISP_PWR_MAN);
		
	
	/* D2 */
	clk_pwrmgt_cntl |= CLK_PWRMGT_CNTL__DISP_PM;
	pll_pwrmgt_cntl |= PLL_PWRMGT_CNTL__MOBILE_SU | PLL_PWRMGT_CNTL__SU_SCLK_USE_BCLK;
	clk_pin_cntl	|= CLK_PIN_CNTL__XTALIN_ALWAYS_ONb;
	disp_pwr_man 	&= ~(DISP_PWR_MAN__DISP_PWR_MAN_D3_CRTC_EN_MASK
			     | DISP_PWR_MAN__DISP2_PWR_MAN_D3_CRTC2_EN_MASK);

	OUTPLL( pllCLK_PWRMGT_CNTL, clk_pwrmgt_cntl);
	OUTPLL( pllPLL_PWRMGT_CNTL, pll_pwrmgt_cntl);
	OUTPLL( pllCLK_PIN_CNTL, clk_pin_cntl);
	OUTREG(DISP_PWR_MAN, disp_pwr_man);

	/* disable display request & disable display */
	OUTREG( CRTC_GEN_CNTL, (INREG( CRTC_GEN_CNTL) & ~CRTC_GEN_CNTL__CRTC_EN)
		| CRTC_GEN_CNTL__CRTC_DISP_REQ_EN_B);
	OUTREG( CRTC2_GEN_CNTL, (INREG( CRTC2_GEN_CNTL) & ~CRTC2_GEN_CNTL__CRTC2_EN)
		| CRTC2_GEN_CNTL__CRTC2_DISP_REQ_EN_B);

	mdelay(17);				   

पूर्ण

अटल व्योम radeon_pm_yclk_mclk_sync(काष्ठा radeonfb_info *rinfo)
अणु
	u32 mc_chp_io_cntl_a1, mc_chp_io_cntl_b1;

	mc_chp_io_cntl_a1 = INMC( rinfo, ixMC_CHP_IO_CNTL_A1)
		& ~MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA_MASK;
	mc_chp_io_cntl_b1 = INMC( rinfo, ixMC_CHP_IO_CNTL_B1)
		& ~MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB_MASK;

	OUTMC( rinfo, ixMC_CHP_IO_CNTL_A1, mc_chp_io_cntl_a1
	       | (1<<MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA__SHIFT));
	OUTMC( rinfo, ixMC_CHP_IO_CNTL_B1, mc_chp_io_cntl_b1
	       | (1<<MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB__SHIFT));

	OUTMC( rinfo, ixMC_CHP_IO_CNTL_A1, mc_chp_io_cntl_a1);
	OUTMC( rinfo, ixMC_CHP_IO_CNTL_B1, mc_chp_io_cntl_b1);

	mdelay( 1);
पूर्ण

अटल व्योम radeon_pm_yclk_mclk_sync_m10(काष्ठा radeonfb_info *rinfo)
अणु
	u32 mc_chp_io_cntl_a1, mc_chp_io_cntl_b1;

	mc_chp_io_cntl_a1 = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_A1)
		& ~MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA_MASK;
	mc_chp_io_cntl_b1 = INMC(rinfo, ixR300_MC_CHP_IO_CNTL_B1)
		& ~MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB_MASK;

	OUTMC( rinfo, ixR300_MC_CHP_IO_CNTL_A1,
	       mc_chp_io_cntl_a1 | (1<<MC_CHP_IO_CNTL_A1__MEM_SYNC_ENA__SHIFT));
	OUTMC( rinfo, ixR300_MC_CHP_IO_CNTL_B1,
	       mc_chp_io_cntl_b1 | (1<<MC_CHP_IO_CNTL_B1__MEM_SYNC_ENB__SHIFT));

	OUTMC( rinfo, ixR300_MC_CHP_IO_CNTL_A1, mc_chp_io_cntl_a1);
	OUTMC( rinfo, ixR300_MC_CHP_IO_CNTL_B1, mc_chp_io_cntl_b1);

	mdelay( 1);
पूर्ण

अटल व्योम radeon_pm_program_mode_reg(काष्ठा radeonfb_info *rinfo, u16 value,
				       u8 delay_required)
अणु  
	u32 mem_sdram_mode;

	mem_sdram_mode  = INREG( MEM_SDRAM_MODE_REG);

	mem_sdram_mode &= ~MEM_SDRAM_MODE_REG__MEM_MODE_REG_MASK;
	mem_sdram_mode |= (value<<MEM_SDRAM_MODE_REG__MEM_MODE_REG__SHIFT)
		| MEM_SDRAM_MODE_REG__MEM_CFG_TYPE;
	OUTREG( MEM_SDRAM_MODE_REG, mem_sdram_mode);
	अगर (delay_required >= 2)
		mdelay(1);

	mem_sdram_mode |=  MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET;
	OUTREG( MEM_SDRAM_MODE_REG, mem_sdram_mode);
	अगर (delay_required >= 2)
		mdelay(1);

	mem_sdram_mode &= ~MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET;
	OUTREG( MEM_SDRAM_MODE_REG, mem_sdram_mode);
	अगर (delay_required >= 2)
		mdelay(1);

	अगर (delay_required) अणु
		करो अणु
			अगर (delay_required >= 2)
				mdelay(1);
		पूर्ण जबतक ((INREG(MC_STATUS)
			  & (MC_STATUS__MEM_PWRUP_COMPL_A |
			     MC_STATUS__MEM_PWRUP_COMPL_B)) == 0);
	पूर्ण
पूर्ण

अटल व्योम radeon_pm_m10_program_mode_रुको(काष्ठा radeonfb_info *rinfo)
अणु
	पूर्णांक cnt;

	क्रम (cnt = 0; cnt < 100; ++cnt) अणु
		mdelay(1);
		अगर (INREG(MC_STATUS) & (MC_STATUS__MEM_PWRUP_COMPL_A
					| MC_STATUS__MEM_PWRUP_COMPL_B))
			अवरोध;
	पूर्ण
पूर्ण


अटल व्योम radeon_pm_enable_dll(काष्ठा radeonfb_info *rinfo)
अणु  
#घोषणा DLL_RESET_DELAY 	5
#घोषणा DLL_SLEEP_DELAY		1

	u32 cko = INPLL(pllMDLL_CKO)   | MDLL_CKO__MCKOA_SLEEP
		| MDLL_CKO__MCKOA_RESET;
	u32 cka = INPLL(pllMDLL_RDCKA) | MDLL_RDCKA__MRDCKA0_SLEEP
		| MDLL_RDCKA__MRDCKA1_SLEEP | MDLL_RDCKA__MRDCKA0_RESET
		| MDLL_RDCKA__MRDCKA1_RESET;
	u32 ckb = INPLL(pllMDLL_RDCKB) | MDLL_RDCKB__MRDCKB0_SLEEP
		| MDLL_RDCKB__MRDCKB1_SLEEP | MDLL_RDCKB__MRDCKB0_RESET
		| MDLL_RDCKB__MRDCKB1_RESET;

	/* Setting up the DLL range क्रम ग_लिखो */
	OUTPLL(pllMDLL_CKO,   	cko);
	OUTPLL(pllMDLL_RDCKA,  	cka);
	OUTPLL(pllMDLL_RDCKB,	ckb);

	mdelay(DLL_RESET_DELAY*2);

	cko &= ~(MDLL_CKO__MCKOA_SLEEP | MDLL_CKO__MCKOB_SLEEP);
	OUTPLL(pllMDLL_CKO, cko);
	mdelay(DLL_SLEEP_DELAY);
	cko &= ~(MDLL_CKO__MCKOA_RESET | MDLL_CKO__MCKOB_RESET);
	OUTPLL(pllMDLL_CKO, cko);
	mdelay(DLL_RESET_DELAY);

	cka &= ~(MDLL_RDCKA__MRDCKA0_SLEEP | MDLL_RDCKA__MRDCKA1_SLEEP);
	OUTPLL(pllMDLL_RDCKA, cka);
	mdelay(DLL_SLEEP_DELAY);
	cka &= ~(MDLL_RDCKA__MRDCKA0_RESET | MDLL_RDCKA__MRDCKA1_RESET);
	OUTPLL(pllMDLL_RDCKA, cka);
	mdelay(DLL_RESET_DELAY);

	ckb &= ~(MDLL_RDCKB__MRDCKB0_SLEEP | MDLL_RDCKB__MRDCKB1_SLEEP);
	OUTPLL(pllMDLL_RDCKB, ckb);
	mdelay(DLL_SLEEP_DELAY);
	ckb &= ~(MDLL_RDCKB__MRDCKB0_RESET | MDLL_RDCKB__MRDCKB1_RESET);
	OUTPLL(pllMDLL_RDCKB, ckb);
	mdelay(DLL_RESET_DELAY);


#अघोषित DLL_RESET_DELAY
#अघोषित DLL_SLEEP_DELAY
पूर्ण

अटल व्योम radeon_pm_enable_dll_m10(काष्ठा radeonfb_info *rinfo)
अणु
	u32 dll_value;
	u32 dll_sleep_mask = 0;
	u32 dll_reset_mask = 0;
	u32 mc;

#घोषणा DLL_RESET_DELAY 	5
#घोषणा DLL_SLEEP_DELAY		1

	OUTMC(rinfo, ixR300_MC_DLL_CNTL, rinfo->save_regs[70]);
	mc = INREG(MC_CNTL);
	/* Check which channels are enabled */
	चयन (mc & 0x3) अणु
	हाल 1:
		अगर (mc & 0x4)
			अवरोध;
		fallthrough;
	हाल 2:
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKB_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKB_RESET;
		fallthrough;
	हाल 0:
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKA_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKA_RESET;
	पूर्ण
	चयन (mc & 0x3) अणु
	हाल 1:
		अगर (!(mc & 0x4))
			अवरोध;
		fallthrough;
	हाल 2:
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKD_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKD_RESET;
		dll_sleep_mask |= MDLL_R300_RDCK__MRDCKC_SLEEP;
		dll_reset_mask |= MDLL_R300_RDCK__MRDCKC_RESET;
	पूर्ण

	dll_value = INPLL(pllMDLL_RDCKA);

	/* Power Up */
	dll_value &= ~(dll_sleep_mask);
	OUTPLL(pllMDLL_RDCKA, dll_value);
	mdelay( DLL_SLEEP_DELAY);  		

	dll_value &= ~(dll_reset_mask);
	OUTPLL(pllMDLL_RDCKA, dll_value);
	mdelay( DLL_RESET_DELAY);  		

#अघोषित DLL_RESET_DELAY 
#अघोषित DLL_SLEEP_DELAY
पूर्ण


अटल व्योम radeon_pm_full_reset_sdram(काष्ठा radeonfb_info *rinfo)
अणु
	u32 crtcGenCntl, crtcGenCntl2, memRefreshCntl, crtc_more_cntl,
		fp_gen_cntl, fp2_gen_cntl;
 
	crtcGenCntl  = INREG( CRTC_GEN_CNTL);
	crtcGenCntl2 = INREG( CRTC2_GEN_CNTL);

	crtc_more_cntl 	= INREG( CRTC_MORE_CNTL);
	fp_gen_cntl 	= INREG( FP_GEN_CNTL);
	fp2_gen_cntl 	= INREG( FP2_GEN_CNTL);
 

	OUTREG( CRTC_MORE_CNTL, 0);
	OUTREG( FP_GEN_CNTL, 0);
	OUTREG( FP2_GEN_CNTL,0);
 
	OUTREG( CRTC_GEN_CNTL,  (crtcGenCntl | CRTC_GEN_CNTL__CRTC_DISP_REQ_EN_B) );
	OUTREG( CRTC2_GEN_CNTL, (crtcGenCntl2 | CRTC2_GEN_CNTL__CRTC2_DISP_REQ_EN_B) );
  
	/* This is the code क्रम the Aluminium PowerBooks M10 / iBooks M11 */
	अगर (rinfo->family == CHIP_FAMILY_RV350) अणु
		u32 sdram_mode_reg = rinfo->save_regs[35];
		अटल स्थिर u32 शेष_mrtable[] =
			अणु 0x21320032,
			  0x21321000, 0xa1321000, 0x21321000, 0xffffffff,
			  0x21320032, 0xa1320032, 0x21320032, 0xffffffff,
			  0x21321002, 0xa1321002, 0x21321002, 0xffffffff,
			  0x21320132, 0xa1320132, 0x21320132, 0xffffffff,
			  0x21320032, 0xa1320032, 0x21320032, 0xffffffff,
			  0x31320032 पूर्ण;

		स्थिर u32 *mrtable = शेष_mrtable;
		पूर्णांक i, mrtable_size = ARRAY_SIZE(शेष_mrtable);

		mdelay(30);

		/* Disable refresh */
		memRefreshCntl 	= INREG( MEM_REFRESH_CNTL)
			& ~MEM_REFRESH_CNTL__MEM_REFRESH_DIS;
		OUTREG( MEM_REFRESH_CNTL, memRefreshCntl
			| MEM_REFRESH_CNTL__MEM_REFRESH_DIS);

		/* Configure and enable M & SPLLs */
       		radeon_pm_enable_dll_m10(rinfo);
		radeon_pm_yclk_mclk_sync_m10(rinfo);

#अगर_घोषित CONFIG_PPC
		अगर (rinfo->of_node != शून्य) अणु
			पूर्णांक size;

			mrtable = of_get_property(rinfo->of_node, "ATY,MRT", &size);
			अगर (mrtable)
				mrtable_size = size >> 2;
			अन्यथा
				mrtable = शेष_mrtable;
		पूर्ण
#पूर्ण_अगर /* CONFIG_PPC */

		/* Program the SDRAM */
		sdram_mode_reg = mrtable[0];
		OUTREG(MEM_SDRAM_MODE_REG, sdram_mode_reg);
		क्रम (i = 0; i < mrtable_size; i++) अणु
			अगर (mrtable[i] == 0xffffffffu)
				radeon_pm_m10_program_mode_रुको(rinfo);
			अन्यथा अणु
				sdram_mode_reg &= ~(MEM_SDRAM_MODE_REG__MEM_MODE_REG_MASK
						    | MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE
						    | MEM_SDRAM_MODE_REG__MEM_SDRAM_RESET);
				sdram_mode_reg |= mrtable[i];

				OUTREG(MEM_SDRAM_MODE_REG, sdram_mode_reg);
				mdelay(1);
			पूर्ण
		पूर्ण

		/* Restore memory refresh */
		OUTREG(MEM_REFRESH_CNTL, memRefreshCntl);
		mdelay(30);

	पूर्ण
	/* Here come the desktop RV200 "QW" card */
	अन्यथा अगर (!rinfo->is_mobility && rinfo->family == CHIP_FAMILY_RV200) अणु
		/* Disable refresh */
		memRefreshCntl 	= INREG( MEM_REFRESH_CNTL)
			& ~MEM_REFRESH_CNTL__MEM_REFRESH_DIS;
		OUTREG(MEM_REFRESH_CNTL, memRefreshCntl
		       | MEM_REFRESH_CNTL__MEM_REFRESH_DIS);
		mdelay(30);

		/* Reset memory */
		OUTREG(MEM_SDRAM_MODE_REG,
		       INREG( MEM_SDRAM_MODE_REG) & ~MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);

		radeon_pm_program_mode_reg(rinfo, 0x2002, 2);
		radeon_pm_program_mode_reg(rinfo, 0x0132, 2);
		radeon_pm_program_mode_reg(rinfo, 0x0032, 2);

		OUTREG(MEM_SDRAM_MODE_REG,
		       INREG(MEM_SDRAM_MODE_REG) | MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);

		OUTREG( MEM_REFRESH_CNTL, 	memRefreshCntl);

	पूर्ण
	/* The M6 */
	अन्यथा अगर (rinfo->is_mobility && rinfo->family == CHIP_FAMILY_RV100) अणु
		/* Disable refresh */
		memRefreshCntl = INREG(EXT_MEM_CNTL) & ~(1 << 20);
		OUTREG( EXT_MEM_CNTL, memRefreshCntl | (1 << 20));
 
		/* Reset memory */
		OUTREG( MEM_SDRAM_MODE_REG,
			INREG( MEM_SDRAM_MODE_REG)
			& ~MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);

		/* DLL */
		radeon_pm_enable_dll(rinfo);

		/* MLCK / YCLK sync */
		radeon_pm_yclk_mclk_sync(rinfo);

		/* Program Mode Register */
		radeon_pm_program_mode_reg(rinfo, 0x2000, 1);   
		radeon_pm_program_mode_reg(rinfo, 0x2001, 1);   
		radeon_pm_program_mode_reg(rinfo, 0x2002, 1);   
		radeon_pm_program_mode_reg(rinfo, 0x0132, 1);   
		radeon_pm_program_mode_reg(rinfo, 0x0032, 1); 

		/* Complete & re-enable refresh */
		OUTREG( MEM_SDRAM_MODE_REG,
			INREG( MEM_SDRAM_MODE_REG) | MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);

		OUTREG(EXT_MEM_CNTL, memRefreshCntl);
	पूर्ण
	/* And finally, the M7..M9 models, including M9+ (RV280) */
	अन्यथा अगर (rinfo->is_mobility) अणु

		/* Disable refresh */
		memRefreshCntl 	= INREG( MEM_REFRESH_CNTL)
			& ~MEM_REFRESH_CNTL__MEM_REFRESH_DIS;
		OUTREG( MEM_REFRESH_CNTL, memRefreshCntl
			| MEM_REFRESH_CNTL__MEM_REFRESH_DIS);

		/* Reset memory */
		OUTREG( MEM_SDRAM_MODE_REG,
			INREG( MEM_SDRAM_MODE_REG)
			& ~MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);

		/* DLL */
		radeon_pm_enable_dll(rinfo);

		/* MLCK / YCLK sync */
		radeon_pm_yclk_mclk_sync(rinfo);

		/* M6, M7 and M9 so far ... */
		अगर (rinfo->family <= CHIP_FAMILY_RV250) अणु
			radeon_pm_program_mode_reg(rinfo, 0x2000, 1);
			radeon_pm_program_mode_reg(rinfo, 0x2001, 1);
			radeon_pm_program_mode_reg(rinfo, 0x2002, 1);
			radeon_pm_program_mode_reg(rinfo, 0x0132, 1);
			radeon_pm_program_mode_reg(rinfo, 0x0032, 1);
		पूर्ण
		/* M9+ (iBook G4) */
		अन्यथा अगर (rinfo->family == CHIP_FAMILY_RV280) अणु
			radeon_pm_program_mode_reg(rinfo, 0x2000, 1);
			radeon_pm_program_mode_reg(rinfo, 0x0132, 1);
			radeon_pm_program_mode_reg(rinfo, 0x0032, 1);
		पूर्ण

		/* Complete & re-enable refresh */
		OUTREG( MEM_SDRAM_MODE_REG,
			INREG( MEM_SDRAM_MODE_REG) | MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);

		OUTREG( MEM_REFRESH_CNTL, 	memRefreshCntl);
	पूर्ण

	OUTREG( CRTC_GEN_CNTL, 		crtcGenCntl);
	OUTREG( CRTC2_GEN_CNTL, 	crtcGenCntl2);
	OUTREG( FP_GEN_CNTL, 		fp_gen_cntl);
	OUTREG( FP2_GEN_CNTL, 		fp2_gen_cntl);

	OUTREG( CRTC_MORE_CNTL, 	crtc_more_cntl);

	mdelay( 15);
पूर्ण

#अगर defined(CONFIG_X86) || defined(CONFIG_PPC_PMAC)
अटल व्योम radeon_pm_reset_pad_ctlr_strength(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp, पंचांगp2;
	पूर्णांक i,j;

	/* Reset the PAD_CTLR_STRENGTH & रुको क्रम it to be stable */
	INREG(PAD_CTLR_STRENGTH);
	OUTREG(PAD_CTLR_STRENGTH, INREG(PAD_CTLR_STRENGTH) & ~PAD_MANUAL_OVERRIDE);
	पंचांगp = INREG(PAD_CTLR_STRENGTH);
	क्रम (i = j = 0; i < 65; ++i) अणु
		mdelay(1);
		पंचांगp2 = INREG(PAD_CTLR_STRENGTH);
		अगर (पंचांगp != पंचांगp2) अणु
			पंचांगp = पंचांगp2;
			i = 0;
			j++;
			अगर (j > 10) अणु
				prपूर्णांकk(KERN_WARNING "radeon: PAD_CTLR_STRENGTH doesn't "
				       "stabilize !\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम radeon_pm_all_ppls_off(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp;

	पंचांगp = INPLL(pllPPLL_CNTL);
	OUTPLL(pllPPLL_CNTL, पंचांगp | 0x3);
	पंचांगp = INPLL(pllP2PLL_CNTL);
	OUTPLL(pllP2PLL_CNTL, पंचांगp | 0x3);
	पंचांगp = INPLL(pllSPLL_CNTL);
	OUTPLL(pllSPLL_CNTL, पंचांगp | 0x3);
	पंचांगp = INPLL(pllMPLL_CNTL);
	OUTPLL(pllMPLL_CNTL, पंचांगp | 0x3);
पूर्ण

अटल व्योम radeon_pm_start_mclk_sclk(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp;

	/* Switch SPLL to PCI source */
	पंचांगp = INPLL(pllSCLK_CNTL);
	OUTPLL(pllSCLK_CNTL, पंचांगp & ~SCLK_CNTL__SCLK_SRC_SEL_MASK);

	/* Reconfigure SPLL अक्षरge pump, VCO gain, duty cycle */
	पंचांगp = INPLL(pllSPLL_CNTL);
	OUTREG8(CLOCK_CNTL_INDEX, pllSPLL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA + 1, (पंचांगp >> 8) & 0xff);
	radeon_pll_errata_after_data(rinfo);

	/* Set SPLL feedback भागider */
	पंचांगp = INPLL(pllM_SPLL_REF_FB_DIV);
	पंचांगp = (पंचांगp & 0xff00fffful) | (rinfo->save_regs[77] & 0x00ff0000ul);
	OUTPLL(pllM_SPLL_REF_FB_DIV, पंचांगp);

	/* Power up SPLL */
	पंचांगp = INPLL(pllSPLL_CNTL);
	OUTPLL(pllSPLL_CNTL, पंचांगp & ~1);
	(व्योम)INPLL(pllSPLL_CNTL);

	mdelay(10);

	/* Release SPLL reset */
	पंचांगp = INPLL(pllSPLL_CNTL);
	OUTPLL(pllSPLL_CNTL, पंचांगp & ~0x2);
	(व्योम)INPLL(pllSPLL_CNTL);

	mdelay(10);

	/* Select SCLK source  */
	पंचांगp = INPLL(pllSCLK_CNTL);
	पंचांगp &= ~SCLK_CNTL__SCLK_SRC_SEL_MASK;
	पंचांगp |= rinfo->save_regs[3] & SCLK_CNTL__SCLK_SRC_SEL_MASK;
	OUTPLL(pllSCLK_CNTL, पंचांगp);
	(व्योम)INPLL(pllSCLK_CNTL);

	mdelay(10);

	/* Reconfigure MPLL अक्षरge pump, VCO gain, duty cycle */
	पंचांगp = INPLL(pllMPLL_CNTL);
	OUTREG8(CLOCK_CNTL_INDEX, pllMPLL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA + 1, (पंचांगp >> 8) & 0xff);
	radeon_pll_errata_after_data(rinfo);

	/* Set MPLL feedback भागider */
	पंचांगp = INPLL(pllM_SPLL_REF_FB_DIV);
	पंचांगp = (पंचांगp & 0xffff00fful) | (rinfo->save_regs[77] & 0x0000ff00ul);

	OUTPLL(pllM_SPLL_REF_FB_DIV, पंचांगp);
	/* Power up MPLL */
	पंचांगp = INPLL(pllMPLL_CNTL);
	OUTPLL(pllMPLL_CNTL, पंचांगp & ~0x2);
	(व्योम)INPLL(pllMPLL_CNTL);

	mdelay(10);

	/* Un-reset MPLL */
	पंचांगp = INPLL(pllMPLL_CNTL);
	OUTPLL(pllMPLL_CNTL, पंचांगp & ~0x1);
	(व्योम)INPLL(pllMPLL_CNTL);

	mdelay(10);

	/* Select source क्रम MCLK */
	पंचांगp = INPLL(pllMCLK_CNTL);
	पंचांगp |= rinfo->save_regs[2] & 0xffff;
	OUTPLL(pllMCLK_CNTL, पंचांगp);
	(व्योम)INPLL(pllMCLK_CNTL);

	mdelay(10);
पूर्ण

अटल व्योम radeon_pm_m10_disable_spपढ़ो_spectrum(काष्ठा radeonfb_info *rinfo)
अणु
	u32 r2ec;

	/* GACK ! I though we didn't have a DDA on Radeon's anymore
	 * here we reग_लिखो with the same value, ... I suppose we clear
	 * some bits that are alपढ़ोy clear ? Or maybe this 0x2ec
	 * रेजिस्टर is something new ?
	 */
	mdelay(20);
	r2ec = INREG(VGA_DDA_ON_OFF);
	OUTREG(VGA_DDA_ON_OFF, r2ec);
	mdelay(1);

	/* Spपढ़ो spectrum PLLL off */
	OUTPLL(pllSSPLL_CNTL, 0xbf03);

	/* Spपढ़ो spectrum disabled */
	OUTPLL(pllSS_INT_CNTL, rinfo->save_regs[90] & ~3);

	/* The trace shows पढ़ो & reग_लिखो of LVDS_PLL_CNTL here with same
	 * value, not sure what क्रम...
	 */

	r2ec |= 0x3f0;
	OUTREG(VGA_DDA_ON_OFF, r2ec);
	mdelay(1);
पूर्ण

अटल व्योम radeon_pm_m10_enable_lvds_spपढ़ो_spectrum(काष्ठा radeonfb_info *rinfo)
अणु
	u32 r2ec, पंचांगp;

	/* GACK (bis) ! I though we didn't have a DDA on Radeon's anymore
	 * here we reग_लिखो with the same value, ... I suppose we clear/set
	 * some bits that are alपढ़ोy clear/set ?
	 */
	r2ec = INREG(VGA_DDA_ON_OFF);
	OUTREG(VGA_DDA_ON_OFF, r2ec);
	mdelay(1);

	/* Enable spपढ़ो spectrum */
	OUTPLL(pllSSPLL_CNTL, rinfo->save_regs[43] | 3);
	mdelay(3);

	OUTPLL(pllSSPLL_REF_DIV, rinfo->save_regs[44]);
	OUTPLL(pllSSPLL_DIV_0, rinfo->save_regs[45]);
	पंचांगp = INPLL(pllSSPLL_CNTL);
	OUTPLL(pllSSPLL_CNTL, पंचांगp & ~0x2);
	mdelay(6);
	पंचांगp = INPLL(pllSSPLL_CNTL);
	OUTPLL(pllSSPLL_CNTL, पंचांगp & ~0x1);
	mdelay(5);

       	OUTPLL(pllSS_INT_CNTL, rinfo->save_regs[90]);

	r2ec |= 8;
	OUTREG(VGA_DDA_ON_OFF, r2ec);
	mdelay(20);

	/* Enable LVDS पूर्णांकerface */
	पंचांगp = INREG(LVDS_GEN_CNTL);
	OUTREG(LVDS_GEN_CNTL, पंचांगp | LVDS_EN);

	/* Enable LVDS_PLL */
	पंचांगp = INREG(LVDS_PLL_CNTL);
	पंचांगp &= ~0x30000;
	पंचांगp |= 0x10000;
	OUTREG(LVDS_PLL_CNTL, पंचांगp);

	OUTPLL(pllSCLK_MORE_CNTL, rinfo->save_regs[34]);
	OUTPLL(pllSS_TST_CNTL, rinfo->save_regs[91]);

	/* The trace पढ़ोs that one here, रुकोing क्रम something to settle करोwn ? */
	INREG(RBBM_STATUS);

	/* Ugh ? SS_TST_DEC is supposed to be a पढ़ो रेजिस्टर in the
	 * R300 रेजिस्टर spec at least...
	 */
	पंचांगp = INPLL(pllSS_TST_CNTL);
	पंचांगp |= 0x00400000;
	OUTPLL(pllSS_TST_CNTL, पंचांगp);
पूर्ण

अटल व्योम radeon_pm_restore_pixel_pll(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp;

	OUTREG8(CLOCK_CNTL_INDEX, pllHTOTAL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA, 0);
	radeon_pll_errata_after_data(rinfo);

	पंचांगp = INPLL(pllVCLK_ECP_CNTL);
	OUTPLL(pllVCLK_ECP_CNTL, पंचांगp | 0x80);
	mdelay(5);

	पंचांगp = INPLL(pllPPLL_REF_DIV);
	पंचांगp = (पंचांगp & ~PPLL_REF_DIV_MASK) | rinfo->pll.ref_भाग;
	OUTPLL(pllPPLL_REF_DIV, पंचांगp);
	INPLL(pllPPLL_REF_DIV);

	/* Reconfigure SPLL अक्षरge pump, VCO gain, duty cycle,
	 * probably useless since we alपढ़ोy did it ...
	 */
	पंचांगp = INPLL(pllPPLL_CNTL);
	OUTREG8(CLOCK_CNTL_INDEX, pllSPLL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA + 1, (पंचांगp >> 8) & 0xff);
	radeon_pll_errata_after_data(rinfo);

	/* Restore our "reference" PPLL भागider set by firmware
	 * according to proper spपढ़ो spectrum calculations
	 */
	OUTPLL(pllPPLL_DIV_0, rinfo->save_regs[92]);

	पंचांगp = INPLL(pllPPLL_CNTL);
	OUTPLL(pllPPLL_CNTL, पंचांगp & ~0x2);
	mdelay(5);

	पंचांगp = INPLL(pllPPLL_CNTL);
	OUTPLL(pllPPLL_CNTL, पंचांगp & ~0x1);
	mdelay(5);

	पंचांगp = INPLL(pllVCLK_ECP_CNTL);
	OUTPLL(pllVCLK_ECP_CNTL, पंचांगp | 3);
	mdelay(5);

	पंचांगp = INPLL(pllVCLK_ECP_CNTL);
	OUTPLL(pllVCLK_ECP_CNTL, पंचांगp | 3);
	mdelay(5);

	/* Switch pixel घड़ी to firmware शेष भाग 0 */
	OUTREG8(CLOCK_CNTL_INDEX+1, 0);
	radeon_pll_errata_after_index(rinfo);
	radeon_pll_errata_after_data(rinfo);
पूर्ण

अटल व्योम radeon_pm_m10_reconfigure_mc(काष्ठा radeonfb_info *rinfo)
अणु
	OUTREG(MC_CNTL, rinfo->save_regs[46]);
	OUTREG(MC_INIT_GFX_LAT_TIMER, rinfo->save_regs[47]);
	OUTREG(MC_INIT_MISC_LAT_TIMER, rinfo->save_regs[48]);
	OUTREG(MEM_SDRAM_MODE_REG,
	       rinfo->save_regs[35] & ~MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);
	OUTREG(MC_TIMING_CNTL, rinfo->save_regs[49]);
	OUTREG(MEM_REFRESH_CNTL, rinfo->save_regs[42]);
	OUTREG(MC_READ_CNTL_AB, rinfo->save_regs[50]);
	OUTREG(MC_CHIP_IO_OE_CNTL_AB, rinfo->save_regs[52]);
	OUTREG(MC_IOPAD_CNTL, rinfo->save_regs[51]);
	OUTREG(MC_DEBUG, rinfo->save_regs[53]);

	OUTMC(rinfo, ixR300_MC_MC_INIT_WR_LAT_TIMER, rinfo->save_regs[58]);
	OUTMC(rinfo, ixR300_MC_IMP_CNTL, rinfo->save_regs[59]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_C0, rinfo->save_regs[60]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_C1, rinfo->save_regs[61]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_D0, rinfo->save_regs[62]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_D1, rinfo->save_regs[63]);
	OUTMC(rinfo, ixR300_MC_BIST_CNTL_3, rinfo->save_regs[64]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_A0, rinfo->save_regs[65]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_A1, rinfo->save_regs[66]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_B0, rinfo->save_regs[67]);
	OUTMC(rinfo, ixR300_MC_CHP_IO_CNTL_B1, rinfo->save_regs[68]);
	OUTMC(rinfo, ixR300_MC_DEBUG_CNTL, rinfo->save_regs[69]);
	OUTMC(rinfo, ixR300_MC_DLL_CNTL, rinfo->save_regs[70]);
	OUTMC(rinfo, ixR300_MC_IMP_CNTL_0, rinfo->save_regs[71]);
	OUTMC(rinfo, ixR300_MC_ELPIDA_CNTL, rinfo->save_regs[72]);
	OUTMC(rinfo, ixR300_MC_READ_CNTL_CD, rinfo->save_regs[96]);
	OUTREG(MC_IND_INDEX, 0);
पूर्ण

अटल व्योम radeon_reinitialize_M10(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp, i;

	/* Restore a bunch of रेजिस्टरs first */
	OUTREG(MC_AGP_LOCATION, rinfo->save_regs[32]);
	OUTREG(DISPLAY_BASE_ADDR, rinfo->save_regs[31]);
	OUTREG(CRTC2_DISPLAY_BASE_ADDR, rinfo->save_regs[33]);
	OUTREG(MC_FB_LOCATION, rinfo->save_regs[30]);
	OUTREG(OV0_BASE_ADDR, rinfo->save_regs[80]);
	OUTREG(CNFG_MEMSIZE, rinfo->video_ram);
	OUTREG(BUS_CNTL, rinfo->save_regs[36]);
	OUTREG(BUS_CNTL1, rinfo->save_regs[14]);
	OUTREG(MPP_TB_CONFIG, rinfo->save_regs[37]);
	OUTREG(FCP_CNTL, rinfo->save_regs[38]);
	OUTREG(RBBM_CNTL, rinfo->save_regs[39]);
	OUTREG(DAC_CNTL, rinfo->save_regs[40]);
	OUTREG(DAC_MACRO_CNTL, (INREG(DAC_MACRO_CNTL) & ~0x6) | 8);
	OUTREG(DAC_MACRO_CNTL, (INREG(DAC_MACRO_CNTL) & ~0x6) | 8);

	/* Hrm... */
	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) | DAC2_EXPAND_MODE);

	/* Reset the PAD CTLR */
	radeon_pm_reset_pad_ctlr_strength(rinfo);

	/* Some PLLs are Read & written identically in the trace here...
	 * I suppose it's actually to चयन them all off & reset,
	 * let's assume off is what we want. I'm just करोing that क्रम all major PLLs now.
	 */
	radeon_pm_all_ppls_off(rinfo);

	/* Clear tiling, reset swappers */
	INREG(SURFACE_CNTL);
	OUTREG(SURFACE_CNTL, 0);

	/* Some black magic with TV_DAC_CNTL, we should restore those from backups
	 * rather than hard coding...
	 */
	पंचांगp = INREG(TV_DAC_CNTL) & ~TV_DAC_CNTL_BGADJ_MASK;
	पंचांगp |= 8 << TV_DAC_CNTL_BGADJ__SHIFT;
	OUTREG(TV_DAC_CNTL, पंचांगp);

	पंचांगp = INREG(TV_DAC_CNTL) & ~TV_DAC_CNTL_DACADJ_MASK;
	पंचांगp |= 7 << TV_DAC_CNTL_DACADJ__SHIFT;
	OUTREG(TV_DAC_CNTL, पंचांगp);

	/* More रेजिस्टरs restored */
	OUTREG(AGP_CNTL, rinfo->save_regs[16]);
	OUTREG(HOST_PATH_CNTL, rinfo->save_regs[41]);
	OUTREG(DISP_MISC_CNTL, rinfo->save_regs[9]);

	/* Hrmmm ... What is that ? */
	पंचांगp = rinfo->save_regs[1]
		& ~(CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK |
		    CLK_PWRMGT_CNTL__MC_BUSY);
	OUTPLL(pllCLK_PWRMGT_CNTL, पंचांगp);

	OUTREG(PAD_CTLR_MISC, rinfo->save_regs[56]);
	OUTREG(FW_CNTL, rinfo->save_regs[57]);
	OUTREG(HDP_DEBUG, rinfo->save_regs[96]);
	OUTREG(PAMAC0_DLY_CNTL, rinfo->save_regs[54]);
	OUTREG(PAMAC1_DLY_CNTL, rinfo->save_regs[55]);
	OUTREG(PAMAC2_DLY_CNTL, rinfo->save_regs[79]);

	/* Restore Memory Controller configuration */
	radeon_pm_m10_reconfigure_mc(rinfo);

	/* Make sure CRTC's करोnt touch memory */
	OUTREG(CRTC_GEN_CNTL, INREG(CRTC_GEN_CNTL)
	       | CRTC_GEN_CNTL__CRTC_DISP_REQ_EN_B);
	OUTREG(CRTC2_GEN_CNTL, INREG(CRTC2_GEN_CNTL)
	       | CRTC2_GEN_CNTL__CRTC2_DISP_REQ_EN_B);
	mdelay(30);

	/* Disable SDRAM refresh */
	OUTREG(MEM_REFRESH_CNTL, INREG(MEM_REFRESH_CNTL)
	       | MEM_REFRESH_CNTL__MEM_REFRESH_DIS);

	/* Restore XTALIN routing (CLK_PIN_CNTL) */
	OUTPLL(pllCLK_PIN_CNTL, rinfo->save_regs[4]);

	/* Switch MCLK, YCLK and SCLK PLLs to PCI source & क्रमce them ON */
	पंचांगp = rinfo->save_regs[2] & 0xff000000;
	पंचांगp |=	MCLK_CNTL__FORCE_MCLKA |
		MCLK_CNTL__FORCE_MCLKB |
		MCLK_CNTL__FORCE_YCLKA |
		MCLK_CNTL__FORCE_YCLKB |
		MCLK_CNTL__FORCE_MC;
	OUTPLL(pllMCLK_CNTL, पंचांगp);

	/* Force all घड़ीs on in SCLK */
	पंचांगp = INPLL(pllSCLK_CNTL);
	पंचांगp |=	SCLK_CNTL__FORCE_DISP2|
		SCLK_CNTL__FORCE_CP|
		SCLK_CNTL__FORCE_HDP|
		SCLK_CNTL__FORCE_DISP1|
		SCLK_CNTL__FORCE_TOP|
		SCLK_CNTL__FORCE_E2|
		SCLK_CNTL__FORCE_SE|
		SCLK_CNTL__FORCE_IDCT|
		SCLK_CNTL__FORCE_VIP|
		SCLK_CNTL__FORCE_PB|
		SCLK_CNTL__FORCE_TAM|
		SCLK_CNTL__FORCE_TDM|
		SCLK_CNTL__FORCE_RB|
		SCLK_CNTL__FORCE_TV_SCLK|
		SCLK_CNTL__FORCE_SUBPIC|
		SCLK_CNTL__FORCE_OV0;
	पंचांगp |=	SCLK_CNTL__CP_MAX_DYN_STOP_LAT  |
		SCLK_CNTL__HDP_MAX_DYN_STOP_LAT |
		SCLK_CNTL__TV_MAX_DYN_STOP_LAT  |
		SCLK_CNTL__E2_MAX_DYN_STOP_LAT  |
		SCLK_CNTL__SE_MAX_DYN_STOP_LAT  |
		SCLK_CNTL__IDCT_MAX_DYN_STOP_LAT|
		SCLK_CNTL__VIP_MAX_DYN_STOP_LAT |
		SCLK_CNTL__RE_MAX_DYN_STOP_LAT  |
		SCLK_CNTL__PB_MAX_DYN_STOP_LAT  |
		SCLK_CNTL__TAM_MAX_DYN_STOP_LAT |
		SCLK_CNTL__TDM_MAX_DYN_STOP_LAT |
		SCLK_CNTL__RB_MAX_DYN_STOP_LAT;
	OUTPLL(pllSCLK_CNTL, पंचांगp);

	OUTPLL(pllVCLK_ECP_CNTL, 0);
	OUTPLL(pllPIXCLKS_CNTL, 0);
	OUTPLL(pllMCLK_MISC,
	       MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT |
	       MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT);

	mdelay(5);

	/* Restore the M_SPLL_REF_FB_DIV, MPLL_AUX_CNTL and SPLL_AUX_CNTL values */
	OUTPLL(pllM_SPLL_REF_FB_DIV, rinfo->save_regs[77]);
	OUTPLL(pllMPLL_AUX_CNTL, rinfo->save_regs[75]);
	OUTPLL(pllSPLL_AUX_CNTL, rinfo->save_regs[76]);

	/* Now restore the major PLLs settings, keeping them off & reset though */
	OUTPLL(pllPPLL_CNTL, rinfo->save_regs[93] | 0x3);
	OUTPLL(pllP2PLL_CNTL, rinfo->save_regs[8] | 0x3);
	OUTPLL(pllMPLL_CNTL, rinfo->save_regs[73] | 0x03);
	OUTPLL(pllSPLL_CNTL, rinfo->save_regs[74] | 0x03);

	/* Restore MC DLL state and चयन it off/reset too  */
	OUTMC(rinfo, ixR300_MC_DLL_CNTL, rinfo->save_regs[70]);

	/* Switch MDLL off & reset */
	OUTPLL(pllMDLL_RDCKA, rinfo->save_regs[98] | 0xff);
	mdelay(5);

	/* Setup some black magic bits in PLL_PWRMGT_CNTL. Hrm... we saved
	 * 0xa1100007... and MacOS ग_लिखोs 0xa1000007 ..
	 */
	OUTPLL(pllPLL_PWRMGT_CNTL, rinfo->save_regs[0]);

	/* Restore more stuffs */
	OUTPLL(pllHTOTAL_CNTL, 0);
	OUTPLL(pllHTOTAL2_CNTL, 0);

	/* More PLL initial configuration */
	पंचांगp = INPLL(pllSCLK_CNTL2); /* What क्रम ? */
	OUTPLL(pllSCLK_CNTL2, पंचांगp);

	पंचांगp = INPLL(pllSCLK_MORE_CNTL);
	पंचांगp |= 	SCLK_MORE_CNTL__FORCE_DISPREGS |	/* a guess */
		SCLK_MORE_CNTL__FORCE_MC_GUI |
		SCLK_MORE_CNTL__FORCE_MC_HOST;
	OUTPLL(pllSCLK_MORE_CNTL, पंचांगp);

	/* Now we actually start MCLK and SCLK */
	radeon_pm_start_mclk_sclk(rinfo);

	/* Full reset sdrams, this also re-inits the MDLL */
	radeon_pm_full_reset_sdram(rinfo);

	/* Fill palettes */
	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) | 0x20);
	क्रम (i=0; i<256; i++)
		OUTREG(PALETTE_30_DATA, 0x15555555);
	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) & ~20);
	udelay(20);
	क्रम (i=0; i<256; i++)
		OUTREG(PALETTE_30_DATA, 0x15555555);

	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) & ~0x20);
	mdelay(3);

	/* Restore TMDS */
	OUTREG(FP_GEN_CNTL, rinfo->save_regs[82]);
	OUTREG(FP2_GEN_CNTL, rinfo->save_regs[83]);

	/* Set LVDS रेजिस्टरs but keep पूर्णांकerface & pll करोwn */
	OUTREG(LVDS_GEN_CNTL, rinfo->save_regs[11] &
	       ~(LVDS_EN | LVDS_ON | LVDS_DIGON | LVDS_BLON | LVDS_BL_MOD_EN));
	OUTREG(LVDS_PLL_CNTL, (rinfo->save_regs[12] & ~0xf0000) | 0x20000);

	OUTREG(DISP_OUTPUT_CNTL, rinfo->save_regs[86]);

	/* Restore GPIOPAD state */
	OUTREG(GPIOPAD_A, rinfo->save_regs[19]);
	OUTREG(GPIOPAD_EN, rinfo->save_regs[20]);
	OUTREG(GPIOPAD_MASK, rinfo->save_regs[21]);

	/* ग_लिखो some stuff to the framebuffer... */
	क्रम (i = 0; i < 0x8000; ++i)
		ग_लिखोb(0, rinfo->fb_base + i);

	mdelay(40);
	OUTREG(LVDS_GEN_CNTL, INREG(LVDS_GEN_CNTL) | LVDS_DIGON | LVDS_ON);
	mdelay(40);

	/* Restore a few more things */
	OUTREG(GRPH_BUFFER_CNTL, rinfo->save_regs[94]);
	OUTREG(GRPH2_BUFFER_CNTL, rinfo->save_regs[95]);

	/* Take care of spपढ़ो spectrum & PPLLs now */
	radeon_pm_m10_disable_spपढ़ो_spectrum(rinfo);
	radeon_pm_restore_pixel_pll(rinfo);

	/* GRRRR... I can't figure out the proper LVDS घातer sequence, and the
	 * code I have क्रम blank/unblank करोesn't quite work on some laptop models
	 * it seems ... Hrm. What I have here works most of the समय ...
	 */
	radeon_pm_m10_enable_lvds_spपढ़ो_spectrum(rinfo);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC
#अगर_घोषित CONFIG_PPC_PMAC
अटल व्योम radeon_pm_m9p_reconfigure_mc(काष्ठा radeonfb_info *rinfo)
अणु
	OUTREG(MC_CNTL, rinfo->save_regs[46]);
	OUTREG(MC_INIT_GFX_LAT_TIMER, rinfo->save_regs[47]);
	OUTREG(MC_INIT_MISC_LAT_TIMER, rinfo->save_regs[48]);
	OUTREG(MEM_SDRAM_MODE_REG,
	       rinfo->save_regs[35] & ~MEM_SDRAM_MODE_REG__MC_INIT_COMPLETE);
	OUTREG(MC_TIMING_CNTL, rinfo->save_regs[49]);
	OUTREG(MC_READ_CNTL_AB, rinfo->save_regs[50]);
	OUTREG(MEM_REFRESH_CNTL, rinfo->save_regs[42]);
	OUTREG(MC_IOPAD_CNTL, rinfo->save_regs[51]);
	OUTREG(MC_DEBUG, rinfo->save_regs[53]);
	OUTREG(MC_CHIP_IO_OE_CNTL_AB, rinfo->save_regs[52]);

	OUTMC(rinfo, ixMC_IMP_CNTL, rinfo->save_regs[59] /*0x00f460d6*/);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_A0, rinfo->save_regs[65] /*0xfecfa666*/);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_A1, rinfo->save_regs[66] /*0x141555ff*/);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_B0, rinfo->save_regs[67] /*0xfecfa666*/);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_B1, rinfo->save_regs[68] /*0x141555ff*/);
	OUTMC(rinfo, ixMC_IMP_CNTL_0, rinfo->save_regs[71] /*0x00009249*/);
	OUTREG(MC_IND_INDEX, 0);
	OUTREG(CNFG_MEMSIZE, rinfo->video_ram);

	mdelay(20);
पूर्ण

अटल व्योम radeon_reinitialize_M9P(काष्ठा radeonfb_info *rinfo)
अणु
	u32 पंचांगp, i;

	/* Restore a bunch of रेजिस्टरs first */
	OUTREG(SURFACE_CNTL, rinfo->save_regs[29]);
	OUTREG(MC_AGP_LOCATION, rinfo->save_regs[32]);
	OUTREG(DISPLAY_BASE_ADDR, rinfo->save_regs[31]);
	OUTREG(CRTC2_DISPLAY_BASE_ADDR, rinfo->save_regs[33]);
	OUTREG(MC_FB_LOCATION, rinfo->save_regs[30]);
	OUTREG(OV0_BASE_ADDR, rinfo->save_regs[80]);
	OUTREG(BUS_CNTL, rinfo->save_regs[36]);
	OUTREG(BUS_CNTL1, rinfo->save_regs[14]);
	OUTREG(MPP_TB_CONFIG, rinfo->save_regs[37]);
	OUTREG(FCP_CNTL, rinfo->save_regs[38]);
	OUTREG(RBBM_CNTL, rinfo->save_regs[39]);

	OUTREG(DAC_CNTL, rinfo->save_regs[40]);
	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) | DAC2_EXPAND_MODE);

	/* Reset the PAD CTLR */
	radeon_pm_reset_pad_ctlr_strength(rinfo);

	/* Some PLLs are Read & written identically in the trace here...
	 * I suppose it's actually to चयन them all off & reset,
	 * let's assume off is what we want. I'm just करोing that क्रम all major PLLs now.
	 */
	radeon_pm_all_ppls_off(rinfo);

	/* Clear tiling, reset swappers */
	INREG(SURFACE_CNTL);
	OUTREG(SURFACE_CNTL, 0);

	/* Some black magic with TV_DAC_CNTL, we should restore those from backups
	 * rather than hard coding...
	 */
	पंचांगp = INREG(TV_DAC_CNTL) & ~TV_DAC_CNTL_BGADJ_MASK;
	पंचांगp |= 6 << TV_DAC_CNTL_BGADJ__SHIFT;
	OUTREG(TV_DAC_CNTL, पंचांगp);

	पंचांगp = INREG(TV_DAC_CNTL) & ~TV_DAC_CNTL_DACADJ_MASK;
	पंचांगp |= 6 << TV_DAC_CNTL_DACADJ__SHIFT;
	OUTREG(TV_DAC_CNTL, पंचांगp);

	OUTPLL(pllAGP_PLL_CNTL, rinfo->save_regs[78]);

	OUTREG(PAMAC0_DLY_CNTL, rinfo->save_regs[54]);
	OUTREG(PAMAC1_DLY_CNTL, rinfo->save_regs[55]);
	OUTREG(PAMAC2_DLY_CNTL, rinfo->save_regs[79]);

	OUTREG(AGP_CNTL, rinfo->save_regs[16]);
	OUTREG(HOST_PATH_CNTL, rinfo->save_regs[41]); /* MacOS sets that to 0 !!! */
	OUTREG(DISP_MISC_CNTL, rinfo->save_regs[9]);

	पंचांगp  = rinfo->save_regs[1]
		& ~(CLK_PWRMGT_CNTL__ACTIVE_HILO_LAT_MASK |
		    CLK_PWRMGT_CNTL__MC_BUSY);
	OUTPLL(pllCLK_PWRMGT_CNTL, पंचांगp);

	OUTREG(FW_CNTL, rinfo->save_regs[57]);

	/* Disable SDRAM refresh */
	OUTREG(MEM_REFRESH_CNTL, INREG(MEM_REFRESH_CNTL)
	       | MEM_REFRESH_CNTL__MEM_REFRESH_DIS);

	/* Restore XTALIN routing (CLK_PIN_CNTL) */
       	OUTPLL(pllCLK_PIN_CNTL, rinfo->save_regs[4]);

	/* Force MCLK to be PCI sourced and क्रमced ON */
	पंचांगp = rinfo->save_regs[2] & 0xff000000;
	पंचांगp |=	MCLK_CNTL__FORCE_MCLKA |
		MCLK_CNTL__FORCE_MCLKB |
		MCLK_CNTL__FORCE_YCLKA |
		MCLK_CNTL__FORCE_YCLKB |
		MCLK_CNTL__FORCE_MC    |
		MCLK_CNTL__FORCE_AIC;
	OUTPLL(pllMCLK_CNTL, पंचांगp);

	/* Force SCLK to be PCI sourced with a bunch क्रमced */
	पंचांगp =	0 |
		SCLK_CNTL__FORCE_DISP2|
		SCLK_CNTL__FORCE_CP|
		SCLK_CNTL__FORCE_HDP|
		SCLK_CNTL__FORCE_DISP1|
		SCLK_CNTL__FORCE_TOP|
		SCLK_CNTL__FORCE_E2|
		SCLK_CNTL__FORCE_SE|
		SCLK_CNTL__FORCE_IDCT|
		SCLK_CNTL__FORCE_VIP|
		SCLK_CNTL__FORCE_RE|
		SCLK_CNTL__FORCE_PB|
		SCLK_CNTL__FORCE_TAM|
		SCLK_CNTL__FORCE_TDM|
		SCLK_CNTL__FORCE_RB;
	OUTPLL(pllSCLK_CNTL, पंचांगp);

	/* Clear VCLK_ECP_CNTL & PIXCLKS_CNTL  */
	OUTPLL(pllVCLK_ECP_CNTL, 0);
	OUTPLL(pllPIXCLKS_CNTL, 0);

	/* Setup MCLK_MISC, non dynamic mode */
	OUTPLL(pllMCLK_MISC,
	       MCLK_MISC__MC_MCLK_MAX_DYN_STOP_LAT |
	       MCLK_MISC__IO_MCLK_MAX_DYN_STOP_LAT);

	mdelay(5);

	/* Set back the शेष घड़ी भागiders */
	OUTPLL(pllM_SPLL_REF_FB_DIV, rinfo->save_regs[77]);
	OUTPLL(pllMPLL_AUX_CNTL, rinfo->save_regs[75]);
	OUTPLL(pllSPLL_AUX_CNTL, rinfo->save_regs[76]);

	/* PPLL and P2PLL शेष values & off */
	OUTPLL(pllPPLL_CNTL, rinfo->save_regs[93] | 0x3);
	OUTPLL(pllP2PLL_CNTL, rinfo->save_regs[8] | 0x3);

	/* S and M PLLs are reset & off, configure them */
	OUTPLL(pllMPLL_CNTL, rinfo->save_regs[73] | 0x03);
	OUTPLL(pllSPLL_CNTL, rinfo->save_regs[74] | 0x03);

	/* Default values क्रम MDLL ... fixme */
	OUTPLL(pllMDLL_CKO, 0x9c009c);
	OUTPLL(pllMDLL_RDCKA, 0x08830883);
	OUTPLL(pllMDLL_RDCKB, 0x08830883);
	mdelay(5);

	/* Restore PLL_PWRMGT_CNTL */ // XXXX
	पंचांगp = rinfo->save_regs[0];
	पंचांगp &= ~PLL_PWRMGT_CNTL_SU_SCLK_USE_BCLK;
	पंचांगp |= PLL_PWRMGT_CNTL_SU_MCLK_USE_BCLK;
	OUTPLL(PLL_PWRMGT_CNTL,  पंचांगp);

	/* Clear HTOTAL_CNTL & HTOTAL2_CNTL */
	OUTPLL(pllHTOTAL_CNTL, 0);
	OUTPLL(pllHTOTAL2_CNTL, 0);

	/* All outमाला_दो off */
	OUTREG(CRTC_GEN_CNTL, 0x04000000);
	OUTREG(CRTC2_GEN_CNTL, 0x04000000);
	OUTREG(FP_GEN_CNTL, 0x00004008);
	OUTREG(FP2_GEN_CNTL, 0x00000008);
	OUTREG(LVDS_GEN_CNTL, 0x08000008);

	/* Restore Memory Controller configuration */
	radeon_pm_m9p_reconfigure_mc(rinfo);

	/* Now we actually start MCLK and SCLK */
	radeon_pm_start_mclk_sclk(rinfo);

	/* Full reset sdrams, this also re-inits the MDLL */
	radeon_pm_full_reset_sdram(rinfo);

	/* Fill palettes */
	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) | 0x20);
	क्रम (i=0; i<256; i++)
		OUTREG(PALETTE_30_DATA, 0x15555555);
	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) & ~20);
	udelay(20);
	क्रम (i=0; i<256; i++)
		OUTREG(PALETTE_30_DATA, 0x15555555);

	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) & ~0x20);
	mdelay(3);

	/* Restore TV stuff, make sure TV DAC is करोwn */
	OUTREG(TV_MASTER_CNTL, rinfo->save_regs[88]);
	OUTREG(TV_DAC_CNTL, rinfo->save_regs[13] | 0x07000000);

	/* Restore GPIOS. MacOS करोes some magic here with one of the GPIO bits,
	 * possibly related to the weird PLL related workarounds and to the
	 * fact that CLK_PIN_CNTL is tweaked in ways I करोn't fully understand,
	 * but we keep things the simple way here
	 */
	OUTREG(GPIOPAD_A, rinfo->save_regs[19]);
	OUTREG(GPIOPAD_EN, rinfo->save_regs[20]);
	OUTREG(GPIOPAD_MASK, rinfo->save_regs[21]);

	/* Now करो things with SCLK_MORE_CNTL. Force bits are alपढ़ोy set, copy
	 * high bits from backup
	 */
	पंचांगp = INPLL(pllSCLK_MORE_CNTL) & 0x0000ffff;
	पंचांगp |= rinfo->save_regs[34] & 0xffff0000;
	पंचांगp |= SCLK_MORE_CNTL__FORCE_DISPREGS;
	OUTPLL(pllSCLK_MORE_CNTL, पंचांगp);

	पंचांगp = INPLL(pllSCLK_MORE_CNTL) & 0x0000ffff;
	पंचांगp |= rinfo->save_regs[34] & 0xffff0000;
	पंचांगp |= SCLK_MORE_CNTL__FORCE_DISPREGS;
	OUTPLL(pllSCLK_MORE_CNTL, पंचांगp);

	OUTREG(LVDS_GEN_CNTL, rinfo->save_regs[11] &
	       ~(LVDS_EN | LVDS_ON | LVDS_DIGON | LVDS_BLON | LVDS_BL_MOD_EN));
	OUTREG(LVDS_GEN_CNTL, INREG(LVDS_GEN_CNTL) | LVDS_BLON);
	OUTREG(LVDS_PLL_CNTL, (rinfo->save_regs[12] & ~0xf0000) | 0x20000);
	mdelay(20);

	/* ग_लिखो some stuff to the framebuffer... */
	क्रम (i = 0; i < 0x8000; ++i)
		ग_लिखोb(0, rinfo->fb_base + i);

	OUTREG(0x2ec, 0x6332a020);
	OUTPLL(pllSSPLL_REF_DIV, rinfo->save_regs[44] /*0x3f */);
	OUTPLL(pllSSPLL_DIV_0, rinfo->save_regs[45] /*0x000081bb */);
	पंचांगp = INPLL(pllSSPLL_CNTL);
	पंचांगp &= ~2;
	OUTPLL(pllSSPLL_CNTL, पंचांगp);
	mdelay(6);
	पंचांगp &= ~1;
	OUTPLL(pllSSPLL_CNTL, पंचांगp);
	mdelay(5);
	पंचांगp |= 3;
	OUTPLL(pllSSPLL_CNTL, पंचांगp);
	mdelay(5);

	OUTPLL(pllSS_INT_CNTL, rinfo->save_regs[90] & ~3);/*0x0020300c*/
	OUTREG(0x2ec, 0x6332a3f0);
	mdelay(17);

	OUTPLL(pllPPLL_REF_DIV, rinfo->pll.ref_भाग);
	OUTPLL(pllPPLL_DIV_0, rinfo->save_regs[92]);

	mdelay(40);
	OUTREG(LVDS_GEN_CNTL, INREG(LVDS_GEN_CNTL) | LVDS_DIGON | LVDS_ON);
	mdelay(40);

	/* Restore a few more things */
	OUTREG(GRPH_BUFFER_CNTL, rinfo->save_regs[94]);
	OUTREG(GRPH2_BUFFER_CNTL, rinfo->save_regs[95]);

	/* Restore PPLL, spपढ़ो spectrum & LVDS */
	radeon_pm_m10_disable_spपढ़ो_spectrum(rinfo);
	radeon_pm_restore_pixel_pll(rinfo);
	radeon_pm_m10_enable_lvds_spपढ़ो_spectrum(rinfo);
पूर्ण
#पूर्ण_अगर

#अगर 0 /* Not पढ़ोy yet */
अटल व्योम radeon_reinitialize_QW(काष्ठा radeonfb_info *rinfo)
अणु
	पूर्णांक i;
	u32 पंचांगp, पंचांगp2;
	u32 cko, cka, ckb;
	u32 cgc, cec, c2gc;

	OUTREG(MC_AGP_LOCATION, rinfo->save_regs[32]);
	OUTREG(DISPLAY_BASE_ADDR, rinfo->save_regs[31]);
	OUTREG(CRTC2_DISPLAY_BASE_ADDR, rinfo->save_regs[33]);
	OUTREG(MC_FB_LOCATION, rinfo->save_regs[30]);
	OUTREG(BUS_CNTL, rinfo->save_regs[36]);
	OUTREG(RBBM_CNTL, rinfo->save_regs[39]);

	INREG(PAD_CTLR_STRENGTH);
	OUTREG(PAD_CTLR_STRENGTH, INREG(PAD_CTLR_STRENGTH) & ~0x10000);
	क्रम (i = 0; i < 65; ++i) अणु
		mdelay(1);
		INREG(PAD_CTLR_STRENGTH);
	पूर्ण

	OUTREG(DISP_TEST_DEBUG_CNTL, INREG(DISP_TEST_DEBUG_CNTL) | 0x10000000);
	OUTREG(OV0_FLAG_CNTRL, INREG(OV0_FLAG_CNTRL) | 0x100);
	OUTREG(CRTC_GEN_CNTL, INREG(CRTC_GEN_CNTL));
	OUTREG(DAC_CNTL, 0xff00410a);
	OUTREG(CRTC2_GEN_CNTL, INREG(CRTC2_GEN_CNTL));
	OUTREG(DAC_CNTL2, INREG(DAC_CNTL2) | 0x4000);

	OUTREG(SURFACE_CNTL, rinfo->save_regs[29]);
	OUTREG(AGP_CNTL, rinfo->save_regs[16]);
	OUTREG(HOST_PATH_CNTL, rinfo->save_regs[41]);
	OUTREG(DISP_MISC_CNTL, rinfo->save_regs[9]);

	OUTMC(rinfo, ixMC_CHP_IO_CNTL_A0, 0xf7bb4433);
	OUTREG(MC_IND_INDEX, 0);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_B0, 0xf7bb4433);
	OUTREG(MC_IND_INDEX, 0);

	OUTREG(CRTC_MORE_CNTL, INREG(CRTC_MORE_CNTL));

	पंचांगp = INPLL(pllVCLK_ECP_CNTL);
	OUTPLL(pllVCLK_ECP_CNTL, पंचांगp);
	पंचांगp = INPLL(pllPIXCLKS_CNTL);
	OUTPLL(pllPIXCLKS_CNTL, पंचांगp);

	OUTPLL(MCLK_CNTL, 0xaa3f0000);
	OUTPLL(SCLK_CNTL, 0xffff0000);
	OUTPLL(pllMPLL_AUX_CNTL, 6);
	OUTPLL(pllSPLL_AUX_CNTL, 1);
	OUTPLL(MDLL_CKO, 0x9f009f);
	OUTPLL(MDLL_RDCKA, 0x830083);
	OUTPLL(pllMDLL_RDCKB, 0x830083);
	OUTPLL(PPLL_CNTL, 0xa433);
	OUTPLL(P2PLL_CNTL, 0xa433);
	OUTPLL(MPLL_CNTL, 0x0400a403);
	OUTPLL(SPLL_CNTL, 0x0400a433);

	पंचांगp = INPLL(M_SPLL_REF_FB_DIV);
	OUTPLL(M_SPLL_REF_FB_DIV, पंचांगp);
	पंचांगp = INPLL(M_SPLL_REF_FB_DIV);
	OUTPLL(M_SPLL_REF_FB_DIV, पंचांगp | 0xc);
	INPLL(M_SPLL_REF_FB_DIV);

	पंचांगp = INPLL(MPLL_CNTL);
	OUTREG8(CLOCK_CNTL_INDEX, MPLL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA + 1, (पंचांगp >> 8) & 0xff);
	radeon_pll_errata_after_data(rinfo);

	पंचांगp = INPLL(M_SPLL_REF_FB_DIV);
	OUTPLL(M_SPLL_REF_FB_DIV, पंचांगp | 0x5900);

	पंचांगp = INPLL(MPLL_CNTL);
	OUTPLL(MPLL_CNTL, पंचांगp & ~0x2);
	mdelay(1);
	पंचांगp = INPLL(MPLL_CNTL);
	OUTPLL(MPLL_CNTL, पंचांगp & ~0x1);
	mdelay(10);

	OUTPLL(MCLK_CNTL, 0xaa3f1212);
	mdelay(1);

	INPLL(M_SPLL_REF_FB_DIV);
	INPLL(MCLK_CNTL);
	INPLL(M_SPLL_REF_FB_DIV);

	पंचांगp = INPLL(SPLL_CNTL);
	OUTREG8(CLOCK_CNTL_INDEX, SPLL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA + 1, (पंचांगp >> 8) & 0xff);
	radeon_pll_errata_after_data(rinfo);

	पंचांगp = INPLL(M_SPLL_REF_FB_DIV);
	OUTPLL(M_SPLL_REF_FB_DIV, पंचांगp | 0x780000);

	पंचांगp = INPLL(SPLL_CNTL);
	OUTPLL(SPLL_CNTL, पंचांगp & ~0x1);
	mdelay(1);
	पंचांगp = INPLL(SPLL_CNTL);
	OUTPLL(SPLL_CNTL, पंचांगp & ~0x2);
	mdelay(10);

	पंचांगp = INPLL(SCLK_CNTL);
	OUTPLL(SCLK_CNTL, पंचांगp | 2);
	mdelay(1);

	cko = INPLL(pllMDLL_CKO);
	cka = INPLL(pllMDLL_RDCKA);
	ckb = INPLL(pllMDLL_RDCKB);

	cko &= ~(MDLL_CKO__MCKOA_SLEEP | MDLL_CKO__MCKOB_SLEEP);
	OUTPLL(pllMDLL_CKO, cko);
	mdelay(1);
	cko &= ~(MDLL_CKO__MCKOA_RESET | MDLL_CKO__MCKOB_RESET);
	OUTPLL(pllMDLL_CKO, cko);
	mdelay(5);

	cka &= ~(MDLL_RDCKA__MRDCKA0_SLEEP | MDLL_RDCKA__MRDCKA1_SLEEP);
	OUTPLL(pllMDLL_RDCKA, cka);
	mdelay(1);
	cka &= ~(MDLL_RDCKA__MRDCKA0_RESET | MDLL_RDCKA__MRDCKA1_RESET);
	OUTPLL(pllMDLL_RDCKA, cka);
	mdelay(5);

	ckb &= ~(MDLL_RDCKB__MRDCKB0_SLEEP | MDLL_RDCKB__MRDCKB1_SLEEP);
	OUTPLL(pllMDLL_RDCKB, ckb);
	mdelay(1);
	ckb &= ~(MDLL_RDCKB__MRDCKB0_RESET | MDLL_RDCKB__MRDCKB1_RESET);
	OUTPLL(pllMDLL_RDCKB, ckb);
	mdelay(5);

	OUTMC(rinfo, ixMC_CHP_IO_CNTL_A1, 0x151550ff);
	OUTREG(MC_IND_INDEX, 0);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_B1, 0x151550ff);
	OUTREG(MC_IND_INDEX, 0);
	mdelay(1);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_A1, 0x141550ff);
	OUTREG(MC_IND_INDEX, 0);
	OUTMC(rinfo, ixMC_CHP_IO_CNTL_B1, 0x141550ff);
	OUTREG(MC_IND_INDEX, 0);
	mdelay(1);

	OUTPLL(pllHTOTAL_CNTL, 0);
	OUTPLL(pllHTOTAL2_CNTL, 0);

	OUTREG(MEM_CNTL, 0x29002901);
	OUTREG(MEM_SDRAM_MODE_REG, 0x45320032);	/* XXX use save_regs[35]? */
	OUTREG(EXT_MEM_CNTL, 0x1a394333);
	OUTREG(MEM_IO_CNTL_A1, 0x0aac0aac);
	OUTREG(MEM_INIT_LATENCY_TIMER, 0x34444444);
	OUTREG(MEM_REFRESH_CNTL, 0x1f1f7218);	/* XXX or save_regs[42]? */
	OUTREG(MC_DEBUG, 0);
	OUTREG(MEM_IO_OE_CNTL, 0x04300430);

	OUTMC(rinfo, ixMC_IMP_CNTL, 0x00f460d6);
	OUTREG(MC_IND_INDEX, 0);
	OUTMC(rinfo, ixMC_IMP_CNTL_0, 0x00009249);
	OUTREG(MC_IND_INDEX, 0);

	OUTREG(CNFG_MEMSIZE, rinfo->video_ram);

	radeon_pm_full_reset_sdram(rinfo);

	INREG(FP_GEN_CNTL);
	OUTREG(TMDS_CNTL, 0x01000000);	/* XXX ? */
	पंचांगp = INREG(FP_GEN_CNTL);
	पंचांगp |= FP_CRTC_DONT_SHADOW_HEND | FP_CRTC_DONT_SHADOW_VPAR | 0x200;
	OUTREG(FP_GEN_CNTL, पंचांगp);

	पंचांगp = INREG(DISP_OUTPUT_CNTL);
	पंचांगp &= ~0x400;
	OUTREG(DISP_OUTPUT_CNTL, पंचांगp);

	OUTPLL(CLK_PIN_CNTL, rinfo->save_regs[4]);
	OUTPLL(CLK_PWRMGT_CNTL, rinfo->save_regs[1]);
	OUTPLL(PLL_PWRMGT_CNTL, rinfo->save_regs[0]);

	पंचांगp = INPLL(MCLK_MISC);
	पंचांगp |= MCLK_MISC__MC_MCLK_DYN_ENABLE | MCLK_MISC__IO_MCLK_DYN_ENABLE;
	OUTPLL(MCLK_MISC, पंचांगp);

	पंचांगp = INPLL(SCLK_CNTL);
	OUTPLL(SCLK_CNTL, पंचांगp);

	OUTREG(CRTC_MORE_CNTL, 0);
	OUTREG8(CRTC_GEN_CNTL+1, 6);
	OUTREG8(CRTC_GEN_CNTL+3, 1);
	OUTREG(CRTC_PITCH, 32);

	पंचांगp = INPLL(VCLK_ECP_CNTL);
	OUTPLL(VCLK_ECP_CNTL, पंचांगp);

	पंचांगp = INPLL(PPLL_CNTL);
	OUTPLL(PPLL_CNTL, पंचांगp);

	/* palette stuff and BIOS_1_SCRATCH... */

	पंचांगp = INREG(FP_GEN_CNTL);
	पंचांगp2 = INREG(TMDS_TRANSMITTER_CNTL);
	पंचांगp |= 2;
	OUTREG(FP_GEN_CNTL, पंचांगp);
	mdelay(5);
	OUTREG(FP_GEN_CNTL, पंचांगp);
	mdelay(5);
	OUTREG(TMDS_TRANSMITTER_CNTL, पंचांगp2);
	OUTREG(CRTC_MORE_CNTL, 0);
	mdelay(20);

	पंचांगp = INREG(CRTC_MORE_CNTL);
	OUTREG(CRTC_MORE_CNTL, पंचांगp);

	cgc = INREG(CRTC_GEN_CNTL);
	cec = INREG(CRTC_EXT_CNTL);
	c2gc = INREG(CRTC2_GEN_CNTL);

	OUTREG(CRTC_H_SYNC_STRT_WID, 0x008e0580);
	OUTREG(CRTC_H_TOTAL_DISP, 0x009f00d2);
	OUTREG8(CLOCK_CNTL_INDEX, HTOTAL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA, 0);
	radeon_pll_errata_after_data(rinfo);
	OUTREG(CRTC_V_SYNC_STRT_WID, 0x00830403);
	OUTREG(CRTC_V_TOTAL_DISP, 0x03ff0429);
	OUTREG(FP_CRTC_H_TOTAL_DISP, 0x009f0033);
	OUTREG(FP_H_SYNC_STRT_WID, 0x008e0080);
	OUTREG(CRT_CRTC_H_SYNC_STRT_WID, 0x008e0080);
	OUTREG(FP_CRTC_V_TOTAL_DISP, 0x03ff002a);
	OUTREG(FP_V_SYNC_STRT_WID, 0x00830004);
	OUTREG(CRT_CRTC_V_SYNC_STRT_WID, 0x00830004);
	OUTREG(FP_HORZ_VERT_ACTIVE, 0x009f03ff);
	OUTREG(FP_HORZ_STRETCH, 0);
	OUTREG(FP_VERT_STRETCH, 0);
	OUTREG(OVR_CLR, 0);
	OUTREG(OVR_WID_LEFT_RIGHT, 0);
	OUTREG(OVR_WID_TOP_BOTTOM, 0);

	पंचांगp = INPLL(PPLL_REF_DIV);
	पंचांगp = (पंचांगp & ~PPLL_REF_DIV_MASK) | rinfo->pll.ref_भाग;
	OUTPLL(PPLL_REF_DIV, पंचांगp);
	INPLL(PPLL_REF_DIV);

	OUTREG8(CLOCK_CNTL_INDEX, PPLL_CNTL + PLL_WR_EN);
	radeon_pll_errata_after_index(rinfo);
	OUTREG8(CLOCK_CNTL_DATA + 1, 0xbc);
	radeon_pll_errata_after_data(rinfo);

	पंचांगp = INREG(CLOCK_CNTL_INDEX);
	radeon_pll_errata_after_index(rinfo);
	OUTREG(CLOCK_CNTL_INDEX, पंचांगp & 0xff);
	radeon_pll_errata_after_index(rinfo);
	radeon_pll_errata_after_data(rinfo);

	OUTPLL(PPLL_DIV_0, 0x48090);

	पंचांगp = INPLL(PPLL_CNTL);
	OUTPLL(PPLL_CNTL, पंचांगp & ~0x2);
	mdelay(1);
	पंचांगp = INPLL(PPLL_CNTL);
	OUTPLL(PPLL_CNTL, पंचांगp & ~0x1);
	mdelay(10);

	पंचांगp = INPLL(VCLK_ECP_CNTL);
	OUTPLL(VCLK_ECP_CNTL, पंचांगp | 3);
	mdelay(1);

	पंचांगp = INPLL(VCLK_ECP_CNTL);
	OUTPLL(VCLK_ECP_CNTL, पंचांगp);

	c2gc |= CRTC2_DISP_REQ_EN_B;
	OUTREG(CRTC2_GEN_CNTL, c2gc);
	cgc |= CRTC_EN;
	OUTREG(CRTC_GEN_CNTL, cgc);
	OUTREG(CRTC_EXT_CNTL, cec);
	OUTREG(CRTC_PITCH, 0xa0);
	OUTREG(CRTC_OFFSET, 0);
	OUTREG(CRTC_OFFSET_CNTL, 0);

	OUTREG(GRPH_BUFFER_CNTL, 0x20117c7c);
	OUTREG(GRPH2_BUFFER_CNTL, 0x00205c5c);

	पंचांगp2 = INREG(FP_GEN_CNTL);
	पंचांगp = INREG(TMDS_TRANSMITTER_CNTL);
	OUTREG(0x2a8, 0x0000061b);
	पंचांगp |= TMDS_PLL_EN;
	OUTREG(TMDS_TRANSMITTER_CNTL, पंचांगp);
	mdelay(1);
	पंचांगp &= ~TMDS_PLLRST;
	OUTREG(TMDS_TRANSMITTER_CNTL, पंचांगp);
	पंचांगp2 &= ~2;
	पंचांगp2 |= FP_TMDS_EN;
	OUTREG(FP_GEN_CNTL, पंचांगp2);
	mdelay(5);
	पंचांगp2 |= FP_FPON;
	OUTREG(FP_GEN_CNTL, पंचांगp2);

	OUTREG(CUR_HORZ_VERT_OFF, CUR_LOCK | 1);
	cgc = INREG(CRTC_GEN_CNTL);
	OUTREG(CUR_HORZ_VERT_POSN, 0xbfff0fff);
	cgc |= 0x10000;
	OUTREG(CUR_OFFSET, 0);
पूर्ण
#पूर्ण_अगर /* 0 */

#पूर्ण_अगर /* CONFIG_PPC */

अटल व्योम radeonfb_whack_घातer_state(काष्ठा radeonfb_info *rinfo, pci_घातer_t state)
अणु
	u16 pwr_cmd;

	क्रम (;;) अणु
		pci_पढ़ो_config_word(rinfo->pdev,
				     rinfo->pdev->pm_cap + PCI_PM_CTRL,
				     &pwr_cmd);
		अगर (pwr_cmd & state)
			अवरोध;
		pwr_cmd = (pwr_cmd & ~PCI_PM_CTRL_STATE_MASK) | state;
		pci_ग_लिखो_config_word(rinfo->pdev,
				      rinfo->pdev->pm_cap + PCI_PM_CTRL,
				      pwr_cmd);
		msleep(500);
	पूर्ण
	rinfo->pdev->current_state = state;
पूर्ण

अटल व्योम radeon_set_suspend(काष्ठा radeonfb_info *rinfo, पूर्णांक suspend)
अणु
	u32 पंचांगp;

	अगर (!rinfo->pdev->pm_cap)
		वापस;

	/* Set the chip पूर्णांकo appropriate suspend mode (we use D2,
	 * D3 would require a compete re-initialization of the chip,
	 * including PCI config रेजिस्टरs, घड़ीs, AGP conf, ...)
	 */
	अगर (suspend) अणु
		prपूर्णांकk(KERN_DEBUG "radeonfb (%s): switching to D2 state...\n",
		       pci_name(rinfo->pdev));

		/* Disable dynamic घातer management of घड़ीs क्रम the
		 * duration of the suspend/resume process
		 */
		radeon_pm_disable_dynamic_mode(rinfo);

		/* Save some रेजिस्टरs */
		radeon_pm_save_regs(rinfo, 0);

		/* Prepare mobility chips क्रम suspend.
		 */
		अगर (rinfo->is_mobility) अणु
			/* Program V2CLK */
			radeon_pm_program_v2clk(rinfo);
		
			/* Disable IO PADs */
			radeon_pm_disable_iopad(rinfo);

			/* Set low current */
			radeon_pm_low_current(rinfo);

			/* Prepare chip क्रम घातer management */
			radeon_pm_setup_क्रम_suspend(rinfo);

			अगर (rinfo->family <= CHIP_FAMILY_RV280) अणु
				/* Reset the MDLL */
				/* because both INPLL and OUTPLL take the same
				 * lock, that's why. */
				पंचांगp = INPLL( pllMDLL_CKO) | MDLL_CKO__MCKOA_RESET
					| MDLL_CKO__MCKOB_RESET;
				OUTPLL( pllMDLL_CKO, पंचांगp );
			पूर्ण
		पूर्ण

		/* Switch PCI घातer management to D2. */
		pci_disable_device(rinfo->pdev);
		pci_save_state(rinfo->pdev);
		/* The chip seems to need us to whack the PM रेजिस्टर
		 * repeatedly until it sticks. We करो that -prior- to
		 * calling pci_set_घातer_state()
		 */
		radeonfb_whack_घातer_state(rinfo, PCI_D2);
		pci_platक्रमm_घातer_transition(rinfo->pdev, PCI_D2);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "radeonfb (%s): switching to D0 state...\n",
		       pci_name(rinfo->pdev));

		अगर (rinfo->family <= CHIP_FAMILY_RV250) अणु
			/* Reset the SDRAM controller  */
			radeon_pm_full_reset_sdram(rinfo);

			/* Restore some रेजिस्टरs */
			radeon_pm_restore_regs(rinfo);
		पूर्ण अन्यथा अणु
			/* Restore रेजिस्टरs first */
			radeon_pm_restore_regs(rinfo);
			/* init sdram controller */
			radeon_pm_full_reset_sdram(rinfo);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक radeonfb_pci_suspend_late(काष्ठा device *dev, pm_message_t mesg)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
        काष्ठा fb_info *info = pci_get_drvdata(pdev);
        काष्ठा radeonfb_info *rinfo = info->par;

	अगर (mesg.event == pdev->dev.घातer.घातer_state.event)
		वापस 0;

	prपूर्णांकk(KERN_DEBUG "radeonfb (%s): suspending for event: %d...\n",
	       pci_name(pdev), mesg.event);

	/* For suspend-to-disk, we cheat here. We करोn't suspend anything and
	 * let fbcon जारी drawing until we are all set. That shouldn't
	 * really cause any problem at this poपूर्णांक, provided that the wakeup
	 * code knows that any state in memory may not match the HW
	 */
	चयन (mesg.event) अणु
	हाल PM_EVENT_FREEZE:		/* about to take snapshot */
	हाल PM_EVENT_PRETHAW:		/* beक्रमe restoring snapshot */
		जाओ करोne;
	पूर्ण

	console_lock();

	fb_set_suspend(info, 1);

	अगर (!(info->flags & FBINFO_HWACCEL_DISABLED)) अणु
		/* Make sure engine is reset */
		radeon_engine_idle();
		radeonfb_engine_reset(rinfo);
		radeon_engine_idle();
	पूर्ण

	/* Blank display and LCD */
	radeon_screen_blank(rinfo, FB_BLANK_POWERDOWN, 1);

	/* Sleep */
	rinfo->asleep = 1;
	rinfo->lock_blank = 1;
	del_समयr_sync(&rinfo->lvds_समयr);

#अगर_घोषित CONFIG_PPC_PMAC
	/* On घातermac, we have hooks to properly suspend/resume AGP now,
	 * use them here. We'll ultimately need some generic support here,
	 * but the generic code isn't quite पढ़ोy क्रम that yet
	 */
	pmac_suspend_agp_क्रम_card(pdev);
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

	/* If we support wakeup from घातeroff, we save all regs we can including cfg
	 * space
	 */
	अगर (rinfo->pm_mode & radeon_pm_off) अणु
		/* Always disable dynamic घड़ीs or weird things are happening when
		 * the chip goes off (basically the panel करोesn't shut करोwn properly
		 * and we crash on wakeup),
		 * also, we want the saved regs context to have no dynamic घड़ीs in
		 * it, we'll restore the dynamic घड़ीs state on wakeup
		 */
		radeon_pm_disable_dynamic_mode(rinfo);
		msleep(50);
		radeon_pm_save_regs(rinfo, 1);

		अगर (rinfo->is_mobility && !(rinfo->pm_mode & radeon_pm_d2)) अणु
			/* Switch off LVDS पूर्णांकerface */
			usleep_range(1000, 2000);
			OUTREG(LVDS_GEN_CNTL, INREG(LVDS_GEN_CNTL) & ~(LVDS_BL_MOD_EN));
			usleep_range(1000, 2000);
			OUTREG(LVDS_GEN_CNTL, INREG(LVDS_GEN_CNTL) & ~(LVDS_EN | LVDS_ON));
			OUTREG(LVDS_PLL_CNTL, (INREG(LVDS_PLL_CNTL) & ~30000) | 0x20000);
			msleep(20);
			OUTREG(LVDS_GEN_CNTL, INREG(LVDS_GEN_CNTL) & ~(LVDS_DIGON));
		पूर्ण
	पूर्ण
	/* If we support D2, we go to it (should be fixed later with a flag क्रमcing
	 * D3 only क्रम some laptops)
	 */
	अगर (rinfo->pm_mode & radeon_pm_d2)
		radeon_set_suspend(rinfo, 1);

	console_unlock();

 करोne:
	pdev->dev.घातer.घातer_state = mesg;

	वापस 0;
पूर्ण

अटल पूर्णांक radeonfb_pci_suspend(काष्ठा device *dev)
अणु
	वापस radeonfb_pci_suspend_late(dev, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक radeonfb_pci_hibernate(काष्ठा device *dev)
अणु
	वापस radeonfb_pci_suspend_late(dev, PMSG_HIBERNATE);
पूर्ण

अटल पूर्णांक radeonfb_pci_मुक्तze(काष्ठा device *dev)
अणु
	वापस radeonfb_pci_suspend_late(dev, PMSG_FREEZE);
पूर्ण

अटल पूर्णांक radeon_check_घातer_loss(काष्ठा radeonfb_info *rinfo)
अणु
	वापस rinfo->save_regs[4] != INPLL(CLK_PIN_CNTL) ||
	       rinfo->save_regs[2] != INPLL(MCLK_CNTL) ||
	       rinfo->save_regs[3] != INPLL(SCLK_CNTL);
पूर्ण

अटल पूर्णांक radeonfb_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
        काष्ठा fb_info *info = pci_get_drvdata(pdev);
        काष्ठा radeonfb_info *rinfo = info->par;
	पूर्णांक rc = 0;

	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_ON)
		वापस 0;

	अगर (rinfo->no_schedule) अणु
		अगर (!console_trylock())
			वापस 0;
	पूर्ण अन्यथा
		console_lock();

	prपूर्णांकk(KERN_DEBUG "radeonfb (%s): resuming from state: %d...\n",
	       pci_name(pdev), pdev->dev.घातer.घातer_state.event);

	/* PCI state will have been restored by the core, so
	 * we should be in D0 now with our config space fully
	 * restored
	 */
	अगर (pdev->dev.घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		/* Wakeup chip */
		अगर ((rinfo->pm_mode & radeon_pm_off) && radeon_check_घातer_loss(rinfo)) अणु
			अगर (rinfo->reinit_func != शून्य)
				rinfo->reinit_func(rinfo);
			अन्यथा अणु
				prपूर्णांकk(KERN_ERR "radeonfb (%s): can't resume radeon from"
				       " D3 cold, need softboot !", pci_name(pdev));
				rc = -EIO;
				जाओ bail;
			पूर्ण
		पूर्ण
		/* If we support D2, try to resume... we should check what was our
		 * state though... (were we really in D2 state ?). Right now, this code
		 * is only enable on Macs so it's fine.
		 */
		अन्यथा अगर (rinfo->pm_mode & radeon_pm_d2)
			radeon_set_suspend(rinfo, 0);

		rinfo->asleep = 0;
	पूर्ण अन्यथा
		radeon_engine_idle();

	/* Restore display & engine */
	radeon_ग_लिखो_mode (rinfo, &rinfo->state, 1);
	अगर (!(info->flags & FBINFO_HWACCEL_DISABLED))
		radeonfb_engine_init (rinfo);

	fb_pan_display(info, &info->var);
	fb_set_cmap(&info->cmap, info);

	/* Refresh */
	fb_set_suspend(info, 0);

	/* Unblank */
	rinfo->lock_blank = 0;
	radeon_screen_blank(rinfo, FB_BLANK_UNBLANK, 1);

#अगर_घोषित CONFIG_PPC_PMAC
	/* On घातermac, we have hooks to properly suspend/resume AGP now,
	 * use them here. We'll ultimately need some generic support here,
	 * but the generic code isn't quite पढ़ोy क्रम that yet
	 */
	pmac_resume_agp_क्रम_card(pdev);
#पूर्ण_अगर /* CONFIG_PPC_PMAC */


	/* Check status of dynclk */
	अगर (rinfo->dynclk == 1)
		radeon_pm_enable_dynamic_mode(rinfo);
	अन्यथा अगर (rinfo->dynclk == 0)
		radeon_pm_disable_dynamic_mode(rinfo);

	pdev->dev.घातer.घातer_state = PMSG_ON;

 bail:
	console_unlock();

	वापस rc;
पूर्ण

स्थिर काष्ठा dev_pm_ops radeonfb_pci_pm_ops = अणु
	.suspend	= radeonfb_pci_suspend,
	.resume		= radeonfb_pci_resume,
	.मुक्तze		= radeonfb_pci_मुक्तze,
	.thaw		= radeonfb_pci_resume,
	.घातeroff	= radeonfb_pci_hibernate,
	.restore	= radeonfb_pci_resume,
पूर्ण;

#अगर_घोषित CONFIG_PPC__disabled
अटल व्योम radeonfb_early_resume(व्योम *data)
अणु
        काष्ठा radeonfb_info *rinfo = data;

	rinfo->no_schedule = 1;
	pci_restore_state(rinfo->pdev);
	radeonfb_pci_resume(rinfo->pdev);
	rinfo->no_schedule = 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC */

#पूर्ण_अगर /* CONFIG_PM */

व्योम radeonfb_pm_init(काष्ठा radeonfb_info *rinfo, पूर्णांक dynclk, पूर्णांक ignore_devlist, पूर्णांक क्रमce_sleep)
अणु
	/* Enable/Disable dynamic घड़ीs: TODO add sysfs access */
	अगर (rinfo->family == CHIP_FAMILY_RS480)
		rinfo->dynclk = -1;
	अन्यथा
		rinfo->dynclk = dynclk;

	अगर (rinfo->dynclk == 1) अणु
		radeon_pm_enable_dynamic_mode(rinfo);
		prपूर्णांकk("radeonfb: Dynamic Clock Power Management enabled\n");
	पूर्ण अन्यथा अगर (rinfo->dynclk == 0) अणु
		radeon_pm_disable_dynamic_mode(rinfo);
		prपूर्णांकk("radeonfb: Dynamic Clock Power Management disabled\n");
	पूर्ण

#अगर defined(CONFIG_PM)
#अगर defined(CONFIG_PPC_PMAC)
	/* Check अगर we can घातer manage on suspend/resume. We can करो
	 * D2 on M6, M7 and M9, and we can resume from D3 cold a few other
	 * "Mac" cards, but that's all. We need more infos about what the
	 * BIOS करोes tho. Right now, all this PM stuff is pmac-only क्रम that
	 * reason. --BenH
	 */
	अगर (machine_is(घातermac) && rinfo->of_node) अणु
		अगर (rinfo->is_mobility && rinfo->pdev->pm_cap &&
		    rinfo->family <= CHIP_FAMILY_RV250)
			rinfo->pm_mode |= radeon_pm_d2;

		/* We can restart Jasper (M10 chip in albooks), BlueStone (7500 chip
		 * in some desktop G4s), Via (M9+ chip on iBook G4) and
		 * Snowy (M11 chip on iBook G4 manufactured after July 2005)
		 */
		अगर (of_node_name_eq(rinfo->of_node, "ATY,JasperParent") ||
		    of_node_name_eq(rinfo->of_node, "ATY,SnowyParent")) अणु
			rinfo->reinit_func = radeon_reinitialize_M10;
			rinfo->pm_mode |= radeon_pm_off;
		पूर्ण
#अगर 0 /* Not पढ़ोy yet */
		अगर (!म_भेद(rinfo->of_node->name, "ATY,BlueStoneParent")) अणु
			rinfo->reinit_func = radeon_reinitialize_QW;
			rinfo->pm_mode |= radeon_pm_off;
		पूर्ण
#पूर्ण_अगर
		अगर (of_node_name_eq(rinfo->of_node, "ATY,ViaParent")) अणु
			rinfo->reinit_func = radeon_reinitialize_M9P;
			rinfo->pm_mode |= radeon_pm_off;
		पूर्ण

		/* If any of the above is set, we assume the machine can sleep/resume.
		 * It's a bit of a "shortcut" but will work fine. Ideally, we need infos
		 * from the platक्रमm about what happens to the chip...
		 * Now we tell the platक्रमm about our capability
		 */
		अगर (rinfo->pm_mode != radeon_pm_none) अणु
			pmac_call_feature(PMAC_FTR_DEVICE_CAN_WAKE, rinfo->of_node, 0, 1);
#अगर 0 /* Disable the early video resume hack क्रम now as it's causing problems, among
       * others we now rely on the PCI core restoring the config space क्रम us, which
       * isn't the हाल with that hack, and that code path causes various things to
       * be called with पूर्णांकerrupts off जबतक they shouldn't. I'm leaving the code in
       * as it can be useful क्रम debugging purposes
       */
			pmac_set_early_video_resume(radeonfb_early_resume, rinfo);
#पूर्ण_अगर
		पूर्ण

#अगर 0
		/* Power करोwn TV DAC, that saves a signअगरicant amount of घातer,
		 * we'll have something better once we actually have some TVOut
		 * support
		 */
		OUTREG(TV_DAC_CNTL, INREG(TV_DAC_CNTL) | 0x07000000);
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर /* defined(CONFIG_PPC_PMAC) */
#पूर्ण_अगर /* defined(CONFIG_PM) */

	अगर (ignore_devlist)
		prपूर्णांकk(KERN_DEBUG
		       "radeonfb: skipping test for device workarounds\n");
	अन्यथा
		radeon_apply_workarounds(rinfo);

	अगर (क्रमce_sleep) अणु
		prपूर्णांकk(KERN_DEBUG
		       "radeonfb: forcefully enabling D2 sleep mode\n");
		rinfo->pm_mode |= radeon_pm_d2;
	पूर्ण
पूर्ण

व्योम radeonfb_pm_निकास(काष्ठा radeonfb_info *rinfo)
अणु
#अगर defined(CONFIG_PM) && defined(CONFIG_PPC_PMAC)
	अगर (rinfo->pm_mode != radeon_pm_none)
		pmac_set_early_video_resume(शून्य, शून्य);
#पूर्ण_अगर
पूर्ण
