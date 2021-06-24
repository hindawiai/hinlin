<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
    i2c-isch.c - Linux kernel driver क्रम Intel SCH chipset SMBus
    - Based on i2c-piix4.c
    Copyright (c) 1998 - 2002 Froकरो Looijaard <froकरोl@dds.nl> and
    Philip Edelbrock <phil@netroedge.com>
    - Intel SCH support
    Copyright (c) 2007 - 2008 Jacob Jun Pan <jacob.jun.pan@पूर्णांकel.com>

*/

/*
   Supports:
	Intel SCH chipsets (AF82US15W, AF82US15L, AF82UL11L)
   Note: we assume there can only be one device, with one SMBus पूर्णांकerface.
*/

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>

/* SCH SMBus address offsets */
#घोषणा SMBHSTCNT	(0 + sch_smba)
#घोषणा SMBHSTSTS	(1 + sch_smba)
#घोषणा SMBHSTCLK	(2 + sch_smba)
#घोषणा SMBHSTADD	(4 + sch_smba) /* TSA */
#घोषणा SMBHSTCMD	(5 + sch_smba)
#घोषणा SMBHSTDAT0	(6 + sch_smba)
#घोषणा SMBHSTDAT1	(7 + sch_smba)
#घोषणा SMBBLKDAT	(0x20 + sch_smba)

/* Other settings */
#घोषणा MAX_RETRIES	5000

/* I2C स्थिरants */
#घोषणा SCH_QUICK		0x00
#घोषणा SCH_BYTE		0x01
#घोषणा SCH_BYTE_DATA		0x02
#घोषणा SCH_WORD_DATA		0x03
#घोषणा SCH_BLOCK_DATA		0x05

अटल अचिन्हित लघु sch_smba;
अटल काष्ठा i2c_adapter sch_adapter;
अटल पूर्णांक backbone_speed = 33000; /* backbone speed in kHz */
module_param(backbone_speed, पूर्णांक, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(backbone_speed, "Backbone speed in kHz, (default = 33000)");

/*
 * Start the i2c transaction -- the i2c_access will prepare the transaction
 * and this function will execute it.
 * वापस 0 क्रम success and others क्रम failure.
 */
अटल पूर्णांक sch_transaction(व्योम)
अणु
	पूर्णांक temp;
	पूर्णांक result = 0;
	पूर्णांक retries = 0;

	dev_dbg(&sch_adapter.dev, "Transaction (pre): CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb(SMBHSTCNT),
		inb(SMBHSTCMD), inb(SMBHSTADD), inb(SMBHSTDAT0),
		inb(SMBHSTDAT1));

	/* Make sure the SMBus host is पढ़ोy to start transmitting */
	temp = inb(SMBHSTSTS) & 0x0f;
	अगर (temp) अणु
		/* Can not be busy since we checked it in sch_access */
		अगर (temp & 0x01) अणु
			dev_dbg(&sch_adapter.dev, "Completion (%02x). "
				"Clear...\n", temp);
		पूर्ण
		अगर (temp & 0x06) अणु
			dev_dbg(&sch_adapter.dev, "SMBus error (%02x). "
				"Resetting...\n", temp);
		पूर्ण
		outb(temp, SMBHSTSTS);
		temp = inb(SMBHSTSTS) & 0x0f;
		अगर (temp) अणु
			dev_err(&sch_adapter.dev,
				"SMBus is not ready: (%02x)\n", temp);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	/* start the transaction by setting bit 4 */
	outb(inb(SMBHSTCNT) | 0x10, SMBHSTCNT);

	करो अणु
		usleep_range(100, 200);
		temp = inb(SMBHSTSTS) & 0x0f;
	पूर्ण जबतक ((temp & 0x08) && (retries++ < MAX_RETRIES));

	/* If the SMBus is still busy, we give up */
	अगर (retries > MAX_RETRIES) अणु
		dev_err(&sch_adapter.dev, "SMBus Timeout!\n");
		result = -ETIMEDOUT;
	पूर्ण
	अगर (temp & 0x04) अणु
		result = -EIO;
		dev_dbg(&sch_adapter.dev, "Bus collision! SMBus may be "
			"locked until next hard reset. (sorry!)\n");
		/* Clock stops and slave is stuck in mid-transmission */
	पूर्ण अन्यथा अगर (temp & 0x02) अणु
		result = -EIO;
		dev_err(&sch_adapter.dev, "Error: no response!\n");
	पूर्ण अन्यथा अगर (temp & 0x01) अणु
		dev_dbg(&sch_adapter.dev, "Post complete!\n");
		outb(temp, SMBHSTSTS);
		temp = inb(SMBHSTSTS) & 0x07;
		अगर (temp & 0x06) अणु
			/* Completion clear failed */
			dev_dbg(&sch_adapter.dev, "Failed reset at end of "
				"transaction (%02x), Bus error!\n", temp);
		पूर्ण
	पूर्ण अन्यथा अणु
		result = -ENXIO;
		dev_dbg(&sch_adapter.dev, "No such address.\n");
	पूर्ण
	dev_dbg(&sch_adapter.dev, "Transaction (post): CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb(SMBHSTCNT),
		inb(SMBHSTCMD), inb(SMBHSTADD), inb(SMBHSTDAT0),
		inb(SMBHSTDAT1));
	वापस result;
पूर्ण

/*
 * This is the मुख्य access entry क्रम i2c-sch access
 * adap is i2c_adapter poपूर्णांकer, addr is the i2c device bus address, पढ़ो_ग_लिखो
 * (0 क्रम पढ़ो and 1 क्रम ग_लिखो), size is i2c transaction type and data is the
 * जोड़ of transaction क्रम data to be transferred or data पढ़ो from bus.
 * वापस 0 क्रम success and others क्रम failure.
 */
अटल s32 sch_access(काष्ठा i2c_adapter *adap, u16 addr,
		 अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		 u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक i, len, temp, rc;

	/* Make sure the SMBus host is not busy */
	temp = inb(SMBHSTSTS) & 0x0f;
	अगर (temp & 0x08) अणु
		dev_dbg(&sch_adapter.dev, "SMBus busy (%02x)\n", temp);
		वापस -EAGAIN;
	पूर्ण
	temp = inw(SMBHSTCLK);
	अगर (!temp) अणु
		/*
		 * We can't determine अगर we have 33 or 25 MHz घड़ी क्रम
		 * SMBus, so expect 33 MHz and calculate a bus घड़ी of
		 * 100 kHz. If we actually run at 25 MHz the bus will be
		 * run ~75 kHz instead which should करो no harm.
		 */
		dev_notice(&sch_adapter.dev,
			"Clock divider uninitialized. Setting defaults\n");
		outw(backbone_speed / (4 * 100), SMBHSTCLK);
	पूर्ण

	dev_dbg(&sch_adapter.dev, "access size: %d %s\n", size,
		(पढ़ो_ग_लिखो)?"READ":"WRITE");
	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		outb((addr << 1) | पढ़ो_ग_लिखो, SMBHSTADD);
		size = SCH_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		outb((addr << 1) | पढ़ो_ग_लिखो, SMBHSTADD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb(command, SMBHSTCMD);
		size = SCH_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		outb((addr << 1) | पढ़ो_ग_लिखो, SMBHSTADD);
		outb(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb(data->byte, SMBHSTDAT0);
		size = SCH_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		outb((addr << 1) | पढ़ो_ग_लिखो, SMBHSTADD);
		outb(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb(data->word & 0xff, SMBHSTDAT0);
			outb((data->word & 0xff00) >> 8, SMBHSTDAT1);
		पूर्ण
		size = SCH_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		outb((addr << 1) | पढ़ो_ग_लिखो, SMBHSTADD);
		outb(command, SMBHSTCMD);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = data->block[0];
			अगर (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
				वापस -EINVAL;
			outb(len, SMBHSTDAT0);
			क्रम (i = 1; i <= len; i++)
				outb(data->block[i], SMBBLKDAT+i-1);
		पूर्ण
		size = SCH_BLOCK_DATA;
		अवरोध;
	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण
	dev_dbg(&sch_adapter.dev, "write size %d to 0x%04x\n", size, SMBHSTCNT);
	outb((inb(SMBHSTCNT) & 0xb0) | (size & 0x7), SMBHSTCNT);

	rc = sch_transaction();
	अगर (rc)	/* Error in transaction */
		वापस rc;

	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (size == SCH_QUICK))
		वापस 0;

	चयन (size) अणु
	हाल SCH_BYTE:
	हाल SCH_BYTE_DATA:
		data->byte = inb(SMBHSTDAT0);
		अवरोध;
	हाल SCH_WORD_DATA:
		data->word = inb(SMBHSTDAT0) + (inb(SMBHSTDAT1) << 8);
		अवरोध;
	हाल SCH_BLOCK_DATA:
		data->block[0] = inb(SMBHSTDAT0);
		अगर (data->block[0] == 0 || data->block[0] > I2C_SMBUS_BLOCK_MAX)
			वापस -EPROTO;
		क्रम (i = 1; i <= data->block[0]; i++)
			data->block[i] = inb(SMBBLKDAT+i-1);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 sch_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_BLOCK_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= sch_access,
	.functionality	= sch_func,
पूर्ण;

अटल काष्ठा i2c_adapter sch_adapter = अणु
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
पूर्ण;

अटल पूर्णांक smbus_sch_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा resource *res;
	पूर्णांक retval;

	res = platक्रमm_get_resource(dev, IORESOURCE_IO, 0);
	अगर (!res)
		वापस -EBUSY;

	अगर (!devm_request_region(&dev->dev, res->start, resource_size(res),
				 dev->name)) अणु
		dev_err(&dev->dev, "SMBus region 0x%x already in use!\n",
			sch_smba);
		वापस -EBUSY;
	पूर्ण

	sch_smba = res->start;

	dev_dbg(&dev->dev, "SMBA = 0x%X\n", sch_smba);

	/* set up the sysfs linkage to our parent device */
	sch_adapter.dev.parent = &dev->dev;

	snम_लिखो(sch_adapter.name, माप(sch_adapter.name),
		"SMBus SCH adapter at %04x", sch_smba);

	retval = i2c_add_adapter(&sch_adapter);
	अगर (retval)
		sch_smba = 0;

	वापस retval;
पूर्ण

अटल पूर्णांक smbus_sch_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (sch_smba) अणु
		i2c_del_adapter(&sch_adapter);
		sch_smba = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver smbus_sch_driver = अणु
	.driver = अणु
		.name = "isch_smbus",
	पूर्ण,
	.probe		= smbus_sch_probe,
	.हटाओ		= smbus_sch_हटाओ,
पूर्ण;

module_platक्रमm_driver(smbus_sch_driver);

MODULE_AUTHOR("Jacob Pan <jacob.jun.pan@intel.com>");
MODULE_DESCRIPTION("Intel SCH SMBus driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:isch_smbus");
