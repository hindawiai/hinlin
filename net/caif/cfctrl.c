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
#समावेश <linux/pkt_sched.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/cfctrl.h>

#घोषणा container_obj(layr) container_of(layr, काष्ठा cfctrl, serv.layer)
#घोषणा UTILITY_NAME_LENGTH 16
#घोषणा CFPKT_CTRL_PKT_LEN 20

#अगर_घोषित CAIF_NO_LOOP
अटल पूर्णांक handle_loop(काष्ठा cfctrl *ctrl,
		       पूर्णांक cmd, काष्ठा cfpkt *pkt)अणु
	वापस -1;
पूर्ण
#अन्यथा
अटल पूर्णांक handle_loop(काष्ठा cfctrl *ctrl,
		       पूर्णांक cmd, काष्ठा cfpkt *pkt);
#पूर्ण_अगर
अटल पूर्णांक cfctrl_recv(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल व्योम cfctrl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid);


काष्ठा cflayer *cfctrl_create(व्योम)
अणु
	काष्ठा dev_info dev_info;
	काष्ठा cfctrl *this =
		kzalloc(माप(काष्ठा cfctrl), GFP_ATOMIC);
	अगर (!this)
		वापस शून्य;
	caअगर_निश्चित(दुरत्व(काष्ठा cfctrl, serv.layer) == 0);
	स_रखो(&dev_info, 0, माप(dev_info));
	dev_info.id = 0xff;
	cfsrvl_init(&this->serv, 0, &dev_info, false);
	atomic_set(&this->req_seq_no, 1);
	atomic_set(&this->rsp_seq_no, 1);
	this->serv.layer.receive = cfctrl_recv;
	प्र_लिखो(this->serv.layer.name, "ctrl");
	this->serv.layer.ctrlcmd = cfctrl_ctrlcmd;
#अगर_अघोषित CAIF_NO_LOOP
	spin_lock_init(&this->loop_linkid_lock);
	this->loop_linkid = 1;
#पूर्ण_अगर
	spin_lock_init(&this->info_list_lock);
	INIT_LIST_HEAD(&this->list);
	वापस &this->serv.layer;
पूर्ण

व्योम cfctrl_हटाओ(काष्ठा cflayer *layer)
अणु
	काष्ठा cfctrl_request_info *p, *पंचांगp;
	काष्ठा cfctrl *ctrl = container_obj(layer);

	spin_lock_bh(&ctrl->info_list_lock);
	list_क्रम_each_entry_safe(p, पंचांगp, &ctrl->list, list) अणु
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण
	spin_unlock_bh(&ctrl->info_list_lock);
	kमुक्त(layer);
पूर्ण

अटल bool param_eq(स्थिर काष्ठा cfctrl_link_param *p1,
		     स्थिर काष्ठा cfctrl_link_param *p2)
अणु
	bool eq =
	    p1->linktype == p2->linktype &&
	    p1->priority == p2->priority &&
	    p1->phyid == p2->phyid &&
	    p1->endpoपूर्णांक == p2->endpoपूर्णांक && p1->chtype == p2->chtype;

	अगर (!eq)
		वापस false;

	चयन (p1->linktype) अणु
	हाल CFCTRL_SRV_VEI:
		वापस true;
	हाल CFCTRL_SRV_DATAGRAM:
		वापस p1->u.datagram.connid == p2->u.datagram.connid;
	हाल CFCTRL_SRV_RFM:
		वापस
		    p1->u.rfm.connid == p2->u.rfm.connid &&
		    म_भेद(p1->u.rfm.volume, p2->u.rfm.volume) == 0;
	हाल CFCTRL_SRV_UTIL:
		वापस
		    p1->u.utility.fअगरosize_kb == p2->u.utility.fअगरosize_kb
		    && p1->u.utility.fअगरosize_bufs ==
		    p2->u.utility.fअगरosize_bufs
		    && म_भेद(p1->u.utility.name, p2->u.utility.name) == 0
		    && p1->u.utility.paramlen == p2->u.utility.paramlen
		    && स_भेद(p1->u.utility.params, p2->u.utility.params,
			      p1->u.utility.paramlen) == 0;

	हाल CFCTRL_SRV_VIDEO:
		वापस p1->u.video.connid == p2->u.video.connid;
	हाल CFCTRL_SRV_DBG:
		वापस true;
	हाल CFCTRL_SRV_DECM:
		वापस false;
	शेष:
		वापस false;
	पूर्ण
	वापस false;
