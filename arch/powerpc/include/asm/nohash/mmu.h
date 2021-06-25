<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_MMU_H_
#घोषणा _ASM_POWERPC_NOHASH_MMU_H_

#अगर defined(CONFIG_40x)
/* 40x-style software loaded TLB */
#समावेश <यंत्र/nohash/32/mmu-40x.h>
#या_अगर defined(CONFIG_44x)
/* 44x-style software loaded TLB */
#समावेश <यंत्र/nohash/32/mmu-44x.h>
#या_अगर defined(CONFIG_PPC_BOOK3E_MMU)
/* Freescale Book-E software loaded TLB or Book-3e (ISA 2.06+) MMU */
#समावेश <यंत्र/nohash/mmu-book3e.h>
#या_अगर defined (CONFIG_PPC_8xx)
/* Motorola/Freescale 8xx software loaded TLB */
#समावेश <यंत्र/nohash/32/mmu-8xx.h>
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_NOHASH_MMU_H_ */
