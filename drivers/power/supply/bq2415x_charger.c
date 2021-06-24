<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * bq2415x अक्षरger driver
 *
 * Copyright (C) 2011-2013  Pali Rohथँr <pali@kernel.org>
 *
 * Datasheets:
 * https://www.ti.com/product/bq24150
 * https://www.ti.com/product/bq24150a
 * https://www.ti.com/product/bq24152
 * https://www.ti.com/product/bq24153
 * https://www.ti.com/product/bq24153a
 * https://www.ti.com/product/bq24155
 * https://www.ti.com/product/bq24157s
 * https://www.ti.com/product/bq24158
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/err.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/idr.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>

#समावेश <linux/घातer/bq2415x_अक्षरger.h>

/* समयout क्रम resetting chip समयr */
#घोषणा BQ2415X_TIMER_TIMEOUT		10

#घोषणा BQ2415X_REG_STATUS		0x00
#घोषणा BQ2415X_REG_CONTROL		0x01
#घोषणा BQ2415X_REG_VOLTAGE		0x02
#घोषणा BQ2415X_REG_VENDER		0x03
#घोषणा BQ2415X_REG_CURRENT		0x04

/* reset state क्रम all रेजिस्टरs */
#घोषणा BQ2415X_RESET_STATUS		BIT(6)
#घोषणा BQ2415X_RESET_CONTROL		(BIT(4)|BIT(5))
#घोषणा BQ2415X_RESET_VOLTAGE		(BIT(1)|BIT(3))
#घोषणा BQ2415X_RESET_CURRENT		(BIT(0)|BIT(3)|BIT(7))

/* status रेजिस्टर */
#घोषणा BQ2415X_BIT_TMR_RST		7
#घोषणा BQ2415X_BIT_OTG			7
#घोषणा BQ2415X_BIT_EN_STAT		6
#घोषणा BQ2415X_MASK_STAT		(BIT(4)|BIT(5))
#घोषणा BQ2415X_SHIFT_STAT		4
#घोषणा BQ2415X_BIT_BOOST		3
#घोषणा BQ2415X_MASK_FAULT		(BIT(0)|BIT(1)|BIT(2))
#घोषणा BQ2415X_SHIFT_FAULT		0

/* control रेजिस्टर */
#घोषणा BQ2415X_MASK_LIMIT		(BIT(6)|BIT(7))
#घोषणा BQ2415X_SHIFT_LIMIT		6
#घोषणा BQ2415X_MASK_VLOWV		(BIT(4)|BIT(5))
#घोषणा BQ2415X_SHIFT_VLOWV		4
#घोषणा BQ2415X_BIT_TE			3
#घोषणा BQ2415X_BIT_CE			2
#घोषणा BQ2415X_BIT_HZ_MODE		1
#घोषणा BQ2415X_BIT_OPA_MODE		0

/* voltage रेजिस्टर */
#घोषणा BQ2415X_MASK_VO		(BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7))
#घोषणा BQ2415X_SHIFT_VO		2
#घोषणा BQ2415X_BIT_OTG_PL		1
#घोषणा BQ2415X_BIT_OTG_EN		0

/* vender रेजिस्टर */
#घोषणा BQ2415X_MASK_VENDER		(BIT(5)|BIT(6)|BIT(7))
#घोषणा BQ2415X_SHIFT_VENDER		5
#घोषणा BQ2415X_MASK_PN			(BIT(3)|BIT(4))
#घोषणा BQ2415X_SHIFT_PN		3
#घोषणा BQ2415X_MASK_REVISION		(BIT(0)|BIT(1)|BIT(2))
#घोषणा BQ2415X_SHIFT_REVISION		0

/* current रेजिस्टर */
#घोषणा BQ2415X_MASK_RESET		BIT(7)
#घोषणा BQ2415X_MASK_VI_CHRG		(BIT(4)|BIT(5)|BIT(6))
#घोषणा BQ2415X_SHIFT_VI_CHRG		4
/* N/A					BIT(3) */
#घोषणा BQ2415X_MASK_VI_TERM		(BIT(0)|BIT(1)|BIT(2))
#घोषणा BQ2415X_SHIFT_VI_TERM		0


क्रमागत bq2415x_command अणु
	BQ2415X_TIMER_RESET,
	BQ2415X_OTG_STATUS,
	BQ2415X_STAT_PIN_STATUS,
	BQ2415X_STAT_PIN_ENABLE,
	BQ2415X_STAT_PIN_DISABLE,
	BQ2415X_CHARGE_STATUS,
	BQ2415X_BOOST_STATUS,
	BQ2415X_FAULT_STATUS,

	BQ2415X_CHARGE_TERMINATION_STATUS,
	BQ2415X_CHARGE_TERMINATION_ENABLE,
	BQ2415X_CHARGE_TERMINATION_DISABLE,
	BQ2415X_CHARGER_STATUS,
	BQ2415X_CHARGER_ENABLE,
	BQ2415X_CHARGER_DISABLE,
	BQ2415X_HIGH_IMPEDANCE_STATUS,
	BQ2415X_HIGH_IMPEDANCE_ENABLE,
	BQ2415X_HIGH_IMPEDANCE_DISABLE,
	BQ2415X_BOOST_MODE_STATUS,
	BQ2415X_BOOST_MODE_ENABLE,
	BQ2415X_BOOST_MODE_DISABLE,

	BQ2415X_OTG_LEVEL,
	BQ2415X_OTG_ACTIVATE_HIGH,
	BQ2415X_OTG_ACTIVATE_LOW,
	BQ2415X_OTG_PIN_STATUS,
	BQ2415X_OTG_PIN_ENABLE,
	BQ2415X_OTG_PIN_DISABLE,

	BQ2415X_VENDER_CODE,
	BQ2415X_PART_NUMBER,
	BQ2415X_REVISION,
पूर्ण;

क्रमागत bq2415x_chip अणु
	BQUNKNOWN,
	BQ24150,
	BQ24150A,
	BQ24151,
	BQ24151A,
	BQ24152,
	BQ24153,
	BQ24153A,
	BQ24155,
	BQ24156,
	BQ24156A,
	BQ24157S,
	BQ24158,
पूर्ण;

अटल अक्षर *bq2415x_chip_name[] = अणु
	"unknown",
	"bq24150",
	"bq24150a",
	"bq24151",
	"bq24151a",
	"bq24152",
	"bq24153",
	"bq24153a",
	"bq24155",
	"bq24156",
	"bq24156a",
	"bq24157s",
	"bq24158",
पूर्ण;

काष्ठा bq2415x_device अणु
	काष्ठा device *dev;
	काष्ठा bq2415x_platक्रमm_data init_data;
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply_desc अक्षरger_desc;
	काष्ठा delayed_work work;
	काष्ठा device_node *notअगरy_node;
	काष्ठा notअगरier_block nb;
	क्रमागत bq2415x_mode reported_mode;/* mode reported by hook function */
	क्रमागत bq2415x_mode mode;		/* currently configured mode */
	क्रमागत bq2415x_chip chip;
	स्थिर अक्षर *समयr_error;
	अक्षर *model;
	अक्षर *name;
	पूर्णांक स्वतःसमयr;	/* 1 - अगर driver स्वतःmatically reset समयr, 0 - not */
	पूर्णांक स्वतःmode;	/* 1 - enabled, 0 - disabled; -1 - not supported */
	पूर्णांक id;
पूर्ण;

/* each रेजिस्टरed chip must have unique id */
अटल DEFINE_IDR(bq2415x_id);

अटल DEFINE_MUTEX(bq2415x_id_mutex);
अटल DEFINE_MUTEX(bq2415x_समयr_mutex);
अटल DEFINE_MUTEX(bq2415x_i2c_mutex);

/**** i2c पढ़ो functions ****/

/* पढ़ो value from रेजिस्टर */
अटल पूर्णांक bq2415x_i2c_पढ़ो(काष्ठा bq2415x_device *bq, u8 reg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(bq->dev);
	काष्ठा i2c_msg msg[2];
	u8 val;
	पूर्णांक ret;

	अगर (!client->adapter)
		वापस -ENODEV;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].buf = &reg;
	msg[0].len = माप(reg);
	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = &val;
	msg[1].len = माप(val);

	mutex_lock(&bq2415x_i2c_mutex);
	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	mutex_unlock(&bq2415x_i2c_mutex);

	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

