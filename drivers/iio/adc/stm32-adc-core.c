<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is part of STM32 ADC driver
 *
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>.
 *
 * Inspired from: fsl-imx25-tsadc
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqdesc.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश "stm32-adc-core.h"

#घोषणा STM32_ADC_CORE_SLEEP_DELAY_MS	2000

/* SYSCFG रेजिस्टरs */
#घोषणा STM32MP1_SYSCFG_PMCSETR		0x04
#घोषणा STM32MP1_SYSCFG_PMCCLRR		0x44

/* SYSCFG bit fields */
#घोषणा STM32MP1_SYSCFG_ANASWVDD_MASK	BIT(9)

/* SYSCFG capability flags */
#घोषणा HAS_VBOOSTER		BIT(0)
#घोषणा HAS_ANASWVDD		BIT(1)

/**
 * काष्ठा sपंचांग32_adc_common_regs - sपंचांग32 common रेजिस्टरs
 * @csr:	common status रेजिस्टर offset
 * @ccr:	common control रेजिस्टर offset
 * @eoc_msk:    array of eoc (end of conversion flag) masks in csr क्रम adc1..n
 * @ovr_msk:    array of ovr (overrun flag) masks in csr क्रम adc1..n
 * @ier:	पूर्णांकerrupt enable रेजिस्टर offset क्रम each adc
 * @eocie_msk:	end of conversion पूर्णांकerrupt enable mask in @ier
 */
काष्ठा sपंचांग32_adc_common_regs अणु
	u32 csr;
	u32 ccr;
	u32 eoc_msk[STM32_ADC_MAX_ADCS];
	u32 ovr_msk[STM32_ADC_MAX_ADCS];
	u32 ier;
	u32 eocie_msk;
पूर्ण;

काष्ठा sपंचांग32_adc_priv;

/**
 * काष्ठा sपंचांग32_adc_priv_cfg - sपंचांग32 core compatible configuration data
 * @regs:	common रेजिस्टरs क्रम all instances
 * @clk_sel:	घड़ी selection routine
 * @max_clk_rate_hz: maximum analog घड़ी rate (Hz, from datasheet)
 * @has_syscfg: SYSCFG capability flags
 * @num_irqs:	number of पूर्णांकerrupt lines
 */
काष्ठा sपंचांग32_adc_priv_cfg अणु
	स्थिर काष्ठा sपंचांग32_adc_common_regs *regs;
	पूर्णांक (*clk_sel)(काष्ठा platक्रमm_device *, काष्ठा sपंचांग32_adc_priv *);
	u32 max_clk_rate_hz;
	अचिन्हित पूर्णांक has_syscfg;
	अचिन्हित पूर्णांक num_irqs;
पूर्ण;

/**
 * काष्ठा sपंचांग32_adc_priv - sपंचांग32 ADC core निजी data
 * @irq:		irq(s) क्रम ADC block
 * @करोमुख्य:		irq करोमुख्य reference
 * @aclk:		घड़ी reference क्रम the analog circuitry
 * @bclk:		bus घड़ी common क्रम all ADCs, depends on part used
 * @max_clk_rate:	desired maximum घड़ी rate
 * @booster:		booster supply reference
 * @vdd:		vdd supply reference
 * @vdda:		vdda analog supply reference
 * @vref:		regulator reference
 * @vdd_uv:		vdd supply voltage (microvolts)
 * @vdda_uv:		vdda supply voltage (microvolts)
 * @cfg:		compatible configuration data
 * @common:		common data क्रम all ADC instances
 * @ccr_bak:		backup CCR in low घातer mode
 * @syscfg:		reference to syscon, प्रणाली control रेजिस्टरs
 */
