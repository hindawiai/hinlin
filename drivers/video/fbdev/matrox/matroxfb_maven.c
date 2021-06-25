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

#समावेश "matroxfb_maven.h"
#समावेश "matroxfb_misc.h"
#समावेश "matroxfb_DAC1064.h"
#समावेश <linux/i2c.h>
#समावेश <linux/matroxfb.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>

#घोषणा MGATVO_B	1
#घोषणा MGATVO_C	2

अटल स्थिर काष्ठा maven_gamma अणु
  अचिन्हित अक्षर reg83;
  अचिन्हित अक्षर reg84;
  अचिन्हित अक्षर reg85;
  अचिन्हित अक्षर reg86;
  अचिन्हित अक्षर reg87;
  अचिन्हित अक्षर reg88;
  अचिन्हित अक्षर reg89;
  अचिन्हित अक्षर reg8a;
  अचिन्हित अक्षर reg8b;
पूर्ण maven_gamma[] = अणु
  अणु 131, 57, 223, 15, 117, 212, 251, 91, 156पूर्ण,
  अणु 133, 61, 128, 63, 180, 147, 195, 100, 180पूर्ण,
  अणु 131, 19, 63, 31, 50, 66, 171, 64, 176पूर्ण,
  अणु 0, 0, 0, 31, 16, 16, 16, 100, 200पूर्ण,
  अणु 8, 23, 47, 73, 147, 244, 220, 80, 195पूर्ण,
  अणु 22, 43, 64, 80, 147, 115, 58, 85, 168पूर्ण,
  अणु 34, 60, 80, 214, 147, 212, 188, 85, 167पूर्ण,
  अणु 45, 77, 96, 216, 147, 99, 91, 85, 159पूर्ण,
  अणु 56, 76, 112, 107, 147, 212, 148, 64, 144पूर्ण,
  अणु 65, 91, 128, 137, 147, 196, 17, 69, 148पूर्ण,
  अणु 72, 104, 136, 138, 147, 180, 245, 73, 147पूर्ण,
  अणु 87, 116, 143, 126, 16, 83, 229, 77, 144पूर्ण,
  अणु 95, 119, 152, 254, 244, 83, 221, 77, 151पूर्ण,
  अणु 100, 129, 159, 156, 244, 148, 197, 77, 160पूर्ण,
  अणु 105, 141, 167, 247, 244, 132, 181, 84, 166पूर्ण,
  अणु 105, 147, 168, 247, 244, 245, 181, 90, 170पूर्ण,
  अणु 120, 153, 175, 248, 212, 229, 165, 90, 180पूर्ण,
  अणु 119, 156, 176, 248, 244, 229, 84, 74, 160पूर्ण,
  अणु 119, 158, 183, 248, 244, 229, 149, 78, 165पूर्ण
पूर्ण;

/* Definition of the various controls */
काष्ठा mctl अणु
	काष्ठा v4l2_queryctrl desc;
	माप_प्रकार control;
पूर्ण;

#घोषणा BLMIN	0x0FF
#घोषणा WLMAX	0x3FF

अटल स्थिर काष्ठा mctl maven_controls[] =
अणु	अणु अणु V4L2_CID_BRIGHTNESS, V4L2_CTRL_TYPE_INTEGER,
	  "brightness",
	  0, WLMAX - BLMIN, 1, 379 - BLMIN, 
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.brightness) पूर्ण,
	अणु अणु V4L2_CID_CONTRAST, V4L2_CTRL_TYPE_INTEGER,
	  "contrast",
	  0, 1023, 1, 127,
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.contrast) पूर्ण,
	अणु अणु V4L2_CID_SATURATION, V4L2_CTRL_TYPE_INTEGER,
	  "saturation",
	  0, 255, 1, 155,
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.saturation) पूर्ण,
	अणु अणु V4L2_CID_HUE, V4L2_CTRL_TYPE_INTEGER,
	  "hue",
	  0, 255, 1, 0,
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.hue) पूर्ण,
	अणु अणु V4L2_CID_GAMMA, V4L2_CTRL_TYPE_INTEGER,
	  "gamma",
	  0, ARRAY_SIZE(maven_gamma) - 1, 1, 3,
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.gamma) पूर्ण,
	अणु अणु MATROXFB_CID_TESTOUT, V4L2_CTRL_TYPE_BOOLEAN,
	  "test output",
	  0, 1, 1, 0,
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.testout) पूर्ण,
	अणु अणु MATROXFB_CID_DEFLICKER, V4L2_CTRL_TYPE_INTEGER,
	  "deflicker mode",
	  0, 2, 1, 0,
	  0,
	पूर्ण, दुरत्व(काष्ठा matrox_fb_info, altout.tvo_params.deflicker) पूर्ण,

पूर्ण;

#घोषणा MAVCTRLS ARRAY_SIZE(maven_controls)

/* Return: positive number: id found
           -EINVAL:         id not found, वापस failure
	   -ENOENT:         id not found, create fake disabled control */
अटल पूर्णांक get_ctrl_id(__u32 v4l2_id) अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAVCTRLS; i++) अणु
		अगर (v4l2_id < maven_controls[i].desc.id) अणु
			अगर (maven_controls[i].desc.id == 0x08000000) अणु
				वापस -EINVAL;
			पूर्ण
			वापस -ENOENT;
		पूर्ण
		अगर (v4l2_id == maven_controls[i].desc.id) अणु
			वापस i;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

काष्ठा maven_data अणु
	काष्ठा matrox_fb_info*		primary_head;
	काष्ठा i2c_client		*client;
	पूर्णांक				version;
पूर्ण;

अटल पूर्णांक* get_ctrl_ptr(काष्ठा maven_data* md, पूर्णांक idx) अणु
	वापस (पूर्णांक*)((अक्षर*)(md->primary_head) + maven_controls[idx].control);
पूर्ण

