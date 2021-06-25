<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_BRIDGE_EBT_802_3_H
#घोषणा _UAPI__LINUX_BRIDGE_EBT_802_3_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#घोषणा EBT_802_3_SAP 0x01
#घोषणा EBT_802_3_TYPE 0x02

#घोषणा EBT_802_3_MATCH "802_3"

/*
 * If frame has DSAP/SSAP value 0xaa you must check the SNAP type
 * to discover what kind of packet we're carrying. 
 */
#घोषणा CHECK_TYPE 0xaa

/*
 * Control field may be one or two bytes.  If the first byte has
 * the value 0x03 then the entire length is one byte, otherwise it is two.
 * One byte controls are used in Unnumbered Inक्रमmation frames.
 * Two byte controls are used in Numbered Inक्रमmation frames.
 */
#घोषणा IS_UI 0x03

#घोषणा EBT_802_3_MASK (EBT_802_3_SAP | EBT_802_3_TYPE | EBT_802_3)

/* ui has one byte ctrl, ni has two */
काष्ठा hdr_ui अणु
	__u8 dsap;
	__u8 ssap;
	__u8 ctrl;
	__u8 orig[3];
	__be16 type;
पूर्ण;

काष्ठा hdr_ni अणु
	__u8 dsap;
	__u8 ssap;
	__be16 ctrl;
	__u8  orig[3];
	__be16 type;
पूर्ण;

काष्ठा ebt_802_3_hdr अणु
	__u8  daddr[ETH_ALEN];
	__u8  saddr[ETH_ALEN];
	__be16 len;
	जोड़ अणु
		काष्ठा hdr_ui ui;
		काष्ठा hdr_ni ni;
	पूर्ण llc;
पूर्ण;


काष्ठा ebt_802_3_info अणु
	__u8  sap;
	__be16 type;
	__u8  biपंचांगask;
	__u8  invflags;
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_BRIDGE_EBT_802_3_H */
