<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_tpg.c
 *
 * This file contains generic Target Portal Group related functions.
 *
 * (c) Copyright 2002-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/net.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/in.h>
#समावेश <linux/export.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <scsi/scsi_proto.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_ua.h"

बाह्य काष्ठा se_device *g_lun0_dev;

/*	__core_tpg_get_initiator_node_acl():
 *
 *	mutex_lock(&tpg->acl_node_mutex); must be held when calling
 */
काष्ठा se_node_acl *__core_tpg_get_initiator_node_acl(
	काष्ठा se_portal_group *tpg,
	स्थिर अक्षर *initiatorname)
अणु
	काष्ठा se_node_acl *acl;

	list_क्रम_each_entry(acl, &tpg->acl_node_list, acl_list) अणु
		अगर (!म_भेद(acl->initiatorname, initiatorname))
			वापस acl;
	पूर्ण

	वापस शून्य;
पूर्ण

/*	core_tpg_get_initiator_node_acl():
 *
 *
 */
काष्ठा se_node_acl *core_tpg_get_initiator_node_acl(
	काष्ठा se_portal_group *tpg,
	अचिन्हित अक्षर *initiatorname)
अणु
	काष्ठा se_node_acl *acl;
	/*
	 * Obtain se_node_acl->acl_kref using fabric driver provided
	 * initiatorname[] during node acl endpoपूर्णांक lookup driven by
	 * new se_session login.
	 *
	 * The reference is held until se_session shutकरोwn -> release
	 * occurs via fabric driver invoked transport_deरेजिस्टर_session()
	 * or transport_मुक्त_session() code.
	 */
	mutex_lock(&tpg->acl_node_mutex);
	acl = __core_tpg_get_initiator_node_acl(tpg, initiatorname);
	अगर (acl) अणु
		अगर (!kref_get_unless_zero(&acl->acl_kref))
			acl = शून्य;
	पूर्ण
	mutex_unlock(&tpg->acl_node_mutex);

	वापस acl;
पूर्ण
EXPORT_SYMBOL(core_tpg_get_initiator_node_acl);

व्योम core_allocate_nexus_loss_ua(
	काष्ठा se_node_acl *nacl)
अणु
	काष्ठा se_dev_entry *deve;

	अगर (!nacl)
		वापस;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(deve, &nacl->lun_entry_hlist, link)
		core_scsi3_ua_allocate(deve, 0x29,
			ASCQ_29H_NEXUS_LOSS_OCCURRED);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(core_allocate_nexus_loss_ua);

/*	core_tpg_add_node_to_devs():
 *
 *
 */
व्योम core_tpg_add_node_to_devs(
	काष्ठा se_node_acl *acl,
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun *lun_orig)
अणु
	bool lun_access_ro = true;
	काष्ठा se_lun *lun;
	काष्ठा se_device *dev;

	mutex_lock(&tpg->tpg_lun_mutex);
	hlist_क्रम_each_entry_rcu(lun, &tpg->tpg_lun_hlist, link) अणु
		अगर (lun_orig && lun != lun_orig)
			जारी;

		dev = rcu_dereference_check(lun->lun_se_dev,
					    lockdep_is_held(&tpg->tpg_lun_mutex));
		/*
		 * By शेष in LIO-Target $FABRIC_MOD,
		 * demo_mode_ग_लिखो_protect is ON, or READ_ONLY;
		 */
		अगर (!tpg->se_tpg_tfo->tpg_check_demo_mode_ग_लिखो_protect(tpg)) अणु
			lun_access_ro = false;
		पूर्ण अन्यथा अणु
			/*
			 * Allow only optical drives to issue R/W in शेष RO
			 * demo mode.
			 */
			अगर (dev->transport->get_device_type(dev) == TYPE_DISK)
				lun_access_ro = true;
			अन्यथा
				lun_access_ro = false;
		पूर्ण

		pr_debug("TARGET_CORE[%s]->TPG[%u]_LUN[%llu] - Adding %s"
			" access for LUN in Demo Mode\n",
			tpg->se_tpg_tfo->fabric_name,
			tpg->se_tpg_tfo->tpg_get_tag(tpg), lun->unpacked_lun,
			lun_access_ro ? "READ-ONLY" : "READ-WRITE");

		core_enable_device_list_क्रम_node(lun, शून्य, lun->unpacked_lun,
						 lun_access_ro, acl, tpg);
		/*
		 * Check to see अगर there are any existing persistent reservation
		 * APTPL pre-registrations that need to be enabled क्रम this dynamic
		 * LUN ACL now..
		 */
		core_scsi3_check_aptpl_registration(dev, tpg, lun, acl,
						    lun->unpacked_lun);
	पूर्ण
	mutex_unlock(&tpg->tpg_lun_mutex);
