<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 HiSilicon Limited, All Rights Reserved.
 * Author: Jun Ma <majun258@huawei.com>
 * Author: Yun Wu <wuyun.wu@huawei.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* Interrupt numbers per mbigen node supported */
#घोषणा IRQS_PER_MBIGEN_NODE		128

/* 64 irqs (Pin0-pin63) are reserved क्रम each mbigen chip */
#घोषणा RESERVED_IRQ_PER_MBIGEN_CHIP	64

/* The maximum IRQ pin number of mbigen chip(start from 0) */
#घोषणा MAXIMUM_IRQ_PIN_NUM		1407

/**
 * In mbigen vector रेजिस्टर
 * bit[21:12]:	event id value
 * bit[11:0]:	device id
 */
#घोषणा IRQ_EVENT_ID_SHIFT		12
#घोषणा IRQ_EVENT_ID_MASK		0x3ff

/* रेजिस्टर range of each mbigen node */
#घोषणा MBIGEN_NODE_OFFSET		0x1000

/* offset of vector रेजिस्टर in mbigen node */
#घोषणा REG_MBIGEN_VEC_OFFSET		0x200

/**
 * offset of clear रेजिस्टर in mbigen node
 * This रेजिस्टर is used to clear the status
 * of पूर्णांकerrupt
 */
#घोषणा REG_MBIGEN_CLEAR_OFFSET		0xa000

/**
 * offset of पूर्णांकerrupt type रेजिस्टर
 * This रेजिस्टर is used to configure पूर्णांकerrupt
 * trigger type
 */
#घोषणा REG_MBIGEN_TYPE_OFFSET		0x0

/**
 * काष्ठा mbigen_device - holds the inक्रमmation of mbigen device.
 *
 * @pdev:		poपूर्णांकer to the platक्रमm device काष्ठाure of mbigen chip.
 * @base:		mapped address of this mbigen chip.
 */
काष्ठा mbigen_device अणु
	काष्ठा platक्रमm_device	*pdev;
	व्योम __iomem		*base;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक get_mbigen_vec_reg(irq_hw_number_t hwirq)
अणु
	अचिन्हित पूर्णांक nid, pin;

	hwirq -= RESERVED_IRQ_PER_MBIGEN_CHIP;
	nid = hwirq / IRQS_PER_MBIGEN_NODE + 1;
	pin = hwirq % IRQS_PER_MBIGEN_NODE;

	वापस pin * 4 + nid * MBIGEN_NODE_OFFSET
			+ REG_MBIGEN_VEC_OFFSET;
पूर्ण

अटल अंतरभूत व्योम get_mbigen_type_reg(irq_hw_number_t hwirq,
					u32 *mask, u32 *addr)
अणु
	अचिन्हित पूर्णांक nid, irq_ofst, ofst;

	hwirq -= RESERVED_IRQ_PER_MBIGEN_CHIP;
	nid = hwirq / IRQS_PER_MBIGEN_NODE + 1;
	irq_ofst = hwirq % IRQS_PER_MBIGEN_NODE;

	*mask = 1 << (irq_ofst % 32);
	ofst = irq_ofst / 32 * 4;

	*addr = ofst + nid * MBIGEN_NODE_OFFSET
		+ REG_MBIGEN_TYPE_OFFSET;
पूर्ण

अटल अंतरभूत व्योम get_mbigen_clear_reg(irq_hw_number_t hwirq,
					u32 *mask, u32 *addr)
अणु
	अचिन्हित पूर्णांक ofst = (hwirq / 32) * 4;

	*mask = 1 << (hwirq % 32);
	*addr = ofst + REG_MBIGEN_CLEAR_OFFSET;
पूर्ण

अटल व्योम mbigen_eoi_irq(काष्ठा irq_data *data)
अणु
	व्योम __iomem *base = data->chip_data;
	u32 mask, addr;

	get_mbigen_clear_reg(data->hwirq, &mask, &addr);

	ग_लिखोl_relaxed(mask, base + addr);

	irq_chip_eoi_parent(data);
पूर्ण

