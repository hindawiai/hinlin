<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_device.c (based on iscsi_target_device.c)
 *
 * This file contains the TCM Virtual Device and Disk Transport
 * agnostic related functions.
 *
 * (c) Copyright 2003-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/net.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/in.h>
#समावेश <linux/export.h>
#समावेश <linux/t10-pi.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <scsi/scsi_common.h>
#समावेश <scsi/scsi_proto.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_ua.h"

अटल DEFINE_MUTEX(device_mutex);
अटल LIST_HEAD(device_list);
अटल DEFINE_IDR(devices_idr);

अटल काष्ठा se_hba *lun0_hba;
/* not अटल, needed by tpg.c */
काष्ठा se_device *g_lun0_dev;

sense_reason_t
transport_lookup_cmd_lun(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा se_lun *se_lun = शून्य;
	काष्ठा se_session *se_sess = se_cmd->se_sess;
	काष्ठा se_node_acl *nacl = se_sess->se_node_acl;
	काष्ठा se_dev_entry *deve;
	sense_reason_t ret = TCM_NO_SENSE;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, se_cmd->orig_fe_lun);
	अगर (deve) अणु
		atomic_दीर्घ_inc(&deve->total_cmds);

		अगर (se_cmd->data_direction == DMA_TO_DEVICE)
			atomic_दीर्घ_add(se_cmd->data_length,
					&deve->ग_लिखो_bytes);
		अन्यथा अगर (se_cmd->data_direction == DMA_FROM_DEVICE)
			atomic_दीर्घ_add(se_cmd->data_length,
					&deve->पढ़ो_bytes);

		अगर ((se_cmd->data_direction == DMA_TO_DEVICE) &&
		    deve->lun_access_ro) अणु
			pr_err("TARGET_CORE[%s]: Detected WRITE_PROTECTED LUN"
				" Access for 0x%08llx\n",
				se_cmd->se_tfo->fabric_name,
				se_cmd->orig_fe_lun);
			rcu_पढ़ो_unlock();
			वापस TCM_WRITE_PROTECTED;
		पूर्ण

		se_lun = rcu_dereference(deve->se_lun);

		अगर (!percpu_ref_tryget_live(&se_lun->lun_ref)) अणु
			se_lun = शून्य;
			जाओ out_unlock;
		पूर्ण

		se_cmd->se_lun = se_lun;
		se_cmd->pr_res_key = deve->pr_res_key;
		se_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
		se_cmd->lun_ref_active = true;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();

	अगर (!se_lun) अणु
		/*
		 * Use the se_portal_group->tpg_virt_lun0 to allow क्रम
		 * REPORT_LUNS, et al to be वापसed when no active
		 * MappedLUN=0 exists क्रम this Initiator Port.
		 */
		अगर (se_cmd->orig_fe_lun != 0) अणु
			pr_err("TARGET_CORE[%s]: Detected NON_EXISTENT_LUN"
				" Access for 0x%08llx from %s\n",
				se_cmd->se_tfo->fabric_name,
				se_cmd->orig_fe_lun,
				nacl->initiatorname);
			वापस TCM_NON_EXISTENT_LUN;
		पूर्ण

		/*
		 * Force WRITE PROTECT क्रम भव LUN 0
		 */
		अगर ((se_cmd->data_direction != DMA_FROM_DEVICE) &&
		    (se_cmd->data_direction != DMA_NONE))
			वापस TCM_WRITE_PROTECTED;

		se_lun = se_sess->se_tpg->tpg_virt_lun0;
		अगर (!percpu_ref_tryget_live(&se_lun->lun_ref))
			वापस TCM_NON_EXISTENT_LUN;

		se_cmd->se_lun = se_sess->se_tpg->tpg_virt_lun0;
		se_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
		se_cmd->lun_ref_active = true;
	पूर्ण
	/*
	 * RCU reference रक्षित by percpu se_lun->lun_ref taken above that
	 * must drop to zero (including initial reference) beक्रमe this se_lun
	 * poपूर्णांकer can be kमुक्त_rcu() by the final se_lun->lun_group put via
	 * target_core_fabric_configfs.c:target_fabric_port_release
	 */
	se_cmd->se_dev = rcu_dereference_raw(se_lun->lun_se_dev);
	atomic_दीर्घ_inc(&se_cmd->se_dev->num_cmds);

	अगर (se_cmd->data_direction == DMA_TO_DEVICE)
		atomic_दीर्घ_add(se_cmd->data_length,
				&se_cmd->se_dev->ग_लिखो_bytes);
	अन्यथा अगर (se_cmd->data_direction == DMA_FROM_DEVICE)
		atomic_दीर्घ_add(se_cmd->data_length,
				&se_cmd->se_dev->पढ़ो_bytes);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(transport_lookup_cmd_lun);

पूर्णांक transport_lookup_पंचांगr_lun(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा se_dev_entry *deve;
	काष्ठा se_lun *se_lun = शून्य;
	काष्ठा se_session *se_sess = se_cmd->se_sess;
	काष्ठा se_node_acl *nacl = se_sess->se_node_acl;
	काष्ठा se_पंचांगr_req *se_पंचांगr = se_cmd->se_पंचांगr_req;
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, se_cmd->orig_fe_lun);
	अगर (deve) अणु
		se_lun = rcu_dereference(deve->se_lun);

		अगर (!percpu_ref_tryget_live(&se_lun->lun_ref)) अणु
			se_lun = शून्य;
			जाओ out_unlock;
		पूर्ण

		se_cmd->se_lun = se_lun;
		se_cmd->pr_res_key = deve->pr_res_key;
		se_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
		se_cmd->lun_ref_active = true;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();

	अगर (!se_lun) अणु
		pr_debug("TARGET_CORE[%s]: Detected NON_EXISTENT_LUN"
			" Access for 0x%08llx for %s\n",
			se_cmd->se_tfo->fabric_name,
			se_cmd->orig_fe_lun,
			nacl->initiatorname);
		वापस -ENODEV;
	पूर्ण
	se_cmd->se_dev = rcu_dereference_raw(se_lun->lun_se_dev);
	se_पंचांगr->पंचांगr_dev = rcu_dereference_raw(se_lun->lun_se_dev);

	spin_lock_irqsave(&se_पंचांगr->पंचांगr_dev->se_पंचांगr_lock, flags);
	list_add_tail(&se_पंचांगr->पंचांगr_list, &se_पंचांगr->पंचांगr_dev->dev_पंचांगr_list);
	spin_unlock_irqrestore(&se_पंचांगr->पंचांगr_dev->se_पंचांगr_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(transport_lookup_पंचांगr_lun);

bool target_lun_is_rकरोnly(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_dev_entry *deve;
	bool ret;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(se_sess->se_node_acl, cmd->orig_fe_lun);
	ret = deve && deve->lun_access_ro;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(target_lun_is_rकरोnly);

/*
 * This function is called from core_scsi3_emulate_pro_रेजिस्टर_and_move()
 * and core_scsi3_decode_spec_i_port(), and will increment &deve->pr_kref
 * when a matching rtpi is found.
 */
काष्ठा se_dev_entry *core_get_se_deve_from_rtpi(
	काष्ठा se_node_acl *nacl,
	u16 rtpi)
अणु
	काष्ठा se_dev_entry *deve;
	काष्ठा se_lun *lun;
	काष्ठा se_portal_group *tpg = nacl->se_tpg;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(deve, &nacl->lun_entry_hlist, link) अणु
		lun = rcu_dereference(deve->se_lun);
		अगर (!lun) अणु
			pr_err("%s device entries device pointer is"
				" NULL, but Initiator has access.\n",
				tpg->se_tpg_tfo->fabric_name);
			जारी;
		पूर्ण
		अगर (lun->lun_rtpi != rtpi)
			जारी;

		kref_get(&deve->pr_kref);
		rcu_पढ़ो_unlock();

		वापस deve;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

व्योम core_मुक्त_device_list_क्रम_node(
	काष्ठा se_node_acl *nacl,
	काष्ठा se_portal_group *tpg)
अणु
	काष्ठा se_dev_entry *deve;

	mutex_lock(&nacl->lun_entry_mutex);
	hlist_क्रम_each_entry_rcu(deve, &nacl->lun_entry_hlist, link) अणु
		काष्ठा se_lun *lun = rcu_dereference_check(deve->se_lun,
					lockdep_is_held(&nacl->lun_entry_mutex));
		core_disable_device_list_क्रम_node(lun, deve, nacl, tpg);
	पूर्ण
	mutex_unlock(&nacl->lun_entry_mutex);
पूर्ण

व्योम core_update_device_list_access(
	u64 mapped_lun,
	bool lun_access_ro,
	काष्ठा se_node_acl *nacl)
अणु
	काष्ठा se_dev_entry *deve;

	mutex_lock(&nacl->lun_entry_mutex);
	deve = target_nacl_find_deve(nacl, mapped_lun);
	अगर (deve)
		deve->lun_access_ro = lun_access_ro;
	mutex_unlock(&nacl->lun_entry_mutex);
पूर्ण

/*
 * Called with rcu_पढ़ो_lock or nacl->device_list_lock held.
 */
काष्ठा se_dev_entry *target_nacl_find_deve(काष्ठा se_node_acl *nacl, u64 mapped_lun)
अणु
	काष्ठा se_dev_entry *deve;

	hlist_क्रम_each_entry_rcu(deve, &nacl->lun_entry_hlist, link)
		अगर (deve->mapped_lun == mapped_lun)
			वापस deve;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(target_nacl_find_deve);

व्योम target_pr_kref_release(काष्ठा kref *kref)
अणु
	काष्ठा se_dev_entry *deve = container_of(kref, काष्ठा se_dev_entry,
						 pr_kref);
	complete(&deve->pr_comp);
पूर्ण

अटल व्योम
target_luns_data_has_changed(काष्ठा se_node_acl *nacl, काष्ठा se_dev_entry *new,
			     bool skip_new)
अणु
	काष्ठा se_dev_entry *पंचांगp;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp, &nacl->lun_entry_hlist, link) अणु
		अगर (skip_new && पंचांगp == new)
			जारी;
		core_scsi3_ua_allocate(पंचांगp, 0x3F,
				       ASCQ_3FH_REPORTED_LUNS_DATA_HAS_CHANGED);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक core_enable_device_list_क्रम_node(
	काष्ठा se_lun *lun,
	काष्ठा se_lun_acl *lun_acl,
	u64 mapped_lun,
	bool lun_access_ro,
	काष्ठा se_node_acl *nacl,
	काष्ठा se_portal_group *tpg)
अणु
	काष्ठा se_dev_entry *orig, *new;

	new = kzalloc(माप(*new), GFP_KERNEL);
	अगर (!new) अणु
		pr_err("Unable to allocate se_dev_entry memory\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&new->ua_lock);
	INIT_LIST_HEAD(&new->ua_list);
	INIT_LIST_HEAD(&new->lun_link);

	new->mapped_lun = mapped_lun;
	kref_init(&new->pr_kref);
	init_completion(&new->pr_comp);

	new->lun_access_ro = lun_access_ro;
	new->creation_समय = get_jअगरfies_64();
	new->attach_count++;

	mutex_lock(&nacl->lun_entry_mutex);
	orig = target_nacl_find_deve(nacl, mapped_lun);
	अगर (orig && orig->se_lun) अणु
		काष्ठा se_lun *orig_lun = rcu_dereference_check(orig->se_lun,
					lockdep_is_held(&nacl->lun_entry_mutex));

		अगर (orig_lun != lun) अणु
			pr_err("Existing orig->se_lun doesn't match new lun"
			       " for dynamic -> explicit NodeACL conversion:"
				" %s\n", nacl->initiatorname);
			mutex_unlock(&nacl->lun_entry_mutex);
			kमुक्त(new);
			वापस -EINVAL;
		पूर्ण
		अगर (orig->se_lun_acl != शून्य) अणु
			pr_warn_ratelimited("Detected existing explicit"
				" se_lun_acl->se_lun_group reference for %s"
				" mapped_lun: %llu, failing\n",
				 nacl->initiatorname, mapped_lun);
			mutex_unlock(&nacl->lun_entry_mutex);
			kमुक्त(new);
			वापस -EINVAL;
		पूर्ण

		rcu_assign_poपूर्णांकer(new->se_lun, lun);
		rcu_assign_poपूर्णांकer(new->se_lun_acl, lun_acl);
		hlist_del_rcu(&orig->link);
		hlist_add_head_rcu(&new->link, &nacl->lun_entry_hlist);
		mutex_unlock(&nacl->lun_entry_mutex);

		spin_lock(&lun->lun_deve_lock);
		list_del(&orig->lun_link);
		list_add_tail(&new->lun_link, &lun->lun_deve_list);
		spin_unlock(&lun->lun_deve_lock);

		kref_put(&orig->pr_kref, target_pr_kref_release);
		रुको_क्रम_completion(&orig->pr_comp);

		target_luns_data_has_changed(nacl, new, true);
		kमुक्त_rcu(orig, rcu_head);
		वापस 0;
	पूर्ण

	rcu_assign_poपूर्णांकer(new->se_lun, lun);
	rcu_assign_poपूर्णांकer(new->se_lun_acl, lun_acl);
	hlist_add_head_rcu(&new->link, &nacl->lun_entry_hlist);
	mutex_unlock(&nacl->lun_entry_mutex);

	spin_lock(&lun->lun_deve_lock);
	list_add_tail(&new->lun_link, &lun->lun_deve_list);
	spin_unlock(&lun->lun_deve_lock);

	target_luns_data_has_changed(nacl, new, true);
	वापस 0;
पूर्ण

व्योम core_disable_device_list_क्रम_node(
	काष्ठा se_lun *lun,
	काष्ठा se_dev_entry *orig,
	काष्ठा se_node_acl *nacl,
	काष्ठा se_portal_group *tpg)
अणु
	/*
	 * rcu_dereference_raw रक्षित by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	काष्ठा se_device *dev = rcu_dereference_raw(lun->lun_se_dev);

	lockdep_निश्चित_held(&nacl->lun_entry_mutex);

	/*
	 * If the MappedLUN entry is being disabled, the entry in
	 * lun->lun_deve_list must be हटाओd now beक्रमe clearing the
	 * काष्ठा se_dev_entry poपूर्णांकers below as logic in
	 * core_alua_करो_transition_tg_pt() depends on these being present.
	 *
	 * deve->se_lun_acl will be शून्य क्रम demo-mode created LUNs
	 * that have not been explicitly converted to MappedLUNs ->
	 * काष्ठा se_lun_acl, but we हटाओ deve->lun_link from
	 * lun->lun_deve_list. This also means that active UAs and
	 * NodeACL context specअगरic PR metadata क्रम demo-mode
	 * MappedLUN *deve will be released below..
	 */
	spin_lock(&lun->lun_deve_lock);
	list_del(&orig->lun_link);
	spin_unlock(&lun->lun_deve_lock);
	/*
	 * Disable काष्ठा se_dev_entry LUN ACL mapping
	 */
	core_scsi3_ua_release_all(orig);

	hlist_del_rcu(&orig->link);
	clear_bit(DEF_PR_REG_ACTIVE, &orig->deve_flags);
	orig->lun_access_ro = false;
	orig->creation_समय = 0;
	orig->attach_count--;
	/*
	 * Beक्रमe firing off RCU callback, रुको क्रम any in process SPEC_I_PT=1
	 * or REGISTER_AND_MOVE PR operation to complete.
	 */
	kref_put(&orig->pr_kref, target_pr_kref_release);
	रुको_क्रम_completion(&orig->pr_comp);

	rcu_assign_poपूर्णांकer(orig->se_lun, शून्य);
	rcu_assign_poपूर्णांकer(orig->se_lun_acl, शून्य);

	kमुक्त_rcu(orig, rcu_head);

	core_scsi3_मुक्त_pr_reg_from_nacl(dev, nacl);
	target_luns_data_has_changed(nacl, शून्य, false);
पूर्ण

/*      core_clear_lun_from_tpg():
 *
 *
 */
व्योम core_clear_lun_from_tpg(काष्ठा se_lun *lun, काष्ठा se_portal_group *tpg)
अणु
	काष्ठा se_node_acl *nacl;
	काष्ठा se_dev_entry *deve;

	mutex_lock(&tpg->acl_node_mutex);
	list_क्रम_each_entry(nacl, &tpg->acl_node_list, acl_list) अणु

		mutex_lock(&nacl->lun_entry_mutex);
		hlist_क्रम_each_entry_rcu(deve, &nacl->lun_entry_hlist, link) अणु
			काष्ठा se_lun *पंचांगp_lun = rcu_dereference_check(deve->se_lun,
					lockdep_is_held(&nacl->lun_entry_mutex));

			अगर (lun != पंचांगp_lun)
				जारी;

			core_disable_device_list_क्रम_node(lun, deve, nacl, tpg);
		पूर्ण
		mutex_unlock(&nacl->lun_entry_mutex);
	पूर्ण
	mutex_unlock(&tpg->acl_node_mutex);
पूर्ण

पूर्णांक core_alloc_rtpi(काष्ठा se_lun *lun, काष्ठा se_device *dev)
अणु
	काष्ठा se_lun *पंचांगp;

	spin_lock(&dev->se_port_lock);
	अगर (dev->export_count == 0x0000ffff) अणु
		pr_warn("Reached dev->dev_port_count =="
				" 0x0000ffff\n");
		spin_unlock(&dev->se_port_lock);
		वापस -ENOSPC;
	पूर्ण
again:
	/*
	 * Allocate the next RELATIVE TARGET PORT IDENTIFIER क्रम this काष्ठा se_device
	 * Here is the table from spc4r17 section 7.7.3.8.
	 *
	 *    Table 473 -- RELATIVE TARGET PORT IDENTIFIER field
	 *
	 * Code      Description
	 * 0h        Reserved
	 * 1h        Relative port 1, historically known as port A
	 * 2h        Relative port 2, historically known as port B
	 * 3h to FFFFh    Relative port 3 through 65 535
	 */
	lun->lun_rtpi = dev->dev_rpti_counter++;
	अगर (!lun->lun_rtpi)
		जाओ again;

	list_क्रम_each_entry(पंचांगp, &dev->dev_sep_list, lun_dev_link) अणु
		/*
		 * Make sure RELATIVE TARGET PORT IDENTIFIER is unique
		 * क्रम 16-bit wrap..
		 */
		अगर (lun->lun_rtpi == पंचांगp->lun_rtpi)
			जाओ again;
	पूर्ण
	spin_unlock(&dev->se_port_lock);

	वापस 0;
पूर्ण

अटल व्योम se_release_vpd_क्रम_dev(काष्ठा se_device *dev)
अणु
	काष्ठा t10_vpd *vpd, *vpd_पंचांगp;

	spin_lock(&dev->t10_wwn.t10_vpd_lock);
	list_क्रम_each_entry_safe(vpd, vpd_पंचांगp,
			&dev->t10_wwn.t10_vpd_list, vpd_list) अणु
		list_del(&vpd->vpd_list);
		kमुक्त(vpd);
	पूर्ण
	spin_unlock(&dev->t10_wwn.t10_vpd_lock);
पूर्ण

अटल u32 se_dev_align_max_sectors(u32 max_sectors, u32 block_size)
अणु
	u32 aligned_max_sectors;
	u32 alignment;
	/*
	 * Limit max_sectors to a PAGE_SIZE aligned value क्रम modern
	 * transport_allocate_data_tasks() operation.
	 */
	alignment = max(1ul, PAGE_SIZE / block_size);
	aligned_max_sectors = roundकरोwn(max_sectors, alignment);

	अगर (max_sectors != aligned_max_sectors)
		pr_info("Rounding down aligned max_sectors from %u to %u\n",
			max_sectors, aligned_max_sectors);

	वापस aligned_max_sectors;
पूर्ण

पूर्णांक core_dev_add_lun(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_device *dev,
	काष्ठा se_lun *lun)
अणु
	पूर्णांक rc;

	rc = core_tpg_add_lun(tpg, lun, false, dev);
	अगर (rc < 0)
		वापस rc;

	pr_debug("%s_TPG[%u]_LUN[%llu] - Activated %s Logical Unit from"
		" CORE HBA: %u\n", tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), lun->unpacked_lun,
		tpg->se_tpg_tfo->fabric_name, dev->se_hba->hba_id);
	/*
	 * Update LUN maps क्रम dynamically added initiators when
	 * generate_node_acl is enabled.
	 */
	अगर (tpg->se_tpg_tfo->tpg_check_demo_mode(tpg)) अणु
		काष्ठा se_node_acl *acl;

		mutex_lock(&tpg->acl_node_mutex);
		list_क्रम_each_entry(acl, &tpg->acl_node_list, acl_list) अणु
			अगर (acl->dynamic_node_acl &&
			    (!tpg->se_tpg_tfo->tpg_check_demo_mode_login_only ||
			     !tpg->se_tpg_tfo->tpg_check_demo_mode_login_only(tpg))) अणु
				core_tpg_add_node_to_devs(acl, tpg, lun);
			पूर्ण
		पूर्ण
		mutex_unlock(&tpg->acl_node_mutex);
	पूर्ण

	वापस 0;
पूर्ण

/*      core_dev_del_lun():
 *
 *
 */
व्योम core_dev_del_lun(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun *lun)
अणु
	pr_debug("%s_TPG[%u]_LUN[%llu] - Deactivating %s Logical Unit from"
		" device object\n", tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), lun->unpacked_lun,
		tpg->se_tpg_tfo->fabric_name);

	core_tpg_हटाओ_lun(tpg, lun);
पूर्ण

काष्ठा se_lun_acl *core_dev_init_initiator_node_lun_acl(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_node_acl *nacl,
	u64 mapped_lun,
	पूर्णांक *ret)
अणु
	काष्ठा se_lun_acl *lacl;

	अगर (म_माप(nacl->initiatorname) >= TRANSPORT_IQN_LEN) अणु
		pr_err("%s InitiatorName exceeds maximum size.\n",
			tpg->se_tpg_tfo->fabric_name);
		*ret = -EOVERFLOW;
		वापस शून्य;
	पूर्ण
	lacl = kzalloc(माप(काष्ठा se_lun_acl), GFP_KERNEL);
	अगर (!lacl) अणु
		pr_err("Unable to allocate memory for struct se_lun_acl.\n");
		*ret = -ENOMEM;
		वापस शून्य;
	पूर्ण

	lacl->mapped_lun = mapped_lun;
	lacl->se_lun_nacl = nacl;

	वापस lacl;
पूर्ण

पूर्णांक core_dev_add_initiator_node_lun_acl(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun_acl *lacl,
	काष्ठा se_lun *lun,
	bool lun_access_ro)
अणु
	काष्ठा se_node_acl *nacl = lacl->se_lun_nacl;
	/*
	 * rcu_dereference_raw रक्षित by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	काष्ठा se_device *dev = rcu_dereference_raw(lun->lun_se_dev);

	अगर (!nacl)
		वापस -EINVAL;

	अगर (lun->lun_access_ro)
		lun_access_ro = true;

	lacl->se_lun = lun;

	अगर (core_enable_device_list_क्रम_node(lun, lacl, lacl->mapped_lun,
			lun_access_ro, nacl, tpg) < 0)
		वापस -EINVAL;

	pr_debug("%s_TPG[%hu]_LUN[%llu->%llu] - Added %s ACL for "
		" InitiatorNode: %s\n", tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), lun->unpacked_lun, lacl->mapped_lun,
		lun_access_ro ? "RO" : "RW",
		nacl->initiatorname);
	/*
	 * Check to see अगर there are any existing persistent reservation APTPL
	 * pre-registrations that need to be enabled क्रम this LUN ACL..
	 */
	core_scsi3_check_aptpl_registration(dev, tpg, lun, nacl,
					    lacl->mapped_lun);
	वापस 0;
