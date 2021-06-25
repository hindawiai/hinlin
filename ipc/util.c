<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/ipc/util.c
 * Copyright (C) 1992 Krishna Balasubramanian
 *
 * Sep 1997 - Call suser() last after "normal" permission checks so we
 *            get BSD style process accounting right.
 *            Occurs in several places in the IPC code.
 *            Chris Evans, <chris@ferret.lmh.ox.ac.uk>
 * Nov 1999 - ipc helper functions, unअगरied SMP locking
 *	      Manfred Spraul <manfred@colorfullअगरe.com>
 * Oct 2002 - One lock per IPC id. RCU ipc_मुक्त क्रम lock-मुक्त grow_ary().
 *            Mingming Cao <cmm@us.ibm.com>
 * Mar 2006 - support क्रम audit of ipc object properties
 *            Dustin Kirkland <dustin.kirkland@us.ibm.com>
 * Jun 2006 - namespaces ssupport
 *            OpenVZ, SWsoft Inc.
 *            Pavel Emelianov <xemul@खोलोvz.org>
 *
 * General sysv ipc locking scheme:
 *	rcu_पढ़ो_lock()
 *          obtain the ipc object (kern_ipc_perm) by looking up the id in an idr
 *	    tree.
 *	    - perक्रमm initial checks (capabilities, auditing and permission,
 *	      etc).
 *	    - perक्रमm पढ़ो-only operations, such as INFO command, that
 *	      करो not demand atomicity
 *	      acquire the ipc lock (kern_ipc_perm.lock) through
 *	      ipc_lock_object()
 *		- perक्रमm पढ़ो-only operations that demand atomicity,
 *		  such as STAT command.
 *		- perक्रमm data updates, such as SET, RMID commands and
 *		  mechanism-specअगरic operations (semop/semसमयकरोp,
 *		  msgsnd/msgrcv, shmat/shmdt).
 *	    drop the ipc lock, through ipc_unlock_object().
 *	rcu_पढ़ो_unlock()
 *
 *  The ids->rwsem must be taken when:
 *	- creating, removing and iterating the existing entries in ipc
 *	  identअगरier sets.
 *	- iterating through files under /proc/sysvipc/
 *
 *  Note that sems have a special fast path that aव्योमs kern_ipc_perm.lock -
 *  see sem_lock().
 */

#समावेश <linux/mm.h>
#समावेश <linux/shm.h>
#समावेश <linux/init.h>
#समावेश <linux/msg.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/capability.h>
#समावेश <linux/highuid.h>
#समावेश <linux/security.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/audit.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/memory.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/rhashtable.h>

#समावेश <यंत्र/unistd.h>

#समावेश "util.h"

काष्ठा ipc_proc_अगरace अणु
	स्थिर अक्षर *path;
	स्थिर अक्षर *header;
	पूर्णांक ids;
	पूर्णांक (*show)(काष्ठा seq_file *, व्योम *);
पूर्ण;

/**
 * ipc_init - initialise ipc subप्रणाली
 *
 * The various sysv ipc resources (semaphores, messages and shared
 * memory) are initialised.
 *
 * A callback routine is रेजिस्टरed पूर्णांकo the memory hotplug notअगरier
 * chain: since msgmni scales to lowmem this callback routine will be
 * called upon successful memory add / हटाओ to recompute msmgni.
 */
अटल पूर्णांक __init ipc_init(व्योम)
अणु
	proc_सूची_गढ़ो("sysvipc", शून्य);
	sem_init();
	msg_init();
	shm_init();

	वापस 0;
पूर्ण
device_initcall(ipc_init);

अटल स्थिर काष्ठा rhashtable_params ipc_kht_params = अणु
	.head_offset		= दुरत्व(काष्ठा kern_ipc_perm, khtnode),
	.key_offset		= दुरत्व(काष्ठा kern_ipc_perm, key),
	.key_len		= माप_field(काष्ठा kern_ipc_perm, key),
	.स्वतःmatic_shrinking	= true,
पूर्ण;

/**
 * ipc_init_ids	- initialise ipc identअगरiers
 * @ids: ipc identअगरier set
 *
 * Set up the sequence range to use क्रम the ipc identअगरier range (limited
 * below ipc_mni) then initialise the keys hashtable and ids idr.
 */
