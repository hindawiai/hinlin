<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains मुख्य functions related to iSCSI Parameter negotiation.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/uपन.स> /* काष्ठा kvec */
#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target_parameters.h"

पूर्णांक iscsi_login_rx_data(
	काष्ठा iscsi_conn *conn,
	अक्षर *buf,
	पूर्णांक length)
अणु
	पूर्णांक rx_got;
	काष्ठा kvec iov;

	स_रखो(&iov, 0, माप(काष्ठा kvec));
	iov.iov_len	= length;
	iov.iov_base	= buf;

	rx_got = rx_data(conn, &iov, 1, length);
	अगर (rx_got != length) अणु
		pr_err("rx_data returned %d, expecting %d.\n",
				rx_got, length);
		वापस -1;
	पूर्ण

	वापस 0 ;
पूर्ण

पूर्णांक iscsi_login_tx_data(
	काष्ठा iscsi_conn *conn,
	अक्षर *pdu_buf,
	अक्षर *text_buf,
	पूर्णांक text_length)
अणु
	पूर्णांक length, tx_sent, iov_cnt = 1;
	काष्ठा kvec iov[2];

	length = (ISCSI_HDR_LEN + text_length);

	स_रखो(&iov[0], 0, 2 * माप(काष्ठा kvec));
	iov[0].iov_len		= ISCSI_HDR_LEN;
	iov[0].iov_base		= pdu_buf;

	अगर (text_buf && text_length) अणु
		iov[1].iov_len	= text_length;
		iov[1].iov_base	= text_buf;
		iov_cnt++;
	पूर्ण

	tx_sent = tx_data(conn, &iov[0], iov_cnt, length);
	अगर (tx_sent != length) अणु
		pr_err("tx_data returned %d, expecting %d.\n",
				tx_sent, length);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम iscsi_dump_conn_ops(काष्ठा iscsi_conn_ops *conn_ops)
अणु
	pr_debug("HeaderDigest: %s\n", (conn_ops->HeaderDigest) ?
				"CRC32C" : "None");
	pr_debug("DataDigest: %s\n", (conn_ops->DataDigest) ?
				"CRC32C" : "None");
	pr_debug("MaxRecvDataSegmentLength: %u\n",
				conn_ops->MaxRecvDataSegmentLength);
पूर्ण

व्योम iscsi_dump_sess_ops(काष्ठा iscsi_sess_ops *sess_ops)
अणु
	pr_debug("InitiatorName: %s\n", sess_ops->InitiatorName);
	pr_debug("InitiatorAlias: %s\n", sess_ops->InitiatorAlias);
	pr_debug("TargetName: %s\n", sess_ops->TargetName);
	pr_debug("TargetAlias: %s\n", sess_ops->TargetAlias);
	pr_debug("TargetPortalGroupTag: %hu\n",
			sess_ops->TargetPortalGroupTag);
	pr_debug("MaxConnections: %hu\n", sess_ops->MaxConnections);
	pr_debug("InitialR2T: %s\n",
			(sess_ops->InitialR2T) ? "Yes" : "No");
	pr_debug("ImmediateData: %s\n", (sess_ops->ImmediateData) ?
			"Yes" : "No");
	pr_debug("MaxBurstLength: %u\n", sess_ops->MaxBurstLength);
	pr_debug("FirstBurstLength: %u\n", sess_ops->FirstBurstLength);
	pr_debug("DefaultTime2Wait: %hu\n", sess_ops->DefaultTime2Wait);
	pr_debug("DefaultTime2Retain: %hu\n",
			sess_ops->DefaultTime2Retain);
	pr_debug("MaxOutstandingR2T: %hu\n",
			sess_ops->MaxOutstandingR2T);
	pr_debug("DataPDUInOrder: %s\n",
			(sess_ops->DataPDUInOrder) ? "Yes" : "No");
	pr_debug("DataSequenceInOrder: %s\n",
			(sess_ops->DataSequenceInOrder) ? "Yes" : "No");
	pr_debug("ErrorRecoveryLevel: %hu\n",
			sess_ops->ErrorRecoveryLevel);
	pr_debug("SessionType: %s\n", (sess_ops->SessionType) ?
			"Discovery" : "Normal");
पूर्ण

