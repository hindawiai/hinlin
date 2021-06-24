<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This is included by init/मुख्य.c to check क्रम architecture-dependent bugs.
 *
 * Copyright (C) 2007  Maciej W. Rozycki
 *
 * Needs:
 *	व्योम check_bugs(व्योम);
 */
#अगर_अघोषित _ASM_BUGS_H
#घोषणा _ASM_BUGS_H

#समावेश <linux/bug.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>

बाह्य पूर्णांक daddiu_bug;

बाह्य व्योम check_bugs64_early(व्योम);

बाह्य व्योम check_bugs32(व्योम);
बाह्य व्योम check_bugs64(व्योम);

अटल अंतरभूत व्योम check_bugs_early(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_CPU_R4X00_BUGS64))
		check_bugs64_early();
पूर्ण

अटल अंतरभूत व्योम check_bugs(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	cpu_data[cpu].udelay_val = loops_per_jअगरfy;
	check_bugs32();

	अगर (IS_ENABLED(CONFIG_CPU_R4X00_BUGS64))
		check_bugs64();
पूर्ण

अटल अंतरभूत पूर्णांक r4k_daddiu_bug(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_CPU_R4X00_BUGS64))
		वापस 0;

	WARN_ON(daddiu_bug < 0);
	वापस daddiu_bug != 0;
पूर्ण

#पूर्ण_अगर /* _ASM_BUGS_H */
