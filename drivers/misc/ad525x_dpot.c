<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ad525x_dpot: Driver क्रम the Analog Devices digital potentiometers
 * Copyright (c) 2009-2010 Analog Devices, Inc.
 * Author: Michael Hennerich <michael.hennerich@analog.com>
 *
 * DEVID		#Wipers		#Positions	Resistor Options (kOhm)
 * AD5258		1		64		1, 10, 50, 100
 * AD5259		1		256		5, 10, 50, 100
 * AD5251		2		64		1, 10, 50, 100
 * AD5252		2		256		1, 10, 50, 100
 * AD5255		3		512		25, 250
 * AD5253		4		64		1, 10, 50, 100
 * AD5254		4		256		1, 10, 50, 100
 * AD5160		1		256		5, 10, 50, 100
 * AD5161		1		256		5, 10, 50, 100
 * AD5162		2		256		2.5, 10, 50, 100
 * AD5165		1		256		100
 * AD5200		1		256		10, 50
 * AD5201		1		33		10, 50
 * AD5203		4		64		10, 100
 * AD5204		4		256		10, 50, 100
 * AD5206		6		256		10, 50, 100
 * AD5207		2		256		10, 50, 100
 * AD5231		1		1024		10, 50, 100
 * AD5232		2		256		10, 50, 100
 * AD5233		4		64		10, 50, 100
 * AD5235		2		1024		25, 250
 * AD5260		1		256		20, 50, 200
 * AD5262		2		256		20, 50, 200
 * AD5263		4		256		20, 50, 200
 * AD5290		1		256		10, 50, 100
 * AD5291		1		256		20, 50, 100  (20-TP)
 * AD5292		1		1024		20, 50, 100  (20-TP)
 * AD5293		1		1024		20, 50, 100
 * AD7376		1		128		10, 50, 100, 1M
 * AD8400		1		256		1, 10, 50, 100
 * AD8402		2		256		1, 10, 50, 100
 * AD8403		4		256		1, 10, 50, 100
 * ADN2850		3		512		25, 250
 * AD5241		1		256		10, 100, 1M
 * AD5246		1		128		5, 10, 50, 100
 * AD5247		1		128		5, 10, 50, 100
 * AD5245		1		256		5, 10, 50, 100
 * AD5243		2		256		2.5, 10, 50, 100
 * AD5248		2		256		2.5, 10, 50, 100
 * AD5242		2		256		20, 50, 200
 * AD5280		1		256		20, 50, 200
 * AD5282		2		256		20, 50, 200
 * ADN2860		3		512		25, 250
 * AD5273		1		64		1, 10, 50, 100 (OTP)
 * AD5171		1		64		5, 10, 50, 100 (OTP)
 * AD5170		1		256		2.5, 10, 50, 100 (OTP)
 * AD5172		2		256		2.5, 10, 50, 100 (OTP)
 * AD5173		2		256		2.5, 10, 50, 100 (OTP)
 * AD5270		1		1024		20, 50, 100 (50-TP)
 * AD5271		1		256		20, 50, 100 (50-TP)
 * AD5272		1		1024		20, 50, 100 (50-TP)
 * AD5274		1		256		20, 50, 100 (50-TP)
 *
 * See Documentation/misc-devices/ad525x_dpot.rst क्रम more info.
 *
 * derived from ad5258.c
 * Copyright (c) 2009 Cyber Switching, Inc.
 * Author: Chris Verges <chrisv@cyberचयनing.com>
 *
 * derived from ad5252.c
 * Copyright (c) 2006-2011 Michael Hennerich <michael.hennerich@analog.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "ad525x_dpot.h"

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा dpot_data अणु
	काष्ठा ad_dpot_bus_data	bdata;
	काष्ठा mutex update_lock;
	अचिन्हित पूर्णांक rdac_mask;
	अचिन्हित पूर्णांक max_pos;
	अचिन्हित दीर्घ devid;
	अचिन्हित पूर्णांक uid;
	अचिन्हित पूर्णांक feat;
	अचिन्हित पूर्णांक wipers;
	u16 rdac_cache[MAX_RDACS];
	DECLARE_BITMAP(otp_en_mask, MAX_RDACS);
पूर्ण;

अटल अंतरभूत पूर्णांक dpot_पढ़ो_d8(काष्ठा dpot_data *dpot)
अणु
	वापस dpot->bdata.bops->पढ़ो_d8(dpot->bdata.client);