अटल पूर्णांक maven_get_reg(काष्ठा i2c_client* c, अक्षर reg) अणु
	अक्षर dst;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = c->addr,
			.flags = I2C_M_REV_सूची_ADDR,
			.len = माप(reg),
			.buf = &reg
		पूर्ण,
		अणु
			.addr = c->addr,
			.flags = I2C_M_RD | I2C_M_NOSTART,
			.len = माप(dst),
			.buf = &dst
		पूर्ण
	पूर्ण;
	s32 err;

	err = i2c_transfer(c->adapter, msgs, 2);
	अगर (err < 0)
		prपूर्णांकk(KERN_INFO "ReadReg(%d) failed\n", reg);
	वापस dst & 0xFF;
पूर्ण

अटल पूर्णांक maven_set_reg(काष्ठा i2c_client* c, पूर्णांक reg, पूर्णांक val) अणु
	s32 err;

	err = i2c_smbus_ग_लिखो_byte_data(c, reg, val);
	अगर (err)
		prपूर्णांकk(KERN_INFO "WriteReg(%d) failed\n", reg);
	वापस err;
पूर्ण

अटल पूर्णांक maven_set_reg_pair(काष्ठा i2c_client* c, पूर्णांक reg, पूर्णांक val) अणु
	s32 err;

	err = i2c_smbus_ग_लिखो_word_data(c, reg, val);
	अगर (err)
		prपूर्णांकk(KERN_INFO "WriteRegPair(%d) failed\n", reg);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा matrox_pll_features maven_pll = अणु
	50000,
	27000,
	4, 127,
	2, 31,
	3
पूर्ण;

काष्ठा matrox_pll_features2 अणु
	अचिन्हित पूर्णांक	vco_freq_min;
	अचिन्हित पूर्णांक	vco_freq_max;
	अचिन्हित पूर्णांक	feed_भाग_min;
	अचिन्हित पूर्णांक	feed_भाग_max;
	अचिन्हित पूर्णांक	in_भाग_min;
	अचिन्हित पूर्णांक	in_भाग_max;
	अचिन्हित पूर्णांक	post_shअगरt_max;
पूर्ण;

काष्ठा matrox_pll_ctl अणु
	अचिन्हित पूर्णांक	ref_freq;
	अचिन्हित पूर्णांक	den;
पूर्ण;

अटल स्थिर काष्ठा matrox_pll_features2 maven1000_pll = अणु
	.vco_freq_min = 50000000,
	.vco_freq_max = 300000000,
	.feed_भाग_min = 5,
	.feed_भाग_max = 128,
	.in_भाग_min = 3,
	.in_भाग_max = 32,
	.post_shअगरt_max = 3
पूर्ण;

अटल स्थिर काष्ठा matrox_pll_ctl maven_PAL = अणु
	.ref_freq = 540000,
	.den = 50
पूर्ण;

अटल स्थिर काष्ठा matrox_pll_ctl maven_NTSC = अणु
	.ref_freq = 450450,	/* 27027000/60 == 27000000/59.94005994 */
	.den = 60
पूर्ण;

अटल पूर्णांक matroxfb_PLL_mavenघड़ी(स्थिर काष्ठा matrox_pll_features2* pll,
		स्थिर काष्ठा matrox_pll_ctl* ctl,
		अचिन्हित पूर्णांक htotal, अचिन्हित पूर्णांक vtotal,
		अचिन्हित पूर्णांक* in, अचिन्हित पूर्णांक* feed, अचिन्हित पूर्णांक* post,
		अचिन्हित पूर्णांक* h2) अणु
	अचिन्हित पूर्णांक besth2 = 0;
	अचिन्हित पूर्णांक fxtal = ctl->ref_freq;
	अचिन्हित पूर्णांक fmin = pll->vco_freq_min / ctl->den;
	अचिन्हित पूर्णांक fwant;
	अचिन्हित पूर्णांक p;
	अचिन्हित पूर्णांक scrlen;
	अचिन्हित पूर्णांक fmax;

	DBG(__func__)

	scrlen = htotal * (vtotal - 1);
	fwant = htotal * vtotal;
	fmax = pll->vco_freq_max / ctl->den;

	dprपूर्णांकk(KERN_DEBUG "want: %u, xtal: %u, h: %u, v: %u, fmax: %u\n",
		fwant, fxtal, htotal, vtotal, fmax);
	क्रम (p = 1; p <= pll->post_shअगरt_max; p++) अणु
		अगर (fwant * 2 > fmax)
			अवरोध;
		fwant *= 2;
	पूर्ण
	अगर (fwant > fmax)
		वापस 0;
	क्रम (; p-- > 0; fwant >>= 1) अणु
		अचिन्हित पूर्णांक m;

		अगर (fwant < fmin) अवरोध;
		क्रम (m = pll->in_भाग_min; m <= pll->in_भाग_max; m++) अणु
			अचिन्हित पूर्णांक n;
			अचिन्हित पूर्णांक dvd;
			अचिन्हित पूर्णांक ln;

			n = (fwant * m) / fxtal;
			अगर (n < pll->feed_भाग_min)
				जारी;
			अगर (n > pll->feed_भाग_max)
				अवरोध;

			ln = fxtal * n;
			dvd = m << p;

			अगर (ln % dvd)
				जारी;
			ln = ln / dvd;

			अगर (ln < scrlen + 2)
				जारी;
			ln = ln - scrlen;
			अगर (ln > htotal)
				जारी;
			dprपूर्णांकk(KERN_DEBUG "Match: %u / %u / %u / %u\n", n, m, p, ln);
			अगर (ln > besth2) अणु
				dprपूर्णांकk(KERN_DEBUG "Better...\n");
				*h2 = besth2 = ln;
				*post = p;
				*in = m;
				*feed = n;
			पूर्ण
		पूर्ण
	पूर्ण

	/* अगर h2/post/in/feed have not been asचिन्हित, वापस zero (error) */
	अगर (besth2 < 2)
		वापस 0;

	dprपूर्णांकk(KERN_ERR "clk: %02X %02X %02X %d %d\n", *in, *feed, *post, fxtal, fwant);
	वापस fxtal * (*feed) / (*in) * ctl->den;
