<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा CSKY_PMU_MAX_EVENTS 32
#घोषणा DEFAULT_COUNT_WIDTH 48

#घोषणा HPCR		"<0, 0x0>"      /* PMU Control reg */
#घोषणा HPSPR		"<0, 0x1>"      /* Start PC reg */
#घोषणा HPEPR		"<0, 0x2>"      /* End PC reg */
#घोषणा HPSIR		"<0, 0x3>"      /* Soft Counter reg */
#घोषणा HPCNTENR	"<0, 0x4>"      /* Count Enable reg */
#घोषणा HPINTENR	"<0, 0x5>"      /* Interrupt Enable reg */
#घोषणा HPOFSR		"<0, 0x6>"      /* Interrupt Status reg */

/* The events क्रम a given PMU रेजिस्टर set. */
काष्ठा pmu_hw_events अणु
	/*
	 * The events that are active on the PMU क्रम the given index.
	 */
	काष्ठा perf_event *events[CSKY_PMU_MAX_EVENTS];

	/*
	 * A 1 bit क्रम an index indicates that the counter is being used क्रम
	 * an event. A 0 means that the counter can be used.
	 */
	अचिन्हित दीर्घ used_mask[BITS_TO_LONGS(CSKY_PMU_MAX_EVENTS)];
पूर्ण;

अटल uपूर्णांक64_t (*hw_raw_पढ़ो_mapping[CSKY_PMU_MAX_EVENTS])(व्योम);
अटल व्योम (*hw_raw_ग_लिखो_mapping[CSKY_PMU_MAX_EVENTS])(uपूर्णांक64_t val);

अटल काष्ठा csky_pmu_t अणु
	काष्ठा pmu			pmu;
	काष्ठा pmu_hw_events __percpu	*hw_events;
	काष्ठा platक्रमm_device		*plat_device;
	uपूर्णांक32_t			count_width;
	uपूर्णांक32_t			hpcr;
	u64				max_period;
पूर्ण csky_pmu;
अटल पूर्णांक csky_pmu_irq;

#घोषणा to_csky_pmu(p)  (container_of(p, काष्ठा csky_pmu, pmu))

#घोषणा cprgr(reg)				\
(अणु						\
	अचिन्हित पूर्णांक पंचांगp;			\
	यंत्र अस्थिर("cprgr %0, "reg"\n"	\
		     : "=r"(पंचांगp)		\
		     :				\
		     : "memory");		\
	पंचांगp;					\
पूर्ण)

#घोषणा cpwgr(reg, val)		\
(अणु				\
	यंत्र अस्थिर(		\
	"cpwgr %0, "reg"\n"	\
	:			\
	: "r"(val)		\
	: "memory");		\
पूर्ण)

#घोषणा cprcr(reg)				\
(अणु						\
	अचिन्हित पूर्णांक पंचांगp;			\
	यंत्र अस्थिर("cprcr %0, "reg"\n"	\
		     : "=r"(पंचांगp)		\
		     :				\
		     : "memory");		\
	पंचांगp;					\
पूर्ण)

#घोषणा cpwcr(reg, val)		\
(अणु				\
	यंत्र अस्थिर(		\
	"cpwcr %0, "reg"\n"	\
	:			\
	: "r"(val)		\
	: "memory");		\
पूर्ण)

