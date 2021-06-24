<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 ADEC audio functions
 *
 *  Derived from cx25840-core.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-cards.h"

पूर्णांक cx18_av_ग_लिखो(काष्ठा cx18 *cx, u16 addr, u8 value)
अणु
	u32 reg = 0xc40000 + (addr & ~3);
	u32 mask = 0xff;
	पूर्णांक shअगरt = (addr & 3) * 8;
	u32 x = cx18_पढ़ो_reg(cx, reg);

	x = (x & ~(mask << shअगरt)) | ((u32)value << shअगरt);
	cx18_ग_लिखो_reg(cx, x, reg);
	वापस 0;
पूर्ण

पूर्णांक cx18_av_ग_लिखो_expect(काष्ठा cx18 *cx, u16 addr, u8 value, u8 eval, u8 mask)
अणु
	u32 reg = 0xc40000 + (addr & ~3);
	पूर्णांक shअगरt = (addr & 3) * 8;
	u32 x = cx18_पढ़ो_reg(cx, reg);

	x = (x & ~((u32)0xff << shअगरt)) | ((u32)value << shअगरt);
	cx18_ग_लिखो_reg_expect(cx, x, reg,
				((u32)eval << shअगरt), ((u32)mask << shअगरt));
	वापस 0;
पूर्ण

पूर्णांक cx18_av_ग_लिखो4(काष्ठा cx18 *cx, u16 addr, u32 value)
अणु
	cx18_ग_लिखो_reg(cx, value, 0xc40000 + addr);
	वापस 0;
पूर्ण

पूर्णांक
cx18_av_ग_लिखो4_expect(काष्ठा cx18 *cx, u16 addr, u32 value, u32 eval, u32 mask)
अणु
	cx18_ग_लिखो_reg_expect(cx, value, 0xc40000 + addr, eval, mask);
	वापस 0;
पूर्ण

पूर्णांक cx18_av_ग_लिखो4_noretry(काष्ठा cx18 *cx, u16 addr, u32 value)
अणु
	cx18_ग_लिखो_reg_noretry(cx, value, 0xc40000 + addr);
	वापस 0;
पूर्ण

u8 cx18_av_पढ़ो(काष्ठा cx18 *cx, u16 addr)
अणु
	u32 x = cx18_पढ़ो_reg(cx, 0xc40000 + (addr & ~3));
	पूर्णांक shअगरt = (addr & 3) * 8;

	वापस (x >> shअगरt) & 0xff;
पूर्ण

u32 cx18_av_पढ़ो4(काष्ठा cx18 *cx, u16 addr)
अणु
	वापस cx18_पढ़ो_reg(cx, 0xc40000 + addr);
पूर्ण

पूर्णांक cx18_av_and_or(काष्ठा cx18 *cx, u16 addr, अचिन्हित and_mask,
		   u8 or_value)
अणु
	वापस cx18_av_ग_लिखो(cx, addr,
			     (cx18_av_पढ़ो(cx, addr) & and_mask) |
			     or_value);
पूर्ण

पूर्णांक cx18_av_and_or4(काष्ठा cx18 *cx, u16 addr, u32 and_mask,
		   u32 or_value)
अणु
	वापस cx18_av_ग_लिखो4(cx, addr,
			     (cx18_av_पढ़ो4(cx, addr) & and_mask) |
			     or_value);
पूर्ण

अटल व्योम cx18_av_init(काष्ठा cx18 *cx)
अणु
	/*
	 * The crystal freq used in calculations in this driver will be
	 * 28.636360 MHz.
	 * Aim to run the PLLs' VCOs near 400 MHz to minimize errors.
	 */

	/*
	 * VDCLK  Integer = 0x0f, Post Divider = 0x04
	 * AIMCLK Integer = 0x0e, Post Divider = 0x16
	 */
	cx18_av_ग_लिखो4(cx, CXADEC_PLL_CTRL1, 0x160e040f);

	/* VDCLK Fraction = 0x2be2fe */
	/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz beक्रमe post भागide */
	cx18_av_ग_लिखो4(cx, CXADEC_VID_PLL_FRAC, 0x002be2fe);

	/* AIMCLK Fraction = 0x05227ad */
	/* xtal * 0xe.2913d68/0x16 = 48000 * 384: 406 MHz pre post-भाग*/
	cx18_av_ग_लिखो4(cx, CXADEC_AUX_PLL_FRAC, 0x005227ad);

	/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x16 */
	cx18_av_ग_लिखो(cx, CXADEC_I2S_MCLK, 0x56);
पूर्ण