पूर्ण

अटल पूर्णांक matroxfb_mavenघड़ी(स्थिर काष्ठा matrox_pll_ctl *ctl,
		अचिन्हित पूर्णांक htotal, अचिन्हित पूर्णांक vtotal,
		अचिन्हित पूर्णांक* in, अचिन्हित पूर्णांक* feed, अचिन्हित पूर्णांक* post,
		अचिन्हित पूर्णांक* htotal2) अणु
	अचिन्हित पूर्णांक fvco;
	अचिन्हित पूर्णांक p;

	fvco = matroxfb_PLL_mavenघड़ी(&maven1000_pll, ctl, htotal, vtotal, in, feed, &p, htotal2);
	अगर (!fvco)
		वापस -EINVAL;
	p = (1 << p) - 1;
	अगर (fvco <= 100000000)
		;
	अन्यथा अगर (fvco <= 140000000)
		p |= 0x08;
	अन्यथा अगर (fvco <= 180000000)
		p |= 0x10;
	अन्यथा
		p |= 0x18;
	*post = p;
	वापस 0;
पूर्ण

अटल व्योम DAC1064_calcघड़ी(अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक fmax,
		अचिन्हित पूर्णांक* in, अचिन्हित पूर्णांक* feed, अचिन्हित पूर्णांक* post) अणु
	अचिन्हित पूर्णांक fvco;
	अचिन्हित पूर्णांक p;

	fvco = matroxfb_PLL_calcघड़ी(&maven_pll, freq, fmax, in, feed, &p);
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
	वापस;
पूर्ण

अटल अचिन्हित अक्षर maven_compute_deflicker (स्थिर काष्ठा maven_data* md) अणु
	अचिन्हित अक्षर df;
	
	df = (md->version == MGATVO_B?0x40:0x00);
	चयन (md->primary_head->altout.tvo_params.deflicker) अणु
		हाल 0:
/*			df |= 0x00; */
			अवरोध;
		हाल 1:
			df |= 0xB1;
			अवरोध;
		हाल 2:
			df |= 0xA2;
			अवरोध;
	पूर्ण
	वापस df;
पूर्ण

अटल व्योम maven_compute_bwlevel (स्थिर काष्ठा maven_data* md,
				   पूर्णांक *bl, पूर्णांक *wl) अणु
	स्थिर पूर्णांक b = md->primary_head->altout.tvo_params.brightness + BLMIN;
	स्थिर पूर्णांक c = md->primary_head->altout.tvo_params.contrast;

	*bl = max(b - c, BLMIN);
	*wl = min(b + c, WLMAX);
पूर्ण

अटल स्थिर काष्ठा maven_gamma* maven_compute_gamma (स्थिर काष्ठा maven_data* md) अणु
 	वापस maven_gamma + md->primary_head->altout.tvo_params.gamma;
पूर्ण


अटल व्योम maven_init_TVdata(स्थिर काष्ठा maven_data* md, काष्ठा mavenregs* data) अणु
	अटल काष्ठा mavenregs palregs = अणु अणु
		0x2A, 0x09, 0x8A, 0xCB,	/* 00: chroma subcarrier */
		0x00,
		0x00,	/* ? not written */
		0x00,	/* modअगरied by code (F9 written...) */
		0x00,	/* ? not written */
		0x7E,	/* 08 */
		0x44,	/* 09 */
		0x9C,	/* 0A */
		0x2E,	/* 0B */
		0x21,	/* 0C */
		0x00,	/* ? not written */
		0x3F, 0x03, /* 0E-0F */
		0x3F, 0x03, /* 10-11 */
		0x1A,	/* 12 */
		0x2A,	/* 13 */
		0x1C, 0x3D, 0x14, /* 14-16 */
		0x9C, 0x01, /* 17-18 */
		0x00,	/* 19 */
		0xFE,	/* 1A */
		0x7E,	/* 1B */
		0x60,	/* 1C */
		0x05,	/* 1D */
		0x89, 0x03, /* 1E-1F */
		0x72,	/* 20 */
		0x07,	/* 21 */
		0x72,	/* 22 */
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
	पूर्ण, MATROXFB_OUTPUT_MODE_PAL, 625, 50 पूर्ण;
	अटल काष्ठा mavenregs ntscregs = अणु अणु
		0x21, 0xF0, 0x7C, 0x1F,	/* 00: chroma subcarrier */
		0x00,
		0x00,	/* ? not written */
		0x00,	/* modअगरied by code (F9 written...) */
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
		0x89, 0x02, /* 1E-1F */
		0x5F,	/* 20 */
		0x04,	/* 21 */
		0x5F,	/* 22 */
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
	पूर्ण, MATROXFB_OUTPUT_MODE_NTSC, 525, 60 पूर्ण;
	काष्ठा matrox_fb_info *minfo = md->primary_head;

	अगर (minfo->outमाला_दो[1].mode == MATROXFB_OUTPUT_MODE_PAL)
		*data = palregs;
	अन्यथा
		*data = ntscregs;

	/* Set deflicker */
	data->regs[0x93] = maven_compute_deflicker(md);
 
	/* set gamma */
	अणु
		स्थिर काष्ठा maven_gamma* g;
		g = maven_compute_gamma(md);
		data->regs[0x83] = g->reg83;
		data->regs[0x84] = g->reg84;
		data->regs[0x85] = g->reg85;
		data->regs[0x86] = g->reg86;
		data->regs[0x87] = g->reg87;
		data->regs[0x88] = g->reg88;
		data->regs[0x89] = g->reg89;
		data->regs[0x8A] = g->reg8a;
		data->regs[0x8B] = g->reg8b;
	पूर्ण
 
	/* Set contrast / brightness */
	अणु
		पूर्णांक bl, wl;
		maven_compute_bwlevel (md, &bl, &wl);
		data->regs[0x0e] = bl >> 2;
		data->regs[0x0f] = bl & 3;
		data->regs[0x1e] = wl >> 2;
		data->regs[0x1f] = wl & 3;
	पूर्ण

	/* Set saturation */
	अणु
		data->regs[0x20] =
		data->regs[0x22] = minfo->altout.tvo_params.saturation;
	पूर्ण
 
	/* Set HUE */
	data->regs[0x25] = minfo->altout.tvo_params.hue;
	वापस;
