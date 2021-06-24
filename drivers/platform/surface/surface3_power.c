<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Supports क्रम the घातer IC on the Surface 3 tablet.
 *
 * (C) Copyright 2016-2018 Red Hat, Inc
 * (C) Copyright 2016-2018 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 * (C) Copyright 2016 Stephen Just <stephenjust@gmail.com>
 *
 * This driver has been reverse-engineered by parsing the DSDT of the Surface 3
 * and looking at the रेजिस्टरs of the chips.
 *
 * The DSDT allowed to find out that:
 * - the driver is required क्रम the ACPI BAT0 device to communicate to the chip
 *   through an operation region.
 * - the various defines क्रम the operation region functions to communicate with
 *   this driver
 * - the DSM 3f99e367-6220-4955-8b0f-06ef2ae79412 allows to trigger ACPI
 *   events to BAT0 (the code is all available in the DSDT).
 *
 * Further findings regarding the 2 chips declared in the MSHW0011 are:
 * - there are 2 chips declared:
 *   . 0x22 seems to control the ADP1 line status (and probably the अक्षरger)
 *   . 0x55 controls the battery directly
 * - the battery chip uses a SMBus protocol (using plain SMBus allows non
 *   deकाष्ठाive commands):
 *   . the commands/रेजिस्टरs used are in the range 0x00..0x7F
 *   . अगर bit 8 (0x80) is set in the SMBus command, the वापसed value is the
 *     same as when it is not set. There is a high chance this bit is the
 *     पढ़ो/ग_लिखो
 *   . the various रेजिस्टरs semantic as been deduced by observing the रेजिस्टर
 *     dumps.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bits.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uuid.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा SURFACE_3_POLL_INTERVAL		(2 * HZ)
#घोषणा SURFACE_3_STRLEN		10

काष्ठा mshw0011_data अणु
	काष्ठा i2c_client	*adp1;
	काष्ठा i2c_client	*bat0;
	अचिन्हित लघु		notअगरy_mask;
	काष्ठा task_काष्ठा	*poll_task;
	bool			kthपढ़ो_running;

	bool			अक्षरging;
	bool			bat_अक्षरging;
	u8			trip_poपूर्णांक;
	s32			full_capacity;
पूर्ण;

काष्ठा mshw0011_handler_data अणु
	काष्ठा acpi_connection_info	info;
	काष्ठा i2c_client		*client;
पूर्ण;

काष्ठा bix अणु
	u32	revision;
	u32	घातer_unit;
	u32	design_capacity;
	u32	last_full_अक्षरg_capacity;
	u32	battery_technology;
	u32	design_voltage;
	u32	design_capacity_of_warning;
	u32	design_capacity_of_low;
	u32	cycle_count;
	u32	measurement_accuracy;
	u32	max_sampling_समय;
	u32	min_sampling_समय;
	u32	max_average_पूर्णांकerval;
	u32	min_average_पूर्णांकerval;
	u32	battery_capacity_granularity_1;
	u32	battery_capacity_granularity_2;
	अक्षर	model[SURFACE_3_STRLEN];
	अक्षर	serial[SURFACE_3_STRLEN];
	अक्षर	type[SURFACE_3_STRLEN];
	अक्षर	OEM[SURFACE_3_STRLEN];
पूर्ण __packed;

काष्ठा bst अणु
	u32	battery_state;
	s32	battery_present_rate;
	u32	battery_reमुख्यing_capacity;
	u32	battery_present_voltage;
पूर्ण __packed;

काष्ठा gsb_command अणु
	u8	arg0;
	u8	arg1;
	u8	arg2;
पूर्ण __packed;

काष्ठा gsb_buffer अणु
	u8	status;
	u8	len;
	u8	ret;
	जोड़ अणु
		काष्ठा gsb_command	cmd;
		काष्ठा bst		bst;
		काष्ठा bix		bix;
	पूर्ण __packed;
पूर्ण __packed;

#घोषणा ACPI_BATTERY_STATE_DISCHARGING	BIT(0)
#घोषणा ACPI_BATTERY_STATE_CHARGING	BIT(1)
#घोषणा ACPI_BATTERY_STATE_CRITICAL	BIT(2)

#घोषणा MSHW0011_CMD_DEST_BAT0		0x01
#घोषणा MSHW0011_CMD_DEST_ADP1		0x03

