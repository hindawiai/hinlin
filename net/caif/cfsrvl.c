<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfsrvl.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/caअगर_dev.h>

#घोषणा SRVL_CTRL_PKT_SIZE 1
#घोषणा SRVL_FLOW_OFF 0x81
#घोषणा SRVL_FLOW_ON  0x80
#घोषणा SRVL_SET_PIN  0x82

#घोषणा container_obj(layr) container_of(layr, काष्ठा cfsrvl, layer)

अटल व्योम cfservl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			    पूर्णांक phyid)
अणु
	काष्ठा cfsrvl *service = container_obj(layr);

	अगर (layr->up == शून्य || layr->up->ctrlcmd == शून्य)
		वापस;

	चयन (ctrl) अणु
	हाल CAIF_CTRLCMD_INIT_RSP:
		service->खोलो = true;
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		अवरोध;
	हाल CAIF_CTRLCMD_DEINIT_RSP:
	हाल CAIF_CTRLCMD_INIT_FAIL_RSP:
		service->खोलो = false;
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		अवरोध;
	हाल _CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND:
		अगर (phyid != service->dev_info.id)
			अवरोध;
		अगर (service->modem_flow_on)
			layr->up->ctrlcmd(layr->up,
					  CAIF_CTRLCMD_FLOW_OFF_IND, phyid);
		service->phy_flow_on = false;
		अवरोध;
	हाल _CAIF_CTRLCMD_PHYIF_FLOW_ON_IND:
		अगर (phyid != service->dev_info.id)
			वापस;
		अगर (service->modem_flow_on) अणु
			layr->up->ctrlcmd(layr->up,
					   CAIF_CTRLCMD_FLOW_ON_IND,
					   phyid);
		पूर्ण
		service->phy_flow_on = true;
		अवरोध;
	हाल CAIF_CTRLCMD_FLOW_OFF_IND:
		अगर (service->phy_flow_on) अणु
			layr->up->ctrlcmd(layr->up,
					  CAIF_CTRLCMD_FLOW_OFF_IND, phyid);
		पूर्ण
		service->modem_flow_on = false;
		अवरोध;
	हाल CAIF_CTRLCMD_FLOW_ON_IND:
		अगर (service->phy_flow_on) अणु
			layr->up->ctrlcmd(layr->up,
					  CAIF_CTRLCMD_FLOW_ON_IND, phyid);
		पूर्ण
		service->modem_flow_on = true;
		अवरोध;
	हाल _CAIF_CTRLCMD_PHYIF_DOWN_IND:
		/* In हाल पूर्णांकerface is करोwn, let's fake a हटाओ shutकरोwn */
		layr->up->ctrlcmd(layr->up,
				CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND, phyid);
		अवरोध;
	हाल CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND:
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		अवरोध;
	शेष:
		pr_warn("Unexpected ctrl in cfsrvl (%d)\n", ctrl);
		/* We have both modem and phy flow on, send flow on */
		layr->up->ctrlcmd(layr->up, ctrl, phyid);
		service->phy_flow_on = true;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cfservl_modemcmd(काष्ठा cflayer *layr, क्रमागत caअगर_modemcmd ctrl)
