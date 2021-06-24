<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ASM_POWERPC_VDSO_PROCESSOR_H
#घोषणा _ASM_POWERPC_VDSO_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__

/* Macros क्रम adjusting thपढ़ो priority (hardware multi-thपढ़ोing) */
#घोषणा HMT_very_low()		यंत्र अस्थिर("or 31, 31, 31	# very low priority")
#घोषणा HMT_low()		यंत्र अस्थिर("or 1, 1, 1	# low priority")
#घोषणा HMT_medium_low()	यंत्र अस्थिर("or 6, 6, 6	# medium low priority")
#घोषणा HMT_medium()		यंत्र अस्थिर("or 2, 2, 2	# medium priority")
#घोषणा HMT_medium_high()	यंत्र अस्थिर("or 5, 5, 5	# medium high priority")
#घोषणा HMT_high()		यंत्र अस्थिर("or 3, 3, 3	# high priority")

#अगर_घोषित CONFIG_PPC64
#घोषणा cpu_relax()	करो अणु HMT_low(); HMT_medium(); barrier(); पूर्ण जबतक (0)
#अन्यथा
#घोषणा cpu_relax()	barrier()
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_VDSO_PROCESSOR_H */