/* पढ़ो value from रेजिस्टर, apply mask and right shअगरt it */
अटल पूर्णांक bq2415x_i2c_पढ़ो_mask(काष्ठा bq2415x_device *bq, u8 reg,
				 u8 mask, u8 shअगरt)
अणु
	पूर्णांक ret;

	अगर (shअगरt > 8)
		वापस -EINVAL;

	ret = bq2415x_i2c_पढ़ो(bq, reg);
	अगर (ret < 0)
		वापस ret;
	वापस (ret & mask) >> shअगरt;
पूर्ण

/* पढ़ो value from रेजिस्टर and वापस one specअगरied bit */
अटल पूर्णांक bq2415x_i2c_पढ़ो_bit(काष्ठा bq2415x_device *bq, u8 reg, u8 bit)
अणु
	अगर (bit > 8)
		वापस -EINVAL;
	वापस bq2415x_i2c_पढ़ो_mask(bq, reg, BIT(bit), bit);
पूर्ण

/**** i2c ग_लिखो functions ****/

/* ग_लिखो value to रेजिस्टर */
अटल पूर्णांक bq2415x_i2c_ग_लिखो(काष्ठा bq2415x_device *bq, u8 reg, u8 val)
अणु
	काष्ठा i2c_client *client = to_i2c_client(bq->dev);
	काष्ठा i2c_msg msg[1];
	u8 data[2];
	पूर्णांक ret;

	data[0] = reg;
	data[1] = val;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].buf = data;
	msg[0].len = ARRAY_SIZE(data);

	mutex_lock(&bq2415x_i2c_mutex);
	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	mutex_unlock(&bq2415x_i2c_mutex);

	/* i2c_transfer वापसs number of messages transferred */
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

/* पढ़ो value from रेजिस्टर, change it with mask left shअगरted and ग_लिखो back */
अटल पूर्णांक bq2415x_i2c_ग_लिखो_mask(काष्ठा bq2415x_device *bq, u8 reg, u8 val,
				  u8 mask, u8 shअगरt)
अणु
	पूर्णांक ret;

	अगर (shअगरt > 8)
		वापस -EINVAL;

	ret = bq2415x_i2c_पढ़ो(bq, reg);
	अगर (ret < 0)
		वापस ret;

	ret &= ~mask;
	ret |= val << shअगरt;

	वापस bq2415x_i2c_ग_लिखो(bq, reg, ret);
पूर्ण

/* change only one bit in रेजिस्टर */
अटल पूर्णांक bq2415x_i2c_ग_लिखो_bit(काष्ठा bq2415x_device *bq, u8 reg,
				 bool val, u8 bit)
अणु
	अगर (bit > 8)
		वापस -EINVAL;
	वापस bq2415x_i2c_ग_लिखो_mask(bq, reg, val, BIT(bit), bit);
पूर्ण

/**** global functions ****/

/* exec command function */
अटल पूर्णांक bq2415x_exec_command(काष्ठा bq2415x_device *bq,
				क्रमागत bq2415x_command command)
अणु
	पूर्णांक ret;

	चयन (command) अणु
	हाल BQ2415X_TIMER_RESET:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_STATUS,
				1, BQ2415X_BIT_TMR_RST);
	हाल BQ2415X_OTG_STATUS:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_STATUS,
				BQ2415X_BIT_OTG);
	हाल BQ2415X_STAT_PIN_STATUS:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_STATUS,
				BQ2415X_BIT_EN_STAT);
	हाल BQ2415X_STAT_PIN_ENABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_STATUS, 1,
				BQ2415X_BIT_EN_STAT);
	हाल BQ2415X_STAT_PIN_DISABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_STATUS, 0,
				BQ2415X_BIT_EN_STAT);
	हाल BQ2415X_CHARGE_STATUS:
		वापस bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_STATUS,
				BQ2415X_MASK_STAT, BQ2415X_SHIFT_STAT);
	हाल BQ2415X_BOOST_STATUS:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_STATUS,
				BQ2415X_BIT_BOOST);
	हाल BQ2415X_FAULT_STATUS:
		वापस bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_STATUS,
			BQ2415X_MASK_FAULT, BQ2415X_SHIFT_FAULT);

	हाल BQ2415X_CHARGE_TERMINATION_STATUS:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_CONTROL,
				BQ2415X_BIT_TE);
	हाल BQ2415X_CHARGE_TERMINATION_ENABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_TE);
	हाल BQ2415X_CHARGE_TERMINATION_DISABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_TE);
	हाल BQ2415X_CHARGER_STATUS:
		ret = bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_CONTROL,
			BQ2415X_BIT_CE);
		अगर (ret < 0)
			वापस ret;
		वापस ret > 0 ? 0 : 1;
	हाल BQ2415X_CHARGER_ENABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_CE);
	हाल BQ2415X_CHARGER_DISABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_CE);
	हाल BQ2415X_HIGH_IMPEDANCE_STATUS:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_CONTROL,
				BQ2415X_BIT_HZ_MODE);
	हाल BQ2415X_HIGH_IMPEDANCE_ENABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_HZ_MODE);
	हाल BQ2415X_HIGH_IMPEDANCE_DISABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_HZ_MODE);
	हाल BQ2415X_BOOST_MODE_STATUS:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_CONTROL,
				BQ2415X_BIT_OPA_MODE);
	हाल BQ2415X_BOOST_MODE_ENABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				1, BQ2415X_BIT_OPA_MODE);
	हाल BQ2415X_BOOST_MODE_DISABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_CONTROL,
				0, BQ2415X_BIT_OPA_MODE);

	हाल BQ2415X_OTG_LEVEL:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_VOLTAGE,
				BQ2415X_BIT_OTG_PL);
	हाल BQ2415X_OTG_ACTIVATE_HIGH:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_VOLTAGE,
				1, BQ2415X_BIT_OTG_PL);
	हाल BQ2415X_OTG_ACTIVATE_LOW:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_VOLTAGE,
				0, BQ2415X_BIT_OTG_PL);
	हाल BQ2415X_OTG_PIN_STATUS:
		वापस bq2415x_i2c_पढ़ो_bit(bq, BQ2415X_REG_VOLTAGE,
				BQ2415X_BIT_OTG_EN);
	हाल BQ2415X_OTG_PIN_ENABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_VOLTAGE,
				1, BQ2415X_BIT_OTG_EN);
	हाल BQ2415X_OTG_PIN_DISABLE:
		वापस bq2415x_i2c_ग_लिखो_bit(bq, BQ2415X_REG_VOLTAGE,
				0, BQ2415X_BIT_OTG_EN);

	हाल BQ2415X_VENDER_CODE:
		वापस bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_VENDER,
			BQ2415X_MASK_VENDER, BQ2415X_SHIFT_VENDER);
	हाल BQ2415X_PART_NUMBER:
		वापस bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_VENDER,
				BQ2415X_MASK_PN, BQ2415X_SHIFT_PN);
	हाल BQ2415X_REVISION:
		वापस bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_VENDER,
			BQ2415X_MASK_REVISION, BQ2415X_SHIFT_REVISION);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* detect chip type */
अटल क्रमागत bq2415x_chip bq2415x_detect_chip(काष्ठा bq2415x_device *bq)
अणु
	काष्ठा i2c_client *client = to_i2c_client(bq->dev);
	पूर्णांक ret = bq2415x_exec_command(bq, BQ2415X_PART_NUMBER);

	अगर (ret < 0)
		वापस ret;

	चयन (client->addr) अणु
	हाल 0x6b:
		चयन (ret) अणु
		हाल 0:
			अगर (bq->chip == BQ24151A)
				वापस bq->chip;
			वापस BQ24151;
		हाल 1:
			अगर (bq->chip == BQ24150A ||
				bq->chip == BQ24152 ||
				bq->chip == BQ24155)
				वापस bq->chip;
			वापस BQ24150;
		हाल 2:
			अगर (bq->chip == BQ24153A)
				वापस bq->chip;
			वापस BQ24153;
		शेष:
			वापस BQUNKNOWN;
		पूर्ण
		अवरोध;

	हाल 0x6a:
		चयन (ret) अणु
		हाल 0:
			अगर (bq->chip == BQ24156A)
				वापस bq->chip;
			वापस BQ24156;
		हाल 2:
			अगर (bq->chip == BQ24157S)
				वापस bq->chip;
			वापस BQ24158;
		शेष:
			वापस BQUNKNOWN;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस BQUNKNOWN;
