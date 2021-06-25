<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device driver क्रम regulators in HISI PMIC IC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (c) 2011 Hisilicon.
 * Copyright (c) 2020-2021 Huawei Technologies Co., Ltd
 */

#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/hi6421-spmi-pmic.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spmi.h>

क्रमागत hi6421_spmi_pmic_irq_list अणु
	OTMP = 0,
	VBUS_CONNECT,
	VBUS_DISCONNECT,
	ALARMON_R,
	HOLD_6S,
	HOLD_1S,
	POWERKEY_UP,
	POWERKEY_DOWN,
	OCP_SCP_R,
	COUL_R,
	SIM0_HPD_R,
	SIM0_HPD_F,
	SIM1_HPD_R,
	SIM1_HPD_F,
	PMIC_IRQ_LIST_MAX,
पूर्ण;

#घोषणा HISI_IRQ_ARRAY			2
#घोषणा HISI_IRQ_NUM			(HISI_IRQ_ARRAY * 8)

#घोषणा HISI_IRQ_KEY_NUM		0

#घोषणा HISI_BITS			8
#घोषणा HISI_IRQ_KEY_VALUE		(BIT(POWERKEY_DOWN) | BIT(POWERKEY_UP))
#घोषणा HISI_MASK			GENMASK(HISI_BITS - 1, 0)

/*
 * The IRQs are mapped as:
 *
 *	======================  =============   ============	=====
 *	IRQ			MASK REGISTER	IRQ REGISTER	BIT
 *	======================  =============   ============	=====
 *	OTMP			0x0202		0x212		bit 0
 *	VBUS_CONNECT		0x0202		0x212		bit 1
 *	VBUS_DISCONNECT		0x0202		0x212		bit 2
 *	ALARMON_R		0x0202		0x212		bit 3
 *	HOLD_6S			0x0202		0x212		bit 4
 *	HOLD_1S			0x0202		0x212		bit 5
 *	POWERKEY_UP		0x0202		0x212		bit 6
 *	POWERKEY_DOWN		0x0202		0x212		bit 7
 *
 *	OCP_SCP_R		0x0203		0x213		bit 0
 *	COUL_R			0x0203		0x213		bit 1
 *	SIM0_HPD_R		0x0203		0x213		bit 2
 *	SIM0_HPD_F		0x0203		0x213		bit 3
 *	SIM1_HPD_R		0x0203		0x213		bit 4
 *	SIM1_HPD_F		0x0203		0x213		bit 5
 *	======================  =============   ============	=====
 */
#घोषणा SOC_PMIC_IRQ_MASK_0_ADDR	0x0202
#घोषणा SOC_PMIC_IRQ0_ADDR		0x0212

#घोषणा IRQ_MASK_REGISTER(irq_data)	(SOC_PMIC_IRQ_MASK_0_ADDR + \
					 (irqd_to_hwirq(irq_data) >> 3))
#घोषणा IRQ_MASK_BIT(irq_data)		BIT(irqd_to_hwirq(irq_data) & 0x07)

अटल स्थिर काष्ठा mfd_cell hi6421v600_devs[] = अणु
	अणु .name = "hi6421v600-regulator", पूर्ण,
पूर्ण;

अटल irqवापस_t hi6421_spmi_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा hi6421_spmi_pmic *ddata = (काष्ठा hi6421_spmi_pmic *)priv;
	अचिन्हित दीर्घ pending;
	अचिन्हित पूर्णांक in;
	पूर्णांक i, offset;

	क्रम (i = 0; i < HISI_IRQ_ARRAY; i++) अणु
		regmap_पढ़ो(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i, &in);
		pending = HISI_MASK & in;
		regmap_ग_लिखो(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i, pending);

		अगर (i == HISI_IRQ_KEY_NUM &&
		    (pending & HISI_IRQ_KEY_VALUE) == HISI_IRQ_KEY_VALUE) अणु
			generic_handle_irq(ddata->irqs[POWERKEY_DOWN]);
			generic_handle_irq(ddata->irqs[POWERKEY_UP]);
			pending &= (~HISI_IRQ_KEY_VALUE);
		पूर्ण

		अगर (!pending)
			जारी;

		क्रम_each_set_bit(offset, &pending, HISI_BITS)
			generic_handle_irq(ddata->irqs[offset + i * HISI_BITS]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hi6421_spmi_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा hi6421_spmi_pmic *ddata = irq_data_get_irq_chip_data(d);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक data;
	u32 offset;

	offset = IRQ_MASK_REGISTER(d);

	spin_lock_irqsave(&ddata->lock, flags);

	regmap_पढ़ो(ddata->regmap, offset, &data);
	data |= IRQ_MASK_BIT(d);
	regmap_ग_लिखो(ddata->regmap, offset, data);

	spin_unlock_irqrestore(&ddata->lock, flags);
पूर्ण

अटल व्योम hi6421_spmi_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा hi6421_spmi_pmic *ddata = irq_data_get_irq_chip_data(d);
	u32 data, offset;
	अचिन्हित दीर्घ flags;

	offset = (irqd_to_hwirq(d) >> 3);
	offset += SOC_PMIC_IRQ_MASK_0_ADDR;

	spin_lock_irqsave(&ddata->lock, flags);

	regmap_पढ़ो(ddata->regmap, offset, &data);
	data &= ~(1 << (irqd_to_hwirq(d) & 0x07));
	regmap_ग_लिखो(ddata->regmap, offset, data);

	spin_unlock_irqrestore(&ddata->lock, flags);
पूर्ण

अटल काष्ठा irq_chip hi6421_spmi_pmu_irqchip = अणु
	.name		= "hisi-irq",
	.irq_mask	= hi6421_spmi_irq_mask,
	.irq_unmask	= hi6421_spmi_irq_unmask,
	.irq_disable	= hi6421_spmi_irq_mask,
	.irq_enable	= hi6421_spmi_irq_unmask,
पूर्ण;

अटल पूर्णांक hi6421_spmi_irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक virq,
			       irq_hw_number_t hw)
