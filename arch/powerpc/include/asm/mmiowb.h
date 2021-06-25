<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_MMIOWB_H
#घोषणा _ASM_POWERPC_MMIOWB_H

#अगर_घोषित CONFIG_MMIOWB

#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/paca.h>

#घोषणा arch_mmiowb_state()	(&local_paca->mmiowb_state)
#घोषणा mmiowb()		mb()

#पूर्ण_अगर /* CONFIG_MMIOWB */

#समावेश <यंत्र-generic/mmiowb.h>

#पूर्ण_अगर	/* _ASM_POWERPC_MMIOWB_H */
