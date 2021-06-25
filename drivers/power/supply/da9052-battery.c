<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Batttery Driver क्रम Dialog DA9052 PMICs
 *
 * Copyright(c) 2011 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/fs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/pdata.h>
#समावेश <linux/mfd/da9052/reg.h>

/* STATIC CONFIGURATION */
#घोषणा DA9052_BAT_CUTOFF_VOLT		2800
#घोषणा DA9052_BAT_TSH			62000
#घोषणा DA9052_BAT_LOW_CAP		4
#घोषणा DA9052_AVG_SZ			4
#घोषणा DA9052_VC_TBL_SZ		68
#घोषणा DA9052_VC_TBL_REF_SZ		3

#घोषणा DA9052_ISET_USB_MASK		0x0F
#घोषणा DA9052_CHG_USB_ILIM_MASK	0x40
#घोषणा DA9052_CHG_LIM_COLS		16

#घोषणा DA9052_MEAN(x, y)		((x + y) / 2)

क्रमागत अक्षरger_type_क्रमागत अणु
	DA9052_NOCHARGER = 1,
	DA9052_CHARGER,
पूर्ण;

अटल स्थिर u16 da9052_chg_current_lim[2][DA9052_CHG_LIM_COLS] = अणु
	अणु70,  80,  90,  100, 110, 120, 400,  450,
	 500, 550, 600, 650, 700, 900, 1100, 1300पूर्ण,
	अणु80,  90,  100, 110,  120,  400,  450,  500,
	 550, 600, 800, 1000, 1200, 1400, 1600, 1800पूर्ण,
पूर्ण;

