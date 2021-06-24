<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  w83795.c - Linux kernel driver क्रम hardware monitoring
 *  Copyright (C) 2008 Nuvoton Technology Corp.
 *                Wei Song
 *  Copyright (C) 2010 Jean Delvare <jdelvare@suse.de>
 *
 *  Supports following chips:
 *
 *  Chip       #vin   #fanin #pwm #temp #dts wchipid  vendid  i2c  ISA
 *  w83795g     21     14     8     6     8    0x79   0x5ca3  yes   no
 *  w83795adg   18     14     2     6     8    0x79   0x5ca3  yes   no
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/util_macros.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x2c, 0x2d, 0x2e, 0x2f, I2C_CLIENT_END
पूर्ण;


अटल bool reset;
module_param(reset, bool, 0);
MODULE_PARM_DESC(reset, "Set to 1 to reset chip, not recommended");


#घोषणा W83795_REG_BANKSEL		0x00
#घोषणा W83795_REG_VENDORID		0xfd
#घोषणा W83795_REG_CHIPID		0xfe
#घोषणा W83795_REG_DEVICEID		0xfb
#घोषणा W83795_REG_DEVICEID_A		0xff

#घोषणा W83795_REG_I2C_ADDR		0xfc
#घोषणा W83795_REG_CONFIG		0x01
#घोषणा W83795_REG_CONFIG_CONFIG48	0x04
#घोषणा W83795_REG_CONFIG_START	0x01

/* Multi-Function Pin Ctrl Registers */
#घोषणा W83795_REG_VOLT_CTRL1		0x02
#घोषणा W83795_REG_VOLT_CTRL2		0x03
#घोषणा W83795_REG_TEMP_CTRL1		0x04
#घोषणा W83795_REG_TEMP_CTRL2		0x05
#घोषणा W83795_REG_FANIN_CTRL1		0x06
#घोषणा W83795_REG_FANIN_CTRL2		0x07
#घोषणा W83795_REG_VMIGB_CTRL		0x08

#घोषणा TEMP_READ			0
#घोषणा TEMP_CRIT			1
#घोषणा TEMP_CRIT_HYST			2
#घोषणा TEMP_WARN			3
#घोषणा TEMP_WARN_HYST			4
/*
 * only crit and crit_hyst affect real-समय alarm status
 * current crit crit_hyst warn warn_hyst
 */
अटल स्थिर u16 W83795_REG_TEMP[][5] = अणु
	अणु0x21, 0x96, 0x97, 0x98, 0x99पूर्ण,	/* TD1/TR1 */
	अणु0x22, 0x9a, 0x9b, 0x9c, 0x9dपूर्ण,	/* TD2/TR2 */
	अणु0x23, 0x9e, 0x9f, 0xa0, 0xa1पूर्ण,	/* TD3/TR3 */
	अणु0x24, 0xa2, 0xa3, 0xa4, 0xa5पूर्ण,	/* TD4/TR4 */
	अणु0x1f, 0xa6, 0xa7, 0xa8, 0xa9पूर्ण,	/* TR5 */
	अणु0x20, 0xaa, 0xab, 0xac, 0xadपूर्ण,	/* TR6 */
पूर्ण;

#घोषणा IN_READ				0
#घोषणा IN_MAX				1
#घोषणा IN_LOW				2
अटल स्थिर u16 W83795_REG_IN[][3] = अणु
	/* Current, HL, LL */
	अणु0x10, 0x70, 0x71पूर्ण,	/* VSEN1 */
	अणु0x11, 0x72, 0x73पूर्ण,	/* VSEN2 */
	अणु0x12, 0x74, 0x75पूर्ण,	/* VSEN3 */
	अणु0x13, 0x76, 0x77पूर्ण,	/* VSEN4 */
	अणु0x14, 0x78, 0x79पूर्ण,	/* VSEN5 */
	अणु0x15, 0x7a, 0x7bपूर्ण,	/* VSEN6 */
	अणु0x16, 0x7c, 0x7dपूर्ण,	/* VSEN7 */
	अणु0x17, 0x7e, 0x7fपूर्ण,	/* VSEN8 */
	अणु0x18, 0x80, 0x81पूर्ण,	/* VSEN9 */
	अणु0x19, 0x82, 0x83पूर्ण,	/* VSEN10 */
	अणु0x1A, 0x84, 0x85पूर्ण,	/* VSEN11 */
	अणु0x1B, 0x86, 0x87पूर्ण,	/* VTT */
	अणु0x1C, 0x88, 0x89पूर्ण,	/* 3VDD */
	अणु0x1D, 0x8a, 0x8bपूर्ण,	/* 3VSB */
	अणु0x1E, 0x8c, 0x8dपूर्ण,	/* VBAT */
	अणु0x1F, 0xa6, 0xa7पूर्ण,	/* VSEN12 */
	अणु0x20, 0xaa, 0xabपूर्ण,	/* VSEN13 */
	अणु0x21, 0x96, 0x97पूर्ण,	/* VSEN14 */
	अणु0x22, 0x9a, 0x9bपूर्ण,	/* VSEN15 */
	अणु0x23, 0x9e, 0x9fपूर्ण,	/* VSEN16 */
	अणु0x24, 0xa2, 0xa3पूर्ण,	/* VSEN17 */
पूर्ण;
#घोषणा W83795_REG_VRLSB		0x3C

अटल स्थिर u8 W83795_REG_IN_HL_LSB[] = अणु
	0x8e,	/* VSEN1-4 */
	0x90,	/* VSEN5-8 */
	0x92,	/* VSEN9-11 */
	0x94,	/* VTT, 3VDD, 3VSB, 3VBAT */
	0xa8,	/* VSEN12 */
	0xac,	/* VSEN13 */
	0x98,	/* VSEN14 */
	0x9c,	/* VSEN15 */
	0xa0,	/* VSEN16 */
	0xa4,	/* VSEN17 */
पूर्ण;

#घोषणा IN_LSB_REG(index, type) \
	(((type) == 1) ? W83795_REG_IN_HL_LSB[(index)] \
	: (W83795_REG_IN_HL_LSB[(index)] + 1))

#घोषणा IN_LSB_SHIFT			0
#घोषणा IN_LSB_IDX			1
अटल स्थिर u8 IN_LSB_SHIFT_IDX[][2] = अणु
	/* High/Low LSB shअगरt, LSB No. */
	अणु0x00, 0x00पूर्ण,	/* VSEN1 */
	अणु0x02, 0x00पूर्ण,	/* VSEN2 */
	अणु0x04, 0x00पूर्ण,	/* VSEN3 */
	अणु0x06, 0x00पूर्ण,	/* VSEN4 */
	अणु0x00, 0x01पूर्ण,	/* VSEN5 */
	अणु0x02, 0x01पूर्ण,	/* VSEN6 */
	अणु0x04, 0x01पूर्ण,	/* VSEN7 */
	अणु0x06, 0x01पूर्ण,	/* VSEN8 */
	अणु0x00, 0x02पूर्ण,	/* VSEN9 */
	अणु0x02, 0x02पूर्ण,	/* VSEN10 */
	अणु0x04, 0x02पूर्ण,	/* VSEN11 */
	अणु0x00, 0x03पूर्ण,	/* VTT */
	अणु0x02, 0x03पूर्ण,	/* 3VDD */
	अणु0x04, 0x03पूर्ण,	/* 3VSB	*/
	अणु0x06, 0x03पूर्ण,	/* VBAT	*/
	अणु0x06, 0x04पूर्ण,	/* VSEN12 */
	अणु0x06, 0x05पूर्ण,	/* VSEN13 */
	अणु0x06, 0x06पूर्ण,	/* VSEN14 */
	अणु0x06, 0x07पूर्ण,	/* VSEN15 */
	अणु0x06, 0x08पूर्ण,	/* VSEN16 */
	अणु0x06, 0x09पूर्ण,	/* VSEN17 */
पूर्ण;


#घोषणा W83795_REG_FAN(index)		(0x2E + (index))
#घोषणा W83795_REG_FAN_MIN_HL(index)	(0xB6 + (index))
#घोषणा W83795_REG_FAN_MIN_LSB(index)	(0xC4 + (index) / 2)
#घोषणा W83795_REG_FAN_MIN_LSB_SHIFT(index) \
	(((index) & 1) ? 4 : 0)

#घोषणा W83795_REG_VID_CTRL		0x6A

#घोषणा W83795_REG_ALARM_CTRL		0x40
#घोषणा ALARM_CTRL_RTSACS		(1 << 7)
#घोषणा W83795_REG_ALARM(index)		(0x41 + (index))
#घोषणा W83795_REG_CLR_CHASSIS		0x4D
#घोषणा W83795_REG_BEEP(index)		(0x50 + (index))

#घोषणा W83795_REG_OVT_CFG		0x58
#घोषणा OVT_CFG_SEL			(1 << 7)


#घोषणा W83795_REG_FCMS1		0x201
#घोषणा W83795_REG_FCMS2		0x208
#घोषणा W83795_REG_TFMR(index)		(0x202 + (index))
#घोषणा W83795_REG_FOMC			0x20F

#घोषणा W83795_REG_TSS(index)		(0x209 + (index))

#घोषणा TSS_MAP_RESERVED		0xff
अटल स्थिर u8 tss_map[4][6] = अणु
	अणु 0,  1,  2,  3,  4,  5पूर्ण,
	अणु 6,  7,  8,  9,  0,  1पूर्ण,
	अणु10, 11, 12, 13,  2,  3पूर्ण,
	अणु 4,  5,  4,  5, TSS_MAP_RESERVED, TSS_MAP_RESERVEDपूर्ण,
पूर्ण;

#घोषणा PWM_OUTPUT			0
#घोषणा PWM_FREQ			1
#घोषणा PWM_START			2
#घोषणा PWM_NONSTOP			3
#घोषणा PWM_STOP_TIME			4
#घोषणा W83795_REG_PWM(index, nr)	(0x210 + (nr) * 8 + (index))

#घोषणा W83795_REG_FTSH(index)		(0x240 + (index) * 2)
#घोषणा W83795_REG_FTSL(index)		(0x241 + (index) * 2)
#घोषणा W83795_REG_TFTS			0x250

