<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_pr.c
 *
 * This file contains SPC-3 compliant persistent reservations and
 * legacy SPC-2 reservations with compatible reservation handling (CRH=1)
 *
 * (c) Copyright 2009-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/file.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/fs.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_ua.h"

/*
 * Used क्रम Specअगरy Initiator Ports Capable Bit (SPEC_I_PT)
 */
काष्ठा pr_transport_id_holder अणु
	काष्ठा t10_pr_registration *dest_pr_reg;
	काष्ठा se_portal_group *dest_tpg;
	काष्ठा se_node_acl *dest_node_acl;
	काष्ठा se_dev_entry *dest_se_deve;
	काष्ठा list_head dest_list;
पूर्ण;

व्योम core_pr_dump_initiator_port(
	काष्ठा t10_pr_registration *pr_reg,
	अक्षर *buf,
	u32 size)
अणु
	अगर (!pr_reg->isid_present_at_reg) अणु
		buf[0] = '\0';
		वापस;
	पूर्ण

	snम_लिखो(buf, size, ",i,0x%s", pr_reg->pr_reg_isid);
पूर्ण

क्रमागत रेजिस्टर_type अणु
	REGISTER,
	REGISTER_AND_IGNORE_EXISTING_KEY,
	REGISTER_AND_MOVE,
पूर्ण;

क्रमागत preempt_type अणु
	PREEMPT,
	PREEMPT_AND_ABORT,
पूर्ण;

अटल व्योम __core_scsi3_complete_pro_release(काष्ठा se_device *, काष्ठा se_node_acl *,
					      काष्ठा t10_pr_registration *, पूर्णांक, पूर्णांक);

अटल पूर्णांक is_reservation_holder(
	काष्ठा t10_pr_registration *pr_res_holder,
	काष्ठा t10_pr_registration *pr_reg)
अणु
	पूर्णांक pr_res_type;

	अगर (pr_res_holder) अणु
		pr_res_type = pr_res_holder->pr_res_type;

		वापस pr_res_holder == pr_reg ||
		       pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG ||
		       pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG;
	पूर्ण
	वापस 0;
पूर्ण

अटल sense_reason_t
target_scsi2_reservation_check(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;

	चयन (cmd->t_task_cdb[0]) अणु
	हाल INQUIRY:
	हाल RELEASE:
	हाल RELEASE_10:
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!dev->reservation_holder || !sess)
		वापस 0;

	अगर (dev->reservation_holder->se_node_acl != sess->se_node_acl)
		वापस TCM_RESERVATION_CONFLICT;

	अगर (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS_WITH_ISID) अणु
		अगर (dev->dev_res_bin_isid != sess->sess_bin_isid)
			वापस TCM_RESERVATION_CONFLICT;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा t10_pr_registration *core_scsi3_locate_pr_reg(काष्ठा se_device *,
					काष्ठा se_node_acl *, काष्ठा se_session *);
अटल व्योम core_scsi3_put_pr_reg(काष्ठा t10_pr_registration *);

