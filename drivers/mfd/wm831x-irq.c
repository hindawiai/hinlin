<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm831x-irq.c  --  Interrupt controller support क्रम Wolfson WM831x PMICs
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/gpपन.स>
#समावेश <linux/mfd/wm831x/irq.h>

#समावेश <linux/delay.h>

काष्ठा wm831x_irq_data अणु
	पूर्णांक primary;
	पूर्णांक reg;
	पूर्णांक mask;
पूर्ण;

अटल काष्ठा wm831x_irq_data wm831x_irqs[] = अणु
	[WM831X_IRQ_TEMP_THW] = अणु
		.primary = WM831X_TEMP_INT,
		.reg = 1,
		.mask = WM831X_TEMP_THW_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_1] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP1_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_2] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP2_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_3] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP3_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_4] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP4_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_5] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP5_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_6] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP6_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_7] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP7_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_8] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP8_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_9] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP9_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_10] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP10_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_11] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP11_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_12] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP12_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_13] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP13_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_14] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP14_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_15] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP15_EINT,
	पूर्ण,
	[WM831X_IRQ_GPIO_16] = अणु
		.primary = WM831X_GP_INT,
		.reg = 5,
		.mask = WM831X_GP16_EINT,
	पूर्ण,
	[WM831X_IRQ_ON] = अणु
		.primary = WM831X_ON_PIN_INT,
		.reg = 1,
		.mask = WM831X_ON_PIN_EINT,
	पूर्ण,
	[WM831X_IRQ_PPM_SYSLO] = अणु
		.primary = WM831X_PPM_INT,
		.reg = 1,
		.mask = WM831X_PPM_SYSLO_EINT,
	पूर्ण,
	[WM831X_IRQ_PPM_PWR_SRC] = अणु
		.primary = WM831X_PPM_INT,
		.reg = 1,
		.mask = WM831X_PPM_PWR_SRC_EINT,
	पूर्ण,
	[WM831X_IRQ_PPM_USB_CURR] = अणु
		.primary = WM831X_PPM_INT,
		.reg = 1,
		.mask = WM831X_PPM_USB_CURR_EINT,
	पूर्ण,
	[WM831X_IRQ_WDOG_TO] = अणु
		.primary = WM831X_WDOG_INT,
		.reg = 1,
		.mask = WM831X_WDOG_TO_EINT,
	पूर्ण,
	[WM831X_IRQ_RTC_PER] = अणु
		.primary = WM831X_RTC_INT,
		.reg = 1,
		.mask = WM831X_RTC_PER_EINT,
	पूर्ण,
	[WM831X_IRQ_RTC_ALM] = अणु
		.primary = WM831X_RTC_INT,
		.reg = 1,
		.mask = WM831X_RTC_ALM_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_BATT_HOT] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_BATT_HOT_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_BATT_COLD] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_BATT_COLD_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_BATT_FAIL] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_BATT_FAIL_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_OV] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_OV_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_END] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_END_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_TO] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_TO_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_MODE] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_MODE_EINT,
	पूर्ण,
	[WM831X_IRQ_CHG_START] = अणु
		.primary = WM831X_CHG_INT,
		.reg = 2,
		.mask = WM831X_CHG_START_EINT,
	पूर्ण,
	[WM831X_IRQ_TCHDATA] = अणु
		.primary = WM831X_TCHDATA_INT,
		.reg = 1,
		.mask = WM831X_TCHDATA_EINT,
	पूर्ण,
	[WM831X_IRQ_TCHPD] = अणु
		.primary = WM831X_TCHPD_INT,
		.reg = 1,
		.mask = WM831X_TCHPD_EINT,
	पूर्ण,
	[WM831X_IRQ_AUXADC_DATA] = अणु
		.primary = WM831X_AUXADC_INT,
		.reg = 1,
		.mask = WM831X_AUXADC_DATA_EINT,
	पूर्ण,
	[WM831X_IRQ_AUXADC_DCOMP1] = अणु
		.primary = WM831X_AUXADC_INT,
		.reg = 1,
		.mask = WM831X_AUXADC_DCOMP1_EINT,
	पूर्ण,
	[WM831X_IRQ_AUXADC_DCOMP2] = अणु
		.primary = WM831X_AUXADC_INT,
		.reg = 1,
		.mask = WM831X_AUXADC_DCOMP2_EINT,
	पूर्ण,
	[WM831X_IRQ_AUXADC_DCOMP3] = अणु
		.primary = WM831X_AUXADC_INT,
		.reg = 1,
		.mask = WM831X_AUXADC_DCOMP3_EINT,
	पूर्ण,
	[WM831X_IRQ_AUXADC_DCOMP4] = अणु
		.primary = WM831X_AUXADC_INT,
		.reg = 1,
		.mask = WM831X_AUXADC_DCOMP4_EINT,
	पूर्ण,
	[WM831X_IRQ_CS1] = अणु
		.primary = WM831X_CS_INT,
		.reg = 2,
		.mask = WM831X_CS1_EINT,
	पूर्ण,
	[WM831X_IRQ_CS2] = अणु
		.primary = WM831X_CS_INT,
		.reg = 2,
		.mask = WM831X_CS2_EINT,
	पूर्ण,
	[WM831X_IRQ_HC_DC1] = अणु
		.primary = WM831X_HC_INT,
		.reg = 4,
		.mask = WM831X_HC_DC1_EINT,
	पूर्ण,
	[WM831X_IRQ_HC_DC2] = अणु
		.primary = WM831X_HC_INT,
		.reg = 4,
		.mask = WM831X_HC_DC2_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO1] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO1_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO2] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO2_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO3] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO3_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO4] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO4_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO5] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO5_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO6] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO6_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO7] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO7_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO8] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO8_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO9] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO9_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_LDO10] = अणु
		.primary = WM831X_UV_INT,
		.reg = 3,
		.mask = WM831X_UV_LDO10_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_DC1] = अणु
		.primary = WM831X_UV_INT,
		.reg = 4,
		.mask = WM831X_UV_DC1_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_DC2] = अणु
		.primary = WM831X_UV_INT,
		.reg = 4,
		.mask = WM831X_UV_DC2_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_DC3] = अणु
		.primary = WM831X_UV_INT,
		.reg = 4,
		.mask = WM831X_UV_DC3_EINT,
	पूर्ण,
	[WM831X_IRQ_UV_DC4] = अणु
		.primary = WM831X_UV_INT,
		.reg = 4,
		.mask = WM831X_UV_DC4_EINT,
	पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक irq_data_to_status_reg(काष्ठा wm831x_irq_data *irq_data)
