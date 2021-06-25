<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2012
 * Author(s): Jan Glauber <jang@linux.vnet.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/runसमय_instr.h>
#समावेश <यंत्र/cpu_mf.h>
#समावेश <यंत्र/irq.h>

#समावेश "entry.h"

/* empty control block to disable RI by loading it */
काष्ठा runसमय_instr_cb runसमय_instr_empty_cb;

व्योम runसमय_instr_release(काष्ठा task_काष्ठा *tsk)
अणु
	kमुक्त(tsk->thपढ़ो.ri_cb);
पूर्ण

अटल व्योम disable_runसमय_instr(व्योम)
अणु
	काष्ठा task_काष्ठा *task = current;
	काष्ठा pt_regs *regs;

	अगर (!task->thपढ़ो.ri_cb)
		वापस;
	regs = task_pt_regs(task);
	preempt_disable();
	load_runसमय_instr_cb(&runसमय_instr_empty_cb);
	kमुक्त(task->thपढ़ो.ri_cb);
	task->thपढ़ो.ri_cb = शून्य;
	preempt_enable();

	/*
	 * Make sure the RI bit is deleted from the PSW. If the user did not
	 * चयन off RI beक्रमe the प्रणाली call the process will get a
	 * specअगरication exception otherwise.
	 */
	regs->psw.mask &= ~PSW_MASK_RI;
पूर्ण

अटल व्योम init_runसमय_instr_cb(काष्ठा runसमय_instr_cb *cb)
अणु
	cb->rla = 0xfff;
	cb->s = 1;
	cb->k = 1;
	cb->ps = 1;
	cb->pc = 1;
	cb->key = PAGE_DEFAULT_KEY >> 4;
	cb->v = 1;
पूर्ण

/*
 * The signum argument is unused. In older kernels it was used to
 * specअगरy a real-समय संकेत. For backwards compatibility user space
 * should pass a valid real-समय संकेत number (the signum argument
 * was checked in older kernels).
 */
SYSCALL_DEFINE2(s390_runसमय_instr, पूर्णांक, command, पूर्णांक, signum)
अणु
	काष्ठा runसमय_instr_cb *cb;

	अगर (!test_facility(64))
		वापस -EOPNOTSUPP;

	अगर (command == S390_RUNTIME_INSTR_STOP) अणु
		disable_runसमय_instr();
		वापस 0;
	पूर्ण

	अगर (command != S390_RUNTIME_INSTR_START)
		वापस -EINVAL;

	अगर (!current->thपढ़ो.ri_cb) अणु
		cb = kzalloc(माप(*cb), GFP_KERNEL);
		अगर (!cb)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		cb = current->thपढ़ो.ri_cb;
		स_रखो(cb, 0, माप(*cb));
	पूर्ण

	init_runसमय_instr_cb(cb);

	/* now load the control block to make it available */
	preempt_disable();
	current->thपढ़ो.ri_cb = cb;
	load_runसमय_instr_cb(cb);
	preempt_enable();
	वापस 0;
पूर्ण
