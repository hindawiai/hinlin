<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AXI clkgen driver
 *
 * Copyright 2012-2013 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>

#घोषणा AXI_CLKGEN_V2_REG_RESET		0x40
#घोषणा AXI_CLKGEN_V2_REG_CLKSEL	0x44
#घोषणा AXI_CLKGEN_V2_REG_DRP_CNTRL	0x70
#घोषणा AXI_CLKGEN_V2_REG_DRP_STATUS	0x74

#घोषणा AXI_CLKGEN_V2_RESET_MMCM_ENABLE	BIT(1)
#घोषणा AXI_CLKGEN_V2_RESET_ENABLE	BIT(0)

#घोषणा AXI_CLKGEN_V2_DRP_CNTRL_SEL	BIT(29)
#घोषणा AXI_CLKGEN_V2_DRP_CNTRL_READ	BIT(28)

#घोषणा AXI_CLKGEN_V2_DRP_STATUS_BUSY	BIT(16)

#घोषणा MMCM_REG_CLKOUT5_2	0x07
#घोषणा MMCM_REG_CLKOUT0_1	0x08
#घोषणा MMCM_REG_CLKOUT0_2	0x09
#घोषणा MMCM_REG_CLKOUT6_2	0x13
#घोषणा MMCM_REG_CLK_FB1	0x14
#घोषणा MMCM_REG_CLK_FB2	0x15
#घोषणा MMCM_REG_CLK_DIV	0x16
#घोषणा MMCM_REG_LOCK1		0x18
#घोषणा MMCM_REG_LOCK2		0x19
#घोषणा MMCM_REG_LOCK3		0x1a
#घोषणा MMCM_REG_POWER		0x28
#घोषणा MMCM_REG_FILTER1	0x4e
#घोषणा MMCM_REG_FILTER2	0x4f

#घोषणा MMCM_CLKOUT_NOCOUNT	BIT(6)

#घोषणा MMCM_CLK_DIV_DIVIDE	BIT(11)
#घोषणा MMCM_CLK_DIV_NOCOUNT	BIT(12)

काष्ठा axi_clkgen_limits अणु
	अचिन्हित पूर्णांक fpfd_min;
	अचिन्हित पूर्णांक fpfd_max;
	अचिन्हित पूर्णांक fvco_min;
	अचिन्हित पूर्णांक fvco_max;
पूर्ण;

काष्ठा axi_clkgen अणु
	व्योम __iomem *base;
	काष्ठा clk_hw clk_hw;
	काष्ठा axi_clkgen_limits limits;
पूर्ण;

अटल uपूर्णांक32_t axi_clkgen_lookup_filter(अचिन्हित पूर्णांक m)
अणु
	चयन (m) अणु
	हाल 0:
		वापस 0x01001990;
	हाल 1:
		वापस 0x01001190;
	हाल 2:
		वापस 0x01009890;
	हाल 3:
		वापस 0x01001890;
	हाल 4:
		वापस 0x01008890;
	हाल 5 ... 8:
		वापस 0x01009090;
	हाल 9 ... 11:
		वापस 0x01000890;
	हाल 12:
		वापस 0x08009090;
	हाल 13 ... 22:
		वापस 0x01001090;
	हाल 23 ... 36:
		वापस 0x01008090;
	हाल 37 ... 46:
		वापस 0x08001090;
	शेष:
		वापस 0x08008090;
	पूर्ण
पूर्ण

अटल स्थिर uपूर्णांक32_t axi_clkgen_lock_table[] = अणु
	0x060603e8, 0x060603e8, 0x080803e8, 0x0b0b03e8,
	0x0e0e03e8, 0x111103e8, 0x131303e8, 0x161603e8,
	0x191903e8, 0x1c1c03e8, 0x1f1f0384, 0x1f1f0339,
	0x1f1f02ee, 0x1f1f02bc, 0x1f1f028a, 0x1f1f0271,
	0x1f1f023f, 0x1f1f0226, 0x1f1f020d, 0x1f1f01f4,
	0x1f1f01db, 0x1f1f01c2, 0x1f1f01a9, 0x1f1f0190,
	0x1f1f0190, 0x1f1f0177, 0x1f1f015e, 0x1f1f015e,
	0x1f1f0145, 0x1f1f0145, 0x1f1f012c, 0x1f1f012c,
	0x1f1f012c, 0x1f1f0113, 0x1f1f0113, 0x1f1f0113,
