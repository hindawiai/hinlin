<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains the configfs implementation क्रम iSCSI Target mode
 * from the LIO-Target Project.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ****************************************************************************/

#समावेश <linux/configfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/export.h>
#समावेश <linux/inet.h>
#समावेश <linux/module.h>
#समावेश <net/ipv6.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/iscsi/iscsi_transport.h>
#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_parameters.h"
#समावेश "iscsi_target_device.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_nodeattrib.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"
#समावेश <target/iscsi/iscsi_target_स्थिति.स>


/* Start items क्रम lio_target_portal_cit */

अटल अंतरभूत काष्ठा iscsi_tpg_np *to_iscsi_tpg_np(काष्ठा config_item *item)
अणु
	वापस container_of(to_tpg_np(item), काष्ठा iscsi_tpg_np, se_tpg_np);
पूर्ण

अटल sमाप_प्रकार lio_target_np_driver_show(काष्ठा config_item *item, अक्षर *page,
					 क्रमागत iscsit_transport_type type)
अणु
	काष्ठा iscsi_tpg_np *tpg_np = to_iscsi_tpg_np(item);
	काष्ठा iscsi_tpg_np *tpg_np_new;
	sमाप_प्रकार rb;

	tpg_np_new = iscsit_tpg_locate_child_np(tpg_np, type);
	अगर (tpg_np_new)
		rb = प्र_लिखो(page, "1\n");
	अन्यथा
		rb = प्र_लिखो(page, "0\n");

	वापस rb;
पूर्ण

अटल sमाप_प्रकार lio_target_np_driver_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count, क्रमागत iscsit_transport_type type,
		स्थिर अक्षर *mod_name)
अणु
	काष्ठा iscsi_tpg_np *tpg_np = to_iscsi_tpg_np(item);
	काष्ठा iscsi_np *np;
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tpg_np *tpg_np_new = शून्य;
	u32 op;
	पूर्णांक rc;

	rc = kstrtou32(page, 0, &op);
	अगर (rc)
		वापस rc;
	अगर ((op != 1) && (op != 0)) अणु
		pr_err("Illegal value for tpg_enable: %u\n", op);
		वापस -EINVAL;
	पूर्ण
	np = tpg_np->tpg_np;
	अगर (!np) अणु
		pr_err("Unable to locate struct iscsi_np from"
				" struct iscsi_tpg_np\n");
		वापस -EINVAL;
	पूर्ण

	tpg = tpg_np->tpg;
	अगर (iscsit_get_tpg(tpg) < 0)
		वापस -EINVAL;

	अगर (op) अणु
		अगर (म_माप(mod_name)) अणु
			rc = request_module(mod_name);
			अगर (rc != 0) अणु
				pr_warn("Unable to request_module for %s\n",
					mod_name);
				rc = 0;
			पूर्ण
		पूर्ण

		tpg_np_new = iscsit_tpg_add_network_portal(tpg,
					&np->np_sockaddr, tpg_np, type);
		अगर (IS_ERR(tpg_np_new)) अणु
			rc = PTR_ERR(tpg_np_new);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		tpg_np_new = iscsit_tpg_locate_child_np(tpg_np, type);
		अगर (tpg_np_new) अणु
			rc = iscsit_tpg_del_network_portal(tpg, tpg_np_new);
			अगर (rc < 0)
				जाओ out;
		पूर्ण
	पूर्ण

	iscsit_put_tpg(tpg);
	वापस count;
out:
	iscsit_put_tpg(tpg);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार lio_target_np_iser_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस lio_target_np_driver_show(item, page, ISCSI_INFINIBAND);
पूर्ण

