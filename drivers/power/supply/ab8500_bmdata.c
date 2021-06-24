<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/of.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>

#समावेश "ab8500-bm.h"

/*
 * These are the defined batteries that uses a NTC and ID resistor placed
 * inside of the battery pack.
 * Note that the res_to_temp table must be strictly sorted by falling resistance
 * values to work.
 */
स्थिर काष्ठा abx500_res_to_temp ab8500_temp_tbl_a_thermistor[] = अणु
	अणु-5, 53407पूर्ण,
	अणु 0, 48594पूर्ण,
	अणु 5, 43804पूर्ण,
	अणु10, 39188पूर्ण,
	अणु15, 34870पूर्ण,
	अणु20, 30933पूर्ण,
	अणु25, 27422पूर्ण,
	अणु30, 24347पूर्ण,
	अणु35, 21694पूर्ण,
	अणु40, 19431पूर्ण,
	अणु45, 17517पूर्ण,
	अणु50, 15908पूर्ण,
	अणु55, 14561पूर्ण,
	अणु60, 13437पूर्ण,
	अणु65, 12500पूर्ण,
पूर्ण;
EXPORT_SYMBOL(ab8500_temp_tbl_a_thermistor);

स्थिर पूर्णांक ab8500_temp_tbl_a_size = ARRAY_SIZE(ab8500_temp_tbl_a_thermistor);
EXPORT_SYMBOL(ab8500_temp_tbl_a_size);

स्थिर काष्ठा abx500_res_to_temp ab8500_temp_tbl_b_thermistor[] = अणु
	अणु-5, 200000पूर्ण,
	अणु 0, 159024पूर्ण,
	अणु 5, 151921पूर्ण,
	अणु10, 144300पूर्ण,
	अणु15, 136424पूर्ण,
	अणु20, 128565पूर्ण,
	अणु25, 120978पूर्ण,
	अणु30, 113875पूर्ण,
	अणु35, 107397पूर्ण,
	अणु40, 101629पूर्ण,
	अणु45,  96592पूर्ण,
	अणु50,  92253पूर्ण,
	अणु55,  88569पूर्ण,
	अणु60,  85461पूर्ण,
	अणु65,  82869पूर्ण,
पूर्ण;
EXPORT_SYMBOL(ab8500_temp_tbl_b_thermistor);

स्थिर पूर्णांक ab8500_temp_tbl_b_size = ARRAY_SIZE(ab8500_temp_tbl_b_thermistor);
EXPORT_SYMBOL(ab8500_temp_tbl_b_size);

अटल स्थिर काष्ठा abx500_v_to_cap cap_tbl_a_thermistor[] = अणु
	अणु4171,	100पूर्ण,
	अणु4114,	 95पूर्ण,
	अणु4009,	 83पूर्ण,
	अणु3947,	 74पूर्ण,
	अणु3907,	 67पूर्ण,
	अणु3863,	 59पूर्ण,
	अणु3830,	 56पूर्ण,
	अणु3813,	 53पूर्ण,
	अणु3791,	 46पूर्ण,
	अणु3771,	 33पूर्ण,
	अणु3754,	 25पूर्ण,
	अणु3735,	 20पूर्ण,
	अणु3717,	 17पूर्ण,
	अणु3681,	 13पूर्ण,
	अणु3664,	  8पूर्ण,
	अणु3651,	  6पूर्ण,
	अणु3635,	  5पूर्ण,
	अणु3560,	  3पूर्ण,
	अणु3408,    1पूर्ण,
	अणु3247,	  0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा abx500_v_to_cap cap_tbl_b_thermistor[] = अणु
	अणु4161,	100पूर्ण,
	अणु4124,	 98पूर्ण,
	अणु4044,	 90पूर्ण,
	अणु4003,	 85पूर्ण,
	अणु3966,	 80पूर्ण,
	अणु3933,	 75पूर्ण,
	अणु3888,	 67पूर्ण,
	अणु3849,	 60पूर्ण,
	अणु3813,	 55पूर्ण,
	अणु3787,	 47पूर्ण,
	अणु3772,	 30पूर्ण,
	अणु3751,	 25पूर्ण,
	अणु3718,	 20पूर्ण,
	अणु3681,	 16पूर्ण,
	अणु3660,	 14पूर्ण,
	अणु3589,	 10पूर्ण,
	अणु3546,	  7पूर्ण,
	अणु3495,	  4पूर्ण,
	अणु3404,	  2पूर्ण,
	अणु3250,	  0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा abx500_v_to_cap cap_tbl[] = अणु
	अणु4186,	100पूर्ण,
	अणु4163,	 99पूर्ण,
	अणु4114,	 95पूर्ण,
	अणु4068,	 90पूर्ण,
	अणु3990,	 80पूर्ण,
	अणु3926,	 70पूर्ण,
	अणु3898,	 65पूर्ण,
	अणु3866,	 60पूर्ण,
	अणु3833,	 55पूर्ण,
	अणु3812,	 50पूर्ण,
	अणु3787,	 40पूर्ण,
	अणु3768,	 30पूर्ण,
	अणु3747,	 25पूर्ण,
	अणु3730,	 20पूर्ण,
	अणु3705,	 15पूर्ण,
	अणु3699,	 14पूर्ण,
	अणु3684,	 12पूर्ण,
	अणु3672,	  9पूर्ण,
	अणु3657,	  7पूर्ण,
	अणु3638,	  6पूर्ण,
	अणु3556,	  4पूर्ण,
	अणु3424,	  2पूर्ण,
	अणु3317,	  1पूर्ण,
	अणु3094,	  0पूर्ण,
