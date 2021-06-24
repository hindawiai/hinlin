<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015-2016 Red Hat
 * Copyright (C) 2015 Lyude Paul <thatslyude@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/serपन.स>
#समावेश <linux/notअगरier.h>
#समावेश "rmi_driver.h"

#घोषणा RMI_F03_RX_DATA_OFB		0x01
#घोषणा RMI_F03_OB_SIZE			2

#घोषणा RMI_F03_OB_OFFSET		2
#घोषणा RMI_F03_OB_DATA_OFFSET		1
#घोषणा RMI_F03_OB_FLAG_TIMEOUT		BIT(6)
#घोषणा RMI_F03_OB_FLAG_PARITY		BIT(7)

#घोषणा RMI_F03_DEVICE_COUNT		0x07
#घोषणा RMI_F03_BYTES_PER_DEVICE	0x07
#घोषणा RMI_F03_BYTES_PER_DEVICE_SHIFT	4
#घोषणा RMI_F03_QUEUE_LENGTH		0x0F

#घोषणा PSMOUSE_OOB_EXTRA_BTNS		0x01

काष्ठा f03_data अणु
	काष्ठा rmi_function *fn;

	काष्ठा serio *serio;
	bool serio_रेजिस्टरed;

	अचिन्हित पूर्णांक overग_लिखो_buttons;

	u8 device_count;
	u8 rx_queue_length;
पूर्ण;

पूर्णांक rmi_f03_overग_लिखो_button(काष्ठा rmi_function *fn, अचिन्हित पूर्णांक button,
			     पूर्णांक value)
अणु
	काष्ठा f03_data *f03 = dev_get_drvdata(&fn->dev);
	अचिन्हित पूर्णांक bit;

	अगर (button < BTN_LEFT || button > BTN_MIDDLE)
		वापस -EINVAL;

	bit = BIT(button - BTN_LEFT);

	अगर (value)
		f03->overग_लिखो_buttons |= bit;
	अन्यथा
		f03->overग_लिखो_buttons &= ~bit;

	वापस 0;
पूर्ण

व्योम rmi_f03_commit_buttons(काष्ठा rmi_function *fn)
अणु
	काष्ठा f03_data *f03 = dev_get_drvdata(&fn->dev);
	काष्ठा serio *serio = f03->serio;

	serio_छोड़ो_rx(serio);
	अगर (serio->drv) अणु
		serio->drv->पूर्णांकerrupt(serio, PSMOUSE_OOB_EXTRA_BTNS,
				      SERIO_OOB_DATA);
		serio->drv->पूर्णांकerrupt(serio, f03->overग_लिखो_buttons,
				      SERIO_OOB_DATA);
	पूर्ण
	serio_जारी_rx(serio);
पूर्ण