पूर्ण

#घोषणा LR(x) maven_set_reg(c, (x), m->regs[(x)])
#घोषणा LRP(x) maven_set_reg_pair(c, (x), m->regs[(x)] | (m->regs[(x)+1] << 8))
अटल व्योम maven_init_TV(काष्ठा i2c_client* c, स्थिर काष्ठा mavenregs* m) अणु
	पूर्णांक val;


	maven_set_reg(c, 0x3E, 0x01);
	maven_get_reg(c, 0x82);	/* fetch oscillator state? */
	maven_set_reg(c, 0x8C, 0x00);
	maven_get_reg(c, 0x94);	/* get 0x82 */
	maven_set_reg(c, 0x94, 0xA2);
	/* xmiscctrl */

	maven_set_reg_pair(c, 0x8E, 0x1EFF);
	maven_set_reg(c, 0xC6, 0x01);

	/* हटाओd code... */

	maven_get_reg(c, 0x06);
	maven_set_reg(c, 0x06, 0xF9);	/* or पढ़ो |= 0xF0 ? */

	/* हटाओd code here... */

	/* real code begins here? */
	/* chroma subcarrier */
	LR(0x00); LR(0x01); LR(0x02); LR(0x03);

	LR(0x04);

	LR(0x2C);
	LR(0x08);
	LR(0x0A);
	LR(0x09);
	LR(0x29);
	LRP(0x31);
	LRP(0x17);
	LR(0x0B);
	LR(0x0C);
	अगर (m->mode == MATROXFB_OUTPUT_MODE_PAL) अणु
		maven_set_reg(c, 0x35, 0x10); /* ... */
	पूर्ण अन्यथा अणु
		maven_set_reg(c, 0x35, 0x0F); /* ... */
	पूर्ण

	LRP(0x10);

	LRP(0x0E);
	LRP(0x1E);

	LR(0x20);	/* saturation #1 */
	LR(0x22);	/* saturation #2 */
	LR(0x25);	/* hue */
	LR(0x34);
	LR(0x33);
	LR(0x19);
	LR(0x12);
	LR(0x3B);
	LR(0x13);
	LR(0x39);
	LR(0x1D);
	LR(0x3A);
	LR(0x24);
	LR(0x14);
	LR(0x15);
	LR(0x16);
	LRP(0x2D);
	LRP(0x2F);
	LR(0x1A);
	LR(0x1B);
	LR(0x1C);
	LR(0x23);
	LR(0x26);
	LR(0x28);
	LR(0x27);
	LR(0x21);
	LRP(0x2A);
	अगर (m->mode == MATROXFB_OUTPUT_MODE_PAL)
		maven_set_reg(c, 0x35, 0x1D);	/* ... */
	अन्यथा
		maven_set_reg(c, 0x35, 0x1C);

	LRP(0x3C);
	LR(0x37);
	LR(0x38);
	maven_set_reg(c, 0xB3, 0x01);

	maven_get_reg(c, 0xB0);	/* पढ़ो 0x80 */
	maven_set_reg(c, 0xB0, 0x08);	/* ugh... */
	maven_get_reg(c, 0xB9);	/* पढ़ो 0x7C */
	maven_set_reg(c, 0xB9, 0x78);
	maven_get_reg(c, 0xBF);	/* पढ़ो 0x00 */
	maven_set_reg(c, 0xBF, 0x02);
	maven_get_reg(c, 0x94);	/* पढ़ो 0x82 */
	maven_set_reg(c, 0x94, 0xB3);

	LR(0x80); /* 04 1A 91 or 05 21 91 */
	LR(0x81);
	LR(0x82);

	maven_set_reg(c, 0x8C, 0x20);
	maven_get_reg(c, 0x8D);
	maven_set_reg(c, 0x8D, 0x10);

	LR(0x90); /* 4D 50 52 or 4E 05 45 */
	LR(0x91);
	LR(0x92);

	LRP(0x9A); /* 0049 or 004F */
	LRP(0x9C); /* 0004 or 0004 */
	LRP(0x9E); /* 0458 or 045E */
	LRP(0xA0); /* 05DA or 051B */
	LRP(0xA2); /* 00CC or 00CF */
	LRP(0xA4); /* 007D or 007F */
	LRP(0xA6); /* 007C or 007E */
	LRP(0xA8); /* 03CB or 03CE */
	LRP(0x98); /* 0000 or 0000 */
	LRP(0xAE); /* 0044 or 003A */
	LRP(0x96); /* 05DA or 051B */
	LRP(0xAA); /* 04BC or 046A */
	LRP(0xAC); /* 004D or 004E */

	LR(0xBE);
	LR(0xC2);

	maven_get_reg(c, 0x8D);
	maven_set_reg(c, 0x8D, 0x04);

	LR(0x20);	/* saturation #1 */
	LR(0x22);	/* saturation #2 */
	LR(0x93);	/* whoops */
	LR(0x20);	/* oh, saturation #1 again */
	LR(0x22);	/* oh, saturation #2 again */
	LR(0x25);	/* hue */
	LRP(0x0E);
	LRP(0x1E);
	LRP(0x0E);	/* problems with memory? */
	LRP(0x1E);	/* yes, matrox must have problems in memory area... */

	/* load gamma correction stuff */
	LR(0x83);
	LR(0x84);
	LR(0x85);
	LR(0x86);
	LR(0x87);
	LR(0x88);
	LR(0x89);
	LR(0x8A);
	LR(0x8B);

	val = maven_get_reg(c, 0x8D);
	val &= 0x14;			/* 0x10 or anything ored with it */
	maven_set_reg(c, 0x8D, val);

	LR(0x33);
	LR(0x19);
	LR(0x12);
	LR(0x3B);
	LR(0x13);
	LR(0x39);
	LR(0x1D);
	LR(0x3A);
	LR(0x24);
	LR(0x14);
	LR(0x15);
	LR(0x16);
	LRP(0x2D);
	LRP(0x2F);
	LR(0x1A);
	LR(0x1B);
	LR(0x1C);
	LR(0x23);
	LR(0x26);
	LR(0x28);
	LR(0x27);
	LR(0x21);
	LRP(0x2A);
	अगर (m->mode == MATROXFB_OUTPUT_MODE_PAL)
		maven_set_reg(c, 0x35, 0x1D);
	अन्यथा
		maven_set_reg(c, 0x35, 0x1C);
	LRP(0x3C);
	LR(0x37);
	LR(0x38);

	maven_get_reg(c, 0xB0);
	LR(0xB0);	/* output mode */
	LR(0x90);
	LR(0xBE);
	LR(0xC2);

	LRP(0x9A);
	LRP(0xA2);
	LRP(0x9E);
	LRP(0xA6);
	LRP(0xAA);
	LRP(0xAC);
	maven_set_reg(c, 0x3E, 0x00);
	maven_set_reg(c, 0x95, 0x20);