व्योम ipc_init_ids(काष्ठा ipc_ids *ids)
अणु
	ids->in_use = 0;
	ids->seq = 0;
	init_rwsem(&ids->rwsem);
	rhashtable_init(&ids->key_ht, &ipc_kht_params);
	idr_init(&ids->ipcs_idr);
	ids->max_idx = -1;
	ids->last_idx = -1;
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	ids->next_id = -1;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल स्थिर काष्ठा proc_ops sysvipc_proc_ops;
/**
 * ipc_init_proc_पूर्णांकerface -  create a proc पूर्णांकerface क्रम sysipc types using a seq_file पूर्णांकerface.
 * @path: Path in procfs
 * @header: Banner to be prपूर्णांकed at the beginning of the file.
 * @ids: ipc id table to iterate.
 * @show: show routine.
 */
व्योम __init ipc_init_proc_पूर्णांकerface(स्थिर अक्षर *path, स्थिर अक्षर *header,
		पूर्णांक ids, पूर्णांक (*show)(काष्ठा seq_file *, व्योम *))
अणु
	काष्ठा proc_dir_entry *pde;
	काष्ठा ipc_proc_अगरace *अगरace;

	अगरace = kदो_स्मृति(माप(*अगरace), GFP_KERNEL);
	अगर (!अगरace)
		वापस;
	अगरace->path	= path;
	अगरace->header	= header;
	अगरace->ids	= ids;
	अगरace->show	= show;

	pde = proc_create_data(path,
			       S_IRUGO,        /* world पढ़ोable */
			       शून्य,           /* parent dir */
			       &sysvipc_proc_ops,
			       अगरace);
	अगर (!pde)
		kमुक्त(अगरace);
पूर्ण
#पूर्ण_अगर

/**
 * ipc_findkey	- find a key in an ipc identअगरier set
 * @ids: ipc identअगरier set
 * @key: key to find
 *
 * Returns the locked poपूर्णांकer to the ipc काष्ठाure अगर found or शून्य
 * otherwise. If key is found ipc poपूर्णांकs to the owning ipc काष्ठाure
 *
 * Called with ग_लिखोr ipc_ids.rwsem held.
 */
अटल काष्ठा kern_ipc_perm *ipc_findkey(काष्ठा ipc_ids *ids, key_t key)
अणु
	काष्ठा kern_ipc_perm *ipcp;

	ipcp = rhashtable_lookup_fast(&ids->key_ht, &key,
					      ipc_kht_params);
	अगर (!ipcp)
		वापस शून्य;

	rcu_पढ़ो_lock();
	ipc_lock_object(ipcp);
	वापस ipcp;
पूर्ण

/*
 * Insert new IPC object पूर्णांकo idr tree, and set sequence number and id
 * in the correct order.
 * Especially:
 * - the sequence number must be set beक्रमe inserting the object पूर्णांकo the idr,
 *   because the sequence number is accessed without a lock.
 * - the id can/must be set after inserting the object पूर्णांकo the idr.
 *   All accesses must be करोne after getting kern_ipc_perm.lock.
 *
 * The caller must own kern_ipc_perm.lock.of the new object.
 * On error, the function वापसs a (negative) error code.
 *
 * To conserve sequence number space, especially with extended ipc_mni,
 * the sequence number is incremented only when the वापसed ID is less than
 * the last one.
 */
अटल अंतरभूत पूर्णांक ipc_idr_alloc(काष्ठा ipc_ids *ids, काष्ठा kern_ipc_perm *new)
अणु
	पूर्णांक idx, next_id = -1;

#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	next_id = ids->next_id;
	ids->next_id = -1;
