<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * twl6030-irq.c - TWL6030 irq support
 *
 * Copyright (C) 2005-2009 Texas Instruments, Inc.
 *
 * Modअगरications to defer पूर्णांकerrupt handling to a kernel thपढ़ो:
 * Copyright (C) 2006 MontaVista Software, Inc.
 *
 * Based on tlv320aic23.c:
 * Copyright (c) by Kai Svahn <kai.svahn@nokia.com>
 *
 * Code cleanup and modअगरications to IRQ handler.
 * by syed khasim <x0khasim@ti.com>
 *
 * TWL6030 specअगरic code and IRQ handling changes by
 * Jagadeesh Bhaskar Pakaravoor <j-pakaravoor@ti.com>
 * Balaji T K <balajitk@ti.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/suspend.h>
#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_device.h>

#समावेश "twl-core.h"

/*
 * TWL6030 (unlike its predecessors, which had two level पूर्णांकerrupt handling)
 * three पूर्णांकerrupt रेजिस्टरs INT_STS_A, INT_STS_B and INT_STS_C.
 * It exposes status bits saying who has उठाओd an पूर्णांकerrupt. There are
 * three mask रेजिस्टरs that corresponds to these status रेजिस्टरs, that
 * enables/disables these पूर्णांकerrupts.
 *
 * We set up IRQs starting at a platक्रमm-specअगरied base. An पूर्णांकerrupt map table,
 * specअगरies mapping between पूर्णांकerrupt number and the associated module.
 */
#घोषणा TWL6030_NR_IRQS    20

अटल पूर्णांक twl6030_पूर्णांकerrupt_mapping[24] = अणु
	PWR_INTR_OFFSET,	/* Bit 0	PWRON			*/
	PWR_INTR_OFFSET,	/* Bit 1	RPWRON			*/
	PWR_INTR_OFFSET,	/* Bit 2	BAT_VLOW		*/
	RTC_INTR_OFFSET,	/* Bit 3	RTC_ALARM		*/
	RTC_INTR_OFFSET,	/* Bit 4	RTC_PERIOD		*/
	HOTDIE_INTR_OFFSET,	/* Bit 5	HOT_DIE			*/
	SMPSLDO_INTR_OFFSET,	/* Bit 6	VXXX_SHORT		*/
	SMPSLDO_INTR_OFFSET,	/* Bit 7	VMMC_SHORT		*/

	SMPSLDO_INTR_OFFSET,	/* Bit 8	VUSIM_SHORT		*/
	BATDETECT_INTR_OFFSET,	/* Bit 9	BAT			*/
	SIMDETECT_INTR_OFFSET,	/* Bit 10	SIM			*/
	MMCDETECT_INTR_OFFSET,	/* Bit 11	MMC			*/
	RSV_INTR_OFFSET,	/* Bit 12	Reserved		*/
	MADC_INTR_OFFSET,	/* Bit 13	GPADC_RT_EOC		*/
	MADC_INTR_OFFSET,	/* Bit 14	GPADC_SW_EOC		*/
	GASGAUGE_INTR_OFFSET,	/* Bit 15	CC_AUTOCAL		*/

	USBOTG_INTR_OFFSET,	/* Bit 16	ID_WKUP			*/
	USBOTG_INTR_OFFSET,	/* Bit 17	VBUS_WKUP		*/
	USBOTG_INTR_OFFSET,	/* Bit 18	ID			*/
	USB_PRES_INTR_OFFSET,	/* Bit 19	VBUS			*/
	CHARGER_INTR_OFFSET,	/* Bit 20	CHRG_CTRL		*/
	CHARGERFAULT_INTR_OFFSET,	/* Bit 21	EXT_CHRG	*/
	CHARGERFAULT_INTR_OFFSET,	/* Bit 22	INT_CHRG	*/
	RSV_INTR_OFFSET,	/* Bit 23	Reserved		*/
पूर्ण;

अटल पूर्णांक twl6032_पूर्णांकerrupt_mapping[24] = अणु
	PWR_INTR_OFFSET,	/* Bit 0	PWRON			*/
	PWR_INTR_OFFSET,	/* Bit 1	RPWRON			*/
	PWR_INTR_OFFSET,	/* Bit 2	SYS_VLOW		*/
	RTC_INTR_OFFSET,	/* Bit 3	RTC_ALARM		*/
	RTC_INTR_OFFSET,	/* Bit 4	RTC_PERIOD		*/
	HOTDIE_INTR_OFFSET,	/* Bit 5	HOT_DIE			*/
	SMPSLDO_INTR_OFFSET,	/* Bit 6	VXXX_SHORT		*/
	PWR_INTR_OFFSET,	/* Bit 7	SPDURATION		*/

	PWR_INTR_OFFSET,	/* Bit 8	WATCHDOG		*/
	BATDETECT_INTR_OFFSET,	/* Bit 9	BAT			*/
	SIMDETECT_INTR_OFFSET,	/* Bit 10	SIM			*/
	MMCDETECT_INTR_OFFSET,	/* Bit 11	MMC			*/
	MADC_INTR_OFFSET,	/* Bit 12	GPADC_RT_EOC		*/
	MADC_INTR_OFFSET,	/* Bit 13	GPADC_SW_EOC		*/
	GASGAUGE_INTR_OFFSET,	/* Bit 14	CC_EOC			*/
	GASGAUGE_INTR_OFFSET,	/* Bit 15	CC_AUTOCAL		*/

	USBOTG_INTR_OFFSET,	/* Bit 16	ID_WKUP			*/
	USBOTG_INTR_OFFSET,	/* Bit 17	VBUS_WKUP		*/
	USBOTG_INTR_OFFSET,	/* Bit 18	ID			*/
	USB_PRES_INTR_OFFSET,	/* Bit 19	VBUS			*/
	CHARGER_INTR_OFFSET,	/* Bit 20	CHRG_CTRL		*/
	CHARGERFAULT_INTR_OFFSET,	/* Bit 21	EXT_CHRG	*/
	CHARGERFAULT_INTR_OFFSET,	/* Bit 22	INT_CHRG	*/
	RSV_INTR_OFFSET,	/* Bit 23	Reserved		*/
पूर्ण;

/*----------------------------------------------------------------------*/

काष्ठा twl6030_irq अणु
	अचिन्हित पूर्णांक		irq_base;
	पूर्णांक			twl_irq;
	bool			irq_wake_enabled;
	atomic_t		wakeirqs;
	काष्ठा notअगरier_block	pm_nb;
	काष्ठा irq_chip		irq_chip;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	स्थिर पूर्णांक		*irq_mapping_tbl;
पूर्ण;

अटल काष्ठा twl6030_irq *twl6030_irq;

अटल पूर्णांक twl6030_irq_pm_notअगरier(काष्ठा notअगरier_block *notअगरier,
				   अचिन्हित दीर्घ pm_event, व्योम *unused)