पूर्ण;

/*
 * Note that the res_to_temp table must be strictly sorted by falling
 * resistance values to work.
 */
अटल स्थिर काष्ठा abx500_res_to_temp temp_tbl[] = अणु
	अणु-5, 214834पूर्ण,
	अणु 0, 162943पूर्ण,
	अणु 5, 124820पूर्ण,
	अणु10,  96520पूर्ण,
	अणु15,  75306पूर्ण,
	अणु20,  59254पूर्ण,
	अणु25,  47000पूर्ण,
	अणु30,  37566पूर्ण,
	अणु35,  30245पूर्ण,
	अणु40,  24520पूर्ण,
	अणु45,  20010पूर्ण,
	अणु50,  16432पूर्ण,
	अणु55,  13576पूर्ण,
	अणु60,  11280पूर्ण,
	अणु65,   9425पूर्ण,
पूर्ण;

/*
 * Note that the batres_vs_temp table must be strictly sorted by falling
 * temperature values to work.
 */
अटल स्थिर काष्ठा batres_vs_temp temp_to_batres_tbl_thermistor[] = अणु
	अणु 40, 120पूर्ण,
	अणु 30, 135पूर्ण,
	अणु 20, 165पूर्ण,
	अणु 10, 230पूर्ण,
	अणु 00, 325पूर्ण,
	अणु-10, 445पूर्ण,
	अणु-20, 595पूर्ण,
पूर्ण;

/*
 * Note that the batres_vs_temp table must be strictly sorted by falling
 * temperature values to work.
 */
अटल स्थिर काष्ठा batres_vs_temp temp_to_batres_tbl_ext_thermistor[] = अणु
	अणु 60, 300पूर्ण,
	अणु 30, 300पूर्ण,
	अणु 20, 300पूर्ण,
	अणु 10, 300पूर्ण,
	अणु 00, 300पूर्ण,
	अणु-10, 300पूर्ण,
	अणु-20, 300पूर्ण,
पूर्ण;

/* battery resistance table क्रम LI ION 9100 battery */
अटल स्थिर काष्ठा batres_vs_temp temp_to_batres_tbl_9100[] = अणु
	अणु 60, 180पूर्ण,
	अणु 30, 180पूर्ण,
	अणु 20, 180पूर्ण,
	अणु 10, 180पूर्ण,
	अणु 00, 180पूर्ण,
	अणु-10, 180पूर्ण,
	अणु-20, 180पूर्ण,
पूर्ण;

अटल काष्ठा abx500_battery_type bat_type_thermistor[] = अणु
	[BATTERY_UNKNOWN] = अणु
		/* First element always represent the UNKNOWN battery */
		.name = POWER_SUPPLY_TECHNOLOGY_UNKNOWN,
		.resis_high = 0,
		.resis_low = 0,
		.battery_resistance = 300,
		.अक्षरge_full_design = 612,
		.nominal_voltage = 3700,
		.termination_vol = 4050,
		.termination_curr = 200,
		.reअक्षरge_cap = 95,
		.normal_cur_lvl = 400,
		.normal_vol_lvl = 4100,
		.मुख्यt_a_cur_lvl = 400,
		.मुख्यt_a_vol_lvl = 4050,
		.मुख्यt_a_chg_समयr_h = 60,
		.मुख्यt_b_cur_lvl = 400,
		.मुख्यt_b_vol_lvl = 4000,
		.मुख्यt_b_chg_समयr_h = 200,
		.low_high_cur_lvl = 300,
		.low_high_vol_lvl = 4000,
		.n_temp_tbl_elements = ARRAY_SIZE(temp_tbl),
		.r_to_t_tbl = temp_tbl,
		.n_v_cap_tbl_elements = ARRAY_SIZE(cap_tbl),
		.v_to_cap_tbl = cap_tbl,
		.n_batres_tbl_elements = ARRAY_SIZE(temp_to_batres_tbl_thermistor),
		.batres_tbl = temp_to_batres_tbl_thermistor,
	पूर्ण,
	अणु
		.name = POWER_SUPPLY_TECHNOLOGY_LIPO,
		.resis_high = 53407,
		.resis_low = 12500,
		.battery_resistance = 300,
		.अक्षरge_full_design = 900,
		.nominal_voltage = 3600,
		.termination_vol = 4150,
		.termination_curr = 80,
		.reअक्षरge_cap = 95,
		.normal_cur_lvl = 700,
		.normal_vol_lvl = 4200,
		.मुख्यt_a_cur_lvl = 600,
		.मुख्यt_a_vol_lvl = 4150,
		.मुख्यt_a_chg_समयr_h = 60,
		.मुख्यt_b_cur_lvl = 600,
		.मुख्यt_b_vol_lvl = 4100,
		.मुख्यt_b_chg_समयr_h = 200,
		.low_high_cur_lvl = 300,
		.low_high_vol_lvl = 4000,
		.n_temp_tbl_elements = ARRAY_SIZE(ab8500_temp_tbl_a_thermistor),
		.r_to_t_tbl = ab8500_temp_tbl_a_thermistor,
		.n_v_cap_tbl_elements = ARRAY_SIZE(cap_tbl_a_thermistor),
		.v_to_cap_tbl = cap_tbl_a_thermistor,
		.n_batres_tbl_elements = ARRAY_SIZE(temp_to_batres_tbl_thermistor),
		.batres_tbl = temp_to_batres_tbl_thermistor,

	पूर्ण,
	अणु
		.name = POWER_SUPPLY_TECHNOLOGY_LIPO,
		.resis_high = 200000,
		.resis_low = 82869,
		.battery_resistance = 300,
		.अक्षरge_full_design = 900,
		.nominal_voltage = 3600,
		.termination_vol = 4150,
		.termination_curr = 80,
		.reअक्षरge_cap = 95,
		.normal_cur_lvl = 700,
		.normal_vol_lvl = 4200,
		.मुख्यt_a_cur_lvl = 600,
		.मुख्यt_a_vol_lvl = 4150,
		.मुख्यt_a_chg_समयr_h = 60,
		.मुख्यt_b_cur_lvl = 600,
		.मुख्यt_b_vol_lvl = 4100,
		.मुख्यt_b_chg_समयr_h = 200,
		.low_high_cur_lvl = 300,
		.low_high_vol_lvl = 4000,
		.n_temp_tbl_elements = ARRAY_SIZE(ab8500_temp_tbl_b_thermistor),
		.r_to_t_tbl = ab8500_temp_tbl_b_thermistor,
		.n_v_cap_tbl_elements = ARRAY_SIZE(cap_tbl_b_thermistor),
		.v_to_cap_tbl = cap_tbl_b_thermistor,
		.n_batres_tbl_elements = ARRAY_SIZE(temp_to_batres_tbl_thermistor),
		.batres_tbl = temp_to_batres_tbl_thermistor,
	पूर्ण,
