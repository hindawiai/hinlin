<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic SCSI-3 ALUA SCSI Device Handler
 *
 * Copyright (C) 2007-2010 Hannes Reinecke, SUSE Linux Products GmbH.
 * All rights reserved.
 */
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_dh.h>

#घोषणा ALUA_DH_NAME "alua"
#घोषणा ALUA_DH_VER "2.0"

#घोषणा TPGS_SUPPORT_NONE		0x00
#घोषणा TPGS_SUPPORT_OPTIMIZED		0x01
#घोषणा TPGS_SUPPORT_NONOPTIMIZED	0x02
#घोषणा TPGS_SUPPORT_STANDBY		0x04
#घोषणा TPGS_SUPPORT_UNAVAILABLE	0x08
#घोषणा TPGS_SUPPORT_LBA_DEPENDENT	0x10
#घोषणा TPGS_SUPPORT_OFFLINE		0x40
#घोषणा TPGS_SUPPORT_TRANSITION		0x80
#घोषणा TPGS_SUPPORT_ALL		0xdf

#घोषणा RTPG_FMT_MASK			0x70
#घोषणा RTPG_FMT_EXT_HDR		0x10

#घोषणा TPGS_MODE_UNINITIALIZED		 -1
#घोषणा TPGS_MODE_NONE			0x0
#घोषणा TPGS_MODE_IMPLICIT		0x1
#घोषणा TPGS_MODE_EXPLICIT		0x2

#घोषणा ALUA_RTPG_SIZE			128
#घोषणा ALUA_FAILOVER_TIMEOUT		60
#घोषणा ALUA_FAILOVER_RETRIES		5
#घोषणा ALUA_RTPG_DELAY_MSECS		5
#घोषणा ALUA_RTPG_RETRY_DELAY		2

/* device handler flags */
#घोषणा ALUA_OPTIMIZE_STPG		0x01
#घोषणा ALUA_RTPG_EXT_HDR_UNSUPP	0x02
/* State machine flags */
#घोषणा ALUA_PG_RUN_RTPG		0x10
#घोषणा ALUA_PG_RUN_STPG		0x20
#घोषणा ALUA_PG_RUNNING			0x40

अटल uपूर्णांक optimize_stpg;
module_param(optimize_stpg, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(optimize_stpg, "Allow use of a non-optimized path, rather than sending a STPG, when implicit TPGS is supported (0=No,1=Yes). Default is 0.");

अटल LIST_HEAD(port_group_list);
अटल DEFINE_SPINLOCK(port_group_lock);
अटल काष्ठा workqueue_काष्ठा *kaluad_wq;

काष्ठा alua_port_group अणु
	काष्ठा kref		kref;
	काष्ठा rcu_head		rcu;
	काष्ठा list_head	node;
	काष्ठा list_head	dh_list;
	अचिन्हित अक्षर		device_id_str[256];
	पूर्णांक			device_id_len;
	पूर्णांक			group_id;
	पूर्णांक			tpgs;
	पूर्णांक			state;
	पूर्णांक			pref;
	पूर्णांक			valid_states;
	अचिन्हित		flags; /* used क्रम optimizing STPG */
	अचिन्हित अक्षर		transition_पंचांगo;
	अचिन्हित दीर्घ		expiry;
	अचिन्हित दीर्घ		पूर्णांकerval;
	काष्ठा delayed_work	rtpg_work;
	spinlock_t		lock;
	काष्ठा list_head	rtpg_list;
	काष्ठा scsi_device	*rtpg_sdev;
पूर्ण;

काष्ठा alua_dh_data अणु
	काष्ठा list_head	node;
	काष्ठा alua_port_group __rcu *pg;
	पूर्णांक			group_id;
	spinlock_t		pg_lock;
	काष्ठा scsi_device	*sdev;
	पूर्णांक			init_error;
	काष्ठा mutex		init_mutex;
पूर्ण;

काष्ठा alua_queue_data अणु
	काष्ठा list_head	entry;
	activate_complete	callback_fn;
	व्योम			*callback_data;
पूर्ण;

#घोषणा ALUA_POLICY_SWITCH_CURRENT	0
#घोषणा ALUA_POLICY_SWITCH_ALL		1

अटल व्योम alua_rtpg_work(काष्ठा work_काष्ठा *work);
अटल bool alua_rtpg_queue(काष्ठा alua_port_group *pg,
			    काष्ठा scsi_device *sdev,
			    काष्ठा alua_queue_data *qdata, bool क्रमce);
अटल व्योम alua_check(काष्ठा scsi_device *sdev, bool क्रमce);

अटल व्योम release_port_group(काष्ठा kref *kref)
अणु
	काष्ठा alua_port_group *pg;

	pg = container_of(kref, काष्ठा alua_port_group, kref);
	अगर (pg->rtpg_sdev)
		flush_delayed_work(&pg->rtpg_work);
	spin_lock(&port_group_lock);
	list_del(&pg->node);
	spin_unlock(&port_group_lock);
	kमुक्त_rcu(pg, rcu);
पूर्ण

/*
 * submit_rtpg - Issue a REPORT TARGET GROUP STATES command
 * @sdev: sdev the command should be sent to
 */
अटल पूर्णांक submit_rtpg(काष्ठा scsi_device *sdev, अचिन्हित अक्षर *buff,
		       पूर्णांक bufflen, काष्ठा scsi_sense_hdr *sshdr, पूर्णांक flags)
अणु
	u8 cdb[MAX_COMMAND_SIZE];
	पूर्णांक req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

	/* Prepare the command. */
	स_रखो(cdb, 0x0, MAX_COMMAND_SIZE);
	cdb[0] = MAINTEन_अंकCE_IN;
	अगर (!(flags & ALUA_RTPG_EXT_HDR_UNSUPP))
		cdb[1] = MI_REPORT_TARGET_PGS | MI_EXT_HDR_PARAM_FMT;
	अन्यथा
		cdb[1] = MI_REPORT_TARGET_PGS;
	put_unaligned_be32(bufflen, &cdb[6]);

	वापस scsi_execute(sdev, cdb, DMA_FROM_DEVICE, buff, bufflen, शून्य,
			sshdr, ALUA_FAILOVER_TIMEOUT * HZ,
			ALUA_FAILOVER_RETRIES, req_flags, 0, शून्य);
पूर्ण

/*
 * submit_stpg - Issue a SET TARGET PORT GROUP command
 *
 * Currently we're only setting the current target port group state
 * to 'active/optimized' and let the array firmware figure out
 * the states of the reमुख्यing groups.
 */
अटल पूर्णांक submit_stpg(काष्ठा scsi_device *sdev, पूर्णांक group_id,
		       काष्ठा scsi_sense_hdr *sshdr)
अणु
	u8 cdb[MAX_COMMAND_SIZE];
	अचिन्हित अक्षर stpg_data[8];
	पूर्णांक stpg_len = 8;
	पूर्णांक req_flags = REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT |
		REQ_FAILFAST_DRIVER;

	/* Prepare the data buffer */
	स_रखो(stpg_data, 0, stpg_len);
	stpg_data[4] = SCSI_ACCESS_STATE_OPTIMAL;
	put_unaligned_be16(group_id, &stpg_data[6]);

	/* Prepare the command. */
	स_रखो(cdb, 0x0, MAX_COMMAND_SIZE);
	cdb[0] = MAINTEन_अंकCE_OUT;
	cdb[1] = MO_SET_TARGET_PGS;
	put_unaligned_be32(stpg_len, &cdb[6]);

	वापस scsi_execute(sdev, cdb, DMA_TO_DEVICE, stpg_data, stpg_len, शून्य,
			sshdr, ALUA_FAILOVER_TIMEOUT * HZ,
			ALUA_FAILOVER_RETRIES, req_flags, 0, शून्य);
पूर्ण

अटल काष्ठा alua_port_group *alua_find_get_pg(अक्षर *id_str, माप_प्रकार id_size,
						पूर्णांक group_id)
अणु
	काष्ठा alua_port_group *pg;

	अगर (!id_str || !id_size || !म_माप(id_str))
		वापस शून्य;

	list_क्रम_each_entry(pg, &port_group_list, node) अणु
		अगर (pg->group_id != group_id)
			जारी;
		अगर (!pg->device_id_len || pg->device_id_len != id_size)
			जारी;
		अगर (म_भेदन(pg->device_id_str, id_str, id_size))
			जारी;
		अगर (!kref_get_unless_zero(&pg->kref))
			जारी;
		वापस pg;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * alua_alloc_pg - Allocate a new port_group काष्ठाure
 * @sdev: scsi device
 * @group_id: port group id
 * @tpgs: target port group settings
 *
 * Allocate a new port_group काष्ठाure क्रम a given
 * device.
 */
अटल काष्ठा alua_port_group *alua_alloc_pg(काष्ठा scsi_device *sdev,
					     पूर्णांक group_id, पूर्णांक tpgs)
अणु
	काष्ठा alua_port_group *pg, *पंचांगp_pg;

	pg = kzalloc(माप(काष्ठा alua_port_group), GFP_KERNEL);
	अगर (!pg)
		वापस ERR_PTR(-ENOMEM);

	pg->device_id_len = scsi_vpd_lun_id(sdev, pg->device_id_str,
					    माप(pg->device_id_str));
	अगर (pg->device_id_len <= 0) अणु
		/*
		 * TPGS supported but no device identअगरication found.
		 * Generate निजी device identअगरication.
		 */
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: No device descriptors found\n",
			    ALUA_DH_NAME);
		pg->device_id_str[0] = '\0';
		pg->device_id_len = 0;
	पूर्ण
	pg->group_id = group_id;
	pg->tpgs = tpgs;
	pg->state = SCSI_ACCESS_STATE_OPTIMAL;
	pg->valid_states = TPGS_SUPPORT_ALL;
	अगर (optimize_stpg)
		pg->flags |= ALUA_OPTIMIZE_STPG;
	kref_init(&pg->kref);
	INIT_DELAYED_WORK(&pg->rtpg_work, alua_rtpg_work);
	INIT_LIST_HEAD(&pg->rtpg_list);
	INIT_LIST_HEAD(&pg->node);
	INIT_LIST_HEAD(&pg->dh_list);
	spin_lock_init(&pg->lock);

	spin_lock(&port_group_lock);
	पंचांगp_pg = alua_find_get_pg(pg->device_id_str, pg->device_id_len,
				  group_id);
	अगर (पंचांगp_pg) अणु
		spin_unlock(&port_group_lock);
		kमुक्त(pg);
		वापस पंचांगp_pg;
	पूर्ण

	list_add(&pg->node, &port_group_list);
	spin_unlock(&port_group_lock);

	वापस pg;
पूर्ण

/*
 * alua_check_tpgs - Evaluate TPGS setting
 * @sdev: device to be checked
 *
 * Examine the TPGS setting of the sdev to find out अगर ALUA
 * is supported.
 */
अटल पूर्णांक alua_check_tpgs(काष्ठा scsi_device *sdev)
अणु
	पूर्णांक tpgs = TPGS_MODE_NONE;

	/*
	 * ALUA support क्रम non-disk devices is fraught with
	 * dअगरficulties, so disable it क्रम now.
	 */
	अगर (sdev->type != TYPE_DISK) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: disable for non-disk devices\n",
			    ALUA_DH_NAME);
		वापस tpgs;
	पूर्ण

	tpgs = scsi_device_tpgs(sdev);
	चयन (tpgs) अणु
	हाल TPGS_MODE_EXPLICIT|TPGS_MODE_IMPLICIT:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: supports implicit and explicit TPGS\n",
			    ALUA_DH_NAME);
		अवरोध;
	हाल TPGS_MODE_EXPLICIT:
		sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: supports explicit TPGS\n",
			    ALUA_DH_NAME);
		अवरोध;
	हाल TPGS_MODE_IMPLICIT:
		sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: supports implicit TPGS\n",
			    ALUA_DH_NAME);
		अवरोध;
	हाल TPGS_MODE_NONE:
		sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: not supported\n",
			    ALUA_DH_NAME);
		अवरोध;
	शेष:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: unsupported TPGS setting %d\n",
			    ALUA_DH_NAME, tpgs);
		tpgs = TPGS_MODE_NONE;
		अवरोध;
	पूर्ण

	वापस tpgs;
