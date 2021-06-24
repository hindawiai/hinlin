<शैली गुरु>
/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __NVKM_CLK_GK20A_H__
#घोषणा __NVKM_CLK_GK20A_H__

#घोषणा KHZ (1000)
#घोषणा MHZ (KHZ * 1000)

#घोषणा MASK(w)	((1 << (w)) - 1)

#घोषणा GK20A_CLK_GPC_MDIV 1000

#घोषणा SYS_GPCPLL_CFG_BASE	0x00137000
#घोषणा GPCPLL_CFG		(SYS_GPCPLL_CFG_BASE + 0)
#घोषणा GPCPLL_CFG_ENABLE	BIT(0)
#घोषणा GPCPLL_CFG_IDDQ		BIT(1)
#घोषणा GPCPLL_CFG_LOCK_DET_OFF	BIT(4)
#घोषणा GPCPLL_CFG_LOCK		BIT(17)

#घोषणा GPCPLL_CFG2		(SYS_GPCPLL_CFG_BASE + 0xc)
#घोषणा GPCPLL_CFG2_SETUP2_SHIFT	16
#घोषणा GPCPLL_CFG2_PLL_STEPA_SHIFT	24

#घोषणा GPCPLL_CFG3			(SYS_GPCPLL_CFG_BASE + 0x18)
#घोषणा GPCPLL_CFG3_VCO_CTRL_SHIFT		0
#घोषणा GPCPLL_CFG3_VCO_CTRL_WIDTH		9
#घोषणा GPCPLL_CFG3_VCO_CTRL_MASK		\
	(MASK(GPCPLL_CFG3_VCO_CTRL_WIDTH) << GPCPLL_CFG3_VCO_CTRL_SHIFT)
#घोषणा GPCPLL_CFG3_PLL_STEPB_SHIFT		16
#घोषणा GPCPLL_CFG3_PLL_STEPB_WIDTH		8

#घोषणा GPCPLL_COEFF		(SYS_GPCPLL_CFG_BASE + 4)
#घोषणा GPCPLL_COEFF_M_SHIFT	0
#घोषणा GPCPLL_COEFF_M_WIDTH	8
#घोषणा GPCPLL_COEFF_N_SHIFT	8
#घोषणा GPCPLL_COEFF_N_WIDTH	8
#घोषणा GPCPLL_COEFF_N_MASK	\
	(MASK(GPCPLL_COEFF_N_WIDTH) << GPCPLL_COEFF_N_SHIFT)
#घोषणा GPCPLL_COEFF_P_SHIFT	16
#घोषणा GPCPLL_COEFF_P_WIDTH	6

#घोषणा GPCPLL_NDIV_SLOWDOWN			(SYS_GPCPLL_CFG_BASE + 0x1c)
#घोषणा GPCPLL_NDIV_SLOWDOWN_NDIV_LO_SHIFT	0
#घोषणा GPCPLL_NDIV_SLOWDOWN_NDIV_MID_SHIFT	8
#घोषणा GPCPLL_NDIV_SLOWDOWN_STEP_SIZE_LO2MID_SHIFT	16
#घोषणा GPCPLL_NDIV_SLOWDOWN_SLOWDOWN_USING_PLL_SHIFT	22
#घोषणा GPCPLL_NDIV_SLOWDOWN_EN_DYNRAMP_SHIFT	31

#घोषणा GPC_BCAST_GPCPLL_CFG_BASE		0x00132800
#घोषणा GPC_BCAST_NDIV_SLOWDOWN_DEBUG	(GPC_BCAST_GPCPLL_CFG_BASE + 0xa0)
#घोषणा GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_SHIFT	24
#घोषणा GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_MASK \
	(0x1 << GPC_BCAST_NDIV_SLOWDOWN_DEBUG_PLL_DYNRAMP_DONE_SYNCED_SHIFT)

#घोषणा SEL_VCO				(SYS_GPCPLL_CFG_BASE + 0x100)
#घोषणा SEL_VCO_GPC2CLK_OUT_SHIFT	0

#घोषणा GPC2CLK_OUT			(SYS_GPCPLL_CFG_BASE + 0x250)
#घोषणा GPC2CLK_OUT_SDIV14_INDIV4_WIDTH	1
#घोषणा GPC2CLK_OUT_SDIV14_INDIV4_SHIFT	31
#घोषणा GPC2CLK_OUT_SDIV14_INDIV4_MODE	1
#घोषणा GPC2CLK_OUT_VCODIV_WIDTH	6
#घोषणा GPC2CLK_OUT_VCODIV_SHIFT	8
#घोषणा GPC2CLK_OUT_VCODIV1		0
#घोषणा GPC2CLK_OUT_VCODIV2		2
#घोषणा GPC2CLK_OUT_VCODIV_MASK		(MASK(GPC2CLK_OUT_VCODIV_WIDTH) << \
					GPC2CLK_OUT_VCODIV_SHIFT)
