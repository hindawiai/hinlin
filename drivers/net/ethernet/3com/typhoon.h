<शैली गुरु>
/* typhoon.h:	chip info क्रम the 3Com 3CR990 family of controllers */
/*
	Written 2002-2003 by David Dillow <dave@thedillows.org>

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	This software is available on a खुला web site. It may enable
	cryptographic capabilities of the 3Com hardware, and may be
	exported from the United States under License Exception "TSU"
	pursuant to 15 C.F.R. Section 740.13(e).

	This work was funded by the National Library of Medicine under
	the Deparपंचांगent of Energy project number 0274DD06D1 and NLM project
	number Y1-LM-2015-01.
*/

/* All Typhoon ring positions are specअगरiced in bytes, and poपूर्णांक to the
 * first "clean" entry in the ring -- ie the next entry we use क्रम whatever
 * purpose.
 */

/* The Typhoon basic ring
 * ringBase:  where this ring lives (our भव address)
 * lastWrite: the next entry we'll use
 */
काष्ठा basic_ring अणु
	u8 *ringBase;
	u32 lastWrite;
पूर्ण;

/* The Typhoon transmit ring -- same as a basic ring, plus:
 * lastRead:      where we're at in regard to cleaning up the ring
 * ग_लिखोRegister: रेजिस्टर to use क्रम writing (dअगरferent क्रम Hi & Lo rings)
 */
काष्ठा transmit_ring अणु
	u8 *ringBase;
	u32 lastWrite;
	u32 lastRead;
	पूर्णांक ग_लिखोRegister;
पूर्ण;

/* The host<->Typhoon ring index काष्ठाure
 * This indicates the current positions in the rings
 *
 * All values must be in little endian क्रमmat क्रम the 3XP
 *
 * rxHiCleared:   entry we've cleared to in the Hi receive ring
 * rxLoCleared:   entry we've cleared to in the Lo receive ring
 * rxBuffReady:   next entry we'll put a मुक्त buffer in
 * respCleared:   entry we've cleared to in the response ring
 *
 * txLoCleared:   entry the NIC has cleared to in the Lo transmit ring
 * txHiCleared:   entry the NIC has cleared to in the Hi transmit ring
 * rxLoReady:     entry the NIC has filled to in the Lo receive ring
 * rxBuffCleared: entry the NIC has cleared in the मुक्त buffer ring
 * cmdCleared:    entry the NIC has cleared in the command ring
 * respReady:     entry the NIC has filled to in the response ring
 * rxHiReady:     entry the NIC has filled to in the Hi receive ring
 */
काष्ठा typhoon_indexes अणु
	/* The first four are written by the host, and पढ़ो by the NIC */
	अस्थिर __le32 rxHiCleared;
	अस्थिर __le32 rxLoCleared;
	अस्थिर __le32 rxBuffReady;
	अस्थिर __le32 respCleared;

	/* The reमुख्यing are written by the NIC, and पढ़ो by the host */
	अस्थिर __le32 txLoCleared;
	अस्थिर __le32 txHiCleared;
	अस्थिर __le32 rxLoReady;
	अस्थिर __le32 rxBuffCleared;
	अस्थिर __le32 cmdCleared;
	अस्थिर __le32 respReady;
	अस्थिर __le32 rxHiReady;
पूर्ण __packed;

/* The host<->Typhoon पूर्णांकerface
 * Our means of communicating where things are
 *
 * All values must be in little endian क्रमmat क्रम the 3XP
 *
 * ringIndex:   64 bit bus address of the index काष्ठाure
 * txLoAddr:    64 bit bus address of the Lo transmit ring
 * txLoSize:    size (in bytes) of the Lo transmit ring
 * txHi*:       as above क्रम the Hi priority transmit ring
 * rxLo*:       as above क्रम the Lo priority receive ring
 * rxBuff*:     as above क्रम the मुक्त buffer ring
 * cmd*:        as above क्रम the command ring
 * resp*:       as above क्रम the response ring
 * zeroAddr:    64 bit bus address of a zero word (क्रम DMA)
 * rxHi*:       as above क्रम the Hi Priority receive ring
 *
 * While there is room क्रम 64 bit addresses, current versions of the 3XP
 * only करो 32 bit addresses, so the *Hi क्रम each of the above will always
 * be zero.
 */
काष्ठा typhoon_पूर्णांकerface अणु
	__le32 ringIndex;
	__le32 ringIndexHi;
	__le32 txLoAddr;
	__le32 txLoAddrHi;
	__le32 txLoSize;
	__le32 txHiAddr;
	__le32 txHiAddrHi;
	__le32 txHiSize;
	__le32 rxLoAddr;
	__le32 rxLoAddrHi;
	__le32 rxLoSize;
	__le32 rxBuffAddr;
	__le32 rxBuffAddrHi;
	__le32 rxBuffSize;
	__le32 cmdAddr;
	__le32 cmdAddrHi;
	__le32 cmdSize;
	__le32 respAddr;
	__le32 respAddrHi;
	__le32 respSize;
	__le32 zeroAddr;
	__le32 zeroAddrHi;
	__le32 rxHiAddr;
	__le32 rxHiAddrHi;
	__le32 rxHiSize;
पूर्ण __packed;

/* The Typhoon transmit/fragment descriptor
 *
 * A packet is described by a packet descriptor, followed by option descriptors,
 * अगर any, then one or more fragment descriptors.
 *
 * Packet descriptor:
 * flags:	Descriptor type
 * len:i	zero, or length of this packet
 * addr*:	8 bytes of opaque data to the firmware -- क्रम skb poपूर्णांकer
 * processFlags: Determine offload tasks to perक्रमm on this packet.
 *
 * Fragment descriptor:
 * flags:	Descriptor type
 * len:i	length of this fragment
 * addr:	low bytes of DMA address क्रम this part of the packet
 * addrHi:	hi bytes of DMA address क्रम this part of the packet
 * processFlags: must be zero
 *
 * TYPHOON_DESC_VALID is not mentioned in their करोcs, but their Linux
 * driver uses it.
 */
काष्ठा tx_desc अणु
	u8  flags;
#घोषणा TYPHOON_TYPE_MASK	0x07
#घोषणा 	TYPHOON_FRAG_DESC	0x00
#घोषणा 	TYPHOON_TX_DESC		0x01
#घोषणा 	TYPHOON_CMD_DESC	0x02
#घोषणा 	TYPHOON_OPT_DESC	0x03
#घोषणा 	TYPHOON_RX_DESC		0x04
#घोषणा 	TYPHOON_RESP_DESC	0x05
#घोषणा TYPHOON_OPT_TYPE_MASK	0xf0
#घोषणा 	TYPHOON_OPT_IPSEC	0x00
#घोषणा 	TYPHOON_OPT_TCP_SEG	0x10
#घोषणा TYPHOON_CMD_RESPOND	0x40
#घोषणा TYPHOON_RESP_ERROR	0x40
#घोषणा TYPHOON_RX_ERROR	0x40
#घोषणा TYPHOON_DESC_VALID	0x80
	u8  numDesc;
	__le16 len;
	जोड़ अणु
		काष्ठा अणु
			__le32 addr;
			__le32 addrHi;
		पूर्ण frag;
		u64 tx_addr;	/* opaque क्रम hardware, क्रम TX_DESC */
	पूर्ण;
	__le32 processFlags;
#घोषणा TYPHOON_TX_PF_NO_CRC		cpu_to_le32(0x00000001)
#घोषणा TYPHOON_TX_PF_IP_CHKSUM		cpu_to_le32(0x00000002)
#घोषणा TYPHOON_TX_PF_TCP_CHKSUM	cpu_to_le32(0x00000004)
#घोषणा TYPHOON_TX_PF_TCP_SEGMENT	cpu_to_le32(0x00000008)
#घोषणा TYPHOON_TX_PF_INSERT_VLAN	cpu_to_le32(0x00000010)
#घोषणा TYPHOON_TX_PF_IPSEC		cpu_to_le32(0x00000020)
#घोषणा TYPHOON_TX_PF_VLAN_PRIORITY	cpu_to_le32(0x00000040)
#घोषणा TYPHOON_TX_PF_UDP_CHKSUM	cpu_to_le32(0x00000080)
#घोषणा TYPHOON_TX_PF_PAD_FRAME		cpu_to_le32(0x00000100)
#घोषणा TYPHOON_TX_PF_RESERVED		cpu_to_le32(0x00000e00)
#घोषणा TYPHOON_TX_PF_VLAN_MASK		cpu_to_le32(0x0ffff000)
#घोषणा TYPHOON_TX_PF_INTERNAL		cpu_to_le32(0xf0000000)
#घोषणा TYPHOON_TX_PF_VLAN_TAG_SHIFT	12
पूर्ण __packed;

