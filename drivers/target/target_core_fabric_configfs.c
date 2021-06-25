<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
* Filename: target_core_fabric_configfs.c
 *
 * This file contains generic fabric module configfs infraकाष्ठाure क्रम
 * TCM v4.x code
 *
 * (c) Copyright 2010-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@linux-iscsi.org>
*
 ****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/utsname.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/unistd.h>
#समावेश <linux/माला.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/configfs.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"

#घोषणा TF_CIT_SETUP(_name, _item_ops, _group_ops, _attrs)		\
अटल व्योम target_fabric_setup_##_name##_cit(काष्ठा target_fabric_configfs *tf) \
अणु									\
	काष्ठा config_item_type *cit = &tf->tf_##_name##_cit;		\
									\
	cit->ct_item_ops = _item_ops;					\
	cit->ct_group_ops = _group_ops;					\
	cit->ct_attrs = _attrs;						\
	cit->ct_owner = tf->tf_ops->module;				\
	pr_debug("Setup generic %s\n", __stringअगरy(_name));		\
पूर्ण

#घोषणा TF_CIT_SETUP_DRV(_name, _item_ops, _group_ops)		\
अटल व्योम target_fabric_setup_##_name##_cit(काष्ठा target_fabric_configfs *tf) \
अणु									\
	काष्ठा config_item_type *cit = &tf->tf_##_name##_cit;		\
	काष्ठा configfs_attribute **attrs = tf->tf_ops->tfc_##_name##_attrs; \
									\
	cit->ct_item_ops = _item_ops;					\
	cit->ct_group_ops = _group_ops;					\
	cit->ct_attrs = attrs;						\
	cit->ct_owner = tf->tf_ops->module;				\
	pr_debug("Setup generic %s\n", __stringअगरy(_name));		\
पूर्ण

अटल काष्ठा configfs_item_operations target_fabric_port_item_ops;

/* Start of tfc_tpg_mappedlun_cit */

अटल पूर्णांक target_fabric_mappedlun_link(
	काष्ठा config_item *lun_acl_ci,
	काष्ठा config_item *lun_ci)
अणु
	काष्ठा se_dev_entry *deve;
	काष्ठा se_lun *lun;
	काष्ठा se_lun_acl *lacl = container_of(to_config_group(lun_acl_ci),
			काष्ठा se_lun_acl, se_lun_group);
	काष्ठा se_portal_group *se_tpg;
	काष्ठा config_item *nacl_ci, *tpg_ci, *tpg_ci_s, *wwn_ci, *wwn_ci_s;
	bool lun_access_ro;

	अगर (!lun_ci->ci_type ||
	    lun_ci->ci_type->ct_item_ops != &target_fabric_port_item_ops) अणु
		pr_err("Bad lun_ci, not a valid lun_ci pointer: %p\n", lun_ci);
		वापस -EFAULT;
	पूर्ण
	lun = container_of(to_config_group(lun_ci), काष्ठा se_lun, lun_group);

	/*
	 * Ensure that the source port exists
	 */
	अगर (!lun->lun_se_dev) अणु
		pr_err("Source se_lun->lun_se_dev does not exist\n");
		वापस -EINVAL;
	पूर्ण
	अगर (lun->lun_shutकरोwn) अणु
		pr_err("Unable to create mappedlun symlink because"
			" lun->lun_shutdown=true\n");
		वापस -EINVAL;
	पूर्ण
	se_tpg = lun->lun_tpg;

	nacl_ci = &lun_acl_ci->ci_parent->ci_group->cg_item;
	tpg_ci = &nacl_ci->ci_group->cg_item;
	wwn_ci = &tpg_ci->ci_group->cg_item;
	tpg_ci_s = &lun_ci->ci_parent->ci_group->cg_item;
	wwn_ci_s = &tpg_ci_s->ci_group->cg_item;
	/*
	 * Make sure the SymLink is going to the same $FABRIC/$WWN/tpgt_$TPGT
	 */
	अगर (म_भेद(config_item_name(wwn_ci), config_item_name(wwn_ci_s))) अणु
		pr_err("Illegal Initiator ACL SymLink outside of %s\n",
			config_item_name(wwn_ci));
		वापस -EINVAL;
	पूर्ण
	अगर (म_भेद(config_item_name(tpg_ci), config_item_name(tpg_ci_s))) अणु
		pr_err("Illegal Initiator ACL Symlink outside of %s"
			" TPGT: %s\n", config_item_name(wwn_ci),
			config_item_name(tpg_ci));
		वापस -EINVAL;
	पूर्ण
	/*
	 * If this काष्ठा se_node_acl was dynamically generated with
	 * tpg_1/attrib/generate_node_acls=1, use the existing
	 * deve->lun_access_ro value, which will be true when
	 * tpg_1/attrib/demo_mode_ग_लिखो_protect=1
	 */
	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(lacl->se_lun_nacl, lacl->mapped_lun);
	अगर (deve)
		lun_access_ro = deve->lun_access_ro;
	अन्यथा
		lun_access_ro =
			(se_tpg->se_tpg_tfo->tpg_check_prod_mode_ग_लिखो_protect(
				se_tpg)) ? true : false;
	rcu_पढ़ो_unlock();
	/*
	 * Determine the actual mapped LUN value user wants..
	 *
	 * This value is what the SCSI Initiator actually sees the
	 * $FABRIC/$WWPN/$TPGT/lun/lun_* as on their SCSI Initiator Ports.
	 */
	वापस core_dev_add_initiator_node_lun_acl(se_tpg, lacl, lun, lun_access_ro);
पूर्ण

अटल व्योम target_fabric_mappedlun_unlink(
	काष्ठा config_item *lun_acl_ci,
	काष्ठा config_item *lun_ci)
अणु
	काष्ठा se_lun_acl *lacl = container_of(to_config_group(lun_acl_ci),
			काष्ठा se_lun_acl, se_lun_group);
	काष्ठा se_lun *lun = container_of(to_config_group(lun_ci),
			काष्ठा se_lun, lun_group);

	core_dev_del_initiator_node_lun_acl(lun, lacl);
पूर्ण

अटल काष्ठा se_lun_acl *item_to_lun_acl(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_lun_acl,
			se_lun_group);
पूर्ण

अटल sमाप_प्रकार target_fabric_mappedlun_ग_लिखो_protect_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun_acl *lacl = item_to_lun_acl(item);
	काष्ठा se_node_acl *se_nacl = lacl->se_lun_nacl;
	काष्ठा se_dev_entry *deve;
	sमाप_प्रकार len = 0;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(se_nacl, lacl->mapped_lun);
	अगर (deve) अणु
		len = प्र_लिखो(page, "%d\n", deve->lun_access_ro);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस len;
पूर्ण

अटल sमाप_प्रकार target_fabric_mappedlun_ग_लिखो_protect_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_lun_acl *lacl = item_to_lun_acl(item);
	काष्ठा se_node_acl *se_nacl = lacl->se_lun_nacl;
	काष्ठा se_portal_group *se_tpg = se_nacl->se_tpg;
	अचिन्हित दीर्घ wp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &wp);
	अगर (ret)
		वापस ret;

	अगर ((wp != 1) && (wp != 0))
		वापस -EINVAL;

	/* wp=1 means lun_access_ro=true */
	core_update_device_list_access(lacl->mapped_lun, wp, lacl->se_lun_nacl);

	pr_debug("%s_ConfigFS: Changed Initiator ACL: %s"
		" Mapped LUN: %llu Write Protect bit to %s\n",
		se_tpg->se_tpg_tfo->fabric_name,
		se_nacl->initiatorname, lacl->mapped_lun, (wp) ? "ON" : "OFF");

	वापस count;

पूर्ण

CONFIGFS_ATTR(target_fabric_mappedlun_, ग_लिखो_protect);

अटल काष्ठा configfs_attribute *target_fabric_mappedlun_attrs[] = अणु
	&target_fabric_mappedlun_attr_ग_लिखो_protect,
	शून्य,
पूर्ण;

अटल व्योम target_fabric_mappedlun_release(काष्ठा config_item *item)
अणु
	काष्ठा se_lun_acl *lacl = container_of(to_config_group(item),
				काष्ठा se_lun_acl, se_lun_group);
	काष्ठा se_portal_group *se_tpg = lacl->se_lun_nacl->se_tpg;

	core_dev_मुक्त_initiator_node_lun_acl(se_tpg, lacl);
पूर्ण

अटल काष्ठा configfs_item_operations target_fabric_mappedlun_item_ops = अणु
	.release		= target_fabric_mappedlun_release,
	.allow_link		= target_fabric_mappedlun_link,
	.drop_link		= target_fabric_mappedlun_unlink,
पूर्ण;

TF_CIT_SETUP(tpg_mappedlun, &target_fabric_mappedlun_item_ops, शून्य,
		target_fabric_mappedlun_attrs);

/* End of tfc_tpg_mappedlun_cit */

/* Start of tfc_tpg_mappedlun_port_cit */

