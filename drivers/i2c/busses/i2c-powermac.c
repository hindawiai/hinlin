<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    i2c Support क्रम Apple SMU Controller

    Copyright (c) 2005 Benjamin Herrenschmidt, IBM Corp.
                       <benh@kernel.crashing.org>


*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_irq.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmac_low_i2c.h>

MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("I2C driver for Apple PowerMac");
MODULE_LICENSE("GPL");

/*
 * SMBUS-type transfer entrypoपूर्णांक
 */
अटल s32 i2c_घातermac_smbus_xfer(	काष्ठा i2c_adapter*	adap,
					u16			addr,
					अचिन्हित लघु		flags,
					अक्षर			पढ़ो_ग_लिखो,
					u8			command,
					पूर्णांक			size,
					जोड़ i2c_smbus_data*	data)
अणु
	काष्ठा pmac_i2c_bus	*bus = i2c_get_adapdata(adap);
	पूर्णांक			rc = 0;
	पूर्णांक			पढ़ो = (पढ़ो_ग_लिखो == I2C_SMBUS_READ);
	पूर्णांक			addrdir = (addr << 1) | पढ़ो;
	पूर्णांक			mode, subsize, len;
	u32			subaddr;
	u8			*buf;
	u8			local[2];

	अगर (size == I2C_SMBUS_QUICK || size == I2C_SMBUS_BYTE) अणु
		mode = pmac_i2c_mode_std;
		subsize = 0;
		subaddr = 0;
	पूर्ण अन्यथा अणु
		mode = पढ़ो ? pmac_i2c_mode_combined : pmac_i2c_mode_stdsub;
		subsize = 1;
		subaddr = command;
	पूर्ण

	चयन (size) अणु
        हाल I2C_SMBUS_QUICK:
		buf = शून्य;
		len = 0;
	    	अवरोध;
        हाल I2C_SMBUS_BYTE:
        हाल I2C_SMBUS_BYTE_DATA:
		buf = &data->byte;
		len = 1;
	    	अवरोध;
        हाल I2C_SMBUS_WORD_DATA:
		अगर (!पढ़ो) अणु
			local[0] = data->word & 0xff;
			local[1] = (data->word >> 8) & 0xff;
		पूर्ण
		buf = local;
		len = 2;
	    	अवरोध;

	/* Note that these are broken vs. the expected smbus API where
	 * on पढ़ोs, the length is actually वापसed from the function,
	 * but I think the current API makes no sense and I करोn't want
	 * any driver that I haven't verअगरied क्रम correctness to go
	 * anywhere near a pmac i2c bus anyway ...
	 */
        हाल I2C_SMBUS_BLOCK_DATA:
		buf = data->block;
		len = data->block[0] + 1;
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		buf = &data->block[1];
		len = data->block[0];
		अवरोध;

        शेष:
		वापस -EINVAL;
	पूर्ण

	rc = pmac_i2c_खोलो(bus, 0);
	अगर (rc) अणु
		dev_err(&adap->dev, "Failed to open I2C, err %d\n", rc);
		वापस rc;
	पूर्ण

	rc = pmac_i2c_seपंचांगode(bus, mode);
	अगर (rc) अणु
		dev_err(&adap->dev, "Failed to set I2C mode %d, err %d\n",
			mode, rc);
		जाओ bail;
	पूर्ण

	rc = pmac_i2c_xfer(bus, addrdir, subsize, subaddr, buf, len);
	अगर (rc) अणु
		अगर (rc == -ENXIO)
			dev_dbg(&adap->dev,
				"I2C transfer at 0x%02x failed, size %d, "
				"err %d\n", addrdir >> 1, size, rc);
		अन्यथा
			dev_err(&adap->dev,
				"I2C transfer at 0x%02x failed, size %d, "
				"err %d\n", addrdir >> 1, size, rc);
		जाओ bail;
	पूर्ण

	अगर (size == I2C_SMBUS_WORD_DATA && पढ़ो) अणु
		data->word = ((u16)local[1]) << 8;
		data->word |= local[0];
	पूर्ण

 bail:
	pmac_i2c_बंद(bus);
	वापस rc;