अटल sमाप_प्रकार lio_target_np_iser_store(काष्ठा config_item *item,
					स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस lio_target_np_driver_store(item, page, count,
					  ISCSI_INFINIBAND, "ib_isert");
पूर्ण
CONFIGFS_ATTR(lio_target_np_, iser);

अटल sमाप_प्रकार lio_target_np_cxgbit_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस lio_target_np_driver_show(item, page, ISCSI_CXGBIT);
पूर्ण

अटल sमाप_प्रकार lio_target_np_cxgbit_store(काष्ठा config_item *item,
					  स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस lio_target_np_driver_store(item, page, count,
					  ISCSI_CXGBIT, "cxgbit");
पूर्ण
CONFIGFS_ATTR(lio_target_np_, cxgbit);

अटल काष्ठा configfs_attribute *lio_target_portal_attrs[] = अणु
	&lio_target_np_attr_iser,
	&lio_target_np_attr_cxgbit,
	शून्य,
पूर्ण;

/* Stop items क्रम lio_target_portal_cit */

/* Start items क्रम lio_target_np_cit */

#घोषणा MAX_PORTAL_LEN		256

अटल काष्ठा se_tpg_np *lio_target_call_addnptotpg(
	काष्ठा se_portal_group *se_tpg,
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tpg_np *tpg_np;
	अक्षर *str, *str2, *ip_str, *port_str;
	काष्ठा sockaddr_storage sockaddr = अणु पूर्ण;
	पूर्णांक ret;
	अक्षर buf[MAX_PORTAL_LEN + 1] = अणु पूर्ण;

	अगर (म_माप(name) > MAX_PORTAL_LEN) अणु
		pr_err("strlen(name): %d exceeds MAX_PORTAL_LEN: %d\n",
			(पूर्णांक)म_माप(name), MAX_PORTAL_LEN);
		वापस ERR_PTR(-EOVERFLOW);
	पूर्ण
	snम_लिखो(buf, MAX_PORTAL_LEN + 1, "%s", name);

	str = म_माला(buf, "[");
	अगर (str) अणु
		str2 = म_माला(str, "]");
		अगर (!str2) अणु
			pr_err("Unable to locate trailing \"]\""
				" in IPv6 iSCSI network portal address\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		ip_str = str + 1; /* Skip over leading "[" */
		*str2 = '\0'; /* Terminate the unbracketed IPv6 address */
		str2++; /* Skip over the \0 */

		port_str = म_माला(str2, ":");
		अगर (!port_str) अणु
			pr_err("Unable to locate \":port\""
				" in IPv6 iSCSI network portal address\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		*port_str = '\0'; /* Terminate string क्रम IP */
		port_str++; /* Skip over ":" */
	पूर्ण अन्यथा अणु
		ip_str = &buf[0];
		port_str = म_माला(ip_str, ":");
		अगर (!port_str) अणु
			pr_err("Unable to locate \":port\""
				" in IPv4 iSCSI network portal address\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		*port_str = '\0'; /* Terminate string क्रम IP */
		port_str++; /* Skip over ":" */
	पूर्ण

	ret = inet_pton_with_scope(&init_net, AF_UNSPEC, ip_str,
			port_str, &sockaddr);
	अगर (ret) अणु
		pr_err("malformed ip/port passed: %s\n", name);
		वापस ERR_PTR(ret);
	पूर्ण

	tpg = container_of(se_tpg, काष्ठा iscsi_portal_group, tpg_se_tpg);
	ret = iscsit_get_tpg(tpg);
	अगर (ret < 0)
		वापस ERR_PTR(-EINVAL);

	pr_debug("LIO_Target_ConfigFS: REGISTER -> %s TPGT: %hu"
		" PORTAL: %s\n",
		config_item_name(&se_tpg->se_tpg_wwn->wwn_group.cg_item),
		tpg->tpgt, name);
	/*
	 * Assume ISCSI_TCP by शेष.  Other network portals क्रम other
	 * iSCSI fabrics:
	 *
	 * Traditional iSCSI over SCTP (initial support)
	 * iSER/TCP (TODO, hardware available)
	 * iSER/SCTP (TODO, software emulation with osc-iwarp)
	 * iSER/IB (TODO, hardware available)
	 *
	 * can be enabled with attributes under
	 * sys/kernel/config/iscsi/$IQN/$TPG/np/$IP:$PORT/
	 *
	 */
	tpg_np = iscsit_tpg_add_network_portal(tpg, &sockaddr, शून्य,
				ISCSI_TCP);
	अगर (IS_ERR(tpg_np)) अणु
		iscsit_put_tpg(tpg);
		वापस ERR_CAST(tpg_np);
	पूर्ण
	pr_debug("LIO_Target_ConfigFS: addnptotpg done!\n");

	iscsit_put_tpg(tpg);
	वापस &tpg_np->se_tpg_np;
पूर्ण

अटल व्योम lio_target_call_delnpfromtpg(
	काष्ठा se_tpg_np *se_tpg_np)
अणु
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tpg_np *tpg_np;
	काष्ठा se_portal_group *se_tpg;
	पूर्णांक ret;

	tpg_np = container_of(se_tpg_np, काष्ठा iscsi_tpg_np, se_tpg_np);
	tpg = tpg_np->tpg;
	ret = iscsit_get_tpg(tpg);
	अगर (ret < 0)
		वापस;

	se_tpg = &tpg->tpg_se_tpg;
	pr_debug("LIO_Target_ConfigFS: DEREGISTER -> %s TPGT: %hu"
		" PORTAL: %pISpc\n", config_item_name(&se_tpg->se_tpg_wwn->wwn_group.cg_item),
		tpg->tpgt, &tpg_np->tpg_np->np_sockaddr);

	ret = iscsit_tpg_del_network_portal(tpg, tpg_np);
	अगर (ret < 0)
		जाओ out;

	pr_debug("LIO_Target_ConfigFS: delnpfromtpg done!\n");
out:
	iscsit_put_tpg(tpg);
पूर्ण

/* End items क्रम lio_target_np_cit */

/* Start items क्रम lio_target_nacl_attrib_cit */

#घोषणा ISCSI_NACL_ATTR(name)						\
अटल sमाप_प्रकार iscsi_nacl_attrib_##name##_show(काष्ठा config_item *item,\
		अक्षर *page)						\
अणु									\
	काष्ठा se_node_acl *se_nacl = attrib_to_nacl(item);		\
	काष्ठा iscsi_node_acl *nacl = container_of(se_nacl, काष्ठा iscsi_node_acl, \
					se_node_acl);			\
									\
	वापस प्र_लिखो(page, "%u\n", nacl->node_attrib.name);		\
पूर्ण									\
									\
अटल sमाप_प्रकार iscsi_nacl_attrib_##name##_store(काष्ठा config_item *item,\
		स्थिर अक्षर *page, माप_प्रकार count)				\
अणु									\
	काष्ठा se_node_acl *se_nacl = attrib_to_nacl(item);		\
	काष्ठा iscsi_node_acl *nacl = container_of(se_nacl, काष्ठा iscsi_node_acl, \
					se_node_acl);			\
	u32 val;							\
	पूर्णांक ret;							\
									\
	ret = kstrtou32(page, 0, &val);					\
	अगर (ret)							\
		वापस ret;						\
	ret = iscsit_na_##name(nacl, val);				\
	अगर (ret < 0)							\
		वापस ret;						\
									\
	वापस count;							\
पूर्ण									\
									\
CONFIGFS_ATTR(iscsi_nacl_attrib_, name)

ISCSI_NACL_ATTR(dataout_समयout);
ISCSI_NACL_ATTR(dataout_समयout_retries);
ISCSI_NACL_ATTR(शेष_erl);
ISCSI_NACL_ATTR(nopin_समयout);
ISCSI_NACL_ATTR(nopin_response_समयout);
ISCSI_NACL_ATTR(अक्रमom_datain_pdu_offsets);
ISCSI_NACL_ATTR(अक्रमom_datain_seq_offsets);
ISCSI_NACL_ATTR(अक्रमom_r2t_offsets);

अटल काष्ठा configfs_attribute *lio_target_nacl_attrib_attrs[] = अणु
	&iscsi_nacl_attrib_attr_dataout_समयout,
	&iscsi_nacl_attrib_attr_dataout_समयout_retries,
	&iscsi_nacl_attrib_attr_शेष_erl,
	&iscsi_nacl_attrib_attr_nopin_समयout,
	&iscsi_nacl_attrib_attr_nopin_response_समयout,
	&iscsi_nacl_attrib_attr_अक्रमom_datain_pdu_offsets,
	&iscsi_nacl_attrib_attr_अक्रमom_datain_seq_offsets,
	&iscsi_nacl_attrib_attr_अक्रमom_r2t_offsets,
	शून्य,
पूर्ण;

/* End items क्रम lio_target_nacl_attrib_cit */

/* Start items क्रम lio_target_nacl_auth_cit */

#घोषणा __DEF_NACL_AUTH_STR(prefix, name, flags)			\
अटल sमाप_प्रकार __iscsi_##prefix##_##name##_show(			\
	काष्ठा iscsi_node_acl *nacl,					\
	अक्षर *page)							\
अणु									\
	काष्ठा iscsi_node_auth *auth = &nacl->node_auth;		\
									\
	अगर (!capable(CAP_SYS_ADMIN))					\
		वापस -EPERM;						\
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", auth->name);		\
पूर्ण									\
									\
अटल sमाप_प्रकार __iscsi_##prefix##_##name##_store(			\
	काष्ठा iscsi_node_acl *nacl,					\
	स्थिर अक्षर *page,						\
	माप_प्रकार count)							\
अणु									\
	काष्ठा iscsi_node_auth *auth = &nacl->node_auth;		\
									\
	अगर (!capable(CAP_SYS_ADMIN))					\
		वापस -EPERM;						\
	अगर (count >= माप(auth->name))				\
		वापस -EINVAL;						\
	snम_लिखो(auth->name, माप(auth->name), "%s", page);		\
	अगर (!म_भेदन("NULL", auth->name, 4))				\
		auth->naf_flags &= ~flags;				\
	अन्यथा								\
		auth->naf_flags |= flags;				\
									\
	अगर ((auth->naf_flags & NAF_USERID_IN_SET) &&			\
	    (auth->naf_flags & NAF_PASSWORD_IN_SET))			\
		auth->authenticate_target = 1;				\
	अन्यथा								\
		auth->authenticate_target = 0;				\
									\
	वापस count;							\
पूर्ण

#घोषणा DEF_NACL_AUTH_STR(name, flags)					\
	__DEF_NACL_AUTH_STR(nacl_auth, name, flags)			\
अटल sमाप_प्रकार iscsi_nacl_auth_##name##_show(काष्ठा config_item *item,	\
		अक्षर *page)						\
अणु									\
	काष्ठा se_node_acl *nacl = auth_to_nacl(item);			\
	वापस __iscsi_nacl_auth_##name##_show(container_of(nacl,	\
			काष्ठा iscsi_node_acl, se_node_acl), page);	\
पूर्ण									\
अटल sमाप_प्रकार iscsi_nacl_auth_##name##_store(काष्ठा config_item *item,	\
		स्थिर अक्षर *page, माप_प्रकार count)				\
अणु									\
	काष्ठा se_node_acl *nacl = auth_to_nacl(item);			\
	वापस __iscsi_nacl_auth_##name##_store(container_of(nacl,	\
			काष्ठा iscsi_node_acl, se_node_acl), page, count); \
पूर्ण									\
									\
CONFIGFS_ATTR(iscsi_nacl_auth_, name)

/*
 * One-way authentication userid
 */
DEF_NACL_AUTH_STR(userid, NAF_USERID_SET);
DEF_NACL_AUTH_STR(password, NAF_PASSWORD_SET);
DEF_NACL_AUTH_STR(userid_mutual, NAF_USERID_IN_SET);
DEF_NACL_AUTH_STR(password_mutual, NAF_PASSWORD_IN_SET);

#घोषणा __DEF_NACL_AUTH_INT(prefix, name)				\
अटल sमाप_प्रकार __iscsi_##prefix##_##name##_show(				\
	काष्ठा iscsi_node_acl *nacl,					\
	अक्षर *page)							\
अणु									\
	काष्ठा iscsi_node_auth *auth = &nacl->node_auth;		\
									\
	अगर (!capable(CAP_SYS_ADMIN))					\
		वापस -EPERM;						\
									\
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", auth->name);		\
पूर्ण

#घोषणा DEF_NACL_AUTH_INT(name)						\
	__DEF_NACL_AUTH_INT(nacl_auth, name)				\
अटल sमाप_प्रकार iscsi_nacl_auth_##name##_show(काष्ठा config_item *item,	\
		अक्षर *page)						\
अणु									\
	काष्ठा se_node_acl *nacl = auth_to_nacl(item);			\
	वापस __iscsi_nacl_auth_##name##_show(container_of(nacl,	\
			काष्ठा iscsi_node_acl, se_node_acl), page);	\
