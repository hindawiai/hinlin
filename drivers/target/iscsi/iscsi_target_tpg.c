<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains iSCSI Target Portal Group related functions.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_login.h"
#समावेश "iscsi_target_nodeattrib.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"
#समावेश "iscsi_target_parameters.h"

#समावेश <target/iscsi/iscsi_transport.h>

काष्ठा iscsi_portal_group *iscsit_alloc_portal_group(काष्ठा iscsi_tiqn *tiqn, u16 tpgt)
अणु
	काष्ठा iscsi_portal_group *tpg;

	tpg = kzalloc(माप(काष्ठा iscsi_portal_group), GFP_KERNEL);
	अगर (!tpg) अणु
		pr_err("Unable to allocate struct iscsi_portal_group\n");
		वापस शून्य;
	पूर्ण

	tpg->tpgt = tpgt;
	tpg->tpg_state = TPG_STATE_FREE;
	tpg->tpg_tiqn = tiqn;
	INIT_LIST_HEAD(&tpg->tpg_gnp_list);
	INIT_LIST_HEAD(&tpg->tpg_list);
	mutex_init(&tpg->tpg_access_lock);
	sema_init(&tpg->np_login_sem, 1);
	spin_lock_init(&tpg->tpg_state_lock);
	spin_lock_init(&tpg->tpg_np_lock);

	वापस tpg;
पूर्ण

अटल व्योम iscsit_set_शेष_tpg_attribs(काष्ठा iscsi_portal_group *);

पूर्णांक iscsit_load_discovery_tpg(व्योम)
अणु
	काष्ठा iscsi_param *param;
	काष्ठा iscsi_portal_group *tpg;
	पूर्णांक ret;

	tpg = iscsit_alloc_portal_group(शून्य, 1);
	अगर (!tpg) अणु
		pr_err("Unable to allocate struct iscsi_portal_group\n");
		वापस -1;
	पूर्ण
	/*
	 * Save iscsi_ops poपूर्णांकer क्रम special हाल discovery TPG that
	 * करोesn't exist as se_wwn->wwn_group within configfs.
	 */
	tpg->tpg_se_tpg.se_tpg_tfo = &iscsi_ops;
	ret = core_tpg_रेजिस्टर(शून्य, &tpg->tpg_se_tpg, -1);
	अगर (ret < 0) अणु
		kमुक्त(tpg);
		वापस -1;
	पूर्ण

	tpg->sid = 1; /* First Asचिन्हित LIO Session ID */
	iscsit_set_शेष_tpg_attribs(tpg);

	अगर (iscsi_create_शेष_params(&tpg->param_list) < 0)
		जाओ out;
	/*
	 * By शेष we disable authentication क्रम discovery sessions,
	 * this can be changed with:
	 *
	 * /sys/kernel/config/target/iscsi/discovery_auth/enक्रमce_discovery_auth
	 */
	param = iscsi_find_param_from_key(AUTHMETHOD, tpg->param_list);
	अगर (!param)
		जाओ मुक्त_pl_out;

	अगर (iscsi_update_param_value(param, "CHAP,None") < 0)
		जाओ मुक्त_pl_out;

	tpg->tpg_attrib.authentication = 0;

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state  = TPG_STATE_ACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	iscsit_global->discovery_tpg = tpg;
	pr_debug("CORE[0] - Allocated Discovery TPG\n");

	वापस 0;
मुक्त_pl_out:
	iscsi_release_param_list(tpg->param_list);
out:
	अगर (tpg->sid == 1)
		core_tpg_deरेजिस्टर(&tpg->tpg_se_tpg);
	kमुक्त(tpg);
	वापस -1;
पूर्ण

व्योम iscsit_release_discovery_tpg(व्योम)
अणु
	काष्ठा iscsi_portal_group *tpg = iscsit_global->discovery_tpg;

	अगर (!tpg)
		वापस;

	iscsi_release_param_list(tpg->param_list);
	core_tpg_deरेजिस्टर(&tpg->tpg_se_tpg);

	kमुक्त(tpg);
	iscsit_global->discovery_tpg = शून्य;
