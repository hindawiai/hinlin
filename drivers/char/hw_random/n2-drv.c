<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* n2-drv.c: Niagara-2 RNG driver.
 *
 * Copyright (C) 2008, 2011 David S. Miller <davem@davemloft.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/preempt.h>
#समावेश <linux/hw_अक्रमom.h>

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/hypervisor.h>

#समावेश "n2rng.h"

#घोषणा DRV_MODULE_NAME		"n2rng"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_MODULE_VERSION	"0.3"
#घोषणा DRV_MODULE_RELDATE	"Jan 7, 2017"

अटल अक्षर version[] =
	DRV_MODULE_NAME " v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";

MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("Niagara2 RNG driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

/* The Niagara2 RNG provides a 64-bit पढ़ो-only अक्रमom number
 * रेजिस्टर, plus a control रेजिस्टर.  Access to the RNG is
 * भवized through the hypervisor so that both guests and control
 * nodes can access the device.
 *
 * The entropy source consists of raw entropy sources, each
 * स्थिरructed from a voltage controlled oscillator whose phase is
 * jittered by thermal noise sources.
 *
 * The oscillator in each of the three raw entropy sources run at
 * dअगरferent frequencies.  Normally, all three generator outमाला_दो are
 * gathered, xored together, and fed पूर्णांकo a CRC circuit, the output of
 * which is the 64-bit पढ़ो-only रेजिस्टर.
 *
 * Some समय is necessary क्रम all the necessary entropy to build up
 * such that a full 64-bits of entropy are available in the रेजिस्टर.
 * In normal operating mode (RNG_CTL_LFSR is set), the chip implements
 * an पूर्णांकerlock which blocks रेजिस्टर पढ़ोs until sufficient entropy
 * is available.
 *
 * A control रेजिस्टर is provided क्रम adjusting various aspects of RNG
 * operation, and to enable diagnostic modes.  Each of the three raw
 * entropy sources has an enable bit (RNG_CTL_ESअणु1,2,3पूर्ण).  Also
 * provided are fields क्रम controlling the minimum समय in cycles
 * between पढ़ो accesses to the रेजिस्टर (RNG_CTL_WAIT, this controls
 * the पूर्णांकerlock described in the previous paragraph).
 *
 * The standard setting is to have the mode bit (RNG_CTL_LFSR) set,
 * all three entropy sources enabled, and the पूर्णांकerlock समय set
 * appropriately.
 *
 * The CRC polynomial used by the chip is:
 *
 * P(X) = x64 + x61 + x57 + x56 + x52 + x51 + x50 + x48 + x47 + x46 +
 *        x43 + x42 + x41 + x39 + x38 + x37 + x35 + x32 + x28 + x25 +
 *        x22 + x21 + x17 + x15 + x13 + x12 + x11 + x7 + x5 + x + 1
 *
 * The RNG_CTL_VCO value of each noise cell must be programmed
 * separately.  This is why 4 control रेजिस्टर values must be provided
 * to the hypervisor.  During a ग_लिखो, the hypervisor ग_लिखोs them all,
 * one at a समय, to the actual RNG_CTL रेजिस्टर.  The first three
 * values are used to setup the desired RNG_CTL_VCO क्रम each entropy
 * source, क्रम example:
 *
 *	control 0: (1 << RNG_CTL_VCO_SHIFT) | RNG_CTL_ES1
 *	control 1: (2 << RNG_CTL_VCO_SHIFT) | RNG_CTL_ES2
 *	control 2: (3 << RNG_CTL_VCO_SHIFT) | RNG_CTL_ES3
 *
 * And then the fourth value sets the final chip state and enables
 * desired.
 */

अटल पूर्णांक n2rng_hv_err_trans(अचिन्हित दीर्घ hv_err)
अणु
	चयन (hv_err) अणु
	हाल HV_EOK:
		वापस 0;
	हाल HV_EWOULDBLOCK:
		वापस -EAGAIN;
	हाल HV_ENOACCESS:
		वापस -EPERM;
	हाल HV_EIO:
		वापस -EIO;
	हाल HV_EBUSY:
		वापस -EBUSY;
	हाल HV_EBADALIGN:
	हाल HV_ENORADDR:
		वापस -EFAULT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ n2rng_generic_पढ़ो_control_v2(अचिन्हित दीर्घ ra,
						   अचिन्हित दीर्घ unit)
अणु
	अचिन्हित दीर्घ hv_err, state, ticks, watchकरोg_delta, watchकरोg_status;
	पूर्णांक block = 0, busy = 0;

	जबतक (1) अणु
		hv_err = sun4v_rng_ctl_पढ़ो_v2(ra, unit, &state,
					       &ticks,
					       &watchकरोg_delta,
					       &watchकरोg_status);
		अगर (hv_err == HV_EOK)
			अवरोध;

		अगर (hv_err == HV_EBUSY) अणु
			अगर (++busy >= N2RNG_BUSY_LIMIT)
				अवरोध;

			udelay(1);
		पूर्ण अन्यथा अगर (hv_err == HV_EWOULDBLOCK) अणु
			अगर (++block >= N2RNG_BLOCK_LIMIT)
				अवरोध;

			__delay(ticks);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	वापस hv_err;
पूर्ण

/* In multi-socket situations, the hypervisor might need to
 * queue up the RNG control रेजिस्टर ग_लिखो अगर it's क्रम a unit
 * that is on a cpu socket other than the one we are executing on.
 *
 * We poll here रुकोing क्रम a successful पढ़ो of that control
 * रेजिस्टर to make sure the ग_लिखो has been actually perक्रमmed.
 */
अटल अचिन्हित दीर्घ n2rng_control_settle_v2(काष्ठा n2rng *np, पूर्णांक unit)
अणु
	अचिन्हित दीर्घ ra = __pa(&np->scratch_control[0]);

	वापस n2rng_generic_पढ़ो_control_v2(ra, unit);
पूर्ण

अटल अचिन्हित दीर्घ n2rng_ग_लिखो_ctl_one(काष्ठा n2rng *np, पूर्णांक unit,
					 अचिन्हित दीर्घ state,
					 अचिन्हित दीर्घ control_ra,
					 अचिन्हित दीर्घ watchकरोg_समयout,
					 अचिन्हित दीर्घ *ticks)
अणु
	अचिन्हित दीर्घ hv_err;

	अगर (np->hvapi_major == 1) अणु
		hv_err = sun4v_rng_ctl_ग_लिखो_v1(control_ra, state,
						watchकरोg_समयout, ticks);
	पूर्ण अन्यथा अणु
		hv_err = sun4v_rng_ctl_ग_लिखो_v2(control_ra, state,
						watchकरोg_समयout, unit);
		अगर (hv_err == HV_EOK)
			hv_err = n2rng_control_settle_v2(np, unit);
		*ticks = N2RNG_ACCUM_CYCLES_DEFAULT;
	पूर्ण

	वापस hv_err;
पूर्ण

अटल पूर्णांक n2rng_generic_पढ़ो_data(अचिन्हित दीर्घ data_ra)
अणु
	अचिन्हित दीर्घ ticks, hv_err;
	पूर्णांक block = 0, hcheck = 0;

	जबतक (1) अणु
		hv_err = sun4v_rng_data_पढ़ो(data_ra, &ticks);
		अगर (hv_err == HV_EOK)
			वापस 0;

		अगर (hv_err == HV_EWOULDBLOCK) अणु
			अगर (++block >= N2RNG_BLOCK_LIMIT)
				वापस -EWOULDBLOCK;
			__delay(ticks);
		पूर्ण अन्यथा अगर (hv_err == HV_ENOACCESS) अणु
			वापस -EPERM;
		पूर्ण अन्यथा अगर (hv_err == HV_EIO) अणु
			अगर (++hcheck >= N2RNG_HCHECK_LIMIT)
				वापस -EIO;
			udelay(10000);
		पूर्ण अन्यथा
			वापस -ENODEV;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ n2rng_पढ़ो_diag_data_one(काष्ठा n2rng *np,
					      अचिन्हित दीर्घ unit,
					      अचिन्हित दीर्घ data_ra,
					      अचिन्हित दीर्घ data_len,
					      अचिन्हित दीर्घ *ticks)
अणु
	अचिन्हित दीर्घ hv_err;

	अगर (np->hvapi_major == 1) अणु
		hv_err = sun4v_rng_data_पढ़ो_diag_v1(data_ra, data_len, ticks);
	पूर्ण अन्यथा अणु
		hv_err = sun4v_rng_data_पढ़ो_diag_v2(data_ra, data_len,
						     unit, ticks);
		अगर (!*ticks)
			*ticks = N2RNG_ACCUM_CYCLES_DEFAULT;
	पूर्ण
	वापस hv_err;
पूर्ण

अटल पूर्णांक n2rng_generic_पढ़ो_diag_data(काष्ठा n2rng *np,
					अचिन्हित दीर्घ unit,
					अचिन्हित दीर्घ data_ra,
					अचिन्हित दीर्घ data_len)
अणु
	अचिन्हित दीर्घ ticks, hv_err;
	पूर्णांक block = 0;

	जबतक (1) अणु
		hv_err = n2rng_पढ़ो_diag_data_one(np, unit,
						  data_ra, data_len,
						  &ticks);
		अगर (hv_err == HV_EOK)
			वापस 0;

		अगर (hv_err == HV_EWOULDBLOCK) अणु
			अगर (++block >= N2RNG_BLOCK_LIMIT)
				वापस -EWOULDBLOCK;
			__delay(ticks);
		पूर्ण अन्यथा अगर (hv_err == HV_ENOACCESS) अणु
			वापस -EPERM;
		पूर्ण अन्यथा अगर (hv_err == HV_EIO) अणु
			वापस -EIO;
		पूर्ण अन्यथा
			वापस -ENODEV;
	पूर्ण
पूर्ण


अटल पूर्णांक n2rng_generic_ग_लिखो_control(काष्ठा n2rng *np,
				       अचिन्हित दीर्घ control_ra,
				       अचिन्हित दीर्घ unit,
				       अचिन्हित दीर्घ state)
अणु
	अचिन्हित दीर्घ hv_err, ticks;
	पूर्णांक block = 0, busy = 0;

	जबतक (1) अणु
		hv_err = n2rng_ग_लिखो_ctl_one(np, unit, state, control_ra,
					     np->wd_समयo, &ticks);
		अगर (hv_err == HV_EOK)
			वापस 0;

		अगर (hv_err == HV_EWOULDBLOCK) अणु
			अगर (++block >= N2RNG_BLOCK_LIMIT)
				वापस -EWOULDBLOCK;
			__delay(ticks);
		पूर्ण अन्यथा अगर (hv_err == HV_EBUSY) अणु
			अगर (++busy >= N2RNG_BUSY_LIMIT)
				वापस -EBUSY;
			udelay(1);
		पूर्ण अन्यथा
			वापस -ENODEV;
	पूर्ण
पूर्ण

/* Just try to see अगर we can successfully access the control रेजिस्टर
 * of the RNG on the करोमुख्य on which we are currently executing.
 */
अटल पूर्णांक n2rng_try_पढ़ो_ctl(काष्ठा n2rng *np)
अणु
	अचिन्हित दीर्घ hv_err;
	अचिन्हित दीर्घ x;

	अगर (np->hvapi_major == 1) अणु
		hv_err = sun4v_rng_get_diag_ctl();
	पूर्ण अन्यथा अणु
		/* We purposefully give invalid arguments, HV_NOACCESS
		 * is higher priority than the errors we'd get from
		 * these other हालs, and that's the error we are
		 * truly पूर्णांकerested in.
		 */
		hv_err = sun4v_rng_ctl_पढ़ो_v2(0UL, ~0UL, &x, &x, &x, &x);
		चयन (hv_err) अणु
		हाल HV_EWOULDBLOCK:
		हाल HV_ENOACCESS:
			अवरोध;
		शेष:
			hv_err = HV_EOK;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस n2rng_hv_err_trans(hv_err);
पूर्ण

अटल u64 n2rng_control_शेष(काष्ठा n2rng *np, पूर्णांक ctl)
अणु
	u64 val = 0;

	अगर (np->data->chip_version == 1) अणु
		val = ((2 << RNG_v1_CTL_ASEL_SHIFT) |
			(N2RNG_ACCUM_CYCLES_DEFAULT << RNG_v1_CTL_WAIT_SHIFT) |
			 RNG_CTL_LFSR);

		चयन (ctl) अणु
		हाल 0:
			val |= (1 << RNG_v1_CTL_VCO_SHIFT) | RNG_CTL_ES1;
			अवरोध;
		हाल 1:
			val |= (2 << RNG_v1_CTL_VCO_SHIFT) | RNG_CTL_ES2;
			अवरोध;
		हाल 2:
			val |= (3 << RNG_v1_CTL_VCO_SHIFT) | RNG_CTL_ES3;
			अवरोध;
		हाल 3:
			val |= RNG_CTL_ES1 | RNG_CTL_ES2 | RNG_CTL_ES3;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		val = ((2 << RNG_v2_CTL_ASEL_SHIFT) |
			(N2RNG_ACCUM_CYCLES_DEFAULT << RNG_v2_CTL_WAIT_SHIFT) |
			 RNG_CTL_LFSR);

		चयन (ctl) अणु
		हाल 0:
			val |= (1 << RNG_v2_CTL_VCO_SHIFT) | RNG_CTL_ES1;
			अवरोध;
		हाल 1:
			val |= (2 << RNG_v2_CTL_VCO_SHIFT) | RNG_CTL_ES2;
			अवरोध;
		हाल 2:
			val |= (3 << RNG_v2_CTL_VCO_SHIFT) | RNG_CTL_ES3;
			अवरोध;
		हाल 3:
			val |= RNG_CTL_ES1 | RNG_CTL_ES2 | RNG_CTL_ES3;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम n2rng_control_swstate_init(काष्ठा n2rng *np)
अणु
	पूर्णांक i;

	np->flags |= N2RNG_FLAG_CONTROL;

	np->health_check_sec = N2RNG_HEALTH_CHECK_SEC_DEFAULT;
	np->accum_cycles = N2RNG_ACCUM_CYCLES_DEFAULT;
	np->wd_समयo = N2RNG_WD_TIMEO_DEFAULT;

	क्रम (i = 0; i < np->num_units; i++) अणु
		काष्ठा n2rng_unit *up = &np->units[i];

		up->control[0] = n2rng_control_शेष(np, 0);
		up->control[1] = n2rng_control_शेष(np, 1);
		up->control[2] = n2rng_control_शेष(np, 2);
		up->control[3] = n2rng_control_शेष(np, 3);
	पूर्ण

	np->hv_state = HV_RNG_STATE_UNCONFIGURED;
पूर्ण

अटल पूर्णांक n2rng_grab_diag_control(काष्ठा n2rng *np)
अणु
	पूर्णांक i, busy_count, err = -ENODEV;

	busy_count = 0;
	क्रम (i = 0; i < 100; i++) अणु
		err = n2rng_try_पढ़ो_ctl(np);
		अगर (err != -EAGAIN)
			अवरोध;

		अगर (++busy_count > 100) अणु
			dev_err(&np->op->dev,
				"Grab diag control timeout.\n");
			वापस -ENODEV;
		पूर्ण

		udelay(1);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक n2rng_init_control(काष्ठा n2rng *np)
अणु
	पूर्णांक err = n2rng_grab_diag_control(np);

	/* Not in the control करोमुख्य, that's OK we are only a consumer
	 * of the RNG data, we करोn't setup and program it.
	 */
	अगर (err == -EPERM)
		वापस 0;
	अगर (err)
		वापस err;

	n2rng_control_swstate_init(np);

	वापस 0;
पूर्ण

अटल पूर्णांक n2rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा n2rng *np = (काष्ठा n2rng *) rng->priv;
	अचिन्हित दीर्घ ra = __pa(&np->test_data);
	पूर्णांक len;

	अगर (!(np->flags & N2RNG_FLAG_READY)) अणु
		len = 0;
	पूर्ण अन्यथा अगर (np->flags & N2RNG_FLAG_BUFFER_VALID) अणु
		np->flags &= ~N2RNG_FLAG_BUFFER_VALID;
		*data = np->buffer;
		len = 4;
	पूर्ण अन्यथा अणु
		पूर्णांक err = n2rng_generic_पढ़ो_data(ra);
		अगर (!err) अणु
			np->flags |= N2RNG_FLAG_BUFFER_VALID;
			np->buffer = np->test_data >> 32;
			*data = np->test_data & 0xffffffff;
			len = 4;
		पूर्ण अन्यथा अणु
			dev_err(&np->op->dev, "RNG error, retesting\n");
			np->flags &= ~N2RNG_FLAG_READY;
			अगर (!(np->flags & N2RNG_FLAG_SHUTDOWN))
				schedule_delayed_work(&np->work, 0);
			len = 0;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

/* On a guest node, just make sure we can पढ़ो अक्रमom data properly.
 * If a control node reboots or reloads it's n2rng driver, this won't
 * work during that समय.  So we have to keep probing until the device
 * becomes usable.
 */
अटल पूर्णांक n2rng_guest_check(काष्ठा n2rng *np)
अणु
	अचिन्हित दीर्घ ra = __pa(&np->test_data);

	वापस n2rng_generic_पढ़ो_data(ra);
पूर्ण

अटल पूर्णांक n2rng_entropy_diag_पढ़ो(काष्ठा n2rng *np, अचिन्हित दीर्घ unit,
				   u64 *pre_control, u64 pre_state,
				   u64 *buffer, अचिन्हित दीर्घ buf_len,
				   u64 *post_control, u64 post_state)
अणु
	अचिन्हित दीर्घ post_ctl_ra = __pa(post_control);
	अचिन्हित दीर्घ pre_ctl_ra = __pa(pre_control);
	अचिन्हित दीर्घ buffer_ra = __pa(buffer);
	पूर्णांक err;

	err = n2rng_generic_ग_लिखो_control(np, pre_ctl_ra, unit, pre_state);
	अगर (err)
		वापस err;

	err = n2rng_generic_पढ़ो_diag_data(np, unit,
					   buffer_ra, buf_len);

	(व्योम) n2rng_generic_ग_लिखो_control(np, post_ctl_ra, unit,
					   post_state);

	वापस err;
पूर्ण

अटल u64 advance_polynomial(u64 poly, u64 val, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक highbit_set = ((s64)val < 0);

		val <<= 1;
		अगर (highbit_set)
			val ^= poly;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक n2rng_test_buffer_find(काष्ठा n2rng *np, u64 val)
अणु
	पूर्णांक i, count = 0;

	/* Purposefully skip over the first word.  */
	क्रम (i = 1; i < SELFTEST_BUFFER_WORDS; i++) अणु
		अगर (np->test_buffer[i] == val)
			count++;
	पूर्ण
	वापस count;
पूर्ण

अटल व्योम n2rng_dump_test_buffer(काष्ठा n2rng *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SELFTEST_BUFFER_WORDS; i++)
		dev_err(&np->op->dev, "Test buffer slot %d [0x%016llx]\n",
			i, np->test_buffer[i]);
पूर्ण

अटल पूर्णांक n2rng_check_selftest_buffer(काष्ठा n2rng *np, अचिन्हित दीर्घ unit)
अणु
	u64 val;
	पूर्णांक err, matches, limit;

	चयन (np->data->id) अणु
	हाल N2_n2_rng:
	हाल N2_vf_rng:
	हाल N2_kt_rng:
	हाल N2_m4_rng:  /* yes, m4 uses the old value */
		val = RNG_v1_SELFTEST_VAL;
		अवरोध;
	शेष:
		val = RNG_v2_SELFTEST_VAL;
		अवरोध;
	पूर्ण

	matches = 0;
	क्रम (limit = 0; limit < SELFTEST_LOOPS_MAX; limit++) अणु
		matches += n2rng_test_buffer_find(np, val);
		अगर (matches >= SELFTEST_MATCH_GOAL)
			अवरोध;
		val = advance_polynomial(SELFTEST_POLY, val, 1);
	पूर्ण

	err = 0;
	अगर (limit >= SELFTEST_LOOPS_MAX) अणु
		err = -ENODEV;
		dev_err(&np->op->dev, "Selftest failed on unit %lu\n", unit);
		n2rng_dump_test_buffer(np);
	पूर्ण अन्यथा
		dev_info(&np->op->dev, "Selftest passed on unit %lu\n", unit);

	वापस err;
पूर्ण

अटल पूर्णांक n2rng_control_selftest(काष्ठा n2rng *np, अचिन्हित दीर्घ unit)
अणु
	पूर्णांक err;
	u64 base, base3;

	चयन (np->data->id) अणु
	हाल N2_n2_rng:
	हाल N2_vf_rng:
	हाल N2_kt_rng:
		base = RNG_v1_CTL_ASEL_NOOUT << RNG_v1_CTL_ASEL_SHIFT;
		base3 = base | RNG_CTL_LFSR |
			((RNG_v1_SELFTEST_TICKS - 2) << RNG_v1_CTL_WAIT_SHIFT);
		अवरोध;
	हाल N2_m4_rng:
		base = RNG_v2_CTL_ASEL_NOOUT << RNG_v2_CTL_ASEL_SHIFT;
		base3 = base | RNG_CTL_LFSR |
			((RNG_v1_SELFTEST_TICKS - 2) << RNG_v2_CTL_WAIT_SHIFT);
		अवरोध;
	शेष:
		base = RNG_v2_CTL_ASEL_NOOUT << RNG_v2_CTL_ASEL_SHIFT;
		base3 = base | RNG_CTL_LFSR |
			(RNG_v2_SELFTEST_TICKS << RNG_v2_CTL_WAIT_SHIFT);
		अवरोध;
	पूर्ण

	np->test_control[0] = base;
	np->test_control[1] = base;
	np->test_control[2] = base;
	np->test_control[3] = base3;

	err = n2rng_entropy_diag_पढ़ो(np, unit, np->test_control,
				      HV_RNG_STATE_HEALTHCHECK,
				      np->test_buffer,
				      माप(np->test_buffer),
				      &np->units[unit].control[0],
				      np->hv_state);
	अगर (err)
		वापस err;

	वापस n2rng_check_selftest_buffer(np, unit);
पूर्ण

अटल पूर्णांक n2rng_control_check(काष्ठा n2rng *np)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < np->num_units; i++) अणु
		पूर्णांक err = n2rng_control_selftest(np, i);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* The sanity checks passed, install the final configuration पूर्णांकo the
 * chip, it's पढ़ोy to use.
 */
अटल पूर्णांक n2rng_control_configure_units(काष्ठा n2rng *np)
अणु
	पूर्णांक unit, err;

	err = 0;
	क्रम (unit = 0; unit < np->num_units; unit++) अणु
		काष्ठा n2rng_unit *up = &np->units[unit];
		अचिन्हित दीर्घ ctl_ra = __pa(&up->control[0]);
		पूर्णांक esrc;
		u64 base, shअगरt;

		अगर (np->data->chip_version == 1) अणु
			base = ((np->accum_cycles << RNG_v1_CTL_WAIT_SHIFT) |
			      (RNG_v1_CTL_ASEL_NOOUT << RNG_v1_CTL_ASEL_SHIFT) |
			      RNG_CTL_LFSR);
			shअगरt = RNG_v1_CTL_VCO_SHIFT;
		पूर्ण अन्यथा अणु
			base = ((np->accum_cycles << RNG_v2_CTL_WAIT_SHIFT) |
			      (RNG_v2_CTL_ASEL_NOOUT << RNG_v2_CTL_ASEL_SHIFT) |
			      RNG_CTL_LFSR);
			shअगरt = RNG_v2_CTL_VCO_SHIFT;
		पूर्ण

		/* XXX This isn't the best.  We should fetch a bunch
		 * XXX of words using each entropy source combined XXX
		 * with each VCO setting, and see which combinations
		 * XXX give the best अक्रमom data.
		 */
		क्रम (esrc = 0; esrc < 3; esrc++)
			up->control[esrc] = base |
				(esrc << shअगरt) |
				(RNG_CTL_ES1 << esrc);

		up->control[3] = base |
			(RNG_CTL_ES1 | RNG_CTL_ES2 | RNG_CTL_ES3);

		err = n2rng_generic_ग_लिखो_control(np, ctl_ra, unit,
						  HV_RNG_STATE_CONFIGURED);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम n2rng_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा n2rng *np = container_of(work, काष्ठा n2rng, work.work);
	पूर्णांक err = 0;
	अटल पूर्णांक retries = 4;

	अगर (!(np->flags & N2RNG_FLAG_CONTROL)) अणु
		err = n2rng_guest_check(np);
	पूर्ण अन्यथा अणु
		preempt_disable();
		err = n2rng_control_check(np);
		preempt_enable();

		अगर (!err)
			err = n2rng_control_configure_units(np);
	पूर्ण

	अगर (!err) अणु
		np->flags |= N2RNG_FLAG_READY;
		dev_info(&np->op->dev, "RNG ready\n");
	पूर्ण

	अगर (--retries == 0)
		dev_err(&np->op->dev, "Self-test retries failed, RNG not ready\n");
	अन्यथा अगर (err && !(np->flags & N2RNG_FLAG_SHUTDOWN))
		schedule_delayed_work(&np->work, HZ * 2);
पूर्ण

अटल व्योम n2rng_driver_version(व्योम)
अणु
	अटल पूर्णांक n2rng_version_prपूर्णांकed;

	अगर (n2rng_version_prपूर्णांकed++ == 0)
		pr_info("%s", version);
पूर्ण

अटल स्थिर काष्ठा of_device_id n2rng_match[];
अटल पूर्णांक n2rng_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक err = -ENOMEM;
	काष्ठा n2rng *np;

	match = of_match_device(n2rng_match, &op->dev);
	अगर (!match)
		वापस -EINVAL;

	n2rng_driver_version();
	np = devm_kzalloc(&op->dev, माप(*np), GFP_KERNEL);
	अगर (!np)
		जाओ out;
	np->op = op;
	np->data = (काष्ठा n2rng_ढाँचा *)match->data;

	INIT_DELAYED_WORK(&np->work, n2rng_work);

	अगर (np->data->multi_capable)
		np->flags |= N2RNG_FLAG_MULTI;

	err = -ENODEV;
	np->hvapi_major = 2;
	अगर (sun4v_hvapi_रेजिस्टर(HV_GRP_RNG,
				 np->hvapi_major,
				 &np->hvapi_minor)) अणु
		np->hvapi_major = 1;
		अगर (sun4v_hvapi_रेजिस्टर(HV_GRP_RNG,
					 np->hvapi_major,
					 &np->hvapi_minor)) अणु
			dev_err(&op->dev, "Cannot register suitable "
				"HVAPI version.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (np->flags & N2RNG_FLAG_MULTI) अणु
		अगर (np->hvapi_major < 2) अणु
			dev_err(&op->dev, "multi-unit-capable RNG requires "
				"HVAPI major version 2 or later, got %lu\n",
				np->hvapi_major);
			जाओ out_hvapi_unरेजिस्टर;
		पूर्ण
		np->num_units = of_getपूर्णांकprop_शेष(op->dev.of_node,
						      "rng-#units", 0);
		अगर (!np->num_units) अणु
			dev_err(&op->dev, "VF RNG lacks rng-#units property\n");
			जाओ out_hvapi_unरेजिस्टर;
		पूर्ण
	पूर्ण अन्यथा अणु
		np->num_units = 1;
	पूर्ण

	dev_info(&op->dev, "Registered RNG HVAPI major %lu minor %lu\n",
		 np->hvapi_major, np->hvapi_minor);
	np->units = devm_kसुस्मृति(&op->dev, np->num_units, माप(*np->units),
				 GFP_KERNEL);
	err = -ENOMEM;
	अगर (!np->units)
		जाओ out_hvapi_unरेजिस्टर;

	err = n2rng_init_control(np);
	अगर (err)
		जाओ out_hvapi_unरेजिस्टर;

	dev_info(&op->dev, "Found %s RNG, units: %d\n",
		 ((np->flags & N2RNG_FLAG_MULTI) ?
		  "multi-unit-capable" : "single-unit"),
		 np->num_units);

	np->hwrng.name = DRV_MODULE_NAME;
	np->hwrng.data_पढ़ो = n2rng_data_पढ़ो;
	np->hwrng.priv = (अचिन्हित दीर्घ) np;

	err = devm_hwrng_रेजिस्टर(&op->dev, &np->hwrng);
	अगर (err)
		जाओ out_hvapi_unरेजिस्टर;

	platक्रमm_set_drvdata(op, np);

	schedule_delayed_work(&np->work, 0);

	वापस 0;

out_hvapi_unरेजिस्टर:
	sun4v_hvapi_unरेजिस्टर(HV_GRP_RNG);

out:
	वापस err;
पूर्ण

अटल पूर्णांक n2rng_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा n2rng *np = platक्रमm_get_drvdata(op);

	np->flags |= N2RNG_FLAG_SHUTDOWN;

	cancel_delayed_work_sync(&np->work);

	sun4v_hvapi_unरेजिस्टर(HV_GRP_RNG);

	वापस 0;
पूर्ण

अटल काष्ठा n2rng_ढाँचा n2_ढाँचा = अणु
	.id = N2_n2_rng,
	.multi_capable = 0,
	.chip_version = 1,
पूर्ण;

अटल काष्ठा n2rng_ढाँचा vf_ढाँचा = अणु
	.id = N2_vf_rng,
	.multi_capable = 1,
	.chip_version = 1,
पूर्ण;

अटल काष्ठा n2rng_ढाँचा kt_ढाँचा = अणु
	.id = N2_kt_rng,
	.multi_capable = 1,
	.chip_version = 1,
पूर्ण;

अटल काष्ठा n2rng_ढाँचा m4_ढाँचा = अणु
	.id = N2_m4_rng,
	.multi_capable = 1,
	.chip_version = 2,
पूर्ण;

अटल काष्ठा n2rng_ढाँचा m7_ढाँचा = अणु
	.id = N2_m7_rng,
	.multi_capable = 1,
	.chip_version = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id n2rng_match[] = अणु
	अणु
		.name		= "random-number-generator",
		.compatible	= "SUNW,n2-rng",
		.data		= &n2_ढाँचा,
	पूर्ण,
	अणु
		.name		= "random-number-generator",
		.compatible	= "SUNW,vf-rng",
		.data		= &vf_ढाँचा,
	पूर्ण,
	अणु
		.name		= "random-number-generator",
		.compatible	= "SUNW,kt-rng",
		.data		= &kt_ढाँचा,
	पूर्ण,
	अणु
		.name		= "random-number-generator",
		.compatible	= "ORCL,m4-rng",
		.data		= &m4_ढाँचा,
	पूर्ण,
	अणु
		.name		= "random-number-generator",
		.compatible	= "ORCL,m7-rng",
		.data		= &m7_ढाँचा,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, n2rng_match);

अटल काष्ठा platक्रमm_driver n2rng_driver = अणु
	.driver = अणु
		.name = "n2rng",
		.of_match_table = n2rng_match,
	पूर्ण,
	.probe		= n2rng_probe,
	.हटाओ		= n2rng_हटाओ,
पूर्ण;

module_platक्रमm_driver(n2rng_driver);
