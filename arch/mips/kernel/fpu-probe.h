<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#समावेश <linux/kernel.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

बाह्य पूर्णांक mips_fpu_disabled;

पूर्णांक __cpu_has_fpu(व्योम);
व्योम cpu_set_fpu_opts(काष्ठा cpuinfo_mips *c);
व्योम cpu_set_nofpu_opts(काष्ठा cpuinfo_mips *c);

#अन्यथा /* !CONFIG_MIPS_FP_SUPPORT */

#घोषणा mips_fpu_disabled 1

अटल अंतरभूत अचिन्हित दीर्घ cpu_get_fpu_id(व्योम)
अणु
	वापस FPIR_IMP_NONE;
पूर्ण

अटल अंतरभूत पूर्णांक __cpu_has_fpu(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cpu_set_fpu_opts(काष्ठा cpuinfo_mips *c)
अणु
	/* no-op */
पूर्ण

अटल अंतरभूत व्योम cpu_set_nofpu_opts(काष्ठा cpuinfo_mips *c)
अणु
	/* no-op */
पूर्ण

#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */
