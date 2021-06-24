<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Nano River Technologies viperboard i2c master driver
 *
 *  (C) 2012 by Lemonage GmbH
 *  Author: Lars Poeschel <poeschel@lemonage.de>
 *  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>

#समावेश <linux/mfd/viperboard.h>

काष्ठा vprbrd_i2c अणु
	काष्ठा i2c_adapter i2c;
	u8 bus_freq_param;
पूर्ण;

/* i2c bus frequency module parameter */
अटल u8 i2c_bus_param;
अटल अचिन्हित पूर्णांक i2c_bus_freq = 100;
module_param(i2c_bus_freq, पूर्णांक, 0);
MODULE_PARM_DESC(i2c_bus_freq,
	"i2c bus frequency in khz (default is 100) valid values: 10, 100, 200, 400, 1000, 3000, 6000");

अटल पूर्णांक vprbrd_i2c_status(काष्ठा i2c_adapter *i2c,
	काष्ठा vprbrd_i2c_status *status, bool prev_error)
अणु
	u16 bytes_xfer;
	पूर्णांक ret;
	काष्ठा vprbrd *vb = (काष्ठा vprbrd *)i2c->algo_data;

	/* check क्रम protocol error */
	bytes_xfer = माप(काष्ठा vprbrd_i2c_status);

	ret = usb_control_msg(vb->usb_dev, usb_rcvctrlpipe(vb->usb_dev, 0),
		VPRBRD_USB_REQUEST_I2C, VPRBRD_USB_TYPE_IN, 0x0000, 0x0000,
		status, bytes_xfer, VPRBRD_USB_TIMEOUT_MS);

	अगर (ret != bytes_xfer)
		prev_error = true;

	अगर (prev_error) अणु
		dev_err(&i2c->dev, "failure in usb communication\n");
		वापस -EREMOTEIO;
	पूर्ण

	dev_dbg(&i2c->dev, "  status = %d\n", status->status);
	अगर (status->status != 0x00) अणु
		dev_err(&i2c->dev, "failure: i2c protocol error\n");
		वापस -EPROTO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vprbrd_i2c_receive(काष्ठा usb_device *usb_dev,
	काष्ठा vprbrd_i2c_पढ़ो_msg *rmsg, पूर्णांक bytes_xfer)
अणु
	पूर्णांक ret, bytes_actual;
	पूर्णांक error = 0;

	/* send the पढ़ो request */
	ret = usb_bulk_msg(usb_dev,
		usb_sndbulkpipe(usb_dev, VPRBRD_EP_OUT), rmsg,
		माप(काष्ठा vprbrd_i2c_पढ़ो_hdr), &bytes_actual,
		VPRBRD_USB_TIMEOUT_MS);

	अगर ((ret < 0)
		|| (bytes_actual != माप(काष्ठा vprbrd_i2c_पढ़ो_hdr))) अणु
		dev_err(&usb_dev->dev, "failure transmitting usb\n");
		error = -EREMOTEIO;
	पूर्ण

	/* पढ़ो the actual data */
	ret = usb_bulk_msg(usb_dev,
		usb_rcvbulkpipe(usb_dev, VPRBRD_EP_IN), rmsg,
		bytes_xfer, &bytes_actual, VPRBRD_USB_TIMEOUT_MS);

	अगर ((ret < 0) || (bytes_xfer != bytes_actual)) अणु
		dev_err(&usb_dev->dev, "failure receiving usb\n");
		error = -EREMOTEIO;
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक vprbrd_i2c_addr(काष्ठा usb_device *usb_dev,
	काष्ठा vprbrd_i2c_addr_msg *amsg)
