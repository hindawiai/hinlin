<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IBM OPAL I2C driver
 * Copyright (C) 2014 IBM
 */

#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/opal.h>

अटल पूर्णांक i2c_opal_translate_error(पूर्णांक rc)
अणु
	चयन (rc) अणु
	हाल OPAL_NO_MEM:
		वापस -ENOMEM;
	हाल OPAL_PARAMETER:
		वापस -EINVAL;
	हाल OPAL_I2C_ARBT_LOST:
		वापस -EAGAIN;
	हाल OPAL_I2C_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल OPAL_I2C_NACK_RCVD:
		वापस -ENXIO;
	हाल OPAL_I2C_STOP_ERR:
		वापस -EBUSY;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक i2c_opal_send_request(u32 bus_id, काष्ठा opal_i2c_request *req)
अणु
	काष्ठा opal_msg msg;
	पूर्णांक token, rc;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			pr_err("Failed to get the async token\n");

		वापस token;
	पूर्ण

	rc = opal_i2c_request(token, bus_id, req);
	अगर (rc != OPAL_ASYNC_COMPLETION) अणु
		rc = i2c_opal_translate_error(rc);
		जाओ निकास;
	पूर्ण

	rc = opal_async_रुको_response(token, &msg);
	अगर (rc)
		जाओ निकास;

	rc = opal_get_async_rc(msg);
	अगर (rc != OPAL_SUCCESS) अणु
		rc = i2c_opal_translate_error(rc);
		जाओ निकास;
	पूर्ण

निकास:
	opal_async_release_token(token);
	वापस rc;
पूर्ण

अटल पूर्णांक i2c_opal_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	अचिन्हित दीर्घ opal_id = (अचिन्हित दीर्घ)adap->algo_data;
	काष्ठा opal_i2c_request req;
	पूर्णांक rc, i;

	/* We only support fairly simple combinations here of one
	 * or two messages
	 */
	स_रखो(&req, 0, माप(req));
	चयन(num) अणु
	हाल 1:
		req.type = (msgs[0].flags & I2C_M_RD) ?
			OPAL_I2C_RAW_READ : OPAL_I2C_RAW_WRITE;
		req.addr = cpu_to_be16(msgs[0].addr);
		req.size = cpu_to_be32(msgs[0].len);
		req.buffer_ra = cpu_to_be64(__pa(msgs[0].buf));
		अवरोध;
	हाल 2:
		req.type = (msgs[1].flags & I2C_M_RD) ?
			OPAL_I2C_SM_READ : OPAL_I2C_SM_WRITE;
		req.addr = cpu_to_be16(msgs[0].addr);
		req.subaddr_sz = msgs[0].len;
		क्रम (i = 0; i < msgs[0].len; i++)
			req.subaddr = (req.subaddr << 8) | msgs[0].buf[i];
		req.subaddr = cpu_to_be32(req.subaddr);
		req.size = cpu_to_be32(msgs[1].len);
		req.buffer_ra = cpu_to_be64(__pa(msgs[1].buf));
		अवरोध;
	पूर्ण

	rc = i2c_opal_send_request(opal_id, &req);
	अगर (rc)
		वापस rc;

	वापस num;
पूर्ण