पूर्ण

अटल व्योम
target_set_nacl_queue_depth(काष्ठा se_portal_group *tpg,
			    काष्ठा se_node_acl *acl, u32 queue_depth)
अणु
	acl->queue_depth = queue_depth;

	अगर (!acl->queue_depth) अणु
		pr_warn("Queue depth for %s Initiator Node: %s is 0,"
			"defaulting to 1.\n", tpg->se_tpg_tfo->fabric_name,
			acl->initiatorname);
		acl->queue_depth = 1;
	पूर्ण
पूर्ण

अटल काष्ठा se_node_acl *target_alloc_node_acl(काष्ठा se_portal_group *tpg,
		स्थिर अचिन्हित अक्षर *initiatorname)
अणु
	काष्ठा se_node_acl *acl;
	u32 queue_depth;

	acl = kzalloc(max(माप(*acl), tpg->se_tpg_tfo->node_acl_size),
			GFP_KERNEL);
	अगर (!acl)
		वापस शून्य;

	INIT_LIST_HEAD(&acl->acl_list);
	INIT_LIST_HEAD(&acl->acl_sess_list);
	INIT_HLIST_HEAD(&acl->lun_entry_hlist);
	kref_init(&acl->acl_kref);
	init_completion(&acl->acl_मुक्त_comp);
	spin_lock_init(&acl->nacl_sess_lock);
	mutex_init(&acl->lun_entry_mutex);
	atomic_set(&acl->acl_pr_ref_count, 0);

	अगर (tpg->se_tpg_tfo->tpg_get_शेष_depth)
		queue_depth = tpg->se_tpg_tfo->tpg_get_शेष_depth(tpg);
	अन्यथा
		queue_depth = 1;
	target_set_nacl_queue_depth(tpg, acl, queue_depth);

	snम_लिखो(acl->initiatorname, TRANSPORT_IQN_LEN, "%s", initiatorname);
	acl->se_tpg = tpg;
	acl->acl_index = scsi_get_new_index(SCSI_AUTH_INTR_INDEX);

	tpg->se_tpg_tfo->set_शेष_node_attributes(acl);

	वापस acl;
पूर्ण

अटल व्योम target_add_node_acl(काष्ठा se_node_acl *acl)
अणु
	काष्ठा se_portal_group *tpg = acl->se_tpg;

	mutex_lock(&tpg->acl_node_mutex);
	list_add_tail(&acl->acl_list, &tpg->acl_node_list);
	mutex_unlock(&tpg->acl_node_mutex);

	pr_debug("%s_TPG[%hu] - Added %s ACL with TCQ Depth: %d for %s"
		" Initiator Node: %s\n",
		tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		acl->dynamic_node_acl ? "DYNAMIC" : "",
		acl->queue_depth,
		tpg->se_tpg_tfo->fabric_name,
		acl->initiatorname);
पूर्ण

bool target_tpg_has_node_acl(काष्ठा se_portal_group *tpg,
			     स्थिर अक्षर *initiatorname)
अणु
	काष्ठा se_node_acl *acl;
	bool found = false;

	mutex_lock(&tpg->acl_node_mutex);
	list_क्रम_each_entry(acl, &tpg->acl_node_list, acl_list) अणु
		अगर (!म_भेद(acl->initiatorname, initiatorname)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tpg->acl_node_mutex);

	वापस found;
पूर्ण
EXPORT_SYMBOL(target_tpg_has_node_acl);