पूर्ण

/*
 * Generic i2c master transfer entrypoपूर्णांक. This driver only support single
 * messages (क्रम "lame i2c" transfers). Anything अन्यथा should use the smbus
 * entry poपूर्णांक
 */
अटल पूर्णांक i2c_घातermac_master_xfer(	काष्ठा i2c_adapter *adap,
					काष्ठा i2c_msg *msgs,
					पूर्णांक num)
अणु
	काष्ठा pmac_i2c_bus	*bus = i2c_get_adapdata(adap);
	पूर्णांक			rc = 0;
	पूर्णांक			addrdir;

	अगर (msgs->flags & I2C_M_TEN)
		वापस -EINVAL;
	addrdir = i2c_8bit_addr_from_msg(msgs);

	rc = pmac_i2c_खोलो(bus, 0);
	अगर (rc) अणु
		dev_err(&adap->dev, "Failed to open I2C, err %d\n", rc);
		वापस rc;
	पूर्ण
	rc = pmac_i2c_seपंचांगode(bus, pmac_i2c_mode_std);
	अगर (rc) अणु
		dev_err(&adap->dev, "Failed to set I2C mode %d, err %d\n",
			pmac_i2c_mode_std, rc);
		जाओ bail;
	पूर्ण
	rc = pmac_i2c_xfer(bus, addrdir, 0, 0, msgs->buf, msgs->len);
	अगर (rc < 0) अणु
		अगर (rc == -ENXIO)
			dev_dbg(&adap->dev, "I2C %s 0x%02x failed, err %d\n",
				addrdir & 1 ? "read from" : "write to",
				addrdir >> 1, rc);
		अन्यथा
			dev_err(&adap->dev, "I2C %s 0x%02x failed, err %d\n",
				addrdir & 1 ? "read from" : "write to",
				addrdir >> 1, rc);
	पूर्ण
 bail:
	pmac_i2c_बंद(bus);
	वापस rc < 0 ? rc : 1;
पूर्ण