#पूर्ण_अगर

	/*
	 * As soon as a new object is inserted पूर्णांकo the idr,
	 * ipc_obtain_object_idr() or ipc_obtain_object_check() can find it,
	 * and the lockless preparations क्रम ipc operations can start.
	 * This means especially: permission checks, audit calls, allocation
	 * of unकरो काष्ठाures, ...
	 *
	 * Thus the object must be fully initialized, and अगर something fails,
	 * then the full tear-करोwn sequence must be followed.
	 * (i.e.: set new->deleted, reduce refcount, call_rcu())
	 */

	अगर (next_id < 0) अणु /* !CHECKPOINT_RESTORE or next_id is unset */
		पूर्णांक max_idx;

		max_idx = max(ids->in_use*3/2, ipc_min_cycle);
		max_idx = min(max_idx, ipc_mni);

		/* allocate the idx, with a शून्य काष्ठा kern_ipc_perm */
		idx = idr_alloc_cyclic(&ids->ipcs_idr, शून्य, 0, max_idx,
					GFP_NOWAIT);

		अगर (idx >= 0) अणु
			/*
			 * idx got allocated successfully.
			 * Now calculate the sequence number and set the
			 * poपूर्णांकer क्रम real.
			 */
			अगर (idx <= ids->last_idx) अणु
				ids->seq++;
				अगर (ids->seq >= ipcid_seq_max())
					ids->seq = 0;
			पूर्ण
			ids->last_idx = idx;

			new->seq = ids->seq;
			/* no need क्रम smp_wmb(), this is करोne
			 * inside idr_replace, as part of
			 * rcu_assign_poपूर्णांकer
			 */
			idr_replace(&ids->ipcs_idr, new, idx);
		पूर्ण
	पूर्ण अन्यथा अणु
		new->seq = ipcid_to_seqx(next_id);
		idx = idr_alloc(&ids->ipcs_idr, new, ipcid_to_idx(next_id),
				0, GFP_NOWAIT);
	पूर्ण
	अगर (idx >= 0)
		new->id = (new->seq << ipcmni_seq_shअगरt()) + idx;
	वापस idx;
पूर्ण

/**
 * ipc_addid - add an ipc identअगरier
 * @ids: ipc identअगरier set
 * @new: new ipc permission set
 * @limit: limit क्रम the number of used ids
 *
 * Add an entry 'new' to the ipc ids idr. The permissions object is
 * initialised and the first मुक्त entry is set up and the index asचिन्हित
 * is वापसed. The 'new' entry is वापसed in a locked state on success.
 *
 * On failure the entry is not locked and a negative err-code is वापसed.
 * The caller must use ipc_rcu_putref() to मुक्त the identअगरier.
 *
 * Called with ग_लिखोr ipc_ids.rwsem held.
 */
पूर्णांक ipc_addid(काष्ठा ipc_ids *ids, काष्ठा kern_ipc_perm *new, पूर्णांक limit)
अणु
	kuid_t euid;
	kgid_t egid;
	पूर्णांक idx, err;

	/* 1) Initialize the refcount so that ipc_rcu_putref works */
	refcount_set(&new->refcount, 1);

	अगर (limit > ipc_mni)
		limit = ipc_mni;

	अगर (ids->in_use >= limit)
		वापस -ENOSPC;

	idr_preload(GFP_KERNEL);

	spin_lock_init(&new->lock);
	rcu_पढ़ो_lock();
	spin_lock(&new->lock);

	current_euid_egid(&euid, &egid);
	new->cuid = new->uid = euid;
	new->gid = new->cgid = egid;

	new->deleted = false;

	idx = ipc_idr_alloc(ids, new);
	idr_preload_end();

	अगर (idx >= 0 && new->key != IPC_PRIVATE) अणु
		err = rhashtable_insert_fast(&ids->key_ht, &new->khtnode,
					     ipc_kht_params);
		अगर (err < 0) अणु
			idr_हटाओ(&ids->ipcs_idr, idx);
			idx = err;
		पूर्ण
	पूर्ण
	अगर (idx < 0) अणु
		new->deleted = true;
		spin_unlock(&new->lock);
		rcu_पढ़ो_unlock();
		वापस idx;
	पूर्ण

	ids->in_use++;
	अगर (idx > ids->max_idx)
		ids->max_idx = idx;
	वापस idx;
पूर्ण

/**
 * ipcget_new -	create a new ipc object
 * @ns: ipc namespace
 * @ids: ipc identअगरier set
 * @ops: the actual creation routine to call
 * @params: its parameters
 *
 * This routine is called by sys_msgget, sys_semget() and sys_shmget()
 * when the key is IPC_PRIVATE.
 */
