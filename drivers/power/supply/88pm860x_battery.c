<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery driver क्रम Marvell 88PM860x PMIC
 *
 * Copyright (c) 2012 Marvell International Ltd.
 * Author:	Jett Zhou <jtzhou@marvell.com>
 *		Haojian Zhuang <haojian.zhuang@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mfd/88pm860x.h>
#समावेश <linux/delay.h>

/* bit definitions of Status Query Interface 2 */
#घोषणा STATUS2_CHG			(1 << 2)
#घोषणा STATUS2_BAT			(1 << 3)
#घोषणा STATUS2_VBUS			(1 << 4)

/* bit definitions of Measurement Enable 1 Register */
#घोषणा MEAS1_TINT			(1 << 3)
#घोषणा MEAS1_GP1			(1 << 5)

/* bit definitions of Measurement Enable 3 Register */
#घोषणा MEAS3_IBAT			(1 << 0)
#घोषणा MEAS3_BAT_DET			(1 << 1)
#घोषणा MEAS3_CC			(1 << 2)

/* bit definitions of Measurement Off Time Register */
#घोषणा MEAS_OFF_SLEEP_EN		(1 << 1)

/* bit definitions of GPADC Bias Current 2 Register */
#घोषणा GPBIAS2_GPADC1_SET		(2 << 4)
/* GPADC1 Bias Current value in uA unit */
#घोषणा GPBIAS2_GPADC1_UA		((GPBIAS2_GPADC1_SET >> 4) * 5 + 1)

/* bit definitions of GPADC Misc 1 Register */
#घोषणा GPMISC1_GPADC_EN		(1 << 0)

/* bit definitions of Charger Control 6 Register */
#घोषणा CC6_BAT_DET_GPADC1		1

/* bit definitions of Coulomb Counter Reading Register */
#घोषणा CCNT_AVG_SEL			(4 << 3)

/* bit definitions of RTC miscellaneous Register1 */
#घोषणा RTC_SOC_5LSB		(0x1F << 3)

/* bit definitions of RTC Register1 */
#घोषणा RTC_SOC_3MSB		(0x7)

/* bit definitions of Power up Log रेजिस्टर */
#घोषणा BAT_WU_LOG			(1<<6)

/* coulomb counter index */
#घोषणा CCNT_POS1			0
#घोषणा CCNT_POS2			1
#घोषणा CCNT_NEG1			2
#घोषणा CCNT_NEG2			3
#घोषणा CCNT_SPOS			4
#घोषणा CCNT_SNEG			5

/* OCV -- Open Circuit Voltage */
#घोषणा OCV_MODE_ACTIVE			0
#घोषणा OCV_MODE_SLEEP			1

/* Vbat range of CC क्रम measuring Rbat */
#घोषणा LOW_BAT_THRESHOLD		3600
#घोषणा VBATT_RESISTOR_MIN		3800
#घोषणा VBATT_RESISTOR_MAX		4100

/* TBAT क्रम batt, TINT क्रम chip itself */
#घोषणा PM860X_TEMP_TINT		(0)
#घोषणा PM860X_TEMP_TBAT		(1)

/*
 * Battery temperature based on NTC resistor, defined
 * corresponding resistor value  -- Ohm / C degeree.
 */
#घोषणा TBAT_NEG_25D		127773	/* -25 */
#घोषणा TBAT_NEG_10D		54564	/* -10 */
#घोषणा TBAT_0D			32330	/* 0 */
#घोषणा TBAT_10D		19785	/* 10 */
#घोषणा TBAT_20D		12468	/* 20 */
#घोषणा TBAT_30D		8072	/* 30 */
#घोषणा TBAT_40D		5356	/* 40 */

काष्ठा pm860x_battery_info अणु
	काष्ठा pm860x_chip *chip;
	काष्ठा i2c_client *i2c;
	काष्ठा device *dev;

	काष्ठा घातer_supply *battery;
	काष्ठा mutex lock;
	पूर्णांक status;
	पूर्णांक irq_cc;
	पूर्णांक irq_batt;
	पूर्णांक max_capacity;
	पूर्णांक resistor;		/* Battery Internal Resistor */
	पूर्णांक last_capacity;
	पूर्णांक start_soc;
	अचिन्हित present:1;
	अचिन्हित temp_type:1;	/* TINT or TBAT */
पूर्ण;

काष्ठा ccnt अणु
	अचिन्हित दीर्घ दीर्घ pos;
	अचिन्हित दीर्घ दीर्घ neg;
	अचिन्हित पूर्णांक spos;
	अचिन्हित पूर्णांक sneg;

	पूर्णांक total_chg;		/* mAh(3.6C) */
	पूर्णांक total_dischg;	/* mAh(3.6C) */
