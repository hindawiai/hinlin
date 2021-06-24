<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 BAIKAL ELECTRONICS, JSC
 *
 * Authors:
 *   Maxim Kaurkin <maxim.kaurkin@baikalelectronics.ru>
 *   Serge Semin <Sergey.Semin@baikalelectronics.ru>
 *
 * Baikal-T1 Process, Voltage, Temperature sensor driver
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#समावेश "bt1-pvt.h"

/*
 * For the sake of the code simplअगरication we created the sensors info table
 * with the sensor names, activation modes, threshold रेजिस्टरs base address
 * and the thresholds bit fields.
 */
अटल स्थिर काष्ठा pvt_sensor_info pvt_info[] = अणु
	PVT_SENSOR_INFO(0, "CPU Core Temperature", hwmon_temp, TEMP, TTHRES),
	PVT_SENSOR_INFO(0, "CPU Core Voltage", hwmon_in, VOLT, VTHRES),
	PVT_SENSOR_INFO(1, "CPU Core Low-Vt", hwmon_in, LVT, LTHRES),
	PVT_SENSOR_INFO(2, "CPU Core High-Vt", hwmon_in, HVT, HTHRES),
	PVT_SENSOR_INFO(3, "CPU Core Standard-Vt", hwmon_in, SVT, STHRES),
पूर्ण;

/*
 * The original translation क्रमmulae of the temperature (in degrees of Celsius)
 * to PVT data and vice-versa are following:
 * N = 1.8322e-8*(T^4) + 2.343e-5*(T^3) + 8.7018e-3*(T^2) + 3.9269*(T^1) +
 *     1.7204e2,
 * T = -1.6743e-11*(N^4) + 8.1542e-8*(N^3) + -1.8201e-4*(N^2) +
 *     3.1020e-1*(N^1) - 4.838e1,
 * where T = [-48.380, 147.438]C and N = [0, 1023].
 * They must be accordingly altered to be suitable क्रम the पूर्णांकeger arithmetics.
 * The technique is called 'factor redistribution', which just makes sure the
 * multiplications and भागisions are made so to have a result of the operations
 * within the पूर्णांकeger numbers limit. In addition we need to translate the
 * क्रमmulae to accept millidegrees of Celsius. Here what they look like after
 * the alterations:
 * N = (18322e-20*(T^4) + 2343e-13*(T^3) + 87018e-9*(T^2) + 39269e-3*T +
 *     17204e2) / 1e4,
 * T = -16743e-12*(D^4) + 81542e-9*(D^3) - 182010e-6*(D^2) + 310200e-3*D -
 *     48380,
 * where T = [-48380, 147438] mC and N = [0, 1023].
 */
अटल स्थिर काष्ठा pvt_poly __maybe_unused poly_temp_to_N = अणु
	.total_भागider = 10000,
	.terms = अणु
		अणु4, 18322, 10000, 10000पूर्ण,
		अणु3, 2343, 10000, 10पूर्ण,
		अणु2, 87018, 10000, 10पूर्ण,
		अणु1, 39269, 1000, 1पूर्ण,
		अणु0, 1720400, 1, 1पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pvt_poly poly_N_to_temp = अणु
	.total_भागider = 1,
	.terms = अणु
		अणु4, -16743, 1000, 1पूर्ण,
		अणु3, 81542, 1000, 1पूर्ण,
		अणु2, -182010, 1000, 1पूर्ण,
		अणु1, 310200, 1000, 1पूर्ण,
		अणु0, -48380, 1, 1पूर्ण
	पूर्ण
पूर्ण;

/*
 * Similar alterations are perक्रमmed क्रम the voltage conversion equations.
 * The original क्रमmulae are:
 * N = 1.8658e3*V - 1.1572e3,
 * V = (N + 1.1572e3) / 1.8658e3,
 * where V = [0.620, 1.168] V and N = [0, 1023].
 * After the optimization they looks as follows:
 * N = (18658e-3*V - 11572) / 10,
 * V = N * 10^5 / 18658 + 11572 * 10^4 / 18658.
 */
अटल स्थिर काष्ठा pvt_poly __maybe_unused poly_volt_to_N = अणु
	.total_भागider = 10,
	.terms = अणु
		अणु1, 18658, 1000, 1पूर्ण,
		अणु0, -11572, 1, 1पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा pvt_poly poly_N_to_volt = अणु
	.total_भागider = 10,
	.terms = अणु
		अणु1, 100000, 18658, 1पूर्ण,
		अणु0, 115720000, 1, 18658पूर्ण
	पूर्ण
पूर्ण;

/*
 * Here is the polynomial calculation function, which perक्रमms the
 * redistributed terms calculations. It's pretty straightक्रमward. We walk
 * over each degree term up to the मुक्त one, and perक्रमm the redistributed
 * multiplication of the term coefficient, its भागider (as क्रम the rationale
 * fraction representation), data घातer and the rational fraction भागider
 * leftover. Then all of this is collected in a total sum variable, which
 * value is normalized by the total भागider beक्रमe being वापसed.
 */