अटल पूर्णांक rmi_f03_pt_ग_लिखो(काष्ठा serio *id, अचिन्हित अक्षर val)
अणु
	काष्ठा f03_data *f03 = id->port_data;
	पूर्णांक error;

	rmi_dbg(RMI_DEBUG_FN, &f03->fn->dev,
		"%s: Wrote %.2hhx to PS/2 passthrough address",
		__func__, val);

	error = rmi_ग_लिखो(f03->fn->rmi_dev, f03->fn->fd.data_base_addr, val);
	अगर (error) अणु
		dev_err(&f03->fn->dev,
			"%s: Failed to write to F03 TX register (%d).\n",
			__func__, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f03_initialize(काष्ठा f03_data *f03)
अणु
	काष्ठा rmi_function *fn = f03->fn;
	काष्ठा device *dev = &fn->dev;
	पूर्णांक error;
	u8 bytes_per_device;
	u8 query1;
	u8 query2[RMI_F03_DEVICE_COUNT * RMI_F03_BYTES_PER_DEVICE];
	माप_प्रकार query2_len;

	error = rmi_पढ़ो(fn->rmi_dev, fn->fd.query_base_addr, &query1);
	अगर (error) अणु
		dev_err(dev, "Failed to read query register (%d).\n", error);
		वापस error;
	पूर्ण

	f03->device_count = query1 & RMI_F03_DEVICE_COUNT;
	bytes_per_device = (query1 >> RMI_F03_BYTES_PER_DEVICE_SHIFT) &
				RMI_F03_BYTES_PER_DEVICE;

	query2_len = f03->device_count * bytes_per_device;

	/*
	 * The first generation of image sensors करोn't have a second part to
	 * their f03 query, as such we have to set some of these values manually
	 */
	अगर (query2_len < 1) अणु
		f03->device_count = 1;
		f03->rx_queue_length = 7;
	पूर्ण अन्यथा अणु
		error = rmi_पढ़ो_block(fn->rmi_dev, fn->fd.query_base_addr + 1,
				       query2, query2_len);
		अगर (error) अणु
			dev_err(dev,
				"Failed to read second set of query registers (%d).\n",
				error);
			वापस error;
		पूर्ण

		f03->rx_queue_length = query2[0] & RMI_F03_QUEUE_LENGTH;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f03_pt_खोलो(काष्ठा serio *serio)
अणु
	काष्ठा f03_data *f03 = serio->port_data;
	काष्ठा rmi_function *fn = f03->fn;
	स्थिर u8 ob_len = f03->rx_queue_length * RMI_F03_OB_SIZE;
	स्थिर u16 data_addr = fn->fd.data_base_addr + RMI_F03_OB_OFFSET;
	u8 obs[RMI_F03_QUEUE_LENGTH * RMI_F03_OB_SIZE];
	पूर्णांक error;

	/*
	 * Consume any pending data. Some devices like to spam with
	 * 0xaa 0x00 announcements which may confuse us as we try to
	 * probe the device.
	 */
	error = rmi_पढ़ो_block(fn->rmi_dev, data_addr, &obs, ob_len);
	अगर (!error)
		rmi_dbg(RMI_DEBUG_FN, &fn->dev,
			"%s: Consumed %*ph (%d) from PS2 guest\n",
			__func__, ob_len, obs, ob_len);

	वापस fn->rmi_dev->driver->set_irq_bits(fn->rmi_dev, fn->irq_mask);
पूर्ण

अटल व्योम rmi_f03_pt_बंद(काष्ठा serio *serio)
अणु
	काष्ठा f03_data *f03 = serio->port_data;
	काष्ठा rmi_function *fn = f03->fn;

	fn->rmi_dev->driver->clear_irq_bits(fn->rmi_dev, fn->irq_mask);
पूर्ण

अटल पूर्णांक rmi_f03_रेजिस्टर_pt(काष्ठा f03_data *f03)
अणु
	काष्ठा serio *serio;

	serio = kzalloc(माप(काष्ठा serio), GFP_KERNEL);
	अगर (!serio)
		वापस -ENOMEM;

	serio->id.type = SERIO_PS_PSTHRU;
	serio->ग_लिखो = rmi_f03_pt_ग_लिखो;
	serio->खोलो = rmi_f03_pt_खोलो;
	serio->बंद = rmi_f03_pt_बंद;
	serio->port_data = f03;

	strlcpy(serio->name, "RMI4 PS/2 pass-through", माप(serio->name));
	snम_लिखो(serio->phys, माप(serio->phys), "%s/serio0",
		 dev_name(&f03->fn->dev));
	serio->dev.parent = &f03->fn->dev;

	f03->serio = serio;

	prपूर्णांकk(KERN_INFO "serio: %s port at %s\n",
		serio->name, dev_name(&f03->fn->dev));
	serio_रेजिस्टर_port(serio);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f03_probe(काष्ठा rmi_function *fn)
अणु
	काष्ठा device *dev = &fn->dev;
	काष्ठा f03_data *f03;
	पूर्णांक error;

	f03 = devm_kzalloc(dev, माप(काष्ठा f03_data), GFP_KERNEL);
	अगर (!f03)
		वापस -ENOMEM;

	f03->fn = fn;

	error = rmi_f03_initialize(f03);
	अगर (error < 0)
		वापस error;

	अगर (f03->device_count != 1)
		dev_warn(dev, "found %d devices on PS/2 passthrough",
			 f03->device_count);

	dev_set_drvdata(dev, f03);
	वापस 0;
पूर्ण

अटल पूर्णांक rmi_f03_config(काष्ठा rmi_function *fn)
अणु
	काष्ठा f03_data *f03 = dev_get_drvdata(&fn->dev);
	पूर्णांक error;

	अगर (!f03->serio_रेजिस्टरed) अणु
		error = rmi_f03_रेजिस्टर_pt(f03);
		अगर (error)
			वापस error;

		f03->serio_रेजिस्टरed = true;
	पूर्ण अन्यथा अणु
		/*
		 * We must be re-configuring the sensor, just enable
		 * पूर्णांकerrupts क्रम this function.
		 */
		fn->rmi_dev->driver->set_irq_bits(fn->rmi_dev, fn->irq_mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t rmi_f03_attention(पूर्णांक irq, व्योम *ctx)
अणु
	काष्ठा rmi_function *fn = ctx;
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	काष्ठा f03_data *f03 = dev_get_drvdata(&fn->dev);
	स्थिर u16 data_addr = fn->fd.data_base_addr + RMI_F03_OB_OFFSET;
	स्थिर u8 ob_len = f03->rx_queue_length * RMI_F03_OB_SIZE;
	u8 obs[RMI_F03_QUEUE_LENGTH * RMI_F03_OB_SIZE];
	u8 ob_status;
	u8 ob_data;
	अचिन्हित पूर्णांक serio_flags;
	पूर्णांक i;
	पूर्णांक error;

	अगर (drvdata->attn_data.data) अणु
		/* First grab the data passed by the transport device */
		अगर (drvdata->attn_data.size < ob_len) अणु
			dev_warn(&fn->dev, "F03 interrupted, but data is missing!\n");
			वापस IRQ_HANDLED;
		पूर्ण

		स_नकल(obs, drvdata->attn_data.data, ob_len);

		drvdata->attn_data.data += ob_len;
		drvdata->attn_data.size -= ob_len;
	पूर्ण अन्यथा अणु
		/* Grab all of the data रेजिस्टरs, and check them क्रम data */
		error = rmi_पढ़ो_block(fn->rmi_dev, data_addr, &obs, ob_len);
		अगर (error) अणु
			dev_err(&fn->dev,
				"%s: Failed to read F03 output buffers: %d\n",
				__func__, error);
			serio_पूर्णांकerrupt(f03->serio, 0, SERIO_TIMEOUT);
			वापस IRQ_RETVAL(error);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ob_len; i += RMI_F03_OB_SIZE) अणु
		ob_status = obs[i];
		ob_data = obs[i + RMI_F03_OB_DATA_OFFSET];
		serio_flags = 0;

		अगर (!(ob_status & RMI_F03_RX_DATA_OFB))
			जारी;

		अगर (ob_status & RMI_F03_OB_FLAG_TIMEOUT)
			serio_flags |= SERIO_TIMEOUT;
		अगर (ob_status & RMI_F03_OB_FLAG_PARITY)
			serio_flags |= SERIO_PARITY;

		rmi_dbg(RMI_DEBUG_FN, &fn->dev,
			"%s: Received %.2hhx from PS2 guest T: %c P: %c\n",
			__func__, ob_data,
			serio_flags & SERIO_TIMEOUT ?  'Y' : 'N',
			serio_flags & SERIO_PARITY ? 'Y' : 'N');

		serio_पूर्णांकerrupt(f03->serio, ob_data, serio_flags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rmi_f03_हटाओ(काष्ठा rmi_function *fn)
अणु
	काष्ठा f03_data *f03 = dev_get_drvdata(&fn->dev);

	अगर (f03->serio_रेजिस्टरed)
		serio_unरेजिस्टर_port(f03->serio);
पूर्ण

काष्ठा rmi_function_handler rmi_f03_handler = अणु
	.driver = अणु
		.name = "rmi4_f03",
	पूर्ण,
	.func = 0x03,
	.probe = rmi_f03_probe,
	.config = rmi_f03_config,
	.attention = rmi_f03_attention,
	.हटाओ = rmi_f03_हटाओ,
पूर्ण;

MODULE_AUTHOR("Lyude Paul <thatslyude@gmail.com>");
MODULE_DESCRIPTION("RMI F03 module");
MODULE_LICENSE("GPL");
