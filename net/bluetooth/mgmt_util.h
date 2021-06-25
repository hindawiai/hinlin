<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2015  Intel Coropration

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

काष्ठा mgmt_pending_cmd अणु
	काष्ठा list_head list;
	u16 opcode;
	पूर्णांक index;
	व्योम *param;
	माप_प्रकार param_len;
	काष्ठा sock *sk;
	व्योम *user_data;
	पूर्णांक (*cmd_complete)(काष्ठा mgmt_pending_cmd *cmd, u8 status);
पूर्ण;

पूर्णांक mgmt_send_event(u16 event, काष्ठा hci_dev *hdev, अचिन्हित लघु channel,
		    व्योम *data, u16 data_len, पूर्णांक flag, काष्ठा sock *skip_sk);
पूर्णांक mgmt_cmd_status(काष्ठा sock *sk, u16 index, u16 cmd, u8 status);
पूर्णांक mgmt_cmd_complete(काष्ठा sock *sk, u16 index, u16 cmd, u8 status,
		      व्योम *rp, माप_प्रकार rp_len);

काष्ठा mgmt_pending_cmd *mgmt_pending_find(अचिन्हित लघु channel, u16 opcode,
					   काष्ठा hci_dev *hdev);
काष्ठा mgmt_pending_cmd *mgmt_pending_find_data(अचिन्हित लघु channel,
						u16 opcode,
						काष्ठा hci_dev *hdev,
						स्थिर व्योम *data);
व्योम mgmt_pending_क्रमeach(u16 opcode, काष्ठा hci_dev *hdev,
			  व्योम (*cb)(काष्ठा mgmt_pending_cmd *cmd, व्योम *data),
			  व्योम *data);
काष्ठा mgmt_pending_cmd *mgmt_pending_add(काष्ठा sock *sk, u16 opcode,
					  काष्ठा hci_dev *hdev,
					  व्योम *data, u16 len);
व्योम mgmt_pending_मुक्त(काष्ठा mgmt_pending_cmd *cmd);
व्योम mgmt_pending_हटाओ(काष्ठा mgmt_pending_cmd *cmd);
