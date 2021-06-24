<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/cfcnfg.h>
#समावेश <net/caअगर/cfctrl.h>
#समावेश <net/caअगर/cfmuxl.h>
#समावेश <net/caअगर/cffrml.h>
#समावेश <net/caअगर/cfserl.h>
#समावेश <net/caअगर/cfsrvl.h>
#समावेश <net/caअगर/caअगर_dev.h>

#घोषणा container_obj(layr) container_of(layr, काष्ठा cfcnfg, layer)

/* Inक्रमmation about CAIF physical पूर्णांकerfaces held by Config Module in order
 * to manage physical पूर्णांकerfaces
 */
काष्ठा cfcnfg_phyinfo अणु
	काष्ठा list_head node;
	bool up;

	/* Poपूर्णांकer to the layer below the MUX (framing layer) */
	काष्ठा cflayer *frm_layer;
	/* Poपूर्णांकer to the lowest actual physical layer */
	काष्ठा cflayer *phy_layer;
	/* Unique identअगरier of the physical पूर्णांकerface */
	अचिन्हित पूर्णांक id;
	/* Preference of the physical in पूर्णांकerface */
	क्रमागत cfcnfg_phy_preference pref;

	/* Inक्रमmation about the physical device */
	काष्ठा dev_info dev_info;

	/* Interface index */
	पूर्णांक अगरindex;

	/* Protocol head room added क्रम CAIF link layer */
	पूर्णांक head_room;

	/* Use Start of frame checksum */
	bool use_fcs;
पूर्ण;

काष्ठा cfcnfg अणु
	काष्ठा cflayer layer;
	काष्ठा cflayer *ctrl;
	काष्ठा cflayer *mux;
	काष्ठा list_head phys;
	काष्ठा mutex lock;
पूर्ण;

अटल व्योम cfcnfg_linkup_rsp(काष्ठा cflayer *layer, u8 channel_id,
			      क्रमागत cfctrl_srv serv, u8 phyid,
			      काष्ठा cflayer *adapt_layer);
अटल व्योम cfcnfg_linkdestroy_rsp(काष्ठा cflayer *layer, u8 channel_id);
अटल व्योम cfcnfg_reject_rsp(काष्ठा cflayer *layer, u8 channel_id,
			      काष्ठा cflayer *adapt_layer);
अटल व्योम cfctrl_resp_func(व्योम);
अटल व्योम cfctrl_क्रमागत_resp(व्योम);

काष्ठा cfcnfg *cfcnfg_create(व्योम)
अणु
	काष्ठा cfcnfg *this;
	काष्ठा cfctrl_rsp *resp;

	might_sleep();

	/* Initiate this layer */
	this = kzalloc(माप(काष्ठा cfcnfg), GFP_ATOMIC);
	अगर (!this)
		वापस शून्य;
	this->mux = cfmuxl_create();
	अगर (!this->mux)
		जाओ out_of_mem;
	this->ctrl = cfctrl_create();
	अगर (!this->ctrl)
		जाओ out_of_mem;
	/* Initiate response functions */
	resp = cfctrl_get_respfuncs(this->ctrl);
	resp->क्रमागत_rsp = cfctrl_क्रमागत_resp;
	resp->linkerror_ind = cfctrl_resp_func;
	resp->linkdestroy_rsp = cfcnfg_linkdestroy_rsp;
	resp->sleep_rsp = cfctrl_resp_func;
	resp->wake_rsp = cfctrl_resp_func;
	resp->restart_rsp = cfctrl_resp_func;
	resp->radioset_rsp = cfctrl_resp_func;
	resp->linksetup_rsp = cfcnfg_linkup_rsp;
	resp->reject_rsp = cfcnfg_reject_rsp;
	INIT_LIST_HEAD(&this->phys);

	cfmuxl_set_uplayer(this->mux, this->ctrl, 0);
	layer_set_dn(this->ctrl, this->mux);
	layer_set_up(this->ctrl, this);
	mutex_init(&this->lock);

	वापस this;