#घोषणा MSHW0011_CMD_BAT0_STA		0x01
#घोषणा MSHW0011_CMD_BAT0_BIX		0x02
#घोषणा MSHW0011_CMD_BAT0_BCT		0x03
#घोषणा MSHW0011_CMD_BAT0_BTM		0x04
#घोषणा MSHW0011_CMD_BAT0_BST		0x05
#घोषणा MSHW0011_CMD_BAT0_BTP		0x06
#घोषणा MSHW0011_CMD_ADP1_PSR		0x07
#घोषणा MSHW0011_CMD_BAT0_PSOC		0x09
#घोषणा MSHW0011_CMD_BAT0_PMAX		0x0a
#घोषणा MSHW0011_CMD_BAT0_PSRC		0x0b
#घोषणा MSHW0011_CMD_BAT0_CHGI		0x0c
#घोषणा MSHW0011_CMD_BAT0_ARTG		0x0d

#घोषणा MSHW0011_NOTIFY_GET_VERSION	0x00
#घोषणा MSHW0011_NOTIFY_ADP1		0x01
#घोषणा MSHW0011_NOTIFY_BAT0_BST	0x02
#घोषणा MSHW0011_NOTIFY_BAT0_BIX	0x05

#घोषणा MSHW0011_ADP1_REG_PSR		0x04

#घोषणा MSHW0011_BAT0_REG_CAPACITY		0x0c
#घोषणा MSHW0011_BAT0_REG_FULL_CHG_CAPACITY	0x0e
#घोषणा MSHW0011_BAT0_REG_DESIGN_CAPACITY	0x40
#घोषणा MSHW0011_BAT0_REG_VOLTAGE	0x08
#घोषणा MSHW0011_BAT0_REG_RATE		0x14
#घोषणा MSHW0011_BAT0_REG_OEM		0x45
#घोषणा MSHW0011_BAT0_REG_TYPE		0x4e
#घोषणा MSHW0011_BAT0_REG_SERIAL_NO	0x56
#घोषणा MSHW0011_BAT0_REG_CYCLE_CNT	0x6e

#घोषणा MSHW0011_EV_2_5_MASK		GENMASK(8, 0)

/* 3f99e367-6220-4955-8b0f-06ef2ae79412 */
अटल स्थिर guid_t mshw0011_guid =
	GUID_INIT(0x3F99E367, 0x6220, 0x4955, 0x8B, 0x0F, 0x06, 0xEF,
		  0x2A, 0xE7, 0x94, 0x12);

अटल पूर्णांक
mshw0011_notअगरy(काष्ठा mshw0011_data *cdata, u8 arg1, u8 arg2,
		अचिन्हित पूर्णांक *ret_value)
अणु
	जोड़ acpi_object *obj;
	काष्ठा acpi_device *adev;
	acpi_handle handle;
	अचिन्हित पूर्णांक i;

	handle = ACPI_HANDLE(&cdata->adp1->dev);
	अगर (!handle || acpi_bus_get_device(handle, &adev))
		वापस -ENODEV;

	obj = acpi_evaluate_dsm_typed(handle, &mshw0011_guid, arg1, arg2, शून्य,
				      ACPI_TYPE_BUFFER);
	अगर (!obj) अणु
		dev_err(&cdata->adp1->dev, "device _DSM execution failed\n");
		वापस -ENODEV;
	पूर्ण

	*ret_value = 0;
	क्रम (i = 0; i < obj->buffer.length; i++)
		*ret_value |= obj->buffer.poपूर्णांकer[i] << (i * 8);

	ACPI_FREE(obj);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bix शेष_bix = अणु
	.revision = 0x00,
	.घातer_unit = 0x01,
	.design_capacity = 0x1dca,
	.last_full_अक्षरg_capacity = 0x1dca,
	.battery_technology = 0x01,
	.design_voltage = 0x10df,
	.design_capacity_of_warning = 0x8f,
	.design_capacity_of_low = 0x47,
	.cycle_count = 0xffffffff,
	.measurement_accuracy = 0x00015f90,
	.max_sampling_समय = 0x03e8,
	.min_sampling_समय = 0x03e8,
	.max_average_पूर्णांकerval = 0x03e8,
	.min_average_पूर्णांकerval = 0x03e8,
	.battery_capacity_granularity_1 = 0x45,
	.battery_capacity_granularity_2 = 0x11,
	.model = "P11G8M",
	.serial = "",
	.type = "LION",
	.OEM = "",
