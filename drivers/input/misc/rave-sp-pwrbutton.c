<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Power Button driver क्रम RAVE SP
//
// Copyright (C) 2017 Zodiac Inflight Innovations
//
//

#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/rave-sp.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा RAVE_SP_EVNT_BUTTON_PRESS	(RAVE_SP_EVNT_BASE + 0x00)

काष्ठा rave_sp_घातer_button अणु
	काष्ठा input_dev *idev;
	काष्ठा notअगरier_block nb;
पूर्ण;

अटल पूर्णांक rave_sp_घातer_button_event(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा rave_sp_घातer_button *pb =
		container_of(nb, काष्ठा rave_sp_घातer_button, nb);
	स्थिर u8 event = rave_sp_action_unpack_event(action);
	स्थिर u8 value = rave_sp_action_unpack_value(action);
	काष्ठा input_dev *idev = pb->idev;

	अगर (event == RAVE_SP_EVNT_BUTTON_PRESS) अणु
		input_report_key(idev, KEY_POWER, value);
		input_sync(idev);

		वापस NOTIFY_STOP;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक rave_sp_pwrbutton_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rave_sp_घातer_button *pb;
	काष्ठा input_dev *idev;
	पूर्णांक error;

	pb = devm_kzalloc(dev, माप(*pb), GFP_KERNEL);
	अगर (!pb)
		वापस -ENOMEM;

	idev = devm_input_allocate_device(dev);
	अगर (!idev)
		वापस -ENOMEM;

	idev->name = pdev->name;

	input_set_capability(idev, EV_KEY, KEY_POWER);

	error = input_रेजिस्टर_device(idev);
	अगर (error)
		वापस error;

	pb->idev = idev;
	pb->nb.notअगरier_call = rave_sp_घातer_button_event;
	pb->nb.priority = 128;

	error = devm_rave_sp_रेजिस्टर_event_notअगरier(dev, &pb->nb);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rave_sp_pwrbutton_of_match[] = अणु
	अणु .compatible = "zii,rave-sp-pwrbutton" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver rave_sp_pwrbutton_driver = अणु
	.probe = rave_sp_pwrbutton_probe,
	.driver	= अणु
		.name = KBUILD_MODNAME,
		.of_match_table = rave_sp_pwrbutton_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rave_sp_pwrbutton_driver);

MODULE_DEVICE_TABLE(of, rave_sp_pwrbutton_of_match);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrey Vostrikov <andrey.vostrikov@cogentembedded.com>");
MODULE_AUTHOR("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODULE_AUTHOR("Andrey Smirnov <andrew.smirnov@gmail.com>");
MODULE_DESCRIPTION("RAVE SP Power Button driver");