अणु
	काष्ठा cfsrvl *service = container_obj(layr);

	caअगर_निश्चित(layr != शून्य);
	caअगर_निश्चित(layr->dn != शून्य);
	caअगर_निश्चित(layr->dn->transmit != शून्य);

	अगर (!service->supports_flowctrl)
		वापस 0;

	चयन (ctrl) अणु
	हाल CAIF_MODEMCMD_FLOW_ON_REQ:
		अणु
			काष्ठा cfpkt *pkt;
			काष्ठा caअगर_payload_info *info;
			u8 flow_on = SRVL_FLOW_ON;
			pkt = cfpkt_create(SRVL_CTRL_PKT_SIZE);
			अगर (!pkt)
				वापस -ENOMEM;

			अगर (cfpkt_add_head(pkt, &flow_on, 1) < 0) अणु
				pr_err("Packet is erroneous!\n");
				cfpkt_destroy(pkt);
				वापस -EPROTO;
			पूर्ण
			info = cfpkt_info(pkt);
			info->channel_id = service->layer.id;
			info->hdr_len = 1;
			info->dev_info = &service->dev_info;
			cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
			वापस layr->dn->transmit(layr->dn, pkt);
		पूर्ण
	हाल CAIF_MODEMCMD_FLOW_OFF_REQ:
		अणु
			काष्ठा cfpkt *pkt;
			काष्ठा caअगर_payload_info *info;
			u8 flow_off = SRVL_FLOW_OFF;
			pkt = cfpkt_create(SRVL_CTRL_PKT_SIZE);
			अगर (!pkt)
				वापस -ENOMEM;

			अगर (cfpkt_add_head(pkt, &flow_off, 1) < 0) अणु
				pr_err("Packet is erroneous!\n");
				cfpkt_destroy(pkt);
				वापस -EPROTO;
			पूर्ण
			info = cfpkt_info(pkt);
			info->channel_id = service->layer.id;
			info->hdr_len = 1;
			info->dev_info = &service->dev_info;
			cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
			वापस layr->dn->transmit(layr->dn, pkt);
		पूर्ण
	शेष:
	  अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम cfsrvl_release(काष्ठा cflayer *layer)
अणु
	काष्ठा cfsrvl *service = container_of(layer, काष्ठा cfsrvl, layer);
	kमुक्त(service);
पूर्ण

व्योम cfsrvl_init(काष्ठा cfsrvl *service,
		 u8 channel_id,
		 काष्ठा dev_info *dev_info,
		 bool supports_flowctrl)
अणु
	caअगर_निश्चित(दुरत्व(काष्ठा cfsrvl, layer) == 0);
	service->खोलो = false;
	service->modem_flow_on = true;
	service->phy_flow_on = true;
	service->layer.id = channel_id;
	service->layer.ctrlcmd = cfservl_ctrlcmd;
	service->layer.modemcmd = cfservl_modemcmd;
	service->dev_info = *dev_info;
	service->supports_flowctrl = supports_flowctrl;
	service->release = cfsrvl_release;
पूर्ण

bool cfsrvl_पढ़ोy(काष्ठा cfsrvl *service, पूर्णांक *err)
अणु
	अगर (!service->खोलो) अणु
		*err = -ENOTCONN;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

u8 cfsrvl_getphyid(काष्ठा cflayer *layer)
अणु
	काष्ठा cfsrvl *servl = container_obj(layer);
	वापस servl->dev_info.id;
पूर्ण

bool cfsrvl_phyid_match(काष्ठा cflayer *layer, पूर्णांक phyid)
अणु
	काष्ठा cfsrvl *servl = container_obj(layer);
	वापस servl->dev_info.id == phyid;
पूर्ण

व्योम caअगर_मुक्त_client(काष्ठा cflayer *adap_layer)
अणु
	काष्ठा cfsrvl *servl;
	अगर (adap_layer == शून्य || adap_layer->dn == शून्य)
		वापस;
	servl = container_obj(adap_layer->dn);
	servl->release(&servl->layer);
पूर्ण
EXPORT_SYMBOL(caअगर_मुक्त_client);

व्योम caअगर_client_रेजिस्टर_refcnt(काष्ठा cflayer *adapt_layer,
				 व्योम (*hold)(काष्ठा cflayer *lyr),
				 व्योम (*put)(काष्ठा cflayer *lyr))
अणु
	काष्ठा cfsrvl *service;

	अगर (WARN_ON(adapt_layer == शून्य || adapt_layer->dn == शून्य))
		वापस;
	service = container_of(adapt_layer->dn, काष्ठा cfsrvl, layer);
	service->hold = hold;
	service->put = put;
पूर्ण
EXPORT_SYMBOL(caअगर_client_रेजिस्टर_refcnt);
