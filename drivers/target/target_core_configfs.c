<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_configfs.c
 *
 * This file contains ConfigFS logic क्रम the Generic Target Engine project.
 *
 * (c) Copyright 2008-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 * based on configfs Copyright (C) 2005 Oracle.  All rights reserved.
 *
 ****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <generated/utsrelease.h>
#समावेश <linux/utsname.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/unistd.h>
#समावेश <linux/माला.स>
#समावेश <linux/parser.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/configfs.h>
#समावेश <linux/spinlock.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_rd.h"
#समावेश "target_core_xcopy.h"

#घोषणा TB_CIT_SETUP(_name, _item_ops, _group_ops, _attrs)		\
अटल व्योम target_core_setup_##_name##_cit(काष्ठा target_backend *tb)	\
अणु									\
	काष्ठा config_item_type *cit = &tb->tb_##_name##_cit;		\
									\
	cit->ct_item_ops = _item_ops;					\
	cit->ct_group_ops = _group_ops;					\
	cit->ct_attrs = _attrs;						\
	cit->ct_owner = tb->ops->owner;					\
	pr_debug("Setup generic %s\n", __stringअगरy(_name));		\
पूर्ण

#घोषणा TB_CIT_SETUP_DRV(_name, _item_ops, _group_ops)			\
अटल व्योम target_core_setup_##_name##_cit(काष्ठा target_backend *tb)	\
अणु									\
	काष्ठा config_item_type *cit = &tb->tb_##_name##_cit;		\
									\
	cit->ct_item_ops = _item_ops;					\
	cit->ct_group_ops = _group_ops;					\
	cit->ct_attrs = tb->ops->tb_##_name##_attrs;			\
	cit->ct_owner = tb->ops->owner;					\
	pr_debug("Setup generic %s\n", __stringअगरy(_name));		\
पूर्ण

बाह्य काष्ठा t10_alua_lu_gp *शेष_lu_gp;

अटल LIST_HEAD(g_tf_list);
अटल DEFINE_MUTEX(g_tf_lock);

अटल काष्ठा config_group target_core_hbagroup;
अटल काष्ठा config_group alua_group;
अटल काष्ठा config_group alua_lu_gps_group;

अटल अंतरभूत काष्ठा se_hba *
item_to_hba(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_hba, hba_group);
पूर्ण

/*
 * Attributes क्रम /sys/kernel/config/target/
 */
अटल sमाप_प्रकार target_core_item_version_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "Target Engine Core ConfigFS Infrastructure %s"
		" on %s/%s on "UTS_RELEASE"\n", TARGET_CORE_VERSION,
		utsname()->sysname, utsname()->machine);
पूर्ण

CONFIGFS_ATTR_RO(target_core_item_, version);

अक्षर db_root[DB_ROOT_LEN] = DB_ROOT_DEFAULT;
अटल अक्षर db_root_stage[DB_ROOT_LEN];

अटल sमाप_प्रकार target_core_item_dbroot_show(काष्ठा config_item *item,
					    अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", db_root);
पूर्ण

अटल sमाप_प्रकार target_core_item_dbroot_store(काष्ठा config_item *item,
					स्थिर अक्षर *page, माप_प्रकार count)
अणु
	sमाप_प्रकार पढ़ो_bytes;
	काष्ठा file *fp;

	mutex_lock(&g_tf_lock);
	अगर (!list_empty(&g_tf_list)) अणु
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: cannot be changed: target drivers registered");
		वापस -EINVAL;
	पूर्ण

	अगर (count > (DB_ROOT_LEN - 1)) अणु
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: count %d exceeds DB_ROOT_LEN-1: %u\n",
		       (पूर्णांक)count, DB_ROOT_LEN - 1);
		वापस -EINVAL;
	पूर्ण

	पढ़ो_bytes = snम_लिखो(db_root_stage, DB_ROOT_LEN, "%s", page);
	अगर (!पढ़ो_bytes) अणु
		mutex_unlock(&g_tf_lock);
		वापस -EINVAL;
	पूर्ण
	अगर (db_root_stage[पढ़ो_bytes - 1] == '\n')
		db_root_stage[पढ़ो_bytes - 1] = '\0';

	/* validate new db root beक्रमe accepting it */
	fp = filp_खोलो(db_root_stage, O_RDONLY, 0);
	अगर (IS_ERR(fp)) अणु
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: cannot open: %s\n", db_root_stage);
		वापस -EINVAL;
	पूर्ण
	अगर (!S_ISसूची(file_inode(fp)->i_mode)) अणु
		filp_बंद(fp, शून्य);
		mutex_unlock(&g_tf_lock);
		pr_err("db_root: not a directory: %s\n", db_root_stage);
		वापस -EINVAL;
	पूर्ण
	filp_बंद(fp, शून्य);

	म_नकलन(db_root, db_root_stage, पढ़ो_bytes);

	mutex_unlock(&g_tf_lock);

	pr_debug("Target_Core_ConfigFS: db_root set to %s\n", db_root);

	वापस पढ़ो_bytes;
पूर्ण

CONFIGFS_ATTR(target_core_item_, dbroot);

अटल काष्ठा target_fabric_configfs *target_core_get_fabric(
	स्थिर अक्षर *name)
अणु
	काष्ठा target_fabric_configfs *tf;

	अगर (!name)
		वापस शून्य;

	mutex_lock(&g_tf_lock);
	list_क्रम_each_entry(tf, &g_tf_list, tf_list) अणु
		स्थिर अक्षर *cmp_name = tf->tf_ops->fabric_alias;
		अगर (!cmp_name)
			cmp_name = tf->tf_ops->fabric_name;
		अगर (!म_भेद(cmp_name, name)) अणु
			atomic_inc(&tf->tf_access_cnt);
			mutex_unlock(&g_tf_lock);
			वापस tf;
		पूर्ण
	पूर्ण
	mutex_unlock(&g_tf_lock);

	वापस शून्य;
पूर्ण

/*
 * Called from काष्ठा target_core_group_ops->make_group()
 */
