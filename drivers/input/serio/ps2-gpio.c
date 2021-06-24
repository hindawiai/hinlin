<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * GPIO based serio bus driver क्रम bit banging the PS/2 protocol
 *
 * Author: Danilo Krummrich <danilokrummrich@dk-develop.de>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/serपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/preempt.h>
#समावेश <linux/property.h>
#समावेश <linux/of.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>

#घोषणा DRIVER_NAME		"ps2-gpio"

#घोषणा PS2_MODE_RX		0
#घोषणा PS2_MODE_TX		1

#घोषणा PS2_START_BIT		0
#घोषणा PS2_DATA_BIT0		1
#घोषणा PS2_DATA_BIT1		2
#घोषणा PS2_DATA_BIT2		3
#घोषणा PS2_DATA_BIT3		4
#घोषणा PS2_DATA_BIT4		5
#घोषणा PS2_DATA_BIT5		6
#घोषणा PS2_DATA_BIT6		7
#घोषणा PS2_DATA_BIT7		8
#घोषणा PS2_PARITY_BIT		9
#घोषणा PS2_STOP_BIT		10
#घोषणा PS2_TX_TIMEOUT		11
#घोषणा PS2_ACK_BIT		12

#घोषणा PS2_DEV_RET_ACK		0xfa
#घोषणा PS2_DEV_RET_NACK	0xfe

#घोषणा PS2_CMD_RESEND		0xfe

काष्ठा ps2_gpio_data अणु
	काष्ठा device *dev;
	काष्ठा serio *serio;
	अचिन्हित अक्षर mode;
	काष्ठा gpio_desc *gpio_clk;
	काष्ठा gpio_desc *gpio_data;
	bool ग_लिखो_enable;
	पूर्णांक irq;
	अचिन्हित अक्षर rx_cnt;
	अचिन्हित अक्षर rx_byte;
	अचिन्हित अक्षर tx_cnt;
	अचिन्हित अक्षर tx_byte;
	काष्ठा completion tx_करोne;
	काष्ठा mutex tx_mutex;
	काष्ठा delayed_work tx_work;
पूर्ण;

अटल पूर्णांक ps2_gpio_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा ps2_gpio_data *drvdata = serio->port_data;

	enable_irq(drvdata->irq);
	वापस 0;
पूर्ण

अटल व्योम ps2_gpio_बंद(काष्ठा serio *serio)
अणु
	काष्ठा ps2_gpio_data *drvdata = serio->port_data;

	flush_delayed_work(&drvdata->tx_work);
	disable_irq(drvdata->irq);
पूर्ण

अटल पूर्णांक __ps2_gpio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर val)
अणु
	काष्ठा ps2_gpio_data *drvdata = serio->port_data;

	disable_irq_nosync(drvdata->irq);
	gpiod_direction_output(drvdata->gpio_clk, 0);

	drvdata->mode = PS2_MODE_TX;
	drvdata->tx_byte = val;

	schedule_delayed_work(&drvdata->tx_work, usecs_to_jअगरfies(200));

	वापस 0;
पूर्ण

अटल पूर्णांक ps2_gpio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर val)
अणु
	काष्ठा ps2_gpio_data *drvdata = serio->port_data;
	पूर्णांक ret = 0;

	अगर (in_task()) अणु
		mutex_lock(&drvdata->tx_mutex);
		__ps2_gpio_ग_लिखो(serio, val);
		अगर (!रुको_क्रम_completion_समयout(&drvdata->tx_करोne,
						 msecs_to_jअगरfies(10000)))
			ret = SERIO_TIMEOUT;
		mutex_unlock(&drvdata->tx_mutex);
	पूर्ण अन्यथा अणु
		__ps2_gpio_ग_लिखो(serio, val);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ps2_gpio_tx_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा ps2_gpio_data *drvdata = container_of(dwork,
						    काष्ठा ps2_gpio_data,
						    tx_work);

	enable_irq(drvdata->irq);
	gpiod_direction_output(drvdata->gpio_data, 0);
	gpiod_direction_input(drvdata->gpio_clk);