अणु
	पूर्णांक ret, bytes_actual;

	ret = usb_bulk_msg(usb_dev,
		usb_sndbulkpipe(usb_dev, VPRBRD_EP_OUT), amsg,
		माप(काष्ठा vprbrd_i2c_addr_msg), &bytes_actual,
		VPRBRD_USB_TIMEOUT_MS);

	अगर ((ret < 0) ||
			(माप(काष्ठा vprbrd_i2c_addr_msg) != bytes_actual)) अणु
		dev_err(&usb_dev->dev, "failure transmitting usb\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vprbrd_i2c_पढ़ो(काष्ठा vprbrd *vb, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक ret;
	u16 reमुख्य_len, len1, len2, start = 0x0000;
	काष्ठा vprbrd_i2c_पढ़ो_msg *rmsg =
		(काष्ठा vprbrd_i2c_पढ़ो_msg *)vb->buf;

	reमुख्य_len = msg->len;
	rmsg->header.cmd = VPRBRD_I2C_CMD_READ;
	जबतक (reमुख्य_len > 0) अणु
		rmsg->header.addr = cpu_to_le16(start + 0x4000);
		अगर (reमुख्य_len <= 255) अणु
			len1 = reमुख्य_len;
			len2 = 0x00;
			rmsg->header.len0 = reमुख्य_len;
			rmsg->header.len1 = 0x00;
			rmsg->header.len2 = 0x00;
			rmsg->header.len3 = 0x00;
			rmsg->header.len4 = 0x00;
			rmsg->header.len5 = 0x00;
			reमुख्य_len = 0;
		पूर्ण अन्यथा अगर (reमुख्य_len <= 510) अणु
			len1 = reमुख्य_len;
			len2 = 0x00;
			rmsg->header.len0 = reमुख्य_len - 255;
			rmsg->header.len1 = 0xff;
			rmsg->header.len2 = 0x00;
			rmsg->header.len3 = 0x00;
			rmsg->header.len4 = 0x00;
			rmsg->header.len5 = 0x00;
			reमुख्य_len = 0;
		पूर्ण अन्यथा अगर (reमुख्य_len <= 512) अणु
			len1 = reमुख्य_len;
			len2 = 0x00;
			rmsg->header.len0 = reमुख्य_len - 510;
			rmsg->header.len1 = 0xff;
			rmsg->header.len2 = 0xff;
			rmsg->header.len3 = 0x00;
			rmsg->header.len4 = 0x00;
			rmsg->header.len5 = 0x00;
			reमुख्य_len = 0;
		पूर्ण अन्यथा अगर (reमुख्य_len <= 767) अणु
			len1 = 512;
			len2 = reमुख्य_len - 512;
			rmsg->header.len0 = 0x02;
			rmsg->header.len1 = 0xff;
			rmsg->header.len2 = 0xff;
			rmsg->header.len3 = reमुख्य_len - 512;
			rmsg->header.len4 = 0x00;
			rmsg->header.len5 = 0x00;
			reमुख्य_len = 0;
		पूर्ण अन्यथा अगर (reमुख्य_len <= 1022) अणु
			len1 = 512;
			len2 = reमुख्य_len - 512;
			rmsg->header.len0 = 0x02;
			rmsg->header.len1 = 0xff;
			rmsg->header.len2 = 0xff;
			rmsg->header.len3 = reमुख्य_len - 767;
			rmsg->header.len4 = 0xff;
			rmsg->header.len5 = 0x00;
			reमुख्य_len = 0;
		पूर्ण अन्यथा अगर (reमुख्य_len <= 1024) अणु
			len1 = 512;
			len2 = reमुख्य_len - 512;
			rmsg->header.len0 = 0x02;
			rmsg->header.len1 = 0xff;
			rmsg->header.len2 = 0xff;
			rmsg->header.len3 = reमुख्य_len - 1022;
			rmsg->header.len4 = 0xff;
			rmsg->header.len5 = 0xff;
			reमुख्य_len = 0;
		पूर्ण अन्यथा अणु
			len1 = 512;
			len2 = 512;
			rmsg->header.len0 = 0x02;
			rmsg->header.len1 = 0xff;
			rmsg->header.len2 = 0xff;
			rmsg->header.len3 = 0x02;
			rmsg->header.len4 = 0xff;
			rmsg->header.len5 = 0xff;
			reमुख्य_len -= 1024;
			start += 1024;
		पूर्ण
		rmsg->header.tf1 = cpu_to_le16(len1);
		rmsg->header.tf2 = cpu_to_le16(len2);

		/* first पढ़ो transfer */
		ret = vprbrd_i2c_receive(vb->usb_dev, rmsg, len1);
		अगर (ret < 0)
			वापस ret;
		/* copy the received data */
		स_नकल(msg->buf + start, rmsg, len1);

		/* second पढ़ो transfer अगर neccessary */
		अगर (len2 > 0) अणु
			ret = vprbrd_i2c_receive(vb->usb_dev, rmsg, len2);
			अगर (ret < 0)
				वापस ret;
			/* copy the received data */
			स_नकल(msg->buf + start + 512, rmsg, len2);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vprbrd_i2c_ग_लिखो(काष्ठा vprbrd *vb, काष्ठा i2c_msg *msg)
अणु
	पूर्णांक ret, bytes_actual;
	u16 reमुख्य_len, bytes_xfer,
		start = 0x0000;
	काष्ठा vprbrd_i2c_ग_लिखो_msg *wmsg =
		(काष्ठा vprbrd_i2c_ग_लिखो_msg *)vb->buf;

	reमुख्य_len = msg->len;
	wmsg->header.cmd = VPRBRD_I2C_CMD_WRITE;
	wmsg->header.last = 0x00;
	wmsg->header.chan = 0x00;
	wmsg->header.spi = 0x0000;
	जबतक (reमुख्य_len > 0) अणु
		wmsg->header.addr = cpu_to_le16(start + 0x4000);
		अगर (reमुख्य_len > 503) अणु
			wmsg->header.len1 = 0xff;
			wmsg->header.len2 = 0xf8;
			reमुख्य_len -= 503;
			bytes_xfer = 503 + माप(काष्ठा vprbrd_i2c_ग_लिखो_hdr);
			start += 503;
		पूर्ण अन्यथा अगर (reमुख्य_len > 255) अणु
			wmsg->header.len1 = 0xff;
			wmsg->header.len2 = (reमुख्य_len - 255);
			bytes_xfer = reमुख्य_len +
				माप(काष्ठा vprbrd_i2c_ग_लिखो_hdr);
			reमुख्य_len = 0;
		पूर्ण अन्यथा अणु
			wmsg->header.len1 = reमुख्य_len;
			wmsg->header.len2 = 0x00;
			bytes_xfer = reमुख्य_len +
				माप(काष्ठा vprbrd_i2c_ग_लिखो_hdr);
			reमुख्य_len = 0;
		पूर्ण
		स_नकल(wmsg->data, msg->buf + start,
			bytes_xfer - माप(काष्ठा vprbrd_i2c_ग_लिखो_hdr));

		ret = usb_bulk_msg(vb->usb_dev,
			usb_sndbulkpipe(vb->usb_dev,
			VPRBRD_EP_OUT), wmsg,
			bytes_xfer, &bytes_actual, VPRBRD_USB_TIMEOUT_MS);
		अगर ((ret < 0) || (bytes_xfer != bytes_actual))
			वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vprbrd_i2c_xfer(काष्ठा i2c_adapter *i2c, काष्ठा i2c_msg *msgs,
		पूर्णांक num)
अणु
	काष्ठा i2c_msg *pmsg;
	पूर्णांक i, ret,
		error = 0;
	काष्ठा vprbrd *vb = (काष्ठा vprbrd *)i2c->algo_data;
	काष्ठा vprbrd_i2c_addr_msg *amsg =
		(काष्ठा vprbrd_i2c_addr_msg *)vb->buf;
	काष्ठा vprbrd_i2c_status *smsg = (काष्ठा vprbrd_i2c_status *)vb->buf;

	dev_dbg(&i2c->dev, "master xfer %d messages:\n", num);

	क्रम (i = 0 ; i < num ; i++) अणु
		pmsg = &msgs[i];

		dev_dbg(&i2c->dev,
			"  %d: %s (flags %d) %d bytes to 0x%02x\n",
			i, pmsg->flags & I2C_M_RD ? "read" : "write",
			pmsg->flags, pmsg->len, pmsg->addr);

		mutex_lock(&vb->lock);
		/* directly send the message */
		अगर (pmsg->flags & I2C_M_RD) अणु
			/* पढ़ो data */
			amsg->cmd = VPRBRD_I2C_CMD_ADDR;
			amsg->unknown2 = 0x00;
			amsg->unknown3 = 0x00;
			amsg->addr = pmsg->addr;
			amsg->unknown1 = 0x01;
			amsg->len = cpu_to_le16(pmsg->len);
			/* send the addr and len, we're पूर्णांकerested to board */
			ret = vprbrd_i2c_addr(vb->usb_dev, amsg);
			अगर (ret < 0)
				error = ret;

			ret = vprbrd_i2c_पढ़ो(vb, pmsg);
			अगर (ret < 0)
				error = ret;

			ret = vprbrd_i2c_status(i2c, smsg, error);
			अगर (ret < 0)
				error = ret;
			/* in हाल of protocol error, वापस the error */
			अगर (error < 0)
				जाओ error;
		पूर्ण अन्यथा अणु
			/* ग_लिखो data */
			ret = vprbrd_i2c_ग_लिखो(vb, pmsg);

			amsg->cmd = VPRBRD_I2C_CMD_ADDR;
			amsg->unknown2 = 0x00;
			amsg->unknown3 = 0x00;
			amsg->addr = pmsg->addr;
			amsg->unknown1 = 0x00;
			amsg->len = cpu_to_le16(pmsg->len);
			/* send the addr, the data goes to to board */
			ret = vprbrd_i2c_addr(vb->usb_dev, amsg);
			अगर (ret < 0)
				error = ret;

			ret = vprbrd_i2c_status(i2c, smsg, error);
			अगर (ret < 0)
				error = ret;

			अगर (error < 0)
				जाओ error;
		पूर्ण
		mutex_unlock(&vb->lock);
	पूर्ण
	वापस num;
error:
	mutex_unlock(&vb->lock);
	वापस error;
पूर्ण

अटल u32 vprbrd_i2c_func(काष्ठा i2c_adapter *i2c)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

/* This is the actual algorithm we define */
अटल स्थिर काष्ठा i2c_algorithm vprbrd_algorithm = अणु
	.master_xfer	= vprbrd_i2c_xfer,
	.functionality	= vprbrd_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks vprbrd_quirks = अणु
	.max_पढ़ो_len = 2048,
	.max_ग_लिखो_len = 2048,
पूर्ण;

अटल पूर्णांक vprbrd_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vprbrd *vb = dev_get_drvdata(pdev->dev.parent);
	काष्ठा vprbrd_i2c *vb_i2c;
	पूर्णांक ret;
	पूर्णांक pipe;

	vb_i2c = devm_kzalloc(&pdev->dev, माप(*vb_i2c), GFP_KERNEL);
	अगर (vb_i2c == शून्य)
		वापस -ENOMEM;

	/* setup i2c adapter description */
	vb_i2c->i2c.owner = THIS_MODULE;
	vb_i2c->i2c.class = I2C_CLASS_HWMON;
	vb_i2c->i2c.algo = &vprbrd_algorithm;
	vb_i2c->i2c.quirks = &vprbrd_quirks;
	vb_i2c->i2c.algo_data = vb;
	/* save the param in usb capabable memory */
	vb_i2c->bus_freq_param = i2c_bus_param;

	snम_लिखो(vb_i2c->i2c.name, माप(vb_i2c->i2c.name),
		 "viperboard at bus %03d device %03d",
		 vb->usb_dev->bus->busnum, vb->usb_dev->devnum);

	/* setting the bus frequency */
	अगर ((i2c_bus_param <= VPRBRD_I2C_FREQ_10KHZ)
		&& (i2c_bus_param >= VPRBRD_I2C_FREQ_6MHZ)) अणु
		pipe = usb_sndctrlpipe(vb->usb_dev, 0);
		ret = usb_control_msg(vb->usb_dev, pipe,
			VPRBRD_USB_REQUEST_I2C_FREQ, VPRBRD_USB_TYPE_OUT,
			0x0000, 0x0000, &vb_i2c->bus_freq_param, 1,
			VPRBRD_USB_TIMEOUT_MS);
		अगर (ret != 1) अणु
			dev_err(&pdev->dev, "failure setting i2c_bus_freq to %d\n",
				i2c_bus_freq);
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev,
			"invalid i2c_bus_freq setting:%d\n", i2c_bus_freq);
		वापस -EIO;
	पूर्ण

	vb_i2c->i2c.dev.parent = &pdev->dev;

	/* attach to i2c layer */
	i2c_add_adapter(&vb_i2c->i2c);

	platक्रमm_set_drvdata(pdev, vb_i2c);

	वापस 0;