अटल काष्ठा config_group *target_core_रेजिस्टर_fabric(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा target_fabric_configfs *tf;
	पूर्णांक ret;

	pr_debug("Target_Core_ConfigFS: REGISTER -> group: %p name:"
			" %s\n", group, name);

	tf = target_core_get_fabric(name);
	अगर (!tf) अणु
		pr_debug("target_core_register_fabric() trying autoload for %s\n",
			 name);

		/*
		 * Below are some hardcoded request_module() calls to स्वतःmatically
		 * local fabric modules when the following is called:
		 *
		 * सूची_गढ़ो -p /sys/kernel/config/target/$MODULE_NAME
		 *
		 * Note that this करोes not limit which TCM fabric module can be
		 * रेजिस्टरed, but simply provids स्वतः loading logic क्रम modules with
		 * सूची_गढ़ो(2) प्रणाली calls with known TCM fabric modules.
		 */

		अगर (!म_भेदन(name, "iscsi", 5)) अणु
			/*
			 * Automatically load the LIO Target fabric module when the
			 * following is called:
			 *
			 * सूची_गढ़ो -p $CONFIGFS/target/iscsi
			 */
			ret = request_module("iscsi_target_mod");
			अगर (ret < 0) अणु
				pr_debug("request_module() failed for"
				         " iscsi_target_mod.ko: %d\n", ret);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(name, "loopback", 8)) अणु
			/*
			 * Automatically load the tcm_loop fabric module when the
			 * following is called:
			 *
			 * सूची_गढ़ो -p $CONFIGFS/target/loopback
			 */
			ret = request_module("tcm_loop");
			अगर (ret < 0) अणु
				pr_debug("request_module() failed for"
				         " tcm_loop.ko: %d\n", ret);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
		पूर्ण

		tf = target_core_get_fabric(name);
	पूर्ण

	अगर (!tf) अणु
		pr_debug("target_core_get_fabric() failed for %s\n",
		         name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	pr_debug("Target_Core_ConfigFS: REGISTER -> Located fabric:"
			" %s\n", tf->tf_ops->fabric_name);
	/*
	 * On a successful target_core_get_fabric() look, the वापसed
	 * काष्ठा target_fabric_configfs *tf will contain a usage reference.
	 */
	pr_debug("Target_Core_ConfigFS: REGISTER tfc_wwn_cit -> %p\n",
			&tf->tf_wwn_cit);

	config_group_init_type_name(&tf->tf_group, name, &tf->tf_wwn_cit);

	config_group_init_type_name(&tf->tf_disc_group, "discovery_auth",
			&tf->tf_discovery_cit);
	configfs_add_शेष_group(&tf->tf_disc_group, &tf->tf_group);

	pr_debug("Target_Core_ConfigFS: REGISTER -> Allocated Fabric: %s\n",
		 config_item_name(&tf->tf_group.cg_item));
	वापस &tf->tf_group;
पूर्ण

/*
 * Called from काष्ठा target_core_group_ops->drop_item()
 */
अटल व्योम target_core_deरेजिस्टर_fabric(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा target_fabric_configfs *tf = container_of(
		to_config_group(item), काष्ठा target_fabric_configfs, tf_group);

	pr_debug("Target_Core_ConfigFS: DEREGISTER -> Looking up %s in"
		" tf list\n", config_item_name(item));

	pr_debug("Target_Core_ConfigFS: DEREGISTER -> located fabric:"
			" %s\n", tf->tf_ops->fabric_name);
	atomic_dec(&tf->tf_access_cnt);

	pr_debug("Target_Core_ConfigFS: DEREGISTER -> Releasing ci"
			" %s\n", config_item_name(item));

	configfs_हटाओ_शेष_groups(&tf->tf_group);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_core_fabric_group_ops = अणु
	.make_group	= &target_core_रेजिस्टर_fabric,
	.drop_item	= &target_core_deरेजिस्टर_fabric,
पूर्ण;

/*
 * All item attributes appearing in /sys/kernel/target/ appear here.
 */
अटल काष्ठा configfs_attribute *target_core_fabric_item_attrs[] = अणु
	&target_core_item_attr_version,
	&target_core_item_attr_dbroot,
	शून्य,
पूर्ण;

/*
 * Provides Fabrics Groups and Item Attributes क्रम /sys/kernel/config/target/
 */
अटल स्थिर काष्ठा config_item_type target_core_fabrics_item = अणु
	.ct_group_ops	= &target_core_fabric_group_ops,
	.ct_attrs	= target_core_fabric_item_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली target_core_fabrics = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "target",
			.ci_type = &target_core_fabrics_item,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक target_depend_item(काष्ठा config_item *item)
अणु
	वापस configfs_depend_item(&target_core_fabrics, item);
पूर्ण
EXPORT_SYMBOL(target_depend_item);

व्योम target_undepend_item(काष्ठा config_item *item)
अणु
	वापस configfs_undepend_item(item);
पूर्ण
EXPORT_SYMBOL(target_undepend_item);

/*##############################################################################
// Start functions called by बाह्यal Target Fabrics Modules
//############################################################################*/

अटल पूर्णांक target_fabric_tf_ops_check(स्थिर काष्ठा target_core_fabric_ops *tfo)
अणु
	अगर (tfo->fabric_alias) अणु
		अगर (म_माप(tfo->fabric_alias) >= TARGET_FABRIC_NAME_SIZE) अणु
			pr_err("Passed alias: %s exceeds "
				"TARGET_FABRIC_NAME_SIZE\n", tfo->fabric_alias);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (!tfo->fabric_name) अणु
		pr_err("Missing tfo->fabric_name\n");
		वापस -EINVAL;
	पूर्ण
	अगर (म_माप(tfo->fabric_name) >= TARGET_FABRIC_NAME_SIZE) अणु
		pr_err("Passed name: %s exceeds "
			"TARGET_FABRIC_NAME_SIZE\n", tfo->fabric_name);
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->tpg_get_wwn) अणु
		pr_err("Missing tfo->tpg_get_wwn()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->tpg_get_tag) अणु
		pr_err("Missing tfo->tpg_get_tag()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->tpg_check_demo_mode) अणु
		pr_err("Missing tfo->tpg_check_demo_mode()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->tpg_check_demo_mode_cache) अणु
		pr_err("Missing tfo->tpg_check_demo_mode_cache()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->tpg_check_demo_mode_ग_लिखो_protect) अणु
		pr_err("Missing tfo->tpg_check_demo_mode_write_protect()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->tpg_check_prod_mode_ग_लिखो_protect) अणु
		pr_err("Missing tfo->tpg_check_prod_mode_write_protect()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->tpg_get_inst_index) अणु
		pr_err("Missing tfo->tpg_get_inst_index()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->release_cmd) अणु
		pr_err("Missing tfo->release_cmd()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->sess_get_index) अणु
		pr_err("Missing tfo->sess_get_index()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->ग_लिखो_pending) अणु
		pr_err("Missing tfo->write_pending()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->set_शेष_node_attributes) अणु
		pr_err("Missing tfo->set_default_node_attributes()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->get_cmd_state) अणु
		pr_err("Missing tfo->get_cmd_state()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->queue_data_in) अणु
		pr_err("Missing tfo->queue_data_in()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->queue_status) अणु
		pr_err("Missing tfo->queue_status()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->queue_पंचांग_rsp) अणु
		pr_err("Missing tfo->queue_tm_rsp()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->पातed_task) अणु
		pr_err("Missing tfo->aborted_task()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->check_stop_मुक्त) अणु
		pr_err("Missing tfo->check_stop_free()\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * We at least require tfo->fabric_make_wwn(), tfo->fabric_drop_wwn()
	 * tfo->fabric_make_tpg() and tfo->fabric_drop_tpg() in
	 * target_core_fabric_configfs.c WWN+TPG group context code.
	 */
	अगर (!tfo->fabric_make_wwn) अणु
		pr_err("Missing tfo->fabric_make_wwn()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->fabric_drop_wwn) अणु
		pr_err("Missing tfo->fabric_drop_wwn()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->fabric_make_tpg) अणु
		pr_err("Missing tfo->fabric_make_tpg()\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!tfo->fabric_drop_tpg) अणु
		pr_err("Missing tfo->fabric_drop_tpg()\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक target_रेजिस्टर_ढाँचा(स्थिर काष्ठा target_core_fabric_ops *fo)
अणु
	काष्ठा target_fabric_configfs *tf;
	पूर्णांक ret;

	ret = target_fabric_tf_ops_check(fo);
	अगर (ret)
		वापस ret;

	tf = kzalloc(माप(काष्ठा target_fabric_configfs), GFP_KERNEL);
	अगर (!tf) अणु
		pr_err("%s: could not allocate memory!\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&tf->tf_list);
	atomic_set(&tf->tf_access_cnt, 0);
	tf->tf_ops = fo;
	target_fabric_setup_cits(tf);

	mutex_lock(&g_tf_lock);
	list_add_tail(&tf->tf_list, &g_tf_list);
	mutex_unlock(&g_tf_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(target_रेजिस्टर_ढाँचा);

व्योम target_unरेजिस्टर_ढाँचा(स्थिर काष्ठा target_core_fabric_ops *fo)
अणु
	काष्ठा target_fabric_configfs *t;

	mutex_lock(&g_tf_lock);
	list_क्रम_each_entry(t, &g_tf_list, tf_list) अणु
		अगर (!म_भेद(t->tf_ops->fabric_name, fo->fabric_name)) अणु
			BUG_ON(atomic_पढ़ो(&t->tf_access_cnt));
			list_del(&t->tf_list);
			mutex_unlock(&g_tf_lock);
			/*
			 * Wait क्रम any outstanding fabric se_deve_entry->rcu_head
			 * callbacks to complete post kमुक्त_rcu(), beक्रमe allowing
			 * fabric driver unload of TFO->module to proceed.
			 */
			rcu_barrier();
			kमुक्त(t);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&g_tf_lock);
पूर्ण
EXPORT_SYMBOL(target_unरेजिस्टर_ढाँचा);

/*##############################################################################
// Stop functions called by बाह्यal Target Fabrics Modules
//############################################################################*/

अटल अंतरभूत काष्ठा se_dev_attrib *to_attrib(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_dev_attrib,
			da_group);
पूर्ण

/* Start functions क्रम काष्ठा config_item_type tb_dev_attrib_cit */
#घोषणा DEF_CONFIGFS_ATTRIB_SHOW(_name)					\
अटल sमाप_प्रकार _name##_show(काष्ठा config_item *item, अक्षर *page)	\
अणु									\
	वापस snम_लिखो(page, PAGE_SIZE, "%u\n", to_attrib(item)->_name); \
पूर्ण

DEF_CONFIGFS_ATTRIB_SHOW(emulate_model_alias);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_dpo);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_fua_ग_लिखो);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_fua_पढ़ो);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_ग_लिखो_cache);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_ua_पूर्णांकlck_ctrl);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_tas);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_tpu);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_tpws);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_caw);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_3pc);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_pr);
DEF_CONFIGFS_ATTRIB_SHOW(pi_prot_type);
DEF_CONFIGFS_ATTRIB_SHOW(hw_pi_prot_type);
DEF_CONFIGFS_ATTRIB_SHOW(pi_prot_verअगरy);
DEF_CONFIGFS_ATTRIB_SHOW(enक्रमce_pr_isids);
DEF_CONFIGFS_ATTRIB_SHOW(is_nonrot);
DEF_CONFIGFS_ATTRIB_SHOW(emulate_rest_reord);
DEF_CONFIGFS_ATTRIB_SHOW(क्रमce_pr_aptpl);
DEF_CONFIGFS_ATTRIB_SHOW(hw_block_size);
DEF_CONFIGFS_ATTRIB_SHOW(block_size);
DEF_CONFIGFS_ATTRIB_SHOW(hw_max_sectors);
DEF_CONFIGFS_ATTRIB_SHOW(optimal_sectors);
DEF_CONFIGFS_ATTRIB_SHOW(hw_queue_depth);
DEF_CONFIGFS_ATTRIB_SHOW(queue_depth);
DEF_CONFIGFS_ATTRIB_SHOW(max_unmap_lba_count);
DEF_CONFIGFS_ATTRIB_SHOW(max_unmap_block_desc_count);
DEF_CONFIGFS_ATTRIB_SHOW(unmap_granularity);
DEF_CONFIGFS_ATTRIB_SHOW(unmap_granularity_alignment);
DEF_CONFIGFS_ATTRIB_SHOW(unmap_zeroes_data);
DEF_CONFIGFS_ATTRIB_SHOW(max_ग_लिखो_same_len);

#घोषणा DEF_CONFIGFS_ATTRIB_STORE_U32(_name)				\
अटल sमाप_प्रकार _name##_store(काष्ठा config_item *item, स्थिर अक्षर *page,\
		माप_प्रकार count)						\
अणु									\
	काष्ठा se_dev_attrib *da = to_attrib(item);			\
	u32 val;							\
	पूर्णांक ret;							\
									\
	ret = kstrtou32(page, 0, &val);					\
	अगर (ret < 0)							\
		वापस ret;						\
	da->_name = val;						\
	वापस count;							\
पूर्ण

DEF_CONFIGFS_ATTRIB_STORE_U32(max_unmap_lba_count);
DEF_CONFIGFS_ATTRIB_STORE_U32(max_unmap_block_desc_count);
DEF_CONFIGFS_ATTRIB_STORE_U32(unmap_granularity);
DEF_CONFIGFS_ATTRIB_STORE_U32(unmap_granularity_alignment);
DEF_CONFIGFS_ATTRIB_STORE_U32(max_ग_लिखो_same_len);

#घोषणा DEF_CONFIGFS_ATTRIB_STORE_BOOL(_name)				\
अटल sमाप_प्रकार _name##_store(काष्ठा config_item *item, स्थिर अक्षर *page,	\
		माप_प्रकार count)						\
अणु									\
	काष्ठा se_dev_attrib *da = to_attrib(item);			\
	bool flag;							\
	पूर्णांक ret;							\
									\
	ret = strtobool(page, &flag);					\
	अगर (ret < 0)							\
		वापस ret;						\
	da->_name = flag;						\
	वापस count;							\
पूर्ण

DEF_CONFIGFS_ATTRIB_STORE_BOOL(emulate_fua_ग_लिखो);
DEF_CONFIGFS_ATTRIB_STORE_BOOL(emulate_caw);
DEF_CONFIGFS_ATTRIB_STORE_BOOL(emulate_3pc);
DEF_CONFIGFS_ATTRIB_STORE_BOOL(emulate_pr);
DEF_CONFIGFS_ATTRIB_STORE_BOOL(enक्रमce_pr_isids);
DEF_CONFIGFS_ATTRIB_STORE_BOOL(is_nonrot);

#घोषणा DEF_CONFIGFS_ATTRIB_STORE_STUB(_name)				\
अटल sमाप_प्रकार _name##_store(काष्ठा config_item *item, स्थिर अक्षर *page,\
		माप_प्रकार count)						\
अणु									\
	prपूर्णांकk_once(KERN_WARNING					\
		"ignoring deprecated %s attribute\n",			\
		__stringअगरy(_name));					\
	वापस count;							\
पूर्ण

DEF_CONFIGFS_ATTRIB_STORE_STUB(emulate_dpo);
DEF_CONFIGFS_ATTRIB_STORE_STUB(emulate_fua_पढ़ो);

अटल व्योम dev_set_t10_wwn_model_alias(काष्ठा se_device *dev)
अणु
	स्थिर अक्षर *configname;

	configname = config_item_name(&dev->dev_group.cg_item);
	अगर (म_माप(configname) >= INQUIRY_MODEL_LEN) अणु
		pr_warn("dev[%p]: Backstore name '%s' is too long for "
			"INQUIRY_MODEL, truncating to 15 characters\n", dev,
			configname);
	पूर्ण
	/*
	 * XXX We can't use माप(dev->t10_wwn.model) (INQUIRY_MODEL_LEN + 1)
	 * here without potentially अवरोधing existing setups, so जारी to
	 * truncate one byte लघुer than what can be carried in INQUIRY.
	 */
	strlcpy(dev->t10_wwn.model, configname, INQUIRY_MODEL_LEN);
पूर्ण

अटल sमाप_प्रकार emulate_model_alias_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	काष्ठा se_device *dev = da->da_dev;
	bool flag;
	पूर्णांक ret;

	अगर (dev->export_count) अणु
		pr_err("dev[%p]: Unable to change model alias"
			" while export_count is %d\n",
			dev, dev->export_count);
		वापस -EINVAL;
	पूर्ण

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	BUILD_BUG_ON(माप(dev->t10_wwn.model) != INQUIRY_MODEL_LEN + 1);
	अगर (flag) अणु
		dev_set_t10_wwn_model_alias(dev);
	पूर्ण अन्यथा अणु
		strlcpy(dev->t10_wwn.model, dev->transport->inquiry_prod,
			माप(dev->t10_wwn.model));
	पूर्ण
	da->emulate_model_alias = flag;
	वापस count;
पूर्ण

अटल sमाप_प्रकार emulate_ग_लिखो_cache_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (flag && da->da_dev->transport->get_ग_लिखो_cache) अणु
		pr_err("emulate_write_cache not supported for this device\n");
		वापस -EINVAL;
	पूर्ण

	da->emulate_ग_लिखो_cache = flag;
	pr_debug("dev[%p]: SE Device WRITE_CACHE_EMULATION flag: %d\n",
			da->da_dev, flag);
	वापस count;
पूर्ण

अटल sमाप_प्रकार emulate_ua_पूर्णांकlck_ctrl_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val != TARGET_UA_INTLCK_CTRL_CLEAR
	 && val != TARGET_UA_INTLCK_CTRL_NO_CLEAR
	 && val != TARGET_UA_INTLCK_CTRL_ESTABLISH_UA) अणु
		pr_err("Illegal value %d\n", val);
		वापस -EINVAL;
	पूर्ण

	अगर (da->da_dev->export_count) अणु
		pr_err("dev[%p]: Unable to change SE Device"
			" UA_INTRLCK_CTRL while export_count is %d\n",
			da->da_dev, da->da_dev->export_count);
		वापस -EINVAL;
	पूर्ण
	da->emulate_ua_पूर्णांकlck_ctrl = val;
	pr_debug("dev[%p]: SE Device UA_INTRLCK_CTRL flag: %d\n",
		da->da_dev, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार emulate_tas_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (da->da_dev->export_count) अणु
		pr_err("dev[%p]: Unable to change SE Device TAS while"
			" export_count is %d\n",
			da->da_dev, da->da_dev->export_count);
		वापस -EINVAL;
	पूर्ण
	da->emulate_tas = flag;
	pr_debug("dev[%p]: SE Device TASK_ABORTED status bit: %s\n",
		da->da_dev, flag ? "Enabled" : "Disabled");

	वापस count;
पूर्ण

अटल sमाप_प्रकार emulate_tpu_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	/*
	 * We expect this value to be non-zero when generic Block Layer
	 * Discard supported is detected iblock_create_virtdevice().
	 */
	अगर (flag && !da->max_unmap_block_desc_count) अणु
		pr_err("Generic Block Discard not supported\n");
		वापस -ENOSYS;
	पूर्ण

	da->emulate_tpu = flag;
	pr_debug("dev[%p]: SE Device Thin Provisioning UNMAP bit: %d\n",
		da->da_dev, flag);
	वापस count;
पूर्ण

अटल sमाप_प्रकार emulate_tpws_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	/*
	 * We expect this value to be non-zero when generic Block Layer
	 * Discard supported is detected iblock_create_virtdevice().
	 */
	अगर (flag && !da->max_unmap_block_desc_count) अणु
		pr_err("Generic Block Discard not supported\n");
		वापस -ENOSYS;
	पूर्ण

	da->emulate_tpws = flag;
	pr_debug("dev[%p]: SE Device Thin Provisioning WRITE_SAME: %d\n",
				da->da_dev, flag);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pi_prot_type_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	पूर्णांक old_prot = da->pi_prot_type, ret;
	काष्ठा se_device *dev = da->da_dev;
	u32 flag;

	ret = kstrtou32(page, 0, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (flag != 0 && flag != 1 && flag != 2 && flag != 3) अणु
		pr_err("Illegal value %d for pi_prot_type\n", flag);
		वापस -EINVAL;
	पूर्ण
	अगर (flag == 2) अणु
		pr_err("DIF TYPE2 protection currently not supported\n");
		वापस -ENOSYS;
	पूर्ण
	अगर (da->hw_pi_prot_type) अणु
		pr_warn("DIF protection enabled on underlying hardware,"
			" ignoring\n");
		वापस count;
	पूर्ण
	अगर (!dev->transport->init_prot || !dev->transport->मुक्त_prot) अणु
		/* 0 is only allowed value क्रम non-supporting backends */
		अगर (flag == 0)
			वापस count;

		pr_err("DIF protection not supported by backend: %s\n",
		       dev->transport->name);
		वापस -ENOSYS;
	पूर्ण
	अगर (!target_dev_configured(dev)) अणु
		pr_err("DIF protection requires device to be configured\n");
		वापस -ENODEV;
	पूर्ण
	अगर (dev->export_count) अणु
		pr_err("dev[%p]: Unable to change SE Device PROT type while"
		       " export_count is %d\n", dev, dev->export_count);
		वापस -EINVAL;
	पूर्ण

	da->pi_prot_type = flag;

	अगर (flag && !old_prot) अणु
		ret = dev->transport->init_prot(dev);
		अगर (ret) अणु
			da->pi_prot_type = old_prot;
			da->pi_prot_verअगरy = (bool) da->pi_prot_type;
			वापस ret;
		पूर्ण

	पूर्ण अन्यथा अगर (!flag && old_prot) अणु
		dev->transport->मुक्त_prot(dev);
	पूर्ण

	da->pi_prot_verअगरy = (bool) da->pi_prot_type;
	pr_debug("dev[%p]: SE Device Protection Type: %d\n", dev, flag);
	वापस count;
पूर्ण

/* always zero, but attr needs to reमुख्य RW to aव्योम userspace अवरोधage */
अटल sमाप_प्रकार pi_prot_क्रमmat_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस snम_लिखो(page, PAGE_SIZE, "0\n");
पूर्ण

अटल sमाप_प्रकार pi_prot_क्रमmat_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	काष्ठा se_device *dev = da->da_dev;
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (!flag)
		वापस count;

	अगर (!dev->transport->क्रमmat_prot) अणु
		pr_err("DIF protection format not supported by backend %s\n",
		       dev->transport->name);
		वापस -ENOSYS;
	पूर्ण
	अगर (!target_dev_configured(dev)) अणु
		pr_err("DIF protection format requires device to be configured\n");
		वापस -ENODEV;
	पूर्ण
	अगर (dev->export_count) अणु
		pr_err("dev[%p]: Unable to format SE Device PROT type while"
		       " export_count is %d\n", dev, dev->export_count);
		वापस -EINVAL;
	पूर्ण

	ret = dev->transport->क्रमmat_prot(dev);
	अगर (ret)
		वापस ret;

	pr_debug("dev[%p]: SE Device Protection Format complete\n", dev);
	वापस count;
पूर्ण

अटल sमाप_प्रकार pi_prot_verअगरy_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (!flag) अणु
		da->pi_prot_verअगरy = flag;
		वापस count;
	पूर्ण
	अगर (da->hw_pi_prot_type) अणु
		pr_warn("DIF protection enabled on underlying hardware,"
			" ignoring\n");
		वापस count;
	पूर्ण
	अगर (!da->pi_prot_type) अणु
		pr_warn("DIF protection not supported by backend, ignoring\n");
		वापस count;
	पूर्ण
	da->pi_prot_verअगरy = flag;

	वापस count;
पूर्ण

अटल sमाप_प्रकार क्रमce_pr_aptpl_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;
	अगर (da->da_dev->export_count) अणु
		pr_err("dev[%p]: Unable to set force_pr_aptpl while"
		       " export_count is %d\n",
		       da->da_dev, da->da_dev->export_count);
		वापस -EINVAL;
	पूर्ण

	da->क्रमce_pr_aptpl = flag;
	pr_debug("dev[%p]: SE Device force_pr_aptpl: %d\n", da->da_dev, flag);
	वापस count;
पूर्ण

अटल sमाप_प्रकार emulate_rest_reord_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (flag != 0) अणु
		prपूर्णांकk(KERN_ERR "dev[%p]: SE Device emulation of restricted"
			" reordering not implemented\n", da->da_dev);
		वापस -ENOSYS;
	पूर्ण
	da->emulate_rest_reord = flag;
	pr_debug("dev[%p]: SE Device emulate_rest_reord: %d\n",
		da->da_dev, flag);
	वापस count;
पूर्ण

अटल sमाप_प्रकार unmap_zeroes_data_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	bool flag;
	पूर्णांक ret;

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (da->da_dev->export_count) अणु
		pr_err("dev[%p]: Unable to change SE Device"
		       " unmap_zeroes_data while export_count is %d\n",
		       da->da_dev, da->da_dev->export_count);
		वापस -EINVAL;
	पूर्ण
	/*
	 * We expect this value to be non-zero when generic Block Layer
	 * Discard supported is detected iblock_configure_device().
	 */
	अगर (flag && !da->max_unmap_block_desc_count) अणु
		pr_err("dev[%p]: Thin Provisioning LBPRZ will not be set"
		       " because max_unmap_block_desc_count is zero\n",
		       da->da_dev);
		वापस -ENOSYS;
	पूर्ण
	da->unmap_zeroes_data = flag;
	pr_debug("dev[%p]: SE Device Thin Provisioning LBPRZ bit: %d\n",
		 da->da_dev, flag);
	वापस count;
पूर्ण

/*
 * Note, this can only be called on unexported SE Device Object.
 */
अटल sमाप_प्रकार queue_depth_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	काष्ठा se_device *dev = da->da_dev;
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (dev->export_count) अणु
		pr_err("dev[%p]: Unable to change SE Device TCQ while"
			" export_count is %d\n",
			dev, dev->export_count);
		वापस -EINVAL;
	पूर्ण
	अगर (!val) अणु
		pr_err("dev[%p]: Illegal ZERO value for queue_depth\n", dev);
		वापस -EINVAL;
	पूर्ण

	अगर (val > dev->dev_attrib.queue_depth) अणु
		अगर (val > dev->dev_attrib.hw_queue_depth) अणु
			pr_err("dev[%p]: Passed queue_depth:"
				" %u exceeds TCM/SE_Device MAX"
				" TCQ: %u\n", dev, val,
				dev->dev_attrib.hw_queue_depth);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	da->queue_depth = dev->queue_depth = val;
	pr_debug("dev[%p]: SE Device TCQ Depth changed to: %u\n", dev, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार optimal_sectors_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (da->da_dev->export_count) अणु
		pr_err("dev[%p]: Unable to change SE Device"
			" optimal_sectors while export_count is %d\n",
			da->da_dev, da->da_dev->export_count);
		वापस -EINVAL;
	पूर्ण
	अगर (val > da->hw_max_sectors) अणु
		pr_err("dev[%p]: Passed optimal_sectors %u cannot be"
			" greater than hw_max_sectors: %u\n",
			da->da_dev, val, da->hw_max_sectors);
		वापस -EINVAL;
	पूर्ण

	da->optimal_sectors = val;
	pr_debug("dev[%p]: SE Device optimal_sectors changed to %u\n",
			da->da_dev, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार block_size_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	u32 val;
	पूर्णांक ret;

	ret = kstrtou32(page, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (da->da_dev->export_count) अणु
		pr_err("dev[%p]: Unable to change SE Device block_size"
			" while export_count is %d\n",
			da->da_dev, da->da_dev->export_count);
		वापस -EINVAL;
	पूर्ण

	अगर (val != 512 && val != 1024 && val != 2048 && val != 4096) अणु
		pr_err("dev[%p]: Illegal value for block_device: %u"
			" for SE device, must be 512, 1024, 2048 or 4096\n",
			da->da_dev, val);
		वापस -EINVAL;
	पूर्ण

	da->block_size = val;
	अगर (da->max_bytes_per_io)
		da->hw_max_sectors = da->max_bytes_per_io / val;

	pr_debug("dev[%p]: SE Device block_size changed to %u\n",
			da->da_dev, val);
	वापस count;
पूर्ण

अटल sमाप_प्रकार alua_support_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	u8 flags = da->da_dev->transport_flags;

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
			flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA ? 0 : 1);
पूर्ण

अटल sमाप_प्रकार alua_support_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	काष्ठा se_device *dev = da->da_dev;
	bool flag;
	पूर्णांक ret;

	अगर (!(dev->transport->transport_flags_changeable &
	      TRANSPORT_FLAG_PASSTHROUGH_ALUA)) अणु
		pr_err("dev[%p]: Unable to change SE Device alua_support:"
			" alua_support has fixed value\n", dev);
		वापस -EINVAL;
	पूर्ण

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (flag)
		dev->transport_flags &= ~TRANSPORT_FLAG_PASSTHROUGH_ALUA;
	अन्यथा
		dev->transport_flags |= TRANSPORT_FLAG_PASSTHROUGH_ALUA;
	वापस count;
पूर्ण

अटल sमाप_प्रकार pgr_support_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	u8 flags = da->da_dev->transport_flags;

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n",
			flags & TRANSPORT_FLAG_PASSTHROUGH_PGR ? 0 : 1);
पूर्ण

अटल sमाप_प्रकार pgr_support_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_dev_attrib *da = to_attrib(item);
	काष्ठा se_device *dev = da->da_dev;
	bool flag;
	पूर्णांक ret;

	अगर (!(dev->transport->transport_flags_changeable &
	      TRANSPORT_FLAG_PASSTHROUGH_PGR)) अणु
		pr_err("dev[%p]: Unable to change SE Device pgr_support:"
			" pgr_support has fixed value\n", dev);
		वापस -EINVAL;
	पूर्ण

	ret = strtobool(page, &flag);
	अगर (ret < 0)
		वापस ret;

	अगर (flag)
		dev->transport_flags &= ~TRANSPORT_FLAG_PASSTHROUGH_PGR;
	अन्यथा
		dev->transport_flags |= TRANSPORT_FLAG_PASSTHROUGH_PGR;
	वापस count;
पूर्ण

CONFIGFS_ATTR(, emulate_model_alias);
CONFIGFS_ATTR(, emulate_dpo);
CONFIGFS_ATTR(, emulate_fua_ग_लिखो);
CONFIGFS_ATTR(, emulate_fua_पढ़ो);
CONFIGFS_ATTR(, emulate_ग_लिखो_cache);
CONFIGFS_ATTR(, emulate_ua_पूर्णांकlck_ctrl);
CONFIGFS_ATTR(, emulate_tas);
CONFIGFS_ATTR(, emulate_tpu);
CONFIGFS_ATTR(, emulate_tpws);
CONFIGFS_ATTR(, emulate_caw);
CONFIGFS_ATTR(, emulate_3pc);
CONFIGFS_ATTR(, emulate_pr);
CONFIGFS_ATTR(, pi_prot_type);
CONFIGFS_ATTR_RO(, hw_pi_prot_type);
CONFIGFS_ATTR(, pi_prot_क्रमmat);
CONFIGFS_ATTR(, pi_prot_verअगरy);
CONFIGFS_ATTR(, enक्रमce_pr_isids);
CONFIGFS_ATTR(, is_nonrot);
CONFIGFS_ATTR(, emulate_rest_reord);
CONFIGFS_ATTR(, क्रमce_pr_aptpl);
CONFIGFS_ATTR_RO(, hw_block_size);
CONFIGFS_ATTR(, block_size);
CONFIGFS_ATTR_RO(, hw_max_sectors);
CONFIGFS_ATTR(, optimal_sectors);
CONFIGFS_ATTR_RO(, hw_queue_depth);
CONFIGFS_ATTR(, queue_depth);
CONFIGFS_ATTR(, max_unmap_lba_count);
CONFIGFS_ATTR(, max_unmap_block_desc_count);
CONFIGFS_ATTR(, unmap_granularity);
CONFIGFS_ATTR(, unmap_granularity_alignment);
CONFIGFS_ATTR(, unmap_zeroes_data);
CONFIGFS_ATTR(, max_ग_लिखो_same_len);
CONFIGFS_ATTR(, alua_support);
CONFIGFS_ATTR(, pgr_support);

/*
 * dev_attrib attributes क्रम devices using the target core SBC/SPC
 * पूर्णांकerpreter.  Any backend using spc_parse_cdb should be using
 * these.
 */
काष्ठा configfs_attribute *sbc_attrib_attrs[] = अणु
	&attr_emulate_model_alias,
	&attr_emulate_dpo,
	&attr_emulate_fua_ग_लिखो,
	&attr_emulate_fua_पढ़ो,
	&attr_emulate_ग_लिखो_cache,
	&attr_emulate_ua_पूर्णांकlck_ctrl,
	&attr_emulate_tas,
	&attr_emulate_tpu,
	&attr_emulate_tpws,
	&attr_emulate_caw,
	&attr_emulate_3pc,
	&attr_emulate_pr,
	&attr_pi_prot_type,
	&attr_hw_pi_prot_type,
	&attr_pi_prot_क्रमmat,
	&attr_pi_prot_verअगरy,
	&attr_enक्रमce_pr_isids,
	&attr_is_nonrot,
	&attr_emulate_rest_reord,
	&attr_क्रमce_pr_aptpl,
	&attr_hw_block_size,
	&attr_block_size,
	&attr_hw_max_sectors,
	&attr_optimal_sectors,
	&attr_hw_queue_depth,
	&attr_queue_depth,
	&attr_max_unmap_lba_count,
	&attr_max_unmap_block_desc_count,
	&attr_unmap_granularity,
	&attr_unmap_granularity_alignment,
	&attr_unmap_zeroes_data,
	&attr_max_ग_लिखो_same_len,
	&attr_alua_support,
	&attr_pgr_support,
	शून्य,
पूर्ण;
EXPORT_SYMBOL(sbc_attrib_attrs);

/*
 * Minimal dev_attrib attributes क्रम devices passing through CDBs.
 * In this हाल we only provide a few पढ़ो-only attributes क्रम
 * backwards compatibility.
 */
काष्ठा configfs_attribute *passthrough_attrib_attrs[] = अणु
	&attr_hw_pi_prot_type,
	&attr_hw_block_size,
	&attr_hw_max_sectors,
	&attr_hw_queue_depth,
	&attr_emulate_pr,
	&attr_alua_support,
	&attr_pgr_support,
	शून्य,
पूर्ण;
EXPORT_SYMBOL(passthrough_attrib_attrs);

/*
 * pr related dev_attrib attributes क्रम devices passing through CDBs,
 * but allowing in core pr emulation.
 */
काष्ठा configfs_attribute *passthrough_pr_attrib_attrs[] = अणु
	&attr_enक्रमce_pr_isids,
	&attr_क्रमce_pr_aptpl,
	शून्य,
पूर्ण;
EXPORT_SYMBOL(passthrough_pr_attrib_attrs);

TB_CIT_SETUP_DRV(dev_attrib, शून्य, शून्य);
TB_CIT_SETUP_DRV(dev_action, शून्य, शून्य);

/* End functions क्रम काष्ठा config_item_type tb_dev_attrib_cit */

/*  Start functions क्रम काष्ठा config_item_type tb_dev_wwn_cit */

अटल काष्ठा t10_wwn *to_t10_wwn(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा t10_wwn, t10_wwn_group);
पूर्ण

अटल sमाप_प्रकार target_check_inquiry_data(अक्षर *buf)
अणु
	माप_प्रकार len;
	पूर्णांक i;

	len = म_माप(buf);

	/*
	 * SPC 4.3.1:
	 * ASCII data fields shall contain only ASCII prपूर्णांकable अक्षरacters
	 * (i.e., code values 20h to 7Eh) and may be terminated with one or
	 * more ASCII null (00h) अक्षरacters.
	 */
	क्रम (i = 0; i < len; i++) अणु
		अगर (buf[i] < 0x20 || buf[i] > 0x7E) अणु
			pr_err("Emulated T10 Inquiry Data contains non-ASCII-printable characters\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

/*
 * STANDARD and VPD page 0x83 T10 Venकरोr Identअगरication
 */
अटल sमाप_प्रकार target_wwn_venकरोr_id_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", &to_t10_wwn(item)->venकरोr[0]);
पूर्ण

अटल sमाप_प्रकार target_wwn_venकरोr_id_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_wwn *t10_wwn = to_t10_wwn(item);
	काष्ठा se_device *dev = t10_wwn->t10_dev;
	/* +2 to allow क्रम a trailing (stripped) '\n' and null-terminator */
	अचिन्हित अक्षर buf[INQUIRY_VENDOR_LEN + 2];
	अक्षर *stripped = शून्य;
	माप_प्रकार len;
	sमाप_प्रकार ret;

	len = strlcpy(buf, page, माप(buf));
	अगर (len < माप(buf)) अणु
		/* Strip any newline added from userspace. */
		stripped = म_मालाip(buf);
		len = म_माप(stripped);
	पूर्ण
	अगर (len > INQUIRY_VENDOR_LEN) अणु
		pr_err("Emulated T10 Vendor Identification exceeds"
			" INQUIRY_VENDOR_LEN: " __stringअगरy(INQUIRY_VENDOR_LEN)
			"\n");
		वापस -EOVERFLOW;
	पूर्ण

	ret = target_check_inquiry_data(stripped);

	अगर (ret < 0)
		वापस ret;

	/*
	 * Check to see अगर any active exports exist.  If they करो exist, fail
	 * here as changing this inक्रमmation on the fly (underneath the
	 * initiator side OS dependent multipath code) could cause negative
	 * effects.
	 */
	अगर (dev->export_count) अणु
		pr_err("Unable to set T10 Vendor Identification while"
			" active %d exports exist\n", dev->export_count);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(माप(dev->t10_wwn.venकरोr) != INQUIRY_VENDOR_LEN + 1);
	strlcpy(dev->t10_wwn.venकरोr, stripped, माप(dev->t10_wwn.venकरोr));

	pr_debug("Target_Core_ConfigFS: Set emulated T10 Vendor Identification:"
		 " %s\n", dev->t10_wwn.venकरोr);

	वापस count;
पूर्ण

अटल sमाप_प्रकार target_wwn_product_id_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", &to_t10_wwn(item)->model[0]);
पूर्ण

अटल sमाप_प्रकार target_wwn_product_id_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_wwn *t10_wwn = to_t10_wwn(item);
	काष्ठा se_device *dev = t10_wwn->t10_dev;
	/* +2 to allow क्रम a trailing (stripped) '\n' and null-terminator */
	अचिन्हित अक्षर buf[INQUIRY_MODEL_LEN + 2];
	अक्षर *stripped = शून्य;
	माप_प्रकार len;
	sमाप_प्रकार ret;

	len = strlcpy(buf, page, माप(buf));
	अगर (len < माप(buf)) अणु
		/* Strip any newline added from userspace. */
		stripped = म_मालाip(buf);
		len = म_माप(stripped);
	पूर्ण
	अगर (len > INQUIRY_MODEL_LEN) अणु
		pr_err("Emulated T10 Vendor exceeds INQUIRY_MODEL_LEN: "
			 __stringअगरy(INQUIRY_MODEL_LEN)
			"\n");
		वापस -EOVERFLOW;
	पूर्ण

	ret = target_check_inquiry_data(stripped);

	अगर (ret < 0)
		वापस ret;

	/*
	 * Check to see अगर any active exports exist.  If they करो exist, fail
	 * here as changing this inक्रमmation on the fly (underneath the
	 * initiator side OS dependent multipath code) could cause negative
	 * effects.
	 */
	अगर (dev->export_count) अणु
		pr_err("Unable to set T10 Model while active %d exports exist\n",
			dev->export_count);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(माप(dev->t10_wwn.model) != INQUIRY_MODEL_LEN + 1);
	strlcpy(dev->t10_wwn.model, stripped, माप(dev->t10_wwn.model));

	pr_debug("Target_Core_ConfigFS: Set emulated T10 Model Identification: %s\n",
		 dev->t10_wwn.model);

	वापस count;
पूर्ण

अटल sमाप_प्रकार target_wwn_revision_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n", &to_t10_wwn(item)->revision[0]);
पूर्ण

अटल sमाप_प्रकार target_wwn_revision_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_wwn *t10_wwn = to_t10_wwn(item);
	काष्ठा se_device *dev = t10_wwn->t10_dev;
	/* +2 to allow क्रम a trailing (stripped) '\n' and null-terminator */
	अचिन्हित अक्षर buf[INQUIRY_REVISION_LEN + 2];
	अक्षर *stripped = शून्य;
	माप_प्रकार len;
	sमाप_प्रकार ret;

	len = strlcpy(buf, page, माप(buf));
	अगर (len < माप(buf)) अणु
		/* Strip any newline added from userspace. */
		stripped = म_मालाip(buf);
		len = म_माप(stripped);
	पूर्ण
	अगर (len > INQUIRY_REVISION_LEN) अणु
		pr_err("Emulated T10 Revision exceeds INQUIRY_REVISION_LEN: "
			 __stringअगरy(INQUIRY_REVISION_LEN)
			"\n");
		वापस -EOVERFLOW;
	पूर्ण

	ret = target_check_inquiry_data(stripped);

	अगर (ret < 0)
		वापस ret;

	/*
	 * Check to see अगर any active exports exist.  If they करो exist, fail
	 * here as changing this inक्रमmation on the fly (underneath the
	 * initiator side OS dependent multipath code) could cause negative
	 * effects.
	 */
	अगर (dev->export_count) अणु
		pr_err("Unable to set T10 Revision while active %d exports exist\n",
			dev->export_count);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(माप(dev->t10_wwn.revision) != INQUIRY_REVISION_LEN + 1);
	strlcpy(dev->t10_wwn.revision, stripped, माप(dev->t10_wwn.revision));

	pr_debug("Target_Core_ConfigFS: Set emulated T10 Revision: %s\n",
		 dev->t10_wwn.revision);

	वापस count;
पूर्ण

/*
 * VPD page 0x80 Unit serial
 */
अटल sमाप_प्रकार target_wwn_vpd_unit_serial_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "T10 VPD Unit Serial Number: %s\n",
		&to_t10_wwn(item)->unit_serial[0]);
पूर्ण

अटल sमाप_प्रकार target_wwn_vpd_unit_serial_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_wwn *t10_wwn = to_t10_wwn(item);
	काष्ठा se_device *dev = t10_wwn->t10_dev;
	अचिन्हित अक्षर buf[INQUIRY_VPD_SERIAL_LEN] = अणु पूर्ण;

	/*
	 * If Linux/SCSI subप्रणाली_api_t plugin got a VPD Unit Serial
	 * from the काष्ठा scsi_device level firmware, करो not allow
	 * VPD Unit Serial to be emulated.
	 *
	 * Note this काष्ठा scsi_device could also be emulating VPD
	 * inक्रमmation from its drivers/scsi LLD.  But क्रम now we assume
	 * it is करोing 'the right thing' wrt a world wide unique
	 * VPD Unit Serial Number that OS dependent multipath can depend on.
	 */
	अगर (dev->dev_flags & DF_FIRMWARE_VPD_UNIT_SERIAL) अणु
		pr_err("Underlying SCSI device firmware provided VPD"
			" Unit Serial, ignoring request\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (म_माप(page) >= INQUIRY_VPD_SERIAL_LEN) अणु
		pr_err("Emulated VPD Unit Serial exceeds"
		" INQUIRY_VPD_SERIAL_LEN: %d\n", INQUIRY_VPD_SERIAL_LEN);
		वापस -EOVERFLOW;
	पूर्ण
	/*
	 * Check to see अगर any active $FABRIC_MOD exports exist.  If they
	 * करो exist, fail here as changing this inक्रमmation on the fly
	 * (underneath the initiator side OS dependent multipath code)
	 * could cause negative effects.
	 */
	अगर (dev->export_count) अणु
		pr_err("Unable to set VPD Unit Serial while"
			" active %d $FABRIC_MOD exports exist\n",
			dev->export_count);
		वापस -EINVAL;
	पूर्ण

	/*
	 * This currently assumes ASCII encoding क्रम emulated VPD Unit Serial.
	 *
	 * Also, strip any newline added from the userspace
	 * echo $UUID > $TARGET/$HBA/$STORAGE_OBJECT/wwn/vpd_unit_serial
	 */
	snम_लिखो(buf, INQUIRY_VPD_SERIAL_LEN, "%s", page);
	snम_लिखो(dev->t10_wwn.unit_serial, INQUIRY_VPD_SERIAL_LEN,
			"%s", म_मालाip(buf));
	dev->dev_flags |= DF_EMULATED_VPD_UNIT_SERIAL;

	pr_debug("Target_Core_ConfigFS: Set emulated VPD Unit Serial:"
			" %s\n", dev->t10_wwn.unit_serial);

	वापस count;
पूर्ण

/*
 * VPD page 0x83 Protocol Identअगरier
 */
अटल sमाप_प्रकार target_wwn_vpd_protocol_identअगरier_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा t10_wwn *t10_wwn = to_t10_wwn(item);
	काष्ठा t10_vpd *vpd;
	अचिन्हित अक्षर buf[VPD_TMP_BUF_SIZE] = अणु पूर्ण;
	sमाप_प्रकार len = 0;

	spin_lock(&t10_wwn->t10_vpd_lock);
	list_क्रम_each_entry(vpd, &t10_wwn->t10_vpd_list, vpd_list) अणु
		अगर (!vpd->protocol_identअगरier_set)
			जारी;

		transport_dump_vpd_proto_id(vpd, buf, VPD_TMP_BUF_SIZE);

		अगर (len + म_माप(buf) >= PAGE_SIZE)
			अवरोध;

		len += प्र_लिखो(page+len, "%s", buf);
	पूर्ण
	spin_unlock(&t10_wwn->t10_vpd_lock);

	वापस len;
पूर्ण

/*
 * Generic wrapper क्रम dumping VPD identअगरiers by association.
 */
#घोषणा DEF_DEV_WWN_ASSOC_SHOW(_name, _assoc)				\
अटल sमाप_प्रकार target_wwn_##_name##_show(काष्ठा config_item *item,	\
		अक्षर *page)						\
अणु									\
	काष्ठा t10_wwn *t10_wwn = to_t10_wwn(item);			\
	काष्ठा t10_vpd *vpd;						\
	अचिन्हित अक्षर buf[VPD_TMP_BUF_SIZE];				\
	sमाप_प्रकार len = 0;						\
									\
	spin_lock(&t10_wwn->t10_vpd_lock);				\
	list_क्रम_each_entry(vpd, &t10_wwn->t10_vpd_list, vpd_list) अणु	\
		अगर (vpd->association != _assoc)				\
			जारी;					\
									\
		स_रखो(buf, 0, VPD_TMP_BUF_SIZE);			\
		transport_dump_vpd_assoc(vpd, buf, VPD_TMP_BUF_SIZE);	\
		अगर (len + म_माप(buf) >= PAGE_SIZE)			\
			अवरोध;						\
		len += प्र_लिखो(page+len, "%s", buf);			\
									\
		स_रखो(buf, 0, VPD_TMP_BUF_SIZE);			\
		transport_dump_vpd_ident_type(vpd, buf, VPD_TMP_BUF_SIZE); \
		अगर (len + म_माप(buf) >= PAGE_SIZE)			\
			अवरोध;						\
		len += प्र_लिखो(page+len, "%s", buf);			\
									\
		स_रखो(buf, 0, VPD_TMP_BUF_SIZE);			\
		transport_dump_vpd_ident(vpd, buf, VPD_TMP_BUF_SIZE); \
		अगर (len + म_माप(buf) >= PAGE_SIZE)			\
			अवरोध;						\
		len += प्र_लिखो(page+len, "%s", buf);			\
	पूर्ण								\
	spin_unlock(&t10_wwn->t10_vpd_lock);				\
									\
	वापस len;							\
पूर्ण

/* VPD page 0x83 Association: Logical Unit */
DEF_DEV_WWN_ASSOC_SHOW(vpd_assoc_logical_unit, 0x00);
/* VPD page 0x83 Association: Target Port */
DEF_DEV_WWN_ASSOC_SHOW(vpd_assoc_target_port, 0x10);
/* VPD page 0x83 Association: SCSI Target Device */
DEF_DEV_WWN_ASSOC_SHOW(vpd_assoc_scsi_target_device, 0x20);

CONFIGFS_ATTR(target_wwn_, venकरोr_id);
CONFIGFS_ATTR(target_wwn_, product_id);
CONFIGFS_ATTR(target_wwn_, revision);
CONFIGFS_ATTR(target_wwn_, vpd_unit_serial);
CONFIGFS_ATTR_RO(target_wwn_, vpd_protocol_identअगरier);
CONFIGFS_ATTR_RO(target_wwn_, vpd_assoc_logical_unit);
CONFIGFS_ATTR_RO(target_wwn_, vpd_assoc_target_port);
CONFIGFS_ATTR_RO(target_wwn_, vpd_assoc_scsi_target_device);

अटल काष्ठा configfs_attribute *target_core_dev_wwn_attrs[] = अणु
	&target_wwn_attr_venकरोr_id,
	&target_wwn_attr_product_id,
	&target_wwn_attr_revision,
	&target_wwn_attr_vpd_unit_serial,
	&target_wwn_attr_vpd_protocol_identअगरier,
	&target_wwn_attr_vpd_assoc_logical_unit,
	&target_wwn_attr_vpd_assoc_target_port,
	&target_wwn_attr_vpd_assoc_scsi_target_device,
	शून्य,
पूर्ण;

TB_CIT_SETUP(dev_wwn, शून्य, शून्य, target_core_dev_wwn_attrs);

/*  End functions क्रम काष्ठा config_item_type tb_dev_wwn_cit */

/*  Start functions क्रम काष्ठा config_item_type tb_dev_pr_cit */

अटल काष्ठा se_device *pr_to_dev(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_device,
			dev_pr_group);
पूर्ण

अटल sमाप_प्रकार target_core_dev_pr_show_spc3_res(काष्ठा se_device *dev,
		अक्षर *page)
अणु
	काष्ठा se_node_acl *se_nacl;
	काष्ठा t10_pr_registration *pr_reg;
	अक्षर i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;

	pr_reg = dev->dev_pr_res_holder;
	अगर (!pr_reg)
		वापस प्र_लिखो(page, "No SPC-3 Reservation holder\n");

	se_nacl = pr_reg->pr_reg_nacl;
	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);

	वापस प्र_लिखो(page, "SPC-3 Reservation: %s Initiator: %s%s\n",
		se_nacl->se_tpg->se_tpg_tfo->fabric_name,
		se_nacl->initiatorname, i_buf);
पूर्ण

अटल sमाप_प्रकार target_core_dev_pr_show_spc2_res(काष्ठा se_device *dev,
		अक्षर *page)
अणु
	काष्ठा se_session *sess = dev->reservation_holder;
	काष्ठा se_node_acl *se_nacl;
	sमाप_प्रकार len;

	अगर (sess) अणु
		se_nacl = sess->se_node_acl;
		len = प्र_लिखो(page,
			      "SPC-2 Reservation: %s Initiator: %s\n",
			      se_nacl->se_tpg->se_tpg_tfo->fabric_name,
			      se_nacl->initiatorname);
	पूर्ण अन्यथा अणु
		len = प्र_लिखो(page, "No SPC-2 Reservation holder\n");
	पूर्ण
	वापस len;
पूर्ण

अटल sमाप_प्रकार target_pr_res_holder_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);
	पूर्णांक ret;

	अगर (!dev->dev_attrib.emulate_pr)
		वापस प्र_लिखो(page, "SPC_RESERVATIONS_DISABLED\n");

	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR)
		वापस प्र_लिखो(page, "Passthrough\n");

	spin_lock(&dev->dev_reservation_lock);
	अगर (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		ret = target_core_dev_pr_show_spc2_res(dev, page);
	अन्यथा
		ret = target_core_dev_pr_show_spc3_res(dev, page);
	spin_unlock(&dev->dev_reservation_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार target_pr_res_pr_all_tgt_pts_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);
	sमाप_प्रकार len = 0;

	spin_lock(&dev->dev_reservation_lock);
	अगर (!dev->dev_pr_res_holder) अणु
		len = प्र_लिखो(page, "No SPC-3 Reservation holder\n");
	पूर्ण अन्यथा अगर (dev->dev_pr_res_holder->pr_reg_all_tg_pt) अणु
		len = प्र_लिखो(page, "SPC-3 Reservation: All Target"
			" Ports registration\n");
	पूर्ण अन्यथा अणु
		len = प्र_लिखो(page, "SPC-3 Reservation: Single"
			" Target Port registration\n");
	पूर्ण

	spin_unlock(&dev->dev_reservation_lock);
	वापस len;
पूर्ण

अटल sमाप_प्रकार target_pr_res_pr_generation_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "0x%08x\n", pr_to_dev(item)->t10_pr.pr_generation);
पूर्ण


अटल sमाप_प्रकार target_pr_res_pr_holder_tg_port_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);
	काष्ठा se_node_acl *se_nacl;
	काष्ठा se_portal_group *se_tpg;
	काष्ठा t10_pr_registration *pr_reg;
	स्थिर काष्ठा target_core_fabric_ops *tfo;
	sमाप_प्रकार len = 0;

	spin_lock(&dev->dev_reservation_lock);
	pr_reg = dev->dev_pr_res_holder;
	अगर (!pr_reg) अणु
		len = प्र_लिखो(page, "No SPC-3 Reservation holder\n");
		जाओ out_unlock;
	पूर्ण

	se_nacl = pr_reg->pr_reg_nacl;
	se_tpg = se_nacl->se_tpg;
	tfo = se_tpg->se_tpg_tfo;

	len += प्र_लिखो(page+len, "SPC-3 Reservation: %s"
		" Target Node Endpoint: %s\n", tfo->fabric_name,
		tfo->tpg_get_wwn(se_tpg));
	len += प्र_लिखो(page+len, "SPC-3 Reservation: Relative Port"
		" Identifier Tag: %hu %s Portal Group Tag: %hu"
		" %s Logical Unit: %llu\n", pr_reg->tg_pt_sep_rtpi,
		tfo->fabric_name, tfo->tpg_get_tag(se_tpg),
		tfo->fabric_name, pr_reg->pr_aptpl_target_lun);

out_unlock:
	spin_unlock(&dev->dev_reservation_lock);
	वापस len;
पूर्ण


अटल sमाप_प्रकार target_pr_res_pr_रेजिस्टरed_i_pts_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);
	स्थिर काष्ठा target_core_fabric_ops *tfo;
	काष्ठा t10_pr_registration *pr_reg;
	अचिन्हित अक्षर buf[384];
	अक्षर i_buf[PR_REG_ISID_ID_LEN];
	sमाप_प्रकार len = 0;
	पूर्णांक reg_count = 0;

	len += प्र_लिखो(page+len, "SPC-3 PR Registrations:\n");

	spin_lock(&dev->t10_pr.registration_lock);
	list_क्रम_each_entry(pr_reg, &dev->t10_pr.registration_list,
			pr_reg_list) अणु

		स_रखो(buf, 0, 384);
		स_रखो(i_buf, 0, PR_REG_ISID_ID_LEN);
		tfo = pr_reg->pr_reg_nacl->se_tpg->se_tpg_tfo;
		core_pr_dump_initiator_port(pr_reg, i_buf,
					PR_REG_ISID_ID_LEN);
		प्र_लिखो(buf, "%s Node: %s%s Key: 0x%016Lx PRgen: 0x%08x\n",
			tfo->fabric_name,
			pr_reg->pr_reg_nacl->initiatorname, i_buf, pr_reg->pr_res_key,
			pr_reg->pr_res_generation);

		अगर (len + म_माप(buf) >= PAGE_SIZE)
			अवरोध;

		len += प्र_लिखो(page+len, "%s", buf);
		reg_count++;
	पूर्ण
	spin_unlock(&dev->t10_pr.registration_lock);

	अगर (!reg_count)
		len += प्र_लिखो(page+len, "None\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार target_pr_res_pr_type_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);
	काष्ठा t10_pr_registration *pr_reg;
	sमाप_प्रकार len = 0;

	spin_lock(&dev->dev_reservation_lock);
	pr_reg = dev->dev_pr_res_holder;
	अगर (pr_reg) अणु
		len = प्र_लिखो(page, "SPC-3 Reservation Type: %s\n",
			core_scsi3_pr_dump_type(pr_reg->pr_res_type));
	पूर्ण अन्यथा अणु
		len = प्र_लिखो(page, "No SPC-3 Reservation holder\n");
	पूर्ण

	spin_unlock(&dev->dev_reservation_lock);
	वापस len;
पूर्ण

अटल sमाप_प्रकार target_pr_res_type_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);

	अगर (!dev->dev_attrib.emulate_pr)
		वापस प्र_लिखो(page, "SPC_RESERVATIONS_DISABLED\n");
	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR)
		वापस प्र_लिखो(page, "SPC_PASSTHROUGH\n");
	अगर (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		वापस प्र_लिखो(page, "SPC2_RESERVATIONS\n");

	वापस प्र_लिखो(page, "SPC3_PERSISTENT_RESERVATIONS\n");
पूर्ण

अटल sमाप_प्रकार target_pr_res_aptpl_active_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);

	अगर (!dev->dev_attrib.emulate_pr ||
	    (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR))
		वापस 0;

	वापस प्र_लिखो(page, "APTPL Bit Status: %s\n",
		(dev->t10_pr.pr_aptpl_active) ? "Activated" : "Disabled");
पूर्ण

अटल sमाप_प्रकार target_pr_res_aptpl_metadata_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);

	अगर (!dev->dev_attrib.emulate_pr ||
	    (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR))
		वापस 0;

	वापस प्र_लिखो(page, "Ready to process PR APTPL metadata..\n");
पूर्ण

क्रमागत अणु
	Opt_initiator_fabric, Opt_initiator_node, Opt_initiator_sid,
	Opt_sa_res_key, Opt_res_holder, Opt_res_type, Opt_res_scope,
	Opt_res_all_tg_pt, Opt_mapped_lun, Opt_target_fabric,
	Opt_target_node, Opt_tpgt, Opt_port_rtpi, Opt_target_lun, Opt_err
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_initiator_fabric, "initiator_fabric=%s"पूर्ण,
	अणुOpt_initiator_node, "initiator_node=%s"पूर्ण,
	अणुOpt_initiator_sid, "initiator_sid=%s"पूर्ण,
	अणुOpt_sa_res_key, "sa_res_key=%s"पूर्ण,
	अणुOpt_res_holder, "res_holder=%d"पूर्ण,
	अणुOpt_res_type, "res_type=%d"पूर्ण,
	अणुOpt_res_scope, "res_scope=%d"पूर्ण,
	अणुOpt_res_all_tg_pt, "res_all_tg_pt=%d"पूर्ण,
	अणुOpt_mapped_lun, "mapped_lun=%u"पूर्ण,
	अणुOpt_target_fabric, "target_fabric=%s"पूर्ण,
	अणुOpt_target_node, "target_node=%s"पूर्ण,
	अणुOpt_tpgt, "tpgt=%d"पूर्ण,
	अणुOpt_port_rtpi, "port_rtpi=%d"पूर्ण,
	अणुOpt_target_lun, "target_lun=%u"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल sमाप_प्रकार target_pr_res_aptpl_metadata_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_device *dev = pr_to_dev(item);
	अचिन्हित अक्षर *i_fabric = शून्य, *i_port = शून्य, *isid = शून्य;
	अचिन्हित अक्षर *t_fabric = शून्य, *t_port = शून्य;
	अक्षर *orig, *ptr, *opts;
	substring_t args[MAX_OPT_ARGS];
	अचिन्हित दीर्घ दीर्घ पंचांगp_ll;
	u64 sa_res_key = 0;
	u64 mapped_lun = 0, target_lun = 0;
	पूर्णांक ret = -1, res_holder = 0, all_tg_pt = 0, arg, token;
	u16 tpgt = 0;
	u8 type = 0;

	अगर (!dev->dev_attrib.emulate_pr ||
	    (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR))
		वापस count;
	अगर (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		वापस count;

	अगर (dev->export_count) अणु
		pr_debug("Unable to process APTPL metadata while"
			" active fabric exports exist\n");
		वापस -EINVAL;
	पूर्ण

	opts = kstrdup(page, GFP_KERNEL);
	अगर (!opts)
		वापस -ENOMEM;

	orig = opts;
	जबतक ((ptr = strsep(&opts, ",\n")) != शून्य) अणु
		अगर (!*ptr)
			जारी;

		token = match_token(ptr, tokens, args);
		चयन (token) अणु
		हाल Opt_initiator_fabric:
			i_fabric = match_strdup(args);
			अगर (!i_fabric) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल Opt_initiator_node:
			i_port = match_strdup(args);
			अगर (!i_port) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अगर (म_माप(i_port) >= PR_APTPL_MAX_IPORT_LEN) अणु
				pr_err("APTPL metadata initiator_node="
					" exceeds PR_APTPL_MAX_IPORT_LEN: %d\n",
					PR_APTPL_MAX_IPORT_LEN);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल Opt_initiator_sid:
			isid = match_strdup(args);
			अगर (!isid) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अगर (म_माप(isid) >= PR_REG_ISID_LEN) अणु
				pr_err("APTPL metadata initiator_isid"
					"= exceeds PR_REG_ISID_LEN: %d\n",
					PR_REG_ISID_LEN);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल Opt_sa_res_key:
			ret = match_u64(args,  &पंचांगp_ll);
			अगर (ret < 0) अणु
				pr_err("kstrtoull() failed for sa_res_key=\n");
				जाओ out;
			पूर्ण
			sa_res_key = (u64)पंचांगp_ll;
			अवरोध;
		/*
		 * PR APTPL Metadata क्रम Reservation
		 */
		हाल Opt_res_holder:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			res_holder = arg;
			अवरोध;
		हाल Opt_res_type:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			type = (u8)arg;
			अवरोध;
		हाल Opt_res_scope:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			अवरोध;
		हाल Opt_res_all_tg_pt:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			all_tg_pt = (पूर्णांक)arg;
			अवरोध;
		हाल Opt_mapped_lun:
			ret = match_u64(args, &पंचांगp_ll);
			अगर (ret)
				जाओ out;
			mapped_lun = (u64)पंचांगp_ll;
			अवरोध;
		/*
		 * PR APTPL Metadata क्रम Target Port
		 */
		हाल Opt_target_fabric:
			t_fabric = match_strdup(args);
			अगर (!t_fabric) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल Opt_target_node:
			t_port = match_strdup(args);
			अगर (!t_port) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अगर (म_माप(t_port) >= PR_APTPL_MAX_TPORT_LEN) अणु
				pr_err("APTPL metadata target_node="
					" exceeds PR_APTPL_MAX_TPORT_LEN: %d\n",
					PR_APTPL_MAX_TPORT_LEN);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल Opt_tpgt:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			tpgt = (u16)arg;
			अवरोध;
		हाल Opt_port_rtpi:
			ret = match_पूर्णांक(args, &arg);
			अगर (ret)
				जाओ out;
			अवरोध;
		हाल Opt_target_lun:
			ret = match_u64(args, &पंचांगp_ll);
			अगर (ret)
				जाओ out;
			target_lun = (u64)पंचांगp_ll;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!i_port || !t_port || !sa_res_key) अणु
		pr_err("Illegal parameters for APTPL registration\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (res_holder && !(type)) अणु
		pr_err("Illegal PR type: 0x%02x for reservation"
				" holder\n", type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = core_scsi3_alloc_aptpl_registration(&dev->t10_pr, sa_res_key,
			i_port, isid, mapped_lun, t_port, tpgt, target_lun,
			res_holder, all_tg_pt, type);
out:
	kमुक्त(i_fabric);
	kमुक्त(i_port);
	kमुक्त(isid);
	kमुक्त(t_fabric);
	kमुक्त(t_port);
	kमुक्त(orig);
	वापस (ret == 0) ? count : ret;
पूर्ण


CONFIGFS_ATTR_RO(target_pr_, res_holder);
CONFIGFS_ATTR_RO(target_pr_, res_pr_all_tgt_pts);
CONFIGFS_ATTR_RO(target_pr_, res_pr_generation);
CONFIGFS_ATTR_RO(target_pr_, res_pr_holder_tg_port);
CONFIGFS_ATTR_RO(target_pr_, res_pr_रेजिस्टरed_i_pts);
CONFIGFS_ATTR_RO(target_pr_, res_pr_type);
CONFIGFS_ATTR_RO(target_pr_, res_type);
CONFIGFS_ATTR_RO(target_pr_, res_aptpl_active);
CONFIGFS_ATTR(target_pr_, res_aptpl_metadata);

अटल काष्ठा configfs_attribute *target_core_dev_pr_attrs[] = अणु
	&target_pr_attr_res_holder,
	&target_pr_attr_res_pr_all_tgt_pts,
	&target_pr_attr_res_pr_generation,
	&target_pr_attr_res_pr_holder_tg_port,
	&target_pr_attr_res_pr_रेजिस्टरed_i_pts,
	&target_pr_attr_res_pr_type,
	&target_pr_attr_res_type,
	&target_pr_attr_res_aptpl_active,
	&target_pr_attr_res_aptpl_metadata,
	शून्य,
पूर्ण;

TB_CIT_SETUP(dev_pr, शून्य, शून्य, target_core_dev_pr_attrs);

/*  End functions क्रम काष्ठा config_item_type tb_dev_pr_cit */

/*  Start functions क्रम काष्ठा config_item_type tb_dev_cit */

अटल अंतरभूत काष्ठा se_device *to_device(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_device, dev_group);
पूर्ण

अटल sमाप_प्रकार target_dev_info_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_device(item);
	पूर्णांक bl = 0;
	sमाप_प्रकार पढ़ो_bytes = 0;

	transport_dump_dev_state(dev, page, &bl);
	पढ़ो_bytes += bl;
	पढ़ो_bytes += dev->transport->show_configfs_dev_params(dev,
			page+पढ़ो_bytes);
	वापस पढ़ो_bytes;
पूर्ण

अटल sमाप_प्रकार target_dev_control_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_device *dev = to_device(item);

	वापस dev->transport->set_configfs_dev_params(dev, page, count);
पूर्ण

अटल sमाप_प्रकार target_dev_alias_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_device(item);

	अगर (!(dev->dev_flags & DF_USING_ALIAS))
		वापस 0;

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", dev->dev_alias);
पूर्ण

अटल sमाप_प्रकार target_dev_alias_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_device *dev = to_device(item);
	काष्ठा se_hba *hba = dev->se_hba;
	sमाप_प्रकार पढ़ो_bytes;

	अगर (count > (SE_DEV_ALIAS_LEN-1)) अणु
		pr_err("alias count: %d exceeds"
			" SE_DEV_ALIAS_LEN-1: %u\n", (पूर्णांक)count,
			SE_DEV_ALIAS_LEN-1);
		वापस -EINVAL;
	पूर्ण

	पढ़ो_bytes = snम_लिखो(&dev->dev_alias[0], SE_DEV_ALIAS_LEN, "%s", page);
	अगर (!पढ़ो_bytes)
		वापस -EINVAL;
	अगर (dev->dev_alias[पढ़ो_bytes - 1] == '\n')
		dev->dev_alias[पढ़ो_bytes - 1] = '\0';

	dev->dev_flags |= DF_USING_ALIAS;

	pr_debug("Target_Core_ConfigFS: %s/%s set alias: %s\n",
		config_item_name(&hba->hba_group.cg_item),
		config_item_name(&dev->dev_group.cg_item),
		dev->dev_alias);

	वापस पढ़ो_bytes;
पूर्ण

अटल sमाप_प्रकार target_dev_udev_path_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_device(item);

	अगर (!(dev->dev_flags & DF_USING_UDEV_PATH))
		वापस 0;

	वापस snम_लिखो(page, PAGE_SIZE, "%s\n", dev->udev_path);
पूर्ण

अटल sमाप_प्रकार target_dev_udev_path_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_device *dev = to_device(item);
	काष्ठा se_hba *hba = dev->se_hba;
	sमाप_प्रकार पढ़ो_bytes;

	अगर (count > (SE_UDEV_PATH_LEN-1)) अणु
		pr_err("udev_path count: %d exceeds"
			" SE_UDEV_PATH_LEN-1: %u\n", (पूर्णांक)count,
			SE_UDEV_PATH_LEN-1);
		वापस -EINVAL;
	पूर्ण

	पढ़ो_bytes = snम_लिखो(&dev->udev_path[0], SE_UDEV_PATH_LEN,
			"%s", page);
	अगर (!पढ़ो_bytes)
		वापस -EINVAL;
	अगर (dev->udev_path[पढ़ो_bytes - 1] == '\n')
		dev->udev_path[पढ़ो_bytes - 1] = '\0';

	dev->dev_flags |= DF_USING_UDEV_PATH;

	pr_debug("Target_Core_ConfigFS: %s/%s set udev_path: %s\n",
		config_item_name(&hba->hba_group.cg_item),
		config_item_name(&dev->dev_group.cg_item),
		dev->udev_path);

	वापस पढ़ो_bytes;
पूर्ण

अटल sमाप_प्रकार target_dev_enable_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_device(item);

	वापस snम_लिखो(page, PAGE_SIZE, "%d\n", target_dev_configured(dev));
पूर्ण

अटल sमाप_प्रकार target_dev_enable_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_device *dev = to_device(item);
	अक्षर *ptr;
	पूर्णांक ret;

	ptr = म_माला(page, "1");
	अगर (!ptr) अणु
		pr_err("For dev_enable ops, only valid value"
				" is \"1\"\n");
		वापस -EINVAL;
	पूर्ण

	ret = target_configure_device(dev);
	अगर (ret)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार target_dev_alua_lu_gp_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_device(item);
	काष्ठा config_item *lu_ci;
	काष्ठा t10_alua_lu_gp *lu_gp;
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem;
	sमाप_प्रकार len = 0;

	lu_gp_mem = dev->dev_alua_lu_gp_mem;
	अगर (!lu_gp_mem)
		वापस 0;

	spin_lock(&lu_gp_mem->lu_gp_mem_lock);
	lu_gp = lu_gp_mem->lu_gp;
	अगर (lu_gp) अणु
		lu_ci = &lu_gp->lu_gp_group.cg_item;
		len += प्र_लिखो(page, "LU Group Alias: %s\nLU Group ID: %hu\n",
			config_item_name(lu_ci), lu_gp->lu_gp_id);
	पूर्ण
	spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार target_dev_alua_lu_gp_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_device *dev = to_device(item);
	काष्ठा se_hba *hba = dev->se_hba;
	काष्ठा t10_alua_lu_gp *lu_gp = शून्य, *lu_gp_new = शून्य;
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem;
	अचिन्हित अक्षर buf[LU_GROUP_NAME_BUF] = अणु पूर्ण;
	पूर्णांक move = 0;

	lu_gp_mem = dev->dev_alua_lu_gp_mem;
	अगर (!lu_gp_mem)
		वापस count;

	अगर (count > LU_GROUP_NAME_BUF) अणु
		pr_err("ALUA LU Group Alias too large!\n");
		वापस -EINVAL;
	पूर्ण
	स_नकल(buf, page, count);
	/*
	 * Any ALUA logical unit alias besides "NULL" means we will be
	 * making a new group association.
	 */
	अगर (म_भेद(म_मालाip(buf), "NULL")) अणु
		/*
		 * core_alua_get_lu_gp_by_name() will increment reference to
		 * काष्ठा t10_alua_lu_gp.  This reference is released with
		 * core_alua_get_lu_gp_by_name below().
		 */
		lu_gp_new = core_alua_get_lu_gp_by_name(म_मालाip(buf));
		अगर (!lu_gp_new)
			वापस -ENODEV;
	पूर्ण

	spin_lock(&lu_gp_mem->lu_gp_mem_lock);
	lu_gp = lu_gp_mem->lu_gp;
	अगर (lu_gp) अणु
		/*
		 * Clearing an existing lu_gp association, and replacing
		 * with शून्य
		 */
		अगर (!lu_gp_new) अणु
			pr_debug("Target_Core_ConfigFS: Releasing %s/%s"
				" from ALUA LU Group: core/alua/lu_gps/%s, ID:"
				" %hu\n",
				config_item_name(&hba->hba_group.cg_item),
				config_item_name(&dev->dev_group.cg_item),
				config_item_name(&lu_gp->lu_gp_group.cg_item),
				lu_gp->lu_gp_id);

			__core_alua_drop_lu_gp_mem(lu_gp_mem, lu_gp);
			spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

			वापस count;
		पूर्ण
		/*
		 * Removing existing association of lu_gp_mem with lu_gp
		 */
		__core_alua_drop_lu_gp_mem(lu_gp_mem, lu_gp);
		move = 1;
	पूर्ण
	/*
	 * Associate lu_gp_mem with lu_gp_new.
	 */
	__core_alua_attach_lu_gp_mem(lu_gp_mem, lu_gp_new);
	spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

	pr_debug("Target_Core_ConfigFS: %s %s/%s to ALUA LU Group:"
		" core/alua/lu_gps/%s, ID: %hu\n",
		(move) ? "Moving" : "Adding",
		config_item_name(&hba->hba_group.cg_item),
		config_item_name(&dev->dev_group.cg_item),
		config_item_name(&lu_gp_new->lu_gp_group.cg_item),
		lu_gp_new->lu_gp_id);

	core_alua_put_lu_gp_from_name(lu_gp_new);
	वापस count;
पूर्ण

अटल sमाप_प्रकार target_dev_lba_map_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_device *dev = to_device(item);
	काष्ठा t10_alua_lba_map *map;
	काष्ठा t10_alua_lba_map_member *mem;
	अक्षर *b = page;
	पूर्णांक bl = 0;
	अक्षर state;

	spin_lock(&dev->t10_alua.lba_map_lock);
	अगर (!list_empty(&dev->t10_alua.lba_map_list))
	    bl += प्र_लिखो(b + bl, "%u %u\n",
			  dev->t10_alua.lba_map_segment_size,
			  dev->t10_alua.lba_map_segment_multiplier);
	list_क्रम_each_entry(map, &dev->t10_alua.lba_map_list, lba_map_list) अणु
		bl += प्र_लिखो(b + bl, "%llu %llu",
			      map->lba_map_first_lba, map->lba_map_last_lba);
		list_क्रम_each_entry(mem, &map->lba_map_mem_list,
				    lba_map_mem_list) अणु
			चयन (mem->lba_map_mem_alua_state) अणु
			हाल ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED:
				state = 'O';
				अवरोध;
			हाल ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
				state = 'A';
				अवरोध;
			हाल ALUA_ACCESS_STATE_STANDBY:
				state = 'S';
				अवरोध;
			हाल ALUA_ACCESS_STATE_UNAVAILABLE:
				state = 'U';
				अवरोध;
			शेष:
				state = '.';
				अवरोध;
			पूर्ण
			bl += प्र_लिखो(b + bl, " %d:%c",
				      mem->lba_map_mem_alua_pg_id, state);
		पूर्ण
		bl += प्र_लिखो(b + bl, "\n");
	पूर्ण
	spin_unlock(&dev->t10_alua.lba_map_lock);
	वापस bl;
पूर्ण

अटल sमाप_प्रकार target_dev_lba_map_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_device *dev = to_device(item);
	काष्ठा t10_alua_lba_map *lba_map = शून्य;
	काष्ठा list_head lba_list;
	अक्षर *map_entries, *orig, *ptr;
	अक्षर state;
	पूर्णांक pg_num = -1, pg;
	पूर्णांक ret = 0, num = 0, pg_id, alua_state;
	अचिन्हित दीर्घ start_lba = -1, end_lba = -1;
	अचिन्हित दीर्घ segment_size = -1, segment_mult = -1;

	orig = map_entries = kstrdup(page, GFP_KERNEL);
	अगर (!map_entries)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&lba_list);
	जबतक ((ptr = strsep(&map_entries, "\n")) != शून्य) अणु
		अगर (!*ptr)
			जारी;

		अगर (num == 0) अणु
			अगर (माला_पूछो(ptr, "%lu %lu\n",
				   &segment_size, &segment_mult) != 2) अणु
				pr_err("Invalid line %d\n", num);
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			num++;
			जारी;
		पूर्ण
		अगर (माला_पूछो(ptr, "%lu %lu", &start_lba, &end_lba) != 2) अणु
			pr_err("Invalid line %d\n", num);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ptr = म_अक्षर(ptr, ' ');
		अगर (!ptr) अणु
			pr_err("Invalid line %d, missing end lba\n", num);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ptr++;
		ptr = म_अक्षर(ptr, ' ');
		अगर (!ptr) अणु
			pr_err("Invalid line %d, missing state definitions\n",
			       num);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ptr++;
		lba_map = core_alua_allocate_lba_map(&lba_list,
						     start_lba, end_lba);
		अगर (IS_ERR(lba_map)) अणु
			ret = PTR_ERR(lba_map);
			अवरोध;
		पूर्ण
		pg = 0;
		जबतक (माला_पूछो(ptr, "%d:%c", &pg_id, &state) == 2) अणु
			चयन (state) अणु
			हाल 'O':
				alua_state = ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED;
				अवरोध;
			हाल 'A':
				alua_state = ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED;
				अवरोध;
			हाल 'S':
				alua_state = ALUA_ACCESS_STATE_STANDBY;
				अवरोध;
			हाल 'U':
				alua_state = ALUA_ACCESS_STATE_UNAVAILABLE;
				अवरोध;
			शेष:
				pr_err("Invalid ALUA state '%c'\n", state);
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			ret = core_alua_allocate_lba_map_mem(lba_map,
							     pg_id, alua_state);
			अगर (ret) अणु
				pr_err("Invalid target descriptor %d:%c "
				       "at line %d\n",
				       pg_id, state, num);
				अवरोध;
			पूर्ण
			pg++;
			ptr = म_अक्षर(ptr, ' ');
			अगर (ptr)
				ptr++;
			अन्यथा
				अवरोध;
		पूर्ण
		अगर (pg_num == -1)
		    pg_num = pg;
		अन्यथा अगर (pg != pg_num) अणु
			pr_err("Only %d from %d port groups definitions "
			       "at line %d\n", pg, pg_num, num);
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		num++;
	पूर्ण
out:
	अगर (ret) अणु
		core_alua_मुक्त_lba_map(&lba_list);
		count = ret;
	पूर्ण अन्यथा
		core_alua_set_lba_map(dev, &lba_list,
				      segment_size, segment_mult);
	kमुक्त(orig);
	वापस count;
पूर्ण

CONFIGFS_ATTR_RO(target_dev_, info);
CONFIGFS_ATTR_WO(target_dev_, control);
CONFIGFS_ATTR(target_dev_, alias);
CONFIGFS_ATTR(target_dev_, udev_path);
CONFIGFS_ATTR(target_dev_, enable);
CONFIGFS_ATTR(target_dev_, alua_lu_gp);
CONFIGFS_ATTR(target_dev_, lba_map);

अटल काष्ठा configfs_attribute *target_core_dev_attrs[] = अणु
	&target_dev_attr_info,
	&target_dev_attr_control,
	&target_dev_attr_alias,
	&target_dev_attr_udev_path,
	&target_dev_attr_enable,
	&target_dev_attr_alua_lu_gp,
	&target_dev_attr_lba_map,
	शून्य,
पूर्ण;

अटल व्योम target_core_dev_release(काष्ठा config_item *item)
अणु
	काष्ठा config_group *dev_cg = to_config_group(item);
	काष्ठा se_device *dev =
		container_of(dev_cg, काष्ठा se_device, dev_group);

	target_मुक्त_device(dev);
पूर्ण

/*
 * Used in target_core_fabric_configfs.c to verअगरy valid se_device symlink
 * within target_fabric_port_link()
 */
काष्ठा configfs_item_operations target_core_dev_item_ops = अणु
	.release		= target_core_dev_release,
पूर्ण;

TB_CIT_SETUP(dev, &target_core_dev_item_ops, शून्य, target_core_dev_attrs);

/* End functions क्रम काष्ठा config_item_type tb_dev_cit */

/* Start functions क्रम काष्ठा config_item_type target_core_alua_lu_gp_cit */

अटल अंतरभूत काष्ठा t10_alua_lu_gp *to_lu_gp(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा t10_alua_lu_gp,
			lu_gp_group);
पूर्ण

अटल sमाप_प्रकार target_lu_gp_lu_gp_id_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp = to_lu_gp(item);

	अगर (!lu_gp->lu_gp_valid_id)
		वापस 0;
	वापस प्र_लिखो(page, "%hu\n", lu_gp->lu_gp_id);
पूर्ण

अटल sमाप_प्रकार target_lu_gp_lu_gp_id_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp = to_lu_gp(item);
	काष्ठा config_group *alua_lu_gp_cg = &lu_gp->lu_gp_group;
	अचिन्हित दीर्घ lu_gp_id;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &lu_gp_id);
	अगर (ret < 0) अणु
		pr_err("kstrtoul() returned %d for"
			" lu_gp_id\n", ret);
		वापस ret;
	पूर्ण
	अगर (lu_gp_id > 0x0000ffff) अणु
		pr_err("ALUA lu_gp_id: %lu exceeds maximum:"
			" 0x0000ffff\n", lu_gp_id);
		वापस -EINVAL;
	पूर्ण

	ret = core_alua_set_lu_gp_id(lu_gp, (u16)lu_gp_id);
	अगर (ret < 0)
		वापस -EINVAL;

	pr_debug("Target_Core_ConfigFS: Set ALUA Logical Unit"
		" Group: core/alua/lu_gps/%s to ID: %hu\n",
		config_item_name(&alua_lu_gp_cg->cg_item),
		lu_gp->lu_gp_id);

	वापस count;
पूर्ण

अटल sमाप_प्रकार target_lu_gp_members_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp = to_lu_gp(item);
	काष्ठा se_device *dev;
	काष्ठा se_hba *hba;
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem;
	sमाप_प्रकार len = 0, cur_len;
	अचिन्हित अक्षर buf[LU_GROUP_NAME_BUF] = अणु पूर्ण;

	spin_lock(&lu_gp->lu_gp_lock);
	list_क्रम_each_entry(lu_gp_mem, &lu_gp->lu_gp_mem_list, lu_gp_mem_list) अणु
		dev = lu_gp_mem->lu_gp_mem_dev;
		hba = dev->se_hba;

		cur_len = snम_लिखो(buf, LU_GROUP_NAME_BUF, "%s/%s\n",
			config_item_name(&hba->hba_group.cg_item),
			config_item_name(&dev->dev_group.cg_item));
		cur_len++; /* Extra byte क्रम शून्य terminator */

		अगर ((cur_len + len) > PAGE_SIZE) अणु
			pr_warn("Ran out of lu_gp_show_attr"
				"_members buffer\n");
			अवरोध;
		पूर्ण
		स_नकल(page+len, buf, cur_len);
		len += cur_len;
	पूर्ण
	spin_unlock(&lu_gp->lu_gp_lock);

	वापस len;
पूर्ण

CONFIGFS_ATTR(target_lu_gp_, lu_gp_id);
CONFIGFS_ATTR_RO(target_lu_gp_, members);

अटल काष्ठा configfs_attribute *target_core_alua_lu_gp_attrs[] = अणु
	&target_lu_gp_attr_lu_gp_id,
	&target_lu_gp_attr_members,
	शून्य,
पूर्ण;

अटल व्योम target_core_alua_lu_gp_release(काष्ठा config_item *item)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp = container_of(to_config_group(item),
			काष्ठा t10_alua_lu_gp, lu_gp_group);

	core_alua_मुक्त_lu_gp(lu_gp);
पूर्ण

अटल काष्ठा configfs_item_operations target_core_alua_lu_gp_ops = अणु
	.release		= target_core_alua_lu_gp_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_core_alua_lu_gp_cit = अणु
	.ct_item_ops		= &target_core_alua_lu_gp_ops,
	.ct_attrs		= target_core_alua_lu_gp_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/* End functions क्रम काष्ठा config_item_type target_core_alua_lu_gp_cit */

/* Start functions क्रम काष्ठा config_item_type target_core_alua_lu_gps_cit */

अटल काष्ठा config_group *target_core_alua_create_lu_gp(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp;
	काष्ठा config_group *alua_lu_gp_cg = शून्य;
	काष्ठा config_item *alua_lu_gp_ci = शून्य;

	lu_gp = core_alua_allocate_lu_gp(name, 0);
	अगर (IS_ERR(lu_gp))
		वापस शून्य;

	alua_lu_gp_cg = &lu_gp->lu_gp_group;
	alua_lu_gp_ci = &alua_lu_gp_cg->cg_item;

	config_group_init_type_name(alua_lu_gp_cg, name,
			&target_core_alua_lu_gp_cit);

	pr_debug("Target_Core_ConfigFS: Allocated ALUA Logical Unit"
		" Group: core/alua/lu_gps/%s\n",
		config_item_name(alua_lu_gp_ci));

	वापस alua_lu_gp_cg;

पूर्ण

अटल व्योम target_core_alua_drop_lu_gp(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp = container_of(to_config_group(item),
			काष्ठा t10_alua_lu_gp, lu_gp_group);

	pr_debug("Target_Core_ConfigFS: Releasing ALUA Logical Unit"
		" Group: core/alua/lu_gps/%s, ID: %hu\n",
		config_item_name(item), lu_gp->lu_gp_id);
	/*
	 * core_alua_मुक्त_lu_gp() is called from target_core_alua_lu_gp_ops->release()
	 * -> target_core_alua_lu_gp_release()
	 */
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_core_alua_lu_gps_group_ops = अणु
	.make_group		= &target_core_alua_create_lu_gp,
	.drop_item		= &target_core_alua_drop_lu_gp,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_core_alua_lu_gps_cit = अणु
	.ct_item_ops		= शून्य,
	.ct_group_ops		= &target_core_alua_lu_gps_group_ops,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/* End functions क्रम काष्ठा config_item_type target_core_alua_lu_gps_cit */

/* Start functions क्रम काष्ठा config_item_type target_core_alua_tg_pt_gp_cit */

अटल अंतरभूत काष्ठा t10_alua_tg_pt_gp *to_tg_pt_gp(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा t10_alua_tg_pt_gp,
			tg_pt_gp_group);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_alua_access_state_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n",
		       to_tg_pt_gp(item)->tg_pt_gp_alua_access_state);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_alua_access_state_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	काष्ठा se_device *dev = tg_pt_gp->tg_pt_gp_dev;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक new_state, ret;

	अगर (!tg_pt_gp->tg_pt_gp_valid_id) अणु
		pr_err("Unable to do implicit ALUA on invalid tg_pt_gp ID\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!target_dev_configured(dev)) अणु
		pr_err("Unable to set alua_access_state while device is"
		       " not configured\n");
		वापस -ENODEV;
	पूर्ण

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract new ALUA access state from"
				" %s\n", page);
		वापस ret;
	पूर्ण
	new_state = (पूर्णांक)पंचांगp;

	अगर (!(tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_IMPLICIT_ALUA)) अणु
		pr_err("Unable to process implicit configfs ALUA"
			" transition while TPGS_IMPLICIT_ALUA is disabled\n");
		वापस -EINVAL;
	पूर्ण
	अगर (tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_EXPLICIT_ALUA &&
	    new_state == ALUA_ACCESS_STATE_LBA_DEPENDENT) अणु
		/* LBA DEPENDENT is only allowed with implicit ALUA */
		pr_err("Unable to process implicit configfs ALUA transition"
		       " while explicit ALUA management is enabled\n");
		वापस -EINVAL;
	पूर्ण

	ret = core_alua_करो_port_transition(tg_pt_gp, dev,
					शून्य, शून्य, new_state, 0);
	वापस (!ret) ? count : -EINVAL;
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_alua_access_status_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	वापस प्र_लिखो(page, "%s\n",
		core_alua_dump_status(tg_pt_gp->tg_pt_gp_alua_access_status));
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_alua_access_status_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक new_status, ret;

	अगर (!tg_pt_gp->tg_pt_gp_valid_id) अणु
		pr_err("Unable to set ALUA access status on invalid tg_pt_gp ID\n");
		वापस -EINVAL;
	पूर्ण

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract new ALUA access status"
				" from %s\n", page);
		वापस ret;
	पूर्ण
	new_status = (पूर्णांक)पंचांगp;

	अगर ((new_status != ALUA_STATUS_NONE) &&
	    (new_status != ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG) &&
	    (new_status != ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA)) अणु
		pr_err("Illegal ALUA access status: 0x%02x\n",
				new_status);
		वापस -EINVAL;
	पूर्ण

	tg_pt_gp->tg_pt_gp_alua_access_status = new_status;
	वापस count;
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_alua_access_type_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस core_alua_show_access_type(to_tg_pt_gp(item), page);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_alua_access_type_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस core_alua_store_access_type(to_tg_pt_gp(item), page, count);
पूर्ण

#घोषणा ALUA_SUPPORTED_STATE_ATTR(_name, _bit)				\
अटल sमाप_प्रकार target_tg_pt_gp_alua_support_##_name##_show(		\
		काष्ठा config_item *item, अक्षर *p)			\
अणु									\
	काष्ठा t10_alua_tg_pt_gp *t = to_tg_pt_gp(item);		\
	वापस प्र_लिखो(p, "%d\n",					\
		!!(t->tg_pt_gp_alua_supported_states & _bit));		\
पूर्ण									\
									\
अटल sमाप_प्रकार target_tg_pt_gp_alua_support_##_name##_store(		\
		काष्ठा config_item *item, स्थिर अक्षर *p, माप_प्रकार c)	\
अणु									\
	काष्ठा t10_alua_tg_pt_gp *t = to_tg_pt_gp(item);		\
	अचिन्हित दीर्घ पंचांगp;						\
	पूर्णांक ret;							\
									\
	अगर (!t->tg_pt_gp_valid_id) अणु					\
		pr_err("Unable to set " #_name " ALUA state on invalid tg_pt_gp ID\n"); \
		वापस -EINVAL;						\
	पूर्ण								\
									\
	ret = kम_से_अदीर्घ(p, 0, &पंचांगp);					\
	अगर (ret < 0) अणु							\
		pr_err("Invalid value '%s', must be '0' or '1'\n", p);	\
		वापस -EINVAL;						\
	पूर्ण								\
	अगर (पंचांगp > 1) अणु							\
		pr_err("Invalid value '%ld', must be '0' or '1'\n", पंचांगp); \
		वापस -EINVAL;						\
	पूर्ण								\
	अगर (पंचांगp)							\
		t->tg_pt_gp_alua_supported_states |= _bit;		\
	अन्यथा								\
		t->tg_pt_gp_alua_supported_states &= ~_bit;		\
									\
	वापस c;							\
पूर्ण

ALUA_SUPPORTED_STATE_ATTR(transitioning, ALUA_T_SUP);
ALUA_SUPPORTED_STATE_ATTR(offline, ALUA_O_SUP);
ALUA_SUPPORTED_STATE_ATTR(lba_dependent, ALUA_LBD_SUP);
ALUA_SUPPORTED_STATE_ATTR(unavailable, ALUA_U_SUP);
ALUA_SUPPORTED_STATE_ATTR(standby, ALUA_S_SUP);
ALUA_SUPPORTED_STATE_ATTR(active_optimized, ALUA_AO_SUP);
ALUA_SUPPORTED_STATE_ATTR(active_nonoptimized, ALUA_AN_SUP);

अटल sमाप_प्रकार target_tg_pt_gp_alua_ग_लिखो_metadata_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n",
		to_tg_pt_gp(item)->tg_pt_gp_ग_लिखो_metadata);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_alua_ग_लिखो_metadata_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract alua_write_metadata\n");
		वापस ret;
	पूर्ण

	अगर ((पंचांगp != 0) && (पंचांगp != 1)) अणु
		pr_err("Illegal value for alua_write_metadata:"
			" %lu\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण
	tg_pt_gp->tg_pt_gp_ग_लिखो_metadata = (पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_nonop_delay_msecs_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस core_alua_show_nonop_delay_msecs(to_tg_pt_gp(item), page);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_nonop_delay_msecs_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस core_alua_store_nonop_delay_msecs(to_tg_pt_gp(item), page,
			count);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_trans_delay_msecs_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस core_alua_show_trans_delay_msecs(to_tg_pt_gp(item), page);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_trans_delay_msecs_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस core_alua_store_trans_delay_msecs(to_tg_pt_gp(item), page,
			count);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_implicit_trans_secs_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	वापस core_alua_show_implicit_trans_secs(to_tg_pt_gp(item), page);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_implicit_trans_secs_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस core_alua_store_implicit_trans_secs(to_tg_pt_gp(item), page,
			count);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_preferred_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस core_alua_show_preferred_bit(to_tg_pt_gp(item), page);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_preferred_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस core_alua_store_preferred_bit(to_tg_pt_gp(item), page, count);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_tg_pt_gp_id_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);

	अगर (!tg_pt_gp->tg_pt_gp_valid_id)
		वापस 0;
	वापस प्र_लिखो(page, "%hu\n", tg_pt_gp->tg_pt_gp_id);
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_tg_pt_gp_id_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	काष्ठा config_group *alua_tg_pt_gp_cg = &tg_pt_gp->tg_pt_gp_group;
	अचिन्हित दीर्घ tg_pt_gp_id;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &tg_pt_gp_id);
	अगर (ret < 0) अणु
		pr_err("ALUA tg_pt_gp_id: invalid value '%s' for tg_pt_gp_id\n",
		       page);
		वापस ret;
	पूर्ण
	अगर (tg_pt_gp_id > 0x0000ffff) अणु
		pr_err("ALUA tg_pt_gp_id: %lu exceeds maximum: 0x0000ffff\n",
		       tg_pt_gp_id);
		वापस -EINVAL;
	पूर्ण

	ret = core_alua_set_tg_pt_gp_id(tg_pt_gp, (u16)tg_pt_gp_id);
	अगर (ret < 0)
		वापस -EINVAL;

	pr_debug("Target_Core_ConfigFS: Set ALUA Target Port Group: "
		"core/alua/tg_pt_gps/%s to ID: %hu\n",
		config_item_name(&alua_tg_pt_gp_cg->cg_item),
		tg_pt_gp->tg_pt_gp_id);

	वापस count;
पूर्ण

अटल sमाप_प्रकार target_tg_pt_gp_members_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = to_tg_pt_gp(item);
	काष्ठा se_lun *lun;
	sमाप_प्रकार len = 0, cur_len;
	अचिन्हित अक्षर buf[TG_PT_GROUP_NAME_BUF] = अणु पूर्ण;

	spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	list_क्रम_each_entry(lun, &tg_pt_gp->tg_pt_gp_lun_list,
			lun_tg_pt_gp_link) अणु
		काष्ठा se_portal_group *tpg = lun->lun_tpg;

		cur_len = snम_लिखो(buf, TG_PT_GROUP_NAME_BUF, "%s/%s/tpgt_%hu"
			"/%s\n", tpg->se_tpg_tfo->fabric_name,
			tpg->se_tpg_tfo->tpg_get_wwn(tpg),
			tpg->se_tpg_tfo->tpg_get_tag(tpg),
			config_item_name(&lun->lun_group.cg_item));
		cur_len++; /* Extra byte क्रम शून्य terminator */

		अगर ((cur_len + len) > PAGE_SIZE) अणु
			pr_warn("Ran out of lu_gp_show_attr"
				"_members buffer\n");
			अवरोध;
		पूर्ण
		स_नकल(page+len, buf, cur_len);
		len += cur_len;
	पूर्ण
	spin_unlock(&tg_pt_gp->tg_pt_gp_lock);

	वापस len;
पूर्ण

CONFIGFS_ATTR(target_tg_pt_gp_, alua_access_state);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_access_status);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_access_type);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_support_transitioning);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_support_offline);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_support_lba_dependent);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_support_unavailable);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_support_standby);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_support_active_optimized);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_support_active_nonoptimized);
CONFIGFS_ATTR(target_tg_pt_gp_, alua_ग_लिखो_metadata);
CONFIGFS_ATTR(target_tg_pt_gp_, nonop_delay_msecs);
CONFIGFS_ATTR(target_tg_pt_gp_, trans_delay_msecs);
CONFIGFS_ATTR(target_tg_pt_gp_, implicit_trans_secs);
CONFIGFS_ATTR(target_tg_pt_gp_, preferred);
CONFIGFS_ATTR(target_tg_pt_gp_, tg_pt_gp_id);
CONFIGFS_ATTR_RO(target_tg_pt_gp_, members);

