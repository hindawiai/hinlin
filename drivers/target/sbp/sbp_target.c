<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SBP2 target driver (SCSI over IEEE1394 in target mode)
 *
 * Copyright (C) 2011  Chris Boot <bootc@bootc.net>
 */

#घोषणा KMSG_COMPONENT "sbp_target"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "sbp_target.h"

/* FireWire address region क्रम management and command block address handlers */
अटल स्थिर काष्ठा fw_address_region sbp_रेजिस्टर_region = अणु
	.start	= CSR_REGISTER_BASE + 0x10000,
	.end	= 0x1000000000000ULL,
पूर्ण;

अटल स्थिर u32 sbp_unit_directory_ढाँचा[] = अणु
	0x1200609e, /* unit_specअगरier_id: NCITS/T10 */
	0x13010483, /* unit_sw_version: 1155D Rev 4 */
	0x3800609e, /* command_set_specअगरier_id: NCITS/T10 */
	0x390104d8, /* command_set: SPC-2 */
	0x3b000000, /* command_set_revision: 0 */
	0x3c000001, /* firmware_revision: 1 */
पूर्ण;

#घोषणा SESSION_MAINTEन_अंकCE_INTERVAL HZ

अटल atomic_t login_id = ATOMIC_INIT(0);

अटल व्योम session_मुख्यtenance_work(काष्ठा work_काष्ठा *);
अटल पूर्णांक sbp_run_transaction(काष्ठा fw_card *, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक,
		अचिन्हित दीर्घ दीर्घ, व्योम *, माप_प्रकार);

अटल पूर्णांक पढ़ो_peer_guid(u64 *guid, स्थिर काष्ठा sbp_management_request *req)
अणु
	पूर्णांक ret;
	__be32 high, low;

	ret = sbp_run_transaction(req->card, TCODE_READ_QUADLET_REQUEST,
			req->node_addr, req->generation, req->speed,
			(CSR_REGISTER_BASE | CSR_CONFIG_ROM) + 3 * 4,
			&high, माप(high));
	अगर (ret != RCODE_COMPLETE)
		वापस ret;

	ret = sbp_run_transaction(req->card, TCODE_READ_QUADLET_REQUEST,
			req->node_addr, req->generation, req->speed,
			(CSR_REGISTER_BASE | CSR_CONFIG_ROM) + 4 * 4,
			&low, माप(low));
	अगर (ret != RCODE_COMPLETE)
		वापस ret;

	*guid = (u64)be32_to_cpu(high) << 32 | be32_to_cpu(low);

	वापस RCODE_COMPLETE;
पूर्ण

अटल काष्ठा sbp_session *sbp_session_find_by_guid(
	काष्ठा sbp_tpg *tpg, u64 guid)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा sbp_session *sess, *found = शून्य;

	spin_lock_bh(&tpg->se_tpg.session_lock);
	list_क्रम_each_entry(se_sess, &tpg->se_tpg.tpg_sess_list, sess_list) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess->guid == guid)
			found = sess;
	पूर्ण
	spin_unlock_bh(&tpg->se_tpg.session_lock);

	वापस found;
पूर्ण

अटल काष्ठा sbp_login_descriptor *sbp_login_find_by_lun(
		काष्ठा sbp_session *session, u32 unpacked_lun)
अणु
	काष्ठा sbp_login_descriptor *login, *found = शून्य;

	spin_lock_bh(&session->lock);
	list_क्रम_each_entry(login, &session->login_list, link) अणु
		अगर (login->login_lun == unpacked_lun)
			found = login;
	पूर्ण
	spin_unlock_bh(&session->lock);

	वापस found;
पूर्ण

अटल पूर्णांक sbp_login_count_all_by_lun(
		काष्ठा sbp_tpg *tpg,
		u32 unpacked_lun,
		पूर्णांक exclusive)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा sbp_session *sess;
	काष्ठा sbp_login_descriptor *login;
	पूर्णांक count = 0;

	spin_lock_bh(&tpg->se_tpg.session_lock);
	list_क्रम_each_entry(se_sess, &tpg->se_tpg.tpg_sess_list, sess_list) अणु
		sess = se_sess->fabric_sess_ptr;

		spin_lock_bh(&sess->lock);
		list_क्रम_each_entry(login, &sess->login_list, link) अणु
			अगर (login->login_lun != unpacked_lun)
				जारी;

			अगर (!exclusive || login->exclusive)
				count++;
		पूर्ण
		spin_unlock_bh(&sess->lock);
	पूर्ण
	spin_unlock_bh(&tpg->se_tpg.session_lock);

	वापस count;
पूर्ण

अटल काष्ठा sbp_login_descriptor *sbp_login_find_by_id(
	काष्ठा sbp_tpg *tpg, पूर्णांक login_id)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा sbp_session *sess;
	काष्ठा sbp_login_descriptor *login, *found = शून्य;

	spin_lock_bh(&tpg->se_tpg.session_lock);
	list_क्रम_each_entry(se_sess, &tpg->se_tpg.tpg_sess_list, sess_list) अणु
		sess = se_sess->fabric_sess_ptr;

		spin_lock_bh(&sess->lock);
		list_क्रम_each_entry(login, &sess->login_list, link) अणु
			अगर (login->login_id == login_id)
				found = login;
		पूर्ण
		spin_unlock_bh(&sess->lock);
	पूर्ण
	spin_unlock_bh(&tpg->se_tpg.session_lock);

	वापस found;
पूर्ण

अटल u32 sbp_get_lun_from_tpg(काष्ठा sbp_tpg *tpg, u32 login_lun, पूर्णांक *err)
अणु
	काष्ठा se_portal_group *se_tpg = &tpg->se_tpg;
	काष्ठा se_lun *se_lun;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(se_lun, &se_tpg->tpg_lun_hlist, link) अणु
		अगर (se_lun->unpacked_lun == login_lun) अणु
			rcu_पढ़ो_unlock();
			*err = 0;
			वापस login_lun;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	*err = -ENODEV;
	वापस login_lun;
पूर्ण

अटल काष्ठा sbp_session *sbp_session_create(
		काष्ठा sbp_tpg *tpg,
		u64 guid)
अणु
	काष्ठा sbp_session *sess;
	पूर्णांक ret;
	अक्षर guid_str[17];

	snम_लिखो(guid_str, माप(guid_str), "%016llx", guid);

	sess = kदो_स्मृति(माप(*sess), GFP_KERNEL);
	अगर (!sess)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&sess->lock);
	INIT_LIST_HEAD(&sess->login_list);
	INIT_DELAYED_WORK(&sess->मुख्यt_work, session_मुख्यtenance_work);
	sess->guid = guid;

	sess->se_sess = target_setup_session(&tpg->se_tpg, 128,
					     माप(काष्ठा sbp_target_request),
					     TARGET_PROT_NORMAL, guid_str,
					     sess, शून्य);
	अगर (IS_ERR(sess->se_sess)) अणु
		pr_err("failed to init se_session\n");
		ret = PTR_ERR(sess->se_sess);
		kमुक्त(sess);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस sess;
पूर्ण

अटल व्योम sbp_session_release(काष्ठा sbp_session *sess, bool cancel_work)
अणु
	spin_lock_bh(&sess->lock);
	अगर (!list_empty(&sess->login_list)) अणु
		spin_unlock_bh(&sess->lock);
		वापस;
	पूर्ण
	spin_unlock_bh(&sess->lock);

	अगर (cancel_work)
		cancel_delayed_work_sync(&sess->मुख्यt_work);

	target_हटाओ_session(sess->se_sess);

	अगर (sess->card)
		fw_card_put(sess->card);

	kमुक्त(sess);
पूर्ण

अटल व्योम sbp_target_agent_unरेजिस्टर(काष्ठा sbp_target_agent *);

अटल व्योम sbp_login_release(काष्ठा sbp_login_descriptor *login,
	bool cancel_work)
अणु
	काष्ठा sbp_session *sess = login->sess;

	/* FIXME: पात/रुको on tasks */

	sbp_target_agent_unरेजिस्टर(login->tgt_agt);

	अगर (sess) अणु
		spin_lock_bh(&sess->lock);
		list_del(&login->link);
		spin_unlock_bh(&sess->lock);

		sbp_session_release(sess, cancel_work);
	पूर्ण

	kमुक्त(login);
पूर्ण

अटल काष्ठा sbp_target_agent *sbp_target_agent_रेजिस्टर(
	काष्ठा sbp_login_descriptor *);

अटल व्योम sbp_management_request_login(
	काष्ठा sbp_management_agent *agent, काष्ठा sbp_management_request *req,
	पूर्णांक *status_data_size)
