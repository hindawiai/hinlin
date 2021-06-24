<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * An I2C driver क्रम the Intersil ISL 12026
 *
 * Copyright (c) 2018 Cavium, Inc.
 */
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

/* रेजिस्टर offsets */
#घोषणा ISL12026_REG_PWR	0x14
# define ISL12026_REG_PWR_BSW	BIT(6)
# define ISL12026_REG_PWR_SBIB	BIT(7)
#घोषणा ISL12026_REG_SC		0x30
#घोषणा ISL12026_REG_HR		0x32
# define ISL12026_REG_HR_MIL	BIT(7)	/* military or 24 hour समय */
#घोषणा ISL12026_REG_SR		0x3f
# define ISL12026_REG_SR_RTCF	BIT(0)
# define ISL12026_REG_SR_WEL	BIT(1)
# define ISL12026_REG_SR_RWEL	BIT(2)
# define ISL12026_REG_SR_MBZ	BIT(3)
# define ISL12026_REG_SR_OSCF	BIT(4)

/* The EEPROM array responds at i2c address 0x57 */
#घोषणा ISL12026_EEPROM_ADDR	0x57

#घोषणा ISL12026_PAGESIZE 16
#घोषणा ISL12026_NVMEM_WRITE_TIME 20

काष्ठा isl12026 अणु
	काष्ठा rtc_device *rtc;
	काष्ठा i2c_client *nvm_client;
पूर्ण;

अटल पूर्णांक isl12026_पढ़ो_reg(काष्ठा i2c_client *client, पूर्णांक reg)
अणु
	u8 addr[] = अणु0, regपूर्ण;
	u8 val;
	पूर्णांक ret;

	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.flags	= 0,
			.len	= माप(addr),
			.buf	= addr
		पूर्ण, अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
			.len	= 1,
			.buf	= &val
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(&client->dev, "read reg error, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
	पूर्ण अन्यथा अणु
		ret = val;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक isl12026_arm_ग_लिखो(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	u8 op[3];
	काष्ठा i2c_msg msg = अणु
		.addr	= client->addr,
		.flags	= 0,
		.len	= 1,
		.buf	= op
	पूर्ण;

	/* Set SR.WEL */
	op[0] = 0;
	op[1] = ISL12026_REG_SR;
	op[2] = ISL12026_REG_SR_WEL;
	msg.len = 3;
	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		dev_err(&client->dev, "write error SR.WEL, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण

	/* Set SR.WEL and SR.RWEL */
	op[2] = ISL12026_REG_SR_WEL | ISL12026_REG_SR_RWEL;
	msg.len = 3;
	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		dev_err(&client->dev,
			"write error SR.WEL|SR.RWEL, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक isl12026_disarm_ग_लिखो(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	u8 op[3] = अणु0, ISL12026_REG_SR, 0पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr	= client->addr,
		.flags	= 0,
		.len	= माप(op),
		.buf	= op
	पूर्ण;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		dev_err(&client->dev,
			"write error SR, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक isl12026_ग_लिखो_reg(काष्ठा i2c_client *client, पूर्णांक reg, u8 val)
अणु
	पूर्णांक ret;
	u8 op[3] = अणु0, reg, valपूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr	= client->addr,
		.flags	= 0,
		.len	= माप(op),
		.buf	= op
	पूर्ण;

	ret = isl12026_arm_ग_लिखो(client);
	अगर (ret)
		वापस ret;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		dev_err(&client->dev, "write error CCR, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण

	msleep(ISL12026_NVMEM_WRITE_TIME);

	ret = isl12026_disarm_ग_लिखो(client);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक isl12026_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;
	u8 op[10];
	काष्ठा i2c_msg msg = अणु
		.addr	= client->addr,
		.flags	= 0,
		.len	= माप(op),
		.buf	= op
	पूर्ण;

	ret = isl12026_arm_ग_लिखो(client);
	अगर (ret)
		वापस ret;

	/* Set the CCR रेजिस्टरs */
	op[0] = 0;
	op[1] = ISL12026_REG_SC;
	op[2] = bin2bcd(पंचांग->पंचांग_sec); /* SC */
	op[3] = bin2bcd(पंचांग->पंचांग_min); /* MN */
	op[4] = bin2bcd(पंचांग->पंचांग_hour) | ISL12026_REG_HR_MIL; /* HR */
	op[5] = bin2bcd(पंचांग->पंचांग_mday); /* DT */
	op[6] = bin2bcd(पंचांग->पंचांग_mon + 1); /* MO */
	op[7] = bin2bcd(पंचांग->पंचांग_year % 100); /* YR */
	op[8] = bin2bcd(पंचांग->पंचांग_wday & 7); /* DW */
	op[9] = bin2bcd(पंचांग->पंचांग_year >= 100 ? 20 : 19); /* Y2K */
	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret != 1) अणु
		dev_err(&client->dev, "write error CCR, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण

	ret = isl12026_disarm_ग_लिखो(client);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक isl12026_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 ccr[8];
	u8 addr[2];
	u8 sr;
	पूर्णांक ret;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= client->addr,
			.flags	= 0,
			.len	= माप(addr),
			.buf	= addr
		पूर्ण, अणु
			.addr	= client->addr,
			.flags	= I2C_M_RD,
		पूर्ण
	पूर्ण;

	/* First, पढ़ो SR */
	addr[0] = 0;
	addr[1] = ISL12026_REG_SR;
	msgs[1].len = 1;
	msgs[1].buf = &sr;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(&client->dev, "read error, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण

	अगर (sr & ISL12026_REG_SR_RTCF)
		dev_warn(&client->dev, "Real-Time Clock Failure on read\n");
	अगर (sr & ISL12026_REG_SR_OSCF)
		dev_warn(&client->dev, "Oscillator Failure on read\n");

	/* Second, CCR regs */
	addr[0] = 0;
	addr[1] = ISL12026_REG_SC;
	msgs[1].len = माप(ccr);
	msgs[1].buf = ccr;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(&client->dev, "read error, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(ccr[0] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(ccr[1] & 0x7F);
	अगर (ccr[2] & ISL12026_REG_HR_MIL)
		पंचांग->पंचांग_hour = bcd2bin(ccr[2] & 0x3F);
	अन्यथा
		पंचांग->पंचांग_hour = bcd2bin(ccr[2] & 0x1F) +
			((ccr[2] & 0x20) ? 12 : 0);
	पंचांग->पंचांग_mday = bcd2bin(ccr[3] & 0x3F);
	पंचांग->पंचांग_mon = bcd2bin(ccr[4] & 0x1F) - 1;
	पंचांग->पंचांग_year = bcd2bin(ccr[5]);
	अगर (bcd2bin(ccr[7]) == 20)
		पंचांग->पंचांग_year += 100;
	पंचांग->पंचांग_wday = ccr[6] & 0x07;

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops isl12026_rtc_ops = अणु
	.पढ़ो_समय	= isl12026_rtc_पढ़ो_समय,
	.set_समय	= isl12026_rtc_set_समय,
पूर्ण;

अटल पूर्णांक isl12026_nvm_पढ़ो(व्योम *p, अचिन्हित पूर्णांक offset,
			     व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा isl12026 *priv = p;
	पूर्णांक ret;
	u8 addr[2];
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= priv->nvm_client->addr,
			.flags	= 0,
			.len	= माप(addr),
			.buf	= addr
		पूर्ण, अणु
			.addr	= priv->nvm_client->addr,
			.flags	= I2C_M_RD,
			.buf	= val
		पूर्ण
	पूर्ण;

	/*
	 * offset and bytes checked and limited by nvmem core, so
	 * proceed without further checks.
	 */
	ret = mutex_lock_पूर्णांकerruptible(&priv->rtc->ops_lock);
	अगर (ret)
		वापस ret;

	/* 2 bytes of address, most signअगरicant first */
	addr[0] = offset >> 8;
	addr[1] = offset;
	msgs[1].len = bytes;
	ret = i2c_transfer(priv->nvm_client->adapter, msgs, ARRAY_SIZE(msgs));

	mutex_unlock(&priv->rtc->ops_lock);

	अगर (ret != ARRAY_SIZE(msgs)) अणु
		dev_err(&priv->nvm_client->dev,
			"nvmem read error, ret=%d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक isl12026_nvm_ग_लिखो(व्योम *p, अचिन्हित पूर्णांक offset,
			      व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा isl12026 *priv = p;
	पूर्णांक ret;
	u8 *v = val;
	माप_प्रकार chunk_size, num_written;
	u8 payload[ISL12026_PAGESIZE + 2]; /* page + 2 address bytes */
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= priv->nvm_client->addr,
			.flags	= 0,
			.buf	= payload
		पूर्ण
	पूर्ण;

	/*
	 * offset and bytes checked and limited by nvmem core, so
	 * proceed without further checks.
	 */
	ret = mutex_lock_पूर्णांकerruptible(&priv->rtc->ops_lock);
	अगर (ret)
		वापस ret;

	num_written = 0;
	जबतक (bytes) अणु
		chunk_size = round_करोwn(offset, ISL12026_PAGESIZE) +
			ISL12026_PAGESIZE - offset;
		chunk_size = min(bytes, chunk_size);
		/*
		 * 2 bytes of address, most signअगरicant first, followed
		 * by page data bytes
		 */
		स_नकल(payload + 2, v + num_written, chunk_size);
		payload[0] = offset >> 8;
		payload[1] = offset;
		msgs[0].len = chunk_size + 2;
		ret = i2c_transfer(priv->nvm_client->adapter,
				   msgs, ARRAY_SIZE(msgs));
		अगर (ret != ARRAY_SIZE(msgs)) अणु
			dev_err(&priv->nvm_client->dev,
				"nvmem write error, ret=%d\n", ret);
			ret = ret < 0 ? ret : -EIO;
			अवरोध;
		पूर्ण
		ret = 0;
		bytes -= chunk_size;
		offset += chunk_size;
		num_written += chunk_size;
		msleep(ISL12026_NVMEM_WRITE_TIME);
	पूर्ण

	mutex_unlock(&priv->rtc->ops_lock);

	वापस ret;
पूर्ण

अटल व्योम isl12026_क्रमce_घातer_modes(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	पूर्णांक pwr, requested_pwr;
	u32 bsw_val, sbib_val;
	bool set_bsw, set_sbib;

	/*
	 * If we can पढ़ो the of_property, set the specअगरied value.
	 * If there is an error पढ़ोing the of_property (likely
	 * because it करोes not exist), keep the current value.
	 */
	ret = of_property_पढ़ो_u32(client->dev.of_node,
				   "isil,pwr-bsw", &bsw_val);
	set_bsw = (ret == 0);

	ret = of_property_पढ़ो_u32(client->dev.of_node,
				   "isil,pwr-sbib", &sbib_val);
	set_sbib = (ret == 0);

	/* Check अगर PWR.BSW and/or PWR.SBIB need specअगरied values */
	अगर (!set_bsw && !set_sbib)
		वापस;

	pwr = isl12026_पढ़ो_reg(client, ISL12026_REG_PWR);
	अगर (pwr < 0) अणु
		dev_warn(&client->dev, "Error: Failed to read PWR %d\n", pwr);
		वापस;
	पूर्ण

	requested_pwr = pwr;

	अगर (set_bsw) अणु
		अगर (bsw_val)
			requested_pwr |= ISL12026_REG_PWR_BSW;
		अन्यथा
			requested_pwr &= ~ISL12026_REG_PWR_BSW;
	पूर्ण /* अन्यथा keep current BSW */

	अगर (set_sbib) अणु
		अगर (sbib_val)
			requested_pwr |= ISL12026_REG_PWR_SBIB;
		अन्यथा
			requested_pwr &= ~ISL12026_REG_PWR_SBIB;
	पूर्ण /* अन्यथा keep current SBIB */

	अगर (pwr >= 0 && pwr != requested_pwr) अणु
		dev_dbg(&client->dev, "PWR: %02x\n", pwr);
		dev_dbg(&client->dev, "Updating PWR to: %02x\n", requested_pwr);
		isl12026_ग_लिखो_reg(client, ISL12026_REG_PWR, requested_pwr);
	पूर्ण
पूर्ण

अटल पूर्णांक isl12026_probe_new(काष्ठा i2c_client *client)
अणु
	काष्ठा isl12026 *priv;
	पूर्णांक ret;
	काष्ठा nvmem_config nvm_cfg = अणु
		.name = "isl12026-",
		.base_dev = &client->dev,
		.stride = 1,
		.word_size = 1,
		.size = 512,
		.reg_पढ़ो = isl12026_nvm_पढ़ो,
		.reg_ग_लिखो = isl12026_nvm_ग_लिखो,
	पूर्ण;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	priv = devm_kzalloc(&client->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_clientdata(client, priv);

	isl12026_क्रमce_घातer_modes(client);

	priv->nvm_client = i2c_new_dummy_device(client->adapter, ISL12026_EEPROM_ADDR);
	अगर (IS_ERR(priv->nvm_client))
		वापस PTR_ERR(priv->nvm_client);

	priv->rtc = devm_rtc_allocate_device(&client->dev);
	ret = PTR_ERR_OR_ZERO(priv->rtc);
	अगर (ret)
		वापस ret;

	priv->rtc->ops = &isl12026_rtc_ops;
	nvm_cfg.priv = priv;
	ret = devm_rtc_nvmem_रेजिस्टर(priv->rtc, &nvm_cfg);
	अगर (ret)
		वापस ret;

	वापस devm_rtc_रेजिस्टर_device(priv->rtc);
पूर्ण

अटल पूर्णांक isl12026_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा isl12026 *priv = i2c_get_clientdata(client);

	i2c_unरेजिस्टर_device(priv->nvm_client);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id isl12026_dt_match[] = अणु
	अणु .compatible = "isil,isl12026" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, isl12026_dt_match);

अटल काष्ठा i2c_driver isl12026_driver = अणु
	.driver		= अणु
		.name	= "rtc-isl12026",
		.of_match_table = isl12026_dt_match,
	पूर्ण,
	.probe_new	= isl12026_probe_new,
	.हटाओ		= isl12026_हटाओ,
पूर्ण;

module_i2c_driver(isl12026_driver);

MODULE_DESCRIPTION("ISL 12026 RTC driver");
MODULE_LICENSE("GPL");
