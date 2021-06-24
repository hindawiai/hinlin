<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Modern ConfigFS group context specअगरic iSCSI statistics based on original
 * iscsi_target_mib.c code
 *
 * Copyright (c) 2011-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/configfs.h>
#समावेश <linux/export.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_parameters.h"
#समावेश "iscsi_target_device.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश <target/iscsi/iscsi_target_स्थिति.स>

#अगर_अघोषित INITIAL_JIFFIES
#घोषणा INITIAL_JIFFIES ((अचिन्हित दीर्घ)(अचिन्हित पूर्णांक) (-300*HZ))
#पूर्ण_अगर

/* Instance Attributes Table */
#घोषणा ISCSI_INST_NUM_NODES		1
#घोषणा ISCSI_INST_DESCR		"Storage Engine Target"
#घोषणा ISCSI_DISCONTINUITY_TIME	0

#घोषणा ISCSI_NODE_INDEX		1

#घोषणा ISPRINT(a)   ((a >= ' ') && (a <= '~'))

/****************************************************************************
 * iSCSI MIB Tables
 ****************************************************************************/
/*
 * Instance Attributes Table
 */
अटल काष्ठा iscsi_tiqn *iscsi_instance_tiqn(काष्ठा config_item *item)
अणु
	काष्ठा iscsi_wwn_stat_grps *igrps = container_of(to_config_group(item),
			काष्ठा iscsi_wwn_stat_grps, iscsi_instance_group);
	वापस container_of(igrps, काष्ठा iscsi_tiqn, tiqn_stat_grps);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_inst_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
			iscsi_instance_tiqn(item)->tiqn_index);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_min_ver_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", ISCSI_DRAFT20_VERSION);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_max_ver_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", ISCSI_DRAFT20_VERSION);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_portals_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
			iscsi_instance_tiqn(item)->tiqn_num_tpg_nps);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_nodes_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", ISCSI_INST_NUM_NODES);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_sessions_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
		iscsi_instance_tiqn(item)->tiqn_nsessions);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_fail_sess_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_instance_tiqn(item);
	काष्ठा iscsi_sess_err_stats *sess_err = &tiqn->sess_err_stats;
	u32 sess_err_count;

	spin_lock_bh(&sess_err->lock);
	sess_err_count = (sess_err->digest_errors +
			  sess_err->cxn_समयout_errors +
			  sess_err->pdu_क्रमmat_errors);
	spin_unlock_bh(&sess_err->lock);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", sess_err_count);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_fail_type_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_instance_tiqn(item);
	काष्ठा iscsi_sess_err_stats *sess_err = &tiqn->sess_err_stats;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
			sess_err->last_sess_failure_type);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_fail_rem_name_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_instance_tiqn(item);
	काष्ठा iscsi_sess_err_stats *sess_err = &tiqn->sess_err_stats;

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n",
			sess_err->last_sess_fail_rem_name[0] ?
			sess_err->last_sess_fail_rem_name : NONE);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_disc_समय_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", ISCSI_DISCONTINUITY_TIME);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_description_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", ISCSI_INST_DESCR);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_venकरोr_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "Datera, Inc. iSCSI-Target\n");
पूर्ण

अटल sमाप_प्रकार iscsi_stat_instance_version_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", ISCSIT_VERSION);
पूर्ण

CONFIGFS_ATTR_RO(iscsi_stat_instance_, inst);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, min_ver);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, max_ver);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, portals);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, nodes);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, sessions);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, fail_sess);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, fail_type);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, fail_rem_name);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, disc_समय);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, description);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, venकरोr);
CONFIGFS_ATTR_RO(iscsi_stat_instance_, version);

अटल काष्ठा configfs_attribute *iscsi_stat_instance_attrs[] = अणु
	&iscsi_stat_instance_attr_inst,
	&iscsi_stat_instance_attr_min_ver,
	&iscsi_stat_instance_attr_max_ver,
	&iscsi_stat_instance_attr_portals,
	&iscsi_stat_instance_attr_nodes,
	&iscsi_stat_instance_attr_sessions,
	&iscsi_stat_instance_attr_fail_sess,
	&iscsi_stat_instance_attr_fail_type,
	&iscsi_stat_instance_attr_fail_rem_name,
	&iscsi_stat_instance_attr_disc_समय,
	&iscsi_stat_instance_attr_description,
	&iscsi_stat_instance_attr_venकरोr,
	&iscsi_stat_instance_attr_version,
	शून्य,
पूर्ण;

स्थिर काष्ठा config_item_type iscsi_stat_instance_cit = अणु
	.ct_attrs		= iscsi_stat_instance_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Instance Session Failure Stats Table
 */