/* cycle counter */
uपूर्णांक64_t csky_pmu_पढ़ो_cc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x3>");
		lo  = cprgr("<0, 0x2>");
		hi  = cprgr("<0, 0x3>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_cc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x2>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x3>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* inकाष्ठाion counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_ic(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x5>");
		lo  = cprgr("<0, 0x4>");
		hi  = cprgr("<0, 0x5>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_ic(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x4>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x5>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l1 icache access counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_icac(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x7>");
		lo  = cprgr("<0, 0x6>");
		hi  = cprgr("<0, 0x7>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_icac(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x6>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x7>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l1 icache miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_icmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x9>");
		lo  = cprgr("<0, 0x8>");
		hi  = cprgr("<0, 0x9>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_icmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x8>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x9>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l1 dcache access counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_dcac(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0xb>");
		lo  = cprgr("<0, 0xa>");
		hi  = cprgr("<0, 0xb>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_dcac(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0xa>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0xb>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l1 dcache miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_dcmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0xd>");
		lo  = cprgr("<0, 0xc>");
		hi  = cprgr("<0, 0xd>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_dcmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0xc>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0xd>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l2 cache access counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_l2ac(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0xf>");
		lo  = cprgr("<0, 0xe>");
		hi  = cprgr("<0, 0xf>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_l2ac(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0xe>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0xf>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l2 cache miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_l2mc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x11>");
		lo  = cprgr("<0, 0x10>");
		hi  = cprgr("<0, 0x11>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_l2mc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x10>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x11>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* I-UTLB miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_iutlbmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x15>");
		lo  = cprgr("<0, 0x14>");
		hi  = cprgr("<0, 0x15>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_iutlbmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x14>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x15>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* D-UTLB miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_dutlbmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x17>");
		lo  = cprgr("<0, 0x16>");
		hi  = cprgr("<0, 0x17>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_dutlbmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x16>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x17>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* JTLB miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_jtlbmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x19>");
		lo  = cprgr("<0, 0x18>");
		hi  = cprgr("<0, 0x19>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_jtlbmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x18>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x19>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* software counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_softc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x1b>");
		lo  = cprgr("<0, 0x1a>");
		hi  = cprgr("<0, 0x1b>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_softc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x1a>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x1b>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* conditional branch mispredict counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_cbmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x1d>");
		lo  = cprgr("<0, 0x1c>");
		hi  = cprgr("<0, 0x1d>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_cbmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x1c>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x1d>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* conditional branch inकाष्ठाion counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_cbic(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x1f>");
		lo  = cprgr("<0, 0x1e>");
		hi  = cprgr("<0, 0x1f>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_cbic(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x1e>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x1f>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* indirect branch mispredict counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_ibmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x21>");
		lo  = cprgr("<0, 0x20>");
		hi  = cprgr("<0, 0x21>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_ibmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x20>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x21>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* indirect branch inकाष्ठाion counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_ibic(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x23>");
		lo  = cprgr("<0, 0x22>");
		hi  = cprgr("<0, 0x23>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_ibic(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x22>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x23>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* LSU spec fail counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_lsfc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x25>");
		lo  = cprgr("<0, 0x24>");
		hi  = cprgr("<0, 0x25>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_lsfc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x24>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x25>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* store inकाष्ठाion counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_sic(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x27>");
		lo  = cprgr("<0, 0x26>");
		hi  = cprgr("<0, 0x27>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_sic(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x26>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x27>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* dcache पढ़ो access counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_dcrac(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x29>");
		lo  = cprgr("<0, 0x28>");
		hi  = cprgr("<0, 0x29>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_dcrac(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x28>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x29>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* dcache पढ़ो miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_dcrmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x2b>");
		lo  = cprgr("<0, 0x2a>");
		hi  = cprgr("<0, 0x2b>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_dcrmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x2a>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x2b>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* dcache ग_लिखो access counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_dcwac(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x2d>");
		lo  = cprgr("<0, 0x2c>");
		hi  = cprgr("<0, 0x2d>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_dcwac(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x2c>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x2d>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* dcache ग_लिखो miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_dcwmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x2f>");
		lo  = cprgr("<0, 0x2e>");
		hi  = cprgr("<0, 0x2f>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_dcwmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x2e>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x2f>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l2cache पढ़ो access counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_l2rac(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x31>");
		lo  = cprgr("<0, 0x30>");
		hi  = cprgr("<0, 0x31>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_l2rac(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x30>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x31>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l2cache पढ़ो miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_l2rmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x33>");
		lo  = cprgr("<0, 0x32>");
		hi  = cprgr("<0, 0x33>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_l2rmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x32>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x33>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l2cache ग_लिखो access counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_l2wac(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x35>");
		lo  = cprgr("<0, 0x34>");
		hi  = cprgr("<0, 0x35>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_l2wac(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x34>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x35>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

/* l2cache ग_लिखो miss counter */
अटल uपूर्णांक64_t csky_pmu_पढ़ो_l2wmc(व्योम)
अणु
	uपूर्णांक32_t lo, hi, पंचांगp;
	uपूर्णांक64_t result;

	करो अणु
		पंचांगp = cprgr("<0, 0x37>");
		lo  = cprgr("<0, 0x36>");
		hi  = cprgr("<0, 0x37>");
	पूर्ण जबतक (hi != पंचांगp);

	result = (uपूर्णांक64_t) (hi) << 32;
	result |= lo;

	वापस result;
पूर्ण

अटल व्योम csky_pmu_ग_लिखो_l2wmc(uपूर्णांक64_t val)
अणु
	cpwgr("<0, 0x36>", (uपूर्णांक32_t)  val);
	cpwgr("<0, 0x37>", (uपूर्णांक32_t) (val >> 32));
पूर्ण

#घोषणा HW_OP_UNSUPPORTED	0xffff
अटल स्थिर पूर्णांक csky_pmu_hw_map[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= 0x1,
	[PERF_COUNT_HW_INSTRUCTIONS]		= 0x2,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_CACHE_MISSES]		= HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= 0xf,
	[PERF_COUNT_HW_BRANCH_MISSES]		= 0xe,
	[PERF_COUNT_HW_BUS_CYCLES]		= HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_STALLED_CYCLES_FRONTEND]	= HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_STALLED_CYCLES_BACKEND]	= HW_OP_UNSUPPORTED,
	[PERF_COUNT_HW_REF_CPU_CYCLES]		= HW_OP_UNSUPPORTED,