पूर्ण

अटल पूर्णांक maven_find_exact_घड़ीs(अचिन्हित पूर्णांक ht, अचिन्हित पूर्णांक vt,
		काष्ठा mavenregs* m) अणु
	अचिन्हित पूर्णांक x;
	अचिन्हित पूर्णांक err = ~0;

	/* 1:1 */
	m->regs[0x80] = 0x0F;
	m->regs[0x81] = 0x07;
	m->regs[0x82] = 0x81;

	क्रम (x = 0; x < 8; x++) अणु
		अचिन्हित पूर्णांक c;
		अचिन्हित पूर्णांक a, b,
			     h2;
		अचिन्हित पूर्णांक h = ht + 2 + x;

		अगर (!matroxfb_mavenघड़ी((m->mode == MATROXFB_OUTPUT_MODE_PAL) ? &maven_PAL : &maven_NTSC, h, vt, &a, &b, &c, &h2)) अणु
			अचिन्हित पूर्णांक dअगरf = h - h2;

			अगर (dअगरf < err) अणु
				err = dअगरf;
				m->regs[0x80] = a - 1;
				m->regs[0x81] = b - 1;
				m->regs[0x82] = c | 0x80;
				m->hcorr = h2 - 2;
				m->htotal = h - 2;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err != ~0U;
पूर्ण

अटल अंतरभूत पूर्णांक maven_compute_timming(काष्ठा maven_data* md,
		काष्ठा my_timming* mt,
		काष्ठा mavenregs* m) अणु
	अचिन्हित पूर्णांक पंचांगpi;
	अचिन्हित पूर्णांक a, bv, c;
	काष्ठा matrox_fb_info *minfo = md->primary_head;

	m->mode = minfo->outमाला_दो[1].mode;
	अगर (m->mode != MATROXFB_OUTPUT_MODE_MONITOR) अणु
		अचिन्हित पूर्णांक lmargin;
		अचिन्हित पूर्णांक umargin;
		अचिन्हित पूर्णांक vslen;
		अचिन्हित पूर्णांक hcrt;
		अचिन्हित पूर्णांक slen;

		maven_init_TVdata(md, m);

		अगर (maven_find_exact_घड़ीs(mt->HTotal, mt->VTotal, m) == 0)
			वापस -EINVAL;

		lmargin = mt->HTotal - mt->HSyncEnd;
		slen = mt->HSyncEnd - mt->HSyncStart;
		hcrt = mt->HTotal - slen - mt->delay;
		umargin = mt->VTotal - mt->VSyncEnd;
		vslen = mt->VSyncEnd - mt->VSyncStart;

		अगर (m->hcorr < mt->HTotal)
			hcrt += m->hcorr;
		अगर (hcrt > mt->HTotal)
			hcrt -= mt->HTotal;
		अगर (hcrt + 2 > mt->HTotal)
			hcrt = 0;	/* or issue warning? */

		/* last (first? middle?) line in picture can have dअगरferent length */
		/* hlen - 2 */
		m->regs[0x96] = m->hcorr;
		m->regs[0x97] = m->hcorr >> 8;
		/* ... */
		m->regs[0x98] = 0x00; m->regs[0x99] = 0x00;
		/* hblanking end */
		m->regs[0x9A] = lmargin;	/* 100% */
		m->regs[0x9B] = lmargin >> 8;	/* 100% */
		/* who knows */
		m->regs[0x9C] = 0x04;
		m->regs[0x9D] = 0x00;
		/* htotal - 2 */
		m->regs[0xA0] = m->htotal;
		m->regs[0xA1] = m->htotal >> 8;
		/* vblanking end */
		m->regs[0xA2] = mt->VTotal - mt->VSyncStart - 1;	/* stop vblanking */
		m->regs[0xA3] = (mt->VTotal - mt->VSyncStart - 1) >> 8;
		/* something end... [A6]+1..[A8] */
		अगर (md->version == MGATVO_B) अणु
			m->regs[0xA4] = 0x04;
			m->regs[0xA5] = 0x00;
		पूर्ण अन्यथा अणु
			m->regs[0xA4] = 0x01;
			m->regs[0xA5] = 0x00;
		पूर्ण
		/* something start... 0..[A4]-1 */
		m->regs[0xA6] = 0x00;
		m->regs[0xA7] = 0x00;
		/* vertical line count - 1 */
		m->regs[0xA8] = mt->VTotal - 1;
		m->regs[0xA9] = (mt->VTotal - 1) >> 8;
		/* horizontal vidrst pos */
		m->regs[0xAA] = hcrt;		/* 0 <= hcrt <= htotal - 2 */
		m->regs[0xAB] = hcrt >> 8;
		/* vertical vidrst pos */
		m->regs[0xAC] = mt->VTotal - 2;
		m->regs[0xAD] = (mt->VTotal - 2) >> 8;
		/* moves picture up/करोwn and so on... */
		m->regs[0xAE] = 0x01; /* Fix this... 0..VTotal */
		m->regs[0xAF] = 0x00;
		अणु
			पूर्णांक hdec;
			पूर्णांक hlen;
			अचिन्हित पूर्णांक ibmin = 4 + lmargin + mt->HDisplay;
			अचिन्हित पूर्णांक ib;
			पूर्णांक i;

			/* Verअगरy! */
			/* Where 94208 came from? */
			अगर (mt->HTotal)
				hdec = 94208 / (mt->HTotal);
			अन्यथा
				hdec = 0x81;
			अगर (hdec > 0x81)
				hdec = 0x81;
			अगर (hdec < 0x41)
				hdec = 0x41;
			hdec--;
			hlen = 98304 - 128 - ((lmargin + mt->HDisplay - 8) * hdec);
			अगर (hlen < 0)
				hlen = 0;
			hlen = hlen >> 8;
			अगर (hlen > 0xFF)
				hlen = 0xFF;
			/* Now we have to compute input buffer length.
			   If you want any picture, it must be between
			     4 + lmargin + xres
			   and
			     94208 / hdec
			   If you want perfect picture even on the top
			   of screen, it must be also
			     0x3C0000 * i / hdec + Q - R / hdec
			   where
			        R      Qmin   Qmax
			     0x07000   0x5AE  0x5BF
			     0x08000   0x5CF  0x5FF
			     0x0C000   0x653  0x67F
			     0x10000   0x6F8  0x6FF
			 */
			i = 1;
			करो अणु
				ib = ((0x3C0000 * i - 0x8000)/ hdec + 0x05E7) >> 8;
				i++;
			पूर्ण जबतक (ib < ibmin);
			अगर (ib >= m->htotal + 2) अणु
				ib = ibmin;
			पूर्ण

			m->regs[0x90] = hdec;	/* < 0x40 || > 0x80 is bad... 0x80 is questionable */
			m->regs[0xC2] = hlen;
			/* 'valid' input line length */
			m->regs[0x9E] = ib;
			m->regs[0x9F] = ib >> 8;
		पूर्ण
		अणु
			पूर्णांक vdec;
			पूर्णांक vlen;