व्योम iscsi_prपूर्णांक_params(काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_param *param;

	list_क्रम_each_entry(param, &param_list->param_list, p_list)
		pr_debug("%s: %s\n", param->name, param->value);
पूर्ण

अटल काष्ठा iscsi_param *iscsi_set_शेष_param(काष्ठा iscsi_param_list *param_list,
		अक्षर *name, अक्षर *value, u8 phase, u8 scope, u8 sender,
		u16 type_range, u8 use)
अणु
	काष्ठा iscsi_param *param = शून्य;

	param = kzalloc(माप(काष्ठा iscsi_param), GFP_KERNEL);
	अगर (!param) अणु
		pr_err("Unable to allocate memory for parameter.\n");
		जाओ out;
	पूर्ण
	INIT_LIST_HEAD(&param->p_list);

	param->name = kstrdup(name, GFP_KERNEL);
	अगर (!param->name) अणु
		pr_err("Unable to allocate memory for parameter name.\n");
		जाओ out;
	पूर्ण

	param->value = kstrdup(value, GFP_KERNEL);
	अगर (!param->value) अणु
		pr_err("Unable to allocate memory for parameter value.\n");
		जाओ out;
	पूर्ण

	param->phase		= phase;
	param->scope		= scope;
	param->sender		= sender;
	param->use		= use;
	param->type_range	= type_range;

	चयन (param->type_range) अणु
	हाल TYPदुस्फल_BOOL_AND:
		param->type = TYPE_BOOL_AND;
		अवरोध;
	हाल TYPदुस्फल_BOOL_OR:
		param->type = TYPE_BOOL_OR;
		अवरोध;
	हाल TYPदुस्फल_0_TO_2:
	हाल TYPदुस्फल_0_TO_3600:
	हाल TYPदुस्फल_0_TO_32767:
	हाल TYPदुस्फल_0_TO_65535:
	हाल TYPदुस्फल_1_TO_65535:
	हाल TYPदुस्फल_2_TO_3600:
	हाल TYPदुस्फल_512_TO_16777215:
		param->type = TYPE_NUMBER;
		अवरोध;
	हाल TYPदुस्फल_AUTH:
	हाल TYPदुस्फल_DIGEST:
		param->type = TYPE_VALUE_LIST | TYPE_STRING;
		अवरोध;
	हाल TYPदुस्फल_ISCSINAME:
	हाल TYPदुस्फल_SESSIONTYPE:
	हाल TYPदुस्फल_TARGETADDRESS:
	हाल TYPदुस्फल_UTF8:
		param->type = TYPE_STRING;
		अवरोध;
	शेष:
		pr_err("Unknown type_range 0x%02x\n",
				param->type_range);
		जाओ out;
	पूर्ण
	list_add_tail(&param->p_list, &param_list->param_list);

	वापस param;
out:
	अगर (param) अणु
		kमुक्त(param->value);
		kमुक्त(param->name);
		kमुक्त(param);
	पूर्ण

	वापस शून्य;
पूर्ण

/* #warning Add extension keys */
पूर्णांक iscsi_create_शेष_params(काष्ठा iscsi_param_list **param_list_ptr)
अणु
	काष्ठा iscsi_param *param = शून्य;
	काष्ठा iscsi_param_list *pl;

	pl = kzalloc(माप(काष्ठा iscsi_param_list), GFP_KERNEL);
	अगर (!pl) अणु
		pr_err("Unable to allocate memory for"
				" struct iscsi_param_list.\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&pl->param_list);
	INIT_LIST_HEAD(&pl->extra_response_list);

	/*
	 * The क्रमmat क्रम setting the initial parameter definitions are:
	 *
	 * Parameter name:
	 * Initial value:
	 * Allowable phase:
	 * Scope:
	 * Allowable senders:
	 * Typerange:
	 * Use:
	 */
	param = iscsi_set_शेष_param(pl, AUTHMETHOD, INITIAL_AUTHMETHOD,
			PHASE_SECURITY, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_AUTH, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, HEADERDIGEST, INITIAL_HEADERDIGEST,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_DIGEST, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, DATADIGEST, INITIAL_DATADIGEST,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_DIGEST, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, MAXCONNECTIONS,
			INITIAL_MAXCONNECTIONS, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_1_TO_65535, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, SENDTARGETS, INITIAL_SENDTARGETS,
			PHASE_FFP0, SCOPE_SESSION_WIDE, SENDER_INITIATOR,
			TYPदुस्फल_UTF8, 0);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, TARGETNAME, INITIAL_TARGETNAME,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_ISCSINAME, USE_ALL);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, INITIATORNAME,
			INITIAL_INITIATORNAME, PHASE_DECLARATIVE,
			SCOPE_SESSION_WIDE, SENDER_INITIATOR,
			TYPदुस्फल_ISCSINAME, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, TARGETALIAS, INITIAL_TARGETALIAS,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_TARGET,
			TYPदुस्फल_UTF8, USE_ALL);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, INITIATORALIAS,
			INITIAL_INITIATORALIAS, PHASE_DECLARATIVE,
			SCOPE_SESSION_WIDE, SENDER_INITIATOR, TYPदुस्फल_UTF8,
			USE_ALL);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, TARGETADDRESS,
			INITIAL_TARGETADDRESS, PHASE_DECLARATIVE,
			SCOPE_SESSION_WIDE, SENDER_TARGET,
			TYPदुस्फल_TARGETADDRESS, USE_ALL);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, TARGETPORTALGROUPTAG,
			INITIAL_TARGETPORTALGROUPTAG,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_TARGET,
			TYPदुस्फल_0_TO_65535, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, INITIALR2T, INITIAL_INITIALR2T,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_BOOL_OR, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, IMMEDIATEDATA,
			INITIAL_IMMEDIATEDATA, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH, TYPदुस्फल_BOOL_AND,
			USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, MAXXMITDATASEGMENTLENGTH,
			INITIAL_MAXXMITDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_512_TO_16777215, USE_ALL);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, MAXRECVDATASEGMENTLENGTH,
			INITIAL_MAXRECVDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_512_TO_16777215, USE_ALL);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, MAXBURSTLENGTH,
			INITIAL_MAXBURSTLENGTH, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_512_TO_16777215, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, FIRSTBURSTLENGTH,
			INITIAL_FIRSTBURSTLENGTH,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_512_TO_16777215, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, DEFAULTTIME2WAIT,
			INITIAL_DEFAULTTIME2WAIT,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_0_TO_3600, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, DEFAULTTIME2RETAIN,
			INITIAL_DEFAULTTIME2RETAIN,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_0_TO_3600, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, MAXOUTSTANDINGR2T,
			INITIAL_MAXOUTSTANDINGR2T,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_1_TO_65535, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, DATAPDUINORDER,
			INITIAL_DATAPDUINORDER, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH, TYPदुस्फल_BOOL_OR,
			USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, DATASEQUENCEINORDER,
			INITIAL_DATASEQUENCEINORDER,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_BOOL_OR, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, ERRORRECOVERYLEVEL,
			INITIAL_ERRORRECOVERYLEVEL,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_0_TO_2, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, SESSIONTYPE, INITIAL_SESSIONTYPE,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_INITIATOR,
			TYPदुस्फल_SESSIONTYPE, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, IFMARKER, INITIAL_IFMARKER,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_BOOL_AND, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, OFMARKER, INITIAL_OFMARKER,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_BOOL_AND, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, IFMARKINT, INITIAL_IFMARKINT,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_UTF8, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, OFMARKINT, INITIAL_OFMARKINT,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_UTF8, USE_INITIAL_ONLY);
	अगर (!param)
		जाओ out;

	/*
	 * Extra parameters क्रम ISER from RFC-5046
	 */
	param = iscsi_set_शेष_param(pl, RDMAEXTENSIONS, INITIAL_RDMAEXTENSIONS,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPदुस्फल_BOOL_AND, USE_LEADING_ONLY);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, INITIATORRECVDATASEGMENTLENGTH,
			INITIAL_INITIATORRECVDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_512_TO_16777215, USE_ALL);
	अगर (!param)
		जाओ out;

	param = iscsi_set_शेष_param(pl, TARGETRECVDATASEGMENTLENGTH,
			INITIAL_TARGETRECVDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPदुस्फल_512_TO_16777215, USE_ALL);
	अगर (!param)
		जाओ out;

	*param_list_ptr = pl;
	वापस 0;
out:
	iscsi_release_param_list(pl);
	वापस -1;
पूर्ण

पूर्णांक iscsi_set_keys_to_negotiate(
	काष्ठा iscsi_param_list *param_list,
	bool iser)
