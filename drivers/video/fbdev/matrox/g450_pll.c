<शैली गुरु>
/*
 *
 * Hardware accelerated Matrox PCI cards - G450/G550 PLL control.
 *
 * (c) 2001-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
 *
 * Portions Copyright (c) 2001 Matrox Graphics Inc.
 *
 * Version: 1.64 2002/06/10
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 */

#समावेश "g450_pll.h"
#समावेश "matroxfb_DAC1064.h"

अटल अंतरभूत अचिन्हित पूर्णांक g450_vco2f(अचिन्हित अक्षर p, अचिन्हित पूर्णांक fvco) अणु
	वापस (p & 0x40) ? fvco : fvco >> ((p & 3) + 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक g450_f2vco(अचिन्हित अक्षर p, अचिन्हित पूर्णांक fin) अणु
	वापस (p & 0x40) ? fin : fin << ((p & 3) + 1);
पूर्ण

अटल अचिन्हित पूर्णांक g450_mnp2vco(स्थिर काष्ठा matrox_fb_info *minfo,
				 अचिन्हित पूर्णांक mnp)
अणु
	अचिन्हित पूर्णांक m, n;

	m = ((mnp >> 16) & 0x0FF) + 1;
	n = ((mnp >>  7) & 0x1FE) + 4;
	वापस (minfo->features.pll.ref_freq * n + (m >> 1)) / m;
पूर्ण

अचिन्हित पूर्णांक g450_mnp2f(स्थिर काष्ठा matrox_fb_info *minfo, अचिन्हित पूर्णांक mnp)
अणु
	वापस g450_vco2f(mnp, g450_mnp2vco(minfo, mnp));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pll_freq_delta(अचिन्हित पूर्णांक f1, अचिन्हित पूर्णांक f2) अणु
	अगर (f2 < f1) अणु
    		f2 = f1 - f2;
	पूर्ण अन्यथा अणु
		f2 = f2 - f1;
	पूर्ण
	वापस f2;
पूर्ण

#घोषणा NO_MORE_MNP	0x01FFFFFF
#घोषणा G450_MNP_FREQBITS	(0xFFFFFF43)	/* करो not mask high byte so we'll catch NO_MORE_MNP */

अटल अचिन्हित पूर्णांक g450_nextpll(स्थिर काष्ठा matrox_fb_info *minfo,
				 स्थिर काष्ठा matrox_pll_limits *pi,
				 अचिन्हित पूर्णांक *fvco, अचिन्हित पूर्णांक mnp)
अणु
	अचिन्हित पूर्णांक m, n, p;
	अचिन्हित पूर्णांक tvco = *fvco;

	m = (mnp >> 16) & 0xFF;
	p = mnp & 0xFF;

	करो अणु
		अगर (m == 0 || m == 0xFF) अणु
			अगर (m == 0) अणु
				अगर (p & 0x40) अणु
					वापस NO_MORE_MNP;
				पूर्ण
			        अगर (p & 3) अणु
					p--;
				पूर्ण अन्यथा अणु
					p = 0x40;
				पूर्ण
				tvco >>= 1;
				अगर (tvco < pi->vcomin) अणु
					वापस NO_MORE_MNP;
				पूर्ण
				*fvco = tvco;
			पूर्ण

			p &= 0x43;
			अगर (tvco < 550000) अणु
/*				p |= 0x00; */
			पूर्ण अन्यथा अगर (tvco < 700000) अणु
				p |= 0x08;
			पूर्ण अन्यथा अगर (tvco < 1000000) अणु
				p |= 0x10;
			पूर्ण अन्यथा अगर (tvco < 1150000) अणु
				p |= 0x18;
			पूर्ण अन्यथा अणु
				p |= 0x20;
			पूर्ण
			m = 9;
		पूर्ण अन्यथा अणु
			m--;
		पूर्ण
		n = ((tvco * (m+1) + minfo->features.pll.ref_freq) / (minfo->features.pll.ref_freq * 2)) - 2;
	पूर्ण जबतक (n < 0x03 || n > 0x7A);
	वापस (m << 16) | (n << 8) | p;
पूर्ण

अटल अचिन्हित पूर्णांक g450_firstpll(स्थिर काष्ठा matrox_fb_info *minfo,
				  स्थिर काष्ठा matrox_pll_limits *pi,
				  अचिन्हित पूर्णांक *vco, अचिन्हित पूर्णांक fout)
अणु
	अचिन्हित पूर्णांक p;
	अचिन्हित पूर्णांक vcomax;

	vcomax = pi->vcomax;
	अगर (fout > (vcomax / 2)) अणु
		अगर (fout > vcomax) अणु
			*vco = vcomax;
		पूर्ण अन्यथा अणु
			*vco = fout;
		पूर्ण
		p = 0x40;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक tvco;

		p = 3;
		tvco = g450_f2vco(p, fout);
		जबतक (p && (tvco > vcomax)) अणु
			p--;
			tvco >>= 1;
		पूर्ण
		अगर (tvco < pi->vcomin) अणु
			tvco = pi->vcomin;
		पूर्ण
		*vco = tvco;
	पूर्ण
	वापस g450_nextpll(minfo, pi, vco, 0xFF0000 | p);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक g450_setpll(स्थिर काष्ठा matrox_fb_info *minfo,
				       अचिन्हित पूर्णांक mnp, अचिन्हित पूर्णांक pll)
अणु
	चयन (pll) अणु
		हाल M_PIXEL_PLL_A:
			matroxfb_DAC_out(minfo, M1064_XPIXPLLAM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLAN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLAP, mnp);
			वापस M1064_XPIXPLLSTAT;

		हाल M_PIXEL_PLL_B:
			matroxfb_DAC_out(minfo, M1064_XPIXPLLBM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLBN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLBP, mnp);
			वापस M1064_XPIXPLLSTAT;

		हाल M_PIXEL_PLL_C:
			matroxfb_DAC_out(minfo, M1064_XPIXPLLCM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLCN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XPIXPLLCP, mnp);
			वापस M1064_XPIXPLLSTAT;

		हाल M_SYSTEM_PLL:
			matroxfb_DAC_out(minfo, DAC1064_XSYSPLLM, mnp >> 16);
			matroxfb_DAC_out(minfo, DAC1064_XSYSPLLN, mnp >> 8);
			matroxfb_DAC_out(minfo, DAC1064_XSYSPLLP, mnp);
			वापस DAC1064_XSYSPLLSTAT;

		हाल M_VIDEO_PLL:
			matroxfb_DAC_out(minfo, M1064_XVIDPLLM, mnp >> 16);
			matroxfb_DAC_out(minfo, M1064_XVIDPLLN, mnp >> 8);
			matroxfb_DAC_out(minfo, M1064_XVIDPLLP, mnp);
			वापस M1064_XVIDPLLSTAT;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक g450_cmppll(स्थिर काष्ठा matrox_fb_info *minfo,
				       अचिन्हित पूर्णांक mnp, अचिन्हित पूर्णांक pll)
अणु
	अचिन्हित अक्षर m = mnp >> 16;
	अचिन्हित अक्षर n = mnp >> 8;
	अचिन्हित अक्षर p = mnp;

	चयन (pll) अणु
		हाल M_PIXEL_PLL_A:
			वापस (matroxfb_DAC_in(minfo, M1064_XPIXPLLAM) != m ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLAN) != n ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLAP) != p);

		हाल M_PIXEL_PLL_B:
			वापस (matroxfb_DAC_in(minfo, M1064_XPIXPLLBM) != m ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLBN) != n ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLBP) != p);

		हाल M_PIXEL_PLL_C:
			वापस (matroxfb_DAC_in(minfo, M1064_XPIXPLLCM) != m ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLCN) != n ||
				matroxfb_DAC_in(minfo, M1064_XPIXPLLCP) != p);

		हाल M_SYSTEM_PLL:
			वापस (matroxfb_DAC_in(minfo, DAC1064_XSYSPLLM) != m ||
				matroxfb_DAC_in(minfo, DAC1064_XSYSPLLN) != n ||
				matroxfb_DAC_in(minfo, DAC1064_XSYSPLLP) != p);

		हाल M_VIDEO_PLL:
			वापस (matroxfb_DAC_in(minfo, M1064_XVIDPLLM) != m ||
				matroxfb_DAC_in(minfo, M1064_XVIDPLLN) != n ||
				matroxfb_DAC_in(minfo, M1064_XVIDPLLP) != p);
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक g450_isplllocked(स्थिर काष्ठा matrox_fb_info *minfo,
				   अचिन्हित पूर्णांक regidx)
अणु
	अचिन्हित पूर्णांक j;

	क्रम (j = 0; j < 1000; j++) अणु
		अगर (matroxfb_DAC_in(minfo, regidx) & 0x40) अणु
			अचिन्हित पूर्णांक r = 0;
			पूर्णांक i;

			क्रम (i = 0; i < 100; i++) अणु
				r += matroxfb_DAC_in(minfo, regidx) & 0x40;
			पूर्ण
			वापस r >= (90 * 0x40);
		पूर्ण
		/* udelay(1)... but DAC_in is much slower... */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक g450_testpll(स्थिर काष्ठा matrox_fb_info *minfo, अचिन्हित पूर्णांक mnp,
			अचिन्हित पूर्णांक pll)
अणु
	वापस g450_isplllocked(minfo, g450_setpll(minfo, mnp, pll));
पूर्ण

अटल व्योम updatehwstate_clk(काष्ठा matrox_hw_state* hw, अचिन्हित पूर्णांक mnp, अचिन्हित पूर्णांक pll) अणु
	चयन (pll) अणु
		हाल M_SYSTEM_PLL:
			hw->DACclk[3] = mnp >> 16;
			hw->DACclk[4] = mnp >> 8;
			hw->DACclk[5] = mnp;
			अवरोध;
	पूर्ण