पूर्ण

अटल bool cfctrl_req_eq(स्थिर काष्ठा cfctrl_request_info *r1,
			  स्थिर काष्ठा cfctrl_request_info *r2)
अणु
	अगर (r1->cmd != r2->cmd)
		वापस false;
	अगर (r1->cmd == CFCTRL_CMD_LINK_SETUP)
		वापस param_eq(&r1->param, &r2->param);
	अन्यथा
		वापस r1->channel_id == r2->channel_id;
पूर्ण

/* Insert request at the end */
अटल व्योम cfctrl_insert_req(काष्ठा cfctrl *ctrl,
			      काष्ठा cfctrl_request_info *req)
अणु
	spin_lock_bh(&ctrl->info_list_lock);
	atomic_inc(&ctrl->req_seq_no);
	req->sequence_no = atomic_पढ़ो(&ctrl->req_seq_no);
	list_add_tail(&req->list, &ctrl->list);
	spin_unlock_bh(&ctrl->info_list_lock);
पूर्ण

/* Compare and हटाओ request */
अटल काष्ठा cfctrl_request_info *cfctrl_हटाओ_req(काष्ठा cfctrl *ctrl,
						काष्ठा cfctrl_request_info *req)
अणु
	काष्ठा cfctrl_request_info *p, *पंचांगp, *first;

	first = list_first_entry(&ctrl->list, काष्ठा cfctrl_request_info, list);

	list_क्रम_each_entry_safe(p, पंचांगp, &ctrl->list, list) अणु
		अगर (cfctrl_req_eq(req, p)) अणु
			अगर (p != first)
				pr_warn("Requests are not received in order\n");

			atomic_set(&ctrl->rsp_seq_no,
					 p->sequence_no);
			list_del(&p->list);
			जाओ out;
		पूर्ण
	पूर्ण
	p = शून्य;
out:
	वापस p;
पूर्ण

काष्ठा cfctrl_rsp *cfctrl_get_respfuncs(काष्ठा cflayer *layer)
अणु
	काष्ठा cfctrl *this = container_obj(layer);
	वापस &this->res;
पूर्ण

अटल व्योम init_info(काष्ठा caअगर_payload_info *info, काष्ठा cfctrl *cfctrl)
अणु
	info->hdr_len = 0;
	info->channel_id = cfctrl->serv.layer.id;
	info->dev_info = &cfctrl->serv.dev_info;
पूर्ण

व्योम cfctrl_क्रमागत_req(काष्ठा cflayer *layer, u8 physlinkid)
अणु
	काष्ठा cfpkt *pkt;
	काष्ठा cfctrl *cfctrl = container_obj(layer);
	काष्ठा cflayer *dn = cfctrl->serv.layer.dn;

	अगर (!dn) अणु
		pr_debug("not able to send enum request\n");
		वापस;
	पूर्ण
	pkt = cfpkt_create(CFPKT_CTRL_PKT_LEN);
	अगर (!pkt)
		वापस;
	caअगर_निश्चित(दुरत्व(काष्ठा cfctrl, serv.layer) == 0);
	init_info(cfpkt_info(pkt), cfctrl);
	cfpkt_info(pkt)->dev_info->id = physlinkid;
	cfctrl->serv.dev_info.id = physlinkid;
	cfpkt_addbdy(pkt, CFCTRL_CMD_ENUM);
	cfpkt_addbdy(pkt, physlinkid);
	cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
	dn->transmit(dn, pkt);
पूर्ण

पूर्णांक cfctrl_linkup_request(काष्ठा cflayer *layer,
			  काष्ठा cfctrl_link_param *param,
			  काष्ठा cflayer *user_layer)