अटल पूर्णांक target_check_scsi2_reservation_conflict(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_pr_registration *pr_reg;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	पूर्णांक conflict = 0;

	pr_reg = core_scsi3_locate_pr_reg(cmd->se_dev, se_sess->se_node_acl,
			se_sess);
	अगर (pr_reg) अणु
		/*
		 * From spc4r17 5.7.3 Exceptions to SPC-2 RESERVE and RELEASE
		 * behavior
		 *
		 * A RESERVE(6) or RESERVE(10) command shall complete with GOOD
		 * status, but no reservation shall be established and the
		 * persistent reservation shall not be changed, अगर the command
		 * is received from a) and b) below.
		 *
		 * A RELEASE(6) or RELEASE(10) command shall complete with GOOD
		 * status, but the persistent reservation shall not be released,
		 * अगर the command is received from a) and b)
		 *
		 * a) An I_T nexus that is a persistent reservation holder; or
		 * b) An I_T nexus that is रेजिस्टरed अगर a registrants only or
		 *    all registrants type persistent reservation is present.
		 *
		 * In all other हालs, a RESERVE(6) command, RESERVE(10) command,
		 * RELEASE(6) command, or RELEASE(10) command shall be processed
		 * as defined in SPC-2.
		 */
		अगर (pr_reg->pr_res_holder) अणु
			core_scsi3_put_pr_reg(pr_reg);
			वापस 1;
		पूर्ण
		अगर ((pr_reg->pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_REGONLY) ||
		    (pr_reg->pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_REGONLY) ||
		    (pr_reg->pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG) ||
		    (pr_reg->pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG)) अणु
			core_scsi3_put_pr_reg(pr_reg);
			वापस 1;
		पूर्ण
		core_scsi3_put_pr_reg(pr_reg);
		conflict = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Following spc2r20 5.5.1 Reservations overview:
		 *
		 * If a logical unit has executed a PERSISTENT RESERVE OUT
		 * command with the REGISTER or the REGISTER AND IGNORE
		 * EXISTING KEY service action and is still रेजिस्टरed by any
		 * initiator, all RESERVE commands and all RELEASE commands
		 * regardless of initiator shall conflict and shall terminate
		 * with a RESERVATION CONFLICT status.
		 */
		spin_lock(&pr_पंचांगpl->registration_lock);
		conflict = (list_empty(&pr_पंचांगpl->registration_list)) ? 0 : 1;
		spin_unlock(&pr_पंचांगpl->registration_lock);
	पूर्ण

	अगर (conflict) अणु
		pr_err("Received legacy SPC-2 RESERVE/RELEASE"
			" while active SPC-3 registrations exist,"
			" returning RESERVATION_CONFLICT\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

व्योम target_release_reservation(काष्ठा se_device *dev)
अणु
	dev->reservation_holder = शून्य;
	dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS;
	अगर (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS_WITH_ISID) अणु
		dev->dev_res_bin_isid = 0;
		dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS_WITH_ISID;
	पूर्ण
पूर्ण

sense_reason_t
target_scsi2_reservation_release(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;
	काष्ठा se_portal_group *tpg;
	पूर्णांक rc;

	अगर (!sess || !sess->se_tpg)
		जाओ out;
	rc = target_check_scsi2_reservation_conflict(cmd);
	अगर (rc == 1)
		जाओ out;
	अगर (rc < 0)
		वापस TCM_RESERVATION_CONFLICT;

	spin_lock(&dev->dev_reservation_lock);
	अगर (!dev->reservation_holder || !sess)
		जाओ out_unlock;

	अगर (dev->reservation_holder->se_node_acl != sess->se_node_acl)
		जाओ out_unlock;

	अगर (dev->dev_res_bin_isid != sess->sess_bin_isid)
		जाओ out_unlock;

	target_release_reservation(dev);
	tpg = sess->se_tpg;
	pr_debug("SCSI-2 Released reservation for %s LUN: %llu ->"
		" MAPPED LUN: %llu for %s\n",
		tpg->se_tpg_tfo->fabric_name,
		cmd->se_lun->unpacked_lun, cmd->orig_fe_lun,
		sess->se_node_acl->initiatorname);

out_unlock:
	spin_unlock(&dev->dev_reservation_lock);
out:
	target_complete_cmd(cmd, GOOD);
	वापस 0;
पूर्ण

sense_reason_t
target_scsi2_reservation_reserve(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;
	काष्ठा se_portal_group *tpg;
	sense_reason_t ret = 0;
	पूर्णांक rc;

	अगर ((cmd->t_task_cdb[1] & 0x01) &&
	    (cmd->t_task_cdb[1] & 0x02)) अणु
		pr_err("LongIO and Obsolete Bits set, returning ILLEGAL_REQUEST\n");
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण
	/*
	 * This is currently the हाल क्रम target_core_mod passthrough काष्ठा se_cmd
	 * ops
	 */
	अगर (!sess || !sess->se_tpg)
		जाओ out;
	rc = target_check_scsi2_reservation_conflict(cmd);
	अगर (rc == 1)
		जाओ out;

	अगर (rc < 0)
		वापस TCM_RESERVATION_CONFLICT;

	tpg = sess->se_tpg;
	spin_lock(&dev->dev_reservation_lock);
	अगर (dev->reservation_holder &&
	    dev->reservation_holder->se_node_acl != sess->se_node_acl) अणु
		pr_err("SCSI-2 RESERVATION CONFLIFT for %s fabric\n",
			tpg->se_tpg_tfo->fabric_name);
		pr_err("Original reserver LUN: %llu %s\n",
			cmd->se_lun->unpacked_lun,
			dev->reservation_holder->se_node_acl->initiatorname);
		pr_err("Current attempt - LUN: %llu -> MAPPED LUN: %llu"
			" from %s \n", cmd->se_lun->unpacked_lun,
			cmd->orig_fe_lun,
			sess->se_node_acl->initiatorname);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out_unlock;
	पूर्ण

	dev->reservation_holder = sess;
	dev->dev_reservation_flags |= DRF_SPC2_RESERVATIONS;
	अगर (sess->sess_bin_isid != 0) अणु
		dev->dev_res_bin_isid = sess->sess_bin_isid;
		dev->dev_reservation_flags |= DRF_SPC2_RESERVATIONS_WITH_ISID;
	पूर्ण
	pr_debug("SCSI-2 Reserved %s LUN: %llu -> MAPPED LUN: %llu"
		" for %s\n", tpg->se_tpg_tfo->fabric_name,
		cmd->se_lun->unpacked_lun, cmd->orig_fe_lun,
		sess->se_node_acl->initiatorname);

out_unlock:
	spin_unlock(&dev->dev_reservation_lock);
out:
	अगर (!ret)
		target_complete_cmd(cmd, GOOD);
	वापस ret;
पूर्ण


/*
 * Begin SPC-3/SPC-4 Persistent Reservations emulation support
 *
 * This function is called by those initiator ports who are *NOT*
 * the active PR reservation holder when a reservation is present.
 */
अटल पूर्णांक core_scsi3_pr_seq_non_holder(काष्ठा se_cmd *cmd, u32 pr_reg_type,
					bool isid_mismatch)
अणु
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_node_acl *nacl = se_sess->se_node_acl;
	पूर्णांक other_cdb = 0;
	पूर्णांक रेजिस्टरed_nexus = 0, ret = 1; /* Conflict by शेष */
	पूर्णांक all_reg = 0, reg_only = 0; /* ALL_REG, REG_ONLY */
	पूर्णांक we = 0; /* Write Exclusive */
	पूर्णांक legacy = 0; /* Act like a legacy device and वापस
			 * RESERVATION CONFLICT on some CDBs */

	अगर (isid_mismatch) अणु
		रेजिस्टरed_nexus = 0;
	पूर्ण अन्यथा अणु
		काष्ठा se_dev_entry *se_deve;

		rcu_पढ़ो_lock();
		se_deve = target_nacl_find_deve(nacl, cmd->orig_fe_lun);
		अगर (se_deve)
			रेजिस्टरed_nexus = test_bit(DEF_PR_REG_ACTIVE,
						    &se_deve->deve_flags);
		rcu_पढ़ो_unlock();
	पूर्ण

	चयन (pr_reg_type) अणु
	हाल PR_TYPE_WRITE_EXCLUSIVE:
		we = 1;
		fallthrough;
	हाल PR_TYPE_EXCLUSIVE_ACCESS:
		/*
		 * Some commands are only allowed क्रम the persistent reservation
		 * holder.
		 */
		अवरोध;
	हाल PR_TYPE_WRITE_EXCLUSIVE_REGONLY:
		we = 1;
		fallthrough;
	हाल PR_TYPE_EXCLUSIVE_ACCESS_REGONLY:
		/*
		 * Some commands are only allowed क्रम रेजिस्टरed I_T Nexuses.
		 */
		reg_only = 1;
		अवरोध;
	हाल PR_TYPE_WRITE_EXCLUSIVE_ALLREG:
		we = 1;
		fallthrough;
	हाल PR_TYPE_EXCLUSIVE_ACCESS_ALLREG:
		/*
		 * Each रेजिस्टरed I_T Nexus is a reservation holder.
		 */
		all_reg = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/*
	 * Referenced from spc4r17 table 45 क्रम *NON* PR holder access
	 */
	चयन (cdb[0]) अणु
	हाल SECURITY_PROTOCOL_IN:
		अगर (रेजिस्टरed_nexus)
			वापस 0;
		ret = (we) ? 0 : 1;
		अवरोध;
	हाल MODE_SENSE:
	हाल MODE_SENSE_10:
	हाल READ_ATTRIBUTE:
	हाल READ_BUFFER:
	हाल RECEIVE_DIAGNOSTIC:
		अगर (legacy) अणु
			ret = 1;
			अवरोध;
		पूर्ण
		अगर (रेजिस्टरed_nexus) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		ret = (we) ? 0 : 1; /* Allowed Write Exclusive */
		अवरोध;
	हाल PERSISTENT_RESERVE_OUT:
		/*
		 * This follows PERSISTENT_RESERVE_OUT service actions that
		 * are allowed in the presence of various reservations.
		 * See spc4r17, table 46
		 */
		चयन (cdb[1] & 0x1f) अणु
		हाल PRO_CLEAR:
		हाल PRO_PREEMPT:
		हाल PRO_PREEMPT_AND_ABORT:
			ret = (रेजिस्टरed_nexus) ? 0 : 1;
			अवरोध;
		हाल PRO_REGISTER:
		हाल PRO_REGISTER_AND_IGNORE_EXISTING_KEY:
			ret = 0;
			अवरोध;
		हाल PRO_REGISTER_AND_MOVE:
		हाल PRO_RESERVE:
			ret = 1;
			अवरोध;
		हाल PRO_RELEASE:
			ret = (रेजिस्टरed_nexus) ? 0 : 1;
			अवरोध;
		शेष:
			pr_err("Unknown PERSISTENT_RESERVE_OUT service"
				" action: 0x%02x\n", cdb[1] & 0x1f);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RELEASE:
	हाल RELEASE_10:
		/* Handled by CRH=1 in target_scsi2_reservation_release() */
		ret = 0;
		अवरोध;
	हाल RESERVE:
	हाल RESERVE_10:
		/* Handled by CRH=1 in target_scsi2_reservation_reserve() */
		ret = 0;
		अवरोध;
	हाल TEST_UNIT_READY:
		ret = (legacy) ? 1 : 0; /* Conflict क्रम legacy */
		अवरोध;
	हाल MAINTEन_अंकCE_IN:
		चयन (cdb[1] & 0x1f) अणु
		हाल MI_MANAGEMENT_PROTOCOL_IN:
			अगर (रेजिस्टरed_nexus) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			ret = (we) ? 0 : 1; /* Allowed Write Exclusive */
			अवरोध;
		हाल MI_REPORT_SUPPORTED_OPERATION_CODES:
		हाल MI_REPORT_SUPPORTED_TASK_MANAGEMENT_FUNCTIONS:
			अगर (legacy) अणु
				ret = 1;
				अवरोध;
			पूर्ण
			अगर (रेजिस्टरed_nexus) अणु
				ret = 0;
				अवरोध;
			पूर्ण
			ret = (we) ? 0 : 1; /* Allowed Write Exclusive */
			अवरोध;
		हाल MI_REPORT_ALIASES:
		हाल MI_REPORT_IDENTIFYING_INFORMATION:
		हाल MI_REPORT_PRIORITY:
		हाल MI_REPORT_TARGET_PGS:
		हाल MI_REPORT_TIMESTAMP:
			ret = 0; /* Allowed */
			अवरोध;
		शेष:
			pr_err("Unknown MI Service Action: 0x%02x\n",
				(cdb[1] & 0x1f));
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल ACCESS_CONTROL_IN:
	हाल ACCESS_CONTROL_OUT:
	हाल INQUIRY:
	हाल LOG_SENSE:
	हाल SERVICE_ACTION_IN_12:
	हाल REPORT_LUNS:
	हाल REQUEST_SENSE:
	हाल PERSISTENT_RESERVE_IN:
		ret = 0; /*/ Allowed CDBs */
		अवरोध;
	शेष:
		other_cdb = 1;
		अवरोध;
	पूर्ण
	/*
	 * Case where the CDB is explicitly allowed in the above चयन
	 * statement.
	 */
	अगर (!ret && !other_cdb) अणु
		pr_debug("Allowing explicit CDB: 0x%02x for %s"
			" reservation holder\n", cdb[0],
			core_scsi3_pr_dump_type(pr_reg_type));

		वापस ret;
	पूर्ण
	/*
	 * Check अगर ग_लिखो exclusive initiator ports *NOT* holding the
	 * WRITE_EXCLUSIVE_* reservation.
	 */
	अगर (we && !रेजिस्टरed_nexus) अणु
		अगर (cmd->data_direction == DMA_TO_DEVICE) अणु
			/*
			 * Conflict क्रम ग_लिखो exclusive
			 */
			pr_debug("%s Conflict for unregistered nexus"
				" %s CDB: 0x%02x to %s reservation\n",
				transport_dump_cmd_direction(cmd),
				se_sess->se_node_acl->initiatorname, cdb[0],
				core_scsi3_pr_dump_type(pr_reg_type));
			वापस 1;
		पूर्ण अन्यथा अणु
			/*
			 * Allow non WRITE CDBs क्रम all Write Exclusive
			 * PR TYPEs to pass क्रम रेजिस्टरed and
			 * non-रेजिस्टरed_nexuxes NOT holding the reservation.
			 *
			 * We only make noise क्रम the unरेजिस्टरd nexuses,
			 * as we expect रेजिस्टरed non-reservation holding
			 * nexuses to issue CDBs.
			 */

			अगर (!रेजिस्टरed_nexus) अणु
				pr_debug("Allowing implicit CDB: 0x%02x"
					" for %s reservation on unregistered"
					" nexus\n", cdb[0],
					core_scsi3_pr_dump_type(pr_reg_type));
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर ((reg_only) || (all_reg)) अणु
		अगर (रेजिस्टरed_nexus) अणु
			/*
			 * For PR_*_REG_ONLY and PR_*_ALL_REG reservations,
			 * allow commands from रेजिस्टरed nexuses.
			 */

			pr_debug("Allowing implicit CDB: 0x%02x for %s"
				" reservation\n", cdb[0],
				core_scsi3_pr_dump_type(pr_reg_type));

			वापस 0;
		पूर्ण
       पूर्ण अन्यथा अगर (we && रेजिस्टरed_nexus) अणु
               /*
                * Reads are allowed क्रम Write Exclusive locks
                * from all registrants.
                */
               अगर (cmd->data_direction == DMA_FROM_DEVICE) अणु
                       pr_debug("Allowing READ CDB: 0x%02x for %s"
                               " reservation\n", cdb[0],
                               core_scsi3_pr_dump_type(pr_reg_type));

                       वापस 0;
               पूर्ण
	पूर्ण
	pr_debug("%s Conflict for %sregistered nexus %s CDB: 0x%2x"
		" for %s reservation\n", transport_dump_cmd_direction(cmd),
		(रेजिस्टरed_nexus) ? "" : "un",
		se_sess->se_node_acl->initiatorname, cdb[0],
		core_scsi3_pr_dump_type(pr_reg_type));

	वापस 1; /* Conflict by शेष */
पूर्ण

अटल sense_reason_t
target_scsi3_pr_reservation_check(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *sess = cmd->se_sess;
	u32 pr_reg_type;
	bool isid_mismatch = false;

	अगर (!dev->dev_pr_res_holder)
		वापस 0;

	pr_reg_type = dev->dev_pr_res_holder->pr_res_type;
	cmd->pr_res_key = dev->dev_pr_res_holder->pr_res_key;
	अगर (dev->dev_pr_res_holder->pr_reg_nacl != sess->se_node_acl)
		जाओ check_nonholder;

	अगर (dev->dev_pr_res_holder->isid_present_at_reg) अणु
		अगर (dev->dev_pr_res_holder->pr_reg_bin_isid !=
		    sess->sess_bin_isid) अणु
			isid_mismatch = true;
			जाओ check_nonholder;
		पूर्ण
	पूर्ण

	वापस 0;

check_nonholder:
	अगर (core_scsi3_pr_seq_non_holder(cmd, pr_reg_type, isid_mismatch))
		वापस TCM_RESERVATION_CONFLICT;
	वापस 0;
पूर्ण

अटल u32 core_scsi3_pr_generation(काष्ठा se_device *dev)
अणु
	u32 prg;

	/*
	 * PRGeneration field shall contain the value of a 32-bit wrapping
	 * counter मुख्यted by the device server.
	 *
	 * Note that this is करोne regardless of Active Persist across
	 * Target PowerLoss (APTPL)
	 *
	 * See spc4r17 section 6.3.12 READ_KEYS service action
	 */
	spin_lock(&dev->dev_reservation_lock);
	prg = dev->t10_pr.pr_generation++;
	spin_unlock(&dev->dev_reservation_lock);

	वापस prg;
पूर्ण

अटल काष्ठा t10_pr_registration *__core_scsi3_करो_alloc_registration(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl,
	काष्ठा se_lun *lun,
	काष्ठा se_dev_entry *dest_deve,
	u64 mapped_lun,
	अचिन्हित अक्षर *isid,
	u64 sa_res_key,
	पूर्णांक all_tg_pt,
	पूर्णांक aptpl)
अणु
	काष्ठा t10_pr_registration *pr_reg;

	pr_reg = kmem_cache_zalloc(t10_pr_reg_cache, GFP_ATOMIC);
	अगर (!pr_reg) अणु
		pr_err("Unable to allocate struct t10_pr_registration\n");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&pr_reg->pr_reg_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_पात_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_aptpl_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_atp_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_atp_mem_list);
	atomic_set(&pr_reg->pr_res_holders, 0);
	pr_reg->pr_reg_nacl = nacl;
	/*
	 * For destination registrations क्रम ALL_TG_PT=1 and SPEC_I_PT=1,
	 * the se_dev_entry->pr_ref will have been alपढ़ोy obtained by
	 * core_get_se_deve_from_rtpi() or __core_scsi3_alloc_registration().
	 *
	 * Otherwise, locate se_dev_entry now and obtain a reference until
	 * registration completes in __core_scsi3_add_registration().
	 */
	अगर (dest_deve) अणु
		pr_reg->pr_reg_deve = dest_deve;
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_lock();
		pr_reg->pr_reg_deve = target_nacl_find_deve(nacl, mapped_lun);
		अगर (!pr_reg->pr_reg_deve) अणु
			rcu_पढ़ो_unlock();
			pr_err("Unable to locate PR deve %s mapped_lun: %llu\n",
				nacl->initiatorname, mapped_lun);
			kmem_cache_मुक्त(t10_pr_reg_cache, pr_reg);
			वापस शून्य;
		पूर्ण
		kref_get(&pr_reg->pr_reg_deve->pr_kref);
		rcu_पढ़ो_unlock();
	पूर्ण
	pr_reg->pr_res_mapped_lun = mapped_lun;
	pr_reg->pr_aptpl_target_lun = lun->unpacked_lun;
	pr_reg->tg_pt_sep_rtpi = lun->lun_rtpi;
	pr_reg->pr_res_key = sa_res_key;
	pr_reg->pr_reg_all_tg_pt = all_tg_pt;
	pr_reg->pr_reg_aptpl = aptpl;
	/*
	 * If an ISID value क्रम this SCSI Initiator Port exists,
	 * save it to the registration now.
	 */
	अगर (isid != शून्य) अणु
		pr_reg->pr_reg_bin_isid = get_unaligned_be64(isid);
		snम_लिखो(pr_reg->pr_reg_isid, PR_REG_ISID_LEN, "%s", isid);
		pr_reg->isid_present_at_reg = 1;
	पूर्ण

	वापस pr_reg;
पूर्ण

अटल पूर्णांक core_scsi3_lunacl_depend_item(काष्ठा se_dev_entry *);
अटल व्योम core_scsi3_lunacl_undepend_item(काष्ठा se_dev_entry *);

/*
 * Function used क्रम handling PR registrations क्रम ALL_TG_PT=1 and ALL_TG_PT=0
 * modes.
 */
अटल काष्ठा t10_pr_registration *__core_scsi3_alloc_registration(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl,
	काष्ठा se_lun *lun,
	काष्ठा se_dev_entry *deve,
	u64 mapped_lun,
	अचिन्हित अक्षर *isid,
	u64 sa_res_key,
	पूर्णांक all_tg_pt,
	पूर्णांक aptpl)
अणु
	काष्ठा se_dev_entry *deve_पंचांगp;
	काष्ठा se_node_acl *nacl_पंचांगp;
	काष्ठा se_lun_acl *lacl_पंचांगp;
	काष्ठा se_lun *lun_पंचांगp, *next, *dest_lun;
	स्थिर काष्ठा target_core_fabric_ops *tfo = nacl->se_tpg->se_tpg_tfo;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_atp, *pr_reg_पंचांगp, *pr_reg_पंचांगp_safe;
	पूर्णांक ret;
	/*
	 * Create a registration क्रम the I_T Nexus upon which the
	 * PROUT REGISTER was received.
	 */
	pr_reg = __core_scsi3_करो_alloc_registration(dev, nacl, lun, deve, mapped_lun,
						    isid, sa_res_key, all_tg_pt,
						    aptpl);
	अगर (!pr_reg)
		वापस शून्य;
	/*
	 * Return poपूर्णांकer to pr_reg क्रम ALL_TG_PT=0
	 */
	अगर (!all_tg_pt)
		वापस pr_reg;
	/*
	 * Create list of matching SCSI Initiator Port registrations
	 * क्रम ALL_TG_PT=1
	 */
	spin_lock(&dev->se_port_lock);
	list_क्रम_each_entry_safe(lun_पंचांगp, next, &dev->dev_sep_list, lun_dev_link) अणु
		अगर (!percpu_ref_tryget_live(&lun_पंचांगp->lun_ref))
			जारी;
		spin_unlock(&dev->se_port_lock);

		spin_lock(&lun_पंचांगp->lun_deve_lock);
		list_क्रम_each_entry(deve_पंचांगp, &lun_पंचांगp->lun_deve_list, lun_link) अणु
			/*
			 * This poपूर्णांकer will be शून्य क्रम demo mode MappedLUNs
			 * that have not been make explicit via a ConfigFS
			 * MappedLUN group क्रम the SCSI Initiator Node ACL.
			 */
			अगर (!deve_पंचांगp->se_lun_acl)
				जारी;

			lacl_पंचांगp = rcu_dereference_check(deve_पंचांगp->se_lun_acl,
						lockdep_is_held(&lun_पंचांगp->lun_deve_lock));
			nacl_पंचांगp = lacl_पंचांगp->se_lun_nacl;
			/*
			 * Skip the matching काष्ठा se_node_acl that is allocated
			 * above..
			 */
			अगर (nacl == nacl_पंचांगp)
				जारी;
			/*
			 * Only perक्रमm PR registrations क्रम target ports on
			 * the same fabric module as the REGISTER w/ ALL_TG_PT=1
			 * arrived.
			 */
			अगर (tfo != nacl_पंचांगp->se_tpg->se_tpg_tfo)
				जारी;
			/*
			 * Look क्रम a matching Initiator Node ACL in ASCII क्रमmat
			 */
			अगर (म_भेद(nacl->initiatorname, nacl_पंचांगp->initiatorname))
				जारी;

			kref_get(&deve_पंचांगp->pr_kref);
			spin_unlock(&lun_पंचांगp->lun_deve_lock);
			/*
			 * Grab a configfs group dependency that is released
			 * क्रम the exception path at label out: below, or upon
			 * completion of adding ALL_TG_PT=1 registrations in
			 * __core_scsi3_add_registration()
			 */
			ret = core_scsi3_lunacl_depend_item(deve_पंचांगp);
			अगर (ret < 0) अणु
				pr_err("core_scsi3_lunacl_depend"
						"_item() failed\n");
				percpu_ref_put(&lun_पंचांगp->lun_ref);
				kref_put(&deve_पंचांगp->pr_kref, target_pr_kref_release);
				जाओ out;
			पूर्ण
			/*
			 * Located a matching SCSI Initiator Port on a dअगरferent
			 * port, allocate the pr_reg_atp and attach it to the
			 * pr_reg->pr_reg_atp_list that will be processed once
			 * the original *pr_reg is processed in
			 * __core_scsi3_add_registration()
			 */
			dest_lun = rcu_dereference_check(deve_पंचांगp->se_lun,
				kref_पढ़ो(&deve_पंचांगp->pr_kref) != 0);

			pr_reg_atp = __core_scsi3_करो_alloc_registration(dev,
						nacl_पंचांगp, dest_lun, deve_पंचांगp,
						deve_पंचांगp->mapped_lun, शून्य,
						sa_res_key, all_tg_pt, aptpl);
			अगर (!pr_reg_atp) अणु
				percpu_ref_put(&lun_पंचांगp->lun_ref);
				core_scsi3_lunacl_undepend_item(deve_पंचांगp);
				जाओ out;
			पूर्ण

			list_add_tail(&pr_reg_atp->pr_reg_atp_mem_list,
				      &pr_reg->pr_reg_atp_list);
			spin_lock(&lun_पंचांगp->lun_deve_lock);
		पूर्ण
		spin_unlock(&lun_पंचांगp->lun_deve_lock);

		spin_lock(&dev->se_port_lock);
		percpu_ref_put(&lun_पंचांगp->lun_ref);
	पूर्ण
	spin_unlock(&dev->se_port_lock);

	वापस pr_reg;
out:
	list_क्रम_each_entry_safe(pr_reg_पंचांगp, pr_reg_पंचांगp_safe,
			&pr_reg->pr_reg_atp_list, pr_reg_atp_mem_list) अणु
		list_del(&pr_reg_पंचांगp->pr_reg_atp_mem_list);
		core_scsi3_lunacl_undepend_item(pr_reg_पंचांगp->pr_reg_deve);
		kmem_cache_मुक्त(t10_pr_reg_cache, pr_reg_पंचांगp);
	पूर्ण
	kmem_cache_मुक्त(t10_pr_reg_cache, pr_reg);
	वापस शून्य;
पूर्ण

पूर्णांक core_scsi3_alloc_aptpl_registration(
	काष्ठा t10_reservation *pr_पंचांगpl,
	u64 sa_res_key,
	अचिन्हित अक्षर *i_port,
	अचिन्हित अक्षर *isid,
	u64 mapped_lun,
	अचिन्हित अक्षर *t_port,
	u16 tpgt,
	u64 target_lun,
	पूर्णांक res_holder,
	पूर्णांक all_tg_pt,
	u8 type)
अणु
	काष्ठा t10_pr_registration *pr_reg;

	अगर (!i_port || !t_port || !sa_res_key) अणु
		pr_err("Illegal parameters for APTPL registration\n");
		वापस -EINVAL;
	पूर्ण

	pr_reg = kmem_cache_zalloc(t10_pr_reg_cache, GFP_KERNEL);
	अगर (!pr_reg) अणु
		pr_err("Unable to allocate struct t10_pr_registration\n");
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&pr_reg->pr_reg_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_पात_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_aptpl_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_atp_list);
	INIT_LIST_HEAD(&pr_reg->pr_reg_atp_mem_list);
	atomic_set(&pr_reg->pr_res_holders, 0);
	pr_reg->pr_reg_nacl = शून्य;
	pr_reg->pr_reg_deve = शून्य;
	pr_reg->pr_res_mapped_lun = mapped_lun;
	pr_reg->pr_aptpl_target_lun = target_lun;
	pr_reg->pr_res_key = sa_res_key;
	pr_reg->pr_reg_all_tg_pt = all_tg_pt;
	pr_reg->pr_reg_aptpl = 1;
	pr_reg->pr_res_scope = 0; /* Always LUN_SCOPE */
	pr_reg->pr_res_type = type;
	/*
	 * If an ISID value had been saved in APTPL metadata क्रम this
	 * SCSI Initiator Port, restore it now.
	 */
	अगर (isid != शून्य) अणु
		pr_reg->pr_reg_bin_isid = get_unaligned_be64(isid);
		snम_लिखो(pr_reg->pr_reg_isid, PR_REG_ISID_LEN, "%s", isid);
		pr_reg->isid_present_at_reg = 1;
	पूर्ण
	/*
	 * Copy the i_port and t_port inक्रमmation from caller.
	 */
	snम_लिखो(pr_reg->pr_iport, PR_APTPL_MAX_IPORT_LEN, "%s", i_port);
	snम_लिखो(pr_reg->pr_tport, PR_APTPL_MAX_TPORT_LEN, "%s", t_port);
	pr_reg->pr_reg_tpgt = tpgt;
	/*
	 * Set pr_res_holder from caller, the pr_reg who is the reservation
	 * holder will get it's poपूर्णांकer set in core_scsi3_aptpl_reserve() once
	 * the Initiator Node LUN ACL from the fabric module is created क्रम
	 * this registration.
	 */
	pr_reg->pr_res_holder = res_holder;

	list_add_tail(&pr_reg->pr_reg_aptpl_list, &pr_पंचांगpl->aptpl_reg_list);
	pr_debug("SPC-3 PR APTPL Successfully added registration%s from"
			" metadata\n", (res_holder) ? "+reservation" : "");
	वापस 0;
पूर्ण

अटल व्योम core_scsi3_aptpl_reserve(
	काष्ठा se_device *dev,
	काष्ठा se_portal_group *tpg,
	काष्ठा se_node_acl *node_acl,
	काष्ठा t10_pr_registration *pr_reg)
अणु
	अक्षर i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;

	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);

	spin_lock(&dev->dev_reservation_lock);
	dev->dev_pr_res_holder = pr_reg;
	spin_unlock(&dev->dev_reservation_lock);

	pr_debug("SPC-3 PR [%s] Service Action: APTPL RESERVE created"
		" new reservation holder TYPE: %s ALL_TG_PT: %d\n",
		tpg->se_tpg_tfo->fabric_name,
		core_scsi3_pr_dump_type(pr_reg->pr_res_type),
		(pr_reg->pr_reg_all_tg_pt) ? 1 : 0);
	pr_debug("SPC-3 PR [%s] RESERVE Node: %s%s\n",
		tpg->se_tpg_tfo->fabric_name, node_acl->initiatorname,
		i_buf);
पूर्ण

अटल व्योम __core_scsi3_add_registration(काष्ठा se_device *, काष्ठा se_node_acl *,
				काष्ठा t10_pr_registration *, क्रमागत रेजिस्टर_type, पूर्णांक);

अटल पूर्णांक __core_scsi3_check_aptpl_registration(
	काष्ठा se_device *dev,
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun *lun,
	u64 target_lun,
	काष्ठा se_node_acl *nacl,
	u64 mapped_lun)
अणु
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	अचिन्हित अक्षर i_port[PR_APTPL_MAX_IPORT_LEN] = अणु पूर्ण;
	अचिन्हित अक्षर t_port[PR_APTPL_MAX_TPORT_LEN] = अणु पूर्ण;
	u16 tpgt;

	/*
	 * Copy Initiator Port inक्रमmation from काष्ठा se_node_acl
	 */
	snम_लिखो(i_port, PR_APTPL_MAX_IPORT_LEN, "%s", nacl->initiatorname);
	snम_लिखो(t_port, PR_APTPL_MAX_TPORT_LEN, "%s",
			tpg->se_tpg_tfo->tpg_get_wwn(tpg));
	tpgt = tpg->se_tpg_tfo->tpg_get_tag(tpg);
	/*
	 * Look क्रम the matching registrations+reservation from those
	 * created from APTPL metadata.  Note that multiple registrations
	 * may exist क्रम fabrics that use ISIDs in their SCSI Initiator Port
	 * TransportIDs.
	 */
	spin_lock(&pr_पंचांगpl->aptpl_reg_lock);
	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp, &pr_पंचांगpl->aptpl_reg_list,
				pr_reg_aptpl_list) अणु

		अगर (!म_भेद(pr_reg->pr_iport, i_port) &&
		     (pr_reg->pr_res_mapped_lun == mapped_lun) &&
		    !(म_भेद(pr_reg->pr_tport, t_port)) &&
		     (pr_reg->pr_reg_tpgt == tpgt) &&
		     (pr_reg->pr_aptpl_target_lun == target_lun)) अणु
			/*
			 * Obtain the ->pr_reg_deve poपूर्णांकer + reference, that
			 * is released by __core_scsi3_add_registration() below.
			 */
			rcu_पढ़ो_lock();
			pr_reg->pr_reg_deve = target_nacl_find_deve(nacl, mapped_lun);
			अगर (!pr_reg->pr_reg_deve) अणु
				pr_err("Unable to locate PR APTPL %s mapped_lun:"
					" %llu\n", nacl->initiatorname, mapped_lun);
				rcu_पढ़ो_unlock();
				जारी;
			पूर्ण
			kref_get(&pr_reg->pr_reg_deve->pr_kref);
			rcu_पढ़ो_unlock();

			pr_reg->pr_reg_nacl = nacl;
			pr_reg->tg_pt_sep_rtpi = lun->lun_rtpi;
			list_del(&pr_reg->pr_reg_aptpl_list);
			spin_unlock(&pr_पंचांगpl->aptpl_reg_lock);
			/*
			 * At this poपूर्णांक all of the poपूर्णांकers in *pr_reg will
			 * be setup, so go ahead and add the registration.
			 */
			__core_scsi3_add_registration(dev, nacl, pr_reg, 0, 0);
			/*
			 * If this registration is the reservation holder,
			 * make that happen now..
			 */
			अगर (pr_reg->pr_res_holder)
				core_scsi3_aptpl_reserve(dev, tpg,
						nacl, pr_reg);
			/*
			 * Reenable pr_aptpl_active to accept new metadata
			 * updates once the SCSI device is active again..
			 */
			spin_lock(&pr_पंचांगpl->aptpl_reg_lock);
			pr_पंचांगpl->pr_aptpl_active = 1;
		पूर्ण
	पूर्ण
	spin_unlock(&pr_पंचांगpl->aptpl_reg_lock);

	वापस 0;
पूर्ण

पूर्णांक core_scsi3_check_aptpl_registration(
	काष्ठा se_device *dev,
	काष्ठा se_portal_group *tpg,
	काष्ठा se_lun *lun,
	काष्ठा se_node_acl *nacl,
	u64 mapped_lun)
अणु
	अगर (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		वापस 0;

	वापस __core_scsi3_check_aptpl_registration(dev, tpg, lun,
						     lun->unpacked_lun, nacl,
						     mapped_lun);
पूर्ण

अटल व्योम __core_scsi3_dump_registration(
	स्थिर काष्ठा target_core_fabric_ops *tfo,
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl,
	काष्ठा t10_pr_registration *pr_reg,
	क्रमागत रेजिस्टर_type रेजिस्टर_type)
अणु
	काष्ठा se_portal_group *se_tpg = nacl->se_tpg;
	अक्षर i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;

	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);

	pr_debug("SPC-3 PR [%s] Service Action: REGISTER%s Initiator"
		" Node: %s%s\n", tfo->fabric_name, (रेजिस्टर_type == REGISTER_AND_MOVE) ?
		"_AND_MOVE" : (रेजिस्टर_type == REGISTER_AND_IGNORE_EXISTING_KEY) ?
		"_AND_IGNORE_EXISTING_KEY" : "", nacl->initiatorname,
		i_buf);
	pr_debug("SPC-3 PR [%s] registration on Target Port: %s,0x%04x\n",
		 tfo->fabric_name, tfo->tpg_get_wwn(se_tpg),
		tfo->tpg_get_tag(se_tpg));
	pr_debug("SPC-3 PR [%s] for %s TCM Subsystem %s Object Target"
		" Port(s)\n",  tfo->fabric_name,
		(pr_reg->pr_reg_all_tg_pt) ? "ALL" : "SINGLE",
		dev->transport->name);
	pr_debug("SPC-3 PR [%s] SA Res Key: 0x%016Lx PRgeneration:"
		" 0x%08x  APTPL: %d\n", tfo->fabric_name,
		pr_reg->pr_res_key, pr_reg->pr_res_generation,
		pr_reg->pr_reg_aptpl);
पूर्ण

अटल व्योम __core_scsi3_add_registration(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl,
	काष्ठा t10_pr_registration *pr_reg,
	क्रमागत रेजिस्टर_type रेजिस्टर_type,
	पूर्णांक रेजिस्टर_move)
अणु
	स्थिर काष्ठा target_core_fabric_ops *tfo = nacl->se_tpg->se_tpg_tfo;
	काष्ठा t10_pr_registration *pr_reg_पंचांगp, *pr_reg_पंचांगp_safe;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	काष्ठा se_dev_entry *deve;

	/*
	 * Increment PRgeneration counter क्रम काष्ठा se_device upon a successful
	 * REGISTER, see spc4r17 section 6.3.2 READ_KEYS service action
	 *
	 * Also, when रेजिस्टर_move = 1 क्रम PROUT REGISTER_AND_MOVE service
	 * action, the काष्ठा se_device->dev_reservation_lock will alपढ़ोy be held,
	 * so we करो not call core_scsi3_pr_generation() which grअसल the lock
	 * क्रम the REGISTER.
	 */
	pr_reg->pr_res_generation = (रेजिस्टर_move) ?
			dev->t10_pr.pr_generation++ :
			core_scsi3_pr_generation(dev);

	spin_lock(&pr_पंचांगpl->registration_lock);
	list_add_tail(&pr_reg->pr_reg_list, &pr_पंचांगpl->registration_list);

	__core_scsi3_dump_registration(tfo, dev, nacl, pr_reg, रेजिस्टर_type);
	spin_unlock(&pr_पंचांगpl->registration_lock);
	/*
	 * Skip extra processing क्रम ALL_TG_PT=0 or REGISTER_AND_MOVE.
	 */
	अगर (!pr_reg->pr_reg_all_tg_pt || रेजिस्टर_move)
		जाओ out;
	/*
	 * Walk pr_reg->pr_reg_atp_list and add registrations क्रम ALL_TG_PT=1
	 * allocated in __core_scsi3_alloc_registration()
	 */
	list_क्रम_each_entry_safe(pr_reg_पंचांगp, pr_reg_पंचांगp_safe,
			&pr_reg->pr_reg_atp_list, pr_reg_atp_mem_list) अणु
		काष्ठा se_node_acl *nacl_पंचांगp = pr_reg_पंचांगp->pr_reg_nacl;

		list_del(&pr_reg_पंचांगp->pr_reg_atp_mem_list);

		pr_reg_पंचांगp->pr_res_generation = core_scsi3_pr_generation(dev);

		spin_lock(&pr_पंचांगpl->registration_lock);
		list_add_tail(&pr_reg_पंचांगp->pr_reg_list,
			      &pr_पंचांगpl->registration_list);

		__core_scsi3_dump_registration(tfo, dev, nacl_पंचांगp, pr_reg_पंचांगp,
					       रेजिस्टर_type);
		spin_unlock(&pr_पंचांगpl->registration_lock);
		/*
		 * Drop configfs group dependency reference and deve->pr_kref
		 * obtained from  __core_scsi3_alloc_registration() code.
		 */
		rcu_पढ़ो_lock();
		deve = pr_reg_पंचांगp->pr_reg_deve;
		अगर (deve) अणु
			set_bit(DEF_PR_REG_ACTIVE, &deve->deve_flags);
			core_scsi3_lunacl_undepend_item(deve);
			pr_reg_पंचांगp->pr_reg_deve = शून्य;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
out:
	/*
	 * Drop deve->pr_kref obtained in __core_scsi3_करो_alloc_registration()
	 */
	rcu_पढ़ो_lock();
	deve = pr_reg->pr_reg_deve;
	अगर (deve) अणु
		set_bit(DEF_PR_REG_ACTIVE, &deve->deve_flags);
		kref_put(&deve->pr_kref, target_pr_kref_release);
		pr_reg->pr_reg_deve = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक core_scsi3_alloc_registration(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl,
	काष्ठा se_lun *lun,
	काष्ठा se_dev_entry *deve,
	u64 mapped_lun,
	अचिन्हित अक्षर *isid,
	u64 sa_res_key,
	पूर्णांक all_tg_pt,
	पूर्णांक aptpl,
	क्रमागत रेजिस्टर_type रेजिस्टर_type,
	पूर्णांक रेजिस्टर_move)
अणु
	काष्ठा t10_pr_registration *pr_reg;

	pr_reg = __core_scsi3_alloc_registration(dev, nacl, lun, deve, mapped_lun,
						 isid, sa_res_key, all_tg_pt,
						 aptpl);
	अगर (!pr_reg)
		वापस -EPERM;

	__core_scsi3_add_registration(dev, nacl, pr_reg,
			रेजिस्टर_type, रेजिस्टर_move);
	वापस 0;
पूर्ण

अटल काष्ठा t10_pr_registration *__core_scsi3_locate_pr_reg(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl,
	अचिन्हित अक्षर *isid)
अणु
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp;

	spin_lock(&pr_पंचांगpl->registration_lock);
	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
			&pr_पंचांगpl->registration_list, pr_reg_list) अणु
		/*
		 * First look क्रम a matching काष्ठा se_node_acl
		 */
		अगर (pr_reg->pr_reg_nacl != nacl)
			जारी;

		/*
		 * If this registration करोes NOT contain a fabric provided
		 * ISID, then we have found a match.
		 */
		अगर (!pr_reg->isid_present_at_reg) अणु
			atomic_inc_mb(&pr_reg->pr_res_holders);
			spin_unlock(&pr_पंचांगpl->registration_lock);
			वापस pr_reg;
		पूर्ण
		/*
		 * If the *pr_reg contains a fabric defined ISID क्रम multi-value
		 * SCSI Initiator Port TransportIDs, then we expect a valid
		 * matching ISID to be provided by the local SCSI Initiator Port.
		 */
		अगर (!isid)
			जारी;
		अगर (म_भेद(isid, pr_reg->pr_reg_isid))
			जारी;

		atomic_inc_mb(&pr_reg->pr_res_holders);
		spin_unlock(&pr_पंचांगpl->registration_lock);
		वापस pr_reg;
	पूर्ण
	spin_unlock(&pr_पंचांगpl->registration_lock);

	वापस शून्य;
पूर्ण

अटल काष्ठा t10_pr_registration *core_scsi3_locate_pr_reg(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl,
	काष्ठा se_session *sess)
अणु
	काष्ठा se_portal_group *tpg = nacl->se_tpg;
	अचिन्हित अक्षर buf[PR_REG_ISID_LEN] = अणु पूर्ण;
	अचिन्हित अक्षर *isid_ptr = शून्य;

	अगर (tpg->se_tpg_tfo->sess_get_initiator_sid != शून्य) अणु
		tpg->se_tpg_tfo->sess_get_initiator_sid(sess, &buf[0],
					PR_REG_ISID_LEN);
		isid_ptr = &buf[0];
	पूर्ण

	वापस __core_scsi3_locate_pr_reg(dev, nacl, isid_ptr);
पूर्ण

अटल व्योम core_scsi3_put_pr_reg(काष्ठा t10_pr_registration *pr_reg)
अणु
	atomic_dec_mb(&pr_reg->pr_res_holders);
पूर्ण

अटल पूर्णांक core_scsi3_check_implicit_release(
	काष्ठा se_device *dev,
	काष्ठा t10_pr_registration *pr_reg)
अणु
	काष्ठा se_node_acl *nacl = pr_reg->pr_reg_nacl;
	काष्ठा t10_pr_registration *pr_res_holder;
	पूर्णांक ret = 0;

	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर (!pr_res_holder) अणु
		spin_unlock(&dev->dev_reservation_lock);
		वापस ret;
	पूर्ण
	अगर (pr_res_holder == pr_reg) अणु
		/*
		 * Perक्रमm an implicit RELEASE अगर the registration that
		 * is being released is holding the reservation.
		 *
		 * From spc4r17, section 5.7.11.1:
		 *
		 * e) If the I_T nexus is the persistent reservation holder
		 *    and the persistent reservation is not an all registrants
		 *    type, then a PERSISTENT RESERVE OUT command with REGISTER
		 *    service action or REGISTER AND  IGNORE EXISTING KEY
		 *    service action with the SERVICE ACTION RESERVATION KEY
		 *    field set to zero (see 5.7.11.3).
		 */
		__core_scsi3_complete_pro_release(dev, nacl, pr_reg, 0, 1);
		ret = 1;
		/*
		 * For 'All Registrants' reservation types, all existing
		 * registrations are still processed as reservation holders
		 * in core_scsi3_pr_seq_non_holder() after the initial
		 * reservation holder is implicitly released here.
		 */
	पूर्ण अन्यथा अगर (pr_reg->pr_reg_all_tg_pt &&
		  (!म_भेद(pr_res_holder->pr_reg_nacl->initiatorname,
			  pr_reg->pr_reg_nacl->initiatorname)) &&
		  (pr_res_holder->pr_res_key == pr_reg->pr_res_key)) अणु
		pr_err("SPC-3 PR: Unable to perform ALL_TG_PT=1"
			" UNREGISTER while existing reservation with matching"
			" key 0x%016Lx is present from another SCSI Initiator"
			" Port\n", pr_reg->pr_res_key);
		ret = -EPERM;
	पूर्ण
	spin_unlock(&dev->dev_reservation_lock);

	वापस ret;
पूर्ण

अटल व्योम __core_scsi3_मुक्त_registration(
	काष्ठा se_device *dev,
	काष्ठा t10_pr_registration *pr_reg,
	काष्ठा list_head *preempt_and_पात_list,
	पूर्णांक dec_holders)
	__releases(&pr_पंचांगpl->registration_lock)
	__acquires(&pr_पंचांगpl->registration_lock)
अणु
	स्थिर काष्ठा target_core_fabric_ops *tfo =
			pr_reg->pr_reg_nacl->se_tpg->se_tpg_tfo;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	काष्ठा se_node_acl *nacl = pr_reg->pr_reg_nacl;
	काष्ठा se_dev_entry *deve;
	अक्षर i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;

	lockdep_निश्चित_held(&pr_पंचांगpl->registration_lock);

	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);

	अगर (!list_empty(&pr_reg->pr_reg_list))
		list_del(&pr_reg->pr_reg_list);
	/*
	 * Caller accessing *pr_reg using core_scsi3_locate_pr_reg(),
	 * so call core_scsi3_put_pr_reg() to decrement our reference.
	 */
	अगर (dec_holders)
		core_scsi3_put_pr_reg(pr_reg);

	spin_unlock(&pr_पंचांगpl->registration_lock);
	/*
	 * Wait until all reference from any other I_T nexuses क्रम this
	 * *pr_reg have been released.  Because list_del() is called above,
	 * the last core_scsi3_put_pr_reg(pr_reg) will release this reference
	 * count back to zero, and we release *pr_reg.
	 */
	जबतक (atomic_पढ़ो(&pr_reg->pr_res_holders) != 0) अणु
		pr_debug("SPC-3 PR [%s] waiting for pr_res_holders\n",
				tfo->fabric_name);
		cpu_relax();
	पूर्ण

	rcu_पढ़ो_lock();
	deve = target_nacl_find_deve(nacl, pr_reg->pr_res_mapped_lun);
	अगर (deve)
		clear_bit(DEF_PR_REG_ACTIVE, &deve->deve_flags);
	rcu_पढ़ो_unlock();

	spin_lock(&pr_पंचांगpl->registration_lock);
	pr_debug("SPC-3 PR [%s] Service Action: UNREGISTER Initiator"
		" Node: %s%s\n", tfo->fabric_name,
		pr_reg->pr_reg_nacl->initiatorname,
		i_buf);
	pr_debug("SPC-3 PR [%s] for %s TCM Subsystem %s Object Target"
		" Port(s)\n", tfo->fabric_name,
		(pr_reg->pr_reg_all_tg_pt) ? "ALL" : "SINGLE",
		dev->transport->name);
	pr_debug("SPC-3 PR [%s] SA Res Key: 0x%016Lx PRgeneration:"
		" 0x%08x\n", tfo->fabric_name, pr_reg->pr_res_key,
		pr_reg->pr_res_generation);

	अगर (!preempt_and_पात_list) अणु
		pr_reg->pr_reg_deve = शून्य;
		pr_reg->pr_reg_nacl = शून्य;
		kmem_cache_मुक्त(t10_pr_reg_cache, pr_reg);
		वापस;
	पूर्ण
	/*
	 * For PREEMPT_AND_ABORT, the list of *pr_reg in preempt_and_पात_list
	 * are released once the ABORT_TASK_SET has completed..
	 */
	list_add_tail(&pr_reg->pr_reg_पात_list, preempt_and_पात_list);
पूर्ण

व्योम core_scsi3_मुक्त_pr_reg_from_nacl(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *nacl)
अणु
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp, *pr_res_holder;
	bool मुक्त_reg = false;
	/*
	 * If the passed se_node_acl matches the reservation holder,
	 * release the reservation.
	 */
	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर ((pr_res_holder != शून्य) &&
	    (pr_res_holder->pr_reg_nacl == nacl)) अणु
		__core_scsi3_complete_pro_release(dev, nacl, pr_res_holder, 0, 1);
		मुक्त_reg = true;
	पूर्ण
	spin_unlock(&dev->dev_reservation_lock);
	/*
	 * Release any registration associated with the काष्ठा se_node_acl.
	 */
	spin_lock(&pr_पंचांगpl->registration_lock);
	अगर (pr_res_holder && मुक्त_reg)
		__core_scsi3_मुक्त_registration(dev, pr_res_holder, शून्य, 0);

	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
			&pr_पंचांगpl->registration_list, pr_reg_list) अणु

		अगर (pr_reg->pr_reg_nacl != nacl)
			जारी;

		__core_scsi3_मुक्त_registration(dev, pr_reg, शून्य, 0);
	पूर्ण
	spin_unlock(&pr_पंचांगpl->registration_lock);
पूर्ण

व्योम core_scsi3_मुक्त_all_registrations(
	काष्ठा se_device *dev)
अणु
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp, *pr_res_holder;

	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर (pr_res_holder != शून्य) अणु
		काष्ठा se_node_acl *pr_res_nacl = pr_res_holder->pr_reg_nacl;
		__core_scsi3_complete_pro_release(dev, pr_res_nacl,
						  pr_res_holder, 0, 0);
	पूर्ण
	spin_unlock(&dev->dev_reservation_lock);

	spin_lock(&pr_पंचांगpl->registration_lock);
	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
			&pr_पंचांगpl->registration_list, pr_reg_list) अणु

		__core_scsi3_मुक्त_registration(dev, pr_reg, शून्य, 0);
	पूर्ण
	spin_unlock(&pr_पंचांगpl->registration_lock);

	spin_lock(&pr_पंचांगpl->aptpl_reg_lock);
	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp, &pr_पंचांगpl->aptpl_reg_list,
				pr_reg_aptpl_list) अणु
		list_del(&pr_reg->pr_reg_aptpl_list);
		kmem_cache_मुक्त(t10_pr_reg_cache, pr_reg);
	पूर्ण
	spin_unlock(&pr_पंचांगpl->aptpl_reg_lock);
पूर्ण

अटल पूर्णांक core_scsi3_tpg_depend_item(काष्ठा se_portal_group *tpg)
अणु
	वापस target_depend_item(&tpg->tpg_group.cg_item);
पूर्ण

अटल व्योम core_scsi3_tpg_undepend_item(काष्ठा se_portal_group *tpg)
अणु
	target_undepend_item(&tpg->tpg_group.cg_item);
	atomic_dec_mb(&tpg->tpg_pr_ref_count);
पूर्ण

अटल पूर्णांक core_scsi3_nodeacl_depend_item(काष्ठा se_node_acl *nacl)
अणु
	अगर (nacl->dynamic_node_acl)
		वापस 0;
	वापस target_depend_item(&nacl->acl_group.cg_item);
पूर्ण

अटल व्योम core_scsi3_nodeacl_undepend_item(काष्ठा se_node_acl *nacl)
अणु
	अगर (!nacl->dynamic_node_acl)
		target_undepend_item(&nacl->acl_group.cg_item);
	atomic_dec_mb(&nacl->acl_pr_ref_count);
पूर्ण

अटल पूर्णांक core_scsi3_lunacl_depend_item(काष्ठा se_dev_entry *se_deve)
अणु
	काष्ठा se_lun_acl *lun_acl;

	/*
	 * For nacl->dynamic_node_acl=1
	 */
	lun_acl = rcu_dereference_check(se_deve->se_lun_acl,
				kref_पढ़ो(&se_deve->pr_kref) != 0);
	अगर (!lun_acl)
		वापस 0;

	वापस target_depend_item(&lun_acl->se_lun_group.cg_item);
पूर्ण

अटल व्योम core_scsi3_lunacl_undepend_item(काष्ठा se_dev_entry *se_deve)
अणु
	काष्ठा se_lun_acl *lun_acl;

	/*
	 * For nacl->dynamic_node_acl=1
	 */
	lun_acl = rcu_dereference_check(se_deve->se_lun_acl,
				kref_पढ़ो(&se_deve->pr_kref) != 0);
	अगर (!lun_acl) अणु
		kref_put(&se_deve->pr_kref, target_pr_kref_release);
		वापस;
	पूर्ण

	target_undepend_item(&lun_acl->se_lun_group.cg_item);
	kref_put(&se_deve->pr_kref, target_pr_kref_release);
पूर्ण

अटल sense_reason_t
core_scsi3_decode_spec_i_port(
	काष्ठा se_cmd *cmd,
	काष्ठा se_portal_group *tpg,
	अचिन्हित अक्षर *l_isid,
	u64 sa_res_key,
	पूर्णांक all_tg_pt,
	पूर्णांक aptpl)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_portal_group *dest_tpg = शून्य, *पंचांगp_tpg;
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_node_acl *dest_node_acl = शून्य;
	काष्ठा se_dev_entry *dest_se_deve = शून्य;
	काष्ठा t10_pr_registration *dest_pr_reg, *local_pr_reg, *pr_reg_e;
	काष्ठा t10_pr_registration *pr_reg_पंचांगp, *pr_reg_पंचांगp_safe;
	LIST_HEAD(tid_dest_list);
	काष्ठा pr_transport_id_holder *tidh_new, *tidh, *tidh_पंचांगp;
	अचिन्हित अक्षर *buf, *ptr, proto_ident;
	स्थिर अचिन्हित अक्षर *i_str = शून्य;
	अक्षर *iport_ptr = शून्य, i_buf[PR_REG_ISID_ID_LEN];
	sense_reason_t ret;
	u32 tpdl, tid_len = 0;
	u32 dest_rtpi = 0;

	/*
	 * Allocate a काष्ठा pr_transport_id_holder and setup the
	 * local_node_acl poपूर्णांकer and add to काष्ठा list_head tid_dest_list
	 * क्रम add registration processing in the loop of tid_dest_list below.
	 */
	tidh_new = kzalloc(माप(काष्ठा pr_transport_id_holder), GFP_KERNEL);
	अगर (!tidh_new) अणु
		pr_err("Unable to allocate tidh_new\n");
		वापस TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
	पूर्ण
	INIT_LIST_HEAD(&tidh_new->dest_list);
	tidh_new->dest_tpg = tpg;
	tidh_new->dest_node_acl = se_sess->se_node_acl;

	local_pr_reg = __core_scsi3_alloc_registration(cmd->se_dev,
				se_sess->se_node_acl, cmd->se_lun,
				शून्य, cmd->orig_fe_lun, l_isid,
				sa_res_key, all_tg_pt, aptpl);
	अगर (!local_pr_reg) अणु
		kमुक्त(tidh_new);
		वापस TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
	पूर्ण

	अगर (core_scsi3_lunacl_depend_item(local_pr_reg->pr_reg_deve)) अणु
		kमुक्त(tidh_new);
		kref_put(&local_pr_reg->pr_reg_deve->pr_kref,
			 target_pr_kref_release);
		kmem_cache_मुक्त(t10_pr_reg_cache, local_pr_reg);
		वापस TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
	पूर्ण

	tidh_new->dest_pr_reg = local_pr_reg;
	list_add_tail(&tidh_new->dest_list, &tid_dest_list);

	अगर (cmd->data_length < 28) अणु
		pr_warn("SPC-PR: Received PR OUT parameter list"
			" length too small: %u\n", cmd->data_length);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf) अणु
		ret = TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
		जाओ out;
	पूर्ण

	/*
	 * For a PERSISTENT RESERVE OUT specअगरy initiator ports payload,
	 * first extract TransportID Parameter Data Length, and make sure
	 * the value matches up to the SCSI expected data transfer length.
	 */
	tpdl = get_unaligned_be32(&buf[24]);

	अगर ((tpdl + 28) != cmd->data_length) अणु
		pr_err("SPC-3 PR: Illegal tpdl: %u + 28 byte header"
			" does not equal CDB data_length: %u\n", tpdl,
			cmd->data_length);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out_unmap;
	पूर्ण
	/*
	 * Start processing the received transport IDs using the
	 * receiving I_T Nexus portal's fabric dependent methods to
	 * obtain the SCSI Initiator Port/Device Identअगरiers.
	 */
	ptr = &buf[28];

	जबतक (tpdl > 0) अणु
		काष्ठा se_lun *dest_lun, *पंचांगp_lun;

		proto_ident = (ptr[0] & 0x0f);
		dest_tpg = शून्य;

		spin_lock(&dev->se_port_lock);
		list_क्रम_each_entry(पंचांगp_lun, &dev->dev_sep_list, lun_dev_link) अणु
			पंचांगp_tpg = पंचांगp_lun->lun_tpg;

			/*
			 * Look क्रम the matching proto_ident provided by
			 * the received TransportID
			 */
			अगर (पंचांगp_tpg->proto_id != proto_ident)
				जारी;
			dest_rtpi = पंचांगp_lun->lun_rtpi;

			iport_ptr = शून्य;
			i_str = target_parse_pr_out_transport_id(पंचांगp_tpg,
					ptr, &tid_len, &iport_ptr);
			अगर (!i_str)
				जारी;
			/*
			 * Determine अगर this SCSI device server requires that
			 * SCSI Intiatior TransportID w/ ISIDs is enक्रमced
			 * क्रम fabric modules (iSCSI) requiring them.
			 */
			अगर (tpg->se_tpg_tfo->sess_get_initiator_sid &&
			    dev->dev_attrib.enक्रमce_pr_isids &&
			    !iport_ptr) अणु
				pr_warn("SPC-PR: enforce_pr_isids is set but a isid has not been sent in the SPEC_I_PT data for %s.",
					i_str);
				ret = TCM_INVALID_PARAMETER_LIST;
				spin_unlock(&dev->se_port_lock);
				जाओ out_unmap;
			पूर्ण

			atomic_inc_mb(&पंचांगp_tpg->tpg_pr_ref_count);
			spin_unlock(&dev->se_port_lock);

			अगर (core_scsi3_tpg_depend_item(पंचांगp_tpg)) अणु
				pr_err(" core_scsi3_tpg_depend_item()"
					" for tmp_tpg\n");
				atomic_dec_mb(&पंचांगp_tpg->tpg_pr_ref_count);
				ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
				जाओ out_unmap;
			पूर्ण
			/*
			 * Locate the destination initiator ACL to be रेजिस्टरed
			 * from the decoded fabric module specअगरic TransportID
			 * at *i_str.
			 */
			mutex_lock(&पंचांगp_tpg->acl_node_mutex);
			dest_node_acl = __core_tpg_get_initiator_node_acl(
						पंचांगp_tpg, i_str);
			अगर (dest_node_acl)
				atomic_inc_mb(&dest_node_acl->acl_pr_ref_count);
			mutex_unlock(&पंचांगp_tpg->acl_node_mutex);

			अगर (!dest_node_acl) अणु
				core_scsi3_tpg_undepend_item(पंचांगp_tpg);
				spin_lock(&dev->se_port_lock);
				जारी;
			पूर्ण

			अगर (core_scsi3_nodeacl_depend_item(dest_node_acl)) अणु
				pr_err("configfs_depend_item() failed"
					" for dest_node_acl->acl_group\n");
				atomic_dec_mb(&dest_node_acl->acl_pr_ref_count);
				core_scsi3_tpg_undepend_item(पंचांगp_tpg);
				ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
				जाओ out_unmap;
			पूर्ण

			dest_tpg = पंचांगp_tpg;
			pr_debug("SPC-3 PR SPEC_I_PT: Located %s Node: %s Port RTPI: %u\n",
				dest_tpg->se_tpg_tfo->fabric_name,
				dest_node_acl->initiatorname, dest_rtpi);

			spin_lock(&dev->se_port_lock);
			अवरोध;
		पूर्ण
		spin_unlock(&dev->se_port_lock);

		अगर (!dest_tpg) अणु
			pr_err("SPC-3 PR SPEC_I_PT: Unable to locate"
					" dest_tpg\n");
			ret = TCM_INVALID_PARAMETER_LIST;
			जाओ out_unmap;
		पूर्ण

		pr_debug("SPC-3 PR SPEC_I_PT: Got %s data_length: %u tpdl: %u"
			" tid_len: %d for %s + %s\n",
			dest_tpg->se_tpg_tfo->fabric_name, cmd->data_length,
			tpdl, tid_len, i_str, iport_ptr);

		अगर (tid_len > tpdl) अणु
			pr_err("SPC-3 PR SPEC_I_PT: Illegal tid_len:"
				" %u for Transport ID: %s\n", tid_len, ptr);
			core_scsi3_nodeacl_undepend_item(dest_node_acl);
			core_scsi3_tpg_undepend_item(dest_tpg);
			ret = TCM_INVALID_PARAMETER_LIST;
			जाओ out_unmap;
		पूर्ण
		/*
		 * Locate the desपूर्णांकation काष्ठा se_dev_entry poपूर्णांकer क्रम matching
		 * RELATIVE TARGET PORT IDENTIFIER on the receiving I_T Nexus
		 * Target Port.
		 */
		dest_se_deve = core_get_se_deve_from_rtpi(dest_node_acl,
					dest_rtpi);
		अगर (!dest_se_deve) अणु
			pr_err("Unable to locate %s dest_se_deve from destination RTPI: %u\n",
				dest_tpg->se_tpg_tfo->fabric_name,
				dest_rtpi);

			core_scsi3_nodeacl_undepend_item(dest_node_acl);
			core_scsi3_tpg_undepend_item(dest_tpg);
			ret = TCM_INVALID_PARAMETER_LIST;
			जाओ out_unmap;
		पूर्ण

		अगर (core_scsi3_lunacl_depend_item(dest_se_deve)) अणु
			pr_err("core_scsi3_lunacl_depend_item()"
					" failed\n");
			kref_put(&dest_se_deve->pr_kref, target_pr_kref_release);
			core_scsi3_nodeacl_undepend_item(dest_node_acl);
			core_scsi3_tpg_undepend_item(dest_tpg);
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
			जाओ out_unmap;
		पूर्ण

		pr_debug("SPC-3 PR SPEC_I_PT: Located %s Node: %s"
			" dest_se_deve mapped_lun: %llu\n",
			dest_tpg->se_tpg_tfo->fabric_name,
			dest_node_acl->initiatorname, dest_se_deve->mapped_lun);

		/*
		 * Skip any TransportIDs that alपढ़ोy have a registration क्रम
		 * this target port.
		 */
		pr_reg_e = __core_scsi3_locate_pr_reg(dev, dest_node_acl,
					iport_ptr);
		अगर (pr_reg_e) अणु
			core_scsi3_put_pr_reg(pr_reg_e);
			core_scsi3_lunacl_undepend_item(dest_se_deve);
			core_scsi3_nodeacl_undepend_item(dest_node_acl);
			core_scsi3_tpg_undepend_item(dest_tpg);
			ptr += tid_len;
			tpdl -= tid_len;
			tid_len = 0;
			जारी;
		पूर्ण
		/*
		 * Allocate a काष्ठा pr_transport_id_holder and setup
		 * the dest_node_acl and dest_se_deve poपूर्णांकers क्रम the
		 * loop below.
		 */
		tidh_new = kzalloc(माप(काष्ठा pr_transport_id_holder),
				GFP_KERNEL);
		अगर (!tidh_new) अणु
			pr_err("Unable to allocate tidh_new\n");
			core_scsi3_lunacl_undepend_item(dest_se_deve);
			core_scsi3_nodeacl_undepend_item(dest_node_acl);
			core_scsi3_tpg_undepend_item(dest_tpg);
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
			जाओ out_unmap;
		पूर्ण
		INIT_LIST_HEAD(&tidh_new->dest_list);
		tidh_new->dest_tpg = dest_tpg;
		tidh_new->dest_node_acl = dest_node_acl;
		tidh_new->dest_se_deve = dest_se_deve;

		/*
		 * Allocate, but करो NOT add the registration क्रम the
		 * TransportID referenced SCSI Initiator port.  This
		 * करोne because of the following from spc4r17 in section
		 * 6.14.3 wrt SPEC_I_PT:
		 *
		 * "If a registration fails क्रम any initiator port (e.g., अगर th
		 * logical unit करोes not have enough resources available to
		 * hold the registration inक्रमmation), no registrations shall be
		 * made, and the command shall be terminated with
		 * CHECK CONDITION status."
		 *
		 * That means we call __core_scsi3_alloc_registration() here,
		 * and then call __core_scsi3_add_registration() in the
		 * 2nd loop which will never fail.
		 */
		dest_lun = rcu_dereference_check(dest_se_deve->se_lun,
				kref_पढ़ो(&dest_se_deve->pr_kref) != 0);

		dest_pr_reg = __core_scsi3_alloc_registration(cmd->se_dev,
					dest_node_acl, dest_lun, dest_se_deve,
					dest_se_deve->mapped_lun, iport_ptr,
					sa_res_key, all_tg_pt, aptpl);
		अगर (!dest_pr_reg) अणु
			core_scsi3_lunacl_undepend_item(dest_se_deve);
			core_scsi3_nodeacl_undepend_item(dest_node_acl);
			core_scsi3_tpg_undepend_item(dest_tpg);
			kमुक्त(tidh_new);
			ret = TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
			जाओ out_unmap;
		पूर्ण
		tidh_new->dest_pr_reg = dest_pr_reg;
		list_add_tail(&tidh_new->dest_list, &tid_dest_list);

		ptr += tid_len;
		tpdl -= tid_len;
		tid_len = 0;

	पूर्ण

	transport_kunmap_data_sg(cmd);

	/*
	 * Go ahead and create a registrations from tid_dest_list क्रम the
	 * SPEC_I_PT provided TransportID क्रम the *tidh referenced dest_node_acl
	 * and dest_se_deve.
	 *
	 * The SA Reservation Key from the PROUT is set क्रम the
	 * registration, and ALL_TG_PT is also passed.  ALL_TG_PT=1
	 * means that the TransportID Initiator port will be
	 * रेजिस्टरed on all of the target ports in the SCSI target device
	 * ALL_TG_PT=0 means the registration will only be क्रम the
	 * SCSI target port the PROUT REGISTER with SPEC_I_PT=1
	 * was received.
	 */
	list_क्रम_each_entry_safe(tidh, tidh_पंचांगp, &tid_dest_list, dest_list) अणु
		dest_tpg = tidh->dest_tpg;
		dest_node_acl = tidh->dest_node_acl;
		dest_se_deve = tidh->dest_se_deve;
		dest_pr_reg = tidh->dest_pr_reg;

		list_del(&tidh->dest_list);
		kमुक्त(tidh);

		स_रखो(i_buf, 0, PR_REG_ISID_ID_LEN);
		core_pr_dump_initiator_port(dest_pr_reg, i_buf, PR_REG_ISID_ID_LEN);

		__core_scsi3_add_registration(cmd->se_dev, dest_node_acl,
					dest_pr_reg, 0, 0);

		pr_debug("SPC-3 PR [%s] SPEC_I_PT: Successfully"
			" registered Transport ID for Node: %s%s Mapped LUN:"
			" %llu\n", dest_tpg->se_tpg_tfo->fabric_name,
			dest_node_acl->initiatorname, i_buf, (dest_se_deve) ?
			dest_se_deve->mapped_lun : 0);

		अगर (dest_pr_reg == local_pr_reg)
			जारी;

		core_scsi3_nodeacl_undepend_item(dest_node_acl);
		core_scsi3_tpg_undepend_item(dest_tpg);
	पूर्ण

	वापस 0;
out_unmap:
	transport_kunmap_data_sg(cmd);
out:
	/*
	 * For the failure हाल, release everything from tid_dest_list
	 * including *dest_pr_reg and the configfs dependances..
	 */
	list_क्रम_each_entry_safe(tidh, tidh_पंचांगp, &tid_dest_list, dest_list) अणु
		bool is_local = false;

		dest_tpg = tidh->dest_tpg;
		dest_node_acl = tidh->dest_node_acl;
		dest_se_deve = tidh->dest_se_deve;
		dest_pr_reg = tidh->dest_pr_reg;

		अगर (dest_pr_reg == local_pr_reg)
			is_local = true;

		list_del(&tidh->dest_list);
		kमुक्त(tidh);
		/*
		 * Release any extra ALL_TG_PT=1 registrations क्रम
		 * the SPEC_I_PT=1 हाल.
		 */
		list_क्रम_each_entry_safe(pr_reg_पंचांगp, pr_reg_पंचांगp_safe,
				&dest_pr_reg->pr_reg_atp_list,
				pr_reg_atp_mem_list) अणु
			list_del(&pr_reg_पंचांगp->pr_reg_atp_mem_list);
			core_scsi3_lunacl_undepend_item(pr_reg_पंचांगp->pr_reg_deve);
			kmem_cache_मुक्त(t10_pr_reg_cache, pr_reg_पंचांगp);
		पूर्ण

		kmem_cache_मुक्त(t10_pr_reg_cache, dest_pr_reg);
		core_scsi3_lunacl_undepend_item(dest_se_deve);

		अगर (is_local)
			जारी;

		core_scsi3_nodeacl_undepend_item(dest_node_acl);
		core_scsi3_tpg_undepend_item(dest_tpg);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक core_scsi3_update_aptpl_buf(
	काष्ठा se_device *dev,
	अचिन्हित अक्षर *buf,
	u32 pr_aptpl_buf_len)
अणु
	काष्ठा se_portal_group *tpg;
	काष्ठा t10_pr_registration *pr_reg;
	अचिन्हित अक्षर पंचांगp[512], isid_buf[32];
	sमाप_प्रकार len = 0;
	पूर्णांक reg_count = 0;
	पूर्णांक ret = 0;

	spin_lock(&dev->dev_reservation_lock);
	spin_lock(&dev->t10_pr.registration_lock);
	/*
	 * Walk the registration list..
	 */
	list_क्रम_each_entry(pr_reg, &dev->t10_pr.registration_list,
			pr_reg_list) अणु

		पंचांगp[0] = '\0';
		isid_buf[0] = '\0';
		tpg = pr_reg->pr_reg_nacl->se_tpg;
		/*
		 * Write out any ISID value to APTPL metadata that was included
		 * in the original registration.
		 */
		अगर (pr_reg->isid_present_at_reg)
			snम_लिखो(isid_buf, 32, "initiator_sid=%s\n",
					pr_reg->pr_reg_isid);
		/*
		 * Include special metadata अगर the pr_reg matches the
		 * reservation holder.
		 */
		अगर (dev->dev_pr_res_holder == pr_reg) अणु
			snम_लिखो(पंचांगp, 512, "PR_REG_START: %d"
				"\ninitiator_fabric=%s\n"
				"initiator_node=%s\n%s"
				"sa_res_key=%llu\n"
				"res_holder=1\nres_type=%02x\n"
				"res_scope=%02x\nres_all_tg_pt=%d\n"
				"mapped_lun=%llu\n", reg_count,
				tpg->se_tpg_tfo->fabric_name,
				pr_reg->pr_reg_nacl->initiatorname, isid_buf,
				pr_reg->pr_res_key, pr_reg->pr_res_type,
				pr_reg->pr_res_scope, pr_reg->pr_reg_all_tg_pt,
				pr_reg->pr_res_mapped_lun);
		पूर्ण अन्यथा अणु
			snम_लिखो(पंचांगp, 512, "PR_REG_START: %d\n"
				"initiator_fabric=%s\ninitiator_node=%s\n%s"
				"sa_res_key=%llu\nres_holder=0\n"
				"res_all_tg_pt=%d\nmapped_lun=%llu\n",
				reg_count, tpg->se_tpg_tfo->fabric_name,
				pr_reg->pr_reg_nacl->initiatorname, isid_buf,
				pr_reg->pr_res_key, pr_reg->pr_reg_all_tg_pt,
				pr_reg->pr_res_mapped_lun);
		पूर्ण

		अगर ((len + म_माप(पंचांगp) >= pr_aptpl_buf_len)) अणु
			pr_err("Unable to update renaming APTPL metadata,"
			       " reallocating larger buffer\n");
			ret = -EMSGSIZE;
			जाओ out;
		पूर्ण
		len += प्र_लिखो(buf+len, "%s", पंचांगp);

		/*
		 * Include inक्रमmation about the associated SCSI target port.
		 */
		snम_लिखो(पंचांगp, 512, "target_fabric=%s\ntarget_node=%s\n"
			"tpgt=%hu\nport_rtpi=%hu\ntarget_lun=%llu\nPR_REG_END:"
			" %d\n", tpg->se_tpg_tfo->fabric_name,
			tpg->se_tpg_tfo->tpg_get_wwn(tpg),
			tpg->se_tpg_tfo->tpg_get_tag(tpg),
			pr_reg->tg_pt_sep_rtpi, pr_reg->pr_aptpl_target_lun,
			reg_count);

		अगर ((len + म_माप(पंचांगp) >= pr_aptpl_buf_len)) अणु
			pr_err("Unable to update renaming APTPL metadata,"
			       " reallocating larger buffer\n");
			ret = -EMSGSIZE;
			जाओ out;
		पूर्ण
		len += प्र_लिखो(buf+len, "%s", पंचांगp);
		reg_count++;
	पूर्ण

	अगर (!reg_count)
		len += प्र_लिखो(buf+len, "No Registrations or Reservations");

