<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8350-irq.c  --  IRQ support क्रम Wolfson WM8350
 *
 * Copyright 2007, 2008, 2009 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood, Mark Brown
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/bug.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <linux/mfd/wm8350/core.h>
#समावेश <linux/mfd/wm8350/audपन.स>
#समावेश <linux/mfd/wm8350/comparator.h>
#समावेश <linux/mfd/wm8350/gpपन.स>
#समावेश <linux/mfd/wm8350/pmic.h>
#समावेश <linux/mfd/wm8350/rtc.h>
#समावेश <linux/mfd/wm8350/supply.h>
#समावेश <linux/mfd/wm8350/wdt.h>

#घोषणा WM8350_INT_OFFSET_1                     0
#घोषणा WM8350_INT_OFFSET_2                     1
#घोषणा WM8350_POWER_UP_INT_OFFSET              2
#घोषणा WM8350_UNDER_VOLTAGE_INT_OFFSET         3
#घोषणा WM8350_OVER_CURRENT_INT_OFFSET          4
#घोषणा WM8350_GPIO_INT_OFFSET                  5
#घोषणा WM8350_COMPARATOR_INT_OFFSET            6

काष्ठा wm8350_irq_data अणु
	पूर्णांक primary;
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक primary_only;
पूर्ण;

