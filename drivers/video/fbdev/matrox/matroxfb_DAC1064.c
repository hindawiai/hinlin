<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200, G400 and G450.
 *
 * (c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
 *
 * Portions Copyright (c) 2001 Matrox Graphics Inc.
 *
 * Version: 1.65 2002/08/14
 *
 * See matroxfb_base.c क्रम contributors.
 *
 */


#समावेश "matroxfb_DAC1064.h"
#समावेश "matroxfb_misc.h"
#समावेश "matroxfb_accel.h"
#समावेश "g450_pll.h"
#समावेश <linux/matroxfb.h>

#अगर_घोषित NEED_DAC1064
#घोषणा outDAC1064 matroxfb_DAC_out
#घोषणा inDAC1064 matroxfb_DAC_in

#घोषणा DAC1064_OPT_SCLK_PCI	0x00
#घोषणा DAC1064_OPT_SCLK_PLL	0x01
#घोषणा DAC1064_OPT_SCLK_EXT	0x02
#घोषणा DAC1064_OPT_SCLK_MASK	0x03
#घोषणा DAC1064_OPT_GDIV1	0x04	/* maybe it is GDIV2 on G100 ?! */
#घोषणा DAC1064_OPT_GDIV3	0x00
#घोषणा DAC1064_OPT_MDIV1	0x08
#घोषणा DAC1064_OPT_MDIV2	0x00
#घोषणा DAC1064_OPT_RESERVED	0x10

अटल व्योम DAC1064_calcघड़ी(स्थिर काष्ठा matrox_fb_info *minfo,
			      अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक fmax,
			      अचिन्हित पूर्णांक *in, अचिन्हित पूर्णांक *feed,
			      अचिन्हित पूर्णांक *post)
अणु
	अचिन्हित पूर्णांक fvco;
	अचिन्हित पूर्णांक p;

	DBG(__func__)
	
	/* only क्रम devices older than G450 */

	fvco = PLL_calcघड़ी(minfo, freq, fmax, in, feed, &p);
	
	p = (1 << p) - 1;
	अगर (fvco <= 100000)
		;
	अन्यथा अगर (fvco <= 140000)
		p |= 0x08;
	अन्यथा अगर (fvco <= 180000)
		p |= 0x10;
	अन्यथा
		p |= 0x18;
	*post = p;
पूर्ण

/* they must be in POS order */
अटल स्थिर अचिन्हित अक्षर MGA1064_DAC_regs[] = अणु
		M1064_XCURADDL, M1064_XCURADDH, M1064_XCURCTRL,
		M1064_XCURCOL0RED, M1064_XCURCOL0GREEN, M1064_XCURCOL0BLUE,
		M1064_XCURCOL1RED, M1064_XCURCOL1GREEN, M1064_XCURCOL1BLUE,
		M1064_XCURCOL2RED, M1064_XCURCOL2GREEN, M1064_XCURCOL2BLUE,
		DAC1064_XVREFCTRL, M1064_XMULCTRL, M1064_XPIXCLKCTRL, M1064_XGENCTRL,
		M1064_XMISCCTRL,
		M1064_XGENIOCTRL, M1064_XGENIODATA, M1064_XZOOMCTRL, M1064_XSENSETEST,
		M1064_XCRCBITSEL,
		M1064_XCOLKEYMASKL, M1064_XCOLKEYMASKH, M1064_XCOLKEYL, M1064_XCOLKEYH पूर्ण;

अटल स्थिर अचिन्हित अक्षर MGA1064_DAC[] = अणु
		0x00, 0x00, M1064_XCURCTRL_DIS,
		0x00, 0x00, 0x00, 	/* black */
		0xFF, 0xFF, 0xFF,	/* white */
		0xFF, 0x00, 0x00,	/* red */
		0x00, 0,
		M1064_XPIXCLKCTRL_PLL_UP | M1064_XPIXCLKCTRL_EN | M1064_XPIXCLKCTRL_SRC_PLL,
		M1064_XGENCTRL_VS_0 | M1064_XGENCTRL_ALPHA_DIS | M1064_XGENCTRL_BLACK_0IRE | M1064_XGENCTRL_NO_SYNC_ON_GREEN,
		M1064_XMISCCTRL_DAC_8BIT,
		0x00, 0x00, M1064_XZOOMCTRL_1, M1064_XSENSETEST_BCOMP | M1064_XSENSETEST_GCOMP | M1064_XSENSETEST_RCOMP | M1064_XSENSETEST_PDOWN,
		0x00,
		0x00, 0x00, 0xFF, 0xFFपूर्ण;

अटल व्योम DAC1064_setpclk(काष्ठा matrox_fb_info *minfo, अचिन्हित दीर्घ fout)
अणु
	अचिन्हित पूर्णांक m, n, p;

	DBG(__func__)

	DAC1064_calcघड़ी(minfo, fout, minfo->max_pixel_घड़ी, &m, &n, &p);
	minfo->hw.DACclk[0] = m;
	minfo->hw.DACclk[1] = n;
	minfo->hw.DACclk[2] = p;
पूर्ण

अटल व्योम DAC1064_seपंचांगclk(काष्ठा matrox_fb_info *minfo, पूर्णांक oscinfo,
			    अचिन्हित दीर्घ fmem)
अणु
	u_पूर्णांक32_t mx;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	अगर (minfo->devflags.noinit) अणु
		/* पढ़ो MCLK and give up... */
		hw->DACclk[3] = inDAC1064(minfo, DAC1064_XSYSPLLM);
		hw->DACclk[4] = inDAC1064(minfo, DAC1064_XSYSPLLN);
		hw->DACclk[5] = inDAC1064(minfo, DAC1064_XSYSPLLP);
		वापस;
	पूर्ण
	mx = hw->MXoptionReg | 0x00000004;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, mx);
	mx &= ~0x000000BB;
	अगर (oscinfo & DAC1064_OPT_GDIV1)
		mx |= 0x00000008;
	अगर (oscinfo & DAC1064_OPT_MDIV1)
		mx |= 0x00000010;
	अगर (oscinfo & DAC1064_OPT_RESERVED)
		mx |= 0x00000080;
	अगर ((oscinfo & DAC1064_OPT_SCLK_MASK) == DAC1064_OPT_SCLK_PLL) अणु
		/* select PCI घड़ी until we have setup oscilator... */
		पूर्णांक clk;
		अचिन्हित पूर्णांक m, n, p;

		/* घातerup प्रणाली PLL, select PCI घड़ी */
		mx |= 0x00000020;
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, mx);
		mx &= ~0x00000004;
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, mx);

		/* !!! you must not access device अगर MCLK is not running !!!
		   Doing so cause immediate PCI lockup :-( Maybe they should
		   generate ABORT or I/O (parity...) error and Linux should
		   recover from this... (समाप्त driver/process). But world is not
		   perfect... */
		/* (bit 2 of PCI_OPTION_REG must be 0... and bits 0,1 must not
		   select PLL... because of PLL can be stopped at this समय) */
		DAC1064_calcघड़ी(minfo, fmem, minfo->max_pixel_घड़ी, &m, &n, &p);
		outDAC1064(minfo, DAC1064_XSYSPLLM, hw->DACclk[3] = m);
		outDAC1064(minfo, DAC1064_XSYSPLLN, hw->DACclk[4] = n);
		outDAC1064(minfo, DAC1064_XSYSPLLP, hw->DACclk[5] = p);
		क्रम (clk = 65536; clk; --clk) अणु
			अगर (inDAC1064(minfo, DAC1064_XSYSPLLSTAT) & 0x40)
				अवरोध;
		पूर्ण
		अगर (!clk)
			prपूर्णांकk(KERN_ERR "matroxfb: aiee, SYSPLL not locked\n");
		/* select PLL */
		mx |= 0x00000005;
	पूर्ण अन्यथा अणु
		/* select specअगरied प्रणाली घड़ी source */
		mx |= oscinfo & DAC1064_OPT_SCLK_MASK;
	पूर्ण
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, mx);
	mx &= ~0x00000004;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, mx);
	hw->MXoptionReg = mx;