पूर्ण;

/*
 * State of Charge.
 * The first number is mAh(=3.6C), and the second number is percent poपूर्णांक.
 */
अटल पूर्णांक array_soc[][2] = अणु
	अणु4170, 100पूर्ण, अणु4154, 99पूर्ण, अणु4136, 98पूर्ण, अणु4122, 97पूर्ण, अणु4107, 96पूर्ण,
	अणु4102, 95पूर्ण, अणु4088, 94पूर्ण, अणु4081, 93पूर्ण, अणु4070, 92पूर्ण, अणु4060, 91पूर्ण,
	अणु4053, 90पूर्ण, अणु4044, 89पूर्ण, अणु4035, 88पूर्ण, अणु4028, 87पूर्ण, अणु4019, 86पूर्ण,
	अणु4013, 85पूर्ण, अणु4006, 84पूर्ण, अणु3995, 83पूर्ण, अणु3987, 82पूर्ण, अणु3982, 81पूर्ण,
	अणु3976, 80पूर्ण, अणु3968, 79पूर्ण, अणु3962, 78पूर्ण, अणु3954, 77पूर्ण, अणु3946, 76पूर्ण,
	अणु3941, 75पूर्ण, अणु3934, 74पूर्ण, अणु3929, 73पूर्ण, अणु3922, 72पूर्ण, अणु3916, 71पूर्ण,
	अणु3910, 70पूर्ण, अणु3904, 69पूर्ण, अणु3898, 68पूर्ण, अणु3892, 67पूर्ण, अणु3887, 66पूर्ण,
	अणु3880, 65पूर्ण, अणु3874, 64पूर्ण, अणु3868, 63पूर्ण, अणु3862, 62पूर्ण, अणु3854, 61पूर्ण,
	अणु3849, 60पूर्ण, अणु3843, 59पूर्ण, अणु3840, 58पूर्ण, अणु3833, 57पूर्ण, अणु3829, 56पूर्ण,
	अणु3824, 55पूर्ण, अणु3818, 54पूर्ण, अणु3815, 53पूर्ण, अणु3810, 52पूर्ण, अणु3808, 51पूर्ण,
	अणु3804, 50पूर्ण, अणु3801, 49पूर्ण, अणु3798, 48पूर्ण, अणु3796, 47पूर्ण, अणु3792, 46पूर्ण,
	अणु3789, 45पूर्ण, अणु3785, 44पूर्ण, अणु3784, 43पूर्ण, अणु3782, 42पूर्ण, अणु3780, 41पूर्ण,
	अणु3777, 40पूर्ण, अणु3776, 39पूर्ण, अणु3774, 38पूर्ण, अणु3772, 37पूर्ण, अणु3771, 36पूर्ण,
	अणु3769, 35पूर्ण, अणु3768, 34पूर्ण, अणु3764, 33पूर्ण, अणु3763, 32पूर्ण, अणु3760, 31पूर्ण,
	अणु3760, 30पूर्ण, अणु3754, 29पूर्ण, अणु3750, 28पूर्ण, अणु3749, 27पूर्ण, अणु3744, 26पूर्ण,
	अणु3740, 25पूर्ण, अणु3734, 24पूर्ण, अणु3732, 23पूर्ण, अणु3728, 22पूर्ण, अणु3726, 21पूर्ण,
	अणु3720, 20पूर्ण, अणु3716, 19पूर्ण, अणु3709, 18पूर्ण, अणु3703, 17पूर्ण, अणु3698, 16पूर्ण,
	अणु3692, 15पूर्ण, अणु3683, 14पूर्ण, अणु3675, 13पूर्ण, अणु3670, 12पूर्ण, अणु3665, 11पूर्ण,
	अणु3661, 10पूर्ण, अणु3649, 9पूर्ण, अणु3637, 8पूर्ण, अणु3622, 7पूर्ण, अणु3609, 6पूर्ण,
	अणु3580, 5पूर्ण, अणु3558, 4पूर्ण, अणु3540, 3पूर्ण, अणु3510, 2पूर्ण, अणु3429, 1पूर्ण,
पूर्ण;

अटल काष्ठा ccnt ccnt_data;

/*
 * रेजिस्टर 1 bit[7:0] -- bit[11:4] of measured value of voltage
 * रेजिस्टर 0 bit[3:0] -- bit[3:0] of measured value of voltage
 */
अटल पूर्णांक measure_12bit_voltage(काष्ठा pm860x_battery_info *info,
				 पूर्णांक offset, पूर्णांक *data)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक ret;

	ret = pm860x_bulk_पढ़ो(info->i2c, offset, 2, buf);
	अगर (ret < 0)
		वापस ret;

	*data = ((buf[0] & 0xff) << 4) | (buf[1] & 0x0f);
	/* V_MEAS(mV) = data * 1.8 * 1000 / (2^12) */
	*data = ((*data & 0xfff) * 9 * 25) >> 9;
	वापस 0;