out_of_mem:
	synchronize_rcu();

	kमुक्त(this->mux);
	kमुक्त(this->ctrl);
	kमुक्त(this);
	वापस शून्य;
पूर्ण

व्योम cfcnfg_हटाओ(काष्ठा cfcnfg *cfg)
अणु
	might_sleep();
	अगर (cfg) अणु
		synchronize_rcu();

		kमुक्त(cfg->mux);
		cfctrl_हटाओ(cfg->ctrl);
		kमुक्त(cfg);
	पूर्ण
पूर्ण

अटल व्योम cfctrl_resp_func(व्योम)
अणु
पूर्ण

अटल काष्ठा cfcnfg_phyinfo *cfcnfg_get_phyinfo_rcu(काष्ठा cfcnfg *cnfg,
						     u8 phyid)
अणु
	काष्ठा cfcnfg_phyinfo *phy;

	list_क्रम_each_entry_rcu(phy, &cnfg->phys, node)
		अगर (phy->id == phyid)
			वापस phy;
	वापस शून्य;
पूर्ण

अटल व्योम cfctrl_क्रमागत_resp(व्योम)
अणु
पूर्ण

अटल काष्ठा dev_info *cfcnfg_get_phyid(काष्ठा cfcnfg *cnfg,
				  क्रमागत cfcnfg_phy_preference phy_pref)
अणु
	/* Try to match with specअगरied preference */
	काष्ठा cfcnfg_phyinfo *phy;

	list_क्रम_each_entry_rcu(phy, &cnfg->phys, node) अणु
		अगर (phy->up && phy->pref == phy_pref &&
				phy->frm_layer != शून्य)

			वापस &phy->dev_info;
	पूर्ण

	/* Otherwise just वापस something */
	list_क्रम_each_entry_rcu(phy, &cnfg->phys, node)
		अगर (phy->up)
			वापस &phy->dev_info;

	वापस शून्य;
पूर्ण

अटल पूर्णांक cfcnfg_get_id_from_अगरi(काष्ठा cfcnfg *cnfg, पूर्णांक अगरi)
अणु
	काष्ठा cfcnfg_phyinfo *phy;

	list_क्रम_each_entry_rcu(phy, &cnfg->phys, node)
		अगर (phy->अगरindex == अगरi && phy->up)
			वापस phy->id;
	वापस -ENODEV;
पूर्ण

पूर्णांक caअगर_disconnect_client(काष्ठा net *net, काष्ठा cflayer *adap_layer)
अणु
	u8 channel_id;
	काष्ठा cfcnfg *cfg = get_cfcnfg(net);

	caअगर_निश्चित(adap_layer != शून्य);
	cfctrl_cancel_req(cfg->ctrl, adap_layer);
	channel_id = adap_layer->id;
	अगर (channel_id != 0) अणु
		काष्ठा cflayer *servl;
		servl = cfmuxl_हटाओ_uplayer(cfg->mux, channel_id);
		cfctrl_linkकरोwn_req(cfg->ctrl, channel_id, adap_layer);
		अगर (servl != शून्य)
			layer_set_up(servl, शून्य);
	पूर्ण अन्यथा
		pr_debug("nothing to disconnect\n");

	/* Do RCU sync beक्रमe initiating cleanup */
	synchronize_rcu();
	अगर (adap_layer->ctrlcmd != शून्य)
		adap_layer->ctrlcmd(adap_layer, CAIF_CTRLCMD_DEINIT_RSP, 0);
	वापस 0;

पूर्ण
EXPORT_SYMBOL(caअगर_disconnect_client);

अटल व्योम cfcnfg_linkdestroy_rsp(काष्ठा cflayer *layer, u8 channel_id)
अणु
पूर्ण

