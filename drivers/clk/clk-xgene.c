<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * clk-xgene.c - AppliedMicro X-Gene Clock Interface
 *
 * Copyright (c) 2013, Applied Micro Circuits Corporation
 * Author: Loc Ho <lho@apm.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of_address.h>

/* Register SCU_PCPPLL bit fields */
#घोषणा N_DIV_RD(src)			((src) & 0x000001ff)
#घोषणा SC_N_DIV_RD(src)		((src) & 0x0000007f)
#घोषणा SC_OUTDIV2(src)			(((src) & 0x00000100) >> 8)

/* Register SCU_SOCPLL bit fields */
#घोषणा CLKR_RD(src)			(((src) & 0x07000000)>>24)
#घोषणा CLKOD_RD(src)			(((src) & 0x00300000)>>20)
#घोषणा REGSPEC_RESET_F1_MASK		0x00010000
#घोषणा CLKF_RD(src)			(((src) & 0x000001ff))

#घोषणा XGENE_CLK_DRIVER_VER		"0.1"

अटल DEFINE_SPINLOCK(clk_lock);

अटल अंतरभूत u32 xgene_clk_पढ़ो(व्योम __iomem *csr)
अणु
	वापस पढ़ोl_relaxed(csr);
पूर्ण

अटल अंतरभूत व्योम xgene_clk_ग_लिखो(u32 data, व्योम __iomem *csr)
अणु
	ग_लिखोl_relaxed(data, csr);
पूर्ण

/* PLL Clock */
क्रमागत xgene_pll_type अणु
	PLL_TYPE_PCP = 0,
	PLL_TYPE_SOC = 1,
पूर्ण;

काष्ठा xgene_clk_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	spinlock_t	*lock;
	u32		pll_offset;
	क्रमागत xgene_pll_type	type;
	पूर्णांक		version;
पूर्ण;

#घोषणा to_xgene_clk_pll(_hw) container_of(_hw, काष्ठा xgene_clk_pll, hw)

अटल पूर्णांक xgene_clk_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा xgene_clk_pll *pllclk = to_xgene_clk_pll(hw);
	u32 data;

	data = xgene_clk_पढ़ो(pllclk->reg + pllclk->pll_offset);
	pr_debug("%s pll %s\n", clk_hw_get_name(hw),
		data & REGSPEC_RESET_F1_MASK ? "disabled" : "enabled");

	वापस data & REGSPEC_RESET_F1_MASK ? 0 : 1;
पूर्ण

अटल अचिन्हित दीर्घ xgene_clk_pll_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा xgene_clk_pll *pllclk = to_xgene_clk_pll(hw);
	अचिन्हित दीर्घ fref;
	अचिन्हित दीर्घ fvco;
	u32 pll;
	u32 nref;
	u32 nout;
	u32 nfb;

	pll = xgene_clk_पढ़ो(pllclk->reg + pllclk->pll_offset);

	अगर (pllclk->version <= 1) अणु
		अगर (pllclk->type == PLL_TYPE_PCP) अणु
			/*
			* PLL VCO = Reference घड़ी * NF
			* PCP PLL = PLL_VCO / 2
			*/
			nout = 2;
			fvco = parent_rate * (N_DIV_RD(pll) + 4);
		पूर्ण अन्यथा अणु
			/*
			* Fref = Reference Clock / NREF;
			* Fvco = Fref * NFB;
			* Fout = Fvco / NOUT;
			*/
			nref = CLKR_RD(pll) + 1;
			nout = CLKOD_RD(pll) + 1;
			nfb = CLKF_RD(pll);
			fref = parent_rate / nref;
			fvco = fref * nfb;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * fvco = Reference घड़ी * FBDIVC
		 * PLL freq = fvco / NOUT
		 */
		nout = SC_OUTDIV2(pll) ? 2 : 3;
		fvco = parent_rate * SC_N_DIV_RD(pll);
	पूर्ण
	pr_debug("%s pll recalc rate %ld parent %ld version %d\n",
		 clk_hw_get_name(hw), fvco / nout, parent_rate,
		 pllclk->version);

	वापस fvco / nout;
पूर्ण

अटल स्थिर काष्ठा clk_ops xgene_clk_pll_ops = अणु
	.is_enabled = xgene_clk_pll_is_enabled,
	.recalc_rate = xgene_clk_pll_recalc_rate,
पूर्ण;