पूर्ण;

अटल uपूर्णांक32_t axi_clkgen_lookup_lock(अचिन्हित पूर्णांक m)
अणु
	अगर (m < ARRAY_SIZE(axi_clkgen_lock_table))
		वापस axi_clkgen_lock_table[m];
	वापस 0x1f1f00fa;
पूर्ण

अटल स्थिर काष्ठा axi_clkgen_limits axi_clkgen_zynqmp_शेष_limits = अणु
	.fpfd_min = 10000,
	.fpfd_max = 450000,
	.fvco_min = 800000,
	.fvco_max = 1600000,
पूर्ण;

अटल स्थिर काष्ठा axi_clkgen_limits axi_clkgen_zynq_शेष_limits = अणु
	.fpfd_min = 10000,
	.fpfd_max = 300000,
	.fvco_min = 600000,
	.fvco_max = 1200000,
पूर्ण;

अटल व्योम axi_clkgen_calc_params(स्थिर काष्ठा axi_clkgen_limits *limits,
	अचिन्हित दीर्घ fin, अचिन्हित दीर्घ fout,
	अचिन्हित पूर्णांक *best_d, अचिन्हित पूर्णांक *best_m, अचिन्हित पूर्णांक *best_करोut)
अणु
	अचिन्हित दीर्घ d, d_min, d_max, _d_min, _d_max;
	अचिन्हित दीर्घ m, m_min, m_max;
	अचिन्हित दीर्घ f, करोut, best_f, fvco;
	अचिन्हित दीर्घ fract_shअगरt = 0;
	अचिन्हित दीर्घ fvco_min_fract, fvco_max_fract;

	fin /= 1000;
	fout /= 1000;

	best_f = अच_दीर्घ_उच्च;
	*best_d = 0;
	*best_m = 0;
	*best_करोut = 0;

	d_min = max_t(अचिन्हित दीर्घ, DIV_ROUND_UP(fin, limits->fpfd_max), 1);
	d_max = min_t(अचिन्हित दीर्घ, fin / limits->fpfd_min, 80);

again:
	fvco_min_fract = limits->fvco_min << fract_shअगरt;
	fvco_max_fract = limits->fvco_max << fract_shअगरt;

	m_min = max_t(अचिन्हित दीर्घ, DIV_ROUND_UP(fvco_min_fract, fin) * d_min, 1);
	m_max = min_t(अचिन्हित दीर्घ, fvco_max_fract * d_max / fin, 64 << fract_shअगरt);

	क्रम (m = m_min; m <= m_max; m++) अणु
		_d_min = max(d_min, DIV_ROUND_UP(fin * m, fvco_max_fract));
		_d_max = min(d_max, fin * m / fvco_min_fract);

		क्रम (d = _d_min; d <= _d_max; d++) अणु
			fvco = fin * m / d;

			करोut = DIV_ROUND_CLOSEST(fvco, fout);
			करोut = clamp_t(अचिन्हित दीर्घ, करोut, 1, 128 << fract_shअगरt);
			f = fvco / करोut;
			अगर (असल(f - fout) < असल(best_f - fout)) अणु
				best_f = f;
				*best_d = d;
				*best_m = m << (3 - fract_shअगरt);
				*best_करोut = करोut << (3 - fract_shअगरt);
				अगर (best_f == fout)
					वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Lets see अगर we find a better setting in fractional mode */
	अगर (fract_shअगरt == 0) अणु
		fract_shअगरt = 3;
		जाओ again;
	पूर्ण
पूर्ण