अटल काष्ठा configfs_attribute *target_core_alua_tg_pt_gp_attrs[] = अणु
	&target_tg_pt_gp_attr_alua_access_state,
	&target_tg_pt_gp_attr_alua_access_status,
	&target_tg_pt_gp_attr_alua_access_type,
	&target_tg_pt_gp_attr_alua_support_transitioning,
	&target_tg_pt_gp_attr_alua_support_offline,
	&target_tg_pt_gp_attr_alua_support_lba_dependent,
	&target_tg_pt_gp_attr_alua_support_unavailable,
	&target_tg_pt_gp_attr_alua_support_standby,
	&target_tg_pt_gp_attr_alua_support_active_nonoptimized,
	&target_tg_pt_gp_attr_alua_support_active_optimized,
	&target_tg_pt_gp_attr_alua_ग_लिखो_metadata,
	&target_tg_pt_gp_attr_nonop_delay_msecs,
	&target_tg_pt_gp_attr_trans_delay_msecs,
	&target_tg_pt_gp_attr_implicit_trans_secs,
	&target_tg_pt_gp_attr_preferred,
	&target_tg_pt_gp_attr_tg_pt_gp_id,
	&target_tg_pt_gp_attr_members,
	शून्य,
पूर्ण;

अटल व्योम target_core_alua_tg_pt_gp_release(काष्ठा config_item *item)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = container_of(to_config_group(item),
			काष्ठा t10_alua_tg_pt_gp, tg_pt_gp_group);

	core_alua_मुक्त_tg_pt_gp(tg_pt_gp);