अणु
	काष्ठा sbp_tport *tport = agent->tport;
	काष्ठा sbp_tpg *tpg = tport->tpg;
	काष्ठा sbp_session *sess;
	काष्ठा sbp_login_descriptor *login;
	काष्ठा sbp_login_response_block *response;
	u64 guid;
	u32 unpacked_lun;
	पूर्णांक login_response_len, ret;

	unpacked_lun = sbp_get_lun_from_tpg(tpg,
			LOGIN_ORB_LUN(be32_to_cpu(req->orb.misc)), &ret);
	अगर (ret) अणु
		pr_notice("login to unknown LUN: %d\n",
			LOGIN_ORB_LUN(be32_to_cpu(req->orb.misc)));

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_LUN_NOTSUPP));
		वापस;
	पूर्ण

	ret = पढ़ो_peer_guid(&guid, req);
	अगर (ret != RCODE_COMPLETE) अणु
		pr_warn("failed to read peer GUID: %d\n", ret);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_TRANSPORT_FAILURE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_UNSPECIFIED_ERROR));
		वापस;
	पूर्ण

	pr_notice("mgt_agent LOGIN to LUN %d from %016llx\n",
		unpacked_lun, guid);

	sess = sbp_session_find_by_guid(tpg, guid);
	अगर (sess) अणु
		login = sbp_login_find_by_lun(sess, unpacked_lun);
		अगर (login) अणु
			pr_notice("initiator already logged-in\n");

			/*
			 * SBP-2 R4 says we should वापस access denied, but
			 * that can confuse initiators. Instead we need to
			 * treat this like a reconnect, but send the login
			 * response block like a fresh login.
			 *
			 * This is required particularly in the हाल of Apple
			 * devices booting off the FireWire target, where
			 * the firmware has an active login to the target. When
			 * the OS takes control of the session it issues its own
			 * LOGIN rather than a RECONNECT. To aव्योम the machine
			 * रुकोing until the reconnect_hold expires, we can skip
			 * the ACCESS_DENIED errors to speed things up.
			 */

			जाओ alपढ़ोy_logged_in;
		पूर्ण
	पूर्ण

	/*
	 * check exclusive bit in login request
	 * reject with access_denied अगर any logins present
	 */
	अगर (LOGIN_ORB_EXCLUSIVE(be32_to_cpu(req->orb.misc)) &&
			sbp_login_count_all_by_lun(tpg, unpacked_lun, 0)) अणु
		pr_warn("refusing exclusive login with other active logins\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		वापस;
	पूर्ण

	/*
	 * check exclusive bit in any existing login descriptor
	 * reject with access_denied अगर any exclusive logins present
	 */
	अगर (sbp_login_count_all_by_lun(tpg, unpacked_lun, 1)) अणु
		pr_warn("refusing login while another exclusive login present\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		वापस;
	पूर्ण

	/*
	 * check we haven't exceeded the number of allowed logins
	 * reject with resources_unavailable अगर we have
	 */
	अगर (sbp_login_count_all_by_lun(tpg, unpacked_lun, 0) >=
			tport->max_logins_per_lun) अणु
		pr_warn("max number of logins reached\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_RESOURCES_UNAVAIL));
		वापस;
	पूर्ण

	अगर (!sess) अणु
		sess = sbp_session_create(tpg, guid);
		अगर (IS_ERR(sess)) अणु
			चयन (PTR_ERR(sess)) अणु
			हाल -EPERM:
				ret = SBP_STATUS_ACCESS_DENIED;
				अवरोध;
			शेष:
				ret = SBP_STATUS_RESOURCES_UNAVAIL;
				अवरोध;
			पूर्ण

			req->status.status = cpu_to_be32(
				STATUS_BLOCK_RESP(
					STATUS_RESP_REQUEST_COMPLETE) |
				STATUS_BLOCK_SBP_STATUS(ret));
			वापस;
		पूर्ण

		sess->node_id = req->node_addr;
		sess->card = fw_card_get(req->card);
		sess->generation = req->generation;
		sess->speed = req->speed;

		schedule_delayed_work(&sess->मुख्यt_work,
				SESSION_MAINTEन_अंकCE_INTERVAL);
	पूर्ण

	/* only take the latest reconnect_hold पूर्णांकo account */
	sess->reconnect_hold = min(
		1 << LOGIN_ORB_RECONNECT(be32_to_cpu(req->orb.misc)),
		tport->max_reconnect_समयout) - 1;

	login = kदो_स्मृति(माप(*login), GFP_KERNEL);
	अगर (!login) अणु
		pr_err("failed to allocate login descriptor\n");

		sbp_session_release(sess, true);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_RESOURCES_UNAVAIL));
		वापस;
	पूर्ण

	login->sess = sess;
	login->login_lun = unpacked_lun;
	login->status_fअगरo_addr = sbp2_poपूर्णांकer_to_addr(&req->orb.status_fअगरo);
	login->exclusive = LOGIN_ORB_EXCLUSIVE(be32_to_cpu(req->orb.misc));
	login->login_id = atomic_inc_वापस(&login_id);

	login->tgt_agt = sbp_target_agent_रेजिस्टर(login);
	अगर (IS_ERR(login->tgt_agt)) अणु
		ret = PTR_ERR(login->tgt_agt);
		pr_err("failed to map command block handler: %d\n", ret);

		sbp_session_release(sess, true);
		kमुक्त(login);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_RESOURCES_UNAVAIL));
		वापस;
	पूर्ण

	spin_lock_bh(&sess->lock);
	list_add_tail(&login->link, &sess->login_list);
	spin_unlock_bh(&sess->lock);

alपढ़ोy_logged_in:
	response = kzalloc(माप(*response), GFP_KERNEL);
	अगर (!response) अणु
		pr_err("failed to allocate login response block\n");

		sbp_login_release(login, true);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_RESOURCES_UNAVAIL));
		वापस;
	पूर्ण

	login_response_len = clamp_val(
			LOGIN_ORB_RESPONSE_LENGTH(be32_to_cpu(req->orb.length)),
			12, माप(*response));
	response->misc = cpu_to_be32(
		((login_response_len & 0xffff) << 16) |
		(login->login_id & 0xffff));
	response->reconnect_hold = cpu_to_be32(sess->reconnect_hold & 0xffff);
	addr_to_sbp2_poपूर्णांकer(login->tgt_agt->handler.offset,
		&response->command_block_agent);

	ret = sbp_run_transaction(sess->card, TCODE_WRITE_BLOCK_REQUEST,
		sess->node_id, sess->generation, sess->speed,
		sbp2_poपूर्णांकer_to_addr(&req->orb.ptr2), response,
		login_response_len);
	अगर (ret != RCODE_COMPLETE) अणु
		pr_debug("failed to write login response block: %x\n", ret);

		kमुक्त(response);
		sbp_login_release(login, true);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_TRANSPORT_FAILURE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_UNSPECIFIED_ERROR));
		वापस;
	पूर्ण

	kमुक्त(response);

	req->status.status = cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
पूर्ण

अटल व्योम sbp_management_request_query_logins(
	काष्ठा sbp_management_agent *agent, काष्ठा sbp_management_request *req,
	पूर्णांक *status_data_size)
अणु
	pr_notice("QUERY LOGINS not implemented\n");
	/* FIXME: implement */

	req->status.status = cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));
पूर्ण

अटल व्योम sbp_management_request_reconnect(
	काष्ठा sbp_management_agent *agent, काष्ठा sbp_management_request *req,
	पूर्णांक *status_data_size)
