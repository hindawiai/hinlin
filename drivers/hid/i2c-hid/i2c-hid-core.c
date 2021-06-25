<शैली गुरु>
/*
 * HID over I2C protocol implementation
 *
 * Copyright (c) 2012 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 * Copyright (c) 2012 Ecole Nationale de l'Aviation Civile, France
 * Copyright (c) 2012 Red Hat, Inc
 *
 * This code is partly based on "USB HID support for Linux":
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2007-2008 Oliver Neukum
 *  Copyright (c) 2006-2010 Jiri Kosina
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hid.h>
#समावेश <linux/mutex.h>

#समावेश "../hid-ids.h"
#समावेश "i2c-hid.h"

/* quirks to control the device */
#घोषणा I2C_HID_QUIRK_SET_PWR_WAKEUP_DEV	BIT(0)
#घोषणा I2C_HID_QUIRK_NO_IRQ_AFTER_RESET	BIT(1)
#घोषणा I2C_HID_QUIRK_BOGUS_IRQ			BIT(4)
#घोषणा I2C_HID_QUIRK_RESET_ON_RESUME		BIT(5)
#घोषणा I2C_HID_QUIRK_BAD_INPUT_SIZE		BIT(6)
#घोषणा I2C_HID_QUIRK_NO_WAKEUP_AFTER_RESET	BIT(7)


/* flags */
#घोषणा I2C_HID_STARTED		0
#घोषणा I2C_HID_RESET_PENDING	1
#घोषणा I2C_HID_READ_PENDING	2

#घोषणा I2C_HID_PWR_ON		0x00
#घोषणा I2C_HID_PWR_SLEEP	0x01

/* debug option */
अटल bool debug;
module_param(debug, bool, 0444);
MODULE_PARM_DESC(debug, "print a lot of debug information");