पूर्ण

/*
 * alua_check_vpd - Evaluate INQUIRY vpd page 0x83
 * @sdev: device to be checked
 *
 * Extract the relative target port and the target port group
 * descriptor from the list of identअगरicators.
 */
अटल पूर्णांक alua_check_vpd(काष्ठा scsi_device *sdev, काष्ठा alua_dh_data *h,
			  पूर्णांक tpgs)
अणु
	पूर्णांक rel_port = -1, group_id;
	काष्ठा alua_port_group *pg, *old_pg = शून्य;
	bool pg_updated = false;
	अचिन्हित दीर्घ flags;

	group_id = scsi_vpd_tpg_id(sdev, &rel_port);
	अगर (group_id < 0) अणु
		/*
		 * Internal error; TPGS supported but required
		 * VPD identअगरication descriptors not present.
		 * Disable ALUA support
		 */
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: No target port descriptors found\n",
			    ALUA_DH_NAME);
		वापस SCSI_DH_DEV_UNSUPP;
	पूर्ण

	pg = alua_alloc_pg(sdev, group_id, tpgs);
	अगर (IS_ERR(pg)) अणु
		अगर (PTR_ERR(pg) == -ENOMEM)
			वापस SCSI_DH_NOMEM;
		वापस SCSI_DH_DEV_UNSUPP;
	पूर्ण
	अगर (pg->device_id_len)
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: device %s port group %x rel port %x\n",
			    ALUA_DH_NAME, pg->device_id_str,
			    group_id, rel_port);
	अन्यथा
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: port group %x rel port %x\n",
			    ALUA_DH_NAME, group_id, rel_port);

	/* Check क्रम existing port group references */
	spin_lock(&h->pg_lock);
	old_pg = rcu_dereference_रक्षित(h->pg, lockdep_is_held(&h->pg_lock));
	अगर (old_pg != pg) अणु
		/* port group has changed. Update to new port group */
		अगर (h->pg) अणु
			spin_lock_irqsave(&old_pg->lock, flags);
			list_del_rcu(&h->node);
			spin_unlock_irqrestore(&old_pg->lock, flags);
		पूर्ण
		rcu_assign_poपूर्णांकer(h->pg, pg);
		pg_updated = true;
	पूर्ण

	spin_lock_irqsave(&pg->lock, flags);
	अगर (pg_updated)
		list_add_rcu(&h->node, &pg->dh_list);
	spin_unlock_irqrestore(&pg->lock, flags);

	alua_rtpg_queue(rcu_dereference_रक्षित(h->pg,
						  lockdep_is_held(&h->pg_lock)),
			sdev, शून्य, true);
	spin_unlock(&h->pg_lock);

	अगर (old_pg)
		kref_put(&old_pg->kref, release_port_group);

	वापस SCSI_DH_OK;
पूर्ण

अटल अक्षर prपूर्णांक_alua_state(अचिन्हित अक्षर state)
अणु
	चयन (state) अणु
	हाल SCSI_ACCESS_STATE_OPTIMAL:
		वापस 'A';
	हाल SCSI_ACCESS_STATE_ACTIVE:
		वापस 'N';
	हाल SCSI_ACCESS_STATE_STANDBY:
		वापस 'S';
	हाल SCSI_ACCESS_STATE_UNAVAILABLE:
		वापस 'U';
	हाल SCSI_ACCESS_STATE_LBA:
		वापस 'L';
	हाल SCSI_ACCESS_STATE_OFFLINE:
		वापस 'O';
	हाल SCSI_ACCESS_STATE_TRANSITIONING:
		वापस 'T';
	शेष:
		वापस 'X';
	पूर्ण
पूर्ण

अटल क्रमागत scsi_disposition alua_check_sense(काष्ठा scsi_device *sdev,
					      काष्ठा scsi_sense_hdr *sense_hdr)
अणु
	काष्ठा alua_dh_data *h = sdev->handler_data;
	काष्ठा alua_port_group *pg;

	चयन (sense_hdr->sense_key) अणु
	हाल NOT_READY:
		अगर (sense_hdr->asc == 0x04 && sense_hdr->ascq == 0x0a) अणु
			/*
			 * LUN Not Accessible - ALUA state transition
			 */
			rcu_पढ़ो_lock();
			pg = rcu_dereference(h->pg);
			अगर (pg)
				pg->state = SCSI_ACCESS_STATE_TRANSITIONING;
			rcu_पढ़ो_unlock();
			alua_check(sdev, false);
			वापस NEEDS_RETRY;
		पूर्ण
		अवरोध;
	हाल UNIT_ATTENTION:
		अगर (sense_hdr->asc == 0x29 && sense_hdr->ascq == 0x00) अणु
			/*
			 * Power On, Reset, or Bus Device Reset.
			 * Might have obscured a state transition,
			 * so schedule a recheck.
			 */
			alua_check(sdev, true);
			वापस ADD_TO_MLQUEUE;
		पूर्ण
		अगर (sense_hdr->asc == 0x29 && sense_hdr->ascq == 0x04)
			/*
			 * Device पूर्णांकernal reset
			 */
			वापस ADD_TO_MLQUEUE;
		अगर (sense_hdr->asc == 0x2a && sense_hdr->ascq == 0x01)
			/*
			 * Mode Parameters Changed
			 */
			वापस ADD_TO_MLQUEUE;
		अगर (sense_hdr->asc == 0x2a && sense_hdr->ascq == 0x06) अणु
			/*
			 * ALUA state changed
			 */
			alua_check(sdev, true);
			वापस ADD_TO_MLQUEUE;
		पूर्ण
		अगर (sense_hdr->asc == 0x2a && sense_hdr->ascq == 0x07) अणु
			/*
			 * Implicit ALUA state transition failed
			 */
			alua_check(sdev, true);
			वापस ADD_TO_MLQUEUE;
		पूर्ण
		अगर (sense_hdr->asc == 0x3f && sense_hdr->ascq == 0x03)
			/*
			 * Inquiry data has changed
			 */
			वापस ADD_TO_MLQUEUE;
		अगर (sense_hdr->asc == 0x3f && sense_hdr->ascq == 0x0e)
			/*
			 * REPORTED_LUNS_DATA_HAS_CHANGED is reported
			 * when चयनing controllers on tarमाला_लो like
			 * Intel Multi-Flex. We can just retry.
			 */
			वापस ADD_TO_MLQUEUE;
		अवरोध;
	पूर्ण

	वापस SCSI_RETURN_NOT_HANDLED;
पूर्ण

/*
 * alua_tur - Send a TEST UNIT READY
 * @sdev: device to which the TEST UNIT READY command should be send
 *
 * Send a TEST UNIT READY to @sdev to figure out the device state
 * Returns SCSI_DH_RETRY अगर the sense code is NOT READY/ALUA TRANSITIONING,
 * SCSI_DH_OK अगर no error occurred, and SCSI_DH_IO otherwise.
 */
अटल पूर्णांक alua_tur(काष्ठा scsi_device *sdev)
अणु
	काष्ठा scsi_sense_hdr sense_hdr;
	पूर्णांक retval;

	retval = scsi_test_unit_पढ़ोy(sdev, ALUA_FAILOVER_TIMEOUT * HZ,
				      ALUA_FAILOVER_RETRIES, &sense_hdr);
	अगर (sense_hdr.sense_key == NOT_READY &&
	    sense_hdr.asc == 0x04 && sense_hdr.ascq == 0x0a)
		वापस SCSI_DH_RETRY;
	अन्यथा अगर (retval)
		वापस SCSI_DH_IO;
	अन्यथा
		वापस SCSI_DH_OK;
पूर्ण

/*
 * alua_rtpg - Evaluate REPORT TARGET GROUP STATES
 * @sdev: the device to be evaluated.
 *
 * Evaluate the Target Port Group State.
 * Returns SCSI_DH_DEV_OFFLINED अगर the path is
 * found to be unusable.
 */
