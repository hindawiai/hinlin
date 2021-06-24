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

#समावेश "matroxfb_base.h"
#समावेश "matroxfb_misc.h"
#समावेश "matroxfb_DAC1064.h"
#समावेश "g450_pll.h"
#समावेश <linux/matroxfb.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "matroxfb_g450.h"

/* Definition of the various controls */
काष्ठा mctl अणु
	काष्ठा v4l2_queryctrl desc;
	माप_प्रकार control;
पूर्ण;

#घोषणा BLMIN	0xF3
#घोषणा WLMAX	0x3FF

अटल स्थिर काष्ठा mctl g450_controls[] =
अणु	अणु अणु V4L2_CID_BRIGHTNESS, V4L2_CTRL_TYPE_INTEGER, 
	  "brightness",
	  0, WLMAX-BLMIN, 1, 370-BLMIN, 
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.brightness) पूर्ण,
	अणु अणु V4L2_CID_CONTRAST, V4L2_CTRL_TYPE_INTEGER, 
	  "contrast",
	  0, 1023, 1, 127, 
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.contrast) पूर्ण,
	अणु अणु V4L2_CID_SATURATION, V4L2_CTRL_TYPE_INTEGER,
	  "saturation",
	  0, 255, 1, 165, 
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.saturation) पूर्ण,
	अणु अणु V4L2_CID_HUE, V4L2_CTRL_TYPE_INTEGER,
	  "hue",
	  0, 255, 1, 0, 
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.hue) पूर्ण,
	अणु अणु MATROXFB_CID_TESTOUT, V4L2_CTRL_TYPE_BOOLEAN,
	  "test output",
	  0, 1, 1, 0, 
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.testout) पूर्ण,
पूर्ण;

#घोषणा G450CTRLS ARRAY_SIZE(g450_controls)

/* Return: positive number: id found
           -EINVAL:         id not found, वापस failure
	   -ENOENT:         id not found, create fake disabled control */
अटल पूर्णांक get_ctrl_id(__u32 v4l2_id) अणु
	पूर्णांक i;

	क्रम (i = 0; i < G450CTRLS; i++) अणु
		अगर (v4l2_id < g450_controls[i].desc.id) अणु
			अगर (g450_controls[i].desc.id == 0x08000000) अणु
				वापस -EINVAL;
			पूर्ण
			वापस -ENOENT;
		पूर्ण
		अगर (v4l2_id == g450_controls[i].desc.id) अणु
			वापस i;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक *get_ctrl_ptr(काष्ठा matrox_fb_info *minfo, अचिन्हित पूर्णांक idx)
अणु
	वापस (पूर्णांक*)((अक्षर*)minfo + g450_controls[idx].control);
पूर्ण

अटल व्योम tvo_fill_शेषs(काष्ठा matrox_fb_info *minfo)
अणु
	अचिन्हित पूर्णांक i;
	
	क्रम (i = 0; i < G450CTRLS; i++) अणु
		*get_ctrl_ptr(minfo, i) = g450_controls[i].desc.शेष_value;
	पूर्ण
पूर्ण

