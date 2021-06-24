<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SMBus 2.0 driver क्रम AMD-8111 IO-Hub.
 *
 * Copyright (c) 2002 Vojtech Pavlik
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ioport.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

MODULE_LICENSE("GPL");
MODULE_AUTHOR ("Vojtech Pavlik <vojtech@suse.cz>");
MODULE_DESCRIPTION("AMD8111 SMBus 2.0 driver");

काष्ठा amd_smbus अणु
	काष्ठा pci_dev *dev;
	काष्ठा i2c_adapter adapter;
	पूर्णांक base;
	पूर्णांक size;
पूर्ण;

अटल काष्ठा pci_driver amd8111_driver;

/*
 * AMD PCI control रेजिस्टरs definitions.
 */

#घोषणा AMD_PCI_MISC	0x48

#घोषणा AMD_PCI_MISC_SCI	0x04	/* deliver SCI */
#घोषणा AMD_PCI_MISC_INT	0x02	/* deliver PCI IRQ */
#घोषणा AMD_PCI_MISC_SPEEDUP	0x01	/* 16x घड़ी speedup */

/*
 * ACPI 2.0 chapter 13 PCI पूर्णांकerface definitions.
 */

#घोषणा AMD_EC_DATA	0x00	/* data रेजिस्टर */
#घोषणा AMD_EC_SC	0x04	/* status of controller */
#घोषणा AMD_EC_CMD	0x04	/* command रेजिस्टर */
#घोषणा AMD_EC_ICR	0x08	/* पूर्णांकerrupt control रेजिस्टर */

#घोषणा AMD_EC_SC_SMI	0x04	/* smi event pending */
#घोषणा AMD_EC_SC_SCI	0x02	/* sci event pending */
#घोषणा AMD_EC_SC_BURST	0x01	/* burst mode enabled */
#घोषणा AMD_EC_SC_CMD	0x08	/* byte in data reg is command */
#घोषणा AMD_EC_SC_IBF	0x02	/* data पढ़ोy क्रम embedded controller */
#घोषणा AMD_EC_SC_OBF	0x01	/* data पढ़ोy क्रम host */

#घोषणा AMD_EC_CMD_RD	0x80	/* पढ़ो EC */
#घोषणा AMD_EC_CMD_WR	0x81	/* ग_लिखो EC */
#घोषणा AMD_EC_CMD_BE	0x82	/* enable burst mode */
#घोषणा AMD_EC_CMD_BD	0x83	/* disable burst mode */
#घोषणा AMD_EC_CMD_QR	0x84	/* query EC */

/*
 * ACPI 2.0 chapter 13 access of रेजिस्टरs of the EC
 */