पूर्ण

अटल पूर्णांक measure_vbatt(काष्ठा pm860x_battery_info *info, पूर्णांक state,
			 पूर्णांक *data)
अणु
	अचिन्हित अक्षर buf[5];
	पूर्णांक ret;

	चयन (state) अणु
	हाल OCV_MODE_ACTIVE:
		ret = measure_12bit_voltage(info, PM8607_VBAT_MEAS1, data);
		अगर (ret)
			वापस ret;
		/* V_BATT_MEAS(mV) = value * 3 * 1.8 * 1000 / (2^12) */
		*data *= 3;
		अवरोध;
	हाल OCV_MODE_SLEEP:
		/*
		 * voltage value of VBATT in sleep mode is saved in dअगरferent
		 * रेजिस्टरs.
		 * bit[11:10] -- bit[7:6] of LDO9(0x18)
		 * bit[9:8] -- bit[7:6] of LDO8(0x17)
		 * bit[7:6] -- bit[7:6] of LDO7(0x16)
		 * bit[5:4] -- bit[7:6] of LDO6(0x15)
		 * bit[3:0] -- bit[7:4] of LDO5(0x14)
		 */
		ret = pm860x_bulk_पढ़ो(info->i2c, PM8607_LDO5, 5, buf);
		अगर (ret < 0)
			वापस ret;
		ret = ((buf[4] >> 6) << 10) | ((buf[3] >> 6) << 8)
		    | ((buf[2] >> 6) << 6) | ((buf[1] >> 6) << 4)
		    | (buf[0] >> 4);
		/* V_BATT_MEAS(mV) = data * 3 * 1.8 * 1000 / (2^12) */
		*data = ((*data & 0xff) * 27 * 25) >> 9;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return value is चिन्हित data.
 * Negative value means disअक्षरging, and positive value means अक्षरging.
 */
अटल पूर्णांक measure_current(काष्ठा pm860x_battery_info *info, पूर्णांक *data)
अणु
	अचिन्हित अक्षर buf[2];
	लघु s;
	पूर्णांक ret;

	ret = pm860x_bulk_पढ़ो(info->i2c, PM8607_IBAT_MEAS1, 2, buf);
	अगर (ret < 0)
		वापस ret;

	s = ((buf[0] & 0xff) << 8) | (buf[1] & 0xff);
	/* current(mA) = value * 0.125 */
	*data = s >> 3;
	वापस 0;
पूर्ण

अटल पूर्णांक set_अक्षरger_current(काष्ठा pm860x_battery_info *info, पूर्णांक data,
			       पूर्णांक *old)
अणु
	पूर्णांक ret;

	अगर (data < 50 || data > 1600 || !old)
		वापस -EINVAL;

	data = ((data - 50) / 50) & 0x1f;
	*old = pm860x_reg_पढ़ो(info->i2c, PM8607_CHG_CTRL2);
	*old = (*old & 0x1f) * 50 + 50;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL2, 0x1f, data);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_ccnt(काष्ठा pm860x_battery_info *info, पूर्णांक offset,
		     पूर्णांक *ccnt)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक ret;

	ret = pm860x_set_bits(info->i2c, PM8607_CCNT, 7, offset & 7);
	अगर (ret < 0)
		जाओ out;
	ret = pm860x_bulk_पढ़ो(info->i2c, PM8607_CCNT_MEAS1, 2, buf);
	अगर (ret < 0)
		जाओ out;
	*ccnt = ((buf[0] & 0xff) << 8) | (buf[1] & 0xff);
	वापस 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक calc_ccnt(काष्ठा pm860x_battery_info *info, काष्ठा ccnt *ccnt)
अणु
	अचिन्हित पूर्णांक sum;
	पूर्णांक ret;
	पूर्णांक data;

	ret = पढ़ो_ccnt(info, CCNT_POS1, &data);
	अगर (ret)
		जाओ out;
	sum = data & 0xffff;
	ret = पढ़ो_ccnt(info, CCNT_POS2, &data);
	अगर (ret)
		जाओ out;
	sum |= (data & 0xffff) << 16;
	ccnt->pos += sum;

	ret = पढ़ो_ccnt(info, CCNT_NEG1, &data);
	अगर (ret)
		जाओ out;
	sum = data & 0xffff;
	ret = पढ़ो_ccnt(info, CCNT_NEG2, &data);
	अगर (ret)
		जाओ out;
	sum |= (data & 0xffff) << 16;
	sum = ~sum + 1;		/* since it's negative */
	ccnt->neg += sum;

	ret = पढ़ो_ccnt(info, CCNT_SPOS, &data);
	अगर (ret)
		जाओ out;
	ccnt->spos += data;
	ret = पढ़ो_ccnt(info, CCNT_SNEG, &data);
	अगर (ret)
		जाओ out;

	/*
	 * अक्षरge(mAh)  = count * 1.6984 * 1e(-8)
	 *              = count * 16984 * 1.024 * 1.024 * 1.024 / (2 ^ 40)
	 *              = count * 18236 / (2 ^ 40)
	 */
	ccnt->total_chg = (पूर्णांक) ((ccnt->pos * 18236) >> 40);
	ccnt->total_dischg = (पूर्णांक) ((ccnt->neg * 18236) >> 40);
	वापस 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक clear_ccnt(काष्ठा pm860x_battery_info *info, काष्ठा ccnt *ccnt)
