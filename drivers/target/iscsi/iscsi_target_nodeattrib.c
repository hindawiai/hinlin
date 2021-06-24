<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains the मुख्य functions related to Initiator Node Attributes.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <target/target_core_base.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_device.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target_nodeattrib.h"

अटल अंतरभूत अक्षर *iscsit_na_get_initiatorname(
	काष्ठा iscsi_node_acl *nacl)
अणु
	काष्ठा se_node_acl *se_nacl = &nacl->se_node_acl;

	वापस &se_nacl->initiatorname[0];
पूर्ण

व्योम iscsit_set_शेष_node_attribues(
	काष्ठा iscsi_node_acl *acl,
	काष्ठा iscsi_portal_group *tpg)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	a->dataout_समयout = NA_DATAOUT_TIMEOUT;
	a->dataout_समयout_retries = NA_DATAOUT_TIMEOUT_RETRIES;
	a->nopin_समयout = NA_NOPIN_TIMEOUT;
	a->nopin_response_समयout = NA_NOPIN_RESPONSE_TIMEOUT;
	a->अक्रमom_datain_pdu_offsets = NA_RANDOM_DATAIN_PDU_OFFSETS;
	a->अक्रमom_datain_seq_offsets = NA_RANDOM_DATAIN_SEQ_OFFSETS;
	a->अक्रमom_r2t_offsets = NA_RANDOM_R2T_OFFSETS;
	a->शेष_erl = tpg->tpg_attrib.शेष_erl;
पूर्ण

पूर्णांक iscsit_na_dataout_समयout(
	काष्ठा iscsi_node_acl *acl,
	u32 dataout_समयout)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	अगर (dataout_समयout > NA_DATAOUT_TIMEOUT_MAX) अणु
		pr_err("Requested DataOut Timeout %u larger than"
			" maximum %u\n", dataout_समयout,
			NA_DATAOUT_TIMEOUT_MAX);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (dataout_समयout < NA_DATAOUT_TIMEOUT_MIX) अणु
		pr_err("Requested DataOut Timeout %u smaller than"
			" minimum %u\n", dataout_समयout,
			NA_DATAOUT_TIMEOUT_MIX);
		वापस -EINVAL;
	पूर्ण

	a->dataout_समयout = dataout_समयout;
	pr_debug("Set DataOut Timeout to %u for Initiator Node"
		" %s\n", a->dataout_समयout, iscsit_na_get_initiatorname(acl));

	वापस 0;
पूर्ण

पूर्णांक iscsit_na_dataout_समयout_retries(
	काष्ठा iscsi_node_acl *acl,
	u32 dataout_समयout_retries)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	अगर (dataout_समयout_retries > NA_DATAOUT_TIMEOUT_RETRIES_MAX) अणु
		pr_err("Requested DataOut Timeout Retries %u larger"
			" than maximum %u", dataout_समयout_retries,
				NA_DATAOUT_TIMEOUT_RETRIES_MAX);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (dataout_समयout_retries < NA_DATAOUT_TIMEOUT_RETRIES_MIN) अणु
		pr_err("Requested DataOut Timeout Retries %u smaller"
			" than minimum %u", dataout_समयout_retries,
				NA_DATAOUT_TIMEOUT_RETRIES_MIN);
		वापस -EINVAL;
	पूर्ण

	a->dataout_समयout_retries = dataout_समयout_retries;
	pr_debug("Set DataOut Timeout Retries to %u for"
		" Initiator Node %s\n", a->dataout_समयout_retries,
		iscsit_na_get_initiatorname(acl));

	वापस 0;
पूर्ण

पूर्णांक iscsit_na_nopin_समयout(
	काष्ठा iscsi_node_acl *acl,
	u32 nopin_समयout)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;
	काष्ठा iscsi_session *sess;
	काष्ठा iscsi_conn *conn;
	काष्ठा se_node_acl *se_nacl = &a->nacl->se_node_acl;
	काष्ठा se_session *se_sess;
	u32 orig_nopin_समयout = a->nopin_समयout;

	अगर (nopin_समयout > NA_NOPIN_TIMEOUT_MAX) अणु
		pr_err("Requested NopIn Timeout %u larger than maximum"
			" %u\n", nopin_समयout, NA_NOPIN_TIMEOUT_MAX);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर ((nopin_समयout < NA_NOPIN_TIMEOUT_MIN) &&
		   (nopin_समयout != 0)) अणु
		pr_err("Requested NopIn Timeout %u smaller than"
			" minimum %u and not 0\n", nopin_समयout,
			NA_NOPIN_TIMEOUT_MIN);
		वापस -EINVAL;
	पूर्ण

	a->nopin_समयout = nopin_समयout;
	pr_debug("Set NopIn Timeout to %u for Initiator"
		" Node %s\n", a->nopin_समयout,
		iscsit_na_get_initiatorname(acl));
	/*
	 * Reenable disabled nopin_समयout समयr क्रम all iSCSI connections.
	 */
	अगर (!orig_nopin_समयout) अणु
		spin_lock_bh(&se_nacl->nacl_sess_lock);
		se_sess = se_nacl->nacl_sess;
		अगर (se_sess) अणु
			sess = se_sess->fabric_sess_ptr;

			spin_lock(&sess->conn_lock);
			list_क्रम_each_entry(conn, &sess->sess_conn_list,
					conn_list) अणु
				अगर (conn->conn_state !=
						TARG_CONN_STATE_LOGGED_IN)
					जारी;

				spin_lock(&conn->nopin_समयr_lock);
				__iscsit_start_nopin_समयr(conn);
				spin_unlock(&conn->nopin_समयr_lock);
			पूर्ण
			spin_unlock(&sess->conn_lock);
		पूर्ण
		spin_unlock_bh(&se_nacl->nacl_sess_lock);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsit_na_nopin_response_समयout(
	काष्ठा iscsi_node_acl *acl,
	u32 nopin_response_समयout)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	अगर (nopin_response_समयout > NA_NOPIN_RESPONSE_TIMEOUT_MAX) अणु
		pr_err("Requested NopIn Response Timeout %u larger"
			" than maximum %u\n", nopin_response_समयout,
				NA_NOPIN_RESPONSE_TIMEOUT_MAX);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (nopin_response_समयout < NA_NOPIN_RESPONSE_TIMEOUT_MIN) अणु
		pr_err("Requested NopIn Response Timeout %u smaller"
			" than minimum %u\n", nopin_response_समयout,
				NA_NOPIN_RESPONSE_TIMEOUT_MIN);
		वापस -EINVAL;
	पूर्ण

	a->nopin_response_समयout = nopin_response_समयout;
	pr_debug("Set NopIn Response Timeout to %u for"
		" Initiator Node %s\n", a->nopin_समयout,
		iscsit_na_get_initiatorname(acl));

	वापस 0;
पूर्ण

पूर्णांक iscsit_na_अक्रमom_datain_pdu_offsets(
	काष्ठा iscsi_node_acl *acl,
	u32 अक्रमom_datain_pdu_offsets)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	अगर (अक्रमom_datain_pdu_offsets != 0 && अक्रमom_datain_pdu_offsets != 1) अणु
		pr_err("Requested Random DataIN PDU Offsets: %u not"
			" 0 or 1\n", अक्रमom_datain_pdu_offsets);
		वापस -EINVAL;
	पूर्ण

	a->अक्रमom_datain_pdu_offsets = अक्रमom_datain_pdu_offsets;
	pr_debug("Set Random DataIN PDU Offsets to %u for"
		" Initiator Node %s\n", a->अक्रमom_datain_pdu_offsets,
		iscsit_na_get_initiatorname(acl));

	वापस 0;
पूर्ण

पूर्णांक iscsit_na_अक्रमom_datain_seq_offsets(
	काष्ठा iscsi_node_acl *acl,
	u32 अक्रमom_datain_seq_offsets)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	अगर (अक्रमom_datain_seq_offsets != 0 && अक्रमom_datain_seq_offsets != 1) अणु
		pr_err("Requested Random DataIN Sequence Offsets: %u"
			" not 0 or 1\n", अक्रमom_datain_seq_offsets);
		वापस -EINVAL;
	पूर्ण

	a->अक्रमom_datain_seq_offsets = अक्रमom_datain_seq_offsets;
	pr_debug("Set Random DataIN Sequence Offsets to %u for"
		" Initiator Node %s\n", a->अक्रमom_datain_seq_offsets,
		iscsit_na_get_initiatorname(acl));

	वापस 0;
पूर्ण

पूर्णांक iscsit_na_अक्रमom_r2t_offsets(
	काष्ठा iscsi_node_acl *acl,
	u32 अक्रमom_r2t_offsets)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	अगर (अक्रमom_r2t_offsets != 0 && अक्रमom_r2t_offsets != 1) अणु
		pr_err("Requested Random R2T Offsets: %u not"
			" 0 or 1\n", अक्रमom_r2t_offsets);
		वापस -EINVAL;
	पूर्ण

	a->अक्रमom_r2t_offsets = अक्रमom_r2t_offsets;
	pr_debug("Set Random R2T Offsets to %u for"
		" Initiator Node %s\n", a->अक्रमom_r2t_offsets,
		iscsit_na_get_initiatorname(acl));

	वापस 0;
पूर्ण

पूर्णांक iscsit_na_शेष_erl(
	काष्ठा iscsi_node_acl *acl,
	u32 शेष_erl)
अणु
	काष्ठा iscsi_node_attrib *a = &acl->node_attrib;

	अगर (शेष_erl != 0 && शेष_erl != 1 && शेष_erl != 2) अणु
		pr_err("Requested default ERL: %u not 0, 1, or 2\n",
				शेष_erl);
		वापस -EINVAL;
	पूर्ण

	a->शेष_erl = शेष_erl;
	pr_debug("Set use ERL0 flag to %u for Initiator"
		" Node %s\n", a->शेष_erl,
		iscsit_na_get_initiatorname(acl));

	वापस 0;
पूर्ण
