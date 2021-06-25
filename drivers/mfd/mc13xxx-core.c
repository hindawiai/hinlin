<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2009-2010 Pengutronix
 * Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>
 *
 * loosely based on an earlier driver that has
 * Copyright 2009 Pengutronix, Sascha Hauer <s.hauer@pengutronix.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>

#समावेश "mc13xxx.h"

#घोषणा MC13XXX_IRQSTAT0	0
#घोषणा MC13XXX_IRQMASK0	1
#घोषणा MC13XXX_IRQSTAT1	3
#घोषणा MC13XXX_IRQMASK1	4

#घोषणा MC13XXX_REVISION	7
#घोषणा MC13XXX_REVISION_REVMETAL	(0x07 <<  0)
#घोषणा MC13XXX_REVISION_REVFULL	(0x03 <<  3)
#घोषणा MC13XXX_REVISION_ICID		(0x07 <<  6)
#घोषणा MC13XXX_REVISION_FIN		(0x03 <<  9)
#घोषणा MC13XXX_REVISION_FAB		(0x03 << 11)
#घोषणा MC13XXX_REVISION_ICIDCODE	(0x3f << 13)

#घोषणा MC34708_REVISION_REVMETAL	(0x07 <<  0)
#घोषणा MC34708_REVISION_REVFULL	(0x07 <<  3)
#घोषणा MC34708_REVISION_FIN		(0x07 <<  6)
#घोषणा MC34708_REVISION_FAB		(0x07 <<  9)

#घोषणा MC13XXX_PWRCTRL		15
#घोषणा MC13XXX_PWRCTRL_WसूचीESET	(1 << 12)

#घोषणा MC13XXX_ADC1		44
#घोषणा MC13XXX_ADC1_ADEN		(1 << 0)
#घोषणा MC13XXX_ADC1_RAND		(1 << 1)
#घोषणा MC13XXX_ADC1_ADSEL		(1 << 3)
#घोषणा MC13XXX_ADC1_ASC		(1 << 20)
#घोषणा MC13XXX_ADC1_ADTRIGIGN		(1 << 21)

#घोषणा MC13XXX_ADC2		45

व्योम mc13xxx_lock(काष्ठा mc13xxx *mc13xxx)
अणु
	अगर (!mutex_trylock(&mc13xxx->lock)) अणु
		dev_dbg(mc13xxx->dev, "wait for %s from %ps\n",
				__func__, __builtin_वापस_address(0));

		mutex_lock(&mc13xxx->lock);
	पूर्ण
	dev_dbg(mc13xxx->dev, "%s from %ps\n",
			__func__, __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(mc13xxx_lock);

व्योम mc13xxx_unlock(काष्ठा mc13xxx *mc13xxx)
अणु
	dev_dbg(mc13xxx->dev, "%s from %ps\n",
			__func__, __builtin_वापस_address(0));
	mutex_unlock(&mc13xxx->lock);
पूर्ण
EXPORT_SYMBOL(mc13xxx_unlock);

पूर्णांक mc13xxx_reg_पढ़ो(काष्ठा mc13xxx *mc13xxx, अचिन्हित पूर्णांक offset, u32 *val)
अणु
	पूर्णांक ret;

	ret = regmap_पढ़ो(mc13xxx->regmap, offset, val);
	dev_vdbg(mc13xxx->dev, "[0x%02x] -> 0x%06x\n", offset, *val);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mc13xxx_reg_पढ़ो);

पूर्णांक mc13xxx_reg_ग_लिखो(काष्ठा mc13xxx *mc13xxx, अचिन्हित पूर्णांक offset, u32 val)
अणु
	dev_vdbg(mc13xxx->dev, "[0x%02x] <- 0x%06x\n", offset, val);

	अगर (val >= BIT(24))
		वापस -EINVAL;

	वापस regmap_ग_लिखो(mc13xxx->regmap, offset, val);
पूर्ण
EXPORT_SYMBOL(mc13xxx_reg_ग_लिखो);

पूर्णांक mc13xxx_reg_rmw(काष्ठा mc13xxx *mc13xxx, अचिन्हित पूर्णांक offset,
		u32 mask, u32 val)
अणु
	BUG_ON(val & ~mask);
	dev_vdbg(mc13xxx->dev, "[0x%02x] <- 0x%06x (mask: 0x%06x)\n",
			offset, val, mask);

	वापस regmap_update_bits(mc13xxx->regmap, offset, mask, val);