अटल दीर्घ pvt_calc_poly(स्थिर काष्ठा pvt_poly *poly, दीर्घ data)
अणु
	स्थिर काष्ठा pvt_poly_term *term = poly->terms;
	दीर्घ पंचांगp, ret = 0;
	पूर्णांक deg;

	करो अणु
		पंचांगp = term->coef;
		क्रम (deg = 0; deg < term->deg; ++deg)
			पंचांगp = mult_frac(पंचांगp, data, term->भागider);
		ret += पंचांगp / term->भागider_leftover;
	पूर्ण जबतक ((term++)->deg);

	वापस ret / poly->total_भागider;
पूर्ण

अटल अंतरभूत u32 pvt_update(व्योम __iomem *reg, u32 mask, u32 data)
अणु
	u32 old;

	old = पढ़ोl_relaxed(reg);
	ग_लिखोl((old & ~mask) | (data & mask), reg);

	वापस old & mask;
पूर्ण

/*
 * Baikal-T1 PVT mode can be updated only when the controller is disabled.
 * So first we disable it, then set the new mode together with the controller
 * getting back enabled. The same concerns the temperature trim and
 * measurements समयout. If it is necessary the पूर्णांकerface mutex is supposed
 * to be locked at the समय the operations are perक्रमmed.
 */
अटल अंतरभूत व्योम pvt_set_mode(काष्ठा pvt_hwmon *pvt, u32 mode)
अणु
	u32 old;

	mode = FIELD_PREP(PVT_CTRL_MODE_MASK, mode);

	old = pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, 0);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_MODE_MASK | PVT_CTRL_EN,
		   mode | old);
पूर्ण

अटल अंतरभूत u32 pvt_calc_trim(दीर्घ temp)
अणु
	temp = clamp_val(temp, 0, PVT_TRIM_TEMP);

	वापस DIV_ROUND_UP(temp, PVT_TRIM_STEP);
पूर्ण

अटल अंतरभूत व्योम pvt_set_trim(काष्ठा pvt_hwmon *pvt, u32 trim)
अणु
	u32 old;

	trim = FIELD_PREP(PVT_CTRL_TRIM_MASK, trim);

	old = pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, 0);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_TRIM_MASK | PVT_CTRL_EN,
		   trim | old);
पूर्ण

अटल अंतरभूत व्योम pvt_set_tout(काष्ठा pvt_hwmon *pvt, u32 tout)
अणु
	u32 old;

	old = pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, 0);
	ग_लिखोl(tout, pvt->regs + PVT_TTIMEOUT);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, old);
पूर्ण

/*
 * This driver can optionally provide the hwmon alarms क्रम each sensor the PVT
 * controller supports. The alarms functionality is made compile-समय
 * configurable due to the hardware पूर्णांकerface implementation peculiarity
 * described further in this comment. So in हाल अगर alarms are unnecessary in
 * your प्रणाली design it's recommended to have them disabled to prevent the PVT
 * IRQs being periodically उठाओd to get the data cache/alarms status up to
 * date.
 *
 * Baikal-T1 PVT embedded controller is based on the Analog Bits PVT sensor,
 * but is equipped with a dedicated control wrapper. It exposes the PVT
 * sub-block रेजिस्टरs space via the APB3 bus. In addition the wrapper provides
 * a common पूर्णांकerrupt vector of the sensors conversion completion events and
 * threshold value alarms. Alas the wrapper पूर्णांकerface hasn't been fully thought
 * through. There is only one sensor can be activated at a समय, क्रम which the
 * thresholds comparator is enabled right after the data conversion is
 * completed. Due to this अगर alarms need to be implemented क्रम all available
 * sensors we can't just set the thresholds and enable the पूर्णांकerrupts. We need
 * to enable the sensors one after another and let the controller to detect
 * the alarms by itself at each conversion. This also makes poपूर्णांकless to handle
 * the alarms पूर्णांकerrupts, since in occasion they happen synchronously with
 * data conversion completion. The best driver design would be to have the
 * completion पूर्णांकerrupts enabled only and keep the converted value in the
 * driver data cache. This solution is implemented अगर hwmon alarms are enabled
 * in this driver. In हाल अगर the alarms are disabled, the conversion is
 * perक्रमmed on demand at the समय a sensors input file is पढ़ो.
 */

#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)

#घोषणा pvt_hard_isr शून्य