पूर्ण

/* detect chip revision */
अटल पूर्णांक bq2415x_detect_revision(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret = bq2415x_exec_command(bq, BQ2415X_REVISION);
	पूर्णांक chip = bq2415x_detect_chip(bq);

	अगर (ret < 0 || chip < 0)
		वापस -1;

	चयन (chip) अणु
	हाल BQ24150:
	हाल BQ24150A:
	हाल BQ24151:
	हाल BQ24151A:
	हाल BQ24152:
		अगर (ret >= 0 && ret <= 3)
			वापस ret;
		वापस -1;
	हाल BQ24153:
	हाल BQ24153A:
	हाल BQ24156:
	हाल BQ24156A:
	हाल BQ24157S:
	हाल BQ24158:
		अगर (ret == 3)
			वापस 0;
		अन्यथा अगर (ret == 1)
			वापस 1;
		वापस -1;
	हाल BQ24155:
		अगर (ret == 3)
			वापस 3;
		वापस -1;
	हाल BQUNKNOWN:
		वापस -1;
	पूर्ण

	वापस -1;
पूर्ण

/* वापस chip vender code */
अटल पूर्णांक bq2415x_get_vender_code(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret;

	ret = bq2415x_exec_command(bq, BQ2415X_VENDER_CODE);
	अगर (ret < 0)
		वापस 0;

	/* convert to binary */
	वापस (ret & 0x1) +
	       ((ret >> 1) & 0x1) * 10 +
	       ((ret >> 2) & 0x1) * 100;
पूर्ण

/* reset all chip रेजिस्टरs to शेष state */
अटल व्योम bq2415x_reset_chip(काष्ठा bq2415x_device *bq)
अणु
	bq2415x_i2c_ग_लिखो(bq, BQ2415X_REG_CURRENT, BQ2415X_RESET_CURRENT);
	bq2415x_i2c_ग_लिखो(bq, BQ2415X_REG_VOLTAGE, BQ2415X_RESET_VOLTAGE);
	bq2415x_i2c_ग_लिखो(bq, BQ2415X_REG_CONTROL, BQ2415X_RESET_CONTROL);
	bq2415x_i2c_ग_लिखो(bq, BQ2415X_REG_STATUS, BQ2415X_RESET_STATUS);
	bq->समयr_error = शून्य;
पूर्ण

/**** properties functions ****/

/* set current limit in mA */
अटल पूर्णांक bq2415x_set_current_limit(काष्ठा bq2415x_device *bq, पूर्णांक mA)
अणु
	पूर्णांक val;

	अगर (mA <= 100)
		val = 0;
	अन्यथा अगर (mA <= 500)
		val = 1;
	अन्यथा अगर (mA <= 800)
		val = 2;
	अन्यथा
		val = 3;

	वापस bq2415x_i2c_ग_लिखो_mask(bq, BQ2415X_REG_CONTROL, val,
			BQ2415X_MASK_LIMIT, BQ2415X_SHIFT_LIMIT);
पूर्ण

/* get current limit in mA */
अटल पूर्णांक bq2415x_get_current_limit(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret;

	ret = bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_CONTROL,
			BQ2415X_MASK_LIMIT, BQ2415X_SHIFT_LIMIT);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret == 0)
		वापस 100;
	अन्यथा अगर (ret == 1)
		वापस 500;
	अन्यथा अगर (ret == 2)
		वापस 800;
	अन्यथा अगर (ret == 3)
		वापस 1800;
	वापस -EINVAL;
पूर्ण

/* set weak battery voltage in mV */
अटल पूर्णांक bq2415x_set_weak_battery_voltage(काष्ठा bq2415x_device *bq, पूर्णांक mV)
अणु
	पूर्णांक val;

	/* round to 100mV */
	अगर (mV <= 3400 + 50)
		val = 0;
	अन्यथा अगर (mV <= 3500 + 50)
		val = 1;
	अन्यथा अगर (mV <= 3600 + 50)
		val = 2;
	अन्यथा
		val = 3;

	वापस bq2415x_i2c_ग_लिखो_mask(bq, BQ2415X_REG_CONTROL, val,
			BQ2415X_MASK_VLOWV, BQ2415X_SHIFT_VLOWV);
पूर्ण

/* get weak battery voltage in mV */
अटल पूर्णांक bq2415x_get_weak_battery_voltage(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret;

	ret = bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_CONTROL,
			BQ2415X_MASK_VLOWV, BQ2415X_SHIFT_VLOWV);
	अगर (ret < 0)
		वापस ret;
	वापस 100 * (34 + ret);
पूर्ण

/* set battery regulation voltage in mV */
अटल पूर्णांक bq2415x_set_battery_regulation_voltage(काष्ठा bq2415x_device *bq,
						  पूर्णांक mV)
अणु
	पूर्णांक val = (mV/10 - 350) / 2;

	/*
	 * According to datasheet, maximum battery regulation voltage is
	 * 4440mV which is b101111 = 47.
	 */
	अगर (val < 0)
		val = 0;
	अन्यथा अगर (val > 47)
		वापस -EINVAL;

	वापस bq2415x_i2c_ग_लिखो_mask(bq, BQ2415X_REG_VOLTAGE, val,
			BQ2415X_MASK_VO, BQ2415X_SHIFT_VO);
पूर्ण

/* get battery regulation voltage in mV */
अटल पूर्णांक bq2415x_get_battery_regulation_voltage(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret = bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_VOLTAGE,
			BQ2415X_MASK_VO, BQ2415X_SHIFT_VO);

	अगर (ret < 0)
		वापस ret;
	वापस 10 * (350 + 2*ret);
पूर्ण

/* set अक्षरge current in mA (platक्रमm data must provide resistor sense) */
अटल पूर्णांक bq2415x_set_अक्षरge_current(काष्ठा bq2415x_device *bq, पूर्णांक mA)
अणु
	पूर्णांक val;

	अगर (bq->init_data.resistor_sense <= 0)
		वापस -EINVAL;

	val = (mA * bq->init_data.resistor_sense - 37400) / 6800;
	अगर (val < 0)
		val = 0;
	अन्यथा अगर (val > 7)
		val = 7;

	वापस bq2415x_i2c_ग_लिखो_mask(bq, BQ2415X_REG_CURRENT, val,
			BQ2415X_MASK_VI_CHRG | BQ2415X_MASK_RESET,
			BQ2415X_SHIFT_VI_CHRG);
पूर्ण

/* get अक्षरge current in mA (platक्रमm data must provide resistor sense) */
अटल पूर्णांक bq2415x_get_अक्षरge_current(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret;

	अगर (bq->init_data.resistor_sense <= 0)
		वापस -EINVAL;

	ret = bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_CURRENT,
			BQ2415X_MASK_VI_CHRG, BQ2415X_SHIFT_VI_CHRG);
	अगर (ret < 0)
		वापस ret;
	वापस (37400 + 6800*ret) / bq->init_data.resistor_sense;
पूर्ण

/* set termination current in mA (platक्रमm data must provide resistor sense) */
अटल पूर्णांक bq2415x_set_termination_current(काष्ठा bq2415x_device *bq, पूर्णांक mA)
अणु
	पूर्णांक val;

	अगर (bq->init_data.resistor_sense <= 0)
		वापस -EINVAL;

	val = (mA * bq->init_data.resistor_sense - 3400) / 3400;
	अगर (val < 0)
		val = 0;
	अन्यथा अगर (val > 7)
		val = 7;

	वापस bq2415x_i2c_ग_लिखो_mask(bq, BQ2415X_REG_CURRENT, val,
			BQ2415X_MASK_VI_TERM | BQ2415X_MASK_RESET,
			BQ2415X_SHIFT_VI_TERM);
पूर्ण

/* get termination current in mA (platक्रमm data must provide resistor sense) */
अटल पूर्णांक bq2415x_get_termination_current(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret;

	अगर (bq->init_data.resistor_sense <= 0)
		वापस -EINVAL;

	ret = bq2415x_i2c_पढ़ो_mask(bq, BQ2415X_REG_CURRENT,
			BQ2415X_MASK_VI_TERM, BQ2415X_SHIFT_VI_TERM);
	अगर (ret < 0)
		वापस ret;
	वापस (3400 + 3400*ret) / bq->init_data.resistor_sense;
पूर्ण

/* set शेष value of property */
#घोषणा bq2415x_set_शेष_value(bq, prop) \
	करो अणु \
		पूर्णांक ret = 0; \
		अगर (bq->init_data.prop != -1) \
			ret = bq2415x_set_##prop(bq, bq->init_data.prop); \
		अगर (ret < 0) \
			वापस ret; \
	पूर्ण जबतक (0)

/* set शेष values of all properties */
अटल पूर्णांक bq2415x_set_शेषs(काष्ठा bq2415x_device *bq)
अणु
	bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_DISABLE);
	bq2415x_exec_command(bq, BQ2415X_CHARGER_DISABLE);
	bq2415x_exec_command(bq, BQ2415X_CHARGE_TERMINATION_DISABLE);

	bq2415x_set_शेष_value(bq, current_limit);
	bq2415x_set_शेष_value(bq, weak_battery_voltage);
	bq2415x_set_शेष_value(bq, battery_regulation_voltage);

	अगर (bq->init_data.resistor_sense > 0) अणु
		bq2415x_set_शेष_value(bq, अक्षरge_current);
		bq2415x_set_शेष_value(bq, termination_current);
		bq2415x_exec_command(bq, BQ2415X_CHARGE_TERMINATION_ENABLE);
	पूर्ण

	bq2415x_exec_command(bq, BQ2415X_CHARGER_ENABLE);
	वापस 0;
पूर्ण

/**** अक्षरger mode functions ****/

/* set अक्षरger mode */
अटल पूर्णांक bq2415x_set_mode(काष्ठा bq2415x_device *bq, क्रमागत bq2415x_mode mode)
अणु
	पूर्णांक ret = 0;
	पूर्णांक अक्षरger = 0;
	पूर्णांक boost = 0;

	अगर (mode == BQ2415X_MODE_BOOST)
		boost = 1;
	अन्यथा अगर (mode != BQ2415X_MODE_OFF)
		अक्षरger = 1;

	अगर (!अक्षरger)
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGER_DISABLE);

	अगर (!boost)
		ret = bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_DISABLE);

	अगर (ret < 0)
		वापस ret;

	चयन (mode) अणु
	हाल BQ2415X_MODE_OFF:
		dev_dbg(bq->dev, "changing mode to: Offline\n");
		ret = bq2415x_set_current_limit(bq, 100);
		अवरोध;
	हाल BQ2415X_MODE_NONE:
		dev_dbg(bq->dev, "changing mode to: N/A\n");
		ret = bq2415x_set_current_limit(bq, 100);
		अवरोध;
	हाल BQ2415X_MODE_HOST_CHARGER:
		dev_dbg(bq->dev, "changing mode to: Host/HUB charger\n");
		ret = bq2415x_set_current_limit(bq, 500);
		अवरोध;
	हाल BQ2415X_MODE_DEDICATED_CHARGER:
		dev_dbg(bq->dev, "changing mode to: Dedicated charger\n");
		ret = bq2415x_set_current_limit(bq, 1800);
		अवरोध;
	हाल BQ2415X_MODE_BOOST: /* Boost mode */
		dev_dbg(bq->dev, "changing mode to: Boost\n");
		ret = bq2415x_set_current_limit(bq, 100);
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	अगर (अक्षरger)
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGER_ENABLE);
	अन्यथा अगर (boost)
		ret = bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_ENABLE);

	अगर (ret < 0)
		वापस ret;

	bq2415x_set_शेष_value(bq, weak_battery_voltage);
	bq2415x_set_शेष_value(bq, battery_regulation_voltage);

	bq->mode = mode;
	sysfs_notअगरy(&bq->अक्षरger->dev.kobj, शून्य, "mode");

	वापस 0;