पूर्ण;

अटल काष्ठा abx500_battery_type bat_type_ext_thermistor[] = अणु
	[BATTERY_UNKNOWN] = अणु
		/* First element always represent the UNKNOWN battery */
		.name = POWER_SUPPLY_TECHNOLOGY_UNKNOWN,
		.resis_high = 0,
		.resis_low = 0,
		.battery_resistance = 300,
		.अक्षरge_full_design = 612,
		.nominal_voltage = 3700,
		.termination_vol = 4050,
		.termination_curr = 200,
		.reअक्षरge_cap = 95,
		.normal_cur_lvl = 400,
		.normal_vol_lvl = 4100,
		.मुख्यt_a_cur_lvl = 400,
		.मुख्यt_a_vol_lvl = 4050,
		.मुख्यt_a_chg_समयr_h = 60,
		.मुख्यt_b_cur_lvl = 400,
		.मुख्यt_b_vol_lvl = 4000,
		.मुख्यt_b_chg_समयr_h = 200,
		.low_high_cur_lvl = 300,
		.low_high_vol_lvl = 4000,
		.n_temp_tbl_elements = ARRAY_SIZE(temp_tbl),
		.r_to_t_tbl = temp_tbl,
		.n_v_cap_tbl_elements = ARRAY_SIZE(cap_tbl),
		.v_to_cap_tbl = cap_tbl,
		.n_batres_tbl_elements = ARRAY_SIZE(temp_to_batres_tbl_thermistor),
		.batres_tbl = temp_to_batres_tbl_thermistor,
	पूर्ण,
/*
 * These are the batteries that करोesn't have an पूर्णांकernal NTC resistor to measure
 * its temperature. The temperature in this हाल is measure with a NTC placed
 * near the battery but on the PCB.
 */
	अणु
		.name = POWER_SUPPLY_TECHNOLOGY_LIPO,
		.resis_high = 76000,
		.resis_low = 53000,
		.battery_resistance = 300,
		.अक्षरge_full_design = 900,
		.nominal_voltage = 3700,
		.termination_vol = 4150,
		.termination_curr = 100,
		.reअक्षरge_cap = 95,
		.normal_cur_lvl = 700,
		.normal_vol_lvl = 4200,
		.मुख्यt_a_cur_lvl = 600,
		.मुख्यt_a_vol_lvl = 4150,
		.मुख्यt_a_chg_समयr_h = 60,
		.मुख्यt_b_cur_lvl = 600,
		.मुख्यt_b_vol_lvl = 4100,
		.मुख्यt_b_chg_समयr_h = 200,
		.low_high_cur_lvl = 300,
		.low_high_vol_lvl = 4000,
		.n_temp_tbl_elements = ARRAY_SIZE(temp_tbl),
		.r_to_t_tbl = temp_tbl,
		.n_v_cap_tbl_elements = ARRAY_SIZE(cap_tbl),
		.v_to_cap_tbl = cap_tbl,
		.n_batres_tbl_elements = ARRAY_SIZE(temp_to_batres_tbl_thermistor),
		.batres_tbl = temp_to_batres_tbl_thermistor,
	पूर्ण,
	अणु
		.name = POWER_SUPPLY_TECHNOLOGY_LION,
		.resis_high = 30000,
		.resis_low = 10000,
		.battery_resistance = 300,
		.अक्षरge_full_design = 950,
		.nominal_voltage = 3700,
		.termination_vol = 4150,
		.termination_curr = 100,
		.reअक्षरge_cap = 95,
		.normal_cur_lvl = 700,
		.normal_vol_lvl = 4200,
		.मुख्यt_a_cur_lvl = 600,
		.मुख्यt_a_vol_lvl = 4150,
		.मुख्यt_a_chg_समयr_h = 60,
		.मुख्यt_b_cur_lvl = 600,
		.मुख्यt_b_vol_lvl = 4100,
		.मुख्यt_b_chg_समयr_h = 200,
		.low_high_cur_lvl = 300,
		.low_high_vol_lvl = 4000,
		.n_temp_tbl_elements = ARRAY_SIZE(temp_tbl),
		.r_to_t_tbl = temp_tbl,
		.n_v_cap_tbl_elements = ARRAY_SIZE(cap_tbl),
		.v_to_cap_tbl = cap_tbl,
		.n_batres_tbl_elements = ARRAY_SIZE(temp_to_batres_tbl_thermistor),
		.batres_tbl = temp_to_batres_tbl_thermistor,
	पूर्ण,
	अणु
		.name = POWER_SUPPLY_TECHNOLOGY_LION,
		.resis_high = 95000,
		.resis_low = 76001,
		.battery_resistance = 300,
		.अक्षरge_full_design = 950,
		.nominal_voltage = 3700,
		.termination_vol = 4150,
		.termination_curr = 100,
		.reअक्षरge_cap = 95,
		.normal_cur_lvl = 700,
		.normal_vol_lvl = 4200,
		.मुख्यt_a_cur_lvl = 600,
		.मुख्यt_a_vol_lvl = 4150,
		.मुख्यt_a_chg_समयr_h = 60,
		.मुख्यt_b_cur_lvl = 600,
		.मुख्यt_b_vol_lvl = 4100,
		.मुख्यt_b_chg_समयr_h = 200,
		.low_high_cur_lvl = 300,
		.low_high_vol_lvl = 4000,
		.n_temp_tbl_elements = ARRAY_SIZE(temp_tbl),
		.r_to_t_tbl = temp_tbl,
		.n_v_cap_tbl_elements = ARRAY_SIZE(cap_tbl),
		.v_to_cap_tbl = cap_tbl,
		.n_batres_tbl_elements = ARRAY_SIZE(temp_to_batres_tbl_thermistor),
		.batres_tbl = temp_to_batres_tbl_thermistor,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा abx500_bm_capacity_levels cap_levels = अणु
	.critical	= 2,
	.low		= 10,
	.normal		= 70,
	.high		= 95,
	.full		= 100,
