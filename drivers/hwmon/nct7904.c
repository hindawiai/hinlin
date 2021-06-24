<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * nct7904.c - driver क्रम Nuvoton NCT7904D.
 *
 * Copyright (c) 2015 Kontron
 * Author: Vadim V. Vlasov <vvlasov@dev.rtsoft.ru>
 *
 * Copyright (c) 2019 Advantech
 * Author: Amy.Shih <amy.shih@advantech.com.tw>
 *
 * Copyright (c) 2020 Advantech
 * Author: Yuechao Zhao <yuechao.zhao@advantech.com.cn>
 *
 * Supports the following chips:
 *
 * Chip        #vin  #fan  #pwm  #temp  #dts  chip ID
 * nct7904d     20    12    4     5      8    0xc5
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/watchकरोg.h>

#घोषणा VENDOR_ID_REG		0x7A	/* Any bank */
#घोषणा NUVOTON_ID		0x50
#घोषणा CHIP_ID_REG		0x7B	/* Any bank */
#घोषणा NCT7904_ID		0xC5
#घोषणा DEVICE_ID_REG		0x7C	/* Any bank */

#घोषणा BANK_SEL_REG		0xFF
#घोषणा BANK_0			0x00
#घोषणा BANK_1			0x01
#घोषणा BANK_2			0x02
#घोषणा BANK_3			0x03
#घोषणा BANK_4			0x04
#घोषणा BANK_MAX		0x04

#घोषणा FANIN_MAX		12	/* Counted from 1 */
#घोषणा VSEN_MAX		21	/* VSEN1..14, 3VDD, VBAT, V3VSB,
					   LTD (not a voltage), VSEN17..19 */
#घोषणा FANCTL_MAX		4	/* Counted from 1 */
#घोषणा TCPU_MAX		8	/* Counted from 1 */
#घोषणा TEMP_MAX		4	/* Counted from 1 */
#घोषणा SMI_STS_MAX		10	/* Counted from 1 */

#घोषणा VT_ADC_CTRL0_REG	0x20	/* Bank 0 */
#घोषणा VT_ADC_CTRL1_REG	0x21	/* Bank 0 */
#घोषणा VT_ADC_CTRL2_REG	0x22	/* Bank 0 */
#घोषणा FANIN_CTRL0_REG		0x24
#घोषणा FANIN_CTRL1_REG		0x25
#घोषणा DTS_T_CTRL0_REG		0x26
#घोषणा DTS_T_CTRL1_REG		0x27
#घोषणा VT_ADC_MD_REG		0x2E

#घोषणा VSEN1_HV_LL_REG		0x02	/* Bank 1; 2 regs (HV/LV) per sensor */
#घोषणा VSEN1_LV_LL_REG		0x03	/* Bank 1; 2 regs (HV/LV) per sensor */
#घोषणा VSEN1_HV_HL_REG		0x00	/* Bank 1; 2 regs (HV/LV) per sensor */
#घोषणा VSEN1_LV_HL_REG		0x01	/* Bank 1; 2 regs (HV/LV) per sensor */
#घोषणा SMI_STS1_REG		0xC1	/* Bank 0; SMI Status Register */
#घोषणा SMI_STS3_REG		0xC3	/* Bank 0; SMI Status Register */
#घोषणा SMI_STS5_REG		0xC5	/* Bank 0; SMI Status Register */
#घोषणा SMI_STS7_REG		0xC7	/* Bank 0; SMI Status Register */
#घोषणा SMI_STS8_REG		0xC8	/* Bank 0; SMI Status Register */

#घोषणा VSEN1_HV_REG		0x40	/* Bank 0; 2 regs (HV/LV) per sensor */
#घोषणा TEMP_CH1_HV_REG		0x42	/* Bank 0; same as VSEN2_HV */
#घोषणा LTD_HV_REG		0x62	/* Bank 0; 2 regs in VSEN range */
#घोषणा LTD_HV_HL_REG		0x44	/* Bank 1; 1 reg क्रम LTD */
#घोषणा LTD_LV_HL_REG		0x45	/* Bank 1; 1 reg क्रम LTD */
#घोषणा LTD_HV_LL_REG		0x46	/* Bank 1; 1 reg क्रम LTD */
#घोषणा LTD_LV_LL_REG		0x47	/* Bank 1; 1 reg क्रम LTD */
#घोषणा TEMP_CH1_CH_REG		0x05	/* Bank 1; 1 reg क्रम LTD */
#घोषणा TEMP_CH1_W_REG		0x06	/* Bank 1; 1 reg क्रम LTD */
#घोषणा TEMP_CH1_WH_REG		0x07	/* Bank 1; 1 reg क्रम LTD */
#घोषणा TEMP_CH1_C_REG		0x04	/* Bank 1; 1 reg per sensor */
#घोषणा DTS_T_CPU1_C_REG	0x90	/* Bank 1; 1 reg per sensor */
#घोषणा DTS_T_CPU1_CH_REG	0x91	/* Bank 1; 1 reg per sensor */
#घोषणा DTS_T_CPU1_W_REG	0x92	/* Bank 1; 1 reg per sensor */
#घोषणा DTS_T_CPU1_WH_REG	0x93	/* Bank 1; 1 reg per sensor */
#घोषणा FANIN1_HV_REG		0x80	/* Bank 0; 2 regs (HV/LV) per sensor */
#घोषणा FANIN1_HV_HL_REG	0x60	/* Bank 1; 2 regs (HV/LV) per sensor */
#घोषणा FANIN1_LV_HL_REG	0x61	/* Bank 1; 2 regs (HV/LV) per sensor */
#घोषणा T_CPU1_HV_REG		0xA0	/* Bank 0; 2 regs (HV/LV) per sensor */