पूर्ण

#अगर_घोषित CONFIG_FB_MATROX_G
अटल व्योम g450_set_plls(काष्ठा matrox_fb_info *minfo)
अणु
	u_पूर्णांक32_t c2_ctl;
	अचिन्हित पूर्णांक pxc;
	काष्ठा matrox_hw_state *hw = &minfo->hw;
	पूर्णांक pixelmnp;
	पूर्णांक videomnp;
	
	c2_ctl = hw->crtc2.ctl & ~0x4007;	/* Clear PLL + enable क्रम CRTC2 */
	c2_ctl |= 0x0001;			/* Enable CRTC2 */
	hw->DACreg[POS1064_XPWRCTRL] &= ~0x02;	/* Stop VIDEO PLL */
	pixelmnp = minfo->crtc1.mnp;
	videomnp = minfo->crtc2.mnp;
	अगर (videomnp < 0) अणु
		c2_ctl &= ~0x0001;			/* Disable CRTC2 */
		hw->DACreg[POS1064_XPWRCTRL] &= ~0x10;	/* Powerकरोwn CRTC2 */
	पूर्ण अन्यथा अगर (minfo->crtc2.pixघड़ी == minfo->features.pll.ref_freq) अणु
		c2_ctl |=  0x4002;	/* Use reference directly */
	पूर्ण अन्यथा अगर (videomnp == pixelmnp) अणु
		c2_ctl |=  0x0004;	/* Use pixel PLL */
	पूर्ण अन्यथा अणु
		अगर (0 == ((videomnp ^ pixelmnp) & 0xFFFFFF00)) अणु
			/* PIXEL and VIDEO PLL must not use same frequency. We modअगरy N
			   of PIXEL PLL in such हाल because of VIDEO PLL may be source
			   of TVO घड़ीs, and chroma subcarrier is derived from its
			   pixel घड़ीs */
			pixelmnp += 0x000100;
		पूर्ण
		c2_ctl |=  0x0006;	/* Use video PLL */
		hw->DACreg[POS1064_XPWRCTRL] |= 0x02;
		
		outDAC1064(minfo, M1064_XPWRCTRL, hw->DACreg[POS1064_XPWRCTRL]);
		matroxfb_g450_setpll_cond(minfo, videomnp, M_VIDEO_PLL);
	पूर्ण

	hw->DACreg[POS1064_XPIXCLKCTRL] &= ~M1064_XPIXCLKCTRL_PLL_UP;
	अगर (pixelmnp >= 0) अणु
		hw->DACreg[POS1064_XPIXCLKCTRL] |= M1064_XPIXCLKCTRL_PLL_UP;
		
		outDAC1064(minfo, M1064_XPIXCLKCTRL, hw->DACreg[POS1064_XPIXCLKCTRL]);
		matroxfb_g450_setpll_cond(minfo, pixelmnp, M_PIXEL_PLL_C);
	पूर्ण
	अगर (c2_ctl != hw->crtc2.ctl) अणु
		hw->crtc2.ctl = c2_ctl;
		mga_outl(0x3C10, c2_ctl);
	पूर्ण

	pxc = minfo->crtc1.pixघड़ी;
	अगर (pxc == 0 || minfo->outमाला_दो[2].src == MATROXFB_SRC_CRTC2) अणु
		pxc = minfo->crtc2.pixघड़ी;
	पूर्ण
	अगर (minfo->chip == MGA_G550) अणु
		अगर (pxc < 45000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x00;	/* 0-50 */
		पूर्ण अन्यथा अगर (pxc < 55000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x08;	/* 34-62 */
		पूर्ण अन्यथा अगर (pxc < 70000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x10;	/* 42-78 */
		पूर्ण अन्यथा अगर (pxc < 85000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x18;	/* 62-92 */
		पूर्ण अन्यथा अगर (pxc < 100000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x20;	/* 74-108 */
		पूर्ण अन्यथा अगर (pxc < 115000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x28;	/* 94-122 */
		पूर्ण अन्यथा अगर (pxc < 125000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x30;	/* 108-132 */
		पूर्ण अन्यथा अणु
			hw->DACreg[POS1064_XPANMODE] = 0x38;	/* 120-168 */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* G450 */
		अगर (pxc < 45000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x00;	/* 0-54 */
		पूर्ण अन्यथा अगर (pxc < 65000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x08;	/* 38-70 */
		पूर्ण अन्यथा अगर (pxc < 85000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x10;	/* 56-96 */
		पूर्ण अन्यथा अगर (pxc < 105000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x18;	/* 80-114 */
		पूर्ण अन्यथा अगर (pxc < 135000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x20;	/* 102-144 */
		पूर्ण अन्यथा अगर (pxc < 160000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x28;	/* 132-166 */
		पूर्ण अन्यथा अगर (pxc < 175000) अणु
			hw->DACreg[POS1064_XPANMODE] = 0x30;	/* 154-182 */
		पूर्ण अन्यथा अणु
			hw->DACreg[POS1064_XPANMODE] = 0x38;	/* 170-204 */
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम DAC1064_global_init(काष्ठा matrox_fb_info *minfo)
अणु
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	hw->DACreg[POS1064_XMISCCTRL] &= M1064_XMISCCTRL_DAC_WIDTHMASK;
	hw->DACreg[POS1064_XMISCCTRL] |= M1064_XMISCCTRL_LUT_EN;
	hw->DACreg[POS1064_XPIXCLKCTRL] = M1064_XPIXCLKCTRL_PLL_UP | M1064_XPIXCLKCTRL_EN | M1064_XPIXCLKCTRL_SRC_PLL;
#अगर_घोषित CONFIG_FB_MATROX_G
	अगर (minfo->devflags.g450dac) अणु
		hw->DACreg[POS1064_XPWRCTRL] = 0x1F;	/* घातerup everything */
		hw->DACreg[POS1064_XOUTPUTCONN] = 0x00;	/* disable outमाला_दो */
		hw->DACreg[POS1064_XMISCCTRL] |= M1064_XMISCCTRL_DAC_EN;
		चयन (minfo->outमाला_दो[0].src) अणु
			हाल MATROXFB_SRC_CRTC1:
			हाल MATROXFB_SRC_CRTC2:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x01;	/* enable output; CRTC1/2 selection is in CRTC2 ctl */
				अवरोध;
			हाल MATROXFB_SRC_NONE:
				hw->DACreg[POS1064_XMISCCTRL] &= ~M1064_XMISCCTRL_DAC_EN;
				अवरोध;
		पूर्ण
		चयन (minfo->outमाला_दो[1].src) अणु
			हाल MATROXFB_SRC_CRTC1:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x04;
				अवरोध;
			हाल MATROXFB_SRC_CRTC2:
				अगर (minfo->outमाला_दो[1].mode == MATROXFB_OUTPUT_MODE_MONITOR) अणु
					hw->DACreg[POS1064_XOUTPUTCONN] |= 0x08;
				पूर्ण अन्यथा अणु
					hw->DACreg[POS1064_XOUTPUTCONN] |= 0x0C;
				पूर्ण
				अवरोध;
			हाल MATROXFB_SRC_NONE:
				hw->DACreg[POS1064_XPWRCTRL] &= ~0x01;		/* Poweroff DAC2 */
				अवरोध;
		पूर्ण
		चयन (minfo->outमाला_दो[2].src) अणु
			हाल MATROXFB_SRC_CRTC1:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x20;
				अवरोध;
			हाल MATROXFB_SRC_CRTC2:
				hw->DACreg[POS1064_XOUTPUTCONN] |= 0x40;
				अवरोध;
			हाल MATROXFB_SRC_NONE:
#अगर 0
				/* HELP! If we boot without DFP connected to DVI, we can
				   घातeroff TMDS. But अगर we boot with DFP connected,
				   TMDS generated घड़ीs are used instead of ALL pixघड़ीs
				   available... If someone knows which रेजिस्टर
				   handles it, please reveal this secret to me... */			
				hw->DACreg[POS1064_XPWRCTRL] &= ~0x04;		/* Poweroff TMDS */
#पूर्ण_अगर				
				अवरोध;
		पूर्ण
		/* Now set timming related variables... */
		g450_set_plls(minfo);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (minfo->outमाला_दो[1].src == MATROXFB_SRC_CRTC1) अणु
			hw->DACreg[POS1064_XPIXCLKCTRL] = M1064_XPIXCLKCTRL_PLL_UP | M1064_XPIXCLKCTRL_EN | M1064_XPIXCLKCTRL_SRC_EXT;
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_MAFC | G400_XMISCCTRL_VDO_MAFC12;
		पूर्ण अन्यथा अगर (minfo->outमाला_दो[1].src == MATROXFB_SRC_CRTC2) अणु
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_MAFC | G400_XMISCCTRL_VDO_C2_MAFC12;
		पूर्ण अन्यथा अगर (minfo->outमाला_दो[2].src == MATROXFB_SRC_CRTC1)
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_PANELLINK | G400_XMISCCTRL_VDO_MAFC12;
		अन्यथा
			hw->DACreg[POS1064_XMISCCTRL] |= GX00_XMISCCTRL_MFC_DIS;

		अगर (minfo->outमाला_दो[0].src != MATROXFB_SRC_NONE)
			hw->DACreg[POS1064_XMISCCTRL] |= M1064_XMISCCTRL_DAC_EN;
	पूर्ण
पूर्ण

व्योम DAC1064_global_restore(काष्ठा matrox_fb_info *minfo)
अणु
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	outDAC1064(minfo, M1064_XPIXCLKCTRL, hw->DACreg[POS1064_XPIXCLKCTRL]);
	outDAC1064(minfo, M1064_XMISCCTRL, hw->DACreg[POS1064_XMISCCTRL]);
	अगर (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG400) अणु
		outDAC1064(minfo, 0x20, 0x04);
		outDAC1064(minfo, 0x1F, minfo->devflags.dfp_type);
		अगर (minfo->devflags.g450dac) अणु
			outDAC1064(minfo, M1064_XSYNCCTRL, 0xCC);
			outDAC1064(minfo, M1064_XPWRCTRL, hw->DACreg[POS1064_XPWRCTRL]);
			outDAC1064(minfo, M1064_XPANMODE, hw->DACreg[POS1064_XPANMODE]);
			outDAC1064(minfo, M1064_XOUTPUTCONN, hw->DACreg[POS1064_XOUTPUTCONN]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक DAC1064_init_1(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming *m)
अणु
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	स_नकल(hw->DACreg, MGA1064_DAC, माप(MGA1064_DAC_regs));
	चयन (minfo->fbcon.var.bits_per_pixel) अणु
		/* हाल 4: not supported by MGA1064 DAC */
		हाल 8:
			hw->DACreg[POS1064_XMULCTRL] = M1064_XMULCTRL_DEPTH_8BPP | M1064_XMULCTRL_GRAPHICS_PALETIZED;
			अवरोध;
		हाल 16:
			अगर (minfo->fbcon.var.green.length == 5)
				hw->DACreg[POS1064_XMULCTRL] = M1064_XMULCTRL_DEPTH_15BPP_1BPP | M1064_XMULCTRL_GRAPHICS_PALETIZED;
			अन्यथा
				hw->DACreg[POS1064_XMULCTRL] = M1064_XMULCTRL_DEPTH_16BPP | M1064_XMULCTRL_GRAPHICS_PALETIZED;
			अवरोध;
		हाल 24:
			hw->DACreg[POS1064_XMULCTRL] = M1064_XMULCTRL_DEPTH_24BPP | M1064_XMULCTRL_GRAPHICS_PALETIZED;
			अवरोध;
		हाल 32:
			hw->DACreg[POS1064_XMULCTRL] = M1064_XMULCTRL_DEPTH_32BPP | M1064_XMULCTRL_GRAPHICS_PALETIZED;
			अवरोध;
		शेष:
			वापस 1;	/* unsupported depth */
	पूर्ण
	hw->DACreg[POS1064_XVREFCTRL] = minfo->features.DAC1064.xvrefctrl;
	hw->DACreg[POS1064_XGENCTRL] &= ~M1064_XGENCTRL_SYNC_ON_GREEN_MASK;
	hw->DACreg[POS1064_XGENCTRL] |= (m->sync & FB_SYNC_ON_GREEN)?M1064_XGENCTRL_SYNC_ON_GREEN:M1064_XGENCTRL_NO_SYNC_ON_GREEN;
	hw->DACreg[POS1064_XCURADDL] = 0;
	hw->DACreg[POS1064_XCURADDH] = 0;

	DAC1064_global_init(minfo);
	वापस 0;
पूर्ण

अटल पूर्णांक DAC1064_init_2(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming *m)
अणु
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	अगर (minfo->fbcon.var.bits_per_pixel > 16) अणु	/* 256 entries */
		पूर्णांक i;

		क्रम (i = 0; i < 256; i++) अणु
			hw->DACpal[i * 3 + 0] = i;
			hw->DACpal[i * 3 + 1] = i;
			hw->DACpal[i * 3 + 2] = i;
		पूर्ण
	पूर्ण अन्यथा अगर (minfo->fbcon.var.bits_per_pixel > 8) अणु
		अगर (minfo->fbcon.var.green.length == 5) अणु	/* 0..31, 128..159 */
			पूर्णांक i;

			क्रम (i = 0; i < 32; i++) अणु
				/* with p15 == 0 */
				hw->DACpal[i * 3 + 0] = i << 3;
				hw->DACpal[i * 3 + 1] = i << 3;
				hw->DACpal[i * 3 + 2] = i << 3;
				/* with p15 == 1 */
				hw->DACpal[(i + 128) * 3 + 0] = i << 3;
				hw->DACpal[(i + 128) * 3 + 1] = i << 3;
				hw->DACpal[(i + 128) * 3 + 2] = i << 3;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक i;

			क्रम (i = 0; i < 64; i++) अणु		/* 0..63 */
				hw->DACpal[i * 3 + 0] = i << 3;
				hw->DACpal[i * 3 + 1] = i << 2;
				hw->DACpal[i * 3 + 2] = i << 3;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(hw->DACpal, 0, 768);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम DAC1064_restore_1(काष्ठा matrox_fb_info *minfo)
अणु
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	अगर ((inDAC1064(minfo, DAC1064_XSYSPLLM) != hw->DACclk[3]) ||
	    (inDAC1064(minfo, DAC1064_XSYSPLLN) != hw->DACclk[4]) ||
	    (inDAC1064(minfo, DAC1064_XSYSPLLP) != hw->DACclk[5])) अणु
		outDAC1064(minfo, DAC1064_XSYSPLLM, hw->DACclk[3]);
		outDAC1064(minfo, DAC1064_XSYSPLLN, hw->DACclk[4]);
		outDAC1064(minfo, DAC1064_XSYSPLLP, hw->DACclk[5]);
	पूर्ण
	अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < माप(MGA1064_DAC_regs); i++) अणु
			अगर ((i != POS1064_XPIXCLKCTRL) && (i != POS1064_XMISCCTRL))
				outDAC1064(minfo, MGA1064_DAC_regs[i], hw->DACreg[i]);
		पूर्ण
	पूर्ण

	DAC1064_global_restore(minfo);

	CRITEND
पूर्ण;

अटल व्योम DAC1064_restore_2(काष्ठा matrox_fb_info *minfo)
अणु
#अगर_घोषित DEBUG
	अचिन्हित पूर्णांक i;
#पूर्ण_अगर

	DBG(__func__)

#अगर_घोषित DEBUG
	dprपूर्णांकk(KERN_DEBUG "DAC1064regs ");
	क्रम (i = 0; i < माप(MGA1064_DAC_regs); i++) अणु
		dprपूर्णांकk("R%02X=%02X ", MGA1064_DAC_regs[i], minfo->hw.DACreg[i]);
		अगर ((i & 0x7) == 0x7) dprपूर्णांकk(KERN_DEBUG "continuing... ");
	पूर्ण
	dprपूर्णांकk(KERN_DEBUG "DAC1064clk ");
	क्रम (i = 0; i < 6; i++)
		dprपूर्णांकk("C%02X=%02X ", i, minfo->hw.DACclk[i]);
	dprपूर्णांकk("\n");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक m1064_compute(व्योम* out, काष्ठा my_timming* m) अणु
#घोषणा minfo ((काष्ठा matrox_fb_info*)out)
	अणु
		पूर्णांक i;
		पूर्णांक पंचांगout;
		CRITFLAGS

		DAC1064_setpclk(minfo, m->pixघड़ी);

		CRITBEGIN

		क्रम (i = 0; i < 3; i++)
			outDAC1064(minfo, M1064_XPIXPLLCM + i, minfo->hw.DACclk[i]);
		क्रम (पंचांगout = 500000; पंचांगout; पंचांगout--) अणु
			अगर (inDAC1064(minfo, M1064_XPIXPLLSTAT) & 0x40)
				अवरोध;
			udelay(10);
		पूर्ण

		CRITEND

		अगर (!पंचांगout)
			prपूर्णांकk(KERN_ERR "matroxfb: Pixel PLL not locked after 5 secs\n");
	पूर्ण
#अघोषित minfo
	वापस 0;
पूर्ण

अटल काष्ठा matrox_altout m1064 = अणु
	.name	 = "Primary output",
	.compute = m1064_compute,
पूर्ण;

#अगर_घोषित CONFIG_FB_MATROX_G
अटल पूर्णांक g450_compute(व्योम* out, काष्ठा my_timming* m) अणु
#घोषणा minfo ((काष्ठा matrox_fb_info*)out)
	अगर (m->mnp < 0) अणु
		m->mnp = matroxfb_g450_setclk(minfo, m->pixघड़ी, (m->crtc == MATROXFB_SRC_CRTC1) ? M_PIXEL_PLL_C : M_VIDEO_PLL);
		अगर (m->mnp >= 0) अणु
			m->pixघड़ी = g450_mnp2f(minfo, m->mnp);
		पूर्ण
	पूर्ण
#अघोषित minfo
	वापस 0;
पूर्ण

अटल काष्ठा matrox_altout g450out = अणु
	.name	 = "Primary output",
	.compute = g450_compute,
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* NEED_DAC1064 */

#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
अटल पूर्णांक MGA1064_init(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming *m)
अणु
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	अगर (DAC1064_init_1(minfo, m)) वापस 1;
	अगर (matroxfb_vgaHWinit(minfo, m)) वापस 1;

	hw->MiscOutReg = 0xCB;
	अगर (m->sync & FB_SYNC_HOR_HIGH_ACT)
		hw->MiscOutReg &= ~0x40;
	अगर (m->sync & FB_SYNC_VERT_HIGH_ACT)
		hw->MiscOutReg &= ~0x80;
	अगर (m->sync & FB_SYNC_COMP_HIGH_ACT) /* should be only FB_SYNC_COMP */
		hw->CRTCEXT[3] |= 0x40;

	अगर (DAC1064_init_2(minfo, m)) वापस 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_G
अटल पूर्णांक MGAG100_init(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming *m)
अणु
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	अगर (DAC1064_init_1(minfo, m)) वापस 1;
	hw->MXoptionReg &= ~0x2000;
	अगर (matroxfb_vgaHWinit(minfo, m)) वापस 1;

	hw->MiscOutReg = 0xEF;
	अगर (m->sync & FB_SYNC_HOR_HIGH_ACT)
		hw->MiscOutReg &= ~0x40;
	अगर (m->sync & FB_SYNC_VERT_HIGH_ACT)
		hw->MiscOutReg &= ~0x80;
	अगर (m->sync & FB_SYNC_COMP_HIGH_ACT) /* should be only FB_SYNC_COMP */
		hw->CRTCEXT[3] |= 0x40;

	अगर (DAC1064_init_2(minfo, m)) वापस 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* G */

#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
अटल व्योम MGA1064_ramdac_init(काष्ठा matrox_fb_info *minfo)
अणु

	DBG(__func__)

	/* minfo->features.DAC1064.vco_freq_min = 120000; */
	minfo->features.pll.vco_freq_min = 62000;
	minfo->features.pll.ref_freq	 = 14318;
	minfo->features.pll.feed_भाग_min = 100;
	minfo->features.pll.feed_भाग_max = 127;
	minfo->features.pll.in_भाग_min	 = 1;
	minfo->features.pll.in_भाग_max	 = 31;
	minfo->features.pll.post_shअगरt_max = 3;
	minfo->features.DAC1064.xvrefctrl = DAC1064_XVREFCTRL_EXTERNAL;
	/* maybe cmdline MCLK= ?, करोc says gclk=44MHz, mclk=66MHz... it was 55/83 with old values */
	DAC1064_seपंचांगclk(minfo, DAC1064_OPT_MDIV2 | DAC1064_OPT_GDIV3 | DAC1064_OPT_SCLK_PLL, 133333);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_G
/* BIOS environ */
अटल पूर्णांक x7AF4 = 0x10;	/* flags, maybe 0x10 = SDRAM, 0x00 = SGRAM??? */
				/* G100 wants 0x10, G200 SGRAM करोes not care... */
#अगर 0
अटल पूर्णांक def50 = 0;	/* reg50, & 0x0F, & 0x3000 (only 0x0000, 0x1000, 0x2000 (0x3000 disallowed and treated as 0) */
#पूर्ण_अगर

अटल व्योम MGAG100_progPixClock(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक flags,
				 पूर्णांक m, पूर्णांक n, पूर्णांक p)
अणु
	पूर्णांक reg;
	पूर्णांक selClk;
	पूर्णांक clk;

	DBG(__func__)

	outDAC1064(minfo, M1064_XPIXCLKCTRL, inDAC1064(minfo, M1064_XPIXCLKCTRL) | M1064_XPIXCLKCTRL_DIS |
		   M1064_XPIXCLKCTRL_PLL_UP);
	चयन (flags & 3) अणु
		हाल 0:		reg = M1064_XPIXPLLAM; अवरोध;
		हाल 1:		reg = M1064_XPIXPLLBM; अवरोध;
		शेष:	reg = M1064_XPIXPLLCM; अवरोध;
	पूर्ण
	outDAC1064(minfo, reg++, m);
	outDAC1064(minfo, reg++, n);
	outDAC1064(minfo, reg, p);
	selClk = mga_inb(M_MISC_REG_READ) & ~0xC;
	/* there should be flags & 0x03 & हाल 0/1/अन्यथा */
	/* and we should first select source and after that we should रुको क्रम PLL */
	/* and we are रुकोing क्रम PLL with oscilator disabled... Is it right? */
	चयन (flags & 0x03) अणु
		हाल 0x00:	अवरोध;
		हाल 0x01:	selClk |= 4; अवरोध;
		शेष:	selClk |= 0x0C; अवरोध;
	पूर्ण
	mga_outb(M_MISC_REG, selClk);
	क्रम (clk = 500000; clk; clk--) अणु
		अगर (inDAC1064(minfo, M1064_XPIXPLLSTAT) & 0x40)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (!clk)
		prपूर्णांकk(KERN_ERR "matroxfb: Pixel PLL%c not locked after usual time\n", (reg-M1064_XPIXPLLAM-2)/4 + 'A');
	selClk = inDAC1064(minfo, M1064_XPIXCLKCTRL) & ~M1064_XPIXCLKCTRL_SRC_MASK;
	चयन (flags & 0x0C) अणु
		हाल 0x00:	selClk |= M1064_XPIXCLKCTRL_SRC_PCI; अवरोध;
		हाल 0x04:	selClk |= M1064_XPIXCLKCTRL_SRC_PLL; अवरोध;
		शेष:	selClk |= M1064_XPIXCLKCTRL_SRC_EXT; अवरोध;
	पूर्ण
	outDAC1064(minfo, M1064_XPIXCLKCTRL, selClk);
	outDAC1064(minfo, M1064_XPIXCLKCTRL, inDAC1064(minfo, M1064_XPIXCLKCTRL) & ~M1064_XPIXCLKCTRL_DIS);
पूर्ण

अटल व्योम MGAG100_setPixClock(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक flags,
				पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक m, n, p;

	DBG(__func__)

	DAC1064_calcघड़ी(minfo, freq, minfo->max_pixel_घड़ी, &m, &n, &p);
	MGAG100_progPixClock(minfo, flags, m, n, p);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
अटल पूर्णांक MGA1064_preinit(काष्ठा matrox_fb_info *minfo)
अणु
	अटल स्थिर पूर्णांक vxres_mystique[] = अणु 512,        640, 768,  800,  832,  960,
					     1024, 1152, 1280,      1600, 1664, 1920,
					     2048,    0पूर्ण;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	/* minfo->capable.cfb4 = 0; ... preinitialized by 0 */
	minfo->capable.text = 1;
	minfo->capable.vxres = vxres_mystique;

	minfo->outमाला_दो[0].output = &m1064;
	minfo->outमाला_दो[0].src = minfo->outमाला_दो[0].शेष_src;
	minfo->outमाला_दो[0].data = minfo;
	minfo->outमाला_दो[0].mode = MATROXFB_OUTPUT_MODE_MONITOR;

	अगर (minfo->devflags.noinit)
		वापस 0;	/* करो not modअगरy settings */
	hw->MXoptionReg &= 0xC0000100;
	hw->MXoptionReg |= 0x00094E20;
	अगर (minfo->devflags.novga)
		hw->MXoptionReg &= ~0x00000100;
	अगर (minfo->devflags.nobios)
		hw->MXoptionReg &= ~0x40000000;
	अगर (minfo->devflags.nopciretry)
		hw->MXoptionReg |=  0x20000000;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);
	mga_setr(M_SEQ_INDEX, 0x01, 0x20);
	mga_outl(M_CTLWTST, 0x00000000);
	udelay(200);
	mga_outl(M_MACCESS, 0x00008000);
	udelay(100);
	mga_outl(M_MACCESS, 0x0000C000);
	वापस 0;
पूर्ण

अटल व्योम MGA1064_reset(काष्ठा matrox_fb_info *minfo)
अणु

	DBG(__func__);

	MGA1064_ramdac_init(minfo);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_G
अटल व्योम g450_mclk_init(काष्ठा matrox_fb_info *minfo)
अणु
	/* चयन all घड़ीs to PCI source */
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg | 4);
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION3_REG, minfo->values.reg.opt3 & ~0x00300C03);
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg);

	अगर (((minfo->values.reg.opt3 & 0x000003) == 0x000003) ||
	    ((minfo->values.reg.opt3 & 0x000C00) == 0x000C00) ||
	    ((minfo->values.reg.opt3 & 0x300000) == 0x300000)) अणु
		matroxfb_g450_setclk(minfo, minfo->values.pll.video, M_VIDEO_PLL);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags;
		अचिन्हित पूर्णांक pwr;
		
		matroxfb_DAC_lock_irqsave(flags);
		pwr = inDAC1064(minfo, M1064_XPWRCTRL) & ~0x02;
		outDAC1064(minfo, M1064_XPWRCTRL, pwr);
		matroxfb_DAC_unlock_irqrestore(flags);
	पूर्ण
	matroxfb_g450_setclk(minfo, minfo->values.pll.प्रणाली, M_SYSTEM_PLL);
	
	/* चयन घड़ीs to their real PLL source(s) */
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg | 4);
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION3_REG, minfo->values.reg.opt3);
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg);

पूर्ण

अटल व्योम g450_memory_init(काष्ठा matrox_fb_info *minfo)
अणु
	/* disable memory refresh */
	minfo->hw.MXoptionReg &= ~0x001F8000;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg);
	
	/* set memory पूर्णांकerface parameters */
	minfo->hw.MXoptionReg &= ~0x00207E00;
	minfo->hw.MXoptionReg |= 0x00207E00 & minfo->values.reg.opt;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg);
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION2_REG, minfo->values.reg.opt2);
	
	mga_outl(M_CTLWTST, minfo->values.reg.mctlwtst);
	
	/* first set up memory पूर्णांकerface with disabled memory पूर्णांकerface घड़ीs */
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_MEMMISC_REG, minfo->values.reg.memmisc & ~0x80000000U);
	mga_outl(M_MEMRDBK, minfo->values.reg.memrdbk);
	mga_outl(M_MACCESS, minfo->values.reg.maccess);
	/* start memory घड़ीs */
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_MEMMISC_REG, minfo->values.reg.memmisc | 0x80000000U);

	udelay(200);
	
	अगर (minfo->values.memory.ddr && (!minfo->values.memory.emrswen || !minfo->values.memory.dll)) अणु
		mga_outl(M_MEMRDBK, minfo->values.reg.memrdbk & ~0x1000);
	पूर्ण
	mga_outl(M_MACCESS, minfo->values.reg.maccess | 0x8000);
	
	udelay(200);
	
	minfo->hw.MXoptionReg |= 0x001F8000 & minfo->values.reg.opt;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg);
	
	/* value is written to memory chips only अगर old != new */
	mga_outl(M_PLNWT, 0);
	mga_outl(M_PLNWT, ~0);
	
	अगर (minfo->values.reg.mctlwtst != minfo->values.reg.mctlwtst_core) अणु
		mga_outl(M_CTLWTST, minfo->values.reg.mctlwtst_core);
	पूर्ण
	
पूर्ण

अटल व्योम g450_preinit(काष्ठा matrox_fb_info *minfo)
अणु
	u_पूर्णांक32_t c2ctl;
	u_पूर्णांक8_t curctl;
	u_पूर्णांक8_t c1ctl;
	
	/* minfo->hw.MXoptionReg = minfo->values.reg.opt; */
	minfo->hw.MXoptionReg &= 0xC0000100;
	minfo->hw.MXoptionReg |= 0x00000020;
	अगर (minfo->devflags.novga)
		minfo->hw.MXoptionReg &= ~0x00000100;
	अगर (minfo->devflags.nobios)
		minfo->hw.MXoptionReg &= ~0x40000000;
	अगर (minfo->devflags.nopciretry)
		minfo->hw.MXoptionReg |=  0x20000000;
	minfo->hw.MXoptionReg |= minfo->values.reg.opt & 0x03400040;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, minfo->hw.MXoptionReg);

	/* Init प्रणाली घड़ीs */
		
	/* stop crtc2 */
	c2ctl = mga_inl(M_C2CTL);
	mga_outl(M_C2CTL, c2ctl & ~1);
	/* stop cursor */
	curctl = inDAC1064(minfo, M1064_XCURCTRL);
	outDAC1064(minfo, M1064_XCURCTRL, 0);
	/* stop crtc1 */
	c1ctl = mga_पढ़ोr(M_SEQ_INDEX, 1);
	mga_setr(M_SEQ_INDEX, 1, c1ctl | 0x20);

	g450_mclk_init(minfo);
	g450_memory_init(minfo);
	
	/* set legacy VGA घड़ी sources क्रम DOSEmu or VMware... */
	matroxfb_g450_setclk(minfo, 25175, M_PIXEL_PLL_A);
	matroxfb_g450_setclk(minfo, 28322, M_PIXEL_PLL_B);

	/* restore crtc1 */
	mga_setr(M_SEQ_INDEX, 1, c1ctl);
	
	/* restore cursor */
	outDAC1064(minfo, M1064_XCURCTRL, curctl);

	/* restore crtc2 */
	mga_outl(M_C2CTL, c2ctl);
	
	वापस;