अणु
	वापस WM831X_INTERRUPT_STATUS_1 - 1 + irq_data->reg;
पूर्ण

अटल अंतरभूत काष्ठा wm831x_irq_data *irq_to_wm831x_irq(काष्ठा wm831x *wm831x,
							पूर्णांक irq)
अणु
	वापस &wm831x_irqs[irq];
पूर्ण

अटल व्योम wm831x_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा wm831x *wm831x = irq_data_get_irq_chip_data(data);

	mutex_lock(&wm831x->irq_lock);
पूर्ण

अटल व्योम wm831x_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा wm831x *wm831x = irq_data_get_irq_chip_data(data);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm831x->gpio_update); i++) अणु
		अगर (wm831x->gpio_update[i]) अणु
			wm831x_set_bits(wm831x, WM831X_GPIO1_CONTROL + i,
					WM831X_GPN_INT_MODE | WM831X_GPN_POL,
					wm831x->gpio_update[i]);
			wm831x->gpio_update[i] = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm831x->irq_masks_cur); i++) अणु
		/* If there's been a change in the mask ग_लिखो it back
		 * to the hardware. */
		अगर (wm831x->irq_masks_cur[i] != wm831x->irq_masks_cache[i]) अणु
			dev_dbg(wm831x->dev, "IRQ mask sync: %x = %x\n",
				WM831X_INTERRUPT_STATUS_1_MASK + i,
				wm831x->irq_masks_cur[i]);

			wm831x->irq_masks_cache[i] = wm831x->irq_masks_cur[i];
			wm831x_reg_ग_लिखो(wm831x,
					 WM831X_INTERRUPT_STATUS_1_MASK + i,
					 wm831x->irq_masks_cur[i]);
		पूर्ण
	पूर्ण

	mutex_unlock(&wm831x->irq_lock);
पूर्ण

अटल व्योम wm831x_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा wm831x *wm831x = irq_data_get_irq_chip_data(data);
	काष्ठा wm831x_irq_data *irq_data = irq_to_wm831x_irq(wm831x,
							     data->hwirq);

	wm831x->irq_masks_cur[irq_data->reg - 1] &= ~irq_data->mask;
पूर्ण

अटल व्योम wm831x_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा wm831x *wm831x = irq_data_get_irq_chip_data(data);
	काष्ठा wm831x_irq_data *irq_data = irq_to_wm831x_irq(wm831x,
							     data->hwirq);

	wm831x->irq_masks_cur[irq_data->reg - 1] |= irq_data->mask;
पूर्ण

अटल पूर्णांक wm831x_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा wm831x *wm831x = irq_data_get_irq_chip_data(data);
	पूर्णांक irq;

	irq = data->hwirq;

	अगर (irq < WM831X_IRQ_GPIO_1 || irq > WM831X_IRQ_GPIO_11) अणु
		/* Ignore पूर्णांकernal-only IRQs */
		अगर (irq >= 0 && irq < WM831X_NUM_IRQS)
			वापस 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	/* Rebase the IRQ पूर्णांकo the GPIO range so we've got a sensible array
	 * index.
	 */
	irq -= WM831X_IRQ_GPIO_1;

	/* We set the high bit to flag that we need an update; करोn't
	 * करो the update here as we can be called with the bus lock
	 * held.
	 */
	wm831x->gpio_level_low[irq] = false;
	wm831x->gpio_level_high[irq] = false;
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_BOTH:
		wm831x->gpio_update[irq] = 0x10000 | WM831X_GPN_INT_MODE;
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
		wm831x->gpio_update[irq] = 0x10000 | WM831X_GPN_POL;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		wm831x->gpio_update[irq] = 0x10000;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		wm831x->gpio_update[irq] = 0x10000 | WM831X_GPN_POL;
		wm831x->gpio_level_high[irq] = true;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		wm831x->gpio_update[irq] = 0x10000;
		wm831x->gpio_level_low[irq] = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip wm831x_irq_chip = अणु
	.name			= "wm831x",
	.irq_bus_lock		= wm831x_irq_lock,
	.irq_bus_sync_unlock	= wm831x_irq_sync_unlock,
	.irq_disable		= wm831x_irq_disable,
	.irq_enable		= wm831x_irq_enable,
	.irq_set_type		= wm831x_irq_set_type,
पूर्ण;

/* The processing of the primary पूर्णांकerrupt occurs in a thपढ़ो so that
 * we can पूर्णांकeract with the device over I2C or SPI. */
अटल irqवापस_t wm831x_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm831x *wm831x = data;
	अचिन्हित पूर्णांक i;
	पूर्णांक primary, status_addr, ret;
	पूर्णांक status_regs[WM831X_NUM_IRQ_REGS] = अणु 0 पूर्ण;
	पूर्णांक पढ़ो[WM831X_NUM_IRQ_REGS] = अणु 0 पूर्ण;
	पूर्णांक *status;

	primary = wm831x_reg_पढ़ो(wm831x, WM831X_SYSTEM_INTERRUPTS);
	अगर (primary < 0) अणु
		dev_err(wm831x->dev, "Failed to read system interrupt: %d\n",
			primary);
		जाओ out;
	पूर्ण

	/* The touch पूर्णांकerrupts are visible in the primary रेजिस्टर as
	 * an optimisation; खोलो code this to aव्योम complicating the
	 * मुख्य handling loop and so we can also skip iterating the
	 * descriptors.
	 */
	अगर (primary & WM831X_TCHPD_INT)
		handle_nested_irq(irq_find_mapping(wm831x->irq_करोमुख्य,
						   WM831X_IRQ_TCHPD));
	अगर (primary & WM831X_TCHDATA_INT)
		handle_nested_irq(irq_find_mapping(wm831x->irq_करोमुख्य,
						   WM831X_IRQ_TCHDATA));
	primary &= ~(WM831X_TCHDATA_EINT | WM831X_TCHPD_EINT);

	क्रम (i = 0; i < ARRAY_SIZE(wm831x_irqs); i++) अणु
		पूर्णांक offset = wm831x_irqs[i].reg - 1;

		अगर (!(primary & wm831x_irqs[i].primary))
			जारी;

		status = &status_regs[offset];

		/* Hopefully there should only be one रेजिस्टर to पढ़ो
		 * each समय otherwise we ought to करो a block पढ़ो. */
		अगर (!पढ़ो[offset]) अणु
			status_addr = irq_data_to_status_reg(&wm831x_irqs[i]);

			*status = wm831x_reg_पढ़ो(wm831x, status_addr);
			अगर (*status < 0) अणु
				dev_err(wm831x->dev,
					"Failed to read IRQ status: %d\n",
					*status);
				जाओ out;
			पूर्ण

			पढ़ो[offset] = 1;

			/* Ignore any bits that we करोn't think are masked */
			*status &= ~wm831x->irq_masks_cur[offset];

			/* Acknowledge now so we करोn't miss
			 * notअगरications जबतक we handle.
			 */
			wm831x_reg_ग_लिखो(wm831x, status_addr, *status);
		पूर्ण

		अगर (*status & wm831x_irqs[i].mask)
			handle_nested_irq(irq_find_mapping(wm831x->irq_करोमुख्य,
							   i));

		/* Simulate an edge triggered IRQ by polling the input
		 * status.  This is sucky but improves पूर्णांकeroperability.
		 */
		अगर (primary == WM831X_GP_INT &&
		    wm831x->gpio_level_high[i - WM831X_IRQ_GPIO_1]) अणु
			ret = wm831x_reg_पढ़ो(wm831x, WM831X_GPIO_LEVEL);
			जबतक (ret & 1 << (i - WM831X_IRQ_GPIO_1)) अणु
				handle_nested_irq(irq_find_mapping(wm831x->irq_करोमुख्य,
								   i));
				ret = wm831x_reg_पढ़ो(wm831x,
						      WM831X_GPIO_LEVEL);
			पूर्ण
		पूर्ण

		अगर (primary == WM831X_GP_INT &&
		    wm831x->gpio_level_low[i - WM831X_IRQ_GPIO_1]) अणु
			ret = wm831x_reg_पढ़ो(wm831x, WM831X_GPIO_LEVEL);
			जबतक (!(ret & 1 << (i - WM831X_IRQ_GPIO_1))) अणु
				handle_nested_irq(irq_find_mapping(wm831x->irq_करोमुख्य,
								   i));
				ret = wm831x_reg_पढ़ो(wm831x,
						      WM831X_GPIO_LEVEL);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm831x_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	irq_set_chip_data(virq, h->host_data);
	irq_set_chip_and_handler(virq, &wm831x_irq_chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops wm831x_irq_करोमुख्य_ops = अणु
	.map	= wm831x_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

पूर्णांक wm831x_irq_init(काष्ठा wm831x *wm831x, पूर्णांक irq)
अणु
	काष्ठा wm831x_pdata *pdata = &wm831x->pdata;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक i, ret, irq_base;

	mutex_init(&wm831x->irq_lock);

	/* Mask the inभागidual पूर्णांकerrupt sources */
	क्रम (i = 0; i < ARRAY_SIZE(wm831x->irq_masks_cur); i++) अणु
		wm831x->irq_masks_cur[i] = 0xffff;
		wm831x->irq_masks_cache[i] = 0xffff;
		wm831x_reg_ग_लिखो(wm831x, WM831X_INTERRUPT_STATUS_1_MASK + i,
				 0xffff);
	पूर्ण

	/* Try to dynamically allocate IRQs अगर no base is specअगरied */
	अगर (pdata->irq_base) अणु
		irq_base = irq_alloc_descs(pdata->irq_base, 0,
					   WM831X_NUM_IRQS, 0);
		अगर (irq_base < 0) अणु
			dev_warn(wm831x->dev, "Failed to allocate IRQs: %d\n",
				 irq_base);
			irq_base = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		irq_base = 0;
	पूर्ण

	अगर (irq_base)
		करोमुख्य = irq_करोमुख्य_add_legacy(wm831x->dev->of_node,
					       ARRAY_SIZE(wm831x_irqs),
					       irq_base, 0,
					       &wm831x_irq_करोमुख्य_ops,
					       wm831x);
	अन्यथा
		करोमुख्य = irq_करोमुख्य_add_linear(wm831x->dev->of_node,
					       ARRAY_SIZE(wm831x_irqs),
					       &wm831x_irq_करोमुख्य_ops,
					       wm831x);

	अगर (!करोमुख्य) अणु
		dev_warn(wm831x->dev, "Failed to allocate IRQ domain\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->irq_cmos)
		i = 0;
	अन्यथा
		i = WM831X_IRQ_OD;

	wm831x_set_bits(wm831x, WM831X_IRQ_CONFIG,
			WM831X_IRQ_OD, i);

	wm831x->irq = irq;
	wm831x->irq_करोमुख्य = करोमुख्य;

	अगर (irq) अणु
		/* Try to flag /IRQ as a wake source; there are a number of
		 * unconditional wake sources in the PMIC so this isn't
		 * conditional but we करोn't actually care *too* much अगर it
		 * fails.
		 */
		ret = enable_irq_wake(irq);
		अगर (ret != 0) अणु
			dev_warn(wm831x->dev,
				 "Can't enable IRQ as wake source: %d\n",
				 ret);
		पूर्ण

		ret = request_thपढ़ोed_irq(irq, शून्य, wm831x_irq_thपढ़ो,
					   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					   "wm831x", wm831x);
		अगर (ret != 0) अणु
			dev_err(wm831x->dev, "Failed to request IRQ %d: %d\n",
				irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(wm831x->dev,
			 "No interrupt specified - functionality limited\n");
	पूर्ण

	/* Enable top level पूर्णांकerrupts, we mask at secondary level */
	wm831x_reg_ग_लिखो(wm831x, WM831X_SYSTEM_INTERRUPTS_MASK, 0);

	वापस 0;
पूर्ण

व्योम wm831x_irq_निकास(काष्ठा wm831x *wm831x)
अणु
	अगर (wm831x->irq)
		मुक्त_irq(wm831x->irq, wm831x);
पूर्ण
