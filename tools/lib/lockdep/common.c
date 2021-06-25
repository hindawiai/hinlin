<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <linux/compiler.h>
#समावेश <linux/lockdep.h>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

अटल __thपढ़ो काष्ठा task_काष्ठा current_obj;

/* lockdep wants these */
bool debug_locks = true;
bool debug_locks_silent;

__attribute__((deकाष्ठाor)) अटल व्योम liblockdep_निकास(व्योम)
अणु
	debug_check_no_locks_held();
पूर्ण

काष्ठा task_काष्ठा *__curr(व्योम)
अणु
	अगर (current_obj.pid == 0) अणु
		/* Makes lockdep output pretty */
		prctl(PR_GET_NAME, current_obj.comm);
		current_obj.pid = syscall(__NR_gettid);
	पूर्ण

	वापस &current_obj;
पूर्ण
