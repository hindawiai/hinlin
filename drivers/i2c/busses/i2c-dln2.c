<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Diolan DLN-2 USB-I2C adapter
 *
 * Copyright (c) 2014 Intel Corporation
 *
 * Derived from:
 *  i2c-diolan-u2c.c
 *  Copyright (c) 2010-2011 Ericsson AB
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/dln2.h>
#समावेश <linux/acpi.h>

#घोषणा DLN2_I2C_MODULE_ID		0x03
#घोषणा DLN2_I2C_CMD(cmd)		DLN2_CMD(cmd, DLN2_I2C_MODULE_ID)

/* I2C commands */
#घोषणा DLN2_I2C_GET_PORT_COUNT		DLN2_I2C_CMD(0x00)
#घोषणा DLN2_I2C_ENABLE			DLN2_I2C_CMD(0x01)
#घोषणा DLN2_I2C_DISABLE		DLN2_I2C_CMD(0x02)
#घोषणा DLN2_I2C_IS_ENABLED		DLN2_I2C_CMD(0x03)
#घोषणा DLN2_I2C_WRITE			DLN2_I2C_CMD(0x06)
#घोषणा DLN2_I2C_READ			DLN2_I2C_CMD(0x07)
#घोषणा DLN2_I2C_SCAN_DEVICES		DLN2_I2C_CMD(0x08)
#घोषणा DLN2_I2C_PULLUP_ENABLE		DLN2_I2C_CMD(0x09)
#घोषणा DLN2_I2C_PULLUP_DISABLE		DLN2_I2C_CMD(0x0A)
#घोषणा DLN2_I2C_PULLUP_IS_ENABLED	DLN2_I2C_CMD(0x0B)
#घोषणा DLN2_I2C_TRANSFER		DLN2_I2C_CMD(0x0C)
#घोषणा DLN2_I2C_SET_MAX_REPLY_COUNT	DLN2_I2C_CMD(0x0D)
#घोषणा DLN2_I2C_GET_MAX_REPLY_COUNT	DLN2_I2C_CMD(0x0E)

#घोषणा DLN2_I2C_MAX_XFER_SIZE		256
#घोषणा DLN2_I2C_BUF_SIZE		(DLN2_I2C_MAX_XFER_SIZE + 16)

काष्ठा dln2_i2c अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा i2c_adapter adapter;
	u8 port;
	/*
	 * Buffer to hold the packet क्रम पढ़ो or ग_लिखो transfers. One is enough
	 * since we can't have multiple transfers in parallel on the i2c bus.
	 */
	व्योम *buf;
पूर्ण;

अटल पूर्णांक dln2_i2c_enable(काष्ठा dln2_i2c *dln2, bool enable)
अणु
	u16 cmd;
	काष्ठा अणु
		u8 port;
	पूर्ण tx;

	tx.port = dln2->port;

	अगर (enable)
		cmd = DLN2_I2C_ENABLE;
	अन्यथा
		cmd = DLN2_I2C_DISABLE;

	वापस dln2_transfer_tx(dln2->pdev, cmd, &tx, माप(tx));
पूर्ण

अटल पूर्णांक dln2_i2c_ग_लिखो(काष्ठा dln2_i2c *dln2, u8 addr,
			  u8 *data, u16 data_len)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
		u8 addr;
		u8 mem_addr_len;
		__le32 mem_addr;
		__le16 buf_len;
		u8 buf[DLN2_I2C_MAX_XFER_SIZE];
	पूर्ण __packed *tx = dln2->buf;
	अचिन्हित len;

	BUILD_BUG_ON(माप(*tx) > DLN2_I2C_BUF_SIZE);

	tx->port = dln2->port;
	tx->addr = addr;
	tx->mem_addr_len = 0;
	tx->mem_addr = 0;
	tx->buf_len = cpu_to_le16(data_len);
	स_नकल(tx->buf, data, data_len);

	len = माप(*tx) + data_len - DLN2_I2C_MAX_XFER_SIZE;
	ret = dln2_transfer_tx(dln2->pdev, DLN2_I2C_WRITE, tx, len);
	अगर (ret < 0)
		वापस ret;

	वापस data_len;
पूर्ण