पूर्ण

व्योम matroxfb_g450_setpll_cond(काष्ठा matrox_fb_info *minfo, अचिन्हित पूर्णांक mnp,
			       अचिन्हित पूर्णांक pll)
अणु
	अगर (g450_cmppll(minfo, mnp, pll)) अणु
		g450_setpll(minfo, mnp, pll);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक g450_findworkingpll(काष्ठा matrox_fb_info *minfo,
					       अचिन्हित पूर्णांक pll,
					       अचिन्हित पूर्णांक *mnparray,
					       अचिन्हित पूर्णांक mnpcount)
अणु
	अचिन्हित पूर्णांक found = 0;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक mnpfound = mnparray[0];
		
	क्रम (idx = 0; idx < mnpcount; idx++) अणु
		अचिन्हित पूर्णांक sarray[3];
		अचिन्हित पूर्णांक *sptr;
		अणु
			अचिन्हित पूर्णांक mnp;
		
			sptr = sarray;
			mnp = mnparray[idx];
			अगर (mnp & 0x38) अणु
				*sptr++ = mnp - 8;
			पूर्ण
			अगर ((mnp & 0x38) != 0x38) अणु
				*sptr++ = mnp + 8;
			पूर्ण
			*sptr = mnp;
		पूर्ण
		जबतक (sptr >= sarray) अणु
			अचिन्हित पूर्णांक mnp = *sptr--;
		
			अगर (g450_testpll(minfo, mnp - 0x0300, pll) &&
			    g450_testpll(minfo, mnp + 0x0300, pll) &&
			    g450_testpll(minfo, mnp - 0x0200, pll) &&
			    g450_testpll(minfo, mnp + 0x0200, pll) &&
			    g450_testpll(minfo, mnp - 0x0100, pll) &&
			    g450_testpll(minfo, mnp + 0x0100, pll)) अणु
				अगर (g450_testpll(minfo, mnp, pll)) अणु
					वापस mnp;
				पूर्ण
			पूर्ण अन्यथा अगर (!found && g450_testpll(minfo, mnp, pll)) अणु
				mnpfound = mnp;
				found = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	g450_setpll(minfo, mnpfound, pll);
	वापस mnpfound;
पूर्ण

अटल व्योम g450_addcache(काष्ठा matrox_pll_cache* ci, अचिन्हित पूर्णांक mnp_key, अचिन्हित पूर्णांक mnp_value) अणु
	अगर (++ci->valid > ARRAY_SIZE(ci->data)) अणु
		ci->valid = ARRAY_SIZE(ci->data);
	पूर्ण
	स_हटाओ(ci->data + 1, ci->data, (ci->valid - 1) * माप(*ci->data));
	ci->data[0].mnp_key = mnp_key & G450_MNP_FREQBITS;
	ci->data[0].mnp_value = mnp_value;
पूर्ण

अटल पूर्णांक g450_checkcache(काष्ठा matrox_fb_info *minfo,
			   काष्ठा matrox_pll_cache *ci, अचिन्हित पूर्णांक mnp_key)
अणु
	अचिन्हित पूर्णांक i;
	
	mnp_key &= G450_MNP_FREQBITS;
	क्रम (i = 0; i < ci->valid; i++) अणु
		अगर (ci->data[i].mnp_key == mnp_key) अणु
			अचिन्हित पूर्णांक mnp;
			
			mnp = ci->data[i].mnp_value;
			अगर (i) अणु
				स_हटाओ(ci->data + 1, ci->data, i * माप(*ci->data));
				ci->data[0].mnp_key = mnp_key;
				ci->data[0].mnp_value = mnp;
			पूर्ण
			वापस mnp;
		पूर्ण
	पूर्ण
	वापस NO_MORE_MNP;
