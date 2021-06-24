<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2013 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_SMP_CPS_H__
#घोषणा __MIPS_ASM_SMP_CPS_H__

#अगर_अघोषित __ASSEMBLY__

काष्ठा vpe_boot_config अणु
	अचिन्हित दीर्घ pc;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ gp;
पूर्ण;

काष्ठा core_boot_config अणु
	atomic_t vpe_mask;
	काष्ठा vpe_boot_config *vpe_config;
पूर्ण;

बाह्य काष्ठा core_boot_config *mips_cps_core_bootcfg;

बाह्य व्योम mips_cps_core_entry(व्योम);
बाह्य व्योम mips_cps_core_init(व्योम);

बाह्य व्योम mips_cps_boot_vpes(काष्ठा core_boot_config *cfg, अचिन्हित vpe);

बाह्य व्योम mips_cps_pm_save(व्योम);
बाह्य व्योम mips_cps_pm_restore(व्योम);

#अगर_घोषित CONFIG_MIPS_CPS

बाह्य bool mips_cps_smp_in_use(व्योम);

#अन्यथा /* !CONFIG_MIPS_CPS */

अटल अंतरभूत bool mips_cps_smp_in_use(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर /* !CONFIG_MIPS_CPS */

#अन्यथा /* __ASSEMBLY__ */

.बाह्य mips_cps_bootcfg;

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __MIPS_ASM_SMP_CPS_H__ */
