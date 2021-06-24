<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/ipc/util.h
 * Copyright (C) 1999 Christoph Rohland
 *
 * ipc helper functions (c) 1999 Manfred Spraul <manfred@colorfullअगरe.com>
 * namespaces support.      2006 OpenVZ, SWsoft Inc.
 *                               Pavel Emelianov <xemul@खोलोvz.org>
 */

#अगर_अघोषित _IPC_UTIL_H
#घोषणा _IPC_UTIL_H

#समावेश <linux/unistd.h>
#समावेश <linux/err.h>
#समावेश <linux/ipc_namespace.h>

/*
 * The IPC ID contains 2 separate numbers - index and sequence number.
 * By शेष,
 *   bits  0-14: index (32k, 15 bits)
 *   bits 15-30: sequence number (64k, 16 bits)
 *
 * When IPCMNI extension mode is turned on, the composition changes:
 *   bits  0-23: index (16M, 24 bits)
 *   bits 24-30: sequence number (128, 7 bits)
 */
#घोषणा IPCMNI_SHIFT		15
#घोषणा IPCMNI_EXTEND_SHIFT	24
#घोषणा IPCMNI_EXTEND_MIN_CYCLE	(RADIX_TREE_MAP_SIZE * RADIX_TREE_MAP_SIZE)
#घोषणा IPCMNI			(1 << IPCMNI_SHIFT)
#घोषणा IPCMNI_EXTEND		(1 << IPCMNI_EXTEND_SHIFT)

#अगर_घोषित CONFIG_SYSVIPC_SYSCTL
बाह्य पूर्णांक ipc_mni;
बाह्य पूर्णांक ipc_mni_shअगरt;
बाह्य पूर्णांक ipc_min_cycle;

#घोषणा ipcmni_seq_shअगरt()	ipc_mni_shअगरt
#घोषणा IPCMNI_IDX_MASK		((1 << ipc_mni_shअगरt) - 1)

#अन्यथा /* CONFIG_SYSVIPC_SYSCTL */

#घोषणा ipc_mni			IPCMNI
#घोषणा ipc_min_cycle		((पूर्णांक)RADIX_TREE_MAP_SIZE)
#घोषणा ipcmni_seq_shअगरt()	IPCMNI_SHIFT
#घोषणा IPCMNI_IDX_MASK		((1 << IPCMNI_SHIFT) - 1)
#पूर्ण_अगर /* CONFIG_SYSVIPC_SYSCTL */

व्योम sem_init(व्योम);
व्योम msg_init(व्योम);
व्योम shm_init(व्योम);

काष्ठा ipc_namespace;
काष्ठा pid_namespace;

#अगर_घोषित CONFIG_POSIX_MQUEUE
बाह्य व्योम mq_clear_sbinfo(काष्ठा ipc_namespace *ns);
बाह्य व्योम mq_put_mnt(काष्ठा ipc_namespace *ns);
#अन्यथा
अटल अंतरभूत व्योम mq_clear_sbinfo(काष्ठा ipc_namespace *ns) अणु पूर्ण
अटल अंतरभूत व्योम mq_put_mnt(काष्ठा ipc_namespace *ns) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSVIPC
व्योम sem_init_ns(काष्ठा ipc_namespace *ns);
व्योम msg_init_ns(काष्ठा ipc_namespace *ns);
व्योम shm_init_ns(काष्ठा ipc_namespace *ns);

व्योम sem_निकास_ns(काष्ठा ipc_namespace *ns);
व्योम msg_निकास_ns(काष्ठा ipc_namespace *ns);
व्योम shm_निकास_ns(काष्ठा ipc_namespace *ns);
#अन्यथा
अटल अंतरभूत व्योम sem_init_ns(काष्ठा ipc_namespace *ns) अणु पूर्ण
अटल अंतरभूत व्योम msg_init_ns(काष्ठा ipc_namespace *ns) अणु पूर्ण
अटल अंतरभूत व्योम shm_init_ns(काष्ठा ipc_namespace *ns) अणु पूर्ण

अटल अंतरभूत व्योम sem_निकास_ns(काष्ठा ipc_namespace *ns) अणु पूर्ण
अटल अंतरभूत व्योम msg_निकास_ns(काष्ठा ipc_namespace *ns) अणु पूर्ण
अटल अंतरभूत व्योम shm_निकास_ns(काष्ठा ipc_namespace *ns) अणु पूर्ण
#पूर्ण_अगर

/*
 * Structure that holds the parameters needed by the ipc operations
 * (see after)
 */
काष्ठा ipc_params अणु
	key_t key;
	पूर्णांक flg;
	जोड़ अणु
		माप_प्रकार size;	/* क्रम shared memories */
		पूर्णांक nsems;	/* क्रम semaphores */
	पूर्ण u;			/* holds the getnew() specअगरic param */
पूर्ण;