अटल व्योम cx18_av_initialize(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	पूर्णांक शेष_volume;
	u32 v;

	cx18_av_loadfw(cx);
	/* Stop 8051 code execution */
	cx18_av_ग_लिखो4_expect(cx, CXADEC_DL_CTL, 0x03000000,
						 0x03000000, 0x13000000);

	/* initialize the PLL by toggling sleep bit */
	v = cx18_av_पढ़ो4(cx, CXADEC_HOST_REG1);
	/* enable sleep mode - रेजिस्टर appears to be पढ़ो only... */
	cx18_av_ग_लिखो4_expect(cx, CXADEC_HOST_REG1, v | 1, v, 0xfffe);
	/* disable sleep mode */
	cx18_av_ग_लिखो4_expect(cx, CXADEC_HOST_REG1, v & 0xfffe,
						    v & 0xfffe, 0xffff);

	/* initialize DLLs */
	v = cx18_av_पढ़ो4(cx, CXADEC_DLL1_DIAG_CTRL) & 0xE1FFFEFF;
	/* disable FLD */
	cx18_av_ग_लिखो4(cx, CXADEC_DLL1_DIAG_CTRL, v);
	/* enable FLD */
	cx18_av_ग_लिखो4(cx, CXADEC_DLL1_DIAG_CTRL, v | 0x10000100);

	v = cx18_av_पढ़ो4(cx, CXADEC_DLL2_DIAG_CTRL) & 0xE1FFFEFF;
	/* disable FLD */
	cx18_av_ग_लिखो4(cx, CXADEC_DLL2_DIAG_CTRL, v);
	/* enable FLD */
	cx18_av_ग_लिखो4(cx, CXADEC_DLL2_DIAG_CTRL, v | 0x06000100);

	/* set analog bias currents. Set Vreg to 1.20V. */
	cx18_av_ग_लिखो4(cx, CXADEC_AFE_DIAG_CTRL1, 0x000A1802);

	v = cx18_av_पढ़ो4(cx, CXADEC_AFE_DIAG_CTRL3) | 1;
	/* enable TUNE_FIL_RST */
	cx18_av_ग_लिखो4_expect(cx, CXADEC_AFE_DIAG_CTRL3, v, v, 0x03009F0F);
	/* disable TUNE_FIL_RST */
	cx18_av_ग_लिखो4_expect(cx, CXADEC_AFE_DIAG_CTRL3,
			      v & 0xFFFFFFFE, v & 0xFFFFFFFE, 0x03009F0F);

	/* enable 656 output */
	cx18_av_and_or4(cx, CXADEC_PIN_CTRL1, ~0, 0x040C00);

	/* video output drive strength */
	cx18_av_and_or4(cx, CXADEC_PIN_CTRL2, ~0, 0x2);

	/* reset video */
	cx18_av_ग_लिखो4(cx, CXADEC_SOFT_RST_CTRL, 0x8000);
	cx18_av_ग_लिखो4(cx, CXADEC_SOFT_RST_CTRL, 0);

	/*
	 * Disable Video Auto-config of the Analog Front End and Video PLL.
	 *
	 * Since we only use BT.656 pixel mode, which works क्रम both 525 and 625
	 * line प्रणालीs, it's just easier क्रम us to set रेजिस्टरs
	 * 0x102 (CXADEC_CHIP_CTRL), 0x104-0x106 (CXADEC_AFE_CTRL),
	 * 0x108-0x109 (CXADEC_PLL_CTRL1), and 0x10c-0x10f (CXADEC_VID_PLL_FRAC)
	 * ourselves, than to run around cleaning up after the स्वतः-config.
	 *
	 * (Note: my CX23418 chip करोesn't seem to let the ACFG_DIS bit
	 * get set to 1, but OTOH, it करोesn't seem to करो AFE and VID PLL
	 * स्वतःconfig either.)
	 *
	 * As a शेष, also turn off Dual mode क्रम ADC2 and set ADC2 to CH3.
	 */
	cx18_av_and_or4(cx, CXADEC_CHIP_CTRL, 0xFFFBFFFF, 0x00120000);

	/* Setup the Video and and Aux/Audio PLLs */
	cx18_av_init(cx);

	/* set video to स्वतः-detect */
	/* Clear bits 11-12 to enable slow locking mode.  Set स्वतःdetect mode */
	/* set the comb notch = 1 */
	cx18_av_and_or4(cx, CXADEC_MODE_CTRL, 0xFFF7E7F0, 0x02040800);

	/* Enable wtw_en in CRUSH_CTRL (Set bit 22) */
	/* Enable maj_sel in CRUSH_CTRL (Set bit 20) */
	cx18_av_and_or4(cx, CXADEC_CRUSH_CTRL, ~0, 0x00500000);

	/* Set VGA_TRACK_RANGE to 0x20 */
	cx18_av_and_or4(cx, CXADEC_DFE_CTRL2, 0xFFFF00FF, 0x00002000);

	/*
	 * Initial VBI setup
	 * VIP-1.1, 10 bit mode, enable Raw, disable sliced,
	 * करोn't clamp raw samples when codes are in use, 1 byte user D-words,
	 * IDID0 has line #, RP code V bit transition on VBLANK, data during
	 * blanking पूर्णांकervals
	 */
	cx18_av_ग_लिखो4(cx, CXADEC_OUT_CTRL1, 0x4013252e);

	/* Set the video input.
	   The setting in MODE_CTRL माला_लो lost when we करो the above setup */
	/* EncSetSignalStd(dwDevNum, pEnc->dwSigStd); */
	/* EncSetVideoInput(dwDevNum, pEnc->VidIndSelection); */

	/*
	 * Analog Front End (AFE)
	 * Default to luma on ch1/ADC1, chroma on ch2/ADC2, SIF on ch3/ADC2
	 *  bypass_ch[1-3]     use filter
	 *  droop_comp_ch[1-3] disable
	 *  clamp_en_ch[1-3]   disable
	 *  aud_in_sel         ADC2
	 *  luma_in_sel        ADC1
	 *  chroma_in_sel      ADC2
	 *  clamp_sel_ch[2-3]  midcode
	 *  clamp_sel_ch1      video decoder
	 *  vga_sel_ch3        audio decoder
	 *  vga_sel_ch[1-2]    video decoder
	 *  half_bw_ch[1-3]    disable
	 *  +12db_ch[1-3]      disable
	 */
	cx18_av_and_or4(cx, CXADEC_AFE_CTRL, 0xFF000000, 0x00005D00);

/*	अगर(dwEnable && dw3DCombAvailable) अणु */
/*		CxDevWrReg(CXADEC_SRC_COMB_CFG, 0x7728021F); */
/*    पूर्ण अन्यथा अणु */
/*		CxDevWrReg(CXADEC_SRC_COMB_CFG, 0x6628021F); */
/*    पूर्ण */
	cx18_av_ग_लिखो4(cx, CXADEC_SRC_COMB_CFG, 0x6628021F);
	शेष_volume = cx18_av_पढ़ो(cx, 0x8d4);
	/*
	 * Enक्रमce the legacy volume scale mapping limits to aव्योम
	 * -दुस्फल errors when initializing the volume control
	 */
	अगर (शेष_volume > 228) अणु
		/* Bottom out at -96 dB, v4l2 vol range 0x2e00-0x2fff */
		शेष_volume = 228;
		cx18_av_ग_लिखो(cx, 0x8d4, 228);
	पूर्ण अन्यथा अगर (शेष_volume < 20) अणु
		/* Top out at + 8 dB, v4l2 vol range 0xfe00-0xffff */
		शेष_volume = 20;
		cx18_av_ग_लिखो(cx, 0x8d4, 20);
	पूर्ण
	शेष_volume = (((228 - शेष_volume) >> 1) + 23) << 9;
	state->volume->cur.val = state->volume->शेष_value = शेष_volume;
	v4l2_ctrl_handler_setup(&state->hdl);
पूर्ण

अटल पूर्णांक cx18_av_reset(काष्ठा v4l2_subdev *sd, u32 val)
अणु
	cx18_av_initialize(sd);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_load_fw(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);

	अगर (!state->is_initialized) अणु
		/* initialize on first use */
		state->is_initialized = 1;
		cx18_av_initialize(sd);
	पूर्ण
	वापस 0;
पूर्ण

व्योम cx18_av_std_setup(काष्ठा cx18 *cx)
अणु
	काष्ठा cx18_av_state *state = &cx->av_state;
	काष्ठा v4l2_subdev *sd = &state->sd;
	v4l2_std_id std = state->std;

	/*
	 * Video ADC crystal घड़ी to pixel घड़ी SRC decimation ratio
	 * 28.636360 MHz/13.5 Mpps * 256 = 0x21f.07b
	 */
	स्थिर पूर्णांक src_decimation = 0x21f;

	पूर्णांक hblank, hactive, burst, vblank, vactive, sc;
	पूर्णांक vblank656;
	पूर्णांक luma_lpf, uv_lpf, comb;
	u32 pll_पूर्णांक, pll_frac, pll_post;

	/* datasheet startup, step 8d */
	अगर (std & ~V4L2_STD_NTSC)
		cx18_av_ग_लिखो(cx, 0x49f, 0x11);
	अन्यथा
		cx18_av_ग_लिखो(cx, 0x49f, 0x14);

	/*
	 * Note: At the end of a field, there are 3 sets of half line duration
	 * (द्विगुन horizontal rate) pulses:
	 *
	 * 5 (625) or 6 (525) half-lines to blank क्रम the vertical retrace
	 * 5 (625) or 6 (525) vertical sync pulses of half line duration
	 * 5 (625) or 6 (525) half-lines of equalization pulses
	 */
	अगर (std & V4L2_STD_625_50) अणु
		/*
		 * The following relationships of half line counts should hold:
		 * 625 = vblank656 + vactive
		 * 10 = vblank656 - vblank = vsync pulses + equalization pulses
		 *
		 * vblank656: half lines after line 625/mid-313 of blanked video
		 * vblank:    half lines, after line 5/317, of blanked video
		 * vactive:   half lines of active video +
		 *		5 half lines after the end of active video
		 *
		 * As far as I can tell:
		 * vblank656 starts counting from the falling edge of the first
		 *	vsync pulse (start of line 1 or mid-313)
		 * vblank starts counting from the after the 5 vsync pulses and
		 *	5 or 4 equalization pulses (start of line 6 or 318)
		 *
		 * For 625 line प्रणालीs the driver will extract VBI inक्रमmation
		 * from lines 6-23 and lines 318-335 (but the slicer can only
		 * handle 17 lines, not the 18 in the vblank region).
		 * In addition, we need vblank656 and vblank to be one whole
		 * line दीर्घer, to cover line 24 and 336, so the SAV/EAV RP
		 * codes get generated such that the encoder can actually
		 * extract line 23 & 335 (WSS).  We'll lose 1 line in each field
		 * at the top of the screen.
		 *
		 * It appears the 5 half lines that happen after active
		 * video must be included in vactive (579 instead of 574),
		 * otherwise the colors get badly displayed in various regions
		 * of the screen.  I guess the chroma comb filter माला_लो confused
		 * without them (at least when a PVR-350 is the PAL source).
		 */
		vblank656 = 48; /* lines  1 -  24  &  313 - 336 */
		vblank = 38;    /* lines  6 -  24  &  318 - 336 */
		vactive = 579;  /* lines 24 - 313  &  337 - 626 */

		/*
		 * For a 13.5 Mpps घड़ी and 15,625 Hz line rate, a line is
		 * is 864 pixels = 720 active + 144 blanking.  ITU-R BT.601
		 * specअगरies 12 luma घड़ी periods or ~ 0.9 * 13.5 Mpps after
		 * the end of active video to start a horizontal line, so that
		 * leaves 132 pixels of hblank to ignore.
		 */
		hblank = 132;
		hactive = 720;

		/*
		 * Burst gate delay (क्रम 625 line प्रणालीs)
		 * Hsync leading edge to color burst rise = 5.6 us
		 * Color burst width = 2.25 us
		 * Gate width = 4 pixel घड़ीs
		 * (5.6 us + 2.25/2 us) * 13.5 Mpps + 4/2 घड़ीs = 92.79 घड़ीs
		 */
		burst = 93;
		luma_lpf = 2;
		अगर (std & V4L2_STD_PAL) अणु
			uv_lpf = 1;
			comb = 0x20;
			/* sc = 4433618.75 * src_decimation/28636360 * 2^13 */
			sc = 688700;
		पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_Nc) अणु
			uv_lpf = 1;
			comb = 0x20;
			/* sc = 3582056.25 * src_decimation/28636360 * 2^13 */
			sc = 556422;
		पूर्ण अन्यथा अणु /* SECAM */
			uv_lpf = 0;
			comb = 0;
			/* (fr + fb)/2 = (4406260 + 4250000)/2 = 4328130 */
			/* sc = 4328130 * src_decimation/28636360 * 2^13 */
			sc = 672314;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The following relationships of half line counts should hold:
		 * 525 = prevsync + vblank656 + vactive
		 * 12 = vblank656 - vblank = vsync pulses + equalization pulses
		 *
		 * prevsync:  6 half-lines beक्रमe the vsync pulses
		 * vblank656: half lines, after line 3/mid-266, of blanked video
		 * vblank:    half lines, after line 9/272, of blanked video
		 * vactive:   half lines of active video
		 *
		 * As far as I can tell:
		 * vblank656 starts counting from the falling edge of the first
		 *	vsync pulse (start of line 4 or mid-266)
		 * vblank starts counting from the after the 6 vsync pulses and
		 *	6 or 5 equalization pulses (start of line 10 or 272)
		 *
		 * For 525 line प्रणालीs the driver will extract VBI inक्रमmation
		 * from lines 10-21 and lines 273-284.
		 */
		vblank656 = 38; /* lines  4 -  22  &  266 - 284 */
		vblank = 26;	/* lines 10 -  22  &  272 - 284 */
		vactive = 481;  /* lines 23 - 263  &  285 - 525 */

		/*
		 * For a 13.5 Mpps घड़ी and 15,734.26 Hz line rate, a line is
		 * is 858 pixels = 720 active + 138 blanking.  The Hsync leading
		 * edge should happen 1.2 us * 13.5 Mpps ~= 16 pixels after the
		 * end of active video, leaving 122 pixels of hblank to ignore
		 * beक्रमe active video starts.
		 */
		hactive = 720;
		hblank = 122;
		luma_lpf = 1;
		uv_lpf = 1;

		/*
		 * Burst gate delay (क्रम 525 line प्रणालीs)
		 * Hsync leading edge to color burst rise = 5.3 us
		 * Color burst width = 2.5 us
		 * Gate width = 4 pixel घड़ीs
		 * (5.3 us + 2.5/2 us) * 13.5 Mpps + 4/2 घड़ीs = 90.425 घड़ीs
		 */
		अगर (std == V4L2_STD_PAL_60) अणु
			burst = 90;
			luma_lpf = 2;
			comb = 0x20;
			/* sc = 4433618.75 * src_decimation/28636360 * 2^13 */
			sc = 688700;
		पूर्ण अन्यथा अगर (std == V4L2_STD_PAL_M) अणु
			/* The 97 needs to be verअगरied against PAL-M timings */
			burst = 97;
			comb = 0x20;
			/* sc = 3575611.49 * src_decimation/28636360 * 2^13 */
			sc = 555421;
		पूर्ण अन्यथा अणु
			burst = 90;
			comb = 0x66;
			/* sc = 3579545.45.. * src_decimation/28636360 * 2^13 */
			sc = 556032;
		पूर्ण
	पूर्ण

	/* DEBUG: Displays configured PLL frequency */
	pll_पूर्णांक = cx18_av_पढ़ो(cx, 0x108);
	pll_frac = cx18_av_पढ़ो4(cx, 0x10c) & 0x1ffffff;
	pll_post = cx18_av_पढ़ो(cx, 0x109);
	CX18_DEBUG_INFO_DEV(sd, "PLL regs = int: %u, frac: %u, post: %u\n",
			    pll_पूर्णांक, pll_frac, pll_post);

	अगर (pll_post) अणु
		पूर्णांक fsc, pll;
		u64 पंचांगp;

		pll = (28636360L * ((((u64)pll_पूर्णांक) << 25) + pll_frac)) >> 25;
		pll /= pll_post;
		CX18_DEBUG_INFO_DEV(sd, "Video PLL = %d.%06d MHz\n",
				    pll / 1000000, pll % 1000000);
		CX18_DEBUG_INFO_DEV(sd, "Pixel rate = %d.%06d Mpixel/sec\n",
				    pll / 8000000, (pll / 8) % 1000000);

		CX18_DEBUG_INFO_DEV(sd, "ADC XTAL/pixel clock decimation ratio = %d.%03d\n",
				    src_decimation / 256,
				    ((src_decimation % 256) * 1000) / 256);

		पंचांगp = 28636360 * (u64) sc;
		करो_भाग(पंचांगp, src_decimation);
		fsc = पंचांगp >> 13;
		CX18_DEBUG_INFO_DEV(sd,
				    "Chroma sub-carrier initial freq = %d.%06d MHz\n",
				    fsc / 1000000, fsc % 1000000);

		CX18_DEBUG_INFO_DEV(sd,
				    "hblank %i, hactive %i, vblank %i, vactive %i, vblank656 %i, src_dec %i, burst 0x%02x, luma_lpf %i, uv_lpf %i, comb 0x%02x, sc 0x%06x\n",
				    hblank, hactive, vblank, vactive, vblank656,
				    src_decimation, burst, luma_lpf, uv_lpf,
				    comb, sc);
	पूर्ण

	/* Sets horizontal blanking delay and active lines */
	cx18_av_ग_लिखो(cx, 0x470, hblank);
	cx18_av_ग_लिखो(cx, 0x471,
		      (((hblank >> 8) & 0x3) | (hactive << 4)) & 0xff);
	cx18_av_ग_लिखो(cx, 0x472, hactive >> 4);

	/* Sets burst gate delay */
	cx18_av_ग_लिखो(cx, 0x473, burst);

	/* Sets vertical blanking delay and active duration */
	cx18_av_ग_लिखो(cx, 0x474, vblank);
	cx18_av_ग_लिखो(cx, 0x475,
		      (((vblank >> 8) & 0x3) | (vactive << 4)) & 0xff);
	cx18_av_ग_लिखो(cx, 0x476, vactive >> 4);
	cx18_av_ग_लिखो(cx, 0x477, vblank656);

	/* Sets src decimation rate */
	cx18_av_ग_लिखो(cx, 0x478, src_decimation & 0xff);
	cx18_av_ग_लिखो(cx, 0x479, (src_decimation >> 8) & 0xff);

	/* Sets Luma and UV Low pass filters */
	cx18_av_ग_लिखो(cx, 0x47a, luma_lpf << 6 | ((uv_lpf << 4) & 0x30));

	/* Enables comb filters */
	cx18_av_ग_लिखो(cx, 0x47b, comb);

	/* Sets SC Step*/
	cx18_av_ग_लिखो(cx, 0x47c, sc);
	cx18_av_ग_लिखो(cx, 0x47d, (sc >> 8) & 0xff);
	cx18_av_ग_लिखो(cx, 0x47e, (sc >> 16) & 0xff);

	अगर (std & V4L2_STD_625_50) अणु
		state->slicer_line_delay = 1;
		state->slicer_line_offset = (6 + state->slicer_line_delay - 2);
	पूर्ण अन्यथा अणु
		state->slicer_line_delay = 0;
		state->slicer_line_offset = (10 + state->slicer_line_delay - 2);
	पूर्ण
	cx18_av_ग_लिखो(cx, 0x47f, state->slicer_line_delay);
