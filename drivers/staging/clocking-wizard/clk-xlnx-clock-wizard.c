<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx 'Clocking Wizard' driver
 *
 *  Copyright (C) 2013 - 2014 Xilinx
 *
 *  Sथघren Brinkmann <soren.brinkmann@xilinx.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/iopoll.h>

#घोषणा WZRD_NUM_OUTPUTS	7
#घोषणा WZRD_ACLK_MAX_FREQ	250000000UL

#घोषणा WZRD_CLK_CFG_REG(n)	(0x200 + 4 * (n))

#घोषणा WZRD_CLKOUT0_FRAC_EN	BIT(18)
#घोषणा WZRD_CLKFBOUT_FRAC_EN	BIT(26)

#घोषणा WZRD_CLKFBOUT_MULT_SHIFT	8
#घोषणा WZRD_CLKFBOUT_MULT_MASK		(0xff << WZRD_CLKFBOUT_MULT_SHIFT)
#घोषणा WZRD_CLKFBOUT_FRAC_SHIFT	16
#घोषणा WZRD_CLKFBOUT_FRAC_MASK		(0x3ff << WZRD_CLKFBOUT_FRAC_SHIFT)
#घोषणा WZRD_DIVCLK_DIVIDE_SHIFT	0
#घोषणा WZRD_DIVCLK_DIVIDE_MASK		(0xff << WZRD_DIVCLK_DIVIDE_SHIFT)
#घोषणा WZRD_CLKOUT_DIVIDE_SHIFT	0
#घोषणा WZRD_CLKOUT_DIVIDE_WIDTH	8
#घोषणा WZRD_CLKOUT_DIVIDE_MASK		(0xff << WZRD_DIVCLK_DIVIDE_SHIFT)
#घोषणा WZRD_CLKOUT_FRAC_SHIFT		8
#घोषणा WZRD_CLKOUT_FRAC_MASK		0x3ff

#घोषणा WZRD_DR_MAX_INT_DIV_VALUE	255
#घोषणा WZRD_DR_STATUS_REG_OFFSET	0x04
#घोषणा WZRD_DR_LOCK_BIT_MASK		0x00000001
#घोषणा WZRD_DR_INIT_REG_OFFSET		0x25C
#घोषणा WZRD_DR_DIV_TO_PHASE_OFFSET	4
#घोषणा WZRD_DR_BEGIN_DYNA_RECONF	0x03

#घोषणा WZRD_USEC_POLL		10
#घोषणा WZRD_TIMEOUT_POLL		1000
/* Get the mask from width */
#घोषणा भाग_mask(width)			((1 << (width)) - 1)

/* Extract भागider instance from घड़ी hardware instance */
#घोषणा to_clk_wzrd_भागider(_hw) container_of(_hw, काष्ठा clk_wzrd_भागider, hw)

क्रमागत clk_wzrd_पूर्णांक_clks अणु
	wzrd_clk_mul,
	wzrd_clk_mul_भाग,
	wzrd_clk_mul_frac,
	wzrd_clk_पूर्णांक_max
पूर्ण;

/**
 * काष्ठा clk_wzrd - Clock wizard निजी data काष्ठाure
 *
 * @clk_data:		Clock data
 * @nb:			Notअगरier block
 * @base:		Memory base
 * @clk_in1:		Handle to input घड़ी 'clk_in1'
 * @axi_clk:		Handle to input घड़ी 's_axi_aclk'
 * @clks_पूर्णांकernal:	Internal घड़ीs
 * @clkout:		Output घड़ीs
 * @speed_grade:	Speed grade of the device
 * @suspended:		Flag indicating घातer state of the device
 */
काष्ठा clk_wzrd अणु
	काष्ठा clk_onecell_data clk_data;
	काष्ठा notअगरier_block nb;
	व्योम __iomem *base;
	काष्ठा clk *clk_in1;
	काष्ठा clk *axi_clk;
	काष्ठा clk *clks_पूर्णांकernal[wzrd_clk_पूर्णांक_max];
	काष्ठा clk *clkout[WZRD_NUM_OUTPUTS];
	अचिन्हित पूर्णांक speed_grade;
	bool suspended;
पूर्ण;

