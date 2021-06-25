<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic HDLC support routines क्रम Linux
 * Frame Relay support
 *
 * Copyright (C) 1999 - 2006 Krzysztof Halasa <khc@pm.waw.pl>
 *

            Theory of PVC state

 DCE mode:

 (exist,new) -> 0,0 when "PVC create" or अगर "link unreliable"
         0,x -> 1,1 अगर "link reliable" when sending FULL STATUS
         1,1 -> 1,0 अगर received FULL STATUS ACK

 (active)    -> 0 when "ifconfig PVC down" or "link unreliable" or "PVC create"
             -> 1 when "PVC up" and (exist,new) = 1,0

 DTE mode:
 (exist,new,active) = FULL STATUS अगर "link reliable"
		    = 0, 0, 0 अगर "link unreliable"
 No LMI:
 active = खोलो and "link reliable"
 exist = new = not used

 CCITT LMI: ITU-T Q.933 Annex A
 ANSI LMI: ANSI T1.617 Annex D
 CISCO LMI: the original, aka "Gang of Four" LMI

*/

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/hdlc.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/poll.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>

#अघोषित DEBUG_PKT
#अघोषित DEBUG_ECN
#अघोषित DEBUG_LINK
#अघोषित DEBUG_PROTO
#अघोषित DEBUG_PVC

#घोषणा FR_UI			0x03
#घोषणा FR_PAD			0x00

#घोषणा NLPID_IP		0xCC
#घोषणा NLPID_IPV6		0x8E
#घोषणा NLPID_SNAP		0x80
#घोषणा NLPID_PAD		0x00
#घोषणा NLPID_CCITT_ANSI_LMI	0x08
#घोषणा NLPID_CISCO_LMI		0x09


#घोषणा LMI_CCITT_ANSI_DLCI	   0 /* LMI DLCI */
#घोषणा LMI_CISCO_DLCI		1023

#घोषणा LMI_CALLREF		0x00 /* Call Reference */
#घोषणा LMI_ANSI_LOCKSHIFT	0x95 /* ANSI locking shअगरt */
#घोषणा LMI_ANSI_CISCO_REPTYPE	0x01 /* report type */
#घोषणा LMI_CCITT_REPTYPE	0x51
#घोषणा LMI_ANSI_CISCO_ALIVE	0x03 /* keep alive */
#घोषणा LMI_CCITT_ALIVE		0x53
#घोषणा LMI_ANSI_CISCO_PVCSTAT	0x07 /* PVC status */
#घोषणा LMI_CCITT_PVCSTAT	0x57

#घोषणा LMI_FULLREP		0x00 /* full report  */
#घोषणा LMI_INTEGRITY		0x01 /* link पूर्णांकegrity report */
#घोषणा LMI_SINGLE		0x02 /* single PVC report */

#घोषणा LMI_STATUS_ENQUIRY      0x75
#घोषणा LMI_STATUS              0x7D /* reply */

#घोषणा LMI_REPT_LEN               1 /* report type element length */
#घोषणा LMI_INTEG_LEN              2 /* link पूर्णांकegrity element length */

#घोषणा LMI_CCITT_CISCO_LENGTH	  13 /* LMI frame lengths */
#घोषणा LMI_ANSI_LENGTH		  14


काष्ठा fr_hdr अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	अचिन्हित ea1:	1;
	अचिन्हित cr:	1;
	अचिन्हित dlcih:	6;

	अचिन्हित ea2:	1;
	अचिन्हित de:	1;
	अचिन्हित becn:	1;
	अचिन्हित fecn:	1;
	अचिन्हित dlcil:	4;
#अन्यथा
	अचिन्हित dlcih:	6;
	अचिन्हित cr:	1;
	अचिन्हित ea1:	1;

	अचिन्हित dlcil:	4;
	अचिन्हित fecn:	1;
	अचिन्हित becn:	1;
	अचिन्हित de:	1;
	अचिन्हित ea2:	1;
#पूर्ण_अगर
पूर्ण __packed;


काष्ठा pvc_device अणु
	काष्ठा net_device *frad;
	काष्ठा net_device *मुख्य;
	काष्ठा net_device *ether;	/* bridged Ethernet पूर्णांकerface	*/
	काष्ठा pvc_device *next;	/* Sorted in ascending DLCI order */
	पूर्णांक dlci;
	पूर्णांक खोलो_count;

	काष्ठा अणु
		अचिन्हित पूर्णांक new: 1;
		अचिन्हित पूर्णांक active: 1;
		अचिन्हित पूर्णांक exist: 1;
		अचिन्हित पूर्णांक deleted: 1;
		अचिन्हित पूर्णांक fecn: 1;
		अचिन्हित पूर्णांक becn: 1;
		अचिन्हित पूर्णांक bandwidth;	/* Cisco LMI reporting only */
	पूर्णstate;
पूर्ण;

काष्ठा frad_state अणु
	fr_proto settings;
	काष्ठा pvc_device *first_pvc;
	पूर्णांक dce_pvc_count;

	काष्ठा समयr_list समयr;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ last_poll;
	पूर्णांक reliable;
	पूर्णांक dce_changed;
	पूर्णांक request;
	पूर्णांक fullrep_sent;
	u32 last_errors; /* last errors bit list */
	u8 n391cnt;
	u8 txseq; /* TX sequence number */
	u8 rxseq; /* RX sequence number */
पूर्ण;


अटल पूर्णांक fr_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr);


अटल अंतरभूत u16 q922_to_dlci(u8 *hdr)
अणु
	वापस ((hdr[0] & 0xFC) << 2) | ((hdr[1] & 0xF0) >> 4);
पूर्ण


अटल अंतरभूत व्योम dlci_to_q922(u8 *hdr, u16 dlci)
अणु
	hdr[0] = (dlci >> 2) & 0xFC;
	hdr[1] = ((dlci << 4) & 0xF0) | 0x01;
पूर्ण


अटल अंतरभूत काष्ठा frad_state* state(hdlc_device *hdlc)
अणु
	वापस(काष्ठा frad_state *)(hdlc->state);
