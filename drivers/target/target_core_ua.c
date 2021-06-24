<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename: target_core_ua.c
 *
 * This file contains logic क्रम SPC-3 Unit Attention emulation
 *
 * (c) Copyright 2009-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <scsi/scsi_proto.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_ua.h"

sense_reason_t
target_scsi3_ua_check(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_dev_entry *deve;
	काष्ठा se_session *sess = cmd->se_sess;
	काष्ठा se_node_acl *nacl;

	अगर (!sess)
		वापस 0;

	nacl = sess->se_node_acl;
	अगर (!nacl)
		वापस 0;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, cmd->orig_fe_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	अगर (list_empty_careful(&deve->ua_list)) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();
	/*
	 * From sam4r14, section 5.14 Unit attention condition:
	 *
	 * a) अगर an INQUIRY command enters the enabled command state, the
	 *    device server shall process the INQUIRY command and shall neither
	 *    report nor clear any unit attention condition;
	 * b) अगर a REPORT LUNS command enters the enabled command state, the
	 *    device server shall process the REPORT LUNS command and shall not
	 *    report any unit attention condition;
	 * e) अगर a REQUEST SENSE command enters the enabled command state जबतक
	 *    a unit attention condition exists क्रम the SCSI initiator port
	 *    associated with the I_T nexus on which the REQUEST SENSE command
	 *    was received, then the device server shall process the command
	 *    and either:
	 */
	चयन (cmd->t_task_cdb[0]) अणु
	हाल INQUIRY:
	हाल REPORT_LUNS:
	हाल REQUEST_SENSE:
		वापस 0;
	शेष:
		वापस TCM_CHECK_CONDITION_UNIT_ATTENTION;
	पूर्ण
पूर्ण

पूर्णांक core_scsi3_ua_allocate(
	काष्ठा se_dev_entry *deve,
	u8 asc,
	u8 ascq)
अणु
	काष्ठा se_ua *ua, *ua_p, *ua_पंचांगp;

	ua = kmem_cache_zalloc(se_ua_cache, GFP_ATOMIC);
	अगर (!ua) अणु
		pr_err("Unable to allocate struct se_ua\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&ua->ua_nacl_list);

	ua->ua_asc = asc;
	ua->ua_ascq = ascq;

	spin_lock(&deve->ua_lock);
	list_क्रम_each_entry_safe(ua_p, ua_पंचांगp, &deve->ua_list, ua_nacl_list) अणु
		/*
		 * Do not report the same UNIT ATTENTION twice..
		 */
		अगर ((ua_p->ua_asc == asc) && (ua_p->ua_ascq == ascq)) अणु
			spin_unlock(&deve->ua_lock);
			kmem_cache_मुक्त(se_ua_cache, ua);
			वापस 0;
		पूर्ण
		/*
		 * Attach the highest priority Unit Attention to
		 * the head of the list following sam4r14,
		 * Section 5.14 Unit Attention Condition:
		 *
		 * POWER ON, RESET, OR BUS DEVICE RESET OCCURRED highest
		 * POWER ON OCCURRED or
		 * DEVICE INTERNAL RESET
		 * SCSI BUS RESET OCCURRED or
		 * MICROCODE HAS BEEN CHANGED or
		 * protocol specअगरic
		 * BUS DEVICE RESET FUNCTION OCCURRED
		 * I_T NEXUS LOSS OCCURRED
		 * COMMANDS CLEARED BY POWER LOSS NOTIFICATION
		 * all others                                    Lowest
		 *
		 * Each of the ASCQ codes listed above are defined in
		 * the 29h ASC family, see spc4r17 Table D.1
		 */
		अगर (ua_p->ua_asc == 0x29) अणु
			अगर ((asc == 0x29) && (ascq > ua_p->ua_ascq))
				list_add(&ua->ua_nacl_list,
						&deve->ua_list);
			अन्यथा
				list_add_tail(&ua->ua_nacl_list,
						&deve->ua_list);
		पूर्ण अन्यथा अगर (ua_p->ua_asc == 0x2a) अणु
			/*
			 * Incoming Family 29h ASCQ codes will override
			 * Family 2AHh ASCQ codes क्रम Unit Attention condition.
			 */
			अगर ((asc == 0x29) || (ascq > ua_p->ua_asc))
				list_add(&ua->ua_nacl_list,
					&deve->ua_list);
			अन्यथा
				list_add_tail(&ua->ua_nacl_list,
						&deve->ua_list);
		पूर्ण अन्यथा
			list_add_tail(&ua->ua_nacl_list,
				&deve->ua_list);
		spin_unlock(&deve->ua_lock);

		वापस 0;
	पूर्ण
	list_add_tail(&ua->ua_nacl_list, &deve->ua_list);
	spin_unlock(&deve->ua_lock);

	pr_debug("Allocated UNIT ATTENTION, mapped LUN: %llu, ASC:"
		" 0x%02x, ASCQ: 0x%02x\n", deve->mapped_lun,
		asc, ascq);

	वापस 0;
पूर्ण

व्योम target_ua_allocate_lun(काष्ठा se_node_acl *nacl,
			    u32 unpacked_lun, u8 asc, u8 ascq)
अणु
	काष्ठा se_dev_entry *deve;

	अगर (!nacl)
		वापस;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, unpacked_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	core_scsi3_ua_allocate(deve, asc, ascq);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम core_scsi3_ua_release_all(
	काष्ठा se_dev_entry *deve)
अणु
	काष्ठा se_ua *ua, *ua_p;

	spin_lock(&deve->ua_lock);
	list_क्रम_each_entry_safe(ua, ua_p, &deve->ua_list, ua_nacl_list) अणु
		list_del(&ua->ua_nacl_list);
		kmem_cache_मुक्त(se_ua_cache, ua);
	पूर्ण
	spin_unlock(&deve->ua_lock);
पूर्ण

/*
 * Dequeue a unit attention from the unit attention list. This function
 * वापसs true अगर the dequeuing succeeded and अगर *@key, *@asc and *@ascq have
 * been set.
 */
bool core_scsi3_ua_क्रम_check_condition(काष्ठा se_cmd *cmd, u8 *key, u8 *asc,
				       u8 *ascq)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_dev_entry *deve;
	काष्ठा se_session *sess = cmd->se_sess;
	काष्ठा se_node_acl *nacl;
	काष्ठा se_ua *ua = शून्य, *ua_p;
	पूर्णांक head = 1;
	bool dev_ua_पूर्णांकlck_clear = (dev->dev_attrib.emulate_ua_पूर्णांकlck_ctrl
						== TARGET_UA_INTLCK_CTRL_CLEAR);

	अगर (WARN_ON_ONCE(!sess))
		वापस false;

	nacl = sess->se_node_acl;
	अगर (WARN_ON_ONCE(!nacl))
		वापस false;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, cmd->orig_fe_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		*key = ILLEGAL_REQUEST;
		*asc = 0x25; /* LOGICAL UNIT NOT SUPPORTED */
		*ascq = 0;
		वापस true;
	पूर्ण
	*key = UNIT_ATTENTION;
	/*
	 * The highest priority Unit Attentions are placed at the head of the
	 * काष्ठा se_dev_entry->ua_list, and will be वापसed in CHECK_CONDITION +
	 * sense data क्रम the received CDB.
	 */
	spin_lock(&deve->ua_lock);
	list_क्रम_each_entry_safe(ua, ua_p, &deve->ua_list, ua_nacl_list) अणु
		/*
		 * For ua_पूर्णांकlck_ctrl code not equal to 00b, only report the
		 * highest priority UNIT_ATTENTION and ASC/ASCQ without
		 * clearing it.
		 */
		अगर (!dev_ua_पूर्णांकlck_clear) अणु
			*asc = ua->ua_asc;
			*ascq = ua->ua_ascq;
			अवरोध;
		पूर्ण
		/*
		 * Otherwise क्रम the शेष 00b, release the UNIT ATTENTION
		 * condition.  Return the ASC/ASCQ of the highest priority UA
		 * (head of the list) in the outgoing CHECK_CONDITION + sense.
		 */
		अगर (head) अणु
			*asc = ua->ua_asc;
			*ascq = ua->ua_ascq;
			head = 0;
		पूर्ण
		list_del(&ua->ua_nacl_list);
		kmem_cache_मुक्त(se_ua_cache, ua);
	पूर्ण
	spin_unlock(&deve->ua_lock);
	rcu_पढ़ो_unlock();

	pr_debug("[%s]: %s UNIT ATTENTION condition with"
		" INTLCK_CTRL: %d, mapped LUN: %llu, got CDB: 0x%02x"
		" reported ASC: 0x%02x, ASCQ: 0x%02x\n",
		nacl->se_tpg->se_tpg_tfo->fabric_name,
		dev_ua_पूर्णांकlck_clear ? "Releasing" : "Reporting",
		dev->dev_attrib.emulate_ua_पूर्णांकlck_ctrl,
		cmd->orig_fe_lun, cmd->t_task_cdb[0], *asc, *ascq);

	वापस head == 0;
पूर्ण

पूर्णांक core_scsi3_ua_clear_क्रम_request_sense(
	काष्ठा se_cmd *cmd,
	u8 *asc,
	u8 *ascq)
अणु
	काष्ठा se_dev_entry *deve;
	काष्ठा se_session *sess = cmd->se_sess;
	काष्ठा se_node_acl *nacl;
	काष्ठा se_ua *ua = शून्य, *ua_p;
	पूर्णांक head = 1;

	अगर (!sess)
		वापस -EINVAL;

	nacl = sess->se_node_acl;
	अगर (!nacl)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, cmd->orig_fe_lun);
	अगर (!deve) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	अगर (list_empty_careful(&deve->ua_list)) अणु
		rcu_पढ़ो_unlock();
		वापस -EPERM;
	पूर्ण
	/*
	 * The highest priority Unit Attentions are placed at the head of the
	 * काष्ठा se_dev_entry->ua_list.  The First (and hence highest priority)
	 * ASC/ASCQ will be वापसed in REQUEST_SENSE payload data क्रम the
	 * matching काष्ठा se_lun.
	 *
	 * Once the वापसing ASC/ASCQ values are set, we go ahead and
	 * release all of the Unit Attention conditions क्रम the associated
	 * काष्ठा se_lun.
	 */
	spin_lock(&deve->ua_lock);
	list_क्रम_each_entry_safe(ua, ua_p, &deve->ua_list, ua_nacl_list) अणु
		अगर (head) अणु
			*asc = ua->ua_asc;
			*ascq = ua->ua_ascq;
			head = 0;
		पूर्ण
		list_del(&ua->ua_nacl_list);
		kmem_cache_मुक्त(se_ua_cache, ua);
	पूर्ण
	spin_unlock(&deve->ua_lock);
	rcu_पढ़ो_unlock();

	pr_debug("[%s]: Released UNIT ATTENTION condition, mapped"
		" LUN: %llu, got REQUEST_SENSE reported ASC: 0x%02x,"
		" ASCQ: 0x%02x\n", nacl->se_tpg->se_tpg_tfo->fabric_name,
		cmd->orig_fe_lun, *asc, *ascq);

	वापस (head) ? -EPERM : 0;
पूर्ण