अटल काष्ठा iscsi_tiqn *iscsi_sess_err_tiqn(काष्ठा config_item *item)
अणु
	काष्ठा iscsi_wwn_stat_grps *igrps = container_of(to_config_group(item),
			काष्ठा iscsi_wwn_stat_grps, iscsi_sess_err_group);
	वापस container_of(igrps, काष्ठा iscsi_tiqn, tiqn_stat_grps);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_err_inst_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
		iscsi_sess_err_tiqn(item)->tiqn_index);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_err_digest_errors_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_sess_err_tiqn(item);
	काष्ठा iscsi_sess_err_stats *sess_err = &tiqn->sess_err_stats;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", sess_err->digest_errors);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_err_cxn_errors_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_sess_err_tiqn(item);
	काष्ठा iscsi_sess_err_stats *sess_err = &tiqn->sess_err_stats;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", sess_err->cxn_समयout_errors);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_err_क्रमmat_errors_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_sess_err_tiqn(item);
	काष्ठा iscsi_sess_err_stats *sess_err = &tiqn->sess_err_stats;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", sess_err->pdu_क्रमmat_errors);
पूर्ण

CONFIGFS_ATTR_RO(iscsi_stat_sess_err_, inst);
CONFIGFS_ATTR_RO(iscsi_stat_sess_err_, digest_errors);
CONFIGFS_ATTR_RO(iscsi_stat_sess_err_, cxn_errors);
CONFIGFS_ATTR_RO(iscsi_stat_sess_err_, क्रमmat_errors);

अटल काष्ठा configfs_attribute *iscsi_stat_sess_err_attrs[] = अणु
	&iscsi_stat_sess_err_attr_inst,
	&iscsi_stat_sess_err_attr_digest_errors,
	&iscsi_stat_sess_err_attr_cxn_errors,
	&iscsi_stat_sess_err_attr_क्रमmat_errors,
	शून्य,
पूर्ण;

स्थिर काष्ठा config_item_type iscsi_stat_sess_err_cit = अणु
	.ct_attrs		= iscsi_stat_sess_err_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Target Attributes Table
 */
अटल काष्ठा iscsi_tiqn *iscsi_tgt_attr_tiqn(काष्ठा config_item *item)
अणु
	काष्ठा iscsi_wwn_stat_grps *igrps = container_of(to_config_group(item),
			काष्ठा iscsi_wwn_stat_grps, iscsi_tgt_attr_group);
	वापस container_of(igrps, काष्ठा iscsi_tiqn, tiqn_stat_grps);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_inst_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
			iscsi_tgt_attr_tiqn(item)->tiqn_index);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", ISCSI_NODE_INDEX);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_login_fails_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	u32 fail_count;

	spin_lock(&lstat->lock);
	fail_count = (lstat->redirects + lstat->authorize_fails +
			lstat->authenticate_fails + lstat->negotiate_fails +
			lstat->other_fails);
	spin_unlock(&lstat->lock);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", fail_count);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_last_fail_समय_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	u32 last_fail_समय;

	spin_lock(&lstat->lock);
	last_fail_समय = lstat->last_fail_समय ?
			(u32)(((u32)lstat->last_fail_समय -
				INITIAL_JIFFIES) * 100 / HZ) : 0;
	spin_unlock(&lstat->lock);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", last_fail_समय);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_last_fail_type_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	u32 last_fail_type;

	spin_lock(&lstat->lock);
	last_fail_type = lstat->last_fail_type;
	spin_unlock(&lstat->lock);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", last_fail_type);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_fail_पूर्णांकr_name_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	अचिन्हित अक्षर buf[ISCSI_IQN_LEN];

	spin_lock(&lstat->lock);
	snम_लिखो(buf, ISCSI_IQN_LEN, "%s", lstat->last_पूर्णांकr_fail_name[0] ?
				lstat->last_पूर्णांकr_fail_name : NONE);
	spin_unlock(&lstat->lock);

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", buf);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_fail_पूर्णांकr_addr_type_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	पूर्णांक ret;

	spin_lock(&lstat->lock);
	अगर (lstat->last_पूर्णांकr_fail_ip_family == AF_INET6)
		ret = snम_लिखो(page, PAGE_SIZE, "ipv6\n");
	अन्यथा
		ret = snम_लिखो(page, PAGE_SIZE, "ipv4\n");
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_tgt_attr_fail_पूर्णांकr_addr_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_tgt_attr_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	पूर्णांक ret;

	spin_lock(&lstat->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%pISc\n", &lstat->last_पूर्णांकr_fail_sockaddr);
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, inst);
CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, indx);
CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, login_fails);
CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, last_fail_समय);
CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, last_fail_type);
CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, fail_पूर्णांकr_name);
CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, fail_पूर्णांकr_addr_type);
CONFIGFS_ATTR_RO(iscsi_stat_tgt_attr_, fail_पूर्णांकr_addr);