अटल पूर्णांक i2c_opal_smbus_xfer(काष्ठा i2c_adapter *adap, u16 addr,
			       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			       u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	अचिन्हित दीर्घ opal_id = (अचिन्हित दीर्घ)adap->algo_data;
	काष्ठा opal_i2c_request req;
	u8 local[2];
	पूर्णांक rc;

	स_रखो(&req, 0, माप(req));

	req.addr = cpu_to_be16(addr);
	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
		req.buffer_ra = cpu_to_be64(__pa(&data->byte));
		req.size = cpu_to_be32(1);
		fallthrough;
	हाल I2C_SMBUS_QUICK:
		req.type = (पढ़ो_ग_लिखो == I2C_SMBUS_READ) ?
			OPAL_I2C_RAW_READ : OPAL_I2C_RAW_WRITE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		req.buffer_ra = cpu_to_be64(__pa(&data->byte));
		req.size = cpu_to_be32(1);
		req.subaddr = cpu_to_be32(command);
		req.subaddr_sz = 1;
		req.type = (पढ़ो_ग_लिखो == I2C_SMBUS_READ) ?
			OPAL_I2C_SM_READ : OPAL_I2C_SM_WRITE;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		अगर (!पढ़ो_ग_लिखो) अणु
			local[0] = data->word & 0xff;
			local[1] = (data->word >> 8) & 0xff;
		पूर्ण
		req.buffer_ra = cpu_to_be64(__pa(local));
		req.size = cpu_to_be32(2);
		req.subaddr = cpu_to_be32(command);
		req.subaddr_sz = 1;
		req.type = (पढ़ो_ग_लिखो == I2C_SMBUS_READ) ?
			OPAL_I2C_SM_READ : OPAL_I2C_SM_WRITE;
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		req.buffer_ra = cpu_to_be64(__pa(&data->block[1]));
		req.size = cpu_to_be32(data->block[0]);
		req.subaddr = cpu_to_be32(command);
		req.subaddr_sz = 1;
		req.type = (पढ़ो_ग_लिखो == I2C_SMBUS_READ) ?
			OPAL_I2C_SM_READ : OPAL_I2C_SM_WRITE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rc = i2c_opal_send_request(opal_id, &req);
	अगर (!rc && पढ़ो_ग_लिखो && size == I2C_SMBUS_WORD_DATA) अणु
		data->word = ((u16)local[1]) << 8;
		data->word |= local[0];
	पूर्ण

	वापस rc;
पूर्ण

अटल u32 i2c_opal_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	       I2C_FUNC_SMBUS_I2C_BLOCK;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i2c_opal_algo = अणु
	.master_xfer	= i2c_opal_master_xfer,
	.smbus_xfer	= i2c_opal_smbus_xfer,
	.functionality	= i2c_opal_func,
पूर्ण;

/*
 * For two messages, we basically support simple smbus transactions of a
 * ग_लिखो-then-anything.
 */
अटल स्थिर काष्ठा i2c_adapter_quirks i2c_opal_quirks = अणु
	.flags = I2C_AQ_COMB | I2C_AQ_COMB_WRITE_FIRST | I2C_AQ_COMB_SAME_ADDR,
	.max_comb_1st_msg_len = 4,
पूर्ण;

अटल पूर्णांक i2c_opal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_adapter	*adapter;
	स्थिर अक्षर		*pname;
	u32			opal_id;
	पूर्णांक			rc;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	rc = of_property_पढ़ो_u32(pdev->dev.of_node, "ibm,opal-id", &opal_id);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Missing ibm,opal-id property !\n");
		वापस -EIO;
	पूर्ण

	adapter = devm_kzalloc(&pdev->dev, माप(*adapter), GFP_KERNEL);
	अगर (!adapter)
		वापस -ENOMEM;

	adapter->algo = &i2c_opal_algo;
	adapter->algo_data = (व्योम *)(अचिन्हित दीर्घ)opal_id;
	adapter->quirks = &i2c_opal_quirks;
	adapter->dev.parent = &pdev->dev;
	adapter->dev.of_node = of_node_get(pdev->dev.of_node);
	pname = of_get_property(pdev->dev.of_node, "ibm,port-name", शून्य);
	अगर (pname)
		strlcpy(adapter->name, pname, माप(adapter->name));
	अन्यथा
		strlcpy(adapter->name, "opal", माप(adapter->name));

	platक्रमm_set_drvdata(pdev, adapter);
	rc = i2c_add_adapter(adapter);
	अगर (rc)
		dev_err(&pdev->dev, "Failed to register the i2c adapter\n");

	वापस rc;
पूर्ण

अटल पूर्णांक i2c_opal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_adapter *adapter = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(adapter);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_opal_of_match[] = अणु
	अणु
		.compatible = "ibm,opal-i2c",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_opal_of_match);

अटल काष्ठा platक्रमm_driver i2c_opal_driver = अणु
	.probe	= i2c_opal_probe,
	.हटाओ	= i2c_opal_हटाओ,
	.driver	= अणु
		.name		= "i2c-opal",
		.of_match_table	= i2c_opal_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init i2c_opal_init(व्योम)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&i2c_opal_driver);
पूर्ण
module_init(i2c_opal_init);

अटल व्योम __निकास i2c_opal_निकास(व्योम)
अणु
	वापस platक्रमm_driver_unरेजिस्टर(&i2c_opal_driver);
पूर्ण
module_निकास(i2c_opal_निकास);

MODULE_AUTHOR("Neelesh Gupta <neelegup@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("IBM OPAL I2C driver");
MODULE_LICENSE("GPL");