अटल काष्ठा wm8350_irq_data wm8350_irqs[] = अणु
	[WM8350_IRQ_OC_LS] = अणु
		.primary = WM8350_OC_INT,
		.reg = WM8350_OVER_CURRENT_INT_OFFSET,
		.mask = WM8350_OC_LS_EINT,
		.primary_only = 1,
	पूर्ण,
	[WM8350_IRQ_UV_DC1] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_DC1_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_DC2] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_DC2_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_DC3] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_DC3_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_DC4] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_DC4_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_DC5] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_DC5_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_DC6] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_DC6_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_LDO1] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_LDO1_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_LDO2] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_LDO2_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_LDO3] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_LDO3_EINT,
	पूर्ण,
	[WM8350_IRQ_UV_LDO4] = अणु
		.primary = WM8350_UV_INT,
		.reg = WM8350_UNDER_VOLTAGE_INT_OFFSET,
		.mask = WM8350_UV_LDO4_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_BAT_HOT] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_BAT_HOT_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_BAT_COLD] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_BAT_COLD_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_BAT_FAIL] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_BAT_FAIL_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_TO] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_TO_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_END] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_END_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_START] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_START_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_FAST_RDY] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_FAST_RDY_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_VBATT_LT_3P9] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_VBATT_LT_3P9_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_VBATT_LT_3P1] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_VBATT_LT_3P1_EINT,
	पूर्ण,
	[WM8350_IRQ_CHG_VBATT_LT_2P85] = अणु
		.primary = WM8350_CHG_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_CHG_VBATT_LT_2P85_EINT,
	पूर्ण,
	[WM8350_IRQ_RTC_ALM] = अणु
		.primary = WM8350_RTC_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_RTC_ALM_EINT,
	पूर्ण,
	[WM8350_IRQ_RTC_SEC] = अणु
		.primary = WM8350_RTC_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_RTC_SEC_EINT,
	पूर्ण,
	[WM8350_IRQ_RTC_PER] = अणु
		.primary = WM8350_RTC_INT,
		.reg = WM8350_INT_OFFSET_1,
		.mask = WM8350_RTC_PER_EINT,
	पूर्ण,
	[WM8350_IRQ_CS1] = अणु
		.primary = WM8350_CS_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_CS1_EINT,
	पूर्ण,
	[WM8350_IRQ_CS2] = अणु
		.primary = WM8350_CS_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_CS2_EINT,
	पूर्ण,
	[WM8350_IRQ_SYS_HYST_COMP_FAIL] = अणु
		.primary = WM8350_SYS_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_SYS_HYST_COMP_FAIL_EINT,
	पूर्ण,
	[WM8350_IRQ_SYS_CHIP_GT115] = अणु
		.primary = WM8350_SYS_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_SYS_CHIP_GT115_EINT,
	पूर्ण,
	[WM8350_IRQ_SYS_CHIP_GT140] = अणु
		.primary = WM8350_SYS_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_SYS_CHIP_GT140_EINT,
	पूर्ण,
	[WM8350_IRQ_SYS_WDOG_TO] = अणु
		.primary = WM8350_SYS_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_SYS_WDOG_TO_EINT,
	पूर्ण,
	[WM8350_IRQ_AUXADC_DATARDY] = अणु
		.primary = WM8350_AUXADC_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_AUXADC_DATARDY_EINT,
	पूर्ण,
	[WM8350_IRQ_AUXADC_DCOMP4] = अणु
		.primary = WM8350_AUXADC_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_AUXADC_DCOMP4_EINT,
	पूर्ण,
	[WM8350_IRQ_AUXADC_DCOMP3] = अणु
		.primary = WM8350_AUXADC_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_AUXADC_DCOMP3_EINT,
	पूर्ण,
	[WM8350_IRQ_AUXADC_DCOMP2] = अणु
		.primary = WM8350_AUXADC_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_AUXADC_DCOMP2_EINT,
	पूर्ण,
	[WM8350_IRQ_AUXADC_DCOMP1] = अणु
		.primary = WM8350_AUXADC_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_AUXADC_DCOMP1_EINT,
	पूर्ण,
	[WM8350_IRQ_USB_LIMIT] = अणु
		.primary = WM8350_USB_INT,
		.reg = WM8350_INT_OFFSET_2,
		.mask = WM8350_USB_LIMIT_EINT,
		.primary_only = 1,
	पूर्ण,
	[WM8350_IRQ_WKUP_OFF_STATE] = अणु
		.primary = WM8350_WKUP_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_WKUP_OFF_STATE_EINT,
	पूर्ण,
	[WM8350_IRQ_WKUP_HIB_STATE] = अणु
		.primary = WM8350_WKUP_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_WKUP_HIB_STATE_EINT,
	पूर्ण,
	[WM8350_IRQ_WKUP_CONV_FAULT] = अणु
		.primary = WM8350_WKUP_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_WKUP_CONV_FAULT_EINT,
	पूर्ण,
	[WM8350_IRQ_WKUP_WDOG_RST] = अणु
		.primary = WM8350_WKUP_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_WKUP_WDOG_RST_EINT,
	पूर्ण,
	[WM8350_IRQ_WKUP_GP_PWR_ON] = अणु
		.primary = WM8350_WKUP_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_WKUP_GP_PWR_ON_EINT,
	पूर्ण,
	[WM8350_IRQ_WKUP_ONKEY] = अणु
		.primary = WM8350_WKUP_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_WKUP_ONKEY_EINT,
	पूर्ण,
	[WM8350_IRQ_WKUP_GP_WAKEUP] = अणु
		.primary = WM8350_WKUP_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_WKUP_GP_WAKEUP_EINT,
	पूर्ण,
	[WM8350_IRQ_CODEC_JCK_DET_L] = अणु
		.primary = WM8350_CODEC_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_CODEC_JCK_DET_L_EINT,
	पूर्ण,
	[WM8350_IRQ_CODEC_JCK_DET_R] = अणु
		.primary = WM8350_CODEC_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_CODEC_JCK_DET_R_EINT,
	पूर्ण,
	[WM8350_IRQ_CODEC_MICSCD] = अणु
		.primary = WM8350_CODEC_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_CODEC_MICSCD_EINT,
	पूर्ण,
	[WM8350_IRQ_CODEC_MICD] = अणु
		.primary = WM8350_CODEC_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_CODEC_MICD_EINT,
	पूर्ण,
	[WM8350_IRQ_EXT_USB_FB] = अणु
		.primary = WM8350_EXT_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_EXT_USB_FB_EINT,
	पूर्ण,
	[WM8350_IRQ_EXT_WALL_FB] = अणु
		.primary = WM8350_EXT_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_EXT_WALL_FB_EINT,
	पूर्ण,
	[WM8350_IRQ_EXT_BAT_FB] = अणु
		.primary = WM8350_EXT_INT,
		.reg = WM8350_COMPARATOR_INT_OFFSET,
		.mask = WM8350_EXT_BAT_FB_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(0)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP0_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(1)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP1_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(2)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP2_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(3)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP3_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(4)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP4_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(5)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP5_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(6)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP6_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(7)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP7_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(8)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP8_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(9)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP9_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(10)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP10_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(11)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP11_EINT,
	पूर्ण,
	[WM8350_IRQ_GPIO(12)] = अणु
		.primary = WM8350_GP_INT,
		.reg = WM8350_GPIO_INT_OFFSET,
		.mask = WM8350_GP12_EINT,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा wm8350_irq_data *irq_to_wm8350_irq(काष्ठा wm8350 *wm8350,
							पूर्णांक irq)