पूर्ण

अटल व्योम input_change(काष्ठा cx18 *cx)
अणु
	काष्ठा cx18_av_state *state = &cx->av_state;
	v4l2_std_id std = state->std;
	u8 v;

	/* Follow step 8c and 8d of section 3.16 in the cx18_av datasheet */
	cx18_av_ग_लिखो(cx, 0x49f, (std & V4L2_STD_NTSC) ? 0x14 : 0x11);
	cx18_av_and_or(cx, 0x401, ~0x60, 0);
	cx18_av_and_or(cx, 0x401, ~0x60, 0x60);

	अगर (std & V4L2_STD_525_60) अणु
		अगर (std == V4L2_STD_NTSC_M_JP) अणु
			/* Japan uses EIAJ audio standard */
			cx18_av_ग_लिखो_expect(cx, 0x808, 0xf7, 0xf7, 0xff);
			cx18_av_ग_लिखो_expect(cx, 0x80b, 0x02, 0x02, 0x3f);
		पूर्ण अन्यथा अगर (std == V4L2_STD_NTSC_M_KR) अणु
			/* South Korea uses A2 audio standard */
			cx18_av_ग_लिखो_expect(cx, 0x808, 0xf8, 0xf8, 0xff);
			cx18_av_ग_लिखो_expect(cx, 0x80b, 0x03, 0x03, 0x3f);
		पूर्ण अन्यथा अणु
			/* Others use the BTSC audio standard */
			cx18_av_ग_लिखो_expect(cx, 0x808, 0xf6, 0xf6, 0xff);
			cx18_av_ग_लिखो_expect(cx, 0x80b, 0x01, 0x01, 0x3f);
		पूर्ण
	पूर्ण अन्यथा अगर (std & V4L2_STD_PAL) अणु
		/* Follow tuner change procedure क्रम PAL */
		cx18_av_ग_लिखो_expect(cx, 0x808, 0xff, 0xff, 0xff);
		cx18_av_ग_लिखो_expect(cx, 0x80b, 0x03, 0x03, 0x3f);
	पूर्ण अन्यथा अगर (std & V4L2_STD_SECAM) अणु
		/* Select स्वतःdetect क्रम SECAM */
		cx18_av_ग_लिखो_expect(cx, 0x808, 0xff, 0xff, 0xff);
		cx18_av_ग_लिखो_expect(cx, 0x80b, 0x03, 0x03, 0x3f);
	पूर्ण

	v = cx18_av_पढ़ो(cx, 0x803);
	अगर (v & 0x10) अणु
		/* restart audio decoder microcontroller */
		v &= ~0x10;
		cx18_av_ग_लिखो_expect(cx, 0x803, v, v, 0x1f);
		v |= 0x10;
		cx18_av_ग_लिखो_expect(cx, 0x803, v, v, 0x1f);
	पूर्ण