अटल पूर्णांक alua_rtpg(काष्ठा scsi_device *sdev, काष्ठा alua_port_group *pg)
अणु
	काष्ठा scsi_sense_hdr sense_hdr;
	काष्ठा alua_port_group *पंचांगp_pg;
	पूर्णांक len, k, off, bufflen = ALUA_RTPG_SIZE;
	पूर्णांक group_id_old, state_old, pref_old, valid_states_old;
	अचिन्हित अक्षर *desc, *buff;
	अचिन्हित err, retval;
	अचिन्हित पूर्णांक tpg_desc_tbl_off;
	अचिन्हित अक्षर orig_transition_पंचांगo;
	अचिन्हित दीर्घ flags;
	bool transitioning_sense = false;

	group_id_old = pg->group_id;
	state_old = pg->state;
	pref_old = pg->pref;
	valid_states_old = pg->valid_states;

	अगर (!pg->expiry) अणु
		अचिन्हित दीर्घ transition_पंचांगo = ALUA_FAILOVER_TIMEOUT * HZ;

		अगर (pg->transition_पंचांगo)
			transition_पंचांगo = pg->transition_पंचांगo * HZ;

		pg->expiry = round_jअगरfies_up(jअगरfies + transition_पंचांगo);
	पूर्ण

	buff = kzalloc(bufflen, GFP_KERNEL);
	अगर (!buff)
		वापस SCSI_DH_DEV_TEMP_BUSY;

 retry:
	err = 0;
	retval = submit_rtpg(sdev, buff, bufflen, &sense_hdr, pg->flags);

	अगर (retval) अणु
		/*
		 * Some (broken) implementations have a habit of वापसing
		 * an error during things like firmware update etc.
		 * But अगर the target only supports active/optimized there's
		 * not much we can करो; it's not that we can चयन paths
		 * or anything.
		 * So ignore any errors to aव्योम spurious failures during
		 * path failover.
		 */
		अगर ((pg->valid_states & ~TPGS_SUPPORT_OPTIMIZED) == 0) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "%s: ignoring rtpg result %d\n",
				    ALUA_DH_NAME, retval);
			kमुक्त(buff);
			वापस SCSI_DH_OK;
		पूर्ण
		अगर (!scsi_sense_valid(&sense_hdr)) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "%s: rtpg failed, result %d\n",
				    ALUA_DH_NAME, retval);
			kमुक्त(buff);
			अगर (driver_byte(retval) == DRIVER_ERROR)
				वापस SCSI_DH_DEV_TEMP_BUSY;
			वापस SCSI_DH_IO;
		पूर्ण

		/*
		 * submit_rtpg() has failed on existing arrays
		 * when requesting extended header info, and
		 * the array करोesn't support extended headers,
		 * even though it shouldn't according to T10.
		 * The retry without rtpg_ext_hdr_req set
		 * handles this.
		 * Note:  some arrays वापस a sense key of ILLEGAL_REQUEST
		 * with ASC 00h अगर they करोn't support the extended header.
		 */
		अगर (!(pg->flags & ALUA_RTPG_EXT_HDR_UNSUPP) &&
		    sense_hdr.sense_key == ILLEGAL_REQUEST) अणु
			pg->flags |= ALUA_RTPG_EXT_HDR_UNSUPP;
			जाओ retry;
		पूर्ण
		/*
		 * If the array वापसs with 'ALUA state transition'
		 * sense code here it cannot वापस RTPG data during
		 * transition. So set the state to 'transitioning' directly.
		 */
		अगर (sense_hdr.sense_key == NOT_READY &&
		    sense_hdr.asc == 0x04 && sense_hdr.ascq == 0x0a) अणु
			transitioning_sense = true;
			जाओ skip_rtpg;
		पूर्ण
		/*
		 * Retry on any other UNIT ATTENTION occurred.
		 */
		अगर (sense_hdr.sense_key == UNIT_ATTENTION)
			err = SCSI_DH_RETRY;
		अगर (err == SCSI_DH_RETRY &&
		    pg->expiry != 0 && समय_beक्रमe(jअगरfies, pg->expiry)) अणु
			sdev_prपूर्णांकk(KERN_ERR, sdev, "%s: rtpg retry\n",
				    ALUA_DH_NAME);
			scsi_prपूर्णांक_sense_hdr(sdev, ALUA_DH_NAME, &sense_hdr);
			kमुक्त(buff);
			वापस err;
		पूर्ण
		sdev_prपूर्णांकk(KERN_ERR, sdev, "%s: rtpg failed\n",
			    ALUA_DH_NAME);
		scsi_prपूर्णांक_sense_hdr(sdev, ALUA_DH_NAME, &sense_hdr);
		kमुक्त(buff);
		pg->expiry = 0;
		वापस SCSI_DH_IO;
	पूर्ण

	len = get_unaligned_be32(&buff[0]) + 4;

	अगर (len > bufflen) अणु
		/* Resubmit with the correct length */
		kमुक्त(buff);
		bufflen = len;
		buff = kदो_स्मृति(bufflen, GFP_KERNEL);
		अगर (!buff) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				    "%s: kmalloc buffer failed\n",__func__);
			/* Temporary failure, bypass */
			pg->expiry = 0;
			वापस SCSI_DH_DEV_TEMP_BUSY;
		पूर्ण
		जाओ retry;
	पूर्ण

	orig_transition_पंचांगo = pg->transition_पंचांगo;
	अगर ((buff[4] & RTPG_FMT_MASK) == RTPG_FMT_EXT_HDR && buff[5] != 0)
		pg->transition_पंचांगo = buff[5];
	अन्यथा
		pg->transition_पंचांगo = ALUA_FAILOVER_TIMEOUT;

	अगर (orig_transition_पंचांगo != pg->transition_पंचांगo) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: transition timeout set to %d seconds\n",
			    ALUA_DH_NAME, pg->transition_पंचांगo);
		pg->expiry = jअगरfies + pg->transition_पंचांगo * HZ;
	पूर्ण

	अगर ((buff[4] & RTPG_FMT_MASK) == RTPG_FMT_EXT_HDR)
		tpg_desc_tbl_off = 8;
	अन्यथा
		tpg_desc_tbl_off = 4;

	क्रम (k = tpg_desc_tbl_off, desc = buff + tpg_desc_tbl_off;
	     k < len;
	     k += off, desc += off) अणु
		u16 group_id = get_unaligned_be16(&desc[2]);

		spin_lock_irqsave(&port_group_lock, flags);
		पंचांगp_pg = alua_find_get_pg(pg->device_id_str, pg->device_id_len,
					  group_id);
		spin_unlock_irqrestore(&port_group_lock, flags);
		अगर (पंचांगp_pg) अणु
			अगर (spin_trylock_irqsave(&पंचांगp_pg->lock, flags)) अणु
				अगर ((पंचांगp_pg == pg) ||
				    !(पंचांगp_pg->flags & ALUA_PG_RUNNING)) अणु
					काष्ठा alua_dh_data *h;

					पंचांगp_pg->state = desc[0] & 0x0f;
					पंचांगp_pg->pref = desc[0] >> 7;
					rcu_पढ़ो_lock();
					list_क्रम_each_entry_rcu(h,
						&पंचांगp_pg->dh_list, node) अणु
						अगर (!h->sdev)
							जारी;
						h->sdev->access_state = desc[0];
					पूर्ण
					rcu_पढ़ो_unlock();
				पूर्ण
				अगर (पंचांगp_pg == pg)
					पंचांगp_pg->valid_states = desc[1];
				spin_unlock_irqrestore(&पंचांगp_pg->lock, flags);
			पूर्ण
			kref_put(&पंचांगp_pg->kref, release_port_group);
		पूर्ण
		off = 8 + (desc[7] * 4);
	पूर्ण

 skip_rtpg:
	spin_lock_irqsave(&pg->lock, flags);
	अगर (transitioning_sense)
		pg->state = SCSI_ACCESS_STATE_TRANSITIONING;

	अगर (group_id_old != pg->group_id || state_old != pg->state ||
		pref_old != pg->pref || valid_states_old != pg->valid_states)
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			"%s: port group %02x state %c %s supports %c%c%c%c%c%c%c\n",
			ALUA_DH_NAME, pg->group_id, prपूर्णांक_alua_state(pg->state),
			pg->pref ? "preferred" : "non-preferred",
			pg->valid_states&TPGS_SUPPORT_TRANSITION?'T':'t',
			pg->valid_states&TPGS_SUPPORT_OFFLINE?'O':'o',
			pg->valid_states&TPGS_SUPPORT_LBA_DEPENDENT?'L':'l',
			pg->valid_states&TPGS_SUPPORT_UNAVAILABLE?'U':'u',
			pg->valid_states&TPGS_SUPPORT_STANDBY?'S':'s',
			pg->valid_states&TPGS_SUPPORT_NONOPTIMIZED?'N':'n',
			pg->valid_states&TPGS_SUPPORT_OPTIMIZED?'A':'a');

	चयन (pg->state) अणु
	हाल SCSI_ACCESS_STATE_TRANSITIONING:
		अगर (समय_beक्रमe(jअगरfies, pg->expiry)) अणु
			/* State transition, retry */
			pg->पूर्णांकerval = ALUA_RTPG_RETRY_DELAY;
			err = SCSI_DH_RETRY;
		पूर्ण अन्यथा अणु
			काष्ठा alua_dh_data *h;

			/* Transitioning समय exceeded, set port to standby */
			err = SCSI_DH_IO;
			pg->state = SCSI_ACCESS_STATE_STANDBY;
			pg->expiry = 0;
			rcu_पढ़ो_lock();
			list_क्रम_each_entry_rcu(h, &pg->dh_list, node) अणु
				अगर (!h->sdev)
					जारी;
				h->sdev->access_state =
					(pg->state & SCSI_ACCESS_STATE_MASK);
				अगर (pg->pref)
					h->sdev->access_state |=
						SCSI_ACCESS_STATE_PREFERRED;
			पूर्ण
			rcu_पढ़ो_unlock();
		पूर्ण
		अवरोध;
	हाल SCSI_ACCESS_STATE_OFFLINE:
		/* Path unusable */
		err = SCSI_DH_DEV_OFFLINED;
		pg->expiry = 0;
		अवरोध;
	शेष:
		/* Useable path अगर active */
		err = SCSI_DH_OK;
		pg->expiry = 0;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&pg->lock, flags);
	kमुक्त(buff);
	वापस err;
पूर्ण

