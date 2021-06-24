<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux I2C core SMBus and SMBus emulation code
 *
 * This file contains the SMBus functions which are always included in the I2C
 * core because they can be emulated via I2C. SMBus specअगरic extensions
 * (e.g. smbalert) are handled in a separate i2c-smbus module.
 *
 * All SMBus-related things are written by Froकरो Looijaard <froकरोl@dds.nl>
 * SMBus 2.0 support by Mark Studebaker <mdsxyz123@yahoo.com> and
 * Jean Delvare <jdelvare@suse.de>
 */
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/slab.h>

#समावेश "i2c-core.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/smbus.h>


/* The SMBus parts */

#घोषणा POLY    (0x1070U << 3)
अटल u8 crc8(u16 data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (data & 0x8000)
			data = data ^ POLY;
		data = data << 1;
	पूर्ण
	वापस (u8)(data >> 8);
पूर्ण

/* Incremental CRC8 over count bytes in the array poपूर्णांकed to by p */
अटल u8 i2c_smbus_pec(u8 crc, u8 *p, माप_प्रकार count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		crc = crc8((crc ^ p[i]) << 8);
	वापस crc;
पूर्ण

/* Assume a 7-bit address, which is reasonable क्रम SMBus */
अटल u8 i2c_smbus_msg_pec(u8 pec, काष्ठा i2c_msg *msg)
अणु
	/* The address will be sent first */
	u8 addr = i2c_8bit_addr_from_msg(msg);
	pec = i2c_smbus_pec(pec, &addr, 1);

	/* The data buffer follows */
	वापस i2c_smbus_pec(pec, msg->buf, msg->len);
पूर्ण

/* Used क्रम ग_लिखो only transactions */
अटल अंतरभूत व्योम i2c_smbus_add_pec(काष्ठा i2c_msg *msg)
अणु
	msg->buf[msg->len] = i2c_smbus_msg_pec(0, msg);
	msg->len++;
पूर्ण

/* Return <0 on CRC error
   If there was a ग_लिखो beक्रमe this पढ़ो (most हालs) we need to take the
   partial CRC from the ग_लिखो part पूर्णांकo account.
   Note that this function करोes modअगरy the message (we need to decrease the
   message length to hide the CRC byte from the caller). */
अटल पूर्णांक i2c_smbus_check_pec(u8 cpec, काष्ठा i2c_msg *msg)
अणु
	u8 rpec = msg->buf[--msg->len];
	cpec = i2c_smbus_msg_pec(cpec, msg);

	अगर (rpec != cpec) अणु
		pr_debug("Bad PEC 0x%02x vs. 0x%02x\n",
			rpec, cpec);
		वापस -EBADMSG;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * i2c_smbus_पढ़ो_byte - SMBus "receive byte" protocol
 * @client: Handle to slave device
 *
 * This executes the SMBus "receive byte" protocol, वापसing negative त्रुटि_सं
 * अन्यथा the byte received from the device.
 */
s32 i2c_smbus_पढ़ो_byte(स्थिर काष्ठा i2c_client *client)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक status;

	status = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
				I2C_SMBUS_READ, 0,
				I2C_SMBUS_BYTE, &data);
	वापस (status < 0) ? status : data.byte;
पूर्ण
EXPORT_SYMBOL(i2c_smbus_पढ़ो_byte);

/**
 * i2c_smbus_ग_लिखो_byte - SMBus "send byte" protocol
 * @client: Handle to slave device
 * @value: Byte to be sent
 *
 * This executes the SMBus "send byte" protocol, वापसing negative त्रुटि_सं
 * अन्यथा zero on success.
 */
s32 i2c_smbus_ग_लिखो_byte(स्थिर काष्ठा i2c_client *client, u8 value)
अणु
	वापस i2c_smbus_xfer(client->adapter, client->addr, client->flags,
	                      I2C_SMBUS_WRITE, value, I2C_SMBUS_BYTE, शून्य);
पूर्ण
EXPORT_SYMBOL(i2c_smbus_ग_लिखो_byte);

/**
 * i2c_smbus_पढ़ो_byte_data - SMBus "read byte" protocol
 * @client: Handle to slave device
 * @command: Byte पूर्णांकerpreted by slave
 *
 * This executes the SMBus "read byte" protocol, वापसing negative त्रुटि_सं
 * अन्यथा a data byte received from the device.
 */
s32 i2c_smbus_पढ़ो_byte_data(स्थिर काष्ठा i2c_client *client, u8 command)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक status;

	status = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
				I2C_SMBUS_READ, command,
				I2C_SMBUS_BYTE_DATA, &data);
	वापस (status < 0) ? status : data.byte;
