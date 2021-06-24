<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pps_gen_parport.c -- kernel parallel port PPS संकेत generator
 *
 * Copyright (C) 2009   Alexander Gordeev <lasaine@lvk.cs.msu.su>
 */


/*
 * TODO:
 * fix issues when realसमय घड़ी is adjusted in a leap
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/parport.h>

#घोषणा DRVDESC "parallel port PPS signal generator"

#घोषणा SIGNAL		0
#घोषणा NO_SIGNAL	PARPORT_CONTROL_STROBE

/* module parameters */

#घोषणा SEND_DELAY_MAX		100000

अटल अचिन्हित पूर्णांक send_delay = 30000;
MODULE_PARM_DESC(delay,
	"Delay between setting and dropping the signal (ns)");
module_param_named(delay, send_delay, uपूर्णांक, 0);


#घोषणा SAFETY_INTERVAL	3000	/* set the hrसमयr earlier क्रम safety (ns) */

/* पूर्णांकernal per port काष्ठाure */
काष्ठा pps_generator_pp अणु
	काष्ठा pardevice *pardev;	/* parport device */
	काष्ठा hrसमयr समयr;
	दीर्घ port_ग_लिखो_समय;		/* calibrated port ग_लिखो समय (ns) */
पूर्ण;

अटल काष्ठा pps_generator_pp device = अणु
	.pardev = शून्य,
पूर्ण;

अटल पूर्णांक attached;

/* calibrated समय between a hrसमयr event and the reaction */
अटल दीर्घ hrसमयr_error = SAFETY_INTERVAL;

