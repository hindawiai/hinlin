<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

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

#अगर_अघोषित __HCI_SOCK_H
#घोषणा __HCI_SOCK_H

/* Socket options */
#घोषणा HCI_DATA_सूची	1
#घोषणा HCI_FILTER	2
#घोषणा HCI_TIME_STAMP	3

/* CMSG flags */
#घोषणा HCI_CMSG_सूची	0x01
#घोषणा HCI_CMSG_TSTAMP	0x02

काष्ठा sockaddr_hci अणु
	sa_family_t    hci_family;
	अचिन्हित लघु hci_dev;
	अचिन्हित लघु hci_channel;
पूर्ण;
#घोषणा HCI_DEV_NONE	0xffff

#घोषणा HCI_CHANNEL_RAW		0
#घोषणा HCI_CHANNEL_USER	1
#घोषणा HCI_CHANNEL_MONITOR	2
#घोषणा HCI_CHANNEL_CONTROL	3
#घोषणा HCI_CHANNEL_LOGGING	4

काष्ठा hci_filter अणु
	अचिन्हित दीर्घ type_mask;
	अचिन्हित दीर्घ event_mask[2];
	__le16 opcode;
पूर्ण;

काष्ठा hci_ufilter अणु
	__u32  type_mask;
	__u32  event_mask[2];
	__le16 opcode;
पूर्ण;

#घोषणा HCI_FLT_TYPE_BITS	31
#घोषणा HCI_FLT_EVENT_BITS	63
#घोषणा HCI_FLT_OGF_BITS	63
#घोषणा HCI_FLT_OCF_BITS	127

/* Ioctl defines */
#घोषणा HCIDEVUP	_IOW('H', 201, पूर्णांक)
#घोषणा HCIDEVDOWN	_IOW('H', 202, पूर्णांक)
#घोषणा HCIDEVRESET	_IOW('H', 203, पूर्णांक)
#घोषणा HCIDEVRESTAT	_IOW('H', 204, पूर्णांक)

#घोषणा HCIGETDEVLIST	_IOR('H', 210, पूर्णांक)
#घोषणा HCIGETDEVINFO	_IOR('H', 211, पूर्णांक)
#घोषणा HCIGETCONNLIST	_IOR('H', 212, पूर्णांक)
#घोषणा HCIGETCONNINFO	_IOR('H', 213, पूर्णांक)
#घोषणा HCIGETAUTHINFO	_IOR('H', 215, पूर्णांक)

#घोषणा HCISETRAW	_IOW('H', 220, पूर्णांक)
#घोषणा HCISETSCAN	_IOW('H', 221, पूर्णांक)
#घोषणा HCISETAUTH	_IOW('H', 222, पूर्णांक)
#घोषणा HCISETENCRYPT	_IOW('H', 223, पूर्णांक)
#घोषणा HCISETPTYPE	_IOW('H', 224, पूर्णांक)
#घोषणा HCISETLINKPOL	_IOW('H', 225, पूर्णांक)
#घोषणा HCISETLINKMODE	_IOW('H', 226, पूर्णांक)
#घोषणा HCISETACLMTU	_IOW('H', 227, पूर्णांक)
#घोषणा HCISETSCOMTU	_IOW('H', 228, पूर्णांक)

#घोषणा HCIBLOCKADDR	_IOW('H', 230, पूर्णांक)
#घोषणा HCIUNBLOCKADDR	_IOW('H', 231, पूर्णांक)

#घोषणा HCIINQUIRY	_IOR('H', 240, पूर्णांक)

/* Ioctl requests काष्ठाures */
काष्ठा hci_dev_stats अणु
	__u32 err_rx;
	__u32 err_tx;
	__u32 cmd_tx;
	__u32 evt_rx;
	__u32 acl_tx;
	__u32 acl_rx;
	__u32 sco_tx;
	__u32 sco_rx;
	__u32 byte_rx;
	__u32 byte_tx;
पूर्ण;

काष्ठा hci_dev_info अणु
	__u16 dev_id;
	अक्षर  name[8];

	bdaddr_t bdaddr;

	__u32 flags;
	__u8  type;

	__u8  features[8];

	__u32 pkt_type;
	__u32 link_policy;
	__u32 link_mode;

	__u16 acl_mtu;
	__u16 acl_pkts;
	__u16 sco_mtu;
	__u16 sco_pkts;

	काष्ठा hci_dev_stats stat;
पूर्ण;

काष्ठा hci_conn_info अणु
	__u16    handle;
	bdaddr_t bdaddr;
	__u8     type;
	__u8     out;
	__u16    state;
	__u32    link_mode;
पूर्ण;

काष्ठा hci_dev_req अणु
	__u16  dev_id;
	__u32  dev_opt;
पूर्ण;

काष्ठा hci_dev_list_req अणु
	__u16  dev_num;
	काष्ठा hci_dev_req dev_req[];	/* hci_dev_req काष्ठाures */
पूर्ण;

काष्ठा hci_conn_list_req अणु
	__u16  dev_id;
	__u16  conn_num;
	काष्ठा hci_conn_info conn_info[];
पूर्ण;

काष्ठा hci_conn_info_req अणु
	bdaddr_t bdaddr;
	__u8     type;
	काष्ठा   hci_conn_info conn_info[];
पूर्ण;

काष्ठा hci_auth_info_req अणु
	bdaddr_t bdaddr;
	__u8     type;
पूर्ण;

काष्ठा hci_inquiry_req अणु
	__u16 dev_id;
	__u16 flags;
	__u8  lap[3];
	__u8  length;
	__u8  num_rsp;
पूर्ण;
#घोषणा IREQ_CACHE_FLUSH 0x0001

#पूर्ण_अगर /* __HCI_SOCK_H */