पूर्ण
EXPORT_SYMBOL(i2c_smbus_पढ़ो_byte_data);

/**
 * i2c_smbus_ग_लिखो_byte_data - SMBus "write byte" protocol
 * @client: Handle to slave device
 * @command: Byte पूर्णांकerpreted by slave
 * @value: Byte being written
 *
 * This executes the SMBus "write byte" protocol, वापसing negative त्रुटि_सं
 * अन्यथा zero on success.
 */
s32 i2c_smbus_ग_लिखो_byte_data(स्थिर काष्ठा i2c_client *client, u8 command,
			      u8 value)
अणु
	जोड़ i2c_smbus_data data;
	data.byte = value;
	वापस i2c_smbus_xfer(client->adapter, client->addr, client->flags,
			      I2C_SMBUS_WRITE, command,
			      I2C_SMBUS_BYTE_DATA, &data);
पूर्ण
EXPORT_SYMBOL(i2c_smbus_ग_लिखो_byte_data);

/**
 * i2c_smbus_पढ़ो_word_data - SMBus "read word" protocol
 * @client: Handle to slave device
 * @command: Byte पूर्णांकerpreted by slave
 *
 * This executes the SMBus "read word" protocol, वापसing negative त्रुटि_सं
 * अन्यथा a 16-bit अचिन्हित "word" received from the device.
 */
s32 i2c_smbus_पढ़ो_word_data(स्थिर काष्ठा i2c_client *client, u8 command)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक status;

	status = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
				I2C_SMBUS_READ, command,
				I2C_SMBUS_WORD_DATA, &data);
	वापस (status < 0) ? status : data.word;
पूर्ण
EXPORT_SYMBOL(i2c_smbus_पढ़ो_word_data);

/**
 * i2c_smbus_ग_लिखो_word_data - SMBus "write word" protocol
 * @client: Handle to slave device
 * @command: Byte पूर्णांकerpreted by slave
 * @value: 16-bit "word" being written
 *
 * This executes the SMBus "write word" protocol, वापसing negative त्रुटि_सं
 * अन्यथा zero on success.
 */
s32 i2c_smbus_ग_लिखो_word_data(स्थिर काष्ठा i2c_client *client, u8 command,
			      u16 value)
अणु
	जोड़ i2c_smbus_data data;
	data.word = value;
	वापस i2c_smbus_xfer(client->adapter, client->addr, client->flags,
			      I2C_SMBUS_WRITE, command,
			      I2C_SMBUS_WORD_DATA, &data);
पूर्ण
EXPORT_SYMBOL(i2c_smbus_ग_लिखो_word_data);

/**
 * i2c_smbus_पढ़ो_block_data - SMBus "block read" protocol
 * @client: Handle to slave device
 * @command: Byte पूर्णांकerpreted by slave
 * @values: Byte array पूर्णांकo which data will be पढ़ो; big enough to hold
 *	the data वापसed by the slave.  SMBus allows at most 32 bytes.
 *
 * This executes the SMBus "block read" protocol, वापसing negative त्रुटि_सं
 * अन्यथा the number of data bytes in the slave's response.
 *
 * Note that using this function requires that the client's adapter support
 * the I2C_FUNC_SMBUS_READ_BLOCK_DATA functionality.  Not all adapter drivers
 * support this; its emulation through I2C messaging relies on a specअगरic
 * mechanism (I2C_M_RECV_LEN) which may not be implemented.
 */