पूर्ण
EXPORT_SYMBOL(mc13xxx_reg_rmw);

पूर्णांक mc13xxx_irq_mask(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq)
अणु
	पूर्णांक virq = regmap_irq_get_virq(mc13xxx->irq_data, irq);

	disable_irq_nosync(virq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mc13xxx_irq_mask);

पूर्णांक mc13xxx_irq_unmask(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq)
अणु
	पूर्णांक virq = regmap_irq_get_virq(mc13xxx->irq_data, irq);

	enable_irq(virq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mc13xxx_irq_unmask);

पूर्णांक mc13xxx_irq_status(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq,
		पूर्णांक *enabled, पूर्णांक *pending)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक offmask = irq < 24 ? MC13XXX_IRQMASK0 : MC13XXX_IRQMASK1;
	अचिन्हित पूर्णांक ofख_स्थिति = irq < 24 ? MC13XXX_IRQSTAT0 : MC13XXX_IRQSTAT1;
	u32 irqbit = 1 << (irq < 24 ? irq : irq - 24);

	अगर (irq < 0 || irq >= ARRAY_SIZE(mc13xxx->irqs))
		वापस -EINVAL;

	अगर (enabled) अणु
		u32 mask;

		ret = mc13xxx_reg_पढ़ो(mc13xxx, offmask, &mask);
		अगर (ret)
			वापस ret;

		*enabled = mask & irqbit;
	पूर्ण

	अगर (pending) अणु
		u32 stat;

		ret = mc13xxx_reg_पढ़ो(mc13xxx, ofख_स्थिति, &stat);
		अगर (ret)
			वापस ret;

		*pending = stat & irqbit;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mc13xxx_irq_status);

पूर्णांक mc13xxx_irq_request(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq,
		irq_handler_t handler, स्थिर अक्षर *name, व्योम *dev)
अणु
	पूर्णांक virq = regmap_irq_get_virq(mc13xxx->irq_data, irq);

	वापस devm_request_thपढ़ोed_irq(mc13xxx->dev, virq, शून्य, handler,
					 IRQF_ONESHOT, name, dev);
पूर्ण
EXPORT_SYMBOL(mc13xxx_irq_request);

पूर्णांक mc13xxx_irq_मुक्त(काष्ठा mc13xxx *mc13xxx, पूर्णांक irq, व्योम *dev)
अणु
	पूर्णांक virq = regmap_irq_get_virq(mc13xxx->irq_data, irq);

	devm_मुक्त_irq(mc13xxx->dev, virq, dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mc13xxx_irq_मुक्त);

#घोषणा maskval(reg, mask)	(((reg) & (mask)) >> __ffs(mask))
अटल व्योम mc13xxx_prपूर्णांक_revision(काष्ठा mc13xxx *mc13xxx, u32 revision)
अणु
	dev_info(mc13xxx->dev, "%s: rev: %d.%d, "
			"fin: %d, fab: %d, icid: %d/%d\n",
			mc13xxx->variant->name,
			maskval(revision, MC13XXX_REVISION_REVFULL),
			maskval(revision, MC13XXX_REVISION_REVMETAL),
			maskval(revision, MC13XXX_REVISION_FIN),
			maskval(revision, MC13XXX_REVISION_FAB),
			maskval(revision, MC13XXX_REVISION_ICID),
			maskval(revision, MC13XXX_REVISION_ICIDCODE));
पूर्ण

अटल व्योम mc34708_prपूर्णांक_revision(काष्ठा mc13xxx *mc13xxx, u32 revision)
अणु
	dev_info(mc13xxx->dev, "%s: rev %d.%d, fin: %d, fab: %d\n",
			mc13xxx->variant->name,
			maskval(revision, MC34708_REVISION_REVFULL),
			maskval(revision, MC34708_REVISION_REVMETAL),
			maskval(revision, MC34708_REVISION_FIN),
			maskval(revision, MC34708_REVISION_FAB));
पूर्ण

/* These are only exported क्रम mc13xxx-i2c and mc13xxx-spi */
काष्ठा mc13xxx_variant mc13xxx_variant_mc13783 = अणु
	.name = "mc13783",
	.prपूर्णांक_revision = mc13xxx_prपूर्णांक_revision,
पूर्ण;
EXPORT_SYMBOL_GPL(mc13xxx_variant_mc13783);

काष्ठा mc13xxx_variant mc13xxx_variant_mc13892 = अणु
	.name = "mc13892",
	.prपूर्णांक_revision = mc13xxx_prपूर्णांक_revision,
