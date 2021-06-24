<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DesignWare PWM Controller driver
 *
 * Copyright (C) 2018-2020 Intel Corporation
 *
 * Author: Felipe Balbi (Intel)
 * Author: Jarkko Nikula <jarkko.nikula@linux.पूर्णांकel.com>
 * Author: Raymond Tan <raymond.tan@पूर्णांकel.com>
 *
 * Limitations:
 * - The hardware cannot generate a 0 % or 100 % duty cycle. Both high and low
 *   periods are one or more input घड़ी periods दीर्घ.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pwm.h>

#घोषणा DWC_TIM_LD_CNT(n)	((n) * 0x14)
#घोषणा DWC_TIM_LD_CNT2(n)	(((n) * 4) + 0xb0)
#घोषणा DWC_TIM_CUR_VAL(n)	(((n) * 0x14) + 0x04)
#घोषणा DWC_TIM_CTRL(n)		(((n) * 0x14) + 0x08)
#घोषणा DWC_TIM_EOI(n)		(((n) * 0x14) + 0x0c)
#घोषणा DWC_TIM_INT_STS(n)	(((n) * 0x14) + 0x10)

#घोषणा DWC_TIMERS_INT_STS	0xa0
#घोषणा DWC_TIMERS_EOI		0xa4
#घोषणा DWC_TIMERS_RAW_INT_STS	0xa8
#घोषणा DWC_TIMERS_COMP_VERSION	0xac

#घोषणा DWC_TIMERS_TOTAL	8
#घोषणा DWC_CLK_PERIOD_NS	10

/* Timer Control Register */
#घोषणा DWC_TIM_CTRL_EN		BIT(0)
#घोषणा DWC_TIM_CTRL_MODE	BIT(1)
#घोषणा DWC_TIM_CTRL_MODE_FREE	(0 << 1)
#घोषणा DWC_TIM_CTRL_MODE_USER	(1 << 1)
#घोषणा DWC_TIM_CTRL_INT_MASK	BIT(2)
#घोषणा DWC_TIM_CTRL_PWM	BIT(3)

काष्ठा dwc_pwm_ctx अणु
	u32 cnt;
	u32 cnt2;
	u32 ctrl;
पूर्ण;

काष्ठा dwc_pwm अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *base;
	काष्ठा dwc_pwm_ctx ctx[DWC_TIMERS_TOTAL];
पूर्ण;
#घोषणा to_dwc_pwm(p)	(container_of((p), काष्ठा dwc_pwm, chip))

अटल अंतरभूत u32 dwc_pwm_पढ़ोl(काष्ठा dwc_pwm *dwc, u32 offset)
अणु
	वापस पढ़ोl(dwc->base + offset);
पूर्ण

अटल अंतरभूत व्योम dwc_pwm_ग_लिखोl(काष्ठा dwc_pwm *dwc, u32 value, u32 offset)
अणु
	ग_लिखोl(value, dwc->base + offset);
पूर्ण

अटल व्योम __dwc_pwm_set_enable(काष्ठा dwc_pwm *dwc, पूर्णांक pwm, पूर्णांक enabled)
अणु
	u32 reg;

	reg = dwc_pwm_पढ़ोl(dwc, DWC_TIM_CTRL(pwm));

	अगर (enabled)
		reg |= DWC_TIM_CTRL_EN;
	अन्यथा
		reg &= ~DWC_TIM_CTRL_EN;

	dwc_pwm_ग_लिखोl(dwc, reg, DWC_TIM_CTRL(pwm));
पूर्ण

अटल पूर्णांक __dwc_pwm_configure_समयr(काष्ठा dwc_pwm *dwc,
				     काष्ठा pwm_device *pwm,
				     स्थिर काष्ठा pwm_state *state)