/*
 * alua_stpg - Issue a SET TARGET PORT GROUP command
 *
 * Issue a SET TARGET PORT GROUP command and evaluate the
 * response. Returns SCSI_DH_RETRY per शेष to trigger
 * a re-evaluation of the target group state or SCSI_DH_OK
 * अगर no further action needs to be taken.
 */
अटल अचिन्हित alua_stpg(काष्ठा scsi_device *sdev, काष्ठा alua_port_group *pg)
अणु
	पूर्णांक retval;
	काष्ठा scsi_sense_hdr sense_hdr;

	अगर (!(pg->tpgs & TPGS_MODE_EXPLICIT)) अणु
		/* Only implicit ALUA supported, retry */
		वापस SCSI_DH_RETRY;
	पूर्ण
	चयन (pg->state) अणु
	हाल SCSI_ACCESS_STATE_OPTIMAL:
		वापस SCSI_DH_OK;
	हाल SCSI_ACCESS_STATE_ACTIVE:
		अगर ((pg->flags & ALUA_OPTIMIZE_STPG) &&
		    !pg->pref &&
		    (pg->tpgs & TPGS_MODE_IMPLICIT))
			वापस SCSI_DH_OK;
		अवरोध;
	हाल SCSI_ACCESS_STATE_STANDBY:
	हाल SCSI_ACCESS_STATE_UNAVAILABLE:
		अवरोध;
	हाल SCSI_ACCESS_STATE_OFFLINE:
		वापस SCSI_DH_IO;
	हाल SCSI_ACCESS_STATE_TRANSITIONING:
		अवरोध;
	शेष:
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s: stpg failed, unhandled TPGS state %d",
			    ALUA_DH_NAME, pg->state);
		वापस SCSI_DH_NOSYS;
	पूर्ण
	retval = submit_stpg(sdev, pg->group_id, &sense_hdr);

	अगर (retval) अणु
		अगर (!scsi_sense_valid(&sense_hdr)) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				    "%s: stpg failed, result %d",
				    ALUA_DH_NAME, retval);
			अगर (driver_byte(retval) == DRIVER_ERROR)
				वापस SCSI_DH_DEV_TEMP_BUSY;
		पूर्ण अन्यथा अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: stpg failed\n",
				    ALUA_DH_NAME);
			scsi_prपूर्णांक_sense_hdr(sdev, ALUA_DH_NAME, &sense_hdr);
		पूर्ण
	पूर्ण
	/* Retry RTPG */
	वापस SCSI_DH_RETRY;
पूर्ण

अटल व्योम alua_rtpg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा alua_port_group *pg =
		container_of(work, काष्ठा alua_port_group, rtpg_work.work);
	काष्ठा scsi_device *sdev;
	LIST_HEAD(qdata_list);
	पूर्णांक err = SCSI_DH_OK;
	काष्ठा alua_queue_data *qdata, *पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pg->lock, flags);
	sdev = pg->rtpg_sdev;
	अगर (!sdev) अणु
		WARN_ON(pg->flags & ALUA_PG_RUN_RTPG);
		WARN_ON(pg->flags & ALUA_PG_RUN_STPG);
		spin_unlock_irqrestore(&pg->lock, flags);
		kref_put(&pg->kref, release_port_group);
		वापस;
	पूर्ण
	pg->flags |= ALUA_PG_RUNNING;
	अगर (pg->flags & ALUA_PG_RUN_RTPG) अणु
		पूर्णांक state = pg->state;

		pg->flags &= ~ALUA_PG_RUN_RTPG;
		spin_unlock_irqrestore(&pg->lock, flags);
		अगर (state == SCSI_ACCESS_STATE_TRANSITIONING) अणु
			अगर (alua_tur(sdev) == SCSI_DH_RETRY) अणु
				spin_lock_irqsave(&pg->lock, flags);
				pg->flags &= ~ALUA_PG_RUNNING;
				pg->flags |= ALUA_PG_RUN_RTPG;
				अगर (!pg->पूर्णांकerval)
					pg->पूर्णांकerval = ALUA_RTPG_RETRY_DELAY;
				spin_unlock_irqrestore(&pg->lock, flags);
				queue_delayed_work(kaluad_wq, &pg->rtpg_work,
						   pg->पूर्णांकerval * HZ);
				वापस;
			पूर्ण
			/* Send RTPG on failure or अगर TUR indicates SUCCESS */
		पूर्ण
		err = alua_rtpg(sdev, pg);
		spin_lock_irqsave(&pg->lock, flags);
		अगर (err == SCSI_DH_RETRY || pg->flags & ALUA_PG_RUN_RTPG) अणु
			pg->flags &= ~ALUA_PG_RUNNING;
			अगर (!pg->पूर्णांकerval && !(pg->flags & ALUA_PG_RUN_RTPG))
				pg->पूर्णांकerval = ALUA_RTPG_RETRY_DELAY;
			pg->flags |= ALUA_PG_RUN_RTPG;
			spin_unlock_irqrestore(&pg->lock, flags);
			queue_delayed_work(kaluad_wq, &pg->rtpg_work,
					   pg->पूर्णांकerval * HZ);
			वापस;
		पूर्ण
		अगर (err != SCSI_DH_OK)
			pg->flags &= ~ALUA_PG_RUN_STPG;
	पूर्ण
	अगर (pg->flags & ALUA_PG_RUN_STPG) अणु
		pg->flags &= ~ALUA_PG_RUN_STPG;
		spin_unlock_irqrestore(&pg->lock, flags);
		err = alua_stpg(sdev, pg);
		spin_lock_irqsave(&pg->lock, flags);
		अगर (err == SCSI_DH_RETRY || pg->flags & ALUA_PG_RUN_RTPG) अणु
			pg->flags |= ALUA_PG_RUN_RTPG;
			pg->पूर्णांकerval = 0;
			pg->flags &= ~ALUA_PG_RUNNING;
			spin_unlock_irqrestore(&pg->lock, flags);
			queue_delayed_work(kaluad_wq, &pg->rtpg_work,
					   pg->पूर्णांकerval * HZ);
			वापस;
		पूर्ण
	पूर्ण

	list_splice_init(&pg->rtpg_list, &qdata_list);
	pg->rtpg_sdev = शून्य;
	spin_unlock_irqrestore(&pg->lock, flags);

	list_क्रम_each_entry_safe(qdata, पंचांगp, &qdata_list, entry) अणु
		list_del(&qdata->entry);
		अगर (qdata->callback_fn)
			qdata->callback_fn(qdata->callback_data, err);
		kमुक्त(qdata);
	पूर्ण
	spin_lock_irqsave(&pg->lock, flags);
	pg->flags &= ~ALUA_PG_RUNNING;
	spin_unlock_irqrestore(&pg->lock, flags);
	scsi_device_put(sdev);
	kref_put(&pg->kref, release_port_group);
पूर्ण

/**
 * alua_rtpg_queue() - cause RTPG to be submitted asynchronously
 * @pg: ALUA port group associated with @sdev.
 * @sdev: SCSI device क्रम which to submit an RTPG.
 * @qdata: Inक्रमmation about the callback to invoke after the RTPG.
 * @क्रमce: Whether or not to submit an RTPG अगर a work item that will submit an
 *         RTPG alपढ़ोy has been scheduled.
 *
 * Returns true अगर and only अगर alua_rtpg_work() will be called asynchronously.
 * That function is responsible क्रम calling @qdata->fn().
 */
अटल bool alua_rtpg_queue(काष्ठा alua_port_group *pg,
			    काष्ठा scsi_device *sdev,
			    काष्ठा alua_queue_data *qdata, bool क्रमce)
अणु
	पूर्णांक start_queue = 0;
	अचिन्हित दीर्घ flags;
	अगर (WARN_ON_ONCE(!pg) || scsi_device_get(sdev))
		वापस false;

	spin_lock_irqsave(&pg->lock, flags);
	अगर (qdata) अणु
		list_add_tail(&qdata->entry, &pg->rtpg_list);
		pg->flags |= ALUA_PG_RUN_STPG;
		क्रमce = true;
	पूर्ण
	अगर (pg->rtpg_sdev == शून्य) अणु
		pg->पूर्णांकerval = 0;
		pg->flags |= ALUA_PG_RUN_RTPG;
		kref_get(&pg->kref);
		pg->rtpg_sdev = sdev;
		start_queue = 1;
	पूर्ण अन्यथा अगर (!(pg->flags & ALUA_PG_RUN_RTPG) && क्रमce) अणु
		pg->flags |= ALUA_PG_RUN_RTPG;
		/* Do not queue अगर the worker is alपढ़ोy running */
		अगर (!(pg->flags & ALUA_PG_RUNNING)) अणु
			kref_get(&pg->kref);
			start_queue = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pg->lock, flags);

	अगर (start_queue) अणु
		अगर (queue_delayed_work(kaluad_wq, &pg->rtpg_work,
				msecs_to_jअगरfies(ALUA_RTPG_DELAY_MSECS)))
			sdev = शून्य;
		अन्यथा
			kref_put(&pg->kref, release_port_group);
	पूर्ण
	अगर (sdev)
		scsi_device_put(sdev);

	वापस true;
पूर्ण

/*
 * alua_initialize - Initialize ALUA state
 * @sdev: the device to be initialized
 *
 * For the prep_fn to work correctly we have
 * to initialize the ALUA state क्रम the device.
 */
अटल पूर्णांक alua_initialize(काष्ठा scsi_device *sdev, काष्ठा alua_dh_data *h)
अणु
	पूर्णांक err = SCSI_DH_DEV_UNSUPP, tpgs;

	mutex_lock(&h->init_mutex);
	tpgs = alua_check_tpgs(sdev);
	अगर (tpgs != TPGS_MODE_NONE)
		err = alua_check_vpd(sdev, h, tpgs);
	h->init_error = err;
	mutex_unlock(&h->init_mutex);
	वापस err;
पूर्ण
/*
 * alua_set_params - set/unset the optimize flag
 * @sdev: device on the path to be activated
 * params - parameters in the following क्रमmat
 *      "no_of_params\0param1\0param2\0param3\0...\0"
 * For example, to set the flag pass the following parameters
 * from multipath.conf
 *     hardware_handler        "2 alua 1"
 */
अटल पूर्णांक alua_set_params(काष्ठा scsi_device *sdev, स्थिर अक्षर *params)
अणु
	काष्ठा alua_dh_data *h = sdev->handler_data;
	काष्ठा alua_port_group *pg = शून्य;
	अचिन्हित पूर्णांक optimize = 0, argc;
	स्थिर अक्षर *p = params;
	पूर्णांक result = SCSI_DH_OK;
	अचिन्हित दीर्घ flags;

	अगर ((माला_पूछो(params, "%u", &argc) != 1) || (argc != 1))
		वापस -EINVAL;

	जबतक (*p++)
		;
	अगर ((माला_पूछो(p, "%u", &optimize) != 1) || (optimize > 1))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	pg = rcu_dereference(h->pg);
	अगर (!pg) अणु
		rcu_पढ़ो_unlock();
		वापस -ENXIO;
	पूर्ण
	spin_lock_irqsave(&pg->lock, flags);
	अगर (optimize)
		pg->flags |= ALUA_OPTIMIZE_STPG;
	अन्यथा
		pg->flags &= ~ALUA_OPTIMIZE_STPG;
	spin_unlock_irqrestore(&pg->lock, flags);
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

/*
 * alua_activate - activate a path
 * @sdev: device on the path to be activated
 *
 * We're currently चयनing the port group to be activated only and
 * let the array figure out the rest.
 * There may be other arrays which require us to चयन all port groups
 * based on a certain policy. But until we actually encounter them it
 * should be okay.
 */
अटल पूर्णांक alua_activate(काष्ठा scsi_device *sdev,
			activate_complete fn, व्योम *data)
