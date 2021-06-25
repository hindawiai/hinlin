<शैली गुरु>
/*
 * llc_input.c - Minimal input path क्रम LLC
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/net_namespace.h>
#समावेश <net/llc.h>
#समावेश <net/llc_pdu.h>
#समावेश <net/llc_sap.h>

#अगर 0
#घोषणा dprपूर्णांकk(args...) prपूर्णांकk(KERN_DEBUG args)
#अन्यथा
#घोषणा dprपूर्णांकk(args...)
#पूर्ण_अगर

/*
 * Packet handler क्रम the station, रेजिस्टरable because in the minimal
 * LLC core that is taking shape only the very minimal subset of LLC that
 * is needed क्रम things like IPX, Appletalk, etc will stay, with all the
 * rest in the llc1 and llc2 modules.
 */
अटल व्योम (*llc_station_handler)(काष्ठा sk_buff *skb);

/*
 * Packet handlers क्रम LLC_DEST_SAP and LLC_DEST_CONN.
 */
अटल व्योम (*llc_type_handlers[2])(काष्ठा llc_sap *sap,
				    काष्ठा sk_buff *skb);

व्योम llc_add_pack(पूर्णांक type, व्योम (*handler)(काष्ठा llc_sap *sap,
					    काष्ठा sk_buff *skb))
अणु
	smp_wmb(); /* ensure initialisation is complete beक्रमe it's called */
	अगर (type == LLC_DEST_SAP || type == LLC_DEST_CONN)
		llc_type_handlers[type - 1] = handler;
पूर्ण

व्योम llc_हटाओ_pack(पूर्णांक type)
अणु
	अगर (type == LLC_DEST_SAP || type == LLC_DEST_CONN)
		llc_type_handlers[type - 1] = शून्य;
	synchronize_net();
पूर्ण

व्योम llc_set_station_handler(व्योम (*handler)(काष्ठा sk_buff *skb))
अणु
	/* Ensure initialisation is complete beक्रमe it's called */
	अगर (handler)
		smp_wmb();

	llc_station_handler = handler;

	अगर (!handler)
		synchronize_net();
पूर्ण

/**
 *	llc_pdu_type - वापसs which LLC component must handle क्रम PDU
 *	@skb: input skb
 *
 *	This function वापसs which LLC component must handle this PDU.
 */
अटल __अंतरभूत__ पूर्णांक llc_pdu_type(काष्ठा sk_buff *skb)
अणु
	पूर्णांक type = LLC_DEST_CONN; /* I-PDU or S-PDU type */
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	अगर ((pdu->ctrl_1 & LLC_PDU_TYPE_MASK) != LLC_PDU_TYPE_U)
		जाओ out;
	चयन (LLC_U_PDU_CMD(pdu)) अणु
	हाल LLC_1_PDU_CMD_XID:
	हाल LLC_1_PDU_CMD_UI:
	हाल LLC_1_PDU_CMD_TEST:
		type = LLC_DEST_SAP;
		अवरोध;
	हाल LLC_2_PDU_CMD_SABME:
	हाल LLC_2_PDU_CMD_DISC:
	हाल LLC_2_PDU_RSP_UA:
	हाल LLC_2_PDU_RSP_DM:
	हाल LLC_2_PDU_RSP_FRMR:
		अवरोध;
	शेष:
		type = LLC_DEST_INVALID;
		अवरोध;
	पूर्ण
out:
	वापस type;
पूर्ण

/**
 *	llc_fixup_skb - initializes skb poपूर्णांकers
 *	@skb: This argument poपूर्णांकs to incoming skb
 *
 *	Initializes पूर्णांकernal skb poपूर्णांकer to start of network layer by deriving
 *	length of LLC header; finds length of LLC control field in LLC header
 *	by looking at the two lowest-order bits of the first control field
 *	byte; field is either 3 or 4 bytes दीर्घ.
 */
