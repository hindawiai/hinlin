<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm90.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *          monitoring
 * Copyright (C) 2003-2010  Jean Delvare <jdelvare@suse.de>
 *
 * Based on the lm83 driver. The LM90 is a sensor chip made by National
 * Semiconductor. It reports up to two temperatures (its own plus up to
 * one बाह्यal one) with a 0.125 deg resolution (1 deg क्रम local
 * temperature) and a 3-4 deg accuracy.
 *
 * This driver also supports the LM89 and LM99, two other sensor chips
 * made by National Semiconductor. Both have an increased remote
 * temperature measurement accuracy (1 degree), and the LM99
 * additionally shअगरts remote temperatures (measured and limits) by 16
 * degrees, which allows क्रम higher temperatures measurement.
 * Note that there is no way to dअगरferentiate between both chips.
 * When device is स्वतः-detected, the driver will assume an LM99.
 *
 * This driver also supports the LM86, another sensor chip made by
 * National Semiconductor. It is exactly similar to the LM90 except it
 * has a higher accuracy.
 *
 * This driver also supports the ADM1032, a sensor chip made by Analog
 * Devices. That chip is similar to the LM90, with a few dअगरferences
 * that are not handled by this driver. Among others, it has a higher
 * accuracy than the LM90, much like the LM86 करोes.
 *
 * This driver also supports the MAX6657, MAX6658 and MAX6659 sensor
 * chips made by Maxim. These chips are similar to the LM86.
 * Note that there is no easy way to dअगरferentiate between the three
 * variants. We use the device address to detect MAX6659, which will result
 * in a detection as max6657 अगर it is on address 0x4c. The extra address
 * and features of the MAX6659 are only supported अगर the chip is configured
 * explicitly as max6659, or अगर its address is not 0x4c.
 * These chips lack the remote temperature offset feature.
 *
 * This driver also supports the MAX6654 chip made by Maxim. This chip can
 * be at 9 dअगरferent addresses, similar to MAX6680/MAX6681. The MAX6654 is
 * otherwise similar to MAX6657/MAX6658/MAX6659. Extended range is available
 * by setting the configuration रेजिस्टर accordingly, and is करोne during
 * initialization. Extended precision is only available at conversion rates
 * of 1 Hz and slower. Note that extended precision is not enabled by
 * शेष, as this driver initializes all chips to 2 Hz by design.
 *
 * This driver also supports the MAX6646, MAX6647, MAX6648, MAX6649 and
 * MAX6692 chips made by Maxim.  These are again similar to the LM86,
 * but they use अचिन्हित temperature values and can report temperatures
 * from 0 to 145 degrees.
 *
 * This driver also supports the MAX6680 and MAX6681, two other sensor
 * chips made by Maxim. These are quite similar to the other Maxim
 * chips. The MAX6680 and MAX6681 only dअगरfer in the pinout so they can
 * be treated identically.
 *
 * This driver also supports the MAX6695 and MAX6696, two other sensor
 * chips made by Maxim. These are also quite similar to other Maxim
 * chips, but support three temperature sensors instead of two. MAX6695
 * and MAX6696 only dअगरfer in the pinout so they can be treated identically.
 *
 * This driver also supports ADT7461 and ADT7461A from Analog Devices as well as
 * NCT1008 from ON Semiconductor. The chips are supported in both compatibility
 * and extended mode. They are mostly compatible with LM90 except क्रम a data
 * क्रमmat dअगरference क्रम the temperature value रेजिस्टरs.
 *
 * This driver also supports the SA56004 from Philips. This device is
 * pin-compatible with the LM86, the ED/EDP parts are also address-compatible.
 *
 * This driver also supports the G781 from GMT. This device is compatible
 * with the ADM1032.
 *
 * This driver also supports TMP451 from Texas Instruments. This device is
 * supported in both compatibility and extended mode. It's mostly compatible
 * with ADT7461 except क्रम local temperature low byte रेजिस्टर and max
 * conversion rate.
 *
 * Since the LM90 was the first chipset supported by this driver, most
 * comments will refer to this chipset, but are actually general and
 * concern all supported chipsets, unless mentioned otherwise.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/consumer.h>

/*
 * Addresses to scan
 * Address is fully defined पूर्णांकernally and cannot be changed except क्रम
 * MAX6659, MAX6680 and MAX6681.
 * LM86, LM89, LM90, LM99, ADM1032, ADM1032-1, ADT7461, ADT7461A, MAX6649,
 * MAX6657, MAX6658, NCT1008 and W83L771 have address 0x4c.
 * ADM1032-2, ADT7461-2, ADT7461A-2, LM89-1, LM99-1, MAX6646, and NCT1008D
 * have address 0x4d.
 * MAX6647 has address 0x4e.
 * MAX6659 can have address 0x4c, 0x4d or 0x4e.
 * MAX6654, MAX6680, and MAX6681 can have address 0x18, 0x19, 0x1a, 0x29,
 * 0x2a, 0x2b, 0x4c, 0x4d or 0x4e.
 * SA56004 can have address 0x48 through 0x4F.
 */

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x18, 0x19, 0x1a, 0x29, 0x2a, 0x2b, 0x48, 0x49, 0x4a, 0x4b, 0x4c,
	0x4d, 0x4e, 0x4f, I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु lm90, adm1032, lm99, lm86, max6657, max6659, adt7461, max6680,
	max6646, w83l771, max6696, sa56004, g781, पंचांगp451, max6654 पूर्ण;

/*
 * The LM90 रेजिस्टरs
 */

#घोषणा LM90_REG_R_MAN_ID		0xFE
#घोषणा LM90_REG_R_CHIP_ID		0xFF
#घोषणा LM90_REG_R_CONFIG1		0x03
#घोषणा LM90_REG_W_CONFIG1		0x09
#घोषणा LM90_REG_R_CONFIG2		0xBF
#घोषणा LM90_REG_W_CONFIG2		0xBF
#घोषणा LM90_REG_R_CONVRATE		0x04
#घोषणा LM90_REG_W_CONVRATE		0x0A
#घोषणा LM90_REG_R_STATUS		0x02
#घोषणा LM90_REG_R_LOCAL_TEMP		0x00
#घोषणा LM90_REG_R_LOCAL_HIGH		0x05
#घोषणा LM90_REG_W_LOCAL_HIGH		0x0B
#घोषणा LM90_REG_R_LOCAL_LOW		0x06
#घोषणा LM90_REG_W_LOCAL_LOW		0x0C
#घोषणा LM90_REG_R_LOCAL_CRIT		0x20
#घोषणा LM90_REG_W_LOCAL_CRIT		0x20
#घोषणा LM90_REG_R_REMOTE_TEMPH		0x01
#घोषणा LM90_REG_R_REMOTE_TEMPL		0x10
#घोषणा LM90_REG_R_REMOTE_OFFSH		0x11
#घोषणा LM90_REG_W_REMOTE_OFFSH		0x11
#घोषणा LM90_REG_R_REMOTE_OFFSL		0x12
#घोषणा LM90_REG_W_REMOTE_OFFSL		0x12
#घोषणा LM90_REG_R_REMOTE_HIGHH		0x07
#घोषणा LM90_REG_W_REMOTE_HIGHH		0x0D
#घोषणा LM90_REG_R_REMOTE_HIGHL		0x13
#घोषणा LM90_REG_W_REMOTE_HIGHL		0x13
#घोषणा LM90_REG_R_REMOTE_LOWH		0x08
#घोषणा LM90_REG_W_REMOTE_LOWH		0x0E
#घोषणा LM90_REG_R_REMOTE_LOWL		0x14
#घोषणा LM90_REG_W_REMOTE_LOWL		0x14
#घोषणा LM90_REG_R_REMOTE_CRIT		0x19
#घोषणा LM90_REG_W_REMOTE_CRIT		0x19
#घोषणा LM90_REG_R_TCRIT_HYST		0x21
#घोषणा LM90_REG_W_TCRIT_HYST		0x21

/* MAX6646/6647/6649/6654/6657/6658/6659/6695/6696 रेजिस्टरs */

#घोषणा MAX6657_REG_R_LOCAL_TEMPL	0x11
#घोषणा MAX6696_REG_R_STATUS2		0x12
#घोषणा MAX6659_REG_R_REMOTE_EMERG	0x16
#घोषणा MAX6659_REG_W_REMOTE_EMERG	0x16
#घोषणा MAX6659_REG_R_LOCAL_EMERG	0x17
#घोषणा MAX6659_REG_W_LOCAL_EMERG	0x17

/*  SA56004 रेजिस्टरs */

#घोषणा SA56004_REG_R_LOCAL_TEMPL 0x22

#घोषणा LM90_MAX_CONVRATE_MS	16000	/* Maximum conversion rate in ms */

/* TMP451 रेजिस्टरs */
#घोषणा TMP451_REG_R_LOCAL_TEMPL	0x15

/*
 * Device flags
 */