अटल स्थिर u16 vc_tbl_ref[3] = अणु10, 25, 40पूर्ण;
/* Lookup table क्रम voltage vs capacity */
अटल u32 स्थिर vc_tbl[3][68][2] = अणु
	/* For temperature 10 degree Celsius */
	अणु
	अणु4082, 100पूर्ण, अणु4036, 98पूर्ण,
	अणु4020, 96पूर्ण, अणु4008, 95पूर्ण,
	अणु3997, 93पूर्ण, अणु3983, 91पूर्ण,
	अणु3964, 90पूर्ण, अणु3943, 88पूर्ण,
	अणु3926, 87पूर्ण, अणु3912, 85पूर्ण,
	अणु3900, 84पूर्ण, अणु3890, 82पूर्ण,
	अणु3881, 80पूर्ण, अणु3873, 79पूर्ण,
	अणु3865, 77पूर्ण, अणु3857, 76पूर्ण,
	अणु3848, 74पूर्ण, अणु3839, 73पूर्ण,
	अणु3829, 71पूर्ण, अणु3820, 70पूर्ण,
	अणु3811, 68पूर्ण, अणु3802, 67पूर्ण,
	अणु3794, 65पूर्ण, अणु3785, 64पूर्ण,
	अणु3778, 62पूर्ण, अणु3770, 61पूर्ण,
	अणु3763, 59पूर्ण, अणु3756, 58पूर्ण,
	अणु3750, 56पूर्ण, अणु3744, 55पूर्ण,
	अणु3738, 53पूर्ण, अणु3732, 52पूर्ण,
	अणु3727, 50पूर्ण, अणु3722, 49पूर्ण,
	अणु3717, 47पूर्ण, अणु3712, 46पूर्ण,
	अणु3708, 44पूर्ण, अणु3703, 43पूर्ण,
	अणु3700, 41पूर्ण, अणु3696, 40पूर्ण,
	अणु3693, 38पूर्ण, अणु3691, 37पूर्ण,
	अणु3688, 35पूर्ण, अणु3686, 34पूर्ण,
	अणु3683, 32पूर्ण, अणु3681, 31पूर्ण,
	अणु3678, 29पूर्ण, अणु3675, 28पूर्ण,
	अणु3672, 26पूर्ण, अणु3669, 25पूर्ण,
	अणु3665, 23पूर्ण, अणु3661, 22पूर्ण,
	अणु3656, 21पूर्ण, अणु3651, 19पूर्ण,
	अणु3645, 18पूर्ण, अणु3639, 16पूर्ण,
	अणु3631, 15पूर्ण, अणु3622, 13पूर्ण,
	अणु3611, 12पूर्ण, अणु3600, 10पूर्ण,
	अणु3587, 9पूर्ण, अणु3572, 7पूर्ण,
	अणु3548, 6पूर्ण, अणु3503, 5पूर्ण,
	अणु3420, 3पूर्ण, अणु3268, 2पूर्ण,
	अणु2992, 1पूर्ण, अणु2746, 0पूर्ण
	पूर्ण,
	/* For temperature 25 degree Celsius */
	अणु
	अणु4102, 100पूर्ण, अणु4065, 98पूर्ण,
	अणु4048, 96पूर्ण, अणु4034, 95पूर्ण,
	अणु4021, 93पूर्ण, अणु4011, 92पूर्ण,
	अणु4001, 90पूर्ण, अणु3986, 88पूर्ण,
	अणु3968, 87पूर्ण, अणु3952, 85पूर्ण,
	अणु3938, 84पूर्ण, अणु3926, 82पूर्ण,
	अणु3916, 81पूर्ण, अणु3908, 79पूर्ण,
	अणु3900, 77पूर्ण, अणु3892, 76पूर्ण,
	अणु3883, 74पूर्ण, अणु3874, 73पूर्ण,
	अणु3864, 71पूर्ण, अणु3855, 70पूर्ण,
	अणु3846, 68पूर्ण, अणु3836, 67पूर्ण,
	अणु3827, 65पूर्ण, अणु3819, 64पूर्ण,
	अणु3810, 62पूर्ण, अणु3801, 61पूर्ण,
	अणु3793, 59पूर्ण, अणु3786, 58पूर्ण,
	अणु3778, 56पूर्ण, अणु3772, 55पूर्ण,
	अणु3765, 53पूर्ण, अणु3759, 52पूर्ण,
	अणु3754, 50पूर्ण, अणु3748, 49पूर्ण,
	अणु3743, 47पूर्ण, अणु3738, 46पूर्ण,
	अणु3733, 44पूर्ण, अणु3728, 43पूर्ण,
	अणु3724, 41पूर्ण, अणु3720, 40पूर्ण,
	अणु3716, 38पूर्ण, अणु3712, 37पूर्ण,
	अणु3709, 35पूर्ण, अणु3706, 34पूर्ण,
	अणु3703, 33पूर्ण, अणु3701, 31पूर्ण,
	अणु3698, 30पूर्ण, अणु3696, 28पूर्ण,
	अणु3693, 27पूर्ण, अणु3690, 25पूर्ण,
	अणु3687, 24पूर्ण, अणु3683, 22पूर्ण,
	अणु3680, 21पूर्ण, अणु3675, 19पूर्ण,
	अणु3671, 18पूर्ण, अणु3666, 17पूर्ण,
	अणु3660, 15पूर्ण, अणु3654, 14पूर्ण,
	अणु3647, 12पूर्ण, अणु3639, 11पूर्ण,
	अणु3630, 9पूर्ण, अणु3621, 8पूर्ण,
	अणु3613, 6पूर्ण, अणु3606, 5पूर्ण,
	अणु3597, 4पूर्ण, अणु3582, 2पूर्ण,
	अणु3546, 1पूर्ण, अणु2747, 0पूर्ण
	पूर्ण,
	/* For temperature 40 degree Celsius */
	अणु
	अणु4114, 100पूर्ण, अणु4081, 98पूर्ण,
	अणु4065, 96पूर्ण, अणु4050, 95पूर्ण,
	अणु4036, 93पूर्ण, अणु4024, 92पूर्ण,
	अणु4013, 90पूर्ण, अणु4002, 88पूर्ण,
	अणु3990, 87पूर्ण, अणु3976, 85पूर्ण,
	अणु3962, 84पूर्ण, अणु3950, 82पूर्ण,
	अणु3939, 81पूर्ण, अणु3930, 79पूर्ण,
	अणु3921, 77पूर्ण, अणु3912, 76पूर्ण,
	अणु3902, 74पूर्ण, अणु3893, 73पूर्ण,
	अणु3883, 71पूर्ण, अणु3874, 70पूर्ण,
	अणु3865, 68पूर्ण, अणु3856, 67पूर्ण,
	अणु3847, 65पूर्ण, अणु3838, 64पूर्ण,
	अणु3829, 62पूर्ण, अणु3820, 61पूर्ण,
	अणु3812, 59पूर्ण, अणु3803, 58पूर्ण,
	अणु3795, 56पूर्ण, अणु3787, 55पूर्ण,
	अणु3780, 53पूर्ण, अणु3773, 52पूर्ण,
	अणु3767, 50पूर्ण, अणु3761, 49पूर्ण,
	अणु3756, 47पूर्ण, अणु3751, 46पूर्ण,
	अणु3746, 44पूर्ण, अणु3741, 43पूर्ण,
	अणु3736, 41पूर्ण, अणु3732, 40पूर्ण,
	अणु3728, 38पूर्ण, अणु3724, 37पूर्ण,
	अणु3720, 35पूर्ण, अणु3716, 34पूर्ण,
	अणु3713, 33पूर्ण, अणु3710, 31पूर्ण,
	अणु3707, 30पूर्ण, अणु3704, 28पूर्ण,
	अणु3701, 27पूर्ण, अणु3698, 25पूर्ण,
	अणु3695, 24पूर्ण, अणु3691, 22पूर्ण,
	अणु3686, 21पूर्ण, अणु3681, 19पूर्ण,
	अणु3676, 18पूर्ण, अणु3671, 17पूर्ण,
	अणु3666, 15पूर्ण, अणु3661, 14पूर्ण,
	अणु3655, 12पूर्ण, अणु3648, 11पूर्ण,
	अणु3640, 9पूर्ण, अणु3632, 8पूर्ण,
	अणु3622, 6पूर्ण, अणु3616, 5पूर्ण,
	अणु3611, 4पूर्ण, अणु3604, 2पूर्ण,
	अणु3594, 1पूर्ण, अणु2747, 0पूर्ण
	पूर्ण
