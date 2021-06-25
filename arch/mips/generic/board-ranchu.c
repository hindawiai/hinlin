<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support code क्रम भव Ranchu board क्रम MIPS.
 *
 * Author: Miodrag Dinic <miodrag.dinic@mips.com>
 */

#समावेश <linux/of_address.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/machine.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/समय.स>

#घोषणा GOLDFISH_TIMER_LOW		0x00
#घोषणा GOLDFISH_TIMER_HIGH		0x04

अटल __init u64 पढ़ो_rtc_समय(व्योम __iomem *base)
अणु
	u32 समय_low;
	u32 समय_high;

	/*
	 * Reading the low address latches the high value
	 * as well so there is no fear that we may पढ़ो
	 * inaccurate high value.
	 */
	समय_low = पढ़ोl(base + GOLDFISH_TIMER_LOW);
	समय_high = पढ़ोl(base + GOLDFISH_TIMER_HIGH);

	वापस ((u64)समय_high << 32) | समय_low;
पूर्ण

अटल __init अचिन्हित पूर्णांक ranchu_measure_hpt_freq(व्योम)
अणु
	u64 rtc_start, rtc_current, rtc_delta;
	अचिन्हित पूर्णांक start, count;
	काष्ठा device_node *np;
	व्योम __iomem *rtc_base;

	np = of_find_compatible_node(शून्य, शून्य, "google,goldfish-rtc");
	अगर (!np)
		panic("%s(): Failed to find 'google,goldfish-rtc' dt node!",
		      __func__);

	rtc_base = of_iomap(np, 0);
	अगर (!rtc_base)
		panic("%s(): Failed to ioremap Goldfish RTC base!", __func__);

	/*
	 * Poll the nanosecond resolution RTC क्रम one
	 * second to calibrate the CPU frequency.
	 */
	rtc_start = पढ़ो_rtc_समय(rtc_base);
	start = पढ़ो_c0_count();

	करो अणु
		rtc_current = पढ़ो_rtc_समय(rtc_base);
		rtc_delta = rtc_current - rtc_start;
	पूर्ण जबतक (rtc_delta < NSEC_PER_SEC);

	count = पढ़ो_c0_count() - start;

	/*
	 * Make sure the frequency will be a round number.
	 * Without this correction, the वापसed value may vary
	 * between subsequent emulation executions.
	 *
	 * TODO: Set this value using device tree.
	 */
	count += 5000;
	count -= count % 10000;

	iounmap(rtc_base);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा of_device_id ranchu_of_match[] __initस्थिर = अणु
	अणु
		.compatible = "mti,ranchu",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

MIPS_MACHINE(ranchu) = अणु
	.matches = ranchu_of_match,
	.measure_hpt_freq = ranchu_measure_hpt_freq,
पूर्ण;