पूर्ण

अटल पूर्णांक vprbrd_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vprbrd_i2c *vb_i2c = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&vb_i2c->i2c);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vprbrd_i2c_driver = अणु
	.driver.name	= "viperboard-i2c",
	.driver.owner	= THIS_MODULE,
	.probe		= vprbrd_i2c_probe,
	.हटाओ		= vprbrd_i2c_हटाओ,
पूर्ण;

अटल पूर्णांक __init vprbrd_i2c_init(व्योम)
अणु
	चयन (i2c_bus_freq) अणु
	हाल 6000:
		i2c_bus_param = VPRBRD_I2C_FREQ_6MHZ;
		अवरोध;
	हाल 3000:
		i2c_bus_param = VPRBRD_I2C_FREQ_3MHZ;
		अवरोध;
	हाल 1000:
		i2c_bus_param = VPRBRD_I2C_FREQ_1MHZ;
		अवरोध;
	हाल 400:
		i2c_bus_param = VPRBRD_I2C_FREQ_400KHZ;
		अवरोध;
	हाल 200:
		i2c_bus_param = VPRBRD_I2C_FREQ_200KHZ;
		अवरोध;
	हाल 100:
		i2c_bus_param = VPRBRD_I2C_FREQ_100KHZ;
		अवरोध;
	हाल 10:
		i2c_bus_param = VPRBRD_I2C_FREQ_10KHZ;
		अवरोध;
	शेष:
		pr_warn("invalid i2c_bus_freq (%d)\n", i2c_bus_freq);
		i2c_bus_param = VPRBRD_I2C_FREQ_100KHZ;
	पूर्ण

	वापस platक्रमm_driver_रेजिस्टर(&vprbrd_i2c_driver);
पूर्ण
subsys_initcall(vprbrd_i2c_init);

अटल व्योम __निकास vprbrd_i2c_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&vprbrd_i2c_driver);
पूर्ण
module_निकास(vprbrd_i2c_निकास);

MODULE_AUTHOR("Lars Poeschel <poeschel@lemonage.de>");
MODULE_DESCRIPTION("I2C master driver for Nano River Techs Viperboard");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:viperboard-i2c");