पूर्ण

अटल bool bq2415x_update_reported_mode(काष्ठा bq2415x_device *bq, पूर्णांक mA)
अणु
	क्रमागत bq2415x_mode mode;

	अगर (mA == 0)
		mode = BQ2415X_MODE_OFF;
	अन्यथा अगर (mA < 500)
		mode = BQ2415X_MODE_NONE;
	अन्यथा अगर (mA < 1800)
		mode = BQ2415X_MODE_HOST_CHARGER;
	अन्यथा
		mode = BQ2415X_MODE_DEDICATED_CHARGER;

	अगर (bq->reported_mode == mode)
		वापस false;

	bq->reported_mode = mode;
	वापस true;
पूर्ण

अटल पूर्णांक bq2415x_notअगरier_call(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ val, व्योम *v)
अणु
	काष्ठा bq2415x_device *bq =
		container_of(nb, काष्ठा bq2415x_device, nb);
	काष्ठा घातer_supply *psy = v;
	जोड़ घातer_supply_propval prop;
	पूर्णांक ret;

	अगर (val != PSY_EVENT_PROP_CHANGED)
		वापस NOTIFY_OK;

	/* Ignore event अगर it was not send by notअगरy_node/notअगरy_device */
	अगर (bq->notअगरy_node) अणु
		अगर (!psy->dev.parent ||
		    psy->dev.parent->of_node != bq->notअगरy_node)
			वापस NOTIFY_OK;
	पूर्ण अन्यथा अगर (bq->init_data.notअगरy_device) अणु
		अगर (म_भेद(psy->desc->name, bq->init_data.notअगरy_device) != 0)
			वापस NOTIFY_OK;
	पूर्ण

	dev_dbg(bq->dev, "notifier call was called\n");

	ret = घातer_supply_get_property(psy, POWER_SUPPLY_PROP_CURRENT_MAX,
			&prop);
	अगर (ret != 0)
		वापस NOTIFY_OK;

	अगर (!bq2415x_update_reported_mode(bq, prop.पूर्णांकval))
		वापस NOTIFY_OK;

	/* अगर स्वतःmode is not enabled करो not tell about reported_mode */
	अगर (bq->स्वतःmode < 1)
		वापस NOTIFY_OK;

	schedule_delayed_work(&bq->work, 0);

	वापस NOTIFY_OK;
पूर्ण

/**** समयr functions ****/

/* enable/disable स्वतः resetting chip समयr */
अटल व्योम bq2415x_set_स्वतःसमयr(काष्ठा bq2415x_device *bq, पूर्णांक state)
अणु
	mutex_lock(&bq2415x_समयr_mutex);

	अगर (bq->स्वतःसमयr == state) अणु
		mutex_unlock(&bq2415x_समयr_mutex);
		वापस;
	पूर्ण

	bq->स्वतःसमयr = state;

	अगर (state) अणु
		schedule_delayed_work(&bq->work, BQ2415X_TIMER_TIMEOUT * HZ);
		bq2415x_exec_command(bq, BQ2415X_TIMER_RESET);
		bq->समयr_error = शून्य;
	पूर्ण अन्यथा अणु
		cancel_delayed_work_sync(&bq->work);
	पूर्ण

	mutex_unlock(&bq2415x_समयr_mutex);
पूर्ण

/* called by bq2415x_समयr_work on समयr error */
अटल व्योम bq2415x_समयr_error(काष्ठा bq2415x_device *bq, स्थिर अक्षर *msg)
अणु
	bq->समयr_error = msg;
	sysfs_notअगरy(&bq->अक्षरger->dev.kobj, शून्य, "timer");
	dev_err(bq->dev, "%s\n", msg);
	अगर (bq->स्वतःmode > 0)
		bq->स्वतःmode = 0;
	bq2415x_set_mode(bq, BQ2415X_MODE_OFF);
	bq2415x_set_स्वतःसमयr(bq, 0);
पूर्ण

