<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 STMicroelectronics Limited
 * Author: Srinivas Kandagatla <srinivas.kandagatla@st.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <media/rc-core.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_wakeirq.h>

काष्ठा st_rc_device अणु
	काष्ठा device			*dev;
	पूर्णांक				irq;
	पूर्णांक				irq_wake;
	काष्ठा clk			*sys_घड़ी;
	व्योम __iomem			*base;	/* Register base address */
	व्योम __iomem			*rx_base;/* RX Register base address */
	काष्ठा rc_dev			*rdev;
	bool				overघड़ीing;
	पूर्णांक				sample_mult;
	पूर्णांक				sample_भाग;
	bool				rxuhभ_शेषe;
	काष्ठा	reset_control		*rstc;
पूर्ण;

/* Registers */
#घोषणा IRB_SAMPLE_RATE_COMM	0x64	/* sample freq भागisor*/
#घोषणा IRB_CLOCK_SEL		0x70	/* घड़ी select       */
#घोषणा IRB_CLOCK_SEL_STATUS	0x74	/* घड़ी status       */
/* IRB IR/UHF receiver रेजिस्टरs */
#घोषणा IRB_RX_ON               0x40	/* pulse समय capture */
#घोषणा IRB_RX_SYS              0X44	/* sym period capture */
#घोषणा IRB_RX_INT_EN           0x48	/* IRQ enable (R/W)   */
#घोषणा IRB_RX_INT_STATUS       0x4c	/* IRQ status (R/W)   */
#घोषणा IRB_RX_EN               0x50	/* Receive enable     */
#घोषणा IRB_MAX_SYM_PERIOD      0x54	/* max sym value      */
#घोषणा IRB_RX_INT_CLEAR        0x58	/* overrun status     */
#घोषणा IRB_RX_STATUS           0x6c	/* receive status     */
#घोषणा IRB_RX_NOISE_SUPPR      0x5c	/* noise suppression  */
#घोषणा IRB_RX_POLARITY_INV     0x68	/* polarity inverter  */

/*
 * IRQ set: Enable full FIFO                 1  -> bit  3;
 *          Enable overrun IRQ               1  -> bit  2;
 *          Enable last symbol IRQ           1  -> bit  1:
 *          Enable RX पूर्णांकerrupt              1  -> bit  0;
 */
#घोषणा IRB_RX_INTS		0x0f
#घोषणा IRB_RX_OVERRUN_INT	0x04
 /* maximum symbol period (microsecs),समयout to detect end of symbol train */
#घोषणा MAX_SYMB_TIME		0x5000
#घोषणा IRB_SAMPLE_FREQ		10000000
#घोषणा	IRB_FIFO_NOT_EMPTY	0xff00
#घोषणा IRB_OVERFLOW		0x4
#घोषणा IRB_TIMEOUT		0xffff
#घोषणा IR_ST_NAME "st-rc"

अटल व्योम st_rc_send_lirc_समयout(काष्ठा rc_dev *rdev)
अणु
	काष्ठा ir_raw_event ev = अणु .समयout = true, .duration = rdev->समयout पूर्ण;
	ir_raw_event_store(rdev, &ev);
पूर्ण

/*
 * RX graphical example to better understand the dअगरference between ST IR block
 * output and standard definition used by LIRC (and most of the world!)
 *
 *           mark                                     mark
 *      |-IRB_RX_ON-|                            |-IRB_RX_ON-|
 *      ___  ___  ___                            ___  ___  ___             _
 *      | |  | |  | |                            | |  | |  | |             |
 *      | |  | |  | |         space 0            | |  | |  | |   space 1   |
 * _____| |__| |__| |____________________________| |__| |__| |_____________|
 *
 *      |--------------- IRB_RX_SYS -------------|------ IRB_RX_SYS -------|
 *
 *      |------------- encoding bit 0 -----------|---- encoding bit 1 -----|
 *
 * ST hardware वापसs mark (IRB_RX_ON) and total symbol समय (IRB_RX_SYS), so
 * convert to standard mark/space we have to calculate space=(IRB_RX_SYS-mark)
 * The mark समय represents the amount of समय the carrier (usually 36-40kHz)
 * is detected.The above examples shows Pulse Width Modulation encoding where
 * bit 0 is represented by space>mark.
 */