पूर्ण;

काष्ठा da9052_battery अणु
	काष्ठा da9052 *da9052;
	काष्ठा घातer_supply *psy;
	काष्ठा notअगरier_block nb;
	पूर्णांक अक्षरger_type;
	पूर्णांक status;
	पूर्णांक health;
पूर्ण;

अटल अंतरभूत पूर्णांक volt_reg_to_mV(पूर्णांक value)
अणु
	वापस ((value * 1000) / 512) + 2500;
पूर्ण

अटल अंतरभूत पूर्णांक ichg_reg_to_mA(पूर्णांक value)
अणु
	वापस (value * 3900) / 1000;
पूर्ण

अटल पूर्णांक da9052_पढ़ो_chgend_current(काष्ठा da9052_battery *bat,
				       पूर्णांक *current_mA)
अणु
	पूर्णांक ret;

	अगर (bat->status == POWER_SUPPLY_STATUS_DISCHARGING)
		वापस -EINVAL;

	ret = da9052_reg_पढ़ो(bat->da9052, DA9052_ICHG_END_REG);
	अगर (ret < 0)
		वापस ret;

	*current_mA = ichg_reg_to_mA(ret & DA9052_ICHGEND_ICHGEND);

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_पढ़ो_chg_current(काष्ठा da9052_battery *bat, पूर्णांक *current_mA)
अणु
	पूर्णांक ret;

	अगर (bat->status == POWER_SUPPLY_STATUS_DISCHARGING)
		वापस -EINVAL;

	ret = da9052_reg_पढ़ो(bat->da9052, DA9052_ICHG_AV_REG);
	अगर (ret < 0)
		वापस ret;

	*current_mA = ichg_reg_to_mA(ret & DA9052_ICHGAV_ICHGAV);

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_bat_check_status(काष्ठा da9052_battery *bat, पूर्णांक *status)
अणु
	u8 v[2] = अणु0, 0पूर्ण;
	u8 bat_status;
	u8 chg_end;
	पूर्णांक ret;
	पूर्णांक chg_current;
	पूर्णांक chg_end_current;
	bool dcinsel;
	bool dcindet;
	bool vbussel;
	bool vbusdet;
	bool dc;
	bool vbus;

	ret = da9052_group_पढ़ो(bat->da9052, DA9052_STATUS_A_REG, 2, v);
	अगर (ret < 0)
		वापस ret;

	bat_status = v[0];
	chg_end = v[1];

	dcinsel = bat_status & DA9052_STATUSA_DCINSEL;
	dcindet = bat_status & DA9052_STATUSA_DCINDET;
	vbussel = bat_status & DA9052_STATUSA_VBUSSEL;
	vbusdet = bat_status & DA9052_STATUSA_VBUSDET;
	dc = dcinsel && dcindet;
	vbus = vbussel && vbusdet;

	/* Preference to WALL(DCIN) अक्षरger unit */
	अगर (dc || vbus) अणु
		bat->अक्षरger_type = DA9052_CHARGER;

		/* If अक्षरging end flag is set and Charging current is greater
		 * than अक्षरging end limit then battery is अक्षरging
		*/
		अगर ((chg_end & DA9052_STATUSB_CHGEND) != 0) अणु
			ret = da9052_पढ़ो_chg_current(bat, &chg_current);
			अगर (ret < 0)
				वापस ret;
			ret = da9052_पढ़ो_chgend_current(bat, &chg_end_current);
			अगर (ret < 0)
				वापस ret;

			अगर (chg_current >= chg_end_current)
				bat->status = POWER_SUPPLY_STATUS_CHARGING;
			अन्यथा
				bat->status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		पूर्ण अन्यथा अणु
			/* If Charging end flag is cleared then battery is
			 * अक्षरging
			*/
			bat->status = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण
	पूर्ण अन्यथा अगर (dcindet || vbusdet) अणु
			bat->अक्षरger_type = DA9052_CHARGER;
			bat->status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण अन्यथा अणु
		bat->अक्षरger_type = DA9052_NOCHARGER;
		bat->status = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	अगर (status != शून्य)
		*status = bat->status;
	वापस 0;