#घोषणा PRTS_REG		0x03	/* Bank 2 */
#घोषणा PFE_REG			0x00	/* Bank 2; PECI Function Enable */
#घोषणा TSI_CTRL_REG		0x50	/* Bank 2; TSI Control Register */
#घोषणा FANCTL1_FMR_REG		0x00	/* Bank 3; 1 reg per channel */
#घोषणा FANCTL1_OUT_REG		0x10	/* Bank 3; 1 reg per channel */

#घोषणा WDT_LOCK_REG		0xE0	/* W/O Lock Watchकरोg Register */
#घोषणा WDT_EN_REG		0xE1	/* R/O Watchकरोg Enable Register */
#घोषणा WDT_STS_REG		0xE2	/* R/O Watchकरोg Status Register */
#घोषणा WDT_TIMER_REG		0xE3	/* R/W Watchकरोg Timer Register */
#घोषणा WDT_SOFT_EN		0x55	/* Enable soft watchकरोg समयr */
#घोषणा WDT_SOFT_DIS		0xAA	/* Disable soft watchकरोg समयr */

#घोषणा VOLT_MONITOR_MODE	0x0
#घोषणा THERMAL_DIODE_MODE	0x1
#घोषणा THERMISTOR_MODE		0x3

#घोषणा ENABLE_TSI	BIT(1)

#घोषणा WATCHDOG_TIMEOUT	1	/* 1 minute शेष समयout */

/*The समयout range is 1-255 minutes*/
#घोषणा MIN_TIMEOUT		(1 * 60)
#घोषणा MAX_TIMEOUT		(255 * 60)

अटल पूर्णांक समयout;
module_param(समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "Watchdog timeout in minutes. 1 <= timeout <= 255, default="
			__MODULE_STRING(WATCHDOG_TIMEOUT) ".");

अटल bool nowayout = WATCHDOG_NOWAYOUT;
module_param(nowayout, bool, 0);
MODULE_PARM_DESC(nowayout, "Watchdog cannot be stopped once started (default="
			__MODULE_STRING(WATCHDOG_NOWAYOUT) ")");

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु
	0x2d, 0x2e, I2C_CLIENT_END
पूर्ण;

काष्ठा nct7904_data अणु
	काष्ठा i2c_client *client;
	काष्ठा watchकरोg_device wdt;
	काष्ठा mutex bank_lock;
	पूर्णांक bank_sel;
	u32 fanin_mask;
	u32 vsen_mask;
	u32 tcpu_mask;
	u8 fan_mode[FANCTL_MAX];
	u8 enable_dts;
	u8 has_dts;
	u8 temp_mode; /* 0: TR mode, 1: TD mode */
	u8 fan_alarm[2];
	u8 vsen_alarm[3];
पूर्ण;

/* Access functions */
अटल पूर्णांक nct7904_bank_lock(काष्ठा nct7904_data *data, अचिन्हित पूर्णांक bank)
अणु
	पूर्णांक ret;

	mutex_lock(&data->bank_lock);
	अगर (data->bank_sel == bank)
		वापस 0;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, BANK_SEL_REG, bank);
	अगर (ret == 0)
		data->bank_sel = bank;
	अन्यथा
		data->bank_sel = -1;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम nct7904_bank_release(काष्ठा nct7904_data *data)
अणु
	mutex_unlock(&data->bank_lock);
पूर्ण

/* Read 1-byte रेजिस्टर. Returns अचिन्हित reg or -ERRNO on error. */
अटल पूर्णांक nct7904_पढ़ो_reg(काष्ठा nct7904_data *data,
			    अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = nct7904_bank_lock(data, bank);
	अगर (ret == 0)
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);

	nct7904_bank_release(data);
	वापस ret;
पूर्ण

/*
 * Read 2-byte रेजिस्टर. Returns रेजिस्टर in big-endian क्रमmat or
 * -ERRNO on error.
 */