#घोषणा MATROX_USE64BIT_DIVIDE
			अगर (mt->VTotal) अणु
#अगर_घोषित MATROX_USE64BIT_DIVIDE
				u64 f1;
				u32 a;
				u32 b;

				a = m->vlines * (m->htotal + 2);
				b = (mt->VTotal - 1) * (m->htotal + 2) + m->hcorr + 2;

				f1 = ((u64)a) << 15;	/* *32768 */
				करो_भाग(f1, b);
				vdec = f1;
#अन्यथा
				vdec = m->vlines * 32768 / mt->VTotal;
#पूर्ण_अगर
			पूर्ण अन्यथा
				vdec = 0x8000;
			अगर (vdec > 0x8000)
				vdec = 0x8000;
			vlen = (vslen + umargin + mt->VDisplay) * vdec;
			vlen = (vlen >> 16) - 146; /* FIXME: 146?! */
			अगर (vlen < 0)
				vlen = 0;
			अगर (vlen > 0xFF)
				vlen = 0xFF;
			vdec--;
			m->regs[0x91] = vdec;
			m->regs[0x92] = vdec >> 8;
			m->regs[0xBE] = vlen;
		पूर्ण
		m->regs[0xB0] = 0x08;	/* output: SVideo/Composite */
		वापस 0;
	पूर्ण

	DAC1064_calcघड़ी(mt->pixघड़ी, 450000, &a, &bv, &c);
	m->regs[0x80] = a;
	m->regs[0x81] = bv;
	m->regs[0x82] = c | 0x80;

	m->regs[0xB3] = 0x01;
	m->regs[0x94] = 0xB2;

	/* htotal... */
	m->regs[0x96] = mt->HTotal;
	m->regs[0x97] = mt->HTotal >> 8;
	/* ?? */
	m->regs[0x98] = 0x00;
	m->regs[0x99] = 0x00;
	/* hsync len */
	पंचांगpi = mt->HSyncEnd - mt->HSyncStart;
	m->regs[0x9A] = पंचांगpi;
	m->regs[0x9B] = पंचांगpi >> 8;
	/* hblank end */
	पंचांगpi = mt->HTotal - mt->HSyncStart;
	m->regs[0x9C] = पंचांगpi;
	m->regs[0x9D] = पंचांगpi >> 8;
	/* hblank start */
	पंचांगpi += mt->HDisplay;
	m->regs[0x9E] = पंचांगpi;
	m->regs[0x9F] = पंचांगpi >> 8;
	/* htotal + 1 */
	पंचांगpi = mt->HTotal + 1;
	m->regs[0xA0] = पंचांगpi;
	m->regs[0xA1] = पंचांगpi >> 8;
	/* vsync?! */
	पंचांगpi = mt->VSyncEnd - mt->VSyncStart - 1;
	m->regs[0xA2] = पंचांगpi;
	m->regs[0xA3] = पंचांगpi >> 8;
	/* ignored? */
	पंचांगpi = mt->VTotal - mt->VSyncStart;
	m->regs[0xA4] = पंचांगpi;
	m->regs[0xA5] = पंचांगpi >> 8;
	/* ignored? */
	पंचांगpi = mt->VTotal - 1;
	m->regs[0xA6] = पंचांगpi;
	m->regs[0xA7] = पंचांगpi >> 8;
	/* vtotal - 1 */
	m->regs[0xA8] = पंचांगpi;
	m->regs[0xA9] = पंचांगpi >> 8;
	/* hor vidrst */
	पंचांगpi = mt->HTotal - mt->delay;
	m->regs[0xAA] = पंचांगpi;
	m->regs[0xAB] = पंचांगpi >> 8;
	/* vert vidrst */
	पंचांगpi = mt->VTotal - 2;
	m->regs[0xAC] = पंचांगpi;
	m->regs[0xAD] = पंचांगpi >> 8;
	/* ignored? */
	m->regs[0xAE] = 0x00;
	m->regs[0xAF] = 0x00;

	m->regs[0xB0] = 0x03;	/* output: monitor */
	m->regs[0xB1] = 0xA0;	/* ??? */
	m->regs[0x8C] = 0x20;	/* must be set... */
	m->regs[0x8D] = 0x04;	/* शेषs to 0x10: test संकेत */
	m->regs[0xB9] = 0x1A;	/* शेषs to 0x2C: too bright */
	m->regs[0xBF] = 0x22;	/* makes picture stable */

	वापस 0;