/*
 * Structure that holds some ipc operations. This काष्ठाure is used to unअगरy
 * the calls to sys_msgget(), sys_semget(), sys_shmget()
 *      . routine to call to create a new ipc object. Can be one of newque,
 *        newary, newseg
 *      . routine to call to check permissions क्रम a new ipc object.
 *        Can be one of security_msg_associate, security_sem_associate,
 *        security_shm_associate
 *      . routine to call क्रम an extra check अगर needed
 */
काष्ठा ipc_ops अणु
	पूर्णांक (*getnew)(काष्ठा ipc_namespace *, काष्ठा ipc_params *);
	पूर्णांक (*associate)(काष्ठा kern_ipc_perm *, पूर्णांक);
	पूर्णांक (*more_checks)(काष्ठा kern_ipc_perm *, काष्ठा ipc_params *);
पूर्ण;

काष्ठा seq_file;
काष्ठा ipc_ids;

व्योम ipc_init_ids(काष्ठा ipc_ids *ids);
#अगर_घोषित CONFIG_PROC_FS
व्योम __init ipc_init_proc_पूर्णांकerface(स्थिर अक्षर *path, स्थिर अक्षर *header,
		पूर्णांक ids, पूर्णांक (*show)(काष्ठा seq_file *, व्योम *));
काष्ठा pid_namespace *ipc_seq_pid_ns(काष्ठा seq_file *);
#अन्यथा
#घोषणा ipc_init_proc_पूर्णांकerface(path, header, ids, show) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा IPC_SEM_IDS	0
#घोषणा IPC_MSG_IDS	1
#घोषणा IPC_SHM_IDS	2

#घोषणा ipcid_to_idx(id)  ((id) & IPCMNI_IDX_MASK)
#घोषणा ipcid_to_seqx(id) ((id) >> ipcmni_seq_shअगरt())
#घोषणा ipcid_seq_max()	  (पूर्णांक_उच्च >> ipcmni_seq_shअगरt())

/* must be called with ids->rwsem acquired क्रम writing */
पूर्णांक ipc_addid(काष्ठा ipc_ids *, काष्ठा kern_ipc_perm *, पूर्णांक);

/* must be called with both locks acquired. */
व्योम ipc_rmid(काष्ठा ipc_ids *, काष्ठा kern_ipc_perm *);

/* must be called with both locks acquired. */
व्योम ipc_set_key_निजी(काष्ठा ipc_ids *, काष्ठा kern_ipc_perm *);

/* must be called with ipcp locked */
पूर्णांक ipcperms(काष्ठा ipc_namespace *ns, काष्ठा kern_ipc_perm *ipcp, लघु flg);

/**
 * ipc_get_maxidx - get the highest asचिन्हित index
 * @ids: ipc identअगरier set
 *
 * Called with ipc_ids.rwsem held क्रम पढ़ोing.
 */
अटल अंतरभूत पूर्णांक ipc_get_maxidx(काष्ठा ipc_ids *ids)
अणु
	अगर (ids->in_use == 0)
		वापस -1;

	अगर (ids->in_use == ipc_mni)
		वापस ipc_mni - 1;

	वापस ids->max_idx;
पूर्ण

/*
 * For allocation that need to be मुक्तd by RCU.
 * Objects are reference counted, they start with reference count 1.
 * getref increases the refcount, the putref call that reduces the recount
 * to 0 schedules the rcu deकाष्ठाion. Caller must guarantee locking.
 *
 * refcount is initialized by ipc_addid(), beक्रमe that poपूर्णांक call_rcu()
 * must be used.
 */
bool ipc_rcu_getref(काष्ठा kern_ipc_perm *ptr);
व्योम ipc_rcu_putref(काष्ठा kern_ipc_perm *ptr,
			व्योम (*func)(काष्ठा rcu_head *head));

काष्ठा kern_ipc_perm *ipc_obtain_object_idr(काष्ठा ipc_ids *ids, पूर्णांक id);

व्योम kernel_to_ipc64_perm(काष्ठा kern_ipc_perm *in, काष्ठा ipc64_perm *out);
व्योम ipc64_perm_to_ipc_perm(काष्ठा ipc64_perm *in, काष्ठा ipc_perm *out);
पूर्णांक ipc_update_perm(काष्ठा ipc64_perm *in, काष्ठा kern_ipc_perm *out);
काष्ठा kern_ipc_perm *ipcctl_obtain_check(काष्ठा ipc_namespace *ns,
					     काष्ठा ipc_ids *ids, पूर्णांक id, पूर्णांक cmd,
					     काष्ठा ipc64_perm *perm, पूर्णांक extra_perm);

अटल अंतरभूत व्योम ipc_update_pid(काष्ठा pid **pos, काष्ठा pid *pid)
अणु
	काष्ठा pid *old = *pos;
	अगर (old != pid) अणु
		*pos = get_pid(pid);
		put_pid(old);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_IPC_PARSE_VERSION
पूर्णांक ipc_parse_version(पूर्णांक *cmd);
#पूर्ण_अगर

बाह्य व्योम मुक्त_msg(काष्ठा msg_msg *msg);
बाह्य काष्ठा msg_msg *load_msg(स्थिर व्योम __user *src, माप_प्रकार len);
बाह्य काष्ठा msg_msg *copy_msg(काष्ठा msg_msg *src, काष्ठा msg_msg *dst);
बाह्य पूर्णांक store_msg(व्योम __user *dest, काष्ठा msg_msg *msg, माप_प्रकार len);

अटल अंतरभूत पूर्णांक ipc_checkid(काष्ठा kern_ipc_perm *ipcp, पूर्णांक id)
अणु
	वापस ipcid_to_seqx(id) != ipcp->seq;
पूर्ण

अटल अंतरभूत व्योम ipc_lock_object(काष्ठा kern_ipc_perm *perm)
अणु
	spin_lock(&perm->lock);
पूर्ण

अटल अंतरभूत व्योम ipc_unlock_object(काष्ठा kern_ipc_perm *perm)
अणु
	spin_unlock(&perm->lock);
पूर्ण

अटल अंतरभूत व्योम ipc_निश्चित_locked_object(काष्ठा kern_ipc_perm *perm)
अणु
	निश्चित_spin_locked(&perm->lock);
पूर्ण

अटल अंतरभूत व्योम ipc_unlock(काष्ठा kern_ipc_perm *perm)
अणु
	ipc_unlock_object(perm);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * ipc_valid_object() - helper to sort out IPC_RMID races क्रम codepaths
 * where the respective ipc_ids.rwsem is not being held करोwn.
 * Checks whether the ipc object is still around or अगर it's gone alपढ़ोy, as
 * ipc_rmid() may have alपढ़ोy मुक्तd the ID जबतक the ipc lock was spinning.
 * Needs to be called with kern_ipc_perm.lock held -- exception made क्रम one
 * checkpoपूर्णांक हाल at sys_semसमयकरोp() as noted in code commentary.
 */
अटल अंतरभूत bool ipc_valid_object(काष्ठा kern_ipc_perm *perm)
अणु
	वापस !perm->deleted;
पूर्ण

काष्ठा kern_ipc_perm *ipc_obtain_object_check(काष्ठा ipc_ids *ids, पूर्णांक id);
पूर्णांक ipcget(काष्ठा ipc_namespace *ns, काष्ठा ipc_ids *ids,
			स्थिर काष्ठा ipc_ops *ops, काष्ठा ipc_params *params);
व्योम मुक्त_ipcs(काष्ठा ipc_namespace *ns, काष्ठा ipc_ids *ids,
		व्योम (*मुक्त)(काष्ठा ipc_namespace *, काष्ठा kern_ipc_perm *));

अटल अंतरभूत पूर्णांक sem_check_semmni(काष्ठा ipc_namespace *ns) अणु
	/*
	 * Check semmni range [0, ipc_mni]
	 * semmni is the last element of sem_ctls[4] array
	 */
	वापस ((ns->sem_ctls[3] < 0) || (ns->sem_ctls[3] > ipc_mni))
		? -दुस्फल : 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>
काष्ठा compat_ipc_perm अणु
	key_t key;
	__compat_uid_t uid;
	__compat_gid_t gid;
	__compat_uid_t cuid;
	__compat_gid_t cgid;
	compat_mode_t mode;
	अचिन्हित लघु seq;
पूर्ण;

व्योम to_compat_ipc_perm(काष्ठा compat_ipc_perm *, काष्ठा ipc64_perm *);
व्योम to_compat_ipc64_perm(काष्ठा compat_ipc64_perm *, काष्ठा ipc64_perm *);
पूर्णांक get_compat_ipc_perm(काष्ठा ipc64_perm *, काष्ठा compat_ipc_perm __user *);
पूर्णांक get_compat_ipc64_perm(काष्ठा ipc64_perm *,
			  काष्ठा compat_ipc64_perm __user *);

अटल अंतरभूत पूर्णांक compat_ipc_parse_version(पूर्णांक *cmd)
अणु
	पूर्णांक version = *cmd & IPC_64;
	*cmd &= ~IPC_64;
	वापस version;
पूर्ण

दीर्घ compat_ksys_old_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, पूर्णांक arg);
दीर्घ compat_ksys_old_msgctl(पूर्णांक msqid, पूर्णांक cmd, व्योम __user *uptr);
दीर्घ compat_ksys_msgrcv(पूर्णांक msqid, compat_uptr_t msgp, compat_sमाप_प्रकार msgsz,
			compat_दीर्घ_t msgtyp, पूर्णांक msgflg);
दीर्घ compat_ksys_msgsnd(पूर्णांक msqid, compat_uptr_t msgp,
		       compat_sमाप_प्रकार msgsz, पूर्णांक msgflg);
दीर्घ compat_ksys_old_shmctl(पूर्णांक shmid, पूर्णांक cmd, व्योम __user *uptr);

#पूर्ण_अगर

#पूर्ण_अगर
