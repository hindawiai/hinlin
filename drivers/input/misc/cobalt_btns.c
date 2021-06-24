<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Cobalt button पूर्णांकerface driver.
 *
 *  Copyright (C) 2007-2008  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/input.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा BUTTONS_POLL_INTERVAL	30	/* msec */
#घोषणा BUTTONS_COUNT_THRESHOLD	3
#घोषणा BUTTONS_STATUS_MASK	0xfe000000

अटल स्थिर अचिन्हित लघु cobalt_map[] = अणु
	KEY_RESERVED,
	KEY_RESTART,
	KEY_LEFT,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_ENTER,
	KEY_SELECT
पूर्ण;

काष्ठा buttons_dev अणु
	अचिन्हित लघु keymap[ARRAY_SIZE(cobalt_map)];
	पूर्णांक count[ARRAY_SIZE(cobalt_map)];
	व्योम __iomem *reg;
पूर्ण;

अटल व्योम handle_buttons(काष्ठा input_dev *input)
अणु
	काष्ठा buttons_dev *bdev = input_get_drvdata(input);
	uपूर्णांक32_t status;
	पूर्णांक i;

	status = ~पढ़ोl(bdev->reg) >> 24;

	क्रम (i = 0; i < ARRAY_SIZE(bdev->keymap); i++) अणु
		अगर (status & (1U << i)) अणु
			अगर (++bdev->count[i] == BUTTONS_COUNT_THRESHOLD) अणु
				input_event(input, EV_MSC, MSC_SCAN, i);
				input_report_key(input, bdev->keymap[i], 1);
				input_sync(input);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bdev->count[i] >= BUTTONS_COUNT_THRESHOLD) अणु
				input_event(input, EV_MSC, MSC_SCAN, i);
				input_report_key(input, bdev->keymap[i], 0);
				input_sync(input);
			पूर्ण
			bdev->count[i] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cobalt_buttons_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा buttons_dev *bdev;
	काष्ठा input_dev *input;
	काष्ठा resource *res;
	पूर्णांक error, i;

	bdev = devm_kzalloc(&pdev->dev, माप(*bdev), GFP_KERNEL);
	अगर (!bdev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EBUSY;

	bdev->reg = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!bdev->reg)
		वापस -ENOMEM;

	स_नकल(bdev->keymap, cobalt_map, माप(bdev->keymap));

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	input_set_drvdata(input, bdev);

	input->name = "Cobalt buttons";
	input->phys = "cobalt/input0";
	input->id.bustype = BUS_HOST;

	input->keycode = bdev->keymap;
	input->keycodemax = ARRAY_SIZE(bdev->keymap);
	input->keycodesize = माप(अचिन्हित लघु);

	input_set_capability(input, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input->evbit);
	क्रम (i = 0; i < ARRAY_SIZE(cobalt_map); i++)
		__set_bit(bdev->keymap[i], input->keybit);
	__clear_bit(KEY_RESERVED, input->keybit);


	error = input_setup_polling(input, handle_buttons);
	अगर (error)
		वापस error;

	input_set_poll_पूर्णांकerval(input, BUTTONS_POLL_INTERVAL);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

MODULE_AUTHOR("Yoichi Yuasa <yuasa@linux-mips.org>");
MODULE_DESCRIPTION("Cobalt button interface driver");
MODULE_LICENSE("GPL");
/* work with hotplug and coldplug */
MODULE_ALIAS("platform:Cobalt buttons");

अटल काष्ठा platक्रमm_driver cobalt_buttons_driver = अणु
	.probe	= cobalt_buttons_probe,
	.driver	= अणु
		.name	= "Cobalt buttons",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cobalt_buttons_driver);