पूर्ण;

अटल स्थिर काष्ठा abx500_fg_parameters fg = अणु
	.recovery_sleep_समयr = 10,
	.recovery_total_समय = 100,
	.init_समयr = 1,
	.init_discard_समय = 5,
	.init_total_समय = 40,
	.high_curr_समय = 60,
	.accu_अक्षरging = 30,
	.accu_high_curr = 30,
	.high_curr_threshold = 50,
	.lowbat_threshold = 3100,
	.battok_falling_th_sel0 = 2860,
	.battok_raising_th_sel1 = 2860,
	.मुख्यt_thres = 95,
	.user_cap_limit = 15,
	.pcut_enable = 1,
	.pcut_max_समय = 127,
	.pcut_flag_समय = 112,
	.pcut_max_restart = 15,
	.pcut_debounce_समय = 2,
पूर्ण;

अटल स्थिर काष्ठा abx500_maxim_parameters ab8500_maxi_params = अणु
	.ena_maxi = true,
	.chg_curr = 910,
	.रुको_cycles = 10,
	.अक्षरger_curr_step = 100,
पूर्ण;

अटल स्थिर काष्ठा abx500_bm_अक्षरger_parameters chg = अणु
	.usb_volt_max		= 5500,
	.usb_curr_max		= 1500,
	.ac_volt_max		= 7500,
	.ac_curr_max		= 1500,
पूर्ण;

/*
 * This array maps the raw hex value to अक्षरger output current used by the
 * AB8500 values
 */
अटल पूर्णांक ab8500_अक्षरge_output_curr_map[] = अणु
        100,    200,    300,    400,    500,    600,    700,    800,
        900,    1000,   1100,   1200,   1300,   1400,   1500,   1500,
पूर्ण;

/*
 * This array maps the raw hex value to अक्षरger input current used by the
 * AB8500 values
 */
अटल पूर्णांक ab8500_अक्षरge_input_curr_map[] = अणु
        50,     98,     193,    290,    380,    450,    500,    600,
        700,    800,    900,    1000,   1100,   1300,   1400,   1500,
पूर्ण;