अटल पूर्णांक mbigen_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	व्योम __iomem *base = data->chip_data;
	u32 mask, addr, val;

	अगर (type != IRQ_TYPE_LEVEL_HIGH && type != IRQ_TYPE_EDGE_RISING)
		वापस -EINVAL;

	get_mbigen_type_reg(data->hwirq, &mask, &addr);

	val = पढ़ोl_relaxed(base + addr);

	अगर (type == IRQ_TYPE_LEVEL_HIGH)
		val |= mask;
	अन्यथा
		val &= ~mask;

	ग_लिखोl_relaxed(val, base + addr);

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mbigen_irq_chip = अणु
	.name =			"mbigen-v2",
	.irq_mask =		irq_chip_mask_parent,
	.irq_unmask =		irq_chip_unmask_parent,
	.irq_eoi =		mbigen_eoi_irq,
	.irq_set_type =		mbigen_set_type,
	.irq_set_affinity =	irq_chip_set_affinity_parent,
पूर्ण;

अटल व्योम mbigen_ग_लिखो_msg(काष्ठा msi_desc *desc, काष्ठा msi_msg *msg)
अणु
	काष्ठा irq_data *d = irq_get_irq_data(desc->irq);
	व्योम __iomem *base = d->chip_data;
	u32 val;

	अगर (!msg->address_lo && !msg->address_hi)
		वापस;
 
	base += get_mbigen_vec_reg(d->hwirq);
	val = पढ़ोl_relaxed(base);

	val &= ~(IRQ_EVENT_ID_MASK << IRQ_EVENT_ID_SHIFT);
	val |= (msg->data << IRQ_EVENT_ID_SHIFT);

	/* The address of करोorbell is encoded in mbigen रेजिस्टर by शेष
	 * So,we करोn't need to program the करोorbell address at here
	 */
	ग_लिखोl_relaxed(val, base);
पूर्ण

अटल पूर्णांक mbigen_करोमुख्य_translate(काष्ठा irq_करोमुख्य *d,
				    काष्ठा irq_fwspec *fwspec,
				    अचिन्हित दीर्घ *hwirq,
				    अचिन्हित पूर्णांक *type)
अणु
	अगर (is_of_node(fwspec->fwnode) || is_acpi_device_node(fwspec->fwnode)) अणु
		अगर (fwspec->param_count != 2)
			वापस -EINVAL;

		अगर ((fwspec->param[0] > MAXIMUM_IRQ_PIN_NUM) ||
			(fwspec->param[0] < RESERVED_IRQ_PER_MBIGEN_CHIP))
			वापस -EINVAL;
		अन्यथा
			*hwirq = fwspec->param[0];

		/* If there is no valid irq type, just use the शेष type */
		अगर ((fwspec->param[1] == IRQ_TYPE_EDGE_RISING) ||
			(fwspec->param[1] == IRQ_TYPE_LEVEL_HIGH))
			*type = fwspec->param[1];
		अन्यथा
			वापस -EINVAL;

		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mbigen_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
					अचिन्हित पूर्णांक virq,
					अचिन्हित पूर्णांक nr_irqs,
					व्योम *args)
अणु
	काष्ठा irq_fwspec *fwspec = args;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	काष्ठा mbigen_device *mgn_chip;
	पूर्णांक i, err;

	err = mbigen_करोमुख्य_translate(करोमुख्य, fwspec, &hwirq, &type);
	अगर (err)
		वापस err;

	err = platक्रमm_msi_करोमुख्य_alloc(करोमुख्य, virq, nr_irqs);
	अगर (err)
		वापस err;

	mgn_chip = platक्रमm_msi_get_host_data(करोमुख्य);

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_hwirq_and_chip(करोमुख्य, virq + i, hwirq + i,
				      &mbigen_irq_chip, mgn_chip->base);

	वापस 0;
पूर्ण

अटल व्योम mbigen_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs)
अणु
	platक्रमm_msi_करोमुख्य_मुक्त(करोमुख्य, virq, nr_irqs);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops mbigen_करोमुख्य_ops = अणु
	.translate	= mbigen_करोमुख्य_translate,
	.alloc		= mbigen_irq_करोमुख्य_alloc,
	.मुक्त		= mbigen_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल पूर्णांक mbigen_of_create_करोमुख्य(काष्ठा platक्रमm_device *pdev,
				   काष्ठा mbigen_device *mgn_chip)
