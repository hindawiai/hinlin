<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
   Copyright (c) 2010,2011 Code Aurora Forum.  All rights reserved.
   Copyright (c) 2011,2012 Intel Corp.

*/

#अगर_अघोषित __A2MP_H
#घोषणा __A2MP_H

#समावेश <net/bluetooth/l2cap.h>

क्रमागत amp_mgr_state अणु
	READ_LOC_AMP_INFO,
	READ_LOC_AMP_ASSOC,
	READ_LOC_AMP_ASSOC_FINAL,
	WRITE_REMOTE_AMP_ASSOC,
पूर्ण;

काष्ठा amp_mgr अणु
	काष्ठा list_head	list;
	काष्ठा l2cap_conn	*l2cap_conn;
	काष्ठा l2cap_chan	*a2mp_chan;
	काष्ठा l2cap_chan	*bredr_chan;
	काष्ठा kref		kref;
	__u8			ident;
	__u8			handle;
	अचिन्हित दीर्घ		state;
	अचिन्हित दीर्घ		flags;

	काष्ठा list_head	amp_ctrls;
	काष्ठा mutex		amp_ctrls_lock;
पूर्ण;

काष्ठा a2mp_cmd अणु
	__u8	code;
	__u8	ident;
	__le16	len;
	__u8	data[];
पूर्ण __packed;

/* A2MP command codes */
#घोषणा A2MP_COMMAND_REJ         0x01
काष्ठा a2mp_cmd_rej अणु
	__le16	reason;
	__u8	data[];
पूर्ण __packed;

#घोषणा A2MP_DISCOVER_REQ        0x02
काष्ठा a2mp_discov_req अणु
	__le16	mtu;
	__le16	ext_feat;
पूर्ण __packed;

काष्ठा a2mp_cl अणु
	__u8	id;
	__u8	type;
	__u8	status;
पूर्ण __packed;

#घोषणा A2MP_DISCOVER_RSP        0x03
काष्ठा a2mp_discov_rsp अणु
	__le16     mtu;
	__le16     ext_feat;
	काष्ठा a2mp_cl cl[];
पूर्ण __packed;

#घोषणा A2MP_CHANGE_NOTIFY       0x04
#घोषणा A2MP_CHANGE_RSP          0x05

#घोषणा A2MP_GETINFO_REQ         0x06
काष्ठा a2mp_info_req अणु
	__u8       id;
पूर्ण __packed;

#घोषणा A2MP_GETINFO_RSP         0x07
काष्ठा a2mp_info_rsp अणु
	__u8	id;
	__u8	status;
	__le32	total_bw;
	__le32	max_bw;
	__le32	min_latency;
	__le16	pal_cap;
	__le16	assoc_size;
पूर्ण __packed;

#घोषणा A2MP_GETAMPASSOC_REQ     0x08
काष्ठा a2mp_amp_assoc_req अणु
	__u8	id;
पूर्ण __packed;

#घोषणा A2MP_GETAMPASSOC_RSP     0x09
काष्ठा a2mp_amp_assoc_rsp अणु
	__u8	id;
	__u8	status;
	__u8	amp_assoc[];
पूर्ण __packed;

#घोषणा A2MP_CREATEPHYSLINK_REQ  0x0A
#घोषणा A2MP_DISCONNPHYSLINK_REQ 0x0C
काष्ठा a2mp_physlink_req अणु
	__u8	local_id;
	__u8	remote_id;
	__u8	amp_assoc[];
पूर्ण __packed;

#घोषणा A2MP_CREATEPHYSLINK_RSP  0x0B
#घोषणा A2MP_DISCONNPHYSLINK_RSP 0x0D
काष्ठा a2mp_physlink_rsp अणु
	__u8	local_id;
	__u8	remote_id;
	__u8	status;
पूर्ण __packed;

/* A2MP response status */
#घोषणा A2MP_STATUS_SUCCESS			0x00
#घोषणा A2MP_STATUS_INVALID_CTRL_ID		0x01
#घोषणा A2MP_STATUS_UNABLE_START_LINK_CREATION	0x02
#घोषणा A2MP_STATUS_NO_PHYSICAL_LINK_EXISTS	0x02
#घोषणा A2MP_STATUS_COLLISION_OCCURED		0x03
#घोषणा A2MP_STATUS_DISCONN_REQ_RECVD		0x04
#घोषणा A2MP_STATUS_PHYS_LINK_EXISTS		0x05
#घोषणा A2MP_STATUS_SECURITY_VIOLATION		0x06

काष्ठा amp_mgr *amp_mgr_get(काष्ठा amp_mgr *mgr);

#अगर IS_ENABLED(CONFIG_BT_HS)
पूर्णांक amp_mgr_put(काष्ठा amp_mgr *mgr);
काष्ठा l2cap_chan *a2mp_channel_create(काष्ठा l2cap_conn *conn,
				       काष्ठा sk_buff *skb);
व्योम a2mp_discover_amp(काष्ठा l2cap_chan *chan);
#अन्यथा
अटल अंतरभूत पूर्णांक amp_mgr_put(काष्ठा amp_mgr *mgr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा l2cap_chan *a2mp_channel_create(काष्ठा l2cap_conn *conn,
						     काष्ठा sk_buff *skb)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम a2mp_discover_amp(काष्ठा l2cap_chan *chan)
अणु
पूर्ण
#पूर्ण_अगर

व्योम a2mp_send_getinfo_rsp(काष्ठा hci_dev *hdev);
व्योम a2mp_send_getampassoc_rsp(काष्ठा hci_dev *hdev, u8 status);
व्योम a2mp_send_create_phy_link_req(काष्ठा hci_dev *hdev, u8 status);
व्योम a2mp_send_create_phy_link_rsp(काष्ठा hci_dev *hdev, u8 status);

#पूर्ण_अगर /* __A2MP_H */
