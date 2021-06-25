<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SH_UNALIGNED_H
#घोषणा _ASM_SH_UNALIGNED_H

#अगर_घोषित CONFIG_CPU_SH4A
/* SH-4A can handle unaligned loads in a relatively neutered fashion. */
#समावेश <यंत्र/unaligned-sh4a.h>
#अन्यथा
/* Otherwise, SH can't handle unaligned accesses. */
#समावेश <यंत्र-generic/unaligned.h>
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SH_UNALIGNED_H */