अटल irqवापस_t st_rc_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक symbol, mark = 0;
	काष्ठा st_rc_device *dev = data;
	पूर्णांक last_symbol = 0;
	u32 status, पूर्णांक_status;
	काष्ठा ir_raw_event ev = अणुपूर्ण;

	अगर (dev->irq_wake)
		pm_wakeup_event(dev->dev, 0);

	/* FIXME: is 10ms good enough ? */
	समयout = jअगरfies +  msecs_to_jअगरfies(10);
	करो अणु
		status  = पढ़ोl(dev->rx_base + IRB_RX_STATUS);
		अगर (!(status & (IRB_FIFO_NOT_EMPTY | IRB_OVERFLOW)))
			अवरोध;

		पूर्णांक_status = पढ़ोl(dev->rx_base + IRB_RX_INT_STATUS);
		अगर (unlikely(पूर्णांक_status & IRB_RX_OVERRUN_INT)) अणु
			/* discard the entire collection in हाल of errors!  */
			ir_raw_event_reset(dev->rdev);
			dev_info(dev->dev, "IR RX overrun\n");
			ग_लिखोl(IRB_RX_OVERRUN_INT,
					dev->rx_base + IRB_RX_INT_CLEAR);
			जारी;
		पूर्ण

		symbol = पढ़ोl(dev->rx_base + IRB_RX_SYS);
		mark = पढ़ोl(dev->rx_base + IRB_RX_ON);

		अगर (symbol == IRB_TIMEOUT)
			last_symbol = 1;

		 /* Ignore any noise */
		अगर ((mark > 2) && (symbol > 1)) अणु
			symbol -= mark;
			अगर (dev->overघड़ीing) अणु /* adjusपंचांगents to timings */
				symbol *= dev->sample_mult;
				symbol /= dev->sample_भाग;
				mark *= dev->sample_mult;
				mark /= dev->sample_भाग;
			पूर्ण

			ev.duration = mark;
			ev.pulse = true;
			ir_raw_event_store(dev->rdev, &ev);

			अगर (!last_symbol) अणु
				ev.duration = symbol;
				ev.pulse = false;
				ir_raw_event_store(dev->rdev, &ev);
			पूर्ण अन्यथा  अणु
				st_rc_send_lirc_समयout(dev->rdev);
			पूर्ण

		पूर्ण
		last_symbol = 0;
	पूर्ण जबतक (समय_is_after_jअगरfies(समयout));

	ग_लिखोl(IRB_RX_INTS, dev->rx_base + IRB_RX_INT_CLEAR);

	/* Empty software fअगरo */
	ir_raw_event_handle(dev->rdev);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम st_rc_hardware_init(काष्ठा st_rc_device *dev)
अणु
	पूर्णांक baseघड़ी, freqdअगरf;
	अचिन्हित पूर्णांक rx_max_symbol_per = MAX_SYMB_TIME;
	अचिन्हित पूर्णांक rx_sampling_freq_भाग;

	/* Enable the IP */
	reset_control_deनिश्चित(dev->rstc);

	clk_prepare_enable(dev->sys_घड़ी);
	baseघड़ी = clk_get_rate(dev->sys_घड़ी);

	/* IRB input pins are inverted पूर्णांकernally from high to low. */
	ग_लिखोl(1, dev->rx_base + IRB_RX_POLARITY_INV);

	rx_sampling_freq_भाग = baseघड़ी / IRB_SAMPLE_FREQ;
	ग_लिखोl(rx_sampling_freq_भाग, dev->base + IRB_SAMPLE_RATE_COMM);

	freqdअगरf = baseघड़ी - (rx_sampling_freq_भाग * IRB_SAMPLE_FREQ);
	अगर (freqdअगरf) अणु /* over घड़ीing, workout the adjusपंचांगent factors */
		dev->overघड़ीing = true;
		dev->sample_mult = 1000;
		dev->sample_भाग = baseघड़ी / (10000 * rx_sampling_freq_भाग);
		rx_max_symbol_per = (rx_max_symbol_per * 1000)/dev->sample_भाग;
	पूर्ण

	ग_लिखोl(rx_max_symbol_per, dev->rx_base + IRB_MAX_SYM_PERIOD);
