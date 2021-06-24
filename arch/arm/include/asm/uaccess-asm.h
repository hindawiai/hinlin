<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित __ASM_UACCESS_ASM_H__
#घोषणा __ASM_UACCESS_ASM_H__

#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/करोमुख्य.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/thपढ़ो_info.h>

	.macro	csdb
#अगर_घोषित CONFIG_THUMB2_KERNEL
	.inst.w	0xf3af8014
#अन्यथा
	.inst	0xe320f014
#पूर्ण_अगर
	.endm

	.macro check_uaccess, addr:req, size:req, limit:req, पंचांगp:req, bad:req
#अगर_अघोषित CONFIG_CPU_USE_DOMAINS
	adds	\टmp, \चddr, #\size - 1
	sbcscc	\टmp, \टmp, \limit
	bcs	\मad
#अगर_घोषित CONFIG_CPU_SPECTRE
	movcs	\चddr, #0
	csdb
#पूर्ण_अगर
#पूर्ण_अगर
	.endm

	.macro uaccess_mask_range_ptr, addr:req, size:req, limit:req, पंचांगp:req
#अगर_घोषित CONFIG_CPU_SPECTRE
	sub	\टmp, \limit, #1
	subs	\टmp, \टmp, \चddr	@ पंचांगp = limit - 1 - addr
	addhs	\टmp, \टmp, #1		@ अगर (पंचांगp >= 0) अणु
	subshs	\टmp, \टmp, \size	@ पंचांगp = limit - (addr + size) पूर्ण
	movlo	\चddr, #0		@ अगर (पंचांगp < 0) addr = शून्य
	csdb
#पूर्ण_अगर
	.endm

	.macro	uaccess_disable, पंचांगp, isb=1
#अगर_घोषित CONFIG_CPU_SW_DOMAIN_PAN
	/*
	 * Whenever we re-enter userspace, the करोमुख्यs should always be
	 * set appropriately.
	 */
	mov	\टmp, #DACR_UACCESS_DISABLE
	mcr	p15, 0, \टmp, c3, c0, 0		@ Set करोमुख्य रेजिस्टर
	.अगर	\isb
	instr_sync
	.endअगर
#पूर्ण_अगर
	.endm

	.macro	uaccess_enable, पंचांगp, isb=1
#अगर_घोषित CONFIG_CPU_SW_DOMAIN_PAN
	/*
	 * Whenever we re-enter userspace, the करोमुख्यs should always be
	 * set appropriately.
	 */
	mov	\टmp, #DACR_UACCESS_ENABLE
	mcr	p15, 0, \टmp, c3, c0, 0
	.अगर	\isb
	instr_sync
	.endअगर
#पूर्ण_अगर
	.endm

#अगर defined(CONFIG_CPU_SW_DOMAIN_PAN) || defined(CONFIG_CPU_USE_DOMAINS)
#घोषणा DACR(x...)	x
#अन्यथा
#घोषणा DACR(x...)
#पूर्ण_अगर

	/*
	 * Save the address limit on entry to a privileged exception.
	 *
	 * If we are using the DACR क्रम kernel access by the user accessors
	 * (CONFIG_CPU_USE_DOMAINS=y), always reset the DACR kernel करोमुख्य
	 * back to client mode, whether or not \disable is set.
	 *
	 * If we are using SW PAN, set the DACR user करोमुख्य to no access
	 * अगर \disable is set.
	 */
	.macro	uaccess_entry, tsk, पंचांगp0, पंचांगp1, पंचांगp2, disable
	ldr	\टmp1, [\टsk, #TI_ADDR_LIMIT]
	ldr	\टmp2, =TASK_SIZE
	str	\टmp2, [\टsk, #TI_ADDR_LIMIT]
 DACR(	mrc	p15, 0, \टmp0, c3, c0, 0)
 DACR(	str	\टmp0, [sp, #SVC_DACR])
	str	\टmp1, [sp, #SVC_ADDR_LIMIT]
	.अगर \disable && IS_ENABLED(CONFIG_CPU_SW_DOMAIN_PAN)
	/* kernel=client, user=no access */
	mov	\टmp2, #DACR_UACCESS_DISABLE
	mcr	p15, 0, \टmp2, c3, c0, 0
	instr_sync
	.अन्यथाअगर IS_ENABLED(CONFIG_CPU_USE_DOMAINS)
	/* kernel=client */
	bic	\टmp2, \टmp0, #करोमुख्य_mask(DOMAIN_KERNEL)
	orr	\टmp2, \टmp2, #करोमुख्य_val(DOMAIN_KERNEL, DOMAIN_CLIENT)
	mcr	p15, 0, \टmp2, c3, c0, 0
	instr_sync
	.endअगर
	.endm

	/* Restore the user access state previously saved by uaccess_entry */
	.macro	uaccess_निकास, tsk, पंचांगp0, पंचांगp1
	ldr	\टmp1, [sp, #SVC_ADDR_LIMIT]
 DACR(	ldr	\टmp0, [sp, #SVC_DACR])
	str	\टmp1, [\टsk, #TI_ADDR_LIMIT]
 DACR(	mcr	p15, 0, \टmp0, c3, c0, 0)
	.endm

#अघोषित DACR

#पूर्ण_अगर /* __ASM_UACCESS_ASM_H__ */
