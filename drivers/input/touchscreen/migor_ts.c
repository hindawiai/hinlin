<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Touch Screen driver क्रम Renesas MIGO-R Platक्रमm
 *
 * Copyright (c) 2008 Magnus Damm
 * Copyright (c) 2007 Ujjwal Pande <ujjwal@kenati.com>,
 *  Kenati Technologies Pvt Ltd.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/समयr.h>

#घोषणा EVENT_PENDOWN 1
#घोषणा EVENT_REPEAT  2
#घोषणा EVENT_PENUP   3

काष्ठा migor_ts_priv अणु
	काष्ठा i2c_client *client;
	काष्ठा input_dev *input;
	पूर्णांक irq;
पूर्ण;

अटल स्थिर u_पूर्णांक8_t migor_ts_ena_seq[17] = अणु 0x33, 0x22, 0x11,
					       0x01, 0x06, 0x07, पूर्ण;
अटल स्थिर u_पूर्णांक8_t migor_ts_dis_seq[17] = अणु पूर्ण;

अटल irqवापस_t migor_ts_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा migor_ts_priv *priv = dev_id;
	अचिन्हित लघु xpos, ypos;
	अचिन्हित अक्षर event;
	u_पूर्णांक8_t buf[16];

	/*
	 * The touch screen controller chip is hooked up to the CPU
	 * using I2C and a single पूर्णांकerrupt line. The पूर्णांकerrupt line
	 * is pulled low whenever someone taps the screen. To deनिश्चित
	 * the पूर्णांकerrupt line we need to acknowledge the पूर्णांकerrupt by
	 * communicating with the controller over the slow i2c bus.
	 *
	 * Since I2C bus controller may sleep we are using thपढ़ोed
	 * IRQ here.
	 */

	स_रखो(buf, 0, माप(buf));

	/* Set Index 0 */
	buf[0] = 0;
	अगर (i2c_master_send(priv->client, buf, 1) != 1) अणु
		dev_err(&priv->client->dev, "Unable to write i2c index\n");
		जाओ out;
	पूर्ण

	/* Now करो Page Read */
	अगर (i2c_master_recv(priv->client, buf, माप(buf)) != माप(buf)) अणु
		dev_err(&priv->client->dev, "Unable to read i2c page\n");
		जाओ out;
	पूर्ण

	ypos = ((buf[9] & 0x03) << 8 | buf[8]);
	xpos = ((buf[11] & 0x03) << 8 | buf[10]);
	event = buf[12];

	चयन (event) अणु
	हाल EVENT_PENDOWN:
	हाल EVENT_REPEAT:
		input_report_key(priv->input, BTN_TOUCH, 1);
		input_report_असल(priv->input, ABS_X, ypos); /*X-Y swap*/
		input_report_असल(priv->input, ABS_Y, xpos);
		input_sync(priv->input);
		अवरोध;

	हाल EVENT_PENUP:
		input_report_key(priv->input, BTN_TOUCH, 0);
		input_sync(priv->input);
		अवरोध;
	पूर्ण

 out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक migor_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा migor_ts_priv *priv = input_get_drvdata(dev);
	काष्ठा i2c_client *client = priv->client;
	पूर्णांक count;

	/* enable controller */
	count = i2c_master_send(client, migor_ts_ena_seq,
				माप(migor_ts_ena_seq));
	अगर (count != माप(migor_ts_ena_seq)) अणु
		dev_err(&client->dev, "Unable to enable touchscreen.\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम migor_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा migor_ts_priv *priv = input_get_drvdata(dev);
	काष्ठा i2c_client *client = priv->client;

	disable_irq(priv->irq);

	/* disable controller */
	i2c_master_send(client, migor_ts_dis_seq, माप(migor_ts_dis_seq));

	enable_irq(priv->irq);
पूर्ण

अटल पूर्णांक migor_ts_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *idp)
अणु
	काष्ठा migor_ts_priv *priv;
	काष्ठा input_dev *input;
	पूर्णांक error;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	input = input_allocate_device();
	अगर (!priv || !input) अणु
		dev_err(&client->dev, "failed to allocate memory\n");
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	priv->client = client;
	priv->input = input;
	priv->irq = client->irq;

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	__set_bit(BTN_TOUCH, input->keybit);

	input_set_असल_params(input, ABS_X, 95, 955, 0, 0);
	input_set_असल_params(input, ABS_Y, 85, 935, 0, 0);

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;

	input->खोलो = migor_ts_खोलो;
	input->बंद = migor_ts_बंद;

	input_set_drvdata(input, priv);

	error = request_thपढ़ोed_irq(priv->irq, शून्य, migor_ts_isr,
                                     IRQF_TRIGGER_LOW | IRQF_ONESHOT,
                                     client->name, priv);
	अगर (error) अणु
		dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");
		जाओ err_मुक्त_mem;
	पूर्ण

	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ err_मुक्त_irq;

	i2c_set_clientdata(client, priv);
	device_init_wakeup(&client->dev, 1);

	वापस 0;

 err_मुक्त_irq:
	मुक्त_irq(priv->irq, priv);
 err_मुक्त_mem:
	input_मुक्त_device(input);
	kमुक्त(priv);
	वापस error;
पूर्ण

अटल पूर्णांक migor_ts_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा migor_ts_priv *priv = i2c_get_clientdata(client);

	मुक्त_irq(priv->irq, priv);
	input_unरेजिस्टर_device(priv->input);
	kमुक्त(priv);

	dev_set_drvdata(&client->dev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused migor_ts_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा migor_ts_priv *priv = i2c_get_clientdata(client);

	अगर (device_may_wakeup(&client->dev))
		enable_irq_wake(priv->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused migor_ts_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा migor_ts_priv *priv = i2c_get_clientdata(client);

	अगर (device_may_wakeup(&client->dev))
		disable_irq_wake(priv->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(migor_ts_pm, migor_ts_suspend, migor_ts_resume);

अटल स्थिर काष्ठा i2c_device_id migor_ts_id[] = अणु
	अणु "migor_ts", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, migor_ts_id);

अटल काष्ठा i2c_driver migor_ts_driver = अणु
	.driver = अणु
		.name = "migor_ts",
		.pm = &migor_ts_pm,
	पूर्ण,
	.probe = migor_ts_probe,
	.हटाओ = migor_ts_हटाओ,
	.id_table = migor_ts_id,
पूर्ण;

module_i2c_driver(migor_ts_driver);

MODULE_DESCRIPTION("MigoR Touchscreen driver");
MODULE_AUTHOR("Magnus Damm <damm@opensource.se>");
MODULE_LICENSE("GPL");
