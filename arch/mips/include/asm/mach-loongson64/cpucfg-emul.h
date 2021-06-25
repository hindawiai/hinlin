<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MACH_LOONGSON64_CPUCFG_EMUL_H_
#घोषणा _ASM_MACH_LOONGSON64_CPUCFG_EMUL_H_

#समावेश <यंत्र/cpu-info.h>

#अगर_घोषित CONFIG_CPU_LOONGSON3_CPUCFG_EMULATION

#समावेश <loongson_regs.h>

#घोषणा LOONGSON_FPREV_MASK 0x7

व्योम loongson3_cpucfg_synthesize_data(काष्ठा cpuinfo_mips *c);

अटल अंतरभूत bool loongson3_cpucfg_emulation_enabled(काष्ठा cpuinfo_mips *c)
अणु
	/* All supported cores have non-zero LOONGSON_CFG1 data. */
	वापस c->loongson3_cpucfg_data[0] != 0;
पूर्ण

अटल अंतरभूत u32 loongson3_cpucfg_पढ़ो_synthesized(काष्ठा cpuinfo_mips *c,
	__u64 sel)
अणु
	चयन (sel) अणु
	हाल LOONGSON_CFG0:
		वापस c->processor_id;
	हाल LOONGSON_CFG1:
	हाल LOONGSON_CFG2:
	हाल LOONGSON_CFG3:
		वापस c->loongson3_cpucfg_data[sel - 1];
	हाल LOONGSON_CFG4:
	हाल LOONGSON_CFG5:
		/* CPUCFG selects 4 and 5 are related to the input घड़ी
		 * संकेत.
		 *
		 * Unimplemented क्रम now.
		 */
		वापस 0;
	हाल LOONGSON_CFG6:
		/* CPUCFG select 6 is क्रम the unकरोcumented Safe Extension. */
		वापस 0;
	हाल LOONGSON_CFG7:
		/* CPUCFG select 7 is क्रम the भवization extension.
		 * We करोn't know अगर the two currently known features are
		 * supported on older cores according to the खुला
		 * करोcumentation, so leave this at zero.
		 */
		वापस 0;
	पूर्ण

	/*
	 * Return 0 क्रम unrecognized CPUCFG selects, which is real hardware
	 * behavior observed on Loongson 3A R4.
	 */
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम loongson3_cpucfg_synthesize_data(काष्ठा cpuinfo_mips *c)
अणु
पूर्ण

अटल अंतरभूत bool loongson3_cpucfg_emulation_enabled(काष्ठा cpuinfo_mips *c)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u32 loongson3_cpucfg_पढ़ो_synthesized(काष्ठा cpuinfo_mips *c,
	__u64 sel)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_MACH_LOONGSON64_CPUCFG_EMUL_H_ */
