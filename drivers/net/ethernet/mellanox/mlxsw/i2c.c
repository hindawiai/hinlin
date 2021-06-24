<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>

#समावेश "cmd.h"
#समावेश "core.h"
#समावेश "i2c.h"
#समावेश "resources.h"

#घोषणा MLXSW_I2C_CIR2_BASE		0x72000
#घोषणा MLXSW_I2C_CIR_STATUS_OFF	0x18
#घोषणा MLXSW_I2C_CIR2_OFF_STATUS	(MLXSW_I2C_CIR2_BASE + \
					 MLXSW_I2C_CIR_STATUS_OFF)
#घोषणा MLXSW_I2C_OPMOD_SHIFT		12
#घोषणा MLXSW_I2C_EVENT_BIT_SHIFT	22
#घोषणा MLXSW_I2C_GO_BIT_SHIFT		23
#घोषणा MLXSW_I2C_CIR_CTRL_STATUS_SHIFT	24
#घोषणा MLXSW_I2C_EVENT_BIT		BIT(MLXSW_I2C_EVENT_BIT_SHIFT)
#घोषणा MLXSW_I2C_GO_BIT		BIT(MLXSW_I2C_GO_BIT_SHIFT)
#घोषणा MLXSW_I2C_GO_OPMODE		BIT(MLXSW_I2C_OPMOD_SHIFT)
#घोषणा MLXSW_I2C_SET_IMM_CMD		(MLXSW_I2C_GO_OPMODE | \
					 MLXSW_CMD_OPCODE_QUERY_FW)
#घोषणा MLXSW_I2C_PUSH_IMM_CMD		(MLXSW_I2C_GO_BIT | \
					 MLXSW_I2C_SET_IMM_CMD)
#घोषणा MLXSW_I2C_SET_CMD		(MLXSW_CMD_OPCODE_ACCESS_REG)
#घोषणा MLXSW_I2C_PUSH_CMD		(MLXSW_I2C_GO_BIT | MLXSW_I2C_SET_CMD)
#घोषणा MLXSW_I2C_TLV_HDR_SIZE		0x10
#घोषणा MLXSW_I2C_ADDR_WIDTH		4
#घोषणा MLXSW_I2C_PUSH_CMD_SIZE		(MLXSW_I2C_ADDR_WIDTH + 4)
#घोषणा MLXSW_I2C_SET_EVENT_CMD		(MLXSW_I2C_EVENT_BIT)
#घोषणा MLXSW_I2C_PUSH_EVENT_CMD	(MLXSW_I2C_GO_BIT | \
					 MLXSW_I2C_SET_EVENT_CMD)
#घोषणा MLXSW_I2C_READ_SEMA_SIZE	4
#घोषणा MLXSW_I2C_PREP_SIZE		(MLXSW_I2C_ADDR_WIDTH + 28)
#घोषणा MLXSW_I2C_MBOX_SIZE		20
#घोषणा MLXSW_I2C_MBOX_OUT_PARAM_OFF	12
#घोषणा MLXSW_I2C_MBOX_OFFSET_BITS	20
#घोषणा MLXSW_I2C_MBOX_SIZE_BITS	12
#घोषणा MLXSW_I2C_ADDR_BUF_SIZE		4
#घोषणा MLXSW_I2C_BLK_DEF		32
#घोषणा MLXSW_I2C_RETRY			5
#घोषणा MLXSW_I2C_TIMEOUT_MSECS		5000
#घोषणा MLXSW_I2C_MAX_DATA_SIZE		256

/**
 * काष्ठा mlxsw_i2c - device निजी data:
 * @cmd: command attributes;
 * @cmd.mb_size_in: input mailbox size;
 * @cmd.mb_off_in: input mailbox offset in रेजिस्टर space;
 * @cmd.mb_size_out: output mailbox size;
 * @cmd.mb_off_out: output mailbox offset in रेजिस्टर space;
 * @cmd.lock: command execution lock;
 * @dev: I2C device;
 * @core: चयन core poपूर्णांकer;
 * @bus_info: bus info block;
 * @block_size: maximum block size allowed to pass to under layer;
 */
