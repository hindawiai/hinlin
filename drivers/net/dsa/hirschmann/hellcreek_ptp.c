<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * DSA driver क्रम:
 * Hirschmann Hellcreek TSN चयन.
 *
 * Copyright (C) 2019,2020 Hochschule Offenburg
 * Copyright (C) 2019,2020 Linutronix GmbH
 * Authors: Kamil Alkhouri <kamil.alkhouri@hs-offenburg.de>
 *	    Kurt Kanzenbach <kurt@linutronix.de>
 */

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश "hellcreek.h"
#समावेश "hellcreek_ptp.h"
#समावेश "hellcreek_hwtstamp.h"

u16 hellcreek_ptp_पढ़ो(काष्ठा hellcreek *hellcreek, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोw(hellcreek->ptp_base + offset);
पूर्ण

व्योम hellcreek_ptp_ग_लिखो(काष्ठा hellcreek *hellcreek, u16 data,
			 अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोw(data, hellcreek->ptp_base + offset);
पूर्ण

/* Get nanoseconds from PTP घड़ी */
अटल u64 hellcreek_ptp_घड़ी_पढ़ो(काष्ठा hellcreek *hellcreek)
अणु
	u16 nsl, nsh;

	/* Take a snapshot */
	hellcreek_ptp_ग_लिखो(hellcreek, PR_COMMAND_C_SS, PR_COMMAND_C);

	/* The समय of the day is saved as 96 bits. However, due to hardware
	 * limitations the seconds are not or only partly kept in the PTP
	 * core. Currently only three bits क्रम the seconds are available. That's
	 * why only the nanoseconds are used and the seconds are tracked in
	 * software. Anyway due to पूर्णांकernal locking all five रेजिस्टरs should be
	 * पढ़ो.
	 */
	nsh = hellcreek_ptp_पढ़ो(hellcreek, PR_SS_SYNC_DATA_C);
	nsh = hellcreek_ptp_पढ़ो(hellcreek, PR_SS_SYNC_DATA_C);
	nsh = hellcreek_ptp_पढ़ो(hellcreek, PR_SS_SYNC_DATA_C);
	nsh = hellcreek_ptp_पढ़ो(hellcreek, PR_SS_SYNC_DATA_C);
	nsl = hellcreek_ptp_पढ़ो(hellcreek, PR_SS_SYNC_DATA_C);

	वापस (u64)nsl | ((u64)nsh << 16);
पूर्ण

अटल u64 __hellcreek_ptp_समय_लो(काष्ठा hellcreek *hellcreek)
अणु
	u64 ns;

	ns = hellcreek_ptp_घड़ी_पढ़ो(hellcreek);
	अगर (ns < hellcreek->last_ts)
		hellcreek->seconds++;
	hellcreek->last_ts = ns;
	ns += hellcreek->seconds * NSEC_PER_SEC;

	वापस ns;
पूर्ण

/* Retrieve the seconds parts in nanoseconds क्रम a packet बारtamped with @ns.
 * There has to be a check whether an overflow occurred between the packet
 * arrival and now. If so use the correct seconds (-1) क्रम calculating the
 * packet arrival समय.
 */
u64 hellcreek_ptp_समय_लो_seconds(काष्ठा hellcreek *hellcreek, u64 ns)
अणु
	u64 s;

	__hellcreek_ptp_समय_लो(hellcreek);
	अगर (hellcreek->last_ts > ns)
		s = hellcreek->seconds * NSEC_PER_SEC;
	अन्यथा
		s = (hellcreek->seconds - 1) * NSEC_PER_SEC;

	वापस s;
पूर्ण

अटल पूर्णांक hellcreek_ptp_समय_लो(काष्ठा ptp_घड़ी_info *ptp,
				 काष्ठा बारpec64 *ts)
अणु
	काष्ठा hellcreek *hellcreek = ptp_to_hellcreek(ptp);
	u64 ns;

	mutex_lock(&hellcreek->ptp_lock);
	ns = __hellcreek_ptp_समय_लो(hellcreek);
	mutex_unlock(&hellcreek->ptp_lock);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
				 स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा hellcreek *hellcreek = ptp_to_hellcreek(ptp);
	u16 secl, nsh, nsl;

	secl = ts->tv_sec & 0xffff;
	nsh  = ((u32)ts->tv_nsec & 0xffff0000) >> 16;
	nsl  = ts->tv_nsec & 0xffff;

	mutex_lock(&hellcreek->ptp_lock);

	/* Update overflow data काष्ठाure */
	hellcreek->seconds = ts->tv_sec;
	hellcreek->last_ts = ts->tv_nsec;

	/* Set समय in घड़ी */
	hellcreek_ptp_ग_लिखो(hellcreek, 0x00, PR_CLOCK_WRITE_C);
	hellcreek_ptp_ग_लिखो(hellcreek, 0x00, PR_CLOCK_WRITE_C);
	hellcreek_ptp_ग_लिखो(hellcreek, secl, PR_CLOCK_WRITE_C);
	hellcreek_ptp_ग_लिखो(hellcreek, nsh,  PR_CLOCK_WRITE_C);
	hellcreek_ptp_ग_लिखो(hellcreek, nsl,  PR_CLOCK_WRITE_C);

	mutex_unlock(&hellcreek->ptp_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा hellcreek *hellcreek = ptp_to_hellcreek(ptp);
	u16 negative = 0, addendh, addendl;
	u32 addend;
	u64 adj;

	अगर (scaled_ppm < 0) अणु
		negative = 1;
		scaled_ppm = -scaled_ppm;
	पूर्ण

	/* IP-Core adjusts the nominal frequency by adding or subtracting 1 ns
	 * from the 8 ns (period of the oscillator) every समय the accumulator
	 * रेजिस्टर overflows. The value stored in the addend रेजिस्टर is added
	 * to the accumulator रेजिस्टर every 8 ns.
	 *
	 * addend value = (2^30 * accumulator_overflow_rate) /
	 *                oscillator_frequency
	 * where:
	 *
	 * oscillator_frequency = 125 MHz
	 * accumulator_overflow_rate = 125 MHz * scaled_ppm * 2^-16 * 10^-6 * 8
	 */
	adj = scaled_ppm;
	adj <<= 11;
	addend = (u32)भाग_u64(adj, 15625);

	addendh = (addend & 0xffff0000) >> 16;
	addendl = addend & 0xffff;

	negative = (negative << 15) & 0x8000;

	mutex_lock(&hellcreek->ptp_lock);

	/* Set drअगरt रेजिस्टर */
	hellcreek_ptp_ग_लिखो(hellcreek, negative, PR_CLOCK_DRIFT_C);
	hellcreek_ptp_ग_लिखो(hellcreek, 0x00, PR_CLOCK_DRIFT_C);
	hellcreek_ptp_ग_लिखो(hellcreek, 0x00, PR_CLOCK_DRIFT_C);
	hellcreek_ptp_ग_लिखो(hellcreek, addendh,  PR_CLOCK_DRIFT_C);
	hellcreek_ptp_ग_लिखो(hellcreek, addendl,  PR_CLOCK_DRIFT_C);

	mutex_unlock(&hellcreek->ptp_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा hellcreek *hellcreek = ptp_to_hellcreek(ptp);
	u16 negative = 0, counth, countl;
	u32 count_val;

	/* If the offset is larger than IP-Core slow offset resources. Don't
	 * consider slow adjusपंचांगent. Rather, add the offset directly to the
	 * current समय
	 */
	अगर (असल(delta) > MAX_SLOW_OFFSET_ADJ) अणु
		काष्ठा बारpec64 now, then = ns_to_बारpec64(delta);

		hellcreek_ptp_समय_लो(ptp, &now);
		now = बारpec64_add(now, then);
		hellcreek_ptp_समय_रखो(ptp, &now);

		वापस 0;
	पूर्ण

	अगर (delta < 0) अणु
		negative = 1;
		delta = -delta;
	पूर्ण

	/* 'count_val' करोes not exceed the maximum रेजिस्टर size (2^30) */
	count_val = भाग_s64(delta, MAX_NS_PER_STEP);

	counth = (count_val & 0xffff0000) >> 16;
	countl = count_val & 0xffff;

	negative = (negative << 15) & 0x8000;

	mutex_lock(&hellcreek->ptp_lock);

	/* Set offset ग_लिखो रेजिस्टर */
	hellcreek_ptp_ग_लिखो(hellcreek, negative, PR_CLOCK_OFFSET_C);
	hellcreek_ptp_ग_लिखो(hellcreek, MAX_NS_PER_STEP, PR_CLOCK_OFFSET_C);
	hellcreek_ptp_ग_लिखो(hellcreek, MIN_CLK_CYCLES_BETWEEN_STEPS,
			    PR_CLOCK_OFFSET_C);
	hellcreek_ptp_ग_लिखो(hellcreek, countl,  PR_CLOCK_OFFSET_C);
	hellcreek_ptp_ग_लिखो(hellcreek, counth,  PR_CLOCK_OFFSET_C);

	mutex_unlock(&hellcreek->ptp_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
				काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम hellcreek_ptp_overflow_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा hellcreek *hellcreek;

	hellcreek = dw_overflow_to_hellcreek(dw);

	mutex_lock(&hellcreek->ptp_lock);
	__hellcreek_ptp_समय_लो(hellcreek);
	mutex_unlock(&hellcreek->ptp_lock);

	schedule_delayed_work(&hellcreek->overflow_work,
			      HELLCREEK_OVERFLOW_PERIOD);
पूर्ण

अटल क्रमागत led_brightness hellcreek_get_brightness(काष्ठा hellcreek *hellcreek,
						    पूर्णांक led)
अणु
	वापस (hellcreek->status_out & led) ? 1 : 0;
पूर्ण

अटल व्योम hellcreek_set_brightness(काष्ठा hellcreek *hellcreek, पूर्णांक led,
				     क्रमागत led_brightness b)
अणु
	mutex_lock(&hellcreek->ptp_lock);

	अगर (b)
		hellcreek->status_out |= led;
	अन्यथा
		hellcreek->status_out &= ~led;

	hellcreek_ptp_ग_लिखो(hellcreek, hellcreek->status_out, STATUS_OUT);

	mutex_unlock(&hellcreek->ptp_lock);
पूर्ण

अटल व्योम hellcreek_led_sync_good_set(काष्ठा led_classdev *ldev,
					क्रमागत led_brightness b)
अणु
	काष्ठा hellcreek *hellcreek = led_to_hellcreek(ldev, led_sync_good);

	hellcreek_set_brightness(hellcreek, STATUS_OUT_SYNC_GOOD, b);
पूर्ण

अटल क्रमागत led_brightness hellcreek_led_sync_good_get(काष्ठा led_classdev *ldev)
अणु
	काष्ठा hellcreek *hellcreek = led_to_hellcreek(ldev, led_sync_good);

	वापस hellcreek_get_brightness(hellcreek, STATUS_OUT_SYNC_GOOD);
पूर्ण

अटल व्योम hellcreek_led_is_gm_set(काष्ठा led_classdev *ldev,
				    क्रमागत led_brightness b)
अणु
	काष्ठा hellcreek *hellcreek = led_to_hellcreek(ldev, led_is_gm);

	hellcreek_set_brightness(hellcreek, STATUS_OUT_IS_GM, b);
पूर्ण

अटल क्रमागत led_brightness hellcreek_led_is_gm_get(काष्ठा led_classdev *ldev)
अणु
	काष्ठा hellcreek *hellcreek = led_to_hellcreek(ldev, led_is_gm);

	वापस hellcreek_get_brightness(hellcreek, STATUS_OUT_IS_GM);
पूर्ण

/* There two available LEDs पूर्णांकernally called sync_good and is_gm. However, the
 * user might want to use a dअगरferent label and specअगरy the शेष state. Take
 * those properties from device tree.
 */
अटल पूर्णांक hellcreek_led_setup(काष्ठा hellcreek *hellcreek)
अणु
	काष्ठा device_node *leds, *led = शून्य;
	स्थिर अक्षर *label, *state;
	पूर्णांक ret = -EINVAL;

	leds = of_find_node_by_name(hellcreek->dev->of_node, "leds");
	अगर (!leds) अणु
		dev_err(hellcreek->dev, "No LEDs specified in device tree!\n");
		वापस ret;
	पूर्ण

	hellcreek->status_out = 0;

	led = of_get_next_available_child(leds, led);
	अगर (!led) अणु
		dev_err(hellcreek->dev, "First LED not specified!\n");
		जाओ out;
	पूर्ण

	ret = of_property_पढ़ो_string(led, "label", &label);
	hellcreek->led_sync_good.name = ret ? "sync_good" : label;

	ret = of_property_पढ़ो_string(led, "default-state", &state);
	अगर (!ret) अणु
		अगर (!म_भेद(state, "on"))
			hellcreek->led_sync_good.brightness = 1;
		अन्यथा अगर (!म_भेद(state, "off"))
			hellcreek->led_sync_good.brightness = 0;
		अन्यथा अगर (!म_भेद(state, "keep"))
			hellcreek->led_sync_good.brightness =
				hellcreek_get_brightness(hellcreek,
							 STATUS_OUT_SYNC_GOOD);
	पूर्ण

	hellcreek->led_sync_good.max_brightness = 1;
	hellcreek->led_sync_good.brightness_set = hellcreek_led_sync_good_set;
	hellcreek->led_sync_good.brightness_get = hellcreek_led_sync_good_get;

	led = of_get_next_available_child(leds, led);
	अगर (!led) अणु
		dev_err(hellcreek->dev, "Second LED not specified!\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = of_property_पढ़ो_string(led, "label", &label);
	hellcreek->led_is_gm.name = ret ? "is_gm" : label;

	ret = of_property_पढ़ो_string(led, "default-state", &state);
	अगर (!ret) अणु
		अगर (!म_भेद(state, "on"))
			hellcreek->led_is_gm.brightness = 1;
		अन्यथा अगर (!म_भेद(state, "off"))
			hellcreek->led_is_gm.brightness = 0;
		अन्यथा अगर (!म_भेद(state, "keep"))
			hellcreek->led_is_gm.brightness =
				hellcreek_get_brightness(hellcreek,
							 STATUS_OUT_IS_GM);
	पूर्ण

	hellcreek->led_is_gm.max_brightness = 1;
	hellcreek->led_is_gm.brightness_set = hellcreek_led_is_gm_set;
	hellcreek->led_is_gm.brightness_get = hellcreek_led_is_gm_get;

	/* Set initial state */
	अगर (hellcreek->led_sync_good.brightness == 1)
		hellcreek_set_brightness(hellcreek, STATUS_OUT_SYNC_GOOD, 1);
	अगर (hellcreek->led_is_gm.brightness == 1)
		hellcreek_set_brightness(hellcreek, STATUS_OUT_IS_GM, 1);

	/* Register both leds */
	led_classdev_रेजिस्टर(hellcreek->dev, &hellcreek->led_sync_good);
	led_classdev_रेजिस्टर(hellcreek->dev, &hellcreek->led_is_gm);

	ret = 0;

out:
	of_node_put(leds);

	वापस ret;
पूर्ण

पूर्णांक hellcreek_ptp_setup(काष्ठा hellcreek *hellcreek)
अणु
	u16 status;
	पूर्णांक ret;

	/* Set up the overflow work */
	INIT_DELAYED_WORK(&hellcreek->overflow_work,
			  hellcreek_ptp_overflow_check);

	/* Setup PTP घड़ी */
	hellcreek->ptp_घड़ी_info.owner = THIS_MODULE;
	snम_लिखो(hellcreek->ptp_घड़ी_info.name,
		 माप(hellcreek->ptp_घड़ी_info.name),
		 dev_name(hellcreek->dev));

	/* IP-Core can add up to 0.5 ns per 8 ns cycle, which means
	 * accumulator_overflow_rate shall not exceed 62.5 MHz (which adjusts
	 * the nominal frequency by 6.25%)
	 */
	hellcreek->ptp_घड़ी_info.max_adj     = 62500000;
	hellcreek->ptp_घड़ी_info.n_alarm     = 0;
	hellcreek->ptp_घड़ी_info.n_pins      = 0;
	hellcreek->ptp_घड़ी_info.n_ext_ts    = 0;
	hellcreek->ptp_घड़ी_info.n_per_out   = 0;
	hellcreek->ptp_घड़ी_info.pps	      = 0;
	hellcreek->ptp_घड़ी_info.adjfine     = hellcreek_ptp_adjfine;
	hellcreek->ptp_घड़ी_info.adjसमय     = hellcreek_ptp_adjसमय;
	hellcreek->ptp_घड़ी_info.समय_लो64   = hellcreek_ptp_समय_लो;
	hellcreek->ptp_घड़ी_info.समय_रखो64   = hellcreek_ptp_समय_रखो;
	hellcreek->ptp_घड़ी_info.enable      = hellcreek_ptp_enable;
	hellcreek->ptp_घड़ी_info.करो_aux_work = hellcreek_hwtstamp_work;

	hellcreek->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&hellcreek->ptp_घड़ी_info,
						  hellcreek->dev);
	अगर (IS_ERR(hellcreek->ptp_घड़ी))
		वापस PTR_ERR(hellcreek->ptp_घड़ी);

	/* Enable the offset correction process, अगर no offset correction is
	 * alपढ़ोy taking place
	 */
	status = hellcreek_ptp_पढ़ो(hellcreek, PR_CLOCK_STATUS_C);
	अगर (!(status & PR_CLOCK_STATUS_C_OFS_ACT))
		hellcreek_ptp_ग_लिखो(hellcreek,
				    status | PR_CLOCK_STATUS_C_ENA_OFS,
				    PR_CLOCK_STATUS_C);

	/* Enable the drअगरt correction process */
	hellcreek_ptp_ग_लिखो(hellcreek, status | PR_CLOCK_STATUS_C_ENA_DRIFT,
			    PR_CLOCK_STATUS_C);

	/* LED setup */
	ret = hellcreek_led_setup(hellcreek);
	अगर (ret) अणु
		अगर (hellcreek->ptp_घड़ी)
			ptp_घड़ी_unरेजिस्टर(hellcreek->ptp_घड़ी);
		वापस ret;
	पूर्ण

	schedule_delayed_work(&hellcreek->overflow_work,
			      HELLCREEK_OVERFLOW_PERIOD);

	वापस 0;
पूर्ण

व्योम hellcreek_ptp_मुक्त(काष्ठा hellcreek *hellcreek)
अणु
	led_classdev_unरेजिस्टर(&hellcreek->led_is_gm);
	led_classdev_unरेजिस्टर(&hellcreek->led_sync_good);
	cancel_delayed_work_sync(&hellcreek->overflow_work);
	अगर (hellcreek->ptp_घड़ी)
		ptp_घड़ी_unरेजिस्टर(hellcreek->ptp_घड़ी);
	hellcreek->ptp_घड़ी = शून्य;
पूर्ण
