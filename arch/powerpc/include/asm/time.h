<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Common समय prototypes and such क्रम all ppc machines.
 *
 * Written by Cort Dougan (cort@cs.nmt.edu) to merge
 * Paul Mackerras' version and mine क्रम PReP and Pmac.
 */

#अगर_अघोषित __POWERPC_TIME_H
#घोषणा __POWERPC_TIME_H

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#समावेश <linux/percpu.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/vdso/समयbase.h>

/* समय.c */
बाह्य अचिन्हित दीर्घ tb_ticks_per_jअगरfy;
बाह्य अचिन्हित दीर्घ tb_ticks_per_usec;
बाह्य अचिन्हित दीर्घ tb_ticks_per_sec;
बाह्य काष्ठा घड़ी_event_device decrementer_घड़ीevent;


बाह्य व्योम generic_calibrate_decr(व्योम);

/* Some sane शेषs: 125 MHz समयbase, 1GHz processor */
बाह्य अचिन्हित दीर्घ ppc_proc_freq;
#घोषणा DEFAULT_PROC_FREQ	(DEFAULT_TB_FREQ * 8)
बाह्य अचिन्हित दीर्घ ppc_tb_freq;
#घोषणा DEFAULT_TB_FREQ		125000000UL

बाह्य bool tb_invalid;

काष्ठा भाग_result अणु
	u64 result_high;
	u64 result_low;
पूर्ण;

अटल अंतरभूत u64 get_vtb(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस mfspr(SPRN_VTB);

	वापस 0;
पूर्ण

/* Accessor functions क्रम the decrementer रेजिस्टर.
 * The 4xx करोesn't even have a decrementer.  I tried to use the
 * generic समयr पूर्णांकerrupt code, which seems OK, with the 4xx PIT
 * in स्वतः-reload mode.  The problem is PIT stops counting when it
 * hits zero.  If it would wrap, we could use it just like a decrementer.
 */
अटल अंतरभूत u64 get_dec(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_40x))
		वापस mfspr(SPRN_PIT);

	वापस mfspr(SPRN_DEC);
पूर्ण

/*
 * Note: Book E and 4xx processors dअगरfer from other PowerPC processors
 * in when the decrementer generates its पूर्णांकerrupt: on the 1 to 0
 * transition क्रम Book E/4xx, but on the 0 to -1 transition क्रम others.
 */
अटल अंतरभूत व्योम set_dec(u64 val)
अणु
	अगर (IS_ENABLED(CONFIG_40x))
		mtspr(SPRN_PIT, (u32)val);
	अन्यथा अगर (IS_ENABLED(CONFIG_BOOKE))
		mtspr(SPRN_DEC, val);
	अन्यथा
		mtspr(SPRN_DEC, val - 1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tb_ticks_since(अचिन्हित दीर्घ tstamp)
अणु
	वापस mftb() - tstamp;
पूर्ण

#घोषणा mulhwu(x,y) \
(अणुअचिन्हित z; यंत्र ("mulhwu %0,%1,%2" : "=r" (z) : "r" (x), "r" (y)); z;पूर्ण)

#अगर_घोषित CONFIG_PPC64
#घोषणा mulhdu(x,y) \
(अणुअचिन्हित दीर्घ z; यंत्र ("mulhdu %0,%1,%2" : "=r" (z) : "r" (x), "r" (y)); z;पूर्ण)
#अन्यथा
बाह्य u64 mulhdu(u64, u64);
#पूर्ण_अगर

बाह्य व्योम भाग128_by_32(u64 भागidend_high, u64 भागidend_low,
			 अचिन्हित भागisor, काष्ठा भाग_result *dr);

बाह्य व्योम secondary_cpu_समय_init(व्योम);
बाह्य व्योम __init समय_init(व्योम);

DECLARE_PER_CPU(u64, decrementers_next_tb);

/* Convert समयbase ticks to nanoseconds */
अचिन्हित दीर्घ दीर्घ tb_to_ns(अचिन्हित दीर्घ दीर्घ tb_ticks);

व्योम समयr_broadcast_पूर्णांकerrupt(व्योम);

/* SPLPAR */
व्योम accumulate_stolen_समय(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __POWERPC_TIME_H */
