<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * KPC2000 i2c driver
 *
 * Adapted i2c-i801.c क्रम use with Kaकरोka hardware.
 *
 * Copyright (C) 1998 - 2002
 *	Froकरो Looijaard <froकरोl@dds.nl>,
 *	Philip Edelbrock <phil@netroedge.com>,
 *	Mark D. Studebaker <mdsxyz123@yahoo.com>
 * Copyright (C) 2007 - 2012
 *	Jean Delvare <khali@linux-fr.org>
 * Copyright (C) 2010 Intel Corporation
 *	David Woodhouse <dwmw2@infradead.org>
 * Copyright (C) 2014-2018 Daktronics
 *	Matt Sickler <matt.sickler@daktronics.com>,
 *	Jorकरोn Hofer <jorकरोn.hofer@daktronics.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश "kpc.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matt.Sickler@Daktronics.com");

काष्ठा kpc_i2c अणु
	अचिन्हित दीर्घ           smba;
	काष्ठा i2c_adapter      adapter;
	अचिन्हित पूर्णांक            features;
पूर्ण;

/*****************************
 *** Part 1 - i2c Handlers ***
 *****************************/

#घोषणा REG_SIZE 8

/* I801 SMBus address offsets */
#घोषणा SMBHSTSTS(p)    ((0  * REG_SIZE) + (p)->smba)
#घोषणा SMBHSTCNT(p)    ((2  * REG_SIZE) + (p)->smba)
#घोषणा SMBHSTCMD(p)    ((3  * REG_SIZE) + (p)->smba)
#घोषणा SMBHSTADD(p)    ((4  * REG_SIZE) + (p)->smba)
#घोषणा SMBHSTDAT0(p)   ((5  * REG_SIZE) + (p)->smba)
#घोषणा SMBHSTDAT1(p)   ((6  * REG_SIZE) + (p)->smba)
#घोषणा SMBBLKDAT(p)    ((7  * REG_SIZE) + (p)->smba)
#घोषणा SMBPEC(p)       ((8  * REG_SIZE) + (p)->smba)   /* ICH3 and later */
#घोषणा SMBAUXSTS(p)    ((12 * REG_SIZE) + (p)->smba)   /* ICH4 and later */
#घोषणा SMBAUXCTL(p)    ((13 * REG_SIZE) + (p)->smba)   /* ICH4 and later */

/* PCI Address Constants */
#घोषणा SMBBAR      4
#घोषणा SMBHSTCFG   0x040

/* Host configuration bits क्रम SMBHSTCFG */
#घोषणा SMBHSTCFG_HST_EN        1
#घोषणा SMBHSTCFG_SMB_SMI_EN    2
#घोषणा SMBHSTCFG_I2C_EN        4

/* Auxiliary control रेजिस्टर bits, ICH4+ only */
#घोषणा SMBAUXCTL_CRC       1
#घोषणा SMBAUXCTL_E32B      2

/* समाप्त bit क्रम SMBHSTCNT */
#घोषणा SMBHSTCNT_KILL      2

/* Other settings */
#घोषणा MAX_RETRIES         400
#घोषणा ENABLE_INT9         0       /* set to 0x01 to enable - untested */

/* I801 command स्थिरants */
#घोषणा I801_QUICK              0x00
#घोषणा I801_BYTE               0x04
#घोषणा I801_BYTE_DATA          0x08
#घोषणा I801_WORD_DATA          0x0C
#घोषणा I801_PROC_CALL          0x10    /* unimplemented */
#घोषणा I801_BLOCK_DATA         0x14
#घोषणा I801_I2C_BLOCK_DATA     0x18    /* ICH5 and later */
#घोषणा I801_BLOCK_LAST         0x34
#घोषणा I801_I2C_BLOCK_LAST     0x38    /* ICH5 and later */
#घोषणा I801_START              0x40
#घोषणा I801_PEC_EN             0x80    /* ICH3 and later */

/* I801 Hosts Status रेजिस्टर bits */
#घोषणा SMBHSTSTS_BYTE_DONE     0x80
#घोषणा SMBHSTSTS_INUSE_STS     0x40
#घोषणा SMBHSTSTS_SMBALERT_STS  0x20
#घोषणा SMBHSTSTS_FAILED        0x10
#घोषणा SMBHSTSTS_BUS_ERR       0x08
#घोषणा SMBHSTSTS_DEV_ERR       0x04
#घोषणा SMBHSTSTS_INTR          0x02
#घोषणा SMBHSTSTS_HOST_BUSY     0x01