अटल अंतरभूत पूर्णांक llc_fixup_skb(काष्ठा sk_buff *skb)
अणु
	u8 llc_len = 2;
	काष्ठा llc_pdu_un *pdu;

	अगर (unlikely(!pskb_may_pull(skb, माप(*pdu))))
		वापस 0;

	pdu = (काष्ठा llc_pdu_un *)skb->data;
	अगर ((pdu->ctrl_1 & LLC_PDU_TYPE_MASK) == LLC_PDU_TYPE_U)
		llc_len = 1;
	llc_len += 2;

	अगर (unlikely(!pskb_may_pull(skb, llc_len)))
		वापस 0;

	skb->transport_header += llc_len;
	skb_pull(skb, llc_len);
	अगर (skb->protocol == htons(ETH_P_802_2)) अणु
		__be16 pdulen = eth_hdr(skb)->h_proto;
		s32 data_size = ntohs(pdulen) - llc_len;

		अगर (data_size < 0 ||
		    !pskb_may_pull(skb, data_size))
			वापस 0;
		अगर (unlikely(pskb_trim_rcsum(skb, data_size)))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	llc_rcv - 802.2 entry poपूर्णांक from net lower layers
 *	@skb: received pdu
 *	@dev: device that receive pdu
 *	@pt: packet type
 *	@orig_dev: the original receive net device
 *
 *	When the प्रणाली receives a 802.2 frame this function is called. It
 *	checks SAP and connection of received pdu and passes frame to
 *	llc_अणुstation,sap,connपूर्ण_rcv क्रम sending to proper state machine. If
 *	the frame is related to a busy connection (a connection is sending
 *	data now), it queues this frame in the connection's backlog.
 */
पूर्णांक llc_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
	    काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा llc_sap *sap;
	काष्ठा llc_pdu_sn *pdu;
	पूर्णांक dest;
	पूर्णांक (*rcv)(काष्ठा sk_buff *, काष्ठा net_device *,
		   काष्ठा packet_type *, काष्ठा net_device *);
	व्योम (*sta_handler)(काष्ठा sk_buff *skb);
	व्योम (*sap_handler)(काष्ठा llc_sap *sap, काष्ठा sk_buff *skb);

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ drop;

	/*
	 * When the पूर्णांकerface is in promisc. mode, drop all the crap that it
	 * receives, करो not try to analyse it.
	 */
	अगर (unlikely(skb->pkt_type == PACKET_OTHERHOST)) अणु
		dprपूर्णांकk("%s: PACKET_OTHERHOST\n", __func__);
		जाओ drop;
	पूर्ण
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		जाओ out;
	अगर (unlikely(!llc_fixup_skb(skb)))
		जाओ drop;
	pdu = llc_pdu_sn_hdr(skb);
	अगर (unlikely(!pdu->dsap)) /* शून्य DSAP, refer to station */
	       जाओ handle_station;
	sap = llc_sap_find(pdu->dsap);
	अगर (unlikely(!sap)) अणु/* unknown SAP */
		dprपूर्णांकk("%s: llc_sap_find(%02X) failed!\n", __func__,
			pdu->dsap);
		जाओ drop;
	पूर्ण
	/*
	 * First the upper layer protocols that करोn't need the full
	 * LLC functionality
	 */
	rcv = rcu_dereference(sap->rcv_func);
	dest = llc_pdu_type(skb);
	sap_handler = dest ? READ_ONCE(llc_type_handlers[dest - 1]) : शून्य;
	अगर (unlikely(!sap_handler)) अणु
		अगर (rcv)
			rcv(skb, dev, pt, orig_dev);
		अन्यथा
			kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		अगर (rcv) अणु
			काष्ठा sk_buff *cskb = skb_clone(skb, GFP_ATOMIC);
			अगर (cskb)
				rcv(cskb, dev, pt, orig_dev);
		पूर्ण
		sap_handler(sap, skb);
	पूर्ण
	llc_sap_put(sap);
out:
	वापस 0;
drop:
	kमुक्त_skb(skb);
	जाओ out;
handle_station:
	sta_handler = READ_ONCE(llc_station_handler);
	अगर (!sta_handler)
		जाओ drop;
	sta_handler(skb);
	जाओ out;
पूर्ण

EXPORT_SYMBOL(llc_add_pack);
EXPORT_SYMBOL(llc_हटाओ_pack);
EXPORT_SYMBOL(llc_set_station_handler);