/**
 * काष्ठा clk_wzrd_भागider - घड़ी भागider specअगरic to clk_wzrd
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @base:	base address of रेजिस्टर containing the भागider
 * @offset:	offset address of रेजिस्टर containing the भागider
 * @shअगरt:	shअगरt to the भागider bit field
 * @width:	width of the भागider bit field
 * @flags:	clk_wzrd भागider flags
 * @table:	array of value/भागider pairs, last entry should have भाग = 0
 * @lock:	रेजिस्टर lock
 */
काष्ठा clk_wzrd_भागider अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	u16 offset;
	u8 shअगरt;
	u8 width;
	u8 flags;
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
	spinlock_t *lock;  /* भागider lock */
पूर्ण;

#घोषणा to_clk_wzrd(_nb) container_of(_nb, काष्ठा clk_wzrd, nb)

/* maximum frequencies क्रम input/output घड़ीs per speed grade */
अटल स्थिर अचिन्हित दीर्घ clk_wzrd_max_freq[] = अणु
	800000000UL,
	933000000UL,
	1066000000UL
पूर्ण;

/* spin lock variable क्रम clk_wzrd */
अटल DEFINE_SPINLOCK(clkwzrd_lock);

अटल अचिन्हित दीर्घ clk_wzrd_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_wzrd_भागider *भागider = to_clk_wzrd_भागider(hw);
	व्योम __iomem *भाग_addr = भागider->base + भागider->offset;
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(भाग_addr) >> भागider->shअगरt;
	val &= भाग_mask(भागider->width);

	वापस भागider_recalc_rate(hw, parent_rate, val, भागider->table,
			भागider->flags, भागider->width);
पूर्ण

