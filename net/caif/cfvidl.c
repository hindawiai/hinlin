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

अटल पूर्णांक cfvidl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfvidl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);

काष्ठा cflayer *cfvidl_create(u8 channel_id, काष्ठा dev_info *dev_info)
अणु
	काष्ठा cfsrvl *vid = kzalloc(माप(काष्ठा cfsrvl), GFP_ATOMIC);
	अगर (!vid)
		वापस शून्य;
	caअगर_निश्चित(दुरत्व(काष्ठा cfsrvl, layer) == 0);

	cfsrvl_init(vid, channel_id, dev_info, false);
	vid->layer.receive = cfvidl_receive;
	vid->layer.transmit = cfvidl_transmit;
	snम_लिखो(vid->layer.name, CAIF_LAYER_NAME_SZ, "vid1");
	वापस &vid->layer;
पूर्ण

अटल पूर्णांक cfvidl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	u32 videoheader;
	अगर (cfpkt_extr_head(pkt, &videoheader, 4) < 0) अणु
		pr_err("Packet is erroneous!\n");
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण
	वापस layr->up->receive(layr->up, pkt);
पूर्ण

अटल पूर्णांक cfvidl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	काष्ठा cfsrvl *service = container_obj(layr);
	काष्ठा caअगर_payload_info *info;
	u32 videoheader = 0;
	पूर्णांक ret;

	अगर (!cfsrvl_पढ़ोy(service, &ret)) अणु
		cfpkt_destroy(pkt);
		वापस ret;
	पूर्ण

	cfpkt_add_head(pkt, &videoheader, 4);
	/* Add info क्रम MUX-layer to route the packet out */
	info = cfpkt_info(pkt);
	info->channel_id = service->layer.id;
	info->dev_info = &service->dev_info;
	वापस layr->dn->transmit(layr->dn, pkt);
पूर्ण
