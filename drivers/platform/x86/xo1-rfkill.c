<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम rfसमाप्त through the OLPC XO-1 laptop embedded controller
 *
 * Copyright (C) 2010 One Laptop per Child
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/olpc-ec.h>

अटल bool card_blocked;

अटल पूर्णांक rfसमाप्त_set_block(व्योम *data, bool blocked)
अणु
	अचिन्हित अक्षर cmd;
	पूर्णांक r;

	अगर (blocked == card_blocked)
		वापस 0;

	अगर (blocked)
		cmd = EC_WLAN_ENTER_RESET;
	अन्यथा
		cmd = EC_WLAN_LEAVE_RESET;

	r = olpc_ec_cmd(cmd, शून्य, 0, शून्य, 0);
	अगर (r == 0)
		card_blocked = blocked;

	वापस r;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops rfसमाप्त_ops = अणु
	.set_block = rfसमाप्त_set_block,
पूर्ण;

अटल पूर्णांक xo1_rfसमाप्त_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rfसमाप्त *rfk;
	पूर्णांक r;

	rfk = rfसमाप्त_alloc(pdev->name, &pdev->dev, RFKILL_TYPE_WLAN,
			   &rfसमाप्त_ops, शून्य);
	अगर (!rfk)
		वापस -ENOMEM;

	r = rfसमाप्त_रेजिस्टर(rfk);
	अगर (r) अणु
		rfसमाप्त_destroy(rfk);
		वापस r;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rfk);
	वापस 0;
पूर्ण

अटल पूर्णांक xo1_rfसमाप्त_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rfसमाप्त *rfk = platक्रमm_get_drvdata(pdev);
	rfसमाप्त_unरेजिस्टर(rfk);
	rfसमाप्त_destroy(rfk);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xo1_rfसमाप्त_driver = अणु
	.driver = अणु
		.name = "xo1-rfkill",
	पूर्ण,
	.probe		= xo1_rfसमाप्त_probe,
	.हटाओ		= xo1_rfसमाप्त_हटाओ,
पूर्ण;

module_platक्रमm_driver(xo1_rfसमाप्त_driver);

MODULE_AUTHOR("Daniel Drake <dsd@laptop.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:xo1-rfkill");