/* The TCP Segmentation offload option descriptor
 *
 * flags:	descriptor type
 * numDesc:	must be 1
 * mss_flags:	bits 0-11 (little endian) are MSS, 12 is first TSO descriptor
 *			13 is list TSO descriptor, set both अगर only one TSO
 * respAddrLo:	low bytes of address of the bytesTx field of this descriptor
 * bytesTx:	total number of bytes in this TSO request
 * status:	0 on completion
 */
काष्ठा tcpopt_desc अणु
	u8  flags;
	u8  numDesc;
	__le16 mss_flags;
#घोषणा TYPHOON_TSO_FIRST		cpu_to_le16(0x1000)
#घोषणा TYPHOON_TSO_LAST		cpu_to_le16(0x2000)
	__le32 respAddrLo;
	__le32 bytesTx;
	__le32 status;
पूर्ण __packed;

/* The IPSEC Offload descriptor
 *
 * flags:	descriptor type
 * numDesc:	must be 1
 * ipsecFlags:	bit 0: 0 -- generate IV, 1 -- use supplied IV
 * sa1, sa2:	Security Association IDs क्रम this packet
 * reserved:	set to 0
 */
काष्ठा ipsec_desc अणु
	u8  flags;
	u8  numDesc;
	__le16 ipsecFlags;
#घोषणा TYPHOON_IPSEC_GEN_IV	cpu_to_le16(0x0000)
#घोषणा TYPHOON_IPSEC_USE_IV	cpu_to_le16(0x0001)
	__le32 sa1;
	__le32 sa2;
	__le32 reserved;
पूर्ण __packed;

/* The Typhoon receive descriptor (Updated by NIC)
 *
 * flags:         Descriptor type, error indication
 * numDesc:       Always zero
 * frameLen:      the size of the packet received
 * addr:          low 32 bytes of the भव addr passed in क्रम this buffer
 * addrHi:        high 32 bytes of the भव addr passed in क्रम this buffer
 * rxStatus:      Error अगर set in flags, otherwise result of offload processing
 * filterResults: results of filtering on packet, not used
 * ipsecResults:  Results of IPSEC processing
 * vlanTag:       the 801.2q TCI from the packet
 */
काष्ठा rx_desc अणु
	u8  flags;
	u8  numDesc;
	__le16 frameLen;
	u32 addr;	/* opaque, comes from virtAddr */
	u32 addrHi;	/* opaque, comes from virtAddrHi */
	__le32 rxStatus;
#घोषणा TYPHOON_RX_ERR_INTERNAL		cpu_to_le32(0x00000000)
#घोषणा TYPHOON_RX_ERR_FIFO_UNDERRUN	cpu_to_le32(0x00000001)
#घोषणा TYPHOON_RX_ERR_BAD_SSD		cpu_to_le32(0x00000002)
#घोषणा TYPHOON_RX_ERR_RUNT		cpu_to_le32(0x00000003)
#घोषणा TYPHOON_RX_ERR_CRC		cpu_to_le32(0x00000004)
#घोषणा TYPHOON_RX_ERR_OVERSIZE		cpu_to_le32(0x00000005)
#घोषणा TYPHOON_RX_ERR_ALIGN		cpu_to_le32(0x00000006)
#घोषणा TYPHOON_RX_ERR_DRIBBLE		cpu_to_le32(0x00000007)
#घोषणा TYPHOON_RX_PROTO_MASK		cpu_to_le32(0x00000003)
#घोषणा TYPHOON_RX_PROTO_UNKNOWN	cpu_to_le32(0x00000000)
#घोषणा TYPHOON_RX_PROTO_IP		cpu_to_le32(0x00000001)
#घोषणा TYPHOON_RX_PROTO_IPX		cpu_to_le32(0x00000002)
#घोषणा TYPHOON_RX_VLAN			cpu_to_le32(0x00000004)
#घोषणा TYPHOON_RX_IP_FRAG		cpu_to_le32(0x00000008)
#घोषणा TYPHOON_RX_IPSEC		cpu_to_le32(0x00000010)
#घोषणा TYPHOON_RX_IP_CHK_FAIL		cpu_to_le32(0x00000020)
#घोषणा TYPHOON_RX_TCP_CHK_FAIL		cpu_to_le32(0x00000040)
#घोषणा TYPHOON_RX_UDP_CHK_FAIL		cpu_to_le32(0x00000080)
#घोषणा TYPHOON_RX_IP_CHK_GOOD		cpu_to_le32(0x00000100)
#घोषणा TYPHOON_RX_TCP_CHK_GOOD		cpu_to_le32(0x00000200)
#घोषणा TYPHOON_RX_UDP_CHK_GOOD		cpu_to_le32(0x00000400)
	__le16 filterResults;
#घोषणा TYPHOON_RX_FILTER_MASK		cpu_to_le16(0x7fff)
#घोषणा TYPHOON_RX_FILTERED		cpu_to_le16(0x8000)
	__le16 ipsecResults;
#घोषणा TYPHOON_RX_OUTER_AH_GOOD	cpu_to_le16(0x0001)
#घोषणा TYPHOON_RX_OUTER_ESP_GOOD	cpu_to_le16(0x0002)
#घोषणा TYPHOON_RX_INNER_AH_GOOD	cpu_to_le16(0x0004)
#घोषणा TYPHOON_RX_INNER_ESP_GOOD	cpu_to_le16(0x0008)
#घोषणा TYPHOON_RX_OUTER_AH_FAIL	cpu_to_le16(0x0010)
#घोषणा TYPHOON_RX_OUTER_ESP_FAIL	cpu_to_le16(0x0020)
#घोषणा TYPHOON_RX_INNER_AH_FAIL	cpu_to_le16(0x0040)
#घोषणा TYPHOON_RX_INNER_ESP_FAIL	cpu_to_le16(0x0080)
#घोषणा TYPHOON_RX_UNKNOWN_SA		cpu_to_le16(0x0100)
#घोषणा TYPHOON_RX_ESP_FORMAT_ERR	cpu_to_le16(0x0200)
	__be32 vlanTag;
पूर्ण __packed;

/* The Typhoon मुक्त buffer descriptor, used to give a buffer to the NIC
 *
 * physAddr:    low 32 bits of the bus address of the buffer
 * physAddrHi:  high 32 bits of the bus address of the buffer, always zero
 * virtAddr:    low 32 bits of the skb address
 * virtAddrHi:  high 32 bits of the skb address, always zero
 *
 * the virt* address is basically two 32 bit cookies, just passed back
 * from the NIC
 */
काष्ठा rx_मुक्त अणु
	__le32 physAddr;
	__le32 physAddrHi;
	u32 virtAddr;
	u32 virtAddrHi;
पूर्ण __packed;

/* The Typhoon command descriptor, used क्रम commands and responses
 *
 * flags:   descriptor type
 * numDesc: number of descriptors following in this command/response,
 *				ie, zero क्रम a one descriptor command
 * cmd:     the command
 * seqNo:   sequence number (unused)
 * parm1:   use varies by command
 * parm2:   use varies by command
 * parm3:   use varies by command
 */
काष्ठा cmd_desc अणु
	u8  flags;
	u8  numDesc;
	__le16 cmd;
#घोषणा TYPHOON_CMD_TX_ENABLE		cpu_to_le16(0x0001)
#घोषणा TYPHOON_CMD_TX_DISABLE		cpu_to_le16(0x0002)
#घोषणा TYPHOON_CMD_RX_ENABLE		cpu_to_le16(0x0003)
#घोषणा TYPHOON_CMD_RX_DISABLE		cpu_to_le16(0x0004)
#घोषणा TYPHOON_CMD_SET_RX_FILTER	cpu_to_le16(0x0005)
#घोषणा TYPHOON_CMD_READ_STATS		cpu_to_le16(0x0007)
#घोषणा TYPHOON_CMD_XCVR_SELECT		cpu_to_le16(0x0013)
#घोषणा TYPHOON_CMD_SET_MAX_PKT_SIZE	cpu_to_le16(0x001a)
#घोषणा TYPHOON_CMD_READ_MEDIA_STATUS	cpu_to_le16(0x001b)
#घोषणा TYPHOON_CMD_GOTO_SLEEP		cpu_to_le16(0x0023)
#घोषणा TYPHOON_CMD_SET_MULTICAST_HASH	cpu_to_le16(0x0025)
#घोषणा TYPHOON_CMD_SET_MAC_ADDRESS	cpu_to_le16(0x0026)
#घोषणा TYPHOON_CMD_READ_MAC_ADDRESS	cpu_to_le16(0x0027)
#घोषणा TYPHOON_CMD_VLAN_TYPE_WRITE	cpu_to_le16(0x002b)
#घोषणा TYPHOON_CMD_CREATE_SA		cpu_to_le16(0x0034)
#घोषणा TYPHOON_CMD_DELETE_SA		cpu_to_le16(0x0035)
#घोषणा TYPHOON_CMD_READ_VERSIONS	cpu_to_le16(0x0043)
#घोषणा TYPHOON_CMD_IRQ_COALESCE_CTRL	cpu_to_le16(0x0045)
#घोषणा TYPHOON_CMD_ENABLE_WAKE_EVENTS	cpu_to_le16(0x0049)
#घोषणा TYPHOON_CMD_SET_OFFLOAD_TASKS	cpu_to_le16(0x004f)
#घोषणा TYPHOON_CMD_HELLO_RESP		cpu_to_le16(0x0057)
#घोषणा TYPHOON_CMD_HALT		cpu_to_le16(0x005d)
#घोषणा TYPHOON_CMD_READ_IPSEC_INFO	cpu_to_le16(0x005e)
#घोषणा TYPHOON_CMD_GET_IPSEC_ENABLE	cpu_to_le16(0x0067)
#घोषणा TYPHOON_CMD_GET_CMD_LVL		cpu_to_le16(0x0069)
	u16 seqNo;
	__le16 parm1;
	__le32 parm2;
	__le32 parm3;
