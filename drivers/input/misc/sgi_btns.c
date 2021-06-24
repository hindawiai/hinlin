<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  SGI Volume Button पूर्णांकerface driver
 *
 *  Copyright (C) 2008  Thomas Bogenकरोerfer <tsbogend@alpha.franken.de>
 */
#समावेश <linux/input.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#अगर_घोषित CONFIG_SGI_IP22
#समावेश <यंत्र/sgi/ioc.h>

अटल अंतरभूत u8 button_status(व्योम)
अणु
	u8 status;

	status = पढ़ोb(&sgioc->panel) ^ 0xa0;
	वापस ((status & 0x80) >> 6) | ((status & 0x20) >> 5);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SGI_IP32
#समावेश <यंत्र/ip32/mace.h>

अटल अंतरभूत u8 button_status(व्योम)
अणु
	u64 status;

	status = पढ़ोq(&mace->perअगर.audio.control);
	ग_लिखोq(status & ~(3U << 23), &mace->perअगर.audio.control);

	वापस (status >> 23) & 3;
पूर्ण
#पूर्ण_अगर

#घोषणा BUTTONS_POLL_INTERVAL	30	/* msec */
#घोषणा BUTTONS_COUNT_THRESHOLD	3

अटल स्थिर अचिन्हित लघु sgi_map[] = अणु
	KEY_VOLUMEDOWN,
	KEY_VOLUMEUP
पूर्ण;

काष्ठा buttons_dev अणु
	अचिन्हित लघु keymap[ARRAY_SIZE(sgi_map)];
	पूर्णांक count[ARRAY_SIZE(sgi_map)];
पूर्ण;

अटल व्योम handle_buttons(काष्ठा input_dev *input)
अणु
	काष्ठा buttons_dev *bdev = input_get_drvdata(input);
	u8 status;
	पूर्णांक i;

	status = button_status();

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

अटल पूर्णांक sgi_buttons_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा buttons_dev *bdev;
	काष्ठा input_dev *input;
	पूर्णांक error, i;

	bdev = devm_kzalloc(&pdev->dev, माप(*bdev), GFP_KERNEL);
	अगर (!bdev)
		वापस -ENOMEM;

	input = devm_input_allocate_device(&pdev->dev);
	अगर (!input)
		वापस -ENOMEM;

	स_नकल(bdev->keymap, sgi_map, माप(bdev->keymap));

	input_set_drvdata(input, bdev);

	input->name = "SGI buttons";
	input->phys = "sgi/input0";
	input->id.bustype = BUS_HOST;

	input->keycode = bdev->keymap;
	input->keycodemax = ARRAY_SIZE(bdev->keymap);
	input->keycodesize = माप(अचिन्हित लघु);

	input_set_capability(input, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input->evbit);
	क्रम (i = 0; i < ARRAY_SIZE(sgi_map); i++)
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

अटल काष्ठा platक्रमm_driver sgi_buttons_driver = अणु
	.probe	= sgi_buttons_probe,
	.driver	= अणु
		.name	= "sgibtns",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sgi_buttons_driver);

MODULE_LICENSE("GPL");