पूर्ण

अटल पूर्णांक MGAG100_preinit(काष्ठा matrox_fb_info *minfo)
अणु
	अटल स्थिर पूर्णांक vxres_g100[] = अणु  512,        640, 768,  800,  832,  960,
                                          1024, 1152, 1280,      1600, 1664, 1920,
                                          2048, 0पूर्ण;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

        u_पूर्णांक32_t reg50;
#अगर 0
	u_पूर्णांक32_t q;
#पूर्ण_अगर

	DBG(__func__)

	/* there are some instabilities अगर in_भाग > 19 && vco < 61000 */
	अगर (minfo->devflags.g450dac) अणु
		minfo->features.pll.vco_freq_min = 130000;	/* my sample: >118 */
	पूर्ण अन्यथा अणु
		minfo->features.pll.vco_freq_min = 62000;
	पूर्ण
	अगर (!minfo->features.pll.ref_freq) अणु
		minfo->features.pll.ref_freq	 = 27000;
	पूर्ण
	minfo->features.pll.feed_भाग_min = 7;
	minfo->features.pll.feed_भाग_max = 127;
	minfo->features.pll.in_भाग_min	 = 1;
	minfo->features.pll.in_भाग_max	 = 31;
	minfo->features.pll.post_shअगरt_max = 3;
	minfo->features.DAC1064.xvrefctrl = DAC1064_XVREFCTRL_G100_DEFAULT;
	/* minfo->capable.cfb4 = 0; ... preinitialized by 0 */
	minfo->capable.text = 1;
	minfo->capable.vxres = vxres_g100;
	minfo->capable.plnwt = minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG100
			? minfo->devflags.sgram : 1;

	अगर (minfo->devflags.g450dac) अणु
		minfo->outमाला_दो[0].output = &g450out;
	पूर्ण अन्यथा अणु
		minfo->outमाला_दो[0].output = &m1064;
	पूर्ण
	minfo->outमाला_दो[0].src = minfo->outमाला_दो[0].शेष_src;
	minfo->outमाला_दो[0].data = minfo;
	minfo->outमाला_दो[0].mode = MATROXFB_OUTPUT_MODE_MONITOR;

	अगर (minfo->devflags.g450dac) अणु
		/* we must करो this always, BIOS करोes not करो it क्रम us
		   and accelerator dies without it */
		mga_outl(0x1C0C, 0);
	पूर्ण
	अगर (minfo->devflags.noinit)
		वापस 0;
	अगर (minfo->devflags.g450dac) अणु
		g450_preinit(minfo);
		वापस 0;
	पूर्ण
	hw->MXoptionReg &= 0xC0000100;
	hw->MXoptionReg |= 0x00000020;
	अगर (minfo->devflags.novga)
		hw->MXoptionReg &= ~0x00000100;
	अगर (minfo->devflags.nobios)
		hw->MXoptionReg &= ~0x40000000;
	अगर (minfo->devflags.nopciretry)
		hw->MXoptionReg |=  0x20000000;
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);
	DAC1064_seपंचांगclk(minfo, DAC1064_OPT_MDIV2 | DAC1064_OPT_GDIV3 | DAC1064_OPT_SCLK_PCI, 133333);

	अगर (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG100) अणु
		pci_पढ़ो_config_dword(minfo->pcidev, PCI_OPTION2_REG, &reg50);
		reg50 &= ~0x3000;
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION2_REG, reg50);

		hw->MXoptionReg |= 0x1080;
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);
		mga_outl(M_CTLWTST, minfo->values.reg.mctlwtst);
		udelay(100);
		mga_outb(0x1C05, 0x00);
		mga_outb(0x1C05, 0x80);
		udelay(100);
		mga_outb(0x1C05, 0x40);
		mga_outb(0x1C05, 0xC0);
		udelay(100);
		reg50 &= ~0xFF;
		reg50 |=  0x07;
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION2_REG, reg50);
		/* it should help with G100 */
		mga_outb(M_GRAPHICS_INDEX, 6);
		mga_outb(M_GRAPHICS_DATA, (mga_inb(M_GRAPHICS_DATA) & 3) | 4);
		mga_setr(M_EXTVGA_INDEX, 0x03, 0x81);
		mga_setr(M_EXTVGA_INDEX, 0x04, 0x00);
		mga_ग_लिखोb(minfo->video.vbase, 0x0000, 0xAA);
		mga_ग_लिखोb(minfo->video.vbase, 0x0800, 0x55);
		mga_ग_लिखोb(minfo->video.vbase, 0x4000, 0x55);
#अगर 0
		अगर (mga_पढ़ोb(minfo->video.vbase, 0x0000) != 0xAA) अणु
			hw->MXoptionReg &= ~0x1000;
		पूर्ण
#पूर्ण_अगर
		hw->MXoptionReg |= 0x00078020;
	पूर्ण अन्यथा अगर (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG200) अणु
		pci_पढ़ो_config_dword(minfo->pcidev, PCI_OPTION2_REG, &reg50);
		reg50 &= ~0x3000;
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION2_REG, reg50);

		अगर (minfo->devflags.memtype == -1)
			hw->MXoptionReg |= minfo->values.reg.opt & 0x1C00;
		अन्यथा
			hw->MXoptionReg |= (minfo->devflags.memtype & 7) << 10;
		अगर (minfo->devflags.sgram)
			hw->MXoptionReg |= 0x4000;
		mga_outl(M_CTLWTST, minfo->values.reg.mctlwtst);
		mga_outl(M_MEMRDBK, minfo->values.reg.memrdbk);
		udelay(200);
		mga_outl(M_MACCESS, 0x00000000);
		mga_outl(M_MACCESS, 0x00008000);
		udelay(100);
		mga_outw(M_MEMRDBK, minfo->values.reg.memrdbk);
		hw->MXoptionReg |= 0x00078020;
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(minfo->pcidev, PCI_OPTION2_REG, &reg50);
		reg50 &= ~0x00000100;
		reg50 |=  0x00000000;
		pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION2_REG, reg50);

		अगर (minfo->devflags.memtype == -1)
			hw->MXoptionReg |= minfo->values.reg.opt & 0x1C00;
		अन्यथा
			hw->MXoptionReg |= (minfo->devflags.memtype & 7) << 10;
		अगर (minfo->devflags.sgram)
			hw->MXoptionReg |= 0x4000;
		mga_outl(M_CTLWTST, minfo->values.reg.mctlwtst);
		mga_outl(M_MEMRDBK, minfo->values.reg.memrdbk);
		udelay(200);
		mga_outl(M_MACCESS, 0x00000000);
		mga_outl(M_MACCESS, 0x00008000);
		udelay(100);
		mga_outl(M_MEMRDBK, minfo->values.reg.memrdbk);
		hw->MXoptionReg |= 0x00040020;
	पूर्ण
	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);
	वापस 0;
