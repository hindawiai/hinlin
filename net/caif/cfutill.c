<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfsrvl.h>
#समावेश <net/caअगर/cfpkt.h>

#घोषणा container_obj(layr) ((काष्ठा cfsrvl *) layr)
#घोषणा UTIL_PAYLOAD  0x00
#घोषणा UTIL_CMD_BIT  0x80
#घोषणा UTIL_REMOTE_SHUTDOWN 0x82
#घोषणा UTIL_FLOW_OFF 0x81
#घोषणा UTIL_FLOW_ON  0x80

अटल पूर्णांक cfutill_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfutill_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);

काष्ठा cflayer *cfutill_create(u8 channel_id, काष्ठा dev_info *dev_info)
अणु
	काष्ठा cfsrvl *util = kzalloc(माप(काष्ठा cfsrvl), GFP_ATOMIC);
	अगर (!util)
		वापस शून्य;
	caअगर_निश्चित(दुरत्व(काष्ठा cfsrvl, layer) == 0);
	cfsrvl_init(util, channel_id, dev_info, true);
	util->layer.receive = cfutill_receive;
	util->layer.transmit = cfutill_transmit;
	snम_लिखो(util->layer.name, CAIF_LAYER_NAME_SZ, "util1");
	वापस &util->layer;
पूर्ण

अटल पूर्णांक cfutill_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 cmd = -1;
	काष्ठा cfsrvl *service = container_obj(layr);
	caअगर_निश्चित(layr != शून्य);
	caअगर_निश्चित(layr->up != शून्य);
	caअगर_निश्चित(layr->up->receive != शून्य);
	caअगर_निश्चित(layr->up->ctrlcmd != शून्य);
	अगर (cfpkt_extr_head(pkt, &cmd, 1) < 0) अणु
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण

	चयन (cmd) अणु
	हाल UTIL_PAYLOAD:
		वापस layr->up->receive(layr->up, pkt);
	हाल UTIL_FLOW_OFF:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_OFF_IND, 0);
		cfpkt_destroy(pkt);
		वापस 0;
	हाल UTIL_FLOW_ON:
		layr->ctrlcmd(layr, CAIF_CTRLCMD_FLOW_ON_IND, 0);
		cfpkt_destroy(pkt);
		वापस 0;
	हाल UTIL_REMOTE_SHUTDOWN:	/* Remote Shutकरोwn Request */
		pr_err("REMOTE SHUTDOWN REQUEST RECEIVED\n");
		layr->ctrlcmd(layr, CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND, 0);
		service->खोलो = false;
		cfpkt_destroy(pkt);
		वापस 0;
	शेष:
		cfpkt_destroy(pkt);
		pr_warn("Unknown service control %d (0x%x)\n", cmd, cmd);
		वापस -EPROTO;
	पूर्ण
पूर्ण

अटल पूर्णांक cfutill_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u8 zero = 0;
	काष्ठा caअगर_payload_info *info;
	पूर्णांक ret;
	काष्ठा cfsrvl *service = container_obj(layr);
	caअगर_निश्चित(layr != शून्य);
	caअगर_निश्चित(layr->dn != शून्य);
	caअगर_निश्चित(layr->dn->transmit != शून्य);

	अगर (!cfsrvl_पढ़ोy(service, &ret)) अणु
		cfpkt_destroy(pkt);
		वापस ret;
	पूर्ण

	cfpkt_add_head(pkt, &zero, 1);
	/* Add info क्रम MUX-layer to route the packet out. */
	info = cfpkt_info(pkt);
	info->channel_id = service->layer.id;
	/*
	 * To optimize alignment, we add up the size of CAIF header beक्रमe
	 * payload.
	 */
	info->hdr_len = 1;
	info->dev_info = &service->dev_info;
	वापस layr->dn->transmit(layr->dn, pkt);
पूर्ण