अटल पूर्णांक ipcget_new(काष्ठा ipc_namespace *ns, काष्ठा ipc_ids *ids,
		स्थिर काष्ठा ipc_ops *ops, काष्ठा ipc_params *params)
अणु
	पूर्णांक err;

	करोwn_ग_लिखो(&ids->rwsem);
	err = ops->getnew(ns, params);
	up_ग_लिखो(&ids->rwsem);
	वापस err;
पूर्ण

/**
 * ipc_check_perms - check security and permissions क्रम an ipc object
 * @ns: ipc namespace
 * @ipcp: ipc permission set
 * @ops: the actual security routine to call
 * @params: its parameters
 *
 * This routine is called by sys_msgget(), sys_semget() and sys_shmget()
 * when the key is not IPC_PRIVATE and that key alपढ़ोy exists in the
 * ds IDR.
 *
 * On success, the ipc id is वापसed.
 *
 * It is called with ipc_ids.rwsem and ipcp->lock held.
 */
अटल पूर्णांक ipc_check_perms(काष्ठा ipc_namespace *ns,
			   काष्ठा kern_ipc_perm *ipcp,
			   स्थिर काष्ठा ipc_ops *ops,
			   काष्ठा ipc_params *params)
अणु
	पूर्णांक err;

	अगर (ipcperms(ns, ipcp, params->flg))
		err = -EACCES;
	अन्यथा अणु
		err = ops->associate(ipcp, params->flg);
		अगर (!err)
			err = ipcp->id;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ipcget_खुला - get an ipc object or create a new one
 * @ns: ipc namespace
 * @ids: ipc identअगरier set
 * @ops: the actual creation routine to call
 * @params: its parameters
 *
 * This routine is called by sys_msgget, sys_semget() and sys_shmget()
 * when the key is not IPC_PRIVATE.
 * It adds a new entry अगर the key is not found and करोes some permission
 * / security checkings अगर the key is found.
 *
 * On success, the ipc id is वापसed.
 */
अटल पूर्णांक ipcget_खुला(काष्ठा ipc_namespace *ns, काष्ठा ipc_ids *ids,
		स्थिर काष्ठा ipc_ops *ops, काष्ठा ipc_params *params)
अणु
	काष्ठा kern_ipc_perm *ipcp;
	पूर्णांक flg = params->flg;
	पूर्णांक err;

	/*
	 * Take the lock as a ग_लिखोr since we are potentially going to add
	 * a new entry + पढ़ो locks are not "upgradable"
	 */
	करोwn_ग_लिखो(&ids->rwsem);
	ipcp = ipc_findkey(ids, params->key);
	अगर (ipcp == शून्य) अणु
		/* key not used */
		अगर (!(flg & IPC_CREAT))
			err = -ENOENT;
		अन्यथा
			err = ops->getnew(ns, params);
	पूर्ण अन्यथा अणु
		/* ipc object has been locked by ipc_findkey() */

		अगर (flg & IPC_CREAT && flg & IPC_EXCL)
			err = -EEXIST;
		अन्यथा अणु
			err = 0;
			अगर (ops->more_checks)
				err = ops->more_checks(ipcp, params);
			अगर (!err)
				/*
				 * ipc_check_perms वापसs the IPC id on
				 * success
				 */
				err = ipc_check_perms(ns, ipcp, ops, params);
		पूर्ण
		ipc_unlock(ipcp);
	पूर्ण
	up_ग_लिखो(&ids->rwsem);

	वापस err;
पूर्ण

/**
 * ipc_kht_हटाओ - हटाओ an ipc from the key hashtable
 * @ids: ipc identअगरier set
 * @ipcp: ipc perm काष्ठाure containing the key to हटाओ
 *
 * ipc_ids.rwsem (as a ग_लिखोr) and the spinlock क्रम this ID are held
 * beक्रमe this function is called, and reमुख्य locked on the निकास.
 */
अटल व्योम ipc_kht_हटाओ(काष्ठा ipc_ids *ids, काष्ठा kern_ipc_perm *ipcp)
अणु
	अगर (ipcp->key != IPC_PRIVATE)
		rhashtable_हटाओ_fast(&ids->key_ht, &ipcp->khtnode,
				       ipc_kht_params);