पूर्ण									\
									\
CONFIGFS_ATTR_RO(iscsi_nacl_auth_, name)

DEF_NACL_AUTH_INT(authenticate_target);

अटल काष्ठा configfs_attribute *lio_target_nacl_auth_attrs[] = अणु
	&iscsi_nacl_auth_attr_userid,
	&iscsi_nacl_auth_attr_password,
	&iscsi_nacl_auth_attr_authenticate_target,
	&iscsi_nacl_auth_attr_userid_mutual,
	&iscsi_nacl_auth_attr_password_mutual,
	शून्य,
पूर्ण;

/* End items क्रम lio_target_nacl_auth_cit */

/* Start items क्रम lio_target_nacl_param_cit */

#घोषणा ISCSI_NACL_PARAM(name)						\
अटल sमाप_प्रकार iscsi_nacl_param_##name##_show(काष्ठा config_item *item,	\
		अक्षर *page)						\
अणु									\
	काष्ठा se_node_acl *se_nacl = param_to_nacl(item);		\
	काष्ठा iscsi_session *sess;					\
	काष्ठा se_session *se_sess;					\
	sमाप_प्रकार rb;							\
									\
	spin_lock_bh(&se_nacl->nacl_sess_lock);				\
	se_sess = se_nacl->nacl_sess;					\
	अगर (!se_sess) अणु							\
		rb = snम_लिखो(page, PAGE_SIZE,				\
			"No Active iSCSI Session\n");			\
	पूर्ण अन्यथा अणु							\
		sess = se_sess->fabric_sess_ptr;			\
		rb = snम_लिखो(page, PAGE_SIZE, "%u\n",			\
			(u32)sess->sess_ops->name);			\
	पूर्ण								\
	spin_unlock_bh(&se_nacl->nacl_sess_lock);			\
									\
	वापस rb;							\
पूर्ण									\
									\
CONFIGFS_ATTR_RO(iscsi_nacl_param_, name)

ISCSI_NACL_PARAM(MaxConnections);
ISCSI_NACL_PARAM(InitialR2T);
ISCSI_NACL_PARAM(ImmediateData);
ISCSI_NACL_PARAM(MaxBurstLength);
ISCSI_NACL_PARAM(FirstBurstLength);
ISCSI_NACL_PARAM(DefaultTime2Wait);
ISCSI_NACL_PARAM(DefaultTime2Retain);
ISCSI_NACL_PARAM(MaxOutstandingR2T);
ISCSI_NACL_PARAM(DataPDUInOrder);
ISCSI_NACL_PARAM(DataSequenceInOrder);
ISCSI_NACL_PARAM(ErrorRecoveryLevel);

अटल काष्ठा configfs_attribute *lio_target_nacl_param_attrs[] = अणु
	&iscsi_nacl_param_attr_MaxConnections,
	&iscsi_nacl_param_attr_InitialR2T,
	&iscsi_nacl_param_attr_ImmediateData,
	&iscsi_nacl_param_attr_MaxBurstLength,
	&iscsi_nacl_param_attr_FirstBurstLength,
	&iscsi_nacl_param_attr_DefaultTime2Wait,
	&iscsi_nacl_param_attr_DefaultTime2Retain,
	&iscsi_nacl_param_attr_MaxOutstandingR2T,
	&iscsi_nacl_param_attr_DataPDUInOrder,
	&iscsi_nacl_param_attr_DataSequenceInOrder,
	&iscsi_nacl_param_attr_ErrorRecoveryLevel,
	शून्य,
पूर्ण;

/* End items क्रम lio_target_nacl_param_cit */

/* Start items क्रम lio_target_acl_cit */

अटल sमाप_प्रकार lio_target_nacl_info_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_node_acl *se_nacl = acl_to_nacl(item);
	काष्ठा iscsi_session *sess;
	काष्ठा iscsi_conn *conn;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार rb = 0;
	u32 max_cmd_sn;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (!se_sess) अणु
		rb += प्र_लिखो(page+rb, "No active iSCSI Session for Initiator"
			" Endpoint: %s\n", se_nacl->initiatorname);
	पूर्ण अन्यथा अणु
		sess = se_sess->fabric_sess_ptr;

		rb += प्र_लिखो(page+rb, "InitiatorName: %s\n",
			sess->sess_ops->InitiatorName);
		rb += प्र_लिखो(page+rb, "InitiatorAlias: %s\n",
			sess->sess_ops->InitiatorAlias);

		rb += प्र_लिखो(page+rb,
			      "LIO Session ID: %u   ISID: 0x%6ph  TSIH: %hu  ",
			      sess->sid, sess->isid, sess->tsih);
		rb += प्र_लिखो(page+rb, "SessionType: %s\n",
				(sess->sess_ops->SessionType) ?
				"Discovery" : "Normal");
		rb += प्र_लिखो(page+rb, "Session State: ");
		चयन (sess->session_state) अणु
		हाल TARG_SESS_STATE_FREE:
			rb += प्र_लिखो(page+rb, "TARG_SESS_FREE\n");
			अवरोध;
		हाल TARG_SESS_STATE_ACTIVE:
			rb += प्र_लिखो(page+rb, "TARG_SESS_STATE_ACTIVE\n");
			अवरोध;
		हाल TARG_SESS_STATE_LOGGED_IN:
			rb += प्र_लिखो(page+rb, "TARG_SESS_STATE_LOGGED_IN\n");
			अवरोध;
		हाल TARG_SESS_STATE_FAILED:
			rb += प्र_लिखो(page+rb, "TARG_SESS_STATE_FAILED\n");
			अवरोध;
		हाल TARG_SESS_STATE_IN_CONTINUE:
			rb += प्र_लिखो(page+rb, "TARG_SESS_STATE_IN_CONTINUE\n");
			अवरोध;
		शेष:
			rb += प्र_लिखो(page+rb, "ERROR: Unknown Session"
					" State!\n");
			अवरोध;
		पूर्ण

		rb += प्र_लिखो(page+rb, "---------------------[iSCSI Session"
				" Values]-----------------------\n");
		rb += प्र_लिखो(page+rb, "  CmdSN/WR  :  CmdSN/WC  :  ExpCmdSN"
				"  :  MaxCmdSN  :     ITT    :     TTT\n");
		max_cmd_sn = (u32) atomic_पढ़ो(&sess->max_cmd_sn);
		rb += प्र_लिखो(page+rb, " 0x%08x   0x%08x   0x%08x   0x%08x"
				"   0x%08x   0x%08x\n",
			sess->cmdsn_winकरोw,
			(max_cmd_sn - sess->exp_cmd_sn) + 1,
			sess->exp_cmd_sn, max_cmd_sn,
			sess->init_task_tag, sess->targ_xfer_tag);
		rb += प्र_लिखो(page+rb, "----------------------[iSCSI"
				" Connections]-------------------------\n");

		spin_lock(&sess->conn_lock);
		list_क्रम_each_entry(conn, &sess->sess_conn_list, conn_list) अणु
			rb += प्र_लिखो(page+rb, "CID: %hu  Connection"
					" State: ", conn->cid);
			चयन (conn->conn_state) अणु
			हाल TARG_CONN_STATE_FREE:
				rb += प्र_लिखो(page+rb,
					"TARG_CONN_STATE_FREE\n");
				अवरोध;
			हाल TARG_CONN_STATE_XPT_UP:
				rb += प्र_लिखो(page+rb,
					"TARG_CONN_STATE_XPT_UP\n");
				अवरोध;
			हाल TARG_CONN_STATE_IN_LOGIN:
				rb += प्र_लिखो(page+rb,
					"TARG_CONN_STATE_IN_LOGIN\n");
				अवरोध;
			हाल TARG_CONN_STATE_LOGGED_IN:
				rb += प्र_लिखो(page+rb,
					"TARG_CONN_STATE_LOGGED_IN\n");
				अवरोध;
			हाल TARG_CONN_STATE_IN_LOGOUT:
				rb += प्र_लिखो(page+rb,
					"TARG_CONN_STATE_IN_LOGOUT\n");
				अवरोध;
			हाल TARG_CONN_STATE_LOGOUT_REQUESTED:
				rb += प्र_लिखो(page+rb,
					"TARG_CONN_STATE_LOGOUT_REQUESTED\n");
				अवरोध;
			हाल TARG_CONN_STATE_CLEANUP_WAIT:
				rb += प्र_लिखो(page+rb,
					"TARG_CONN_STATE_CLEANUP_WAIT\n");
				अवरोध;
			शेष:
				rb += प्र_लिखो(page+rb,
					"ERROR: Unknown Connection State!\n");
				अवरोध;
			पूर्ण

			rb += प्र_लिखो(page+rb, "   Address %pISc %s", &conn->login_sockaddr,
				(conn->network_transport == ISCSI_TCP) ?
				"TCP" : "SCTP");
			rb += प्र_लिखो(page+rb, "  StatSN: 0x%08x\n",
				conn->stat_sn);
		पूर्ण
		spin_unlock(&sess->conn_lock);
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस rb;
पूर्ण

