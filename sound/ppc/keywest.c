<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * common keywest i2c layer
 *
 * Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */


#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश "pmac.h"

अटल काष्ठा pmac_keywest *keywest_ctx;
अटल bool keywest_probed;

अटल पूर्णांक keywest_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	keywest_probed = true;
	/* If instantiated via i2c-घातermac, we still need to set the client */
	अगर (!keywest_ctx->client)
		keywest_ctx->client = client;
	i2c_set_clientdata(client, keywest_ctx);
	वापस 0;
पूर्ण

/*
 * This is kind of a hack, best would be to turn घातermac to fixed i2c
 * bus numbers and declare the sound device as part of platक्रमm
 * initialization
 */
अटल पूर्णांक keywest_attach_adapter(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i2c_board_info info;
	काष्ठा i2c_client *client;

	अगर (! keywest_ctx)
		वापस -EINVAL;

	अगर (म_भेदन(adapter->name, "mac-io", 6))
		वापस -EINVAL; /* ignored */

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	strscpy(info.type, "keywest", I2C_NAME_SIZE);
	info.addr = keywest_ctx->addr;
	client = i2c_new_client_device(adapter, &info);
	अगर (IS_ERR(client))
		वापस PTR_ERR(client);
	keywest_ctx->client = client;

	/*
	 * We know the driver is alपढ़ोy loaded, so the device should be
	 * alपढ़ोy bound. If not it means binding failed, and then there
	 * is no poपूर्णांक in keeping the device instantiated.
	 */
	अगर (!keywest_ctx->client->dev.driver) अणु
		i2c_unरेजिस्टर_device(keywest_ctx->client);
		keywest_ctx->client = शून्य;
		वापस -ENODEV;
	पूर्ण
	
	/*
	 * Let i2c-core delete that device on driver removal.
	 * This is safe because i2c-core holds the core_lock mutex क्रम us.
	 */
	list_add_tail(&keywest_ctx->client->detected,
		      &to_i2c_driver(keywest_ctx->client->dev.driver)->clients);
	वापस 0;
पूर्ण

अटल पूर्णांक keywest_हटाओ(काष्ठा i2c_client *client)
अणु
	अगर (! keywest_ctx)
		वापस 0;
	अगर (client == keywest_ctx->client)
		keywest_ctx->client = शून्य;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id keywest_i2c_id[] = अणु
	अणु "MAC,tas3004", 0 पूर्ण,		/* instantiated by i2c-घातermac */
	अणु "keywest", 0 पूर्ण,		/* instantiated by us अगर needed */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, keywest_i2c_id);

अटल काष्ठा i2c_driver keywest_driver = अणु
	.driver = अणु
		.name = "PMac Keywest Audio",
	पूर्ण,
	.probe = keywest_probe,
	.हटाओ = keywest_हटाओ,
	.id_table = keywest_i2c_id,
पूर्ण;

/* exported */
व्योम snd_pmac_keywest_cleanup(काष्ठा pmac_keywest *i2c)
अणु
	अगर (keywest_ctx && keywest_ctx == i2c) अणु
		i2c_del_driver(&keywest_driver);
		keywest_ctx = शून्य;
	पूर्ण
पूर्ण

पूर्णांक snd_pmac_tumbler_post_init(व्योम)
अणु
	पूर्णांक err;
	
	अगर (!keywest_ctx || !keywest_ctx->client)
		वापस -ENXIO;

	अगर ((err = keywest_ctx->init_client(keywest_ctx)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "tumbler: %i :cannot initialize the MCS\n", err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* exported */
पूर्णांक snd_pmac_keywest_init(काष्ठा pmac_keywest *i2c)
अणु
	काष्ठा i2c_adapter *adap;
	पूर्णांक err, i = 0;

	अगर (keywest_ctx)
		वापस -EBUSY;

	adap = i2c_get_adapter(0);
	अगर (!adap)
		वापस -EPROBE_DEFER;

	keywest_ctx = i2c;

	अगर ((err = i2c_add_driver(&keywest_driver))) अणु
		snd_prपूर्णांकk(KERN_ERR "cannot register keywest i2c driver\n");
		i2c_put_adapter(adap);
		वापस err;
	पूर्ण

	/* There was alपढ़ोy a device from i2c-घातermac. Great, let's वापस */
	अगर (keywest_probed)
		वापस 0;

	/* We assume Macs have consecutive I2C bus numbers starting at 0 */
	जबतक (adap) अणु
		/* Scan क्रम devices to be bound to */
		err = keywest_attach_adapter(adap);
		अगर (!err)
			वापस 0;
		i2c_put_adapter(adap);
		adap = i2c_get_adapter(++i);
	पूर्ण

	वापस -ENODEV;
पूर्ण