अणु
	वापस &wm8350_irqs[irq - wm8350->irq_base];
पूर्ण

/*
 * This is a thपढ़ोed IRQ handler so can access I2C/SPI.  Since all
 * पूर्णांकerrupts are clear on पढ़ो the IRQ line will be reनिश्चितed and
 * the physical IRQ will be handled again अगर another पूर्णांकerrupt is
 * निश्चितed जबतक we run - in the normal course of events this is a
 * rare occurrence so we save I2C/SPI पढ़ोs.  We're also assuming that
 * it's rare to get lots of पूर्णांकerrupts firing simultaneously so try to
 * minimise I/O.
 */
अटल irqवापस_t wm8350_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा wm8350 *wm8350 = irq_data;
	u16 level_one;
	u16 sub_reg[WM8350_NUM_IRQ_REGS];
	पूर्णांक पढ़ो_करोne[WM8350_NUM_IRQ_REGS];
	काष्ठा wm8350_irq_data *data;
	पूर्णांक i;

	level_one = wm8350_reg_पढ़ो(wm8350, WM8350_SYSTEM_INTERRUPTS)
		& ~wm8350_reg_पढ़ो(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK);

	अगर (!level_one)
		वापस IRQ_NONE;

	स_रखो(&पढ़ो_करोne, 0, माप(पढ़ो_करोne));

	क्रम (i = 0; i < ARRAY_SIZE(wm8350_irqs); i++) अणु
		data = &wm8350_irqs[i];

		अगर (!(level_one & data->primary))
			जारी;

		अगर (!पढ़ो_करोne[data->reg]) अणु
			sub_reg[data->reg] =
				wm8350_reg_पढ़ो(wm8350, WM8350_INT_STATUS_1 +
						data->reg);
			sub_reg[data->reg] &= ~wm8350->irq_masks[data->reg];
			पढ़ो_करोne[data->reg] = 1;
		पूर्ण

		अगर (sub_reg[data->reg] & data->mask)
			handle_nested_irq(wm8350->irq_base + i);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम wm8350_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा wm8350 *wm8350 = irq_data_get_irq_chip_data(data);

	mutex_lock(&wm8350->irq_lock);
पूर्ण

अटल व्योम wm8350_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा wm8350 *wm8350 = irq_data_get_irq_chip_data(data);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8350->irq_masks); i++) अणु
		/* If there's been a change in the mask ग_लिखो it back
		 * to the hardware. */
		WARN_ON(regmap_update_bits(wm8350->regmap,
					   WM8350_INT_STATUS_1_MASK + i,
					   0xffff, wm8350->irq_masks[i]));
	पूर्ण

	mutex_unlock(&wm8350->irq_lock);
पूर्ण

अटल व्योम wm8350_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा wm8350 *wm8350 = irq_data_get_irq_chip_data(data);
	काष्ठा wm8350_irq_data *irq_data = irq_to_wm8350_irq(wm8350,
							     data->irq);

	wm8350->irq_masks[irq_data->reg] &= ~irq_data->mask;
पूर्ण

अटल व्योम wm8350_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा wm8350 *wm8350 = irq_data_get_irq_chip_data(data);
	काष्ठा wm8350_irq_data *irq_data = irq_to_wm8350_irq(wm8350,
							     data->irq);

	wm8350->irq_masks[irq_data->reg] |= irq_data->mask;