अटल irqवापस_t pvt_soft_isr(पूर्णांक irq, व्योम *data)
अणु
	स्थिर काष्ठा pvt_sensor_info *info;
	काष्ठा pvt_hwmon *pvt = data;
	काष्ठा pvt_cache *cache;
	u32 val, thres_sts, old;

	/*
	 * DVALID bit will be cleared by पढ़ोing the data. We need to save the
	 * status beक्रमe the next conversion happens. Threshold events will be
	 * handled a bit later.
	 */
	thres_sts = पढ़ोl(pvt->regs + PVT_RAW_INTR_STAT);

	/*
	 * Then lets reअक्षरge the PVT पूर्णांकerface with the next sampling mode.
	 * Lock the पूर्णांकerface mutex to serialize trim, समयouts and alarm
	 * thresholds settings.
	 */
	cache = &pvt->cache[pvt->sensor];
	info = &pvt_info[pvt->sensor];
	pvt->sensor = (pvt->sensor == PVT_SENSOR_LAST) ?
		      PVT_SENSOR_FIRST : (pvt->sensor + 1);

	/*
	 * For some reason we have to mask the पूर्णांकerrupt beक्रमe changing the
	 * mode, otherwise someबार the temperature mode करोesn't get
	 * activated even though the actual mode in the ctrl रेजिस्टर
	 * corresponds to one. Then we पढ़ो the data. By करोing so we also
	 * reअक्षरge the data conversion. After this the mode corresponding
	 * to the next sensor in the row is set. Finally we enable the
	 * पूर्णांकerrupts back.
	 */
	mutex_lock(&pvt->अगरace_mtx);

	old = pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_DVALID,
			 PVT_INTR_DVALID);

	val = पढ़ोl(pvt->regs + PVT_DATA);

	pvt_set_mode(pvt, pvt_info[pvt->sensor].mode);

	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_DVALID, old);

	mutex_unlock(&pvt->अगरace_mtx);

	/*
	 * We can now update the data cache with data just retrieved from the
	 * sensor. Lock ग_लिखो-seqlock to make sure the पढ़ोer has a coherent
	 * data.
	 */
	ग_लिखो_seqlock(&cache->data_seqlock);

	cache->data = FIELD_GET(PVT_DATA_DATA_MASK, val);

	ग_लिखो_sequnlock(&cache->data_seqlock);

	/*
	 * While PVT core is करोing the next mode data conversion, we'll check
	 * whether the alarms were triggered क्रम the current sensor. Note that
	 * according to the करोcumentation only one threshold IRQ status can be
	 * set at a समय, that's why अगर-अन्यथा statement is utilized.
	 */
	अगर ((thres_sts & info->thres_sts_lo) ^ cache->thres_sts_lo) अणु
		WRITE_ONCE(cache->thres_sts_lo, thres_sts & info->thres_sts_lo);
		hwmon_notअगरy_event(pvt->hwmon, info->type, info->attr_min_alarm,
				   info->channel);
	पूर्ण अन्यथा अगर ((thres_sts & info->thres_sts_hi) ^ cache->thres_sts_hi) अणु
		WRITE_ONCE(cache->thres_sts_hi, thres_sts & info->thres_sts_hi);
		hwmon_notअगरy_event(pvt->hwmon, info->type, info->attr_max_alarm,
				   info->channel);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत umode_t pvt_limit_is_visible(क्रमागत pvt_sensor_type type)
अणु
	वापस 0644;
पूर्ण

अटल अंतरभूत umode_t pvt_alarm_is_visible(क्रमागत pvt_sensor_type type)
अणु
	वापस 0444;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_data(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			 दीर्घ *val)
अणु
	काष्ठा pvt_cache *cache = &pvt->cache[type];
	अचिन्हित पूर्णांक seq;
	u32 data;

	करो अणु
		seq = पढ़ो_seqbegin(&cache->data_seqlock);
		data = cache->data;
	पूर्ण जबतक (पढ़ो_seqretry(&cache->data_seqlock, seq));

	अगर (type == PVT_TEMP)
		*val = pvt_calc_poly(&poly_N_to_temp, data);
	अन्यथा
		*val = pvt_calc_poly(&poly_N_to_volt, data);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_limit(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			  bool is_low, दीर्घ *val)
अणु
	u32 data;

	/* No need in serialization, since it is just पढ़ो from MMIO. */
	data = पढ़ोl(pvt->regs + pvt_info[type].thres_base);

	अगर (is_low)
		data = FIELD_GET(PVT_THRES_LO_MASK, data);
	अन्यथा
		data = FIELD_GET(PVT_THRES_HI_MASK, data);

	अगर (type == PVT_TEMP)
		*val = pvt_calc_poly(&poly_N_to_temp, data);
	अन्यथा
		*val = pvt_calc_poly(&poly_N_to_volt, data);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_ग_लिखो_limit(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			   bool is_low, दीर्घ val)