काष्ठा axi_clkgen_भाग_params अणु
	अचिन्हित पूर्णांक low;
	अचिन्हित पूर्णांक high;
	अचिन्हित पूर्णांक edge;
	अचिन्हित पूर्णांक nocount;
	अचिन्हित पूर्णांक frac_en;
	अचिन्हित पूर्णांक frac;
	अचिन्हित पूर्णांक frac_wf_f;
	अचिन्हित पूर्णांक frac_wf_r;
	अचिन्हित पूर्णांक frac_phase;
पूर्ण;

अटल व्योम axi_clkgen_calc_clk_params(अचिन्हित पूर्णांक भागider,
	अचिन्हित पूर्णांक frac_भागider, काष्ठा axi_clkgen_भाग_params *params)
अणु

	स_रखो(params, 0x0, माप(*params));

	अगर (भागider == 1) अणु
		params->nocount = 1;
		वापस;
	पूर्ण

	अगर (frac_भागider == 0) अणु
		params->high = भागider / 2;
		params->edge = भागider % 2;
		params->low = भागider - params->high;
	पूर्ण अन्यथा अणु
		params->frac_en = 1;
		params->frac = frac_भागider;

		params->high = भागider / 2;
		params->edge = भागider % 2;
		params->low = params->high;

		अगर (params->edge == 0) अणु
			params->high--;
			params->frac_wf_r = 1;
		पूर्ण

		अगर (params->edge == 0 || frac_भागider == 1)
			params->low--;
		अगर (((params->edge == 0) ^ (frac_भागider == 1)) ||
			(भागider == 2 && frac_भागider == 1))
			params->frac_wf_f = 1;

		params->frac_phase = params->edge * 4 + frac_भागider / 2;
	पूर्ण
पूर्ण

अटल व्योम axi_clkgen_ग_लिखो(काष्ठा axi_clkgen *axi_clkgen,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, axi_clkgen->base + reg);
पूर्ण

