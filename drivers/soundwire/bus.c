<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
// Copyright(c) 2015-17 Intel Corporation.

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश "bus.h"
#समावेश "sysfs_local.h"

अटल DEFINE_IDA(sdw_ida);

अटल पूर्णांक sdw_get_id(काष्ठा sdw_bus *bus)
अणु
	पूर्णांक rc = ida_alloc(&sdw_ida, GFP_KERNEL);

	अगर (rc < 0)
		वापस rc;

	bus->id = rc;
	वापस 0;
पूर्ण

/**
 * sdw_bus_master_add() - add a bus Master instance
 * @bus: bus instance
 * @parent: parent device
 * @fwnode: firmware node handle
 *
 * Initializes the bus instance, पढ़ो properties and create child
 * devices.
 */
पूर्णांक sdw_bus_master_add(काष्ठा sdw_bus *bus, काष्ठा device *parent,
		       काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा sdw_master_prop *prop = शून्य;
	पूर्णांक ret;

	अगर (!parent) अणु
		pr_err("SoundWire parent device is not set\n");
		वापस -ENODEV;
	पूर्ण

	ret = sdw_get_id(bus);
	अगर (ret < 0) अणु
		dev_err(parent, "Failed to get bus id\n");
		वापस ret;
	पूर्ण

	ret = sdw_master_device_add(bus, parent, fwnode);
	अगर (ret < 0) अणु
		dev_err(parent, "Failed to add master device at link %d\n",
			bus->link_id);
		वापस ret;
	पूर्ण

	अगर (!bus->ops) अणु
		dev_err(bus->dev, "SoundWire Bus ops are not set\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!bus->compute_params) अणु
		dev_err(bus->dev,
			"Bandwidth allocation not configured, compute_params no set\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&bus->msg_lock);
	mutex_init(&bus->bus_lock);
	INIT_LIST_HEAD(&bus->slaves);
	INIT_LIST_HEAD(&bus->m_rt_list);

	/*
	 * Initialize multi_link flag
	 * TODO: populate this flag by पढ़ोing property from FW node
	 */
	bus->multi_link = false;
	अगर (bus->ops->पढ़ो_prop) अणु
		ret = bus->ops->पढ़ो_prop(bus);
		अगर (ret < 0) अणु
			dev_err(bus->dev,
				"Bus read properties failed:%d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	sdw_bus_debugfs_init(bus);

	/*
	 * Device numbers in SoundWire are 0 through 15. Enumeration device
	 * number (0), Broadcast device number (15), Group numbers (12 and
	 * 13) and Master device number (14) are not used क्रम assignment so
	 * mask these and other higher bits.
	 */

	/* Set higher order bits */
	*bus->asचिन्हित = ~GENMASK(SDW_BROADCAST_DEV_NUM, SDW_ENUM_DEV_NUM);

	/* Set क्रमागतuration device number and broadcast device number */
	set_bit(SDW_ENUM_DEV_NUM, bus->asचिन्हित);
	set_bit(SDW_BROADCAST_DEV_NUM, bus->asचिन्हित);

	/* Set group device numbers and master device number */
	set_bit(SDW_GROUP12_DEV_NUM, bus->asचिन्हित);
	set_bit(SDW_GROUP13_DEV_NUM, bus->asचिन्हित);
	set_bit(SDW_MASTER_DEV_NUM, bus->asचिन्हित);

	/*
	 * SDW is an क्रमागतerable bus, but devices can be घातered off. So,
	 * they won't be able to report as present.
	 *
	 * Create Slave devices based on Slaves described in
	 * the respective firmware (ACPI/DT)
	 */
	अगर (IS_ENABLED(CONFIG_ACPI) && ACPI_HANDLE(bus->dev))
		ret = sdw_acpi_find_slaves(bus);
	अन्यथा अगर (IS_ENABLED(CONFIG_OF) && bus->dev->of_node)
		ret = sdw_of_find_slaves(bus);
	अन्यथा
		ret = -ENOTSUPP; /* No ACPI/DT so error out */

	अगर (ret < 0) अणु
		dev_err(bus->dev, "Finding slaves failed:%d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Initialize घड़ी values based on Master properties. The max
	 * frequency is पढ़ो from max_clk_freq property. Current assumption
	 * is that the bus will start at highest घड़ी frequency when
	 * घातered on.
	 *
	 * Default active bank will be 0 as out of reset the Slaves have
	 * to start with bank 0 (Table 40 of Spec)
	 */
	prop = &bus->prop;
	bus->params.max_dr_freq = prop->max_clk_freq * SDW_DOUBLE_RATE_FACTOR;
	bus->params.curr_dr_freq = bus->params.max_dr_freq;
	bus->params.curr_bank = SDW_BANK0;
	bus->params.next_bank = SDW_BANK1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_bus_master_add);

अटल पूर्णांक sdw_delete_slave(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा sdw_slave *slave = dev_to_sdw_dev(dev);
	काष्ठा sdw_bus *bus = slave->bus;

	pm_runसमय_disable(dev);

	sdw_slave_debugfs_निकास(slave);

	mutex_lock(&bus->bus_lock);

	अगर (slave->dev_num) /* clear dev_num अगर asचिन्हित */
		clear_bit(slave->dev_num, bus->asचिन्हित);

	list_del_init(&slave->node);
	mutex_unlock(&bus->bus_lock);

	device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

/**
 * sdw_bus_master_delete() - delete the bus master instance
 * @bus: bus to be deleted
 *
 * Remove the instance, delete the child devices.
 */
व्योम sdw_bus_master_delete(काष्ठा sdw_bus *bus)
अणु
	device_क्रम_each_child(bus->dev, शून्य, sdw_delete_slave);
	sdw_master_device_del(bus);

	sdw_bus_debugfs_निकास(bus);
	ida_मुक्त(&sdw_ida, bus->id);
पूर्ण
EXPORT_SYMBOL(sdw_bus_master_delete);

/*
 * SDW IO Calls
 */

अटल अंतरभूत पूर्णांक find_response_code(क्रमागत sdw_command_response resp)
अणु
	चयन (resp) अणु
	हाल SDW_CMD_OK:
		वापस 0;

	हाल SDW_CMD_IGNORED:
		वापस -ENODATA;

	हाल SDW_CMD_TIMEOUT:
		वापस -ETIMEDOUT;

	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक करो_transfer(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg)
अणु
	पूर्णांक retry = bus->prop.err_threshold;
	क्रमागत sdw_command_response resp;
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i <= retry; i++) अणु
		resp = bus->ops->xfer_msg(bus, msg);
		ret = find_response_code(resp);

		/* अगर cmd is ok or ignored वापस */
		अगर (ret == 0 || ret == -ENODATA)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक करो_transfer_defer(काष्ठा sdw_bus *bus,
				    काष्ठा sdw_msg *msg,
				    काष्ठा sdw_defer *defer)
अणु
	पूर्णांक retry = bus->prop.err_threshold;
	क्रमागत sdw_command_response resp;
	पूर्णांक ret = 0, i;

	defer->msg = msg;
	defer->length = msg->len;
	init_completion(&defer->complete);

	क्रम (i = 0; i <= retry; i++) अणु
		resp = bus->ops->xfer_msg_defer(bus, msg, defer);
		ret = find_response_code(resp);
		/* अगर cmd is ok or ignored वापस */
		अगर (ret == 0 || ret == -ENODATA)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_reset_page(काष्ठा sdw_bus *bus, u16 dev_num)
अणु
	पूर्णांक retry = bus->prop.err_threshold;
	क्रमागत sdw_command_response resp;
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i <= retry; i++) अणु
		resp = bus->ops->reset_page_addr(bus, dev_num);
		ret = find_response_code(resp);
		/* अगर cmd is ok or ignored वापस */
		अगर (ret == 0 || ret == -ENODATA)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_transfer_unlocked(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg)
अणु
	पूर्णांक ret;

	ret = करो_transfer(bus, msg);
	अगर (ret != 0 && ret != -ENODATA)
		dev_err(bus->dev, "trf on Slave %d failed:%d %s addr %x count %d\n",
			msg->dev_num, ret,
			(msg->flags & SDW_MSG_FLAG_WRITE) ? "write" : "read",
			msg->addr, msg->len);

	अगर (msg->page)
		sdw_reset_page(bus, msg->dev_num);

	वापस ret;
पूर्ण

/**
 * sdw_transfer() - Synchronous transfer message to a SDW Slave device
 * @bus: SDW bus
 * @msg: SDW message to be xfered
 */
पूर्णांक sdw_transfer(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg)
अणु
	पूर्णांक ret;

	mutex_lock(&bus->msg_lock);

	ret = sdw_transfer_unlocked(bus, msg);

	mutex_unlock(&bus->msg_lock);

	वापस ret;
पूर्ण

/**
 * sdw_transfer_defer() - Asynchronously transfer message to a SDW Slave device
 * @bus: SDW bus
 * @msg: SDW message to be xfered
 * @defer: Defer block क्रम संकेत completion
 *
 * Caller needs to hold the msg_lock lock जबतक calling this
 */
पूर्णांक sdw_transfer_defer(काष्ठा sdw_bus *bus, काष्ठा sdw_msg *msg,
		       काष्ठा sdw_defer *defer)
अणु
	पूर्णांक ret;

	अगर (!bus->ops->xfer_msg_defer)
		वापस -ENOTSUPP;

	ret = करो_transfer_defer(bus, msg, defer);
	अगर (ret != 0 && ret != -ENODATA)
		dev_err(bus->dev, "Defer trf on Slave %d failed:%d\n",
			msg->dev_num, ret);

	अगर (msg->page)
		sdw_reset_page(bus, msg->dev_num);

	वापस ret;
पूर्ण

पूर्णांक sdw_fill_msg(काष्ठा sdw_msg *msg, काष्ठा sdw_slave *slave,
		 u32 addr, माप_प्रकार count, u16 dev_num, u8 flags, u8 *buf)
अणु
	स_रखो(msg, 0, माप(*msg));
	msg->addr = addr; /* addr is 16 bit and truncated here */
	msg->len = count;
	msg->dev_num = dev_num;
	msg->flags = flags;
	msg->buf = buf;

	अगर (addr < SDW_REG_NO_PAGE) /* no paging area */
		वापस 0;

	अगर (addr >= SDW_REG_MAX) अणु /* illegal addr */
		pr_err("SDW: Invalid address %x passed\n", addr);
		वापस -EINVAL;
	पूर्ण

	अगर (addr < SDW_REG_OPTIONAL_PAGE) अणु /* 32k but no page */
		अगर (slave && !slave->prop.paging_support)
			वापस 0;
		/* no need क्रम अन्यथा as that will fall-through to paging */
	पूर्ण

	/* paging mandatory */
	अगर (dev_num == SDW_ENUM_DEV_NUM || dev_num == SDW_BROADCAST_DEV_NUM) अणु
		pr_err("SDW: Invalid device for paging :%d\n", dev_num);
		वापस -EINVAL;
	पूर्ण

	अगर (!slave) अणु
		pr_err("SDW: No slave for paging addr\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!slave->prop.paging_support) अणु
		dev_err(&slave->dev,
			"address %x needs paging but no support\n", addr);
		वापस -EINVAL;
	पूर्ण

	msg->addr_page1 = FIELD_GET(SDW_SCP_ADDRPAGE1_MASK, addr);
	msg->addr_page2 = FIELD_GET(SDW_SCP_ADDRPAGE2_MASK, addr);
	msg->addr |= BIT(15);
	msg->page = true;

	वापस 0;
पूर्ण

/*
 * Read/Write IO functions.
 * no_pm versions can only be called by the bus, e.g. जबतक क्रमागतerating or
 * handling suspend-resume sequences.
 * all clients need to use the pm versions
 */

अटल पूर्णांक
sdw_nपढ़ो_no_pm(काष्ठा sdw_slave *slave, u32 addr, माप_प्रकार count, u8 *val)
अणु
	काष्ठा sdw_msg msg;
	पूर्णांक ret;

	ret = sdw_fill_msg(&msg, slave, addr, count,
			   slave->dev_num, SDW_MSG_FLAG_READ, val);
	अगर (ret < 0)
		वापस ret;

	वापस sdw_transfer(slave->bus, &msg);
पूर्ण

अटल पूर्णांक
sdw_nग_लिखो_no_pm(काष्ठा sdw_slave *slave, u32 addr, माप_प्रकार count, u8 *val)
अणु
	काष्ठा sdw_msg msg;
	पूर्णांक ret;

	ret = sdw_fill_msg(&msg, slave, addr, count,
			   slave->dev_num, SDW_MSG_FLAG_WRITE, val);
	अगर (ret < 0)
		वापस ret;

	वापस sdw_transfer(slave->bus, &msg);
पूर्ण

पूर्णांक sdw_ग_लिखो_no_pm(काष्ठा sdw_slave *slave, u32 addr, u8 value)
अणु
	वापस sdw_nग_लिखो_no_pm(slave, addr, 1, &value);
पूर्ण
EXPORT_SYMBOL(sdw_ग_लिखो_no_pm);

अटल पूर्णांक
sdw_bपढ़ो_no_pm(काष्ठा sdw_bus *bus, u16 dev_num, u32 addr)
अणु
	काष्ठा sdw_msg msg;
	u8 buf;
	पूर्णांक ret;

	ret = sdw_fill_msg(&msg, शून्य, addr, 1, dev_num,
			   SDW_MSG_FLAG_READ, &buf);
	अगर (ret < 0)
		वापस ret;

	ret = sdw_transfer(bus, &msg);
	अगर (ret < 0)
		वापस ret;

	वापस buf;
पूर्ण

अटल पूर्णांक
sdw_bग_लिखो_no_pm(काष्ठा sdw_bus *bus, u16 dev_num, u32 addr, u8 value)
अणु
	काष्ठा sdw_msg msg;
	पूर्णांक ret;

	ret = sdw_fill_msg(&msg, शून्य, addr, 1, dev_num,
			   SDW_MSG_FLAG_WRITE, &value);
	अगर (ret < 0)
		वापस ret;

	वापस sdw_transfer(bus, &msg);
पूर्ण

पूर्णांक sdw_bपढ़ो_no_pm_unlocked(काष्ठा sdw_bus *bus, u16 dev_num, u32 addr)
अणु
	काष्ठा sdw_msg msg;
	u8 buf;
	पूर्णांक ret;

	ret = sdw_fill_msg(&msg, शून्य, addr, 1, dev_num,
			   SDW_MSG_FLAG_READ, &buf);
	अगर (ret < 0)
		वापस ret;

	ret = sdw_transfer_unlocked(bus, &msg);
	अगर (ret < 0)
		वापस ret;

	वापस buf;
पूर्ण
EXPORT_SYMBOL(sdw_bपढ़ो_no_pm_unlocked);

पूर्णांक sdw_bग_लिखो_no_pm_unlocked(काष्ठा sdw_bus *bus, u16 dev_num, u32 addr, u8 value)
अणु
	काष्ठा sdw_msg msg;
	पूर्णांक ret;

	ret = sdw_fill_msg(&msg, शून्य, addr, 1, dev_num,
			   SDW_MSG_FLAG_WRITE, &value);
	अगर (ret < 0)
		वापस ret;

	वापस sdw_transfer_unlocked(bus, &msg);
पूर्ण
EXPORT_SYMBOL(sdw_bग_लिखो_no_pm_unlocked);

पूर्णांक sdw_पढ़ो_no_pm(काष्ठा sdw_slave *slave, u32 addr)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = sdw_nपढ़ो_no_pm(slave, addr, 1, &buf);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस buf;
पूर्ण
EXPORT_SYMBOL(sdw_पढ़ो_no_pm);

अटल पूर्णांक sdw_update_no_pm(काष्ठा sdw_slave *slave, u32 addr, u8 mask, u8 val)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = sdw_पढ़ो_no_pm(slave, addr);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	पंचांगp = (पंचांगp & ~mask) | val;
	वापस sdw_ग_लिखो_no_pm(slave, addr, पंचांगp);
पूर्ण

/**
 * sdw_nपढ़ो() - Read "n" contiguous SDW Slave रेजिस्टरs
 * @slave: SDW Slave
 * @addr: Register address
 * @count: length
 * @val: Buffer क्रम values to be पढ़ो
 */
पूर्णांक sdw_nपढ़ो(काष्ठा sdw_slave *slave, u32 addr, माप_प्रकार count, u8 *val)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&slave->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_noidle(&slave->dev);
		वापस ret;
	पूर्ण

	ret = sdw_nपढ़ो_no_pm(slave, addr, count, val);

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put(&slave->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_nपढ़ो);

/**
 * sdw_nग_लिखो() - Write "n" contiguous SDW Slave रेजिस्टरs
 * @slave: SDW Slave
 * @addr: Register address
 * @count: length
 * @val: Buffer क्रम values to be पढ़ो
 */
पूर्णांक sdw_nग_लिखो(काष्ठा sdw_slave *slave, u32 addr, माप_प्रकार count, u8 *val)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&slave->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		pm_runसमय_put_noidle(&slave->dev);
		वापस ret;
	पूर्ण

	ret = sdw_nग_लिखो_no_pm(slave, addr, count, val);

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put(&slave->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_nग_लिखो);

/**
 * sdw_पढ़ो() - Read a SDW Slave रेजिस्टर
 * @slave: SDW Slave
 * @addr: Register address
 */
पूर्णांक sdw_पढ़ो(काष्ठा sdw_slave *slave, u32 addr)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = sdw_nपढ़ो(slave, addr, 1, &buf);
	अगर (ret < 0)
		वापस ret;

	वापस buf;
पूर्ण
EXPORT_SYMBOL(sdw_पढ़ो);

/**
 * sdw_ग_लिखो() - Write a SDW Slave रेजिस्टर
 * @slave: SDW Slave
 * @addr: Register address
 * @value: Register value
 */
पूर्णांक sdw_ग_लिखो(काष्ठा sdw_slave *slave, u32 addr, u8 value)
अणु
	वापस sdw_nग_लिखो(slave, addr, 1, &value);
पूर्ण
EXPORT_SYMBOL(sdw_ग_लिखो);

/*
 * SDW alert handling
 */

/* called with bus_lock held */
अटल काष्ठा sdw_slave *sdw_get_slave(काष्ठा sdw_bus *bus, पूर्णांक i)
अणु
	काष्ठा sdw_slave *slave;

	list_क्रम_each_entry(slave, &bus->slaves, node) अणु
		अगर (slave->dev_num == i)
			वापस slave;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक sdw_compare_devid(काष्ठा sdw_slave *slave, काष्ठा sdw_slave_id id)
अणु
	अगर (slave->id.mfg_id != id.mfg_id ||
	    slave->id.part_id != id.part_id ||
	    slave->id.class_id != id.class_id ||
	    (slave->id.unique_id != SDW_IGNORED_UNIQUE_ID &&
	     slave->id.unique_id != id.unique_id))
		वापस -ENODEV;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_compare_devid);

/* called with bus_lock held */
अटल पूर्णांक sdw_get_device_num(काष्ठा sdw_slave *slave)
अणु
	पूर्णांक bit;

	bit = find_first_zero_bit(slave->bus->asचिन्हित, SDW_MAX_DEVICES);
	अगर (bit == SDW_MAX_DEVICES) अणु
		bit = -ENODEV;
		जाओ err;
	पूर्ण

	/*
	 * Do not update dev_num in Slave data काष्ठाure here,
	 * Update once program dev_num is successful
	 */
	set_bit(bit, slave->bus->asचिन्हित);

err:
	वापस bit;
पूर्ण

अटल पूर्णांक sdw_assign_device_num(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_bus *bus = slave->bus;
	पूर्णांक ret, dev_num;
	bool new_device = false;

	/* check first अगर device number is asचिन्हित, अगर so reuse that */
	अगर (!slave->dev_num) अणु
		अगर (!slave->dev_num_sticky) अणु
			mutex_lock(&slave->bus->bus_lock);
			dev_num = sdw_get_device_num(slave);
			mutex_unlock(&slave->bus->bus_lock);
			अगर (dev_num < 0) अणु
				dev_err(bus->dev, "Get dev_num failed: %d\n",
					dev_num);
				वापस dev_num;
			पूर्ण
			slave->dev_num = dev_num;
			slave->dev_num_sticky = dev_num;
			new_device = true;
		पूर्ण अन्यथा अणु
			slave->dev_num = slave->dev_num_sticky;
		पूर्ण
	पूर्ण

	अगर (!new_device)
		dev_dbg(bus->dev,
			"Slave already registered, reusing dev_num:%d\n",
			slave->dev_num);

	/* Clear the slave->dev_num to transfer message on device 0 */
	dev_num = slave->dev_num;
	slave->dev_num = 0;

	ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_DEVNUMBER, dev_num);
	अगर (ret < 0) अणु
		dev_err(bus->dev, "Program device_num %d failed: %d\n",
			dev_num, ret);
		वापस ret;
	पूर्ण

	/* After xfer of msg, restore dev_num */
	slave->dev_num = slave->dev_num_sticky;

	वापस 0;
पूर्ण

व्योम sdw_extract_slave_id(काष्ठा sdw_bus *bus,
			  u64 addr, काष्ठा sdw_slave_id *id)
अणु
	dev_dbg(bus->dev, "SDW Slave Addr: %llx\n", addr);

	id->sdw_version = SDW_VERSION(addr);
	id->unique_id = SDW_UNIQUE_ID(addr);
	id->mfg_id = SDW_MFG_ID(addr);
	id->part_id = SDW_PART_ID(addr);
	id->class_id = SDW_CLASS_ID(addr);

	dev_dbg(bus->dev,
		"SDW Slave class_id 0x%02x, mfg_id 0x%04x, part_id 0x%04x, unique_id 0x%x, version 0x%x\n",
		id->class_id, id->mfg_id, id->part_id, id->unique_id, id->sdw_version);
पूर्ण
EXPORT_SYMBOL(sdw_extract_slave_id);

अटल पूर्णांक sdw_program_device_num(काष्ठा sdw_bus *bus)
अणु
	u8 buf[SDW_NUM_DEV_ID_REGISTERS] = अणु0पूर्ण;
	काष्ठा sdw_slave *slave, *_s;
	काष्ठा sdw_slave_id id;
	काष्ठा sdw_msg msg;
	bool found;
	पूर्णांक count = 0, ret;
	u64 addr;

	/* No Slave, so use raw xfer api */
	ret = sdw_fill_msg(&msg, शून्य, SDW_SCP_DEVID_0,
			   SDW_NUM_DEV_ID_REGISTERS, 0, SDW_MSG_FLAG_READ, buf);
	अगर (ret < 0)
		वापस ret;

	करो अणु
		ret = sdw_transfer(bus, &msg);
		अगर (ret == -ENODATA) अणु /* end of device id पढ़ोs */
			dev_dbg(bus->dev, "No more devices to enumerate\n");
			ret = 0;
			अवरोध;
		पूर्ण
		अगर (ret < 0) अणु
			dev_err(bus->dev, "DEVID read fail:%d\n", ret);
			अवरोध;
		पूर्ण

		/*
		 * Conकाष्ठा the addr and extract. Cast the higher shअगरt
		 * bits to aव्योम truncation due to size limit.
		 */
		addr = buf[5] | (buf[4] << 8) | (buf[3] << 16) |
			((u64)buf[2] << 24) | ((u64)buf[1] << 32) |
			((u64)buf[0] << 40);

		sdw_extract_slave_id(bus, addr, &id);

		found = false;
		/* Now compare with entries */
		list_क्रम_each_entry_safe(slave, _s, &bus->slaves, node) अणु
			अगर (sdw_compare_devid(slave, id) == 0) अणु
				found = true;

				/*
				 * Assign a new dev_num to this Slave and
				 * not mark it present. It will be marked
				 * present after it reports ATTACHED on new
				 * dev_num
				 */
				ret = sdw_assign_device_num(slave);
				अगर (ret < 0) अणु
					dev_err(bus->dev,
						"Assign dev_num failed:%d\n",
						ret);
					वापस ret;
				पूर्ण

				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			/* TODO: Park this device in Group 13 */

			/*
			 * add Slave device even अगर there is no platक्रमm
			 * firmware description. There will be no driver probe
			 * but the user/पूर्णांकegration will be able to see the
			 * device, क्रमागतeration status and device number in sysfs
			 */
			sdw_slave_add(bus, &id, शून्य);

			dev_err(bus->dev, "Slave Entry not found\n");
		पूर्ण

		count++;

		/*
		 * Check till error out or retry (count) exhausts.
		 * Device can drop off and rejoin during क्रमागतeration
		 * so count till twice the bound.
		 */

	पूर्ण जबतक (ret == 0 && count < (SDW_MAX_DEVICES * 2));

	वापस ret;
पूर्ण

अटल व्योम sdw_modअगरy_slave_status(काष्ठा sdw_slave *slave,
				    क्रमागत sdw_slave_status status)
अणु
	काष्ठा sdw_bus *bus = slave->bus;

	mutex_lock(&bus->bus_lock);

	dev_vdbg(bus->dev,
		 "%s: changing status slave %d status %d new status %d\n",
		 __func__, slave->dev_num, slave->status, status);

	अगर (status == SDW_SLAVE_UNATTACHED) अणु
		dev_dbg(&slave->dev,
			"%s: initializing enumeration and init completion for Slave %d\n",
			__func__, slave->dev_num);

		init_completion(&slave->क्रमागतeration_complete);
		init_completion(&slave->initialization_complete);

	पूर्ण अन्यथा अगर ((status == SDW_SLAVE_ATTACHED) &&
		   (slave->status == SDW_SLAVE_UNATTACHED)) अणु
		dev_dbg(&slave->dev,
			"%s: signaling enumeration completion for Slave %d\n",
			__func__, slave->dev_num);

		complete(&slave->क्रमागतeration_complete);
	पूर्ण
	slave->status = status;
	mutex_unlock(&bus->bus_lock);
पूर्ण

अटल क्रमागत sdw_clk_stop_mode sdw_get_clk_stop_mode(काष्ठा sdw_slave *slave)
अणु
	क्रमागत sdw_clk_stop_mode mode;

	/*
	 * Query क्रम घड़ी stop mode अगर Slave implements
	 * ops->get_clk_stop_mode, अन्यथा पढ़ो from property.
	 */
	अगर (slave->ops && slave->ops->get_clk_stop_mode) अणु
		mode = slave->ops->get_clk_stop_mode(slave);
	पूर्ण अन्यथा अणु
		अगर (slave->prop.clk_stop_mode1)
			mode = SDW_CLK_STOP_MODE1;
		अन्यथा
			mode = SDW_CLK_STOP_MODE0;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक sdw_slave_clk_stop_callback(काष्ठा sdw_slave *slave,
				       क्रमागत sdw_clk_stop_mode mode,
				       क्रमागत sdw_clk_stop_type type)
अणु
	पूर्णांक ret;

	अगर (slave->ops && slave->ops->clk_stop) अणु
		ret = slave->ops->clk_stop(slave, mode, type);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"Clk Stop type =%d failed: %d\n", type, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdw_slave_clk_stop_prepare(काष्ठा sdw_slave *slave,
				      क्रमागत sdw_clk_stop_mode mode,
				      bool prepare)
अणु
	bool wake_en;
	u32 val = 0;
	पूर्णांक ret;

	wake_en = slave->prop.wake_capable;

	अगर (prepare) अणु
		val = SDW_SCP_SYSTEMCTRL_CLK_STP_PREP;

		अगर (mode == SDW_CLK_STOP_MODE1)
			val |= SDW_SCP_SYSTEMCTRL_CLK_STP_MODE1;

		अगर (wake_en)
			val |= SDW_SCP_SYSTEMCTRL_WAKE_UP_EN;
	पूर्ण अन्यथा अणु
		ret = sdw_पढ़ो_no_pm(slave, SDW_SCP_SYSTEMCTRL);
		अगर (ret < 0) अणु
			dev_err(&slave->dev, "SDW_SCP_SYSTEMCTRL read failed:%d\n", ret);
			वापस ret;
		पूर्ण
		val = ret;
		val &= ~(SDW_SCP_SYSTEMCTRL_CLK_STP_PREP);
	पूर्ण

	ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_SYSTEMCTRL, val);

	अगर (ret < 0)
		dev_err(&slave->dev,
			"Clock Stop prepare failed for slave: %d", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_bus_रुको_क्रम_clk_prep_deprep(काष्ठा sdw_bus *bus, u16 dev_num)
अणु
	पूर्णांक retry = bus->clk_stop_समयout;
	पूर्णांक val;

	करो अणु
		val = sdw_bपढ़ो_no_pm(bus, dev_num, SDW_SCP_STAT);
		अगर (val < 0) अणु
			dev_err(bus->dev, "SDW_SCP_STAT bread failed:%d\n", val);
			वापस val;
		पूर्ण
		val &= SDW_SCP_STAT_CLK_STP_NF;
		अगर (!val) अणु
			dev_dbg(bus->dev, "clock stop prep/de-prep done slave:%d",
				dev_num);
			वापस 0;
		पूर्ण

		usleep_range(1000, 1500);
		retry--;
	पूर्ण जबतक (retry);

	dev_err(bus->dev, "clock stop prep/de-prep failed slave:%d",
		dev_num);

	वापस -ETIMEDOUT;
पूर्ण

/**
 * sdw_bus_prep_clk_stop: prepare Slave(s) क्रम घड़ी stop
 *
 * @bus: SDW bus instance
 *
 * Query Slave क्रम घड़ी stop mode and prepare क्रम that mode.
 */
पूर्णांक sdw_bus_prep_clk_stop(काष्ठा sdw_bus *bus)
अणु
	क्रमागत sdw_clk_stop_mode slave_mode;
	bool simple_clk_stop = true;
	काष्ठा sdw_slave *slave;
	bool is_slave = false;
	पूर्णांक ret = 0;

	/*
	 * In order to save on transition समय, prepare
	 * each Slave and then रुको क्रम all Slave(s) to be
	 * prepared क्रम घड़ी stop.
	 */
	list_क्रम_each_entry(slave, &bus->slaves, node) अणु
		अगर (!slave->dev_num)
			जारी;

		अगर (slave->status != SDW_SLAVE_ATTACHED &&
		    slave->status != SDW_SLAVE_ALERT)
			जारी;

		/* Identअगरy अगर Slave(s) are available on Bus */
		is_slave = true;

		slave_mode = sdw_get_clk_stop_mode(slave);
		slave->curr_clk_stop_mode = slave_mode;

		ret = sdw_slave_clk_stop_callback(slave, slave_mode,
						  SDW_CLK_PRE_PREPARE);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"pre-prepare failed:%d", ret);
			वापस ret;
		पूर्ण

		ret = sdw_slave_clk_stop_prepare(slave,
						 slave_mode, true);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"pre-prepare failed:%d", ret);
			वापस ret;
		पूर्ण

		अगर (slave_mode == SDW_CLK_STOP_MODE1)
			simple_clk_stop = false;
	पूर्ण

	/* Skip reमुख्यing घड़ी stop preparation अगर no Slave is attached */
	अगर (!is_slave)
		वापस ret;

	अगर (!simple_clk_stop) अणु
		ret = sdw_bus_रुको_क्रम_clk_prep_deprep(bus,
						       SDW_BROADCAST_DEV_NUM);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Inक्रमm slaves that prep is करोne */
	list_क्रम_each_entry(slave, &bus->slaves, node) अणु
		अगर (!slave->dev_num)
			जारी;

		अगर (slave->status != SDW_SLAVE_ATTACHED &&
		    slave->status != SDW_SLAVE_ALERT)
			जारी;

		slave_mode = slave->curr_clk_stop_mode;

		अगर (slave_mode == SDW_CLK_STOP_MODE1) अणु
			ret = sdw_slave_clk_stop_callback(slave,
							  slave_mode,
							  SDW_CLK_POST_PREPARE);

			अगर (ret < 0) अणु
				dev_err(&slave->dev,
					"post-prepare failed:%d", ret);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_bus_prep_clk_stop);

