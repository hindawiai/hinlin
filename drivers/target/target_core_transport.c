<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_transport.c
 *
 * This file contains the Generic Target Engine Core.
 *
 * (c) Copyright 2002-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/net.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/in.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/module.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_common.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_ua.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/target.h>

अटल काष्ठा workqueue_काष्ठा *target_completion_wq;
अटल काष्ठा workqueue_काष्ठा *target_submission_wq;
अटल काष्ठा kmem_cache *se_sess_cache;
काष्ठा kmem_cache *se_ua_cache;
काष्ठा kmem_cache *t10_pr_reg_cache;
काष्ठा kmem_cache *t10_alua_lu_gp_cache;
काष्ठा kmem_cache *t10_alua_lu_gp_mem_cache;
काष्ठा kmem_cache *t10_alua_tg_pt_gp_cache;
काष्ठा kmem_cache *t10_alua_lba_map_cache;
काष्ठा kmem_cache *t10_alua_lba_map_mem_cache;

अटल व्योम transport_complete_task_attr(काष्ठा se_cmd *cmd);
अटल व्योम translate_sense_reason(काष्ठा se_cmd *cmd, sense_reason_t reason);
अटल व्योम transport_handle_queue_full(काष्ठा se_cmd *cmd,
		काष्ठा se_device *dev, पूर्णांक err, bool ग_लिखो_pending);
अटल व्योम target_complete_ok_work(काष्ठा work_काष्ठा *work);

पूर्णांक init_se_kmem_caches(व्योम)
अणु
	se_sess_cache = kmem_cache_create("se_sess_cache",
			माप(काष्ठा se_session), __alignof__(काष्ठा se_session),
			0, शून्य);
	अगर (!se_sess_cache) अणु
		pr_err("kmem_cache_create() for struct se_session"
				" failed\n");
		जाओ out;
	पूर्ण
	se_ua_cache = kmem_cache_create("se_ua_cache",
			माप(काष्ठा se_ua), __alignof__(काष्ठा se_ua),
			0, शून्य);
	अगर (!se_ua_cache) अणु
		pr_err("kmem_cache_create() for struct se_ua failed\n");
		जाओ out_मुक्त_sess_cache;
	पूर्ण
	t10_pr_reg_cache = kmem_cache_create("t10_pr_reg_cache",
			माप(काष्ठा t10_pr_registration),
			__alignof__(काष्ठा t10_pr_registration), 0, शून्य);
	अगर (!t10_pr_reg_cache) अणु
		pr_err("kmem_cache_create() for struct t10_pr_registration"
				" failed\n");
		जाओ out_मुक्त_ua_cache;
	पूर्ण
	t10_alua_lu_gp_cache = kmem_cache_create("t10_alua_lu_gp_cache",
			माप(काष्ठा t10_alua_lu_gp), __alignof__(काष्ठा t10_alua_lu_gp),
			0, शून्य);
	अगर (!t10_alua_lu_gp_cache) अणु
		pr_err("kmem_cache_create() for t10_alua_lu_gp_cache"
				" failed\n");
		जाओ out_मुक्त_pr_reg_cache;
	पूर्ण
	t10_alua_lu_gp_mem_cache = kmem_cache_create("t10_alua_lu_gp_mem_cache",
			माप(काष्ठा t10_alua_lu_gp_member),
			__alignof__(काष्ठा t10_alua_lu_gp_member), 0, शून्य);
	अगर (!t10_alua_lu_gp_mem_cache) अणु
		pr_err("kmem_cache_create() for t10_alua_lu_gp_mem_"
				"cache failed\n");
		जाओ out_मुक्त_lu_gp_cache;
	पूर्ण
	t10_alua_tg_pt_gp_cache = kmem_cache_create("t10_alua_tg_pt_gp_cache",
			माप(काष्ठा t10_alua_tg_pt_gp),
			__alignof__(काष्ठा t10_alua_tg_pt_gp), 0, शून्य);
	अगर (!t10_alua_tg_pt_gp_cache) अणु
		pr_err("kmem_cache_create() for t10_alua_tg_pt_gp_"
				"cache failed\n");
		जाओ out_मुक्त_lu_gp_mem_cache;
	पूर्ण
	t10_alua_lba_map_cache = kmem_cache_create(
			"t10_alua_lba_map_cache",
			माप(काष्ठा t10_alua_lba_map),
			__alignof__(काष्ठा t10_alua_lba_map), 0, शून्य);
	अगर (!t10_alua_lba_map_cache) अणु
		pr_err("kmem_cache_create() for t10_alua_lba_map_"
				"cache failed\n");
		जाओ out_मुक्त_tg_pt_gp_cache;
	पूर्ण
	t10_alua_lba_map_mem_cache = kmem_cache_create(
			"t10_alua_lba_map_mem_cache",
			माप(काष्ठा t10_alua_lba_map_member),
			__alignof__(काष्ठा t10_alua_lba_map_member), 0, शून्य);
	अगर (!t10_alua_lba_map_mem_cache) अणु
		pr_err("kmem_cache_create() for t10_alua_lba_map_mem_"
				"cache failed\n");
		जाओ out_मुक्त_lba_map_cache;
	पूर्ण

	target_completion_wq = alloc_workqueue("target_completion",
					       WQ_MEM_RECLAIM, 0);
	अगर (!target_completion_wq)
		जाओ out_मुक्त_lba_map_mem_cache;

	target_submission_wq = alloc_workqueue("target_submission",
					       WQ_MEM_RECLAIM, 0);
	अगर (!target_submission_wq)
		जाओ out_मुक्त_completion_wq;

	वापस 0;

out_मुक्त_completion_wq:
	destroy_workqueue(target_completion_wq);
out_मुक्त_lba_map_mem_cache:
	kmem_cache_destroy(t10_alua_lba_map_mem_cache);
out_मुक्त_lba_map_cache:
	kmem_cache_destroy(t10_alua_lba_map_cache);
out_मुक्त_tg_pt_gp_cache:
	kmem_cache_destroy(t10_alua_tg_pt_gp_cache);
out_मुक्त_lu_gp_mem_cache:
	kmem_cache_destroy(t10_alua_lu_gp_mem_cache);
out_मुक्त_lu_gp_cache:
	kmem_cache_destroy(t10_alua_lu_gp_cache);
out_मुक्त_pr_reg_cache:
	kmem_cache_destroy(t10_pr_reg_cache);
out_मुक्त_ua_cache:
	kmem_cache_destroy(se_ua_cache);
out_मुक्त_sess_cache:
	kmem_cache_destroy(se_sess_cache);
out:
	वापस -ENOMEM;
पूर्ण

व्योम release_se_kmem_caches(व्योम)
अणु
	destroy_workqueue(target_submission_wq);
	destroy_workqueue(target_completion_wq);
	kmem_cache_destroy(se_sess_cache);
	kmem_cache_destroy(se_ua_cache);
	kmem_cache_destroy(t10_pr_reg_cache);
	kmem_cache_destroy(t10_alua_lu_gp_cache);
	kmem_cache_destroy(t10_alua_lu_gp_mem_cache);
	kmem_cache_destroy(t10_alua_tg_pt_gp_cache);
	kmem_cache_destroy(t10_alua_lba_map_cache);
	kmem_cache_destroy(t10_alua_lba_map_mem_cache);
पूर्ण

/* This code ensures unique mib indexes are handed out. */
अटल DEFINE_SPINLOCK(scsi_mib_index_lock);
अटल u32 scsi_mib_index[SCSI_INDEX_TYPE_MAX];

/*
 * Allocate a new row index क्रम the entry type specअगरied
 */
u32 scsi_get_new_index(scsi_index_t type)
अणु
	u32 new_index;

	BUG_ON((type < 0) || (type >= SCSI_INDEX_TYPE_MAX));

	spin_lock(&scsi_mib_index_lock);
	new_index = ++scsi_mib_index[type];
	spin_unlock(&scsi_mib_index_lock);

	वापस new_index;
पूर्ण

व्योम transport_subप्रणाली_check_init(व्योम)
अणु
	पूर्णांक ret;
	अटल पूर्णांक sub_api_initialized;

	अगर (sub_api_initialized)
		वापस;

	ret = IS_ENABLED(CONFIG_TCM_IBLOCK) && request_module("target_core_iblock");
	अगर (ret != 0)
		pr_err("Unable to load target_core_iblock\n");

	ret = IS_ENABLED(CONFIG_TCM_खाताIO) && request_module("target_core_file");
	अगर (ret != 0)
		pr_err("Unable to load target_core_file\n");

	ret = IS_ENABLED(CONFIG_TCM_PSCSI) && request_module("target_core_pscsi");
	अगर (ret != 0)
		pr_err("Unable to load target_core_pscsi\n");

	ret = IS_ENABLED(CONFIG_TCM_USER2) && request_module("target_core_user");
	अगर (ret != 0)
		pr_err("Unable to load target_core_user\n");

	sub_api_initialized = 1;
पूर्ण

अटल व्योम target_release_sess_cmd_refcnt(काष्ठा percpu_ref *ref)
अणु
	काष्ठा se_session *sess = container_of(ref, typeof(*sess), cmd_count);

	wake_up(&sess->cmd_count_wq);
पूर्ण

/**
 * transport_init_session - initialize a session object
 * @se_sess: Session object poपूर्णांकer.
 *
 * The caller must have zero-initialized @se_sess beक्रमe calling this function.
 */