अणु
	u32 data, limit, mask;
	पूर्णांक ret;

	अगर (type == PVT_TEMP) अणु
		val = clamp(val, PVT_TEMP_MIN, PVT_TEMP_MAX);
		data = pvt_calc_poly(&poly_temp_to_N, val);
	पूर्ण अन्यथा अणु
		val = clamp(val, PVT_VOLT_MIN, PVT_VOLT_MAX);
		data = pvt_calc_poly(&poly_volt_to_N, val);
	पूर्ण

	/* Serialize limit update, since a part of the रेजिस्टर is changed. */
	ret = mutex_lock_पूर्णांकerruptible(&pvt->अगरace_mtx);
	अगर (ret)
		वापस ret;

	/* Make sure the upper and lower ranges करोn't पूर्णांकersect. */
	limit = पढ़ोl(pvt->regs + pvt_info[type].thres_base);
	अगर (is_low) अणु
		limit = FIELD_GET(PVT_THRES_HI_MASK, limit);
		data = clamp_val(data, PVT_DATA_MIN, limit);
		data = FIELD_PREP(PVT_THRES_LO_MASK, data);
		mask = PVT_THRES_LO_MASK;
	पूर्ण अन्यथा अणु
		limit = FIELD_GET(PVT_THRES_LO_MASK, limit);
		data = clamp_val(data, limit, PVT_DATA_MAX);
		data = FIELD_PREP(PVT_THRES_HI_MASK, data);
		mask = PVT_THRES_HI_MASK;
	पूर्ण

	pvt_update(pvt->regs + pvt_info[type].thres_base, mask, data);

	mutex_unlock(&pvt->अगरace_mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_alarm(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			  bool is_low, दीर्घ *val)
अणु
	अगर (is_low)
		*val = !!READ_ONCE(pvt->cache[type].thres_sts_lo);
	अन्यथा
		*val = !!READ_ONCE(pvt->cache[type].thres_sts_hi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *pvt_channel_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ | HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_TYPE | HWMON_T_LABEL |
			   HWMON_T_MIN | HWMON_T_MIN_ALARM |
			   HWMON_T_MAX | HWMON_T_MAX_ALARM |
			   HWMON_T_OFFSET),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LABEL |
			   HWMON_I_MIN | HWMON_I_MIN_ALARM |
			   HWMON_I_MAX | HWMON_I_MAX_ALARM,
			   HWMON_I_INPUT | HWMON_I_LABEL |
			   HWMON_I_MIN | HWMON_I_MIN_ALARM |
			   HWMON_I_MAX | HWMON_I_MAX_ALARM,
			   HWMON_I_INPUT | HWMON_I_LABEL |
			   HWMON_I_MIN | HWMON_I_MIN_ALARM |
			   HWMON_I_MAX | HWMON_I_MAX_ALARM,
			   HWMON_I_INPUT | HWMON_I_LABEL |
			   HWMON_I_MIN | HWMON_I_MIN_ALARM |
			   HWMON_I_MAX | HWMON_I_MAX_ALARM),
	शून्य
पूर्ण;

#अन्यथा /* !CONFIG_SENSORS_BT1_PVT_ALARMS */

अटल irqवापस_t pvt_hard_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pvt_hwmon *pvt = data;
	काष्ठा pvt_cache *cache;
	u32 val;

	/*
	 * Mask the DVALID पूर्णांकerrupt so after निकासing from the handler a
	 * repeated conversion wouldn't happen.
	 */
	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_DVALID,
		   PVT_INTR_DVALID);

	/*
	 * Nothing special क्रम alarm-less driver. Just पढ़ो the data, update
	 * the cache and notअगरy a रुकोer of this event.
	 */
	val = पढ़ोl(pvt->regs + PVT_DATA);
	अगर (!(val & PVT_DATA_VALID)) अणु
		dev_err(pvt->dev, "Got IRQ when data isn't valid\n");
		वापस IRQ_HANDLED;
	पूर्ण

	cache = &pvt->cache[pvt->sensor];

	WRITE_ONCE(cache->data, FIELD_GET(PVT_DATA_DATA_MASK, val));

	complete(&cache->conversion);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा pvt_soft_isr शून्य

अटल अंतरभूत umode_t pvt_limit_is_visible(क्रमागत pvt_sensor_type type)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत umode_t pvt_alarm_is_visible(क्रमागत pvt_sensor_type type)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_data(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			 दीर्घ *val)
अणु
	काष्ठा pvt_cache *cache = &pvt->cache[type];
	अचिन्हित दीर्घ समयout;
	u32 data;
	पूर्णांक ret;

	/*
	 * Lock PVT conversion पूर्णांकerface until data cache is updated. The
	 * data पढ़ो procedure is following: set the requested PVT sensor
	 * mode, enable IRQ and conversion, रुको until conversion is finished,
	 * then disable conversion and IRQ, and पढ़ो the cached data.
	 */
	ret = mutex_lock_पूर्णांकerruptible(&pvt->अगरace_mtx);
	अगर (ret)
		वापस ret;

	pvt->sensor = type;
	pvt_set_mode(pvt, pvt_info[type].mode);

	/*
	 * Unmask the DVALID पूर्णांकerrupt and enable the sensors conversions.
	 * Do the reverse procedure when conversion is करोne.
	 */
	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_DVALID, 0);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, PVT_CTRL_EN);

	/*
	 * Wait with समयout since in हाल अगर the sensor is suddenly घातered
	 * करोwn the request won't be completed and the caller will hang up on
	 * this procedure until the घातer is back up again. Multiply the
	 * समयout by the factor of two to prevent a false समयout.
	 */
	समयout = 2 * usecs_to_jअगरfies(kसमय_प्रकारo_us(pvt->समयout));
	ret = रुको_क्रम_completion_समयout(&cache->conversion, समयout);

	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, 0);
	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_DVALID,
		   PVT_INTR_DVALID);

	data = READ_ONCE(cache->data);

	mutex_unlock(&pvt->अगरace_mtx);

	अगर (!ret)
		वापस -ETIMEDOUT;

	अगर (type == PVT_TEMP)
		*val = pvt_calc_poly(&poly_N_to_temp, data);
	अन्यथा
		*val = pvt_calc_poly(&poly_N_to_volt, data);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_limit(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			  bool is_low, दीर्घ *val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pvt_ग_लिखो_limit(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			   bool is_low, दीर्घ val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_alarm(काष्ठा pvt_hwmon *pvt, क्रमागत pvt_sensor_type type,
			  bool is_low, दीर्घ *val)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *pvt_channel_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ | HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_TYPE | HWMON_T_LABEL |
			   HWMON_T_OFFSET),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL),
	शून्य