#घोषणा TEMP_PWM_TTTI			0
#घोषणा TEMP_PWM_CTFS			1
#घोषणा TEMP_PWM_HCT			2
#घोषणा TEMP_PWM_HOT			3
#घोषणा W83795_REG_TTTI(index)		(0x260 + (index))
#घोषणा W83795_REG_CTFS(index)		(0x268 + (index))
#घोषणा W83795_REG_HT(index)		(0x270 + (index))

#घोषणा SF4_TEMP			0
#घोषणा SF4_PWM				1
#घोषणा W83795_REG_SF4_TEMP(temp_num, index) \
	(0x280 + 0x10 * (temp_num) + (index))
#घोषणा W83795_REG_SF4_PWM(temp_num, index) \
	(0x288 + 0x10 * (temp_num) + (index))

#घोषणा W83795_REG_DTSC			0x301
#घोषणा W83795_REG_DTSE			0x302
#घोषणा W83795_REG_DTS(index)		(0x26 + (index))
#घोषणा W83795_REG_PECI_TBASE(index)	(0x320 + (index))

#घोषणा DTS_CRIT			0
#घोषणा DTS_CRIT_HYST			1
#घोषणा DTS_WARN			2
#घोषणा DTS_WARN_HYST			3
#घोषणा W83795_REG_DTS_EXT(index)	(0xB2 + (index))

#घोषणा SETUP_PWM_DEFAULT		0
#घोषणा SETUP_PWM_UPTIME		1
#घोषणा SETUP_PWM_DOWNTIME		2
#घोषणा W83795_REG_SETUP_PWM(index)    (0x20C + (index))

अटल अंतरभूत u16 in_from_reg(u8 index, u16 val)
अणु
	/* 3VDD, 3VSB and VBAT: 6 mV/bit; other inमाला_दो: 2 mV/bit */
	अगर (index >= 12 && index <= 14)
		वापस val * 6;
	अन्यथा
		वापस val * 2;
पूर्ण

अटल अंतरभूत u16 in_to_reg(u8 index, u16 val)
अणु
	अगर (index >= 12 && index <= 14)
		वापस val / 6;
	अन्यथा
		वापस val / 2;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fan_from_reg(u16 val)
अणु
	अगर ((val == 0xfff) || (val == 0))
		वापस 0;
	वापस 1350000UL / val;
पूर्ण

अटल अंतरभूत u16 fan_to_reg(दीर्घ rpm)
अणु
	अगर (rpm <= 0)
		वापस 0x0fff;
	वापस clamp_val((1350000 + (rpm >> 1)) / rpm, 1, 0xffe);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ समय_from_reg(u8 reg)
अणु
	वापस reg * 100;
पूर्ण

अटल अंतरभूत u8 समय_प्रकारo_reg(अचिन्हित दीर्घ val)
अणु
	वापस clamp_val((val + 50) / 100, 0, 0xff);
पूर्ण

अटल अंतरभूत दीर्घ temp_from_reg(s8 reg)
अणु
	वापस reg * 1000;
पूर्ण

अटल अंतरभूत s8 temp_to_reg(दीर्घ val, s8 min, s8 max)
अणु
	वापस clamp_val(val / 1000, min, max);
पूर्ण

अटल स्थिर u16 pwm_freq_cksel0[16] = अणु
	1024, 512, 341, 256, 205, 171, 146, 128,
	85, 64, 32, 16, 8, 4, 2, 1
पूर्ण;

अटल अचिन्हित पूर्णांक pwm_freq_from_reg(u8 reg, u16 clkin)
अणु
	अचिन्हित दीर्घ base_घड़ी;

	अगर (reg & 0x80) अणु
		base_घड़ी = clkin * 1000 / ((clkin == 48000) ? 384 : 256);
		वापस base_घड़ी / ((reg & 0x7f) + 1);
	पूर्ण अन्यथा
		वापस pwm_freq_cksel0[reg & 0x0f];
पूर्ण

अटल u8 pwm_freq_to_reg(अचिन्हित दीर्घ val, u16 clkin)
अणु
	अचिन्हित दीर्घ base_घड़ी;
	u8 reg0, reg1;
	अचिन्हित दीर्घ best0, best1;

	/* Best fit क्रम cksel = 0 */
	reg0 = find_बंदst_descending(val, pwm_freq_cksel0,
				       ARRAY_SIZE(pwm_freq_cksel0));
	अगर (val < 375)	/* cksel = 1 can't beat this */
		वापस reg0;
	best0 = pwm_freq_cksel0[reg0];

	/* Best fit क्रम cksel = 1 */
	base_घड़ी = clkin * 1000 / ((clkin == 48000) ? 384 : 256);
	reg1 = clamp_val(DIV_ROUND_CLOSEST(base_घड़ी, val), 1, 128);
	best1 = base_घड़ी / reg1;
	reg1 = 0x80 | (reg1 - 1);

	/* Choose the बंदst one */
	अगर (असल(val - best0) > असल(val - best1))
		वापस reg1;
	अन्यथा
		वापस reg0;
पूर्ण

क्रमागत chip_types अणुw83795g, w83795adgपूर्ण;

काष्ठा w83795_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	क्रमागत chip_types chip_type;

	u8 bank;

	u32 has_in;		/* Enable monitor VIN or not */
	u8 has_dyn_in;		/* Only in2-0 can have this */
	u16 in[21][3];		/* Register value, पढ़ो/high/low */
	u8 in_lsb[10][3];	/* LSB Register value, high/low */
	u8 has_gain;		/* has gain: in17-20 * 8 */

	u16 has_fan;		/* Enable fan14-1 or not */
	u16 fan[14];		/* Register value combine */
	u16 fan_min[14];	/* Register value combine */

	u8 has_temp;		/* Enable monitor temp6-1 or not */
	s8 temp[6][5];		/* current, crit, crit_hyst, warn, warn_hyst */
	u8 temp_पढ़ो_vrlsb[6];
	u8 temp_mode;		/* Bit vector, 0 = TR, 1 = TD */
	u8 temp_src[3];		/* Register value */

	u8 enable_dts;		/*
				 * Enable PECI and SB-TSI,
				 * bit 0: =1 enable, =0 disable,
				 * bit 1: =1 AMD SB-TSI, =0 Intel PECI
				 */
	u8 has_dts;		/* Enable monitor DTS temp */
	s8 dts[8];		/* Register value */
	u8 dts_पढ़ो_vrlsb[8];	/* Register value */
	s8 dts_ext[4];		/* Register value */

	u8 has_pwm;		/*
				 * 795g supports 8 pwm, 795adg only supports 2,
				 * no config रेजिस्टर, only affected by chip
				 * type
				 */
	u8 pwm[8][5];		/*
				 * Register value, output, freq, start,
				 *  non stop, stop समय
				 */
	u16 clkin;		/* CLKIN frequency in kHz */
	u8 pwm_fcms[2];		/* Register value */
	u8 pwm_tfmr[6];		/* Register value */
	u8 pwm_fomc;		/* Register value */

	u16 target_speed[8];	/*
				 * Register value, target speed क्रम speed
				 * cruise
				 */
	u8 tol_speed;		/* tolerance of target speed */
	u8 pwm_temp[6][4];	/* TTTI, CTFS, HCT, HOT */
	u8 sf4_reg[6][2][7];	/* 6 temp, temp/dcpwm, 7 रेजिस्टरs */

	u8 setup_pwm[3];	/* Register value */

	u8 alarms[6];		/* Register value */
	u8 enable_beep;
	u8 beeps[6];		/* Register value */

	अक्षर valid;
	अक्षर valid_limits;
	अक्षर valid_pwm_config;
पूर्ण;

/*
 * Hardware access
 * We assume that nobकरोdy can change the bank outside the driver.
 */

/* Must be called with data->update_lock held, except during initialization */
अटल पूर्णांक w83795_set_bank(काष्ठा i2c_client *client, u8 bank)
अणु
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	पूर्णांक err;

	/* If the same bank is alपढ़ोy set, nothing to करो */
	अगर ((data->bank & 0x07) == bank)
		वापस 0;

	/* Change to new bank, preserve all other bits */
	bank |= data->bank & ~0x07;
	err = i2c_smbus_ग_लिखो_byte_data(client, W83795_REG_BANKSEL, bank);
	अगर (err < 0) अणु
		dev_err(&client->dev,
			"Failed to set bank to %d, err %d\n",
			(पूर्णांक)bank, err);
		वापस err;
	पूर्ण
	data->bank = bank;

	वापस 0;
पूर्ण

/* Must be called with data->update_lock held, except during initialization */
अटल u8 w83795_पढ़ो(काष्ठा i2c_client *client, u16 reg)
अणु
	पूर्णांक err;

	err = w83795_set_bank(client, reg >> 8);
	अगर (err < 0)
		वापस 0x00;	/* Arbitrary */

	err = i2c_smbus_पढ़ो_byte_data(client, reg & 0xff);
	अगर (err < 0) अणु
		dev_err(&client->dev,
			"Failed to read from register 0x%03x, err %d\n",
			(पूर्णांक)reg, err);
		वापस 0x00;	/* Arbitrary */
	पूर्ण
	वापस err;
पूर्ण

/* Must be called with data->update_lock held, except during initialization */
अटल पूर्णांक w83795_ग_लिखो(काष्ठा i2c_client *client, u16 reg, u8 value)
अणु
	पूर्णांक err;

	err = w83795_set_bank(client, reg >> 8);
	अगर (err < 0)
		वापस err;

	err = i2c_smbus_ग_लिखो_byte_data(client, reg & 0xff, value);
	अगर (err < 0)
		dev_err(&client->dev,
			"Failed to write to register 0x%03x, err %d\n",
			(पूर्णांक)reg, err);
	वापस err;
पूर्ण

