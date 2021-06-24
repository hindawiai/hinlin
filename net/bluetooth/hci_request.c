<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux

   Copyright (C) 2014 Intel Corporation

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <linux/sched/संकेत.स>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/mgmt.h>

#समावेश "smp.h"
#समावेश "hci_request.h"
#समावेश "msft.h"

#घोषणा HCI_REQ_DONE	  0
#घोषणा HCI_REQ_PEND	  1
#घोषणा HCI_REQ_CANCELED  2

व्योम hci_req_init(काष्ठा hci_request *req, काष्ठा hci_dev *hdev)
अणु
	skb_queue_head_init(&req->cmd_q);
	req->hdev = hdev;
	req->err = 0;
पूर्ण

व्योम hci_req_purge(काष्ठा hci_request *req)
अणु
	skb_queue_purge(&req->cmd_q);
पूर्ण

bool hci_req_status_pend(काष्ठा hci_dev *hdev)
अणु
	वापस hdev->req_status == HCI_REQ_PEND;
पूर्ण

अटल पूर्णांक req_run(काष्ठा hci_request *req, hci_req_complete_t complete,
		   hci_req_complete_skb_t complete_skb)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;

	bt_dev_dbg(hdev, "length %u", skb_queue_len(&req->cmd_q));

	/* If an error occurred during request building, हटाओ all HCI
	 * commands queued on the HCI request queue.
	 */
	अगर (req->err) अणु
		skb_queue_purge(&req->cmd_q);
		वापस req->err;
	पूर्ण

	/* Do not allow empty requests */
	अगर (skb_queue_empty(&req->cmd_q))
		वापस -ENODATA;

	skb = skb_peek_tail(&req->cmd_q);
	अगर (complete) अणु
		bt_cb(skb)->hci.req_complete = complete;
	पूर्ण अन्यथा अगर (complete_skb) अणु
		bt_cb(skb)->hci.req_complete_skb = complete_skb;
		bt_cb(skb)->hci.req_flags |= HCI_REQ_SKB;
	पूर्ण

	spin_lock_irqsave(&hdev->cmd_q.lock, flags);
	skb_queue_splice_tail(&req->cmd_q, &hdev->cmd_q);
	spin_unlock_irqrestore(&hdev->cmd_q.lock, flags);

	queue_work(hdev->workqueue, &hdev->cmd_work);

	वापस 0;
पूर्ण

पूर्णांक hci_req_run(काष्ठा hci_request *req, hci_req_complete_t complete)
अणु
	वापस req_run(req, complete, शून्य);
पूर्ण

पूर्णांक hci_req_run_skb(काष्ठा hci_request *req, hci_req_complete_skb_t complete)
अणु
	वापस req_run(req, शून्य, complete);
पूर्ण

अटल व्योम hci_req_sync_complete(काष्ठा hci_dev *hdev, u8 result, u16 opcode,
				  काष्ठा sk_buff *skb)
अणु
	bt_dev_dbg(hdev, "result 0x%2.2x", result);

	अगर (hdev->req_status == HCI_REQ_PEND) अणु
		hdev->req_result = result;
		hdev->req_status = HCI_REQ_DONE;
		अगर (skb)
			hdev->req_skb = skb_get(skb);
		wake_up_पूर्णांकerruptible(&hdev->req_रुको_q);
	पूर्ण
पूर्ण

व्योम hci_req_sync_cancel(काष्ठा hci_dev *hdev, पूर्णांक err)
अणु
	bt_dev_dbg(hdev, "err 0x%2.2x", err);

	अगर (hdev->req_status == HCI_REQ_PEND) अणु
		hdev->req_result = err;
		hdev->req_status = HCI_REQ_CANCELED;
		wake_up_पूर्णांकerruptible(&hdev->req_रुको_q);
	पूर्ण
पूर्ण

काष्ठा sk_buff *__hci_cmd_sync_ev(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
				  स्थिर व्योम *param, u8 event, u32 समयout)
अणु
	काष्ठा hci_request req;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	bt_dev_dbg(hdev, "");

	hci_req_init(&req, hdev);

	hci_req_add_ev(&req, opcode, plen, param, event);

	hdev->req_status = HCI_REQ_PEND;

	err = hci_req_run_skb(&req, hci_req_sync_complete);
	अगर (err < 0)
		वापस ERR_PTR(err);

	err = रुको_event_पूर्णांकerruptible_समयout(hdev->req_रुको_q,
			hdev->req_status != HCI_REQ_PEND, समयout);

	अगर (err == -ERESTARTSYS)
		वापस ERR_PTR(-EINTR);

	चयन (hdev->req_status) अणु
	हाल HCI_REQ_DONE:
		err = -bt_to_त्रुटि_सं(hdev->req_result);
		अवरोध;

	हाल HCI_REQ_CANCELED:
		err = -hdev->req_result;
		अवरोध;

	शेष:
		err = -ETIMEDOUT;
		अवरोध;
	पूर्ण

	hdev->req_status = hdev->req_result = 0;
	skb = hdev->req_skb;
	hdev->req_skb = शून्य;

	bt_dev_dbg(hdev, "end: err %d", err);

	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(err);
	पूर्ण

	अगर (!skb)
		वापस ERR_PTR(-ENODATA);

	वापस skb;
पूर्ण
EXPORT_SYMBOL(__hci_cmd_sync_ev);

काष्ठा sk_buff *__hci_cmd_sync(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
			       स्थिर व्योम *param, u32 समयout)
अणु
	वापस __hci_cmd_sync_ev(hdev, opcode, plen, param, 0, समयout);
पूर्ण
EXPORT_SYMBOL(__hci_cmd_sync);

/* Execute request and रुको क्रम completion. */
पूर्णांक __hci_req_sync(काष्ठा hci_dev *hdev, पूर्णांक (*func)(काष्ठा hci_request *req,
						     अचिन्हित दीर्घ opt),
		   अचिन्हित दीर्घ opt, u32 समयout, u8 *hci_status)
अणु
	काष्ठा hci_request req;
	पूर्णांक err = 0;

	bt_dev_dbg(hdev, "start");

	hci_req_init(&req, hdev);

	hdev->req_status = HCI_REQ_PEND;

	err = func(&req, opt);
	अगर (err) अणु
		अगर (hci_status)
			*hci_status = HCI_ERROR_UNSPECIFIED;
		वापस err;
	पूर्ण

	err = hci_req_run_skb(&req, hci_req_sync_complete);
	अगर (err < 0) अणु
		hdev->req_status = 0;

		/* ENODATA means the HCI request command queue is empty.
		 * This can happen when a request with conditionals करोesn't
		 * trigger any commands to be sent. This is normal behavior
		 * and should not trigger an error वापस.
		 */
		अगर (err == -ENODATA) अणु
			अगर (hci_status)
				*hci_status = 0;
			वापस 0;
		पूर्ण

		अगर (hci_status)
			*hci_status = HCI_ERROR_UNSPECIFIED;

		वापस err;
	पूर्ण

	err = रुको_event_पूर्णांकerruptible_समयout(hdev->req_रुको_q,
			hdev->req_status != HCI_REQ_PEND, समयout);

	अगर (err == -ERESTARTSYS)
		वापस -EINTR;

	चयन (hdev->req_status) अणु
	हाल HCI_REQ_DONE:
		err = -bt_to_त्रुटि_सं(hdev->req_result);
		अगर (hci_status)
			*hci_status = hdev->req_result;
		अवरोध;

	हाल HCI_REQ_CANCELED:
		err = -hdev->req_result;
		अगर (hci_status)
			*hci_status = HCI_ERROR_UNSPECIFIED;
		अवरोध;

	शेष:
		err = -ETIMEDOUT;
		अगर (hci_status)
			*hci_status = HCI_ERROR_UNSPECIFIED;
		अवरोध;
	पूर्ण

	kमुक्त_skb(hdev->req_skb);
	hdev->req_skb = शून्य;
	hdev->req_status = hdev->req_result = 0;

	bt_dev_dbg(hdev, "end: err %d", err);

	वापस err;
पूर्ण

पूर्णांक hci_req_sync(काष्ठा hci_dev *hdev, पूर्णांक (*req)(काष्ठा hci_request *req,
						  अचिन्हित दीर्घ opt),
		 अचिन्हित दीर्घ opt, u32 समयout, u8 *hci_status)
अणु
	पूर्णांक ret;

	/* Serialize all requests */
	hci_req_sync_lock(hdev);
	/* check the state after obtaing the lock to protect the HCI_UP
	 * against any races from hci_dev_करो_बंद when the controller
	 * माला_लो हटाओd.
	 */
	अगर (test_bit(HCI_UP, &hdev->flags))
		ret = __hci_req_sync(hdev, req, opt, समयout, hci_status);
	अन्यथा
		ret = -ENETDOWN;
	hci_req_sync_unlock(hdev);

	वापस ret;
पूर्ण

काष्ठा sk_buff *hci_prepare_cmd(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
				स्थिर व्योम *param)
अणु
	पूर्णांक len = HCI_COMMAND_HDR_SIZE + plen;
	काष्ठा hci_command_hdr *hdr;
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(len, GFP_ATOMIC);
	अगर (!skb)
		वापस शून्य;

	hdr = skb_put(skb, HCI_COMMAND_HDR_SIZE);
	hdr->opcode = cpu_to_le16(opcode);
	hdr->plen   = plen;

	अगर (plen)
		skb_put_data(skb, param, plen);

	bt_dev_dbg(hdev, "skb len %d", skb->len);

	hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;
	hci_skb_opcode(skb) = opcode;

	वापस skb;
पूर्ण

/* Queue a command to an asynchronous HCI request */
व्योम hci_req_add_ev(काष्ठा hci_request *req, u16 opcode, u32 plen,
		    स्थिर व्योम *param, u8 event)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा sk_buff *skb;

	bt_dev_dbg(hdev, "opcode 0x%4.4x plen %d", opcode, plen);

	/* If an error occurred during request building, there is no poपूर्णांक in
	 * queueing the HCI command. We can simply वापस.
	 */
	अगर (req->err)
		वापस;

	skb = hci_prepare_cmd(hdev, opcode, plen, param);
	अगर (!skb) अणु
		bt_dev_err(hdev, "no memory for command (opcode 0x%4.4x)",
			   opcode);
		req->err = -ENOMEM;
		वापस;
	पूर्ण

	अगर (skb_queue_empty(&req->cmd_q))
		bt_cb(skb)->hci.req_flags |= HCI_REQ_START;

	bt_cb(skb)->hci.req_event = event;

	skb_queue_tail(&req->cmd_q, skb);
पूर्ण

व्योम hci_req_add(काष्ठा hci_request *req, u16 opcode, u32 plen,
		 स्थिर व्योम *param)
अणु
	hci_req_add_ev(req, opcode, plen, param, 0);
पूर्ण

व्योम __hci_req_ग_लिखो_fast_connectable(काष्ठा hci_request *req, bool enable)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_ग_लिखो_page_scan_activity acp;
	u8 type;

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		वापस;

	अगर (hdev->hci_ver < BLUETOOTH_VER_1_2)
		वापस;

	अगर (enable) अणु
		type = PAGE_SCAN_TYPE_INTERLACED;

		/* 160 msec page scan पूर्णांकerval */
		acp.पूर्णांकerval = cpu_to_le16(0x0100);
	पूर्ण अन्यथा अणु
		type = hdev->def_page_scan_type;
		acp.पूर्णांकerval = cpu_to_le16(hdev->def_page_scan_पूर्णांक);
	पूर्ण

	acp.winकरोw = cpu_to_le16(hdev->def_page_scan_winकरोw);

	अगर (__cpu_to_le16(hdev->page_scan_पूर्णांकerval) != acp.पूर्णांकerval ||
	    __cpu_to_le16(hdev->page_scan_winकरोw) != acp.winकरोw)
		hci_req_add(req, HCI_OP_WRITE_PAGE_SCAN_ACTIVITY,
			    माप(acp), &acp);

	अगर (hdev->page_scan_type != type)
		hci_req_add(req, HCI_OP_WRITE_PAGE_SCAN_TYPE, 1, &type);
पूर्ण

अटल व्योम start_पूर्णांकerleave_scan(काष्ठा hci_dev *hdev)
अणु
	hdev->पूर्णांकerleave_scan_state = INTERLEAVE_SCAN_NO_FILTER;
	queue_delayed_work(hdev->req_workqueue,
			   &hdev->पूर्णांकerleave_scan, 0);
पूर्ण

अटल bool is_पूर्णांकerleave_scanning(काष्ठा hci_dev *hdev)
अणु
	वापस hdev->पूर्णांकerleave_scan_state != INTERLEAVE_SCAN_NONE;
पूर्ण

अटल व्योम cancel_पूर्णांकerleave_scan(काष्ठा hci_dev *hdev)
अणु
	bt_dev_dbg(hdev, "cancelling interleave scan");

	cancel_delayed_work_sync(&hdev->पूर्णांकerleave_scan);

	hdev->पूर्णांकerleave_scan_state = INTERLEAVE_SCAN_NONE;
पूर्ण

/* Return true अगर पूर्णांकerleave_scan wasn't started until निकासing this function,
 * otherwise, वापस false
 */
अटल bool __hci_update_पूर्णांकerleaved_scan(काष्ठा hci_dev *hdev)
अणु
	/* Do पूर्णांकerleaved scan only अगर all of the following are true:
	 * - There is at least one ADV monitor
	 * - At least one pending LE connection or one device to be scanned क्रम
	 * - Monitor offloading is not supported
	 * If so, we should alternate between allowlist scan and one without
	 * any filters to save घातer.
	 */
	bool use_पूर्णांकerleaving = hci_is_adv_monitoring(hdev) &&
				!(list_empty(&hdev->pend_le_conns) &&
				  list_empty(&hdev->pend_le_reports)) &&
				hci_get_adv_monitor_offload_ext(hdev) ==
				    HCI_ADV_MONITOR_EXT_NONE;
	bool is_पूर्णांकerleaving = is_पूर्णांकerleave_scanning(hdev);

	अगर (use_पूर्णांकerleaving && !is_पूर्णांकerleaving) अणु
		start_पूर्णांकerleave_scan(hdev);
		bt_dev_dbg(hdev, "starting interleave scan");
		वापस true;
	पूर्ण

	अगर (!use_पूर्णांकerleaving && is_पूर्णांकerleaving)
		cancel_पूर्णांकerleave_scan(hdev);

	वापस false;
पूर्ण

/* This function controls the background scanning based on hdev->pend_le_conns
 * list. If there are pending LE connection we start the background scanning,
 * otherwise we stop it.
 *
 * This function requires the caller holds hdev->lock.
 */