पूर्ण

अटल पूर्णांक maven_program_timming(काष्ठा maven_data* md,
		स्थिर काष्ठा mavenregs* m) अणु
	काष्ठा i2c_client *c = md->client;

	अगर (m->mode == MATROXFB_OUTPUT_MODE_MONITOR) अणु
		LR(0x80);
		LR(0x81);
		LR(0x82);

		LR(0xB3);
		LR(0x94);

		LRP(0x96);
		LRP(0x98);
		LRP(0x9A);
		LRP(0x9C);
		LRP(0x9E);
		LRP(0xA0);
		LRP(0xA2);
		LRP(0xA4);
		LRP(0xA6);
		LRP(0xA8);
		LRP(0xAA);
		LRP(0xAC);
		LRP(0xAE);

		LR(0xB0);	/* output: monitor */
		LR(0xB1);	/* ??? */
		LR(0x8C);	/* must be set... */
		LR(0x8D);	/* शेषs to 0x10: test संकेत */
		LR(0xB9);	/* शेषs to 0x2C: too bright */
		LR(0xBF);	/* makes picture stable */
	पूर्ण अन्यथा अणु
		maven_init_TV(c, m);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक maven_resync(काष्ठा maven_data* md) अणु
	काष्ठा i2c_client *c = md->client;
	maven_set_reg(c, 0x95, 0x20);	/* start whole thing */
	वापस 0;
पूर्ण

अटल पूर्णांक maven_get_queryctrl (काष्ठा maven_data* md, 
				काष्ठा v4l2_queryctrl *p) अणु
	पूर्णांक i;
	
	i = get_ctrl_id(p->id);
	अगर (i >= 0) अणु
		*p = maven_controls[i].desc;
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

अटल पूर्णांक maven_set_control (काष्ठा maven_data* md, 
			      काष्ठा v4l2_control *p) अणु
	पूर्णांक i;
	
	i = get_ctrl_id(p->id);
	अगर (i < 0) वापस -EINVAL;

	/*
	 * Check अगर changed.
	 */
	अगर (p->value == *get_ctrl_ptr(md, i)) वापस 0;

	/*
	 * Check limits.
	 */
	अगर (p->value > maven_controls[i].desc.maximum) वापस -EINVAL;
	अगर (p->value < maven_controls[i].desc.minimum) वापस -EINVAL;

	/*
	 * Store new value.
	 */
	*get_ctrl_ptr(md, i) = p->value;

	चयन (p->id) अणु
		हाल V4L2_CID_BRIGHTNESS:
		हाल V4L2_CID_CONTRAST:
		अणु
		  पूर्णांक blacklevel, whitelevel;
		  maven_compute_bwlevel(md, &blacklevel, &whitelevel);
		  blacklevel = (blacklevel >> 2) | ((blacklevel & 3) << 8);
		  whitelevel = (whitelevel >> 2) | ((whitelevel & 3) << 8);
		  maven_set_reg_pair(md->client, 0x0e, blacklevel);
		  maven_set_reg_pair(md->client, 0x1e, whitelevel);
		पूर्ण
		अवरोध;
		हाल V4L2_CID_SATURATION:
		अणु
		  maven_set_reg(md->client, 0x20, p->value);
		  maven_set_reg(md->client, 0x22, p->value);
		पूर्ण
		अवरोध;
		हाल V4L2_CID_HUE:
		अणु
		  maven_set_reg(md->client, 0x25, p->value);
		पूर्ण
		अवरोध;
		हाल V4L2_CID_GAMMA:
		अणु
		  स्थिर काष्ठा maven_gamma* g;
		  g = maven_compute_gamma(md);
		  maven_set_reg(md->client, 0x83, g->reg83);
		  maven_set_reg(md->client, 0x84, g->reg84);
		  maven_set_reg(md->client, 0x85, g->reg85);
		  maven_set_reg(md->client, 0x86, g->reg86);
		  maven_set_reg(md->client, 0x87, g->reg87);
		  maven_set_reg(md->client, 0x88, g->reg88);
		  maven_set_reg(md->client, 0x89, g->reg89);
		  maven_set_reg(md->client, 0x8a, g->reg8a);
		  maven_set_reg(md->client, 0x8b, g->reg8b);
		पूर्ण
		अवरोध;
		हाल MATROXFB_CID_TESTOUT:
		अणु
			अचिन्हित अक्षर val 
			  = maven_get_reg(md->client, 0x8d);
			अगर (p->value) val |= 0x10;
			अन्यथा          val &= ~0x10;
			maven_set_reg(md->client, 0x8d, val);
		पूर्ण
		अवरोध;
		हाल MATROXFB_CID_DEFLICKER:
		अणु
		  maven_set_reg(md->client, 0x93, maven_compute_deflicker(md));
		पूर्ण
		अवरोध;
	पूर्ण
	

	वापस 0;
पूर्ण

अटल पूर्णांक maven_get_control (काष्ठा maven_data* md, 
			      काष्ठा v4l2_control *p) अणु
	पूर्णांक i;
	
	i = get_ctrl_id(p->id);
	अगर (i < 0) वापस -EINVAL;
	p->value = *get_ctrl_ptr(md, i);
	वापस 0;