पूर्ण

/**
 * ipc_rmid - हटाओ an ipc identअगरier
 * @ids: ipc identअगरier set
 * @ipcp: ipc perm काष्ठाure containing the identअगरier to हटाओ
 *
 * ipc_ids.rwsem (as a ग_लिखोr) and the spinlock क्रम this ID are held
 * beक्रमe this function is called, and reमुख्य locked on the निकास.
 */
व्योम ipc_rmid(काष्ठा ipc_ids *ids, काष्ठा kern_ipc_perm *ipcp)
अणु
	पूर्णांक idx = ipcid_to_idx(ipcp->id);

	idr_हटाओ(&ids->ipcs_idr, idx);
	ipc_kht_हटाओ(ids, ipcp);
	ids->in_use--;
	ipcp->deleted = true;

	अगर (unlikely(idx == ids->max_idx)) अणु
		करो अणु
			idx--;
			अगर (idx == -1)
				अवरोध;
		पूर्ण जबतक (!idr_find(&ids->ipcs_idr, idx));
		ids->max_idx = idx;
	पूर्ण
पूर्ण

/**
 * ipc_set_key_निजी - चयन the key of an existing ipc to IPC_PRIVATE
 * @ids: ipc identअगरier set
 * @ipcp: ipc perm काष्ठाure containing the key to modअगरy
 *
 * ipc_ids.rwsem (as a ग_लिखोr) and the spinlock क्रम this ID are held
 * beक्रमe this function is called, and reमुख्य locked on the निकास.
 */
व्योम ipc_set_key_निजी(काष्ठा ipc_ids *ids, काष्ठा kern_ipc_perm *ipcp)
अणु
	ipc_kht_हटाओ(ids, ipcp);
	ipcp->key = IPC_PRIVATE;
पूर्ण

bool ipc_rcu_getref(काष्ठा kern_ipc_perm *ptr)
अणु
	वापस refcount_inc_not_zero(&ptr->refcount);
पूर्ण

व्योम ipc_rcu_putref(काष्ठा kern_ipc_perm *ptr,
			व्योम (*func)(काष्ठा rcu_head *head))
अणु
	अगर (!refcount_dec_and_test(&ptr->refcount))
		वापस;

	call_rcu(&ptr->rcu, func);
पूर्ण

/**
 * ipcperms - check ipc permissions
 * @ns: ipc namespace
 * @ipcp: ipc permission set
 * @flag: desired permission set
 *
 * Check user, group, other permissions क्रम access
 * to ipc resources. वापस 0 अगर allowed
 *
 * @flag will most probably be 0 or ``S_...UGO`` from <linux/स्थिति.स>
 */
पूर्णांक ipcperms(काष्ठा ipc_namespace *ns, काष्ठा kern_ipc_perm *ipcp, लघु flag)
अणु
	kuid_t euid = current_euid();
	पूर्णांक requested_mode, granted_mode;

	audit_ipc_obj(ipcp);
	requested_mode = (flag >> 6) | (flag >> 3) | flag;
	granted_mode = ipcp->mode;
	अगर (uid_eq(euid, ipcp->cuid) ||
	    uid_eq(euid, ipcp->uid))
		granted_mode >>= 6;
	अन्यथा अगर (in_group_p(ipcp->cgid) || in_group_p(ipcp->gid))
		granted_mode >>= 3;
	/* is there some bit set in requested_mode but not in granted_mode? */
	अगर ((requested_mode & ~granted_mode & 0007) &&
	    !ns_capable(ns->user_ns, CAP_IPC_OWNER))
		वापस -1;

	वापस security_ipc_permission(ipcp, flag);
पूर्ण

/*
 * Functions to convert between the kern_ipc_perm काष्ठाure and the
 * old/new ipc_perm काष्ठाures
 */

/**
 * kernel_to_ipc64_perm	- convert kernel ipc permissions to user
 * @in: kernel permissions
 * @out: new style ipc permissions
 *
 * Turn the kernel object @in पूर्णांकo a set of permissions descriptions
 * क्रम वापसing to userspace (@out).
 */
