<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/मानकघोष.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfsrvl.h>
#समावेश <net/caअगर/cfpkt.h>


#घोषणा container_obj(layr) ((काष्ठा cfsrvl *) layr)

#घोषणा DGM_CMD_BIT  0x80
#घोषणा DGM_FLOW_OFF 0x81
#घोषणा DGM_FLOW_ON  0x80
#घोषणा DGM_MTU 1500

अटल पूर्णांक cfdgml_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfdgml_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);

काष्ठा cflayer *cfdgml_create(u8 channel_id, काष्ठा dev_info *dev_info)
अणु
	काष्ठा cfsrvl *dgm = kzalloc(माप(काष्ठा cfsrvl), GFP_ATOMIC);
	अगर (!dgm)
		वापस शून्य;
	caअगर_निश्चित(दुरत्व(काष्ठा cfsrvl, layer) == 0);
	cfsrvl_init(dgm, channel_id, dev_info, true);
	dgm->layer.receive = cfdgml_receive;
	dgm->layer.transmit = cfdgml_transmit;
	snम_लिखो(dgm->layer.name, CAIF_LAYER_NAME_SZ, "dgm%d", channel_id);
	वापस &dgm->layer;
पूर्ण

अटल पूर्णांक cfdgml_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 cmd = -1;
	u8 dgmhdr[3];
	पूर्णांक ret;
	caअगर_निश्चित(layr->up != शून्य);
	caअगर_निश्चित(layr->receive != शून्य);
	caअगर_निश्चित(layr->ctrlcmd != शून्य);

	अगर (cfpkt_extr_head(pkt, &cmd, 1) < 0) अणु
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण

	अगर ((cmd & DGM_CMD_BIT) == 0) अणु
		अगर (cfpkt_extr_head(pkt, &dgmhdr, 3) < 0) अणु
			pr_err("Packet is erroneous!\n");
			cfpkt_destroy(pkt);
			वापस -EPROTO;
		पूर्ण
		ret = layr->up->receive(layr->up, pkt);
		वापस ret;
	पूर्ण

	चयन (cmd) अणु
	हाल DGM_FLOW_OFF:	/* FLOW OFF */
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_OFF_IND, 0);
		cfpkt_destroy(pkt);
		वापस 0;
	हाल DGM_FLOW_ON:	/* FLOW ON */
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_ON_IND, 0);
		cfpkt_destroy(pkt);
		वापस 0;
	शेष:
		cfpkt_destroy(pkt);
		pr_info("Unknown datagram control %d (0x%x)\n", cmd, cmd);
		वापस -EPROTO;
	पूर्ण
पूर्ण

अटल पूर्णांक cfdgml_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 packet_type;
	u32 zero = 0;
	काष्ठा caअगर_payload_info *info;
	काष्ठा cfsrvl *service = container_obj(layr);
	पूर्णांक ret;

	अगर (!cfsrvl_पढ़ोy(service, &ret)) अणु
		cfpkt_destroy(pkt);
		वापस ret;
	पूर्ण

	/* STE Modem cannot handle more than 1500 bytes datagrams */
	अगर (cfpkt_getlen(pkt) > DGM_MTU) अणु
		cfpkt_destroy(pkt);
		वापस -EMSGSIZE;
	पूर्ण

	cfpkt_add_head(pkt, &zero, 3);
	packet_type = 0x08; /* B9 set - UNCLASSIFIED */
	cfpkt_add_head(pkt, &packet_type, 1);

	/* Add info क्रम MUX-layer to route the packet out. */
	info = cfpkt_info(pkt);
	info->channel_id = service->layer.id;
	/* To optimize alignment, we add up the size of CAIF header
	 * beक्रमe payload.
	 */
	info->hdr_len = 4;
	info->dev_info = &service->dev_info;
	वापस layr->dn->transmit(layr->dn, pkt);
पूर्ण
