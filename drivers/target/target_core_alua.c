<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename:  target_core_alua.c
 *
 * This file contains SPC-3 compliant asymmetric logical unit assignपंचांगent (ALUA)
 *
 * (c) Copyright 2009-2013 Datera, Inc.
 *
 * Nicholas A. Bellinger <nab@kernel.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/configfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_alua.h"
#समावेश "target_core_ua.h"

अटल sense_reason_t core_alua_check_transition(पूर्णांक state, पूर्णांक valid,
						 पूर्णांक *primary, पूर्णांक explicit);
अटल पूर्णांक core_alua_set_tg_pt_secondary_state(
		काष्ठा se_lun *lun, पूर्णांक explicit, पूर्णांक offline);

अटल अक्षर *core_alua_dump_state(पूर्णांक state);

अटल व्योम __target_attach_tg_pt_gp(काष्ठा se_lun *lun,
		काष्ठा t10_alua_tg_pt_gp *tg_pt_gp);

अटल u16 alua_lu_gps_counter;
अटल u32 alua_lu_gps_count;

अटल DEFINE_SPINLOCK(lu_gps_lock);
अटल LIST_HEAD(lu_gps_list);

काष्ठा t10_alua_lu_gp *शेष_lu_gp;

/*
 * REPORT REFERRALS
 *
 * See sbc3r35 section 5.23
 */
