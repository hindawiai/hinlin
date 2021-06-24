<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * Filename: target_core_xcopy.c
 *
 * This file contains support क्रम SPC-4 Extended-Copy offload with generic
 * TCM backends.
 *
 * Copyright (c) 2011-2013 Datera, Inc. All rights reserved.
 *
 * Author:
 * Nicholas A. Bellinger <nab@daterainc.com>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/configfs.h>
#समावेश <linux/ratelimit.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_backend.h>
#समावेश <target/target_core_fabric.h>

#समावेश "target_core_internal.h"
#समावेश "target_core_pr.h"
#समावेश "target_core_ua.h"
#समावेश "target_core_xcopy.h"

अटल काष्ठा workqueue_काष्ठा *xcopy_wq = शून्य;

अटल sense_reason_t target_parse_xcopy_cmd(काष्ठा xcopy_op *xop);

अटल पूर्णांक target_xcopy_gen_naa_ieee(काष्ठा se_device *dev, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक off = 0;

	buf[off++] = (0x6 << 4);
	buf[off++] = 0x01;
	buf[off++] = 0x40;
	buf[off] = (0x5 << 4);

	spc_parse_naa_6h_venकरोr_specअगरic(dev, &buf[off]);
	वापस 0;
पूर्ण

/**
 * target_xcopy_locate_se_dev_e4_iter - compare XCOPY NAA device identअगरiers
 *
 * @se_dev: device being considered क्रम match
 * @dev_wwn: XCOPY requested NAA dev_wwn
 * @वापस: 1 on match, 0 on no-match
 */
अटल पूर्णांक target_xcopy_locate_se_dev_e4_iter(काष्ठा se_device *se_dev,
					      स्थिर अचिन्हित अक्षर *dev_wwn)
अणु
	अचिन्हित अक्षर पंचांगp_dev_wwn[XCOPY_NAA_IEEE_REGEX_LEN];
	पूर्णांक rc;

	अगर (!se_dev->dev_attrib.emulate_3pc) अणु
		pr_debug("XCOPY: emulate_3pc disabled on se_dev %p\n", se_dev);
		वापस 0;
	पूर्ण

	स_रखो(&पंचांगp_dev_wwn[0], 0, XCOPY_NAA_IEEE_REGEX_LEN);
	target_xcopy_gen_naa_ieee(se_dev, &पंचांगp_dev_wwn[0]);

	rc = स_भेद(&पंचांगp_dev_wwn[0], dev_wwn, XCOPY_NAA_IEEE_REGEX_LEN);
	अगर (rc != 0) अणु
		pr_debug("XCOPY: skip non-matching: %*ph\n",
			 XCOPY_NAA_IEEE_REGEX_LEN, पंचांगp_dev_wwn);
		वापस 0;
	पूर्ण
	pr_debug("XCOPY 0xe4: located se_dev: %p\n", se_dev);

	वापस 1;
पूर्ण

अटल पूर्णांक target_xcopy_locate_se_dev_e4(काष्ठा se_session *sess,
					स्थिर अचिन्हित अक्षर *dev_wwn,
					काष्ठा se_device **_found_dev,
					काष्ठा percpu_ref **_found_lun_ref)
अणु
	काष्ठा se_dev_entry *deve;
	काष्ठा se_node_acl *nacl;
	काष्ठा se_lun *this_lun = शून्य;
	काष्ठा se_device *found_dev = शून्य;

	/* cmd with शून्य sess indicates no associated $FABRIC_MOD */
	अगर (!sess)
		जाओ err_out;

	pr_debug("XCOPY 0xe4: searching for: %*ph\n",
		 XCOPY_NAA_IEEE_REGEX_LEN, dev_wwn);

	nacl = sess->se_node_acl;
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(deve, &nacl->lun_entry_hlist, link) अणु
		काष्ठा se_device *this_dev;
		पूर्णांक rc;

		this_lun = rcu_dereference(deve->se_lun);
		this_dev = rcu_dereference_raw(this_lun->lun_se_dev);

		rc = target_xcopy_locate_se_dev_e4_iter(this_dev, dev_wwn);
		अगर (rc) अणु
			अगर (percpu_ref_tryget_live(&this_lun->lun_ref))
				found_dev = this_dev;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (found_dev == शून्य)
		जाओ err_out;

	pr_debug("lun_ref held for se_dev: %p se_dev->se_dev_group: %p\n",
		 found_dev, &found_dev->dev_group);
	*_found_dev = found_dev;
	*_found_lun_ref = &this_lun->lun_ref;
	वापस 0;
err_out:
	pr_debug_ratelimited("Unable to locate 0xe4 descriptor for EXTENDED_COPY\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक target_xcopy_parse_tiddesc_e4(काष्ठा se_cmd *se_cmd, काष्ठा xcopy_op *xop,
				अचिन्हित अक्षर *p, अचिन्हित लघु cscd_index)
अणु
	अचिन्हित अक्षर *desc = p;
	अचिन्हित लघु ript;
	u8 desig_len;
	/*
	 * Extract RELATIVE INITIATOR PORT IDENTIFIER
	 */
	ript = get_unaligned_be16(&desc[2]);
	pr_debug("XCOPY 0xe4: RELATIVE INITIATOR PORT IDENTIFIER: %hu\n", ript);
	/*
	 * Check क्रम supported code set, association, and designator type
	 */
	अगर ((desc[4] & 0x0f) != 0x1) अणु
		pr_err("XCOPY 0xe4: code set of non binary type not supported\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((desc[5] & 0x30) != 0x00) अणु
		pr_err("XCOPY 0xe4: association other than LUN not supported\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((desc[5] & 0x0f) != 0x3) अणु
		pr_err("XCOPY 0xe4: designator type unsupported: 0x%02x\n",
				(desc[5] & 0x0f));
		वापस -EINVAL;
	पूर्ण
	/*
	 * Check क्रम matching 16 byte length क्रम NAA IEEE Registered Extended
	 * Asचिन्हित designator
	 */
	desig_len = desc[7];
	अगर (desig_len != XCOPY_NAA_IEEE_REGEX_LEN) अणु
		pr_err("XCOPY 0xe4: invalid desig_len: %d\n", (पूर्णांक)desig_len);
		वापस -EINVAL;
	पूर्ण
	pr_debug("XCOPY 0xe4: desig_len: %d\n", (पूर्णांक)desig_len);
	/*
	 * Check क्रम NAA IEEE Registered Extended Asचिन्हित header..
	 */
	अगर ((desc[8] & 0xf0) != 0x60) अणु
		pr_err("XCOPY 0xe4: Unsupported DESIGNATOR TYPE: 0x%02x\n",
					(desc[8] & 0xf0));
		वापस -EINVAL;
	पूर्ण

	अगर (cscd_index != xop->stdi && cscd_index != xop->dtdi) अणु
		pr_debug("XCOPY 0xe4: ignoring CSCD entry %d - neither src nor "
			 "dest\n", cscd_index);
		वापस 0;
	पूर्ण

	अगर (cscd_index == xop->stdi) अणु
		स_नकल(&xop->src_tid_wwn[0], &desc[8], XCOPY_NAA_IEEE_REGEX_LEN);
		/*
		 * Determine अगर the source designator matches the local device
		 */
		अगर (!स_भेद(&xop->local_dev_wwn[0], &xop->src_tid_wwn[0],
				XCOPY_NAA_IEEE_REGEX_LEN)) अणु
			xop->op_origin = XCOL_SOURCE_RECV_OP;
			xop->src_dev = se_cmd->se_dev;
			pr_debug("XCOPY 0xe4: Set xop->src_dev %p from source"
					" received xop\n", xop->src_dev);
		पूर्ण
	पूर्ण

	अगर (cscd_index == xop->dtdi) अणु
		स_नकल(&xop->dst_tid_wwn[0], &desc[8], XCOPY_NAA_IEEE_REGEX_LEN);
		/*
		 * Determine अगर the destination designator matches the local
		 * device. If @cscd_index corresponds to both source (stdi) and
		 * destination (dtdi), or dtdi comes after stdi, then
		 * XCOL_DEST_RECV_OP wins.
		 */
		अगर (!स_भेद(&xop->local_dev_wwn[0], &xop->dst_tid_wwn[0],
				XCOPY_NAA_IEEE_REGEX_LEN)) अणु
			xop->op_origin = XCOL_DEST_RECV_OP;
			xop->dst_dev = se_cmd->se_dev;
			pr_debug("XCOPY 0xe4: Set xop->dst_dev: %p from destination"
				" received xop\n", xop->dst_dev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक target_xcopy_parse_target_descriptors(काष्ठा se_cmd *se_cmd,
				काष्ठा xcopy_op *xop, अचिन्हित अक्षर *p,
				अचिन्हित लघु tdll, sense_reason_t *sense_ret)
अणु
	काष्ठा se_device *local_dev = se_cmd->se_dev;
	अचिन्हित अक्षर *desc = p;
	पूर्णांक offset = tdll % XCOPY_TARGET_DESC_LEN, rc;
	अचिन्हित लघु cscd_index = 0;
	अचिन्हित लघु start = 0;

	*sense_ret = TCM_INVALID_PARAMETER_LIST;

	अगर (offset != 0) अणु
		pr_err("XCOPY target descriptor list length is not"
			" multiple of %d\n", XCOPY_TARGET_DESC_LEN);
		*sense_ret = TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE;
		वापस -EINVAL;
	पूर्ण
	अगर (tdll > RCR_OP_MAX_TARGET_DESC_COUNT * XCOPY_TARGET_DESC_LEN) अणु
		pr_err("XCOPY target descriptor supports a maximum"
			" two src/dest descriptors, tdll: %hu too large..\n", tdll);
		/* spc4r37 6.4.3.4 CSCD DESCRIPTOR LIST LENGTH field */
		*sense_ret = TCM_TOO_MANY_TARGET_DESCS;
		वापस -EINVAL;
	पूर्ण
	/*
	 * Generate an IEEE Registered Extended designator based upon the
	 * se_device the XCOPY was received upon..
	 */
	स_रखो(&xop->local_dev_wwn[0], 0, XCOPY_NAA_IEEE_REGEX_LEN);
	target_xcopy_gen_naa_ieee(local_dev, &xop->local_dev_wwn[0]);

	जबतक (start < tdll) अणु
		/*
		 * Check target descriptor identअगरication with 0xE4 type, and
		 * compare the current index with the CSCD descriptor IDs in
		 * the segment descriptor. Use VPD 0x83 WWPN matching ..
		 */
		चयन (desc[0]) अणु
		हाल 0xe4:
			rc = target_xcopy_parse_tiddesc_e4(se_cmd, xop,
							&desc[0], cscd_index);
			अगर (rc != 0)
				जाओ out;
			start += XCOPY_TARGET_DESC_LEN;
			desc += XCOPY_TARGET_DESC_LEN;
			cscd_index++;
			अवरोध;
		शेष:
			pr_err("XCOPY unsupported descriptor type code:"
					" 0x%02x\n", desc[0]);
			*sense_ret = TCM_UNSUPPORTED_TARGET_DESC_TYPE_CODE;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (xop->op_origin) अणु
	हाल XCOL_SOURCE_RECV_OP:
		rc = target_xcopy_locate_se_dev_e4(se_cmd->se_sess,
						xop->dst_tid_wwn,
						&xop->dst_dev,
						&xop->remote_lun_ref);
		अवरोध;
	हाल XCOL_DEST_RECV_OP:
		rc = target_xcopy_locate_se_dev_e4(se_cmd->se_sess,
						xop->src_tid_wwn,
						&xop->src_dev,
						&xop->remote_lun_ref);
		अवरोध;
	शेष:
		pr_err("XCOPY CSCD descriptor IDs not found in CSCD list - "
			"stdi: %hu dtdi: %hu\n", xop->stdi, xop->dtdi);
		rc = -EINVAL;
		अवरोध;
	पूर्ण
	/*
	 * If a matching IEEE NAA 0x83 descriptor क्रम the requested device
	 * is not located on this node, वापस COPY_ABORTED with ASQ/ASQC
	 * 0x0d/0x02 - COPY_TARGET_DEVICE_NOT_REACHABLE to request the
	 * initiator to fall back to normal copy method.
	 */
	अगर (rc < 0) अणु
		*sense_ret = TCM_COPY_TARGET_DEVICE_NOT_REACHABLE;
		जाओ out;
	पूर्ण

	pr_debug("XCOPY TGT desc: Source dev: %p NAA IEEE WWN: 0x%16phN\n",
		 xop->src_dev, &xop->src_tid_wwn[0]);
	pr_debug("XCOPY TGT desc: Dest dev: %p NAA IEEE WWN: 0x%16phN\n",
		 xop->dst_dev, &xop->dst_tid_wwn[0]);

	वापस cscd_index;

out:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक target_xcopy_parse_segdesc_02(काष्ठा se_cmd *se_cmd, काष्ठा xcopy_op *xop,
					अचिन्हित अक्षर *p)
अणु
	अचिन्हित अक्षर *desc = p;
	पूर्णांक dc = (desc[1] & 0x02);
	अचिन्हित लघु desc_len;

	desc_len = get_unaligned_be16(&desc[2]);
	अगर (desc_len != 0x18) अणु
		pr_err("XCOPY segment desc 0x02: Illegal desc_len:"
				" %hu\n", desc_len);
		वापस -EINVAL;
	पूर्ण

	xop->stdi = get_unaligned_be16(&desc[4]);
	xop->dtdi = get_unaligned_be16(&desc[6]);

	अगर (xop->stdi > XCOPY_CSCD_DESC_ID_LIST_OFF_MAX ||
	    xop->dtdi > XCOPY_CSCD_DESC_ID_LIST_OFF_MAX) अणु
		pr_err("XCOPY segment desc 0x02: unsupported CSCD ID > 0x%x; stdi: %hu dtdi: %hu\n",
			XCOPY_CSCD_DESC_ID_LIST_OFF_MAX, xop->stdi, xop->dtdi);
		वापस -EINVAL;
	पूर्ण

	pr_debug("XCOPY seg desc 0x02: desc_len: %hu stdi: %hu dtdi: %hu, DC: %d\n",
		desc_len, xop->stdi, xop->dtdi, dc);

	xop->nolb = get_unaligned_be16(&desc[10]);
	xop->src_lba = get_unaligned_be64(&desc[12]);
	xop->dst_lba = get_unaligned_be64(&desc[20]);
	pr_debug("XCOPY seg desc 0x02: nolb: %hu src_lba: %llu dst_lba: %llu\n",
		xop->nolb, (अचिन्हित दीर्घ दीर्घ)xop->src_lba,
		(अचिन्हित दीर्घ दीर्घ)xop->dst_lba);

	वापस 0;
पूर्ण

अटल पूर्णांक target_xcopy_parse_segment_descriptors(काष्ठा se_cmd *se_cmd,
				काष्ठा xcopy_op *xop, अचिन्हित अक्षर *p,
				अचिन्हित पूर्णांक sdll, sense_reason_t *sense_ret)
अणु
	अचिन्हित अक्षर *desc = p;
	अचिन्हित पूर्णांक start = 0;
	पूर्णांक offset = sdll % XCOPY_SEGMENT_DESC_LEN, rc, ret = 0;

	*sense_ret = TCM_INVALID_PARAMETER_LIST;

	अगर (offset != 0) अणु
		pr_err("XCOPY segment descriptor list length is not"
			" multiple of %d\n", XCOPY_SEGMENT_DESC_LEN);
		*sense_ret = TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE;
		वापस -EINVAL;
	पूर्ण
	अगर (sdll > RCR_OP_MAX_SG_DESC_COUNT * XCOPY_SEGMENT_DESC_LEN) अणु
		pr_err("XCOPY supports %u segment descriptor(s), sdll: %u too"
			" large..\n", RCR_OP_MAX_SG_DESC_COUNT, sdll);
		/* spc4r37 6.4.3.5 SEGMENT DESCRIPTOR LIST LENGTH field */
		*sense_ret = TCM_TOO_MANY_SEGMENT_DESCS;
		वापस -EINVAL;
	पूर्ण

	जबतक (start < sdll) अणु
		/*
		 * Check segment descriptor type code क्रम block -> block
		 */
		चयन (desc[0]) अणु
		हाल 0x02:
			rc = target_xcopy_parse_segdesc_02(se_cmd, xop, desc);
			अगर (rc < 0)
				जाओ out;

			ret++;
			start += XCOPY_SEGMENT_DESC_LEN;
			desc += XCOPY_SEGMENT_DESC_LEN;
			अवरोध;
		शेष:
			pr_err("XCOPY unsupported segment descriptor"
				"type: 0x%02x\n", desc[0]);
			*sense_ret = TCM_UNSUPPORTED_SEGMENT_DESC_TYPE_CODE;
			जाओ out;
		पूर्ण
	पूर्ण

	वापस ret;

out:
	वापस -EINVAL;
पूर्ण

/*
 * Start xcopy_pt ops
 */

काष्ठा xcopy_pt_cmd अणु
	काष्ठा se_cmd se_cmd;
	काष्ठा completion xpt_passthrough_sem;
	अचिन्हित अक्षर sense_buffer[TRANSPORT_SENSE_BUFFER];
पूर्ण;

काष्ठा se_portal_group xcopy_pt_tpg;
अटल काष्ठा se_session xcopy_pt_sess;
अटल काष्ठा se_node_acl xcopy_pt_nacl;

अटल पूर्णांक xcopy_pt_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
        वापस 0;
पूर्ण

अटल व्योम xcopy_pt_undepend_remotedev(काष्ठा xcopy_op *xop)
अणु
	अगर (xop->op_origin == XCOL_SOURCE_RECV_OP)
		pr_debug("putting dst lun_ref for %p\n", xop->dst_dev);
	अन्यथा
		pr_debug("putting src lun_ref for %p\n", xop->src_dev);

	percpu_ref_put(xop->remote_lun_ref);
पूर्ण

अटल व्योम xcopy_pt_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा xcopy_pt_cmd *xpt_cmd = container_of(se_cmd,
				काष्ठा xcopy_pt_cmd, se_cmd);

	/* xpt_cmd is on the stack, nothing to मुक्त here */
	pr_debug("xpt_cmd done: %p\n", xpt_cmd);
पूर्ण

अटल पूर्णांक xcopy_pt_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा xcopy_pt_cmd *xpt_cmd = container_of(se_cmd,
				काष्ठा xcopy_pt_cmd, se_cmd);

	complete(&xpt_cmd->xpt_passthrough_sem);
	वापस 0;
पूर्ण

अटल पूर्णांक xcopy_pt_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xcopy_pt_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक xcopy_pt_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा target_core_fabric_ops xcopy_pt_tfo = अणु
	.fabric_name		= "xcopy-pt",
	.get_cmd_state		= xcopy_pt_get_cmd_state,
	.release_cmd		= xcopy_pt_release_cmd,
	.check_stop_मुक्त	= xcopy_pt_check_stop_मुक्त,
	.ग_लिखो_pending		= xcopy_pt_ग_लिखो_pending,
	.queue_data_in		= xcopy_pt_queue_data_in,
	.queue_status		= xcopy_pt_queue_status,
पूर्ण;

/*
 * End xcopy_pt_ops
 */

पूर्णांक target_xcopy_setup_pt(व्योम)
अणु
	पूर्णांक ret;

	xcopy_wq = alloc_workqueue("xcopy_wq", WQ_MEM_RECLAIM, 0);
	अगर (!xcopy_wq) अणु
		pr_err("Unable to allocate xcopy_wq\n");
		वापस -ENOMEM;
	पूर्ण

	स_रखो(&xcopy_pt_tpg, 0, माप(काष्ठा se_portal_group));
	INIT_LIST_HEAD(&xcopy_pt_tpg.acl_node_list);
	INIT_LIST_HEAD(&xcopy_pt_tpg.tpg_sess_list);

	xcopy_pt_tpg.se_tpg_tfo = &xcopy_pt_tfo;

	स_रखो(&xcopy_pt_nacl, 0, माप(काष्ठा se_node_acl));
	INIT_LIST_HEAD(&xcopy_pt_nacl.acl_list);
	INIT_LIST_HEAD(&xcopy_pt_nacl.acl_sess_list);
	स_रखो(&xcopy_pt_sess, 0, माप(काष्ठा se_session));
	ret = transport_init_session(&xcopy_pt_sess);
	अगर (ret < 0)
		जाओ destroy_wq;

	xcopy_pt_nacl.se_tpg = &xcopy_pt_tpg;
	xcopy_pt_nacl.nacl_sess = &xcopy_pt_sess;

	xcopy_pt_sess.se_tpg = &xcopy_pt_tpg;
	xcopy_pt_sess.se_node_acl = &xcopy_pt_nacl;

	वापस 0;

destroy_wq:
	destroy_workqueue(xcopy_wq);
	xcopy_wq = शून्य;
	वापस ret;
पूर्ण

व्योम target_xcopy_release_pt(व्योम)
अणु
	अगर (xcopy_wq) अणु
		destroy_workqueue(xcopy_wq);
		transport_uninit_session(&xcopy_pt_sess);
	पूर्ण
पूर्ण

/*
 * target_xcopy_setup_pt_cmd - set up a pass-through command
 * @xpt_cmd:	 Data काष्ठाure to initialize.
 * @xop:	 Describes the XCOPY operation received from an initiator.
 * @se_dev:	 Backend device to associate with @xpt_cmd अगर
 *		 @remote_port == true.
 * @cdb:	 SCSI CDB to be copied पूर्णांकo @xpt_cmd.
 * @remote_port: If false, use the LUN through which the XCOPY command has
 *		 been received. If true, use @se_dev->xcopy_lun.
 *
 * Set up a SCSI command (READ or WRITE) that will be used to execute an
 * XCOPY command.
 */
अटल पूर्णांक target_xcopy_setup_pt_cmd(
	काष्ठा xcopy_pt_cmd *xpt_cmd,
	काष्ठा xcopy_op *xop,
	काष्ठा se_device *se_dev,
	अचिन्हित अक्षर *cdb,
	bool remote_port)
अणु
	काष्ठा se_cmd *cmd = &xpt_cmd->se_cmd;

	/*
	 * Setup LUN+port to honor reservations based upon xop->op_origin क्रम
	 * X-COPY PUSH or X-COPY PULL based upon where the CDB was received.
	 */
	अगर (remote_port) अणु
		cmd->se_lun = &se_dev->xcopy_lun;
		cmd->se_dev = se_dev;
	पूर्ण अन्यथा अणु
		cmd->se_lun = xop->xop_se_cmd->se_lun;
		cmd->se_dev = xop->xop_se_cmd->se_dev;
	पूर्ण
	cmd->se_cmd_flags |= SCF_SE_LUN_CMD;

	अगर (target_cmd_init_cdb(cmd, cdb, GFP_KERNEL))
		वापस -EINVAL;

	cmd->tag = 0;
	अगर (target_cmd_parse_cdb(cmd))
		वापस -EINVAL;

	अगर (transport_generic_map_mem_to_cmd(cmd, xop->xop_data_sg,
					xop->xop_data_nents, शून्य, 0))
		वापस -EINVAL;

	pr_debug("Setup PASSTHROUGH_NOALLOC t_data_sg: %p t_data_nents:"
		 " %u\n", cmd->t_data_sg, cmd->t_data_nents);

	वापस 0;
पूर्ण

अटल पूर्णांक target_xcopy_issue_pt_cmd(काष्ठा xcopy_pt_cmd *xpt_cmd)
अणु
	काष्ठा se_cmd *se_cmd = &xpt_cmd->se_cmd;
	sense_reason_t sense_rc;

	sense_rc = transport_generic_new_cmd(se_cmd);
	अगर (sense_rc)
		वापस -EINVAL;

	अगर (se_cmd->data_direction == DMA_TO_DEVICE)
		target_execute_cmd(se_cmd);

	रुको_क्रम_completion_पूर्णांकerruptible(&xpt_cmd->xpt_passthrough_sem);

	pr_debug("target_xcopy_issue_pt_cmd(): SCSI status: 0x%02x\n",
			se_cmd->scsi_status);

	वापस (se_cmd->scsi_status) ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक target_xcopy_पढ़ो_source(
	काष्ठा se_cmd *ec_cmd,
	काष्ठा xcopy_op *xop,
	काष्ठा se_device *src_dev,
	sector_t src_lba,
	u32 src_sectors)
अणु
	काष्ठा xcopy_pt_cmd xpt_cmd;
	काष्ठा se_cmd *se_cmd = &xpt_cmd.se_cmd;
	u32 length = (src_sectors * src_dev->dev_attrib.block_size);
	पूर्णांक rc;
	अचिन्हित अक्षर cdb[16];
	bool remote_port = (xop->op_origin == XCOL_DEST_RECV_OP);

	स_रखो(&xpt_cmd, 0, माप(xpt_cmd));
	init_completion(&xpt_cmd.xpt_passthrough_sem);

	स_रखो(&cdb[0], 0, 16);
	cdb[0] = READ_16;
	put_unaligned_be64(src_lba, &cdb[2]);
	put_unaligned_be32(src_sectors, &cdb[10]);
	pr_debug("XCOPY: Built READ_16: LBA: %llu Sectors: %u Length: %u\n",
		(अचिन्हित दीर्घ दीर्घ)src_lba, src_sectors, length);

	__target_init_cmd(se_cmd, &xcopy_pt_tfo, &xcopy_pt_sess, length,
			  DMA_FROM_DEVICE, 0, &xpt_cmd.sense_buffer[0], 0);

	rc = target_xcopy_setup_pt_cmd(&xpt_cmd, xop, src_dev, &cdb[0],
				remote_port);
	अगर (rc < 0) अणु
		ec_cmd->scsi_status = se_cmd->scsi_status;
		जाओ out;
	पूर्ण

	pr_debug("XCOPY-READ: Saved xop->xop_data_sg: %p, num: %u for READ"
		" memory\n", xop->xop_data_sg, xop->xop_data_nents);

	rc = target_xcopy_issue_pt_cmd(&xpt_cmd);
	अगर (rc < 0)
		ec_cmd->scsi_status = se_cmd->scsi_status;
out:
	transport_generic_मुक्त_cmd(se_cmd, 0);
	वापस rc;
पूर्ण

अटल पूर्णांक target_xcopy_ग_लिखो_destination(
	काष्ठा se_cmd *ec_cmd,
	काष्ठा xcopy_op *xop,
	काष्ठा se_device *dst_dev,
	sector_t dst_lba,
	u32 dst_sectors)
अणु
	काष्ठा xcopy_pt_cmd xpt_cmd;
	काष्ठा se_cmd *se_cmd = &xpt_cmd.se_cmd;
	u32 length = (dst_sectors * dst_dev->dev_attrib.block_size);
	पूर्णांक rc;
	अचिन्हित अक्षर cdb[16];
	bool remote_port = (xop->op_origin == XCOL_SOURCE_RECV_OP);

	स_रखो(&xpt_cmd, 0, माप(xpt_cmd));
	init_completion(&xpt_cmd.xpt_passthrough_sem);

	स_रखो(&cdb[0], 0, 16);
	cdb[0] = WRITE_16;
	put_unaligned_be64(dst_lba, &cdb[2]);
	put_unaligned_be32(dst_sectors, &cdb[10]);
	pr_debug("XCOPY: Built WRITE_16: LBA: %llu Sectors: %u Length: %u\n",
		(अचिन्हित दीर्घ दीर्घ)dst_lba, dst_sectors, length);

	__target_init_cmd(se_cmd, &xcopy_pt_tfo, &xcopy_pt_sess, length,
			  DMA_TO_DEVICE, 0, &xpt_cmd.sense_buffer[0], 0);

	rc = target_xcopy_setup_pt_cmd(&xpt_cmd, xop, dst_dev, &cdb[0],
				remote_port);
	अगर (rc < 0) अणु
		ec_cmd->scsi_status = se_cmd->scsi_status;
		जाओ out;
	पूर्ण

	rc = target_xcopy_issue_pt_cmd(&xpt_cmd);
	अगर (rc < 0)
		ec_cmd->scsi_status = se_cmd->scsi_status;
out:
	transport_generic_मुक्त_cmd(se_cmd, 0);
	वापस rc;
पूर्ण

अटल व्योम target_xcopy_करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xcopy_op *xop = container_of(work, काष्ठा xcopy_op, xop_work);
	काष्ठा se_cmd *ec_cmd = xop->xop_se_cmd;
	काष्ठा se_device *src_dev, *dst_dev;
	sector_t src_lba, dst_lba, end_lba;
	अचिन्हित पूर्णांक max_sectors;
	पूर्णांक rc = 0;
	अचिन्हित लघु nolb, max_nolb, copied_nolb = 0;

	अगर (target_parse_xcopy_cmd(xop) != TCM_NO_SENSE)
		जाओ err_मुक्त;

	अगर (WARN_ON_ONCE(!xop->src_dev) || WARN_ON_ONCE(!xop->dst_dev))
		जाओ err_मुक्त;

	src_dev = xop->src_dev;
	dst_dev = xop->dst_dev;
	src_lba = xop->src_lba;
	dst_lba = xop->dst_lba;
	nolb = xop->nolb;
	end_lba = src_lba + nolb;
	/*
	 * Break up XCOPY I/O पूर्णांकo hw_max_sectors sized I/O based on the
	 * smallest max_sectors between src_dev + dev_dev, or
	 */
	max_sectors = min(src_dev->dev_attrib.hw_max_sectors,
			  dst_dev->dev_attrib.hw_max_sectors);
	max_sectors = min_t(u32, max_sectors, XCOPY_MAX_SECTORS);

	max_nolb = min_t(u16, max_sectors, ((u16)(~0U)));

	pr_debug("target_xcopy_do_work: nolb: %hu, max_nolb: %hu end_lba: %llu\n",
			nolb, max_nolb, (अचिन्हित दीर्घ दीर्घ)end_lba);
	pr_debug("target_xcopy_do_work: Starting src_lba: %llu, dst_lba: %llu\n",
			(अचिन्हित दीर्घ दीर्घ)src_lba, (अचिन्हित दीर्घ दीर्घ)dst_lba);

	जबतक (src_lba < end_lba) अणु
		अचिन्हित लघु cur_nolb = min(nolb, max_nolb);
		u32 cur_bytes = cur_nolb * src_dev->dev_attrib.block_size;

		अगर (cur_bytes != xop->xop_data_bytes) अणु
			/*
			 * (Re)allocate a buffer large enough to hold the XCOPY
			 * I/O size, which can be reused each पढ़ो / ग_लिखो loop.
			 */
			target_मुक्त_sgl(xop->xop_data_sg, xop->xop_data_nents);
			rc = target_alloc_sgl(&xop->xop_data_sg,
					      &xop->xop_data_nents,
					      cur_bytes,
					      false, false);
			अगर (rc < 0)
				जाओ out;
			xop->xop_data_bytes = cur_bytes;
		पूर्ण

		pr_debug("target_xcopy_do_work: Calling read src_dev: %p src_lba: %llu,"
			" cur_nolb: %hu\n", src_dev, (अचिन्हित दीर्घ दीर्घ)src_lba, cur_nolb);

		rc = target_xcopy_पढ़ो_source(ec_cmd, xop, src_dev, src_lba, cur_nolb);
		अगर (rc < 0)
			जाओ out;

		src_lba += cur_nolb;
		pr_debug("target_xcopy_do_work: Incremented READ src_lba to %llu\n",
				(अचिन्हित दीर्घ दीर्घ)src_lba);

		pr_debug("target_xcopy_do_work: Calling write dst_dev: %p dst_lba: %llu,"
			" cur_nolb: %hu\n", dst_dev, (अचिन्हित दीर्घ दीर्घ)dst_lba, cur_nolb);

		rc = target_xcopy_ग_लिखो_destination(ec_cmd, xop, dst_dev,
						dst_lba, cur_nolb);
		अगर (rc < 0)
			जाओ out;

		dst_lba += cur_nolb;
		pr_debug("target_xcopy_do_work: Incremented WRITE dst_lba to %llu\n",
				(अचिन्हित दीर्घ दीर्घ)dst_lba);

		copied_nolb += cur_nolb;
		nolb -= cur_nolb;
	पूर्ण

	xcopy_pt_undepend_remotedev(xop);
	target_मुक्त_sgl(xop->xop_data_sg, xop->xop_data_nents);
	kमुक्त(xop);

	pr_debug("target_xcopy_do_work: Final src_lba: %llu, dst_lba: %llu\n",
		(अचिन्हित दीर्घ दीर्घ)src_lba, (अचिन्हित दीर्घ दीर्घ)dst_lba);
	pr_debug("target_xcopy_do_work: Blocks copied: %hu, Bytes Copied: %u\n",
		copied_nolb, copied_nolb * dst_dev->dev_attrib.block_size);

	pr_debug("target_xcopy_do_work: Setting X-COPY GOOD status -> sending response\n");
	target_complete_cmd(ec_cmd, SAM_STAT_GOOD);
	वापस;

out:
	xcopy_pt_undepend_remotedev(xop);
	target_मुक्त_sgl(xop->xop_data_sg, xop->xop_data_nents);

err_मुक्त:
	kमुक्त(xop);
	/*
	 * Don't override an error scsi status अगर it has alपढ़ोy been set
	 */
	अगर (ec_cmd->scsi_status == SAM_STAT_GOOD) अणु
		pr_warn_ratelimited("target_xcopy_do_work: rc: %d, Setting X-COPY"
			" CHECK_CONDITION -> sending response\n", rc);
		ec_cmd->scsi_status = SAM_STAT_CHECK_CONDITION;
	पूर्ण
	target_complete_cmd(ec_cmd, ec_cmd->scsi_status);
पूर्ण

/*
 * Returns TCM_NO_SENSE upon success or a sense code != TCM_NO_SENSE अगर parsing
 * fails.
 */
अटल sense_reason_t target_parse_xcopy_cmd(काष्ठा xcopy_op *xop)
अणु
	काष्ठा se_cmd *se_cmd = xop->xop_se_cmd;
	अचिन्हित अक्षर *p = शून्य, *seg_desc;
	अचिन्हित पूर्णांक list_id, list_id_usage, sdll, अंतरभूत_dl;
	sense_reason_t ret = TCM_INVALID_PARAMETER_LIST;
	पूर्णांक rc;
	अचिन्हित लघु tdll;

	p = transport_kmap_data_sg(se_cmd);
	अगर (!p) अणु
		pr_err("transport_kmap_data_sg() failed in target_do_xcopy\n");
		वापस TCM_OUT_OF_RESOURCES;
	पूर्ण

	list_id = p[0];
	list_id_usage = (p[1] & 0x18) >> 3;

	/*
	 * Determine TARGET DESCRIPTOR LIST LENGTH + SEGMENT DESCRIPTOR LIST LENGTH
	 */
	tdll = get_unaligned_be16(&p[2]);
	sdll = get_unaligned_be32(&p[8]);
	अगर (tdll + sdll > RCR_OP_MAX_DESC_LIST_LEN) अणु
		pr_err("XCOPY descriptor list length %u exceeds maximum %u\n",
		       tdll + sdll, RCR_OP_MAX_DESC_LIST_LEN);
		ret = TCM_PARAMETER_LIST_LENGTH_ERROR;
		जाओ out;
	पूर्ण

	अंतरभूत_dl = get_unaligned_be32(&p[12]);
	अगर (अंतरभूत_dl != 0) अणु
		pr_err("XCOPY with non zero inline data length\n");
		जाओ out;
	पूर्ण

	अगर (se_cmd->data_length < (XCOPY_HDR_LEN + tdll + sdll + अंतरभूत_dl)) अणु
		pr_err("XCOPY parameter truncation: data length %u too small "
			"for tdll: %hu sdll: %u inline_dl: %u\n",
			se_cmd->data_length, tdll, sdll, अंतरभूत_dl);
		ret = TCM_PARAMETER_LIST_LENGTH_ERROR;
		जाओ out;
	पूर्ण

	pr_debug("Processing XCOPY with list_id: 0x%02x list_id_usage: 0x%02x"
		" tdll: %hu sdll: %u inline_dl: %u\n", list_id, list_id_usage,
		tdll, sdll, अंतरभूत_dl);

	/*
	 * skip over the target descriptors until segment descriptors
	 * have been passed - CSCD ids are needed to determine src and dest.
	 */
	seg_desc = &p[16] + tdll;

	rc = target_xcopy_parse_segment_descriptors(se_cmd, xop, seg_desc,
						    sdll, &ret);
	अगर (rc <= 0)
		जाओ out;

	pr_debug("XCOPY: Processed %d segment descriptors, length: %u\n", rc,
				rc * XCOPY_SEGMENT_DESC_LEN);

	rc = target_xcopy_parse_target_descriptors(se_cmd, xop, &p[16], tdll, &ret);
	अगर (rc <= 0)
		जाओ out;

	अगर (xop->src_dev->dev_attrib.block_size !=
	    xop->dst_dev->dev_attrib.block_size) अणु
		pr_err("XCOPY: Non matching src_dev block_size: %u + dst_dev"
		       " block_size: %u currently unsupported\n",
			xop->src_dev->dev_attrib.block_size,
			xop->dst_dev->dev_attrib.block_size);
		xcopy_pt_undepend_remotedev(xop);
		ret = TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;
		जाओ out;
	पूर्ण

	pr_debug("XCOPY: Processed %d target descriptors, length: %u\n", rc,
				rc * XCOPY_TARGET_DESC_LEN);
	transport_kunmap_data_sg(se_cmd);
	वापस TCM_NO_SENSE;

out:
	अगर (p)
		transport_kunmap_data_sg(se_cmd);
	वापस ret;
पूर्ण

sense_reason_t target_करो_xcopy(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा se_device *dev = se_cmd->se_dev;
	काष्ठा xcopy_op *xop;
	अचिन्हित पूर्णांक sa;

	अगर (!dev->dev_attrib.emulate_3pc) अणु
		pr_err("EXTENDED_COPY operation explicitly disabled\n");
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण

	sa = se_cmd->t_task_cdb[1] & 0x1f;
	अगर (sa != 0x00) अणु
		pr_err("EXTENDED_COPY(LID4) not supported\n");
		वापस TCM_UNSUPPORTED_SCSI_OPCODE;
	पूर्ण

	अगर (se_cmd->data_length == 0) अणु
		target_complete_cmd(se_cmd, SAM_STAT_GOOD);
		वापस TCM_NO_SENSE;
	पूर्ण
	अगर (se_cmd->data_length < XCOPY_HDR_LEN) अणु
		pr_err("XCOPY parameter truncation: length %u < hdr_len %u\n",
				se_cmd->data_length, XCOPY_HDR_LEN);
		वापस TCM_PARAMETER_LIST_LENGTH_ERROR;
	पूर्ण

	xop = kzalloc(माप(काष्ठा xcopy_op), GFP_KERNEL);
	अगर (!xop)
		जाओ err;
	xop->xop_se_cmd = se_cmd;
	INIT_WORK(&xop->xop_work, target_xcopy_करो_work);
	अगर (WARN_ON_ONCE(!queue_work(xcopy_wq, &xop->xop_work)))
		जाओ मुक्त;
	वापस TCM_NO_SENSE;

मुक्त:
	kमुक्त(xop);

err:
	वापस TCM_OUT_OF_RESOURCES;
पूर्ण

अटल sense_reason_t target_rcr_operating_parameters(काष्ठा se_cmd *se_cmd)
अणु
	अचिन्हित अक्षर *p;

	p = transport_kmap_data_sg(se_cmd);
	अगर (!p) अणु
		pr_err("transport_kmap_data_sg failed in"
		       " target_rcr_operating_parameters\n");
		वापस TCM_OUT_OF_RESOURCES;
	पूर्ण

	अगर (se_cmd->data_length < 54) अणु
		pr_err("Receive Copy Results Op Parameters length"
		       " too small: %u\n", se_cmd->data_length);
		transport_kunmap_data_sg(se_cmd);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण
	/*
	 * Set SNLID=1 (Supports no List ID)
	 */
	p[4] = 0x1;
	/*
	 * MAXIMUM TARGET DESCRIPTOR COUNT
	 */
	put_unaligned_be16(RCR_OP_MAX_TARGET_DESC_COUNT, &p[8]);
	/*
	 * MAXIMUM SEGMENT DESCRIPTOR COUNT
	 */
	put_unaligned_be16(RCR_OP_MAX_SG_DESC_COUNT, &p[10]);
	/*
	 * MAXIMUM DESCRIPTOR LIST LENGTH
	 */
	put_unaligned_be32(RCR_OP_MAX_DESC_LIST_LEN, &p[12]);
	/*
	 * MAXIMUM SEGMENT LENGTH
	 */
	put_unaligned_be32(RCR_OP_MAX_SEGMENT_LEN, &p[16]);
	/*
	 * MAXIMUM INLINE DATA LENGTH क्रम SA 0x04 (NOT SUPPORTED)
	 */
	put_unaligned_be32(0x0, &p[20]);
	/*
	 * HELD DATA LIMIT
	 */
	put_unaligned_be32(0x0, &p[24]);
	/*
	 * MAXIMUM STREAM DEVICE TRANSFER SIZE
	 */
	put_unaligned_be32(0x0, &p[28]);
	/*
	 * TOTAL CONCURRENT COPIES
	 */
	put_unaligned_be16(RCR_OP_TOTAL_CONCURR_COPIES, &p[34]);
	/*
	 * MAXIMUM CONCURRENT COPIES
	 */
	p[36] = RCR_OP_MAX_CONCURR_COPIES;
	/*
	 * DATA SEGMENT GRANULARITY (log 2)
	 */
	p[37] = RCR_OP_DATA_SEG_GRAN_LOG2;
	/*
	 * INLINE DATA GRANULARITY log 2)
	 */
	p[38] = RCR_OP_INLINE_DATA_GRAN_LOG2;
	/*
	 * HELD DATA GRANULARITY
	 */
	p[39] = RCR_OP_HELD_DATA_GRAN_LOG2;
	/*
	 * IMPLEMENTED DESCRIPTOR LIST LENGTH
	 */
	p[43] = 0x2;
	/*
	 * List of implemented descriptor type codes (ordered)
	 */
	p[44] = 0x02; /* Copy Block to Block device */
	p[45] = 0xe4; /* Identअगरication descriptor target descriptor */

	/*
	 * AVAILABLE DATA (n-3)
	 */
	put_unaligned_be32(42, &p[0]);

	transport_kunmap_data_sg(se_cmd);
	target_complete_cmd(se_cmd, GOOD);

	वापस TCM_NO_SENSE;
पूर्ण

sense_reason_t target_करो_receive_copy_results(काष्ठा se_cmd *se_cmd)
अणु
	अचिन्हित अक्षर *cdb = &se_cmd->t_task_cdb[0];
	पूर्णांक sa = (cdb[1] & 0x1f), list_id = cdb[2];
	sense_reason_t rc = TCM_NO_SENSE;

	pr_debug("Entering target_do_receive_copy_results: SA: 0x%02x, List ID:"
		" 0x%02x, AL: %u\n", sa, list_id, se_cmd->data_length);

	अगर (list_id != 0) अणु
		pr_err("Receive Copy Results with non zero list identifier"
		       " not supported\n");
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	चयन (sa) अणु
	हाल RCR_SA_OPERATING_PARAMETERS:
		rc = target_rcr_operating_parameters(se_cmd);
		अवरोध;
	हाल RCR_SA_COPY_STATUS:
	हाल RCR_SA_RECEIVE_DATA:
	हाल RCR_SA_FAILED_SEGMENT_DETAILS:
	शेष:
		pr_err("Unsupported SA for receive copy results: 0x%02x\n", sa);
		वापस TCM_INVALID_CDB_FIELD;
	पूर्ण

	वापस rc;
पूर्ण
