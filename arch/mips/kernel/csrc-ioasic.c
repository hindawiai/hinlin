<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  DEC I/O ASIC's counter घड़ीsource
 *
 *  Copyright (C) 2008	Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ds1287.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/dec/ioasic.h>
#समावेश <यंत्र/dec/ioasic_addrs.h>

अटल u64 dec_ioasic_hpt_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस ioasic_पढ़ो(IO_REG_FCTR);
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_dec = अणु
	.name		= "dec-ioasic",
	.पढ़ो		= dec_ioasic_hpt_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u64 notrace dec_ioasic_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ioasic_पढ़ो(IO_REG_FCTR);
पूर्ण

पूर्णांक __init dec_ioasic_घड़ीsource_init(व्योम)
अणु
	अचिन्हित पूर्णांक freq;
	u32 start, end;
	पूर्णांक i = HZ / 8;

	ds1287_समयr_state();
	जबतक (!ds1287_समयr_state())
		;

	start = dec_ioasic_hpt_पढ़ो(&घड़ीsource_dec);

	जबतक (i--)
		जबतक (!ds1287_समयr_state())
			;

	end = dec_ioasic_hpt_पढ़ो(&घड़ीsource_dec);

	freq = (end - start) * 8;

	/* An early revision of the I/O ASIC didn't have the counter.  */
	अगर (!freq)
		वापस -ENXIO;

	prपूर्णांकk(KERN_INFO "I/O ASIC clock frequency %dHz\n", freq);

	घड़ीsource_dec.rating = 200 + freq / 10000000;
	घड़ीsource_रेजिस्टर_hz(&घड़ीsource_dec, freq);

	sched_घड़ी_रेजिस्टर(dec_ioasic_पढ़ो_sched_घड़ी, 32, freq);

	वापस 0;
पूर्ण
