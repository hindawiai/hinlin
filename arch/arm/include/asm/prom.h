<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/prom.h
 *
 *  Copyright (C) 2009 Canonical Ltd. <jeremy.kerr@canonical.com>
 */
#अगर_अघोषित __ASMARM_PROM_H
#घोषणा __ASMARM_PROM_H

#अगर_घोषित CONFIG_OF

बाह्य स्थिर काष्ठा machine_desc *setup_machine_fdt(व्योम *dt_virt);
बाह्य व्योम __init arm_dt_init_cpu_maps(व्योम);

#अन्यथा /* CONFIG_OF */

अटल अंतरभूत स्थिर काष्ठा machine_desc *setup_machine_fdt(व्योम *dt_virt)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम arm_dt_init_cpu_maps(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_OF */
#पूर्ण_अगर /* ASMARM_PROM_H */
