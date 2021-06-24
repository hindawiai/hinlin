<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 - 2016 Red Hat, Inc
 * Copyright (c) 2011, 2012 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/rmi.h>
#समावेश <linux/slab.h>
#समावेश "rmi_driver.h"

#घोषणा SMB_PROTOCOL_VERSION_ADDRESS	0xfd
#घोषणा SMB_MAX_COUNT			32
#घोषणा RMI_SMB2_MAP_SIZE		8 /* 8 entry of 4 bytes each */
#घोषणा RMI_SMB2_MAP_FLAGS_WE		0x01

काष्ठा mapping_table_entry अणु
	__le16 rmiaddr;
	u8 पढ़ोcount;
	u8 flags;
पूर्ण;

काष्ठा rmi_smb_xport अणु
	काष्ठा rmi_transport_dev xport;
	काष्ठा i2c_client *client;

	काष्ठा mutex page_mutex;
	पूर्णांक page;
	u8 table_index;
	काष्ठा mutex mappingtable_mutex;
	काष्ठा mapping_table_entry mapping_table[RMI_SMB2_MAP_SIZE];
पूर्ण;

अटल पूर्णांक rmi_smb_get_version(काष्ठा rmi_smb_xport *rmi_smb)
अणु
	काष्ठा i2c_client *client = rmi_smb->client;
	पूर्णांक retval;

	/* Check अगर क्रम SMBus new version device by पढ़ोing version byte. */
	retval = i2c_smbus_पढ़ो_byte_data(client, SMB_PROTOCOL_VERSION_ADDRESS);
	अगर (retval < 0) अणु
		dev_err(&client->dev, "failed to get SMBus version number!\n");
		वापस retval;
	पूर्ण

	वापस retval + 1;
पूर्ण

/* SMB block ग_लिखो - wrapper over ic2_smb_ग_लिखो_block */
अटल पूर्णांक smb_block_ग_लिखो(काष्ठा rmi_transport_dev *xport,
			      u8 commandcode, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_smb_xport *rmi_smb =
		container_of(xport, काष्ठा rmi_smb_xport, xport);
	काष्ठा i2c_client *client = rmi_smb->client;
	पूर्णांक retval;

	retval = i2c_smbus_ग_लिखो_block_data(client, commandcode, len, buf);

	rmi_dbg(RMI_DEBUG_XPORT, &client->dev,
		"wrote %zd bytes at %#04x: %d (%*ph)\n",
		len, commandcode, retval, (पूर्णांक)len, buf);

	वापस retval;
पूर्ण

/*
 * The function to get command code क्रम smbus operations and keeps
 * records to the driver mapping table
 */
अटल पूर्णांक rmi_smb_get_command_code(काष्ठा rmi_transport_dev *xport,
		u16 rmiaddr, पूर्णांक bytecount, bool isपढ़ो, u8 *commandcode)
अणु
	काष्ठा rmi_smb_xport *rmi_smb =
		container_of(xport, काष्ठा rmi_smb_xport, xport);
	काष्ठा mapping_table_entry new_map;
	पूर्णांक i;
	पूर्णांक retval = 0;

	mutex_lock(&rmi_smb->mappingtable_mutex);

	क्रम (i = 0; i < RMI_SMB2_MAP_SIZE; i++) अणु
		काष्ठा mapping_table_entry *entry = &rmi_smb->mapping_table[i];

		अगर (le16_to_cpu(entry->rmiaddr) == rmiaddr) अणु
			अगर (isपढ़ो) अणु
				अगर (entry->पढ़ोcount == bytecount)
					जाओ निकास;
			पूर्ण अन्यथा अणु
				अगर (entry->flags & RMI_SMB2_MAP_FLAGS_WE) अणु
					जाओ निकास;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	i = rmi_smb->table_index;
	rmi_smb->table_index = (i + 1) % RMI_SMB2_MAP_SIZE;

	/* स्थिरructs mapping table data entry. 4 bytes each entry */
	स_रखो(&new_map, 0, माप(new_map));
	new_map.rmiaddr = cpu_to_le16(rmiaddr);
	new_map.पढ़ोcount = bytecount;
	new_map.flags = !isपढ़ो ? RMI_SMB2_MAP_FLAGS_WE : 0;

	retval = smb_block_ग_लिखो(xport, i + 0x80, &new_map, माप(new_map));
	अगर (retval < 0) अणु
		/*
		 * अगर not written to device mapping table
		 * clear the driver mapping table records
		 */
		स_रखो(&new_map, 0, माप(new_map));
	पूर्ण

	/* save to the driver level mapping table */
	rmi_smb->mapping_table[i] = new_map;

निकास:
	mutex_unlock(&rmi_smb->mappingtable_mutex);

	अगर (retval < 0)
		वापस retval;

	*commandcode = i;
	वापस 0;
पूर्ण

अटल पूर्णांक rmi_smb_ग_लिखो_block(काष्ठा rmi_transport_dev *xport, u16 rmiaddr,
				स्थिर व्योम *databuff, माप_प्रकार len)
अणु
	पूर्णांक retval = 0;
	u8 commandcode;
	काष्ठा rmi_smb_xport *rmi_smb =
		container_of(xport, काष्ठा rmi_smb_xport, xport);
	पूर्णांक cur_len = (पूर्णांक)len;

	mutex_lock(&rmi_smb->page_mutex);

	जबतक (cur_len > 0) अणु
		/*
		 * अवरोध पूर्णांकo 32 bytes chunks to ग_लिखो get command code
		 */
		पूर्णांक block_len = min_t(पूर्णांक, len, SMB_MAX_COUNT);

		retval = rmi_smb_get_command_code(xport, rmiaddr, block_len,
						  false, &commandcode);
		अगर (retval < 0)
			जाओ निकास;

		retval = smb_block_ग_लिखो(xport, commandcode,
					 databuff, block_len);
		अगर (retval < 0)
			जाओ निकास;

		/* prepare to ग_लिखो next block of bytes */
		cur_len -= SMB_MAX_COUNT;
		databuff += SMB_MAX_COUNT;
		rmiaddr += SMB_MAX_COUNT;
	पूर्ण
निकास:
	mutex_unlock(&rmi_smb->page_mutex);
	वापस retval;
पूर्ण

/* SMB block पढ़ो - wrapper over ic2_smb_पढ़ो_block */
अटल पूर्णांक smb_block_पढ़ो(काष्ठा rmi_transport_dev *xport,
			     u8 commandcode, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा rmi_smb_xport *rmi_smb =
		container_of(xport, काष्ठा rmi_smb_xport, xport);
	काष्ठा i2c_client *client = rmi_smb->client;
	पूर्णांक retval;

	retval = i2c_smbus_पढ़ो_block_data(client, commandcode, buf);
	अगर (retval < 0)
		वापस retval;

	वापस retval;
पूर्ण

अटल पूर्णांक rmi_smb_पढ़ो_block(काष्ठा rmi_transport_dev *xport, u16 rmiaddr,
			      व्योम *databuff, माप_प्रकार len)
अणु
	काष्ठा rmi_smb_xport *rmi_smb =
		container_of(xport, काष्ठा rmi_smb_xport, xport);
	पूर्णांक retval;
	u8 commandcode;
	पूर्णांक cur_len = (पूर्णांक)len;

	mutex_lock(&rmi_smb->page_mutex);
	स_रखो(databuff, 0, len);

	जबतक (cur_len > 0) अणु
		/* अवरोध पूर्णांकo 32 bytes chunks to ग_लिखो get command code */
		पूर्णांक block_len =  min_t(पूर्णांक, cur_len, SMB_MAX_COUNT);

		retval = rmi_smb_get_command_code(xport, rmiaddr, block_len,
						  true, &commandcode);
		अगर (retval < 0)
			जाओ निकास;

		retval = smb_block_पढ़ो(xport, commandcode,
					databuff, block_len);
		अगर (retval < 0)
			जाओ निकास;

		/* prepare to पढ़ो next block of bytes */
		cur_len -= SMB_MAX_COUNT;
		databuff += SMB_MAX_COUNT;
		rmiaddr += SMB_MAX_COUNT;
	पूर्ण

	retval = 0;

निकास:
	mutex_unlock(&rmi_smb->page_mutex);
	वापस retval;
पूर्ण

अटल व्योम rmi_smb_clear_state(काष्ठा rmi_smb_xport *rmi_smb)
अणु
	/* the mapping table has been flushed, discard the current one */
	mutex_lock(&rmi_smb->mappingtable_mutex);
	स_रखो(rmi_smb->mapping_table, 0, माप(rmi_smb->mapping_table));
	mutex_unlock(&rmi_smb->mappingtable_mutex);
पूर्ण

अटल पूर्णांक rmi_smb_enable_smbus_mode(काष्ठा rmi_smb_xport *rmi_smb)
अणु
	पूर्णांक retval;

	/* we need to get the smbus version to activate the touchpad */
	retval = rmi_smb_get_version(rmi_smb);
	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_smb_reset(काष्ठा rmi_transport_dev *xport, u16 reset_addr)
अणु
	काष्ठा rmi_smb_xport *rmi_smb =
		container_of(xport, काष्ठा rmi_smb_xport, xport);

	rmi_smb_clear_state(rmi_smb);

	/*
	 * we करो not call the actual reset command, it has to be handled in
	 * PS/2 or there will be races between PS/2 and SMBus.
	 * PS/2 should ensure that a psmouse_reset is called beक्रमe
	 * पूर्णांकializing the device and after it has been हटाओd to be in a known
	 * state.
	 */
	वापस rmi_smb_enable_smbus_mode(rmi_smb);
पूर्ण

अटल स्थिर काष्ठा rmi_transport_ops rmi_smb_ops = अणु
	.ग_लिखो_block	= rmi_smb_ग_लिखो_block,
	.पढ़ो_block	= rmi_smb_पढ़ो_block,
	.reset		= rmi_smb_reset,
पूर्ण;

अटल पूर्णांक rmi_smb_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rmi_device_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा rmi_smb_xport *rmi_smb;
	पूर्णांक smbus_version;
	पूर्णांक error;

	अगर (!pdata) अणु
		dev_err(&client->dev, "no platform data, aborting\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BLOCK_DATA |
				     I2C_FUNC_SMBUS_HOST_NOTIFY)) अणु
		dev_err(&client->dev,
			"adapter does not support required functionality\n");
		वापस -ENODEV;
	पूर्ण

	अगर (client->irq <= 0) अणु
		dev_err(&client->dev, "no IRQ provided, giving up\n");
		वापस client->irq ? client->irq : -ENODEV;
	पूर्ण

	rmi_smb = devm_kzalloc(&client->dev, माप(काष्ठा rmi_smb_xport),
				GFP_KERNEL);
	अगर (!rmi_smb)
		वापस -ENOMEM;

	rmi_dbg(RMI_DEBUG_XPORT, &client->dev, "Probing %s\n",
		dev_name(&client->dev));

	rmi_smb->client = client;
	mutex_init(&rmi_smb->page_mutex);
	mutex_init(&rmi_smb->mappingtable_mutex);

	rmi_smb->xport.dev = &client->dev;
	rmi_smb->xport.pdata = *pdata;
	rmi_smb->xport.pdata.irq = client->irq;
	rmi_smb->xport.proto_name = "smb";
	rmi_smb->xport.ops = &rmi_smb_ops;

	smbus_version = rmi_smb_get_version(rmi_smb);
	अगर (smbus_version < 0)
		वापस smbus_version;

	rmi_dbg(RMI_DEBUG_XPORT, &client->dev, "Smbus version is %d",
		smbus_version);

	अगर (smbus_version != 2 && smbus_version != 3) अणु
		dev_err(&client->dev, "Unrecognized SMB version %d\n",
				smbus_version);
		वापस -ENODEV;
	पूर्ण

	i2c_set_clientdata(client, rmi_smb);

	dev_info(&client->dev, "registering SMbus-connected sensor\n");

	error = rmi_रेजिस्टर_transport_device(&rmi_smb->xport);
	अगर (error) अणु
		dev_err(&client->dev, "failed to register sensor: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_smb_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rmi_smb_xport *rmi_smb = i2c_get_clientdata(client);

	rmi_unरेजिस्टर_transport_device(&rmi_smb->xport);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rmi_smb_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rmi_smb_xport *rmi_smb = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = rmi_driver_suspend(rmi_smb->xport.rmi_dev, true);
	अगर (ret)
		dev_warn(dev, "Failed to suspend device: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused rmi_smb_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rmi_smb_xport *rmi_smb = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = rmi_driver_suspend(rmi_smb->xport.rmi_dev, false);
	अगर (ret)
		dev_warn(dev, "Failed to suspend device: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused rmi_smb_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = container_of(dev, काष्ठा i2c_client, dev);
	काष्ठा rmi_smb_xport *rmi_smb = i2c_get_clientdata(client);
	काष्ठा rmi_device *rmi_dev = rmi_smb->xport.rmi_dev;
	पूर्णांक ret;

	rmi_smb_reset(&rmi_smb->xport, 0);

	rmi_reset(rmi_dev);

	ret = rmi_driver_resume(rmi_smb->xport.rmi_dev, true);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rmi_smb_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rmi_smb_xport *rmi_smb = i2c_get_clientdata(client);
	पूर्णांक ret;

	ret = rmi_driver_resume(rmi_smb->xport.rmi_dev, false);
	अगर (ret)
		dev_warn(dev, "Failed to resume device: %d\n", ret);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rmi_smb_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(rmi_smb_suspend, rmi_smb_resume)
	SET_RUNTIME_PM_OPS(rmi_smb_runसमय_suspend, rmi_smb_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rmi_id[] = अणु
	अणु "rmi4_smbus", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rmi_id);

अटल काष्ठा i2c_driver rmi_smb_driver = अणु
	.driver = अणु
		.name	= "rmi4_smbus",
		.pm	= &rmi_smb_pm,
	पूर्ण,
	.id_table	= rmi_id,
	.probe		= rmi_smb_probe,
	.हटाओ		= rmi_smb_हटाओ,
पूर्ण;

module_i2c_driver(rmi_smb_driver);

MODULE_AUTHOR("Andrew Duggan <aduggan@synaptics.com>");
MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@redhat.com>");
MODULE_DESCRIPTION("RMI4 SMBus driver");
MODULE_LICENSE("GPL");