व्योम kernel_to_ipc64_perm(काष्ठा kern_ipc_perm *in, काष्ठा ipc64_perm *out)
अणु
	out->key	= in->key;
	out->uid	= from_kuid_munged(current_user_ns(), in->uid);
	out->gid	= from_kgid_munged(current_user_ns(), in->gid);
	out->cuid	= from_kuid_munged(current_user_ns(), in->cuid);
	out->cgid	= from_kgid_munged(current_user_ns(), in->cgid);
	out->mode	= in->mode;
	out->seq	= in->seq;
पूर्ण

/**
 * ipc64_perm_to_ipc_perm - convert new ipc permissions to old
 * @in: new style ipc permissions
 * @out: old style ipc permissions
 *
 * Turn the new style permissions object @in पूर्णांकo a compatibility
 * object and store it पूर्णांकo the @out poपूर्णांकer.
 */
व्योम ipc64_perm_to_ipc_perm(काष्ठा ipc64_perm *in, काष्ठा ipc_perm *out)
अणु
	out->key	= in->key;
	SET_UID(out->uid, in->uid);
	SET_GID(out->gid, in->gid);
	SET_UID(out->cuid, in->cuid);
	SET_GID(out->cgid, in->cgid);
	out->mode	= in->mode;
	out->seq	= in->seq;
पूर्ण

/**
 * ipc_obtain_object_idr
 * @ids: ipc identअगरier set
 * @id: ipc id to look क्रम
 *
 * Look क्रम an id in the ipc ids idr and वापस associated ipc object.
 *
 * Call inside the RCU critical section.
 * The ipc object is *not* locked on निकास.
 */
