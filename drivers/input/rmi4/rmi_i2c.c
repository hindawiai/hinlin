<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#समावेश <linux/i2c.h>
#समावेश <linux/rmi.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश "rmi_driver.h"

#घोषणा BUFFER_SIZE_INCREMENT 32

/**
 * काष्ठा rmi_i2c_xport - stores inक्रमmation क्रम i2c communication
 *
 * @xport: The transport पूर्णांकerface काष्ठाure
 * @client: The I2C client device काष्ठाure
 *
 * @page_mutex: Locks current page to aव्योम changing pages in unexpected ways.
 * @page: Keeps track of the current भव page
 *
 * @tx_buf: Buffer used क्रम transmitting data to the sensor over i2c.
 * @tx_buf_size: Size of the buffer
 *
 * @supplies: Array of voltage regulators
 * @startup_delay: Milliseconds to छोड़ो after घातering up the regulators
 */
काष्ठा rmi_i2c_xport अणु
	काष्ठा rmi_transport_dev xport;
	काष्ठा i2c_client *client;

	काष्ठा mutex page_mutex;
	पूर्णांक page;

	u8 *tx_buf;
	माप_प्रकार tx_buf_size;

	काष्ठा regulator_bulk_data supplies[2];
	u32 startup_delay;
पूर्ण;

#घोषणा RMI_PAGE_SELECT_REGISTER 0xff
#घोषणा RMI_I2C_PAGE(addr) (((addr) >> 8) & 0xff)

/*
 * rmi_set_page - Set RMI page
 * @xport: The poपूर्णांकer to the rmi_transport_dev काष्ठा
 * @page: The new page address.
 *
 * RMI devices have 16-bit addressing, but some of the transport
 * implementations (like SMBus) only have 8-bit addressing. So RMI implements
 * a page address at 0xff of every page so we can reliable page addresses
 * every 256 रेजिस्टरs.
 *
 * The page_mutex lock must be held when this function is entered.
 *
 * Returns zero on success, non-zero on failure.
 */
अटल पूर्णांक rmi_set_page(काष्ठा rmi_i2c_xport *rmi_i2c, u8 page)
अणु
	काष्ठा i2c_client *client = rmi_i2c->client;
	u8 txbuf[2] = अणुRMI_PAGE_SELECT_REGISTER, pageपूर्ण;
	पूर्णांक retval;

	retval = i2c_master_send(client, txbuf, माप(txbuf));
	अगर (retval != माप(txbuf)) अणु
		dev_err(&client->dev,
			"%s: set page failed: %d.", __func__, retval);
		वापस (retval < 0) ? retval : -EIO;
	पूर्ण

	rmi_i2c->page = page;
	वापस 0;
पूर्ण

अटल पूर्णांक rmi_i2c_ग_लिखो_block(काष्ठा rmi_transport_dev *xport, u16 addr,
			       स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_i2c_xport *rmi_i2c =
		container_of(xport, काष्ठा rmi_i2c_xport, xport);
	काष्ठा i2c_client *client = rmi_i2c->client;
	माप_प्रकार tx_size = len + 1;
	पूर्णांक retval;

	mutex_lock(&rmi_i2c->page_mutex);

	अगर (!rmi_i2c->tx_buf || rmi_i2c->tx_buf_size < tx_size) अणु
		अगर (rmi_i2c->tx_buf)
			devm_kमुक्त(&client->dev, rmi_i2c->tx_buf);
		rmi_i2c->tx_buf_size = tx_size + BUFFER_SIZE_INCREMENT;
		rmi_i2c->tx_buf = devm_kzalloc(&client->dev,
					       rmi_i2c->tx_buf_size,
					       GFP_KERNEL);
		अगर (!rmi_i2c->tx_buf) अणु
			rmi_i2c->tx_buf_size = 0;
			retval = -ENOMEM;
			जाओ निकास;
		पूर्ण
	पूर्ण

	rmi_i2c->tx_buf[0] = addr & 0xff;
	स_नकल(rmi_i2c->tx_buf + 1, buf, len);

	अगर (RMI_I2C_PAGE(addr) != rmi_i2c->page) अणु
		retval = rmi_set_page(rmi_i2c, RMI_I2C_PAGE(addr));
		अगर (retval)
			जाओ निकास;
	पूर्ण

	retval = i2c_master_send(client, rmi_i2c->tx_buf, tx_size);
	अगर (retval == tx_size)
		retval = 0;
	अन्यथा अगर (retval >= 0)
		retval = -EIO;

निकास:
	rmi_dbg(RMI_DEBUG_XPORT, &client->dev,
		"write %zd bytes at %#06x: %d (%*ph)\n",
		len, addr, retval, (पूर्णांक)len, buf);

	mutex_unlock(&rmi_i2c->page_mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक rmi_i2c_पढ़ो_block(काष्ठा rmi_transport_dev *xport, u16 addr,
			      व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_i2c_xport *rmi_i2c =
		container_of(xport, काष्ठा rmi_i2c_xport, xport);
	काष्ठा i2c_client *client = rmi_i2c->client;
	u8 addr_offset = addr & 0xff;
	पूर्णांक retval;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.len	= माप(addr_offset),
			.buf	= &addr_offset,
		पूर्ण,
		अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
			.len	= len,
			.buf	= buf,
		पूर्ण,
	पूर्ण;

	mutex_lock(&rmi_i2c->page_mutex);

	अगर (RMI_I2C_PAGE(addr) != rmi_i2c->page) अणु
		retval = rmi_set_page(rmi_i2c, RMI_I2C_PAGE(addr));
		अगर (retval)
			जाओ निकास;
	पूर्ण

	retval = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (retval == ARRAY_SIZE(msgs))
		retval = 0; /* success */
	अन्यथा अगर (retval >= 0)
		retval = -EIO;

निकास:
	rmi_dbg(RMI_DEBUG_XPORT, &client->dev,
		"read %zd bytes at %#06x: %d (%*ph)\n",
		len, addr, retval, (पूर्णांक)len, buf);

	mutex_unlock(&rmi_i2c->page_mutex);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा rmi_transport_ops rmi_i2c_ops = अणु
	.ग_लिखो_block	= rmi_i2c_ग_लिखो_block,
	.पढ़ो_block	= rmi_i2c_पढ़ो_block,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id rmi_i2c_of_match[] = अणु
	अणु .compatible = "syna,rmi4-i2c" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rmi_i2c_of_match);
#पूर्ण_अगर

अटल व्योम rmi_i2c_regulator_bulk_disable(व्योम *data)
अणु
	काष्ठा rmi_i2c_xport *rmi_i2c = data;

	regulator_bulk_disable(ARRAY_SIZE(rmi_i2c->supplies),
			       rmi_i2c->supplies);
पूर्ण

अटल व्योम rmi_i2c_unरेजिस्टर_transport(व्योम *data)
अणु
	काष्ठा rmi_i2c_xport *rmi_i2c = data;

	rmi_unरेजिस्टर_transport_device(&rmi_i2c->xport);
पूर्ण

अटल पूर्णांक rmi_i2c_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rmi_device_platक्रमm_data *pdata;
	काष्ठा rmi_device_platक्रमm_data *client_pdata =
					dev_get_platdata(&client->dev);
	काष्ठा rmi_i2c_xport *rmi_i2c;
	पूर्णांक error;

	rmi_i2c = devm_kzalloc(&client->dev, माप(काष्ठा rmi_i2c_xport),
				GFP_KERNEL);
	अगर (!rmi_i2c)
		वापस -ENOMEM;

	pdata = &rmi_i2c->xport.pdata;

	अगर (!client->dev.of_node && client_pdata)
		*pdata = *client_pdata;

	pdata->irq = client->irq;

	rmi_dbg(RMI_DEBUG_XPORT, &client->dev, "Probing %s.\n",
			dev_name(&client->dev));

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev,
			"adapter does not support required functionality\n");
		वापस -ENODEV;
	पूर्ण

	rmi_i2c->supplies[0].supply = "vdd";
	rmi_i2c->supplies[1].supply = "vio";
	error = devm_regulator_bulk_get(&client->dev,
					 ARRAY_SIZE(rmi_i2c->supplies),
					 rmi_i2c->supplies);
	अगर (error < 0)
		वापस error;

	error = regulator_bulk_enable(ARRAY_SIZE(rmi_i2c->supplies),
				       rmi_i2c->supplies);
	अगर (error < 0)
		वापस error;

	error = devm_add_action_or_reset(&client->dev,
					  rmi_i2c_regulator_bulk_disable,
					  rmi_i2c);
	अगर (error)
		वापस error;

	of_property_पढ़ो_u32(client->dev.of_node, "syna,startup-delay-ms",
			     &rmi_i2c->startup_delay);

	msleep(rmi_i2c->startup_delay);

	rmi_i2c->client = client;
	mutex_init(&rmi_i2c->page_mutex);

	rmi_i2c->xport.dev = &client->dev;
	rmi_i2c->xport.proto_name = "i2c";
	rmi_i2c->xport.ops = &rmi_i2c_ops;

	i2c_set_clientdata(client, rmi_i2c);

	/*
	 * Setting the page to zero will (a) make sure the PSR is in a
	 * known state, and (b) make sure we can talk to the device.
	 */
	error = rmi_set_page(rmi_i2c, 0);
	अगर (error) अणु
		dev_err(&client->dev, "Failed to set page select to 0\n");
		वापस error;
	पूर्ण

	dev_info(&client->dev, "registering I2C-connected sensor\n");

	error = rmi_रेजिस्टर_transport_device(&rmi_i2c->xport);
	अगर (error) अणु
		dev_err(&client->dev, "failed to register sensor: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_add_action_or_reset(&client->dev,
					  rmi_i2c_unरेजिस्टर_transport,
					  rmi_i2c);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rmi_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rmi_i2c_xport *rmi_i2c = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = rmi_driver_suspend(rmi_i2c->xport.rmi_dev, true);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	regulator_bulk_disable(ARRAY_SIZE(rmi_i2c->supplies),
			       rmi_i2c->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक rmi_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rmi_i2c_xport *rmi_i2c = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(rmi_i2c->supplies),
				    rmi_i2c->supplies);
	अगर (ret)
		वापस ret;

	msleep(rmi_i2c->startup_delay);

	ret = rmi_driver_resume(rmi_i2c->xport.rmi_dev, true);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rmi_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rmi_i2c_xport *rmi_i2c = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = rmi_driver_suspend(rmi_i2c->xport.rmi_dev, false);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	regulator_bulk_disable(ARRAY_SIZE(rmi_i2c->supplies),
			       rmi_i2c->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rmi_i2c_xport *rmi_i2c = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(rmi_i2c->supplies),
				    rmi_i2c->supplies);
	अगर (ret)
		वापस ret;

	msleep(rmi_i2c->startup_delay);

	ret = rmi_driver_resume(rmi_i2c->xport.rmi_dev, false);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rmi_i2c_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rmi_i2c_suspend, rmi_i2c_resume)
	SET_RUNTIME_PM_OPS(rmi_i2c_runसमय_suspend, rmi_i2c_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rmi_id[] = अणु
	अणु "rmi4_i2c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rmi_id);

अटल काष्ठा i2c_driver rmi_i2c_driver = अणु
	.driver = अणु
		.name	= "rmi4_i2c",
		.pm	= &rmi_i2c_pm,
		.of_match_table = of_match_ptr(rmi_i2c_of_match),
	पूर्ण,
	.id_table	= rmi_id,
	.probe		= rmi_i2c_probe,
पूर्ण;

module_i2c_driver(rmi_i2c_driver);

MODULE_AUTHOR("Christopher Heiny <cheiny@synaptics.com>");
MODULE_AUTHOR("Andrew Duggan <aduggan@synaptics.com>");
MODULE_DESCRIPTION("RMI I2C driver");
MODULE_LICENSE("GPL");