अटल पूर्णांक cve2_get_reg(काष्ठा matrox_fb_info *minfo, पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक val;
	
	matroxfb_DAC_lock_irqsave(flags);
	matroxfb_DAC_out(minfo, 0x87, reg);
	val = matroxfb_DAC_in(minfo, 0x88);
	matroxfb_DAC_unlock_irqrestore(flags);
	वापस val;
पूर्ण

अटल व्योम cve2_set_reg(काष्ठा matrox_fb_info *minfo, पूर्णांक reg, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	matroxfb_DAC_lock_irqsave(flags);
	matroxfb_DAC_out(minfo, 0x87, reg);
	matroxfb_DAC_out(minfo, 0x88, val);
	matroxfb_DAC_unlock_irqrestore(flags);
पूर्ण

अटल व्योम cve2_set_reg10(काष्ठा matrox_fb_info *minfo, पूर्णांक reg, पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	matroxfb_DAC_lock_irqsave(flags);
	matroxfb_DAC_out(minfo, 0x87, reg);
	matroxfb_DAC_out(minfo, 0x88, val >> 2);
	matroxfb_DAC_out(minfo, 0x87, reg + 1);
	matroxfb_DAC_out(minfo, 0x88, val & 3);
	matroxfb_DAC_unlock_irqrestore(flags);
पूर्ण

अटल व्योम g450_compute_bwlevel(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक *bl,
				 पूर्णांक *wl)
अणु
	स्थिर पूर्णांक b = minfo->altout.tvo_params.brightness + BLMIN;
	स्थिर पूर्णांक c = minfo->altout.tvo_params.contrast;

	*bl = max(b - c, BLMIN);
	*wl = min(b + c, WLMAX);
पूर्ण

अटल पूर्णांक g450_query_ctrl(व्योम* md, काष्ठा v4l2_queryctrl *p) अणु
	पूर्णांक i;
	
	i = get_ctrl_id(p->id);
	अगर (i >= 0) अणु
		*p = g450_controls[i].desc;
		वापस 0;
	पूर्ण
	अगर (i == -ENOENT) अणु
		अटल स्थिर काष्ठा v4l2_queryctrl disctrl = 
			अणु .flags = V4L2_CTRL_FLAG_DISABLED पूर्ण;
			
		i = p->id;
		*p = disctrl;
		p->id = i;
		प्र_लिखो(p->name, "Ctrl #%08X", i);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक g450_set_ctrl(व्योम* md, काष्ठा v4l2_control *p) अणु
	पूर्णांक i;
	काष्ठा matrox_fb_info *minfo = md;
	
	i = get_ctrl_id(p->id);
	अगर (i < 0) वापस -EINVAL;

	/*
	 * Check अगर changed.
	 */
	अगर (p->value == *get_ctrl_ptr(minfo, i)) वापस 0;

	/*
	 * Check limits.
	 */
	अगर (p->value > g450_controls[i].desc.maximum) वापस -EINVAL;
	अगर (p->value < g450_controls[i].desc.minimum) वापस -EINVAL;

	/*
	 * Store new value.
	 */
	*get_ctrl_ptr(minfo, i) = p->value;

	चयन (p->id) अणु
		हाल V4L2_CID_BRIGHTNESS:
		हाल V4L2_CID_CONTRAST:
			अणु
				पूर्णांक blacklevel, whitelevel;
				g450_compute_bwlevel(minfo, &blacklevel, &whitelevel);
				cve2_set_reg10(minfo, 0x0e, blacklevel);
				cve2_set_reg10(minfo, 0x1e, whitelevel);
			पूर्ण
			अवरोध;
		हाल V4L2_CID_SATURATION:
			cve2_set_reg(minfo, 0x20, p->value);
			cve2_set_reg(minfo, 0x22, p->value);
			अवरोध;
		हाल V4L2_CID_HUE:
			cve2_set_reg(minfo, 0x25, p->value);
			अवरोध;
		हाल MATROXFB_CID_TESTOUT:
			अणु
				अचिन्हित अक्षर val = cve2_get_reg(minfo, 0x05);
				अगर (p->value) val |=  0x02;
				अन्यथा          val &= ~0x02;
				cve2_set_reg(minfo, 0x05, val);
			पूर्ण
			अवरोध;
	पूर्ण
	

	वापस 0;
पूर्ण

अटल पूर्णांक g450_get_ctrl(व्योम* md, काष्ठा v4l2_control *p) अणु
	पूर्णांक i;
	काष्ठा matrox_fb_info *minfo = md;
	
	i = get_ctrl_id(p->id);
	अगर (i < 0) वापस -EINVAL;
	p->value = *get_ctrl_ptr(minfo, i);
	वापस 0;
पूर्ण

काष्ठा output_desc अणु
	अचिन्हित पूर्णांक	h_vis;
	अचिन्हित पूर्णांक	h_f_porch;
	अचिन्हित पूर्णांक	h_sync;
	अचिन्हित पूर्णांक	h_b_porch;
	अचिन्हित दीर्घ दीर्घ पूर्णांक	chromasc;
	अचिन्हित पूर्णांक	burst;
	अचिन्हित पूर्णांक	v_total;
पूर्ण;

अटल व्योम computeRegs(काष्ठा matrox_fb_info *minfo, काष्ठा mavenregs *r,
			काष्ठा my_timming *mt, स्थिर काष्ठा output_desc *outd)
अणु
	u_पूर्णांक32_t chromasc;
	u_पूर्णांक32_t hlen;
	u_पूर्णांक32_t hsl;
	u_पूर्णांक32_t hbp;
	u_पूर्णांक32_t hfp;
	u_पूर्णांक32_t hvis;
	अचिन्हित पूर्णांक pixघड़ी;
	अचिन्हित दीर्घ दीर्घ piic;
	पूर्णांक mnp;
	पूर्णांक over;
	
	r->regs[0x80] = 0x03;	/* | 0x40 क्रम SCART */

	hvis = ((mt->HDisplay << 1) + 3) & ~3;
	
	अगर (hvis >= 2048) अणु
		hvis = 2044;
	पूर्ण
	
	piic = 1000000000ULL * hvis;
	करो_भाग(piic, outd->h_vis);

	dprपूर्णांकk(KERN_DEBUG "Want %u kHz pixclock\n", (अचिन्हित पूर्णांक)piic);
	
	mnp = matroxfb_g450_setclk(minfo, piic, M_VIDEO_PLL);
	
	mt->mnp = mnp;
	mt->pixघड़ी = g450_mnp2f(minfo, mnp);

	dprपूर्णांकk(KERN_DEBUG "MNP=%08X\n", mnp);

	pixघड़ी = 1000000000U / mt->pixघड़ी;

	dprपूर्णांकk(KERN_DEBUG "Got %u ps pixclock\n", pixघड़ी);

	piic = outd->chromasc;
	करो_भाग(piic, mt->pixघड़ी);
	chromasc = piic;
	
	dprपूर्णांकk(KERN_DEBUG "Chroma is %08X\n", chromasc);

	r->regs[0] = piic >> 24;
	r->regs[1] = piic >> 16;
	r->regs[2] = piic >>  8;
	r->regs[3] = piic >>  0;
	hbp = (((outd->h_b_porch + pixघड़ी) / pixघड़ी)) & ~1;
	hfp = (((outd->h_f_porch + pixघड़ी) / pixघड़ी)) & ~1;
	hsl = (((outd->h_sync + pixघड़ी) / pixघड़ी)) & ~1;
	hlen = hvis + hfp + hsl + hbp;
	over = hlen & 0x0F;
	
	dprपूर्णांकk(KERN_DEBUG "WL: vis=%u, hf=%u, hs=%u, hb=%u, total=%u\n", hvis, hfp, hsl, hbp, hlen);

	अगर (over) अणु
		hfp -= over;
		hlen -= over;
		अगर (over <= 2) अणु
		पूर्ण अन्यथा अगर (over < 10) अणु
			hfp += 4;
			hlen += 4;
		पूर्ण अन्यथा अणु
			hfp += 16;
			hlen += 16;
		पूर्ण
	पूर्ण

	/* maybe cve2 has requirement 800 < hlen < 1184 */
	r->regs[0x08] = hsl;
	r->regs[0x09] = (outd->burst + pixघड़ी - 1) / pixघड़ी;	/* burst length */
	r->regs[0x0A] = hbp;
	r->regs[0x2C] = hfp;
	r->regs[0x31] = hvis / 8;
	r->regs[0x32] = hvis & 7;
	
	dprपूर्णांकk(KERN_DEBUG "PG: vis=%04X, hf=%02X, hs=%02X, hb=%02X, total=%04X\n", hvis, hfp, hsl, hbp, hlen);

	r->regs[0x84] = 1;	/* x sync poपूर्णांक */
	r->regs[0x85] = 0;
	hvis = hvis >> 1;
	hlen = hlen >> 1;
	
	dprपूर्णांकk(KERN_DEBUG "hlen=%u hvis=%u\n", hlen, hvis);

	mt->पूर्णांकerlaced = 1;

	mt->HDisplay = hvis & ~7;
	mt->HSyncStart = mt->HDisplay + 8;
	mt->HSyncEnd = (hlen & ~7) - 8;
	mt->HTotal = hlen;

	अणु
		पूर्णांक upper;
		अचिन्हित पूर्णांक vtotal;
		अचिन्हित पूर्णांक vsyncend;
		अचिन्हित पूर्णांक vdisplay;
		
		vtotal = mt->VTotal;
		vsyncend = mt->VSyncEnd;
		vdisplay = mt->VDisplay;
		अगर (vtotal < outd->v_total) अणु
			अचिन्हित पूर्णांक yovr = outd->v_total - vtotal;
			
			vsyncend += yovr >> 1;
		पूर्ण अन्यथा अगर (vtotal > outd->v_total) अणु
			vdisplay = outd->v_total - 4;
			vsyncend = outd->v_total;
		पूर्ण
		upper = (outd->v_total - vsyncend) >> 1;	/* in field lines */
		r->regs[0x17] = outd->v_total / 4;
		r->regs[0x18] = outd->v_total & 3;
		r->regs[0x33] = upper - 1;	/* upper blanking */
		r->regs[0x82] = upper;		/* y sync poपूर्णांक */
		r->regs[0x83] = upper >> 8;
		
		mt->VDisplay = vdisplay;
		mt->VSyncStart = outd->v_total - 2;
		mt->VSyncEnd = outd->v_total;
		mt->VTotal = outd->v_total;
	पूर्ण
पूर्ण

अटल व्योम cve2_init_TVdata(पूर्णांक norm, काष्ठा mavenregs* data, स्थिर काष्ठा output_desc** outd) अणु
	अटल स्थिर काष्ठा output_desc paloutd = अणु
		.h_vis	   = 52148148,	// ps
		.h_f_porch =  1407407,	// ps
		.h_sync    =  4666667,	// ps
		.h_b_porch =  5777778,	// ps
		.chromasc  = 19042247534182ULL,	// 4433618.750 Hz
		.burst     =  2518518,	// ps
		.v_total   =      625,
	पूर्ण;
	अटल स्थिर काष्ठा output_desc ntscoutd = अणु
		.h_vis     = 52888889,	// ps
		.h_f_porch =  1333333,	// ps
		.h_sync    =  4666667,	// ps
		.h_b_porch =  4666667,	// ps
		.chromasc  = 15374030659475ULL,	// 3579545.454 Hz
		.burst     =  2418418,	// ps
		.v_total   =      525,	// lines
	पूर्ण;

	अटल स्थिर काष्ठा mavenregs palregs = अणु अणु
		0x2A, 0x09, 0x8A, 0xCB,	/* 00: chroma subcarrier */
		0x00,
		0x00,	/* test */
		0xF9,	/* modअगरied by code (F9 written...) */
		0x00,	/* ? not written */
		0x7E,	/* 08 */
		0x44,	/* 09 */
		0x9C,	/* 0A */
		0x2E,	/* 0B */
		0x21,	/* 0C */
		0x00,	/* ? not written */
//		0x3F, 0x03, /* 0E-0F */
		0x3C, 0x03,
		0x3C, 0x03, /* 10-11 */
		0x1A,	/* 12 */
		0x2A,	/* 13 */
		0x1C, 0x3D, 0x14, /* 14-16 */
		0x9C, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0xFE,	/* 1A */
		0x7E,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
//		0x89, 0x03, /* 1E-1F */
		0xAD, 0x03,
//		0x72,	/* 20 */
		0xA5,
		0x07,	/* 21 */
//		0x72,	/* 22 */
		0xA5,
		0x00,	/* 23 */
		0x00,	/* 24 */
		0x00,	/* 25 */
		0x08,	/* 26 */
		0x04,	/* 27 */
		0x00,	/* 28 */
		0x1A,	/* 29 */
		0x55, 0x01, /* 2A-2B */
		0x26,	/* 2C */
		0x07, 0x7E, /* 2D-2E */
		0x02, 0x54, /* 2F-30 */
		0xB0, 0x00, /* 31-32 */
		0x14,	/* 33 */
		0x49,	/* 34 */
		0x00,	/* 35 written multiple बार */
		0x00,	/* 36 not written */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x22,	/* 39 */
		0x02,	/* 3A */
		0x22,	/* 3B */
		0x3F, 0x03, /* 3C-3D */
		0x00,	/* 3E written multiple बार */
		0x00,	/* 3F not written */
	पूर्ण पूर्ण;
	अटल स्थिर काष्ठा mavenregs ntscregs = अणु अणु
		0x21, 0xF0, 0x7C, 0x1F,	/* 00: chroma subcarrier */
		0x00,
		0x00,	/* test */
		0xF9,	/* modअगरied by code (F9 written...) */
		0x00,	/* ? not written */
		0x7E,	/* 08 */
		0x43,	/* 09 */
		0x7E,	/* 0A */
		0x3D,	/* 0B */
		0x00,	/* 0C */
		0x00,	/* ? not written */
		0x41, 0x00, /* 0E-0F */
		0x3C, 0x00, /* 10-11 */
		0x17,	/* 12 */
		0x21,	/* 13 */
		0x1B, 0x1B, 0x24, /* 14-16 */
		0x83, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0x0F,	/* 1A */
		0x0F,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
		//0x89, 0x02, /* 1E-1F */
		0xC0, 0x02, /* 1E-1F */
		//0x5F,	/* 20 */
		0x9C,	/* 20 */
		0x04,	/* 21 */
		//0x5F,	/* 22 */
		0x9C,	/* 22 */
		0x01,	/* 23 */
		0x02,	/* 24 */
		0x00,	/* 25 */
		0x0A,	/* 26 */
		0x05,	/* 27 */
		0x00,	/* 28 */
		0x10,	/* 29 */
		0xFF, 0x03, /* 2A-2B */
		0x24,	/* 2C */
		0x0F, 0x78, /* 2D-2E */
		0x00, 0x00, /* 2F-30 */
		0xB2, 0x04, /* 31-32 */
		0x14,	/* 33 */
		0x02,	/* 34 */
		0x00,	/* 35 written multiple बार */
		0x00,	/* 36 not written */
		0xA3,	/* 37 */
		0xC8,	/* 38 */
		0x15,	/* 39 */
		0x05,	/* 3A */
		0x3B,	/* 3B */
		0x3C, 0x00, /* 3C-3D */
		0x00,	/* 3E written multiple बार */
		0x00,	/* never written */
	पूर्ण पूर्ण;

	अगर (norm == MATROXFB_OUTPUT_MODE_PAL) अणु
		*data = palregs;
		*outd = &paloutd;
	पूर्ण अन्यथा अणु
  		*data = ntscregs;
		*outd = &ntscoutd;
	पूर्ण
 	वापस;
पूर्ण

#घोषणा LR(x) cve2_set_reg(minfo, (x), m->regs[(x)])
अटल व्योम cve2_init_TV(काष्ठा matrox_fb_info *minfo,
			 स्थिर काष्ठा mavenregs *m)
अणु
	पूर्णांक i;

	LR(0x80);
	LR(0x82); LR(0x83);
	LR(0x84); LR(0x85);
	
	cve2_set_reg(minfo, 0x3E, 0x01);
	
	क्रम (i = 0; i < 0x3E; i++) अणु
		LR(i);
	पूर्ण
	cve2_set_reg(minfo, 0x3E, 0x00);
पूर्ण

अटल पूर्णांक matroxfb_g450_compute(व्योम* md, काष्ठा my_timming* mt) अणु
	काष्ठा matrox_fb_info *minfo = md;

	dprपूर्णांकk(KERN_DEBUG "Computing, mode=%u\n", minfo->outमाला_दो[1].mode);

	अगर (mt->crtc == MATROXFB_SRC_CRTC2 &&
	    minfo->outमाला_दो[1].mode != MATROXFB_OUTPUT_MODE_MONITOR) अणु
		स्थिर काष्ठा output_desc* outd;

		cve2_init_TVdata(minfo->outमाला_दो[1].mode, &minfo->hw.maven, &outd);
		अणु
			पूर्णांक blacklevel, whitelevel;
			g450_compute_bwlevel(minfo, &blacklevel, &whitelevel);
			minfo->hw.maven.regs[0x0E] = blacklevel >> 2;
			minfo->hw.maven.regs[0x0F] = blacklevel & 3;
			minfo->hw.maven.regs[0x1E] = whitelevel >> 2;
			minfo->hw.maven.regs[0x1F] = whitelevel & 3;

			minfo->hw.maven.regs[0x20] =
			minfo->hw.maven.regs[0x22] = minfo->altout.tvo_params.saturation;

			minfo->hw.maven.regs[0x25] = minfo->altout.tvo_params.hue;

			अगर (minfo->altout.tvo_params.testout) अणु
				minfo->hw.maven.regs[0x05] |= 0x02;
			पूर्ण
		पूर्ण
		computeRegs(minfo, &minfo->hw.maven, mt, outd);
	पूर्ण अन्यथा अगर (mt->mnp < 0) अणु
		/* We must program घड़ीs beक्रमe CRTC2, otherwise पूर्णांकerlaced mode
		   startup may fail */
		mt->mnp = matroxfb_g450_setclk(minfo, mt->pixघड़ी, (mt->crtc == MATROXFB_SRC_CRTC1) ? M_PIXEL_PLL_C : M_VIDEO_PLL);
		mt->pixघड़ी = g450_mnp2f(minfo, mt->mnp);
	पूर्ण
	dprपूर्णांकk(KERN_DEBUG "Pixclock = %u\n", mt->pixघड़ी);
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_g450_program(व्योम* md) अणु
	काष्ठा matrox_fb_info *minfo = md;
	
	अगर (minfo->outमाला_दो[1].mode != MATROXFB_OUTPUT_MODE_MONITOR) अणु
		cve2_init_TV(minfo, &minfo->hw.maven);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक matroxfb_g450_verअगरy_mode(व्योम* md, u_पूर्णांक32_t arg) अणु
	चयन (arg) अणु
		हाल MATROXFB_OUTPUT_MODE_PAL:
		हाल MATROXFB_OUTPUT_MODE_NTSC:
		हाल MATROXFB_OUTPUT_MODE_MONITOR:
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक g450_dvi_compute(व्योम* md, काष्ठा my_timming* mt) अणु
	काष्ठा matrox_fb_info *minfo = md;

	अगर (mt->mnp < 0) अणु
		mt->mnp = matroxfb_g450_setclk(minfo, mt->pixघड़ी, (mt->crtc == MATROXFB_SRC_CRTC1) ? M_PIXEL_PLL_C : M_VIDEO_PLL);
		mt->pixघड़ी = g450_mnp2f(minfo, mt->mnp);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा matrox_altout matroxfb_g450_altout = अणु
	.name		= "Secondary output",
	.compute	= matroxfb_g450_compute,
	.program	= matroxfb_g450_program,
	.verअगरymode	= matroxfb_g450_verअगरy_mode,
	.getqueryctrl	= g450_query_ctrl,
	.अ_लोtrl	= g450_get_ctrl,
	.setctrl	= g450_set_ctrl,
पूर्ण;

अटल काष्ठा matrox_altout matroxfb_g450_dvi = अणु
	.name		= "DVI output",
	.compute	= g450_dvi_compute,
पूर्ण;

व्योम matroxfb_g450_connect(काष्ठा matrox_fb_info *minfo)
अणु
	अगर (minfo->devflags.g450dac) अणु
		करोwn_ग_लिखो(&minfo->altout.lock);
		tvo_fill_शेषs(minfo);
		minfo->outमाला_दो[1].src = minfo->outमाला_दो[1].शेष_src;
		minfo->outमाला_दो[1].data = minfo;
		minfo->outमाला_दो[1].output = &matroxfb_g450_altout;
		minfo->outमाला_दो[1].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		minfo->outमाला_दो[2].src = minfo->outमाला_दो[2].शेष_src;
		minfo->outमाला_दो[2].data = minfo;
		minfo->outमाला_दो[2].output = &matroxfb_g450_dvi;
		minfo->outमाला_दो[2].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		up_ग_लिखो(&minfo->altout.lock);
	पूर्ण
पूर्ण

व्योम matroxfb_g450_shutकरोwn(काष्ठा matrox_fb_info *minfo)
अणु
	अगर (minfo->devflags.g450dac) अणु
		करोwn_ग_लिखो(&minfo->altout.lock);
		minfo->outमाला_दो[1].src = MATROXFB_SRC_NONE;
		minfo->outमाला_दो[1].output = शून्य;
		minfo->outमाला_दो[1].data = शून्य;
		minfo->outमाला_दो[1].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		minfo->outमाला_दो[2].src = MATROXFB_SRC_NONE;
		minfo->outमाला_दो[2].output = शून्य;
		minfo->outमाला_दो[2].data = शून्य;
		minfo->outमाला_दो[2].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		up_ग_लिखो(&minfo->altout.lock);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(matroxfb_g450_connect);
EXPORT_SYMBOL(matroxfb_g450_shutकरोwn);

MODULE_AUTHOR("(c) 2000-2002 Petr Vandrovec <vandrove@vc.cvut.cz>");
MODULE_DESCRIPTION("Matrox G450/G550 output driver");
MODULE_LICENSE("GPL");