पूर्ण;

#घोषणा C(_x)			PERF_COUNT_HW_CACHE_##_x
#घोषणा CACHE_OP_UNSUPPORTED	0xffff
अटल स्थिर पूर्णांक csky_pmu_cache_map[C(MAX)][C(OP_MAX)][C(RESULT_MAX)] = अणु
	[C(L1D)] = अणु
#अगर_घोषित CONFIG_CPU_CK810
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x5,
			[C(RESULT_MISS)]	= 0x6,
		पूर्ण,
#अन्यथा
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x14,
			[C(RESULT_MISS)]	= 0x15,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x16,
			[C(RESULT_MISS)]	= 0x17,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
#पूर्ण_अगर
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x3,
			[C(RESULT_MISS)]	= 0x4,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु
#अगर_घोषित CONFIG_CPU_CK810
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= 0x7,
			[C(RESULT_MISS)]	= 0x8,
		पूर्ण,
#अन्यथा
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x18,
			[C(RESULT_MISS)]	= 0x19,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x1a,
			[C(RESULT_MISS)]	= 0x1b,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
#पूर्ण_अगर
	पूर्ण,
	[C(DTLB)] = अणु
#अगर_घोषित CONFIG_CPU_CK810
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
#अन्यथा
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x14,
			[C(RESULT_MISS)]	= 0xb,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= 0x16,
			[C(RESULT_MISS)]	= 0xb,
		पूर्ण,
#पूर्ण_अगर
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
#अगर_घोषित CONFIG_CPU_CK810
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
#अन्यथा
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= 0x3,
			[C(RESULT_MISS)]	= 0xa,
		पूर्ण,
#पूर्ण_अगर
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
	[C(NODE)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)]	= CACHE_OP_UNSUPPORTED,
			[C(RESULT_MISS)]	= CACHE_OP_UNSUPPORTED,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक  csky_pmu_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 left = local64_पढ़ो(&hwc->period_left);
	s64 period = hwc->sample_period;
	पूर्णांक ret = 0;

	अगर (unlikely(left <= -period)) अणु
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (unlikely(left <= 0)) अणु
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (left > (s64)csky_pmu.max_period)
		left = csky_pmu.max_period;

	/*
	 * The hw event starts counting from this event offset,
	 * mark it to be able to extract future "deltas":
	 */
	local64_set(&hwc->prev_count, (u64)(-left));

	अगर (hw_raw_ग_लिखो_mapping[hwc->idx] != शून्य)
		hw_raw_ग_लिखो_mapping[hwc->idx]((u64)(-left) &
						csky_pmu.max_period);

	cpwcr(HPOFSR, ~BIT(hwc->idx) & cprcr(HPOFSR));

	perf_event_update_userpage(event);

	वापस ret;
पूर्ण

अटल व्योम csky_perf_event_update(काष्ठा perf_event *event,
				   काष्ठा hw_perf_event *hwc)
