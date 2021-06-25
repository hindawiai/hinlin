<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  linux/include/linux/घड़ीsource.h
 *
 *  This file contains the काष्ठाure definitions क्रम घड़ीsources.
 *
 *  If you are not a घड़ीsource, or समयkeeping code, you should
 *  not be including this file!
 */
#अगर_अघोषित _LINUX_CLOCKSOURCE_H
#घोषणा _LINUX_CLOCKSOURCE_H

#समावेश <linux/types.h>
#समावेश <linux/समयx.h>
#समावेश <linux/समय.स>
#समावेश <linux/list.h>
#समावेश <linux/cache.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/घड़ीsource_ids.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/पन.स>

काष्ठा घड़ीsource;
काष्ठा module;

#अगर defined(CONFIG_ARCH_CLOCKSOURCE_DATA) || \
    defined(CONFIG_GENERIC_GETTIMखातापूर्णDAY)
#समावेश <यंत्र/घड़ीsource.h>
#पूर्ण_अगर

#समावेश <vdso/घड़ीsource.h>

/**
 * काष्ठा घड़ीsource - hardware असलtraction क्रम a मुक्त running counter
 *	Provides mostly state-मुक्त accessors to the underlying hardware.
 *	This is the काष्ठाure used क्रम प्रणाली समय.
 *
 * @पढ़ो:		Returns a cycle value, passes घड़ीsource as argument
 * @mask:		Biपंचांगask क्रम two's complement
 *			subtraction of non 64 bit counters
 * @mult:		Cycle to nanosecond multiplier
 * @shअगरt:		Cycle to nanosecond भागisor (घातer of two)
 * @max_idle_ns:	Maximum idle समय permitted by the घड़ीsource (nsecs)
 * @maxadj:		Maximum adjusपंचांगent value to mult (~11%)
 * @archdata:		Optional arch-specअगरic data
 * @max_cycles:		Maximum safe cycle value which won't overflow on
 *			multiplication
 * @name:		Poपूर्णांकer to घड़ीsource name
 * @list:		List head क्रम registration (पूर्णांकernal)
 * @rating:		Rating value क्रम selection (higher is better)
 *			To aव्योम rating inflation the following
 *			list should give you a guide as to how
 *			to assign your घड़ीsource a rating
 *			1-99: Unfit क्रम real use
 *				Only available क्रम bootup and testing purposes.
 *			100-199: Base level usability.
 *				Functional क्रम real use, but not desired.
 *			200-299: Good.
 *				A correct and usable घड़ीsource.
 *			300-399: Desired.
 *				A reasonably fast and accurate घड़ीsource.
 *			400-499: Perfect
 *				The ideal घड़ीsource. A must-use where
 *				available.
 * @id:			Defaults to CSID_GENERIC. The id value is captured
 *			in certain snapshot functions to allow callers to
 *			validate the घड़ीsource from which the snapshot was
 *			taken.
 * @flags:		Flags describing special properties
 * @enable:		Optional function to enable the घड़ीsource
 * @disable:		Optional function to disable the घड़ीsource
 * @suspend:		Optional suspend function क्रम the घड़ीsource
 * @resume:		Optional resume function क्रम the घड़ीsource
 * @mark_unstable:	Optional function to inक्रमm the घड़ीsource driver that
 *			the watchकरोg marked the घड़ीsource unstable
 * @tick_stable:        Optional function called periodically from the watchकरोg
 *			code to provide stable synchronization poपूर्णांकs
 * @wd_list:		List head to enqueue पूर्णांकo the watchकरोg list (पूर्णांकernal)
 * @cs_last:		Last घड़ीsource value क्रम घड़ीsource watchकरोg
 * @wd_last:		Last watchकरोg value corresponding to @cs_last
 * @owner:		Module reference, must be set by घड़ीsource in modules
 *
 * Note: This काष्ठा is not used in hotpathes of the समयkeeping code
 * because the समयkeeper caches the hot path fields in its own data
 * काष्ठाure, so no cache line alignment is required,
 *
 * The poपूर्णांकer to the घड़ीsource itself is handed to the पढ़ो
 * callback. If you need extra inक्रमmation there you can wrap काष्ठा
 * घड़ीsource पूर्णांकo your own काष्ठा. Depending on the amount of
 * inक्रमmation you need you should consider to cache line align that
 * काष्ठाure.
 */
काष्ठा घड़ीsource अणु
	u64			(*पढ़ो)(काष्ठा घड़ीsource *cs);
	u64			mask;
	u32			mult;
	u32			shअगरt;
	u64			max_idle_ns;
	u32			maxadj;
#अगर_घोषित CONFIG_ARCH_CLOCKSOURCE_DATA
	काष्ठा arch_घड़ीsource_data archdata;
#पूर्ण_अगर
	u64			max_cycles;
	स्थिर अक्षर		*name;
	काष्ठा list_head	list;
	पूर्णांक			rating;
	क्रमागत घड़ीsource_ids	id;
	क्रमागत vdso_घड़ी_mode	vdso_घड़ी_mode;
	अचिन्हित दीर्घ		flags;

	पूर्णांक			(*enable)(काष्ठा घड़ीsource *cs);
	व्योम			(*disable)(काष्ठा घड़ीsource *cs);
	व्योम			(*suspend)(काष्ठा घड़ीsource *cs);
	व्योम			(*resume)(काष्ठा घड़ीsource *cs);
	व्योम			(*mark_unstable)(काष्ठा घड़ीsource *cs);
	व्योम			(*tick_stable)(काष्ठा घड़ीsource *cs);

	/* निजी: */
#अगर_घोषित CONFIG_CLOCKSOURCE_WATCHDOG
	/* Watchकरोg related data, used by the framework */
	काष्ठा list_head	wd_list;
	u64			cs_last;
	u64			wd_last;
#पूर्ण_अगर
	काष्ठा module		*owner;
पूर्ण;

/*
 * Clock source flags bits::
 */
#घोषणा CLOCK_SOURCE_IS_CONTINUOUS		0x01
#घोषणा CLOCK_SOURCE_MUST_VERIFY		0x02

#घोषणा CLOCK_SOURCE_WATCHDOG			0x10
#घोषणा CLOCK_SOURCE_VALID_FOR_HRES		0x20
#घोषणा CLOCK_SOURCE_UNSTABLE			0x40
#घोषणा CLOCK_SOURCE_SUSPEND_NONSTOP		0x80
#घोषणा CLOCK_SOURCE_RESELECT			0x100

/* simplअगरy initialization of mask field */
#घोषणा CLOCKSOURCE_MASK(bits) GENMASK_ULL((bits) - 1, 0)

अटल अंतरभूत u32 घड़ीsource_freq2mult(u32 freq, u32 shअगरt_स्थिरant, u64 from)
अणु
	/*  freq = cyc/from
	 *  mult/2^shअगरt  = ns/cyc
	 *  mult = ns/cyc * 2^shअगरt
	 *  mult = from/freq * 2^shअगरt
	 *  mult = from * 2^shअगरt / freq
	 *  mult = (from<<shअगरt) / freq
	 */
	u64 पंचांगp = ((u64)from) << shअगरt_स्थिरant;

	पंचांगp += freq/2; /* round क्रम करो_भाग */
	करो_भाग(पंचांगp, freq);

	वापस (u32)पंचांगp;
पूर्ण

/**
 * घड़ीsource_khz2mult - calculates mult from khz and shअगरt
 * @khz:		Clocksource frequency in KHz
 * @shअगरt_स्थिरant:	Clocksource shअगरt factor
 *
 * Helper functions that converts a khz counter frequency to a timsource
 * multiplier, given the घड़ीsource shअगरt value
 */
अटल अंतरभूत u32 घड़ीsource_khz2mult(u32 khz, u32 shअगरt_स्थिरant)
अणु
	वापस घड़ीsource_freq2mult(khz, shअगरt_स्थिरant, NSEC_PER_MSEC);
पूर्ण

/**
 * घड़ीsource_hz2mult - calculates mult from hz and shअगरt
 * @hz:			Clocksource frequency in Hz
 * @shअगरt_स्थिरant:	Clocksource shअगरt factor
 *
 * Helper functions that converts a hz counter
 * frequency to a timsource multiplier, given the
 * घड़ीsource shअगरt value
 */
अटल अंतरभूत u32 घड़ीsource_hz2mult(u32 hz, u32 shअगरt_स्थिरant)
अणु
	वापस घड़ीsource_freq2mult(hz, shअगरt_स्थिरant, NSEC_PER_SEC);
पूर्ण

/**
 * घड़ीsource_cyc2ns - converts घड़ीsource cycles to nanoseconds
 * @cycles:	cycles
 * @mult:	cycle to nanosecond multiplier
 * @shअगरt:	cycle to nanosecond भागisor (घातer of two)
 *
 * Converts घड़ीsource cycles to nanoseconds, using the given @mult and @shअगरt.
 * The code is optimized क्रम perक्रमmance and is not पूर्णांकended to work
 * with असलolute घड़ीsource cycles (as those will easily overflow),
 * but is only पूर्णांकended to be used with relative (delta) घड़ीsource cycles.
 *
 * XXX - This could use some mult_lxl_ll() यंत्र optimization
 */
अटल अंतरभूत s64 घड़ीsource_cyc2ns(u64 cycles, u32 mult, u32 shअगरt)
अणु
	वापस ((u64) cycles * mult) >> shअगरt;
पूर्ण


बाह्य पूर्णांक घड़ीsource_unरेजिस्टर(काष्ठा घड़ीsource*);
बाह्य व्योम घड़ीsource_touch_watchकरोg(व्योम);
बाह्य व्योम घड़ीsource_change_rating(काष्ठा घड़ीsource *cs, पूर्णांक rating);
बाह्य व्योम घड़ीsource_suspend(व्योम);
बाह्य व्योम घड़ीsource_resume(व्योम);
बाह्य काष्ठा घड़ीsource * __init घड़ीsource_शेष_घड़ी(व्योम);
बाह्य व्योम घड़ीsource_mark_unstable(काष्ठा घड़ीsource *cs);
बाह्य व्योम
घड़ीsource_start_suspend_timing(काष्ठा घड़ीsource *cs, u64 start_cycles);
बाह्य u64 घड़ीsource_stop_suspend_timing(काष्ठा घड़ीsource *cs, u64 now);

बाह्य u64
घड़ीs_calc_max_nsecs(u32 mult, u32 shअगरt, u32 maxadj, u64 mask, u64 *max_cycles);
बाह्य व्योम
घड़ीs_calc_mult_shअगरt(u32 *mult, u32 *shअगरt, u32 from, u32 to, u32 minsec);

/*
 * Don't call __घड़ीsource_रेजिस्टर_scale directly, use
 * घड़ीsource_रेजिस्टर_hz/khz
 */
बाह्य पूर्णांक
__घड़ीsource_रेजिस्टर_scale(काष्ठा घड़ीsource *cs, u32 scale, u32 freq);
बाह्य व्योम
__घड़ीsource_update_freq_scale(काष्ठा घड़ीsource *cs, u32 scale, u32 freq);

/*
 * Don't call this unless you are a शेष घड़ीsource
 * (AKA: jअगरfies) and असलolutely have to.
 */
अटल अंतरभूत पूर्णांक __घड़ीsource_रेजिस्टर(काष्ठा घड़ीsource *cs)
अणु
	वापस __घड़ीsource_रेजिस्टर_scale(cs, 1, 0);
पूर्ण

अटल अंतरभूत पूर्णांक घड़ीsource_रेजिस्टर_hz(काष्ठा घड़ीsource *cs, u32 hz)
अणु
	वापस __घड़ीsource_रेजिस्टर_scale(cs, 1, hz);
पूर्ण

अटल अंतरभूत पूर्णांक घड़ीsource_रेजिस्टर_khz(काष्ठा घड़ीsource *cs, u32 khz)
अणु
	वापस __घड़ीsource_रेजिस्टर_scale(cs, 1000, khz);
पूर्ण

अटल अंतरभूत व्योम __घड़ीsource_update_freq_hz(काष्ठा घड़ीsource *cs, u32 hz)
अणु
	__घड़ीsource_update_freq_scale(cs, 1, hz);
पूर्ण

अटल अंतरभूत व्योम __घड़ीsource_update_freq_khz(काष्ठा घड़ीsource *cs, u32 khz)
अणु
	__घड़ीsource_update_freq_scale(cs, 1000, khz);
पूर्ण

#अगर_घोषित CONFIG_ARCH_CLOCKSOURCE_INIT
बाह्य व्योम घड़ीsource_arch_init(काष्ठा घड़ीsource *cs);
#अन्यथा
अटल अंतरभूत व्योम घड़ीsource_arch_init(काष्ठा घड़ीsource *cs) अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक समयkeeping_notअगरy(काष्ठा घड़ीsource *घड़ी);

बाह्य u64 घड़ीsource_mmio_पढ़ोl_up(काष्ठा घड़ीsource *);
बाह्य u64 घड़ीsource_mmio_पढ़ोl_करोwn(काष्ठा घड़ीsource *);
बाह्य u64 घड़ीsource_mmio_पढ़ोw_up(काष्ठा घड़ीsource *);
बाह्य u64 घड़ीsource_mmio_पढ़ोw_करोwn(काष्ठा घड़ीsource *);

बाह्य पूर्णांक घड़ीsource_mmio_init(व्योम __iomem *, स्थिर अक्षर *,
	अचिन्हित दीर्घ, पूर्णांक, अचिन्हित, u64 (*)(काष्ठा घड़ीsource *));

बाह्य पूर्णांक घड़ीsource_i8253_init(व्योम);

#घोषणा TIMER_OF_DECLARE(name, compat, fn) \
	OF_DECLARE_1_RET(समयr, name, compat, fn)

#अगर_घोषित CONFIG_TIMER_PROBE
बाह्य व्योम समयr_probe(व्योम);
#अन्यथा
अटल अंतरभूत व्योम समयr_probe(व्योम) अणुपूर्ण
#पूर्ण_अगर

#घोषणा TIMER_ACPI_DECLARE(name, table_id, fn)		\
	ACPI_DECLARE_PROBE_ENTRY(समयr, name, table_id, 0, शून्य, 0, fn)

#पूर्ण_अगर /* _LINUX_CLOCKSOURCE_H */