अटल काष्ठा clk *xgene_रेजिस्टर_clk_pll(काष्ठा device *dev,
	स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
	अचिन्हित दीर्घ flags, व्योम __iomem *reg, u32 pll_offset,
	u32 type, spinlock_t *lock, पूर्णांक version)
अणु
	काष्ठा xgene_clk_pll *apmclk;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;

	/* allocate the APM घड़ी काष्ठाure */
	apmclk = kzalloc(माप(*apmclk), GFP_KERNEL);
	अगर (!apmclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &xgene_clk_pll_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	apmclk->version = version;
	apmclk->reg = reg;
	apmclk->lock = lock;
	apmclk->pll_offset = pll_offset;
	apmclk->type = type;
	apmclk->hw.init = &init;

	/* Register the घड़ी */
	clk = clk_रेजिस्टर(dev, &apmclk->hw);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: could not register clk %s\n", __func__, name);
		kमुक्त(apmclk);
		वापस शून्य;
	पूर्ण
	वापस clk;
पूर्ण

अटल पूर्णांक xgene_pllclk_version(काष्ठा device_node *np)
अणु
	अगर (of_device_is_compatible(np, "apm,xgene-socpll-clock"))
		वापस 1;
	अगर (of_device_is_compatible(np, "apm,xgene-pcppll-clock"))
		वापस 1;
	वापस 2;
पूर्ण

अटल व्योम xgene_pllclk_init(काष्ठा device_node *np, क्रमागत xgene_pll_type pll_type)
अणु
	स्थिर अक्षर *clk_name = np->full_name;
	काष्ठा clk *clk;
	व्योम __iomem *reg;
	पूर्णांक version = xgene_pllclk_version(np);

	reg = of_iomap(np, 0);
	अगर (!reg) अणु
		pr_err("Unable to map CSR register for %pOF\n", np);
		वापस;
	पूर्ण
	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);
	clk = xgene_रेजिस्टर_clk_pll(शून्य,
			clk_name, of_clk_get_parent_name(np, 0),
			0, reg, 0, pll_type, &clk_lock,
			version);
	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(np, of_clk_src_simple_get, clk);
		clk_रेजिस्टर_clkdev(clk, clk_name, शून्य);
		pr_debug("Add %s clock PLL\n", clk_name);
	पूर्ण
पूर्ण

अटल व्योम xgene_socpllclk_init(काष्ठा device_node *np)
अणु
	xgene_pllclk_init(np, PLL_TYPE_SOC);
पूर्ण

अटल व्योम xgene_pcppllclk_init(काष्ठा device_node *np)
अणु
	xgene_pllclk_init(np, PLL_TYPE_PCP);
पूर्ण

/**
 * काष्ठा xgene_clk_pmd - PMD घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर containing the fractional scale multiplier (scaler)
 * @shअगरt:	shअगरt to the unit bit field
 * @mask:	mask to the unit bit field
 * @denom:	1/denominator unit
 * @lock:	रेजिस्टर lock
 * @flags: XGENE_CLK_PMD_SCALE_INVERTED - By शेष the scaler is the value पढ़ो
 *	from the रेजिस्टर plus one. For example,
 *		0 क्रम (0 + 1) / denom,
 *		1 क्रम (1 + 1) / denom and etc.
 *	If this flag is set, it is
 *		0 क्रम (denom - 0) / denom,
 *		1 क्रम (denom - 1) / denom and etc.
 */
काष्ठा xgene_clk_pmd अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		shअगरt;
	u32		mask;
	u64		denom;
	u32		flags;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_xgene_clk_pmd(_hw) container_of(_hw, काष्ठा xgene_clk_pmd, hw)

#घोषणा XGENE_CLK_PMD_SCALE_INVERTED	BIT(0)
#घोषणा XGENE_CLK_PMD_SHIFT		8
#घोषणा XGENE_CLK_PMD_WIDTH		3

