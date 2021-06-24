<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FUTEX_H
#घोषणा _LINUX_FUTEX_H

#समावेश <linux/sched.h>
#समावेश <linux/kसमय.स>

#समावेश <uapi/linux/futex.h>

काष्ठा inode;
काष्ठा mm_काष्ठा;
काष्ठा task_काष्ठा;

/*
 * Futexes are matched on equal values of this key.
 * The key type depends on whether it's a shared or निजी mapping.
 * Don't rearrange members without looking at hash_futex().
 *
 * offset is aligned to a multiple of माप(u32) (== 4) by definition.
 * We use the two low order bits of offset to tell what is the kind of key :
 *  00 : Private process futex (PTHREAD_PROCESS_PRIVATE)
 *       (no reference on an inode or mm)
 *  01 : Shared futex (PTHREAD_PROCESS_SHARED)
 *	mapped on a file (reference on the underlying inode)
 *  10 : Shared futex (PTHREAD_PROCESS_SHARED)
 *       (but निजी mapping on an mm, and reference taken on it)
*/

#घोषणा FUT_OFF_INODE    1 /* We set bit 0 अगर key has a reference on inode */
#घोषणा FUT_OFF_MMSHARED 2 /* We set bit 1 अगर key has a reference on mm */

जोड़ futex_key अणु
	काष्ठा अणु
		u64 i_seq;
		अचिन्हित दीर्घ pgoff;
		अचिन्हित पूर्णांक offset;
	पूर्ण shared;
	काष्ठा अणु
		जोड़ अणु
			काष्ठा mm_काष्ठा *mm;
			u64 __पंचांगp;
		पूर्ण;
		अचिन्हित दीर्घ address;
		अचिन्हित पूर्णांक offset;
	पूर्ण निजी;
	काष्ठा अणु
		u64 ptr;
		अचिन्हित दीर्घ word;
		अचिन्हित पूर्णांक offset;
	पूर्ण both;
पूर्ण;

#घोषणा FUTEX_KEY_INIT (जोड़ futex_key) अणु .both = अणु .ptr = 0ULL पूर्ण पूर्ण

#अगर_घोषित CONFIG_FUTEX
क्रमागत अणु
	FUTEX_STATE_OK,
	FUTEX_STATE_EXITING,
	FUTEX_STATE_DEAD,
पूर्ण;

अटल अंतरभूत व्योम futex_init_task(काष्ठा task_काष्ठा *tsk)
अणु
	tsk->robust_list = शून्य;
#अगर_घोषित CONFIG_COMPAT
	tsk->compat_robust_list = शून्य;
#पूर्ण_अगर
	INIT_LIST_HEAD(&tsk->pi_state_list);
	tsk->pi_state_cache = शून्य;
	tsk->futex_state = FUTEX_STATE_OK;
	mutex_init(&tsk->futex_निकास_mutex);
पूर्ण

व्योम futex_निकास_recursive(काष्ठा task_काष्ठा *tsk);
व्योम futex_निकास_release(काष्ठा task_काष्ठा *tsk);
व्योम futex_exec_release(काष्ठा task_काष्ठा *tsk);

दीर्घ करो_futex(u32 __user *uaddr, पूर्णांक op, u32 val, kसमय_प्रकार *समयout,
	      u32 __user *uaddr2, u32 val2, u32 val3);
#अन्यथा
अटल अंतरभूत व्योम futex_init_task(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम futex_निकास_recursive(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम futex_निकास_release(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत व्योम futex_exec_release(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
अटल अंतरभूत दीर्घ करो_futex(u32 __user *uaddr, पूर्णांक op, u32 val,
			    kसमय_प्रकार *समयout, u32 __user *uaddr2,
			    u32 val2, u32 val3)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