पूर्ण;

#पूर्ण_अगर /* !CONFIG_SENSORS_BT1_PVT_ALARMS */

अटल अंतरभूत bool pvt_hwmon_channel_is_valid(क्रमागत hwmon_sensor_types type,
					      पूर्णांक ch)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		अगर (ch < 0 || ch >= PVT_TEMP_CHS)
			वापस false;
		अवरोध;
	हाल hwmon_in:
		अगर (ch < 0 || ch >= PVT_VOLT_CHS)
			वापस false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* The rest of the types are independent from the channel number. */
	वापस true;
पूर्ण

अटल umode_t pvt_hwmon_is_visible(स्थिर व्योम *data,
				    क्रमागत hwmon_sensor_types type,
				    u32 attr, पूर्णांक ch)
अणु
	अगर (!pvt_hwmon_channel_is_valid(type, ch))
		वापस 0;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_type:
		हाल hwmon_temp_label:
			वापस 0444;
		हाल hwmon_temp_min:
		हाल hwmon_temp_max:
			वापस pvt_limit_is_visible(ch);
		हाल hwmon_temp_min_alarm:
		हाल hwmon_temp_max_alarm:
			वापस pvt_alarm_is_visible(ch);
		हाल hwmon_temp_offset:
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_label:
			वापस 0444;
		हाल hwmon_in_min:
		हाल hwmon_in_max:
			वापस pvt_limit_is_visible(PVT_VOLT + ch);
		हाल hwmon_in_min_alarm:
		हाल hwmon_in_max_alarm:
			वापस pvt_alarm_is_visible(PVT_VOLT + ch);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_trim(काष्ठा pvt_hwmon *pvt, दीर्घ *val)