अणु
	पूर्णांक chained_wakeups;
	काष्ठा twl6030_irq *pdata = container_of(notअगरier, काष्ठा twl6030_irq,
						  pm_nb);

	चयन (pm_event) अणु
	हाल PM_SUSPEND_PREPARE:
		chained_wakeups = atomic_पढ़ो(&pdata->wakeirqs);

		अगर (chained_wakeups && !pdata->irq_wake_enabled) अणु
			अगर (enable_irq_wake(pdata->twl_irq))
				pr_err("twl6030 IRQ wake enable failed\n");
			अन्यथा
				pdata->irq_wake_enabled = true;
		पूर्ण अन्यथा अगर (!chained_wakeups && pdata->irq_wake_enabled) अणु
			disable_irq_wake(pdata->twl_irq);
			pdata->irq_wake_enabled = false;
		पूर्ण

		disable_irq(pdata->twl_irq);
		अवरोध;

	हाल PM_POST_SUSPEND:
		enable_irq(pdata->twl_irq);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/*
* Thपढ़ोed irq handler क्रम the twl6030 पूर्णांकerrupt.
* We query the पूर्णांकerrupt controller in the twl6030 to determine
* which module is generating the पूर्णांकerrupt request and call
* handle_nested_irq क्रम that module.
*/
अटल irqवापस_t twl6030_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक i, ret;
	जोड़ अणु
		u8 bytes[4];
		__le32 पूर्णांक_sts;
	पूर्ण sts;
	u32 पूर्णांक_sts; /* sts.पूर्णांक_sts converted to CPU endianness */
	काष्ठा twl6030_irq *pdata = data;

	/* पढ़ो INT_STS_A, B and C in one shot using a burst पढ़ो */
	ret = twl_i2c_पढ़ो(TWL_MODULE_PIH, sts.bytes, REG_INT_STS_A, 3);
	अगर (ret) अणु
		pr_warn("twl6030_irq: I2C error %d reading PIH ISR\n", ret);
		वापस IRQ_HANDLED;
	पूर्ण

	sts.bytes[3] = 0; /* Only 24 bits are valid*/

	/*
	 * Since VBUS status bit is not reliable क्रम VBUS disconnect
	 * use CHARGER VBUS detection status bit instead.
	 */
	अगर (sts.bytes[2] & 0x10)
		sts.bytes[2] |= 0x08;

	पूर्णांक_sts = le32_to_cpu(sts.पूर्णांक_sts);
	क्रम (i = 0; पूर्णांक_sts; पूर्णांक_sts >>= 1, i++)
		अगर (पूर्णांक_sts & 0x1) अणु
			पूर्णांक module_irq =
				irq_find_mapping(pdata->irq_करोमुख्य,
						 pdata->irq_mapping_tbl[i]);
			अगर (module_irq)
				handle_nested_irq(module_irq);
			अन्यथा
				pr_err("twl6030_irq: Unmapped PIH ISR %u detected\n",
				       i);
			pr_debug("twl6030_irq: PIH ISR %u, virq%u\n",
				 i, module_irq);
		पूर्ण

	/*
	 * NOTE:
	 * Simulation confirms that करोcumentation is wrong w.r.t the
	 * पूर्णांकerrupt status clear operation. A single *byte* ग_लिखो to
	 * any one of STS_A to STS_C रेजिस्टर results in all three
	 * STS रेजिस्टरs being reset. Since it करोes not matter which
	 * value is written, all three रेजिस्टरs are cleared on a
	 * single byte ग_लिखो, so we just use 0x0 to clear.
	 */
	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_PIH, 0x00, REG_INT_STS_A);
	अगर (ret)
		pr_warn("twl6030_irq: I2C error in clearing PIH ISR\n");

	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

अटल पूर्णांक twl6030_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा twl6030_irq *pdata = irq_data_get_irq_chip_data(d);

	अगर (on)
		atomic_inc(&pdata->wakeirqs);
	अन्यथा
		atomic_dec(&pdata->wakeirqs);

	वापस 0;
पूर्ण

पूर्णांक twl6030_पूर्णांकerrupt_unmask(u8 bit_mask, u8 offset)
अणु
	पूर्णांक ret;
	u8 unmask_value;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_PIH, &unmask_value,
			REG_INT_STS_A + offset);
	unmask_value &= (~(bit_mask));
	ret |= twl_i2c_ग_लिखो_u8(TWL_MODULE_PIH, unmask_value,
			REG_INT_STS_A + offset); /* unmask INT_MSK_A/B/C */
	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl6030_पूर्णांकerrupt_unmask);

पूर्णांक twl6030_पूर्णांकerrupt_mask(u8 bit_mask, u8 offset)
अणु
	पूर्णांक ret;
	u8 mask_value;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_PIH, &mask_value,
			REG_INT_STS_A + offset);
	mask_value |= (bit_mask);
	ret |= twl_i2c_ग_लिखो_u8(TWL_MODULE_PIH, mask_value,
			REG_INT_STS_A + offset); /* mask INT_MSK_A/B/C */
	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl6030_पूर्णांकerrupt_mask);

