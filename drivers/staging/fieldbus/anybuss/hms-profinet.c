<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HMS Profinet Client Driver
 *
 * Copyright (C) 2018 Arcx Inc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

/* move to <linux/fieldbus_dev.h> when taking this out of staging */
#समावेश "../fieldbus_dev.h"

/* move to <linux/anybuss-client.h> when taking this out of staging */
#समावेश "anybuss-client.h"

#घोषणा PROFI_DPRAM_SIZE	512

/*
 * ---------------------------------------------------------------
 * Anybus Profinet mailbox messages - definitions
 * ---------------------------------------------------------------
 * note that we're depending on the layout of these काष्ठाures being
 * exactly as advertised.
 */

काष्ठा msg_mac_addr अणु
	u8 addr[6];
पूर्ण;

काष्ठा profi_priv अणु
	काष्ठा fieldbus_dev fbdev;
	काष्ठा anybuss_client *client;
	काष्ठा mutex enable_lock; /* serializes card enable */
	bool घातer_on;
पूर्ण;

अटल sमाप_प्रकार
profi_पढ़ो_area(काष्ठा fieldbus_dev *fbdev, अक्षर __user *buf, माप_प्रकार size,
		loff_t *offset)
अणु
	काष्ठा profi_priv *priv = container_of(fbdev, काष्ठा profi_priv, fbdev);

	वापस anybuss_पढ़ो_output(priv->client, buf, size, offset);
पूर्ण

अटल sमाप_प्रकार
profi_ग_लिखो_area(काष्ठा fieldbus_dev *fbdev, स्थिर अक्षर __user *buf,
		 माप_प्रकार size, loff_t *offset)
अणु
	काष्ठा profi_priv *priv = container_of(fbdev, काष्ठा profi_priv, fbdev);

	वापस anybuss_ग_लिखो_input(priv->client, buf, size, offset);
पूर्ण

अटल पूर्णांक profi_id_get(काष्ठा fieldbus_dev *fbdev, अक्षर *buf,
			माप_प्रकार max_size)
अणु
	काष्ठा profi_priv *priv = container_of(fbdev, काष्ठा profi_priv, fbdev);
	काष्ठा msg_mac_addr response;
	पूर्णांक ret;

	ret = anybuss_recv_msg(priv->client, 0x0010, &response,
			       माप(response));
	अगर (ret < 0)
		वापस ret;
	वापस snम_लिखो(buf, max_size, "%pM\n", response.addr);
पूर्ण

अटल bool profi_enable_get(काष्ठा fieldbus_dev *fbdev)
अणु
	काष्ठा profi_priv *priv = container_of(fbdev, काष्ठा profi_priv, fbdev);
	bool घातer_on;

	mutex_lock(&priv->enable_lock);
	घातer_on = priv->घातer_on;
	mutex_unlock(&priv->enable_lock);

	वापस घातer_on;
पूर्ण