अणु
	काष्ठा device *parent;
	काष्ठा platक्रमm_device *child;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा device_node *np;
	u32 num_pins;

	क्रम_each_child_of_node(pdev->dev.of_node, np) अणु
		अगर (!of_property_पढ़ो_bool(np, "interrupt-controller"))
			जारी;

		parent = platक्रमm_bus_type.dev_root;
		child = of_platक्रमm_device_create(np, शून्य, parent);
		अगर (!child) अणु
			of_node_put(np);
			वापस -ENOMEM;
		पूर्ण

		अगर (of_property_पढ़ो_u32(child->dev.of_node, "num-pins",
					 &num_pins) < 0) अणु
			dev_err(&pdev->dev, "No num-pins property\n");
			of_node_put(np);
			वापस -EINVAL;
		पूर्ण

		करोमुख्य = platक्रमm_msi_create_device_करोमुख्य(&child->dev, num_pins,
							   mbigen_ग_लिखो_msg,
							   &mbigen_करोमुख्य_ops,
							   mgn_chip);
		अगर (!करोमुख्य) अणु
			of_node_put(np);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक mbigen_acpi_create_करोमुख्य(काष्ठा platक्रमm_device *pdev,
				     काष्ठा mbigen_device *mgn_chip)
अणु
	काष्ठा irq_करोमुख्य *करोमुख्य;
	u32 num_pins = 0;
	पूर्णांक ret;

	/*
	 * "num-pins" is the total number of पूर्णांकerrupt pins implemented in
	 * this mbigen instance, and mbigen is an पूर्णांकerrupt controller
	 * connected to ITS  converting wired पूर्णांकerrupts पूर्णांकo MSI, so we
	 * use "num-pins" to alloc MSI vectors which are needed by client
	 * devices connected to it.
	 *
	 * Here is the DSDT device node used क्रम mbigen in firmware:
	 *	Device(MBI0) अणु
	 *		Name(_HID, "HISI0152")
	 *		Name(_UID, Zero)
	 *		Name(_CRS, ResourceTemplate() अणु
	 *			Memory32Fixed(ReadWrite, 0xa0080000, 0x10000)
	 *		पूर्ण)
	 *
	 *		Name(_DSD, Package () अणु
	 *			ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
	 *			Package () अणु
	 *				Package () अणु"num-pins", 378पूर्ण
	 *			पूर्ण
	 *		पूर्ण)
	 *	पूर्ण
	 */
	ret = device_property_पढ़ो_u32(&pdev->dev, "num-pins", &num_pins);
	अगर (ret || num_pins == 0)
		वापस -EINVAL;

	करोमुख्य = platक्रमm_msi_create_device_करोमुख्य(&pdev->dev, num_pins,
						   mbigen_ग_लिखो_msg,
						   &mbigen_करोमुख्य_ops,
						   mgn_chip);
	अगर (!करोमुख्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mbigen_acpi_create_करोमुख्य(काष्ठा platक्रमm_device *pdev,
					    काष्ठा mbigen_device *mgn_chip)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mbigen_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mbigen_device *mgn_chip;
	काष्ठा resource *res;
	पूर्णांक err;

	mgn_chip = devm_kzalloc(&pdev->dev, माप(*mgn_chip), GFP_KERNEL);
	अगर (!mgn_chip)
		वापस -ENOMEM;

	mgn_chip->pdev = pdev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	mgn_chip->base = devm_ioremap(&pdev->dev, res->start,
				      resource_size(res));
	अगर (!mgn_chip->base) अणु
		dev_err(&pdev->dev, "failed to ioremap %pR\n", res);
		वापस -ENOMEM;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node)
		err = mbigen_of_create_करोमुख्य(pdev, mgn_chip);
	अन्यथा अगर (ACPI_COMPANION(&pdev->dev))
		err = mbigen_acpi_create_करोमुख्य(pdev, mgn_chip);
	अन्यथा
		err = -EINVAL;

	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to create mbi-gen irqdomain\n");
		वापस err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mgn_chip);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mbigen_of_match[] = अणु
	अणु .compatible = "hisilicon,mbigen-v2" पूर्ण,
	अणु /* END */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mbigen_of_match);

अटल स्थिर काष्ठा acpi_device_id mbigen_acpi_match[] = अणु
	अणु "HISI0152", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mbigen_acpi_match);

अटल काष्ठा platक्रमm_driver mbigen_platक्रमm_driver = अणु
	.driver = अणु
		.name		= "Hisilicon MBIGEN-V2",
		.of_match_table	= mbigen_of_match,
		.acpi_match_table = ACPI_PTR(mbigen_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe			= mbigen_device_probe,
पूर्ण;

module_platक्रमm_driver(mbigen_platक्रमm_driver);

MODULE_AUTHOR("Jun Ma <majun258@huawei.com>");
MODULE_AUTHOR("Yun Wu <wuyun.wu@huawei.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HiSilicon MBI Generator driver");
