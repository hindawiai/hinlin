<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions and declarations क्रम MIPS MT support that are common between
 * the VSMP, and AP/SP kernel models.
 */
#अगर_अघोषित __ASM_MIPS_MT_H
#घोषणा __ASM_MIPS_MT_H

#समावेश <linux/cpumask.h>

/*
 * How many VPEs and TCs is Linux allowed to use?  0 means no limit.
 */
बाह्य पूर्णांक tclimit;
बाह्य पूर्णांक vpelimit;

बाह्य cpumask_t mt_fpu_cpumask;
बाह्य अचिन्हित दीर्घ mt_fpemul_threshold;

बाह्य व्योम mips_mt_regdump(अचिन्हित दीर्घ previous_mvpcontrol_value);

#अगर_घोषित CONFIG_MIPS_MT
बाह्य व्योम mips_mt_set_cpuoptions(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mips_mt_set_cpuoptions(व्योम) अणु पूर्ण
#पूर्ण_अगर

काष्ठा class;
बाह्य काष्ठा class *mt_class;

#पूर्ण_अगर /* __ASM_MIPS_MT_H */