काष्ठा mlxsw_i2c अणु
	काष्ठा अणु
		u32 mb_size_in;
		u32 mb_off_in;
		u32 mb_size_out;
		u32 mb_off_out;
		काष्ठा mutex lock;
	पूर्ण cmd;
	काष्ठा device *dev;
	काष्ठा mlxsw_core *core;
	काष्ठा mlxsw_bus_info bus_info;
	u16 block_size;
पूर्ण;

#घोषणा MLXSW_I2C_READ_MSG(_client, _addr_buf, _buf, _len) अणु	\
	अणु .addr = (_client)->addr,				\
	  .buf = (_addr_buf),					\
	  .len = MLXSW_I2C_ADDR_BUF_SIZE,			\
	  .flags = 0 पूर्ण,						\
	अणु .addr = (_client)->addr,				\
	  .buf = (_buf),					\
	  .len = (_len),					\
	  .flags = I2C_M_RD पूर्ण पूर्ण

#घोषणा MLXSW_I2C_WRITE_MSG(_client, _buf, _len)		\
	अणु .addr = (_client)->addr,				\
	  .buf = (u8 *)(_buf),					\
	  .len = (_len),					\
	  .flags = 0 पूर्ण

/* Routine converts in and out mail boxes offset and size. */
अटल अंतरभूत व्योम
mlxsw_i2c_convert_mbox(काष्ठा mlxsw_i2c *mlxsw_i2c, u8 *buf)
अणु
	u32 पंचांगp;

	/* Local in/out mailboxes: 20 bits क्रम offset, 12 क्रम size */
	पंचांगp = be32_to_cpup((__be32 *) buf);
	mlxsw_i2c->cmd.mb_off_in = पंचांगp &
				   GENMASK(MLXSW_I2C_MBOX_OFFSET_BITS - 1, 0);
	mlxsw_i2c->cmd.mb_size_in = (पंचांगp & GENMASK(31,
					MLXSW_I2C_MBOX_OFFSET_BITS)) >>
					MLXSW_I2C_MBOX_OFFSET_BITS;

	पंचांगp = be32_to_cpup((__be32 *) (buf + MLXSW_I2C_ADDR_WIDTH));
	mlxsw_i2c->cmd.mb_off_out = पंचांगp &
				    GENMASK(MLXSW_I2C_MBOX_OFFSET_BITS - 1, 0);
	mlxsw_i2c->cmd.mb_size_out = (पंचांगp & GENMASK(31,
					MLXSW_I2C_MBOX_OFFSET_BITS)) >>
					MLXSW_I2C_MBOX_OFFSET_BITS;
पूर्ण

/* Routine obtains रेजिस्टर size from mail box buffer. */
अटल अंतरभूत पूर्णांक mlxsw_i2c_get_reg_size(u8 *in_mbox)
अणु
	u16  पंचांगp = be16_to_cpup((__be16 *) (in_mbox + MLXSW_I2C_TLV_HDR_SIZE));

	वापस (पंचांगp & 0x7ff) * 4 + MLXSW_I2C_TLV_HDR_SIZE;
पूर्ण

/* Routine sets I2C device पूर्णांकernal offset in the transaction buffer. */
अटल अंतरभूत व्योम mlxsw_i2c_set_slave_addr(u8 *buf, u32 off)
अणु
	__be32 *val = (__be32 *) buf;

	*val = htonl(off);
पूर्ण

/* Routine रुकोs until go bit is cleared. */
अटल पूर्णांक mlxsw_i2c_रुको_go_bit(काष्ठा i2c_client *client,
				 काष्ठा mlxsw_i2c *mlxsw_i2c, u8 *p_status)
