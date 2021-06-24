<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * i2c support क्रम Silicon Lअसल' CP2615 Digital Audio Bridge
 *
 * (c) 2021, Bence Csथकkथँs <bence98@sch.bme.hu>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb.h>

/** CP2615 I/O Protocol implementation */

#घोषणा CP2615_VID 0x10c4
#घोषणा CP2615_PID 0xeac1

#घोषणा IOP_EP_IN  0x82
#घोषणा IOP_EP_OUT 0x02
#घोषणा IOP_IFN 1
#घोषणा IOP_ALTSETTING 2

#घोषणा MAX_IOP_SIZE 64
#घोषणा MAX_IOP_PAYLOAD_SIZE (MAX_IOP_SIZE - 6)
#घोषणा MAX_I2C_SIZE (MAX_IOP_PAYLOAD_SIZE - 4)

क्रमागत cp2615_iop_msg_type अणु
	iop_GetAccessoryInfo = 0xD100,
	iop_AccessoryInfo = 0xA100,
	iop_GetPortConfiguration = 0xD203,
	iop_PortConfiguration = 0xA203,
	iop_DoI2cTransfer = 0xD400,
	iop_I2cTransferResult = 0xA400,
	iop_GetSerialState = 0xD501,
	iop_SerialState = 0xA501
पूर्ण;

काष्ठा __packed cp2615_iop_msg अणु
	__be16 preamble, length, msg;
	u8 data[MAX_IOP_PAYLOAD_SIZE];
पूर्ण;

#घोषणा PART_ID_A01 0x1400
#घोषणा PART_ID_A02 0x1500

काष्ठा __packed cp2615_iop_accessory_info अणु
	__be16 part_id, option_id, proto_ver;
पूर्ण;

काष्ठा __packed cp2615_i2c_transfer अणु
	u8 tag, i2caddr, पढ़ो_len, ग_लिखो_len;
	u8 data[MAX_I2C_SIZE];
पूर्ण;

/* Possible values क्रम काष्ठा cp2615_i2c_transfer_result.status */
क्रमागत cp2615_i2c_status अणु
	/* Writing to the पूर्णांकernal EEPROM failed, because it is locked */
	CP2615_CFG_LOCKED = -6,
	/* पढ़ो_len or ग_लिखो_len out of range */
	CP2615_INVALID_PARAM = -4,
	/* I2C slave did not ACK in समय */
	CP2615_TIMEOUT,
	/* I2C bus busy */
	CP2615_BUS_BUSY,
	/* I2C bus error (ie. device NAK'd the request) */
	CP2615_BUS_ERROR,
	CP2615_SUCCESS
पूर्ण;

काष्ठा __packed cp2615_i2c_transfer_result अणु
	u8 tag, i2caddr;
	s8 status;
	u8 पढ़ो_len;
	u8 data[MAX_I2C_SIZE];
पूर्ण;

अटल पूर्णांक cp2615_init_iop_msg(काष्ठा cp2615_iop_msg *ret, क्रमागत cp2615_iop_msg_type msg,
			स्थिर व्योम *data, माप_प्रकार data_len)
अणु
	अगर (data_len > MAX_IOP_PAYLOAD_SIZE)
		वापस -EFBIG;

	अगर (!ret)
		वापस -EINVAL;

	ret->preamble = 0x2A2A;
	ret->length = htons(data_len + 6);
	ret->msg = htons(msg);
	अगर (data && data_len)
		स_नकल(&ret->data, data, data_len);
	वापस 0;
पूर्ण

अटल पूर्णांक cp2615_init_i2c_msg(काष्ठा cp2615_iop_msg *ret, स्थिर काष्ठा cp2615_i2c_transfer *data)
अणु
	वापस cp2615_init_iop_msg(ret, iop_DoI2cTransfer, data, 4 + data->ग_लिखो_len);
पूर्ण

/* Translates status codes to Linux त्रुटि_सं's */
अटल पूर्णांक cp2615_check_status(क्रमागत cp2615_i2c_status status)
अणु
	चयन (status) अणु
	हाल CP2615_SUCCESS:
			वापस 0;
	हाल CP2615_BUS_ERROR:
		वापस -ENXIO;
	हाल CP2615_BUS_BUSY:
		वापस -EAGAIN;
	हाल CP2615_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल CP2615_INVALID_PARAM:
		वापस -EINVAL;
	हाल CP2615_CFG_LOCKED:
		वापस -EPERM;
	पूर्ण
	/* Unknown error code */
	वापस -EPROTO;
पूर्ण

/** Driver code */

अटल पूर्णांक
cp2615_i2c_send(काष्ठा usb_पूर्णांकerface *usbअगर, काष्ठा cp2615_i2c_transfer *i2c_w)
अणु
	काष्ठा cp2615_iop_msg *msg = kzalloc(माप(*msg), GFP_KERNEL);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	पूर्णांक res = cp2615_init_i2c_msg(msg, i2c_w);

	अगर (!res)
		res = usb_bulk_msg(usbdev, usb_sndbulkpipe(usbdev, IOP_EP_OUT),
				   msg, ntohs(msg->length), शून्य, 0);
	kमुक्त(msg);
	वापस res;
पूर्ण

अटल पूर्णांक
cp2615_i2c_recv(काष्ठा usb_पूर्णांकerface *usbअगर, अचिन्हित अक्षर tag, व्योम *buf)
अणु
	काष्ठा cp2615_iop_msg *msg = kzalloc(माप(*msg), GFP_KERNEL);
	काष्ठा cp2615_i2c_transfer_result *i2c_r = (काष्ठा cp2615_i2c_transfer_result *)&msg->data;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	पूर्णांक res = usb_bulk_msg(usbdev, usb_rcvbulkpipe(usbdev, IOP_EP_IN),
			       msg, माप(काष्ठा cp2615_iop_msg), शून्य, 0);

	अगर (res < 0) अणु
		kमुक्त(msg);
		वापस res;
	पूर्ण

	अगर (msg->msg != htons(iop_I2cTransferResult) || i2c_r->tag != tag) अणु
		kमुक्त(msg);
		वापस -EIO;
	पूर्ण

	res = cp2615_check_status(i2c_r->status);
	अगर (!res)
		स_नकल(buf, &i2c_r->data, i2c_r->पढ़ो_len);

	kमुक्त(msg);
	वापस res;
पूर्ण

/* Checks अगर the IOP is functional by querying the part's ID */
अटल पूर्णांक cp2615_check_iop(काष्ठा usb_पूर्णांकerface *usbअगर)
अणु
	काष्ठा cp2615_iop_msg *msg = kzalloc(माप(*msg), GFP_KERNEL);
	काष्ठा cp2615_iop_accessory_info *info = (काष्ठा cp2615_iop_accessory_info *)&msg->data;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	पूर्णांक res = cp2615_init_iop_msg(msg, iop_GetAccessoryInfo, शून्य, 0);

	अगर (res)
		जाओ out;

	res = usb_bulk_msg(usbdev, usb_sndbulkpipe(usbdev, IOP_EP_OUT),
				   msg, ntohs(msg->length), शून्य, 0);
	अगर (res)
		जाओ out;

	res = usb_bulk_msg(usbdev, usb_rcvbulkpipe(usbdev, IOP_EP_IN),
			       msg, माप(काष्ठा cp2615_iop_msg), शून्य, 0);
	अगर (res)
		जाओ out;

	अगर (msg->msg != htons(iop_AccessoryInfo)) अणु
		res = -EIO;
		जाओ out;
	पूर्ण

	चयन (ntohs(info->part_id)) अणु
	हाल PART_ID_A01:
		dev_dbg(&usbअगर->dev, "Found A01 part. (WARNING: errata exists!)\n");
		अवरोध;
	हाल PART_ID_A02:
		dev_dbg(&usbअगर->dev, "Found good A02 part.\n");
		अवरोध;
	शेष:
		dev_warn(&usbअगर->dev, "Unknown part ID %04X\n", ntohs(info->part_id));
	पूर्ण

out:
	kमुक्त(msg);
	वापस res;
पूर्ण