अटल अचिन्हित दीर्घ xgene_clk_pmd_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा xgene_clk_pmd *fd = to_xgene_clk_pmd(hw);
	अचिन्हित दीर्घ flags = 0;
	u64 ret, scale;
	u32 val;

	अगर (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	अन्यथा
		__acquire(fd->lock);

	val = पढ़ोl(fd->reg);

	अगर (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	अन्यथा
		__release(fd->lock);

	ret = (u64)parent_rate;

	scale = (val & fd->mask) >> fd->shअगरt;
	अगर (fd->flags & XGENE_CLK_PMD_SCALE_INVERTED)
		scale = fd->denom - scale;
	अन्यथा
		scale++;

	/* freq = parent_rate * scaler / denom */
	करो_भाग(ret, fd->denom);
	ret *= scale;
	अगर (ret == 0)
		ret = (u64)parent_rate;

	वापस ret;
पूर्ण

अटल दीर्घ xgene_clk_pmd_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा xgene_clk_pmd *fd = to_xgene_clk_pmd(hw);
	u64 ret, scale;

	अगर (!rate || rate >= *parent_rate)
		वापस *parent_rate;

	/* freq = parent_rate * scaler / denom */
	ret = rate * fd->denom;
	scale = DIV_ROUND_UP_ULL(ret, *parent_rate);

	ret = (u64)*parent_rate * scale;
	करो_भाग(ret, fd->denom);

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_clk_pmd_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा xgene_clk_pmd *fd = to_xgene_clk_pmd(hw);
	अचिन्हित दीर्घ flags = 0;
	u64 scale, ret;
	u32 val;

	/*
	 * Compute the scaler:
	 *
	 * freq = parent_rate * scaler / denom, or
	 * scaler = freq * denom / parent_rate
	 */
	ret = rate * fd->denom;
	scale = DIV_ROUND_UP_ULL(ret, (u64)parent_rate);

	/* Check अगर inverted */
	अगर (fd->flags & XGENE_CLK_PMD_SCALE_INVERTED)
		scale = fd->denom - scale;
	अन्यथा
		scale--;

	अगर (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	अन्यथा
		__acquire(fd->lock);

	val = पढ़ोl(fd->reg);
	val &= ~fd->mask;
	val |= (scale << fd->shअगरt);
	ग_लिखोl(val, fd->reg);

	अगर (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	अन्यथा
		__release(fd->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops xgene_clk_pmd_ops = अणु
	.recalc_rate = xgene_clk_pmd_recalc_rate,
	.round_rate = xgene_clk_pmd_round_rate,
	.set_rate = xgene_clk_pmd_set_rate,
पूर्ण;

अटल काष्ठा clk *
xgene_रेजिस्टर_clk_pmd(काष्ठा device *dev,
		       स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		       अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt,
		       u8 width, u64 denom, u32 clk_flags, spinlock_t *lock)
अणु
	काष्ठा xgene_clk_pmd *fd;
	काष्ठा clk_init_data init;
	काष्ठा clk *clk;

	fd = kzalloc(माप(*fd), GFP_KERNEL);
	अगर (!fd)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &xgene_clk_pmd_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	fd->reg = reg;
	fd->shअगरt = shअगरt;
	fd->mask = (BIT(width) - 1) << shअगरt;
	fd->denom = denom;
	fd->flags = clk_flags;
	fd->lock = lock;
	fd->hw.init = &init;

	clk = clk_रेजिस्टर(dev, &fd->hw);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: could not register clk %s\n", __func__, name);
		kमुक्त(fd);
		वापस शून्य;
	पूर्ण

	वापस clk;
पूर्ण

अटल व्योम xgene_pmdclk_init(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *clk_name = np->full_name;
	व्योम __iomem *csr_reg;
	काष्ठा resource res;
	काष्ठा clk *clk;
	u64 denom;
	u32 flags = 0;
	पूर्णांक rc;

	/* Check अगर the entry is disabled */
	अगर (!of_device_is_available(np))
		वापस;

	/* Parse the DTS रेजिस्टर क्रम resource */
	rc = of_address_to_resource(np, 0, &res);
	अगर (rc != 0) अणु
		pr_err("no DTS register for %pOF\n", np);
		वापस;
	पूर्ण
	csr_reg = of_iomap(np, 0);
	अगर (!csr_reg) अणु
		pr_err("Unable to map resource for %pOF\n", np);
		वापस;
	पूर्ण
	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	denom = BIT(XGENE_CLK_PMD_WIDTH);
	flags |= XGENE_CLK_PMD_SCALE_INVERTED;

	clk = xgene_रेजिस्टर_clk_pmd(शून्य, clk_name,
				     of_clk_get_parent_name(np, 0), 0,
				     csr_reg, XGENE_CLK_PMD_SHIFT,
				     XGENE_CLK_PMD_WIDTH, denom,
				     flags, &clk_lock);
	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(np, of_clk_src_simple_get, clk);
		clk_रेजिस्टर_clkdev(clk, clk_name, शून्य);
		pr_debug("Add %s clock\n", clk_name);
	पूर्ण अन्यथा अणु
		अगर (csr_reg)
			iounmap(csr_reg);
	पूर्ण
पूर्ण

/* IP Clock */
काष्ठा xgene_dev_parameters अणु
	व्योम __iomem *csr_reg;		/* CSR क्रम IP घड़ी */
	u32 reg_clk_offset;		/* Offset to घड़ी enable CSR */
	u32 reg_clk_mask;		/* Mask bit क्रम घड़ी enable */
	u32 reg_csr_offset;		/* Offset to CSR reset */
	u32 reg_csr_mask;		/* Mask bit क्रम disable CSR reset */
	व्योम __iomem *भागider_reg;	/* CSR क्रम भागider */
	u32 reg_भागider_offset;		/* Offset to भागider रेजिस्टर */
	u32 reg_भागider_shअगरt;		/* Bit shअगरt to भागider field */
	u32 reg_भागider_width;		/* Width of the bit to भागider field */
पूर्ण;

काष्ठा xgene_clk अणु
	काष्ठा clk_hw	hw;
	spinlock_t	*lock;
	काष्ठा xgene_dev_parameters	param;
पूर्ण;

#घोषणा to_xgene_clk(_hw) container_of(_hw, काष्ठा xgene_clk, hw)

अटल पूर्णांक xgene_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा xgene_clk *pclk = to_xgene_clk(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 data;

	अगर (pclk->lock)
		spin_lock_irqsave(pclk->lock, flags);

	अगर (pclk->param.csr_reg) अणु
		pr_debug("%s clock enabled\n", clk_hw_get_name(hw));
		/* First enable the घड़ी */
		data = xgene_clk_पढ़ो(pclk->param.csr_reg +
					pclk->param.reg_clk_offset);
		data |= pclk->param.reg_clk_mask;
		xgene_clk_ग_लिखो(data, pclk->param.csr_reg +
					pclk->param.reg_clk_offset);
		pr_debug("%s clk offset 0x%08X mask 0x%08X value 0x%08X\n",
			clk_hw_get_name(hw),
			pclk->param.reg_clk_offset, pclk->param.reg_clk_mask,
			data);

		/* Second enable the CSR */
		data = xgene_clk_पढ़ो(pclk->param.csr_reg +
					pclk->param.reg_csr_offset);
		data &= ~pclk->param.reg_csr_mask;
		xgene_clk_ग_लिखो(data, pclk->param.csr_reg +
					pclk->param.reg_csr_offset);
		pr_debug("%s csr offset 0x%08X mask 0x%08X value 0x%08X\n",
			clk_hw_get_name(hw),
			pclk->param.reg_csr_offset, pclk->param.reg_csr_mask,
			data);
	पूर्ण

	अगर (pclk->lock)
		spin_unlock_irqrestore(pclk->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम xgene_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा xgene_clk *pclk = to_xgene_clk(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 data;

	अगर (pclk->lock)
		spin_lock_irqsave(pclk->lock, flags);

	अगर (pclk->param.csr_reg) अणु
		pr_debug("%s clock disabled\n", clk_hw_get_name(hw));
		/* First put the CSR in reset */
		data = xgene_clk_पढ़ो(pclk->param.csr_reg +
					pclk->param.reg_csr_offset);
		data |= pclk->param.reg_csr_mask;
		xgene_clk_ग_लिखो(data, pclk->param.csr_reg +
					pclk->param.reg_csr_offset);

		/* Second disable the घड़ी */
		data = xgene_clk_पढ़ो(pclk->param.csr_reg +
					pclk->param.reg_clk_offset);
		data &= ~pclk->param.reg_clk_mask;
		xgene_clk_ग_लिखो(data, pclk->param.csr_reg +
					pclk->param.reg_clk_offset);
	पूर्ण

	अगर (pclk->lock)
		spin_unlock_irqrestore(pclk->lock, flags);
पूर्ण

अटल पूर्णांक xgene_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा xgene_clk *pclk = to_xgene_clk(hw);
	u32 data = 0;

	अगर (pclk->param.csr_reg) अणु
		pr_debug("%s clock checking\n", clk_hw_get_name(hw));
		data = xgene_clk_पढ़ो(pclk->param.csr_reg +
					pclk->param.reg_clk_offset);
		pr_debug("%s clock is %s\n", clk_hw_get_name(hw),
			data & pclk->param.reg_clk_mask ? "enabled" :
							"disabled");
	पूर्ण

	अगर (!pclk->param.csr_reg)
		वापस 1;
	वापस data & pclk->param.reg_clk_mask ? 1 : 0;
पूर्ण

अटल अचिन्हित दीर्घ xgene_clk_recalc_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा xgene_clk *pclk = to_xgene_clk(hw);
	u32 data;

	अगर (pclk->param.भागider_reg) अणु
		data = xgene_clk_पढ़ो(pclk->param.भागider_reg +
					pclk->param.reg_भागider_offset);
		data >>= pclk->param.reg_भागider_shअगरt;
		data &= (1 << pclk->param.reg_भागider_width) - 1;

		pr_debug("%s clock recalc rate %ld parent %ld\n",
			clk_hw_get_name(hw),
			parent_rate / data, parent_rate);

		वापस parent_rate / data;
	पूर्ण अन्यथा अणु
		pr_debug("%s clock recalc rate %ld parent %ld\n",
			clk_hw_get_name(hw), parent_rate, parent_rate);
		वापस parent_rate;
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा xgene_clk *pclk = to_xgene_clk(hw);
	अचिन्हित दीर्घ flags = 0;
	u32 data;
	u32 भागider;
	u32 भागider_save;

	अगर (pclk->lock)
		spin_lock_irqsave(pclk->lock, flags);

	अगर (pclk->param.भागider_reg) अणु
		/* Let's compute the भागider */
		अगर (rate > parent_rate)
			rate = parent_rate;
		भागider_save = भागider = parent_rate / rate; /* Rounded करोwn */
		भागider &= (1 << pclk->param.reg_भागider_width) - 1;
		भागider <<= pclk->param.reg_भागider_shअगरt;

		/* Set new भागider */
		data = xgene_clk_पढ़ो(pclk->param.भागider_reg +
				pclk->param.reg_भागider_offset);
		data &= ~(((1 << pclk->param.reg_भागider_width) - 1)
				<< pclk->param.reg_भागider_shअगरt);
		data |= भागider;
		xgene_clk_ग_लिखो(data, pclk->param.भागider_reg +
					pclk->param.reg_भागider_offset);
		pr_debug("%s clock set rate %ld\n", clk_hw_get_name(hw),
			parent_rate / भागider_save);
	पूर्ण अन्यथा अणु
		भागider_save = 1;
	पूर्ण

	अगर (pclk->lock)
		spin_unlock_irqrestore(pclk->lock, flags);

	वापस parent_rate / भागider_save;
पूर्ण

अटल दीर्घ xgene_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा xgene_clk *pclk = to_xgene_clk(hw);
	अचिन्हित दीर्घ parent_rate = *prate;
	u32 भागider;

	अगर (pclk->param.भागider_reg) अणु
		/* Let's compute the भागider */
		अगर (rate > parent_rate)
			rate = parent_rate;
		भागider = parent_rate / rate;   /* Rounded करोwn */
	पूर्ण अन्यथा अणु
		भागider = 1;
	पूर्ण

	वापस parent_rate / भागider;
पूर्ण

अटल स्थिर काष्ठा clk_ops xgene_clk_ops = अणु
	.enable = xgene_clk_enable,
	.disable = xgene_clk_disable,
	.is_enabled = xgene_clk_is_enabled,
	.recalc_rate = xgene_clk_recalc_rate,
	.set_rate = xgene_clk_set_rate,
	.round_rate = xgene_clk_round_rate,
पूर्ण;

अटल काष्ठा clk *xgene_रेजिस्टर_clk(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		काष्ठा xgene_dev_parameters *parameters, spinlock_t *lock)
अणु
	काष्ठा xgene_clk *apmclk;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	पूर्णांक rc;

	/* allocate the APM घड़ी काष्ठाure */
	apmclk = kzalloc(माप(*apmclk), GFP_KERNEL);
	अगर (!apmclk)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &xgene_clk_ops;
	init.flags = 0;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	apmclk->lock = lock;
	apmclk->hw.init = &init;
	apmclk->param = *parameters;

	/* Register the घड़ी */
	clk = clk_रेजिस्टर(dev, &apmclk->hw);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: could not register clk %s\n", __func__, name);
		kमुक्त(apmclk);
		वापस clk;
	पूर्ण

	/* Register the घड़ी क्रम lookup */
	rc = clk_रेजिस्टर_clkdev(clk, name, शून्य);
	अगर (rc != 0) अणु
		pr_err("%s: could not register lookup clk %s\n",
			__func__, name);
	पूर्ण
	वापस clk;
पूर्ण

अटल व्योम __init xgene_devclk_init(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *clk_name = np->full_name;
	काष्ठा clk *clk;
	काष्ठा resource res;
	पूर्णांक rc;
	काष्ठा xgene_dev_parameters parameters;
	पूर्णांक i;

	/* Check अगर the entry is disabled */
        अगर (!of_device_is_available(np))
                वापस;

	/* Parse the DTS रेजिस्टर क्रम resource */
	parameters.csr_reg = शून्य;
	parameters.भागider_reg = शून्य;
	क्रम (i = 0; i < 2; i++) अणु
		व्योम __iomem *map_res;
		rc = of_address_to_resource(np, i, &res);
		अगर (rc != 0) अणु
			अगर (i == 0) अणु
				pr_err("no DTS register for %pOF\n", np);
				वापस;
			पूर्ण
			अवरोध;
		पूर्ण
		map_res = of_iomap(np, i);
		अगर (!map_res) अणु
			pr_err("Unable to map resource %d for %pOF\n", i, np);
			जाओ err;
		पूर्ण
		अगर (म_भेद(res.name, "div-reg") == 0)
			parameters.भागider_reg = map_res;
		अन्यथा /* अगर (म_भेद(res->name, "csr-reg") == 0) */
			parameters.csr_reg = map_res;
	पूर्ण
	अगर (of_property_पढ़ो_u32(np, "csr-offset", &parameters.reg_csr_offset))
		parameters.reg_csr_offset = 0;
	अगर (of_property_पढ़ो_u32(np, "csr-mask", &parameters.reg_csr_mask))
		parameters.reg_csr_mask = 0xF;
	अगर (of_property_पढ़ो_u32(np, "enable-offset",
				&parameters.reg_clk_offset))
		parameters.reg_clk_offset = 0x8;
	अगर (of_property_पढ़ो_u32(np, "enable-mask", &parameters.reg_clk_mask))
		parameters.reg_clk_mask = 0xF;
	अगर (of_property_पढ़ो_u32(np, "divider-offset",
				&parameters.reg_भागider_offset))
		parameters.reg_भागider_offset = 0;
	अगर (of_property_पढ़ो_u32(np, "divider-width",
				&parameters.reg_भागider_width))
		parameters.reg_भागider_width = 0;
	अगर (of_property_पढ़ो_u32(np, "divider-shift",
				&parameters.reg_भागider_shअगरt))
		parameters.reg_भागider_shअगरt = 0;
	of_property_पढ़ो_string(np, "clock-output-names", &clk_name);

	clk = xgene_रेजिस्टर_clk(शून्य, clk_name,
		of_clk_get_parent_name(np, 0), &parameters, &clk_lock);
	अगर (IS_ERR(clk))
		जाओ err;
	pr_debug("Add %s clock\n", clk_name);
	rc = of_clk_add_provider(np, of_clk_src_simple_get, clk);
	अगर (rc != 0)
		pr_err("%s: could register provider clk %pOF\n", __func__, np);

	वापस;

err:
	अगर (parameters.csr_reg)
		iounmap(parameters.csr_reg);
	अगर (parameters.भागider_reg)
		iounmap(parameters.भागider_reg);
पूर्ण

CLK_OF_DECLARE(xgene_socpll_घड़ी, "apm,xgene-socpll-clock", xgene_socpllclk_init);
CLK_OF_DECLARE(xgene_pcppll_घड़ी, "apm,xgene-pcppll-clock", xgene_pcppllclk_init);
CLK_OF_DECLARE(xgene_pmd_घड़ी, "apm,xgene-pmd-clock", xgene_pmdclk_init);
CLK_OF_DECLARE(xgene_socpll_v2_घड़ी, "apm,xgene-socpll-v2-clock",
	       xgene_socpllclk_init);
CLK_OF_DECLARE(xgene_pcppll_v2_घड़ी, "apm,xgene-pcppll-v2-clock",
	       xgene_pcppllclk_init);
CLK_OF_DECLARE(xgene_dev_घड़ी, "apm,xgene-device-clock", xgene_devclk_init);