अणु
	काष्ठा cfctrl *cfctrl = container_obj(layer);
	u32 पंचांगp32;
	u16 पंचांगp16;
	u8 पंचांगp8;
	काष्ठा cfctrl_request_info *req;
	पूर्णांक ret;
	अक्षर utility_name[16];
	काष्ठा cfpkt *pkt;
	काष्ठा cflayer *dn = cfctrl->serv.layer.dn;

	अगर (!dn) अणु
		pr_debug("not able to send linkup request\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cfctrl_cancel_req(layer, user_layer) > 0) अणु
		/* Slight Paranoia, check अगर alपढ़ोy connecting */
		pr_err("Duplicate connect request for same client\n");
		WARN_ON(1);
		वापस -EALREADY;
	पूर्ण

	pkt = cfpkt_create(CFPKT_CTRL_PKT_LEN);
	अगर (!pkt)
		वापस -ENOMEM;
	cfpkt_addbdy(pkt, CFCTRL_CMD_LINK_SETUP);
	cfpkt_addbdy(pkt, (param->chtype << 4) | param->linktype);
	cfpkt_addbdy(pkt, (param->priority << 3) | param->phyid);
	cfpkt_addbdy(pkt, param->endpoपूर्णांक & 0x03);

	चयन (param->linktype) अणु
	हाल CFCTRL_SRV_VEI:
		अवरोध;
	हाल CFCTRL_SRV_VIDEO:
		cfpkt_addbdy(pkt, (u8) param->u.video.connid);
		अवरोध;
	हाल CFCTRL_SRV_DBG:
		अवरोध;
	हाल CFCTRL_SRV_DATAGRAM:
		पंचांगp32 = cpu_to_le32(param->u.datagram.connid);
		cfpkt_add_body(pkt, &पंचांगp32, 4);
		अवरोध;
	हाल CFCTRL_SRV_RFM:
		/* Conकाष्ठा a frame, convert DatagramConnectionID to network
		 * क्रमmat दीर्घ and copy it out...
		 */
		पंचांगp32 = cpu_to_le32(param->u.rfm.connid);
		cfpkt_add_body(pkt, &पंचांगp32, 4);
		/* Add volume name, including zero termination... */
		cfpkt_add_body(pkt, param->u.rfm.volume,
			       म_माप(param->u.rfm.volume) + 1);
		अवरोध;
	हाल CFCTRL_SRV_UTIL:
		पंचांगp16 = cpu_to_le16(param->u.utility.fअगरosize_kb);
		cfpkt_add_body(pkt, &पंचांगp16, 2);
		पंचांगp16 = cpu_to_le16(param->u.utility.fअगरosize_bufs);
		cfpkt_add_body(pkt, &पंचांगp16, 2);
		स_रखो(utility_name, 0, माप(utility_name));
		strlcpy(utility_name, param->u.utility.name,
			UTILITY_NAME_LENGTH);
		cfpkt_add_body(pkt, utility_name, UTILITY_NAME_LENGTH);
		पंचांगp8 = param->u.utility.paramlen;
		cfpkt_add_body(pkt, &पंचांगp8, 1);
		cfpkt_add_body(pkt, param->u.utility.params,
			       param->u.utility.paramlen);
		अवरोध;
	शेष:
		pr_warn("Request setup of bad link type = %d\n",
			param->linktype);
		वापस -EINVAL;
	पूर्ण
	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;
	req->client_layer = user_layer;
	req->cmd = CFCTRL_CMD_LINK_SETUP;
	req->param = *param;
	cfctrl_insert_req(cfctrl, req);
	init_info(cfpkt_info(pkt), cfctrl);
	/*
	 * NOTE:Always send linkup and linkकरोwn request on the same
	 *	device as the payload. Otherwise old queued up payload
	 *	might arrive with the newly allocated channel ID.
	 */
	cfpkt_info(pkt)->dev_info->id = param->phyid;
	cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
	ret =
	    dn->transmit(dn, pkt);
	अगर (ret < 0) अणु
		पूर्णांक count;

		count = cfctrl_cancel_req(&cfctrl->serv.layer,
						user_layer);
		अगर (count != 1) अणु
			pr_err("Could not remove request (%d)", count);
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cfctrl_linkकरोwn_req(काष्ठा cflayer *layer, u8 channelid,
			काष्ठा cflayer *client)
अणु
	पूर्णांक ret;
	काष्ठा cfpkt *pkt;
	काष्ठा cfctrl *cfctrl = container_obj(layer);
	काष्ठा cflayer *dn = cfctrl->serv.layer.dn;

	अगर (!dn) अणु
		pr_debug("not able to send link-down request\n");
		वापस -ENODEV;
	पूर्ण
	pkt = cfpkt_create(CFPKT_CTRL_PKT_LEN);
	अगर (!pkt)
		वापस -ENOMEM;
	cfpkt_addbdy(pkt, CFCTRL_CMD_LINK_DESTROY);
	cfpkt_addbdy(pkt, channelid);
	init_info(cfpkt_info(pkt), cfctrl);
	cfpkt_set_prio(pkt, TC_PRIO_CONTROL);
	ret =
	    dn->transmit(dn, pkt);
#अगर_अघोषित CAIF_NO_LOOP
	cfctrl->loop_linkused[channelid] = 0;
#पूर्ण_अगर
	वापस ret;
पूर्ण

पूर्णांक cfctrl_cancel_req(काष्ठा cflayer *layr, काष्ठा cflayer *adap_layer)
अणु
	काष्ठा cfctrl_request_info *p, *पंचांगp;
	काष्ठा cfctrl *ctrl = container_obj(layr);
	पूर्णांक found = 0;
	spin_lock_bh(&ctrl->info_list_lock);

	list_क्रम_each_entry_safe(p, पंचांगp, &ctrl->list, list) अणु
		अगर (p->client_layer == adap_layer) अणु
			list_del(&p->list);
			kमुक्त(p);
			found++;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ctrl->info_list_lock);
	वापस found;