पूर्ण

पूर्णांक core_dev_del_initiator_node_lun_acl(
	काष्ठा se_lun *lun,
	काष्ठा se_lun_acl *lacl)
अणु
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	काष्ठा se_node_acl *nacl;
	काष्ठा se_dev_entry *deve;

	nacl = lacl->se_lun_nacl;
	अगर (!nacl)
		वापस -EINVAL;

	mutex_lock(&nacl->lun_entry_mutex);
	deve = target_nacl_find_deve(nacl, lacl->mapped_lun);
	अगर (deve)
		core_disable_device_list_क्रम_node(lun, deve, nacl, tpg);
	mutex_unlock(&nacl->lun_entry_mutex);

	pr_debug("%s_TPG[%hu]_LUN[%llu] - Removed ACL for"
		" InitiatorNode: %s Mapped LUN: %llu\n",
		tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg), lun->unpacked_lun,
		nacl->initiatorname, lacl->mapped_lun);

	वापस 0;
पूर्ण

व्योम core_dev_मुक्त_initiator_node_lun_acl(
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun_acl *lacl)
अणु
	pr_debug("%s_TPG[%hu] - Freeing ACL for %s InitiatorNode: %s"
		" Mapped LUN: %llu\n", tpg->se_tpg_tfo->fabric_name,
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		tpg->se_tpg_tfo->fabric_name,
		lacl->se_lun_nacl->initiatorname, lacl->mapped_lun);

	kमुक्त(lacl);