/**
 * sdw_bus_clk_stop: stop bus घड़ी
 *
 * @bus: SDW bus instance
 *
 * After preparing the Slaves क्रम घड़ी stop, stop the घड़ी by broadcasting
 * ग_लिखो to SCP_CTRL रेजिस्टर.
 */
पूर्णांक sdw_bus_clk_stop(काष्ठा sdw_bus *bus)
अणु
	पूर्णांक ret;

	/*
	 * broadcast घड़ी stop now, attached Slaves will ACK this,
	 * unattached will ignore
	 */
	ret = sdw_bग_लिखो_no_pm(bus, SDW_BROADCAST_DEV_NUM,
			       SDW_SCP_CTRL, SDW_SCP_CTRL_CLK_STP_NOW);
	अगर (ret < 0) अणु
		अगर (ret == -ENODATA)
			dev_dbg(bus->dev,
				"ClockStopNow Broadcast msg ignored %d", ret);
		अन्यथा
			dev_err(bus->dev,
				"ClockStopNow Broadcast msg failed %d", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_bus_clk_stop);

/**
 * sdw_bus_निकास_clk_stop: Exit घड़ी stop mode
 *
 * @bus: SDW bus instance
 *
 * This De-prepares the Slaves by निकासing Clock Stop Mode 0. For the Slaves
 * निकासing Clock Stop Mode 1, they will be de-prepared after they क्रमागतerate
 * back.
 */
