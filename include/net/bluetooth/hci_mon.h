<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux

   Copyright (C) 2011-2012  Intel Corporation

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

#अगर_अघोषित __HCI_MON_H
#घोषणा __HCI_MON_H

काष्ठा hci_mon_hdr अणु
	__le16	opcode;
	__le16	index;
	__le16	len;
पूर्ण __packed;
#घोषणा HCI_MON_HDR_SIZE 6

#घोषणा HCI_MON_NEW_INDEX	0
#घोषणा HCI_MON_DEL_INDEX	1
#घोषणा HCI_MON_COMMAND_PKT	2
#घोषणा HCI_MON_EVENT_PKT	3
#घोषणा HCI_MON_ACL_TX_PKT	4
#घोषणा HCI_MON_ACL_RX_PKT	5
#घोषणा HCI_MON_SCO_TX_PKT	6
#घोषणा HCI_MON_SCO_RX_PKT	7
#घोषणा HCI_MON_OPEN_INDEX	8
#घोषणा HCI_MON_CLOSE_INDEX	9
#घोषणा HCI_MON_INDEX_INFO	10
#घोषणा HCI_MON_VENDOR_DIAG	11
#घोषणा HCI_MON_SYSTEM_NOTE	12
#घोषणा HCI_MON_USER_LOGGING	13
#घोषणा HCI_MON_CTRL_OPEN	14
#घोषणा HCI_MON_CTRL_CLOSE	15
#घोषणा HCI_MON_CTRL_COMMAND	16
#घोषणा HCI_MON_CTRL_EVENT	17
#घोषणा HCI_MON_ISO_TX_PKT	18
#घोषणा HCI_MON_ISO_RX_PKT	19

काष्ठा hci_mon_new_index अणु
	__u8		type;
	__u8		bus;
	bdaddr_t	bdaddr;
	अक्षर		name[8];
पूर्ण __packed;
#घोषणा HCI_MON_NEW_INDEX_SIZE 16

काष्ठा hci_mon_index_info अणु
	bdaddr_t	bdaddr;
	__le16		manufacturer;
पूर्ण __packed;
#घोषणा HCI_MON_INDEX_INFO_SIZE 8

#पूर्ण_अगर /* __HCI_MON_H */
