<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006 Andi Kleen, SUSE Lअसल.
 *
 * Fast user context implementation of घड़ी_समय_लो, समय_लोofday, and समय.
 *
 * The code should have no पूर्णांकernal unresolved relocations.
 * Check with पढ़ोelf after changing.
 * Also alternative() करोesn't work.
 */
/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/घड़ीsource.h>
#समावेश <यंत्र/vvar.h>

#अगर_घोषित	CONFIG_SPARC64
#घोषणा SYSCALL_STRING							\
	"ta	0x6d;"							\
	"bcs,a	1f;"							\
	" sub	%%g0, %%o0, %%o0;"					\
	"1:"
#अन्यथा
#घोषणा SYSCALL_STRING							\
	"ta	0x10;"							\
	"bcs,a	1f;"							\
	" sub	%%g0, %%o0, %%o0;"					\
	"1:"
#पूर्ण_अगर

#घोषणा SYSCALL_CLOBBERS						\
	"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",			\
	"f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",		\
	"f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",		\
	"f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31",		\
	"f32", "f34", "f36", "f38", "f40", "f42", "f44", "f46",		\
	"f48", "f50", "f52", "f54", "f56", "f58", "f60", "f62",		\
	"cc", "memory"

/*
 * Compute the vvar page's address in the process address space, and वापस it
 * as a poपूर्णांकer to the vvar_data.
 */
notrace अटल __always_अंतरभूत काष्ठा vvar_data *get_vvar_data(व्योम)
अणु
	अचिन्हित दीर्घ ret;

	/*
	 * vdso data page is the first vDSO page so grab the PC
	 * and move up a page to get to the data page.
	 */
	__यंत्र__("rd %%pc, %0" : "=r" (ret));
	ret &= ~(8192 - 1);
	ret -= 8192;

	वापस (काष्ठा vvar_data *) ret;
पूर्ण

notrace अटल दीर्घ vdso_fallback_समय_लो(दीर्घ घड़ी, काष्ठा __kernel_old_बारpec *ts)
अणु
	रेजिस्टर दीर्घ num __यंत्र__("g1") = __NR_घड़ी_समय_लो;
	रेजिस्टर दीर्घ o0 __यंत्र__("o0") = घड़ी;
	रेजिस्टर दीर्घ o1 __यंत्र__("o1") = (दीर्घ) ts;

	__यंत्र__ __अस्थिर__(SYSCALL_STRING : "=r" (o0) : "r" (num),
			     "0" (o0), "r" (o1) : SYSCALL_CLOBBERS);
	वापस o0;
पूर्ण

notrace अटल दीर्घ vdso_fallback_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	रेजिस्टर दीर्घ num __यंत्र__("g1") = __NR_समय_लोofday;
	रेजिस्टर दीर्घ o0 __यंत्र__("o0") = (दीर्घ) tv;
	रेजिस्टर दीर्घ o1 __यंत्र__("o1") = (दीर्घ) tz;

	__यंत्र__ __अस्थिर__(SYSCALL_STRING : "=r" (o0) : "r" (num),
			     "0" (o0), "r" (o1) : SYSCALL_CLOBBERS);
	वापस o0;
पूर्ण

#अगर_घोषित	CONFIG_SPARC64
notrace अटल __always_अंतरभूत u64 vपढ़ो_tick(व्योम)
अणु
	u64	ret;

	__यंत्र__ __अस्थिर__("rd %%tick, %0" : "=r" (ret));
	वापस ret;
पूर्ण

notrace अटल __always_अंतरभूत u64 vपढ़ो_tick_stick(व्योम)
अणु
	u64	ret;

	__यंत्र__ __अस्थिर__("rd %%asr24, %0" : "=r" (ret));
	वापस ret;
पूर्ण
#अन्यथा
notrace अटल __always_अंतरभूत u64 vपढ़ो_tick(व्योम)
अणु
	रेजिस्टर अचिन्हित दीर्घ दीर्घ ret यंत्र("o4");

	__यंत्र__ __अस्थिर__("rd %%tick, %L0\n\t"
			     "srlx %L0, 32, %H0"
			     : "=r" (ret));
	वापस ret;
पूर्ण

notrace अटल __always_अंतरभूत u64 vपढ़ो_tick_stick(व्योम)
अणु
	रेजिस्टर अचिन्हित दीर्घ दीर्घ ret यंत्र("o4");

	__यंत्र__ __अस्थिर__("rd %%asr24, %L0\n\t"
			     "srlx %L0, 32, %H0"
			     : "=r" (ret));
	वापस ret;
पूर्ण
#पूर्ण_अगर

notrace अटल __always_अंतरभूत u64 vमाला_लोns(काष्ठा vvar_data *vvar)
अणु
	u64 v;
	u64 cycles;

	cycles = vपढ़ो_tick();
	v = (cycles - vvar->घड़ी.cycle_last) & vvar->घड़ी.mask;
	वापस v * vvar->घड़ी.mult;
