<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 ARM Ltd.
 */
#अगर_अघोषित __ASM_VDSO_PROCESSOR_H
#घोषणा __ASM_VDSO_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_CPU_LOONGSON64
/*
 * Loongson-3's SFB (Store-Fill-Buffer) may buffer ग_लिखोs indefinitely when a
 * tight पढ़ो loop is executed, because पढ़ोs take priority over ग_लिखोs & the
 * hardware (incorrectly) करोesn't ensure that ग_लिखोs will eventually occur.
 *
 * Since spin loops of any kind should have a cpu_relax() in them, क्रमce an SFB
 * flush from cpu_relax() such that any pending ग_लिखोs will become visible as
 * expected.
 */
#घोषणा cpu_relax()	smp_mb()
#अन्यथा
#घोषणा cpu_relax()	barrier()
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_PROCESSOR_H */