पूर्ण

अटल व्योम MGAG100_reset(काष्ठा matrox_fb_info *minfo)
अणु
	u_पूर्णांक8_t b;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	DBG(__func__)

	अणु
#अगर_घोषित G100_BROKEN_IBM_82351
		u_पूर्णांक32_t d;

		find 1014/22 (IBM/82351); /* अगर found and bridging Matrox, करो some strange stuff */
		pci_पढ़ो_config_byte(ibm, PCI_SECONDARY_BUS, &b);
		अगर (b == minfo->pcidev->bus->number) अणु
			pci_ग_लिखो_config_byte(ibm, PCI_COMMAND+1, 0);	/* disable back-to-back & SERR */
			pci_ग_लिखो_config_byte(ibm, 0x41, 0xF4);		/* ??? */
			pci_ग_लिखो_config_byte(ibm, PCI_IO_BASE, 0xF0);	/* ??? */
			pci_ग_लिखो_config_byte(ibm, PCI_IO_LIMIT, 0x00);	/* ??? */
		पूर्ण
#पूर्ण_अगर
		अगर (!minfo->devflags.noinit) अणु
			अगर (x7AF4 & 8) अणु
				hw->MXoptionReg |= 0x40;	/* FIXME... */
				pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);
			पूर्ण
			mga_setr(M_EXTVGA_INDEX, 0x06, 0x00);
		पूर्ण
	पूर्ण
	अगर (minfo->devflags.g450dac) अणु
		/* either leave MCLK as is... or they were set in preinit */
		hw->DACclk[3] = inDAC1064(minfo, DAC1064_XSYSPLLM);
		hw->DACclk[4] = inDAC1064(minfo, DAC1064_XSYSPLLN);
		hw->DACclk[5] = inDAC1064(minfo, DAC1064_XSYSPLLP);
	पूर्ण अन्यथा अणु
		DAC1064_seपंचांगclk(minfo, DAC1064_OPT_RESERVED | DAC1064_OPT_MDIV2 | DAC1064_OPT_GDIV1 | DAC1064_OPT_SCLK_PLL, 133333);
	पूर्ण
	अगर (minfo->devflags.accelerator == FB_ACCEL_MATROX_MGAG400) अणु
		अगर (minfo->devflags.dfp_type == -1) अणु
			minfo->devflags.dfp_type = inDAC1064(minfo, 0x1F);
		पूर्ण
	पूर्ण
	अगर (minfo->devflags.noinit)
		वापस;
	अगर (minfo->devflags.g450dac) अणु
	पूर्ण अन्यथा अणु
		MGAG100_setPixClock(minfo, 4, 25175);
		MGAG100_setPixClock(minfo, 5, 28322);
		अगर (x7AF4 & 0x10) अणु
			b = inDAC1064(minfo, M1064_XGENIODATA) & ~1;
			outDAC1064(minfo, M1064_XGENIODATA, b);
			b = inDAC1064(minfo, M1064_XGENIOCTRL) | 1;
			outDAC1064(minfo, M1064_XGENIOCTRL, b);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
अटल व्योम MGA1064_restore(काष्ठा matrox_fb_info *minfo)
अणु
	पूर्णांक i;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);
	mga_outb(M_IEN, 0x00);
	mga_outb(M_CACHEFLUSH, 0x00);

	CRITEND

	DAC1064_restore_1(minfo);
	matroxfb_vgaHWrestore(minfo);
	minfo->crtc1.panpos = -1;
	क्रम (i = 0; i < 6; i++)
		mga_setr(M_EXTVGA_INDEX, i, hw->CRTCEXT[i]);
	DAC1064_restore_2(minfo);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_G
अटल व्योम MGAG100_restore(काष्ठा matrox_fb_info *minfo)
अणु
	पूर्णांक i;
	काष्ठा matrox_hw_state *hw = &minfo->hw;

	CRITFLAGS

	DBG(__func__)

	CRITBEGIN

	pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, hw->MXoptionReg);
	CRITEND

	DAC1064_restore_1(minfo);
	matroxfb_vgaHWrestore(minfo);
	अगर (minfo->devflags.support32MB)
		mga_setr(M_EXTVGA_INDEX, 8, hw->CRTCEXT[8]);
	minfo->crtc1.panpos = -1;
	क्रम (i = 0; i < 6; i++)
		mga_setr(M_EXTVGA_INDEX, i, hw->CRTCEXT[i]);
	DAC1064_restore_2(minfo);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_MYSTIQUE
काष्ठा matrox_चयन matrox_mystique = अणु
	.preinit	= MGA1064_preinit,
	.reset		= MGA1064_reset,
	.init		= MGA1064_init,
	.restore	= MGA1064_restore,
पूर्ण;
EXPORT_SYMBOL(matrox_mystique);
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_MATROX_G
काष्ठा matrox_चयन matrox_G100 = अणु
	.preinit	= MGAG100_preinit,
	.reset		= MGAG100_reset,
	.init		= MGAG100_init,
	.restore	= MGAG100_restore,
पूर्ण;
EXPORT_SYMBOL(matrox_G100);
#पूर्ण_अगर

#अगर_घोषित NEED_DAC1064
EXPORT_SYMBOL(DAC1064_global_init);
EXPORT_SYMBOL(DAC1064_global_restore);
#पूर्ण_अगर
MODULE_LICENSE("GPL");
