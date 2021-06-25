<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Pericom PI3USB30532 Type-C cross चयन / mux driver
 *
 * Copyright (c) 2017-2018 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb/typec_dp.h>
#समावेश <linux/usb/typec_mux.h>

#घोषणा PI3USB30532_CONF			0x00

#घोषणा PI3USB30532_CONF_OPEN			0x00
#घोषणा PI3USB30532_CONF_SWAP			0x01
#घोषणा PI3USB30532_CONF_4LANE_DP		0x02
#घोषणा PI3USB30532_CONF_USB3			0x04
#घोषणा PI3USB30532_CONF_USB3_AND_2LANE_DP	0x06

काष्ठा pi3usb30532 अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock; /* protects the cached conf रेजिस्टर */
	काष्ठा typec_चयन *sw;
	काष्ठा typec_mux *mux;
	u8 conf;
पूर्ण;

अटल पूर्णांक pi3usb30532_set_conf(काष्ठा pi3usb30532 *pi, u8 new_conf)
अणु
	पूर्णांक ret = 0;

	अगर (pi->conf == new_conf)
		वापस 0;

	ret = i2c_smbus_ग_लिखो_byte_data(pi->client, PI3USB30532_CONF, new_conf);
	अगर (ret) अणु
		dev_err(&pi->client->dev, "Error writing conf: %d\n", ret);
		वापस ret;
	पूर्ण

	pi->conf = new_conf;
	वापस 0;
पूर्ण

अटल पूर्णांक pi3usb30532_sw_set(काष्ठा typec_चयन *sw,
			      क्रमागत typec_orientation orientation)
अणु
	काष्ठा pi3usb30532 *pi = typec_चयन_get_drvdata(sw);
	u8 new_conf;
	पूर्णांक ret;

	mutex_lock(&pi->lock);
	new_conf = pi->conf;

	चयन (orientation) अणु
	हाल TYPEC_ORIENTATION_NONE:
		new_conf = PI3USB30532_CONF_OPEN;
		अवरोध;
	हाल TYPEC_ORIENTATION_NORMAL:
		new_conf &= ~PI3USB30532_CONF_SWAP;
		अवरोध;
	हाल TYPEC_ORIENTATION_REVERSE:
		new_conf |= PI3USB30532_CONF_SWAP;
		अवरोध;
	पूर्ण

	ret = pi3usb30532_set_conf(pi, new_conf);
	mutex_unlock(&pi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
pi3usb30532_mux_set(काष्ठा typec_mux *mux, काष्ठा typec_mux_state *state)
अणु
	काष्ठा pi3usb30532 *pi = typec_mux_get_drvdata(mux);
	u8 new_conf;
	पूर्णांक ret;

	mutex_lock(&pi->lock);
	new_conf = pi->conf;

	चयन (state->mode) अणु
	हाल TYPEC_STATE_SAFE:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_OPEN;
		अवरोध;
	हाल TYPEC_STATE_USB:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_USB3;
		अवरोध;
	हाल TYPEC_DP_STATE_C:
	हाल TYPEC_DP_STATE_E:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_4LANE_DP;
		अवरोध;
	हाल TYPEC_DP_STATE_D:
		new_conf = (new_conf & PI3USB30532_CONF_SWAP) |
			   PI3USB30532_CONF_USB3_AND_2LANE_DP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = pi3usb30532_set_conf(pi, new_conf);
	mutex_unlock(&pi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pi3usb30532_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा typec_चयन_desc sw_desc = अणु पूर्ण;
	काष्ठा typec_mux_desc mux_desc = अणु पूर्ण;
	काष्ठा pi3usb30532 *pi;
	पूर्णांक ret;

	pi = devm_kzalloc(dev, माप(*pi), GFP_KERNEL);
	अगर (!pi)
		वापस -ENOMEM;

	pi->client = client;
	mutex_init(&pi->lock);

	ret = i2c_smbus_पढ़ो_byte_data(client, PI3USB30532_CONF);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading config register %d\n", ret);
		वापस ret;
	पूर्ण
	pi->conf = ret;

	sw_desc.drvdata = pi;
	sw_desc.fwnode = dev->fwnode;
	sw_desc.set = pi3usb30532_sw_set;

	pi->sw = typec_चयन_रेजिस्टर(dev, &sw_desc);
	अगर (IS_ERR(pi->sw)) अणु
		dev_err(dev, "Error registering typec switch: %ld\n",
			PTR_ERR(pi->sw));
		वापस PTR_ERR(pi->sw);
	पूर्ण

	mux_desc.drvdata = pi;
	mux_desc.fwnode = dev->fwnode;
	mux_desc.set = pi3usb30532_mux_set;

	pi->mux = typec_mux_रेजिस्टर(dev, &mux_desc);
	अगर (IS_ERR(pi->mux)) अणु
		typec_चयन_unरेजिस्टर(pi->sw);
		dev_err(dev, "Error registering typec mux: %ld\n",
			PTR_ERR(pi->mux));
		वापस PTR_ERR(pi->mux);
	पूर्ण

	i2c_set_clientdata(client, pi);
	वापस 0;
पूर्ण

अटल पूर्णांक pi3usb30532_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pi3usb30532 *pi = i2c_get_clientdata(client);

	typec_mux_unरेजिस्टर(pi->mux);
	typec_चयन_unरेजिस्टर(pi->sw);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pi3usb30532_table[] = अणु
	अणु "pi3usb30532" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pi3usb30532_table);

अटल काष्ठा i2c_driver pi3usb30532_driver = अणु
	.driver = अणु
		.name = "pi3usb30532",
	पूर्ण,
	.probe_new	= pi3usb30532_probe,
	.हटाओ		= pi3usb30532_हटाओ,
	.id_table	= pi3usb30532_table,
पूर्ण;

module_i2c_driver(pi3usb30532_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Pericom PI3USB30532 Type-C mux driver");
MODULE_LICENSE("GPL");