पूर्ण

अटल पूर्णांक da9052_bat_पढ़ो_volt(काष्ठा da9052_battery *bat, पूर्णांक *volt_mV)
अणु
	पूर्णांक volt;

	volt = da9052_adc_manual_पढ़ो(bat->da9052, DA9052_ADC_MAN_MUXSEL_VBAT);
	अगर (volt < 0)
		वापस volt;

	*volt_mV = volt_reg_to_mV(volt);

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_bat_check_presence(काष्ठा da9052_battery *bat, पूर्णांक *illegal)
अणु
	पूर्णांक bat_temp;

	bat_temp = da9052_adc_पढ़ो_temp(bat->da9052);
	अगर (bat_temp < 0)
		वापस bat_temp;

	अगर (bat_temp > DA9052_BAT_TSH)
		*illegal = 1;
	अन्यथा
		*illegal = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_bat_पूर्णांकerpolate(पूर्णांक vbat_lower, पूर्णांक  vbat_upper,
				   पूर्णांक level_lower, पूर्णांक level_upper,
				   पूर्णांक bat_voltage)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = ((level_upper - level_lower) * 1000) / (vbat_upper - vbat_lower);
	पंचांगp = level_lower + (((bat_voltage - vbat_lower) * पंचांगp) / 1000);

	वापस पंचांगp;
पूर्ण

अटल अचिन्हित अक्षर da9052_determine_vc_tbl_index(अचिन्हित अक्षर adc_temp)
अणु
	पूर्णांक i;

	अगर (adc_temp <= vc_tbl_ref[0])
		वापस 0;

	अगर (adc_temp > vc_tbl_ref[DA9052_VC_TBL_REF_SZ - 1])
		वापस DA9052_VC_TBL_REF_SZ - 1;

	क्रम (i = 0; i < DA9052_VC_TBL_REF_SZ - 1; i++) अणु
		अगर ((adc_temp > vc_tbl_ref[i]) &&
		    (adc_temp <= DA9052_MEAN(vc_tbl_ref[i], vc_tbl_ref[i + 1])))
				वापस i;
		अगर ((adc_temp > DA9052_MEAN(vc_tbl_ref[i], vc_tbl_ref[i + 1]))
		     && (adc_temp <= vc_tbl_ref[i]))
				वापस i + 1;
	पूर्ण
	/*
	 * For some reason authors of the driver didn't presume that we can
	 * end up here. It might be OK, but might be not, no one knows क्रम
	 * sure. Go check your battery, is it on fire?
	 */
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल पूर्णांक da9052_bat_पढ़ो_capacity(काष्ठा da9052_battery *bat, पूर्णांक *capacity)
अणु
	पूर्णांक adc_temp;
	पूर्णांक bat_voltage;
	पूर्णांक vbat_lower;
	पूर्णांक vbat_upper;
	पूर्णांक level_upper;
	पूर्णांक level_lower;
	पूर्णांक ret;
	पूर्णांक flag;
	पूर्णांक i = 0;
	पूर्णांक j;

	ret = da9052_bat_पढ़ो_volt(bat, &bat_voltage);
	अगर (ret < 0)
		वापस ret;

	adc_temp = da9052_adc_पढ़ो_temp(bat->da9052);
	अगर (adc_temp < 0)
		वापस adc_temp;

	i = da9052_determine_vc_tbl_index(adc_temp);

	अगर (bat_voltage >= vc_tbl[i][0][0]) अणु
		*capacity = 100;
		वापस 0;
	पूर्ण
	अगर (bat_voltage <= vc_tbl[i][DA9052_VC_TBL_SZ - 1][0]) अणु
		*capacity = 0;
		वापस 0;
	पूर्ण
	flag = 0;

	क्रम (j = 0; j < (DA9052_VC_TBL_SZ-1); j++) अणु
		अगर ((bat_voltage <= vc_tbl[i][j][0]) &&
		    (bat_voltage >= vc_tbl[i][j + 1][0])) अणु
			vbat_upper = vc_tbl[i][j][0];
			vbat_lower = vc_tbl[i][j + 1][0];
			level_upper = vc_tbl[i][j][1];
			level_lower = vc_tbl[i][j + 1][1];
			flag = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!flag)
		वापस -EIO;

	*capacity = da9052_bat_पूर्णांकerpolate(vbat_lower, vbat_upper, level_lower,
					   level_upper, bat_voltage);

	वापस 0;