/* the kernel hrसमयr event */
अटल क्रमागत hrसमयr_restart hrसमयr_event(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा बारpec64 expire_समय, ts1, ts2, ts3, dts;
	काष्ठा pps_generator_pp *dev;
	काष्ठा parport *port;
	दीर्घ lim, delta;
	अचिन्हित दीर्घ flags;

	/* We have to disable पूर्णांकerrupts here. The idea is to prevent
	 * other पूर्णांकerrupts on the same processor to पूर्णांकroduce अक्रमom
	 * lags जबतक polling the घड़ी. kसमय_get_real_ts64() takes <1us on
	 * most machines जबतक other पूर्णांकerrupt handlers can take much
	 * more potentially.
	 *
	 * NB: approx समय with blocked पूर्णांकerrupts =
	 * send_delay + 3 * SAFETY_INTERVAL
	 */
	local_irq_save(flags);

	/* first of all we get the समय stamp... */
	kसमय_get_real_ts64(&ts1);
	expire_समय = kसमय_प्रकारo_बारpec64(hrसमयr_get_softexpires(समयr));
	dev = container_of(समयr, काष्ठा pps_generator_pp, समयr);
	lim = NSEC_PER_SEC - send_delay - dev->port_ग_लिखो_समय;

	/* check अगर we are late */
	अगर (expire_समय.tv_sec != ts1.tv_sec || ts1.tv_nsec > lim) अणु
		local_irq_restore(flags);
		pr_err("we are late this time %lld.%09ld\n",
				(s64)ts1.tv_sec, ts1.tv_nsec);
		जाओ करोne;
	पूर्ण

	/* busy loop until the समय is right क्रम an निश्चित edge */
	करो अणु
		kसमय_get_real_ts64(&ts2);
	पूर्ण जबतक (expire_समय.tv_sec == ts2.tv_sec && ts2.tv_nsec < lim);

	/* set the संकेत */
	port = dev->pardev->port;
	port->ops->ग_लिखो_control(port, SIGNAL);

	/* busy loop until the समय is right क्रम a clear edge */
	lim = NSEC_PER_SEC - dev->port_ग_लिखो_समय;
	करो अणु
		kसमय_get_real_ts64(&ts2);
	पूर्ण जबतक (expire_समय.tv_sec == ts2.tv_sec && ts2.tv_nsec < lim);

	/* unset the संकेत */
	port->ops->ग_लिखो_control(port, NO_SIGNAL);

	kसमय_get_real_ts64(&ts3);

	local_irq_restore(flags);

	/* update calibrated port ग_लिखो समय */
	dts = बारpec64_sub(ts3, ts2);
	dev->port_ग_लिखो_समय =
		(dev->port_ग_लिखो_समय + बारpec64_to_ns(&dts)) >> 1;

करोne:
	/* update calibrated hrसमयr error */
	dts = बारpec64_sub(ts1, expire_समय);
	delta = बारpec64_to_ns(&dts);
	/* If the new error value is bigger then the old, use the new
	 * value, अगर not then slowly move towards the new value. This
	 * way it should be safe in bad conditions and efficient in
	 * good conditions.
	 */
	अगर (delta >= hrसमयr_error)
		hrसमयr_error = delta;
	अन्यथा
		hrसमयr_error = (3 * hrसमयr_error + delta) >> 2;

	/* update the hrसमयr expire समय */
	hrसमयr_set_expires(समयr,
			kसमय_set(expire_समय.tv_sec + 1,
				NSEC_PER_SEC - (send_delay +
				dev->port_ग_लिखो_समय + SAFETY_INTERVAL +
				2 * hrसमयr_error)));

	वापस HRTIMER_RESTART;
पूर्ण

/* calibrate port ग_लिखो समय */
#घोषणा PORT_NTESTS_SHIFT	5
अटल व्योम calibrate_port(काष्ठा pps_generator_pp *dev)
अणु
	काष्ठा parport *port = dev->pardev->port;
	पूर्णांक i;
	दीर्घ acc = 0;

	क्रम (i = 0; i < (1 << PORT_NTESTS_SHIFT); i++) अणु
		काष्ठा बारpec64 a, b;
		अचिन्हित दीर्घ irq_flags;

		local_irq_save(irq_flags);
		kसमय_get_real_ts64(&a);
		port->ops->ग_लिखो_control(port, NO_SIGNAL);
		kसमय_get_real_ts64(&b);
		local_irq_restore(irq_flags);

		b = बारpec64_sub(b, a);
		acc += बारpec64_to_ns(&b);
	पूर्ण

	dev->port_ग_लिखो_समय = acc >> PORT_NTESTS_SHIFT;
	pr_info("port write takes %ldns\n", dev->port_ग_लिखो_समय);
पूर्ण

अटल अंतरभूत kसमय_प्रकार next_पूर्णांकr_समय(काष्ठा pps_generator_pp *dev)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_real_ts64(&ts);

	वापस kसमय_set(ts.tv_sec +
			((ts.tv_nsec > 990 * NSEC_PER_MSEC) ? 1 : 0),
			NSEC_PER_SEC - (send_delay +
			dev->port_ग_लिखो_समय + 3 * SAFETY_INTERVAL));
पूर्ण

अटल व्योम parport_attach(काष्ठा parport *port)
अणु
	काष्ठा pardev_cb pps_cb;

	अगर (attached) अणु
		/* we alपढ़ोy have a port */
		वापस;
	पूर्ण

	स_रखो(&pps_cb, 0, माप(pps_cb));
	pps_cb.निजी = &device;
	pps_cb.flags = PARPORT_FLAG_EXCL;
	device.pardev = parport_रेजिस्टर_dev_model(port, KBUILD_MODNAME,
						   &pps_cb, 0);
	अगर (!device.pardev) अणु
		pr_err("couldn't register with %s\n", port->name);
		वापस;
	पूर्ण

	अगर (parport_claim_or_block(device.pardev) < 0) अणु
		pr_err("couldn't claim %s\n", port->name);
		जाओ err_unरेजिस्टर_dev;
	पूर्ण

	pr_info("attached to %s\n", port->name);
	attached = 1;

	calibrate_port(&device);

	hrसमयr_init(&device.समयr, CLOCK_REALTIME, HRTIMER_MODE_ABS);
	device.समयr.function = hrसमयr_event;
	hrसमयr_start(&device.समयr, next_पूर्णांकr_समय(&device), HRTIMER_MODE_ABS);

	वापस;

err_unरेजिस्टर_dev:
	parport_unरेजिस्टर_device(device.pardev);
पूर्ण

अटल व्योम parport_detach(काष्ठा parport *port)
अणु
	अगर (port->cad != device.pardev)
		वापस;	/* not our port */

	hrसमयr_cancel(&device.समयr);
	parport_release(device.pardev);
	parport_unरेजिस्टर_device(device.pardev);
पूर्ण

अटल काष्ठा parport_driver pps_gen_parport_driver = अणु
	.name = KBUILD_MODNAME,
	.match_port = parport_attach,
	.detach = parport_detach,
	.devmodel = true,
पूर्ण;

/* module staff */

अटल पूर्णांक __init pps_gen_parport_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info(DRVDESC "\n");

	अगर (send_delay > SEND_DELAY_MAX) अणु
		pr_err("delay value should be not greater"
				" then %d\n", SEND_DELAY_MAX);
		वापस -EINVAL;
	पूर्ण

	ret = parport_रेजिस्टर_driver(&pps_gen_parport_driver);
	अगर (ret) अणु
		pr_err("unable to register with parport\n");
		वापस ret;
	पूर्ण

	वापस  0;
पूर्ण

अटल व्योम __निकास pps_gen_parport_निकास(व्योम)
अणु
	parport_unरेजिस्टर_driver(&pps_gen_parport_driver);
	pr_info("hrtimer avg error is %ldns\n", hrसमयr_error);
पूर्ण

module_init(pps_gen_parport_init);
module_निकास(pps_gen_parport_निकास);

MODULE_AUTHOR("Alexander Gordeev <lasaine@lvk.cs.msu.su>");
MODULE_DESCRIPTION(DRVDESC);
MODULE_LICENSE("GPL");