अटल व्योम __hci_update_background_scan(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	अगर (!test_bit(HCI_UP, &hdev->flags) ||
	    test_bit(HCI_INIT, &hdev->flags) ||
	    hci_dev_test_flag(hdev, HCI_SETUP) ||
	    hci_dev_test_flag(hdev, HCI_CONFIG) ||
	    hci_dev_test_flag(hdev, HCI_AUTO_OFF) ||
	    hci_dev_test_flag(hdev, HCI_UNREGISTER))
		वापस;

	/* No poपूर्णांक in करोing scanning अगर LE support hasn't been enabled */
	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		वापस;

	/* If discovery is active करोn't पूर्णांकerfere with it */
	अगर (hdev->discovery.state != DISCOVERY_STOPPED)
		वापस;

	/* Reset RSSI and UUID filters when starting background scanning
	 * since these filters are meant क्रम service discovery only.
	 *
	 * The Start Discovery and Start Service Discovery operations
	 * ensure to set proper values क्रम RSSI threshold and UUID
	 * filter list. So it is safe to just reset them here.
	 */
	hci_discovery_filter_clear(hdev);

	bt_dev_dbg(hdev, "ADV monitoring is %s",
		   hci_is_adv_monitoring(hdev) ? "on" : "off");

	अगर (list_empty(&hdev->pend_le_conns) &&
	    list_empty(&hdev->pend_le_reports) &&
	    !hci_is_adv_monitoring(hdev)) अणु
		/* If there is no pending LE connections or devices
		 * to be scanned क्रम or no ADV monitors, we should stop the
		 * background scanning.
		 */

		/* If controller is not scanning we are करोne. */
		अगर (!hci_dev_test_flag(hdev, HCI_LE_SCAN))
			वापस;

		hci_req_add_le_scan_disable(req, false);

		bt_dev_dbg(hdev, "stopping background scanning");
	पूर्ण अन्यथा अणु
		/* If there is at least one pending LE connection, we should
		 * keep the background scan running.
		 */

		/* If controller is connecting, we should not start scanning
		 * since some controllers are not able to scan and connect at
		 * the same समय.
		 */
		अगर (hci_lookup_le_connect(hdev))
			वापस;

		/* If controller is currently scanning, we stop it to ensure we
		 * करोn't miss any advertising (due to duplicates filter).
		 */
		अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN))
			hci_req_add_le_scan_disable(req, false);

		hci_req_add_le_passive_scan(req);
		bt_dev_dbg(hdev, "starting background scanning");
	पूर्ण
पूर्ण

व्योम __hci_req_update_name(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_ग_लिखो_local_name cp;

	स_नकल(cp.name, hdev->dev_name, माप(cp.name));

	hci_req_add(req, HCI_OP_WRITE_LOCAL_NAME, माप(cp), &cp);
पूर्ण

#घोषणा PNP_INFO_SVCLASS_ID		0x1200

अटल u8 *create_uuid16_list(काष्ठा hci_dev *hdev, u8 *data, सूचक_भेद_प्रकार len)
अणु
	u8 *ptr = data, *uuids_start = शून्य;
	काष्ठा bt_uuid *uuid;

	अगर (len < 4)
		वापस ptr;

	list_क्रम_each_entry(uuid, &hdev->uuids, list) अणु
		u16 uuid16;

		अगर (uuid->size != 16)
			जारी;

		uuid16 = get_unaligned_le16(&uuid->uuid[12]);
		अगर (uuid16 < 0x1100)
			जारी;

		अगर (uuid16 == PNP_INFO_SVCLASS_ID)
			जारी;

		अगर (!uuids_start) अणु
			uuids_start = ptr;
			uuids_start[0] = 1;
			uuids_start[1] = EIR_UUID16_ALL;
			ptr += 2;
		पूर्ण

		/* Stop अगर not enough space to put next UUID */
		अगर ((ptr - data) + माप(u16) > len) अणु
			uuids_start[1] = EIR_UUID16_SOME;
			अवरोध;
		पूर्ण

		*ptr++ = (uuid16 & 0x00ff);
		*ptr++ = (uuid16 & 0xff00) >> 8;
		uuids_start[0] += माप(uuid16);
	पूर्ण

	वापस ptr;
पूर्ण

अटल u8 *create_uuid32_list(काष्ठा hci_dev *hdev, u8 *data, सूचक_भेद_प्रकार len)
अणु
	u8 *ptr = data, *uuids_start = शून्य;
	काष्ठा bt_uuid *uuid;

	अगर (len < 6)
		वापस ptr;

	list_क्रम_each_entry(uuid, &hdev->uuids, list) अणु
		अगर (uuid->size != 32)
			जारी;

		अगर (!uuids_start) अणु
			uuids_start = ptr;
			uuids_start[0] = 1;
			uuids_start[1] = EIR_UUID32_ALL;
			ptr += 2;
		पूर्ण

		/* Stop अगर not enough space to put next UUID */
		अगर ((ptr - data) + माप(u32) > len) अणु
			uuids_start[1] = EIR_UUID32_SOME;
			अवरोध;
		पूर्ण

		स_नकल(ptr, &uuid->uuid[12], माप(u32));
		ptr += माप(u32);
		uuids_start[0] += माप(u32);
	पूर्ण

	वापस ptr;
पूर्ण

अटल u8 *create_uuid128_list(काष्ठा hci_dev *hdev, u8 *data, सूचक_भेद_प्रकार len)
अणु
	u8 *ptr = data, *uuids_start = शून्य;
	काष्ठा bt_uuid *uuid;

	अगर (len < 18)
		वापस ptr;

	list_क्रम_each_entry(uuid, &hdev->uuids, list) अणु
		अगर (uuid->size != 128)
			जारी;

		अगर (!uuids_start) अणु
			uuids_start = ptr;
			uuids_start[0] = 1;
			uuids_start[1] = EIR_UUID128_ALL;
			ptr += 2;
		पूर्ण

		/* Stop अगर not enough space to put next UUID */
		अगर ((ptr - data) + 16 > len) अणु
			uuids_start[1] = EIR_UUID128_SOME;
			अवरोध;
		पूर्ण

		स_नकल(ptr, uuid->uuid, 16);
		ptr += 16;
		uuids_start[0] += 16;
	पूर्ण

	वापस ptr;
पूर्ण

अटल व्योम create_eir(काष्ठा hci_dev *hdev, u8 *data)
अणु
	u8 *ptr = data;
	माप_प्रकार name_len;

	name_len = म_माप(hdev->dev_name);

	अगर (name_len > 0) अणु
		/* EIR Data type */
		अगर (name_len > 48) अणु
			name_len = 48;
			ptr[1] = EIR_NAME_SHORT;
		पूर्ण अन्यथा
			ptr[1] = EIR_NAME_COMPLETE;

		/* EIR Data length */
		ptr[0] = name_len + 1;

		स_नकल(ptr + 2, hdev->dev_name, name_len);

		ptr += (name_len + 2);
	पूर्ण

	अगर (hdev->inq_tx_घातer != HCI_TX_POWER_INVALID) अणु
		ptr[0] = 2;
		ptr[1] = EIR_TX_POWER;
		ptr[2] = (u8) hdev->inq_tx_घातer;

		ptr += 3;
	पूर्ण

	अगर (hdev->devid_source > 0) अणु
		ptr[0] = 9;
		ptr[1] = EIR_DEVICE_ID;

		put_unaligned_le16(hdev->devid_source, ptr + 2);
		put_unaligned_le16(hdev->devid_venकरोr, ptr + 4);
		put_unaligned_le16(hdev->devid_product, ptr + 6);
		put_unaligned_le16(hdev->devid_version, ptr + 8);

		ptr += 10;
	पूर्ण

	ptr = create_uuid16_list(hdev, ptr, HCI_MAX_EIR_LENGTH - (ptr - data));
	ptr = create_uuid32_list(hdev, ptr, HCI_MAX_EIR_LENGTH - (ptr - data));
	ptr = create_uuid128_list(hdev, ptr, HCI_MAX_EIR_LENGTH - (ptr - data));
पूर्ण

व्योम __hci_req_update_eir(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_ग_लिखो_eir cp;

	अगर (!hdev_is_घातered(hdev))
		वापस;

	अगर (!lmp_ext_inq_capable(hdev))
		वापस;

	अगर (!hci_dev_test_flag(hdev, HCI_SSP_ENABLED))
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_SERVICE_CACHE))
		वापस;

	स_रखो(&cp, 0, माप(cp));

	create_eir(hdev, cp.data);

	अगर (स_भेद(cp.data, hdev->eir, माप(cp.data)) == 0)
		वापस;

	स_नकल(hdev->eir, cp.data, माप(cp.data));

	hci_req_add(req, HCI_OP_WRITE_EIR, माप(cp), &cp);
पूर्ण

व्योम hci_req_add_le_scan_disable(काष्ठा hci_request *req, bool rpa_le_conn)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	अगर (hdev->scanning_छोड़ोd) अणु
		bt_dev_dbg(hdev, "Scanning is paused for suspend");
		वापस;
	पूर्ण

	अगर (hdev->suspended)
		set_bit(SUSPEND_SCAN_DISABLE, hdev->suspend_tasks);

	अगर (use_ext_scan(hdev)) अणु
		काष्ठा hci_cp_le_set_ext_scan_enable cp;

		स_रखो(&cp, 0, माप(cp));
		cp.enable = LE_SCAN_DISABLE;
		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_ENABLE, माप(cp),
			    &cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_le_set_scan_enable cp;

		स_रखो(&cp, 0, माप(cp));
		cp.enable = LE_SCAN_DISABLE;
		hci_req_add(req, HCI_OP_LE_SET_SCAN_ENABLE, माप(cp), &cp);
	पूर्ण

	/* Disable address resolution */
	अगर (use_ll_privacy(hdev) &&
	    hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY) &&
	    hci_dev_test_flag(hdev, HCI_LL_RPA_RESOLUTION) && !rpa_le_conn) अणु
		__u8 enable = 0x00;

		hci_req_add(req, HCI_OP_LE_SET_ADDR_RESOLV_ENABLE, 1, &enable);
	पूर्ण
पूर्ण

अटल व्योम del_from_white_list(काष्ठा hci_request *req, bdaddr_t *bdaddr,
				u8 bdaddr_type)
अणु
	काष्ठा hci_cp_le_del_from_white_list cp;

	cp.bdaddr_type = bdaddr_type;
	bacpy(&cp.bdaddr, bdaddr);

	bt_dev_dbg(req->hdev, "Remove %pMR (0x%x) from whitelist", &cp.bdaddr,
		   cp.bdaddr_type);
	hci_req_add(req, HCI_OP_LE_DEL_FROM_WHITE_LIST, माप(cp), &cp);

	अगर (use_ll_privacy(req->hdev) &&
	    hci_dev_test_flag(req->hdev, HCI_ENABLE_LL_PRIVACY)) अणु
		काष्ठा smp_irk *irk;

		irk = hci_find_irk_by_addr(req->hdev, bdaddr, bdaddr_type);
		अगर (irk) अणु
			काष्ठा hci_cp_le_del_from_resolv_list cp;

			cp.bdaddr_type = bdaddr_type;
			bacpy(&cp.bdaddr, bdaddr);

			hci_req_add(req, HCI_OP_LE_DEL_FROM_RESOLV_LIST,
				    माप(cp), &cp);
		पूर्ण
	पूर्ण
पूर्ण

/* Adds connection to white list अगर needed. On error, वापसs -1. */
अटल पूर्णांक add_to_white_list(काष्ठा hci_request *req,
			     काष्ठा hci_conn_params *params, u8 *num_entries,
			     bool allow_rpa)
अणु
	काष्ठा hci_cp_le_add_to_white_list cp;
	काष्ठा hci_dev *hdev = req->hdev;

	/* Alपढ़ोy in white list */
	अगर (hci_bdaddr_list_lookup(&hdev->le_white_list, &params->addr,
				   params->addr_type))
		वापस 0;

	/* Select filter policy to accept all advertising */
	अगर (*num_entries >= hdev->le_white_list_size)
		वापस -1;

	/* White list can not be used with RPAs */
	अगर (!allow_rpa &&
	    !hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY) &&
	    hci_find_irk_by_addr(hdev, &params->addr, params->addr_type)) अणु
		वापस -1;
	पूर्ण

	/* During suspend, only wakeable devices can be in whitelist */
	अगर (hdev->suspended && !hci_conn_test_flag(HCI_CONN_FLAG_REMOTE_WAKEUP,
						   params->current_flags))
		वापस 0;

	*num_entries += 1;
	cp.bdaddr_type = params->addr_type;
	bacpy(&cp.bdaddr, &params->addr);

	bt_dev_dbg(hdev, "Add %pMR (0x%x) to whitelist", &cp.bdaddr,
		   cp.bdaddr_type);
	hci_req_add(req, HCI_OP_LE_ADD_TO_WHITE_LIST, माप(cp), &cp);

	अगर (use_ll_privacy(hdev) &&
	    hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY)) अणु
		काष्ठा smp_irk *irk;

		irk = hci_find_irk_by_addr(hdev, &params->addr,
					   params->addr_type);
		अगर (irk) अणु
			काष्ठा hci_cp_le_add_to_resolv_list cp;

			cp.bdaddr_type = params->addr_type;
			bacpy(&cp.bdaddr, &params->addr);
			स_नकल(cp.peer_irk, irk->val, 16);

			अगर (hci_dev_test_flag(hdev, HCI_PRIVACY))
				स_नकल(cp.local_irk, hdev->irk, 16);
			अन्यथा
				स_रखो(cp.local_irk, 0, 16);

			hci_req_add(req, HCI_OP_LE_ADD_TO_RESOLV_LIST,
				    माप(cp), &cp);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 update_white_list(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_conn_params *params;
	काष्ठा bdaddr_list *b;
	u8 num_entries = 0;
	bool pend_conn, pend_report;
	/* We allow whitelisting even with RPAs in suspend. In the worst हाल,
	 * we won't be able to wake from devices that use the privacy1.2
	 * features. Additionally, once we support privacy1.2 and IRK
	 * offloading, we can update this to also check क्रम those conditions.
	 */
	bool allow_rpa = hdev->suspended;

	अगर (use_ll_privacy(hdev) &&
	    hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
		allow_rpa = true;

	/* Go through the current white list programmed पूर्णांकo the
	 * controller one by one and check अगर that address is still
	 * in the list of pending connections or list of devices to
	 * report. If not present in either list, then queue the
	 * command to हटाओ it from the controller.
	 */
	list_क्रम_each_entry(b, &hdev->le_white_list, list) अणु
		pend_conn = hci_pend_le_action_lookup(&hdev->pend_le_conns,
						      &b->bdaddr,
						      b->bdaddr_type);
		pend_report = hci_pend_le_action_lookup(&hdev->pend_le_reports,
							&b->bdaddr,
							b->bdaddr_type);

		/* If the device is not likely to connect or report,
		 * हटाओ it from the whitelist.
		 */
		अगर (!pend_conn && !pend_report) अणु
			del_from_white_list(req, &b->bdaddr, b->bdaddr_type);
			जारी;
		पूर्ण

		/* White list can not be used with RPAs */
		अगर (!allow_rpa &&
		    !hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY) &&
		    hci_find_irk_by_addr(hdev, &b->bdaddr, b->bdaddr_type)) अणु
			वापस 0x00;
		पूर्ण

		num_entries++;
	पूर्ण

	/* Since all no दीर्घer valid white list entries have been
	 * हटाओd, walk through the list of pending connections
	 * and ensure that any new device माला_लो programmed पूर्णांकo
	 * the controller.
	 *
	 * If the list of the devices is larger than the list of
	 * available white list entries in the controller, then
	 * just पात and वापस filer policy value to not use the
	 * white list.
	 */
	list_क्रम_each_entry(params, &hdev->pend_le_conns, action) अणु
		अगर (add_to_white_list(req, params, &num_entries, allow_rpa))
			वापस 0x00;
	पूर्ण

	/* After adding all new pending connections, walk through
	 * the list of pending reports and also add these to the
	 * white list अगर there is still space. Abort अगर space runs out.
	 */
	list_क्रम_each_entry(params, &hdev->pend_le_reports, action) अणु
		अगर (add_to_white_list(req, params, &num_entries, allow_rpa))
			वापस 0x00;
	पूर्ण

	/* Use the allowlist unless the following conditions are all true:
	 * - We are not currently suspending
	 * - There are 1 or more ADV monitors रेजिस्टरed and it's not offloaded
	 * - Interleaved scanning is not currently using the allowlist
	 */
	अगर (!idr_is_empty(&hdev->adv_monitors_idr) && !hdev->suspended &&
	    hci_get_adv_monitor_offload_ext(hdev) == HCI_ADV_MONITOR_EXT_NONE &&
	    hdev->पूर्णांकerleave_scan_state != INTERLEAVE_SCAN_ALLOWLIST)
		वापस 0x00;

	/* Select filter policy to use white list */
	वापस 0x01;
पूर्ण

अटल bool scan_use_rpa(काष्ठा hci_dev *hdev)
अणु
	वापस hci_dev_test_flag(hdev, HCI_PRIVACY);
पूर्ण

अटल व्योम hci_req_start_scan(काष्ठा hci_request *req, u8 type, u16 पूर्णांकerval,
			       u16 winकरोw, u8 own_addr_type, u8 filter_policy,
			       bool addr_resolv)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	अगर (hdev->scanning_छोड़ोd) अणु
		bt_dev_dbg(hdev, "Scanning is paused for suspend");
		वापस;
	पूर्ण

	अगर (use_ll_privacy(hdev) &&
	    hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY) &&
	    addr_resolv) अणु
		u8 enable = 0x01;

		hci_req_add(req, HCI_OP_LE_SET_ADDR_RESOLV_ENABLE, 1, &enable);
	पूर्ण

	/* Use ext scanning अगर set ext scan param and ext scan enable is
	 * supported
	 */
	अगर (use_ext_scan(hdev)) अणु
		काष्ठा hci_cp_le_set_ext_scan_params *ext_param_cp;
		काष्ठा hci_cp_le_set_ext_scan_enable ext_enable_cp;
		काष्ठा hci_cp_le_scan_phy_params *phy_params;
		u8 data[माप(*ext_param_cp) + माप(*phy_params) * 2];
		u32 plen;

		ext_param_cp = (व्योम *)data;
		phy_params = (व्योम *)ext_param_cp->data;

		स_रखो(ext_param_cp, 0, माप(*ext_param_cp));
		ext_param_cp->own_addr_type = own_addr_type;
		ext_param_cp->filter_policy = filter_policy;

		plen = माप(*ext_param_cp);

		अगर (scan_1m(hdev) || scan_2m(hdev)) अणु
			ext_param_cp->scanning_phys |= LE_SCAN_PHY_1M;

			स_रखो(phy_params, 0, माप(*phy_params));
			phy_params->type = type;
			phy_params->पूर्णांकerval = cpu_to_le16(पूर्णांकerval);
			phy_params->winकरोw = cpu_to_le16(winकरोw);

			plen += माप(*phy_params);
			phy_params++;
		पूर्ण

		अगर (scan_coded(hdev)) अणु
			ext_param_cp->scanning_phys |= LE_SCAN_PHY_CODED;

			स_रखो(phy_params, 0, माप(*phy_params));
			phy_params->type = type;
			phy_params->पूर्णांकerval = cpu_to_le16(पूर्णांकerval);
			phy_params->winकरोw = cpu_to_le16(winकरोw);

			plen += माप(*phy_params);
			phy_params++;
		पूर्ण

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_PARAMS,
			    plen, ext_param_cp);

		स_रखो(&ext_enable_cp, 0, माप(ext_enable_cp));
		ext_enable_cp.enable = LE_SCAN_ENABLE;
		ext_enable_cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_ENABLE,
			    माप(ext_enable_cp), &ext_enable_cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_le_set_scan_param param_cp;
		काष्ठा hci_cp_le_set_scan_enable enable_cp;

		स_रखो(&param_cp, 0, माप(param_cp));
		param_cp.type = type;
		param_cp.पूर्णांकerval = cpu_to_le16(पूर्णांकerval);
		param_cp.winकरोw = cpu_to_le16(winकरोw);
		param_cp.own_address_type = own_addr_type;
		param_cp.filter_policy = filter_policy;
		hci_req_add(req, HCI_OP_LE_SET_SCAN_PARAM, माप(param_cp),
			    &param_cp);

		स_रखो(&enable_cp, 0, माप(enable_cp));
		enable_cp.enable = LE_SCAN_ENABLE;
		enable_cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;
		hci_req_add(req, HCI_OP_LE_SET_SCAN_ENABLE, माप(enable_cp),
			    &enable_cp);
	पूर्ण
पूर्ण

