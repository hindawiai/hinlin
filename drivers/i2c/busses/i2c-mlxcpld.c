<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*
 * Mellanox i2c driver
 *
 * Copyright (C) 2016-2020 Mellanox Technologies
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/mlxreg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* General defines */
#घोषणा MLXPLAT_CPLD_LPC_I2C_BASE_ADDR	0x2000
#घोषणा MLXCPLD_I2C_DEVICE_NAME		"i2c_mlxcpld"
#घोषणा MLXCPLD_I2C_VALID_FLAG		(I2C_M_RECV_LEN | I2C_M_RD)
#घोषणा MLXCPLD_I2C_BUS_NUM		1
#घोषणा MLXCPLD_I2C_DATA_REG_SZ		36
#घोषणा MLXCPLD_I2C_DATA_SZ_BIT		BIT(5)
#घोषणा MLXCPLD_I2C_DATA_SZ_MASK	GENMASK(6, 5)
#घोषणा MLXCPLD_I2C_SMBUS_BLK_BIT	BIT(7)
#घोषणा MLXCPLD_I2C_MAX_ADDR_LEN	4
#घोषणा MLXCPLD_I2C_RETR_NUM		2
#घोषणा MLXCPLD_I2C_XFER_TO		500000 /* usec */
#घोषणा MLXCPLD_I2C_POLL_TIME		400   /* usec */

/* LPC I2C रेजिस्टरs */
#घोषणा MLXCPLD_LPCI2C_CPBLTY_REG	0x0
#घोषणा MLXCPLD_LPCI2C_CTRL_REG		0x1
#घोषणा MLXCPLD_LPCI2C_HALF_CYC_REG	0x4
#घोषणा MLXCPLD_LPCI2C_I2C_HOLD_REG	0x5
#घोषणा MLXCPLD_LPCI2C_CMD_REG		0x6
#घोषणा MLXCPLD_LPCI2C_NUM_DAT_REG	0x7
#घोषणा MLXCPLD_LPCI2C_NUM_ADDR_REG	0x8
#घोषणा MLXCPLD_LPCI2C_STATUS_REG	0x9
#घोषणा MLXCPLD_LPCI2C_DATA_REG		0xa

/* LPC I2C masks and parametres */
#घोषणा MLXCPLD_LPCI2C_RST_SEL_MASK	0x1
#घोषणा MLXCPLD_LPCI2C_TRANS_END	0x1
#घोषणा MLXCPLD_LPCI2C_STATUS_NACK	0x10
#घोषणा MLXCPLD_LPCI2C_NO_IND		0
#घोषणा MLXCPLD_LPCI2C_ACK_IND		1
#घोषणा MLXCPLD_LPCI2C_NACK_IND		2

#घोषणा MLXCPLD_I2C_FREQ_1000KHZ_SET	0x04
#घोषणा MLXCPLD_I2C_FREQ_400KHZ_SET	0x0f
#घोषणा MLXCPLD_I2C_FREQ_100KHZ_SET	0x42

क्रमागत mlxcpld_i2c_frequency अणु
	MLXCPLD_I2C_FREQ_1000KHZ = 1,
	MLXCPLD_I2C_FREQ_400KHZ = 2,
	MLXCPLD_I2C_FREQ_100KHZ = 3,
पूर्ण;

काष्ठा  mlxcpld_i2c_curr_xfer अणु
	u8 cmd;
	u8 addr_width;
	u8 data_len;
	u8 msg_num;
	काष्ठा i2c_msg *msg;
पूर्ण;

काष्ठा mlxcpld_i2c_priv अणु
	काष्ठा i2c_adapter adap;
	u32 base_addr;
	काष्ठा mutex lock;
	काष्ठा  mlxcpld_i2c_curr_xfer xfer;
	काष्ठा device *dev;
	bool smbus_block;
पूर्ण;

अटल व्योम mlxcpld_i2c_lpc_ग_लिखो_buf(u8 *data, u8 len, u32 addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len - len % 4; i += 4)
		outl(*(u32 *)(data + i), addr + i);
	क्रम (; i < len; ++i)
		outb(*(data + i), addr + i);
पूर्ण

अटल व्योम mlxcpld_i2c_lpc_पढ़ो_buf(u8 *data, u8 len, u32 addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len - len % 4; i += 4)
		*(u32 *)(data + i) = inl(addr + i);
	क्रम (; i < len; ++i)
		*(data + i) = inb(addr + i);
पूर्ण

अटल व्योम mlxcpld_i2c_पढ़ो_comm(काष्ठा mlxcpld_i2c_priv *priv, u8 offs,
				  u8 *data, u8 datalen)
अणु
	u32 addr = priv->base_addr + offs;

	चयन (datalen) अणु
	हाल 1:
		*(data) = inb(addr);
		अवरोध;
	हाल 2:
		*((u16 *)data) = inw(addr);
		अवरोध;
	हाल 3:
		*((u16 *)data) = inw(addr);
		*(data + 2) = inb(addr + 2);
		अवरोध;
	हाल 4:
		*((u32 *)data) = inl(addr);
		अवरोध;
	शेष:
		mlxcpld_i2c_lpc_पढ़ो_buf(data, datalen, addr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxcpld_i2c_ग_लिखो_comm(काष्ठा mlxcpld_i2c_priv *priv, u8 offs,
				   u8 *data, u8 datalen)
अणु
	u32 addr = priv->base_addr + offs;

	चयन (datalen) अणु
	हाल 1:
		outb(*(data), addr);
		अवरोध;
	हाल 2:
		outw(*((u16 *)data), addr);
		अवरोध;
	हाल 3:
		outw(*((u16 *)data), addr);
		outb(*(data + 2), addr + 2);
		अवरोध;
	हाल 4:
		outl(*((u32 *)data), addr);
		अवरोध;
	शेष:
		mlxcpld_i2c_lpc_ग_लिखो_buf(data, datalen, addr);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Check validity of received i2c messages parameters.
 * Returns 0 अगर OK, other - in हाल of invalid parameters.
 */
अटल पूर्णांक mlxcpld_i2c_check_msg_params(काष्ठा mlxcpld_i2c_priv *priv,
					काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक i;

	अगर (!num) अणु
		dev_err(priv->dev, "Incorrect 0 num of messages\n");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(msgs[0].addr > 0x7f)) अणु
		dev_err(priv->dev, "Invalid address 0x%03x\n",
			msgs[0].addr);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num; ++i) अणु
		अगर (unlikely(!msgs[i].buf)) अणु
			dev_err(priv->dev, "Invalid buf in msg[%d]\n",
				i);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(msgs[0].addr != msgs[i].addr)) अणु
			dev_err(priv->dev, "Invalid addr in msg[%d]\n",
				i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check अगर transfer is completed and status of operation.
 * Returns 0 - transfer completed (both ACK or NACK),
 * negative - transfer isn't finished.
 */
अटल पूर्णांक mlxcpld_i2c_check_status(काष्ठा mlxcpld_i2c_priv *priv, पूर्णांक *status)
अणु
	u8 val;

	mlxcpld_i2c_पढ़ो_comm(priv, MLXCPLD_LPCI2C_STATUS_REG, &val, 1);

	अगर (val & MLXCPLD_LPCI2C_TRANS_END) अणु
		अगर (val & MLXCPLD_LPCI2C_STATUS_NACK)
			/*
			 * The slave is unable to accept the data. No such
			 * slave, command not understood, or unable to accept
			 * any more data.
			 */
			*status = MLXCPLD_LPCI2C_NACK_IND;
		अन्यथा
			*status = MLXCPLD_LPCI2C_ACK_IND;
		वापस 0;
	पूर्ण
	*status = MLXCPLD_LPCI2C_NO_IND;

	वापस -EIO;
पूर्ण

अटल व्योम mlxcpld_i2c_set_transf_data(काष्ठा mlxcpld_i2c_priv *priv,
					काष्ठा i2c_msg *msgs, पूर्णांक num,
					u8 comm_len)
अणु
	priv->xfer.msg = msgs;
	priv->xfer.msg_num = num;

	/*
	 * All upper layers currently are never use transfer with more than
	 * 2 messages. Actually, it's also not so relevant in Mellanox प्रणालीs
	 * because of HW limitation. Max size of transfer is not more than 32
	 * or 68 bytes in the current x86 LPCI2C bridge.
	 */
	priv->xfer.cmd = msgs[num - 1].flags & I2C_M_RD;

	अगर (priv->xfer.cmd == I2C_M_RD && comm_len != msgs[0].len) अणु
		priv->xfer.addr_width = msgs[0].len;
		priv->xfer.data_len = comm_len - priv->xfer.addr_width;
	पूर्ण अन्यथा अणु
		priv->xfer.addr_width = 0;
		priv->xfer.data_len = comm_len;
	पूर्ण
पूर्ण

/* Reset CPLD LPCI2C block */
अटल व्योम mlxcpld_i2c_reset(काष्ठा mlxcpld_i2c_priv *priv)
अणु
	u8 val;

	mutex_lock(&priv->lock);

	mlxcpld_i2c_पढ़ो_comm(priv, MLXCPLD_LPCI2C_CTRL_REG, &val, 1);
	val &= ~MLXCPLD_LPCI2C_RST_SEL_MASK;
	mlxcpld_i2c_ग_लिखो_comm(priv, MLXCPLD_LPCI2C_CTRL_REG, &val, 1);

	mutex_unlock(&priv->lock);
पूर्ण

/* Make sure the CPLD is पढ़ोy to start transmitting. */
अटल पूर्णांक mlxcpld_i2c_check_busy(काष्ठा mlxcpld_i2c_priv *priv)
अणु
	u8 val;

	mlxcpld_i2c_पढ़ो_comm(priv, MLXCPLD_LPCI2C_STATUS_REG, &val, 1);

	अगर (val & MLXCPLD_LPCI2C_TRANS_END)
		वापस 0;

	वापस -EIO;
पूर्ण

अटल पूर्णांक mlxcpld_i2c_रुको_क्रम_मुक्त(काष्ठा mlxcpld_i2c_priv *priv)
अणु
	पूर्णांक समयout = 0;

	करो अणु
		अगर (!mlxcpld_i2c_check_busy(priv))
			अवरोध;
		usleep_range(MLXCPLD_I2C_POLL_TIME / 2, MLXCPLD_I2C_POLL_TIME);
		समयout += MLXCPLD_I2C_POLL_TIME;
	पूर्ण जबतक (समयout <= MLXCPLD_I2C_XFER_TO);

	अगर (समयout > MLXCPLD_I2C_XFER_TO)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/*
 * Wait क्रम master transfer to complete.
 * It माला_दो current process to sleep until we get पूर्णांकerrupt or समयout expires.
 * Returns the number of transferred or पढ़ो bytes or error (<0).
 */
अटल पूर्णांक mlxcpld_i2c_रुको_क्रम_tc(काष्ठा mlxcpld_i2c_priv *priv)
अणु
	पूर्णांक status, i, समयout = 0;
	u8 datalen, val;

	करो अणु
		usleep_range(MLXCPLD_I2C_POLL_TIME / 2, MLXCPLD_I2C_POLL_TIME);
		अगर (!mlxcpld_i2c_check_status(priv, &status))
			अवरोध;
		समयout += MLXCPLD_I2C_POLL_TIME;
	पूर्ण जबतक (status == 0 && समयout < MLXCPLD_I2C_XFER_TO);

	चयन (status) अणु
	हाल MLXCPLD_LPCI2C_NO_IND:
		वापस -ETIMEDOUT;

	हाल MLXCPLD_LPCI2C_ACK_IND:
		अगर (priv->xfer.cmd != I2C_M_RD)
			वापस (priv->xfer.addr_width + priv->xfer.data_len);

		अगर (priv->xfer.msg_num == 1)
			i = 0;
		अन्यथा
			i = 1;

		अगर (!priv->xfer.msg[i].buf)
			वापस -EINVAL;

		/*
		 * Actual पढ़ो data len will be always the same as
		 * requested len. 0xff (line pull-up) will be वापसed
		 * अगर slave has no data to वापस. Thus करोn't पढ़ो
		 * MLXCPLD_LPCI2C_NUM_DAT_REG reg from CPLD.  Only in हाल of
		 * SMBus block पढ़ो transaction data len can be dअगरferent,
		 * check this हाल.
		 */
		mlxcpld_i2c_पढ़ो_comm(priv, MLXCPLD_LPCI2C_NUM_ADDR_REG, &val,
				      1);
		अगर (priv->smbus_block && (val & MLXCPLD_I2C_SMBUS_BLK_BIT)) अणु
			mlxcpld_i2c_पढ़ो_comm(priv, MLXCPLD_LPCI2C_NUM_DAT_REG,
					      &datalen, 1);
			अगर (unlikely(datalen > I2C_SMBUS_BLOCK_MAX)) अणु
				dev_err(priv->dev, "Incorrect smbus block read message len\n");
				वापस -EPROTO;
			पूर्ण
		पूर्ण अन्यथा अणु
			datalen = priv->xfer.data_len;
		पूर्ण

		mlxcpld_i2c_पढ़ो_comm(priv, MLXCPLD_LPCI2C_DATA_REG,
				      priv->xfer.msg[i].buf, datalen);

		वापस datalen;

	हाल MLXCPLD_LPCI2C_NACK_IND:
		वापस -ENXIO;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम mlxcpld_i2c_xfer_msg(काष्ठा mlxcpld_i2c_priv *priv)
अणु
	पूर्णांक i, len = 0;
	u8 cmd, val;

	mlxcpld_i2c_ग_लिखो_comm(priv, MLXCPLD_LPCI2C_NUM_DAT_REG,
			       &priv->xfer.data_len, 1);

	val = priv->xfer.addr_width;
	/* Notअगरy HW about SMBus block पढ़ो transaction */
	अगर (priv->smbus_block && priv->xfer.msg_num >= 2 &&
	    priv->xfer.msg[1].len == 1 &&
	    (priv->xfer.msg[1].flags & I2C_M_RECV_LEN) &&
	    (priv->xfer.msg[1].flags & I2C_M_RD))
		val |= MLXCPLD_I2C_SMBUS_BLK_BIT;

	mlxcpld_i2c_ग_लिखो_comm(priv, MLXCPLD_LPCI2C_NUM_ADDR_REG, &val, 1);

	क्रम (i = 0; i < priv->xfer.msg_num; i++) अणु
		अगर ((priv->xfer.msg[i].flags & I2C_M_RD) != I2C_M_RD) अणु
			/* Don't ग_लिखो to CPLD buffer in पढ़ो transaction */
			mlxcpld_i2c_ग_लिखो_comm(priv, MLXCPLD_LPCI2C_DATA_REG +
					       len, priv->xfer.msg[i].buf,
					       priv->xfer.msg[i].len);
			len += priv->xfer.msg[i].len;
		पूर्ण
	पूर्ण

	/*
	 * Set target slave address with command क्रम master transfer.
	 * It should be latest executed function beक्रमe CPLD transaction.
	 */
	cmd = (priv->xfer.msg[0].addr << 1) | priv->xfer.cmd;
	mlxcpld_i2c_ग_लिखो_comm(priv, MLXCPLD_LPCI2C_CMD_REG, &cmd, 1);
पूर्ण

/*
 * Generic lpc-i2c transfer.
 * Returns the number of processed messages or error (<0).
 */
अटल पूर्णांक mlxcpld_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			    पूर्णांक num)
अणु
	काष्ठा mlxcpld_i2c_priv *priv = i2c_get_adapdata(adap);
	u8 comm_len = 0;
	पूर्णांक i, err;

	err = mlxcpld_i2c_check_msg_params(priv, msgs, num);
	अगर (err) अणु
		dev_err(priv->dev, "Incorrect message\n");
		वापस err;
	पूर्ण

	क्रम (i = 0; i < num; ++i)
		comm_len += msgs[i].len;

	/* Check bus state */
	अगर (mlxcpld_i2c_रुको_क्रम_मुक्त(priv)) अणु
		dev_err(priv->dev, "LPCI2C bridge is busy\n");

		/*
		 * Usually it means something serious has happened.
		 * We can not have unfinished previous transfer
		 * so it करोesn't make any sense to try to stop it.
		 * Probably we were not able to recover from the
		 * previous error.
		 * The only reasonable thing - is soft reset.
		 */
		mlxcpld_i2c_reset(priv);
		अगर (mlxcpld_i2c_check_busy(priv)) अणु
			dev_err(priv->dev, "LPCI2C bridge is busy after reset\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	mlxcpld_i2c_set_transf_data(priv, msgs, num, comm_len);

	mutex_lock(&priv->lock);

	/* Do real transfer. Can't fail */
	mlxcpld_i2c_xfer_msg(priv);

	/* Wait क्रम transaction complete */
	err = mlxcpld_i2c_रुको_क्रम_tc(priv);

	mutex_unlock(&priv->lock);

	वापस err < 0 ? err : num;
पूर्ण

अटल u32 mlxcpld_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा mlxcpld_i2c_priv *priv = i2c_get_adapdata(adap);

	अगर (priv->smbus_block)
		वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
			I2C_FUNC_SMBUS_I2C_BLOCK | I2C_FUNC_SMBUS_BLOCK_DATA;
	अन्यथा
		वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
			I2C_FUNC_SMBUS_I2C_BLOCK;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mlxcpld_i2c_algo = अणु
	.master_xfer	= mlxcpld_i2c_xfer,
	.functionality	= mlxcpld_i2c_func
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks mlxcpld_i2c_quirks = अणु
	.flags = I2C_AQ_COMB_WRITE_THEN_READ,
	.max_पढ़ो_len = MLXCPLD_I2C_DATA_REG_SZ - MLXCPLD_I2C_MAX_ADDR_LEN,
	.max_ग_लिखो_len = MLXCPLD_I2C_DATA_REG_SZ,
	.max_comb_1st_msg_len = 4,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter_quirks mlxcpld_i2c_quirks_ext = अणु
	.flags = I2C_AQ_COMB_WRITE_THEN_READ,
	.max_पढ़ो_len = MLXCPLD_I2C_DATA_REG_SZ * 2 - MLXCPLD_I2C_MAX_ADDR_LEN,
	.max_ग_लिखो_len = MLXCPLD_I2C_DATA_REG_SZ * 2,
	.max_comb_1st_msg_len = 4,
पूर्ण;

अटल काष्ठा i2c_adapter mlxcpld_i2c_adapter = अणु
	.owner          = THIS_MODULE,
	.name           = "i2c-mlxcpld",
	.class          = I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo           = &mlxcpld_i2c_algo,
	.quirks		= &mlxcpld_i2c_quirks,
	.retries	= MLXCPLD_I2C_RETR_NUM,
	.nr		= MLXCPLD_I2C_BUS_NUM,
पूर्ण;

अटल पूर्णांक
mlxcpld_i2c_set_frequency(काष्ठा mlxcpld_i2c_priv *priv,
			  काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata)
अणु
	काष्ठा mlxreg_core_item *item = pdata->items;
	काष्ठा mlxreg_core_data *data;
	u32 regval;
	u8 freq;
	पूर्णांक err;

	अगर (!item)
		वापस 0;

	/* Read frequency setting. */
	data = item->data;
	err = regmap_पढ़ो(pdata->regmap, data->reg, &regval);
	अगर (err)
		वापस err;

	/* Set frequency only अगर it is not 100KHz, which is शेष. */
	चयन ((data->reg & data->mask) >> data->bit) अणु
	हाल MLXCPLD_I2C_FREQ_1000KHZ:
		freq = MLXCPLD_I2C_FREQ_1000KHZ_SET;
		अवरोध;
	हाल MLXCPLD_I2C_FREQ_400KHZ:
		freq = MLXCPLD_I2C_FREQ_400KHZ_SET;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	mlxcpld_i2c_ग_लिखो_comm(priv, MLXCPLD_LPCI2C_HALF_CYC_REG, &freq, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxcpld_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxreg_core_hotplug_platक्रमm_data *pdata;
	काष्ठा mlxcpld_i2c_priv *priv;
	पूर्णांक err;
	u8 val;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	mutex_init(&priv->lock);
	platक्रमm_set_drvdata(pdev, priv);

	priv->dev = &pdev->dev;
	priv->base_addr = MLXPLAT_CPLD_LPC_I2C_BASE_ADDR;

	/* Set I2C bus frequency अगर platक्रमm data provides this info. */
	pdata = dev_get_platdata(&pdev->dev);
	अगर (pdata) अणु
		err = mlxcpld_i2c_set_frequency(priv, pdata);
		अगर (err)
			जाओ mlxcpld_i2_probe_failed;
	पूर्ण

	/* Register with i2c layer */
	mlxcpld_i2c_adapter.समयout = usecs_to_jअगरfies(MLXCPLD_I2C_XFER_TO);
	/* Read capability रेजिस्टर */
	mlxcpld_i2c_पढ़ो_comm(priv, MLXCPLD_LPCI2C_CPBLTY_REG, &val, 1);
	/* Check support क्रम extended transaction length */
	अगर ((val & MLXCPLD_I2C_DATA_SZ_MASK) == MLXCPLD_I2C_DATA_SZ_BIT)
		mlxcpld_i2c_adapter.quirks = &mlxcpld_i2c_quirks_ext;
	/* Check support क्रम smbus block transaction */
	अगर (val & MLXCPLD_I2C_SMBUS_BLK_BIT)
		priv->smbus_block = true;
	अगर (pdev->id >= -1)
		mlxcpld_i2c_adapter.nr = pdev->id;
	priv->adap = mlxcpld_i2c_adapter;
	priv->adap.dev.parent = &pdev->dev;
	i2c_set_adapdata(&priv->adap, priv);

	err = i2c_add_numbered_adapter(&priv->adap);
	अगर (err)
		जाओ mlxcpld_i2_probe_failed;

	वापस 0;

mlxcpld_i2_probe_failed:
	mutex_destroy(&priv->lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlxcpld_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxcpld_i2c_priv *priv = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&priv->adap);
	mutex_destroy(&priv->lock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxcpld_i2c_driver = अणु
	.probe		= mlxcpld_i2c_probe,
	.हटाओ		= mlxcpld_i2c_हटाओ,
	.driver = अणु
		.name = MLXCPLD_I2C_DEVICE_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mlxcpld_i2c_driver);

MODULE_AUTHOR("Michael Shych <michaels@mellanox.com>");
MODULE_DESCRIPTION("Mellanox I2C-CPLD controller driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:i2c-mlxcpld");
