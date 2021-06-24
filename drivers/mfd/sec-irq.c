<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2011-2014 Samsung Electronics Co., Ltd
//              http://www.samsung.com

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/samsung/core.h>
#समावेश <linux/mfd/samsung/irq.h>
#समावेश <linux/mfd/samsung/s2mps11.h>
#समावेश <linux/mfd/samsung/s2mps14.h>
#समावेश <linux/mfd/samsung/s2mpu02.h>
#समावेश <linux/mfd/samsung/s5m8763.h>
#समावेश <linux/mfd/samsung/s5m8767.h>

अटल स्थिर काष्ठा regmap_irq s2mps11_irqs[] = अणु
	[S2MPS11_IRQ_PWRONF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRONF_MASK,
	पूर्ण,
	[S2MPS11_IRQ_PWRONR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRONR_MASK,
	पूर्ण,
	[S2MPS11_IRQ_JIGONBF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_JIGONBF_MASK,
	पूर्ण,
	[S2MPS11_IRQ_JIGONBR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_JIGONBR_MASK,
	पूर्ण,
	[S2MPS11_IRQ_ACOKBF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_ACOKBF_MASK,
	पूर्ण,
	[S2MPS11_IRQ_ACOKBR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_ACOKBR_MASK,
	पूर्ण,
	[S2MPS11_IRQ_PWRON1S] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRON1S_MASK,
	पूर्ण,
	[S2MPS11_IRQ_MRB] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_MRB_MASK,
	पूर्ण,
	[S2MPS11_IRQ_RTC60S] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTC60S_MASK,
	पूर्ण,
	[S2MPS11_IRQ_RTCA1] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTCA1_MASK,
	पूर्ण,
	[S2MPS11_IRQ_RTCA0] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTCA0_MASK,
	पूर्ण,
	[S2MPS11_IRQ_SMPL] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_SMPL_MASK,
	पूर्ण,
	[S2MPS11_IRQ_RTC1S] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTC1S_MASK,
	पूर्ण,
	[S2MPS11_IRQ_WTSR] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_WTSR_MASK,
	पूर्ण,
	[S2MPS11_IRQ_INT120C] = अणु
		.reg_offset = 2,
		.mask = S2MPS11_IRQ_INT120C_MASK,
	पूर्ण,
	[S2MPS11_IRQ_INT140C] = अणु
		.reg_offset = 2,
		.mask = S2MPS11_IRQ_INT140C_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq s2mps14_irqs[] = अणु
	[S2MPS14_IRQ_PWRONF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRONF_MASK,
	पूर्ण,
	[S2MPS14_IRQ_PWRONR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRONR_MASK,
	पूर्ण,
	[S2MPS14_IRQ_JIGONBF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_JIGONBF_MASK,
	पूर्ण,
	[S2MPS14_IRQ_JIGONBR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_JIGONBR_MASK,
	पूर्ण,
	[S2MPS14_IRQ_ACOKBF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_ACOKBF_MASK,
	पूर्ण,
	[S2MPS14_IRQ_ACOKBR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_ACOKBR_MASK,
	पूर्ण,
	[S2MPS14_IRQ_PWRON1S] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRON1S_MASK,
	पूर्ण,
	[S2MPS14_IRQ_MRB] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_MRB_MASK,
	पूर्ण,
	[S2MPS14_IRQ_RTC60S] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTC60S_MASK,
	पूर्ण,
	[S2MPS14_IRQ_RTCA1] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTCA1_MASK,
	पूर्ण,
	[S2MPS14_IRQ_RTCA0] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTCA0_MASK,
	पूर्ण,
	[S2MPS14_IRQ_SMPL] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_SMPL_MASK,
	पूर्ण,
	[S2MPS14_IRQ_RTC1S] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTC1S_MASK,
	पूर्ण,
	[S2MPS14_IRQ_WTSR] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_WTSR_MASK,
	पूर्ण,
	[S2MPS14_IRQ_INT120C] = अणु
		.reg_offset = 2,
		.mask = S2MPS11_IRQ_INT120C_MASK,
	पूर्ण,
	[S2MPS14_IRQ_INT140C] = अणु
		.reg_offset = 2,
		.mask = S2MPS11_IRQ_INT140C_MASK,
	पूर्ण,
	[S2MPS14_IRQ_TSD] = अणु
		.reg_offset = 2,
		.mask = S2MPS14_IRQ_TSD_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq s2mpu02_irqs[] = अणु
	[S2MPU02_IRQ_PWRONF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRONF_MASK,
	पूर्ण,
	[S2MPU02_IRQ_PWRONR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRONR_MASK,
	पूर्ण,
	[S2MPU02_IRQ_JIGONBF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_JIGONBF_MASK,
	पूर्ण,
	[S2MPU02_IRQ_JIGONBR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_JIGONBR_MASK,
	पूर्ण,
	[S2MPU02_IRQ_ACOKBF] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_ACOKBF_MASK,
	पूर्ण,
	[S2MPU02_IRQ_ACOKBR] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_ACOKBR_MASK,
	पूर्ण,
	[S2MPU02_IRQ_PWRON1S] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_PWRON1S_MASK,
	पूर्ण,
	[S2MPU02_IRQ_MRB] = अणु
		.reg_offset = 0,
		.mask = S2MPS11_IRQ_MRB_MASK,
	पूर्ण,
	[S2MPU02_IRQ_RTC60S] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTC60S_MASK,
	पूर्ण,
	[S2MPU02_IRQ_RTCA1] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTCA1_MASK,
	पूर्ण,
	[S2MPU02_IRQ_RTCA0] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTCA0_MASK,
	पूर्ण,
	[S2MPU02_IRQ_SMPL] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_SMPL_MASK,
	पूर्ण,
	[S2MPU02_IRQ_RTC1S] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_RTC1S_MASK,
	पूर्ण,
	[S2MPU02_IRQ_WTSR] = अणु
		.reg_offset = 1,
		.mask = S2MPS11_IRQ_WTSR_MASK,
	पूर्ण,
	[S2MPU02_IRQ_INT120C] = अणु
		.reg_offset = 2,
		.mask = S2MPS11_IRQ_INT120C_MASK,
	पूर्ण,
	[S2MPU02_IRQ_INT140C] = अणु
		.reg_offset = 2,
		.mask = S2MPS11_IRQ_INT140C_MASK,
	पूर्ण,
	[S2MPU02_IRQ_TSD] = अणु
		.reg_offset = 2,
		.mask = S2MPS14_IRQ_TSD_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq s5m8767_irqs[] = अणु
	[S5M8767_IRQ_PWRR] = अणु
		.reg_offset = 0,
		.mask = S5M8767_IRQ_PWRR_MASK,
	पूर्ण,
	[S5M8767_IRQ_PWRF] = अणु
		.reg_offset = 0,
		.mask = S5M8767_IRQ_PWRF_MASK,
	पूर्ण,
	[S5M8767_IRQ_PWR1S] = अणु
		.reg_offset = 0,
		.mask = S5M8767_IRQ_PWR1S_MASK,
	पूर्ण,
	[S5M8767_IRQ_JIGR] = अणु
		.reg_offset = 0,
		.mask = S5M8767_IRQ_JIGR_MASK,
	पूर्ण,
	[S5M8767_IRQ_JIGF] = अणु
		.reg_offset = 0,
		.mask = S5M8767_IRQ_JIGF_MASK,
	पूर्ण,
	[S5M8767_IRQ_LOWBAT2] = अणु
		.reg_offset = 0,
		.mask = S5M8767_IRQ_LOWBAT2_MASK,
	पूर्ण,
	[S5M8767_IRQ_LOWBAT1] = अणु
		.reg_offset = 0,
		.mask = S5M8767_IRQ_LOWBAT1_MASK,
	पूर्ण,
	[S5M8767_IRQ_MRB] = अणु
		.reg_offset = 1,
		.mask = S5M8767_IRQ_MRB_MASK,
	पूर्ण,
	[S5M8767_IRQ_DVSOK2] = अणु
		.reg_offset = 1,
		.mask = S5M8767_IRQ_DVSOK2_MASK,
	पूर्ण,
	[S5M8767_IRQ_DVSOK3] = अणु
		.reg_offset = 1,
		.mask = S5M8767_IRQ_DVSOK3_MASK,
	पूर्ण,
	[S5M8767_IRQ_DVSOK4] = अणु
		.reg_offset = 1,
		.mask = S5M8767_IRQ_DVSOK4_MASK,
	पूर्ण,
	[S5M8767_IRQ_RTC60S] = अणु
		.reg_offset = 2,
		.mask = S5M8767_IRQ_RTC60S_MASK,
	पूर्ण,
	[S5M8767_IRQ_RTCA1] = अणु
		.reg_offset = 2,
		.mask = S5M8767_IRQ_RTCA1_MASK,
	पूर्ण,
	[S5M8767_IRQ_RTCA2] = अणु
		.reg_offset = 2,
		.mask = S5M8767_IRQ_RTCA2_MASK,
	पूर्ण,
	[S5M8767_IRQ_SMPL] = अणु
		.reg_offset = 2,
		.mask = S5M8767_IRQ_SMPL_MASK,
	पूर्ण,
	[S5M8767_IRQ_RTC1S] = अणु
		.reg_offset = 2,
		.mask = S5M8767_IRQ_RTC1S_MASK,
	पूर्ण,
	[S5M8767_IRQ_WTSR] = अणु
		.reg_offset = 2,
		.mask = S5M8767_IRQ_WTSR_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq s5m8763_irqs[] = अणु
	[S5M8763_IRQ_DCINF] = अणु
		.reg_offset = 0,
		.mask = S5M8763_IRQ_DCINF_MASK,
	पूर्ण,
	[S5M8763_IRQ_DCINR] = अणु
		.reg_offset = 0,
		.mask = S5M8763_IRQ_DCINR_MASK,
	पूर्ण,
	[S5M8763_IRQ_JIGF] = अणु
		.reg_offset = 0,
		.mask = S5M8763_IRQ_JIGF_MASK,
	पूर्ण,
	[S5M8763_IRQ_JIGR] = अणु
		.reg_offset = 0,
		.mask = S5M8763_IRQ_JIGR_MASK,
	पूर्ण,
	[S5M8763_IRQ_PWRONF] = अणु
		.reg_offset = 0,
		.mask = S5M8763_IRQ_PWRONF_MASK,
	पूर्ण,
	[S5M8763_IRQ_PWRONR] = अणु
		.reg_offset = 0,
		.mask = S5M8763_IRQ_PWRONR_MASK,
	पूर्ण,
	[S5M8763_IRQ_WTSREVNT] = अणु
		.reg_offset = 1,
		.mask = S5M8763_IRQ_WTSREVNT_MASK,
	पूर्ण,
	[S5M8763_IRQ_SMPLEVNT] = अणु
		.reg_offset = 1,
		.mask = S5M8763_IRQ_SMPLEVNT_MASK,
	पूर्ण,
	[S5M8763_IRQ_ALARM1] = अणु
		.reg_offset = 1,
		.mask = S5M8763_IRQ_ALARM1_MASK,
	पूर्ण,
	[S5M8763_IRQ_ALARM0] = अणु
		.reg_offset = 1,
		.mask = S5M8763_IRQ_ALARM0_MASK,
	पूर्ण,
	[S5M8763_IRQ_ONKEY1S] = अणु
		.reg_offset = 2,
		.mask = S5M8763_IRQ_ONKEY1S_MASK,
	पूर्ण,
	[S5M8763_IRQ_TOPOFFR] = अणु
		.reg_offset = 2,
		.mask = S5M8763_IRQ_TOPOFFR_MASK,
	पूर्ण,
	[S5M8763_IRQ_DCINOVPR] = अणु
		.reg_offset = 2,
		.mask = S5M8763_IRQ_DCINOVPR_MASK,
	पूर्ण,
	[S5M8763_IRQ_CHGRSTF] = अणु
		.reg_offset = 2,
		.mask = S5M8763_IRQ_CHGRSTF_MASK,
	पूर्ण,
	[S5M8763_IRQ_DONER] = अणु
		.reg_offset = 2,
		.mask = S5M8763_IRQ_DONER_MASK,
	पूर्ण,
	[S5M8763_IRQ_CHGFAULT] = अणु
		.reg_offset = 2,
		.mask = S5M8763_IRQ_CHGFAULT_MASK,
	पूर्ण,
	[S5M8763_IRQ_LOBAT1] = अणु
		.reg_offset = 3,
		.mask = S5M8763_IRQ_LOBAT1_MASK,
	पूर्ण,
	[S5M8763_IRQ_LOBAT2] = अणु
		.reg_offset = 3,
		.mask = S5M8763_IRQ_LOBAT2_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip s2mps11_irq_chip = अणु
	.name = "s2mps11",
	.irqs = s2mps11_irqs,
	.num_irqs = ARRAY_SIZE(s2mps11_irqs),
	.num_regs = 3,
	.status_base = S2MPS11_REG_INT1,
	.mask_base = S2MPS11_REG_INT1M,
	.ack_base = S2MPS11_REG_INT1,
पूर्ण;

#घोषणा S2MPS1X_IRQ_CHIP_COMMON_DATA		\
	.irqs = s2mps14_irqs,			\
	.num_irqs = ARRAY_SIZE(s2mps14_irqs),	\
	.num_regs = 3,				\
	.status_base = S2MPS14_REG_INT1,	\
	.mask_base = S2MPS14_REG_INT1M,		\
	.ack_base = S2MPS14_REG_INT1		\

अटल स्थिर काष्ठा regmap_irq_chip s2mps13_irq_chip = अणु
	.name = "s2mps13",
	S2MPS1X_IRQ_CHIP_COMMON_DATA,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip s2mps14_irq_chip = अणु
	.name = "s2mps14",
	S2MPS1X_IRQ_CHIP_COMMON_DATA,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip s2mps15_irq_chip = अणु
	.name = "s2mps15",
	S2MPS1X_IRQ_CHIP_COMMON_DATA,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip s2mpu02_irq_chip = अणु
	.name = "s2mpu02",
	.irqs = s2mpu02_irqs,
	.num_irqs = ARRAY_SIZE(s2mpu02_irqs),
	.num_regs = 3,
	.status_base = S2MPU02_REG_INT1,
	.mask_base = S2MPU02_REG_INT1M,
	.ack_base = S2MPU02_REG_INT1,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip s5m8767_irq_chip = अणु
	.name = "s5m8767",
	.irqs = s5m8767_irqs,
	.num_irqs = ARRAY_SIZE(s5m8767_irqs),
	.num_regs = 3,
	.status_base = S5M8767_REG_INT1,
	.mask_base = S5M8767_REG_INT1M,
	.ack_base = S5M8767_REG_INT1,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip s5m8763_irq_chip = अणु
	.name = "s5m8763",
	.irqs = s5m8763_irqs,
	.num_irqs = ARRAY_SIZE(s5m8763_irqs),
	.num_regs = 4,
	.status_base = S5M8763_REG_IRQ1,
	.mask_base = S5M8763_REG_IRQM1,
	.ack_base = S5M8763_REG_IRQ1,
पूर्ण;

पूर्णांक sec_irq_init(काष्ठा sec_pmic_dev *sec_pmic)
अणु
	पूर्णांक ret = 0;
	पूर्णांक type = sec_pmic->device_type;
	स्थिर काष्ठा regmap_irq_chip *sec_irq_chip;

	अगर (!sec_pmic->irq) अणु
		dev_warn(sec_pmic->dev,
			 "No interrupt specified, no interrupts\n");
		sec_pmic->irq_base = 0;
		वापस 0;
	पूर्ण

	चयन (type) अणु
	हाल S5M8763X:
		sec_irq_chip = &s5m8763_irq_chip;
		अवरोध;
	हाल S5M8767X:
		sec_irq_chip = &s5m8767_irq_chip;
		अवरोध;
	हाल S2MPA01:
		sec_irq_chip = &s2mps14_irq_chip;
		अवरोध;
	हाल S2MPS11X:
		sec_irq_chip = &s2mps11_irq_chip;
		अवरोध;
	हाल S2MPS13X:
		sec_irq_chip = &s2mps13_irq_chip;
		अवरोध;
	हाल S2MPS14X:
		sec_irq_chip = &s2mps14_irq_chip;
		अवरोध;
	हाल S2MPS15X:
		sec_irq_chip = &s2mps15_irq_chip;
		अवरोध;
	हाल S2MPU02:
		sec_irq_chip = &s2mpu02_irq_chip;
		अवरोध;
	शेष:
		dev_err(sec_pmic->dev, "Unknown device type %lu\n",
			sec_pmic->device_type);
		वापस -EINVAL;
	पूर्ण

	ret = devm_regmap_add_irq_chip(sec_pmic->dev, sec_pmic->regmap_pmic,
				       sec_pmic->irq,
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				       sec_pmic->irq_base, sec_irq_chip,
				       &sec_pmic->irq_data);
	अगर (ret != 0) अणु
		dev_err(sec_pmic->dev, "Failed to register IRQ chip: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * The rtc-s5m driver requests S2MPS14_IRQ_RTCA0 also क्रम S2MPS11
	 * so the पूर्णांकerrupt number must be consistent.
	 */
	BUILD_BUG_ON(((क्रमागत s2mps14_irq)S2MPS11_IRQ_RTCA0) != S2MPS14_IRQ_RTCA0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sec_irq_init);

MODULE_AUTHOR("Sangbeom Kim <sbkim73@samsung.com>");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_DESCRIPTION("Interrupt support for the S5M MFD");
MODULE_LICENSE("GPL");
