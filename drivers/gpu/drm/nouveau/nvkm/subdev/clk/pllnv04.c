<शैली गुरु>
/*
 * Copyright 1993-2003 NVIDIA, Corporation
 * Copyright 2007-2009 Stuart Bennett
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश "pll.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>

अटल पूर्णांक
getMNP_single(काष्ठा nvkm_subdev *subdev, काष्ठा nvbios_pll *info, पूर्णांक clk,
	      पूर्णांक *pN, पूर्णांक *pM, पूर्णांक *pP)
अणु
	/* Find M, N and P क्रम a single stage PLL
	 *
	 * Note that some bioses (NV3x) have lookup tables of precomputed MNP
	 * values, but we're too lazy to use those aपंचांग
	 *
	 * "clk" parameter in kHz
	 * वापसs calculated घड़ी
	 */
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	पूर्णांक minvco = info->vco1.min_freq, maxvco = info->vco1.max_freq;
	पूर्णांक minM = info->vco1.min_m, maxM = info->vco1.max_m;
	पूर्णांक minN = info->vco1.min_n, maxN = info->vco1.max_n;
	पूर्णांक minU = info->vco1.min_inputfreq;
	पूर्णांक maxU = info->vco1.max_inputfreq;
	पूर्णांक minP = info->min_p;
	पूर्णांक maxP = info->max_p_usable;
	पूर्णांक crystal = info->refclk;
	पूर्णांक M, N, thisP, P;
	पूर्णांक clkP, calcclk;
	पूर्णांक delta, bestdelta = पूर्णांक_उच्च;
	पूर्णांक bestclk = 0;

	/* this भागision verअगरied क्रम nv20, nv18, nv28 (Haiku), and nv34 */
	/* possibly correlated with पूर्णांकroduction of 27MHz crystal */
	अगर (bios->version.major < 0x60) अणु
		पूर्णांक cv = bios->version.chip;
		अगर (cv < 0x17 || cv == 0x1a || cv == 0x20) अणु
			अगर (clk > 250000)
				maxM = 6;
			अगर (clk > 340000)
				maxM = 2;
		पूर्ण अन्यथा अगर (cv < 0x40) अणु
			अगर (clk > 150000)
				maxM = 6;
			अगर (clk > 200000)
				maxM = 4;
			अगर (clk > 340000)
				maxM = 2;
		पूर्ण
	पूर्ण

	P = 1 << maxP;
	अगर ((clk * P) < minvco) अणु
		minvco = clk * maxP;
		maxvco = minvco * 2;
	पूर्ण

	अगर (clk + clk/200 > maxvco)	/* +0.5% */
		maxvco = clk + clk/200;

	/* NV34 goes maxlog2P->0, NV20 goes 0->maxlog2P */
	क्रम (thisP = minP; thisP <= maxP; thisP++) अणु
		P = 1 << thisP;
		clkP = clk * P;

		अगर (clkP < minvco)
			जारी;
		अगर (clkP > maxvco)
			वापस bestclk;

		क्रम (M = minM; M <= maxM; M++) अणु
			अगर (crystal/M < minU)
				वापस bestclk;
			अगर (crystal/M > maxU)
				जारी;

			/* add crystal/2 to round better */
			N = (clkP * M + crystal/2) / crystal;

			अगर (N < minN)
				जारी;
			अगर (N > maxN)
				अवरोध;

			/* more rounding additions */
			calcclk = ((N * crystal + P/2) / P + M/2) / M;
			delta = असल(calcclk - clk);
			/* we करो an exhaustive search rather than terminating
			 * on an optimality condition...
			 */
			अगर (delta < bestdelta) अणु
				bestdelta = delta;
				bestclk = calcclk;
				*pN = N;
				*pM = M;
				*pP = thisP;
				अगर (delta == 0)	/* except this one */
					वापस bestclk;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस bestclk;
पूर्ण

अटल पूर्णांक
getMNP_द्विगुन(काष्ठा nvkm_subdev *subdev, काष्ठा nvbios_pll *info, पूर्णांक clk,
	      पूर्णांक *pN1, पूर्णांक *pM1, पूर्णांक *pN2, पूर्णांक *pM2, पूर्णांक *pP)