अटल काष्ठा config_group *target_core_mappedlun_stat_सूची_गढ़ो(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल व्योम target_core_mappedlun_stat_सूची_हटाओ(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	वापस;
पूर्ण

अटल काष्ठा configfs_group_operations target_fabric_mappedlun_stat_group_ops = अणु
	.make_group		= target_core_mappedlun_stat_सूची_गढ़ो,
	.drop_item		= target_core_mappedlun_stat_सूची_हटाओ,
पूर्ण;

TF_CIT_SETUP(tpg_mappedlun_stat, शून्य, &target_fabric_mappedlun_stat_group_ops,
		शून्य);

/* End of tfc_tpg_mappedlun_port_cit */

TF_CIT_SETUP_DRV(tpg_nacl_attrib, शून्य, शून्य);
TF_CIT_SETUP_DRV(tpg_nacl_auth, शून्य, शून्य);
TF_CIT_SETUP_DRV(tpg_nacl_param, शून्य, शून्य);

/* Start of tfc_tpg_nacl_base_cit */

अटल काष्ठा config_group *target_fabric_make_mappedlun(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा se_node_acl *se_nacl = container_of(group,
			काष्ठा se_node_acl, acl_group);
	काष्ठा se_portal_group *se_tpg = se_nacl->se_tpg;
	काष्ठा target_fabric_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	काष्ठा se_lun_acl *lacl = शून्य;
	अक्षर *buf;
	अचिन्हित दीर्घ दीर्घ mapped_lun;
	पूर्णांक ret = 0;

	buf = kzalloc(म_माप(name) + 1, GFP_KERNEL);
	अगर (!buf) अणु
		pr_err("Unable to allocate memory for name buf\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	snम_लिखो(buf, म_माप(name) + 1, "%s", name);
	/*
	 * Make sure user is creating iscsi/$IQN/$TPGT/acls/$INITIATOR/lun_$ID.
	 */
	अगर (म_माला(buf, "lun_") != buf) अणु
		pr_err("Unable to locate \"lun_\" from buf: %s"
			" name: %s\n", buf, name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	/*
	 * Determine the Mapped LUN value.  This is what the SCSI Initiator
	 * Port will actually see.
	 */
	ret = kम_से_अदीर्घl(buf + 4, 0, &mapped_lun);
	अगर (ret)
		जाओ out;

	lacl = core_dev_init_initiator_node_lun_acl(se_tpg, se_nacl,
			mapped_lun, &ret);
	अगर (!lacl) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	config_group_init_type_name(&lacl->se_lun_group, name,
			&tf->tf_tpg_mappedlun_cit);

	config_group_init_type_name(&lacl->ml_stat_grps.stat_group,
			"statistics", &tf->tf_tpg_mappedlun_stat_cit);
	configfs_add_शेष_group(&lacl->ml_stat_grps.stat_group,
			&lacl->se_lun_group);

	target_stat_setup_mappedlun_शेष_groups(lacl);

	kमुक्त(buf);
	वापस &lacl->se_lun_group;
out:
	kमुक्त(lacl);
	kमुक्त(buf);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम target_fabric_drop_mappedlun(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा se_lun_acl *lacl = container_of(to_config_group(item),
			काष्ठा se_lun_acl, se_lun_group);

	configfs_हटाओ_शेष_groups(&lacl->ml_stat_grps.stat_group);
	configfs_हटाओ_शेष_groups(&lacl->se_lun_group);

	config_item_put(item);
पूर्ण

अटल व्योम target_fabric_nacl_base_release(काष्ठा config_item *item)
अणु
	काष्ठा se_node_acl *se_nacl = container_of(to_config_group(item),
			काष्ठा se_node_acl, acl_group);

	configfs_हटाओ_शेष_groups(&se_nacl->acl_fabric_stat_group);
	core_tpg_del_initiator_node_acl(se_nacl);
पूर्ण

अटल काष्ठा configfs_item_operations target_fabric_nacl_base_item_ops = अणु
	.release		= target_fabric_nacl_base_release,
पूर्ण;

अटल काष्ठा configfs_group_operations target_fabric_nacl_base_group_ops = अणु
	.make_group		= target_fabric_make_mappedlun,
	.drop_item		= target_fabric_drop_mappedlun,
पूर्ण;

TF_CIT_SETUP_DRV(tpg_nacl_base, &target_fabric_nacl_base_item_ops,
		&target_fabric_nacl_base_group_ops);

/* End of tfc_tpg_nacl_base_cit */

/* Start of tfc_node_fabric_stats_cit */
/*
 * This is used as a placeholder क्रम काष्ठा se_node_acl->acl_fabric_stat_group
 * to allow fabrics access to ->acl_fabric_stat_group->शेष_groups[]
 */
TF_CIT_SETUP(tpg_nacl_stat, शून्य, शून्य, शून्य);

/* End of tfc_wwn_fabric_stats_cit */

/* Start of tfc_tpg_nacl_cit */

अटल काष्ठा config_group *target_fabric_make_nodeacl(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा se_portal_group *se_tpg = container_of(group,
			काष्ठा se_portal_group, tpg_acl_group);
	काष्ठा target_fabric_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	काष्ठा se_node_acl *se_nacl;

	se_nacl = core_tpg_add_initiator_node_acl(se_tpg, name);
	अगर (IS_ERR(se_nacl))
		वापस ERR_CAST(se_nacl);

	config_group_init_type_name(&se_nacl->acl_group, name,
			&tf->tf_tpg_nacl_base_cit);

	config_group_init_type_name(&se_nacl->acl_attrib_group, "attrib",
			&tf->tf_tpg_nacl_attrib_cit);
	configfs_add_शेष_group(&se_nacl->acl_attrib_group,
			&se_nacl->acl_group);

	config_group_init_type_name(&se_nacl->acl_auth_group, "auth",
			&tf->tf_tpg_nacl_auth_cit);
	configfs_add_शेष_group(&se_nacl->acl_auth_group,
			&se_nacl->acl_group);

	config_group_init_type_name(&se_nacl->acl_param_group, "param",
			&tf->tf_tpg_nacl_param_cit);
	configfs_add_शेष_group(&se_nacl->acl_param_group,
			&se_nacl->acl_group);

	config_group_init_type_name(&se_nacl->acl_fabric_stat_group,
			"fabric_statistics", &tf->tf_tpg_nacl_stat_cit);
	configfs_add_शेष_group(&se_nacl->acl_fabric_stat_group,
			&se_nacl->acl_group);

	अगर (tf->tf_ops->fabric_init_nodeacl) अणु
		पूर्णांक ret = tf->tf_ops->fabric_init_nodeacl(se_nacl, name);
		अगर (ret) अणु
			configfs_हटाओ_शेष_groups(&se_nacl->acl_fabric_stat_group);
			core_tpg_del_initiator_node_acl(se_nacl);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस &se_nacl->acl_group;
पूर्ण

अटल व्योम target_fabric_drop_nodeacl(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा se_node_acl *se_nacl = container_of(to_config_group(item),
			काष्ठा se_node_acl, acl_group);

	configfs_हटाओ_शेष_groups(&se_nacl->acl_group);

	/*
	 * काष्ठा se_node_acl मुक्त is करोne in target_fabric_nacl_base_release()
	 */
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_fabric_nacl_group_ops = अणु
	.make_group	= target_fabric_make_nodeacl,
	.drop_item	= target_fabric_drop_nodeacl,
पूर्ण;

TF_CIT_SETUP(tpg_nacl, शून्य, &target_fabric_nacl_group_ops, शून्य);

/* End of tfc_tpg_nacl_cit */

/* Start of tfc_tpg_np_base_cit */

अटल व्योम target_fabric_np_base_release(काष्ठा config_item *item)
अणु
	काष्ठा se_tpg_np *se_tpg_np = container_of(to_config_group(item),
				काष्ठा se_tpg_np, tpg_np_group);
	काष्ठा se_portal_group *se_tpg = se_tpg_np->tpg_np_parent;
	काष्ठा target_fabric_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;

	tf->tf_ops->fabric_drop_np(se_tpg_np);
पूर्ण

अटल काष्ठा configfs_item_operations target_fabric_np_base_item_ops = अणु
	.release		= target_fabric_np_base_release,
पूर्ण;

TF_CIT_SETUP_DRV(tpg_np_base, &target_fabric_np_base_item_ops, शून्य);

/* End of tfc_tpg_np_base_cit */

/* Start of tfc_tpg_np_cit */

अटल काष्ठा config_group *target_fabric_make_np(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा se_portal_group *se_tpg = container_of(group,
				काष्ठा se_portal_group, tpg_np_group);
	काष्ठा target_fabric_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	काष्ठा se_tpg_np *se_tpg_np;

	अगर (!tf->tf_ops->fabric_make_np) अणु
		pr_err("tf->tf_ops.fabric_make_np is NULL\n");
		वापस ERR_PTR(-ENOSYS);
	पूर्ण

	se_tpg_np = tf->tf_ops->fabric_make_np(se_tpg, group, name);
	अगर (!se_tpg_np || IS_ERR(se_tpg_np))
		वापस ERR_PTR(-EINVAL);

	se_tpg_np->tpg_np_parent = se_tpg;
	config_group_init_type_name(&se_tpg_np->tpg_np_group, name,
			&tf->tf_tpg_np_base_cit);

	वापस &se_tpg_np->tpg_np_group;
पूर्ण

अटल व्योम target_fabric_drop_np(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	/*
	 * काष्ठा se_tpg_np is released via target_fabric_np_base_release()
	 */
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_fabric_np_group_ops = अणु
	.make_group	= &target_fabric_make_np,
	.drop_item	= &target_fabric_drop_np,
पूर्ण;

TF_CIT_SETUP(tpg_np, शून्य, &target_fabric_np_group_ops, शून्य);

/* End of tfc_tpg_np_cit */

/* Start of tfc_tpg_port_cit */

अटल काष्ठा se_lun *item_to_lun(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_lun,
			lun_group);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_gp_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_show_tg_pt_gp_info(lun, page);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_gp_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_store_tg_pt_gp_info(lun, page, count);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_offline_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_show_offline_bit(lun, page);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_offline_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_store_offline_bit(lun, page, count);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_status_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_show_secondary_status(lun, page);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_status_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_store_secondary_status(lun, page, count);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_ग_लिखो_md_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_show_secondary_ग_लिखो_metadata(lun, page);
पूर्ण

अटल sमाप_प्रकार target_fabric_port_alua_tg_pt_ग_लिखो_md_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_lun *lun = item_to_lun(item);

	अगर (!lun || !lun->lun_se_dev)
		वापस -ENODEV;

	वापस core_alua_store_secondary_ग_लिखो_metadata(lun, page, count);
पूर्ण

CONFIGFS_ATTR(target_fabric_port_, alua_tg_pt_gp);
CONFIGFS_ATTR(target_fabric_port_, alua_tg_pt_offline);
CONFIGFS_ATTR(target_fabric_port_, alua_tg_pt_status);
CONFIGFS_ATTR(target_fabric_port_, alua_tg_pt_ग_लिखो_md);

अटल काष्ठा configfs_attribute *target_fabric_port_attrs[] = अणु
	&target_fabric_port_attr_alua_tg_pt_gp,
	&target_fabric_port_attr_alua_tg_pt_offline,
	&target_fabric_port_attr_alua_tg_pt_status,
	&target_fabric_port_attr_alua_tg_pt_ग_लिखो_md,
	शून्य,
पूर्ण;

अटल पूर्णांक target_fabric_port_link(
	काष्ठा config_item *lun_ci,
	काष्ठा config_item *se_dev_ci)
अणु
	काष्ठा config_item *tpg_ci;
	काष्ठा se_lun *lun = container_of(to_config_group(lun_ci),
				काष्ठा se_lun, lun_group);
	काष्ठा se_portal_group *se_tpg;
	काष्ठा se_device *dev;
	काष्ठा target_fabric_configfs *tf;
	पूर्णांक ret;

	अगर (!se_dev_ci->ci_type ||
	    se_dev_ci->ci_type->ct_item_ops != &target_core_dev_item_ops) अणु
		pr_err("Bad se_dev_ci, not a valid se_dev_ci pointer: %p\n", se_dev_ci);
		वापस -EFAULT;
	पूर्ण
	dev = container_of(to_config_group(se_dev_ci), काष्ठा se_device, dev_group);

	अगर (!target_dev_configured(dev)) अणु
		pr_err("se_device not configured yet, cannot port link\n");
		वापस -ENODEV;
	पूर्ण

	tpg_ci = &lun_ci->ci_parent->ci_group->cg_item;
	se_tpg = container_of(to_config_group(tpg_ci),
				काष्ठा se_portal_group, tpg_group);
	tf = se_tpg->se_tpg_wwn->wwn_tf;

	अगर (lun->lun_se_dev !=  शून्य) अणु
		pr_err("Port Symlink already exists\n");
		वापस -EEXIST;
	पूर्ण

	ret = core_dev_add_lun(se_tpg, dev, lun);
	अगर (ret) अणु
		pr_err("core_dev_add_lun() failed: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (tf->tf_ops->fabric_post_link) अणु
		/*
		 * Call the optional fabric_post_link() to allow a
		 * fabric module to setup any additional state once
		 * core_dev_add_lun() has been called..
		 */
		tf->tf_ops->fabric_post_link(se_tpg, lun);
	पूर्ण

	वापस 0;
out:
	वापस ret;
पूर्ण

अटल व्योम target_fabric_port_unlink(
	काष्ठा config_item *lun_ci,
	काष्ठा config_item *se_dev_ci)
अणु
	काष्ठा se_lun *lun = container_of(to_config_group(lun_ci),
				काष्ठा se_lun, lun_group);
	काष्ठा se_portal_group *se_tpg = lun->lun_tpg;
	काष्ठा target_fabric_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;

	अगर (tf->tf_ops->fabric_pre_unlink) अणु
		/*
		 * Call the optional fabric_pre_unlink() to allow a
		 * fabric module to release any additional stat beक्रमe
		 * core_dev_del_lun() is called.
		*/
		tf->tf_ops->fabric_pre_unlink(se_tpg, lun);
	पूर्ण

	core_dev_del_lun(se_tpg, lun);
पूर्ण

अटल व्योम target_fabric_port_release(काष्ठा config_item *item)
अणु
	काष्ठा se_lun *lun = container_of(to_config_group(item),
					  काष्ठा se_lun, lun_group);

	kमुक्त_rcu(lun, rcu_head);
पूर्ण

अटल काष्ठा configfs_item_operations target_fabric_port_item_ops = अणु
	.release		= target_fabric_port_release,
	.allow_link		= target_fabric_port_link,
	.drop_link		= target_fabric_port_unlink,
पूर्ण;

TF_CIT_SETUP(tpg_port, &target_fabric_port_item_ops, शून्य, target_fabric_port_attrs);

/* End of tfc_tpg_port_cit */

/* Start of tfc_tpg_port_stat_cit */

अटल काष्ठा config_group *target_core_port_stat_सूची_गढ़ो(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल व्योम target_core_port_stat_सूची_हटाओ(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	वापस;
पूर्ण

अटल काष्ठा configfs_group_operations target_fabric_port_stat_group_ops = अणु
	.make_group		= target_core_port_stat_सूची_गढ़ो,
	.drop_item		= target_core_port_stat_सूची_हटाओ,
पूर्ण;

TF_CIT_SETUP(tpg_port_stat, शून्य, &target_fabric_port_stat_group_ops, शून्य);

/* End of tfc_tpg_port_stat_cit */

/* Start of tfc_tpg_lun_cit */

अटल काष्ठा config_group *target_fabric_make_lun(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा se_lun *lun;
	काष्ठा se_portal_group *se_tpg = container_of(group,
			काष्ठा se_portal_group, tpg_lun_group);
	काष्ठा target_fabric_configfs *tf = se_tpg->se_tpg_wwn->wwn_tf;
	अचिन्हित दीर्घ दीर्घ unpacked_lun;
	पूर्णांक त्रुटि_सं;

	अगर (म_माला(name, "lun_") != name) अणु
		pr_err("Unable to locate \'_\" in"
				" \"lun_$LUN_NUMBER\"\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	त्रुटि_सं = kम_से_अदीर्घl(name + 4, 0, &unpacked_lun);
	अगर (त्रुटि_सं)
		वापस ERR_PTR(त्रुटि_सं);

	lun = core_tpg_alloc_lun(se_tpg, unpacked_lun);
	अगर (IS_ERR(lun))
		वापस ERR_CAST(lun);

	config_group_init_type_name(&lun->lun_group, name,
			&tf->tf_tpg_port_cit);

	config_group_init_type_name(&lun->port_stat_grps.stat_group,
			"statistics", &tf->tf_tpg_port_stat_cit);
	configfs_add_शेष_group(&lun->port_stat_grps.stat_group,
			&lun->lun_group);

	target_stat_setup_port_शेष_groups(lun);

	वापस &lun->lun_group;
पूर्ण

अटल व्योम target_fabric_drop_lun(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा se_lun *lun = container_of(to_config_group(item),
				काष्ठा se_lun, lun_group);

	configfs_हटाओ_शेष_groups(&lun->port_stat_grps.stat_group);
	configfs_हटाओ_शेष_groups(&lun->lun_group);

	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_fabric_lun_group_ops = अणु
	.make_group	= &target_fabric_make_lun,
	.drop_item	= &target_fabric_drop_lun,
पूर्ण;

TF_CIT_SETUP(tpg_lun, शून्य, &target_fabric_lun_group_ops, शून्य);

/* End of tfc_tpg_lun_cit */

TF_CIT_SETUP_DRV(tpg_attrib, शून्य, शून्य);
TF_CIT_SETUP_DRV(tpg_auth, शून्य, शून्य);
TF_CIT_SETUP_DRV(tpg_param, शून्य, शून्य);

/* Start of tfc_tpg_base_cit */

अटल व्योम target_fabric_tpg_release(काष्ठा config_item *item)
अणु
	काष्ठा se_portal_group *se_tpg = container_of(to_config_group(item),
			काष्ठा se_portal_group, tpg_group);
	काष्ठा se_wwn *wwn = se_tpg->se_tpg_wwn;
	काष्ठा target_fabric_configfs *tf = wwn->wwn_tf;

	tf->tf_ops->fabric_drop_tpg(se_tpg);
पूर्ण

अटल काष्ठा configfs_item_operations target_fabric_tpg_base_item_ops = अणु
	.release		= target_fabric_tpg_release,
पूर्ण;

TF_CIT_SETUP_DRV(tpg_base, &target_fabric_tpg_base_item_ops, शून्य);

/* End of tfc_tpg_base_cit */

/* Start of tfc_tpg_cit */

अटल काष्ठा config_group *target_fabric_make_tpg(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा se_wwn *wwn = container_of(group, काष्ठा se_wwn, wwn_group);
	काष्ठा target_fabric_configfs *tf = wwn->wwn_tf;
	काष्ठा se_portal_group *se_tpg;

	अगर (!tf->tf_ops->fabric_make_tpg) अणु
		pr_err("tf->tf_ops->fabric_make_tpg is NULL\n");
		वापस ERR_PTR(-ENOSYS);
	पूर्ण

	se_tpg = tf->tf_ops->fabric_make_tpg(wwn, name);
	अगर (!se_tpg || IS_ERR(se_tpg))
		वापस ERR_PTR(-EINVAL);

	config_group_init_type_name(&se_tpg->tpg_group, name,
			&tf->tf_tpg_base_cit);

	config_group_init_type_name(&se_tpg->tpg_lun_group, "lun",
			&tf->tf_tpg_lun_cit);
	configfs_add_शेष_group(&se_tpg->tpg_lun_group,
			&se_tpg->tpg_group);

	config_group_init_type_name(&se_tpg->tpg_np_group, "np",
			&tf->tf_tpg_np_cit);
	configfs_add_शेष_group(&se_tpg->tpg_np_group,
			&se_tpg->tpg_group);

	config_group_init_type_name(&se_tpg->tpg_acl_group, "acls",
			&tf->tf_tpg_nacl_cit);
	configfs_add_शेष_group(&se_tpg->tpg_acl_group,
			&se_tpg->tpg_group);

	config_group_init_type_name(&se_tpg->tpg_attrib_group, "attrib",
			&tf->tf_tpg_attrib_cit);
	configfs_add_शेष_group(&se_tpg->tpg_attrib_group,
			&se_tpg->tpg_group);

	config_group_init_type_name(&se_tpg->tpg_auth_group, "auth",
			&tf->tf_tpg_auth_cit);
	configfs_add_शेष_group(&se_tpg->tpg_auth_group,
			&se_tpg->tpg_group);

	config_group_init_type_name(&se_tpg->tpg_param_group, "param",
			&tf->tf_tpg_param_cit);
	configfs_add_शेष_group(&se_tpg->tpg_param_group,
			&se_tpg->tpg_group);

	वापस &se_tpg->tpg_group;
पूर्ण

अटल व्योम target_fabric_drop_tpg(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा se_portal_group *se_tpg = container_of(to_config_group(item),
				काष्ठा se_portal_group, tpg_group);

	configfs_हटाओ_शेष_groups(&se_tpg->tpg_group);
	config_item_put(item);
पूर्ण

अटल व्योम target_fabric_release_wwn(काष्ठा config_item *item)
अणु
	काष्ठा se_wwn *wwn = container_of(to_config_group(item),
				काष्ठा se_wwn, wwn_group);
	काष्ठा target_fabric_configfs *tf = wwn->wwn_tf;

	configfs_हटाओ_शेष_groups(&wwn->fabric_stat_group);
	configfs_हटाओ_शेष_groups(&wwn->param_group);
	tf->tf_ops->fabric_drop_wwn(wwn);
पूर्ण

अटल काष्ठा configfs_item_operations target_fabric_tpg_item_ops = अणु
	.release	= target_fabric_release_wwn,
पूर्ण;

अटल काष्ठा configfs_group_operations target_fabric_tpg_group_ops = अणु
	.make_group	= target_fabric_make_tpg,
	.drop_item	= target_fabric_drop_tpg,
पूर्ण;

TF_CIT_SETUP(tpg, &target_fabric_tpg_item_ops, &target_fabric_tpg_group_ops,
		शून्य);

/* End of tfc_tpg_cit */

/* Start of tfc_wwn_fabric_stats_cit */
/*
 * This is used as a placeholder क्रम काष्ठा se_wwn->fabric_stat_group
 * to allow fabrics access to ->fabric_stat_group->शेष_groups[]
 */
TF_CIT_SETUP(wwn_fabric_stats, शून्य, शून्य, शून्य);

/* End of tfc_wwn_fabric_stats_cit */

अटल sमाप_प्रकार
target_fabric_wwn_cmd_completion_affinity_show(काष्ठा config_item *item,
					       अक्षर *page)
अणु
	काष्ठा se_wwn *wwn = container_of(to_config_group(item), काष्ठा se_wwn,
					  param_group);
	वापस प्र_लिखो(page, "%d\n",
		       wwn->cmd_compl_affinity == WORK_CPU_UNBOUND ?
		       SE_COMPL_AFFINITY_CURR_CPU : wwn->cmd_compl_affinity);
पूर्ण

अटल sमाप_प्रकार
target_fabric_wwn_cmd_completion_affinity_store(काष्ठा config_item *item,
						स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_wwn *wwn = container_of(to_config_group(item), काष्ठा se_wwn,
					  param_group);
	पूर्णांक compl_val;

	अगर (kstrtoपूर्णांक(page, 0, &compl_val))
		वापस -EINVAL;

	चयन (compl_val) अणु
	हाल SE_COMPL_AFFINITY_CPUID:
		wwn->cmd_compl_affinity = compl_val;
		अवरोध;
	हाल SE_COMPL_AFFINITY_CURR_CPU:
		wwn->cmd_compl_affinity = WORK_CPU_UNBOUND;
		अवरोध;
	शेष:
		अगर (compl_val < 0 || compl_val >= nr_cpu_ids ||
		    !cpu_online(compl_val)) अणु
			pr_err("Command completion value must be between %d and %d or an online CPU.\n",
			       SE_COMPL_AFFINITY_CPUID,
			       SE_COMPL_AFFINITY_CURR_CPU);
			वापस -EINVAL;
		पूर्ण
		wwn->cmd_compl_affinity = compl_val;
	पूर्ण

	वापस count;
पूर्ण
CONFIGFS_ATTR(target_fabric_wwn_, cmd_completion_affinity);

अटल काष्ठा configfs_attribute *target_fabric_wwn_param_attrs[] = अणु
	&target_fabric_wwn_attr_cmd_completion_affinity,
	शून्य,
पूर्ण;

TF_CIT_SETUP(wwn_param, शून्य, शून्य, target_fabric_wwn_param_attrs);

/* Start of tfc_wwn_cit */

अटल काष्ठा config_group *target_fabric_make_wwn(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा target_fabric_configfs *tf = container_of(group,
				काष्ठा target_fabric_configfs, tf_group);
	काष्ठा se_wwn *wwn;

	अगर (!tf->tf_ops->fabric_make_wwn) अणु
		pr_err("tf->tf_ops.fabric_make_wwn is NULL\n");
		वापस ERR_PTR(-ENOSYS);
	पूर्ण

	wwn = tf->tf_ops->fabric_make_wwn(tf, group, name);
	अगर (!wwn || IS_ERR(wwn))
		वापस ERR_PTR(-EINVAL);

	wwn->cmd_compl_affinity = SE_COMPL_AFFINITY_CPUID;
	wwn->wwn_tf = tf;

	config_group_init_type_name(&wwn->wwn_group, name, &tf->tf_tpg_cit);

	config_group_init_type_name(&wwn->fabric_stat_group, "fabric_statistics",
			&tf->tf_wwn_fabric_stats_cit);
	configfs_add_शेष_group(&wwn->fabric_stat_group, &wwn->wwn_group);

	config_group_init_type_name(&wwn->param_group, "param",
			&tf->tf_wwn_param_cit);
	configfs_add_शेष_group(&wwn->param_group, &wwn->wwn_group);

	अगर (tf->tf_ops->add_wwn_groups)
		tf->tf_ops->add_wwn_groups(wwn);
	वापस &wwn->wwn_group;
पूर्ण

अटल व्योम target_fabric_drop_wwn(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा se_wwn *wwn = container_of(to_config_group(item),
				काष्ठा se_wwn, wwn_group);

	configfs_हटाओ_शेष_groups(&wwn->wwn_group);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_fabric_wwn_group_ops = अणु
	.make_group	= target_fabric_make_wwn,
	.drop_item	= target_fabric_drop_wwn,
पूर्ण;

TF_CIT_SETUP_DRV(wwn, शून्य, &target_fabric_wwn_group_ops);
TF_CIT_SETUP_DRV(discovery, शून्य, शून्य);

पूर्णांक target_fabric_setup_cits(काष्ठा target_fabric_configfs *tf)
अणु
	target_fabric_setup_discovery_cit(tf);
	target_fabric_setup_wwn_cit(tf);
	target_fabric_setup_wwn_fabric_stats_cit(tf);
	target_fabric_setup_wwn_param_cit(tf);
	target_fabric_setup_tpg_cit(tf);
	target_fabric_setup_tpg_base_cit(tf);
	target_fabric_setup_tpg_port_cit(tf);
	target_fabric_setup_tpg_port_stat_cit(tf);
	target_fabric_setup_tpg_lun_cit(tf);
	target_fabric_setup_tpg_np_cit(tf);
	target_fabric_setup_tpg_np_base_cit(tf);
	target_fabric_setup_tpg_attrib_cit(tf);
	target_fabric_setup_tpg_auth_cit(tf);
	target_fabric_setup_tpg_param_cit(tf);
	target_fabric_setup_tpg_nacl_cit(tf);
	target_fabric_setup_tpg_nacl_base_cit(tf);
	target_fabric_setup_tpg_nacl_attrib_cit(tf);
	target_fabric_setup_tpg_nacl_auth_cit(tf);
	target_fabric_setup_tpg_nacl_param_cit(tf);
	target_fabric_setup_tpg_nacl_stat_cit(tf);
	target_fabric_setup_tpg_mappedlun_cit(tf);
	target_fabric_setup_tpg_mappedlun_stat_cit(tf);

	वापस 0;
पूर्ण
