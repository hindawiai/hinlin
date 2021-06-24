<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Google, Inc.
 * Copyright (C) 2012 Intel, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/acpi.h>

क्रमागत अणु
	REG_READ        = 0x00,
	REG_SET_PAGE    = 0x00,
	REG_LEN         = 0x04,
	REG_DATA        = 0x08,

	PAGE_NAME       = 0x00000,
	PAGE_EVBITS     = 0x10000,
	PAGE_ABSDATA    = 0x20000 | EV_ABS,
पूर्ण;

काष्ठा event_dev अणु
	काष्ठा input_dev *input;
	पूर्णांक irq;
	व्योम __iomem *addr;
	अक्षर name[];
पूर्ण;

अटल irqवापस_t events_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा event_dev *edev = dev_id;
	अचिन्हित पूर्णांक type, code, value;

	type = __raw_पढ़ोl(edev->addr + REG_READ);
	code = __raw_पढ़ोl(edev->addr + REG_READ);
	value = __raw_पढ़ोl(edev->addr + REG_READ);

	input_event(edev->input, type, code, value);
	input_sync(edev->input);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम events_import_bits(काष्ठा event_dev *edev,
			अचिन्हित दीर्घ bits[], अचिन्हित पूर्णांक type, माप_प्रकार count)
अणु
	व्योम __iomem *addr = edev->addr;
	पूर्णांक i, j;
	माप_प्रकार size;
	uपूर्णांक8_t val;

	__raw_ग_लिखोl(PAGE_EVBITS | type, addr + REG_SET_PAGE);

	size = __raw_पढ़ोl(addr + REG_LEN) * 8;
	अगर (size < count)
		count = size;

	addr += REG_DATA;
	क्रम (i = 0; i < count; i += 8) अणु
		val = __raw_पढ़ोb(addr++);
		क्रम (j = 0; j < 8; j++)
			अगर (val & 1 << j)
				set_bit(i + j, bits);
	पूर्ण
पूर्ण

अटल व्योम events_import_असल_params(काष्ठा event_dev *edev)
अणु
	काष्ठा input_dev *input_dev = edev->input;
	व्योम __iomem *addr = edev->addr;
	u32 val[4];
	पूर्णांक count;
	पूर्णांक i, j;

	__raw_ग_लिखोl(PAGE_ABSDATA, addr + REG_SET_PAGE);

	count = __raw_पढ़ोl(addr + REG_LEN) / माप(val);
	अगर (count > ABS_MAX)
		count = ABS_MAX;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!test_bit(i, input_dev->असलbit))
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(val); j++) अणु
			पूर्णांक offset = (i * ARRAY_SIZE(val) + j) * माप(u32);

			val[j] = __raw_पढ़ोl(edev->addr + REG_DATA + offset);
		पूर्ण

		input_set_असल_params(input_dev, i,
				     val[0], val[1], val[2], val[3]);
	पूर्ण
पूर्ण

अटल पूर्णांक events_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input_dev;
	काष्ठा event_dev *edev;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक keymapnamelen;
	व्योम __iomem *addr;
	पूर्णांक irq;
	पूर्णांक i;
	पूर्णांक error;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EINVAL;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	addr = devm_ioremap(&pdev->dev, res->start, 4096);
	अगर (!addr)
		वापस -ENOMEM;

	__raw_ग_लिखोl(PAGE_NAME, addr + REG_SET_PAGE);
	keymapnamelen = __raw_पढ़ोl(addr + REG_LEN);

	edev = devm_kzalloc(&pdev->dev,
			    माप(काष्ठा event_dev) + keymapnamelen + 1,
			    GFP_KERNEL);
	अगर (!edev)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	edev->input = input_dev;
	edev->addr = addr;
	edev->irq = irq;

	क्रम (i = 0; i < keymapnamelen; i++)
		edev->name[i] = __raw_पढ़ोb(edev->addr + REG_DATA + i);

	pr_debug("%s: keymap=%s\n", __func__, edev->name);

	input_dev->name = edev->name;
	input_dev->id.bustype = BUS_HOST;

	events_import_bits(edev, input_dev->evbit, EV_SYN, EV_MAX);
	events_import_bits(edev, input_dev->keybit, EV_KEY, KEY_MAX);
	events_import_bits(edev, input_dev->relbit, EV_REL, REL_MAX);
	events_import_bits(edev, input_dev->असलbit, EV_ABS, ABS_MAX);
	events_import_bits(edev, input_dev->mscbit, EV_MSC, MSC_MAX);
	events_import_bits(edev, input_dev->ledbit, EV_LED, LED_MAX);
	events_import_bits(edev, input_dev->sndbit, EV_SND, SND_MAX);
	events_import_bits(edev, input_dev->ffbit, EV_FF, FF_MAX);
	events_import_bits(edev, input_dev->swbit, EV_SW, SW_MAX);

	events_import_असल_params(edev);

	error = devm_request_irq(&pdev->dev, edev->irq, events_पूर्णांकerrupt, 0,
				 "goldfish-events-keypad", edev);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input_dev);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id goldfish_events_of_match[] = अणु
	अणु .compatible = "google,goldfish-events-keypad", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, goldfish_events_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id goldfish_events_acpi_match[] = अणु
	अणु "GFSH0002", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, goldfish_events_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver events_driver = अणु
	.probe	= events_probe,
	.driver	= अणु
		.name	= "goldfish_events",
		.of_match_table = goldfish_events_of_match,
		.acpi_match_table = ACPI_PTR(goldfish_events_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(events_driver);

MODULE_AUTHOR("Brian Swetland");
MODULE_DESCRIPTION("Goldfish Event Device");
MODULE_LICENSE("GPL");