अणु
	uपूर्णांक64_t prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	/*
	 * Sign extend count value to 64bit, otherwise delta calculation
	 * would be incorrect when overflow occurs.
	 */
	uपूर्णांक64_t new_raw_count = sign_extend64(
		hw_raw_पढ़ो_mapping[hwc->idx](), csky_pmu.count_width - 1);
	पूर्णांक64_t delta = new_raw_count - prev_raw_count;

	/*
	 * We aren't afraid of hwc->prev_count changing beneath our feet
	 * because there's no way क्रम us to re-enter this function anyसमय.
	 */
	local64_set(&hwc->prev_count, new_raw_count);
	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);
पूर्ण

अटल व्योम csky_pmu_reset(व्योम *info)
अणु
	cpwcr(HPCR, BIT(31) | BIT(30) | BIT(1));
पूर्ण

अटल व्योम csky_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	csky_perf_event_update(event, &event->hw);
पूर्ण

अटल पूर्णांक csky_pmu_cache_event(u64 config)
अणु
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result;

	cache_type	= (config >>  0) & 0xff;
	cache_op	= (config >>  8) & 0xff;
	cache_result	= (config >> 16) & 0xff;

	अगर (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		वापस -EINVAL;
	अगर (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		वापस -EINVAL;
	अगर (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	वापस csky_pmu_cache_map[cache_type][cache_op][cache_result];
पूर्ण

अटल पूर्णांक csky_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक ret;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		अगर (event->attr.config >= PERF_COUNT_HW_MAX)
			वापस -ENOENT;
		ret = csky_pmu_hw_map[event->attr.config];
		अगर (ret == HW_OP_UNSUPPORTED)
			वापस -ENOENT;
		hwc->idx = ret;
		अवरोध;
	हाल PERF_TYPE_HW_CACHE:
		ret = csky_pmu_cache_event(event->attr.config);
		अगर (ret == CACHE_OP_UNSUPPORTED)
			वापस -ENOENT;
		hwc->idx = ret;
		अवरोध;
	हाल PERF_TYPE_RAW:
		अगर (hw_raw_पढ़ो_mapping[event->attr.config] == शून्य)
			वापस -ENOENT;
		hwc->idx = event->attr.config;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (event->attr.exclude_user)
		csky_pmu.hpcr = BIT(2);
	अन्यथा अगर (event->attr.exclude_kernel)
		csky_pmu.hpcr = BIT(3);
	अन्यथा
		csky_pmu.hpcr = BIT(2) | BIT(3);

	csky_pmu.hpcr |= BIT(1) | BIT(0);

	वापस 0;
पूर्ण

/* starts all counters */
अटल व्योम csky_pmu_enable(काष्ठा pmu *pmu)
अणु
	cpwcr(HPCR, csky_pmu.hpcr);
पूर्ण

/* stops all counters */
अटल व्योम csky_pmu_disable(काष्ठा pmu *pmu)
अणु
	cpwcr(HPCR, BIT(1));
पूर्ण

अटल व्योम csky_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अचिन्हित दीर्घ flg;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (WARN_ON_ONCE(idx == -1))
		वापस;

	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	csky_pmu_event_set_period(event);

	local_irq_save(flg);

	cpwcr(HPINTENR, BIT(idx) | cprcr(HPINTENR));
	cpwcr(HPCNTENR, BIT(idx) | cprcr(HPCNTENR));

	local_irq_restore(flg);
पूर्ण

अटल व्योम csky_pmu_stop_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flg;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	local_irq_save(flg);

	cpwcr(HPINTENR, ~BIT(idx) & cprcr(HPINTENR));
	cpwcr(HPCNTENR, ~BIT(idx) & cprcr(HPCNTENR));

	local_irq_restore(flg);
पूर्ण

अटल व्योम csky_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (!(event->hw.state & PERF_HES_STOPPED)) अणु
		csky_pmu_stop_event(event);
		event->hw.state |= PERF_HES_STOPPED;
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) &&
	    !(event->hw.state & PERF_HES_UPTODATE)) अणु
		csky_perf_event_update(event, &event->hw);
		event->hw.state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल व्योम csky_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा pmu_hw_events *hw_events = this_cpu_ptr(csky_pmu.hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	csky_pmu_stop(event, PERF_EF_UPDATE);

	hw_events->events[hwc->idx] = शून्य;

	perf_event_update_userpage(event);
पूर्ण

/* allocate hardware counter and optionally start counting */
अटल पूर्णांक csky_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा pmu_hw_events *hw_events = this_cpu_ptr(csky_pmu.hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	hw_events->events[hwc->idx] = event;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START)
		csky_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल irqवापस_t csky_pmu_handle_irq(पूर्णांक irq_num, व्योम *dev)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा pmu_hw_events *cpuc = this_cpu_ptr(csky_pmu.hw_events);
	काष्ठा pt_regs *regs;
	पूर्णांक idx;

	/*
	 * Did an overflow occur?
	 */
	अगर (!cprcr(HPOFSR))
		वापस IRQ_NONE;

	/*
	 * Handle the counter(s) overflow(s)
	 */
	regs = get_irq_regs();

	csky_pmu_disable(&csky_pmu.pmu);

	क्रम (idx = 0; idx < CSKY_PMU_MAX_EVENTS; ++idx) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		काष्ठा hw_perf_event *hwc;

		/* Ignore अगर we करोn't have an event. */
		अगर (!event)
			जारी;
		/*
		 * We have a single पूर्णांकerrupt क्रम all counters. Check that
		 * each counter has overflowed beक्रमe we process it.
		 */
		अगर (!(cprcr(HPOFSR) & BIT(idx)))
			जारी;

		hwc = &event->hw;
		csky_perf_event_update(event, &event->hw);
		perf_sample_data_init(&data, 0, hwc->last_period);
		csky_pmu_event_set_period(event);

		अगर (perf_event_overflow(event, &data, regs))
			csky_pmu_stop_event(event);
	पूर्ण

	csky_pmu_enable(&csky_pmu.pmu);

	/*
	 * Handle the pending perf events.
	 *
	 * Note: this call *must* be run with पूर्णांकerrupts disabled. For
	 * platक्रमms that can have the PMU पूर्णांकerrupts उठाओd as an NMI, this
	 * will not work.
	 */
	irq_work_run();

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक csky_pmu_request_irq(irq_handler_t handler)
अणु
	पूर्णांक err, irqs;
	काष्ठा platक्रमm_device *pmu_device = csky_pmu.plat_device;

	अगर (!pmu_device)
		वापस -ENODEV;

	irqs = min(pmu_device->num_resources, num_possible_cpus());
	अगर (irqs < 1) अणु
		pr_err("no irqs for PMUs defined\n");
		वापस -ENODEV;
	पूर्ण

	csky_pmu_irq = platक्रमm_get_irq(pmu_device, 0);
	अगर (csky_pmu_irq < 0)
		वापस -ENODEV;
	err = request_percpu_irq(csky_pmu_irq, handler, "csky-pmu",
				 this_cpu_ptr(csky_pmu.hw_events));
	अगर (err) अणु
		pr_err("unable to request IRQ%d for CSKY PMU counters\n",
		       csky_pmu_irq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम csky_pmu_मुक्त_irq(व्योम)
अणु
	पूर्णांक irq;
	काष्ठा platक्रमm_device *pmu_device = csky_pmu.plat_device;

	irq = platक्रमm_get_irq(pmu_device, 0);
	अगर (irq >= 0)
		मुक्त_percpu_irq(irq, this_cpu_ptr(csky_pmu.hw_events));
पूर्ण

पूर्णांक init_hw_perf_events(व्योम)
अणु
	csky_pmu.hw_events = alloc_percpu_gfp(काष्ठा pmu_hw_events,
					      GFP_KERNEL);
	अगर (!csky_pmu.hw_events) अणु
		pr_info("failed to allocate per-cpu PMU data.\n");
		वापस -ENOMEM;
	पूर्ण

	csky_pmu.pmu = (काष्ठा pmu) अणु
		.pmu_enable	= csky_pmu_enable,
		.pmu_disable	= csky_pmu_disable,
		.event_init	= csky_pmu_event_init,
		.add		= csky_pmu_add,
		.del		= csky_pmu_del,
		.start		= csky_pmu_start,
		.stop		= csky_pmu_stop,
		.पढ़ो		= csky_pmu_पढ़ो,
	पूर्ण;

	स_रखो((व्योम *)hw_raw_पढ़ो_mapping, 0,
		माप(hw_raw_पढ़ो_mapping[CSKY_PMU_MAX_EVENTS]));

	hw_raw_पढ़ो_mapping[0x1]  = csky_pmu_पढ़ो_cc;
	hw_raw_पढ़ो_mapping[0x2]  = csky_pmu_पढ़ो_ic;
	hw_raw_पढ़ो_mapping[0x3]  = csky_pmu_पढ़ो_icac;
	hw_raw_पढ़ो_mapping[0x4]  = csky_pmu_पढ़ो_icmc;
	hw_raw_पढ़ो_mapping[0x5]  = csky_pmu_पढ़ो_dcac;
	hw_raw_पढ़ो_mapping[0x6]  = csky_pmu_पढ़ो_dcmc;
	hw_raw_पढ़ो_mapping[0x7]  = csky_pmu_पढ़ो_l2ac;
	hw_raw_पढ़ो_mapping[0x8]  = csky_pmu_पढ़ो_l2mc;
	hw_raw_पढ़ो_mapping[0xa]  = csky_pmu_पढ़ो_iutlbmc;
	hw_raw_पढ़ो_mapping[0xb]  = csky_pmu_पढ़ो_dutlbmc;
	hw_raw_पढ़ो_mapping[0xc]  = csky_pmu_पढ़ो_jtlbmc;
	hw_raw_पढ़ो_mapping[0xd]  = csky_pmu_पढ़ो_softc;
	hw_raw_पढ़ो_mapping[0xe]  = csky_pmu_पढ़ो_cbmc;
	hw_raw_पढ़ो_mapping[0xf]  = csky_pmu_पढ़ो_cbic;
	hw_raw_पढ़ो_mapping[0x10] = csky_pmu_पढ़ो_ibmc;
	hw_raw_पढ़ो_mapping[0x11] = csky_pmu_पढ़ो_ibic;
	hw_raw_पढ़ो_mapping[0x12] = csky_pmu_पढ़ो_lsfc;
	hw_raw_पढ़ो_mapping[0x13] = csky_pmu_पढ़ो_sic;
	hw_raw_पढ़ो_mapping[0x14] = csky_pmu_पढ़ो_dcrac;
	hw_raw_पढ़ो_mapping[0x15] = csky_pmu_पढ़ो_dcrmc;
	hw_raw_पढ़ो_mapping[0x16] = csky_pmu_पढ़ो_dcwac;
	hw_raw_पढ़ो_mapping[0x17] = csky_pmu_पढ़ो_dcwmc;
	hw_raw_पढ़ो_mapping[0x18] = csky_pmu_पढ़ो_l2rac;
	hw_raw_पढ़ो_mapping[0x19] = csky_pmu_पढ़ो_l2rmc;
	hw_raw_पढ़ो_mapping[0x1a] = csky_pmu_पढ़ो_l2wac;
	hw_raw_पढ़ो_mapping[0x1b] = csky_pmu_पढ़ो_l2wmc;

	स_रखो((व्योम *)hw_raw_ग_लिखो_mapping, 0,
		माप(hw_raw_ग_लिखो_mapping[CSKY_PMU_MAX_EVENTS]));

	hw_raw_ग_लिखो_mapping[0x1]  = csky_pmu_ग_लिखो_cc;
	hw_raw_ग_लिखो_mapping[0x2]  = csky_pmu_ग_लिखो_ic;
	hw_raw_ग_लिखो_mapping[0x3]  = csky_pmu_ग_लिखो_icac;
	hw_raw_ग_लिखो_mapping[0x4]  = csky_pmu_ग_लिखो_icmc;
	hw_raw_ग_लिखो_mapping[0x5]  = csky_pmu_ग_लिखो_dcac;
	hw_raw_ग_लिखो_mapping[0x6]  = csky_pmu_ग_लिखो_dcmc;
	hw_raw_ग_लिखो_mapping[0x7]  = csky_pmu_ग_लिखो_l2ac;
	hw_raw_ग_लिखो_mapping[0x8]  = csky_pmu_ग_लिखो_l2mc;
	hw_raw_ग_लिखो_mapping[0xa]  = csky_pmu_ग_लिखो_iutlbmc;
	hw_raw_ग_लिखो_mapping[0xb]  = csky_pmu_ग_लिखो_dutlbmc;
	hw_raw_ग_लिखो_mapping[0xc]  = csky_pmu_ग_लिखो_jtlbmc;
	hw_raw_ग_लिखो_mapping[0xd]  = csky_pmu_ग_लिखो_softc;
	hw_raw_ग_लिखो_mapping[0xe]  = csky_pmu_ग_लिखो_cbmc;
	hw_raw_ग_लिखो_mapping[0xf]  = csky_pmu_ग_लिखो_cbic;
	hw_raw_ग_लिखो_mapping[0x10] = csky_pmu_ग_लिखो_ibmc;
	hw_raw_ग_लिखो_mapping[0x11] = csky_pmu_ग_लिखो_ibic;
	hw_raw_ग_लिखो_mapping[0x12] = csky_pmu_ग_लिखो_lsfc;
	hw_raw_ग_लिखो_mapping[0x13] = csky_pmu_ग_लिखो_sic;
	hw_raw_ग_लिखो_mapping[0x14] = csky_pmu_ग_लिखो_dcrac;
	hw_raw_ग_लिखो_mapping[0x15] = csky_pmu_ग_लिखो_dcrmc;
	hw_raw_ग_लिखो_mapping[0x16] = csky_pmu_ग_लिखो_dcwac;
	hw_raw_ग_लिखो_mapping[0x17] = csky_pmu_ग_लिखो_dcwmc;
	hw_raw_ग_लिखो_mapping[0x18] = csky_pmu_ग_लिखो_l2rac;
	hw_raw_ग_लिखो_mapping[0x19] = csky_pmu_ग_लिखो_l2rmc;
	hw_raw_ग_लिखो_mapping[0x1a] = csky_pmu_ग_लिखो_l2wac;
	hw_raw_ग_लिखो_mapping[0x1b] = csky_pmu_ग_लिखो_l2wmc;

	वापस 0;
पूर्ण

अटल पूर्णांक csky_pmu_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	enable_percpu_irq(csky_pmu_irq, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक csky_pmu_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(csky_pmu_irq);
	वापस 0;
पूर्ण

पूर्णांक csky_pmu_device_probe(काष्ठा platक्रमm_device *pdev,
			  स्थिर काष्ठा of_device_id *of_table)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	पूर्णांक ret;

	ret = init_hw_perf_events();
	अगर (ret) अणु
		pr_notice("[perf] failed to probe PMU!\n");
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "count-width",
				 &csky_pmu.count_width)) अणु
		csky_pmu.count_width = DEFAULT_COUNT_WIDTH;
	पूर्ण
	csky_pmu.max_period = BIT_ULL(csky_pmu.count_width) - 1;

	csky_pmu.plat_device = pdev;

	/* Ensure the PMU has sane values out of reset. */
	on_each_cpu(csky_pmu_reset, &csky_pmu, 1);

	ret = csky_pmu_request_irq(csky_pmu_handle_irq);
	अगर (ret) अणु
		csky_pmu.pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;
		pr_notice("[perf] PMU request irq fail!\n");
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_PERF_CSKY_ONLINE, "AP_PERF_ONLINE",
				csky_pmu_starting_cpu,
				csky_pmu_dying_cpu);
	अगर (ret) अणु
		csky_pmu_मुक्त_irq();
		मुक्त_percpu(csky_pmu.hw_events);
		वापस ret;
	पूर्ण

	ret = perf_pmu_रेजिस्टर(&csky_pmu.pmu, "cpu", PERF_TYPE_RAW);
	अगर (ret) अणु
		csky_pmu_मुक्त_irq();
		मुक्त_percpu(csky_pmu.hw_events);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id csky_pmu_of_device_ids[] = अणु
	अणु.compatible = "csky,csky-pmu"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक csky_pmu_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस csky_pmu_device_probe(pdev, csky_pmu_of_device_ids);
पूर्ण

अटल काष्ठा platक्रमm_driver csky_pmu_driver = अणु
	.driver = अणु
		   .name = "csky-pmu",
		   .of_match_table = csky_pmu_of_device_ids,
		   पूर्ण,
	.probe = csky_pmu_dev_probe,
पूर्ण;

अटल पूर्णांक __init csky_pmu_probe(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&csky_pmu_driver);
	अगर (ret)
		pr_notice("[perf] PMU initialization failed\n");
	अन्यथा
		pr_notice("[perf] PMU initialization done\n");

	वापस ret;
पूर्ण

device_initcall(csky_pmu_probe);