पूर्ण __packed;

/* The Typhoon response descriptor, see command descriptor क्रम details
 */
काष्ठा resp_desc अणु
	u8  flags;
	u8  numDesc;
	__le16 cmd;
	__le16 seqNo;
	__le16 parm1;
	__le32 parm2;
	__le32 parm3;
पूर्ण __packed;

#घोषणा INIT_COMMAND_NO_RESPONSE(x, command)				\
	करो अणु काष्ठा cmd_desc *_ptr = (x);				\
		स_रखो(_ptr, 0, माप(काष्ठा cmd_desc));		\
		_ptr->flags = TYPHOON_CMD_DESC | TYPHOON_DESC_VALID;	\
		_ptr->cmd = command;					\
	पूर्ण जबतक (0)

/* We set seqNo to 1 अगर we're expecting a response from this command */
#घोषणा INIT_COMMAND_WITH_RESPONSE(x, command)				\
	करो अणु काष्ठा cmd_desc *_ptr = (x);				\
		स_रखो(_ptr, 0, माप(काष्ठा cmd_desc));		\
		_ptr->flags = TYPHOON_CMD_RESPOND | TYPHOON_CMD_DESC;	\
		_ptr->flags |= TYPHOON_DESC_VALID; 			\
		_ptr->cmd = command;					\
		_ptr->seqNo = 1;					\
	पूर्ण जबतक (0)

/* TYPHOON_CMD_SET_RX_FILTER filter bits (cmd.parm1)
 */
#घोषणा TYPHOON_RX_FILTER_सूचीECTED	cpu_to_le16(0x0001)
#घोषणा TYPHOON_RX_FILTER_ALL_MCAST	cpu_to_le16(0x0002)
#घोषणा TYPHOON_RX_FILTER_BROADCAST	cpu_to_le16(0x0004)
#घोषणा TYPHOON_RX_FILTER_PROMISCOUS	cpu_to_le16(0x0008)
#घोषणा TYPHOON_RX_FILTER_MCAST_HASH	cpu_to_le16(0x0010)

/* TYPHOON_CMD_READ_STATS response क्रमmat
 */
काष्ठा stats_resp अणु
	u8  flags;
	u8  numDesc;
	__le16 cmd;
	__le16 seqNo;
	__le16 unused;
	__le32 txPackets;
	__le64 txBytes;
	__le32 txDeferred;
	__le32 txLateCollisions;
	__le32 txCollisions;
	__le32 txCarrierLost;
	__le32 txMultipleCollisions;
	__le32 txExcessiveCollisions;
	__le32 txFअगरoUnderruns;
	__le32 txMulticastTxOverflows;
	__le32 txFiltered;
	__le32 rxPacketsGood;
	__le64 rxBytesGood;
	__le32 rxFअगरoOverruns;
	__le32 BadSSD;
	__le32 rxCrcErrors;
	__le32 rxOversized;
	__le32 rxBroadcast;
	__le32 rxMulticast;
	__le32 rxOverflow;
	__le32 rxFiltered;
	__le32 linkStatus;
#घोषणा TYPHOON_LINK_STAT_MASK		cpu_to_le32(0x00000001)
#घोषणा TYPHOON_LINK_GOOD		cpu_to_le32(0x00000001)
#घोषणा TYPHOON_LINK_BAD		cpu_to_le32(0x00000000)
#घोषणा TYPHOON_LINK_SPEED_MASK		cpu_to_le32(0x00000002)
#घोषणा TYPHOON_LINK_100MBPS		cpu_to_le32(0x00000002)
#घोषणा TYPHOON_LINK_10MBPS		cpu_to_le32(0x00000000)
#घोषणा TYPHOON_LINK_DUPLEX_MASK	cpu_to_le32(0x00000004)
#घोषणा TYPHOON_LINK_FULL_DUPLEX	cpu_to_le32(0x00000004)
#घोषणा TYPHOON_LINK_HALF_DUPLEX	cpu_to_le32(0x00000000)
	__le32 unused2;
	__le32 unused3;
पूर्ण __packed;

/* TYPHOON_CMD_XCVR_SELECT xcvr values (resp.parm1)
 */
#घोषणा TYPHOON_XCVR_10HALF	cpu_to_le16(0x0000)
#घोषणा TYPHOON_XCVR_10FULL	cpu_to_le16(0x0001)
#घोषणा TYPHOON_XCVR_100HALF	cpu_to_le16(0x0002)
#घोषणा TYPHOON_XCVR_100FULL	cpu_to_le16(0x0003)
#घोषणा TYPHOON_XCVR_AUTONEG	cpu_to_le16(0x0004)

/* TYPHOON_CMD_READ_MEDIA_STATUS (resp.parm1)
 */
#घोषणा TYPHOON_MEDIA_STAT_CRC_STRIP_DISABLE	cpu_to_le16(0x0004)
#घोषणा TYPHOON_MEDIA_STAT_COLLISION_DETECT	cpu_to_le16(0x0010)
#घोषणा TYPHOON_MEDIA_STAT_CARRIER_SENSE	cpu_to_le16(0x0020)
#घोषणा TYPHOON_MEDIA_STAT_POLARITY_REV		cpu_to_le16(0x0400)
#घोषणा TYPHOON_MEDIA_STAT_NO_LINK		cpu_to_le16(0x0800)

/* TYPHOON_CMD_SET_MULTICAST_HASH enable values (cmd.parm1)
 */
#घोषणा TYPHOON_MCAST_HASH_DISABLE	cpu_to_le16(0x0000)
#घोषणा TYPHOON_MCAST_HASH_ENABLE	cpu_to_le16(0x0001)
#घोषणा TYPHOON_MCAST_HASH_SET		cpu_to_le16(0x0002)

/* TYPHOON_CMD_CREATE_SA descriptor and settings
 */
काष्ठा sa_descriptor अणु
	u8  flags;
	u8  numDesc;
	u16 cmd;
	u16 seqNo;
	u16 mode;
#घोषणा TYPHOON_SA_MODE_शून्य		cpu_to_le16(0x0000)
#घोषणा TYPHOON_SA_MODE_AH		cpu_to_le16(0x0001)
#घोषणा TYPHOON_SA_MODE_ESP		cpu_to_le16(0x0002)
	u8  hashFlags;
#घोषणा TYPHOON_SA_HASH_ENABLE		0x01
#घोषणा TYPHOON_SA_HASH_SHA1		0x02
#घोषणा TYPHOON_SA_HASH_MD5		0x04
	u8  direction;
#घोषणा TYPHOON_SA_सूची_RX		0x00
#घोषणा TYPHOON_SA_सूची_TX		0x01
	u8  encryptionFlags;
#घोषणा TYPHOON_SA_ENCRYPT_ENABLE	0x01
#घोषणा TYPHOON_SA_ENCRYPT_DES		0x02
#घोषणा TYPHOON_SA_ENCRYPT_3DES		0x00
#घोषणा TYPHOON_SA_ENCRYPT_3DES_2KEY	0x00
#घोषणा TYPHOON_SA_ENCRYPT_3DES_3KEY	0x04
#घोषणा TYPHOON_SA_ENCRYPT_CBC		0x08
#घोषणा TYPHOON_SA_ENCRYPT_ECB		0x00
	u8  specअगरyIndex;
#घोषणा TYPHOON_SA_SPECIFY_INDEX	0x01
#घोषणा TYPHOON_SA_GENERATE_INDEX	0x00
	u32 SPI;
	u32 destAddr;
	u32 destMask;
	u8  पूर्णांकegKey[20];
	u8  confKey[24];
	u32 index;
	u32 unused;
	u32 unused2;
पूर्ण __packed;

/* TYPHOON_CMD_SET_OFFLOAD_TASKS bits (cmd.parm2 (Tx) & cmd.parm3 (Rx))
 * This is all क्रम IPv4.
 */
#घोषणा TYPHOON_OFFLOAD_TCP_CHKSUM	cpu_to_le32(0x00000002)
#घोषणा TYPHOON_OFFLOAD_UDP_CHKSUM	cpu_to_le32(0x00000004)
#घोषणा TYPHOON_OFFLOAD_IP_CHKSUM	cpu_to_le32(0x00000008)
#घोषणा TYPHOON_OFFLOAD_IPSEC		cpu_to_le32(0x00000010)
#घोषणा TYPHOON_OFFLOAD_BCAST_THROTTLE	cpu_to_le32(0x00000020)
#घोषणा TYPHOON_OFFLOAD_DHCP_PREVENT	cpu_to_le32(0x00000040)
#घोषणा TYPHOON_OFFLOAD_VLAN		cpu_to_le32(0x00000080)
#घोषणा TYPHOON_OFFLOAD_FILTERING	cpu_to_le32(0x00000100)
#घोषणा TYPHOON_OFFLOAD_TCP_SEGMENT	cpu_to_le32(0x00000200)

/* TYPHOON_CMD_ENABLE_WAKE_EVENTS bits (cmd.parm1)
 */
#घोषणा TYPHOON_WAKE_MAGIC_PKT		cpu_to_le16(0x01)
#घोषणा TYPHOON_WAKE_LINK_EVENT		cpu_to_le16(0x02)
#घोषणा TYPHOON_WAKE_ICMP_ECHO		cpu_to_le16(0x04)
#घोषणा TYPHOON_WAKE_ARP		cpu_to_le16(0x08)

/* These are used to load the firmware image on the NIC
 */
काष्ठा typhoon_file_header अणु
	u8  tag[8];
	__le32 version;
	__le32 numSections;
	__le32 startAddr;
	__le32 hmacDigest[5];
पूर्ण __packed;

काष्ठा typhoon_section_header अणु
	__le32 len;
	u16 checksum;
	u16 reserved;
	__le32 startAddr;
पूर्ण __packed;

/* The Typhoon Register offsets
 */
#घोषणा TYPHOON_REG_SOFT_RESET			0x00
#घोषणा TYPHOON_REG_INTR_STATUS			0x04
#घोषणा TYPHOON_REG_INTR_ENABLE			0x08
#घोषणा TYPHOON_REG_INTR_MASK			0x0c
#घोषणा TYPHOON_REG_SELF_INTERRUPT		0x10
#घोषणा TYPHOON_REG_HOST2ARM7			0x14
#घोषणा TYPHOON_REG_HOST2ARM6			0x18
#घोषणा TYPHOON_REG_HOST2ARM5			0x1c
#घोषणा TYPHOON_REG_HOST2ARM4			0x20
#घोषणा TYPHOON_REG_HOST2ARM3			0x24
#घोषणा TYPHOON_REG_HOST2ARM2			0x28
#घोषणा TYPHOON_REG_HOST2ARM1			0x2c
#घोषणा TYPHOON_REG_HOST2ARM0			0x30
#घोषणा TYPHOON_REG_ARM2HOST3			0x34
#घोषणा TYPHOON_REG_ARM2HOST2			0x38
#घोषणा TYPHOON_REG_ARM2HOST1			0x3c
#घोषणा TYPHOON_REG_ARM2HOST0			0x40

#घोषणा TYPHOON_REG_BOOT_DATA_LO		TYPHOON_REG_HOST2ARM5
#घोषणा TYPHOON_REG_BOOT_DATA_HI		TYPHOON_REG_HOST2ARM4
#घोषणा TYPHOON_REG_BOOT_DEST_ADDR		TYPHOON_REG_HOST2ARM3
#घोषणा TYPHOON_REG_BOOT_CHECKSUM		TYPHOON_REG_HOST2ARM2
#घोषणा TYPHOON_REG_BOOT_LENGTH			TYPHOON_REG_HOST2ARM1

#घोषणा TYPHOON_REG_DOWNLOAD_BOOT_ADDR		TYPHOON_REG_HOST2ARM1
#घोषणा TYPHOON_REG_DOWNLOAD_HMAC_0		TYPHOON_REG_HOST2ARM2
#घोषणा TYPHOON_REG_DOWNLOAD_HMAC_1		TYPHOON_REG_HOST2ARM3
#घोषणा TYPHOON_REG_DOWNLOAD_HMAC_2		TYPHOON_REG_HOST2ARM4
#घोषणा TYPHOON_REG_DOWNLOAD_HMAC_3		TYPHOON_REG_HOST2ARM5
#घोषणा TYPHOON_REG_DOWNLOAD_HMAC_4		TYPHOON_REG_HOST2ARM6

#घोषणा TYPHOON_REG_BOOT_RECORD_ADDR_HI		TYPHOON_REG_HOST2ARM2
#घोषणा TYPHOON_REG_BOOT_RECORD_ADDR_LO		TYPHOON_REG_HOST2ARM1

#घोषणा TYPHOON_REG_TX_LO_READY			TYPHOON_REG_HOST2ARM3
#घोषणा TYPHOON_REG_CMD_READY			TYPHOON_REG_HOST2ARM2
#घोषणा TYPHOON_REG_TX_HI_READY			TYPHOON_REG_HOST2ARM1

#घोषणा TYPHOON_REG_COMMAND			TYPHOON_REG_HOST2ARM0
#घोषणा TYPHOON_REG_HEARTBEAT			TYPHOON_REG_ARM2HOST3
#घोषणा TYPHOON_REG_STATUS			TYPHOON_REG_ARM2HOST0

/* 3XP Reset values (TYPHOON_REG_SOFT_RESET)
 */
#घोषणा TYPHOON_RESET_ALL	0x7f
#घोषणा TYPHOON_RESET_NONE	0x00

/* 3XP irq bits (TYPHOON_REG_INTRअणुSTATUS,ENABLE,MASKपूर्ण)
 *
 * Some of these came from OpenBSD, as the 3Com करोcs have it wrong
 * (INTR_SELF) or करोn't list it at all (INTR_*_ABORT)
 *
 * Enabling irqs on the Heartbeat reg (ArmToHost3) माला_लो you an irq
 * about every 8ms, so करोn't करो it.
 */
#घोषणा TYPHOON_INTR_HOST_INT		0x00000001
#घोषणा TYPHOON_INTR_ARM2HOST0		0x00000002
#घोषणा TYPHOON_INTR_ARM2HOST1		0x00000004
#घोषणा TYPHOON_INTR_ARM2HOST2		0x00000008
#घोषणा TYPHOON_INTR_ARM2HOST3		0x00000010
#घोषणा TYPHOON_INTR_DMA0		0x00000020
#घोषणा TYPHOON_INTR_DMA1		0x00000040
#घोषणा TYPHOON_INTR_DMA2		0x00000080
#घोषणा TYPHOON_INTR_DMA3		0x00000100
#घोषणा TYPHOON_INTR_MASTER_ABORT	0x00000200
#घोषणा TYPHOON_INTR_TARGET_ABORT	0x00000400
#घोषणा TYPHOON_INTR_SELF		0x00000800
#घोषणा TYPHOON_INTR_RESERVED		0xfffff000

#घोषणा TYPHOON_INTR_BOOTCMD		TYPHOON_INTR_ARM2HOST0

#घोषणा TYPHOON_INTR_ENABLE_ALL		0xffffffef
#घोषणा TYPHOON_INTR_ALL		0xffffffff
#घोषणा TYPHOON_INTR_NONE		0x00000000

/* The commands क्रम the 3XP chip (TYPHOON_REG_COMMAND)
 */
#घोषणा TYPHOON_BOOTCMD_BOOT			0x00
#घोषणा TYPHOON_BOOTCMD_WAKEUP			0xfa
#घोषणा TYPHOON_BOOTCMD_DNLD_COMPLETE		0xfb
#घोषणा TYPHOON_BOOTCMD_SEG_AVAILABLE		0xfc
#घोषणा TYPHOON_BOOTCMD_RUNTIME_IMAGE		0xfd
#घोषणा TYPHOON_BOOTCMD_REG_BOOT_RECORD		0xff

/* 3XP Status values (TYPHOON_REG_STATUS)
 */
#घोषणा TYPHOON_STATUS_WAITING_FOR_BOOT		0x07
#घोषणा TYPHOON_STATUS_SECOND_INIT		0x08
#घोषणा TYPHOON_STATUS_RUNNING			0x09
#घोषणा TYPHOON_STATUS_WAITING_FOR_HOST		0x0d
#घोषणा TYPHOON_STATUS_WAITING_FOR_SEGMENT	0x10
#घोषणा TYPHOON_STATUS_SLEEPING			0x11
#घोषणा TYPHOON_STATUS_HALTED			0x14