/* Returns true अगर an le connection is in the scanning state */
अटल अंतरभूत bool hci_is_le_conn_scanning(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn  *c;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(c, &h->list, list) अणु
		अगर (c->type == LE_LINK && c->state == BT_CONNECT &&
		    test_bit(HCI_CONN_SCANNING, &c->flags)) अणु
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस false;
पूर्ण

/* Ensure to call hci_req_add_le_scan_disable() first to disable the
 * controller based address resolution to be able to reconfigure
 * resolving list.
 */
व्योम hci_req_add_le_passive_scan(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 own_addr_type;
	u8 filter_policy;
	u16 winकरोw, पूर्णांकerval;
	/* Background scanning should run with address resolution */
	bool addr_resolv = true;

	अगर (hdev->scanning_छोड़ोd) अणु
		bt_dev_dbg(hdev, "Scanning is paused for suspend");
		वापस;
	पूर्ण

	/* Set require_privacy to false since no SCAN_REQ are send
	 * during passive scanning. Not using an non-resolvable address
	 * here is important so that peer devices using direct
	 * advertising with our address will be correctly reported
	 * by the controller.
	 */
	अगर (hci_update_अक्रमom_address(req, false, scan_use_rpa(hdev),
				      &own_addr_type))
		वापस;

	अगर (hdev->enable_advmon_पूर्णांकerleave_scan &&
	    __hci_update_पूर्णांकerleaved_scan(hdev))
		वापस;

	bt_dev_dbg(hdev, "interleave state %d", hdev->पूर्णांकerleave_scan_state);
	/* Adding or removing entries from the white list must
	 * happen beक्रमe enabling scanning. The controller करोes
	 * not allow white list modअगरication जबतक scanning.
	 */
	filter_policy = update_white_list(req);

	/* When the controller is using अक्रमom resolvable addresses and
	 * with that having LE privacy enabled, then controllers with
	 * Extended Scanner Filter Policies support can now enable support
	 * क्रम handling directed advertising.
	 *
	 * So instead of using filter polices 0x00 (no whitelist)
	 * and 0x01 (whitelist enabled) use the new filter policies
	 * 0x02 (no whitelist) and 0x03 (whitelist enabled).
	 */
	अगर (hci_dev_test_flag(hdev, HCI_PRIVACY) &&
	    (hdev->le_features[0] & HCI_LE_EXT_SCAN_POLICY))
		filter_policy |= 0x02;

	अगर (hdev->suspended) अणु
		winकरोw = hdev->le_scan_winकरोw_suspend;
		पूर्णांकerval = hdev->le_scan_पूर्णांक_suspend;

		set_bit(SUSPEND_SCAN_ENABLE, hdev->suspend_tasks);
	पूर्ण अन्यथा अगर (hci_is_le_conn_scanning(hdev)) अणु
		winकरोw = hdev->le_scan_winकरोw_connect;
		पूर्णांकerval = hdev->le_scan_पूर्णांक_connect;
	पूर्ण अन्यथा अगर (hci_is_adv_monitoring(hdev)) अणु
		winकरोw = hdev->le_scan_winकरोw_adv_monitor;
		पूर्णांकerval = hdev->le_scan_पूर्णांक_adv_monitor;
	पूर्ण अन्यथा अणु
		winकरोw = hdev->le_scan_winकरोw;
		पूर्णांकerval = hdev->le_scan_पूर्णांकerval;
	पूर्ण

	bt_dev_dbg(hdev, "LE passive scan with whitelist = %d", filter_policy);
	hci_req_start_scan(req, LE_SCAN_PASSIVE, पूर्णांकerval, winकरोw,
			   own_addr_type, filter_policy, addr_resolv);
पूर्ण

अटल bool adv_instance_is_scannable(काष्ठा hci_dev *hdev, u8 instance)
अणु
	काष्ठा adv_info *adv_instance;

	/* Instance 0x00 always set local name */
	अगर (instance == 0x00)
		वापस true;

	adv_instance = hci_find_adv_instance(hdev, instance);
	अगर (!adv_instance)
		वापस false;

	अगर (adv_instance->flags & MGMT_ADV_FLAG_APPEARANCE ||
	    adv_instance->flags & MGMT_ADV_FLAG_LOCAL_NAME)
		वापस true;

	वापस adv_instance->scan_rsp_len ? true : false;
पूर्ण

अटल व्योम hci_req_clear_event_filter(काष्ठा hci_request *req)
अणु
	काष्ठा hci_cp_set_event_filter f;

	अगर (!hci_dev_test_flag(req->hdev, HCI_BREDR_ENABLED))
		वापस;

	अगर (hci_dev_test_flag(req->hdev, HCI_EVENT_FILTER_CONFIGURED)) अणु
		स_रखो(&f, 0, माप(f));
		f.flt_type = HCI_FLT_CLEAR_ALL;
		hci_req_add(req, HCI_OP_SET_EVENT_FLT, 1, &f);
	पूर्ण
पूर्ण

अटल व्योम hci_req_set_event_filter(काष्ठा hci_request *req)
अणु
	काष्ठा bdaddr_list_with_flags *b;
	काष्ठा hci_cp_set_event_filter f;
	काष्ठा hci_dev *hdev = req->hdev;
	u8 scan = SCAN_DISABLED;
	bool scanning = test_bit(HCI_PSCAN, &hdev->flags);

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		वापस;

	/* Always clear event filter when starting */
	hci_req_clear_event_filter(req);

	list_क्रम_each_entry(b, &hdev->whitelist, list) अणु
		अगर (!hci_conn_test_flag(HCI_CONN_FLAG_REMOTE_WAKEUP,
					b->current_flags))
			जारी;

		स_रखो(&f, 0, माप(f));
		bacpy(&f.addr_conn_flt.bdaddr, &b->bdaddr);
		f.flt_type = HCI_FLT_CONN_SETUP;
		f.cond_type = HCI_CONN_SETUP_ALLOW_BDADDR;
		f.addr_conn_flt.स्वतः_accept = HCI_CONN_SETUP_AUTO_ON;

		bt_dev_dbg(hdev, "Adding event filters for %pMR", &b->bdaddr);
		hci_req_add(req, HCI_OP_SET_EVENT_FLT, माप(f), &f);
		scan = SCAN_PAGE;
	पूर्ण

	अगर (scan && !scanning) अणु
		set_bit(SUSPEND_SCAN_ENABLE, hdev->suspend_tasks);
		hci_req_add(req, HCI_OP_WRITE_SCAN_ENABLE, 1, &scan);
	पूर्ण अन्यथा अगर (!scan && scanning) अणु
		set_bit(SUSPEND_SCAN_DISABLE, hdev->suspend_tasks);
		hci_req_add(req, HCI_OP_WRITE_SCAN_ENABLE, 1, &scan);
	पूर्ण
पूर्ण

अटल व्योम cancel_adv_समयout(काष्ठा hci_dev *hdev)
अणु
	अगर (hdev->adv_instance_समयout) अणु
		hdev->adv_instance_समयout = 0;
		cancel_delayed_work(&hdev->adv_instance_expire);
	पूर्ण
पूर्ण

/* This function requires the caller holds hdev->lock */
व्योम __hci_req_छोड़ो_adv_instances(काष्ठा hci_request *req)
अणु
	bt_dev_dbg(req->hdev, "Pausing advertising instances");

	/* Call to disable any advertisements active on the controller.
	 * This will succeed even अगर no advertisements are configured.
	 */
	__hci_req_disable_advertising(req);

	/* If we are using software rotation, छोड़ो the loop */
	अगर (!ext_adv_capable(req->hdev))
		cancel_adv_समयout(req->hdev);
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल व्योम __hci_req_resume_adv_instances(काष्ठा hci_request *req)
अणु
	काष्ठा adv_info *adv;

	bt_dev_dbg(req->hdev, "Resuming advertising instances");

	अगर (ext_adv_capable(req->hdev)) अणु
		/* Call क्रम each tracked instance to be re-enabled */
		list_क्रम_each_entry(adv, &req->hdev->adv_instances, list) अणु
			__hci_req_enable_ext_advertising(req,
							 adv->instance);
		पूर्ण

	पूर्ण अन्यथा अणु
		/* Schedule क्रम most recent instance to be restarted and begin
		 * the software rotation loop
		 */
		__hci_req_schedule_adv_instance(req,
						req->hdev->cur_adv_instance,
						true);
	पूर्ण
पूर्ण

/* This function requires the caller holds hdev->lock */
पूर्णांक hci_req_resume_adv_instances(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_request req;

	hci_req_init(&req, hdev);
	__hci_req_resume_adv_instances(&req);

	वापस hci_req_run(&req, शून्य);
पूर्ण

अटल व्योम suspend_req_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	bt_dev_dbg(hdev, "Request complete opcode=0x%x, status=0x%x", opcode,
		   status);
	अगर (test_bit(SUSPEND_SCAN_ENABLE, hdev->suspend_tasks) ||
	    test_bit(SUSPEND_SCAN_DISABLE, hdev->suspend_tasks)) अणु
		clear_bit(SUSPEND_SCAN_ENABLE, hdev->suspend_tasks);
		clear_bit(SUSPEND_SCAN_DISABLE, hdev->suspend_tasks);
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण

	अगर (test_bit(SUSPEND_SET_ADV_FILTER, hdev->suspend_tasks)) अणु
		clear_bit(SUSPEND_SET_ADV_FILTER, hdev->suspend_tasks);
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण
पूर्ण

अटल व्योम hci_req_add_set_adv_filter_enable(काष्ठा hci_request *req,
					      bool enable)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	चयन (hci_get_adv_monitor_offload_ext(hdev)) अणु
	हाल HCI_ADV_MONITOR_EXT_MSFT:
		msft_req_add_set_filter_enable(req, enable);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* No need to block when enabling since it's on resume path */
	अगर (hdev->suspended && !enable)
		set_bit(SUSPEND_SET_ADV_FILTER, hdev->suspend_tasks);
पूर्ण

/* Call with hci_dev_lock */
व्योम hci_req_prepare_suspend(काष्ठा hci_dev *hdev, क्रमागत suspended_state next)
अणु
	पूर्णांक old_state;
	काष्ठा hci_conn *conn;
	काष्ठा hci_request req;
	u8 page_scan;
	पूर्णांक disconnect_counter;

	अगर (next == hdev->suspend_state) अणु
		bt_dev_dbg(hdev, "Same state before and after: %d", next);
		जाओ करोne;
	पूर्ण

	hdev->suspend_state = next;
	hci_req_init(&req, hdev);

	अगर (next == BT_SUSPEND_DISCONNECT) अणु
		/* Mark device as suspended */
		hdev->suspended = true;

		/* Pause discovery अगर not alपढ़ोy stopped */
		old_state = hdev->discovery.state;
		अगर (old_state != DISCOVERY_STOPPED) अणु
			set_bit(SUSPEND_PAUSE_DISCOVERY, hdev->suspend_tasks);
			hci_discovery_set_state(hdev, DISCOVERY_STOPPING);
			queue_work(hdev->req_workqueue, &hdev->discov_update);
		पूर्ण

		hdev->discovery_छोड़ोd = true;
		hdev->discovery_old_state = old_state;

		/* Stop directed advertising */
		old_state = hci_dev_test_flag(hdev, HCI_ADVERTISING);
		अगर (old_state) अणु
			set_bit(SUSPEND_PAUSE_ADVERTISING, hdev->suspend_tasks);
			cancel_delayed_work(&hdev->discov_off);
			queue_delayed_work(hdev->req_workqueue,
					   &hdev->discov_off, 0);
		पूर्ण

		/* Pause other advertisements */
		अगर (hdev->adv_instance_cnt)
			__hci_req_छोड़ो_adv_instances(&req);

		hdev->advertising_छोड़ोd = true;
		hdev->advertising_old_state = old_state;

		/* Disable page scan अगर enabled */
		अगर (test_bit(HCI_PSCAN, &hdev->flags)) अणु
			page_scan = SCAN_DISABLED;
			hci_req_add(&req, HCI_OP_WRITE_SCAN_ENABLE, 1,
				    &page_scan);
			set_bit(SUSPEND_SCAN_DISABLE, hdev->suspend_tasks);
		पूर्ण

		/* Disable LE passive scan अगर enabled */
		अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN)) अणु
			cancel_पूर्णांकerleave_scan(hdev);
			hci_req_add_le_scan_disable(&req, false);
		पूर्ण

		/* Disable advertisement filters */
		hci_req_add_set_adv_filter_enable(&req, false);

		/* Prevent disconnects from causing scanning to be re-enabled */
		hdev->scanning_छोड़ोd = true;

		/* Run commands beक्रमe disconnecting */
		hci_req_run(&req, suspend_req_complete);

		disconnect_counter = 0;
		/* Soft disconnect everything (घातer off) */
		list_क्रम_each_entry(conn, &hdev->conn_hash.list, list) अणु
			hci_disconnect(conn, HCI_ERROR_REMOTE_POWER_OFF);
			disconnect_counter++;
		पूर्ण

		अगर (disconnect_counter > 0) अणु
			bt_dev_dbg(hdev,
				   "Had %d disconnects. Will wait on them",
				   disconnect_counter);
			set_bit(SUSPEND_DISCONNECTING, hdev->suspend_tasks);
		पूर्ण
	पूर्ण अन्यथा अगर (next == BT_SUSPEND_CONFIGURE_WAKE) अणु
		/* Unछोड़ो to take care of updating scanning params */
		hdev->scanning_छोड़ोd = false;
		/* Enable event filter क्रम paired devices */
		hci_req_set_event_filter(&req);
		/* Enable passive scan at lower duty cycle */
		__hci_update_background_scan(&req);
		/* Pause scan changes again. */
		hdev->scanning_छोड़ोd = true;
		hci_req_run(&req, suspend_req_complete);
	पूर्ण अन्यथा अणु
		hdev->suspended = false;
		hdev->scanning_छोड़ोd = false;

		/* Clear any event filters and restore scan state */
		hci_req_clear_event_filter(&req);
		__hci_req_update_scan(&req);

		/* Reset passive/background scanning to normal */
		__hci_update_background_scan(&req);
		/* Enable all of the advertisement filters */
		hci_req_add_set_adv_filter_enable(&req, true);

		/* Unछोड़ो directed advertising */
		hdev->advertising_छोड़ोd = false;
		अगर (hdev->advertising_old_state) अणु
			set_bit(SUSPEND_UNPAUSE_ADVERTISING,
				hdev->suspend_tasks);
			hci_dev_set_flag(hdev, HCI_ADVERTISING);
			queue_work(hdev->req_workqueue,
				   &hdev->discoverable_update);
			hdev->advertising_old_state = 0;
		पूर्ण

		/* Resume other advertisements */
		अगर (hdev->adv_instance_cnt)
			__hci_req_resume_adv_instances(&req);

		/* Unछोड़ो discovery */
		hdev->discovery_छोड़ोd = false;
		अगर (hdev->discovery_old_state != DISCOVERY_STOPPED &&
		    hdev->discovery_old_state != DISCOVERY_STOPPING) अणु
			set_bit(SUSPEND_UNPAUSE_DISCOVERY, hdev->suspend_tasks);
			hci_discovery_set_state(hdev, DISCOVERY_STARTING);
			queue_work(hdev->req_workqueue, &hdev->discov_update);
		पूर्ण

		hci_req_run(&req, suspend_req_complete);
	पूर्ण

	hdev->suspend_state = next;

करोne:
	clear_bit(SUSPEND_PREPARE_NOTIFIER, hdev->suspend_tasks);
	wake_up(&hdev->suspend_रुको_q);
पूर्ण

अटल bool adv_cur_instance_is_scannable(काष्ठा hci_dev *hdev)
अणु
	वापस adv_instance_is_scannable(hdev, hdev->cur_adv_instance);
पूर्ण

व्योम __hci_req_disable_advertising(काष्ठा hci_request *req)
अणु
	अगर (ext_adv_capable(req->hdev)) अणु
		__hci_req_disable_ext_adv_instance(req, 0x00);

	पूर्ण अन्यथा अणु
		u8 enable = 0x00;

		hci_req_add(req, HCI_OP_LE_SET_ADV_ENABLE, माप(enable), &enable);
	पूर्ण
पूर्ण

अटल u32 get_adv_instance_flags(काष्ठा hci_dev *hdev, u8 instance)
अणु
	u32 flags;
	काष्ठा adv_info *adv_instance;

	अगर (instance == 0x00) अणु
		/* Instance 0 always manages the "Tx Power" and "Flags"
		 * fields
		 */
		flags = MGMT_ADV_FLAG_TX_POWER | MGMT_ADV_FLAG_MANAGED_FLAGS;

		/* For instance 0, the HCI_ADVERTISING_CONNECTABLE setting
		 * corresponds to the "connectable" instance flag.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING_CONNECTABLE))
			flags |= MGMT_ADV_FLAG_CONNECTABLE;

		अगर (hci_dev_test_flag(hdev, HCI_LIMITED_DISCOVERABLE))
			flags |= MGMT_ADV_FLAG_LIMITED_DISCOV;
		अन्यथा अगर (hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
			flags |= MGMT_ADV_FLAG_DISCOV;

		वापस flags;
	पूर्ण

	adv_instance = hci_find_adv_instance(hdev, instance);

	/* Return 0 when we got an invalid instance identअगरier. */
	अगर (!adv_instance)
		वापस 0;

	वापस adv_instance->flags;
पूर्ण

अटल bool adv_use_rpa(काष्ठा hci_dev *hdev, uपूर्णांक32_t flags)
अणु
	/* If privacy is not enabled करोn't use RPA */
	अगर (!hci_dev_test_flag(hdev, HCI_PRIVACY))
		वापस false;

	/* If basic privacy mode is enabled use RPA */
	अगर (!hci_dev_test_flag(hdev, HCI_LIMITED_PRIVACY))
		वापस true;

	/* If limited privacy mode is enabled करोn't use RPA if we're
	 * both discoverable and bondable.
	 */
	अगर ((flags & MGMT_ADV_FLAG_DISCOV) &&
	    hci_dev_test_flag(hdev, HCI_BONDABLE))
		वापस false;

	/* We're neither bondable nor discoverable in the limited
	 * privacy mode, thereक्रमe use RPA.
	 */
	वापस true;
पूर्ण

अटल bool is_advertising_allowed(काष्ठा hci_dev *hdev, bool connectable)
अणु
	/* If there is no connection we are OK to advertise. */
	अगर (hci_conn_num(hdev, LE_LINK) == 0)
		वापस true;

	/* Check le_states अगर there is any connection in slave role. */
	अगर (hdev->conn_hash.le_num_slave > 0) अणु
		/* Slave connection state and non connectable mode bit 20. */
		अगर (!connectable && !(hdev->le_states[2] & 0x10))
			वापस false;

		/* Slave connection state and connectable mode bit 38
		 * and scannable bit 21.
		 */
		अगर (connectable && (!(hdev->le_states[4] & 0x40) ||
				    !(hdev->le_states[2] & 0x20)))
			वापस false;
	पूर्ण

	/* Check le_states अगर there is any connection in master role. */
	अगर (hci_conn_num(hdev, LE_LINK) != hdev->conn_hash.le_num_slave) अणु
		/* Master connection state and non connectable mode bit 18. */
		अगर (!connectable && !(hdev->le_states[2] & 0x02))
			वापस false;

		/* Master connection state and connectable mode bit 35 and
		 * scannable 19.
		 */
		अगर (connectable && (!(hdev->le_states[4] & 0x08) ||
				    !(hdev->le_states[2] & 0x08)))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम __hci_req_enable_advertising(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा adv_info *adv_instance;
	काष्ठा hci_cp_le_set_adv_param cp;
	u8 own_addr_type, enable = 0x01;
	bool connectable;
	u16 adv_min_पूर्णांकerval, adv_max_पूर्णांकerval;
	u32 flags;

	flags = get_adv_instance_flags(hdev, hdev->cur_adv_instance);
	adv_instance = hci_find_adv_instance(hdev, hdev->cur_adv_instance);

	/* If the "connectable" instance flag was not set, then choose between
	 * ADV_IND and ADV_NONCONN_IND based on the global connectable setting.
	 */
	connectable = (flags & MGMT_ADV_FLAG_CONNECTABLE) ||
		      mgmt_get_connectable(hdev);

	अगर (!is_advertising_allowed(hdev, connectable))
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_LE_ADV))
		__hci_req_disable_advertising(req);

	/* Clear the HCI_LE_ADV bit temporarily so that the
	 * hci_update_अक्रमom_address knows that it's safe to go ahead
	 * and ग_लिखो a new अक्रमom address. The flag will be set back on
	 * as soon as the SET_ADV_ENABLE HCI command completes.
	 */
	hci_dev_clear_flag(hdev, HCI_LE_ADV);

	/* Set require_privacy to true only when non-connectable
	 * advertising is used. In that हाल it is fine to use a
	 * non-resolvable निजी address.
	 */
	अगर (hci_update_अक्रमom_address(req, !connectable,
				      adv_use_rpa(hdev, flags),
				      &own_addr_type) < 0)
		वापस;

	स_रखो(&cp, 0, माप(cp));

	अगर (adv_instance) अणु
		adv_min_पूर्णांकerval = adv_instance->min_पूर्णांकerval;
		adv_max_पूर्णांकerval = adv_instance->max_पूर्णांकerval;
	पूर्ण अन्यथा अणु
		adv_min_पूर्णांकerval = hdev->le_adv_min_पूर्णांकerval;
		adv_max_पूर्णांकerval = hdev->le_adv_max_पूर्णांकerval;
	पूर्ण

	अगर (connectable) अणु
		cp.type = LE_ADV_IND;
	पूर्ण अन्यथा अणु
		अगर (adv_cur_instance_is_scannable(hdev))
			cp.type = LE_ADV_SCAN_IND;
		अन्यथा
			cp.type = LE_ADV_NONCONN_IND;

		अगर (!hci_dev_test_flag(hdev, HCI_DISCOVERABLE) ||
		    hci_dev_test_flag(hdev, HCI_LIMITED_DISCOVERABLE)) अणु
			adv_min_पूर्णांकerval = DISCOV_LE_FAST_ADV_पूर्णांक_न्यून;
			adv_max_पूर्णांकerval = DISCOV_LE_FAST_ADV_पूर्णांक_उच्च;
		पूर्ण
	पूर्ण

	cp.min_पूर्णांकerval = cpu_to_le16(adv_min_पूर्णांकerval);
	cp.max_पूर्णांकerval = cpu_to_le16(adv_max_पूर्णांकerval);
	cp.own_address_type = own_addr_type;
	cp.channel_map = hdev->le_adv_channel_map;

	hci_req_add(req, HCI_OP_LE_SET_ADV_PARAM, माप(cp), &cp);

	hci_req_add(req, HCI_OP_LE_SET_ADV_ENABLE, माप(enable), &enable);
पूर्ण

u8 append_local_name(काष्ठा hci_dev *hdev, u8 *ptr, u8 ad_len)
अणु
	माप_प्रकार लघु_len;
	माप_प्रकार complete_len;

	/* no space left क्रम name (+ शून्य + type + len) */
	अगर ((HCI_MAX_AD_LENGTH - ad_len) < HCI_MAX_SHORT_NAME_LENGTH + 3)
		वापस ad_len;

	/* use complete name अगर present and fits */
	complete_len = म_माप(hdev->dev_name);
	अगर (complete_len && complete_len <= HCI_MAX_SHORT_NAME_LENGTH)
		वापस eir_append_data(ptr, ad_len, EIR_NAME_COMPLETE,
				       hdev->dev_name, complete_len + 1);

	/* use लघु name अगर present */
	लघु_len = म_माप(hdev->लघु_name);
	अगर (लघु_len)
		वापस eir_append_data(ptr, ad_len, EIR_NAME_SHORT,
				       hdev->लघु_name, लघु_len + 1);

	/* use लघुened full name अगर present, we alपढ़ोy know that name
	 * is दीर्घer then HCI_MAX_SHORT_NAME_LENGTH
	 */
	अगर (complete_len) अणु
		u8 name[HCI_MAX_SHORT_NAME_LENGTH + 1];

		स_नकल(name, hdev->dev_name, HCI_MAX_SHORT_NAME_LENGTH);
		name[HCI_MAX_SHORT_NAME_LENGTH] = '\0';

		वापस eir_append_data(ptr, ad_len, EIR_NAME_SHORT, name,
				       माप(name));
	पूर्ण

	वापस ad_len;
पूर्ण

अटल u8 append_appearance(काष्ठा hci_dev *hdev, u8 *ptr, u8 ad_len)
अणु
	वापस eir_append_le16(ptr, ad_len, EIR_APPEARANCE, hdev->appearance);
पूर्ण

अटल u8 create_शेष_scan_rsp_data(काष्ठा hci_dev *hdev, u8 *ptr)
अणु
	u8 scan_rsp_len = 0;

	अगर (hdev->appearance)
		scan_rsp_len = append_appearance(hdev, ptr, scan_rsp_len);

	वापस append_local_name(hdev, ptr, scan_rsp_len);
पूर्ण

अटल u8 create_instance_scan_rsp_data(काष्ठा hci_dev *hdev, u8 instance,
					u8 *ptr)
अणु
	काष्ठा adv_info *adv_instance;
	u32 instance_flags;
	u8 scan_rsp_len = 0;

	adv_instance = hci_find_adv_instance(hdev, instance);
	अगर (!adv_instance)
		वापस 0;

	instance_flags = adv_instance->flags;

	अगर ((instance_flags & MGMT_ADV_FLAG_APPEARANCE) && hdev->appearance)
		scan_rsp_len = append_appearance(hdev, ptr, scan_rsp_len);

	स_नकल(&ptr[scan_rsp_len], adv_instance->scan_rsp_data,
	       adv_instance->scan_rsp_len);

	scan_rsp_len += adv_instance->scan_rsp_len;

	अगर (instance_flags & MGMT_ADV_FLAG_LOCAL_NAME)
		scan_rsp_len = append_local_name(hdev, ptr, scan_rsp_len);

	वापस scan_rsp_len;
