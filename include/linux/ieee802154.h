<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IEEE802.15.4-2003 specअगरication
 *
 * Copyright (C) 2007, 2008 Siemens AG
 *
 * Written by:
 * Pavel Smolenskiy <pavel.smolenskiy@gmail.com>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 * Maxim Osipov <maxim.osipov@siemens.com>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#अगर_अघोषित LINUX_IEEE802154_H
#घोषणा LINUX_IEEE802154_H

#समावेश <linux/types.h>
#समावेश <linux/अक्रमom.h>

#घोषणा IEEE802154_MTU			127
#घोषणा IEEE802154_ACK_PSDU_LEN		5
#घोषणा IEEE802154_MIN_PSDU_LEN		9
#घोषणा IEEE802154_FCS_LEN		2
#घोषणा IEEE802154_MAX_AUTH_TAG_LEN	16
#घोषणा IEEE802154_FC_LEN		2
#घोषणा IEEE802154_SEQ_LEN		1

/*  General MAC frame क्रमmat:
 *  2 bytes: Frame Control
 *  1 byte:  Sequence Number
 * 20 bytes: Addressing fields
 * 14 bytes: Auxiliary Security Header
 */
#घोषणा IEEE802154_MAX_HEADER_LEN	(2 + 1 + 20 + 14)
#घोषणा IEEE802154_MIN_HEADER_LEN	(IEEE802154_ACK_PSDU_LEN - \
					 IEEE802154_FCS_LEN)

#घोषणा IEEE802154_PAN_ID_BROADCAST	0xffff
#घोषणा IEEE802154_ADDR_SHORT_BROADCAST	0xffff
#घोषणा IEEE802154_ADDR_SHORT_UNSPEC	0xfffe

#घोषणा IEEE802154_EXTENDED_ADDR_LEN	8
#घोषणा IEEE802154_SHORT_ADDR_LEN	2
#घोषणा IEEE802154_PAN_ID_LEN		2

#घोषणा IEEE802154_LIFS_PERIOD		40
#घोषणा IEEE802154_SIFS_PERIOD		12
#घोषणा IEEE802154_MAX_SIFS_FRAME_SIZE	18

#घोषणा IEEE802154_MAX_CHANNEL		26
#घोषणा IEEE802154_MAX_PAGE		31

#घोषणा IEEE802154_FC_TYPE_BEACON	0x0	/* Frame is beacon */
#घोषणा	IEEE802154_FC_TYPE_DATA		0x1	/* Frame is data */
#घोषणा IEEE802154_FC_TYPE_ACK		0x2	/* Frame is acknowledgment */
#घोषणा IEEE802154_FC_TYPE_MAC_CMD	0x3	/* Frame is MAC command */

#घोषणा IEEE802154_FC_TYPE_SHIFT		0
#घोषणा IEEE802154_FC_TYPE_MASK		((1 << 3) - 1)
#घोषणा IEEE802154_FC_TYPE(x)		((x & IEEE802154_FC_TYPE_MASK) >> IEEE802154_FC_TYPE_SHIFT)
#घोषणा IEEE802154_FC_SET_TYPE(v, x)	करो अणु	\
	v = (((v) & ~IEEE802154_FC_TYPE_MASK) | \
	    (((x) << IEEE802154_FC_TYPE_SHIFT) & IEEE802154_FC_TYPE_MASK)); \
	पूर्ण जबतक (0)

#घोषणा IEEE802154_FC_SECEN_SHIFT	3
#घोषणा IEEE802154_FC_SECEN		(1 << IEEE802154_FC_SECEN_SHIFT)
#घोषणा IEEE802154_FC_FRPEND_SHIFT	4
#घोषणा IEEE802154_FC_FRPEND		(1 << IEEE802154_FC_FRPEND_SHIFT)
#घोषणा IEEE802154_FC_ACK_REQ_SHIFT	5
#घोषणा IEEE802154_FC_ACK_REQ		(1 << IEEE802154_FC_ACK_REQ_SHIFT)
#घोषणा IEEE802154_FC_INTRA_PAN_SHIFT	6
#घोषणा IEEE802154_FC_INTRA_PAN		(1 << IEEE802154_FC_INTRA_PAN_SHIFT)

#घोषणा IEEE802154_FC_SAMODE_SHIFT	14
#घोषणा IEEE802154_FC_SAMODE_MASK	(3 << IEEE802154_FC_SAMODE_SHIFT)
#घोषणा IEEE802154_FC_DAMODE_SHIFT	10
#घोषणा IEEE802154_FC_DAMODE_MASK	(3 << IEEE802154_FC_DAMODE_SHIFT)

