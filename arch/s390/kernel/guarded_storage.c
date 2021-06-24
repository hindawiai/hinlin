<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2016
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/guarded_storage.h>
#समावेश "entry.h"

व्योम guarded_storage_release(काष्ठा task_काष्ठा *tsk)
अणु
	kमुक्त(tsk->thपढ़ो.gs_cb);
	kमुक्त(tsk->thपढ़ो.gs_bc_cb);
पूर्ण

अटल पूर्णांक gs_enable(व्योम)
अणु
	काष्ठा gs_cb *gs_cb;

	अगर (!current->thपढ़ो.gs_cb) अणु
		gs_cb = kzalloc(माप(*gs_cb), GFP_KERNEL);
		अगर (!gs_cb)
			वापस -ENOMEM;
		gs_cb->gsd = 25;
		preempt_disable();
		__ctl_set_bit(2, 4);
		load_gs_cb(gs_cb);
		current->thपढ़ो.gs_cb = gs_cb;
		preempt_enable();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gs_disable(व्योम)
अणु
	अगर (current->thपढ़ो.gs_cb) अणु
		preempt_disable();
		kमुक्त(current->thपढ़ो.gs_cb);
		current->thपढ़ो.gs_cb = शून्य;
		__ctl_clear_bit(2, 4);
		preempt_enable();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gs_set_bc_cb(काष्ठा gs_cb __user *u_gs_cb)
अणु
	काष्ठा gs_cb *gs_cb;

	gs_cb = current->thपढ़ो.gs_bc_cb;
	अगर (!gs_cb) अणु
		gs_cb = kzalloc(माप(*gs_cb), GFP_KERNEL);
		अगर (!gs_cb)
			वापस -ENOMEM;
		current->thपढ़ो.gs_bc_cb = gs_cb;
	पूर्ण
	अगर (copy_from_user(gs_cb, u_gs_cb, माप(*gs_cb)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक gs_clear_bc_cb(व्योम)
अणु
	काष्ठा gs_cb *gs_cb;

	gs_cb = current->thपढ़ो.gs_bc_cb;
	current->thपढ़ो.gs_bc_cb = शून्य;
	kमुक्त(gs_cb);
	वापस 0;
पूर्ण

व्योम gs_load_bc_cb(काष्ठा pt_regs *regs)
अणु
	काष्ठा gs_cb *gs_cb;

	preempt_disable();
	clear_thपढ़ो_flag(TIF_GUARDED_STORAGE);
	gs_cb = current->thपढ़ो.gs_bc_cb;
	अगर (gs_cb) अणु
		kमुक्त(current->thपढ़ो.gs_cb);
		current->thपढ़ो.gs_bc_cb = शून्य;
		__ctl_set_bit(2, 4);
		load_gs_cb(gs_cb);
		current->thपढ़ो.gs_cb = gs_cb;
	पूर्ण
	preempt_enable();
पूर्ण

अटल पूर्णांक gs_broadcast(व्योम)
अणु
	काष्ठा task_काष्ठा *sibling;

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_thपढ़ो(current, sibling) अणु
		अगर (!sibling->thपढ़ो.gs_bc_cb)
			जारी;
		अगर (test_and_set_tsk_thपढ़ो_flag(sibling, TIF_GUARDED_STORAGE))
			kick_process(sibling);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(s390_guarded_storage, पूर्णांक, command,
		काष्ठा gs_cb __user *, gs_cb)
अणु
	अगर (!MACHINE_HAS_GS)
		वापस -EOPNOTSUPP;
	चयन (command) अणु
	हाल GS_ENABLE:
		वापस gs_enable();
	हाल GS_DISABLE:
		वापस gs_disable();
	हाल GS_SET_BC_CB:
		वापस gs_set_bc_cb(gs_cb);
	हाल GS_CLEAR_BC_CB:
		वापस gs_clear_bc_cb();
	हाल GS_BROADCAST:
		वापस gs_broadcast();
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