पूर्ण

/******************************************************/

अटल पूर्णांक maven_out_compute(व्योम* md, काष्ठा my_timming* mt) अणु
#घोषणा mdinfo ((काष्ठा maven_data*)md)
#घोषणा minfo (mdinfo->primary_head)
	वापस maven_compute_timming(md, mt, &minfo->hw.maven);
#अघोषित minfo
#अघोषित mdinfo
पूर्ण

अटल पूर्णांक maven_out_program(व्योम* md) अणु
#घोषणा mdinfo ((काष्ठा maven_data*)md)
#घोषणा minfo (mdinfo->primary_head)
	वापस maven_program_timming(md, &minfo->hw.maven);
#अघोषित minfo
#अघोषित mdinfo
पूर्ण

अटल पूर्णांक maven_out_start(व्योम* md) अणु
	वापस maven_resync(md);
पूर्ण

अटल पूर्णांक maven_out_verअगरy_mode(व्योम* md, u_पूर्णांक32_t arg) अणु
	चयन (arg) अणु
		हाल MATROXFB_OUTPUT_MODE_PAL:
		हाल MATROXFB_OUTPUT_MODE_NTSC:
		हाल MATROXFB_OUTPUT_MODE_MONITOR:
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक maven_out_get_queryctrl(व्योम* md, काष्ठा v4l2_queryctrl* p) अणु
        वापस maven_get_queryctrl(md, p);
पूर्ण

अटल पूर्णांक maven_out_get_ctrl(व्योम* md, काष्ठा v4l2_control* p) अणु
	वापस maven_get_control(md, p);
पूर्ण

अटल पूर्णांक maven_out_set_ctrl(व्योम* md, काष्ठा v4l2_control* p) अणु
	वापस maven_set_control(md, p);
पूर्ण

अटल काष्ठा matrox_altout maven_altout = अणु
	.name		= "Secondary output",
	.compute	= maven_out_compute,
	.program	= maven_out_program,
	.start		= maven_out_start,
	.verअगरymode	= maven_out_verअगरy_mode,
	.getqueryctrl	= maven_out_get_queryctrl,
	.अ_लोtrl	= maven_out_get_ctrl,
	.setctrl	= maven_out_set_ctrl,
पूर्ण;

अटल पूर्णांक maven_init_client(काष्ठा i2c_client* clnt) अणु
	काष्ठा maven_data* md = i2c_get_clientdata(clnt);
	काष्ठा matrox_fb_info *minfo = container_of(clnt->adapter,
						    काष्ठा i2c_bit_adapter,
						    adapter)->minfo;

	md->primary_head = minfo;
	md->client = clnt;
	करोwn_ग_लिखो(&minfo->altout.lock);
	minfo->outमाला_दो[1].output = &maven_altout;
	minfo->outमाला_दो[1].src = minfo->outमाला_दो[1].शेष_src;
	minfo->outमाला_दो[1].data = md;
	minfo->outमाला_दो[1].mode = MATROXFB_OUTPUT_MODE_MONITOR;
	up_ग_लिखो(&minfo->altout.lock);
	अगर (maven_get_reg(clnt, 0xB2) < 0x14) अणु
		md->version = MGATVO_B;
		/* Tweak some things क्रम this old chip */
	पूर्ण अन्यथा अणु
		md->version = MGATVO_C;
	पूर्ण
	/*
	 * Set all parameters to its initial values.
	 */
	अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < MAVCTRLS; ++i) अणु
			*get_ctrl_ptr(md, i) = maven_controls[i].desc.शेष_value;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक maven_shutकरोwn_client(काष्ठा i2c_client* clnt) अणु
	काष्ठा maven_data* md = i2c_get_clientdata(clnt);

	अगर (md->primary_head) अणु
		काष्ठा matrox_fb_info *minfo = md->primary_head;

		करोwn_ग_लिखो(&minfo->altout.lock);
		minfo->outमाला_दो[1].src = MATROXFB_SRC_NONE;
		minfo->outमाला_दो[1].output = शून्य;
		minfo->outमाला_दो[1].data = शून्य;
		minfo->outमाला_दो[1].mode = MATROXFB_OUTPUT_MODE_MONITOR;
		up_ग_लिखो(&minfo->altout.lock);
		md->primary_head = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक maven_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक err = -ENODEV;
	काष्ठा maven_data* data;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WRITE_WORD_DATA |
					      I2C_FUNC_SMBUS_BYTE_DATA |
					      I2C_FUNC_NOSTART |
					      I2C_FUNC_PROTOCOL_MANGLING))
		जाओ ERROR0;
	अगर (!(data = kzalloc(माप(*data), GFP_KERNEL))) अणु
		err = -ENOMEM;
		जाओ ERROR0;
	पूर्ण
	i2c_set_clientdata(client, data);
	err = maven_init_client(client);
	अगर (err)
		जाओ ERROR4;
	वापस 0;
ERROR4:;
	kमुक्त(data);
ERROR0:;
	वापस err;
पूर्ण

अटल पूर्णांक maven_हटाओ(काष्ठा i2c_client *client)
अणु
	maven_shutकरोwn_client(client);
	kमुक्त(i2c_get_clientdata(client));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id maven_id[] = अणु
	अणु "maven", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, maven_id);

अटल काष्ठा i2c_driver maven_driver=अणु
	.driver = अणु
		.name	= "maven",
	पूर्ण,
	.probe		= maven_probe,
	.हटाओ		= maven_हटाओ,
	.id_table	= maven_id,
पूर्ण;

module_i2c_driver(maven_driver);
MODULE_AUTHOR("(c) 1999-2002 Petr Vandrovec <vandrove@vc.cvut.cz>");
MODULE_DESCRIPTION("Matrox G200/G400 Matrox MGA-TVO driver");
MODULE_LICENSE("GPL");