अटल पूर्णांक amd_ec_रुको_ग_लिखो(काष्ठा amd_smbus *smbus)
अणु
	पूर्णांक समयout = 500;

	जबतक ((inb(smbus->base + AMD_EC_SC) & AMD_EC_SC_IBF) && --समयout)
		udelay(1);

	अगर (!समयout) अणु
		dev_warn(&smbus->dev->dev,
			 "Timeout while waiting for IBF to clear\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ec_रुको_पढ़ो(काष्ठा amd_smbus *smbus)
अणु
	पूर्णांक समयout = 500;

	जबतक ((~inb(smbus->base + AMD_EC_SC) & AMD_EC_SC_OBF) && --समयout)
		udelay(1);

	अगर (!समयout) अणु
		dev_warn(&smbus->dev->dev,
			 "Timeout while waiting for OBF to set\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ec_पढ़ो(काष्ठा amd_smbus *smbus, अचिन्हित अक्षर address,
		अचिन्हित अक्षर *data)
अणु
	पूर्णांक status;

	status = amd_ec_रुको_ग_लिखो(smbus);
	अगर (status)
		वापस status;
	outb(AMD_EC_CMD_RD, smbus->base + AMD_EC_CMD);

	status = amd_ec_रुको_ग_लिखो(smbus);
	अगर (status)
		वापस status;
	outb(address, smbus->base + AMD_EC_DATA);

	status = amd_ec_रुको_पढ़ो(smbus);
	अगर (status)
		वापस status;
	*data = inb(smbus->base + AMD_EC_DATA);

	वापस 0;
पूर्ण

अटल पूर्णांक amd_ec_ग_लिखो(काष्ठा amd_smbus *smbus, अचिन्हित अक्षर address,
		अचिन्हित अक्षर data)
अणु
	पूर्णांक status;

	status = amd_ec_रुको_ग_लिखो(smbus);
	अगर (status)
		वापस status;
	outb(AMD_EC_CMD_WR, smbus->base + AMD_EC_CMD);

	status = amd_ec_रुको_ग_लिखो(smbus);
	अगर (status)
		वापस status;
	outb(address, smbus->base + AMD_EC_DATA);

	status = amd_ec_रुको_ग_लिखो(smbus);
	अगर (status)
		वापस status;
	outb(data, smbus->base + AMD_EC_DATA);

	वापस 0;
पूर्ण

/*
 * ACPI 2.0 chapter 13 SMBus 2.0 EC रेजिस्टर model
 */

#घोषणा AMD_SMB_PRTCL	0x00	/* protocol, PEC */
#घोषणा AMD_SMB_STS	0x01	/* status */
#घोषणा AMD_SMB_ADDR	0x02	/* address */
#घोषणा AMD_SMB_CMD	0x03	/* command */
#घोषणा AMD_SMB_DATA	0x04	/* 32 data रेजिस्टरs */
#घोषणा AMD_SMB_BCNT	0x24	/* number of data bytes */
#घोषणा AMD_SMB_ALRM_A	0x25	/* alarm address */
#घोषणा AMD_SMB_ALRM_D	0x26	/* 2 bytes alarm data */

#घोषणा AMD_SMB_STS_DONE	0x80
#घोषणा AMD_SMB_STS_ALRM	0x40
#घोषणा AMD_SMB_STS_RES		0x20
#घोषणा AMD_SMB_STS_STATUS	0x1f

#घोषणा AMD_SMB_STATUS_OK	0x00
#घोषणा AMD_SMB_STATUS_FAIL	0x07
#घोषणा AMD_SMB_STATUS_DNAK	0x10
#घोषणा AMD_SMB_STATUS_DERR	0x11
#घोषणा AMD_SMB_STATUS_CMD_DENY	0x12
#घोषणा AMD_SMB_STATUS_UNKNOWN	0x13
#घोषणा AMD_SMB_STATUS_ACC_DENY	0x17
#घोषणा AMD_SMB_STATUS_TIMEOUT	0x18
#घोषणा AMD_SMB_STATUS_NOTSUP	0x19
#घोषणा AMD_SMB_STATUS_BUSY	0x1A
#घोषणा AMD_SMB_STATUS_PEC	0x1F

#घोषणा AMD_SMB_PRTCL_WRITE		0x00
#घोषणा AMD_SMB_PRTCL_READ		0x01
#घोषणा AMD_SMB_PRTCL_QUICK		0x02
#घोषणा AMD_SMB_PRTCL_BYTE		0x04
#घोषणा AMD_SMB_PRTCL_BYTE_DATA		0x06
#घोषणा AMD_SMB_PRTCL_WORD_DATA		0x08
#घोषणा AMD_SMB_PRTCL_BLOCK_DATA	0x0a
#घोषणा AMD_SMB_PRTCL_PROC_CALL		0x0c
#घोषणा AMD_SMB_PRTCL_BLOCK_PROC_CALL	0x0d
#घोषणा AMD_SMB_PRTCL_I2C_BLOCK_DATA	0x4a
#घोषणा AMD_SMB_PRTCL_PEC		0x80


अटल s32 amd8111_access(काष्ठा i2c_adapter *adap, u16 addr,
		अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक size,
		जोड़ i2c_smbus_data *data)
अणु
	काष्ठा amd_smbus *smbus = adap->algo_data;
	अचिन्हित अक्षर protocol, len, pec, temp[2];
	पूर्णांक i, status;

	protocol = (पढ़ो_ग_लिखो == I2C_SMBUS_READ) ? AMD_SMB_PRTCL_READ
						  : AMD_SMB_PRTCL_WRITE;
	pec = (flags & I2C_CLIENT_PEC) ? AMD_SMB_PRTCL_PEC : 0;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		protocol |= AMD_SMB_PRTCL_QUICK;
		पढ़ो_ग_लिखो = I2C_SMBUS_WRITE;
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			status = amd_ec_ग_लिखो(smbus, AMD_SMB_CMD,
						command);
			अगर (status)
				वापस status;
		पूर्ण
		protocol |= AMD_SMB_PRTCL_BYTE;
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_CMD, command);
		अगर (status)
			वापस status;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			status = amd_ec_ग_लिखो(smbus, AMD_SMB_DATA,
						data->byte);
			अगर (status)
				वापस status;
		पूर्ण
		protocol |= AMD_SMB_PRTCL_BYTE_DATA;
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_CMD, command);
		अगर (status)
			वापस status;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			status = amd_ec_ग_लिखो(smbus, AMD_SMB_DATA,
						data->word & 0xff);
			अगर (status)
				वापस status;
			status = amd_ec_ग_लिखो(smbus, AMD_SMB_DATA + 1,
						data->word >> 8);
			अगर (status)
				वापस status;
		पूर्ण
		protocol |= AMD_SMB_PRTCL_WORD_DATA | pec;
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_CMD, command);
		अगर (status)
			वापस status;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = min_t(u8, data->block[0],
					I2C_SMBUS_BLOCK_MAX);
			status = amd_ec_ग_लिखो(smbus, AMD_SMB_BCNT, len);
			अगर (status)
				वापस status;
			क्रम (i = 0; i < len; i++) अणु
				status =
					amd_ec_ग_लिखो(smbus, AMD_SMB_DATA + i,
						data->block[i + 1]);
				अगर (status)
					वापस status;
			पूर्ण
		पूर्ण
		protocol |= AMD_SMB_PRTCL_BLOCK_DATA | pec;
		अवरोध;

	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		len = min_t(u8, data->block[0],
				I2C_SMBUS_BLOCK_MAX);
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_CMD, command);
		अगर (status)
			वापस status;
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_BCNT, len);
		अगर (status)
			वापस status;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			क्रम (i = 0; i < len; i++) अणु
				status =
					amd_ec_ग_लिखो(smbus, AMD_SMB_DATA + i,
						data->block[i + 1]);
				अगर (status)
					वापस status;
			पूर्ण
		protocol |= AMD_SMB_PRTCL_I2C_BLOCK_DATA;
		अवरोध;

	हाल I2C_SMBUS_PROC_CALL:
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_CMD, command);
		अगर (status)
			वापस status;
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_DATA,
					data->word & 0xff);
		अगर (status)
			वापस status;
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_DATA + 1,
					data->word >> 8);
		अगर (status)
			वापस status;
		protocol = AMD_SMB_PRTCL_PROC_CALL | pec;
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		अवरोध;

	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		len = min_t(u8, data->block[0],
				I2C_SMBUS_BLOCK_MAX - 1);
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_CMD, command);
		अगर (status)
			वापस status;
		status = amd_ec_ग_लिखो(smbus, AMD_SMB_BCNT, len);
		अगर (status)
			वापस status;
		क्रम (i = 0; i < len; i++) अणु
			status = amd_ec_ग_लिखो(smbus, AMD_SMB_DATA + i,
						data->block[i + 1]);
			अगर (status)
				वापस status;
		पूर्ण
		protocol = AMD_SMB_PRTCL_BLOCK_PROC_CALL | pec;
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		अवरोध;

	शेष:
		dev_warn(&adap->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	status = amd_ec_ग_लिखो(smbus, AMD_SMB_ADDR, addr << 1);
	अगर (status)
		वापस status;
	status = amd_ec_ग_लिखो(smbus, AMD_SMB_PRTCL, protocol);
	अगर (status)
		वापस status;

	status = amd_ec_पढ़ो(smbus, AMD_SMB_STS, temp + 0);
	अगर (status)
		वापस status;

	अगर (~temp[0] & AMD_SMB_STS_DONE) अणु
		udelay(500);
		status = amd_ec_पढ़ो(smbus, AMD_SMB_STS, temp + 0);
		अगर (status)
			वापस status;
	पूर्ण

	अगर (~temp[0] & AMD_SMB_STS_DONE) अणु
		msleep(1);
		status = amd_ec_पढ़ो(smbus, AMD_SMB_STS, temp + 0);
		अगर (status)
			वापस status;
	पूर्ण

	अगर ((~temp[0] & AMD_SMB_STS_DONE) || (temp[0] & AMD_SMB_STS_STATUS))
		वापस -EIO;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
		वापस 0;

	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
	हाल I2C_SMBUS_BYTE_DATA:
		status = amd_ec_पढ़ो(smbus, AMD_SMB_DATA, &data->byte);
		अगर (status)
			वापस status;
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
	हाल I2C_SMBUS_PROC_CALL:
		status = amd_ec_पढ़ो(smbus, AMD_SMB_DATA, temp + 0);
		अगर (status)
			वापस status;
		status = amd_ec_पढ़ो(smbus, AMD_SMB_DATA + 1, temp + 1);
		अगर (status)
			वापस status;
		data->word = (temp[1] << 8) | temp[0];
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		status = amd_ec_पढ़ो(smbus, AMD_SMB_BCNT, &len);
		अगर (status)
			वापस status;
		len = min_t(u8, len, I2C_SMBUS_BLOCK_MAX);
		fallthrough;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		क्रम (i = 0; i < len; i++) अणु
			status = amd_ec_पढ़ो(smbus, AMD_SMB_DATA + i,
						data->block + i + 1);
			अगर (status)
				वापस status;
		पूर्ण
		data->block[0] = len;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


अटल u32 amd8111_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस	I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_BLOCK_DATA |
		I2C_FUNC_SMBUS_PROC_CALL | I2C_FUNC_SMBUS_BLOCK_PROC_CALL |
		I2C_FUNC_SMBUS_I2C_BLOCK | I2C_FUNC_SMBUS_PEC;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer = amd8111_access,
	.functionality = amd8111_func,
पूर्ण;


अटल स्थिर काष्ठा pci_device_id amd8111_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8111_SMBUS2) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, amd8111_ids);