पूर्ण

अटल पूर्णांक cfctrl_recv(काष्ठा cflayer *layer, काष्ठा cfpkt *pkt)
अणु
	u8 cmdrsp;
	u8 cmd;
	पूर्णांक ret = -1;
	u8 len;
	u8 param[255];
	u8 linkid = 0;
	काष्ठा cfctrl *cfctrl = container_obj(layer);
	काष्ठा cfctrl_request_info rsp, *req;


	cmdrsp = cfpkt_extr_head_u8(pkt);
	cmd = cmdrsp & CFCTRL_CMD_MASK;
	अगर (cmd != CFCTRL_CMD_LINK_ERR
	    && CFCTRL_RSP_BIT != (CFCTRL_RSP_BIT & cmdrsp)
		&& CFCTRL_ERR_BIT != (CFCTRL_ERR_BIT & cmdrsp)) अणु
		अगर (handle_loop(cfctrl, cmd, pkt) != 0)
			cmdrsp |= CFCTRL_ERR_BIT;
	पूर्ण

	चयन (cmd) अणु
	हाल CFCTRL_CMD_LINK_SETUP:
		अणु
			क्रमागत cfctrl_srv serv;
			क्रमागत cfctrl_srv servtype;
			u8 endpoपूर्णांक;
			u8 physlinkid;
			u8 prio;
			u8 पंचांगp;
			u8 *cp;
			पूर्णांक i;
			काष्ठा cfctrl_link_param linkparam;
			स_रखो(&linkparam, 0, माप(linkparam));

			पंचांगp = cfpkt_extr_head_u8(pkt);

			serv = पंचांगp & CFCTRL_SRV_MASK;
			linkparam.linktype = serv;

			servtype = पंचांगp >> 4;
			linkparam.chtype = servtype;

			पंचांगp = cfpkt_extr_head_u8(pkt);
			physlinkid = पंचांगp & 0x07;
			prio = पंचांगp >> 3;

			linkparam.priority = prio;
			linkparam.phyid = physlinkid;
			endpoपूर्णांक = cfpkt_extr_head_u8(pkt);
			linkparam.endpoपूर्णांक = endpoपूर्णांक & 0x03;

			चयन (serv) अणु
			हाल CFCTRL_SRV_VEI:
			हाल CFCTRL_SRV_DBG:
				अगर (CFCTRL_ERR_BIT & cmdrsp)
					अवरोध;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				अवरोध;
			हाल CFCTRL_SRV_VIDEO:
				पंचांगp = cfpkt_extr_head_u8(pkt);
				linkparam.u.video.connid = पंचांगp;
				अगर (CFCTRL_ERR_BIT & cmdrsp)
					अवरोध;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				अवरोध;

			हाल CFCTRL_SRV_DATAGRAM:
				linkparam.u.datagram.connid =
				    cfpkt_extr_head_u32(pkt);
				अगर (CFCTRL_ERR_BIT & cmdrsp)
					अवरोध;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				अवरोध;
			हाल CFCTRL_SRV_RFM:
				/* Conकाष्ठा a frame, convert
				 * DatagramConnectionID
				 * to network क्रमmat दीर्घ and copy it out...
				 */
				linkparam.u.rfm.connid =
				    cfpkt_extr_head_u32(pkt);
				cp = (u8 *) linkparam.u.rfm.volume;
				क्रम (पंचांगp = cfpkt_extr_head_u8(pkt);
				     cfpkt_more(pkt) && पंचांगp != '\0';
				     पंचांगp = cfpkt_extr_head_u8(pkt))
					*cp++ = पंचांगp;
				*cp = '\0';

				अगर (CFCTRL_ERR_BIT & cmdrsp)
					अवरोध;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);

				अवरोध;
			हाल CFCTRL_SRV_UTIL:
				/* Conकाष्ठा a frame, convert
				 * DatagramConnectionID
				 * to network क्रमmat दीर्घ and copy it out...
				 */
				/* Fअगरosize KB */
				linkparam.u.utility.fअगरosize_kb =
				    cfpkt_extr_head_u16(pkt);
				/* Fअगरosize bufs */
				linkparam.u.utility.fअगरosize_bufs =
				    cfpkt_extr_head_u16(pkt);
				/* name */
				cp = (u8 *) linkparam.u.utility.name;
				caअगर_निश्चित(माप(linkparam.u.utility.name)
					     >= UTILITY_NAME_LENGTH);
				क्रम (i = 0;
				     i < UTILITY_NAME_LENGTH
				     && cfpkt_more(pkt); i++) अणु
					पंचांगp = cfpkt_extr_head_u8(pkt);
					*cp++ = पंचांगp;
				पूर्ण
				/* Length */
				len = cfpkt_extr_head_u8(pkt);
				linkparam.u.utility.paramlen = len;
				/* Param Data */
				cp = linkparam.u.utility.params;
				जबतक (cfpkt_more(pkt) && len--) अणु
					पंचांगp = cfpkt_extr_head_u8(pkt);
					*cp++ = पंचांगp;
				पूर्ण
				अगर (CFCTRL_ERR_BIT & cmdrsp)
					अवरोध;
				/* Link ID */
				linkid = cfpkt_extr_head_u8(pkt);
				/* Length */
				len = cfpkt_extr_head_u8(pkt);
				/* Param Data */
				cfpkt_extr_head(pkt, &param, len);
				अवरोध;
			शेष:
				pr_warn("Request setup, invalid type (%d)\n",
					serv);
				जाओ error;
			पूर्ण

			rsp.cmd = cmd;
			rsp.param = linkparam;
			spin_lock_bh(&cfctrl->info_list_lock);
			req = cfctrl_हटाओ_req(cfctrl, &rsp);

			अगर (CFCTRL_ERR_BIT == (CFCTRL_ERR_BIT & cmdrsp) ||
				cfpkt_erroneous(pkt)) अणु
				pr_err("Invalid O/E bit or parse error "
						"on CAIF control channel\n");
				cfctrl->res.reject_rsp(cfctrl->serv.layer.up,
						       0,
						       req ? req->client_layer
						       : शून्य);
			पूर्ण अन्यथा अणु
				cfctrl->res.linksetup_rsp(cfctrl->serv.
							  layer.up, linkid,
							  serv, physlinkid,
							  req ? req->
							  client_layer : शून्य);
			पूर्ण

			kमुक्त(req);

			spin_unlock_bh(&cfctrl->info_list_lock);
		पूर्ण
		अवरोध;
	हाल CFCTRL_CMD_LINK_DESTROY:
		linkid = cfpkt_extr_head_u8(pkt);
		cfctrl->res.linkdestroy_rsp(cfctrl->serv.layer.up, linkid);
		अवरोध;
	हाल CFCTRL_CMD_LINK_ERR:
		pr_err("Frame Error Indication received\n");
		cfctrl->res.linkerror_ind();
		अवरोध;
	हाल CFCTRL_CMD_ENUM:
		cfctrl->res.क्रमागत_rsp();
		अवरोध;
	हाल CFCTRL_CMD_SLEEP:
		cfctrl->res.sleep_rsp();
		अवरोध;
	हाल CFCTRL_CMD_WAKE:
		cfctrl->res.wake_rsp();
		अवरोध;
	हाल CFCTRL_CMD_LINK_RECONF:
		cfctrl->res.restart_rsp();
		अवरोध;
	हाल CFCTRL_CMD_RADIO_SET:
		cfctrl->res.radioset_rsp();
		अवरोध;
	शेष:
		pr_err("Unrecognized Control Frame\n");
		जाओ error;
	पूर्ण
	ret = 0;