पूर्ण


अटल अंतरभूत काष्ठा pvc_device *find_pvc(hdlc_device *hdlc, u16 dlci)
अणु
	काष्ठा pvc_device *pvc = state(hdlc)->first_pvc;

	जबतक (pvc) अणु
		अगर (pvc->dlci == dlci)
			वापस pvc;
		अगर (pvc->dlci > dlci)
			वापस शून्य; /* the list is sorted */
		pvc = pvc->next;
	पूर्ण

	वापस शून्य;
पूर्ण


अटल काष्ठा pvc_device *add_pvc(काष्ठा net_device *dev, u16 dlci)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा pvc_device *pvc, **pvc_p = &state(hdlc)->first_pvc;

	जबतक (*pvc_p) अणु
		अगर ((*pvc_p)->dlci == dlci)
			वापस *pvc_p;
		अगर ((*pvc_p)->dlci > dlci)
			अवरोध;	/* the list is sorted */
		pvc_p = &(*pvc_p)->next;
	पूर्ण

	pvc = kzalloc(माप(*pvc), GFP_ATOMIC);
#अगर_घोषित DEBUG_PVC
	prपूर्णांकk(KERN_DEBUG "add_pvc: allocated pvc %p, frad %p\n", pvc, dev);
#पूर्ण_अगर
	अगर (!pvc)
		वापस शून्य;

	pvc->dlci = dlci;
	pvc->frad = dev;
	pvc->next = *pvc_p;	/* Put it in the chain */
	*pvc_p = pvc;
	वापस pvc;
पूर्ण


अटल अंतरभूत पूर्णांक pvc_is_used(काष्ठा pvc_device *pvc)
अणु
	वापस pvc->मुख्य || pvc->ether;
पूर्ण


अटल अंतरभूत व्योम pvc_carrier(पूर्णांक on, काष्ठा pvc_device *pvc)
अणु
	अगर (on) अणु
		अगर (pvc->मुख्य)
			अगर (!netअगर_carrier_ok(pvc->मुख्य))
				netअगर_carrier_on(pvc->मुख्य);
		अगर (pvc->ether)
			अगर (!netअगर_carrier_ok(pvc->ether))
				netअगर_carrier_on(pvc->ether);
	पूर्ण अन्यथा अणु
		अगर (pvc->मुख्य)
			अगर (netअगर_carrier_ok(pvc->मुख्य))
				netअगर_carrier_off(pvc->मुख्य);
		अगर (pvc->ether)
			अगर (netअगर_carrier_ok(pvc->ether))
				netअगर_carrier_off(pvc->ether);
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम delete_unused_pvcs(hdlc_device *hdlc)
अणु
	काष्ठा pvc_device **pvc_p = &state(hdlc)->first_pvc;

	जबतक (*pvc_p) अणु
		अगर (!pvc_is_used(*pvc_p)) अणु
			काष्ठा pvc_device *pvc = *pvc_p;
#अगर_घोषित DEBUG_PVC
			prपूर्णांकk(KERN_DEBUG "freeing unused pvc: %p\n", pvc);
#पूर्ण_अगर
			*pvc_p = pvc->next;
			kमुक्त(pvc);
			जारी;
		पूर्ण
		pvc_p = &(*pvc_p)->next;
	पूर्ण
पूर्ण


अटल अंतरभूत काष्ठा net_device **get_dev_p(काष्ठा pvc_device *pvc,
					    पूर्णांक type)
अणु
	अगर (type == ARPHRD_ETHER)
		वापस &pvc->ether;
	अन्यथा
		वापस &pvc->मुख्य;
पूर्ण


अटल पूर्णांक fr_hard_header(काष्ठा sk_buff *skb, u16 dlci)
अणु
	अगर (!skb->dev) अणु /* Control packets */
		चयन (dlci) अणु
		हाल LMI_CCITT_ANSI_DLCI:
			skb_push(skb, 4);
			skb->data[3] = NLPID_CCITT_ANSI_LMI;
			अवरोध;

		हाल LMI_CISCO_DLCI:
			skb_push(skb, 4);
			skb->data[3] = NLPID_CISCO_LMI;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

	पूर्ण अन्यथा अगर (skb->dev->type == ARPHRD_DLCI) अणु
		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP):
			skb_push(skb, 4);
			skb->data[3] = NLPID_IP;
			अवरोध;

		हाल htons(ETH_P_IPV6):
			skb_push(skb, 4);
			skb->data[3] = NLPID_IPV6;
			अवरोध;

		शेष:
			skb_push(skb, 10);
			skb->data[3] = FR_PAD;
			skb->data[4] = NLPID_SNAP;
			/* OUI 00-00-00 indicates an Ethertype follows */
			skb->data[5] = 0x00;
			skb->data[6] = 0x00;
			skb->data[7] = 0x00;
			/* This should be an Ethertype: */
			*(__be16 *)(skb->data + 8) = skb->protocol;
		पूर्ण

	पूर्ण अन्यथा अगर (skb->dev->type == ARPHRD_ETHER) अणु
		skb_push(skb, 10);
		skb->data[3] = FR_PAD;
		skb->data[4] = NLPID_SNAP;
		/* OUI 00-80-C2 stands क्रम the 802.1 organization */
		skb->data[5] = 0x00;
		skb->data[6] = 0x80;
		skb->data[7] = 0xC2;
		/* PID 00-07 stands क्रम Ethernet frames without FCS */
		skb->data[8] = 0x00;
		skb->data[9] = 0x07;

	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	dlci_to_q922(skb->data, dlci);
	skb->data[2] = FR_UI;
	वापस 0;
पूर्ण



अटल पूर्णांक pvc_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा pvc_device *pvc = dev->ml_priv;

	अगर ((pvc->frad->flags & IFF_UP) == 0)
		वापस -EIO;  /* Frad must be UP in order to activate PVC */

	अगर (pvc->खोलो_count++ == 0) अणु
		hdlc_device *hdlc = dev_to_hdlc(pvc->frad);
		अगर (state(hdlc)->settings.lmi == LMI_NONE)
			pvc->state.active = netअगर_carrier_ok(pvc->frad);

		pvc_carrier(pvc->state.active, pvc);
		state(hdlc)->dce_changed = 1;
	पूर्ण
	वापस 0;
पूर्ण



अटल पूर्णांक pvc_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा pvc_device *pvc = dev->ml_priv;

	अगर (--pvc->खोलो_count == 0) अणु
		hdlc_device *hdlc = dev_to_hdlc(pvc->frad);
		अगर (state(hdlc)->settings.lmi == LMI_NONE)
			pvc->state.active = 0;

		अगर (state(hdlc)->settings.dce) अणु
			state(hdlc)->dce_changed = 1;
			pvc->state.active = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण



अटल पूर्णांक pvc_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा pvc_device *pvc = dev->ml_priv;
	fr_proto_pvc_info info;

	अगर (अगरr->अगरr_settings.type == IF_GET_PROTO) अणु
		अगर (dev->type == ARPHRD_ETHER)
			अगरr->अगरr_settings.type = IF_PROTO_FR_ETH_PVC;
		अन्यथा
			अगरr->अगरr_settings.type = IF_PROTO_FR_PVC;

		अगर (अगरr->अगरr_settings.size < माप(info)) अणु
			/* data size wanted */
			अगरr->अगरr_settings.size = माप(info);
			वापस -ENOBUFS;
		पूर्ण

		info.dlci = pvc->dlci;
		स_नकल(info.master, pvc->frad->name, IFNAMSIZ);
		अगर (copy_to_user(अगरr->अगरr_settings.अगरs_अगरsu.fr_pvc_info,
				 &info, माप(info)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल netdev_tx_t pvc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा pvc_device *pvc = dev->ml_priv;

	अगर (!pvc->state.active)
		जाओ drop;

	अगर (dev->type == ARPHRD_ETHER) अणु
		पूर्णांक pad = ETH_ZLEN - skb->len;

		अगर (pad > 0) अणु /* Pad the frame with zeros */
			अगर (__skb_pad(skb, pad, false))
				जाओ drop;
			skb_put(skb, pad);
		पूर्ण
	पूर्ण

	/* We alपढ़ोy requested the header space with dev->needed_headroom.
	 * So this is just a protection in हाल the upper layer didn't take
	 * dev->needed_headroom पूर्णांकo consideration.
	 */
	अगर (skb_headroom(skb) < 10) अणु
		काष्ठा sk_buff *skb2 = skb_पुनः_स्मृति_headroom(skb, 10);

		अगर (!skb2)
			जाओ drop;
		dev_kमुक्त_skb(skb);
		skb = skb2;
	पूर्ण

	skb->dev = dev;
	अगर (fr_hard_header(skb, pvc->dlci))
		जाओ drop;

	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;
	अगर (pvc->state.fecn) /* TX Congestion counter */
		dev->stats.tx_compressed++;
	skb->dev = pvc->frad;
	skb->protocol = htons(ETH_P_HDLC);
	skb_reset_network_header(skb);
	dev_queue_xmit(skb);
	वापस NETDEV_TX_OK;

drop:
	dev->stats.tx_dropped++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल अंतरभूत व्योम fr_log_dlci_active(काष्ठा pvc_device *pvc)
अणु
	netdev_info(pvc->frad, "DLCI %d [%s%s%s]%s %s\n",
		    pvc->dlci,
		    pvc->मुख्य ? pvc->मुख्य->name : "",
		    pvc->मुख्य && pvc->ether ? " " : "",
		    pvc->ether ? pvc->ether->name : "",
		    pvc->state.new ? " new" : "",
		    !pvc->state.exist ? "deleted" :
		    pvc->state.active ? "active" : "inactive");
पूर्ण



अटल अंतरभूत u8 fr_lmi_nextseq(u8 x)
अणु
	x++;
	वापस x ? x : 1;
पूर्ण


अटल व्योम fr_lmi_send(काष्ठा net_device *dev, पूर्णांक fullrep)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा sk_buff *skb;
	काष्ठा pvc_device *pvc = state(hdlc)->first_pvc;
	पूर्णांक lmi = state(hdlc)->settings.lmi;
	पूर्णांक dce = state(hdlc)->settings.dce;
	पूर्णांक len = lmi == LMI_ANSI ? LMI_ANSI_LENGTH : LMI_CCITT_CISCO_LENGTH;
	पूर्णांक stat_len = (lmi == LMI_CISCO) ? 6 : 3;
	u8 *data;
	पूर्णांक i = 0;

	अगर (dce && fullrep) अणु
		len += state(hdlc)->dce_pvc_count * (2 + stat_len);
		अगर (len > HDLC_MAX_MRU) अणु
			netdev_warn(dev, "Too many PVCs while sending LMI full report\n");
			वापस;
		पूर्ण
	पूर्ण

	skb = dev_alloc_skb(len);
	अगर (!skb) अणु
		netdev_warn(dev, "Memory squeeze on fr_lmi_send()\n");
		वापस;
	पूर्ण
	स_रखो(skb->data, 0, len);
	skb_reserve(skb, 4);
	अगर (lmi == LMI_CISCO) अणु
		fr_hard_header(skb, LMI_CISCO_DLCI);
	पूर्ण अन्यथा अणु
		fr_hard_header(skb, LMI_CCITT_ANSI_DLCI);
	पूर्ण
	data = skb_tail_poपूर्णांकer(skb);
	data[i++] = LMI_CALLREF;
	data[i++] = dce ? LMI_STATUS : LMI_STATUS_ENQUIRY;
	अगर (lmi == LMI_ANSI)
		data[i++] = LMI_ANSI_LOCKSHIFT;
	data[i++] = lmi == LMI_CCITT ? LMI_CCITT_REPTYPE :
		LMI_ANSI_CISCO_REPTYPE;
	data[i++] = LMI_REPT_LEN;
	data[i++] = fullrep ? LMI_FULLREP : LMI_INTEGRITY;
	data[i++] = lmi == LMI_CCITT ? LMI_CCITT_ALIVE : LMI_ANSI_CISCO_ALIVE;
	data[i++] = LMI_INTEG_LEN;
	data[i++] = state(hdlc)->txseq =
		fr_lmi_nextseq(state(hdlc)->txseq);
	data[i++] = state(hdlc)->rxseq;

	अगर (dce && fullrep) अणु
		जबतक (pvc) अणु
			data[i++] = lmi == LMI_CCITT ? LMI_CCITT_PVCSTAT :
				LMI_ANSI_CISCO_PVCSTAT;
			data[i++] = stat_len;

			/* LMI start/restart */
			अगर (state(hdlc)->reliable && !pvc->state.exist) अणु
				pvc->state.exist = pvc->state.new = 1;
				fr_log_dlci_active(pvc);
			पूर्ण

			/* अगरconfig PVC up */
			अगर (pvc->खोलो_count && !pvc->state.active &&
			    pvc->state.exist && !pvc->state.new) अणु
				pvc_carrier(1, pvc);
				pvc->state.active = 1;
				fr_log_dlci_active(pvc);
			पूर्ण

			अगर (lmi == LMI_CISCO) अणु
				data[i] = pvc->dlci >> 8;
				data[i + 1] = pvc->dlci & 0xFF;
			पूर्ण अन्यथा अणु
				data[i] = (pvc->dlci >> 4) & 0x3F;
				data[i + 1] = ((pvc->dlci << 3) & 0x78) | 0x80;
				data[i + 2] = 0x80;
			पूर्ण

			अगर (pvc->state.new)
				data[i + 2] |= 0x08;
			अन्यथा अगर (pvc->state.active)
				data[i + 2] |= 0x02;

			i += stat_len;
			pvc = pvc->next;
		पूर्ण
	पूर्ण

	skb_put(skb, i);
	skb->priority = TC_PRIO_CONTROL;
	skb->dev = dev;
	skb->protocol = htons(ETH_P_HDLC);
	skb_reset_network_header(skb);

	dev_queue_xmit(skb);
पूर्ण



अटल व्योम fr_set_link_state(पूर्णांक reliable, काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा pvc_device *pvc = state(hdlc)->first_pvc;

	state(hdlc)->reliable = reliable;
	अगर (reliable) अणु
		netअगर_करोrmant_off(dev);
		state(hdlc)->n391cnt = 0; /* Request full status */
		state(hdlc)->dce_changed = 1;

		अगर (state(hdlc)->settings.lmi == LMI_NONE) अणु
			जबतक (pvc) अणु	/* Activate all PVCs */
				pvc_carrier(1, pvc);
				pvc->state.exist = pvc->state.active = 1;
				pvc->state.new = 0;
				pvc = pvc->next;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_करोrmant_on(dev);
		जबतक (pvc) अणु		/* Deactivate all PVCs */
			pvc_carrier(0, pvc);
			pvc->state.exist = pvc->state.active = 0;
			pvc->state.new = 0;
			अगर (!state(hdlc)->settings.dce)
				pvc->state.bandwidth = 0;
			pvc = pvc->next;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम fr_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा frad_state *st = from_समयr(st, t, समयr);
	काष्ठा net_device *dev = st->dev;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	पूर्णांक i, cnt = 0, reliable;
	u32 list;

	अगर (state(hdlc)->settings.dce) अणु
		reliable = state(hdlc)->request &&
			समय_beक्रमe(jअगरfies, state(hdlc)->last_poll +
				    state(hdlc)->settings.t392 * HZ);
		state(hdlc)->request = 0;
	पूर्ण अन्यथा अणु
		state(hdlc)->last_errors <<= 1; /* Shअगरt the list */
		अगर (state(hdlc)->request) अणु
			अगर (state(hdlc)->reliable)
				netdev_info(dev, "No LMI status reply received\n");
			state(hdlc)->last_errors |= 1;
		पूर्ण

		list = state(hdlc)->last_errors;
		क्रम (i = 0; i < state(hdlc)->settings.n393; i++, list >>= 1)
			cnt += (list & 1);	/* errors count */

		reliable = (cnt < state(hdlc)->settings.n392);
	पूर्ण

	अगर (state(hdlc)->reliable != reliable) अणु
		netdev_info(dev, "Link %sreliable\n", reliable ? "" : "un");
		fr_set_link_state(reliable, dev);
	पूर्ण

	अगर (state(hdlc)->settings.dce)
		state(hdlc)->समयr.expires = jअगरfies +
			state(hdlc)->settings.t392 * HZ;
	अन्यथा अणु
		अगर (state(hdlc)->n391cnt)
			state(hdlc)->n391cnt--;

		fr_lmi_send(dev, state(hdlc)->n391cnt == 0);

		state(hdlc)->last_poll = jअगरfies;
		state(hdlc)->request = 1;
		state(hdlc)->समयr.expires = jअगरfies +
			state(hdlc)->settings.t391 * HZ;
	पूर्ण

	add_समयr(&state(hdlc)->समयr);
पूर्ण


अटल पूर्णांक fr_lmi_recv(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा pvc_device *pvc;
	u8 rxseq, txseq;
	पूर्णांक lmi = state(hdlc)->settings.lmi;
	पूर्णांक dce = state(hdlc)->settings.dce;
	पूर्णांक stat_len = (lmi == LMI_CISCO) ? 6 : 3, reptype, error, no_ram, i;

	अगर (skb->len < (lmi == LMI_ANSI ? LMI_ANSI_LENGTH :
			LMI_CCITT_CISCO_LENGTH)) अणु
		netdev_info(dev, "Short LMI frame\n");
		वापस 1;
	पूर्ण

	अगर (skb->data[3] != (lmi == LMI_CISCO ? NLPID_CISCO_LMI :
			     NLPID_CCITT_ANSI_LMI)) अणु
		netdev_info(dev, "Received non-LMI frame with LMI DLCI\n");
		वापस 1;
	पूर्ण

	अगर (skb->data[4] != LMI_CALLREF) अणु
		netdev_info(dev, "Invalid LMI Call reference (0x%02X)\n",
			    skb->data[4]);
		वापस 1;
	पूर्ण

	अगर (skb->data[5] != (dce ? LMI_STATUS_ENQUIRY : LMI_STATUS)) अणु
		netdev_info(dev, "Invalid LMI Message type (0x%02X)\n",
			    skb->data[5]);
		वापस 1;
	पूर्ण

	अगर (lmi == LMI_ANSI) अणु
		अगर (skb->data[6] != LMI_ANSI_LOCKSHIFT) अणु
			netdev_info(dev, "Not ANSI locking shift in LMI message (0x%02X)\n",
				    skb->data[6]);
			वापस 1;
		पूर्ण
		i = 7;
	पूर्ण अन्यथा
		i = 6;

	अगर (skb->data[i] != (lmi == LMI_CCITT ? LMI_CCITT_REPTYPE :
			     LMI_ANSI_CISCO_REPTYPE)) अणु
		netdev_info(dev, "Not an LMI Report type IE (0x%02X)\n",
			    skb->data[i]);
		वापस 1;
	पूर्ण

	अगर (skb->data[++i] != LMI_REPT_LEN) अणु
		netdev_info(dev, "Invalid LMI Report type IE length (%u)\n",
			    skb->data[i]);
		वापस 1;
	पूर्ण

	reptype = skb->data[++i];
	अगर (reptype != LMI_INTEGRITY && reptype != LMI_FULLREP) अणु
		netdev_info(dev, "Unsupported LMI Report type (0x%02X)\n",
			    reptype);
		वापस 1;
	पूर्ण

	अगर (skb->data[++i] != (lmi == LMI_CCITT ? LMI_CCITT_ALIVE :
			       LMI_ANSI_CISCO_ALIVE)) अणु
		netdev_info(dev, "Not an LMI Link integrity verification IE (0x%02X)\n",
			    skb->data[i]);
		वापस 1;
	पूर्ण

	अगर (skb->data[++i] != LMI_INTEG_LEN) अणु
		netdev_info(dev, "Invalid LMI Link integrity verification IE length (%u)\n",
			    skb->data[i]);
		वापस 1;
	पूर्ण
	i++;

	state(hdlc)->rxseq = skb->data[i++]; /* TX sequence from peer */
	rxseq = skb->data[i++];	/* Should confirm our sequence */

	txseq = state(hdlc)->txseq;

	अगर (dce)
		state(hdlc)->last_poll = jअगरfies;

	error = 0;
	अगर (!state(hdlc)->reliable)
		error = 1;

	अगर (rxseq == 0 || rxseq != txseq) अणु /* Ask क्रम full report next समय */
		state(hdlc)->n391cnt = 0;
		error = 1;
	पूर्ण

	अगर (dce) अणु
		अगर (state(hdlc)->fullrep_sent && !error) अणु
/* Stop sending full report - the last one has been confirmed by DTE */
			state(hdlc)->fullrep_sent = 0;
			pvc = state(hdlc)->first_pvc;
			जबतक (pvc) अणु
				अगर (pvc->state.new) अणु
					pvc->state.new = 0;

/* Tell DTE that new PVC is now active */
					state(hdlc)->dce_changed = 1;
				पूर्ण
				pvc = pvc->next;
			पूर्ण
		पूर्ण

		अगर (state(hdlc)->dce_changed) अणु
			reptype = LMI_FULLREP;
			state(hdlc)->fullrep_sent = 1;
			state(hdlc)->dce_changed = 0;
		पूर्ण

		state(hdlc)->request = 1; /* got request */
		fr_lmi_send(dev, reptype == LMI_FULLREP ? 1 : 0);
		वापस 0;
	पूर्ण

	/* DTE */

	state(hdlc)->request = 0; /* got response, no request pending */

	अगर (error)
		वापस 0;

	अगर (reptype != LMI_FULLREP)
		वापस 0;

	pvc = state(hdlc)->first_pvc;

	जबतक (pvc) अणु
		pvc->state.deleted = 1;
		pvc = pvc->next;
	पूर्ण

	no_ram = 0;
	जबतक (skb->len >= i + 2 + stat_len) अणु
		u16 dlci;
		u32 bw;
		अचिन्हित पूर्णांक active, new;

		अगर (skb->data[i] != (lmi == LMI_CCITT ? LMI_CCITT_PVCSTAT :
				       LMI_ANSI_CISCO_PVCSTAT)) अणु
			netdev_info(dev, "Not an LMI PVC status IE (0x%02X)\n",
				    skb->data[i]);
			वापस 1;
		पूर्ण

		अगर (skb->data[++i] != stat_len) अणु
			netdev_info(dev, "Invalid LMI PVC status IE length (%u)\n",
				    skb->data[i]);
			वापस 1;
		पूर्ण
		i++;

		new = !! (skb->data[i + 2] & 0x08);
		active = !! (skb->data[i + 2] & 0x02);
		अगर (lmi == LMI_CISCO) अणु
			dlci = (skb->data[i] << 8) | skb->data[i + 1];
			bw = (skb->data[i + 3] << 16) |
				(skb->data[i + 4] << 8) |
				(skb->data[i + 5]);
		पूर्ण अन्यथा अणु
			dlci = ((skb->data[i] & 0x3F) << 4) |
				((skb->data[i + 1] & 0x78) >> 3);
			bw = 0;
		पूर्ण

		pvc = add_pvc(dev, dlci);

		अगर (!pvc && !no_ram) अणु
			netdev_warn(dev, "Memory squeeze on fr_lmi_recv()\n");
			no_ram = 1;
		पूर्ण

		अगर (pvc) अणु
			pvc->state.exist = 1;
			pvc->state.deleted = 0;
			अगर (active != pvc->state.active ||
			    new != pvc->state.new ||
			    bw != pvc->state.bandwidth ||
			    !pvc->state.exist) अणु
				pvc->state.new = new;
				pvc->state.active = active;
				pvc->state.bandwidth = bw;
				pvc_carrier(active, pvc);
				fr_log_dlci_active(pvc);
			पूर्ण
		पूर्ण

		i += stat_len;
	पूर्ण

	pvc = state(hdlc)->first_pvc;

	जबतक (pvc) अणु
		अगर (pvc->state.deleted && pvc->state.exist) अणु
			pvc_carrier(0, pvc);
			pvc->state.active = pvc->state.new = 0;
			pvc->state.exist = 0;
			pvc->state.bandwidth = 0;
			fr_log_dlci_active(pvc);
		पूर्ण
		pvc = pvc->next;
	पूर्ण

	/* Next full report after N391 polls */
	state(hdlc)->n391cnt = state(hdlc)->settings.n391;

	वापस 0;
पूर्ण

अटल पूर्णांक fr_snap_parse(काष्ठा sk_buff *skb, काष्ठा pvc_device *pvc)
अणु
	/* OUI 00-00-00 indicates an Ethertype follows */
	अगर (skb->data[0] == 0x00 &&
	    skb->data[1] == 0x00 &&
	    skb->data[2] == 0x00) अणु
		अगर (!pvc->मुख्य)
			वापस -1;
		skb->dev = pvc->मुख्य;
		skb->protocol = *(__be16 *)(skb->data + 3); /* Ethertype */
		skb_pull(skb, 5);
		skb_reset_mac_header(skb);
		वापस 0;

	/* OUI 00-80-C2 stands क्रम the 802.1 organization */
	पूर्ण अन्यथा अगर (skb->data[0] == 0x00 &&
		   skb->data[1] == 0x80 &&
		   skb->data[2] == 0xC2) अणु
		/* PID 00-07 stands क्रम Ethernet frames without FCS */
		अगर (skb->data[3] == 0x00 &&
		    skb->data[4] == 0x07) अणु
			अगर (!pvc->ether)
				वापस -1;
			skb_pull(skb, 5);
			अगर (skb->len < ETH_HLEN)
				वापस -1;
			skb->protocol = eth_type_trans(skb, pvc->ether);
			वापस 0;

		/* PID unsupported */
		पूर्ण अन्यथा अणु
			वापस -1;
		पूर्ण

	/* OUI unsupported */
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक fr_rx(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *frad = skb->dev;
	hdlc_device *hdlc = dev_to_hdlc(frad);
	काष्ठा fr_hdr *fh = (काष्ठा fr_hdr *)skb->data;
	u8 *data = skb->data;
	u16 dlci;
	काष्ठा pvc_device *pvc;
	काष्ठा net_device *dev;

	अगर (skb->len < 4 || fh->ea1 || !fh->ea2 || data[2] != FR_UI)
		जाओ rx_error;

	dlci = q922_to_dlci(skb->data);

	अगर ((dlci == LMI_CCITT_ANSI_DLCI &&
	     (state(hdlc)->settings.lmi == LMI_ANSI ||
	      state(hdlc)->settings.lmi == LMI_CCITT)) ||
	    (dlci == LMI_CISCO_DLCI &&
	     state(hdlc)->settings.lmi == LMI_CISCO)) अणु
		अगर (fr_lmi_recv(frad, skb))
			जाओ rx_error;
		dev_kमुक्त_skb_any(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	pvc = find_pvc(hdlc, dlci);
	अगर (!pvc) अणु
#अगर_घोषित DEBUG_PKT
		netdev_info(frad, "No PVC for received frame's DLCI %d\n",
			    dlci);
#पूर्ण_अगर
		जाओ rx_drop;
	पूर्ण

	अगर (pvc->state.fecn != fh->fecn) अणु
#अगर_घोषित DEBUG_ECN
		prपूर्णांकk(KERN_DEBUG "%s: DLCI %d FECN O%s\n", frad->name,
		       dlci, fh->fecn ? "N" : "FF");
#पूर्ण_अगर
		pvc->state.fecn ^= 1;
	पूर्ण

	अगर (pvc->state.becn != fh->becn) अणु
#अगर_घोषित DEBUG_ECN
		prपूर्णांकk(KERN_DEBUG "%s: DLCI %d BECN O%s\n", frad->name,
		       dlci, fh->becn ? "N" : "FF");
#पूर्ण_अगर
		pvc->state.becn ^= 1;
	पूर्ण


	अगर ((skb = skb_share_check(skb, GFP_ATOMIC)) == शून्य) अणु
		frad->stats.rx_dropped++;
		वापस NET_RX_DROP;
	पूर्ण

	अगर (data[3] == NLPID_IP) अणु
		अगर (!pvc->मुख्य)
			जाओ rx_drop;
		skb_pull(skb, 4); /* Remove 4-byte header (hdr, UI, NLPID) */
		skb->dev = pvc->मुख्य;
		skb->protocol = htons(ETH_P_IP);
		skb_reset_mac_header(skb);

	पूर्ण अन्यथा अगर (data[3] == NLPID_IPV6) अणु
		अगर (!pvc->मुख्य)
			जाओ rx_drop;
		skb_pull(skb, 4); /* Remove 4-byte header (hdr, UI, NLPID) */
		skb->dev = pvc->मुख्य;
		skb->protocol = htons(ETH_P_IPV6);
		skb_reset_mac_header(skb);

	पूर्ण अन्यथा अगर (data[3] == FR_PAD) अणु
		अगर (skb->len < 5)
			जाओ rx_error;
		अगर (data[4] == NLPID_SNAP) अणु /* A SNAP header follows */
			skb_pull(skb, 5);
			अगर (skb->len < 5) /* Incomplete SNAP header */
				जाओ rx_error;
			अगर (fr_snap_parse(skb, pvc))
				जाओ rx_drop;
		पूर्ण अन्यथा अणु
			जाओ rx_drop;
		पूर्ण

	पूर्ण अन्यथा अणु
		netdev_info(frad, "Unsupported protocol, NLPID=%x length=%i\n",
			    data[3], skb->len);
		जाओ rx_drop;
	पूर्ण

	dev = skb->dev;
	dev->stats.rx_packets++; /* PVC traffic */
	dev->stats.rx_bytes += skb->len;
	अगर (pvc->state.becn)
		dev->stats.rx_compressed++;
	netअगर_rx(skb);
	वापस NET_RX_SUCCESS;

rx_error:
	frad->stats.rx_errors++; /* Mark error */
rx_drop:
	dev_kमुक्त_skb_any(skb);
	वापस NET_RX_DROP;
पूर्ण



अटल व्योम fr_start(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
#अगर_घोषित DEBUG_LINK
	prपूर्णांकk(KERN_DEBUG "fr_start\n");
#पूर्ण_अगर
	अगर (state(hdlc)->settings.lmi != LMI_NONE) अणु
		state(hdlc)->reliable = 0;
		state(hdlc)->dce_changed = 1;
		state(hdlc)->request = 0;
		state(hdlc)->fullrep_sent = 0;
		state(hdlc)->last_errors = 0xFFFFFFFF;
		state(hdlc)->n391cnt = 0;
		state(hdlc)->txseq = state(hdlc)->rxseq = 0;

		state(hdlc)->dev = dev;
		समयr_setup(&state(hdlc)->समयr, fr_समयr, 0);
		/* First poll after 1 s */
		state(hdlc)->समयr.expires = jअगरfies + HZ;
		add_समयr(&state(hdlc)->समयr);
	पूर्ण अन्यथा
		fr_set_link_state(1, dev);
पूर्ण


अटल व्योम fr_stop(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
#अगर_घोषित DEBUG_LINK
	prपूर्णांकk(KERN_DEBUG "fr_stop\n");
#पूर्ण_अगर
	अगर (state(hdlc)->settings.lmi != LMI_NONE)
		del_समयr_sync(&state(hdlc)->समयr);
	fr_set_link_state(0, dev);
पूर्ण


अटल व्योम fr_बंद(काष्ठा net_device *dev)
अणु
	hdlc_device *hdlc = dev_to_hdlc(dev);
	काष्ठा pvc_device *pvc = state(hdlc)->first_pvc;

	जबतक (pvc) अणु		/* Shutकरोwn all PVCs क्रम this FRAD */
		अगर (pvc->मुख्य)
			dev_बंद(pvc->मुख्य);
		अगर (pvc->ether)
			dev_बंद(pvc->ether);
		pvc = pvc->next;
	पूर्ण
पूर्ण


अटल व्योम pvc_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_DLCI;
	dev->flags = IFF_POINTOPOINT;
	dev->hard_header_len = 0;
	dev->addr_len = 2;
	netअगर_keep_dst(dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops pvc_ops = अणु
	.nकरो_खोलो       = pvc_खोलो,
	.nकरो_stop       = pvc_बंद,
	.nकरो_start_xmit = pvc_xmit,
	.nकरो_करो_ioctl   = pvc_ioctl,
पूर्ण;

अटल पूर्णांक fr_add_pvc(काष्ठा net_device *frad, अचिन्हित पूर्णांक dlci, पूर्णांक type)
अणु
	hdlc_device *hdlc = dev_to_hdlc(frad);
	काष्ठा pvc_device *pvc;
	काष्ठा net_device *dev;
	पूर्णांक used;

	अगर ((pvc = add_pvc(frad, dlci)) == शून्य) अणु
		netdev_warn(frad, "Memory squeeze on fr_add_pvc()\n");
		वापस -ENOBUFS;
	पूर्ण

	अगर (*get_dev_p(pvc, type))
		वापस -EEXIST;

	used = pvc_is_used(pvc);

	अगर (type == ARPHRD_ETHER)
		dev = alloc_netdev(0, "pvceth%d", NET_NAME_UNKNOWN,
				   ether_setup);
	अन्यथा
		dev = alloc_netdev(0, "pvc%d", NET_NAME_UNKNOWN, pvc_setup);

	अगर (!dev) अणु
		netdev_warn(frad, "Memory squeeze on fr_pvc()\n");
		delete_unused_pvcs(hdlc);
		वापस -ENOBUFS;
	पूर्ण

	अगर (type == ARPHRD_ETHER) अणु
		dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		eth_hw_addr_अक्रमom(dev);
	पूर्ण अन्यथा अणु
		*(__be16*)dev->dev_addr = htons(dlci);
		dlci_to_q922(dev->broadcast, dlci);
	पूर्ण
	dev->netdev_ops = &pvc_ops;
	dev->mtu = HDLC_MAX_MTU;
	dev->min_mtu = 68;
	dev->max_mtu = HDLC_MAX_MTU;
	dev->needed_headroom = 10;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->ml_priv = pvc;

	अगर (रेजिस्टर_netdevice(dev) != 0) अणु
		मुक्त_netdev(dev);
		delete_unused_pvcs(hdlc);
		वापस -EIO;
	पूर्ण

	dev->needs_मुक्त_netdev = true;
	*get_dev_p(pvc, type) = dev;
	अगर (!used) अणु
		state(hdlc)->dce_changed = 1;
		state(hdlc)->dce_pvc_count++;
	पूर्ण
	वापस 0;
पूर्ण



अटल पूर्णांक fr_del_pvc(hdlc_device *hdlc, अचिन्हित पूर्णांक dlci, पूर्णांक type)
अणु
	काष्ठा pvc_device *pvc;
	काष्ठा net_device *dev;

	अगर ((pvc = find_pvc(hdlc, dlci)) == शून्य)
		वापस -ENOENT;

	अगर ((dev = *get_dev_p(pvc, type)) == शून्य)
		वापस -ENOENT;

	अगर (dev->flags & IFF_UP)
		वापस -EBUSY;		/* PVC in use */

	unरेजिस्टर_netdevice(dev); /* the deकाष्ठाor will मुक्त_netdev(dev) */
	*get_dev_p(pvc, type) = शून्य;

	अगर (!pvc_is_used(pvc)) अणु
		state(hdlc)->dce_pvc_count--;
		state(hdlc)->dce_changed = 1;
	पूर्ण
	delete_unused_pvcs(hdlc);
	वापस 0;
पूर्ण



अटल व्योम fr_destroy(काष्ठा net_device *frad)
अणु
	hdlc_device *hdlc = dev_to_hdlc(frad);
	काष्ठा pvc_device *pvc = state(hdlc)->first_pvc;
	state(hdlc)->first_pvc = शून्य; /* All PVCs destroyed */
	state(hdlc)->dce_pvc_count = 0;
	state(hdlc)->dce_changed = 1;

	जबतक (pvc) अणु
		काष्ठा pvc_device *next = pvc->next;
		/* deकाष्ठाors will मुक्त_netdev() मुख्य and ether */
		अगर (pvc->मुख्य)
			unरेजिस्टर_netdevice(pvc->मुख्य);

		अगर (pvc->ether)
			unरेजिस्टर_netdevice(pvc->ether);

		kमुक्त(pvc);
		pvc = next;
	पूर्ण
पूर्ण


अटल काष्ठा hdlc_proto proto = अणु
	.बंद		= fr_बंद,
	.start		= fr_start,
	.stop		= fr_stop,
	.detach		= fr_destroy,
	.ioctl		= fr_ioctl,
	.netअगर_rx	= fr_rx,
	.module		= THIS_MODULE,
पूर्ण;


अटल पूर्णांक fr_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	fr_proto __user *fr_s = अगरr->अगरr_settings.अगरs_अगरsu.fr;
	स्थिर माप_प्रकार size = माप(fr_proto);
	fr_proto new_settings;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	fr_proto_pvc pvc;
	पूर्णांक result;

	चयन (अगरr->अगरr_settings.type) अणु
	हाल IF_GET_PROTO:
		अगर (dev_to_hdlc(dev)->proto != &proto) /* Dअगरferent proto */
			वापस -EINVAL;
		अगरr->अगरr_settings.type = IF_PROTO_FR;
		अगर (अगरr->अगरr_settings.size < size) अणु
			अगरr->अगरr_settings.size = size; /* data size wanted */
			वापस -ENOBUFS;
		पूर्ण
		अगर (copy_to_user(fr_s, &state(hdlc)->settings, size))
			वापस -EFAULT;
		वापस 0;

	हाल IF_PROTO_FR:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (dev->flags & IFF_UP)
			वापस -EBUSY;

		अगर (copy_from_user(&new_settings, fr_s, size))
			वापस -EFAULT;

		अगर (new_settings.lmi == LMI_DEFAULT)
			new_settings.lmi = LMI_ANSI;

		अगर ((new_settings.lmi != LMI_NONE &&
		     new_settings.lmi != LMI_ANSI &&
		     new_settings.lmi != LMI_CCITT &&
		     new_settings.lmi != LMI_CISCO) ||
		    new_settings.t391 < 1 ||
		    new_settings.t392 < 2 ||
		    new_settings.n391 < 1 ||
		    new_settings.n392 < 1 ||
		    new_settings.n393 < new_settings.n392 ||
		    new_settings.n393 > 32 ||
		    (new_settings.dce != 0 &&
		     new_settings.dce != 1))
			वापस -EINVAL;

		result=hdlc->attach(dev, ENCODING_NRZ,PARITY_CRC16_PR1_CCITT);
		अगर (result)
			वापस result;

		अगर (dev_to_hdlc(dev)->proto != &proto) अणु /* Dअगरferent proto */
			result = attach_hdlc_protocol(dev, &proto,
						      माप(काष्ठा frad_state));
			अगर (result)
				वापस result;
			state(hdlc)->first_pvc = शून्य;
			state(hdlc)->dce_pvc_count = 0;
		पूर्ण
		स_नकल(&state(hdlc)->settings, &new_settings, size);
		dev->type = ARPHRD_FRAD;
		call_netdevice_notअगरiers(NETDEV_POST_TYPE_CHANGE, dev);
		वापस 0;

	हाल IF_PROTO_FR_ADD_PVC:
	हाल IF_PROTO_FR_DEL_PVC:
	हाल IF_PROTO_FR_ADD_ETH_PVC:
	हाल IF_PROTO_FR_DEL_ETH_PVC:
		अगर (dev_to_hdlc(dev)->proto != &proto) /* Dअगरferent proto */
			वापस -EINVAL;

		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&pvc, अगरr->अगरr_settings.अगरs_अगरsu.fr_pvc,
				   माप(fr_proto_pvc)))
			वापस -EFAULT;

		अगर (pvc.dlci <= 0 || pvc.dlci >= 1024)
			वापस -EINVAL;	/* Only 10 bits, DLCI 0 reserved */

		अगर (अगरr->अगरr_settings.type == IF_PROTO_FR_ADD_ETH_PVC ||
		    अगरr->अगरr_settings.type == IF_PROTO_FR_DEL_ETH_PVC)
			result = ARPHRD_ETHER; /* bridged Ethernet device */
		अन्यथा
			result = ARPHRD_DLCI;

		अगर (अगरr->अगरr_settings.type == IF_PROTO_FR_ADD_PVC ||
		    अगरr->अगरr_settings.type == IF_PROTO_FR_ADD_ETH_PVC)
			वापस fr_add_pvc(dev, pvc.dlci, result);
		अन्यथा
			वापस fr_del_pvc(hdlc, pvc.dlci, result);
	पूर्ण

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक __init mod_init(व्योम)
अणु
	रेजिस्टर_hdlc_protocol(&proto);
	वापस 0;
पूर्ण


अटल व्योम __निकास mod_निकास(व्योम)
अणु
	unरेजिस्टर_hdlc_protocol(&proto);
पूर्ण


module_init(mod_init);
module_निकास(mod_निकास);

MODULE_AUTHOR("Krzysztof Halasa <khc@pm.waw.pl>");
MODULE_DESCRIPTION("Frame-Relay protocol support for generic HDLC");
MODULE_LICENSE("GPL v2");