अटल काष्ठा configfs_attribute *iscsi_stat_tgt_attr_attrs[] = अणु
	&iscsi_stat_tgt_attr_attr_inst,
	&iscsi_stat_tgt_attr_attr_indx,
	&iscsi_stat_tgt_attr_attr_login_fails,
	&iscsi_stat_tgt_attr_attr_last_fail_समय,
	&iscsi_stat_tgt_attr_attr_last_fail_type,
	&iscsi_stat_tgt_attr_attr_fail_पूर्णांकr_name,
	&iscsi_stat_tgt_attr_attr_fail_पूर्णांकr_addr_type,
	&iscsi_stat_tgt_attr_attr_fail_पूर्णांकr_addr,
	शून्य,
पूर्ण;

स्थिर काष्ठा config_item_type iscsi_stat_tgt_attr_cit = अणु
	.ct_attrs		= iscsi_stat_tgt_attr_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Target Login Stats Table
 */
अटल काष्ठा iscsi_tiqn *iscsi_login_stat_tiqn(काष्ठा config_item *item)
अणु
	काष्ठा iscsi_wwn_stat_grps *igrps = container_of(to_config_group(item),
			काष्ठा iscsi_wwn_stat_grps, iscsi_login_stats_group);
	वापस container_of(igrps, काष्ठा iscsi_tiqn, tiqn_stat_grps);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_inst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
		iscsi_login_stat_tiqn(item)->tiqn_index);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_indx_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", ISCSI_NODE_INDEX);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_accepts_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_login_stat_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	sमाप_प्रकार ret;

	spin_lock(&lstat->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lstat->accepts);
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_other_fails_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_login_stat_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	sमाप_प्रकार ret;

	spin_lock(&lstat->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lstat->other_fails);
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_redirects_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_login_stat_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	sमाप_प्रकार ret;

	spin_lock(&lstat->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lstat->redirects);
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_authorize_fails_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_login_stat_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	sमाप_प्रकार ret;

	spin_lock(&lstat->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lstat->authorize_fails);
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_authenticate_fails_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_login_stat_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	sमाप_प्रकार ret;

	spin_lock(&lstat->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lstat->authenticate_fails);
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_login_negotiate_fails_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_login_stat_tiqn(item);
	काष्ठा iscsi_login_stats *lstat = &tiqn->login_stats;
	sमाप_प्रकार ret;

	spin_lock(&lstat->lock);
	ret = snम_लिखो(page, PAGE_SIZE, "%u\n", lstat->negotiate_fails);
	spin_unlock(&lstat->lock);

	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(iscsi_stat_login_, inst);
CONFIGFS_ATTR_RO(iscsi_stat_login_, indx);
CONFIGFS_ATTR_RO(iscsi_stat_login_, accepts);
CONFIGFS_ATTR_RO(iscsi_stat_login_, other_fails);
CONFIGFS_ATTR_RO(iscsi_stat_login_, redirects);
CONFIGFS_ATTR_RO(iscsi_stat_login_, authorize_fails);
CONFIGFS_ATTR_RO(iscsi_stat_login_, authenticate_fails);
CONFIGFS_ATTR_RO(iscsi_stat_login_, negotiate_fails);

अटल काष्ठा configfs_attribute *iscsi_stat_login_stats_attrs[] = अणु
	&iscsi_stat_login_attr_inst,
	&iscsi_stat_login_attr_indx,
	&iscsi_stat_login_attr_accepts,
	&iscsi_stat_login_attr_other_fails,
	&iscsi_stat_login_attr_redirects,
	&iscsi_stat_login_attr_authorize_fails,
	&iscsi_stat_login_attr_authenticate_fails,
	&iscsi_stat_login_attr_negotiate_fails,
	शून्य,
पूर्ण;

स्थिर काष्ठा config_item_type iscsi_stat_login_cit = अणु
	.ct_attrs		= iscsi_stat_login_stats_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Target Logout Stats Table
 */
अटल काष्ठा iscsi_tiqn *iscsi_logout_stat_tiqn(काष्ठा config_item *item)
अणु
	काष्ठा iscsi_wwn_stat_grps *igrps = container_of(to_config_group(item),
			काष्ठा iscsi_wwn_stat_grps, iscsi_logout_stats_group);
	वापस container_of(igrps, काष्ठा iscsi_tiqn, tiqn_stat_grps);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_logout_inst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n",
		iscsi_logout_stat_tiqn(item)->tiqn_index);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_logout_indx_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", ISCSI_NODE_INDEX);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_logout_normal_logouts_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_logout_stat_tiqn(item);
	काष्ठा iscsi_logout_stats *lstats = &tiqn->logout_stats;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", lstats->normal_logouts);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_logout_abnormal_logouts_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_tiqn *tiqn = iscsi_logout_stat_tiqn(item);
	काष्ठा iscsi_logout_stats *lstats = &tiqn->logout_stats;

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", lstats->abnormal_logouts);
पूर्ण

