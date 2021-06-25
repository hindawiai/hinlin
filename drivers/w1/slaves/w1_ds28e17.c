<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	w1_ds28e17.c - w1 family 19 (DS28E17) driver
 *
 * Copyright (c) 2016 Jan Kandziora <jjj@gmx.de>
 */

#समावेश <linux/crc16.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#घोषणा CRC16_INIT 0

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_DS28E17 0x19

/* Module setup. */
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Jan Kandziora <jjj@gmx.de>");
MODULE_DESCRIPTION("w1 family 19 driver for DS28E17, 1-wire to I2C master bridge");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS28E17));


/* Default I2C speed to be set when a DS28E17 is detected. */
अटल पूर्णांक i2c_speed = 100;
module_param_named(speed, i2c_speed, पूर्णांक, (S_IRUSR | S_IWUSR));
MODULE_PARM_DESC(speed, "Default I2C speed to be set when a DS28E17 is detected");

/* Default I2C stretch value to be set when a DS28E17 is detected. */
अटल अक्षर i2c_stretch = 1;
module_param_named(stretch, i2c_stretch, byte, (S_IRUSR | S_IWUSR));
MODULE_PARM_DESC(stretch, "Default I2C stretch value to be set when a DS28E17 is detected");

/* DS28E17 device command codes. */
#घोषणा W1_F19_WRITE_DATA_WITH_STOP      0x4B
#घोषणा W1_F19_WRITE_DATA_NO_STOP        0x5A
#घोषणा W1_F19_WRITE_DATA_ONLY           0x69
#घोषणा W1_F19_WRITE_DATA_ONLY_WITH_STOP 0x78
#घोषणा W1_F19_READ_DATA_WITH_STOP       0x87
#घोषणा W1_F19_WRITE_READ_DATA_WITH_STOP 0x2D
#घोषणा W1_F19_WRITE_CONFIGURATION       0xD2
#घोषणा W1_F19_READ_CONFIGURATION        0xE1
#घोषणा W1_F19_ENABLE_SLEEP_MODE         0x1E
#घोषणा W1_F19_READ_DEVICE_REVISION      0xC4

/* DS28E17 status bits */
#घोषणा W1_F19_STATUS_CRC     0x01
#घोषणा W1_F19_STATUS_ADDRESS 0x02
#घोषणा W1_F19_STATUS_START   0x08

/*
 * Maximum number of I2C bytes to transfer within one CRC16 रक्षित onewire
 * command.
 * */
#घोषणा W1_F19_WRITE_DATA_LIMIT 255

/* Maximum number of I2C bytes to पढ़ो with one onewire command. */
#घोषणा W1_F19_READ_DATA_LIMIT 255

/* Constants क्रम calculating the busy sleep. */
#घोषणा W1_F19_BUSY_TIMEBASES अणु 90, 23, 10 पूर्ण
#घोषणा W1_F19_BUSY_GRATUITY  1000

/* Number of checks क्रम the busy flag beक्रमe समयout. */
#घोषणा W1_F19_BUSY_CHECKS 1000


/* Slave specअगरic data. */
काष्ठा w1_f19_data अणु
	u8 speed;
	u8 stretch;
	काष्ठा i2c_adapter adapter;
पूर्ण;


/* Wait a जबतक until the busy flag clears. */
अटल पूर्णांक w1_f19_i2c_busy_रुको(काष्ठा w1_slave *sl, माप_प्रकार count)
अणु
	स्थिर अचिन्हित दीर्घ समयbases[3] = W1_F19_BUSY_TIMEBASES;
	काष्ठा w1_f19_data *data = sl->family_data;
	अचिन्हित पूर्णांक checks;

	/* Check the busy flag first in any हाल.*/
	अगर (w1_touch_bit(sl->master, 1) == 0)
		वापस 0;

	/*
	 * Do a generously दीर्घ sleep in the beginning,
	 * as we have to रुको at least this समय क्रम all
	 * the I2C bytes at the given speed to be transferred.
	 */
	usleep_range(समयbases[data->speed] * (data->stretch) * count,
		समयbases[data->speed] * (data->stretch) * count
		+ W1_F19_BUSY_GRATUITY);

	/* Now continusly check the busy flag sent by the DS28E17. */
	checks = W1_F19_BUSY_CHECKS;
	जबतक ((checks--) > 0) अणु
		/* Return success अगर the busy flag is cleared. */
		अगर (w1_touch_bit(sl->master, 1) == 0)
			वापस 0;

		/* Wait one non-streched byte बारlot. */
		udelay(समयbases[data->speed]);
	पूर्ण

	/* Timeout. */
	dev_warn(&sl->dev, "busy timeout\n");
	वापस -ETIMEDOUT;
पूर्ण


/* Utility function: result. */
अटल माप_प्रकार w1_f19_error(काष्ठा w1_slave *sl, u8 w1_buf[])
अणु
	/* Warnings. */
	अगर (w1_buf[0] & W1_F19_STATUS_CRC)
		dev_warn(&sl->dev, "crc16 mismatch\n");
	अगर (w1_buf[0] & W1_F19_STATUS_ADDRESS)
		dev_warn(&sl->dev, "i2c device not responding\n");
	अगर ((w1_buf[0] & (W1_F19_STATUS_CRC | W1_F19_STATUS_ADDRESS)) == 0
			&& w1_buf[1] != 0) अणु
		dev_warn(&sl->dev, "i2c short write, %d bytes not acknowledged\n",
			w1_buf[1]);
	पूर्ण

	/* Check error conditions. */
	अगर (w1_buf[0] & W1_F19_STATUS_ADDRESS)
		वापस -ENXIO;
	अगर (w1_buf[0] & W1_F19_STATUS_START)
		वापस -EAGAIN;
	अगर (w1_buf[0] != 0 || w1_buf[1] != 0)
		वापस -EIO;

	/* All ok. */
	वापस 0;
पूर्ण


/* Utility function: ग_लिखो data to I2C slave, single chunk. */
अटल पूर्णांक __w1_f19_i2c_ग_लिखो(काष्ठा w1_slave *sl,
	स्थिर u8 *command, माप_प्रकार command_count,
	स्थिर u8 *buffer, माप_प्रकार count)
अणु
	u16 crc;
	पूर्णांक error;
	u8 w1_buf[2];

	/* Send command and I2C data to DS28E17. */
	crc = crc16(CRC16_INIT, command, command_count);
	w1_ग_लिखो_block(sl->master, command, command_count);

	w1_buf[0] = count;
	crc = crc16(crc, w1_buf, 1);
	w1_ग_लिखो_8(sl->master, w1_buf[0]);

	crc = crc16(crc, buffer, count);
	w1_ग_लिखो_block(sl->master, buffer, count);

	w1_buf[0] = ~(crc & 0xFF);
	w1_buf[1] = ~((crc >> 8) & 0xFF);
	w1_ग_लिखो_block(sl->master, w1_buf, 2);

	/* Wait until busy flag clears (or समयout). */
	अगर (w1_f19_i2c_busy_रुको(sl, count + 1) < 0)
		वापस -ETIMEDOUT;

	/* Read status from DS28E17. */
	w1_पढ़ो_block(sl->master, w1_buf, 2);

	/* Check error conditions. */
	error = w1_f19_error(sl, w1_buf);
	अगर (error < 0)
		वापस error;

	/* Return number of bytes written. */
	वापस count;
पूर्ण


/* Write data to I2C slave. */
अटल पूर्णांक w1_f19_i2c_ग_लिखो(काष्ठा w1_slave *sl, u16 i2c_address,
	स्थिर u8 *buffer, माप_प्रकार count, bool stop)