अटल स्थिर पूर्णांक protohead[CFCTRL_SRV_MASK] = अणु
	[CFCTRL_SRV_VEI] = 4,
	[CFCTRL_SRV_DATAGRAM] = 7,
	[CFCTRL_SRV_UTIL] = 4,
	[CFCTRL_SRV_RFM] = 3,
	[CFCTRL_SRV_DBG] = 3,
पूर्ण;


अटल पूर्णांक caअगर_connect_req_to_link_param(काष्ठा cfcnfg *cnfg,
					  काष्ठा caअगर_connect_request *s,
					  काष्ठा cfctrl_link_param *l)
अणु
	काष्ठा dev_info *dev_info;
	क्रमागत cfcnfg_phy_preference pref;
	पूर्णांक res;

	स_रखो(l, 0, माप(*l));
	/* In caअगर protocol low value is high priority */
	l->priority = CAIF_PRIO_MAX - s->priority + 1;

	अगर (s->अगरindex != 0) अणु
		res = cfcnfg_get_id_from_अगरi(cnfg, s->अगरindex);
		अगर (res < 0)
			वापस res;
		l->phyid = res;
	पूर्ण अन्यथा अणु
		चयन (s->link_selector) अणु
		हाल CAIF_LINK_HIGH_BANDW:
			pref = CFPHYPREF_HIGH_BW;
			अवरोध;
		हाल CAIF_LINK_LOW_LATENCY:
			pref = CFPHYPREF_LOW_LAT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		dev_info = cfcnfg_get_phyid(cnfg, pref);
		अगर (dev_info == शून्य)
			वापस -ENODEV;
		l->phyid = dev_info->id;
	पूर्ण
	चयन (s->protocol) अणु
	हाल CAIFPROTO_AT:
		l->linktype = CFCTRL_SRV_VEI;
		l->endpoपूर्णांक = (s->sockaddr.u.at.type >> 2) & 0x3;
		l->chtype = s->sockaddr.u.at.type & 0x3;
		अवरोध;
	हाल CAIFPROTO_DATAGRAM:
		l->linktype = CFCTRL_SRV_DATAGRAM;
		l->chtype = 0x00;
		l->u.datagram.connid = s->sockaddr.u.dgm.connection_id;
		अवरोध;
	हाल CAIFPROTO_DATAGRAM_LOOP:
		l->linktype = CFCTRL_SRV_DATAGRAM;
		l->chtype = 0x03;
		l->endpoपूर्णांक = 0x00;
		l->u.datagram.connid = s->sockaddr.u.dgm.connection_id;
		अवरोध;
	हाल CAIFPROTO_RFM:
		l->linktype = CFCTRL_SRV_RFM;
		l->u.datagram.connid = s->sockaddr.u.rfm.connection_id;
		strlcpy(l->u.rfm.volume, s->sockaddr.u.rfm.volume,
			माप(l->u.rfm.volume));
		अवरोध;
	हाल CAIFPROTO_UTIL:
		l->linktype = CFCTRL_SRV_UTIL;
		l->endpoपूर्णांक = 0x00;
		l->chtype = 0x00;
		strlcpy(l->u.utility.name, s->sockaddr.u.util.service,
			माप(l->u.utility.name));
		caअगर_निश्चित(माप(l->u.utility.name) > 10);
		l->u.utility.paramlen = s->param.size;
		अगर (l->u.utility.paramlen > माप(l->u.utility.params))
			l->u.utility.paramlen = माप(l->u.utility.params);

		स_नकल(l->u.utility.params, s->param.data,
		       l->u.utility.paramlen);

		अवरोध;
	हाल CAIFPROTO_DEBUG:
		l->linktype = CFCTRL_SRV_DBG;
		l->endpoपूर्णांक = s->sockaddr.u.dbg.service;
		l->chtype = s->sockaddr.u.dbg.type;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक caअगर_connect_client(काष्ठा net *net, काष्ठा caअगर_connect_request *conn_req,
			काष्ठा cflayer *adap_layer, पूर्णांक *अगरindex,
			पूर्णांक *proto_head, पूर्णांक *proto_tail)