#घोषणा LM90_FLAG_ADT7461_EXT	(1 << 0) /* ADT7461 extended mode	*/
/* Device features */
#घोषणा LM90_HAVE_OFFSET	(1 << 1) /* temperature offset रेजिस्टर	*/
#घोषणा LM90_HAVE_REM_LIMIT_EXT	(1 << 3) /* extended remote limit	*/
#घोषणा LM90_HAVE_EMERGENCY	(1 << 4) /* 3rd upper (emergency) limit	*/
#घोषणा LM90_HAVE_EMERGENCY_ALARM (1 << 5)/* emergency alarm		*/
#घोषणा LM90_HAVE_TEMP3		(1 << 6) /* 3rd temperature sensor	*/
#घोषणा LM90_HAVE_BROKEN_ALERT	(1 << 7) /* Broken alert		*/
#घोषणा LM90_PAUSE_FOR_CONFIG	(1 << 8) /* Pause conversion क्रम config	*/

/* LM90 status */
#घोषणा LM90_STATUS_LTHRM	(1 << 0) /* local THERM limit tripped */
#घोषणा LM90_STATUS_RTHRM	(1 << 1) /* remote THERM limit tripped */
#घोषणा LM90_STATUS_ROPEN	(1 << 2) /* remote is an खोलो circuit */
#घोषणा LM90_STATUS_RLOW	(1 << 3) /* remote low temp limit tripped */
#घोषणा LM90_STATUS_RHIGH	(1 << 4) /* remote high temp limit tripped */
#घोषणा LM90_STATUS_LLOW	(1 << 5) /* local low temp limit tripped */
#घोषणा LM90_STATUS_LHIGH	(1 << 6) /* local high temp limit tripped */

#घोषणा MAX6696_STATUS2_R2THRM	(1 << 1) /* remote2 THERM limit tripped */
#घोषणा MAX6696_STATUS2_R2OPEN	(1 << 2) /* remote2 is an खोलो circuit */
#घोषणा MAX6696_STATUS2_R2LOW	(1 << 3) /* remote2 low temp limit tripped */
#घोषणा MAX6696_STATUS2_R2HIGH	(1 << 4) /* remote2 high temp limit tripped */
#घोषणा MAX6696_STATUS2_ROT2	(1 << 5) /* remote emergency limit tripped */
#घोषणा MAX6696_STATUS2_R2OT2	(1 << 6) /* remote2 emergency limit tripped */
#घोषणा MAX6696_STATUS2_LOT2	(1 << 7) /* local emergency limit tripped */

/*
 * Driver data (common to all clients)
 */

अटल स्थिर काष्ठा i2c_device_id lm90_id[] = अणु
	अणु "adm1032", adm1032 पूर्ण,
	अणु "adt7461", adt7461 पूर्ण,
	अणु "adt7461a", adt7461 पूर्ण,
	अणु "g781", g781 पूर्ण,
	अणु "lm90", lm90 पूर्ण,
	अणु "lm86", lm86 पूर्ण,
	अणु "lm89", lm86 पूर्ण,
	अणु "lm99", lm99 पूर्ण,
	अणु "max6646", max6646 पूर्ण,
	अणु "max6647", max6646 पूर्ण,
	अणु "max6649", max6646 पूर्ण,
	अणु "max6654", max6654 पूर्ण,
	अणु "max6657", max6657 पूर्ण,
	अणु "max6658", max6657 पूर्ण,
	अणु "max6659", max6659 पूर्ण,
	अणु "max6680", max6680 पूर्ण,
	अणु "max6681", max6680 पूर्ण,
	अणु "max6695", max6696 पूर्ण,
	अणु "max6696", max6696 पूर्ण,
	अणु "nct1008", adt7461 पूर्ण,
	अणु "w83l771", w83l771 पूर्ण,
	अणु "sa56004", sa56004 पूर्ण,
	अणु "tmp451", पंचांगp451 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm90_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused lm90_of_match[] = अणु
	अणु
		.compatible = "adi,adm1032",
		.data = (व्योम *)adm1032
	पूर्ण,
	अणु
		.compatible = "adi,adt7461",
		.data = (व्योम *)adt7461
	पूर्ण,
	अणु
		.compatible = "adi,adt7461a",
		.data = (व्योम *)adt7461
	पूर्ण,
	अणु
		.compatible = "gmt,g781",
		.data = (व्योम *)g781
	पूर्ण,
	अणु
		.compatible = "national,lm90",
		.data = (व्योम *)lm90
	पूर्ण,
	अणु
		.compatible = "national,lm86",
		.data = (व्योम *)lm86
	पूर्ण,
	अणु
		.compatible = "national,lm89",
		.data = (व्योम *)lm86
	पूर्ण,
	अणु
		.compatible = "national,lm99",
		.data = (व्योम *)lm99
	पूर्ण,
	अणु
		.compatible = "dallas,max6646",
		.data = (व्योम *)max6646
	पूर्ण,
	अणु
		.compatible = "dallas,max6647",
		.data = (व्योम *)max6646
	पूर्ण,
	अणु
		.compatible = "dallas,max6649",
		.data = (व्योम *)max6646
	पूर्ण,
	अणु
		.compatible = "dallas,max6654",
		.data = (व्योम *)max6654
	पूर्ण,
	अणु
		.compatible = "dallas,max6657",
		.data = (व्योम *)max6657
	पूर्ण,
	अणु
		.compatible = "dallas,max6658",
		.data = (व्योम *)max6657
	पूर्ण,
	अणु
		.compatible = "dallas,max6659",
		.data = (व्योम *)max6659
	पूर्ण,
	अणु
		.compatible = "dallas,max6680",
		.data = (व्योम *)max6680
	पूर्ण,
	अणु
		.compatible = "dallas,max6681",
		.data = (व्योम *)max6680
	पूर्ण,
	अणु
		.compatible = "dallas,max6695",
		.data = (व्योम *)max6696
	पूर्ण,
	अणु
		.compatible = "dallas,max6696",
		.data = (व्योम *)max6696
	पूर्ण,
	अणु
		.compatible = "onnn,nct1008",
		.data = (व्योम *)adt7461
	पूर्ण,
	अणु
		.compatible = "winbond,w83l771",
		.data = (व्योम *)w83l771
	पूर्ण,
	अणु
		.compatible = "nxp,sa56004",
		.data = (व्योम *)sa56004
	पूर्ण,
	अणु
		.compatible = "ti,tmp451",
		.data = (व्योम *)पंचांगp451
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lm90_of_match);

/*
 * chip type specअगरic parameters
 */
काष्ठा lm90_params अणु
	u32 flags;		/* Capabilities */
	u16 alert_alarms;	/* Which alarm bits trigger ALERT# */
				/* Upper 8 bits क्रम max6695/96 */
	u8 max_convrate;	/* Maximum conversion rate रेजिस्टर value */
	u8 reg_local_ext;	/* Extended local temp रेजिस्टर (optional) */
पूर्ण;

अटल स्थिर काष्ठा lm90_params lm90_params[] = अणु
	[adm1032] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT
		  | LM90_HAVE_BROKEN_ALERT,
		.alert_alarms = 0x7c,
		.max_convrate = 10,
	पूर्ण,
	[adt7461] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT
		  | LM90_HAVE_BROKEN_ALERT,
		.alert_alarms = 0x7c,
		.max_convrate = 10,
	पूर्ण,
	[g781] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT
		  | LM90_HAVE_BROKEN_ALERT,
		.alert_alarms = 0x7c,
		.max_convrate = 8,
	पूर्ण,
	[lm86] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT,
		.alert_alarms = 0x7b,
		.max_convrate = 9,
	पूर्ण,
	[lm90] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT,
		.alert_alarms = 0x7b,
		.max_convrate = 9,
	पूर्ण,
	[lm99] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT,
		.alert_alarms = 0x7b,
		.max_convrate = 9,
	पूर्ण,
	[max6646] = अणु
		.alert_alarms = 0x7c,
		.max_convrate = 6,
		.reg_local_ext = MAX6657_REG_R_LOCAL_TEMPL,
	पूर्ण,
	[max6654] = अणु
		.alert_alarms = 0x7c,
		.max_convrate = 7,
		.reg_local_ext = MAX6657_REG_R_LOCAL_TEMPL,
	पूर्ण,
	[max6657] = अणु
		.flags = LM90_PAUSE_FOR_CONFIG,
		.alert_alarms = 0x7c,
		.max_convrate = 8,
		.reg_local_ext = MAX6657_REG_R_LOCAL_TEMPL,
	पूर्ण,
	[max6659] = अणु
		.flags = LM90_HAVE_EMERGENCY,
		.alert_alarms = 0x7c,
		.max_convrate = 8,
		.reg_local_ext = MAX6657_REG_R_LOCAL_TEMPL,
	पूर्ण,
	[max6680] = अणु
		.flags = LM90_HAVE_OFFSET,
		.alert_alarms = 0x7c,
		.max_convrate = 7,
	पूर्ण,
	[max6696] = अणु
		.flags = LM90_HAVE_EMERGENCY
		  | LM90_HAVE_EMERGENCY_ALARM | LM90_HAVE_TEMP3,
		.alert_alarms = 0x1c7c,
		.max_convrate = 6,
		.reg_local_ext = MAX6657_REG_R_LOCAL_TEMPL,
	पूर्ण,
	[w83l771] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT,
		.alert_alarms = 0x7c,
		.max_convrate = 8,
	पूर्ण,
	[sa56004] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT,
		.alert_alarms = 0x7b,
		.max_convrate = 9,
		.reg_local_ext = SA56004_REG_R_LOCAL_TEMPL,
	पूर्ण,
	[पंचांगp451] = अणु
		.flags = LM90_HAVE_OFFSET | LM90_HAVE_REM_LIMIT_EXT
		  | LM90_HAVE_BROKEN_ALERT,
		.alert_alarms = 0x7c,
		.max_convrate = 9,
		.reg_local_ext = TMP451_REG_R_LOCAL_TEMPL,
	पूर्ण,
पूर्ण;

/*
 * TEMP8 रेजिस्टर index
 */
क्रमागत lm90_temp8_reg_index अणु
	LOCAL_LOW = 0,
	LOCAL_HIGH,
	LOCAL_CRIT,
	REMOTE_CRIT,
	LOCAL_EMERG,	/* max6659 and max6695/96 */
	REMOTE_EMERG,	/* max6659 and max6695/96 */
	REMOTE2_CRIT,	/* max6695/96 only */
	REMOTE2_EMERG,	/* max6695/96 only */
	TEMP8_REG_NUM
पूर्ण;

/*
 * TEMP11 रेजिस्टर index
 */
क्रमागत lm90_temp11_reg_index अणु
	REMOTE_TEMP = 0,
	REMOTE_LOW,
	REMOTE_HIGH,
	REMOTE_OFFSET,	/* except max6646, max6657/58/59, and max6695/96 */
	LOCAL_TEMP,
	REMOTE2_TEMP,	/* max6695/96 only */
	REMOTE2_LOW,	/* max6695/96 only */
	REMOTE2_HIGH,	/* max6695/96 only */
	TEMP11_REG_NUM
पूर्ण;

/*
 * Client data (each client माला_लो its own)
 */

काष्ठा lm90_data अणु
	काष्ठा i2c_client *client;
	u32 channel_config[4];
	काष्ठा hwmon_channel_info temp_info;
	स्थिर काष्ठा hwmon_channel_info *info[3];
	काष्ठा hwmon_chip_info chip;
	काष्ठा mutex update_lock;
	bool valid;		/* true अगर रेजिस्टर values are valid */
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	पूर्णांक kind;
	u32 flags;

	अचिन्हित पूर्णांक update_पूर्णांकerval; /* in milliseconds */

	u8 config;		/* Current configuration रेजिस्टर value */
	u8 config_orig;		/* Original configuration रेजिस्टर value */
	u8 convrate_orig;	/* Original conversion rate रेजिस्टर value */
	u16 alert_alarms;	/* Which alarm bits trigger ALERT# */
				/* Upper 8 bits क्रम max6695/96 */
	u8 max_convrate;	/* Maximum conversion rate */
	u8 reg_local_ext;	/* local extension रेजिस्टर offset */

	/* रेजिस्टरs values */
	s8 temp8[TEMP8_REG_NUM];
	s16 temp11[TEMP11_REG_NUM];
	u8 temp_hyst;
	u16 alarms; /* bitvector (upper 8 bits क्रम max6695/96) */
पूर्ण;

/*
 * Support functions
 */

/*
 * The ADM1032 supports PEC but not on ग_लिखो byte transactions, so we need
 * to explicitly ask क्रम a transaction without PEC.
 */
अटल अंतरभूत s32 adm1032_ग_लिखो_byte(काष्ठा i2c_client *client, u8 value)
अणु
	वापस i2c_smbus_xfer(client->adapter, client->addr,
			      client->flags & ~I2C_CLIENT_PEC,
			      I2C_SMBUS_WRITE, value, I2C_SMBUS_BYTE, शून्य);
पूर्ण

/*
 * It is assumed that client->update_lock is held (unless we are in
 * detection or initialization steps). This matters when PEC is enabled,
 * because we करोn't want the address poपूर्णांकer to change between the ग_लिखो
 * byte and the पढ़ो byte transactions.
 */