पूर्णांक sdw_bus_निकास_clk_stop(काष्ठा sdw_bus *bus)
अणु
	क्रमागत sdw_clk_stop_mode mode;
	bool simple_clk_stop = true;
	काष्ठा sdw_slave *slave;
	bool is_slave = false;
	पूर्णांक ret;

	/*
	 * In order to save on transition समय, de-prepare
	 * each Slave and then रुको क्रम all Slave(s) to be
	 * de-prepared after घड़ी resume.
	 */
	list_क्रम_each_entry(slave, &bus->slaves, node) अणु
		अगर (!slave->dev_num)
			जारी;

		अगर (slave->status != SDW_SLAVE_ATTACHED &&
		    slave->status != SDW_SLAVE_ALERT)
			जारी;

		/* Identअगरy अगर Slave(s) are available on Bus */
		is_slave = true;

		mode = slave->curr_clk_stop_mode;

		अगर (mode == SDW_CLK_STOP_MODE1) अणु
			simple_clk_stop = false;
			जारी;
		पूर्ण

		ret = sdw_slave_clk_stop_callback(slave, mode,
						  SDW_CLK_PRE_DEPREPARE);
		अगर (ret < 0)
			dev_warn(&slave->dev,
				 "clk stop deprep failed:%d", ret);

		ret = sdw_slave_clk_stop_prepare(slave, mode,
						 false);

		अगर (ret < 0)
			dev_warn(&slave->dev,
				 "clk stop deprep failed:%d", ret);
	पूर्ण

	/* Skip reमुख्यing घड़ी stop de-preparation अगर no Slave is attached */
	अगर (!is_slave)
		वापस 0;

	अगर (!simple_clk_stop)
		sdw_bus_रुको_क्रम_clk_prep_deprep(bus, SDW_BROADCAST_DEV_NUM);

	list_क्रम_each_entry(slave, &bus->slaves, node) अणु
		अगर (!slave->dev_num)
			जारी;

		अगर (slave->status != SDW_SLAVE_ATTACHED &&
		    slave->status != SDW_SLAVE_ALERT)
			जारी;

		mode = slave->curr_clk_stop_mode;
		sdw_slave_clk_stop_callback(slave, mode,
					    SDW_CLK_POST_DEPREPARE);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sdw_bus_निकास_clk_stop);

पूर्णांक sdw_configure_dpn_पूर्णांकr(काष्ठा sdw_slave *slave,
			   पूर्णांक port, bool enable, पूर्णांक mask)
अणु
	u32 addr;
	पूर्णांक ret;
	u8 val = 0;

	अगर (slave->bus->params.s_data_mode != SDW_PORT_DATA_MODE_NORMAL) अणु
		dev_dbg(&slave->dev, "TEST FAIL interrupt %s\n",
			enable ? "on" : "off");
		mask |= SDW_DPN_INT_TEST_FAIL;
	पूर्ण

	addr = SDW_DPN_INTMASK(port);

	/* Set/Clear port पढ़ोy पूर्णांकerrupt mask */
	अगर (enable) अणु
		val |= mask;
		val |= SDW_DPN_INT_PORT_READY;
	पूर्ण अन्यथा अणु
		val &= ~(mask);
		val &= ~SDW_DPN_INT_PORT_READY;
	पूर्ण

	ret = sdw_update(slave, addr, (mask | SDW_DPN_INT_PORT_READY), val);
	अगर (ret < 0)
		dev_err(&slave->dev,
			"SDW_DPN_INTMASK write failed:%d\n", val);

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_slave_set_frequency(काष्ठा sdw_slave *slave)
अणु
	u32 mclk_freq = slave->bus->prop.mclk_freq;
	u32 curr_freq = slave->bus->params.curr_dr_freq >> 1;
	अचिन्हित पूर्णांक scale;
	u8 scale_index;
	u8 base;
	पूर्णांक ret;

	/*
	 * frequency base and scale रेजिस्टरs are required क्रम SDCA
	 * devices. They may also be used क्रम 1.2+/non-SDCA devices,
	 * but we will need a DisCo property to cover this हाल
	 */
	अगर (!slave->id.class_id)
		वापस 0;

	अगर (!mclk_freq) अणु
		dev_err(&slave->dev,
			"no bus MCLK, cannot set SDW_SCP_BUS_CLOCK_BASE\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * map base frequency using Table 89 of SoundWire 1.2 spec.
	 * The order of the tests just follows the specअगरication, this
	 * is not a selection between possible values or a search क्रम
	 * the best value but just a mapping.  Only one हाल per platक्रमm
	 * is relevant.
	 * Some BIOS have inconsistent values क्रम mclk_freq but a
	 * correct root so we क्रमce the mclk_freq to aव्योम variations.
	 */
	अगर (!(19200000 % mclk_freq)) अणु
		mclk_freq = 19200000;
		base = SDW_SCP_BASE_CLOCK_19200000_HZ;
	पूर्ण अन्यथा अगर (!(24000000 % mclk_freq)) अणु
		mclk_freq = 24000000;
		base = SDW_SCP_BASE_CLOCK_24000000_HZ;
	पूर्ण अन्यथा अगर (!(24576000 % mclk_freq)) अणु
		mclk_freq = 24576000;
		base = SDW_SCP_BASE_CLOCK_24576000_HZ;
	पूर्ण अन्यथा अगर (!(22579200 % mclk_freq)) अणु
		mclk_freq = 22579200;
		base = SDW_SCP_BASE_CLOCK_22579200_HZ;
	पूर्ण अन्यथा अगर (!(32000000 % mclk_freq)) अणु
		mclk_freq = 32000000;
		base = SDW_SCP_BASE_CLOCK_32000000_HZ;
	पूर्ण अन्यथा अणु
		dev_err(&slave->dev,
			"Unsupported clock base, mclk %d\n",
			mclk_freq);
		वापस -EINVAL;
	पूर्ण

	अगर (mclk_freq % curr_freq) अणु
		dev_err(&slave->dev,
			"mclk %d is not multiple of bus curr_freq %d\n",
			mclk_freq, curr_freq);
		वापस -EINVAL;
	पूर्ण

	scale = mclk_freq / curr_freq;

	/*
	 * map scale to Table 90 of SoundWire 1.2 spec - and check
	 * that the scale is a घातer of two and maximum 64
	 */
	scale_index = ilog2(scale);

	अगर (BIT(scale_index) != scale || scale_index > 6) अणु
		dev_err(&slave->dev,
			"No match found for scale %d, bus mclk %d curr_freq %d\n",
			scale, mclk_freq, curr_freq);
		वापस -EINVAL;
	पूर्ण
	scale_index++;

	ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_BUS_CLOCK_BASE, base);
	अगर (ret < 0) अणु
		dev_err(&slave->dev,
			"SDW_SCP_BUS_CLOCK_BASE write failed:%d\n", ret);
		वापस ret;
	पूर्ण

	/* initialize scale क्रम both banks */
	ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_BUSCLOCK_SCALE_B0, scale_index);
	अगर (ret < 0) अणु
		dev_err(&slave->dev,
			"SDW_SCP_BUSCLOCK_SCALE_B0 write failed:%d\n", ret);
		वापस ret;
	पूर्ण
	ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_BUSCLOCK_SCALE_B1, scale_index);
	अगर (ret < 0)
		dev_err(&slave->dev,
			"SDW_SCP_BUSCLOCK_SCALE_B1 write failed:%d\n", ret);

	dev_dbg(&slave->dev,
		"Configured bus base %d, scale %d, mclk %d, curr_freq %d\n",
		base, scale_index, mclk_freq, curr_freq);

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_initialize_slave(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_prop *prop = &slave->prop;
	पूर्णांक status;
	पूर्णांक ret;
	u8 val;

	ret = sdw_slave_set_frequency(slave);
	अगर (ret < 0)
		वापस ret;

	अगर (slave->bus->prop.quirks & SDW_MASTER_QUIRKS_CLEAR_INITIAL_CLASH) अणु
		/* Clear bus clash पूर्णांकerrupt beक्रमe enabling पूर्णांकerrupt mask */
		status = sdw_पढ़ो_no_pm(slave, SDW_SCP_INT1);
		अगर (status < 0) अणु
			dev_err(&slave->dev,
				"SDW_SCP_INT1 (BUS_CLASH) read failed:%d\n", status);
			वापस status;
		पूर्ण
		अगर (status & SDW_SCP_INT1_BUS_CLASH) अणु
			dev_warn(&slave->dev, "Bus clash detected before INT mask is enabled\n");
			ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_INT1, SDW_SCP_INT1_BUS_CLASH);
			अगर (ret < 0) अणु
				dev_err(&slave->dev,
					"SDW_SCP_INT1 (BUS_CLASH) write failed:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((slave->bus->prop.quirks & SDW_MASTER_QUIRKS_CLEAR_INITIAL_PARITY) &&
	    !(slave->prop.quirks & SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY)) अणु
		/* Clear parity पूर्णांकerrupt beक्रमe enabling पूर्णांकerrupt mask */
		status = sdw_पढ़ो_no_pm(slave, SDW_SCP_INT1);
		अगर (status < 0) अणु
			dev_err(&slave->dev,
				"SDW_SCP_INT1 (PARITY) read failed:%d\n", status);
			वापस status;
		पूर्ण
		अगर (status & SDW_SCP_INT1_PARITY) अणु
			dev_warn(&slave->dev, "PARITY error detected before INT mask is enabled\n");
			ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_INT1, SDW_SCP_INT1_PARITY);
			अगर (ret < 0) अणु
				dev_err(&slave->dev,
					"SDW_SCP_INT1 (PARITY) write failed:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Set SCP_INT1_MASK रेजिस्टर, typically bus clash and
	 * implementation-defined पूर्णांकerrupt mask. The Parity detection
	 * may not always be correct on startup so its use is
	 * device-dependent, it might e.g. only be enabled in
	 * steady-state after a couple of frames.
	 */
	val = slave->prop.scp_पूर्णांक1_mask;

	/* Enable SCP पूर्णांकerrupts */
	ret = sdw_update_no_pm(slave, SDW_SCP_INTMASK1, val, val);
	अगर (ret < 0) अणु
		dev_err(&slave->dev,
			"SDW_SCP_INTMASK1 write failed:%d\n", ret);
		वापस ret;
	पूर्ण

	/* No need to जारी अगर DP0 is not present */
	अगर (!slave->prop.dp0_prop)
		वापस 0;

	/* Enable DP0 पूर्णांकerrupts */
	val = prop->dp0_prop->imp_def_पूर्णांकerrupts;
	val |= SDW_DP0_INT_PORT_READY | SDW_DP0_INT_BRA_FAILURE;

	ret = sdw_update_no_pm(slave, SDW_DP0_INTMASK, val, val);
	अगर (ret < 0)
		dev_err(&slave->dev,
			"SDW_DP0_INTMASK read failed:%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sdw_handle_dp0_पूर्णांकerrupt(काष्ठा sdw_slave *slave, u8 *slave_status)
अणु
	u8 clear, impl_पूर्णांक_mask;
	पूर्णांक status, status2, ret, count = 0;

	status = sdw_पढ़ो_no_pm(slave, SDW_DP0_INT);
	अगर (status < 0) अणु
		dev_err(&slave->dev,
			"SDW_DP0_INT read failed:%d\n", status);
		वापस status;
	पूर्ण

	करो अणु
		clear = status & ~SDW_DP0_INTERRUPTS;

		अगर (status & SDW_DP0_INT_TEST_FAIL) अणु
			dev_err(&slave->dev, "Test fail for port 0\n");
			clear |= SDW_DP0_INT_TEST_FAIL;
		पूर्ण

		/*
		 * Assumption: PORT_READY पूर्णांकerrupt will be received only क्रम
		 * ports implementing Channel Prepare state machine (CP_SM)
		 */

		अगर (status & SDW_DP0_INT_PORT_READY) अणु
			complete(&slave->port_पढ़ोy[0]);
			clear |= SDW_DP0_INT_PORT_READY;
		पूर्ण

		अगर (status & SDW_DP0_INT_BRA_FAILURE) अणु
			dev_err(&slave->dev, "BRA failed\n");
			clear |= SDW_DP0_INT_BRA_FAILURE;
		पूर्ण

		impl_पूर्णांक_mask = SDW_DP0_INT_IMPDEF1 |
			SDW_DP0_INT_IMPDEF2 | SDW_DP0_INT_IMPDEF3;

		अगर (status & impl_पूर्णांक_mask) अणु
			clear |= impl_पूर्णांक_mask;
			*slave_status = clear;
		पूर्ण

		/* clear the पूर्णांकerrupts but करोn't touch reserved and SDCA_CASCADE fields */
		ret = sdw_ग_लिखो_no_pm(slave, SDW_DP0_INT, clear);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"SDW_DP0_INT write failed:%d\n", ret);
			वापस ret;
		पूर्ण

		/* Read DP0 पूर्णांकerrupt again */
		status2 = sdw_पढ़ो_no_pm(slave, SDW_DP0_INT);
		अगर (status2 < 0) अणु
			dev_err(&slave->dev,
				"SDW_DP0_INT read failed:%d\n", status2);
			वापस status2;
		पूर्ण
		/* filter to limit loop to पूर्णांकerrupts identअगरied in the first status पढ़ो */
		status &= status2;

		count++;

		/* we can get alerts जबतक processing so keep retrying */
	पूर्ण जबतक ((status & SDW_DP0_INTERRUPTS) && (count < SDW_READ_INTR_CLEAR_RETRY));

	अगर (count == SDW_READ_INTR_CLEAR_RETRY)
		dev_warn(&slave->dev, "Reached MAX_RETRY on DP0 read\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_handle_port_पूर्णांकerrupt(काष्ठा sdw_slave *slave,
				     पूर्णांक port, u8 *slave_status)
अणु
	u8 clear, impl_पूर्णांक_mask;
	पूर्णांक status, status2, ret, count = 0;
	u32 addr;

	अगर (port == 0)
		वापस sdw_handle_dp0_पूर्णांकerrupt(slave, slave_status);

	addr = SDW_DPN_INT(port);
	status = sdw_पढ़ो_no_pm(slave, addr);
	अगर (status < 0) अणु
		dev_err(&slave->dev,
			"SDW_DPN_INT read failed:%d\n", status);

		वापस status;
	पूर्ण

	करो अणु
		clear = status & ~SDW_DPN_INTERRUPTS;

		अगर (status & SDW_DPN_INT_TEST_FAIL) अणु
			dev_err(&slave->dev, "Test fail for port:%d\n", port);
			clear |= SDW_DPN_INT_TEST_FAIL;
		पूर्ण

		/*
		 * Assumption: PORT_READY पूर्णांकerrupt will be received only
		 * क्रम ports implementing CP_SM.
		 */
		अगर (status & SDW_DPN_INT_PORT_READY) अणु
			complete(&slave->port_पढ़ोy[port]);
			clear |= SDW_DPN_INT_PORT_READY;
		पूर्ण

		impl_पूर्णांक_mask = SDW_DPN_INT_IMPDEF1 |
			SDW_DPN_INT_IMPDEF2 | SDW_DPN_INT_IMPDEF3;

		अगर (status & impl_पूर्णांक_mask) अणु
			clear |= impl_पूर्णांक_mask;
			*slave_status = clear;
		पूर्ण

		/* clear the पूर्णांकerrupt but करोn't touch reserved fields */
		ret = sdw_ग_लिखो_no_pm(slave, addr, clear);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"SDW_DPN_INT write failed:%d\n", ret);
			वापस ret;
		पूर्ण

		/* Read DPN पूर्णांकerrupt again */
		status2 = sdw_पढ़ो_no_pm(slave, addr);
		अगर (status2 < 0) अणु
			dev_err(&slave->dev,
				"SDW_DPN_INT read failed:%d\n", status2);
			वापस status2;
		पूर्ण
		/* filter to limit loop to पूर्णांकerrupts identअगरied in the first status पढ़ो */
		status &= status2;

		count++;

		/* we can get alerts जबतक processing so keep retrying */
	पूर्ण जबतक ((status & SDW_DPN_INTERRUPTS) && (count < SDW_READ_INTR_CLEAR_RETRY));

	अगर (count == SDW_READ_INTR_CLEAR_RETRY)
		dev_warn(&slave->dev, "Reached MAX_RETRY on port read");

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_handle_slave_alerts(काष्ठा sdw_slave *slave)
अणु
	काष्ठा sdw_slave_पूर्णांकr_status slave_पूर्णांकr;
	u8 clear = 0, bit, port_status[15] = अणु0पूर्ण;
	पूर्णांक port_num, stat, ret, count = 0;
	अचिन्हित दीर्घ port;
	bool slave_notअगरy;
	u8 sdca_cascade = 0;
	u8 buf, buf2[2], _buf, _buf2[2];
	bool parity_check;
	bool parity_quirk;

	sdw_modअगरy_slave_status(slave, SDW_SLAVE_ALERT);

	ret = pm_runसमय_get_sync(&slave->dev);
	अगर (ret < 0 && ret != -EACCES) अणु
		dev_err(&slave->dev, "Failed to resume device: %d\n", ret);
		pm_runसमय_put_noidle(&slave->dev);
		वापस ret;
	पूर्ण

	/* Read Intstat 1, Intstat 2 and Intstat 3 रेजिस्टरs */
	ret = sdw_पढ़ो_no_pm(slave, SDW_SCP_INT1);
	अगर (ret < 0) अणु
		dev_err(&slave->dev,
			"SDW_SCP_INT1 read failed:%d\n", ret);
		जाओ io_err;
	पूर्ण
	buf = ret;

	ret = sdw_nपढ़ो_no_pm(slave, SDW_SCP_INTSTAT2, 2, buf2);
	अगर (ret < 0) अणु
		dev_err(&slave->dev,
			"SDW_SCP_INT2/3 read failed:%d\n", ret);
		जाओ io_err;
	पूर्ण

	अगर (slave->prop.is_sdca) अणु
		ret = sdw_पढ़ो_no_pm(slave, SDW_DP0_INT);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"SDW_DP0_INT read failed:%d\n", ret);
			जाओ io_err;
		पूर्ण
		sdca_cascade = ret & SDW_DP0_SDCA_CASCADE;
	पूर्ण

	करो अणु
		slave_notअगरy = false;

		/*
		 * Check parity, bus clash and Slave (impl defined)
		 * पूर्णांकerrupt
		 */
		अगर (buf & SDW_SCP_INT1_PARITY) अणु
			parity_check = slave->prop.scp_पूर्णांक1_mask & SDW_SCP_INT1_PARITY;
			parity_quirk = !slave->first_पूर्णांकerrupt_करोne &&
				(slave->prop.quirks & SDW_SLAVE_QUIRKS_INVALID_INITIAL_PARITY);

			अगर (parity_check && !parity_quirk)
				dev_err(&slave->dev, "Parity error detected\n");
			clear |= SDW_SCP_INT1_PARITY;
		पूर्ण

		अगर (buf & SDW_SCP_INT1_BUS_CLASH) अणु
			अगर (slave->prop.scp_पूर्णांक1_mask & SDW_SCP_INT1_BUS_CLASH)
				dev_err(&slave->dev, "Bus clash detected\n");
			clear |= SDW_SCP_INT1_BUS_CLASH;
		पूर्ण

		/*
		 * When bus clash or parity errors are detected, such errors
		 * are unlikely to be recoverable errors.
		 * TODO: In such scenario, reset bus. Make this configurable
		 * via sysfs property with bus reset being the शेष.
		 */

		अगर (buf & SDW_SCP_INT1_IMPL_DEF) अणु
			अगर (slave->prop.scp_पूर्णांक1_mask & SDW_SCP_INT1_IMPL_DEF) अणु
				dev_dbg(&slave->dev, "Slave impl defined interrupt\n");
				slave_notअगरy = true;
			पूर्ण
			clear |= SDW_SCP_INT1_IMPL_DEF;
		पूर्ण

		/* the SDCA पूर्णांकerrupts are cleared in the codec driver .पूर्णांकerrupt_callback() */
		अगर (sdca_cascade)
			slave_notअगरy = true;

		/* Check port 0 - 3 पूर्णांकerrupts */
		port = buf & SDW_SCP_INT1_PORT0_3;

		/* To get port number corresponding to bits, shअगरt it */
		port = FIELD_GET(SDW_SCP_INT1_PORT0_3, port);
		क्रम_each_set_bit(bit, &port, 8) अणु
			sdw_handle_port_पूर्णांकerrupt(slave, bit,
						  &port_status[bit]);
		पूर्ण

		/* Check अगर cascade 2 पूर्णांकerrupt is present */
		अगर (buf & SDW_SCP_INT1_SCP2_CASCADE) अणु
			port = buf2[0] & SDW_SCP_INTSTAT2_PORT4_10;
			क्रम_each_set_bit(bit, &port, 8) अणु
				/* scp2 ports start from 4 */
				port_num = bit + 3;
				sdw_handle_port_पूर्णांकerrupt(slave,
						port_num,
						&port_status[port_num]);
			पूर्ण
		पूर्ण

		/* now check last cascade */
		अगर (buf2[0] & SDW_SCP_INTSTAT2_SCP3_CASCADE) अणु
			port = buf2[1] & SDW_SCP_INTSTAT3_PORT11_14;
			क्रम_each_set_bit(bit, &port, 8) अणु
				/* scp3 ports start from 11 */
				port_num = bit + 10;
				sdw_handle_port_पूर्णांकerrupt(slave,
						port_num,
						&port_status[port_num]);
			पूर्ण
		पूर्ण

		/* Update the Slave driver */
		अगर (slave_notअगरy && slave->ops &&
		    slave->ops->पूर्णांकerrupt_callback) अणु
			slave_पूर्णांकr.sdca_cascade = sdca_cascade;
			slave_पूर्णांकr.control_port = clear;
			स_नकल(slave_पूर्णांकr.port, &port_status,
			       माप(slave_पूर्णांकr.port));

			slave->ops->पूर्णांकerrupt_callback(slave, &slave_पूर्णांकr);
		पूर्ण

		/* Ack पूर्णांकerrupt */
		ret = sdw_ग_लिखो_no_pm(slave, SDW_SCP_INT1, clear);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"SDW_SCP_INT1 write failed:%d\n", ret);
			जाओ io_err;
		पूर्ण

		/* at this poपूर्णांक all initial पूर्णांकerrupt sources were handled */
		slave->first_पूर्णांकerrupt_करोne = true;

		/*
		 * Read status again to ensure no new पूर्णांकerrupts arrived
		 * जबतक servicing पूर्णांकerrupts.
		 */
		ret = sdw_पढ़ो_no_pm(slave, SDW_SCP_INT1);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"SDW_SCP_INT1 recheck read failed:%d\n", ret);
			जाओ io_err;
		पूर्ण
		_buf = ret;

		ret = sdw_nपढ़ो_no_pm(slave, SDW_SCP_INTSTAT2, 2, _buf2);
		अगर (ret < 0) अणु
			dev_err(&slave->dev,
				"SDW_SCP_INT2/3 recheck read failed:%d\n", ret);
			जाओ io_err;
		पूर्ण

		अगर (slave->prop.is_sdca) अणु
			ret = sdw_पढ़ो_no_pm(slave, SDW_DP0_INT);
			अगर (ret < 0) अणु
				dev_err(&slave->dev,
					"SDW_DP0_INT recheck read failed:%d\n", ret);
				जाओ io_err;
			पूर्ण
			sdca_cascade = ret & SDW_DP0_SDCA_CASCADE;
		पूर्ण

		/*
		 * Make sure no पूर्णांकerrupts are pending, but filter to limit loop
		 * to पूर्णांकerrupts identअगरied in the first status पढ़ो
		 */
		buf &= _buf;
		buf2[0] &= _buf2[0];
		buf2[1] &= _buf2[1];
		stat = buf || buf2[0] || buf2[1] || sdca_cascade;

		/*
		 * Exit loop अगर Slave is continuously in ALERT state even
		 * after servicing the पूर्णांकerrupt multiple बार.
		 */
		count++;

		/* we can get alerts जबतक processing so keep retrying */
	पूर्ण जबतक (stat != 0 && count < SDW_READ_INTR_CLEAR_RETRY);

	अगर (count == SDW_READ_INTR_CLEAR_RETRY)
		dev_warn(&slave->dev, "Reached MAX_RETRY on alert read\n");

