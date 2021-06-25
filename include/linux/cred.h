<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Credentials management - see Documentation/security/credentials.rst
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_CRED_H
#घोषणा _LINUX_CRED_H

#समावेश <linux/capability.h>
#समावेश <linux/init.h>
#समावेश <linux/key.h>
#समावेश <linux/atomic.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/user.h>

काष्ठा cred;
काष्ठा inode;

/*
 * COW Supplementary groups list
 */
काष्ठा group_info अणु
	atomic_t	usage;
	पूर्णांक		ngroups;
	kgid_t		gid[];
पूर्ण __अक्रमomize_layout;

/**
 * get_group_info - Get a reference to a group info काष्ठाure
 * @group_info: The group info to reference
 *
 * This माला_लो a reference to a set of supplementary groups.
 *
 * If the caller is accessing a task's credentials, they must hold the RCU पढ़ो
 * lock when पढ़ोing.
 */
अटल अंतरभूत काष्ठा group_info *get_group_info(काष्ठा group_info *gi)
अणु
	atomic_inc(&gi->usage);
	वापस gi;
पूर्ण

/**
 * put_group_info - Release a reference to a group info काष्ठाure
 * @group_info: The group info to release
 */
#घोषणा put_group_info(group_info)			\
करो अणु							\
	अगर (atomic_dec_and_test(&(group_info)->usage))	\
		groups_मुक्त(group_info);		\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_MULTIUSER
बाह्य काष्ठा group_info *groups_alloc(पूर्णांक);
बाह्य व्योम groups_मुक्त(काष्ठा group_info *);

बाह्य पूर्णांक in_group_p(kgid_t);
बाह्य पूर्णांक in_egroup_p(kgid_t);
बाह्य पूर्णांक groups_search(स्थिर काष्ठा group_info *, kgid_t);

बाह्य पूर्णांक set_current_groups(काष्ठा group_info *);
बाह्य व्योम set_groups(काष्ठा cred *, काष्ठा group_info *);
बाह्य bool may_setgroups(व्योम);
बाह्य व्योम groups_sort(काष्ठा group_info *);
#अन्यथा
अटल अंतरभूत व्योम groups_मुक्त(काष्ठा group_info *group_info)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक in_group_p(kgid_t grp)
अणु
        वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक in_egroup_p(kgid_t grp)
अणु
        वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक groups_search(स्थिर काष्ठा group_info *group_info, kgid_t grp)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

/*
 * The security context of a task
 *
 * The parts of the context अवरोध करोwn पूर्णांकo two categories:
 *
 *  (1) The objective context of a task.  These parts are used when some other
 *	task is attempting to affect this one.
 *
 *  (2) The subjective context.  These details are used when the task is acting
 *	upon another object, be that a file, a task, a key or whatever.
 *
 * Note that some members of this काष्ठाure beदीर्घ to both categories - the
 * LSM security poपूर्णांकer क्रम instance.
 *
 * A task has two security poपूर्णांकers.  task->real_cred poपूर्णांकs to the objective
 * context that defines that task's actual details.  The objective part of this
 * context is used whenever that task is acted upon.
 *
 * task->cred poपूर्णांकs to the subjective context that defines the details of how
 * that task is going to act upon another object.  This may be overridden
 * temporarily to poपूर्णांक to another security context, but normally poपूर्णांकs to the
 * same context as task->real_cred.
 */
काष्ठा cred अणु
	atomic_t	usage;
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
	atomic_t	subscribers;	/* number of processes subscribed */
	व्योम		*put_addr;
	अचिन्हित	magic;
#घोषणा CRED_MAGIC	0x43736564
#घोषणा CRED_MAGIC_DEAD	0x44656144
#पूर्ण_अगर
	kuid_t		uid;		/* real UID of the task */
	kgid_t		gid;		/* real GID of the task */
	kuid_t		suid;		/* saved UID of the task */
	kgid_t		sgid;		/* saved GID of the task */
	kuid_t		euid;		/* effective UID of the task */
	kgid_t		egid;		/* effective GID of the task */
	kuid_t		fsuid;		/* UID क्रम VFS ops */
	kgid_t		fsgid;		/* GID क्रम VFS ops */
	अचिन्हित	securebits;	/* SUID-less security management */
	kernel_cap_t	cap_inheritable; /* caps our children can inherit */
	kernel_cap_t	cap_permitted;	/* caps we're permitted */
	kernel_cap_t	cap_effective;	/* caps we can actually use */
	kernel_cap_t	cap_bset;	/* capability bounding set */
	kernel_cap_t	cap_ambient;	/* Ambient capability set */