पूर्ण

काष्ठा iscsi_portal_group *iscsit_get_tpg_from_np(
	काष्ठा iscsi_tiqn *tiqn,
	काष्ठा iscsi_np *np,
	काष्ठा iscsi_tpg_np **tpg_np_out)
अणु
	काष्ठा iscsi_portal_group *tpg = शून्य;
	काष्ठा iscsi_tpg_np *tpg_np;

	spin_lock(&tiqn->tiqn_tpg_lock);
	list_क्रम_each_entry(tpg, &tiqn->tiqn_tpg_list, tpg_list) अणु

		spin_lock(&tpg->tpg_state_lock);
		अगर (tpg->tpg_state != TPG_STATE_ACTIVE) अणु
			spin_unlock(&tpg->tpg_state_lock);
			जारी;
		पूर्ण
		spin_unlock(&tpg->tpg_state_lock);

		spin_lock(&tpg->tpg_np_lock);
		list_क्रम_each_entry(tpg_np, &tpg->tpg_gnp_list, tpg_np_list) अणु
			अगर (tpg_np->tpg_np == np) अणु
				*tpg_np_out = tpg_np;
				kref_get(&tpg_np->tpg_np_kref);
				spin_unlock(&tpg->tpg_np_lock);
				spin_unlock(&tiqn->tiqn_tpg_lock);
				वापस tpg;
			पूर्ण
		पूर्ण
		spin_unlock(&tpg->tpg_np_lock);
	पूर्ण
	spin_unlock(&tiqn->tiqn_tpg_lock);

	वापस शून्य;
पूर्ण

पूर्णांक iscsit_get_tpg(
	काष्ठा iscsi_portal_group *tpg)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&tpg->tpg_access_lock);
पूर्ण

व्योम iscsit_put_tpg(काष्ठा iscsi_portal_group *tpg)
अणु
	mutex_unlock(&tpg->tpg_access_lock);
पूर्ण

अटल व्योम iscsit_clear_tpg_np_login_thपढ़ो(
	काष्ठा iscsi_tpg_np *tpg_np,
	काष्ठा iscsi_portal_group *tpg,
	bool shutकरोwn)
अणु
	अगर (!tpg_np->tpg_np) अणु
		pr_err("struct iscsi_tpg_np->tpg_np is NULL!\n");
		वापस;
	पूर्ण

	अगर (shutकरोwn)
		tpg_np->tpg_np->enabled = false;
	iscsit_reset_np_thपढ़ो(tpg_np->tpg_np, tpg_np, tpg, shutकरोwn);
पूर्ण

अटल व्योम iscsit_clear_tpg_np_login_thपढ़ोs(
	काष्ठा iscsi_portal_group *tpg,
	bool shutकरोwn)
अणु
	काष्ठा iscsi_tpg_np *tpg_np;

	spin_lock(&tpg->tpg_np_lock);
	list_क्रम_each_entry(tpg_np, &tpg->tpg_gnp_list, tpg_np_list) अणु
		अगर (!tpg_np->tpg_np) अणु
			pr_err("struct iscsi_tpg_np->tpg_np is NULL!\n");
			जारी;
		पूर्ण
		spin_unlock(&tpg->tpg_np_lock);
		iscsit_clear_tpg_np_login_thपढ़ो(tpg_np, tpg, shutकरोwn);
		spin_lock(&tpg->tpg_np_lock);
	पूर्ण
	spin_unlock(&tpg->tpg_np_lock);
पूर्ण

व्योम iscsit_tpg_dump_params(काष्ठा iscsi_portal_group *tpg)
अणु
	iscsi_prपूर्णांक_params(tpg->param_list);
पूर्ण