अणु
	u32 data;

	data = पढ़ोl(pvt->regs + PVT_CTRL);
	*val = FIELD_GET(PVT_CTRL_TRIM_MASK, data) * PVT_TRIM_STEP;

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_ग_लिखो_trim(काष्ठा pvt_hwmon *pvt, दीर्घ val)
अणु
	u32 trim;
	पूर्णांक ret;

	/*
	 * Serialize trim update, since a part of the रेजिस्टर is changed and
	 * the controller is supposed to be disabled during this operation.
	 */
	ret = mutex_lock_पूर्णांकerruptible(&pvt->अगरace_mtx);
	अगर (ret)
		वापस ret;

	trim = pvt_calc_trim(val);
	pvt_set_trim(pvt, trim);

	mutex_unlock(&pvt->अगरace_mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_पढ़ो_समयout(काष्ठा pvt_hwmon *pvt, दीर्घ *val)
अणु
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&pvt->अगरace_mtx);
	अगर (ret)
		वापस ret;

	/* Return the result in msec as hwmon sysfs पूर्णांकerface requires. */
	*val = kसमय_प्रकारo_ms(pvt->समयout);

	mutex_unlock(&pvt->अगरace_mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_ग_लिखो_समयout(काष्ठा pvt_hwmon *pvt, दीर्घ val)
अणु
	अचिन्हित दीर्घ rate;
	kसमय_प्रकार kt, cache;
	u32 data;
	पूर्णांक ret;

	rate = clk_get_rate(pvt->clks[PVT_CLOCK_REF].clk);
	अगर (!rate)
		वापस -ENODEV;

	/*
	 * If alarms are enabled, the requested समयout must be भागided
	 * between all available sensors to have the requested delay
	 * applicable to each inभागidual sensor.
	 */
	cache = kt = ms_to_kसमय(val);
#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)
	kt = kसमय_भागns(kt, PVT_SENSORS_NUM);
#पूर्ण_अगर

	/*
	 * Subtract a स्थिरant lag, which always persists due to the limited
	 * PVT sampling rate. Make sure the समयout is not negative.
	 */
	kt = kसमय_sub_ns(kt, PVT_TOUT_MIN);
	अगर (kसमय_प्रकारo_ns(kt) < 0)
		kt = kसमय_set(0, 0);

	/*
	 * Finally recalculate the समयout in terms of the reference घड़ी
	 * period.
	 */
	data = kसमय_भागns(kt * rate, NSEC_PER_SEC);

	/*
	 * Update the measurements delay, but lock the पूर्णांकerface first, since
	 * we have to disable PVT in order to have the new delay actually
	 * updated.
	 */
	ret = mutex_lock_पूर्णांकerruptible(&pvt->अगरace_mtx);
	अगर (ret)
		वापस ret;

	pvt_set_tout(pvt, data);
	pvt->समयout = cache;

	mutex_unlock(&pvt->अगरace_mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			  u32 attr, पूर्णांक ch, दीर्घ *val)
अणु
	काष्ठा pvt_hwmon *pvt = dev_get_drvdata(dev);

	अगर (!pvt_hwmon_channel_is_valid(type, ch))
		वापस -EINVAL;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			वापस pvt_पढ़ो_समयout(pvt, val);
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस pvt_पढ़ो_data(pvt, ch, val);
		हाल hwmon_temp_type:
			*val = 1;
			वापस 0;
		हाल hwmon_temp_min:
			वापस pvt_पढ़ो_limit(pvt, ch, true, val);
		हाल hwmon_temp_max:
			वापस pvt_पढ़ो_limit(pvt, ch, false, val);
		हाल hwmon_temp_min_alarm:
			वापस pvt_पढ़ो_alarm(pvt, ch, true, val);
		हाल hwmon_temp_max_alarm:
			वापस pvt_पढ़ो_alarm(pvt, ch, false, val);
		हाल hwmon_temp_offset:
			वापस pvt_पढ़ो_trim(pvt, val);
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
			वापस pvt_पढ़ो_data(pvt, PVT_VOLT + ch, val);
		हाल hwmon_in_min:
			वापस pvt_पढ़ो_limit(pvt, PVT_VOLT + ch, true, val);
		हाल hwmon_in_max:
			वापस pvt_पढ़ो_limit(pvt, PVT_VOLT + ch, false, val);
		हाल hwmon_in_min_alarm:
			वापस pvt_पढ़ो_alarm(pvt, PVT_VOLT + ch, true, val);
		हाल hwmon_in_max_alarm:
			वापस pvt_पढ़ो_alarm(pvt, PVT_VOLT + ch, false, val);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pvt_hwmon_पढ़ो_string(काष्ठा device *dev,
				 क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक ch, स्थिर अक्षर **str)
अणु
	अगर (!pvt_hwmon_channel_is_valid(type, ch))
		वापस -EINVAL;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_label:
			*str = pvt_info[ch].label;
			वापस 0;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_label:
			*str = pvt_info[PVT_VOLT + ch].label;
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक pvt_hwmon_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			   u32 attr, पूर्णांक ch, दीर्घ val)
अणु
	काष्ठा pvt_hwmon *pvt = dev_get_drvdata(dev);

	अगर (!pvt_hwmon_channel_is_valid(type, ch))
		वापस -EINVAL;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			वापस pvt_ग_लिखो_समयout(pvt, val);
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_min:
			वापस pvt_ग_लिखो_limit(pvt, ch, true, val);
		हाल hwmon_temp_max:
			वापस pvt_ग_लिखो_limit(pvt, ch, false, val);
		हाल hwmon_temp_offset:
			वापस pvt_ग_लिखो_trim(pvt, val);
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_min:
			वापस pvt_ग_लिखो_limit(pvt, PVT_VOLT + ch, true, val);
		हाल hwmon_in_max:
			वापस pvt_ग_लिखो_limit(pvt, PVT_VOLT + ch, false, val);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops pvt_hwmon_ops = अणु
	.is_visible = pvt_hwmon_is_visible,
	.पढ़ो = pvt_hwmon_पढ़ो,
	.पढ़ो_string = pvt_hwmon_पढ़ो_string,
	.ग_लिखो = pvt_hwmon_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info pvt_hwmon_info = अणु
	.ops = &pvt_hwmon_ops,
	.info = pvt_channel_info
पूर्ण;

अटल व्योम pvt_clear_data(व्योम *data)
अणु
	काष्ठा pvt_hwmon *pvt = data;
#अगर !defined(CONFIG_SENSORS_BT1_PVT_ALARMS)
	पूर्णांक idx;

	क्रम (idx = 0; idx < PVT_SENSORS_NUM; ++idx)
		complete_all(&pvt->cache[idx].conversion);
#पूर्ण_अगर

	mutex_destroy(&pvt->अगरace_mtx);
पूर्ण

अटल काष्ठा pvt_hwmon *pvt_create_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pvt_hwmon *pvt;
	पूर्णांक ret, idx;

	pvt = devm_kzalloc(dev, माप(*pvt), GFP_KERNEL);
	अगर (!pvt)
		वापस ERR_PTR(-ENOMEM);

	ret = devm_add_action(dev, pvt_clear_data, pvt);
	अगर (ret) अणु
		dev_err(dev, "Can't add PVT data clear action\n");
		वापस ERR_PTR(ret);
	पूर्ण

	pvt->dev = dev;
	pvt->sensor = PVT_SENSOR_FIRST;
	mutex_init(&pvt->अगरace_mtx);