पूर्ण;
EXPORT_SYMBOL_GPL(mc13xxx_variant_mc13892);

काष्ठा mc13xxx_variant mc13xxx_variant_mc34708 = अणु
	.name = "mc34708",
	.prपूर्णांक_revision = mc34708_prपूर्णांक_revision,
पूर्ण;
EXPORT_SYMBOL_GPL(mc13xxx_variant_mc34708);

अटल स्थिर अक्षर *mc13xxx_get_chipname(काष्ठा mc13xxx *mc13xxx)
अणु
	वापस mc13xxx->variant->name;
पूर्ण

पूर्णांक mc13xxx_get_flags(काष्ठा mc13xxx *mc13xxx)
अणु
	वापस mc13xxx->flags;
पूर्ण
EXPORT_SYMBOL(mc13xxx_get_flags);

#घोषणा MC13XXX_ADC1_CHAN0_SHIFT	5
#घोषणा MC13XXX_ADC1_CHAN1_SHIFT	8
#घोषणा MC13783_ADC1_ATO_SHIFT		11
#घोषणा MC13783_ADC1_ATOX		(1 << 19)

काष्ठा mc13xxx_adcकरोne_data अणु
	काष्ठा mc13xxx *mc13xxx;
	काष्ठा completion करोne;
पूर्ण;

अटल irqवापस_t mc13xxx_handler_adcकरोne(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mc13xxx_adcकरोne_data *adcकरोne_data = data;

	complete_all(&adcकरोne_data->करोne);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा MC13XXX_ADC_WORKING (1 << 0)

पूर्णांक mc13xxx_adc_करो_conversion(काष्ठा mc13xxx *mc13xxx, अचिन्हित पूर्णांक mode,
		अचिन्हित पूर्णांक channel, u8 ato, bool atox,
		अचिन्हित पूर्णांक *sample)
अणु
	u32 adc0, adc1, old_adc0;
	पूर्णांक i, ret;
	काष्ठा mc13xxx_adcकरोne_data adcकरोne_data = अणु
		.mc13xxx = mc13xxx,
	पूर्ण;
	init_completion(&adcकरोne_data.करोne);

	dev_dbg(mc13xxx->dev, "%s\n", __func__);

	mc13xxx_lock(mc13xxx);

	अगर (mc13xxx->adcflags & MC13XXX_ADC_WORKING) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	mc13xxx->adcflags |= MC13XXX_ADC_WORKING;

	ret = mc13xxx_reg_पढ़ो(mc13xxx, MC13XXX_ADC0, &old_adc0);
	अगर (ret)
		जाओ out;

	adc0 = MC13XXX_ADC0_ADINC1 | MC13XXX_ADC0_ADINC2 |
	       MC13XXX_ADC0_CHRGRAWDIV;
	adc1 = MC13XXX_ADC1_ADEN | MC13XXX_ADC1_ADTRIGIGN | MC13XXX_ADC1_ASC;

	/*
	 * Channels mapped through ADIN7:
	 * 7  - General purpose ADIN7
	 * 16 - UID
	 * 17 - Die temperature
	 */
	अगर (channel > 7 && channel < 16) अणु
		adc1 |= MC13XXX_ADC1_ADSEL;
	पूर्ण अन्यथा अगर (channel == 16) अणु
		adc0 |= MC13XXX_ADC0_ADIN7SEL_UID;
		channel = 7;
	पूर्ण अन्यथा अगर (channel == 17) अणु
		adc0 |= MC13XXX_ADC0_ADIN7SEL_DIE;
		channel = 7;
	पूर्ण

	चयन (mode) अणु
	हाल MC13XXX_ADC_MODE_TS:
		adc0 |= MC13XXX_ADC0_ADREFEN | MC13XXX_ADC0_TSMOD0 |
			MC13XXX_ADC0_TSMOD1;
		adc1 |= 4 << MC13XXX_ADC1_CHAN1_SHIFT;
		अवरोध;

	हाल MC13XXX_ADC_MODE_SINGLE_CHAN:
		adc0 |= old_adc0 & MC13XXX_ADC0_CONFIG_MASK;
		adc1 |= (channel & 0x7) << MC13XXX_ADC1_CHAN0_SHIFT;
		adc1 |= MC13XXX_ADC1_RAND;
		अवरोध;

	हाल MC13XXX_ADC_MODE_MULT_CHAN:
		adc0 |= old_adc0 & MC13XXX_ADC0_CONFIG_MASK;
		adc1 |= 4 << MC13XXX_ADC1_CHAN1_SHIFT;
		अवरोध;

	शेष:
		mc13xxx_unlock(mc13xxx);
		वापस -EINVAL;
	पूर्ण

	adc1 |= ato << MC13783_ADC1_ATO_SHIFT;
	अगर (atox)
		adc1 |= MC13783_ADC1_ATOX;

	dev_dbg(mc13xxx->dev, "%s: request irq\n", __func__);
	mc13xxx_irq_request(mc13xxx, MC13XXX_IRQ_ADCDONE,
			mc13xxx_handler_adcकरोne, __func__, &adcकरोne_data);

	mc13xxx_reg_ग_लिखो(mc13xxx, MC13XXX_ADC0, adc0);
	mc13xxx_reg_ग_लिखो(mc13xxx, MC13XXX_ADC1, adc1);

	mc13xxx_unlock(mc13xxx);

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&adcकरोne_data.करोne, HZ);

	अगर (!ret)
		ret = -ETIMEDOUT;

	mc13xxx_lock(mc13xxx);

	mc13xxx_irq_मुक्त(mc13xxx, MC13XXX_IRQ_ADCDONE, &adcकरोne_data);

	अगर (ret > 0)
		क्रम (i = 0; i < 4; ++i) अणु
			ret = mc13xxx_reg_पढ़ो(mc13xxx,
					MC13XXX_ADC2, &sample[i]);
			अगर (ret)
				अवरोध;
		पूर्ण

	अगर (mode == MC13XXX_ADC_MODE_TS)
		/* restore TSMOD */
		mc13xxx_reg_ग_लिखो(mc13xxx, MC13XXX_ADC0, old_adc0);

	mc13xxx->adcflags &= ~MC13XXX_ADC_WORKING;