अणु
	पूर्णांक result;
	पूर्णांक reमुख्यing = count;
	स्थिर u8 *p;
	u8 command[2];

	/* Check input. */
	अगर (count == 0)
		वापस -EOPNOTSUPP;

	/* Check whether we need multiple commands. */
	अगर (count <= W1_F19_WRITE_DATA_LIMIT) अणु
		/*
		 * Small data amount. Data can be sent with
		 * a single onewire command.
		 */

		/* Send all data to DS28E17. */
		command[0] = (stop ? W1_F19_WRITE_DATA_WITH_STOP
			: W1_F19_WRITE_DATA_NO_STOP);
		command[1] = i2c_address << 1;
		result = __w1_f19_i2c_ग_लिखो(sl, command, 2, buffer, count);
	पूर्ण अन्यथा अणु
		/* Large data amount. Data has to be sent in multiple chunks. */

		/* Send first chunk to DS28E17. */
		p = buffer;
		command[0] = W1_F19_WRITE_DATA_NO_STOP;
		command[1] = i2c_address << 1;
		result = __w1_f19_i2c_ग_लिखो(sl, command, 2, p,
			W1_F19_WRITE_DATA_LIMIT);
		अगर (result < 0)
			वापस result;

		/* Resume to same DS28E17. */
		अगर (w1_reset_resume_command(sl->master))
			वापस -EIO;

		/* Next data chunk. */
		p += W1_F19_WRITE_DATA_LIMIT;
		reमुख्यing -= W1_F19_WRITE_DATA_LIMIT;

		जबतक (reमुख्यing > W1_F19_WRITE_DATA_LIMIT) अणु
			/* Send पूर्णांकermediate chunk to DS28E17. */
			command[0] = W1_F19_WRITE_DATA_ONLY;
			result = __w1_f19_i2c_ग_लिखो(sl, command, 1, p,
					W1_F19_WRITE_DATA_LIMIT);
			अगर (result < 0)
				वापस result;

			/* Resume to same DS28E17. */
			अगर (w1_reset_resume_command(sl->master))
				वापस -EIO;

			/* Next data chunk. */
			p += W1_F19_WRITE_DATA_LIMIT;
			reमुख्यing -= W1_F19_WRITE_DATA_LIMIT;
		पूर्ण

		/* Send final chunk to DS28E17. */
		command[0] = (stop ? W1_F19_WRITE_DATA_ONLY_WITH_STOP
			: W1_F19_WRITE_DATA_ONLY);
		result = __w1_f19_i2c_ग_लिखो(sl, command, 1, p, reमुख्यing);
	पूर्ण

	वापस result;
पूर्ण


/* Read data from I2C slave. */
अटल पूर्णांक w1_f19_i2c_पढ़ो(काष्ठा w1_slave *sl, u16 i2c_address,
	u8 *buffer, माप_प्रकार count)
अणु
	u16 crc;
	पूर्णांक error;
	u8 w1_buf[5];

	/* Check input. */
	अगर (count == 0)
		वापस -EOPNOTSUPP;

	/* Send command to DS28E17. */
	w1_buf[0] = W1_F19_READ_DATA_WITH_STOP;
	w1_buf[1] = i2c_address << 1 | 0x01;
	w1_buf[2] = count;
	crc = crc16(CRC16_INIT, w1_buf, 3);
	w1_buf[3] = ~(crc & 0xFF);
	w1_buf[4] = ~((crc >> 8) & 0xFF);
	w1_ग_लिखो_block(sl->master, w1_buf, 5);

	/* Wait until busy flag clears (or समयout). */
	अगर (w1_f19_i2c_busy_रुको(sl, count + 1) < 0)
		वापस -ETIMEDOUT;

	/* Read status from DS28E17. */
	w1_buf[0] = w1_पढ़ो_8(sl->master);
	w1_buf[1] = 0;

	/* Check error conditions. */
	error = w1_f19_error(sl, w1_buf);
	अगर (error < 0)
		वापस error;

	/* Read received I2C data from DS28E17. */
	वापस w1_पढ़ो_block(sl->master, buffer, count);
पूर्ण


/* Write to, then पढ़ो data from I2C slave. */
अटल पूर्णांक w1_f19_i2c_ग_लिखो_पढ़ो(काष्ठा w1_slave *sl, u16 i2c_address,
	स्थिर u8 *wbuffer, माप_प्रकार wcount, u8 *rbuffer, माप_प्रकार rcount)
अणु
	u16 crc;
	पूर्णांक error;
	u8 w1_buf[3];

	/* Check input. */
	अगर (wcount == 0 || rcount == 0)
		वापस -EOPNOTSUPP;

	/* Send command and I2C data to DS28E17. */
	w1_buf[0] = W1_F19_WRITE_READ_DATA_WITH_STOP;
	w1_buf[1] = i2c_address << 1;
	w1_buf[2] = wcount;
	crc = crc16(CRC16_INIT, w1_buf, 3);
	w1_ग_लिखो_block(sl->master, w1_buf, 3);

	crc = crc16(crc, wbuffer, wcount);
	w1_ग_लिखो_block(sl->master, wbuffer, wcount);

	w1_buf[0] = rcount;
	crc = crc16(crc, w1_buf, 1);
	w1_buf[1] = ~(crc & 0xFF);
	w1_buf[2] = ~((crc >> 8) & 0xFF);
	w1_ग_लिखो_block(sl->master, w1_buf, 3);

	/* Wait until busy flag clears (or समयout). */
	अगर (w1_f19_i2c_busy_रुको(sl, wcount + rcount + 2) < 0)
		वापस -ETIMEDOUT;

	/* Read status from DS28E17. */
	w1_पढ़ो_block(sl->master, w1_buf, 2);

	/* Check error conditions. */
	error = w1_f19_error(sl, w1_buf);
	अगर (error < 0)
		वापस error;

	/* Read received I2C data from DS28E17. */
	वापस w1_पढ़ो_block(sl->master, rbuffer, rcount);