#अगर_घोषित CONFIG_KEYS
	अचिन्हित अक्षर	jit_keyring;	/* शेष keyring to attach requested
					 * keys to */
	काष्ठा key	*session_keyring; /* keyring inherited over विभाजन */
	काष्ठा key	*process_keyring; /* keyring निजी to this process */
	काष्ठा key	*thपढ़ो_keyring; /* keyring निजी to this thपढ़ो */
	काष्ठा key	*request_key_auth; /* assumed request_key authority */
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY
	व्योम		*security;	/* LSM security */
#पूर्ण_अगर
	काष्ठा user_काष्ठा *user;	/* real user ID subscription */
	काष्ठा user_namespace *user_ns; /* user_ns the caps and keyrings are relative to. */
	काष्ठा group_info *group_info;	/* supplementary groups क्रम euid/fsgid */
	/* RCU deletion */
	जोड़ अणु
		पूर्णांक non_rcu;			/* Can we skip RCU deletion? */
		काष्ठा rcu_head	rcu;		/* RCU deletion hook */
	पूर्ण;
पूर्ण __अक्रमomize_layout;

बाह्य व्योम __put_cred(काष्ठा cred *);
बाह्य व्योम निकास_creds(काष्ठा task_काष्ठा *);
बाह्य पूर्णांक copy_creds(काष्ठा task_काष्ठा *, अचिन्हित दीर्घ);
बाह्य स्थिर काष्ठा cred *get_task_cred(काष्ठा task_काष्ठा *);
बाह्य काष्ठा cred *cred_alloc_blank(व्योम);
बाह्य काष्ठा cred *prepare_creds(व्योम);
बाह्य काष्ठा cred *prepare_exec_creds(व्योम);
बाह्य पूर्णांक commit_creds(काष्ठा cred *);
बाह्य व्योम पात_creds(काष्ठा cred *);
बाह्य स्थिर काष्ठा cred *override_creds(स्थिर काष्ठा cred *);
बाह्य व्योम revert_creds(स्थिर काष्ठा cred *);
बाह्य काष्ठा cred *prepare_kernel_cred(काष्ठा task_काष्ठा *);
बाह्य पूर्णांक change_create_files_as(काष्ठा cred *, काष्ठा inode *);
बाह्य पूर्णांक set_security_override(काष्ठा cred *, u32);
बाह्य पूर्णांक set_security_override_from_ctx(काष्ठा cred *, स्थिर अक्षर *);
बाह्य पूर्णांक set_create_files_as(काष्ठा cred *, काष्ठा inode *);
बाह्य पूर्णांक cred_fscmp(स्थिर काष्ठा cred *, स्थिर काष्ठा cred *);
बाह्य व्योम __init cred_init(व्योम);

/*
 * check क्रम validity of credentials
 */
#अगर_घोषित CONFIG_DEBUG_CREDENTIALS
बाह्य व्योम __invalid_creds(स्थिर काष्ठा cred *, स्थिर अक्षर *, अचिन्हित);
बाह्य व्योम __validate_process_creds(काष्ठा task_काष्ठा *,
				     स्थिर अक्षर *, अचिन्हित);

बाह्य bool creds_are_invalid(स्थिर काष्ठा cred *cred);

अटल अंतरभूत व्योम __validate_creds(स्थिर काष्ठा cred *cred,
				    स्थिर अक्षर *file, अचिन्हित line)
अणु
	अगर (unlikely(creds_are_invalid(cred)))
		__invalid_creds(cred, file, line);
पूर्ण

#घोषणा validate_creds(cred)				\
करो अणु							\
	__validate_creds((cred), __खाता__, __LINE__);	\
पूर्ण जबतक(0)