पूर्ण

अटल पूर्णांक da9052_bat_check_health(काष्ठा da9052_battery *bat, पूर्णांक *health)
अणु
	पूर्णांक ret;
	पूर्णांक bat_illegal;
	पूर्णांक capacity;

	ret = da9052_bat_check_presence(bat, &bat_illegal);
	अगर (ret < 0)
		वापस ret;

	अगर (bat_illegal) अणु
		bat->health = POWER_SUPPLY_HEALTH_UNKNOWN;
		वापस 0;
	पूर्ण

	अगर (bat->health != POWER_SUPPLY_HEALTH_OVERHEAT) अणु
		ret = da9052_bat_पढ़ो_capacity(bat, &capacity);
		अगर (ret < 0)
			वापस ret;
		अगर (capacity < DA9052_BAT_LOW_CAP)
			bat->health = POWER_SUPPLY_HEALTH_DEAD;
		अन्यथा
			bat->health = POWER_SUPPLY_HEALTH_GOOD;
	पूर्ण

	*health = bat->health;

	वापस 0;
पूर्ण

अटल irqवापस_t da9052_bat_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9052_battery *bat = data;
	पूर्णांक virq;

	virq = regmap_irq_get_virq(bat->da9052->irq_data, irq);
	irq -= virq;

	अगर (irq == DA9052_IRQ_CHGEND)
		bat->status = POWER_SUPPLY_STATUS_FULL;
	अन्यथा
		da9052_bat_check_status(bat, शून्य);

	अगर (irq == DA9052_IRQ_CHGEND || irq == DA9052_IRQ_DCIN ||
	    irq == DA9052_IRQ_VBUS || irq == DA9052_IRQ_TBAT) अणु
		घातer_supply_changed(bat->psy);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9052_USB_current_notअगरier(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ events, व्योम *data)
अणु
	u8 row;
	u8 col;
	पूर्णांक *current_mA = data;
	पूर्णांक ret;
	काष्ठा da9052_battery *bat = container_of(nb, काष्ठा da9052_battery,
						  nb);

	अगर (bat->status == POWER_SUPPLY_STATUS_DISCHARGING)
		वापस -EPERM;

	ret = da9052_reg_पढ़ो(bat->da9052, DA9052_CHGBUCK_REG);
	अगर (ret & DA9052_CHG_USB_ILIM_MASK)
		वापस -EPERM;

	अगर (bat->da9052->chip_id == DA9052)
		row = 0;
	अन्यथा
		row = 1;

	अगर (*current_mA < da9052_chg_current_lim[row][0] ||
	    *current_mA > da9052_chg_current_lim[row][DA9052_CHG_LIM_COLS - 1])
		वापस -EINVAL;

	क्रम (col = 0; col <= DA9052_CHG_LIM_COLS - 1 ; col++) अणु
		अगर (*current_mA <= da9052_chg_current_lim[row][col])
			अवरोध;
	पूर्ण

	वापस da9052_reg_update(bat->da9052, DA9052_ISET_REG,
				 DA9052_ISET_USB_MASK, col);
पूर्ण

अटल पूर्णांक da9052_bat_get_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;
	पूर्णांक illegal;
	काष्ठा da9052_battery *bat = घातer_supply_get_drvdata(psy);

	ret = da9052_bat_check_presence(bat, &illegal);
	अगर (ret < 0)
		वापस ret;

	अगर (illegal && psp != POWER_SUPPLY_PROP_PRESENT)
		वापस -ENODEV;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = da9052_bat_check_status(bat, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval =
			(bat->अक्षरger_type == DA9052_NOCHARGER) ? 0 : 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = da9052_bat_check_presence(bat, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = da9052_bat_check_health(bat, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = DA9052_BAT_CUTOFF_VOLT * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		ret = da9052_bat_पढ़ो_volt(bat, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = da9052_पढ़ो_chg_current(bat, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = da9052_bat_पढ़ो_capacity(bat, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = da9052_adc_पढ़ो_temp(bat->da9052);
		ret = val->पूर्णांकval;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property da9052_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TECHNOLOGY,
पूर्ण;

अटल काष्ठा घातer_supply_desc psy_desc = अणु
	.name		= "da9052-bat",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= da9052_bat_props,
	.num_properties	= ARRAY_SIZE(da9052_bat_props),
	.get_property	= da9052_bat_get_property,
पूर्ण;

अटल अक्षर *da9052_bat_irqs[] = अणु
	"BATT TEMP",
	"DCIN DET",
	"DCIN REM",
	"VBUS DET",
	"VBUS REM",
	"CHG END",
पूर्ण;

अटल पूर्णांक da9052_bat_irq_bits[] = अणु
	DA9052_IRQ_TBAT,
	DA9052_IRQ_DCIN,
	DA9052_IRQ_DCINREM,
	DA9052_IRQ_VBUS,
	DA9052_IRQ_VBUSREM,
	DA9052_IRQ_CHGEND,
पूर्ण;

अटल s32 da9052_bat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9052_pdata *pdata;
	काष्ठा da9052_battery *bat;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक ret;
	पूर्णांक i;

	bat = devm_kzalloc(&pdev->dev, माप(काष्ठा da9052_battery),
				GFP_KERNEL);
	अगर (!bat)
		वापस -ENOMEM;

	psy_cfg.drv_data = bat;

	bat->da9052 = dev_get_drvdata(pdev->dev.parent);
	bat->अक्षरger_type = DA9052_NOCHARGER;
	bat->status = POWER_SUPPLY_STATUS_UNKNOWN;
	bat->health = POWER_SUPPLY_HEALTH_UNKNOWN;
	bat->nb.notअगरier_call = da9052_USB_current_notअगरier;

	pdata = bat->da9052->dev->platक्रमm_data;
	अगर (pdata != शून्य && pdata->use_क्रम_apm)
		psy_desc.use_क्रम_apm = pdata->use_क्रम_apm;
	अन्यथा
		psy_desc.use_क्रम_apm = 1;

	क्रम (i = 0; i < ARRAY_SIZE(da9052_bat_irqs); i++) अणु
		ret = da9052_request_irq(bat->da9052,
				da9052_bat_irq_bits[i], da9052_bat_irqs[i],
				da9052_bat_irq, bat);

		अगर (ret != 0) अणु
			dev_err(bat->da9052->dev,
				"DA9052 failed to request %s IRQ: %d\n",
				da9052_bat_irqs[i], ret);
			जाओ err;
		पूर्ण
	पूर्ण

	bat->psy = घातer_supply_रेजिस्टर(&pdev->dev, &psy_desc, &psy_cfg);
	अगर (IS_ERR(bat->psy)) अणु
		ret = PTR_ERR(bat->psy);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bat);
	वापस 0;

err:
	जबतक (--i >= 0)
		da9052_मुक्त_irq(bat->da9052, da9052_bat_irq_bits[i], bat);

	वापस ret;
पूर्ण
अटल पूर्णांक da9052_bat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा da9052_battery *bat = platक्रमm_get_drvdata(pdev);

	क्रम (i = 0; i < ARRAY_SIZE(da9052_bat_irqs); i++)
		da9052_मुक्त_irq(bat->da9052, da9052_bat_irq_bits[i], bat);

	घातer_supply_unरेजिस्टर(bat->psy);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9052_bat_driver = अणु
	.probe = da9052_bat_probe,
	.हटाओ = da9052_bat_हटाओ,
	.driver = अणु
		.name = "da9052-bat",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(da9052_bat_driver);

MODULE_DESCRIPTION("DA9052 BAT Device Driver");
MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9052-bat");