पूर्ण


/* Do an I2C master transfer. */
अटल पूर्णांक w1_f19_i2c_master_transfer(काष्ठा i2c_adapter *adapter,
	काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा w1_slave *sl = (काष्ठा w1_slave *) adapter->algo_data;
	पूर्णांक i = 0;
	पूर्णांक result = 0;

	/* Start onewire transaction. */
	mutex_lock(&sl->master->bus_mutex);

	/* Select DS28E17. */
	अगर (w1_reset_select_slave(sl)) अणु
		i = -EIO;
		जाओ error;
	पूर्ण

	/* Loop जबतक there are still messages to transfer. */
	जबतक (i < num) अणु
		/*
		 * Check क्रम special हाल: Small ग_लिखो followed
		 * by पढ़ो to same I2C device.
		 */
		अगर (i < (num-1)
			&& msgs[i].addr == msgs[i+1].addr
			&& !(msgs[i].flags & I2C_M_RD)
			&& (msgs[i+1].flags & I2C_M_RD)
			&& (msgs[i].len <= W1_F19_WRITE_DATA_LIMIT)) अणु
			/*
			 * The DS28E17 has a combined transfer
			 * क्रम small ग_लिखो+पढ़ो.
			 */
			result = w1_f19_i2c_ग_लिखो_पढ़ो(sl, msgs[i].addr,
				msgs[i].buf, msgs[i].len,
				msgs[i+1].buf, msgs[i+1].len);
			अगर (result < 0) अणु
				i = result;
				जाओ error;
			पूर्ण

			/*
			 * Check अगर we should पूर्णांकerpret the पढ़ो data
			 * as a length byte. The DS28E17 unक्रमtunately
			 * has no पढ़ो without stop, so we can just करो
			 * another simple पढ़ो in that हाल.
			 */
			अगर (msgs[i+1].flags & I2C_M_RECV_LEN) अणु
				result = w1_f19_i2c_पढ़ो(sl, msgs[i+1].addr,
					&(msgs[i+1].buf[1]), msgs[i+1].buf[0]);
				अगर (result < 0) अणु
					i = result;
					जाओ error;
				पूर्ण
			पूर्ण

			/* Eat up पढ़ो message, too. */
			i++;
		पूर्ण अन्यथा अगर (msgs[i].flags & I2C_M_RD) अणु
			/* Read transfer. */
			result = w1_f19_i2c_पढ़ो(sl, msgs[i].addr,
				msgs[i].buf, msgs[i].len);
			अगर (result < 0) अणु
				i = result;
				जाओ error;
			पूर्ण

			/*
			 * Check अगर we should पूर्णांकerpret the पढ़ो data
			 * as a length byte. The DS28E17 unक्रमtunately
			 * has no पढ़ो without stop, so we can just करो
			 * another simple पढ़ो in that हाल.
			 */
			अगर (msgs[i].flags & I2C_M_RECV_LEN) अणु
				result = w1_f19_i2c_पढ़ो(sl,
					msgs[i].addr,
					&(msgs[i].buf[1]),
					msgs[i].buf[0]);
				अगर (result < 0) अणु
					i = result;
					जाओ error;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Write transfer.
			 * Stop condition only क्रम last
			 * transfer.
			 */
			result = w1_f19_i2c_ग_लिखो(sl,
				msgs[i].addr,
				msgs[i].buf,
				msgs[i].len,
				i == (num-1));
			अगर (result < 0) अणु
				i = result;
				जाओ error;
			पूर्ण
		पूर्ण

		/* Next message. */
		i++;

		/* Are there still messages to send/receive? */
		अगर (i < num) अणु
			/* Yes. Resume to same DS28E17. */
			अगर (w1_reset_resume_command(sl->master)) अणु
				i = -EIO;
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

error:
	/* End onewire transaction. */
	mutex_unlock(&sl->master->bus_mutex);

	/* Return number of messages processed or error. */
	वापस i;
पूर्ण


/* Get I2C adapter functionality. */
अटल u32 w1_f19_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	/*
	 * Plain I2C functions only.
	 * SMBus is emulated by the kernel's I2C layer.
	 * No "I2C_FUNC_SMBUS_QUICK"
	 * No "I2C_FUNC_SMBUS_READ_BLOCK_DATA"
	 * No "I2C_FUNC_SMBUS_BLOCK_PROC_CALL"
	 */
	वापस I2C_FUNC_I2C |
		I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_PROC_CALL |
		I2C_FUNC_SMBUS_WRITE_BLOCK_DATA |
		I2C_FUNC_SMBUS_I2C_BLOCK |
		I2C_FUNC_SMBUS_PEC;
पूर्ण


/* I2C adapter quirks. */
अटल स्थिर काष्ठा i2c_adapter_quirks w1_f19_i2c_adapter_quirks = अणु
	.max_पढ़ो_len = W1_F19_READ_DATA_LIMIT,
पूर्ण;

/* I2C algorithm. */
अटल स्थिर काष्ठा i2c_algorithm w1_f19_i2c_algorithm = अणु
	.master_xfer    = w1_f19_i2c_master_transfer,
	.functionality  = w1_f19_i2c_functionality,
पूर्ण;


/* Read I2C speed from DS28E17. */
अटल पूर्णांक w1_f19_get_i2c_speed(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_f19_data *data = sl->family_data;
	पूर्णांक result = -EIO;

	/* Start onewire transaction. */
	mutex_lock(&sl->master->bus_mutex);

	/* Select slave. */
	अगर (w1_reset_select_slave(sl))
		जाओ error;

	/* Read slave configuration byte. */
	w1_ग_लिखो_8(sl->master, W1_F19_READ_CONFIGURATION);
	result = w1_पढ़ो_8(sl->master);
	अगर (result < 0 || result > 2) अणु
		result = -EIO;
		जाओ error;
	पूर्ण

	/* Update speed in slave specअगरic data. */
	data->speed = result;

error:
	/* End onewire transaction. */
	mutex_unlock(&sl->master->bus_mutex);

	वापस result;
पूर्ण


/* Set I2C speed on DS28E17. */
अटल पूर्णांक __w1_f19_set_i2c_speed(काष्ठा w1_slave *sl, u8 speed)
अणु
	काष्ठा w1_f19_data *data = sl->family_data;
	स्थिर पूर्णांक i2c_speeds[3] = अणु 100, 400, 900 पूर्ण;
	u8 w1_buf[2];

	/* Select slave. */
	अगर (w1_reset_select_slave(sl))
		वापस -EIO;

	w1_buf[0] = W1_F19_WRITE_CONFIGURATION;
	w1_buf[1] = speed;
	w1_ग_लिखो_block(sl->master, w1_buf, 2);

	/* Update speed in slave specअगरic data. */
	data->speed = speed;

	dev_info(&sl->dev, "i2c speed set to %d kBaud\n", i2c_speeds[speed]);

	वापस 0;
पूर्ण

अटल पूर्णांक w1_f19_set_i2c_speed(काष्ठा w1_slave *sl, u8 speed)
अणु
	पूर्णांक result;

	/* Start onewire transaction. */
	mutex_lock(&sl->master->bus_mutex);

	/* Set I2C speed on DS28E17. */
	result = __w1_f19_set_i2c_speed(sl, speed);

	/* End onewire transaction. */
	mutex_unlock(&sl->master->bus_mutex);

	वापस result;
पूर्ण


/* Sysfs attributes. */

/* I2C speed attribute क्रम a single chip. */
अटल sमाप_प्रकार speed_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(dev);
	पूर्णांक result;

	/* Read current speed from slave. Updates data->speed. */
	result = w1_f19_get_i2c_speed(sl);
	अगर (result < 0)
		वापस result;

	/* Return current speed value. */
	वापस प्र_लिखो(buf, "%d\n", result);
पूर्ण

अटल sमाप_प्रकार speed_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(dev);
	पूर्णांक error;

	/* Valid values are: "100", "400", "900" */
	अगर (count < 3 || count > 4 || !buf)
		वापस -EINVAL;
	अगर (count == 4 && buf[3] != '\n')
		वापस -EINVAL;
	अगर (buf[1] != '0' || buf[2] != '0')
		वापस -EINVAL;

	/* Set speed on slave. */
	चयन (buf[0]) अणु
	हाल '1':
		error = w1_f19_set_i2c_speed(sl, 0);
		अवरोध;
	हाल '4':
		error = w1_f19_set_i2c_speed(sl, 1);
		अवरोध;
	हाल '9':
		error = w1_f19_set_i2c_speed(sl, 2);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (error < 0)
		वापस error;

	/* Return bytes written. */
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(speed);


/* Busy stretch attribute क्रम a single chip. */
अटल sमाप_प्रकार stretch_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(dev);
	काष्ठा w1_f19_data *data = sl->family_data;

	/* Return current stretch value. */
	वापस प्र_लिखो(buf, "%d\n", data->stretch);
पूर्ण

अटल sमाप_प्रकार stretch_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(dev);
	काष्ठा w1_f19_data *data = sl->family_data;

	/* Valid values are '1' to '9' */
	अगर (count < 1 || count > 2 || !buf)
		वापस -EINVAL;
	अगर (count == 2 && buf[1] != '\n')
		वापस -EINVAL;
	अगर (buf[0] < '1' || buf[0] > '9')
		वापस -EINVAL;

	/* Set busy stretch value. */
	data->stretch = buf[0] & 0x0F;

	/* Return bytes written. */
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(stretch);


/* All attributes. */
अटल काष्ठा attribute *w1_f19_attrs[] = अणु
	&dev_attr_speed.attr,
	&dev_attr_stretch.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_f19_group = अणु
	.attrs		= w1_f19_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_f19_groups[] = अणु
	&w1_f19_group,
	शून्य,
पूर्ण;


/* Slave add and हटाओ functions. */
अटल पूर्णांक w1_f19_add_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_f19_data *data = शून्य;

	/* Allocate memory क्रम slave specअगरic data. */
	data = devm_kzalloc(&sl->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	sl->family_data = data;

	/* Setup शेष I2C speed on slave. */
	चयन (i2c_speed) अणु
	हाल 100:
		__w1_f19_set_i2c_speed(sl, 0);
		अवरोध;
	हाल 400:
		__w1_f19_set_i2c_speed(sl, 1);
		अवरोध;
	हाल 900:
		__w1_f19_set_i2c_speed(sl, 2);
		अवरोध;
	शेष:
		/*
		 * A i2c_speed module parameter of anything अन्यथा
		 * than 100, 400, 900 means not to touch the
		 * speed of the DS28E17.
		 * We assume 400kBaud, the घातer-on value.
		 */
		data->speed = 1;
	पूर्ण

	/*
	 * Setup शेष busy stretch
	 * configuration क्रम the DS28E17.
	 */
	data->stretch = i2c_stretch;

	/* Setup I2C adapter. */
	data->adapter.owner      = THIS_MODULE;
	data->adapter.algo       = &w1_f19_i2c_algorithm;
	data->adapter.algo_data  = sl;
	म_नकल(data->adapter.name, "w1-");
	म_जोड़ो(data->adapter.name, sl->name);
	data->adapter.dev.parent = &sl->dev;
	data->adapter.quirks     = &w1_f19_i2c_adapter_quirks;

	वापस i2c_add_adapter(&data->adapter);
पूर्ण

अटल व्योम w1_f19_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_f19_data *family_data = sl->family_data;

	/* Delete I2C adapter. */
	i2c_del_adapter(&family_data->adapter);

	/* Free slave specअगरic data. */
	devm_kमुक्त(&sl->dev, family_data);
	sl->family_data = शून्य;
पूर्ण


/* Declarations within the w1 subप्रणाली. */
अटल स्थिर काष्ठा w1_family_ops w1_f19_fops = अणु
	.add_slave = w1_f19_add_slave,
	.हटाओ_slave = w1_f19_हटाओ_slave,
	.groups = w1_f19_groups,
पूर्ण;

अटल काष्ठा w1_family w1_family_19 = अणु
	.fid = W1_FAMILY_DS28E17,
	.fops = &w1_f19_fops,
पूर्ण;

module_w1_family(w1_family_19);
