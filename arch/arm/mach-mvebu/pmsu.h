<शैली गुरु>
/*
 * Power Management Service Unit (PMSU) support क्रम Armada 370/XP platक्रमms.
 *
 * Copyright (C) 2012 Marvell
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __MACH_MVEBU_PMSU_H
#घोषणा __MACH_MVEBU_PMSU_H

पूर्णांक armada_xp_boot_cpu(अचिन्हित पूर्णांक cpu_id, व्योम *phys_addr);
पूर्णांक mvebu_setup_boot_addr_wa(अचिन्हित पूर्णांक crypto_eng_target,
                             अचिन्हित पूर्णांक crypto_eng_attribute,
                             phys_addr_t resume_addr_reg);

व्योम mvebu_v7_pmsu_idle_निकास(व्योम);
व्योम armada_370_xp_cpu_resume(व्योम);

पूर्णांक armada_370_xp_pmsu_idle_enter(अचिन्हित दीर्घ deepidle);
पूर्णांक armada_38x_करो_cpu_suspend(अचिन्हित दीर्घ deepidle);
#पूर्ण_अगर	/* __MACH_370_XP_PMSU_H */
