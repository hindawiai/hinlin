<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * This file contains the jअगरfies based घड़ीsource.
 *
 * Copyright (C) 2004, 2005 IBM, John Stultz (johnstul@us.ibm.com)
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश "timekeeping.h"


/* Since jअगरfies uses a simple TICK_NSEC multiplier
 * conversion, the .shअगरt value could be zero. However
 * this would make NTP adjusपंचांगents impossible as they are
 * in units of 1/2^.shअगरt. Thus we use JIFFIES_SHIFT to
 * shअगरt both the nominator and denominator the same
 * amount, and give ntp adjusपंचांगents in units of 1/2^8
 *
 * The value 8 is somewhat carefully chosen, as anything
 * larger can result in overflows. TICK_NSEC grows as HZ
 * shrinks, so values greater than 8 overflow 32bits when
 * HZ=100.
 */
#अगर HZ < 34
#घोषणा JIFFIES_SHIFT	6
#या_अगर HZ < 67
#घोषणा JIFFIES_SHIFT	7
#अन्यथा
#घोषणा JIFFIES_SHIFT	8
#पूर्ण_अगर

अटल u64 jअगरfies_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64) jअगरfies;
पूर्ण

/*
 * The Jअगरfies based घड़ीsource is the lowest common
 * denominator घड़ी source which should function on
 * all प्रणालीs. It has the same coarse resolution as
 * the समयr पूर्णांकerrupt frequency HZ and it suffers
 * inaccuracies caused by missed or lost समयr
 * पूर्णांकerrupts and the inability क्रम the समयr
 * पूर्णांकerrupt hardware to accurately tick at the
 * requested HZ value. It is also not recommended
 * क्रम "tick-less" प्रणालीs.
 */
अटल काष्ठा घड़ीsource घड़ीsource_jअगरfies = अणु
	.name		= "jiffies",
	.rating		= 1, /* lowest valid rating*/
	.पढ़ो		= jअगरfies_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.mult		= TICK_NSEC << JIFFIES_SHIFT, /* details above */
	.shअगरt		= JIFFIES_SHIFT,
	.max_cycles	= 10,
पूर्ण;

__cacheline_aligned_in_smp DEFINE_RAW_SPINLOCK(jअगरfies_lock);
__cacheline_aligned_in_smp seqcount_raw_spinlock_t jअगरfies_seq =
	SEQCNT_RAW_SPINLOCK_ZERO(jअगरfies_seq, &jअगरfies_lock);

#अगर (BITS_PER_LONG < 64)
u64 get_jअगरfies_64(व्योम)
अणु
	अचिन्हित पूर्णांक seq;
	u64 ret;

	करो अणु
		seq = पढ़ो_seqcount_begin(&jअगरfies_seq);
		ret = jअगरfies_64;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&jअगरfies_seq, seq));
	वापस ret;
पूर्ण
EXPORT_SYMBOL(get_jअगरfies_64);
#पूर्ण_अगर

EXPORT_SYMBOL(jअगरfies);

अटल पूर्णांक __init init_jअगरfies_घड़ीsource(व्योम)
अणु
	वापस __घड़ीsource_रेजिस्टर(&घड़ीsource_jअगरfies);
पूर्ण

core_initcall(init_jअगरfies_घड़ीsource);

काष्ठा घड़ीsource * __init __weak घड़ीsource_शेष_घड़ी(व्योम)
अणु
	वापस &घड़ीsource_jअगरfies;
पूर्ण

अटल काष्ठा घड़ीsource refined_jअगरfies;

पूर्णांक रेजिस्टर_refined_jअगरfies(दीर्घ cycles_per_second)
अणु
	u64 nsec_per_tick, shअगरt_hz;
	दीर्घ cycles_per_tick;



	refined_jअगरfies = घड़ीsource_jअगरfies;
	refined_jअगरfies.name = "refined-jiffies";
	refined_jअगरfies.rating++;

	/* Calc cycles per tick */
	cycles_per_tick = (cycles_per_second + HZ/2)/HZ;
	/* shअगरt_hz stores hz<<8 क्रम extra accuracy */
	shअगरt_hz = (u64)cycles_per_second << 8;
	shअगरt_hz += cycles_per_tick/2;
	करो_भाग(shअगरt_hz, cycles_per_tick);
	/* Calculate nsec_per_tick using shअगरt_hz */
	nsec_per_tick = (u64)NSEC_PER_SEC << 8;
	nsec_per_tick += (u32)shअगरt_hz/2;
	करो_भाग(nsec_per_tick, (u32)shअगरt_hz);

	refined_jअगरfies.mult = ((u32)nsec_per_tick) << JIFFIES_SHIFT;

	__घड़ीsource_रेजिस्टर(&refined_jअगरfies);
	वापस 0;
पूर्ण