काष्ठा sपंचांग32_adc_priv अणु
	पूर्णांक				irq[STM32_ADC_MAX_ADCS];
	काष्ठा irq_करोमुख्य		*करोमुख्य;
	काष्ठा clk			*aclk;
	काष्ठा clk			*bclk;
	u32				max_clk_rate;
	काष्ठा regulator		*booster;
	काष्ठा regulator		*vdd;
	काष्ठा regulator		*vdda;
	काष्ठा regulator		*vref;
	पूर्णांक				vdd_uv;
	पूर्णांक				vdda_uv;
	स्थिर काष्ठा sपंचांग32_adc_priv_cfg	*cfg;
	काष्ठा sपंचांग32_adc_common		common;
	u32				ccr_bak;
	काष्ठा regmap			*syscfg;
पूर्ण;

अटल काष्ठा sपंचांग32_adc_priv *to_sपंचांग32_adc_priv(काष्ठा sपंचांग32_adc_common *com)
अणु
	वापस container_of(com, काष्ठा sपंचांग32_adc_priv, common);
पूर्ण

/* STM32F4 ADC पूर्णांकernal common घड़ी prescaler भागision ratios */
अटल पूर्णांक sपंचांग32f4_pclk_भाग[] = अणु2, 4, 6, 8पूर्ण;

/**
 * sपंचांग32f4_adc_clk_sel() - Select sपंचांग32f4 ADC common घड़ी prescaler
 * @pdev: platक्रमm device
 * @priv: sपंचांग32 ADC core निजी data
 * Select घड़ी prescaler used क्रम analog conversions, beक्रमe using ADC.
 */
अटल पूर्णांक sपंचांग32f4_adc_clk_sel(काष्ठा platक्रमm_device *pdev,
			       काष्ठा sपंचांग32_adc_priv *priv)