काष्ठा se_node_acl *core_tpg_check_initiator_node_acl(
	काष्ठा se_portal_group *tpg,
	अचिन्हित अक्षर *initiatorname)
अणु
	काष्ठा se_node_acl *acl;

	acl = core_tpg_get_initiator_node_acl(tpg, initiatorname);
	अगर (acl)
		वापस acl;

	अगर (!tpg->se_tpg_tfo->tpg_check_demo_mode(tpg))
		वापस शून्य;

	acl = target_alloc_node_acl(tpg, initiatorname);
	अगर (!acl)
		वापस शून्य;
	/*
	 * When allocating a dynamically generated node_acl, go ahead
	 * and take the extra kref now beक्रमe वापसing to the fabric
	 * driver caller.
	 *
	 * Note this reference will be released at session shutकरोwn
	 * समय within transport_मुक्त_session() code.
	 */
	kref_get(&acl->acl_kref);
	acl->dynamic_node_acl = 1;

	/*
	 * Here we only create demo-mode MappedLUNs from the active
	 * TPG LUNs अगर the fabric is not explicitly asking क्रम
	 * tpg_check_demo_mode_login_only() == 1.
	 */
	अगर ((tpg->se_tpg_tfo->tpg_check_demo_mode_login_only == शून्य) ||
	    (tpg->se_tpg_tfo->tpg_check_demo_mode_login_only(tpg) != 1))
		core_tpg_add_node_to_devs(acl, tpg, शून्य);

	target_add_node_acl(acl);
	वापस acl;
पूर्ण
EXPORT_SYMBOL(core_tpg_check_initiator_node_acl);

व्योम core_tpg_रुको_क्रम_nacl_pr_ref(काष्ठा se_node_acl *nacl)
अणु
	जबतक (atomic_पढ़ो(&nacl->acl_pr_ref_count) != 0)
		cpu_relax();
पूर्ण

काष्ठा se_node_acl *core_tpg_add_initiator_node_acl(
	काष्ठा se_portal_group *tpg,
	स्थिर अक्षर *initiatorname)
अणु
	काष्ठा se_node_acl *acl;

	mutex_lock(&tpg->acl_node_mutex);
	acl = __core_tpg_get_initiator_node_acl(tpg, initiatorname);
	अगर (acl) अणु
		अगर (acl->dynamic_node_acl) अणु
			acl->dynamic_node_acl = 0;
			pr_debug("%s_TPG[%u] - Replacing dynamic ACL"
				" for %s\n", tpg->se_tpg_tfo->fabric_name,
				tpg->se_tpg_tfo->tpg_get_tag(tpg), initiatorname);
			mutex_unlock(&tpg->acl_node_mutex);
			वापस acl;
		पूर्ण

		pr_err("ACL entry for %s Initiator"
			" Node %s already exists for TPG %u, ignoring"
			" request.\n",  tpg->se_tpg_tfo->fabric_name,
			initiatorname, tpg->se_tpg_tfo->tpg_get_tag(tpg));
		mutex_unlock(&tpg->acl_node_mutex);
		वापस ERR_PTR(-EEXIST);
	पूर्ण
	mutex_unlock(&tpg->acl_node_mutex);

	acl = target_alloc_node_acl(tpg, initiatorname);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);

	target_add_node_acl(acl);
	वापस acl;
पूर्ण

अटल व्योम target_shutकरोwn_sessions(काष्ठा se_node_acl *acl)
अणु
	काष्ठा se_session *sess;
	अचिन्हित दीर्घ flags;

restart:
	spin_lock_irqsave(&acl->nacl_sess_lock, flags);
	list_क्रम_each_entry(sess, &acl->acl_sess_list, sess_acl_list) अणु
		अगर (atomic_पढ़ो(&sess->stopped))
			जारी;

		list_del_init(&sess->sess_acl_list);
		spin_unlock_irqrestore(&acl->nacl_sess_lock, flags);

		अगर (acl->se_tpg->se_tpg_tfo->बंद_session)
			acl->se_tpg->se_tpg_tfo->बंद_session(sess);
		जाओ restart;
	पूर्ण
	spin_unlock_irqrestore(&acl->nacl_sess_lock, flags);
पूर्ण

व्योम core_tpg_del_initiator_node_acl(काष्ठा se_node_acl *acl)
अणु
	काष्ठा se_portal_group *tpg = acl->se_tpg;

	mutex_lock(&tpg->acl_node_mutex);
	अगर (acl->dynamic_node_acl)
		acl->dynamic_node_acl = 0;
	list_del_init(&acl->acl_list);
	mutex_unlock(&tpg->acl_node_mutex);

	target_shutकरोwn_sessions(acl);

	target_put_nacl(acl);
	/*
	 * Wait क्रम last target_put_nacl() to complete in target_complete_nacl()
	 * क्रम active fabric session transport_deरेजिस्टर_session() callbacks.
	 */
	रुको_क्रम_completion(&acl->acl_मुक्त_comp);

	core_tpg_रुको_क्रम_nacl_pr_ref(acl);
	core_मुक्त_device_list_क्रम_node(acl, tpg);

	pr_debug("%s_TPG[%hu] - Deleted ACL with TCQ Depth: %d for %s"
		" Initiator Node: %s\n", tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), acl->queue_depth,
		tpg->se_tpg_tfo->fabric_name, acl->initiatorname);

	kमुक्त(acl);
पूर्ण

/*	core_tpg_set_initiator_node_queue_depth():
 *
 *
 */
पूर्णांक core_tpg_set_initiator_node_queue_depth(
	काष्ठा se_node_acl *acl,
	u32 queue_depth)
अणु
	काष्ठा se_portal_group *tpg = acl->se_tpg;

	/*
	 * Allow the setting of se_node_acl queue_depth to be idempotent,
	 * and not क्रमce a session shutकरोwn event अगर the value is not
	 * changing.
	 */
	अगर (acl->queue_depth == queue_depth)
		वापस 0;
	/*
	 * User has requested to change the queue depth क्रम a Initiator Node.
	 * Change the value in the Node's काष्ठा se_node_acl, and call
	 * target_set_nacl_queue_depth() to set the new queue depth.
	 */
	target_set_nacl_queue_depth(tpg, acl, queue_depth);

	/*
	 * Shutकरोwn all pending sessions to क्रमce session reinstatement.
	 */
	target_shutकरोwn_sessions(acl);

	pr_debug("Successfully changed queue depth to: %d for Initiator"
		" Node: %s on %s Target Portal Group: %u\n", acl->queue_depth,
		acl->initiatorname, tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(core_tpg_set_initiator_node_queue_depth);

/*	core_tpg_set_initiator_node_tag():
 *
 *	Initiator nodeacl tags are not used पूर्णांकernally, but may be used by
 *	userspace to emulate aliases or groups.
 *	Returns length of newly-set tag or -EINVAL.
 */
पूर्णांक core_tpg_set_initiator_node_tag(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_node_acl *acl,
	स्थिर अक्षर *new_tag)
अणु
	अगर (म_माप(new_tag) >= MAX_ACL_TAG_SIZE)
		वापस -EINVAL;

	अगर (!म_भेदन("NULL", new_tag, 4)) अणु
		acl->acl_tag[0] = '\0';
		वापस 0;
	पूर्ण

	वापस snम_लिखो(acl->acl_tag, MAX_ACL_TAG_SIZE, "%s", new_tag);
पूर्ण
EXPORT_SYMBOL(core_tpg_set_initiator_node_tag);

अटल व्योम core_tpg_lun_ref_release(काष्ठा percpu_ref *ref)
अणु
	काष्ठा se_lun *lun = container_of(ref, काष्ठा se_lun, lun_ref);

	complete(&lun->lun_shutकरोwn_comp);
पूर्ण

/* Does not change se_wwn->priv. */
पूर्णांक core_tpg_रेजिस्टर(
	काष्ठा se_wwn *se_wwn,
	काष्ठा se_portal_group *se_tpg,
	पूर्णांक proto_id)
अणु
	पूर्णांक ret;

	अगर (!se_tpg)
		वापस -EINVAL;
	/*
	 * For the typical हाल where core_tpg_रेजिस्टर() is called by a
	 * fabric driver from target_core_fabric_ops->fabric_make_tpg()
	 * configfs context, use the original tf_ops poपूर्णांकer alपढ़ोy saved
	 * by target-core in target_fabric_make_wwn().
	 *
	 * Otherwise, क्रम special हालs like iscsi-target discovery TPGs
	 * the caller is responsible क्रम setting ->se_tpg_tfo ahead of
	 * calling core_tpg_रेजिस्टर().
	 */
	अगर (se_wwn)
		se_tpg->se_tpg_tfo = se_wwn->wwn_tf->tf_ops;

	अगर (!se_tpg->se_tpg_tfo) अणु
		pr_err("Unable to locate se_tpg->se_tpg_tfo pointer\n");
		वापस -EINVAL;
	पूर्ण

	INIT_HLIST_HEAD(&se_tpg->tpg_lun_hlist);
	se_tpg->proto_id = proto_id;
	se_tpg->se_tpg_wwn = se_wwn;
	atomic_set(&se_tpg->tpg_pr_ref_count, 0);
	INIT_LIST_HEAD(&se_tpg->acl_node_list);
	INIT_LIST_HEAD(&se_tpg->tpg_sess_list);
	spin_lock_init(&se_tpg->session_lock);
	mutex_init(&se_tpg->tpg_lun_mutex);
	mutex_init(&se_tpg->acl_node_mutex);

	अगर (se_tpg->proto_id >= 0) अणु
		se_tpg->tpg_virt_lun0 = core_tpg_alloc_lun(se_tpg, 0);
		अगर (IS_ERR(se_tpg->tpg_virt_lun0))
			वापस PTR_ERR(se_tpg->tpg_virt_lun0);

		ret = core_tpg_add_lun(se_tpg, se_tpg->tpg_virt_lun0,
				true, g_lun0_dev);
		अगर (ret < 0) अणु
			kमुक्त(se_tpg->tpg_virt_lun0);
			वापस ret;
		पूर्ण
	पूर्ण

	pr_debug("TARGET_CORE[%s]: Allocated portal_group for endpoint: %s, "
		 "Proto: %d, Portal Tag: %u\n", se_tpg->se_tpg_tfo->fabric_name,
		se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg) ?
		se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg) : शून्य,
		se_tpg->proto_id, se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(core_tpg_रेजिस्टर);

पूर्णांक core_tpg_deरेजिस्टर(काष्ठा se_portal_group *se_tpg)
अणु
	स्थिर काष्ठा target_core_fabric_ops *tfo = se_tpg->se_tpg_tfo;
	काष्ठा se_node_acl *nacl, *nacl_पंचांगp;
	LIST_HEAD(node_list);

	pr_debug("TARGET_CORE[%s]: Deallocating portal_group for endpoint: %s, "
		 "Proto: %d, Portal Tag: %u\n", tfo->fabric_name,
		tfo->tpg_get_wwn(se_tpg) ? tfo->tpg_get_wwn(se_tpg) : शून्य,
		se_tpg->proto_id, tfo->tpg_get_tag(se_tpg));

	जबतक (atomic_पढ़ो(&se_tpg->tpg_pr_ref_count) != 0)
		cpu_relax();

	mutex_lock(&se_tpg->acl_node_mutex);
	list_splice_init(&se_tpg->acl_node_list, &node_list);
	mutex_unlock(&se_tpg->acl_node_mutex);
	/*
	 * Release any reमुख्यing demo-mode generated se_node_acl that have
	 * not been released because of TFO->tpg_check_demo_mode_cache() == 1
	 * in transport_deरेजिस्टर_session().
	 */
	list_क्रम_each_entry_safe(nacl, nacl_पंचांगp, &node_list, acl_list) अणु
		list_del_init(&nacl->acl_list);

		core_tpg_रुको_क्रम_nacl_pr_ref(nacl);
		core_मुक्त_device_list_क्रम_node(nacl, se_tpg);
		kमुक्त(nacl);
	पूर्ण

	अगर (se_tpg->proto_id >= 0) अणु
		core_tpg_हटाओ_lun(se_tpg, se_tpg->tpg_virt_lun0);
		kमुक्त_rcu(se_tpg->tpg_virt_lun0, rcu_head);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(core_tpg_deरेजिस्टर);