अटल व्योम iscsit_set_शेष_tpg_attribs(काष्ठा iscsi_portal_group *tpg)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	a->authentication = TA_AUTHENTICATION;
	a->login_समयout = TA_LOGIN_TIMEOUT;
	a->netअगर_समयout = TA_NETIF_TIMEOUT;
	a->शेष_cmdsn_depth = TA_DEFAULT_CMDSN_DEPTH;
	a->generate_node_acls = TA_GENERATE_NODE_ACLS;
	a->cache_dynamic_acls = TA_CACHE_DYNAMIC_ACLS;
	a->demo_mode_ग_लिखो_protect = TA_DEMO_MODE_WRITE_PROTECT;
	a->prod_mode_ग_लिखो_protect = TA_PROD_MODE_WRITE_PROTECT;
	a->demo_mode_discovery = TA_DEMO_MODE_DISCOVERY;
	a->शेष_erl = TA_DEFAULT_ERL;
	a->t10_pi = TA_DEFAULT_T10_PI;
	a->fabric_prot_type = TA_DEFAULT_FABRIC_PROT_TYPE;
	a->tpg_enabled_sendtarमाला_लो = TA_DEFAULT_TPG_ENABLED_SENDTARGETS;
	a->login_keys_workaround = TA_DEFAULT_LOGIN_KEYS_WORKAROUND;
पूर्ण

पूर्णांक iscsit_tpg_add_portal_group(काष्ठा iscsi_tiqn *tiqn, काष्ठा iscsi_portal_group *tpg)
अणु
	अगर (tpg->tpg_state != TPG_STATE_FREE) अणु
		pr_err("Unable to add iSCSI Target Portal Group: %d"
			" while not in TPG_STATE_FREE state.\n", tpg->tpgt);
		वापस -EEXIST;
	पूर्ण
	iscsit_set_शेष_tpg_attribs(tpg);

	अगर (iscsi_create_शेष_params(&tpg->param_list) < 0)
		जाओ err_out;

	tpg->tpg_attrib.tpg = tpg;

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state	= TPG_STATE_INACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	spin_lock(&tiqn->tiqn_tpg_lock);
	list_add_tail(&tpg->tpg_list, &tiqn->tiqn_tpg_list);
	tiqn->tiqn_ntpgs++;
	pr_debug("CORE[%s]_TPG[%hu] - Added iSCSI Target Portal Group\n",
			tiqn->tiqn, tpg->tpgt);
	spin_unlock(&tiqn->tiqn_tpg_lock);

	वापस 0;
err_out:
	अगर (tpg->param_list) अणु
		iscsi_release_param_list(tpg->param_list);
		tpg->param_list = शून्य;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

पूर्णांक iscsit_tpg_del_portal_group(
	काष्ठा iscsi_tiqn *tiqn,
	काष्ठा iscsi_portal_group *tpg,
	पूर्णांक क्रमce)
अणु
	u8 old_state = tpg->tpg_state;

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state = TPG_STATE_INACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	अगर (iscsit_release_sessions_क्रम_tpg(tpg, क्रमce) < 0) अणु
		pr_err("Unable to delete iSCSI Target Portal Group:"
			" %hu while active sessions exist, and force=0\n",
			tpg->tpgt);
		tpg->tpg_state = old_state;
		वापस -EPERM;
	पूर्ण

	अगर (tpg->param_list) अणु
		iscsi_release_param_list(tpg->param_list);
		tpg->param_list = शून्य;
	पूर्ण

	core_tpg_deरेजिस्टर(&tpg->tpg_se_tpg);

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state = TPG_STATE_FREE;
	spin_unlock(&tpg->tpg_state_lock);

	spin_lock(&tiqn->tiqn_tpg_lock);
	tiqn->tiqn_ntpgs--;
	list_del(&tpg->tpg_list);
	spin_unlock(&tiqn->tiqn_tpg_lock);

	pr_debug("CORE[%s]_TPG[%hu] - Deleted iSCSI Target Portal Group\n",
			tiqn->tiqn, tpg->tpgt);

	kमुक्त(tpg);
	वापस 0;
पूर्ण

पूर्णांक iscsit_tpg_enable_portal_group(काष्ठा iscsi_portal_group *tpg)
अणु
	काष्ठा iscsi_param *param;
	काष्ठा iscsi_tiqn *tiqn = tpg->tpg_tiqn;
	पूर्णांक ret;

	अगर (tpg->tpg_state == TPG_STATE_ACTIVE) अणु
		pr_err("iSCSI target portal group: %hu is already"
			" active, ignoring request.\n", tpg->tpgt);
		वापस -EINVAL;
	पूर्ण
	/*
	 * Make sure that AuthMethod करोes not contain None as an option
	 * unless explictly disabled.  Set the शेष to CHAP अगर authentication
	 * is enक्रमced (as per शेष), and हटाओ the NONE option.
	 */
	param = iscsi_find_param_from_key(AUTHMETHOD, tpg->param_list);
	अगर (!param)
		वापस -EINVAL;

	अगर (tpg->tpg_attrib.authentication) अणु
		अगर (!म_भेद(param->value, NONE)) अणु
			ret = iscsi_update_param_value(param, CHAP);
			अगर (ret)
				जाओ err;
		पूर्ण

		ret = iscsit_ta_authentication(tpg, 1);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	spin_lock(&tpg->tpg_state_lock);
	tpg->tpg_state = TPG_STATE_ACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	spin_lock(&tiqn->tiqn_tpg_lock);
	tiqn->tiqn_active_tpgs++;
	pr_debug("iSCSI_TPG[%hu] - Enabled iSCSI Target Portal Group\n",
			tpg->tpgt);
	spin_unlock(&tiqn->tiqn_tpg_lock);

	वापस 0;

err:
	वापस ret;
पूर्ण

पूर्णांक iscsit_tpg_disable_portal_group(काष्ठा iscsi_portal_group *tpg, पूर्णांक क्रमce)
अणु
	काष्ठा iscsi_tiqn *tiqn;
	u8 old_state = tpg->tpg_state;

	spin_lock(&tpg->tpg_state_lock);
	अगर (tpg->tpg_state == TPG_STATE_INACTIVE) अणु
		pr_err("iSCSI Target Portal Group: %hu is already"
			" inactive, ignoring request.\n", tpg->tpgt);
		spin_unlock(&tpg->tpg_state_lock);
		वापस -EINVAL;
	पूर्ण
	tpg->tpg_state = TPG_STATE_INACTIVE;
	spin_unlock(&tpg->tpg_state_lock);

	iscsit_clear_tpg_np_login_thपढ़ोs(tpg, false);

	अगर (iscsit_release_sessions_क्रम_tpg(tpg, क्रमce) < 0) अणु
		spin_lock(&tpg->tpg_state_lock);
		tpg->tpg_state = old_state;
		spin_unlock(&tpg->tpg_state_lock);
		pr_err("Unable to disable iSCSI Target Portal Group:"
			" %hu while active sessions exist, and force=0\n",
			tpg->tpgt);
		वापस -EPERM;
	पूर्ण

	tiqn = tpg->tpg_tiqn;
	अगर (!tiqn || (tpg == iscsit_global->discovery_tpg))
		वापस 0;

	spin_lock(&tiqn->tiqn_tpg_lock);
	tiqn->tiqn_active_tpgs--;
	pr_debug("iSCSI_TPG[%hu] - Disabled iSCSI Target Portal Group\n",
			tpg->tpgt);
	spin_unlock(&tiqn->tiqn_tpg_lock);

	वापस 0;
पूर्ण

काष्ठा iscsi_node_attrib *iscsit_tpg_get_node_attrib(
	काष्ठा iscsi_session *sess)
अणु
	काष्ठा se_session *se_sess = sess->se_sess;
	काष्ठा se_node_acl *se_nacl = se_sess->se_node_acl;
	काष्ठा iscsi_node_acl *acl = container_of(se_nacl, काष्ठा iscsi_node_acl,
					se_node_acl);

	वापस &acl->node_attrib;
पूर्ण

काष्ठा iscsi_tpg_np *iscsit_tpg_locate_child_np(
	काष्ठा iscsi_tpg_np *tpg_np,
	पूर्णांक network_transport)
अणु
	काष्ठा iscsi_tpg_np *tpg_np_child, *tpg_np_child_पंचांगp;

	spin_lock(&tpg_np->tpg_np_parent_lock);
	list_क्रम_each_entry_safe(tpg_np_child, tpg_np_child_पंचांगp,
			&tpg_np->tpg_np_parent_list, tpg_np_child_list) अणु
		अगर (tpg_np_child->tpg_np->np_network_transport ==
				network_transport) अणु
			spin_unlock(&tpg_np->tpg_np_parent_lock);
			वापस tpg_np_child;
		पूर्ण
	पूर्ण
	spin_unlock(&tpg_np->tpg_np_parent_lock);

	वापस शून्य;
पूर्ण

अटल bool iscsit_tpg_check_network_portal(
	काष्ठा iscsi_tiqn *tiqn,
	काष्ठा sockaddr_storage *sockaddr,
	पूर्णांक network_transport)
अणु
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tpg_np *tpg_np;
	काष्ठा iscsi_np *np;
	bool match = false;

	spin_lock(&tiqn->tiqn_tpg_lock);
	list_क्रम_each_entry(tpg, &tiqn->tiqn_tpg_list, tpg_list) अणु

		spin_lock(&tpg->tpg_np_lock);
		list_क्रम_each_entry(tpg_np, &tpg->tpg_gnp_list, tpg_np_list) अणु
			np = tpg_np->tpg_np;

			match = iscsit_check_np_match(sockaddr, np,
						network_transport);
			अगर (match)
				अवरोध;
		पूर्ण
		spin_unlock(&tpg->tpg_np_lock);
	पूर्ण
	spin_unlock(&tiqn->tiqn_tpg_lock);

	वापस match;
पूर्ण

काष्ठा iscsi_tpg_np *iscsit_tpg_add_network_portal(
	काष्ठा iscsi_portal_group *tpg,
	काष्ठा sockaddr_storage *sockaddr,
	काष्ठा iscsi_tpg_np *tpg_np_parent,
	पूर्णांक network_transport)