io_err:
	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sdw_update_slave_status(काष्ठा sdw_slave *slave,
				   क्रमागत sdw_slave_status status)
अणु
	अचिन्हित दीर्घ समय;

	अगर (!slave->probed) अणु
		/*
		 * the slave status update is typically handled in an
		 * पूर्णांकerrupt thपढ़ो, which can race with the driver
		 * probe, e.g. when a module needs to be loaded.
		 *
		 * make sure the probe is complete beक्रमe updating
		 * status.
		 */
		समय = रुको_क्रम_completion_समयout(&slave->probe_complete,
				msecs_to_jअगरfies(DEFAULT_PROBE_TIMEOUT));
		अगर (!समय) अणु
			dev_err(&slave->dev, "Probe not complete, timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	अगर (!slave->ops || !slave->ops->update_status)
		वापस 0;

	वापस slave->ops->update_status(slave, status);
पूर्ण

/**
 * sdw_handle_slave_status() - Handle Slave status
 * @bus: SDW bus instance
 * @status: Status क्रम all Slave(s)
 */
पूर्णांक sdw_handle_slave_status(काष्ठा sdw_bus *bus,
			    क्रमागत sdw_slave_status status[])
अणु
	क्रमागत sdw_slave_status prev_status;
	काष्ठा sdw_slave *slave;
	bool attached_initializing;
	पूर्णांक i, ret = 0;

	/* first check अगर any Slaves fell off the bus */
	क्रम (i = 1; i <= SDW_MAX_DEVICES; i++) अणु
		mutex_lock(&bus->bus_lock);
		अगर (test_bit(i, bus->asचिन्हित) == false) अणु
			mutex_unlock(&bus->bus_lock);
			जारी;
		पूर्ण
		mutex_unlock(&bus->bus_lock);

		slave = sdw_get_slave(bus, i);
		अगर (!slave)
			जारी;

		अगर (status[i] == SDW_SLAVE_UNATTACHED &&
		    slave->status != SDW_SLAVE_UNATTACHED)
			sdw_modअगरy_slave_status(slave, SDW_SLAVE_UNATTACHED);
	पूर्ण

	अगर (status[0] == SDW_SLAVE_ATTACHED) अणु
		dev_dbg(bus->dev, "Slave attached, programming device number\n");
		ret = sdw_program_device_num(bus);
		अगर (ret < 0)
			dev_err(bus->dev, "Slave attach failed: %d\n", ret);
		/*
		 * programming a device number will have side effects,
		 * so we deal with other devices at a later समय
		 */
		वापस ret;
	पूर्ण

	/* Continue to check other slave statuses */
	क्रम (i = 1; i <= SDW_MAX_DEVICES; i++) अणु
		mutex_lock(&bus->bus_lock);
		अगर (test_bit(i, bus->asचिन्हित) == false) अणु
			mutex_unlock(&bus->bus_lock);
			जारी;
		पूर्ण
		mutex_unlock(&bus->bus_lock);

		slave = sdw_get_slave(bus, i);
		अगर (!slave)
			जारी;

		attached_initializing = false;

		चयन (status[i]) अणु
		हाल SDW_SLAVE_UNATTACHED:
			अगर (slave->status == SDW_SLAVE_UNATTACHED)
				अवरोध;

			sdw_modअगरy_slave_status(slave, SDW_SLAVE_UNATTACHED);
			अवरोध;

		हाल SDW_SLAVE_ALERT:
			ret = sdw_handle_slave_alerts(slave);
			अगर (ret < 0)
				dev_err(&slave->dev,
					"Slave %d alert handling failed: %d\n",
					i, ret);
			अवरोध;

		हाल SDW_SLAVE_ATTACHED:
			अगर (slave->status == SDW_SLAVE_ATTACHED)
				अवरोध;

			prev_status = slave->status;
			sdw_modअगरy_slave_status(slave, SDW_SLAVE_ATTACHED);

			अगर (prev_status == SDW_SLAVE_ALERT)
				अवरोध;

			attached_initializing = true;

			ret = sdw_initialize_slave(slave);
			अगर (ret < 0)
				dev_err(&slave->dev,
					"Slave %d initialization failed: %d\n",
					i, ret);

			अवरोध;

		शेष:
			dev_err(&slave->dev, "Invalid slave %d status:%d\n",
				i, status[i]);
			अवरोध;
		पूर्ण

		ret = sdw_update_slave_status(slave, status[i]);
		अगर (ret < 0)
			dev_err(&slave->dev,
				"Update Slave status failed:%d\n", ret);
		अगर (attached_initializing) अणु
			dev_dbg(&slave->dev,
				"%s: signaling initialization completion for Slave %d\n",
				__func__, slave->dev_num);

			complete(&slave->initialization_complete);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(sdw_handle_slave_status);

व्योम sdw_clear_slave_status(काष्ठा sdw_bus *bus, u32 request)
अणु
	काष्ठा sdw_slave *slave;
	पूर्णांक i;

	/* Check all non-zero devices */
	क्रम (i = 1; i <= SDW_MAX_DEVICES; i++) अणु
		mutex_lock(&bus->bus_lock);
		अगर (test_bit(i, bus->asचिन्हित) == false) अणु
			mutex_unlock(&bus->bus_lock);
			जारी;
		पूर्ण
		mutex_unlock(&bus->bus_lock);

		slave = sdw_get_slave(bus, i);
		अगर (!slave)
			जारी;

		अगर (slave->status != SDW_SLAVE_UNATTACHED) अणु
			sdw_modअगरy_slave_status(slave, SDW_SLAVE_UNATTACHED);
			slave->first_पूर्णांकerrupt_करोne = false;
		पूर्ण

		/* keep track of request, used in pm_runसमय resume */
		slave->unattach_request = request;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sdw_clear_slave_status);
