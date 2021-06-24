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
#समावेश <linux/rculist.h>
#समावेश <net/caअगर/cfpkt.h>
#समावेश <net/caअगर/cfmuxl.h>
#समावेश <net/caअगर/cfsrvl.h>
#समावेश <net/caअगर/cffrml.h>

#घोषणा container_obj(layr) container_of(layr, काष्ठा cfmuxl, layer)

#घोषणा CAIF_CTRL_CHANNEL 0
#घोषणा UP_CACHE_SIZE 8
#घोषणा DN_CACHE_SIZE 8

काष्ठा cfmuxl अणु
	काष्ठा cflayer layer;
	काष्ठा list_head srvl_list;
	काष्ठा list_head frml_list;
	काष्ठा cflayer *up_cache[UP_CACHE_SIZE];
	काष्ठा cflayer *dn_cache[DN_CACHE_SIZE];
	/*
	 * Set when inserting or removing करोwnwards layers.
	 */
	spinlock_t transmit_lock;

	/*
	 * Set when inserting or removing upwards layers.
	 */
	spinlock_t receive_lock;

पूर्ण;

अटल पूर्णांक cfmuxl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल पूर्णांक cfmuxl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt);
अटल व्योम cfmuxl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid);
अटल काष्ठा cflayer *get_up(काष्ठा cfmuxl *muxl, u16 id);

काष्ठा cflayer *cfmuxl_create(व्योम)
अणु
	काष्ठा cfmuxl *this = kzalloc(माप(काष्ठा cfmuxl), GFP_ATOMIC);

	अगर (!this)
		वापस शून्य;
	this->layer.receive = cfmuxl_receive;
	this->layer.transmit = cfmuxl_transmit;
	this->layer.ctrlcmd = cfmuxl_ctrlcmd;
	INIT_LIST_HEAD(&this->srvl_list);
	INIT_LIST_HEAD(&this->frml_list);
	spin_lock_init(&this->transmit_lock);
	spin_lock_init(&this->receive_lock);
	snम_लिखो(this->layer.name, CAIF_LAYER_NAME_SZ, "mux");
	वापस &this->layer;
पूर्ण

पूर्णांक cfmuxl_set_dnlayer(काष्ठा cflayer *layr, काष्ठा cflayer *dn, u8 phyid)
अणु
	काष्ठा cfmuxl *muxl = (काष्ठा cfmuxl *) layr;

	spin_lock_bh(&muxl->transmit_lock);
	list_add_rcu(&dn->node, &muxl->frml_list);
	spin_unlock_bh(&muxl->transmit_lock);
	वापस 0;
पूर्ण

अटल काष्ठा cflayer *get_from_id(काष्ठा list_head *list, u16 id)
अणु
	काष्ठा cflayer *lyr;
	list_क्रम_each_entry_rcu(lyr, list, node) अणु
		अगर (lyr->id == id)
			वापस lyr;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक cfmuxl_set_uplayer(काष्ठा cflayer *layr, काष्ठा cflayer *up, u8 linkid)
अणु
	काष्ठा cfmuxl *muxl = container_obj(layr);
	काष्ठा cflayer *old;

	spin_lock_bh(&muxl->receive_lock);

	/* Two entries with same id is wrong, so हटाओ old layer from mux */
	old = get_from_id(&muxl->srvl_list, linkid);
	अगर (old != शून्य)
		list_del_rcu(&old->node);

	list_add_rcu(&up->node, &muxl->srvl_list);
	spin_unlock_bh(&muxl->receive_lock);

	वापस 0;
पूर्ण

काष्ठा cflayer *cfmuxl_हटाओ_dnlayer(काष्ठा cflayer *layr, u8 phyid)
अणु
	काष्ठा cfmuxl *muxl = container_obj(layr);
	काष्ठा cflayer *dn;
	पूर्णांक idx = phyid % DN_CACHE_SIZE;

	spin_lock_bh(&muxl->transmit_lock);
	RCU_INIT_POINTER(muxl->dn_cache[idx], शून्य);
	dn = get_from_id(&muxl->frml_list, phyid);
	अगर (dn == शून्य)
		जाओ out;

	list_del_rcu(&dn->node);
	caअगर_निश्चित(dn != शून्य);
out:
	spin_unlock_bh(&muxl->transmit_lock);
	वापस dn;
पूर्ण

अटल काष्ठा cflayer *get_up(काष्ठा cfmuxl *muxl, u16 id)
अणु
	काष्ठा cflayer *up;
	पूर्णांक idx = id % UP_CACHE_SIZE;
	up = rcu_dereference(muxl->up_cache[idx]);
	अगर (up == शून्य || up->id != id) अणु
		spin_lock_bh(&muxl->receive_lock);
		up = get_from_id(&muxl->srvl_list, id);
		rcu_assign_poपूर्णांकer(muxl->up_cache[idx], up);
		spin_unlock_bh(&muxl->receive_lock);
	पूर्ण
	वापस up;