अटल पूर्णांक nct7904_पढ़ो_reg16(काष्ठा nct7904_data *data,
			      अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret, hi;

	ret = nct7904_bank_lock(data, bank);
	अगर (ret == 0) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		अगर (ret >= 0) अणु
			hi = ret;
			ret = i2c_smbus_पढ़ो_byte_data(client, reg + 1);
			अगर (ret >= 0)
				ret |= hi << 8;
		पूर्ण
	पूर्ण

	nct7904_bank_release(data);
	वापस ret;
पूर्ण

/* Write 1-byte रेजिस्टर. Returns 0 or -ERRNO on error. */
अटल पूर्णांक nct7904_ग_लिखो_reg(काष्ठा nct7904_data *data,
			     अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक reg, u8 val)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = nct7904_bank_lock(data, bank);
	अगर (ret == 0)
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);

	nct7904_bank_release(data);
	वापस ret;
पूर्ण

अटल पूर्णांक nct7904_पढ़ो_fan(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			    दीर्घ *val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक cnt, rpm;
	पूर्णांक ret;

	चयन (attr) अणु
	हाल hwmon_fan_input:
		ret = nct7904_पढ़ो_reg16(data, BANK_0,
					 FANIN1_HV_REG + channel * 2);
		अगर (ret < 0)
			वापस ret;
		cnt = ((ret & 0xff00) >> 3) | (ret & 0x1f);
		अगर (cnt == 0 || cnt == 0x1fff)
			rpm = 0;
		अन्यथा
			rpm = 1350000 / cnt;
		*val = rpm;
		वापस 0;
	हाल hwmon_fan_min:
		ret = nct7904_पढ़ो_reg16(data, BANK_1,
					 FANIN1_HV_HL_REG + channel * 2);
		अगर (ret < 0)
			वापस ret;
		cnt = ((ret & 0xff00) >> 3) | (ret & 0x1f);
		अगर (cnt == 0 || cnt == 0x1fff)
			rpm = 0;
		अन्यथा
			rpm = 1350000 / cnt;
		*val = rpm;
		वापस 0;
	हाल hwmon_fan_alarm:
		ret = nct7904_पढ़ो_reg(data, BANK_0,
				       SMI_STS5_REG + (channel >> 3));
		अगर (ret < 0)
			वापस ret;
		अगर (!data->fan_alarm[channel >> 3])
			data->fan_alarm[channel >> 3] = ret & 0xff;
		अन्यथा
			/* If there is new alarm showing up */
			data->fan_alarm[channel >> 3] |= (ret & 0xff);
		*val = (data->fan_alarm[channel >> 3] >> (channel & 0x07)) & 1;
		/* Needs to clean the alarm अगर alarm existing */
		अगर (*val)
			data->fan_alarm[channel >> 3] ^= 1 << (channel & 0x07);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t nct7904_fan_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा nct7904_data *data = _data;

	चयन (attr) अणु
	हाल hwmon_fan_input:
	हाल hwmon_fan_alarm:
		अगर (data->fanin_mask & (1 << channel))
			वापस 0444;
		अवरोध;
	हाल hwmon_fan_min:
		अगर (data->fanin_mask & (1 << channel))
			वापस 0644;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 nct7904_chan_to_index[] = अणु
	0,	/* Not used */
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	18, 19, 20, 16
पूर्ण;

अटल पूर्णांक nct7904_पढ़ो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			   दीर्घ *val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	पूर्णांक ret, volt, index;

	index = nct7904_chan_to_index[channel];

	चयन (attr) अणु
	हाल hwmon_in_input:
		ret = nct7904_पढ़ो_reg16(data, BANK_0,
					 VSEN1_HV_REG + index * 2);
		अगर (ret < 0)
			वापस ret;
		volt = ((ret & 0xff00) >> 5) | (ret & 0x7);
		अगर (index < 14)
			volt *= 2; /* 0.002V scale */
		अन्यथा
			volt *= 6; /* 0.006V scale */
		*val = volt;
		वापस 0;
	हाल hwmon_in_min:
		ret = nct7904_पढ़ो_reg16(data, BANK_1,
					 VSEN1_HV_LL_REG + index * 4);
		अगर (ret < 0)
			वापस ret;
		volt = ((ret & 0xff00) >> 5) | (ret & 0x7);
		अगर (index < 14)
			volt *= 2; /* 0.002V scale */
		अन्यथा
			volt *= 6; /* 0.006V scale */
		*val = volt;
		वापस 0;
	हाल hwmon_in_max:
		ret = nct7904_पढ़ो_reg16(data, BANK_1,
					 VSEN1_HV_HL_REG + index * 4);
		अगर (ret < 0)
			वापस ret;
		volt = ((ret & 0xff00) >> 5) | (ret & 0x7);
		अगर (index < 14)
			volt *= 2; /* 0.002V scale */
		अन्यथा
			volt *= 6; /* 0.006V scale */
		*val = volt;
		वापस 0;
	हाल hwmon_in_alarm:
		ret = nct7904_पढ़ो_reg(data, BANK_0,
				       SMI_STS1_REG + (index >> 3));
		अगर (ret < 0)
			वापस ret;
		अगर (!data->vsen_alarm[index >> 3])
			data->vsen_alarm[index >> 3] = ret & 0xff;
		अन्यथा
			/* If there is new alarm showing up */
			data->vsen_alarm[index >> 3] |= (ret & 0xff);
		*val = (data->vsen_alarm[index >> 3] >> (index & 0x07)) & 1;
		/* Needs to clean the alarm अगर alarm existing */
		अगर (*val)
			data->vsen_alarm[index >> 3] ^= 1 << (index & 0x07);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t nct7904_in_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा nct7904_data *data = _data;
	पूर्णांक index = nct7904_chan_to_index[channel];

	चयन (attr) अणु
	हाल hwmon_in_input:
	हाल hwmon_in_alarm:
		अगर (channel > 0 && (data->vsen_mask & BIT(index)))
			वापस 0444;
		अवरोध;
	हाल hwmon_in_min:
	हाल hwmon_in_max:
		अगर (channel > 0 && (data->vsen_mask & BIT(index)))
			वापस 0644;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nct7904_पढ़ो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	पूर्णांक ret, temp;
	अचिन्हित पूर्णांक reg1, reg2, reg3;
	s8 temps;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (channel == 4)
			ret = nct7904_पढ़ो_reg16(data, BANK_0, LTD_HV_REG);
		अन्यथा अगर (channel < 5)
			ret = nct7904_पढ़ो_reg16(data, BANK_0,
						 TEMP_CH1_HV_REG + channel * 4);
		अन्यथा
			ret = nct7904_पढ़ो_reg16(data, BANK_0,
						 T_CPU1_HV_REG + (channel - 5)
						 * 2);
		अगर (ret < 0)
			वापस ret;
		temp = ((ret & 0xff00) >> 5) | (ret & 0x7);
		*val = sign_extend32(temp, 10) * 125;
		वापस 0;
	हाल hwmon_temp_alarm:
		अगर (channel == 4) अणु
			ret = nct7904_पढ़ो_reg(data, BANK_0,
					       SMI_STS3_REG);
			अगर (ret < 0)
				वापस ret;
			*val = (ret >> 1) & 1;
		पूर्ण अन्यथा अगर (channel < 4) अणु
			ret = nct7904_पढ़ो_reg(data, BANK_0,
					       SMI_STS1_REG);
			अगर (ret < 0)
				वापस ret;
			*val = (ret >> (((channel * 2) + 1) & 0x07)) & 1;
		पूर्ण अन्यथा अणु
			अगर ((channel - 5) < 4) अणु
				ret = nct7904_पढ़ो_reg(data, BANK_0,
						       SMI_STS7_REG +
						       ((channel - 5) >> 3));
				अगर (ret < 0)
					वापस ret;
				*val = (ret >> ((channel - 5) & 0x07)) & 1;
			पूर्ण अन्यथा अणु
				ret = nct7904_पढ़ो_reg(data, BANK_0,
						       SMI_STS8_REG +
						       ((channel - 5) >> 3));
				अगर (ret < 0)
					वापस ret;
				*val = (ret >> (((channel - 5) & 0x07) - 4))
							& 1;
			पूर्ण
		पूर्ण
		वापस 0;
	हाल hwmon_temp_type:
		अगर (channel < 5) अणु
			अगर ((data->tcpu_mask >> channel) & 0x01) अणु
				अगर ((data->temp_mode >> channel) & 0x01)
					*val = 3; /* TD */
				अन्यथा
					*val = 4; /* TR */
			पूर्ण अन्यथा अणु
				*val = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((data->has_dts >> (channel - 5)) & 0x01) अणु
				अगर (data->enable_dts & ENABLE_TSI)
					*val = 5; /* TSI */
				अन्यथा
					*val = 6; /* PECI */
			पूर्ण अन्यथा अणु
				*val = 0;
			पूर्ण
		पूर्ण
		वापस 0;
	हाल hwmon_temp_max:
		reg1 = LTD_HV_LL_REG;
		reg2 = TEMP_CH1_W_REG;
		reg3 = DTS_T_CPU1_W_REG;
		अवरोध;
	हाल hwmon_temp_max_hyst:
		reg1 = LTD_LV_LL_REG;
		reg2 = TEMP_CH1_WH_REG;
		reg3 = DTS_T_CPU1_WH_REG;
		अवरोध;
	हाल hwmon_temp_crit:
		reg1 = LTD_HV_HL_REG;
		reg2 = TEMP_CH1_C_REG;
		reg3 = DTS_T_CPU1_C_REG;
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		reg1 = LTD_LV_HL_REG;
		reg2 = TEMP_CH1_CH_REG;
		reg3 = DTS_T_CPU1_CH_REG;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (channel == 4)
		ret = nct7904_पढ़ो_reg(data, BANK_1, reg1);
	अन्यथा अगर (channel < 5)
		ret = nct7904_पढ़ो_reg(data, BANK_1,
				       reg2 + channel * 8);
	अन्यथा
		ret = nct7904_पढ़ो_reg(data, BANK_1,
				       reg3 + (channel - 5) * 4);

	अगर (ret < 0)
		वापस ret;
	temps = ret;
	*val = temps * 1000;
	वापस 0;
पूर्ण

अटल umode_t nct7904_temp_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा nct7904_data *data = _data;

	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_alarm:
	हाल hwmon_temp_type:
		अगर (channel < 5) अणु
			अगर (data->tcpu_mask & BIT(channel))
				वापस 0444;
		पूर्ण अन्यथा अणु
			अगर (data->has_dts & BIT(channel - 5))
				वापस 0444;
		पूर्ण
		अवरोध;
	हाल hwmon_temp_max:
	हाल hwmon_temp_max_hyst:
	हाल hwmon_temp_crit:
	हाल hwmon_temp_crit_hyst:
		अगर (channel < 5) अणु
			अगर (data->tcpu_mask & BIT(channel))
				वापस 0644;
		पूर्ण अन्यथा अणु
			अगर (data->has_dts & BIT(channel - 5))
				वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nct7904_पढ़ो_pwm(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			    दीर्घ *val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		ret = nct7904_पढ़ो_reg(data, BANK_3, FANCTL1_OUT_REG + channel);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस 0;
	हाल hwmon_pwm_enable:
		ret = nct7904_पढ़ो_reg(data, BANK_3, FANCTL1_FMR_REG + channel);
		अगर (ret < 0)
			वापस ret;

		*val = ret ? 2 : 1;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nct7904_ग_लिखो_temp(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg1, reg2, reg3;

	val = clamp_val(val / 1000, -128, 127);

	चयन (attr) अणु
	हाल hwmon_temp_max:
		reg1 = LTD_HV_LL_REG;
		reg2 = TEMP_CH1_W_REG;
		reg3 = DTS_T_CPU1_W_REG;
		अवरोध;
	हाल hwmon_temp_max_hyst:
		reg1 = LTD_LV_LL_REG;
		reg2 = TEMP_CH1_WH_REG;
		reg3 = DTS_T_CPU1_WH_REG;
		अवरोध;
	हाल hwmon_temp_crit:
		reg1 = LTD_HV_HL_REG;
		reg2 = TEMP_CH1_C_REG;
		reg3 = DTS_T_CPU1_C_REG;
		अवरोध;
	हाल hwmon_temp_crit_hyst:
		reg1 = LTD_LV_HL_REG;
		reg2 = TEMP_CH1_CH_REG;
		reg3 = DTS_T_CPU1_CH_REG;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (channel == 4)
		ret = nct7904_ग_लिखो_reg(data, BANK_1, reg1, val);
	अन्यथा अगर (channel < 5)
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					reg2 + channel * 8, val);
	अन्यथा
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					reg3 + (channel - 5) * 4, val);

	वापस ret;
पूर्ण

अटल पूर्णांक nct7904_ग_लिखो_fan(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	u8 पंचांगp;

	चयन (attr) अणु
	हाल hwmon_fan_min:
		अगर (val <= 0)
			वापस -EINVAL;

		val = clamp_val(DIV_ROUND_CLOSEST(1350000, val), 1, 0x1fff);
		पंचांगp = (val >> 5) & 0xff;
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					FANIN1_HV_HL_REG + channel * 2, पंचांगp);
		अगर (ret < 0)
			वापस ret;
		पंचांगp = val & 0x1f;
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					FANIN1_LV_HL_REG + channel * 2, पंचांगp);
		वापस ret;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nct7904_ग_लिखो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			    दीर्घ val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	पूर्णांक ret, index, पंचांगp;

	index = nct7904_chan_to_index[channel];

	अगर (index < 14)
		val = val / 2; /* 0.002V scale */
	अन्यथा
		val = val / 6; /* 0.006V scale */

	val = clamp_val(val, 0, 0x7ff);

	चयन (attr) अणु
	हाल hwmon_in_min:
		पंचांगp = nct7904_पढ़ो_reg(data, BANK_1,
				       VSEN1_LV_LL_REG + index * 4);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		पंचांगp &= ~0x7;
		पंचांगp |= val & 0x7;
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					VSEN1_LV_LL_REG + index * 4, पंचांगp);
		अगर (ret < 0)
			वापस ret;
		पंचांगp = nct7904_पढ़ो_reg(data, BANK_1,
				       VSEN1_HV_LL_REG + index * 4);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		पंचांगp = (val >> 3) & 0xff;
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					VSEN1_HV_LL_REG + index * 4, पंचांगp);
		वापस ret;
	हाल hwmon_in_max:
		पंचांगp = nct7904_पढ़ो_reg(data, BANK_1,
				       VSEN1_LV_HL_REG + index * 4);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		पंचांगp &= ~0x7;
		पंचांगp |= val & 0x7;
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					VSEN1_LV_HL_REG + index * 4, पंचांगp);
		अगर (ret < 0)
			वापस ret;
		पंचांगp = nct7904_पढ़ो_reg(data, BANK_1,
				       VSEN1_HV_HL_REG + index * 4);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		पंचांगp = (val >> 3) & 0xff;
		ret = nct7904_ग_लिखो_reg(data, BANK_1,
					VSEN1_HV_HL_REG + index * 4, पंचांगp);
		वापस ret;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nct7904_ग_लिखो_pwm(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ val)
