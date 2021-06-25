<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP
 *
 * Clock driver क्रम LS1028A Display output पूर्णांकerfaces(LCD, DPHY).
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitfield.h>

/* PLLDIG रेजिस्टर offsets and bit masks */
#घोषणा PLLDIG_REG_PLLSR            0x24
#घोषणा PLLDIG_LOCK_MASK            BIT(2)
#घोषणा PLLDIG_REG_PLLDV            0x28
#घोषणा PLLDIG_MFD_MASK             GENMASK(7, 0)
#घोषणा PLLDIG_RFDPHI1_MASK         GENMASK(30, 25)
#घोषणा PLLDIG_REG_PLLFM            0x2c
#घोषणा PLLDIG_SSCGBYP_ENABLE       BIT(30)
#घोषणा PLLDIG_REG_PLLFD            0x30
#घोषणा PLLDIG_FDEN                 BIT(30)
#घोषणा PLLDIG_FRAC_MASK            GENMASK(15, 0)
#घोषणा PLLDIG_REG_PLLCAL1          0x38
#घोषणा PLLDIG_REG_PLLCAL2          0x3c

/* Range of the VCO frequencies, in Hz */
#घोषणा PLLDIG_MIN_VCO_FREQ         650000000
#घोषणा PLLDIG_MAX_VCO_FREQ         1300000000

/* Range of the output frequencies, in Hz */
#घोषणा PHI1_MIN_FREQ               27000000UL
#घोषणा PHI1_MAX_FREQ               600000000UL

/* Maximum value of the reduced frequency भागider */
#घोषणा MAX_RFDPHI1          63UL

/* Best value of multiplication factor भागider */
#घोषणा PLLDIG_DEFAULT_MFD   44

/*
 * Denominator part of the fractional part of the
 * loop multiplication factor.
 */
#घोषणा MFDEN          20480

अटल स्थिर काष्ठा clk_parent_data parent_data[] = अणु
	अणु .index = 0 पूर्ण,
पूर्ण;

काष्ठा clk_plldig अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक vco_freq;
पूर्ण;

#घोषणा to_clk_plldig(_hw)	container_of(_hw, काष्ठा clk_plldig, hw)

अटल पूर्णांक plldig_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plldig *data = to_clk_plldig(hw);
	u32 val;

	val = पढ़ोl(data->regs + PLLDIG_REG_PLLFM);
	/*
	 * Use Bypass mode with PLL off by शेष, the frequency overshoot
	 * detector output was disable. SSCG Bypass mode should be enable.
	 */
	val |= PLLDIG_SSCGBYP_ENABLE;
	ग_लिखोl(val, data->regs + PLLDIG_REG_PLLFM);

	वापस 0;
पूर्ण

अटल व्योम plldig_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plldig *data = to_clk_plldig(hw);
	u32 val;

	val = पढ़ोl(data->regs + PLLDIG_REG_PLLFM);

	val &= ~PLLDIG_SSCGBYP_ENABLE;
	val |= FIELD_PREP(PLLDIG_SSCGBYP_ENABLE, 0x0);

	ग_लिखोl(val, data->regs + PLLDIG_REG_PLLFM);
पूर्ण

अटल पूर्णांक plldig_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plldig *data = to_clk_plldig(hw);

	वापस पढ़ोl(data->regs + PLLDIG_REG_PLLFM) &
			      PLLDIG_SSCGBYP_ENABLE;
पूर्ण

अटल अचिन्हित दीर्घ plldig_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_plldig *data = to_clk_plldig(hw);
	u32 val, rfdphi1;

	val = पढ़ोl(data->regs + PLLDIG_REG_PLLDV);

	/* Check अगर PLL is bypassed */
	अगर (val & PLLDIG_SSCGBYP_ENABLE)
		वापस parent_rate;

	rfdphi1 = FIELD_GET(PLLDIG_RFDPHI1_MASK, val);

	/*
	 * If RFDPHI1 has a value of 1 the VCO frequency is also भागided by
	 * one.
	 */
	अगर (!rfdphi1)
		rfdphi1 = 1;

	वापस DIV_ROUND_UP(data->vco_freq, rfdphi1);
पूर्ण

अटल अचिन्हित दीर्घ plldig_calc_target_भाग(अचिन्हित दीर्घ vco_freq,
					    अचिन्हित दीर्घ target_rate)
अणु
	अचिन्हित दीर्घ भाग;

	भाग = DIV_ROUND_CLOSEST(vco_freq, target_rate);
	भाग = clamp(भाग, 1UL, MAX_RFDPHI1);

	वापस भाग;
पूर्ण

