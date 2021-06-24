<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Filename: ks0108.c
 *     Version: 0.1.0
 * Description: ks0108 LCD Controller driver
 *     Depends: parport
 *
 *      Author: Copyright (C) Miguel Ojeda <ojeda@kernel.org>
 *        Date: 2006-10-31
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/parport.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ks0108.h>

#घोषणा KS0108_NAME "ks0108"

/*
 * Module Parameters
 */

अटल अचिन्हित पूर्णांक ks0108_port = CONFIG_KS0108_PORT;
module_param(ks0108_port, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ks0108_port, "Parallel port where the LCD is connected");

अटल अचिन्हित पूर्णांक ks0108_delay = CONFIG_KS0108_DELAY;
module_param(ks0108_delay, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ks0108_delay, "Delay between each control writing (microseconds)");

/*
 * Device
 */

अटल काष्ठा parport *ks0108_parport;
अटल काष्ठा pardevice *ks0108_pardevice;

/*
 * ks0108 Exported Commands (करोn't lock)
 *
 *   You _should_ lock in the top driver: This functions _should not_
 *   get race conditions in any way. Locking क्रम each byte here would be
 *   so slow and useless.
 *
 *   There are not bit definitions because they are not flags,
 *   just arbitrary combinations defined by the करोcumentation क्रम each
 *   function in the ks0108 LCD controller. If you want to know what means
 *   a specअगरic combination, look at the function's name.
 *
 *   The ks0108_ग_लिखोcontrol bits need to be reverted ^(0,1,3) because
 *   the parallel port also revert them using a "not" logic gate.
 */

#घोषणा bit(n) (((अचिन्हित अक्षर)1)<<(n))

व्योम ks0108_ग_लिखोdata(अचिन्हित अक्षर byte)
अणु
	parport_ग_लिखो_data(ks0108_parport, byte);
पूर्ण

व्योम ks0108_ग_लिखोcontrol(अचिन्हित अक्षर byte)
अणु
	udelay(ks0108_delay);
	parport_ग_लिखो_control(ks0108_parport, byte ^ (bit(0) | bit(1) | bit(3)));
पूर्ण

व्योम ks0108_displaystate(अचिन्हित अक्षर state)
अणु
	ks0108_ग_लिखोdata((state ? bit(0) : 0) | bit(1) | bit(2) | bit(3) | bit(4) | bit(5));
पूर्ण

व्योम ks0108_startline(अचिन्हित अक्षर startline)
अणु
	ks0108_ग_लिखोdata(min_t(अचिन्हित अक्षर, startline, 63) | bit(6) |
			 bit(7));
पूर्ण

व्योम ks0108_address(अचिन्हित अक्षर address)
अणु
	ks0108_ग_लिखोdata(min_t(अचिन्हित अक्षर, address, 63) | bit(6));
पूर्ण

व्योम ks0108_page(अचिन्हित अक्षर page)
अणु
	ks0108_ग_लिखोdata(min_t(अचिन्हित अक्षर, page, 7) | bit(3) | bit(4) |
			 bit(5) | bit(7));
पूर्ण

EXPORT_SYMBOL_GPL(ks0108_ग_लिखोdata);
EXPORT_SYMBOL_GPL(ks0108_ग_लिखोcontrol);
EXPORT_SYMBOL_GPL(ks0108_displaystate);
EXPORT_SYMBOL_GPL(ks0108_startline);
EXPORT_SYMBOL_GPL(ks0108_address);
EXPORT_SYMBOL_GPL(ks0108_page);

/*
 * Is the module inited?
 */

अटल अचिन्हित अक्षर ks0108_inited;
अचिन्हित अक्षर ks0108_isinited(व्योम)
अणु
	वापस ks0108_inited;
पूर्ण
EXPORT_SYMBOL_GPL(ks0108_isinited);

अटल व्योम ks0108_parport_attach(काष्ठा parport *port)
अणु
	काष्ठा pardev_cb ks0108_cb;

	अगर (port->base != ks0108_port)
		वापस;

	स_रखो(&ks0108_cb, 0, माप(ks0108_cb));
	ks0108_cb.flags = PARPORT_DEV_EXCL;
	ks0108_pardevice = parport_रेजिस्टर_dev_model(port, KS0108_NAME,
						      &ks0108_cb, 0);
	अगर (!ks0108_pardevice) अणु
		pr_err("ERROR: parport didn't register new device\n");
		वापस;
	पूर्ण
	अगर (parport_claim(ks0108_pardevice)) अणु
		pr_err("could not claim access to parport %i. Aborting.\n",
		       ks0108_port);
		जाओ err_unreg_device;
	पूर्ण

	ks0108_parport = port;
	ks0108_inited = 1;
	वापस;

err_unreg_device:
	parport_unरेजिस्टर_device(ks0108_pardevice);
	ks0108_pardevice = शून्य;
पूर्ण

अटल व्योम ks0108_parport_detach(काष्ठा parport *port)
अणु
	अगर (port->base != ks0108_port)
		वापस;

	अगर (!ks0108_pardevice) अणु
		pr_err("%s: already unregistered.\n", KS0108_NAME);
		वापस;
	पूर्ण

	parport_release(ks0108_pardevice);
	parport_unरेजिस्टर_device(ks0108_pardevice);
	ks0108_pardevice = शून्य;
	ks0108_parport = शून्य;
पूर्ण

/*
 * Module Init & Exit
 */

अटल काष्ठा parport_driver ks0108_parport_driver = अणु
	.name = "ks0108",
	.match_port = ks0108_parport_attach,
	.detach = ks0108_parport_detach,
	.devmodel = true,
पूर्ण;

अटल पूर्णांक __init ks0108_init(व्योम)
अणु
	वापस parport_रेजिस्टर_driver(&ks0108_parport_driver);
पूर्ण

अटल व्योम __निकास ks0108_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&ks0108_parport_driver);
पूर्ण

module_init(ks0108_init);
module_निकास(ks0108_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Miguel Ojeda <ojeda@kernel.org>");
MODULE_DESCRIPTION("ks0108 LCD Controller driver");