अणु
	काष्ठा nct7904_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	चयन (attr) अणु
	हाल hwmon_pwm_input:
		अगर (val < 0 || val > 255)
			वापस -EINVAL;
		ret = nct7904_ग_लिखो_reg(data, BANK_3, FANCTL1_OUT_REG + channel,
					val);
		वापस ret;
	हाल hwmon_pwm_enable:
		अगर (val < 1 || val > 2 ||
		    (val == 2 && !data->fan_mode[channel]))
			वापस -EINVAL;
		ret = nct7904_ग_लिखो_reg(data, BANK_3, FANCTL1_FMR_REG + channel,
					val == 2 ? data->fan_mode[channel] : 0);
		वापस ret;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t nct7904_pwm_is_visible(स्थिर व्योम *_data, u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_pwm_input:
	हाल hwmon_pwm_enable:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक nct7904_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस nct7904_पढ़ो_in(dev, attr, channel, val);
	हाल hwmon_fan:
		वापस nct7904_पढ़ो_fan(dev, attr, channel, val);
	हाल hwmon_pwm:
		वापस nct7904_पढ़ो_pwm(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस nct7904_पढ़ो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nct7904_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस nct7904_ग_लिखो_in(dev, attr, channel, val);
	हाल hwmon_fan:
		वापस nct7904_ग_लिखो_fan(dev, attr, channel, val);
	हाल hwmon_pwm:
		वापस nct7904_ग_लिखो_pwm(dev, attr, channel, val);
	हाल hwmon_temp:
		वापस nct7904_ग_लिखो_temp(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t nct7904_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		वापस nct7904_in_is_visible(data, attr, channel);
	हाल hwmon_fan:
		वापस nct7904_fan_is_visible(data, attr, channel);
	हाल hwmon_pwm:
		वापस nct7904_pwm_is_visible(data, attr, channel);
	हाल hwmon_temp:
		वापस nct7904_temp_is_visible(data, attr, channel);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक nct7904_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;

	अगर (!i2c_check_functionality(adapter,
				     I2C_FUNC_SMBUS_READ_BYTE |
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		वापस -ENODEV;

	/* Determine the chip type. */
	अगर (i2c_smbus_पढ़ो_byte_data(client, VENDOR_ID_REG) != NUVOTON_ID ||
	    i2c_smbus_पढ़ो_byte_data(client, CHIP_ID_REG) != NCT7904_ID ||
	    (i2c_smbus_पढ़ो_byte_data(client, DEVICE_ID_REG) & 0xf0) != 0x50 ||
	    (i2c_smbus_पढ़ो_byte_data(client, BANK_SEL_REG) & 0xf8) != 0x00)
		वापस -ENODEV;

	strlcpy(info->type, "nct7904", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *nct7904_info[] = अणु
	HWMON_CHANNEL_INFO(in,
			   /* dummy, skipped in is_visible */
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_ALARM),
	HWMON_CHANNEL_INFO(pwm,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE,
			   HWMON_PWM_INPUT | HWMON_PWM_ENABLE),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_ALARM | HWMON_T_MAX |
			   HWMON_T_MAX_HYST | HWMON_T_TYPE | HWMON_T_CRIT |
			   HWMON_T_CRIT_HYST),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops nct7904_hwmon_ops = अणु
	.is_visible = nct7904_is_visible,
	.पढ़ो = nct7904_पढ़ो,
	.ग_लिखो = nct7904_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info nct7904_chip_info = अणु
	.ops = &nct7904_hwmon_ops,
	.info = nct7904_info,
पूर्ण;

/*
 * Watchकरोg Function
 */
अटल पूर्णांक nct7904_wdt_start(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा nct7904_data *data = watchकरोg_get_drvdata(wdt);

	/* Enable soft watchकरोg समयr */
	वापस nct7904_ग_लिखो_reg(data, BANK_0, WDT_LOCK_REG, WDT_SOFT_EN);
पूर्ण

अटल पूर्णांक nct7904_wdt_stop(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा nct7904_data *data = watchकरोg_get_drvdata(wdt);

	वापस nct7904_ग_लिखो_reg(data, BANK_0, WDT_LOCK_REG, WDT_SOFT_DIS);
पूर्ण

अटल पूर्णांक nct7904_wdt_set_समयout(काष्ठा watchकरोg_device *wdt,
				   अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा nct7904_data *data = watchकरोg_get_drvdata(wdt);
	/*
	 * The NCT7904 is very special in watchकरोg function.
	 * Its minimum unit is minutes. And wdt->समयout needs
	 * to match the actual समयout selected. So, this needs
	 * to be: wdt->समयout = समयout / 60 * 60.
	 * For example, अगर the user configures a समयout of
	 * 119 seconds, the actual समयout will be 60 seconds.
	 * So, wdt->समयout must then be set to 60 seconds.
	 */
	wdt->समयout = समयout / 60 * 60;

	वापस nct7904_ग_लिखो_reg(data, BANK_0, WDT_TIMER_REG,
				 wdt->समयout / 60);
पूर्ण

अटल पूर्णांक nct7904_wdt_ping(काष्ठा watchकरोg_device *wdt)
अणु
	/*
	 * Note:
	 * NCT7904 करोes not support refreshing WDT_TIMER_REG रेजिस्टर when
	 * the watchकरोg is active. Please disable watchकरोg beक्रमe feeding
	 * the watchकरोg and enable it again.
	 */
	काष्ठा nct7904_data *data = watchकरोg_get_drvdata(wdt);
	पूर्णांक ret;

	/* Disable soft watchकरोg समयr */
	ret = nct7904_ग_लिखो_reg(data, BANK_0, WDT_LOCK_REG, WDT_SOFT_DIS);
	अगर (ret < 0)
		वापस ret;

	/* feed watchकरोg */
	ret = nct7904_ग_लिखो_reg(data, BANK_0, WDT_TIMER_REG, wdt->समयout / 60);
	अगर (ret < 0)
		वापस ret;

	/* Enable soft watchकरोg समयr */
	वापस nct7904_ग_लिखो_reg(data, BANK_0, WDT_LOCK_REG, WDT_SOFT_EN);
पूर्ण

अटल अचिन्हित पूर्णांक nct7904_wdt_get_समयleft(काष्ठा watchकरोg_device *wdt)
अणु
	काष्ठा nct7904_data *data = watchकरोg_get_drvdata(wdt);
	पूर्णांक ret;

	ret = nct7904_पढ़ो_reg(data, BANK_0, WDT_TIMER_REG);
	अगर (ret < 0)
		वापस 0;

	वापस ret * 60;
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info nct7904_wdt_info = अणु
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
				WDIOF_MAGICCLOSE,
	.identity	= "nct7904 watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops nct7904_wdt_ops = अणु
	.owner		= THIS_MODULE,
	.start		= nct7904_wdt_start,
	.stop		= nct7904_wdt_stop,
	.ping		= nct7904_wdt_ping,
	.set_समयout	= nct7904_wdt_set_समयout,
	.get_समयleft	= nct7904_wdt_get_समयleft,
पूर्ण;

अटल पूर्णांक nct7904_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा nct7904_data *data;
	काष्ठा device *hwmon_dev;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret, i;
	u32 mask;
	u8 val, bit;

	data = devm_kzalloc(dev, माप(काष्ठा nct7904_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->bank_lock);
	data->bank_sel = -1;

	/* Setup sensor groups. */
	/* FANIN attributes */
	ret = nct7904_पढ़ो_reg16(data, BANK_0, FANIN_CTRL0_REG);
	अगर (ret < 0)
		वापस ret;
	data->fanin_mask = (ret >> 8) | ((ret & 0xff) << 8);

	/*
	 * VSEN attributes
	 *
	 * Note: voltage sensors overlap with बाह्यal temperature
	 * sensors. So, अगर we ever decide to support the latter
	 * we will have to adjust 'vsen_mask' accordingly.
	 */
	mask = 0;
	ret = nct7904_पढ़ो_reg16(data, BANK_0, VT_ADC_CTRL0_REG);
	अगर (ret >= 0)
		mask = (ret >> 8) | ((ret & 0xff) << 8);
	ret = nct7904_पढ़ो_reg(data, BANK_0, VT_ADC_CTRL2_REG);
	अगर (ret >= 0)
		mask |= (ret << 16);
	data->vsen_mask = mask;

	/* CPU_TEMP attributes */
	ret = nct7904_पढ़ो_reg(data, BANK_0, VT_ADC_CTRL0_REG);
	अगर (ret < 0)
		वापस ret;

	अगर ((ret & 0x6) == 0x6)
		data->tcpu_mask |= 1; /* TR1 */
	अगर ((ret & 0x18) == 0x18)
		data->tcpu_mask |= 2; /* TR2 */
	अगर ((ret & 0x20) == 0x20)
		data->tcpu_mask |= 4; /* TR3 */
	अगर ((ret & 0x80) == 0x80)
		data->tcpu_mask |= 8; /* TR4 */

	/* LTD */
	ret = nct7904_पढ़ो_reg(data, BANK_0, VT_ADC_CTRL2_REG);
	अगर (ret < 0)
		वापस ret;
	अगर ((ret & 0x02) == 0x02)
		data->tcpu_mask |= 0x10;

	/* Multi-Function detecting क्रम Volt and TR/TD */
	ret = nct7904_पढ़ो_reg(data, BANK_0, VT_ADC_MD_REG);
	अगर (ret < 0)
		वापस ret;

	data->temp_mode = 0;
	क्रम (i = 0; i < 4; i++) अणु
		val = (ret >> (i * 2)) & 0x03;
		bit = (1 << i);
		अगर (val == VOLT_MONITOR_MODE) अणु
			data->tcpu_mask &= ~bit;
		पूर्ण अन्यथा अगर (val == THERMAL_DIODE_MODE && i < 2) अणु
			data->temp_mode |= bit;
			data->vsen_mask &= ~(0x06 << (i * 2));
		पूर्ण अन्यथा अगर (val == THERMISTOR_MODE) अणु
			data->vsen_mask &= ~(0x02 << (i * 2));
		पूर्ण अन्यथा अणु
			/* Reserved */
			data->tcpu_mask &= ~bit;
			data->vsen_mask &= ~(0x06 << (i * 2));
		पूर्ण
	पूर्ण

	/* PECI */
	ret = nct7904_पढ़ो_reg(data, BANK_2, PFE_REG);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & 0x80) अणु
		data->enable_dts = 1; /* Enable DTS & PECI */
	पूर्ण अन्यथा अणु
		ret = nct7904_पढ़ो_reg(data, BANK_2, TSI_CTRL_REG);
		अगर (ret < 0)
			वापस ret;
		अगर (ret & 0x80)
			data->enable_dts = 0x3; /* Enable DTS & TSI */
	पूर्ण

	/* Check DTS enable status */
	अगर (data->enable_dts) अणु
		ret = nct7904_पढ़ो_reg(data, BANK_0, DTS_T_CTRL0_REG);
		अगर (ret < 0)
			वापस ret;
		data->has_dts = ret & 0xF;
		अगर (data->enable_dts & ENABLE_TSI) अणु
			ret = nct7904_पढ़ो_reg(data, BANK_0, DTS_T_CTRL1_REG);
			अगर (ret < 0)
				वापस ret;
			data->has_dts |= (ret & 0xF) << 4;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < FANCTL_MAX; i++) अणु
		ret = nct7904_पढ़ो_reg(data, BANK_3, FANCTL1_FMR_REG + i);
		अगर (ret < 0)
			वापस ret;
		data->fan_mode[i] = ret;
	पूर्ण

	/* Read all of SMI status रेजिस्टर to clear alarms */
	क्रम (i = 0; i < SMI_STS_MAX; i++) अणु
		ret = nct7904_पढ़ो_reg(data, BANK_0, SMI_STS1_REG + i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	hwmon_dev =
		devm_hwmon_device_रेजिस्टर_with_info(dev, client->name, data,
						     &nct7904_chip_info, शून्य);
	ret = PTR_ERR_OR_ZERO(hwmon_dev);
	अगर (ret)
		वापस ret;

	/* Watchकरोg initialization */
	data->wdt.ops = &nct7904_wdt_ops;
	data->wdt.info = &nct7904_wdt_info;

	data->wdt.समयout = WATCHDOG_TIMEOUT * 60; /* Set शेष समयout */
	data->wdt.min_समयout = MIN_TIMEOUT;
	data->wdt.max_समयout = MAX_TIMEOUT;
	data->wdt.parent = &client->dev;

	watchकरोg_init_समयout(&data->wdt, समयout * 60, &client->dev);
	watchकरोg_set_nowayout(&data->wdt, nowayout);
	watchकरोg_set_drvdata(&data->wdt, data);

	watchकरोg_stop_on_unरेजिस्टर(&data->wdt);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &data->wdt);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nct7904_id[] = अणु
	अणु"nct7904", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nct7904_id);

अटल काष्ठा i2c_driver nct7904_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "nct7904",
	पूर्ण,
	.probe_new = nct7904_probe,
	.id_table = nct7904_id,
	.detect = nct7904_detect,
	.address_list = normal_i2c,
पूर्ण;

module_i2c_driver(nct7904_driver);

MODULE_AUTHOR("Vadim V. Vlasov <vvlasov@dev.rtsoft.ru>");
MODULE_DESCRIPTION("Hwmon driver for NUVOTON NCT7904");
MODULE_LICENSE("GPL");