अटल पूर्णांक plldig_determine_rate(काष्ठा clk_hw *hw,
				 काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_plldig *data = to_clk_plldig(hw);
	अचिन्हित पूर्णांक भाग;

	req->rate = clamp(req->rate, PHI1_MIN_FREQ, PHI1_MAX_FREQ);
	भाग = plldig_calc_target_भाग(data->vco_freq, req->rate);
	req->rate = DIV_ROUND_UP(data->vco_freq, भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक plldig_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_plldig *data = to_clk_plldig(hw);
	अचिन्हित पूर्णांक val, cond;
	अचिन्हित पूर्णांक rfdphi1;

	rate = clamp(rate, PHI1_MIN_FREQ, PHI1_MAX_FREQ);
	rfdphi1 = plldig_calc_target_भाग(data->vco_freq, rate);

	/* update the भागider value */
	val = पढ़ोl(data->regs + PLLDIG_REG_PLLDV);
	val &= ~PLLDIG_RFDPHI1_MASK;
	val |= FIELD_PREP(PLLDIG_RFDPHI1_MASK, rfdphi1);
	ग_लिखोl(val, data->regs + PLLDIG_REG_PLLDV);

	/* रुकोing क्रम old lock state to clear */
	udelay(200);

	/* Wait until PLL is locked or समयout */
	वापस पढ़ोl_poll_समयout_atomic(data->regs + PLLDIG_REG_PLLSR, cond,
					 cond & PLLDIG_LOCK_MASK, 0,
					 USEC_PER_MSEC);
पूर्ण

अटल स्थिर काष्ठा clk_ops plldig_clk_ops = अणु
	.enable = plldig_enable,
	.disable = plldig_disable,
	.is_enabled = plldig_is_enabled,
	.recalc_rate = plldig_recalc_rate,
	.determine_rate = plldig_determine_rate,
	.set_rate = plldig_set_rate,
पूर्ण;

अटल पूर्णांक plldig_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_plldig *data = to_clk_plldig(hw);
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित दीर्घ val;
	अचिन्हित दीर्घ दीर्घ llपंचांगp;
	अचिन्हित पूर्णांक mfd, fracभाग = 0;

	अगर (!parent)
		वापस -EINVAL;

	parent_rate = clk_hw_get_rate(parent);

	अगर (data->vco_freq) अणु
		mfd = data->vco_freq / parent_rate;
		llपंचांगp = data->vco_freq % parent_rate;
		llपंचांगp *= MFDEN;
		करो_भाग(llपंचांगp, parent_rate);
		fracभाग = llपंचांगp;
	पूर्ण अन्यथा अणु
		mfd = PLLDIG_DEFAULT_MFD;
		data->vco_freq = parent_rate * mfd;
	पूर्ण

	val = FIELD_PREP(PLLDIG_MFD_MASK, mfd);
	ग_लिखोl(val, data->regs + PLLDIG_REG_PLLDV);

	/* Enable fractional भागider */
	अगर (fracभाग) अणु
		val = FIELD_PREP(PLLDIG_FRAC_MASK, fracभाग);
		val |= PLLDIG_FDEN;
		ग_लिखोl(val, data->regs + PLLDIG_REG_PLLFD);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक plldig_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_plldig *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->regs))
		वापस PTR_ERR(data->regs);

	data->hw.init = CLK_HW_INIT_PARENTS_DATA("dpclk",
						 parent_data,
						 &plldig_clk_ops,
						 0);

	ret = devm_clk_hw_रेजिस्टर(dev, &data->hw);
	अगर (ret) अणु
		dev_err(dev, "failed to register %s clock\n",
						dev->of_node->name);
		वापस ret;
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					  &data->hw);
	अगर (ret) अणु
		dev_err(dev, "unable to add clk provider\n");
		वापस ret;
	पूर्ण

	/*
	 * The frequency of the VCO cannot be changed during runसमय.
	 * Thereक्रमe, let the user specअगरy a desired frequency.
	 */
	अगर (!of_property_पढ़ो_u32(dev->of_node, "fsl,vco-hz",
				  &data->vco_freq)) अणु
		अगर (data->vco_freq < PLLDIG_MIN_VCO_FREQ ||
		    data->vco_freq > PLLDIG_MAX_VCO_FREQ)
			वापस -EINVAL;
	पूर्ण

	वापस plldig_init(&data->hw);
पूर्ण

अटल स्थिर काष्ठा of_device_id plldig_clk_id[] = अणु
	अणु .compatible = "fsl,ls1028a-plldig" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, plldig_clk_id);

अटल काष्ठा platक्रमm_driver plldig_clk_driver = अणु
	.driver = अणु
		.name = "plldig-clock",
		.of_match_table = plldig_clk_id,
	पूर्ण,
	.probe = plldig_clk_probe,
पूर्ण;
module_platक्रमm_driver(plldig_clk_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Wen He <wen.he_1@nxp.com>");
MODULE_DESCRIPTION("LS1028A Display output interface pixel clock driver");