out:
	mc13xxx_unlock(mc13xxx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mc13xxx_adc_करो_conversion);

अटल पूर्णांक mc13xxx_add_subdevice_pdata(काष्ठा mc13xxx *mc13xxx,
		स्थिर अक्षर *क्रमmat, व्योम *pdata, माप_प्रकार pdata_size)
अणु
	अक्षर buf[30];
	स्थिर अक्षर *name = mc13xxx_get_chipname(mc13xxx);

	काष्ठा mfd_cell cell = अणु
		.platक्रमm_data = pdata,
		.pdata_size = pdata_size,
	पूर्ण;

	/* there is no asnम_लिखो in the kernel :-( */
	अगर (snम_लिखो(buf, माप(buf), क्रमmat, name) > माप(buf))
		वापस -E2BIG;

	cell.name = kmemdup(buf, म_माप(buf) + 1, GFP_KERNEL);
	अगर (!cell.name)
		वापस -ENOMEM;

	वापस mfd_add_devices(mc13xxx->dev, -1, &cell, 1, शून्य, 0,
			       regmap_irq_get_करोमुख्य(mc13xxx->irq_data));
पूर्ण

अटल पूर्णांक mc13xxx_add_subdevice(काष्ठा mc13xxx *mc13xxx, स्थिर अक्षर *क्रमmat)
अणु
	वापस mc13xxx_add_subdevice_pdata(mc13xxx, क्रमmat, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक mc13xxx_probe_flags_dt(काष्ठा mc13xxx *mc13xxx)
अणु
	काष्ठा device_node *np = mc13xxx->dev->of_node;

	अगर (!np)
		वापस -ENODEV;

	अगर (of_property_पढ़ो_bool(np, "fsl,mc13xxx-uses-adc"))
		mc13xxx->flags |= MC13XXX_USE_ADC;

	अगर (of_property_पढ़ो_bool(np, "fsl,mc13xxx-uses-codec"))
		mc13xxx->flags |= MC13XXX_USE_CODEC;

	अगर (of_property_पढ़ो_bool(np, "fsl,mc13xxx-uses-rtc"))
		mc13xxx->flags |= MC13XXX_USE_RTC;

	अगर (of_property_पढ़ो_bool(np, "fsl,mc13xxx-uses-touch"))
		mc13xxx->flags |= MC13XXX_USE_TOUCHSCREEN;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mc13xxx_probe_flags_dt(काष्ठा mc13xxx *mc13xxx)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

पूर्णांक mc13xxx_common_init(काष्ठा device *dev)
अणु
	काष्ठा mc13xxx_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा mc13xxx *mc13xxx = dev_get_drvdata(dev);
	u32 revision;
	पूर्णांक i, ret;

	mc13xxx->dev = dev;

	ret = mc13xxx_reg_पढ़ो(mc13xxx, MC13XXX_REVISION, &revision);
	अगर (ret)
		वापस ret;

	mc13xxx->variant->prपूर्णांक_revision(mc13xxx, revision);

	ret = mc13xxx_reg_rmw(mc13xxx, MC13XXX_PWRCTRL,
			MC13XXX_PWRCTRL_WसूचीESET, MC13XXX_PWRCTRL_WसूचीESET);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(mc13xxx->irqs); i++) अणु
		mc13xxx->irqs[i].reg_offset = i / MC13XXX_IRQ_PER_REG;
		mc13xxx->irqs[i].mask = BIT(i % MC13XXX_IRQ_PER_REG);
	पूर्ण

	mc13xxx->irq_chip.name = dev_name(dev);
	mc13xxx->irq_chip.status_base = MC13XXX_IRQSTAT0;
	mc13xxx->irq_chip.mask_base = MC13XXX_IRQMASK0;
	mc13xxx->irq_chip.ack_base = MC13XXX_IRQSTAT0;
	mc13xxx->irq_chip.irq_reg_stride = MC13XXX_IRQSTAT1 - MC13XXX_IRQSTAT0;
	mc13xxx->irq_chip.init_ack_masked = true;
	mc13xxx->irq_chip.use_ack = true;
	mc13xxx->irq_chip.num_regs = MC13XXX_IRQ_REG_CNT;
	mc13xxx->irq_chip.irqs = mc13xxx->irqs;
	mc13xxx->irq_chip.num_irqs = ARRAY_SIZE(mc13xxx->irqs);

	ret = regmap_add_irq_chip(mc13xxx->regmap, mc13xxx->irq, IRQF_ONESHOT,
				  0, &mc13xxx->irq_chip, &mc13xxx->irq_data);
	अगर (ret)
		वापस ret;

	mutex_init(&mc13xxx->lock);

	अगर (mc13xxx_probe_flags_dt(mc13xxx) < 0 && pdata)
		mc13xxx->flags = pdata->flags;

	अगर (pdata) अणु
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-regulator",
			&pdata->regulators, माप(pdata->regulators));
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-led",
				pdata->leds, माप(*pdata->leds));
		mc13xxx_add_subdevice_pdata(mc13xxx, "%s-pwrbutton",
				pdata->buttons, माप(*pdata->buttons));
		अगर (mc13xxx->flags & MC13XXX_USE_CODEC)
			mc13xxx_add_subdevice_pdata(mc13xxx, "%s-codec",
				pdata->codec, माप(*pdata->codec));
		अगर (mc13xxx->flags & MC13XXX_USE_TOUCHSCREEN)
			mc13xxx_add_subdevice_pdata(mc13xxx, "%s-ts",
				&pdata->touch, माप(pdata->touch));
	पूर्ण अन्यथा अणु
		mc13xxx_add_subdevice(mc13xxx, "%s-regulator");
		mc13xxx_add_subdevice(mc13xxx, "%s-led");
		mc13xxx_add_subdevice(mc13xxx, "%s-pwrbutton");
		अगर (mc13xxx->flags & MC13XXX_USE_CODEC)
			mc13xxx_add_subdevice(mc13xxx, "%s-codec");
		अगर (mc13xxx->flags & MC13XXX_USE_TOUCHSCREEN)
			mc13xxx_add_subdevice(mc13xxx, "%s-ts");
	पूर्ण

	अगर (mc13xxx->flags & MC13XXX_USE_ADC)
		mc13xxx_add_subdevice(mc13xxx, "%s-adc");

	अगर (mc13xxx->flags & MC13XXX_USE_RTC)
		mc13xxx_add_subdevice(mc13xxx, "%s-rtc");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mc13xxx_common_init);

पूर्णांक mc13xxx_common_निकास(काष्ठा device *dev)
अणु
	काष्ठा mc13xxx *mc13xxx = dev_get_drvdata(dev);

	mfd_हटाओ_devices(dev);
	regmap_del_irq_chip(mc13xxx->irq, mc13xxx->irq_data);
	mutex_destroy(&mc13xxx->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mc13xxx_common_निकास);

MODULE_DESCRIPTION("Core driver for Freescale MC13XXX PMIC");
MODULE_AUTHOR("Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>");
MODULE_LICENSE("GPL v2");