अटल पूर्णांक lm90_पढ़ो_reg(काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक err;

	अगर (client->flags & I2C_CLIENT_PEC) अणु
		err = adm1032_ग_लिखो_byte(client, reg);
		अगर (err >= 0)
			err = i2c_smbus_पढ़ो_byte(client);
	पूर्ण अन्यथा
		err = i2c_smbus_पढ़ो_byte_data(client, reg);

	वापस err;
पूर्ण

अटल पूर्णांक lm90_पढ़ो16(काष्ठा i2c_client *client, u8 regh, u8 regl)
अणु
	पूर्णांक oldh, newh, l;

	/*
	 * There is a trick here. We have to पढ़ो two रेजिस्टरs to have the
	 * sensor temperature, but we have to beware a conversion could occur
	 * between the पढ़ोings. The datasheet says we should either use
	 * the one-shot conversion रेजिस्टर, which we करोn't want to करो
	 * (disables hardware monitoring) or monitor the busy bit, which is
	 * impossible (we can't पढ़ो the values and monitor that bit at the
	 * exact same समय). So the solution used here is to पढ़ो the high
	 * byte once, then the low byte, then the high byte again. If the new
	 * high byte matches the old one, then we have a valid पढ़ोing. Else
	 * we have to पढ़ो the low byte again, and now we believe we have a
	 * correct पढ़ोing.
	 */
	oldh = lm90_पढ़ो_reg(client, regh);
	अगर (oldh < 0)
		वापस oldh;
	l = lm90_पढ़ो_reg(client, regl);
	अगर (l < 0)
		वापस l;
	newh = lm90_पढ़ो_reg(client, regh);
	अगर (newh < 0)
		वापस newh;
	अगर (oldh != newh) अणु
		l = lm90_पढ़ो_reg(client, regl);
		अगर (l < 0)
			वापस l;
	पूर्ण
	वापस (newh << 8) | l;
पूर्ण

अटल पूर्णांक lm90_update_confreg(काष्ठा lm90_data *data, u8 config)
अणु
	अगर (data->config != config) अणु
		पूर्णांक err;

		err = i2c_smbus_ग_लिखो_byte_data(data->client,
						LM90_REG_W_CONFIG1,
						config);
		अगर (err)
			वापस err;
		data->config = config;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * client->update_lock must be held when calling this function (unless we are
 * in detection or initialization steps), and जबतक a remote channel other
 * than channel 0 is selected. Also, calling code must make sure to re-select
 * बाह्यal channel 0 beक्रमe releasing the lock. This is necessary because
 * various रेजिस्टरs have dअगरferent meanings as a result of selecting a
 * non-शेष remote channel.
 */
अटल पूर्णांक lm90_select_remote_channel(काष्ठा lm90_data *data, पूर्णांक channel)
अणु
	पूर्णांक err = 0;

	अगर (data->kind == max6696) अणु
		u8 config = data->config & ~0x08;

		अगर (channel)
			config |= 0x08;
		err = lm90_update_confreg(data, config);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक lm90_ग_लिखो_convrate(काष्ठा lm90_data *data, पूर्णांक val)
अणु
	u8 config = data->config;
	पूर्णांक err;

	/* Save config and छोड़ो conversion */
	अगर (data->flags & LM90_PAUSE_FOR_CONFIG) अणु
		err = lm90_update_confreg(data, config | 0x40);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Set conv rate */
	err = i2c_smbus_ग_लिखो_byte_data(data->client, LM90_REG_W_CONVRATE, val);

	/* Revert change to config */
	lm90_update_confreg(data, config);

	वापस err;
पूर्ण

/*
 * Set conversion rate.
 * client->update_lock must be held when calling this function (unless we are
 * in detection or initialization steps).
 */
अटल पूर्णांक lm90_set_convrate(काष्ठा i2c_client *client, काष्ठा lm90_data *data,
			     अचिन्हित पूर्णांक पूर्णांकerval)
अणु
	अचिन्हित पूर्णांक update_पूर्णांकerval;
	पूर्णांक i, err;

	/* Shअगरt calculations to aव्योम rounding errors */
	पूर्णांकerval <<= 6;

	/* find the nearest update rate */
	क्रम (i = 0, update_पूर्णांकerval = LM90_MAX_CONVRATE_MS << 6;
	     i < data->max_convrate; i++, update_पूर्णांकerval >>= 1)
		अगर (पूर्णांकerval >= update_पूर्णांकerval * 3 / 4)
			अवरोध;

	err = lm90_ग_लिखो_convrate(data, i);
	data->update_पूर्णांकerval = DIV_ROUND_CLOSEST(update_पूर्णांकerval, 64);
	वापस err;
पूर्ण

अटल पूर्णांक lm90_update_limits(काष्ठा device *dev)
अणु
	काष्ठा lm90_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक val;

	val = lm90_पढ़ो_reg(client, LM90_REG_R_LOCAL_CRIT);
	अगर (val < 0)
		वापस val;
	data->temp8[LOCAL_CRIT] = val;

	val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_CRIT);
	अगर (val < 0)
		वापस val;
	data->temp8[REMOTE_CRIT] = val;

	val = lm90_पढ़ो_reg(client, LM90_REG_R_TCRIT_HYST);
	अगर (val < 0)
		वापस val;
	data->temp_hyst = val;

	val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_LOWH);
	अगर (val < 0)
		वापस val;
	data->temp11[REMOTE_LOW] = val << 8;

	अगर (data->flags & LM90_HAVE_REM_LIMIT_EXT) अणु
		val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_LOWL);
		अगर (val < 0)
			वापस val;
		data->temp11[REMOTE_LOW] |= val;
	पूर्ण

	val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_HIGHH);
	अगर (val < 0)
		वापस val;
	data->temp11[REMOTE_HIGH] = val << 8;

	अगर (data->flags & LM90_HAVE_REM_LIMIT_EXT) अणु
		val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_HIGHL);
		अगर (val < 0)
			वापस val;
		data->temp11[REMOTE_HIGH] |= val;
	पूर्ण

	अगर (data->flags & LM90_HAVE_OFFSET) अणु
		val = lm90_पढ़ो16(client, LM90_REG_R_REMOTE_OFFSH,
				  LM90_REG_R_REMOTE_OFFSL);
		अगर (val < 0)
			वापस val;
		data->temp11[REMOTE_OFFSET] = val;
	पूर्ण

	अगर (data->flags & LM90_HAVE_EMERGENCY) अणु
		val = lm90_पढ़ो_reg(client, MAX6659_REG_R_LOCAL_EMERG);
		अगर (val < 0)
			वापस val;
		data->temp8[LOCAL_EMERG] = val;

		val = lm90_पढ़ो_reg(client, MAX6659_REG_R_REMOTE_EMERG);
		अगर (val < 0)
			वापस val;
		data->temp8[REMOTE_EMERG] = val;
	पूर्ण

	अगर (data->kind == max6696) अणु
		val = lm90_select_remote_channel(data, 1);
		अगर (val < 0)
			वापस val;

		val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_CRIT);
		अगर (val < 0)
			वापस val;
		data->temp8[REMOTE2_CRIT] = val;

		val = lm90_पढ़ो_reg(client, MAX6659_REG_R_REMOTE_EMERG);
		अगर (val < 0)
			वापस val;
		data->temp8[REMOTE2_EMERG] = val;

		val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_LOWH);
		अगर (val < 0)
			वापस val;
		data->temp11[REMOTE2_LOW] = val << 8;

		val = lm90_पढ़ो_reg(client, LM90_REG_R_REMOTE_HIGHH);
		अगर (val < 0)
			वापस val;
		data->temp11[REMOTE2_HIGH] = val << 8;

		lm90_select_remote_channel(data, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm90_update_device(काष्ठा device *dev)
अणु
	काष्ठा lm90_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ next_update;
	पूर्णांक val;

	अगर (!data->valid) अणु
		val = lm90_update_limits(dev);
		अगर (val < 0)
			वापस val;
	पूर्ण

	next_update = data->last_updated +
		      msecs_to_jअगरfies(data->update_पूर्णांकerval);
	अगर (समय_after(jअगरfies, next_update) || !data->valid) अणु
		dev_dbg(&client->dev, "Updating lm90 data.\n");

		data->valid = false;

		val = lm90_पढ़ो_reg(client, LM90_REG_R_LOCAL_LOW);
		अगर (val < 0)
			वापस val;
		data->temp8[LOCAL_LOW] = val;

		val = lm90_पढ़ो_reg(client, LM90_REG_R_LOCAL_HIGH);
		अगर (val < 0)
			वापस val;
		data->temp8[LOCAL_HIGH] = val;

		अगर (data->reg_local_ext) अणु
			val = lm90_पढ़ो16(client, LM90_REG_R_LOCAL_TEMP,
					  data->reg_local_ext);
			अगर (val < 0)
				वापस val;
			data->temp11[LOCAL_TEMP] = val;
		पूर्ण अन्यथा अणु
			val = lm90_पढ़ो_reg(client, LM90_REG_R_LOCAL_TEMP);
			अगर (val < 0)
				वापस val;
			data->temp11[LOCAL_TEMP] = val << 8;
		पूर्ण
		val = lm90_पढ़ो16(client, LM90_REG_R_REMOTE_TEMPH,
				  LM90_REG_R_REMOTE_TEMPL);
		अगर (val < 0)
			वापस val;
		data->temp11[REMOTE_TEMP] = val;

		val = lm90_पढ़ो_reg(client, LM90_REG_R_STATUS);
		अगर (val < 0)
			वापस val;
		data->alarms = val;	/* lower 8 bit of alarms */

		अगर (data->kind == max6696) अणु
			val = lm90_select_remote_channel(data, 1);
			अगर (val < 0)
				वापस val;

			val = lm90_पढ़ो16(client, LM90_REG_R_REMOTE_TEMPH,
					  LM90_REG_R_REMOTE_TEMPL);
			अगर (val < 0) अणु
				lm90_select_remote_channel(data, 0);
				वापस val;
			पूर्ण
			data->temp11[REMOTE2_TEMP] = val;

			lm90_select_remote_channel(data, 0);

			val = lm90_पढ़ो_reg(client, MAX6696_REG_R_STATUS2);
			अगर (val < 0)
				वापस val;
			data->alarms |= val << 8;
		पूर्ण

		/*
		 * Re-enable ALERT# output अगर it was originally enabled and
		 * relevant alarms are all clear
		 */
		अगर (!(data->config_orig & 0x80) &&
		    !(data->alarms & data->alert_alarms)) अणु
			अगर (data->config & 0x80) अणु
				dev_dbg(&client->dev, "Re-enabling ALERT#\n");
				lm90_update_confreg(data, data->config & ~0x80);
			पूर्ण
		पूर्ण

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Conversions
 * For local temperatures and limits, critical limits and the hysteresis
 * value, the LM90 uses चिन्हित 8-bit values with LSB = 1 degree Celsius.
 * For remote temperatures and limits, it uses चिन्हित 11-bit values with
 * LSB = 0.125 degree Celsius, left-justअगरied in 16-bit रेजिस्टरs.  Some
 * Maxim chips use अचिन्हित values.
 */

अटल अंतरभूत पूर्णांक temp_from_s8(s8 val)
अणु
	वापस val * 1000;
पूर्ण

अटल अंतरभूत पूर्णांक temp_from_u8(u8 val)
अणु
	वापस val * 1000;
पूर्ण

अटल अंतरभूत पूर्णांक temp_from_s16(s16 val)
अणु
	वापस val / 32 * 125;
पूर्ण

अटल अंतरभूत पूर्णांक temp_from_u16(u16 val)
अणु
	वापस val / 32 * 125;
पूर्ण

अटल s8 temp_to_s8(दीर्घ val)
अणु
	अगर (val <= -128000)
		वापस -128;
	अगर (val >= 127000)
		वापस 127;
	अगर (val < 0)
		वापस (val - 500) / 1000;
	वापस (val + 500) / 1000;
पूर्ण

अटल u8 temp_to_u8(दीर्घ val)
अणु
	अगर (val <= 0)
		वापस 0;
	अगर (val >= 255000)
		वापस 255;
	वापस (val + 500) / 1000;
पूर्ण

अटल s16 temp_to_s16(दीर्घ val)
अणु
	अगर (val <= -128000)
		वापस 0x8000;
	अगर (val >= 127875)
		वापस 0x7FE0;
	अगर (val < 0)
		वापस (val - 62) / 125 * 32;
	वापस (val + 62) / 125 * 32;
पूर्ण

अटल u8 hyst_to_reg(दीर्घ val)
अणु
	अगर (val <= 0)
		वापस 0;
	अगर (val >= 30500)
		वापस 31;
	वापस (val + 500) / 1000;
पूर्ण

/*
 * ADT7461 in compatibility mode is almost identical to LM90 except that
 * attempts to ग_लिखो values that are outside the range 0 < temp < 127 are
 * treated as the boundary value.
 *
 * ADT7461 in "extended mode" operation uses अचिन्हित पूर्णांकegers offset by
 * 64 (e.g., 0 -> -64 degC).  The range is restricted to -64..191 degC.
 */
अटल अंतरभूत पूर्णांक temp_from_u8_adt7461(काष्ठा lm90_data *data, u8 val)
अणु
	अगर (data->flags & LM90_FLAG_ADT7461_EXT)
		वापस (val - 64) * 1000;
	वापस temp_from_s8(val);
पूर्ण

अटल अंतरभूत पूर्णांक temp_from_u16_adt7461(काष्ठा lm90_data *data, u16 val)
अणु
	अगर (data->flags & LM90_FLAG_ADT7461_EXT)
		वापस (val - 0x4000) / 64 * 250;
	वापस temp_from_s16(val);
पूर्ण

अटल u8 temp_to_u8_adt7461(काष्ठा lm90_data *data, दीर्घ val)
अणु
	अगर (data->flags & LM90_FLAG_ADT7461_EXT) अणु
		अगर (val <= -64000)
			वापस 0;
		अगर (val >= 191000)
			वापस 0xFF;
		वापस (val + 500 + 64000) / 1000;
	पूर्ण
	अगर (val <= 0)
		वापस 0;
	अगर (val >= 127000)
		वापस 127;
	वापस (val + 500) / 1000;
पूर्ण

अटल u16 temp_to_u16_adt7461(काष्ठा lm90_data *data, दीर्घ val)
अणु
	अगर (data->flags & LM90_FLAG_ADT7461_EXT) अणु
		अगर (val <= -64000)
			वापस 0;
		अगर (val >= 191750)
			वापस 0xFFC0;
		वापस (val + 64000 + 125) / 250 * 64;
	पूर्ण
	अगर (val <= 0)
		वापस 0;
	अगर (val >= 127750)
		वापस 0x7FC0;
	वापस (val + 125) / 250 * 64;
पूर्ण

/* pec used क्रम ADM1032 only */
अटल sमाप_प्रकार pec_show(काष्ठा device *dev, काष्ठा device_attribute *dummy,
			अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस प्र_लिखो(buf, "%d\n", !!(client->flags & I2C_CLIENT_PEC));
पूर्ण

अटल sमाप_प्रकार pec_store(काष्ठा device *dev, काष्ठा device_attribute *dummy,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err < 0)
		वापस err;

	चयन (val) अणु
	हाल 0:
		client->flags &= ~I2C_CLIENT_PEC;
		अवरोध;
	हाल 1:
		client->flags |= I2C_CLIENT_PEC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(pec);

अटल पूर्णांक lm90_get_temp11(काष्ठा lm90_data *data, पूर्णांक index)
अणु
	s16 temp11 = data->temp11[index];
	पूर्णांक temp;

	अगर (data->kind == adt7461 || data->kind == पंचांगp451)
		temp = temp_from_u16_adt7461(data, temp11);
	अन्यथा अगर (data->kind == max6646)
		temp = temp_from_u16(temp11);
	अन्यथा
		temp = temp_from_s16(temp11);

	/* +16 degrees offset क्रम temp2 क्रम the LM99 */
	अगर (data->kind == lm99 && index <= 2)
		temp += 16000;

	वापस temp;
पूर्ण

अटल पूर्णांक lm90_set_temp11(काष्ठा lm90_data *data, पूर्णांक index, दीर्घ val)
अणु
	अटल काष्ठा reg अणु
		u8 high;
		u8 low;
	पूर्ण reg[] = अणु
	[REMOTE_LOW] = अणु LM90_REG_W_REMOTE_LOWH, LM90_REG_W_REMOTE_LOWL पूर्ण,
	[REMOTE_HIGH] = अणु LM90_REG_W_REMOTE_HIGHH, LM90_REG_W_REMOTE_HIGHL पूर्ण,
	[REMOTE_OFFSET] = अणु LM90_REG_W_REMOTE_OFFSH, LM90_REG_W_REMOTE_OFFSL पूर्ण,
	[REMOTE2_LOW] = अणु LM90_REG_W_REMOTE_LOWH, LM90_REG_W_REMOTE_LOWL पूर्ण,
	[REMOTE2_HIGH] = अणु LM90_REG_W_REMOTE_HIGHH, LM90_REG_W_REMOTE_HIGHL पूर्ण
	पूर्ण;
	काष्ठा i2c_client *client = data->client;
	काष्ठा reg *regp = &reg[index];
	पूर्णांक err;

	/* +16 degrees offset क्रम temp2 क्रम the LM99 */
	अगर (data->kind == lm99 && index <= 2)
		val -= 16000;

	अगर (data->kind == adt7461 || data->kind == पंचांगp451)
		data->temp11[index] = temp_to_u16_adt7461(data, val);
	अन्यथा अगर (data->kind == max6646)
		data->temp11[index] = temp_to_u8(val) << 8;
	अन्यथा अगर (data->flags & LM90_HAVE_REM_LIMIT_EXT)
		data->temp11[index] = temp_to_s16(val);
	अन्यथा
		data->temp11[index] = temp_to_s8(val) << 8;

	lm90_select_remote_channel(data, index >= 3);
	err = i2c_smbus_ग_लिखो_byte_data(client, regp->high,
				  data->temp11[index] >> 8);
	अगर (err < 0)
		वापस err;
	अगर (data->flags & LM90_HAVE_REM_LIMIT_EXT)
		err = i2c_smbus_ग_लिखो_byte_data(client, regp->low,
						data->temp11[index] & 0xff);

	lm90_select_remote_channel(data, 0);
	वापस err;
पूर्ण

अटल पूर्णांक lm90_get_temp8(काष्ठा lm90_data *data, पूर्णांक index)
अणु
	s8 temp8 = data->temp8[index];
	पूर्णांक temp;

	अगर (data->kind == adt7461 || data->kind == पंचांगp451)
		temp = temp_from_u8_adt7461(data, temp8);
	अन्यथा अगर (data->kind == max6646)
		temp = temp_from_u8(temp8);
	अन्यथा
		temp = temp_from_s8(temp8);

	/* +16 degrees offset क्रम temp2 क्रम the LM99 */
	अगर (data->kind == lm99 && index == 3)
		temp += 16000;

	वापस temp;
पूर्ण

अटल पूर्णांक lm90_set_temp8(काष्ठा lm90_data *data, पूर्णांक index, दीर्घ val)
अणु
	अटल स्थिर u8 reg[TEMP8_REG_NUM] = अणु
		LM90_REG_W_LOCAL_LOW,
		LM90_REG_W_LOCAL_HIGH,
		LM90_REG_W_LOCAL_CRIT,
		LM90_REG_W_REMOTE_CRIT,
		MAX6659_REG_W_LOCAL_EMERG,
		MAX6659_REG_W_REMOTE_EMERG,
		LM90_REG_W_REMOTE_CRIT,
		MAX6659_REG_W_REMOTE_EMERG,
	पूर्ण;
	काष्ठा i2c_client *client = data->client;
	पूर्णांक err;

	/* +16 degrees offset क्रम temp2 क्रम the LM99 */
	अगर (data->kind == lm99 && index == 3)
		val -= 16000;

	अगर (data->kind == adt7461 || data->kind == पंचांगp451)
		data->temp8[index] = temp_to_u8_adt7461(data, val);
	अन्यथा अगर (data->kind == max6646)
		data->temp8[index] = temp_to_u8(val);
	अन्यथा
		data->temp8[index] = temp_to_s8(val);

	lm90_select_remote_channel(data, index >= 6);
	err = i2c_smbus_ग_लिखो_byte_data(client, reg[index], data->temp8[index]);
	lm90_select_remote_channel(data, 0);

	वापस err;
पूर्ण

अटल पूर्णांक lm90_get_temphyst(काष्ठा lm90_data *data, पूर्णांक index)
अणु
	पूर्णांक temp;

	अगर (data->kind == adt7461 || data->kind == पंचांगp451)
		temp = temp_from_u8_adt7461(data, data->temp8[index]);
	अन्यथा अगर (data->kind == max6646)
		temp = temp_from_u8(data->temp8[index]);
	अन्यथा
		temp = temp_from_s8(data->temp8[index]);

	/* +16 degrees offset क्रम temp2 क्रम the LM99 */
	अगर (data->kind == lm99 && index == 3)
		temp += 16000;

	वापस temp - temp_from_s8(data->temp_hyst);
पूर्ण

अटल पूर्णांक lm90_set_temphyst(काष्ठा lm90_data *data, दीर्घ val)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक temp;
	पूर्णांक err;

	अगर (data->kind == adt7461 || data->kind == पंचांगp451)
		temp = temp_from_u8_adt7461(data, data->temp8[LOCAL_CRIT]);
	अन्यथा अगर (data->kind == max6646)
		temp = temp_from_u8(data->temp8[LOCAL_CRIT]);
	अन्यथा
		temp = temp_from_s8(data->temp8[LOCAL_CRIT]);

	data->temp_hyst = hyst_to_reg(temp - val);
	err = i2c_smbus_ग_लिखो_byte_data(client, LM90_REG_W_TCRIT_HYST,
					data->temp_hyst);
	वापस err;
पूर्ण

अटल स्थिर u8 lm90_temp_index[3] = अणु
	LOCAL_TEMP, REMOTE_TEMP, REMOTE2_TEMP
पूर्ण;

अटल स्थिर u8 lm90_temp_min_index[3] = अणु
	LOCAL_LOW, REMOTE_LOW, REMOTE2_LOW
पूर्ण;

अटल स्थिर u8 lm90_temp_max_index[3] = अणु
	LOCAL_HIGH, REMOTE_HIGH, REMOTE2_HIGH
पूर्ण;

अटल स्थिर u8 lm90_temp_crit_index[3] = अणु
	LOCAL_CRIT, REMOTE_CRIT, REMOTE2_CRIT
पूर्ण;

अटल स्थिर u8 lm90_temp_emerg_index[3] = अणु
	LOCAL_EMERG, REMOTE_EMERG, REMOTE2_EMERG
पूर्ण;

अटल स्थिर u8 lm90_min_alarm_bits[3] = अणु 5, 3, 11 पूर्ण;
अटल स्थिर u8 lm90_max_alarm_bits[3] = अणु 6, 4, 12 पूर्ण;
अटल स्थिर u8 lm90_crit_alarm_bits[3] = अणु 0, 1, 9 पूर्ण;
अटल स्थिर u8 lm90_emergency_alarm_bits[3] = अणु 15, 13, 14 पूर्ण;
अटल स्थिर u8 lm90_fault_bits[3] = अणु 0, 2, 10 पूर्ण;

अटल पूर्णांक lm90_temp_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा lm90_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	mutex_lock(&data->update_lock);
	err = lm90_update_device(dev);
	mutex_unlock(&data->update_lock);
	अगर (err)
		वापस err;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		*val = lm90_get_temp11(data, lm90_temp_index[channel]);
		अवरोध;
	हाल hwmon_temp_min_alarm:
		*val = (data->alarms >> lm90_min_alarm_bits[channel]) & 1;
		अवरोध;
	हाल hwmon_temp_max_alarm:
		*val = (data->alarms >> lm90_max_alarm_bits[channel]) & 1;
		अवरोध;
	हाल hwmon_temp_crit_alarm:
		*val = (data->alarms >> lm90_crit_alarm_bits[channel]) & 1;
		अवरोध;
	हाल hwmon_temp_emergency_alarm:
		*val = (data->alarms >> lm90_emergency_alarm_bits[channel]) & 1;
		अवरोध;
	हाल hwmon_temp_fault:
		*val = (data->alarms >> lm90_fault_bits[channel]) & 1;
		अवरोध;
	हाल hwmon_temp_min:
		अगर (channel == 0)
			*val = lm90_get_temp8(data,
					      lm90_temp_min_index[channel]);
		अन्यथा
			*val = lm90_get_temp11(data,
					       lm90_temp_min_index[channel]);
		अवरोध;
	हाल hwmon_temp_max:
		अगर (channel == 0)
			*val = lm90_get_temp8(data,
					      lm90_temp_max_index[channel]);
		अन्यथा
			*val = lm90_get_temp11(data,
					       lm90_temp_max_index[channel]);
		अवरोध;
	हाल hwmon_temp_crit:
		*val = lm90_get_temp8(data, lm90_temp_crit_index[channel]);
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		*val = lm90_get_temphyst(data, lm90_temp_crit_index[channel]);
		अवरोध;
	हाल hwmon_temp_emergency:
		*val = lm90_get_temp8(data, lm90_temp_emerg_index[channel]);
		अवरोध;
	हाल hwmon_temp_emergency_hyst:
		*val = lm90_get_temphyst(data, lm90_temp_emerg_index[channel]);
		अवरोध;
	हाल hwmon_temp_offset:
		*val = lm90_get_temp11(data, REMOTE_OFFSET);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lm90_temp_ग_लिखो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा lm90_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	mutex_lock(&data->update_lock);

	err = lm90_update_device(dev);
	अगर (err)
		जाओ error;

	चयन (attr) अणु
	हाल hwmon_temp_min:
		अगर (channel == 0)
			err = lm90_set_temp8(data,
					      lm90_temp_min_index[channel],
					      val);
		अन्यथा
			err = lm90_set_temp11(data,
					      lm90_temp_min_index[channel],
					      val);
		अवरोध;
	हाल hwmon_temp_max:
		अगर (channel == 0)
			err = lm90_set_temp8(data,
					     lm90_temp_max_index[channel],
					     val);
		अन्यथा
			err = lm90_set_temp11(data,
					      lm90_temp_max_index[channel],
					      val);
		अवरोध;
	हाल hwmon_temp_crit:
		err = lm90_set_temp8(data, lm90_temp_crit_index[channel], val);
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		err = lm90_set_temphyst(data, val);
		अवरोध;
	हाल hwmon_temp_emergency:
		err = lm90_set_temp8(data, lm90_temp_emerg_index[channel], val);
		अवरोध;
	हाल hwmon_temp_offset:
		err = lm90_set_temp11(data, REMOTE_OFFSET, val);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
error:
	mutex_unlock(&data->update_lock);

	वापस err;
पूर्ण

अटल umode_t lm90_temp_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_min_alarm:
	हाल hwmon_temp_max_alarm:
	हाल hwmon_temp_crit_alarm:
	हाल hwmon_temp_emergency_alarm:
	हाल hwmon_temp_emergency_hyst:
	हाल hwmon_temp_fault:
		वापस 0444;
	हाल hwmon_temp_min:
	हाल hwmon_temp_max:
	हाल hwmon_temp_crit:
	हाल hwmon_temp_emergency:
	हाल hwmon_temp_offset:
		वापस 0644;
	हाल hwmon_temp_crit_hyst:
		अगर (channel == 0)
			वापस 0644;
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक lm90_chip_पढ़ो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा lm90_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	mutex_lock(&data->update_lock);
	err = lm90_update_device(dev);
	mutex_unlock(&data->update_lock);
	अगर (err)
		वापस err;

	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		*val = data->update_पूर्णांकerval;
		अवरोध;
	हाल hwmon_chip_alarms:
		*val = data->alarms;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm90_chip_ग_लिखो(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा lm90_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक err;

	mutex_lock(&data->update_lock);

	err = lm90_update_device(dev);
	अगर (err)
		जाओ error;

	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		err = lm90_set_convrate(client, data,
					clamp_val(val, 0, 100000));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
error:
	mutex_unlock(&data->update_lock);

	वापस err;
पूर्ण

अटल umode_t lm90_chip_is_visible(स्थिर व्योम *data, u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		वापस 0644;
	हाल hwmon_chip_alarms:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक lm90_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		     u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm90_chip_पढ़ो(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस lm90_temp_पढ़ो(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक lm90_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		      u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm90_chip_ग_लिखो(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस lm90_temp_ग_लिखो(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t lm90_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm90_chip_is_visible(data, attr, channel);
	हाल hwmon_temp:
		वापस lm90_temp_is_visible(data, attr, channel);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm90_detect(काष्ठा i2c_client *client,
		       काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक address = client->addr;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक man_id, chip_id, config1, config2, convrate;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	/* detection and identअगरication */
	man_id = i2c_smbus_पढ़ो_byte_data(client, LM90_REG_R_MAN_ID);
	chip_id = i2c_smbus_पढ़ो_byte_data(client, LM90_REG_R_CHIP_ID);
	config1 = i2c_smbus_पढ़ो_byte_data(client, LM90_REG_R_CONFIG1);
	convrate = i2c_smbus_पढ़ो_byte_data(client, LM90_REG_R_CONVRATE);
	अगर (man_id < 0 || chip_id < 0 || config1 < 0 || convrate < 0)
		वापस -ENODEV;

	अगर (man_id == 0x01 || man_id == 0x5C || man_id == 0x41) अणु
		config2 = i2c_smbus_पढ़ो_byte_data(client, LM90_REG_R_CONFIG2);
		अगर (config2 < 0)
			वापस -ENODEV;
	पूर्ण अन्यथा
		config2 = 0;		/* Make compiler happy */

	अगर ((address == 0x4C || address == 0x4D)
	 && man_id == 0x01) अणु /* National Semiconductor */
		अगर ((config1 & 0x2A) == 0x00
		 && (config2 & 0xF8) == 0x00
		 && convrate <= 0x09) अणु
			अगर (address == 0x4C
			 && (chip_id & 0xF0) == 0x20) अणु /* LM90 */
				name = "lm90";
			पूर्ण अन्यथा
			अगर ((chip_id & 0xF0) == 0x30) अणु /* LM89/LM99 */
				name = "lm99";
				dev_info(&adapter->dev,
					 "Assuming LM99 chip at 0x%02x\n",
					 address);
				dev_info(&adapter->dev,
					 "If it is an LM89, instantiate it "
					 "with the new_device sysfs "
					 "interface\n");
			पूर्ण अन्यथा
			अगर (address == 0x4C
			 && (chip_id & 0xF0) == 0x10) अणु /* LM86 */
				name = "lm86";
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
	अगर ((address == 0x4C || address == 0x4D)
	 && man_id == 0x41) अणु /* Analog Devices */
		अगर ((chip_id & 0xF0) == 0x40 /* ADM1032 */
		 && (config1 & 0x3F) == 0x00
		 && convrate <= 0x0A) अणु
			name = "adm1032";
			/*
			 * The ADM1032 supports PEC, but only अगर combined
			 * transactions are not used.
			 */
			अगर (i2c_check_functionality(adapter,
						    I2C_FUNC_SMBUS_BYTE))
				info->flags |= I2C_CLIENT_PEC;
		पूर्ण अन्यथा
		अगर (chip_id == 0x51 /* ADT7461 */
		 && (config1 & 0x1B) == 0x00
		 && convrate <= 0x0A) अणु
			name = "adt7461";
		पूर्ण अन्यथा
		अगर (chip_id == 0x57 /* ADT7461A, NCT1008 */
		 && (config1 & 0x1B) == 0x00
		 && convrate <= 0x0A) अणु
			name = "adt7461a";
		पूर्ण
	पूर्ण अन्यथा
	अगर (man_id == 0x4D) अणु /* Maxim */
		पूर्णांक emerg, emerg2, status2;

		/*
		 * We पढ़ो MAX6659_REG_R_REMOTE_EMERG twice, and re-पढ़ो
		 * LM90_REG_R_MAN_ID in between. If MAX6659_REG_R_REMOTE_EMERG
		 * exists, both पढ़ोings will reflect the same value. Otherwise,
		 * the पढ़ोings will be dअगरferent.
		 */
		emerg = i2c_smbus_पढ़ो_byte_data(client,
						 MAX6659_REG_R_REMOTE_EMERG);
		man_id = i2c_smbus_पढ़ो_byte_data(client,
						  LM90_REG_R_MAN_ID);
		emerg2 = i2c_smbus_पढ़ो_byte_data(client,
						  MAX6659_REG_R_REMOTE_EMERG);
		status2 = i2c_smbus_पढ़ो_byte_data(client,
						   MAX6696_REG_R_STATUS2);
		अगर (emerg < 0 || man_id < 0 || emerg2 < 0 || status2 < 0)
			वापस -ENODEV;

		/*
		 * The MAX6657, MAX6658 and MAX6659 करो NOT have a chip_id
		 * रेजिस्टर. Reading from that address will वापस the last
		 * पढ़ो value, which in our हाल is those of the man_id
		 * रेजिस्टर. Likewise, the config1 रेजिस्टर seems to lack a
		 * low nibble, so the value will be those of the previous
		 * पढ़ो, so in our हाल those of the man_id रेजिस्टर.
		 * MAX6659 has a third set of upper temperature limit रेजिस्टरs.
		 * Those रेजिस्टरs also वापस values on MAX6657 and MAX6658,
		 * thus the only way to detect MAX6659 is by its address.
		 * For this reason it will be mis-detected as MAX6657 अगर its
		 * address is 0x4C.
		 */
		अगर (chip_id == man_id
		 && (address == 0x4C || address == 0x4D || address == 0x4E)
		 && (config1 & 0x1F) == (man_id & 0x0F)
		 && convrate <= 0x09) अणु
			अगर (address == 0x4C)
				name = "max6657";
			अन्यथा
				name = "max6659";
		पूर्ण अन्यथा
		/*
		 * Even though MAX6695 and MAX6696 करो not have a chip ID
		 * रेजिस्टर, पढ़ोing it वापसs 0x01. Bit 4 of the config1
		 * रेजिस्टर is unused and should वापस zero when पढ़ो. Bit 0 of
		 * the status2 रेजिस्टर is unused and should वापस zero when
		 * पढ़ो.
		 *
		 * MAX6695 and MAX6696 have an additional set of temperature
		 * limit रेजिस्टरs. We can detect those chips by checking अगर
		 * one of those रेजिस्टरs exists.
		 */
		अगर (chip_id == 0x01
		 && (config1 & 0x10) == 0x00
		 && (status2 & 0x01) == 0x00
		 && emerg == emerg2
		 && convrate <= 0x07) अणु
			name = "max6696";
		पूर्ण अन्यथा
		/*
		 * The chip_id रेजिस्टर of the MAX6680 and MAX6681 holds the
		 * revision of the chip. The lowest bit of the config1 रेजिस्टर
		 * is unused and should वापस zero when पढ़ो, so should the
		 * second to last bit of config1 (software reset).
		 */
		अगर (chip_id == 0x01
		 && (config1 & 0x03) == 0x00
		 && convrate <= 0x07) अणु
			name = "max6680";
		पूर्ण अन्यथा
		/*
		 * The chip_id रेजिस्टर of the MAX6646/6647/6649 holds the
		 * revision of the chip. The lowest 6 bits of the config1
		 * रेजिस्टर are unused and should वापस zero when पढ़ो.
		 */
		अगर (chip_id == 0x59
		 && (config1 & 0x3f) == 0x00
		 && convrate <= 0x07) अणु
			name = "max6646";
		पूर्ण अन्यथा
		/*
		 * The chip_id of the MAX6654 holds the revision of the chip.
		 * The lowest 3 bits of the config1 रेजिस्टर are unused and
		 * should वापस zero when पढ़ो.
		 */
		अगर (chip_id == 0x08
		 && (config1 & 0x07) == 0x00
		 && convrate <= 0x07) अणु
			name = "max6654";
		पूर्ण
	पूर्ण अन्यथा
	अगर (address == 0x4C
	 && man_id == 0x5C) अणु /* Winbond/Nuvoton */
		अगर ((config1 & 0x2A) == 0x00
		 && (config2 & 0xF8) == 0x00) अणु
			अगर (chip_id == 0x01 /* W83L771W/G */
			 && convrate <= 0x09) अणु
				name = "w83l771";
			पूर्ण अन्यथा
			अगर ((chip_id & 0xFE) == 0x10 /* W83L771AWG/ASG */
			 && convrate <= 0x08) अणु
				name = "w83l771";
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
	अगर (address >= 0x48 && address <= 0x4F
	 && man_id == 0xA1) अणु /*  NXP Semiconductor/Philips */
		अगर (chip_id == 0x00
		 && (config1 & 0x2A) == 0x00
		 && (config2 & 0xFE) == 0x00
		 && convrate <= 0x09) अणु
			name = "sa56004";
		पूर्ण
	पूर्ण अन्यथा
	अगर ((address == 0x4C || address == 0x4D)
	 && man_id == 0x47) अणु /* GMT */
		अगर (chip_id == 0x01 /* G781 */
		 && (config1 & 0x3F) == 0x00
		 && convrate <= 0x08)
			name = "g781";
	पूर्ण अन्यथा
	अगर (address == 0x4C
	 && man_id == 0x55) अणु /* Texas Instruments */
		पूर्णांक local_ext;

		local_ext = i2c_smbus_पढ़ो_byte_data(client,
						     TMP451_REG_R_LOCAL_TEMPL);

		अगर (chip_id == 0x00 /* TMP451 */
		 && (config1 & 0x1B) == 0x00
		 && convrate <= 0x09
		 && (local_ext & 0x0F) == 0x00)
			name = "tmp451";
	पूर्ण

	अगर (!name) अणु /* identअगरication failed */
		dev_dbg(&adapter->dev,
			"Unsupported chip at 0x%02x (man_id=0x%02X, "
			"chip_id=0x%02X)\n", address, man_id, chip_id);
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम lm90_restore_conf(व्योम *_data)
अणु
	काष्ठा lm90_data *data = _data;
	काष्ठा i2c_client *client = data->client;

	/* Restore initial configuration */
	lm90_ग_लिखो_convrate(data, data->convrate_orig);
	i2c_smbus_ग_लिखो_byte_data(client, LM90_REG_W_CONFIG1,
				  data->config_orig);
पूर्ण

अटल पूर्णांक lm90_init_client(काष्ठा i2c_client *client, काष्ठा lm90_data *data)
अणु
	पूर्णांक config, convrate;

	convrate = lm90_पढ़ो_reg(client, LM90_REG_R_CONVRATE);
	अगर (convrate < 0)
		वापस convrate;
	data->convrate_orig = convrate;

	/*
	 * Start the conversions.
	 */
	config = lm90_पढ़ो_reg(client, LM90_REG_R_CONFIG1);
	अगर (config < 0)
		वापस config;
	data->config_orig = config;
	data->config = config;

	lm90_set_convrate(client, data, 500); /* 500ms; 2Hz conversion rate */

	/* Check Temperature Range Select */
	अगर (data->kind == adt7461 || data->kind == पंचांगp451) अणु
		अगर (config & 0x04)
			data->flags |= LM90_FLAG_ADT7461_EXT;
	पूर्ण

	/*
	 * Put MAX6680/MAX8881 पूर्णांकo extended resolution (bit 0x10,
	 * 0.125 degree resolution) and range (0x08, extend range
	 * to -64 degree) mode क्रम the remote temperature sensor.
	 */
	अगर (data->kind == max6680)
		config |= 0x18;

	/*
	 * Put MAX6654 पूर्णांकo extended range (0x20, extend minimum range from
	 * 0 degrees to -64 degrees). Note that extended resolution is not
	 * possible on the MAX6654 unless conversion rate is set to 1 Hz or
	 * slower, which is पूर्णांकentionally not करोne by शेष.
	 */
	अगर (data->kind == max6654)
		config |= 0x20;

	/*
	 * Select बाह्यal channel 0 क्रम max6695/96
	 */
	अगर (data->kind == max6696)
		config &= ~0x08;

	config &= 0xBF;	/* run */
	lm90_update_confreg(data, config);

	वापस devm_add_action_or_reset(&client->dev, lm90_restore_conf, data);
पूर्ण

अटल bool lm90_is_tripped(काष्ठा i2c_client *client, u16 *status)
अणु
	काष्ठा lm90_data *data = i2c_get_clientdata(client);
	पूर्णांक st, st2 = 0;

	st = lm90_पढ़ो_reg(client, LM90_REG_R_STATUS);
	अगर (st < 0)
		वापस false;

	अगर (data->kind == max6696) अणु
		st2 = lm90_पढ़ो_reg(client, MAX6696_REG_R_STATUS2);
		अगर (st2 < 0)
			वापस false;
	पूर्ण

	*status = st | (st2 << 8);

	अगर ((st & 0x7f) == 0 && (st2 & 0xfe) == 0)
		वापस false;

	अगर ((st & (LM90_STATUS_LLOW | LM90_STATUS_LHIGH | LM90_STATUS_LTHRM)) ||
	    (st2 & MAX6696_STATUS2_LOT2))
		dev_warn(&client->dev,
			 "temp%d out of range, please check!\n", 1);
	अगर ((st & (LM90_STATUS_RLOW | LM90_STATUS_RHIGH | LM90_STATUS_RTHRM)) ||
	    (st2 & MAX6696_STATUS2_ROT2))
		dev_warn(&client->dev,
			 "temp%d out of range, please check!\n", 2);
	अगर (st & LM90_STATUS_ROPEN)
		dev_warn(&client->dev,
			 "temp%d diode open, please check!\n", 2);
	अगर (st2 & (MAX6696_STATUS2_R2LOW | MAX6696_STATUS2_R2HIGH |
		   MAX6696_STATUS2_R2THRM | MAX6696_STATUS2_R2OT2))
		dev_warn(&client->dev,
			 "temp%d out of range, please check!\n", 3);
	अगर (st2 & MAX6696_STATUS2_R2OPEN)
		dev_warn(&client->dev,
			 "temp%d diode open, please check!\n", 3);

	वापस true;
पूर्ण

अटल irqवापस_t lm90_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *client = dev_id;
	u16 status;

	अगर (lm90_is_tripped(client, &status))
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल व्योम lm90_हटाओ_pec(व्योम *dev)
अणु
	device_हटाओ_file(dev, &dev_attr_pec);
पूर्ण

अटल व्योम lm90_regulator_disable(व्योम *regulator)
अणु
	regulator_disable(regulator);
पूर्ण


अटल स्थिर काष्ठा hwmon_ops lm90_ops = अणु
	.is_visible = lm90_is_visible,
	.पढ़ो = lm90_पढ़ो,
	.ग_लिखो = lm90_ग_लिखो,
पूर्ण;

अटल पूर्णांक lm90_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा hwmon_channel_info *info;
	काष्ठा regulator *regulator;
	काष्ठा device *hwmon_dev;
	काष्ठा lm90_data *data;
	पूर्णांक err;

	regulator = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(regulator))
		वापस PTR_ERR(regulator);

	err = regulator_enable(regulator);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to enable regulator: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(dev, lm90_regulator_disable, regulator);
	अगर (err)
		वापस err;

	data = devm_kzalloc(dev, माप(काष्ठा lm90_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Set the device type */
	अगर (client->dev.of_node)
		data->kind = (क्रमागत chips)of_device_get_match_data(&client->dev);
	अन्यथा
		data->kind = i2c_match_id(lm90_id, client)->driver_data;
	अगर (data->kind == adm1032) अणु
		अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
			client->flags &= ~I2C_CLIENT_PEC;
	पूर्ण

	/*
	 * Dअगरferent devices have dअगरferent alarm bits triggering the
	 * ALERT# output
	 */
	data->alert_alarms = lm90_params[data->kind].alert_alarms;

	/* Set chip capabilities */
	data->flags = lm90_params[data->kind].flags;

	data->chip.ops = &lm90_ops;
	data->chip.info = data->info;

	data->info[0] = HWMON_CHANNEL_INFO(chip,
		HWMON_C_REGISTER_TZ | HWMON_C_UPDATE_INTERVAL | HWMON_C_ALARMS);
	data->info[1] = &data->temp_info;

	info = &data->temp_info;
	info->type = hwmon_temp;
	info->config = data->channel_config;

	data->channel_config[0] = HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
		HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_MIN_ALARM |
		HWMON_T_MAX_ALARM | HWMON_T_CRIT_ALARM;
	data->channel_config[1] = HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
		HWMON_T_CRIT | HWMON_T_CRIT_HYST | HWMON_T_MIN_ALARM |
		HWMON_T_MAX_ALARM | HWMON_T_CRIT_ALARM | HWMON_T_FAULT;

	अगर (data->flags & LM90_HAVE_OFFSET)
		data->channel_config[1] |= HWMON_T_OFFSET;

	अगर (data->flags & LM90_HAVE_EMERGENCY) अणु
		data->channel_config[0] |= HWMON_T_EMERGENCY |
			HWMON_T_EMERGENCY_HYST;
		data->channel_config[1] |= HWMON_T_EMERGENCY |
			HWMON_T_EMERGENCY_HYST;
	पूर्ण

	अगर (data->flags & LM90_HAVE_EMERGENCY_ALARM) अणु
		data->channel_config[0] |= HWMON_T_EMERGENCY_ALARM;
		data->channel_config[1] |= HWMON_T_EMERGENCY_ALARM;
	पूर्ण

	अगर (data->flags & LM90_HAVE_TEMP3) अणु
		data->channel_config[2] = HWMON_T_INPUT |
			HWMON_T_MIN | HWMON_T_MAX |
			HWMON_T_CRIT | HWMON_T_CRIT_HYST |
			HWMON_T_EMERGENCY | HWMON_T_EMERGENCY_HYST |
			HWMON_T_MIN_ALARM | HWMON_T_MAX_ALARM |
			HWMON_T_CRIT_ALARM | HWMON_T_EMERGENCY_ALARM |
			HWMON_T_FAULT;
	पूर्ण

	data->reg_local_ext = lm90_params[data->kind].reg_local_ext;

	/* Set maximum conversion rate */
	data->max_convrate = lm90_params[data->kind].max_convrate;

	/* Initialize the LM90 chip */
	err = lm90_init_client(client, data);
	अगर (err < 0) अणु
		dev_err(dev, "Failed to initialize device\n");
		वापस err;
	पूर्ण

	/*
	 * The 'pec' attribute is attached to the i2c device and thus created
	 * separately.
	 */
	अगर (client->flags & I2C_CLIENT_PEC) अणु
		err = device_create_file(dev, &dev_attr_pec);
		अगर (err)
			वापस err;
		err = devm_add_action_or_reset(dev, lm90_हटाओ_pec, dev);
		अगर (err)
			वापस err;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data, &data->chip,
							 शून्य);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	अगर (client->irq) अणु
		dev_dbg(dev, "IRQ: %d\n", client->irq);
		err = devm_request_thपढ़ोed_irq(dev, client->irq,
						शून्य, lm90_irq_thपढ़ो,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"lm90", client);
		अगर (err < 0) अणु
			dev_err(dev, "cannot request IRQ %d\n", client->irq);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lm90_alert(काष्ठा i2c_client *client, क्रमागत i2c_alert_protocol type,
		       अचिन्हित पूर्णांक flag)
अणु
	u16 alarms;

	अगर (type != I2C_PROTOCOL_SMBUS_ALERT)
		वापस;

	अगर (lm90_is_tripped(client, &alarms)) अणु
		/*
		 * Disable ALERT# output, because these chips करोn't implement
		 * SMBus alert correctly; they should only hold the alert line
		 * low briefly.
		 */
		काष्ठा lm90_data *data = i2c_get_clientdata(client);

		अगर ((data->flags & LM90_HAVE_BROKEN_ALERT) &&
		    (alarms & data->alert_alarms)) अणु
			dev_dbg(&client->dev, "Disabling ALERT#\n");
			lm90_update_confreg(data, data->config | 0x80);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&client->dev, "Everything OK\n");
	पूर्ण
पूर्ण

अटल काष्ठा i2c_driver lm90_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm90",
		.of_match_table = of_match_ptr(lm90_of_match),
	पूर्ण,
	.probe_new	= lm90_probe,
	.alert		= lm90_alert,
	.id_table	= lm90_id,
	.detect		= lm90_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm90_driver);

MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("LM90/ADM1032 driver");
MODULE_LICENSE("GPL");