पूर्णांक transport_init_session(काष्ठा se_session *se_sess)
अणु
	INIT_LIST_HEAD(&se_sess->sess_list);
	INIT_LIST_HEAD(&se_sess->sess_acl_list);
	spin_lock_init(&se_sess->sess_cmd_lock);
	init_रुकोqueue_head(&se_sess->cmd_count_wq);
	init_completion(&se_sess->stop_करोne);
	atomic_set(&se_sess->stopped, 0);
	वापस percpu_ref_init(&se_sess->cmd_count,
			       target_release_sess_cmd_refcnt, 0, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(transport_init_session);

व्योम transport_uninit_session(काष्ठा se_session *se_sess)
अणु
	/*
	 * Drivers like iscsi and loop करो not call target_stop_session
	 * during session shutकरोwn so we have to drop the ref taken at init
	 * समय here.
	 */
	अगर (!atomic_पढ़ो(&se_sess->stopped))
		percpu_ref_put(&se_sess->cmd_count);

	percpu_ref_निकास(&se_sess->cmd_count);
पूर्ण

/**
 * transport_alloc_session - allocate a session object and initialize it
 * @sup_prot_ops: biपंचांगask that defines which T10-PI modes are supported.
 */
काष्ठा se_session *transport_alloc_session(क्रमागत target_prot_op sup_prot_ops)
अणु
	काष्ठा se_session *se_sess;
	पूर्णांक ret;

	se_sess = kmem_cache_zalloc(se_sess_cache, GFP_KERNEL);
	अगर (!se_sess) अणु
		pr_err("Unable to allocate struct se_session from"
				" se_sess_cache\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	ret = transport_init_session(se_sess);
	अगर (ret < 0) अणु
		kmem_cache_मुक्त(se_sess_cache, se_sess);
		वापस ERR_PTR(ret);
	पूर्ण
	se_sess->sup_prot_ops = sup_prot_ops;

	वापस se_sess;
पूर्ण
EXPORT_SYMBOL(transport_alloc_session);

/**
 * transport_alloc_session_tags - allocate target driver निजी data
 * @se_sess:  Session poपूर्णांकer.
 * @tag_num:  Maximum number of in-flight commands between initiator and target.
 * @tag_size: Size in bytes of the निजी data a target driver associates with
 *	      each command.
 */
पूर्णांक transport_alloc_session_tags(काष्ठा se_session *se_sess,
			         अचिन्हित पूर्णांक tag_num, अचिन्हित पूर्णांक tag_size)
अणु
	पूर्णांक rc;

	se_sess->sess_cmd_map = kvसुस्मृति(tag_size, tag_num,
					 GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!se_sess->sess_cmd_map) अणु
		pr_err("Unable to allocate se_sess->sess_cmd_map\n");
		वापस -ENOMEM;
	पूर्ण

	rc = sbiपंचांगap_queue_init_node(&se_sess->sess_tag_pool, tag_num, -1,
			false, GFP_KERNEL, NUMA_NO_NODE);
	अगर (rc < 0) अणु
		pr_err("Unable to init se_sess->sess_tag_pool,"
			" tag_num: %u\n", tag_num);
		kvमुक्त(se_sess->sess_cmd_map);
		se_sess->sess_cmd_map = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(transport_alloc_session_tags);

/**
 * transport_init_session_tags - allocate a session and target driver निजी data
 * @tag_num:  Maximum number of in-flight commands between initiator and target.
 * @tag_size: Size in bytes of the निजी data a target driver associates with
 *	      each command.
 * @sup_prot_ops: biपंचांगask that defines which T10-PI modes are supported.
 */
अटल काष्ठा se_session *
transport_init_session_tags(अचिन्हित पूर्णांक tag_num, अचिन्हित पूर्णांक tag_size,
			    क्रमागत target_prot_op sup_prot_ops)
अणु
	काष्ठा se_session *se_sess;
	पूर्णांक rc;

	अगर (tag_num != 0 && !tag_size) अणु
		pr_err("init_session_tags called with percpu-ida tag_num:"
		       " %u, but zero tag_size\n", tag_num);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (!tag_num && tag_size) अणु
		pr_err("init_session_tags called with percpu-ida tag_size:"
		       " %u, but zero tag_num\n", tag_size);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	se_sess = transport_alloc_session(sup_prot_ops);
	अगर (IS_ERR(se_sess))
		वापस se_sess;

	rc = transport_alloc_session_tags(se_sess, tag_num, tag_size);
	अगर (rc < 0) अणु
		transport_मुक्त_session(se_sess);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस se_sess;
पूर्ण

/*
 * Called with spin_lock_irqsave(&काष्ठा se_portal_group->session_lock called.
 */
व्योम __transport_रेजिस्टर_session(
	काष्ठा se_portal_group *se_tpg,
	काष्ठा se_node_acl *se_nacl,
	काष्ठा se_session *se_sess,
	व्योम *fabric_sess_ptr)
अणु
	स्थिर काष्ठा target_core_fabric_ops *tfo = se_tpg->se_tpg_tfo;
	अचिन्हित अक्षर buf[PR_REG_ISID_LEN];
	अचिन्हित दीर्घ flags;

	se_sess->se_tpg = se_tpg;
	se_sess->fabric_sess_ptr = fabric_sess_ptr;
	/*
	 * Used by काष्ठा se_node_acl's under ConfigFS to locate active se_session-t
	 *
	 * Only set क्रम काष्ठा se_session's that will actually be moving I/O.
	 * eg: *NOT* discovery sessions.
	 */
	अगर (se_nacl) अणु
		/*
		 *
		 * Determine अगर fabric allows क्रम T10-PI feature bits exposed to
		 * initiators क्रम device backends with !dev->dev_attrib.pi_prot_type.
		 *
		 * If so, then always save prot_type on a per se_node_acl node
		 * basis and re-instate the previous sess_prot_type to aव्योम
		 * disabling PI from below any previously initiator side
		 * रेजिस्टरed LUNs.
		 */
		अगर (se_nacl->saved_prot_type)
			se_sess->sess_prot_type = se_nacl->saved_prot_type;
		अन्यथा अगर (tfo->tpg_check_prot_fabric_only)
			se_sess->sess_prot_type = se_nacl->saved_prot_type =
					tfo->tpg_check_prot_fabric_only(se_tpg);
		/*
		 * If the fabric module supports an ISID based TransportID,
		 * save this value in binary from the fabric I_T Nexus now.
		 */
		अगर (se_tpg->se_tpg_tfo->sess_get_initiator_sid != शून्य) अणु
			स_रखो(&buf[0], 0, PR_REG_ISID_LEN);
			se_tpg->se_tpg_tfo->sess_get_initiator_sid(se_sess,
					&buf[0], PR_REG_ISID_LEN);
			se_sess->sess_bin_isid = get_unaligned_be64(&buf[0]);
		पूर्ण

		spin_lock_irqsave(&se_nacl->nacl_sess_lock, flags);
		/*
		 * The se_nacl->nacl_sess poपूर्णांकer will be set to the
		 * last active I_T Nexus क्रम each काष्ठा se_node_acl.
		 */
		se_nacl->nacl_sess = se_sess;

		list_add_tail(&se_sess->sess_acl_list,
			      &se_nacl->acl_sess_list);
		spin_unlock_irqrestore(&se_nacl->nacl_sess_lock, flags);
	पूर्ण
	list_add_tail(&se_sess->sess_list, &se_tpg->tpg_sess_list);

	pr_debug("TARGET_CORE[%s]: Registered fabric_sess_ptr: %p\n",
		se_tpg->se_tpg_tfo->fabric_name, se_sess->fabric_sess_ptr);
पूर्ण
EXPORT_SYMBOL(__transport_रेजिस्टर_session);

व्योम transport_रेजिस्टर_session(
	काष्ठा se_portal_group *se_tpg,
	काष्ठा se_node_acl *se_nacl,
	काष्ठा se_session *se_sess,
	व्योम *fabric_sess_ptr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&se_tpg->session_lock, flags);
	__transport_रेजिस्टर_session(se_tpg, se_nacl, se_sess, fabric_sess_ptr);
	spin_unlock_irqrestore(&se_tpg->session_lock, flags);
पूर्ण
EXPORT_SYMBOL(transport_रेजिस्टर_session);

काष्ठा se_session *
target_setup_session(काष्ठा se_portal_group *tpg,
		     अचिन्हित पूर्णांक tag_num, अचिन्हित पूर्णांक tag_size,
		     क्रमागत target_prot_op prot_op,
		     स्थिर अक्षर *initiatorname, व्योम *निजी,
		     पूर्णांक (*callback)(काष्ठा se_portal_group *,
				     काष्ठा se_session *, व्योम *))
अणु
	काष्ठा se_session *sess;

	/*
	 * If the fabric driver is using percpu-ida based pre allocation
	 * of I/O descriptor tags, go ahead and perक्रमm that setup now..
	 */
	अगर (tag_num != 0)
		sess = transport_init_session_tags(tag_num, tag_size, prot_op);
	अन्यथा
		sess = transport_alloc_session(prot_op);

	अगर (IS_ERR(sess))
		वापस sess;

	sess->se_node_acl = core_tpg_check_initiator_node_acl(tpg,
					(अचिन्हित अक्षर *)initiatorname);
	अगर (!sess->se_node_acl) अणु
		transport_मुक्त_session(sess);
		वापस ERR_PTR(-EACCES);
	पूर्ण
	/*
	 * Go ahead and perक्रमm any reमुख्यing fabric setup that is
	 * required beक्रमe transport_रेजिस्टर_session().
	 */
	अगर (callback != शून्य) अणु
		पूर्णांक rc = callback(tpg, sess, निजी);
		अगर (rc) अणु
			transport_मुक्त_session(sess);
			वापस ERR_PTR(rc);
		पूर्ण
	पूर्ण

	transport_रेजिस्टर_session(tpg, sess->se_node_acl, sess, निजी);
	वापस sess;
पूर्ण
EXPORT_SYMBOL(target_setup_session);

sमाप_प्रकार target_show_dynamic_sessions(काष्ठा se_portal_group *se_tpg, अक्षर *page)
अणु
	काष्ठा se_session *se_sess;
	sमाप_प्रकार len = 0;

	spin_lock_bh(&se_tpg->session_lock);
	list_क्रम_each_entry(se_sess, &se_tpg->tpg_sess_list, sess_list) अणु
		अगर (!se_sess->se_node_acl)
			जारी;
		अगर (!se_sess->se_node_acl->dynamic_node_acl)
			जारी;
		अगर (म_माप(se_sess->se_node_acl->initiatorname) + 1 + len > PAGE_SIZE)
			अवरोध;

		len += snम_लिखो(page + len, PAGE_SIZE - len, "%s\n",
				se_sess->se_node_acl->initiatorname);
		len += 1; /* Include शून्य terminator */
	पूर्ण
	spin_unlock_bh(&se_tpg->session_lock);

	वापस len;
पूर्ण
EXPORT_SYMBOL(target_show_dynamic_sessions);

अटल व्योम target_complete_nacl(काष्ठा kref *kref)
अणु
	काष्ठा se_node_acl *nacl = container_of(kref,
				काष्ठा se_node_acl, acl_kref);
	काष्ठा se_portal_group *se_tpg = nacl->se_tpg;

	अगर (!nacl->dynamic_stop) अणु
		complete(&nacl->acl_मुक्त_comp);
		वापस;
	पूर्ण

	mutex_lock(&se_tpg->acl_node_mutex);
	list_del_init(&nacl->acl_list);
	mutex_unlock(&se_tpg->acl_node_mutex);

	core_tpg_रुको_क्रम_nacl_pr_ref(nacl);
	core_मुक्त_device_list_क्रम_node(nacl, se_tpg);
	kमुक्त(nacl);
पूर्ण

व्योम target_put_nacl(काष्ठा se_node_acl *nacl)
अणु
	kref_put(&nacl->acl_kref, target_complete_nacl);
पूर्ण
EXPORT_SYMBOL(target_put_nacl);

व्योम transport_deरेजिस्टर_session_configfs(काष्ठा se_session *se_sess)
अणु
	काष्ठा se_node_acl *se_nacl;
	अचिन्हित दीर्घ flags;
	/*
	 * Used by काष्ठा se_node_acl's under ConfigFS to locate active काष्ठा se_session
	 */
	se_nacl = se_sess->se_node_acl;
	अगर (se_nacl) अणु
		spin_lock_irqsave(&se_nacl->nacl_sess_lock, flags);
		अगर (!list_empty(&se_sess->sess_acl_list))
			list_del_init(&se_sess->sess_acl_list);
		/*
		 * If the session list is empty, then clear the poपूर्णांकer.
		 * Otherwise, set the काष्ठा se_session poपूर्णांकer from the tail
		 * element of the per काष्ठा se_node_acl active session list.
		 */
		अगर (list_empty(&se_nacl->acl_sess_list))
			se_nacl->nacl_sess = शून्य;
		अन्यथा अणु
			se_nacl->nacl_sess = container_of(
					se_nacl->acl_sess_list.prev,
					काष्ठा se_session, sess_acl_list);
		पूर्ण
		spin_unlock_irqrestore(&se_nacl->nacl_sess_lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(transport_deरेजिस्टर_session_configfs);

व्योम transport_मुक्त_session(काष्ठा se_session *se_sess)
अणु
	काष्ठा se_node_acl *se_nacl = se_sess->se_node_acl;

	/*
	 * Drop the se_node_acl->nacl_kref obtained from within
	 * core_tpg_get_initiator_node_acl().
	 */
	अगर (se_nacl) अणु
		काष्ठा se_portal_group *se_tpg = se_nacl->se_tpg;
		स्थिर काष्ठा target_core_fabric_ops *se_tfo = se_tpg->se_tpg_tfo;
		अचिन्हित दीर्घ flags;

		se_sess->se_node_acl = शून्य;

		/*
		 * Also determine अगर we need to drop the extra ->cmd_kref अगर
		 * it had been previously dynamically generated, and
		 * the endpoपूर्णांक is not caching dynamic ACLs.
		 */
		mutex_lock(&se_tpg->acl_node_mutex);
		अगर (se_nacl->dynamic_node_acl &&
		    !se_tfo->tpg_check_demo_mode_cache(se_tpg)) अणु
			spin_lock_irqsave(&se_nacl->nacl_sess_lock, flags);
			अगर (list_empty(&se_nacl->acl_sess_list))
				se_nacl->dynamic_stop = true;
			spin_unlock_irqrestore(&se_nacl->nacl_sess_lock, flags);

			अगर (se_nacl->dynamic_stop)
				list_del_init(&se_nacl->acl_list);
		पूर्ण
		mutex_unlock(&se_tpg->acl_node_mutex);

		अगर (se_nacl->dynamic_stop)
			target_put_nacl(se_nacl);

		target_put_nacl(se_nacl);
	पूर्ण
	अगर (se_sess->sess_cmd_map) अणु
		sbiपंचांगap_queue_मुक्त(&se_sess->sess_tag_pool);
		kvमुक्त(se_sess->sess_cmd_map);
	पूर्ण
	transport_uninit_session(se_sess);
	kmem_cache_मुक्त(se_sess_cache, se_sess);
पूर्ण
EXPORT_SYMBOL(transport_मुक्त_session);

अटल पूर्णांक target_release_res(काष्ठा se_device *dev, व्योम *data)
अणु
	काष्ठा se_session *sess = data;

	अगर (dev->reservation_holder == sess)
		target_release_reservation(dev);
	वापस 0;
पूर्ण

व्योम transport_deरेजिस्टर_session(काष्ठा se_session *se_sess)
अणु
	काष्ठा se_portal_group *se_tpg = se_sess->se_tpg;
	अचिन्हित दीर्घ flags;

	अगर (!se_tpg) अणु
		transport_मुक्त_session(se_sess);
		वापस;
	पूर्ण

	spin_lock_irqsave(&se_tpg->session_lock, flags);
	list_del(&se_sess->sess_list);
	se_sess->se_tpg = शून्य;
	se_sess->fabric_sess_ptr = शून्य;
	spin_unlock_irqrestore(&se_tpg->session_lock, flags);

	/*
	 * Since the session is being हटाओd, release SPC-2
	 * reservations held by the session that is disappearing.
	 */
	target_क्रम_each_device(target_release_res, se_sess);

	pr_debug("TARGET_CORE[%s]: Deregistered fabric_sess\n",
		se_tpg->se_tpg_tfo->fabric_name);
	/*
	 * If last kref is dropping now क्रम an explicit NodeACL, awake sleeping
	 * ->acl_मुक्त_comp caller to wakeup configfs se_node_acl->acl_group
	 * removal context from within transport_मुक्त_session() code.
	 *
	 * For dynamic ACL, target_put_nacl() uses target_complete_nacl()
	 * to release all reमुख्यing generate_node_acl=1 created ACL resources.
	 */

	transport_मुक्त_session(se_sess);
पूर्ण
EXPORT_SYMBOL(transport_deरेजिस्टर_session);

व्योम target_हटाओ_session(काष्ठा se_session *se_sess)
अणु
	transport_deरेजिस्टर_session_configfs(se_sess);
	transport_deरेजिस्टर_session(se_sess);
पूर्ण
EXPORT_SYMBOL(target_हटाओ_session);

अटल व्योम target_हटाओ_from_state_list(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित दीर्घ flags;

	अगर (!dev)
		वापस;

	spin_lock_irqsave(&dev->queues[cmd->cpuid].lock, flags);
	अगर (cmd->state_active) अणु
		list_del(&cmd->state_list);
		cmd->state_active = false;
	पूर्ण
	spin_unlock_irqrestore(&dev->queues[cmd->cpuid].lock, flags);
पूर्ण

/*
 * This function is called by the target core after the target core has
 * finished processing a SCSI command or SCSI TMF. Both the regular command
 * processing code and the code क्रम पातing commands can call this
 * function. CMD_T_STOP is set अगर and only अगर another thपढ़ो is रुकोing
 * inside transport_रुको_क्रम_tasks() क्रम t_transport_stop_comp.
 */
अटल पूर्णांक transport_cmd_check_stop_to_fabric(काष्ठा se_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;

	target_हटाओ_from_state_list(cmd);

	/*
	 * Clear काष्ठा se_cmd->se_lun beक्रमe the hanकरोff to FE.
	 */
	cmd->se_lun = शून्य;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	/*
	 * Determine अगर frontend context caller is requesting the stopping of
	 * this command क्रम frontend exceptions.
	 */
	अगर (cmd->transport_state & CMD_T_STOP) अणु
		pr_debug("%s:%d CMD_T_STOP for ITT: 0x%08llx\n",
			__func__, __LINE__, cmd->tag);

		spin_unlock_irqrestore(&cmd->t_state_lock, flags);

		complete_all(&cmd->t_transport_stop_comp);
		वापस 1;
	पूर्ण
	cmd->transport_state &= ~CMD_T_ACTIVE;
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	/*
	 * Some fabric modules like tcm_loop can release their पूर्णांकernally
	 * allocated I/O reference and काष्ठा se_cmd now.
	 *
	 * Fabric modules are expected to वापस '1' here अगर the se_cmd being
	 * passed is released at this poपूर्णांक, or zero अगर not being released.
	 */
	वापस cmd->se_tfo->check_stop_मुक्त(cmd);
पूर्ण

अटल व्योम transport_lun_हटाओ_cmd(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_lun *lun = cmd->se_lun;

	अगर (!lun)
		वापस;

	अगर (cmpxchg(&cmd->lun_ref_active, true, false))
		percpu_ref_put(&lun->lun_ref);
पूर्ण

अटल व्योम target_complete_failure_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा se_cmd *cmd = container_of(work, काष्ठा se_cmd, work);

	transport_generic_request_failure(cmd,
			TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE);
पूर्ण

/*
 * Used when asking transport to copy Sense Data from the underlying
 * Linux/SCSI काष्ठा scsi_cmnd
 */
अटल अचिन्हित अक्षर *transport_get_sense_buffer(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	WARN_ON(!cmd->se_lun);

	अगर (!dev)
		वापस शून्य;

	अगर (cmd->se_cmd_flags & SCF_SENT_CHECK_CONDITION)
		वापस शून्य;

	cmd->scsi_sense_length = TRANSPORT_SENSE_BUFFER;

	pr_debug("HBA_[%u]_PLUG[%s]: Requesting sense for SAM STATUS: 0x%02x\n",
		dev->se_hba->hba_id, dev->transport->name, cmd->scsi_status);
	वापस cmd->sense_buffer;
पूर्ण

व्योम transport_copy_sense_to_cmd(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *sense)
अणु
	अचिन्हित अक्षर *cmd_sense_buf;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	cmd_sense_buf = transport_get_sense_buffer(cmd);
	अगर (!cmd_sense_buf) अणु
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		वापस;
	पूर्ण

	cmd->se_cmd_flags |= SCF_TRANSPORT_TASK_SENSE;
	स_नकल(cmd_sense_buf, sense, cmd->scsi_sense_length);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);
पूर्ण
EXPORT_SYMBOL(transport_copy_sense_to_cmd);

अटल व्योम target_handle_पात(काष्ठा se_cmd *cmd)
अणु
	bool tas = cmd->transport_state & CMD_T_TAS;
	bool ack_kref = cmd->se_cmd_flags & SCF_ACK_KREF;
	पूर्णांक ret;

	pr_debug("tag %#llx: send_abort_response = %d\n", cmd->tag, tas);

	अगर (tas) अणु
		अगर (!(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)) अणु
			cmd->scsi_status = SAM_STAT_TASK_ABORTED;
			pr_debug("Setting SAM_STAT_TASK_ABORTED status for CDB: 0x%02x, ITT: 0x%08llx\n",
				 cmd->t_task_cdb[0], cmd->tag);
			trace_target_cmd_complete(cmd);
			ret = cmd->se_tfo->queue_status(cmd);
			अगर (ret) अणु
				transport_handle_queue_full(cmd, cmd->se_dev,
							    ret, false);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			cmd->se_पंचांगr_req->response = TMR_FUNCTION_REJECTED;
			cmd->se_tfo->queue_पंचांग_rsp(cmd);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Allow the fabric driver to unmap any resources beक्रमe
		 * releasing the descriptor via TFO->release_cmd().
		 */
		cmd->se_tfo->पातed_task(cmd);
		अगर (ack_kref)
			WARN_ON_ONCE(target_put_sess_cmd(cmd) != 0);
		/*
		 * To करो: establish a unit attention condition on the I_T
		 * nexus associated with cmd. See also the paragraph "Aborting
		 * commands" in SAM.
		 */
	पूर्ण

	WARN_ON_ONCE(kref_पढ़ो(&cmd->cmd_kref) == 0);

	transport_lun_हटाओ_cmd(cmd);

	transport_cmd_check_stop_to_fabric(cmd);
पूर्ण

अटल व्योम target_पात_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा se_cmd *cmd = container_of(work, काष्ठा se_cmd, work);

	target_handle_पात(cmd);
पूर्ण

अटल bool target_cmd_पूर्णांकerrupted(काष्ठा se_cmd *cmd)
अणु
	पूर्णांक post_ret;

	अगर (cmd->transport_state & CMD_T_ABORTED) अणु
		अगर (cmd->transport_complete_callback)
			cmd->transport_complete_callback(cmd, false, &post_ret);
		INIT_WORK(&cmd->work, target_पात_work);
		queue_work(target_completion_wq, &cmd->work);
		वापस true;
	पूर्ण अन्यथा अगर (cmd->transport_state & CMD_T_STOP) अणु
		अगर (cmd->transport_complete_callback)
			cmd->transport_complete_callback(cmd, false, &post_ret);
		complete_all(&cmd->t_transport_stop_comp);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* May be called from पूर्णांकerrupt context so must not sleep. */
व्योम target_complete_cmd(काष्ठा se_cmd *cmd, u8 scsi_status)
अणु
	काष्ठा se_wwn *wwn = cmd->se_sess->se_tpg->se_tpg_wwn;
	पूर्णांक success, cpu;
	अचिन्हित दीर्घ flags;

	अगर (target_cmd_पूर्णांकerrupted(cmd))
		वापस;

	cmd->scsi_status = scsi_status;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	चयन (cmd->scsi_status) अणु
	हाल SAM_STAT_CHECK_CONDITION:
		अगर (cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE)
			success = 1;
		अन्यथा
			success = 0;
		अवरोध;
	शेष:
		success = 1;
		अवरोध;
	पूर्ण

	cmd->t_state = TRANSPORT_COMPLETE;
	cmd->transport_state |= (CMD_T_COMPLETE | CMD_T_ACTIVE);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	INIT_WORK(&cmd->work, success ? target_complete_ok_work :
		  target_complete_failure_work);

	अगर (wwn->cmd_compl_affinity == SE_COMPL_AFFINITY_CPUID)
		cpu = cmd->cpuid;
	अन्यथा
		cpu = wwn->cmd_compl_affinity;

	queue_work_on(cpu, target_completion_wq, &cmd->work);
पूर्ण
EXPORT_SYMBOL(target_complete_cmd);

व्योम target_set_cmd_data_length(काष्ठा se_cmd *cmd, पूर्णांक length)
अणु
	अगर (length < cmd->data_length) अणु
		अगर (cmd->se_cmd_flags & SCF_UNDERFLOW_BIT) अणु
			cmd->residual_count += cmd->data_length - length;
		पूर्ण अन्यथा अणु
			cmd->se_cmd_flags |= SCF_UNDERFLOW_BIT;
			cmd->residual_count = cmd->data_length - length;
		पूर्ण

		cmd->data_length = length;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(target_set_cmd_data_length);

व्योम target_complete_cmd_with_length(काष्ठा se_cmd *cmd, u8 scsi_status, पूर्णांक length)
अणु
	अगर (scsi_status == SAM_STAT_GOOD ||
	    cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL) अणु
		target_set_cmd_data_length(cmd, length);
	पूर्ण

	target_complete_cmd(cmd, scsi_status);
पूर्ण
EXPORT_SYMBOL(target_complete_cmd_with_length);

अटल व्योम target_add_to_state_list(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->queues[cmd->cpuid].lock, flags);
	अगर (!cmd->state_active) अणु
		list_add_tail(&cmd->state_list,
			      &dev->queues[cmd->cpuid].state_list);
		cmd->state_active = true;
	पूर्ण
	spin_unlock_irqrestore(&dev->queues[cmd->cpuid].lock, flags);
पूर्ण

/*
 * Handle QUEUE_FULL / -EAGAIN and -ENOMEM status
 */
अटल व्योम transport_ग_लिखो_pending_qf(काष्ठा se_cmd *cmd);
अटल व्योम transport_complete_qf(काष्ठा se_cmd *cmd);

व्योम target_qf_करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा se_device *dev = container_of(work, काष्ठा se_device,
					qf_work_queue);
	LIST_HEAD(qf_cmd_list);
	काष्ठा se_cmd *cmd, *cmd_पंचांगp;

	spin_lock_irq(&dev->qf_cmd_lock);
	list_splice_init(&dev->qf_cmd_list, &qf_cmd_list);
	spin_unlock_irq(&dev->qf_cmd_lock);

	list_क्रम_each_entry_safe(cmd, cmd_पंचांगp, &qf_cmd_list, se_qf_node) अणु
		list_del(&cmd->se_qf_node);
		atomic_dec_mb(&dev->dev_qf_count);

		pr_debug("Processing %s cmd: %p QUEUE_FULL in work queue"
			" context: %s\n", cmd->se_tfo->fabric_name, cmd,
			(cmd->t_state == TRANSPORT_COMPLETE_QF_OK) ? "COMPLETE_OK" :
			(cmd->t_state == TRANSPORT_COMPLETE_QF_WP) ? "WRITE_PENDING"
			: "UNKNOWN");

		अगर (cmd->t_state == TRANSPORT_COMPLETE_QF_WP)
			transport_ग_लिखो_pending_qf(cmd);
		अन्यथा अगर (cmd->t_state == TRANSPORT_COMPLETE_QF_OK ||
			 cmd->t_state == TRANSPORT_COMPLETE_QF_ERR)
			transport_complete_qf(cmd);
	पूर्ण
पूर्ण

अचिन्हित अक्षर *transport_dump_cmd_direction(काष्ठा se_cmd *cmd)
अणु
	चयन (cmd->data_direction) अणु
	हाल DMA_NONE:
		वापस "NONE";
	हाल DMA_FROM_DEVICE:
		वापस "READ";
	हाल DMA_TO_DEVICE:
		वापस "WRITE";
	हाल DMA_BIसूचीECTIONAL:
		वापस "BIDI";
	शेष:
		अवरोध;
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

व्योम transport_dump_dev_state(
	काष्ठा se_device *dev,
	अक्षर *b,
	पूर्णांक *bl)
अणु
	*bl += प्र_लिखो(b + *bl, "Status: ");
	अगर (dev->export_count)
		*bl += प्र_लिखो(b + *bl, "ACTIVATED");
	अन्यथा
		*bl += प्र_लिखो(b + *bl, "DEACTIVATED");

	*bl += प्र_लिखो(b + *bl, "  Max Queue Depth: %d", dev->queue_depth);
	*bl += प्र_लिखो(b + *bl, "  SectorSize: %u  HwMaxSectors: %u\n",
		dev->dev_attrib.block_size,
		dev->dev_attrib.hw_max_sectors);
	*bl += प्र_लिखो(b + *bl, "        ");
पूर्ण

व्योम transport_dump_vpd_proto_id(
	काष्ठा t10_vpd *vpd,
	अचिन्हित अक्षर *p_buf,
	पूर्णांक p_buf_len)
अणु
	अचिन्हित अक्षर buf[VPD_TMP_BUF_SIZE];
	पूर्णांक len;

	स_रखो(buf, 0, VPD_TMP_BUF_SIZE);
	len = प्र_लिखो(buf, "T10 VPD Protocol Identifier: ");

	चयन (vpd->protocol_identअगरier) अणु
	हाल 0x00:
		प्र_लिखो(buf+len, "Fibre Channel\n");
		अवरोध;
	हाल 0x10:
		प्र_लिखो(buf+len, "Parallel SCSI\n");
		अवरोध;
	हाल 0x20:
		प्र_लिखो(buf+len, "SSA\n");
		अवरोध;
	हाल 0x30:
		प्र_लिखो(buf+len, "IEEE 1394\n");
		अवरोध;
	हाल 0x40:
		प्र_लिखो(buf+len, "SCSI Remote Direct Memory Access"
				" Protocol\n");
		अवरोध;
	हाल 0x50:
		प्र_लिखो(buf+len, "Internet SCSI (iSCSI)\n");
		अवरोध;
	हाल 0x60:
		प्र_लिखो(buf+len, "SAS Serial SCSI Protocol\n");
		अवरोध;
	हाल 0x70:
		प्र_लिखो(buf+len, "Automation/Drive Interface Transport"
				" Protocol\n");
		अवरोध;
	हाल 0x80:
		प्र_लिखो(buf+len, "AT Attachment Interface ATA/ATAPI\n");
		अवरोध;
	शेष:
		प्र_लिखो(buf+len, "Unknown 0x%02x\n",
				vpd->protocol_identअगरier);
		अवरोध;
	पूर्ण

	अगर (p_buf)
		म_नकलन(p_buf, buf, p_buf_len);
	अन्यथा
		pr_debug("%s", buf);
पूर्ण

व्योम
transport_set_vpd_proto_id(काष्ठा t10_vpd *vpd, अचिन्हित अक्षर *page_83)
अणु
	/*
	 * Check अगर the Protocol Identअगरier Valid (PIV) bit is set..
	 *
	 * from spc3r23.pdf section 7.5.1
	 */
	 अगर (page_83[1] & 0x80) अणु
		vpd->protocol_identअगरier = (page_83[0] & 0xf0);
		vpd->protocol_identअगरier_set = 1;
		transport_dump_vpd_proto_id(vpd, शून्य, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(transport_set_vpd_proto_id);

पूर्णांक transport_dump_vpd_assoc(
	काष्ठा t10_vpd *vpd,
	अचिन्हित अक्षर *p_buf,
	पूर्णांक p_buf_len)
अणु
	अचिन्हित अक्षर buf[VPD_TMP_BUF_SIZE];
	पूर्णांक ret = 0;
	पूर्णांक len;

	स_रखो(buf, 0, VPD_TMP_BUF_SIZE);
	len = प्र_लिखो(buf, "T10 VPD Identifier Association: ");

	चयन (vpd->association) अणु
	हाल 0x00:
		प्र_लिखो(buf+len, "addressed logical unit\n");
		अवरोध;
	हाल 0x10:
		प्र_लिखो(buf+len, "target port\n");
		अवरोध;
	हाल 0x20:
		प्र_लिखो(buf+len, "SCSI target device\n");
		अवरोध;
	शेष:
		प्र_लिखो(buf+len, "Unknown 0x%02x\n", vpd->association);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (p_buf)
		म_नकलन(p_buf, buf, p_buf_len);
	अन्यथा
		pr_debug("%s", buf);

	वापस ret;
पूर्ण

पूर्णांक transport_set_vpd_assoc(काष्ठा t10_vpd *vpd, अचिन्हित अक्षर *page_83)
अणु
	/*
	 * The VPD identअगरication association..
	 *
	 * from spc3r23.pdf Section 7.6.3.1 Table 297
	 */
	vpd->association = (page_83[1] & 0x30);
	वापस transport_dump_vpd_assoc(vpd, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(transport_set_vpd_assoc);

पूर्णांक transport_dump_vpd_ident_type(
	काष्ठा t10_vpd *vpd,
	अचिन्हित अक्षर *p_buf,
	पूर्णांक p_buf_len)
अणु
	अचिन्हित अक्षर buf[VPD_TMP_BUF_SIZE];
	पूर्णांक ret = 0;
	पूर्णांक len;

	स_रखो(buf, 0, VPD_TMP_BUF_SIZE);
	len = प्र_लिखो(buf, "T10 VPD Identifier Type: ");

	चयन (vpd->device_identअगरier_type) अणु
	हाल 0x00:
		प्र_लिखो(buf+len, "Vendor specific\n");
		अवरोध;
	हाल 0x01:
		प्र_लिखो(buf+len, "T10 Vendor ID based\n");
		अवरोध;
	हाल 0x02:
		प्र_लिखो(buf+len, "EUI-64 based\n");
		अवरोध;
	हाल 0x03:
		प्र_लिखो(buf+len, "NAA\n");
		अवरोध;
	हाल 0x04:
		प्र_लिखो(buf+len, "Relative target port identifier\n");
		अवरोध;
	हाल 0x08:
		प्र_लिखो(buf+len, "SCSI name string\n");
		अवरोध;
	शेष:
		प्र_लिखो(buf+len, "Unsupported: 0x%02x\n",
				vpd->device_identअगरier_type);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (p_buf) अणु
		अगर (p_buf_len < म_माप(buf)+1)
			वापस -EINVAL;
		म_नकलन(p_buf, buf, p_buf_len);
	पूर्ण अन्यथा अणु
		pr_debug("%s", buf);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक transport_set_vpd_ident_type(काष्ठा t10_vpd *vpd, अचिन्हित अक्षर *page_83)
अणु
	/*
	 * The VPD identअगरier type..
	 *
	 * from spc3r23.pdf Section 7.6.3.1 Table 298
	 */
	vpd->device_identअगरier_type = (page_83[1] & 0x0f);
	वापस transport_dump_vpd_ident_type(vpd, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(transport_set_vpd_ident_type);

पूर्णांक transport_dump_vpd_ident(
	काष्ठा t10_vpd *vpd,
	अचिन्हित अक्षर *p_buf,
	पूर्णांक p_buf_len)
अणु
	अचिन्हित अक्षर buf[VPD_TMP_BUF_SIZE];
	पूर्णांक ret = 0;

	स_रखो(buf, 0, VPD_TMP_BUF_SIZE);

	चयन (vpd->device_identअगरier_code_set) अणु
	हाल 0x01: /* Binary */
		snम_लिखो(buf, माप(buf),
			"T10 VPD Binary Device Identifier: %s\n",
			&vpd->device_identअगरier[0]);
		अवरोध;
	हाल 0x02: /* ASCII */
		snम_लिखो(buf, माप(buf),
			"T10 VPD ASCII Device Identifier: %s\n",
			&vpd->device_identअगरier[0]);
		अवरोध;
	हाल 0x03: /* UTF-8 */
		snम_लिखो(buf, माप(buf),
			"T10 VPD UTF-8 Device Identifier: %s\n",
			&vpd->device_identअगरier[0]);
		अवरोध;
	शेष:
		प्र_लिखो(buf, "T10 VPD Device Identifier encoding unsupported:"
			" 0x%02x", vpd->device_identअगरier_code_set);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (p_buf)
		म_नकलन(p_buf, buf, p_buf_len);
	अन्यथा
		pr_debug("%s", buf);

	वापस ret;
पूर्ण

पूर्णांक
transport_set_vpd_ident(काष्ठा t10_vpd *vpd, अचिन्हित अक्षर *page_83)
अणु
	अटल स्थिर अक्षर hex_str[] = "0123456789abcdef";
	पूर्णांक j = 0, i = 4; /* offset to start of the identअगरier */

	/*
	 * The VPD Code Set (encoding)
	 *
	 * from spc3r23.pdf Section 7.6.3.1 Table 296
	 */
	vpd->device_identअगरier_code_set = (page_83[0] & 0x0f);
	चयन (vpd->device_identअगरier_code_set) अणु
	हाल 0x01: /* Binary */
		vpd->device_identअगरier[j++] =
				hex_str[vpd->device_identअगरier_type];
		जबतक (i < (4 + page_83[3])) अणु
			vpd->device_identअगरier[j++] =
				hex_str[(page_83[i] & 0xf0) >> 4];
			vpd->device_identअगरier[j++] =
				hex_str[page_83[i] & 0x0f];
			i++;
		पूर्ण
		अवरोध;
	हाल 0x02: /* ASCII */
	हाल 0x03: /* UTF-8 */
		जबतक (i < (4 + page_83[3]))
			vpd->device_identअगरier[j++] = page_83[i++];
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस transport_dump_vpd_ident(vpd, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(transport_set_vpd_ident);

अटल sense_reason_t
target_check_max_data_sg_nents(काष्ठा se_cmd *cmd, काष्ठा se_device *dev,
			       अचिन्हित पूर्णांक size)
अणु
	u32 mtl;

	अगर (!cmd->se_tfo->max_data_sg_nents)
		वापस TCM_NO_SENSE;
	/*
	 * Check अगर fabric enक्रमced maximum SGL entries per I/O descriptor
	 * exceeds se_cmd->data_length.  If true, set SCF_UNDERFLOW_BIT +
	 * residual_count and reduce original cmd->data_length to maximum
	 * length based on single PAGE_SIZE entry scatter-lists.
	 */
	mtl = (cmd->se_tfo->max_data_sg_nents * PAGE_SIZE);
	अगर (cmd->data_length > mtl) अणु
		/*
		 * If an existing CDB overflow is present, calculate new residual
		 * based on CDB size minus fabric maximum transfer length.
		 *
		 * If an existing CDB underflow is present, calculate new residual
		 * based on original cmd->data_length minus fabric maximum transfer
		 * length.
		 *
		 * Otherwise, set the underflow residual based on cmd->data_length
		 * minus fabric maximum transfer length.
		 */
		अगर (cmd->se_cmd_flags & SCF_OVERFLOW_BIT) अणु
			cmd->residual_count = (size - mtl);
		पूर्ण अन्यथा अगर (cmd->se_cmd_flags & SCF_UNDERFLOW_BIT) अणु
			u32 orig_dl = size + cmd->residual_count;
			cmd->residual_count = (orig_dl - mtl);
		पूर्ण अन्यथा अणु
			cmd->se_cmd_flags |= SCF_UNDERFLOW_BIT;
			cmd->residual_count = (cmd->data_length - mtl);
		पूर्ण
		cmd->data_length = mtl;
		/*
		 * Reset sbc_check_prot() calculated protection payload
		 * length based upon the new smaller MTL.
		 */
		अगर (cmd->prot_length) अणु
			u32 sectors = (mtl / dev->dev_attrib.block_size);
			cmd->prot_length = dev->prot_length * sectors;
		पूर्ण
	पूर्ण
	वापस TCM_NO_SENSE;
पूर्ण

/**
 * target_cmd_size_check - Check whether there will be a residual.
 * @cmd: SCSI command.
 * @size: Data buffer size derived from CDB. The data buffer size provided by
 *   the SCSI transport driver is available in @cmd->data_length.
 *
 * Compare the data buffer size from the CDB with the data buffer limit from the transport
 * header. Set @cmd->residual_count and SCF_OVERFLOW_BIT or SCF_UNDERFLOW_BIT अगर necessary.
 *
 * Note: target drivers set @cmd->data_length by calling __target_init_cmd().
 *
 * Return: TCM_NO_SENSE
 */
sense_reason_t
target_cmd_size_check(काष्ठा se_cmd *cmd, अचिन्हित पूर्णांक size)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	अगर (cmd->unknown_data_length) अणु
		cmd->data_length = size;
	पूर्ण अन्यथा अगर (size != cmd->data_length) अणु
		pr_warn_ratelimited("TARGET_CORE[%s]: Expected Transfer Length:"
			" %u does not match SCSI CDB Length: %u for SAM Opcode:"
			" 0x%02x\n", cmd->se_tfo->fabric_name,
				cmd->data_length, size, cmd->t_task_cdb[0]);
		/*
		 * For READ command क्रम the overflow हाल keep the existing
		 * fabric provided ->data_length. Otherwise क्रम the underflow
		 * हाल, reset ->data_length to the smaller SCSI expected data
		 * transfer length.
		 */
		अगर (size > cmd->data_length) अणु
			cmd->se_cmd_flags |= SCF_OVERFLOW_BIT;
			cmd->residual_count = (size - cmd->data_length);
		पूर्ण अन्यथा अणु
			cmd->se_cmd_flags |= SCF_UNDERFLOW_BIT;
			cmd->residual_count = (cmd->data_length - size);
			/*
			 * Do not truncate ->data_length क्रम WRITE command to
			 * dump all payload
			 */
			अगर (cmd->data_direction == DMA_FROM_DEVICE) अणु
				cmd->data_length = size;
			पूर्ण
		पूर्ण

		अगर (cmd->data_direction == DMA_TO_DEVICE) अणु
			अगर (cmd->se_cmd_flags & SCF_SCSI_DATA_CDB) अणु
				pr_err_ratelimited("Rejecting underflow/overflow"
						   " for WRITE data CDB\n");
				वापस TCM_INVALID_FIELD_IN_COMMAND_IU;
			पूर्ण
			/*
			 * Some fabric drivers like iscsi-target still expect to
			 * always reject overflow ग_लिखोs.  Reject this हाल until
			 * full fabric driver level support क्रम overflow ग_लिखोs
			 * is पूर्णांकroduced tree-wide.
			 */
			अगर (size > cmd->data_length) अणु
				pr_err_ratelimited("Rejecting overflow for"
						   " WRITE control CDB\n");
				वापस TCM_INVALID_CDB_FIELD;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस target_check_max_data_sg_nents(cmd, dev, size);

पूर्ण

/*
 * Used by fabric modules containing a local काष्ठा se_cmd within their
 * fabric dependent per I/O descriptor.
 *
 * Preserves the value of @cmd->tag.
 */
व्योम __target_init_cmd(
	काष्ठा se_cmd *cmd,
	स्थिर काष्ठा target_core_fabric_ops *tfo,
	काष्ठा se_session *se_sess,
	u32 data_length,
	पूर्णांक data_direction,
	पूर्णांक task_attr,
	अचिन्हित अक्षर *sense_buffer, u64 unpacked_lun)
अणु
	INIT_LIST_HEAD(&cmd->se_delayed_node);
	INIT_LIST_HEAD(&cmd->se_qf_node);
	INIT_LIST_HEAD(&cmd->state_list);
	init_completion(&cmd->t_transport_stop_comp);
	cmd->मुक्त_compl = शून्य;
	cmd->abrt_compl = शून्य;
	spin_lock_init(&cmd->t_state_lock);
	INIT_WORK(&cmd->work, शून्य);
	kref_init(&cmd->cmd_kref);

	cmd->t_task_cdb = &cmd->__t_task_cdb[0];
	cmd->se_tfo = tfo;
	cmd->se_sess = se_sess;
	cmd->data_length = data_length;
	cmd->data_direction = data_direction;
	cmd->sam_task_attr = task_attr;
	cmd->sense_buffer = sense_buffer;
	cmd->orig_fe_lun = unpacked_lun;

	अगर (!(cmd->se_cmd_flags & SCF_USE_CPUID))
		cmd->cpuid = raw_smp_processor_id();

	cmd->state_active = false;
पूर्ण
EXPORT_SYMBOL(__target_init_cmd);

अटल sense_reason_t
transport_check_alloc_task_attr(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	/*
	 * Check अगर SAM Task Attribute emulation is enabled क्रम this
	 * काष्ठा se_device storage object
	 */
	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH)
		वापस 0;

	अगर (cmd->sam_task_attr == TCM_ACA_TAG) अणु
		pr_debug("SAM Task Attribute ACA"
			" emulation is not supported\n");
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	वापस 0;
पूर्ण

sense_reason_t
target_cmd_init_cdb(काष्ठा se_cmd *cmd, अचिन्हित अक्षर *cdb, gfp_t gfp)
अणु
	sense_reason_t ret;

	/*
	 * Ensure that the received CDB is less than the max (252 + 8) bytes
	 * क्रम VARIABLE_LENGTH_CMD
	 */
	अगर (scsi_command_size(cdb) > SCSI_MAX_VARLEN_CDB_SIZE) अणु
		pr_err("Received SCSI CDB with command_size: %d that"
			" exceeds SCSI_MAX_VARLEN_CDB_SIZE: %d\n",
			scsi_command_size(cdb), SCSI_MAX_VARLEN_CDB_SIZE);
		ret = TCM_INVALID_CDB_FIELD;
		जाओ err;
	पूर्ण
	/*
	 * If the received CDB is larger than TCM_MAX_COMMAND_SIZE,
	 * allocate the additional extended CDB buffer now..  Otherwise
	 * setup the poपूर्णांकer from __t_task_cdb to t_task_cdb.
	 */
	अगर (scsi_command_size(cdb) > माप(cmd->__t_task_cdb)) अणु
		cmd->t_task_cdb = kzalloc(scsi_command_size(cdb), gfp);
		अगर (!cmd->t_task_cdb) अणु
			pr_err("Unable to allocate cmd->t_task_cdb"
				" %u > sizeof(cmd->__t_task_cdb): %lu ops\n",
				scsi_command_size(cdb),
				(अचिन्हित दीर्घ)माप(cmd->__t_task_cdb));
			ret = TCM_OUT_OF_RESOURCES;
			जाओ err;
		पूर्ण
	पूर्ण
	/*
	 * Copy the original CDB पूर्णांकo cmd->
	 */
	स_नकल(cmd->t_task_cdb, cdb, scsi_command_size(cdb));

	trace_target_sequencer_start(cmd);
	वापस 0;

err:
	/*
	 * Copy the CDB here to allow trace_target_cmd_complete() to
	 * prपूर्णांक the cdb to the trace buffers.
	 */
	स_नकल(cmd->t_task_cdb, cdb, min(scsi_command_size(cdb),
					 (अचिन्हित पूर्णांक)TCM_MAX_COMMAND_SIZE));
	वापस ret;
पूर्ण
EXPORT_SYMBOL(target_cmd_init_cdb);

sense_reason_t
target_cmd_parse_cdb(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	sense_reason_t ret;

	ret = dev->transport->parse_cdb(cmd);
	अगर (ret == TCM_UNSUPPORTED_SCSI_OPCODE)
		pr_warn_ratelimited("%s/%s: Unsupported SCSI Opcode 0x%02x, sending CHECK_CONDITION.\n",
				    cmd->se_tfo->fabric_name,
				    cmd->se_sess->se_node_acl->initiatorname,
				    cmd->t_task_cdb[0]);
	अगर (ret)
		वापस ret;

	ret = transport_check_alloc_task_attr(cmd);
	अगर (ret)
		वापस ret;

	cmd->se_cmd_flags |= SCF_SUPPORTED_SAM_OPCODE;
	atomic_दीर्घ_inc(&cmd->se_lun->lun_stats.cmd_pdus);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(target_cmd_parse_cdb);

/*
 * Used by fabric module frontends to queue tasks directly.
 * May only be used from process context.
 */
पूर्णांक transport_handle_cdb_direct(
	काष्ठा se_cmd *cmd)
अणु
	sense_reason_t ret;

	might_sleep();

	अगर (!cmd->se_lun) अणु
		dump_stack();
		pr_err("cmd->se_lun is NULL\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Set TRANSPORT_NEW_CMD state and CMD_T_ACTIVE to ensure that
	 * outstanding descriptors are handled correctly during shutकरोwn via
	 * transport_रुको_क्रम_tasks()
	 *
	 * Also, we करोn't take cmd->t_state_lock here as we only expect
	 * this to be called क्रम initial descriptor submission.
	 */
	cmd->t_state = TRANSPORT_NEW_CMD;
	cmd->transport_state |= CMD_T_ACTIVE;

	/*
	 * transport_generic_new_cmd() is alपढ़ोy handling QUEUE_FULL,
	 * so follow TRANSPORT_NEW_CMD processing thपढ़ो context usage
	 * and call transport_generic_request_failure() अगर necessary..
	 */
	ret = transport_generic_new_cmd(cmd);
	अगर (ret)
		transport_generic_request_failure(cmd, ret);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(transport_handle_cdb_direct);

sense_reason_t
transport_generic_map_mem_to_cmd(काष्ठा se_cmd *cmd, काष्ठा scatterlist *sgl,
		u32 sgl_count, काष्ठा scatterlist *sgl_bidi, u32 sgl_bidi_count)
अणु
	अगर (!sgl || !sgl_count)
		वापस 0;

	/*
	 * Reject SCSI data overflow with map_mem_to_cmd() as incoming
	 * scatterlists alपढ़ोy have been set to follow what the fabric
	 * passes क्रम the original expected data transfer length.
	 */
	अगर (cmd->se_cmd_flags & SCF_OVERFLOW_BIT) अणु
		pr_warn("Rejecting SCSI DATA overflow for fabric using"
			" SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC\n");
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	cmd->t_data_sg = sgl;
	cmd->t_data_nents = sgl_count;
	cmd->t_bidi_data_sg = sgl_bidi;
	cmd->t_bidi_data_nents = sgl_bidi_count;

	cmd->se_cmd_flags |= SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC;
	वापस 0;
पूर्ण

/**
 * target_init_cmd - initialize se_cmd
 * @se_cmd: command descriptor to init
 * @se_sess: associated se_sess क्रम endpoपूर्णांक
 * @sense: poपूर्णांकer to SCSI sense buffer
 * @unpacked_lun: unpacked LUN to reference क्रम काष्ठा se_lun
 * @data_length: fabric expected data transfer length
 * @task_attr: SAM task attribute
 * @data_dir: DMA data direction
 * @flags: flags क्रम command submission from target_sc_flags_tables
 *
 * Task tags are supported अगर the caller has set @se_cmd->tag.
 *
 * Returns:
 *	- less than zero to संकेत active I/O shutकरोwn failure.
 *	- zero on success.
 *
 * If the fabric driver calls target_stop_session, then it must check the
 * वापस code and handle failures. This will never fail क्रम other drivers,
 * and the वापस code can be ignored.
 */
पूर्णांक target_init_cmd(काष्ठा se_cmd *se_cmd, काष्ठा se_session *se_sess,
		    अचिन्हित अक्षर *sense, u64 unpacked_lun,
		    u32 data_length, पूर्णांक task_attr, पूर्णांक data_dir, पूर्णांक flags)
अणु
	काष्ठा se_portal_group *se_tpg;

	se_tpg = se_sess->se_tpg;
	BUG_ON(!se_tpg);
	BUG_ON(se_cmd->se_tfo || se_cmd->se_sess);

	अगर (flags & TARGET_SCF_USE_CPUID)
		se_cmd->se_cmd_flags |= SCF_USE_CPUID;
	/*
	 * Signal bidirectional data payloads to target-core
	 */
	अगर (flags & TARGET_SCF_BIDI_OP)
		se_cmd->se_cmd_flags |= SCF_BIDI;

	अगर (flags & TARGET_SCF_UNKNOWN_SIZE)
		se_cmd->unknown_data_length = 1;
	/*
	 * Initialize se_cmd क्रम target operation.  From this poपूर्णांक
	 * exceptions are handled by sending exception status via
	 * target_core_fabric_ops->queue_status() callback
	 */
	__target_init_cmd(se_cmd, se_tpg->se_tpg_tfo, se_sess, data_length,
			  data_dir, task_attr, sense, unpacked_lun);

	/*
	 * Obtain काष्ठा se_cmd->cmd_kref reference. A second kref_get here is
	 * necessary क्रम fabrics using TARGET_SCF_ACK_KREF that expect a second
	 * kref_put() to happen during fabric packet acknowledgement.
	 */
	वापस target_get_sess_cmd(se_cmd, flags & TARGET_SCF_ACK_KREF);
पूर्ण
EXPORT_SYMBOL_GPL(target_init_cmd);

/**
 * target_submit_prep - prepare cmd क्रम submission
 * @se_cmd: command descriptor to prep
 * @cdb: poपूर्णांकer to SCSI CDB
 * @sgl: काष्ठा scatterlist memory क्रम unidirectional mapping
 * @sgl_count: scatterlist count क्रम unidirectional mapping
 * @sgl_bidi: काष्ठा scatterlist memory क्रम bidirectional READ mapping
 * @sgl_bidi_count: scatterlist count क्रम bidirectional READ mapping
 * @sgl_prot: काष्ठा scatterlist memory protection inक्रमmation
 * @sgl_prot_count: scatterlist count क्रम protection inक्रमmation
 * @gfp: gfp allocation type
 *
 * Returns:
 *	- less than zero to संकेत failure.
 *	- zero on success.
 *
 * If failure is वापसed, lio will the callers queue_status to complete
 * the cmd.
 */
पूर्णांक target_submit_prep(काष्ठा se_cmd *se_cmd, अचिन्हित अक्षर *cdb,
		       काष्ठा scatterlist *sgl, u32 sgl_count,
		       काष्ठा scatterlist *sgl_bidi, u32 sgl_bidi_count,
		       काष्ठा scatterlist *sgl_prot, u32 sgl_prot_count,
		       gfp_t gfp)
अणु
	sense_reason_t rc;

	rc = target_cmd_init_cdb(se_cmd, cdb, gfp);
	अगर (rc)
		जाओ send_cc_direct;

	/*
	 * Locate se_lun poपूर्णांकer and attach it to काष्ठा se_cmd
	 */
	rc = transport_lookup_cmd_lun(se_cmd);
	अगर (rc)
		जाओ send_cc_direct;

	rc = target_cmd_parse_cdb(se_cmd);
	अगर (rc != 0)
		जाओ generic_fail;

	/*
	 * Save poपूर्णांकers क्रम SGLs containing protection inक्रमmation,
	 * अगर present.
	 */
	अगर (sgl_prot_count) अणु
		se_cmd->t_prot_sg = sgl_prot;
		se_cmd->t_prot_nents = sgl_prot_count;
		se_cmd->se_cmd_flags |= SCF_PASSTHROUGH_PROT_SG_TO_MEM_NOALLOC;
	पूर्ण

	/*
	 * When a non zero sgl_count has been passed perक्रमm SGL passthrough
	 * mapping क्रम pre-allocated fabric memory instead of having target
	 * core perक्रमm an पूर्णांकernal SGL allocation..
	 */
	अगर (sgl_count != 0) अणु
		BUG_ON(!sgl);

		rc = transport_generic_map_mem_to_cmd(se_cmd, sgl, sgl_count,
				sgl_bidi, sgl_bidi_count);
		अगर (rc != 0)
			जाओ generic_fail;
	पूर्ण

	वापस 0;

send_cc_direct:
	transport_send_check_condition_and_sense(se_cmd, rc, 0);
	target_put_sess_cmd(se_cmd);
	वापस -EIO;

generic_fail:
	transport_generic_request_failure(se_cmd, rc);
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(target_submit_prep);

/**
 * target_submit - perक्रमm final initialization and submit cmd to LIO core
 * @se_cmd: command descriptor to submit
 *
 * target_submit_prep must have been called on the cmd, and this must be
 * called from process context.
 */
व्योम target_submit(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा scatterlist *sgl = se_cmd->t_data_sg;
	अचिन्हित अक्षर *buf = शून्य;

	might_sleep();

	अगर (se_cmd->t_data_nents != 0) अणु
		BUG_ON(!sgl);
		/*
		 * A work-around क्रम tcm_loop as some userspace code via
		 * scsi-generic करो not स_रखो their associated पढ़ो buffers,
		 * so go ahead and करो that here क्रम type non-data CDBs.  Also
		 * note that this is currently guaranteed to be a single SGL
		 * क्रम this हाल by target core in target_setup_cmd_from_cdb()
		 * -> transport_generic_cmd_sequencer().
		 */
		अगर (!(se_cmd->se_cmd_flags & SCF_SCSI_DATA_CDB) &&
		     se_cmd->data_direction == DMA_FROM_DEVICE) अणु
			अगर (sgl)
				buf = kmap(sg_page(sgl)) + sgl->offset;

			अगर (buf) अणु
				स_रखो(buf, 0, sgl->length);
				kunmap(sg_page(sgl));
			पूर्ण
		पूर्ण

	पूर्ण

	/*
	 * Check अगर we need to delay processing because of ALUA
	 * Active/NonOptimized primary access state..
	 */
	core_alua_check_nonop_delay(se_cmd);

	transport_handle_cdb_direct(se_cmd);
पूर्ण
EXPORT_SYMBOL_GPL(target_submit);

/**
 * target_submit_cmd - lookup unpacked lun and submit uninitialized se_cmd
 *
 * @se_cmd: command descriptor to submit
 * @se_sess: associated se_sess क्रम endpoपूर्णांक
 * @cdb: poपूर्णांकer to SCSI CDB
 * @sense: poपूर्णांकer to SCSI sense buffer
 * @unpacked_lun: unpacked LUN to reference क्रम काष्ठा se_lun
 * @data_length: fabric expected data transfer length
 * @task_attr: SAM task attribute
 * @data_dir: DMA data direction
 * @flags: flags क्रम command submission from target_sc_flags_tables
 *
 * Task tags are supported अगर the caller has set @se_cmd->tag.
 *
 * This may only be called from process context, and also currently
 * assumes पूर्णांकernal allocation of fabric payload buffer by target-core.
 *
 * It also assumes पूर्णांकeral target core SGL memory allocation.
 *
 * This function must only be used by drivers that करो their own
 * sync during shutकरोwn and करोes not use target_stop_session. If there
 * is a failure this function will call पूर्णांकo the fabric driver's
 * queue_status with a CHECK_CONDITION.
 */
व्योम target_submit_cmd(काष्ठा se_cmd *se_cmd, काष्ठा se_session *se_sess,
		अचिन्हित अक्षर *cdb, अचिन्हित अक्षर *sense, u64 unpacked_lun,
		u32 data_length, पूर्णांक task_attr, पूर्णांक data_dir, पूर्णांक flags)
अणु
	पूर्णांक rc;

	rc = target_init_cmd(se_cmd, se_sess, sense, unpacked_lun, data_length,
			     task_attr, data_dir, flags);
	WARN(rc, "Invalid target_submit_cmd use. Driver must not use target_stop_session or call target_init_cmd directly.\n");
	अगर (rc)
		वापस;

	अगर (target_submit_prep(se_cmd, cdb, शून्य, 0, शून्य, 0, शून्य, 0,
			       GFP_KERNEL))
		वापस;

	target_submit(se_cmd);
पूर्ण
EXPORT_SYMBOL(target_submit_cmd);


अटल काष्ठा se_dev_plug *target_plug_device(काष्ठा se_device *se_dev)
अणु
	काष्ठा se_dev_plug *se_plug;

	अगर (!se_dev->transport->plug_device)
		वापस शून्य;

	se_plug = se_dev->transport->plug_device(se_dev);
	अगर (!se_plug)
		वापस शून्य;

	se_plug->se_dev = se_dev;
	/*
	 * We have a ref to the lun at this poपूर्णांक, but the cmds could
	 * complete beक्रमe we unplug, so grab a ref to the se_device so we
	 * can call back पूर्णांकo the backend.
	 */
	config_group_get(&se_dev->dev_group);
	वापस se_plug;
पूर्ण

अटल व्योम target_unplug_device(काष्ठा se_dev_plug *se_plug)
अणु
	काष्ठा se_device *se_dev = se_plug->se_dev;

	se_dev->transport->unplug_device(se_plug);
	config_group_put(&se_dev->dev_group);
पूर्ण

व्योम target_queued_submit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा se_cmd_queue *sq = container_of(work, काष्ठा se_cmd_queue, work);
	काष्ठा se_cmd *se_cmd, *next_cmd;
	काष्ठा se_dev_plug *se_plug = शून्य;
	काष्ठा se_device *se_dev = शून्य;
	काष्ठा llist_node *cmd_list;

	cmd_list = llist_del_all(&sq->cmd_list);
	अगर (!cmd_list)
		/* Previous call took what we were queued to submit */
		वापस;

	cmd_list = llist_reverse_order(cmd_list);
	llist_क्रम_each_entry_safe(se_cmd, next_cmd, cmd_list, se_cmd_list) अणु
		अगर (!se_dev) अणु
			se_dev = se_cmd->se_dev;
			se_plug = target_plug_device(se_dev);
		पूर्ण

		target_submit(se_cmd);
	पूर्ण

	अगर (se_plug)
		target_unplug_device(se_plug);
पूर्ण

/**
 * target_queue_submission - queue the cmd to run on the LIO workqueue
 * @se_cmd: command descriptor to submit
 */
व्योम target_queue_submission(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा se_device *se_dev = se_cmd->se_dev;
	पूर्णांक cpu = se_cmd->cpuid;
	काष्ठा se_cmd_queue *sq;

	sq = &se_dev->queues[cpu].sq;
	llist_add(&se_cmd->se_cmd_list, &sq->cmd_list);
	queue_work_on(cpu, target_submission_wq, &sq->work);
पूर्ण
EXPORT_SYMBOL_GPL(target_queue_submission);

अटल व्योम target_complete_पंचांगr_failure(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा se_cmd *se_cmd = container_of(work, काष्ठा se_cmd, work);

	se_cmd->se_पंचांगr_req->response = TMR_LUN_DOES_NOT_EXIST;
	se_cmd->se_tfo->queue_पंचांग_rsp(se_cmd);

	transport_lun_हटाओ_cmd(se_cmd);
	transport_cmd_check_stop_to_fabric(se_cmd);
पूर्ण

/**
 * target_submit_पंचांगr - lookup unpacked lun and submit uninitialized se_cmd
 *                     क्रम TMR CDBs
 *
 * @se_cmd: command descriptor to submit
 * @se_sess: associated se_sess क्रम endpoपूर्णांक
 * @sense: poपूर्णांकer to SCSI sense buffer
 * @unpacked_lun: unpacked LUN to reference क्रम काष्ठा se_lun
 * @fabric_पंचांगr_ptr: fabric context क्रम TMR req
 * @पंचांग_type: Type of TM request
 * @gfp: gfp type क्रम caller
 * @tag: referenced task tag क्रम TMR_ABORT_TASK
 * @flags: submit cmd flags
 *
 * Callable from all contexts.
 **/

पूर्णांक target_submit_पंचांगr(काष्ठा se_cmd *se_cmd, काष्ठा se_session *se_sess,
		अचिन्हित अक्षर *sense, u64 unpacked_lun,
		व्योम *fabric_पंचांगr_ptr, अचिन्हित अक्षर पंचांग_type,
		gfp_t gfp, u64 tag, पूर्णांक flags)
अणु
	काष्ठा se_portal_group *se_tpg;
	पूर्णांक ret;

	se_tpg = se_sess->se_tpg;
	BUG_ON(!se_tpg);

	__target_init_cmd(se_cmd, se_tpg->se_tpg_tfo, se_sess,
			  0, DMA_NONE, TCM_SIMPLE_TAG, sense, unpacked_lun);
	/*
	 * FIXME: Currently expect caller to handle se_cmd->se_पंचांगr_req
	 * allocation failure.
	 */
	ret = core_पंचांगr_alloc_req(se_cmd, fabric_पंचांगr_ptr, पंचांग_type, gfp);
	अगर (ret < 0)
		वापस -ENOMEM;

	अगर (पंचांग_type == TMR_ABORT_TASK)
		se_cmd->se_पंचांगr_req->ref_task_tag = tag;

	/* See target_submit_cmd क्रम commentary */
	ret = target_get_sess_cmd(se_cmd, flags & TARGET_SCF_ACK_KREF);
	अगर (ret) अणु
		core_पंचांगr_release_req(se_cmd->se_पंचांगr_req);
		वापस ret;
	पूर्ण

	ret = transport_lookup_पंचांगr_lun(se_cmd);
	अगर (ret)
		जाओ failure;

	transport_generic_handle_पंचांगr(se_cmd);
	वापस 0;

	/*
	 * For callback during failure handling, push this work off
	 * to process context with TMR_LUN_DOES_NOT_EXIST status.
	 */
failure:
	INIT_WORK(&se_cmd->work, target_complete_पंचांगr_failure);
	schedule_work(&se_cmd->work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(target_submit_पंचांगr);

/*
 * Handle SAM-esque emulation क्रम generic transport request failures.
 */
व्योम transport_generic_request_failure(काष्ठा se_cmd *cmd,
		sense_reason_t sense_reason)
अणु
	पूर्णांक ret = 0, post_ret;

	pr_debug("-----[ Storage Engine Exception; sense_reason %d\n",
		 sense_reason);
	target_show_cmd("-----[ ", cmd);

	/*
	 * For SAM Task Attribute emulation क्रम failed काष्ठा se_cmd
	 */
	transport_complete_task_attr(cmd);

	अगर (cmd->transport_complete_callback)
		cmd->transport_complete_callback(cmd, false, &post_ret);

	अगर (cmd->transport_state & CMD_T_ABORTED) अणु
		INIT_WORK(&cmd->work, target_पात_work);
		queue_work(target_completion_wq, &cmd->work);
		वापस;
	पूर्ण

	चयन (sense_reason) अणु
	हाल TCM_NON_EXISTENT_LUN:
	हाल TCM_UNSUPPORTED_SCSI_OPCODE:
	हाल TCM_INVALID_CDB_FIELD:
	हाल TCM_INVALID_PARAMETER_LIST:
	हाल TCM_PARAMETER_LIST_LENGTH_ERROR:
	हाल TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE:
	हाल TCM_UNKNOWN_MODE_PAGE:
	हाल TCM_WRITE_PROTECTED:
	हाल TCM_ADDRESS_OUT_OF_RANGE:
	हाल TCM_CHECK_CONDITION_ABORT_CMD:
	हाल TCM_CHECK_CONDITION_UNIT_ATTENTION:
	हाल TCM_CHECK_CONDITION_NOT_READY:
	हाल TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED:
	हाल TCM_LOGICAL_BLOCK_APP_TAG_CHECK_FAILED:
	हाल TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED:
	हाल TCM_COPY_TARGET_DEVICE_NOT_REACHABLE:
	हाल TCM_TOO_MANY_TARGET_DESCS:
	हाल TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE:
	हाल TCM_TOO_MANY_SEGMENT_DESCS:
	हाल TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE:
	हाल TCM_INVALID_FIELD_IN_COMMAND_IU:
		अवरोध;
	हाल TCM_OUT_OF_RESOURCES:
		cmd->scsi_status = SAM_STAT_TASK_SET_FULL;
		जाओ queue_status;
	हाल TCM_LUN_BUSY:
		cmd->scsi_status = SAM_STAT_BUSY;
		जाओ queue_status;
	हाल TCM_RESERVATION_CONFLICT:
		/*
		 * No SENSE Data payload क्रम this हाल, set SCSI Status
		 * and queue the response to $FABRIC_MOD.
		 *
		 * Uses linux/include/scsi/scsi.h SAM status codes defs
		 */
		cmd->scsi_status = SAM_STAT_RESERVATION_CONFLICT;
		/*
		 * For UA Interlock Code 11b, a RESERVATION CONFLICT will
		 * establish a UNIT ATTENTION with PREVIOUS RESERVATION
		 * CONFLICT STATUS.
		 *
		 * See spc4r17, section 7.4.6 Control Mode Page, Table 349
		 */
		अगर (cmd->se_sess &&
		    cmd->se_dev->dev_attrib.emulate_ua_पूर्णांकlck_ctrl
					== TARGET_UA_INTLCK_CTRL_ESTABLISH_UA) अणु
			target_ua_allocate_lun(cmd->se_sess->se_node_acl,
					       cmd->orig_fe_lun, 0x2C,
					ASCQ_2CH_PREVIOUS_RESERVATION_CONFLICT_STATUS);
		पूर्ण

		जाओ queue_status;
	शेष:
		pr_err("Unknown transport error for CDB 0x%02x: %d\n",
			cmd->t_task_cdb[0], sense_reason);
		sense_reason = TCM_UNSUPPORTED_SCSI_OPCODE;
		अवरोध;
	पूर्ण

	ret = transport_send_check_condition_and_sense(cmd, sense_reason, 0);
	अगर (ret)
		जाओ queue_full;

check_stop:
	transport_lun_हटाओ_cmd(cmd);
	transport_cmd_check_stop_to_fabric(cmd);
	वापस;

queue_status:
	trace_target_cmd_complete(cmd);
	ret = cmd->se_tfo->queue_status(cmd);
	अगर (!ret)
		जाओ check_stop;
queue_full:
	transport_handle_queue_full(cmd, cmd->se_dev, ret, false);
पूर्ण
EXPORT_SYMBOL(transport_generic_request_failure);

व्योम __target_execute_cmd(काष्ठा se_cmd *cmd, bool करो_checks)
अणु
	sense_reason_t ret;

	अगर (!cmd->execute_cmd) अणु
		ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		जाओ err;
	पूर्ण
	अगर (करो_checks) अणु
		/*
		 * Check क्रम an existing UNIT ATTENTION condition after
		 * target_handle_task_attr() has करोne SAM task attr
		 * checking, and possibly have alपढ़ोy defered execution
		 * out to target_restart_delayed_cmds() context.
		 */
		ret = target_scsi3_ua_check(cmd);
		अगर (ret)
			जाओ err;

		ret = target_alua_state_check(cmd);
		अगर (ret)
			जाओ err;

		ret = target_check_reservation(cmd);
		अगर (ret) अणु
			cmd->scsi_status = SAM_STAT_RESERVATION_CONFLICT;
			जाओ err;
		पूर्ण
	पूर्ण

	ret = cmd->execute_cmd(cmd);
	अगर (!ret)
		वापस;
err:
	spin_lock_irq(&cmd->t_state_lock);
	cmd->transport_state &= ~CMD_T_SENT;
	spin_unlock_irq(&cmd->t_state_lock);

	transport_generic_request_failure(cmd, ret);
पूर्ण

अटल पूर्णांक target_ग_लिखो_prot_action(काष्ठा se_cmd *cmd)
अणु
	u32 sectors;
	/*
	 * Perक्रमm WRITE_INSERT of PI using software emulation when backend
	 * device has PI enabled, अगर the transport has not alपढ़ोy generated
	 * PI using hardware WRITE_INSERT offload.
	 */
	चयन (cmd->prot_op) अणु
	हाल TARGET_PROT_DOUT_INSERT:
		अगर (!(cmd->se_sess->sup_prot_ops & TARGET_PROT_DOUT_INSERT))
			sbc_dअगर_generate(cmd);
		अवरोध;
	हाल TARGET_PROT_DOUT_STRIP:
		अगर (cmd->se_sess->sup_prot_ops & TARGET_PROT_DOUT_STRIP)
			अवरोध;

		sectors = cmd->data_length >> ilog2(cmd->se_dev->dev_attrib.block_size);
		cmd->pi_err = sbc_dअगर_verअगरy(cmd, cmd->t_task_lba,
					     sectors, 0, cmd->t_prot_sg, 0);
		अगर (unlikely(cmd->pi_err)) अणु
			spin_lock_irq(&cmd->t_state_lock);
			cmd->transport_state &= ~CMD_T_SENT;
			spin_unlock_irq(&cmd->t_state_lock);
			transport_generic_request_failure(cmd, cmd->pi_err);
			वापस -1;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool target_handle_task_attr(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH)
		वापस false;

	cmd->se_cmd_flags |= SCF_TASK_ATTR_SET;

	/*
	 * Check क्रम the existence of HEAD_OF_QUEUE, and अगर true वापस 1
	 * to allow the passed काष्ठा se_cmd list of tasks to the front of the list.
	 */
	चयन (cmd->sam_task_attr) अणु
	हाल TCM_HEAD_TAG:
		pr_debug("Added HEAD_OF_QUEUE for CDB: 0x%02x\n",
			 cmd->t_task_cdb[0]);
		वापस false;
	हाल TCM_ORDERED_TAG:
		atomic_inc_mb(&dev->dev_ordered_sync);

		pr_debug("Added ORDERED for CDB: 0x%02x to ordered list\n",
			 cmd->t_task_cdb[0]);

		/*
		 * Execute an ORDERED command अगर no other older commands
		 * exist that need to be completed first.
		 */
		अगर (!atomic_पढ़ो(&dev->simple_cmds))
			वापस false;
		अवरोध;
	शेष:
		/*
		 * For SIMPLE and UNTAGGED Task Attribute commands
		 */
		atomic_inc_mb(&dev->simple_cmds);
		अवरोध;
	पूर्ण

	अगर (atomic_पढ़ो(&dev->dev_ordered_sync) == 0)
		वापस false;

	spin_lock(&dev->delayed_cmd_lock);
	list_add_tail(&cmd->se_delayed_node, &dev->delayed_cmd_list);
	spin_unlock(&dev->delayed_cmd_lock);

	pr_debug("Added CDB: 0x%02x Task Attr: 0x%02x to delayed CMD listn",
		cmd->t_task_cdb[0], cmd->sam_task_attr);
	वापस true;
पूर्ण

व्योम target_execute_cmd(काष्ठा se_cmd *cmd)
अणु
	/*
	 * Determine अगर frontend context caller is requesting the stopping of
	 * this command क्रम frontend exceptions.
	 *
	 * If the received CDB has alपढ़ोy been पातed stop processing it here.
	 */
	अगर (target_cmd_पूर्णांकerrupted(cmd))
		वापस;

	spin_lock_irq(&cmd->t_state_lock);
	cmd->t_state = TRANSPORT_PROCESSING;
	cmd->transport_state |= CMD_T_ACTIVE | CMD_T_SENT;
	spin_unlock_irq(&cmd->t_state_lock);

	अगर (target_ग_लिखो_prot_action(cmd))
		वापस;

	अगर (target_handle_task_attr(cmd)) अणु
		spin_lock_irq(&cmd->t_state_lock);
		cmd->transport_state &= ~CMD_T_SENT;
		spin_unlock_irq(&cmd->t_state_lock);
		वापस;
	पूर्ण

	__target_execute_cmd(cmd, true);
पूर्ण
EXPORT_SYMBOL(target_execute_cmd);

/*
 * Process all commands up to the last received ORDERED task attribute which
 * requires another blocking boundary
 */
अटल व्योम target_restart_delayed_cmds(काष्ठा se_device *dev)
अणु
	क्रम (;;) अणु
		काष्ठा se_cmd *cmd;

		spin_lock(&dev->delayed_cmd_lock);
		अगर (list_empty(&dev->delayed_cmd_list)) अणु
			spin_unlock(&dev->delayed_cmd_lock);
			अवरोध;
		पूर्ण

		cmd = list_entry(dev->delayed_cmd_list.next,
				 काष्ठा se_cmd, se_delayed_node);
		list_del(&cmd->se_delayed_node);
		spin_unlock(&dev->delayed_cmd_lock);

		cmd->transport_state |= CMD_T_SENT;

		__target_execute_cmd(cmd, true);

		अगर (cmd->sam_task_attr == TCM_ORDERED_TAG)
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Called from I/O completion to determine which करोrmant/delayed
 * and ordered cmds need to have their tasks added to the execution queue.
 */
अटल व्योम transport_complete_task_attr(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;

	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH)
		वापस;

	अगर (!(cmd->se_cmd_flags & SCF_TASK_ATTR_SET))
		जाओ restart;

	अगर (cmd->sam_task_attr == TCM_SIMPLE_TAG) अणु
		atomic_dec_mb(&dev->simple_cmds);
		dev->dev_cur_ordered_id++;
	पूर्ण अन्यथा अगर (cmd->sam_task_attr == TCM_HEAD_TAG) अणु
		dev->dev_cur_ordered_id++;
		pr_debug("Incremented dev_cur_ordered_id: %u for HEAD_OF_QUEUE\n",
			 dev->dev_cur_ordered_id);
	पूर्ण अन्यथा अगर (cmd->sam_task_attr == TCM_ORDERED_TAG) अणु
		atomic_dec_mb(&dev->dev_ordered_sync);

		dev->dev_cur_ordered_id++;
		pr_debug("Incremented dev_cur_ordered_id: %u for ORDERED\n",
			 dev->dev_cur_ordered_id);
	पूर्ण
	cmd->se_cmd_flags &= ~SCF_TASK_ATTR_SET;

restart:
	target_restart_delayed_cmds(dev);
पूर्ण

अटल व्योम transport_complete_qf(काष्ठा se_cmd *cmd)
अणु
	पूर्णांक ret = 0;

	transport_complete_task_attr(cmd);
	/*
	 * If a fabric driver ->ग_लिखो_pending() or ->queue_data_in() callback
	 * has वापसed neither -ENOMEM or -EAGAIN, assume it's fatal and
	 * the same callbacks should not be retried.  Return CHECK_CONDITION
	 * अगर a scsi_status is not alपढ़ोy set.
	 *
	 * If a fabric driver ->queue_status() has वापसed non zero, always
	 * keep retrying no matter what..
	 */
	अगर (cmd->t_state == TRANSPORT_COMPLETE_QF_ERR) अणु
		अगर (cmd->scsi_status)
			जाओ queue_status;

		translate_sense_reason(cmd, TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE);
		जाओ queue_status;
	पूर्ण

	/*
	 * Check अगर we need to send a sense buffer from
	 * the काष्ठा se_cmd in question. We करो NOT want
	 * to take this path of the IO has been marked as
	 * needing to be treated like a "normal read". This
	 * is the हाल अगर it's a tape पढ़ो, and either the
	 * FM, EOM, or ILI bits are set, but there is no
	 * sense data.
	 */
	अगर (!(cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL) &&
	    cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE)
		जाओ queue_status;

	चयन (cmd->data_direction) अणु
	हाल DMA_FROM_DEVICE:
		/* queue status अगर not treating this as a normal पढ़ो */
		अगर (cmd->scsi_status &&
		    !(cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL))
			जाओ queue_status;

		trace_target_cmd_complete(cmd);
		ret = cmd->se_tfo->queue_data_in(cmd);
		अवरोध;
	हाल DMA_TO_DEVICE:
		अगर (cmd->se_cmd_flags & SCF_BIDI) अणु
			ret = cmd->se_tfo->queue_data_in(cmd);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल DMA_NONE:
queue_status:
		trace_target_cmd_complete(cmd);
		ret = cmd->se_tfo->queue_status(cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret < 0) अणु
		transport_handle_queue_full(cmd, cmd->se_dev, ret, false);
		वापस;
	पूर्ण
	transport_lun_हटाओ_cmd(cmd);
	transport_cmd_check_stop_to_fabric(cmd);
पूर्ण

अटल व्योम transport_handle_queue_full(काष्ठा se_cmd *cmd, काष्ठा se_device *dev,
					पूर्णांक err, bool ग_लिखो_pending)
अणु
	/*
	 * -EAGAIN or -ENOMEM संकेतs retry of ->ग_लिखो_pending() and/or
	 * ->queue_data_in() callbacks from new process context.
	 *
	 * Otherwise क्रम other errors, transport_complete_qf() will send
	 * CHECK_CONDITION via ->queue_status() instead of attempting to
	 * retry associated fabric driver data-transfer callbacks.
	 */
	अगर (err == -EAGAIN || err == -ENOMEM) अणु
		cmd->t_state = (ग_लिखो_pending) ? TRANSPORT_COMPLETE_QF_WP :
						 TRANSPORT_COMPLETE_QF_OK;
	पूर्ण अन्यथा अणु
		pr_warn_ratelimited("Got unknown fabric queue status: %d\n", err);
		cmd->t_state = TRANSPORT_COMPLETE_QF_ERR;
	पूर्ण

	spin_lock_irq(&dev->qf_cmd_lock);
	list_add_tail(&cmd->se_qf_node, &cmd->se_dev->qf_cmd_list);
	atomic_inc_mb(&dev->dev_qf_count);
	spin_unlock_irq(&cmd->se_dev->qf_cmd_lock);

	schedule_work(&cmd->se_dev->qf_work_queue);
पूर्ण

अटल bool target_पढ़ो_prot_action(काष्ठा se_cmd *cmd)
अणु
	चयन (cmd->prot_op) अणु
	हाल TARGET_PROT_DIN_STRIP:
		अगर (!(cmd->se_sess->sup_prot_ops & TARGET_PROT_DIN_STRIP)) अणु
			u32 sectors = cmd->data_length >>
				  ilog2(cmd->se_dev->dev_attrib.block_size);

			cmd->pi_err = sbc_dअगर_verअगरy(cmd, cmd->t_task_lba,
						     sectors, 0, cmd->t_prot_sg,
						     0);
			अगर (cmd->pi_err)
				वापस true;
		पूर्ण
		अवरोध;
	हाल TARGET_PROT_DIN_INSERT:
		अगर (cmd->se_sess->sup_prot_ops & TARGET_PROT_DIN_INSERT)
			अवरोध;

		sbc_dअगर_generate(cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम target_complete_ok_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा se_cmd *cmd = container_of(work, काष्ठा se_cmd, work);
	पूर्णांक ret;

	/*
	 * Check अगर we need to move delayed/करोrmant tasks from cmds on the
	 * delayed execution list after a HEAD_OF_QUEUE or ORDERED Task
	 * Attribute.
	 */
	transport_complete_task_attr(cmd);

	/*
	 * Check to schedule QUEUE_FULL work, or execute an existing
	 * cmd->transport_qf_callback()
	 */
	अगर (atomic_पढ़ो(&cmd->se_dev->dev_qf_count) != 0)
		schedule_work(&cmd->se_dev->qf_work_queue);

	/*
	 * Check अगर we need to send a sense buffer from
	 * the काष्ठा se_cmd in question. We करो NOT want
	 * to take this path of the IO has been marked as
	 * needing to be treated like a "normal read". This
	 * is the हाल अगर it's a tape पढ़ो, and either the
	 * FM, EOM, or ILI bits are set, but there is no
	 * sense data.
	 */
	अगर (!(cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL) &&
	    cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE) अणु
		WARN_ON(!cmd->scsi_status);
		ret = transport_send_check_condition_and_sense(
					cmd, 0, 1);
		अगर (ret)
			जाओ queue_full;

		transport_lun_हटाओ_cmd(cmd);
		transport_cmd_check_stop_to_fabric(cmd);
		वापस;
	पूर्ण
	/*
	 * Check क्रम a callback, used by amongst other things
	 * XDWRITE_READ_10 and COMPARE_AND_WRITE emulation.
	 */
	अगर (cmd->transport_complete_callback) अणु
		sense_reason_t rc;
		bool caw = (cmd->se_cmd_flags & SCF_COMPARE_AND_WRITE);
		bool zero_dl = !(cmd->data_length);
		पूर्णांक post_ret = 0;

		rc = cmd->transport_complete_callback(cmd, true, &post_ret);
		अगर (!rc && !post_ret) अणु
			अगर (caw && zero_dl)
				जाओ queue_rsp;

			वापस;
		पूर्ण अन्यथा अगर (rc) अणु
			ret = transport_send_check_condition_and_sense(cmd,
						rc, 0);
			अगर (ret)
				जाओ queue_full;

			transport_lun_हटाओ_cmd(cmd);
			transport_cmd_check_stop_to_fabric(cmd);
			वापस;
		पूर्ण
	पूर्ण

queue_rsp:
	चयन (cmd->data_direction) अणु
	हाल DMA_FROM_DEVICE:
		/*
		 * अगर this is a READ-type IO, but SCSI status
		 * is set, then skip वापसing data and just
		 * वापस the status -- unless this IO is marked
		 * as needing to be treated as a normal पढ़ो,
		 * in which हाल we want to go ahead and वापस
		 * the data. This happens, क्रम example, क्रम tape
		 * पढ़ोs with the FM, EOM, or ILI bits set, with
		 * no sense data.
		 */
		अगर (cmd->scsi_status &&
		    !(cmd->se_cmd_flags & SCF_TREAT_READ_AS_NORMAL))
			जाओ queue_status;

		atomic_दीर्घ_add(cmd->data_length,
				&cmd->se_lun->lun_stats.tx_data_octets);
		/*
		 * Perक्रमm READ_STRIP of PI using software emulation when
		 * backend had PI enabled, अगर the transport will not be
		 * perक्रमming hardware READ_STRIP offload.
		 */
		अगर (target_पढ़ो_prot_action(cmd)) अणु
			ret = transport_send_check_condition_and_sense(cmd,
						cmd->pi_err, 0);
			अगर (ret)
				जाओ queue_full;

			transport_lun_हटाओ_cmd(cmd);
			transport_cmd_check_stop_to_fabric(cmd);
			वापस;
		पूर्ण

		trace_target_cmd_complete(cmd);
		ret = cmd->se_tfo->queue_data_in(cmd);
		अगर (ret)
			जाओ queue_full;
		अवरोध;
	हाल DMA_TO_DEVICE:
		atomic_दीर्घ_add(cmd->data_length,
				&cmd->se_lun->lun_stats.rx_data_octets);
		/*
		 * Check अगर we need to send READ payload क्रम BIDI-COMMAND
		 */
		अगर (cmd->se_cmd_flags & SCF_BIDI) अणु
			atomic_दीर्घ_add(cmd->data_length,
					&cmd->se_lun->lun_stats.tx_data_octets);
			ret = cmd->se_tfo->queue_data_in(cmd);
			अगर (ret)
				जाओ queue_full;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल DMA_NONE:
queue_status:
		trace_target_cmd_complete(cmd);
		ret = cmd->se_tfo->queue_status(cmd);
		अगर (ret)
			जाओ queue_full;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	transport_lun_हटाओ_cmd(cmd);
	transport_cmd_check_stop_to_fabric(cmd);
	वापस;

queue_full:
	pr_debug("Handling complete_ok QUEUE_FULL: se_cmd: %p,"
		" data_direction: %d\n", cmd, cmd->data_direction);

	transport_handle_queue_full(cmd, cmd->se_dev, ret, false);
पूर्ण

व्योम target_मुक्त_sgl(काष्ठा scatterlist *sgl, पूर्णांक nents)
अणु
	sgl_मुक्त_n_order(sgl, nents, 0);
पूर्ण
EXPORT_SYMBOL(target_मुक्त_sgl);

अटल अंतरभूत व्योम transport_reset_sgl_orig(काष्ठा se_cmd *cmd)
अणु
	/*
	 * Check क्रम saved t_data_sg that may be used क्रम COMPARE_AND_WRITE
	 * emulation, and मुक्त + reset poपूर्णांकers अगर necessary..
	 */
	अगर (!cmd->t_data_sg_orig)
		वापस;

	kमुक्त(cmd->t_data_sg);
	cmd->t_data_sg = cmd->t_data_sg_orig;
	cmd->t_data_sg_orig = शून्य;
	cmd->t_data_nents = cmd->t_data_nents_orig;
	cmd->t_data_nents_orig = 0;
पूर्ण

अटल अंतरभूत व्योम transport_मुक्त_pages(काष्ठा se_cmd *cmd)
अणु
	अगर (!(cmd->se_cmd_flags & SCF_PASSTHROUGH_PROT_SG_TO_MEM_NOALLOC)) अणु
		target_मुक्त_sgl(cmd->t_prot_sg, cmd->t_prot_nents);
		cmd->t_prot_sg = शून्य;
		cmd->t_prot_nents = 0;
	पूर्ण

	अगर (cmd->se_cmd_flags & SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC) अणु
		/*
		 * Release special हाल READ buffer payload required क्रम
		 * SG_TO_MEM_NOALLOC to function with COMPARE_AND_WRITE
		 */
		अगर (cmd->se_cmd_flags & SCF_COMPARE_AND_WRITE) अणु
			target_मुक्त_sgl(cmd->t_bidi_data_sg,
					   cmd->t_bidi_data_nents);
			cmd->t_bidi_data_sg = शून्य;
			cmd->t_bidi_data_nents = 0;
		पूर्ण
		transport_reset_sgl_orig(cmd);
		वापस;
	पूर्ण
	transport_reset_sgl_orig(cmd);

	target_मुक्त_sgl(cmd->t_data_sg, cmd->t_data_nents);
	cmd->t_data_sg = शून्य;
	cmd->t_data_nents = 0;

	target_मुक्त_sgl(cmd->t_bidi_data_sg, cmd->t_bidi_data_nents);
	cmd->t_bidi_data_sg = शून्य;
	cmd->t_bidi_data_nents = 0;
पूर्ण

व्योम *transport_kmap_data_sg(काष्ठा se_cmd *cmd)
अणु
	काष्ठा scatterlist *sg = cmd->t_data_sg;
	काष्ठा page **pages;
	पूर्णांक i;

	/*
	 * We need to take पूर्णांकo account a possible offset here क्रम fabrics like
	 * tcm_loop who may be using a contig buffer from the SCSI midlayer क्रम
	 * control CDBs passed as SGLs via transport_generic_map_mem_to_cmd()
	 */
	अगर (!cmd->t_data_nents)
		वापस शून्य;

	BUG_ON(!sg);
	अगर (cmd->t_data_nents == 1)
		वापस kmap(sg_page(sg)) + sg->offset;

	/* >1 page. use vmap */
	pages = kदो_स्मृति_array(cmd->t_data_nents, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस शून्य;

	/* convert sg[] to pages[] */
	क्रम_each_sg(cmd->t_data_sg, sg, cmd->t_data_nents, i) अणु
		pages[i] = sg_page(sg);
	पूर्ण

	cmd->t_data_vmap = vmap(pages, cmd->t_data_nents,  VM_MAP, PAGE_KERNEL);
	kमुक्त(pages);
	अगर (!cmd->t_data_vmap)
		वापस शून्य;

	वापस cmd->t_data_vmap + cmd->t_data_sg[0].offset;
पूर्ण
EXPORT_SYMBOL(transport_kmap_data_sg);

व्योम transport_kunmap_data_sg(काष्ठा se_cmd *cmd)
अणु
	अगर (!cmd->t_data_nents) अणु
		वापस;
	पूर्ण अन्यथा अगर (cmd->t_data_nents == 1) अणु
		kunmap(sg_page(cmd->t_data_sg));
		वापस;
	पूर्ण

	vunmap(cmd->t_data_vmap);
	cmd->t_data_vmap = शून्य;
पूर्ण
EXPORT_SYMBOL(transport_kunmap_data_sg);

पूर्णांक
target_alloc_sgl(काष्ठा scatterlist **sgl, अचिन्हित पूर्णांक *nents, u32 length,
		 bool zero_page, bool chainable)
अणु
	gfp_t gfp = GFP_KERNEL | (zero_page ? __GFP_ZERO : 0);

	*sgl = sgl_alloc_order(length, 0, chainable, gfp, nents);
	वापस *sgl ? 0 : -ENOMEM;
पूर्ण
EXPORT_SYMBOL(target_alloc_sgl);

/*
 * Allocate any required resources to execute the command.  For ग_लिखोs we
 * might not have the payload yet, so notअगरy the fabric via a call to
 * ->ग_लिखो_pending instead. Otherwise place it on the execution queue.
 */
sense_reason_t
transport_generic_new_cmd(काष्ठा se_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	bool zero_flag = !(cmd->se_cmd_flags & SCF_SCSI_DATA_CDB);

	अगर (cmd->prot_op != TARGET_PROT_NORMAL &&
	    !(cmd->se_cmd_flags & SCF_PASSTHROUGH_PROT_SG_TO_MEM_NOALLOC)) अणु
		ret = target_alloc_sgl(&cmd->t_prot_sg, &cmd->t_prot_nents,
				       cmd->prot_length, true, false);
		अगर (ret < 0)
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	/*
	 * Determine अगर the TCM fabric module has alपढ़ोy allocated physical
	 * memory, and is directly calling transport_generic_map_mem_to_cmd()
	 * beक्रमehand.
	 */
	अगर (!(cmd->se_cmd_flags & SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC) &&
	    cmd->data_length) अणु

		अगर ((cmd->se_cmd_flags & SCF_BIDI) ||
		    (cmd->se_cmd_flags & SCF_COMPARE_AND_WRITE)) अणु
			u32 bidi_length;

			अगर (cmd->se_cmd_flags & SCF_COMPARE_AND_WRITE)
				bidi_length = cmd->t_task_nolb *
					      cmd->se_dev->dev_attrib.block_size;
			अन्यथा
				bidi_length = cmd->data_length;

			ret = target_alloc_sgl(&cmd->t_bidi_data_sg,
					       &cmd->t_bidi_data_nents,
					       bidi_length, zero_flag, false);
			अगर (ret < 0)
				वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		पूर्ण

		ret = target_alloc_sgl(&cmd->t_data_sg, &cmd->t_data_nents,
				       cmd->data_length, zero_flag, false);
		अगर (ret < 0)
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण अन्यथा अगर ((cmd->se_cmd_flags & SCF_COMPARE_AND_WRITE) &&
		    cmd->data_length) अणु
		/*
		 * Special हाल क्रम COMPARE_AND_WRITE with fabrics
		 * using SCF_PASSTHROUGH_SG_TO_MEM_NOALLOC.
		 */
		u32 caw_length = cmd->t_task_nolb *
				 cmd->se_dev->dev_attrib.block_size;

		ret = target_alloc_sgl(&cmd->t_bidi_data_sg,
				       &cmd->t_bidi_data_nents,
				       caw_length, zero_flag, false);
		अगर (ret < 0)
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * If this command is not a ग_लिखो we can execute it right here,
	 * क्रम ग_लिखो buffers we need to notअगरy the fabric driver first
	 * and let it call back once the ग_लिखो buffers are पढ़ोy.
	 */
	target_add_to_state_list(cmd);
	अगर (cmd->data_direction != DMA_TO_DEVICE || cmd->data_length == 0) अणु
		target_execute_cmd(cmd);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	cmd->t_state = TRANSPORT_WRITE_PENDING;
	/*
	 * Determine अगर frontend context caller is requesting the stopping of
	 * this command क्रम frontend exceptions.
	 */
	अगर (cmd->transport_state & CMD_T_STOP &&
	    !cmd->se_tfo->ग_लिखो_pending_must_be_called) अणु
		pr_debug("%s:%d CMD_T_STOP for ITT: 0x%08llx\n",
			 __func__, __LINE__, cmd->tag);

		spin_unlock_irqrestore(&cmd->t_state_lock, flags);

		complete_all(&cmd->t_transport_stop_comp);
		वापस 0;
	पूर्ण
	cmd->transport_state &= ~CMD_T_ACTIVE;
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	ret = cmd->se_tfo->ग_लिखो_pending(cmd);
	अगर (ret)
		जाओ queue_full;

	वापस 0;

queue_full:
	pr_debug("Handling write_pending QUEUE__FULL: se_cmd: %p\n", cmd);
	transport_handle_queue_full(cmd, cmd->se_dev, ret, true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(transport_generic_new_cmd);

अटल व्योम transport_ग_लिखो_pending_qf(काष्ठा se_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	bool stop;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	stop = (cmd->transport_state & (CMD_T_STOP | CMD_T_ABORTED));
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	अगर (stop) अणु
		pr_debug("%s:%d CMD_T_STOP|CMD_T_ABORTED for ITT: 0x%08llx\n",
			__func__, __LINE__, cmd->tag);
		complete_all(&cmd->t_transport_stop_comp);
		वापस;
	पूर्ण

	ret = cmd->se_tfo->ग_लिखो_pending(cmd);
	अगर (ret) अणु
		pr_debug("Handling write_pending QUEUE__FULL: se_cmd: %p\n",
			 cmd);
		transport_handle_queue_full(cmd, cmd->se_dev, ret, true);
	पूर्ण
पूर्ण

अटल bool
__transport_रुको_क्रम_tasks(काष्ठा se_cmd *, bool, bool *, bool *,
			   अचिन्हित दीर्घ *flags);

अटल व्योम target_रुको_मुक्त_cmd(काष्ठा se_cmd *cmd, bool *पातed, bool *tas)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	__transport_रुको_क्रम_tasks(cmd, true, पातed, tas, &flags);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);
पूर्ण

/*
 * Call target_put_sess_cmd() and रुको until target_release_cmd_kref(@cmd) has
 * finished.
 */
व्योम target_put_cmd_and_रुको(काष्ठा se_cmd *cmd)
अणु
	DECLARE_COMPLETION_ONSTACK(compl);

	WARN_ON_ONCE(cmd->abrt_compl);
	cmd->abrt_compl = &compl;
	target_put_sess_cmd(cmd);
	रुको_क्रम_completion(&compl);
पूर्ण

/*
 * This function is called by frontend drivers after processing of a command
 * has finished.
 *
 * The protocol क्रम ensuring that either the regular frontend command
 * processing flow or target_handle_पात() code drops one reference is as
 * follows:
 * - Calling .queue_data_in(), .queue_status() or queue_पंचांग_rsp() will cause
 *   the frontend driver to call this function synchronously or asynchronously.
 *   That will cause one reference to be dropped.
 * - During regular command processing the target core sets CMD_T_COMPLETE
 *   beक्रमe invoking one of the .queue_*() functions.
 * - The code that पातs commands skips commands and TMFs क्रम which
 *   CMD_T_COMPLETE has been set.
 * - CMD_T_ABORTED is set atomically after the CMD_T_COMPLETE check क्रम
 *   commands that will be पातed.
 * - If the CMD_T_ABORTED flag is set but CMD_T_TAS has not been set
 *   transport_generic_मुक्त_cmd() skips its call to target_put_sess_cmd().
 * - For पातed commands क्रम which CMD_T_TAS has been set .queue_status() will
 *   be called and will drop a reference.
 * - For पातed commands क्रम which CMD_T_TAS has not been set .पातed_task()
 *   will be called. target_handle_पात() will drop the final reference.
 */
पूर्णांक transport_generic_मुक्त_cmd(काष्ठा se_cmd *cmd, पूर्णांक रुको_क्रम_tasks)
अणु
	DECLARE_COMPLETION_ONSTACK(compl);
	पूर्णांक ret = 0;
	bool पातed = false, tas = false;

	अगर (रुको_क्रम_tasks)
		target_रुको_मुक्त_cmd(cmd, &पातed, &tas);

	अगर (cmd->se_cmd_flags & SCF_SE_LUN_CMD) अणु
		/*
		 * Handle WRITE failure हाल where transport_generic_new_cmd()
		 * has alपढ़ोy added se_cmd to state_list, but fabric has
		 * failed command beक्रमe I/O submission.
		 */
		अगर (cmd->state_active)
			target_हटाओ_from_state_list(cmd);

		अगर (cmd->se_lun)
			transport_lun_हटाओ_cmd(cmd);
	पूर्ण
	अगर (पातed)
		cmd->मुक्त_compl = &compl;
	ret = target_put_sess_cmd(cmd);
	अगर (पातed) अणु
		pr_debug("Detected CMD_T_ABORTED for ITT: %llu\n", cmd->tag);
		रुको_क्रम_completion(&compl);
		ret = 1;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(transport_generic_मुक्त_cmd);

/**
 * target_get_sess_cmd - Verअगरy the session is accepting cmds and take ref
 * @se_cmd:	command descriptor to add
 * @ack_kref:	Signal that fabric will perक्रमm an ack target_put_sess_cmd()
 */
पूर्णांक target_get_sess_cmd(काष्ठा se_cmd *se_cmd, bool ack_kref)
अणु
	काष्ठा se_session *se_sess = se_cmd->se_sess;
	पूर्णांक ret = 0;

	/*
	 * Add a second kref अगर the fabric caller is expecting to handle
	 * fabric acknowledgement that requires two target_put_sess_cmd()
	 * invocations beक्रमe se_cmd descriptor release.
	 */
	अगर (ack_kref) अणु
		kref_get(&se_cmd->cmd_kref);
		se_cmd->se_cmd_flags |= SCF_ACK_KREF;
	पूर्ण

	अगर (!percpu_ref_tryget_live(&se_sess->cmd_count))
		ret = -ESHUTDOWN;

	अगर (ret && ack_kref)
		target_put_sess_cmd(se_cmd);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(target_get_sess_cmd);

अटल व्योम target_मुक्त_cmd_mem(काष्ठा se_cmd *cmd)
अणु
	transport_मुक्त_pages(cmd);

	अगर (cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)
		core_पंचांगr_release_req(cmd->se_पंचांगr_req);
	अगर (cmd->t_task_cdb != cmd->__t_task_cdb)
		kमुक्त(cmd->t_task_cdb);
पूर्ण

अटल व्योम target_release_cmd_kref(काष्ठा kref *kref)
अणु
	काष्ठा se_cmd *se_cmd = container_of(kref, काष्ठा se_cmd, cmd_kref);
	काष्ठा se_session *se_sess = se_cmd->se_sess;
	काष्ठा completion *मुक्त_compl = se_cmd->मुक्त_compl;
	काष्ठा completion *abrt_compl = se_cmd->abrt_compl;

	target_मुक्त_cmd_mem(se_cmd);
	se_cmd->se_tfo->release_cmd(se_cmd);
	अगर (मुक्त_compl)
		complete(मुक्त_compl);
	अगर (abrt_compl)
		complete(abrt_compl);

	percpu_ref_put(&se_sess->cmd_count);
पूर्ण

/**
 * target_put_sess_cmd - decrease the command reference count
 * @se_cmd:	command to drop a reference from
 *
 * Returns 1 अगर and only अगर this target_put_sess_cmd() call caused the
 * refcount to drop to zero. Returns zero otherwise.
 */
पूर्णांक target_put_sess_cmd(काष्ठा se_cmd *se_cmd)
अणु
	वापस kref_put(&se_cmd->cmd_kref, target_release_cmd_kref);
पूर्ण
EXPORT_SYMBOL(target_put_sess_cmd);

अटल स्थिर अक्षर *data_dir_name(क्रमागत dma_data_direction d)
अणु
	चयन (d) अणु
	हाल DMA_BIसूचीECTIONAL:	वापस "BIDI";
	हाल DMA_TO_DEVICE:	वापस "WRITE";
	हाल DMA_FROM_DEVICE:	वापस "READ";
	हाल DMA_NONE:		वापस "NONE";
	पूर्ण

	वापस "(?)";
पूर्ण

अटल स्थिर अक्षर *cmd_state_name(क्रमागत transport_state_table t)
अणु
	चयन (t) अणु
	हाल TRANSPORT_NO_STATE:	वापस "NO_STATE";
	हाल TRANSPORT_NEW_CMD:		वापस "NEW_CMD";
	हाल TRANSPORT_WRITE_PENDING:	वापस "WRITE_PENDING";
	हाल TRANSPORT_PROCESSING:	वापस "PROCESSING";
	हाल TRANSPORT_COMPLETE:	वापस "COMPLETE";
	हाल TRANSPORT_ISTATE_PROCESSING:
					वापस "ISTATE_PROCESSING";
	हाल TRANSPORT_COMPLETE_QF_WP:	वापस "COMPLETE_QF_WP";
	हाल TRANSPORT_COMPLETE_QF_OK:	वापस "COMPLETE_QF_OK";
	हाल TRANSPORT_COMPLETE_QF_ERR:	वापस "COMPLETE_QF_ERR";
	पूर्ण

	वापस "(?)";
पूर्ण

अटल व्योम target_append_str(अक्षर **str, स्थिर अक्षर *txt)
अणु
	अक्षर *prev = *str;

	*str = *str ? kaप्र_लिखो(GFP_ATOMIC, "%s,%s", *str, txt) :
		kstrdup(txt, GFP_ATOMIC);
	kमुक्त(prev);
पूर्ण

/*
 * Convert a transport state biपंचांगask पूर्णांकo a string. The caller is
 * responsible क्रम मुक्तing the वापसed poपूर्णांकer.
 */
अटल अक्षर *target_ts_to_str(u32 ts)
अणु
	अक्षर *str = शून्य;

	अगर (ts & CMD_T_ABORTED)
		target_append_str(&str, "aborted");
	अगर (ts & CMD_T_ACTIVE)
		target_append_str(&str, "active");
	अगर (ts & CMD_T_COMPLETE)
		target_append_str(&str, "complete");
	अगर (ts & CMD_T_SENT)
		target_append_str(&str, "sent");
	अगर (ts & CMD_T_STOP)
		target_append_str(&str, "stop");
	अगर (ts & CMD_T_FABRIC_STOP)
		target_append_str(&str, "fabric_stop");

	वापस str;
पूर्ण

अटल स्थिर अक्षर *target_पंचांगf_name(क्रमागत tcm_पंचांगreq_table पंचांगf)
अणु
	चयन (पंचांगf) अणु
	हाल TMR_ABORT_TASK:		वापस "ABORT_TASK";
	हाल TMR_ABORT_TASK_SET:	वापस "ABORT_TASK_SET";
	हाल TMR_CLEAR_ACA:		वापस "CLEAR_ACA";
	हाल TMR_CLEAR_TASK_SET:	वापस "CLEAR_TASK_SET";
	हाल TMR_LUN_RESET:		वापस "LUN_RESET";
	हाल TMR_TARGET_WARM_RESET:	वापस "TARGET_WARM_RESET";
	हाल TMR_TARGET_COLD_RESET:	वापस "TARGET_COLD_RESET";
	हाल TMR_LUN_RESET_PRO:		वापस "LUN_RESET_PRO";
	हाल TMR_UNKNOWN:		अवरोध;
	पूर्ण
	वापस "(?)";
पूर्ण

व्योम target_show_cmd(स्थिर अक्षर *pfx, काष्ठा se_cmd *cmd)
अणु
	अक्षर *ts_str = target_ts_to_str(cmd->transport_state);
	स्थिर u8 *cdb = cmd->t_task_cdb;
	काष्ठा se_पंचांगr_req *पंचांगf = cmd->se_पंचांगr_req;

	अगर (!(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)) अणु
		pr_debug("%scmd %#02x:%#02x with tag %#llx dir %s i_state %d t_state %s len %d refcnt %d transport_state %s\n",
			 pfx, cdb[0], cdb[1], cmd->tag,
			 data_dir_name(cmd->data_direction),
			 cmd->se_tfo->get_cmd_state(cmd),
			 cmd_state_name(cmd->t_state), cmd->data_length,
			 kref_पढ़ो(&cmd->cmd_kref), ts_str);
	पूर्ण अन्यथा अणु
		pr_debug("%stmf %s with tag %#llx ref_task_tag %#llx i_state %d t_state %s refcnt %d transport_state %s\n",
			 pfx, target_पंचांगf_name(पंचांगf->function), cmd->tag,
			 पंचांगf->ref_task_tag, cmd->se_tfo->get_cmd_state(cmd),
			 cmd_state_name(cmd->t_state),
			 kref_पढ़ो(&cmd->cmd_kref), ts_str);
	पूर्ण
	kमुक्त(ts_str);
पूर्ण
EXPORT_SYMBOL(target_show_cmd);

अटल व्योम target_stop_session_confirm(काष्ठा percpu_ref *ref)
अणु
	काष्ठा se_session *se_sess = container_of(ref, काष्ठा se_session,
						  cmd_count);
	complete_all(&se_sess->stop_करोne);
पूर्ण

/**
 * target_stop_session - Stop new IO from being queued on the session.
 * @se_sess:    session to stop
 */
व्योम target_stop_session(काष्ठा se_session *se_sess)
अणु
	pr_debug("Stopping session queue.\n");
	अगर (atomic_cmpxchg(&se_sess->stopped, 0, 1) == 0)
		percpu_ref_समाप्त_and_confirm(&se_sess->cmd_count,
					    target_stop_session_confirm);
पूर्ण
EXPORT_SYMBOL(target_stop_session);

/**
 * target_रुको_क्रम_sess_cmds - Wait क्रम outstanding commands
 * @se_sess:    session to रुको क्रम active I/O
 */
व्योम target_रुको_क्रम_sess_cmds(काष्ठा se_session *se_sess)
अणु
	पूर्णांक ret;

	WARN_ON_ONCE(!atomic_पढ़ो(&se_sess->stopped));

	करो अणु
		pr_debug("Waiting for running cmds to complete.\n");
		ret = रुको_event_समयout(se_sess->cmd_count_wq,
				percpu_ref_is_zero(&se_sess->cmd_count),
				180 * HZ);
	पूर्ण जबतक (ret <= 0);

	रुको_क्रम_completion(&se_sess->stop_करोne);
	pr_debug("Waiting for cmds done.\n");
पूर्ण
EXPORT_SYMBOL(target_रुको_क्रम_sess_cmds);

/*
 * Prevent that new percpu_ref_tryget_live() calls succeed and रुको until
 * all references to the LUN have been released. Called during LUN shutकरोwn.
 */
व्योम transport_clear_lun_ref(काष्ठा se_lun *lun)
अणु
	percpu_ref_समाप्त(&lun->lun_ref);
	रुको_क्रम_completion(&lun->lun_shutकरोwn_comp);
पूर्ण

अटल bool
__transport_रुको_क्रम_tasks(काष्ठा se_cmd *cmd, bool fabric_stop,
			   bool *पातed, bool *tas, अचिन्हित दीर्घ *flags)
	__releases(&cmd->t_state_lock)
	__acquires(&cmd->t_state_lock)
अणु
	lockdep_निश्चित_held(&cmd->t_state_lock);

	अगर (fabric_stop)
		cmd->transport_state |= CMD_T_FABRIC_STOP;

	अगर (cmd->transport_state & CMD_T_ABORTED)
		*पातed = true;

	अगर (cmd->transport_state & CMD_T_TAS)
		*tas = true;

	अगर (!(cmd->se_cmd_flags & SCF_SE_LUN_CMD) &&
	    !(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB))
		वापस false;

	अगर (!(cmd->se_cmd_flags & SCF_SUPPORTED_SAM_OPCODE) &&
	    !(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB))
		वापस false;

	अगर (!(cmd->transport_state & CMD_T_ACTIVE))
		वापस false;

	अगर (fabric_stop && *पातed)
		वापस false;

	cmd->transport_state |= CMD_T_STOP;

	target_show_cmd("wait_for_tasks: Stopping ", cmd);

	spin_unlock_irqrestore(&cmd->t_state_lock, *flags);

	जबतक (!रुको_क्रम_completion_समयout(&cmd->t_transport_stop_comp,
					    180 * HZ))
		target_show_cmd("wait for tasks: ", cmd);

	spin_lock_irqsave(&cmd->t_state_lock, *flags);
	cmd->transport_state &= ~(CMD_T_ACTIVE | CMD_T_STOP);

	pr_debug("wait_for_tasks: Stopped wait_for_completion(&cmd->"
		 "t_transport_stop_comp) for ITT: 0x%08llx\n", cmd->tag);

	वापस true;
पूर्ण

/**
 * transport_रुको_क्रम_tasks - set CMD_T_STOP and रुको क्रम t_transport_stop_comp
 * @cmd: command to रुको on
 */
bool transport_रुको_क्रम_tasks(काष्ठा se_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;
	bool ret, पातed = false, tas = false;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	ret = __transport_रुको_क्रम_tasks(cmd, false, &पातed, &tas, &flags);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(transport_रुको_क्रम_tasks);

काष्ठा sense_detail अणु
	u8 key;
	u8 asc;
	u8 ascq;
	bool add_sense_info;
पूर्ण;

अटल स्थिर काष्ठा sense_detail sense_detail_table[] = अणु
	[TCM_NO_SENSE] = अणु
		.key = NOT_READY
	पूर्ण,
	[TCM_NON_EXISTENT_LUN] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x25 /* LOGICAL UNIT NOT SUPPORTED */
	पूर्ण,
	[TCM_UNSUPPORTED_SCSI_OPCODE] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x20, /* INVALID COMMAND OPERATION CODE */
	पूर्ण,
	[TCM_SECTOR_COUNT_TOO_MANY] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x20, /* INVALID COMMAND OPERATION CODE */
	पूर्ण,
	[TCM_UNKNOWN_MODE_PAGE] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x24, /* INVALID FIELD IN CDB */
	पूर्ण,
	[TCM_CHECK_CONDITION_ABORT_CMD] = अणु
		.key = ABORTED_COMMAND,
		.asc = 0x29, /* BUS DEVICE RESET FUNCTION OCCURRED */
		.ascq = 0x03,
	पूर्ण,
	[TCM_INCORRECT_AMOUNT_OF_DATA] = अणु
		.key = ABORTED_COMMAND,
		.asc = 0x0c, /* WRITE ERROR */
		.ascq = 0x0d, /* NOT ENOUGH UNSOLICITED DATA */
	पूर्ण,
	[TCM_INVALID_CDB_FIELD] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x24, /* INVALID FIELD IN CDB */
	पूर्ण,
	[TCM_INVALID_PARAMETER_LIST] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x26, /* INVALID FIELD IN PARAMETER LIST */
	पूर्ण,
	[TCM_TOO_MANY_TARGET_DESCS] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x26,
		.ascq = 0x06, /* TOO MANY TARGET DESCRIPTORS */
	पूर्ण,
	[TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x26,
		.ascq = 0x07, /* UNSUPPORTED TARGET DESCRIPTOR TYPE CODE */
	पूर्ण,
	[TCM_TOO_MANY_SEGMENT_DESCS] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x26,
		.ascq = 0x08, /* TOO MANY SEGMENT DESCRIPTORS */
	पूर्ण,
	[TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x26,
		.ascq = 0x09, /* UNSUPPORTED SEGMENT DESCRIPTOR TYPE CODE */
	पूर्ण,
	[TCM_PARAMETER_LIST_LENGTH_ERROR] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x1a, /* PARAMETER LIST LENGTH ERROR */
	पूर्ण,
	[TCM_UNEXPECTED_UNSOLICITED_DATA] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x0c, /* WRITE ERROR */
		.ascq = 0x0c, /* UNEXPECTED_UNSOLICITED_DATA */
	पूर्ण,
	[TCM_SERVICE_CRC_ERROR] = अणु
		.key = ABORTED_COMMAND,
		.asc = 0x47, /* PROTOCOL SERVICE CRC ERROR */
		.ascq = 0x05, /* N/A */
	पूर्ण,
	[TCM_SNACK_REJECTED] = अणु
		.key = ABORTED_COMMAND,
		.asc = 0x11, /* READ ERROR */
		.ascq = 0x13, /* FAILED RETRANSMISSION REQUEST */
	पूर्ण,
	[TCM_WRITE_PROTECTED] = अणु
		.key = DATA_PROTECT,
		.asc = 0x27, /* WRITE PROTECTED */
	पूर्ण,
	[TCM_ADDRESS_OUT_OF_RANGE] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x21, /* LOGICAL BLOCK ADDRESS OUT OF RANGE */
	पूर्ण,
	[TCM_CHECK_CONDITION_UNIT_ATTENTION] = अणु
		.key = UNIT_ATTENTION,
	पूर्ण,
	[TCM_CHECK_CONDITION_NOT_READY] = अणु
		.key = NOT_READY,
	पूर्ण,
	[TCM_MISCOMPARE_VERIFY] = अणु
		.key = MISCOMPARE,
		.asc = 0x1d, /* MISCOMPARE DURING VERIFY OPERATION */
		.ascq = 0x00,
		.add_sense_info = true,
	पूर्ण,
	[TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED] = अणु
		.key = ABORTED_COMMAND,
		.asc = 0x10,
		.ascq = 0x01, /* LOGICAL BLOCK GUARD CHECK FAILED */
		.add_sense_info = true,
	पूर्ण,
	[TCM_LOGICAL_BLOCK_APP_TAG_CHECK_FAILED] = अणु
		.key = ABORTED_COMMAND,
		.asc = 0x10,
		.ascq = 0x02, /* LOGICAL BLOCK APPLICATION TAG CHECK FAILED */
		.add_sense_info = true,
	पूर्ण,
	[TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED] = अणु
		.key = ABORTED_COMMAND,
		.asc = 0x10,
		.ascq = 0x03, /* LOGICAL BLOCK REFERENCE TAG CHECK FAILED */
		.add_sense_info = true,
	पूर्ण,
	[TCM_COPY_TARGET_DEVICE_NOT_REACHABLE] = अणु
		.key = COPY_ABORTED,
		.asc = 0x0d,
		.ascq = 0x02, /* COPY TARGET DEVICE NOT REACHABLE */

	पूर्ण,
	[TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE] = अणु
		/*
		 * Returning ILLEGAL REQUEST would cause immediate IO errors on
		 * Solaris initiators.  Returning NOT READY instead means the
		 * operations will be retried a finite number of बार and we
		 * can survive पूर्णांकermittent errors.
		 */
		.key = NOT_READY,
		.asc = 0x08, /* LOGICAL UNIT COMMUNICATION FAILURE */
	पूर्ण,
	[TCM_INSUFFICIENT_REGISTRATION_RESOURCES] = अणु
		/*
		 * From spc4r22 section5.7.7,5.7.8
		 * If a PERSISTENT RESERVE OUT command with a REGISTER service action
		 * or a REGISTER AND IGNORE EXISTING KEY service action or
		 * REGISTER AND MOVE service actionis attempted,
		 * but there are insufficient device server resources to complete the
		 * operation, then the command shall be terminated with CHECK CONDITION
		 * status, with the sense key set to ILLEGAL REQUEST,and the additonal
		 * sense code set to INSUFFICIENT REGISTRATION RESOURCES.
		 */
		.key = ILLEGAL_REQUEST,
		.asc = 0x55,
		.ascq = 0x04, /* INSUFFICIENT REGISTRATION RESOURCES */
	पूर्ण,
	[TCM_INVALID_FIELD_IN_COMMAND_IU] = अणु
		.key = ILLEGAL_REQUEST,
		.asc = 0x0e,
		.ascq = 0x03, /* INVALID FIELD IN COMMAND INFORMATION UNIT */
	पूर्ण,
पूर्ण;

/**
 * translate_sense_reason - translate a sense reason पूर्णांकo T10 key, asc and ascq
 * @cmd: SCSI command in which the resulting sense buffer or SCSI status will
 *   be stored.
 * @reason: LIO sense reason code. If this argument has the value
 *   TCM_CHECK_CONDITION_UNIT_ATTENTION, try to dequeue a unit attention. If
 *   dequeuing a unit attention fails due to multiple commands being processed
 *   concurrently, set the command status to BUSY.
 *
 * Return: 0 upon success or -EINVAL अगर the sense buffer is too small.
 */
अटल व्योम translate_sense_reason(काष्ठा se_cmd *cmd, sense_reason_t reason)
अणु
	स्थिर काष्ठा sense_detail *sd;
	u8 *buffer = cmd->sense_buffer;
	पूर्णांक r = (__क्रमce पूर्णांक)reason;
	u8 key, asc, ascq;
	bool desc_क्रमmat = target_sense_desc_क्रमmat(cmd->se_dev);

	अगर (r < ARRAY_SIZE(sense_detail_table) && sense_detail_table[r].key)
		sd = &sense_detail_table[r];
	अन्यथा
		sd = &sense_detail_table[(__क्रमce पूर्णांक)
				       TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE];

	key = sd->key;
	अगर (reason == TCM_CHECK_CONDITION_UNIT_ATTENTION) अणु
		अगर (!core_scsi3_ua_क्रम_check_condition(cmd, &key, &asc,
						       &ascq)) अणु
			cmd->scsi_status = SAM_STAT_BUSY;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (sd->asc == 0) अणु
		WARN_ON_ONCE(cmd->scsi_asc == 0);
		asc = cmd->scsi_asc;
		ascq = cmd->scsi_ascq;
	पूर्ण अन्यथा अणु
		asc = sd->asc;
		ascq = sd->ascq;
	पूर्ण

	cmd->se_cmd_flags |= SCF_EMULATED_TASK_SENSE;
	cmd->scsi_status = SAM_STAT_CHECK_CONDITION;
	cmd->scsi_sense_length  = TRANSPORT_SENSE_BUFFER;
	scsi_build_sense_buffer(desc_क्रमmat, buffer, key, asc, ascq);
	अगर (sd->add_sense_info)
		WARN_ON_ONCE(scsi_set_sense_inक्रमmation(buffer,
							cmd->scsi_sense_length,
							cmd->sense_info) < 0);
पूर्ण

पूर्णांक
transport_send_check_condition_and_sense(काष्ठा se_cmd *cmd,
		sense_reason_t reason, पूर्णांक from_transport)
अणु
	अचिन्हित दीर्घ flags;

	WARN_ON_ONCE(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB);

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	अगर (cmd->se_cmd_flags & SCF_SENT_CHECK_CONDITION) अणु
		spin_unlock_irqrestore(&cmd->t_state_lock, flags);
		वापस 0;
	पूर्ण
	cmd->se_cmd_flags |= SCF_SENT_CHECK_CONDITION;
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	अगर (!from_transport)
		translate_sense_reason(cmd, reason);

	trace_target_cmd_complete(cmd);
	वापस cmd->se_tfo->queue_status(cmd);
पूर्ण
EXPORT_SYMBOL(transport_send_check_condition_and_sense);

/**
 * target_send_busy - Send SCSI BUSY status back to the initiator
 * @cmd: SCSI command क्रम which to send a BUSY reply.
 *
 * Note: Only call this function अगर target_submit_cmd*() failed.
 */
पूर्णांक target_send_busy(काष्ठा se_cmd *cmd)
अणु
	WARN_ON_ONCE(cmd->se_cmd_flags & SCF_SCSI_TMR_CDB);

	cmd->scsi_status = SAM_STAT_BUSY;
	trace_target_cmd_complete(cmd);
	वापस cmd->se_tfo->queue_status(cmd);
पूर्ण
EXPORT_SYMBOL(target_send_busy);

अटल व्योम target_पंचांगr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा se_cmd *cmd = container_of(work, काष्ठा se_cmd, work);
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_पंचांगr_req *पंचांगr = cmd->se_पंचांगr_req;
	पूर्णांक ret;

	अगर (cmd->transport_state & CMD_T_ABORTED)
		जाओ पातed;

	चयन (पंचांगr->function) अणु
	हाल TMR_ABORT_TASK:
		core_पंचांगr_पात_task(dev, पंचांगr, cmd->se_sess);
		अवरोध;
	हाल TMR_ABORT_TASK_SET:
	हाल TMR_CLEAR_ACA:
	हाल TMR_CLEAR_TASK_SET:
		पंचांगr->response = TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED;
		अवरोध;
	हाल TMR_LUN_RESET:
		ret = core_पंचांगr_lun_reset(dev, पंचांगr, शून्य, शून्य);
		पंचांगr->response = (!ret) ? TMR_FUNCTION_COMPLETE :
					 TMR_FUNCTION_REJECTED;
		अगर (पंचांगr->response == TMR_FUNCTION_COMPLETE) अणु
			target_ua_allocate_lun(cmd->se_sess->se_node_acl,
					       cmd->orig_fe_lun, 0x29,
					       ASCQ_29H_BUS_DEVICE_RESET_FUNCTION_OCCURRED);
		पूर्ण
		अवरोध;
	हाल TMR_TARGET_WARM_RESET:
		पंचांगr->response = TMR_FUNCTION_REJECTED;
		अवरोध;
	हाल TMR_TARGET_COLD_RESET:
		पंचांगr->response = TMR_FUNCTION_REJECTED;
		अवरोध;
	शेष:
		pr_err("Unknown TMR function: 0x%02x.\n",
				पंचांगr->function);
		पंचांगr->response = TMR_FUNCTION_REJECTED;
		अवरोध;
	पूर्ण

	अगर (cmd->transport_state & CMD_T_ABORTED)
		जाओ पातed;

	cmd->se_tfo->queue_पंचांग_rsp(cmd);

	transport_lun_हटाओ_cmd(cmd);
	transport_cmd_check_stop_to_fabric(cmd);
	वापस;

पातed:
	target_handle_पात(cmd);
पूर्ण

पूर्णांक transport_generic_handle_पंचांगr(
	काष्ठा se_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;
	bool पातed = false;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	अगर (cmd->transport_state & CMD_T_ABORTED) अणु
		पातed = true;
	पूर्ण अन्यथा अणु
		cmd->t_state = TRANSPORT_ISTATE_PROCESSING;
		cmd->transport_state |= CMD_T_ACTIVE;
	पूर्ण
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	अगर (पातed) अणु
		pr_warn_ratelimited("handle_tmr caught CMD_T_ABORTED TMR %d ref_tag: %llu tag: %llu\n",
				    cmd->se_पंचांगr_req->function,
				    cmd->se_पंचांगr_req->ref_task_tag, cmd->tag);
		target_handle_पात(cmd);
		वापस 0;
	पूर्ण

	INIT_WORK(&cmd->work, target_पंचांगr_work);
	schedule_work(&cmd->work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(transport_generic_handle_पंचांगr);

bool
target_check_wce(काष्ठा se_device *dev)
अणु
	bool wce = false;

	अगर (dev->transport->get_ग_लिखो_cache)
		wce = dev->transport->get_ग_लिखो_cache(dev);
	अन्यथा अगर (dev->dev_attrib.emulate_ग_लिखो_cache > 0)
		wce = true;

	वापस wce;
पूर्ण

bool
target_check_fua(काष्ठा se_device *dev)
अणु
	वापस target_check_wce(dev) && dev->dev_attrib.emulate_fua_ग_लिखो > 0;
पूर्ण
