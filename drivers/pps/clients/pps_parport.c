<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pps_parport.c -- kernel parallel port PPS client
 *
 * Copyright (C) 2009   Alexander Gordeev <lasaine@lvk.cs.msu.su>
 */


/*
 * TODO:
 * implement echo over SEL pin
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/irqnr.h>
#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/parport.h>
#समावेश <linux/pps_kernel.h>

#घोषणा DRVDESC "parallel port PPS client"

/* module parameters */

#घोषणा CLEAR_WAIT_MAX		100
#घोषणा CLEAR_WAIT_MAX_ERRORS	5

अटल अचिन्हित पूर्णांक clear_रुको = 100;
MODULE_PARM_DESC(clear_रुको,
	"Maximum number of port reads when polling for signal clear,"
	" zero turns clear edge capture off entirely");
module_param(clear_रुको, uपूर्णांक, 0);

अटल DEFINE_IDA(pps_client_index);

/* पूर्णांकernal per port काष्ठाure */
काष्ठा pps_client_pp अणु
	काष्ठा pardevice *pardev;	/* parport device */
	काष्ठा pps_device *pps;		/* PPS device */
	अचिन्हित पूर्णांक cw;		/* port clear समयout */
	अचिन्हित पूर्णांक cw_err;		/* number of समयouts */
	पूर्णांक index;			/* device number */
पूर्ण;

अटल अंतरभूत पूर्णांक संकेत_is_set(काष्ठा parport *port)
अणु
	वापस (port->ops->पढ़ो_status(port) & PARPORT_STATUS_ACK) != 0;
पूर्ण

/* parport पूर्णांकerrupt handler */
अटल व्योम parport_irq(व्योम *handle)
अणु
	काष्ठा pps_event_समय ts_निश्चित, ts_clear;
	काष्ठा pps_client_pp *dev = handle;
	काष्ठा parport *port = dev->pardev->port;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/* first of all we get the समय stamp... */
	pps_get_ts(&ts_निश्चित);

	अगर (dev->cw == 0)
		/* clear edge capture disabled */
		जाओ out_निश्चित;

	/* try capture the clear edge */

	/* We have to disable पूर्णांकerrupts here. The idea is to prevent
	 * other पूर्णांकerrupts on the same processor to पूर्णांकroduce अक्रमom
	 * lags जबतक polling the port. Reading from IO port is known
	 * to take approximately 1us जबतक other पूर्णांकerrupt handlers can
	 * take much more potentially.
	 *
	 * Interrupts won't be disabled क्रम a दीर्घ समय because the
	 * number of polls is limited by clear_रुको parameter which is
	 * kept rather low. So it should never be an issue.
	 */
	local_irq_save(flags);
	/* check the संकेत (no संकेत means the pulse is lost this समय) */
	अगर (!संकेत_is_set(port)) अणु
		local_irq_restore(flags);
		dev_err(dev->pps->dev, "lost the signal\n");
		जाओ out_निश्चित;
	पूर्ण

	/* poll the port until the संकेत is unset */
	क्रम (i = dev->cw; i; i--)
		अगर (!संकेत_is_set(port)) अणु
			pps_get_ts(&ts_clear);
			local_irq_restore(flags);
			dev->cw_err = 0;
			जाओ out_both;
		पूर्ण
	local_irq_restore(flags);

	/* समयout */
	dev->cw_err++;
	अगर (dev->cw_err >= CLEAR_WAIT_MAX_ERRORS) अणु
		dev_err(dev->pps->dev, "disabled clear edge capture after %d"
				" timeouts\n", dev->cw_err);
		dev->cw = 0;
		dev->cw_err = 0;
	पूर्ण

out_निश्चित:
	/* fire निश्चित event */
	pps_event(dev->pps, &ts_निश्चित,
			PPS_CAPTUREASSERT, शून्य);
	वापस;

out_both:
	/* fire निश्चित event */
	pps_event(dev->pps, &ts_निश्चित,
			PPS_CAPTUREASSERT, शून्य);
	/* fire clear event */
	pps_event(dev->pps, &ts_clear,
			PPS_CAPTURECLEAR, शून्य);
	वापस;
पूर्ण