अटल पूर्णांक dln2_i2c_पढ़ो(काष्ठा dln2_i2c *dln2, u16 addr, u8 *data,
			 u16 data_len)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
		u8 addr;
		u8 mem_addr_len;
		__le32 mem_addr;
		__le16 buf_len;
	पूर्ण __packed tx;
	काष्ठा अणु
		__le16 buf_len;
		u8 buf[DLN2_I2C_MAX_XFER_SIZE];
	पूर्ण __packed *rx = dln2->buf;
	अचिन्हित rx_len = माप(*rx);

	BUILD_BUG_ON(माप(*rx) > DLN2_I2C_BUF_SIZE);

	tx.port = dln2->port;
	tx.addr = addr;
	tx.mem_addr_len = 0;
	tx.mem_addr = 0;
	tx.buf_len = cpu_to_le16(data_len);

	ret = dln2_transfer(dln2->pdev, DLN2_I2C_READ, &tx, माप(tx),
			    rx, &rx_len);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_len < माप(rx->buf_len) + data_len)
		वापस -EPROTO;
	अगर (le16_to_cpu(rx->buf_len) != data_len)
		वापस -EPROTO;

	स_नकल(data, rx->buf, data_len);

	वापस data_len;
पूर्ण

अटल पूर्णांक dln2_i2c_xfer(काष्ठा i2c_adapter *adapter,
			 काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा dln2_i2c *dln2 = i2c_get_adapdata(adapter);
	काष्ठा i2c_msg *pmsg;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		पूर्णांक ret;

		pmsg = &msgs[i];

		अगर (pmsg->flags & I2C_M_RD) अणु
			ret = dln2_i2c_पढ़ो(dln2, pmsg->addr, pmsg->buf,
					    pmsg->len);
			अगर (ret < 0)
				वापस ret;

			pmsg->len = ret;
		पूर्ण अन्यथा अणु
			ret = dln2_i2c_ग_लिखो(dln2, pmsg->addr, pmsg->buf,
					     pmsg->len);
			अगर (ret != pmsg->len)
				वापस -EPROTO;
		पूर्ण
	पूर्ण

	वापस num;
पूर्ण

अटल u32 dln2_i2c_func(काष्ठा i2c_adapter *a)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_BLOCK_PROC_CALL |
		I2C_FUNC_SMBUS_I2C_BLOCK;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm dln2_i2c_usb_algorithm = अणु
	.master_xfer = dln2_i2c_xfer,
	.functionality = dln2_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks dln2_i2c_quirks = अणु
	.max_पढ़ो_len = DLN2_I2C_MAX_XFER_SIZE,
	.max_ग_लिखो_len = DLN2_I2C_MAX_XFER_SIZE,
पूर्ण;

अटल पूर्णांक dln2_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा dln2_i2c *dln2;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dln2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	dln2 = devm_kzalloc(dev, माप(*dln2), GFP_KERNEL);
	अगर (!dln2)
		वापस -ENOMEM;

	dln2->buf = devm_kदो_स्मृति(dev, DLN2_I2C_BUF_SIZE, GFP_KERNEL);
	अगर (!dln2->buf)
		वापस -ENOMEM;

	dln2->pdev = pdev;
	dln2->port = pdata->port;

	/* setup i2c adapter description */
	dln2->adapter.owner = THIS_MODULE;
	dln2->adapter.class = I2C_CLASS_HWMON;
	dln2->adapter.algo = &dln2_i2c_usb_algorithm;
	dln2->adapter.quirks = &dln2_i2c_quirks;
	dln2->adapter.dev.parent = dev;
	ACPI_COMPANION_SET(&dln2->adapter.dev, ACPI_COMPANION(&pdev->dev));
	dln2->adapter.dev.of_node = dev->of_node;
	i2c_set_adapdata(&dln2->adapter, dln2);
	snम_लिखो(dln2->adapter.name, माप(dln2->adapter.name), "%s-%s-%d",
		 "dln2-i2c", dev_name(pdev->dev.parent), dln2->port);

	platक्रमm_set_drvdata(pdev, dln2);

	/* initialize the i2c पूर्णांकerface */
	ret = dln2_i2c_enable(dln2, true);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to initialize adapter: %d\n", ret);
		वापस ret;
	पूर्ण

	/* and finally attach to i2c layer */
	ret = i2c_add_adapter(&dln2->adapter);
	अगर (ret < 0)
		जाओ out_disable;

	वापस 0;

out_disable:
	dln2_i2c_enable(dln2, false);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dln2_i2c *dln2 = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&dln2->adapter);
	dln2_i2c_enable(dln2, false);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dln2_i2c_driver = अणु
	.driver.name	= "dln2-i2c",
	.probe		= dln2_i2c_probe,
	.हटाओ		= dln2_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(dln2_i2c_driver);

MODULE_AUTHOR("Laurentiu Palcu <laurentiu.palcu@intel.com>");
MODULE_DESCRIPTION("Driver for the Diolan DLN2 I2C master interface");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dln2-i2c");