#घोषणा validate_process_creds()				\
करो अणु								\
	__validate_process_creds(current, __खाता__, __LINE__);	\
पूर्ण जबतक(0)

बाह्य व्योम validate_creds_क्रम_करो_निकास(काष्ठा task_काष्ठा *);
#अन्यथा
अटल अंतरभूत व्योम validate_creds(स्थिर काष्ठा cred *cred)
अणु
पूर्ण
अटल अंतरभूत व्योम validate_creds_क्रम_करो_निकास(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
अटल अंतरभूत व्योम validate_process_creds(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool cap_ambient_invariant_ok(स्थिर काष्ठा cred *cred)
अणु
	वापस cap_issubset(cred->cap_ambient,
			    cap_पूर्णांकersect(cred->cap_permitted,
					  cred->cap_inheritable));
पूर्ण

/**
 * get_new_cred - Get a reference on a new set of credentials
 * @cred: The new credentials to reference
 *
 * Get a reference on the specअगरied set of new credentials.  The caller must
 * release the reference.
 */
अटल अंतरभूत काष्ठा cred *get_new_cred(काष्ठा cred *cred)
अणु
	atomic_inc(&cred->usage);
	वापस cred;
पूर्ण

/**
 * get_cred - Get a reference on a set of credentials
 * @cred: The credentials to reference
 *
 * Get a reference on the specअगरied set of credentials.  The caller must
 * release the reference.  If %शून्य is passed, it is वापसed with no action.
 *
 * This is used to deal with a committed set of credentials.  Although the
 * poपूर्णांकer is स्थिर, this will temporarily discard the स्थिर and increment the
 * usage count.  The purpose of this is to attempt to catch at compile समय the
 * accidental alteration of a set of credentials that should be considered
 * immutable.
 */
अटल अंतरभूत स्थिर काष्ठा cred *get_cred(स्थिर काष्ठा cred *cred)
अणु
	काष्ठा cred *nonस्थिर_cred = (काष्ठा cred *) cred;
	अगर (!cred)
		वापस cred;
	validate_creds(cred);
	nonस्थिर_cred->non_rcu = 0;
	वापस get_new_cred(nonस्थिर_cred);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cred *get_cred_rcu(स्थिर काष्ठा cred *cred)
अणु
	काष्ठा cred *nonस्थिर_cred = (काष्ठा cred *) cred;
	अगर (!cred)
		वापस शून्य;
	अगर (!atomic_inc_not_zero(&nonस्थिर_cred->usage))
		वापस शून्य;
	validate_creds(cred);
	nonस्थिर_cred->non_rcu = 0;
	वापस cred;
पूर्ण

/**
 * put_cred - Release a reference to a set of credentials
 * @cred: The credentials to release
 *
 * Release a reference to a set of credentials, deleting them when the last ref
 * is released.  If %शून्य is passed, nothing is करोne.
 *
 * This takes a स्थिर poपूर्णांकer to a set of credentials because the credentials
 * on task_काष्ठा are attached by स्थिर poपूर्णांकers to prevent accidental
 * alteration of otherwise immutable credential sets.
 */
अटल अंतरभूत व्योम put_cred(स्थिर काष्ठा cred *_cred)
अणु
	काष्ठा cred *cred = (काष्ठा cred *) _cred;

	अगर (cred) अणु
		validate_creds(cred);
		अगर (atomic_dec_and_test(&(cred)->usage))
			__put_cred(cred);
	पूर्ण
पूर्ण

/**
 * current_cred - Access the current task's subjective credentials
 *
 * Access the subjective credentials of the current task.  RCU-safe,
 * since nobody अन्यथा can modअगरy it.
 */
#घोषणा current_cred() \
	rcu_dereference_रक्षित(current->cred, 1)

/**
 * current_real_cred - Access the current task's objective credentials
 *
 * Access the objective credentials of the current task.  RCU-safe,
 * since nobody अन्यथा can modअगरy it.
 */
#घोषणा current_real_cred() \
	rcu_dereference_रक्षित(current->real_cred, 1)

/**
 * __task_cred - Access a task's objective credentials
 * @task: The task to query
 *
 * Access the objective credentials of a task.  The caller must hold the RCU
 * पढ़ोlock.
 *
 * The result of this function should not be passed directly to get_cred();
 * rather get_task_cred() should be used instead.
 */
#घोषणा __task_cred(task)	\
	rcu_dereference((task)->real_cred)

/**
 * get_current_cred - Get the current task's subjective credentials
 *
 * Get the subjective credentials of the current task, pinning them so that
 * they can't go away.  Accessing the current task's credentials directly is
 * not permitted.
 */
#घोषणा get_current_cred()				\
	(get_cred(current_cred()))

/**
 * get_current_user - Get the current task's user_काष्ठा
 *
 * Get the user record of the current task, pinning it so that it can't go
 * away.
 */
#घोषणा get_current_user()				\
(अणु							\
	काष्ठा user_काष्ठा *__u;			\
	स्थिर काष्ठा cred *__cred;			\
	__cred = current_cred();			\
	__u = get_uid(__cred->user);			\
	__u;						\
पूर्ण)

/**
 * get_current_groups - Get the current task's supplementary group list
 *
 * Get the supplementary group list of the current task, pinning it so that it
 * can't go away.
 */
#घोषणा get_current_groups()				\
(अणु							\
	काष्ठा group_info *__groups;			\
	स्थिर काष्ठा cred *__cred;			\
	__cred = current_cred();			\
	__groups = get_group_info(__cred->group_info);	\
	__groups;					\
पूर्ण)

#घोषणा task_cred_xxx(task, xxx)			\
(अणु							\
	__typeof__(((काष्ठा cred *)शून्य)->xxx) ___val;	\
	rcu_पढ़ो_lock();				\
	___val = __task_cred((task))->xxx;		\
	rcu_पढ़ो_unlock();				\
	___val;						\
पूर्ण)

#घोषणा task_uid(task)		(task_cred_xxx((task), uid))
#घोषणा task_euid(task)		(task_cred_xxx((task), euid))

#घोषणा current_cred_xxx(xxx)			\
(अणु						\
	current_cred()->xxx;			\
पूर्ण)

#घोषणा current_uid()		(current_cred_xxx(uid))
#घोषणा current_gid()		(current_cred_xxx(gid))
#घोषणा current_euid()		(current_cred_xxx(euid))
#घोषणा current_egid()		(current_cred_xxx(egid))
#घोषणा current_suid()		(current_cred_xxx(suid))
#घोषणा current_sgid()		(current_cred_xxx(sgid))
#घोषणा current_fsuid() 	(current_cred_xxx(fsuid))
#घोषणा current_fsgid() 	(current_cred_xxx(fsgid))
#घोषणा current_cap()		(current_cred_xxx(cap_effective))
#घोषणा current_user()		(current_cred_xxx(user))

बाह्य काष्ठा user_namespace init_user_ns;
#अगर_घोषित CONFIG_USER_NS
#घोषणा current_user_ns()	(current_cred_xxx(user_ns))
#अन्यथा
अटल अंतरभूत काष्ठा user_namespace *current_user_ns(व्योम)
अणु
	वापस &init_user_ns;
पूर्ण
#पूर्ण_अगर


#घोषणा current_uid_gid(_uid, _gid)		\
करो अणु						\
	स्थिर काष्ठा cred *__cred;		\
	__cred = current_cred();		\
	*(_uid) = __cred->uid;			\
	*(_gid) = __cred->gid;			\
पूर्ण जबतक(0)

#घोषणा current_euid_egid(_euid, _egid)		\
करो अणु						\
	स्थिर काष्ठा cred *__cred;		\
	__cred = current_cred();		\
	*(_euid) = __cred->euid;		\
	*(_egid) = __cred->egid;		\
पूर्ण जबतक(0)

#घोषणा current_fsuid_fsgid(_fsuid, _fsgid)	\
करो अणु						\
	स्थिर काष्ठा cred *__cred;		\
	__cred = current_cred();		\
	*(_fsuid) = __cred->fsuid;		\
	*(_fsgid) = __cred->fsgid;		\
पूर्ण जबतक(0)

#पूर्ण_अगर /* _LINUX_CRED_H */
