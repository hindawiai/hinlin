<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2009 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
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
#समावेश <यंत्र/octeon/octeon.h>

अटल पूर्णांक cnmips_cu2_call(काष्ठा notअगरier_block *nfb, अचिन्हित दीर्घ action,
	व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक status;

	चयन (action) अणु
	हाल CU2_EXCEPTION:
		prefetch(&current->thपढ़ो.cp2);
		local_irq_save(flags);
		KSTK_STATUS(current) |= ST0_CU2;
		status = पढ़ो_c0_status();
		ग_लिखो_c0_status(status | ST0_CU2);
		octeon_cop2_restore(&(current->thपढ़ो.cp2));
		ग_लिखो_c0_status(status & ~ST0_CU2);
		local_irq_restore(flags);

		वापस NOTIFY_BAD;	/* Don't call शेष notअगरier */
	पूर्ण

	वापस NOTIFY_OK;		/* Let शेष notअगरier send संकेतs */
पूर्ण

अटल पूर्णांक __init cnmips_cu2_setup(व्योम)
अणु
	वापस cu2_notअगरier(cnmips_cu2_call, 0);
पूर्ण
early_initcall(cnmips_cu2_setup);