#घोषणा STATUS_FLAGS	(SMBHSTSTS_BYTE_DONE | SMBHSTSTS_FAILED | \
			 SMBHSTSTS_BUS_ERR | SMBHSTSTS_DEV_ERR | SMBHSTSTS_INTR)

/* Older devices have their ID defined in <linux/pci_ids.h> */
#घोषणा PCI_DEVICE_ID_INTEL_COUGARPOINT_SMBUS       0x1c22
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS          0x1d22
/* Patsburg also has three 'Integrated Device Function' SMBus controllers */
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF0     0x1d70
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF1     0x1d71
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF2     0x1d72
#घोषणा PCI_DEVICE_ID_INTEL_PANTHERPOINT_SMBUS      0x1e22
#घोषणा PCI_DEVICE_ID_INTEL_DH89XXCC_SMBUS          0x2330
#घोषणा PCI_DEVICE_ID_INTEL_5_3400_SERIES_SMBUS     0x3b30
#घोषणा PCI_DEVICE_ID_INTEL_LYNXPOINT_SMBUS         0x8c22
#घोषणा PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_SMBUS      0x9c22

#घोषणा FEATURE_SMBUS_PEC       BIT(0)
#घोषणा FEATURE_BLOCK_BUFFER    BIT(1)
#घोषणा FEATURE_BLOCK_PROC      BIT(2)
#घोषणा FEATURE_I2C_BLOCK_READ  BIT(3)
/* Not really a feature, but it's convenient to handle it as such */
#घोषणा FEATURE_IDF             BIT(15)

// FIXME!
#अघोषित inb_p
#घोषणा inb_p(a) पढ़ोq((व्योम __iomem *)a)
#अघोषित outb_p
#घोषणा outb_p(d, a) ग_लिखोq(d, (व्योम __iomem *)a)

/* Make sure the SMBus host is पढ़ोy to start transmitting.
 * Return 0 अगर it is, -EBUSY अगर it is not.
 */
अटल पूर्णांक i801_check_pre(काष्ठा kpc_i2c *priv)
अणु
	पूर्णांक status;

	status = inb_p(SMBHSTSTS(priv));
	अगर (status & SMBHSTSTS_HOST_BUSY) अणु
		dev_err(&priv->adapter.dev,
			"SMBus is busy, can't use it! (status=%x)\n", status);
		वापस -EBUSY;
	पूर्ण

	status &= STATUS_FLAGS;
	अगर (status) अणु
		outb_p(status, SMBHSTSTS(priv));
		status = inb_p(SMBHSTSTS(priv)) & STATUS_FLAGS;
		अगर (status) अणु
			dev_err(&priv->adapter.dev,
				"Failed clearing status flags (%02x)\n", status);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Convert the status रेजिस्टर to an error code, and clear it. */
अटल पूर्णांक i801_check_post(काष्ठा kpc_i2c *priv, पूर्णांक status, पूर्णांक समयout)
अणु
	पूर्णांक result = 0;

	/* If the SMBus is still busy, we give up */
	अगर (समयout) अणु
		dev_err(&priv->adapter.dev, "Transaction timeout\n");
		/* try to stop the current command */
		dev_dbg(&priv->adapter.dev,
			"Terminating the current operation\n");
		outb_p(inb_p(SMBHSTCNT(priv)) | SMBHSTCNT_KILL,
		       SMBHSTCNT(priv));
		usleep_range(1000, 2000);
		outb_p(inb_p(SMBHSTCNT(priv)) & (~SMBHSTCNT_KILL),
		       SMBHSTCNT(priv));

		/* Check अगर it worked */
		status = inb_p(SMBHSTSTS(priv));
		अगर ((status & SMBHSTSTS_HOST_BUSY) ||
		    !(status & SMBHSTSTS_FAILED))
			dev_err(&priv->adapter.dev,
				"Failed terminating the transaction\n");
		outb_p(STATUS_FLAGS, SMBHSTSTS(priv));
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (status & SMBHSTSTS_FAILED) अणु
		result = -EIO;
		dev_err(&priv->adapter.dev, "Transaction failed\n");
	पूर्ण
	अगर (status & SMBHSTSTS_DEV_ERR) अणु
		result = -ENXIO;
		dev_dbg(&priv->adapter.dev, "No response\n");
	पूर्ण
	अगर (status & SMBHSTSTS_BUS_ERR) अणु
		result = -EAGAIN;
		dev_dbg(&priv->adapter.dev, "Lost arbitration\n");
	पूर्ण

	अगर (result) अणु
		/* Clear error flags */
		outb_p(status & STATUS_FLAGS, SMBHSTSTS(priv));
		status = inb_p(SMBHSTSTS(priv)) & STATUS_FLAGS;
		अगर (status)
			dev_warn(&priv->adapter.dev,
				 "Failed clearing status flags at end of transaction (%02x)\n",
				 status);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक i801_transaction(काष्ठा kpc_i2c *priv, पूर्णांक xact)
अणु
	पूर्णांक status;
	पूर्णांक result;
	पूर्णांक समयout = 0;

	result = i801_check_pre(priv);
	अगर (result < 0)
		वापस result;
	/* the current contents of SMBHSTCNT can be overwritten, since PEC,
	 * INTREN, SMBSCMD are passed in xact
	 */
	outb_p(xact | I801_START, SMBHSTCNT(priv));

	/* We will always रुको क्रम a fraction of a second! */
	करो अणु
		usleep_range(250, 500);
		status = inb_p(SMBHSTSTS(priv));
	पूर्ण जबतक ((status & SMBHSTSTS_HOST_BUSY) && (समयout++ < MAX_RETRIES));

	result = i801_check_post(priv, status, समयout > MAX_RETRIES);
	अगर (result < 0)
		वापस result;

	outb_p(SMBHSTSTS_INTR, SMBHSTSTS(priv));
	वापस 0;
पूर्ण

/* रुको क्रम INTR bit as advised by Intel */
अटल व्योम i801_रुको_hwpec(काष्ठा kpc_i2c *priv)
अणु
	पूर्णांक समयout = 0;
	पूर्णांक status;

	करो अणु
		usleep_range(250, 500);
		status = inb_p(SMBHSTSTS(priv));
	पूर्ण जबतक ((!(status & SMBHSTSTS_INTR)) && (समयout++ < MAX_RETRIES));

	अगर (समयout > MAX_RETRIES)
		dev_dbg(&priv->adapter.dev, "PEC Timeout!\n");

	outb_p(status, SMBHSTSTS(priv));
पूर्ण

अटल पूर्णांक i801_block_transaction_by_block(काष्ठा kpc_i2c *priv,
					   जोड़ i2c_smbus_data *data,
					   अक्षर पढ़ो_ग_लिखो, पूर्णांक hwpec)
अणु
	पूर्णांक i, len;
	पूर्णांक status;

	inb_p(SMBHSTCNT(priv)); /* reset the data buffer index */

	/* Use 32-byte buffer to process this transaction */
	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		len = data->block[0];
		outb_p(len, SMBHSTDAT0(priv));
		क्रम (i = 0; i < len; i++)
			outb_p(data->block[i + 1], SMBBLKDAT(priv));
	पूर्ण

	status = i801_transaction(priv,
				  I801_BLOCK_DATA | ENABLE_INT9 | I801_PEC_EN * hwpec);
	अगर (status)
		वापस status;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
		len = inb_p(SMBHSTDAT0(priv));
		अगर (len < 1 || len > I2C_SMBUS_BLOCK_MAX)
			वापस -EPROTO;

		data->block[0] = len;
		क्रम (i = 0; i < len; i++)
			data->block[i + 1] = inb_p(SMBBLKDAT(priv));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i801_block_transaction_byte_by_byte(काष्ठा kpc_i2c *priv,
					       जोड़ i2c_smbus_data *data,
					       अक्षर पढ़ो_ग_लिखो, पूर्णांक command,
					       पूर्णांक hwpec)
अणु
	पूर्णांक i, len;
	पूर्णांक smbcmd;
	पूर्णांक status;
	पूर्णांक result;
	पूर्णांक समयout;

	result = i801_check_pre(priv);
	अगर (result < 0)
		वापस result;

	len = data->block[0];

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		outb_p(len, SMBHSTDAT0(priv));
		outb_p(data->block[1], SMBBLKDAT(priv));
	पूर्ण

	क्रम (i = 1; i <= len; i++) अणु
		अगर (i == len && पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			अगर (command == I2C_SMBUS_I2C_BLOCK_DATA)
				smbcmd = I801_I2C_BLOCK_LAST;
			अन्यथा
				smbcmd = I801_BLOCK_LAST;
		पूर्ण अन्यथा अणु
			अगर (command == I2C_SMBUS_I2C_BLOCK_DATA &&
			    पढ़ो_ग_लिखो == I2C_SMBUS_READ)
				smbcmd = I801_I2C_BLOCK_DATA;
			अन्यथा
				smbcmd = I801_BLOCK_DATA;
		पूर्ण
		outb_p(smbcmd | ENABLE_INT9, SMBHSTCNT(priv));

		अगर (i == 1)
			outb_p(inb(SMBHSTCNT(priv)) | I801_START,
			       SMBHSTCNT(priv));
		/* We will always रुको क्रम a fraction of a second! */
		समयout = 0;
		करो अणु
			usleep_range(250, 500);
			status = inb_p(SMBHSTSTS(priv));
		पूर्ण जबतक (!(status & SMBHSTSTS_BYTE_DONE) &&
			 (समयout++ < MAX_RETRIES));

		result = i801_check_post(priv, status, समयout > MAX_RETRIES);
		अगर (result < 0)
			वापस result;
		अगर (i == 1 && पढ़ो_ग_लिखो == I2C_SMBUS_READ &&
		    command != I2C_SMBUS_I2C_BLOCK_DATA) अणु
			len = inb_p(SMBHSTDAT0(priv));
			अगर (len < 1 || len > I2C_SMBUS_BLOCK_MAX) अणु
				dev_err(&priv->adapter.dev,
					"Illegal SMBus block read size %d\n",
					len);
				/* Recover */
				जबतक (inb_p(SMBHSTSTS(priv)) &
						SMBHSTSTS_HOST_BUSY)
					outb_p(SMBHSTSTS_BYTE_DONE,
					       SMBHSTSTS(priv));
				outb_p(SMBHSTSTS_INTR,
				       SMBHSTSTS(priv));
				वापस -EPROTO;
			पूर्ण
			data->block[0] = len;
		पूर्ण

		/* Retrieve/store value in SMBBLKDAT */
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			data->block[i] = inb_p(SMBBLKDAT(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE && i + 1 <= len)
			outb_p(data->block[i + 1], SMBBLKDAT(priv));
		/* संकेतs SMBBLKDAT पढ़ोy */
		outb_p(SMBHSTSTS_BYTE_DONE | SMBHSTSTS_INTR, SMBHSTSTS(priv));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i801_set_block_buffer_mode(काष्ठा kpc_i2c *priv)
अणु
	outb_p(inb_p(SMBAUXCTL(priv)) | SMBAUXCTL_E32B, SMBAUXCTL(priv));
	अगर ((inb_p(SMBAUXCTL(priv)) & SMBAUXCTL_E32B) == 0)
		वापस -EIO;
	वापस 0;
पूर्ण

/* Block transaction function */
अटल पूर्णांक i801_block_transaction(काष्ठा kpc_i2c *priv,
				  जोड़ i2c_smbus_data *data, अक्षर पढ़ो_ग_लिखो,
				  पूर्णांक command, पूर्णांक hwpec)
अणु
	पूर्णांक result = 0;
	//अचिन्हित अक्षर hostc;

	अगर (command == I2C_SMBUS_I2C_BLOCK_DATA) अणु
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			/* set I2C_EN bit in configuration रेजिस्टर */
			//TODO: Figure out the right thing to करो here...
			//pci_पढ़ो_config_byte(priv->pci_dev, SMBHSTCFG, &hostc);
			//pci_ग_लिखो_config_byte(priv->pci_dev, SMBHSTCFG, hostc | SMBHSTCFG_I2C_EN);
		पूर्ण अन्यथा अगर (!(priv->features & FEATURE_I2C_BLOCK_READ)) अणु
			dev_err(&priv->adapter.dev,
				"I2C block read is unsupported!\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE ||
	    command == I2C_SMBUS_I2C_BLOCK_DATA) अणु
		अगर (data->block[0] < 1)
			data->block[0] = 1;
		अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX)
			data->block[0] = I2C_SMBUS_BLOCK_MAX;
	पूर्ण अन्यथा अणु
		data->block[0] = 32;	/* max क्रम SMBus block पढ़ोs */
	पूर्ण

	/* Experience has shown that the block buffer can only be used क्रम
	 * SMBus (not I2C) block transactions, even though the datasheet
	 * करोesn't mention this limitation.
	 */
	अगर ((priv->features & FEATURE_BLOCK_BUFFER) &&
	    command != I2C_SMBUS_I2C_BLOCK_DATA &&
	    i801_set_block_buffer_mode(priv) == 0) अणु
		result = i801_block_transaction_by_block(priv, data,
							 पढ़ो_ग_लिखो, hwpec);
	पूर्ण अन्यथा अणु
		result = i801_block_transaction_byte_by_byte(priv, data,
							     पढ़ो_ग_लिखो,
							     command, hwpec);
	पूर्ण

	अगर (result == 0 && hwpec)
		i801_रुको_hwpec(priv);
	अगर (command == I2C_SMBUS_I2C_BLOCK_DATA &&
	    पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		/* restore saved configuration रेजिस्टर value */
		//TODO: Figure out the right thing to करो here...
		//pci_ग_लिखो_config_byte(priv->pci_dev, SMBHSTCFG, hostc);
	पूर्ण
	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 i801_access(काष्ठा i2c_adapter *adap, u16 addr,
		       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		       पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक hwpec;
	पूर्णांक block = 0;
	पूर्णांक ret, xact = 0;
	काष्ठा kpc_i2c *priv = i2c_get_adapdata(adap);

	hwpec = (priv->features & FEATURE_SMBUS_PEC) &&
		(flags & I2C_CLIENT_PEC) &&
		size != I2C_SMBUS_QUICK && size != I2C_SMBUS_I2C_BLOCK_DATA;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_QUICK\n");
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));

		xact = I801_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_BYTE\n");

		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD(priv));
		xact = I801_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_BYTE_DATA\n");
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));

		outb_p(command, SMBHSTCMD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0(priv));
		xact = I801_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_WORD_DATA\n");
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));

		outb_p(command, SMBHSTCMD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb_p(data->word & 0xff, SMBHSTDAT0(priv));
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1(priv));
		पूर्ण
		xact = I801_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_BLOCK_DATA\n");
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));

		outb_p(command, SMBHSTCMD(priv));
		block = 1;
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] SMBUS_I2C_BLOCK_DATA\n");
		/* NB: page 240 of ICH5 datasheet shows that the R/#W
		 * bit should be cleared here, even when पढ़ोing
		 */
		outb_p((addr & 0x7f) << 1, SMBHSTADD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			/* NB: page 240 of ICH5 datasheet also shows
			 * that DATA1 is the cmd field when पढ़ोing
			 */
			outb_p(command, SMBHSTDAT1(priv));
		पूर्ण अन्यथा अणु
			outb_p(command, SMBHSTCMD(priv));
		पूर्ण
		block = 1;
		अवरोध;
	शेष:
		dev_dbg(&priv->adapter.dev,
			"  [acc] Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (hwpec) अणु /* enable/disable hardware PEC */
		dev_dbg(&priv->adapter.dev, "  [acc] hwpec: yes\n");
		outb_p(inb_p(SMBAUXCTL(priv)) | SMBAUXCTL_CRC, SMBAUXCTL(priv));
	पूर्ण अन्यथा अणु
		dev_dbg(&priv->adapter.dev, "  [acc] hwpec: no\n");
		outb_p(inb_p(SMBAUXCTL(priv)) &
				(~SMBAUXCTL_CRC), SMBAUXCTL(priv));
	पूर्ण

	अगर (block) अणु
		dev_dbg(&priv->adapter.dev, "  [acc] block: yes\n");
		ret = i801_block_transaction(priv, data, पढ़ो_ग_लिखो, size,
					     hwpec);
	पूर्ण अन्यथा अणु
		dev_dbg(&priv->adapter.dev, "  [acc] block: no\n");
		ret = i801_transaction(priv, xact | ENABLE_INT9);
	पूर्ण

	/* Some BIOSes करोn't like it when PEC is enabled at reboot or resume
	 * समय, so we क्रमcibly disable it after every transaction. Turn off
	 * E32B क्रम the same reason.
	 */
	अगर (hwpec || block) अणु
		dev_dbg(&priv->adapter.dev, "  [acc] hwpec || block\n");
		outb_p(inb_p(SMBAUXCTL(priv)) & ~(SMBAUXCTL_CRC |
					SMBAUXCTL_E32B), SMBAUXCTL(priv));
	पूर्ण
	अगर (block) अणु
		dev_dbg(&priv->adapter.dev, "  [acc] block\n");
		वापस ret;
	पूर्ण
	अगर (ret) अणु
		dev_dbg(&priv->adapter.dev, "  [acc] ret %d\n", ret);
		वापस ret;
	पूर्ण
	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (xact == I801_QUICK)) अणु
		dev_dbg(&priv->adapter.dev,
			"  [acc] I2C_SMBUS_WRITE || I801_QUICK  -> ret 0\n");
		वापस 0;
	पूर्ण

	चयन (xact & 0x7f) अणु
	हाल I801_BYTE:  /* Result put in SMBHSTDAT0 */
	हाल I801_BYTE_DATA:
		dev_dbg(&priv->adapter.dev,
			"  [acc] I801_BYTE or I801_BYTE_DATA\n");
		data->byte = inb_p(SMBHSTDAT0(priv));
		अवरोध;
	हाल I801_WORD_DATA:
		dev_dbg(&priv->adapter.dev, "  [acc] I801_WORD_DATA\n");
		data->word = inb_p(SMBHSTDAT0(priv)) +
			     (inb_p(SMBHSTDAT1(priv)) << 8);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा enable_flag(x) (x)
#घोषणा disable_flag(x) 0
#घोषणा enable_flag_अगर(x, cond) ((cond) ? (x) : 0)

अटल u32 i801_func(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा kpc_i2c *priv = i2c_get_adapdata(adapter);

	/* original settings
	 * u32 f = I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	 * I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	 * I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_WRITE_I2C_BLOCK |
	 * ((priv->features & FEATURE_SMBUS_PEC) ? I2C_FUNC_SMBUS_PEC : 0) |
	 * ((priv->features & FEATURE_I2C_BLOCK_READ) ?
	 * I2C_FUNC_SMBUS_READ_I2C_BLOCK : 0);
	 */

	// http://lxr.मुक्त-electrons.com/source/include/uapi/linux/i2c.h#L85

	u32 f =
		enable_flag(I2C_FUNC_I2C) | /* 0x00000001(I enabled this one) */
		disable_flag(I2C_FUNC_10BIT_ADDR)             | /* 0x00000002 */
		disable_flag(I2C_FUNC_PROTOCOL_MANGLING)      | /* 0x00000004 */
		enable_flag_अगर(I2C_FUNC_SMBUS_PEC,
			       priv->features & FEATURE_SMBUS_PEC) |
								/* 0x00000008 */
		disable_flag(I2C_FUNC_SMBUS_BLOCK_PROC_CALL)  | /* 0x00008000 */
		enable_flag(I2C_FUNC_SMBUS_QUICK)             | /* 0x00010000 */
		disable_flag(I2C_FUNC_SMBUS_READ_BYTE)	      |	/* 0x00020000 */
		disable_flag(I2C_FUNC_SMBUS_WRITE_BYTE)       |	/* 0x00040000 */
		disable_flag(I2C_FUNC_SMBUS_READ_BYTE_DATA)   |	/* 0x00080000 */
		disable_flag(I2C_FUNC_SMBUS_WRITE_BYTE_DATA)  |	/* 0x00100000 */
		disable_flag(I2C_FUNC_SMBUS_READ_WORD_DATA)   |	/* 0x00200000 */
		disable_flag(I2C_FUNC_SMBUS_WRITE_WORD_DATA)  |	/* 0x00400000 */
		disable_flag(I2C_FUNC_SMBUS_PROC_CALL)        |	/* 0x00800000 */
		disable_flag(I2C_FUNC_SMBUS_READ_BLOCK_DATA)  |	/* 0x01000000 */
		disable_flag(I2C_FUNC_SMBUS_WRITE_BLOCK_DATA) |	/* 0x02000000 */
		enable_flag_अगर(I2C_FUNC_SMBUS_READ_I2C_BLOCK,
			       priv->features & FEATURE_I2C_BLOCK_READ) |
								/* 0x04000000 */
		enable_flag(I2C_FUNC_SMBUS_WRITE_I2C_BLOCK)   |	/* 0x08000000 */

		enable_flag(I2C_FUNC_SMBUS_BYTE) | /* _READ_BYTE  _WRITE_BYTE */
		enable_flag(I2C_FUNC_SMBUS_BYTE_DATA)  | /* _READ_BYTE_DATA
							  * _WRITE_BYTE_DATA
							  */
		enable_flag(I2C_FUNC_SMBUS_WORD_DATA)  | /* _READ_WORD_DATA
							  * _WRITE_WORD_DATA
							  */
		enable_flag(I2C_FUNC_SMBUS_BLOCK_DATA) | /* _READ_BLOCK_DATA
							  * _WRITE_BLOCK_DATA
							  */
		disable_flag(I2C_FUNC_SMBUS_I2C_BLOCK) | /* _READ_I2C_BLOCK
							  * _WRITE_I2C_BLOCK
							  */
		disable_flag(I2C_FUNC_SMBUS_EMUL); /* _QUICK  _BYTE
						    * _BYTE_DATA  _WORD_DATA
						    * _PROC_CALL
						    * _WRITE_BLOCK_DATA
						    * _I2C_BLOCK _PEC
						    */
	वापस f;
पूर्ण

#अघोषित enable_flag
#अघोषित disable_flag
#अघोषित enable_flag_अगर

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer     = i801_access,
	.functionality  = i801_func,
पूर्ण;

/********************************
 *** Part 2 - Driver Handlers ***
 ********************************/
अटल पूर्णांक kpc_i2c_probe(काष्ठा platक्रमm_device *pldev)
अणु
	पूर्णांक err;
	काष्ठा kpc_i2c *priv;
	काष्ठा resource *res;

	priv = devm_kzalloc(&pldev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_adapdata(&priv->adapter, priv);
	priv->adapter.owner = THIS_MODULE;
	priv->adapter.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	priv->adapter.algo = &smbus_algorithm;

	res = platक्रमm_get_resource(pldev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	priv->smba = (अचिन्हित दीर्घ)devm_ioremap(&pldev->dev,
							 res->start,
							 resource_size(res));
	अगर (!priv->smba)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pldev, priv);

	priv->features |= FEATURE_IDF;
	priv->features |= FEATURE_I2C_BLOCK_READ;
	priv->features |= FEATURE_SMBUS_PEC;
	priv->features |= FEATURE_BLOCK_BUFFER;

	//init_MUTEX(&lddata->sem);

	/* set up the sysfs linkage to our parent device */
	priv->adapter.dev.parent = &pldev->dev;

	/* Retry up to 3 बार on lost arbitration */
	priv->adapter.retries = 3;

	snम_लिखो(priv->adapter.name, माप(priv->adapter.name),
		 "Fake SMBus I801 adapter");

	err = i2c_add_adapter(&priv->adapter);
	अगर (err) अणु
		dev_err(&priv->adapter.dev, "Failed to add SMBus adapter\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kpc_i2c_हटाओ(काष्ठा platक्रमm_device *pldev)
अणु
	काष्ठा kpc_i2c *lddev;

	lddev = (काष्ठा kpc_i2c *)platक्रमm_get_drvdata(pldev);

	i2c_del_adapter(&lddev->adapter);

	//TODO: Figure out the right thing to करो here...
	//pci_ग_लिखो_config_byte(dev, SMBHSTCFG, priv->original_hstcfg);
	//pci_release_region(dev, SMBBAR);
	//pci_set_drvdata(dev, शून्य);

	//cdev_del(&lddev->cdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver kpc_i2c_driver = अणु
	.probe      = kpc_i2c_probe,
	.हटाओ     = kpc_i2c_हटाओ,
	.driver     = अणु
		.name   = KP_DRIVER_NAME_I2C,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kpc_i2c_driver);