अटल sमाप_प्रकार lio_target_nacl_cmdsn_depth_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", acl_to_nacl(item)->queue_depth);
पूर्ण

अटल sमाप_प्रकार lio_target_nacl_cmdsn_depth_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_node_acl *se_nacl = acl_to_nacl(item);
	काष्ठा se_portal_group *se_tpg = se_nacl->se_tpg;
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,
			काष्ठा iscsi_portal_group, tpg_se_tpg);
	काष्ठा config_item *acl_ci, *tpg_ci, *wwn_ci;
	u32 cmdsn_depth = 0;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &cmdsn_depth);
	अगर (ret)
		वापस ret;
	अगर (cmdsn_depth > TA_DEFAULT_CMDSN_DEPTH_MAX) अणु
		pr_err("Passed cmdsn_depth: %u exceeds"
			" TA_DEFAULT_CMDSN_DEPTH_MAX: %u\n", cmdsn_depth,
			TA_DEFAULT_CMDSN_DEPTH_MAX);
		वापस -EINVAL;
	पूर्ण
	acl_ci = &se_nacl->acl_group.cg_item;
	अगर (!acl_ci) अणु
		pr_err("Unable to locatel acl_ci\n");
		वापस -EINVAL;
	पूर्ण
	tpg_ci = &acl_ci->ci_parent->ci_group->cg_item;
	अगर (!tpg_ci) अणु
		pr_err("Unable to locate tpg_ci\n");
		वापस -EINVAL;
	पूर्ण
	wwn_ci = &tpg_ci->ci_group->cg_item;
	अगर (!wwn_ci) अणु
		pr_err("Unable to locate config_item wwn_ci\n");
		वापस -EINVAL;
	पूर्ण

	अगर (iscsit_get_tpg(tpg) < 0)
		वापस -EINVAL;

	ret = core_tpg_set_initiator_node_queue_depth(se_nacl, cmdsn_depth);

	pr_debug("LIO_Target_ConfigFS: %s/%s Set CmdSN Window: %u for"
		"InitiatorName: %s\n", config_item_name(wwn_ci),
		config_item_name(tpg_ci), cmdsn_depth,
		config_item_name(acl_ci));

	iscsit_put_tpg(tpg);
	वापस (!ret) ? count : (sमाप_प्रकार)ret;
पूर्ण

अटल sमाप_प्रकार lio_target_nacl_tag_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s", acl_to_nacl(item)->acl_tag);
पूर्ण

अटल sमाप_प्रकार lio_target_nacl_tag_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_node_acl *se_nacl = acl_to_nacl(item);
	पूर्णांक ret;

	ret = core_tpg_set_initiator_node_tag(se_nacl->se_tpg, se_nacl, page);

	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

CONFIGFS_ATTR_RO(lio_target_nacl_, info);
CONFIGFS_ATTR(lio_target_nacl_, cmdsn_depth);
CONFIGFS_ATTR(lio_target_nacl_, tag);

अटल काष्ठा configfs_attribute *lio_target_initiator_attrs[] = अणु
	&lio_target_nacl_attr_info,
	&lio_target_nacl_attr_cmdsn_depth,
	&lio_target_nacl_attr_tag,
	शून्य,
पूर्ण;

अटल पूर्णांक lio_target_init_nodeacl(काष्ठा se_node_acl *se_nacl,
		स्थिर अक्षर *name)
अणु
	काष्ठा iscsi_node_acl *acl =
		container_of(se_nacl, काष्ठा iscsi_node_acl, se_node_acl);

	config_group_init_type_name(&acl->node_stat_grps.iscsi_sess_stats_group,
			"iscsi_sess_stats", &iscsi_stat_sess_cit);
	configfs_add_शेष_group(&acl->node_stat_grps.iscsi_sess_stats_group,
			&se_nacl->acl_fabric_stat_group);
	वापस 0;
पूर्ण

/* End items क्रम lio_target_acl_cit */

/* Start items क्रम lio_target_tpg_attrib_cit */

#घोषणा DEF_TPG_ATTRIB(name)						\
									\
अटल sमाप_प्रकार iscsi_tpg_attrib_##name##_show(काष्ठा config_item *item,	\
		अक्षर *page)						\
अणु									\
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);		\
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,		\
			काष्ठा iscsi_portal_group, tpg_se_tpg);	\
	sमाप_प्रकार rb;							\
									\
	अगर (iscsit_get_tpg(tpg) < 0)					\
		वापस -EINVAL;						\
									\
	rb = प्र_लिखो(page, "%u\n", tpg->tpg_attrib.name);		\
	iscsit_put_tpg(tpg);						\
	वापस rb;							\
पूर्ण									\
									\
अटल sमाप_प्रकार iscsi_tpg_attrib_##name##_store(काष्ठा config_item *item,\
		स्थिर अक्षर *page, माप_प्रकार count)				\
अणु									\
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);		\
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,		\
			काष्ठा iscsi_portal_group, tpg_se_tpg);	\
	u32 val;							\
	पूर्णांक ret;							\
									\
	अगर (iscsit_get_tpg(tpg) < 0)					\
		वापस -EINVAL;						\
									\
	ret = kstrtou32(page, 0, &val);					\
	अगर (ret)							\
		जाओ out;						\
	ret = iscsit_ta_##name(tpg, val);				\
	अगर (ret < 0)							\
		जाओ out;						\
									\
	iscsit_put_tpg(tpg);						\
	वापस count;							\
out:									\
	iscsit_put_tpg(tpg);						\
	वापस ret;							\
पूर्ण									\
CONFIGFS_ATTR(iscsi_tpg_attrib_, name)

DEF_TPG_ATTRIB(authentication);
DEF_TPG_ATTRIB(login_समयout);
DEF_TPG_ATTRIB(netअगर_समयout);
DEF_TPG_ATTRIB(generate_node_acls);
DEF_TPG_ATTRIB(शेष_cmdsn_depth);
DEF_TPG_ATTRIB(cache_dynamic_acls);
DEF_TPG_ATTRIB(demo_mode_ग_लिखो_protect);
DEF_TPG_ATTRIB(prod_mode_ग_लिखो_protect);
DEF_TPG_ATTRIB(demo_mode_discovery);
DEF_TPG_ATTRIB(शेष_erl);
DEF_TPG_ATTRIB(t10_pi);
DEF_TPG_ATTRIB(fabric_prot_type);
DEF_TPG_ATTRIB(tpg_enabled_sendtarमाला_लो);
DEF_TPG_ATTRIB(login_keys_workaround);

अटल काष्ठा configfs_attribute *lio_target_tpg_attrib_attrs[] = अणु
	&iscsi_tpg_attrib_attr_authentication,
	&iscsi_tpg_attrib_attr_login_समयout,
	&iscsi_tpg_attrib_attr_netअगर_समयout,
	&iscsi_tpg_attrib_attr_generate_node_acls,
	&iscsi_tpg_attrib_attr_शेष_cmdsn_depth,
	&iscsi_tpg_attrib_attr_cache_dynamic_acls,
	&iscsi_tpg_attrib_attr_demo_mode_ग_लिखो_protect,
	&iscsi_tpg_attrib_attr_prod_mode_ग_लिखो_protect,
	&iscsi_tpg_attrib_attr_demo_mode_discovery,
	&iscsi_tpg_attrib_attr_शेष_erl,
	&iscsi_tpg_attrib_attr_t10_pi,
	&iscsi_tpg_attrib_attr_fabric_prot_type,
	&iscsi_tpg_attrib_attr_tpg_enabled_sendtarमाला_लो,
	&iscsi_tpg_attrib_attr_login_keys_workaround,
	शून्य,
