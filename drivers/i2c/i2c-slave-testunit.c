<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C slave mode testunit
 *
 * Copyright (C) 2020 by Wolfram Sang, Sang Engineering <wsa@sang-engineering.com>
 * Copyright (C) 2020 by Renesas Electronics Corporation
 */

#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h> /* FIXME: is प्रणाली_दीर्घ_wq the best choice? */

#घोषणा TU_CUR_VERSION 0x01

क्रमागत testunit_cmds अणु
	TU_CMD_READ_BYTES = 1,	/* save 0 क्रम ABORT, RESET or similar */
	TU_CMD_HOST_NOTIFY,
	TU_CMD_SMBUS_BLOCK_PROC_CALL,
	TU_NUM_CMDS
पूर्ण;

क्रमागत testunit_regs अणु
	TU_REG_CMD,
	TU_REG_DATAL,
	TU_REG_DATAH,
	TU_REG_DELAY,
	TU_NUM_REGS
पूर्ण;

क्रमागत testunit_flags अणु
	TU_FLAG_IN_PROCESS,
पूर्ण;

काष्ठा testunit_data अणु
	अचिन्हित दीर्घ flags;
	u8 regs[TU_NUM_REGS];
	u8 reg_idx;
	काष्ठा i2c_client *client;
	काष्ठा delayed_work worker;
पूर्ण;

अटल व्योम i2c_slave_testunit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा testunit_data *tu = container_of(work, काष्ठा testunit_data, worker.work);
	काष्ठा i2c_msg msg;
	u8 msgbuf[256];
	पूर्णांक ret = 0;

	msg.addr = I2C_CLIENT_END;
	msg.buf = msgbuf;

	चयन (tu->regs[TU_REG_CMD]) अणु
	हाल TU_CMD_READ_BYTES:
		msg.addr = tu->regs[TU_REG_DATAL];
		msg.flags = I2C_M_RD;
		msg.len = tu->regs[TU_REG_DATAH];
		अवरोध;

	हाल TU_CMD_HOST_NOTIFY:
		msg.addr = 0x08;
		msg.flags = 0;
		msg.len = 3;
		msgbuf[0] = tu->client->addr;
		msgbuf[1] = tu->regs[TU_REG_DATAL];
		msgbuf[2] = tu->regs[TU_REG_DATAH];
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (msg.addr != I2C_CLIENT_END) अणु
		ret = i2c_transfer(tu->client->adapter, &msg, 1);
		/* convert '0 msgs transferred' to त्रुटि_सं */
		ret = (ret == 0) ? -EIO : ret;
	पूर्ण

	अगर (ret < 0)
		dev_err(&tu->client->dev, "CMD%02X failed (%d)\n", tu->regs[TU_REG_CMD], ret);

	clear_bit(TU_FLAG_IN_PROCESS, &tu->flags);
पूर्ण

अटल पूर्णांक i2c_slave_testunit_slave_cb(काष्ठा i2c_client *client,
				     क्रमागत i2c_slave_event event, u8 *val)
अणु
	काष्ठा testunit_data *tu = i2c_get_clientdata(client);
	bool is_proc_call = tu->reg_idx == 3 && tu->regs[TU_REG_DATAL] == 1 &&
			    tu->regs[TU_REG_CMD] == TU_CMD_SMBUS_BLOCK_PROC_CALL;
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल I2C_SLAVE_WRITE_RECEIVED:
		अगर (test_bit(TU_FLAG_IN_PROCESS, &tu->flags))
			वापस -EBUSY;

		अगर (tu->reg_idx < TU_NUM_REGS)
			tu->regs[tu->reg_idx] = *val;
		अन्यथा
			ret = -EMSGSIZE;

		अगर (tu->reg_idx <= TU_NUM_REGS)
			tu->reg_idx++;

		/* TU_REG_CMD always written at this poपूर्णांक */
		अगर (tu->regs[TU_REG_CMD] >= TU_NUM_CMDS)
			ret = -EINVAL;

		अवरोध;

	हाल I2C_SLAVE_STOP:
		अगर (tu->reg_idx == TU_NUM_REGS) अणु
			set_bit(TU_FLAG_IN_PROCESS, &tu->flags);
			queue_delayed_work(प्रणाली_दीर्घ_wq, &tu->worker,
					   msecs_to_jअगरfies(10 * tu->regs[TU_REG_DELAY]));
		पूर्ण
		fallthrough;

	हाल I2C_SLAVE_WRITE_REQUESTED:
		स_रखो(tu->regs, 0, TU_NUM_REGS);
		tu->reg_idx = 0;
		अवरोध;

	हाल I2C_SLAVE_READ_PROCESSED:
		अगर (is_proc_call && tu->regs[TU_REG_DATAH])
			tu->regs[TU_REG_DATAH]--;
		fallthrough;

	हाल I2C_SLAVE_READ_REQUESTED:
		*val = is_proc_call ? tu->regs[TU_REG_DATAH] : TU_CUR_VERSION;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_slave_testunit_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा testunit_data *tu;

	tu = devm_kzalloc(&client->dev, माप(काष्ठा testunit_data), GFP_KERNEL);
	अगर (!tu)
		वापस -ENOMEM;

	tu->client = client;
	i2c_set_clientdata(client, tu);
	INIT_DELAYED_WORK(&tu->worker, i2c_slave_testunit_work);

	वापस i2c_slave_रेजिस्टर(client, i2c_slave_testunit_slave_cb);
पूर्ण;

अटल पूर्णांक i2c_slave_testunit_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा testunit_data *tu = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&tu->worker);
	i2c_slave_unरेजिस्टर(client);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id i2c_slave_testunit_id[] = अणु
	अणु "slave-testunit", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, i2c_slave_testunit_id);

अटल काष्ठा i2c_driver i2c_slave_testunit_driver = अणु
	.driver = अणु
		.name = "i2c-slave-testunit",
	पूर्ण,
	.probe_new = i2c_slave_testunit_probe,
	.हटाओ = i2c_slave_testunit_हटाओ,
	.id_table = i2c_slave_testunit_id,
पूर्ण;
module_i2c_driver(i2c_slave_testunit_driver);

MODULE_AUTHOR("Wolfram Sang <wsa@sang-engineering.com>");
MODULE_DESCRIPTION("I2C slave mode test unit");
MODULE_LICENSE("GPL v2");
