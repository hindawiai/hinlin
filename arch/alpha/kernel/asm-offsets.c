<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generate definitions needed by assembly language modules.
 * This code generates raw यंत्र output which is post-processed to extract
 * and क्रमmat the required data.
 */

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/पन.स>

व्योम foo(व्योम)
अणु
	DEFINE(TI_TASK, दुरत्व(काष्ठा thपढ़ो_info, task));
	DEFINE(TI_FLAGS, दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(TI_CPU, दुरत्व(काष्ठा thपढ़ो_info, cpu));
	BLANK();

        DEFINE(TASK_BLOCKED, दुरत्व(काष्ठा task_काष्ठा, blocked));
        DEFINE(TASK_CRED, दुरत्व(काष्ठा task_काष्ठा, cred));
        DEFINE(TASK_REAL_PARENT, दुरत्व(काष्ठा task_काष्ठा, real_parent));
        DEFINE(TASK_GROUP_LEADER, दुरत्व(काष्ठा task_काष्ठा, group_leader));
        DEFINE(TASK_TGID, दुरत्व(काष्ठा task_काष्ठा, tgid));
        BLANK();

        DEFINE(CRED_UID,  दुरत्व(काष्ठा cred, uid));
        DEFINE(CRED_EUID, दुरत्व(काष्ठा cred, euid));
        DEFINE(CRED_GID,  दुरत्व(काष्ठा cred, gid));
        DEFINE(CRED_EGID, दुरत्व(काष्ठा cred, egid));
        BLANK();

	DEFINE(SIZखातापूर्ण_PT_REGS, माप(काष्ठा pt_regs));
	DEFINE(PT_PTRACED, PT_PTRACED);
	DEFINE(CLONE_VM, CLONE_VM);
	DEFINE(CLONE_UNTRACED, CLONE_UNTRACED);
	DEFINE(SIGCHLD, SIGCHLD);
	BLANK();

	DEFINE(HAE_CACHE, दुरत्व(काष्ठा alpha_machine_vector, hae_cache));
	DEFINE(HAE_REG, दुरत्व(काष्ठा alpha_machine_vector, hae_रेजिस्टर));
पूर्ण
