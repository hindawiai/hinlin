<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * ds2482.c - provides i2c to w1-master bridge(s)
 * Copyright (C) 2005  Ben Gardner <bgardner@wabtec.com>
 *
 * The DS2482 is a sensor chip made by Dallas Semiconductor (Maxim).
 * It is a I2C to 1-wire bridge.
 * There are two variations: -100 and -800, which have 1 or 8 1-wire ports.
 * The complete datasheet can be obtained from MAXIM's website at:
 *   http://www.maxim-ic.com/quick_view2.cfm/qv_pk/4382
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/delay.h>

#समावेश <linux/w1.h>

/**
 * Allow the active pullup to be disabled, शेष is enabled.
 *
 * Note from the DS2482 datasheet:
 * The APU bit controls whether an active pullup (controlled slew-rate
 * transistor) or a passive pullup (Rwpu resistor) will be used to drive
 * a 1-Wire line from low to high. When APU = 0, active pullup is disabled
 * (resistor mode). Active Pullup should always be selected unless there is
 * only a single slave on the 1-Wire line.
 */
अटल पूर्णांक ds2482_active_pullup = 1;
module_param_named(active_pullup, ds2482_active_pullup, पूर्णांक, 0644);
MODULE_PARM_DESC(active_pullup, "Active pullup (apply to all buses): " \
				"0-disable, 1-enable (default)");

