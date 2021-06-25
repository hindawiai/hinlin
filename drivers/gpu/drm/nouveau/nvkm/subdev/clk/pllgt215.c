<शैली गुरु>
/*
 * Copyright 2010 Red Hat Inc.
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
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश "pll.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>

पूर्णांक
gt215_pll_calc(काष्ठा nvkm_subdev *subdev, काष्ठा nvbios_pll *info,
	       u32 freq, पूर्णांक *pN, पूर्णांक *pfN, पूर्णांक *pM, पूर्णांक *P)
अणु
	u32 best_err = ~0, err;
	पूर्णांक M, lM, hM, N, fN;

	*P = info->vco1.max_freq / freq;
	अगर (*P > info->max_p)
		*P = info->max_p;
	अगर (*P < info->min_p)
		*P = info->min_p;

	lM = (info->refclk + info->vco1.max_inputfreq) / info->vco1.max_inputfreq;
	lM = max(lM, (पूर्णांक)info->vco1.min_m);
	hM = (info->refclk + info->vco1.min_inputfreq) / info->vco1.min_inputfreq;
	hM = min(hM, (पूर्णांक)info->vco1.max_m);
	lM = min(lM, hM);

	क्रम (M = lM; M <= hM; M++) अणु
		u32 पंचांगp = freq * *P * M;
		N  = पंचांगp / info->refclk;
		fN = पंचांगp % info->refclk;

		अगर (!pfN) अणु
			अगर (fN >= info->refclk / 2)
				N++;
		पूर्ण अन्यथा अणु
			अगर (fN <  info->refclk / 2)
				N--;
			fN = पंचांगp - (N * info->refclk);
		पूर्ण

		अगर (N < info->vco1.min_n)
			जारी;
		अगर (N > info->vco1.max_n)
			अवरोध;

		err = असल(freq - (info->refclk * N / M / *P));
		अगर (err < best_err) अणु
			best_err = err;
			*pN = N;
			*pM = M;
		पूर्ण

		अगर (pfN) अणु
			*pfN = ((fN << 13) + info->refclk / 2) / info->refclk;
			*pfN = (*pfN - 4096) & 0xffff;
			वापस freq;
		पूर्ण
	पूर्ण

	अगर (unlikely(best_err == ~0)) अणु
		nvkm_error(subdev, "unable to find matching pll values\n");
		वापस -EINVAL;
	पूर्ण

	वापस info->refclk * *pN / *pM / *P;
पूर्ण