काष्ठा kern_ipc_perm *ipc_obtain_object_idr(काष्ठा ipc_ids *ids, पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *out;
	पूर्णांक idx = ipcid_to_idx(id);

	out = idr_find(&ids->ipcs_idr, idx);
	अगर (!out)
		वापस ERR_PTR(-EINVAL);

	वापस out;
पूर्ण

/**
 * ipc_obtain_object_check
 * @ids: ipc identअगरier set
 * @id: ipc id to look क्रम
 *
 * Similar to ipc_obtain_object_idr() but also checks the ipc object
 * sequence number.
 *
 * Call inside the RCU critical section.
 * The ipc object is *not* locked on निकास.
 */
काष्ठा kern_ipc_perm *ipc_obtain_object_check(काष्ठा ipc_ids *ids, पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *out = ipc_obtain_object_idr(ids, id);

	अगर (IS_ERR(out))
		जाओ out;

	अगर (ipc_checkid(out, id))
		वापस ERR_PTR(-EINVAL);
out:
	वापस out;
पूर्ण

/**
 * ipcget - Common sys_*get() code
 * @ns: namespace
 * @ids: ipc identअगरier set
 * @ops: operations to be called on ipc object creation, permission checks
 *       and further checks
 * @params: the parameters needed by the previous operations.
 *
 * Common routine called by sys_msgget(), sys_semget() and sys_shmget().
 */
पूर्णांक ipcget(काष्ठा ipc_namespace *ns, काष्ठा ipc_ids *ids,
			स्थिर काष्ठा ipc_ops *ops, काष्ठा ipc_params *params)
अणु
	अगर (params->key == IPC_PRIVATE)
		वापस ipcget_new(ns, ids, ops, params);
	अन्यथा
		वापस ipcget_खुला(ns, ids, ops, params);
पूर्ण

/**
 * ipc_update_perm - update the permissions of an ipc object
 * @in:  the permission given as input.
 * @out: the permission of the ipc to set.
 */
पूर्णांक ipc_update_perm(काष्ठा ipc64_perm *in, काष्ठा kern_ipc_perm *out)
अणु
	kuid_t uid = make_kuid(current_user_ns(), in->uid);
	kgid_t gid = make_kgid(current_user_ns(), in->gid);
	अगर (!uid_valid(uid) || !gid_valid(gid))
		वापस -EINVAL;

	out->uid = uid;
	out->gid = gid;
	out->mode = (out->mode & ~S_IRWXUGO)
		| (in->mode & S_IRWXUGO);

	वापस 0;
पूर्ण

/**
 * ipcctl_obtain_check - retrieve an ipc object and check permissions
 * @ns:  ipc namespace
 * @ids:  the table of ids where to look क्रम the ipc
 * @id:   the id of the ipc to retrieve
 * @cmd:  the cmd to check
 * @perm: the permission to set
 * @extra_perm: one extra permission parameter used by msq
 *
 * This function करोes some common audit and permissions check क्रम some IPC_XXX
 * cmd and is called from semctl_करोwn, shmctl_करोwn and msgctl_करोwn.
 *
 * It:
 *   - retrieves the ipc object with the given id in the given table.
 *   - perक्रमms some audit and permission check, depending on the given cmd
 *   - वापसs a poपूर्णांकer to the ipc object or otherwise, the corresponding
 *     error.
 *
 * Call holding the both the rwsem and the rcu पढ़ो lock.
 */
काष्ठा kern_ipc_perm *ipcctl_obtain_check(काष्ठा ipc_namespace *ns,
					काष्ठा ipc_ids *ids, पूर्णांक id, पूर्णांक cmd,
					काष्ठा ipc64_perm *perm, पूर्णांक extra_perm)
अणु
	kuid_t euid;
	पूर्णांक err = -EPERM;
	काष्ठा kern_ipc_perm *ipcp;

	ipcp = ipc_obtain_object_check(ids, id);
	अगर (IS_ERR(ipcp)) अणु
		err = PTR_ERR(ipcp);
		जाओ err;
	पूर्ण

	audit_ipc_obj(ipcp);
	अगर (cmd == IPC_SET)
		audit_ipc_set_perm(extra_perm, perm->uid,
				   perm->gid, perm->mode);

	euid = current_euid();
	अगर (uid_eq(euid, ipcp->cuid) || uid_eq(euid, ipcp->uid)  ||
	    ns_capable(ns->user_ns, CAP_SYS_ADMIN))
		वापस ipcp; /* successful lookup */
err:
	वापस ERR_PTR(err);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_IPC_PARSE_VERSION


/**
 * ipc_parse_version - ipc call version
 * @cmd: poपूर्णांकer to command
 *
 * Return IPC_64 क्रम new style IPC and IPC_OLD क्रम old style IPC.
 * The @cmd value is turned from an encoding command and version पूर्णांकo
 * just the command code.
 */
पूर्णांक ipc_parse_version(पूर्णांक *cmd)
अणु
	अगर (*cmd & IPC_64) अणु
		*cmd ^= IPC_64;
		वापस IPC_64;
	पूर्ण अन्यथा अणु
		वापस IPC_OLD;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_ARCH_WANT_IPC_PARSE_VERSION */

#अगर_घोषित CONFIG_PROC_FS
काष्ठा ipc_proc_iter अणु
	काष्ठा ipc_namespace *ns;
	काष्ठा pid_namespace *pid_ns;
	काष्ठा ipc_proc_अगरace *अगरace;
पूर्ण;

काष्ठा pid_namespace *ipc_seq_pid_ns(काष्ठा seq_file *s)
अणु
	काष्ठा ipc_proc_iter *iter = s->निजी;
	वापस iter->pid_ns;
पूर्ण

/*
 * This routine locks the ipc काष्ठाure found at least at position pos.
 */
अटल काष्ठा kern_ipc_perm *sysvipc_find_ipc(काष्ठा ipc_ids *ids, loff_t pos,
					      loff_t *new_pos)
अणु
	काष्ठा kern_ipc_perm *ipc;
	पूर्णांक total, id;

	total = 0;
	क्रम (id = 0; id < pos && total < ids->in_use; id++) अणु
		ipc = idr_find(&ids->ipcs_idr, id);
		अगर (ipc != शून्य)
			total++;
	पूर्ण

	ipc = शून्य;
	अगर (total >= ids->in_use)
		जाओ out;

	क्रम (; pos < ipc_mni; pos++) अणु
		ipc = idr_find(&ids->ipcs_idr, pos);
		अगर (ipc != शून्य) अणु
			rcu_पढ़ो_lock();
			ipc_lock_object(ipc);
			अवरोध;
		पूर्ण
	पूर्ण
out:
	*new_pos = pos + 1;
	वापस ipc;
पूर्ण

अटल व्योम *sysvipc_proc_next(काष्ठा seq_file *s, व्योम *it, loff_t *pos)
अणु
	काष्ठा ipc_proc_iter *iter = s->निजी;
	काष्ठा ipc_proc_अगरace *अगरace = iter->अगरace;
	काष्ठा kern_ipc_perm *ipc = it;

	/* If we had an ipc id locked beक्रमe, unlock it */
	अगर (ipc && ipc != SEQ_START_TOKEN)
		ipc_unlock(ipc);

	वापस sysvipc_find_ipc(&iter->ns->ids[अगरace->ids], *pos, pos);
पूर्ण

/*
 * File positions: pos 0 -> header, pos n -> ipc id = n - 1.
 * SeqFile iterator: iterator value locked ipc poपूर्णांकer or SEQ_TOKEN_START.
 */
अटल व्योम *sysvipc_proc_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा ipc_proc_iter *iter = s->निजी;
	काष्ठा ipc_proc_अगरace *अगरace = iter->अगरace;
	काष्ठा ipc_ids *ids;

	ids = &iter->ns->ids[अगरace->ids];

	/*
	 * Take the lock - this will be released by the corresponding
	 * call to stop().
	 */
	करोwn_पढ़ो(&ids->rwsem);

	/* pos < 0 is invalid */
	अगर (*pos < 0)
		वापस शून्य;

	/* pos == 0 means header */
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	/* Find the (pos-1)th ipc */
	वापस sysvipc_find_ipc(ids, *pos - 1, pos);
पूर्ण

अटल व्योम sysvipc_proc_stop(काष्ठा seq_file *s, व्योम *it)
अणु
	काष्ठा kern_ipc_perm *ipc = it;
	काष्ठा ipc_proc_iter *iter = s->निजी;
	काष्ठा ipc_proc_अगरace *अगरace = iter->अगरace;
	काष्ठा ipc_ids *ids;

	/* If we had a locked काष्ठाure, release it */
	अगर (ipc && ipc != SEQ_START_TOKEN)
		ipc_unlock(ipc);

	ids = &iter->ns->ids[अगरace->ids];
	/* Release the lock we took in start() */
	up_पढ़ो(&ids->rwsem);
पूर्ण

अटल पूर्णांक sysvipc_proc_show(काष्ठा seq_file *s, व्योम *it)
अणु
	काष्ठा ipc_proc_iter *iter = s->निजी;
	काष्ठा ipc_proc_अगरace *अगरace = iter->अगरace;

	अगर (it == SEQ_START_TOKEN) अणु
		seq_माला_दो(s, अगरace->header);
		वापस 0;
	पूर्ण

	वापस अगरace->show(s, it);
पूर्ण

अटल स्थिर काष्ठा seq_operations sysvipc_proc_seqops = अणु
	.start = sysvipc_proc_start,
	.stop  = sysvipc_proc_stop,
	.next  = sysvipc_proc_next,
	.show  = sysvipc_proc_show,
पूर्ण;

अटल पूर्णांक sysvipc_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ipc_proc_iter *iter;

	iter = __seq_खोलो_निजी(file, &sysvipc_proc_seqops, माप(*iter));
	अगर (!iter)
		वापस -ENOMEM;

	iter->अगरace = PDE_DATA(inode);
	iter->ns    = get_ipc_ns(current->nsproxy->ipc_ns);
	iter->pid_ns = get_pid_ns(task_active_pid_ns(current));

	वापस 0;
पूर्ण

अटल पूर्णांक sysvipc_proc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा ipc_proc_iter *iter = seq->निजी;
	put_ipc_ns(iter->ns);
	put_pid_ns(iter->pid_ns);
	वापस seq_release_निजी(inode, file);
पूर्ण

अटल स्थिर काष्ठा proc_ops sysvipc_proc_ops = अणु
	.proc_flags	= PROC_ENTRY_PERMANENT,
	.proc_खोलो	= sysvipc_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= sysvipc_proc_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */
