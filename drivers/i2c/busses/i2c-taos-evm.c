<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the TAOS evaluation modules
 * These devices include an I2C master which can be controlled over the
 * serial port.
 *
 * Copyright (C) 2007 Jean Delvare <jdelvare@suse.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>

#घोषणा TAOS_BUFFER_SIZE	63

#घोषणा TAOS_STATE_INIT		0
#घोषणा TAOS_STATE_IDLE		1
#घोषणा TAOS_STATE_खातापूर्णF		2
#घोषणा TAOS_STATE_RECV		3

#घोषणा TAOS_CMD_RESET		0x12
#घोषणा TAOS_CMD_ECHO_ON	'+'
#घोषणा TAOS_CMD_ECHO_OFF	'-'

अटल DECLARE_WAIT_QUEUE_HEAD(wq);

काष्ठा taos_data अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_client *client;
	पूर्णांक state;
	u8 addr;		/* last used address */
	अचिन्हित अक्षर buffer[TAOS_BUFFER_SIZE];
	अचिन्हित पूर्णांक pos;	/* position inside the buffer */
पूर्ण;

/* TAOS TSL2550 EVM */
अटल स्थिर काष्ठा i2c_board_info tsl2550_info = अणु
	I2C_BOARD_INFO("tsl2550", 0x39),
पूर्ण;