पूर्ण;

/* End items क्रम lio_target_tpg_attrib_cit */

/* Start items क्रम lio_target_tpg_auth_cit */

#घोषणा __DEF_TPG_AUTH_STR(prefix, name, flags)					\
अटल sमाप_प्रकार __iscsi_##prefix##_##name##_show(काष्ठा se_portal_group *se_tpg,	\
		अक्षर *page)							\
अणु										\
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,			\
				काष्ठा iscsi_portal_group, tpg_se_tpg);		\
	काष्ठा iscsi_node_auth *auth = &tpg->tpg_demo_auth;			\
										\
	अगर (!capable(CAP_SYS_ADMIN))						\
		वापस -EPERM;							\
										\
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", auth->name);			\
पूर्ण										\
										\
अटल sमाप_प्रकार __iscsi_##prefix##_##name##_store(काष्ठा se_portal_group *se_tpg,\
		स्थिर अक्षर *page, माप_प्रकार count)					\
अणु										\
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,			\
				काष्ठा iscsi_portal_group, tpg_se_tpg);		\
	काष्ठा iscsi_node_auth *auth = &tpg->tpg_demo_auth;			\
										\
	अगर (!capable(CAP_SYS_ADMIN))						\
		वापस -EPERM;							\
										\
	snम_लिखो(auth->name, माप(auth->name), "%s", page);			\
	अगर (!(म_भेदन("NULL", auth->name, 4)))					\
		auth->naf_flags &= ~flags;					\
	अन्यथा									\
		auth->naf_flags |= flags;					\
										\
	अगर ((auth->naf_flags & NAF_USERID_IN_SET) &&				\
	    (auth->naf_flags & NAF_PASSWORD_IN_SET))				\
		auth->authenticate_target = 1;					\
	अन्यथा									\
		auth->authenticate_target = 0;					\
										\
	वापस count;								\
पूर्ण

#घोषणा DEF_TPG_AUTH_STR(name, flags)						\
	__DEF_TPG_AUTH_STR(tpg_auth, name, flags)				\
अटल sमाप_प्रकार iscsi_tpg_auth_##name##_show(काष्ठा config_item *item,		\
		अक्षर *page)							\
अणु										\
	वापस __iscsi_tpg_auth_##name##_show(auth_to_tpg(item), page);		\
पूर्ण										\
										\
अटल sमाप_प्रकार iscsi_tpg_auth_##name##_store(काष्ठा config_item *item,		\
		स्थिर अक्षर *page, माप_प्रकार count)					\
अणु										\
	वापस __iscsi_tpg_auth_##name##_store(auth_to_tpg(item), page, count);	\
पूर्ण										\
										\
CONFIGFS_ATTR(iscsi_tpg_auth_, name);


DEF_TPG_AUTH_STR(userid, NAF_USERID_SET);
DEF_TPG_AUTH_STR(password, NAF_PASSWORD_SET);
DEF_TPG_AUTH_STR(userid_mutual, NAF_USERID_IN_SET);
DEF_TPG_AUTH_STR(password_mutual, NAF_PASSWORD_IN_SET);

#घोषणा __DEF_TPG_AUTH_INT(prefix, name)					\
अटल sमाप_प्रकार __iscsi_##prefix##_##name##_show(काष्ठा se_portal_group *se_tpg,	\
		अक्षर *page)								\
अणु										\
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,			\
				काष्ठा iscsi_portal_group, tpg_se_tpg);		\
	काष्ठा iscsi_node_auth *auth = &tpg->tpg_demo_auth;			\
										\
	अगर (!capable(CAP_SYS_ADMIN))						\
		वापस -EPERM;							\
										\
	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", auth->name);			\
पूर्ण

#घोषणा DEF_TPG_AUTH_INT(name)							\
	__DEF_TPG_AUTH_INT(tpg_auth, name)					\
अटल sमाप_प्रकार iscsi_tpg_auth_##name##_show(काष्ठा config_item *item,		\
		अक्षर *page) \
अणु										\
	वापस __iscsi_tpg_auth_##name##_show(auth_to_tpg(item), page);		\
पूर्ण										\
CONFIGFS_ATTR_RO(iscsi_tpg_auth_, name);

DEF_TPG_AUTH_INT(authenticate_target);

अटल काष्ठा configfs_attribute *lio_target_tpg_auth_attrs[] = अणु
	&iscsi_tpg_auth_attr_userid,
	&iscsi_tpg_auth_attr_password,
	&iscsi_tpg_auth_attr_authenticate_target,
	&iscsi_tpg_auth_attr_userid_mutual,
	&iscsi_tpg_auth_attr_password_mutual,
	शून्य,
पूर्ण;

/* End items क्रम lio_target_tpg_auth_cit */

/* Start items क्रम lio_target_tpg_param_cit */

#घोषणा DEF_TPG_PARAM(name)						\
अटल sमाप_प्रकार iscsi_tpg_param_##name##_show(काष्ठा config_item *item,	\
		अक्षर *page)						\
अणु									\
	काष्ठा se_portal_group *se_tpg = param_to_tpg(item);		\
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,		\
			काष्ठा iscsi_portal_group, tpg_se_tpg);		\
	काष्ठा iscsi_param *param;					\
	sमाप_प्रकार rb;							\
									\
	अगर (iscsit_get_tpg(tpg) < 0)					\
		वापस -EINVAL;						\
									\
	param = iscsi_find_param_from_key(__stringअगरy(name),		\
				tpg->param_list);			\
	अगर (!param) अणु							\
		iscsit_put_tpg(tpg);					\
		वापस -EINVAL;						\
	पूर्ण								\
	rb = snम_लिखो(page, PAGE_SIZE, "%s\n", param->value);		\
									\
	iscsit_put_tpg(tpg);						\
	वापस rb;							\
पूर्ण									\
अटल sमाप_प्रकार iscsi_tpg_param_##name##_store(काष्ठा config_item *item, \
		स्थिर अक्षर *page, माप_प्रकार count)				\
अणु									\
	काष्ठा se_portal_group *se_tpg = param_to_tpg(item);		\
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,		\
			काष्ठा iscsi_portal_group, tpg_se_tpg);		\
	अक्षर *buf;							\
	पूर्णांक ret, len;							\
									\
	buf = kzalloc(PAGE_SIZE, GFP_KERNEL);				\
	अगर (!buf)							\
		वापस -ENOMEM;						\
	len = snम_लिखो(buf, PAGE_SIZE, "%s=%s", __stringअगरy(name), page);	\
	अगर (है_खाली(buf[len-1]))					\
		buf[len-1] = '\0'; /* Kill newline */			\
									\
	अगर (iscsit_get_tpg(tpg) < 0) अणु					\
		kमुक्त(buf);						\
		वापस -EINVAL;						\
	पूर्ण								\
									\
	ret = iscsi_change_param_value(buf, tpg->param_list, 1);	\
	अगर (ret < 0)							\
		जाओ out;						\
									\
	kमुक्त(buf);							\
	iscsit_put_tpg(tpg);						\
	वापस count;							\
out:									\
	kमुक्त(buf);							\
	iscsit_put_tpg(tpg);						\
	वापस -EINVAL;							\
पूर्ण									\
CONFIGFS_ATTR(iscsi_tpg_param_, name)

DEF_TPG_PARAM(AuthMethod);
DEF_TPG_PARAM(HeaderDigest);
DEF_TPG_PARAM(DataDigest);
DEF_TPG_PARAM(MaxConnections);
DEF_TPG_PARAM(TargetAlias);
DEF_TPG_PARAM(InitialR2T);
DEF_TPG_PARAM(ImmediateData);
DEF_TPG_PARAM(MaxRecvDataSegmentLength);
DEF_TPG_PARAM(MaxXmitDataSegmentLength);
DEF_TPG_PARAM(MaxBurstLength);
DEF_TPG_PARAM(FirstBurstLength);
DEF_TPG_PARAM(DefaultTime2Wait);
DEF_TPG_PARAM(DefaultTime2Retain);
DEF_TPG_PARAM(MaxOutstandingR2T);
DEF_TPG_PARAM(DataPDUInOrder);
DEF_TPG_PARAM(DataSequenceInOrder);
DEF_TPG_PARAM(ErrorRecoveryLevel);
DEF_TPG_PARAM(IFMarker);
DEF_TPG_PARAM(OFMarker);
DEF_TPG_PARAM(IFMarkInt);
DEF_TPG_PARAM(OFMarkInt);