अणु
	काष्ठा sbp_tport *tport = agent->tport;
	काष्ठा sbp_tpg *tpg = tport->tpg;
	पूर्णांक ret;
	u64 guid;
	काष्ठा sbp_login_descriptor *login;

	ret = पढ़ो_peer_guid(&guid, req);
	अगर (ret != RCODE_COMPLETE) अणु
		pr_warn("failed to read peer GUID: %d\n", ret);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_TRANSPORT_FAILURE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_UNSPECIFIED_ERROR));
		वापस;
	पूर्ण

	pr_notice("mgt_agent RECONNECT from %016llx\n", guid);

	login = sbp_login_find_by_id(tpg,
		RECONNECT_ORB_LOGIN_ID(be32_to_cpu(req->orb.misc)));

	अगर (!login) अणु
		pr_err("mgt_agent RECONNECT unknown login ID\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		वापस;
	पूर्ण

	अगर (login->sess->guid != guid) अणु
		pr_err("mgt_agent RECONNECT login GUID doesn't match\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		वापस;
	पूर्ण

	spin_lock_bh(&login->sess->lock);
	अगर (login->sess->card)
		fw_card_put(login->sess->card);

	/* update the node details */
	login->sess->generation = req->generation;
	login->sess->node_id = req->node_addr;
	login->sess->card = fw_card_get(req->card);
	login->sess->speed = req->speed;
	spin_unlock_bh(&login->sess->lock);

	req->status.status = cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
पूर्ण

अटल व्योम sbp_management_request_logout(
	काष्ठा sbp_management_agent *agent, काष्ठा sbp_management_request *req,
	पूर्णांक *status_data_size)
अणु
	काष्ठा sbp_tport *tport = agent->tport;
	काष्ठा sbp_tpg *tpg = tport->tpg;
	पूर्णांक id;
	काष्ठा sbp_login_descriptor *login;

	id = LOGOUT_ORB_LOGIN_ID(be32_to_cpu(req->orb.misc));

	login = sbp_login_find_by_id(tpg, id);
	अगर (!login) अणु
		pr_warn("cannot find login: %d\n", id);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_LOGIN_ID_UNKNOWN));
		वापस;
	पूर्ण

	pr_info("mgt_agent LOGOUT from LUN %d session %d\n",
		login->login_lun, login->login_id);

	अगर (req->node_addr != login->sess->node_id) अणु
		pr_warn("logout from different node ID\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		वापस;
	पूर्ण

	sbp_login_release(login, true);

	req->status.status = cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
पूर्ण

अटल व्योम session_check_क्रम_reset(काष्ठा sbp_session *sess)
अणु
	bool card_valid = false;

	spin_lock_bh(&sess->lock);

	अगर (sess->card) अणु
		spin_lock_irq(&sess->card->lock);
		card_valid = (sess->card->local_node != शून्य);
		spin_unlock_irq(&sess->card->lock);

		अगर (!card_valid) अणु
			fw_card_put(sess->card);
			sess->card = शून्य;
		पूर्ण
	पूर्ण

	अगर (!card_valid || (sess->generation != sess->card->generation)) अणु
		pr_info("Waiting for reconnect from node: %016llx\n",
				sess->guid);

		sess->node_id = -1;
		sess->reconnect_expires = get_jअगरfies_64() +
			((sess->reconnect_hold + 1) * HZ);
	पूर्ण

	spin_unlock_bh(&sess->lock);
पूर्ण

अटल व्योम session_reconnect_expired(काष्ठा sbp_session *sess)
अणु
	काष्ठा sbp_login_descriptor *login, *temp;
	LIST_HEAD(login_list);

	pr_info("Reconnect timer expired for node: %016llx\n", sess->guid);

	spin_lock_bh(&sess->lock);
	list_क्रम_each_entry_safe(login, temp, &sess->login_list, link) अणु
		login->sess = शून्य;
		list_move_tail(&login->link, &login_list);
	पूर्ण
	spin_unlock_bh(&sess->lock);

	list_क्रम_each_entry_safe(login, temp, &login_list, link) अणु
		list_del(&login->link);
		sbp_login_release(login, false);
	पूर्ण

	sbp_session_release(sess, false);
पूर्ण

अटल व्योम session_मुख्यtenance_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbp_session *sess = container_of(work, काष्ठा sbp_session,
			मुख्यt_work.work);

	/* could be called जबतक tearing करोwn the session */
	spin_lock_bh(&sess->lock);
	अगर (list_empty(&sess->login_list)) अणु
		spin_unlock_bh(&sess->lock);
		वापस;
	पूर्ण
	spin_unlock_bh(&sess->lock);

	अगर (sess->node_id != -1) अणु
		/* check क्रम bus reset and make node_id invalid */
		session_check_क्रम_reset(sess);

		schedule_delayed_work(&sess->मुख्यt_work,
				SESSION_MAINTEन_अंकCE_INTERVAL);
	पूर्ण अन्यथा अगर (!समय_after64(get_jअगरfies_64(), sess->reconnect_expires)) अणु
		/* still रुकोing क्रम reconnect */
		schedule_delayed_work(&sess->मुख्यt_work,
				SESSION_MAINTEन_अंकCE_INTERVAL);
	पूर्ण अन्यथा अणु
		/* reconnect समयout has expired */
		session_reconnect_expired(sess);
	पूर्ण
पूर्ण

अटल पूर्णांक tgt_agent_rw_agent_state(काष्ठा fw_card *card, पूर्णांक tcode, व्योम *data,
		काष्ठा sbp_target_agent *agent)
अणु
	पूर्णांक state;

	चयन (tcode) अणु
	हाल TCODE_READ_QUADLET_REQUEST:
		pr_debug("tgt_agent AGENT_STATE READ\n");

		spin_lock_bh(&agent->lock);
		state = agent->state;
		spin_unlock_bh(&agent->lock);

		*(__be32 *)data = cpu_to_be32(state);

		वापस RCODE_COMPLETE;

	हाल TCODE_WRITE_QUADLET_REQUEST:
		/* ignored */
		वापस RCODE_COMPLETE;

	शेष:
		वापस RCODE_TYPE_ERROR;
	पूर्ण
पूर्ण

अटल पूर्णांक tgt_agent_rw_agent_reset(काष्ठा fw_card *card, पूर्णांक tcode, व्योम *data,
		काष्ठा sbp_target_agent *agent)
अणु
	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
		pr_debug("tgt_agent AGENT_RESET\n");
		spin_lock_bh(&agent->lock);
		agent->state = AGENT_STATE_RESET;
		spin_unlock_bh(&agent->lock);
		वापस RCODE_COMPLETE;

	शेष:
		वापस RCODE_TYPE_ERROR;
	पूर्ण
पूर्ण

अटल पूर्णांक tgt_agent_rw_orb_poपूर्णांकer(काष्ठा fw_card *card, पूर्णांक tcode, व्योम *data,
		काष्ठा sbp_target_agent *agent)
अणु
	काष्ठा sbp2_poपूर्णांकer *ptr = data;

	चयन (tcode) अणु
	हाल TCODE_WRITE_BLOCK_REQUEST:
		spin_lock_bh(&agent->lock);
		अगर (agent->state != AGENT_STATE_SUSPENDED &&
				agent->state != AGENT_STATE_RESET) अणु
			spin_unlock_bh(&agent->lock);
			pr_notice("Ignoring ORB_POINTER write while active.\n");
			वापस RCODE_CONFLICT_ERROR;
		पूर्ण
		agent->state = AGENT_STATE_ACTIVE;
		spin_unlock_bh(&agent->lock);

		agent->orb_poपूर्णांकer = sbp2_poपूर्णांकer_to_addr(ptr);
		agent->करोorbell = false;

		pr_debug("tgt_agent ORB_POINTER write: 0x%llx\n",
				agent->orb_poपूर्णांकer);

		queue_work(प्रणाली_unbound_wq, &agent->work);

		वापस RCODE_COMPLETE;

	हाल TCODE_READ_BLOCK_REQUEST:
		pr_debug("tgt_agent ORB_POINTER READ\n");
		spin_lock_bh(&agent->lock);
		addr_to_sbp2_poपूर्णांकer(agent->orb_poपूर्णांकer, ptr);
		spin_unlock_bh(&agent->lock);
		वापस RCODE_COMPLETE;

	शेष:
		वापस RCODE_TYPE_ERROR;
	पूर्ण
पूर्ण

अटल पूर्णांक tgt_agent_rw_करोorbell(काष्ठा fw_card *card, पूर्णांक tcode, व्योम *data,
		काष्ठा sbp_target_agent *agent)
अणु
	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
		spin_lock_bh(&agent->lock);
		अगर (agent->state != AGENT_STATE_SUSPENDED) अणु
			spin_unlock_bh(&agent->lock);
			pr_debug("Ignoring DOORBELL while active.\n");
			वापस RCODE_CONFLICT_ERROR;
		पूर्ण
		agent->state = AGENT_STATE_ACTIVE;
		spin_unlock_bh(&agent->lock);

		agent->करोorbell = true;

		pr_debug("tgt_agent DOORBELL\n");

		queue_work(प्रणाली_unbound_wq, &agent->work);

		वापस RCODE_COMPLETE;

	हाल TCODE_READ_QUADLET_REQUEST:
		वापस RCODE_COMPLETE;

	शेष:
		वापस RCODE_TYPE_ERROR;
	पूर्ण
पूर्ण

अटल पूर्णांक tgt_agent_rw_unsolicited_status_enable(काष्ठा fw_card *card,
		पूर्णांक tcode, व्योम *data, काष्ठा sbp_target_agent *agent)
अणु
	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
		pr_debug("tgt_agent UNSOLICITED_STATUS_ENABLE\n");
		/* ignored as we करोn't send unsolicited status */
		वापस RCODE_COMPLETE;

	हाल TCODE_READ_QUADLET_REQUEST:
		वापस RCODE_COMPLETE;

	शेष:
		वापस RCODE_TYPE_ERROR;
	पूर्ण
पूर्ण

अटल व्योम tgt_agent_rw(काष्ठा fw_card *card, काष्ठा fw_request *request,
		पूर्णांक tcode, पूर्णांक destination, पूर्णांक source, पूर्णांक generation,
		अचिन्हित दीर्घ दीर्घ offset, व्योम *data, माप_प्रकार length,
		व्योम *callback_data)
अणु
	काष्ठा sbp_target_agent *agent = callback_data;
	काष्ठा sbp_session *sess = agent->login->sess;
	पूर्णांक sess_gen, sess_node, rcode;

	spin_lock_bh(&sess->lock);
	sess_gen = sess->generation;
	sess_node = sess->node_id;
	spin_unlock_bh(&sess->lock);

	अगर (generation != sess_gen) अणु
		pr_notice("ignoring request with wrong generation\n");
		rcode = RCODE_TYPE_ERROR;
		जाओ out;
	पूर्ण

	अगर (source != sess_node) अणु
		pr_notice("ignoring request from foreign node (%x != %x)\n",
				source, sess_node);
		rcode = RCODE_TYPE_ERROR;
		जाओ out;
	पूर्ण

	/* turn offset पूर्णांकo the offset from the start of the block */
	offset -= agent->handler.offset;

	अगर (offset == 0x00 && length == 4) अणु
		/* AGENT_STATE */
		rcode = tgt_agent_rw_agent_state(card, tcode, data, agent);
	पूर्ण अन्यथा अगर (offset == 0x04 && length == 4) अणु
		/* AGENT_RESET */
		rcode = tgt_agent_rw_agent_reset(card, tcode, data, agent);
	पूर्ण अन्यथा अगर (offset == 0x08 && length == 8) अणु
		/* ORB_POINTER */
		rcode = tgt_agent_rw_orb_poपूर्णांकer(card, tcode, data, agent);
	पूर्ण अन्यथा अगर (offset == 0x10 && length == 4) अणु
		/* DOORBELL */
		rcode = tgt_agent_rw_करोorbell(card, tcode, data, agent);
	पूर्ण अन्यथा अगर (offset == 0x14 && length == 4) अणु
		/* UNSOLICITED_STATUS_ENABLE */
		rcode = tgt_agent_rw_unsolicited_status_enable(card, tcode,
				data, agent);
	पूर्ण अन्यथा अणु
		rcode = RCODE_ADDRESS_ERROR;
	पूर्ण

out:
	fw_send_response(card, request, rcode);
पूर्ण

अटल व्योम sbp_handle_command(काष्ठा sbp_target_request *);
अटल पूर्णांक sbp_send_status(काष्ठा sbp_target_request *);
अटल व्योम sbp_मुक्त_request(काष्ठा sbp_target_request *);

अटल व्योम tgt_agent_process_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbp_target_request *req =
		container_of(work, काष्ठा sbp_target_request, work);

	pr_debug("tgt_orb ptr:0x%llx next_ORB:0x%llx data_descriptor:0x%llx misc:0x%x\n",
			req->orb_poपूर्णांकer,
			sbp2_poपूर्णांकer_to_addr(&req->orb.next_orb),
			sbp2_poपूर्णांकer_to_addr(&req->orb.data_descriptor),
			be32_to_cpu(req->orb.misc));

	अगर (req->orb_poपूर्णांकer >> 32)
		pr_debug("ORB with high bits set\n");

	चयन (ORB_REQUEST_FORMAT(be32_to_cpu(req->orb.misc))) अणु
		हाल 0:/* Format specअगरied by this standard */
			sbp_handle_command(req);
			वापस;
		हाल 1: /* Reserved क्रम future standardization */
		हाल 2: /* Venकरोr-dependent */
			req->status.status |= cpu_to_be32(
					STATUS_BLOCK_RESP(
						STATUS_RESP_REQUEST_COMPLETE) |
					STATUS_BLOCK_DEAD(0) |
					STATUS_BLOCK_LEN(1) |
					STATUS_BLOCK_SBP_STATUS(
						SBP_STATUS_REQ_TYPE_NOTSUPP));
			sbp_send_status(req);
			वापस;
		हाल 3: /* Dummy ORB */
			req->status.status |= cpu_to_be32(
					STATUS_BLOCK_RESP(
						STATUS_RESP_REQUEST_COMPLETE) |
					STATUS_BLOCK_DEAD(0) |
					STATUS_BLOCK_LEN(1) |
					STATUS_BLOCK_SBP_STATUS(
						SBP_STATUS_DUMMY_ORB_COMPLETE));
			sbp_send_status(req);
			वापस;
		शेष:
			BUG();
	पूर्ण
पूर्ण

/* used to द्विगुन-check we haven't been issued an AGENT_RESET */
अटल अंतरभूत bool tgt_agent_check_active(काष्ठा sbp_target_agent *agent)
अणु
	bool active;

	spin_lock_bh(&agent->lock);
	active = (agent->state == AGENT_STATE_ACTIVE);
	spin_unlock_bh(&agent->lock);

	वापस active;
पूर्ण

अटल काष्ठा sbp_target_request *sbp_mgt_get_req(काष्ठा sbp_session *sess,
	काष्ठा fw_card *card, u64 next_orb)
अणु
	काष्ठा se_session *se_sess = sess->se_sess;
	काष्ठा sbp_target_request *req;
	पूर्णांक tag, cpu;

	tag = sbiपंचांगap_queue_get(&se_sess->sess_tag_pool, &cpu);
	अगर (tag < 0)
		वापस ERR_PTR(-ENOMEM);

	req = &((काष्ठा sbp_target_request *)se_sess->sess_cmd_map)[tag];
	स_रखो(req, 0, माप(*req));
	req->se_cmd.map_tag = tag;
	req->se_cmd.map_cpu = cpu;
	req->se_cmd.tag = next_orb;

	वापस req;
पूर्ण

अटल व्योम tgt_agent_fetch_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbp_target_agent *agent =
		container_of(work, काष्ठा sbp_target_agent, work);
	काष्ठा sbp_session *sess = agent->login->sess;
	काष्ठा sbp_target_request *req;
	पूर्णांक ret;
	bool करोorbell = agent->करोorbell;
	u64 next_orb = agent->orb_poपूर्णांकer;

	जबतक (next_orb && tgt_agent_check_active(agent)) अणु
		req = sbp_mgt_get_req(sess, sess->card, next_orb);
		अगर (IS_ERR(req)) अणु
			spin_lock_bh(&agent->lock);
			agent->state = AGENT_STATE_DEAD;
			spin_unlock_bh(&agent->lock);
			वापस;
		पूर्ण

		req->login = agent->login;
		req->orb_poपूर्णांकer = next_orb;

		req->status.status = cpu_to_be32(STATUS_BLOCK_ORB_OFFSET_HIGH(
					req->orb_poपूर्णांकer >> 32));
		req->status.orb_low = cpu_to_be32(
				req->orb_poपूर्णांकer & 0xfffffffc);

		/* पढ़ो in the ORB */
		ret = sbp_run_transaction(sess->card, TCODE_READ_BLOCK_REQUEST,
				sess->node_id, sess->generation, sess->speed,
				req->orb_poपूर्णांकer, &req->orb, माप(req->orb));
		अगर (ret != RCODE_COMPLETE) अणु
			pr_debug("tgt_orb fetch failed: %x\n", ret);
			req->status.status |= cpu_to_be32(
					STATUS_BLOCK_SRC(
						STATUS_SRC_ORB_FINISHED) |
					STATUS_BLOCK_RESP(
						STATUS_RESP_TRANSPORT_FAILURE) |
					STATUS_BLOCK_DEAD(1) |
					STATUS_BLOCK_LEN(1) |
					STATUS_BLOCK_SBP_STATUS(
						SBP_STATUS_UNSPECIFIED_ERROR));
			spin_lock_bh(&agent->lock);
			agent->state = AGENT_STATE_DEAD;
			spin_unlock_bh(&agent->lock);

			sbp_send_status(req);
			वापस;
		पूर्ण

		/* check the next_ORB field */
		अगर (be32_to_cpu(req->orb.next_orb.high) & 0x80000000) अणु
			next_orb = 0;
			req->status.status |= cpu_to_be32(STATUS_BLOCK_SRC(
						STATUS_SRC_ORB_FINISHED));
		पूर्ण अन्यथा अणु
			next_orb = sbp2_poपूर्णांकer_to_addr(&req->orb.next_orb);
			req->status.status |= cpu_to_be32(STATUS_BLOCK_SRC(
						STATUS_SRC_ORB_CONTINUING));
		पूर्ण

		अगर (tgt_agent_check_active(agent) && !करोorbell) अणु
			INIT_WORK(&req->work, tgt_agent_process_work);
			queue_work(प्रणाली_unbound_wq, &req->work);
		पूर्ण अन्यथा अणु
			/* करोn't process this request, just check next_ORB */
			sbp_मुक्त_request(req);
		पूर्ण

		spin_lock_bh(&agent->lock);
		करोorbell = agent->करोorbell = false;

		/* check अगर we should carry on processing */
		अगर (next_orb)
			agent->orb_poपूर्णांकer = next_orb;
		अन्यथा
			agent->state = AGENT_STATE_SUSPENDED;

		spin_unlock_bh(&agent->lock);
	पूर्ण
पूर्ण

अटल काष्ठा sbp_target_agent *sbp_target_agent_रेजिस्टर(
		काष्ठा sbp_login_descriptor *login)
अणु
	काष्ठा sbp_target_agent *agent;
	पूर्णांक ret;

	agent = kदो_स्मृति(माप(*agent), GFP_KERNEL);
	अगर (!agent)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&agent->lock);

	agent->handler.length = 0x20;
	agent->handler.address_callback = tgt_agent_rw;
	agent->handler.callback_data = agent;

	agent->login = login;
	agent->state = AGENT_STATE_RESET;
	INIT_WORK(&agent->work, tgt_agent_fetch_work);
	agent->orb_poपूर्णांकer = 0;
	agent->करोorbell = false;

	ret = fw_core_add_address_handler(&agent->handler,
			&sbp_रेजिस्टर_region);
	अगर (ret < 0) अणु
		kमुक्त(agent);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस agent;
