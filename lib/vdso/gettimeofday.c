<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic userspace implementations of समय_लोofday() and similar.
 */
#समावेश <vdso/datapage.h>
#समावेश <vdso/helpers.h>

#अगर_अघोषित vdso_calc_delta
/*
 * Default implementation which works क्रम all sane घड़ीsources. That
 * obviously excludes x86/TSC.
 */
अटल __always_अंतरभूत
u64 vdso_calc_delta(u64 cycles, u64 last, u64 mask, u32 mult)
अणु
	वापस ((cycles - last) & mask) * mult;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित vdso_shअगरt_ns
अटल __always_अंतरभूत u64 vdso_shअगरt_ns(u64 ns, u32 shअगरt)
अणु
	वापस ns >> shअगरt;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __arch_vdso_hres_capable
अटल अंतरभूत bool __arch_vdso_hres_capable(व्योम)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित vdso_घड़ीsource_ok
अटल अंतरभूत bool vdso_घड़ीsource_ok(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस vd->घड़ी_mode != VDSO_CLOCKMODE_NONE;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित vdso_cycles_ok
अटल अंतरभूत bool vdso_cycles_ok(u64 cycles)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TIME_NS
अटल __always_अंतरभूत पूर्णांक करो_hres_समयns(स्थिर काष्ठा vdso_data *vdns, घड़ीid_t clk,
					  काष्ठा __kernel_बारpec *ts)
अणु
	स्थिर काष्ठा vdso_data *vd;
	स्थिर काष्ठा समयns_offset *offs = &vdns->offset[clk];
	स्थिर काष्ठा vdso_बारtamp *vdso_ts;
	u64 cycles, last, ns;
	u32 seq;
	s64 sec;

	vd = vdns - (clk == CLOCK_MONOTONIC_RAW ? CS_RAW : CS_HRES_COARSE);
	vd = __arch_get_समयns_vdso_data(vd);
	अगर (clk != CLOCK_MONOTONIC_RAW)
		vd = &vd[CS_HRES_COARSE];
	अन्यथा
		vd = &vd[CS_RAW];
	vdso_ts = &vd->baseसमय[clk];

	करो अणु
		seq = vdso_पढ़ो_begin(vd);

		अगर (unlikely(!vdso_घड़ीsource_ok(vd)))
			वापस -1;

		cycles = __arch_get_hw_counter(vd->घड़ी_mode, vd);
		अगर (unlikely(!vdso_cycles_ok(cycles)))
			वापस -1;
		ns = vdso_ts->nsec;
		last = vd->cycle_last;
		ns += vdso_calc_delta(cycles, last, vd->mask, vd->mult);
		ns = vdso_shअगरt_ns(ns, vd->shअगरt);
		sec = vdso_ts->sec;
	पूर्ण जबतक (unlikely(vdso_पढ़ो_retry(vd, seq)));

	/* Add the namespace offset */
	sec += offs->sec;
	ns += offs->nsec;

	/*
	 * Do this outside the loop: a race inside the loop could result
	 * in __iter_भाग_u64_rem() being extremely slow.
	 */
	ts->tv_sec = sec + __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण
#अन्यथा
अटल __always_अंतरभूत
स्थिर काष्ठा vdso_data *__arch_get_समयns_vdso_data(स्थिर काष्ठा vdso_data *vd)
अणु
	वापस शून्य;
पूर्ण

अटल __always_अंतरभूत पूर्णांक करो_hres_समयns(स्थिर काष्ठा vdso_data *vdns, घड़ीid_t clk,
					  काष्ठा __kernel_बारpec *ts)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत पूर्णांक करो_hres(स्थिर काष्ठा vdso_data *vd, घड़ीid_t clk,
				   काष्ठा __kernel_बारpec *ts)
अणु
	स्थिर काष्ठा vdso_बारtamp *vdso_ts = &vd->baseसमय[clk];
	u64 cycles, last, sec, ns;
	u32 seq;

	/* Allows to compile the high resolution parts out */
	अगर (!__arch_vdso_hres_capable())
		वापस -1;

	करो अणु
		/*
		 * Open coded to handle VDSO_CLOCKMODE_TIMENS. Time namespace
		 * enabled tasks have a special VVAR page installed which
		 * has vd->seq set to 1 and vd->घड़ी_mode set to
		 * VDSO_CLOCKMODE_TIMENS. For non समय namespace affected tasks
		 * this करोes not affect perक्रमmance because अगर vd->seq is
		 * odd, i.e. a concurrent update is in progress the extra
		 * check क्रम vd->घड़ी_mode is just a few extra
		 * inकाष्ठाions जबतक spin रुकोing क्रम vd->seq to become
		 * even again.
		 */
		जबतक (unlikely((seq = READ_ONCE(vd->seq)) & 1)) अणु
			अगर (IS_ENABLED(CONFIG_TIME_NS) &&
			    vd->घड़ी_mode == VDSO_CLOCKMODE_TIMENS)
				वापस करो_hres_समयns(vd, clk, ts);
			cpu_relax();
		पूर्ण
		smp_rmb();

		अगर (unlikely(!vdso_घड़ीsource_ok(vd)))
			वापस -1;

		cycles = __arch_get_hw_counter(vd->घड़ी_mode, vd);
		अगर (unlikely(!vdso_cycles_ok(cycles)))
			वापस -1;
		ns = vdso_ts->nsec;
		last = vd->cycle_last;
		ns += vdso_calc_delta(cycles, last, vd->mask, vd->mult);
		ns = vdso_shअगरt_ns(ns, vd->shअगरt);
		sec = vdso_ts->sec;
	पूर्ण जबतक (unlikely(vdso_पढ़ो_retry(vd, seq)));

	/*
	 * Do this outside the loop: a race inside the loop could result
	 * in __iter_भाग_u64_rem() being extremely slow.
	 */
	ts->tv_sec = sec + __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_TIME_NS
अटल __always_अंतरभूत पूर्णांक करो_coarse_समयns(स्थिर काष्ठा vdso_data *vdns, घड़ीid_t clk,
					    काष्ठा __kernel_बारpec *ts)
अणु
	स्थिर काष्ठा vdso_data *vd = __arch_get_समयns_vdso_data(vdns);
	स्थिर काष्ठा vdso_बारtamp *vdso_ts = &vd->baseसमय[clk];
	स्थिर काष्ठा समयns_offset *offs = &vdns->offset[clk];
	u64 nsec;
	s64 sec;
	s32 seq;

	करो अणु
		seq = vdso_पढ़ो_begin(vd);
		sec = vdso_ts->sec;
		nsec = vdso_ts->nsec;
	पूर्ण जबतक (unlikely(vdso_पढ़ो_retry(vd, seq)));

	/* Add the namespace offset */
	sec += offs->sec;
	nsec += offs->nsec;

	/*
	 * Do this outside the loop: a race inside the loop could result
	 * in __iter_भाग_u64_rem() being extremely slow.
	 */
	ts->tv_sec = sec + __iter_भाग_u64_rem(nsec, NSEC_PER_SEC, &nsec);
	ts->tv_nsec = nsec;
	वापस 0;
पूर्ण
#अन्यथा
अटल __always_अंतरभूत पूर्णांक करो_coarse_समयns(स्थिर काष्ठा vdso_data *vdns, घड़ीid_t clk,
					    काष्ठा __kernel_बारpec *ts)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत पूर्णांक करो_coarse(स्थिर काष्ठा vdso_data *vd, घड़ीid_t clk,
				     काष्ठा __kernel_बारpec *ts)
अणु
	स्थिर काष्ठा vdso_बारtamp *vdso_ts = &vd->baseसमय[clk];
	u32 seq;

	करो अणु
		/*
		 * Open coded to handle VDSO_CLOCK_TIMENS. See comment in
		 * करो_hres().
		 */
		जबतक ((seq = READ_ONCE(vd->seq)) & 1) अणु
			अगर (IS_ENABLED(CONFIG_TIME_NS) &&
			    vd->घड़ी_mode == VDSO_CLOCKMODE_TIMENS)
				वापस करो_coarse_समयns(vd, clk, ts);
			cpu_relax();
		पूर्ण
		smp_rmb();

		ts->tv_sec = vdso_ts->sec;
		ts->tv_nsec = vdso_ts->nsec;
	पूर्ण जबतक (unlikely(vdso_पढ़ो_retry(vd, seq)));

	वापस 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक
__cvdso_घड़ी_समय_लो_common(स्थिर काष्ठा vdso_data *vd, घड़ीid_t घड़ी,
			     काष्ठा __kernel_बारpec *ts)
अणु
	u32 msk;

	/* Check क्रम negative values or invalid घड़ीs */
	अगर (unlikely((u32) घड़ी >= MAX_CLOCKS))
		वापस -1;

	/*
	 * Convert the घड़ीid to a biपंचांगask and use it to check which
	 * घड़ीs are handled in the VDSO directly.
	 */
	msk = 1U << घड़ी;
	अगर (likely(msk & VDSO_HRES))
		vd = &vd[CS_HRES_COARSE];
	अन्यथा अगर (msk & VDSO_COARSE)
		वापस करो_coarse(&vd[CS_HRES_COARSE], घड़ी, ts);
	अन्यथा अगर (msk & VDSO_RAW)
		vd = &vd[CS_RAW];
	अन्यथा
		वापस -1;

	वापस करो_hres(vd, घड़ी, ts);
पूर्ण

अटल __maybe_unused पूर्णांक
__cvdso_घड़ी_समय_लो_data(स्थिर काष्ठा vdso_data *vd, घड़ीid_t घड़ी,
			   काष्ठा __kernel_बारpec *ts)
अणु
	पूर्णांक ret = __cvdso_घड़ी_समय_लो_common(vd, घड़ी, ts);

	अगर (unlikely(ret))
		वापस घड़ी_समय_लो_fallback(घड़ी, ts);
	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक
__cvdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *ts)
अणु
	वापस __cvdso_घड़ी_समय_लो_data(__arch_get_vdso_data(), घड़ी, ts);
पूर्ण

#अगर_घोषित BUILD_VDSO32
अटल __maybe_unused पूर्णांक
__cvdso_घड़ी_समय_लो32_data(स्थिर काष्ठा vdso_data *vd, घड़ीid_t घड़ी,
			     काष्ठा old_बारpec32 *res)
अणु
	काष्ठा __kernel_बारpec ts;
	पूर्णांक ret;

	ret = __cvdso_घड़ी_समय_लो_common(vd, घड़ी, &ts);

	अगर (unlikely(ret))
		वापस घड़ी_समय_लो32_fallback(घड़ी, res);

	/* For ret == 0 */
	res->tv_sec = ts.tv_sec;
	res->tv_nsec = ts.tv_nsec;

	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक
__cvdso_घड़ी_समय_लो32(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *res)
अणु
	वापस __cvdso_घड़ी_समय_लो32_data(__arch_get_vdso_data(), घड़ी, res);
पूर्ण
#पूर्ण_अगर /* BUILD_VDSO32 */

अटल __maybe_unused पूर्णांक
__cvdso_समय_लोofday_data(स्थिर काष्ठा vdso_data *vd,
			  काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु

	अगर (likely(tv != शून्य)) अणु
		काष्ठा __kernel_बारpec ts;

		अगर (करो_hres(&vd[CS_HRES_COARSE], CLOCK_REALTIME, &ts))
			वापस समय_लोofday_fallback(tv, tz);

		tv->tv_sec = ts.tv_sec;
		tv->tv_usec = (u32)ts.tv_nsec / NSEC_PER_USEC;
	पूर्ण

	अगर (unlikely(tz != शून्य)) अणु
		अगर (IS_ENABLED(CONFIG_TIME_NS) &&
		    vd->घड़ी_mode == VDSO_CLOCKMODE_TIMENS)
			vd = __arch_get_समयns_vdso_data(vd);

		tz->tz_minuteswest = vd[CS_HRES_COARSE].tz_minuteswest;
		tz->tz_dstसमय = vd[CS_HRES_COARSE].tz_dstसमय;
	पूर्ण

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक
__cvdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	वापस __cvdso_समय_लोofday_data(__arch_get_vdso_data(), tv, tz);
पूर्ण

#अगर_घोषित VDSO_HAS_TIME
अटल __maybe_unused __kernel_old_समय_प्रकार
__cvdso_समय_data(स्थिर काष्ठा vdso_data *vd, __kernel_old_समय_प्रकार *समय)
अणु
	__kernel_old_समय_प्रकार t;

	अगर (IS_ENABLED(CONFIG_TIME_NS) &&
	    vd->घड़ी_mode == VDSO_CLOCKMODE_TIMENS)
		vd = __arch_get_समयns_vdso_data(vd);

	t = READ_ONCE(vd[CS_HRES_COARSE].baseसमय[CLOCK_REALTIME].sec);

	अगर (समय)
		*समय = t;

	वापस t;
पूर्ण

अटल __maybe_unused __kernel_old_समय_प्रकार __cvdso_समय(__kernel_old_समय_प्रकार *समय)
अणु
	वापस __cvdso_समय_data(__arch_get_vdso_data(), समय);
पूर्ण
#पूर्ण_अगर /* VDSO_HAS_TIME */

#अगर_घोषित VDSO_HAS_CLOCK_GETRES
अटल __maybe_unused
पूर्णांक __cvdso_घड़ी_getres_common(स्थिर काष्ठा vdso_data *vd, घड़ीid_t घड़ी,
				काष्ठा __kernel_बारpec *res)
अणु
	u32 msk;
	u64 ns;

	/* Check क्रम negative values or invalid घड़ीs */
	अगर (unlikely((u32) घड़ी >= MAX_CLOCKS))
		वापस -1;

	अगर (IS_ENABLED(CONFIG_TIME_NS) &&
	    vd->घड़ी_mode == VDSO_CLOCKMODE_TIMENS)
		vd = __arch_get_समयns_vdso_data(vd);

	/*
	 * Convert the घड़ीid to a biपंचांगask and use it to check which
	 * घड़ीs are handled in the VDSO directly.
	 */
	msk = 1U << घड़ी;
	अगर (msk & (VDSO_HRES | VDSO_RAW)) अणु
		/*
		 * Preserves the behaviour of posix_get_hrसमयr_res().
		 */
		ns = READ_ONCE(vd[CS_HRES_COARSE].hrसमयr_res);
	पूर्ण अन्यथा अगर (msk & VDSO_COARSE) अणु
		/*
		 * Preserves the behaviour of posix_get_coarse_res().
		 */
		ns = LOW_RES_NSEC;
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	अगर (likely(res)) अणु
		res->tv_sec = 0;
		res->tv_nsec = ns;
	पूर्ण
	वापस 0;
पूर्ण

अटल __maybe_unused
पूर्णांक __cvdso_घड़ी_getres_data(स्थिर काष्ठा vdso_data *vd, घड़ीid_t घड़ी,
			      काष्ठा __kernel_बारpec *res)
अणु
	पूर्णांक ret = __cvdso_घड़ी_getres_common(vd, घड़ी, res);

	अगर (unlikely(ret))
		वापस घड़ी_getres_fallback(घड़ी, res);
	वापस 0;
पूर्ण

अटल __maybe_unused
पूर्णांक __cvdso_घड़ी_getres(घड़ीid_t घड़ी, काष्ठा __kernel_बारpec *res)
अणु
	वापस __cvdso_घड़ी_getres_data(__arch_get_vdso_data(), घड़ी, res);
पूर्ण

#अगर_घोषित BUILD_VDSO32
अटल __maybe_unused पूर्णांक
__cvdso_घड़ी_getres_समय32_data(स्थिर काष्ठा vdso_data *vd, घड़ीid_t घड़ी,
				 काष्ठा old_बारpec32 *res)
अणु
	काष्ठा __kernel_बारpec ts;
	पूर्णांक ret;

	ret = __cvdso_घड़ी_getres_common(vd, घड़ी, &ts);

	अगर (unlikely(ret))
		वापस घड़ी_getres32_fallback(घड़ी, res);

	अगर (likely(res)) अणु
		res->tv_sec = ts.tv_sec;
		res->tv_nsec = ts.tv_nsec;
	पूर्ण
	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक
__cvdso_घड़ी_getres_समय32(घड़ीid_t घड़ी, काष्ठा old_बारpec32 *res)
अणु
	वापस __cvdso_घड़ी_getres_समय32_data(__arch_get_vdso_data(),
						घड़ी, res);
पूर्ण
#पूर्ण_अगर /* BUILD_VDSO32 */
#पूर्ण_अगर /* VDSO_HAS_CLOCK_GETRES */