पूर्ण

अटल काष्ठा irq_chip wm8350_irq_chip = अणु
	.name			= "wm8350",
	.irq_bus_lock		= wm8350_irq_lock,
	.irq_bus_sync_unlock	= wm8350_irq_sync_unlock,
	.irq_disable		= wm8350_irq_disable,
	.irq_enable		= wm8350_irq_enable,
पूर्ण;

पूर्णांक wm8350_irq_init(काष्ठा wm8350 *wm8350, पूर्णांक irq,
		    काष्ठा wm8350_platक्रमm_data *pdata)
अणु
	पूर्णांक ret, cur_irq, i;
	पूर्णांक flags = IRQF_ONESHOT;
	पूर्णांक irq_base = -1;

	अगर (!irq) अणु
		dev_warn(wm8350->dev, "No interrupt support, no core IRQ\n");
		वापस 0;
	पूर्ण

	/* Mask top level पूर्णांकerrupts */
	wm8350_reg_ग_लिखो(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK, 0xFFFF);

	/* Mask all inभागidual पूर्णांकerrupts by शेष and cache the
	 * masks.  We पढ़ो the masks back since there are unwritable
	 * bits in the mask रेजिस्टरs. */
	क्रम (i = 0; i < ARRAY_SIZE(wm8350->irq_masks); i++) अणु
		wm8350_reg_ग_लिखो(wm8350, WM8350_INT_STATUS_1_MASK + i,
				 0xFFFF);
		wm8350->irq_masks[i] =
			wm8350_reg_पढ़ो(wm8350,
					WM8350_INT_STATUS_1_MASK + i);
	पूर्ण

	mutex_init(&wm8350->irq_lock);
	wm8350->chip_irq = irq;

	अगर (pdata && pdata->irq_base > 0)
		irq_base = pdata->irq_base;

	wm8350->irq_base =
		irq_alloc_descs(irq_base, 0, ARRAY_SIZE(wm8350_irqs), 0);
	अगर (wm8350->irq_base < 0) अणु
		dev_warn(wm8350->dev, "Allocating irqs failed with %d\n",
			wm8350->irq_base);
		वापस 0;
	पूर्ण

	अगर (pdata && pdata->irq_high) अणु
		flags |= IRQF_TRIGGER_HIGH;

		wm8350_set_bits(wm8350, WM8350_SYSTEM_CONTROL_1,
				WM8350_IRQ_POL);
	पूर्ण अन्यथा अणु
		flags |= IRQF_TRIGGER_LOW;

		wm8350_clear_bits(wm8350, WM8350_SYSTEM_CONTROL_1,
				  WM8350_IRQ_POL);
	पूर्ण

	/* Register with genirq */
	क्रम (cur_irq = wm8350->irq_base;
	     cur_irq < ARRAY_SIZE(wm8350_irqs) + wm8350->irq_base;
	     cur_irq++) अणु
		irq_set_chip_data(cur_irq, wm8350);
		irq_set_chip_and_handler(cur_irq, &wm8350_irq_chip,
					 handle_edge_irq);
		irq_set_nested_thपढ़ो(cur_irq, 1);

		irq_clear_status_flags(cur_irq, IRQ_NOREQUEST | IRQ_NOPROBE);
	पूर्ण

	ret = request_thपढ़ोed_irq(irq, शून्य, wm8350_irq, flags,
				   "wm8350", wm8350);
	अगर (ret != 0)
		dev_err(wm8350->dev, "Failed to request IRQ: %d\n", ret);

	/* Allow पूर्णांकerrupts to fire */
	wm8350_reg_ग_लिखो(wm8350, WM8350_SYSTEM_INTERRUPTS_MASK, 0);

	वापस ret;
पूर्ण

पूर्णांक wm8350_irq_निकास(काष्ठा wm8350 *wm8350)
अणु
	मुक्त_irq(wm8350->chip_irq, wm8350);
	वापस 0;
पूर्ण