अणु
	u64 पंचांगp;
	u32 ctrl;
	u32 high;
	u32 low;

	/*
	 * Calculate width of low and high period in terms of input घड़ी
	 * periods and check are the result within HW limits between 1 and
	 * 2^32 periods.
	 */
	पंचांगp = DIV_ROUND_CLOSEST_ULL(state->duty_cycle, DWC_CLK_PERIOD_NS);
	अगर (पंचांगp < 1 || पंचांगp > (1ULL << 32))
		वापस -दुस्फल;
	low = पंचांगp - 1;

	पंचांगp = DIV_ROUND_CLOSEST_ULL(state->period - state->duty_cycle,
				    DWC_CLK_PERIOD_NS);
	अगर (पंचांगp < 1 || पंचांगp > (1ULL << 32))
		वापस -दुस्फल;
	high = पंचांगp - 1;

	/*
	 * Specअगरication says समयr usage flow is to disable समयr, then
	 * program it followed by enable. It also says Load Count is loaded
	 * पूर्णांकo समयr after it is enabled - either after a disable or
	 * a reset. Based on measurements it happens also without disable
	 * whenever Load Count is updated. But follow the specअगरication.
	 */
	__dwc_pwm_set_enable(dwc, pwm->hwpwm, false);

	/*
	 * Write Load Count and Load Count 2 रेजिस्टरs. Former defines the
	 * width of low period and latter the width of high period in terms
	 * multiple of input घड़ी periods:
	 * Width = ((Count + 1) * input घड़ी period).
	 */
	dwc_pwm_ग_लिखोl(dwc, low, DWC_TIM_LD_CNT(pwm->hwpwm));
	dwc_pwm_ग_लिखोl(dwc, high, DWC_TIM_LD_CNT2(pwm->hwpwm));

	/*
	 * Set user-defined mode, समयr reloads from Load Count रेजिस्टरs
	 * when it counts करोwn to 0.
	 * Set PWM mode, it makes output to toggle and width of low and high
	 * periods are set by Load Count रेजिस्टरs.
	 */
	ctrl = DWC_TIM_CTRL_MODE_USER | DWC_TIM_CTRL_PWM;
	dwc_pwm_ग_लिखोl(dwc, ctrl, DWC_TIM_CTRL(pwm->hwpwm));

	/*
	 * Enable समयr. Output starts from low period.
	 */
	__dwc_pwm_set_enable(dwc, pwm->hwpwm, state->enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			 स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा dwc_pwm *dwc = to_dwc_pwm(chip);

	अगर (state->polarity != PWM_POLARITY_INVERSED)
		वापस -EINVAL;

	अगर (state->enabled) अणु
		अगर (!pwm->state.enabled)
			pm_runसमय_get_sync(chip->dev);
		वापस __dwc_pwm_configure_समयr(dwc, pwm, state);
	पूर्ण अन्यथा अणु
		अगर (pwm->state.enabled) अणु
			__dwc_pwm_set_enable(dwc, pwm->hwpwm, false);
			pm_runसमय_put_sync(chip->dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dwc_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      काष्ठा pwm_state *state)
अणु
	काष्ठा dwc_pwm *dwc = to_dwc_pwm(chip);
	u64 duty, period;

	pm_runसमय_get_sync(chip->dev);

	state->enabled = !!(dwc_pwm_पढ़ोl(dwc,
				DWC_TIM_CTRL(pwm->hwpwm)) & DWC_TIM_CTRL_EN);

	duty = dwc_pwm_पढ़ोl(dwc, DWC_TIM_LD_CNT(pwm->hwpwm));
	duty += 1;
	duty *= DWC_CLK_PERIOD_NS;
	state->duty_cycle = duty;

	period = dwc_pwm_पढ़ोl(dwc, DWC_TIM_LD_CNT2(pwm->hwpwm));
	period += 1;
	period *= DWC_CLK_PERIOD_NS;
	period += duty;
	state->period = period;

	state->polarity = PWM_POLARITY_INVERSED;

	pm_runसमय_put_sync(chip->dev);
पूर्ण

अटल स्थिर काष्ठा pwm_ops dwc_pwm_ops = अणु
	.apply = dwc_pwm_apply,
	.get_state = dwc_pwm_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक dwc_pwm_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pci->dev;
	काष्ठा dwc_pwm *dwc;
	पूर्णांक ret;

	dwc = devm_kzalloc(&pci->dev, माप(*dwc), GFP_KERNEL);
	अगर (!dwc)
		वापस -ENOMEM;

	ret = pcim_enable_device(pci);
	अगर (ret) अणु
		dev_err(&pci->dev,
			"Failed to enable device (%pe)\n", ERR_PTR(ret));
		वापस ret;
	पूर्ण

	pci_set_master(pci);

	ret = pcim_iomap_regions(pci, BIT(0), pci_name(pci));
	अगर (ret) अणु
		dev_err(&pci->dev,
			"Failed to iomap PCI BAR (%pe)\n", ERR_PTR(ret));
		वापस ret;
	पूर्ण

	dwc->base = pcim_iomap_table(pci)[0];
	अगर (!dwc->base) अणु
		dev_err(&pci->dev, "Base address missing\n");
		वापस -ENOMEM;
	पूर्ण

	pci_set_drvdata(pci, dwc);

	dwc->chip.dev = dev;
	dwc->chip.ops = &dwc_pwm_ops;
	dwc->chip.npwm = DWC_TIMERS_TOTAL;

	ret = pwmchip_add(&dwc->chip);
	अगर (ret)
		वापस ret;

	pm_runसमय_put(dev);
	pm_runसमय_allow(dev);

	वापस 0;
पूर्ण

अटल व्योम dwc_pwm_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा dwc_pwm *dwc = pci_get_drvdata(pci);

	pm_runसमय_क्रमbid(&pci->dev);
	pm_runसमय_get_noresume(&pci->dev);

	pwmchip_हटाओ(&dwc->chip);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwc_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = container_of(dev, काष्ठा pci_dev, dev);
	काष्ठा dwc_pwm *dwc = pci_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < DWC_TIMERS_TOTAL; i++) अणु
		अगर (dwc->chip.pwms[i].state.enabled) अणु
			dev_err(dev, "PWM %u in use by consumer (%s)\n",
				i, dwc->chip.pwms[i].label);
			वापस -EBUSY;
		पूर्ण
		dwc->ctx[i].cnt = dwc_pwm_पढ़ोl(dwc, DWC_TIM_LD_CNT(i));
		dwc->ctx[i].cnt2 = dwc_pwm_पढ़ोl(dwc, DWC_TIM_LD_CNT2(i));
		dwc->ctx[i].ctrl = dwc_pwm_पढ़ोl(dwc, DWC_TIM_CTRL(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dwc_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = container_of(dev, काष्ठा pci_dev, dev);
	काष्ठा dwc_pwm *dwc = pci_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < DWC_TIMERS_TOTAL; i++) अणु
		dwc_pwm_ग_लिखोl(dwc, dwc->ctx[i].cnt, DWC_TIM_LD_CNT(i));
		dwc_pwm_ग_लिखोl(dwc, dwc->ctx[i].cnt2, DWC_TIM_LD_CNT2(i));
		dwc_pwm_ग_लिखोl(dwc, dwc->ctx[i].ctrl, DWC_TIM_CTRL(i));
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(dwc_pwm_pm_ops, dwc_pwm_suspend, dwc_pwm_resume);

अटल स्थिर काष्ठा pci_device_id dwc_pwm_id_table[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x4bb7) पूर्ण, /* Elkhart Lake */
	अणु  पूर्ण	/* Terminating Entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, dwc_pwm_id_table);

अटल काष्ठा pci_driver dwc_pwm_driver = अणु
	.name = "pwm-dwc",
	.probe = dwc_pwm_probe,
	.हटाओ = dwc_pwm_हटाओ,
	.id_table = dwc_pwm_id_table,
	.driver = अणु
		.pm = &dwc_pwm_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(dwc_pwm_driver);

MODULE_AUTHOR("Felipe Balbi (Intel)");
MODULE_AUTHOR("Jarkko Nikula <jarkko.nikula@linux.intel.com>");
MODULE_AUTHOR("Raymond Tan <raymond.tan@intel.com>");
MODULE_DESCRIPTION("DesignWare PWM Controller");
MODULE_LICENSE("GPL");