पूर्ण

अटल irqवापस_t ps2_gpio_irq_rx(काष्ठा ps2_gpio_data *drvdata)
अणु
	अचिन्हित अक्षर byte, cnt;
	पूर्णांक data;
	पूर्णांक rxflags = 0;
	अटल अचिन्हित दीर्घ old_jअगरfies;

	byte = drvdata->rx_byte;
	cnt = drvdata->rx_cnt;

	अगर (old_jअगरfies == 0)
		old_jअगरfies = jअगरfies;

	अगर ((jअगरfies - old_jअगरfies) > usecs_to_jअगरfies(100)) अणु
		dev_err(drvdata->dev,
			"RX: timeout, probably we missed an interrupt\n");
		जाओ err;
	पूर्ण
	old_jअगरfies = jअगरfies;

	data = gpiod_get_value(drvdata->gpio_data);
	अगर (unlikely(data < 0)) अणु
		dev_err(drvdata->dev, "RX: failed to get data gpio val: %d\n",
			data);
		जाओ err;
	पूर्ण

	चयन (cnt) अणु
	हाल PS2_START_BIT:
		/* start bit should be low */
		अगर (unlikely(data)) अणु
			dev_err(drvdata->dev, "RX: start bit should be low\n");
			जाओ err;
		पूर्ण
		अवरोध;
	हाल PS2_DATA_BIT0:
	हाल PS2_DATA_BIT1:
	हाल PS2_DATA_BIT2:
	हाल PS2_DATA_BIT3:
	हाल PS2_DATA_BIT4:
	हाल PS2_DATA_BIT5:
	हाल PS2_DATA_BIT6:
	हाल PS2_DATA_BIT7:
		/* processing data bits */
		अगर (data)
			byte |= (data << (cnt - 1));
		अवरोध;
	हाल PS2_PARITY_BIT:
		/* check odd parity */
		अगर (!((hweight8(byte) & 1) ^ data)) अणु
			rxflags |= SERIO_PARITY;
			dev_warn(drvdata->dev, "RX: parity error\n");
			अगर (!drvdata->ग_लिखो_enable)
				जाओ err;
		पूर्ण

		/* Do not send spurious ACK's and NACK's when ग_लिखो fn is
		 * not provided.
		 */
		अगर (!drvdata->ग_लिखो_enable) अणु
			अगर (byte == PS2_DEV_RET_NACK)
				जाओ err;
			अन्यथा अगर (byte == PS2_DEV_RET_ACK)
				अवरोध;
		पूर्ण

		/* Let's send the data without रुकोing क्रम the stop bit to be
		 * sent. It may happen that we miss the stop bit. When this
		 * happens we have no way to recover from this, certainly
		 * missing the parity bit would be recognized when processing
		 * the stop bit. When missing both, data is lost.
		 */
		serio_पूर्णांकerrupt(drvdata->serio, byte, rxflags);
		dev_dbg(drvdata->dev, "RX: sending byte 0x%x\n", byte);
		अवरोध;
	हाल PS2_STOP_BIT:
		/* stop bit should be high */
		अगर (unlikely(!data)) अणु
			dev_err(drvdata->dev, "RX: stop bit should be high\n");
			जाओ err;
		पूर्ण
		cnt = byte = 0;
		old_jअगरfies = 0;
		जाओ end; /* success */
	शेष:
		dev_err(drvdata->dev, "RX: got out of sync with the device\n");
		जाओ err;
	पूर्ण

	cnt++;
	जाओ end; /* success */

err:
	cnt = byte = 0;
	old_jअगरfies = 0;
	__ps2_gpio_ग_लिखो(drvdata->serio, PS2_CMD_RESEND);