अटल पूर्णांक __profi_enable(काष्ठा profi_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा anybuss_client *client = priv->client;
	/* Initialization Sequence, Generic Anybus Mode */
	स्थिर काष्ठा anybuss_memcfg mem_cfg = अणु
		.input_io = 220,
		.input_dpram = PROFI_DPRAM_SIZE,
		.input_total = PROFI_DPRAM_SIZE,
		.output_io = 220,
		.output_dpram = PROFI_DPRAM_SIZE,
		.output_total = PROFI_DPRAM_SIZE,
		.offl_mode = FIELDBUS_DEV_OFFL_MODE_CLEAR,
	पूर्ण;

	/*
	 * चयन anybus off then on, this ensures we can करो a complete
	 * configuration cycle in हाल anybus was alपढ़ोy on.
	 */
	anybuss_set_घातer(client, false);
	ret = anybuss_set_घातer(client, true);
	अगर (ret)
		जाओ err;
	ret = anybuss_start_init(client, &mem_cfg);
	अगर (ret)
		जाओ err;
	ret = anybuss_finish_init(client);
	अगर (ret)
		जाओ err;
	priv->घातer_on = true;
	वापस 0;

err:
	anybuss_set_घातer(client, false);
	priv->घातer_on = false;
	वापस ret;
पूर्ण

अटल पूर्णांक __profi_disable(काष्ठा profi_priv *priv)
अणु
	काष्ठा anybuss_client *client = priv->client;

	anybuss_set_घातer(client, false);
	priv->घातer_on = false;
	वापस 0;
पूर्ण

अटल पूर्णांक profi_simple_enable(काष्ठा fieldbus_dev *fbdev, bool enable)
अणु
	पूर्णांक ret;
	काष्ठा profi_priv *priv = container_of(fbdev, काष्ठा profi_priv, fbdev);

	mutex_lock(&priv->enable_lock);
	अगर (enable)
		ret = __profi_enable(priv);
	अन्यथा
		ret = __profi_disable(priv);
	mutex_unlock(&priv->enable_lock);

	वापस ret;
पूर्ण

अटल व्योम profi_on_area_updated(काष्ठा anybuss_client *client)
अणु
	काष्ठा profi_priv *priv = anybuss_get_drvdata(client);

	fieldbus_dev_area_updated(&priv->fbdev);
पूर्ण

अटल व्योम profi_on_online_changed(काष्ठा anybuss_client *client, bool online)
अणु
	काष्ठा profi_priv *priv = anybuss_get_drvdata(client);

	fieldbus_dev_online_changed(&priv->fbdev, online);
पूर्ण

अटल पूर्णांक profinet_probe(काष्ठा anybuss_client *client)
अणु
	काष्ठा profi_priv *priv;
	काष्ठा device *dev = &client->dev;
	पूर्णांक err;

	client->on_area_updated = profi_on_area_updated;
	client->on_online_changed = profi_on_online_changed;
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	mutex_init(&priv->enable_lock);
	priv->client = client;
	priv->fbdev.पढ़ो_area_sz = PROFI_DPRAM_SIZE;
	priv->fbdev.ग_लिखो_area_sz = PROFI_DPRAM_SIZE;
	priv->fbdev.card_name = "HMS Profinet IRT (Anybus-S)";
	priv->fbdev.fieldbus_type = FIELDBUS_DEV_TYPE_PROFINET;
	priv->fbdev.पढ़ो_area = profi_पढ़ो_area;
	priv->fbdev.ग_लिखो_area = profi_ग_लिखो_area;
	priv->fbdev.fieldbus_id_get = profi_id_get;
	priv->fbdev.enable_get = profi_enable_get;
	priv->fbdev.simple_enable_set = profi_simple_enable;
	priv->fbdev.parent = dev;
	err = fieldbus_dev_रेजिस्टर(&priv->fbdev);
	अगर (err < 0)
		वापस err;
	dev_info(dev, "card detected, registered as %s",
		 dev_name(priv->fbdev.dev));
	anybuss_set_drvdata(client, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक profinet_हटाओ(काष्ठा anybuss_client *client)
अणु
	काष्ठा profi_priv *priv = anybuss_get_drvdata(client);

	fieldbus_dev_unरेजिस्टर(&priv->fbdev);
	वापस 0;
पूर्ण

अटल काष्ठा anybuss_client_driver profinet_driver = अणु
	.probe = profinet_probe,
	.हटाओ = profinet_हटाओ,
	.driver		= अणु
		.name   = "hms-profinet",
		.owner	= THIS_MODULE,
	पूर्ण,
	.anybus_id = 0x0089,
पूर्ण;

अटल पूर्णांक __init profinet_init(व्योम)
अणु
	वापस anybuss_client_driver_रेजिस्टर(&profinet_driver);
पूर्ण
module_init(profinet_init);

अटल व्योम __निकास profinet_निकास(व्योम)
अणु
	वापस anybuss_client_driver_unरेजिस्टर(&profinet_driver);
पूर्ण
module_निकास(profinet_निकास);

MODULE_AUTHOR("Sven Van Asbroeck <TheSven73@gmail.com>");
MODULE_DESCRIPTION("HMS Profinet IRT Driver (Anybus-S)");
MODULE_LICENSE("GPL v2");