sense_reason_t
target_emulate_report_referrals(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_alua_lba_map *map;
	काष्ठा t10_alua_lba_map_member *map_mem;
	अचिन्हित अक्षर *buf;
	u32 rd_len = 0, off;

	अगर (cmd->data_length < 4) अणु
		pr_warn("REPORT REFERRALS allocation length %u too"
			" small\n", cmd->data_length);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	off = 4;
	spin_lock(&dev->t10_alua.lba_map_lock);
	अगर (list_empty(&dev->t10_alua.lba_map_list)) अणु
		spin_unlock(&dev->t10_alua.lba_map_lock);
		transport_kunmap_data_sg(cmd);

		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण

	list_क्रम_each_entry(map, &dev->t10_alua.lba_map_list,
			    lba_map_list) अणु
		पूर्णांक desc_num = off + 3;
		पूर्णांक pg_num;

		off += 4;
		अगर (cmd->data_length > off)
			put_unaligned_be64(map->lba_map_first_lba, &buf[off]);
		off += 8;
		अगर (cmd->data_length > off)
			put_unaligned_be64(map->lba_map_last_lba, &buf[off]);
		off += 8;
		rd_len += 20;
		pg_num = 0;
		list_क्रम_each_entry(map_mem, &map->lba_map_mem_list,
				    lba_map_mem_list) अणु
			पूर्णांक alua_state = map_mem->lba_map_mem_alua_state;
			पूर्णांक alua_pg_id = map_mem->lba_map_mem_alua_pg_id;

			अगर (cmd->data_length > off)
				buf[off] = alua_state & 0x0f;
			off += 2;
			अगर (cmd->data_length > off)
				buf[off] = (alua_pg_id >> 8) & 0xff;
			off++;
			अगर (cmd->data_length > off)
				buf[off] = (alua_pg_id & 0xff);
			off++;
			rd_len += 4;
			pg_num++;
		पूर्ण
		अगर (cmd->data_length > desc_num)
			buf[desc_num] = pg_num;
	पूर्ण
	spin_unlock(&dev->t10_alua.lba_map_lock);

	/*
	 * Set the RETURN DATA LENGTH set in the header of the DataIN Payload
	 */
	put_unaligned_be16(rd_len, &buf[2]);

	transport_kunmap_data_sg(cmd);

	target_complete_cmd(cmd, GOOD);
	वापस 0;
पूर्ण

/*
 * REPORT_TARGET_PORT_GROUPS
 *
 * See spc4r17 section 6.27
 */
sense_reason_t
target_emulate_report_target_port_groups(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	काष्ठा se_lun *lun;
	अचिन्हित अक्षर *buf;
	u32 rd_len = 0, off;
	पूर्णांक ext_hdr = (cmd->t_task_cdb[1] & 0x20);

	/*
	 * Skip over RESERVED area to first Target port group descriptor
	 * depending on the PARAMETER DATA FORMAT type..
	 */
	अगर (ext_hdr != 0)
		off = 8;
	अन्यथा
		off = 4;

	अगर (cmd->data_length < off) अणु
		pr_warn("REPORT TARGET PORT GROUPS allocation length %u too"
			" small for %s header\n", cmd->data_length,
			(ext_hdr) ? "extended" : "normal");
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण
	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	spin_lock(&dev->t10_alua.tg_pt_gps_lock);
	list_क्रम_each_entry(tg_pt_gp, &dev->t10_alua.tg_pt_gps_list,
			tg_pt_gp_list) अणु
		/*
		 * Check अगर the Target port group and Target port descriptor list
		 * based on tg_pt_gp_members count will fit पूर्णांकo the response payload.
		 * Otherwise, bump rd_len to let the initiator know we have exceeded
		 * the allocation length and the response is truncated.
		 */
		अगर ((off + 8 + (tg_pt_gp->tg_pt_gp_members * 4)) >
		     cmd->data_length) अणु
			rd_len += 8 + (tg_pt_gp->tg_pt_gp_members * 4);
			जारी;
		पूर्ण
		/*
		 * PREF: Preferred target port bit, determine अगर this
		 * bit should be set क्रम port group.
		 */
		अगर (tg_pt_gp->tg_pt_gp_pref)
			buf[off] = 0x80;
		/*
		 * Set the ASYMMETRIC ACCESS State
		 */
		buf[off++] |= tg_pt_gp->tg_pt_gp_alua_access_state & 0xff;
		/*
		 * Set supported ASYMMETRIC ACCESS State bits
		 */
		buf[off++] |= tg_pt_gp->tg_pt_gp_alua_supported_states;
		/*
		 * TARGET PORT GROUP
		 */
		put_unaligned_be16(tg_pt_gp->tg_pt_gp_id, &buf[off]);
		off += 2;

		off++; /* Skip over Reserved */
		/*
		 * STATUS CODE
		 */
		buf[off++] = (tg_pt_gp->tg_pt_gp_alua_access_status & 0xff);
		/*
		 * Venकरोr Specअगरic field
		 */
		buf[off++] = 0x00;
		/*
		 * TARGET PORT COUNT
		 */
		buf[off++] = (tg_pt_gp->tg_pt_gp_members & 0xff);
		rd_len += 8;

		spin_lock(&tg_pt_gp->tg_pt_gp_lock);
		list_क्रम_each_entry(lun, &tg_pt_gp->tg_pt_gp_lun_list,
				lun_tg_pt_gp_link) अणु
			/*
			 * Start Target Port descriptor क्रमmat
			 *
			 * See spc4r17 section 6.2.7 Table 247
			 */
			off += 2; /* Skip over Obsolete */
			/*
			 * Set RELATIVE TARGET PORT IDENTIFIER
			 */
			put_unaligned_be16(lun->lun_rtpi, &buf[off]);
			off += 2;
			rd_len += 4;
		पूर्ण
		spin_unlock(&tg_pt_gp->tg_pt_gp_lock);
	पूर्ण
	spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
	/*
	 * Set the RETURN DATA LENGTH set in the header of the DataIN Payload
	 */
	put_unaligned_be32(rd_len, &buf[0]);

	/*
	 * Fill in the Extended header parameter data क्रमmat अगर requested
	 */
	अगर (ext_hdr != 0) अणु
		buf[4] = 0x10;
		/*
		 * Set the implicit transition समय (in seconds) क्रम the application
		 * client to use as a base क्रम it's transition समयout value.
		 *
		 * Use the current tg_pt_gp_mem -> tg_pt_gp membership from the LUN
		 * this CDB was received upon to determine this value inभागidually
		 * क्रम ALUA target port group.
		 */
		spin_lock(&cmd->se_lun->lun_tg_pt_gp_lock);
		tg_pt_gp = cmd->se_lun->lun_tg_pt_gp;
		अगर (tg_pt_gp)
			buf[5] = tg_pt_gp->tg_pt_gp_implicit_trans_secs;
		spin_unlock(&cmd->se_lun->lun_tg_pt_gp_lock);
	पूर्ण
	transport_kunmap_data_sg(cmd);

	target_complete_cmd_with_length(cmd, GOOD, rd_len + 4);
	वापस 0;
पूर्ण

/*
 * SET_TARGET_PORT_GROUPS क्रम explicit ALUA operation.
 *
 * See spc4r17 section 6.35
 */
sense_reason_t
target_emulate_set_target_port_groups(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	काष्ठा se_lun *l_lun = cmd->se_lun;
	काष्ठा se_node_acl *nacl = cmd->se_sess->se_node_acl;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = शून्य, *l_tg_pt_gp;
	अचिन्हित अक्षर *buf;
	अचिन्हित अक्षर *ptr;
	sense_reason_t rc = TCM_NO_SENSE;
	u32 len = 4; /* Skip over RESERVED area in header */
	पूर्णांक alua_access_state, primary = 0, valid_states;
	u16 tg_pt_id, rtpi;

	अगर (cmd->data_length < 4) अणु
		pr_warn("SET TARGET PORT GROUPS parameter list length %u too"
			" small\n", cmd->data_length);
		वापस TCM_INVALID_PARAMETER_LIST;
	पूर्ण

	buf = transport_kmap_data_sg(cmd);
	अगर (!buf)
		वापस TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	/*
	 * Determine अगर explicit ALUA via SET_TARGET_PORT_GROUPS is allowed
	 * क्रम the local tg_pt_gp.
	 */
	spin_lock(&l_lun->lun_tg_pt_gp_lock);
	l_tg_pt_gp = l_lun->lun_tg_pt_gp;
	अगर (!l_tg_pt_gp) अणु
		spin_unlock(&l_lun->lun_tg_pt_gp_lock);
		pr_err("Unable to access l_lun->tg_pt_gp\n");
		rc = TCM_UNSUPPORTED_SCSI_OPCODE;
		जाओ out;
	पूर्ण

	अगर (!(l_tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_EXPLICIT_ALUA)) अणु
		spin_unlock(&l_lun->lun_tg_pt_gp_lock);
		pr_debug("Unable to process SET_TARGET_PORT_GROUPS"
				" while TPGS_EXPLICIT_ALUA is disabled\n");
		rc = TCM_UNSUPPORTED_SCSI_OPCODE;
		जाओ out;
	पूर्ण
	valid_states = l_tg_pt_gp->tg_pt_gp_alua_supported_states;
	spin_unlock(&l_lun->lun_tg_pt_gp_lock);

	ptr = &buf[4]; /* Skip over RESERVED area in header */

	जबतक (len < cmd->data_length) अणु
		bool found = false;
		alua_access_state = (ptr[0] & 0x0f);
		/*
		 * Check the received ALUA access state, and determine अगर
		 * the state is a primary or secondary target port asymmetric
		 * access state.
		 */
		rc = core_alua_check_transition(alua_access_state, valid_states,
						&primary, 1);
		अगर (rc) अणु
			/*
			 * If the SET TARGET PORT GROUPS attempts to establish
			 * an invalid combination of target port asymmetric
			 * access states or attempts to establish an
			 * unsupported target port asymmetric access state,
			 * then the command shall be terminated with CHECK
			 * CONDITION status, with the sense key set to ILLEGAL
			 * REQUEST, and the additional sense code set to INVALID
			 * FIELD IN PARAMETER LIST.
			 */
			जाओ out;
		पूर्ण

		/*
		 * If the ASYMMETRIC ACCESS STATE field (see table 267)
		 * specअगरies a primary target port asymmetric access state,
		 * then the TARGET PORT GROUP OR TARGET PORT field specअगरies
		 * a primary target port group क्रम which the primary target
		 * port asymmetric access state shall be changed. If the
		 * ASYMMETRIC ACCESS STATE field specअगरies a secondary target
		 * port asymmetric access state, then the TARGET PORT GROUP OR
		 * TARGET PORT field specअगरies the relative target port
		 * identअगरier (see 3.1.120) of the target port क्रम which the
		 * secondary target port asymmetric access state shall be
		 * changed.
		 */
		अगर (primary) अणु
			tg_pt_id = get_unaligned_be16(ptr + 2);
			/*
			 * Locate the matching target port group ID from
			 * the global tg_pt_gp list
			 */
			spin_lock(&dev->t10_alua.tg_pt_gps_lock);
			list_क्रम_each_entry(tg_pt_gp,
					&dev->t10_alua.tg_pt_gps_list,
					tg_pt_gp_list) अणु
				अगर (!tg_pt_gp->tg_pt_gp_valid_id)
					जारी;

				अगर (tg_pt_id != tg_pt_gp->tg_pt_gp_id)
					जारी;

				atomic_inc_mb(&tg_pt_gp->tg_pt_gp_ref_cnt);

				spin_unlock(&dev->t10_alua.tg_pt_gps_lock);

				अगर (!core_alua_करो_port_transition(tg_pt_gp,
						dev, l_lun, nacl,
						alua_access_state, 1))
					found = true;

				spin_lock(&dev->t10_alua.tg_pt_gps_lock);
				atomic_dec_mb(&tg_pt_gp->tg_pt_gp_ref_cnt);
				अवरोध;
			पूर्ण
			spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
		पूर्ण अन्यथा अणु
			काष्ठा se_lun *lun;

			/*
			 * Extract the RELATIVE TARGET PORT IDENTIFIER to identअगरy
			 * the Target Port in question क्रम the the incoming
			 * SET_TARGET_PORT_GROUPS op.
			 */
			rtpi = get_unaligned_be16(ptr + 2);
			/*
			 * Locate the matching relative target port identअगरier
			 * क्रम the काष्ठा se_device storage object.
			 */
			spin_lock(&dev->se_port_lock);
			list_क्रम_each_entry(lun, &dev->dev_sep_list,
							lun_dev_link) अणु
				अगर (lun->lun_rtpi != rtpi)
					जारी;

				// XXX: racy unlock
				spin_unlock(&dev->se_port_lock);

				अगर (!core_alua_set_tg_pt_secondary_state(
						lun, 1, 1))
					found = true;

				spin_lock(&dev->se_port_lock);
				अवरोध;
			पूर्ण
			spin_unlock(&dev->se_port_lock);
		पूर्ण

		अगर (!found) अणु
			rc = TCM_INVALID_PARAMETER_LIST;
			जाओ out;
		पूर्ण

		ptr += 4;
		len += 4;
	पूर्ण

out:
	transport_kunmap_data_sg(cmd);
	अगर (!rc)
		target_complete_cmd(cmd, GOOD);
	वापस rc;
पूर्ण

अटल अंतरभूत व्योम set_ascq(काष्ठा se_cmd *cmd, u8 alua_ascq)
अणु
	/*
	 * Set SCSI additional sense code (ASC) to 'LUN Not Accessible';
	 * The ALUA additional sense code qualअगरier (ASCQ) is determined
	 * by the ALUA primary or secondary access state..
	 */
	pr_debug("[%s]: ALUA TG Port not available, "
		"SenseKey: NOT_READY, ASC/ASCQ: "
		"0x04/0x%02x\n",
		cmd->se_tfo->fabric_name, alua_ascq);

	cmd->scsi_asc = 0x04;
	cmd->scsi_ascq = alua_ascq;
पूर्ण

अटल अंतरभूत व्योम core_alua_state_nonoptimized(
	काष्ठा se_cmd *cmd,
	अचिन्हित अक्षर *cdb,
	पूर्णांक nonop_delay_msecs)
अणु
	/*
	 * Set SCF_ALUA_NON_OPTIMIZED here, this value will be checked
	 * later to determine अगर processing of this cmd needs to be
	 * temporarily delayed क्रम the Active/NonOptimized primary access state.
	 */
	cmd->se_cmd_flags |= SCF_ALUA_NON_OPTIMIZED;
	cmd->alua_nonop_delay = nonop_delay_msecs;
पूर्ण

अटल अंतरभूत पूर्णांक core_alua_state_lba_dependent(
	काष्ठा se_cmd *cmd,
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	u64 segment_size, segment_mult, sectors, lba;

	/* Only need to check क्रम cdb actually containing LBAs */
	अगर (!(cmd->se_cmd_flags & SCF_SCSI_DATA_CDB))
		वापस 0;

	spin_lock(&dev->t10_alua.lba_map_lock);
	segment_size = dev->t10_alua.lba_map_segment_size;
	segment_mult = dev->t10_alua.lba_map_segment_multiplier;
	sectors = cmd->data_length / dev->dev_attrib.block_size;

	lba = cmd->t_task_lba;
	जबतक (lba < cmd->t_task_lba + sectors) अणु
		काष्ठा t10_alua_lba_map *cur_map = शून्य, *map;
		काष्ठा t10_alua_lba_map_member *map_mem;

		list_क्रम_each_entry(map, &dev->t10_alua.lba_map_list,
				    lba_map_list) अणु
			u64 start_lba, last_lba;
			u64 first_lba = map->lba_map_first_lba;

			अगर (segment_mult) अणु
				u64 पंचांगp = lba;
				start_lba = करो_भाग(पंचांगp, segment_size * segment_mult);

				last_lba = first_lba + segment_size - 1;
				अगर (start_lba >= first_lba &&
				    start_lba <= last_lba) अणु
					lba += segment_size;
					cur_map = map;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				last_lba = map->lba_map_last_lba;
				अगर (lba >= first_lba && lba <= last_lba) अणु
					lba = last_lba + 1;
					cur_map = map;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (!cur_map) अणु
			spin_unlock(&dev->t10_alua.lba_map_lock);
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_UNAVAILABLE);
			वापस 1;
		पूर्ण
		list_क्रम_each_entry(map_mem, &cur_map->lba_map_mem_list,
				    lba_map_mem_list) अणु
			अगर (map_mem->lba_map_mem_alua_pg_id !=
			    tg_pt_gp->tg_pt_gp_id)
				जारी;
			चयन(map_mem->lba_map_mem_alua_state) अणु
			हाल ALUA_ACCESS_STATE_STANDBY:
				spin_unlock(&dev->t10_alua.lba_map_lock);
				set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
				वापस 1;
			हाल ALUA_ACCESS_STATE_UNAVAILABLE:
				spin_unlock(&dev->t10_alua.lba_map_lock);
				set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_UNAVAILABLE);
				वापस 1;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&dev->t10_alua.lba_map_lock);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक core_alua_state_standby(
	काष्ठा se_cmd *cmd,
	अचिन्हित अक्षर *cdb)
अणु
	/*
	 * Allowed CDBs क्रम ALUA_ACCESS_STATE_STANDBY as defined by
	 * spc4r17 section 5.9.2.4.4
	 */
	चयन (cdb[0]) अणु
	हाल INQUIRY:
	हाल LOG_SELECT:
	हाल LOG_SENSE:
	हाल MODE_SELECT:
	हाल MODE_SENSE:
	हाल REPORT_LUNS:
	हाल RECEIVE_DIAGNOSTIC:
	हाल SEND_DIAGNOSTIC:
	हाल READ_CAPACITY:
		वापस 0;
	हाल SERVICE_ACTION_IN_16:
		चयन (cdb[1] & 0x1f) अणु
		हाल SAI_READ_CAPACITY_16:
			वापस 0;
		शेष:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
			वापस 1;
		पूर्ण
	हाल MAINTEन_अंकCE_IN:
		चयन (cdb[1] & 0x1f) अणु
		हाल MI_REPORT_TARGET_PGS:
			वापस 0;
		शेष:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
			वापस 1;
		पूर्ण
	हाल MAINTEन_अंकCE_OUT:
		चयन (cdb[1]) अणु
		हाल MO_SET_TARGET_PGS:
			वापस 0;
		शेष:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
			वापस 1;
		पूर्ण
	हाल REQUEST_SENSE:
	हाल PERSISTENT_RESERVE_IN:
	हाल PERSISTENT_RESERVE_OUT:
	हाल READ_BUFFER:
	हाल WRITE_BUFFER:
		वापस 0;
	शेष:
		set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_STANDBY);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक core_alua_state_unavailable(
	काष्ठा se_cmd *cmd,
	अचिन्हित अक्षर *cdb)
अणु
	/*
	 * Allowed CDBs क्रम ALUA_ACCESS_STATE_UNAVAILABLE as defined by
	 * spc4r17 section 5.9.2.4.5
	 */
	चयन (cdb[0]) अणु
	हाल INQUIRY:
	हाल REPORT_LUNS:
		वापस 0;
	हाल MAINTEन_अंकCE_IN:
		चयन (cdb[1] & 0x1f) अणु
		हाल MI_REPORT_TARGET_PGS:
			वापस 0;
		शेष:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_UNAVAILABLE);
			वापस 1;
		पूर्ण
	हाल MAINTEन_अंकCE_OUT:
		चयन (cdb[1]) अणु
		हाल MO_SET_TARGET_PGS:
			वापस 0;
		शेष:
			set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_UNAVAILABLE);
			वापस 1;
		पूर्ण
	हाल REQUEST_SENSE:
	हाल READ_BUFFER:
	हाल WRITE_BUFFER:
		वापस 0;
	शेष:
		set_ascq(cmd, ASCQ_04H_ALUA_TG_PT_UNAVAILABLE);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक core_alua_state_transition(
	काष्ठा se_cmd *cmd,
	अचिन्हित अक्षर *cdb)