अटल काष्ठा configfs_attribute *lio_target_tpg_param_attrs[] = अणु
	&iscsi_tpg_param_attr_AuthMethod,
	&iscsi_tpg_param_attr_HeaderDigest,
	&iscsi_tpg_param_attr_DataDigest,
	&iscsi_tpg_param_attr_MaxConnections,
	&iscsi_tpg_param_attr_TargetAlias,
	&iscsi_tpg_param_attr_InitialR2T,
	&iscsi_tpg_param_attr_ImmediateData,
	&iscsi_tpg_param_attr_MaxRecvDataSegmentLength,
	&iscsi_tpg_param_attr_MaxXmitDataSegmentLength,
	&iscsi_tpg_param_attr_MaxBurstLength,
	&iscsi_tpg_param_attr_FirstBurstLength,
	&iscsi_tpg_param_attr_DefaultTime2Wait,
	&iscsi_tpg_param_attr_DefaultTime2Retain,
	&iscsi_tpg_param_attr_MaxOutstandingR2T,
	&iscsi_tpg_param_attr_DataPDUInOrder,
	&iscsi_tpg_param_attr_DataSequenceInOrder,
	&iscsi_tpg_param_attr_ErrorRecoveryLevel,
	&iscsi_tpg_param_attr_IFMarker,
	&iscsi_tpg_param_attr_OFMarker,
	&iscsi_tpg_param_attr_IFMarkInt,
	&iscsi_tpg_param_attr_OFMarkInt,
	शून्य,
पूर्ण;

/* End items क्रम lio_target_tpg_param_cit */

/* Start items क्रम lio_target_tpg_cit */

अटल sमाप_प्रकार lio_target_tpg_enable_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,
			काष्ठा iscsi_portal_group, tpg_se_tpg);
	sमाप_प्रकार len;

	spin_lock(&tpg->tpg_state_lock);
	len = प्र_लिखो(page, "%d\n",
			(tpg->tpg_state == TPG_STATE_ACTIVE) ? 1 : 0);
	spin_unlock(&tpg->tpg_state_lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार lio_target_tpg_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,
			काष्ठा iscsi_portal_group, tpg_se_tpg);
	u32 op;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &op);
	अगर (ret)
		वापस ret;
	अगर ((op != 1) && (op != 0)) अणु
		pr_err("Illegal value for tpg_enable: %u\n", op);
		वापस -EINVAL;
	पूर्ण

	ret = iscsit_get_tpg(tpg);
	अगर (ret < 0)
		वापस -EINVAL;

	अगर (op) अणु
		ret = iscsit_tpg_enable_portal_group(tpg);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		/*
		 * iscsit_tpg_disable_portal_group() assumes क्रमce=1
		 */
		ret = iscsit_tpg_disable_portal_group(tpg, 1);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	iscsit_put_tpg(tpg);
	वापस count;
out:
	iscsit_put_tpg(tpg);
	वापस -EINVAL;
पूर्ण


अटल sमाप_प्रकार lio_target_tpg_dynamic_sessions_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस target_show_dynamic_sessions(to_tpg(item), page);
पूर्ण

CONFIGFS_ATTR(lio_target_tpg_, enable);
CONFIGFS_ATTR_RO(lio_target_tpg_, dynamic_sessions);

अटल काष्ठा configfs_attribute *lio_target_tpg_attrs[] = अणु
	&lio_target_tpg_attr_enable,
	&lio_target_tpg_attr_dynamic_sessions,
	शून्य,
पूर्ण;

/* End items क्रम lio_target_tpg_cit */

/* Start items क्रम lio_target_tiqn_cit */

अटल काष्ठा se_portal_group *lio_target_tiqn_addtpg(काष्ठा se_wwn *wwn,
						      स्थिर अक्षर *name)
अणु
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tiqn *tiqn;
	अक्षर *tpgt_str;
	पूर्णांक ret;
	u16 tpgt;

	tiqn = container_of(wwn, काष्ठा iscsi_tiqn, tiqn_wwn);
	/*
	 * Only tpgt_# directory groups can be created below
	 * target/iscsi/iqn.superturodiskarry/
	 */
	tpgt_str = म_माला(name, "tpgt_");
	अगर (!tpgt_str) अणु
		pr_err("Unable to locate \"tpgt_#\" directory"
				" group\n");
		वापस शून्य;
	पूर्ण
	tpgt_str += 5; /* Skip ahead of "tpgt_" */
	ret = kstrtou16(tpgt_str, 0, &tpgt);
	अगर (ret)
		वापस शून्य;

	tpg = iscsit_alloc_portal_group(tiqn, tpgt);
	अगर (!tpg)
		वापस शून्य;

	ret = core_tpg_रेजिस्टर(wwn, &tpg->tpg_se_tpg, SCSI_PROTOCOL_ISCSI);
	अगर (ret < 0)
		जाओ मुक्त_out;

	ret = iscsit_tpg_add_portal_group(tiqn, tpg);
	अगर (ret != 0)
		जाओ out;

	pr_debug("LIO_Target_ConfigFS: REGISTER -> %s\n", tiqn->tiqn);
	pr_debug("LIO_Target_ConfigFS: REGISTER -> Allocated TPG: %s\n",
			name);
	वापस &tpg->tpg_se_tpg;
out:
	core_tpg_deरेजिस्टर(&tpg->tpg_se_tpg);
मुक्त_out:
	kमुक्त(tpg);
	वापस शून्य;
पूर्ण

अटल व्योम lio_target_tiqn_deltpg(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tiqn *tiqn;

	tpg = container_of(se_tpg, काष्ठा iscsi_portal_group, tpg_se_tpg);
	tiqn = tpg->tpg_tiqn;
	/*
	 * iscsit_tpg_del_portal_group() assumes क्रमce=1
	 */
	pr_debug("LIO_Target_ConfigFS: DEREGISTER -> Releasing TPG\n");
	iscsit_tpg_del_portal_group(tiqn, tpg, 1);
पूर्ण

/* End items क्रम lio_target_tiqn_cit */

/* Start LIO-Target TIQN काष्ठा contig_item lio_target_cit */

अटल sमाप_प्रकार lio_target_wwn_lio_version_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "Datera Inc. iSCSI Target "ISCSIT_VERSION"\n");
पूर्ण

CONFIGFS_ATTR_RO(lio_target_wwn_, lio_version);

अटल काष्ठा configfs_attribute *lio_target_wwn_attrs[] = अणु
	&lio_target_wwn_attr_lio_version,
	शून्य,
पूर्ण;

अटल काष्ठा se_wwn *lio_target_call_coपढ़ोdtiqn(
	काष्ठा target_fabric_configfs *tf,
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा iscsi_tiqn *tiqn;

	tiqn = iscsit_add_tiqn((अचिन्हित अक्षर *)name);
	अगर (IS_ERR(tiqn))
		वापस ERR_CAST(tiqn);

	pr_debug("LIO_Target_ConfigFS: REGISTER -> %s\n", tiqn->tiqn);
	pr_debug("LIO_Target_ConfigFS: REGISTER -> Allocated Node:"
			" %s\n", name);
	वापस &tiqn->tiqn_wwn;
पूर्ण

अटल व्योम lio_target_add_wwn_groups(काष्ठा se_wwn *wwn)
अणु
	काष्ठा iscsi_tiqn *tiqn = container_of(wwn, काष्ठा iscsi_tiqn, tiqn_wwn);

	config_group_init_type_name(&tiqn->tiqn_stat_grps.iscsi_instance_group,
			"iscsi_instance", &iscsi_stat_instance_cit);
	configfs_add_शेष_group(&tiqn->tiqn_stat_grps.iscsi_instance_group,
			&tiqn->tiqn_wwn.fabric_stat_group);

	config_group_init_type_name(&tiqn->tiqn_stat_grps.iscsi_sess_err_group,
			"iscsi_sess_err", &iscsi_stat_sess_err_cit);
	configfs_add_शेष_group(&tiqn->tiqn_stat_grps.iscsi_sess_err_group,
			&tiqn->tiqn_wwn.fabric_stat_group);

	config_group_init_type_name(&tiqn->tiqn_stat_grps.iscsi_tgt_attr_group,
			"iscsi_tgt_attr", &iscsi_stat_tgt_attr_cit);
	configfs_add_शेष_group(&tiqn->tiqn_stat_grps.iscsi_tgt_attr_group,
			&tiqn->tiqn_wwn.fabric_stat_group);

	config_group_init_type_name(&tiqn->tiqn_stat_grps.iscsi_login_stats_group,
			"iscsi_login_stats", &iscsi_stat_login_cit);
	configfs_add_शेष_group(&tiqn->tiqn_stat_grps.iscsi_login_stats_group,
			&tiqn->tiqn_wwn.fabric_stat_group);

	config_group_init_type_name(&tiqn->tiqn_stat_grps.iscsi_logout_stats_group,
			"iscsi_logout_stats", &iscsi_stat_logout_cit);
	configfs_add_शेष_group(&tiqn->tiqn_stat_grps.iscsi_logout_stats_group,
			&tiqn->tiqn_wwn.fabric_stat_group);
पूर्ण

अटल व्योम lio_target_call_coredeltiqn(
	काष्ठा se_wwn *wwn)
अणु
	काष्ठा iscsi_tiqn *tiqn = container_of(wwn, काष्ठा iscsi_tiqn, tiqn_wwn);

	pr_debug("LIO_Target_ConfigFS: DEREGISTER -> %s\n",
			tiqn->tiqn);
	iscsit_del_tiqn(tiqn);
पूर्ण

/* End LIO-Target TIQN काष्ठा contig_lio_target_cit */

/* Start lio_target_discovery_auth_cit */

#घोषणा DEF_DISC_AUTH_STR(name, flags)					\
	__DEF_NACL_AUTH_STR(disc, name, flags)				\
अटल sमाप_प्रकार iscsi_disc_##name##_show(काष्ठा config_item *item, अक्षर *page) \
अणु									\
	वापस __iscsi_disc_##name##_show(&iscsit_global->discovery_acl,\
		page);							\
पूर्ण									\
अटल sमाप_प्रकार iscsi_disc_##name##_store(काष्ठा config_item *item,	\
		स्थिर अक्षर *page, माप_प्रकार count)				\
अणु									\
	वापस __iscsi_disc_##name##_store(&iscsit_global->discovery_acl,	\
		page, count);						\
									\
पूर्ण									\
CONFIGFS_ATTR(iscsi_disc_, name)

DEF_DISC_AUTH_STR(userid, NAF_USERID_SET);
DEF_DISC_AUTH_STR(password, NAF_PASSWORD_SET);
DEF_DISC_AUTH_STR(userid_mutual, NAF_USERID_IN_SET);
DEF_DISC_AUTH_STR(password_mutual, NAF_PASSWORD_IN_SET);

#घोषणा DEF_DISC_AUTH_INT(name)						\
	__DEF_NACL_AUTH_INT(disc, name)					\
अटल sमाप_प्रकार iscsi_disc_##name##_show(काष्ठा config_item *item, अक्षर *page) \
अणु									\
	वापस __iscsi_disc_##name##_show(&iscsit_global->discovery_acl, \
			page);						\
पूर्ण									\
CONFIGFS_ATTR_RO(iscsi_disc_, name)

DEF_DISC_AUTH_INT(authenticate_target);


अटल sमाप_प्रकार iscsi_disc_enक्रमce_discovery_auth_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_node_auth *discovery_auth = &iscsit_global->discovery_acl.node_auth;

	वापस प्र_लिखो(page, "%d\n", discovery_auth->enक्रमce_discovery_auth);
पूर्ण

अटल sमाप_प्रकार iscsi_disc_enक्रमce_discovery_auth_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा iscsi_param *param;
	काष्ठा iscsi_portal_group *discovery_tpg = iscsit_global->discovery_tpg;
	u32 op;
	पूर्णांक err;

	err = kstrtou32(page, 0, &op);
	अगर (err)
		वापस -EINVAL;
	अगर ((op != 1) && (op != 0)) अणु
		pr_err("Illegal value for enforce_discovery_auth:"
				" %u\n", op);
		वापस -EINVAL;
	पूर्ण

	अगर (!discovery_tpg) अणु
		pr_err("iscsit_global->discovery_tpg is NULL\n");
		वापस -EINVAL;
	पूर्ण

	param = iscsi_find_param_from_key(AUTHMETHOD,
				discovery_tpg->param_list);
	अगर (!param)
		वापस -EINVAL;

	अगर (op) अणु
		/*
		 * Reset the AuthMethod key to CHAP.
		 */
		अगर (iscsi_update_param_value(param, CHAP) < 0)
			वापस -EINVAL;

		discovery_tpg->tpg_attrib.authentication = 1;
		iscsit_global->discovery_acl.node_auth.enक्रमce_discovery_auth = 1;
		pr_debug("LIO-CORE[0] Successfully enabled"
			" authentication enforcement for iSCSI"
			" Discovery TPG\n");
	पूर्ण अन्यथा अणु
		/*
		 * Reset the AuthMethod key to CHAP,None
		 */
		अगर (iscsi_update_param_value(param, "CHAP,None") < 0)
			वापस -EINVAL;

		discovery_tpg->tpg_attrib.authentication = 0;
		iscsit_global->discovery_acl.node_auth.enक्रमce_discovery_auth = 0;
		pr_debug("LIO-CORE[0] Successfully disabled"
			" authentication enforcement for iSCSI"
			" Discovery TPG\n");
	पूर्ण

	वापस count;
पूर्ण

CONFIGFS_ATTR(iscsi_disc_, enक्रमce_discovery_auth);

अटल काष्ठा configfs_attribute *lio_target_discovery_auth_attrs[] = अणु
	&iscsi_disc_attr_userid,
	&iscsi_disc_attr_password,
	&iscsi_disc_attr_authenticate_target,
	&iscsi_disc_attr_userid_mutual,
	&iscsi_disc_attr_password_mutual,
	&iscsi_disc_attr_enक्रमce_discovery_auth,
	शून्य,
पूर्ण;

/* End lio_target_discovery_auth_cit */

/* Start functions क्रम target_core_fabric_ops */

अटल पूर्णांक iscsi_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा iscsi_cmd *cmd = container_of(se_cmd, काष्ठा iscsi_cmd, se_cmd);

	वापस cmd->i_state;
पूर्ण

अटल u32 lio_sess_get_index(काष्ठा se_session *se_sess)
अणु
	काष्ठा iscsi_session *sess = se_sess->fabric_sess_ptr;

	वापस sess->session_index;
पूर्ण

अटल u32 lio_sess_get_initiator_sid(
	काष्ठा se_session *se_sess,
	अचिन्हित अक्षर *buf,
	u32 size)
अणु
	काष्ठा iscsi_session *sess = se_sess->fabric_sess_ptr;
	/*
	 * iSCSI Initiator Session Identअगरier from RFC-3720.
	 */
	वापस snम_लिखो(buf, size, "%6phN", sess->isid);
पूर्ण

अटल पूर्णांक lio_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा iscsi_cmd *cmd = container_of(se_cmd, काष्ठा iscsi_cmd, se_cmd);
	काष्ठा iscsi_conn *conn = cmd->conn;

	cmd->i_state = ISTATE_SEND_DATAIN;
	वापस conn->conn_transport->iscsit_queue_data_in(conn, cmd);
पूर्ण

अटल पूर्णांक lio_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा iscsi_cmd *cmd = container_of(se_cmd, काष्ठा iscsi_cmd, se_cmd);
	काष्ठा iscsi_conn *conn = cmd->conn;

	अगर (!cmd->immediate_data && !cmd->unsolicited_data)
		वापस conn->conn_transport->iscsit_get_dataout(conn, cmd, false);

	वापस 0;
पूर्ण

अटल पूर्णांक lio_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा iscsi_cmd *cmd = container_of(se_cmd, काष्ठा iscsi_cmd, se_cmd);
	काष्ठा iscsi_conn *conn = cmd->conn;

	cmd->i_state = ISTATE_SEND_STATUS;

	अगर (cmd->se_cmd.scsi_status || cmd->sense_reason) अणु
		वापस iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	पूर्ण
	वापस conn->conn_transport->iscsit_queue_status(conn, cmd);
पूर्ण