पूर्ण

अटल पूर्णांक cx18_av_s_frequency(काष्ठा v4l2_subdev *sd,
			       स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	input_change(cx);
	वापस 0;
पूर्ण

अटल पूर्णांक set_input(काष्ठा cx18 *cx, क्रमागत cx18_av_video_input vid_input,
					क्रमागत cx18_av_audio_input aud_input)
अणु
	काष्ठा cx18_av_state *state = &cx->av_state;
	काष्ठा v4l2_subdev *sd = &state->sd;

	क्रमागत analog_संकेत_type अणु
		NONE, CVBS, Y, C, SIF, Pb, Pr
	पूर्ण ch[3] = अणुNONE, NONE, NONEपूर्ण;

	u8 afe_mux_cfg;
	u8 adc2_cfg;
	u8 input_mode;
	u32 afe_cfg;
	पूर्णांक i;

	CX18_DEBUG_INFO_DEV(sd, "decoder set video input %d, audio input %d\n",
			    vid_input, aud_input);

	अगर (vid_input >= CX18_AV_COMPOSITE1 &&
	    vid_input <= CX18_AV_COMPOSITE8) अणु
		afe_mux_cfg = 0xf0 + (vid_input - CX18_AV_COMPOSITE1);
		ch[0] = CVBS;
		input_mode = 0x0;
	पूर्ण अन्यथा अगर (vid_input >= CX18_AV_COMPONENT_LUMA1) अणु
		पूर्णांक luma = vid_input & 0xf000;
		पूर्णांक r_chroma = vid_input & 0xf0000;
		पूर्णांक b_chroma = vid_input & 0xf00000;

		अगर ((vid_input & ~0xfff000) ||
		    luma < CX18_AV_COMPONENT_LUMA1 ||
		    luma > CX18_AV_COMPONENT_LUMA8 ||
		    r_chroma < CX18_AV_COMPONENT_R_CHROMA4 ||
		    r_chroma > CX18_AV_COMPONENT_R_CHROMA6 ||
		    b_chroma < CX18_AV_COMPONENT_B_CHROMA7 ||
		    b_chroma > CX18_AV_COMPONENT_B_CHROMA8) अणु
			CX18_ERR_DEV(sd, "0x%06x is not a valid video input!\n",
				     vid_input);
			वापस -EINVAL;
		पूर्ण
		afe_mux_cfg = (luma - CX18_AV_COMPONENT_LUMA1) >> 12;
		ch[0] = Y;
		afe_mux_cfg |= (r_chroma - CX18_AV_COMPONENT_R_CHROMA4) >> 12;
		ch[1] = Pr;
		afe_mux_cfg |= (b_chroma - CX18_AV_COMPONENT_B_CHROMA7) >> 14;
		ch[2] = Pb;
		input_mode = 0x6;
	पूर्ण अन्यथा अणु
		पूर्णांक luma = vid_input & 0xf0;
		पूर्णांक chroma = vid_input & 0xf00;

		अगर ((vid_input & ~0xff0) ||
		    luma < CX18_AV_SVIDEO_LUMA1 ||
		    luma > CX18_AV_SVIDEO_LUMA8 ||
		    chroma < CX18_AV_SVIDEO_CHROMA4 ||
		    chroma > CX18_AV_SVIDEO_CHROMA8) अणु
			CX18_ERR_DEV(sd, "0x%06x is not a valid video input!\n",
				     vid_input);
			वापस -EINVAL;
		पूर्ण
		afe_mux_cfg = 0xf0 + ((luma - CX18_AV_SVIDEO_LUMA1) >> 4);
		ch[0] = Y;
		अगर (chroma >= CX18_AV_SVIDEO_CHROMA7) अणु
			afe_mux_cfg &= 0x3f;
			afe_mux_cfg |= (chroma - CX18_AV_SVIDEO_CHROMA7) >> 2;
			ch[2] = C;
		पूर्ण अन्यथा अणु
			afe_mux_cfg &= 0xcf;
			afe_mux_cfg |= (chroma - CX18_AV_SVIDEO_CHROMA4) >> 4;
			ch[1] = C;
		पूर्ण
		input_mode = 0x2;
	पूर्ण

	चयन (aud_input) अणु
	हाल CX18_AV_AUDIO_SERIAL1:
	हाल CX18_AV_AUDIO_SERIAL2:
		/* करो nothing, use serial audio input */
		अवरोध;
	हाल CX18_AV_AUDIO4:
		afe_mux_cfg &= ~0x30;
		ch[1] = SIF;
		अवरोध;
	हाल CX18_AV_AUDIO5:
		afe_mux_cfg = (afe_mux_cfg & ~0x30) | 0x10;
		ch[1] = SIF;
		अवरोध;
	हाल CX18_AV_AUDIO6:
		afe_mux_cfg = (afe_mux_cfg & ~0x30) | 0x20;
		ch[1] = SIF;
		अवरोध;
	हाल CX18_AV_AUDIO7:
		afe_mux_cfg &= ~0xc0;
		ch[2] = SIF;
		अवरोध;
	हाल CX18_AV_AUDIO8:
		afe_mux_cfg = (afe_mux_cfg & ~0xc0) | 0x40;
		ch[2] = SIF;
		अवरोध;

	शेष:
		CX18_ERR_DEV(sd, "0x%04x is not a valid audio input!\n",
			     aud_input);
		वापस -EINVAL;
	पूर्ण

	/* Set up analog front end multiplexers */
	cx18_av_ग_लिखो_expect(cx, 0x103, afe_mux_cfg, afe_mux_cfg, 0xf7);
	/* Set INPUT_MODE to Composite, S-Video, or Component */
	cx18_av_and_or(cx, 0x401, ~0x6, input_mode);

	/* Set CH_SEL_ADC2 to 1 अगर input comes from CH3 */
	adc2_cfg = cx18_av_पढ़ो(cx, 0x102);
	अगर (ch[2] == NONE)
		adc2_cfg &= ~0x2; /* No sig on CH3, set ADC2 to CH2 क्रम input */
	अन्यथा
		adc2_cfg |= 0x2;  /* Signal on CH3, set ADC2 to CH3 क्रम input */

	/* Set DUAL_MODE_ADC2 to 1 अगर input comes from both CH2 and CH3 */
	अगर (ch[1] != NONE && ch[2] != NONE)
		adc2_cfg |= 0x4; /* Set dual mode */
	अन्यथा
		adc2_cfg &= ~0x4; /* Clear dual mode */
	cx18_av_ग_लिखो_expect(cx, 0x102, adc2_cfg, adc2_cfg, 0x17);

	/* Configure the analog front end */
	afe_cfg = cx18_av_पढ़ो4(cx, CXADEC_AFE_CTRL);
	afe_cfg &= 0xff000000;
	afe_cfg |= 0x00005000; /* CHROMA_IN, AUD_IN: ADC2; LUMA_IN: ADC1 */
	अगर (ch[1] != NONE && ch[2] != NONE)
		afe_cfg |= 0x00000030; /* half_bw_ch[2-3] since in dual mode */

	क्रम (i = 0; i < 3; i++) अणु
		चयन (ch[i]) अणु
		शेष:
		हाल NONE:
			/* CLAMP_SEL = Fixed to midcode clamp level */
			afe_cfg |= (0x00000200 << i);
			अवरोध;
		हाल CVBS:
		हाल Y:
			अगर (i > 0)
				afe_cfg |= 0x00002000; /* LUMA_IN_SEL: ADC2 */
			अवरोध;
		हाल C:
		हाल Pb:
		हाल Pr:
			/* CLAMP_SEL = Fixed to midcode clamp level */
			afe_cfg |= (0x00000200 << i);
			अगर (i == 0 && ch[i] == C)
				afe_cfg &= ~0x00001000; /* CHROMA_IN_SEL ADC1 */
			अवरोध;
		हाल SIF:
			/*
			 * VGA_GAIN_SEL = Audio Decoder
			 * CLAMP_SEL = Fixed to midcode clamp level
			 */
			afe_cfg |= (0x00000240 << i);
			अगर (i == 0)
				afe_cfg &= ~0x00004000; /* AUD_IN_SEL ADC1 */
			अवरोध;
		पूर्ण
	पूर्ण

	cx18_av_ग_लिखो4(cx, CXADEC_AFE_CTRL, afe_cfg);

	state->vid_input = vid_input;
	state->aud_input = aud_input;
	cx18_av_audio_set_path(cx);
	input_change(cx);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_s_video_routing(काष्ठा v4l2_subdev *sd,
				   u32 input, u32 output, u32 config)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	वापस set_input(cx, input, state->aud_input);
पूर्ण

अटल पूर्णांक cx18_av_s_audio_routing(काष्ठा v4l2_subdev *sd,
				   u32 input, u32 output, u32 config)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	वापस set_input(cx, state->vid_input, input);
पूर्ण

अटल पूर्णांक cx18_av_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	u8 vpres;
	u8 mode;
	पूर्णांक val = 0;

	अगर (state->radio)
		वापस 0;

	vpres = cx18_av_पढ़ो(cx, 0x40e) & 0x20;
	vt->संकेत = vpres ? 0xffff : 0x0;

	vt->capability |=
		    V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LANG1 |
		    V4L2_TUNER_CAP_LANG2 | V4L2_TUNER_CAP_SAP;

	mode = cx18_av_पढ़ो(cx, 0x804);

	/* get rxsubchans and audmode */
	अगर ((mode & 0xf) == 1)
		val |= V4L2_TUNER_SUB_STEREO;
	अन्यथा
		val |= V4L2_TUNER_SUB_MONO;

	अगर (mode == 2 || mode == 4)
		val = V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;

	अगर (mode & 0x10)
		val |= V4L2_TUNER_SUB_SAP;

	vt->rxsubchans = val;
	vt->audmode = state->audmode;
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	u8 v;

	अगर (state->radio)
		वापस 0;

	v = cx18_av_पढ़ो(cx, 0x809);
	v &= ~0xf;

	चयन (vt->audmode) अणु
	हाल V4L2_TUNER_MODE_MONO:
		/* mono      -> mono
		   stereo    -> mono
		   bilingual -> lang1 */
		अवरोध;
	हाल V4L2_TUNER_MODE_STEREO:
	हाल V4L2_TUNER_MODE_LANG1:
		/* mono      -> mono
		   stereo    -> stereo
		   bilingual -> lang1 */
		v |= 0x4;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG1_LANG2:
		/* mono      -> mono
		   stereo    -> stereo
		   bilingual -> lang1/lang2 */
		v |= 0x7;
		अवरोध;
	हाल V4L2_TUNER_MODE_LANG2:
		/* mono      -> mono
		   stereo    -> stereo
		   bilingual -> lang2 */
		v |= 0x1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	cx18_av_ग_लिखो_expect(cx, 0x809, v, v, 0xff);
	state->audmode = vt->audmode;
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id norm)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	u8 fmt = 0;	/* zero is स्वतःdetect */
	u8 pal_m = 0;

	अगर (state->radio == 0 && state->std == norm)
		वापस 0;

	state->radio = 0;
	state->std = norm;

	/* First tests should be against specअगरic std */
	अगर (state->std == V4L2_STD_NTSC_M_JP) अणु
		fmt = 0x2;
	पूर्ण अन्यथा अगर (state->std == V4L2_STD_NTSC_443) अणु
		fmt = 0x3;
	पूर्ण अन्यथा अगर (state->std == V4L2_STD_PAL_M) अणु
		pal_m = 1;
		fmt = 0x5;
	पूर्ण अन्यथा अगर (state->std == V4L2_STD_PAL_N) अणु
		fmt = 0x6;
	पूर्ण अन्यथा अगर (state->std == V4L2_STD_PAL_Nc) अणु
		fmt = 0x7;
	पूर्ण अन्यथा अगर (state->std == V4L2_STD_PAL_60) अणु
		fmt = 0x8;
	पूर्ण अन्यथा अणु
		/* Then, test against generic ones */
		अगर (state->std & V4L2_STD_NTSC)
			fmt = 0x1;
		अन्यथा अगर (state->std & V4L2_STD_PAL)
			fmt = 0x4;
		अन्यथा अगर (state->std & V4L2_STD_SECAM)
			fmt = 0xc;
	पूर्ण

	CX18_DEBUG_INFO_DEV(sd, "changing video std to fmt %i\n", fmt);

	/* Follow step 9 of section 3.16 in the cx18_av datasheet.
	   Without this PAL may display a vertical ghosting effect.
	   This happens क्रम example with the Yuan MPC622. */
	अगर (fmt >= 4 && fmt < 8) अणु
		/* Set क्रमmat to NTSC-M */
		cx18_av_and_or(cx, 0x400, ~0xf, 1);
		/* Turn off LCOMB */
		cx18_av_and_or(cx, 0x47b, ~6, 0);
	पूर्ण
	cx18_av_and_or(cx, 0x400, ~0x2f, fmt | 0x20);
	cx18_av_and_or(cx, 0x403, ~0x3, pal_m);
	cx18_av_std_setup(cx);
	input_change(cx);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	state->radio = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		cx18_av_ग_लिखो(cx, 0x414, ctrl->val - 128);
		अवरोध;

	हाल V4L2_CID_CONTRAST:
		cx18_av_ग_लिखो(cx, 0x415, ctrl->val << 1);
		अवरोध;

	हाल V4L2_CID_SATURATION:
		cx18_av_ग_लिखो(cx, 0x420, ctrl->val << 1);
		cx18_av_ग_लिखो(cx, 0x421, ctrl->val << 1);
		अवरोध;

	हाल V4L2_CID_HUE:
		cx18_av_ग_लिखो(cx, 0x422, ctrl->val);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_set_fmt(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_subdev_pad_config *cfg,
		काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा v4l2_mbus_framefmt *fmt = &क्रमmat->क्रमmat;
	काष्ठा cx18_av_state *state = to_cx18_av_state(sd);
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	पूर्णांक HSC, VSC, Vsrc, Hsrc, filter, Vlines;
	पूर्णांक is_50Hz = !(state->std & V4L2_STD_525_60);

	अगर (क्रमmat->pad || fmt->code != MEDIA_BUS_FMT_FIXED)
		वापस -EINVAL;

	fmt->field = V4L2_FIELD_INTERLACED;
	fmt->colorspace = V4L2_COLORSPACE_SMPTE170M;

	Vsrc = (cx18_av_पढ़ो(cx, 0x476) & 0x3f) << 4;
	Vsrc |= (cx18_av_पढ़ो(cx, 0x475) & 0xf0) >> 4;

	Hsrc = (cx18_av_पढ़ो(cx, 0x472) & 0x3f) << 4;
	Hsrc |= (cx18_av_पढ़ो(cx, 0x471) & 0xf0) >> 4;

	/*
	 * This adjusपंचांगent reflects the excess of vactive, set in
	 * cx18_av_std_setup(), above standard values:
	 *
	 * 480 + 1 क्रम 60 Hz प्रणालीs
	 * 576 + 3 क्रम 50 Hz प्रणालीs
	 */
	Vlines = fmt->height + (is_50Hz ? 3 : 1);

	/*
	 * Invalid height and width scaling requests are:
	 * 1. width less than 1/16 of the source width
	 * 2. width greater than the source width
	 * 3. height less than 1/8 of the source height
	 * 4. height greater than the source height
	 */
	अगर ((fmt->width * 16 < Hsrc) || (Hsrc < fmt->width) ||
	    (Vlines * 8 < Vsrc) || (Vsrc < Vlines)) अणु
		CX18_ERR_DEV(sd, "%dx%d is not a valid size!\n",
			     fmt->width, fmt->height);
		वापस -दुस्फल;
	पूर्ण

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY)
		वापस 0;

	HSC = (Hsrc * (1 << 20)) / fmt->width - (1 << 20);
	VSC = (1 << 16) - (Vsrc * (1 << 9) / Vlines - (1 << 9));
	VSC &= 0x1fff;

	अगर (fmt->width >= 385)
		filter = 0;
	अन्यथा अगर (fmt->width > 192)
		filter = 1;
	अन्यथा अगर (fmt->width > 96)
		filter = 2;
	अन्यथा
		filter = 3;

	CX18_DEBUG_INFO_DEV(sd,
			    "decoder set size %dx%d -> scale  %ux%u\n",
			    fmt->width, fmt->height, HSC, VSC);

	/* HSCALE=HSC */
	cx18_av_ग_लिखो(cx, 0x418, HSC & 0xff);
	cx18_av_ग_लिखो(cx, 0x419, (HSC >> 8) & 0xff);
	cx18_av_ग_लिखो(cx, 0x41a, HSC >> 16);
	/* VSCALE=VSC */
	cx18_av_ग_लिखो(cx, 0x41c, VSC & 0xff);
	cx18_av_ग_लिखो(cx, 0x41d, VSC >> 8);
	/* VS_INTRLACE=1 VFILT=filter */
	cx18_av_ग_लिखो(cx, 0x41e, 0x8 | filter);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	CX18_DEBUG_INFO_DEV(sd, "%s output\n", enable ? "enable" : "disable");
	अगर (enable) अणु
		cx18_av_ग_लिखो(cx, 0x115, 0x8c);
		cx18_av_ग_लिखो(cx, 0x116, 0x07);
	पूर्ण अन्यथा अणु
		cx18_av_ग_लिखो(cx, 0x115, 0x00);
		cx18_av_ग_लिखो(cx, 0x116, 0x00);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम log_video_status(काष्ठा cx18 *cx)
