<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2014 Imagination Technologies Ltd.
 *
 */

#अगर_अघोषित __ASM_ASM_EVA_H
#घोषणा __ASM_ASM_EVA_H

#अगर_अघोषित __ASSEMBLY__

/* Kernel variants */

#घोषणा kernel_cache(op, base)		"cache " op ", " base "\n"
#घोषणा kernel_pref(hपूर्णांक, base)		"pref " hपूर्णांक ", " base "\n"
#घोषणा kernel_ll(reg, addr)		"ll " reg ", " addr "\n"
#घोषणा kernel_sc(reg, addr)		"sc " reg ", " addr "\n"
#घोषणा kernel_lw(reg, addr)		"lw " reg ", " addr "\n"
#घोषणा kernel_lwl(reg, addr)		"lwl " reg ", " addr "\n"
#घोषणा kernel_lwr(reg, addr)		"lwr " reg ", " addr "\n"
#घोषणा kernel_lh(reg, addr)		"lh " reg ", " addr "\n"
#घोषणा kernel_lb(reg, addr)		"lb " reg ", " addr "\n"
#घोषणा kernel_lbu(reg, addr)		"lbu " reg ", " addr "\n"
#घोषणा kernel_sw(reg, addr)		"sw " reg ", " addr "\n"
#घोषणा kernel_swl(reg, addr)		"swl " reg ", " addr "\n"
#घोषणा kernel_swr(reg, addr)		"swr " reg ", " addr "\n"
#घोषणा kernel_sh(reg, addr)		"sh " reg ", " addr "\n"
#घोषणा kernel_sb(reg, addr)		"sb " reg ", " addr "\n"

#अगर_घोषित CONFIG_32BIT
/*
 * No 'sd' or 'ld' inकाष्ठाions in 32-bit but the code will
 * करो the correct thing
 */
#घोषणा kernel_sd(reg, addr)		user_sw(reg, addr)
#घोषणा kernel_ld(reg, addr)		user_lw(reg, addr)
#अन्यथा
#घोषणा kernel_sd(reg, addr)		"sd " reg", " addr "\n"
#घोषणा kernel_ld(reg, addr)		"ld " reg", " addr "\n"
#पूर्ण_अगर /* CONFIG_32BIT */

#अगर_घोषित CONFIG_EVA

#घोषणा __BUILD_EVA_INSN(insn, reg, addr)				\
				"	.set	push\n"			\
				"	.set	mips0\n"		\
				"	.set	eva\n"			\
				"	"insn" "reg", "addr "\n"	\
				"	.set	pop\n"

#घोषणा user_cache(op, base)		__BUILD_EVA_INSN("cachee", op, base)
#घोषणा user_pref(hपूर्णांक, base)		__BUILD_EVA_INSN("prefe", hपूर्णांक, base)
#घोषणा user_ll(reg, addr)		__BUILD_EVA_INSN("lle", reg, addr)
#घोषणा user_sc(reg, addr)		__BUILD_EVA_INSN("sce", reg, addr)
#घोषणा user_lw(reg, addr)		__BUILD_EVA_INSN("lwe", reg, addr)
#घोषणा user_lwl(reg, addr)		__BUILD_EVA_INSN("lwle", reg, addr)
#घोषणा user_lwr(reg, addr)		__BUILD_EVA_INSN("lwre", reg, addr)
#घोषणा user_lh(reg, addr)		__BUILD_EVA_INSN("lhe", reg, addr)
#घोषणा user_lb(reg, addr)		__BUILD_EVA_INSN("lbe", reg, addr)
#घोषणा user_lbu(reg, addr)		__BUILD_EVA_INSN("lbue", reg, addr)
/* No 64-bit EVA inकाष्ठाion क्रम loading द्विगुन words */
#घोषणा user_ld(reg, addr)		user_lw(reg, addr)
#घोषणा user_sw(reg, addr)		__BUILD_EVA_INSN("swe", reg, addr)
#घोषणा user_swl(reg, addr)		__BUILD_EVA_INSN("swle", reg, addr)
#घोषणा user_swr(reg, addr)		__BUILD_EVA_INSN("swre", reg, addr)
#घोषणा user_sh(reg, addr)		__BUILD_EVA_INSN("she", reg, addr)
#घोषणा user_sb(reg, addr)		__BUILD_EVA_INSN("sbe", reg, addr)
/* No 64-bit EVA inकाष्ठाion क्रम storing द्विगुन words */
#घोषणा user_sd(reg, addr)		user_sw(reg, addr)

#अन्यथा

#घोषणा user_cache(op, base)		kernel_cache(op, base)
#घोषणा user_pref(hपूर्णांक, base)		kernel_pref(hपूर्णांक, base)
#घोषणा user_ll(reg, addr)		kernel_ll(reg, addr)
#घोषणा user_sc(reg, addr)		kernel_sc(reg, addr)
#घोषणा user_lw(reg, addr)		kernel_lw(reg, addr)
#घोषणा user_lwl(reg, addr)		kernel_lwl(reg, addr)
#घोषणा user_lwr(reg, addr)		kernel_lwr(reg, addr)
#घोषणा user_lh(reg, addr)		kernel_lh(reg, addr)
#घोषणा user_lb(reg, addr)		kernel_lb(reg, addr)
#घोषणा user_lbu(reg, addr)		kernel_lbu(reg, addr)
#घोषणा user_sw(reg, addr)		kernel_sw(reg, addr)
#घोषणा user_swl(reg, addr)		kernel_swl(reg, addr)
#घोषणा user_swr(reg, addr)		kernel_swr(reg, addr)
#घोषणा user_sh(reg, addr)		kernel_sh(reg, addr)
#घोषणा user_sb(reg, addr)		kernel_sb(reg, addr)

#अगर_घोषित CONFIG_32BIT
#घोषणा user_sd(reg, addr)		kernel_sw(reg, addr)
#घोषणा user_ld(reg, addr)		kernel_lw(reg, addr)
#अन्यथा
#घोषणा user_sd(reg, addr)		kernel_sd(reg, addr)
#घोषणा user_ld(reg, addr)		kernel_ld(reg, addr)
#पूर्ण_अगर /* CONFIG_32BIT */

#पूर्ण_अगर /* CONFIG_EVA */

#अन्यथा /* __ASSEMBLY__ */

#घोषणा kernel_cache(op, base)		cache op, base
#घोषणा kernel_pref(hपूर्णांक, base)		pref hपूर्णांक, base
#घोषणा kernel_ll(reg, addr)		ll reg, addr
#घोषणा kernel_sc(reg, addr)		sc reg, addr
#घोषणा kernel_lw(reg, addr)		lw reg, addr
#घोषणा kernel_lwl(reg, addr)		lwl reg, addr
#घोषणा kernel_lwr(reg, addr)		lwr reg, addr
#घोषणा kernel_lh(reg, addr)		lh reg, addr
#घोषणा kernel_lb(reg, addr)		lb reg, addr
#घोषणा kernel_lbu(reg, addr)		lbu reg, addr
#घोषणा kernel_sw(reg, addr)		sw reg, addr
#घोषणा kernel_swl(reg, addr)		swl reg, addr
#घोषणा kernel_swr(reg, addr)		swr reg, addr
#घोषणा kernel_sh(reg, addr)		sh reg, addr
#घोषणा kernel_sb(reg, addr)		sb reg, addr

#अगर_घोषित CONFIG_32BIT
/*
 * No 'sd' or 'ld' inकाष्ठाions in 32-bit but the code will
 * करो the correct thing
 */
#घोषणा kernel_sd(reg, addr)		user_sw(reg, addr)
#घोषणा kernel_ld(reg, addr)		user_lw(reg, addr)
#अन्यथा
#घोषणा kernel_sd(reg, addr)		sd reg, addr
#घोषणा kernel_ld(reg, addr)		ld reg, addr
#पूर्ण_अगर /* CONFIG_32BIT */

#अगर_घोषित CONFIG_EVA

#घोषणा __BUILD_EVA_INSN(insn, reg, addr)			\
				.set	push;			\
				.set	mips0;			\
				.set	eva;			\
				insn reg, addr;			\
				.set	pop;

#घोषणा user_cache(op, base)		__BUILD_EVA_INSN(cachee, op, base)
#घोषणा user_pref(hपूर्णांक, base)		__BUILD_EVA_INSN(prefe, hपूर्णांक, base)
#घोषणा user_ll(reg, addr)		__BUILD_EVA_INSN(lle, reg, addr)
#घोषणा user_sc(reg, addr)		__BUILD_EVA_INSN(sce, reg, addr)
#घोषणा user_lw(reg, addr)		__BUILD_EVA_INSN(lwe, reg, addr)
#घोषणा user_lwl(reg, addr)		__BUILD_EVA_INSN(lwle, reg, addr)
#घोषणा user_lwr(reg, addr)		__BUILD_EVA_INSN(lwre, reg, addr)
#घोषणा user_lh(reg, addr)		__BUILD_EVA_INSN(lhe, reg, addr)
#घोषणा user_lb(reg, addr)		__BUILD_EVA_INSN(lbe, reg, addr)
#घोषणा user_lbu(reg, addr)		__BUILD_EVA_INSN(lbue, reg, addr)
/* No 64-bit EVA inकाष्ठाion क्रम loading द्विगुन words */
#घोषणा user_ld(reg, addr)		user_lw(reg, addr)
#घोषणा user_sw(reg, addr)		__BUILD_EVA_INSN(swe, reg, addr)
#घोषणा user_swl(reg, addr)		__BUILD_EVA_INSN(swle, reg, addr)
#घोषणा user_swr(reg, addr)		__BUILD_EVA_INSN(swre, reg, addr)
#घोषणा user_sh(reg, addr)		__BUILD_EVA_INSN(she, reg, addr)
#घोषणा user_sb(reg, addr)		__BUILD_EVA_INSN(sbe, reg, addr)
/* No 64-bit EVA inकाष्ठाion क्रम loading द्विगुन words */
#घोषणा user_sd(reg, addr)		user_sw(reg, addr)
#अन्यथा

#घोषणा user_cache(op, base)		kernel_cache(op, base)
#घोषणा user_pref(hपूर्णांक, base)		kernel_pref(hपूर्णांक, base)
#घोषणा user_ll(reg, addr)		kernel_ll(reg, addr)
#घोषणा user_sc(reg, addr)		kernel_sc(reg, addr)
#घोषणा user_lw(reg, addr)		kernel_lw(reg, addr)
#घोषणा user_lwl(reg, addr)		kernel_lwl(reg, addr)
#घोषणा user_lwr(reg, addr)		kernel_lwr(reg, addr)
#घोषणा user_lh(reg, addr)		kernel_lh(reg, addr)
#घोषणा user_lb(reg, addr)		kernel_lb(reg, addr)
#घोषणा user_lbu(reg, addr)		kernel_lbu(reg, addr)
#घोषणा user_sw(reg, addr)		kernel_sw(reg, addr)
#घोषणा user_swl(reg, addr)		kernel_swl(reg, addr)
#घोषणा user_swr(reg, addr)		kernel_swr(reg, addr)
#घोषणा user_sh(reg, addr)		kernel_sh(reg, addr)
#घोषणा user_sb(reg, addr)		kernel_sb(reg, addr)

#अगर_घोषित CONFIG_32BIT
#घोषणा user_sd(reg, addr)		kernel_sw(reg, addr)
#घोषणा user_ld(reg, addr)		kernel_lw(reg, addr)
#अन्यथा
#घोषणा user_sd(reg, addr)		kernel_sd(reg, addr)
#घोषणा user_ld(reg, addr)		kernel_ld(reg, addr)
#पूर्ण_अगर /* CONFIG_32BIT */

#पूर्ण_अगर /* CONFIG_EVA */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_ASM_EVA_H */