अटल व्योम axi_clkgen_पढ़ो(काष्ठा axi_clkgen *axi_clkgen,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	*val = पढ़ोl(axi_clkgen->base + reg);
पूर्ण

अटल पूर्णांक axi_clkgen_रुको_non_busy(काष्ठा axi_clkgen *axi_clkgen)
अणु
	अचिन्हित पूर्णांक समयout = 10000;
	अचिन्हित पूर्णांक val;

	करो अणु
		axi_clkgen_पढ़ो(axi_clkgen, AXI_CLKGEN_V2_REG_DRP_STATUS, &val);
	पूर्ण जबतक ((val & AXI_CLKGEN_V2_DRP_STATUS_BUSY) && --समयout);

	अगर (val & AXI_CLKGEN_V2_DRP_STATUS_BUSY)
		वापस -EIO;

	वापस val & 0xffff;
पूर्ण

अटल पूर्णांक axi_clkgen_mmcm_पढ़ो(काष्ठा axi_clkgen *axi_clkgen,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक reg_val;
	पूर्णांक ret;

	ret = axi_clkgen_रुको_non_busy(axi_clkgen);
	अगर (ret < 0)
		वापस ret;

	reg_val = AXI_CLKGEN_V2_DRP_CNTRL_SEL | AXI_CLKGEN_V2_DRP_CNTRL_READ;
	reg_val |= (reg << 16);

	axi_clkgen_ग_लिखो(axi_clkgen, AXI_CLKGEN_V2_REG_DRP_CNTRL, reg_val);

	ret = axi_clkgen_रुको_non_busy(axi_clkgen);
	अगर (ret < 0)
		वापस ret;

	*val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक axi_clkgen_mmcm_ग_लिखो(काष्ठा axi_clkgen *axi_clkgen,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक reg_val = 0;
	पूर्णांक ret;

	ret = axi_clkgen_रुको_non_busy(axi_clkgen);
	अगर (ret < 0)
		वापस ret;

	अगर (mask != 0xffff) अणु
		axi_clkgen_mmcm_पढ़ो(axi_clkgen, reg, &reg_val);
		reg_val &= ~mask;
	पूर्ण

	reg_val |= AXI_CLKGEN_V2_DRP_CNTRL_SEL | (reg << 16) | (val & mask);

	axi_clkgen_ग_लिखो(axi_clkgen, AXI_CLKGEN_V2_REG_DRP_CNTRL, reg_val);

	वापस 0;
पूर्ण

अटल व्योम axi_clkgen_mmcm_enable(काष्ठा axi_clkgen *axi_clkgen,
	bool enable)
अणु
	अचिन्हित पूर्णांक val = AXI_CLKGEN_V2_RESET_ENABLE;

	अगर (enable)
		val |= AXI_CLKGEN_V2_RESET_MMCM_ENABLE;

	axi_clkgen_ग_लिखो(axi_clkgen, AXI_CLKGEN_V2_REG_RESET, val);
पूर्ण

अटल काष्ठा axi_clkgen *clk_hw_to_axi_clkgen(काष्ठा clk_hw *clk_hw)
अणु
	वापस container_of(clk_hw, काष्ठा axi_clkgen, clk_hw);
पूर्ण

अटल व्योम axi_clkgen_set_भाग(काष्ठा axi_clkgen *axi_clkgen,
	अचिन्हित पूर्णांक reg1, अचिन्हित पूर्णांक reg2, अचिन्हित पूर्णांक reg3,
	काष्ठा axi_clkgen_भाग_params *params)
अणु
	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, reg1,
		(params->high << 6) | params->low, 0xefff);
	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, reg2,
		(params->frac << 12) | (params->frac_en << 11) |
		(params->frac_wf_r << 10) | (params->edge << 7) |
		(params->nocount << 6), 0x7fff);
	अगर (reg3 != 0) अणु
		axi_clkgen_mmcm_ग_लिखो(axi_clkgen, reg3,
			(params->frac_phase << 11) | (params->frac_wf_f << 10), 0x3c00);
	पूर्ण
पूर्ण

अटल पूर्णांक axi_clkgen_set_rate(काष्ठा clk_hw *clk_hw,
	अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);
	स्थिर काष्ठा axi_clkgen_limits *limits = &axi_clkgen->limits;
	अचिन्हित पूर्णांक d, m, करोut;
	काष्ठा axi_clkgen_भाग_params params;
	uपूर्णांक32_t घातer = 0;
	uपूर्णांक32_t filter;
	uपूर्णांक32_t lock;

	अगर (parent_rate == 0 || rate == 0)
		वापस -EINVAL;

	axi_clkgen_calc_params(limits, parent_rate, rate, &d, &m, &करोut);

	अगर (d == 0 || करोut == 0 || m == 0)
		वापस -EINVAL;

	अगर ((करोut & 0x7) != 0 || (m & 0x7) != 0)
		घातer |= 0x9800;

	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, MMCM_REG_POWER, घातer, 0x9800);

	filter = axi_clkgen_lookup_filter(m - 1);
	lock = axi_clkgen_lookup_lock(m - 1);

	axi_clkgen_calc_clk_params(करोut >> 3, करोut & 0x7, &params);
	axi_clkgen_set_भाग(axi_clkgen,  MMCM_REG_CLKOUT0_1, MMCM_REG_CLKOUT0_2,
		MMCM_REG_CLKOUT5_2, &params);

	axi_clkgen_calc_clk_params(d, 0, &params);
	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, MMCM_REG_CLK_DIV,
		(params.edge << 13) | (params.nocount << 12) |
		(params.high << 6) | params.low, 0x3fff);

	axi_clkgen_calc_clk_params(m >> 3, m & 0x7, &params);
	axi_clkgen_set_भाग(axi_clkgen,  MMCM_REG_CLK_FB1, MMCM_REG_CLK_FB2,
		MMCM_REG_CLKOUT6_2, &params);

	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, MMCM_REG_LOCK1, lock & 0x3ff, 0x3ff);
	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, MMCM_REG_LOCK2,
		(((lock >> 16) & 0x1f) << 10) | 0x1, 0x7fff);
	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, MMCM_REG_LOCK3,
		(((lock >> 24) & 0x1f) << 10) | 0x3e9, 0x7fff);
	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, MMCM_REG_FILTER1, filter >> 16, 0x9900);
	axi_clkgen_mmcm_ग_लिखो(axi_clkgen, MMCM_REG_FILTER2, filter, 0x9900);

	वापस 0;
पूर्ण

अटल दीर्घ axi_clkgen_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
	अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(hw);
	स्थिर काष्ठा axi_clkgen_limits *limits = &axi_clkgen->limits;
	अचिन्हित पूर्णांक d, m, करोut;
	अचिन्हित दीर्घ दीर्घ पंचांगp;

	axi_clkgen_calc_params(limits, *parent_rate, rate, &d, &m, &करोut);

	अगर (d == 0 || करोut == 0 || m == 0)
		वापस -EINVAL;

	पंचांगp = (अचिन्हित दीर्घ दीर्घ)*parent_rate * m;
	पंचांगp = DIV_ROUND_CLOSEST_ULL(पंचांगp, करोut * d);

	वापस min_t(अचिन्हित दीर्घ दीर्घ, पंचांगp, दीर्घ_उच्च);
पूर्ण

अटल अचिन्हित पूर्णांक axi_clkgen_get_भाग(काष्ठा axi_clkgen *axi_clkgen,
	अचिन्हित पूर्णांक reg1, अचिन्हित पूर्णांक reg2)
अणु
	अचिन्हित पूर्णांक val1, val2;
	अचिन्हित पूर्णांक भाग;

	axi_clkgen_mmcm_पढ़ो(axi_clkgen, reg2, &val2);
	अगर (val2 & MMCM_CLKOUT_NOCOUNT)
		वापस 8;

	axi_clkgen_mmcm_पढ़ो(axi_clkgen, reg1, &val1);

	भाग = (val1 & 0x3f) + ((val1 >> 6) & 0x3f);
	भाग <<= 3;

	अगर (val2 & MMCM_CLK_DIV_DIVIDE) अणु
		अगर ((val2 & BIT(7)) && (val2 & 0x7000) != 0x1000)
			भाग += 8;
		अन्यथा
			भाग += 16;

		भाग += (val2 >> 12) & 0x7;
	पूर्ण

	वापस भाग;
पूर्ण

अटल अचिन्हित दीर्घ axi_clkgen_recalc_rate(काष्ठा clk_hw *clk_hw,
	अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);
	अचिन्हित पूर्णांक d, m, करोut;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	अचिन्हित पूर्णांक val;

	करोut = axi_clkgen_get_भाग(axi_clkgen, MMCM_REG_CLKOUT0_1,
		MMCM_REG_CLKOUT0_2);
	m = axi_clkgen_get_भाग(axi_clkgen, MMCM_REG_CLK_FB1,
		MMCM_REG_CLK_FB2);

	axi_clkgen_mmcm_पढ़ो(axi_clkgen, MMCM_REG_CLK_DIV, &val);
	अगर (val & MMCM_CLK_DIV_NOCOUNT)
		d = 1;
	अन्यथा
		d = (val & 0x3f) + ((val >> 6) & 0x3f);

	अगर (d == 0 || करोut == 0)
		वापस 0;

	पंचांगp = (अचिन्हित दीर्घ दीर्घ)parent_rate * m;
	पंचांगp = DIV_ROUND_CLOSEST_ULL(पंचांगp, करोut * d);

	वापस min_t(अचिन्हित दीर्घ दीर्घ, पंचांगp, अच_दीर्घ_उच्च);
पूर्ण

अटल पूर्णांक axi_clkgen_enable(काष्ठा clk_hw *clk_hw)
अणु
	काष्ठा axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);

	axi_clkgen_mmcm_enable(axi_clkgen, true);

	वापस 0;
पूर्ण

अटल व्योम axi_clkgen_disable(काष्ठा clk_hw *clk_hw)
अणु
	काष्ठा axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);

	axi_clkgen_mmcm_enable(axi_clkgen, false);