out:
	spin_unlock(&dev->t10_pr.registration_lock);
	spin_unlock(&dev->dev_reservation_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __core_scsi3_ग_लिखो_aptpl_to_file(
	काष्ठा se_device *dev,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा t10_wwn *wwn = &dev->t10_wwn;
	काष्ठा file *file;
	पूर्णांक flags = O_RDWR | O_CREAT | O_TRUNC;
	अक्षर *path;
	u32 pr_aptpl_buf_len;
	पूर्णांक ret;
	loff_t pos = 0;

	path = kaप्र_लिखो(GFP_KERNEL, "%s/pr/aptpl_%s", db_root,
			&wwn->unit_serial[0]);
	अगर (!path)
		वापस -ENOMEM;

	file = filp_खोलो(path, flags, 0600);
	अगर (IS_ERR(file)) अणु
		pr_err("filp_open(%s) for APTPL metadata"
			" failed\n", path);
		kमुक्त(path);
		वापस PTR_ERR(file);
	पूर्ण

	pr_aptpl_buf_len = (म_माप(buf) + 1); /* Add extra क्रम शून्य */

	ret = kernel_ग_लिखो(file, buf, pr_aptpl_buf_len, &pos);

	अगर (ret < 0)
		pr_debug("Error writing APTPL metadata file: %s\n", path);
	fput(file);
	kमुक्त(path);

	वापस (ret < 0) ? -EIO : 0;
पूर्ण

/*
 * Clear the APTPL metadata अगर APTPL has been disabled, otherwise
 * ग_लिखो out the updated metadata to काष्ठा file क्रम this SCSI device.
 */
अटल sense_reason_t core_scsi3_update_and_ग_लिखो_aptpl(काष्ठा se_device *dev, bool aptpl)
अणु
	अचिन्हित अक्षर *buf;
	पूर्णांक rc, len = PR_APTPL_BUF_LEN;

	अगर (!aptpl) अणु
		अक्षर *null_buf = "No Registrations or Reservations\n";

		rc = __core_scsi3_ग_लिखो_aptpl_to_file(dev, null_buf);
		dev->t10_pr.pr_aptpl_active = 0;
		pr_debug("SPC-3 PR: Set APTPL Bit Deactivated\n");

		अगर (rc)
			वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

		वापस 0;
	पूर्ण
retry:
	buf = vzalloc(len);
	अगर (!buf)
		वापस TCM_OUT_OF_RESOURCES;

	rc = core_scsi3_update_aptpl_buf(dev, buf, len);
	अगर (rc < 0) अणु
		vमुक्त(buf);
		len *= 2;
		जाओ retry;
	पूर्ण

	rc = __core_scsi3_ग_लिखो_aptpl_to_file(dev, buf);
	अगर (rc != 0) अणु
		pr_err("SPC-3 PR: Could not update APTPL\n");
		vमुक्त(buf);
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	dev->t10_pr.pr_aptpl_active = 1;
	vमुक्त(buf);
	pr_debug("SPC-3 PR: Set APTPL Bit Activated\n");
	वापस 0;
पूर्ण

अटल sense_reason_t
core_scsi3_emulate_pro_रेजिस्टर(काष्ठा se_cmd *cmd, u64 res_key, u64 sa_res_key,
		bool aptpl, bool all_tg_pt, bool spec_i_pt, क्रमागत रेजिस्टर_type रेजिस्टर_type)
अणु
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_lun *se_lun = cmd->se_lun;
	काष्ठा se_portal_group *se_tpg;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_p, *pr_reg_पंचांगp;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	अचिन्हित अक्षर isid_buf[PR_REG_ISID_LEN] = अणु पूर्ण;
	अचिन्हित अक्षर *isid_ptr = शून्य;
	sense_reason_t ret = TCM_NO_SENSE;
	पूर्णांक pr_holder = 0, type;

	अगर (!se_sess || !se_lun) अणु
		pr_err("SPC-3 PR: se_sess || struct se_lun is NULL!\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	se_tpg = se_sess->se_tpg;

	अगर (se_tpg->se_tpg_tfo->sess_get_initiator_sid) अणु
		se_tpg->se_tpg_tfo->sess_get_initiator_sid(se_sess, &isid_buf[0],
				PR_REG_ISID_LEN);
		isid_ptr = &isid_buf[0];
	पूर्ण
	/*
	 * Follow logic from spc4r17 Section 5.7.7, Register Behaviors Table 47
	 */
	pr_reg = core_scsi3_locate_pr_reg(dev, se_sess->se_node_acl, se_sess);
	अगर (!pr_reg) अणु
		अगर (res_key) अणु
			pr_warn("SPC-3 PR: Reservation Key non-zero"
				" for SA REGISTER, returning CONFLICT\n");
			वापस TCM_RESERVATION_CONFLICT;
		पूर्ण
		/*
		 * Do nothing but वापस GOOD status.
		 */
		अगर (!sa_res_key)
			वापस 0;

		अगर (!spec_i_pt) अणु
			/*
			 * Perक्रमm the Service Action REGISTER on the Initiator
			 * Port Endpoपूर्णांक that the PRO was received from on the
			 * Logical Unit of the SCSI device server.
			 */
			अगर (core_scsi3_alloc_registration(cmd->se_dev,
					se_sess->se_node_acl, cmd->se_lun,
					शून्य, cmd->orig_fe_lun, isid_ptr,
					sa_res_key, all_tg_pt, aptpl,
					रेजिस्टर_type, 0)) अणु
				pr_err("Unable to allocate"
					" struct t10_pr_registration\n");
				वापस TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Register both the Initiator port that received
			 * PROUT SA REGISTER + SPEC_I_PT=1 and extract SCSI
			 * TransportID from Parameter list and loop through
			 * fabric dependent parameter list जबतक calling
			 * logic from of core_scsi3_alloc_registration() क्रम
			 * each TransportID provided SCSI Initiator Port/Device
			 */
			ret = core_scsi3_decode_spec_i_port(cmd, se_tpg,
					isid_ptr, sa_res_key, all_tg_pt, aptpl);
			अगर (ret != 0)
				वापस ret;
		पूर्ण
		वापस core_scsi3_update_and_ग_लिखो_aptpl(dev, aptpl);
	पूर्ण

	/* ok, existing registration */

	अगर ((रेजिस्टर_type == REGISTER) && (res_key != pr_reg->pr_res_key)) अणु
		pr_err("SPC-3 PR REGISTER: Received"
		       " res_key: 0x%016Lx does not match"
		       " existing SA REGISTER res_key:"
		       " 0x%016Lx\n", res_key,
		       pr_reg->pr_res_key);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out;
	पूर्ण

	अगर (spec_i_pt) अणु
		pr_err("SPC-3 PR REGISTER: SPEC_I_PT"
			" set on a registered nexus\n");
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण

	/*
	 * An existing ALL_TG_PT=1 registration being released
	 * must also set ALL_TG_PT=1 in the incoming PROUT.
	 */
	अगर (pr_reg->pr_reg_all_tg_pt && !all_tg_pt) अणु
		pr_err("SPC-3 PR REGISTER: ALL_TG_PT=1"
			" registration exists, but ALL_TG_PT=1 bit not"
			" present in received PROUT\n");
		ret = TCM_INVALID_CDB_FIELD;
		जाओ out;
	पूर्ण

	/*
	 * sa_res_key=1 Change Reservation Key क्रम रेजिस्टरed I_T Nexus.
	 */
	अगर (sa_res_key) अणु
		/*
		 * Increment PRgeneration counter क्रम काष्ठा se_device"
		 * upon a successful REGISTER, see spc4r17 section 6.3.2
		 * READ_KEYS service action.
		 */
		pr_reg->pr_res_generation = core_scsi3_pr_generation(cmd->se_dev);
		pr_reg->pr_res_key = sa_res_key;
		pr_debug("SPC-3 PR [%s] REGISTER%s: Changed Reservation"
			 " Key for %s to: 0x%016Lx PRgeneration:"
			 " 0x%08x\n", cmd->se_tfo->fabric_name,
			 (रेजिस्टर_type == REGISTER_AND_IGNORE_EXISTING_KEY) ? "_AND_IGNORE_EXISTING_KEY" : "",
			 pr_reg->pr_reg_nacl->initiatorname,
			 pr_reg->pr_res_key, pr_reg->pr_res_generation);

	पूर्ण अन्यथा अणु
		/*
		 * sa_res_key=0 Unरेजिस्टर Reservation Key क्रम रेजिस्टरed I_T Nexus.
		 */
		type = pr_reg->pr_res_type;
		pr_holder = core_scsi3_check_implicit_release(cmd->se_dev,
							      pr_reg);
		अगर (pr_holder < 0) अणु
			ret = TCM_RESERVATION_CONFLICT;
			जाओ out;
		पूर्ण

		spin_lock(&pr_पंचांगpl->registration_lock);
		/*
		 * Release all ALL_TG_PT=1 क्रम the matching SCSI Initiator Port
		 * and matching pr_res_key.
		 */
		अगर (pr_reg->pr_reg_all_tg_pt) अणु
			list_क्रम_each_entry_safe(pr_reg_p, pr_reg_पंचांगp,
					&pr_पंचांगpl->registration_list,
					pr_reg_list) अणु

				अगर (!pr_reg_p->pr_reg_all_tg_pt)
					जारी;
				अगर (pr_reg_p->pr_res_key != res_key)
					जारी;
				अगर (pr_reg == pr_reg_p)
					जारी;
				अगर (म_भेद(pr_reg->pr_reg_nacl->initiatorname,
					   pr_reg_p->pr_reg_nacl->initiatorname))
					जारी;

				__core_scsi3_मुक्त_registration(dev,
						pr_reg_p, शून्य, 0);
			पूर्ण
		पूर्ण

		/*
		 * Release the calling I_T Nexus registration now..
		 */
		__core_scsi3_मुक्त_registration(cmd->se_dev, pr_reg, शून्य, 1);
		pr_reg = शून्य;

		/*
		 * From spc4r17, section 5.7.11.3 Unरेजिस्टरing
		 *
		 * If the persistent reservation is a registrants only
		 * type, the device server shall establish a unit
		 * attention condition क्रम the initiator port associated
		 * with every रेजिस्टरed I_T nexus except क्रम the I_T
		 * nexus on which the PERSISTENT RESERVE OUT command was
		 * received, with the additional sense code set to
		 * RESERVATIONS RELEASED.
		 */
		अगर (pr_holder &&
		    (type == PR_TYPE_WRITE_EXCLUSIVE_REGONLY ||
		     type == PR_TYPE_EXCLUSIVE_ACCESS_REGONLY)) अणु
			list_क्रम_each_entry(pr_reg_p,
					&pr_पंचांगpl->registration_list,
					pr_reg_list) अणु

				target_ua_allocate_lun(
					pr_reg_p->pr_reg_nacl,
					pr_reg_p->pr_res_mapped_lun,
					0x2A,
					ASCQ_2AH_RESERVATIONS_RELEASED);
			पूर्ण
		पूर्ण

		spin_unlock(&pr_पंचांगpl->registration_lock);
	पूर्ण

	ret = core_scsi3_update_and_ग_लिखो_aptpl(dev, aptpl);

out:
	अगर (pr_reg)
		core_scsi3_put_pr_reg(pr_reg);
	वापस ret;
पूर्ण

अचिन्हित अक्षर *core_scsi3_pr_dump_type(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल PR_TYPE_WRITE_EXCLUSIVE:
		वापस "Write Exclusive Access";
	हाल PR_TYPE_EXCLUSIVE_ACCESS:
		वापस "Exclusive Access";
	हाल PR_TYPE_WRITE_EXCLUSIVE_REGONLY:
		वापस "Write Exclusive Access, Registrants Only";
	हाल PR_TYPE_EXCLUSIVE_ACCESS_REGONLY:
		वापस "Exclusive Access, Registrants Only";
	हाल PR_TYPE_WRITE_EXCLUSIVE_ALLREG:
		वापस "Write Exclusive Access, All Registrants";
	हाल PR_TYPE_EXCLUSIVE_ACCESS_ALLREG:
		वापस "Exclusive Access, All Registrants";
	शेष:
		अवरोध;
	पूर्ण

	वापस "Unknown SPC-3 PR Type";
पूर्ण

अटल sense_reason_t
core_scsi3_pro_reserve(काष्ठा se_cmd *cmd, पूर्णांक type, पूर्णांक scope, u64 res_key)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_lun *se_lun = cmd->se_lun;
	काष्ठा t10_pr_registration *pr_reg, *pr_res_holder;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	अक्षर i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;
	sense_reason_t ret;

	अगर (!se_sess || !se_lun) अणु
		pr_err("SPC-3 PR: se_sess || struct se_lun is NULL!\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * Locate the existing *pr_reg via काष्ठा se_node_acl poपूर्णांकers
	 */
	pr_reg = core_scsi3_locate_pr_reg(cmd->se_dev, se_sess->se_node_acl,
				se_sess);
	अगर (!pr_reg) अणु
		pr_err("SPC-3 PR: Unable to locate"
			" PR_REGISTERED *pr_reg for RESERVE\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * From spc4r17 Section 5.7.9: Reserving:
	 *
	 * An application client creates a persistent reservation by issuing
	 * a PERSISTENT RESERVE OUT command with RESERVE service action through
	 * a रेजिस्टरed I_T nexus with the following parameters:
	 *    a) RESERVATION KEY set to the value of the reservation key that is
	 * 	 रेजिस्टरed with the logical unit क्रम the I_T nexus; and
	 */
	अगर (res_key != pr_reg->pr_res_key) अणु
		pr_err("SPC-3 PR RESERVE: Received res_key: 0x%016Lx"
			" does not match existing SA REGISTER res_key:"
			" 0x%016Lx\n", res_key, pr_reg->pr_res_key);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out_put_pr_reg;
	पूर्ण
	/*
	 * From spc4r17 Section 5.7.9: Reserving:
	 *
	 * From above:
	 *  b) TYPE field and SCOPE field set to the persistent reservation
	 *     being created.
	 *
	 * Only one persistent reservation is allowed at a समय per logical unit
	 * and that persistent reservation has a scope of LU_SCOPE.
	 */
	अगर (scope != PR_SCOPE_LU_SCOPE) अणु
		pr_err("SPC-3 PR: Illegal SCOPE: 0x%02x\n", scope);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out_put_pr_reg;
	पूर्ण
	/*
	 * See अगर we have an existing PR reservation holder poपूर्णांकer at
	 * काष्ठा se_device->dev_pr_res_holder in the क्रमm काष्ठा t10_pr_registration
	 * *pr_res_holder.
	 */
	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर (pr_res_holder) अणु
		/*
		 * From spc4r17 Section 5.7.9: Reserving:
		 *
		 * If the device server receives a PERSISTENT RESERVE OUT
		 * command from an I_T nexus other than a persistent reservation
		 * holder (see 5.7.10) that attempts to create a persistent
		 * reservation when a persistent reservation alपढ़ोy exists क्रम
		 * the logical unit, then the command shall be completed with
		 * RESERVATION CONFLICT status.
		 */
		अगर (!is_reservation_holder(pr_res_holder, pr_reg)) अणु
			काष्ठा se_node_acl *pr_res_nacl = pr_res_holder->pr_reg_nacl;
			pr_err("SPC-3 PR: Attempted RESERVE from"
				" [%s]: %s while reservation already held by"
				" [%s]: %s, returning RESERVATION_CONFLICT\n",
				cmd->se_tfo->fabric_name,
				se_sess->se_node_acl->initiatorname,
				pr_res_nacl->se_tpg->se_tpg_tfo->fabric_name,
				pr_res_holder->pr_reg_nacl->initiatorname);

			spin_unlock(&dev->dev_reservation_lock);
			ret = TCM_RESERVATION_CONFLICT;
			जाओ out_put_pr_reg;
		पूर्ण
		/*
		 * From spc4r17 Section 5.7.9: Reserving:
		 *
		 * If a persistent reservation holder attempts to modअगरy the
		 * type or scope of an existing persistent reservation, the
		 * command shall be completed with RESERVATION CONFLICT status.
		 */
		अगर ((pr_res_holder->pr_res_type != type) ||
		    (pr_res_holder->pr_res_scope != scope)) अणु
			काष्ठा se_node_acl *pr_res_nacl = pr_res_holder->pr_reg_nacl;
			pr_err("SPC-3 PR: Attempted RESERVE from"
				" [%s]: %s trying to change TYPE and/or SCOPE,"
				" while reservation already held by [%s]: %s,"
				" returning RESERVATION_CONFLICT\n",
				cmd->se_tfo->fabric_name,
				se_sess->se_node_acl->initiatorname,
				pr_res_nacl->se_tpg->se_tpg_tfo->fabric_name,
				pr_res_holder->pr_reg_nacl->initiatorname);

			spin_unlock(&dev->dev_reservation_lock);
			ret = TCM_RESERVATION_CONFLICT;
			जाओ out_put_pr_reg;
		पूर्ण
		/*
		 * From spc4r17 Section 5.7.9: Reserving:
		 *
		 * If the device server receives a PERSISTENT RESERVE OUT
		 * command with RESERVE service action where the TYPE field and
		 * the SCOPE field contain the same values as the existing type
		 * and scope from a persistent reservation holder, it shall not
		 * make any change to the existing persistent reservation and
		 * shall completethe command with GOOD status.
		 */
		spin_unlock(&dev->dev_reservation_lock);
		ret = 0;
		जाओ out_put_pr_reg;
	पूर्ण
	/*
	 * Otherwise, our *pr_reg becomes the PR reservation holder क्रम said
	 * TYPE/SCOPE.  Also set the received scope and type in *pr_reg.
	 */
	pr_reg->pr_res_scope = scope;
	pr_reg->pr_res_type = type;
	pr_reg->pr_res_holder = 1;
	dev->dev_pr_res_holder = pr_reg;
	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);

	pr_debug("SPC-3 PR [%s] Service Action: RESERVE created new"
		" reservation holder TYPE: %s ALL_TG_PT: %d\n",
		cmd->se_tfo->fabric_name, core_scsi3_pr_dump_type(type),
		(pr_reg->pr_reg_all_tg_pt) ? 1 : 0);
	pr_debug("SPC-3 PR [%s] RESERVE Node: %s%s\n",
			cmd->se_tfo->fabric_name,
			se_sess->se_node_acl->initiatorname,
			i_buf);
	spin_unlock(&dev->dev_reservation_lock);

	अगर (pr_पंचांगpl->pr_aptpl_active)
		core_scsi3_update_and_ग_लिखो_aptpl(cmd->se_dev, true);

	ret = 0;
out_put_pr_reg:
	core_scsi3_put_pr_reg(pr_reg);
	वापस ret;
पूर्ण

अटल sense_reason_t
core_scsi3_emulate_pro_reserve(काष्ठा se_cmd *cmd, पूर्णांक type, पूर्णांक scope,
		u64 res_key)
अणु
	चयन (type) अणु
	हाल PR_TYPE_WRITE_EXCLUSIVE:
	हाल PR_TYPE_EXCLUSIVE_ACCESS:
	हाल PR_TYPE_WRITE_EXCLUSIVE_REGONLY:
	हाल PR_TYPE_EXCLUSIVE_ACCESS_REGONLY:
	हाल PR_TYPE_WRITE_EXCLUSIVE_ALLREG:
	हाल PR_TYPE_EXCLUSIVE_ACCESS_ALLREG:
		वापस core_scsi3_pro_reserve(cmd, type, scope, res_key);
	शेष:
		pr_err("SPC-3 PR: Unknown Service Action RESERVE Type:"
			" 0x%02x\n", type);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण
पूर्ण

अटल व्योम __core_scsi3_complete_pro_release(
	काष्ठा se_device *dev,
	काष्ठा se_node_acl *se_nacl,
	काष्ठा t10_pr_registration *pr_reg,
	पूर्णांक explicit,
	पूर्णांक unreg)
अणु
	स्थिर काष्ठा target_core_fabric_ops *tfo = se_nacl->se_tpg->se_tpg_tfo;
	अक्षर i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;
	पूर्णांक pr_res_type = 0, pr_res_scope = 0;

	lockdep_निश्चित_held(&dev->dev_reservation_lock);

	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);
	/*
	 * Go ahead and release the current PR reservation holder.
	 * If an All Registrants reservation is currently active and
	 * a unरेजिस्टर operation is requested, replace the current
	 * dev_pr_res_holder with another active registration.
	 */
	अगर (dev->dev_pr_res_holder) अणु
		pr_res_type = dev->dev_pr_res_holder->pr_res_type;
		pr_res_scope = dev->dev_pr_res_holder->pr_res_scope;
		dev->dev_pr_res_holder->pr_res_type = 0;
		dev->dev_pr_res_holder->pr_res_scope = 0;
		dev->dev_pr_res_holder->pr_res_holder = 0;
		dev->dev_pr_res_holder = शून्य;
	पूर्ण
	अगर (!unreg)
		जाओ out;

	spin_lock(&dev->t10_pr.registration_lock);
	list_del_init(&pr_reg->pr_reg_list);
	/*
	 * If the I_T nexus is a reservation holder, the persistent reservation
	 * is of an all registrants type, and the I_T nexus is the last reमुख्यing
	 * रेजिस्टरed I_T nexus, then the device server shall also release the
	 * persistent reservation.
	 */
	अगर (!list_empty(&dev->t10_pr.registration_list) &&
	    ((pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG) ||
	     (pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG))) अणु
		dev->dev_pr_res_holder =
			list_entry(dev->t10_pr.registration_list.next,
				   काष्ठा t10_pr_registration, pr_reg_list);
		dev->dev_pr_res_holder->pr_res_type = pr_res_type;
		dev->dev_pr_res_holder->pr_res_scope = pr_res_scope;
		dev->dev_pr_res_holder->pr_res_holder = 1;
	पूर्ण
	spin_unlock(&dev->t10_pr.registration_lock);
out:
	अगर (!dev->dev_pr_res_holder) अणु
		pr_debug("SPC-3 PR [%s] Service Action: %s RELEASE cleared"
			" reservation holder TYPE: %s ALL_TG_PT: %d\n",
			tfo->fabric_name, (explicit) ? "explicit" :
			"implicit", core_scsi3_pr_dump_type(pr_res_type),
			(pr_reg->pr_reg_all_tg_pt) ? 1 : 0);
	पूर्ण
	pr_debug("SPC-3 PR [%s] RELEASE Node: %s%s\n",
		tfo->fabric_name, se_nacl->initiatorname,
		i_buf);
	/*
	 * Clear TYPE and SCOPE क्रम the next PROUT Service Action: RESERVE
	 */
	pr_reg->pr_res_holder = pr_reg->pr_res_type = pr_reg->pr_res_scope = 0;
पूर्ण

अटल sense_reason_t
core_scsi3_emulate_pro_release(काष्ठा se_cmd *cmd, पूर्णांक type, पूर्णांक scope,
		u64 res_key)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_lun *se_lun = cmd->se_lun;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_p, *pr_res_holder;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	sense_reason_t ret = 0;

	अगर (!se_sess || !se_lun) अणु
		pr_err("SPC-3 PR: se_sess || struct se_lun is NULL!\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * Locate the existing *pr_reg via काष्ठा se_node_acl poपूर्णांकers
	 */
	pr_reg = core_scsi3_locate_pr_reg(dev, se_sess->se_node_acl, se_sess);
	अगर (!pr_reg) अणु
		pr_err("SPC-3 PR: Unable to locate"
			" PR_REGISTERED *pr_reg for RELEASE\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * From spc4r17 Section 5.7.11.2 Releasing:
	 *
	 * If there is no persistent reservation or in response to a persistent
	 * reservation release request from a रेजिस्टरed I_T nexus that is not a
	 * persistent reservation holder (see 5.7.10), the device server shall
	 * करो the following:
	 *
	 *     a) Not release the persistent reservation, अगर any;
	 *     b) Not हटाओ any registrations; and
	 *     c) Complete the command with GOOD status.
	 */
	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर (!pr_res_holder) अणु
		/*
		 * No persistent reservation, वापस GOOD status.
		 */
		spin_unlock(&dev->dev_reservation_lock);
		जाओ out_put_pr_reg;
	पूर्ण

	अगर (!is_reservation_holder(pr_res_holder, pr_reg)) अणु
		/*
		 * Release request from a रेजिस्टरed I_T nexus that is not a
		 * persistent reservation holder. वापस GOOD status.
		 */
		spin_unlock(&dev->dev_reservation_lock);
		जाओ out_put_pr_reg;
	पूर्ण

	/*
	 * From spc4r17 Section 5.7.11.2 Releasing:
	 *
	 * Only the persistent reservation holder (see 5.7.10) is allowed to
	 * release a persistent reservation.
	 *
	 * An application client releases the persistent reservation by issuing
	 * a PERSISTENT RESERVE OUT command with RELEASE service action through
	 * an I_T nexus that is a persistent reservation holder with the
	 * following parameters:
	 *
	 *     a) RESERVATION KEY field set to the value of the reservation key
	 *	  that is रेजिस्टरed with the logical unit क्रम the I_T nexus;
	 */
	अगर (res_key != pr_reg->pr_res_key) अणु
		pr_err("SPC-3 PR RELEASE: Received res_key: 0x%016Lx"
			" does not match existing SA REGISTER res_key:"
			" 0x%016Lx\n", res_key, pr_reg->pr_res_key);
		spin_unlock(&dev->dev_reservation_lock);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out_put_pr_reg;
	पूर्ण
	/*
	 * From spc4r17 Section 5.7.11.2 Releasing and above:
	 *
	 * b) TYPE field and SCOPE field set to match the persistent
	 *    reservation being released.
	 */
	अगर ((pr_res_holder->pr_res_type != type) ||
	    (pr_res_holder->pr_res_scope != scope)) अणु
		काष्ठा se_node_acl *pr_res_nacl = pr_res_holder->pr_reg_nacl;
		pr_err("SPC-3 PR RELEASE: Attempted to release"
			" reservation from [%s]: %s with different TYPE "
			"and/or SCOPE  while reservation already held by"
			" [%s]: %s, returning RESERVATION_CONFLICT\n",
			cmd->se_tfo->fabric_name,
			se_sess->se_node_acl->initiatorname,
			pr_res_nacl->se_tpg->se_tpg_tfo->fabric_name,
			pr_res_holder->pr_reg_nacl->initiatorname);

		spin_unlock(&dev->dev_reservation_lock);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out_put_pr_reg;
	पूर्ण
	/*
	 * In response to a persistent reservation release request from the
	 * persistent reservation holder the device server shall perक्रमm a
	 * release by करोing the following as an unपूर्णांकerrupted series of actions:
	 * a) Release the persistent reservation;
	 * b) Not हटाओ any registration(s);
	 * c) If the released persistent reservation is a registrants only type
	 * or all registrants type persistent reservation,
	 *    the device server shall establish a unit attention condition क्रम
	 *    the initiator port associated with every regis-
	 *    tered I_T nexus other than I_T nexus on which the PERSISTENT
	 *    RESERVE OUT command with RELEASE service action was received,
	 *    with the additional sense code set to RESERVATIONS RELEASED; and
	 * d) If the persistent reservation is of any other type, the device
	 *    server shall not establish a unit attention condition.
	 */
	__core_scsi3_complete_pro_release(dev, se_sess->se_node_acl,
					  pr_reg, 1, 0);

	spin_unlock(&dev->dev_reservation_lock);

	अगर ((type != PR_TYPE_WRITE_EXCLUSIVE_REGONLY) &&
	    (type != PR_TYPE_EXCLUSIVE_ACCESS_REGONLY) &&
	    (type != PR_TYPE_WRITE_EXCLUSIVE_ALLREG) &&
	    (type != PR_TYPE_EXCLUSIVE_ACCESS_ALLREG)) अणु
		/*
		 * If no UNIT ATTENTION conditions will be established क्रम
		 * PR_TYPE_WRITE_EXCLUSIVE or PR_TYPE_EXCLUSIVE_ACCESS
		 * go ahead and check क्रम APTPL=1 update+ग_लिखो below
		 */
		जाओ ग_लिखो_aptpl;
	पूर्ण

	spin_lock(&pr_पंचांगpl->registration_lock);
	list_क्रम_each_entry(pr_reg_p, &pr_पंचांगpl->registration_list,
			pr_reg_list) अणु
		/*
		 * Do not establish a UNIT ATTENTION condition
		 * क्रम the calling I_T Nexus
		 */
		अगर (pr_reg_p == pr_reg)
			जारी;

		target_ua_allocate_lun(pr_reg_p->pr_reg_nacl,
				pr_reg_p->pr_res_mapped_lun,
				0x2A, ASCQ_2AH_RESERVATIONS_RELEASED);
	पूर्ण
	spin_unlock(&pr_पंचांगpl->registration_lock);

ग_लिखो_aptpl:
	अगर (pr_पंचांगpl->pr_aptpl_active)
		core_scsi3_update_and_ग_लिखो_aptpl(cmd->se_dev, true);

out_put_pr_reg:
	core_scsi3_put_pr_reg(pr_reg);
	वापस ret;
पूर्ण

अटल sense_reason_t
core_scsi3_emulate_pro_clear(काष्ठा se_cmd *cmd, u64 res_key)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_node_acl *pr_reg_nacl;
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp, *pr_reg_n, *pr_res_holder;
	u64 pr_res_mapped_lun = 0;
	पूर्णांक calling_it_nexus = 0;
	/*
	 * Locate the existing *pr_reg via काष्ठा se_node_acl poपूर्णांकers
	 */
	pr_reg_n = core_scsi3_locate_pr_reg(cmd->se_dev,
			se_sess->se_node_acl, se_sess);
	अगर (!pr_reg_n) अणु
		pr_err("SPC-3 PR: Unable to locate"
			" PR_REGISTERED *pr_reg for CLEAR\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * From spc4r17 section 5.7.11.6, Clearing:
	 *
	 * Any application client may release the persistent reservation and
	 * हटाओ all registrations from a device server by issuing a
	 * PERSISTENT RESERVE OUT command with CLEAR service action through a
	 * रेजिस्टरed I_T nexus with the following parameter:
	 *
	 *	a) RESERVATION KEY field set to the value of the reservation key
	 * 	   that is रेजिस्टरed with the logical unit क्रम the I_T nexus.
	 */
	अगर (res_key != pr_reg_n->pr_res_key) अणु
		pr_err("SPC-3 PR REGISTER: Received"
			" res_key: 0x%016Lx does not match"
			" existing SA REGISTER res_key:"
			" 0x%016Lx\n", res_key, pr_reg_n->pr_res_key);
		core_scsi3_put_pr_reg(pr_reg_n);
		वापस TCM_RESERVATION_CONFLICT;
	पूर्ण
	/*
	 * a) Release the persistent reservation, अगर any;
	 */
	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर (pr_res_holder) अणु
		काष्ठा se_node_acl *pr_res_nacl = pr_res_holder->pr_reg_nacl;
		__core_scsi3_complete_pro_release(dev, pr_res_nacl,
						  pr_res_holder, 0, 0);
	पूर्ण
	spin_unlock(&dev->dev_reservation_lock);
	/*
	 * b) Remove all registration(s) (see spc4r17 5.7.7);
	 */
	spin_lock(&pr_पंचांगpl->registration_lock);
	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
			&pr_पंचांगpl->registration_list, pr_reg_list) अणु

		calling_it_nexus = (pr_reg_n == pr_reg) ? 1 : 0;
		pr_reg_nacl = pr_reg->pr_reg_nacl;
		pr_res_mapped_lun = pr_reg->pr_res_mapped_lun;
		__core_scsi3_मुक्त_registration(dev, pr_reg, शून्य,
					calling_it_nexus);
		/*
		 * e) Establish a unit attention condition क्रम the initiator
		 *    port associated with every रेजिस्टरed I_T nexus other
		 *    than the I_T nexus on which the PERSISTENT RESERVE OUT
		 *    command with CLEAR service action was received, with the
		 *    additional sense code set to RESERVATIONS PREEMPTED.
		 */
		अगर (!calling_it_nexus)
			target_ua_allocate_lun(pr_reg_nacl, pr_res_mapped_lun,
				0x2A, ASCQ_2AH_RESERVATIONS_PREEMPTED);
	पूर्ण
	spin_unlock(&pr_पंचांगpl->registration_lock);

	pr_debug("SPC-3 PR [%s] Service Action: CLEAR complete\n",
		cmd->se_tfo->fabric_name);

	core_scsi3_update_and_ग_लिखो_aptpl(cmd->se_dev, false);

	core_scsi3_pr_generation(dev);
	वापस 0;
पूर्ण

अटल व्योम __core_scsi3_complete_pro_preempt(
	काष्ठा se_device *dev,
	काष्ठा t10_pr_registration *pr_reg,
	काष्ठा list_head *preempt_and_पात_list,
	पूर्णांक type,
	पूर्णांक scope,
	क्रमागत preempt_type preempt_type)
अणु
	काष्ठा se_node_acl *nacl = pr_reg->pr_reg_nacl;
	स्थिर काष्ठा target_core_fabric_ops *tfo = nacl->se_tpg->se_tpg_tfo;
	अक्षर i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;

	lockdep_निश्चित_held(&dev->dev_reservation_lock);

	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);
	/*
	 * Do an implicit RELEASE of the existing reservation.
	 */
	अगर (dev->dev_pr_res_holder)
		__core_scsi3_complete_pro_release(dev, nacl,
						  dev->dev_pr_res_holder, 0, 0);

	dev->dev_pr_res_holder = pr_reg;
	pr_reg->pr_res_holder = 1;
	pr_reg->pr_res_type = type;
	pr_reg->pr_res_scope = scope;

	pr_debug("SPC-3 PR [%s] Service Action: PREEMPT%s created new"
		" reservation holder TYPE: %s ALL_TG_PT: %d\n",
		tfo->fabric_name, (preempt_type == PREEMPT_AND_ABORT) ? "_AND_ABORT" : "",
		core_scsi3_pr_dump_type(type),
		(pr_reg->pr_reg_all_tg_pt) ? 1 : 0);
	pr_debug("SPC-3 PR [%s] PREEMPT%s from Node: %s%s\n",
		tfo->fabric_name, (preempt_type == PREEMPT_AND_ABORT) ? "_AND_ABORT" : "",
		nacl->initiatorname, i_buf);
	/*
	 * For PREEMPT_AND_ABORT, add the preempting reservation's
	 * काष्ठा t10_pr_registration to the list that will be compared
	 * against received CDBs..
	 */
	अगर (preempt_and_पात_list)
		list_add_tail(&pr_reg->pr_reg_पात_list,
				preempt_and_पात_list);
पूर्ण

अटल व्योम core_scsi3_release_preempt_and_पात(
	काष्ठा list_head *preempt_and_पात_list,
	काष्ठा t10_pr_registration *pr_reg_holder)
अणु
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp;

	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp, preempt_and_पात_list,
				pr_reg_पात_list) अणु

		list_del(&pr_reg->pr_reg_पात_list);
		अगर (pr_reg_holder == pr_reg)
			जारी;
		अगर (pr_reg->pr_res_holder) अणु
			pr_warn("pr_reg->pr_res_holder still set\n");
			जारी;
		पूर्ण

		pr_reg->pr_reg_deve = शून्य;
		pr_reg->pr_reg_nacl = शून्य;
		kmem_cache_मुक्त(t10_pr_reg_cache, pr_reg);
	पूर्ण
पूर्ण

अटल sense_reason_t
core_scsi3_pro_preempt(काष्ठा se_cmd *cmd, पूर्णांक type, पूर्णांक scope, u64 res_key,
		u64 sa_res_key, क्रमागत preempt_type preempt_type)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_node_acl *pr_reg_nacl;
	काष्ठा se_session *se_sess = cmd->se_sess;
	LIST_HEAD(preempt_and_पात_list);
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp, *pr_reg_n, *pr_res_holder;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	u64 pr_res_mapped_lun = 0;
	पूर्णांक all_reg = 0, calling_it_nexus = 0;
	bool sa_res_key_unmatched = sa_res_key != 0;
	पूर्णांक prh_type = 0, prh_scope = 0;

	अगर (!se_sess)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	pr_reg_n = core_scsi3_locate_pr_reg(cmd->se_dev, se_sess->se_node_acl,
				se_sess);
	अगर (!pr_reg_n) अणु
		pr_err("SPC-3 PR: Unable to locate"
			" PR_REGISTERED *pr_reg for PREEMPT%s\n",
			(preempt_type == PREEMPT_AND_ABORT) ? "_AND_ABORT" : "");
		वापस TCM_RESERVATION_CONFLICT;
	पूर्ण
	अगर (pr_reg_n->pr_res_key != res_key) अणु
		core_scsi3_put_pr_reg(pr_reg_n);
		वापस TCM_RESERVATION_CONFLICT;
	पूर्ण
	अगर (scope != PR_SCOPE_LU_SCOPE) अणु
		pr_err("SPC-3 PR: Illegal SCOPE: 0x%02x\n", scope);
		core_scsi3_put_pr_reg(pr_reg_n);
		वापस TCM_INVALID_PARAMETER_LIST;
	पूर्ण

	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर (pr_res_holder &&
	   ((pr_res_holder->pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG) ||
	    (pr_res_holder->pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG)))
		all_reg = 1;

	अगर (!all_reg && !sa_res_key) अणु
		spin_unlock(&dev->dev_reservation_lock);
		core_scsi3_put_pr_reg(pr_reg_n);
		वापस TCM_INVALID_PARAMETER_LIST;
	पूर्ण
	/*
	 * From spc4r17, section 5.7.11.4.4 Removing Registrations:
	 *
	 * If the SERVICE ACTION RESERVATION KEY field करोes not identअगरy a
	 * persistent reservation holder or there is no persistent reservation
	 * holder (i.e., there is no persistent reservation), then the device
	 * server shall perक्रमm a preempt by करोing the following in an
	 * unपूर्णांकerrupted series of actions. (See below..)
	 */
	अगर (!pr_res_holder || (pr_res_holder->pr_res_key != sa_res_key)) अणु
		/*
		 * No existing or SA Reservation Key matching reservations..
		 *
		 * PROUT SA PREEMPT with All Registrant type reservations are
		 * allowed to be processed without a matching SA Reservation Key
		 */
		spin_lock(&pr_पंचांगpl->registration_lock);
		list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
				&pr_पंचांगpl->registration_list, pr_reg_list) अणु
			/*
			 * Removing of registrations in non all registrants
			 * type reservations without a matching SA reservation
			 * key.
			 *
			 * a) Remove the registrations क्रम all I_T nexuses
			 *    specअगरied by the SERVICE ACTION RESERVATION KEY
			 *    field;
			 * b) Ignore the contents of the SCOPE and TYPE fields;
			 * c) Process tasks as defined in 5.7.1; and
			 * d) Establish a unit attention condition क्रम the
			 *    initiator port associated with every I_T nexus
			 *    that lost its registration other than the I_T
			 *    nexus on which the PERSISTENT RESERVE OUT command
			 *    was received, with the additional sense code set
			 *    to REGISTRATIONS PREEMPTED.
			 */
			अगर (!all_reg) अणु
				अगर (pr_reg->pr_res_key != sa_res_key)
					जारी;
				sa_res_key_unmatched = false;

				calling_it_nexus = (pr_reg_n == pr_reg) ? 1 : 0;
				pr_reg_nacl = pr_reg->pr_reg_nacl;
				pr_res_mapped_lun = pr_reg->pr_res_mapped_lun;
				__core_scsi3_मुक्त_registration(dev, pr_reg,
					(preempt_type == PREEMPT_AND_ABORT) ? &preempt_and_पात_list :
						शून्य, calling_it_nexus);
			पूर्ण अन्यथा अणु
				/*
				 * Case क्रम any existing all registrants type
				 * reservation, follow logic in spc4r17 section
				 * 5.7.11.4 Preempting, Table 52 and Figure 7.
				 *
				 * For a ZERO SA Reservation key, release
				 * all other registrations and करो an implicit
				 * release of active persistent reservation.
				 *
				 * For a non-ZERO SA Reservation key, only
				 * release the matching reservation key from
				 * registrations.
				 */
				अगर ((sa_res_key) &&
				     (pr_reg->pr_res_key != sa_res_key))
					जारी;
				sa_res_key_unmatched = false;

				calling_it_nexus = (pr_reg_n == pr_reg) ? 1 : 0;
				अगर (calling_it_nexus)
					जारी;

				pr_reg_nacl = pr_reg->pr_reg_nacl;
				pr_res_mapped_lun = pr_reg->pr_res_mapped_lun;
				__core_scsi3_मुक्त_registration(dev, pr_reg,
					(preempt_type == PREEMPT_AND_ABORT) ? &preempt_and_पात_list :
						शून्य, 0);
			पूर्ण
			अगर (!calling_it_nexus)
				target_ua_allocate_lun(pr_reg_nacl,
					pr_res_mapped_lun, 0x2A,
					ASCQ_2AH_REGISTRATIONS_PREEMPTED);
		पूर्ण
		spin_unlock(&pr_पंचांगpl->registration_lock);
		/*
		 * If a PERSISTENT RESERVE OUT with a PREEMPT service action or
		 * a PREEMPT AND ABORT service action sets the SERVICE ACTION
		 * RESERVATION KEY field to a value that करोes not match any
		 * रेजिस्टरed reservation key, then the device server shall
		 * complete the command with RESERVATION CONFLICT status.
		 */
		अगर (sa_res_key_unmatched) अणु
			spin_unlock(&dev->dev_reservation_lock);
			core_scsi3_put_pr_reg(pr_reg_n);
			वापस TCM_RESERVATION_CONFLICT;
		पूर्ण
		/*
		 * For an existing all registrants type reservation
		 * with a zero SA rservation key, preempt the existing
		 * reservation with the new PR type and scope.
		 */
		अगर (pr_res_holder && all_reg && !(sa_res_key)) अणु
			__core_scsi3_complete_pro_preempt(dev, pr_reg_n,
				(preempt_type == PREEMPT_AND_ABORT) ? &preempt_and_पात_list : शून्य,
				type, scope, preempt_type);

			अगर (preempt_type == PREEMPT_AND_ABORT)
				core_scsi3_release_preempt_and_पात(
					&preempt_and_पात_list, pr_reg_n);
		पूर्ण
		spin_unlock(&dev->dev_reservation_lock);

		अगर (pr_पंचांगpl->pr_aptpl_active)
			core_scsi3_update_and_ग_लिखो_aptpl(cmd->se_dev, true);

		core_scsi3_put_pr_reg(pr_reg_n);
		core_scsi3_pr_generation(cmd->se_dev);
		वापस 0;
	पूर्ण
	/*
	 * The PREEMPTing SA reservation key matches that of the
	 * existing persistent reservation, first, we check अगर
	 * we are preempting our own reservation.
	 * From spc4r17, section 5.7.11.4.3 Preempting
	 * persistent reservations and registration handling
	 *
	 * If an all registrants persistent reservation is not
	 * present, it is not an error क्रम the persistent
	 * reservation holder to preempt itself (i.e., a
	 * PERSISTENT RESERVE OUT with a PREEMPT service action
	 * or a PREEMPT AND ABORT service action with the
	 * SERVICE ACTION RESERVATION KEY value equal to the
	 * persistent reservation holder's reservation key that
	 * is received from the persistent reservation holder).
	 * In that हाल, the device server shall establish the
	 * new persistent reservation and मुख्यtain the
	 * registration.
	 */
	prh_type = pr_res_holder->pr_res_type;
	prh_scope = pr_res_holder->pr_res_scope;
	/*
	 * If the SERVICE ACTION RESERVATION KEY field identअगरies a
	 * persistent reservation holder (see 5.7.10), the device
	 * server shall perक्रमm a preempt by करोing the following as
	 * an unपूर्णांकerrupted series of actions:
	 *
	 * a) Release the persistent reservation क्रम the holder
	 *    identअगरied by the SERVICE ACTION RESERVATION KEY field;
	 */
	अगर (pr_reg_n != pr_res_holder)
		__core_scsi3_complete_pro_release(dev,
						  pr_res_holder->pr_reg_nacl,
						  dev->dev_pr_res_holder, 0, 0);
	/*
	 * b) Remove the registrations क्रम all I_T nexuses identअगरied
	 *    by the SERVICE ACTION RESERVATION KEY field, except the
	 *    I_T nexus that is being used क्रम the PERSISTENT RESERVE
	 *    OUT command. If an all registrants persistent reservation
	 *    is present and the SERVICE ACTION RESERVATION KEY field
	 *    is set to zero, then all registrations shall be हटाओd
	 *    except क्रम that of the I_T nexus that is being used क्रम
	 *    the PERSISTENT RESERVE OUT command;
	 */
	spin_lock(&pr_पंचांगpl->registration_lock);
	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
			&pr_पंचांगpl->registration_list, pr_reg_list) अणु

		calling_it_nexus = (pr_reg_n == pr_reg) ? 1 : 0;
		अगर (calling_it_nexus)
			जारी;

		अगर (pr_reg->pr_res_key != sa_res_key)
			जारी;

		pr_reg_nacl = pr_reg->pr_reg_nacl;
		pr_res_mapped_lun = pr_reg->pr_res_mapped_lun;
		__core_scsi3_मुक्त_registration(dev, pr_reg,
				(preempt_type == PREEMPT_AND_ABORT) ? &preempt_and_पात_list : शून्य,
				calling_it_nexus);
		/*
		 * e) Establish a unit attention condition क्रम the initiator
		 *    port associated with every I_T nexus that lost its
		 *    persistent reservation and/or registration, with the
		 *    additional sense code set to REGISTRATIONS PREEMPTED;
		 */
		target_ua_allocate_lun(pr_reg_nacl, pr_res_mapped_lun, 0x2A,
				ASCQ_2AH_REGISTRATIONS_PREEMPTED);
	पूर्ण
	spin_unlock(&pr_पंचांगpl->registration_lock);
	/*
	 * c) Establish a persistent reservation क्रम the preempting
	 *    I_T nexus using the contents of the SCOPE and TYPE fields;
	 */
	__core_scsi3_complete_pro_preempt(dev, pr_reg_n,
			(preempt_type == PREEMPT_AND_ABORT) ? &preempt_and_पात_list : शून्य,
			type, scope, preempt_type);
	/*
	 * d) Process tasks as defined in 5.7.1;
	 * e) See above..
	 * f) If the type or scope has changed, then क्रम every I_T nexus
	 *    whose reservation key was not हटाओd, except क्रम the I_T
	 *    nexus on which the PERSISTENT RESERVE OUT command was
	 *    received, the device server shall establish a unit
	 *    attention condition क्रम the initiator port associated with
	 *    that I_T nexus, with the additional sense code set to
	 *    RESERVATIONS RELEASED. If the type or scope have not
	 *    changed, then no unit attention condition(s) shall be
	 *    established क्रम this reason.
	 */
	अगर ((prh_type != type) || (prh_scope != scope)) अणु
		spin_lock(&pr_पंचांगpl->registration_lock);
		list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
				&pr_पंचांगpl->registration_list, pr_reg_list) अणु

			calling_it_nexus = (pr_reg_n == pr_reg) ? 1 : 0;
			अगर (calling_it_nexus)
				जारी;

			target_ua_allocate_lun(pr_reg->pr_reg_nacl,
					pr_reg->pr_res_mapped_lun, 0x2A,
					ASCQ_2AH_RESERVATIONS_RELEASED);
		पूर्ण
		spin_unlock(&pr_पंचांगpl->registration_lock);
	पूर्ण
	spin_unlock(&dev->dev_reservation_lock);
	/*
	 * Call LUN_RESET logic upon list of काष्ठा t10_pr_registration,
	 * All received CDBs क्रम the matching existing reservation and
	 * registrations undergo ABORT_TASK logic.
	 *
	 * From there, core_scsi3_release_preempt_and_पात() will
	 * release every registration in the list (which have alपढ़ोy
	 * been हटाओd from the primary pr_reg list), except the
	 * new persistent reservation holder, the calling Initiator Port.
	 */
	अगर (preempt_type == PREEMPT_AND_ABORT) अणु
		core_पंचांगr_lun_reset(dev, शून्य, &preempt_and_पात_list, cmd);
		core_scsi3_release_preempt_and_पात(&preempt_and_पात_list,
						pr_reg_n);
	पूर्ण

	अगर (pr_पंचांगpl->pr_aptpl_active)
		core_scsi3_update_and_ग_लिखो_aptpl(cmd->se_dev, true);

	core_scsi3_put_pr_reg(pr_reg_n);
	core_scsi3_pr_generation(cmd->se_dev);
	वापस 0;
पूर्ण

अटल sense_reason_t
core_scsi3_emulate_pro_preempt(काष्ठा se_cmd *cmd, पूर्णांक type, पूर्णांक scope,
		u64 res_key, u64 sa_res_key, क्रमागत preempt_type preempt_type)
अणु
	चयन (type) अणु
	हाल PR_TYPE_WRITE_EXCLUSIVE:
	हाल PR_TYPE_EXCLUSIVE_ACCESS:
	हाल PR_TYPE_WRITE_EXCLUSIVE_REGONLY:
	हाल PR_TYPE_EXCLUSIVE_ACCESS_REGONLY:
	हाल PR_TYPE_WRITE_EXCLUSIVE_ALLREG:
	हाल PR_TYPE_EXCLUSIVE_ACCESS_ALLREG:
		वापस core_scsi3_pro_preempt(cmd, type, scope, res_key,
					      sa_res_key, preempt_type);
	शेष:
		pr_err("SPC-3 PR: Unknown Service Action PREEMPT%s"
			" Type: 0x%02x\n", (preempt_type == PREEMPT_AND_ABORT) ? "_AND_ABORT" : "", type);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण
पूर्ण


अटल sense_reason_t
core_scsi3_emulate_pro_रेजिस्टर_and_move(काष्ठा se_cmd *cmd, u64 res_key,
		u64 sa_res_key, पूर्णांक aptpl, पूर्णांक unreg)
अणु
	काष्ठा se_session *se_sess = cmd->se_sess;
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_dev_entry *dest_se_deve = शून्य;
	काष्ठा se_lun *se_lun = cmd->se_lun, *पंचांगp_lun;
	काष्ठा se_node_acl *pr_res_nacl, *pr_reg_nacl, *dest_node_acl = शून्य;
	काष्ठा se_portal_group *se_tpg, *dest_se_tpg = शून्य;
	स्थिर काष्ठा target_core_fabric_ops *dest_tf_ops = शून्य, *tf_ops;
	काष्ठा t10_pr_registration *pr_reg, *pr_res_holder, *dest_pr_reg;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	अचिन्हित अक्षर *buf;
	स्थिर अचिन्हित अक्षर *initiator_str;
	अक्षर *iport_ptr = शून्य, i_buf[PR_REG_ISID_ID_LEN] = अणु पूर्ण;
	u32 tid_len, पंचांगp_tid_len;
	पूर्णांक new_reg = 0, type, scope, matching_iname;
	sense_reason_t ret;
	अचिन्हित लघु rtpi;
	अचिन्हित अक्षर proto_ident;

	अगर (!se_sess || !se_lun) अणु
		pr_err("SPC-3 PR: se_sess || struct se_lun is NULL!\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण

	se_tpg = se_sess->se_tpg;
	tf_ops = se_tpg->se_tpg_tfo;
	/*
	 * Follow logic from spc4r17 Section 5.7.8, Table 50 --
	 *	Register behaviors क्रम a REGISTER AND MOVE service action
	 *
	 * Locate the existing *pr_reg via काष्ठा se_node_acl poपूर्णांकers
	 */
	pr_reg = core_scsi3_locate_pr_reg(cmd->se_dev, se_sess->se_node_acl,
				se_sess);
	अगर (!pr_reg) अणु
		pr_err("SPC-3 PR: Unable to locate PR_REGISTERED"
			" *pr_reg for REGISTER_AND_MOVE\n");
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
	पूर्ण
	/*
	 * The provided reservation key much match the existing reservation key
	 * provided during this initiator's I_T nexus registration.
	 */
	अगर (res_key != pr_reg->pr_res_key) अणु
		pr_warn("SPC-3 PR REGISTER_AND_MOVE: Received"
			" res_key: 0x%016Lx does not match existing SA REGISTER"
			" res_key: 0x%016Lx\n", res_key, pr_reg->pr_res_key);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out_put_pr_reg;
	पूर्ण
	/*
	 * The service active reservation key needs to be non zero
	 */
	अगर (!sa_res_key) अणु
		pr_warn("SPC-3 PR REGISTER_AND_MOVE: Received zero"
			" sa_res_key\n");
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out_put_pr_reg;
	पूर्ण

	/*
	 * Determine the Relative Target Port Identअगरier where the reservation
	 * will be moved to क्रम the TransportID containing SCSI initiator WWN
	 * inक्रमmation.
	 */
	buf = transport_kmap_data_sg(cmd);
	अगर (!buf) अणु
		ret = TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
		जाओ out_put_pr_reg;
	पूर्ण

	rtpi = get_unaligned_be16(&buf[18]);
	tid_len = get_unaligned_be32(&buf[20]);
	transport_kunmap_data_sg(cmd);
	buf = शून्य;

	अगर ((tid_len + 24) != cmd->data_length) अणु
		pr_err("SPC-3 PR: Illegal tid_len: %u + 24 byte header"
			" does not equal CDB data_length: %u\n", tid_len,
			cmd->data_length);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out_put_pr_reg;
	पूर्ण

	spin_lock(&dev->se_port_lock);
	list_क्रम_each_entry(पंचांगp_lun, &dev->dev_sep_list, lun_dev_link) अणु
		अगर (पंचांगp_lun->lun_rtpi != rtpi)
			जारी;
		dest_se_tpg = पंचांगp_lun->lun_tpg;
		dest_tf_ops = dest_se_tpg->se_tpg_tfo;
		अगर (!dest_tf_ops)
			जारी;

		atomic_inc_mb(&dest_se_tpg->tpg_pr_ref_count);
		spin_unlock(&dev->se_port_lock);

		अगर (core_scsi3_tpg_depend_item(dest_se_tpg)) अणु
			pr_err("core_scsi3_tpg_depend_item() failed"
				" for dest_se_tpg\n");
			atomic_dec_mb(&dest_se_tpg->tpg_pr_ref_count);
			ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
			जाओ out_put_pr_reg;
		पूर्ण

		spin_lock(&dev->se_port_lock);
		अवरोध;
	पूर्ण
	spin_unlock(&dev->se_port_lock);

	अगर (!dest_se_tpg || !dest_tf_ops) अणु
		pr_err("SPC-3 PR REGISTER_AND_MOVE: Unable to locate"
			" fabric ops from Relative Target Port Identifier:"
			" %hu\n", rtpi);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out_put_pr_reg;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf) अणु
		ret = TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
		जाओ out_put_pr_reg;
	पूर्ण
	proto_ident = (buf[24] & 0x0f);

	pr_debug("SPC-3 PR REGISTER_AND_MOVE: Extracted Protocol Identifier:"
			" 0x%02x\n", proto_ident);

	अगर (proto_ident != dest_se_tpg->proto_id) अणु
		pr_err("SPC-3 PR REGISTER_AND_MOVE: Received"
			" proto_ident: 0x%02x does not match ident: 0x%02x"
			" from fabric: %s\n", proto_ident,
			dest_se_tpg->proto_id,
			dest_tf_ops->fabric_name);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण
	initiator_str = target_parse_pr_out_transport_id(dest_se_tpg,
			&buf[24], &पंचांगp_tid_len, &iport_ptr);
	अगर (!initiator_str) अणु
		pr_err("SPC-3 PR REGISTER_AND_MOVE: Unable to locate"
			" initiator_str from Transport ID\n");
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण

	transport_kunmap_data_sg(cmd);
	buf = शून्य;

	pr_debug("SPC-3 PR [%s] Extracted initiator %s identifier: %s"
		" %s\n", dest_tf_ops->fabric_name, (iport_ptr != शून्य) ?
		"port" : "device", initiator_str, (iport_ptr != शून्य) ?
		iport_ptr : "");
	/*
	 * If a PERSISTENT RESERVE OUT command with a REGISTER AND MOVE service
	 * action specअगरies a TransportID that is the same as the initiator port
	 * of the I_T nexus क्रम the command received, then the command shall
	 * be terminated with CHECK CONDITION status, with the sense key set to
	 * ILLEGAL REQUEST, and the additional sense code set to INVALID FIELD
	 * IN PARAMETER LIST.
	 */
	pr_reg_nacl = pr_reg->pr_reg_nacl;
	matching_iname = (!म_भेद(initiator_str,
				  pr_reg_nacl->initiatorname)) ? 1 : 0;
	अगर (!matching_iname)
		जाओ after_iport_check;

	अगर (!iport_ptr || !pr_reg->isid_present_at_reg) अणु
		pr_err("SPC-3 PR REGISTER_AND_MOVE: TransportID: %s"
			" matches: %s on received I_T Nexus\n", initiator_str,
			pr_reg_nacl->initiatorname);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण
	अगर (!म_भेद(iport_ptr, pr_reg->pr_reg_isid)) अणु
		pr_err("SPC-3 PR REGISTER_AND_MOVE: TransportID: %s %s"
			" matches: %s %s on received I_T Nexus\n",
			initiator_str, iport_ptr, pr_reg_nacl->initiatorname,
			pr_reg->pr_reg_isid);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण
after_iport_check:
	/*
	 * Locate the destination काष्ठा se_node_acl from the received Transport ID
	 */
	mutex_lock(&dest_se_tpg->acl_node_mutex);
	dest_node_acl = __core_tpg_get_initiator_node_acl(dest_se_tpg,
				initiator_str);
	अगर (dest_node_acl)
		atomic_inc_mb(&dest_node_acl->acl_pr_ref_count);
	mutex_unlock(&dest_se_tpg->acl_node_mutex);

	अगर (!dest_node_acl) अणु
		pr_err("Unable to locate %s dest_node_acl for"
			" TransportID%s\n", dest_tf_ops->fabric_name,
			initiator_str);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण

	अगर (core_scsi3_nodeacl_depend_item(dest_node_acl)) अणु
		pr_err("core_scsi3_nodeacl_depend_item() for"
			" dest_node_acl\n");
		atomic_dec_mb(&dest_node_acl->acl_pr_ref_count);
		dest_node_acl = शून्य;
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण

	pr_debug("SPC-3 PR REGISTER_AND_MOVE: Found %s dest_node_acl:"
		" %s from TransportID\n", dest_tf_ops->fabric_name,
		dest_node_acl->initiatorname);

	/*
	 * Locate the काष्ठा se_dev_entry poपूर्णांकer क्रम the matching RELATIVE TARGET
	 * PORT IDENTIFIER.
	 */
	dest_se_deve = core_get_se_deve_from_rtpi(dest_node_acl, rtpi);
	अगर (!dest_se_deve) अणु
		pr_err("Unable to locate %s dest_se_deve from RTPI:"
			" %hu\n",  dest_tf_ops->fabric_name, rtpi);
		ret = TCM_INVALID_PARAMETER_LIST;
		जाओ out;
	पूर्ण

	अगर (core_scsi3_lunacl_depend_item(dest_se_deve)) अणु
		pr_err("core_scsi3_lunacl_depend_item() failed\n");
		kref_put(&dest_se_deve->pr_kref, target_pr_kref_release);
		dest_se_deve = शून्य;
		ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		जाओ out;
	पूर्ण

	pr_debug("SPC-3 PR REGISTER_AND_MOVE: Located %s node %s LUN"
		" ACL for dest_se_deve->mapped_lun: %llu\n",
		dest_tf_ops->fabric_name, dest_node_acl->initiatorname,
		dest_se_deve->mapped_lun);

	/*
	 * A persistent reservation needs to alपढ़ोy existing in order to
	 * successfully complete the REGISTER_AND_MOVE service action..
	 */
	spin_lock(&dev->dev_reservation_lock);
	pr_res_holder = dev->dev_pr_res_holder;
	अगर (!pr_res_holder) अणु
		pr_warn("SPC-3 PR REGISTER_AND_MOVE: No reservation"
			" currently held\n");
		spin_unlock(&dev->dev_reservation_lock);
		ret = TCM_INVALID_CDB_FIELD;
		जाओ out;
	पूर्ण
	/*
	 * The received on I_T Nexus must be the reservation holder.
	 *
	 * From spc4r17 section 5.7.8  Table 50 --
	 * 	Register behaviors क्रम a REGISTER AND MOVE service action
	 */
	अगर (!is_reservation_holder(pr_res_holder, pr_reg)) अणु
		pr_warn("SPC-3 PR REGISTER_AND_MOVE: Calling I_T"
			" Nexus is not reservation holder\n");
		spin_unlock(&dev->dev_reservation_lock);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out;
	पूर्ण
	/*
	 * From spc4r17 section 5.7.8: रेजिस्टरing and moving reservation
	 *
	 * If a PERSISTENT RESERVE OUT command with a REGISTER AND MOVE service
	 * action is received and the established persistent reservation is a
	 * Write Exclusive - All Registrants type or Exclusive Access -
	 * All Registrants type reservation, then the command shall be completed
	 * with RESERVATION CONFLICT status.
	 */
	अगर ((pr_res_holder->pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG) ||
	    (pr_res_holder->pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG)) अणु
		pr_warn("SPC-3 PR REGISTER_AND_MOVE: Unable to move"
			" reservation for type: %s\n",
			core_scsi3_pr_dump_type(pr_res_holder->pr_res_type));
		spin_unlock(&dev->dev_reservation_lock);
		ret = TCM_RESERVATION_CONFLICT;
		जाओ out;
	पूर्ण
	pr_res_nacl = pr_res_holder->pr_reg_nacl;
	/*
	 * b) Ignore the contents of the (received) SCOPE and TYPE fields;
	 */
	type = pr_res_holder->pr_res_type;
	scope = pr_res_holder->pr_res_type;
	/*
	 * c) Associate the reservation key specअगरied in the SERVICE ACTION
	 *    RESERVATION KEY field with the I_T nexus specअगरied as the
	 *    destination of the रेजिस्टर and move, where:
	 *    A) The I_T nexus is specअगरied by the TransportID and the
	 *	 RELATIVE TARGET PORT IDENTIFIER field (see 6.14.4); and
	 *    B) Regardless of the TransportID क्रमmat used, the association क्रम
	 *       the initiator port is based on either the initiator port name
	 *       (see 3.1.71) on SCSI transport protocols where port names are
	 *       required or the initiator port identअगरier (see 3.1.70) on SCSI
	 *       transport protocols where port names are not required;
	 * d) Register the reservation key specअगरied in the SERVICE ACTION
	 *    RESERVATION KEY field;
	 * e) Retain the reservation key specअगरied in the SERVICE ACTION
	 *    RESERVATION KEY field and associated inक्रमmation;
	 *
	 * Also, It is not an error क्रम a REGISTER AND MOVE service action to
	 * रेजिस्टर an I_T nexus that is alपढ़ोy रेजिस्टरed with the same
	 * reservation key or a dअगरferent reservation key.
	 */
	dest_pr_reg = __core_scsi3_locate_pr_reg(dev, dest_node_acl,
					iport_ptr);
	अगर (!dest_pr_reg) अणु
		काष्ठा se_lun *dest_lun = rcu_dereference_check(dest_se_deve->se_lun,
				kref_पढ़ो(&dest_se_deve->pr_kref) != 0);

		spin_unlock(&dev->dev_reservation_lock);
		अगर (core_scsi3_alloc_registration(cmd->se_dev, dest_node_acl,
					dest_lun, dest_se_deve, dest_se_deve->mapped_lun,
					iport_ptr, sa_res_key, 0, aptpl, 2, 1)) अणु
			ret = TCM_INSUFFICIENT_REGISTRATION_RESOURCES;
			जाओ out;
		पूर्ण
		spin_lock(&dev->dev_reservation_lock);
		dest_pr_reg = __core_scsi3_locate_pr_reg(dev, dest_node_acl,
						iport_ptr);
		new_reg = 1;
	पूर्ण
	/*
	 * f) Release the persistent reservation क्रम the persistent reservation
	 *    holder (i.e., the I_T nexus on which the
	 */
	__core_scsi3_complete_pro_release(dev, pr_res_nacl,
					  dev->dev_pr_res_holder, 0, 0);
	/*
	 * g) Move the persistent reservation to the specअगरied I_T nexus using
	 *    the same scope and type as the persistent reservation released in
	 *    item f); and
	 */
	dev->dev_pr_res_holder = dest_pr_reg;
	dest_pr_reg->pr_res_holder = 1;
	dest_pr_reg->pr_res_type = type;
	pr_reg->pr_res_scope = scope;
	core_pr_dump_initiator_port(pr_reg, i_buf, PR_REG_ISID_ID_LEN);
	/*
	 * Increment PRGeneration क्रम existing registrations..
	 */
	अगर (!new_reg)
		dest_pr_reg->pr_res_generation = pr_पंचांगpl->pr_generation++;
	spin_unlock(&dev->dev_reservation_lock);

	pr_debug("SPC-3 PR [%s] Service Action: REGISTER_AND_MOVE"
		" created new reservation holder TYPE: %s on object RTPI:"
		" %hu  PRGeneration: 0x%08x\n", dest_tf_ops->fabric_name,
		core_scsi3_pr_dump_type(type), rtpi,
		dest_pr_reg->pr_res_generation);
	pr_debug("SPC-3 PR Successfully moved reservation from"
		" %s Fabric Node: %s%s -> %s Fabric Node: %s %s\n",
		tf_ops->fabric_name, pr_reg_nacl->initiatorname,
		i_buf, dest_tf_ops->fabric_name,
		dest_node_acl->initiatorname, (iport_ptr != शून्य) ?
		iport_ptr : "");
	/*
	 * It is now safe to release configfs group dependencies क्रम destination
	 * of Transport ID Initiator Device/Port Identअगरier
	 */
	core_scsi3_lunacl_undepend_item(dest_se_deve);
	core_scsi3_nodeacl_undepend_item(dest_node_acl);
	core_scsi3_tpg_undepend_item(dest_se_tpg);
	/*
	 * h) If the UNREG bit is set to one, unरेजिस्टर (see 5.7.11.3) the I_T
	 * nexus on which PERSISTENT RESERVE OUT command was received.
	 */
	अगर (unreg) अणु
		spin_lock(&pr_पंचांगpl->registration_lock);
		__core_scsi3_मुक्त_registration(dev, pr_reg, शून्य, 1);
		spin_unlock(&pr_पंचांगpl->registration_lock);
	पूर्ण अन्यथा
		core_scsi3_put_pr_reg(pr_reg);

	core_scsi3_update_and_ग_लिखो_aptpl(cmd->se_dev, aptpl);

	core_scsi3_put_pr_reg(dest_pr_reg);
	वापस 0;
out:
	अगर (buf)
		transport_kunmap_data_sg(cmd);
	अगर (dest_se_deve)
		core_scsi3_lunacl_undepend_item(dest_se_deve);
	अगर (dest_node_acl)
		core_scsi3_nodeacl_undepend_item(dest_node_acl);
	core_scsi3_tpg_undepend_item(dest_se_tpg);

out_put_pr_reg:
	core_scsi3_put_pr_reg(pr_reg);
	वापस ret;
पूर्ण

/*
 * See spc4r17 section 6.14 Table 170
 */
sense_reason_t
target_scsi3_emulate_pr_out(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित अक्षर *cdb = &cmd->t_task_cdb[0];
	अचिन्हित अक्षर *buf;
	u64 res_key, sa_res_key;
	पूर्णांक sa, scope, type, aptpl;
	पूर्णांक spec_i_pt = 0, all_tg_pt = 0, unreg = 0;
	sense_reason_t ret;

	/*
	 * Following spc2r20 5.5.1 Reservations overview:
	 *
	 * If a logical unit has been reserved by any RESERVE command and is
	 * still reserved by any initiator, all PERSISTENT RESERVE IN and all
	 * PERSISTENT RESERVE OUT commands shall conflict regardless of
	 * initiator or service action and shall terminate with a RESERVATION
	 * CONFLICT status.
	 */
	अगर (cmd->se_dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS) अणु
		pr_err("Received PERSISTENT_RESERVE CDB while legacy"
			" SPC-2 reservation is held, returning"
			" RESERVATION_CONFLICT\n");
		वापस TCM_RESERVATION_CONFLICT;
	पूर्ण

	/*
	 * FIXME: A शून्य काष्ठा se_session poपूर्णांकer means an this is not coming from
	 * a $FABRIC_MOD's nexus, but from पूर्णांकernal passthrough ops.
	 */
	अगर (!cmd->se_sess)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	अगर (cmd->data_length < 24) अणु
		pr_warn("SPC-PR: Received PR OUT parameter list"
			" length too small: %u\n", cmd->data_length);
		वापस TCM_PARAMETER_LIST_LENGTH_ERROR;
	पूर्ण

	/*
	 * From the PERSISTENT_RESERVE_OUT command descriptor block (CDB)
	 */
	sa = (cdb[1] & 0x1f);
	scope = (cdb[2] & 0xf0);
	type = (cdb[2] & 0x0f);

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	/*
	 * From PERSISTENT_RESERVE_OUT parameter list (payload)
	 */
	res_key = get_unaligned_be64(&buf[0]);
	sa_res_key = get_unaligned_be64(&buf[8]);
	/*
	 * REGISTER_AND_MOVE uses a dअगरferent SA parameter list containing
	 * SCSI TransportIDs.
	 */
	अगर (sa != PRO_REGISTER_AND_MOVE) अणु
		spec_i_pt = (buf[20] & 0x08);
		all_tg_pt = (buf[20] & 0x04);
		aptpl = (buf[20] & 0x01);
	पूर्ण अन्यथा अणु
		aptpl = (buf[17] & 0x01);
		unreg = (buf[17] & 0x02);
	पूर्ण
	/*
	 * If the backend device has been configured to क्रमce APTPL metadata
	 * ग_लिखो-out, go ahead and propigate aptpl=1 करोwn now.
	 */
	अगर (dev->dev_attrib.क्रमce_pr_aptpl)
		aptpl = 1;

	transport_kunmap_data_sg(cmd);
	buf = शून्य;

	/*
	 * SPEC_I_PT=1 is only valid क्रम Service action: REGISTER
	 */
	अगर (spec_i_pt && (sa != PRO_REGISTER))
		वापस TCM_INVALID_PARAMETER_LIST;

	/*
	 * From spc4r17 section 6.14:
	 *
	 * If the SPEC_I_PT bit is set to zero, the service action is not
	 * REGISTER AND MOVE, and the parameter list length is not 24, then
	 * the command shall be terminated with CHECK CONDITION status, with
	 * the sense key set to ILLEGAL REQUEST, and the additional sense
	 * code set to PARAMETER LIST LENGTH ERROR.
	 */
	अगर (!spec_i_pt && (sa != PRO_REGISTER_AND_MOVE) &&
	    (cmd->data_length != 24)) अणु
		pr_warn("SPC-PR: Received PR OUT illegal parameter"
			" list length: %u\n", cmd->data_length);
		वापस TCM_PARAMETER_LIST_LENGTH_ERROR;
	पूर्ण

	/*
	 * (core_scsi3_emulate_pro_* function parameters
	 * are defined by spc4r17 Table 174:
	 * PERSISTENT_RESERVE_OUT service actions and valid parameters.
	 */
	चयन (sa) अणु
	हाल PRO_REGISTER:
		ret = core_scsi3_emulate_pro_रेजिस्टर(cmd,
			res_key, sa_res_key, aptpl, all_tg_pt, spec_i_pt, REGISTER);
		अवरोध;
	हाल PRO_RESERVE:
		ret = core_scsi3_emulate_pro_reserve(cmd, type, scope, res_key);
		अवरोध;
	हाल PRO_RELEASE:
		ret = core_scsi3_emulate_pro_release(cmd, type, scope, res_key);
		अवरोध;
	हाल PRO_CLEAR:
		ret = core_scsi3_emulate_pro_clear(cmd, res_key);
		अवरोध;
	हाल PRO_PREEMPT:
		ret = core_scsi3_emulate_pro_preempt(cmd, type, scope,
					res_key, sa_res_key, PREEMPT);
		अवरोध;
	हाल PRO_PREEMPT_AND_ABORT:
		ret = core_scsi3_emulate_pro_preempt(cmd, type, scope,
					res_key, sa_res_key, PREEMPT_AND_ABORT);
		अवरोध;
	हाल PRO_REGISTER_AND_IGNORE_EXISTING_KEY:
		ret = core_scsi3_emulate_pro_रेजिस्टर(cmd,
			0, sa_res_key, aptpl, all_tg_pt, spec_i_pt, REGISTER_AND_IGNORE_EXISTING_KEY);
		अवरोध;
	हाल PRO_REGISTER_AND_MOVE:
		ret = core_scsi3_emulate_pro_रेजिस्टर_and_move(cmd, res_key,
				sa_res_key, aptpl, unreg);
		अवरोध;
	शेष:
		pr_err("Unknown PERSISTENT_RESERVE_OUT service"
			" action: 0x%02x\n", sa);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	अगर (!ret)
		target_complete_cmd(cmd, GOOD);
	वापस ret;
पूर्ण

/*
 * PERSISTENT_RESERVE_IN Service Action READ_KEYS
 *
 * See spc4r17 section 5.7.6.2 and section 6.13.2, Table 160
 */
अटल sense_reason_t
core_scsi3_pri_पढ़ो_keys(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_pr_registration *pr_reg;
	अचिन्हित अक्षर *buf;
	u32 add_len = 0, off = 8;

	अगर (cmd->data_length < 8) अणु
		pr_err("PRIN SA READ_KEYS SCSI Data Length: %u"
			" too small\n", cmd->data_length);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	put_unaligned_be32(dev->t10_pr.pr_generation, buf);

	spin_lock(&dev->t10_pr.registration_lock);
	list_क्रम_each_entry(pr_reg, &dev->t10_pr.registration_list,
			pr_reg_list) अणु
		/*
		 * Check क्रम overflow of 8byte PRI READ_KEYS payload and
		 * next reservation key list descriptor.
		 */
		अगर (off + 8 <= cmd->data_length) अणु
			put_unaligned_be64(pr_reg->pr_res_key, &buf[off]);
			off += 8;
		पूर्ण
		/*
		 * SPC5r17: 6.16.2 READ KEYS service action
		 * The ADDITIONAL LENGTH field indicates the number of bytes in
		 * the Reservation key list. The contents of the ADDITIONAL
		 * LENGTH field are not altered based on the allocation length
		 */
		add_len += 8;
	पूर्ण
	spin_unlock(&dev->t10_pr.registration_lock);

	put_unaligned_be32(add_len, &buf[4]);
	target_set_cmd_data_length(cmd, 8 + add_len);

	transport_kunmap_data_sg(cmd);

	वापस 0;
पूर्ण

/*
 * PERSISTENT_RESERVE_IN Service Action READ_RESERVATION
 *
 * See spc4r17 section 5.7.6.3 and section 6.13.3.2 Table 161 and 162
 */
अटल sense_reason_t
core_scsi3_pri_पढ़ो_reservation(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_pr_registration *pr_reg;
	अचिन्हित अक्षर *buf;
	u64 pr_res_key;
	u32 add_len = 0;

	अगर (cmd->data_length < 8) अणु
		pr_err("PRIN SA READ_RESERVATIONS SCSI Data Length: %u"
			" too small\n", cmd->data_length);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	put_unaligned_be32(dev->t10_pr.pr_generation, &buf[0]);

	spin_lock(&dev->dev_reservation_lock);
	pr_reg = dev->dev_pr_res_holder;
	अगर (pr_reg) अणु
		/*
		 * Set the Additional Length to 16 when a reservation is held
		 */
		add_len = 16;
		put_unaligned_be32(add_len, &buf[4]);

		अगर (cmd->data_length < 22)
			जाओ err;

		/*
		 * Set the Reservation key.
		 *
		 * From spc4r17, section 5.7.10:
		 * A persistent reservation holder has its reservation key
		 * वापसed in the parameter data from a PERSISTENT
		 * RESERVE IN command with READ RESERVATION service action as
		 * follows:
		 * a) For a persistent reservation of the type Write Exclusive
		 *    - All Registrants or Exclusive Access तऐ All Regitrants,
		 *      the reservation key shall be set to zero; or
		 * b) For all other persistent reservation types, the
		 *    reservation key shall be set to the रेजिस्टरed
		 *    reservation key क्रम the I_T nexus that holds the
		 *    persistent reservation.
		 */
		अगर ((pr_reg->pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG) ||
		    (pr_reg->pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG))
			pr_res_key = 0;
		अन्यथा
			pr_res_key = pr_reg->pr_res_key;

		put_unaligned_be64(pr_res_key, &buf[8]);
		/*
		 * Set the SCOPE and TYPE
		 */
		buf[21] = (pr_reg->pr_res_scope & 0xf0) |
			  (pr_reg->pr_res_type & 0x0f);
	पूर्ण

	target_set_cmd_data_length(cmd, 8 + add_len);

err:
	spin_unlock(&dev->dev_reservation_lock);
	transport_kunmap_data_sg(cmd);

	वापस 0;
पूर्ण

/*
 * PERSISTENT_RESERVE_IN Service Action REPORT_CAPABILITIES
 *
 * See spc4r17 section 6.13.4 Table 165
 */
अटल sense_reason_t
core_scsi3_pri_report_capabilities(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	अचिन्हित अक्षर *buf;
	u16 len = 8; /* Hardcoded to 8. */

	अगर (cmd->data_length < 6) अणु
		pr_err("PRIN SA REPORT_CAPABILITIES SCSI Data Length:"
			" %u too small\n", cmd->data_length);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	put_unaligned_be16(len, &buf[0]);
	buf[2] |= 0x10; /* CRH: Compatible Reservation Hanlding bit. */
	buf[2] |= 0x08; /* SIP_C: Specअगरy Initiator Ports Capable bit */
	buf[2] |= 0x04; /* ATP_C: All Target Ports Capable bit */
	buf[2] |= 0x01; /* PTPL_C: Persistence across Target Power Loss bit */
	/*
	 * We are filling in the PERSISTENT RESERVATION TYPE MASK below, so
	 * set the TMV: Task Mask Valid bit.
	 */
	buf[3] |= 0x80;
	/*
	 * Change ALLOW COMMANDs to 0x20 or 0x40 later from Table 166
	 */
	buf[3] |= 0x10; /* ALLOW COMMANDs field 001b */
	/*
	 * PTPL_A: Persistence across Target Power Loss Active bit
	 */
	अगर (pr_पंचांगpl->pr_aptpl_active)
		buf[3] |= 0x01;
	/*
	 * Setup the PERSISTENT RESERVATION TYPE MASK from Table 167
	 */
	buf[4] |= 0x80; /* PR_TYPE_EXCLUSIVE_ACCESS_ALLREG */
	buf[4] |= 0x40; /* PR_TYPE_EXCLUSIVE_ACCESS_REGONLY */
	buf[4] |= 0x20; /* PR_TYPE_WRITE_EXCLUSIVE_REGONLY */
	buf[4] |= 0x08; /* PR_TYPE_EXCLUSIVE_ACCESS */
	buf[4] |= 0x02; /* PR_TYPE_WRITE_EXCLUSIVE */
	buf[5] |= 0x01; /* PR_TYPE_EXCLUSIVE_ACCESS_ALLREG */

	target_set_cmd_data_length(cmd, len);

	transport_kunmap_data_sg(cmd);

	वापस 0;
पूर्ण

/*
 * PERSISTENT_RESERVE_IN Service Action READ_FULL_STATUS
 *
 * See spc4r17 section 6.13.5 Table 168 and 169
 */
अटल sense_reason_t
core_scsi3_pri_पढ़ो_full_status(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_node_acl *se_nacl;
	काष्ठा se_portal_group *se_tpg;
	काष्ठा t10_pr_registration *pr_reg, *pr_reg_पंचांगp;
	काष्ठा t10_reservation *pr_पंचांगpl = &dev->t10_pr;
	अचिन्हित अक्षर *buf;
	u32 add_desc_len = 0, add_len = 0;
	u32 off = 8; /* off पूर्णांकo first Full Status descriptor */
	पूर्णांक क्रमmat_code = 0, pr_res_type = 0, pr_res_scope = 0;
	पूर्णांक exp_desc_len, desc_len;
	bool all_reg = false;

	अगर (cmd->data_length < 8) अणु
		pr_err("PRIN SA READ_FULL_STATUS SCSI Data Length: %u"
			" too small\n", cmd->data_length);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	put_unaligned_be32(dev->t10_pr.pr_generation, &buf[0]);

	spin_lock(&dev->dev_reservation_lock);
	अगर (dev->dev_pr_res_holder) अणु
		काष्ठा t10_pr_registration *pr_holder = dev->dev_pr_res_holder;

		अगर (pr_holder->pr_res_type == PR_TYPE_WRITE_EXCLUSIVE_ALLREG ||
		    pr_holder->pr_res_type == PR_TYPE_EXCLUSIVE_ACCESS_ALLREG) अणु
			all_reg = true;
			pr_res_type = pr_holder->pr_res_type;
			pr_res_scope = pr_holder->pr_res_scope;
		पूर्ण
	पूर्ण
	spin_unlock(&dev->dev_reservation_lock);

	spin_lock(&pr_पंचांगpl->registration_lock);
	list_क्रम_each_entry_safe(pr_reg, pr_reg_पंचांगp,
			&pr_पंचांगpl->registration_list, pr_reg_list) अणु

		se_nacl = pr_reg->pr_reg_nacl;
		se_tpg = pr_reg->pr_reg_nacl->se_tpg;
		add_desc_len = 0;

		atomic_inc_mb(&pr_reg->pr_res_holders);
		spin_unlock(&pr_पंचांगpl->registration_lock);
		/*
		 * Determine expected length of $FABRIC_MOD specअगरic
		 * TransportID full status descriptor..
		 */
		exp_desc_len = target_get_pr_transport_id_len(se_nacl, pr_reg,
					&क्रमmat_code);
		अगर (exp_desc_len < 0 ||
		    exp_desc_len + add_len > cmd->data_length) अणु
			pr_warn("SPC-3 PRIN READ_FULL_STATUS ran"
				" out of buffer: %d\n", cmd->data_length);
			spin_lock(&pr_पंचांगpl->registration_lock);
			atomic_dec_mb(&pr_reg->pr_res_holders);
			अवरोध;
		पूर्ण
		/*
		 * Set RESERVATION KEY
		 */
		put_unaligned_be64(pr_reg->pr_res_key, &buf[off]);
		off += 8;
		off += 4; /* Skip Over Reserved area */

		/*
		 * Set ALL_TG_PT bit अगर PROUT SA REGISTER had this set.
		 */
		अगर (pr_reg->pr_reg_all_tg_pt)
			buf[off] = 0x02;
		/*
		 * The काष्ठा se_lun poपूर्णांकer will be present क्रम the
		 * reservation holder क्रम PR_HOLDER bit.
		 *
		 * Also, अगर this registration is the reservation
		 * holder or there is an All Registrants reservation
		 * active, fill in SCOPE and TYPE in the next byte.
		 */
		अगर (pr_reg->pr_res_holder) अणु
			buf[off++] |= 0x01;
			buf[off++] = (pr_reg->pr_res_scope & 0xf0) |
				     (pr_reg->pr_res_type & 0x0f);
		पूर्ण अन्यथा अगर (all_reg) अणु
			buf[off++] |= 0x01;
			buf[off++] = (pr_res_scope & 0xf0) |
				     (pr_res_type & 0x0f);
		पूर्ण अन्यथा अणु
			off += 2;
		पूर्ण

		off += 4; /* Skip over reserved area */
		/*
		 * From spc4r17 6.3.15:
		 *
		 * If the ALL_TG_PT bit set to zero, the RELATIVE TARGET PORT
		 * IDENTIFIER field contains the relative port identअगरier (see
		 * 3.1.120) of the target port that is part of the I_T nexus
		 * described by this full status descriptor. If the ALL_TG_PT
		 * bit is set to one, the contents of the RELATIVE TARGET PORT
		 * IDENTIFIER field are not defined by this standard.
		 */
		अगर (!pr_reg->pr_reg_all_tg_pt) अणु
			u16 sep_rtpi = pr_reg->tg_pt_sep_rtpi;

			put_unaligned_be16(sep_rtpi, &buf[off]);
			off += 2;
		पूर्ण अन्यथा
			off += 2; /* Skip over RELATIVE TARGET PORT IDENTIFIER */

		buf[off+4] = se_tpg->proto_id;

		/*
		 * Now, have the $FABRIC_MOD fill in the transport ID.
		 */
		desc_len = target_get_pr_transport_id(se_nacl, pr_reg,
				&क्रमmat_code, &buf[off+4]);

		spin_lock(&pr_पंचांगpl->registration_lock);
		atomic_dec_mb(&pr_reg->pr_res_holders);

		अगर (desc_len < 0)
			अवरोध;
		/*
		 * Set the ADDITIONAL DESCRIPTOR LENGTH
		 */
		put_unaligned_be32(desc_len, &buf[off]);
		off += 4;
		/*
		 * Size of full desctipor header minus TransportID
		 * containing $FABRIC_MOD specअगरic) initiator device/port
		 * WWN inक्रमmation.
		 *
		 *  See spc4r17 Section 6.13.5 Table 169
		 */
		add_desc_len = (24 + desc_len);

		off += desc_len;
		add_len += add_desc_len;
	पूर्ण
	spin_unlock(&pr_पंचांगpl->registration_lock);
	/*
	 * Set ADDITIONAL_LENGTH
	 */
	put_unaligned_be32(add_len, &buf[4]);
	target_set_cmd_data_length(cmd, 8 + add_len);

	transport_kunmap_data_sg(cmd);

	वापस 0;
पूर्ण

sense_reason_t
target_scsi3_emulate_pr_in(काष्ठा se_cmd *cmd)
अणु
	sense_reason_t ret;

	/*
	 * Following spc2r20 5.5.1 Reservations overview:
	 *
	 * If a logical unit has been reserved by any RESERVE command and is
	 * still reserved by any initiator, all PERSISTENT RESERVE IN and all
	 * PERSISTENT RESERVE OUT commands shall conflict regardless of
	 * initiator or service action and shall terminate with a RESERVATION
	 * CONFLICT status.
	 */
	अगर (cmd->se_dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS) अणु
		pr_err("Received PERSISTENT_RESERVE CDB while legacy"
			" SPC-2 reservation is held, returning"
			" RESERVATION_CONFLICT\n");
		वापस TCM_RESERVATION_CONFLICT;
	पूर्ण

	चयन (cmd->t_task_cdb[1] & 0x1f) अणु
	हाल PRI_READ_KEYS:
		ret = core_scsi3_pri_पढ़ो_keys(cmd);
		अवरोध;
	हाल PRI_READ_RESERVATION:
		ret = core_scsi3_pri_पढ़ो_reservation(cmd);
		अवरोध;
	हाल PRI_REPORT_CAPABILITIES:
		ret = core_scsi3_pri_report_capabilities(cmd);
		अवरोध;
	हाल PRI_READ_FULL_STATUS:
		ret = core_scsi3_pri_पढ़ो_full_status(cmd);
		अवरोध;
	शेष:
		pr_err("Unknown PERSISTENT_RESERVE_IN service"
			" action: 0x%02x\n", cmd->t_task_cdb[1] & 0x1f);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	अगर (!ret)
		target_complete_cmd(cmd, GOOD);
	वापस ret;
पूर्ण

sense_reason_t
target_check_reservation(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	sense_reason_t ret;

	अगर (!cmd->se_sess)
		वापस 0;
	अगर (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE)
		वापस 0;
	अगर (!dev->dev_attrib.emulate_pr)
		वापस 0;
	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR)
		वापस 0;

	spin_lock(&dev->dev_reservation_lock);
	अगर (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		ret = target_scsi2_reservation_check(cmd);
	अन्यथा
		ret = target_scsi3_pr_reservation_check(cmd);
	spin_unlock(&dev->dev_reservation_lock);

	वापस ret;
पूर्ण