काष्ठा se_lun *core_tpg_alloc_lun(
	काष्ठा se_portal_group *tpg,
	u64 unpacked_lun)
अणु
	काष्ठा se_lun *lun;

	lun = kzalloc(माप(*lun), GFP_KERNEL);
	अगर (!lun) अणु
		pr_err("Unable to allocate se_lun memory\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	lun->unpacked_lun = unpacked_lun;
	atomic_set(&lun->lun_acl_count, 0);
	init_completion(&lun->lun_shutकरोwn_comp);
	INIT_LIST_HEAD(&lun->lun_deve_list);
	INIT_LIST_HEAD(&lun->lun_dev_link);
	atomic_set(&lun->lun_tg_pt_secondary_offline, 0);
	spin_lock_init(&lun->lun_deve_lock);
	mutex_init(&lun->lun_tg_pt_md_mutex);
	INIT_LIST_HEAD(&lun->lun_tg_pt_gp_link);
	spin_lock_init(&lun->lun_tg_pt_gp_lock);
	lun->lun_tpg = tpg;

	वापस lun;
पूर्ण

पूर्णांक core_tpg_add_lun(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun *lun,
	bool lun_access_ro,
	काष्ठा se_device *dev)
अणु
	पूर्णांक ret;

	ret = percpu_ref_init(&lun->lun_ref, core_tpg_lun_ref_release, 0,
			      GFP_KERNEL);
	अगर (ret < 0)
		जाओ out;

	ret = core_alloc_rtpi(lun, dev);
	अगर (ret)
		जाओ out_समाप्त_ref;

	अगर (!(dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA) &&
	    !(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		target_attach_tg_pt_gp(lun, dev->t10_alua.शेष_tg_pt_gp);

	mutex_lock(&tpg->tpg_lun_mutex);

	spin_lock(&dev->se_port_lock);
	lun->lun_index = dev->dev_index;
	rcu_assign_poपूर्णांकer(lun->lun_se_dev, dev);
	dev->export_count++;
	list_add_tail(&lun->lun_dev_link, &dev->dev_sep_list);
	spin_unlock(&dev->se_port_lock);

	अगर (dev->dev_flags & DF_READ_ONLY)
		lun->lun_access_ro = true;
	अन्यथा
		lun->lun_access_ro = lun_access_ro;
	अगर (!(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		hlist_add_head_rcu(&lun->link, &tpg->tpg_lun_hlist);
	mutex_unlock(&tpg->tpg_lun_mutex);

	वापस 0;

out_समाप्त_ref:
	percpu_ref_निकास(&lun->lun_ref);
out:
	वापस ret;
पूर्ण

व्योम core_tpg_हटाओ_lun(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun *lun)
अणु
	/*
	 * rcu_dereference_raw रक्षित by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	काष्ठा se_device *dev = rcu_dereference_raw(lun->lun_se_dev);

	lun->lun_shutकरोwn = true;

	core_clear_lun_from_tpg(lun, tpg);
	/*
	 * Wait क्रम any active I/O references to percpu se_lun->lun_ref to
	 * be released.  Also, se_lun->lun_ref is now used by PR and ALUA
	 * logic when referencing a remote target port during ALL_TGT_PT=1
	 * and generating UNIT_ATTENTIONs क्रम ALUA access state transition.
	 */
	transport_clear_lun_ref(lun);

	mutex_lock(&tpg->tpg_lun_mutex);
	अगर (lun->lun_se_dev) अणु
		target_detach_tg_pt_gp(lun);

		spin_lock(&dev->se_port_lock);
		list_del(&lun->lun_dev_link);
		dev->export_count--;
		rcu_assign_poपूर्णांकer(lun->lun_se_dev, शून्य);
		spin_unlock(&dev->se_port_lock);
	पूर्ण
	अगर (!(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		hlist_del_rcu(&lun->link);

	lun->lun_shutकरोwn = false;
	mutex_unlock(&tpg->tpg_lun_mutex);

	percpu_ref_निकास(&lun->lun_ref);
पूर्ण