अणु
	काष्ठा iscsi_np *np;
	काष्ठा iscsi_tpg_np *tpg_np;

	अगर (!tpg_np_parent) अणु
		अगर (iscsit_tpg_check_network_portal(tpg->tpg_tiqn, sockaddr,
				network_transport)) अणु
			pr_err("Network Portal: %pISc already exists on a"
				" different TPG on %s\n", sockaddr,
				tpg->tpg_tiqn->tiqn);
			वापस ERR_PTR(-EEXIST);
		पूर्ण
	पूर्ण

	tpg_np = kzalloc(माप(काष्ठा iscsi_tpg_np), GFP_KERNEL);
	अगर (!tpg_np) अणु
		pr_err("Unable to allocate memory for"
				" struct iscsi_tpg_np.\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	np = iscsit_add_np(sockaddr, network_transport);
	अगर (IS_ERR(np)) अणु
		kमुक्त(tpg_np);
		वापस ERR_CAST(np);
	पूर्ण

	INIT_LIST_HEAD(&tpg_np->tpg_np_list);
	INIT_LIST_HEAD(&tpg_np->tpg_np_child_list);
	INIT_LIST_HEAD(&tpg_np->tpg_np_parent_list);
	spin_lock_init(&tpg_np->tpg_np_parent_lock);
	init_completion(&tpg_np->tpg_np_comp);
	kref_init(&tpg_np->tpg_np_kref);
	tpg_np->tpg_np		= np;
	tpg_np->tpg		= tpg;

	spin_lock(&tpg->tpg_np_lock);
	list_add_tail(&tpg_np->tpg_np_list, &tpg->tpg_gnp_list);
	tpg->num_tpg_nps++;
	अगर (tpg->tpg_tiqn)
		tpg->tpg_tiqn->tiqn_num_tpg_nps++;
	spin_unlock(&tpg->tpg_np_lock);

	अगर (tpg_np_parent) अणु
		tpg_np->tpg_np_parent = tpg_np_parent;
		spin_lock(&tpg_np_parent->tpg_np_parent_lock);
		list_add_tail(&tpg_np->tpg_np_child_list,
			&tpg_np_parent->tpg_np_parent_list);
		spin_unlock(&tpg_np_parent->tpg_np_parent_lock);
	पूर्ण

	pr_debug("CORE[%s] - Added Network Portal: %pISpc,%hu on %s\n",
		tpg->tpg_tiqn->tiqn, &np->np_sockaddr, tpg->tpgt,
		np->np_transport->name);

	वापस tpg_np;
पूर्ण

अटल पूर्णांक iscsit_tpg_release_np(
	काष्ठा iscsi_tpg_np *tpg_np,
	काष्ठा iscsi_portal_group *tpg,
	काष्ठा iscsi_np *np)
अणु
	iscsit_clear_tpg_np_login_thपढ़ो(tpg_np, tpg, true);

	pr_debug("CORE[%s] - Removed Network Portal: %pISpc,%hu on %s\n",
		tpg->tpg_tiqn->tiqn, &np->np_sockaddr, tpg->tpgt,
		np->np_transport->name);

	tpg_np->tpg_np = शून्य;
	tpg_np->tpg = शून्य;
	kमुक्त(tpg_np);
	/*
	 * iscsit_del_np() will shutकरोwn काष्ठा iscsi_np when last TPG reference is released.
	 */
	वापस iscsit_del_np(np);
पूर्ण

पूर्णांक iscsit_tpg_del_network_portal(
	काष्ठा iscsi_portal_group *tpg,
	काष्ठा iscsi_tpg_np *tpg_np)
अणु
	काष्ठा iscsi_np *np;
	काष्ठा iscsi_tpg_np *tpg_np_child, *tpg_np_child_पंचांगp;
	पूर्णांक ret = 0;

	np = tpg_np->tpg_np;
	अगर (!np) अणु
		pr_err("Unable to locate struct iscsi_np from"
				" struct iscsi_tpg_np\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!tpg_np->tpg_np_parent) अणु
		/*
		 * We are the parent tpg network portal.  Release all of the
		 * child tpg_np's (eg: the non ISCSI_TCP ones) on our parent
		 * list first.
		 */
		list_क्रम_each_entry_safe(tpg_np_child, tpg_np_child_पंचांगp,
				&tpg_np->tpg_np_parent_list,
				tpg_np_child_list) अणु
			ret = iscsit_tpg_del_network_portal(tpg, tpg_np_child);
			अगर (ret < 0)
				pr_err("iscsit_tpg_del_network_portal()"
					" failed: %d\n", ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We are not the parent ISCSI_TCP tpg network portal.  Release
		 * our own network portals from the child list.
		 */
		spin_lock(&tpg_np->tpg_np_parent->tpg_np_parent_lock);
		list_del(&tpg_np->tpg_np_child_list);
		spin_unlock(&tpg_np->tpg_np_parent->tpg_np_parent_lock);
	पूर्ण

	spin_lock(&tpg->tpg_np_lock);
	list_del(&tpg_np->tpg_np_list);
	tpg->num_tpg_nps--;
	अगर (tpg->tpg_tiqn)
		tpg->tpg_tiqn->tiqn_num_tpg_nps--;
	spin_unlock(&tpg->tpg_np_lock);

	वापस iscsit_tpg_release_np(tpg_np, tpg, np);
पूर्ण

पूर्णांक iscsit_ta_authentication(काष्ठा iscsi_portal_group *tpg, u32 authentication)
अणु
	अचिन्हित अक्षर buf1[256], buf2[256], *none = शून्य;
	पूर्णांक len;
	काष्ठा iscsi_param *param;
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((authentication != 1) && (authentication != 0)) अणु
		pr_err("Illegal value for authentication parameter:"
			" %u, ignoring request.\n", authentication);
		वापस -EINVAL;
	पूर्ण

	स_रखो(buf1, 0, माप(buf1));
	स_रखो(buf2, 0, माप(buf2));

	param = iscsi_find_param_from_key(AUTHMETHOD, tpg->param_list);
	अगर (!param)
		वापस -EINVAL;

	अगर (authentication) अणु
		snम_लिखो(buf1, माप(buf1), "%s", param->value);
		none = म_माला(buf1, NONE);
		अगर (!none)
			जाओ out;
		अगर (!म_भेदन(none + 4, ",", 1)) अणु
			अगर (!म_भेद(buf1, none))
				प्र_लिखो(buf2, "%s", none+5);
			अन्यथा अणु
				none--;
				*none = '\0';
				len = प्र_लिखो(buf2, "%s", buf1);
				none += 5;
				प्र_लिखो(buf2 + len, "%s", none);
			पूर्ण
		पूर्ण अन्यथा अणु
			none--;
			*none = '\0';
			प्र_लिखो(buf2, "%s", buf1);
		पूर्ण
		अगर (iscsi_update_param_value(param, buf2) < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		snम_लिखो(buf1, माप(buf1), "%s", param->value);
		none = म_माला(buf1, NONE);
		अगर (none)
			जाओ out;
		strlcat(buf1, "," NONE, माप(buf1));
		अगर (iscsi_update_param_value(param, buf1) < 0)
			वापस -EINVAL;
	पूर्ण

out:
	a->authentication = authentication;
	pr_debug("%s iSCSI Authentication Methods for TPG: %hu.\n",
		a->authentication ? "Enforcing" : "Disabling", tpg->tpgt);

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_login_समयout(
	काष्ठा iscsi_portal_group *tpg,
	u32 login_समयout)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर (login_समयout > TA_LOGIN_TIMEOUT_MAX) अणु
		pr_err("Requested Login Timeout %u larger than maximum"
			" %u\n", login_समयout, TA_LOGIN_TIMEOUT_MAX);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (login_समयout < TA_LOGIN_TIMEOUT_MIN) अणु
		pr_err("Requested Logout Timeout %u smaller than"
			" minimum %u\n", login_समयout, TA_LOGIN_TIMEOUT_MIN);
		वापस -EINVAL;
	पूर्ण

	a->login_समयout = login_समयout;
	pr_debug("Set Logout Timeout to %u for Target Portal Group"
		" %hu\n", a->login_समयout, tpg->tpgt);

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_netअगर_समयout(
	काष्ठा iscsi_portal_group *tpg,
	u32 netअगर_समयout)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर (netअगर_समयout > TA_NETIF_TIMEOUT_MAX) अणु
		pr_err("Requested Network Interface Timeout %u larger"
			" than maximum %u\n", netअगर_समयout,
				TA_NETIF_TIMEOUT_MAX);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (netअगर_समयout < TA_NETIF_TIMEOUT_MIN) अणु
		pr_err("Requested Network Interface Timeout %u smaller"
			" than minimum %u\n", netअगर_समयout,
				TA_NETIF_TIMEOUT_MIN);
		वापस -EINVAL;
	पूर्ण

	a->netअगर_समयout = netअगर_समयout;
	pr_debug("Set Network Interface Timeout to %u for"
		" Target Portal Group %hu\n", a->netअगर_समयout, tpg->tpgt);

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_generate_node_acls(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	a->generate_node_acls = flag;
	pr_debug("iSCSI_TPG[%hu] - Generate Initiator Portal Group ACLs: %s\n",
		tpg->tpgt, (a->generate_node_acls) ? "Enabled" : "Disabled");

	अगर (flag == 1 && a->cache_dynamic_acls == 0) अणु
		pr_debug("Explicitly setting cache_dynamic_acls=1 when "
			"generate_node_acls=1\n");
		a->cache_dynamic_acls = 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_शेष_cmdsn_depth(
	काष्ठा iscsi_portal_group *tpg,
	u32 tcq_depth)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर (tcq_depth > TA_DEFAULT_CMDSN_DEPTH_MAX) अणु
		pr_err("Requested Default Queue Depth: %u larger"
			" than maximum %u\n", tcq_depth,
				TA_DEFAULT_CMDSN_DEPTH_MAX);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (tcq_depth < TA_DEFAULT_CMDSN_DEPTH_MIN) अणु
		pr_err("Requested Default Queue Depth: %u smaller"
			" than minimum %u\n", tcq_depth,
				TA_DEFAULT_CMDSN_DEPTH_MIN);
		वापस -EINVAL;
	पूर्ण

	a->शेष_cmdsn_depth = tcq_depth;
	pr_debug("iSCSI_TPG[%hu] - Set Default CmdSN TCQ Depth to %u\n",
		tpg->tpgt, a->शेष_cmdsn_depth);

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_cache_dynamic_acls(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	अगर (a->generate_node_acls == 1 && flag == 0) अणु
		pr_debug("Skipping cache_dynamic_acls=0 when"
			" generate_node_acls=1\n");
		वापस 0;
	पूर्ण

	a->cache_dynamic_acls = flag;
	pr_debug("iSCSI_TPG[%hu] - Cache Dynamic Initiator Portal Group"
		" ACLs %s\n", tpg->tpgt, (a->cache_dynamic_acls) ?
		"Enabled" : "Disabled");

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_demo_mode_ग_लिखो_protect(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	a->demo_mode_ग_लिखो_protect = flag;
	pr_debug("iSCSI_TPG[%hu] - Demo Mode Write Protect bit: %s\n",
		tpg->tpgt, (a->demo_mode_ग_लिखो_protect) ? "ON" : "OFF");

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_prod_mode_ग_लिखो_protect(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	a->prod_mode_ग_लिखो_protect = flag;
	pr_debug("iSCSI_TPG[%hu] - Production Mode Write Protect bit:"
		" %s\n", tpg->tpgt, (a->prod_mode_ग_लिखो_protect) ?
		"ON" : "OFF");

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_demo_mode_discovery(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	a->demo_mode_discovery = flag;
	pr_debug("iSCSI_TPG[%hu] - Demo Mode Discovery bit:"
		" %s\n", tpg->tpgt, (a->demo_mode_discovery) ?
		"ON" : "OFF");

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_शेष_erl(
	काष्ठा iscsi_portal_group *tpg,
	u32 शेष_erl)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((शेष_erl != 0) && (शेष_erl != 1) && (शेष_erl != 2)) अणु
		pr_err("Illegal value for default_erl: %u\n", शेष_erl);
		वापस -EINVAL;
	पूर्ण

	a->शेष_erl = शेष_erl;
	pr_debug("iSCSI_TPG[%hu] - DefaultERL: %u\n", tpg->tpgt, a->शेष_erl);

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_t10_pi(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	a->t10_pi = flag;
	pr_debug("iSCSI_TPG[%hu] - T10 Protection information bit:"
		" %s\n", tpg->tpgt, (a->t10_pi) ?
		"ON" : "OFF");

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_fabric_prot_type(
	काष्ठा iscsi_portal_group *tpg,
	u32 prot_type)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((prot_type != 0) && (prot_type != 1) && (prot_type != 3)) अणु
		pr_err("Illegal value for fabric_prot_type: %u\n", prot_type);
		वापस -EINVAL;
	पूर्ण

	a->fabric_prot_type = prot_type;
	pr_debug("iSCSI_TPG[%hu] - T10 Fabric Protection Type: %u\n",
		 tpg->tpgt, prot_type);

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_tpg_enabled_sendtarमाला_लो(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	a->tpg_enabled_sendtarमाला_लो = flag;
	pr_debug("iSCSI_TPG[%hu] - TPG enabled bit required for SendTargets:"
		" %s\n", tpg->tpgt, (a->tpg_enabled_sendtarमाला_लो) ? "ON" : "OFF");

	वापस 0;
पूर्ण

पूर्णांक iscsit_ta_login_keys_workaround(
	काष्ठा iscsi_portal_group *tpg,
	u32 flag)
अणु
	काष्ठा iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	अगर ((flag != 0) && (flag != 1)) अणु
		pr_err("Illegal value %d\n", flag);
		वापस -EINVAL;
	पूर्ण

	a->login_keys_workaround = flag;
	pr_debug("iSCSI_TPG[%hu] - TPG enabled bit for login keys workaround: %s ",
		tpg->tpgt, (a->login_keys_workaround) ? "ON" : "OFF");

	वापस 0;
पूर्ण