अणु
	काष्ठा alua_dh_data *h = sdev->handler_data;
	पूर्णांक err = SCSI_DH_OK;
	काष्ठा alua_queue_data *qdata;
	काष्ठा alua_port_group *pg;

	qdata = kzalloc(माप(*qdata), GFP_KERNEL);
	अगर (!qdata) अणु
		err = SCSI_DH_RES_TEMP_UNAVAIL;
		जाओ out;
	पूर्ण
	qdata->callback_fn = fn;
	qdata->callback_data = data;

	mutex_lock(&h->init_mutex);
	rcu_पढ़ो_lock();
	pg = rcu_dereference(h->pg);
	अगर (!pg || !kref_get_unless_zero(&pg->kref)) अणु
		rcu_पढ़ो_unlock();
		kमुक्त(qdata);
		err = h->init_error;
		mutex_unlock(&h->init_mutex);
		जाओ out;
	पूर्ण
	rcu_पढ़ो_unlock();
	mutex_unlock(&h->init_mutex);

	अगर (alua_rtpg_queue(pg, sdev, qdata, true))
		fn = शून्य;
	अन्यथा
		err = SCSI_DH_DEV_OFFLINED;
	kref_put(&pg->kref, release_port_group);
out:
	अगर (fn)
		fn(data, err);
	वापस 0;
पूर्ण

/*
 * alua_check - check path status
 * @sdev: device on the path to be checked
 *
 * Check the device status
 */
अटल व्योम alua_check(काष्ठा scsi_device *sdev, bool क्रमce)
अणु
	काष्ठा alua_dh_data *h = sdev->handler_data;
	काष्ठा alua_port_group *pg;

	rcu_पढ़ो_lock();
	pg = rcu_dereference(h->pg);
	अगर (!pg || !kref_get_unless_zero(&pg->kref)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();

	alua_rtpg_queue(pg, sdev, शून्य, क्रमce);
	kref_put(&pg->kref, release_port_group);
पूर्ण

/*
 * alua_prep_fn - request callback
 *
 * Fail I/O to all paths not in state
 * active/optimized or active/non-optimized.
 */
अटल blk_status_t alua_prep_fn(काष्ठा scsi_device *sdev, काष्ठा request *req)
अणु
	काष्ठा alua_dh_data *h = sdev->handler_data;
	काष्ठा alua_port_group *pg;
	अचिन्हित अक्षर state = SCSI_ACCESS_STATE_OPTIMAL;

	rcu_पढ़ो_lock();
	pg = rcu_dereference(h->pg);
	अगर (pg)
		state = pg->state;
	rcu_पढ़ो_unlock();

	चयन (state) अणु
	हाल SCSI_ACCESS_STATE_OPTIMAL:
	हाल SCSI_ACCESS_STATE_ACTIVE:
	हाल SCSI_ACCESS_STATE_LBA:
		वापस BLK_STS_OK;
	हाल SCSI_ACCESS_STATE_TRANSITIONING:
		वापस BLK_STS_AGAIN;
	शेष:
		req->rq_flags |= RQF_QUIET;
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

अटल व्योम alua_rescan(काष्ठा scsi_device *sdev)
अणु
	काष्ठा alua_dh_data *h = sdev->handler_data;

	alua_initialize(sdev, h);
पूर्ण

/*
 * alua_bus_attach - Attach device handler
 * @sdev: device to be attached to
 */
अटल पूर्णांक alua_bus_attach(काष्ठा scsi_device *sdev)
अणु
	काष्ठा alua_dh_data *h;
	पूर्णांक err;

	h = kzalloc(माप(*h) , GFP_KERNEL);
	अगर (!h)
		वापस SCSI_DH_NOMEM;
	spin_lock_init(&h->pg_lock);
	rcu_assign_poपूर्णांकer(h->pg, शून्य);
	h->init_error = SCSI_DH_OK;
	h->sdev = sdev;
	INIT_LIST_HEAD(&h->node);

	mutex_init(&h->init_mutex);
	err = alua_initialize(sdev, h);
	अगर (err != SCSI_DH_OK && err != SCSI_DH_DEV_OFFLINED)
		जाओ failed;

	sdev->handler_data = h;
	वापस SCSI_DH_OK;
failed:
	kमुक्त(h);
	वापस err;
पूर्ण

/*
 * alua_bus_detach - Detach device handler
 * @sdev: device to be detached from
 */
अटल व्योम alua_bus_detach(काष्ठा scsi_device *sdev)
अणु
	काष्ठा alua_dh_data *h = sdev->handler_data;
	काष्ठा alua_port_group *pg;

	spin_lock(&h->pg_lock);
	pg = rcu_dereference_रक्षित(h->pg, lockdep_is_held(&h->pg_lock));
	rcu_assign_poपूर्णांकer(h->pg, शून्य);
	spin_unlock(&h->pg_lock);
	अगर (pg) अणु
		spin_lock_irq(&pg->lock);
		list_del_rcu(&h->node);
		spin_unlock_irq(&pg->lock);
		kref_put(&pg->kref, release_port_group);
	पूर्ण
	sdev->handler_data = शून्य;
	synchronize_rcu();
	kमुक्त(h);
पूर्ण

अटल काष्ठा scsi_device_handler alua_dh = अणु
	.name = ALUA_DH_NAME,
	.module = THIS_MODULE,
	.attach = alua_bus_attach,
	.detach = alua_bus_detach,
	.prep_fn = alua_prep_fn,
	.check_sense = alua_check_sense,
	.activate = alua_activate,
	.rescan = alua_rescan,
	.set_params = alua_set_params,
पूर्ण;

अटल पूर्णांक __init alua_init(व्योम)
अणु
	पूर्णांक r;

	kaluad_wq = alloc_workqueue("kaluad", WQ_MEM_RECLAIM, 0);
	अगर (!kaluad_wq)
		वापस -ENOMEM;

	r = scsi_रेजिस्टर_device_handler(&alua_dh);
	अगर (r != 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to register scsi device handler",
			ALUA_DH_NAME);
		destroy_workqueue(kaluad_wq);
	पूर्ण
	वापस r;
पूर्ण

अटल व्योम __निकास alua_निकास(व्योम)
अणु
	scsi_unरेजिस्टर_device_handler(&alua_dh);
	destroy_workqueue(kaluad_wq);
पूर्ण

module_init(alua_init);
module_निकास(alua_निकास);

MODULE_DESCRIPTION("DM Multipath ALUA support");
MODULE_AUTHOR("Hannes Reinecke <hare@suse.de>");
MODULE_LICENSE("GPL");
MODULE_VERSION(ALUA_DH_VER);