पूर्ण

व्योम __hci_req_update_scan_rsp_data(काष्ठा hci_request *req, u8 instance)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 len;

	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		वापस;

	अगर (ext_adv_capable(hdev)) अणु
		काष्ठा hci_cp_le_set_ext_scan_rsp_data cp;

		स_रखो(&cp, 0, माप(cp));

		अगर (instance)
			len = create_instance_scan_rsp_data(hdev, instance,
							    cp.data);
		अन्यथा
			len = create_शेष_scan_rsp_data(hdev, cp.data);

		अगर (hdev->scan_rsp_data_len == len &&
		    !स_भेद(cp.data, hdev->scan_rsp_data, len))
			वापस;

		स_नकल(hdev->scan_rsp_data, cp.data, माप(cp.data));
		hdev->scan_rsp_data_len = len;

		cp.handle = instance;
		cp.length = len;
		cp.operation = LE_SET_ADV_DATA_OP_COMPLETE;
		cp.frag_pref = LE_SET_ADV_DATA_NO_FRAG;

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_RSP_DATA, माप(cp),
			    &cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_le_set_scan_rsp_data cp;

		स_रखो(&cp, 0, माप(cp));

		अगर (instance)
			len = create_instance_scan_rsp_data(hdev, instance,
							    cp.data);
		अन्यथा
			len = create_शेष_scan_rsp_data(hdev, cp.data);

		अगर (hdev->scan_rsp_data_len == len &&
		    !स_भेद(cp.data, hdev->scan_rsp_data, len))
			वापस;

		स_नकल(hdev->scan_rsp_data, cp.data, माप(cp.data));
		hdev->scan_rsp_data_len = len;

		cp.length = len;

		hci_req_add(req, HCI_OP_LE_SET_SCAN_RSP_DATA, माप(cp), &cp);
	पूर्ण
पूर्ण

अटल u8 create_instance_adv_data(काष्ठा hci_dev *hdev, u8 instance, u8 *ptr)
अणु
	काष्ठा adv_info *adv_instance = शून्य;
	u8 ad_len = 0, flags = 0;
	u32 instance_flags;

	/* Return 0 when the current instance identअगरier is invalid. */
	अगर (instance) अणु
		adv_instance = hci_find_adv_instance(hdev, instance);
		अगर (!adv_instance)
			वापस 0;
	पूर्ण

	instance_flags = get_adv_instance_flags(hdev, instance);

	/* If instance alपढ़ोy has the flags set skip adding it once
	 * again.
	 */
	अगर (adv_instance && eir_get_data(adv_instance->adv_data,
					 adv_instance->adv_data_len, EIR_FLAGS,
					 शून्य))
		जाओ skip_flags;

	/* The Add Advertising command allows userspace to set both the general
	 * and limited discoverable flags.
	 */
	अगर (instance_flags & MGMT_ADV_FLAG_DISCOV)
		flags |= LE_AD_GENERAL;

	अगर (instance_flags & MGMT_ADV_FLAG_LIMITED_DISCOV)
		flags |= LE_AD_LIMITED;

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		flags |= LE_AD_NO_BREDR;

	अगर (flags || (instance_flags & MGMT_ADV_FLAG_MANAGED_FLAGS)) अणु
		/* If a discovery flag wasn't provided, simply use the global
		 * settings.
		 */
		अगर (!flags)
			flags |= mgmt_get_adv_discov_flags(hdev);

		/* If flags would still be empty, then there is no need to
		 * include the "Flags" AD field".
		 */
		अगर (flags) अणु
			ptr[0] = 0x02;
			ptr[1] = EIR_FLAGS;
			ptr[2] = flags;

			ad_len += 3;
			ptr += 3;
		पूर्ण
	पूर्ण

skip_flags:
	अगर (adv_instance) अणु
		स_नकल(ptr, adv_instance->adv_data,
		       adv_instance->adv_data_len);
		ad_len += adv_instance->adv_data_len;
		ptr += adv_instance->adv_data_len;
	पूर्ण

	अगर (instance_flags & MGMT_ADV_FLAG_TX_POWER) अणु
		s8 adv_tx_घातer;

		अगर (ext_adv_capable(hdev)) अणु
			अगर (adv_instance)
				adv_tx_घातer = adv_instance->tx_घातer;
			अन्यथा
				adv_tx_घातer = hdev->adv_tx_घातer;
		पूर्ण अन्यथा अणु
			adv_tx_घातer = hdev->adv_tx_घातer;
		पूर्ण

		/* Provide Tx Power only अगर we can provide a valid value क्रम it */
		अगर (adv_tx_घातer != HCI_TX_POWER_INVALID) अणु
			ptr[0] = 0x02;
			ptr[1] = EIR_TX_POWER;
			ptr[2] = (u8)adv_tx_घातer;

			ad_len += 3;
			ptr += 3;
		पूर्ण
	पूर्ण

	वापस ad_len;
पूर्ण

व्योम __hci_req_update_adv_data(काष्ठा hci_request *req, u8 instance)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 len;

	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		वापस;

	अगर (ext_adv_capable(hdev)) अणु
		काष्ठा hci_cp_le_set_ext_adv_data cp;

		स_रखो(&cp, 0, माप(cp));

		len = create_instance_adv_data(hdev, instance, cp.data);

		/* There's nothing to do if the data hasn't changed */
		अगर (hdev->adv_data_len == len &&
		    स_भेद(cp.data, hdev->adv_data, len) == 0)
			वापस;

		स_नकल(hdev->adv_data, cp.data, माप(cp.data));
		hdev->adv_data_len = len;

		cp.length = len;
		cp.handle = instance;
		cp.operation = LE_SET_ADV_DATA_OP_COMPLETE;
		cp.frag_pref = LE_SET_ADV_DATA_NO_FRAG;

		hci_req_add(req, HCI_OP_LE_SET_EXT_ADV_DATA, माप(cp), &cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_le_set_adv_data cp;

		स_रखो(&cp, 0, माप(cp));

		len = create_instance_adv_data(hdev, instance, cp.data);

		/* There's nothing to do if the data hasn't changed */
		अगर (hdev->adv_data_len == len &&
		    स_भेद(cp.data, hdev->adv_data, len) == 0)
			वापस;

		स_नकल(hdev->adv_data, cp.data, माप(cp.data));
		hdev->adv_data_len = len;

		cp.length = len;

		hci_req_add(req, HCI_OP_LE_SET_ADV_DATA, माप(cp), &cp);
	पूर्ण
पूर्ण

पूर्णांक hci_req_update_adv_data(काष्ठा hci_dev *hdev, u8 instance)
अणु
	काष्ठा hci_request req;

	hci_req_init(&req, hdev);
	__hci_req_update_adv_data(&req, instance);

	वापस hci_req_run(&req, शून्य);
पूर्ण

अटल व्योम enable_addr_resolution_complete(काष्ठा hci_dev *hdev, u8 status,
					    u16 opcode)
अणु
	BT_DBG("%s status %u", hdev->name, status);
पूर्ण

व्योम hci_req_disable_address_resolution(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_request req;
	__u8 enable = 0x00;

	अगर (!use_ll_privacy(hdev) &&
	    !hci_dev_test_flag(hdev, HCI_LL_RPA_RESOLUTION))
		वापस;

	hci_req_init(&req, hdev);

	hci_req_add(&req, HCI_OP_LE_SET_ADDR_RESOLV_ENABLE, 1, &enable);

	hci_req_run(&req, enable_addr_resolution_complete);
पूर्ण

अटल व्योम adv_enable_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	bt_dev_dbg(hdev, "status %u", status);
पूर्ण

व्योम hci_req_reenable_advertising(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_request req;

	अगर (!hci_dev_test_flag(hdev, HCI_ADVERTISING) &&
	    list_empty(&hdev->adv_instances))
		वापस;

	hci_req_init(&req, hdev);

	अगर (hdev->cur_adv_instance) अणु
		__hci_req_schedule_adv_instance(&req, hdev->cur_adv_instance,
						true);
	पूर्ण अन्यथा अणु
		अगर (ext_adv_capable(hdev)) अणु
			__hci_req_start_ext_adv(&req, 0x00);
		पूर्ण अन्यथा अणु
			__hci_req_update_adv_data(&req, 0x00);
			__hci_req_update_scan_rsp_data(&req, 0x00);
			__hci_req_enable_advertising(&req);
		पूर्ण
	पूर्ण

	hci_req_run(&req, adv_enable_complete);
पूर्ण

अटल व्योम adv_समयout_expire(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    adv_instance_expire.work);

	काष्ठा hci_request req;
	u8 instance;

	bt_dev_dbg(hdev, "");

	hci_dev_lock(hdev);

	hdev->adv_instance_समयout = 0;

	instance = hdev->cur_adv_instance;
	अगर (instance == 0x00)
		जाओ unlock;

	hci_req_init(&req, hdev);

	hci_req_clear_adv_instance(hdev, शून्य, &req, instance, false);

	अगर (list_empty(&hdev->adv_instances))
		__hci_req_disable_advertising(&req);

	hci_req_run(&req, शून्य);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक hci_req_add_le_पूर्णांकerleaved_scan(काष्ठा hci_request *req,
					   अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	पूर्णांक ret = 0;

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN))
		hci_req_add_le_scan_disable(req, false);
	hci_req_add_le_passive_scan(req);

	चयन (hdev->पूर्णांकerleave_scan_state) अणु
	हाल INTERLEAVE_SCAN_ALLOWLIST:
		bt_dev_dbg(hdev, "next state: allowlist");
		hdev->पूर्णांकerleave_scan_state = INTERLEAVE_SCAN_NO_FILTER;
		अवरोध;
	हाल INTERLEAVE_SCAN_NO_FILTER:
		bt_dev_dbg(hdev, "next state: no filter");
		hdev->पूर्णांकerleave_scan_state = INTERLEAVE_SCAN_ALLOWLIST;
		अवरोध;
	हाल INTERLEAVE_SCAN_NONE:
		BT_ERR("unexpected error");
		ret = -1;
	पूर्ण

	hci_dev_unlock(hdev);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकerleave_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    पूर्णांकerleave_scan.work);
	u8 status;
	अचिन्हित दीर्घ समयout;

	अगर (hdev->पूर्णांकerleave_scan_state == INTERLEAVE_SCAN_ALLOWLIST) अणु
		समयout = msecs_to_jअगरfies(hdev->advmon_allowlist_duration);
	पूर्ण अन्यथा अगर (hdev->पूर्णांकerleave_scan_state == INTERLEAVE_SCAN_NO_FILTER) अणु
		समयout = msecs_to_jअगरfies(hdev->advmon_no_filter_duration);
	पूर्ण अन्यथा अणु
		bt_dev_err(hdev, "unexpected error");
		वापस;
	पूर्ण

	hci_req_sync(hdev, hci_req_add_le_पूर्णांकerleaved_scan, 0,
		     HCI_CMD_TIMEOUT, &status);

	/* Don't जारी पूर्णांकerleaving अगर it was canceled */
	अगर (is_पूर्णांकerleave_scanning(hdev))
		queue_delayed_work(hdev->req_workqueue,
				   &hdev->पूर्णांकerleave_scan, समयout);
पूर्ण

पूर्णांक hci_get_अक्रमom_address(काष्ठा hci_dev *hdev, bool require_privacy,
			   bool use_rpa, काष्ठा adv_info *adv_instance,
			   u8 *own_addr_type, bdaddr_t *अक्रम_addr)
अणु
	पूर्णांक err;

	bacpy(अक्रम_addr, BDADDR_ANY);

	/* If privacy is enabled use a resolvable निजी address. If
	 * current RPA has expired then generate a new one.
	 */
	अगर (use_rpa) अणु
		पूर्णांक to;

		/* If Controller supports LL Privacy use own address type is
		 * 0x03
		 */
		अगर (use_ll_privacy(hdev) &&
		    hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
			*own_addr_type = ADDR_LE_DEV_RANDOM_RESOLVED;
		अन्यथा
			*own_addr_type = ADDR_LE_DEV_RANDOM;

		अगर (adv_instance) अणु
			अगर (!adv_instance->rpa_expired &&
			    !bacmp(&adv_instance->अक्रमom_addr, &hdev->rpa))
				वापस 0;

			adv_instance->rpa_expired = false;
		पूर्ण अन्यथा अणु
			अगर (!hci_dev_test_and_clear_flag(hdev, HCI_RPA_EXPIRED) &&
			    !bacmp(&hdev->अक्रमom_addr, &hdev->rpa))
				वापस 0;
		पूर्ण

		err = smp_generate_rpa(hdev, hdev->irk, &hdev->rpa);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "failed to generate new RPA");
			वापस err;
		पूर्ण

		bacpy(अक्रम_addr, &hdev->rpa);

		to = msecs_to_jअगरfies(hdev->rpa_समयout * 1000);
		अगर (adv_instance)
			queue_delayed_work(hdev->workqueue,
					   &adv_instance->rpa_expired_cb, to);
		अन्यथा
			queue_delayed_work(hdev->workqueue,
					   &hdev->rpa_expired, to);

		वापस 0;
	पूर्ण

	/* In हाल of required privacy without resolvable निजी address,
	 * use an non-resolvable निजी address. This is useful क्रम
	 * non-connectable advertising.
	 */
	अगर (require_privacy) अणु
		bdaddr_t nrpa;

		जबतक (true) अणु
			/* The non-resolvable निजी address is generated
			 * from अक्रमom six bytes with the two most signअगरicant
			 * bits cleared.
			 */
			get_अक्रमom_bytes(&nrpa, 6);
			nrpa.b[5] &= 0x3f;

			/* The non-resolvable निजी address shall not be
			 * equal to the खुला address.
			 */
			अगर (bacmp(&hdev->bdaddr, &nrpa))
				अवरोध;
		पूर्ण

		*own_addr_type = ADDR_LE_DEV_RANDOM;
		bacpy(अक्रम_addr, &nrpa);

		वापस 0;
	पूर्ण

	/* No privacy so use a खुला address. */
	*own_addr_type = ADDR_LE_DEV_PUBLIC;

	वापस 0;
पूर्ण

व्योम __hci_req_clear_ext_adv_sets(काष्ठा hci_request *req)
अणु
	hci_req_add(req, HCI_OP_LE_CLEAR_ADV_SETS, 0, शून्य);
पूर्ण

पूर्णांक __hci_req_setup_ext_adv_instance(काष्ठा hci_request *req, u8 instance)
अणु
	काष्ठा hci_cp_le_set_ext_adv_params cp;
	काष्ठा hci_dev *hdev = req->hdev;
	bool connectable;
	u32 flags;
	bdaddr_t अक्रमom_addr;
	u8 own_addr_type;
	पूर्णांक err;
	काष्ठा adv_info *adv_instance;
	bool secondary_adv;

	अगर (instance > 0) अणु
		adv_instance = hci_find_adv_instance(hdev, instance);
		अगर (!adv_instance)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		adv_instance = शून्य;
	पूर्ण

	flags = get_adv_instance_flags(hdev, instance);

	/* If the "connectable" instance flag was not set, then choose between
	 * ADV_IND and ADV_NONCONN_IND based on the global connectable setting.
	 */
	connectable = (flags & MGMT_ADV_FLAG_CONNECTABLE) ||
		      mgmt_get_connectable(hdev);

	अगर (!is_advertising_allowed(hdev, connectable))
		वापस -EPERM;

	/* Set require_privacy to true only when non-connectable
	 * advertising is used. In that हाल it is fine to use a
	 * non-resolvable निजी address.
	 */
	err = hci_get_अक्रमom_address(hdev, !connectable,
				     adv_use_rpa(hdev, flags), adv_instance,
				     &own_addr_type, &अक्रमom_addr);
	अगर (err < 0)
		वापस err;

	स_रखो(&cp, 0, माप(cp));

	अगर (adv_instance) अणु
		hci_cpu_to_le24(adv_instance->min_पूर्णांकerval, cp.min_पूर्णांकerval);
		hci_cpu_to_le24(adv_instance->max_पूर्णांकerval, cp.max_पूर्णांकerval);
		cp.tx_घातer = adv_instance->tx_घातer;
	पूर्ण अन्यथा अणु
		hci_cpu_to_le24(hdev->le_adv_min_पूर्णांकerval, cp.min_पूर्णांकerval);
		hci_cpu_to_le24(hdev->le_adv_max_पूर्णांकerval, cp.max_पूर्णांकerval);
		cp.tx_घातer = HCI_ADV_TX_POWER_NO_PREFERENCE;
	पूर्ण

	secondary_adv = (flags & MGMT_ADV_FLAG_SEC_MASK);

	अगर (connectable) अणु
		अगर (secondary_adv)
			cp.evt_properties = cpu_to_le16(LE_EXT_ADV_CONN_IND);
		अन्यथा
			cp.evt_properties = cpu_to_le16(LE_LEGACY_ADV_IND);
	पूर्ण अन्यथा अगर (adv_instance_is_scannable(hdev, instance) ||
		   (flags & MGMT_ADV_PARAM_SCAN_RSP)) अणु
		अगर (secondary_adv)
			cp.evt_properties = cpu_to_le16(LE_EXT_ADV_SCAN_IND);
		अन्यथा
			cp.evt_properties = cpu_to_le16(LE_LEGACY_ADV_SCAN_IND);
	पूर्ण अन्यथा अणु
		अगर (secondary_adv)
			cp.evt_properties = cpu_to_le16(LE_EXT_ADV_NON_CONN_IND);
		अन्यथा
			cp.evt_properties = cpu_to_le16(LE_LEGACY_NONCONN_IND);
	पूर्ण

	cp.own_addr_type = own_addr_type;
	cp.channel_map = hdev->le_adv_channel_map;
	cp.handle = instance;

	अगर (flags & MGMT_ADV_FLAG_SEC_2M) अणु
		cp.primary_phy = HCI_ADV_PHY_1M;
		cp.secondary_phy = HCI_ADV_PHY_2M;
	पूर्ण अन्यथा अगर (flags & MGMT_ADV_FLAG_SEC_CODED) अणु
		cp.primary_phy = HCI_ADV_PHY_CODED;
		cp.secondary_phy = HCI_ADV_PHY_CODED;
	पूर्ण अन्यथा अणु
		/* In all other हालs use 1M */
		cp.primary_phy = HCI_ADV_PHY_1M;
		cp.secondary_phy = HCI_ADV_PHY_1M;
	पूर्ण

	hci_req_add(req, HCI_OP_LE_SET_EXT_ADV_PARAMS, माप(cp), &cp);

	अगर (own_addr_type == ADDR_LE_DEV_RANDOM &&
	    bacmp(&अक्रमom_addr, BDADDR_ANY)) अणु
		काष्ठा hci_cp_le_set_adv_set_अक्रम_addr cp;

		/* Check अगर अक्रमom address need to be updated */
		अगर (adv_instance) अणु
			अगर (!bacmp(&अक्रमom_addr, &adv_instance->अक्रमom_addr))
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (!bacmp(&अक्रमom_addr, &hdev->अक्रमom_addr))
				वापस 0;
		पूर्ण

		स_रखो(&cp, 0, माप(cp));

		cp.handle = instance;
		bacpy(&cp.bdaddr, &अक्रमom_addr);

		hci_req_add(req,
			    HCI_OP_LE_SET_ADV_SET_RAND_ADDR,
			    माप(cp), &cp);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __hci_req_enable_ext_advertising(काष्ठा hci_request *req, u8 instance)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_le_set_ext_adv_enable *cp;
	काष्ठा hci_cp_ext_adv_set *adv_set;
	u8 data[माप(*cp) + माप(*adv_set) * 1];
	काष्ठा adv_info *adv_instance;

	अगर (instance > 0) अणु
		adv_instance = hci_find_adv_instance(hdev, instance);
		अगर (!adv_instance)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		adv_instance = शून्य;
	पूर्ण

	cp = (व्योम *) data;
	adv_set = (व्योम *) cp->data;

	स_रखो(cp, 0, माप(*cp));

	cp->enable = 0x01;
	cp->num_of_sets = 0x01;

	स_रखो(adv_set, 0, माप(*adv_set));

	adv_set->handle = instance;

	/* Set duration per instance since controller is responsible क्रम
	 * scheduling it.
	 */
	अगर (adv_instance && adv_instance->duration) अणु
		u16 duration = adv_instance->समयout * MSEC_PER_SEC;

		/* Time = N * 10 ms */
		adv_set->duration = cpu_to_le16(duration / 10);
	पूर्ण

	hci_req_add(req, HCI_OP_LE_SET_EXT_ADV_ENABLE,
		    माप(*cp) + माप(*adv_set) * cp->num_of_sets,
		    data);

	वापस 0;
पूर्ण

पूर्णांक __hci_req_disable_ext_adv_instance(काष्ठा hci_request *req, u8 instance)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_le_set_ext_adv_enable *cp;
	काष्ठा hci_cp_ext_adv_set *adv_set;
	u8 data[माप(*cp) + माप(*adv_set) * 1];
	u8 req_size;

	/* If request specअगरies an instance that करोesn't exist, fail */
	अगर (instance > 0 && !hci_find_adv_instance(hdev, instance))
		वापस -EINVAL;

	स_रखो(data, 0, माप(data));

	cp = (व्योम *)data;
	adv_set = (व्योम *)cp->data;

	/* Instance 0x00 indicates all advertising instances will be disabled */
	cp->num_of_sets = !!instance;
	cp->enable = 0x00;

	adv_set->handle = instance;

	req_size = माप(*cp) + माप(*adv_set) * cp->num_of_sets;
	hci_req_add(req, HCI_OP_LE_SET_EXT_ADV_ENABLE, req_size, data);

	वापस 0;
पूर्ण

पूर्णांक __hci_req_हटाओ_ext_adv_instance(काष्ठा hci_request *req, u8 instance)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	/* If request specअगरies an instance that करोesn't exist, fail */
	अगर (instance > 0 && !hci_find_adv_instance(hdev, instance))
		वापस -EINVAL;

	hci_req_add(req, HCI_OP_LE_REMOVE_ADV_SET, माप(instance), &instance);

	वापस 0;
पूर्ण

पूर्णांक __hci_req_start_ext_adv(काष्ठा hci_request *req, u8 instance)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा adv_info *adv_instance = hci_find_adv_instance(hdev, instance);
	पूर्णांक err;

	/* If instance isn't pending, the chip knows about it, and it's safe to
	 * disable
	 */
	अगर (adv_instance && !adv_instance->pending)
		__hci_req_disable_ext_adv_instance(req, instance);

	err = __hci_req_setup_ext_adv_instance(req, instance);
	अगर (err < 0)
		वापस err;

	__hci_req_update_scan_rsp_data(req, instance);
	__hci_req_enable_ext_advertising(req, instance);

	वापस 0;
पूर्ण

पूर्णांक __hci_req_schedule_adv_instance(काष्ठा hci_request *req, u8 instance,
				    bool क्रमce)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा adv_info *adv_instance = शून्य;
	u16 समयout;

	अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
	    list_empty(&hdev->adv_instances))
		वापस -EPERM;

	अगर (hdev->adv_instance_समयout)
		वापस -EBUSY;

	adv_instance = hci_find_adv_instance(hdev, instance);
	अगर (!adv_instance)
		वापस -ENOENT;

	/* A zero समयout means unlimited advertising. As दीर्घ as there is
	 * only one instance, duration should be ignored. We still set a समयout
	 * in हाल further instances are being added later on.
	 *
	 * If the reमुख्यing lअगरeसमय of the instance is more than the duration
	 * then the समयout corresponds to the duration, otherwise it will be
	 * reduced to the reमुख्यing instance lअगरeसमय.
	 */
	अगर (adv_instance->समयout == 0 ||
	    adv_instance->duration <= adv_instance->reमुख्यing_समय)
		समयout = adv_instance->duration;
	अन्यथा
		समयout = adv_instance->reमुख्यing_समय;

	/* The reमुख्यing समय is being reduced unless the instance is being
	 * advertised without समय limit.
	 */
	अगर (adv_instance->समयout)
		adv_instance->reमुख्यing_समय =
				adv_instance->reमुख्यing_समय - समयout;

	/* Only use work क्रम scheduling instances with legacy advertising */
	अगर (!ext_adv_capable(hdev)) अणु
		hdev->adv_instance_समयout = समयout;
		queue_delayed_work(hdev->req_workqueue,
			   &hdev->adv_instance_expire,
			   msecs_to_jअगरfies(समयout * 1000));
	पूर्ण

	/* If we're just re-scheduling the same instance again then करो not
	 * execute any HCI commands. This happens when a single instance is
	 * being advertised.
	 */
	अगर (!क्रमce && hdev->cur_adv_instance == instance &&
	    hci_dev_test_flag(hdev, HCI_LE_ADV))
		वापस 0;

	hdev->cur_adv_instance = instance;
	अगर (ext_adv_capable(hdev)) अणु
		__hci_req_start_ext_adv(req, instance);
	पूर्ण अन्यथा अणु
		__hci_req_update_adv_data(req, instance);
		__hci_req_update_scan_rsp_data(req, instance);
		__hci_req_enable_advertising(req);
	पूर्ण

	वापस 0;
पूर्ण

/* For a single instance:
 * - क्रमce == true: The instance will be हटाओd even when its reमुख्यing
 *   lअगरeसमय is not zero.
 * - क्रमce == false: the instance will be deactivated but kept stored unless
 *   the reमुख्यing lअगरeसमय is zero.
 *
 * For instance == 0x00:
 * - क्रमce == true: All instances will be हटाओd regardless of their समयout
 *   setting.
 * - क्रमce == false: Only instances that have a समयout will be हटाओd.
 */
व्योम hci_req_clear_adv_instance(काष्ठा hci_dev *hdev, काष्ठा sock *sk,
				काष्ठा hci_request *req, u8 instance,
				bool क्रमce)
अणु
	काष्ठा adv_info *adv_instance, *n, *next_instance = शून्य;
	पूर्णांक err;
	u8 rem_inst;

	/* Cancel any समयout concerning the हटाओd instance(s). */
	अगर (!instance || hdev->cur_adv_instance == instance)
		cancel_adv_समयout(hdev);

	/* Get the next instance to advertise BEFORE we हटाओ
	 * the current one. This can be the same instance again
	 * अगर there is only one instance.
	 */
	अगर (instance && hdev->cur_adv_instance == instance)
		next_instance = hci_get_next_instance(hdev, instance);

	अगर (instance == 0x00) अणु
		list_क्रम_each_entry_safe(adv_instance, n, &hdev->adv_instances,
					 list) अणु
			अगर (!(क्रमce || adv_instance->समयout))
				जारी;

			rem_inst = adv_instance->instance;
			err = hci_हटाओ_adv_instance(hdev, rem_inst);
			अगर (!err)
				mgmt_advertising_हटाओd(sk, hdev, rem_inst);
		पूर्ण
	पूर्ण अन्यथा अणु
		adv_instance = hci_find_adv_instance(hdev, instance);

		अगर (क्रमce || (adv_instance && adv_instance->समयout &&
			      !adv_instance->reमुख्यing_समय)) अणु
			/* Don't advertise a हटाओd instance. */
			अगर (next_instance &&
			    next_instance->instance == instance)
				next_instance = शून्य;

			err = hci_हटाओ_adv_instance(hdev, instance);
			अगर (!err)
				mgmt_advertising_हटाओd(sk, hdev, instance);
		पूर्ण
	पूर्ण

	अगर (!req || !hdev_is_घातered(hdev) ||
	    hci_dev_test_flag(hdev, HCI_ADVERTISING))
		वापस;

	अगर (next_instance && !ext_adv_capable(hdev))
		__hci_req_schedule_adv_instance(req, next_instance->instance,
						false);
पूर्ण

अटल व्योम set_अक्रमom_addr(काष्ठा hci_request *req, bdaddr_t *rpa)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	/* If we're advertising or initiating an LE connection we can't
	 * go ahead and change the अक्रमom address at this समय. This is
	 * because the eventual initiator address used क्रम the
	 * subsequently created connection will be undefined (some
	 * controllers use the new address and others the one we had
	 * when the operation started).
	 *
	 * In this kind of scenario skip the update and let the अक्रमom
	 * address be updated at the next cycle.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_LE_ADV) ||
	    hci_lookup_le_connect(hdev)) अणु
		bt_dev_dbg(hdev, "Deferring random address update");
		hci_dev_set_flag(hdev, HCI_RPA_EXPIRED);
		वापस;
	पूर्ण

	hci_req_add(req, HCI_OP_LE_SET_RANDOM_ADDR, 6, rpa);
पूर्ण

पूर्णांक hci_update_अक्रमom_address(काष्ठा hci_request *req, bool require_privacy,
			      bool use_rpa, u8 *own_addr_type)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	पूर्णांक err;

	/* If privacy is enabled use a resolvable निजी address. If
	 * current RPA has expired or there is something अन्यथा than
	 * the current RPA in use, then generate a new one.
	 */
	अगर (use_rpa) अणु
		पूर्णांक to;

		/* If Controller supports LL Privacy use own address type is
		 * 0x03
		 */
		अगर (use_ll_privacy(hdev) &&
		    hci_dev_test_flag(hdev, HCI_ENABLE_LL_PRIVACY))
			*own_addr_type = ADDR_LE_DEV_RANDOM_RESOLVED;
		अन्यथा
			*own_addr_type = ADDR_LE_DEV_RANDOM;

		अगर (!hci_dev_test_and_clear_flag(hdev, HCI_RPA_EXPIRED) &&
		    !bacmp(&hdev->अक्रमom_addr, &hdev->rpa))
			वापस 0;

		err = smp_generate_rpa(hdev, hdev->irk, &hdev->rpa);
		अगर (err < 0) अणु
			bt_dev_err(hdev, "failed to generate new RPA");
			वापस err;
		पूर्ण

		set_अक्रमom_addr(req, &hdev->rpa);

		to = msecs_to_jअगरfies(hdev->rpa_समयout * 1000);
		queue_delayed_work(hdev->workqueue, &hdev->rpa_expired, to);

		वापस 0;
	पूर्ण

	/* In हाल of required privacy without resolvable निजी address,
	 * use an non-resolvable निजी address. This is useful क्रम active
	 * scanning and non-connectable advertising.
	 */
	अगर (require_privacy) अणु
		bdaddr_t nrpa;

		जबतक (true) अणु
			/* The non-resolvable निजी address is generated
			 * from अक्रमom six bytes with the two most signअगरicant
			 * bits cleared.
			 */
			get_अक्रमom_bytes(&nrpa, 6);
			nrpa.b[5] &= 0x3f;

			/* The non-resolvable निजी address shall not be
			 * equal to the खुला address.
			 */
			अगर (bacmp(&hdev->bdaddr, &nrpa))
				अवरोध;
		पूर्ण

		*own_addr_type = ADDR_LE_DEV_RANDOM;
		set_अक्रमom_addr(req, &nrpa);
		वापस 0;
	पूर्ण

	/* If क्रमcing अटल address is in use or there is no खुला
	 * address use the अटल address as अक्रमom address (but skip
	 * the HCI command अगर the current अक्रमom address is alपढ़ोy the
	 * अटल one.
	 *
	 * In हाल BR/EDR has been disabled on a dual-mode controller
	 * and a अटल address has been configured, then use that
	 * address instead of the खुला BR/EDR address.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_FORCE_STATIC_ADDR) ||
	    !bacmp(&hdev->bdaddr, BDADDR_ANY) ||
	    (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) &&
	     bacmp(&hdev->अटल_addr, BDADDR_ANY))) अणु
		*own_addr_type = ADDR_LE_DEV_RANDOM;
		अगर (bacmp(&hdev->अटल_addr, &hdev->अक्रमom_addr))
			hci_req_add(req, HCI_OP_LE_SET_RANDOM_ADDR, 6,
				    &hdev->अटल_addr);
		वापस 0;
	पूर्ण

	/* Neither privacy nor अटल address is being used so use a
	 * खुला address.
	 */
	*own_addr_type = ADDR_LE_DEV_PUBLIC;

	वापस 0;