#घोषणा IEEE802154_FC_VERSION_SHIFT	12
#घोषणा IEEE802154_FC_VERSION_MASK	(3 << IEEE802154_FC_VERSION_SHIFT)
#घोषणा IEEE802154_FC_VERSION(x)	((x & IEEE802154_FC_VERSION_MASK) >> IEEE802154_FC_VERSION_SHIFT)

#घोषणा IEEE802154_FC_SAMODE(x)		\
	(((x) & IEEE802154_FC_SAMODE_MASK) >> IEEE802154_FC_SAMODE_SHIFT)

#घोषणा IEEE802154_FC_DAMODE(x)		\
	(((x) & IEEE802154_FC_DAMODE_MASK) >> IEEE802154_FC_DAMODE_SHIFT)

#घोषणा IEEE802154_SCF_SECLEVEL_MASK		7
#घोषणा IEEE802154_SCF_SECLEVEL_SHIFT		0
#घोषणा IEEE802154_SCF_SECLEVEL(x)		(x & IEEE802154_SCF_SECLEVEL_MASK)
#घोषणा IEEE802154_SCF_KEY_ID_MODE_SHIFT	3
#घोषणा IEEE802154_SCF_KEY_ID_MODE_MASK		(3 << IEEE802154_SCF_KEY_ID_MODE_SHIFT)
#घोषणा IEEE802154_SCF_KEY_ID_MODE(x)		\
	((x & IEEE802154_SCF_KEY_ID_MODE_MASK) >> IEEE802154_SCF_KEY_ID_MODE_SHIFT)

#घोषणा IEEE802154_SCF_KEY_IMPLICIT		0
#घोषणा IEEE802154_SCF_KEY_INDEX		1
#घोषणा IEEE802154_SCF_KEY_SHORT_INDEX		2
#घोषणा IEEE802154_SCF_KEY_HW_INDEX		3

#घोषणा IEEE802154_SCF_SECLEVEL_NONE		0
#घोषणा IEEE802154_SCF_SECLEVEL_MIC32		1
#घोषणा IEEE802154_SCF_SECLEVEL_MIC64		2
#घोषणा IEEE802154_SCF_SECLEVEL_MIC128		3
#घोषणा IEEE802154_SCF_SECLEVEL_ENC		4
#घोषणा IEEE802154_SCF_SECLEVEL_ENC_MIC32	5
#घोषणा IEEE802154_SCF_SECLEVEL_ENC_MIC64	6
#घोषणा IEEE802154_SCF_SECLEVEL_ENC_MIC128	7

/* MAC footer size */
#घोषणा IEEE802154_MFR_SIZE	2 /* 2 octets */

/* MAC's Command Frames Identअगरiers */
#घोषणा IEEE802154_CMD_ASSOCIATION_REQ		0x01
#घोषणा IEEE802154_CMD_ASSOCIATION_RESP		0x02
#घोषणा IEEE802154_CMD_DISASSOCIATION_NOTIFY	0x03
#घोषणा IEEE802154_CMD_DATA_REQ			0x04
#घोषणा IEEE802154_CMD_PANID_CONFLICT_NOTIFY	0x05
#घोषणा IEEE802154_CMD_ORPHAN_NOTIFY		0x06
#घोषणा IEEE802154_CMD_BEACON_REQ		0x07
#घोषणा IEEE802154_CMD_COORD_REALIGN_NOTIFY	0x08
#घोषणा IEEE802154_CMD_GTS_REQ			0x09

/*
 * The वापस values of MAC operations
 */
क्रमागत अणु
	/*
	 * The requested operation was completed successfully.
	 * For a transmission request, this value indicates
	 * a successful transmission.
	 */
	IEEE802154_SUCCESS = 0x0,

	/* The beacon was lost following a synchronization request. */
	IEEE802154_BEACON_LOSS = 0xe0,
	/*
	 * A transmission could not take place due to activity on the
	 * channel, i.e., the CSMA-CA mechanism has failed.
	 */
	IEEE802154_CHNL_ACCESS_FAIL = 0xe1,
	/* The GTS request has been denied by the PAN coordinator. */
	IEEE802154_DENINED = 0xe2,
	/* The attempt to disable the transceiver has failed. */
	IEEE802154_DISABLE_TRX_FAIL = 0xe3,
	/*
	 * The received frame induces a failed security check according to
	 * the security suite.
	 */
	IEEE802154_FAILED_SECURITY_CHECK = 0xe4,
	/*
	 * The frame resulting from secure processing has a length that is
	 * greater than aMACMaxFrameSize.
	 */
	IEEE802154_FRAME_TOO_LONG = 0xe5,
	/*
	 * The requested GTS transmission failed because the specअगरied GTS
	 * either did not have a transmit GTS direction or was not defined.
	 */
	IEEE802154_INVALID_GTS = 0xe6,
	/*
	 * A request to purge an MSDU from the transaction queue was made using
	 * an MSDU handle that was not found in the transaction table.
	 */
	IEEE802154_INVALID_HANDLE = 0xe7,
	/* A parameter in the primitive is out of the valid range.*/
	IEEE802154_INVALID_PARAMETER = 0xe8,
	/* No acknowledgment was received after aMaxFrameRetries. */
	IEEE802154_NO_ACK = 0xe9,
	/* A scan operation failed to find any network beacons.*/
	IEEE802154_NO_BEACON = 0xea,
	/* No response data were available following a request. */
	IEEE802154_NO_DATA = 0xeb,
	/* The operation failed because a लघु address was not allocated. */
	IEEE802154_NO_SHORT_ADDRESS = 0xec,
	/*
	 * A receiver enable request was unsuccessful because it could not be
	 * completed within the CAP.
	 */
	IEEE802154_OUT_OF_CAP = 0xed,
	/*
	 * A PAN identअगरier conflict has been detected and communicated to the
	 * PAN coordinator.
	 */
	IEEE802154_PANID_CONFLICT = 0xee,
	/* A coordinator realignment command has been received. */
	IEEE802154_REALIGMENT = 0xef,
	/* The transaction has expired and its inक्रमmation discarded. */
	IEEE802154_TRANSACTION_EXPIRED = 0xf0,
	/* There is no capacity to store the transaction. */
	IEEE802154_TRANSACTION_OVERFLOW = 0xf1,
	/*
	 * The transceiver was in the transmitter enabled state when the
	 * receiver was requested to be enabled.
	 */
	IEEE802154_TX_ACTIVE = 0xf2,
	/* The appropriate key is not available in the ACL. */
	IEEE802154_UNAVAILABLE_KEY = 0xf3,
	/*
	 * A SET/GET request was issued with the identअगरier of a PIB attribute
	 * that is not supported.
	 */
	IEEE802154_UNSUPPORTED_ATTR = 0xf4,
	/*
	 * A request to perक्रमm a scan operation failed because the MLME was
	 * in the process of perक्रमming a previously initiated scan operation.
	 */
	IEEE802154_SCAN_IN_PROGRESS = 0xfc,
पूर्ण;

/* frame control handling */
#घोषणा IEEE802154_FCTL_FTYPE		0x0003
#घोषणा IEEE802154_FCTL_ACKREQ		0x0020
#घोषणा IEEE802154_FCTL_SECEN		0x0004
#घोषणा IEEE802154_FCTL_INTRA_PAN	0x0040
#घोषणा IEEE802154_FCTL_DADDR		0x0c00
#घोषणा IEEE802154_FCTL_SADDR		0xc000

#घोषणा IEEE802154_FTYPE_DATA		0x0001

#घोषणा IEEE802154_FCTL_ADDR_NONE	0x0000
#घोषणा IEEE802154_FCTL_DADDR_SHORT	0x0800
#घोषणा IEEE802154_FCTL_DADDR_EXTENDED	0x0c00
#घोषणा IEEE802154_FCTL_SADDR_SHORT	0x8000
#घोषणा IEEE802154_FCTL_SADDR_EXTENDED	0xc000

/*
 * ieee802154_is_data - check अगर type is IEEE802154_FTYPE_DATA
 * @fc: frame control bytes in little-endian byteorder
 */
अटल अंतरभूत पूर्णांक ieee802154_is_data(__le16 fc)
अणु
	वापस (fc & cpu_to_le16(IEEE802154_FCTL_FTYPE)) ==
		cpu_to_le16(IEEE802154_FTYPE_DATA);
पूर्ण

/**
 * ieee802154_is_secen - check अगर Security bit is set
 * @fc: frame control bytes in little-endian byteorder
 */
अटल अंतरभूत bool ieee802154_is_secen(__le16 fc)
अणु
	वापस fc & cpu_to_le16(IEEE802154_FCTL_SECEN);
पूर्ण

/**
 * ieee802154_is_ackreq - check अगर acknowledgment request bit is set
 * @fc: frame control bytes in little-endian byteorder
 */
अटल अंतरभूत bool ieee802154_is_ackreq(__le16 fc)
अणु
	वापस fc & cpu_to_le16(IEEE802154_FCTL_ACKREQ);
पूर्ण

/**
 * ieee802154_is_पूर्णांकra_pan - check अगर पूर्णांकra pan id communication
 * @fc: frame control bytes in little-endian byteorder
 */
अटल अंतरभूत bool ieee802154_is_पूर्णांकra_pan(__le16 fc)
अणु
	वापस fc & cpu_to_le16(IEEE802154_FCTL_INTRA_PAN);
पूर्ण

/*
 * ieee802154_daddr_mode - get daddr mode from fc
 * @fc: frame control bytes in little-endian byteorder
 */
अटल अंतरभूत __le16 ieee802154_daddr_mode(__le16 fc)
अणु
	वापस fc & cpu_to_le16(IEEE802154_FCTL_DADDR);
पूर्ण

/*
 * ieee802154_saddr_mode - get saddr mode from fc
 * @fc: frame control bytes in little-endian byteorder
 */
अटल अंतरभूत __le16 ieee802154_saddr_mode(__le16 fc)
अणु
	वापस fc & cpu_to_le16(IEEE802154_FCTL_SADDR);
पूर्ण

/**
 * ieee802154_is_valid_psdu_len - check अगर psdu len is valid
 * available lengths:
 *	0-4	Reserved
 *	5	MPDU (Acknowledgment)
 *	6-8	Reserved
 *	9-127	MPDU
 *
 * @len: psdu len with (MHR + payload + MFR)
 */
अटल अंतरभूत bool ieee802154_is_valid_psdu_len(u8 len)
अणु
	वापस (len == IEEE802154_ACK_PSDU_LEN ||
		(len >= IEEE802154_MIN_PSDU_LEN && len <= IEEE802154_MTU));
पूर्ण

/**
 * ieee802154_is_valid_extended_unicast_addr - check अगर extended addr is valid
 * @addr: extended addr to check
 */
अटल अंतरभूत bool ieee802154_is_valid_extended_unicast_addr(__le64 addr)
अणु
	/* Bail out अगर the address is all zero, or अगर the group
	 * address bit is set.
	 */
	वापस ((addr != cpu_to_le64(0x0000000000000000ULL)) &&
		!(addr & cpu_to_le64(0x0100000000000000ULL)));
पूर्ण

/**
 * ieee802154_is_broadcast_लघु_addr - check अगर लघु addr is broadcast
 * @addr: लघु addr to check
 */
अटल अंतरभूत bool ieee802154_is_broadcast_लघु_addr(__le16 addr)
अणु
	वापस (addr == cpu_to_le16(IEEE802154_ADDR_SHORT_BROADCAST));
पूर्ण

/**
 * ieee802154_is_unspec_लघु_addr - check अगर लघु addr is unspecअगरied
 * @addr: लघु addr to check
 */
अटल अंतरभूत bool ieee802154_is_unspec_लघु_addr(__le16 addr)
अणु
	वापस (addr == cpu_to_le16(IEEE802154_ADDR_SHORT_UNSPEC));
पूर्ण

/**
 * ieee802154_is_valid_src_लघु_addr - check अगर source लघु address is valid
 * @addr: लघु addr to check
 */
अटल अंतरभूत bool ieee802154_is_valid_src_लघु_addr(__le16 addr)
अणु
	वापस !(ieee802154_is_broadcast_लघु_addr(addr) ||
		 ieee802154_is_unspec_लघु_addr(addr));
पूर्ण

/**
 * ieee802154_अक्रमom_extended_addr - generates a अक्रमom extended address
 * @addr: extended addr poपूर्णांकer to place the अक्रमom address
 */
अटल अंतरभूत व्योम ieee802154_अक्रमom_extended_addr(__le64 *addr)
अणु
	get_अक्रमom_bytes(addr, IEEE802154_EXTENDED_ADDR_LEN);

	/* clear the group bit, and set the locally administered bit */
	((u8 *)addr)[IEEE802154_EXTENDED_ADDR_LEN - 1] &= ~0x01;
	((u8 *)addr)[IEEE802154_EXTENDED_ADDR_LEN - 1] |= 0x02;
पूर्ण

#पूर्ण_अगर /* LINUX_IEEE802154_H */