पूर्ण

अटल व्योम scsi_dump_inquiry(काष्ठा se_device *dev)
अणु
	काष्ठा t10_wwn *wwn = &dev->t10_wwn;
	पूर्णांक device_type = dev->transport->get_device_type(dev);

	/*
	 * Prपूर्णांक Linux/SCSI style INQUIRY क्रमmatting to the kernel ring buffer
	 */
	pr_debug("  Vendor: %-" __stringअगरy(INQUIRY_VENDOR_LEN) "s\n",
		wwn->venकरोr);
	pr_debug("  Model: %-" __stringअगरy(INQUIRY_MODEL_LEN) "s\n",
		wwn->model);
	pr_debug("  Revision: %-" __stringअगरy(INQUIRY_REVISION_LEN) "s\n",
		wwn->revision);
	pr_debug("  Type:   %s ", scsi_device_type(device_type));
पूर्ण

काष्ठा se_device *target_alloc_device(काष्ठा se_hba *hba, स्थिर अक्षर *name)
अणु
	काष्ठा se_device *dev;
	काष्ठा se_lun *xcopy_lun;
	पूर्णांक i;

	dev = hba->backend->ops->alloc_device(hba, name);
	अगर (!dev)
		वापस शून्य;

	dev->queues = kसुस्मृति(nr_cpu_ids, माप(*dev->queues), GFP_KERNEL);
	अगर (!dev->queues) अणु
		dev->transport->मुक्त_device(dev);
		वापस शून्य;
	पूर्ण

	dev->queue_cnt = nr_cpu_ids;
	क्रम (i = 0; i < dev->queue_cnt; i++) अणु
		काष्ठा se_device_queue *q;

		q = &dev->queues[i];
		INIT_LIST_HEAD(&q->state_list);
		spin_lock_init(&q->lock);

		init_llist_head(&q->sq.cmd_list);
		INIT_WORK(&q->sq.work, target_queued_submit_work);
	पूर्ण

	dev->se_hba = hba;
	dev->transport = hba->backend->ops;
	dev->transport_flags = dev->transport->transport_flags_शेष;
	dev->prot_length = माप(काष्ठा t10_pi_tuple);
	dev->hba_index = hba->hba_index;

	INIT_LIST_HEAD(&dev->dev_sep_list);
	INIT_LIST_HEAD(&dev->dev_पंचांगr_list);
	INIT_LIST_HEAD(&dev->delayed_cmd_list);
	INIT_LIST_HEAD(&dev->qf_cmd_list);
	spin_lock_init(&dev->delayed_cmd_lock);
	spin_lock_init(&dev->dev_reservation_lock);
	spin_lock_init(&dev->se_port_lock);
	spin_lock_init(&dev->se_पंचांगr_lock);
	spin_lock_init(&dev->qf_cmd_lock);
	sema_init(&dev->caw_sem, 1);
	INIT_LIST_HEAD(&dev->t10_wwn.t10_vpd_list);
	spin_lock_init(&dev->t10_wwn.t10_vpd_lock);
	INIT_LIST_HEAD(&dev->t10_pr.registration_list);
	INIT_LIST_HEAD(&dev->t10_pr.aptpl_reg_list);
	spin_lock_init(&dev->t10_pr.registration_lock);
	spin_lock_init(&dev->t10_pr.aptpl_reg_lock);
	INIT_LIST_HEAD(&dev->t10_alua.tg_pt_gps_list);
	spin_lock_init(&dev->t10_alua.tg_pt_gps_lock);
	INIT_LIST_HEAD(&dev->t10_alua.lba_map_list);
	spin_lock_init(&dev->t10_alua.lba_map_lock);

	dev->t10_wwn.t10_dev = dev;
	dev->t10_alua.t10_dev = dev;

	dev->dev_attrib.da_dev = dev;
	dev->dev_attrib.emulate_model_alias = DA_EMULATE_MODEL_ALIAS;
	dev->dev_attrib.emulate_dpo = 1;
	dev->dev_attrib.emulate_fua_ग_लिखो = 1;
	dev->dev_attrib.emulate_fua_पढ़ो = 1;
	dev->dev_attrib.emulate_ग_लिखो_cache = DA_EMULATE_WRITE_CACHE;
	dev->dev_attrib.emulate_ua_पूर्णांकlck_ctrl = TARGET_UA_INTLCK_CTRL_CLEAR;
	dev->dev_attrib.emulate_tas = DA_EMULATE_TAS;
	dev->dev_attrib.emulate_tpu = DA_EMULATE_TPU;
	dev->dev_attrib.emulate_tpws = DA_EMULATE_TPWS;
	dev->dev_attrib.emulate_caw = DA_EMULATE_CAW;
	dev->dev_attrib.emulate_3pc = DA_EMULATE_3PC;
	dev->dev_attrib.emulate_pr = DA_EMULATE_PR;
	dev->dev_attrib.pi_prot_type = TARGET_DIF_TYPE0_PROT;
	dev->dev_attrib.enक्रमce_pr_isids = DA_ENFORCE_PR_ISIDS;
	dev->dev_attrib.क्रमce_pr_aptpl = DA_FORCE_PR_APTPL;
	dev->dev_attrib.is_nonrot = DA_IS_NONROT;
	dev->dev_attrib.emulate_rest_reord = DA_EMULATE_REST_REORD;
	dev->dev_attrib.max_unmap_lba_count = DA_MAX_UNMAP_LBA_COUNT;
	dev->dev_attrib.max_unmap_block_desc_count =
		DA_MAX_UNMAP_BLOCK_DESC_COUNT;
	dev->dev_attrib.unmap_granularity = DA_UNMAP_GRANULARITY_DEFAULT;
	dev->dev_attrib.unmap_granularity_alignment =
				DA_UNMAP_GRANULARITY_ALIGNMENT_DEFAULT;
	dev->dev_attrib.unmap_zeroes_data =
				DA_UNMAP_ZEROES_DATA_DEFAULT;
	dev->dev_attrib.max_ग_लिखो_same_len = DA_MAX_WRITE_SAME_LEN;

	xcopy_lun = &dev->xcopy_lun;
	rcu_assign_poपूर्णांकer(xcopy_lun->lun_se_dev, dev);
	init_completion(&xcopy_lun->lun_shutकरोwn_comp);
	INIT_LIST_HEAD(&xcopy_lun->lun_deve_list);
	INIT_LIST_HEAD(&xcopy_lun->lun_dev_link);
	mutex_init(&xcopy_lun->lun_tg_pt_md_mutex);
	xcopy_lun->lun_tpg = &xcopy_pt_tpg;

	/* Preload the शेष INQUIRY स्थिर values */
	strlcpy(dev->t10_wwn.venकरोr, "LIO-ORG", माप(dev->t10_wwn.venकरोr));
	strlcpy(dev->t10_wwn.model, dev->transport->inquiry_prod,
		माप(dev->t10_wwn.model));
	strlcpy(dev->t10_wwn.revision, dev->transport->inquiry_rev,
		माप(dev->t10_wwn.revision));

	वापस dev;