अणु
	u8 addr_buf[MLXSW_I2C_ADDR_BUF_SIZE];
	u8 buf[MLXSW_I2C_READ_SEMA_SIZE];
	पूर्णांक len = MLXSW_I2C_READ_SEMA_SIZE;
	काष्ठा i2c_msg पढ़ो_sema[] =
		MLXSW_I2C_READ_MSG(client, addr_buf, buf, len);
	bool रुको_करोne = false;
	अचिन्हित दीर्घ end;
	पूर्णांक i = 0, err;

	mlxsw_i2c_set_slave_addr(addr_buf, MLXSW_I2C_CIR2_OFF_STATUS);

	end = jअगरfies + msecs_to_jअगरfies(MLXSW_I2C_TIMEOUT_MSECS);
	करो अणु
		u32 ctrl;

		err = i2c_transfer(client->adapter, पढ़ो_sema,
				   ARRAY_SIZE(पढ़ो_sema));

		ctrl = be32_to_cpu(*(__be32 *) buf);
		अगर (err == ARRAY_SIZE(पढ़ो_sema)) अणु
			अगर (!(ctrl & MLXSW_I2C_GO_BIT)) अणु
				रुको_करोne = true;
				*p_status = ctrl >>
					    MLXSW_I2C_CIR_CTRL_STATUS_SHIFT;
				अवरोध;
			पूर्ण
		पूर्ण
		cond_resched();
	पूर्ण जबतक ((समय_beक्रमe(jअगरfies, end)) || (i++ < MLXSW_I2C_RETRY));

	अगर (रुको_करोne) अणु
		अगर (*p_status)
			err = -EIO;
	पूर्ण अन्यथा अणु
		वापस -ETIMEDOUT;
	पूर्ण

	वापस err > 0 ? 0 : err;
पूर्ण

/* Routine posts a command to ASIC through mail box. */
अटल पूर्णांक mlxsw_i2c_ग_लिखो_cmd(काष्ठा i2c_client *client,
			       काष्ठा mlxsw_i2c *mlxsw_i2c,
			       पूर्णांक immediate)
अणु
	__be32 push_cmd_buf[MLXSW_I2C_PUSH_CMD_SIZE / 4] = अणु
		0, cpu_to_be32(MLXSW_I2C_PUSH_IMM_CMD)
	पूर्ण;
	__be32 prep_cmd_buf[MLXSW_I2C_PREP_SIZE / 4] = अणु
		0, 0, 0, 0, 0, 0,
		cpu_to_be32(client->adapter->nr & 0xffff),
		cpu_to_be32(MLXSW_I2C_SET_IMM_CMD)
	पूर्ण;
	काष्ठा i2c_msg push_cmd =
		MLXSW_I2C_WRITE_MSG(client, push_cmd_buf,
				    MLXSW_I2C_PUSH_CMD_SIZE);
	काष्ठा i2c_msg prep_cmd =
		MLXSW_I2C_WRITE_MSG(client, prep_cmd_buf, MLXSW_I2C_PREP_SIZE);
	पूर्णांक err;

	अगर (!immediate) अणु
		push_cmd_buf[1] = cpu_to_be32(MLXSW_I2C_PUSH_CMD);
		prep_cmd_buf[7] = cpu_to_be32(MLXSW_I2C_SET_CMD);
	पूर्ण
	mlxsw_i2c_set_slave_addr((u8 *)prep_cmd_buf,
				 MLXSW_I2C_CIR2_BASE);
	mlxsw_i2c_set_slave_addr((u8 *)push_cmd_buf,
				 MLXSW_I2C_CIR2_OFF_STATUS);

	/* Prepare Command Interface Register क्रम transaction */
	err = i2c_transfer(client->adapter, &prep_cmd, 1);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (err != 1)
		वापस -EIO;

	/* Write out Command Interface Register GO bit to push transaction */
	err = i2c_transfer(client->adapter, &push_cmd, 1);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (err != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

/* Routine posts initialization command to ASIC through mail box. */
अटल पूर्णांक
mlxsw_i2c_ग_लिखो_init_cmd(काष्ठा i2c_client *client,
			 काष्ठा mlxsw_i2c *mlxsw_i2c, u16 opcode, u32 in_mod)
अणु
	__be32 push_cmd_buf[MLXSW_I2C_PUSH_CMD_SIZE / 4] = अणु
		0, cpu_to_be32(MLXSW_I2C_PUSH_EVENT_CMD)
	पूर्ण;
	__be32 prep_cmd_buf[MLXSW_I2C_PREP_SIZE / 4] = अणु
		0, 0, 0, 0, 0, 0,
		cpu_to_be32(client->adapter->nr & 0xffff),
		cpu_to_be32(MLXSW_I2C_SET_EVENT_CMD)
	पूर्ण;
	काष्ठा i2c_msg push_cmd =
		MLXSW_I2C_WRITE_MSG(client, push_cmd_buf,
				    MLXSW_I2C_PUSH_CMD_SIZE);
	काष्ठा i2c_msg prep_cmd =
		MLXSW_I2C_WRITE_MSG(client, prep_cmd_buf, MLXSW_I2C_PREP_SIZE);
	u8 status;
	पूर्णांक err;

	push_cmd_buf[1] = cpu_to_be32(MLXSW_I2C_PUSH_EVENT_CMD | opcode);
	prep_cmd_buf[3] = cpu_to_be32(in_mod);
	prep_cmd_buf[7] = cpu_to_be32(MLXSW_I2C_GO_BIT | opcode);
	mlxsw_i2c_set_slave_addr((u8 *)prep_cmd_buf,
				 MLXSW_I2C_CIR2_BASE);
	mlxsw_i2c_set_slave_addr((u8 *)push_cmd_buf,
				 MLXSW_I2C_CIR2_OFF_STATUS);

	/* Prepare Command Interface Register क्रम transaction */
	err = i2c_transfer(client->adapter, &prep_cmd, 1);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (err != 1)
		वापस -EIO;

	/* Write out Command Interface Register GO bit to push transaction */
	err = i2c_transfer(client->adapter, &push_cmd, 1);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (err != 1)
		वापस -EIO;

	/* Wait until go bit is cleared. */
	err = mlxsw_i2c_रुको_go_bit(client, mlxsw_i2c, &status);
	अगर (err) अणु
		dev_err(&client->dev, "HW semaphore is not released");
		वापस err;
	पूर्ण

	/* Validate transaction completion status. */
	अगर (status) अणु
		dev_err(&client->dev, "Bad transaction completion status %x\n",
			status);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Routine obtains mail box offsets from ASIC रेजिस्टर space. */
अटल पूर्णांक mlxsw_i2c_get_mbox(काष्ठा i2c_client *client,
			      काष्ठा mlxsw_i2c *mlxsw_i2c)
अणु
	u8 addr_buf[MLXSW_I2C_ADDR_BUF_SIZE];
	u8 buf[MLXSW_I2C_MBOX_SIZE];
	काष्ठा i2c_msg mbox_cmd[] =
		MLXSW_I2C_READ_MSG(client, addr_buf, buf, MLXSW_I2C_MBOX_SIZE);
	पूर्णांक err;

	/* Read mail boxes offsets. */
	mlxsw_i2c_set_slave_addr(addr_buf, MLXSW_I2C_CIR2_BASE);
	err = i2c_transfer(client->adapter, mbox_cmd, 2);
	अगर (err != 2) अणु
		dev_err(&client->dev, "Could not obtain mail boxes\n");
		अगर (!err)
			वापस -EIO;
		अन्यथा
			वापस err;
	पूर्ण

	/* Convert mail boxes. */
	mlxsw_i2c_convert_mbox(mlxsw_i2c, &buf[MLXSW_I2C_MBOX_OUT_PARAM_OFF]);

	वापस err;
पूर्ण

/* Routine sends I2C ग_लिखो transaction to ASIC device. */
अटल पूर्णांक
mlxsw_i2c_ग_लिखो(काष्ठा device *dev, माप_प्रकार in_mbox_size, u8 *in_mbox, पूर्णांक num,
		u8 *p_status)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mlxsw_i2c *mlxsw_i2c = i2c_get_clientdata(client);
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(MLXSW_I2C_TIMEOUT_MSECS);
	पूर्णांक off = mlxsw_i2c->cmd.mb_off_in, chunk_size, i, j;
	अचिन्हित दीर्घ end;
	u8 *tran_buf;
	काष्ठा i2c_msg ग_लिखो_tran =
		MLXSW_I2C_WRITE_MSG(client, शून्य, MLXSW_I2C_PUSH_CMD_SIZE);
	पूर्णांक err;

	tran_buf = kदो_स्मृति(mlxsw_i2c->block_size + MLXSW_I2C_ADDR_BUF_SIZE,
			   GFP_KERNEL);
	अगर (!tran_buf)
		वापस -ENOMEM;

	ग_लिखो_tran.buf = tran_buf;
	क्रम (i = 0; i < num; i++) अणु
		chunk_size = (in_mbox_size > mlxsw_i2c->block_size) ?
			     mlxsw_i2c->block_size : in_mbox_size;
		ग_लिखो_tran.len = MLXSW_I2C_ADDR_WIDTH + chunk_size;
		mlxsw_i2c_set_slave_addr(tran_buf, off);
		स_नकल(&tran_buf[MLXSW_I2C_ADDR_BUF_SIZE], in_mbox +
		       mlxsw_i2c->block_size * i, chunk_size);

		j = 0;
		end = jअगरfies + समयout;
		करो अणु
			err = i2c_transfer(client->adapter, &ग_लिखो_tran, 1);
			अगर (err == 1)
				अवरोध;

			cond_resched();
		पूर्ण जबतक ((समय_beक्रमe(jअगरfies, end)) ||
			 (j++ < MLXSW_I2C_RETRY));

		अगर (err != 1) अणु
			अगर (!err) अणु
				err = -EIO;
				जाओ mlxsw_i2c_ग_लिखो_निकास;
			पूर्ण
		पूर्ण

		off += chunk_size;
		in_mbox_size -= chunk_size;
	पूर्ण

	/* Prepare and ग_लिखो out Command Interface Register क्रम transaction. */
	err = mlxsw_i2c_ग_लिखो_cmd(client, mlxsw_i2c, 0);
	अगर (err) अणु
		dev_err(&client->dev, "Could not start transaction");
		err = -EIO;
		जाओ mlxsw_i2c_ग_लिखो_निकास;
	पूर्ण

	/* Wait until go bit is cleared. */
	err = mlxsw_i2c_रुको_go_bit(client, mlxsw_i2c, p_status);
	अगर (err) अणु
		dev_err(&client->dev, "HW semaphore is not released");
		जाओ mlxsw_i2c_ग_लिखो_निकास;
	पूर्ण

	/* Validate transaction completion status. */
	अगर (*p_status) अणु
		dev_err(&client->dev, "Bad transaction completion status %x\n",
			*p_status);
		err = -EIO;
	पूर्ण

mlxsw_i2c_ग_लिखो_निकास:
	kमुक्त(tran_buf);
	वापस err;
पूर्ण

/* Routine executes I2C command. */
अटल पूर्णांक
mlxsw_i2c_cmd(काष्ठा device *dev, u16 opcode, u32 in_mod, माप_प्रकार in_mbox_size,
	      u8 *in_mbox, माप_प्रकार out_mbox_size, u8 *out_mbox, u8 *status)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mlxsw_i2c *mlxsw_i2c = i2c_get_clientdata(client);
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(MLXSW_I2C_TIMEOUT_MSECS);
	u8 tran_buf[MLXSW_I2C_ADDR_BUF_SIZE];
	पूर्णांक num, chunk_size, reg_size, i, j;
	पूर्णांक off = mlxsw_i2c->cmd.mb_off_out;
	अचिन्हित दीर्घ end;
	काष्ठा i2c_msg पढ़ो_tran[] =
		MLXSW_I2C_READ_MSG(client, tran_buf, शून्य, 0);
	पूर्णांक err;

	WARN_ON(in_mbox_size % माप(u32) || out_mbox_size % माप(u32));

	अगर (in_mbox) अणु
		reg_size = mlxsw_i2c_get_reg_size(in_mbox);
		num = reg_size / mlxsw_i2c->block_size;
		अगर (reg_size % mlxsw_i2c->block_size)
			num++;

		अगर (mutex_lock_पूर्णांकerruptible(&mlxsw_i2c->cmd.lock) < 0) अणु
			dev_err(&client->dev, "Could not acquire lock");
			वापस -EINVAL;
		पूर्ण

		err = mlxsw_i2c_ग_लिखो(dev, reg_size, in_mbox, num, status);
		अगर (err)
			जाओ cmd_fail;

		/* No out mailbox is हाल of ग_लिखो transaction. */
		अगर (!out_mbox) अणु
			mutex_unlock(&mlxsw_i2c->cmd.lock);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No input mailbox is हाल of initialization query command. */
		reg_size = MLXSW_I2C_MAX_DATA_SIZE;
		num = reg_size / mlxsw_i2c->block_size;

		अगर (mutex_lock_पूर्णांकerruptible(&mlxsw_i2c->cmd.lock) < 0) अणु
			dev_err(&client->dev, "Could not acquire lock");
			वापस -EINVAL;
		पूर्ण

		err = mlxsw_i2c_ग_लिखो_init_cmd(client, mlxsw_i2c, opcode,
					       in_mod);
		अगर (err)
			जाओ cmd_fail;
	पूर्ण

	/* Send पढ़ो transaction to get output mailbox content. */
	पढ़ो_tran[1].buf = out_mbox;
	क्रम (i = 0; i < num; i++) अणु
		chunk_size = (reg_size > mlxsw_i2c->block_size) ?
			     mlxsw_i2c->block_size : reg_size;
		पढ़ो_tran[1].len = chunk_size;
		mlxsw_i2c_set_slave_addr(tran_buf, off);

		j = 0;
		end = jअगरfies + समयout;
		करो अणु
			err = i2c_transfer(client->adapter, पढ़ो_tran,
					   ARRAY_SIZE(पढ़ो_tran));
			अगर (err == ARRAY_SIZE(पढ़ो_tran))
				अवरोध;

			cond_resched();
		पूर्ण जबतक ((समय_beक्रमe(jअगरfies, end)) ||
			 (j++ < MLXSW_I2C_RETRY));

		अगर (err != ARRAY_SIZE(पढ़ो_tran)) अणु
			अगर (!err)
				err = -EIO;

			जाओ cmd_fail;
		पूर्ण

		off += chunk_size;
		reg_size -= chunk_size;
		पढ़ो_tran[1].buf += chunk_size;
	पूर्ण

	mutex_unlock(&mlxsw_i2c->cmd.lock);

	वापस 0;

cmd_fail:
	mutex_unlock(&mlxsw_i2c->cmd.lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_i2c_cmd_exec(व्योम *bus_priv, u16 opcode, u8 opcode_mod,
			      u32 in_mod, bool out_mbox_direct,
			      अक्षर *in_mbox, माप_प्रकार in_mbox_size,
			      अक्षर *out_mbox, माप_प्रकार out_mbox_size,
			      u8 *status)
अणु
	काष्ठा mlxsw_i2c *mlxsw_i2c = bus_priv;

	वापस mlxsw_i2c_cmd(mlxsw_i2c->dev, opcode, in_mod, in_mbox_size,
			     in_mbox, out_mbox_size, out_mbox, status);
पूर्ण

अटल bool mlxsw_i2c_skb_transmit_busy(व्योम *bus_priv,
					स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक mlxsw_i2c_skb_transmit(व्योम *bus_priv, काष्ठा sk_buff *skb,
				  स्थिर काष्ठा mlxsw_tx_info *tx_info)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_i2c_init(व्योम *bus_priv, काष्ठा mlxsw_core *mlxsw_core,
	       स्थिर काष्ठा mlxsw_config_profile *profile,
	       काष्ठा mlxsw_res *res)
अणु
	काष्ठा mlxsw_i2c *mlxsw_i2c = bus_priv;
	अक्षर *mbox;
	पूर्णांक err;

	mlxsw_i2c->core = mlxsw_core;

	mbox = mlxsw_cmd_mbox_alloc();
	अगर (!mbox)
		वापस -ENOMEM;

	err = mlxsw_cmd_query_fw(mlxsw_core, mbox);
	अगर (err)
		जाओ mbox_put;

	mlxsw_i2c->bus_info.fw_rev.major =
		mlxsw_cmd_mbox_query_fw_fw_rev_major_get(mbox);
	mlxsw_i2c->bus_info.fw_rev.minor =
		mlxsw_cmd_mbox_query_fw_fw_rev_minor_get(mbox);
	mlxsw_i2c->bus_info.fw_rev.subminor =
		mlxsw_cmd_mbox_query_fw_fw_rev_subminor_get(mbox);

	err = mlxsw_core_resources_query(mlxsw_core, mbox, res);

mbox_put:
	mlxsw_cmd_mbox_मुक्त(mbox);
	वापस err;
पूर्ण

अटल व्योम mlxsw_i2c_fini(व्योम *bus_priv)
अणु
	काष्ठा mlxsw_i2c *mlxsw_i2c = bus_priv;

	mlxsw_i2c->core = शून्य;
पूर्ण

अटल स्थिर काष्ठा mlxsw_bus mlxsw_i2c_bus = अणु
	.kind			= "i2c",
	.init			= mlxsw_i2c_init,
	.fini			= mlxsw_i2c_fini,
	.skb_transmit_busy	= mlxsw_i2c_skb_transmit_busy,
	.skb_transmit		= mlxsw_i2c_skb_transmit,
	.cmd_exec		= mlxsw_i2c_cmd_exec,
पूर्ण;

अटल पूर्णांक mlxsw_i2c_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा i2c_adapter_quirks *quirks = client->adapter->quirks;
	काष्ठा mlxsw_i2c *mlxsw_i2c;
	u8 status;
	पूर्णांक err;

	mlxsw_i2c = devm_kzalloc(&client->dev, माप(*mlxsw_i2c), GFP_KERNEL);
	अगर (!mlxsw_i2c)
		वापस -ENOMEM;

	अगर (quirks) अणु
		अगर ((quirks->max_पढ़ो_len &&
		     quirks->max_पढ़ो_len < MLXSW_I2C_BLK_DEF) ||
		    (quirks->max_ग_लिखो_len &&
		     quirks->max_ग_लिखो_len < MLXSW_I2C_BLK_DEF)) अणु
			dev_err(&client->dev, "Insufficient transaction buffer length\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		mlxsw_i2c->block_size = max_t(u16, MLXSW_I2C_BLK_DEF,
					      min_t(u16, quirks->max_पढ़ो_len,
						    quirks->max_ग_लिखो_len));
	पूर्ण अन्यथा अणु
		mlxsw_i2c->block_size = MLXSW_I2C_BLK_DEF;
	पूर्ण

	i2c_set_clientdata(client, mlxsw_i2c);
	mutex_init(&mlxsw_i2c->cmd.lock);

	/* In order to use mailboxes through the i2c, special area is reserved
	 * on the i2c address space that can be used क्रम input and output
	 * mailboxes. Such mailboxes are called local mailboxes. When using a
	 * local mailbox, software should specअगरy 0 as the Input/Output
	 * parameters. The location of the Local Mailbox addresses on the i2c
	 * space can be retrieved through the QUERY_FW command.
	 * For this purpose QUERY_FW is to be issued with opcode modअगरier equal
	 * 0x01. For such command the output parameter is an immediate value.
	 * Here QUERY_FW command is invoked क्रम ASIC probing and क्रम getting
	 * local mailboxes addresses from immedate output parameters.
	 */

	/* Prepare and ग_लिखो out Command Interface Register क्रम transaction */
	err = mlxsw_i2c_ग_लिखो_cmd(client, mlxsw_i2c, 1);
	अगर (err) अणु
		dev_err(&client->dev, "Could not start transaction");
		जाओ errout;
	पूर्ण

	/* Wait until go bit is cleared. */
	err = mlxsw_i2c_रुको_go_bit(client, mlxsw_i2c, &status);
	अगर (err) अणु
		dev_err(&client->dev, "HW semaphore is not released");
		जाओ errout;
	पूर्ण

	/* Validate transaction completion status. */
	अगर (status) अणु
		dev_err(&client->dev, "Bad transaction completion status %x\n",
			status);
		err = -EIO;
		जाओ errout;
	पूर्ण

	/* Get mailbox offsets. */
	err = mlxsw_i2c_get_mbox(client, mlxsw_i2c);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Fail to get mailboxes\n");
		जाओ errout;
	पूर्ण

	dev_info(&client->dev, "%s mb size=%x off=0x%08x out mb size=%x off=0x%08x\n",
		 id->name, mlxsw_i2c->cmd.mb_size_in,
		 mlxsw_i2c->cmd.mb_off_in, mlxsw_i2c->cmd.mb_size_out,
		 mlxsw_i2c->cmd.mb_off_out);

	/* Register device bus. */
	mlxsw_i2c->bus_info.device_kind = id->name;
	mlxsw_i2c->bus_info.device_name = client->name;
	mlxsw_i2c->bus_info.dev = &client->dev;
	mlxsw_i2c->bus_info.low_frequency = true;
	mlxsw_i2c->dev = &client->dev;

	err = mlxsw_core_bus_device_रेजिस्टर(&mlxsw_i2c->bus_info,
					     &mlxsw_i2c_bus, mlxsw_i2c, false,
					     शून्य, शून्य);
	अगर (err) अणु
		dev_err(&client->dev, "Fail to register core bus\n");
		वापस err;
	पूर्ण

	वापस 0;

errout:
	i2c_set_clientdata(client, शून्य);

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mlxsw_i2c *mlxsw_i2c = i2c_get_clientdata(client);

	mlxsw_core_bus_device_unरेजिस्टर(mlxsw_i2c->core, false);
	mutex_destroy(&mlxsw_i2c->cmd.lock);

	वापस 0;
पूर्ण

पूर्णांक mlxsw_i2c_driver_रेजिस्टर(काष्ठा i2c_driver *i2c_driver)
अणु
	i2c_driver->probe = mlxsw_i2c_probe;
	i2c_driver->हटाओ = mlxsw_i2c_हटाओ;
	वापस i2c_add_driver(i2c_driver);
पूर्ण
EXPORT_SYMBOL(mlxsw_i2c_driver_रेजिस्टर);

व्योम mlxsw_i2c_driver_unरेजिस्टर(काष्ठा i2c_driver *i2c_driver)
अणु
	i2c_del_driver(i2c_driver);
पूर्ण
EXPORT_SYMBOL(mlxsw_i2c_driver_unरेजिस्टर);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Mellanox switch I2C interface driver");
MODULE_LICENSE("Dual BSD/GPL");
