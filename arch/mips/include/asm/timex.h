<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998, 1999, 2003 by Ralf Baechle
 * Copyright (C) 2014 by Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_TIMEX_H
#घोषणा _ASM_TIMEX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/cpu-type.h>

/*
 * This is the घड़ी rate of the i8253 PIT.  A MIPS प्रणाली may not have
 * a PIT by the symbol is used all over the kernel including some APIs.
 * So keeping it defined to the number क्रम the PIT is the only sane thing
 * क्रम now.
 */
#घोषणा CLOCK_TICK_RATE 1193182

/*
 * Standard way to access the cycle counter.
 * Currently only used on SMP क्रम scheduling.
 *
 * Only the low 32 bits are available as a continuously counting entity.
 * But this only means we'll क्रमce a reschedule every 8 seconds or so,
 * which isn't an evil thing.
 *
 * We know that all SMP capable CPUs have cycle counters.
 */

प्रकार अचिन्हित पूर्णांक cycles_t;

/*
 * On R4000/R4400 beक्रमe version 5.0 an erratum exists such that अगर the
 * cycle counter is पढ़ो in the exact moment that it is matching the
 * compare रेजिस्टर, no पूर्णांकerrupt will be generated.
 *
 * There is a suggested workaround and also the erratum can't strike अगर
 * the compare पूर्णांकerrupt isn't being used as the घड़ी source device.
 * However क्रम now the implementaton of this function करोesn't get these
 * fine details right.
 */
अटल अंतरभूत पूर्णांक can_use_mips_counter(अचिन्हित पूर्णांक prid)
अणु
	पूर्णांक comp = (prid & PRID_COMP_MASK) != PRID_COMP_LEGACY;

	अगर (__builtin_स्थिरant_p(cpu_has_counter) && !cpu_has_counter)
		वापस 0;
	अन्यथा अगर (__builtin_स्थिरant_p(cpu_has_mips_r) && cpu_has_mips_r)
		वापस 1;
	अन्यथा अगर (likely(!__builtin_स्थिरant_p(cpu_has_mips_r) && comp))
		वापस 1;
	/* Make sure we करोn't peek at cpu_data[0].options in the fast path! */
	अगर (!__builtin_स्थिरant_p(cpu_has_counter))
		यंत्र अस्थिर("" : "=m" (cpu_data[0].options));
	अगर (likely(cpu_has_counter &&
		   prid >= (PRID_IMP_R4000 | PRID_REV_ENCODE_44(5, 0))))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	अगर (can_use_mips_counter(पढ़ो_c0_prid()))
		वापस पढ़ो_c0_count();
	अन्यथा
		वापस 0;	/* no usable counter */
पूर्ण

/*
 * Like get_cycles - but where c0_count is not available we desperately
 * use c0_अक्रमom in an attempt to get at least a little bit of entropy.
 *
 * R6000 and R6000A neither have a count रेजिस्टर nor a अक्रमom रेजिस्टर.
 * That leaves no entropy source in the CPU itself.
 */
अटल अंतरभूत अचिन्हित दीर्घ अक्रमom_get_entropy(व्योम)
अणु
	अचिन्हित पूर्णांक prid = पढ़ो_c0_prid();
	अचिन्हित पूर्णांक imp = prid & PRID_IMP_MASK;

	अगर (can_use_mips_counter(prid))
		वापस पढ़ो_c0_count();
	अन्यथा अगर (likely(imp != PRID_IMP_R6000 && imp != PRID_IMP_R6000A))
		वापस पढ़ो_c0_अक्रमom();
	अन्यथा
		वापस 0;	/* no usable रेजिस्टर */
पूर्ण
#घोषणा अक्रमom_get_entropy अक्रमom_get_entropy

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /*  _ASM_TIMEX_H */