/* delayed work function क्रम स्वतः resetting chip समयr */
अटल व्योम bq2415x_समयr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bq2415x_device *bq = container_of(work, काष्ठा bq2415x_device,
						 work.work);
	पूर्णांक ret;
	पूर्णांक error;
	पूर्णांक boost;

	अगर (bq->स्वतःmode > 0 && (bq->reported_mode != bq->mode)) अणु
		sysfs_notअगरy(&bq->अक्षरger->dev.kobj, शून्य, "reported_mode");
		bq2415x_set_mode(bq, bq->reported_mode);
	पूर्ण

	अगर (!bq->स्वतःसमयr)
		वापस;

	ret = bq2415x_exec_command(bq, BQ2415X_TIMER_RESET);
	अगर (ret < 0) अणु
		bq2415x_समयr_error(bq, "Resetting timer failed");
		वापस;
	पूर्ण

	boost = bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_STATUS);
	अगर (boost < 0) अणु
		bq2415x_समयr_error(bq, "Unknown error");
		वापस;
	पूर्ण

	error = bq2415x_exec_command(bq, BQ2415X_FAULT_STATUS);
	अगर (error < 0) अणु
		bq2415x_समयr_error(bq, "Unknown error");
		वापस;
	पूर्ण

	अगर (boost) अणु
		चयन (error) अणु
		/* Non fatal errors, chip is OK */
		हाल 0: /* No error */
			अवरोध;
		हाल 6: /* Timer expired */
			dev_err(bq->dev, "Timer expired\n");
			अवरोध;
		हाल 3: /* Battery voltage too low */
			dev_err(bq->dev, "Battery voltage to low\n");
			अवरोध;

		/* Fatal errors, disable and reset chip */
		हाल 1: /* Overvoltage protection (chip fried) */
			bq2415x_समयr_error(bq,
				"Overvoltage protection (chip fried)");
			वापस;
		हाल 2: /* Overload */
			bq2415x_समयr_error(bq, "Overload");
			वापस;
		हाल 4: /* Battery overvoltage protection */
			bq2415x_समयr_error(bq,
				"Battery overvoltage protection");
			वापस;
		हाल 5: /* Thermal shutकरोwn (too hot) */
			bq2415x_समयr_error(bq,
					"Thermal shutdown (too hot)");
			वापस;
		हाल 7: /* N/A */
			bq2415x_समयr_error(bq, "Unknown error");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (error) अणु
		/* Non fatal errors, chip is OK */
		हाल 0: /* No error */
			अवरोध;
		हाल 2: /* Sleep mode */
			dev_err(bq->dev, "Sleep mode\n");
			अवरोध;
		हाल 3: /* Poor input source */
			dev_err(bq->dev, "Poor input source\n");
			अवरोध;
		हाल 6: /* Timer expired */
			dev_err(bq->dev, "Timer expired\n");
			अवरोध;
		हाल 7: /* No battery */
			dev_err(bq->dev, "No battery\n");
			अवरोध;

		/* Fatal errors, disable and reset chip */
		हाल 1: /* Overvoltage protection (chip fried) */
			bq2415x_समयr_error(bq,
				"Overvoltage protection (chip fried)");
			वापस;
		हाल 4: /* Battery overvoltage protection */
			bq2415x_समयr_error(bq,
				"Battery overvoltage protection");
			वापस;
		हाल 5: /* Thermal shutकरोwn (too hot) */
			bq2415x_समयr_error(bq,
				"Thermal shutdown (too hot)");
			वापस;
		पूर्ण
	पूर्ण

	schedule_delayed_work(&bq->work, BQ2415X_TIMER_TIMEOUT * HZ);
पूर्ण

/**** घातer supply पूर्णांकerface code ****/

अटल क्रमागत घातer_supply_property bq2415x_घातer_supply_props[] = अणु
	/* TODO: maybe add more घातer supply properties */
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_MODEL_NAME,
पूर्ण;

अटल पूर्णांक bq2415x_घातer_supply_get_property(काष्ठा घातer_supply *psy,
					     क्रमागत घातer_supply_property psp,
					     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGE_STATUS);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret == 0) /* Ready */
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अन्यथा अगर (ret == 1) /* Charge in progress */
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (ret == 2) /* Charge करोne */
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq->model;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bq2415x_घातer_supply_निकास(काष्ठा bq2415x_device *bq)
अणु
	bq->स्वतःसमयr = 0;
	अगर (bq->स्वतःmode > 0)
		bq->स्वतःmode = 0;
	cancel_delayed_work_sync(&bq->work);
	घातer_supply_unरेजिस्टर(bq->अक्षरger);
	kमुक्त(bq->model);
पूर्ण

/**** additional sysfs entries क्रम घातer supply पूर्णांकerface ****/

/* show *_status entries */
अटल sमाप_प्रकार bq2415x_sysfs_show_status(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	क्रमागत bq2415x_command command;
	पूर्णांक ret;

	अगर (म_भेद(attr->attr.name, "otg_status") == 0)
		command = BQ2415X_OTG_STATUS;
	अन्यथा अगर (म_भेद(attr->attr.name, "charge_status") == 0)
		command = BQ2415X_CHARGE_STATUS;
	अन्यथा अगर (म_भेद(attr->attr.name, "boost_status") == 0)
		command = BQ2415X_BOOST_STATUS;
	अन्यथा अगर (म_भेद(attr->attr.name, "fault_status") == 0)
		command = BQ2415X_FAULT_STATUS;
	अन्यथा
		वापस -EINVAL;

	ret = bq2415x_exec_command(bq, command);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

/*
 * set समयr entry:
 *    स्वतः - enable स्वतः mode
 *    off - disable स्वतः mode
 *    (other values) - reset chip समयr
 */
अटल sमाप_प्रकार bq2415x_sysfs_set_समयr(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = 0;

	अगर (म_भेदन(buf, "auto", 4) == 0)
		bq2415x_set_स्वतःसमयr(bq, 1);
	अन्यथा अगर (म_भेदन(buf, "off", 3) == 0)
		bq2415x_set_स्वतःसमयr(bq, 0);
	अन्यथा
		ret = bq2415x_exec_command(bq, BQ2415X_TIMER_RESET);

	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/* show समयr entry (स्वतः or off) */
अटल sमाप_प्रकार bq2415x_sysfs_show_समयr(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);

	अगर (bq->समयr_error)
		वापस प्र_लिखो(buf, "%s\n", bq->समयr_error);

	अगर (bq->स्वतःसमयr)
		वापस प्र_लिखो(buf, "auto\n");
	वापस प्र_लिखो(buf, "off\n");
पूर्ण

/*
 * set mode entry:
 *    स्वतः - अगर स्वतःmode is supported, enable it and set mode to reported
 *    none - disable अक्षरger and boost mode
 *    host - अक्षरging mode क्रम host/hub अक्षरgers (current limit 500mA)
 *    dedicated - अक्षरging mode क्रम dedicated अक्षरgers (unlimited current limit)
 *    boost - disable अक्षरger and enable boost mode
 */
अटल sमाप_प्रकार bq2415x_sysfs_set_mode(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf,
				      माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	क्रमागत bq2415x_mode mode;
	पूर्णांक ret = 0;

	अगर (म_भेदन(buf, "auto", 4) == 0) अणु
		अगर (bq->स्वतःmode < 0)
			वापस -EINVAL;
		bq->स्वतःmode = 1;
		mode = bq->reported_mode;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "off", 3) == 0) अणु
		अगर (bq->स्वतःmode > 0)
			bq->स्वतःmode = 0;
		mode = BQ2415X_MODE_OFF;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "none", 4) == 0) अणु
		अगर (bq->स्वतःmode > 0)
			bq->स्वतःmode = 0;
		mode = BQ2415X_MODE_NONE;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "host", 4) == 0) अणु
		अगर (bq->स्वतःmode > 0)
			bq->स्वतःmode = 0;
		mode = BQ2415X_MODE_HOST_CHARGER;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "dedicated", 9) == 0) अणु
		अगर (bq->स्वतःmode > 0)
			bq->स्वतःmode = 0;
		mode = BQ2415X_MODE_DEDICATED_CHARGER;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "boost", 5) == 0) अणु
		अगर (bq->स्वतःmode > 0)
			bq->स्वतःmode = 0;
		mode = BQ2415X_MODE_BOOST;
	पूर्ण अन्यथा अगर (म_भेदन(buf, "reset", 5) == 0) अणु
		bq2415x_reset_chip(bq);
		bq2415x_set_शेषs(bq);
		अगर (bq->स्वतःmode <= 0)
			वापस count;
		bq->स्वतःmode = 1;
		mode = bq->reported_mode;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ret = bq2415x_set_mode(bq, mode);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/* show mode entry (स्वतः, none, host, dedicated or boost) */
