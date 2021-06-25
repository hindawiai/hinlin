<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains the iSCSI Virtual Device and Disk Transport
 * agnostic related functions.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_device.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"

व्योम iscsit_determine_maxcmdsn(काष्ठा iscsi_session *sess)
अणु
	काष्ठा se_node_acl *se_nacl;

	/*
	 * This is a discovery session, the single queue slot was alपढ़ोy
	 * asचिन्हित in iscsi_login_zero_tsih().  Since only Logout and
	 * Text Opcodes are allowed during discovery we करो not have to worry
	 * about the HBA's queue depth here.
	 */
	अगर (sess->sess_ops->SessionType)
		वापस;

	se_nacl = sess->se_sess->se_node_acl;

	/*
	 * This is a normal session, set the Session's CmdSN winकरोw to the
	 * काष्ठा se_node_acl->queue_depth.  The value in काष्ठा se_node_acl->queue_depth
	 * has alपढ़ोy been validated as a legal value in
	 * core_set_queue_depth_क्रम_node().
	 */
	sess->cmdsn_winकरोw = se_nacl->queue_depth;
	atomic_add(se_nacl->queue_depth - 1, &sess->max_cmd_sn);
पूर्ण

व्योम iscsit_increment_maxcmdsn(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_session *sess)
अणु
	u32 max_cmd_sn;

	अगर (cmd->immediate_cmd || cmd->maxcmdsn_inc)
		वापस;

	cmd->maxcmdsn_inc = 1;

	max_cmd_sn = atomic_inc_वापस(&sess->max_cmd_sn);
	pr_debug("Updated MaxCmdSN to 0x%08x\n", max_cmd_sn);
पूर्ण
EXPORT_SYMBOL(iscsit_increment_maxcmdsn);