अटल पूर्णांक
cp2615_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा usb_पूर्णांकerface *usbअगर = adap->algo_data;
	पूर्णांक i = 0, ret = 0;
	काष्ठा i2c_msg *msg;
	काष्ठा cp2615_i2c_transfer i2c_w = अणु0पूर्ण;

	dev_dbg(&usbअगर->dev, "Doing %d I2C transactions\n", num);

	क्रम (; !ret && i < num; i++) अणु
		msg = &msgs[i];

		i2c_w.tag = 0xdd;
		i2c_w.i2caddr = i2c_8bit_addr_from_msg(msg);
		अगर (msg->flags & I2C_M_RD) अणु
			i2c_w.पढ़ो_len = msg->len;
			i2c_w.ग_लिखो_len = 0;
		पूर्ण अन्यथा अणु
			i2c_w.पढ़ो_len = 0;
			i2c_w.ग_लिखो_len = msg->len;
			स_नकल(&i2c_w.data, msg->buf, i2c_w.ग_लिखो_len);
		पूर्ण
		ret = cp2615_i2c_send(usbअगर, &i2c_w);
		अगर (ret)
			अवरोध;
		ret = cp2615_i2c_recv(usbअगर, i2c_w.tag, msg->buf);
	पूर्ण
	अगर (ret < 0)
		वापस ret;
	वापस i;
पूर्ण

अटल u32
cp2615_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cp2615_i2c_algo = अणु
	.master_xfer	= cp2615_i2c_master_xfer,
	.functionality	= cp2615_i2c_func,
पूर्ण;

/*
 * This chip has some limitations: one is that the USB endpoपूर्णांक
 * can only receive 64 bytes/transfer, that leaves 54 bytes क्रम
 * the I2C transfer. On top of that, EITHER पढ़ो_len OR ग_लिखो_len
 * may be zero, but not both. If both are non-zero, the adapter
 * issues a ग_लिखो followed by a पढ़ो. And the chip करोes not
 * support repeated START between the ग_लिखो and पढ़ो phases.
 */
अटल काष्ठा i2c_adapter_quirks cp2615_i2c_quirks = अणु
	.max_ग_लिखो_len = MAX_I2C_SIZE,
	.max_पढ़ो_len = MAX_I2C_SIZE,
	.flags = I2C_AQ_COMB_WRITE_THEN_READ | I2C_AQ_NO_ZERO_LEN | I2C_AQ_NO_REP_START,
	.max_comb_1st_msg_len = MAX_I2C_SIZE,
	.max_comb_2nd_msg_len = MAX_I2C_SIZE
पूर्ण;

अटल व्योम
cp2615_i2c_हटाओ(काष्ठा usb_पूर्णांकerface *usbअगर)
अणु
	काष्ठा i2c_adapter *adap = usb_get_पूर्णांकfdata(usbअगर);

	usb_set_पूर्णांकfdata(usbअगर, शून्य);
	i2c_del_adapter(adap);
पूर्ण

अटल पूर्णांक
cp2615_i2c_probe(काष्ठा usb_पूर्णांकerface *usbअगर, स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा i2c_adapter *adap;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);

	ret = usb_set_पूर्णांकerface(usbdev, IOP_IFN, IOP_ALTSETTING);
	अगर (ret)
		वापस ret;

	ret = cp2615_check_iop(usbअगर);
	अगर (ret)
		वापस ret;

	adap = devm_kzalloc(&usbअगर->dev, माप(काष्ठा i2c_adapter), GFP_KERNEL);
	अगर (!adap)
		वापस -ENOMEM;

	म_नकलन(adap->name, usbdev->serial, माप(adap->name) - 1);
	adap->owner = THIS_MODULE;
	adap->dev.parent = &usbअगर->dev;
	adap->dev.of_node = usbअगर->dev.of_node;
	adap->समयout = HZ;
	adap->algo = &cp2615_i2c_algo;
	adap->quirks = &cp2615_i2c_quirks;
	adap->algo_data = usbअगर;

	ret = i2c_add_adapter(adap);
	अगर (ret)
		वापस ret;

	usb_set_पूर्णांकfdata(usbअगर, adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE_INTERFACE_NUMBER(CP2615_VID, CP2615_PID, IOP_IFN) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

अटल काष्ठा usb_driver cp2615_i2c_driver = अणु
	.name = "i2c-cp2615",
	.probe = cp2615_i2c_probe,
	.disconnect = cp2615_i2c_हटाओ,
	.id_table = id_table,
पूर्ण;

module_usb_driver(cp2615_i2c_driver);

MODULE_AUTHOR("Bence Csथकkथँs <bence98@sch.bme.hu>");
MODULE_DESCRIPTION("CP2615 I2C bus driver");
MODULE_LICENSE("GPL");