अटल पूर्णांक clk_wzrd_dynamic_reconfig(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक err;
	u32 value;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा clk_wzrd_भागider *भागider = to_clk_wzrd_भागider(hw);
	व्योम __iomem *भाग_addr = भागider->base + भागider->offset;

	अगर (भागider->lock)
		spin_lock_irqsave(भागider->lock, flags);
	अन्यथा
		__acquire(भागider->lock);

	value = DIV_ROUND_CLOSEST(parent_rate, rate);

	/* Cap the value to max */
	min_t(u32, value, WZRD_DR_MAX_INT_DIV_VALUE);

	/* Set भागisor and clear phase offset */
	ग_लिखोl(value, भाग_addr);
	ग_लिखोl(0x00, भाग_addr + WZRD_DR_DIV_TO_PHASE_OFFSET);

	/* Check status रेजिस्टर */
	err = पढ़ोl_poll_समयout(भागider->base + WZRD_DR_STATUS_REG_OFFSET,
				 value, value & WZRD_DR_LOCK_BIT_MASK,
				 WZRD_USEC_POLL, WZRD_TIMEOUT_POLL);
	अगर (err)
		जाओ err_reconfig;

	/* Initiate reconfiguration */
	ग_लिखोl(WZRD_DR_BEGIN_DYNA_RECONF,
	       भागider->base + WZRD_DR_INIT_REG_OFFSET);

	/* Check status रेजिस्टर */
	err = पढ़ोl_poll_समयout(भागider->base + WZRD_DR_STATUS_REG_OFFSET,
				 value, value & WZRD_DR_LOCK_BIT_MASK,
				 WZRD_USEC_POLL, WZRD_TIMEOUT_POLL);
err_reconfig:
	अगर (भागider->lock)
		spin_unlock_irqrestore(भागider->lock, flags);
	अन्यथा
		__release(भागider->lock);
	वापस err;
पूर्ण

अटल दीर्घ clk_wzrd_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	u8 भाग;

	/*
	 * since we करोn't change parent rate we just round rate to बंदst
	 * achievable
	 */
	भाग = DIV_ROUND_CLOSEST(*prate, rate);

	वापस *prate / भाग;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_wzrd_clk_भागider_ops = अणु
	.round_rate = clk_wzrd_round_rate,
	.set_rate = clk_wzrd_dynamic_reconfig,
	.recalc_rate = clk_wzrd_recalc_rate,
पूर्ण;

अटल अचिन्हित दीर्घ clk_wzrd_recalc_ratef(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित पूर्णांक val;
	u32 भाग, frac;
	काष्ठा clk_wzrd_भागider *भागider = to_clk_wzrd_भागider(hw);
	व्योम __iomem *भाग_addr = भागider->base + भागider->offset;

	val = पढ़ोl(भाग_addr);
	भाग = val & भाग_mask(भागider->width);
	frac = (val >> WZRD_CLKOUT_FRAC_SHIFT) & WZRD_CLKOUT_FRAC_MASK;

	वापस mult_frac(parent_rate, 1000, (भाग * 1000) + frac);
पूर्ण

अटल पूर्णांक clk_wzrd_dynamic_reconfig_f(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक err;
	u32 value, pre;
	अचिन्हित दीर्घ rate_भाग, f, घड़ीout0_भाग;
	काष्ठा clk_wzrd_भागider *भागider = to_clk_wzrd_भागider(hw);
	व्योम __iomem *भाग_addr = भागider->base + भागider->offset;

	rate_भाग = ((parent_rate * 1000) / rate);
	घड़ीout0_भाग = rate_भाग / 1000;

	pre = DIV_ROUND_CLOSEST((parent_rate * 1000), rate);
	f = (u32)(pre - (घड़ीout0_भाग * 1000));
	f = f & WZRD_CLKOUT_FRAC_MASK;
	f = f << WZRD_CLKOUT_DIVIDE_WIDTH;

	value = (f  | (घड़ीout0_भाग & WZRD_CLKOUT_DIVIDE_MASK));

	/* Set भागisor and clear phase offset */
	ग_लिखोl(value, भाग_addr);
	ग_लिखोl(0x0, भाग_addr + WZRD_DR_DIV_TO_PHASE_OFFSET);

	/* Check status रेजिस्टर */
	err = पढ़ोl_poll_समयout(भागider->base + WZRD_DR_STATUS_REG_OFFSET, value,
				 value & WZRD_DR_LOCK_BIT_MASK,
				 WZRD_USEC_POLL, WZRD_TIMEOUT_POLL);
	अगर (err)
		वापस err;

	/* Initiate reconfiguration */
	ग_लिखोl(WZRD_DR_BEGIN_DYNA_RECONF,
	       भागider->base + WZRD_DR_INIT_REG_OFFSET);

	/* Check status रेजिस्टर */
	वापस पढ़ोl_poll_समयout(भागider->base + WZRD_DR_STATUS_REG_OFFSET, value,
				value & WZRD_DR_LOCK_BIT_MASK,
				WZRD_USEC_POLL, WZRD_TIMEOUT_POLL);
पूर्ण

अटल दीर्घ clk_wzrd_round_rate_f(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_wzrd_clk_भागider_ops_f = अणु
	.round_rate = clk_wzrd_round_rate_f,
	.set_rate = clk_wzrd_dynamic_reconfig_f,
	.recalc_rate = clk_wzrd_recalc_ratef,
पूर्ण;

अटल काष्ठा clk *clk_wzrd_रेजिस्टर_भागf(काष्ठा device *dev,
					  स्थिर अक्षर *name,
					  स्थिर अक्षर *parent_name,
					  अचिन्हित दीर्घ flags,
					  व्योम __iomem *base, u16 offset,
					  u8 shअगरt, u8 width,
					  u8 clk_भागider_flags,
					  स्थिर काष्ठा clk_भाग_प्रकारable *table,
					  spinlock_t *lock)
अणु
	काष्ठा clk_wzrd_भागider *भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	भाग = devm_kzalloc(dev, माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;

	init.ops = &clk_wzrd_clk_भागider_ops_f;

	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	भाग->base = base;
	भाग->offset = offset;
	भाग->shअगरt = shअगरt;
	भाग->width = width;
	भाग->flags = clk_भागider_flags;
	भाग->lock = lock;
	भाग->hw.init = &init;
	भाग->table = table;

	hw = &भाग->hw;
	ret =  devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस hw->clk;
पूर्ण

अटल काष्ठा clk *clk_wzrd_रेजिस्टर_भागider(काष्ठा device *dev,
					     स्थिर अक्षर *name,
					     स्थिर अक्षर *parent_name,
					     अचिन्हित दीर्घ flags,
					     व्योम __iomem *base, u16 offset,
					     u8 shअगरt, u8 width,
					     u8 clk_भागider_flags,
					     स्थिर काष्ठा clk_भाग_प्रकारable *table,
					     spinlock_t *lock)
अणु
	काष्ठा clk_wzrd_भागider *भाग;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	भाग = devm_kzalloc(dev, माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_wzrd_clk_भागider_ops;
	init.flags = flags;
	init.parent_names =  &parent_name;
	init.num_parents =  1;

	भाग->base = base;
	भाग->offset = offset;
	भाग->shअगरt = shअगरt;
	भाग->width = width;
	भाग->flags = clk_भागider_flags;
	भाग->lock = lock;
	भाग->hw.init = &init;
	भाग->table = table;

	hw = &भाग->hw;
	ret = devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		hw = ERR_PTR(ret);

	वापस hw->clk;
पूर्ण

अटल पूर्णांक clk_wzrd_clk_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
				 व्योम *data)
अणु
	अचिन्हित दीर्घ max;
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा clk_wzrd *clk_wzrd = to_clk_wzrd(nb);

	अगर (clk_wzrd->suspended)
		वापस NOTIFY_OK;

	अगर (ndata->clk == clk_wzrd->clk_in1)
		max = clk_wzrd_max_freq[clk_wzrd->speed_grade - 1];
	अन्यथा अगर (ndata->clk == clk_wzrd->axi_clk)
		max = WZRD_ACLK_MAX_FREQ;
	अन्यथा
		वापस NOTIFY_DONE;	/* should never happen */

	चयन (event) अणु
	हाल PRE_RATE_CHANGE:
		अगर (ndata->new_rate > max)
			वापस NOTIFY_BAD;
		वापस NOTIFY_OK;
	हाल POST_RATE_CHANGE:
	हाल ABORT_RATE_CHANGE:
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused clk_wzrd_suspend(काष्ठा device *dev)
अणु
	काष्ठा clk_wzrd *clk_wzrd = dev_get_drvdata(dev);

	clk_disable_unprepare(clk_wzrd->axi_clk);
	clk_wzrd->suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused clk_wzrd_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा clk_wzrd *clk_wzrd = dev_get_drvdata(dev);

	ret = clk_prepare_enable(clk_wzrd->axi_clk);
	अगर (ret) अणु
		dev_err(dev, "unable to enable s_axi_aclk\n");
		वापस ret;
	पूर्ण

	clk_wzrd->suspended = false;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(clk_wzrd_dev_pm_ops, clk_wzrd_suspend,
			 clk_wzrd_resume);

अटल पूर्णांक clk_wzrd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret;
	u32 reg, reg_f, mult;
	अचिन्हित दीर्घ rate;
	स्थिर अक्षर *clk_name;
	व्योम __iomem *ctrl_reg;
	काष्ठा clk_wzrd *clk_wzrd;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक nr_outमाला_दो;
	अचिन्हित दीर्घ flags = 0;

	clk_wzrd = devm_kzalloc(&pdev->dev, माप(*clk_wzrd), GFP_KERNEL);
	अगर (!clk_wzrd)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, clk_wzrd);

	clk_wzrd->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(clk_wzrd->base))
		वापस PTR_ERR(clk_wzrd->base);

	ret = of_property_पढ़ो_u32(np, "xlnx,speed-grade", &clk_wzrd->speed_grade);
	अगर (!ret) अणु
		अगर (clk_wzrd->speed_grade < 1 || clk_wzrd->speed_grade > 3) अणु
			dev_warn(&pdev->dev, "invalid speed grade '%d'\n",
				 clk_wzrd->speed_grade);
			clk_wzrd->speed_grade = 0;
		पूर्ण
	पूर्ण

	clk_wzrd->clk_in1 = devm_clk_get(&pdev->dev, "clk_in1");
	अगर (IS_ERR(clk_wzrd->clk_in1)) अणु
		अगर (clk_wzrd->clk_in1 != ERR_PTR(-EPROBE_DEFER))
			dev_err(&pdev->dev, "clk_in1 not found\n");
		वापस PTR_ERR(clk_wzrd->clk_in1);
	पूर्ण

	clk_wzrd->axi_clk = devm_clk_get(&pdev->dev, "s_axi_aclk");
	अगर (IS_ERR(clk_wzrd->axi_clk)) अणु
		अगर (clk_wzrd->axi_clk != ERR_PTR(-EPROBE_DEFER))
			dev_err(&pdev->dev, "s_axi_aclk not found\n");
		वापस PTR_ERR(clk_wzrd->axi_clk);
	पूर्ण
	ret = clk_prepare_enable(clk_wzrd->axi_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "enabling s_axi_aclk failed\n");
		वापस ret;
	पूर्ण
	rate = clk_get_rate(clk_wzrd->axi_clk);
	अगर (rate > WZRD_ACLK_MAX_FREQ) अणु
		dev_err(&pdev->dev, "s_axi_aclk frequency (%lu) too high\n",
			rate);
		ret = -EINVAL;
		जाओ err_disable_clk;
	पूर्ण

	reg = पढ़ोl(clk_wzrd->base + WZRD_CLK_CFG_REG(0));
	reg_f = reg & WZRD_CLKFBOUT_FRAC_MASK;
	reg_f =  reg_f >> WZRD_CLKFBOUT_FRAC_SHIFT;

	reg = reg & WZRD_CLKFBOUT_MULT_MASK;
	reg =  reg >> WZRD_CLKFBOUT_MULT_SHIFT;
	mult = (reg * 1000) + reg_f;
	clk_name = kaप्र_लिखो(GFP_KERNEL, "%s_mul", dev_name(&pdev->dev));
	अगर (!clk_name) अणु
		ret = -ENOMEM;
		जाओ err_disable_clk;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "nr-outputs", &nr_outमाला_दो);
	अगर (ret || nr_outमाला_दो > WZRD_NUM_OUTPUTS) अणु
		ret = -EINVAL;
		जाओ err_disable_clk;
	पूर्ण
	अगर (nr_outमाला_दो == 1)
		flags = CLK_SET_RATE_PARENT;

	clk_wzrd->clks_पूर्णांकernal[wzrd_clk_mul] = clk_रेजिस्टर_fixed_factor
			(&pdev->dev, clk_name,
			 __clk_get_name(clk_wzrd->clk_in1),
			0, mult, 1000);
	अगर (IS_ERR(clk_wzrd->clks_पूर्णांकernal[wzrd_clk_mul])) अणु
		dev_err(&pdev->dev, "unable to register fixed-factor clock\n");
		ret = PTR_ERR(clk_wzrd->clks_पूर्णांकernal[wzrd_clk_mul]);
		जाओ err_disable_clk;
	पूर्ण

	clk_name = kaप्र_लिखो(GFP_KERNEL, "%s_mul_div", dev_name(&pdev->dev));
	अगर (!clk_name) अणु
		ret = -ENOMEM;
		जाओ err_rm_पूर्णांक_clk;
	पूर्ण

	ctrl_reg = clk_wzrd->base + WZRD_CLK_CFG_REG(0);
	/* रेजिस्टर भाग */
	clk_wzrd->clks_पूर्णांकernal[wzrd_clk_mul_भाग] = clk_रेजिस्टर_भागider
			(&pdev->dev, clk_name,
			 __clk_get_name(clk_wzrd->clks_पूर्णांकernal[wzrd_clk_mul]),
			flags, ctrl_reg, 0, 8, CLK_DIVIDER_ONE_BASED |
			CLK_DIVIDER_ALLOW_ZERO, &clkwzrd_lock);
	अगर (IS_ERR(clk_wzrd->clks_पूर्णांकernal[wzrd_clk_mul_भाग])) अणु
		dev_err(&pdev->dev, "unable to register divider clock\n");
		ret = PTR_ERR(clk_wzrd->clks_पूर्णांकernal[wzrd_clk_mul_भाग]);
		जाओ err_rm_पूर्णांक_clk;
	पूर्ण

	/* रेजिस्टर भाग per output */
	क्रम (i = nr_outमाला_दो - 1; i >= 0 ; i--) अणु
		स्थिर अक्षर *clkout_name;

		clkout_name = kaप्र_लिखो(GFP_KERNEL, "%s_out%d", dev_name(&pdev->dev), i);
		अगर (!clkout_name) अणु
			ret = -ENOMEM;
			जाओ err_rm_पूर्णांक_clk;
		पूर्ण

		अगर (!i)
			clk_wzrd->clkout[i] = clk_wzrd_रेजिस्टर_भागf
				(&pdev->dev, clkout_name,
				clk_name, flags,
				clk_wzrd->base, (WZRD_CLK_CFG_REG(2) + i * 12),
				WZRD_CLKOUT_DIVIDE_SHIFT,
				WZRD_CLKOUT_DIVIDE_WIDTH,
				CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
				शून्य, &clkwzrd_lock);
		अन्यथा
			clk_wzrd->clkout[i] = clk_wzrd_रेजिस्टर_भागider
				(&pdev->dev, clkout_name,
				clk_name, 0,
				clk_wzrd->base, (WZRD_CLK_CFG_REG(2) + i * 12),
				WZRD_CLKOUT_DIVIDE_SHIFT,
				WZRD_CLKOUT_DIVIDE_WIDTH,
				CLK_DIVIDER_ONE_BASED | CLK_DIVIDER_ALLOW_ZERO,
				शून्य, &clkwzrd_lock);
		अगर (IS_ERR(clk_wzrd->clkout[i])) अणु
			पूर्णांक j;

			क्रम (j = i + 1; j < nr_outमाला_दो; j++)
				clk_unरेजिस्टर(clk_wzrd->clkout[j]);
			dev_err(&pdev->dev,
				"unable to register divider clock\n");
			ret = PTR_ERR(clk_wzrd->clkout[i]);
			जाओ err_rm_पूर्णांक_clks;
		पूर्ण
	पूर्ण

	kमुक्त(clk_name);

	clk_wzrd->clk_data.clks = clk_wzrd->clkout;
	clk_wzrd->clk_data.clk_num = ARRAY_SIZE(clk_wzrd->clkout);
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_wzrd->clk_data);

	अगर (clk_wzrd->speed_grade) अणु
		clk_wzrd->nb.notअगरier_call = clk_wzrd_clk_notअगरier;

		ret = clk_notअगरier_रेजिस्टर(clk_wzrd->clk_in1,
					    &clk_wzrd->nb);
		अगर (ret)
			dev_warn(&pdev->dev,
				 "unable to register clock notifier\n");

		ret = clk_notअगरier_रेजिस्टर(clk_wzrd->axi_clk, &clk_wzrd->nb);
		अगर (ret)
			dev_warn(&pdev->dev,
				 "unable to register clock notifier\n");
	पूर्ण

	वापस 0;

err_rm_पूर्णांक_clks:
	clk_unरेजिस्टर(clk_wzrd->clks_पूर्णांकernal[1]);
err_rm_पूर्णांक_clk:
	kमुक्त(clk_name);
	clk_unरेजिस्टर(clk_wzrd->clks_पूर्णांकernal[0]);
err_disable_clk:
	clk_disable_unprepare(clk_wzrd->axi_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_wzrd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा clk_wzrd *clk_wzrd = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);

	क्रम (i = 0; i < WZRD_NUM_OUTPUTS; i++)
		clk_unरेजिस्टर(clk_wzrd->clkout[i]);
	क्रम (i = 0; i < wzrd_clk_पूर्णांक_max; i++)
		clk_unरेजिस्टर(clk_wzrd->clks_पूर्णांकernal[i]);

	अगर (clk_wzrd->speed_grade) अणु
		clk_notअगरier_unरेजिस्टर(clk_wzrd->axi_clk, &clk_wzrd->nb);
		clk_notअगरier_unरेजिस्टर(clk_wzrd->clk_in1, &clk_wzrd->nb);
	पूर्ण

	clk_disable_unprepare(clk_wzrd->axi_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id clk_wzrd_ids[] = अणु
	अणु .compatible = "xlnx,clocking-wizard" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_wzrd_ids);

अटल काष्ठा platक्रमm_driver clk_wzrd_driver = अणु
	.driver = अणु
		.name = "clk-wizard",
		.of_match_table = clk_wzrd_ids,
		.pm = &clk_wzrd_dev_pm_ops,
	पूर्ण,
	.probe = clk_wzrd_probe,
	.हटाओ = clk_wzrd_हटाओ,
पूर्ण;
module_platक्रमm_driver(clk_wzrd_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Soeren Brinkmann <soren.brinkmann@xilinx.com");
MODULE_DESCRIPTION("Driver for the Xilinx Clocking Wizard IP core");