s32 i2c_smbus_पढ़ो_block_data(स्थिर काष्ठा i2c_client *client, u8 command,
			      u8 *values)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक status;

	status = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
				I2C_SMBUS_READ, command,
				I2C_SMBUS_BLOCK_DATA, &data);
	अगर (status)
		वापस status;

	स_नकल(values, &data.block[1], data.block[0]);
	वापस data.block[0];
पूर्ण
EXPORT_SYMBOL(i2c_smbus_पढ़ो_block_data);

/**
 * i2c_smbus_ग_लिखो_block_data - SMBus "block write" protocol
 * @client: Handle to slave device
 * @command: Byte पूर्णांकerpreted by slave
 * @length: Size of data block; SMBus allows at most 32 bytes
 * @values: Byte array which will be written.
 *
 * This executes the SMBus "block write" protocol, वापसing negative त्रुटि_सं
 * अन्यथा zero on success.
 */
s32 i2c_smbus_ग_लिखो_block_data(स्थिर काष्ठा i2c_client *client, u8 command,
			       u8 length, स्थिर u8 *values)
अणु
	जोड़ i2c_smbus_data data;

	अगर (length > I2C_SMBUS_BLOCK_MAX)
		length = I2C_SMBUS_BLOCK_MAX;
	data.block[0] = length;
	स_नकल(&data.block[1], values, length);
	वापस i2c_smbus_xfer(client->adapter, client->addr, client->flags,
			      I2C_SMBUS_WRITE, command,
			      I2C_SMBUS_BLOCK_DATA, &data);
पूर्ण
EXPORT_SYMBOL(i2c_smbus_ग_लिखो_block_data);

/* Returns the number of पढ़ो bytes */
s32 i2c_smbus_पढ़ो_i2c_block_data(स्थिर काष्ठा i2c_client *client, u8 command,
				  u8 length, u8 *values)
अणु
	जोड़ i2c_smbus_data data;
	पूर्णांक status;

	अगर (length > I2C_SMBUS_BLOCK_MAX)
		length = I2C_SMBUS_BLOCK_MAX;
	data.block[0] = length;
	status = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
				I2C_SMBUS_READ, command,
				I2C_SMBUS_I2C_BLOCK_DATA, &data);
	अगर (status < 0)
		वापस status;

	स_नकल(values, &data.block[1], data.block[0]);
	वापस data.block[0];
पूर्ण
EXPORT_SYMBOL(i2c_smbus_पढ़ो_i2c_block_data);

s32 i2c_smbus_ग_लिखो_i2c_block_data(स्थिर काष्ठा i2c_client *client, u8 command,
				   u8 length, स्थिर u8 *values)
अणु
	जोड़ i2c_smbus_data data;

	अगर (length > I2C_SMBUS_BLOCK_MAX)
		length = I2C_SMBUS_BLOCK_MAX;
	data.block[0] = length;
	स_नकल(data.block + 1, values, length);
	वापस i2c_smbus_xfer(client->adapter, client->addr, client->flags,
			      I2C_SMBUS_WRITE, command,
			      I2C_SMBUS_I2C_BLOCK_DATA, &data);
पूर्ण
EXPORT_SYMBOL(i2c_smbus_ग_लिखो_i2c_block_data);

अटल व्योम i2c_smbus_try_get_dmabuf(काष्ठा i2c_msg *msg, u8 init_val)
अणु
	bool is_पढ़ो = msg->flags & I2C_M_RD;
	अचिन्हित अक्षर *dma_buf;

	dma_buf = kzalloc(I2C_SMBUS_BLOCK_MAX + (is_पढ़ो ? 2 : 3), GFP_KERNEL);
	अगर (!dma_buf)
		वापस;

	msg->buf = dma_buf;
	msg->flags |= I2C_M_DMA_SAFE;

	अगर (init_val)
		msg->buf[0] = init_val;
