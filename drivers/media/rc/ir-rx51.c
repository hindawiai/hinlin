<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008 Nokia Corporation
 *
 *  Based on lirc_serial.c
 */
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/pwm.h>
#समावेश <linux/of.h>
#समावेश <linux/hrसमयr.h>

#समावेश <media/rc-core.h>

#घोषणा WBUF_LEN 256

काष्ठा ir_rx51 अणु
	काष्ठा rc_dev *rcdev;
	काष्ठा pwm_device *pwm;
	काष्ठा hrसमयr समयr;
	काष्ठा device	     *dev;
	रुको_queue_head_t     wqueue;

	अचिन्हित पूर्णांक	freq;		/* carrier frequency */
	अचिन्हित पूर्णांक	duty_cycle;	/* carrier duty cycle */
	पूर्णांक		wbuf[WBUF_LEN];
	पूर्णांक		wbuf_index;
	अचिन्हित दीर्घ	device_is_खोलो;
पूर्ण;

अटल अंतरभूत व्योम ir_rx51_on(काष्ठा ir_rx51 *ir_rx51)
अणु
	pwm_enable(ir_rx51->pwm);
पूर्ण

अटल अंतरभूत व्योम ir_rx51_off(काष्ठा ir_rx51 *ir_rx51)
अणु
	pwm_disable(ir_rx51->pwm);
पूर्ण

अटल पूर्णांक init_timing_params(काष्ठा ir_rx51 *ir_rx51)
अणु
	काष्ठा pwm_device *pwm = ir_rx51->pwm;
	पूर्णांक duty, period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, ir_rx51->freq);

	duty = DIV_ROUND_CLOSEST(ir_rx51->duty_cycle * period, 100);

	pwm_config(pwm, duty, period);

	वापस 0;
पूर्ण