पूर्ण;

अटल पूर्णांक mshw0011_bix(काष्ठा mshw0011_data *cdata, काष्ठा bix *bix)
अणु
	काष्ठा i2c_client *client = cdata->bat0;
	अक्षर buf[SURFACE_3_STRLEN];
	पूर्णांक ret;

	*bix = शेष_bix;

	/* get design capacity */
	ret = i2c_smbus_पढ़ो_word_data(client,
				       MSHW0011_BAT0_REG_DESIGN_CAPACITY);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error reading design capacity: %d\n",
			ret);
		वापस ret;
	पूर्ण
	bix->design_capacity = ret;

	/* get last full अक्षरge capacity */
	ret = i2c_smbus_पढ़ो_word_data(client,
				       MSHW0011_BAT0_REG_FULL_CHG_CAPACITY);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"Error reading last full charge capacity: %d\n", ret);
		वापस ret;
	पूर्ण
	bix->last_full_अक्षरg_capacity = ret;

	/* get serial number */
	ret = i2c_smbus_पढ़ो_i2c_block_data(client, MSHW0011_BAT0_REG_SERIAL_NO,
					    माप(buf), buf);
	अगर (ret != माप(buf)) अणु
		dev_err(&client->dev, "Error reading serial no: %d\n", ret);
		वापस ret;
	पूर्ण
	snम_लिखो(bix->serial, ARRAY_SIZE(bix->serial), "%3pE%6pE", buf + 7, buf);

	/* get cycle count */
	ret = i2c_smbus_पढ़ो_word_data(client, MSHW0011_BAT0_REG_CYCLE_CNT);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error reading cycle count: %d\n", ret);
		वापस ret;
	पूर्ण
	bix->cycle_count = ret;

	/* get OEM name */
	ret = i2c_smbus_पढ़ो_i2c_block_data(client, MSHW0011_BAT0_REG_OEM,
					    4, buf);
	अगर (ret != 4) अणु
		dev_err(&client->dev, "Error reading cycle count: %d\n", ret);
		वापस ret;
	पूर्ण
	snम_लिखो(bix->OEM, ARRAY_SIZE(bix->OEM), "%3pE", buf);

	वापस 0;
पूर्ण

अटल पूर्णांक mshw0011_bst(काष्ठा mshw0011_data *cdata, काष्ठा bst *bst)
अणु
	काष्ठा i2c_client *client = cdata->bat0;
	पूर्णांक rate, capacity, voltage, state;
	s16 पंचांगp;

	rate = i2c_smbus_पढ़ो_word_data(client, MSHW0011_BAT0_REG_RATE);
	अगर (rate < 0)
		वापस rate;

	capacity = i2c_smbus_पढ़ो_word_data(client, MSHW0011_BAT0_REG_CAPACITY);
	अगर (capacity < 0)
		वापस capacity;

	voltage = i2c_smbus_पढ़ो_word_data(client, MSHW0011_BAT0_REG_VOLTAGE);
	अगर (voltage < 0)
		वापस voltage;

	पंचांगp = rate;
	bst->battery_present_rate = असल((s32)पंचांगp);

	state = 0;
	अगर ((s32) पंचांगp > 0)
		state |= ACPI_BATTERY_STATE_CHARGING;
	अन्यथा अगर ((s32) पंचांगp < 0)
		state |= ACPI_BATTERY_STATE_DISCHARGING;
	bst->battery_state = state;

	bst->battery_reमुख्यing_capacity = capacity;
	bst->battery_present_voltage = voltage;

	वापस 0;
पूर्ण

अटल पूर्णांक mshw0011_adp_psr(काष्ठा mshw0011_data *cdata)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(cdata->adp1, MSHW0011_ADP1_REG_PSR);
पूर्ण