अटल व्योम lio_queue_पंचांग_rsp(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा iscsi_cmd *cmd = container_of(se_cmd, काष्ठा iscsi_cmd, se_cmd);

	cmd->i_state = ISTATE_SEND_TASKMGTRSP;
	iscsit_add_cmd_to_response_queue(cmd, cmd->conn, cmd->i_state);
पूर्ण

अटल व्योम lio_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा iscsi_cmd *cmd = container_of(se_cmd, काष्ठा iscsi_cmd, se_cmd);

	cmd->conn->conn_transport->iscsit_पातed_task(cmd->conn, cmd);
पूर्ण

अटल अंतरभूत काष्ठा iscsi_portal_group *iscsi_tpg(काष्ठा se_portal_group *se_tpg)
अणु
	वापस container_of(se_tpg, काष्ठा iscsi_portal_group, tpg_se_tpg);
पूर्ण

अटल अक्षर *lio_tpg_get_endpoपूर्णांक_wwn(काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpg_tiqn->tiqn;
पूर्ण

अटल u16 lio_tpg_get_tag(काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpgt;
पूर्ण

अटल u32 lio_tpg_get_शेष_depth(काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpg_attrib.शेष_cmdsn_depth;
पूर्ण

अटल पूर्णांक lio_tpg_check_demo_mode(काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpg_attrib.generate_node_acls;
पूर्ण

अटल पूर्णांक lio_tpg_check_demo_mode_cache(काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpg_attrib.cache_dynamic_acls;
पूर्ण

अटल पूर्णांक lio_tpg_check_demo_mode_ग_लिखो_protect(
	काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpg_attrib.demo_mode_ग_लिखो_protect;
पूर्ण

अटल पूर्णांक lio_tpg_check_prod_mode_ग_लिखो_protect(
	काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpg_attrib.prod_mode_ग_लिखो_protect;
पूर्ण

अटल पूर्णांक lio_tpg_check_prot_fabric_only(
	काष्ठा se_portal_group *se_tpg)
अणु
	/*
	 * Only report fabric_prot_type अगर t10_pi has also been enabled
	 * क्रम incoming ib_isert sessions.
	 */
	अगर (!iscsi_tpg(se_tpg)->tpg_attrib.t10_pi)
		वापस 0;
	वापस iscsi_tpg(se_tpg)->tpg_attrib.fabric_prot_type;
पूर्ण

/*
 * This function calls iscsit_inc_session_usage_count() on the
 * काष्ठा iscsi_session in question.
 */
अटल व्योम lio_tpg_बंद_session(काष्ठा se_session *se_sess)
अणु
	काष्ठा iscsi_session *sess = se_sess->fabric_sess_ptr;
	काष्ठा se_portal_group *se_tpg = &sess->tpg->tpg_se_tpg;

	spin_lock_bh(&se_tpg->session_lock);
	spin_lock(&sess->conn_lock);
	अगर (atomic_पढ़ो(&sess->session_fall_back_to_erl0) ||
	    atomic_पढ़ो(&sess->session_logout) ||
	    atomic_पढ़ो(&sess->session_बंद) ||
	    (sess->समय2retain_समयr_flags & ISCSI_TF_EXPIRED)) अणु
		spin_unlock(&sess->conn_lock);
		spin_unlock_bh(&se_tpg->session_lock);
		वापस;
	पूर्ण
	iscsit_inc_session_usage_count(sess);
	atomic_set(&sess->session_reinstatement, 1);
	atomic_set(&sess->session_fall_back_to_erl0, 1);
	atomic_set(&sess->session_बंद, 1);
	spin_unlock(&sess->conn_lock);

	iscsit_stop_समय2retain_समयr(sess);
	spin_unlock_bh(&se_tpg->session_lock);

	iscsit_stop_session(sess, 1, 1);
	iscsit_dec_session_usage_count(sess);
पूर्ण

अटल u32 lio_tpg_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस iscsi_tpg(se_tpg)->tpg_tiqn->tiqn_index;
पूर्ण

अटल व्योम lio_set_शेष_node_attributes(काष्ठा se_node_acl *se_acl)
अणु
	काष्ठा iscsi_node_acl *acl = container_of(se_acl, काष्ठा iscsi_node_acl,
				se_node_acl);
	काष्ठा se_portal_group *se_tpg = se_acl->se_tpg;
	काष्ठा iscsi_portal_group *tpg = container_of(se_tpg,
				काष्ठा iscsi_portal_group, tpg_se_tpg);

	acl->node_attrib.nacl = acl;
	iscsit_set_शेष_node_attribues(acl, tpg);
पूर्ण

अटल पूर्णांक lio_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	वापस target_put_sess_cmd(se_cmd);
पूर्ण

अटल व्योम lio_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा iscsi_cmd *cmd = container_of(se_cmd, काष्ठा iscsi_cmd, se_cmd);

	pr_debug("Entering lio_release_cmd for se_cmd: %p\n", se_cmd);
	iscsit_release_cmd(cmd);
पूर्ण

स्थिर काष्ठा target_core_fabric_ops iscsi_ops = अणु
	.module				= THIS_MODULE,
	.fabric_alias			= "iscsi",
	.fabric_name			= "iSCSI",
	.node_acl_size			= माप(काष्ठा iscsi_node_acl),
	.tpg_get_wwn			= lio_tpg_get_endpoपूर्णांक_wwn,
	.tpg_get_tag			= lio_tpg_get_tag,
	.tpg_get_शेष_depth		= lio_tpg_get_शेष_depth,
	.tpg_check_demo_mode		= lio_tpg_check_demo_mode,
	.tpg_check_demo_mode_cache	= lio_tpg_check_demo_mode_cache,
	.tpg_check_demo_mode_ग_लिखो_protect =
			lio_tpg_check_demo_mode_ग_लिखो_protect,
	.tpg_check_prod_mode_ग_लिखो_protect =
			lio_tpg_check_prod_mode_ग_लिखो_protect,
	.tpg_check_prot_fabric_only	= &lio_tpg_check_prot_fabric_only,
	.tpg_get_inst_index		= lio_tpg_get_inst_index,
	.check_stop_मुक्त		= lio_check_stop_मुक्त,
	.release_cmd			= lio_release_cmd,
	.बंद_session			= lio_tpg_बंद_session,
	.sess_get_index			= lio_sess_get_index,
	.sess_get_initiator_sid		= lio_sess_get_initiator_sid,
	.ग_लिखो_pending			= lio_ग_लिखो_pending,
	.set_शेष_node_attributes	= lio_set_शेष_node_attributes,
	.get_cmd_state			= iscsi_get_cmd_state,
	.queue_data_in			= lio_queue_data_in,
	.queue_status			= lio_queue_status,
	.queue_पंचांग_rsp			= lio_queue_पंचांग_rsp,
	.पातed_task			= lio_पातed_task,
	.fabric_make_wwn		= lio_target_call_coपढ़ोdtiqn,
	.fabric_drop_wwn		= lio_target_call_coredeltiqn,
	.add_wwn_groups			= lio_target_add_wwn_groups,
	.fabric_make_tpg		= lio_target_tiqn_addtpg,
	.fabric_drop_tpg		= lio_target_tiqn_deltpg,
	.fabric_make_np			= lio_target_call_addnptotpg,
	.fabric_drop_np			= lio_target_call_delnpfromtpg,
	.fabric_init_nodeacl		= lio_target_init_nodeacl,

	.tfc_discovery_attrs		= lio_target_discovery_auth_attrs,
	.tfc_wwn_attrs			= lio_target_wwn_attrs,
	.tfc_tpg_base_attrs		= lio_target_tpg_attrs,
	.tfc_tpg_attrib_attrs		= lio_target_tpg_attrib_attrs,
	.tfc_tpg_auth_attrs		= lio_target_tpg_auth_attrs,
	.tfc_tpg_param_attrs		= lio_target_tpg_param_attrs,
	.tfc_tpg_np_base_attrs		= lio_target_portal_attrs,
	.tfc_tpg_nacl_base_attrs	= lio_target_initiator_attrs,
	.tfc_tpg_nacl_attrib_attrs	= lio_target_nacl_attrib_attrs,
	.tfc_tpg_nacl_auth_attrs	= lio_target_nacl_auth_attrs,
	.tfc_tpg_nacl_param_attrs	= lio_target_nacl_param_attrs,

	.ग_लिखो_pending_must_be_called	= true,
पूर्ण;