अणु
	अटल स्थिर अक्षर *स्थिर fmt_strs[] = अणु
		"0x0",
		"NTSC-M", "NTSC-J", "NTSC-4.43",
		"PAL-BDGHI", "PAL-M", "PAL-N", "PAL-Nc", "PAL-60",
		"0x9", "0xA", "0xB",
		"SECAM",
		"0xD", "0xE", "0xF"
	पूर्ण;

	काष्ठा cx18_av_state *state = &cx->av_state;
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 vidfmt_sel = cx18_av_पढ़ो(cx, 0x400) & 0xf;
	u8 gen_stat1 = cx18_av_पढ़ो(cx, 0x40d);
	u8 gen_stat2 = cx18_av_पढ़ो(cx, 0x40e);
	पूर्णांक vid_input = state->vid_input;

	CX18_INFO_DEV(sd, "Video signal:              %spresent\n",
		      (gen_stat2 & 0x20) ? "" : "not ");
	CX18_INFO_DEV(sd, "Detected format:           %s\n",
		      fmt_strs[gen_stat1 & 0xf]);

	CX18_INFO_DEV(sd, "Specified standard:        %s\n",
		      vidfmt_sel ? fmt_strs[vidfmt_sel]
				 : "automatic detection");

	अगर (vid_input >= CX18_AV_COMPOSITE1 &&
	    vid_input <= CX18_AV_COMPOSITE8) अणु
		CX18_INFO_DEV(sd, "Specified video input:     Composite %d\n",
			      vid_input - CX18_AV_COMPOSITE1 + 1);
	पूर्ण अन्यथा अणु
		CX18_INFO_DEV(sd, "Specified video input:     S-Video (Luma In%d, Chroma In%d)\n",
			      (vid_input & 0xf0) >> 4,
			      (vid_input & 0xf00) >> 8);
	पूर्ण

	CX18_INFO_DEV(sd, "Specified audioclock freq: %d Hz\n",
		      state->audclk_freq);
पूर्ण

अटल व्योम log_audio_status(काष्ठा cx18 *cx)
अणु
	काष्ठा cx18_av_state *state = &cx->av_state;
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 करोwnload_ctl = cx18_av_पढ़ो(cx, 0x803);
	u8 mod_det_stat0 = cx18_av_पढ़ो(cx, 0x804);
	u8 mod_det_stat1 = cx18_av_पढ़ो(cx, 0x805);
	u8 audio_config = cx18_av_पढ़ो(cx, 0x808);
	u8 pref_mode = cx18_av_पढ़ो(cx, 0x809);
	u8 afc0 = cx18_av_पढ़ो(cx, 0x80b);
	u8 mute_ctl = cx18_av_पढ़ो(cx, 0x8d3);
	पूर्णांक aud_input = state->aud_input;
	अक्षर *p;

	चयन (mod_det_stat0) अणु
	हाल 0x00: p = "mono"; अवरोध;
	हाल 0x01: p = "stereo"; अवरोध;
	हाल 0x02: p = "dual"; अवरोध;
	हाल 0x04: p = "tri"; अवरोध;
	हाल 0x10: p = "mono with SAP"; अवरोध;
	हाल 0x11: p = "stereo with SAP"; अवरोध;
	हाल 0x12: p = "dual with SAP"; अवरोध;
	हाल 0x14: p = "tri with SAP"; अवरोध;
	हाल 0xfe: p = "forced mode"; अवरोध;
	शेष: p = "not defined"; अवरोध;
	पूर्ण
	CX18_INFO_DEV(sd, "Detected audio mode:       %s\n", p);

	चयन (mod_det_stat1) अणु
	हाल 0x00: p = "not defined"; अवरोध;
	हाल 0x01: p = "EIAJ"; अवरोध;
	हाल 0x02: p = "A2-M"; अवरोध;
	हाल 0x03: p = "A2-BG"; अवरोध;
	हाल 0x04: p = "A2-DK1"; अवरोध;
	हाल 0x05: p = "A2-DK2"; अवरोध;
	हाल 0x06: p = "A2-DK3"; अवरोध;
	हाल 0x07: p = "A1 (6.0 MHz FM Mono)"; अवरोध;
	हाल 0x08: p = "AM-L"; अवरोध;
	हाल 0x09: p = "NICAM-BG"; अवरोध;
	हाल 0x0a: p = "NICAM-DK"; अवरोध;
	हाल 0x0b: p = "NICAM-I"; अवरोध;
	हाल 0x0c: p = "NICAM-L"; अवरोध;
	हाल 0x0d: p = "BTSC/EIAJ/A2-M Mono (4.5 MHz FMMono)"; अवरोध;
	हाल 0x0e: p = "IF FM Radio"; अवरोध;
	हाल 0x0f: p = "BTSC"; अवरोध;
	हाल 0x10: p = "detected chrominance"; अवरोध;
	हाल 0xfd: p = "unknown audio standard"; अवरोध;
	हाल 0xfe: p = "forced audio standard"; अवरोध;
	हाल 0xff: p = "no detected audio standard"; अवरोध;
	शेष: p = "not defined"; अवरोध;
	पूर्ण
	CX18_INFO_DEV(sd, "Detected audio standard:   %s\n", p);
	CX18_INFO_DEV(sd, "Audio muted:               %s\n",
		      (mute_ctl & 0x2) ? "yes" : "no");
	CX18_INFO_DEV(sd, "Audio microcontroller:     %s\n",
		      (करोwnload_ctl & 0x10) ? "running" : "stopped");

	चयन (audio_config >> 4) अणु
	हाल 0x00: p = "undefined"; अवरोध;
	हाल 0x01: p = "BTSC"; अवरोध;
	हाल 0x02: p = "EIAJ"; अवरोध;
	हाल 0x03: p = "A2-M"; अवरोध;
	हाल 0x04: p = "A2-BG"; अवरोध;
	हाल 0x05: p = "A2-DK1"; अवरोध;
	हाल 0x06: p = "A2-DK2"; अवरोध;
	हाल 0x07: p = "A2-DK3"; अवरोध;
	हाल 0x08: p = "A1 (6.0 MHz FM Mono)"; अवरोध;
	हाल 0x09: p = "AM-L"; अवरोध;
	हाल 0x0a: p = "NICAM-BG"; अवरोध;
	हाल 0x0b: p = "NICAM-DK"; अवरोध;
	हाल 0x0c: p = "NICAM-I"; अवरोध;
	हाल 0x0d: p = "NICAM-L"; अवरोध;
	हाल 0x0e: p = "FM radio"; अवरोध;
	हाल 0x0f: p = "automatic detection"; अवरोध;
	शेष: p = "undefined"; अवरोध;
	पूर्ण
	CX18_INFO_DEV(sd, "Configured audio standard: %s\n", p);

	अगर ((audio_config >> 4) < 0xF) अणु
		चयन (audio_config & 0xF) अणु
		हाल 0x00: p = "MONO1 (LANGUAGE A/Mono L+R channel for BTSC, EIAJ, A2)"; अवरोध;
		हाल 0x01: p = "MONO2 (LANGUAGE B)"; अवरोध;
		हाल 0x02: p = "MONO3 (STEREO forced MONO)"; अवरोध;
		हाल 0x03: p = "MONO4 (NICAM ANALOG-Language C/Analog Fallback)"; अवरोध;
		हाल 0x04: p = "STEREO"; अवरोध;
		हाल 0x05: p = "DUAL1 (AC)"; अवरोध;
		हाल 0x06: p = "DUAL2 (BC)"; अवरोध;
		हाल 0x07: p = "DUAL3 (AB)"; अवरोध;
		शेष: p = "undefined";
		पूर्ण
		CX18_INFO_DEV(sd, "Configured audio mode:     %s\n", p);
	पूर्ण अन्यथा अणु
		चयन (audio_config & 0xF) अणु
		हाल 0x00: p = "BG"; अवरोध;
		हाल 0x01: p = "DK1"; अवरोध;
		हाल 0x02: p = "DK2"; अवरोध;
		हाल 0x03: p = "DK3"; अवरोध;
		हाल 0x04: p = "I"; अवरोध;
		हाल 0x05: p = "L"; अवरोध;
		हाल 0x06: p = "BTSC"; अवरोध;
		हाल 0x07: p = "EIAJ"; अवरोध;
		हाल 0x08: p = "A2-M"; अवरोध;
		हाल 0x09: p = "FM Radio (4.5 MHz)"; अवरोध;
		हाल 0x0a: p = "FM Radio (5.5 MHz)"; अवरोध;
		हाल 0x0b: p = "S-Video"; अवरोध;
		हाल 0x0f: p = "automatic standard and mode detection"; अवरोध;
		शेष: p = "undefined"; अवरोध;
		पूर्ण
		CX18_INFO_DEV(sd, "Configured audio system:   %s\n", p);
	पूर्ण

	अगर (aud_input)
		CX18_INFO_DEV(sd, "Specified audio input:     Tuner (In%d)\n",
			      aud_input);
	अन्यथा
		CX18_INFO_DEV(sd, "Specified audio input:     External\n");

	चयन (pref_mode & 0xf) अणु
	हाल 0: p = "mono/language A"; अवरोध;
	हाल 1: p = "language B"; अवरोध;
	हाल 2: p = "language C"; अवरोध;
	हाल 3: p = "analog fallback"; अवरोध;
	हाल 4: p = "stereo"; अवरोध;
	हाल 5: p = "language AC"; अवरोध;
	हाल 6: p = "language BC"; अवरोध;
	हाल 7: p = "language AB"; अवरोध;
	शेष: p = "undefined"; अवरोध;
	पूर्ण
	CX18_INFO_DEV(sd, "Preferred audio mode:      %s\n", p);

	अगर ((audio_config & 0xf) == 0xf) अणु
		चयन ((afc0 >> 3) & 0x1) अणु
		हाल 0: p = "system DK"; अवरोध;
		हाल 1: p = "system L"; अवरोध;
		पूर्ण
		CX18_INFO_DEV(sd, "Selected 65 MHz format:    %s\n", p);

		चयन (afc0 & 0x7) अणु
		हाल 0: p = "Chroma"; अवरोध;
		हाल 1: p = "BTSC"; अवरोध;
		हाल 2: p = "EIAJ"; अवरोध;
		हाल 3: p = "A2-M"; अवरोध;
		हाल 4: p = "autodetect"; अवरोध;
		शेष: p = "undefined"; अवरोध;
		पूर्ण
		CX18_INFO_DEV(sd, "Selected 45 MHz format:    %s\n", p);
	पूर्ण
