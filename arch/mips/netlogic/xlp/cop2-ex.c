<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2013 Broadcom Corporation.
 *
 * based on arch/mips/cavium-octeon/cpu.c
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/capability.h>
#समावेश <linux/init.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/cop2.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/page.h>

#समावेश <यंत्र/netlogic/mips-extns.h>

/*
 * 64 bit ops are करोne in अंतरभूत assembly to support 32 bit
 * compilation
 */
व्योम nlm_cop2_save(काष्ठा nlm_cop2_state *r)
अणु
	यंत्र अस्थिर(
		".set	push\n"
		".set	noat\n"
		"dmfc2	$1, $0, 0\n"
		"sd	$1, 0(%1)\n"
		"dmfc2	$1, $0, 1\n"
		"sd	$1, 8(%1)\n"
		"dmfc2	$1, $0, 2\n"
		"sd	$1, 16(%1)\n"
		"dmfc2	$1, $0, 3\n"
		"sd	$1, 24(%1)\n"
		"dmfc2	$1, $1, 0\n"
		"sd	$1, 0(%2)\n"
		"dmfc2	$1, $1, 1\n"
		"sd	$1, 8(%2)\n"
		"dmfc2	$1, $1, 2\n"
		"sd	$1, 16(%2)\n"
		"dmfc2	$1, $1, 3\n"
		"sd	$1, 24(%2)\n"
		".set	pop\n"
		: "=m"(*r)
		: "r"(r->tx), "r"(r->rx));

	r->tx_msg_status = __पढ़ो_32bit_c2_रेजिस्टर($2, 0);
	r->rx_msg_status = __पढ़ो_32bit_c2_रेजिस्टर($3, 0) & 0x0fffffff;
पूर्ण

व्योम nlm_cop2_restore(काष्ठा nlm_cop2_state *r)
अणु
	u32 rstat;

	यंत्र अस्थिर(
		".set	push\n"
		".set	noat\n"
		"ld	$1, 0(%1)\n"
		"dmtc2	$1, $0, 0\n"
		"ld	$1, 8(%1)\n"
		"dmtc2	$1, $0, 1\n"
		"ld	$1, 16(%1)\n"
		"dmtc2	$1, $0, 2\n"
		"ld	$1, 24(%1)\n"
		"dmtc2	$1, $0, 3\n"
		"ld	$1, 0(%2)\n"
		"dmtc2	$1, $1, 0\n"
		"ld	$1, 8(%2)\n"
		"dmtc2	$1, $1, 1\n"
		"ld	$1, 16(%2)\n"
		"dmtc2	$1, $1, 2\n"
		"ld	$1, 24(%2)\n"
		"dmtc2	$1, $1, 3\n"
		".set	pop\n"
		: : "m"(*r), "r"(r->tx), "r"(r->rx));

	__ग_लिखो_32bit_c2_रेजिस्टर($2, 0, r->tx_msg_status);
	rstat = __पढ़ो_32bit_c2_रेजिस्टर($3, 0) & 0xf0000000u;
	__ग_लिखो_32bit_c2_रेजिस्टर($3, 0, r->rx_msg_status | rstat);
पूर्ण

अटल पूर्णांक nlm_cu2_call(काष्ठा notअगरier_block *nfb, अचिन्हित दीर्घ action,
	व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	चयन (action) अणु
	हाल CU2_EXCEPTION:
		अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
			अवरोध;
		local_irq_save(flags);
		KSTK_STATUS(current) |= ST0_CU2;
		status = पढ़ो_c0_status();
		ग_लिखो_c0_status(status | ST0_CU2);
		nlm_cop2_restore(&(current->thपढ़ो.cp2));
		ग_लिखो_c0_status(status & ~ST0_CU2);
		local_irq_restore(flags);
		pr_info("COP2 access enabled for pid %d (%s)\n",
					current->pid, current->comm);
		वापस NOTIFY_BAD;	/* Don't call शेष notअगरier */
	पूर्ण

	वापस NOTIFY_OK;		/* Let शेष notअगरier send संकेतs */
पूर्ण

अटल पूर्णांक __init nlm_cu2_setup(व्योम)
अणु
	वापस cu2_notअगरier(nlm_cu2_call, 0);
पूर्ण
early_initcall(nlm_cu2_setup);