अणु
	काष्ठा iscsi_param *param;

	param_list->iser = iser;

	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		param->state = 0;
		अगर (!म_भेद(param->name, AUTHMETHOD)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, HEADERDIGEST)) अणु
			अगर (!iser)
				SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DATADIGEST)) अणु
			अगर (!iser)
				SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXCONNECTIONS)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETNAME)) अणु
			जारी;
		पूर्ण अन्यथा अगर (!म_भेद(param->name, INITIATORNAME)) अणु
			जारी;
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETALIAS)) अणु
			अगर (param->value)
				SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, INITIATORALIAS)) अणु
			जारी;
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETPORTALGROUPTAG)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, INITIALR2T)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, IMMEDIATEDATA)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXRECVDATASEGMENTLENGTH)) अणु
			अगर (!iser)
				SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXXMITDATASEGMENTLENGTH)) अणु
			जारी;
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXBURSTLENGTH)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, FIRSTBURSTLENGTH)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DEFAULTTIME2WAIT)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DEFAULTTIME2RETAIN)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXOUTSTANDINGR2T)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DATAPDUINORDER)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DATASEQUENCEINORDER)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, ERRORRECOVERYLEVEL)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, SESSIONTYPE)) अणु
			SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, IFMARKER)) अणु
			SET_PSTATE_REJECT(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, OFMARKER)) अणु
			SET_PSTATE_REJECT(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, IFMARKINT)) अणु
			SET_PSTATE_REJECT(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, OFMARKINT)) अणु
			SET_PSTATE_REJECT(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, RDMAEXTENSIONS)) अणु
			अगर (iser)
				SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, INITIATORRECVDATASEGMENTLENGTH)) अणु
			अगर (iser)
				SET_PSTATE_NEGOTIATE(param);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETRECVDATASEGMENTLENGTH)) अणु
			अगर (iser)
				SET_PSTATE_NEGOTIATE(param);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsi_set_keys_irrelevant_क्रम_discovery(
	काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_param *param;

	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		अगर (!म_भेद(param->name, MAXCONNECTIONS))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, INITIALR2T))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, IMMEDIATEDATA))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, MAXBURSTLENGTH))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, FIRSTBURSTLENGTH))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, MAXOUTSTANDINGR2T))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, DATAPDUINORDER))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, DATASEQUENCEINORDER))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, ERRORRECOVERYLEVEL))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, DEFAULTTIME2WAIT))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, DEFAULTTIME2RETAIN))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, IFMARKER))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, OFMARKER))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, IFMARKINT))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, OFMARKINT))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, RDMAEXTENSIONS))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, INITIATORRECVDATASEGMENTLENGTH))
			param->state &= ~PSTATE_NEGOTIATE;
		अन्यथा अगर (!म_भेद(param->name, TARGETRECVDATASEGMENTLENGTH))
			param->state &= ~PSTATE_NEGOTIATE;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsi_copy_param_list(
	काष्ठा iscsi_param_list **dst_param_list,
	काष्ठा iscsi_param_list *src_param_list,
	पूर्णांक leading)
