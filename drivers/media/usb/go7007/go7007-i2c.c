<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005-2006 Micronas USA Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/list.h>
#समावेश <linux/unistd.h>
#समावेश <linux/समय.स>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

#समावेश "go7007-priv.h"

/********************* Driver क्रम on-board I2C adapter *********************/

/* #घोषणा GO7007_I2C_DEBUG */

#घोषणा SPI_I2C_ADDR_BASE		0x1400
#घोषणा STATUS_REG_ADDR			(SPI_I2C_ADDR_BASE + 0x2)
#घोषणा I2C_CTRL_REG_ADDR		(SPI_I2C_ADDR_BASE + 0x6)
#घोषणा I2C_DEV_UP_ADDR_REG_ADDR	(SPI_I2C_ADDR_BASE + 0x7)
#घोषणा I2C_LO_ADDR_REG_ADDR		(SPI_I2C_ADDR_BASE + 0x8)
#घोषणा I2C_DATA_REG_ADDR		(SPI_I2C_ADDR_BASE + 0x9)
#घोषणा I2C_CLKFREQ_REG_ADDR		(SPI_I2C_ADDR_BASE + 0xa)

#घोषणा I2C_STATE_MASK			0x0007
#घोषणा I2C_READ_READY_MASK		0x0008

/* There is only one I2C port on the TW2804 that feeds all four GO7007 VIPs
 * on the Adlink PCI-MPG24, so access is shared between all of them. */
अटल DEFINE_MUTEX(adlink_mpg24_i2c_lock);

अटल पूर्णांक go7007_i2c_xfer(काष्ठा go7007 *go, u16 addr, पूर्णांक पढ़ो,
		u16 command, पूर्णांक flags, u8 *data)
अणु
	पूर्णांक i, ret = -EIO;
	u16 val;

	अगर (go->status == STATUS_SHUTDOWN)
		वापस -ENODEV;

#अगर_घोषित GO7007_I2C_DEBUG
	अगर (पढ़ो)
		dev_dbg(go->dev, "go7007-i2c: reading 0x%02x on 0x%02x\n",
			command, addr);
	अन्यथा
		dev_dbg(go->dev,
			"go7007-i2c: writing 0x%02x to 0x%02x on 0x%02x\n",
			*data, command, addr);
#पूर्ण_अगर

	mutex_lock(&go->hw_lock);

	अगर (go->board_id == GO7007_BOARDID_ADLINK_MPG24) अणु
		/* Bridge the I2C port on this GO7007 to the shared bus */
		mutex_lock(&adlink_mpg24_i2c_lock);
		go7007_ग_लिखो_addr(go, 0x3c82, 0x0020);
	पूर्ण

	/* Wait क्रम I2C adapter to be पढ़ोy */
	क्रम (i = 0; i < 10; ++i) अणु
		अगर (go7007_पढ़ो_addr(go, STATUS_REG_ADDR, &val) < 0)
			जाओ i2c_करोne;
		अगर (!(val & I2C_STATE_MASK))
			अवरोध;
		msleep(100);
	पूर्ण
	अगर (i == 10) अणु
		dev_err(go->dev, "go7007-i2c: I2C adapter is hung\n");
		जाओ i2c_करोne;
	पूर्ण

	/* Set target रेजिस्टर (command) */
	go7007_ग_लिखो_addr(go, I2C_CTRL_REG_ADDR, flags);
	go7007_ग_लिखो_addr(go, I2C_LO_ADDR_REG_ADDR, command);

	/* If we're writing, send the data and target address and we're करोne */
	अगर (!पढ़ो) अणु
		go7007_ग_लिखो_addr(go, I2C_DATA_REG_ADDR, *data);
		go7007_ग_लिखो_addr(go, I2C_DEV_UP_ADDR_REG_ADDR,
					(addr << 9) | (command >> 8));
		ret = 0;
		जाओ i2c_करोne;
	पूर्ण

	/* Otherwise, we're पढ़ोing.  First clear i2c_rx_data_rdy. */
	अगर (go7007_पढ़ो_addr(go, I2C_DATA_REG_ADDR, &val) < 0)
		जाओ i2c_करोne;

	/* Send the target address plus पढ़ो flag */
	go7007_ग_लिखो_addr(go, I2C_DEV_UP_ADDR_REG_ADDR,
			(addr << 9) | 0x0100 | (command >> 8));

	/* Wait क्रम i2c_rx_data_rdy */
	क्रम (i = 0; i < 10; ++i) अणु
		अगर (go7007_पढ़ो_addr(go, STATUS_REG_ADDR, &val) < 0)
			जाओ i2c_करोne;
		अगर (val & I2C_READ_READY_MASK)
			अवरोध;
		msleep(100);
	पूर्ण
	अगर (i == 10) अणु
		dev_err(go->dev, "go7007-i2c: I2C adapter is hung\n");
		जाओ i2c_करोne;
	पूर्ण

	/* Retrieve the पढ़ो byte */
	अगर (go7007_पढ़ो_addr(go, I2C_DATA_REG_ADDR, &val) < 0)
		जाओ i2c_करोne;
	*data = val;
	ret = 0;