CONFIGFS_ATTR_RO(iscsi_stat_logout_, inst);
CONFIGFS_ATTR_RO(iscsi_stat_logout_, indx);
CONFIGFS_ATTR_RO(iscsi_stat_logout_, normal_logouts);
CONFIGFS_ATTR_RO(iscsi_stat_logout_, abnormal_logouts);

अटल काष्ठा configfs_attribute *iscsi_stat_logout_stats_attrs[] = अणु
	&iscsi_stat_logout_attr_inst,
	&iscsi_stat_logout_attr_indx,
	&iscsi_stat_logout_attr_normal_logouts,
	&iscsi_stat_logout_attr_abnormal_logouts,
	शून्य,
पूर्ण;

स्थिर काष्ठा config_item_type iscsi_stat_logout_cit = अणु
	.ct_attrs		= iscsi_stat_logout_stats_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/*
 * Session Stats Table
 */
अटल काष्ठा iscsi_node_acl *iscsi_stat_nacl(काष्ठा config_item *item)
अणु
	काष्ठा iscsi_node_stat_grps *igrps = container_of(to_config_group(item),
			काष्ठा iscsi_node_stat_grps, iscsi_sess_stats_group);
	वापस container_of(igrps, काष्ठा iscsi_node_acl, node_stat_grps);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_inst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_wwn *wwn = acl->se_node_acl.se_tpg->se_tpg_wwn;
	काष्ठा iscsi_tiqn *tiqn = container_of(wwn,
			काष्ठा iscsi_tiqn, tiqn_wwn);

	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", tiqn->tiqn_index);
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_node_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
				sess->sess_ops->SessionType ? 0 : ISCSI_NODE_INDEX);
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_indx_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%u\n",
					sess->session_index);
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_cmd_pdus_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
				       atomic_दीर्घ_पढ़ो(&sess->cmd_pdus));
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_rsp_pdus_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
				       atomic_दीर्घ_पढ़ो(&sess->rsp_pdus));
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_txdata_octs_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
				       atomic_दीर्घ_पढ़ो(&sess->tx_data_octets));
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_rxdata_octs_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
				       atomic_दीर्घ_पढ़ो(&sess->rx_data_octets));
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_conn_digest_errors_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
				       atomic_दीर्घ_पढ़ो(&sess->conn_digest_errors));
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार iscsi_stat_sess_conn_समयout_errors_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा iscsi_node_acl *acl = iscsi_stat_nacl(item);
	काष्ठा se_node_acl *se_nacl = &acl->se_node_acl;
	काष्ठा iscsi_session *sess;
	काष्ठा se_session *se_sess;
	sमाप_प्रकार ret = 0;

	spin_lock_bh(&se_nacl->nacl_sess_lock);
	se_sess = se_nacl->nacl_sess;
	अगर (se_sess) अणु
		sess = se_sess->fabric_sess_ptr;
		अगर (sess)
			ret = snम_लिखो(page, PAGE_SIZE, "%lu\n",
				       atomic_दीर्घ_पढ़ो(&sess->conn_समयout_errors));
	पूर्ण
	spin_unlock_bh(&se_nacl->nacl_sess_lock);

	वापस ret;
पूर्ण

CONFIGFS_ATTR_RO(iscsi_stat_sess_, inst);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, node);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, indx);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, cmd_pdus);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, rsp_pdus);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, txdata_octs);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, rxdata_octs);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, conn_digest_errors);
CONFIGFS_ATTR_RO(iscsi_stat_sess_, conn_समयout_errors);

अटल काष्ठा configfs_attribute *iscsi_stat_sess_stats_attrs[] = अणु
	&iscsi_stat_sess_attr_inst,
	&iscsi_stat_sess_attr_node,
	&iscsi_stat_sess_attr_indx,
	&iscsi_stat_sess_attr_cmd_pdus,
	&iscsi_stat_sess_attr_rsp_pdus,
	&iscsi_stat_sess_attr_txdata_octs,
	&iscsi_stat_sess_attr_rxdata_octs,
	&iscsi_stat_sess_attr_conn_digest_errors,
	&iscsi_stat_sess_attr_conn_समयout_errors,
	शून्य,
पूर्ण;

स्थिर काष्ठा config_item_type iscsi_stat_sess_cit = अणु
	.ct_attrs		= iscsi_stat_sess_stats_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;
