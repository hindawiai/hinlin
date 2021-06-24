<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 PA Semi, Inc
 *
 * SMBus host driver क्रम PA Semi PWRficient
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

अटल काष्ठा pci_driver pasemi_smb_driver;

काष्ठा pasemi_smbus अणु
	काष्ठा pci_dev		*dev;
	काष्ठा i2c_adapter	 adapter;
	अचिन्हित दीर्घ		 base;
	पूर्णांक			 size;
पूर्ण;

/* Register offsets */
#घोषणा REG_MTXFIFO	0x00
#घोषणा REG_MRXFIFO	0x04
#घोषणा REG_SMSTA	0x14
#घोषणा REG_CTL		0x1c

/* Register defs */
#घोषणा MTXFIFO_READ	0x00000400
#घोषणा MTXFIFO_STOP	0x00000200
#घोषणा MTXFIFO_START	0x00000100
#घोषणा MTXFIFO_DATA_M	0x000000ff

#घोषणा MRXFIFO_EMPTY	0x00000100
#घोषणा MRXFIFO_DATA_M	0x000000ff

#घोषणा SMSTA_XEN	0x08000000
#घोषणा SMSTA_MTN	0x00200000

#घोषणा CTL_MRR		0x00000400
#घोषणा CTL_MTR		0x00000200
#घोषणा CTL_CLK_M	0x000000ff

#घोषणा CLK_100K_DIV	84
#घोषणा CLK_400K_DIV	21

अटल अंतरभूत व्योम reg_ग_लिखो(काष्ठा pasemi_smbus *smbus, पूर्णांक reg, पूर्णांक val)
अणु
	dev_dbg(&smbus->dev->dev, "smbus write reg %lx val %08x\n",
		smbus->base + reg, val);
	outl(val, smbus->base + reg);
पूर्ण

अटल अंतरभूत पूर्णांक reg_पढ़ो(काष्ठा pasemi_smbus *smbus, पूर्णांक reg)
अणु
	पूर्णांक ret;
	ret = inl(smbus->base + reg);
	dev_dbg(&smbus->dev->dev, "smbus read reg %lx val %08x\n",
		smbus->base + reg, ret);
	वापस ret;
पूर्ण

#घोषणा TXFIFO_WR(smbus, reg)	reg_ग_लिखो((smbus), REG_MTXFIFO, (reg))
#घोषणा RXFIFO_RD(smbus)	reg_पढ़ो((smbus), REG_MRXFIFO)

अटल व्योम pasemi_smb_clear(काष्ठा pasemi_smbus *smbus)
अणु
	अचिन्हित पूर्णांक status;

	status = reg_पढ़ो(smbus, REG_SMSTA);
	reg_ग_लिखो(smbus, REG_SMSTA, status);
पूर्ण

अटल पूर्णांक pasemi_smb_रुकोपढ़ोy(काष्ठा pasemi_smbus *smbus)
अणु
	पूर्णांक समयout = 10;
	अचिन्हित पूर्णांक status;

	status = reg_पढ़ो(smbus, REG_SMSTA);

	जबतक (!(status & SMSTA_XEN) && समयout--) अणु
		msleep(1);
		status = reg_पढ़ो(smbus, REG_SMSTA);
	पूर्ण

	/* Got NACK? */
	अगर (status & SMSTA_MTN)
		वापस -ENXIO;

	अगर (समयout < 0) अणु
		dev_warn(&smbus->dev->dev, "Timeout, status 0x%08x\n", status);
		reg_ग_लिखो(smbus, REG_SMSTA, status);
		वापस -ETIME;
	पूर्ण

	/* Clear XEN */
	reg_ग_लिखो(smbus, REG_SMSTA, SMSTA_XEN);

	वापस 0;
पूर्ण

अटल पूर्णांक pasemi_i2c_xfer_msg(काष्ठा i2c_adapter *adapter,
			       काष्ठा i2c_msg *msg, पूर्णांक stop)
अणु
	काष्ठा pasemi_smbus *smbus = adapter->algo_data;
	पूर्णांक पढ़ो, i, err;
	u32 rd;

	पढ़ो = msg->flags & I2C_M_RD ? 1 : 0;

	TXFIFO_WR(smbus, MTXFIFO_START | i2c_8bit_addr_from_msg(msg));

	अगर (पढ़ो) अणु
		TXFIFO_WR(smbus, msg->len | MTXFIFO_READ |
				 (stop ? MTXFIFO_STOP : 0));

		err = pasemi_smb_रुकोपढ़ोy(smbus);
		अगर (err)
			जाओ reset_out;

		क्रम (i = 0; i < msg->len; i++) अणु
			rd = RXFIFO_RD(smbus);
			अगर (rd & MRXFIFO_EMPTY) अणु
				err = -ENODATA;
				जाओ reset_out;
			पूर्ण
			msg->buf[i] = rd & MRXFIFO_DATA_M;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < msg->len - 1; i++)
			TXFIFO_WR(smbus, msg->buf[i]);

		TXFIFO_WR(smbus, msg->buf[msg->len-1] |
			  (stop ? MTXFIFO_STOP : 0));
	पूर्ण

	वापस 0;

 reset_out:
	reg_ग_लिखो(smbus, REG_CTL, (CTL_MTR | CTL_MRR |
		  (CLK_100K_DIV & CTL_CLK_M)));
	वापस err;
पूर्ण

अटल पूर्णांक pasemi_i2c_xfer(काष्ठा i2c_adapter *adapter,
			   काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा pasemi_smbus *smbus = adapter->algo_data;
	पूर्णांक ret, i;

	pasemi_smb_clear(smbus);

	ret = 0;

	क्रम (i = 0; i < num && !ret; i++)
		ret = pasemi_i2c_xfer_msg(adapter, &msgs[i], (i == (num - 1)));

	वापस ret ? ret : num;
पूर्ण

अटल पूर्णांक pasemi_smb_xfer(काष्ठा i2c_adapter *adapter,
		u16 addr, अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा pasemi_smbus *smbus = adapter->algo_data;
	अचिन्हित पूर्णांक rd;
	पूर्णांक पढ़ो_flag, err;
	पूर्णांक len = 0, i;

	/* All our ops take 8-bit shअगरted addresses */
	addr <<= 1;
	पढ़ो_flag = पढ़ो_ग_लिखो == I2C_SMBUS_READ;

	pasemi_smb_clear(smbus);

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		TXFIFO_WR(smbus, addr | पढ़ो_flag | MTXFIFO_START |
			  MTXFIFO_STOP);
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		TXFIFO_WR(smbus, addr | पढ़ो_flag | MTXFIFO_START);
		अगर (पढ़ो_ग_लिखो)
			TXFIFO_WR(smbus, 1 | MTXFIFO_STOP | MTXFIFO_READ);
		अन्यथा
			TXFIFO_WR(smbus, MTXFIFO_STOP | command);
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		TXFIFO_WR(smbus, addr | MTXFIFO_START);
		TXFIFO_WR(smbus, command);
		अगर (पढ़ो_ग_लिखो) अणु
			TXFIFO_WR(smbus, addr | I2C_SMBUS_READ | MTXFIFO_START);
			TXFIFO_WR(smbus, 1 | MTXFIFO_READ | MTXFIFO_STOP);
		पूर्ण अन्यथा अणु
			TXFIFO_WR(smbus, MTXFIFO_STOP | data->byte);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		TXFIFO_WR(smbus, addr | MTXFIFO_START);
		TXFIFO_WR(smbus, command);
		अगर (पढ़ो_ग_लिखो) अणु
			TXFIFO_WR(smbus, addr | I2C_SMBUS_READ | MTXFIFO_START);
			TXFIFO_WR(smbus, 2 | MTXFIFO_READ | MTXFIFO_STOP);
		पूर्ण अन्यथा अणु
			TXFIFO_WR(smbus, data->word & MTXFIFO_DATA_M);
			TXFIFO_WR(smbus, MTXFIFO_STOP | (data->word >> 8));
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		TXFIFO_WR(smbus, addr | MTXFIFO_START);
		TXFIFO_WR(smbus, command);
		अगर (पढ़ो_ग_लिखो) अणु
			TXFIFO_WR(smbus, addr | I2C_SMBUS_READ | MTXFIFO_START);
			TXFIFO_WR(smbus, 1 | MTXFIFO_READ);
			rd = RXFIFO_RD(smbus);
			len = min_t(u8, (rd & MRXFIFO_DATA_M),
				    I2C_SMBUS_BLOCK_MAX);
			TXFIFO_WR(smbus, len | MTXFIFO_READ |
					 MTXFIFO_STOP);
		पूर्ण अन्यथा अणु
			len = min_t(u8, data->block[0], I2C_SMBUS_BLOCK_MAX);
			TXFIFO_WR(smbus, len);
			क्रम (i = 1; i < len; i++)
				TXFIFO_WR(smbus, data->block[i]);
			TXFIFO_WR(smbus, data->block[len] | MTXFIFO_STOP);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		TXFIFO_WR(smbus, addr | MTXFIFO_START);
		TXFIFO_WR(smbus, command);
		TXFIFO_WR(smbus, data->word & MTXFIFO_DATA_M);
		TXFIFO_WR(smbus, (data->word >> 8) & MTXFIFO_DATA_M);
		TXFIFO_WR(smbus, addr | I2C_SMBUS_READ | MTXFIFO_START);
		TXFIFO_WR(smbus, 2 | MTXFIFO_STOP | MTXFIFO_READ);
		अवरोध;
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		len = min_t(u8, data->block[0], I2C_SMBUS_BLOCK_MAX - 1);
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		TXFIFO_WR(smbus, addr | MTXFIFO_START);
		TXFIFO_WR(smbus, command);
		TXFIFO_WR(smbus, len);
		क्रम (i = 1; i <= len; i++)
			TXFIFO_WR(smbus, data->block[i]);
		TXFIFO_WR(smbus, addr | I2C_SMBUS_READ);
		TXFIFO_WR(smbus, MTXFIFO_READ | 1);
		rd = RXFIFO_RD(smbus);
		len = min_t(u8, (rd & MRXFIFO_DATA_M),
			    I2C_SMBUS_BLOCK_MAX - len);
		TXFIFO_WR(smbus, len | MTXFIFO_READ | MTXFIFO_STOP);
		अवरोध;

	शेष:
		dev_warn(&adapter->dev, "Unsupported transaction %d\n", size);
		वापस -EINVAL;
	पूर्ण

	err = pasemi_smb_रुकोपढ़ोy(smbus);
	अगर (err)
		जाओ reset_out;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
		वापस 0;

	चयन (size) अणु
	हाल I2C_SMBUS_BYTE:
	हाल I2C_SMBUS_BYTE_DATA:
		rd = RXFIFO_RD(smbus);
		अगर (rd & MRXFIFO_EMPTY) अणु
			err = -ENODATA;
			जाओ reset_out;
		पूर्ण
		data->byte = rd & MRXFIFO_DATA_M;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
	हाल I2C_SMBUS_PROC_CALL:
		rd = RXFIFO_RD(smbus);
		अगर (rd & MRXFIFO_EMPTY) अणु
			err = -ENODATA;
			जाओ reset_out;
		पूर्ण
		data->word = rd & MRXFIFO_DATA_M;
		rd = RXFIFO_RD(smbus);
		अगर (rd & MRXFIFO_EMPTY) अणु
			err = -ENODATA;
			जाओ reset_out;
		पूर्ण
		data->word |= (rd & MRXFIFO_DATA_M) << 8;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		data->block[0] = len;
		क्रम (i = 1; i <= len; i ++) अणु
			rd = RXFIFO_RD(smbus);
			अगर (rd & MRXFIFO_EMPTY) अणु
				err = -ENODATA;
				जाओ reset_out;
			पूर्ण
			data->block[i] = rd & MRXFIFO_DATA_M;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;

 reset_out:
	reg_ग_लिखो(smbus, REG_CTL, (CTL_MTR | CTL_MRR |
		  (CLK_100K_DIV & CTL_CLK_M)));
	वापस err;
पूर्ण

अटल u32 pasemi_smb_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	       I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_PROC_CALL |
	       I2C_FUNC_SMBUS_BLOCK_PROC_CALL | I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.master_xfer	= pasemi_i2c_xfer,
	.smbus_xfer	= pasemi_smb_xfer,
	.functionality	= pasemi_smb_func,
पूर्ण;

अटल पूर्णांक pasemi_smb_probe(काष्ठा pci_dev *dev,
				      स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pasemi_smbus *smbus;
	पूर्णांक error;

	अगर (!(pci_resource_flags(dev, 0) & IORESOURCE_IO))
		वापस -ENODEV;

	smbus = kzalloc(माप(काष्ठा pasemi_smbus), GFP_KERNEL);
	अगर (!smbus)
		वापस -ENOMEM;

	smbus->dev = dev;
	smbus->base = pci_resource_start(dev, 0);
	smbus->size = pci_resource_len(dev, 0);

	अगर (!request_region(smbus->base, smbus->size,
			    pasemi_smb_driver.name)) अणु
		error = -EBUSY;
		जाओ out_kमुक्त;
	पूर्ण

	smbus->adapter.owner = THIS_MODULE;
	snम_लिखो(smbus->adapter.name, माप(smbus->adapter.name),
		 "PA Semi SMBus adapter at 0x%lx", smbus->base);
	smbus->adapter.class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	smbus->adapter.algo = &smbus_algorithm;
	smbus->adapter.algo_data = smbus;

	/* set up the sysfs linkage to our parent device */
	smbus->adapter.dev.parent = &dev->dev;

	reg_ग_लिखो(smbus, REG_CTL, (CTL_MTR | CTL_MRR |
		  (CLK_100K_DIV & CTL_CLK_M)));

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

अटल व्योम pasemi_smb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा pasemi_smbus *smbus = pci_get_drvdata(dev);

	i2c_del_adapter(&smbus->adapter);
	release_region(smbus->base, smbus->size);
	kमुक्त(smbus);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pasemi_smb_ids[] = अणु
	अणु PCI_DEVICE(0x1959, 0xa003) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pasemi_smb_ids);

अटल काष्ठा pci_driver pasemi_smb_driver = अणु
	.name		= "i2c-pasemi",
	.id_table	= pasemi_smb_ids,
	.probe		= pasemi_smb_probe,
	.हटाओ		= pasemi_smb_हटाओ,
पूर्ण;

module_pci_driver(pasemi_smb_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR ("Olof Johansson <olof@lixom.net>");
MODULE_DESCRIPTION("PA Semi PWRficient SMBus driver");
