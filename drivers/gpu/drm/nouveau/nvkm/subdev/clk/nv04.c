<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
#समावेश "priv.h"
#समावेश "pll.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/devinit/nv04.h>

पूर्णांक
nv04_clk_pll_calc(काष्ठा nvkm_clk *घड़ी, काष्ठा nvbios_pll *info,
		  पूर्णांक clk, काष्ठा nvkm_pll_vals *pv)
अणु
	पूर्णांक N1, M1, N2, M2, P;
	पूर्णांक ret = nv04_pll_calc(&घड़ी->subdev, info, clk, &N1, &M1, &N2, &M2, &P);
	अगर (ret) अणु
		pv->refclk = info->refclk;
		pv->N1 = N1;
		pv->M1 = M1;
		pv->N2 = N2;
		pv->M2 = M2;
		pv->log2P = P;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
nv04_clk_pll_prog(काष्ठा nvkm_clk *clk, u32 reg1, काष्ठा nvkm_pll_vals *pv)
अणु
	काष्ठा nvkm_device *device = clk->subdev.device;
	काष्ठा nvkm_devinit *devinit = device->devinit;
	पूर्णांक cv = device->bios->version.chip;

	अगर (cv == 0x30 || cv == 0x31 || cv == 0x35 || cv == 0x36 ||
	    cv >= 0x40) अणु
		अगर (reg1 > 0x405c)
			setPLL_द्विगुन_highregs(devinit, reg1, pv);
		अन्यथा
			setPLL_द्विगुन_lowregs(devinit, reg1, pv);
	पूर्ण अन्यथा
		setPLL_single(devinit, reg1, pv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_clk_func
nv04_clk = अणु
	.करोमुख्यs = अणु
		अणु nv_clk_src_max पूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv04_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_clk **pclk)
अणु
	पूर्णांक ret = nvkm_clk_new_(&nv04_clk, device, type, inst, false, pclk);
	अगर (ret == 0) अणु
		(*pclk)->pll_calc = nv04_clk_pll_calc;
		(*pclk)->pll_prog = nv04_clk_pll_prog;
	पूर्ण
	वापस ret;
पूर्ण