अटल व्योम w83795_update_limits(काष्ठा i2c_client *client)
अणु
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	पूर्णांक i, limit;
	u8 lsb;

	/* Read the voltage limits */
	क्रम (i = 0; i < ARRAY_SIZE(data->in); i++) अणु
		अगर (!(data->has_in & (1 << i)))
			जारी;
		data->in[i][IN_MAX] =
			w83795_पढ़ो(client, W83795_REG_IN[i][IN_MAX]);
		data->in[i][IN_LOW] =
			w83795_पढ़ो(client, W83795_REG_IN[i][IN_LOW]);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(data->in_lsb); i++) अणु
		अगर ((i == 2 && data->chip_type == w83795adg) ||
		    (i >= 4 && !(data->has_in & (1 << (i + 11)))))
			जारी;
		data->in_lsb[i][IN_MAX] =
			w83795_पढ़ो(client, IN_LSB_REG(i, IN_MAX));
		data->in_lsb[i][IN_LOW] =
			w83795_पढ़ो(client, IN_LSB_REG(i, IN_LOW));
	पूर्ण

	/* Read the fan limits */
	lsb = 0; /* Silent false gcc warning */
	क्रम (i = 0; i < ARRAY_SIZE(data->fan); i++) अणु
		/*
		 * Each रेजिस्टर contains LSB क्रम 2 fans, but we want to
		 * पढ़ो it only once to save समय
		 */
		अगर ((i & 1) == 0 && (data->has_fan & (3 << i)))
			lsb = w83795_पढ़ो(client, W83795_REG_FAN_MIN_LSB(i));

		अगर (!(data->has_fan & (1 << i)))
			जारी;
		data->fan_min[i] =
			w83795_पढ़ो(client, W83795_REG_FAN_MIN_HL(i)) << 4;
		data->fan_min[i] |=
			(lsb >> W83795_REG_FAN_MIN_LSB_SHIFT(i)) & 0x0F;
	पूर्ण

	/* Read the temperature limits */
	क्रम (i = 0; i < ARRAY_SIZE(data->temp); i++) अणु
		अगर (!(data->has_temp & (1 << i)))
			जारी;
		क्रम (limit = TEMP_CRIT; limit <= TEMP_WARN_HYST; limit++)
			data->temp[i][limit] =
				w83795_पढ़ो(client, W83795_REG_TEMP[i][limit]);
	पूर्ण

	/* Read the DTS limits */
	अगर (data->enable_dts) अणु
		क्रम (limit = DTS_CRIT; limit <= DTS_WARN_HYST; limit++)
			data->dts_ext[limit] =
				w83795_पढ़ो(client, W83795_REG_DTS_EXT(limit));
	पूर्ण

	/* Read beep settings */
	अगर (data->enable_beep) अणु
		क्रम (i = 0; i < ARRAY_SIZE(data->beeps); i++)
			data->beeps[i] =
				w83795_पढ़ो(client, W83795_REG_BEEP(i));
	पूर्ण

	data->valid_limits = 1;
पूर्ण

अटल काष्ठा w83795_data *w83795_update_pwm_config(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	पूर्णांक i, पंचांगp;

	mutex_lock(&data->update_lock);

	अगर (data->valid_pwm_config)
		जाओ END;

	/* Read temperature source selection */
	क्रम (i = 0; i < ARRAY_SIZE(data->temp_src); i++)
		data->temp_src[i] = w83795_पढ़ो(client, W83795_REG_TSS(i));

	/* Read स्वतःmatic fan speed control settings */
	data->pwm_fcms[0] = w83795_पढ़ो(client, W83795_REG_FCMS1);
	data->pwm_fcms[1] = w83795_पढ़ो(client, W83795_REG_FCMS2);
	क्रम (i = 0; i < ARRAY_SIZE(data->pwm_tfmr); i++)
		data->pwm_tfmr[i] = w83795_पढ़ो(client, W83795_REG_TFMR(i));
	data->pwm_fomc = w83795_पढ़ो(client, W83795_REG_FOMC);
	क्रम (i = 0; i < data->has_pwm; i++) अणु
		क्रम (पंचांगp = PWM_FREQ; पंचांगp <= PWM_STOP_TIME; पंचांगp++)
			data->pwm[i][पंचांगp] =
				w83795_पढ़ो(client, W83795_REG_PWM(i, पंचांगp));
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(data->target_speed); i++) अणु
		data->target_speed[i] =
			w83795_पढ़ो(client, W83795_REG_FTSH(i)) << 4;
		data->target_speed[i] |=
			w83795_पढ़ो(client, W83795_REG_FTSL(i)) >> 4;
	पूर्ण
	data->tol_speed = w83795_पढ़ो(client, W83795_REG_TFTS) & 0x3f;

	क्रम (i = 0; i < ARRAY_SIZE(data->pwm_temp); i++) अणु
		data->pwm_temp[i][TEMP_PWM_TTTI] =
			w83795_पढ़ो(client, W83795_REG_TTTI(i)) & 0x7f;
		data->pwm_temp[i][TEMP_PWM_CTFS] =
			w83795_पढ़ो(client, W83795_REG_CTFS(i));
		पंचांगp = w83795_पढ़ो(client, W83795_REG_HT(i));
		data->pwm_temp[i][TEMP_PWM_HCT] = पंचांगp >> 4;
		data->pwm_temp[i][TEMP_PWM_HOT] = पंचांगp & 0x0f;
	पूर्ण

	/* Read SmartFanIV trip poपूर्णांकs */
	क्रम (i = 0; i < ARRAY_SIZE(data->sf4_reg); i++) अणु
		क्रम (पंचांगp = 0; पंचांगp < 7; पंचांगp++) अणु
			data->sf4_reg[i][SF4_TEMP][पंचांगp] =
				w83795_पढ़ो(client,
					    W83795_REG_SF4_TEMP(i, पंचांगp));
			data->sf4_reg[i][SF4_PWM][पंचांगp] =
				w83795_पढ़ो(client, W83795_REG_SF4_PWM(i, पंचांगp));
		पूर्ण
	पूर्ण

	/* Read setup PWM */
	क्रम (i = 0; i < ARRAY_SIZE(data->setup_pwm); i++)
		data->setup_pwm[i] =
			w83795_पढ़ो(client, W83795_REG_SETUP_PWM(i));

	data->valid_pwm_config = 1;

END:
	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

अटल काष्ठा w83795_data *w83795_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	u16 पंचांगp;
	u8 पूर्णांकrusion;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (!data->valid_limits)
		w83795_update_limits(client);

	अगर (!(समय_after(jअगरfies, data->last_updated + HZ * 2)
	      || !data->valid))
		जाओ END;

	/* Update the voltages value */
	क्रम (i = 0; i < ARRAY_SIZE(data->in); i++) अणु
		अगर (!(data->has_in & (1 << i)))
			जारी;
		पंचांगp = w83795_पढ़ो(client, W83795_REG_IN[i][IN_READ]) << 2;
		पंचांगp |= w83795_पढ़ो(client, W83795_REG_VRLSB) >> 6;
		data->in[i][IN_READ] = पंचांगp;
	पूर्ण

	/* in0-2 can have dynamic limits (W83795G only) */
	अगर (data->has_dyn_in) अणु
		u8 lsb_max = w83795_पढ़ो(client, IN_LSB_REG(0, IN_MAX));
		u8 lsb_low = w83795_पढ़ो(client, IN_LSB_REG(0, IN_LOW));

		क्रम (i = 0; i < 3; i++) अणु
			अगर (!(data->has_dyn_in & (1 << i)))
				जारी;
			data->in[i][IN_MAX] =
				w83795_पढ़ो(client, W83795_REG_IN[i][IN_MAX]);
			data->in[i][IN_LOW] =
				w83795_पढ़ो(client, W83795_REG_IN[i][IN_LOW]);
			data->in_lsb[i][IN_MAX] = (lsb_max >> (2 * i)) & 0x03;
			data->in_lsb[i][IN_LOW] = (lsb_low >> (2 * i)) & 0x03;
		पूर्ण
	पूर्ण

	/* Update fan */
	क्रम (i = 0; i < ARRAY_SIZE(data->fan); i++) अणु
		अगर (!(data->has_fan & (1 << i)))
			जारी;
		data->fan[i] = w83795_पढ़ो(client, W83795_REG_FAN(i)) << 4;
		data->fan[i] |= w83795_पढ़ो(client, W83795_REG_VRLSB) >> 4;
	पूर्ण

	/* Update temperature */
	क्रम (i = 0; i < ARRAY_SIZE(data->temp); i++) अणु
		data->temp[i][TEMP_READ] =
			w83795_पढ़ो(client, W83795_REG_TEMP[i][TEMP_READ]);
		data->temp_पढ़ो_vrlsb[i] =
			w83795_पढ़ो(client, W83795_REG_VRLSB);
	पूर्ण

	/* Update dts temperature */
	अगर (data->enable_dts) अणु
		क्रम (i = 0; i < ARRAY_SIZE(data->dts); i++) अणु
			अगर (!(data->has_dts & (1 << i)))
				जारी;
			data->dts[i] =
				w83795_पढ़ो(client, W83795_REG_DTS(i));
			data->dts_पढ़ो_vrlsb[i] =
				w83795_पढ़ो(client, W83795_REG_VRLSB);
		पूर्ण
	पूर्ण

	/* Update pwm output */
	क्रम (i = 0; i < data->has_pwm; i++) अणु
		data->pwm[i][PWM_OUTPUT] =
		    w83795_पढ़ो(client, W83795_REG_PWM(i, PWM_OUTPUT));
	पूर्ण

	/*
	 * Update पूर्णांकrusion and alarms
	 * It is important to पढ़ो पूर्णांकrusion first, because पढ़ोing from
	 * रेजिस्टर SMI STS6 clears the पूर्णांकerrupt status temporarily.
	 */
	पंचांगp = w83795_पढ़ो(client, W83795_REG_ALARM_CTRL);
	/* Switch to पूर्णांकerrupt status क्रम पूर्णांकrusion अगर needed */
	अगर (पंचांगp & ALARM_CTRL_RTSACS)
		w83795_ग_लिखो(client, W83795_REG_ALARM_CTRL,
			     पंचांगp & ~ALARM_CTRL_RTSACS);
	पूर्णांकrusion = w83795_पढ़ो(client, W83795_REG_ALARM(5)) & (1 << 6);
	/* Switch to real-समय alarms */
	w83795_ग_लिखो(client, W83795_REG_ALARM_CTRL, पंचांगp | ALARM_CTRL_RTSACS);
	क्रम (i = 0; i < ARRAY_SIZE(data->alarms); i++)
		data->alarms[i] = w83795_पढ़ो(client, W83795_REG_ALARM(i));
	data->alarms[5] |= पूर्णांकrusion;
	/* Restore original configuration अगर needed */
	अगर (!(पंचांगp & ALARM_CTRL_RTSACS))
		w83795_ग_लिखो(client, W83795_REG_ALARM_CTRL,
			     पंचांगp & ~ALARM_CTRL_RTSACS);

	data->last_updated = jअगरfies;
	data->valid = 1;