अणु
	पूर्णांक data;

	स_रखो(ccnt, 0, माप(*ccnt));
	/* पढ़ो to clear ccnt */
	पढ़ो_ccnt(info, CCNT_POS1, &data);
	पढ़ो_ccnt(info, CCNT_POS2, &data);
	पढ़ो_ccnt(info, CCNT_NEG1, &data);
	पढ़ो_ccnt(info, CCNT_NEG2, &data);
	पढ़ो_ccnt(info, CCNT_SPOS, &data);
	पढ़ो_ccnt(info, CCNT_SNEG, &data);
	वापस 0;
पूर्ण

/* Calculate Open Circuit Voltage */
अटल पूर्णांक calc_ocv(काष्ठा pm860x_battery_info *info, पूर्णांक *ocv)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक data;
	पूर्णांक vbatt_avg;
	पूर्णांक vbatt_sum;
	पूर्णांक ibatt_avg;
	पूर्णांक ibatt_sum;

	अगर (!ocv)
		वापस -EINVAL;

	क्रम (i = 0, ibatt_sum = 0, vbatt_sum = 0; i < 10; i++) अणु
		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		अगर (ret)
			जाओ out;
		vbatt_sum += data;
		ret = measure_current(info, &data);
		अगर (ret)
			जाओ out;
		ibatt_sum += data;
	पूर्ण
	vbatt_avg = vbatt_sum / 10;
	ibatt_avg = ibatt_sum / 10;

	mutex_lock(&info->lock);
	अगर (info->present)
		*ocv = vbatt_avg - ibatt_avg * info->resistor / 1000;
	अन्यथा
		*ocv = vbatt_avg;
	mutex_unlock(&info->lock);
	dev_dbg(info->dev, "VBAT average:%d, OCV:%d\n", vbatt_avg, *ocv);
	वापस 0;
out:
	वापस ret;
पूर्ण

/* Calculate State of Charge (percent poपूर्णांकs) */
अटल पूर्णांक calc_soc(काष्ठा pm860x_battery_info *info, पूर्णांक state, पूर्णांक *soc)
अणु
	पूर्णांक i;
	पूर्णांक ocv;
	पूर्णांक count;
	पूर्णांक ret = -EINVAL;

	अगर (!soc)
		वापस -EINVAL;

	चयन (state) अणु
	हाल OCV_MODE_ACTIVE:
		ret = calc_ocv(info, &ocv);
		अवरोध;
	हाल OCV_MODE_SLEEP:
		ret = measure_vbatt(info, OCV_MODE_SLEEP, &ocv);
		अवरोध;
	पूर्ण
	अगर (ret)
		वापस ret;

	count = ARRAY_SIZE(array_soc);
	अगर (ocv < array_soc[count - 1][0]) अणु
		*soc = 0;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (ocv >= array_soc[i][0]) अणु
			*soc = array_soc[i][1];
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t pm860x_coulomb_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_battery_info *info = data;

	calc_ccnt(info, &ccnt_data);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pm860x_batt_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pm860x_battery_info *info = data;
	पूर्णांक ret;

	mutex_lock(&info->lock);
	ret = pm860x_reg_पढ़ो(info->i2c, PM8607_STATUS_2);
	अगर (ret & STATUS2_BAT) अणु
		info->present = 1;
		info->temp_type = PM860X_TEMP_TBAT;
	पूर्ण अन्यथा अणु
		info->present = 0;
		info->temp_type = PM860X_TEMP_TINT;
	पूर्ण
	mutex_unlock(&info->lock);
	/* clear ccnt since battery is attached or dettached */
	clear_ccnt(info, &ccnt_data);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pm860x_init_battery(काष्ठा pm860x_battery_info *info)
