<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Input driver क्रम PCAP events:
 *   * Power key
 *   * Headphone button
 *
 *  Copyright (c) 2008,2009 Ilya Petrov <ilya.muromec@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/ezx-pcap.h>
#समावेश <linux/slab.h>

काष्ठा pcap_keys अणु
	काष्ठा pcap_chip *pcap;
	काष्ठा input_dev *input;
पूर्ण;

/* PCAP2 पूर्णांकerrupts us on keypress */
अटल irqवापस_t pcap_keys_handler(पूर्णांक irq, व्योम *_pcap_keys)
अणु
	काष्ठा pcap_keys *pcap_keys = _pcap_keys;
	पूर्णांक pirq = irq_to_pcap(pcap_keys->pcap, irq);
	u32 pstat;

	ezx_pcap_पढ़ो(pcap_keys->pcap, PCAP_REG_PSTAT, &pstat);
	pstat &= 1 << pirq;

	चयन (pirq) अणु
	हाल PCAP_IRQ_ONOFF:
		input_report_key(pcap_keys->input, KEY_POWER, !pstat);
		अवरोध;
	हाल PCAP_IRQ_MIC:
		input_report_key(pcap_keys->input, KEY_HP, !pstat);
		अवरोध;
	पूर्ण

	input_sync(pcap_keys->input);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pcap_keys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err = -ENOMEM;
	काष्ठा pcap_keys *pcap_keys;
	काष्ठा input_dev *input_dev;

	pcap_keys = kदो_स्मृति(माप(काष्ठा pcap_keys), GFP_KERNEL);
	अगर (!pcap_keys)
		वापस err;

	pcap_keys->pcap = dev_get_drvdata(pdev->dev.parent);

	input_dev = input_allocate_device();
	अगर (!input_dev)
		जाओ fail;

	pcap_keys->input = input_dev;

	platक्रमm_set_drvdata(pdev, pcap_keys);
	input_dev->name = pdev->name;
	input_dev->phys = "pcap-keys/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(KEY_POWER, input_dev->keybit);
	__set_bit(KEY_HP, input_dev->keybit);

	err = input_रेजिस्टर_device(input_dev);
	अगर (err)
		जाओ fail_allocate;

	err = request_irq(pcap_to_irq(pcap_keys->pcap, PCAP_IRQ_ONOFF),
			pcap_keys_handler, 0, "Power key", pcap_keys);
	अगर (err)
		जाओ fail_रेजिस्टर;

	err = request_irq(pcap_to_irq(pcap_keys->pcap, PCAP_IRQ_MIC),
			pcap_keys_handler, 0, "Headphone button", pcap_keys);
	अगर (err)
		जाओ fail_pwrkey;

	वापस 0;

fail_pwrkey:
	मुक्त_irq(pcap_to_irq(pcap_keys->pcap, PCAP_IRQ_ONOFF), pcap_keys);
fail_रेजिस्टर:
	input_unरेजिस्टर_device(input_dev);
	जाओ fail;
fail_allocate:
	input_मुक्त_device(input_dev);
fail:
	kमुक्त(pcap_keys);
	वापस err;
पूर्ण

अटल पूर्णांक pcap_keys_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcap_keys *pcap_keys = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(pcap_to_irq(pcap_keys->pcap, PCAP_IRQ_ONOFF), pcap_keys);
	मुक्त_irq(pcap_to_irq(pcap_keys->pcap, PCAP_IRQ_MIC), pcap_keys);

	input_unरेजिस्टर_device(pcap_keys->input);
	kमुक्त(pcap_keys);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pcap_keys_device_driver = अणु
	.probe		= pcap_keys_probe,
	.हटाओ		= pcap_keys_हटाओ,
	.driver		= अणु
		.name	= "pcap-keys",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(pcap_keys_device_driver);

MODULE_DESCRIPTION("Motorola PCAP2 input events driver");
MODULE_AUTHOR("Ilya Petrov <ilya.muromec@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pcap_keys");