पूर्ण

/*
 * Simulate a SMBus command using the I2C protocol.
 * No checking of parameters is करोne!
 */
अटल s32 i2c_smbus_xfer_emulated(काष्ठा i2c_adapter *adapter, u16 addr,
				   अचिन्हित लघु flags,
				   अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक size,
				   जोड़ i2c_smbus_data *data)
अणु
	/*
	 * So we need to generate a series of msgs. In the हाल of writing, we
	 * need to use only one message; when पढ़ोing, we need two. We
	 * initialize most things with sane शेषs, to keep the code below
	 * somewhat simpler.
	 */
	अचिन्हित अक्षर msgbuf0[I2C_SMBUS_BLOCK_MAX+3];
	अचिन्हित अक्षर msgbuf1[I2C_SMBUS_BLOCK_MAX+2];
	पूर्णांक nmsgs = पढ़ो_ग_लिखो == I2C_SMBUS_READ ? 2 : 1;
	u8 partial_pec = 0;
	पूर्णांक status;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = addr,
			.flags = flags,
			.len = 1,
			.buf = msgbuf0,
		पूर्ण, अणु
			.addr = addr,
			.flags = flags | I2C_M_RD,
			.len = 0,
			.buf = msgbuf1,
		पूर्ण,
	पूर्ण;
	bool wants_pec = ((flags & I2C_CLIENT_PEC) && size != I2C_SMBUS_QUICK
			  && size != I2C_SMBUS_I2C_BLOCK_DATA);

	msgbuf0[0] = command;
	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		msg[0].len = 0;
		/* Special हाल: The पढ़ो/ग_लिखो field is used as data */
		msg[0].flags = flags | (पढ़ो_ग_लिखो == I2C_SMBUS_READ ?
					I2C_M_RD : 0);
		nmsgs = 1;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			/* Special हाल: only a पढ़ो! */
			msg[0].flags = I2C_M_RD | flags;
			nmsgs = 1;
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			msg[1].len = 1;
		अन्यथा अणु
			msg[0].len = 2;
			msgbuf0[1] = data->byte;
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			msg[1].len = 2;
		अन्यथा अणु
			msg[0].len = 3;
			msgbuf0[1] = data->word & 0xff;
			msgbuf0[2] = data->word >> 8;
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_PROC_CALL:
		nmsgs = 2; /* Special हाल */
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		msg[0].len = 3;
		msg[1].len = 2;
		msgbuf0[1] = data->word & 0xff;
		msgbuf0[2] = data->word >> 8;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			msg[1].flags |= I2C_M_RECV_LEN;
			msg[1].len = 1; /* block length will be added by
					   the underlying bus driver */
			i2c_smbus_try_get_dmabuf(&msg[1], 0);
		पूर्ण अन्यथा अणु
			msg[0].len = data->block[0] + 2;
			अगर (msg[0].len > I2C_SMBUS_BLOCK_MAX + 2) अणु
				dev_err(&adapter->dev,
					"Invalid block write size %d\n",
					data->block[0]);
				वापस -EINVAL;
			पूर्ण

			i2c_smbus_try_get_dmabuf(&msg[0], command);
			स_नकल(msg[0].buf + 1, data->block, msg[0].len - 1);
		पूर्ण
		अवरोध;
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		nmsgs = 2; /* Another special हाल */
		पढ़ो_ग_लिखो = I2C_SMBUS_READ;
		अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX) अणु
			dev_err(&adapter->dev,
				"Invalid block write size %d\n",
				data->block[0]);
			वापस -EINVAL;
		पूर्ण

		msg[0].len = data->block[0] + 2;
		i2c_smbus_try_get_dmabuf(&msg[0], command);
		स_नकल(msg[0].buf + 1, data->block, msg[0].len - 1);

		msg[1].flags |= I2C_M_RECV_LEN;
		msg[1].len = 1; /* block length will be added by
				   the underlying bus driver */
		i2c_smbus_try_get_dmabuf(&msg[1], 0);
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX) अणु
			dev_err(&adapter->dev, "Invalid block %s size %d\n",
				पढ़ो_ग_लिखो == I2C_SMBUS_READ ? "read" : "write",
				data->block[0]);
			वापस -EINVAL;
		पूर्ण

		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			msg[1].len = data->block[0];
			i2c_smbus_try_get_dmabuf(&msg[1], 0);
		पूर्ण अन्यथा अणु
			msg[0].len = data->block[0] + 1;

			i2c_smbus_try_get_dmabuf(&msg[0], command);
			स_नकल(msg[0].buf + 1, data->block + 1, data->block[0]);
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&adapter->dev, "Unsupported transaction %d\n", size);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (wants_pec) अणु
		/* Compute PEC अगर first message is a ग_लिखो */
		अगर (!(msg[0].flags & I2C_M_RD)) अणु
			अगर (nmsgs == 1) /* Write only */
				i2c_smbus_add_pec(&msg[0]);
			अन्यथा /* Write followed by पढ़ो */
				partial_pec = i2c_smbus_msg_pec(0, &msg[0]);
		पूर्ण
		/* Ask क्रम PEC अगर last message is a पढ़ो */
		अगर (msg[nmsgs - 1].flags & I2C_M_RD)
			msg[nmsgs - 1].len++;
	पूर्ण

	status = __i2c_transfer(adapter, msg, nmsgs);
	अगर (status < 0)
		जाओ cleanup;
	अगर (status != nmsgs) अणु
		status = -EIO;
		जाओ cleanup;
	पूर्ण
	status = 0;

	/* Check PEC अगर last message is a पढ़ो */
	अगर (wants_pec && (msg[nmsgs - 1].flags & I2C_M_RD)) अणु
		status = i2c_smbus_check_pec(partial_pec, &msg[nmsgs - 1]);
		अगर (status < 0)
			जाओ cleanup;
	पूर्ण

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
		चयन (size) अणु
		हाल I2C_SMBUS_BYTE:
			data->byte = msgbuf0[0];
			अवरोध;
		हाल I2C_SMBUS_BYTE_DATA:
			data->byte = msgbuf1[0];
			अवरोध;
		हाल I2C_SMBUS_WORD_DATA:
		हाल I2C_SMBUS_PROC_CALL:
			data->word = msgbuf1[0] | (msgbuf1[1] << 8);
			अवरोध;
		हाल I2C_SMBUS_I2C_BLOCK_DATA:
			स_नकल(data->block + 1, msg[1].buf, data->block[0]);
			अवरोध;
		हाल I2C_SMBUS_BLOCK_DATA:
		हाल I2C_SMBUS_BLOCK_PROC_CALL:
			अगर (msg[1].buf[0] > I2C_SMBUS_BLOCK_MAX) अणु
				dev_err(&adapter->dev,
					"Invalid block size returned: %d\n",
					msg[1].buf[0]);
				status = -EPROTO;
				जाओ cleanup;
			पूर्ण
			स_नकल(data->block, msg[1].buf, msg[1].buf[0] + 1);
			अवरोध;
		पूर्ण