error:
	cfpkt_destroy(pkt);
	वापस ret;
पूर्ण

अटल व्योम cfctrl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid)
अणु
	काष्ठा cfctrl *this = container_obj(layr);
	चयन (ctrl) अणु
	हाल _CAIF_CTRLCMD_PHYIF_FLOW_OFF_IND:
	हाल CAIF_CTRLCMD_FLOW_OFF_IND:
		spin_lock_bh(&this->info_list_lock);
		अगर (!list_empty(&this->list))
			pr_debug("Received flow off in control layer\n");
		spin_unlock_bh(&this->info_list_lock);
		अवरोध;
	हाल _CAIF_CTRLCMD_PHYIF_DOWN_IND: अणु
		काष्ठा cfctrl_request_info *p, *पंचांगp;

		/* Find all connect request and report failure */
		spin_lock_bh(&this->info_list_lock);
		list_क्रम_each_entry_safe(p, पंचांगp, &this->list, list) अणु
			अगर (p->param.phyid == phyid) अणु
				list_del(&p->list);
				p->client_layer->ctrlcmd(p->client_layer,
						CAIF_CTRLCMD_INIT_FAIL_RSP,
						phyid);
				kमुक्त(p);
			पूर्ण
		पूर्ण
		spin_unlock_bh(&this->info_list_lock);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#अगर_अघोषित CAIF_NO_LOOP