पूर्ण

अटल काष्ठा cflayer *get_dn(काष्ठा cfmuxl *muxl, काष्ठा dev_info *dev_info)
अणु
	काष्ठा cflayer *dn;
	पूर्णांक idx = dev_info->id % DN_CACHE_SIZE;
	dn = rcu_dereference(muxl->dn_cache[idx]);
	अगर (dn == शून्य || dn->id != dev_info->id) अणु
		spin_lock_bh(&muxl->transmit_lock);
		dn = get_from_id(&muxl->frml_list, dev_info->id);
		rcu_assign_poपूर्णांकer(muxl->dn_cache[idx], dn);
		spin_unlock_bh(&muxl->transmit_lock);
	पूर्ण
	वापस dn;
पूर्ण

काष्ठा cflayer *cfmuxl_हटाओ_uplayer(काष्ठा cflayer *layr, u8 id)
अणु
	काष्ठा cflayer *up;
	काष्ठा cfmuxl *muxl = container_obj(layr);
	पूर्णांक idx = id % UP_CACHE_SIZE;

	अगर (id == 0) अणु
		pr_warn("Trying to remove control layer\n");
		वापस शून्य;
	पूर्ण

	spin_lock_bh(&muxl->receive_lock);
	up = get_from_id(&muxl->srvl_list, id);
	अगर (up == शून्य)
		जाओ out;

	RCU_INIT_POINTER(muxl->up_cache[idx], शून्य);
	list_del_rcu(&up->node);
out:
	spin_unlock_bh(&muxl->receive_lock);
	वापस up;
पूर्ण

अटल पूर्णांक cfmuxl_receive(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	पूर्णांक ret;
	काष्ठा cfmuxl *muxl = container_obj(layr);
	u8 id;
	काष्ठा cflayer *up;
	अगर (cfpkt_extr_head(pkt, &id, 1) < 0) अणु
		pr_err("erroneous Caif Packet\n");
		cfpkt_destroy(pkt);
		वापस -EPROTO;
	पूर्ण
	rcu_पढ़ो_lock();
	up = get_up(muxl, id);

	अगर (up == शून्य) अणु
		pr_debug("Received data on unknown link ID = %d (0x%x)"
			" up == NULL", id, id);
		cfpkt_destroy(pkt);
		/*
		 * Don't वापस ERROR, since modem misbehaves and sends out
		 * flow on beक्रमe linksetup response.
		 */

		rcu_पढ़ो_unlock();
		वापस /* CFGLU_EPROT; */ 0;
	पूर्ण

	/* We can't hold rcu_lock during receive, so take a ref count instead */
	cfsrvl_get(up);
	rcu_पढ़ो_unlock();

	ret = up->receive(up, pkt);

	cfsrvl_put(up);
	वापस ret;
पूर्ण

अटल पूर्णांक cfmuxl_transmit(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	काष्ठा cfmuxl *muxl = container_obj(layr);
	पूर्णांक err;
	u8 linkid;
	काष्ठा cflayer *dn;
	काष्ठा caअगर_payload_info *info = cfpkt_info(pkt);
	BUG_ON(!info);

	rcu_पढ़ो_lock();

	dn = get_dn(muxl, info->dev_info);
	अगर (dn == शून्य) अणु
		pr_debug("Send data on unknown phy ID = %d (0x%x)\n",
			info->dev_info->id, info->dev_info->id);
		rcu_पढ़ो_unlock();
		cfpkt_destroy(pkt);
		वापस -ENOTCONN;
	पूर्ण

	info->hdr_len += 1;
	linkid = info->channel_id;
	cfpkt_add_head(pkt, &linkid, 1);

	/* We can't hold rcu_lock during receive, so take a ref count instead */
	cffrml_hold(dn);

	rcu_पढ़ो_unlock();

	err = dn->transmit(dn, pkt);

	cffrml_put(dn);
	वापस err;
पूर्ण

अटल व्योम cfmuxl_ctrlcmd(काष्ठा cflayer *layr, क्रमागत caअगर_ctrlcmd ctrl,
			   पूर्णांक phyid)
अणु
	काष्ठा cfmuxl *muxl = container_obj(layr);
	काष्ठा cflayer *layer;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(layer, &muxl->srvl_list, node) अणु

		अगर (cfsrvl_phyid_match(layer, phyid) && layer->ctrlcmd) अणु

			अगर ((ctrl == _CAIF_CTRLCMD_PHYIF_DOWN_IND ||
				ctrl == CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND) &&
					layer->id != 0)
				cfmuxl_हटाओ_uplayer(layr, layer->id);

			/* NOTE: ctrlcmd is not allowed to block */
			layer->ctrlcmd(layer, ctrl, phyid);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
