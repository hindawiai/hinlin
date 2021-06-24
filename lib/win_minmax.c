<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * lib/minmax.c: winकरोwed min/max tracker
 *
 * Kathleen Nichols' algorithm क्रम tracking the minimum (or maximum)
 * value of a data stream over some fixed समय पूर्णांकerval.  (E.g.,
 * the minimum RTT over the past five minutes.) It uses स्थिरant
 * space and स्थिरant समय per update yet almost always delivers
 * the same minimum as an implementation that has to keep all the
 * data in the winकरोw.
 *
 * The algorithm keeps track of the best, 2nd best & 3rd best min
 * values, मुख्यtaining an invariant that the measurement समय of
 * the n'th best >= n-1'th best. It also makes sure that the three
 * values are widely separated in the समय winकरोw since that bounds
 * the worse हाल error when that data is monotonically increasing
 * over the winकरोw.
 *
 * Upon getting a new min, we can क्रमget everything earlier because
 * it has no value - the new min is <= everything अन्यथा in the winकरोw
 * by definition and it's the most recent. So we restart fresh on
 * every new min and overग_लिखोs 2nd & 3rd choices. The same property
 * holds क्रम 2nd & 3rd best.
 */
#समावेश <linux/module.h>
#समावेश <linux/win_minmax.h>

/* As समय advances, update the 1st, 2nd, and 3rd choices. */
अटल u32 minmax_subwin_update(काष्ठा minmax *m, u32 win,
				स्थिर काष्ठा minmax_sample *val)
अणु
	u32 dt = val->t - m->s[0].t;

	अगर (unlikely(dt > win)) अणु
		/*
		 * Passed entire winकरोw without a new val so make 2nd
		 * choice the new val & 3rd choice the new 2nd choice.
		 * we may have to iterate this since our 2nd choice
		 * may also be outside the winकरोw (we checked on entry
		 * that the third choice was in the winकरोw).
		 */
		m->s[0] = m->s[1];
		m->s[1] = m->s[2];
		m->s[2] = *val;
		अगर (unlikely(val->t - m->s[0].t > win)) अणु
			m->s[0] = m->s[1];
			m->s[1] = m->s[2];
			m->s[2] = *val;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(m->s[1].t == m->s[0].t) && dt > win/4) अणु
		/*
		 * We've passed a quarter of the winकरोw without a new val
		 * so take a 2nd choice from the 2nd quarter of the winकरोw.
		 */
		m->s[2] = m->s[1] = *val;
	पूर्ण अन्यथा अगर (unlikely(m->s[2].t == m->s[1].t) && dt > win/2) अणु
		/*
		 * We've passed half the winकरोw without finding a new val
		 * so take a 3rd choice from the last half of the winकरोw
		 */
		m->s[2] = *val;
	पूर्ण
	वापस m->s[0].v;
पूर्ण

/* Check अगर new measurement updates the 1st, 2nd or 3rd choice max. */
u32 minmax_running_max(काष्ठा minmax *m, u32 win, u32 t, u32 meas)
अणु
	काष्ठा minmax_sample val = अणु .t = t, .v = meas पूर्ण;

	अगर (unlikely(val.v >= m->s[0].v) ||	  /* found new max? */
	    unlikely(val.t - m->s[2].t > win))	  /* nothing left in winकरोw? */
		वापस minmax_reset(m, t, meas);  /* क्रमget earlier samples */

	अगर (unlikely(val.v >= m->s[1].v))
		m->s[2] = m->s[1] = val;
	अन्यथा अगर (unlikely(val.v >= m->s[2].v))
		m->s[2] = val;

	वापस minmax_subwin_update(m, win, &val);
पूर्ण
EXPORT_SYMBOL(minmax_running_max);

/* Check अगर new measurement updates the 1st, 2nd or 3rd choice min. */
u32 minmax_running_min(काष्ठा minmax *m, u32 win, u32 t, u32 meas)
अणु
	काष्ठा minmax_sample val = अणु .t = t, .v = meas पूर्ण;

	अगर (unlikely(val.v <= m->s[0].v) ||	  /* found new min? */
	    unlikely(val.t - m->s[2].t > win))	  /* nothing left in winकरोw? */
		वापस minmax_reset(m, t, meas);  /* क्रमget earlier samples */

	अगर (unlikely(val.v <= m->s[1].v))
		m->s[2] = m->s[1] = val;
	अन्यथा अगर (unlikely(val.v <= m->s[2].v))
		m->s[2] = val;

	वापस minmax_subwin_update(m, win, &val);
पूर्ण