पूर्ण

अटल व्योम sbp_target_agent_unरेजिस्टर(काष्ठा sbp_target_agent *agent)
अणु
	fw_core_हटाओ_address_handler(&agent->handler);
	cancel_work_sync(&agent->work);
	kमुक्त(agent);
पूर्ण

/*
 * Simple wrapper around fw_run_transaction that retries the transaction several
 * बार in हाल of failure, with an exponential backoff.
 */
अटल पूर्णांक sbp_run_transaction(काष्ठा fw_card *card, पूर्णांक tcode, पूर्णांक destination_id,
		पूर्णांक generation, पूर्णांक speed, अचिन्हित दीर्घ दीर्घ offset,
		व्योम *payload, माप_प्रकार length)
अणु
	पूर्णांक attempt, ret, delay;

	क्रम (attempt = 1; attempt <= 5; attempt++) अणु
		ret = fw_run_transaction(card, tcode, destination_id,
				generation, speed, offset, payload, length);

		चयन (ret) अणु
		हाल RCODE_COMPLETE:
		हाल RCODE_TYPE_ERROR:
		हाल RCODE_ADDRESS_ERROR:
		हाल RCODE_GENERATION:
			वापस ret;

		शेष:
			delay = 5 * attempt * attempt;
			usleep_range(delay, delay * 2);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Wrapper around sbp_run_transaction that माला_लो the card, destination,
 * generation and speed out of the request's session.
 */
अटल पूर्णांक sbp_run_request_transaction(काष्ठा sbp_target_request *req,
		पूर्णांक tcode, अचिन्हित दीर्घ दीर्घ offset, व्योम *payload,
		माप_प्रकार length)
अणु
	काष्ठा sbp_login_descriptor *login = req->login;
	काष्ठा sbp_session *sess = login->sess;
	काष्ठा fw_card *card;
	पूर्णांक node_id, generation, speed, ret;

	spin_lock_bh(&sess->lock);
	card = fw_card_get(sess->card);
	node_id = sess->node_id;
	generation = sess->generation;
	speed = sess->speed;
	spin_unlock_bh(&sess->lock);

	ret = sbp_run_transaction(card, tcode, node_id, generation, speed,
			offset, payload, length);

	fw_card_put(card);

	वापस ret;
पूर्ण

अटल पूर्णांक sbp_fetch_command(काष्ठा sbp_target_request *req)
अणु
	पूर्णांक ret, cmd_len, copy_len;

	cmd_len = scsi_command_size(req->orb.command_block);

	req->cmd_buf = kदो_स्मृति(cmd_len, GFP_KERNEL);
	अगर (!req->cmd_buf)
		वापस -ENOMEM;

	स_नकल(req->cmd_buf, req->orb.command_block,
		min_t(पूर्णांक, cmd_len, माप(req->orb.command_block)));

	अगर (cmd_len > माप(req->orb.command_block)) अणु
		pr_debug("sbp_fetch_command: filling in long command\n");
		copy_len = cmd_len - माप(req->orb.command_block);

		ret = sbp_run_request_transaction(req,
				TCODE_READ_BLOCK_REQUEST,
				req->orb_poपूर्णांकer + माप(req->orb),
				req->cmd_buf + माप(req->orb.command_block),
				copy_len);
		अगर (ret != RCODE_COMPLETE)
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbp_fetch_page_table(काष्ठा sbp_target_request *req)
अणु
	पूर्णांक pg_tbl_sz, ret;
	काष्ठा sbp_page_table_entry *pg_tbl;

	अगर (!CMDBLK_ORB_PG_TBL_PRESENT(be32_to_cpu(req->orb.misc)))
		वापस 0;

	pg_tbl_sz = CMDBLK_ORB_DATA_SIZE(be32_to_cpu(req->orb.misc)) *
		माप(काष्ठा sbp_page_table_entry);

	pg_tbl = kदो_स्मृति(pg_tbl_sz, GFP_KERNEL);
	अगर (!pg_tbl)
		वापस -ENOMEM;

	ret = sbp_run_request_transaction(req, TCODE_READ_BLOCK_REQUEST,
			sbp2_poपूर्णांकer_to_addr(&req->orb.data_descriptor),
			pg_tbl, pg_tbl_sz);
	अगर (ret != RCODE_COMPLETE) अणु
		kमुक्त(pg_tbl);
		वापस -EIO;
	पूर्ण

	req->pg_tbl = pg_tbl;
	वापस 0;
पूर्ण

अटल व्योम sbp_calc_data_length_direction(काष्ठा sbp_target_request *req,
	u32 *data_len, क्रमागत dma_data_direction *data_dir)
अणु
	पूर्णांक data_size, direction, idx;

	data_size = CMDBLK_ORB_DATA_SIZE(be32_to_cpu(req->orb.misc));
	direction = CMDBLK_ORB_सूचीECTION(be32_to_cpu(req->orb.misc));

	अगर (!data_size) अणु
		*data_len = 0;
		*data_dir = DMA_NONE;
		वापस;
	पूर्ण

	*data_dir = direction ? DMA_FROM_DEVICE : DMA_TO_DEVICE;

	अगर (req->pg_tbl) अणु
		*data_len = 0;
		क्रम (idx = 0; idx < data_size; idx++) अणु
			*data_len += be16_to_cpu(
					req->pg_tbl[idx].segment_length);
		पूर्ण
	पूर्ण अन्यथा अणु
		*data_len = data_size;
	पूर्ण
पूर्ण

अटल व्योम sbp_handle_command(काष्ठा sbp_target_request *req)
अणु
	काष्ठा sbp_login_descriptor *login = req->login;
	काष्ठा sbp_session *sess = login->sess;
	पूर्णांक ret, unpacked_lun;
	u32 data_length;
	क्रमागत dma_data_direction data_dir;

	ret = sbp_fetch_command(req);
	अगर (ret) अणु
		pr_debug("sbp_handle_command: fetch command failed: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = sbp_fetch_page_table(req);
	अगर (ret) अणु
		pr_debug("sbp_handle_command: fetch page table failed: %d\n",
			ret);
		जाओ err;
	पूर्ण

	unpacked_lun = req->login->login_lun;
	sbp_calc_data_length_direction(req, &data_length, &data_dir);

	pr_debug("sbp_handle_command ORB:0x%llx unpacked_lun:%d data_len:%d data_dir:%d\n",
			req->orb_poपूर्णांकer, unpacked_lun, data_length, data_dir);

	/* only used क्रम prपूर्णांकk until we करो TMRs */
	req->se_cmd.tag = req->orb_poपूर्णांकer;
	target_submit_cmd(&req->se_cmd, sess->se_sess, req->cmd_buf,
			  req->sense_buf, unpacked_lun, data_length,
			  TCM_SIMPLE_TAG, data_dir, TARGET_SCF_ACK_KREF);
	वापस;

err:
	req->status.status |= cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_TRANSPORT_FAILURE) |
		STATUS_BLOCK_DEAD(0) |
		STATUS_BLOCK_LEN(1) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_UNSPECIFIED_ERROR));
	sbp_send_status(req);
पूर्ण

/*
 * DMA_TO_DEVICE = पढ़ो from initiator (SCSI WRITE)
 * DMA_FROM_DEVICE = ग_लिखो to initiator (SCSI READ)
 */
अटल पूर्णांक sbp_rw_data(काष्ठा sbp_target_request *req)
अणु
	काष्ठा sbp_session *sess = req->login->sess;
	पूर्णांक tcode, sg_miter_flags, max_payload, pg_size, speed, node_id,
		generation, num_pte, length, tfr_length,
		rcode = RCODE_COMPLETE;
	काष्ठा sbp_page_table_entry *pte;
	अचिन्हित दीर्घ दीर्घ offset;
	काष्ठा fw_card *card;
	काष्ठा sg_mapping_iter iter;

	अगर (req->se_cmd.data_direction == DMA_FROM_DEVICE) अणु
		tcode = TCODE_WRITE_BLOCK_REQUEST;
		sg_miter_flags = SG_MITER_FROM_SG;
	पूर्ण अन्यथा अणु
		tcode = TCODE_READ_BLOCK_REQUEST;
		sg_miter_flags = SG_MITER_TO_SG;
	पूर्ण

	max_payload = 4 << CMDBLK_ORB_MAX_PAYLOAD(be32_to_cpu(req->orb.misc));
	speed = CMDBLK_ORB_SPEED(be32_to_cpu(req->orb.misc));

	pg_size = CMDBLK_ORB_PG_SIZE(be32_to_cpu(req->orb.misc));
	अगर (pg_size) अणु
		pr_err("sbp_run_transaction: page size ignored\n");
		pg_size = 0x100 << pg_size;
	पूर्ण

	spin_lock_bh(&sess->lock);
	card = fw_card_get(sess->card);
	node_id = sess->node_id;
	generation = sess->generation;
	spin_unlock_bh(&sess->lock);

	अगर (req->pg_tbl) अणु
		pte = req->pg_tbl;
		num_pte = CMDBLK_ORB_DATA_SIZE(be32_to_cpu(req->orb.misc));

		offset = 0;
		length = 0;
	पूर्ण अन्यथा अणु
		pte = शून्य;
		num_pte = 0;

		offset = sbp2_poपूर्णांकer_to_addr(&req->orb.data_descriptor);
		length = req->se_cmd.data_length;
	पूर्ण

	sg_miter_start(&iter, req->se_cmd.t_data_sg, req->se_cmd.t_data_nents,
		sg_miter_flags);

	जबतक (length || num_pte) अणु
		अगर (!length) अणु
			offset = (u64)be16_to_cpu(pte->segment_base_hi) << 32 |
				be32_to_cpu(pte->segment_base_lo);
			length = be16_to_cpu(pte->segment_length);

			pte++;
			num_pte--;
		पूर्ण

		sg_miter_next(&iter);

		tfr_length = min3(length, max_payload, (पूर्णांक)iter.length);

		/* FIXME: take page_size पूर्णांकo account */

		rcode = sbp_run_transaction(card, tcode, node_id,
				generation, speed,
				offset, iter.addr, tfr_length);

		अगर (rcode != RCODE_COMPLETE)
			अवरोध;

		length -= tfr_length;
		offset += tfr_length;
		iter.consumed = tfr_length;
	पूर्ण

	sg_miter_stop(&iter);
	fw_card_put(card);

	अगर (rcode == RCODE_COMPLETE) अणु
		WARN_ON(length != 0);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक sbp_send_status(काष्ठा sbp_target_request *req)
अणु
	पूर्णांक rc, ret = 0, length;
	काष्ठा sbp_login_descriptor *login = req->login;

	length = (((be32_to_cpu(req->status.status) >> 24) & 0x07) + 1) * 4;

	rc = sbp_run_request_transaction(req, TCODE_WRITE_BLOCK_REQUEST,
			login->status_fअगरo_addr, &req->status, length);
	अगर (rc != RCODE_COMPLETE) अणु
		pr_debug("sbp_send_status: write failed: 0x%x\n", rc);
		ret = -EIO;
		जाओ put_ref;
	पूर्ण

	pr_debug("sbp_send_status: status write complete for ORB: 0x%llx\n",
			req->orb_poपूर्णांकer);
	/*
	 * Drop the extra ACK_KREF reference taken by target_submit_cmd()
	 * ahead of sbp_check_stop_मुक्त() -> transport_generic_मुक्त_cmd()
	 * final se_cmd->cmd_kref put.
	 */
put_ref:
	target_put_sess_cmd(&req->se_cmd);
	वापस ret;
पूर्ण

अटल व्योम sbp_sense_mangle(काष्ठा sbp_target_request *req)
अणु
	काष्ठा se_cmd *se_cmd = &req->se_cmd;
	u8 *sense = req->sense_buf;
	u8 *status = req->status.data;

	WARN_ON(se_cmd->scsi_sense_length < 18);

	चयन (sense[0] & 0x7f) अणु 		/* sfmt */
	हाल 0x70: /* current, fixed */
		status[0] = 0 << 6;
		अवरोध;
	हाल 0x71: /* deferred, fixed */
		status[0] = 1 << 6;
		अवरोध;
	हाल 0x72: /* current, descriptor */
	हाल 0x73: /* deferred, descriptor */
	शेष:
		/*
		 * TODO: SBP-3 specअगरies what we should करो with descriptor
		 * क्रमmat sense data
		 */
		pr_err("sbp_send_sense: unknown sense format: 0x%x\n",
			sense[0]);
		req->status.status |= cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_DEAD(0) |
			STATUS_BLOCK_LEN(1) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQUEST_ABORTED));
		वापस;
	पूर्ण

	status[0] |= se_cmd->scsi_status & 0x3f;/* status */
	status[1] =
		(sense[0] & 0x80) |		/* valid */
		((sense[2] & 0xe0) >> 1) |	/* mark, eom, ili */
		(sense[2] & 0x0f);		/* sense_key */
	status[2] = se_cmd->scsi_asc;		/* sense_code */
	status[3] = se_cmd->scsi_ascq;		/* sense_qualअगरier */

	/* inक्रमmation */
	status[4] = sense[3];
	status[5] = sense[4];
	status[6] = sense[5];
	status[7] = sense[6];

	/* CDB-dependent */
	status[8] = sense[8];
	status[9] = sense[9];
	status[10] = sense[10];
	status[11] = sense[11];

	/* fru */
	status[12] = sense[14];

	/* sense_key-dependent */
	status[13] = sense[15];
	status[14] = sense[16];
	status[15] = sense[17];

	req->status.status |= cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_DEAD(0) |
		STATUS_BLOCK_LEN(5) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
पूर्ण

अटल पूर्णांक sbp_send_sense(काष्ठा sbp_target_request *req)
अणु
	काष्ठा se_cmd *se_cmd = &req->se_cmd;

	अगर (se_cmd->scsi_sense_length) अणु
		sbp_sense_mangle(req);
	पूर्ण अन्यथा अणु
		req->status.status |= cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_DEAD(0) |
			STATUS_BLOCK_LEN(1) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
	पूर्ण

	वापस sbp_send_status(req);
पूर्ण

अटल व्योम sbp_मुक्त_request(काष्ठा sbp_target_request *req)
अणु
	काष्ठा se_cmd *se_cmd = &req->se_cmd;
	काष्ठा se_session *se_sess = se_cmd->se_sess;

	kमुक्त(req->pg_tbl);
	kमुक्त(req->cmd_buf);

	target_मुक्त_tag(se_sess, se_cmd);
पूर्ण

अटल व्योम sbp_mgt_agent_process(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbp_management_agent *agent =
		container_of(work, काष्ठा sbp_management_agent, work);
	काष्ठा sbp_management_request *req = agent->request;
	पूर्णांक ret;
	पूर्णांक status_data_len = 0;

	/* fetch the ORB from the initiator */
	ret = sbp_run_transaction(req->card, TCODE_READ_BLOCK_REQUEST,
		req->node_addr, req->generation, req->speed,
		agent->orb_offset, &req->orb, माप(req->orb));
	अगर (ret != RCODE_COMPLETE) अणु
		pr_debug("mgt_orb fetch failed: %x\n", ret);
		जाओ out;
	पूर्ण

	pr_debug("mgt_orb ptr1:0x%llx ptr2:0x%llx misc:0x%x len:0x%x status_fifo:0x%llx\n",
		sbp2_poपूर्णांकer_to_addr(&req->orb.ptr1),
		sbp2_poपूर्णांकer_to_addr(&req->orb.ptr2),
		be32_to_cpu(req->orb.misc), be32_to_cpu(req->orb.length),
		sbp2_poपूर्णांकer_to_addr(&req->orb.status_fअगरo));

	अगर (!ORB_NOTIFY(be32_to_cpu(req->orb.misc)) ||
		ORB_REQUEST_FORMAT(be32_to_cpu(req->orb.misc)) != 0) अणु
		pr_err("mgt_orb bad request\n");
		जाओ out;
	पूर्ण

	चयन (MANAGEMENT_ORB_FUNCTION(be32_to_cpu(req->orb.misc))) अणु
	हाल MANAGEMENT_ORB_FUNCTION_LOGIN:
		sbp_management_request_login(agent, req, &status_data_len);
		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_QUERY_LOGINS:
		sbp_management_request_query_logins(agent, req,
				&status_data_len);
		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_RECONNECT:
		sbp_management_request_reconnect(agent, req, &status_data_len);
		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_SET_PASSWORD:
		pr_notice("SET PASSWORD not implemented\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));

		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_LOGOUT:
		sbp_management_request_logout(agent, req, &status_data_len);
		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_ABORT_TASK:
		pr_notice("ABORT TASK not implemented\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));

		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_ABORT_TASK_SET:
		pr_notice("ABORT TASK SET not implemented\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));

		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_LOGICAL_UNIT_RESET:
		pr_notice("LOGICAL UNIT RESET not implemented\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));

		अवरोध;

	हाल MANAGEMENT_ORB_FUNCTION_TARGET_RESET:
		pr_notice("TARGET RESET not implemented\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));

		अवरोध;

	शेष:
		pr_notice("unknown management function 0x%x\n",
			MANAGEMENT_ORB_FUNCTION(be32_to_cpu(req->orb.misc)));

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_REQ_TYPE_NOTSUPP));

		अवरोध;
	पूर्ण

	req->status.status |= cpu_to_be32(
		STATUS_BLOCK_SRC(1) | /* Response to ORB, next_ORB असलent */
		STATUS_BLOCK_LEN(DIV_ROUND_UP(status_data_len, 4) + 1) |
		STATUS_BLOCK_ORB_OFFSET_HIGH(agent->orb_offset >> 32));
	req->status.orb_low = cpu_to_be32(agent->orb_offset);

	/* ग_लिखो the status block back to the initiator */
	ret = sbp_run_transaction(req->card, TCODE_WRITE_BLOCK_REQUEST,
		req->node_addr, req->generation, req->speed,
		sbp2_poपूर्णांकer_to_addr(&req->orb.status_fअगरo),
		&req->status, 8 + status_data_len);
	अगर (ret != RCODE_COMPLETE) अणु
		pr_debug("mgt_orb status write failed: %x\n", ret);
		जाओ out;
	पूर्ण

out:
	fw_card_put(req->card);
	kमुक्त(req);

	spin_lock_bh(&agent->lock);
	agent->state = MANAGEMENT_AGENT_STATE_IDLE;
	spin_unlock_bh(&agent->lock);
पूर्ण

अटल व्योम sbp_mgt_agent_rw(काष्ठा fw_card *card,
	काष्ठा fw_request *request, पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
	पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset, व्योम *data, माप_प्रकार length,
	व्योम *callback_data)
अणु
	काष्ठा sbp_management_agent *agent = callback_data;
	काष्ठा sbp2_poपूर्णांकer *ptr = data;
	पूर्णांक rcode = RCODE_ADDRESS_ERROR;

	अगर (!agent->tport->enable)
		जाओ out;

	अगर ((offset != agent->handler.offset) || (length != 8))
		जाओ out;

	अगर (tcode == TCODE_WRITE_BLOCK_REQUEST) अणु
		काष्ठा sbp_management_request *req;
		पूर्णांक prev_state;

		spin_lock_bh(&agent->lock);
		prev_state = agent->state;
		agent->state = MANAGEMENT_AGENT_STATE_BUSY;
		spin_unlock_bh(&agent->lock);

		अगर (prev_state == MANAGEMENT_AGENT_STATE_BUSY) अणु
			pr_notice("ignoring management request while busy\n");
			rcode = RCODE_CONFLICT_ERROR;
			जाओ out;
		पूर्ण
		req = kzalloc(माप(*req), GFP_ATOMIC);
		अगर (!req) अणु
			rcode = RCODE_CONFLICT_ERROR;
			जाओ out;
		पूर्ण

		req->card = fw_card_get(card);
		req->generation = generation;
		req->node_addr = source;
		req->speed = fw_get_request_speed(request);

		agent->orb_offset = sbp2_poपूर्णांकer_to_addr(ptr);
		agent->request = req;

		queue_work(प्रणाली_unbound_wq, &agent->work);
		rcode = RCODE_COMPLETE;
	पूर्ण अन्यथा अगर (tcode == TCODE_READ_BLOCK_REQUEST) अणु
		addr_to_sbp2_poपूर्णांकer(agent->orb_offset, ptr);
		rcode = RCODE_COMPLETE;
	पूर्ण अन्यथा अणु
		rcode = RCODE_TYPE_ERROR;
	पूर्ण

out:
	fw_send_response(card, request, rcode);
पूर्ण

अटल काष्ठा sbp_management_agent *sbp_management_agent_रेजिस्टर(
		काष्ठा sbp_tport *tport)
अणु
	पूर्णांक ret;
	काष्ठा sbp_management_agent *agent;

	agent = kदो_स्मृति(माप(*agent), GFP_KERNEL);
	अगर (!agent)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&agent->lock);
	agent->tport = tport;
	agent->handler.length = 0x08;
	agent->handler.address_callback = sbp_mgt_agent_rw;
	agent->handler.callback_data = agent;
	agent->state = MANAGEMENT_AGENT_STATE_IDLE;
	INIT_WORK(&agent->work, sbp_mgt_agent_process);
	agent->orb_offset = 0;
	agent->request = शून्य;

	ret = fw_core_add_address_handler(&agent->handler,
			&sbp_रेजिस्टर_region);
	अगर (ret < 0) अणु
		kमुक्त(agent);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस agent;
पूर्ण

अटल व्योम sbp_management_agent_unरेजिस्टर(काष्ठा sbp_management_agent *agent)
अणु
	fw_core_हटाओ_address_handler(&agent->handler);
	cancel_work_sync(&agent->work);
	kमुक्त(agent);
पूर्ण

अटल पूर्णांक sbp_check_true(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक sbp_check_false(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

अटल अक्षर *sbp_get_fabric_wwn(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;

	वापस &tport->tport_name[0];
पूर्ण

अटल u16 sbp_get_tag(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	वापस tpg->tport_tpgt;
पूर्ण

अटल u32 sbp_tpg_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल व्योम sbp_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा sbp_target_request *req = container_of(se_cmd,
			काष्ठा sbp_target_request, se_cmd);

	sbp_मुक्त_request(req);
पूर्ण

अटल u32 sbp_sess_get_index(काष्ठा se_session *se_sess)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sbp_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा sbp_target_request *req = container_of(se_cmd,
			काष्ठा sbp_target_request, se_cmd);
	पूर्णांक ret;

	ret = sbp_rw_data(req);
	अगर (ret) अणु
		req->status.status |= cpu_to_be32(
			STATUS_BLOCK_RESP(
				STATUS_RESP_TRANSPORT_FAILURE) |
			STATUS_BLOCK_DEAD(0) |
			STATUS_BLOCK_LEN(1) |
			STATUS_BLOCK_SBP_STATUS(
				SBP_STATUS_UNSPECIFIED_ERROR));
		sbp_send_status(req);
		वापस ret;
	पूर्ण

	target_execute_cmd(se_cmd);
	वापस 0;
पूर्ण

अटल व्योम sbp_set_शेष_node_attrs(काष्ठा se_node_acl *nacl)
अणु
	वापस;
पूर्ण

अटल पूर्णांक sbp_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sbp_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा sbp_target_request *req = container_of(se_cmd,
			काष्ठा sbp_target_request, se_cmd);
	पूर्णांक ret;

	ret = sbp_rw_data(req);
	अगर (ret) अणु
		req->status.status |= cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_TRANSPORT_FAILURE) |
			STATUS_BLOCK_DEAD(0) |
			STATUS_BLOCK_LEN(1) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_UNSPECIFIED_ERROR));
		sbp_send_status(req);
		वापस ret;
	पूर्ण

	वापस sbp_send_sense(req);
पूर्ण

/*
 * Called after command (no data transfer) or after the ग_लिखो (to device)
 * operation is completed
 */
अटल पूर्णांक sbp_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा sbp_target_request *req = container_of(se_cmd,
			काष्ठा sbp_target_request, se_cmd);

	वापस sbp_send_sense(req);
पूर्ण

अटल व्योम sbp_queue_पंचांग_rsp(काष्ठा se_cmd *se_cmd)
अणु
पूर्ण

अटल व्योम sbp_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
	वापस;
पूर्ण

अटल पूर्णांक sbp_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा sbp_target_request *req = container_of(se_cmd,
			काष्ठा sbp_target_request, se_cmd);

	वापस transport_generic_मुक्त_cmd(&req->se_cmd, 0);
पूर्ण

अटल पूर्णांक sbp_count_se_tpg_luns(काष्ठा se_portal_group *tpg)
अणु
	काष्ठा se_lun *lun;
	पूर्णांक count = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(lun, &tpg->tpg_lun_hlist, link)
		count++;
	rcu_पढ़ो_unlock();

	वापस count;
पूर्ण

अटल पूर्णांक sbp_update_unit_directory(काष्ठा sbp_tport *tport)
अणु
	काष्ठा se_lun *lun;
	पूर्णांक num_luns, num_entries, idx = 0, mgt_agt_addr, ret;
	u32 *data;

	अगर (tport->unit_directory.data) अणु
		fw_core_हटाओ_descriptor(&tport->unit_directory);
		kमुक्त(tport->unit_directory.data);
		tport->unit_directory.data = शून्य;
	पूर्ण

	अगर (!tport->enable || !tport->tpg)
		वापस 0;

	num_luns = sbp_count_se_tpg_luns(&tport->tpg->se_tpg);

	/*
	 * Number of entries in the final unit directory:
	 *  - all of those in the ढाँचा
	 *  - management_agent
	 *  - unit_अक्षरacteristics
	 *  - reconnect_समयout
	 *  - unit unique ID
	 *  - one क्रम each LUN
	 *
	 *  MUST NOT include leaf or sub-directory entries
	 */
	num_entries = ARRAY_SIZE(sbp_unit_directory_ढाँचा) + 4 + num_luns;

	अगर (tport->directory_id != -1)
		num_entries++;

	/* allocate num_entries + 4 क्रम the header and unique ID leaf */
	data = kसुस्मृति((num_entries + 4), माप(u32), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* directory_length */
	data[idx++] = num_entries << 16;

	/* directory_id */
	अगर (tport->directory_id != -1)
		data[idx++] = (CSR_सूचीECTORY_ID << 24) | tport->directory_id;

	/* unit directory ढाँचा */
	स_नकल(&data[idx], sbp_unit_directory_ढाँचा,
			माप(sbp_unit_directory_ढाँचा));
	idx += ARRAY_SIZE(sbp_unit_directory_ढाँचा);

	/* management_agent */
	mgt_agt_addr = (tport->mgt_agt->handler.offset - CSR_REGISTER_BASE) / 4;
	data[idx++] = 0x54000000 | (mgt_agt_addr & 0x00ffffff);

	/* unit_अक्षरacteristics */
	data[idx++] = 0x3a000000 |
		(((tport->mgt_orb_समयout * 2) << 8) & 0xff00) |
		SBP_ORB_FETCH_SIZE;

	/* reconnect_समयout */
	data[idx++] = 0x3d000000 | (tport->max_reconnect_समयout & 0xffff);

	/* unit unique ID (leaf is just after LUNs) */
	data[idx++] = 0x8d000000 | (num_luns + 1);

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(lun, &tport->tpg->se_tpg.tpg_lun_hlist, link) अणु
		काष्ठा se_device *dev;
		पूर्णांक type;
		/*
		 * rcu_dereference_raw रक्षित by se_lun->lun_group symlink
		 * reference to se_device->dev_group.
		 */
		dev = rcu_dereference_raw(lun->lun_se_dev);
		type = dev->transport->get_device_type(dev);

		/* logical_unit_number */
		data[idx++] = 0x14000000 |
			((type << 16) & 0x1f0000) |
			(lun->unpacked_lun & 0xffff);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* unit unique ID leaf */
	data[idx++] = 2 << 16;
	data[idx++] = tport->guid >> 32;
	data[idx++] = tport->guid;

	tport->unit_directory.length = idx;
	tport->unit_directory.key = (CSR_सूचीECTORY | CSR_UNIT) << 24;
	tport->unit_directory.data = data;

	ret = fw_core_add_descriptor(&tport->unit_directory);
	अगर (ret < 0) अणु
		kमुक्त(tport->unit_directory.data);
		tport->unit_directory.data = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार sbp_parse_wwn(स्थिर अक्षर *name, u64 *wwn)
अणु
	स्थिर अक्षर *cp;
	अक्षर c, nibble;
	पूर्णांक pos = 0, err;

	*wwn = 0;
	क्रम (cp = name; cp < &name[SBP_NAMELEN - 1]; cp++) अणु
		c = *cp;
		अगर (c == '\n' && cp[1] == '\0')
			जारी;
		अगर (c == '\0') अणु
			err = 2;
			अगर (pos != 16)
				जाओ fail;
			वापस cp - name;
		पूर्ण
		err = 3;
		अगर (है_अंक(c))
			nibble = c - '0';
		अन्यथा अगर (है_षष्ठादशक(c))
			nibble = छोटे(c) - 'a' + 10;
		अन्यथा
			जाओ fail;
		*wwn = (*wwn << 4) | nibble;
		pos++;
	पूर्ण
	err = 4;
fail:
	prपूर्णांकk(KERN_INFO "err %u len %zu pos %u\n",
			err, cp - name, pos);
	वापस -1;
पूर्ण

अटल sमाप_प्रकार sbp_क्रमmat_wwn(अक्षर *buf, माप_प्रकार len, u64 wwn)
अणु
	वापस snम_लिखो(buf, len, "%016llx", wwn);
पूर्ण

अटल पूर्णांक sbp_init_nodeacl(काष्ठा se_node_acl *se_nacl, स्थिर अक्षर *name)
अणु
	u64 guid = 0;

	अगर (sbp_parse_wwn(name, &guid) < 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक sbp_post_link_lun(
		काष्ठा se_portal_group *se_tpg,
		काष्ठा se_lun *se_lun)
अणु
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);

	वापस sbp_update_unit_directory(tpg->tport);
पूर्ण

अटल व्योम sbp_pre_unlink_lun(
		काष्ठा se_portal_group *se_tpg,
		काष्ठा se_lun *se_lun)
अणु
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	पूर्णांक ret;

	अगर (sbp_count_se_tpg_luns(&tpg->se_tpg) == 0)
		tport->enable = 0;

	ret = sbp_update_unit_directory(tport);
	अगर (ret < 0)
		pr_err("unlink LUN: failed to update unit directory\n");
पूर्ण

अटल काष्ठा se_portal_group *sbp_make_tpg(काष्ठा se_wwn *wwn,
					    स्थिर अक्षर *name)
अणु
	काष्ठा sbp_tport *tport =
		container_of(wwn, काष्ठा sbp_tport, tport_wwn);

	काष्ठा sbp_tpg *tpg;
	अचिन्हित दीर्घ tpgt;
	पूर्णांक ret;

	अगर (म_माला(name, "tpgt_") != name)
		वापस ERR_PTR(-EINVAL);
	अगर (kम_से_अदीर्घ(name + 5, 10, &tpgt) || tpgt > अच_पूर्णांक_उच्च)
		वापस ERR_PTR(-EINVAL);

	अगर (tport->tpg) अणु
		pr_err("Only one TPG per Unit is possible.\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	tpg = kzalloc(माप(*tpg), GFP_KERNEL);
	अगर (!tpg)
		वापस ERR_PTR(-ENOMEM);

	tpg->tport = tport;
	tpg->tport_tpgt = tpgt;
	tport->tpg = tpg;

	/* शेष attribute values */
	tport->enable = 0;
	tport->directory_id = -1;
	tport->mgt_orb_समयout = 15;
	tport->max_reconnect_समयout = 5;
	tport->max_logins_per_lun = 1;

	tport->mgt_agt = sbp_management_agent_रेजिस्टर(tport);
	अगर (IS_ERR(tport->mgt_agt)) अणु
		ret = PTR_ERR(tport->mgt_agt);
		जाओ out_मुक्त_tpg;
	पूर्ण

	ret = core_tpg_रेजिस्टर(wwn, &tpg->se_tpg, SCSI_PROTOCOL_SBP);
	अगर (ret < 0)
		जाओ out_unreg_mgt_agt;

	वापस &tpg->se_tpg;

out_unreg_mgt_agt:
	sbp_management_agent_unरेजिस्टर(tport->mgt_agt);
out_मुक्त_tpg:
	tport->tpg = शून्य;
	kमुक्त(tpg);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम sbp_drop_tpg(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;

	core_tpg_deरेजिस्टर(se_tpg);
	sbp_management_agent_unरेजिस्टर(tport->mgt_agt);
	tport->tpg = शून्य;
	kमुक्त(tpg);
पूर्ण

अटल काष्ठा se_wwn *sbp_make_tport(
		काष्ठा target_fabric_configfs *tf,
		काष्ठा config_group *group,
		स्थिर अक्षर *name)
अणु
	काष्ठा sbp_tport *tport;
	u64 guid = 0;

	अगर (sbp_parse_wwn(name, &guid) < 0)
		वापस ERR_PTR(-EINVAL);

	tport = kzalloc(माप(*tport), GFP_KERNEL);
	अगर (!tport)
		वापस ERR_PTR(-ENOMEM);

	tport->guid = guid;
	sbp_क्रमmat_wwn(tport->tport_name, SBP_NAMELEN, guid);

	वापस &tport->tport_wwn;
पूर्ण

अटल व्योम sbp_drop_tport(काष्ठा se_wwn *wwn)
अणु
	काष्ठा sbp_tport *tport =
		container_of(wwn, काष्ठा sbp_tport, tport_wwn);

	kमुक्त(tport);
पूर्ण

अटल sमाप_प्रकार sbp_wwn_version_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "FireWire SBP fabric module %s\n", SBP_VERSION);
पूर्ण

CONFIGFS_ATTR_RO(sbp_wwn_, version);

अटल काष्ठा configfs_attribute *sbp_wwn_attrs[] = अणु
	&sbp_wwn_attr_version,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार sbp_tpg_directory_id_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;

	अगर (tport->directory_id == -1)
		वापस प्र_लिखो(page, "implicit\n");
	अन्यथा
		वापस प्र_लिखो(page, "%06x\n", tport->directory_id);
पूर्ण

अटल sमाप_प्रकार sbp_tpg_directory_id_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	अचिन्हित दीर्घ val;

	अगर (tport->enable) अणु
		pr_err("Cannot change the directory_id on an active target.\n");
		वापस -EBUSY;
	पूर्ण

	अगर (म_माला(page, "implicit") == page) अणु
		tport->directory_id = -1;
	पूर्ण अन्यथा अणु
		अगर (kम_से_अदीर्घ(page, 16, &val) < 0)
			वापस -EINVAL;
		अगर (val > 0xffffff)
			वापस -EINVAL;

		tport->directory_id = val;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार sbp_tpg_enable_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	वापस प्र_लिखो(page, "%d\n", tport->enable);
पूर्ण

अटल sमाप_प्रकार sbp_tpg_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(page, 0, &val) < 0)
		वापस -EINVAL;
	अगर ((val != 0) && (val != 1))
		वापस -EINVAL;

	अगर (tport->enable == val)
		वापस count;

	अगर (val) अणु
		अगर (sbp_count_se_tpg_luns(&tpg->se_tpg) == 0) अणु
			pr_err("Cannot enable a target with no LUNs!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* XXX: क्रमce-shutकरोwn sessions instead? */
		spin_lock_bh(&se_tpg->session_lock);
		अगर (!list_empty(&se_tpg->tpg_sess_list)) अणु
			spin_unlock_bh(&se_tpg->session_lock);
			वापस -EBUSY;
		पूर्ण
		spin_unlock_bh(&se_tpg->session_lock);
	पूर्ण

	tport->enable = val;

	ret = sbp_update_unit_directory(tport);
	अगर (ret < 0) अणु
		pr_err("Could not update Config ROM\n");
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

CONFIGFS_ATTR(sbp_tpg_, directory_id);
CONFIGFS_ATTR(sbp_tpg_, enable);

अटल काष्ठा configfs_attribute *sbp_tpg_base_attrs[] = अणु
	&sbp_tpg_attr_directory_id,
	&sbp_tpg_attr_enable,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार sbp_tpg_attrib_mgt_orb_समयout_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	वापस प्र_लिखो(page, "%d\n", tport->mgt_orb_समयout);
पूर्ण

अटल sमाप_प्रकार sbp_tpg_attrib_mgt_orb_समयout_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(page, 0, &val) < 0)
		वापस -EINVAL;
	अगर ((val < 1) || (val > 127))
		वापस -EINVAL;

	अगर (tport->mgt_orb_समयout == val)
		वापस count;

	tport->mgt_orb_समयout = val;

	ret = sbp_update_unit_directory(tport);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sbp_tpg_attrib_max_reconnect_समयout_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	वापस प्र_लिखो(page, "%d\n", tport->max_reconnect_समयout);
पूर्ण

अटल sमाप_प्रकार sbp_tpg_attrib_max_reconnect_समयout_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(page, 0, &val) < 0)
		वापस -EINVAL;
	अगर ((val < 1) || (val > 32767))
		वापस -EINVAL;

	अगर (tport->max_reconnect_समयout == val)
		वापस count;

	tport->max_reconnect_समयout = val;

	ret = sbp_update_unit_directory(tport);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sbp_tpg_attrib_max_logins_per_lun_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	वापस प्र_लिखो(page, "%d\n", tport->max_logins_per_lun);
पूर्ण

अटल sमाप_प्रकार sbp_tpg_attrib_max_logins_per_lun_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा sbp_tpg *tpg = container_of(se_tpg, काष्ठा sbp_tpg, se_tpg);
	काष्ठा sbp_tport *tport = tpg->tport;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(page, 0, &val) < 0)
		वापस -EINVAL;
	अगर ((val < 1) || (val > 127))
		वापस -EINVAL;

	/* XXX: also check against current count? */

	tport->max_logins_per_lun = val;

	वापस count;
पूर्ण

CONFIGFS_ATTR(sbp_tpg_attrib_, mgt_orb_समयout);
CONFIGFS_ATTR(sbp_tpg_attrib_, max_reconnect_समयout);
CONFIGFS_ATTR(sbp_tpg_attrib_, max_logins_per_lun);

अटल काष्ठा configfs_attribute *sbp_tpg_attrib_attrs[] = अणु
	&sbp_tpg_attrib_attr_mgt_orb_समयout,
	&sbp_tpg_attrib_attr_max_reconnect_समयout,
	&sbp_tpg_attrib_attr_max_logins_per_lun,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा target_core_fabric_ops sbp_ops = अणु
	.module				= THIS_MODULE,
	.fabric_name			= "sbp",
	.tpg_get_wwn			= sbp_get_fabric_wwn,
	.tpg_get_tag			= sbp_get_tag,
	.tpg_check_demo_mode		= sbp_check_true,
	.tpg_check_demo_mode_cache	= sbp_check_true,
	.tpg_check_demo_mode_ग_लिखो_protect = sbp_check_false,
	.tpg_check_prod_mode_ग_लिखो_protect = sbp_check_false,
	.tpg_get_inst_index		= sbp_tpg_get_inst_index,
	.release_cmd			= sbp_release_cmd,
	.sess_get_index			= sbp_sess_get_index,
	.ग_लिखो_pending			= sbp_ग_लिखो_pending,
	.set_शेष_node_attributes	= sbp_set_शेष_node_attrs,
	.get_cmd_state			= sbp_get_cmd_state,
	.queue_data_in			= sbp_queue_data_in,
	.queue_status			= sbp_queue_status,
	.queue_पंचांग_rsp			= sbp_queue_पंचांग_rsp,
	.पातed_task			= sbp_पातed_task,
	.check_stop_मुक्त		= sbp_check_stop_मुक्त,

	.fabric_make_wwn		= sbp_make_tport,
	.fabric_drop_wwn		= sbp_drop_tport,
	.fabric_make_tpg		= sbp_make_tpg,
	.fabric_drop_tpg		= sbp_drop_tpg,
	.fabric_post_link		= sbp_post_link_lun,
	.fabric_pre_unlink		= sbp_pre_unlink_lun,
	.fabric_make_np			= शून्य,
	.fabric_drop_np			= शून्य,
	.fabric_init_nodeacl		= sbp_init_nodeacl,

	.tfc_wwn_attrs			= sbp_wwn_attrs,
	.tfc_tpg_base_attrs		= sbp_tpg_base_attrs,
	.tfc_tpg_attrib_attrs		= sbp_tpg_attrib_attrs,
पूर्ण;

अटल पूर्णांक __init sbp_init(व्योम)
अणु
	वापस target_रेजिस्टर_ढाँचा(&sbp_ops);
पूर्ण;

अटल व्योम __निकास sbp_निकास(व्योम)
अणु
	target_unरेजिस्टर_ढाँचा(&sbp_ops);
पूर्ण;

MODULE_DESCRIPTION("FireWire SBP fabric driver");
MODULE_LICENSE("GPL");
module_init(sbp_init);
module_निकास(sbp_निकास);