cleanup:
	अगर (msg[0].flags & I2C_M_DMA_SAFE)
		kमुक्त(msg[0].buf);
	अगर (msg[1].flags & I2C_M_DMA_SAFE)
		kमुक्त(msg[1].buf);

	वापस status;
पूर्ण

/**
 * i2c_smbus_xfer - execute SMBus protocol operations
 * @adapter: Handle to I2C bus
 * @addr: Address of SMBus slave on that bus
 * @flags: I2C_CLIENT_* flags (usually zero or I2C_CLIENT_PEC)
 * @पढ़ो_ग_लिखो: I2C_SMBUS_READ or I2C_SMBUS_WRITE
 * @command: Byte पूर्णांकerpreted by slave, क्रम protocols which use such bytes
 * @protocol: SMBus protocol operation to execute, such as I2C_SMBUS_PROC_CALL
 * @data: Data to be पढ़ो or written
 *
 * This executes an SMBus protocol operation, and वापसs a negative
 * त्रुटि_सं code अन्यथा zero on success.
 */
s32 i2c_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
		   अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		   u8 command, पूर्णांक protocol, जोड़ i2c_smbus_data *data)
अणु
	s32 res;

	res = __i2c_lock_bus_helper(adapter);
	अगर (res)
		वापस res;

	res = __i2c_smbus_xfer(adapter, addr, flags, पढ़ो_ग_लिखो,
			       command, protocol, data);
	i2c_unlock_bus(adapter, I2C_LOCK_SEGMENT);

	वापस res;