अटल पूर्णांक handle_loop(काष्ठा cfctrl *ctrl, पूर्णांक cmd, काष्ठा cfpkt *pkt)
अणु
	अटल पूर्णांक last_linkid;
	अटल पूर्णांक dec;
	u8 linkid, linktype, पंचांगp;
	चयन (cmd) अणु
	हाल CFCTRL_CMD_LINK_SETUP:
		spin_lock_bh(&ctrl->loop_linkid_lock);
		अगर (!dec) अणु
			क्रम (linkid = last_linkid + 1; linkid < 254; linkid++)
				अगर (!ctrl->loop_linkused[linkid])
					जाओ found;
		पूर्ण
		dec = 1;
		क्रम (linkid = last_linkid - 1; linkid > 1; linkid--)
			अगर (!ctrl->loop_linkused[linkid])
				जाओ found;
		spin_unlock_bh(&ctrl->loop_linkid_lock);
		वापस -1;
found:
		अगर (linkid < 10)
			dec = 0;

		अगर (!ctrl->loop_linkused[linkid])
			ctrl->loop_linkused[linkid] = 1;

		last_linkid = linkid;

		cfpkt_add_trail(pkt, &linkid, 1);
		spin_unlock_bh(&ctrl->loop_linkid_lock);
		cfpkt_peek_head(pkt, &linktype, 1);
		अगर (linktype ==  CFCTRL_SRV_UTIL) अणु
			पंचांगp = 0x01;
			cfpkt_add_trail(pkt, &पंचांगp, 1);
			cfpkt_add_trail(pkt, &पंचांगp, 1);
		पूर्ण
		अवरोध;

	हाल CFCTRL_CMD_LINK_DESTROY:
		spin_lock_bh(&ctrl->loop_linkid_lock);
		cfpkt_peek_head(pkt, &linkid, 1);
		ctrl->loop_linkused[linkid] = 0;
		spin_unlock_bh(&ctrl->loop_linkid_lock);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर
