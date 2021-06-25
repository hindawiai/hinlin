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

#घोषणा container_obj(layr) ((काष्ठा cfsrvl *) layr)

अटल पूर्णांक cfdbgl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfdbgl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);

काष्ठा cflayer *cfdbgl_create(u8 channel_id, काष्ठा dev_info *dev_info)
अणु
	काष्ठा cfsrvl *dbg = kzalloc(माप(काष्ठा cfsrvl), GFP_ATOMIC);
	अगर (!dbg)
		वापस शून्य;
	caअगर_निश्चित(दुरत्व(काष्ठा cfsrvl, layer) == 0);
	cfsrvl_init(dbg, channel_id, dev_info, false);
	dbg->layer.receive = cfdbgl_receive;
	dbg->layer.transmit = cfdbgl_transmit;
	snम_लिखो(dbg->layer.name, CAIF_LAYER_NAME_SZ, "dbg%d", channel_id);
	वापस &dbg->layer;
पूर्ण

अटल पूर्णांक cfdbgl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	वापस layr->up->receive(layr->up, pkt);
पूर्ण

अटल पूर्णांक cfdbgl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	काष्ठा cfsrvl *service = container_obj(layr);
	काष्ठा caअगर_payload_info *info;
	पूर्णांक ret;

	अगर (!cfsrvl_पढ़ोy(service, &ret)) अणु
		cfpkt_destroy(pkt);
		वापस ret;
	पूर्ण

	/* Add info क्रम MUX-layer to route the packet out */
	info = cfpkt_info(pkt);
	info->channel_id = service->layer.id;
	info->dev_info = &service->dev_info;

	वापस layr->dn->transmit(layr->dn, pkt);
पूर्ण