पूर्ण
EXPORT_SYMBOL(i2c_smbus_xfer);

s32 __i2c_smbus_xfer(काष्ठा i2c_adapter *adapter, u16 addr,
		     अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
		     u8 command, पूर्णांक protocol, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक (*xfer_func)(काष्ठा i2c_adapter *adap, u16 addr,
			 अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
			 u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data);
	अचिन्हित दीर्घ orig_jअगरfies;
	पूर्णांक try;
	s32 res;

	res = __i2c_check_suspended(adapter);
	अगर (res)
		वापस res;

	/* If enabled, the following two tracepoपूर्णांकs are conditional on
	 * पढ़ो_ग_लिखो and protocol.
	 */
	trace_smbus_ग_लिखो(adapter, addr, flags, पढ़ो_ग_लिखो,
			  command, protocol, data);
	trace_smbus_पढ़ो(adapter, addr, flags, पढ़ो_ग_लिखो,
			 command, protocol);

	flags &= I2C_M_TEN | I2C_CLIENT_PEC | I2C_CLIENT_SCCB;

	xfer_func = adapter->algo->smbus_xfer;
	अगर (i2c_in_atomic_xfer_mode()) अणु
		अगर (adapter->algo->smbus_xfer_atomic)
			xfer_func = adapter->algo->smbus_xfer_atomic;
		अन्यथा अगर (adapter->algo->master_xfer_atomic)
			xfer_func = शून्य; /* fallback to I2C emulation */
	पूर्ण

	अगर (xfer_func) अणु
		/* Retry स्वतःmatically on arbitration loss */
		orig_jअगरfies = jअगरfies;
		क्रम (res = 0, try = 0; try <= adapter->retries; try++) अणु
			res = xfer_func(adapter, addr, flags, पढ़ो_ग_लिखो,
					command, protocol, data);
			अगर (res != -EAGAIN)
				अवरोध;
			अगर (समय_after(jअगरfies,
				       orig_jअगरfies + adapter->समयout))
				अवरोध;
		पूर्ण

		अगर (res != -EOPNOTSUPP || !adapter->algo->master_xfer)
			जाओ trace;
		/*
		 * Fall back to i2c_smbus_xfer_emulated अगर the adapter करोesn't
		 * implement native support क्रम the SMBus operation.
		 */
	पूर्ण

	res = i2c_smbus_xfer_emulated(adapter, addr, flags, पढ़ो_ग_लिखो,
				      command, protocol, data);

trace:
	/* If enabled, the reply tracepoपूर्णांक is conditional on पढ़ो_ग_लिखो. */
	trace_smbus_reply(adapter, addr, flags, पढ़ो_ग_लिखो,
			  command, protocol, data, res);
	trace_smbus_result(adapter, addr, flags, पढ़ो_ग_लिखो,
			   command, protocol, res);

	वापस res;
पूर्ण
EXPORT_SYMBOL(__i2c_smbus_xfer);

/**
 * i2c_smbus_पढ़ो_i2c_block_data_or_emulated - पढ़ो block or emulate
 * @client: Handle to slave device
 * @command: Byte पूर्णांकerpreted by slave
 * @length: Size of data block; SMBus allows at most I2C_SMBUS_BLOCK_MAX bytes
 * @values: Byte array पूर्णांकo which data will be पढ़ो; big enough to hold
 *	the data वापसed by the slave.  SMBus allows at most
 *	I2C_SMBUS_BLOCK_MAX bytes.
 *
 * This executes the SMBus "block read" protocol अगर supported by the adapter.
 * If block पढ़ो is not supported, it emulates it using either word or byte
 * पढ़ो protocols depending on availability.
 *
 * The addresses of the I2C slave device that are accessed with this function
 * must be mapped to a linear region, so that a block पढ़ो will have the same
 * effect as a byte पढ़ो. Beक्रमe using this function you must द्विगुन-check
 * अगर the I2C slave करोes support exchanging a block transfer with a byte
 * transfer.
 */
s32 i2c_smbus_पढ़ो_i2c_block_data_or_emulated(स्थिर काष्ठा i2c_client *client,
					      u8 command, u8 length, u8 *values)
अणु
	u8 i = 0;
	पूर्णांक status;

	अगर (length > I2C_SMBUS_BLOCK_MAX)
		length = I2C_SMBUS_BLOCK_MAX;

	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		वापस i2c_smbus_पढ़ो_i2c_block_data(client, command, length, values);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_BYTE_DATA))
		वापस -EOPNOTSUPP;

	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_WORD_DATA)) अणु
		जबतक ((i + 2) <= length) अणु
			status = i2c_smbus_पढ़ो_word_data(client, command + i);
			अगर (status < 0)
				वापस status;
			values[i] = status & 0xff;
			values[i + 1] = status >> 8;
			i += 2;
		पूर्ण
	पूर्ण

	जबतक (i < length) अणु
		status = i2c_smbus_पढ़ो_byte_data(client, command + i);
		अगर (status < 0)
			वापस status;
		values[i] = status;
		i++;
	पूर्ण

	वापस i;
पूर्ण
EXPORT_SYMBOL(i2c_smbus_पढ़ो_i2c_block_data_or_emulated);

/**
 * i2c_new_smbus_alert_device - get ara client क्रम SMBus alert support
 * @adapter: the target adapter
 * @setup: setup data क्रम the SMBus alert handler
 * Context: can sleep
 *
 * Setup handling of the SMBus alert protocol on a given I2C bus segment.
 *
 * Handling can be करोne either through our IRQ handler, or by the
 * adapter (from its handler, periodic polling, or whatever).
 *
 * This वापसs the ara client, which should be saved क्रम later use with
 * i2c_handle_smbus_alert() and ultimately i2c_unरेजिस्टर_device(); or an
 * ERRPTR to indicate an error.
 */
काष्ठा i2c_client *i2c_new_smbus_alert_device(काष्ठा i2c_adapter *adapter,
					      काष्ठा i2c_smbus_alert_setup *setup)
अणु
	काष्ठा i2c_board_info ara_board_info = अणु
		I2C_BOARD_INFO("smbus_alert", 0x0c),
		.platक्रमm_data = setup,
	पूर्ण;

	वापस i2c_new_client_device(adapter, &ara_board_info);
पूर्ण
EXPORT_SYMBOL_GPL(i2c_new_smbus_alert_device);

#अगर IS_ENABLED(CONFIG_I2C_SMBUS) && IS_ENABLED(CONFIG_OF)
पूर्णांक of_i2c_setup_smbus_alert(काष्ठा i2c_adapter *adapter)
अणु
	पूर्णांक irq;

	irq = of_property_match_string(adapter->dev.of_node, "interrupt-names",
				       "smbus_alert");
	अगर (irq == -EINVAL || irq == -ENODATA)
		वापस 0;
	अन्यथा अगर (irq < 0)
		वापस irq;

	वापस PTR_ERR_OR_ZERO(i2c_new_smbus_alert_device(adapter, शून्य));
पूर्ण
EXPORT_SYMBOL_GPL(of_i2c_setup_smbus_alert);
#पूर्ण_अगर
