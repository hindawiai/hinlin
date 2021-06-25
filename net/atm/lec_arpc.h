<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Lec arp cache
 *
 * Marko Kiiskila <mkiiskila@yahoo.com>
 */
#अगर_अघोषित _LEC_ARP_H_
#घोषणा _LEC_ARP_H_
#समावेश <linux/aपंचांग.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/aपंचांगlec.h>

काष्ठा lec_arp_table अणु
	काष्ठा hlist_node next;		/* Linked entry list */
	अचिन्हित अक्षर aपंचांग_addr[ATM_ESA_LEN];	/* Aपंचांग address */
	अचिन्हित अक्षर mac_addr[ETH_ALEN];	/* Mac address */
	पूर्णांक is_rdesc;			/* Mac address is a route descriptor */
	काष्ठा aपंचांग_vcc *vcc;		/* Vcc this entry is attached */
	काष्ठा aपंचांग_vcc *recv_vcc;	/* Vcc we receive data from */

	व्योम (*old_push) (काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
					/* Push that leads to daemon */

	व्योम (*old_recv_push) (काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
					/* Push that leads to daemon */

	अचिन्हित दीर्घ last_used;	/* For expiry */
	अचिन्हित दीर्घ बारtamp;	/* Used क्रम various बारtamping things:
					 * 1. FLUSH started
					 *    (status=ESI_FLUSH_PENDING)
					 * 2. Counting to
					 *    max_unknown_frame_समय
					 *    (status=ESI_ARP_PENDING||
					 *     status=ESI_VC_PENDING)
					 */
	अचिन्हित अक्षर no_tries;		/* No of बार arp retry has been tried */
	अचिन्हित अक्षर status;		/* Status of this entry */
	अचिन्हित लघु flags;		/* Flags क्रम this entry */
	अचिन्हित लघु packets_flooded;	/* Data packets flooded */
	अचिन्हित दीर्घ flush_tran_id;	/* Transaction id in flush protocol */
	काष्ठा समयr_list समयr;	/* Arping समयr */
	काष्ठा lec_priv *priv;		/* Poपूर्णांकer back */
	u8 *tlvs;
	u32 मापtlvs;			/*
					 * LANE2: Each MAC address can have TLVs
					 * associated with it.  मापtlvs tells
					 * the length of the tlvs array
					 */
	काष्ठा sk_buff_head tx_रुको;	/* रुको queue क्रम outgoing packets */
	refcount_t usage;		/* usage count */
पूर्ण;

/*
 * LANE2: Template tlv काष्ठा क्रम accessing
 * the tlvs in the lec_arp_table->tlvs array
 */
काष्ठा tlv अणु
	u32 type;
	u8 length;
	u8 value[255];
पूर्ण;

/* Status fields */
#घोषणा ESI_UNKNOWN 0		/*
				 * Next packet sent to this mac address
				 * causes ARP-request to be sent
				 */
#घोषणा ESI_ARP_PENDING 1	/*
				 * There is no ATM address associated with this
				 * 48-bit address.  The LE-ARP protocol is in
				 * progress.
				 */
#घोषणा ESI_VC_PENDING 2	/*
				 * There is a valid ATM address associated with
				 * this 48-bit address but there is no VC set
				 * up to that ATM address.  The संकेतing
				 * protocol is in process.
				 */
#घोषणा ESI_FLUSH_PENDING 4	/*
				 * The LEC has been notअगरied of the FLUSH_START
				 * status and it is assumed that the flush
				 * protocol is in process.
				 */
#घोषणा ESI_FORWARD_सूचीECT 5	/*
				 * Either the Path Switching Delay (C22) has
				 * elapsed or the LEC has notअगरied the Mapping
				 * that the flush protocol has completed.  In
				 * either हाल, it is safe to क्रमward packets
				 * to this address via the data direct VC.
				 */

/* Flag values */
#घोषणा LEC_REMOTE_FLAG      0x0001
#घोषणा LEC_PERMANENT_FLAG   0x0002

#पूर्ण_अगर /* _LEC_ARP_H_ */