पूर्ण

अटल bool disconnected_whitelist_entries(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bdaddr_list *b;

	list_क्रम_each_entry(b, &hdev->whitelist, list) अणु
		काष्ठा hci_conn *conn;

		conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &b->bdaddr);
		अगर (!conn)
			वापस true;

		अगर (conn->state != BT_CONNECTED && conn->state != BT_CONFIG)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम __hci_req_update_scan(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 scan;

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		वापस;

	अगर (!hdev_is_घातered(hdev))
		वापस;

	अगर (mgmt_घातering_करोwn(hdev))
		वापस;

	अगर (hdev->scanning_छोड़ोd)
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_CONNECTABLE) ||
	    disconnected_whitelist_entries(hdev))
		scan = SCAN_PAGE;
	अन्यथा
		scan = SCAN_DISABLED;

	अगर (hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
		scan |= SCAN_INQUIRY;

	अगर (test_bit(HCI_PSCAN, &hdev->flags) == !!(scan & SCAN_PAGE) &&
	    test_bit(HCI_ISCAN, &hdev->flags) == !!(scan & SCAN_INQUIRY))
		वापस;

	hci_req_add(req, HCI_OP_WRITE_SCAN_ENABLE, 1, &scan);
पूर्ण

अटल पूर्णांक update_scan(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	hci_dev_lock(req->hdev);
	__hci_req_update_scan(req);
	hci_dev_unlock(req->hdev);
	वापस 0;
पूर्ण

अटल व्योम scan_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev, scan_update);

	hci_req_sync(hdev, update_scan, 0, HCI_CMD_TIMEOUT, शून्य);
पूर्ण

अटल पूर्णांक connectable_update(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	hci_dev_lock(hdev);

	__hci_req_update_scan(req);

	/* If BR/EDR is not enabled and we disable advertising as a
	 * by-product of disabling connectable, we need to update the
	 * advertising flags.
	 */
	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		__hci_req_update_adv_data(req, hdev->cur_adv_instance);

	/* Update the advertising parameters अगर necessary */
	अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
	    !list_empty(&hdev->adv_instances)) अणु
		अगर (ext_adv_capable(hdev))
			__hci_req_start_ext_adv(req, hdev->cur_adv_instance);
		अन्यथा
			__hci_req_enable_advertising(req);
	पूर्ण

	__hci_update_background_scan(req);

	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल व्योम connectable_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    connectable_update);
	u8 status;

	hci_req_sync(hdev, connectable_update, 0, HCI_CMD_TIMEOUT, &status);
	mgmt_set_connectable_complete(hdev, status);
पूर्ण

अटल u8 get_service_classes(काष्ठा hci_dev *hdev)
अणु
	काष्ठा bt_uuid *uuid;
	u8 val = 0;

	list_क्रम_each_entry(uuid, &hdev->uuids, list)
		val |= uuid->svc_hपूर्णांक;

	वापस val;
पूर्ण

व्योम __hci_req_update_class(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 cod[3];

	bt_dev_dbg(hdev, "");

	अगर (!hdev_is_घातered(hdev))
		वापस;

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_SERVICE_CACHE))
		वापस;

	cod[0] = hdev->minor_class;
	cod[1] = hdev->major_class;
	cod[2] = get_service_classes(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_LIMITED_DISCOVERABLE))
		cod[1] |= 0x20;

	अगर (स_भेद(cod, hdev->dev_class, 3) == 0)
		वापस;

	hci_req_add(req, HCI_OP_WRITE_CLASS_OF_DEV, माप(cod), cod);
पूर्ण

अटल व्योम ग_लिखो_iac(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा hci_cp_ग_लिखो_current_iac_lap cp;

	अगर (!hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
		वापस;

	अगर (hci_dev_test_flag(hdev, HCI_LIMITED_DISCOVERABLE)) अणु
		/* Limited discoverable mode */
		cp.num_iac = min_t(u8, hdev->num_iac, 2);
		cp.iac_lap[0] = 0x00;	/* LIAC */
		cp.iac_lap[1] = 0x8b;
		cp.iac_lap[2] = 0x9e;
		cp.iac_lap[3] = 0x33;	/* GIAC */
		cp.iac_lap[4] = 0x8b;
		cp.iac_lap[5] = 0x9e;
	पूर्ण अन्यथा अणु
		/* General discoverable mode */
		cp.num_iac = 1;
		cp.iac_lap[0] = 0x33;	/* GIAC */
		cp.iac_lap[1] = 0x8b;
		cp.iac_lap[2] = 0x9e;
	पूर्ण

	hci_req_add(req, HCI_OP_WRITE_CURRENT_IAC_LAP,
		    (cp.num_iac * 3) + 1, &cp);
पूर्ण

अटल पूर्णांक discoverable_update(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) अणु
		ग_लिखो_iac(req);
		__hci_req_update_scan(req);
		__hci_req_update_class(req);
	पूर्ण

	/* Advertising instances करोn't use the global discoverable setting, so
	 * only update AD अगर advertising was enabled using Set Advertising.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING)) अणु
		__hci_req_update_adv_data(req, 0x00);

		/* Discoverable mode affects the local advertising
		 * address in limited privacy mode.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_LIMITED_PRIVACY)) अणु
			अगर (ext_adv_capable(hdev))
				__hci_req_start_ext_adv(req, 0x00);
			अन्यथा
				__hci_req_enable_advertising(req);
		पूर्ण
	पूर्ण

	hci_dev_unlock(hdev);

	वापस 0;
पूर्ण

अटल व्योम discoverable_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    discoverable_update);
	u8 status;

	hci_req_sync(hdev, discoverable_update, 0, HCI_CMD_TIMEOUT, &status);
	mgmt_set_discoverable_complete(hdev, status);
पूर्ण

व्योम __hci_पात_conn(काष्ठा hci_request *req, काष्ठा hci_conn *conn,
		      u8 reason)
अणु
	चयन (conn->state) अणु
	हाल BT_CONNECTED:
	हाल BT_CONFIG:
		अगर (conn->type == AMP_LINK) अणु
			काष्ठा hci_cp_disconn_phy_link cp;

			cp.phy_handle = HCI_PHY_HANDLE(conn->handle);
			cp.reason = reason;
			hci_req_add(req, HCI_OP_DISCONN_PHY_LINK, माप(cp),
				    &cp);
		पूर्ण अन्यथा अणु
			काष्ठा hci_cp_disconnect dc;

			dc.handle = cpu_to_le16(conn->handle);
			dc.reason = reason;
			hci_req_add(req, HCI_OP_DISCONNECT, माप(dc), &dc);
		पूर्ण

		conn->state = BT_DISCONN;

		अवरोध;
	हाल BT_CONNECT:
		अगर (conn->type == LE_LINK) अणु
			अगर (test_bit(HCI_CONN_SCANNING, &conn->flags))
				अवरोध;
			hci_req_add(req, HCI_OP_LE_CREATE_CONN_CANCEL,
				    0, शून्य);
		पूर्ण अन्यथा अगर (conn->type == ACL_LINK) अणु
			अगर (req->hdev->hci_ver < BLUETOOTH_VER_1_2)
				अवरोध;
			hci_req_add(req, HCI_OP_CREATE_CONN_CANCEL,
				    6, &conn->dst);
		पूर्ण
		अवरोध;
	हाल BT_CONNECT2:
		अगर (conn->type == ACL_LINK) अणु
			काष्ठा hci_cp_reject_conn_req rej;

			bacpy(&rej.bdaddr, &conn->dst);
			rej.reason = reason;

			hci_req_add(req, HCI_OP_REJECT_CONN_REQ,
				    माप(rej), &rej);
		पूर्ण अन्यथा अगर (conn->type == SCO_LINK || conn->type == ESCO_LINK) अणु
			काष्ठा hci_cp_reject_sync_conn_req rej;

			bacpy(&rej.bdaddr, &conn->dst);

			/* SCO rejection has its own limited set of
			 * allowed error values (0x0D-0x0F) which isn't
			 * compatible with most values passed to this
			 * function. To be safe hard-code one of the
			 * values that's suitable क्रम SCO.
			 */
			rej.reason = HCI_ERROR_REJ_LIMITED_RESOURCES;

			hci_req_add(req, HCI_OP_REJECT_SYNC_CONN_REQ,
				    माप(rej), &rej);
		पूर्ण
		अवरोध;
	शेष:
		conn->state = BT_CLOSED;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम पात_conn_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	अगर (status)
		bt_dev_dbg(hdev, "Failed to abort connection: status 0x%2.2x", status);
पूर्ण

पूर्णांक hci_पात_conn(काष्ठा hci_conn *conn, u8 reason)
अणु
	काष्ठा hci_request req;
	पूर्णांक err;

	hci_req_init(&req, conn->hdev);

	__hci_पात_conn(&req, conn, reason);

	err = hci_req_run(&req, पात_conn_complete);
	अगर (err && err != -ENODATA) अणु
		bt_dev_err(conn->hdev, "failed to run HCI request: err %d", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक update_bg_scan(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	hci_dev_lock(req->hdev);
	__hci_update_background_scan(req);
	hci_dev_unlock(req->hdev);
	वापस 0;
पूर्ण

अटल व्योम bg_scan_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    bg_scan_update);
	काष्ठा hci_conn *conn;
	u8 status;
	पूर्णांक err;

	err = hci_req_sync(hdev, update_bg_scan, 0, HCI_CMD_TIMEOUT, &status);
	अगर (!err)
		वापस;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_state(hdev, LE_LINK, BT_CONNECT);
	अगर (conn)
		hci_le_conn_failed(conn, status);

	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक le_scan_disable(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	hci_req_add_le_scan_disable(req, false);
	वापस 0;
पूर्ण

अटल पूर्णांक bredr_inquiry(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	u8 length = opt;
	स्थिर u8 giac[3] = अणु 0x33, 0x8b, 0x9e पूर्ण;
	स्थिर u8 liac[3] = अणु 0x00, 0x8b, 0x9e पूर्ण;
	काष्ठा hci_cp_inquiry cp;

	अगर (test_bit(HCI_INQUIRY, &req->hdev->flags))
		वापस 0;

	bt_dev_dbg(req->hdev, "");

	hci_dev_lock(req->hdev);
	hci_inquiry_cache_flush(req->hdev);
	hci_dev_unlock(req->hdev);

	स_रखो(&cp, 0, माप(cp));

	अगर (req->hdev->discovery.limited)
		स_नकल(&cp.lap, liac, माप(cp.lap));
	अन्यथा
		स_नकल(&cp.lap, giac, माप(cp.lap));

	cp.length = length;

	hci_req_add(req, HCI_OP_INQUIRY, माप(cp), &cp);

	वापस 0;
पूर्ण

अटल व्योम le_scan_disable_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    le_scan_disable.work);
	u8 status;

	bt_dev_dbg(hdev, "");

	अगर (!hci_dev_test_flag(hdev, HCI_LE_SCAN))
		वापस;

	cancel_delayed_work(&hdev->le_scan_restart);

	hci_req_sync(hdev, le_scan_disable, 0, HCI_CMD_TIMEOUT, &status);
	अगर (status) अणु
		bt_dev_err(hdev, "failed to disable LE scan: status 0x%02x",
			   status);
		वापस;
	पूर्ण

	hdev->discovery.scan_start = 0;

	/* If we were running LE only scan, change discovery state. If
	 * we were running both LE and BR/EDR inquiry simultaneously,
	 * and BR/EDR inquiry is alपढ़ोy finished, stop discovery,
	 * otherwise BR/EDR inquiry will stop discovery when finished.
	 * If we will resolve remote device name, करो not change
	 * discovery state.
	 */

	अगर (hdev->discovery.type == DISCOV_TYPE_LE)
		जाओ discov_stopped;

	अगर (hdev->discovery.type != DISCOV_TYPE_INTERLEAVED)
		वापस;

	अगर (test_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks)) अणु
		अगर (!test_bit(HCI_INQUIRY, &hdev->flags) &&
		    hdev->discovery.state != DISCOVERY_RESOLVING)
			जाओ discov_stopped;

		वापस;
	पूर्ण

	hci_req_sync(hdev, bredr_inquiry, DISCOV_INTERLEAVED_INQUIRY_LEN,
		     HCI_CMD_TIMEOUT, &status);
	अगर (status) अणु
		bt_dev_err(hdev, "inquiry failed: status 0x%02x", status);
		जाओ discov_stopped;
	पूर्ण

	वापस;

discov_stopped:
	hci_dev_lock(hdev);
	hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक le_scan_restart(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;

	/* If controller is not scanning we are करोne. */
	अगर (!hci_dev_test_flag(hdev, HCI_LE_SCAN))
		वापस 0;

	अगर (hdev->scanning_छोड़ोd) अणु
		bt_dev_dbg(hdev, "Scanning is paused for suspend");
		वापस 0;
	पूर्ण

	hci_req_add_le_scan_disable(req, false);

	अगर (use_ext_scan(hdev)) अणु
		काष्ठा hci_cp_le_set_ext_scan_enable ext_enable_cp;

		स_रखो(&ext_enable_cp, 0, माप(ext_enable_cp));
		ext_enable_cp.enable = LE_SCAN_ENABLE;
		ext_enable_cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;

		hci_req_add(req, HCI_OP_LE_SET_EXT_SCAN_ENABLE,
			    माप(ext_enable_cp), &ext_enable_cp);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_le_set_scan_enable cp;

		स_रखो(&cp, 0, माप(cp));
		cp.enable = LE_SCAN_ENABLE;
		cp.filter_dup = LE_SCAN_FILTER_DUP_ENABLE;
		hci_req_add(req, HCI_OP_LE_SET_SCAN_ENABLE, माप(cp), &cp);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम le_scan_restart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    le_scan_restart.work);
	अचिन्हित दीर्घ समयout, duration, scan_start, now;
	u8 status;

	bt_dev_dbg(hdev, "");

	hci_req_sync(hdev, le_scan_restart, 0, HCI_CMD_TIMEOUT, &status);
	अगर (status) अणु
		bt_dev_err(hdev, "failed to restart LE scan: status %d",
			   status);
		वापस;
	पूर्ण

	hci_dev_lock(hdev);

	अगर (!test_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks) ||
	    !hdev->discovery.scan_start)
		जाओ unlock;

	/* When the scan was started, hdev->le_scan_disable has been queued
	 * after duration from scan_start. During scan restart this job
	 * has been canceled, and we need to queue it again after proper
	 * समयout, to make sure that scan करोes not run indefinitely.
	 */
	duration = hdev->discovery.scan_duration;
	scan_start = hdev->discovery.scan_start;
	now = jअगरfies;
	अगर (now - scan_start <= duration) अणु
		पूर्णांक elapsed;

		अगर (now >= scan_start)
			elapsed = now - scan_start;
		अन्यथा
			elapsed = अच_दीर्घ_उच्च - scan_start + now;

		समयout = duration - elapsed;
	पूर्ण अन्यथा अणु
		समयout = 0;
	पूर्ण

	queue_delayed_work(hdev->req_workqueue,
			   &hdev->le_scan_disable, समयout);

unlock:
	hci_dev_unlock(hdev);
पूर्ण

अटल पूर्णांक active_scan(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	uपूर्णांक16_t पूर्णांकerval = opt;
	काष्ठा hci_dev *hdev = req->hdev;
	u8 own_addr_type;
	/* White list is not used क्रम discovery */
	u8 filter_policy = 0x00;
	/* Discovery करोesn't require controller address resolution */
	bool addr_resolv = false;
	पूर्णांक err;

	bt_dev_dbg(hdev, "");

	/* If controller is scanning, it means the background scanning is
	 * running. Thus, we should temporarily stop it in order to set the
	 * discovery scanning parameters.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN)) अणु
		hci_req_add_le_scan_disable(req, false);
		cancel_पूर्णांकerleave_scan(hdev);
	पूर्ण

	/* All active scans will be करोne with either a resolvable निजी
	 * address (when privacy feature has been enabled) or non-resolvable
	 * निजी address.
	 */
	err = hci_update_अक्रमom_address(req, true, scan_use_rpa(hdev),
					&own_addr_type);
	अगर (err < 0)
		own_addr_type = ADDR_LE_DEV_PUBLIC;

	hci_req_start_scan(req, LE_SCAN_ACTIVE, पूर्णांकerval,
			   hdev->le_scan_winकरोw_discovery, own_addr_type,
			   filter_policy, addr_resolv);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकerleaved_discov(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	पूर्णांक err;

	bt_dev_dbg(req->hdev, "");

	err = active_scan(req, opt);
	अगर (err)
		वापस err;

	वापस bredr_inquiry(req, DISCOV_BREDR_INQUIRY_LEN);
पूर्ण

अटल व्योम start_discovery(काष्ठा hci_dev *hdev, u8 *status)
अणु
	अचिन्हित दीर्घ समयout;

	bt_dev_dbg(hdev, "type %u", hdev->discovery.type);

	चयन (hdev->discovery.type) अणु
	हाल DISCOV_TYPE_BREDR:
		अगर (!hci_dev_test_flag(hdev, HCI_INQUIRY))
			hci_req_sync(hdev, bredr_inquiry,
				     DISCOV_BREDR_INQUIRY_LEN, HCI_CMD_TIMEOUT,
				     status);
		वापस;
	हाल DISCOV_TYPE_INTERLEAVED:
		/* When running simultaneous discovery, the LE scanning समय
		 * should occupy the whole discovery समय sine BR/EDR inquiry
		 * and LE scanning are scheduled by the controller.
		 *
		 * For पूर्णांकerleaving discovery in comparison, BR/EDR inquiry
		 * and LE scanning are करोne sequentially with separate
		 * समयouts.
		 */
		अगर (test_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY,
			     &hdev->quirks)) अणु
			समयout = msecs_to_jअगरfies(DISCOV_LE_TIMEOUT);
			/* During simultaneous discovery, we द्विगुन LE scan
			 * पूर्णांकerval. We must leave some समय क्रम the controller
			 * to करो BR/EDR inquiry.
			 */
			hci_req_sync(hdev, पूर्णांकerleaved_discov,
				     hdev->le_scan_पूर्णांक_discovery * 2, HCI_CMD_TIMEOUT,
				     status);
			अवरोध;
		पूर्ण

		समयout = msecs_to_jअगरfies(hdev->discov_पूर्णांकerleaved_समयout);
		hci_req_sync(hdev, active_scan, hdev->le_scan_पूर्णांक_discovery,
			     HCI_CMD_TIMEOUT, status);
		अवरोध;
	हाल DISCOV_TYPE_LE:
		समयout = msecs_to_jअगरfies(DISCOV_LE_TIMEOUT);
		hci_req_sync(hdev, active_scan, hdev->le_scan_पूर्णांक_discovery,
			     HCI_CMD_TIMEOUT, status);
		अवरोध;
	शेष:
		*status = HCI_ERROR_UNSPECIFIED;
		वापस;
	पूर्ण

	अगर (*status)
		वापस;

	bt_dev_dbg(hdev, "timeout %u ms", jअगरfies_to_msecs(समयout));

	/* When service discovery is used and the controller has a
	 * strict duplicate filter, it is important to remember the
	 * start and duration of the scan. This is required क्रम
	 * restarting scanning during the discovery phase.
	 */
	अगर (test_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks) &&
		     hdev->discovery.result_filtering) अणु
		hdev->discovery.scan_start = jअगरfies;
		hdev->discovery.scan_duration = समयout;
	पूर्ण

	queue_delayed_work(hdev->req_workqueue, &hdev->le_scan_disable,
			   समयout);
पूर्ण

bool hci_req_stop_discovery(काष्ठा hci_request *req)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	काष्ठा discovery_state *d = &hdev->discovery;
	काष्ठा hci_cp_remote_name_req_cancel cp;
	काष्ठा inquiry_entry *e;
	bool ret = false;

	bt_dev_dbg(hdev, "state %u", hdev->discovery.state);

	अगर (d->state == DISCOVERY_FINDING || d->state == DISCOVERY_STOPPING) अणु
		अगर (test_bit(HCI_INQUIRY, &hdev->flags))
			hci_req_add(req, HCI_OP_INQUIRY_CANCEL, 0, शून्य);

		अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN)) अणु
			cancel_delayed_work(&hdev->le_scan_disable);
			cancel_delayed_work(&hdev->le_scan_restart);
			hci_req_add_le_scan_disable(req, false);
		पूर्ण

		ret = true;
	पूर्ण अन्यथा अणु
		/* Passive scanning */
		अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN)) अणु
			hci_req_add_le_scan_disable(req, false);
			ret = true;
		पूर्ण
	पूर्ण

	/* No further actions needed क्रम LE-only discovery */
	अगर (d->type == DISCOV_TYPE_LE)
		वापस ret;

	अगर (d->state == DISCOVERY_RESOLVING || d->state == DISCOVERY_STOPPING) अणु
		e = hci_inquiry_cache_lookup_resolve(hdev, BDADDR_ANY,
						     NAME_PENDING);
		अगर (!e)
			वापस ret;

		bacpy(&cp.bdaddr, &e->data.bdaddr);
		hci_req_add(req, HCI_OP_REMOTE_NAME_REQ_CANCEL, माप(cp),
			    &cp);
		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक stop_discovery(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	hci_dev_lock(req->hdev);
	hci_req_stop_discovery(req);
	hci_dev_unlock(req->hdev);

	वापस 0;
पूर्ण

अटल व्योम discov_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    discov_update);
	u8 status = 0;

	चयन (hdev->discovery.state) अणु
	हाल DISCOVERY_STARTING:
		start_discovery(hdev, &status);
		mgmt_start_discovery_complete(hdev, status);
		अगर (status)
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
		अन्यथा
			hci_discovery_set_state(hdev, DISCOVERY_FINDING);
		अवरोध;
	हाल DISCOVERY_STOPPING:
		hci_req_sync(hdev, stop_discovery, 0, HCI_CMD_TIMEOUT, &status);
		mgmt_stop_discovery_complete(hdev, status);
		अगर (!status)
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
		अवरोध;
	हाल DISCOVERY_STOPPED:
	शेष:
		वापस;
	पूर्ण