/* extra configurations - e.g. 1WS */
अटल पूर्णांक extra_config;
module_param(extra_config, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(extra_config, "Extra Configuration settings 1=APU,2=PPM,3=SPU,8=1WS");

/**
 * The DS2482 रेजिस्टरs - there are 3 रेजिस्टरs that are addressed by a पढ़ो
 * poपूर्णांकer. The पढ़ो poपूर्णांकer is set by the last command executed.
 *
 * To पढ़ो the data, issue a रेजिस्टर पढ़ो क्रम any address
 */
#घोषणा DS2482_CMD_RESET		0xF0	/* No param */
#घोषणा DS2482_CMD_SET_READ_PTR		0xE1	/* Param: DS2482_PTR_CODE_xxx */
#घोषणा DS2482_CMD_CHANNEL_SELECT	0xC3	/* Param: Channel byte - DS2482-800 only */
#घोषणा DS2482_CMD_WRITE_CONFIG		0xD2	/* Param: Config byte */
#घोषणा DS2482_CMD_1WIRE_RESET		0xB4	/* Param: None */
#घोषणा DS2482_CMD_1WIRE_SINGLE_BIT	0x87	/* Param: Bit byte (bit7) */
#घोषणा DS2482_CMD_1WIRE_WRITE_BYTE	0xA5	/* Param: Data byte */
#घोषणा DS2482_CMD_1WIRE_READ_BYTE	0x96	/* Param: None */
/* Note to पढ़ो the byte, Set the ReadPtr to Data then पढ़ो (any addr) */
#घोषणा DS2482_CMD_1WIRE_TRIPLET	0x78	/* Param: Dir byte (bit7) */

/* Values क्रम DS2482_CMD_SET_READ_PTR */
#घोषणा DS2482_PTR_CODE_STATUS		0xF0
#घोषणा DS2482_PTR_CODE_DATA		0xE1
#घोषणा DS2482_PTR_CODE_CHANNEL		0xD2	/* DS2482-800 only */
#घोषणा DS2482_PTR_CODE_CONFIG		0xC3

/**
 * Configure Register bit definitions
 * The top 4 bits always पढ़ो 0.
 * To ग_लिखो, the top nibble must be the 1's compl. of the low nibble.
 */
#घोषणा DS2482_REG_CFG_1WS		0x08	/* 1-wire speed */
#घोषणा DS2482_REG_CFG_SPU		0x04	/* strong pull-up */
#घोषणा DS2482_REG_CFG_PPM		0x02	/* presence pulse masking */
#घोषणा DS2482_REG_CFG_APU		0x01	/* active pull-up */


/**
 * Write and verअगरy codes क्रम the CHANNEL_SELECT command (DS2482-800 only).
 * To set the channel, ग_लिखो the value at the index of the channel.
 * Read and compare against the corresponding value to verअगरy the change.
 */
अटल स्थिर u8 ds2482_chan_wr[8] =
	अणु 0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87 पूर्ण;
अटल स्थिर u8 ds2482_chan_rd[8] =
	अणु 0xB8, 0xB1, 0xAA, 0xA3, 0x9C, 0x95, 0x8E, 0x87 पूर्ण;


/**
 * Status Register bit definitions (पढ़ो only)
 */
#घोषणा DS2482_REG_STS_सूची		0x80
#घोषणा DS2482_REG_STS_TSB		0x40
#घोषणा DS2482_REG_STS_SBR		0x20
#घोषणा DS2482_REG_STS_RST		0x10
#घोषणा DS2482_REG_STS_LL		0x08
#घोषणा DS2482_REG_STS_SD		0x04
#घोषणा DS2482_REG_STS_PPD		0x02
#घोषणा DS2482_REG_STS_1WB		0x01

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा ds2482_data;

काष्ठा ds2482_w1_chan अणु
	काष्ठा ds2482_data	*pdev;
	u8			channel;
	काष्ठा w1_bus_master	w1_bm;
पूर्ण;

काष्ठा ds2482_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा mutex		access_lock;

	/* 1-wire पूर्णांकerface(s) */
	पूर्णांक			w1_count;	/* 1 or 8 */
	काष्ठा ds2482_w1_chan	w1_ch[8];

	/* per-device values */
	u8			channel;
	u8			पढ़ो_prt;	/* see DS2482_PTR_CODE_xxx */
	u8			reg_config;
पूर्ण;


/**
 * Helper to calculate values क्रम configuration रेजिस्टर
 * @param conf the raw config value
 * @वापस the value w/ complements that can be written to रेजिस्टर
 */
अटल अंतरभूत u8 ds2482_calculate_config(u8 conf)
अणु
	conf |= extra_config;

	अगर (ds2482_active_pullup)
		conf |= DS2482_REG_CFG_APU;

	वापस conf | ((~conf & 0x0f) << 4);
पूर्ण


/**
 * Sets the पढ़ो poपूर्णांकer.
 * @param pdev		The ds2482 client poपूर्णांकer
 * @param पढ़ो_ptr	see DS2482_PTR_CODE_xxx above
 * @वापस -1 on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक ds2482_select_रेजिस्टर(काष्ठा ds2482_data *pdev, u8 पढ़ो_ptr)
अणु
	अगर (pdev->पढ़ो_prt != पढ़ो_ptr) अणु
		अगर (i2c_smbus_ग_लिखो_byte_data(pdev->client,
					      DS2482_CMD_SET_READ_PTR,
					      पढ़ो_ptr) < 0)
			वापस -1;

		pdev->पढ़ो_prt = पढ़ो_ptr;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Sends a command without a parameter
 * @param pdev	The ds2482 client poपूर्णांकer
 * @param cmd	DS2482_CMD_RESET,
 *		DS2482_CMD_1WIRE_RESET,
 *		DS2482_CMD_1WIRE_READ_BYTE
 * @वापस -1 on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक ds2482_send_cmd(काष्ठा ds2482_data *pdev, u8 cmd)
अणु
	अगर (i2c_smbus_ग_लिखो_byte(pdev->client, cmd) < 0)
		वापस -1;

	pdev->पढ़ो_prt = DS2482_PTR_CODE_STATUS;
	वापस 0;
पूर्ण

/**
 * Sends a command with a parameter
 * @param pdev	The ds2482 client poपूर्णांकer
 * @param cmd	DS2482_CMD_WRITE_CONFIG,
 *		DS2482_CMD_1WIRE_SINGLE_BIT,
 *		DS2482_CMD_1WIRE_WRITE_BYTE,
 *		DS2482_CMD_1WIRE_TRIPLET
 * @param byte	The data to send
 * @वापस -1 on failure, 0 on success
 */
अटल अंतरभूत पूर्णांक ds2482_send_cmd_data(काष्ठा ds2482_data *pdev,
				       u8 cmd, u8 byte)
अणु
	अगर (i2c_smbus_ग_लिखो_byte_data(pdev->client, cmd, byte) < 0)
		वापस -1;

	/* all cmds leave in STATUS, except CONFIG */
	pdev->पढ़ो_prt = (cmd != DS2482_CMD_WRITE_CONFIG) ?
			 DS2482_PTR_CODE_STATUS : DS2482_PTR_CODE_CONFIG;
	वापस 0;
पूर्ण


/*
 * 1-Wire पूर्णांकerface code
 */

#घोषणा DS2482_WAIT_IDLE_TIMEOUT	100

/**
 * Waits until the 1-wire पूर्णांकerface is idle (not busy)
 *
 * @param pdev Poपूर्णांकer to the device काष्ठाure
 * @वापस the last value पढ़ो from status or -1 (failure)
 */
अटल पूर्णांक ds2482_रुको_1wire_idle(काष्ठा ds2482_data *pdev)
अणु
	पूर्णांक temp = -1;
	पूर्णांक retries = 0;

	अगर (!ds2482_select_रेजिस्टर(pdev, DS2482_PTR_CODE_STATUS)) अणु
		करो अणु
			temp = i2c_smbus_पढ़ो_byte(pdev->client);
		पूर्ण जबतक ((temp >= 0) && (temp & DS2482_REG_STS_1WB) &&
			 (++retries < DS2482_WAIT_IDLE_TIMEOUT));
	पूर्ण

	अगर (retries >= DS2482_WAIT_IDLE_TIMEOUT)
		pr_err("%s: timeout on channel %d\n",
		       __func__, pdev->channel);

	वापस temp;
पूर्ण

/**
 * Selects a w1 channel.
 * The 1-wire पूर्णांकerface must be idle beक्रमe calling this function.
 *
 * @param pdev		The ds2482 client poपूर्णांकer
 * @param channel	0-7
 * @वापस		-1 (failure) or 0 (success)
 */
अटल पूर्णांक ds2482_set_channel(काष्ठा ds2482_data *pdev, u8 channel)
अणु
	अगर (i2c_smbus_ग_लिखो_byte_data(pdev->client, DS2482_CMD_CHANNEL_SELECT,
				      ds2482_chan_wr[channel]) < 0)
		वापस -1;

	pdev->पढ़ो_prt = DS2482_PTR_CODE_CHANNEL;
	pdev->channel = -1;
	अगर (i2c_smbus_पढ़ो_byte(pdev->client) == ds2482_chan_rd[channel]) अणु
		pdev->channel = channel;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण


/**
 * Perक्रमms the touch-bit function, which ग_लिखोs a 0 or 1 and पढ़ोs the level.
 *
 * @param data	The ds2482 channel poपूर्णांकer
 * @param bit	The level to ग_लिखो: 0 or non-zero
 * @वापस	The level पढ़ो: 0 or 1
 */
अटल u8 ds2482_w1_touch_bit(व्योम *data, u8 bit)
अणु
	काष्ठा ds2482_w1_chan *pchan = data;
	काष्ठा ds2482_data    *pdev = pchan->pdev;
	पूर्णांक status = -1;

	mutex_lock(&pdev->access_lock);

	/* Select the channel */
	ds2482_रुको_1wire_idle(pdev);
	अगर (pdev->w1_count > 1)
		ds2482_set_channel(pdev, pchan->channel);

	/* Send the touch command, रुको until 1WB == 0, वापस the status */
	अगर (!ds2482_send_cmd_data(pdev, DS2482_CMD_1WIRE_SINGLE_BIT,
				  bit ? 0xFF : 0))
		status = ds2482_रुको_1wire_idle(pdev);

	mutex_unlock(&pdev->access_lock);

	वापस (status & DS2482_REG_STS_SBR) ? 1 : 0;
पूर्ण

/**
 * Perक्रमms the triplet function, which पढ़ोs two bits and ग_लिखोs a bit.
 * The bit written is determined by the two पढ़ोs:
 *   00 => dbit, 01 => 0, 10 => 1
 *
 * @param data	The ds2482 channel poपूर्णांकer
 * @param dbit	The direction to choose अगर both branches are valid
 * @वापस	b0=पढ़ो1 b1=पढ़ो2 b3=bit written
 */
अटल u8 ds2482_w1_triplet(व्योम *data, u8 dbit)
अणु
	काष्ठा ds2482_w1_chan *pchan = data;
	काष्ठा ds2482_data    *pdev = pchan->pdev;
	पूर्णांक status = (3 << 5);

	mutex_lock(&pdev->access_lock);

	/* Select the channel */
	ds2482_रुको_1wire_idle(pdev);
	अगर (pdev->w1_count > 1)
		ds2482_set_channel(pdev, pchan->channel);

	/* Send the triplet command, रुको until 1WB == 0, वापस the status */
	अगर (!ds2482_send_cmd_data(pdev, DS2482_CMD_1WIRE_TRIPLET,
				  dbit ? 0xFF : 0))
		status = ds2482_रुको_1wire_idle(pdev);

	mutex_unlock(&pdev->access_lock);

	/* Decode the status */
	वापस (status >> 5);
पूर्ण

/**
 * Perक्रमms the ग_लिखो byte function.
 *
 * @param data	The ds2482 channel poपूर्णांकer
 * @param byte	The value to ग_लिखो
 */
अटल व्योम ds2482_w1_ग_लिखो_byte(व्योम *data, u8 byte)
अणु
	काष्ठा ds2482_w1_chan *pchan = data;
	काष्ठा ds2482_data    *pdev = pchan->pdev;

	mutex_lock(&pdev->access_lock);

	/* Select the channel */
	ds2482_रुको_1wire_idle(pdev);
	अगर (pdev->w1_count > 1)
		ds2482_set_channel(pdev, pchan->channel);

	/* Send the ग_लिखो byte command */
	ds2482_send_cmd_data(pdev, DS2482_CMD_1WIRE_WRITE_BYTE, byte);

	mutex_unlock(&pdev->access_lock);
पूर्ण

/**
 * Perक्रमms the पढ़ो byte function.
 *
 * @param data	The ds2482 channel poपूर्णांकer
 * @वापस	The value पढ़ो
 */
अटल u8 ds2482_w1_पढ़ो_byte(व्योम *data)
अणु
	काष्ठा ds2482_w1_chan *pchan = data;
	काष्ठा ds2482_data    *pdev = pchan->pdev;
	पूर्णांक result;

	mutex_lock(&pdev->access_lock);

	/* Select the channel */
	ds2482_रुको_1wire_idle(pdev);
	अगर (pdev->w1_count > 1)
		ds2482_set_channel(pdev, pchan->channel);

	/* Send the पढ़ो byte command */
	ds2482_send_cmd(pdev, DS2482_CMD_1WIRE_READ_BYTE);

	/* Wait until 1WB == 0 */
	ds2482_रुको_1wire_idle(pdev);

	/* Select the data रेजिस्टर */
	ds2482_select_रेजिस्टर(pdev, DS2482_PTR_CODE_DATA);

	/* Read the data byte */
	result = i2c_smbus_पढ़ो_byte(pdev->client);

	mutex_unlock(&pdev->access_lock);

	वापस result;
पूर्ण


/**
 * Sends a reset on the 1-wire पूर्णांकerface
 *
 * @param data	The ds2482 channel poपूर्णांकer
 * @वापस	0=Device present, 1=No device present or error
 */
अटल u8 ds2482_w1_reset_bus(व्योम *data)
अणु
	काष्ठा ds2482_w1_chan *pchan = data;
	काष्ठा ds2482_data    *pdev = pchan->pdev;
	पूर्णांक err;
	u8 retval = 1;

	mutex_lock(&pdev->access_lock);

	/* Select the channel */
	ds2482_रुको_1wire_idle(pdev);
	अगर (pdev->w1_count > 1)
		ds2482_set_channel(pdev, pchan->channel);

	/* Send the reset command */
	err = ds2482_send_cmd(pdev, DS2482_CMD_1WIRE_RESET);
	अगर (err >= 0) अणु
		/* Wait until the reset is complete */
		err = ds2482_रुको_1wire_idle(pdev);
		retval = !(err & DS2482_REG_STS_PPD);

		/* If the chip did reset since detect, re-config it */
		अगर (err & DS2482_REG_STS_RST)
			ds2482_send_cmd_data(pdev, DS2482_CMD_WRITE_CONFIG,
					     ds2482_calculate_config(0x00));
	पूर्ण

	mutex_unlock(&pdev->access_lock);

	वापस retval;
पूर्ण

अटल u8 ds2482_w1_set_pullup(व्योम *data, पूर्णांक delay)
अणु
	काष्ठा ds2482_w1_chan *pchan = data;
	काष्ठा ds2482_data    *pdev = pchan->pdev;
	u8 retval = 1;

	/* अगर delay is non-zero activate the pullup,
	 * the strong pullup will be स्वतःmatically deactivated
	 * by the master, so करो not explicitly deactive it
	 */
	अगर (delay) अणु
		/* both रुकोs are crucial, otherwise devices might not be
		 * घातered दीर्घ enough, causing e.g. a w1_therm sensor to
		 * provide wrong conversion results
		 */
		ds2482_रुको_1wire_idle(pdev);
		/* note: it seems like both SPU and APU have to be set! */
		retval = ds2482_send_cmd_data(pdev, DS2482_CMD_WRITE_CONFIG,
			ds2482_calculate_config(DS2482_REG_CFG_SPU |
						DS2482_REG_CFG_APU));
		ds2482_रुको_1wire_idle(pdev);
	पूर्ण

	वापस retval;
पूर्ण


अटल पूर्णांक ds2482_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ds2482_data *data;
	पूर्णांक err = -ENODEV;
	पूर्णांक temp1;
	पूर्णांक idx;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
				     I2C_FUNC_SMBUS_BYTE))
		वापस -ENODEV;

	अगर (!(data = kzalloc(माप(काष्ठा ds2482_data), GFP_KERNEL))) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	data->client = client;
	i2c_set_clientdata(client, data);

	/* Reset the device (sets the पढ़ो_ptr to status) */
	अगर (ds2482_send_cmd(data, DS2482_CMD_RESET) < 0) अणु
		dev_warn(&client->dev, "DS2482 reset failed.\n");
		जाओ निकास_मुक्त;
	पूर्ण

	/* Sleep at least 525ns to allow the reset to complete */
	ndelay(525);

	/* Read the status byte - only reset bit and line should be set */
	temp1 = i2c_smbus_पढ़ो_byte(client);
	अगर (temp1 != (DS2482_REG_STS_LL | DS2482_REG_STS_RST)) अणु
		dev_warn(&client->dev, "DS2482 reset status "
			 "0x%02X - not a DS2482\n", temp1);
		जाओ निकास_मुक्त;
	पूर्ण

	/* Detect the 8-port version */
	data->w1_count = 1;
	अगर (ds2482_set_channel(data, 7) == 0)
		data->w1_count = 8;

	/* Set all config items to 0 (off) */
	ds2482_send_cmd_data(data, DS2482_CMD_WRITE_CONFIG,
		ds2482_calculate_config(0x00));

	mutex_init(&data->access_lock);

	/* Register 1-wire पूर्णांकerface(s) */
	क्रम (idx = 0; idx < data->w1_count; idx++) अणु
		data->w1_ch[idx].pdev = data;
		data->w1_ch[idx].channel = idx;

		/* Populate all the w1 bus master stuff */
		data->w1_ch[idx].w1_bm.data       = &data->w1_ch[idx];
		data->w1_ch[idx].w1_bm.पढ़ो_byte  = ds2482_w1_पढ़ो_byte;
		data->w1_ch[idx].w1_bm.ग_लिखो_byte = ds2482_w1_ग_लिखो_byte;
		data->w1_ch[idx].w1_bm.touch_bit  = ds2482_w1_touch_bit;
		data->w1_ch[idx].w1_bm.triplet    = ds2482_w1_triplet;
		data->w1_ch[idx].w1_bm.reset_bus  = ds2482_w1_reset_bus;
		data->w1_ch[idx].w1_bm.set_pullup = ds2482_w1_set_pullup;

		err = w1_add_master_device(&data->w1_ch[idx].w1_bm);
		अगर (err) अणु
			data->w1_ch[idx].pdev = शून्य;
			जाओ निकास_w1_हटाओ;
		पूर्ण
	पूर्ण

	वापस 0;

निकास_w1_हटाओ:
	क्रम (idx = 0; idx < data->w1_count; idx++) अणु
		अगर (data->w1_ch[idx].pdev != शून्य)
			w1_हटाओ_master_device(&data->w1_ch[idx].w1_bm);
	पूर्ण
निकास_मुक्त:
	kमुक्त(data);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक ds2482_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ds2482_data   *data = i2c_get_clientdata(client);
	पूर्णांक idx;

	/* Unरेजिस्टर the 1-wire bridge(s) */
	क्रम (idx = 0; idx < data->w1_count; idx++) अणु
		अगर (data->w1_ch[idx].pdev != शून्य)
			w1_हटाओ_master_device(&data->w1_ch[idx].w1_bm);
	पूर्ण

	/* Free the memory */
	kमुक्त(data);
	वापस 0;
पूर्ण

/**
 * Driver data (common to all clients)
 */
अटल स्थिर काष्ठा i2c_device_id ds2482_id[] = अणु
	अणु "ds2482", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds2482_id);

अटल काष्ठा i2c_driver ds2482_driver = अणु
	.driver = अणु
		.name	= "ds2482",
	पूर्ण,
	.probe		= ds2482_probe,
	.हटाओ		= ds2482_हटाओ,
	.id_table	= ds2482_id,
पूर्ण;
module_i2c_driver(ds2482_driver);

MODULE_AUTHOR("Ben Gardner <bgardner@wabtec.com>");
MODULE_DESCRIPTION("DS2482 driver");

MODULE_LICENSE("GPL");
