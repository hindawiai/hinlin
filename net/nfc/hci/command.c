<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "hci: %s: " fmt, __func__

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>

#समावेश <net/nfc/hci.h>

#समावेश "hci.h"

#घोषणा MAX_FWI 4949

अटल पूर्णांक nfc_hci_execute_cmd_async(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			       स्थिर u8 *param, माप_प्रकार param_len,
			       data_exchange_cb_t cb, व्योम *cb_context)
अणु
	pr_debug("exec cmd async through pipe=%d, cmd=%d, plen=%zd\n", pipe,
		 cmd, param_len);

	/* TODO: Define hci cmd execution delay. Should it be the same
	 * क्रम all commands?
	 */
	वापस nfc_hci_hcp_message_tx(hdev, pipe, NFC_HCI_HCP_COMMAND, cmd,
				      param, param_len, cb, cb_context, MAX_FWI);
पूर्ण

/*
 * HCI command execution completion callback.
 * err will be a standard linux error (may be converted from HCI response)
 * skb contains the response data and must be disposed, or may be शून्य अगर
 * an error occured
 */
अटल व्योम nfc_hci_execute_cb(व्योम *context, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा hcp_exec_रुकोer *hcp_ew = (काष्ठा hcp_exec_रुकोer *)context;

	pr_debug("HCI Cmd completed with result=%d\n", err);

	hcp_ew->exec_result = err;
	अगर (hcp_ew->exec_result == 0)
		hcp_ew->result_skb = skb;
	अन्यथा
		kमुक्त_skb(skb);
	hcp_ew->exec_complete = true;

	wake_up(hcp_ew->wq);
पूर्ण

अटल पूर्णांक nfc_hci_execute_cmd(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			       स्थिर u8 *param, माप_प्रकार param_len,
			       काष्ठा sk_buff **skb)
अणु
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(ew_wq);
	काष्ठा hcp_exec_रुकोer hcp_ew;
	hcp_ew.wq = &ew_wq;
	hcp_ew.exec_complete = false;
	hcp_ew.result_skb = शून्य;

	pr_debug("exec cmd sync through pipe=%d, cmd=%d, plen=%zd\n", pipe,
		 cmd, param_len);

	/* TODO: Define hci cmd execution delay. Should it be the same
	 * क्रम all commands?
	 */
	hcp_ew.exec_result = nfc_hci_hcp_message_tx(hdev, pipe,
						    NFC_HCI_HCP_COMMAND, cmd,
						    param, param_len,
						    nfc_hci_execute_cb, &hcp_ew,
						    MAX_FWI);
	अगर (hcp_ew.exec_result < 0)
		वापस hcp_ew.exec_result;

	रुको_event(ew_wq, hcp_ew.exec_complete == true);

	अगर (hcp_ew.exec_result == 0) अणु
		अगर (skb)
			*skb = hcp_ew.result_skb;
		अन्यथा
			kमुक्त_skb(hcp_ew.result_skb);
	पूर्ण

	वापस hcp_ew.exec_result;
पूर्ण

पूर्णांक nfc_hci_send_event(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 event,
		       स्थिर u8 *param, माप_प्रकार param_len)
अणु
	u8 pipe;

	pr_debug("%d to gate %d\n", event, gate);

	pipe = hdev->gate2pipe[gate];
	अगर (pipe == NFC_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	वापस nfc_hci_hcp_message_tx(hdev, pipe, NFC_HCI_HCP_EVENT, event,
				      param, param_len, शून्य, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(nfc_hci_send_event);

/*
 * Execute an hci command sent to gate.
 * skb will contain response data अगर success. skb can be शून्य अगर you are not
 * पूर्णांकerested by the response.
 */
पूर्णांक nfc_hci_send_cmd(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 cmd,
		     स्थिर u8 *param, माप_प्रकार param_len, काष्ठा sk_buff **skb)
अणु
	u8 pipe;

	pr_debug("\n");

	pipe = hdev->gate2pipe[gate];
	अगर (pipe == NFC_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	वापस nfc_hci_execute_cmd(hdev, pipe, cmd, param, param_len, skb);
पूर्ण
EXPORT_SYMBOL(nfc_hci_send_cmd);

पूर्णांक nfc_hci_send_cmd_async(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 cmd,
			   स्थिर u8 *param, माप_प्रकार param_len,
			   data_exchange_cb_t cb, व्योम *cb_context)
अणु
	u8 pipe;

	pr_debug("\n");

	pipe = hdev->gate2pipe[gate];
	अगर (pipe == NFC_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	वापस nfc_hci_execute_cmd_async(hdev, pipe, cmd, param, param_len,
					 cb, cb_context);
पूर्ण
EXPORT_SYMBOL(nfc_hci_send_cmd_async);

पूर्णांक nfc_hci_set_param(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 idx,
		      स्थिर u8 *param, माप_प्रकार param_len)
अणु
	पूर्णांक r;
	u8 *पंचांगp;

	/* TODO ELa: reg idx must be inserted beक्रमe param, but we करोn't want
	 * to ask the caller to करो it to keep a simpler API.
	 * For now, just create a new temporary param buffer. This is far from
	 * optimal though, and the plan is to modअगरy APIs to pass idx करोwn to
	 * nfc_hci_hcp_message_tx where the frame is actually built, thereby
	 * eliminating the need क्रम the temp allocation-copy here.
	 */

	pr_debug("idx=%d to gate %d\n", idx, gate);

	पंचांगp = kदो_स्मृति(1 + param_len, GFP_KERNEL);
	अगर (पंचांगp == शून्य)
		वापस -ENOMEM;

	*पंचांगp = idx;
	स_नकल(पंचांगp + 1, param, param_len);

	r = nfc_hci_send_cmd(hdev, gate, NFC_HCI_ANY_SET_PARAMETER,
			     पंचांगp, param_len + 1, शून्य);

	kमुक्त(पंचांगp);

	वापस r;
पूर्ण
EXPORT_SYMBOL(nfc_hci_set_param);

पूर्णांक nfc_hci_get_param(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 idx,
		      काष्ठा sk_buff **skb)
अणु
	pr_debug("gate=%d regidx=%d\n", gate, idx);

	वापस nfc_hci_send_cmd(hdev, gate, NFC_HCI_ANY_GET_PARAMETER,
				&idx, 1, skb);
पूर्ण
EXPORT_SYMBOL(nfc_hci_get_param);

अटल पूर्णांक nfc_hci_खोलो_pipe(काष्ठा nfc_hci_dev *hdev, u8 pipe)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक r;

	pr_debug("pipe=%d\n", pipe);

	r = nfc_hci_execute_cmd(hdev, pipe, NFC_HCI_ANY_OPEN_PIPE,
				शून्य, 0, &skb);
	अगर (r == 0) अणु
		/* dest host other than host controller will send
		 * number of pipes alपढ़ोy खोलो on this gate beक्रमe
		 * execution. The number can be found in skb->data[0]
		 */
		kमुक्त_skb(skb);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक nfc_hci_बंद_pipe(काष्ठा nfc_hci_dev *hdev, u8 pipe)
अणु
	pr_debug("\n");

	वापस nfc_hci_execute_cmd(hdev, pipe, NFC_HCI_ANY_CLOSE_PIPE,
				   शून्य, 0, शून्य);
पूर्ण

अटल u8 nfc_hci_create_pipe(काष्ठा nfc_hci_dev *hdev, u8 dest_host,
			      u8 dest_gate, पूर्णांक *result)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hci_create_pipe_params params;
	काष्ठा hci_create_pipe_resp *resp;
	u8 pipe;

	pr_debug("gate=%d\n", dest_gate);

	params.src_gate = NFC_HCI_ADMIN_GATE;
	params.dest_host = dest_host;
	params.dest_gate = dest_gate;

	*result = nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				      NFC_HCI_ADM_CREATE_PIPE,
				      (u8 *) &params, माप(params), &skb);
	अगर (*result < 0)
		वापस NFC_HCI_INVALID_PIPE;

	resp = (काष्ठा hci_create_pipe_resp *)skb->data;
	pipe = resp->pipe;
	kमुक्त_skb(skb);

	pr_debug("pipe created=%d\n", pipe);

	वापस pipe;
पूर्ण

अटल पूर्णांक nfc_hci_delete_pipe(काष्ठा nfc_hci_dev *hdev, u8 pipe)
अणु
	pr_debug("\n");

	वापस nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				   NFC_HCI_ADM_DELETE_PIPE, &pipe, 1, शून्य);
पूर्ण

अटल पूर्णांक nfc_hci_clear_all_pipes(काष्ठा nfc_hci_dev *hdev)
अणु
	u8 param[2];
	माप_प्रकार param_len = 2;

	/* TODO: Find out what the identity reference data is
	 * and fill param with it. HCI spec 6.1.3.5 */

	pr_debug("\n");

	अगर (test_bit(NFC_HCI_QUIRK_SHORT_CLEAR, &hdev->quirks))
		param_len = 0;

	वापस nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				   NFC_HCI_ADM_CLEAR_ALL_PIPE, param, param_len,
				   शून्य);
पूर्ण

पूर्णांक nfc_hci_disconnect_gate(काष्ठा nfc_hci_dev *hdev, u8 gate)
अणु
	पूर्णांक r;
	u8 pipe = hdev->gate2pipe[gate];

	pr_debug("\n");

	अगर (pipe == NFC_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	r = nfc_hci_बंद_pipe(hdev, pipe);
	अगर (r < 0)
		वापस r;

	अगर (pipe != NFC_HCI_LINK_MGMT_PIPE && pipe != NFC_HCI_ADMIN_PIPE) अणु
		r = nfc_hci_delete_pipe(hdev, pipe);
		अगर (r < 0)
			वापस r;
	पूर्ण

	hdev->gate2pipe[gate] = NFC_HCI_INVALID_PIPE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nfc_hci_disconnect_gate);

पूर्णांक nfc_hci_disconnect_all_gates(काष्ठा nfc_hci_dev *hdev)
अणु
	पूर्णांक r;

	pr_debug("\n");

	r = nfc_hci_clear_all_pipes(hdev);
	अगर (r < 0)
		वापस r;

	nfc_hci_reset_pipes(hdev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nfc_hci_disconnect_all_gates);

पूर्णांक nfc_hci_connect_gate(काष्ठा nfc_hci_dev *hdev, u8 dest_host, u8 dest_gate,
			 u8 pipe)
अणु
	bool pipe_created = false;
	पूर्णांक r;

	pr_debug("\n");

	अगर (pipe == NFC_HCI_DO_NOT_CREATE_PIPE)
		वापस 0;

	अगर (hdev->gate2pipe[dest_gate] != NFC_HCI_INVALID_PIPE)
		वापस -EADDRINUSE;

	अगर (pipe != NFC_HCI_INVALID_PIPE)
		जाओ खोलो_pipe;

	चयन (dest_gate) अणु
	हाल NFC_HCI_LINK_MGMT_GATE:
		pipe = NFC_HCI_LINK_MGMT_PIPE;
		अवरोध;
	हाल NFC_HCI_ADMIN_GATE:
		pipe = NFC_HCI_ADMIN_PIPE;
		अवरोध;
	शेष:
		pipe = nfc_hci_create_pipe(hdev, dest_host, dest_gate, &r);
		अगर (pipe == NFC_HCI_INVALID_PIPE)
			वापस r;
		pipe_created = true;
		अवरोध;
	पूर्ण

खोलो_pipe:
	r = nfc_hci_खोलो_pipe(hdev, pipe);
	अगर (r < 0) अणु
		अगर (pipe_created)
			अगर (nfc_hci_delete_pipe(hdev, pipe) < 0) अणु
				/* TODO: Cannot clean by deleting pipe...
				 * -> inconsistent state */
			पूर्ण
		वापस r;
	पूर्ण

	hdev->pipes[pipe].gate = dest_gate;
	hdev->pipes[pipe].dest_host = dest_host;
	hdev->gate2pipe[dest_gate] = pipe;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nfc_hci_connect_gate);