end:
	drvdata->rx_cnt = cnt;
	drvdata->rx_byte = byte;
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ps2_gpio_irq_tx(काष्ठा ps2_gpio_data *drvdata)
अणु
	अचिन्हित अक्षर byte, cnt;
	पूर्णांक data;
	अटल अचिन्हित दीर्घ old_jअगरfies;

	cnt = drvdata->tx_cnt;
	byte = drvdata->tx_byte;

	अगर (old_jअगरfies == 0)
		old_jअगरfies = jअगरfies;

	अगर ((jअगरfies - old_jअगरfies) > usecs_to_jअगरfies(100)) अणु
		dev_err(drvdata->dev,
			"TX: timeout, probably we missed an interrupt\n");
		जाओ err;
	पूर्ण
	old_jअगरfies = jअगरfies;

	चयन (cnt) अणु
	हाल PS2_START_BIT:
		/* should never happen */
		dev_err(drvdata->dev,
			"TX: start bit should have been sent already\n");
		जाओ err;
	हाल PS2_DATA_BIT0:
	हाल PS2_DATA_BIT1:
	हाल PS2_DATA_BIT2:
	हाल PS2_DATA_BIT3:
	हाल PS2_DATA_BIT4:
	हाल PS2_DATA_BIT5:
	हाल PS2_DATA_BIT6:
	हाल PS2_DATA_BIT7:
		data = byte & BIT(cnt - 1);
		gpiod_set_value(drvdata->gpio_data, data);
		अवरोध;
	हाल PS2_PARITY_BIT:
		/* करो odd parity */
		data = !(hweight8(byte) & 1);
		gpiod_set_value(drvdata->gpio_data, data);
		अवरोध;
	हाल PS2_STOP_BIT:
		/* release data line to generate stop bit */
		gpiod_direction_input(drvdata->gpio_data);
		अवरोध;
	हाल PS2_TX_TIMEOUT:
		/* Devices generate one extra घड़ी pulse beक्रमe sending the
		 * acknowledgment.
		 */
		अवरोध;
	हाल PS2_ACK_BIT:
		gpiod_direction_input(drvdata->gpio_data);
		data = gpiod_get_value(drvdata->gpio_data);
		अगर (data) अणु
			dev_warn(drvdata->dev, "TX: received NACK, retry\n");
			जाओ err;
		पूर्ण

		drvdata->mode = PS2_MODE_RX;
		complete(&drvdata->tx_करोne);

		cnt = 1;
		old_jअगरfies = 0;
		जाओ end; /* success */
	शेष:
		/* Probably we missed the stop bit. Thereक्रमe we release data
		 * line and try again.
		 */
		gpiod_direction_input(drvdata->gpio_data);
		dev_err(drvdata->dev, "TX: got out of sync with the device\n");
		जाओ err;
	पूर्ण

	cnt++;
	जाओ end; /* success */

err:
	cnt = 1;
	old_jअगरfies = 0;
	gpiod_direction_input(drvdata->gpio_data);
	__ps2_gpio_ग_लिखो(drvdata->serio, drvdata->tx_byte);
end:
	drvdata->tx_cnt = cnt;
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ps2_gpio_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ps2_gpio_data *drvdata = dev_id;

	वापस drvdata->mode ? ps2_gpio_irq_tx(drvdata) :
		ps2_gpio_irq_rx(drvdata);
पूर्ण

अटल पूर्णांक ps2_gpio_get_props(काष्ठा device *dev,
				 काष्ठा ps2_gpio_data *drvdata)