अणु
	/*
	 * Allowed CDBs क्रम ALUA_ACCESS_STATE_TRANSITION as defined by
	 * spc4r17 section 5.9.2.5
	 */
	चयन (cdb[0]) अणु
	हाल INQUIRY:
	हाल REPORT_LUNS:
		वापस 0;
	हाल MAINTEन_अंकCE_IN:
		चयन (cdb[1] & 0x1f) अणु
		हाल MI_REPORT_TARGET_PGS:
			वापस 0;
		शेष:
			set_ascq(cmd, ASCQ_04H_ALUA_STATE_TRANSITION);
			वापस 1;
		पूर्ण
	हाल REQUEST_SENSE:
	हाल READ_BUFFER:
	हाल WRITE_BUFFER:
		वापस 0;
	शेष:
		set_ascq(cmd, ASCQ_04H_ALUA_STATE_TRANSITION);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * वापस 1: Is used to संकेत LUN not accessible, and check condition/not पढ़ोy
 * वापस 0: Used to संकेत success
 * वापस -1: Used to संकेत failure, and invalid cdb field
 */
sense_reason_t
target_alua_state_check(काष्ठा se_cmd *cmd)
अणु
	काष्ठा se_device *dev = cmd->se_dev;
	अचिन्हित अक्षर *cdb = cmd->t_task_cdb;
	काष्ठा se_lun *lun = cmd->se_lun;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	पूर्णांक out_alua_state, nonop_delay_msecs;

	अगर (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE)
		वापस 0;
	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA)
		वापस 0;

	/*
	 * First, check क्रम a काष्ठा se_port specअगरic secondary ALUA target port
	 * access state: OFFLINE
	 */
	अगर (atomic_पढ़ो(&lun->lun_tg_pt_secondary_offline)) अणु
		pr_debug("ALUA: Got secondary offline status for local"
				" target port\n");
		set_ascq(cmd, ASCQ_04H_ALUA_OFFLINE);
		वापस TCM_CHECK_CONDITION_NOT_READY;
	पूर्ण

	अगर (!lun->lun_tg_pt_gp)
		वापस 0;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	out_alua_state = tg_pt_gp->tg_pt_gp_alua_access_state;
	nonop_delay_msecs = tg_pt_gp->tg_pt_gp_nonop_delay_msecs;

	// XXX: keeps using tg_pt_gp witout reference after unlock
	spin_unlock(&lun->lun_tg_pt_gp_lock);
	/*
	 * Process ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED in a separate conditional
	 * statement so the compiler knows explicitly to check this हाल first.
	 * For the Optimized ALUA access state हाल, we want to process the
	 * incoming fabric cmd ASAP..
	 */
	अगर (out_alua_state == ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED)
		वापस 0;

	चयन (out_alua_state) अणु
	हाल ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		core_alua_state_nonoptimized(cmd, cdb, nonop_delay_msecs);
		अवरोध;
	हाल ALUA_ACCESS_STATE_STANDBY:
		अगर (core_alua_state_standby(cmd, cdb))
			वापस TCM_CHECK_CONDITION_NOT_READY;
		अवरोध;
	हाल ALUA_ACCESS_STATE_UNAVAILABLE:
		अगर (core_alua_state_unavailable(cmd, cdb))
			वापस TCM_CHECK_CONDITION_NOT_READY;
		अवरोध;
	हाल ALUA_ACCESS_STATE_TRANSITION:
		अगर (core_alua_state_transition(cmd, cdb))
			वापस TCM_CHECK_CONDITION_NOT_READY;
		अवरोध;
	हाल ALUA_ACCESS_STATE_LBA_DEPENDENT:
		अगर (core_alua_state_lba_dependent(cmd, tg_pt_gp))
			वापस TCM_CHECK_CONDITION_NOT_READY;
		अवरोध;
	/*
	 * OFFLINE is a secondary ALUA target port group access state, that is
	 * handled above with काष्ठा se_lun->lun_tg_pt_secondary_offline=1
	 */
	हाल ALUA_ACCESS_STATE_OFFLINE:
	शेष:
		pr_err("Unknown ALUA access state: 0x%02x\n",
				out_alua_state);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check implicit and explicit ALUA state change request.
 */
अटल sense_reason_t
core_alua_check_transition(पूर्णांक state, पूर्णांक valid, पूर्णांक *primary, पूर्णांक explicit)
अणु
	/*
	 * OPTIMIZED, NON-OPTIMIZED, STANDBY and UNAVAILABLE are
	 * defined as primary target port asymmetric access states.
	 */
	चयन (state) अणु
	हाल ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED:
		अगर (!(valid & ALUA_AO_SUP))
			जाओ not_supported;
		*primary = 1;
		अवरोध;
	हाल ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		अगर (!(valid & ALUA_AN_SUP))
			जाओ not_supported;
		*primary = 1;
		अवरोध;
	हाल ALUA_ACCESS_STATE_STANDBY:
		अगर (!(valid & ALUA_S_SUP))
			जाओ not_supported;
		*primary = 1;
		अवरोध;
	हाल ALUA_ACCESS_STATE_UNAVAILABLE:
		अगर (!(valid & ALUA_U_SUP))
			जाओ not_supported;
		*primary = 1;
		अवरोध;
	हाल ALUA_ACCESS_STATE_LBA_DEPENDENT:
		अगर (!(valid & ALUA_LBD_SUP))
			जाओ not_supported;
		*primary = 1;
		अवरोध;
	हाल ALUA_ACCESS_STATE_OFFLINE:
		/*
		 * OFFLINE state is defined as a secondary target port
		 * asymmetric access state.
		 */
		अगर (!(valid & ALUA_O_SUP))
			जाओ not_supported;
		*primary = 0;
		अवरोध;
	हाल ALUA_ACCESS_STATE_TRANSITION:
		अगर (!(valid & ALUA_T_SUP) || explicit)
			/*
			 * Transitioning is set पूर्णांकernally and by tcmu daemon,
			 * and cannot be selected through a STPG.
			 */
			जाओ not_supported;
		*primary = 0;
		अवरोध;
	शेष:
		pr_err("Unknown ALUA access state: 0x%02x\n", state);
		वापस TCM_INVALID_PARAMETER_LIST;
	पूर्ण

	वापस 0;

not_supported:
	pr_err("ALUA access state %s not supported",
	       core_alua_dump_state(state));
	वापस TCM_INVALID_PARAMETER_LIST;
पूर्ण

अटल अक्षर *core_alua_dump_state(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED:
		वापस "Active/Optimized";
	हाल ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		वापस "Active/NonOptimized";
	हाल ALUA_ACCESS_STATE_LBA_DEPENDENT:
		वापस "LBA Dependent";
	हाल ALUA_ACCESS_STATE_STANDBY:
		वापस "Standby";
	हाल ALUA_ACCESS_STATE_UNAVAILABLE:
		वापस "Unavailable";
	हाल ALUA_ACCESS_STATE_OFFLINE:
		वापस "Offline";
	हाल ALUA_ACCESS_STATE_TRANSITION:
		वापस "Transitioning";
	शेष:
		वापस "Unknown";
	पूर्ण

	वापस शून्य;
पूर्ण

अक्षर *core_alua_dump_status(पूर्णांक status)
अणु
	चयन (status) अणु
	हाल ALUA_STATUS_NONE:
		वापस "None";
	हाल ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG:
		वापस "Altered by Explicit STPG";
	हाल ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA:
		वापस "Altered by Implicit ALUA";
	शेष:
		वापस "Unknown";
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Used by fabric modules to determine when we need to delay processing
 * क्रम the Active/NonOptimized paths..
 */
पूर्णांक core_alua_check_nonop_delay(
	काष्ठा se_cmd *cmd)
अणु
	अगर (!(cmd->se_cmd_flags & SCF_ALUA_NON_OPTIMIZED))
		वापस 0;
	/*
	 * The ALUA Active/NonOptimized access state delay can be disabled
	 * in via configfs with a value of zero
	 */
	अगर (!cmd->alua_nonop_delay)
		वापस 0;
	/*
	 * काष्ठा se_cmd->alua_nonop_delay माला_लो set by a target port group
	 * defined पूर्णांकerval in core_alua_state_nonoptimized()
	 */
	msleep_पूर्णांकerruptible(cmd->alua_nonop_delay);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(core_alua_check_nonop_delay);

अटल पूर्णांक core_alua_ग_लिखो_tpg_metadata(
	स्थिर अक्षर *path,
	अचिन्हित अक्षर *md_buf,
	u32 md_buf_len)
अणु
	काष्ठा file *file = filp_खोलो(path, O_RDWR | O_CREAT | O_TRUNC, 0600);
	loff_t pos = 0;
	पूर्णांक ret;

	अगर (IS_ERR(file)) अणु
		pr_err("filp_open(%s) for ALUA metadata failed\n", path);
		वापस -ENODEV;
	पूर्ण
	ret = kernel_ग_लिखो(file, md_buf, md_buf_len, &pos);
	अगर (ret < 0)
		pr_err("Error writing ALUA metadata file: %s\n", path);
	fput(file);
	वापस (ret < 0) ? -EIO : 0;
पूर्ण

अटल पूर्णांक core_alua_update_tpg_primary_metadata(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	अचिन्हित अक्षर *md_buf;
	काष्ठा t10_wwn *wwn = &tg_pt_gp->tg_pt_gp_dev->t10_wwn;
	अक्षर *path;
	पूर्णांक len, rc;

	lockdep_निश्चित_held(&tg_pt_gp->tg_pt_gp_transition_mutex);

	md_buf = kzalloc(ALUA_MD_BUF_LEN, GFP_KERNEL);
	अगर (!md_buf) अणु
		pr_err("Unable to allocate buf for ALUA metadata\n");
		वापस -ENOMEM;
	पूर्ण

	len = snम_लिखो(md_buf, ALUA_MD_BUF_LEN,
			"tg_pt_gp_id=%hu\n"
			"alua_access_state=0x%02x\n"
			"alua_access_status=0x%02x\n",
			tg_pt_gp->tg_pt_gp_id,
			tg_pt_gp->tg_pt_gp_alua_access_state,
			tg_pt_gp->tg_pt_gp_alua_access_status);

	rc = -ENOMEM;
	path = kaप्र_लिखो(GFP_KERNEL, "%s/alua/tpgs_%s/%s", db_root,
			&wwn->unit_serial[0],
			config_item_name(&tg_pt_gp->tg_pt_gp_group.cg_item));
	अगर (path) अणु
		rc = core_alua_ग_लिखो_tpg_metadata(path, md_buf, len);
		kमुक्त(path);
	पूर्ण
	kमुक्त(md_buf);
	वापस rc;
पूर्ण

अटल व्योम core_alua_queue_state_change_ua(काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	काष्ठा se_dev_entry *se_deve;
	काष्ठा se_lun *lun;
	काष्ठा se_lun_acl *lacl;

	spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	list_क्रम_each_entry(lun, &tg_pt_gp->tg_pt_gp_lun_list,
				lun_tg_pt_gp_link) अणु
		/*
		 * After an implicit target port asymmetric access state
		 * change, a device server shall establish a unit attention
		 * condition क्रम the initiator port associated with every I_T
		 * nexus with the additional sense code set to ASYMMETRIC
		 * ACCESS STATE CHANGED.
		 *
		 * After an explicit target port asymmetric access state
		 * change, a device server shall establish a unit attention
		 * condition with the additional sense code set to ASYMMETRIC
		 * ACCESS STATE CHANGED क्रम the initiator port associated with
		 * every I_T nexus other than the I_T nexus on which the SET
		 * TARGET PORT GROUPS command
		 */
		अगर (!percpu_ref_tryget_live(&lun->lun_ref))
			जारी;
		spin_unlock(&tg_pt_gp->tg_pt_gp_lock);

		spin_lock(&lun->lun_deve_lock);
		list_क्रम_each_entry(se_deve, &lun->lun_deve_list, lun_link) अणु
			lacl = rcu_dereference_check(se_deve->se_lun_acl,
					lockdep_is_held(&lun->lun_deve_lock));

			/*
			 * spc4r37 p.242:
			 * After an explicit target port asymmetric access
			 * state change, a device server shall establish a
			 * unit attention condition with the additional sense
			 * code set to ASYMMETRIC ACCESS STATE CHANGED क्रम
			 * the initiator port associated with every I_T nexus
			 * other than the I_T nexus on which the SET TARGET
			 * PORT GROUPS command was received.
			 */
			अगर ((tg_pt_gp->tg_pt_gp_alua_access_status ==
			     ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG) &&
			   (tg_pt_gp->tg_pt_gp_alua_lun != शून्य) &&
			    (tg_pt_gp->tg_pt_gp_alua_lun == lun))
				जारी;

			/*
			 * se_deve->se_lun_acl poपूर्णांकer may be शून्य क्रम a
			 * entry created without explicit Node+MappedLUN ACLs
			 */
			अगर (lacl && (tg_pt_gp->tg_pt_gp_alua_nacl != शून्य) &&
			    (tg_pt_gp->tg_pt_gp_alua_nacl == lacl->se_lun_nacl))
				जारी;

			core_scsi3_ua_allocate(se_deve, 0x2A,
				ASCQ_2AH_ASYMMETRIC_ACCESS_STATE_CHANGED);
		पूर्ण
		spin_unlock(&lun->lun_deve_lock);

		spin_lock(&tg_pt_gp->tg_pt_gp_lock);
		percpu_ref_put(&lun->lun_ref);
	पूर्ण
	spin_unlock(&tg_pt_gp->tg_pt_gp_lock);
पूर्ण

अटल पूर्णांक core_alua_करो_transition_tg_pt(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	पूर्णांक new_state,
	पूर्णांक explicit)
अणु
	पूर्णांक prev_state;

	mutex_lock(&tg_pt_gp->tg_pt_gp_transition_mutex);
	/* Nothing to be करोne here */
	अगर (tg_pt_gp->tg_pt_gp_alua_access_state == new_state) अणु
		mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
		वापस 0;
	पूर्ण

	अगर (explicit && new_state == ALUA_ACCESS_STATE_TRANSITION) अणु
		mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
		वापस -EAGAIN;
	पूर्ण

	/*
	 * Save the old primary ALUA access state, and set the current state
	 * to ALUA_ACCESS_STATE_TRANSITION.
	 */
	prev_state = tg_pt_gp->tg_pt_gp_alua_access_state;
	tg_pt_gp->tg_pt_gp_alua_access_state = ALUA_ACCESS_STATE_TRANSITION;
	tg_pt_gp->tg_pt_gp_alua_access_status = (explicit) ?
				ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG :
				ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA;

	core_alua_queue_state_change_ua(tg_pt_gp);

	अगर (new_state == ALUA_ACCESS_STATE_TRANSITION) अणु
		mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
		वापस 0;
	पूर्ण

	/*
	 * Check क्रम the optional ALUA primary state transition delay
	 */
	अगर (tg_pt_gp->tg_pt_gp_trans_delay_msecs != 0)
		msleep_पूर्णांकerruptible(tg_pt_gp->tg_pt_gp_trans_delay_msecs);

	/*
	 * Set the current primary ALUA access state to the requested new state
	 */
	tg_pt_gp->tg_pt_gp_alua_access_state = new_state;

	/*
	 * Update the ALUA metadata buf that has been allocated in
	 * core_alua_करो_port_transition(), this metadata will be written
	 * to काष्ठा file.
	 *
	 * Note that there is the हाल where we करो not want to update the
	 * metadata when the saved metadata is being parsed in userspace
	 * when setting the existing port access state and access status.
	 *
	 * Also note that the failure to ग_लिखो out the ALUA metadata to
	 * काष्ठा file करोes NOT affect the actual ALUA transition.
	 */
	अगर (tg_pt_gp->tg_pt_gp_ग_लिखो_metadata) अणु
		core_alua_update_tpg_primary_metadata(tg_pt_gp);
	पूर्ण

	pr_debug("Successful %s ALUA transition TG PT Group: %s ID: %hu"
		" from primary access state %s to %s\n", (explicit) ? "explicit" :
		"implicit", config_item_name(&tg_pt_gp->tg_pt_gp_group.cg_item),
		tg_pt_gp->tg_pt_gp_id,
		core_alua_dump_state(prev_state),
		core_alua_dump_state(new_state));

	core_alua_queue_state_change_ua(tg_pt_gp);

	mutex_unlock(&tg_pt_gp->tg_pt_gp_transition_mutex);
	वापस 0;
पूर्ण

पूर्णांक core_alua_करो_port_transition(
	काष्ठा t10_alua_tg_pt_gp *l_tg_pt_gp,
	काष्ठा se_device *l_dev,
	काष्ठा se_lun *l_lun,
	काष्ठा se_node_acl *l_nacl,
	पूर्णांक new_state,
	पूर्णांक explicit)
अणु
	काष्ठा se_device *dev;
	काष्ठा t10_alua_lu_gp *lu_gp;
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem, *local_lu_gp_mem;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	पूर्णांक primary, valid_states, rc = 0;

	अगर (l_dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA)
		वापस -ENODEV;

	valid_states = l_tg_pt_gp->tg_pt_gp_alua_supported_states;
	अगर (core_alua_check_transition(new_state, valid_states, &primary,
				       explicit) != 0)
		वापस -EINVAL;

	local_lu_gp_mem = l_dev->dev_alua_lu_gp_mem;
	spin_lock(&local_lu_gp_mem->lu_gp_mem_lock);
	lu_gp = local_lu_gp_mem->lu_gp;
	atomic_inc(&lu_gp->lu_gp_ref_cnt);
	spin_unlock(&local_lu_gp_mem->lu_gp_mem_lock);
	/*
	 * For storage objects that are members of the 'default_lu_gp',
	 * we only करो transition on the passed *l_tp_pt_gp, and not
	 * on all of the matching target port groups IDs in शेष_lu_gp.
	 */
	अगर (!lu_gp->lu_gp_id) अणु
		/*
		 * core_alua_करो_transition_tg_pt() will always वापस
		 * success.
		 */
		l_tg_pt_gp->tg_pt_gp_alua_lun = l_lun;
		l_tg_pt_gp->tg_pt_gp_alua_nacl = l_nacl;
		rc = core_alua_करो_transition_tg_pt(l_tg_pt_gp,
						   new_state, explicit);
		atomic_dec_mb(&lu_gp->lu_gp_ref_cnt);
		वापस rc;
	पूर्ण
	/*
	 * For all other LU groups aside from 'default_lu_gp', walk all of
	 * the associated storage objects looking क्रम a matching target port
	 * group ID from the local target port group.
	 */
	spin_lock(&lu_gp->lu_gp_lock);
	list_क्रम_each_entry(lu_gp_mem, &lu_gp->lu_gp_mem_list,
				lu_gp_mem_list) अणु

		dev = lu_gp_mem->lu_gp_mem_dev;
		atomic_inc_mb(&lu_gp_mem->lu_gp_mem_ref_cnt);
		spin_unlock(&lu_gp->lu_gp_lock);

		spin_lock(&dev->t10_alua.tg_pt_gps_lock);
		list_क्रम_each_entry(tg_pt_gp,
				&dev->t10_alua.tg_pt_gps_list,
				tg_pt_gp_list) अणु

			अगर (!tg_pt_gp->tg_pt_gp_valid_id)
				जारी;
			/*
			 * If the target behavior port asymmetric access state
			 * is changed क्रम any target port group accessible via
			 * a logical unit within a LU group, the target port
			 * behavior group asymmetric access states क्रम the same
			 * target port group accessible via other logical units
			 * in that LU group will also change.
			 */
			अगर (l_tg_pt_gp->tg_pt_gp_id != tg_pt_gp->tg_pt_gp_id)
				जारी;

			अगर (l_tg_pt_gp == tg_pt_gp) अणु
				tg_pt_gp->tg_pt_gp_alua_lun = l_lun;
				tg_pt_gp->tg_pt_gp_alua_nacl = l_nacl;
			पूर्ण अन्यथा अणु
				tg_pt_gp->tg_pt_gp_alua_lun = शून्य;
				tg_pt_gp->tg_pt_gp_alua_nacl = शून्य;
			पूर्ण
			atomic_inc_mb(&tg_pt_gp->tg_pt_gp_ref_cnt);
			spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
			/*
			 * core_alua_करो_transition_tg_pt() will always वापस
			 * success.
			 */
			rc = core_alua_करो_transition_tg_pt(tg_pt_gp,
					new_state, explicit);

			spin_lock(&dev->t10_alua.tg_pt_gps_lock);
			atomic_dec_mb(&tg_pt_gp->tg_pt_gp_ref_cnt);
			अगर (rc)
				अवरोध;
		पूर्ण
		spin_unlock(&dev->t10_alua.tg_pt_gps_lock);

		spin_lock(&lu_gp->lu_gp_lock);
		atomic_dec_mb(&lu_gp_mem->lu_gp_mem_ref_cnt);
	पूर्ण
	spin_unlock(&lu_gp->lu_gp_lock);

	अगर (!rc) अणु
		pr_debug("Successfully processed LU Group: %s all ALUA TG PT"
			 " Group IDs: %hu %s transition to primary state: %s\n",
			 config_item_name(&lu_gp->lu_gp_group.cg_item),
			 l_tg_pt_gp->tg_pt_gp_id,
			 (explicit) ? "explicit" : "implicit",
			 core_alua_dump_state(new_state));
	पूर्ण

	atomic_dec_mb(&lu_gp->lu_gp_ref_cnt);
	वापस rc;
पूर्ण

अटल पूर्णांक core_alua_update_tpg_secondary_metadata(काष्ठा se_lun *lun)
अणु
	काष्ठा se_portal_group *se_tpg = lun->lun_tpg;
	अचिन्हित अक्षर *md_buf;
	अक्षर *path;
	पूर्णांक len, rc;

	mutex_lock(&lun->lun_tg_pt_md_mutex);

	md_buf = kzalloc(ALUA_MD_BUF_LEN, GFP_KERNEL);
	अगर (!md_buf) अणु
		pr_err("Unable to allocate buf for ALUA metadata\n");
		rc = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	len = snम_लिखो(md_buf, ALUA_MD_BUF_LEN, "alua_tg_pt_offline=%d\n"
			"alua_tg_pt_status=0x%02x\n",
			atomic_पढ़ो(&lun->lun_tg_pt_secondary_offline),
			lun->lun_tg_pt_secondary_stat);

	अगर (se_tpg->se_tpg_tfo->tpg_get_tag != शून्य) अणु
		path = kaप्र_लिखो(GFP_KERNEL, "%s/alua/%s/%s+%hu/lun_%llu",
				db_root, se_tpg->se_tpg_tfo->fabric_name,
				se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg),
				se_tpg->se_tpg_tfo->tpg_get_tag(se_tpg),
				lun->unpacked_lun);
	पूर्ण अन्यथा अणु
		path = kaप्र_लिखो(GFP_KERNEL, "%s/alua/%s/%s/lun_%llu",
				db_root, se_tpg->se_tpg_tfo->fabric_name,
				se_tpg->se_tpg_tfo->tpg_get_wwn(se_tpg),
				lun->unpacked_lun);
	पूर्ण
	अगर (!path) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	rc = core_alua_ग_लिखो_tpg_metadata(path, md_buf, len);
	kमुक्त(path);
out_मुक्त:
	kमुक्त(md_buf);
out_unlock:
	mutex_unlock(&lun->lun_tg_pt_md_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक core_alua_set_tg_pt_secondary_state(
	काष्ठा se_lun *lun,
	पूर्णांक explicit,
	पूर्णांक offline)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	पूर्णांक trans_delay_msecs;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	अगर (!tg_pt_gp) अणु
		spin_unlock(&lun->lun_tg_pt_gp_lock);
		pr_err("Unable to complete secondary state"
				" transition\n");
		वापस -EINVAL;
	पूर्ण
	trans_delay_msecs = tg_pt_gp->tg_pt_gp_trans_delay_msecs;
	/*
	 * Set the secondary ALUA target port access state to OFFLINE
	 * or release the previously secondary state क्रम काष्ठा se_lun
	 */
	अगर (offline)
		atomic_set(&lun->lun_tg_pt_secondary_offline, 1);
	अन्यथा
		atomic_set(&lun->lun_tg_pt_secondary_offline, 0);

	lun->lun_tg_pt_secondary_stat = (explicit) ?
			ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG :
			ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA;

	pr_debug("Successful %s ALUA transition TG PT Group: %s ID: %hu"
		" to secondary access state: %s\n", (explicit) ? "explicit" :
		"implicit", config_item_name(&tg_pt_gp->tg_pt_gp_group.cg_item),
		tg_pt_gp->tg_pt_gp_id, (offline) ? "OFFLINE" : "ONLINE");

	spin_unlock(&lun->lun_tg_pt_gp_lock);
	/*
	 * Do the optional transition delay after we set the secondary
	 * ALUA access state.
	 */
	अगर (trans_delay_msecs != 0)
		msleep_पूर्णांकerruptible(trans_delay_msecs);
	/*
	 * See अगर we need to update the ALUA fabric port metadata क्रम
	 * secondary state and status
	 */
	अगर (lun->lun_tg_pt_secondary_ग_लिखो_md)
		core_alua_update_tpg_secondary_metadata(lun);

	वापस 0;
पूर्ण

काष्ठा t10_alua_lba_map *
core_alua_allocate_lba_map(काष्ठा list_head *list,
			   u64 first_lba, u64 last_lba)
अणु
	काष्ठा t10_alua_lba_map *lba_map;

	lba_map = kmem_cache_zalloc(t10_alua_lba_map_cache, GFP_KERNEL);
	अगर (!lba_map) अणु
		pr_err("Unable to allocate struct t10_alua_lba_map\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	INIT_LIST_HEAD(&lba_map->lba_map_mem_list);
	lba_map->lba_map_first_lba = first_lba;
	lba_map->lba_map_last_lba = last_lba;

	list_add_tail(&lba_map->lba_map_list, list);
	वापस lba_map;
पूर्ण

पूर्णांक
core_alua_allocate_lba_map_mem(काष्ठा t10_alua_lba_map *lba_map,
			       पूर्णांक pg_id, पूर्णांक state)
अणु
	काष्ठा t10_alua_lba_map_member *lba_map_mem;

	list_क्रम_each_entry(lba_map_mem, &lba_map->lba_map_mem_list,
			    lba_map_mem_list) अणु
		अगर (lba_map_mem->lba_map_mem_alua_pg_id == pg_id) अणु
			pr_err("Duplicate pg_id %d in lba_map\n", pg_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	lba_map_mem = kmem_cache_zalloc(t10_alua_lba_map_mem_cache, GFP_KERNEL);
	अगर (!lba_map_mem) अणु
		pr_err("Unable to allocate struct t10_alua_lba_map_mem\n");
		वापस -ENOMEM;
	पूर्ण
	lba_map_mem->lba_map_mem_alua_state = state;
	lba_map_mem->lba_map_mem_alua_pg_id = pg_id;

	list_add_tail(&lba_map_mem->lba_map_mem_list,
		      &lba_map->lba_map_mem_list);
	वापस 0;
पूर्ण

व्योम
core_alua_मुक्त_lba_map(काष्ठा list_head *lba_list)
अणु
	काष्ठा t10_alua_lba_map *lba_map, *lba_map_पंचांगp;
	काष्ठा t10_alua_lba_map_member *lba_map_mem, *lba_map_mem_पंचांगp;

	list_क्रम_each_entry_safe(lba_map, lba_map_पंचांगp, lba_list,
				 lba_map_list) अणु
		list_क्रम_each_entry_safe(lba_map_mem, lba_map_mem_पंचांगp,
					 &lba_map->lba_map_mem_list,
					 lba_map_mem_list) अणु
			list_del(&lba_map_mem->lba_map_mem_list);
			kmem_cache_मुक्त(t10_alua_lba_map_mem_cache,
					lba_map_mem);
		पूर्ण
		list_del(&lba_map->lba_map_list);
		kmem_cache_मुक्त(t10_alua_lba_map_cache, lba_map);
	पूर्ण
पूर्ण

व्योम
core_alua_set_lba_map(काष्ठा se_device *dev, काष्ठा list_head *lba_map_list,
		      पूर्णांक segment_size, पूर्णांक segment_mult)
अणु
	काष्ठा list_head old_lba_map_list;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	पूर्णांक activate = 0, supported;

	INIT_LIST_HEAD(&old_lba_map_list);
	spin_lock(&dev->t10_alua.lba_map_lock);
	dev->t10_alua.lba_map_segment_size = segment_size;
	dev->t10_alua.lba_map_segment_multiplier = segment_mult;
	list_splice_init(&dev->t10_alua.lba_map_list, &old_lba_map_list);
	अगर (lba_map_list) अणु
		list_splice_init(lba_map_list, &dev->t10_alua.lba_map_list);
		activate = 1;
	पूर्ण
	spin_unlock(&dev->t10_alua.lba_map_lock);
	spin_lock(&dev->t10_alua.tg_pt_gps_lock);
	list_क्रम_each_entry(tg_pt_gp, &dev->t10_alua.tg_pt_gps_list,
			    tg_pt_gp_list) अणु

		अगर (!tg_pt_gp->tg_pt_gp_valid_id)
			जारी;
		supported = tg_pt_gp->tg_pt_gp_alua_supported_states;
		अगर (activate)
			supported |= ALUA_LBD_SUP;
		अन्यथा
			supported &= ~ALUA_LBD_SUP;
		tg_pt_gp->tg_pt_gp_alua_supported_states = supported;
	पूर्ण
	spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
	core_alua_मुक्त_lba_map(&old_lba_map_list);
पूर्ण

काष्ठा t10_alua_lu_gp *
core_alua_allocate_lu_gp(स्थिर अक्षर *name, पूर्णांक def_group)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp;

	lu_gp = kmem_cache_zalloc(t10_alua_lu_gp_cache, GFP_KERNEL);
	अगर (!lu_gp) अणु
		pr_err("Unable to allocate struct t10_alua_lu_gp\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	INIT_LIST_HEAD(&lu_gp->lu_gp_node);
	INIT_LIST_HEAD(&lu_gp->lu_gp_mem_list);
	spin_lock_init(&lu_gp->lu_gp_lock);
	atomic_set(&lu_gp->lu_gp_ref_cnt, 0);

	अगर (def_group) अणु
		lu_gp->lu_gp_id = alua_lu_gps_counter++;
		lu_gp->lu_gp_valid_id = 1;
		alua_lu_gps_count++;
	पूर्ण

	वापस lu_gp;
पूर्ण

पूर्णांक core_alua_set_lu_gp_id(काष्ठा t10_alua_lu_gp *lu_gp, u16 lu_gp_id)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp_पंचांगp;
	u16 lu_gp_id_पंचांगp;
	/*
	 * The lu_gp->lu_gp_id may only be set once..
	 */
	अगर (lu_gp->lu_gp_valid_id) अणु
		pr_warn("ALUA LU Group already has a valid ID,"
			" ignoring request\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock(&lu_gps_lock);
	अगर (alua_lu_gps_count == 0x0000ffff) अणु
		pr_err("Maximum ALUA alua_lu_gps_count:"
				" 0x0000ffff reached\n");
		spin_unlock(&lu_gps_lock);
		kmem_cache_मुक्त(t10_alua_lu_gp_cache, lu_gp);
		वापस -ENOSPC;
	पूर्ण
again:
	lu_gp_id_पंचांगp = (lu_gp_id != 0) ? lu_gp_id :
				alua_lu_gps_counter++;

	list_क्रम_each_entry(lu_gp_पंचांगp, &lu_gps_list, lu_gp_node) अणु
		अगर (lu_gp_पंचांगp->lu_gp_id == lu_gp_id_पंचांगp) अणु
			अगर (!lu_gp_id)
				जाओ again;

			pr_warn("ALUA Logical Unit Group ID: %hu"
				" already exists, ignoring request\n",
				lu_gp_id);
			spin_unlock(&lu_gps_lock);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	lu_gp->lu_gp_id = lu_gp_id_पंचांगp;
	lu_gp->lu_gp_valid_id = 1;
	list_add_tail(&lu_gp->lu_gp_node, &lu_gps_list);
	alua_lu_gps_count++;
	spin_unlock(&lu_gps_lock);

	वापस 0;
पूर्ण

अटल काष्ठा t10_alua_lu_gp_member *
core_alua_allocate_lu_gp_mem(काष्ठा se_device *dev)
अणु
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem;

	lu_gp_mem = kmem_cache_zalloc(t10_alua_lu_gp_mem_cache, GFP_KERNEL);
	अगर (!lu_gp_mem) अणु
		pr_err("Unable to allocate struct t10_alua_lu_gp_member\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	INIT_LIST_HEAD(&lu_gp_mem->lu_gp_mem_list);
	spin_lock_init(&lu_gp_mem->lu_gp_mem_lock);
	atomic_set(&lu_gp_mem->lu_gp_mem_ref_cnt, 0);

	lu_gp_mem->lu_gp_mem_dev = dev;
	dev->dev_alua_lu_gp_mem = lu_gp_mem;

	वापस lu_gp_mem;
पूर्ण

व्योम core_alua_मुक्त_lu_gp(काष्ठा t10_alua_lu_gp *lu_gp)
अणु
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem, *lu_gp_mem_पंचांगp;
	/*
	 * Once we have reached this poपूर्णांक, config_item_put() has
	 * alपढ़ोy been called from target_core_alua_drop_lu_gp().
	 *
	 * Here, we हटाओ the *lu_gp from the global list so that
	 * no associations can be made जबतक we are releasing
	 * काष्ठा t10_alua_lu_gp.
	 */
	spin_lock(&lu_gps_lock);
	list_del(&lu_gp->lu_gp_node);
	alua_lu_gps_count--;
	spin_unlock(&lu_gps_lock);
	/*
	 * Allow काष्ठा t10_alua_lu_gp * referenced by core_alua_get_lu_gp_by_name()
	 * in target_core_configfs.c:target_core_store_alua_lu_gp() to be
	 * released with core_alua_put_lu_gp_from_name()
	 */
	जबतक (atomic_पढ़ो(&lu_gp->lu_gp_ref_cnt))
		cpu_relax();
	/*
	 * Release reference to काष्ठा t10_alua_lu_gp * from all associated
	 * काष्ठा se_device.
	 */
	spin_lock(&lu_gp->lu_gp_lock);
	list_क्रम_each_entry_safe(lu_gp_mem, lu_gp_mem_पंचांगp,
				&lu_gp->lu_gp_mem_list, lu_gp_mem_list) अणु
		अगर (lu_gp_mem->lu_gp_assoc) अणु
			list_del(&lu_gp_mem->lu_gp_mem_list);
			lu_gp->lu_gp_members--;
			lu_gp_mem->lu_gp_assoc = 0;
		पूर्ण
		spin_unlock(&lu_gp->lu_gp_lock);
		/*
		 *
		 * lu_gp_mem is associated with a single
		 * काष्ठा se_device->dev_alua_lu_gp_mem, and is released when
		 * काष्ठा se_device is released via core_alua_मुक्त_lu_gp_mem().
		 *
		 * If the passed lu_gp करोes NOT match the शेष_lu_gp, assume
		 * we want to re-associate a given lu_gp_mem with शेष_lu_gp.
		 */
		spin_lock(&lu_gp_mem->lu_gp_mem_lock);
		अगर (lu_gp != शेष_lu_gp)
			__core_alua_attach_lu_gp_mem(lu_gp_mem,
					शेष_lu_gp);
		अन्यथा
			lu_gp_mem->lu_gp = शून्य;
		spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

		spin_lock(&lu_gp->lu_gp_lock);
	पूर्ण
	spin_unlock(&lu_gp->lu_gp_lock);

	kmem_cache_मुक्त(t10_alua_lu_gp_cache, lu_gp);
पूर्ण

व्योम core_alua_मुक्त_lu_gp_mem(काष्ठा se_device *dev)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp;
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem;

	lu_gp_mem = dev->dev_alua_lu_gp_mem;
	अगर (!lu_gp_mem)
		वापस;

	जबतक (atomic_पढ़ो(&lu_gp_mem->lu_gp_mem_ref_cnt))
		cpu_relax();

	spin_lock(&lu_gp_mem->lu_gp_mem_lock);
	lu_gp = lu_gp_mem->lu_gp;
	अगर (lu_gp) अणु
		spin_lock(&lu_gp->lu_gp_lock);
		अगर (lu_gp_mem->lu_gp_assoc) अणु
			list_del(&lu_gp_mem->lu_gp_mem_list);
			lu_gp->lu_gp_members--;
			lu_gp_mem->lu_gp_assoc = 0;
		पूर्ण
		spin_unlock(&lu_gp->lu_gp_lock);
		lu_gp_mem->lu_gp = शून्य;
	पूर्ण
	spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

	kmem_cache_मुक्त(t10_alua_lu_gp_mem_cache, lu_gp_mem);
पूर्ण

काष्ठा t10_alua_lu_gp *core_alua_get_lu_gp_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा t10_alua_lu_gp *lu_gp;
	काष्ठा config_item *ci;

	spin_lock(&lu_gps_lock);
	list_क्रम_each_entry(lu_gp, &lu_gps_list, lu_gp_node) अणु
		अगर (!lu_gp->lu_gp_valid_id)
			जारी;
		ci = &lu_gp->lu_gp_group.cg_item;
		अगर (!म_भेद(config_item_name(ci), name)) अणु
			atomic_inc(&lu_gp->lu_gp_ref_cnt);
			spin_unlock(&lu_gps_lock);
			वापस lu_gp;
		पूर्ण
	पूर्ण
	spin_unlock(&lu_gps_lock);

	वापस शून्य;
पूर्ण

व्योम core_alua_put_lu_gp_from_name(काष्ठा t10_alua_lu_gp *lu_gp)
अणु
	spin_lock(&lu_gps_lock);
	atomic_dec(&lu_gp->lu_gp_ref_cnt);
	spin_unlock(&lu_gps_lock);
पूर्ण

/*
 * Called with काष्ठा t10_alua_lu_gp_member->lu_gp_mem_lock
 */
व्योम __core_alua_attach_lu_gp_mem(
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem,
	काष्ठा t10_alua_lu_gp *lu_gp)
अणु
	spin_lock(&lu_gp->lu_gp_lock);
	lu_gp_mem->lu_gp = lu_gp;
	lu_gp_mem->lu_gp_assoc = 1;
	list_add_tail(&lu_gp_mem->lu_gp_mem_list, &lu_gp->lu_gp_mem_list);
	lu_gp->lu_gp_members++;
	spin_unlock(&lu_gp->lu_gp_lock);
पूर्ण

/*
 * Called with काष्ठा t10_alua_lu_gp_member->lu_gp_mem_lock
 */
व्योम __core_alua_drop_lu_gp_mem(
	काष्ठा t10_alua_lu_gp_member *lu_gp_mem,
	काष्ठा t10_alua_lu_gp *lu_gp)
अणु
	spin_lock(&lu_gp->lu_gp_lock);
	list_del(&lu_gp_mem->lu_gp_mem_list);
	lu_gp_mem->lu_gp = शून्य;
	lu_gp_mem->lu_gp_assoc = 0;
	lu_gp->lu_gp_members--;
	spin_unlock(&lu_gp->lu_gp_lock);
पूर्ण

काष्ठा t10_alua_tg_pt_gp *core_alua_allocate_tg_pt_gp(काष्ठा se_device *dev,
		स्थिर अक्षर *name, पूर्णांक def_group)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;

	tg_pt_gp = kmem_cache_zalloc(t10_alua_tg_pt_gp_cache, GFP_KERNEL);
	अगर (!tg_pt_gp) अणु
		pr_err("Unable to allocate struct t10_alua_tg_pt_gp\n");
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&tg_pt_gp->tg_pt_gp_list);
	INIT_LIST_HEAD(&tg_pt_gp->tg_pt_gp_lun_list);
	mutex_init(&tg_pt_gp->tg_pt_gp_transition_mutex);
	spin_lock_init(&tg_pt_gp->tg_pt_gp_lock);
	atomic_set(&tg_pt_gp->tg_pt_gp_ref_cnt, 0);
	tg_pt_gp->tg_pt_gp_dev = dev;
	tg_pt_gp->tg_pt_gp_alua_access_state =
			ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED;
	/*
	 * Enable both explicit and implicit ALUA support by शेष
	 */
	tg_pt_gp->tg_pt_gp_alua_access_type =
			TPGS_EXPLICIT_ALUA | TPGS_IMPLICIT_ALUA;
	/*
	 * Set the शेष Active/NonOptimized Delay in milliseconds
	 */
	tg_pt_gp->tg_pt_gp_nonop_delay_msecs = ALUA_DEFAULT_NONOP_DELAY_MSECS;
	tg_pt_gp->tg_pt_gp_trans_delay_msecs = ALUA_DEFAULT_TRANS_DELAY_MSECS;
	tg_pt_gp->tg_pt_gp_implicit_trans_secs = ALUA_DEFAULT_IMPLICIT_TRANS_SECS;

	/*
	 * Enable all supported states
	 */
	tg_pt_gp->tg_pt_gp_alua_supported_states =
	    ALUA_T_SUP | ALUA_O_SUP |
	    ALUA_U_SUP | ALUA_S_SUP | ALUA_AN_SUP | ALUA_AO_SUP;

	अगर (def_group) अणु
		spin_lock(&dev->t10_alua.tg_pt_gps_lock);
		tg_pt_gp->tg_pt_gp_id =
				dev->t10_alua.alua_tg_pt_gps_counter++;
		tg_pt_gp->tg_pt_gp_valid_id = 1;
		dev->t10_alua.alua_tg_pt_gps_count++;
		list_add_tail(&tg_pt_gp->tg_pt_gp_list,
			      &dev->t10_alua.tg_pt_gps_list);
		spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
	पूर्ण

	वापस tg_pt_gp;
पूर्ण

पूर्णांक core_alua_set_tg_pt_gp_id(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	u16 tg_pt_gp_id)
अणु
	काष्ठा se_device *dev = tg_pt_gp->tg_pt_gp_dev;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp_पंचांगp;
	u16 tg_pt_gp_id_पंचांगp;

	/*
	 * The tg_pt_gp->tg_pt_gp_id may only be set once..
	 */
	अगर (tg_pt_gp->tg_pt_gp_valid_id) अणु
		pr_warn("ALUA TG PT Group already has a valid ID,"
			" ignoring request\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock(&dev->t10_alua.tg_pt_gps_lock);
	अगर (dev->t10_alua.alua_tg_pt_gps_count == 0x0000ffff) अणु
		pr_err("Maximum ALUA alua_tg_pt_gps_count:"
			" 0x0000ffff reached\n");
		spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
		kmem_cache_मुक्त(t10_alua_tg_pt_gp_cache, tg_pt_gp);
		वापस -ENOSPC;
	पूर्ण
again:
	tg_pt_gp_id_पंचांगp = (tg_pt_gp_id != 0) ? tg_pt_gp_id :
			dev->t10_alua.alua_tg_pt_gps_counter++;

	list_क्रम_each_entry(tg_pt_gp_पंचांगp, &dev->t10_alua.tg_pt_gps_list,
			tg_pt_gp_list) अणु
		अगर (tg_pt_gp_पंचांगp->tg_pt_gp_id == tg_pt_gp_id_पंचांगp) अणु
			अगर (!tg_pt_gp_id)
				जाओ again;

			pr_err("ALUA Target Port Group ID: %hu already"
				" exists, ignoring request\n", tg_pt_gp_id);
			spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	tg_pt_gp->tg_pt_gp_id = tg_pt_gp_id_पंचांगp;
	tg_pt_gp->tg_pt_gp_valid_id = 1;
	list_add_tail(&tg_pt_gp->tg_pt_gp_list,
			&dev->t10_alua.tg_pt_gps_list);
	dev->t10_alua.alua_tg_pt_gps_count++;
	spin_unlock(&dev->t10_alua.tg_pt_gps_lock);

	वापस 0;
पूर्ण

व्योम core_alua_मुक्त_tg_pt_gp(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	काष्ठा se_device *dev = tg_pt_gp->tg_pt_gp_dev;
	काष्ठा se_lun *lun, *next;

	/*
	 * Once we have reached this poपूर्णांक, config_item_put() has alपढ़ोy
	 * been called from target_core_alua_drop_tg_pt_gp().
	 *
	 * Here we हटाओ *tg_pt_gp from the global list so that
	 * no associations *OR* explicit ALUA via SET_TARGET_PORT_GROUPS
	 * can be made जबतक we are releasing काष्ठा t10_alua_tg_pt_gp.
	 */
	spin_lock(&dev->t10_alua.tg_pt_gps_lock);
	अगर (tg_pt_gp->tg_pt_gp_valid_id) अणु
		list_del(&tg_pt_gp->tg_pt_gp_list);
		dev->t10_alua.alua_tg_pt_gps_count--;
	पूर्ण
	spin_unlock(&dev->t10_alua.tg_pt_gps_lock);

	/*
	 * Allow a काष्ठा t10_alua_tg_pt_gp_member * referenced by
	 * core_alua_get_tg_pt_gp_by_name() in
	 * target_core_configfs.c:target_core_store_alua_tg_pt_gp()
	 * to be released with core_alua_put_tg_pt_gp_from_name().
	 */
	जबतक (atomic_पढ़ो(&tg_pt_gp->tg_pt_gp_ref_cnt))
		cpu_relax();

	/*
	 * Release reference to काष्ठा t10_alua_tg_pt_gp from all associated
	 * काष्ठा se_port.
	 */
	spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	list_क्रम_each_entry_safe(lun, next,
			&tg_pt_gp->tg_pt_gp_lun_list, lun_tg_pt_gp_link) अणु
		list_del_init(&lun->lun_tg_pt_gp_link);
		tg_pt_gp->tg_pt_gp_members--;

		spin_unlock(&tg_pt_gp->tg_pt_gp_lock);
		/*
		 * If the passed tg_pt_gp करोes NOT match the शेष_tg_pt_gp,
		 * assume we want to re-associate a given tg_pt_gp_mem with
		 * शेष_tg_pt_gp.
		 */
		spin_lock(&lun->lun_tg_pt_gp_lock);
		अगर (tg_pt_gp != dev->t10_alua.शेष_tg_pt_gp) अणु
			__target_attach_tg_pt_gp(lun,
					dev->t10_alua.शेष_tg_pt_gp);
		पूर्ण अन्यथा
			lun->lun_tg_pt_gp = शून्य;
		spin_unlock(&lun->lun_tg_pt_gp_lock);

		spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	पूर्ण
	spin_unlock(&tg_pt_gp->tg_pt_gp_lock);

	kmem_cache_मुक्त(t10_alua_tg_pt_gp_cache, tg_pt_gp);
पूर्ण

अटल काष्ठा t10_alua_tg_pt_gp *core_alua_get_tg_pt_gp_by_name(
		काष्ठा se_device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	काष्ठा config_item *ci;

	spin_lock(&dev->t10_alua.tg_pt_gps_lock);
	list_क्रम_each_entry(tg_pt_gp, &dev->t10_alua.tg_pt_gps_list,
			tg_pt_gp_list) अणु
		अगर (!tg_pt_gp->tg_pt_gp_valid_id)
			जारी;
		ci = &tg_pt_gp->tg_pt_gp_group.cg_item;
		अगर (!म_भेद(config_item_name(ci), name)) अणु
			atomic_inc(&tg_pt_gp->tg_pt_gp_ref_cnt);
			spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
			वापस tg_pt_gp;
		पूर्ण
	पूर्ण
	spin_unlock(&dev->t10_alua.tg_pt_gps_lock);

	वापस शून्य;
पूर्ण

अटल व्योम core_alua_put_tg_pt_gp_from_name(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	काष्ठा se_device *dev = tg_pt_gp->tg_pt_gp_dev;

	spin_lock(&dev->t10_alua.tg_pt_gps_lock);
	atomic_dec(&tg_pt_gp->tg_pt_gp_ref_cnt);
	spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
पूर्ण

अटल व्योम __target_attach_tg_pt_gp(काष्ठा se_lun *lun,
		काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	काष्ठा se_dev_entry *se_deve;

	निश्चित_spin_locked(&lun->lun_tg_pt_gp_lock);

	spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	lun->lun_tg_pt_gp = tg_pt_gp;
	list_add_tail(&lun->lun_tg_pt_gp_link, &tg_pt_gp->tg_pt_gp_lun_list);
	tg_pt_gp->tg_pt_gp_members++;
	spin_lock(&lun->lun_deve_lock);
	list_क्रम_each_entry(se_deve, &lun->lun_deve_list, lun_link)
		core_scsi3_ua_allocate(se_deve, 0x3f,
				       ASCQ_3FH_INQUIRY_DATA_HAS_CHANGED);
	spin_unlock(&lun->lun_deve_lock);
	spin_unlock(&tg_pt_gp->tg_pt_gp_lock);
पूर्ण

व्योम target_attach_tg_pt_gp(काष्ठा se_lun *lun,
		काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	spin_lock(&lun->lun_tg_pt_gp_lock);
	__target_attach_tg_pt_gp(lun, tg_pt_gp);
	spin_unlock(&lun->lun_tg_pt_gp_lock);
पूर्ण

अटल व्योम __target_detach_tg_pt_gp(काष्ठा se_lun *lun,
		काष्ठा t10_alua_tg_pt_gp *tg_pt_gp)
अणु
	निश्चित_spin_locked(&lun->lun_tg_pt_gp_lock);

	spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	list_del_init(&lun->lun_tg_pt_gp_link);
	tg_pt_gp->tg_pt_gp_members--;
	spin_unlock(&tg_pt_gp->tg_pt_gp_lock);

	lun->lun_tg_pt_gp = शून्य;
पूर्ण

व्योम target_detach_tg_pt_gp(काष्ठा se_lun *lun)
अणु
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	अगर (tg_pt_gp)
		__target_detach_tg_pt_gp(lun, tg_pt_gp);
	spin_unlock(&lun->lun_tg_pt_gp_lock);
पूर्ण

sमाप_प्रकार core_alua_show_tg_pt_gp_info(काष्ठा se_lun *lun, अक्षर *page)
अणु
	काष्ठा config_item *tg_pt_ci;
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp;
	sमाप_प्रकार len = 0;

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	अगर (tg_pt_gp) अणु
		tg_pt_ci = &tg_pt_gp->tg_pt_gp_group.cg_item;
		len += प्र_लिखो(page, "TG Port Alias: %s\nTG Port Group ID:"
			" %hu\nTG Port Primary Access State: %s\nTG Port "
			"Primary Access Status: %s\nTG Port Secondary Access"
			" State: %s\nTG Port Secondary Access Status: %s\n",
			config_item_name(tg_pt_ci), tg_pt_gp->tg_pt_gp_id,
			core_alua_dump_state(
				tg_pt_gp->tg_pt_gp_alua_access_state),
			core_alua_dump_status(
				tg_pt_gp->tg_pt_gp_alua_access_status),
			atomic_पढ़ो(&lun->lun_tg_pt_secondary_offline) ?
			"Offline" : "None",
			core_alua_dump_status(lun->lun_tg_pt_secondary_stat));
	पूर्ण
	spin_unlock(&lun->lun_tg_pt_gp_lock);

	वापस len;
पूर्ण

sमाप_प्रकार core_alua_store_tg_pt_gp_info(
	काष्ठा se_lun *lun,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	काष्ठा se_portal_group *tpg = lun->lun_tpg;
	/*
	 * rcu_dereference_raw रक्षित by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	काष्ठा se_device *dev = rcu_dereference_raw(lun->lun_se_dev);
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp = शून्य, *tg_pt_gp_new = शून्य;
	अचिन्हित अक्षर buf[TG_PT_GROUP_NAME_BUF];
	पूर्णांक move = 0;

	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA ||
	    (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		वापस -ENODEV;

	अगर (count > TG_PT_GROUP_NAME_BUF) अणु
		pr_err("ALUA Target Port Group alias too large!\n");
		वापस -EINVAL;
	पूर्ण
	स_रखो(buf, 0, TG_PT_GROUP_NAME_BUF);
	स_नकल(buf, page, count);
	/*
	 * Any ALUA target port group alias besides "NULL" means we will be
	 * making a new group association.
	 */
	अगर (म_भेद(म_मालाip(buf), "NULL")) अणु
		/*
		 * core_alua_get_tg_pt_gp_by_name() will increment reference to
		 * काष्ठा t10_alua_tg_pt_gp.  This reference is released with
		 * core_alua_put_tg_pt_gp_from_name() below.
		 */
		tg_pt_gp_new = core_alua_get_tg_pt_gp_by_name(dev,
					म_मालाip(buf));
		अगर (!tg_pt_gp_new)
			वापस -ENODEV;
	पूर्ण

	spin_lock(&lun->lun_tg_pt_gp_lock);
	tg_pt_gp = lun->lun_tg_pt_gp;
	अगर (tg_pt_gp) अणु
		/*
		 * Clearing an existing tg_pt_gp association, and replacing
		 * with the शेष_tg_pt_gp.
		 */
		अगर (!tg_pt_gp_new) अणु
			pr_debug("Target_Core_ConfigFS: Moving"
				" %s/tpgt_%hu/%s from ALUA Target Port Group:"
				" alua/%s, ID: %hu back to"
				" default_tg_pt_gp\n",
				tpg->se_tpg_tfo->tpg_get_wwn(tpg),
				tpg->se_tpg_tfo->tpg_get_tag(tpg),
				config_item_name(&lun->lun_group.cg_item),
				config_item_name(
					&tg_pt_gp->tg_pt_gp_group.cg_item),
				tg_pt_gp->tg_pt_gp_id);

			__target_detach_tg_pt_gp(lun, tg_pt_gp);
			__target_attach_tg_pt_gp(lun,
					dev->t10_alua.शेष_tg_pt_gp);
			spin_unlock(&lun->lun_tg_pt_gp_lock);

			वापस count;
		पूर्ण
		__target_detach_tg_pt_gp(lun, tg_pt_gp);
		move = 1;
	पूर्ण

	__target_attach_tg_pt_gp(lun, tg_pt_gp_new);
	spin_unlock(&lun->lun_tg_pt_gp_lock);
	pr_debug("Target_Core_ConfigFS: %s %s/tpgt_%hu/%s to ALUA"
		" Target Port Group: alua/%s, ID: %hu\n", (move) ?
		"Moving" : "Adding", tpg->se_tpg_tfo->tpg_get_wwn(tpg),
		tpg->se_tpg_tfo->tpg_get_tag(tpg),
		config_item_name(&lun->lun_group.cg_item),
		config_item_name(&tg_pt_gp_new->tg_pt_gp_group.cg_item),
		tg_pt_gp_new->tg_pt_gp_id);

	core_alua_put_tg_pt_gp_from_name(tg_pt_gp_new);
	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_access_type(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	अक्षर *page)
अणु
	अगर ((tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_EXPLICIT_ALUA) &&
	    (tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_IMPLICIT_ALUA))
		वापस प्र_लिखो(page, "Implicit and Explicit\n");
	अन्यथा अगर (tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_IMPLICIT_ALUA)
		वापस प्र_लिखो(page, "Implicit\n");
	अन्यथा अगर (tg_pt_gp->tg_pt_gp_alua_access_type & TPGS_EXPLICIT_ALUA)
		वापस प्र_लिखो(page, "Explicit\n");
	अन्यथा
		वापस प्र_लिखो(page, "None\n");
पूर्ण

sमाप_प्रकार core_alua_store_access_type(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract alua_access_type\n");
		वापस ret;
	पूर्ण
	अगर ((पंचांगp != 0) && (पंचांगp != 1) && (पंचांगp != 2) && (पंचांगp != 3)) अणु
		pr_err("Illegal value for alua_access_type:"
				" %lu\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण
	अगर (पंचांगp == 3)
		tg_pt_gp->tg_pt_gp_alua_access_type =
			TPGS_IMPLICIT_ALUA | TPGS_EXPLICIT_ALUA;
	अन्यथा अगर (पंचांगp == 2)
		tg_pt_gp->tg_pt_gp_alua_access_type = TPGS_EXPLICIT_ALUA;
	अन्यथा अगर (पंचांगp == 1)
		tg_pt_gp->tg_pt_gp_alua_access_type = TPGS_IMPLICIT_ALUA;
	अन्यथा
		tg_pt_gp->tg_pt_gp_alua_access_type = 0;

	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_nonop_delay_msecs(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", tg_pt_gp->tg_pt_gp_nonop_delay_msecs);
पूर्ण

sमाप_प्रकार core_alua_store_nonop_delay_msecs(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract nonop_delay_msecs\n");
		वापस ret;
	पूर्ण
	अगर (पंचांगp > ALUA_MAX_NONOP_DELAY_MSECS) अणु
		pr_err("Passed nonop_delay_msecs: %lu, exceeds"
			" ALUA_MAX_NONOP_DELAY_MSECS: %d\n", पंचांगp,
			ALUA_MAX_NONOP_DELAY_MSECS);
		वापस -EINVAL;
	पूर्ण
	tg_pt_gp->tg_pt_gp_nonop_delay_msecs = (पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_trans_delay_msecs(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", tg_pt_gp->tg_pt_gp_trans_delay_msecs);
पूर्ण

sमाप_प्रकार core_alua_store_trans_delay_msecs(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract trans_delay_msecs\n");
		वापस ret;
	पूर्ण
	अगर (पंचांगp > ALUA_MAX_TRANS_DELAY_MSECS) अणु
		pr_err("Passed trans_delay_msecs: %lu, exceeds"
			" ALUA_MAX_TRANS_DELAY_MSECS: %d\n", पंचांगp,
			ALUA_MAX_TRANS_DELAY_MSECS);
		वापस -EINVAL;
	पूर्ण
	tg_pt_gp->tg_pt_gp_trans_delay_msecs = (पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_implicit_trans_secs(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", tg_pt_gp->tg_pt_gp_implicit_trans_secs);
पूर्ण

sमाप_प्रकार core_alua_store_implicit_trans_secs(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract implicit_trans_secs\n");
		वापस ret;
	पूर्ण
	अगर (पंचांगp > ALUA_MAX_IMPLICIT_TRANS_SECS) अणु
		pr_err("Passed implicit_trans_secs: %lu, exceeds"
			" ALUA_MAX_IMPLICIT_TRANS_SECS: %d\n", पंचांगp,
			ALUA_MAX_IMPLICIT_TRANS_SECS);
		वापस  -EINVAL;
	पूर्ण
	tg_pt_gp->tg_pt_gp_implicit_trans_secs = (पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_preferred_bit(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", tg_pt_gp->tg_pt_gp_pref);
पूर्ण

sमाप_प्रकार core_alua_store_preferred_bit(
	काष्ठा t10_alua_tg_pt_gp *tg_pt_gp,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract preferred ALUA value\n");
		वापस ret;
	पूर्ण
	अगर ((पंचांगp != 0) && (पंचांगp != 1)) अणु
		pr_err("Illegal value for preferred ALUA: %lu\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण
	tg_pt_gp->tg_pt_gp_pref = (पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_offline_bit(काष्ठा se_lun *lun, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n",
		atomic_पढ़ो(&lun->lun_tg_pt_secondary_offline));
पूर्ण

sमाप_प्रकार core_alua_store_offline_bit(
	काष्ठा se_lun *lun,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	/*
	 * rcu_dereference_raw रक्षित by se_lun->lun_group symlink
	 * reference to se_device->dev_group.
	 */
	काष्ठा se_device *dev = rcu_dereference_raw(lun->lun_se_dev);
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	अगर (dev->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_ALUA ||
	    (dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		वापस -ENODEV;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract alua_tg_pt_offline value\n");
		वापस ret;
	पूर्ण
	अगर ((पंचांगp != 0) && (पंचांगp != 1)) अणु
		pr_err("Illegal value for alua_tg_pt_offline: %lu\n",
				पंचांगp);
		वापस -EINVAL;
	पूर्ण

	ret = core_alua_set_tg_pt_secondary_state(lun, 0, (पूर्णांक)पंचांगp);
	अगर (ret < 0)
		वापस -EINVAL;

	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_secondary_status(
	काष्ठा se_lun *lun,
	अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", lun->lun_tg_pt_secondary_stat);
पूर्ण

sमाप_प्रकार core_alua_store_secondary_status(
	काष्ठा se_lun *lun,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract alua_tg_pt_status\n");
		वापस ret;
	पूर्ण
	अगर ((पंचांगp != ALUA_STATUS_NONE) &&
	    (पंचांगp != ALUA_STATUS_ALTERED_BY_EXPLICIT_STPG) &&
	    (पंचांगp != ALUA_STATUS_ALTERED_BY_IMPLICIT_ALUA)) अणु
		pr_err("Illegal value for alua_tg_pt_status: %lu\n",
				पंचांगp);
		वापस -EINVAL;
	पूर्ण
	lun->lun_tg_pt_secondary_stat = (पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

sमाप_प्रकार core_alua_show_secondary_ग_लिखो_metadata(
	काष्ठा se_lun *lun,
	अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", lun->lun_tg_pt_secondary_ग_लिखो_md);
पूर्ण

sमाप_प्रकार core_alua_store_secondary_ग_लिखो_metadata(
	काष्ठा se_lun *lun,
	स्थिर अक्षर *page,
	माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(page, 0, &पंचांगp);
	अगर (ret < 0) अणु
		pr_err("Unable to extract alua_tg_pt_write_md\n");
		वापस ret;
	पूर्ण
	अगर ((पंचांगp != 0) && (पंचांगp != 1)) अणु
		pr_err("Illegal value for alua_tg_pt_write_md:"
				" %lu\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण
	lun->lun_tg_pt_secondary_ग_लिखो_md = (पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

पूर्णांक core_setup_alua(काष्ठा se_device *dev)
अणु
	अगर (!(dev->transport_flags &
	     TRANSPORT_FLAG_PASSTHROUGH_ALUA) &&
	    !(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE)) अणु
		काष्ठा t10_alua_lu_gp_member *lu_gp_mem;

		/*
		 * Associate this काष्ठा se_device with the शेष ALUA
		 * LUN Group.
		 */
		lu_gp_mem = core_alua_allocate_lu_gp_mem(dev);
		अगर (IS_ERR(lu_gp_mem))
			वापस PTR_ERR(lu_gp_mem);

		spin_lock(&lu_gp_mem->lu_gp_mem_lock);
		__core_alua_attach_lu_gp_mem(lu_gp_mem,
				शेष_lu_gp);
		spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

		pr_debug("%s: Adding to default ALUA LU Group:"
			" core/alua/lu_gps/default_lu_gp\n",
			dev->transport->name);
	पूर्ण

	वापस 0;
पूर्ण