/* Instantiate i2c devices based on the adapter name */
अटल काष्ठा i2c_client *taos_instantiate_device(काष्ठा i2c_adapter *adapter)
अणु
	अगर (!म_भेदन(adapter->name, "TAOS TSL2550 EVM", 16)) अणु
		dev_info(&adapter->dev, "Instantiating device %s at 0x%02x\n",
			tsl2550_info.type, tsl2550_info.addr);
		वापस i2c_new_client_device(adapter, &tsl2550_info);
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक taos_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
			   अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
			   पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा serio *serio = adapter->algo_data;
	काष्ठा taos_data *taos = serio_get_drvdata(serio);
	अक्षर *p;

	/* Encode our transaction. "@" is क्रम the device address, "$" क्रम the
	   SMBus command and "#" क्रम the data. */
	p = taos->buffer;

	/* The device remembers the last used address, no need to send it
	   again अगर it's the same */
	अगर (addr != taos->addr)
		p += प्र_लिखो(p, "@%02X", addr);

	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			प्र_लिखो(p, "$#%02X", command);
		अन्यथा
			प्र_लिखो(p, "$");
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			प्र_लिखो(p, "$%02X#%02X", command, data->byte);
		अन्यथा
			प्र_लिखो(p, "$%02X", command);
		अवरोध;
	शेष:
		dev_warn(&adapter->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Send the transaction to the TAOS EVM */
	dev_dbg(&adapter->dev, "Command buffer: %s\n", taos->buffer);
	क्रम (p = taos->buffer; *p; p++)
		serio_ग_लिखो(serio, *p);

	taos->addr = addr;

	/* Start the transaction and पढ़ो the answer */
	taos->pos = 0;
	taos->state = TAOS_STATE_RECV;
	serio_ग_लिखो(serio, पढ़ो_ग_लिखो == I2C_SMBUS_WRITE ? '>' : '<');
	रुको_event_पूर्णांकerruptible_समयout(wq, taos->state == TAOS_STATE_IDLE,
					 msecs_to_jअगरfies(150));
	अगर (taos->state != TAOS_STATE_IDLE
	 || taos->pos != 5) अणु
		dev_err(&adapter->dev, "Transaction timeout (pos=%d)\n",
			taos->pos);
		वापस -EIO;
	पूर्ण
	dev_dbg(&adapter->dev, "Answer buffer: %s\n", taos->buffer);

	/* Interpret the वापसed string */
	p = taos->buffer + 1;
	p[3] = '\0';
	अगर (!म_भेद(p, "NAK"))
		वापस -ENODEV;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		अगर (!म_भेद(p, "ACK"))
			वापस 0;
	पूर्ण अन्यथा अणु
		अगर (p[0] == 'x') अणु
			/*
			 * Voluntarily dropping error code of kstrtou8 since all
			 * error code that it could वापस are invalid according
			 * to Documentation/i2c/fault-codes.rst.
			 */
			अगर (kstrtou8(p + 1, 16, &data->byte))
				वापस -EPROTO;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल u32 taos_smbus_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm taos_algorithm = अणु
	.smbus_xfer	= taos_smbus_xfer,
	.functionality	= taos_smbus_func,
पूर्ण;

अटल irqवापस_t taos_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा taos_data *taos = serio_get_drvdata(serio);

	चयन (taos->state) अणु
	हाल TAOS_STATE_INIT:
		taos->buffer[taos->pos++] = data;
		अगर (data == ':'
		 || taos->pos == TAOS_BUFFER_SIZE - 1) अणु
			taos->buffer[taos->pos] = '\0';
			taos->state = TAOS_STATE_IDLE;
			wake_up_पूर्णांकerruptible(&wq);
		पूर्ण
		अवरोध;
	हाल TAOS_STATE_खातापूर्णF:
		taos->state = TAOS_STATE_IDLE;
		wake_up_पूर्णांकerruptible(&wq);
		अवरोध;
	हाल TAOS_STATE_RECV:
		taos->buffer[taos->pos++] = data;
		अगर (data == ']') अणु
			taos->buffer[taos->pos] = '\0';
			taos->state = TAOS_STATE_IDLE;
			wake_up_पूर्णांकerruptible(&wq);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Extract the adapter name from the buffer received after reset.
   The buffer is modअगरied and a poपूर्णांकer inside the buffer is वापसed. */
अटल अक्षर *taos_adapter_name(अक्षर *buffer)
अणु
	अक्षर *start, *end;

	start = म_माला(buffer, "TAOS ");
	अगर (!start)
		वापस शून्य;

	end = म_अक्षर(start, '\r');
	अगर (!end)
		वापस शून्य;
	*end = '\0';

	वापस start;
पूर्ण

अटल पूर्णांक taos_connect(काष्ठा serio *serio, काष्ठा serio_driver *drv)
अणु
	काष्ठा taos_data *taos;
	काष्ठा i2c_adapter *adapter;
	अक्षर *name;
	पूर्णांक err;

	taos = kzalloc(माप(काष्ठा taos_data), GFP_KERNEL);
	अगर (!taos) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	taos->state = TAOS_STATE_INIT;
	serio_set_drvdata(serio, taos);

	err = serio_खोलो(serio, drv);
	अगर (err)
		जाओ निकास_kमुक्त;

	adapter = &taos->adapter;
	adapter->owner = THIS_MODULE;
	adapter->algo = &taos_algorithm;
	adapter->algo_data = serio;
	adapter->dev.parent = &serio->dev;

	/* Reset the TAOS evaluation module to identअगरy it */
	serio_ग_लिखो(serio, TAOS_CMD_RESET);
	रुको_event_पूर्णांकerruptible_समयout(wq, taos->state == TAOS_STATE_IDLE,
					 msecs_to_jअगरfies(2000));

	अगर (taos->state != TAOS_STATE_IDLE) अणु
		err = -ENODEV;
		dev_err(&serio->dev, "TAOS EVM reset failed (state=%d, "
			"pos=%d)\n", taos->state, taos->pos);
		जाओ निकास_बंद;
	पूर्ण

	name = taos_adapter_name(taos->buffer);
	अगर (!name) अणु
		err = -ENODEV;
		dev_err(&serio->dev, "TAOS EVM identification failed\n");
		जाओ निकास_बंद;
	पूर्ण
	strlcpy(adapter->name, name, माप(adapter->name));

	/* Turn echo off क्रम better perक्रमmance */
	taos->state = TAOS_STATE_खातापूर्णF;
	serio_ग_लिखो(serio, TAOS_CMD_ECHO_OFF);

	रुको_event_पूर्णांकerruptible_समयout(wq, taos->state == TAOS_STATE_IDLE,
					 msecs_to_jअगरfies(250));
	अगर (taos->state != TAOS_STATE_IDLE) अणु
		err = -ENODEV;
		dev_err(&serio->dev, "TAOS EVM echo off failed "
			"(state=%d)\n", taos->state);
		जाओ निकास_बंद;
	पूर्ण

	err = i2c_add_adapter(adapter);
	अगर (err)
		जाओ निकास_बंद;
	dev_info(&serio->dev, "Connected to TAOS EVM\n");

	taos->client = taos_instantiate_device(adapter);
	वापस 0;

 निकास_बंद:
	serio_बंद(serio);
 निकास_kमुक्त:
	kमुक्त(taos);
 निकास:
	वापस err;
पूर्ण

अटल व्योम taos_disconnect(काष्ठा serio *serio)
अणु
	काष्ठा taos_data *taos = serio_get_drvdata(serio);

	i2c_unरेजिस्टर_device(taos->client);
	i2c_del_adapter(&taos->adapter);
	serio_बंद(serio);
	kमुक्त(taos);

	dev_info(&serio->dev, "Disconnected from TAOS EVM\n");
पूर्ण

अटल स्थिर काष्ठा serio_device_id taos_serio_ids[] = अणु
	अणु
		.type	= SERIO_RS232,
		.proto	= SERIO_TAOSEVM,
		.id	= SERIO_ANY,
		.extra	= SERIO_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(serio, taos_serio_ids);

अटल काष्ठा serio_driver taos_drv = अणु
	.driver		= अणु
		.name	= "taos-evm",
	पूर्ण,
	.description	= "TAOS evaluation module driver",
	.id_table	= taos_serio_ids,
	.connect	= taos_connect,
	.disconnect	= taos_disconnect,
	.पूर्णांकerrupt	= taos_पूर्णांकerrupt,
पूर्ण;

module_serio_driver(taos_drv);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("TAOS evaluation module driver");
MODULE_LICENSE("GPL");
