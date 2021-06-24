<शैली गुरु>
/*
   HIDP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2003-2004 Marcel Holपंचांगann <marcel@holपंचांगann.org>

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

#अगर_अघोषित __HIDP_H
#घोषणा __HIDP_H

#समावेश <linux/types.h>
#समावेश <linux/hid.h>
#समावेश <linux/kref.h>
#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/l2cap.h>

/* HIDP header masks */
#घोषणा HIDP_HEADER_TRANS_MASK			0xf0
#घोषणा HIDP_HEADER_PARAM_MASK			0x0f

/* HIDP transaction types */
#घोषणा HIDP_TRANS_HANDSHAKE			0x00
#घोषणा HIDP_TRANS_HID_CONTROL			0x10
#घोषणा HIDP_TRANS_GET_REPORT			0x40
#घोषणा HIDP_TRANS_SET_REPORT			0x50
#घोषणा HIDP_TRANS_GET_PROTOCOL			0x60
#घोषणा HIDP_TRANS_SET_PROTOCOL			0x70
#घोषणा HIDP_TRANS_GET_IDLE			0x80
#घोषणा HIDP_TRANS_SET_IDLE			0x90
#घोषणा HIDP_TRANS_DATA				0xa0
#घोषणा HIDP_TRANS_DATC				0xb0

/* HIDP handshake results */
#घोषणा HIDP_HSHK_SUCCESSFUL			0x00
#घोषणा HIDP_HSHK_NOT_READY			0x01
#घोषणा HIDP_HSHK_ERR_INVALID_REPORT_ID		0x02
#घोषणा HIDP_HSHK_ERR_UNSUPPORTED_REQUEST	0x03
#घोषणा HIDP_HSHK_ERR_INVALID_PARAMETER		0x04
#घोषणा HIDP_HSHK_ERR_UNKNOWN			0x0e
#घोषणा HIDP_HSHK_ERR_FATAL			0x0f

/* HIDP control operation parameters */
#घोषणा HIDP_CTRL_NOP				0x00
#घोषणा HIDP_CTRL_HARD_RESET			0x01
#घोषणा HIDP_CTRL_SOFT_RESET			0x02
#घोषणा HIDP_CTRL_SUSPEND			0x03
#घोषणा HIDP_CTRL_EXIT_SUSPEND			0x04
#घोषणा HIDP_CTRL_VIRTUAL_CABLE_UNPLUG		0x05

/* HIDP data transaction headers */
#घोषणा HIDP_DATA_RTYPE_MASK			0x03
#घोषणा HIDP_DATA_RSRVD_MASK			0x0c
#घोषणा HIDP_DATA_RTYPE_OTHER			0x00
#घोषणा HIDP_DATA_RTYPE_INPUT			0x01
#घोषणा HIDP_DATA_RTYPE_OUPUT			0x02
#घोषणा HIDP_DATA_RTYPE_FEATURE			0x03

/* HIDP protocol header parameters */
#घोषणा HIDP_PROTO_BOOT				0x00
#घोषणा HIDP_PROTO_REPORT			0x01

/* HIDP ioctl defines */
#घोषणा HIDPCONNADD	_IOW('H', 200, पूर्णांक)
#घोषणा HIDPCONNDEL	_IOW('H', 201, पूर्णांक)
#घोषणा HIDPGETCONNLIST	_IOR('H', 210, पूर्णांक)
#घोषणा HIDPGETCONNINFO	_IOR('H', 211, पूर्णांक)

#घोषणा HIDP_VIRTUAL_CABLE_UNPLUG	0
#घोषणा HIDP_BOOT_PROTOCOL_MODE		1
#घोषणा HIDP_BLUETOOTH_VENDOR_ID	9
#घोषणा HIDP_WAITING_FOR_RETURN		10
#घोषणा HIDP_WAITING_FOR_SEND_ACK	11

काष्ठा hidp_connadd_req अणु
	पूर्णांक   ctrl_sock;	/* Connected control socket */
	पूर्णांक   पूर्णांकr_sock;	/* Connected पूर्णांकerrupt socket */
	__u16 parser;
	__u16 rd_size;
	__u8 __user *rd_data;
	__u8  country;
	__u8  subclass;
	__u16 venकरोr;
	__u16 product;
	__u16 version;
	__u32 flags;
	__u32 idle_to;
	अक्षर  name[128];
पूर्ण;

काष्ठा hidp_conndel_req अणु
	bdaddr_t bdaddr;
	__u32    flags;
पूर्ण;

काष्ठा hidp_conninfo अणु
	bdaddr_t bdaddr;
	__u32    flags;
	__u16    state;
	__u16    venकरोr;
	__u16    product;
	__u16    version;
	अक्षर     name[128];
पूर्ण;

काष्ठा hidp_connlist_req अणु
	__u32  cnum;
	काष्ठा hidp_conninfo __user *ci;
पूर्ण;

पूर्णांक hidp_connection_add(स्थिर काष्ठा hidp_connadd_req *req, काष्ठा socket *ctrl_sock, काष्ठा socket *पूर्णांकr_sock);
पूर्णांक hidp_connection_del(काष्ठा hidp_conndel_req *req);
पूर्णांक hidp_get_connlist(काष्ठा hidp_connlist_req *req);
पूर्णांक hidp_get_conninfo(काष्ठा hidp_conninfo *ci);

क्रमागत hidp_session_state अणु
	HIDP_SESSION_IDLING,
	HIDP_SESSION_PREPARING,
	HIDP_SESSION_RUNNING,
पूर्ण;

/* HIDP session defines */
काष्ठा hidp_session अणु
	काष्ठा list_head list;
	काष्ठा kref ref;

	/* runसमय management */
	atomic_t state;
	रुको_queue_head_t state_queue;
	atomic_t terminate;
	काष्ठा task_काष्ठा *task;
	अचिन्हित दीर्घ flags;

	/* connection management */
	bdaddr_t bdaddr;
	काष्ठा l2cap_conn *conn;
	काष्ठा l2cap_user user;
	काष्ठा socket *ctrl_sock;
	काष्ठा socket *पूर्णांकr_sock;
	काष्ठा sk_buff_head ctrl_transmit;
	काष्ठा sk_buff_head पूर्णांकr_transmit;
	uपूर्णांक ctrl_mtu;
	uपूर्णांक पूर्णांकr_mtu;
	अचिन्हित दीर्घ idle_to;

	/* device management */
	काष्ठा work_काष्ठा dev_init;
	काष्ठा input_dev *input;
	काष्ठा hid_device *hid;
	काष्ठा समयr_list समयr;

	/* Report descriptor */
	__u8 *rd_data;
	uपूर्णांक rd_size;

	/* session data */
	अचिन्हित अक्षर keys[8];
	अचिन्हित अक्षर leds;

	/* Used in hidp_get_raw_report() */
	पूर्णांक रुकोing_report_type; /* HIDP_DATA_RTYPE_* */
	पूर्णांक रुकोing_report_number; /* -1 क्रम not numbered */
	काष्ठा mutex report_mutex;
	काष्ठा sk_buff *report_वापस;
	रुको_queue_head_t report_queue;

	/* Used in hidp_output_raw_report() */
	पूर्णांक output_report_success; /* boolean */

	/* temporary input buffer */
	u8 input_buf[HID_MAX_BUFFER_SIZE];
पूर्ण;

/* HIDP init defines */
पूर्णांक __init hidp_init_sockets(व्योम);
व्योम __निकास hidp_cleanup_sockets(व्योम);

#पूर्ण_अगर /* __HIDP_H */
