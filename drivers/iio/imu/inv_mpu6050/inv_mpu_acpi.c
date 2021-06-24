<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * inv_mpu_acpi: ACPI processing क्रम creating client devices
 * Copyright (c) 2015, Intel Corporation.
 */

#अगर_घोषित CONFIG_ACPI

#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश "inv_mpu_iio.h"

क्रमागत inv_mpu_product_name अणु
	INV_MPU_NOT_MATCHED,
	INV_MPU_ASUS_T100TA,
पूर्ण;

अटल क्रमागत inv_mpu_product_name matched_product_name;

अटल पूर्णांक __init asus_t100_matched(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	matched_product_name = INV_MPU_ASUS_T100TA;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id inv_mpu_dev_list[] = अणु
	अणु
	.callback = asus_t100_matched,
	.ident = "Asus Transformer Book T100",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "T100TA"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "1.0"),
		पूर्ण,
	पूर्ण,
	/* Add more matching tables here..*/
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक asus_acpi_get_sensor_info(काष्ठा acpi_device *adev,
				     काष्ठा i2c_client *client,
				     काष्ठा i2c_board_info *info)
अणु
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	पूर्णांक i;
	acpi_status status;
	जोड़ acpi_object *cpm;
	पूर्णांक ret;

	status = acpi_evaluate_object(adev->handle, "CNF0", शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	cpm = buffer.poपूर्णांकer;
	क्रम (i = 0; i < cpm->package.count; ++i) अणु
		जोड़ acpi_object *elem;
		पूर्णांक j;

		elem = &cpm->package.elements[i];
		क्रम (j = 0; j < elem->package.count; ++j) अणु
			जोड़ acpi_object *sub_elem;

			sub_elem = &elem->package.elements[j];
			अगर (sub_elem->type == ACPI_TYPE_STRING)
				strlcpy(info->type, sub_elem->string.poपूर्णांकer,
					माप(info->type));
			अन्यथा अगर (sub_elem->type == ACPI_TYPE_INTEGER) अणु
				अगर (sub_elem->पूर्णांकeger.value != client->addr) अणु
					info->addr = sub_elem->पूर्णांकeger.value;
					अवरोध; /* Not a MPU6500 primary */
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	ret = cpm->package.count;
	kमुक्त(buffer.poपूर्णांकer);

	वापस ret;
पूर्ण

अटल पूर्णांक acpi_i2c_check_resource(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा acpi_resource_i2c_serialbus *sb;
	u32 *addr = data;

	अगर (i2c_acpi_get_i2c_resource(ares, &sb)) अणु
		अगर (*addr)
			*addr |= (sb->slave_address << 16);
		अन्यथा
			*addr = sb->slave_address;
	पूर्ण

	/* Tell the ACPI core that we alपढ़ोy copied this address */
	वापस 1;
पूर्ण

अटल पूर्णांक inv_mpu_process_acpi_config(काष्ठा i2c_client *client,
				       अचिन्हित लघु *primary_addr,
				       अचिन्हित लघु *secondary_addr)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&client->dev);
	स्थिर काष्ठा acpi_device_id *id;
	u32 i2c_addr = 0;
	LIST_HEAD(resources);
	पूर्णांक ret;

	id = acpi_match_device(client->dev.driver->acpi_match_table,
			       &client->dev);
	अगर (!id)
		वापस -ENODEV;

	ret = acpi_dev_get_resources(adev, &resources,
				     acpi_i2c_check_resource, &i2c_addr);
	अगर (ret < 0)
		वापस ret;

	acpi_dev_मुक्त_resource_list(&resources);
	*primary_addr = i2c_addr & 0x0000ffff;
	*secondary_addr = (i2c_addr & 0xffff0000) >> 16;

	वापस 0;
पूर्ण

पूर्णांक inv_mpu_acpi_create_mux_client(काष्ठा i2c_client *client)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(dev_get_drvdata(&client->dev));

	st->mux_client = शून्य;
	अगर (ACPI_HANDLE(&client->dev)) अणु
		काष्ठा i2c_board_info info;
		काष्ठा i2c_client *mux_client;
		काष्ठा acpi_device *adev;
		पूर्णांक ret = -1;

		adev = ACPI_COMPANION(&client->dev);
		स_रखो(&info, 0, माप(info));

		dmi_check_प्रणाली(inv_mpu_dev_list);
		चयन (matched_product_name) अणु
		हाल INV_MPU_ASUS_T100TA:
			ret = asus_acpi_get_sensor_info(adev, client,
							&info);
			अवरोध;
		/* Add more matched product processing here */
		शेष:
			अवरोध;
		पूर्ण

		अगर (ret < 0) अणु
			/* No matching DMI, so create device on INV6XX type */
			अचिन्हित लघु primary, secondary;

			ret = inv_mpu_process_acpi_config(client, &primary,
							  &secondary);
			अगर (!ret && secondary) अणु
				अक्षर *name;

				info.addr = secondary;
				strlcpy(info.type, dev_name(&adev->dev),
					माप(info.type));
				name = म_अक्षर(info.type, ':');
				अगर (name)
					*name = '\0';
				strlcat(info.type, "-client",
					माप(info.type));
			पूर्ण अन्यथा
				वापस 0; /* no secondary addr, which is OK */
		पूर्ण
		mux_client = i2c_new_client_device(st->muxc->adapter[0], &info);
		अगर (IS_ERR(mux_client))
			वापस PTR_ERR(mux_client);
		st->mux_client = mux_client;
	पूर्ण

	वापस 0;
पूर्ण

व्योम inv_mpu_acpi_delete_mux_client(काष्ठा i2c_client *client)
अणु
	काष्ठा inv_mpu6050_state *st = iio_priv(dev_get_drvdata(&client->dev));

	i2c_unरेजिस्टर_device(st->mux_client);
पूर्ण
#अन्यथा

#समावेश "inv_mpu_iio.h"

पूर्णांक inv_mpu_acpi_create_mux_client(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

व्योम inv_mpu_acpi_delete_mux_client(काष्ठा i2c_client *client)
अणु
पूर्ण
#पूर्ण_अगर