END:
	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

/*
 * Sysfs attributes
 */

#घोषणा ALARM_STATUS      0
#घोषणा BEEP_ENABLE       1
अटल sमाप_प्रकार
show_alarm_beep(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = w83795_update_device(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index >> 3;
	पूर्णांक bit = sensor_attr->index & 0x07;
	u8 val;

	अगर (nr == ALARM_STATUS)
		val = (data->alarms[index] >> bit) & 1;
	अन्यथा		/* BEEP_ENABLE */
		val = (data->beeps[index] >> bit) & 1;

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार
store_beep(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index >> 3;
	पूर्णांक shअगरt = sensor_attr->index & 0x07;
	u8 beep_bit = 1 << shअगरt;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;
	अगर (val != 0 && val != 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->beeps[index] = w83795_पढ़ो(client, W83795_REG_BEEP(index));
	data->beeps[index] &= ~beep_bit;
	data->beeps[index] |= val << shअगरt;
	w83795_ग_लिखो(client, W83795_REG_BEEP(index), data->beeps[index]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

/* Write 0 to clear chassis alarm */
अटल sमाप_प्रकार
store_chassis_clear(काष्ठा device *dev,
		    काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
		    माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0 || val != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	val = w83795_पढ़ो(client, W83795_REG_CLR_CHASSIS);
	val |= 0x80;
	w83795_ग_लिखो(client, W83795_REG_CLR_CHASSIS, val);

	/* Clear status and क्रमce cache refresh */
	w83795_पढ़ो(client, W83795_REG_ALARM(5));
	data->valid = 0;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

#घोषणा FAN_INPUT     0
#घोषणा FAN_MIN       1
अटल sमाप_प्रकार
show_fan(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83795_data *data = w83795_update_device(dev);
	u16 val;

	अगर (nr == FAN_INPUT)
		val = data->fan[index] & 0x0fff;
	अन्यथा
		val = data->fan_min[index] & 0x0fff;

	वापस प्र_लिखो(buf, "%lu\n", fan_from_reg(val));
पूर्ण

अटल sमाप_प्रकार
store_fan_min(काष्ठा device *dev, काष्ठा device_attribute *attr,
	      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;
	val = fan_to_reg(val);

	mutex_lock(&data->update_lock);
	data->fan_min[index] = val;
	w83795_ग_लिखो(client, W83795_REG_FAN_MIN_HL(index), (val >> 4) & 0xff);
	val &= 0x0f;
	अगर (index & 1) अणु
		val <<= 4;
		val |= w83795_पढ़ो(client, W83795_REG_FAN_MIN_LSB(index))
		       & 0x0f;
	पूर्ण अन्यथा अणु
		val |= w83795_पढ़ो(client, W83795_REG_FAN_MIN_LSB(index))
		       & 0xf0;
	पूर्ण
	w83795_ग_लिखो(client, W83795_REG_FAN_MIN_LSB(index), val & 0xff);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data;
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित पूर्णांक val;

	data = nr == PWM_OUTPUT ? w83795_update_device(dev)
				: w83795_update_pwm_config(dev);

	चयन (nr) अणु
	हाल PWM_STOP_TIME:
		val = समय_from_reg(data->pwm[index][nr]);
		अवरोध;
	हाल PWM_FREQ:
		val = pwm_freq_from_reg(data->pwm[index][nr], data->clkin);
		अवरोध;
	शेष:
		val = data->pwm[index][nr];
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार
store_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	चयन (nr) अणु
	हाल PWM_STOP_TIME:
		val = समय_प्रकारo_reg(val);
		अवरोध;
	हाल PWM_FREQ:
		val = pwm_freq_to_reg(val, data->clkin);
		अवरोध;
	शेष:
		val = clamp_val(val, 0, 0xff);
		अवरोध;
	पूर्ण
	w83795_ग_लिखो(client, W83795_REG_PWM(index, nr), val);
	data->pwm[index][nr] = val;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	पूर्णांक index = sensor_attr->index;
	u8 पंचांगp;

	/* Speed cruise mode */
	अगर (data->pwm_fcms[0] & (1 << index)) अणु
		पंचांगp = 2;
		जाओ out;
	पूर्ण
	/* Thermal cruise or SmartFan IV mode */
	क्रम (पंचांगp = 0; पंचांगp < 6; पंचांगp++) अणु
		अगर (data->pwm_tfmr[पंचांगp] & (1 << index)) अणु
			पंचांगp = 3;
			जाओ out;
		पूर्ण
	पूर्ण
	/* Manual mode */
	पंचांगp = 1;

out:
	वापस प्र_लिखो(buf, "%u\n", पंचांगp);
पूर्ण

अटल sमाप_प्रकार
store_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;
	पूर्णांक i;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;
	अगर (val < 1 || val > 2)
		वापस -EINVAL;

#अगर_अघोषित CONFIG_SENSORS_W83795_FANCTRL
	अगर (val > 1) अणु
		dev_warn(dev, "Automatic fan speed control support disabled\n");
		dev_warn(dev, "Build with CONFIG_SENSORS_W83795_FANCTRL=y if you want it\n");
		वापस -EOPNOTSUPP;
	पूर्ण
#पूर्ण_अगर

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल 1:
		/* Clear speed cruise mode bits */
		data->pwm_fcms[0] &= ~(1 << index);
		w83795_ग_लिखो(client, W83795_REG_FCMS1, data->pwm_fcms[0]);
		/* Clear thermal cruise mode bits */
		क्रम (i = 0; i < 6; i++) अणु
			data->pwm_tfmr[i] &= ~(1 << index);
			w83795_ग_लिखो(client, W83795_REG_TFMR(i),
				data->pwm_tfmr[i]);
		पूर्ण
		अवरोध;
	हाल 2:
		data->pwm_fcms[0] |= (1 << index);
		w83795_ग_लिखो(client, W83795_REG_FCMS1, data->pwm_fcms[0]);
		अवरोध;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_pwm_mode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	पूर्णांक index = to_sensor_dev_attr_2(attr)->index;
	अचिन्हित पूर्णांक mode;

	अगर (data->pwm_fomc & (1 << index))
		mode = 0;	/* DC */
	अन्यथा
		mode = 1;	/* PWM */

	वापस प्र_लिखो(buf, "%u\n", mode);
पूर्ण

/*
 * Check whether a given temperature source can ever be useful.
 * Returns the number of selectable temperature channels which are
 * enabled.
 */
अटल पूर्णांक w83795_tss_useful(स्थिर काष्ठा w83795_data *data, पूर्णांक tsrc)
अणु
	पूर्णांक useful = 0, i;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (tss_map[i][tsrc] == TSS_MAP_RESERVED)
			जारी;
		अगर (tss_map[i][tsrc] < 6)	/* Analog */
			useful += (data->has_temp >> tss_map[i][tsrc]) & 1;
		अन्यथा				/* Digital */
			useful += (data->has_dts >> (tss_map[i][tsrc] - 6)) & 1;
	पूर्ण

	वापस useful;
पूर्ण

अटल sमाप_प्रकार
show_temp_src(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	पूर्णांक index = sensor_attr->index;
	u8 पंचांगp = data->temp_src[index / 2];

	अगर (index & 1)
		पंचांगp >>= 4;	/* Pick high nibble */
	अन्यथा
		पंचांगp &= 0x0f;	/* Pick low nibble */

	/* Look-up the actual temperature channel number */
	अगर (पंचांगp >= 4 || tss_map[पंचांगp][index] == TSS_MAP_RESERVED)
		वापस -EINVAL;		/* Shouldn't happen */

	वापस प्र_लिखो(buf, "%u\n", (अचिन्हित पूर्णांक)tss_map[पंचांगp][index] + 1);
पूर्ण

अटल sमाप_प्रकार
store_temp_src(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	पूर्णांक पंचांगp;
	अचिन्हित दीर्घ channel;
	u8 val = index / 2;

	अगर (kम_से_अदीर्घ(buf, 10, &channel) < 0 ||
	    channel < 1 || channel > 14)
		वापस -EINVAL;

	/* Check अगर request can be fulfilled */
	क्रम (पंचांगp = 0; पंचांगp < 4; पंचांगp++) अणु
		अगर (tss_map[पंचांगp][index] == channel - 1)
			अवरोध;
	पूर्ण
	अगर (पंचांगp == 4)	/* No match */
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (index & 1) अणु
		पंचांगp <<= 4;
		data->temp_src[val] &= 0x0f;
	पूर्ण अन्यथा अणु
		data->temp_src[val] &= 0xf0;
	पूर्ण
	data->temp_src[val] |= पंचांगp;
	w83795_ग_लिखो(client, W83795_REG_TSS(val), data->temp_src[val]);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

#घोषणा TEMP_PWM_ENABLE   0
#घोषणा TEMP_PWM_FAN_MAP  1
अटल sमाप_प्रकार
show_temp_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	u8 पंचांगp = 0xff;

	चयन (nr) अणु
	हाल TEMP_PWM_ENABLE:
		पंचांगp = (data->pwm_fcms[1] >> index) & 1;
		अगर (पंचांगp)
			पंचांगp = 4;
		अन्यथा
			पंचांगp = 3;
		अवरोध;
	हाल TEMP_PWM_FAN_MAP:
		पंचांगp = data->pwm_tfmr[index];
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", पंचांगp);
पूर्ण

अटल sमाप_प्रकार
store_temp_pwm_enable(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ पंचांगp;

	अगर (kम_से_अदीर्घ(buf, 10, &पंचांगp) < 0)
		वापस -EINVAL;

	चयन (nr) अणु
	हाल TEMP_PWM_ENABLE:
		अगर (पंचांगp != 3 && पंचांगp != 4)
			वापस -EINVAL;
		पंचांगp -= 3;
		mutex_lock(&data->update_lock);
		data->pwm_fcms[1] &= ~(1 << index);
		data->pwm_fcms[1] |= पंचांगp << index;
		w83795_ग_लिखो(client, W83795_REG_FCMS2, data->pwm_fcms[1]);
		mutex_unlock(&data->update_lock);
		अवरोध;
	हाल TEMP_PWM_FAN_MAP:
		mutex_lock(&data->update_lock);
		पंचांगp = clamp_val(पंचांगp, 0, 0xff);
		w83795_ग_लिखो(client, W83795_REG_TFMR(index), पंचांगp);
		data->pwm_tfmr[index] = पंचांगp;
		mutex_unlock(&data->update_lock);
		अवरोध;
	पूर्ण
	वापस count;
पूर्ण

#घोषणा FANIN_TARGET   0
#घोषणा FANIN_TOL      1
अटल sमाप_प्रकार
show_fanin(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	u16 पंचांगp = 0;

	चयन (nr) अणु
	हाल FANIN_TARGET:
		पंचांगp = fan_from_reg(data->target_speed[index]);
		अवरोध;
	हाल FANIN_TOL:
		पंचांगp = data->tol_speed;
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", पंचांगp);
पूर्ण

अटल sमाप_प्रकार
store_fanin(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	चयन (nr) अणु
	हाल FANIN_TARGET:
		val = fan_to_reg(clamp_val(val, 0, 0xfff));
		w83795_ग_लिखो(client, W83795_REG_FTSH(index), val >> 4);
		w83795_ग_लिखो(client, W83795_REG_FTSL(index), (val << 4) & 0xf0);
		data->target_speed[index] = val;
		अवरोध;
	हाल FANIN_TOL:
		val = clamp_val(val, 0, 0x3f);
		w83795_ग_लिखो(client, W83795_REG_TFTS, val);
		data->tol_speed = val;
		अवरोध;
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण


अटल sमाप_प्रकार
show_temp_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	दीर्घ पंचांगp = temp_from_reg(data->pwm_temp[index][nr]);

	वापस प्र_लिखो(buf, "%ld\n", पंचांगp);
पूर्ण

अटल sमाप_प्रकार
store_temp_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;
	u8 पंचांगp;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;
	val /= 1000;

	mutex_lock(&data->update_lock);
	चयन (nr) अणु
	हाल TEMP_PWM_TTTI:
		val = clamp_val(val, 0, 0x7f);
		w83795_ग_लिखो(client, W83795_REG_TTTI(index), val);
		अवरोध;
	हाल TEMP_PWM_CTFS:
		val = clamp_val(val, 0, 0x7f);
		w83795_ग_लिखो(client, W83795_REG_CTFS(index), val);
		अवरोध;
	हाल TEMP_PWM_HCT:
		val = clamp_val(val, 0, 0x0f);
		पंचांगp = w83795_पढ़ो(client, W83795_REG_HT(index));
		पंचांगp &= 0x0f;
		पंचांगp |= (val << 4) & 0xf0;
		w83795_ग_लिखो(client, W83795_REG_HT(index), पंचांगp);
		अवरोध;
	हाल TEMP_PWM_HOT:
		val = clamp_val(val, 0, 0x0f);
		पंचांगp = w83795_पढ़ो(client, W83795_REG_HT(index));
		पंचांगp &= 0xf0;
		पंचांगp |= val & 0x0f;
		w83795_ग_लिखो(client, W83795_REG_HT(index), पंचांगp);
		अवरोध;
	पूर्ण
	data->pwm_temp[index][nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_sf4_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;

	वापस प्र_लिखो(buf, "%u\n", data->sf4_reg[index][SF4_PWM][nr]);
पूर्ण

अटल sमाप_प्रकार
store_sf4_pwm(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	w83795_ग_लिखो(client, W83795_REG_SF4_PWM(index, nr), val);
	data->sf4_reg[index][SF4_PWM][nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
show_sf4_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;

	वापस प्र_लिखो(buf, "%u\n",
		(data->sf4_reg[index][SF4_TEMP][nr]) * 1000);
पूर्ण

अटल sमाप_प्रकार
store_sf4_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
	  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;
	val /= 1000;

	mutex_lock(&data->update_lock);
	w83795_ग_लिखो(client, W83795_REG_SF4_TEMP(index, nr), val);
	data->sf4_reg[index][SF4_TEMP][nr] = val;
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण


अटल sमाप_प्रकार
show_temp(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83795_data *data = w83795_update_device(dev);
	दीर्घ temp = temp_from_reg(data->temp[index][nr]);

	अगर (nr == TEMP_READ)
		temp += (data->temp_पढ़ो_vrlsb[index] >> 6) * 250;
	वापस प्र_लिखो(buf, "%ld\n", temp);
पूर्ण

अटल sमाप_प्रकार
store_temp(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	दीर्घ पंचांगp;

	अगर (kम_से_दीर्घ(buf, 10, &पंचांगp) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->temp[index][nr] = temp_to_reg(पंचांगp, -128, 127);
	w83795_ग_लिखो(client, W83795_REG_TEMP[index][nr], data->temp[index][nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण


अटल sमाप_प्रकार
show_dts_mode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = dev_get_drvdata(dev);
	पूर्णांक पंचांगp;

	अगर (data->enable_dts & 2)
		पंचांगp = 5;
	अन्यथा
		पंचांगp = 6;

	वापस प्र_लिखो(buf, "%d\n", पंचांगp);
पूर्ण

अटल sमाप_प्रकार
show_dts(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83795_data *data = w83795_update_device(dev);
	दीर्घ temp = temp_from_reg(data->dts[index]);

	temp += (data->dts_पढ़ो_vrlsb[index] >> 6) * 250;
	वापस प्र_लिखो(buf, "%ld\n", temp);
पूर्ण

अटल sमाप_प्रकार
show_dts_ext(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	काष्ठा w83795_data *data = dev_get_drvdata(dev);
	दीर्घ temp = temp_from_reg(data->dts_ext[nr]);

	वापस प्र_लिखो(buf, "%ld\n", temp);
पूर्ण

अटल sमाप_प्रकार
store_dts_ext(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	दीर्घ पंचांगp;

	अगर (kम_से_दीर्घ(buf, 10, &पंचांगp) < 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->dts_ext[nr] = temp_to_reg(पंचांगp, -128, 127);
	w83795_ग_लिखो(client, W83795_REG_DTS_EXT(nr), data->dts_ext[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण


अटल sमाप_प्रकार
show_temp_mode(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w83795_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	पूर्णांक पंचांगp;

	अगर (data->temp_mode & (1 << index))
		पंचांगp = 3;	/* Thermal diode */
	अन्यथा
		पंचांगp = 4;	/* Thermistor */

	वापस प्र_लिखो(buf, "%d\n", पंचांगp);
पूर्ण

/* Only क्रम temp1-4 (temp5-6 can only be thermistor) */
अटल sमाप_प्रकार
store_temp_mode(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक index = sensor_attr->index;
	पूर्णांक reg_shअगरt;
	अचिन्हित दीर्घ val;
	u8 पंचांगp;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;
	अगर ((val != 4) && (val != 3))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	अगर (val == 3) अणु
		/* Thermal diode */
		val = 0x01;
		data->temp_mode |= 1 << index;
	पूर्ण अन्यथा अगर (val == 4) अणु
		/* Thermistor */
		val = 0x03;
		data->temp_mode &= ~(1 << index);
	पूर्ण

	reg_shअगरt = 2 * index;
	पंचांगp = w83795_पढ़ो(client, W83795_REG_TEMP_CTRL2);
	पंचांगp &= ~(0x03 << reg_shअगरt);
	पंचांगp |= val << reg_shअगरt;
	w83795_ग_लिखो(client, W83795_REG_TEMP_CTRL2, पंचांगp);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण


/* show/store VIN */
अटल sमाप_प्रकार
show_in(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा w83795_data *data = w83795_update_device(dev);
	u16 val = data->in[index][nr];
	u8 lsb_idx;

	चयन (nr) अणु
	हाल IN_READ:
		/* calculate this value again by sensors as sensors3.conf */
		अगर ((index >= 17) &&
		    !((data->has_gain >> (index - 17)) & 1))
			val *= 8;
		अवरोध;
	हाल IN_MAX:
	हाल IN_LOW:
		lsb_idx = IN_LSB_SHIFT_IDX[index][IN_LSB_IDX];
		val <<= 2;
		val |= (data->in_lsb[lsb_idx][nr] >>
			IN_LSB_SHIFT_IDX[index][IN_LSB_SHIFT]) & 0x03;
		अगर ((index >= 17) &&
		    !((data->has_gain >> (index - 17)) & 1))
			val *= 8;
		अवरोध;
	पूर्ण
	val = in_from_reg(index, val);

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार
store_in(काष्ठा device *dev, काष्ठा device_attribute *attr,
	 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	पूर्णांक index = sensor_attr->index;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	u8 पंचांगp;
	u8 lsb_idx;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;
	val = in_to_reg(index, val);

	अगर ((index >= 17) &&
	    !((data->has_gain >> (index - 17)) & 1))
		val /= 8;
	val = clamp_val(val, 0, 0x3FF);
	mutex_lock(&data->update_lock);

	lsb_idx = IN_LSB_SHIFT_IDX[index][IN_LSB_IDX];
	पंचांगp = w83795_पढ़ो(client, IN_LSB_REG(lsb_idx, nr));
	पंचांगp &= ~(0x03 << IN_LSB_SHIFT_IDX[index][IN_LSB_SHIFT]);
	पंचांगp |= (val & 0x03) << IN_LSB_SHIFT_IDX[index][IN_LSB_SHIFT];
	w83795_ग_लिखो(client, IN_LSB_REG(lsb_idx, nr), पंचांगp);
	data->in_lsb[lsb_idx][nr] = पंचांगp;

	पंचांगp = (val >> 2) & 0xff;
	w83795_ग_लिखो(client, W83795_REG_IN[index][nr], पंचांगp);
	data->in[index][nr] = पंचांगp;

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण


#अगर_घोषित CONFIG_SENSORS_W83795_FANCTRL
अटल sमाप_प्रकार
show_sf_setup(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	काष्ठा w83795_data *data = w83795_update_pwm_config(dev);
	u16 val = data->setup_pwm[nr];

	चयन (nr) अणु
	हाल SETUP_PWM_UPTIME:
	हाल SETUP_PWM_DOWNTIME:
		val = समय_from_reg(val);
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार
store_sf_setup(काष्ठा device *dev, काष्ठा device_attribute *attr,
	 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sensor_attr =
	    to_sensor_dev_attr_2(attr);
	पूर्णांक nr = sensor_attr->nr;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val) < 0)
		वापस -EINVAL;

	चयन (nr) अणु
	हाल SETUP_PWM_DEFAULT:
		val = clamp_val(val, 0, 0xff);
		अवरोध;
	हाल SETUP_PWM_UPTIME:
	हाल SETUP_PWM_DOWNTIME:
		val = समय_प्रकारo_reg(val);
		अगर (val == 0)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	mutex_lock(&data->update_lock);
	data->setup_pwm[nr] = val;
	w83795_ग_लिखो(client, W83795_REG_SETUP_PWM(nr), val);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण
#पूर्ण_अगर


#घोषणा NOT_USED			-1

/*
 * Don't change the attribute order, _max, _min and _beep are accessed by index
 * somewhere अन्यथा in the code
 */
#घोषणा SENSOR_ATTR_IN(index) अणु						\
	SENSOR_ATTR_2(in##index##_input, S_IRUGO, show_in, शून्य,	\
		IN_READ, index), \
	SENSOR_ATTR_2(in##index##_max, S_IRUGO | S_IWUSR, show_in,	\
		store_in, IN_MAX, index),				\
	SENSOR_ATTR_2(in##index##_min, S_IRUGO | S_IWUSR, show_in,	\
		store_in, IN_LOW, index),				\
	SENSOR_ATTR_2(in##index##_alarm, S_IRUGO, show_alarm_beep,	\
		शून्य, ALARM_STATUS, index + ((index > 14) ? 1 : 0)), \
	SENSOR_ATTR_2(in##index##_beep, S_IWUSR | S_IRUGO,		\
		show_alarm_beep, store_beep, BEEP_ENABLE,		\
		index + ((index > 14) ? 1 : 0)) पूर्ण

/*
 * Don't change the attribute order, _beep is accessed by index
 * somewhere अन्यथा in the code
 */
#घोषणा SENSOR_ATTR_FAN(index) अणु					\
	SENSOR_ATTR_2(fan##index##_input, S_IRUGO, show_fan,		\
		शून्य, FAN_INPUT, index - 1), \
	SENSOR_ATTR_2(fan##index##_min, S_IWUSR | S_IRUGO,		\
		show_fan, store_fan_min, FAN_MIN, index - 1),	\
	SENSOR_ATTR_2(fan##index##_alarm, S_IRUGO, show_alarm_beep,	\
		शून्य, ALARM_STATUS, index + 31),			\
	SENSOR_ATTR_2(fan##index##_beep, S_IWUSR | S_IRUGO,		\
		show_alarm_beep, store_beep, BEEP_ENABLE, index + 31) पूर्ण

#घोषणा SENSOR_ATTR_PWM(index) अणु					\
	SENSOR_ATTR_2(pwm##index, S_IWUSR | S_IRUGO, show_pwm,		\
		store_pwm, PWM_OUTPUT, index - 1),			\
	SENSOR_ATTR_2(pwm##index##_enable, S_IWUSR | S_IRUGO,		\
		show_pwm_enable, store_pwm_enable, NOT_USED, index - 1), \
	SENSOR_ATTR_2(pwm##index##_mode, S_IRUGO,			\
		show_pwm_mode, शून्य, NOT_USED, index - 1),		\
	SENSOR_ATTR_2(pwm##index##_freq, S_IWUSR | S_IRUGO,		\
		show_pwm, store_pwm, PWM_FREQ, index - 1),		\
	SENSOR_ATTR_2(pwm##index##_nonstop, S_IWUSR | S_IRUGO,		\
		show_pwm, store_pwm, PWM_NONSTOP, index - 1),		\
	SENSOR_ATTR_2(pwm##index##_start, S_IWUSR | S_IRUGO,		\
		show_pwm, store_pwm, PWM_START, index - 1),		\
	SENSOR_ATTR_2(pwm##index##_stop_समय, S_IWUSR | S_IRUGO,	\
		show_pwm, store_pwm, PWM_STOP_TIME, index - 1),	 \
	SENSOR_ATTR_2(fan##index##_target, S_IWUSR | S_IRUGO, \
		show_fanin, store_fanin, FANIN_TARGET, index - 1) पूर्ण

/*
 * Don't change the attribute order, _beep is accessed by index
 * somewhere अन्यथा in the code
 */
#घोषणा SENSOR_ATTR_DTS(index) अणु					\
	SENSOR_ATTR_2(temp##index##_type, S_IRUGO ,		\
		show_dts_mode, शून्य, NOT_USED, index - 7),	\
	SENSOR_ATTR_2(temp##index##_input, S_IRUGO, show_dts,		\
		शून्य, NOT_USED, index - 7),				\
	SENSOR_ATTR_2(temp##index##_crit, S_IRUGO | S_IWUSR, show_dts_ext, \
		store_dts_ext, DTS_CRIT, NOT_USED),			\
	SENSOR_ATTR_2(temp##index##_crit_hyst, S_IRUGO | S_IWUSR,	\
		show_dts_ext, store_dts_ext, DTS_CRIT_HYST, NOT_USED),	\
	SENSOR_ATTR_2(temp##index##_max, S_IRUGO | S_IWUSR, show_dts_ext, \
		store_dts_ext, DTS_WARN, NOT_USED),			\
	SENSOR_ATTR_2(temp##index##_max_hyst, S_IRUGO | S_IWUSR,	\
		show_dts_ext, store_dts_ext, DTS_WARN_HYST, NOT_USED),	\
	SENSOR_ATTR_2(temp##index##_alarm, S_IRUGO,			\
		show_alarm_beep, शून्य, ALARM_STATUS, index + 17),	\
	SENSOR_ATTR_2(temp##index##_beep, S_IWUSR | S_IRUGO,		\
		show_alarm_beep, store_beep, BEEP_ENABLE, index + 17) पूर्ण

/*
 * Don't change the attribute order, _beep is accessed by index
 * somewhere अन्यथा in the code
 */
#घोषणा SENSOR_ATTR_TEMP(index) अणु					\
	SENSOR_ATTR_2(temp##index##_type, S_IRUGO | (index < 5 ? S_IWUSR : 0), \
		show_temp_mode, store_temp_mode, NOT_USED, index - 1),	\
	SENSOR_ATTR_2(temp##index##_input, S_IRUGO, show_temp,		\
		शून्य, TEMP_READ, index - 1),				\
	SENSOR_ATTR_2(temp##index##_crit, S_IRUGO | S_IWUSR, show_temp,	\
		store_temp, TEMP_CRIT, index - 1),			\
	SENSOR_ATTR_2(temp##index##_crit_hyst, S_IRUGO | S_IWUSR,	\
		show_temp, store_temp, TEMP_CRIT_HYST, index - 1),	\
	SENSOR_ATTR_2(temp##index##_max, S_IRUGO | S_IWUSR, show_temp,	\
		store_temp, TEMP_WARN, index - 1),			\
	SENSOR_ATTR_2(temp##index##_max_hyst, S_IRUGO | S_IWUSR,	\
		show_temp, store_temp, TEMP_WARN_HYST, index - 1),	\
	SENSOR_ATTR_2(temp##index##_alarm, S_IRUGO,			\
		show_alarm_beep, शून्य, ALARM_STATUS,			\
		index + (index > 4 ? 11 : 17)),				\
	SENSOR_ATTR_2(temp##index##_beep, S_IWUSR | S_IRUGO,		\
		show_alarm_beep, store_beep, BEEP_ENABLE,		\
		index + (index > 4 ? 11 : 17)),				\
	SENSOR_ATTR_2(temp##index##_pwm_enable, S_IWUSR | S_IRUGO,	\
		show_temp_pwm_enable, store_temp_pwm_enable,		\
		TEMP_PWM_ENABLE, index - 1),				\
	SENSOR_ATTR_2(temp##index##_स्वतः_channels_pwm, S_IWUSR | S_IRUGO, \
		show_temp_pwm_enable, store_temp_pwm_enable,		\
		TEMP_PWM_FAN_MAP, index - 1),				\
	SENSOR_ATTR_2(thermal_cruise##index, S_IWUSR | S_IRUGO,		\
		show_temp_pwm, store_temp_pwm, TEMP_PWM_TTTI, index - 1), \
	SENSOR_ATTR_2(temp##index##_warn, S_IWUSR | S_IRUGO,		\
		show_temp_pwm, store_temp_pwm, TEMP_PWM_CTFS, index - 1), \
	SENSOR_ATTR_2(temp##index##_warn_hyst, S_IWUSR | S_IRUGO,	\
		show_temp_pwm, store_temp_pwm, TEMP_PWM_HCT, index - 1), \
	SENSOR_ATTR_2(temp##index##_operation_hyst, S_IWUSR | S_IRUGO,	\
		show_temp_pwm, store_temp_pwm, TEMP_PWM_HOT, index - 1), \
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक1_pwm, S_IRUGO | S_IWUSR, \
		show_sf4_pwm, store_sf4_pwm, 0, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक2_pwm, S_IRUGO | S_IWUSR, \
		show_sf4_pwm, store_sf4_pwm, 1, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक3_pwm, S_IRUGO | S_IWUSR, \
		show_sf4_pwm, store_sf4_pwm, 2, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक4_pwm, S_IRUGO | S_IWUSR, \
		show_sf4_pwm, store_sf4_pwm, 3, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक5_pwm, S_IRUGO | S_IWUSR, \
		show_sf4_pwm, store_sf4_pwm, 4, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक6_pwm, S_IRUGO | S_IWUSR, \
		show_sf4_pwm, store_sf4_pwm, 5, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक7_pwm, S_IRUGO | S_IWUSR, \
		show_sf4_pwm, store_sf4_pwm, 6, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक1_temp, S_IRUGO | S_IWUSR,\
		show_sf4_temp, store_sf4_temp, 0, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक2_temp, S_IRUGO | S_IWUSR,\
		show_sf4_temp, store_sf4_temp, 1, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक3_temp, S_IRUGO | S_IWUSR,\
		show_sf4_temp, store_sf4_temp, 2, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक4_temp, S_IRUGO | S_IWUSR,\
		show_sf4_temp, store_sf4_temp, 3, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक5_temp, S_IRUGO | S_IWUSR,\
		show_sf4_temp, store_sf4_temp, 4, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक6_temp, S_IRUGO | S_IWUSR,\
		show_sf4_temp, store_sf4_temp, 5, index - 1),		\
	SENSOR_ATTR_2(temp##index##_स्वतः_poपूर्णांक7_temp, S_IRUGO | S_IWUSR,\
		show_sf4_temp, store_sf4_temp, 6, index - 1) पूर्ण


अटल काष्ठा sensor_device_attribute_2 w83795_in[][5] = अणु
	SENSOR_ATTR_IN(0),
	SENSOR_ATTR_IN(1),
	SENSOR_ATTR_IN(2),
	SENSOR_ATTR_IN(3),
	SENSOR_ATTR_IN(4),
	SENSOR_ATTR_IN(5),
	SENSOR_ATTR_IN(6),
	SENSOR_ATTR_IN(7),
	SENSOR_ATTR_IN(8),
	SENSOR_ATTR_IN(9),
	SENSOR_ATTR_IN(10),
	SENSOR_ATTR_IN(11),
	SENSOR_ATTR_IN(12),
	SENSOR_ATTR_IN(13),
	SENSOR_ATTR_IN(14),
	SENSOR_ATTR_IN(15),
	SENSOR_ATTR_IN(16),
	SENSOR_ATTR_IN(17),
	SENSOR_ATTR_IN(18),
	SENSOR_ATTR_IN(19),
	SENSOR_ATTR_IN(20),
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 w83795_fan[][4] = अणु
	SENSOR_ATTR_FAN(1),
	SENSOR_ATTR_FAN(2),
	SENSOR_ATTR_FAN(3),
	SENSOR_ATTR_FAN(4),
	SENSOR_ATTR_FAN(5),
	SENSOR_ATTR_FAN(6),
	SENSOR_ATTR_FAN(7),
	SENSOR_ATTR_FAN(8),
	SENSOR_ATTR_FAN(9),
	SENSOR_ATTR_FAN(10),
	SENSOR_ATTR_FAN(11),
	SENSOR_ATTR_FAN(12),
	SENSOR_ATTR_FAN(13),
	SENSOR_ATTR_FAN(14),
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 w83795_temp[][28] = अणु
	SENSOR_ATTR_TEMP(1),
	SENSOR_ATTR_TEMP(2),
	SENSOR_ATTR_TEMP(3),
	SENSOR_ATTR_TEMP(4),
	SENSOR_ATTR_TEMP(5),
	SENSOR_ATTR_TEMP(6),
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 w83795_dts[][8] = अणु
	SENSOR_ATTR_DTS(7),
	SENSOR_ATTR_DTS(8),
	SENSOR_ATTR_DTS(9),
	SENSOR_ATTR_DTS(10),
	SENSOR_ATTR_DTS(11),
	SENSOR_ATTR_DTS(12),
	SENSOR_ATTR_DTS(13),
	SENSOR_ATTR_DTS(14),
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 w83795_pwm[][8] = अणु
	SENSOR_ATTR_PWM(1),
	SENSOR_ATTR_PWM(2),
	SENSOR_ATTR_PWM(3),
	SENSOR_ATTR_PWM(4),
	SENSOR_ATTR_PWM(5),
	SENSOR_ATTR_PWM(6),
	SENSOR_ATTR_PWM(7),
	SENSOR_ATTR_PWM(8),
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 w83795_tss[6] = अणु
	SENSOR_ATTR_2(temp1_source_sel, S_IWUSR | S_IRUGO,
		      show_temp_src, store_temp_src, NOT_USED, 0),
	SENSOR_ATTR_2(temp2_source_sel, S_IWUSR | S_IRUGO,
		      show_temp_src, store_temp_src, NOT_USED, 1),
	SENSOR_ATTR_2(temp3_source_sel, S_IWUSR | S_IRUGO,
		      show_temp_src, store_temp_src, NOT_USED, 2),
	SENSOR_ATTR_2(temp4_source_sel, S_IWUSR | S_IRUGO,
		      show_temp_src, store_temp_src, NOT_USED, 3),
	SENSOR_ATTR_2(temp5_source_sel, S_IWUSR | S_IRUGO,
		      show_temp_src, store_temp_src, NOT_USED, 4),
	SENSOR_ATTR_2(temp6_source_sel, S_IWUSR | S_IRUGO,
		      show_temp_src, store_temp_src, NOT_USED, 5),
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 sda_single_files[] = अणु
	SENSOR_ATTR_2(पूर्णांकrusion0_alarm, S_IWUSR | S_IRUGO, show_alarm_beep,
		      store_chassis_clear, ALARM_STATUS, 46),
#अगर_घोषित CONFIG_SENSORS_W83795_FANCTRL
	SENSOR_ATTR_2(speed_cruise_tolerance, S_IWUSR | S_IRUGO, show_fanin,
		store_fanin, FANIN_TOL, NOT_USED),
	SENSOR_ATTR_2(pwm_शेष, S_IWUSR | S_IRUGO, show_sf_setup,
		      store_sf_setup, SETUP_PWM_DEFAULT, NOT_USED),
	SENSOR_ATTR_2(pwm_upसमय, S_IWUSR | S_IRUGO, show_sf_setup,
		      store_sf_setup, SETUP_PWM_UPTIME, NOT_USED),
	SENSOR_ATTR_2(pwm_करोwnसमय, S_IWUSR | S_IRUGO, show_sf_setup,
		      store_sf_setup, SETUP_PWM_DOWNTIME, NOT_USED),
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा sensor_device_attribute_2 sda_beep_files[] = अणु
	SENSOR_ATTR_2(पूर्णांकrusion0_beep, S_IWUSR | S_IRUGO, show_alarm_beep,
		      store_beep, BEEP_ENABLE, 46),
	SENSOR_ATTR_2(beep_enable, S_IWUSR | S_IRUGO, show_alarm_beep,
		      store_beep, BEEP_ENABLE, 47),
पूर्ण;

/*
 * Driver पूर्णांकerface
 */

अटल व्योम w83795_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	अटल स्थिर u16 clkin[4] = अणु	/* in kHz */
		14318, 24000, 33333, 48000
	पूर्ण;
	u8 config;

	अगर (reset)
		w83795_ग_लिखो(client, W83795_REG_CONFIG, 0x80);

	/* Start monitoring अगर needed */
	config = w83795_पढ़ो(client, W83795_REG_CONFIG);
	अगर (!(config & W83795_REG_CONFIG_START)) अणु
		dev_info(&client->dev, "Enabling monitoring operations\n");
		w83795_ग_लिखो(client, W83795_REG_CONFIG,
			     config | W83795_REG_CONFIG_START);
	पूर्ण

	data->clkin = clkin[(config >> 3) & 0x3];
	dev_dbg(&client->dev, "clkin = %u kHz\n", data->clkin);
पूर्ण

अटल पूर्णांक w83795_get_device_id(काष्ठा i2c_client *client)
अणु
	पूर्णांक device_id;

	device_id = i2c_smbus_पढ़ो_byte_data(client, W83795_REG_DEVICEID);

	/*
	 * Special हाल क्रम rev. A chips; can't be checked first because later
	 * revisions emulate this क्रम compatibility
	 */
	अगर (device_id < 0 || (device_id & 0xf0) != 0x50) अणु
		पूर्णांक alt_id;

		alt_id = i2c_smbus_पढ़ो_byte_data(client,
						  W83795_REG_DEVICEID_A);
		अगर (alt_id == 0x50)
			device_id = alt_id;
	पूर्ण

	वापस device_id;
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक w83795_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	पूर्णांक bank, venकरोr_id, device_id, expected, i2c_addr, config;
	काष्ठा i2c_adapter *adapter = client->adapter;
	अचिन्हित लघु address = client->addr;
	स्थिर अक्षर *chip_name;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;
	bank = i2c_smbus_पढ़ो_byte_data(client, W83795_REG_BANKSEL);
	अगर (bank < 0 || (bank & 0x7c)) अणु
		dev_dbg(&adapter->dev,
			"w83795: Detection failed at addr 0x%02hx, check %s\n",
			address, "bank");
		वापस -ENODEV;
	पूर्ण

	/* Check Nuvoton venकरोr ID */
	venकरोr_id = i2c_smbus_पढ़ो_byte_data(client, W83795_REG_VENDORID);
	expected = bank & 0x80 ? 0x5c : 0xa3;
	अगर (venकरोr_id != expected) अणु
		dev_dbg(&adapter->dev,
			"w83795: Detection failed at addr 0x%02hx, check %s\n",
			address, "vendor id");
		वापस -ENODEV;
	पूर्ण

	/* Check device ID */
	device_id = w83795_get_device_id(client) |
		    (i2c_smbus_पढ़ो_byte_data(client, W83795_REG_CHIPID) << 8);
	अगर ((device_id >> 4) != 0x795) अणु
		dev_dbg(&adapter->dev,
			"w83795: Detection failed at addr 0x%02hx, check %s\n",
			address, "device id\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * If Nuvoton chip, address of chip and W83795_REG_I2C_ADDR
	 * should match
	 */
	अगर ((bank & 0x07) == 0) अणु
		i2c_addr = i2c_smbus_पढ़ो_byte_data(client,
						    W83795_REG_I2C_ADDR);
		अगर ((i2c_addr & 0x7f) != address) अणु
			dev_dbg(&adapter->dev,
				"w83795: Detection failed at addr 0x%02hx, "
				"check %s\n", address, "i2c addr");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * Check 795 chip type: 795G or 795ADG
	 * Usually we करोn't write to chips during detection, but here we don't
	 * quite have the choice; hopefully it's OK, we are about to वापस
	 * success anyway
	 */
	अगर ((bank & 0x07) != 0)
		i2c_smbus_ग_लिखो_byte_data(client, W83795_REG_BANKSEL,
					  bank & ~0x07);
	config = i2c_smbus_पढ़ो_byte_data(client, W83795_REG_CONFIG);
	अगर (config & W83795_REG_CONFIG_CONFIG48)
		chip_name = "w83795adg";
	अन्यथा
		chip_name = "w83795g";

	strlcpy(info->type, chip_name, I2C_NAME_SIZE);
	dev_info(&adapter->dev, "Found %s rev. %c at 0x%02hx\n", chip_name,
		 'A' + (device_id & 0xf), address);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SENSORS_W83795_FANCTRL
#घोषणा NUM_PWM_ATTRIBUTES	ARRAY_SIZE(w83795_pwm[0])
#घोषणा NUM_TEMP_ATTRIBUTES	ARRAY_SIZE(w83795_temp[0])
#अन्यथा
#घोषणा NUM_PWM_ATTRIBUTES	4
#घोषणा NUM_TEMP_ATTRIBUTES	8
#पूर्ण_अगर

अटल पूर्णांक w83795_handle_files(काष्ठा device *dev, पूर्णांक (*fn)(काष्ठा device *,
			       स्थिर काष्ठा device_attribute *))
अणु
	काष्ठा w83795_data *data = dev_get_drvdata(dev);
	पूर्णांक err, i, j;

	क्रम (i = 0; i < ARRAY_SIZE(w83795_in); i++) अणु
		अगर (!(data->has_in & (1 << i)))
			जारी;
		क्रम (j = 0; j < ARRAY_SIZE(w83795_in[0]); j++) अणु
			अगर (j == 4 && !data->enable_beep)
				जारी;
			err = fn(dev, &w83795_in[i][j].dev_attr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(w83795_fan); i++) अणु
		अगर (!(data->has_fan & (1 << i)))
			जारी;
		क्रम (j = 0; j < ARRAY_SIZE(w83795_fan[0]); j++) अणु
			अगर (j == 3 && !data->enable_beep)
				जारी;
			err = fn(dev, &w83795_fan[i][j].dev_attr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(w83795_tss); i++) अणु
		j = w83795_tss_useful(data, i);
		अगर (!j)
			जारी;
		err = fn(dev, &w83795_tss[i].dev_attr);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sda_single_files); i++) अणु
		err = fn(dev, &sda_single_files[i].dev_attr);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (data->enable_beep) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sda_beep_files); i++) अणु
			err = fn(dev, &sda_beep_files[i].dev_attr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < data->has_pwm; i++) अणु
		क्रम (j = 0; j < NUM_PWM_ATTRIBUTES; j++) अणु
			err = fn(dev, &w83795_pwm[i][j].dev_attr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(w83795_temp); i++) अणु
		अगर (!(data->has_temp & (1 << i)))
			जारी;
		क्रम (j = 0; j < NUM_TEMP_ATTRIBUTES; j++) अणु
			अगर (j == 7 && !data->enable_beep)
				जारी;
			err = fn(dev, &w83795_temp[i][j].dev_attr);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (data->enable_dts) अणु
		क्रम (i = 0; i < ARRAY_SIZE(w83795_dts); i++) अणु
			अगर (!(data->has_dts & (1 << i)))
				जारी;
			क्रम (j = 0; j < ARRAY_SIZE(w83795_dts[0]); j++) अणु
				अगर (j == 7 && !data->enable_beep)
					जारी;
				err = fn(dev, &w83795_dts[i][j].dev_attr);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* We need a wrapper that fits in w83795_handle_files */
अटल पूर्णांक device_हटाओ_file_wrapper(काष्ठा device *dev,
				      स्थिर काष्ठा device_attribute *attr)
अणु
	device_हटाओ_file(dev, attr);
	वापस 0;
पूर्ण

अटल व्योम w83795_check_dynamic_in_limits(काष्ठा i2c_client *client)
अणु
	काष्ठा w83795_data *data = i2c_get_clientdata(client);
	u8 vid_ctl;
	पूर्णांक i, err_max, err_min;

	vid_ctl = w83795_पढ़ो(client, W83795_REG_VID_CTRL);

	/* Return immediately अगर VRM isn't configured */
	अगर ((vid_ctl & 0x07) == 0x00 || (vid_ctl & 0x07) == 0x07)
		वापस;

	data->has_dyn_in = (vid_ctl >> 3) & 0x07;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (!(data->has_dyn_in & (1 << i)))
			जारी;

		/* Voltage limits in dynamic mode, चयन to पढ़ो-only */
		err_max = sysfs_chmod_file(&client->dev.kobj,
					   &w83795_in[i][2].dev_attr.attr,
					   S_IRUGO);
		err_min = sysfs_chmod_file(&client->dev.kobj,
					   &w83795_in[i][3].dev_attr.attr,
					   S_IRUGO);
		अगर (err_max || err_min)
			dev_warn(&client->dev,
				 "Failed to set in%d limits read-only (%d, %d)\n",
				 i, err_max, err_min);
		अन्यथा
			dev_info(&client->dev,
				 "in%d limits set dynamically from VID\n", i);
	पूर्ण
पूर्ण

/* Check pins that can be used क्रम either temperature or voltage monitoring */
अटल व्योम w83795_apply_temp_config(काष्ठा w83795_data *data, u8 config,
				     पूर्णांक temp_chan, पूर्णांक in_chan)
अणु
	/* config is a 2-bit value */
	चयन (config) अणु
	हाल 0x2: /* Voltage monitoring */
		data->has_in |= 1 << in_chan;
		अवरोध;
	हाल 0x1: /* Thermal diode */
		अगर (temp_chan >= 4)
			अवरोध;
		data->temp_mode |= 1 << temp_chan;
		fallthrough;
	हाल 0x3: /* Thermistor */
		data->has_temp |= 1 << temp_chan;
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा i2c_device_id w83795_id[];

अटल पूर्णांक w83795_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक i;
	u8 पंचांगp;
	काष्ठा device *dev = &client->dev;
	काष्ठा w83795_data *data;
	पूर्णांक err;

	data = devm_kzalloc(dev, माप(काष्ठा w83795_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->chip_type = i2c_match_id(w83795_id, client)->driver_data;
	data->bank = i2c_smbus_पढ़ो_byte_data(client, W83795_REG_BANKSEL);
	mutex_init(&data->update_lock);

	/* Initialize the chip */
	w83795_init_client(client);

	/* Check which voltages and fans are present */
	data->has_in = w83795_पढ़ो(client, W83795_REG_VOLT_CTRL1)
		     | (w83795_पढ़ो(client, W83795_REG_VOLT_CTRL2) << 8);
	data->has_fan = w83795_पढ़ो(client, W83795_REG_FANIN_CTRL1)
		      | (w83795_पढ़ो(client, W83795_REG_FANIN_CTRL2) << 8);

	/* Check which analog temperatures and extra voltages are present */
	पंचांगp = w83795_पढ़ो(client, W83795_REG_TEMP_CTRL1);
	अगर (पंचांगp & 0x20)
		data->enable_dts = 1;
	w83795_apply_temp_config(data, (पंचांगp >> 2) & 0x3, 5, 16);
	w83795_apply_temp_config(data, पंचांगp & 0x3, 4, 15);
	पंचांगp = w83795_पढ़ो(client, W83795_REG_TEMP_CTRL2);
	w83795_apply_temp_config(data, पंचांगp >> 6, 3, 20);
	w83795_apply_temp_config(data, (पंचांगp >> 4) & 0x3, 2, 19);
	w83795_apply_temp_config(data, (पंचांगp >> 2) & 0x3, 1, 18);
	w83795_apply_temp_config(data, पंचांगp & 0x3, 0, 17);

	/* Check DTS enable status */
	अगर (data->enable_dts) अणु
		अगर (1 & w83795_पढ़ो(client, W83795_REG_DTSC))
			data->enable_dts |= 2;
		data->has_dts = w83795_पढ़ो(client, W83795_REG_DTSE);
	पूर्ण

	/* Report PECI Tbase values */
	अगर (data->enable_dts == 1) अणु
		क्रम (i = 0; i < 8; i++) अणु
			अगर (!(data->has_dts & (1 << i)))
				जारी;
			पंचांगp = w83795_पढ़ो(client, W83795_REG_PECI_TBASE(i));
			dev_info(&client->dev,
				 "PECI agent %d Tbase temperature: %u\n",
				 i + 1, (अचिन्हित पूर्णांक)पंचांगp & 0x7f);
		पूर्ण
	पूर्ण

	data->has_gain = w83795_पढ़ो(client, W83795_REG_VMIGB_CTRL) & 0x0f;

	/* pwm and smart fan */
	अगर (data->chip_type == w83795g)
		data->has_pwm = 8;
	अन्यथा
		data->has_pwm = 2;

	/* Check अगर BEEP pin is available */
	अगर (data->chip_type == w83795g) अणु
		/* The W83795G has a dedicated BEEP pin */
		data->enable_beep = 1;
	पूर्ण अन्यथा अणु
		/*
		 * The W83795ADG has a shared pin क्रम OVT# and BEEP, so you
		 * can't have both
		 */
		पंचांगp = w83795_पढ़ो(client, W83795_REG_OVT_CFG);
		अगर ((पंचांगp & OVT_CFG_SEL) == 0)
			data->enable_beep = 1;
	पूर्ण

	err = w83795_handle_files(dev, device_create_file);
	अगर (err)
		जाओ निकास_हटाओ;

	अगर (data->chip_type == w83795g)
		w83795_check_dynamic_in_limits(client);

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	वापस 0;

निकास_हटाओ:
	w83795_handle_files(dev, device_हटाओ_file_wrapper);
	वापस err;
पूर्ण

अटल पूर्णांक w83795_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा w83795_data *data = i2c_get_clientdata(client);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	w83795_handle_files(&client->dev, device_हटाओ_file_wrapper);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा i2c_device_id w83795_id[] = अणु
	अणु "w83795g", w83795g पूर्ण,
	अणु "w83795adg", w83795adg पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, w83795_id);

अटल काष्ठा i2c_driver w83795_driver = अणु
	.driver = अणु
		   .name = "w83795",
	पूर्ण,
	.probe_new	= w83795_probe,
	.हटाओ		= w83795_हटाओ,
	.id_table	= w83795_id,

	.class		= I2C_CLASS_HWMON,
	.detect		= w83795_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(w83795_driver);

MODULE_AUTHOR("Wei Song, Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("W83795G/ADG hardware monitoring driver");
MODULE_LICENSE("GPL");
