<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* समयr.h: System समयr definitions क्रम sun5.
 *
 * Copyright (C) 1997, 2008 David S. Miller (davem@davemloft.net)
 */

#अगर_अघोषित _SPARC64_TIMER_H
#घोषणा _SPARC64_TIMER_H

#समावेश <uapi/यंत्र/asi.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>

/* The most frequently accessed fields should be first,
 * to fit पूर्णांकo the same cacheline.
 */
काष्ठा sparc64_tick_ops अणु
	अचिन्हित दीर्घ ticks_per_nsec_quotient;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ दीर्घ (*get_tick)(व्योम);
	पूर्णांक (*add_compare)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ softपूर्णांक_mask;
	व्योम (*disable_irq)(व्योम);

	व्योम (*init_tick)(व्योम);
	अचिन्हित दीर्घ (*add_tick)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ (*get_frequency)(व्योम);
	अचिन्हित दीर्घ frequency;

	अक्षर *name;
पूर्ण;

बाह्य काष्ठा sparc64_tick_ops *tick_ops;

अचिन्हित दीर्घ sparc64_get_घड़ी_प्रकारick(अचिन्हित पूर्णांक cpu);
व्योम setup_sparc64_समयr(व्योम);
व्योम __init समय_init(व्योम);

#घोषणा TICK_PRIV_BIT		BIT(63)
#घोषणा TICKCMP_IRQ_BIT		BIT(63)

#घोषणा HBIRD_STICKCMP_ADDR	0x1fe0000f060UL
#घोषणा HBIRD_STICK_ADDR	0x1fe0000f070UL

#घोषणा GET_TICK_NINSTR		13
काष्ठा get_tick_patch अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	tick[GET_TICK_NINSTR];
	अचिन्हित पूर्णांक	stick[GET_TICK_NINSTR];
पूर्ण;

बाह्य काष्ठा get_tick_patch __get_tick_patch;
बाह्य काष्ठा get_tick_patch __get_tick_patch_end;

अटल अंतरभूत अचिन्हित दीर्घ get_tick(व्योम)
अणु
	अचिन्हित दीर्घ tick, पंचांगp1, पंचांगp2;

	__यंत्र__ __अस्थिर__(
	/* पढ़ो hbtick 13 inकाष्ठाions */
	"661:\n"
	"	mov	0x1fe, %1\n"
	"	sllx	%1, 0x20, %1\n"
	"	sethi	%%hi(0xf000), %2\n"
	"	or	%2, 0x70, %2\n"
	"	or	%1, %2, %1\n"	/* %1 = HBIRD_STICK_ADDR */
	"	add	%1, 8, %2\n"
	"	ldxa	[%2]%3, %0\n"
	"	ldxa	[%1]%3, %1\n"
	"	ldxa	[%2]%3, %2\n"
	"	sub	%2, %0, %0\n"	/* करोn't modअगरy %xcc */
	"	brnz,pn	%0, 661b\n"	/* restart to save one रेजिस्टर */
	"	 sllx	%2, 32, %2\n"
	"	or	%2, %1, %0\n"
	/* Common/not patched code */
	"	sllx	%0, 1, %0\n"
	"	srlx	%0, 1, %0\n"	/* Clear TICK_PRIV_BIT */
	/* Beginning of patch section */
	"	.section .get_tick_patch, \"ax\"\n"
	"	.word	661b\n"
	/* पढ़ो tick 2 inकाष्ठाions and 11 skipped */
	"	ba	1f\n"
	"	 rd	%%tick, %0\n"
	"	.skip	4 * (%4 - 2)\n"
	"1:\n"
	/* पढ़ो stick 2 inकाष्ठाions and 11 skipped */
	"	ba	1f\n"
	"	 rd	%%asr24, %0\n"
	"	.skip	4 * (%4 - 2)\n"
	"1:\n"
	/* End of patch section */
	"	.previous\n"
	: "=&r" (tick), "=&r" (पंचांगp1), "=&r" (पंचांगp2)
	: "i" (ASI_PHYS_BYPASS_EC_E), "i" (GET_TICK_NINSTR));

	वापस tick;
पूर्ण

#पूर्ण_अगर /* _SPARC64_TIMER_H */