अणु
	काष्ठा hi6421_spmi_pmic *ddata = d->host_data;

	irq_set_chip_and_handler_name(virq, &hi6421_spmi_pmu_irqchip,
				      handle_simple_irq, "hisi");
	irq_set_chip_data(virq, ddata);
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops hi6421_spmi_करोमुख्य_ops = अणु
	.map	= hi6421_spmi_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल व्योम hi6421_spmi_pmic_irq_init(काष्ठा hi6421_spmi_pmic *ddata)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक pending;

	क्रम (i = 0; i < HISI_IRQ_ARRAY; i++)
		regmap_ग_लिखो(ddata->regmap, SOC_PMIC_IRQ_MASK_0_ADDR + i,
			     HISI_MASK);

	क्रम (i = 0; i < HISI_IRQ_ARRAY; i++) अणु
		regmap_पढ़ो(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i, &pending);
		regmap_ग_लिखो(ddata->regmap, SOC_PMIC_IRQ0_ADDR + i,
			     HISI_MASK);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config regmap_config = अणु
	.reg_bits		= 16,
	.val_bits		= HISI_BITS,
	.max_रेजिस्टर		= 0xffff,
	.fast_io		= true
पूर्ण;

अटल पूर्णांक hi6421_spmi_pmic_probe(काष्ठा spmi_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा hi6421_spmi_pmic *ddata;
	अचिन्हित पूर्णांक virq;
	पूर्णांक ret, i;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->regmap = devm_regmap_init_spmi_ext(pdev, &regmap_config);
	अगर (IS_ERR(ddata->regmap))
		वापस PTR_ERR(ddata->regmap);

	spin_lock_init(&ddata->lock);

	ddata->dev = dev;

	ddata->gpio = of_get_gpio(np, 0);
	अगर (ddata->gpio < 0)
		वापस ddata->gpio;

	अगर (!gpio_is_valid(ddata->gpio))
		वापस -EINVAL;

	ret = devm_gpio_request_one(dev, ddata->gpio, GPIOF_IN, "pmic");
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request gpio%d\n", ddata->gpio);
		वापस ret;
	पूर्ण

	ddata->irq = gpio_to_irq(ddata->gpio);

	hi6421_spmi_pmic_irq_init(ddata);

	ddata->irqs = devm_kzalloc(dev, HISI_IRQ_NUM * माप(पूर्णांक), GFP_KERNEL);
	अगर (!ddata->irqs)
		वापस -ENOMEM;

	ddata->करोमुख्य = irq_करोमुख्य_add_simple(np, HISI_IRQ_NUM, 0,
					      &hi6421_spmi_करोमुख्य_ops, ddata);
	अगर (!ddata->करोमुख्य) अणु
		dev_err(dev, "Failed to create IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < HISI_IRQ_NUM; i++) अणु
		virq = irq_create_mapping(ddata->करोमुख्य, i);
		अगर (!virq) अणु
			dev_err(dev, "Failed to map H/W IRQ\n");
			वापस -ENOSPC;
		पूर्ण
		ddata->irqs[i] = virq;
	पूर्ण

	ret = request_thपढ़ोed_irq(ddata->irq, hi6421_spmi_irq_handler, शून्य,
				   IRQF_TRIGGER_LOW | IRQF_SHARED | IRQF_NO_SUSPEND,
				   "pmic", ddata);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to start IRQ handling thread: error %d\n",
			ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&pdev->dev, ddata);

	ret = devm_mfd_add_devices(&pdev->dev, PLATFORM_DEVID_NONE,
				   hi6421v600_devs, ARRAY_SIZE(hi6421v600_devs),
				   शून्य, 0, शून्य);
	अगर (ret < 0)
		dev_err(dev, "Failed to add child devices: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम hi6421_spmi_pmic_हटाओ(काष्ठा spmi_device *pdev)
अणु
	काष्ठा hi6421_spmi_pmic *ddata = dev_get_drvdata(&pdev->dev);

	मुक्त_irq(ddata->irq, ddata);
पूर्ण

अटल स्थिर काष्ठा of_device_id pmic_spmi_id_table[] = अणु
	अणु .compatible = "hisilicon,hi6421-spmi" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pmic_spmi_id_table);

अटल काष्ठा spmi_driver hi6421_spmi_pmic_driver = अणु
	.driver = अणु
		.name	= "hi6421-spmi-pmic",
		.of_match_table = pmic_spmi_id_table,
	पूर्ण,
	.probe	= hi6421_spmi_pmic_probe,
	.हटाओ	= hi6421_spmi_pmic_हटाओ,
पूर्ण;
module_spmi_driver(hi6421_spmi_pmic_driver);

MODULE_DESCRIPTION("HiSilicon Hi6421v600 SPMI PMIC driver");
MODULE_LICENSE("GPL v2");
