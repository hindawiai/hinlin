<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Lan Emulation client header file
 *
 * Marko Kiiskila <mkiiskila@yahoo.com>
 */

#अगर_अघोषित _LEC_H_
#घोषणा _LEC_H_

#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/aपंचांगlec.h>

#घोषणा LEC_HEADER_LEN 16

काष्ठा lecdatahdr_8023 अणु
	__be16 le_header;
	अचिन्हित अक्षर h_dest[ETH_ALEN];
	अचिन्हित अक्षर h_source[ETH_ALEN];
	__be16 h_type;
पूर्ण;

काष्ठा lecdatahdr_8025 अणु
	__be16 le_header;
	अचिन्हित अक्षर ac_pad;
	अचिन्हित अक्षर fc;
	अचिन्हित अक्षर h_dest[ETH_ALEN];
	अचिन्हित अक्षर h_source[ETH_ALEN];
पूर्ण;

#घोषणा LEC_MINIMUM_8023_SIZE   62
#घोषणा LEC_MINIMUM_8025_SIZE   16

/*
 * Operations that LANE2 capable device can करो. Two first functions
 * are used to make the device करो things. See spec 3.1.3 and 3.1.4.
 *
 * The third function is पूर्णांकended क्रम the MPOA component sitting on
 * top of the LANE device. The MPOA component assigns it's own function
 * to (*associate_indicator)() and the LANE device will use that
 * function to tell about TLVs it sees भग्नing through.
 *
 */
काष्ठा lane2_ops अणु
	पूर्णांक (*resolve) (काष्ठा net_device *dev, स्थिर u8 *dst_mac, पूर्णांक क्रमce,
			u8 **tlvs, u32 *मापtlvs);
	पूर्णांक (*associate_req) (काष्ठा net_device *dev, स्थिर u8 *lan_dst,
			      स्थिर u8 *tlvs, u32 मापtlvs);
	व्योम (*associate_indicator) (काष्ठा net_device *dev, स्थिर u8 *mac_addr,
				     स्थिर u8 *tlvs, u32 मापtlvs);
पूर्ण;

/*
 * ATM LAN Emulation supports both LLC & Dix Ethernet EtherType
 * frames.
 *
 * 1. Dix Ethernet EtherType frames encoded by placing EtherType
 *    field in h_type field. Data follows immediately after header.
 * 2. LLC Data frames whose total length, including LLC field and data,
 *    but not padding required to meet the minimum data frame length,
 *    is less than ETH_P_802_3_MIN MUST be encoded by placing that length
 *    in the h_type field. The LLC field follows header immediately.
 * 3. LLC data frames दीर्घer than this maximum MUST be encoded by placing
 *    the value 0 in the h_type field.
 *
 */

/* Hash table size */
#घोषणा LEC_ARP_TABLE_SIZE 16

काष्ठा lec_priv अणु
	अचिन्हित लघु lecid;			/* Lecid of this client */
	काष्ठा hlist_head lec_arp_empty_ones;
						/* Used क्रम storing VCC's that don't have a MAC address attached yet */
	काष्ठा hlist_head lec_arp_tables[LEC_ARP_TABLE_SIZE];
						/* Actual LE ARP table */
	काष्ठा hlist_head lec_no_क्रमward;
						/*
						 * Used क्रम storing VCC's (and क्रमward packets from) which are to
						 * age out by not using them to क्रमward packets.
						 * This is because to some LE clients there will be 2 VCCs. Only
						 * one of them माला_लो used.
						 */
	काष्ठा hlist_head mcast_fwds;
						/*
						 * With LANEv2 it is possible that BUS (or a special multicast server)
						 * establishes multiple Multicast Forward VCCs to us. This list
						 * collects all those VCCs. LANEv1 client has only one item in this
						 * list. These entries are not aged out.
						 */
	spinlock_t lec_arp_lock;
	काष्ठा aपंचांग_vcc *mcast_vcc;		/* Default Multicast Send VCC */
	काष्ठा aपंचांग_vcc *lecd;
	काष्ठा delayed_work lec_arp_work;	/* C10 */
	अचिन्हित पूर्णांक maximum_unknown_frame_count;
						/*
						 * Within the period of समय defined by this variable, the client will send
						 * no more than C10 frames to BUS क्रम a given unicast destination. (C11)
						 */
	अचिन्हित दीर्घ max_unknown_frame_समय;
						/*
						 * If no traffic has been sent in this vcc क्रम this period of समय,
						 * vcc will be torn करोwn (C12)
						 */
	अचिन्हित दीर्घ vcc_समयout_period;
						/*
						 * An LE Client MUST not retry an LE_ARP_REQUEST क्रम a
						 * given frame's LAN Destination more than maximum retry count बार,
						 * after the first LEC_ARP_REQUEST (C13)
						 */
	अचिन्हित लघु max_retry_count;
						/*
						 * Max समय the client will मुख्यtain an entry in its arp cache in
						 * असलence of a verअगरication of that relationship (C17)
						 */
	अचिन्हित दीर्घ aging_समय;
						/*
						 * Max समय the client will मुख्यtain an entry in cache when
						 * topology change flag is true (C18)
						 */
	अचिन्हित दीर्घ क्रमward_delay_समय;	/* Topology change flag (C19) */
	पूर्णांक topology_change;
						/*
						 * Max समय the client expects an LE_ARP_REQUEST/LE_ARP_RESPONSE
						 * cycle to take (C20)
						 */
	अचिन्हित दीर्घ arp_response_समय;
						/*
						 * Time limit ot रुको to receive an LE_FLUSH_RESPONSE after the
						 * LE_FLUSH_REQUEST has been sent beक्रमe taking recover action. (C21)
						 */
	अचिन्हित दीर्घ flush_समयout;
						/* The समय since sending a frame to the bus after which the
						 * LE Client may assume that the frame has been either discarded or
						 * delivered to the recipient (C22)
						 */
	अचिन्हित दीर्घ path_चयनing_delay;

	u8 *tlvs;				/* LANE2: TLVs are new */
	u32 मापtlvs;				/* The size of the tlv array in bytes */
	पूर्णांक lane_version;			/* LANE2 */
	पूर्णांक itfnum;				/* e.g. 2 क्रम lec2, 5 क्रम lec5 */
	काष्ठा lane2_ops *lane2_ops;		/* can be शून्य क्रम LANE v1 */
	पूर्णांक is_proxy;				/* bridge between ATM and Ethernet */
पूर्ण;

काष्ठा lec_vcc_priv अणु
	व्योम (*old_pop) (काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
	पूर्णांक xoff;
पूर्ण;

#घोषणा LEC_VCC_PRIV(vcc)	((काष्ठा lec_vcc_priv *)((vcc)->user_back))

#पूर्ण_अगर				/* _LEC_H_ */