अटल sमाप_प्रकार bq2415x_sysfs_show_mode(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	sमाप_प्रकार ret = 0;

	अगर (bq->स्वतःmode > 0)
		ret += प्र_लिखो(buf+ret, "auto (");

	चयन (bq->mode) अणु
	हाल BQ2415X_MODE_OFF:
		ret += प्र_लिखो(buf+ret, "off");
		अवरोध;
	हाल BQ2415X_MODE_NONE:
		ret += प्र_लिखो(buf+ret, "none");
		अवरोध;
	हाल BQ2415X_MODE_HOST_CHARGER:
		ret += प्र_लिखो(buf+ret, "host");
		अवरोध;
	हाल BQ2415X_MODE_DEDICATED_CHARGER:
		ret += प्र_लिखो(buf+ret, "dedicated");
		अवरोध;
	हाल BQ2415X_MODE_BOOST:
		ret += प्र_लिखो(buf+ret, "boost");
		अवरोध;
	पूर्ण

	अगर (bq->स्वतःmode > 0)
		ret += प्र_लिखो(buf+ret, ")");

	ret += प्र_लिखो(buf+ret, "\n");
	वापस ret;
पूर्ण

/* show reported_mode entry (none, host, dedicated or boost) */
अटल sमाप_प्रकार bq2415x_sysfs_show_reported_mode(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);

	अगर (bq->स्वतःmode < 0)
		वापस -EINVAL;

	चयन (bq->reported_mode) अणु
	हाल BQ2415X_MODE_OFF:
		वापस प्र_लिखो(buf, "off\n");
	हाल BQ2415X_MODE_NONE:
		वापस प्र_लिखो(buf, "none\n");
	हाल BQ2415X_MODE_HOST_CHARGER:
		वापस प्र_लिखो(buf, "host\n");
	हाल BQ2415X_MODE_DEDICATED_CHARGER:
		वापस प्र_लिखो(buf, "dedicated\n");
	हाल BQ2415X_MODE_BOOST:
		वापस प्र_लिखो(buf, "boost\n");
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* directly set raw value to chip रेजिस्टर, क्रमmat: 'register value' */
अटल sमाप_प्रकार bq2415x_sysfs_set_रेजिस्टरs(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf,
					   माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	sमाप_प्रकार ret = 0;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक val;

	अगर (माला_पूछो(buf, "%x %x", &reg, &val) != 2)
		वापस -EINVAL;

	अगर (reg > 4 || val > 255)
		वापस -EINVAL;

	ret = bq2415x_i2c_ग_लिखो(bq, reg, val);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/* prपूर्णांक value of chip रेजिस्टर, क्रमmat: 'register=value' */
अटल sमाप_प्रकार bq2415x_sysfs_prपूर्णांक_reg(काष्ठा bq2415x_device *bq,
				       u8 reg,
				       अक्षर *buf)
अणु
	पूर्णांक ret = bq2415x_i2c_पढ़ो(bq, reg);

	अगर (ret < 0)
		वापस प्र_लिखो(buf, "%#.2x=error %d\n", reg, ret);
	वापस प्र_लिखो(buf, "%#.2x=%#.2x\n", reg, ret);
पूर्ण

/* show all raw values of chip रेजिस्टर, क्रमmat per line: 'register=value' */
अटल sमाप_प्रकार bq2415x_sysfs_show_रेजिस्टरs(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	sमाप_प्रकार ret = 0;

	ret += bq2415x_sysfs_prपूर्णांक_reg(bq, BQ2415X_REG_STATUS, buf+ret);
	ret += bq2415x_sysfs_prपूर्णांक_reg(bq, BQ2415X_REG_CONTROL, buf+ret);
	ret += bq2415x_sysfs_prपूर्णांक_reg(bq, BQ2415X_REG_VOLTAGE, buf+ret);
	ret += bq2415x_sysfs_prपूर्णांक_reg(bq, BQ2415X_REG_VENDER, buf+ret);
	ret += bq2415x_sysfs_prपूर्णांक_reg(bq, BQ2415X_REG_CURRENT, buf+ret);
	वापस ret;
पूर्ण

/* set current and voltage limit entries (in mA or mV) */
अटल sमाप_प्रकार bq2415x_sysfs_set_limit(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf,
				       माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	अगर (म_भेद(attr->attr.name, "current_limit") == 0)
		ret = bq2415x_set_current_limit(bq, val);
	अन्यथा अगर (म_भेद(attr->attr.name, "weak_battery_voltage") == 0)
		ret = bq2415x_set_weak_battery_voltage(bq, val);
	अन्यथा अगर (म_भेद(attr->attr.name, "battery_regulation_voltage") == 0)
		ret = bq2415x_set_battery_regulation_voltage(bq, val);
	अन्यथा अगर (म_भेद(attr->attr.name, "charge_current") == 0)
		ret = bq2415x_set_अक्षरge_current(bq, val);
	अन्यथा अगर (म_भेद(attr->attr.name, "termination_current") == 0)
		ret = bq2415x_set_termination_current(bq, val);
	अन्यथा
		वापस -EINVAL;

	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/* show current and voltage limit entries (in mA or mV) */
अटल sमाप_प्रकार bq2415x_sysfs_show_limit(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	अगर (म_भेद(attr->attr.name, "current_limit") == 0)
		ret = bq2415x_get_current_limit(bq);
	अन्यथा अगर (म_भेद(attr->attr.name, "weak_battery_voltage") == 0)
		ret = bq2415x_get_weak_battery_voltage(bq);
	अन्यथा अगर (म_भेद(attr->attr.name, "battery_regulation_voltage") == 0)
		ret = bq2415x_get_battery_regulation_voltage(bq);
	अन्यथा अगर (म_भेद(attr->attr.name, "charge_current") == 0)
		ret = bq2415x_get_अक्षरge_current(bq);
	अन्यथा अगर (म_भेद(attr->attr.name, "termination_current") == 0)
		ret = bq2415x_get_termination_current(bq);
	अन्यथा
		वापस -EINVAL;

	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

/* set *_enable entries */
अटल sमाप_प्रकार bq2415x_sysfs_set_enable(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf,
					माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	क्रमागत bq2415x_command command;
	दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_दीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	अगर (म_भेद(attr->attr.name, "charge_termination_enable") == 0)
		command = val ? BQ2415X_CHARGE_TERMINATION_ENABLE :
			BQ2415X_CHARGE_TERMINATION_DISABLE;
	अन्यथा अगर (म_भेद(attr->attr.name, "high_impedance_enable") == 0)
		command = val ? BQ2415X_HIGH_IMPEDANCE_ENABLE :
			BQ2415X_HIGH_IMPEDANCE_DISABLE;
	अन्यथा अगर (म_भेद(attr->attr.name, "otg_pin_enable") == 0)
		command = val ? BQ2415X_OTG_PIN_ENABLE :
			BQ2415X_OTG_PIN_DISABLE;
	अन्यथा अगर (म_भेद(attr->attr.name, "stat_pin_enable") == 0)
		command = val ? BQ2415X_STAT_PIN_ENABLE :
			BQ2415X_STAT_PIN_DISABLE;
	अन्यथा
		वापस -EINVAL;

	ret = bq2415x_exec_command(bq, command);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/* show *_enable entries */
अटल sमाप_प्रकार bq2415x_sysfs_show_enable(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq2415x_device *bq = घातer_supply_get_drvdata(psy);
	क्रमागत bq2415x_command command;
	पूर्णांक ret;

	अगर (म_भेद(attr->attr.name, "charge_termination_enable") == 0)
		command = BQ2415X_CHARGE_TERMINATION_STATUS;
	अन्यथा अगर (म_भेद(attr->attr.name, "high_impedance_enable") == 0)
		command = BQ2415X_HIGH_IMPEDANCE_STATUS;
	अन्यथा अगर (म_भेद(attr->attr.name, "otg_pin_enable") == 0)
		command = BQ2415X_OTG_PIN_STATUS;
	अन्यथा अगर (म_भेद(attr->attr.name, "stat_pin_enable") == 0)
		command = BQ2415X_STAT_PIN_STATUS;
	अन्यथा
		वापस -EINVAL;

	ret = bq2415x_exec_command(bq, command);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल DEVICE_ATTR(current_limit, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_limit, bq2415x_sysfs_set_limit);
अटल DEVICE_ATTR(weak_battery_voltage, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_limit, bq2415x_sysfs_set_limit);
अटल DEVICE_ATTR(battery_regulation_voltage, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_limit, bq2415x_sysfs_set_limit);
अटल DEVICE_ATTR(अक्षरge_current, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_limit, bq2415x_sysfs_set_limit);
अटल DEVICE_ATTR(termination_current, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_limit, bq2415x_sysfs_set_limit);

अटल DEVICE_ATTR(अक्षरge_termination_enable, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_enable, bq2415x_sysfs_set_enable);
अटल DEVICE_ATTR(high_impedance_enable, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_enable, bq2415x_sysfs_set_enable);
अटल DEVICE_ATTR(otg_pin_enable, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_enable, bq2415x_sysfs_set_enable);
अटल DEVICE_ATTR(stat_pin_enable, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_enable, bq2415x_sysfs_set_enable);

अटल DEVICE_ATTR(reported_mode, S_IRUGO,
		bq2415x_sysfs_show_reported_mode, शून्य);
अटल DEVICE_ATTR(mode, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_mode, bq2415x_sysfs_set_mode);
अटल DEVICE_ATTR(समयr, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_समयr, bq2415x_sysfs_set_समयr);

अटल DEVICE_ATTR(रेजिस्टरs, S_IWUSR | S_IRUGO,
		bq2415x_sysfs_show_रेजिस्टरs, bq2415x_sysfs_set_रेजिस्टरs);

अटल DEVICE_ATTR(otg_status, S_IRUGO, bq2415x_sysfs_show_status, शून्य);
अटल DEVICE_ATTR(अक्षरge_status, S_IRUGO, bq2415x_sysfs_show_status, शून्य);
अटल DEVICE_ATTR(boost_status, S_IRUGO, bq2415x_sysfs_show_status, शून्य);
अटल DEVICE_ATTR(fault_status, S_IRUGO, bq2415x_sysfs_show_status, शून्य);

अटल काष्ठा attribute *bq2415x_sysfs_attrs[] = अणु
	/*
	 * TODO: some (appropriate) of these attrs should be चयनed to
	 * use घातer supply class props.
	 */
	&dev_attr_current_limit.attr,
	&dev_attr_weak_battery_voltage.attr,
	&dev_attr_battery_regulation_voltage.attr,
	&dev_attr_अक्षरge_current.attr,
	&dev_attr_termination_current.attr,

	&dev_attr_अक्षरge_termination_enable.attr,
	&dev_attr_high_impedance_enable.attr,
	&dev_attr_otg_pin_enable.attr,
	&dev_attr_stat_pin_enable.attr,

	&dev_attr_reported_mode.attr,
	&dev_attr_mode.attr,
	&dev_attr_समयr.attr,

	&dev_attr_रेजिस्टरs.attr,

	&dev_attr_otg_status.attr,
	&dev_attr_अक्षरge_status.attr,
	&dev_attr_boost_status.attr,
	&dev_attr_fault_status.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(bq2415x_sysfs);

अटल पूर्णांक bq2415x_घातer_supply_init(काष्ठा bq2415x_device *bq)
अणु
	पूर्णांक ret;
	पूर्णांक chip;
	अक्षर revstr[8];
	काष्ठा घातer_supply_config psy_cfg = अणु
		.drv_data = bq,
		.of_node = bq->dev->of_node,
		.attr_grp = bq2415x_sysfs_groups,
	पूर्ण;

	bq->अक्षरger_desc.name = bq->name;
	bq->अक्षरger_desc.type = POWER_SUPPLY_TYPE_USB;
	bq->अक्षरger_desc.properties = bq2415x_घातer_supply_props;
	bq->अक्षरger_desc.num_properties =
			ARRAY_SIZE(bq2415x_घातer_supply_props);
	bq->अक्षरger_desc.get_property = bq2415x_घातer_supply_get_property;

	ret = bq2415x_detect_chip(bq);
	अगर (ret < 0)
		chip = BQUNKNOWN;
	अन्यथा
		chip = ret;

	ret = bq2415x_detect_revision(bq);
	अगर (ret < 0)
		म_नकल(revstr, "unknown");
	अन्यथा
		प्र_लिखो(revstr, "1.%d", ret);

	bq->model = kaप्र_लिखो(GFP_KERNEL,
				"chip %s, revision %s, vender code %.3d",
				bq2415x_chip_name[chip], revstr,
				bq2415x_get_vender_code(bq));
	अगर (!bq->model) अणु
		dev_err(bq->dev, "failed to allocate model name\n");
		वापस -ENOMEM;
	पूर्ण

	bq->अक्षरger = घातer_supply_रेजिस्टर(bq->dev, &bq->अक्षरger_desc,
					    &psy_cfg);
	अगर (IS_ERR(bq->अक्षरger)) अणु
		kमुक्त(bq->model);
		वापस PTR_ERR(bq->अक्षरger);
	पूर्ण

	वापस 0;
पूर्ण

/* मुख्य bq2415x probe function */
अटल पूर्णांक bq2415x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	पूर्णांक num;
	अक्षर *name = शून्य;
	काष्ठा bq2415x_device *bq;
	काष्ठा device_node *np = client->dev.of_node;
	काष्ठा bq2415x_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	स्थिर काष्ठा acpi_device_id *acpi_id = शून्य;
	काष्ठा घातer_supply *notअगरy_psy = शून्य;
	जोड़ घातer_supply_propval prop;

	अगर (!np && !pdata && !ACPI_HANDLE(&client->dev)) अणु
		dev_err(&client->dev, "Neither devicetree, nor platform data, nor ACPI support\n");
		वापस -ENODEV;
	पूर्ण

	/* Get new ID क्रम the new device */
	mutex_lock(&bq2415x_id_mutex);
	num = idr_alloc(&bq2415x_id, client, 0, 0, GFP_KERNEL);
	mutex_unlock(&bq2415x_id_mutex);
	अगर (num < 0)
		वापस num;

	अगर (id) अणु
		name = kaप्र_लिखो(GFP_KERNEL, "%s-%d", id->name, num);
	पूर्ण अन्यथा अगर (ACPI_HANDLE(&client->dev)) अणु
		acpi_id =
			acpi_match_device(client->dev.driver->acpi_match_table,
					  &client->dev);
		अगर (!acpi_id) अणु
			dev_err(&client->dev, "failed to match device name\n");
			ret = -ENODEV;
			जाओ error_1;
		पूर्ण
		name = kaप्र_लिखो(GFP_KERNEL, "%s-%d", acpi_id->id, num);
	पूर्ण
	अगर (!name) अणु
		dev_err(&client->dev, "failed to allocate device name\n");
		ret = -ENOMEM;
		जाओ error_1;
	पूर्ण

	bq = devm_kzalloc(&client->dev, माप(*bq), GFP_KERNEL);
	अगर (!bq) अणु
		ret = -ENOMEM;
		जाओ error_2;
	पूर्ण

	i2c_set_clientdata(client, bq);

	bq->id = num;
	bq->dev = &client->dev;
	अगर (id)
		bq->chip = id->driver_data;
	अन्यथा अगर (ACPI_HANDLE(bq->dev))
		bq->chip = acpi_id->driver_data;
	bq->name = name;
	bq->mode = BQ2415X_MODE_OFF;
	bq->reported_mode = BQ2415X_MODE_OFF;
	bq->स्वतःसमयr = 0;
	bq->स्वतःmode = 0;

	अगर (np || ACPI_HANDLE(bq->dev)) अणु
		ret = device_property_पढ़ो_u32(bq->dev,
					       "ti,current-limit",
					       &bq->init_data.current_limit);
		अगर (ret)
			जाओ error_2;
		ret = device_property_पढ़ो_u32(bq->dev,
					"ti,weak-battery-voltage",
					&bq->init_data.weak_battery_voltage);
		अगर (ret)
			जाओ error_2;
		ret = device_property_पढ़ो_u32(bq->dev,
				"ti,battery-regulation-voltage",
				&bq->init_data.battery_regulation_voltage);
		अगर (ret)
			जाओ error_2;
		ret = device_property_पढ़ो_u32(bq->dev,
					       "ti,charge-current",
					       &bq->init_data.अक्षरge_current);
		अगर (ret)
			जाओ error_2;
		ret = device_property_पढ़ो_u32(bq->dev,
				"ti,termination-current",
				&bq->init_data.termination_current);
		अगर (ret)
			जाओ error_2;
		ret = device_property_पढ़ो_u32(bq->dev,
					       "ti,resistor-sense",
					       &bq->init_data.resistor_sense);
		अगर (ret)
			जाओ error_2;
		अगर (np)
			bq->notअगरy_node = of_parse_phandle(np,
						"ti,usb-charger-detection", 0);
	पूर्ण अन्यथा अणु
		स_नकल(&bq->init_data, pdata, माप(bq->init_data));
	पूर्ण

	bq2415x_reset_chip(bq);

	ret = bq2415x_घातer_supply_init(bq);
	अगर (ret) अणु
		dev_err(bq->dev, "failed to register power supply: %d\n", ret);
		जाओ error_2;
	पूर्ण

	ret = bq2415x_set_शेषs(bq);
	अगर (ret) अणु
		dev_err(bq->dev, "failed to set default values: %d\n", ret);
		जाओ error_3;
	पूर्ण

	अगर (bq->notअगरy_node || bq->init_data.notअगरy_device) अणु
		bq->nb.notअगरier_call = bq2415x_notअगरier_call;
		ret = घातer_supply_reg_notअगरier(&bq->nb);
		अगर (ret) अणु
			dev_err(bq->dev, "failed to reg notifier: %d\n", ret);
			जाओ error_3;
		पूर्ण

		bq->स्वतःmode = 1;
		dev_info(bq->dev, "automode supported, waiting for events\n");
	पूर्ण अन्यथा अणु
		bq->स्वतःmode = -1;
		dev_info(bq->dev, "automode not supported\n");
	पूर्ण

	/* Query क्रम initial reported_mode and set it */
	अगर (bq->nb.notअगरier_call) अणु
		अगर (np) अणु
			notअगरy_psy = घातer_supply_get_by_phandle(np,
						"ti,usb-charger-detection");
			अगर (IS_ERR(notअगरy_psy))
				notअगरy_psy = शून्य;
		पूर्ण अन्यथा अगर (bq->init_data.notअगरy_device) अणु
			notअगरy_psy = घातer_supply_get_by_name(
						bq->init_data.notअगरy_device);
		पूर्ण
	पूर्ण
	अगर (notअगरy_psy) अणु
		ret = घातer_supply_get_property(notअगरy_psy,
					POWER_SUPPLY_PROP_CURRENT_MAX, &prop);
		घातer_supply_put(notअगरy_psy);

		अगर (ret == 0) अणु
			bq2415x_update_reported_mode(bq, prop.पूर्णांकval);
			bq2415x_set_mode(bq, bq->reported_mode);
		पूर्ण
	पूर्ण

	INIT_DELAYED_WORK(&bq->work, bq2415x_समयr_work);
	bq2415x_set_स्वतःसमयr(bq, 1);

	dev_info(bq->dev, "driver registered\n");
	वापस 0;

error_3:
	bq2415x_घातer_supply_निकास(bq);
error_2:
	अगर (bq)
		of_node_put(bq->notअगरy_node);
	kमुक्त(name);
error_1:
	mutex_lock(&bq2415x_id_mutex);
	idr_हटाओ(&bq2415x_id, num);
	mutex_unlock(&bq2415x_id_mutex);

	वापस ret;
पूर्ण

/* मुख्य bq2415x हटाओ function */

अटल पूर्णांक bq2415x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bq2415x_device *bq = i2c_get_clientdata(client);

	अगर (bq->nb.notअगरier_call)
		घातer_supply_unreg_notअगरier(&bq->nb);

	of_node_put(bq->notअगरy_node);
	bq2415x_घातer_supply_निकास(bq);

	bq2415x_reset_chip(bq);

	mutex_lock(&bq2415x_id_mutex);
	idr_हटाओ(&bq2415x_id, bq->id);
	mutex_unlock(&bq2415x_id_mutex);

	dev_info(bq->dev, "driver unregistered\n");

	kमुक्त(bq->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bq2415x_i2c_id_table[] = अणु
	अणु "bq2415x", BQUNKNOWN पूर्ण,
	अणु "bq24150", BQ24150 पूर्ण,
	अणु "bq24150a", BQ24150A पूर्ण,
	अणु "bq24151", BQ24151 पूर्ण,
	अणु "bq24151a", BQ24151A पूर्ण,
	अणु "bq24152", BQ24152 पूर्ण,
	अणु "bq24153", BQ24153 पूर्ण,
	अणु "bq24153a", BQ24153A पूर्ण,
	अणु "bq24155", BQ24155 पूर्ण,
	अणु "bq24156", BQ24156 पूर्ण,
	अणु "bq24156a", BQ24156A पूर्ण,
	अणु "bq24157s", BQ24157S पूर्ण,
	अणु "bq24158", BQ24158 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq2415x_i2c_id_table);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id bq2415x_i2c_acpi_match[] = अणु
	अणु "BQ2415X", BQUNKNOWN पूर्ण,
	अणु "BQ241500", BQ24150 पूर्ण,
	अणु "BQA24150", BQ24150A पूर्ण,
	अणु "BQ241510", BQ24151 पूर्ण,
	अणु "BQA24151", BQ24151A पूर्ण,
	अणु "BQ241520", BQ24152 पूर्ण,
	अणु "BQ241530", BQ24153 पूर्ण,
	अणु "BQA24153", BQ24153A पूर्ण,
	अणु "BQ241550", BQ24155 पूर्ण,
	अणु "BQ241560", BQ24156 पूर्ण,
	अणु "BQA24156", BQ24156A पूर्ण,
	अणु "BQS24157", BQ24157S पूर्ण,
	अणु "BQ241580", BQ24158 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bq2415x_i2c_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id bq2415x_of_match_table[] = अणु
	अणु .compatible = "ti,bq24150" पूर्ण,
	अणु .compatible = "ti,bq24150a" पूर्ण,
	अणु .compatible = "ti,bq24151" पूर्ण,
	अणु .compatible = "ti,bq24151a" पूर्ण,
	अणु .compatible = "ti,bq24152" पूर्ण,
	अणु .compatible = "ti,bq24153" पूर्ण,
	अणु .compatible = "ti,bq24153a" पूर्ण,
	अणु .compatible = "ti,bq24155" पूर्ण,
	अणु .compatible = "ti,bq24156" पूर्ण,
	अणु .compatible = "ti,bq24156a" पूर्ण,
	अणु .compatible = "ti,bq24157s" पूर्ण,
	अणु .compatible = "ti,bq24158" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq2415x_of_match_table);
#पूर्ण_अगर

अटल काष्ठा i2c_driver bq2415x_driver = अणु
	.driver = अणु
		.name = "bq2415x-charger",
		.of_match_table = of_match_ptr(bq2415x_of_match_table),
		.acpi_match_table = ACPI_PTR(bq2415x_i2c_acpi_match),
	पूर्ण,
	.probe = bq2415x_probe,
	.हटाओ = bq2415x_हटाओ,
	.id_table = bq2415x_i2c_id_table,
पूर्ण;
module_i2c_driver(bq2415x_driver);

MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_DESCRIPTION("bq2415x charger driver");
MODULE_LICENSE("GPL");
