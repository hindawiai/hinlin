<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_KEXEC_H_
#घोषणा _ASM_POWERPC_BOOK3S_64_KEXEC_H_

#समावेश <यंत्र/plpar_wrappers.h>

#घोषणा reset_sprs reset_sprs
अटल अंतरभूत व्योम reset_sprs(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_ARCH_206)) अणु
		mtspr(SPRN_AMR, 0);
		mtspr(SPRN_UAMOR, 0);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		mtspr(SPRN_IAMR, 0);
		अगर (cpu_has_feature(CPU_FTR_HVMODE))
			mtspr(SPRN_CIABR, 0);
		अन्यथा
			plpar_set_ciabr(0);
	पूर्ण

	/*  Do we need isync()? We are going via a kexec reset */
	isync();
पूर्ण

#पूर्ण_अगर