पूर्ण

/*
 * Check अगर the underlying काष्ठा block_device request_queue supports
 * the QUEUE_FLAG_DISCARD bit क्रम UNMAP/WRITE_SAME in SCSI + TRIM
 * in ATA and we need to set TPE=1
 */
bool target_configure_unmap_from_queue(काष्ठा se_dev_attrib *attrib,
				       काष्ठा request_queue *q)
अणु
	पूर्णांक block_size = queue_logical_block_size(q);

	अगर (!blk_queue_discard(q))
		वापस false;

	attrib->max_unmap_lba_count =
		q->limits.max_discard_sectors >> (ilog2(block_size) - 9);
	/*
	 * Currently hardcoded to 1 in Linux/SCSI code..
	 */
	attrib->max_unmap_block_desc_count = 1;
	attrib->unmap_granularity = q->limits.discard_granularity / block_size;
	attrib->unmap_granularity_alignment = q->limits.discard_alignment /
								block_size;
	attrib->unmap_zeroes_data = !!(q->limits.max_ग_लिखो_zeroes_sectors);
	वापस true;
पूर्ण
EXPORT_SYMBOL(target_configure_unmap_from_queue);

/*
 * Convert from blocksize advertised to the initiator to the 512 byte
 * units unconditionally used by the Linux block layer.
 */
sector_t target_to_linux_sector(काष्ठा se_device *dev, sector_t lb)
अणु
	चयन (dev->dev_attrib.block_size) अणु
	हाल 4096:
		वापस lb << 3;
	हाल 2048:
		वापस lb << 2;
	हाल 1024:
		वापस lb << 1;
	शेष:
		वापस lb;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(target_to_linux_sector);

काष्ठा devices_idr_iter अणु
	काष्ठा config_item *prev_item;
	पूर्णांक (*fn)(काष्ठा se_device *dev, व्योम *data);
	व्योम *data;
पूर्ण;

अटल पूर्णांक target_devices_idr_iter(पूर्णांक id, व्योम *p, व्योम *data)
	 __must_hold(&device_mutex)
अणु
	काष्ठा devices_idr_iter *iter = data;
	काष्ठा se_device *dev = p;
	पूर्णांक ret;

	config_item_put(iter->prev_item);
	iter->prev_item = शून्य;

	/*
	 * We add the device early to the idr, so it can be used
	 * by backend modules during configuration. We करो not want
	 * to allow other callers to access partially setup devices,
	 * so we skip them here.
	 */
	अगर (!target_dev_configured(dev))
		वापस 0;

	iter->prev_item = config_item_get_unless_zero(&dev->dev_group.cg_item);
	अगर (!iter->prev_item)
		वापस 0;
	mutex_unlock(&device_mutex);

	ret = iter->fn(dev, iter->data);

	mutex_lock(&device_mutex);
	वापस ret;
पूर्ण

/**
 * target_क्रम_each_device - iterate over configured devices
 * @fn: iterator function
 * @data: poपूर्णांकer to data that will be passed to fn
 *
 * fn must वापस 0 to जारी looping over devices. non-zero will अवरोध
 * from the loop and वापस that value to the caller.
 */
पूर्णांक target_क्रम_each_device(पूर्णांक (*fn)(काष्ठा se_device *dev, व्योम *data),
			   व्योम *data)
अणु
	काष्ठा devices_idr_iter iter = अणु .fn = fn, .data = data पूर्ण;
	पूर्णांक ret;

	mutex_lock(&device_mutex);
	ret = idr_क्रम_each(&devices_idr, target_devices_idr_iter, &iter);
	mutex_unlock(&device_mutex);
	config_item_put(iter.prev_item);
	वापस ret;
पूर्ण

पूर्णांक target_configure_device(काष्ठा se_device *dev)
अणु
	काष्ठा se_hba *hba = dev->se_hba;
	पूर्णांक ret, id;

	अगर (target_dev_configured(dev)) अणु
		pr_err("se_dev->se_dev_ptr already set for storage"
				" object\n");
		वापस -EEXIST;
	पूर्ण

	/*
	 * Add early so modules like tcmu can use during its
	 * configuration.
	 */
	mutex_lock(&device_mutex);
	/*
	 * Use cyclic to try and aव्योम collisions with devices
	 * that were recently हटाओd.
	 */
	id = idr_alloc_cyclic(&devices_idr, dev, 0, पूर्णांक_उच्च, GFP_KERNEL);
	mutex_unlock(&device_mutex);
	अगर (id < 0) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	dev->dev_index = id;

	ret = dev->transport->configure_device(dev);
	अगर (ret)
		जाओ out_मुक्त_index;
	/*
	 * XXX: there is not much poपूर्णांक to have two dअगरferent values here..
	 */
	dev->dev_attrib.block_size = dev->dev_attrib.hw_block_size;
	dev->dev_attrib.queue_depth = dev->dev_attrib.hw_queue_depth;

	/*
	 * Align max_hw_sectors करोwn to PAGE_SIZE I/O transfers
	 */
	dev->dev_attrib.hw_max_sectors =
		se_dev_align_max_sectors(dev->dev_attrib.hw_max_sectors,
					 dev->dev_attrib.hw_block_size);
	dev->dev_attrib.optimal_sectors = dev->dev_attrib.hw_max_sectors;

	dev->creation_समय = get_jअगरfies_64();

	ret = core_setup_alua(dev);
	अगर (ret)
		जाओ out_destroy_device;

	/*
	 * Setup work_queue क्रम QUEUE_FULL
	 */
	INIT_WORK(&dev->qf_work_queue, target_qf_करो_work);

	scsi_dump_inquiry(dev);

	spin_lock(&hba->device_lock);
	hba->dev_count++;
	spin_unlock(&hba->device_lock);

	dev->dev_flags |= DF_CONFIGURED;

	वापस 0;

out_destroy_device:
	dev->transport->destroy_device(dev);
out_मुक्त_index:
	mutex_lock(&device_mutex);
	idr_हटाओ(&devices_idr, dev->dev_index);
	mutex_unlock(&device_mutex);
out:
	se_release_vpd_क्रम_dev(dev);
	वापस ret;
पूर्ण

व्योम target_मुक्त_device(काष्ठा se_device *dev)
अणु
	काष्ठा se_hba *hba = dev->se_hba;

	WARN_ON(!list_empty(&dev->dev_sep_list));

	अगर (target_dev_configured(dev)) अणु
		dev->transport->destroy_device(dev);

		mutex_lock(&device_mutex);
		idr_हटाओ(&devices_idr, dev->dev_index);
		mutex_unlock(&device_mutex);

		spin_lock(&hba->device_lock);
		hba->dev_count--;
		spin_unlock(&hba->device_lock);
	पूर्ण

	core_alua_मुक्त_lu_gp_mem(dev);
	core_alua_set_lba_map(dev, शून्य, 0, 0);
	core_scsi3_मुक्त_all_registrations(dev);
	se_release_vpd_क्रम_dev(dev);

	अगर (dev->transport->मुक्त_prot)
		dev->transport->मुक्त_prot(dev);

	kमुक्त(dev->queues);
	dev->transport->मुक्त_device(dev);
पूर्ण

पूर्णांक core_dev_setup_भव_lun0(व्योम)
अणु
	काष्ठा se_hba *hba;
	काष्ठा se_device *dev;
	अक्षर buf[] = "rd_pages=8,rd_nullio=1,rd_dummy=1";
	पूर्णांक ret;

	hba = core_alloc_hba("rd_mcp", 0, HBA_FLAGS_INTERNAL_USE);
	अगर (IS_ERR(hba))
		वापस PTR_ERR(hba);

	dev = target_alloc_device(hba, "virt_lun0");
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_hba;
	पूर्ण

	hba->backend->ops->set_configfs_dev_params(dev, buf, माप(buf));

	ret = target_configure_device(dev);
	अगर (ret)
		जाओ out_मुक्त_se_dev;

	lun0_hba = hba;
	g_lun0_dev = dev;
	वापस 0;

out_मुक्त_se_dev:
	target_मुक्त_device(dev);
out_मुक्त_hba:
	core_delete_hba(hba);
	वापस ret;
पूर्ण


व्योम core_dev_release_भव_lun0(व्योम)
अणु
	काष्ठा se_hba *hba = lun0_hba;

	अगर (!hba)
		वापस;

	अगर (g_lun0_dev)
		target_मुक्त_device(g_lun0_dev);
	core_delete_hba(hba);
पूर्ण

/*
 * Common CDB parsing क्रम kernel and user passthrough.
 */
sense_reason_t
passthrough_parse_cdb(काष्ठा se_cmd *cmd,
	sense_reason_t (*exec_cmd)(काष्ठा se_cmd *cmd))
अणु
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित पूर्णांक size;

	/*
	 * For REPORT LUNS we always need to emulate the response, क्रम everything
	 * अन्यथा, pass it up.
	 */
	अगर (cdb[0] == REPORT_LUNS) अणु
		cmd->execute_cmd = spc_emulate_report_luns;
		वापस TCM_NO_SENSE;
	पूर्ण

	/*
	 * With emulate_pr disabled, all reservation requests should fail,
	 * regardless of whether or not TRANSPORT_FLAG_PASSTHROUGH_PGR is set.
	 */
	अगर (!dev->dev_attrib.emulate_pr &&
	    ((cdb[0] == PERSISTENT_RESERVE_IN) ||
	     (cdb[0] == PERSISTENT_RESERVE_OUT) ||
	     (cdb[0] == RELEASE || cdb[0] == RELEASE_10) ||
	     (cdb[0] == RESERVE || cdb[0] == RESERVE_10))) अणु
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण

	/*
	 * For PERSISTENT RESERVE IN/OUT, RELEASE, and RESERVE we need to
	 * emulate the response, since tcmu करोes not have the inक्रमmation
	 * required to process these commands.
	 */
	अगर (!(dev->transport_flags &
	      TRANSPORT_FLAG_PASSTHROUGH_PGR)) अणु
		अगर (cdb[0] == PERSISTENT_RESERVE_IN) अणु
			cmd->execute_cmd = target_scsi3_emulate_pr_in;
			size = get_unaligned_be16(&cdb[7]);
			वापस target_cmd_size_check(cmd, size);
		पूर्ण
		अगर (cdb[0] == PERSISTENT_RESERVE_OUT) अणु
			cmd->execute_cmd = target_scsi3_emulate_pr_out;
			size = get_unaligned_be32(&cdb[5]);
			वापस target_cmd_size_check(cmd, size);
		पूर्ण

		अगर (cdb[0] == RELEASE || cdb[0] == RELEASE_10) अणु
			cmd->execute_cmd = target_scsi2_reservation_release;
			अगर (cdb[0] == RELEASE_10)
				size = get_unaligned_be16(&cdb[7]);
			अन्यथा
				size = cmd->data_length;
			वापस target_cmd_size_check(cmd, size);
		पूर्ण
		अगर (cdb[0] == RESERVE || cdb[0] == RESERVE_10) अणु
			cmd->execute_cmd = target_scsi2_reservation_reserve;
			अगर (cdb[0] == RESERVE_10)
				size = get_unaligned_be16(&cdb[7]);
			अन्यथा
				size = cmd->data_length;
			वापस target_cmd_size_check(cmd, size);
		पूर्ण
	पूर्ण

	/* Set DATA_CDB flag क्रम ops that should have it */
	चयन (cdb[0]) अणु
	हाल READ_6:
	हाल READ_10:
	हाल READ_12:
	हाल READ_16:
	हाल WRITE_6:
	हाल WRITE_10:
	हाल WRITE_12:
	हाल WRITE_16:
	हाल WRITE_VERIFY:
	हाल WRITE_VERIFY_12:
	हाल WRITE_VERIFY_16:
	हाल COMPARE_AND_WRITE:
	हाल XDWRITEREAD_10:
		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		अवरोध;
	हाल VARIABLE_LENGTH_CMD:
		चयन (get_unaligned_be16(&cdb[8])) अणु
		हाल READ_32:
		हाल WRITE_32:
		हाल WRITE_VERIFY_32:
		हाल XDWRITEREAD_32:
			cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
			अवरोध;
		पूर्ण
	पूर्ण

	cmd->execute_cmd = exec_cmd;

	वापस TCM_NO_SENSE;
पूर्ण
EXPORT_SYMBOL(passthrough_parse_cdb);
