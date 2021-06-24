<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2003 by Ralf Baechle
 * Copyright (C) 1996 by Paul M. Antoine
 * Copyright (C) 1999 Silicon Graphics
 * Copyright (C) 2000 MIPS Technologies, Inc.
 */
#समावेश <यंत्र/irqflags.h>
#समावेश <यंत्र/hazards.h>
#समावेश <linux/compiler.h>
#समावेश <linux/preempt.h>
#समावेश <linux/export.h>
#समावेश <linux/stringअगरy.h>

#अगर !defined(CONFIG_CPU_HAS_DIEI)

/*
 * For cli() we have to insert nops to make sure that the new value
 * has actually arrived in the status रेजिस्टर beक्रमe the end of this
 * macro.
 * R4000/R4400 need three nops, the R4600 two nops and the R10000 needs
 * no nops at all.
 */
/*
 * For TX49, operating only IE bit is not enough.
 *
 * If mfc0 $12 follows store and the mfc0 is last inकाष्ठाion of a
 * page and fetching the next inकाष्ठाion causes TLB miss, the result
 * of the mfc0 might wrongly contain EXL bit.
 *
 * ERT-TX49H2-027, ERT-TX49H3-012, ERT-TX49HL3-006, ERT-TX49H4-008
 *
 * Workaround: mask EXL bit of the result or place a nop beक्रमe mfc0.
 */
notrace व्योम arch_local_irq_disable(व्योम)
अणु
	preempt_disable_notrace();

	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	noat						\n"
	"	mfc0	$1,$12						\n"
	"	ori	$1,0x1f						\n"
	"	xori	$1,0x1f						\n"
	"	.set	noreorder					\n"
	"	mtc0	$1,$12						\n"
	"	" __stringअगरy(__irq_disable_hazard) "			\n"
	"	.set	pop						\n"
	: /* no outमाला_दो */
	: /* no inमाला_दो */
	: "memory");

	preempt_enable_notrace();
पूर्ण
EXPORT_SYMBOL(arch_local_irq_disable);

notrace अचिन्हित दीर्घ arch_local_irq_save(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	preempt_disable_notrace();

	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	reorder						\n"
	"	.set	noat						\n"
	"	mfc0	%[flags], $12					\n"
	"	ori	$1, %[flags], 0x1f				\n"
	"	xori	$1, 0x1f					\n"
	"	.set	noreorder					\n"
	"	mtc0	$1, $12						\n"
	"	" __stringअगरy(__irq_disable_hazard) "			\n"
	"	.set	pop						\n"
	: [flags] "=r" (flags)
	: /* no inमाला_दो */
	: "memory");

	preempt_enable_notrace();

	वापस flags;
पूर्ण
EXPORT_SYMBOL(arch_local_irq_save);

notrace व्योम arch_local_irq_restore(अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ __पंचांगp1;

	preempt_disable_notrace();

	__यंत्र__ __अस्थिर__(
	"	.set	push						\n"
	"	.set	noreorder					\n"
	"	.set	noat						\n"
	"	mfc0	$1, $12						\n"
	"	andi	%[flags], 1					\n"
	"	ori	$1, 0x1f					\n"
	"	xori	$1, 0x1f					\n"
	"	or	%[flags], $1					\n"
	"	mtc0	%[flags], $12					\n"
	"	" __stringअगरy(__irq_disable_hazard) "			\n"
	"	.set	pop						\n"
	: [flags] "=r" (__पंचांगp1)
	: "0" (flags)
	: "memory");

	preempt_enable_notrace();
पूर्ण
EXPORT_SYMBOL(arch_local_irq_restore);

#पूर्ण_अगर /* !CONFIG_CPU_HAS_DIEI */