#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)
	क्रम (idx = 0; idx < PVT_SENSORS_NUM; ++idx)
		seqlock_init(&pvt->cache[idx].data_seqlock);
#अन्यथा
	क्रम (idx = 0; idx < PVT_SENSORS_NUM; ++idx)
		init_completion(&pvt->cache[idx].conversion);
#पूर्ण_अगर

	वापस pvt;
पूर्ण

अटल पूर्णांक pvt_request_regs(काष्ठा pvt_hwmon *pvt)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(pvt->dev);
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(pvt->dev, "Couldn't find PVT memresource\n");
		वापस -EINVAL;
	पूर्ण

	pvt->regs = devm_ioremap_resource(pvt->dev, res);
	अगर (IS_ERR(pvt->regs)) अणु
		dev_err(pvt->dev, "Couldn't map PVT registers\n");
		वापस PTR_ERR(pvt->regs);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pvt_disable_clks(व्योम *data)
अणु
	काष्ठा pvt_hwmon *pvt = data;

	clk_bulk_disable_unprepare(PVT_CLOCK_NUM, pvt->clks);
पूर्ण

अटल पूर्णांक pvt_request_clks(काष्ठा pvt_hwmon *pvt)
अणु
	पूर्णांक ret;

	pvt->clks[PVT_CLOCK_APB].id = "pclk";
	pvt->clks[PVT_CLOCK_REF].id = "ref";

	ret = devm_clk_bulk_get(pvt->dev, PVT_CLOCK_NUM, pvt->clks);
	अगर (ret) अणु
		dev_err(pvt->dev, "Couldn't get PVT clocks descriptors\n");
		वापस ret;
	पूर्ण

	ret = clk_bulk_prepare_enable(PVT_CLOCK_NUM, pvt->clks);
	अगर (ret) अणु
		dev_err(pvt->dev, "Couldn't enable the PVT clocks\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(pvt->dev, pvt_disable_clks, pvt);
	अगर (ret) अणु
		dev_err(pvt->dev, "Can't add PVT clocks disable action\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_check_pwr(काष्ठा pvt_hwmon *pvt)
अणु
	अचिन्हित दीर्घ tout;
	पूर्णांक ret = 0;
	u32 data;

	/*
	 * Test out the sensor conversion functionality. If it is not करोne on
	 * समय then the करोमुख्य must have been unघातered and we won't be able
	 * to use the device later in this driver.
	 * Note If the घातer source is lost during the normal driver work the
	 * data पढ़ो procedure will either वापस -ETIMEDOUT (क्रम the
	 * alarm-less driver configuration) or just stop the repeated
	 * conversion. In the later हाल alas we won't be able to detect the
	 * problem.
	 */
	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_ALL, PVT_INTR_ALL);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, PVT_CTRL_EN);
	pvt_set_tout(pvt, 0);
	पढ़ोl(pvt->regs + PVT_DATA);

	tout = PVT_TOUT_MIN / NSEC_PER_USEC;
	usleep_range(tout, 2 * tout);

	data = पढ़ोl(pvt->regs + PVT_DATA);
	अगर (!(data & PVT_DATA_VALID)) अणु
		ret = -ENODEV;
		dev_err(pvt->dev, "Sensor is powered down\n");
	पूर्ण

	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक pvt_init_अगरace(काष्ठा pvt_hwmon *pvt)
अणु
	अचिन्हित दीर्घ rate;
	u32 trim, temp;

	rate = clk_get_rate(pvt->clks[PVT_CLOCK_REF].clk);
	अगर (!rate) अणु
		dev_err(pvt->dev, "Invalid reference clock rate\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * Make sure all पूर्णांकerrupts and controller are disabled so not to
	 * accidentally have ISR executed beक्रमe the driver data is fully
	 * initialized. Clear the IRQ status as well.
	 */
	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_ALL, PVT_INTR_ALL);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, 0);
	पढ़ोl(pvt->regs + PVT_CLR_INTR);
	पढ़ोl(pvt->regs + PVT_DATA);

	/* Setup शेष sensor mode, समयout and temperature trim. */
	pvt_set_mode(pvt, pvt_info[pvt->sensor].mode);
	pvt_set_tout(pvt, PVT_TOUT_DEF);

	/*
	 * Preserve the current ref-घड़ी based delay (Ttotal) between the
	 * sensors data samples in the driver data so not to recalculate it
	 * each समय on the data requests and समयout पढ़ोs. It consists of the
	 * delay पूर्णांकroduced by the पूर्णांकernal ref-घड़ी समयr (N / Fclk) and the
	 * स्थिरant समयout caused by each conversion latency (Tmin):
	 *   Ttotal = N / Fclk + Tmin
	 * If alarms are enabled the sensors are polled one after another and
	 * in order to get the next measurement of a particular sensor the
	 * caller will have to रुको क्रम at most until all the others are
	 * polled. In that हाल the क्रमmulae will look a bit dअगरferent:
	 *   Ttotal = 5 * (N / Fclk + Tmin)
	 */
