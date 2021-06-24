<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfsrvl.h>
#समावेश <net/caअगर/cfpkt.h>

#घोषणा VEI_PAYLOAD  0x00
#घोषणा VEI_CMD_BIT  0x80
#घोषणा VEI_FLOW_OFF 0x81
#घोषणा VEI_FLOW_ON  0x80
#घोषणा VEI_SET_PIN  0x82

#घोषणा container_obj(layr) container_of(layr, काष्ठा cfsrvl, layer)

अटल पूर्णांक cfvei_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfvei_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);

काष्ठा cflayer *cfvei_create(u8 channel_id, काष्ठा dev_info *dev_info)
अणु
	काष्ठा cfsrvl *vei = kzalloc(माप(काष्ठा cfsrvl), GFP_ATOMIC);
	अगर (!vei)
		वापस शून्य;
	caअगर_निश्चित(दुरत्व(काष्ठा cfsrvl, layer) == 0);
	cfsrvl_init(vei, channel_id, dev_info, true);
	vei->layer.receive = cfvei_receive;
	vei->layer.transmit = cfvei_transmit;
	snम_लिखो(vei->layer.name, CAIF_LAYER_NAME_SZ, "vei%d", channel_id);
	वापस &vei->layer;
पूर्ण

अटल पूर्णांक cfvei_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 cmd;
	पूर्णांक ret;
	caअगर_निश्चित(layr->up != शून्य);
	caअगर_निश्चित(layr->receive != शून्य);
	caअगर_निश्चित(layr->ctrlcmd != शून्य);


	अगर (cfpkt_extr_head(pkt, &cmd, 1) < 0) अणु
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण
	चयन (cmd) अणु
	हाल VEI_PAYLOAD:
		ret = layr->up->receive(layr->up, pkt);
		वापस ret;
	हाल VEI_FLOW_OFF:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_OFF_IND, 0);
		cfpkt_destroy(pkt);
		वापस 0;
	हाल VEI_FLOW_ON:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_ON_IND, 0);
		cfpkt_destroy(pkt);
		वापस 0;
	हाल VEI_SET_PIN:	/* SET RS232 PIN */
		cfpkt_destroy(pkt);
		वापस 0;
	शेष:		/* SET RS232 PIN */
		pr_warn("Unknown VEI control packet %d (0x%x)!\n", cmd, cmd);
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण
पूर्ण

अटल पूर्णांक cfvei_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 पंचांगp = 0;
	काष्ठा caअगर_payload_info *info;
	पूर्णांक ret;
	काष्ठा cfsrvl *service = container_obj(layr);
	अगर (!cfsrvl_पढ़ोy(service, &ret))
		जाओ err;
	caअगर_निश्चित(layr->dn != शून्य);
	caअगर_निश्चित(layr->dn->transmit != शून्य);

	अगर (cfpkt_add_head(pkt, &पंचांगp, 1) < 0) अणु
		pr_err("Packet is erroneous!\n");
		ret = -EPROTO;
		जाओ err;
	पूर्ण

	/* Add info-> क्रम MUX-layer to route the packet out. */
	info = cfpkt_info(pkt);
	info->channel_id = service->layer.id;
	info->hdr_len = 1;
	info->dev_info = &service->dev_info;
	वापस layr->dn->transmit(layr->dn, pkt);
err:
	cfpkt_destroy(pkt);
	वापस ret;
पूर्ण