अणु
	काष्ठा cflayer *frml;
	काष्ठा cfcnfg_phyinfo *phy;
	पूर्णांक err;
	काष्ठा cfctrl_link_param param;
	काष्ठा cfcnfg *cfg = get_cfcnfg(net);

	rcu_पढ़ो_lock();
	err = caअगर_connect_req_to_link_param(cfg, conn_req, &param);
	अगर (err)
		जाओ unlock;

	phy = cfcnfg_get_phyinfo_rcu(cfg, param.phyid);
	अगर (!phy) अणु
		err = -ENODEV;
		जाओ unlock;
	पूर्ण
	err = -EINVAL;

	अगर (adap_layer == शून्य) अणु
		pr_err("adap_layer is zero\n");
		जाओ unlock;
	पूर्ण
	अगर (adap_layer->receive == शून्य) अणु
		pr_err("adap_layer->receive is NULL\n");
		जाओ unlock;
	पूर्ण
	अगर (adap_layer->ctrlcmd == शून्य) अणु
		pr_err("adap_layer->ctrlcmd == NULL\n");
		जाओ unlock;
	पूर्ण

	err = -ENODEV;
	frml = phy->frm_layer;
	अगर (frml == शून्य) अणु
		pr_err("Specified PHY type does not exist!\n");
		जाओ unlock;
	पूर्ण
	caअगर_निश्चित(param.phyid == phy->id);
	caअगर_निश्चित(phy->frm_layer->id ==
		     param.phyid);
	caअगर_निश्चित(phy->phy_layer->id ==
		     param.phyid);

	*अगरindex = phy->अगरindex;
	*proto_tail = 2;
	*proto_head = protohead[param.linktype] + phy->head_room;

	rcu_पढ़ो_unlock();

	/* FIXME: ENUMERATE INITIALLY WHEN ACTIVATING PHYSICAL INTERFACE */
	cfctrl_क्रमागत_req(cfg->ctrl, param.phyid);
	वापस cfctrl_linkup_request(cfg->ctrl, &param, adap_layer);

unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(caअगर_connect_client);

अटल व्योम cfcnfg_reject_rsp(काष्ठा cflayer *layer, u8 channel_id,
			      काष्ठा cflayer *adapt_layer)
अणु
	अगर (adapt_layer != शून्य && adapt_layer->ctrlcmd != शून्य)
		adapt_layer->ctrlcmd(adapt_layer,
				     CAIF_CTRLCMD_INIT_FAIL_RSP, 0);
पूर्ण

अटल व्योम
cfcnfg_linkup_rsp(काष्ठा cflayer *layer, u8 channel_id, क्रमागत cfctrl_srv serv,
		  u8 phyid, काष्ठा cflayer *adapt_layer)
अणु
	काष्ठा cfcnfg *cnfg = container_obj(layer);
	काष्ठा cflayer *servicel = शून्य;
	काष्ठा cfcnfg_phyinfo *phyinfo;
	काष्ठा net_device *netdev;

	अगर (channel_id == 0) अणु
		pr_warn("received channel_id zero\n");
		अगर (adapt_layer != शून्य && adapt_layer->ctrlcmd != शून्य)
			adapt_layer->ctrlcmd(adapt_layer,
						CAIF_CTRLCMD_INIT_FAIL_RSP, 0);
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();

	अगर (adapt_layer == शून्य) अणु
		pr_debug("link setup response but no client exist, send linkdown back\n");
		cfctrl_linkकरोwn_req(cnfg->ctrl, channel_id, शून्य);
		जाओ unlock;
	पूर्ण

	caअगर_निश्चित(cnfg != शून्य);
	caअगर_निश्चित(phyid != 0);

	phyinfo = cfcnfg_get_phyinfo_rcu(cnfg, phyid);
	अगर (phyinfo == शून्य) अणु
		pr_err("ERROR: Link Layer Device disappeared while connecting\n");
		जाओ unlock;
	पूर्ण

	caअगर_निश्चित(phyinfo != शून्य);
	caअगर_निश्चित(phyinfo->id == phyid);
	caअगर_निश्चित(phyinfo->phy_layer != शून्य);
	caअगर_निश्चित(phyinfo->phy_layer->id == phyid);

	adapt_layer->id = channel_id;

	चयन (serv) अणु
	हाल CFCTRL_SRV_VEI:
		servicel = cfvei_create(channel_id, &phyinfo->dev_info);
		अवरोध;
	हाल CFCTRL_SRV_DATAGRAM:
		servicel = cfdgml_create(channel_id,
					&phyinfo->dev_info);
		अवरोध;
	हाल CFCTRL_SRV_RFM:
		netdev = phyinfo->dev_info.dev;
		servicel = cfrfml_create(channel_id, &phyinfo->dev_info,
						netdev->mtu);
		अवरोध;
	हाल CFCTRL_SRV_UTIL:
		servicel = cfutill_create(channel_id, &phyinfo->dev_info);
		अवरोध;
	हाल CFCTRL_SRV_VIDEO:
		servicel = cfvidl_create(channel_id, &phyinfo->dev_info);
		अवरोध;
	हाल CFCTRL_SRV_DBG:
		servicel = cfdbgl_create(channel_id, &phyinfo->dev_info);
		अवरोध;
	शेष:
		pr_err("Protocol error. Link setup response - unknown channel type\n");
		जाओ unlock;
	पूर्ण
	अगर (!servicel)
		जाओ unlock;
	layer_set_dn(servicel, cnfg->mux);
	cfmuxl_set_uplayer(cnfg->mux, servicel, channel_id);
	layer_set_up(servicel, adapt_layer);
	layer_set_dn(adapt_layer, servicel);

	rcu_पढ़ो_unlock();

	servicel->ctrlcmd(servicel, CAIF_CTRLCMD_INIT_RSP, 0);
	वापस;
unlock:
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक
cfcnfg_add_phy_layer(काष्ठा cfcnfg *cnfg,
		     काष्ठा net_device *dev, काष्ठा cflayer *phy_layer,
		     क्रमागत cfcnfg_phy_preference pref,
		     काष्ठा cflayer *link_support,
		     bool fcs, पूर्णांक head_room)
अणु
	काष्ठा cflayer *frml;
	काष्ठा cfcnfg_phyinfo *phyinfo = शून्य;
	पूर्णांक i, res = 0;
	u8 phyid;

	mutex_lock(&cnfg->lock);

	/* CAIF protocol allow maximum 6 link-layers */
	क्रम (i = 0; i < 7; i++) अणु
		phyid = (dev->अगरindex + i) & 0x7;
		अगर (phyid == 0)
			जारी;
		अगर (cfcnfg_get_phyinfo_rcu(cnfg, phyid) == शून्य)
			जाओ got_phyid;
	पूर्ण
	pr_warn("Too many CAIF Link Layers (max 6)\n");
	res = -EEXIST;
	जाओ out;

got_phyid:
	phyinfo = kzalloc(माप(काष्ठा cfcnfg_phyinfo), GFP_ATOMIC);
	अगर (!phyinfo) अणु
		res = -ENOMEM;
		जाओ out_err;
	पूर्ण

	phy_layer->id = phyid;
	phyinfo->pref = pref;
	phyinfo->id = phyid;
	phyinfo->dev_info.id = phyid;
	phyinfo->dev_info.dev = dev;
	phyinfo->phy_layer = phy_layer;
	phyinfo->अगरindex = dev->अगरindex;
	phyinfo->head_room = head_room;
	phyinfo->use_fcs = fcs;

	frml = cffrml_create(phyid, fcs);

	अगर (!frml) अणु
		res = -ENOMEM;
		जाओ out_err;
	पूर्ण
	phyinfo->frm_layer = frml;
	layer_set_up(frml, cnfg->mux);

	अगर (link_support != शून्य) अणु
		link_support->id = phyid;
		layer_set_dn(frml, link_support);
		layer_set_up(link_support, frml);
		layer_set_dn(link_support, phy_layer);
		layer_set_up(phy_layer, link_support);
	पूर्ण अन्यथा अणु
		layer_set_dn(frml, phy_layer);
		layer_set_up(phy_layer, frml);
	पूर्ण

	list_add_rcu(&phyinfo->node, &cnfg->phys);
out:
	mutex_unlock(&cnfg->lock);
	वापस res;

out_err:
	kमुक्त(phyinfo);
	mutex_unlock(&cnfg->lock);
	वापस res;
पूर्ण
EXPORT_SYMBOL(cfcnfg_add_phy_layer);

पूर्णांक cfcnfg_set_phy_state(काष्ठा cfcnfg *cnfg, काष्ठा cflayer *phy_layer,
			 bool up)
अणु
	काष्ठा cfcnfg_phyinfo *phyinfo;

	rcu_पढ़ो_lock();
	phyinfo = cfcnfg_get_phyinfo_rcu(cnfg, phy_layer->id);
	अगर (phyinfo == शून्य) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण

	अगर (phyinfo->up == up) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	phyinfo->up = up;

	अगर (up) अणु
		cffrml_hold(phyinfo->frm_layer);
		cfmuxl_set_dnlayer(cnfg->mux, phyinfo->frm_layer,
					phy_layer->id);
	पूर्ण अन्यथा अणु
		cfmuxl_हटाओ_dnlayer(cnfg->mux, phy_layer->id);
		cffrml_put(phyinfo->frm_layer);
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfcnfg_set_phy_state);

पूर्णांक cfcnfg_del_phy_layer(काष्ठा cfcnfg *cnfg, काष्ठा cflayer *phy_layer)
अणु
	काष्ठा cflayer *frml, *frml_dn;
	u16 phyid;
	काष्ठा cfcnfg_phyinfo *phyinfo;

	might_sleep();

	mutex_lock(&cnfg->lock);

	phyid = phy_layer->id;
	phyinfo = cfcnfg_get_phyinfo_rcu(cnfg, phyid);

	अगर (phyinfo == शून्य) अणु
		mutex_unlock(&cnfg->lock);
		वापस 0;
	पूर्ण
	caअगर_निश्चित(phyid == phyinfo->id);
	caअगर_निश्चित(phy_layer == phyinfo->phy_layer);
	caअगर_निश्चित(phy_layer->id == phyid);
	caअगर_निश्चित(phyinfo->frm_layer->id == phyid);

	list_del_rcu(&phyinfo->node);
	synchronize_rcu();

	/* Fail अगर reference count is not zero */
	अगर (cffrml_refcnt_पढ़ो(phyinfo->frm_layer) != 0) अणु
		pr_info("Wait for device inuse\n");
		list_add_rcu(&phyinfo->node, &cnfg->phys);
		mutex_unlock(&cnfg->lock);
		वापस -EAGAIN;
	पूर्ण

	frml = phyinfo->frm_layer;
	frml_dn = frml->dn;
	cffrml_set_uplayer(frml, शून्य);
	cffrml_set_dnlayer(frml, शून्य);
	अगर (phy_layer != frml_dn) अणु
		layer_set_up(frml_dn, शून्य);
		layer_set_dn(frml_dn, शून्य);
	पूर्ण
	layer_set_up(phy_layer, शून्य);

	अगर (phyinfo->phy_layer != frml_dn)
		kमुक्त(frml_dn);

	cffrml_मुक्त(frml);
	kमुक्त(phyinfo);
	mutex_unlock(&cnfg->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfcnfg_del_phy_layer);