अटल पूर्णांक amd8111_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा amd_smbus *smbus;
	पूर्णांक error;

	अगर (!(pci_resource_flags(dev, 0) & IORESOURCE_IO))
		वापस -ENODEV;

	smbus = kzalloc(माप(काष्ठा amd_smbus), GFP_KERNEL);
	अगर (!smbus)
		वापस -ENOMEM;

	smbus->dev = dev;
	smbus->base = pci_resource_start(dev, 0);
	smbus->size = pci_resource_len(dev, 0);

	error = acpi_check_resource_conflict(&dev->resource[0]);
	अगर (error) अणु
		error = -ENODEV;
		जाओ out_kमुक्त;
	पूर्ण

	अगर (!request_region(smbus->base, smbus->size, amd8111_driver.name)) अणु
		error = -EBUSY;
		जाओ out_kमुक्त;
	पूर्ण

	smbus->adapter.owner = THIS_MODULE;
	snम_लिखो(smbus->adapter.name, माप(smbus->adapter.name),
		"SMBus2 AMD8111 adapter at %04x", smbus->base);
	smbus->adapter.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	smbus->adapter.algo = &smbus_algorithm;
	smbus->adapter.algo_data = smbus;

	/* set up the sysfs linkage to our parent device */
	smbus->adapter.dev.parent = &dev->dev;

	pci_ग_लिखो_config_dword(smbus->dev, AMD_PCI_MISC, 0);
	error = i2c_add_adapter(&smbus->adapter);
	अगर (error)
		जाओ out_release_region;

	pci_set_drvdata(dev, smbus);
	वापस 0;

 out_release_region:
	release_region(smbus->base, smbus->size);
 out_kमुक्त:
	kमुक्त(smbus);
	वापस error;
पूर्ण

अटल व्योम amd8111_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा amd_smbus *smbus = pci_get_drvdata(dev);

	i2c_del_adapter(&smbus->adapter);
	release_region(smbus->base, smbus->size);
	kमुक्त(smbus);
पूर्ण

अटल काष्ठा pci_driver amd8111_driver = अणु
	.name		= "amd8111_smbus2",
	.id_table	= amd8111_ids,
	.probe		= amd8111_probe,
	.हटाओ		= amd8111_हटाओ,
पूर्ण;

module_pci_driver(amd8111_driver);
