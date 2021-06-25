<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
*******************************************************************************
**
**  Copyright (C) Sistina Software, Inc.  1997-2003  All rights reserved.
**  Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
**
**
*******************************************************************************
******************************************************************************/

#समावेश <linux/module.h>

#समावेश "dlm_internal.h"
#समावेश "lockspace.h"
#समावेश "member.h"
#समावेश "recoverd.h"
#समावेश "dir.h"
#समावेश "lowcomms.h"
#समावेश "config.h"
#समावेश "memory.h"
#समावेश "lock.h"
#समावेश "recover.h"
#समावेश "requestqueue.h"
#समावेश "user.h"
#समावेश "ast.h"

अटल पूर्णांक			ls_count;
अटल काष्ठा mutex		ls_lock;
अटल काष्ठा list_head		lslist;
अटल spinlock_t		lslist_lock;
अटल काष्ठा task_काष्ठा *	scand_task;


अटल sमाप_प्रकार dlm_control_store(काष्ठा dlm_ls *ls, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	sमाप_प्रकार ret = len;
	पूर्णांक n;
	पूर्णांक rc = kstrtoपूर्णांक(buf, 0, &n);

	अगर (rc)
		वापस rc;
	ls = dlm_find_lockspace_local(ls->ls_local_handle);
	अगर (!ls)
		वापस -EINVAL;

	चयन (n) अणु
	हाल 0:
		dlm_ls_stop(ls);
		अवरोध;
	हाल 1:
		dlm_ls_start(ls);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	dlm_put_lockspace(ls);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार dlm_event_store(काष्ठा dlm_ls *ls, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक rc = kstrtoपूर्णांक(buf, 0, &ls->ls_uevent_result);

	अगर (rc)
		वापस rc;
	set_bit(LSFL_UEVENT_WAIT, &ls->ls_flags);
	wake_up(&ls->ls_uevent_रुको);
	वापस len;
पूर्ण

अटल sमाप_प्रकार dlm_id_show(काष्ठा dlm_ls *ls, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", ls->ls_global_id);
पूर्ण

अटल sमाप_प्रकार dlm_id_store(काष्ठा dlm_ls *ls, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक rc = kstrtouपूर्णांक(buf, 0, &ls->ls_global_id);

	अगर (rc)
		वापस rc;
	वापस len;
पूर्ण

अटल sमाप_प्रकार dlm_nodir_show(काष्ठा dlm_ls *ls, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", dlm_no_directory(ls));
पूर्ण

अटल sमाप_प्रकार dlm_nodir_store(काष्ठा dlm_ls *ls, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक val;
	पूर्णांक rc = kstrtoपूर्णांक(buf, 0, &val);

	अगर (rc)
		वापस rc;
	अगर (val == 1)
		set_bit(LSFL_NOसूची, &ls->ls_flags);
	वापस len;
पूर्ण

अटल sमाप_प्रकार dlm_recover_status_show(काष्ठा dlm_ls *ls, अक्षर *buf)
अणु
	uपूर्णांक32_t status = dlm_recover_status(ls);
	वापस snम_लिखो(buf, PAGE_SIZE, "%x\n", status);
पूर्ण

अटल sमाप_प्रकार dlm_recover_nodeid_show(काष्ठा dlm_ls *ls, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", ls->ls_recover_nodeid);
पूर्ण

काष्ठा dlm_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा dlm_ls *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा dlm_ls *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल काष्ठा dlm_attr dlm_attr_control = अणु
	.attr  = अणु.name = "control", .mode = S_IWUSRपूर्ण,
	.store = dlm_control_store
पूर्ण;

अटल काष्ठा dlm_attr dlm_attr_event = अणु
	.attr  = अणु.name = "event_done", .mode = S_IWUSRपूर्ण,
	.store = dlm_event_store
पूर्ण;

अटल काष्ठा dlm_attr dlm_attr_id = अणु
	.attr  = अणु.name = "id", .mode = S_IRUGO | S_IWUSRपूर्ण,
	.show  = dlm_id_show,
	.store = dlm_id_store
पूर्ण;

अटल काष्ठा dlm_attr dlm_attr_nodir = अणु
	.attr  = अणु.name = "nodir", .mode = S_IRUGO | S_IWUSRपूर्ण,
	.show  = dlm_nodir_show,
	.store = dlm_nodir_store
पूर्ण;

अटल काष्ठा dlm_attr dlm_attr_recover_status = अणु
	.attr  = अणु.name = "recover_status", .mode = S_IRUGOपूर्ण,
	.show  = dlm_recover_status_show
पूर्ण;

अटल काष्ठा dlm_attr dlm_attr_recover_nodeid = अणु
	.attr  = अणु.name = "recover_nodeid", .mode = S_IRUGOपूर्ण,
	.show  = dlm_recover_nodeid_show
पूर्ण;

अटल काष्ठा attribute *dlm_attrs[] = अणु
	&dlm_attr_control.attr,
	&dlm_attr_event.attr,
	&dlm_attr_id.attr,
	&dlm_attr_nodir.attr,
	&dlm_attr_recover_status.attr,
	&dlm_attr_recover_nodeid.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(dlm);

अटल sमाप_प्रकार dlm_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा dlm_ls *ls  = container_of(kobj, काष्ठा dlm_ls, ls_kobj);
	काष्ठा dlm_attr *a = container_of(attr, काष्ठा dlm_attr, attr);
	वापस a->show ? a->show(ls, buf) : 0;
पूर्ण

अटल sमाप_प्रकार dlm_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dlm_ls *ls  = container_of(kobj, काष्ठा dlm_ls, ls_kobj);
	काष्ठा dlm_attr *a = container_of(attr, काष्ठा dlm_attr, attr);
	वापस a->store ? a->store(ls, buf, len) : len;
पूर्ण

अटल व्योम lockspace_kobj_release(काष्ठा kobject *k)
अणु
	काष्ठा dlm_ls *ls  = container_of(k, काष्ठा dlm_ls, ls_kobj);
	kमुक्त(ls);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops dlm_attr_ops = अणु
	.show  = dlm_attr_show,
	.store = dlm_attr_store,
पूर्ण;

अटल काष्ठा kobj_type dlm_ktype = अणु
	.शेष_groups = dlm_groups,
	.sysfs_ops     = &dlm_attr_ops,
	.release       = lockspace_kobj_release,
पूर्ण;

अटल काष्ठा kset *dlm_kset;

अटल पूर्णांक करो_uevent(काष्ठा dlm_ls *ls, पूर्णांक in)
अणु
	अगर (in)
		kobject_uevent(&ls->ls_kobj, KOBJ_ONLINE);
	अन्यथा
		kobject_uevent(&ls->ls_kobj, KOBJ_OFFLINE);

	log_rinfo(ls, "%s the lockspace group...", in ? "joining" : "leaving");

	/* dlm_controld will see the uevent, करो the necessary group management
	   and then ग_लिखो to sysfs to wake us */

	रुको_event(ls->ls_uevent_रुको,
		   test_and_clear_bit(LSFL_UEVENT_WAIT, &ls->ls_flags));

	log_rinfo(ls, "group event done %d", ls->ls_uevent_result);

	वापस ls->ls_uevent_result;
पूर्ण

अटल पूर्णांक dlm_uevent(काष्ठा kset *kset, काष्ठा kobject *kobj,
		      काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा dlm_ls *ls = container_of(kobj, काष्ठा dlm_ls, ls_kobj);

	add_uevent_var(env, "LOCKSPACE=%s", ls->ls_name);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kset_uevent_ops dlm_uevent_ops = अणु
	.uevent = dlm_uevent,
पूर्ण;

पूर्णांक __init dlm_lockspace_init(व्योम)
अणु
	ls_count = 0;
	mutex_init(&ls_lock);
	INIT_LIST_HEAD(&lslist);
	spin_lock_init(&lslist_lock);

	dlm_kset = kset_create_and_add("dlm", &dlm_uevent_ops, kernel_kobj);
	अगर (!dlm_kset) अणु
		prपूर्णांकk(KERN_WARNING "%s: can not create kset\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम dlm_lockspace_निकास(व्योम)
अणु
	kset_unरेजिस्टर(dlm_kset);
पूर्ण

अटल काष्ठा dlm_ls *find_ls_to_scan(व्योम)
अणु
	काष्ठा dlm_ls *ls;

	spin_lock(&lslist_lock);
	list_क्रम_each_entry(ls, &lslist, ls_list) अणु
		अगर (समय_after_eq(jअगरfies, ls->ls_scan_समय +
					    dlm_config.ci_scan_secs * HZ)) अणु
			spin_unlock(&lslist_lock);
			वापस ls;
		पूर्ण
	पूर्ण
	spin_unlock(&lslist_lock);
	वापस शून्य;
पूर्ण

अटल पूर्णांक dlm_scand(व्योम *data)
अणु
	काष्ठा dlm_ls *ls;

	जबतक (!kthपढ़ो_should_stop()) अणु
		ls = find_ls_to_scan();
		अगर (ls) अणु
			अगर (dlm_lock_recovery_try(ls)) अणु
				ls->ls_scan_समय = jअगरfies;
				dlm_scan_rsbs(ls);
				dlm_scan_समयout(ls);
				dlm_scan_रुकोers(ls);
				dlm_unlock_recovery(ls);
			पूर्ण अन्यथा अणु
				ls->ls_scan_समय += HZ;
			पूर्ण
			जारी;
		पूर्ण
		schedule_समयout_पूर्णांकerruptible(dlm_config.ci_scan_secs * HZ);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dlm_scand_start(व्योम)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक error = 0;

	p = kthपढ़ो_run(dlm_scand, शून्य, "dlm_scand");
	अगर (IS_ERR(p))
		error = PTR_ERR(p);
	अन्यथा
		scand_task = p;
	वापस error;
पूर्ण

अटल व्योम dlm_scand_stop(व्योम)
अणु
	kthपढ़ो_stop(scand_task);
पूर्ण

काष्ठा dlm_ls *dlm_find_lockspace_global(uपूर्णांक32_t id)
अणु
	काष्ठा dlm_ls *ls;

	spin_lock(&lslist_lock);

	list_क्रम_each_entry(ls, &lslist, ls_list) अणु
		अगर (ls->ls_global_id == id) अणु
			ls->ls_count++;
			जाओ out;
		पूर्ण
	पूर्ण
	ls = शून्य;
 out:
	spin_unlock(&lslist_lock);
	वापस ls;
पूर्ण

काष्ठा dlm_ls *dlm_find_lockspace_local(dlm_lockspace_t *lockspace)
अणु
	काष्ठा dlm_ls *ls;

	spin_lock(&lslist_lock);
	list_क्रम_each_entry(ls, &lslist, ls_list) अणु
		अगर (ls->ls_local_handle == lockspace) अणु
			ls->ls_count++;
			जाओ out;
		पूर्ण
	पूर्ण
	ls = शून्य;
 out:
	spin_unlock(&lslist_lock);
	वापस ls;
पूर्ण

काष्ठा dlm_ls *dlm_find_lockspace_device(पूर्णांक minor)
अणु
	काष्ठा dlm_ls *ls;

	spin_lock(&lslist_lock);
	list_क्रम_each_entry(ls, &lslist, ls_list) अणु
		अगर (ls->ls_device.minor == minor) अणु
			ls->ls_count++;
			जाओ out;
		पूर्ण
	पूर्ण
	ls = शून्य;
 out:
	spin_unlock(&lslist_lock);
	वापस ls;
पूर्ण

व्योम dlm_put_lockspace(काष्ठा dlm_ls *ls)
अणु
	spin_lock(&lslist_lock);
	ls->ls_count--;
	spin_unlock(&lslist_lock);
पूर्ण

अटल व्योम हटाओ_lockspace(काष्ठा dlm_ls *ls)
अणु
	क्रम (;;) अणु
		spin_lock(&lslist_lock);
		अगर (ls->ls_count == 0) अणु
			WARN_ON(ls->ls_create_count != 0);
			list_del(&ls->ls_list);
			spin_unlock(&lslist_lock);
			वापस;
		पूर्ण
		spin_unlock(&lslist_lock);
		ssleep(1);
	पूर्ण
पूर्ण

अटल पूर्णांक thपढ़ोs_start(व्योम)
अणु
	पूर्णांक error;

	error = dlm_scand_start();
	अगर (error) अणु
		log_prपूर्णांक("cannot start dlm_scand thread %d", error);
		जाओ fail;
	पूर्ण

	/* Thपढ़ो क्रम sending/receiving messages क्रम all lockspace's */
	error = dlm_lowcomms_start();
	अगर (error) अणु
		log_prपूर्णांक("cannot start dlm lowcomms %d", error);
		जाओ scand_fail;
	पूर्ण

	वापस 0;

 scand_fail:
	dlm_scand_stop();
 fail:
	वापस error;
पूर्ण

अटल पूर्णांक new_lockspace(स्थिर अक्षर *name, स्थिर अक्षर *cluster,
			 uपूर्णांक32_t flags, पूर्णांक lvblen,
			 स्थिर काष्ठा dlm_lockspace_ops *ops, व्योम *ops_arg,
			 पूर्णांक *ops_result, dlm_lockspace_t **lockspace)
अणु
	काष्ठा dlm_ls *ls;
	पूर्णांक i, size, error;
	पूर्णांक करो_unreg = 0;
	पूर्णांक namelen = म_माप(name);

	अगर (namelen > DLM_LOCKSPACE_LEN || namelen == 0)
		वापस -EINVAL;

	अगर (!lvblen || (lvblen % 8))
		वापस -EINVAL;

	अगर (!try_module_get(THIS_MODULE))
		वापस -EINVAL;

	अगर (!dlm_user_daemon_available()) अणु
		log_prपूर्णांक("dlm user daemon not available");
		error = -EUNATCH;
		जाओ out;
	पूर्ण

	अगर (ops && ops_result) अणु
	       	अगर (!dlm_config.ci_recover_callbacks)
			*ops_result = -EOPNOTSUPP;
		अन्यथा
			*ops_result = 0;
	पूर्ण

	अगर (!cluster)
		log_prपूर्णांक("dlm cluster name '%s' is being used without an application provided cluster name",
			  dlm_config.ci_cluster_name);

	अगर (dlm_config.ci_recover_callbacks && cluster &&
	    म_भेदन(cluster, dlm_config.ci_cluster_name, DLM_LOCKSPACE_LEN)) अणु
		log_prपूर्णांक("dlm cluster name '%s' does not match "
			  "the application cluster name '%s'",
			  dlm_config.ci_cluster_name, cluster);
		error = -EBADR;
		जाओ out;
	पूर्ण

	error = 0;

	spin_lock(&lslist_lock);
	list_क्रम_each_entry(ls, &lslist, ls_list) अणु
		WARN_ON(ls->ls_create_count <= 0);
		अगर (ls->ls_namelen != namelen)
			जारी;
		अगर (स_भेद(ls->ls_name, name, namelen))
			जारी;
		अगर (flags & DLM_LSFL_NEWEXCL) अणु
			error = -EEXIST;
			अवरोध;
		पूर्ण
		ls->ls_create_count++;
		*lockspace = ls;
		error = 1;
		अवरोध;
	पूर्ण
	spin_unlock(&lslist_lock);

	अगर (error)
		जाओ out;

	error = -ENOMEM;

	ls = kzalloc(माप(काष्ठा dlm_ls) + namelen, GFP_NOFS);
	अगर (!ls)
		जाओ out;
	स_नकल(ls->ls_name, name, namelen);
	ls->ls_namelen = namelen;
	ls->ls_lvblen = lvblen;
	ls->ls_count = 0;
	ls->ls_flags = 0;
	ls->ls_scan_समय = jअगरfies;

	अगर (ops && dlm_config.ci_recover_callbacks) अणु
		ls->ls_ops = ops;
		ls->ls_ops_arg = ops_arg;
	पूर्ण

	अगर (flags & DLM_LSFL_TIMEWARN)
		set_bit(LSFL_TIMEWARN, &ls->ls_flags);

	/* ls_exflags are क्रमced to match among nodes, and we करोn't
	   need to require all nodes to have some flags set */
	ls->ls_exflags = (flags & ~(DLM_LSFL_TIMEWARN | DLM_LSFL_FS |
				    DLM_LSFL_NEWEXCL));

	size = dlm_config.ci_rsbtbl_size;
	ls->ls_rsbtbl_size = size;

	ls->ls_rsbtbl = vदो_स्मृति(array_size(size, माप(काष्ठा dlm_rsbtable)));
	अगर (!ls->ls_rsbtbl)
		जाओ out_lsमुक्त;
	क्रम (i = 0; i < size; i++) अणु
		ls->ls_rsbtbl[i].keep.rb_node = शून्य;
		ls->ls_rsbtbl[i].toss.rb_node = शून्य;
		spin_lock_init(&ls->ls_rsbtbl[i].lock);
	पूर्ण

	spin_lock_init(&ls->ls_हटाओ_spin);

	क्रम (i = 0; i < DLM_REMOVE_NAMES_MAX; i++) अणु
		ls->ls_हटाओ_names[i] = kzalloc(DLM_RESNAME_MAXLEN+1,
						 GFP_KERNEL);
		अगर (!ls->ls_हटाओ_names[i])
			जाओ out_rsbtbl;
	पूर्ण

	idr_init(&ls->ls_lkbidr);
	spin_lock_init(&ls->ls_lkbidr_spin);

	INIT_LIST_HEAD(&ls->ls_रुकोers);
	mutex_init(&ls->ls_रुकोers_mutex);
	INIT_LIST_HEAD(&ls->ls_orphans);
	mutex_init(&ls->ls_orphans_mutex);
	INIT_LIST_HEAD(&ls->ls_समयout);
	mutex_init(&ls->ls_समयout_mutex);

	INIT_LIST_HEAD(&ls->ls_new_rsb);
	spin_lock_init(&ls->ls_new_rsb_spin);

	INIT_LIST_HEAD(&ls->ls_nodes);
	INIT_LIST_HEAD(&ls->ls_nodes_gone);
	ls->ls_num_nodes = 0;
	ls->ls_low_nodeid = 0;
	ls->ls_total_weight = 0;
	ls->ls_node_array = शून्य;

	स_रखो(&ls->ls_stub_rsb, 0, माप(काष्ठा dlm_rsb));
	ls->ls_stub_rsb.res_ls = ls;

	ls->ls_debug_rsb_dentry = शून्य;
	ls->ls_debug_रुकोers_dentry = शून्य;

	init_रुकोqueue_head(&ls->ls_uevent_रुको);
	ls->ls_uevent_result = 0;
	init_completion(&ls->ls_members_करोne);
	ls->ls_members_result = -1;

	mutex_init(&ls->ls_cb_mutex);
	INIT_LIST_HEAD(&ls->ls_cb_delay);

	ls->ls_recoverd_task = शून्य;
	mutex_init(&ls->ls_recoverd_active);
	spin_lock_init(&ls->ls_recover_lock);
	spin_lock_init(&ls->ls_rcom_spin);
	get_अक्रमom_bytes(&ls->ls_rcom_seq, माप(uपूर्णांक64_t));
	ls->ls_recover_status = 0;
	ls->ls_recover_seq = 0;
	ls->ls_recover_args = शून्य;
	init_rwsem(&ls->ls_in_recovery);
	init_rwsem(&ls->ls_recv_active);
	INIT_LIST_HEAD(&ls->ls_requestqueue);
	mutex_init(&ls->ls_requestqueue_mutex);
	mutex_init(&ls->ls_clear_proc_locks);

	ls->ls_recover_buf = kदो_स्मृति(LOWCOMMS_MAX_TX_BUFFER_LEN, GFP_NOFS);
	अगर (!ls->ls_recover_buf)
		जाओ out_lkbidr;

	ls->ls_slot = 0;
	ls->ls_num_slots = 0;
	ls->ls_slots_size = 0;
	ls->ls_slots = शून्य;

	INIT_LIST_HEAD(&ls->ls_recover_list);
	spin_lock_init(&ls->ls_recover_list_lock);
	idr_init(&ls->ls_recover_idr);
	spin_lock_init(&ls->ls_recover_idr_lock);
	ls->ls_recover_list_count = 0;
	ls->ls_local_handle = ls;
	init_रुकोqueue_head(&ls->ls_रुको_general);
	INIT_LIST_HEAD(&ls->ls_root_list);
	init_rwsem(&ls->ls_root_sem);

	spin_lock(&lslist_lock);
	ls->ls_create_count = 1;
	list_add(&ls->ls_list, &lslist);
	spin_unlock(&lslist_lock);

	अगर (flags & DLM_LSFL_FS) अणु
		error = dlm_callback_start(ls);
		अगर (error) अणु
			log_error(ls, "can't start dlm_callback %d", error);
			जाओ out_delist;
		पूर्ण
	पूर्ण

	init_रुकोqueue_head(&ls->ls_recover_lock_रुको);

	/*
	 * Once started, dlm_recoverd first looks क्रम ls in lslist, then
	 * initializes ls_in_recovery as locked in "down" mode.  We need
	 * to रुको क्रम the wakeup from dlm_recoverd because in_recovery
	 * has to start out in करोwn mode.
	 */

	error = dlm_recoverd_start(ls);
	अगर (error) अणु
		log_error(ls, "can't start dlm_recoverd %d", error);
		जाओ out_callback;
	पूर्ण

	रुको_event(ls->ls_recover_lock_रुको,
		   test_bit(LSFL_RECOVER_LOCK, &ls->ls_flags));

	/* let kobject handle मुक्तing of ls अगर there's an error */
	करो_unreg = 1;

	ls->ls_kobj.kset = dlm_kset;
	error = kobject_init_and_add(&ls->ls_kobj, &dlm_ktype, शून्य,
				     "%s", ls->ls_name);
	अगर (error)
		जाओ out_recoverd;
	kobject_uevent(&ls->ls_kobj, KOBJ_ADD);

	/* This uevent triggers dlm_controld in userspace to add us to the
	   group of nodes that are members of this lockspace (managed by the
	   cluster infraकाष्ठाure.)  Once it's करोne that, it tells us who the
	   current lockspace members are (via configfs) and then tells the
	   lockspace to start running (via sysfs) in dlm_ls_start(). */

	error = करो_uevent(ls, 1);
	अगर (error)
		जाओ out_recoverd;

	रुको_क्रम_completion(&ls->ls_members_करोne);
	error = ls->ls_members_result;
	अगर (error)
		जाओ out_members;

	dlm_create_debug_file(ls);

	log_rinfo(ls, "join complete");
	*lockspace = ls;
	वापस 0;

 out_members:
	करो_uevent(ls, 0);
	dlm_clear_members(ls);
	kमुक्त(ls->ls_node_array);
 out_recoverd:
	dlm_recoverd_stop(ls);
 out_callback:
	dlm_callback_stop(ls);
 out_delist:
	spin_lock(&lslist_lock);
	list_del(&ls->ls_list);
	spin_unlock(&lslist_lock);
	idr_destroy(&ls->ls_recover_idr);
	kमुक्त(ls->ls_recover_buf);
 out_lkbidr:
	idr_destroy(&ls->ls_lkbidr);
 out_rsbtbl:
	क्रम (i = 0; i < DLM_REMOVE_NAMES_MAX; i++)
		kमुक्त(ls->ls_हटाओ_names[i]);
	vमुक्त(ls->ls_rsbtbl);
 out_lsमुक्त:
	अगर (करो_unreg)
		kobject_put(&ls->ls_kobj);
	अन्यथा
		kमुक्त(ls);
 out:
	module_put(THIS_MODULE);
	वापस error;
पूर्ण

पूर्णांक dlm_new_lockspace(स्थिर अक्षर *name, स्थिर अक्षर *cluster,
		      uपूर्णांक32_t flags, पूर्णांक lvblen,
		      स्थिर काष्ठा dlm_lockspace_ops *ops, व्योम *ops_arg,
		      पूर्णांक *ops_result, dlm_lockspace_t **lockspace)
अणु
	पूर्णांक error = 0;

	mutex_lock(&ls_lock);
	अगर (!ls_count)
		error = thपढ़ोs_start();
	अगर (error)
		जाओ out;

	error = new_lockspace(name, cluster, flags, lvblen, ops, ops_arg,
			      ops_result, lockspace);
	अगर (!error)
		ls_count++;
	अगर (error > 0)
		error = 0;
	अगर (!ls_count) अणु
		dlm_scand_stop();
		dlm_lowcomms_shutकरोwn();
		dlm_lowcomms_stop();
	पूर्ण
 out:
	mutex_unlock(&ls_lock);
	वापस error;
पूर्ण

अटल पूर्णांक lkb_idr_is_local(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा dlm_lkb *lkb = p;

	वापस lkb->lkb_nodeid == 0 && lkb->lkb_grmode != DLM_LOCK_IV;
पूर्ण

अटल पूर्णांक lkb_idr_is_any(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक lkb_idr_मुक्त(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा dlm_lkb *lkb = p;

	अगर (lkb->lkb_lvbptr && lkb->lkb_flags & DLM_IFL_MSTCPY)
		dlm_मुक्त_lvb(lkb->lkb_lvbptr);

	dlm_मुक्त_lkb(lkb);
	वापस 0;
पूर्ण

/* NOTE: We check the lkbidr here rather than the resource table.
   This is because there may be LKBs queued as ASTs that have been unlinked
   from their RSBs and are pending deletion once the AST has been delivered */

अटल पूर्णांक lockspace_busy(काष्ठा dlm_ls *ls, पूर्णांक क्रमce)
अणु
	पूर्णांक rv;

	spin_lock(&ls->ls_lkbidr_spin);
	अगर (क्रमce == 0) अणु
		rv = idr_क्रम_each(&ls->ls_lkbidr, lkb_idr_is_any, ls);
	पूर्ण अन्यथा अगर (क्रमce == 1) अणु
		rv = idr_क्रम_each(&ls->ls_lkbidr, lkb_idr_is_local, ls);
	पूर्ण अन्यथा अणु
		rv = 0;
	पूर्ण
	spin_unlock(&ls->ls_lkbidr_spin);
	वापस rv;
पूर्ण

अटल पूर्णांक release_lockspace(काष्ठा dlm_ls *ls, पूर्णांक क्रमce)
अणु
	काष्ठा dlm_rsb *rsb;
	काष्ठा rb_node *n;
	पूर्णांक i, busy, rv;

	busy = lockspace_busy(ls, क्रमce);

	spin_lock(&lslist_lock);
	अगर (ls->ls_create_count == 1) अणु
		अगर (busy) अणु
			rv = -EBUSY;
		पूर्ण अन्यथा अणु
			/* हटाओ_lockspace takes ls off lslist */
			ls->ls_create_count = 0;
			rv = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (ls->ls_create_count > 1) अणु
		rv = --ls->ls_create_count;
	पूर्ण अन्यथा अणु
		rv = -EINVAL;
	पूर्ण
	spin_unlock(&lslist_lock);

	अगर (rv) अणु
		log_debug(ls, "release_lockspace no remove %d", rv);
		वापस rv;
	पूर्ण

	dlm_device_deरेजिस्टर(ls);

	अगर (क्रमce < 3 && dlm_user_daemon_available())
		करो_uevent(ls, 0);

	dlm_recoverd_stop(ls);

	अगर (ls_count == 1) अणु
		dlm_scand_stop();
		dlm_lowcomms_shutकरोwn();
	पूर्ण

	dlm_callback_stop(ls);

	हटाओ_lockspace(ls);

	dlm_delete_debug_file(ls);

	idr_destroy(&ls->ls_recover_idr);
	kमुक्त(ls->ls_recover_buf);

	/*
	 * Free all lkb's in idr
	 */

	idr_क्रम_each(&ls->ls_lkbidr, lkb_idr_मुक्त, ls);
	idr_destroy(&ls->ls_lkbidr);

	/*
	 * Free all rsb's on rsbtbl[] lists
	 */

	क्रम (i = 0; i < ls->ls_rsbtbl_size; i++) अणु
		जबतक ((n = rb_first(&ls->ls_rsbtbl[i].keep))) अणु
			rsb = rb_entry(n, काष्ठा dlm_rsb, res_hashnode);
			rb_erase(n, &ls->ls_rsbtbl[i].keep);
			dlm_मुक्त_rsb(rsb);
		पूर्ण

		जबतक ((n = rb_first(&ls->ls_rsbtbl[i].toss))) अणु
			rsb = rb_entry(n, काष्ठा dlm_rsb, res_hashnode);
			rb_erase(n, &ls->ls_rsbtbl[i].toss);
			dlm_मुक्त_rsb(rsb);
		पूर्ण
	पूर्ण

	vमुक्त(ls->ls_rsbtbl);

	क्रम (i = 0; i < DLM_REMOVE_NAMES_MAX; i++)
		kमुक्त(ls->ls_हटाओ_names[i]);

	जबतक (!list_empty(&ls->ls_new_rsb)) अणु
		rsb = list_first_entry(&ls->ls_new_rsb, काष्ठा dlm_rsb,
				       res_hashchain);
		list_del(&rsb->res_hashchain);
		dlm_मुक्त_rsb(rsb);
	पूर्ण

	/*
	 * Free काष्ठाures on any other lists
	 */

	dlm_purge_requestqueue(ls);
	kमुक्त(ls->ls_recover_args);
	dlm_clear_members(ls);
	dlm_clear_members_gone(ls);
	kमुक्त(ls->ls_node_array);
	log_rinfo(ls, "release_lockspace final free");
	kobject_put(&ls->ls_kobj);
	/* The ls काष्ठाure will be मुक्तd when the kobject is करोne with */

	module_put(THIS_MODULE);
	वापस 0;
पूर्ण

/*
 * Called when a प्रणाली has released all its locks and is not going to use the
 * lockspace any दीर्घer.  We मुक्त everything we're managing क्रम this lockspace.
 * Reमुख्यing nodes will go through the recovery process as अगर we'd died.  The
 * lockspace must जारी to function as usual, participating in recoveries,
 * until this वापसs.
 *
 * Force has 4 possible values:
 * 0 - करोn't destroy locksapce अगर it has any LKBs
 * 1 - destroy lockspace अगर it has remote LKBs but not अगर it has local LKBs
 * 2 - destroy lockspace regardless of LKBs
 * 3 - destroy lockspace as part of a क्रमced shutकरोwn
 */

पूर्णांक dlm_release_lockspace(व्योम *lockspace, पूर्णांक क्रमce)
अणु
	काष्ठा dlm_ls *ls;
	पूर्णांक error;

	ls = dlm_find_lockspace_local(lockspace);
	अगर (!ls)
		वापस -EINVAL;
	dlm_put_lockspace(ls);

	mutex_lock(&ls_lock);
	error = release_lockspace(ls, क्रमce);
	अगर (!error)
		ls_count--;
	अगर (!ls_count)
		dlm_lowcomms_stop();
	mutex_unlock(&ls_lock);

	वापस error;
पूर्ण

व्योम dlm_stop_lockspaces(व्योम)
अणु
	काष्ठा dlm_ls *ls;
	पूर्णांक count;

 restart:
	count = 0;
	spin_lock(&lslist_lock);
	list_क्रम_each_entry(ls, &lslist, ls_list) अणु
		अगर (!test_bit(LSFL_RUNNING, &ls->ls_flags)) अणु
			count++;
			जारी;
		पूर्ण
		spin_unlock(&lslist_lock);
		log_error(ls, "no userland control daemon, stopping lockspace");
		dlm_ls_stop(ls);
		जाओ restart;
	पूर्ण
	spin_unlock(&lslist_lock);

	अगर (count)
		log_prपूर्णांक("dlm user daemon left %d lockspaces", count);
पूर्ण