अणु
	काष्ठा iscsi_param *param = शून्य;
	काष्ठा iscsi_param *new_param = शून्य;
	काष्ठा iscsi_param_list *param_list = शून्य;

	param_list = kzalloc(माप(काष्ठा iscsi_param_list), GFP_KERNEL);
	अगर (!param_list) अणु
		pr_err("Unable to allocate memory for struct iscsi_param_list.\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&param_list->param_list);
	INIT_LIST_HEAD(&param_list->extra_response_list);

	list_क्रम_each_entry(param, &src_param_list->param_list, p_list) अणु
		अगर (!leading && (param->scope & SCOPE_SESSION_WIDE)) अणु
			अगर ((म_भेद(param->name, "TargetName") != 0) &&
			    (म_भेद(param->name, "InitiatorName") != 0) &&
			    (म_भेद(param->name, "TargetPortalGroupTag") != 0))
				जारी;
		पूर्ण

		new_param = kzalloc(माप(काष्ठा iscsi_param), GFP_KERNEL);
		अगर (!new_param) अणु
			pr_err("Unable to allocate memory for struct iscsi_param.\n");
			जाओ err_out;
		पूर्ण

		new_param->name = kstrdup(param->name, GFP_KERNEL);
		new_param->value = kstrdup(param->value, GFP_KERNEL);
		अगर (!new_param->value || !new_param->name) अणु
			kमुक्त(new_param->value);
			kमुक्त(new_param->name);
			kमुक्त(new_param);
			pr_err("Unable to allocate memory for parameter name/value.\n");
			जाओ err_out;
		पूर्ण

		new_param->set_param = param->set_param;
		new_param->phase = param->phase;
		new_param->scope = param->scope;
		new_param->sender = param->sender;
		new_param->type = param->type;
		new_param->use = param->use;
		new_param->type_range = param->type_range;

		list_add_tail(&new_param->p_list, &param_list->param_list);
	पूर्ण

	अगर (!list_empty(&param_list->param_list)) अणु
		*dst_param_list = param_list;
	पूर्ण अन्यथा अणु
		pr_err("No parameters allocated.\n");
		जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	iscsi_release_param_list(param_list);
	वापस -ENOMEM;
पूर्ण

अटल व्योम iscsi_release_extra_responses(काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_extra_response *er, *er_पंचांगp;

	list_क्रम_each_entry_safe(er, er_पंचांगp, &param_list->extra_response_list,
			er_list) अणु
		list_del(&er->er_list);
		kमुक्त(er);
	पूर्ण
पूर्ण

व्योम iscsi_release_param_list(काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_param *param, *param_पंचांगp;

	list_क्रम_each_entry_safe(param, param_पंचांगp, &param_list->param_list,
			p_list) अणु
		list_del(&param->p_list);

		kमुक्त(param->name);
		kमुक्त(param->value);
		kमुक्त(param);
	पूर्ण

	iscsi_release_extra_responses(param_list);

	kमुक्त(param_list);
पूर्ण

काष्ठा iscsi_param *iscsi_find_param_from_key(
	अक्षर *key,
	काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_param *param;

	अगर (!key || !param_list) अणु
		pr_err("Key or parameter list pointer is NULL.\n");
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		अगर (!म_भेद(key, param->name))
			वापस param;
	पूर्ण

	pr_err("Unable to locate key \"%s\".\n", key);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(iscsi_find_param_from_key);

पूर्णांक iscsi_extract_key_value(अक्षर *textbuf, अक्षर **key, अक्षर **value)
अणु
	*value = म_अक्षर(textbuf, '=');
	अगर (!*value) अणु
		pr_err("Unable to locate \"=\" separator for key,"
				" ignoring request.\n");
		वापस -1;
	पूर्ण

	*key = textbuf;
	**value = '\0';
	*value = *value + 1;

	वापस 0;
पूर्ण

पूर्णांक iscsi_update_param_value(काष्ठा iscsi_param *param, अक्षर *value)
अणु
	kमुक्त(param->value);

	param->value = kstrdup(value, GFP_KERNEL);
	अगर (!param->value) अणु
		pr_err("Unable to allocate memory for value.\n");
		वापस -ENOMEM;
	पूर्ण

	pr_debug("iSCSI Parameter updated to %s=%s\n",
			param->name, param->value);
	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_add_notunderstood_response(
	अक्षर *key,
	अक्षर *value,
	काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_extra_response *extra_response;

	अगर (म_माप(value) > VALUE_MAXLEN) अणु
		pr_err("Value for notunderstood key \"%s\" exceeds %d,"
			" protocol error.\n", key, VALUE_MAXLEN);
		वापस -1;
	पूर्ण

	extra_response = kzalloc(माप(काष्ठा iscsi_extra_response), GFP_KERNEL);
	अगर (!extra_response) अणु
		pr_err("Unable to allocate memory for"
			" struct iscsi_extra_response.\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&extra_response->er_list);

	strlcpy(extra_response->key, key, माप(extra_response->key));
	strlcpy(extra_response->value, NOTUNDERSTOOD,
		माप(extra_response->value));

	list_add_tail(&extra_response->er_list,
			&param_list->extra_response_list);
	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_check_क्रम_auth_key(अक्षर *key)
अणु
	/*
	 * RFC 1994
	 */
	अगर (!म_भेद(key, "CHAP_A") || !म_भेद(key, "CHAP_I") ||
	    !म_भेद(key, "CHAP_C") || !म_भेद(key, "CHAP_N") ||
	    !म_भेद(key, "CHAP_R"))
		वापस 1;

	/*
	 * RFC 2945
	 */
	अगर (!म_भेद(key, "SRP_U") || !म_भेद(key, "SRP_N") ||
	    !म_भेद(key, "SRP_g") || !म_भेद(key, "SRP_s") ||
	    !म_भेद(key, "SRP_A") || !म_भेद(key, "SRP_B") ||
	    !म_भेद(key, "SRP_M") || !म_भेद(key, "SRP_HM"))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम iscsi_check_proposer_क्रम_optional_reply(काष्ठा iscsi_param *param,
						    bool keys_workaround)
अणु
	अगर (IS_TYPE_BOOL_AND(param)) अणु
		अगर (!म_भेद(param->value, NO))
			SET_PSTATE_REPLY_OPTIONAL(param);
	पूर्ण अन्यथा अगर (IS_TYPE_BOOL_OR(param)) अणु
		अगर (!म_भेद(param->value, YES))
			SET_PSTATE_REPLY_OPTIONAL(param);

		अगर (keys_workaround) अणु
			/*
			 * Required क्रम gPXE iSCSI boot client
			 */
			अगर (!म_भेद(param->name, IMMEDIATEDATA))
				SET_PSTATE_REPLY_OPTIONAL(param);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_TYPE_NUMBER(param)) अणु
		अगर (!म_भेद(param->name, MAXRECVDATASEGMENTLENGTH))
			SET_PSTATE_REPLY_OPTIONAL(param);

		अगर (keys_workaround) अणु
			/*
			 * Required क्रम Mellanox Flexboot PXE boot ROM
			 */
			अगर (!म_भेद(param->name, FIRSTBURSTLENGTH))
				SET_PSTATE_REPLY_OPTIONAL(param);

			/*
			 * Required क्रम gPXE iSCSI boot client
			 */
			अगर (!म_भेद(param->name, MAXCONNECTIONS))
				SET_PSTATE_REPLY_OPTIONAL(param);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_PHASE_DECLARATIVE(param))
		SET_PSTATE_REPLY_OPTIONAL(param);
पूर्ण

अटल पूर्णांक iscsi_check_boolean_value(काष्ठा iscsi_param *param, अक्षर *value)
अणु
	अगर (म_भेद(value, YES) && म_भेद(value, NO)) अणु
		pr_err("Illegal value for \"%s\", must be either"
			" \"%s\" or \"%s\".\n", param->name, YES, NO);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_check_numerical_value(काष्ठा iscsi_param *param, अक्षर *value_ptr)
अणु
	अक्षर *पंचांगpptr;
	पूर्णांक value = 0;

	value = simple_म_से_अदीर्घ(value_ptr, &पंचांगpptr, 0);

	अगर (IS_TYPदुस्फल_0_TO_2(param)) अणु
		अगर ((value < 0) || (value > 2)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 2.\n", param->name);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (IS_TYPदुस्फल_0_TO_3600(param)) अणु
		अगर ((value < 0) || (value > 3600)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 3600.\n", param->name);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (IS_TYPदुस्फल_0_TO_32767(param)) अणु
		अगर ((value < 0) || (value > 32767)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 32767.\n", param->name);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (IS_TYPदुस्फल_0_TO_65535(param)) अणु
		अगर ((value < 0) || (value > 65535)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 65535.\n", param->name);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (IS_TYPदुस्फल_1_TO_65535(param)) अणु
		अगर ((value < 1) || (value > 65535)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" between 1 and 65535.\n", param->name);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (IS_TYPदुस्फल_2_TO_3600(param)) अणु
		अगर ((value < 2) || (value > 3600)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" between 2 and 3600.\n", param->name);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (IS_TYPदुस्फल_512_TO_16777215(param)) अणु
		अगर ((value < 512) || (value > 16777215)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" between 512 and 16777215.\n", param->name);
			वापस -1;
		पूर्ण
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_check_string_or_list_value(काष्ठा iscsi_param *param, अक्षर *value)
अणु
	अगर (IS_PSTATE_PROPOSER(param))
		वापस 0;

	अगर (IS_TYPदुस्फल_AUTH_PARAM(param)) अणु
		अगर (म_भेद(value, KRB5) && म_भेद(value, SPKM1) &&
		    म_भेद(value, SPKM2) && म_भेद(value, SRP) &&
		    म_भेद(value, CHAP) && म_भेद(value, NONE)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" \"%s\", \"%s\", \"%s\", \"%s\", \"%s\""
				" or \"%s\".\n", param->name, KRB5,
					SPKM1, SPKM2, SRP, CHAP, NONE);
			वापस -1;
		पूर्ण
	पूर्ण
	अगर (IS_TYPदुस्फल_DIGEST_PARAM(param)) अणु
		अगर (म_भेद(value, CRC32C) && म_भेद(value, NONE)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" \"%s\" or \"%s\".\n", param->name,
					CRC32C, NONE);
			वापस -1;
		पूर्ण
	पूर्ण
	अगर (IS_TYPदुस्फल_SESSIONTYPE(param)) अणु
		अगर (म_भेद(value, DISCOVERY) && म_भेद(value, NORMAL)) अणु
			pr_err("Illegal value for \"%s\", must be"
				" \"%s\" or \"%s\".\n", param->name,
					DISCOVERY, NORMAL);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अक्षर *iscsi_check_valuelist_क्रम_support(
	काष्ठा iscsi_param *param,
	अक्षर *value)
अणु
	अक्षर *पंचांगp1 = शून्य, *पंचांगp2 = शून्य;
	अक्षर *acceptor_values = शून्य, *proposer_values = शून्य;

	acceptor_values = param->value;
	proposer_values = value;

	करो अणु
		अगर (!proposer_values)
			वापस शून्य;
		पंचांगp1 = म_अक्षर(proposer_values, ',');
		अगर (पंचांगp1)
			*पंचांगp1 = '\0';
		acceptor_values = param->value;
		करो अणु
			अगर (!acceptor_values) अणु
				अगर (पंचांगp1)
					*पंचांगp1 = ',';
				वापस शून्य;
			पूर्ण
			पंचांगp2 = म_अक्षर(acceptor_values, ',');
			अगर (पंचांगp2)
				*पंचांगp2 = '\0';
			अगर (!म_भेद(acceptor_values, proposer_values)) अणु
				अगर (पंचांगp2)
					*पंचांगp2 = ',';
				जाओ out;
			पूर्ण
			अगर (पंचांगp2)
				*पंचांगp2++ = ',';

			acceptor_values = पंचांगp2;
		पूर्ण जबतक (acceptor_values);
		अगर (पंचांगp1)
			*पंचांगp1++ = ',';
		proposer_values = पंचांगp1;
	पूर्ण जबतक (proposer_values);

out:
	वापस proposer_values;
पूर्ण

अटल पूर्णांक iscsi_check_acceptor_state(काष्ठा iscsi_param *param, अक्षर *value,
				काष्ठा iscsi_conn *conn)
अणु
	u8 acceptor_boolean_value = 0, proposer_boolean_value = 0;
	अक्षर *negotiated_value = शून्य;

	अगर (IS_PSTATE_ACCEPTOR(param)) अणु
		pr_err("Received key \"%s\" twice, protocol error.\n",
				param->name);
		वापस -1;
	पूर्ण

	अगर (IS_PSTATE_REJECT(param))
		वापस 0;

	अगर (IS_TYPE_BOOL_AND(param)) अणु
		अगर (!म_भेद(value, YES))
			proposer_boolean_value = 1;
		अगर (!म_भेद(param->value, YES))
			acceptor_boolean_value = 1;
		अगर (acceptor_boolean_value && proposer_boolean_value)
			करो अणुपूर्ण जबतक (0);
		अन्यथा अणु
			अगर (iscsi_update_param_value(param, NO) < 0)
				वापस -1;
			अगर (!proposer_boolean_value)
				SET_PSTATE_REPLY_OPTIONAL(param);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_TYPE_BOOL_OR(param)) अणु
		अगर (!म_भेद(value, YES))
			proposer_boolean_value = 1;
		अगर (!म_भेद(param->value, YES))
			acceptor_boolean_value = 1;
		अगर (acceptor_boolean_value || proposer_boolean_value) अणु
			अगर (iscsi_update_param_value(param, YES) < 0)
				वापस -1;
			अगर (proposer_boolean_value)
				SET_PSTATE_REPLY_OPTIONAL(param);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_TYPE_NUMBER(param)) अणु
		अक्षर *पंचांगpptr, buf[11];
		u32 acceptor_value = simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
		u32 proposer_value = simple_म_से_अदीर्घ(value, &पंचांगpptr, 0);

		स_रखो(buf, 0, माप(buf));

		अगर (!म_भेद(param->name, MAXCONNECTIONS) ||
		    !म_भेद(param->name, MAXBURSTLENGTH) ||
		    !म_भेद(param->name, FIRSTBURSTLENGTH) ||
		    !म_भेद(param->name, MAXOUTSTANDINGR2T) ||
		    !म_भेद(param->name, DEFAULTTIME2RETAIN) ||
		    !म_भेद(param->name, ERRORRECOVERYLEVEL)) अणु
			अगर (proposer_value > acceptor_value) अणु
				प्र_लिखो(buf, "%u", acceptor_value);
				अगर (iscsi_update_param_value(param,
						&buf[0]) < 0)
					वापस -1;
			पूर्ण अन्यथा अणु
				अगर (iscsi_update_param_value(param, value) < 0)
					वापस -1;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DEFAULTTIME2WAIT)) अणु
			अगर (acceptor_value > proposer_value) अणु
				प्र_लिखो(buf, "%u", acceptor_value);
				अगर (iscsi_update_param_value(param,
						&buf[0]) < 0)
					वापस -1;
			पूर्ण अन्यथा अणु
				अगर (iscsi_update_param_value(param, value) < 0)
					वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (iscsi_update_param_value(param, value) < 0)
				वापस -1;
		पूर्ण

		अगर (!म_भेद(param->name, MAXRECVDATASEGMENTLENGTH)) अणु
			काष्ठा iscsi_param *param_mxdsl;
			अचिन्हित दीर्घ दीर्घ पंचांगp;
			पूर्णांक rc;

			rc = kम_से_अदीर्घl(param->value, 0, &पंचांगp);
			अगर (rc < 0)
				वापस -1;

			conn->conn_ops->MaxRecvDataSegmentLength = पंचांगp;
			pr_debug("Saving op->MaxRecvDataSegmentLength from"
				" original initiator received value: %u\n",
				conn->conn_ops->MaxRecvDataSegmentLength);

			param_mxdsl = iscsi_find_param_from_key(
						MAXXMITDATASEGMENTLENGTH,
						conn->param_list);
			अगर (!param_mxdsl)
				वापस -1;

			rc = iscsi_update_param_value(param,
						param_mxdsl->value);
			अगर (rc < 0)
				वापस -1;

			pr_debug("Updated %s to target MXDSL value: %s\n",
					param->name, param->value);
		पूर्ण
	पूर्ण अन्यथा अगर (IS_TYPE_VALUE_LIST(param)) अणु
		negotiated_value = iscsi_check_valuelist_क्रम_support(
					param, value);
		अगर (!negotiated_value) अणु
			pr_err("Proposer's value list \"%s\" contains"
				" no valid values from Acceptor's value list"
				" \"%s\".\n", value, param->value);
			वापस -1;
		पूर्ण
		अगर (iscsi_update_param_value(param, negotiated_value) < 0)
			वापस -1;
	पूर्ण अन्यथा अगर (IS_PHASE_DECLARATIVE(param)) अणु
		अगर (iscsi_update_param_value(param, value) < 0)
			वापस -1;
		SET_PSTATE_REPLY_OPTIONAL(param);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_check_proposer_state(काष्ठा iscsi_param *param, अक्षर *value)
अणु
	अगर (IS_PSTATE_RESPONSE_GOT(param)) अणु
		pr_err("Received key \"%s\" twice, protocol error.\n",
				param->name);
		वापस -1;
	पूर्ण

	अगर (IS_TYPE_VALUE_LIST(param)) अणु
		अक्षर *comma_ptr = शून्य, *पंचांगp_ptr = शून्य;

		comma_ptr = म_अक्षर(value, ',');
		अगर (comma_ptr) अणु
			pr_err("Illegal \",\" in response for \"%s\".\n",
					param->name);
			वापस -1;
		पूर्ण

		पंचांगp_ptr = iscsi_check_valuelist_क्रम_support(param, value);
		अगर (!पंचांगp_ptr)
			वापस -1;
	पूर्ण

	अगर (iscsi_update_param_value(param, value) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_check_value(काष्ठा iscsi_param *param, अक्षर *value)
अणु
	अक्षर *comma_ptr = शून्य;

	अगर (!म_भेद(value, REJECT)) अणु
		अगर (!म_भेद(param->name, IFMARKINT) ||
		    !म_भेद(param->name, OFMARKINT)) अणु
			/*
			 * Reject is not fatal क्रम [I,O]FMarkInt,  and causes
			 * [I,O]FMarker to be reset to No. (See iSCSI v20 A.3.2)
			 */
			SET_PSTATE_REJECT(param);
			वापस 0;
		पूर्ण
		pr_err("Received %s=%s\n", param->name, value);
		वापस -1;
	पूर्ण
	अगर (!म_भेद(value, IRRELEVANT)) अणु
		pr_debug("Received %s=%s\n", param->name, value);
		SET_PSTATE_IRRELEVANT(param);
		वापस 0;
	पूर्ण
	अगर (!म_भेद(value, NOTUNDERSTOOD)) अणु
		अगर (!IS_PSTATE_PROPOSER(param)) अणु
			pr_err("Received illegal offer %s=%s\n",
				param->name, value);
			वापस -1;
		पूर्ण

/* #warning FIXME: Add check क्रम X-ExtensionKey here */
		pr_err("Standard iSCSI key \"%s\" cannot be answered"
			" with \"%s\", protocol error.\n", param->name, value);
		वापस -1;
	पूर्ण

	करो अणु
		comma_ptr = शून्य;
		comma_ptr = म_अक्षर(value, ',');

		अगर (comma_ptr && !IS_TYPE_VALUE_LIST(param)) अणु
			pr_err("Detected value separator \",\", but"
				" key \"%s\" does not allow a value list,"
				" protocol error.\n", param->name);
			वापस -1;
		पूर्ण
		अगर (comma_ptr)
			*comma_ptr = '\0';

		अगर (म_माप(value) > VALUE_MAXLEN) अणु
			pr_err("Value for key \"%s\" exceeds %d,"
				" protocol error.\n", param->name,
				VALUE_MAXLEN);
			वापस -1;
		पूर्ण

		अगर (IS_TYPE_BOOL_AND(param) || IS_TYPE_BOOL_OR(param)) अणु
			अगर (iscsi_check_boolean_value(param, value) < 0)
				वापस -1;
		पूर्ण अन्यथा अगर (IS_TYPE_NUMBER(param)) अणु
			अगर (iscsi_check_numerical_value(param, value) < 0)
				वापस -1;
		पूर्ण अन्यथा अगर (IS_TYPE_STRING(param) || IS_TYPE_VALUE_LIST(param)) अणु
			अगर (iscsi_check_string_or_list_value(param, value) < 0)
				वापस -1;
		पूर्ण अन्यथा अणु
			pr_err("Huh? 0x%02x\n", param->type);
			वापस -1;
		पूर्ण

		अगर (comma_ptr)
			*comma_ptr++ = ',';

		value = comma_ptr;
	पूर्ण जबतक (value);

	वापस 0;
पूर्ण

अटल काष्ठा iscsi_param *__iscsi_check_key(
	अक्षर *key,
	पूर्णांक sender,
	काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_param *param;

	अगर (म_माप(key) > KEY_MAXLEN) अणु
		pr_err("Length of key name \"%s\" exceeds %d.\n",
			key, KEY_MAXLEN);
		वापस शून्य;
	पूर्ण

	param = iscsi_find_param_from_key(key, param_list);
	अगर (!param)
		वापस शून्य;

	अगर ((sender & SENDER_INITIATOR) && !IS_SENDER_INITIATOR(param)) अणु
		pr_err("Key \"%s\" may not be sent to %s,"
			" protocol error.\n", param->name,
			(sender & SENDER_RECEIVER) ? "target" : "initiator");
		वापस शून्य;
	पूर्ण

	अगर ((sender & SENDER_TARGET) && !IS_SENDER_TARGET(param)) अणु
		pr_err("Key \"%s\" may not be sent to %s,"
			" protocol error.\n", param->name,
			(sender & SENDER_RECEIVER) ? "initiator" : "target");
		वापस शून्य;
	पूर्ण

	वापस param;
पूर्ण

अटल काष्ठा iscsi_param *iscsi_check_key(
	अक्षर *key,
	पूर्णांक phase,
	पूर्णांक sender,
	काष्ठा iscsi_param_list *param_list)
अणु
	काष्ठा iscsi_param *param;
	/*
	 * Key name length must not exceed 63 bytes. (See iSCSI v20 5.1)
	 */
	अगर (म_माप(key) > KEY_MAXLEN) अणु
		pr_err("Length of key name \"%s\" exceeds %d.\n",
			key, KEY_MAXLEN);
		वापस शून्य;
	पूर्ण

	param = iscsi_find_param_from_key(key, param_list);
	अगर (!param)
		वापस शून्य;

	अगर ((sender & SENDER_INITIATOR) && !IS_SENDER_INITIATOR(param)) अणु
		pr_err("Key \"%s\" may not be sent to %s,"
			" protocol error.\n", param->name,
			(sender & SENDER_RECEIVER) ? "target" : "initiator");
		वापस शून्य;
	पूर्ण
	अगर ((sender & SENDER_TARGET) && !IS_SENDER_TARGET(param)) अणु
		pr_err("Key \"%s\" may not be sent to %s,"
				" protocol error.\n", param->name,
			(sender & SENDER_RECEIVER) ? "initiator" : "target");
		वापस शून्य;
	पूर्ण

	अगर (IS_PSTATE_ACCEPTOR(param)) अणु
		pr_err("Key \"%s\" received twice, protocol error.\n",
				key);
		वापस शून्य;
	पूर्ण

	अगर (!phase)
		वापस param;

	अगर (!(param->phase & phase)) अणु
		pr_err("Key \"%s\" may not be negotiated during ",
				param->name);
		चयन (phase) अणु
		हाल PHASE_SECURITY:
			pr_debug("Security phase.\n");
			अवरोध;
		हाल PHASE_OPERATIONAL:
			pr_debug("Operational phase.\n");
			अवरोध;
		शेष:
			pr_debug("Unknown phase.\n");
		पूर्ण
		वापस शून्य;
	पूर्ण

	वापस param;
पूर्ण

अटल पूर्णांक iscsi_enक्रमce_पूर्णांकegrity_rules(
	u8 phase,
	काष्ठा iscsi_param_list *param_list)
अणु
	अक्षर *पंचांगpptr;
	u8 DataSequenceInOrder = 0;
	u8 ErrorRecoveryLevel = 0, SessionType = 0;
	u32 FirstBurstLength = 0, MaxBurstLength = 0;
	काष्ठा iscsi_param *param = शून्य;

	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		अगर (!(param->phase & phase))
			जारी;
		अगर (!म_भेद(param->name, SESSIONTYPE))
			अगर (!म_भेद(param->value, NORMAL))
				SessionType = 1;
		अगर (!म_भेद(param->name, ERRORRECOVERYLEVEL))
			ErrorRecoveryLevel = simple_म_से_अदीर्घ(param->value,
					&पंचांगpptr, 0);
		अगर (!म_भेद(param->name, DATASEQUENCEINORDER))
			अगर (!म_भेद(param->value, YES))
				DataSequenceInOrder = 1;
		अगर (!म_भेद(param->name, MAXBURSTLENGTH))
			MaxBurstLength = simple_म_से_अदीर्घ(param->value,
					&पंचांगpptr, 0);
	पूर्ण

	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		अगर (!(param->phase & phase))
			जारी;
		अगर (!SessionType && !IS_PSTATE_ACCEPTOR(param))
			जारी;
		अगर (!म_भेद(param->name, MAXOUTSTANDINGR2T) &&
		    DataSequenceInOrder && (ErrorRecoveryLevel > 0)) अणु
			अगर (म_भेद(param->value, "1")) अणु
				अगर (iscsi_update_param_value(param, "1") < 0)
					वापस -1;
				pr_debug("Reset \"%s\" to \"%s\".\n",
					param->name, param->value);
			पूर्ण
		पूर्ण
		अगर (!म_भेद(param->name, MAXCONNECTIONS) && !SessionType) अणु
			अगर (म_भेद(param->value, "1")) अणु
				अगर (iscsi_update_param_value(param, "1") < 0)
					वापस -1;
				pr_debug("Reset \"%s\" to \"%s\".\n",
					param->name, param->value);
			पूर्ण
		पूर्ण
		अगर (!म_भेद(param->name, FIRSTBURSTLENGTH)) अणु
			FirstBurstLength = simple_म_से_अदीर्घ(param->value,
					&पंचांगpptr, 0);
			अगर (FirstBurstLength > MaxBurstLength) अणु
				अक्षर पंचांगpbuf[11];
				स_रखो(पंचांगpbuf, 0, माप(पंचांगpbuf));
				प्र_लिखो(पंचांगpbuf, "%u", MaxBurstLength);
				अगर (iscsi_update_param_value(param, पंचांगpbuf))
					वापस -1;
				pr_debug("Reset \"%s\" to \"%s\".\n",
					param->name, param->value);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsi_decode_text_input(
	u8 phase,
	u8 sender,
	अक्षर *textbuf,
	u32 length,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_param_list *param_list = conn->param_list;
	अक्षर *पंचांगpbuf, *start = शून्य, *end = शून्य;

	पंचांगpbuf = kzalloc(length + 1, GFP_KERNEL);
	अगर (!पंचांगpbuf) अणु
		pr_err("Unable to allocate %u + 1 bytes for tmpbuf.\n", length);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(पंचांगpbuf, textbuf, length);
	पंचांगpbuf[length] = '\0';
	start = पंचांगpbuf;
	end = (start + length);

	जबतक (start < end) अणु
		अक्षर *key, *value;
		काष्ठा iscsi_param *param;

		अगर (iscsi_extract_key_value(start, &key, &value) < 0)
			जाओ मुक्त_buffer;

		pr_debug("Got key: %s=%s\n", key, value);

		अगर (phase & PHASE_SECURITY) अणु
			अगर (iscsi_check_क्रम_auth_key(key) > 0) अणु
				kमुक्त(पंचांगpbuf);
				वापस 1;
			पूर्ण
		पूर्ण

		param = iscsi_check_key(key, phase, sender, param_list);
		अगर (!param) अणु
			अगर (iscsi_add_notunderstood_response(key, value,
							     param_list) < 0)
				जाओ मुक्त_buffer;

			start += म_माप(key) + म_माप(value) + 2;
			जारी;
		पूर्ण
		अगर (iscsi_check_value(param, value) < 0)
			जाओ मुक्त_buffer;

		start += म_माप(key) + म_माप(value) + 2;

		अगर (IS_PSTATE_PROPOSER(param)) अणु
			अगर (iscsi_check_proposer_state(param, value) < 0)
				जाओ मुक्त_buffer;

			SET_PSTATE_RESPONSE_GOT(param);
		पूर्ण अन्यथा अणु
			अगर (iscsi_check_acceptor_state(param, value, conn) < 0)
				जाओ मुक्त_buffer;

			SET_PSTATE_ACCEPTOR(param);
		पूर्ण
	पूर्ण

	kमुक्त(पंचांगpbuf);
	वापस 0;

मुक्त_buffer:
	kमुक्त(पंचांगpbuf);
	वापस -1;
पूर्ण

पूर्णांक iscsi_encode_text_output(
	u8 phase,
	u8 sender,
	अक्षर *textbuf,
	u32 *length,
	काष्ठा iscsi_param_list *param_list,
	bool keys_workaround)
अणु
	अक्षर *output_buf = शून्य;
	काष्ठा iscsi_extra_response *er;
	काष्ठा iscsi_param *param;

	output_buf = textbuf + *length;

	अगर (iscsi_enक्रमce_पूर्णांकegrity_rules(phase, param_list) < 0)
		वापस -1;

	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		अगर (!(param->sender & sender))
			जारी;
		अगर (IS_PSTATE_ACCEPTOR(param) &&
		    !IS_PSTATE_RESPONSE_SENT(param) &&
		    !IS_PSTATE_REPLY_OPTIONAL(param) &&
		    (param->phase & phase)) अणु
			*length += प्र_लिखो(output_buf, "%s=%s",
				param->name, param->value);
			*length += 1;
			output_buf = textbuf + *length;
			SET_PSTATE_RESPONSE_SENT(param);
			pr_debug("Sending key: %s=%s\n",
				param->name, param->value);
			जारी;
		पूर्ण
		अगर (IS_PSTATE_NEGOTIATE(param) &&
		    !IS_PSTATE_ACCEPTOR(param) &&
		    !IS_PSTATE_PROPOSER(param) &&
		    (param->phase & phase)) अणु
			*length += प्र_लिखो(output_buf, "%s=%s",
				param->name, param->value);
			*length += 1;
			output_buf = textbuf + *length;
			SET_PSTATE_PROPOSER(param);
			iscsi_check_proposer_क्रम_optional_reply(param,
							        keys_workaround);
			pr_debug("Sending key: %s=%s\n",
				param->name, param->value);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(er, &param_list->extra_response_list, er_list) अणु
		*length += प्र_लिखो(output_buf, "%s=%s", er->key, er->value);
		*length += 1;
		output_buf = textbuf + *length;
		pr_debug("Sending key: %s=%s\n", er->key, er->value);
	पूर्ण
	iscsi_release_extra_responses(param_list);

	वापस 0;
पूर्ण

पूर्णांक iscsi_check_negotiated_keys(काष्ठा iscsi_param_list *param_list)
अणु
	पूर्णांक ret = 0;
	काष्ठा iscsi_param *param;

	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		अगर (IS_PSTATE_NEGOTIATE(param) &&
		    IS_PSTATE_PROPOSER(param) &&
		    !IS_PSTATE_RESPONSE_GOT(param) &&
		    !IS_PSTATE_REPLY_OPTIONAL(param) &&
		    !IS_PHASE_DECLARATIVE(param)) अणु
			pr_err("No response for proposed key \"%s\".\n",
					param->name);
			ret = -1;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक iscsi_change_param_value(
	अक्षर *keyvalue,
	काष्ठा iscsi_param_list *param_list,
	पूर्णांक check_key)
अणु
	अक्षर *key = शून्य, *value = शून्य;
	काष्ठा iscsi_param *param;
	पूर्णांक sender = 0;

	अगर (iscsi_extract_key_value(keyvalue, &key, &value) < 0)
		वापस -1;

	अगर (!check_key) अणु
		param = __iscsi_check_key(keyvalue, sender, param_list);
		अगर (!param)
			वापस -1;
	पूर्ण अन्यथा अणु
		param = iscsi_check_key(keyvalue, 0, sender, param_list);
		अगर (!param)
			वापस -1;

		param->set_param = 1;
		अगर (iscsi_check_value(param, value) < 0) अणु
			param->set_param = 0;
			वापस -1;
		पूर्ण
		param->set_param = 0;
	पूर्ण

	अगर (iscsi_update_param_value(param, value) < 0)
		वापस -1;

	वापस 0;
पूर्ण

व्योम iscsi_set_connection_parameters(
	काष्ठा iscsi_conn_ops *ops,
	काष्ठा iscsi_param_list *param_list)
अणु
	अक्षर *पंचांगpptr;
	काष्ठा iscsi_param *param;

	pr_debug("---------------------------------------------------"
			"---------------\n");
	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		/*
		 * Special हाल to set MAXXMITDATASEGMENTLENGTH from the
		 * target requested MaxRecvDataSegmentLength, even though
		 * this key is not sent over the wire.
		 */
		अगर (!म_भेद(param->name, MAXXMITDATASEGMENTLENGTH)) अणु
			ops->MaxXmitDataSegmentLength =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("MaxXmitDataSegmentLength:     %s\n",
				param->value);
		पूर्ण

		अगर (!IS_PSTATE_ACCEPTOR(param) && !IS_PSTATE_PROPOSER(param))
			जारी;
		अगर (!म_भेद(param->name, AUTHMETHOD)) अणु
			pr_debug("AuthMethod:                   %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, HEADERDIGEST)) अणु
			ops->HeaderDigest = !म_भेद(param->value, CRC32C);
			pr_debug("HeaderDigest:                 %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DATADIGEST)) अणु
			ops->DataDigest = !म_भेद(param->value, CRC32C);
			pr_debug("DataDigest:                   %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXRECVDATASEGMENTLENGTH)) अणु
			/*
			 * At this poपूर्णांक iscsi_check_acceptor_state() will have
			 * set ops->MaxRecvDataSegmentLength from the original
			 * initiator provided value.
			 */
			pr_debug("MaxRecvDataSegmentLength:     %u\n",
				ops->MaxRecvDataSegmentLength);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, INITIATORRECVDATASEGMENTLENGTH)) अणु
			ops->InitiatorRecvDataSegmentLength =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("InitiatorRecvDataSegmentLength: %s\n",
				param->value);
			ops->MaxRecvDataSegmentLength =
					ops->InitiatorRecvDataSegmentLength;
			pr_debug("Set MRDSL from InitiatorRecvDataSegmentLength\n");
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETRECVDATASEGMENTLENGTH)) अणु
			ops->TargetRecvDataSegmentLength =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("TargetRecvDataSegmentLength:  %s\n",
				param->value);
			ops->MaxXmitDataSegmentLength =
					ops->TargetRecvDataSegmentLength;
			pr_debug("Set MXDSL from TargetRecvDataSegmentLength\n");
		पूर्ण
	पूर्ण
	pr_debug("----------------------------------------------------"
			"--------------\n");
पूर्ण

व्योम iscsi_set_session_parameters(
	काष्ठा iscsi_sess_ops *ops,
	काष्ठा iscsi_param_list *param_list,
	पूर्णांक leading)
अणु
	अक्षर *पंचांगpptr;
	काष्ठा iscsi_param *param;

	pr_debug("----------------------------------------------------"
			"--------------\n");
	list_क्रम_each_entry(param, &param_list->param_list, p_list) अणु
		अगर (!IS_PSTATE_ACCEPTOR(param) && !IS_PSTATE_PROPOSER(param))
			जारी;
		अगर (!म_भेद(param->name, INITIATORNAME)) अणु
			अगर (!param->value)
				जारी;
			अगर (leading)
				snम_लिखो(ops->InitiatorName,
						माप(ops->InitiatorName),
						"%s", param->value);
			pr_debug("InitiatorName:                %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, INITIATORALIAS)) अणु
			अगर (!param->value)
				जारी;
			snम_लिखो(ops->InitiatorAlias,
						माप(ops->InitiatorAlias),
						"%s", param->value);
			pr_debug("InitiatorAlias:               %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETNAME)) अणु
			अगर (!param->value)
				जारी;
			अगर (leading)
				snम_लिखो(ops->TargetName,
						माप(ops->TargetName),
						"%s", param->value);
			pr_debug("TargetName:                   %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETALIAS)) अणु
			अगर (!param->value)
				जारी;
			snम_लिखो(ops->TargetAlias, माप(ops->TargetAlias),
					"%s", param->value);
			pr_debug("TargetAlias:                  %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, TARGETPORTALGROUPTAG)) अणु
			ops->TargetPortalGroupTag =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("TargetPortalGroupTag:         %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXCONNECTIONS)) अणु
			ops->MaxConnections =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("MaxConnections:               %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, INITIALR2T)) अणु
			ops->InitialR2T = !म_भेद(param->value, YES);
			pr_debug("InitialR2T:                   %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, IMMEDIATEDATA)) अणु
			ops->ImmediateData = !म_भेद(param->value, YES);
			pr_debug("ImmediateData:                %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXBURSTLENGTH)) अणु
			ops->MaxBurstLength =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("MaxBurstLength:               %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, FIRSTBURSTLENGTH)) अणु
			ops->FirstBurstLength =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("FirstBurstLength:             %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DEFAULTTIME2WAIT)) अणु
			ops->DefaultTime2Wait =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("DefaultTime2Wait:             %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DEFAULTTIME2RETAIN)) अणु
			ops->DefaultTime2Retain =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("DefaultTime2Retain:           %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, MAXOUTSTANDINGR2T)) अणु
			ops->MaxOutstandingR2T =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("MaxOutstandingR2T:            %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DATAPDUINORDER)) अणु
			ops->DataPDUInOrder = !म_भेद(param->value, YES);
			pr_debug("DataPDUInOrder:               %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, DATASEQUENCEINORDER)) अणु
			ops->DataSequenceInOrder = !म_भेद(param->value, YES);
			pr_debug("DataSequenceInOrder:          %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, ERRORRECOVERYLEVEL)) अणु
			ops->ErrorRecoveryLevel =
				simple_म_से_अदीर्घ(param->value, &पंचांगpptr, 0);
			pr_debug("ErrorRecoveryLevel:           %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, SESSIONTYPE)) अणु
			ops->SessionType = !म_भेद(param->value, DISCOVERY);
			pr_debug("SessionType:                  %s\n",
				param->value);
		पूर्ण अन्यथा अगर (!म_भेद(param->name, RDMAEXTENSIONS)) अणु
			ops->RDMAExtensions = !म_भेद(param->value, YES);
			pr_debug("RDMAExtensions:               %s\n",
				param->value);
		पूर्ण
	पूर्ण
	pr_debug("----------------------------------------------------"
			"--------------\n");

पूर्ण
