<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/compiler.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/vdso_समयr_info.h>
#समावेश <यंत्र/यंत्र-offsets.h>

#घोषणा X(x) #x
#घोषणा Y(x) X(x)

बाह्य काष्ठा vdso_data *__get_datapage(व्योम);
बाह्य काष्ठा vdso_data *__get_समयrpage(व्योम);

अटल notrace अचिन्हित पूर्णांक __vdso_पढ़ो_begin(स्थिर काष्ठा vdso_data *vdata)
अणु
	u32 seq;
repeat:
	seq = READ_ONCE(vdata->seq_count);
	अगर (seq & 1) अणु
		cpu_relax();
		जाओ repeat;
	पूर्ण
	वापस seq;
पूर्ण

अटल notrace अचिन्हित पूर्णांक vdso_पढ़ो_begin(स्थिर काष्ठा vdso_data *vdata)
अणु
	अचिन्हित पूर्णांक seq;

	seq = __vdso_पढ़ो_begin(vdata);

	smp_rmb();		/* Pairs with smp_wmb in vdso_ग_लिखो_end */
	वापस seq;
पूर्ण

अटल notrace पूर्णांक vdso_पढ़ो_retry(स्थिर काष्ठा vdso_data *vdata, u32 start)
अणु
	smp_rmb();		/* Pairs with smp_wmb in vdso_ग_लिखो_begin */
	वापस vdata->seq_count != start;
पूर्ण

अटल notrace दीर्घ घड़ी_समय_लो_fallback(घड़ीid_t _clkid,
					   काष्ठा __kernel_old_बारpec *_ts)
अणु
	रेजिस्टर काष्ठा __kernel_old_बारpec *ts यंत्र("$r1") = _ts;
	रेजिस्टर घड़ीid_t clkid यंत्र("$r0") = _clkid;
	रेजिस्टर दीर्घ ret यंत्र("$r0");

	यंत्र अस्थिर ("movi	$r15, %3\n"
		      "syscall 	0x0\n"
		      :"=r" (ret)
		      :"r"(clkid), "r"(ts), "i"(__NR_घड़ी_समय_लो)
		      :"$r15", "memory");

	वापस ret;
पूर्ण

अटल notrace पूर्णांक करो_realसमय_coarse(काष्ठा __kernel_old_बारpec *ts,
				      काष्ठा vdso_data *vdata)
अणु
	u32 seq;

	करो अणु
		seq = vdso_पढ़ो_begin(vdata);

		ts->tv_sec = vdata->xसमय_coarse_sec;
		ts->tv_nsec = vdata->xसमय_coarse_nsec;

	पूर्ण जबतक (vdso_पढ़ो_retry(vdata, seq));
	वापस 0;
पूर्ण

अटल notrace पूर्णांक करो_monotonic_coarse(काष्ठा __kernel_old_बारpec *ts,
				       काष्ठा vdso_data *vdata)
अणु
	u32 seq;
	u64 ns;

	करो अणु
		seq = vdso_पढ़ो_begin(vdata);

		ts->tv_sec = vdata->xसमय_coarse_sec + vdata->wपंचांग_घड़ी_sec;
		ns = vdata->xसमय_coarse_nsec + vdata->wपंचांग_घड़ी_nsec;

	पूर्ण जबतक (vdso_पढ़ो_retry(vdata, seq));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

अटल notrace अंतरभूत u64 vमाला_लोns(काष्ठा vdso_data *vdso)
अणु
	u32 cycle_now;
	u32 cycle_delta;
	u32 *समयr_cycle_base;

	समयr_cycle_base =
	    (u32 *) ((अक्षर *)__get_समयrpage() + vdso->cycle_count_offset);
	cycle_now = पढ़ोl_relaxed(समयr_cycle_base);
	अगर (true == vdso->cycle_count_करोwn)
		cycle_now = ~(*समयr_cycle_base);
	cycle_delta = cycle_now - (u32) vdso->cs_cycle_last;
	वापस ((u64) cycle_delta & vdso->cs_mask) * vdso->cs_mult;
पूर्ण

अटल notrace पूर्णांक करो_realसमय(काष्ठा __kernel_old_बारpec *ts, काष्ठा vdso_data *vdata)
अणु
	अचिन्हित count;
	u64 ns;
	करो अणु
		count = vdso_पढ़ो_begin(vdata);
		ts->tv_sec = vdata->xसमय_घड़ी_sec;
		ns = vdata->xसमय_घड़ी_nsec;
		ns += vमाला_लोns(vdata);
		ns >>= vdata->cs_shअगरt;
	पूर्ण जबतक (vdso_पढ़ो_retry(vdata, count));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

अटल notrace पूर्णांक करो_monotonic(काष्ठा __kernel_old_बारpec *ts, काष्ठा vdso_data *vdata)
अणु
	u64 ns;
	u32 seq;

	करो अणु
		seq = vdso_पढ़ो_begin(vdata);

		ts->tv_sec = vdata->xसमय_घड़ी_sec;
		ns = vdata->xसमय_घड़ी_nsec;
		ns += vमाला_लोns(vdata);
		ns >>= vdata->cs_shअगरt;

		ts->tv_sec += vdata->wपंचांग_घड़ी_sec;
		ns += vdata->wपंचांग_घड़ी_nsec;

	पूर्ण जबतक (vdso_पढ़ो_retry(vdata, seq));

	ts->tv_sec += __iter_भाग_u64_rem(ns, NSEC_PER_SEC, &ns);
	ts->tv_nsec = ns;

	वापस 0;
पूर्ण

notrace पूर्णांक __vdso_घड़ी_समय_लो(घड़ीid_t clkid, काष्ठा __kernel_old_बारpec *ts)
अणु
	काष्ठा vdso_data *vdata;
	पूर्णांक ret = -1;

	vdata = __get_datapage();
	अगर (vdata->cycle_count_offset == EMPTY_REG_OFFSET)
		वापस घड़ी_समय_लो_fallback(clkid, ts);

	चयन (clkid) अणु
	हाल CLOCK_REALTIME_COARSE:
		ret = करो_realसमय_coarse(ts, vdata);
		अवरोध;
	हाल CLOCK_MONOTONIC_COARSE:
		ret = करो_monotonic_coarse(ts, vdata);
		अवरोध;
	हाल CLOCK_REALTIME:
		ret = करो_realसमय(ts, vdata);
		अवरोध;
	हाल CLOCK_MONOTONIC:
		ret = करो_monotonic(ts, vdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret)
		ret = घड़ी_समय_लो_fallback(clkid, ts);

	वापस ret;
पूर्ण

अटल notrace पूर्णांक घड़ी_getres_fallback(घड़ीid_t _clk_id,
					  काष्ठा __kernel_old_बारpec *_res)
अणु
	रेजिस्टर घड़ीid_t clk_id यंत्र("$r0") = _clk_id;
	रेजिस्टर काष्ठा __kernel_old_बारpec *res यंत्र("$r1") = _res;
	रेजिस्टर पूर्णांक ret यंत्र("$r0");

	यंत्र अस्थिर ("movi	$r15, %3\n"
		      "syscall	0x0\n"
		      :"=r" (ret)
		      :"r"(clk_id), "r"(res), "i"(__NR_घड़ी_getres)
		      :"$r15", "memory");

	वापस ret;
पूर्ण

notrace पूर्णांक __vdso_घड़ी_getres(घड़ीid_t clk_id, काष्ठा __kernel_old_बारpec *res)
अणु
	काष्ठा vdso_data *vdata = __get_datapage();

	अगर (res == शून्य)
		वापस 0;
	चयन (clk_id) अणु
	हाल CLOCK_REALTIME:
	हाल CLOCK_MONOTONIC:
	हाल CLOCK_MONOTONIC_RAW:
		res->tv_sec = 0;
		res->tv_nsec = vdata->hrसमयr_res;
		अवरोध;
	हाल CLOCK_REALTIME_COARSE:
	हाल CLOCK_MONOTONIC_COARSE:
		res->tv_sec = 0;
		res->tv_nsec = CLOCK_COARSE_RES;
		अवरोध;
	शेष:
		वापस घड़ी_getres_fallback(clk_id, res);
	पूर्ण
	वापस 0;
पूर्ण

अटल notrace अंतरभूत पूर्णांक समय_लोofday_fallback(काष्ठा __kernel_old_समयval *_tv,
						काष्ठा समयzone *_tz)
अणु
	रेजिस्टर काष्ठा __kernel_old_समयval *tv यंत्र("$r0") = _tv;
	रेजिस्टर काष्ठा समयzone *tz यंत्र("$r1") = _tz;
	रेजिस्टर पूर्णांक ret यंत्र("$r0");

	यंत्र अस्थिर ("movi	$r15, %3\n"
		      "syscall	0x0\n"
		      :"=r" (ret)
		      :"r"(tv), "r"(tz), "i"(__NR_समय_लोofday)
		      :"$r15", "memory");

	वापस ret;
पूर्ण

notrace पूर्णांक __vdso_समय_लोofday(काष्ठा __kernel_old_समयval *tv, काष्ठा समयzone *tz)
अणु
	काष्ठा __kernel_old_बारpec ts;
	काष्ठा vdso_data *vdata;
	पूर्णांक ret;

	vdata = __get_datapage();

	अगर (vdata->cycle_count_offset == EMPTY_REG_OFFSET)
		वापस समय_लोofday_fallback(tv, tz);

	ret = करो_realसमय(&ts, vdata);

	अगर (tv) अणु
		tv->tv_sec = ts.tv_sec;
		tv->tv_usec = ts.tv_nsec / 1000;
	पूर्ण
	अगर (tz) अणु
		tz->tz_minuteswest = vdata->tz_minuteswest;
		tz->tz_dstसमय = vdata->tz_dstसमय;
	पूर्ण

	वापस ret;
पूर्ण