अणु
	drvdata->gpio_data = devm_gpiod_get(dev, "data", GPIOD_IN);
	अगर (IS_ERR(drvdata->gpio_data)) अणु
		dev_err(dev, "failed to request data gpio: %ld",
			PTR_ERR(drvdata->gpio_data));
		वापस PTR_ERR(drvdata->gpio_data);
	पूर्ण

	drvdata->gpio_clk = devm_gpiod_get(dev, "clk", GPIOD_IN);
	अगर (IS_ERR(drvdata->gpio_clk)) अणु
		dev_err(dev, "failed to request clock gpio: %ld",
			PTR_ERR(drvdata->gpio_clk));
		वापस PTR_ERR(drvdata->gpio_clk);
	पूर्ण

	drvdata->ग_लिखो_enable = device_property_पढ़ो_bool(dev,
				"write-enable");

	वापस 0;
पूर्ण

अटल पूर्णांक ps2_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ps2_gpio_data *drvdata;
	काष्ठा serio *serio;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक error;

	drvdata = devm_kzalloc(dev, माप(काष्ठा ps2_gpio_data), GFP_KERNEL);
	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!drvdata || !serio) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_serio;
	पूर्ण

	error = ps2_gpio_get_props(dev, drvdata);
	अगर (error)
		जाओ err_मुक्त_serio;

	अगर (gpiod_cansleep(drvdata->gpio_data) ||
	    gpiod_cansleep(drvdata->gpio_clk)) अणु
		dev_err(dev, "GPIO data or clk are connected via slow bus\n");
		error = -EINVAL;
		जाओ err_मुक्त_serio;
	पूर्ण

	drvdata->irq = platक्रमm_get_irq(pdev, 0);
	अगर (drvdata->irq < 0) अणु
		error = drvdata->irq;
		जाओ err_मुक्त_serio;
	पूर्ण

	error = devm_request_irq(dev, drvdata->irq, ps2_gpio_irq,
				 IRQF_NO_THREAD, DRIVER_NAME, drvdata);
	अगर (error) अणु
		dev_err(dev, "failed to request irq %d: %d\n",
			drvdata->irq, error);
		जाओ err_मुक्त_serio;
	पूर्ण

	/* Keep irq disabled until serio->खोलो is called. */
	disable_irq(drvdata->irq);

	serio->id.type = SERIO_8042;
	serio->खोलो = ps2_gpio_खोलो;
	serio->बंद = ps2_gpio_बंद;
	/* Write can be enabled in platक्रमm/dt data, but possibly it will not
	 * work because of the tough timings.
	 */
	serio->ग_लिखो = drvdata->ग_लिखो_enable ? ps2_gpio_ग_लिखो : शून्य;
	serio->port_data = drvdata;
	serio->dev.parent = dev;
	strlcpy(serio->name, dev_name(dev), माप(serio->name));
	strlcpy(serio->phys, dev_name(dev), माप(serio->phys));

	drvdata->serio = serio;
	drvdata->dev = dev;
	drvdata->mode = PS2_MODE_RX;

	/* Tx count always starts at 1, as the start bit is sent implicitly by
	 * host-to-device communication initialization.
	 */
	drvdata->tx_cnt = 1;

	INIT_DELAYED_WORK(&drvdata->tx_work, ps2_gpio_tx_work_fn);
	init_completion(&drvdata->tx_करोne);
	mutex_init(&drvdata->tx_mutex);

	serio_रेजिस्टर_port(serio);
	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;	/* success */

err_मुक्त_serio:
	kमुक्त(serio);
	वापस error;
पूर्ण

अटल पूर्णांक ps2_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ps2_gpio_data *drvdata = platक्रमm_get_drvdata(pdev);

	serio_unरेजिस्टर_port(drvdata->serio);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id ps2_gpio_match[] = अणु
	अणु .compatible = "ps2-gpio", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ps2_gpio_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ps2_gpio_driver = अणु
	.probe		= ps2_gpio_probe,
	.हटाओ		= ps2_gpio_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(ps2_gpio_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ps2_gpio_driver);

MODULE_AUTHOR("Danilo Krummrich <danilokrummrich@dk-develop.de>");
MODULE_DESCRIPTION("GPIO PS2 driver");
MODULE_LICENSE("GPL v2");