पूर्ण

अटल व्योम discov_off(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_dev *hdev = container_of(work, काष्ठा hci_dev,
					    discov_off.work);

	bt_dev_dbg(hdev, "");

	hci_dev_lock(hdev);

	/* When discoverable समयout triggers, then just make sure
	 * the limited discoverable flag is cleared. Even in the हाल
	 * of a समयout triggered from general discoverable, it is
	 * safe to unconditionally clear the flag.
	 */
	hci_dev_clear_flag(hdev, HCI_LIMITED_DISCOVERABLE);
	hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);
	hdev->discov_समयout = 0;

	hci_dev_unlock(hdev);

	hci_req_sync(hdev, discoverable_update, 0, HCI_CMD_TIMEOUT, शून्य);
	mgmt_new_settings(hdev);
पूर्ण

अटल पूर्णांक घातered_update_hci(काष्ठा hci_request *req, अचिन्हित दीर्घ opt)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 link_sec;

	hci_dev_lock(hdev);

	अगर (hci_dev_test_flag(hdev, HCI_SSP_ENABLED) &&
	    !lmp_host_ssp_capable(hdev)) अणु
		u8 mode = 0x01;

		hci_req_add(req, HCI_OP_WRITE_SSP_MODE, माप(mode), &mode);

		अगर (bredr_sc_enabled(hdev) && !lmp_host_sc_capable(hdev)) अणु
			u8 support = 0x01;

			hci_req_add(req, HCI_OP_WRITE_SC_SUPPORT,
				    माप(support), &support);
		पूर्ण
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_LE_ENABLED) &&
	    lmp_bredr_capable(hdev)) अणु
		काष्ठा hci_cp_ग_लिखो_le_host_supported cp;

		cp.le = 0x01;
		cp.simul = 0x00;

		/* Check first अगर we alपढ़ोy have the right
		 * host state (host features set)
		 */
		अगर (cp.le != lmp_host_le_capable(hdev) ||
		    cp.simul != lmp_host_le_br_capable(hdev))
			hci_req_add(req, HCI_OP_WRITE_LE_HOST_SUPPORTED,
				    माप(cp), &cp);
	पूर्ण

	अगर (hci_dev_test_flag(hdev, HCI_LE_ENABLED)) अणु
		/* Make sure the controller has a good शेष क्रम
		 * advertising data. This also applies to the हाल
		 * where BR/EDR was toggled during the AUTO_OFF phase.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
		    list_empty(&hdev->adv_instances)) अणु
			पूर्णांक err;

			अगर (ext_adv_capable(hdev)) अणु
				err = __hci_req_setup_ext_adv_instance(req,
								       0x00);
				अगर (!err)
					__hci_req_update_scan_rsp_data(req,
								       0x00);
			पूर्ण अन्यथा अणु
				err = 0;
				__hci_req_update_adv_data(req, 0x00);
				__hci_req_update_scan_rsp_data(req, 0x00);
			पूर्ण

			अगर (hci_dev_test_flag(hdev, HCI_ADVERTISING)) अणु
				अगर (!ext_adv_capable(hdev))
					__hci_req_enable_advertising(req);
				अन्यथा अगर (!err)
					__hci_req_enable_ext_advertising(req,
									 0x00);
			पूर्ण
		पूर्ण अन्यथा अगर (!list_empty(&hdev->adv_instances)) अणु
			काष्ठा adv_info *adv_instance;

			adv_instance = list_first_entry(&hdev->adv_instances,
							काष्ठा adv_info, list);
			__hci_req_schedule_adv_instance(req,
							adv_instance->instance,
							true);
		पूर्ण
	पूर्ण

	link_sec = hci_dev_test_flag(hdev, HCI_LINK_SECURITY);
	अगर (link_sec != test_bit(HCI_AUTH, &hdev->flags))
		hci_req_add(req, HCI_OP_WRITE_AUTH_ENABLE,
			    माप(link_sec), &link_sec);

	अगर (lmp_bredr_capable(hdev)) अणु
		अगर (hci_dev_test_flag(hdev, HCI_FAST_CONNECTABLE))
			__hci_req_ग_लिखो_fast_connectable(req, true);
		अन्यथा
			__hci_req_ग_लिखो_fast_connectable(req, false);
		__hci_req_update_scan(req);
		__hci_req_update_class(req);
		__hci_req_update_name(req);
		__hci_req_update_eir(req);
	पूर्ण

	hci_dev_unlock(hdev);
	वापस 0;
पूर्ण

पूर्णांक __hci_req_hci_घातer_on(काष्ठा hci_dev *hdev)
अणु
	/* Register the available SMP channels (BR/EDR and LE) only when
	 * successfully घातering on the controller. This late
	 * registration is required so that LE SMP can clearly decide अगर
	 * the खुला address or अटल address is used.
	 */
	smp_रेजिस्टर(hdev);

	वापस __hci_req_sync(hdev, घातered_update_hci, 0, HCI_CMD_TIMEOUT,
			      शून्य);
पूर्ण

व्योम hci_request_setup(काष्ठा hci_dev *hdev)
अणु
	INIT_WORK(&hdev->discov_update, discov_update);
	INIT_WORK(&hdev->bg_scan_update, bg_scan_update);
	INIT_WORK(&hdev->scan_update, scan_update_work);
	INIT_WORK(&hdev->connectable_update, connectable_update_work);
	INIT_WORK(&hdev->discoverable_update, discoverable_update_work);
	INIT_DELAYED_WORK(&hdev->discov_off, discov_off);
	INIT_DELAYED_WORK(&hdev->le_scan_disable, le_scan_disable_work);
	INIT_DELAYED_WORK(&hdev->le_scan_restart, le_scan_restart_work);
	INIT_DELAYED_WORK(&hdev->adv_instance_expire, adv_समयout_expire);
	INIT_DELAYED_WORK(&hdev->पूर्णांकerleave_scan, पूर्णांकerleave_scan_work);
पूर्ण

व्योम hci_request_cancel_all(काष्ठा hci_dev *hdev)
अणु
	hci_req_sync_cancel(hdev, ENODEV);

	cancel_work_sync(&hdev->discov_update);
	cancel_work_sync(&hdev->bg_scan_update);
	cancel_work_sync(&hdev->scan_update);
	cancel_work_sync(&hdev->connectable_update);
	cancel_work_sync(&hdev->discoverable_update);
	cancel_delayed_work_sync(&hdev->discov_off);
	cancel_delayed_work_sync(&hdev->le_scan_disable);
	cancel_delayed_work_sync(&hdev->le_scan_restart);

	अगर (hdev->adv_instance_समयout) अणु
		cancel_delayed_work_sync(&hdev->adv_instance_expire);
		hdev->adv_instance_समयout = 0;
	पूर्ण

	cancel_पूर्णांकerleave_scan(hdev);
पूर्ण
