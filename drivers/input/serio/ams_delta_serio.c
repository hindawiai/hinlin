<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Amstrad E3 (Delta) keyboard port driver
 *
 *  Copyright (c) 2006 Matt Callow
 *  Copyright (c) 2010 Janusz Krzysztofik
 *
 * Thanks to Clअगरf Lawson क्रम his help
 *
 * The Amstrad Delta keyboard (aka mailboard) uses normal PC-AT style serial
 * transmission.  The keyboard port is क्रमmed of two GPIO lines, क्रम घड़ी
 * and data.  Due to strict timing requirements of the पूर्णांकerface,
 * the serial data stream is पढ़ो and processed by a FIQ handler.
 * The resulting words are fetched by this driver from a circular buffer.
 *
 * Standard AT keyboard driver (atkbd) is used क्रम handling the keyboard data.
 * However, when used with the E3 mailboard that producecs non-standard
 * scancodes, a custom key table must be prepared and loaded from userspace.
 */
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_data/ams-delta-fiq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_NAME	"ams-delta-serio"

MODULE_AUTHOR("Matt Callow");
MODULE_DESCRIPTION("AMS Delta (E3) keyboard port driver");
MODULE_LICENSE("GPL");

काष्ठा ams_delta_serio अणु
	काष्ठा serio *serio;
	काष्ठा regulator *vcc;
	अचिन्हित पूर्णांक *fiq_buffer;
पूर्ण;

अटल पूर्णांक check_data(काष्ठा serio *serio, पूर्णांक data)
अणु
	पूर्णांक i, parity = 0;

	/* check valid stop bit */
	अगर (!(data & 0x400)) अणु
		dev_warn(&serio->dev, "invalid stop bit, data=0x%X\n", data);
		वापस SERIO_FRAME;
	पूर्ण
	/* calculate the parity */
	क्रम (i = 1; i < 10; i++) अणु
		अगर (data & (1 << i))
			parity++;
	पूर्ण
	/* it should be odd */
	अगर (!(parity & 0x01)) अणु
		dev_warn(&serio->dev,
			 "parity check failed, data=0x%X parity=0x%X\n", data,
			 parity);
		वापस SERIO_PARITY;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t ams_delta_serio_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ams_delta_serio *priv = dev_id;
	पूर्णांक *circ_buff = &priv->fiq_buffer[FIQ_CIRC_BUFF];
	पूर्णांक data, dfl;
	u8 scancode;

	priv->fiq_buffer[FIQ_IRQ_PEND] = 0;

	/*
	 * Read data from the circular buffer, check it
	 * and then pass it on the serio
	 */
	जबतक (priv->fiq_buffer[FIQ_KEYS_CNT] > 0) अणु

		data = circ_buff[priv->fiq_buffer[FIQ_HEAD_OFFSET]++];
		priv->fiq_buffer[FIQ_KEYS_CNT]--;
		अगर (priv->fiq_buffer[FIQ_HEAD_OFFSET] ==
		    priv->fiq_buffer[FIQ_BUF_LEN])
			priv->fiq_buffer[FIQ_HEAD_OFFSET] = 0;

		dfl = check_data(priv->serio, data);
		scancode = (u8) (data >> 1) & 0xFF;
		serio_पूर्णांकerrupt(priv->serio, scancode, dfl);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ams_delta_serio_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा ams_delta_serio *priv = serio->port_data;

	/* enable keyboard */
	वापस regulator_enable(priv->vcc);
पूर्ण

अटल व्योम ams_delta_serio_बंद(काष्ठा serio *serio)
अणु
	काष्ठा ams_delta_serio *priv = serio->port_data;

	/* disable keyboard */
	regulator_disable(priv->vcc);
पूर्ण

अटल पूर्णांक ams_delta_serio_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ams_delta_serio *priv;
	काष्ठा serio *serio;
	पूर्णांक irq, err;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->fiq_buffer = pdev->dev.platक्रमm_data;
	अगर (!priv->fiq_buffer)
		वापस -EINVAL;

	priv->vcc = devm_regulator_get(&pdev->dev, "vcc");
	अगर (IS_ERR(priv->vcc)) अणु
		err = PTR_ERR(priv->vcc);
		dev_err(&pdev->dev, "regulator request failed (%d)\n", err);
		/*
		 * When running on a non-dt platक्रमm and requested regulator
		 * is not available, devm_regulator_get() never वापसs
		 * -EPROBE_DEFER as it is not able to justअगरy अगर the regulator
		 * may still appear later.  On the other hand, the board can
		 * still set full स्थिरriants flag at late_initcall in order
		 * to inकाष्ठा devm_regulator_get() to वापसn a dummy one
		 * अगर sufficient.  Hence, अगर we get -ENODEV here, let's convert
		 * it to -EPROBE_DEFER and रुको क्रम the board to decide or
		 * let Deferred Probe infraकाष्ठाure handle this error.
		 */
		अगर (err == -ENODEV)
			err = -EPROBE_DEFER;
		वापस err;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	err = devm_request_irq(&pdev->dev, irq, ams_delta_serio_पूर्णांकerrupt,
			       IRQ_TYPE_EDGE_RISING, DRIVER_NAME, priv);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "IRQ request failed (%d)\n", err);
		वापस err;
	पूर्ण

	serio = kzalloc(माप(*serio), GFP_KERNEL);
	अगर (!serio)
		वापस -ENOMEM;

	priv->serio = serio;

	serio->id.type = SERIO_8042;
	serio->खोलो = ams_delta_serio_खोलो;
	serio->बंद = ams_delta_serio_बंद;
	strlcpy(serio->name, "AMS DELTA keyboard adapter", माप(serio->name));
	strlcpy(serio->phys, dev_name(&pdev->dev), माप(serio->phys));
	serio->dev.parent = &pdev->dev;
	serio->port_data = priv;

	serio_रेजिस्टर_port(serio);

	platक्रमm_set_drvdata(pdev, priv);

	dev_info(&serio->dev, "%s\n", serio->name);

	वापस 0;
पूर्ण

अटल पूर्णांक ams_delta_serio_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ams_delta_serio *priv = platक्रमm_get_drvdata(pdev);

	serio_unरेजिस्टर_port(priv->serio);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ams_delta_serio_driver = अणु
	.probe	= ams_delta_serio_init,
	.हटाओ	= ams_delta_serio_निकास,
	.driver	= अणु
		.name	= DRIVER_NAME
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ams_delta_serio_driver);