अणु
	अचिन्हित दीर्घ rate;
	u32 val;
	पूर्णांक i;

	/* sपंचांग32f4 has one clk input क्रम analog (mandatory), enक्रमce it here */
	अगर (!priv->aclk) अणु
		dev_err(&pdev->dev, "No 'adc' clock found\n");
		वापस -ENOENT;
	पूर्ण

	rate = clk_get_rate(priv->aclk);
	अगर (!rate) अणु
		dev_err(&pdev->dev, "Invalid clock rate: 0\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sपंचांग32f4_pclk_भाग); i++) अणु
		अगर ((rate / sपंचांग32f4_pclk_भाग[i]) <= priv->max_clk_rate)
			अवरोध;
	पूर्ण
	अगर (i >= ARRAY_SIZE(sपंचांग32f4_pclk_भाग)) अणु
		dev_err(&pdev->dev, "adc clk selection failed\n");
		वापस -EINVAL;
	पूर्ण

	priv->common.rate = rate / sपंचांग32f4_pclk_भाग[i];
	val = पढ़ोl_relaxed(priv->common.base + STM32F4_ADC_CCR);
	val &= ~STM32F4_ADC_ADCPRE_MASK;
	val |= i << STM32F4_ADC_ADCPRE_SHIFT;
	ग_लिखोl_relaxed(val, priv->common.base + STM32F4_ADC_CCR);

	dev_dbg(&pdev->dev, "Using analog clock source at %ld kHz\n",
		priv->common.rate / 1000);

	वापस 0;
पूर्ण

/**
 * काष्ठा sपंचांग32h7_adc_ck_spec - specअगरication क्रम sपंचांग32h7 adc घड़ी
 * @ckmode: ADC घड़ी mode, Async or sync with prescaler.
 * @presc: prescaler bitfield क्रम async घड़ी mode
 * @भाग: prescaler भागision ratio
 */
काष्ठा sपंचांग32h7_adc_ck_spec अणु
	u32 ckmode;
	u32 presc;
	पूर्णांक भाग;
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32h7_adc_ck_spec sपंचांग32h7_adc_ckmodes_spec[] = अणु
	/* 00: CK_ADC[1..3]: Asynchronous घड़ी modes */
	अणु 0, 0, 1 पूर्ण,
	अणु 0, 1, 2 पूर्ण,
	अणु 0, 2, 4 पूर्ण,
	अणु 0, 3, 6 पूर्ण,
	अणु 0, 4, 8 पूर्ण,
	अणु 0, 5, 10 पूर्ण,
	अणु 0, 6, 12 पूर्ण,
	अणु 0, 7, 16 पूर्ण,
	अणु 0, 8, 32 पूर्ण,
	अणु 0, 9, 64 पूर्ण,
	अणु 0, 10, 128 पूर्ण,
	अणु 0, 11, 256 पूर्ण,
	/* HCLK used: Synchronous घड़ी modes (1, 2 or 4 prescaler) */
	अणु 1, 0, 1 पूर्ण,
	अणु 2, 0, 2 पूर्ण,
	अणु 3, 0, 4 पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32h7_adc_clk_sel(काष्ठा platक्रमm_device *pdev,
			       काष्ठा sपंचांग32_adc_priv *priv)
अणु
	u32 ckmode, presc, val;
	अचिन्हित दीर्घ rate;
	पूर्णांक i, भाग, duty;

	/* sपंचांग32h7 bus घड़ी is common क्रम all ADC instances (mandatory) */
	अगर (!priv->bclk) अणु
		dev_err(&pdev->dev, "No 'bus' clock found\n");
		वापस -ENOENT;
	पूर्ण

	/*
	 * sपंचांग32h7 can use either 'bus' or 'adc' घड़ी क्रम analog circuitry.
	 * So, choice is to have bus घड़ी mandatory and adc घड़ी optional.
	 * If optional 'adc' घड़ी has been found, then try to use it first.
	 */
	अगर (priv->aclk) अणु
		/*
		 * Asynchronous घड़ी modes (e.g. ckmode == 0)
		 * From spec: PLL output musn't exceed max rate
		 */
		rate = clk_get_rate(priv->aclk);
		अगर (!rate) अणु
			dev_err(&pdev->dev, "Invalid adc clock rate: 0\n");
			वापस -EINVAL;
		पूर्ण

		/* If duty is an error, kindly use at least /2 भागider */
		duty = clk_get_scaled_duty_cycle(priv->aclk, 100);
		अगर (duty < 0)
			dev_warn(&pdev->dev, "adc clock duty: %d\n", duty);

		क्रम (i = 0; i < ARRAY_SIZE(sपंचांग32h7_adc_ckmodes_spec); i++) अणु
			ckmode = sपंचांग32h7_adc_ckmodes_spec[i].ckmode;
			presc = sपंचांग32h7_adc_ckmodes_spec[i].presc;
			भाग = sपंचांग32h7_adc_ckmodes_spec[i].भाग;

			अगर (ckmode)
				जारी;

			/*
			 * For proper operation, घड़ी duty cycle range is 49%
			 * to 51%. Apply at least /2 prescaler otherwise.
			 */
			अगर (भाग == 1 && (duty < 49 || duty > 51))
				जारी;

			अगर ((rate / भाग) <= priv->max_clk_rate)
				जाओ out;
		पूर्ण
	पूर्ण

	/* Synchronous घड़ी modes (e.g. ckmode is 1, 2 or 3) */
	rate = clk_get_rate(priv->bclk);
	अगर (!rate) अणु
		dev_err(&pdev->dev, "Invalid bus clock rate: 0\n");
		वापस -EINVAL;
	पूर्ण

	duty = clk_get_scaled_duty_cycle(priv->bclk, 100);
	अगर (duty < 0)
		dev_warn(&pdev->dev, "bus clock duty: %d\n", duty);

	क्रम (i = 0; i < ARRAY_SIZE(sपंचांग32h7_adc_ckmodes_spec); i++) अणु
		ckmode = sपंचांग32h7_adc_ckmodes_spec[i].ckmode;
		presc = sपंचांग32h7_adc_ckmodes_spec[i].presc;
		भाग = sपंचांग32h7_adc_ckmodes_spec[i].भाग;

		अगर (!ckmode)
			जारी;

		अगर (भाग == 1 && (duty < 49 || duty > 51))
			जारी;

		अगर ((rate / भाग) <= priv->max_clk_rate)
			जाओ out;
	पूर्ण

	dev_err(&pdev->dev, "adc clk selection failed\n");
	वापस -EINVAL;

out:
	/* rate used later by each ADC instance to control BOOST mode */
	priv->common.rate = rate / भाग;

	/* Set common घड़ी mode and prescaler */
	val = पढ़ोl_relaxed(priv->common.base + STM32H7_ADC_CCR);
	val &= ~(STM32H7_CKMODE_MASK | STM32H7_PRESC_MASK);
	val |= ckmode << STM32H7_CKMODE_SHIFT;
	val |= presc << STM32H7_PRESC_SHIFT;
	ग_लिखोl_relaxed(val, priv->common.base + STM32H7_ADC_CCR);

	dev_dbg(&pdev->dev, "Using %s clock/%d source at %ld kHz\n",
		ckmode ? "bus" : "adc", भाग, priv->common.rate / 1000);

	वापस 0;
पूर्ण

/* STM32F4 common रेजिस्टरs definitions */
अटल स्थिर काष्ठा sपंचांग32_adc_common_regs sपंचांग32f4_adc_common_regs = अणु
	.csr = STM32F4_ADC_CSR,
	.ccr = STM32F4_ADC_CCR,
	.eoc_msk = अणु STM32F4_EOC1, STM32F4_EOC2, STM32F4_EOC3पूर्ण,
	.ovr_msk = अणु STM32F4_OVR1, STM32F4_OVR2, STM32F4_OVR3पूर्ण,
	.ier = STM32F4_ADC_CR1,
	.eocie_msk = STM32F4_EOCIE,
पूर्ण;

/* STM32H7 common रेजिस्टरs definitions */
अटल स्थिर काष्ठा sपंचांग32_adc_common_regs sपंचांग32h7_adc_common_regs = अणु
	.csr = STM32H7_ADC_CSR,
	.ccr = STM32H7_ADC_CCR,
	.eoc_msk = अणु STM32H7_EOC_MST, STM32H7_EOC_SLVपूर्ण,
	.ovr_msk = अणु STM32H7_OVR_MST, STM32H7_OVR_SLVपूर्ण,
	.ier = STM32H7_ADC_IER,
	.eocie_msk = STM32H7_EOCIE,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sपंचांग32_adc_offset[STM32_ADC_MAX_ADCS] = अणु
	0, STM32_ADC_OFFSET, STM32_ADC_OFFSET * 2,
पूर्ण;

अटल अचिन्हित पूर्णांक sपंचांग32_adc_eoc_enabled(काष्ठा sपंचांग32_adc_priv *priv,
					  अचिन्हित पूर्णांक adc)
अणु
	u32 ier, offset = sपंचांग32_adc_offset[adc];

	ier = पढ़ोl_relaxed(priv->common.base + offset + priv->cfg->regs->ier);

	वापस ier & priv->cfg->regs->eocie_msk;
पूर्ण

/* ADC common पूर्णांकerrupt क्रम all instances */
अटल व्योम sपंचांग32_adc_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा sपंचांग32_adc_priv *priv = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक i;
	u32 status;

	chained_irq_enter(chip, desc);
	status = पढ़ोl_relaxed(priv->common.base + priv->cfg->regs->csr);

	/*
	 * End of conversion may be handled by using IRQ or DMA. There may be a
	 * race here when two conversions complete at the same समय on several
	 * ADCs. EOC may be पढ़ो 'set' क्रम several ADCs, with:
	 * - an ADC configured to use DMA (EOC triggers the DMA request, and
	 *   is then स्वतःmatically cleared by DR पढ़ो in hardware)
	 * - an ADC configured to use IRQs (EOCIE bit is set. The handler must
	 *   be called in this हाल)
	 * So both EOC status bit in CSR and EOCIE control bit must be checked
	 * beक्रमe invoking the पूर्णांकerrupt handler (e.g. call ISR only क्रम
	 * IRQ-enabled ADCs).
	 */
	क्रम (i = 0; i < priv->cfg->num_irqs; i++) अणु
		अगर ((status & priv->cfg->regs->eoc_msk[i] &&
		     sपंचांग32_adc_eoc_enabled(priv, i)) ||
		     (status & priv->cfg->regs->ovr_msk[i]))
			generic_handle_irq(irq_find_mapping(priv->करोमुख्य, i));
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण;

अटल पूर्णांक sपंचांग32_adc_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(irq, d->host_data);
	irq_set_chip_and_handler(irq, &dummy_irq_chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_adc_करोमुख्य_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops sपंचांग32_adc_करोमुख्य_ops = अणु
	.map = sपंचांग32_adc_करोमुख्य_map,
	.unmap  = sपंचांग32_adc_करोमुख्य_unmap,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक sपंचांग32_adc_irq_probe(काष्ठा platक्रमm_device *pdev,
			       काष्ठा sपंचांग32_adc_priv *priv)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	अचिन्हित पूर्णांक i;

	/*
	 * Interrupt(s) must be provided, depending on the compatible:
	 * - sपंचांग32f4/h7 shares a common पूर्णांकerrupt line.
	 * - sपंचांग32mp1, has one line per ADC
	 */
	क्रम (i = 0; i < priv->cfg->num_irqs; i++) अणु
		priv->irq[i] = platक्रमm_get_irq(pdev, i);
		अगर (priv->irq[i] < 0)
			वापस priv->irq[i];
	पूर्ण

	priv->करोमुख्य = irq_करोमुख्य_add_simple(np, STM32_ADC_MAX_ADCS, 0,
					     &sपंचांग32_adc_करोमुख्य_ops,
					     priv);
	अगर (!priv->करोमुख्य) अणु
		dev_err(&pdev->dev, "Failed to add irq domain\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < priv->cfg->num_irqs; i++) अणु
		irq_set_chained_handler(priv->irq[i], sपंचांग32_adc_irq_handler);
		irq_set_handler_data(priv->irq[i], priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_adc_irq_हटाओ(काष्ठा platक्रमm_device *pdev,
				 काष्ठा sपंचांग32_adc_priv *priv)
अणु
	पूर्णांक hwirq;
	अचिन्हित पूर्णांक i;

	क्रम (hwirq = 0; hwirq < STM32_ADC_MAX_ADCS; hwirq++)
		irq_dispose_mapping(irq_find_mapping(priv->करोमुख्य, hwirq));
	irq_करोमुख्य_हटाओ(priv->करोमुख्य);

	क्रम (i = 0; i < priv->cfg->num_irqs; i++)
		irq_set_chained_handler(priv->irq[i], शून्य);
पूर्ण

अटल पूर्णांक sपंचांग32_adc_core_चयनes_supply_en(काष्ठा sपंचांग32_adc_priv *priv,
					     काष्ठा device *dev)
अणु
	पूर्णांक ret;

	/*
	 * On STM32H7 and STM32MP1, the ADC inमाला_दो are multiplexed with analog
	 * चयनes (via PCSEL) which have reduced perक्रमmances when their
	 * supply is below 2.7V (vdda by शेष):
	 * - Voltage booster can be used, to get full ADC perक्रमmances
	 *   (increases घातer consumption).
	 * - Vdd can be used to supply them, अगर above 2.7V (STM32MP1 only).
	 *
	 * Recommended settings क्रम ANASWVDD and EN_BOOSTER:
	 * - vdda < 2.7V but vdd > 2.7V: ANASWVDD = 1, EN_BOOSTER = 0 (sपंचांग32mp1)
	 * - vdda < 2.7V and vdd < 2.7V: ANASWVDD = 0, EN_BOOSTER = 1
	 * - vdda >= 2.7V:               ANASWVDD = 0, EN_BOOSTER = 0 (शेष)
	 */
	अगर (priv->vdda_uv < 2700000) अणु
		अगर (priv->syscfg && priv->vdd_uv > 2700000) अणु
			ret = regulator_enable(priv->vdd);
			अगर (ret < 0) अणु
				dev_err(dev, "vdd enable failed %d\n", ret);
				वापस ret;
			पूर्ण

			ret = regmap_ग_लिखो(priv->syscfg,
					   STM32MP1_SYSCFG_PMCSETR,
					   STM32MP1_SYSCFG_ANASWVDD_MASK);
			अगर (ret < 0) अणु
				regulator_disable(priv->vdd);
				dev_err(dev, "vdd select failed, %d\n", ret);
				वापस ret;
			पूर्ण
			dev_dbg(dev, "analog switches supplied by vdd\n");

			वापस 0;
		पूर्ण

		अगर (priv->booster) अणु
			/*
			 * This is optional, as this is a trade-off between
			 * analog perक्रमmance and घातer consumption.
			 */
			ret = regulator_enable(priv->booster);
			अगर (ret < 0) अणु
				dev_err(dev, "booster enable failed %d\n", ret);
				वापस ret;
			पूर्ण
			dev_dbg(dev, "analog switches supplied by booster\n");

			वापस 0;
		पूर्ण
	पूर्ण

	/* Fallback using vdda (शेष), nothing to करो */
	dev_dbg(dev, "analog switches supplied by vdda (%d uV)\n",
		priv->vdda_uv);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_adc_core_चयनes_supply_dis(काष्ठा sपंचांग32_adc_priv *priv)
अणु
	अगर (priv->vdda_uv < 2700000) अणु
		अगर (priv->syscfg && priv->vdd_uv > 2700000) अणु
			regmap_ग_लिखो(priv->syscfg, STM32MP1_SYSCFG_PMCCLRR,
				     STM32MP1_SYSCFG_ANASWVDD_MASK);
			regulator_disable(priv->vdd);
			वापस;
		पूर्ण
		अगर (priv->booster)
			regulator_disable(priv->booster);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_adc_core_hw_start(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_adc_common *common = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_adc_priv *priv = to_sपंचांग32_adc_priv(common);
	पूर्णांक ret;

	ret = regulator_enable(priv->vdda);
	अगर (ret < 0) अणु
		dev_err(dev, "vdda enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_get_voltage(priv->vdda);
	अगर (ret < 0) अणु
		dev_err(dev, "vdda get voltage failed, %d\n", ret);
		जाओ err_vdda_disable;
	पूर्ण
	priv->vdda_uv = ret;

	ret = sपंचांग32_adc_core_चयनes_supply_en(priv, dev);
	अगर (ret < 0)
		जाओ err_vdda_disable;

	ret = regulator_enable(priv->vref);
	अगर (ret < 0) अणु
		dev_err(dev, "vref enable failed\n");
		जाओ err_चयनes_dis;
	पूर्ण

	ret = clk_prepare_enable(priv->bclk);
	अगर (ret < 0) अणु
		dev_err(dev, "bus clk enable failed\n");
		जाओ err_regulator_disable;
	पूर्ण

	ret = clk_prepare_enable(priv->aclk);
	अगर (ret < 0) अणु
		dev_err(dev, "adc clk enable failed\n");
		जाओ err_bclk_disable;
	पूर्ण

	ग_लिखोl_relaxed(priv->ccr_bak, priv->common.base + priv->cfg->regs->ccr);

	वापस 0;

err_bclk_disable:
	clk_disable_unprepare(priv->bclk);
err_regulator_disable:
	regulator_disable(priv->vref);
err_चयनes_dis:
	sपंचांग32_adc_core_चयनes_supply_dis(priv);
err_vdda_disable:
	regulator_disable(priv->vdda);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_adc_core_hw_stop(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_adc_common *common = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_adc_priv *priv = to_sपंचांग32_adc_priv(common);

	/* Backup CCR that may be lost (depends on घातer state to achieve) */
	priv->ccr_bak = पढ़ोl_relaxed(priv->common.base + priv->cfg->regs->ccr);
	clk_disable_unprepare(priv->aclk);
	clk_disable_unprepare(priv->bclk);
	regulator_disable(priv->vref);
	sपंचांग32_adc_core_चयनes_supply_dis(priv);
	regulator_disable(priv->vdda);
पूर्ण

अटल पूर्णांक sपंचांग32_adc_core_चयनes_probe(काष्ठा device *dev,
					 काष्ठा sपंचांग32_adc_priv *priv)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	/* Analog चयनes supply can be controlled by syscfg (optional) */
	priv->syscfg = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(priv->syscfg)) अणु
		ret = PTR_ERR(priv->syscfg);
		अगर (ret != -ENODEV)
			वापस dev_err_probe(dev, ret, "Can't probe syscfg\n");

		priv->syscfg = शून्य;
	पूर्ण

	/* Booster can be used to supply analog चयनes (optional) */
	अगर (priv->cfg->has_syscfg & HAS_VBOOSTER &&
	    of_property_पढ़ो_bool(np, "booster-supply")) अणु
		priv->booster = devm_regulator_get_optional(dev, "booster");
		अगर (IS_ERR(priv->booster)) अणु
			ret = PTR_ERR(priv->booster);
			अगर (ret != -ENODEV)
				वापस dev_err_probe(dev, ret, "can't get booster\n");

			priv->booster = शून्य;
		पूर्ण
	पूर्ण

	/* Vdd can be used to supply analog चयनes (optional) */
	अगर (priv->cfg->has_syscfg & HAS_ANASWVDD &&
	    of_property_पढ़ो_bool(np, "vdd-supply")) अणु
		priv->vdd = devm_regulator_get_optional(dev, "vdd");
		अगर (IS_ERR(priv->vdd)) अणु
			ret = PTR_ERR(priv->vdd);
			अगर (ret != -ENODEV)
				वापस dev_err_probe(dev, ret, "can't get vdd\n");

			priv->vdd = शून्य;
		पूर्ण
	पूर्ण

	अगर (priv->vdd) अणु
		ret = regulator_enable(priv->vdd);
		अगर (ret < 0) अणु
			dev_err(dev, "vdd enable failed %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regulator_get_voltage(priv->vdd);
		अगर (ret < 0) अणु
			dev_err(dev, "vdd get voltage failed %d\n", ret);
			regulator_disable(priv->vdd);
			वापस ret;
		पूर्ण
		priv->vdd_uv = ret;

		regulator_disable(priv->vdd);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_adc_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	u32 max_rate;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, &priv->common);

	priv->cfg = (स्थिर काष्ठा sपंचांग32_adc_priv_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->common.base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->common.base))
		वापस PTR_ERR(priv->common.base);
	priv->common.phys_base = res->start;

	priv->vdda = devm_regulator_get(&pdev->dev, "vdda");
	अगर (IS_ERR(priv->vdda))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(priv->vdda),
				     "vdda get failed\n");

	priv->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(priv->vref))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(priv->vref),
				     "vref get failed\n");

	priv->aclk = devm_clk_get_optional(&pdev->dev, "adc");
	अगर (IS_ERR(priv->aclk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(priv->aclk),
				     "Can't get 'adc' clock\n");

	priv->bclk = devm_clk_get_optional(&pdev->dev, "bus");
	अगर (IS_ERR(priv->bclk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(priv->bclk),
				     "Can't get 'bus' clock\n");

	ret = sपंचांग32_adc_core_चयनes_probe(dev, priv);
	अगर (ret)
		वापस ret;

	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, STM32_ADC_CORE_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	ret = sपंचांग32_adc_core_hw_start(dev);
	अगर (ret)
		जाओ err_pm_stop;

	ret = regulator_get_voltage(priv->vref);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "vref get voltage failed, %d\n", ret);
		जाओ err_hw_stop;
	पूर्ण
	priv->common.vref_mv = ret / 1000;
	dev_dbg(&pdev->dev, "vref+=%dmV\n", priv->common.vref_mv);

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "st,max-clk-rate-hz",
				   &max_rate);
	अगर (!ret)
		priv->max_clk_rate = min(max_rate, priv->cfg->max_clk_rate_hz);
	अन्यथा
		priv->max_clk_rate = priv->cfg->max_clk_rate_hz;

	ret = priv->cfg->clk_sel(pdev, priv);
	अगर (ret < 0)
		जाओ err_hw_stop;

	ret = sपंचांग32_adc_irq_probe(pdev, priv);
	अगर (ret < 0)
		जाओ err_hw_stop;

	ret = of_platक्रमm_populate(np, शून्य, शून्य, &pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to populate DT children\n");
		जाओ err_irq_हटाओ;
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;

err_irq_हटाओ:
	sपंचांग32_adc_irq_हटाओ(pdev, priv);
err_hw_stop:
	sपंचांग32_adc_core_hw_stop(dev);
err_pm_stop:
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_adc_common *common = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_adc_priv *priv = to_sपंचांग32_adc_priv(common);

	pm_runसमय_get_sync(&pdev->dev);
	of_platक्रमm_depopulate(&pdev->dev);
	sपंचांग32_adc_irq_हटाओ(pdev, priv);
	sपंचांग32_adc_core_hw_stop(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_PM)
अटल पूर्णांक sपंचांग32_adc_core_runसमय_suspend(काष्ठा device *dev)
अणु
	sपंचांग32_adc_core_hw_stop(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_adc_core_runसमय_resume(काष्ठा device *dev)
अणु
	वापस sपंचांग32_adc_core_hw_start(dev);
पूर्ण

अटल पूर्णांक sपंचांग32_adc_core_runसमय_idle(काष्ठा device *dev)
अणु
	pm_runसमय_mark_last_busy(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_adc_core_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_adc_core_runसमय_suspend,
			   sपंचांग32_adc_core_runसमय_resume,
			   sपंचांग32_adc_core_runसमय_idle)
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_priv_cfg sपंचांग32f4_adc_priv_cfg = अणु
	.regs = &sपंचांग32f4_adc_common_regs,
	.clk_sel = sपंचांग32f4_adc_clk_sel,
	.max_clk_rate_hz = 36000000,
	.num_irqs = 1,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_priv_cfg sपंचांग32h7_adc_priv_cfg = अणु
	.regs = &sपंचांग32h7_adc_common_regs,
	.clk_sel = sपंचांग32h7_adc_clk_sel,
	.max_clk_rate_hz = 36000000,
	.has_syscfg = HAS_VBOOSTER,
	.num_irqs = 1,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_adc_priv_cfg sपंचांग32mp1_adc_priv_cfg = अणु
	.regs = &sपंचांग32h7_adc_common_regs,
	.clk_sel = sपंचांग32h7_adc_clk_sel,
	.max_clk_rate_hz = 40000000,
	.has_syscfg = HAS_VBOOSTER | HAS_ANASWVDD,
	.num_irqs = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_adc_of_match[] = अणु
	अणु
		.compatible = "st,stm32f4-adc-core",
		.data = (व्योम *)&sपंचांग32f4_adc_priv_cfg
	पूर्ण, अणु
		.compatible = "st,stm32h7-adc-core",
		.data = (व्योम *)&sपंचांग32h7_adc_priv_cfg
	पूर्ण, अणु
		.compatible = "st,stm32mp1-adc-core",
		.data = (व्योम *)&sपंचांग32mp1_adc_priv_cfg
	पूर्ण, अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_adc_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_adc_driver = अणु
	.probe = sपंचांग32_adc_probe,
	.हटाओ = sपंचांग32_adc_हटाओ,
	.driver = अणु
		.name = "stm32-adc-core",
		.of_match_table = sपंचांग32_adc_of_match,
		.pm = &sपंचांग32_adc_core_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_adc_driver);

MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 ADC core driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:stm32-adc-core");