अटल u32 i2c_घातermac_func(काष्ठा i2c_adapter * adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_I2C;
पूर्ण

/* For now, we only handle smbus */
अटल स्थिर काष्ठा i2c_algorithm i2c_घातermac_algorithm = अणु
	.smbus_xfer	= i2c_घातermac_smbus_xfer,
	.master_xfer	= i2c_घातermac_master_xfer,
	.functionality	= i2c_घातermac_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks i2c_घातermac_quirks = अणु
	.max_num_msgs = 1,
पूर्ण;

अटल पूर्णांक i2c_घातermac_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा i2c_adapter	*adapter = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(adapter);
	स_रखो(adapter, 0, माप(*adapter));

	वापस 0;
पूर्ण

अटल u32 i2c_घातermac_get_addr(काष्ठा i2c_adapter *adap,
					   काष्ठा pmac_i2c_bus *bus,
					   काष्ठा device_node *node)
अणु
	u32 prop;
	पूर्णांक ret;

	/* First check क्रम valid "reg" */
	ret = of_property_पढ़ो_u32(node, "reg", &prop);
	अगर (ret == 0)
		वापस (prop & 0xff) >> 1;

	/* Then check old-style "i2c-address" */
	ret = of_property_पढ़ो_u32(node, "i2c-address", &prop);
	अगर (ret == 0)
		वापस (prop & 0xff) >> 1;

	/* Now handle some devices with missing "reg" properties */
	अगर (of_node_name_eq(node, "cereal"))
		वापस 0x60;
	अन्यथा अगर (of_node_name_eq(node, "deq"))
		वापस 0x34;

	dev_warn(&adap->dev, "No i2c address for %pOF\n", node);

	वापस 0xffffffff;
पूर्ण

अटल व्योम i2c_घातermac_create_one(काष्ठा i2c_adapter *adap,
					      स्थिर अक्षर *type,
					      u32 addr)
अणु
	काष्ठा i2c_board_info info = अणुपूर्ण;
	काष्ठा i2c_client *newdev;

	म_नकलन(info.type, type, माप(info.type));
	info.addr = addr;
	newdev = i2c_new_client_device(adap, &info);
	अगर (IS_ERR(newdev))
		dev_err(&adap->dev,
			"i2c-powermac: Failure to register missing %s\n",
			type);
पूर्ण

अटल व्योम i2c_घातermac_add_missing(काष्ठा i2c_adapter *adap,
					       काष्ठा pmac_i2c_bus *bus,
					       bool found_onyx)
अणु
	काष्ठा device_node *busnode = pmac_i2c_get_bus_node(bus);
	पूर्णांक rc;

	/* Check क्रम the onyx audio codec */
#घोषणा ONYX_REG_CONTROL		67
	अगर (of_device_is_compatible(busnode, "k2-i2c") && !found_onyx) अणु
		जोड़ i2c_smbus_data data;

		rc = i2c_smbus_xfer(adap, 0x46, 0, I2C_SMBUS_READ,
				    ONYX_REG_CONTROL, I2C_SMBUS_BYTE_DATA,
				    &data);
		अगर (rc >= 0)
			i2c_घातermac_create_one(adap, "MAC,pcm3052", 0x46);

		rc = i2c_smbus_xfer(adap, 0x47, 0, I2C_SMBUS_READ,
				    ONYX_REG_CONTROL, I2C_SMBUS_BYTE_DATA,
				    &data);
		अगर (rc >= 0)
			i2c_घातermac_create_one(adap, "MAC,pcm3052", 0x47);
	पूर्ण
पूर्ण

अटल bool i2c_घातermac_get_type(काष्ठा i2c_adapter *adap,
					    काष्ठा device_node *node,
					    u32 addr, अक्षर *type, पूर्णांक type_size)
अणु
	अक्षर पंचांगp[16];

	/*
	 * Note: we करो _NOT_ want the standard i2c drivers to match with any of
	 * our घातermac stuff unless they have been specअगरically modअगरied to
	 * handle it on a हाल by हाल basis. For example, क्रम thermal control,
	 * things like lm75 etc... shall match with their corresponding
	 * windfarm drivers, _NOT_ the generic ones, so we क्रमce a prefix of
	 * 'MAC', onto the modalias to make that happen
	 */

	/* First try proper modalias */
	अगर (of_modalias_node(node, पंचांगp, माप(पंचांगp)) >= 0) अणु
		snम_लिखो(type, type_size, "MAC,%s", पंचांगp);
		वापस true;
	पूर्ण

	/* Now look क्रम known workarounds */
	अगर (of_node_name_eq(node, "deq")) अणु
		/* Apple uses address 0x34 क्रम TAS3001 and 0x35 क्रम TAS3004 */
		अगर (addr == 0x34) अणु
			snम_लिखो(type, type_size, "MAC,tas3001");
			वापस true;
		पूर्ण अन्यथा अगर (addr == 0x35) अणु
			snम_लिखो(type, type_size, "MAC,tas3004");
			वापस true;
		पूर्ण
	पूर्ण

	dev_err(&adap->dev, "i2c-powermac: modalias failure on %pOF\n", node);
	वापस false;
पूर्ण

अटल व्योम i2c_घातermac_रेजिस्टर_devices(काष्ठा i2c_adapter *adap,
						    काष्ठा pmac_i2c_bus *bus)
अणु
	काष्ठा i2c_client *newdev;
	काष्ठा device_node *node;
	bool found_onyx = false;

	/*
	 * In some हालs we end up with the via-pmu node itself, in this
	 * हाल we skip this function completely as the device-tree will
	 * not contain anything useful.
	 */
	अगर (of_node_name_eq(adap->dev.of_node, "via-pmu"))
		वापस;

	क्रम_each_child_of_node(adap->dev.of_node, node) अणु
		काष्ठा i2c_board_info info = अणुपूर्ण;
		u32 addr;

		/* Get address & channel */
		addr = i2c_घातermac_get_addr(adap, bus, node);
		अगर (addr == 0xffffffff)
			जारी;

		/* Multibus setup, check channel */
		अगर (!pmac_i2c_match_adapter(node, adap))
			जारी;

		dev_dbg(&adap->dev, "i2c-powermac: register %pOF\n", node);

		/*
		 * Keep track of some device existence to handle
		 * workarounds later.
		 */
		अगर (of_device_is_compatible(node, "pcm3052"))
			found_onyx = true;

		/* Make up a modalias */
		अगर (!i2c_घातermac_get_type(adap, node, addr,
					   info.type, माप(info.type))) अणु
			जारी;
		पूर्ण

		/* Fill out the rest of the info काष्ठाure */
		info.addr = addr;
		info.irq = irq_of_parse_and_map(node, 0);
		info.of_node = of_node_get(node);

		newdev = i2c_new_client_device(adap, &info);
		अगर (IS_ERR(newdev)) अणु
			dev_err(&adap->dev, "i2c-powermac: Failure to register"
				" %pOF\n", node);
			of_node_put(node);
			/* We करो not dispose of the पूर्णांकerrupt mapping on
			 * purpose. It's not necessary (पूर्णांकerrupt cannot be
			 * re-used) and somebody अन्यथा might have grabbed it
			 * via direct DT lookup so let's not bother
			 */
			जारी;
		पूर्ण
	पूर्ण

	/* Additional workarounds */
	i2c_घातermac_add_missing(adap, bus, found_onyx);
पूर्ण

अटल पूर्णांक i2c_घातermac_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pmac_i2c_bus *bus = dev_get_platdata(&dev->dev);
	काष्ठा device_node *parent;
	काष्ठा i2c_adapter *adapter;
	पूर्णांक rc;

	अगर (bus == शून्य)
		वापस -EINVAL;
	adapter = pmac_i2c_get_adapter(bus);

	/* Ok, now we need to make up a name क्रम the पूर्णांकerface that will
	 * match what we used to करो in the past, that is basically the
	 * controller's parent device node for keywest. PMU didn't have a
	 * naming convention and SMU has a dअगरferent one
	 */
	चयन(pmac_i2c_get_type(bus)) अणु
	हाल pmac_i2c_bus_keywest:
		parent = of_get_parent(pmac_i2c_get_controller(bus));
		अगर (parent == शून्य)
			वापस -EINVAL;
		snम_लिखो(adapter->name, माप(adapter->name), "%pOFn %d",
			 parent,
			 pmac_i2c_get_channel(bus));
		of_node_put(parent);
		अवरोध;
	हाल pmac_i2c_bus_pmu:
		snम_लिखो(adapter->name, माप(adapter->name), "pmu %d",
			 pmac_i2c_get_channel(bus));
		अवरोध;
	हाल pmac_i2c_bus_smu:
		/* This is not what we used to करो but I'm fixing drivers at
		 * the same समय as this change
		 */
		snम_लिखो(adapter->name, माप(adapter->name), "smu %d",
			 pmac_i2c_get_channel(bus));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	platक्रमm_set_drvdata(dev, adapter);
	adapter->algo = &i2c_घातermac_algorithm;
	adapter->quirks = &i2c_घातermac_quirks;
	i2c_set_adapdata(adapter, bus);
	adapter->dev.parent = &dev->dev;

	/* Clear of_node to skip स्वतःmatic registration of i2c child nodes */
	adapter->dev.of_node = शून्य;
	rc = i2c_add_adapter(adapter);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "i2c-powermac: Adapter %s registration "
		       "failed\n", adapter->name);
		स_रखो(adapter, 0, माप(*adapter));
		वापस rc;
	पूर्ण

	prपूर्णांकk(KERN_INFO "PowerMac i2c bus %s registered\n", adapter->name);

	/* Use custom child registration due to Apple device-tree funkyness */
	adapter->dev.of_node = dev->dev.of_node;
	i2c_घातermac_रेजिस्टर_devices(adapter, bus);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver i2c_घातermac_driver = अणु
	.probe = i2c_घातermac_probe,
	.हटाओ = i2c_घातermac_हटाओ,
	.driver = अणु
		.name = "i2c-powermac",
		.bus = &platक्रमm_bus_type,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(i2c_घातermac_driver);

MODULE_ALIAS("platform:i2c-powermac");