पूर्ण

अटल काष्ठा configfs_item_operations target_core_alua_tg_pt_gp_ops = अणु
	.release		= target_core_alua_tg_pt_gp_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_core_alua_tg_pt_gp_cit = अणु
	.ct_item_ops		= &target_core_alua_tg_pt_gp_ops,
	.ct_attrs		= target_core_alua_tg_pt_gp_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/* End functions क्रम काष्ठा config_item_type target_core_alua_tg_pt_gp_cit */

/* Start functions क्रम काष्ठा config_item_type tb_alua_tg_pt_gps_cit */

अटल काष्ठा config_group *target_core_alua_create_tg_pt_gp(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा t10_alua *alua = container_of(group, काष्ठा t10_alua,
					alua_tg_pt_gps_group);
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	काष्ठा config_group *alua_tg_pt_gp_cg = शून्य;
	काष्ठा config_item *alua_tg_pt_gp_ci = शून्य;

	tg_pt_gp = core_alua_allocate_tg_pt_gp(alua->t10_dev, name, 0);
	अगर (!tg_pt_gp)
		वापस शून्य;

	alua_tg_pt_gp_cg = &tg_pt_gp->tg_pt_gp_group;
	alua_tg_pt_gp_ci = &alua_tg_pt_gp_cg->cg_item;

	config_group_init_type_name(alua_tg_pt_gp_cg, name,
			&target_core_alua_tg_pt_gp_cit);

	pr_debug("Target_Core_ConfigFS: Allocated ALUA Target Port"
		" Group: alua/tg_pt_gps/%s\n",
		config_item_name(alua_tg_pt_gp_ci));

	वापस alua_tg_pt_gp_cg;
पूर्ण

अटल व्योम target_core_alua_drop_tg_pt_gp(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = container_of(to_config_group(item),
			काष्ठा t10_alua_tg_pt_gp, tg_pt_gp_group);

	pr_debug("Target_Core_ConfigFS: Releasing ALUA Target Port"
		" Group: alua/tg_pt_gps/%s, ID: %hu\n",
		config_item_name(item), tg_pt_gp->tg_pt_gp_id);
	/*
	 * core_alua_मुक्त_tg_pt_gp() is called from target_core_alua_tg_pt_gp_ops->release()
	 * -> target_core_alua_tg_pt_gp_release().
	 */
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_core_alua_tg_pt_gps_group_ops = अणु
	.make_group		= &target_core_alua_create_tg_pt_gp,
	.drop_item		= &target_core_alua_drop_tg_pt_gp,
पूर्ण;

TB_CIT_SETUP(dev_alua_tg_pt_gps, शून्य, &target_core_alua_tg_pt_gps_group_ops, शून्य);

/* End functions क्रम काष्ठा config_item_type tb_alua_tg_pt_gps_cit */

/* Start functions क्रम काष्ठा config_item_type target_core_alua_cit */

/*
 * target_core_alua_cit is a ConfigFS group that lives under
 * /sys/kernel/config/target/core/alua.  There are शेष groups
 * core/alua/lu_gps and core/alua/tg_pt_gps that are attached to
 * target_core_alua_cit in target_core_init_configfs() below.
 */
अटल स्थिर काष्ठा config_item_type target_core_alua_cit = अणु
	.ct_item_ops		= शून्य,
	.ct_attrs		= शून्य,
	.ct_owner		= THIS_MODULE,
पूर्ण;

/* End functions क्रम काष्ठा config_item_type target_core_alua_cit */

/* Start functions क्रम काष्ठा config_item_type tb_dev_stat_cit */

अटल काष्ठा config_group *target_core_stat_सूची_गढ़ो(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

अटल व्योम target_core_stat_सूची_हटाओ(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	वापस;
पूर्ण

अटल काष्ठा configfs_group_operations target_core_stat_group_ops = अणु
	.make_group		= &target_core_stat_सूची_गढ़ो,
	.drop_item		= &target_core_stat_सूची_हटाओ,
पूर्ण;

TB_CIT_SETUP(dev_stat, शून्य, &target_core_stat_group_ops, शून्य);

/* End functions क्रम काष्ठा config_item_type tb_dev_stat_cit */

/* Start functions क्रम काष्ठा config_item_type target_core_hba_cit */

अटल काष्ठा config_group *target_core_make_subdev(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	काष्ठा config_item *hba_ci = &group->cg_item;
	काष्ठा se_hba *hba = item_to_hba(hba_ci);
	काष्ठा target_backend *tb = hba->backend;
	काष्ठा se_device *dev;
	पूर्णांक त्रुटि_सं = -ENOMEM, ret;

	ret = mutex_lock_पूर्णांकerruptible(&hba->hba_access_mutex);
	अगर (ret)
		वापस ERR_PTR(ret);

	dev = target_alloc_device(hba, name);
	अगर (!dev)
		जाओ out_unlock;

	config_group_init_type_name(&dev->dev_group, name, &tb->tb_dev_cit);

	config_group_init_type_name(&dev->dev_action_group, "action",
			&tb->tb_dev_action_cit);
	configfs_add_शेष_group(&dev->dev_action_group, &dev->dev_group);

	config_group_init_type_name(&dev->dev_attrib.da_group, "attrib",
			&tb->tb_dev_attrib_cit);
	configfs_add_शेष_group(&dev->dev_attrib.da_group, &dev->dev_group);

	config_group_init_type_name(&dev->dev_pr_group, "pr",
			&tb->tb_dev_pr_cit);
	configfs_add_शेष_group(&dev->dev_pr_group, &dev->dev_group);

	config_group_init_type_name(&dev->t10_wwn.t10_wwn_group, "wwn",
			&tb->tb_dev_wwn_cit);
	configfs_add_शेष_group(&dev->t10_wwn.t10_wwn_group,
			&dev->dev_group);

	config_group_init_type_name(&dev->t10_alua.alua_tg_pt_gps_group,
			"alua", &tb->tb_dev_alua_tg_pt_gps_cit);
	configfs_add_शेष_group(&dev->t10_alua.alua_tg_pt_gps_group,
			&dev->dev_group);

	config_group_init_type_name(&dev->dev_stat_grps.stat_group,
			"statistics", &tb->tb_dev_stat_cit);
	configfs_add_शेष_group(&dev->dev_stat_grps.stat_group,
			&dev->dev_group);

	/*
	 * Add core/$HBA/$DEV/alua/शेष_tg_pt_gp
	 */
	tg_pt_gp = core_alua_allocate_tg_pt_gp(dev, "default_tg_pt_gp", 1);
	अगर (!tg_pt_gp)
		जाओ out_मुक्त_device;
	dev->t10_alua.शेष_tg_pt_gp = tg_pt_gp;

	config_group_init_type_name(&tg_pt_gp->tg_pt_gp_group,
			"default_tg_pt_gp", &target_core_alua_tg_pt_gp_cit);
	configfs_add_शेष_group(&tg_pt_gp->tg_pt_gp_group,
			&dev->t10_alua.alua_tg_pt_gps_group);

	/*
	 * Add core/$HBA/$DEV/statistics/ शेष groups
	 */
	target_stat_setup_dev_शेष_groups(dev);

	mutex_unlock(&hba->hba_access_mutex);
	वापस &dev->dev_group;

out_मुक्त_device:
	target_मुक्त_device(dev);
out_unlock:
	mutex_unlock(&hba->hba_access_mutex);
	वापस ERR_PTR(त्रुटि_सं);
पूर्ण

अटल व्योम target_core_drop_subdev(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	काष्ठा config_group *dev_cg = to_config_group(item);
	काष्ठा se_device *dev =
		container_of(dev_cg, काष्ठा se_device, dev_group);
	काष्ठा se_hba *hba;

	hba = item_to_hba(&dev->se_hba->hba_group.cg_item);

	mutex_lock(&hba->hba_access_mutex);

	configfs_हटाओ_शेष_groups(&dev->dev_stat_grps.stat_group);
	configfs_हटाओ_शेष_groups(&dev->t10_alua.alua_tg_pt_gps_group);

	/*
	 * core_alua_मुक्त_tg_pt_gp() is called from ->शेष_tg_pt_gp
	 * directly from target_core_alua_tg_pt_gp_release().
	 */
	dev->t10_alua.शेष_tg_pt_gp = शून्य;

	configfs_हटाओ_शेष_groups(dev_cg);

	/*
	 * se_dev is released from target_core_dev_item_ops->release()
	 */
	config_item_put(item);
	mutex_unlock(&hba->hba_access_mutex);
पूर्ण

अटल काष्ठा configfs_group_operations target_core_hba_group_ops = अणु
	.make_group		= target_core_make_subdev,
	.drop_item		= target_core_drop_subdev,
पूर्ण;


अटल अंतरभूत काष्ठा se_hba *to_hba(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा se_hba, hba_group);
पूर्ण

अटल sमाप_प्रकार target_hba_info_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_hba *hba = to_hba(item);

	वापस प्र_लिखो(page, "HBA Index: %d plugin: %s version: %s\n",
			hba->hba_id, hba->backend->ops->name,
			TARGET_CORE_VERSION);
पूर्ण

अटल sमाप_प्रकार target_hba_mode_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_hba *hba = to_hba(item);
	पूर्णांक hba_mode = 0;

	अगर (hba->hba_flags & HBA_FLAGS_PSCSI_MODE)
		hba_mode = 1;

	वापस प्र_लिखो(page, "%d\n", hba_mode);
पूर्ण

अटल sमाप_प्रकार target_hba_mode_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_hba *hba = to_hba(item);
	अचिन्हित दीर्घ mode_flag;
	पूर्णांक ret;

	अगर (hba->backend->ops->pmode_enable_hba == शून्य)
		वापस -EINVAL;

	ret = kम_से_अदीर्घ(page, 0, &mode_flag);
	अगर (ret < 0) अणु
		pr_err("Unable to extract hba mode flag: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (hba->dev_count) अणु
		pr_err("Unable to set hba_mode with active devices\n");
		वापस -EINVAL;
	पूर्ण

	ret = hba->backend->ops->pmode_enable_hba(hba, mode_flag);
	अगर (ret < 0)
		वापस -EINVAL;
	अगर (ret > 0)
		hba->hba_flags |= HBA_FLAGS_PSCSI_MODE;
	अन्यथा अगर (ret == 0)
		hba->hba_flags &= ~HBA_FLAGS_PSCSI_MODE;

	वापस count;
पूर्ण

CONFIGFS_ATTR_RO(target_, hba_info);
CONFIGFS_ATTR(target_, hba_mode);

अटल व्योम target_core_hba_release(काष्ठा config_item *item)
अणु
	काष्ठा se_hba *hba = container_of(to_config_group(item),
				काष्ठा se_hba, hba_group);
	core_delete_hba(hba);
पूर्ण

अटल काष्ठा configfs_attribute *target_core_hba_attrs[] = अणु
	&target_attr_hba_info,
	&target_attr_hba_mode,
	शून्य,
पूर्ण;

अटल काष्ठा configfs_item_operations target_core_hba_item_ops = अणु
	.release		= target_core_hba_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_core_hba_cit = अणु
	.ct_item_ops		= &target_core_hba_item_ops,
	.ct_group_ops		= &target_core_hba_group_ops,
	.ct_attrs		= target_core_hba_attrs,
	.ct_owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group *target_core_call_addhbatotarget(
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	अक्षर *se_plugin_str, *str, *str2;
	काष्ठा se_hba *hba;
	अक्षर buf[TARGET_CORE_NAME_MAX_LEN] = अणु पूर्ण;
	अचिन्हित दीर्घ plugin_dep_id = 0;
	पूर्णांक ret;

	अगर (म_माप(name) >= TARGET_CORE_NAME_MAX_LEN) अणु
		pr_err("Passed *name strlen(): %d exceeds"
			" TARGET_CORE_NAME_MAX_LEN: %d\n", (पूर्णांक)म_माप(name),
			TARGET_CORE_NAME_MAX_LEN);
		वापस ERR_PTR(-ENAMETOOLONG);
	पूर्ण
	snम_लिखो(buf, TARGET_CORE_NAME_MAX_LEN, "%s", name);

	str = म_माला(buf, "_");
	अगर (!str) अणु
		pr_err("Unable to locate \"_\" for $SUBSYSTEM_PLUGIN_$HOST_ID\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	se_plugin_str = buf;
	/*
	 * Special हाल क्रम subप्रणाली plugins that have "_" in their names.
	 * Namely rd_direct and rd_mcp..
	 */
	str2 = म_माला(str+1, "_");
	अगर (str2) अणु
		*str2 = '\0'; /* Terminate क्रम *se_plugin_str */
		str2++; /* Skip to start of plugin dependent ID */
		str = str2;
	पूर्ण अन्यथा अणु
		*str = '\0'; /* Terminate क्रम *se_plugin_str */
		str++; /* Skip to start of plugin dependent ID */
	पूर्ण

	ret = kम_से_अदीर्घ(str, 0, &plugin_dep_id);
	अगर (ret < 0) अणु
		pr_err("kstrtoul() returned %d for"
				" plugin_dep_id\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण
	/*
	 * Load up TCM subप्रणाली plugins अगर they have not alपढ़ोy been loaded.
	 */
	transport_subप्रणाली_check_init();

	hba = core_alloc_hba(se_plugin_str, plugin_dep_id, 0);
	अगर (IS_ERR(hba))
		वापस ERR_CAST(hba);

	config_group_init_type_name(&hba->hba_group, name,
			&target_core_hba_cit);

	वापस &hba->hba_group;
पूर्ण

अटल व्योम target_core_call_delhbafromtarget(
	काष्ठा config_group *group,
	काष्ठा config_item *item)
अणु
	/*
	 * core_delete_hba() is called from target_core_hba_item_ops->release()
	 * -> target_core_hba_release()
	 */
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations target_core_group_ops = अणु
	.make_group	= target_core_call_addhbatotarget,
	.drop_item	= target_core_call_delhbafromtarget,
पूर्ण;

अटल स्थिर काष्ठा config_item_type target_core_cit = अणु
	.ct_item_ops	= शून्य,
	.ct_group_ops	= &target_core_group_ops,
	.ct_attrs	= शून्य,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* Stop functions क्रम काष्ठा config_item_type target_core_hba_cit */

व्योम target_setup_backend_cits(काष्ठा target_backend *tb)
अणु
	target_core_setup_dev_cit(tb);
	target_core_setup_dev_action_cit(tb);
	target_core_setup_dev_attrib_cit(tb);
	target_core_setup_dev_pr_cit(tb);
	target_core_setup_dev_wwn_cit(tb);
	target_core_setup_dev_alua_tg_pt_gps_cit(tb);
	target_core_setup_dev_stat_cit(tb);
पूर्ण

अटल व्योम target_init_dbroot(व्योम)
अणु
	काष्ठा file *fp;

	snम_लिखो(db_root_stage, DB_ROOT_LEN, DB_ROOT_PREFERRED);
	fp = filp_खोलो(db_root_stage, O_RDONLY, 0);
	अगर (IS_ERR(fp)) अणु
		pr_err("db_root: cannot open: %s\n", db_root_stage);
		वापस;
	पूर्ण
	अगर (!S_ISसूची(file_inode(fp)->i_mode)) अणु
		filp_बंद(fp, शून्य);
		pr_err("db_root: not a valid directory: %s\n", db_root_stage);
		वापस;
	पूर्ण
	filp_बंद(fp, शून्य);

	म_नकलन(db_root, db_root_stage, DB_ROOT_LEN);
	pr_debug("Target_Core_ConfigFS: db_root set to %s\n", db_root);
पूर्ण

अटल पूर्णांक __init target_core_init_configfs(व्योम)
अणु
	काष्ठा configfs_subप्रणाली *subsys = &target_core_fabrics;
	काष्ठा t10_alua_lu_gp *lu_gp;
	पूर्णांक ret;

	pr_debug("TARGET_CORE[0]: Loading Generic Kernel Storage"
		" Engine: %s on %s/%s on "UTS_RELEASE"\n",
		TARGET_CORE_VERSION, utsname()->sysname, utsname()->machine);

	config_group_init(&subsys->su_group);
	mutex_init(&subsys->su_mutex);

	ret = init_se_kmem_caches();
	अगर (ret < 0)
		वापस ret;
	/*
	 * Create $CONFIGFS/target/core शेष group क्रम HBA <-> Storage Object
	 * and ALUA Logical Unit Group and Target Port Group infraकाष्ठाure.
	 */
	config_group_init_type_name(&target_core_hbagroup, "core",
			&target_core_cit);
	configfs_add_शेष_group(&target_core_hbagroup, &subsys->su_group);

	/*
	 * Create ALUA infraकाष्ठाure under /sys/kernel/config/target/core/alua/
	 */
	config_group_init_type_name(&alua_group, "alua", &target_core_alua_cit);
	configfs_add_शेष_group(&alua_group, &target_core_hbagroup);

	/*
	 * Add ALUA Logical Unit Group and Target Port Group ConfigFS
	 * groups under /sys/kernel/config/target/core/alua/
	 */
	config_group_init_type_name(&alua_lu_gps_group, "lu_gps",
			&target_core_alua_lu_gps_cit);
	configfs_add_शेष_group(&alua_lu_gps_group, &alua_group);

	/*
	 * Add core/alua/lu_gps/शेष_lu_gp
	 */
	lu_gp = core_alua_allocate_lu_gp("default_lu_gp", 1);
	अगर (IS_ERR(lu_gp)) अणु
		ret = -ENOMEM;
		जाओ out_global;
	पूर्ण

	config_group_init_type_name(&lu_gp->lu_gp_group, "default_lu_gp",
				&target_core_alua_lu_gp_cit);
	configfs_add_शेष_group(&lu_gp->lu_gp_group, &alua_lu_gps_group);

	शेष_lu_gp = lu_gp;

	/*
	 * Register the target_core_mod subप्रणाली with configfs.
	 */
	ret = configfs_रेजिस्टर_subप्रणाली(subsys);
	अगर (ret < 0) अणु
		pr_err("Error %d while registering subsystem %s\n",
			ret, subsys->su_group.cg_item.ci_namebuf);
		जाओ out_global;
	पूर्ण
	pr_debug("TARGET_CORE[0]: Initialized ConfigFS Fabric"
		" Infrastructure: "TARGET_CORE_VERSION" on %s/%s"
		" on "UTS_RELEASE"\n", utsname()->sysname, utsname()->machine);
	/*
	 * Register built-in RAMDISK subप्रणाली logic क्रम भव LUN 0
	 */
	ret = rd_module_init();
	अगर (ret < 0)
		जाओ out;

	ret = core_dev_setup_भव_lun0();
	अगर (ret < 0)
		जाओ out;

	ret = target_xcopy_setup_pt();
	अगर (ret < 0)
		जाओ out;

	target_init_dbroot();

	वापस 0;

out:
	configfs_unरेजिस्टर_subप्रणाली(subsys);
	core_dev_release_भव_lun0();
	rd_module_निकास();
out_global:
	अगर (शेष_lu_gp) अणु
		core_alua_मुक्त_lu_gp(शेष_lu_gp);
		शेष_lu_gp = शून्य;
	पूर्ण
	release_se_kmem_caches();
	वापस ret;
पूर्ण

अटल व्योम __निकास target_core_निकास_configfs(व्योम)
अणु
	configfs_हटाओ_शेष_groups(&alua_lu_gps_group);
	configfs_हटाओ_शेष_groups(&alua_group);
	configfs_हटाओ_शेष_groups(&target_core_hbagroup);

	/*
	 * We expect subsys->su_group.शेष_groups to be released
	 * by configfs subप्रणाली provider logic..
	 */
	configfs_unरेजिस्टर_subप्रणाली(&target_core_fabrics);

	core_alua_मुक्त_lu_gp(शेष_lu_gp);
	शेष_lu_gp = शून्य;

	pr_debug("TARGET_CORE[0]: Released ConfigFS Fabric"
			" Infrastructure\n");

	core_dev_release_भव_lun0();
	rd_module_निकास();
	target_xcopy_release_pt();
	release_se_kmem_caches();
पूर्ण

MODULE_DESCRIPTION("Target_Core_Mod/ConfigFS");
MODULE_AUTHOR("nab@Linux-iSCSI.org");
MODULE_LICENSE("GPL");

module_init(target_core_init_configfs);
module_निकास(target_core_निकास_configfs);