पूर्ण

notrace अटल __always_अंतरभूत u64 vमाला_लोns_stick(काष्ठा vvar_data *vvar)
अणु
	u64 v;
	u64 cycles;

	cycles = vपढ़ो_tick_stick();
	v = (cycles - vvar->घड़ी.cycle_last) & vvar->घड़ी.mask;
	वापस v * vvar->घड़ी.mult;
पूर्ण

notrace अटल __always_अंतरभूत पूर्णांक करो_realसमय(काष्ठा vvar_data *vvar,
					       काष्ठा __kernel_old_बारpec *ts)
अणु
	अचिन्हित दीर्घ seq;
	u64 ns;

	करो अणु
		seq = vvar_पढ़ो_begin(vvar);
		ts->tv_sec = vvar->wall_समय_sec;
		ns = vvar->wall_समय_snsec;
		ns += vमाला_लोns(vvar);
		ns >>= vvar->घड़ी.shअगरt;
	पूर्ण जबतक (unlikely(vvar_पढ़ो_retry(vvar, seq)));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

notrace अटल __always_अंतरभूत पूर्णांक करो_realसमय_stick(काष्ठा vvar_data *vvar,
						     काष्ठा __kernel_old_बारpec *ts)
अणु
	अचिन्हित दीर्घ seq;
	u64 ns;

	करो अणु
		seq = vvar_पढ़ो_begin(vvar);
		ts->tv_sec = vvar->wall_समय_sec;
		ns = vvar->wall_समय_snsec;
		ns += vमाला_लोns_stick(vvar);
		ns >>= vvar->घड़ी.shअगरt;
	पूर्ण जबतक (unlikely(vvar_पढ़ो_retry(vvar, seq)));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

notrace अटल __always_अंतरभूत पूर्णांक करो_monotonic(काष्ठा vvar_data *vvar,
						काष्ठा __kernel_old_बारpec *ts)
अणु
	अचिन्हित दीर्घ seq;
	u64 ns;

	करो अणु
		seq = vvar_पढ़ो_begin(vvar);
		ts->tv_sec = vvar->monotonic_समय_sec;
		ns = vvar->monotonic_समय_snsec;
		ns += vमाला_लोns(vvar);
		ns >>= vvar->घड़ी.shअगरt;
	पूर्ण जबतक (unlikely(vvar_पढ़ो_retry(vvar, seq)));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

notrace अटल __always_अंतरभूत पूर्णांक करो_monotonic_stick(काष्ठा vvar_data *vvar,
						      काष्ठा __kernel_old_बारpec *ts)
अणु
	अचिन्हित दीर्घ seq;
	u64 ns;

	करो अणु
		seq = vvar_पढ़ो_begin(vvar);
		ts->tv_sec = vvar->monotonic_समय_sec;
		ns = vvar->monotonic_समय_snsec;
		ns += vमाला_लोns_stick(vvar);
		ns >>= vvar->घड़ी.shअगरt;
	पूर्ण जबतक (unlikely(vvar_पढ़ो_retry(vvar, seq)));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

notrace अटल पूर्णांक करो_realसमय_coarse(काष्ठा vvar_data *vvar,
				      काष्ठा __kernel_old_बारpec *ts)
अणु
	अचिन्हित दीर्घ seq;

	करो अणु
		seq = vvar_पढ़ो_begin(vvar);
		ts->tv_sec = vvar->wall_समय_coarse_sec;
		ts->tv_nsec = vvar->wall_समय_coarse_nsec;
	पूर्ण जबतक (unlikely(vvar_पढ़ो_retry(vvar, seq)));
	वापस 0;
पूर्ण

notrace अटल पूर्णांक करो_monotonic_coarse(काष्ठा vvar_data *vvar,
				       काष्ठा __kernel_old_बारpec *ts)
अणु
	अचिन्हित दीर्घ seq;

	करो अणु
		seq = vvar_पढ़ो_begin(vvar);
		ts->tv_sec = vvar->monotonic_समय_coarse_sec;
		ts->tv_nsec = vvar->monotonic_समय_coarse_nsec;
	पूर्ण जबतक (unlikely(vvar_पढ़ो_retry(vvar, seq)));

	वापस 0;
पूर्ण

notrace पूर्णांक
__vdso_घड़ी_समय_लो(घड़ीid_t घड़ी, काष्ठा __kernel_old_बारpec *ts)
अणु
	काष्ठा vvar_data *vvd = get_vvar_data();

	चयन (घड़ी) अणु
	हाल CLOCK_REALTIME:
		अगर (unlikely(vvd->vघड़ी_mode == VCLOCK_NONE))
			अवरोध;
		वापस करो_realसमय(vvd, ts);
	हाल CLOCK_MONOTONIC:
		अगर (unlikely(vvd->vघड़ी_mode == VCLOCK_NONE))
			अवरोध;
		वापस करो_monotonic(vvd, ts);
	हाल CLOCK_REALTIME_COARSE:
		वापस करो_realसमय_coarse(vvd, ts);
	हाल CLOCK_MONOTONIC_COARSE:
		वापस करो_monotonic_coarse(vvd, ts);
	पूर्ण
	/*
	 * Unknown घड़ी ID ? Fall back to the syscall.
	 */
	वापस vdso_fallback_समय_लो(घड़ी, ts);
पूर्ण
पूर्णांक
घड़ी_समय_लो(घड़ीid_t, काष्ठा __kernel_old_बारpec *)
	__attribute__((weak, alias("__vdso_clock_gettime")));

notrace पूर्णांक
__vdso_घड़ी_समय_लो_stick(घड़ीid_t घड़ी, काष्ठा __kernel_old_बारpec *ts)
अणु
	काष्ठा vvar_data *vvd = get_vvar_data();

	चयन (घड़ी) अणु
	हाल CLOCK_REALTIME:
		अगर (unlikely(vvd->vघड़ी_mode == VCLOCK_NONE))
			अवरोध;
		वापस करो_realसमय_stick(vvd, ts);
	हाल CLOCK_MONOTONIC:
		अगर (unlikely(vvd->vघड़ी_mode == VCLOCK_NONE))
			अवरोध;
		वापस करो_monotonic_stick(vvd, ts);
	हाल CLOCK_REALTIME_COARSE:
		वापस करो_realसमय_coarse(vvd, ts);
	हाल CLOCK_MONOTONIC_COARSE:
		वापस करो_monotonic_coarse(vvd, ts);
	पूर्ण
	/*
	 * Unknown घड़ी ID ? Fall back to the syscall.
	 */
	वापस vdso_fallback_समय_लो(घड़ी, ts);
पूर्ण

notrace पूर्णांक
__vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	काष्ठा vvar_data *vvd = get_vvar_data();

	अगर (likely(vvd->vघड़ी_mode != VCLOCK_NONE)) अणु
		अगर (likely(tv != शून्य)) अणु
			जोड़ tstv_t अणु
				काष्ठा __kernel_old_बारpec ts;
				काष्ठा __kernel_old_समयval tv;
			पूर्ण *tstv = (जोड़ tstv_t *) tv;
			करो_realसमय(vvd, &tstv->ts);
			/*
			 * Assign beक्रमe भागiding to ensure that the भागision is
			 * करोne in the type of tv_usec, not tv_nsec.
			 *
			 * There cannot be > 1 billion usec in a second:
			 * करो_realसमय() has alपढ़ोy distributed such overflow
			 * पूर्णांकo tv_sec.  So we can assign it to an पूर्णांक safely.
			 */
			tstv->tv.tv_usec = tstv->ts.tv_nsec;
			tstv->tv.tv_usec /= 1000;
		पूर्ण
		अगर (unlikely(tz != शून्य)) अणु
			/* Aव्योम स_नकल. Some old compilers fail to अंतरभूत it */
			tz->tz_minuteswest = vvd->tz_minuteswest;
			tz->tz_dstसमय = vvd->tz_dstसमय;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस vdso_fallback_समय_लोofday(tv, tz);
पूर्ण
पूर्णांक
समय_लोofday(काष्ठा __kernel_old_समयval *, काष्ठा समयzone *)
	__attribute__((weak, alias("__vdso_gettimeofday")));

notrace पूर्णांक
__vdso_समय_लोofday_stick(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	काष्ठा vvar_data *vvd = get_vvar_data();

	अगर (likely(vvd->vघड़ी_mode != VCLOCK_NONE)) अणु
		अगर (likely(tv != शून्य)) अणु
			जोड़ tstv_t अणु
				काष्ठा __kernel_old_बारpec ts;
				काष्ठा __kernel_old_समयval tv;
			पूर्ण *tstv = (जोड़ tstv_t *) tv;
			करो_realसमय_stick(vvd, &tstv->ts);
			/*
			 * Assign beक्रमe भागiding to ensure that the भागision is
			 * करोne in the type of tv_usec, not tv_nsec.
			 *
			 * There cannot be > 1 billion usec in a second:
			 * करो_realसमय() has alपढ़ोy distributed such overflow
			 * पूर्णांकo tv_sec.  So we can assign it to an पूर्णांक safely.
			 */
			tstv->tv.tv_usec = tstv->ts.tv_nsec;
			tstv->tv.tv_usec /= 1000;
		पूर्ण
		अगर (unlikely(tz != शून्य)) अणु
			/* Aव्योम स_नकल. Some old compilers fail to अंतरभूत it */
			tz->tz_minuteswest = vvd->tz_minuteswest;
			tz->tz_dstसमय = vvd->tz_dstसमय;
		पूर्ण
		वापस 0;
	पूर्ण
	वापस vdso_fallback_समय_लोofday(tv, tz);
पूर्ण