पूर्ण

अटल पूर्णांक st_rc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_rc_device *rc_dev = platक्रमm_get_drvdata(pdev);

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);
	clk_disable_unprepare(rc_dev->sys_घड़ी);
	rc_unरेजिस्टर_device(rc_dev->rdev);
	वापस 0;
पूर्ण

अटल पूर्णांक st_rc_खोलो(काष्ठा rc_dev *rdev)
अणु
	काष्ठा st_rc_device *dev = rdev->priv;
	अचिन्हित दीर्घ flags;
	local_irq_save(flags);
	/* enable पूर्णांकerrupts and receiver */
	ग_लिखोl(IRB_RX_INTS, dev->rx_base + IRB_RX_INT_EN);
	ग_लिखोl(0x01, dev->rx_base + IRB_RX_EN);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम st_rc_बंद(काष्ठा rc_dev *rdev)
अणु
	काष्ठा st_rc_device *dev = rdev->priv;
	/* disable पूर्णांकerrupts and receiver */
	ग_लिखोl(0x00, dev->rx_base + IRB_RX_EN);
	ग_लिखोl(0x00, dev->rx_base + IRB_RX_INT_EN);
पूर्ण

अटल पूर्णांक st_rc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा rc_dev *rdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा st_rc_device *rc_dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर अक्षर *rx_mode;

	rc_dev = devm_kzalloc(dev, माप(काष्ठा st_rc_device), GFP_KERNEL);

	अगर (!rc_dev)
		वापस -ENOMEM;

	rdev = rc_allocate_device(RC_DRIVER_IR_RAW);

	अगर (!rdev)
		वापस -ENOMEM;

	अगर (np && !of_property_पढ़ो_string(np, "rx-mode", &rx_mode)) अणु

		अगर (!म_भेद(rx_mode, "uhf")) अणु
			rc_dev->rxuhभ_शेषe = true;
		पूर्ण अन्यथा अगर (!म_भेद(rx_mode, "infrared")) अणु
			rc_dev->rxuhभ_शेषe = false;
		पूर्ण अन्यथा अणु
			dev_err(dev, "Unsupported rx mode [%s]\n", rx_mode);
			जाओ err;
		पूर्ण

	पूर्ण अन्यथा अणु
		जाओ err;
	पूर्ण

	rc_dev->sys_घड़ी = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(rc_dev->sys_घड़ी)) अणु
		dev_err(dev, "System clock not found\n");
		ret = PTR_ERR(rc_dev->sys_घड़ी);
		जाओ err;
	पूर्ण

	rc_dev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rc_dev->irq < 0) अणु
		ret = rc_dev->irq;
		जाओ err;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	rc_dev->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(rc_dev->base)) अणु
		ret = PTR_ERR(rc_dev->base);
		जाओ err;
	पूर्ण

	अगर (rc_dev->rxuhभ_शेषe)
		rc_dev->rx_base = rc_dev->base + 0x40;
	अन्यथा
		rc_dev->rx_base = rc_dev->base;

	rc_dev->rstc = reset_control_get_optional_exclusive(dev, शून्य);
	अगर (IS_ERR(rc_dev->rstc)) अणु
		ret = PTR_ERR(rc_dev->rstc);
		जाओ err;
	पूर्ण

	rc_dev->dev = dev;
	platक्रमm_set_drvdata(pdev, rc_dev);
	st_rc_hardware_init(rc_dev);

	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	/* rx sampling rate is 10Mhz */
	rdev->rx_resolution = 100;
	rdev->समयout = MAX_SYMB_TIME;
	rdev->priv = rc_dev;
	rdev->खोलो = st_rc_खोलो;
	rdev->बंद = st_rc_बंद;
	rdev->driver_name = IR_ST_NAME;
	rdev->map_name = RC_MAP_EMPTY;
	rdev->device_name = "ST Remote Control Receiver";

	ret = rc_रेजिस्टर_device(rdev);
	अगर (ret < 0)
		जाओ clkerr;

	rc_dev->rdev = rdev;
	अगर (devm_request_irq(dev, rc_dev->irq, st_rc_rx_पूर्णांकerrupt,
			     0, IR_ST_NAME, rc_dev) < 0) अणु
		dev_err(dev, "IRQ %d register failed\n", rc_dev->irq);
		ret = -EINVAL;
		जाओ rcerr;
	पूर्ण

	/* enable wake via this device */
	device_init_wakeup(dev, true);
	dev_pm_set_wake_irq(dev, rc_dev->irq);

	/*
	 * क्रम LIRC_MODE_MODE2 or LIRC_MODE_PULSE or LIRC_MODE_RAW
	 * lircd expects a दीर्घ space first beक्रमe a संकेत train to sync.
	 */
	st_rc_send_lirc_समयout(rdev);

	dev_info(dev, "setup in %s mode\n", rc_dev->rxuhभ_शेषe ? "UHF" : "IR");

	वापस ret;
rcerr:
	rc_unरेजिस्टर_device(rdev);
	rdev = शून्य;
clkerr:
	clk_disable_unprepare(rc_dev->sys_घड़ी);
err:
	rc_मुक्त_device(rdev);
	dev_err(dev, "Unable to register device (%d)\n", ret);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक st_rc_suspend(काष्ठा device *dev)
अणु
	काष्ठा st_rc_device *rc_dev = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev)) अणु
		अगर (!enable_irq_wake(rc_dev->irq))
			rc_dev->irq_wake = 1;
		अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		pinctrl_pm_select_sleep_state(dev);
		ग_लिखोl(0x00, rc_dev->rx_base + IRB_RX_EN);
		ग_लिखोl(0x00, rc_dev->rx_base + IRB_RX_INT_EN);
		clk_disable_unprepare(rc_dev->sys_घड़ी);
		reset_control_निश्चित(rc_dev->rstc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_rc_resume(काष्ठा device *dev)
अणु
	काष्ठा st_rc_device *rc_dev = dev_get_drvdata(dev);
	काष्ठा rc_dev	*rdev = rc_dev->rdev;

	अगर (rc_dev->irq_wake) अणु
		disable_irq_wake(rc_dev->irq);
		rc_dev->irq_wake = 0;
	पूर्ण अन्यथा अणु
		pinctrl_pm_select_शेष_state(dev);
		st_rc_hardware_init(rc_dev);
		अगर (rdev->users) अणु
			ग_लिखोl(IRB_RX_INTS, rc_dev->rx_base + IRB_RX_INT_EN);
			ग_लिखोl(0x01, rc_dev->rx_base + IRB_RX_EN);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(st_rc_pm_ops, st_rc_suspend, st_rc_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id st_rc_match[] = अणु
	अणु .compatible = "st,comms-irb", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, st_rc_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver st_rc_driver = अणु
	.driver = अणु
		.name = IR_ST_NAME,
		.of_match_table = of_match_ptr(st_rc_match),
		.pm     = &st_rc_pm_ops,
	पूर्ण,
	.probe = st_rc_probe,
	.हटाओ = st_rc_हटाओ,
पूर्ण;

module_platक्रमm_driver(st_rc_driver);

MODULE_DESCRIPTION("RC Transceiver driver for STMicroelectronics platforms");
MODULE_AUTHOR("STMicroelectronics (R&D) Ltd");
MODULE_LICENSE("GPL");