अणु
	/* Find M, N and P क्रम a two stage PLL
	 *
	 * Note that some bioses (NV30+) have lookup tables of precomputed MNP
	 * values, but we're too lazy to use those aपंचांग
	 *
	 * "clk" parameter in kHz
	 * वापसs calculated घड़ी
	 */
	पूर्णांक chip_version = subdev->device->bios->version.chip;
	पूर्णांक minvco1 = info->vco1.min_freq, maxvco1 = info->vco1.max_freq;
	पूर्णांक minvco2 = info->vco2.min_freq, maxvco2 = info->vco2.max_freq;
	पूर्णांक minU1 = info->vco1.min_inputfreq, minU2 = info->vco2.min_inputfreq;
	पूर्णांक maxU1 = info->vco1.max_inputfreq, maxU2 = info->vco2.max_inputfreq;
	पूर्णांक minM1 = info->vco1.min_m, maxM1 = info->vco1.max_m;
	पूर्णांक minN1 = info->vco1.min_n, maxN1 = info->vco1.max_n;
	पूर्णांक minM2 = info->vco2.min_m, maxM2 = info->vco2.max_m;
	पूर्णांक minN2 = info->vco2.min_n, maxN2 = info->vco2.max_n;
	पूर्णांक maxlog2P = info->max_p_usable;
	पूर्णांक crystal = info->refclk;
	bool fixedgain2 = (minM2 == maxM2 && minN2 == maxN2);
	पूर्णांक M1, N1, M2, N2, log2P;
	पूर्णांक clkP, calcclk1, calcclk2, calcclkout;
	पूर्णांक delta, bestdelta = पूर्णांक_उच्च;
	पूर्णांक bestclk = 0;

	पूर्णांक vco2 = (maxvco2 - maxvco2/200) / 2;
	क्रम (log2P = 0; clk && log2P < maxlog2P && clk <= (vco2 >> log2P); log2P++)
		;
	clkP = clk << log2P;

	अगर (maxvco2 < clk + clk/200)	/* +0.5% */
		maxvco2 = clk + clk/200;

	क्रम (M1 = minM1; M1 <= maxM1; M1++) अणु
		अगर (crystal/M1 < minU1)
			वापस bestclk;
		अगर (crystal/M1 > maxU1)
			जारी;

		क्रम (N1 = minN1; N1 <= maxN1; N1++) अणु
			calcclk1 = crystal * N1 / M1;
			अगर (calcclk1 < minvco1)
				जारी;
			अगर (calcclk1 > maxvco1)
				अवरोध;

			क्रम (M2 = minM2; M2 <= maxM2; M2++) अणु
				अगर (calcclk1/M2 < minU2)
					अवरोध;
				अगर (calcclk1/M2 > maxU2)
					जारी;

				/* add calcclk1/2 to round better */
				N2 = (clkP * M2 + calcclk1/2) / calcclk1;
				अगर (N2 < minN2)
					जारी;
				अगर (N2 > maxN2)
					अवरोध;

				अगर (!fixedgain2) अणु
					अगर (chip_version < 0x60)
						अगर (N2/M2 < 4 || N2/M2 > 10)
							जारी;

					calcclk2 = calcclk1 * N2 / M2;
					अगर (calcclk2 < minvco2)
						अवरोध;
					अगर (calcclk2 > maxvco2)
						जारी;
				पूर्ण अन्यथा
					calcclk2 = calcclk1;

				calcclkout = calcclk2 >> log2P;
				delta = असल(calcclkout - clk);
				/* we करो an exhaustive search rather than terminating
				 * on an optimality condition...
				 */
				अगर (delta < bestdelta) अणु
					bestdelta = delta;
					bestclk = calcclkout;
					*pN1 = N1;
					*pM1 = M1;
					*pN2 = N2;
					*pM2 = M2;
					*pP = log2P;
					अगर (delta == 0)	/* except this one */
						वापस bestclk;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस bestclk;
पूर्ण

पूर्णांक
nv04_pll_calc(काष्ठा nvkm_subdev *subdev, काष्ठा nvbios_pll *info, u32 freq,
	      पूर्णांक *N1, पूर्णांक *M1, पूर्णांक *N2, पूर्णांक *M2, पूर्णांक *P)
अणु
	पूर्णांक ret;

	अगर (!info->vco2.max_freq || !N2) अणु
		ret = getMNP_single(subdev, info, freq, N1, M1, P);
		अगर (N2) अणु
			*N2 = 1;
			*M2 = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = getMNP_द्विगुन(subdev, info, freq, N1, M1, N2, M2, P);
	पूर्ण

	अगर (!ret)
		nvkm_error(subdev, "unable to compute acceptable pll values\n");
	वापस ret;
पूर्ण