पूर्ण

अटल अंतरभूत पूर्णांक dpot_पढ़ो_r8d8(काष्ठा dpot_data *dpot, u8 reg)
अणु
	वापस dpot->bdata.bops->पढ़ो_r8d8(dpot->bdata.client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक dpot_पढ़ो_r8d16(काष्ठा dpot_data *dpot, u8 reg)
अणु
	वापस dpot->bdata.bops->पढ़ो_r8d16(dpot->bdata.client, reg);
पूर्ण

अटल अंतरभूत पूर्णांक dpot_ग_लिखो_d8(काष्ठा dpot_data *dpot, u8 val)
अणु
	वापस dpot->bdata.bops->ग_लिखो_d8(dpot->bdata.client, val);
पूर्ण

अटल अंतरभूत पूर्णांक dpot_ग_लिखो_r8d8(काष्ठा dpot_data *dpot, u8 reg, u16 val)
अणु
	वापस dpot->bdata.bops->ग_लिखो_r8d8(dpot->bdata.client, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक dpot_ग_लिखो_r8d16(काष्ठा dpot_data *dpot, u8 reg, u16 val)
अणु
	वापस dpot->bdata.bops->ग_लिखो_r8d16(dpot->bdata.client, reg, val);
पूर्ण

अटल s32 dpot_पढ़ो_spi(काष्ठा dpot_data *dpot, u8 reg)
अणु
	अचिन्हित पूर्णांक ctrl = 0;
	पूर्णांक value;

	अगर (!(reg & (DPOT_ADDR_EEPROM | DPOT_ADDR_CMD))) अणु

		अगर (dpot->feat & F_RDACS_WONLY)
			वापस dpot->rdac_cache[reg & DPOT_RDAC_MASK];
		अगर (dpot->uid == DPOT_UID(AD5291_ID) ||
			dpot->uid == DPOT_UID(AD5292_ID) ||
			dpot->uid == DPOT_UID(AD5293_ID)) अणु

			value = dpot_पढ़ो_r8d8(dpot,
				DPOT_AD5291_READ_RDAC << 2);

			अगर (value < 0)
				वापस value;

			अगर (dpot->uid == DPOT_UID(AD5291_ID))
				value = value >> 2;

			वापस value;
		पूर्ण अन्यथा अगर (dpot->uid == DPOT_UID(AD5270_ID) ||
			dpot->uid == DPOT_UID(AD5271_ID)) अणु

			value = dpot_पढ़ो_r8d8(dpot,
				DPOT_AD5270_1_2_4_READ_RDAC << 2);

			अगर (value < 0)
				वापस value;

			अगर (dpot->uid == DPOT_UID(AD5271_ID))
				value = value >> 2;

			वापस value;
		पूर्ण

		ctrl = DPOT_SPI_READ_RDAC;
	पूर्ण अन्यथा अगर (reg & DPOT_ADDR_EEPROM) अणु
		ctrl = DPOT_SPI_READ_EEPROM;
	पूर्ण

	अगर (dpot->feat & F_SPI_16BIT)
		वापस dpot_पढ़ो_r8d8(dpot, ctrl);
	अन्यथा अगर (dpot->feat & F_SPI_24BIT)
		वापस dpot_पढ़ो_r8d16(dpot, ctrl);

	वापस -EFAULT;
पूर्ण

अटल s32 dpot_पढ़ो_i2c(काष्ठा dpot_data *dpot, u8 reg)
अणु
	पूर्णांक value;
	अचिन्हित पूर्णांक ctrl = 0;

	चयन (dpot->uid) अणु
	हाल DPOT_UID(AD5246_ID):
	हाल DPOT_UID(AD5247_ID):
		वापस dpot_पढ़ो_d8(dpot);
	हाल DPOT_UID(AD5245_ID):
	हाल DPOT_UID(AD5241_ID):
	हाल DPOT_UID(AD5242_ID):
	हाल DPOT_UID(AD5243_ID):
	हाल DPOT_UID(AD5248_ID):
	हाल DPOT_UID(AD5280_ID):
	हाल DPOT_UID(AD5282_ID):
		ctrl = ((reg & DPOT_RDAC_MASK) == DPOT_RDAC0) ?
			0 : DPOT_AD5282_RDAC_AB;
		वापस dpot_पढ़ो_r8d8(dpot, ctrl);
	हाल DPOT_UID(AD5170_ID):
	हाल DPOT_UID(AD5171_ID):
	हाल DPOT_UID(AD5273_ID):
			वापस dpot_पढ़ो_d8(dpot);
	हाल DPOT_UID(AD5172_ID):
	हाल DPOT_UID(AD5173_ID):
		ctrl = ((reg & DPOT_RDAC_MASK) == DPOT_RDAC0) ?
			0 : DPOT_AD5172_3_A0;
		वापस dpot_पढ़ो_r8d8(dpot, ctrl);
	हाल DPOT_UID(AD5272_ID):
	हाल DPOT_UID(AD5274_ID):
		dpot_ग_लिखो_r8d8(dpot,
				(DPOT_AD5270_1_2_4_READ_RDAC << 2), 0);

		value = dpot_पढ़ो_r8d16(dpot, DPOT_AD5270_1_2_4_RDAC << 2);
		अगर (value < 0)
			वापस value;
		/*
		 * AD5272/AD5274 वापसs high byte first, however
		 * underling smbus expects low byte first.
		 */
		value = swab16(value);

		अगर (dpot->uid == DPOT_UID(AD5274_ID))
			value = value >> 2;
		वापस value;
	शेष:
		अगर ((reg & DPOT_REG_TOL) || (dpot->max_pos > 256))
			वापस dpot_पढ़ो_r8d16(dpot, (reg & 0xF8) |
					((reg & 0x7) << 1));
		अन्यथा
			वापस dpot_पढ़ो_r8d8(dpot, reg);
	पूर्ण
पूर्ण

अटल s32 dpot_पढ़ो(काष्ठा dpot_data *dpot, u8 reg)
अणु
	अगर (dpot->feat & F_SPI)
		वापस dpot_पढ़ो_spi(dpot, reg);
	अन्यथा
		वापस dpot_पढ़ो_i2c(dpot, reg);
पूर्ण

अटल s32 dpot_ग_लिखो_spi(काष्ठा dpot_data *dpot, u8 reg, u16 value)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (!(reg & (DPOT_ADDR_EEPROM | DPOT_ADDR_CMD | DPOT_ADDR_OTP))) अणु
		अगर (dpot->feat & F_RDACS_WONLY)
			dpot->rdac_cache[reg & DPOT_RDAC_MASK] = value;

		अगर (dpot->feat & F_AD_APPDATA) अणु
			अगर (dpot->feat & F_SPI_8BIT) अणु
				val = ((reg & DPOT_RDAC_MASK) <<
					DPOT_MAX_POS(dpot->devid)) |
					value;
				वापस dpot_ग_लिखो_d8(dpot, val);
			पूर्ण अन्यथा अगर (dpot->feat & F_SPI_16BIT) अणु
				val = ((reg & DPOT_RDAC_MASK) <<
					DPOT_MAX_POS(dpot->devid)) |
					value;
				वापस dpot_ग_लिखो_r8d8(dpot, val >> 8,
					val & 0xFF);
			पूर्ण अन्यथा
				BUG();
		पूर्ण अन्यथा अणु
			अगर (dpot->uid == DPOT_UID(AD5291_ID) ||
				dpot->uid == DPOT_UID(AD5292_ID) ||
				dpot->uid == DPOT_UID(AD5293_ID)) अणु

				dpot_ग_लिखो_r8d8(dpot, DPOT_AD5291_CTRLREG << 2,
						DPOT_AD5291_UNLOCK_CMD);

				अगर (dpot->uid == DPOT_UID(AD5291_ID))
					value = value << 2;

				वापस dpot_ग_लिखो_r8d8(dpot,
					(DPOT_AD5291_RDAC << 2) |
					(value >> 8), value & 0xFF);
			पूर्ण अन्यथा अगर (dpot->uid == DPOT_UID(AD5270_ID) ||
				dpot->uid == DPOT_UID(AD5271_ID)) अणु
				dpot_ग_लिखो_r8d8(dpot,
						DPOT_AD5270_1_2_4_CTRLREG << 2,
						DPOT_AD5270_1_2_4_UNLOCK_CMD);

				अगर (dpot->uid == DPOT_UID(AD5271_ID))
					value = value << 2;

				वापस dpot_ग_लिखो_r8d8(dpot,
					(DPOT_AD5270_1_2_4_RDAC << 2) |
					(value >> 8), value & 0xFF);
			पूर्ण
			val = DPOT_SPI_RDAC | (reg & DPOT_RDAC_MASK);
		पूर्ण
	पूर्ण अन्यथा अगर (reg & DPOT_ADDR_EEPROM) अणु
		val = DPOT_SPI_EEPROM | (reg & DPOT_RDAC_MASK);
	पूर्ण अन्यथा अगर (reg & DPOT_ADDR_CMD) अणु
		चयन (reg) अणु
		हाल DPOT_DEC_ALL_6DB:
			val = DPOT_SPI_DEC_ALL_6DB;
			अवरोध;
		हाल DPOT_INC_ALL_6DB:
			val = DPOT_SPI_INC_ALL_6DB;
			अवरोध;
		हाल DPOT_DEC_ALL:
			val = DPOT_SPI_DEC_ALL;
			अवरोध;
		हाल DPOT_INC_ALL:
			val = DPOT_SPI_INC_ALL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (reg & DPOT_ADDR_OTP) अणु
		अगर (dpot->uid == DPOT_UID(AD5291_ID) ||
			dpot->uid == DPOT_UID(AD5292_ID)) अणु
			वापस dpot_ग_लिखो_r8d8(dpot,
				DPOT_AD5291_STORE_XTPM << 2, 0);
		पूर्ण अन्यथा अगर (dpot->uid == DPOT_UID(AD5270_ID) ||
			dpot->uid == DPOT_UID(AD5271_ID)) अणु
			वापस dpot_ग_लिखो_r8d8(dpot,
				DPOT_AD5270_1_2_4_STORE_XTPM << 2, 0);
		पूर्ण
	पूर्ण अन्यथा
		BUG();

	अगर (dpot->feat & F_SPI_16BIT)
		वापस dpot_ग_लिखो_r8d8(dpot, val, value);
	अन्यथा अगर (dpot->feat & F_SPI_24BIT)
		वापस dpot_ग_लिखो_r8d16(dpot, val, value);

	वापस -EFAULT;
पूर्ण

अटल s32 dpot_ग_लिखो_i2c(काष्ठा dpot_data *dpot, u8 reg, u16 value)
अणु
	/* Only ग_लिखो the inकाष्ठाion byte क्रम certain commands */
	अचिन्हित पूर्णांक पंचांगp = 0, ctrl = 0;

	चयन (dpot->uid) अणु
	हाल DPOT_UID(AD5246_ID):
	हाल DPOT_UID(AD5247_ID):
		वापस dpot_ग_लिखो_d8(dpot, value);

	हाल DPOT_UID(AD5245_ID):
	हाल DPOT_UID(AD5241_ID):
	हाल DPOT_UID(AD5242_ID):
	हाल DPOT_UID(AD5243_ID):
	हाल DPOT_UID(AD5248_ID):
	हाल DPOT_UID(AD5280_ID):
	हाल DPOT_UID(AD5282_ID):
		ctrl = ((reg & DPOT_RDAC_MASK) == DPOT_RDAC0) ?
			0 : DPOT_AD5282_RDAC_AB;
		वापस dpot_ग_लिखो_r8d8(dpot, ctrl, value);
	हाल DPOT_UID(AD5171_ID):
	हाल DPOT_UID(AD5273_ID):
		अगर (reg & DPOT_ADDR_OTP) अणु
			पंचांगp = dpot_पढ़ो_d8(dpot);
			अगर (पंचांगp >> 6) /* Ready to Program? */
				वापस -EFAULT;
			ctrl = DPOT_AD5273_FUSE;
		पूर्ण
		वापस dpot_ग_लिखो_r8d8(dpot, ctrl, value);
	हाल DPOT_UID(AD5172_ID):
	हाल DPOT_UID(AD5173_ID):
		ctrl = ((reg & DPOT_RDAC_MASK) == DPOT_RDAC0) ?
			0 : DPOT_AD5172_3_A0;
		अगर (reg & DPOT_ADDR_OTP) अणु
			पंचांगp = dpot_पढ़ो_r8d16(dpot, ctrl);
			अगर (पंचांगp >> 14) /* Ready to Program? */
				वापस -EFAULT;
			ctrl |= DPOT_AD5170_2_3_FUSE;
		पूर्ण
		वापस dpot_ग_लिखो_r8d8(dpot, ctrl, value);
	हाल DPOT_UID(AD5170_ID):
		अगर (reg & DPOT_ADDR_OTP) अणु
			पंचांगp = dpot_पढ़ो_r8d16(dpot, पंचांगp);
			अगर (पंचांगp >> 14) /* Ready to Program? */
				वापस -EFAULT;
			ctrl = DPOT_AD5170_2_3_FUSE;
		पूर्ण
		वापस dpot_ग_लिखो_r8d8(dpot, ctrl, value);
	हाल DPOT_UID(AD5272_ID):
	हाल DPOT_UID(AD5274_ID):
		dpot_ग_लिखो_r8d8(dpot, DPOT_AD5270_1_2_4_CTRLREG << 2,
				DPOT_AD5270_1_2_4_UNLOCK_CMD);

		अगर (reg & DPOT_ADDR_OTP)
			वापस dpot_ग_लिखो_r8d8(dpot,
					DPOT_AD5270_1_2_4_STORE_XTPM << 2, 0);

		अगर (dpot->uid == DPOT_UID(AD5274_ID))
			value = value << 2;

		वापस dpot_ग_लिखो_r8d8(dpot, (DPOT_AD5270_1_2_4_RDAC << 2) |
				       (value >> 8), value & 0xFF);
	शेष:
		अगर (reg & DPOT_ADDR_CMD)
			वापस dpot_ग_लिखो_d8(dpot, reg);

		अगर (dpot->max_pos > 256)
			वापस dpot_ग_लिखो_r8d16(dpot, (reg & 0xF8) |
						((reg & 0x7) << 1), value);
		अन्यथा
			/* All other रेजिस्टरs require inकाष्ठाion + data bytes */
			वापस dpot_ग_लिखो_r8d8(dpot, reg, value);
	पूर्ण
पूर्ण

अटल s32 dpot_ग_लिखो(काष्ठा dpot_data *dpot, u8 reg, u16 value)
अणु
	अगर (dpot->feat & F_SPI)
		वापस dpot_ग_लिखो_spi(dpot, reg, value);
	अन्यथा
		वापस dpot_ग_लिखो_i2c(dpot, reg, value);
पूर्ण

/* sysfs functions */

अटल sमाप_प्रकार sysfs_show_reg(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf, u32 reg)
अणु
	काष्ठा dpot_data *data = dev_get_drvdata(dev);
	s32 value;

	अगर (reg & DPOT_ADDR_OTP_EN)
		वापस प्र_लिखो(buf, "%s\n",
			test_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask) ?
			"enabled" : "disabled");


	mutex_lock(&data->update_lock);
	value = dpot_पढ़ो(data, reg);
	mutex_unlock(&data->update_lock);

	अगर (value < 0)
		वापस -EINVAL;
	/*
	 * Let someone अन्यथा deal with converting this ...
	 * the tolerance is a two-byte value where the MSB
	 * is a sign + पूर्णांकeger value, and the LSB is a
	 * decimal value.  See page 18 of the AD5258
	 * datasheet (Rev. A) क्रम more details.
	 */

	अगर (reg & DPOT_REG_TOL)
		वापस प्र_लिखो(buf, "0x%04x\n", value & 0xFFFF);
	अन्यथा
		वापस प्र_लिखो(buf, "%u\n", value & data->rdac_mask);
पूर्ण

अटल sमाप_प्रकार sysfs_set_reg(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count, u32 reg)
अणु
	काष्ठा dpot_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक err;

	अगर (reg & DPOT_ADDR_OTP_EN) अणु
		अगर (sysfs_streq(buf, "enabled"))
			set_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask);
		अन्यथा
			clear_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask);

		वापस count;
	पूर्ण

	अगर ((reg & DPOT_ADDR_OTP) &&
		!test_bit(DPOT_RDAC_MASK & reg, data->otp_en_mask))
		वापस -EPERM;

	err = kम_से_अदीर्घ(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value > data->rdac_mask)
		value = data->rdac_mask;

	mutex_lock(&data->update_lock);
	dpot_ग_लिखो(data, reg, value);
	अगर (reg & DPOT_ADDR_EEPROM)
		msleep(26);	/* Sleep जबतक the EEPROM updates */
	अन्यथा अगर (reg & DPOT_ADDR_OTP)
		msleep(400);	/* Sleep जबतक the OTP updates */
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार sysfs_करो_cmd(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count, u32 reg)
अणु
	काष्ठा dpot_data *data = dev_get_drvdata(dev);

	mutex_lock(&data->update_lock);
	dpot_ग_लिखो(data, reg, 0);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* ------------------------------------------------------------------------- */