#घोषणा GPC2CLK_OUT_BYPDIV_WIDTH	6
#घोषणा GPC2CLK_OUT_BYPDIV_SHIFT	0
#घोषणा GPC2CLK_OUT_BYPDIV31		0x3c
#घोषणा GPC2CLK_OUT_INIT_MASK	((MASK(GPC2CLK_OUT_SDIV14_INDIV4_WIDTH) << \
		GPC2CLK_OUT_SDIV14_INDIV4_SHIFT)\
		| (MASK(GPC2CLK_OUT_VCODIV_WIDTH) << GPC2CLK_OUT_VCODIV_SHIFT)\
		| (MASK(GPC2CLK_OUT_BYPDIV_WIDTH) << GPC2CLK_OUT_BYPDIV_SHIFT))
#घोषणा GPC2CLK_OUT_INIT_VAL	((GPC2CLK_OUT_SDIV14_INDIV4_MODE << \
		GPC2CLK_OUT_SDIV14_INDIV4_SHIFT) \
		| (GPC2CLK_OUT_VCODIV1 << GPC2CLK_OUT_VCODIV_SHIFT) \
		| (GPC2CLK_OUT_BYPDIV31 << GPC2CLK_OUT_BYPDIV_SHIFT))

/* All frequencies in Khz */
काष्ठा gk20a_clk_pllg_params अणु
	u32 min_vco, max_vco;
	u32 min_u, max_u;
	u32 min_m, max_m;
	u32 min_n, max_n;
	u32 min_pl, max_pl;
पूर्ण;

काष्ठा gk20a_pll अणु
	u32 m;
	u32 n;
	u32 pl;
पूर्ण;

काष्ठा gk20a_clk अणु
	काष्ठा nvkm_clk base;
	स्थिर काष्ठा gk20a_clk_pllg_params *params;
	काष्ठा gk20a_pll pll;
	u32 parent_rate;

	u32 (*भाग_प्रकारo_pl)(u32);
	u32 (*pl_to_भाग)(u32);
पूर्ण;
#घोषणा gk20a_clk(p) container_of((p), काष्ठा gk20a_clk, base)

u32 gk20a_pllg_calc_rate(काष्ठा gk20a_clk *, काष्ठा gk20a_pll *);
पूर्णांक gk20a_pllg_calc_mnp(काष्ठा gk20a_clk *, अचिन्हित दीर्घ, काष्ठा gk20a_pll *);
व्योम gk20a_pllg_पढ़ो_mnp(काष्ठा gk20a_clk *, काष्ठा gk20a_pll *);
व्योम gk20a_pllg_ग_लिखो_mnp(काष्ठा gk20a_clk *, स्थिर काष्ठा gk20a_pll *);

अटल अंतरभूत bool
gk20a_pllg_is_enabled(काष्ठा gk20a_clk *clk)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 val;

	val = nvkm_rd32(device, GPCPLL_CFG);
	वापस val & GPCPLL_CFG_ENABLE;
पूर्ण

अटल अंतरभूत u32
gk20a_pllg_n_lo(काष्ठा gk20a_clk *clk, काष्ठा gk20a_pll *pll)
अणु
	वापस DIV_ROUND_UP(pll->m * clk->params->min_vco,
			    clk->parent_rate / KHZ);
पूर्ण

पूर्णांक gk20a_clk_ctor(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक, स्थिर काष्ठा nvkm_clk_func *,
		   स्थिर काष्ठा gk20a_clk_pllg_params *, काष्ठा gk20a_clk *);
व्योम gk20a_clk_fini(काष्ठा nvkm_clk *);
पूर्णांक gk20a_clk_पढ़ो(काष्ठा nvkm_clk *, क्रमागत nv_clk_src);
पूर्णांक gk20a_clk_calc(काष्ठा nvkm_clk *, काष्ठा nvkm_cstate *);
पूर्णांक gk20a_clk_prog(काष्ठा nvkm_clk *);
व्योम gk20a_clk_tidy(काष्ठा nvkm_clk *);

पूर्णांक gk20a_clk_setup_slide(काष्ठा gk20a_clk *);

#पूर्ण_अगर