अटल पूर्णांक mshw0011_isr(काष्ठा mshw0011_data *cdata)
अणु
	काष्ठा bst bst;
	काष्ठा bix bix;
	पूर्णांक ret;
	bool status, bat_status;

	ret = mshw0011_adp_psr(cdata);
	अगर (ret < 0)
		वापस ret;

	status = ret;
	अगर (status != cdata->अक्षरging)
		mshw0011_notअगरy(cdata, cdata->notअगरy_mask,
				MSHW0011_NOTIFY_ADP1, &ret);

	cdata->अक्षरging = status;

	ret = mshw0011_bst(cdata, &bst);
	अगर (ret < 0)
		वापस ret;

	bat_status = bst.battery_state;
	अगर (bat_status != cdata->bat_अक्षरging)
		mshw0011_notअगरy(cdata, cdata->notअगरy_mask,
				MSHW0011_NOTIFY_BAT0_BST, &ret);

	cdata->bat_अक्षरging = bat_status;

	ret = mshw0011_bix(cdata, &bix);
	अगर (ret < 0)
		वापस ret;

	अगर (bix.last_full_अक्षरg_capacity != cdata->full_capacity)
		mshw0011_notअगरy(cdata, cdata->notअगरy_mask,
				MSHW0011_NOTIFY_BAT0_BIX, &ret);

	cdata->full_capacity = bix.last_full_अक्षरg_capacity;

	वापस 0;
पूर्ण

अटल पूर्णांक mshw0011_poll_task(व्योम *data)
अणु
	काष्ठा mshw0011_data *cdata = data;
	पूर्णांक ret = 0;

	cdata->kthपढ़ो_running = true;

	set_मुक्तzable();

	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule_समयout_पूर्णांकerruptible(SURFACE_3_POLL_INTERVAL);
		try_to_मुक्तze();
		ret = mshw0011_isr(data);
		अगर (ret)
			अवरोध;
	पूर्ण

	cdata->kthपढ़ो_running = false;
	वापस ret;
पूर्ण

अटल acpi_status
mshw0011_space_handler(u32 function, acpi_physical_address command,
			u32 bits, u64 *value64,
			व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा gsb_buffer *gsb = (काष्ठा gsb_buffer *)value64;
	काष्ठा mshw0011_handler_data *data = handler_context;
	काष्ठा acpi_connection_info *info = &data->info;
	काष्ठा acpi_resource_i2c_serialbus *sb;
	काष्ठा i2c_client *client = data->client;
	काष्ठा mshw0011_data *cdata = i2c_get_clientdata(client);
	काष्ठा acpi_resource *ares;
	u32 accessor_type = function >> 16;
	acpi_status ret;
	पूर्णांक status = 1;

	ret = acpi_buffer_to_resource(info->connection, info->length, &ares);
	अगर (ACPI_FAILURE(ret))
		वापस ret;

	अगर (!value64 || ares->type != ACPI_RESOURCE_TYPE_SERIAL_BUS) अणु
		ret = AE_BAD_PARAMETER;
		जाओ err;
	पूर्ण

	sb = &ares->data.i2c_serial_bus;
	अगर (sb->type != ACPI_RESOURCE_SERIAL_TYPE_I2C) अणु
		ret = AE_BAD_PARAMETER;
		जाओ err;
	पूर्ण

	अगर (accessor_type != ACPI_GSB_ACCESS_ATTRIB_RAW_PROCESS) अणु
		ret = AE_BAD_PARAMETER;
		जाओ err;
	पूर्ण

	अगर (gsb->cmd.arg0 == MSHW0011_CMD_DEST_ADP1 &&
	    gsb->cmd.arg1 == MSHW0011_CMD_ADP1_PSR) अणु
		status = mshw0011_adp_psr(cdata);
		अगर (status >= 0) अणु
			ret = AE_OK;
			जाओ out;
		पूर्ण अन्यथा अणु
			ret = AE_ERROR;
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (gsb->cmd.arg0 != MSHW0011_CMD_DEST_BAT0) अणु
		ret = AE_BAD_PARAMETER;
		जाओ err;
	पूर्ण

	चयन (gsb->cmd.arg1) अणु
	हाल MSHW0011_CMD_BAT0_STA:
		अवरोध;
	हाल MSHW0011_CMD_BAT0_BIX:
		ret = mshw0011_bix(cdata, &gsb->bix);
		अवरोध;
	हाल MSHW0011_CMD_BAT0_BTP:
		cdata->trip_poपूर्णांक = gsb->cmd.arg2;
		अवरोध;
	हाल MSHW0011_CMD_BAT0_BST:
		ret = mshw0011_bst(cdata, &gsb->bst);
		अवरोध;
	शेष:
		dev_info(&cdata->bat0->dev, "command(0x%02x) is not supported.\n", gsb->cmd.arg1);
		ret = AE_BAD_PARAMETER;
		जाओ err;
	पूर्ण

 out:
	gsb->ret = status;
	gsb->status = 0;

 err:
	ACPI_FREE(ares);
	वापस ret;
पूर्ण

अटल पूर्णांक mshw0011_install_space_handler(काष्ठा i2c_client *client)
अणु
	acpi_handle handle;
	काष्ठा mshw0011_handler_data *data;
	acpi_status status;

	handle = ACPI_HANDLE(&client->dev);
	अगर (!handle)
		वापस -ENODEV;

	data = kzalloc(माप(काष्ठा mshw0011_handler_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	status = acpi_bus_attach_निजी_data(handle, (व्योम *)data);
	अगर (ACPI_FAILURE(status)) अणु
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण

	status = acpi_install_address_space_handler(handle,
				ACPI_ADR_SPACE_GSBUS,
				&mshw0011_space_handler,
				शून्य,
				data);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&client->dev, "Error installing i2c space handler\n");
		acpi_bus_detach_निजी_data(handle);
		kमुक्त(data);
		वापस -ENOMEM;
	पूर्ण

	acpi_walk_dep_device_list(handle);
	वापस 0;
पूर्ण

अटल व्योम mshw0011_हटाओ_space_handler(काष्ठा i2c_client *client)
अणु
	काष्ठा mshw0011_handler_data *data;
	acpi_handle handle;
	acpi_status status;

	handle = ACPI_HANDLE(&client->dev);
	अगर (!handle)
		वापस;

	acpi_हटाओ_address_space_handler(handle,
				ACPI_ADR_SPACE_GSBUS,
				&mshw0011_space_handler);

	status = acpi_bus_get_निजी_data(handle, (व्योम **)&data);
	अगर (ACPI_SUCCESS(status))
		kमुक्त(data);

	acpi_bus_detach_निजी_data(handle);
पूर्ण

अटल पूर्णांक mshw0011_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_board_info board_info;
	काष्ठा device *dev = &client->dev;
	काष्ठा i2c_client *bat0;
	काष्ठा mshw0011_data *data;
	पूर्णांक error, mask;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->adp1 = client;
	i2c_set_clientdata(client, data);

	स_रखो(&board_info, 0, माप(board_info));
	strlcpy(board_info.type, "MSHW0011-bat0", I2C_NAME_SIZE);

	bat0 = i2c_acpi_new_device(dev, 1, &board_info);
	अगर (IS_ERR(bat0))
		वापस PTR_ERR(bat0);

	data->bat0 = bat0;
	i2c_set_clientdata(bat0, data);

	error = mshw0011_notअगरy(data, 1, MSHW0011_NOTIFY_GET_VERSION, &mask);
	अगर (error)
		जाओ out_err;

	data->notअगरy_mask = mask == MSHW0011_EV_2_5_MASK;

	data->poll_task = kthपढ़ो_run(mshw0011_poll_task, data, "mshw0011_adp");
	अगर (IS_ERR(data->poll_task)) अणु
		error = PTR_ERR(data->poll_task);
		dev_err(&client->dev, "Unable to run kthread err %d\n", error);
		जाओ out_err;
	पूर्ण

	error = mshw0011_install_space_handler(client);
	अगर (error)
		जाओ out_err;

	वापस 0;

out_err:
	अगर (data->kthपढ़ो_running)
		kthपढ़ो_stop(data->poll_task);
	i2c_unरेजिस्टर_device(data->bat0);
	वापस error;
पूर्ण

अटल पूर्णांक mshw0011_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mshw0011_data *cdata = i2c_get_clientdata(client);

	mshw0011_हटाओ_space_handler(client);

	अगर (cdata->kthपढ़ो_running)
		kthपढ़ो_stop(cdata->poll_task);

	i2c_unरेजिस्टर_device(cdata->bat0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id mshw0011_acpi_match[] = अणु
	अणु "MSHW0011", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mshw0011_acpi_match);

अटल काष्ठा i2c_driver mshw0011_driver = अणु
	.probe_new = mshw0011_probe,
	.हटाओ = mshw0011_हटाओ,
	.driver = अणु
		.name = "mshw0011",
		.acpi_match_table = mshw0011_acpi_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(mshw0011_driver);

MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_DESCRIPTION("mshw0011 driver");
MODULE_LICENSE("GPL v2");