#घोषणा DPOT_DEVICE_SHOW(_name, _reg) अटल sमाप_प्रकार \
show_##_name(काष्ठा device *dev, \
			  काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	वापस sysfs_show_reg(dev, attr, buf, _reg); \
पूर्ण

#घोषणा DPOT_DEVICE_SET(_name, _reg) अटल sमाप_प्रकार \
set_##_name(काष्ठा device *dev, \
			 काष्ठा device_attribute *attr, \
			 स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	वापस sysfs_set_reg(dev, attr, buf, count, _reg); \
पूर्ण

#घोषणा DPOT_DEVICE_SHOW_SET(name, reg) \
DPOT_DEVICE_SHOW(name, reg) \
DPOT_DEVICE_SET(name, reg) \
अटल DEVICE_ATTR(name, S_IWUSR | S_IRUGO, show_##name, set_##name)

#घोषणा DPOT_DEVICE_SHOW_ONLY(name, reg) \
DPOT_DEVICE_SHOW(name, reg) \
अटल DEVICE_ATTR(name, S_IWUSR | S_IRUGO, show_##name, शून्य)

DPOT_DEVICE_SHOW_SET(rdac0, DPOT_ADDR_RDAC | DPOT_RDAC0);
DPOT_DEVICE_SHOW_SET(eeprom0, DPOT_ADDR_EEPROM | DPOT_RDAC0);
DPOT_DEVICE_SHOW_ONLY(tolerance0, DPOT_ADDR_EEPROM | DPOT_TOL_RDAC0);
DPOT_DEVICE_SHOW_SET(otp0, DPOT_ADDR_OTP | DPOT_RDAC0);
DPOT_DEVICE_SHOW_SET(otp0en, DPOT_ADDR_OTP_EN | DPOT_RDAC0);

DPOT_DEVICE_SHOW_SET(rdac1, DPOT_ADDR_RDAC | DPOT_RDAC1);
DPOT_DEVICE_SHOW_SET(eeprom1, DPOT_ADDR_EEPROM | DPOT_RDAC1);
DPOT_DEVICE_SHOW_ONLY(tolerance1, DPOT_ADDR_EEPROM | DPOT_TOL_RDAC1);
DPOT_DEVICE_SHOW_SET(otp1, DPOT_ADDR_OTP | DPOT_RDAC1);
DPOT_DEVICE_SHOW_SET(otp1en, DPOT_ADDR_OTP_EN | DPOT_RDAC1);

DPOT_DEVICE_SHOW_SET(rdac2, DPOT_ADDR_RDAC | DPOT_RDAC2);
DPOT_DEVICE_SHOW_SET(eeprom2, DPOT_ADDR_EEPROM | DPOT_RDAC2);
DPOT_DEVICE_SHOW_ONLY(tolerance2, DPOT_ADDR_EEPROM | DPOT_TOL_RDAC2);
DPOT_DEVICE_SHOW_SET(otp2, DPOT_ADDR_OTP | DPOT_RDAC2);
DPOT_DEVICE_SHOW_SET(otp2en, DPOT_ADDR_OTP_EN | DPOT_RDAC2);

DPOT_DEVICE_SHOW_SET(rdac3, DPOT_ADDR_RDAC | DPOT_RDAC3);
DPOT_DEVICE_SHOW_SET(eeprom3, DPOT_ADDR_EEPROM | DPOT_RDAC3);
DPOT_DEVICE_SHOW_ONLY(tolerance3, DPOT_ADDR_EEPROM | DPOT_TOL_RDAC3);
DPOT_DEVICE_SHOW_SET(otp3, DPOT_ADDR_OTP | DPOT_RDAC3);
DPOT_DEVICE_SHOW_SET(otp3en, DPOT_ADDR_OTP_EN | DPOT_RDAC3);

DPOT_DEVICE_SHOW_SET(rdac4, DPOT_ADDR_RDAC | DPOT_RDAC4);
DPOT_DEVICE_SHOW_SET(eeprom4, DPOT_ADDR_EEPROM | DPOT_RDAC4);
DPOT_DEVICE_SHOW_ONLY(tolerance4, DPOT_ADDR_EEPROM | DPOT_TOL_RDAC4);
DPOT_DEVICE_SHOW_SET(otp4, DPOT_ADDR_OTP | DPOT_RDAC4);
DPOT_DEVICE_SHOW_SET(otp4en, DPOT_ADDR_OTP_EN | DPOT_RDAC4);

DPOT_DEVICE_SHOW_SET(rdac5, DPOT_ADDR_RDAC | DPOT_RDAC5);
DPOT_DEVICE_SHOW_SET(eeprom5, DPOT_ADDR_EEPROM | DPOT_RDAC5);
DPOT_DEVICE_SHOW_ONLY(tolerance5, DPOT_ADDR_EEPROM | DPOT_TOL_RDAC5);
DPOT_DEVICE_SHOW_SET(otp5, DPOT_ADDR_OTP | DPOT_RDAC5);
DPOT_DEVICE_SHOW_SET(otp5en, DPOT_ADDR_OTP_EN | DPOT_RDAC5);

अटल स्थिर काष्ठा attribute *dpot_attrib_wipers[] = अणु
	&dev_attr_rdac0.attr,
	&dev_attr_rdac1.attr,
	&dev_attr_rdac2.attr,
	&dev_attr_rdac3.attr,
	&dev_attr_rdac4.attr,
	&dev_attr_rdac5.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute *dpot_attrib_eeprom[] = अणु
	&dev_attr_eeprom0.attr,
	&dev_attr_eeprom1.attr,
	&dev_attr_eeprom2.attr,
	&dev_attr_eeprom3.attr,
	&dev_attr_eeprom4.attr,
	&dev_attr_eeprom5.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute *dpot_attrib_otp[] = अणु
	&dev_attr_otp0.attr,
	&dev_attr_otp1.attr,
	&dev_attr_otp2.attr,
	&dev_attr_otp3.attr,
	&dev_attr_otp4.attr,
	&dev_attr_otp5.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute *dpot_attrib_otp_en[] = अणु
	&dev_attr_otp0en.attr,
	&dev_attr_otp1en.attr,
	&dev_attr_otp2en.attr,
	&dev_attr_otp3en.attr,
	&dev_attr_otp4en.attr,
	&dev_attr_otp5en.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute *dpot_attrib_tolerance[] = अणु
	&dev_attr_tolerance0.attr,
	&dev_attr_tolerance1.attr,
	&dev_attr_tolerance2.attr,
	&dev_attr_tolerance3.attr,
	&dev_attr_tolerance4.attr,
	&dev_attr_tolerance5.attr,
	शून्य
पूर्ण;

/* ------------------------------------------------------------------------- */

#घोषणा DPOT_DEVICE_DO_CMD(_name, _cmd) अटल sमाप_प्रकार \
set_##_name(काष्ठा device *dev, \
			 काष्ठा device_attribute *attr, \
			 स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	वापस sysfs_करो_cmd(dev, attr, buf, count, _cmd); \
पूर्ण \
अटल DEVICE_ATTR(_name, S_IWUSR | S_IRUGO, शून्य, set_##_name)

DPOT_DEVICE_DO_CMD(inc_all, DPOT_INC_ALL);
DPOT_DEVICE_DO_CMD(dec_all, DPOT_DEC_ALL);
DPOT_DEVICE_DO_CMD(inc_all_6db, DPOT_INC_ALL_6DB);
DPOT_DEVICE_DO_CMD(dec_all_6db, DPOT_DEC_ALL_6DB);

अटल काष्ठा attribute *ad525x_attributes_commands[] = अणु
	&dev_attr_inc_all.attr,
	&dev_attr_dec_all.attr,
	&dev_attr_inc_all_6db.attr,
	&dev_attr_dec_all_6db.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad525x_group_commands = अणु
	.attrs = ad525x_attributes_commands,
पूर्ण;

अटल पूर्णांक ad_dpot_add_files(काष्ठा device *dev,
		अचिन्हित पूर्णांक features, अचिन्हित पूर्णांक rdac)
अणु
	पूर्णांक err = sysfs_create_file(&dev->kobj,
		dpot_attrib_wipers[rdac]);
	अगर (features & F_CMD_EEP)
		err |= sysfs_create_file(&dev->kobj,
			dpot_attrib_eeprom[rdac]);
	अगर (features & F_CMD_TOL)
		err |= sysfs_create_file(&dev->kobj,
			dpot_attrib_tolerance[rdac]);
	अगर (features & F_CMD_OTP) अणु
		err |= sysfs_create_file(&dev->kobj,
			dpot_attrib_otp_en[rdac]);
		err |= sysfs_create_file(&dev->kobj,
			dpot_attrib_otp[rdac]);
	पूर्ण

	अगर (err)
		dev_err(dev, "failed to register sysfs hooks for RDAC%d\n",
			rdac);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम ad_dpot_हटाओ_files(काष्ठा device *dev,
		अचिन्हित पूर्णांक features, अचिन्हित पूर्णांक rdac)
अणु
	sysfs_हटाओ_file(&dev->kobj,
		dpot_attrib_wipers[rdac]);
	अगर (features & F_CMD_EEP)
		sysfs_हटाओ_file(&dev->kobj,
			dpot_attrib_eeprom[rdac]);
	अगर (features & F_CMD_TOL)
		sysfs_हटाओ_file(&dev->kobj,
			dpot_attrib_tolerance[rdac]);
	अगर (features & F_CMD_OTP) अणु
		sysfs_हटाओ_file(&dev->kobj,
			dpot_attrib_otp_en[rdac]);
		sysfs_हटाओ_file(&dev->kobj,
			dpot_attrib_otp[rdac]);
	पूर्ण
पूर्ण

पूर्णांक ad_dpot_probe(काष्ठा device *dev,
		काष्ठा ad_dpot_bus_data *bdata, अचिन्हित दीर्घ devid,
			    स्थिर अक्षर *name)
अणु

	काष्ठा dpot_data *data;
	पूर्णांक i, err = 0;

	data = kzalloc(माप(काष्ठा dpot_data), GFP_KERNEL);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	dev_set_drvdata(dev, data);
	mutex_init(&data->update_lock);

	data->bdata = *bdata;
	data->devid = devid;

	data->max_pos = 1 << DPOT_MAX_POS(devid);
	data->rdac_mask = data->max_pos - 1;
	data->feat = DPOT_FEAT(devid);
	data->uid = DPOT_UID(devid);
	data->wipers = DPOT_WIPERS(devid);

	क्रम (i = DPOT_RDAC0; i < MAX_RDACS; i++)
		अगर (data->wipers & (1 << i)) अणु
			err = ad_dpot_add_files(dev, data->feat, i);
			अगर (err)
				जाओ निकास_हटाओ_files;
			/* घातer-up midscale */
			अगर (data->feat & F_RDACS_WONLY)
				data->rdac_cache[i] = data->max_pos / 2;
		पूर्ण

	अगर (data->feat & F_CMD_INC)
		err = sysfs_create_group(&dev->kobj, &ad525x_group_commands);

	अगर (err) अणु
		dev_err(dev, "failed to register sysfs hooks\n");
		जाओ निकास_मुक्त;
	पूर्ण

	dev_info(dev, "%s %d-Position Digital Potentiometer registered\n",
		 name, data->max_pos);

	वापस 0;

निकास_हटाओ_files:
	क्रम (i = DPOT_RDAC0; i < MAX_RDACS; i++)
		अगर (data->wipers & (1 << i))
			ad_dpot_हटाओ_files(dev, data->feat, i);

निकास_मुक्त:
	kमुक्त(data);
	dev_set_drvdata(dev, शून्य);
निकास:
	dev_err(dev, "failed to create client for %s ID 0x%lX\n",
		name, devid);
	वापस err;
पूर्ण
EXPORT_SYMBOL(ad_dpot_probe);

पूर्णांक ad_dpot_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा dpot_data *data = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = DPOT_RDAC0; i < MAX_RDACS; i++)
		अगर (data->wipers & (1 << i))
			ad_dpot_हटाओ_files(dev, data->feat, i);

	kमुक्त(data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ad_dpot_हटाओ);


MODULE_AUTHOR("Chris Verges <chrisv@cyberswitching.com>, "
	      "Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Digital potentiometer driver");
MODULE_LICENSE("GPL");