पूर्ण

अटल पूर्णांक axi_clkgen_set_parent(काष्ठा clk_hw *clk_hw, u8 index)
अणु
	काष्ठा axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);

	axi_clkgen_ग_लिखो(axi_clkgen, AXI_CLKGEN_V2_REG_CLKSEL, index);

	वापस 0;
पूर्ण

अटल u8 axi_clkgen_get_parent(काष्ठा clk_hw *clk_hw)
अणु
	काष्ठा axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);
	अचिन्हित पूर्णांक parent;

	axi_clkgen_पढ़ो(axi_clkgen, AXI_CLKGEN_V2_REG_CLKSEL, &parent);

	वापस parent;
पूर्ण

अटल स्थिर काष्ठा clk_ops axi_clkgen_ops = अणु
	.recalc_rate = axi_clkgen_recalc_rate,
	.round_rate = axi_clkgen_round_rate,
	.set_rate = axi_clkgen_set_rate,
	.enable = axi_clkgen_enable,
	.disable = axi_clkgen_disable,
	.set_parent = axi_clkgen_set_parent,
	.get_parent = axi_clkgen_get_parent,
पूर्ण;

अटल पूर्णांक axi_clkgen_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा axi_clkgen_limits *dflt_limits;
	काष्ठा axi_clkgen *axi_clkgen;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_names[2];
	स्थिर अक्षर *clk_name;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	dflt_limits = device_get_match_data(&pdev->dev);
	अगर (!dflt_limits)
		वापस -ENODEV;

	axi_clkgen = devm_kzalloc(&pdev->dev, माप(*axi_clkgen), GFP_KERNEL);
	अगर (!axi_clkgen)
		वापस -ENOMEM;

	axi_clkgen->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(axi_clkgen->base))
		वापस PTR_ERR(axi_clkgen->base);

	init.num_parents = of_clk_get_parent_count(pdev->dev.of_node);
	अगर (init.num_parents < 1 || init.num_parents > 2)
		वापस -EINVAL;

	क्रम (i = 0; i < init.num_parents; i++) अणु
		parent_names[i] = of_clk_get_parent_name(pdev->dev.of_node, i);
		अगर (!parent_names[i])
			वापस -EINVAL;
	पूर्ण

	स_नकल(&axi_clkgen->limits, dflt_limits, माप(axi_clkgen->limits));

	clk_name = pdev->dev.of_node->name;
	of_property_पढ़ो_string(pdev->dev.of_node, "clock-output-names",
		&clk_name);

	init.name = clk_name;
	init.ops = &axi_clkgen_ops;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;
	init.parent_names = parent_names;

	axi_clkgen_mmcm_enable(axi_clkgen, false);

	axi_clkgen->clk_hw.init = &init;
	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &axi_clkgen->clk_hw);
	अगर (ret)
		वापस ret;

	वापस of_clk_add_hw_provider(pdev->dev.of_node, of_clk_hw_simple_get,
				      &axi_clkgen->clk_hw);
पूर्ण

अटल पूर्णांक axi_clkgen_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id axi_clkgen_ids[] = अणु
	अणु
		.compatible = "adi,zynqmp-axi-clkgen-2.00.a",
		.data = &axi_clkgen_zynqmp_शेष_limits,
	पूर्ण,
	अणु
		.compatible = "adi,axi-clkgen-2.00.a",
		.data = &axi_clkgen_zynq_शेष_limits,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axi_clkgen_ids);

अटल काष्ठा platक्रमm_driver axi_clkgen_driver = अणु
	.driver = अणु
		.name = "adi-axi-clkgen",
		.of_match_table = axi_clkgen_ids,
	पूर्ण,
	.probe = axi_clkgen_probe,
	.हटाओ = axi_clkgen_हटाओ,
पूर्ण;
module_platक्रमm_driver(axi_clkgen_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Driver for the Analog Devices' AXI clkgen pcore clock generator");