अणु
	अचिन्हित अक्षर buf[2];
	पूर्णांक ret;
	पूर्णांक data;
	पूर्णांक bat_हटाओ;
	पूर्णांक soc = 0;

	/* measure enable on GPADC1 */
	data = MEAS1_GP1;
	अगर (info->temp_type == PM860X_TEMP_TINT)
		data |= MEAS1_TINT;
	ret = pm860x_set_bits(info->i2c, PM8607_MEAS_EN1, data, data);
	अगर (ret)
		जाओ out;

	/* measure enable on IBAT, BAT_DET, CC. IBAT is depend on CC. */
	data = MEAS3_IBAT | MEAS3_BAT_DET | MEAS3_CC;
	ret = pm860x_set_bits(info->i2c, PM8607_MEAS_EN3, data, data);
	अगर (ret)
		जाओ out;

	/* measure disable CC in sleep समय  */
	ret = pm860x_reg_ग_लिखो(info->i2c, PM8607_MEAS_OFF_TIME1, 0x82);
	अगर (ret)
		जाओ out;
	ret = pm860x_reg_ग_लिखो(info->i2c, PM8607_MEAS_OFF_TIME2, 0x6c);
	अगर (ret)
		जाओ out;

	/* enable GPADC */
	ret = pm860x_set_bits(info->i2c, PM8607_GPADC_MISC1,
			    GPMISC1_GPADC_EN, GPMISC1_GPADC_EN);
	अगर (ret < 0)
		जाओ out;

	/* detect battery via GPADC1 */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL6,
			    CC6_BAT_DET_GPADC1, CC6_BAT_DET_GPADC1);
	अगर (ret < 0)
		जाओ out;

	ret = pm860x_set_bits(info->i2c, PM8607_CCNT, 7 << 3,
			      CCNT_AVG_SEL);
	अगर (ret < 0)
		जाओ out;

	/* set GPADC1 bias */
	ret = pm860x_set_bits(info->i2c, PM8607_GP_BIAS2, 0xF << 4,
			      GPBIAS2_GPADC1_SET);
	अगर (ret < 0)
		जाओ out;

	/* check whether battery present) */
	mutex_lock(&info->lock);
	ret = pm860x_reg_पढ़ो(info->i2c, PM8607_STATUS_2);
	अगर (ret < 0) अणु
		mutex_unlock(&info->lock);
		जाओ out;
	पूर्ण
	अगर (ret & STATUS2_BAT) अणु
		info->present = 1;
		info->temp_type = PM860X_TEMP_TBAT;
	पूर्ण अन्यथा अणु
		info->present = 0;
		info->temp_type = PM860X_TEMP_TINT;
	पूर्ण
	mutex_unlock(&info->lock);

	ret = calc_soc(info, OCV_MODE_ACTIVE, &soc);
	अगर (ret < 0)
		जाओ out;

	data = pm860x_reg_पढ़ो(info->i2c, PM8607_POWER_UP_LOG);
	bat_हटाओ = data & BAT_WU_LOG;

	dev_dbg(info->dev, "battery wake up? %s\n",
		bat_हटाओ != 0 ? "yes" : "no");

	/* restore SOC from RTC करोमुख्य रेजिस्टर */
	अगर (bat_हटाओ == 0) अणु
		buf[0] = pm860x_reg_पढ़ो(info->i2c, PM8607_RTC_MISC2);
		buf[1] = pm860x_reg_पढ़ो(info->i2c, PM8607_RTC1);
		data = ((buf[1] & 0x3) << 5) | ((buf[0] >> 3) & 0x1F);
		अगर (data > soc + 15)
			info->start_soc = soc;
		अन्यथा अगर (data < soc - 15)
			info->start_soc = soc;
		अन्यथा
			info->start_soc = data;
		dev_dbg(info->dev, "soc_rtc %d, soc_ocv :%d\n", data, soc);
	पूर्ण अन्यथा अणु
		pm860x_set_bits(info->i2c, PM8607_POWER_UP_LOG,
				BAT_WU_LOG, BAT_WU_LOG);
		info->start_soc = soc;
	पूर्ण
	info->last_capacity = info->start_soc;
	dev_dbg(info->dev, "init soc : %d\n", info->last_capacity);
out:
	वापस;
पूर्ण

अटल व्योम set_temp_threshold(काष्ठा pm860x_battery_info *info,
			       पूर्णांक min, पूर्णांक max)
अणु
	पूर्णांक data;

	/* (पंचांगp << 8) / 1800 */
	अगर (min <= 0)
		data = 0;
	अन्यथा
		data = (min << 8) / 1800;
	pm860x_reg_ग_लिखो(info->i2c, PM8607_GPADC1_HIGHTH, data);
	dev_dbg(info->dev, "TEMP_HIGHTH : min: %d, 0x%x\n", min, data);

	अगर (max <= 0)
		data = 0xff;
	अन्यथा
		data = (max << 8) / 1800;
	pm860x_reg_ग_लिखो(info->i2c, PM8607_GPADC1_LOWTH, data);
	dev_dbg(info->dev, "TEMP_LOWTH:max : %d, 0x%x\n", max, data);
पूर्ण

अटल पूर्णांक measure_temp(काष्ठा pm860x_battery_info *info, पूर्णांक *data)
अणु
	पूर्णांक ret;
	पूर्णांक temp;
	पूर्णांक min;
	पूर्णांक max;

	अगर (info->temp_type == PM860X_TEMP_TINT) अणु
		ret = measure_12bit_voltage(info, PM8607_TINT_MEAS1, data);
		अगर (ret)
			वापस ret;
		*data = (*data - 884) * 1000 / 3611;
	पूर्ण अन्यथा अणु
		ret = measure_12bit_voltage(info, PM8607_GPADC1_MEAS1, data);
		अगर (ret)
			वापस ret;
		/* meausered Vtbat(mV) / Ibias_current(11uA)*/
		*data = (*data * 1000) / GPBIAS2_GPADC1_UA;

		अगर (*data > TBAT_NEG_25D) अणु
			temp = -30;	/* over cold , suppose -30 roughly */
			max = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, 0, max);
		पूर्ण अन्यथा अगर (*data > TBAT_NEG_10D) अणु
			temp = -15;	/* -15 degree, code */
			max = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, 0, max);
		पूर्ण अन्यथा अगर (*data > TBAT_0D) अणु
			temp = -5;	/* -5 degree */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, min, max);
		पूर्ण अन्यथा अगर (*data > TBAT_10D) अणु
			temp = 5;	/* in range of (0, 10) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, min, max);
		पूर्ण अन्यथा अगर (*data > TBAT_20D) अणु
			temp = 15;	/* in range of (10, 20) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, min, max);
		पूर्ण अन्यथा अगर (*data > TBAT_30D) अणु
			temp = 25;	/* in range of (20, 30) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, min, max);
		पूर्ण अन्यथा अगर (*data > TBAT_40D) अणु
			temp = 35;	/* in range of (30, 40) */
			min = TBAT_NEG_10D * GPBIAS2_GPADC1_UA / 1000;
			max = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, min, max);
		पूर्ण अन्यथा अणु
			min = TBAT_40D * GPBIAS2_GPADC1_UA / 1000;
			set_temp_threshold(info, min, 0);
			temp = 45;	/* over heat ,suppose 45 roughly */
		पूर्ण

		dev_dbg(info->dev, "temp_C:%d C,temp_mv:%d mv\n", temp, *data);
		*data = temp;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक calc_resistor(काष्ठा pm860x_battery_info *info)
अणु
	पूर्णांक vbatt_sum1;
	पूर्णांक vbatt_sum2;
	पूर्णांक chg_current;
	पूर्णांक ibatt_sum1;
	पूर्णांक ibatt_sum2;
	पूर्णांक data;
	पूर्णांक ret;
	पूर्णांक i;

	ret = measure_current(info, &data);
	/* make sure that अक्षरging is launched by data > 0 */
	अगर (ret || data < 0)
		जाओ out;

	ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
	अगर (ret)
		जाओ out;
	/* calculate resistor only in CC अक्षरge mode */
	अगर (data < VBATT_RESISTOR_MIN || data > VBATT_RESISTOR_MAX)
		जाओ out;

	/* current is saved */
	अगर (set_अक्षरger_current(info, 500, &chg_current))
		जाओ out;

	/*
	 * set अक्षरge current as 500mA, रुको about 500ms till अक्षरging
	 * process is launched and stable with the newer अक्षरging current.
	 */
	msleep(500);

	क्रम (i = 0, vbatt_sum1 = 0, ibatt_sum1 = 0; i < 10; i++) अणु
		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		अगर (ret)
			जाओ out_meas;
		vbatt_sum1 += data;
		ret = measure_current(info, &data);
		अगर (ret)
			जाओ out_meas;

		अगर (data < 0)
			ibatt_sum1 = ibatt_sum1 - data;	/* disअक्षरging */
		अन्यथा
			ibatt_sum1 = ibatt_sum1 + data;	/* अक्षरging */
	पूर्ण

	अगर (set_अक्षरger_current(info, 100, &ret))
		जाओ out_meas;
	/*
	 * set अक्षरge current as 100mA, रुको about 500ms till अक्षरging
	 * process is launched and stable with the newer अक्षरging current.
	 */
	msleep(500);

	क्रम (i = 0, vbatt_sum2 = 0, ibatt_sum2 = 0; i < 10; i++) अणु
		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		अगर (ret)
			जाओ out_meas;
		vbatt_sum2 += data;
		ret = measure_current(info, &data);
		अगर (ret)
			जाओ out_meas;

		अगर (data < 0)
			ibatt_sum2 = ibatt_sum2 - data;	/* disअक्षरging */
		अन्यथा
			ibatt_sum2 = ibatt_sum2 + data;	/* अक्षरging */
	पूर्ण

	/* restore current setting */
	अगर (set_अक्षरger_current(info, chg_current, &ret))
		जाओ out_meas;

	अगर ((vbatt_sum1 > vbatt_sum2) && (ibatt_sum1 > ibatt_sum2) &&
			(ibatt_sum2 > 0)) अणु
		/* calculate resistor in disअक्षरging हाल */
		data = 1000 * (vbatt_sum1 - vbatt_sum2)
		    / (ibatt_sum1 - ibatt_sum2);
		अगर ((data - info->resistor > 0) &&
				(data - info->resistor < info->resistor))
			info->resistor = data;
		अगर ((info->resistor - data > 0) &&
				(info->resistor - data < data))
			info->resistor = data;
	पूर्ण
	वापस 0;

out_meas:
	set_अक्षरger_current(info, chg_current, &ret);
out:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक calc_capacity(काष्ठा pm860x_battery_info *info, पूर्णांक *cap)
अणु
	पूर्णांक ret;
	पूर्णांक data;
	पूर्णांक ibat;
	पूर्णांक cap_ocv = 0;
	पूर्णांक cap_cc = 0;

	ret = calc_ccnt(info, &ccnt_data);
	अगर (ret)
		जाओ out;
soc:
	data = info->max_capacity * info->start_soc / 100;
	अगर (ccnt_data.total_dischg - ccnt_data.total_chg <= data) अणु
		cap_cc =
		    data + ccnt_data.total_chg - ccnt_data.total_dischg;
	पूर्ण अन्यथा अणु
		clear_ccnt(info, &ccnt_data);
		calc_soc(info, OCV_MODE_ACTIVE, &info->start_soc);
		dev_dbg(info->dev, "restart soc = %d !\n",
			info->start_soc);
		जाओ soc;
	पूर्ण

	cap_cc = cap_cc * 100 / info->max_capacity;
	अगर (cap_cc < 0)
		cap_cc = 0;
	अन्यथा अगर (cap_cc > 100)
		cap_cc = 100;

	dev_dbg(info->dev, "%s, last cap : %d", __func__,
		info->last_capacity);

	ret = measure_current(info, &ibat);
	अगर (ret)
		जाओ out;
	/* Calculate the capacity when disअक्षरging(ibat < 0) */
	अगर (ibat < 0) अणु
		ret = calc_soc(info, OCV_MODE_ACTIVE, &cap_ocv);
		अगर (ret)
			cap_ocv = info->last_capacity;
		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		अगर (ret)
			जाओ out;
		अगर (data <= LOW_BAT_THRESHOLD) अणु
			/* choose the lower capacity value to report
			 * between vbat and CC when vbat < 3.6v;
			 * than 3.6v;
			 */
			*cap = min(cap_ocv, cap_cc);
		पूर्ण अन्यथा अणु
			/* when detect vbat > 3.6v, but cap_cc < 15,and
			 * cap_ocv is 10% larger than cap_cc, we can think
			 * CC have some accumulation error, चयन to OCV
			 * to estimate capacity;
			 * */
			अगर (cap_cc < 15 && cap_ocv - cap_cc > 10)
				*cap = cap_ocv;
			अन्यथा
				*cap = cap_cc;
		पूर्ण
		/* when disअक्षरging, make sure current capacity
		 * is lower than last*/
		अगर (*cap > info->last_capacity)
			*cap = info->last_capacity;
	पूर्ण अन्यथा अणु
		*cap = cap_cc;
	पूर्ण
	info->last_capacity = *cap;

	dev_dbg(info->dev, "%s, cap_ocv:%d cap_cc:%d, cap:%d\n",
		(ibat < 0) ? "discharging" : "charging",
		 cap_ocv, cap_cc, *cap);
	/*
	 * store the current capacity to RTC करोमुख्य रेजिस्टर,
	 * after next घातer up , it will be restored.
	 */
	pm860x_set_bits(info->i2c, PM8607_RTC_MISC2, RTC_SOC_5LSB,
			(*cap & 0x1F) << 3);
	pm860x_set_bits(info->i2c, PM8607_RTC1, RTC_SOC_3MSB,
			((*cap >> 5) & 0x3));
	वापस 0;
out:
	वापस ret;
पूर्ण

अटल व्योम pm860x_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);

	calc_resistor(info);
पूर्ण

अटल पूर्णांक pm860x_batt_get_prop(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);
	पूर्णांक data;
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = info->present;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = calc_capacity(info, &data);
		अगर (ret)
			वापस ret;
		अगर (data < 0)
			data = 0;
		अन्यथा अगर (data > 100)
			data = 100;
		/* वापस 100 अगर battery is not attached */
		अगर (!info->present)
			data = 100;
		val->पूर्णांकval = data;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		/* वापस real vbatt Voltage */
		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		अगर (ret)
			वापस ret;
		val->पूर्णांकval = data * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		/* वापस Open Circuit Voltage (not measured voltage) */
		ret = calc_ocv(info, &data);
		अगर (ret)
			वापस ret;
		val->पूर्णांकval = data * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = measure_current(info, &data);
		अगर (ret)
			वापस ret;
		val->पूर्णांकval = data;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		अगर (info->present) अणु
			ret = measure_temp(info, &data);
			अगर (ret)
				वापस ret;
			data *= 10;
		पूर्ण अन्यथा अणु
			/* Fake Temp 25C Without Battery */
			data = 250;
		पूर्ण
		val->पूर्णांकval = data;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_batt_set_prop(काष्ठा घातer_supply *psy,
				       क्रमागत घातer_supply_property psp,
				       स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		clear_ccnt(info, &ccnt_data);
		info->start_soc = 100;
		dev_dbg(info->dev, "chg done, update soc = %d\n",
			info->start_soc);
		अवरोध;
	शेष:
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण


अटल क्रमागत घातer_supply_property pm860x_batt_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc pm860x_battery_desc = अणु
	.name			= "battery-monitor",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= pm860x_batt_props,
	.num_properties		= ARRAY_SIZE(pm860x_batt_props),
	.get_property		= pm860x_batt_get_prop,
	.set_property		= pm860x_batt_set_prop,
	.बाह्यal_घातer_changed	= pm860x_बाह्यal_घातer_changed,
पूर्ण;

अटल पूर्णांक pm860x_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा pm860x_battery_info *info;
	काष्ठा pm860x_घातer_pdata *pdata;
	पूर्णांक ret;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->irq_cc = platक्रमm_get_irq(pdev, 0);
	अगर (info->irq_cc <= 0)
		वापस -EINVAL;

	info->irq_batt = platक्रमm_get_irq(pdev, 1);
	अगर (info->irq_batt <= 0)
		वापस -EINVAL;

	info->chip = chip;
	info->i2c =
	    (chip->id == CHIP_PM8607) ? chip->client : chip->companion;
	info->dev = &pdev->dev;
	info->status = POWER_SUPPLY_STATUS_UNKNOWN;
	pdata = pdev->dev.platक्रमm_data;

	mutex_init(&info->lock);
	platक्रमm_set_drvdata(pdev, info);

	pm860x_init_battery(info);

	अगर (pdata && pdata->max_capacity)
		info->max_capacity = pdata->max_capacity;
	अन्यथा
		info->max_capacity = 1500;	/* set शेष capacity */
	अगर (pdata && pdata->resistor)
		info->resistor = pdata->resistor;
	अन्यथा
		info->resistor = 300;	/* set शेष पूर्णांकernal resistor */

	info->battery = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						   &pm860x_battery_desc,
						   शून्य);
	अगर (IS_ERR(info->battery))
		वापस PTR_ERR(info->battery);
	info->battery->dev.parent = &pdev->dev;

	ret = devm_request_thपढ़ोed_irq(chip->dev, info->irq_cc, शून्य,
					pm860x_coulomb_handler, IRQF_ONESHOT,
					"coulomb", info);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq_cc, ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(chip->dev, info->irq_batt, शून्य,
					pm860x_batt_handler,
					IRQF_ONESHOT, "battery", info);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			info->irq_batt, ret);
		वापस ret;
	पूर्ण


	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pm860x_battery_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag |= 1 << PM8607_IRQ_CC;
	वापस 0;
पूर्ण

अटल पूर्णांक pm860x_battery_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा pm860x_chip *chip = dev_get_drvdata(pdev->dev.parent);

	अगर (device_may_wakeup(dev))
		chip->wakeup_flag &= ~(1 << PM8607_IRQ_CC);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pm860x_battery_pm_ops,
			pm860x_battery_suspend, pm860x_battery_resume);

अटल काष्ठा platक्रमm_driver pm860x_battery_driver = अणु
	.driver = अणु
		   .name = "88pm860x-battery",
		   .pm = &pm860x_battery_pm_ops,
	पूर्ण,
	.probe = pm860x_battery_probe,
पूर्ण;
module_platक्रमm_driver(pm860x_battery_driver);

MODULE_DESCRIPTION("Marvell 88PM860x Battery driver");
MODULE_LICENSE("GPL");