#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)
	pvt->समयout = kसमय_set(PVT_SENSORS_NUM * PVT_TOUT_DEF, 0);
	pvt->समयout = kसमय_भागns(pvt->समयout, rate);
	pvt->समयout = kसमय_add_ns(pvt->समयout, PVT_SENSORS_NUM * PVT_TOUT_MIN);
#अन्यथा
	pvt->समयout = kसमय_set(PVT_TOUT_DEF, 0);
	pvt->समयout = kसमय_भागns(pvt->समयout, rate);
	pvt->समयout = kसमय_add_ns(pvt->समयout, PVT_TOUT_MIN);
#पूर्ण_अगर

	trim = PVT_TRIM_DEF;
	अगर (!of_property_पढ़ो_u32(pvt->dev->of_node,
	     "baikal,pvt-temp-offset-millicelsius", &temp))
		trim = pvt_calc_trim(temp);

	pvt_set_trim(pvt, trim);

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_request_irq(काष्ठा pvt_hwmon *pvt)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(pvt->dev);
	पूर्णांक ret;

	pvt->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pvt->irq < 0)
		वापस pvt->irq;

	ret = devm_request_thपढ़ोed_irq(pvt->dev, pvt->irq,
					pvt_hard_isr, pvt_soft_isr,
#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)
					IRQF_SHARED | IRQF_TRIGGER_HIGH |
					IRQF_ONESHOT,
#अन्यथा
					IRQF_SHARED | IRQF_TRIGGER_HIGH,
#पूर्ण_अगर
					"pvt", pvt);
	अगर (ret) अणु
		dev_err(pvt->dev, "Couldn't request PVT IRQ\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pvt_create_hwmon(काष्ठा pvt_hwmon *pvt)
अणु
	pvt->hwmon = devm_hwmon_device_रेजिस्टर_with_info(pvt->dev, "pvt", pvt,
		&pvt_hwmon_info, शून्य);
	अगर (IS_ERR(pvt->hwmon)) अणु
		dev_err(pvt->dev, "Couldn't create hwmon device\n");
		वापस PTR_ERR(pvt->hwmon);
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_SENSORS_BT1_PVT_ALARMS)

अटल व्योम pvt_disable_अगरace(व्योम *data)
अणु
	काष्ठा pvt_hwmon *pvt = data;

	mutex_lock(&pvt->अगरace_mtx);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, 0);
	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_DVALID,
		   PVT_INTR_DVALID);
	mutex_unlock(&pvt->अगरace_mtx);
पूर्ण

अटल पूर्णांक pvt_enable_अगरace(काष्ठा pvt_hwmon *pvt)
अणु
	पूर्णांक ret;

	ret = devm_add_action(pvt->dev, pvt_disable_अगरace, pvt);
	अगर (ret) अणु
		dev_err(pvt->dev, "Can't add PVT disable interface action\n");
		वापस ret;
	पूर्ण

	/*
	 * Enable sensors data conversion and IRQ. We need to lock the
	 * पूर्णांकerface mutex since hwmon has just been created and the
	 * corresponding sysfs files are accessible from user-space,
	 * which theoretically may cause races.
	 */
	mutex_lock(&pvt->अगरace_mtx);
	pvt_update(pvt->regs + PVT_INTR_MASK, PVT_INTR_DVALID, 0);
	pvt_update(pvt->regs + PVT_CTRL, PVT_CTRL_EN, PVT_CTRL_EN);
	mutex_unlock(&pvt->अगरace_mtx);

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_SENSORS_BT1_PVT_ALARMS */

अटल पूर्णांक pvt_enable_अगरace(काष्ठा pvt_hwmon *pvt)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_SENSORS_BT1_PVT_ALARMS */

अटल पूर्णांक pvt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pvt_hwmon *pvt;
	पूर्णांक ret;

	pvt = pvt_create_data(pdev);
	अगर (IS_ERR(pvt))
		वापस PTR_ERR(pvt);

	ret = pvt_request_regs(pvt);
	अगर (ret)
		वापस ret;

	ret = pvt_request_clks(pvt);
	अगर (ret)
		वापस ret;

	ret = pvt_check_pwr(pvt);
	अगर (ret)
		वापस ret;

	ret = pvt_init_अगरace(pvt);
	अगर (ret)
		वापस ret;

	ret = pvt_request_irq(pvt);
	अगर (ret)
		वापस ret;

	ret = pvt_create_hwmon(pvt);
	अगर (ret)
		वापस ret;

	ret = pvt_enable_अगरace(pvt);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pvt_of_match[] = अणु
	अणु .compatible = "baikal,bt1-pvt" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pvt_of_match);

अटल काष्ठा platक्रमm_driver pvt_driver = अणु
	.probe = pvt_probe,
	.driver = अणु
		.name = "bt1-pvt",
		.of_match_table = pvt_of_match
	पूर्ण
पूर्ण;
module_platक्रमm_driver(pvt_driver);

MODULE_AUTHOR("Maxim Kaurkin <maxim.kaurkin@baikalelectronics.ru>");
MODULE_DESCRIPTION("Baikal-T1 PVT driver");
MODULE_LICENSE("GPL v2");