अटल क्रमागत hrसमयr_restart ir_rx51_समयr_cb(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा ir_rx51 *ir_rx51 = container_of(समयr, काष्ठा ir_rx51, समयr);
	kसमय_प्रकार now;

	अगर (ir_rx51->wbuf_index < 0) अणु
		dev_err_ratelimited(ir_rx51->dev,
				    "BUG wbuf_index has value of %i\n",
				    ir_rx51->wbuf_index);
		जाओ end;
	पूर्ण

	/*
	 * If we happen to hit an odd latency spike, loop through the
	 * pulses until we catch up.
	 */
	करो अणु
		u64 ns;

		अगर (ir_rx51->wbuf_index >= WBUF_LEN)
			जाओ end;
		अगर (ir_rx51->wbuf[ir_rx51->wbuf_index] == -1)
			जाओ end;

		अगर (ir_rx51->wbuf_index % 2)
			ir_rx51_off(ir_rx51);
		अन्यथा
			ir_rx51_on(ir_rx51);

		ns = US_TO_NS(ir_rx51->wbuf[ir_rx51->wbuf_index]);
		hrसमयr_add_expires_ns(समयr, ns);

		ir_rx51->wbuf_index++;

		now = समयr->base->get_समय();

	पूर्ण जबतक (hrसमयr_get_expires_tv64(समयr) < now);

	वापस HRTIMER_RESTART;
end:
	/* Stop TX here */
	ir_rx51_off(ir_rx51);
	ir_rx51->wbuf_index = -1;

	wake_up_पूर्णांकerruptible(&ir_rx51->wqueue);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक ir_rx51_tx(काष्ठा rc_dev *dev, अचिन्हित पूर्णांक *buffer,
		      अचिन्हित पूर्णांक count)
अणु
	काष्ठा ir_rx51 *ir_rx51 = dev->priv;

	अगर (count > WBUF_LEN)
		वापस -EINVAL;

	स_नकल(ir_rx51->wbuf, buffer, count * माप(अचिन्हित पूर्णांक));

	/* Wait any pending transfers to finish */
	रुको_event_पूर्णांकerruptible(ir_rx51->wqueue, ir_rx51->wbuf_index < 0);

	init_timing_params(ir_rx51);
	अगर (count < WBUF_LEN)
		ir_rx51->wbuf[count] = -1; /* Insert termination mark */

	/*
	 * REVISIT: Adjust latency requirements so the device करोesn't go in too
	 * deep sleep states with pm_qos_add_request().
	 */

	ir_rx51_on(ir_rx51);
	ir_rx51->wbuf_index = 1;
	hrसमयr_start(&ir_rx51->समयr,
		      ns_to_kसमय(US_TO_NS(ir_rx51->wbuf[0])),
		      HRTIMER_MODE_REL);
	/*
	 * Don't वापस back to the userspace until the transfer has
	 * finished
	 */
	रुको_event_पूर्णांकerruptible(ir_rx51->wqueue, ir_rx51->wbuf_index < 0);

	/* REVISIT: Remove pm_qos स्थिरraपूर्णांक, we can sleep again */

	वापस count;
पूर्ण

अटल पूर्णांक ir_rx51_खोलो(काष्ठा rc_dev *dev)
अणु
	काष्ठा ir_rx51 *ir_rx51 = dev->priv;

	अगर (test_and_set_bit(1, &ir_rx51->device_is_खोलो))
		वापस -EBUSY;

	ir_rx51->pwm = pwm_get(ir_rx51->dev, शून्य);
	अगर (IS_ERR(ir_rx51->pwm)) अणु
		पूर्णांक res = PTR_ERR(ir_rx51->pwm);

		dev_err(ir_rx51->dev, "pwm_get failed: %d\n", res);
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ir_rx51_release(काष्ठा rc_dev *dev)
अणु
	काष्ठा ir_rx51 *ir_rx51 = dev->priv;

	hrसमयr_cancel(&ir_rx51->समयr);
	ir_rx51_off(ir_rx51);
	pwm_put(ir_rx51->pwm);

	clear_bit(1, &ir_rx51->device_is_खोलो);
पूर्ण

अटल काष्ठा ir_rx51 ir_rx51 = अणु
	.duty_cycle	= 50,
	.wbuf_index	= -1,
पूर्ण;

अटल पूर्णांक ir_rx51_set_duty_cycle(काष्ठा rc_dev *dev, u32 duty)
अणु
	काष्ठा ir_rx51 *ir_rx51 = dev->priv;

	ir_rx51->duty_cycle = duty;

	वापस 0;
पूर्ण

अटल पूर्णांक ir_rx51_set_tx_carrier(काष्ठा rc_dev *dev, u32 carrier)
अणु
	काष्ठा ir_rx51 *ir_rx51 = dev->priv;

	अगर (carrier > 500000 || carrier < 20000)
		वापस -EINVAL;

	ir_rx51->freq = carrier;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक ir_rx51_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	/*
	 * In हाल the device is still खोलो, करो not suspend. Normally
	 * this should not be a problem as lircd only keeps the device
	 * खोलो only क्रम लघु periods of समय. We also करोn't want to
	 * get involved with race conditions that might happen अगर we
	 * were in a middle of a transmit. Thus, we defer any suspend
	 * actions until transmit has completed.
	 */
	अगर (test_and_set_bit(1, &ir_rx51.device_is_खोलो))
		वापस -EAGAIN;

	clear_bit(1, &ir_rx51.device_is_खोलो);

	वापस 0;
पूर्ण

अटल पूर्णांक ir_rx51_resume(काष्ठा platक्रमm_device *dev)
अणु
	वापस 0;
पूर्ण

#अन्यथा

#घोषणा ir_rx51_suspend	शून्य
#घोषणा ir_rx51_resume	शून्य

#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक ir_rx51_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pwm_device *pwm;
	काष्ठा rc_dev *rcdev;

	pwm = pwm_get(&dev->dev, शून्य);
	अगर (IS_ERR(pwm)) अणु
		पूर्णांक err = PTR_ERR(pwm);

		अगर (err != -EPROBE_DEFER)
			dev_err(&dev->dev, "pwm_get failed: %d\n", err);
		वापस err;
	पूर्ण

	/* Use शेष, in हाल userspace करोes not set the carrier */
	ir_rx51.freq = DIV_ROUND_CLOSEST_ULL(pwm_get_period(pwm), NSEC_PER_SEC);
	pwm_put(pwm);

	hrसमयr_init(&ir_rx51.समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ir_rx51.समयr.function = ir_rx51_समयr_cb;

	ir_rx51.dev = &dev->dev;

	rcdev = devm_rc_allocate_device(&dev->dev, RC_DRIVER_IR_RAW_TX);
	अगर (!rcdev)
		वापस -ENOMEM;

	rcdev->priv = &ir_rx51;
	rcdev->खोलो = ir_rx51_खोलो;
	rcdev->बंद = ir_rx51_release;
	rcdev->tx_ir = ir_rx51_tx;
	rcdev->s_tx_duty_cycle = ir_rx51_set_duty_cycle;
	rcdev->s_tx_carrier = ir_rx51_set_tx_carrier;
	rcdev->driver_name = KBUILD_MODNAME;

	ir_rx51.rcdev = rcdev;

	वापस devm_rc_रेजिस्टर_device(&dev->dev, ir_rx51.rcdev);
पूर्ण

अटल पूर्णांक ir_rx51_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ir_rx51_match[] = अणु
	अणु
		.compatible = "nokia,n900-ir",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ir_rx51_match);

अटल काष्ठा platक्रमm_driver ir_rx51_platक्रमm_driver = अणु
	.probe		= ir_rx51_probe,
	.हटाओ		= ir_rx51_हटाओ,
	.suspend	= ir_rx51_suspend,
	.resume		= ir_rx51_resume,
	.driver		= अणु
		.name	= KBUILD_MODNAME,
		.of_match_table = of_match_ptr(ir_rx51_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ir_rx51_platक्रमm_driver);

MODULE_DESCRIPTION("IR TX driver for Nokia RX51");
MODULE_AUTHOR("Nokia Corporation");
MODULE_LICENSE("GPL");