पूर्ण

अटल पूर्णांक cx18_av_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);
	log_video_status(cx);
	log_audio_status(cx);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक cx18_av_g_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	अगर ((reg->reg & 0x3) != 0)
		वापस -EINVAL;
	reg->size = 4;
	reg->val = cx18_av_पढ़ो4(cx, reg->reg & 0x00000ffc);
	वापस 0;
पूर्ण

अटल पूर्णांक cx18_av_s_रेजिस्टर(काष्ठा v4l2_subdev *sd,
			      स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा cx18 *cx = v4l2_get_subdevdata(sd);

	अगर ((reg->reg & 0x3) != 0)
		वापस -EINVAL;
	cx18_av_ग_लिखो4(cx, reg->reg & 0x00000ffc, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा v4l2_ctrl_ops cx18_av_ctrl_ops = अणु
	.s_ctrl = cx18_av_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops cx18_av_general_ops = अणु
	.log_status = cx18_av_log_status,
	.load_fw = cx18_av_load_fw,
	.reset = cx18_av_reset,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.g_रेजिस्टर = cx18_av_g_रेजिस्टर,
	.s_रेजिस्टर = cx18_av_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops cx18_av_tuner_ops = अणु
	.s_radio = cx18_av_s_radio,
	.s_frequency = cx18_av_s_frequency,
	.g_tuner = cx18_av_g_tuner,
	.s_tuner = cx18_av_s_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops cx18_av_audio_ops = अणु
	.s_घड़ी_freq = cx18_av_s_घड़ी_freq,
	.s_routing = cx18_av_s_audio_routing,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops cx18_av_video_ops = अणु
	.s_std = cx18_av_s_std,
	.s_routing = cx18_av_s_video_routing,
	.s_stream = cx18_av_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_vbi_ops cx18_av_vbi_ops = अणु
	.decode_vbi_line = cx18_av_decode_vbi_line,
	.g_sliced_fmt = cx18_av_g_sliced_fmt,
	.s_sliced_fmt = cx18_av_s_sliced_fmt,
	.s_raw_fmt = cx18_av_s_raw_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops cx18_av_pad_ops = अणु
	.set_fmt = cx18_av_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops cx18_av_ops = अणु
	.core = &cx18_av_general_ops,
	.tuner = &cx18_av_tuner_ops,
	.audio = &cx18_av_audio_ops,
	.video = &cx18_av_video_ops,
	.vbi = &cx18_av_vbi_ops,
	.pad = &cx18_av_pad_ops,
पूर्ण;

पूर्णांक cx18_av_probe(काष्ठा cx18 *cx)
अणु
	काष्ठा cx18_av_state *state = &cx->av_state;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक err;

	state->rev = cx18_av_पढ़ो4(cx, CXADEC_CHIP_CTRL) & 0xffff;

	state->vid_input = CX18_AV_COMPOSITE7;
	state->aud_input = CX18_AV_AUDIO8;
	state->audclk_freq = 48000;
	state->audmode = V4L2_TUNER_MODE_LANG1;
	state->slicer_line_delay = 0;
	state->slicer_line_offset = (10 + state->slicer_line_delay - 2);

	sd = &state->sd;
	v4l2_subdev_init(sd, &cx18_av_ops);
	v4l2_set_subdevdata(sd, cx);
	snम_लिखो(sd->name, माप(sd->name),
		 "%s %03x", cx->v4l2_dev.name, (state->rev >> 4));
	sd->grp_id = CX18_HW_418_AV;
	v4l2_ctrl_handler_init(&state->hdl, 9);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);

	state->volume = v4l2_ctrl_new_std(&state->hdl,
			&cx18_av_audio_ctrl_ops, V4L2_CID_AUDIO_VOLUME,
			0, 65535, 65535 / 100, 0);
	v4l2_ctrl_new_std(&state->hdl,
			&cx18_av_audio_ctrl_ops, V4L2_CID_AUDIO_MUTE,
			0, 1, 1, 0);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_audio_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE,
			0, 65535, 65535 / 100, 32768);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_audio_ctrl_ops,
			V4L2_CID_AUDIO_BASS,
			0, 65535, 65535 / 100, 32768);
	v4l2_ctrl_new_std(&state->hdl, &cx18_av_audio_ctrl_ops,
			V4L2_CID_AUDIO_TREBLE,
			0, 65535, 65535 / 100, 32768);
	sd->ctrl_handler = &state->hdl;
	अगर (state->hdl.error) अणु
		पूर्णांक err = state->hdl.error;

		v4l2_ctrl_handler_मुक्त(&state->hdl);
		वापस err;
	पूर्ण
	err = v4l2_device_रेजिस्टर_subdev(&cx->v4l2_dev, sd);
	अगर (err)
		v4l2_ctrl_handler_मुक्त(&state->hdl);
	अन्यथा
		cx18_av_init(cx);
	वापस err;
पूर्ण
