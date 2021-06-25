<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2010 Matt Turner.
 * Copyright 2012 Red Hat
 *
 * Authors: Matthew Garrett
 *	    Matt Turner
 *	    Dave Airlie
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-buf-map.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_state_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "mgag200_drv.h"

#घोषणा MGAG200_LUT_SIZE 256

/*
 * This file contains setup code क्रम the CRTC.
 */

अटल व्योम mga_crtc_load_lut(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा mga_device *mdev = to_mga_device(dev);
	काष्ठा drm_framebuffer *fb;
	u16 *r_ptr, *g_ptr, *b_ptr;
	पूर्णांक i;

	अगर (!crtc->enabled)
		वापस;

	अगर (!mdev->display_pipe.plane.state)
		वापस;

	fb = mdev->display_pipe.plane.state->fb;

	r_ptr = crtc->gamma_store;
	g_ptr = r_ptr + crtc->gamma_size;
	b_ptr = g_ptr + crtc->gamma_size;

	WREG8(DAC_INDEX + MGA1064_INDEX, 0);

	अगर (fb && fb->क्रमmat->cpp[0] * 8 == 16) अणु
		पूर्णांक inc = (fb->क्रमmat->depth == 15) ? 8 : 4;
		u8 r, b;
		क्रम (i = 0; i < MGAG200_LUT_SIZE; i += inc) अणु
			अगर (fb->क्रमmat->depth == 16) अणु
				अगर (i > (MGAG200_LUT_SIZE >> 1)) अणु
					r = b = 0;
				पूर्ण अन्यथा अणु
					r = *r_ptr++ >> 8;
					b = *b_ptr++ >> 8;
					r_ptr++;
					b_ptr++;
				पूर्ण
			पूर्ण अन्यथा अणु
				r = *r_ptr++ >> 8;
				b = *b_ptr++ >> 8;
			पूर्ण
			/* VGA रेजिस्टरs */
			WREG8(DAC_INDEX + MGA1064_COL_PAL, r);
			WREG8(DAC_INDEX + MGA1064_COL_PAL, *g_ptr++ >> 8);
			WREG8(DAC_INDEX + MGA1064_COL_PAL, b);
		पूर्ण
		वापस;
	पूर्ण
	क्रम (i = 0; i < MGAG200_LUT_SIZE; i++) अणु
		/* VGA रेजिस्टरs */
		WREG8(DAC_INDEX + MGA1064_COL_PAL, *r_ptr++ >> 8);
		WREG8(DAC_INDEX + MGA1064_COL_PAL, *g_ptr++ >> 8);
		WREG8(DAC_INDEX + MGA1064_COL_PAL, *b_ptr++ >> 8);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mga_रुको_vsync(काष्ठा mga_device *mdev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ/10;
	अचिन्हित पूर्णांक status = 0;

	करो अणु
		status = RREG32(MGAREG_Status);
	पूर्ण जबतक ((status & 0x08) && समय_beक्रमe(jअगरfies, समयout));
	समयout = jअगरfies + HZ/10;
	status = 0;
	करो अणु
		status = RREG32(MGAREG_Status);
	पूर्ण जबतक (!(status & 0x08) && समय_beक्रमe(jअगरfies, समयout));
पूर्ण

अटल अंतरभूत व्योम mga_रुको_busy(काष्ठा mga_device *mdev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	अचिन्हित पूर्णांक status = 0;
	करो अणु
		status = RREG8(MGAREG_Status + 2);
	पूर्ण जबतक ((status & 0x01) && समय_beक्रमe(jअगरfies, समयout));
पूर्ण

/*
 * PLL setup
 */

अटल पूर्णांक mgag200_g200_set_plls(काष्ठा mga_device *mdev, दीर्घ घड़ी)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	स्थिर पूर्णांक post_भाग_max = 7;
	स्थिर पूर्णांक in_भाग_min = 1;
	स्थिर पूर्णांक in_भाग_max = 6;
	स्थिर पूर्णांक feed_भाग_min = 7;
	स्थिर पूर्णांक feed_भाग_max = 127;
	u8 tesपंचांग, testn;
	u8 n = 0, m = 0, p, s;
	दीर्घ f_vco;
	दीर्घ computed;
	दीर्घ delta, पंचांगp_delta;
	दीर्घ ref_clk = mdev->model.g200.ref_clk;
	दीर्घ p_clk_min = mdev->model.g200.pclk_min;
	दीर्घ p_clk_max =  mdev->model.g200.pclk_max;

	अगर (घड़ी > p_clk_max) अणु
		drm_err(dev, "Pixel Clock %ld too high\n", घड़ी);
		वापस 1;
	पूर्ण

	अगर (घड़ी < p_clk_min >> 3)
		घड़ी = p_clk_min >> 3;

	f_vco = घड़ी;
	क्रम (p = 0;
	     p <= post_भाग_max && f_vco < p_clk_min;
	     p = (p << 1) + 1, f_vco <<= 1)
		;

	delta = घड़ी;

	क्रम (tesपंचांग = in_भाग_min; tesपंचांग <= in_भाग_max; tesपंचांग++) अणु
		क्रम (testn = feed_भाग_min; testn <= feed_भाग_max; testn++) अणु
			computed = ref_clk * (testn + 1) / (tesपंचांग + 1);
			अगर (computed < f_vco)
				पंचांगp_delta = f_vco - computed;
			अन्यथा
				पंचांगp_delta = computed - f_vco;
			अगर (पंचांगp_delta < delta) अणु
				delta = पंचांगp_delta;
				m = tesपंचांग;
				n = testn;
			पूर्ण
		पूर्ण
	पूर्ण
	f_vco = ref_clk * (n + 1) / (m + 1);
	अगर (f_vco < 100000)
		s = 0;
	अन्यथा अगर (f_vco < 140000)
		s = 1;
	अन्यथा अगर (f_vco < 180000)
		s = 2;
	अन्यथा
		s = 3;

	drm_dbg_kms(dev, "clock: %ld vco: %ld m: %d n: %d p: %d s: %d\n",
		    घड़ी, f_vco, m, n, p, s);

	WREG_DAC(MGA1064_PIX_PLLC_M, m);
	WREG_DAC(MGA1064_PIX_PLLC_N, n);
	WREG_DAC(MGA1064_PIX_PLLC_P, (p | (s << 3)));

	वापस 0;
पूर्ण

#घोषणा P_ARRAY_SIZE 9

अटल पूर्णांक mga_g200se_set_plls(काष्ठा mga_device *mdev, दीर्घ घड़ी)
अणु
	u32 unique_rev_id = mdev->model.g200se.unique_rev_id;
	अचिन्हित पूर्णांक vcomax, vcomin, pllreffreq;
	अचिन्हित पूर्णांक delta, पंचांगpdelta, permitteddelta;
	अचिन्हित पूर्णांक testp, tesपंचांग, testn;
	अचिन्हित पूर्णांक p, m, n;
	अचिन्हित पूर्णांक computed;
	अचिन्हित पूर्णांक pvalues_e4[P_ARRAY_SIZE] = अणु16, 14, 12, 10, 8, 6, 4, 2, 1पूर्ण;
	अचिन्हित पूर्णांक fvv;
	अचिन्हित पूर्णांक i;

	अगर (unique_rev_id <= 0x03) अणु

		m = n = p = 0;
		vcomax = 320000;
		vcomin = 160000;
		pllreffreq = 25000;

		delta = 0xffffffff;
		permitteddelta = घड़ी * 5 / 1000;

		क्रम (testp = 8; testp > 0; testp /= 2) अणु
			अगर (घड़ी * testp > vcomax)
				जारी;
			अगर (घड़ी * testp < vcomin)
				जारी;

			क्रम (testn = 17; testn < 256; testn++) अणु
				क्रम (tesपंचांग = 1; tesपंचांग < 32; tesपंचांग++) अणु
					computed = (pllreffreq * testn) /
						(tesपंचांग * testp);
					अगर (computed > घड़ी)
						पंचांगpdelta = computed - घड़ी;
					अन्यथा
						पंचांगpdelta = घड़ी - computed;
					अगर (पंचांगpdelta < delta) अणु
						delta = पंचांगpdelta;
						m = tesपंचांग - 1;
						n = testn - 1;
						p = testp - 1;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु


		m = n = p = 0;
		vcomax        = 1600000;
		vcomin        = 800000;
		pllreffreq    = 25000;

		अगर (घड़ी < 25000)
			घड़ी = 25000;

		घड़ी = घड़ी * 2;

		delta = 0xFFFFFFFF;
		/* Permited delta is 0.5% as VESA Specअगरication */
		permitteddelta = घड़ी * 5 / 1000;

		क्रम (i = 0 ; i < P_ARRAY_SIZE ; i++) अणु
			testp = pvalues_e4[i];

			अगर ((घड़ी * testp) > vcomax)
				जारी;
			अगर ((घड़ी * testp) < vcomin)
				जारी;

			क्रम (testn = 50; testn <= 256; testn++) अणु
				क्रम (tesपंचांग = 1; tesपंचांग <= 32; tesपंचांग++) अणु
					computed = (pllreffreq * testn) /
						(tesपंचांग * testp);
					अगर (computed > घड़ी)
						पंचांगpdelta = computed - घड़ी;
					अन्यथा
						पंचांगpdelta = घड़ी - computed;

					अगर (पंचांगpdelta < delta) अणु
						delta = पंचांगpdelta;
						m = tesपंचांग - 1;
						n = testn - 1;
						p = testp - 1;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		fvv = pllreffreq * (n + 1) / (m + 1);
		fvv = (fvv - 800000) / 50000;

		अगर (fvv > 15)
			fvv = 15;

		p |= (fvv << 4);
		m |= 0x80;

		घड़ी = घड़ी / 2;
	पूर्ण

	अगर (delta > permitteddelta) अणु
		pr_warn("PLL delta too large\n");
		वापस 1;
	पूर्ण

	WREG_DAC(MGA1064_PIX_PLLC_M, m);
	WREG_DAC(MGA1064_PIX_PLLC_N, n);
	WREG_DAC(MGA1064_PIX_PLLC_P, p);

	अगर (unique_rev_id >= 0x04) अणु
		WREG_DAC(0x1a, 0x09);
		msleep(20);
		WREG_DAC(0x1a, 0x01);

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mga_g200wb_set_plls(काष्ठा mga_device *mdev, दीर्घ घड़ी)
अणु
	अचिन्हित पूर्णांक vcomax, vcomin, pllreffreq;
	अचिन्हित पूर्णांक delta, पंचांगpdelta;
	अचिन्हित पूर्णांक testp, tesपंचांग, testn, testp2;
	अचिन्हित पूर्णांक p, m, n;
	अचिन्हित पूर्णांक computed;
	पूर्णांक i, j, पंचांगpcount, vcount;
	bool pll_locked = false;
	u8 पंचांगp;

	m = n = p = 0;

	delta = 0xffffffff;

	अगर (mdev->type == G200_EW3) अणु

		vcomax = 800000;
		vcomin = 400000;
		pllreffreq = 25000;

		क्रम (testp = 1; testp < 8; testp++) अणु
			क्रम (testp2 = 1; testp2 < 8; testp2++) अणु
				अगर (testp < testp2)
					जारी;
				अगर ((घड़ी * testp * testp2) > vcomax)
					जारी;
				अगर ((घड़ी * testp * testp2) < vcomin)
					जारी;
				क्रम (tesपंचांग = 1; tesपंचांग < 26; tesपंचांग++) अणु
					क्रम (testn = 32; testn < 2048 ; testn++) अणु
						computed = (pllreffreq * testn) /
							(tesपंचांग * testp * testp2);
						अगर (computed > घड़ी)
							पंचांगpdelta = computed - घड़ी;
						अन्यथा
							पंचांगpdelta = घड़ी - computed;
						अगर (पंचांगpdelta < delta) अणु
							delta = पंचांगpdelta;
							m = ((testn & 0x100) >> 1) |
								(tesपंचांग);
							n = (testn & 0xFF);
							p = ((testn & 0x600) >> 3) |
								(testp2 << 3) |
								(testp);
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु

		vcomax = 550000;
		vcomin = 150000;
		pllreffreq = 48000;

		क्रम (testp = 1; testp < 9; testp++) अणु
			अगर (घड़ी * testp > vcomax)
				जारी;
			अगर (घड़ी * testp < vcomin)
				जारी;

			क्रम (tesपंचांग = 1; tesपंचांग < 17; tesपंचांग++) अणु
				क्रम (testn = 1; testn < 151; testn++) अणु
					computed = (pllreffreq * testn) /
						(tesपंचांग * testp);
					अगर (computed > घड़ी)
						पंचांगpdelta = computed - घड़ी;
					अन्यथा
						पंचांगpdelta = घड़ी - computed;
					अगर (पंचांगpdelta < delta) अणु
						delta = पंचांगpdelta;
						n = testn - 1;
						m = (tesपंचांग - 1) |
							((n >> 1) & 0x80);
						p = testp - 1;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <= 32 && pll_locked == false; i++) अणु
		अगर (i > 0) अणु
			WREG8(MGAREG_CRTC_INDEX, 0x1e);
			पंचांगp = RREG8(MGAREG_CRTC_DATA);
			अगर (पंचांगp < 0xff)
				WREG8(MGAREG_CRTC_DATA, पंचांगp+1);
		पूर्ण

		/* set pixclkdis to 1 */
		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_DIS;
		WREG8(DAC_DATA, पंचांगp);

		WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp |= MGA1064_REMHEADCTL_CLKDIS;
		WREG8(DAC_DATA, पंचांगp);

		/* select PLL Set C */
		पंचांगp = RREG8(MGAREG_MEM_MISC_READ);
		पंचांगp |= 0x3 << 2;
		WREG8(MGAREG_MEM_MISC_WRITE, पंचांगp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_POW_DOWN | 0x80;
		WREG8(DAC_DATA, पंचांगp);

		udelay(500);

		/* reset the PLL */
		WREG8(DAC_INDEX, MGA1064_VREF_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp &= ~0x04;
		WREG8(DAC_DATA, पंचांगp);

		udelay(50);

		/* program pixel pll रेजिस्टर */
		WREG_DAC(MGA1064_WB_PIX_PLLC_N, n);
		WREG_DAC(MGA1064_WB_PIX_PLLC_M, m);
		WREG_DAC(MGA1064_WB_PIX_PLLC_P, p);

		udelay(50);

		/* turn pll on */
		WREG8(DAC_INDEX, MGA1064_VREF_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp |= 0x04;
		WREG_DAC(MGA1064_VREF_CTL, पंचांगp);

		udelay(500);

		/* select the pixel pll */
		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp &= ~MGA1064_PIX_CLK_CTL_SEL_MSK;
		पंचांगp |= MGA1064_PIX_CLK_CTL_SEL_PLL;
		WREG8(DAC_DATA, पंचांगp);

		WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp &= ~MGA1064_REMHEADCTL_CLKSL_MSK;
		पंचांगp |= MGA1064_REMHEADCTL_CLKSL_PLL;
		WREG8(DAC_DATA, पंचांगp);

		/* reset करोtघड़ी rate bit */
		WREG8(MGAREG_SEQ_INDEX, 1);
		पंचांगp = RREG8(MGAREG_SEQ_DATA);
		पंचांगp &= ~0x8;
		WREG8(MGAREG_SEQ_DATA, पंचांगp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp &= ~MGA1064_PIX_CLK_CTL_CLK_DIS;
		WREG8(DAC_DATA, पंचांगp);

		vcount = RREG8(MGAREG_VCOUNT);

		क्रम (j = 0; j < 30 && pll_locked == false; j++) अणु
			पंचांगpcount = RREG8(MGAREG_VCOUNT);
			अगर (पंचांगpcount < vcount)
				vcount = 0;
			अगर ((पंचांगpcount - vcount) > 2)
				pll_locked = true;
			अन्यथा
				udelay(5);
		पूर्ण
	पूर्ण
	WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp &= ~MGA1064_REMHEADCTL_CLKDIS;
	WREG_DAC(MGA1064_REMHEADCTL, पंचांगp);
	वापस 0;
पूर्ण

अटल पूर्णांक mga_g200ev_set_plls(काष्ठा mga_device *mdev, दीर्घ घड़ी)
अणु
	अचिन्हित पूर्णांक vcomax, vcomin, pllreffreq;
	अचिन्हित पूर्णांक delta, पंचांगpdelta;
	अचिन्हित पूर्णांक testp, tesपंचांग, testn;
	अचिन्हित पूर्णांक p, m, n;
	अचिन्हित पूर्णांक computed;
	u8 पंचांगp;

	m = n = p = 0;
	vcomax = 550000;
	vcomin = 150000;
	pllreffreq = 50000;

	delta = 0xffffffff;

	क्रम (testp = 16; testp > 0; testp--) अणु
		अगर (घड़ी * testp > vcomax)
			जारी;
		अगर (घड़ी * testp < vcomin)
			जारी;

		क्रम (testn = 1; testn < 257; testn++) अणु
			क्रम (tesपंचांग = 1; tesपंचांग < 17; tesपंचांग++) अणु
				computed = (pllreffreq * testn) /
					(tesपंचांग * testp);
				अगर (computed > घड़ी)
					पंचांगpdelta = computed - घड़ी;
				अन्यथा
					पंचांगpdelta = घड़ी - computed;
				अगर (पंचांगpdelta < delta) अणु
					delta = पंचांगpdelta;
					n = testn - 1;
					m = tesपंचांग - 1;
					p = testp - 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_DIS;
	WREG8(DAC_DATA, पंचांगp);

	पंचांगp = RREG8(MGAREG_MEM_MISC_READ);
	पंचांगp |= 0x3 << 2;
	WREG8(MGAREG_MEM_MISC_WRITE, पंचांगp);

	WREG8(DAC_INDEX, MGA1064_PIX_PLL_STAT);
	पंचांगp = RREG8(DAC_DATA);
	WREG8(DAC_DATA, पंचांगp & ~0x40);

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
	WREG8(DAC_DATA, पंचांगp);

	WREG_DAC(MGA1064_EV_PIX_PLLC_M, m);
	WREG_DAC(MGA1064_EV_PIX_PLLC_N, n);
	WREG_DAC(MGA1064_EV_PIX_PLLC_P, p);

	udelay(50);

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp &= ~MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
	WREG8(DAC_DATA, पंचांगp);

	udelay(500);

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp &= ~MGA1064_PIX_CLK_CTL_SEL_MSK;
	पंचांगp |= MGA1064_PIX_CLK_CTL_SEL_PLL;
	WREG8(DAC_DATA, पंचांगp);

	WREG8(DAC_INDEX, MGA1064_PIX_PLL_STAT);
	पंचांगp = RREG8(DAC_DATA);
	WREG8(DAC_DATA, पंचांगp | 0x40);

	पंचांगp = RREG8(MGAREG_MEM_MISC_READ);
	पंचांगp |= (0x3 << 2);
	WREG8(MGAREG_MEM_MISC_WRITE, पंचांगp);

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp &= ~MGA1064_PIX_CLK_CTL_CLK_DIS;
	WREG8(DAC_DATA, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक mga_g200eh_set_plls(काष्ठा mga_device *mdev, दीर्घ घड़ी)
अणु
	अचिन्हित पूर्णांक vcomax, vcomin, pllreffreq;
	अचिन्हित पूर्णांक delta, पंचांगpdelta;
	अचिन्हित पूर्णांक testp, tesपंचांग, testn;
	अचिन्हित पूर्णांक p, m, n;
	अचिन्हित पूर्णांक computed;
	पूर्णांक i, j, पंचांगpcount, vcount;
	u8 पंचांगp;
	bool pll_locked = false;

	m = n = p = 0;

	अगर (mdev->type == G200_EH3) अणु
		vcomax = 3000000;
		vcomin = 1500000;
		pllreffreq = 25000;

		delta = 0xffffffff;

		testp = 0;

		क्रम (tesपंचांग = 150; tesपंचांग >= 6; tesपंचांग--) अणु
			अगर (घड़ी * tesपंचांग > vcomax)
				जारी;
			अगर (घड़ी * tesपंचांग < vcomin)
				जारी;
			क्रम (testn = 120; testn >= 60; testn--) अणु
				computed = (pllreffreq * testn) / tesपंचांग;
				अगर (computed > घड़ी)
					पंचांगpdelta = computed - घड़ी;
				अन्यथा
					पंचांगpdelta = घड़ी - computed;
				अगर (पंचांगpdelta < delta) अणु
					delta = पंचांगpdelta;
					n = testn;
					m = tesपंचांग;
					p = testp;
				पूर्ण
				अगर (delta == 0)
					अवरोध;
			पूर्ण
			अगर (delta == 0)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु

		vcomax = 800000;
		vcomin = 400000;
		pllreffreq = 33333;

		delta = 0xffffffff;

		क्रम (testp = 16; testp > 0; testp >>= 1) अणु
			अगर (घड़ी * testp > vcomax)
				जारी;
			अगर (घड़ी * testp < vcomin)
				जारी;

			क्रम (tesपंचांग = 1; tesपंचांग < 33; tesपंचांग++) अणु
				क्रम (testn = 17; testn < 257; testn++) अणु
					computed = (pllreffreq * testn) /
						(tesपंचांग * testp);
					अगर (computed > घड़ी)
						पंचांगpdelta = computed - घड़ी;
					अन्यथा
						पंचांगpdelta = घड़ी - computed;
					अगर (पंचांगpdelta < delta) अणु
						delta = पंचांगpdelta;
						n = testn - 1;
						m = (tesपंचांग - 1);
						p = testp - 1;
					पूर्ण
					अगर ((घड़ी * testp) >= 600000)
						p |= 0x80;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= 32 && pll_locked == false; i++) अणु
		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_DIS;
		WREG8(DAC_DATA, पंचांगp);

		पंचांगp = RREG8(MGAREG_MEM_MISC_READ);
		पंचांगp |= 0x3 << 2;
		WREG8(MGAREG_MEM_MISC_WRITE, पंचांगp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
		WREG8(DAC_DATA, पंचांगp);

		udelay(500);

		WREG_DAC(MGA1064_EH_PIX_PLLC_M, m);
		WREG_DAC(MGA1064_EH_PIX_PLLC_N, n);
		WREG_DAC(MGA1064_EH_PIX_PLLC_P, p);

		udelay(500);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp &= ~MGA1064_PIX_CLK_CTL_SEL_MSK;
		पंचांगp |= MGA1064_PIX_CLK_CTL_SEL_PLL;
		WREG8(DAC_DATA, पंचांगp);

		WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
		पंचांगp = RREG8(DAC_DATA);
		पंचांगp &= ~MGA1064_PIX_CLK_CTL_CLK_DIS;
		पंचांगp &= ~MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
		WREG8(DAC_DATA, पंचांगp);

		vcount = RREG8(MGAREG_VCOUNT);

		क्रम (j = 0; j < 30 && pll_locked == false; j++) अणु
			पंचांगpcount = RREG8(MGAREG_VCOUNT);
			अगर (पंचांगpcount < vcount)
				vcount = 0;
			अगर ((पंचांगpcount - vcount) > 2)
				pll_locked = true;
			अन्यथा
				udelay(5);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mga_g200er_set_plls(काष्ठा mga_device *mdev, दीर्घ घड़ी)
अणु
	अटल स्थिर अचिन्हित पूर्णांक m_भाग_val[] = अणु 1, 2, 4, 8 पूर्ण;
	अचिन्हित पूर्णांक vcomax, vcomin, pllreffreq;
	अचिन्हित पूर्णांक delta, पंचांगpdelta;
	पूर्णांक testr, testn, tesपंचांग, testo;
	अचिन्हित पूर्णांक p, m, n;
	अचिन्हित पूर्णांक computed, vco;
	पूर्णांक पंचांगp;

	m = n = p = 0;
	vcomax = 1488000;
	vcomin = 1056000;
	pllreffreq = 48000;

	delta = 0xffffffff;

	क्रम (testr = 0; testr < 4; testr++) अणु
		अगर (delta == 0)
			अवरोध;
		क्रम (testn = 5; testn < 129; testn++) अणु
			अगर (delta == 0)
				अवरोध;
			क्रम (tesपंचांग = 3; tesपंचांग >= 0; tesपंचांग--) अणु
				अगर (delta == 0)
					अवरोध;
				क्रम (testo = 5; testo < 33; testo++) अणु
					vco = pllreffreq * (testn + 1) /
						(testr + 1);
					अगर (vco < vcomin)
						जारी;
					अगर (vco > vcomax)
						जारी;
					computed = vco / (m_भाग_val[tesपंचांग] * (testo + 1));
					अगर (computed > घड़ी)
						पंचांगpdelta = computed - घड़ी;
					अन्यथा
						पंचांगpdelta = घड़ी - computed;
					अगर (पंचांगpdelta < delta) अणु
						delta = पंचांगpdelta;
						m = tesपंचांग | (testo << 3);
						n = testn;
						p = testr | (testr << 3);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_DIS;
	WREG8(DAC_DATA, पंचांगp);

	WREG8(DAC_INDEX, MGA1064_REMHEADCTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= MGA1064_REMHEADCTL_CLKDIS;
	WREG8(DAC_DATA, पंचांगp);

	पंचांगp = RREG8(MGAREG_MEM_MISC_READ);
	पंचांगp |= (0x3<<2) | 0xc0;
	WREG8(MGAREG_MEM_MISC_WRITE, पंचांगp);

	WREG8(DAC_INDEX, MGA1064_PIX_CLK_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp &= ~MGA1064_PIX_CLK_CTL_CLK_DIS;
	पंचांगp |= MGA1064_PIX_CLK_CTL_CLK_POW_DOWN;
	WREG8(DAC_DATA, पंचांगp);

	udelay(500);

	WREG_DAC(MGA1064_ER_PIX_PLLC_N, n);
	WREG_DAC(MGA1064_ER_PIX_PLLC_M, m);
	WREG_DAC(MGA1064_ER_PIX_PLLC_P, p);

	udelay(50);

	वापस 0;
पूर्ण

अटल पूर्णांक mgag200_crtc_set_plls(काष्ठा mga_device *mdev, दीर्घ घड़ी)
अणु
	u8 misc;

	चयन(mdev->type) अणु
	हाल G200_PCI:
	हाल G200_AGP:
		वापस mgag200_g200_set_plls(mdev, घड़ी);
	हाल G200_SE_A:
	हाल G200_SE_B:
		वापस mga_g200se_set_plls(mdev, घड़ी);
	हाल G200_WB:
	हाल G200_EW3:
		वापस mga_g200wb_set_plls(mdev, घड़ी);
	हाल G200_EV:
		वापस mga_g200ev_set_plls(mdev, घड़ी);
	हाल G200_EH:
	हाल G200_EH3:
		वापस mga_g200eh_set_plls(mdev, घड़ी);
	हाल G200_ER:
		वापस mga_g200er_set_plls(mdev, घड़ी);
	पूर्ण

	misc = RREG8(MGA_MISC_IN);
	misc &= ~MGAREG_MISC_CLK_SEL_MASK;
	misc |= MGAREG_MISC_CLK_SEL_MGA_MSK;
	WREG8(MGA_MISC_OUT, misc);

	वापस 0;
पूर्ण

अटल व्योम mgag200_g200wb_hold_bmc(काष्ठा mga_device *mdev)
अणु
	u8 पंचांगp;
	पूर्णांक iter_max;

	/* 1- The first step is to warn the BMC of an upcoming mode change.
	 * We are putting the misc<0> to output.*/

	WREG8(DAC_INDEX, MGA1064_GEN_IO_CTL);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= 0x10;
	WREG_DAC(MGA1064_GEN_IO_CTL, पंचांगp);

	/* we are putting a 1 on the misc<0> line */
	WREG8(DAC_INDEX, MGA1064_GEN_IO_DATA);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= 0x10;
	WREG_DAC(MGA1064_GEN_IO_DATA, पंचांगp);

	/* 2- Second step to mask and further scan request
	 * This will be करोne by निश्चितing the remfreqmsk bit (XSPAREREG<7>)
	 */
	WREG8(DAC_INDEX, MGA1064_SPAREREG);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= 0x80;
	WREG_DAC(MGA1064_SPAREREG, पंचांगp);

	/* 3a- the third step is to verअगरu अगर there is an active scan
	 * We are searching क्रम a 0 on remhsyncsts <XSPAREREG<0>)
	 */
	iter_max = 300;
	जबतक (!(पंचांगp & 0x1) && iter_max) अणु
		WREG8(DAC_INDEX, MGA1064_SPAREREG);
		पंचांगp = RREG8(DAC_DATA);
		udelay(1000);
		iter_max--;
	पूर्ण

	/* 3b- this step occurs only अगर the हटाओ is actually scanning
	 * we are रुकोing क्रम the end of the frame which is a 1 on
	 * remvsyncsts (XSPAREREG<1>)
	 */
	अगर (iter_max) अणु
		iter_max = 300;
		जबतक ((पंचांगp & 0x2) && iter_max) अणु
			WREG8(DAC_INDEX, MGA1064_SPAREREG);
			पंचांगp = RREG8(DAC_DATA);
			udelay(1000);
			iter_max--;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mgag200_g200wb_release_bmc(काष्ठा mga_device *mdev)
अणु
	u8 पंचांगp;

	/* 1- The first step is to ensure that the vrsten and hrsten are set */
	WREG8(MGAREG_CRTCEXT_INDEX, 1);
	पंचांगp = RREG8(MGAREG_CRTCEXT_DATA);
	WREG8(MGAREG_CRTCEXT_DATA, पंचांगp | 0x88);

	/* 2- second step is to निश्चित the rstlvl2 */
	WREG8(DAC_INDEX, MGA1064_REMHEADCTL2);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp |= 0x8;
	WREG8(DAC_DATA, पंचांगp);

	/* रुको 10 us */
	udelay(10);

	/* 3- deनिश्चित rstlvl2 */
	पंचांगp &= ~0x08;
	WREG8(DAC_INDEX, MGA1064_REMHEADCTL2);
	WREG8(DAC_DATA, पंचांगp);

	/* 4- हटाओ mask of scan request */
	WREG8(DAC_INDEX, MGA1064_SPAREREG);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp &= ~0x80;
	WREG8(DAC_DATA, पंचांगp);

	/* 5- put back a 0 on the misc<0> line */
	WREG8(DAC_INDEX, MGA1064_GEN_IO_DATA);
	पंचांगp = RREG8(DAC_DATA);
	पंचांगp &= ~0x10;
	WREG_DAC(MGA1064_GEN_IO_DATA, पंचांगp);
पूर्ण

/*
 * This is how the framebuffer base address is stored in g200 cards:
 *   * Assume @offset is the gpu_addr variable of the framebuffer object
 *   * Then addr is the number of _pixels_ (not bytes) from the start of
 *     VRAM to the first pixel we want to display. (भागided by 2 क्रम 32bit
 *     framebuffers)
 *   * addr is stored in the CRTCEXT0, CRTCC and CRTCD रेजिस्टरs
 *      addr<20> -> CRTCEXT0<6>
 *      addr<19-16> -> CRTCEXT0<3-0>
 *      addr<15-8> -> CRTCC<7-0>
 *      addr<7-0> -> CRTCD<7-0>
 *
 *  CRTCEXT0 has to be programmed last to trigger an update and make the
 *  new addr variable take effect.
 */
अटल व्योम mgag200_set_startadd(काष्ठा mga_device *mdev,
				 अचिन्हित दीर्घ offset)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	u32 startadd;
	u8 crtcc, crtcd, crtcext0;

	startadd = offset / 8;

	/*
	 * Can't store addresses any higher than that, but we also
	 * करोn't have more than 16 MiB of memory, so it should be fine.
	 */
	drm_WARN_ON(dev, startadd > 0x1fffff);

	RREG_ECRT(0x00, crtcext0);

	crtcc = (startadd >> 8) & 0xff;
	crtcd = startadd & 0xff;
	crtcext0 &= 0xb0;
	crtcext0 |= ((startadd >> 14) & BIT(6)) |
		    ((startadd >> 16) & 0x0f);

	WREG_CRT(0x0c, crtcc);
	WREG_CRT(0x0d, crtcd);
	WREG_ECRT(0x00, crtcext0);
पूर्ण

अटल व्योम mgag200_set_dac_regs(काष्ठा mga_device *mdev)
अणु
	माप_प्रकार i;
	u8 dacvalue[] = अणु
		/* 0x00: */        0,    0,    0,    0,    0,    0, 0x00,    0,
		/* 0x08: */        0,    0,    0,    0,    0,    0,    0,    0,
		/* 0x10: */        0,    0,    0,    0,    0,    0,    0,    0,
		/* 0x18: */     0x00,    0, 0xC9, 0xFF, 0xBF, 0x20, 0x1F, 0x20,
		/* 0x20: */     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* 0x28: */     0x00, 0x00, 0x00, 0x00,    0,    0,    0, 0x40,
		/* 0x30: */     0x00, 0xB0, 0x00, 0xC2, 0x34, 0x14, 0x02, 0x83,
		/* 0x38: */     0x00, 0x93, 0x00, 0x77, 0x00, 0x00, 0x00, 0x3A,
		/* 0x40: */        0,    0,    0,    0,    0,    0,    0,    0,
		/* 0x48: */        0,    0,    0,    0,    0,    0,    0,    0
	पूर्ण;

	चयन (mdev->type) अणु
	हाल G200_PCI:
	हाल G200_AGP:
		dacvalue[MGA1064_SYS_PLL_M] = 0x04;
		dacvalue[MGA1064_SYS_PLL_N] = 0x2D;
		dacvalue[MGA1064_SYS_PLL_P] = 0x19;
		अवरोध;
	हाल G200_SE_A:
	हाल G200_SE_B:
		dacvalue[MGA1064_VREF_CTL] = 0x03;
		dacvalue[MGA1064_PIX_CLK_CTL] = MGA1064_PIX_CLK_CTL_SEL_PLL;
		dacvalue[MGA1064_MISC_CTL] = MGA1064_MISC_CTL_DAC_EN |
					     MGA1064_MISC_CTL_VGA8 |
					     MGA1064_MISC_CTL_DAC_RAM_CS;
		अवरोध;
	हाल G200_WB:
	हाल G200_EW3:
		dacvalue[MGA1064_VREF_CTL] = 0x07;
		अवरोध;
	हाल G200_EV:
		dacvalue[MGA1064_PIX_CLK_CTL] = MGA1064_PIX_CLK_CTL_SEL_PLL;
		dacvalue[MGA1064_MISC_CTL] = MGA1064_MISC_CTL_VGA8 |
					     MGA1064_MISC_CTL_DAC_RAM_CS;
		अवरोध;
	हाल G200_EH:
	हाल G200_EH3:
		dacvalue[MGA1064_MISC_CTL] = MGA1064_MISC_CTL_VGA8 |
					     MGA1064_MISC_CTL_DAC_RAM_CS;
		अवरोध;
	हाल G200_ER:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(dacvalue); i++) अणु
		अगर ((i <= 0x17) ||
		    (i == 0x1b) ||
		    (i == 0x1c) ||
		    ((i >= 0x1f) && (i <= 0x29)) ||
		    ((i >= 0x30) && (i <= 0x37)))
			जारी;
		अगर (IS_G200_SE(mdev) &&
		    ((i == 0x2c) || (i == 0x2d) || (i == 0x2e)))
			जारी;
		अगर ((mdev->type == G200_EV ||
		    mdev->type == G200_WB ||
		    mdev->type == G200_EH ||
		    mdev->type == G200_EW3 ||
		    mdev->type == G200_EH3) &&
		    (i >= 0x44) && (i <= 0x4e))
			जारी;

		WREG_DAC(i, dacvalue[i]);
	पूर्ण

	अगर (mdev->type == G200_ER)
		WREG_DAC(0x90, 0);
पूर्ण

अटल व्योम mgag200_init_regs(काष्ठा mga_device *mdev)
अणु
	u8 crtc11, misc;

	mgag200_set_dac_regs(mdev);

	WREG_SEQ(2, 0x0f);
	WREG_SEQ(3, 0x00);
	WREG_SEQ(4, 0x0e);

	WREG_CRT(10, 0);
	WREG_CRT(11, 0);
	WREG_CRT(12, 0);
	WREG_CRT(13, 0);
	WREG_CRT(14, 0);
	WREG_CRT(15, 0);

	RREG_CRT(0x11, crtc11);
	crtc11 &= ~(MGAREG_CRTC11_CRTCPROTECT |
		    MGAREG_CRTC11_VINTEN |
		    MGAREG_CRTC11_VINTCLR);
	WREG_CRT(0x11, crtc11);

	अगर (mdev->type == G200_ER)
		WREG_ECRT(0x24, 0x5);

	अगर (mdev->type == G200_EW3)
		WREG_ECRT(0x34, 0x5);

	misc = RREG8(MGA_MISC_IN);
	misc |= MGAREG_MISC_IOADSEL;
	WREG8(MGA_MISC_OUT, misc);
पूर्ण

अटल व्योम mgag200_set_mode_regs(काष्ठा mga_device *mdev,
				  स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित पूर्णांक hdisplay, hsyncstart, hsyncend, htotal;
	अचिन्हित पूर्णांक vdisplay, vsyncstart, vsyncend, vtotal;
	u8 misc, crtcext1, crtcext2, crtcext5;

	hdisplay = mode->hdisplay / 8 - 1;
	hsyncstart = mode->hsync_start / 8 - 1;
	hsyncend = mode->hsync_end / 8 - 1;
	htotal = mode->htotal / 8 - 1;

	/* Work around hardware quirk */
	अगर ((htotal & 0x07) == 0x06 || (htotal & 0x07) == 0x04)
		htotal++;

	vdisplay = mode->vdisplay - 1;
	vsyncstart = mode->vsync_start - 1;
	vsyncend = mode->vsync_end - 1;
	vtotal = mode->vtotal - 2;

	misc = RREG8(MGA_MISC_IN);

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		misc |= MGAREG_MISC_HSYNCPOL;
	अन्यथा
		misc &= ~MGAREG_MISC_HSYNCPOL;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		misc |= MGAREG_MISC_VSYNCPOL;
	अन्यथा
		misc &= ~MGAREG_MISC_VSYNCPOL;

	crtcext1 = (((htotal - 4) & 0x100) >> 8) |
		   ((hdisplay & 0x100) >> 7) |
		   ((hsyncstart & 0x100) >> 6) |
		    (htotal & 0x40);
	अगर (mdev->type == G200_WB || mdev->type == G200_EW3)
		crtcext1 |= BIT(7) | /* vrsten */
			    BIT(3); /* hrsten */

	crtcext2 = ((vtotal & 0xc00) >> 10) |
		   ((vdisplay & 0x400) >> 8) |
		   ((vdisplay & 0xc00) >> 7) |
		   ((vsyncstart & 0xc00) >> 5) |
		   ((vdisplay & 0x400) >> 3);
	crtcext5 = 0x00;

	WREG_CRT(0, htotal - 4);
	WREG_CRT(1, hdisplay);
	WREG_CRT(2, hdisplay);
	WREG_CRT(3, (htotal & 0x1F) | 0x80);
	WREG_CRT(4, hsyncstart);
	WREG_CRT(5, ((htotal & 0x20) << 2) | (hsyncend & 0x1F));
	WREG_CRT(6, vtotal & 0xFF);
	WREG_CRT(7, ((vtotal & 0x100) >> 8) |
		 ((vdisplay & 0x100) >> 7) |
		 ((vsyncstart & 0x100) >> 6) |
		 ((vdisplay & 0x100) >> 5) |
		 ((vdisplay & 0x100) >> 4) | /* linecomp */
		 ((vtotal & 0x200) >> 4) |
		 ((vdisplay & 0x200) >> 3) |
		 ((vsyncstart & 0x200) >> 2));
	WREG_CRT(9, ((vdisplay & 0x200) >> 4) |
		 ((vdisplay & 0x200) >> 3));
	WREG_CRT(16, vsyncstart & 0xFF);
	WREG_CRT(17, (vsyncend & 0x0F) | 0x20);
	WREG_CRT(18, vdisplay & 0xFF);
	WREG_CRT(20, 0);
	WREG_CRT(21, vdisplay & 0xFF);
	WREG_CRT(22, (vtotal + 1) & 0xFF);
	WREG_CRT(23, 0xc3);
	WREG_CRT(24, vdisplay & 0xFF);

	WREG_ECRT(0x01, crtcext1);
	WREG_ECRT(0x02, crtcext2);
	WREG_ECRT(0x05, crtcext5);

	WREG8(MGA_MISC_OUT, misc);
पूर्ण

अटल u8 mgag200_get_bpp_shअगरt(काष्ठा mga_device *mdev,
				स्थिर काष्ठा drm_क्रमmat_info *क्रमmat)
अणु
	वापस mdev->bpp_shअगरts[क्रमmat->cpp[0] - 1];
पूर्ण

/*
 * Calculates the HW offset value from the framebuffer's pitch. The
 * offset is a multiple of the pixel size and depends on the display
 * क्रमmat.
 */
अटल u32 mgag200_calculate_offset(काष्ठा mga_device *mdev,
				    स्थिर काष्ठा drm_framebuffer *fb)
अणु
	u32 offset = fb->pitches[0] / fb->क्रमmat->cpp[0];
	u8 bppshअगरt = mgag200_get_bpp_shअगरt(mdev, fb->क्रमmat);

	अगर (fb->क्रमmat->cpp[0] * 8 == 24)
		offset = (offset * 3) >> (4 - bppshअगरt);
	अन्यथा
		offset = offset >> (4 - bppshअगरt);

	वापस offset;
पूर्ण

अटल व्योम mgag200_set_offset(काष्ठा mga_device *mdev,
			       स्थिर काष्ठा drm_framebuffer *fb)
अणु
	u8 crtc13, crtcext0;
	u32 offset = mgag200_calculate_offset(mdev, fb);

	RREG_ECRT(0, crtcext0);

	crtc13 = offset & 0xff;

	crtcext0 &= ~MGAREG_CRTCEXT0_OFFSET_MASK;
	crtcext0 |= (offset >> 4) & MGAREG_CRTCEXT0_OFFSET_MASK;

	WREG_CRT(0x13, crtc13);
	WREG_ECRT(0x00, crtcext0);
पूर्ण

अटल व्योम mgag200_set_क्रमmat_regs(काष्ठा mga_device *mdev,
				    स्थिर काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	स्थिर काष्ठा drm_क्रमmat_info *क्रमmat = fb->क्रमmat;
	अचिन्हित पूर्णांक bpp, bppshअगरt, scale;
	u8 crtcext3, xmulctrl;

	bpp = क्रमmat->cpp[0] * 8;

	bppshअगरt = mgag200_get_bpp_shअगरt(mdev, क्रमmat);
	चयन (bpp) अणु
	हाल 24:
		scale = ((1 << bppshअगरt) * 3) - 1;
		अवरोध;
	शेष:
		scale = (1 << bppshअगरt) - 1;
		अवरोध;
	पूर्ण

	RREG_ECRT(3, crtcext3);

	चयन (bpp) अणु
	हाल 8:
		xmulctrl = MGA1064_MUL_CTL_8bits;
		अवरोध;
	हाल 16:
		अगर (क्रमmat->depth == 15)
			xmulctrl = MGA1064_MUL_CTL_15bits;
		अन्यथा
			xmulctrl = MGA1064_MUL_CTL_16bits;
		अवरोध;
	हाल 24:
		xmulctrl = MGA1064_MUL_CTL_24bits;
		अवरोध;
	हाल 32:
		xmulctrl = MGA1064_MUL_CTL_32_24bits;
		अवरोध;
	शेष:
		/* BUG: We should have caught this problem alपढ़ोy. */
		drm_WARN_ON(dev, "invalid format depth\n");
		वापस;
	पूर्ण

	crtcext3 &= ~GENMASK(2, 0);
	crtcext3 |= scale;

	WREG_DAC(MGA1064_MUL_CTL, xmulctrl);

	WREG_GFX(0, 0x00);
	WREG_GFX(1, 0x00);
	WREG_GFX(2, 0x00);
	WREG_GFX(3, 0x00);
	WREG_GFX(4, 0x00);
	WREG_GFX(5, 0x40);
	WREG_GFX(6, 0x05);
	WREG_GFX(7, 0x0f);
	WREG_GFX(8, 0x0f);

	WREG_ECRT(3, crtcext3);
पूर्ण

अटल व्योम mgag200_g200er_reset_tagfअगरo(काष्ठा mga_device *mdev)
अणु
	अटल uपूर्णांक32_t RESET_FLAG = 0x00200000; /* unकरोcumented magic value */
	u32 memctl;

	memctl = RREG32(MGAREG_MEMCTL);

	memctl |= RESET_FLAG;
	WREG32(MGAREG_MEMCTL, memctl);

	udelay(1000);

	memctl &= ~RESET_FLAG;
	WREG32(MGAREG_MEMCTL, memctl);
पूर्ण

अटल व्योम mgag200_g200se_set_hiprilvl(काष्ठा mga_device *mdev,
					स्थिर काष्ठा drm_display_mode *mode,
					स्थिर काष्ठा drm_framebuffer *fb)
अणु
	u32 unique_rev_id = mdev->model.g200se.unique_rev_id;
	अचिन्हित पूर्णांक hiprilvl;
	u8 crtcext6;

	अगर  (unique_rev_id >= 0x04) अणु
		hiprilvl = 0;
	पूर्ण अन्यथा अगर (unique_rev_id >= 0x02) अणु
		अचिन्हित पूर्णांक bpp;
		अचिन्हित दीर्घ mb;

		अगर (fb->क्रमmat->cpp[0] * 8 > 16)
			bpp = 32;
		अन्यथा अगर (fb->क्रमmat->cpp[0] * 8 > 8)
			bpp = 16;
		अन्यथा
			bpp = 8;

		mb = (mode->घड़ी * bpp) / 1000;
		अगर (mb > 3100)
			hiprilvl = 0;
		अन्यथा अगर (mb > 2600)
			hiprilvl = 1;
		अन्यथा अगर (mb > 1900)
			hiprilvl = 2;
		अन्यथा अगर (mb > 1160)
			hiprilvl = 3;
		अन्यथा अगर (mb > 440)
			hiprilvl = 4;
		अन्यथा
			hiprilvl = 5;

	पूर्ण अन्यथा अगर (unique_rev_id >= 0x01) अणु
		hiprilvl = 3;
	पूर्ण अन्यथा अणु
		hiprilvl = 4;
	पूर्ण

	crtcext6 = hiprilvl; /* implicitly sets maxhipri to 0 */

	WREG_ECRT(0x06, crtcext6);
पूर्ण

अटल व्योम mgag200_g200ev_set_hiprilvl(काष्ठा mga_device *mdev)
अणु
	WREG_ECRT(0x06, 0x00);
पूर्ण

अटल व्योम mgag200_enable_display(काष्ठा mga_device *mdev)
अणु
	u8 seq0, seq1, crtcext1;

	RREG_SEQ(0x00, seq0);
	seq0 |= MGAREG_SEQ0_SYNCRST |
		MGAREG_SEQ0_ASYNCRST;
	WREG_SEQ(0x00, seq0);

	/*
	 * TODO: replace busy रुकोing with vblank IRQ; put
	 *       msleep(50) beक्रमe changing SCROFF
	 */
	mga_रुको_vsync(mdev);
	mga_रुको_busy(mdev);

	RREG_SEQ(0x01, seq1);
	seq1 &= ~MGAREG_SEQ1_SCROFF;
	WREG_SEQ(0x01, seq1);

	msleep(20);

	RREG_ECRT(0x01, crtcext1);
	crtcext1 &= ~MGAREG_CRTCEXT1_VSYNCOFF;
	crtcext1 &= ~MGAREG_CRTCEXT1_HSYNCOFF;
	WREG_ECRT(0x01, crtcext1);
पूर्ण

अटल व्योम mgag200_disable_display(काष्ठा mga_device *mdev)
अणु
	u8 seq0, seq1, crtcext1;

	RREG_SEQ(0x00, seq0);
	seq0 &= ~MGAREG_SEQ0_SYNCRST;
	WREG_SEQ(0x00, seq0);

	/*
	 * TODO: replace busy रुकोing with vblank IRQ; put
	 *       msleep(50) beक्रमe changing SCROFF
	 */
	mga_रुको_vsync(mdev);
	mga_रुको_busy(mdev);

	RREG_SEQ(0x01, seq1);
	seq1 |= MGAREG_SEQ1_SCROFF;
	WREG_SEQ(0x01, seq1);

	msleep(20);

	RREG_ECRT(0x01, crtcext1);
	crtcext1 |= MGAREG_CRTCEXT1_VSYNCOFF |
		    MGAREG_CRTCEXT1_HSYNCOFF;
	WREG_ECRT(0x01, crtcext1);
पूर्ण

/*
 * Connector
 */

अटल पूर्णांक mga_vga_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा mga_connector *mga_connector = to_mga_connector(connector);
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	edid = drm_get_edid(connector, &mga_connector->i2c->adapter);
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण
	वापस ret;
पूर्ण

अटल uपूर्णांक32_t mga_vga_calculate_mode_bandwidth(काष्ठा drm_display_mode *mode,
							पूर्णांक bits_per_pixel)
अणु
	uपूर्णांक32_t total_area, भागisor;
	uपूर्णांक64_t active_area, pixels_per_second, bandwidth;
	uपूर्णांक64_t bytes_per_pixel = (bits_per_pixel + 7) / 8;

	भागisor = 1024;

	अगर (!mode->htotal || !mode->vtotal || !mode->घड़ी)
		वापस 0;

	active_area = mode->hdisplay * mode->vdisplay;
	total_area = mode->htotal * mode->vtotal;

	pixels_per_second = active_area * mode->घड़ी * 1000;
	करो_भाग(pixels_per_second, total_area);

	bandwidth = pixels_per_second * bytes_per_pixel * 100;
	करो_भाग(bandwidth, भागisor);

	वापस (uपूर्णांक32_t)(bandwidth);
पूर्ण

#घोषणा MODE_BANDWIDTH	MODE_BAD

अटल क्रमागत drm_mode_status mga_vga_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा mga_device *mdev = to_mga_device(dev);
	पूर्णांक bpp = 32;

	अगर (IS_G200_SE(mdev)) अणु
		u32 unique_rev_id = mdev->model.g200se.unique_rev_id;

		अगर (unique_rev_id == 0x01) अणु
			अगर (mode->hdisplay > 1600)
				वापस MODE_VIRTUAL_X;
			अगर (mode->vdisplay > 1200)
				वापस MODE_VIRTUAL_Y;
			अगर (mga_vga_calculate_mode_bandwidth(mode, bpp)
				> (24400 * 1024))
				वापस MODE_BANDWIDTH;
		पूर्ण अन्यथा अगर (unique_rev_id == 0x02) अणु
			अगर (mode->hdisplay > 1920)
				वापस MODE_VIRTUAL_X;
			अगर (mode->vdisplay > 1200)
				वापस MODE_VIRTUAL_Y;
			अगर (mga_vga_calculate_mode_bandwidth(mode, bpp)
				> (30100 * 1024))
				वापस MODE_BANDWIDTH;
		पूर्ण अन्यथा अणु
			अगर (mga_vga_calculate_mode_bandwidth(mode, bpp)
				> (55000 * 1024))
				वापस MODE_BANDWIDTH;
		पूर्ण
	पूर्ण अन्यथा अगर (mdev->type == G200_WB) अणु
		अगर (mode->hdisplay > 1280)
			वापस MODE_VIRTUAL_X;
		अगर (mode->vdisplay > 1024)
			वापस MODE_VIRTUAL_Y;
		अगर (mga_vga_calculate_mode_bandwidth(mode, bpp) >
		    (31877 * 1024))
			वापस MODE_BANDWIDTH;
	पूर्ण अन्यथा अगर (mdev->type == G200_EV &&
		(mga_vga_calculate_mode_bandwidth(mode, bpp)
			> (32700 * 1024))) अणु
		वापस MODE_BANDWIDTH;
	पूर्ण अन्यथा अगर (mdev->type == G200_EH &&
		(mga_vga_calculate_mode_bandwidth(mode, bpp)
			> (37500 * 1024))) अणु
		वापस MODE_BANDWIDTH;
	पूर्ण अन्यथा अगर (mdev->type == G200_ER &&
		(mga_vga_calculate_mode_bandwidth(mode,
			bpp) > (55000 * 1024))) अणु
		वापस MODE_BANDWIDTH;
	पूर्ण

	अगर ((mode->hdisplay % 8) != 0 || (mode->hsync_start % 8) != 0 ||
	    (mode->hsync_end % 8) != 0 || (mode->htotal % 8) != 0) अणु
		वापस MODE_H_ILLEGAL;
	पूर्ण

	अगर (mode->crtc_hdisplay > 2048 || mode->crtc_hsync_start > 4096 ||
	    mode->crtc_hsync_end > 4096 || mode->crtc_htotal > 4096 ||
	    mode->crtc_vdisplay > 2048 || mode->crtc_vsync_start > 4096 ||
	    mode->crtc_vsync_end > 4096 || mode->crtc_vtotal > 4096) अणु
		वापस MODE_BAD;
	पूर्ण

	/* Validate the mode input by the user */
	अगर (connector->cmdline_mode.specअगरied) अणु
		अगर (connector->cmdline_mode.bpp_specअगरied)
			bpp = connector->cmdline_mode.bpp;
	पूर्ण

	अगर ((mode->hdisplay * mode->vdisplay * (bpp/8)) > mdev->vram_fb_available) अणु
		अगर (connector->cmdline_mode.specअगरied)
			connector->cmdline_mode.specअगरied = false;
		वापस MODE_BAD;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल व्योम mga_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा mga_connector *mga_connector = to_mga_connector(connector);
	mgag200_i2c_destroy(mga_connector->i2c);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs mga_vga_connector_helper_funcs = अणु
	.get_modes  = mga_vga_get_modes,
	.mode_valid = mga_vga_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs mga_vga_connector_funcs = अणु
	.reset                  = drm_atomic_helper_connector_reset,
	.fill_modes             = drm_helper_probe_single_connector_modes,
	.destroy                = mga_connector_destroy,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state   = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक mgag200_vga_connector_init(काष्ठा mga_device *mdev)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	काष्ठा mga_connector *mconnector = &mdev->connector;
	काष्ठा drm_connector *connector = &mconnector->base;
	काष्ठा mga_i2c_chan *i2c;
	पूर्णांक ret;

	i2c = mgag200_i2c_create(dev);
	अगर (!i2c)
		drm_warn(dev, "failed to add DDC bus\n");

	ret = drm_connector_init_with_ddc(dev, connector,
					  &mga_vga_connector_funcs,
					  DRM_MODE_CONNECTOR_VGA,
					  &i2c->adapter);
	अगर (ret)
		जाओ err_mgag200_i2c_destroy;
	drm_connector_helper_add(connector, &mga_vga_connector_helper_funcs);

	mconnector->i2c = i2c;

	वापस 0;

err_mgag200_i2c_destroy:
	mgag200_i2c_destroy(i2c);
	वापस ret;
पूर्ण

/*
 * Simple Display Pipe
 */

अटल क्रमागत drm_mode_status
mgag200_simple_display_pipe_mode_valid(काष्ठा drm_simple_display_pipe *pipe,
				       स्थिर काष्ठा drm_display_mode *mode)
अणु
	वापस MODE_OK;
पूर्ण

अटल व्योम
mgag200_handle_damage(काष्ठा mga_device *mdev, काष्ठा drm_framebuffer *fb,
		      काष्ठा drm_rect *clip, स्थिर काष्ठा dma_buf_map *map)
अणु
	व्योम *vmap = map->vaddr; /* TODO: Use mapping असलtraction properly */

	drm_fb_स_नकल_dstclip(mdev->vram, vmap, fb, clip);

	/* Always scanout image at VRAM offset 0 */
	mgag200_set_startadd(mdev, (u32)0);
	mgag200_set_offset(mdev, fb);
पूर्ण

अटल व्योम
mgag200_simple_display_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
				   काष्ठा drm_crtc_state *crtc_state,
				   काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा mga_device *mdev = to_mga_device(dev);
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->adjusted_mode;
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(plane_state);
	काष्ठा drm_rect fullscreen = अणु
		.x1 = 0,
		.x2 = fb->width,
		.y1 = 0,
		.y2 = fb->height,
	पूर्ण;

	अगर (mdev->type == G200_WB || mdev->type == G200_EW3)
		mgag200_g200wb_hold_bmc(mdev);

	mgag200_set_क्रमmat_regs(mdev, fb);
	mgag200_set_mode_regs(mdev, adjusted_mode);
	mgag200_crtc_set_plls(mdev, adjusted_mode->घड़ी);

	अगर (mdev->type == G200_ER)
		mgag200_g200er_reset_tagfअगरo(mdev);

	अगर (IS_G200_SE(mdev))
		mgag200_g200se_set_hiprilvl(mdev, adjusted_mode, fb);
	अन्यथा अगर (mdev->type == G200_EV)
		mgag200_g200ev_set_hiprilvl(mdev);

	अगर (mdev->type == G200_WB || mdev->type == G200_EW3)
		mgag200_g200wb_release_bmc(mdev);

	mga_crtc_load_lut(crtc);
	mgag200_enable_display(mdev);

	mgag200_handle_damage(mdev, fb, &fullscreen, &shaकरोw_plane_state->map[0]);
पूर्ण

अटल व्योम
mgag200_simple_display_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा mga_device *mdev = to_mga_device(crtc->dev);

	mgag200_disable_display(mdev);
पूर्ण

अटल पूर्णांक
mgag200_simple_display_pipe_check(काष्ठा drm_simple_display_pipe *pipe,
				  काष्ठा drm_plane_state *plane_state,
				  काष्ठा drm_crtc_state *crtc_state)
अणु
	काष्ठा drm_plane *plane = plane_state->plane;
	काष्ठा drm_framebuffer *new_fb = plane_state->fb;
	काष्ठा drm_framebuffer *fb = शून्य;

	अगर (!new_fb)
		वापस 0;

	अगर (plane->state)
		fb = plane->state->fb;

	अगर (!fb || (fb->क्रमmat != new_fb->क्रमmat))
		crtc_state->mode_changed = true; /* update PLL settings */

	वापस 0;
पूर्ण

अटल व्योम
mgag200_simple_display_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
				   काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा mga_device *mdev = to_mga_device(dev);
	काष्ठा drm_plane_state *state = plane->state;
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state = to_drm_shaकरोw_plane_state(state);
	काष्ठा drm_framebuffer *fb = state->fb;
	काष्ठा drm_rect damage;

	अगर (!fb)
		वापस;

	अगर (drm_atomic_helper_damage_merged(old_state, state, &damage))
		mgag200_handle_damage(mdev, fb, &damage, &shaकरोw_plane_state->map[0]);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs
mgag200_simple_display_pipe_funcs = अणु
	.mode_valid = mgag200_simple_display_pipe_mode_valid,
	.enable	    = mgag200_simple_display_pipe_enable,
	.disable    = mgag200_simple_display_pipe_disable,
	.check	    = mgag200_simple_display_pipe_check,
	.update	    = mgag200_simple_display_pipe_update,
	DRM_GEM_SIMPLE_DISPLAY_PIPE_SHADOW_PLANE_FUNCS,
पूर्ण;

अटल स्थिर uपूर्णांक32_t mgag200_simple_display_pipe_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_RGB888,
पूर्ण;

अटल स्थिर uपूर्णांक64_t mgag200_simple_display_pipe_fmपंचांगods[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

/*
 * Mode config
 */

अटल स्थिर काष्ठा drm_mode_config_funcs mgag200_mode_config_funcs = अणु
	.fb_create     = drm_gem_fb_create_with_dirty,
	.atomic_check  = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल अचिन्हित पूर्णांक mgag200_preferred_depth(काष्ठा mga_device *mdev)
अणु
	अगर (IS_G200_SE(mdev) && mdev->vram_fb_available < (2048*1024))
		वापस 16;
	अन्यथा
		वापस 32;
पूर्ण

पूर्णांक mgag200_modeset_init(काष्ठा mga_device *mdev)
अणु
	काष्ठा drm_device *dev = &mdev->base;
	काष्ठा drm_connector *connector = &mdev->connector.base;
	काष्ठा drm_simple_display_pipe *pipe = &mdev->display_pipe;
	माप_प्रकार क्रमmat_count = ARRAY_SIZE(mgag200_simple_display_pipe_क्रमmats);
	पूर्णांक ret;

	mdev->bpp_shअगरts[0] = 0;
	mdev->bpp_shअगरts[1] = 1;
	mdev->bpp_shअगरts[2] = 0;
	mdev->bpp_shअगरts[3] = 2;

	mgag200_init_regs(mdev);

	ret = drmm_mode_config_init(dev);
	अगर (ret) अणु
		drm_err(dev, "drmm_mode_config_init() failed, error %d\n",
			ret);
		वापस ret;
	पूर्ण

	dev->mode_config.max_width = MGAG200_MAX_FB_WIDTH;
	dev->mode_config.max_height = MGAG200_MAX_FB_HEIGHT;

	dev->mode_config.preferred_depth = mgag200_preferred_depth(mdev);

	dev->mode_config.fb_base = mdev->mc.vram_base;

	dev->mode_config.funcs = &mgag200_mode_config_funcs;

	ret = mgag200_vga_connector_init(mdev);
	अगर (ret) अणु
		drm_err(dev,
			"mgag200_vga_connector_init() failed, error %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = drm_simple_display_pipe_init(dev, pipe,
					   &mgag200_simple_display_pipe_funcs,
					   mgag200_simple_display_pipe_क्रमmats,
					   क्रमmat_count,
					   mgag200_simple_display_pipe_fmपंचांगods,
					   connector);
	अगर (ret) अणु
		drm_err(dev,
			"drm_simple_display_pipe_init() failed, error %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* FIXME: legacy gamma tables; convert to CRTC state */
	drm_mode_crtc_set_gamma_size(&pipe->crtc, MGAG200_LUT_SIZE);

	drm_mode_config_reset(dev);

	वापस 0;
पूर्ण
