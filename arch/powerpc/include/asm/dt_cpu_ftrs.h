<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_POWERPC_DT_CPU_FTRS_H
#घोषणा __ASM_POWERPC_DT_CPU_FTRS_H

/*
 *  Copyright 2017, IBM Corporation
 *  cpufeatures is the new way to discover CPU features with /cpus/features
 *  devicetree. This supersedes PVR based discovery ("cputable"), and older
 *  device tree feature advertisement.
 */

#समावेश <linux/types.h>
#समावेश <uapi/यंत्र/cputable.h>

#अगर_घोषित CONFIG_PPC_DT_CPU_FTRS
bool dt_cpu_ftrs_init(व्योम *fdt);
व्योम dt_cpu_ftrs_scan(व्योम);
bool dt_cpu_ftrs_in_use(व्योम);
#अन्यथा
अटल अंतरभूत bool dt_cpu_ftrs_init(व्योम *fdt) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम dt_cpu_ftrs_scan(व्योम) अणु पूर्ण
अटल अंतरभूत bool dt_cpu_ftrs_in_use(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_POWERPC_DT_CPU_FTRS_H */
