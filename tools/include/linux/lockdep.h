<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_LOCKDEP_H_
#घोषणा _LIBLOCKDEP_LOCKDEP_H_

#समावेश <sys/prctl.h>
#समावेश <sys/syscall.h>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <linux/utsname.h>
#समावेश <linux/compiler.h>
#समावेश <linux/export.h>
#समावेश <linux/kern_levels.h>
#समावेश <linux/err.h>
#समावेश <linux/rcu.h>
#समावेश <linux/list.h>
#समावेश <linux/hardirq.h>
#समावेश <unistd.h>

#घोषणा MAX_LOCK_DEPTH 63UL

#घोषणा यंत्रlinkage
#घोषणा __visible

#समावेश "../../../include/linux/lockdep.h"

काष्ठा task_काष्ठा अणु
	u64 curr_chain_key;
	पूर्णांक lockdep_depth;
	अचिन्हित पूर्णांक lockdep_recursion;
	काष्ठा held_lock held_locks[MAX_LOCK_DEPTH];
	gfp_t lockdep_reclaim_gfp;
	पूर्णांक pid;
	पूर्णांक state;
	अक्षर comm[17];
पूर्ण;

#घोषणा TASK_RUNNING 0

बाह्य काष्ठा task_काष्ठा *__curr(व्योम);

#घोषणा current (__curr())

अटल अंतरभूत पूर्णांक debug_locks_off(व्योम)
अणु
	वापस 1;
पूर्ण

#घोषणा task_pid_nr(tsk) ((tsk)->pid)

#घोषणा KSYM_NAME_LEN 128
#घोषणा prपूर्णांकk(...) dम_लिखो(STDOUT_खाताNO, __VA_ARGS__)
#घोषणा pr_err(क्रमmat, ...) ख_लिखो (मानक_त्रुटि, क्रमmat, ## __VA_ARGS__)
#घोषणा pr_warn pr_err
#घोषणा pr_cont pr_err

#घोषणा list_del_rcu list_del

#घोषणा atomic_t अचिन्हित दीर्घ
#घोषणा atomic_inc(x) ((*(x))++)

#घोषणा prपूर्णांक_taपूर्णांकed() ""
#घोषणा अटल_obj(x) 1

#घोषणा debug_show_all_locks()
बाह्य व्योम debug_check_no_locks_held(व्योम);

अटल __used bool __is_kernel_percpu_address(अचिन्हित दीर्घ addr, व्योम *can_addr)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर
