<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011 by Kevin Cernekee (cernekee@gmail.com)
 *
 * Definitions क्रम BMIPS processors
 */
#अगर_अघोषित _ASM_BMIPS_H
#घोषणा _ASM_BMIPS_H

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/hazards.h>

/* NOTE: the CBR रेजिस्टर वापसs a PA, and it can be above 0xff00_0000 */
#घोषणा BMIPS_GET_CBR()			((व्योम __iomem *)(CKSEG1 | \
					 (अचिन्हित दीर्घ) \
					 ((पढ़ो_c0_brcm_cbr() >> 18) << 18)))

#घोषणा BMIPS_RAC_CONFIG		0x00000000
#घोषणा BMIPS_RAC_ADDRESS_RANGE		0x00000004
#घोषणा BMIPS_RAC_CONFIG_1		0x00000008
#घोषणा BMIPS_L2_CONFIG			0x0000000c
#घोषणा BMIPS_LMB_CONTROL		0x0000001c
#घोषणा BMIPS_SYSTEM_BASE		0x00000020
#घोषणा BMIPS_PERF_GLOBAL_CONTROL	0x00020000
#घोषणा BMIPS_PERF_CONTROL_0		0x00020004
#घोषणा BMIPS_PERF_CONTROL_1		0x00020008
#घोषणा BMIPS_PERF_COUNTER_0		0x00020010
#घोषणा BMIPS_PERF_COUNTER_1		0x00020014
#घोषणा BMIPS_PERF_COUNTER_2		0x00020018
#घोषणा BMIPS_PERF_COUNTER_3		0x0002001c
#घोषणा BMIPS_RELO_VECTOR_CONTROL_0	0x00030000
#घोषणा BMIPS_RELO_VECTOR_CONTROL_1	0x00038000

#घोषणा BMIPS_NMI_RESET_VEC		0x80000000
#घोषणा BMIPS_WARM_RESTART_VEC		0x80000380

#घोषणा ZSCM_REG_BASE			0x97000000

#अगर !defined(__ASSEMBLY__)

#समावेश <linux/cpumask.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/smp-ops.h>

बाह्य स्थिर काष्ठा plat_smp_ops bmips43xx_smp_ops;
बाह्य स्थिर काष्ठा plat_smp_ops bmips5000_smp_ops;

अटल अंतरभूत पूर्णांक रेजिस्टर_bmips_smp_ops(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_CPU_BMIPS) && IS_ENABLED(CONFIG_SMP)
	चयन (current_cpu_type()) अणु
	हाल CPU_BMIPS32:
	हाल CPU_BMIPS3300:
		वापस रेजिस्टर_up_smp_ops();
	हाल CPU_BMIPS4350:
	हाल CPU_BMIPS4380:
		रेजिस्टर_smp_ops(&bmips43xx_smp_ops);
		अवरोध;
	हाल CPU_BMIPS5000:
		रेजिस्टर_smp_ops(&bmips5000_smp_ops);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	वापस 0;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

बाह्य अक्षर bmips_reset_nmi_vec[];
बाह्य अक्षर bmips_reset_nmi_vec_end[];
बाह्य अक्षर bmips_smp_movevec[];
बाह्य अक्षर bmips_smp_पूर्णांक_vec[];
बाह्य अक्षर bmips_smp_पूर्णांक_vec_end[];

बाह्य पूर्णांक bmips_smp_enabled;
बाह्य पूर्णांक bmips_cpu_offset;
बाह्य cpumask_t bmips_booted_mask;
बाह्य अचिन्हित दीर्घ bmips_tp1_irqs;

बाह्य व्योम bmips_ebase_setup(व्योम);
बाह्य यंत्रlinkage व्योम plat_wired_tlb_setup(व्योम);
बाह्य व्योम bmips_cpu_setup(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ bmips_पढ़ो_zscm_reg(अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित दीर्घ ret;

	barrier();
	cache_op(Index_Load_Tag_S, ZSCM_REG_BASE + offset);
	__sync();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	_ssnop();
	ret = पढ़ो_c0_ddatalo();
	_ssnop();

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम bmips_ग_लिखो_zscm_reg(अचिन्हित पूर्णांक offset, अचिन्हित दीर्घ data)
अणु
	ग_लिखो_c0_ddatalo(data);
	_ssnop();
	_ssnop();
	_ssnop();
	cache_op(Index_Store_Tag_S, ZSCM_REG_BASE + offset);
	_ssnop();
	_ssnop();
	_ssnop();
	barrier();
पूर्ण

#पूर्ण_अगर /* !defined(__ASSEMBLY__) */

#पूर्ण_अगर /* _ASM_BMIPS_H */
