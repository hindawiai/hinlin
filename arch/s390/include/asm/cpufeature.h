<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Module पूर्णांकerface क्रम CPU features
 *
 * Copyright IBM Corp. 2015
 * Author(s): Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */

#अगर_अघोषित __ASM_S390_CPUFEATURE_H
#घोषणा __ASM_S390_CPUFEATURE_H

#समावेश <यंत्र/elf.h>

/* Hardware features on Linux on z Systems are indicated by facility bits that
 * are mapped to the so-called machine flags.  Particular machine flags are
 * then used to define ELF hardware capabilities; most notably hardware flags
 * that are essential क्रम user space / glibc.
 *
 * Restrict the set of exposed CPU features to ELF hardware capabilities क्रम
 * now.  Additional machine flags can be indicated by values larger than
 * MAX_ELF_HWCAP_FEATURES.
 */
#घोषणा MAX_ELF_HWCAP_FEATURES	(8 * माप(elf_hwcap))
#घोषणा MAX_CPU_FEATURES	MAX_ELF_HWCAP_FEATURES

#घोषणा cpu_feature(feat)	ilog2(HWCAP_S390_ ## feat)

पूर्णांक cpu_have_feature(अचिन्हित पूर्णांक nr);

#पूर्ण_अगर /* __ASM_S390_CPUFEATURE_H */
