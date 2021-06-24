<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip / Aपंचांगel SHA204A (I2C) driver.
 *
 * Copyright (c) 2019 Linaro, Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश "atmel-i2c.h"

अटल व्योम aपंचांगel_sha204a_rng_करोne(काष्ठा aपंचांगel_i2c_work_data *work_data,
				   व्योम *areq, पूर्णांक status)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv = work_data->ctx;
	काष्ठा hwrng *rng = areq;

	अगर (status)
		dev_warn_ratelimited(&i2c_priv->client->dev,
				     "i2c transaction failed (%d)\n",
				     status);

	rng->priv = (अचिन्हित दीर्घ)work_data;
	atomic_dec(&i2c_priv->tfm_count);
पूर्ण

अटल पूर्णांक aपंचांगel_sha204a_rng_पढ़ो_nonblocking(काष्ठा hwrng *rng, व्योम *data,
					      माप_प्रकार max)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv;
	काष्ठा aपंचांगel_i2c_work_data *work_data;

	i2c_priv = container_of(rng, काष्ठा aपंचांगel_i2c_client_priv, hwrng);

	/* keep maximum 1 asynchronous पढ़ो in flight at any समय */
	अगर (!atomic_add_unless(&i2c_priv->tfm_count, 1, 1))
		वापस 0;

	अगर (rng->priv) अणु
		work_data = (काष्ठा aपंचांगel_i2c_work_data *)rng->priv;
		max = min(माप(work_data->cmd.data), max);
		स_नकल(data, &work_data->cmd.data, max);
		rng->priv = 0;
	पूर्ण अन्यथा अणु
		work_data = kदो_स्मृति(माप(*work_data), GFP_ATOMIC);
		अगर (!work_data)
			वापस -ENOMEM;

		work_data->ctx = i2c_priv;
		work_data->client = i2c_priv->client;

		max = 0;
	पूर्ण

	aपंचांगel_i2c_init_अक्रमom_cmd(&work_data->cmd);
	aपंचांगel_i2c_enqueue(work_data, aपंचांगel_sha204a_rng_करोne, rng);

	वापस max;
पूर्ण

अटल पूर्णांक aपंचांगel_sha204a_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max,
				  bool रुको)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv;
	काष्ठा aपंचांगel_i2c_cmd cmd;
	पूर्णांक ret;

	अगर (!रुको)
		वापस aपंचांगel_sha204a_rng_पढ़ो_nonblocking(rng, data, max);

	i2c_priv = container_of(rng, काष्ठा aपंचांगel_i2c_client_priv, hwrng);

	aपंचांगel_i2c_init_अक्रमom_cmd(&cmd);

	ret = aपंचांगel_i2c_send_receive(i2c_priv->client, &cmd);
	अगर (ret)
		वापस ret;

	max = min(माप(cmd.data), max);
	स_नकल(data, cmd.data, max);

	वापस max;
पूर्ण

अटल पूर्णांक aपंचांगel_sha204a_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv;
	पूर्णांक ret;

	ret = aपंचांगel_i2c_probe(client, id);
	अगर (ret)
		वापस ret;

	i2c_priv = i2c_get_clientdata(client);

	स_रखो(&i2c_priv->hwrng, 0, माप(i2c_priv->hwrng));

	i2c_priv->hwrng.name = dev_name(&client->dev);
	i2c_priv->hwrng.पढ़ो = aपंचांगel_sha204a_rng_पढ़ो;
	i2c_priv->hwrng.quality = 1024;

	ret = devm_hwrng_रेजिस्टर(&client->dev, &i2c_priv->hwrng);
	अगर (ret)
		dev_warn(&client->dev, "failed to register RNG (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_sha204a_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा aपंचांगel_i2c_client_priv *i2c_priv = i2c_get_clientdata(client);

	अगर (atomic_पढ़ो(&i2c_priv->tfm_count)) अणु
		dev_err(&client->dev, "Device is busy\n");
		वापस -EBUSY;
	पूर्ण

	अगर (i2c_priv->hwrng.priv)
		kमुक्त((व्योम *)i2c_priv->hwrng.priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_sha204a_dt_ids[] = अणु
	अणु .compatible = "atmel,atsha204a", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_sha204a_dt_ids);

अटल स्थिर काष्ठा i2c_device_id aपंचांगel_sha204a_id[] = अणु
	अणु "atsha204a", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, aपंचांगel_sha204a_id);

अटल काष्ठा i2c_driver aपंचांगel_sha204a_driver = अणु
	.probe			= aपंचांगel_sha204a_probe,
	.हटाओ			= aपंचांगel_sha204a_हटाओ,
	.id_table		= aपंचांगel_sha204a_id,

	.driver.name		= "atmel-sha204a",
	.driver.of_match_table	= of_match_ptr(aपंचांगel_sha204a_dt_ids),
पूर्ण;

अटल पूर्णांक __init aपंचांगel_sha204a_init(व्योम)
अणु
	वापस i2c_add_driver(&aपंचांगel_sha204a_driver);
पूर्ण

अटल व्योम __निकास aपंचांगel_sha204a_निकास(व्योम)
अणु
	flush_scheduled_work();
	i2c_del_driver(&aपंचांगel_sha204a_driver);
पूर्ण

module_init(aपंचांगel_sha204a_init);
module_निकास(aपंचांगel_sha204a_निकास);

MODULE_AUTHOR("Ard Biesheuvel <ard.biesheuvel@linaro.org>");
MODULE_LICENSE("GPL v2");
