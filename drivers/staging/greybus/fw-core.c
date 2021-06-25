<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus Firmware Core Bundle Driver.
 *
 * Copyright 2016 Google Inc.
 * Copyright 2016 Linaro Ltd.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/firmware.h>
#समावेश <linux/greybus.h>
#समावेश "firmware.h"
#समावेश "spilib.h"

काष्ठा gb_fw_core अणु
	काष्ठा gb_connection	*करोwnload_connection;
	काष्ठा gb_connection	*mgmt_connection;
	काष्ठा gb_connection	*spi_connection;
	काष्ठा gb_connection	*cap_connection;
पूर्ण;

अटल काष्ठा spilib_ops *spilib_ops;

काष्ठा gb_connection *to_fw_mgmt_connection(काष्ठा device *dev)
अणु
	काष्ठा gb_fw_core *fw_core = dev_get_drvdata(dev);

	वापस fw_core->mgmt_connection;
पूर्ण

अटल पूर्णांक gb_fw_spi_connection_init(काष्ठा gb_connection *connection)
अणु
	पूर्णांक ret;

	अगर (!connection)
		वापस 0;

	ret = gb_connection_enable(connection);
	अगर (ret)
		वापस ret;

	ret = gb_spilib_master_init(connection, &connection->bundle->dev,
				    spilib_ops);
	अगर (ret) अणु
		gb_connection_disable(connection);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gb_fw_spi_connection_निकास(काष्ठा gb_connection *connection)
अणु
	अगर (!connection)
		वापस;

	gb_spilib_master_निकास(connection);
	gb_connection_disable(connection);
पूर्ण

अटल पूर्णांक gb_fw_core_probe(काष्ठा gb_bundle *bundle,
			    स्थिर काष्ठा greybus_bundle_id *id)
अणु
	काष्ठा greybus_descriptor_cport *cport_desc;
	काष्ठा gb_connection *connection;
	काष्ठा gb_fw_core *fw_core;
	पूर्णांक ret, i;
	u16 cport_id;
	u8 protocol_id;

	fw_core = kzalloc(माप(*fw_core), GFP_KERNEL);
	अगर (!fw_core)
		वापस -ENOMEM;

	/* Parse CPorts and create connections */
	क्रम (i = 0; i < bundle->num_cports; i++) अणु
		cport_desc = &bundle->cport_desc[i];
		cport_id = le16_to_cpu(cport_desc->id);
		protocol_id = cport_desc->protocol_id;

		चयन (protocol_id) अणु
		हाल GREYBUS_PROTOCOL_FW_MANAGEMENT:
			/* Disallow multiple Firmware Management CPorts */
			अगर (fw_core->mgmt_connection) अणु
				dev_err(&bundle->dev,
					"multiple management CPorts found\n");
				ret = -EINVAL;
				जाओ err_destroy_connections;
			पूर्ण

			connection = gb_connection_create(bundle, cport_id,
						gb_fw_mgmt_request_handler);
			अगर (IS_ERR(connection)) अणु
				ret = PTR_ERR(connection);
				dev_err(&bundle->dev,
					"failed to create management connection (%d)\n",
					ret);
				जाओ err_destroy_connections;
			पूर्ण

			fw_core->mgmt_connection = connection;
			अवरोध;
		हाल GREYBUS_PROTOCOL_FW_DOWNLOAD:
			/* Disallow multiple Firmware Download CPorts */
			अगर (fw_core->करोwnload_connection) अणु
				dev_err(&bundle->dev,
					"multiple download CPorts found\n");
				ret = -EINVAL;
				जाओ err_destroy_connections;
			पूर्ण

			connection = gb_connection_create(bundle, cport_id,
						gb_fw_करोwnload_request_handler);
			अगर (IS_ERR(connection)) अणु
				dev_err(&bundle->dev, "failed to create download connection (%ld)\n",
					PTR_ERR(connection));
			पूर्ण अन्यथा अणु
				fw_core->करोwnload_connection = connection;
			पूर्ण

			अवरोध;
		हाल GREYBUS_PROTOCOL_SPI:
			/* Disallow multiple SPI CPorts */
			अगर (fw_core->spi_connection) अणु
				dev_err(&bundle->dev,
					"multiple SPI CPorts found\n");
				ret = -EINVAL;
				जाओ err_destroy_connections;
			पूर्ण

			connection = gb_connection_create(bundle, cport_id,
							  शून्य);
			अगर (IS_ERR(connection)) अणु
				dev_err(&bundle->dev, "failed to create SPI connection (%ld)\n",
					PTR_ERR(connection));
			पूर्ण अन्यथा अणु
				fw_core->spi_connection = connection;
			पूर्ण

			अवरोध;
		हाल GREYBUS_PROTOCOL_AUTHENTICATION:
			/* Disallow multiple CAP CPorts */
			अगर (fw_core->cap_connection) अणु
				dev_err(&bundle->dev, "multiple Authentication CPorts found\n");
				ret = -EINVAL;
				जाओ err_destroy_connections;
			पूर्ण

			connection = gb_connection_create(bundle, cport_id,
							  शून्य);
			अगर (IS_ERR(connection)) अणु
				dev_err(&bundle->dev, "failed to create Authentication connection (%ld)\n",
					PTR_ERR(connection));
			पूर्ण अन्यथा अणु
				fw_core->cap_connection = connection;
			पूर्ण

			अवरोध;
		शेष:
			dev_err(&bundle->dev, "invalid protocol id (0x%02x)\n",
				protocol_id);
			ret = -EINVAL;
			जाओ err_destroy_connections;
		पूर्ण
	पूर्ण

	/* Firmware Management connection is mandatory */
	अगर (!fw_core->mgmt_connection) अणु
		dev_err(&bundle->dev, "missing management connection\n");
		ret = -ENODEV;
		जाओ err_destroy_connections;
	पूर्ण

	ret = gb_fw_करोwnload_connection_init(fw_core->करोwnload_connection);
	अगर (ret) अणु
		/* We may still be able to work with the Interface */
		dev_err(&bundle->dev, "failed to initialize firmware download connection, disable it (%d)\n",
			ret);
		gb_connection_destroy(fw_core->करोwnload_connection);
		fw_core->करोwnload_connection = शून्य;
	पूर्ण

	ret = gb_fw_spi_connection_init(fw_core->spi_connection);
	अगर (ret) अणु
		/* We may still be able to work with the Interface */
		dev_err(&bundle->dev, "failed to initialize SPI connection, disable it (%d)\n",
			ret);
		gb_connection_destroy(fw_core->spi_connection);
		fw_core->spi_connection = शून्य;
	पूर्ण

	ret = gb_cap_connection_init(fw_core->cap_connection);
	अगर (ret) अणु
		/* We may still be able to work with the Interface */
		dev_err(&bundle->dev, "failed to initialize CAP connection, disable it (%d)\n",
			ret);
		gb_connection_destroy(fw_core->cap_connection);
		fw_core->cap_connection = शून्य;
	पूर्ण

	ret = gb_fw_mgmt_connection_init(fw_core->mgmt_connection);
	अगर (ret) अणु
		/* We may still be able to work with the Interface */
		dev_err(&bundle->dev, "failed to initialize firmware management connection, disable it (%d)\n",
			ret);
		जाओ err_निकास_connections;
	पूर्ण

	greybus_set_drvdata(bundle, fw_core);

	/* FIXME: Remove this after S2 Loader माला_लो runसमय PM support */
	अगर (!(bundle->पूर्णांकf->quirks & GB_INTERFACE_QUIRK_NO_PM))
		gb_pm_runसमय_put_स्वतःsuspend(bundle);

	वापस 0;

err_निकास_connections:
	gb_cap_connection_निकास(fw_core->cap_connection);
	gb_fw_spi_connection_निकास(fw_core->spi_connection);
	gb_fw_करोwnload_connection_निकास(fw_core->करोwnload_connection);
err_destroy_connections:
	gb_connection_destroy(fw_core->mgmt_connection);
	gb_connection_destroy(fw_core->cap_connection);
	gb_connection_destroy(fw_core->spi_connection);
	gb_connection_destroy(fw_core->करोwnload_connection);
	kमुक्त(fw_core);

	वापस ret;
पूर्ण

अटल व्योम gb_fw_core_disconnect(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_fw_core *fw_core = greybus_get_drvdata(bundle);
	पूर्णांक ret;

	/* FIXME: Remove this after S2 Loader माला_लो runसमय PM support */
	अगर (!(bundle->पूर्णांकf->quirks & GB_INTERFACE_QUIRK_NO_PM)) अणु
		ret = gb_pm_runसमय_get_sync(bundle);
		अगर (ret)
			gb_pm_runसमय_get_noresume(bundle);
	पूर्ण

	gb_fw_mgmt_connection_निकास(fw_core->mgmt_connection);
	gb_cap_connection_निकास(fw_core->cap_connection);
	gb_fw_spi_connection_निकास(fw_core->spi_connection);
	gb_fw_करोwnload_connection_निकास(fw_core->करोwnload_connection);

	gb_connection_destroy(fw_core->mgmt_connection);
	gb_connection_destroy(fw_core->cap_connection);
	gb_connection_destroy(fw_core->spi_connection);
	gb_connection_destroy(fw_core->करोwnload_connection);

	kमुक्त(fw_core);
पूर्ण

अटल स्थिर काष्ठा greybus_bundle_id gb_fw_core_id_table[] = अणु
	अणु GREYBUS_DEVICE_CLASS(GREYBUS_CLASS_FW_MANAGEMENT) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा greybus_driver gb_fw_core_driver = अणु
	.name		= "gb-firmware",
	.probe		= gb_fw_core_probe,
	.disconnect	= gb_fw_core_disconnect,
	.id_table	= gb_fw_core_id_table,
पूर्ण;

अटल पूर्णांक fw_core_init(व्योम)
अणु
	पूर्णांक ret;

	ret = fw_mgmt_init();
	अगर (ret) अणु
		pr_err("Failed to initialize fw-mgmt core (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = cap_init();
	अगर (ret) अणु
		pr_err("Failed to initialize component authentication core (%d)\n",
		       ret);
		जाओ fw_mgmt_निकास;
	पूर्ण

	ret = greybus_रेजिस्टर(&gb_fw_core_driver);
	अगर (ret)
		जाओ cap_निकास;

	वापस 0;

cap_निकास:
	cap_निकास();
fw_mgmt_निकास:
	fw_mgmt_निकास();

	वापस ret;
पूर्ण
module_init(fw_core_init);

अटल व्योम __निकास fw_core_निकास(व्योम)
अणु
	greybus_deरेजिस्टर(&gb_fw_core_driver);
	cap_निकास();
	fw_mgmt_निकास();
पूर्ण
module_निकास(fw_core_निकास);

MODULE_ALIAS("greybus:firmware");
MODULE_AUTHOR("Viresh Kumar <viresh.kumar@linaro.org>");
MODULE_DESCRIPTION("Greybus Firmware Bundle Driver");
MODULE_LICENSE("GPL v2");
