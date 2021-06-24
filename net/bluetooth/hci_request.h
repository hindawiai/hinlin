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

#समावेश <यंत्र/unaligned.h>

#घोषणा hci_req_sync_lock(hdev)   mutex_lock(&hdev->req_lock)
#घोषणा hci_req_sync_unlock(hdev) mutex_unlock(&hdev->req_lock)

काष्ठा hci_request अणु
	काष्ठा hci_dev		*hdev;
	काष्ठा sk_buff_head	cmd_q;

	/* If something goes wrong when building the HCI request, the error
	 * value is stored in this field.
	 */
	पूर्णांक			err;
पूर्ण;

व्योम hci_req_init(काष्ठा hci_request *req, काष्ठा hci_dev *hdev);
व्योम hci_req_purge(काष्ठा hci_request *req);
bool hci_req_status_pend(काष्ठा hci_dev *hdev);
पूर्णांक hci_req_run(काष्ठा hci_request *req, hci_req_complete_t complete);
पूर्णांक hci_req_run_skb(काष्ठा hci_request *req, hci_req_complete_skb_t complete);
व्योम hci_req_add(काष्ठा hci_request *req, u16 opcode, u32 plen,
		 स्थिर व्योम *param);
व्योम hci_req_add_ev(काष्ठा hci_request *req, u16 opcode, u32 plen,
		    स्थिर व्योम *param, u8 event);
व्योम hci_req_cmd_complete(काष्ठा hci_dev *hdev, u16 opcode, u8 status,
			  hci_req_complete_t *req_complete,
			  hci_req_complete_skb_t *req_complete_skb);

पूर्णांक hci_req_sync(काष्ठा hci_dev *hdev, पूर्णांक (*req)(काष्ठा hci_request *req,
						  अचिन्हित दीर्घ opt),
		 अचिन्हित दीर्घ opt, u32 समयout, u8 *hci_status);
पूर्णांक __hci_req_sync(काष्ठा hci_dev *hdev, पूर्णांक (*func)(काष्ठा hci_request *req,
						     अचिन्हित दीर्घ opt),
		   अचिन्हित दीर्घ opt, u32 समयout, u8 *hci_status);
व्योम hci_req_sync_cancel(काष्ठा hci_dev *hdev, पूर्णांक err);

काष्ठा sk_buff *hci_prepare_cmd(काष्ठा hci_dev *hdev, u16 opcode, u32 plen,
				स्थिर व्योम *param);

पूर्णांक __hci_req_hci_घातer_on(काष्ठा hci_dev *hdev);

व्योम __hci_req_ग_लिखो_fast_connectable(काष्ठा hci_request *req, bool enable);
व्योम __hci_req_update_name(काष्ठा hci_request *req);
व्योम __hci_req_update_eir(काष्ठा hci_request *req);

व्योम hci_req_add_le_scan_disable(काष्ठा hci_request *req, bool rpa_le_conn);
व्योम hci_req_add_le_passive_scan(काष्ठा hci_request *req);

व्योम hci_req_prepare_suspend(काष्ठा hci_dev *hdev, क्रमागत suspended_state next);

व्योम hci_req_disable_address_resolution(काष्ठा hci_dev *hdev);
व्योम __hci_req_छोड़ो_adv_instances(काष्ठा hci_request *req);
पूर्णांक hci_req_resume_adv_instances(काष्ठा hci_dev *hdev);
व्योम hci_req_reenable_advertising(काष्ठा hci_dev *hdev);
व्योम __hci_req_enable_advertising(काष्ठा hci_request *req);
व्योम __hci_req_disable_advertising(काष्ठा hci_request *req);
व्योम __hci_req_update_adv_data(काष्ठा hci_request *req, u8 instance);
पूर्णांक hci_req_update_adv_data(काष्ठा hci_dev *hdev, u8 instance);
व्योम __hci_req_update_scan_rsp_data(काष्ठा hci_request *req, u8 instance);

पूर्णांक __hci_req_schedule_adv_instance(काष्ठा hci_request *req, u8 instance,
				    bool क्रमce);
व्योम hci_req_clear_adv_instance(काष्ठा hci_dev *hdev, काष्ठा sock *sk,
				काष्ठा hci_request *req, u8 instance,
				bool क्रमce);

पूर्णांक __hci_req_setup_ext_adv_instance(काष्ठा hci_request *req, u8 instance);
पूर्णांक __hci_req_start_ext_adv(काष्ठा hci_request *req, u8 instance);
पूर्णांक __hci_req_enable_ext_advertising(काष्ठा hci_request *req, u8 instance);
पूर्णांक __hci_req_disable_ext_adv_instance(काष्ठा hci_request *req, u8 instance);
पूर्णांक __hci_req_हटाओ_ext_adv_instance(काष्ठा hci_request *req, u8 instance);
व्योम __hci_req_clear_ext_adv_sets(काष्ठा hci_request *req);
पूर्णांक hci_get_अक्रमom_address(काष्ठा hci_dev *hdev, bool require_privacy,
			   bool use_rpa, काष्ठा adv_info *adv_instance,
			   u8 *own_addr_type, bdaddr_t *अक्रम_addr);

व्योम __hci_req_update_class(काष्ठा hci_request *req);

/* Returns true अगर HCI commands were queued */
bool hci_req_stop_discovery(काष्ठा hci_request *req);

अटल अंतरभूत व्योम hci_req_update_scan(काष्ठा hci_dev *hdev)
अणु
	queue_work(hdev->req_workqueue, &hdev->scan_update);
पूर्ण

व्योम __hci_req_update_scan(काष्ठा hci_request *req);

पूर्णांक hci_update_अक्रमom_address(काष्ठा hci_request *req, bool require_privacy,
			      bool use_rpa, u8 *own_addr_type);

पूर्णांक hci_पात_conn(काष्ठा hci_conn *conn, u8 reason);
व्योम __hci_पात_conn(काष्ठा hci_request *req, काष्ठा hci_conn *conn,
		      u8 reason);

अटल अंतरभूत व्योम hci_update_background_scan(काष्ठा hci_dev *hdev)
अणु
	queue_work(hdev->req_workqueue, &hdev->bg_scan_update);
पूर्ण

व्योम hci_request_setup(काष्ठा hci_dev *hdev);
व्योम hci_request_cancel_all(काष्ठा hci_dev *hdev);

u8 append_local_name(काष्ठा hci_dev *hdev, u8 *ptr, u8 ad_len);

अटल अंतरभूत u16 eir_append_data(u8 *eir, u16 eir_len, u8 type,
				  u8 *data, u8 data_len)
अणु
	eir[eir_len++] = माप(type) + data_len;
	eir[eir_len++] = type;
	स_नकल(&eir[eir_len], data, data_len);
	eir_len += data_len;

	वापस eir_len;
पूर्ण

अटल अंतरभूत u16 eir_append_le16(u8 *eir, u16 eir_len, u8 type, u16 data)
अणु
	eir[eir_len++] = माप(type) + माप(data);
	eir[eir_len++] = type;
	put_unaligned_le16(data, &eir[eir_len]);
	eir_len += माप(data);

	वापस eir_len;
पूर्ण