i2c_करोne:
	अगर (go->board_id == GO7007_BOARDID_ADLINK_MPG24) अणु
		/* Isolate the I2C port on this GO7007 from the shared bus */
		go7007_ग_लिखो_addr(go, 0x3c82, 0x0000);
		mutex_unlock(&adlink_mpg24_i2c_lock);
	पूर्ण
	mutex_unlock(&go->hw_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक go7007_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
		अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	काष्ठा go7007 *go = i2c_get_adapdata(adapter);

	अगर (size != I2C_SMBUS_BYTE_DATA)
		वापस -EIO;
	वापस go7007_i2c_xfer(go, addr, पढ़ो_ग_लिखो == I2C_SMBUS_READ, command,
			flags & I2C_CLIENT_SCCB ? 0x10 : 0x00, &data->byte);
पूर्ण

/* VERY LIMITED I2C master xfer function -- only needed because the
 * SMBus functions only support 8-bit commands and the SAA7135 uses
 * 16-bit commands.  The I2C पूर्णांकerface on the GO7007, as limited as
 * it is, करोes support this mode. */

अटल पूर्णांक go7007_i2c_master_xfer(काष्ठा i2c_adapter *adapter,
					काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा go7007 *go = i2c_get_adapdata(adapter);
	पूर्णांक i;

	क्रम (i = 0; i < num; ++i) अणु
		/* We can only करो two things here -- ग_लिखो three bytes, or
		 * ग_लिखो two bytes and पढ़ो one byte. */
		अगर (msgs[i].len == 2) अणु
			अगर (i + 1 == num || msgs[i].addr != msgs[i + 1].addr ||
					(msgs[i].flags & I2C_M_RD) ||
					!(msgs[i + 1].flags & I2C_M_RD) ||
					msgs[i + 1].len != 1)
				वापस -EIO;
			अगर (go7007_i2c_xfer(go, msgs[i].addr, 1,
					(msgs[i].buf[0] << 8) | msgs[i].buf[1],
					0x01, &msgs[i + 1].buf[0]) < 0)
				वापस -EIO;
			++i;
		पूर्ण अन्यथा अगर (msgs[i].len == 3) अणु
			अगर (msgs[i].flags & I2C_M_RD)
				वापस -EIO;
			अगर (msgs[i].len != 3)
				वापस -EIO;
			अगर (go7007_i2c_xfer(go, msgs[i].addr, 0,
					(msgs[i].buf[0] << 8) | msgs[i].buf[1],
					0x01, &msgs[i].buf[2]) < 0)
				वापस -EIO;
		पूर्ण अन्यथा
			वापस -EIO;
	पूर्ण

	वापस num;
पूर्ण

अटल u32 go7007_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_BYTE_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm go7007_algo = अणु
	.smbus_xfer	= go7007_smbus_xfer,
	.master_xfer	= go7007_i2c_master_xfer,
	.functionality	= go7007_functionality,
पूर्ण;

अटल काष्ठा i2c_adapter go7007_adap_templ = अणु
	.owner			= THIS_MODULE,
	.name			= "WIS GO7007SB",
	.algo			= &go7007_algo,
पूर्ण;

पूर्णांक go7007_i2c_init(काष्ठा go7007 *go)
अणु
	स_नकल(&go->i2c_adapter, &go7007_adap_templ,
			माप(go7007_adap_templ));
	go->i2c_adapter.dev.parent = go->dev;
	i2c_set_adapdata(&go->i2c_adapter, go);
	अगर (i2c_add_adapter(&go->i2c_adapter) < 0) अणु
		dev_err(go->dev,
			"go7007-i2c: error: i2c_add_adapter failed\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