काष्ठा abx500_bm_data ab8500_bm_data = अणु
	.temp_under             = 3,
	.temp_low               = 8,
	.temp_high              = 43,
	.temp_over              = 48,
	.मुख्य_safety_पंचांगr_h      = 4,
	.temp_पूर्णांकerval_chg      = 20,
	.temp_पूर्णांकerval_nochg    = 120,
	.usb_safety_पंचांगr_h       = 4,
	.bkup_bat_v             = BUP_VCH_SEL_2P6V,
	.bkup_bat_i             = BUP_ICH_SEL_150UA,
	.no_मुख्यtenance         = false,
	.capacity_scaling       = false,
	.adc_therm              = ABx500_ADC_THERM_BATCTRL,
	.chg_unknown_bat        = false,
	.enable_overshoot       = false,
	.fg_res                 = 100,
	.cap_levels             = &cap_levels,
	.bat_type               = bat_type_thermistor,
	.n_btypes               = ARRAY_SIZE(bat_type_thermistor),
	.batt_id                = 0,
	.पूर्णांकerval_अक्षरging      = 5,
	.पूर्णांकerval_not_अक्षरging  = 120,
	.temp_hysteresis        = 3,
	.gnd_lअगरt_resistance    = 34,
	.chg_output_curr        = ab8500_अक्षरge_output_curr_map,
	.n_chg_out_curr         = ARRAY_SIZE(ab8500_अक्षरge_output_curr_map),
	.maxi                   = &ab8500_maxi_params,
	.chg_params             = &chg,
	.fg_params              = &fg,
        .chg_input_curr         = ab8500_अक्षरge_input_curr_map,
        .n_chg_in_curr          = ARRAY_SIZE(ab8500_अक्षरge_input_curr_map),
पूर्ण;

पूर्णांक ab8500_bm_of_probe(काष्ठा device *dev,
		       काष्ठा device_node *np,
		       काष्ठा abx500_bm_data *bm)
अणु
	स्थिर काष्ठा batres_vs_temp *पंचांगp_batres_tbl;
	काष्ठा device_node *battery_node;
	स्थिर अक्षर *btech;
	पूर्णांक i;

	/* get phandle to 'battery-info' node */
	battery_node = of_parse_phandle(np, "battery", 0);
	अगर (!battery_node) अणु
		dev_err(dev, "battery node or reference missing\n");
		वापस -EINVAL;
	पूर्ण

	btech = of_get_property(battery_node, "stericsson,battery-type", शून्य);
	अगर (!btech) अणु
		dev_warn(dev, "missing property battery-name/type\n");
		of_node_put(battery_node);
		वापस -EINVAL;
	पूर्ण

	अगर (म_भेदन(btech, "LION", 4) == 0) अणु
		bm->no_मुख्यtenance  = true;
		bm->chg_unknown_bat = true;
		bm->bat_type[BATTERY_UNKNOWN].अक्षरge_full_design = 2600;
		bm->bat_type[BATTERY_UNKNOWN].termination_vol    = 4150;
		bm->bat_type[BATTERY_UNKNOWN].reअक्षरge_cap       = 95;
		bm->bat_type[BATTERY_UNKNOWN].normal_cur_lvl     = 520;
		bm->bat_type[BATTERY_UNKNOWN].normal_vol_lvl     = 4200;
	पूर्ण

	अगर (of_property_पढ़ो_bool(battery_node, "thermistor-on-batctrl")) अणु
		अगर (म_भेदन(btech, "LION", 4) == 0)
			पंचांगp_batres_tbl = temp_to_batres_tbl_9100;
		अन्यथा
			पंचांगp_batres_tbl = temp_to_batres_tbl_thermistor;
	पूर्ण अन्यथा अणु
		bm->n_btypes   = 4;
		bm->bat_type   = bat_type_ext_thermistor;
		bm->adc_therm  = ABx500_ADC_THERM_BATTEMP;
		पंचांगp_batres_tbl = temp_to_batres_tbl_ext_thermistor;
	पूर्ण

	/* select the battery resolution table */
	क्रम (i = 0; i < bm->n_btypes; ++i)
		bm->bat_type[i].batres_tbl = पंचांगp_batres_tbl;

	of_node_put(battery_node);

	वापस 0;
पूर्ण