#घोषणा i2c_hid_dbg(ihid, fmt, arg...)					  \
करो अणु									  \
	अगर (debug)							  \
		dev_prपूर्णांकk(KERN_DEBUG, &(ihid)->client->dev, fmt, ##arg); \
पूर्ण जबतक (0)

काष्ठा i2c_hid_desc अणु
	__le16 wHIDDescLength;
	__le16 bcdVersion;
	__le16 wReportDescLength;
	__le16 wReportDescRegister;
	__le16 wInputRegister;
	__le16 wMaxInputLength;
	__le16 wOutputRegister;
	__le16 wMaxOutputLength;
	__le16 wCommandRegister;
	__le16 wDataRegister;
	__le16 wVenकरोrID;
	__le16 wProductID;
	__le16 wVersionID;
	__le32 reserved;
पूर्ण __packed;

काष्ठा i2c_hid_cmd अणु
	अचिन्हित पूर्णांक रेजिस्टरIndex;
	__u8 opcode;
	अचिन्हित पूर्णांक length;
	bool रुको;
पूर्ण;

जोड़ command अणु
	u8 data[0];
	काष्ठा cmd अणु
		__le16 reg;
		__u8 reportTypeID;
		__u8 opcode;
	पूर्ण __packed c;
पूर्ण;

#घोषणा I2C_HID_CMD(opcode_) \
	.opcode = opcode_, .length = 4, \
	.रेजिस्टरIndex = दुरत्व(काष्ठा i2c_hid_desc, wCommandRegister)

/* fetch HID descriptor */
अटल स्थिर काष्ठा i2c_hid_cmd hid_descr_cmd = अणु .length = 2 पूर्ण;
/* fetch report descriptors */
अटल स्थिर काष्ठा i2c_hid_cmd hid_report_descr_cmd = अणु
		.रेजिस्टरIndex = दुरत्व(काष्ठा i2c_hid_desc,
			wReportDescRegister),
		.opcode = 0x00,
		.length = 2 पूर्ण;
/* commands */
अटल स्थिर काष्ठा i2c_hid_cmd hid_reset_cmd =		अणु I2C_HID_CMD(0x01),
							  .रुको = true पूर्ण;
अटल स्थिर काष्ठा i2c_hid_cmd hid_get_report_cmd =	अणु I2C_HID_CMD(0x02) पूर्ण;
अटल स्थिर काष्ठा i2c_hid_cmd hid_set_report_cmd =	अणु I2C_HID_CMD(0x03) पूर्ण;
अटल स्थिर काष्ठा i2c_hid_cmd hid_set_घातer_cmd =	अणु I2C_HID_CMD(0x08) पूर्ण;
अटल स्थिर काष्ठा i2c_hid_cmd hid_no_cmd =		अणु .length = 0 पूर्ण;

/*
 * These definitions are not used here, but are defined by the spec.
 * Keeping them here क्रम करोcumentation purposes.
 *
 * अटल स्थिर काष्ठा i2c_hid_cmd hid_get_idle_cmd = अणु I2C_HID_CMD(0x04) पूर्ण;
 * अटल स्थिर काष्ठा i2c_hid_cmd hid_set_idle_cmd = अणु I2C_HID_CMD(0x05) पूर्ण;
 * अटल स्थिर काष्ठा i2c_hid_cmd hid_get_protocol_cmd = अणु I2C_HID_CMD(0x06) पूर्ण;
 * अटल स्थिर काष्ठा i2c_hid_cmd hid_set_protocol_cmd = अणु I2C_HID_CMD(0x07) पूर्ण;
 */

/* The मुख्य device काष्ठाure */
काष्ठा i2c_hid अणु
	काष्ठा i2c_client	*client;	/* i2c client */
	काष्ठा hid_device	*hid;	/* poपूर्णांकer to corresponding HID dev */
	जोड़ अणु
		__u8 hdesc_buffer[माप(काष्ठा i2c_hid_desc)];
		काष्ठा i2c_hid_desc hdesc;	/* the HID Descriptor */
	पूर्ण;
	__le16			wHIDDescRegister; /* location of the i2c
						   * रेजिस्टर of the HID
						   * descriptor. */
	अचिन्हित पूर्णांक		bufsize;	/* i2c buffer size */
	u8			*inbuf;		/* Input buffer */
	u8			*rawbuf;	/* Raw Input buffer */
	u8			*cmdbuf;	/* Command buffer */
	u8			*argsbuf;	/* Command arguments buffer */

	अचिन्हित दीर्घ		flags;		/* device flags */
	अचिन्हित दीर्घ		quirks;		/* Various quirks */

	रुको_queue_head_t	रुको;		/* For रुकोing the पूर्णांकerrupt */

	bool			irq_wake_enabled;
	काष्ठा mutex		reset_lock;

	काष्ठा i2chid_ops	*ops;
पूर्ण;

अटल स्थिर काष्ठा i2c_hid_quirks अणु
	__u16 idVenकरोr;
	__u16 idProduct;
	__u32 quirks;
पूर्ण i2c_hid_quirks[] = अणु
	अणु USB_VENDOR_ID_WEIDA, HID_ANY_ID,
		I2C_HID_QUIRK_SET_PWR_WAKEUP_DEV पूर्ण,
	अणु I2C_VENDOR_ID_HANTICK, I2C_PRODUCT_ID_HANTICK_5288,
		I2C_HID_QUIRK_NO_IRQ_AFTER_RESET पूर्ण,
	अणु I2C_VENDOR_ID_ITE, I2C_DEVICE_ID_ITE_VOYO_WINPAD_A15,
		I2C_HID_QUIRK_NO_IRQ_AFTER_RESET पूर्ण,
	अणु I2C_VENDOR_ID_RAYDIUM, I2C_PRODUCT_ID_RAYDIUM_3118,
		I2C_HID_QUIRK_NO_IRQ_AFTER_RESET पूर्ण,
	अणु USB_VENDOR_ID_ELAN, HID_ANY_ID,
		 I2C_HID_QUIRK_BOGUS_IRQ पूर्ण,
	अणु USB_VENDOR_ID_ALPS_JP, HID_ANY_ID,
		 I2C_HID_QUIRK_RESET_ON_RESUME पूर्ण,
	अणु I2C_VENDOR_ID_SYNAPTICS, I2C_PRODUCT_ID_SYNAPTICS_SYNA2393,
		 I2C_HID_QUIRK_RESET_ON_RESUME पूर्ण,
	अणु USB_VENDOR_ID_ITE, I2C_DEVICE_ID_ITE_LENOVO_LEGION_Y720,
		I2C_HID_QUIRK_BAD_INPUT_SIZE पूर्ण,
	/*
	 * Sending the wakeup after reset actually अवरोध ELAN touchscreen controller
	 */
	अणु USB_VENDOR_ID_ELAN, HID_ANY_ID,
		 I2C_HID_QUIRK_NO_WAKEUP_AFTER_RESET पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/*
 * i2c_hid_lookup_quirk: वापस any quirks associated with a I2C HID device
 * @idVenकरोr: the 16-bit venकरोr ID
 * @idProduct: the 16-bit product ID
 *
 * Returns: a u32 quirks value.
 */
अटल u32 i2c_hid_lookup_quirk(स्थिर u16 idVenकरोr, स्थिर u16 idProduct)
अणु
	u32 quirks = 0;
	पूर्णांक n;

	क्रम (n = 0; i2c_hid_quirks[n].idVenकरोr; n++)
		अगर (i2c_hid_quirks[n].idVenकरोr == idVenकरोr &&
		    (i2c_hid_quirks[n].idProduct == (__u16)HID_ANY_ID ||
		     i2c_hid_quirks[n].idProduct == idProduct))
			quirks = i2c_hid_quirks[n].quirks;

	वापस quirks;
पूर्ण

अटल पूर्णांक __i2c_hid_command(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_hid_cmd *command, u8 reportID,
		u8 reportType, u8 *args, पूर्णांक args_len,
		अचिन्हित अक्षर *buf_recv, पूर्णांक data_len)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	जोड़ command *cmd = (जोड़ command *)ihid->cmdbuf;
	पूर्णांक ret;
	काष्ठा i2c_msg msg[2];
	पूर्णांक msg_num = 1;

	पूर्णांक length = command->length;
	bool रुको = command->रुको;
	अचिन्हित पूर्णांक रेजिस्टरIndex = command->रेजिस्टरIndex;

	/* special हाल क्रम hid_descr_cmd */
	अगर (command == &hid_descr_cmd) अणु
		cmd->c.reg = ihid->wHIDDescRegister;
	पूर्ण अन्यथा अणु
		cmd->data[0] = ihid->hdesc_buffer[रेजिस्टरIndex];
		cmd->data[1] = ihid->hdesc_buffer[रेजिस्टरIndex + 1];
	पूर्ण

	अगर (length > 2) अणु
		cmd->c.opcode = command->opcode;
		cmd->c.reportTypeID = reportID | reportType << 4;
	पूर्ण

	स_नकल(cmd->data + length, args, args_len);
	length += args_len;

	i2c_hid_dbg(ihid, "%s: cmd=%*ph\n", __func__, length, cmd->data);

	msg[0].addr = client->addr;
	msg[0].flags = client->flags & I2C_M_TEN;
	msg[0].len = length;
	msg[0].buf = cmd->data;
	अगर (data_len > 0) अणु
		msg[1].addr = client->addr;
		msg[1].flags = client->flags & I2C_M_TEN;
		msg[1].flags |= I2C_M_RD;
		msg[1].len = data_len;
		msg[1].buf = buf_recv;
		msg_num = 2;
		set_bit(I2C_HID_READ_PENDING, &ihid->flags);
	पूर्ण

	अगर (रुको)
		set_bit(I2C_HID_RESET_PENDING, &ihid->flags);

	ret = i2c_transfer(client->adapter, msg, msg_num);

	अगर (data_len > 0)
		clear_bit(I2C_HID_READ_PENDING, &ihid->flags);

	अगर (ret != msg_num)
		वापस ret < 0 ? ret : -EIO;

	ret = 0;

	अगर (रुको && (ihid->quirks & I2C_HID_QUIRK_NO_IRQ_AFTER_RESET)) अणु
		msleep(100);
	पूर्ण अन्यथा अगर (रुको) अणु
		i2c_hid_dbg(ihid, "%s: waiting...\n", __func__);
		अगर (!रुको_event_समयout(ihid->रुको,
				!test_bit(I2C_HID_RESET_PENDING, &ihid->flags),
				msecs_to_jअगरfies(5000)))
			ret = -ENODATA;
		i2c_hid_dbg(ihid, "%s: finished.\n", __func__);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_hid_command(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_hid_cmd *command,
		अचिन्हित अक्षर *buf_recv, पूर्णांक data_len)
अणु
	वापस __i2c_hid_command(client, command, 0, 0, शून्य, 0,
				buf_recv, data_len);
पूर्ण

अटल पूर्णांक i2c_hid_get_report(काष्ठा i2c_client *client, u8 reportType,
		u8 reportID, अचिन्हित अक्षर *buf_recv, पूर्णांक data_len)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	u8 args[3];
	पूर्णांक ret;
	पूर्णांक args_len = 0;
	u16 पढ़ोRegister = le16_to_cpu(ihid->hdesc.wDataRegister);

	i2c_hid_dbg(ihid, "%s\n", __func__);

	अगर (reportID >= 0x0F) अणु
		args[args_len++] = reportID;
		reportID = 0x0F;
	पूर्ण

	args[args_len++] = पढ़ोRegister & 0xFF;
	args[args_len++] = पढ़ोRegister >> 8;

	ret = __i2c_hid_command(client, &hid_get_report_cmd, reportID,
		reportType, args, args_len, buf_recv, data_len);
	अगर (ret) अणु
		dev_err(&client->dev,
			"failed to retrieve report from device.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i2c_hid_set_or_send_report: क्रमward an incoming report to the device
 * @client: the i2c_client of the device
 * @reportType: 0x03 क्रम HID_FEATURE_REPORT ; 0x02 क्रम HID_OUTPUT_REPORT
 * @reportID: the report ID
 * @buf: the actual data to transfer, without the report ID
 * @data_len: size of buf
 * @use_data: true: use SET_REPORT HID command, false: send plain OUTPUT report
 */
अटल पूर्णांक i2c_hid_set_or_send_report(काष्ठा i2c_client *client, u8 reportType,
		u8 reportID, अचिन्हित अक्षर *buf, माप_प्रकार data_len, bool use_data)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	u8 *args = ihid->argsbuf;
	स्थिर काष्ठा i2c_hid_cmd *hidcmd;
	पूर्णांक ret;
	u16 dataRegister = le16_to_cpu(ihid->hdesc.wDataRegister);
	u16 outputRegister = le16_to_cpu(ihid->hdesc.wOutputRegister);
	u16 maxOutputLength = le16_to_cpu(ihid->hdesc.wMaxOutputLength);
	u16 size;
	पूर्णांक args_len;
	पूर्णांक index = 0;

	i2c_hid_dbg(ihid, "%s\n", __func__);

	अगर (data_len > ihid->bufsize)
		वापस -EINVAL;

	size =		2			/* size */ +
			(reportID ? 1 : 0)	/* reportID */ +
			data_len		/* buf */;
	args_len =	(reportID >= 0x0F ? 1 : 0) /* optional third byte */ +
			2			/* dataRegister */ +
			size			/* args */;

	अगर (!use_data && maxOutputLength == 0)
		वापस -ENOSYS;

	अगर (reportID >= 0x0F) अणु
		args[index++] = reportID;
		reportID = 0x0F;
	पूर्ण

	/*
	 * use the data रेजिस्टर क्रम feature reports or अगर the device करोes not
	 * support the output रेजिस्टर
	 */
	अगर (use_data) अणु
		args[index++] = dataRegister & 0xFF;
		args[index++] = dataRegister >> 8;
		hidcmd = &hid_set_report_cmd;
	पूर्ण अन्यथा अणु
		args[index++] = outputRegister & 0xFF;
		args[index++] = outputRegister >> 8;
		hidcmd = &hid_no_cmd;
	पूर्ण

	args[index++] = size & 0xFF;
	args[index++] = size >> 8;

	अगर (reportID)
		args[index++] = reportID;

	स_नकल(&args[index], buf, data_len);

	ret = __i2c_hid_command(client, hidcmd, reportID,
		reportType, args, args_len, शून्य, 0);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to set a report to device.\n");
		वापस ret;
	पूर्ण

	वापस data_len;
पूर्ण

अटल पूर्णांक i2c_hid_set_घातer(काष्ठा i2c_client *client, पूर्णांक घातer_state)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	पूर्णांक ret;

	i2c_hid_dbg(ihid, "%s\n", __func__);

	/*
	 * Some devices require to send a command to wakeup beक्रमe घातer on.
	 * The call will get a वापस value (EREMOTEIO) but device will be
	 * triggered and activated. After that, it goes like a normal device.
	 */
	अगर (घातer_state == I2C_HID_PWR_ON &&
	    ihid->quirks & I2C_HID_QUIRK_SET_PWR_WAKEUP_DEV) अणु
		ret = i2c_hid_command(client, &hid_set_घातer_cmd, शून्य, 0);

		/* Device was alपढ़ोy activated */
		अगर (!ret)
			जाओ set_pwr_निकास;
	पूर्ण

	ret = __i2c_hid_command(client, &hid_set_घातer_cmd, घातer_state,
		0, शून्य, 0, शून्य, 0);

	अगर (ret)
		dev_err(&client->dev, "failed to change power setting.\n");

set_pwr_निकास:

	/*
	 * The HID over I2C specअगरication states that अगर a DEVICE needs समय
	 * after the PWR_ON request, it should utilise CLOCK stretching.
	 * However, it has been observered that the Winकरोws driver provides a
	 * 1ms sleep between the PWR_ON and RESET requests.
	 * According to Goodix Winकरोws even रुकोs 60 ms after (other?)
	 * PWR_ON requests. Testing has confirmed that several devices
	 * will not work properly without a delay after a PWR_ON request.
	 */
	अगर (!ret && घातer_state == I2C_HID_PWR_ON)
		msleep(60);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_hid_hwreset(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	पूर्णांक ret;

	i2c_hid_dbg(ihid, "%s\n", __func__);

	/*
	 * This prevents sending feature reports जबतक the device is
	 * being reset. Otherwise we may lose the reset complete
	 * पूर्णांकerrupt.
	 */
	mutex_lock(&ihid->reset_lock);

	ret = i2c_hid_set_घातer(client, I2C_HID_PWR_ON);
	अगर (ret)
		जाओ out_unlock;

	i2c_hid_dbg(ihid, "resetting...\n");

	ret = i2c_hid_command(client, &hid_reset_cmd, शून्य, 0);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to reset device.\n");
		i2c_hid_set_घातer(client, I2C_HID_PWR_SLEEP);
		जाओ out_unlock;
	पूर्ण

	/* At least some SIS devices need this after reset */
	अगर (!(ihid->quirks & I2C_HID_QUIRK_NO_WAKEUP_AFTER_RESET))
		ret = i2c_hid_set_घातer(client, I2C_HID_PWR_ON);

out_unlock:
	mutex_unlock(&ihid->reset_lock);
	वापस ret;
पूर्ण

अटल व्योम i2c_hid_get_input(काष्ठा i2c_hid *ihid)
अणु
	पूर्णांक ret;
	u32 ret_size;
	पूर्णांक size = le16_to_cpu(ihid->hdesc.wMaxInputLength);

	अगर (size > ihid->bufsize)
		size = ihid->bufsize;

	ret = i2c_master_recv(ihid->client, ihid->inbuf, size);
	अगर (ret != size) अणु
		अगर (ret < 0)
			वापस;

		dev_err(&ihid->client->dev, "%s: got %d data instead of %d\n",
			__func__, ret, size);
		वापस;
	पूर्ण

	ret_size = ihid->inbuf[0] | ihid->inbuf[1] << 8;

	अगर (!ret_size) अणु
		/* host or device initiated RESET completed */
		अगर (test_and_clear_bit(I2C_HID_RESET_PENDING, &ihid->flags))
			wake_up(&ihid->रुको);
		वापस;
	पूर्ण

	अगर (ihid->quirks & I2C_HID_QUIRK_BOGUS_IRQ && ret_size == 0xffff) अणु
		dev_warn_once(&ihid->client->dev, "%s: IRQ triggered but "
			      "there's no data\n", __func__);
		वापस;
	पूर्ण

	अगर ((ret_size > size) || (ret_size < 2)) अणु
		अगर (ihid->quirks & I2C_HID_QUIRK_BAD_INPUT_SIZE) अणु
			ihid->inbuf[0] = size & 0xff;
			ihid->inbuf[1] = size >> 8;
			ret_size = size;
		पूर्ण अन्यथा अणु
			dev_err(&ihid->client->dev, "%s: incomplete report (%d/%d)\n",
				__func__, size, ret_size);
			वापस;
		पूर्ण
	पूर्ण

	i2c_hid_dbg(ihid, "input: %*ph\n", ret_size, ihid->inbuf);

	अगर (test_bit(I2C_HID_STARTED, &ihid->flags))
		hid_input_report(ihid->hid, HID_INPUT_REPORT, ihid->inbuf + 2,
				ret_size - 2, 1);

	वापस;
पूर्ण

अटल irqवापस_t i2c_hid_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_hid *ihid = dev_id;

	अगर (test_bit(I2C_HID_READ_PENDING, &ihid->flags))
		वापस IRQ_HANDLED;

	i2c_hid_get_input(ihid);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक i2c_hid_get_report_length(काष्ठा hid_report *report)
अणु
	वापस ((report->size - 1) >> 3) + 1 +
		report->device->report_क्रमागत[report->type].numbered + 2;
पूर्ण

/*
 * Traverse the supplied list of reports and find the दीर्घest
 */
अटल व्योम i2c_hid_find_max_report(काष्ठा hid_device *hid, अचिन्हित पूर्णांक type,
		अचिन्हित पूर्णांक *max)
अणु
	काष्ठा hid_report *report;
	अचिन्हित पूर्णांक size;

	/* We should not rely on wMaxInputLength, as some devices may set it to
	 * a wrong length. */
	list_क्रम_each_entry(report, &hid->report_क्रमागत[type].report_list, list) अणु
		size = i2c_hid_get_report_length(report);
		अगर (*max < size)
			*max = size;
	पूर्ण
पूर्ण

अटल व्योम i2c_hid_मुक्त_buffers(काष्ठा i2c_hid *ihid)
अणु
	kमुक्त(ihid->inbuf);
	kमुक्त(ihid->rawbuf);
	kमुक्त(ihid->argsbuf);
	kमुक्त(ihid->cmdbuf);
	ihid->inbuf = शून्य;
	ihid->rawbuf = शून्य;
	ihid->cmdbuf = शून्य;
	ihid->argsbuf = शून्य;
	ihid->bufsize = 0;
पूर्ण

अटल पूर्णांक i2c_hid_alloc_buffers(काष्ठा i2c_hid *ihid, माप_प्रकार report_size)
अणु
	/* the worst हाल is computed from the set_report command with a
	 * reportID > 15 and the maximum report length */
	पूर्णांक args_len = माप(__u8) + /* ReportID */
		       माप(__u8) + /* optional ReportID byte */
		       माप(__u16) + /* data रेजिस्टर */
		       माप(__u16) + /* size of the report */
		       report_size; /* report */

	ihid->inbuf = kzalloc(report_size, GFP_KERNEL);
	ihid->rawbuf = kzalloc(report_size, GFP_KERNEL);
	ihid->argsbuf = kzalloc(args_len, GFP_KERNEL);
	ihid->cmdbuf = kzalloc(माप(जोड़ command) + args_len, GFP_KERNEL);

	अगर (!ihid->inbuf || !ihid->rawbuf || !ihid->argsbuf || !ihid->cmdbuf) अणु
		i2c_hid_मुक्त_buffers(ihid);
		वापस -ENOMEM;
	पूर्ण

	ihid->bufsize = report_size;

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_hid_get_raw_report(काष्ठा hid_device *hid,
		अचिन्हित अक्षर report_number, __u8 *buf, माप_प्रकार count,
		अचिन्हित अक्षर report_type)
अणु
	काष्ठा i2c_client *client = hid->driver_data;
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	माप_प्रकार ret_count, ask_count;
	पूर्णांक ret;

	अगर (report_type == HID_OUTPUT_REPORT)
		वापस -EINVAL;

	/* +2 bytes to include the size of the reply in the query buffer */
	ask_count = min(count + 2, (माप_प्रकार)ihid->bufsize);

	ret = i2c_hid_get_report(client,
			report_type == HID_FEATURE_REPORT ? 0x03 : 0x01,
			report_number, ihid->rawbuf, ask_count);

	अगर (ret < 0)
		वापस ret;

	ret_count = ihid->rawbuf[0] | (ihid->rawbuf[1] << 8);

	अगर (ret_count <= 2)
		वापस 0;

	ret_count = min(ret_count, ask_count);

	/* The query buffer contains the size, dropping it in the reply */
	count = min(count, ret_count - 2);
	स_नकल(buf, ihid->rawbuf + 2, count);

	वापस count;
पूर्ण

अटल पूर्णांक i2c_hid_output_raw_report(काष्ठा hid_device *hid, __u8 *buf,
		माप_प्रकार count, अचिन्हित अक्षर report_type, bool use_data)
अणु
	काष्ठा i2c_client *client = hid->driver_data;
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	पूर्णांक report_id = buf[0];
	पूर्णांक ret;

	अगर (report_type == HID_INPUT_REPORT)
		वापस -EINVAL;

	mutex_lock(&ihid->reset_lock);

	अगर (report_id) अणु
		buf++;
		count--;
	पूर्ण

	ret = i2c_hid_set_or_send_report(client,
				report_type == HID_FEATURE_REPORT ? 0x03 : 0x02,
				report_id, buf, count, use_data);

	अगर (report_id && ret >= 0)
		ret++; /* add report_id to the number of transfered bytes */

	mutex_unlock(&ihid->reset_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_hid_output_report(काष्ठा hid_device *hid, __u8 *buf,
		माप_प्रकार count)
अणु
	वापस i2c_hid_output_raw_report(hid, buf, count, HID_OUTPUT_REPORT,
			false);
पूर्ण

अटल पूर्णांक i2c_hid_raw_request(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum,
			       __u8 *buf, माप_प्रकार len, अचिन्हित अक्षर rtype,
			       पूर्णांक reqtype)
अणु
	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		वापस i2c_hid_get_raw_report(hid, reportnum, buf, len, rtype);
	हाल HID_REQ_SET_REPORT:
		अगर (buf[0] != reportnum)
			वापस -EINVAL;
		वापस i2c_hid_output_raw_report(hid, buf, len, rtype, true);
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक i2c_hid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा i2c_client *client = hid->driver_data;
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	काष्ठा i2c_hid_desc *hdesc = &ihid->hdesc;
	अचिन्हित पूर्णांक rsize;
	अक्षर *rdesc;
	पूर्णांक ret;
	पूर्णांक tries = 3;
	अक्षर *use_override;

	i2c_hid_dbg(ihid, "entering %s\n", __func__);

	rsize = le16_to_cpu(hdesc->wReportDescLength);
	अगर (!rsize || rsize > HID_MAX_DESCRIPTOR_SIZE) अणु
		dbg_hid("weird size of report descriptor (%u)\n", rsize);
		वापस -EINVAL;
	पूर्ण

	करो अणु
		ret = i2c_hid_hwreset(client);
		अगर (ret)
			msleep(1000);
	पूर्ण जबतक (tries-- > 0 && ret);

	अगर (ret)
		वापस ret;

	use_override = i2c_hid_get_dmi_hid_report_desc_override(client->name,
								&rsize);

	अगर (use_override) अणु
		rdesc = use_override;
		i2c_hid_dbg(ihid, "Using a HID report descriptor override\n");
	पूर्ण अन्यथा अणु
		rdesc = kzalloc(rsize, GFP_KERNEL);

		अगर (!rdesc) अणु
			dbg_hid("couldn't allocate rdesc memory\n");
			वापस -ENOMEM;
		पूर्ण

		i2c_hid_dbg(ihid, "asking HID report descriptor\n");

		ret = i2c_hid_command(client, &hid_report_descr_cmd,
				      rdesc, rsize);
		अगर (ret) अणु
			hid_err(hid, "reading report descriptor failed\n");
			kमुक्त(rdesc);
			वापस -EIO;
		पूर्ण
	पूर्ण

	i2c_hid_dbg(ihid, "Report Descriptor: %*ph\n", rsize, rdesc);

	ret = hid_parse_report(hid, rdesc, rsize);
	अगर (!use_override)
		kमुक्त(rdesc);

	अगर (ret) अणु
		dbg_hid("parsing report descriptor failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_hid_start(काष्ठा hid_device *hid)
अणु
	काष्ठा i2c_client *client = hid->driver_data;
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	पूर्णांक ret;
	अचिन्हित पूर्णांक bufsize = HID_MIN_BUFFER_SIZE;

	i2c_hid_find_max_report(hid, HID_INPUT_REPORT, &bufsize);
	i2c_hid_find_max_report(hid, HID_OUTPUT_REPORT, &bufsize);
	i2c_hid_find_max_report(hid, HID_FEATURE_REPORT, &bufsize);

	अगर (bufsize > ihid->bufsize) अणु
		disable_irq(client->irq);
		i2c_hid_मुक्त_buffers(ihid);

		ret = i2c_hid_alloc_buffers(ihid, bufsize);
		enable_irq(client->irq);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i2c_hid_stop(काष्ठा hid_device *hid)
अणु
	hid->claimed = 0;
पूर्ण

अटल पूर्णांक i2c_hid_खोलो(काष्ठा hid_device *hid)
अणु
	काष्ठा i2c_client *client = hid->driver_data;
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);

	set_bit(I2C_HID_STARTED, &ihid->flags);
	वापस 0;
पूर्ण

अटल व्योम i2c_hid_बंद(काष्ठा hid_device *hid)
अणु
	काष्ठा i2c_client *client = hid->driver_data;
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);

	clear_bit(I2C_HID_STARTED, &ihid->flags);
पूर्ण

काष्ठा hid_ll_driver i2c_hid_ll_driver = अणु
	.parse = i2c_hid_parse,
	.start = i2c_hid_start,
	.stop = i2c_hid_stop,
	.खोलो = i2c_hid_खोलो,
	.बंद = i2c_hid_बंद,
	.output_report = i2c_hid_output_report,
	.raw_request = i2c_hid_raw_request,
पूर्ण;
EXPORT_SYMBOL_GPL(i2c_hid_ll_driver);

अटल पूर्णांक i2c_hid_init_irq(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	अचिन्हित दीर्घ irqflags = 0;
	पूर्णांक ret;

	dev_dbg(&client->dev, "Requesting IRQ: %d\n", client->irq);

	अगर (!irq_get_trigger_type(client->irq))
		irqflags = IRQF_TRIGGER_LOW;

	ret = request_thपढ़ोed_irq(client->irq, शून्य, i2c_hid_irq,
				   irqflags | IRQF_ONESHOT, client->name, ihid);
	अगर (ret < 0) अणु
		dev_warn(&client->dev,
			"Could not register for %s interrupt, irq = %d,"
			" ret = %d\n",
			client->name, client->irq, ret);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_hid_fetch_hid_descriptor(काष्ठा i2c_hid *ihid)
अणु
	काष्ठा i2c_client *client = ihid->client;
	काष्ठा i2c_hid_desc *hdesc = &ihid->hdesc;
	अचिन्हित पूर्णांक dsize;
	पूर्णांक ret;

	/* i2c hid fetch using a fixed descriptor size (30 bytes) */
	अगर (i2c_hid_get_dmi_i2c_hid_desc_override(client->name)) अणु
		i2c_hid_dbg(ihid, "Using a HID descriptor override\n");
		ihid->hdesc =
			*i2c_hid_get_dmi_i2c_hid_desc_override(client->name);
	पूर्ण अन्यथा अणु
		i2c_hid_dbg(ihid, "Fetching the HID descriptor\n");
		ret = i2c_hid_command(client, &hid_descr_cmd,
				      ihid->hdesc_buffer,
				      माप(काष्ठा i2c_hid_desc));
		अगर (ret) अणु
			dev_err(&client->dev, "hid_descr_cmd failed\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* Validate the length of HID descriptor, the 4 first bytes:
	 * bytes 0-1 -> length
	 * bytes 2-3 -> bcdVersion (has to be 1.00) */
	/* check bcdVersion == 1.0 */
	अगर (le16_to_cpu(hdesc->bcdVersion) != 0x0100) अणु
		dev_err(&client->dev,
			"unexpected HID descriptor bcdVersion (0x%04hx)\n",
			le16_to_cpu(hdesc->bcdVersion));
		वापस -ENODEV;
	पूर्ण

	/* Descriptor length should be 30 bytes as per the specअगरication */
	dsize = le16_to_cpu(hdesc->wHIDDescLength);
	अगर (dsize != माप(काष्ठा i2c_hid_desc)) अणु
		dev_err(&client->dev, "weird size of HID descriptor (%u)\n",
			dsize);
		वापस -ENODEV;
	पूर्ण
	i2c_hid_dbg(ihid, "HID Descriptor: %*ph\n", dsize, ihid->hdesc_buffer);
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_hid_core_घातer_up(काष्ठा i2c_hid *ihid)
अणु
	अगर (!ihid->ops->घातer_up)
		वापस 0;

	वापस ihid->ops->घातer_up(ihid->ops);
पूर्ण

अटल व्योम i2c_hid_core_घातer_करोwn(काष्ठा i2c_hid *ihid)
अणु
	अगर (!ihid->ops->घातer_करोwn)
		वापस;

	ihid->ops->घातer_करोwn(ihid->ops);
पूर्ण

अटल व्योम i2c_hid_core_shutकरोwn_tail(काष्ठा i2c_hid *ihid)
अणु
	अगर (!ihid->ops->shutकरोwn_tail)
		वापस;

	ihid->ops->shutकरोwn_tail(ihid->ops);
पूर्ण

पूर्णांक i2c_hid_core_probe(काष्ठा i2c_client *client, काष्ठा i2chid_ops *ops,
		       u16 hid_descriptor_address)
अणु
	पूर्णांक ret;
	काष्ठा i2c_hid *ihid;
	काष्ठा hid_device *hid;

	dbg_hid("HID probe called for i2c 0x%02x\n", client->addr);

	अगर (!client->irq) अणु
		dev_err(&client->dev,
			"HID over i2c has not been provided an Int IRQ\n");
		वापस -EINVAL;
	पूर्ण

	अगर (client->irq < 0) अणु
		अगर (client->irq != -EPROBE_DEFER)
			dev_err(&client->dev,
				"HID over i2c doesn't have a valid IRQ\n");
		वापस client->irq;
	पूर्ण

	ihid = devm_kzalloc(&client->dev, माप(*ihid), GFP_KERNEL);
	अगर (!ihid)
		वापस -ENOMEM;

	ihid->ops = ops;

	ret = i2c_hid_core_घातer_up(ihid);
	अगर (ret)
		वापस ret;

	i2c_set_clientdata(client, ihid);

	ihid->client = client;

	ihid->wHIDDescRegister = cpu_to_le16(hid_descriptor_address);

	init_रुकोqueue_head(&ihid->रुको);
	mutex_init(&ihid->reset_lock);

	/* we need to allocate the command buffer without knowing the maximum
	 * size of the reports. Let's use HID_MIN_BUFFER_SIZE, then we करो the
	 * real computation later. */
	ret = i2c_hid_alloc_buffers(ihid, HID_MIN_BUFFER_SIZE);
	अगर (ret < 0)
		जाओ err_घातered;

	device_enable_async_suspend(&client->dev);

	/* Make sure there is something at this address */
	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "nothing at this address: %d\n", ret);
		ret = -ENXIO;
		जाओ err_घातered;
	पूर्ण

	ret = i2c_hid_fetch_hid_descriptor(ihid);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"Failed to fetch the HID Descriptor\n");
		जाओ err_घातered;
	पूर्ण

	ret = i2c_hid_init_irq(client);
	अगर (ret < 0)
		जाओ err_घातered;

	hid = hid_allocate_device();
	अगर (IS_ERR(hid)) अणु
		ret = PTR_ERR(hid);
		जाओ err_irq;
	पूर्ण

	ihid->hid = hid;

	hid->driver_data = client;
	hid->ll_driver = &i2c_hid_ll_driver;
	hid->dev.parent = &client->dev;
	hid->bus = BUS_I2C;
	hid->version = le16_to_cpu(ihid->hdesc.bcdVersion);
	hid->venकरोr = le16_to_cpu(ihid->hdesc.wVenकरोrID);
	hid->product = le16_to_cpu(ihid->hdesc.wProductID);

	snम_लिखो(hid->name, माप(hid->name), "%s %04X:%04X",
		 client->name, (u16)hid->venकरोr, (u16)hid->product);
	strlcpy(hid->phys, dev_name(&client->dev), माप(hid->phys));

	ihid->quirks = i2c_hid_lookup_quirk(hid->venकरोr, hid->product);

	ret = hid_add_device(hid);
	अगर (ret) अणु
		अगर (ret != -ENODEV)
			hid_err(client, "can't add hid device: %d\n", ret);
		जाओ err_mem_मुक्त;
	पूर्ण

	वापस 0;

err_mem_मुक्त:
	hid_destroy_device(hid);

err_irq:
	मुक्त_irq(client->irq, ihid);

err_घातered:
	i2c_hid_core_घातer_करोwn(ihid);
	i2c_hid_मुक्त_buffers(ihid);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_hid_core_probe);

पूर्णांक i2c_hid_core_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	काष्ठा hid_device *hid;

	hid = ihid->hid;
	hid_destroy_device(hid);

	मुक्त_irq(client->irq, ihid);

	अगर (ihid->bufsize)
		i2c_hid_मुक्त_buffers(ihid);

	i2c_hid_core_घातer_करोwn(ihid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(i2c_hid_core_हटाओ);

व्योम i2c_hid_core_shutकरोwn(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);

	i2c_hid_set_घातer(client, I2C_HID_PWR_SLEEP);
	मुक्त_irq(client->irq, ihid);

	i2c_hid_core_shutकरोwn_tail(ihid);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_hid_core_shutकरोwn);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक i2c_hid_core_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	काष्ठा hid_device *hid = ihid->hid;
	पूर्णांक ret;
	पूर्णांक wake_status;

	अगर (hid->driver && hid->driver->suspend) अणु
		ret = hid->driver->suspend(hid, PMSG_SUSPEND);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Save some घातer */
	i2c_hid_set_घातer(client, I2C_HID_PWR_SLEEP);

	disable_irq(client->irq);

	अगर (device_may_wakeup(&client->dev)) अणु
		wake_status = enable_irq_wake(client->irq);
		अगर (!wake_status)
			ihid->irq_wake_enabled = true;
		अन्यथा
			hid_warn(hid, "Failed to enable irq wake: %d\n",
				wake_status);
	पूर्ण अन्यथा अणु
		i2c_hid_core_घातer_करोwn(ihid);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_hid_core_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_hid *ihid = i2c_get_clientdata(client);
	काष्ठा hid_device *hid = ihid->hid;
	पूर्णांक wake_status;

	अगर (!device_may_wakeup(&client->dev)) अणु
		i2c_hid_core_घातer_up(ihid);
	पूर्ण अन्यथा अगर (ihid->irq_wake_enabled) अणु
		wake_status = disable_irq_wake(client->irq);
		अगर (!wake_status)
			ihid->irq_wake_enabled = false;
		अन्यथा
			hid_warn(hid, "Failed to disable irq wake: %d\n",
				wake_status);
	पूर्ण

	enable_irq(client->irq);

	/* Instead of resetting device, simply घातers the device on. This
	 * solves "incomplete reports" on Raydium devices 2386:3118 and
	 * 2386:4B33 and fixes various SIS touchscreens no दीर्घer sending
	 * data after a suspend/resume.
	 *
	 * However some ALPS touchpads generate IRQ storm without reset, so
	 * let's still reset them here.
	 */
	अगर (ihid->quirks & I2C_HID_QUIRK_RESET_ON_RESUME)
		ret = i2c_hid_hwreset(client);
	अन्यथा
		ret = i2c_hid_set_घातer(client, I2C_HID_PWR_ON);

	अगर (ret)
		वापस ret;

	अगर (hid->driver && hid->driver->reset_resume) अणु
		ret = hid->driver->reset_resume(hid);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops i2c_hid_core_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(i2c_hid_core_suspend, i2c_hid_core_resume)
पूर्ण;
EXPORT_SYMBOL_GPL(i2c_hid_core_pm);

MODULE_DESCRIPTION("HID over I2C core driver");
MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_LICENSE("GPL");