पूर्णांक twl6030_mmc_card_detect_config(व्योम)
अणु
	पूर्णांक ret;
	u8 reg_val = 0;

	/* Unmasking the Card detect Interrupt line क्रम MMC1 from Phoenix */
	twl6030_पूर्णांकerrupt_unmask(TWL6030_MMCDETECT_INT_MASK,
						REG_INT_MSK_LINE_B);
	twl6030_पूर्णांकerrupt_unmask(TWL6030_MMCDETECT_INT_MASK,
						REG_INT_MSK_STS_B);
	/*
	 * Initially Configuring MMC_CTRL क्रम receiving पूर्णांकerrupts &
	 * Card status on TWL6030 क्रम MMC1
	 */
	ret = twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID0, &reg_val, TWL6030_MMCCTRL);
	अगर (ret < 0) अणु
		pr_err("twl6030: Failed to read MMCCTRL, error %d\n", ret);
		वापस ret;
	पूर्ण
	reg_val &= ~VMMC_AUTO_OFF;
	reg_val |= SW_FC;
	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID0, reg_val, TWL6030_MMCCTRL);
	अगर (ret < 0) अणु
		pr_err("twl6030: Failed to write MMCCTRL, error %d\n", ret);
		वापस ret;
	पूर्ण

	/* Configuring PullUp-PullDown रेजिस्टर */
	ret = twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID0, &reg_val,
						TWL6030_CFG_INPUT_PUPD3);
	अगर (ret < 0) अणु
		pr_err("twl6030: Failed to read CFG_INPUT_PUPD3, error %d\n",
									ret);
		वापस ret;
	पूर्ण
	reg_val &= ~(MMC_PU | MMC_PD);
	ret = twl_i2c_ग_लिखो_u8(TWL6030_MODULE_ID0, reg_val,
						TWL6030_CFG_INPUT_PUPD3);
	अगर (ret < 0) अणु
		pr_err("twl6030: Failed to write CFG_INPUT_PUPD3, error %d\n",
									ret);
		वापस ret;
	पूर्ण

	वापस irq_find_mapping(twl6030_irq->irq_करोमुख्य,
				 MMCDETECT_INTR_OFFSET);
पूर्ण
EXPORT_SYMBOL(twl6030_mmc_card_detect_config);

पूर्णांक twl6030_mmc_card_detect(काष्ठा device *dev, पूर्णांक slot)
अणु
	पूर्णांक ret = -EIO;
	u8 पढ़ो_reg = 0;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (pdev->id) अणु
		/* TWL6030 provide's Card detect support क्रम
		 * only MMC1 controller.
		 */
		pr_err("Unknown MMC controller %d in %s\n", pdev->id, __func__);
		वापस ret;
	पूर्ण
	/*
	 * BIT0 of MMC_CTRL on TWL6030 provides card status क्रम MMC1
	 * 0 - Card not present ,1 - Card present
	 */
	ret = twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID0, &पढ़ो_reg,
						TWL6030_MMCCTRL);
	अगर (ret >= 0)
		ret = पढ़ो_reg & STS_MMC;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(twl6030_mmc_card_detect);

अटल पूर्णांक twl6030_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			      irq_hw_number_t hwirq)
अणु
	काष्ठा twl6030_irq *pdata = d->host_data;

	irq_set_chip_data(virq, pdata);
	irq_set_chip_and_handler(virq,  &pdata->irq_chip, handle_simple_irq);
	irq_set_nested_thपढ़ो(virq, true);
	irq_set_parent(virq, pdata->twl_irq);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल व्योम twl6030_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq)
अणु
	irq_set_chip_and_handler(virq, शून्य, शून्य);
	irq_set_chip_data(virq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops twl6030_irq_करोमुख्य_ops = अणु
	.map	= twl6030_irq_map,
	.unmap	= twl6030_irq_unmap,
	.xlate	= irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

अटल स्थिर काष्ठा of_device_id twl6030_of_match[] __maybe_unused = अणु
	अणु.compatible = "ti,twl6030", &twl6030_पूर्णांकerrupt_mappingपूर्ण,
	अणु.compatible = "ti,twl6032", &twl6032_पूर्णांकerrupt_mappingपूर्ण,
	अणु पूर्ण,
पूर्ण;

पूर्णांक twl6030_init_irq(काष्ठा device *dev, पूर्णांक irq_num)
अणु
	काष्ठा			device_node *node = dev->of_node;
	पूर्णांक			nr_irqs;
	पूर्णांक			status;
	u8			mask[3];
	स्थिर काष्ठा of_device_id *of_id;

	of_id = of_match_device(twl6030_of_match, dev);
	अगर (!of_id || !of_id->data) अणु
		dev_err(dev, "Unknown TWL device model\n");
		वापस -EINVAL;
	पूर्ण

	nr_irqs = TWL6030_NR_IRQS;

	twl6030_irq = devm_kzalloc(dev, माप(*twl6030_irq), GFP_KERNEL);
	अगर (!twl6030_irq)
		वापस -ENOMEM;

	mask[0] = 0xFF;
	mask[1] = 0xFF;
	mask[2] = 0xFF;

	/* mask all पूर्णांक lines */
	status = twl_i2c_ग_लिखो(TWL_MODULE_PIH, &mask[0], REG_INT_MSK_LINE_A, 3);
	/* mask all पूर्णांक sts */
	status |= twl_i2c_ग_लिखो(TWL_MODULE_PIH, &mask[0], REG_INT_MSK_STS_A, 3);
	/* clear INT_STS_A,B,C */
	status |= twl_i2c_ग_लिखो(TWL_MODULE_PIH, &mask[0], REG_INT_STS_A, 3);

	अगर (status < 0) अणु
		dev_err(dev, "I2C err writing TWL_MODULE_PIH: %d\n", status);
		वापस status;
	पूर्ण

	/*
	 * install an irq handler क्रम each of the modules;
	 * clone dummy irq_chip since PIH can't *करो* anything
	 */
	twl6030_irq->irq_chip = dummy_irq_chip;
	twl6030_irq->irq_chip.name = "twl6030";
	twl6030_irq->irq_chip.irq_set_type = शून्य;
	twl6030_irq->irq_chip.irq_set_wake = twl6030_irq_set_wake;

	twl6030_irq->pm_nb.notअगरier_call = twl6030_irq_pm_notअगरier;
	atomic_set(&twl6030_irq->wakeirqs, 0);
	twl6030_irq->irq_mapping_tbl = of_id->data;

	twl6030_irq->irq_करोमुख्य =
		irq_करोमुख्य_add_linear(node, nr_irqs,
				      &twl6030_irq_करोमुख्य_ops, twl6030_irq);
	अगर (!twl6030_irq->irq_करोमुख्य) अणु
		dev_err(dev, "Can't add irq_domain\n");
		वापस -ENOMEM;
	पूर्ण

	dev_info(dev, "PIH (irq %d) nested IRQs\n", irq_num);

	/* install an irq handler to demultiplex the TWL6030 पूर्णांकerrupt */
	status = request_thपढ़ोed_irq(irq_num, शून्य, twl6030_irq_thपढ़ो,
				      IRQF_ONESHOT, "TWL6030-PIH", twl6030_irq);
	अगर (status < 0) अणु
		dev_err(dev, "could not claim irq %d: %d\n", irq_num, status);
		जाओ fail_irq;
	पूर्ण

	twl6030_irq->twl_irq = irq_num;
	रेजिस्टर_pm_notअगरier(&twl6030_irq->pm_nb);
	वापस 0;

fail_irq:
	irq_करोमुख्य_हटाओ(twl6030_irq->irq_करोमुख्य);
	वापस status;
पूर्ण

पूर्णांक twl6030_निकास_irq(व्योम)
अणु
	अगर (twl6030_irq && twl6030_irq->twl_irq) अणु
		unरेजिस्टर_pm_notअगरier(&twl6030_irq->pm_nb);
		मुक्त_irq(twl6030_irq->twl_irq, शून्य);
		/*
		 * TODO: IRQ करोमुख्य and allocated nested IRQ descriptors
		 * should be मुक्तd somehow here. Now It can't be करोne, because
		 * child devices will not be deleted during removing of
		 * TWL Core driver and they will still contain allocated
		 * virt IRQs in their Resources tables.
		 * The same prevents us from using devm_request_thपढ़ोed_irq()
		 * in this module.
		 */
	पूर्ण
	वापस 0;
पूर्ण