अटल व्योम parport_attach(काष्ठा parport *port)
अणु
	काष्ठा pardev_cb pps_client_cb;
	पूर्णांक index;
	काष्ठा pps_client_pp *device;
	काष्ठा pps_source_info info = अणु
		.name		= KBUILD_MODNAME,
		.path		= "",
		.mode		= PPS_CAPTUREBOTH | \
				  PPS_OFFSETASSERT | PPS_OFFSETCLEAR | \
				  PPS_ECHOASSERT | PPS_ECHOCLEAR | \
				  PPS_CANWAIT | PPS_TSFMT_TSPEC,
		.owner		= THIS_MODULE,
		.dev		= शून्य
	पूर्ण;

	device = kzalloc(माप(काष्ठा pps_client_pp), GFP_KERNEL);
	अगर (!device) अणु
		pr_err("memory allocation failed, not attaching\n");
		वापस;
	पूर्ण

	index = ida_simple_get(&pps_client_index, 0, 0, GFP_KERNEL);
	स_रखो(&pps_client_cb, 0, माप(pps_client_cb));
	pps_client_cb.निजी = device;
	pps_client_cb.irq_func = parport_irq;
	pps_client_cb.flags = PARPORT_FLAG_EXCL;
	device->pardev = parport_रेजिस्टर_dev_model(port,
						    KBUILD_MODNAME,
						    &pps_client_cb,
						    index);
	अगर (!device->pardev) अणु
		pr_err("couldn't register with %s\n", port->name);
		जाओ err_मुक्त;
	पूर्ण

	अगर (parport_claim_or_block(device->pardev) < 0) अणु
		pr_err("couldn't claim %s\n", port->name);
		जाओ err_unरेजिस्टर_dev;
	पूर्ण

	device->pps = pps_रेजिस्टर_source(&info,
			PPS_CAPTUREBOTH | PPS_OFFSETASSERT | PPS_OFFSETCLEAR);
	अगर (IS_ERR(device->pps)) अणु
		pr_err("couldn't register PPS source\n");
		जाओ err_release_dev;
	पूर्ण

	device->cw = clear_रुको;

	port->ops->enable_irq(port);
	device->index = index;

	pr_info("attached to %s\n", port->name);

	वापस;

err_release_dev:
	parport_release(device->pardev);
err_unरेजिस्टर_dev:
	parport_unरेजिस्टर_device(device->pardev);
err_मुक्त:
	ida_simple_हटाओ(&pps_client_index, index);
	kमुक्त(device);
पूर्ण

अटल व्योम parport_detach(काष्ठा parport *port)
अणु
	काष्ठा pardevice *pardev = port->cad;
	काष्ठा pps_client_pp *device;

	/* FIXME: oooh, this is ugly! */
	अगर (!pardev || म_भेद(pardev->name, KBUILD_MODNAME))
		/* not our port */
		वापस;

	device = pardev->निजी;

	port->ops->disable_irq(port);
	pps_unरेजिस्टर_source(device->pps);
	parport_release(pardev);
	parport_unरेजिस्टर_device(pardev);
	ida_simple_हटाओ(&pps_client_index, device->index);
	kमुक्त(device);
पूर्ण

अटल काष्ठा parport_driver pps_parport_driver = अणु
	.name = KBUILD_MODNAME,
	.match_port = parport_attach,
	.detach = parport_detach,
	.devmodel = true,
पूर्ण;

/* module staff */

अटल पूर्णांक __init pps_parport_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info(DRVDESC "\n");

	अगर (clear_रुको > CLEAR_WAIT_MAX) अणु
		pr_err("clear_wait value should be not greater"
				" then %d\n", CLEAR_WAIT_MAX);
		वापस -EINVAL;
	पूर्ण

	ret = parport_रेजिस्टर_driver(&pps_parport_driver);
	अगर (ret) अणु
		pr_err("unable to register with parport\n");
		वापस ret;
	पूर्ण

	वापस  0;
पूर्ण

अटल व्योम __निकास pps_parport_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&pps_parport_driver);
पूर्ण

module_init(pps_parport_init);
module_निकास(pps_parport_निकास);

MODULE_AUTHOR("Alexander Gordeev <lasaine@lvk.cs.msu.su>");
MODULE_DESCRIPTION(DRVDESC);
MODULE_LICENSE("GPL");