पूर्ण

अटल पूर्णांक __g450_setclk(काष्ठा matrox_fb_info *minfo, अचिन्हित पूर्णांक fout,
			 अचिन्हित पूर्णांक pll, अचिन्हित पूर्णांक *mnparray,
			 अचिन्हित पूर्णांक *deltaarray)
अणु
	अचिन्हित पूर्णांक mnpcount;
	स्थिर काष्ठा matrox_pll_limits* pi;
	काष्ठा matrox_pll_cache* ci;

	चयन (pll) अणु
		हाल M_PIXEL_PLL_A:
		हाल M_PIXEL_PLL_B:
		हाल M_PIXEL_PLL_C:
			अणु
				u_पूर्णांक8_t पंचांगp, xpwrctrl;
				अचिन्हित दीर्घ flags;
				
				matroxfb_DAC_lock_irqsave(flags);

				xpwrctrl = matroxfb_DAC_in(minfo, M1064_XPWRCTRL);
				matroxfb_DAC_out(minfo, M1064_XPWRCTRL, xpwrctrl & ~M1064_XPWRCTRL_PANELPDN);
				mga_outb(M_SEQ_INDEX, M_SEQ1);
				mga_outb(M_SEQ_DATA, mga_inb(M_SEQ_DATA) | M_SEQ1_SCROFF);
				पंचांगp = matroxfb_DAC_in(minfo, M1064_XPIXCLKCTRL);
				पंचांगp |= M1064_XPIXCLKCTRL_DIS;
				अगर (!(पंचांगp & M1064_XPIXCLKCTRL_PLL_UP)) अणु
					पंचांगp |= M1064_XPIXCLKCTRL_PLL_UP;
				पूर्ण
				matroxfb_DAC_out(minfo, M1064_XPIXCLKCTRL, पंचांगp);
				/* DVI PLL preferred क्रम frequencies up to
				   panel link max, standard PLL otherwise */
				अगर (fout >= minfo->max_pixel_घड़ी_panellink)
					पंचांगp = 0;
				अन्यथा पंचांगp =
					M1064_XDVICLKCTRL_DVIDATAPATHSEL |
					M1064_XDVICLKCTRL_C1DVICLKSEL |
					M1064_XDVICLKCTRL_C1DVICLKEN |
					M1064_XDVICLKCTRL_DVILOOPCTL |
					M1064_XDVICLKCTRL_P1LOOPBWDTCTL;
                                /* Setting this अवरोधs PC प्रणालीs so करोn't करो it */
				/* matroxfb_DAC_out(minfo, M1064_XDVICLKCTRL, पंचांगp); */
				matroxfb_DAC_out(minfo, M1064_XPWRCTRL,
						 xpwrctrl);

				matroxfb_DAC_unlock_irqrestore(flags);
			पूर्ण
			अणु
				u_पूर्णांक8_t misc;
		
				misc = mga_inb(M_MISC_REG_READ) & ~0x0C;
				चयन (pll) अणु
					हाल M_PIXEL_PLL_A:
						अवरोध;
					हाल M_PIXEL_PLL_B:
						misc |=  0x04;
						अवरोध;
					शेष:
						misc |=  0x0C;
						अवरोध;
				पूर्ण
				mga_outb(M_MISC_REG, misc);
			पूर्ण
			pi = &minfo->limits.pixel;
			ci = &minfo->cache.pixel;
			अवरोध;
		हाल M_SYSTEM_PLL:
			अणु
				u_पूर्णांक32_t opt;

				pci_पढ़ो_config_dword(minfo->pcidev, PCI_OPTION_REG, &opt);
				अगर (!(opt & 0x20)) अणु
					pci_ग_लिखो_config_dword(minfo->pcidev, PCI_OPTION_REG, opt | 0x20);
				पूर्ण
			पूर्ण
			pi = &minfo->limits.प्रणाली;
			ci = &minfo->cache.प्रणाली;
			अवरोध;
		हाल M_VIDEO_PLL:
			अणु
				u_पूर्णांक8_t पंचांगp;
				अचिन्हित पूर्णांक mnp;
				अचिन्हित दीर्घ flags;
				
				matroxfb_DAC_lock_irqsave(flags);
				पंचांगp = matroxfb_DAC_in(minfo, M1064_XPWRCTRL);
				अगर (!(पंचांगp & 2)) अणु
					matroxfb_DAC_out(minfo, M1064_XPWRCTRL, पंचांगp | 2);
				पूर्ण
				
				mnp = matroxfb_DAC_in(minfo, M1064_XPIXPLLCM) << 16;
				mnp |= matroxfb_DAC_in(minfo, M1064_XPIXPLLCN) << 8;
				matroxfb_DAC_unlock_irqrestore(flags);
			पूर्ण
			pi = &minfo->limits.video;
			ci = &minfo->cache.video;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	mnpcount = 0;
	अणु
		अचिन्हित पूर्णांक mnp;
		अचिन्हित पूर्णांक xvco;

		क्रम (mnp = g450_firstpll(minfo, pi, &xvco, fout); mnp != NO_MORE_MNP; mnp = g450_nextpll(minfo, pi, &xvco, mnp)) अणु
			अचिन्हित पूर्णांक idx;
			अचिन्हित पूर्णांक vco;
			अचिन्हित पूर्णांक delta;

			vco = g450_mnp2vco(minfo, mnp);
			delta = pll_freq_delta(fout, g450_vco2f(mnp, vco));
			क्रम (idx = mnpcount; idx > 0; idx--) अणु
				/* == is important; due to nextpll algorithm we get
				   sorted equally good frequencies from lower VCO 
				   frequency to higher - with <= lowest wins, जबतक
				   with < highest one wins */
				अगर (delta <= deltaarray[idx-1]) अणु
					/* all अन्यथा being equal except VCO,
					 * choose VCO not near (within 1/16th or so) VCOmin
					 * (freqs near VCOmin aren't as stable)
					 */
					अगर (delta == deltaarray[idx-1]
					    && vco != g450_mnp2vco(minfo, mnparray[idx-1])
					    && vco < (pi->vcomin * 17 / 16)) अणु
						अवरोध;
					पूर्ण
					mnparray[idx] = mnparray[idx-1];
					deltaarray[idx] = deltaarray[idx-1];
				पूर्ण अन्यथा अणु
					अवरोध;
				पूर्ण
			पूर्ण
			mnparray[idx] = mnp;
			deltaarray[idx] = delta;
			mnpcount++;
		पूर्ण
	पूर्ण
	/* VideoPLL and PixelPLL matched: करो nothing... In all other हालs we should get at least one frequency */
	अगर (!mnpcount) अणु
		वापस -EBUSY;
	पूर्ण
	अणु
		अचिन्हित दीर्घ flags;
		अचिन्हित पूर्णांक mnp;
		
		matroxfb_DAC_lock_irqsave(flags);
		mnp = g450_checkcache(minfo, ci, mnparray[0]);
		अगर (mnp != NO_MORE_MNP) अणु
			matroxfb_g450_setpll_cond(minfo, mnp, pll);
		पूर्ण अन्यथा अणु
			mnp = g450_findworkingpll(minfo, pll, mnparray, mnpcount);
			g450_addcache(ci, mnparray[0], mnp);
		पूर्ण
		updatehwstate_clk(&minfo->hw, mnp, pll);
		matroxfb_DAC_unlock_irqrestore(flags);
		वापस mnp;
	पूर्ण
पूर्ण

/* It must be greater than number of possible PLL values.
 * Currently there is 5(p) * 10(m) = 50 possible values. */
#घोषणा MNP_TABLE_SIZE  64

पूर्णांक matroxfb_g450_setclk(काष्ठा matrox_fb_info *minfo, अचिन्हित पूर्णांक fout,
			 अचिन्हित पूर्णांक pll)
अणु
	अचिन्हित पूर्णांक* arr;
	
	arr = kदो_स्मृति(माप(*arr) * MNP_TABLE_SIZE * 2, GFP_KERNEL);
	अगर (arr) अणु
		पूर्णांक r;

		r = __g450_setclk(minfo, fout, pll, arr, arr + MNP_TABLE_SIZE);
		kमुक्त(arr);
		वापस r;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

EXPORT_SYMBOL(matroxfb_g450_setclk);
EXPORT_SYMBOL(g450_mnp2f);
EXPORT_SYMBOL(matroxfb_g450_setpll_cond);

MODULE_AUTHOR("(c) 2001-2002 Petr Vandrovec <vandrove@vc.cvut.cz>");
MODULE_DESCRIPTION("Matrox G450/G550 PLL driver");

MODULE_LICENSE("GPL");
