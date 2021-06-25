<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/netdevice.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/etherdevice.h>

#समावेश "ionic.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_rx_filter.h"

व्योम ionic_rx_filter_मुक्त(काष्ठा ionic_lअगर *lअगर, काष्ठा ionic_rx_filter *f)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;

	hlist_del(&f->by_id);
	hlist_del(&f->by_hash);
	devm_kमुक्त(dev, f);
पूर्ण

व्योम ionic_rx_filter_replay(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_rx_filter_add_cmd *ac;
	काष्ठा hlist_head new_id_list;
	काष्ठा ionic_admin_ctx ctx;
	काष्ठा ionic_rx_filter *f;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित पूर्णांक key;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	INIT_HLIST_HEAD(&new_id_list);
	ac = &ctx.cmd.rx_filter_add;

	क्रम (i = 0; i < IONIC_RX_FILTER_HLISTS; i++) अणु
		head = &lअगर->rx_filters.by_id[i];
		hlist_क्रम_each_entry_safe(f, पंचांगp, head, by_id) अणु
			ctx.work = COMPLETION_INITIALIZER_ONSTACK(ctx.work);
			स_नकल(ac, &f->cmd, माप(f->cmd));
			dev_dbg(&lअगर->netdev->dev, "replay filter command:\n");
			dynamic_hex_dump("cmd ", DUMP_PREFIX_OFFSET, 16, 1,
					 &ctx.cmd, माप(ctx.cmd), true);

			err = ionic_adminq_post_रुको(lअगर, &ctx);
			अगर (err) अणु
				चयन (le16_to_cpu(ac->match)) अणु
				हाल IONIC_RX_FILTER_MATCH_VLAN:
					netdev_info(lअगर->netdev, "Replay failed - %d: vlan %d\n",
						    err,
						    le16_to_cpu(ac->vlan.vlan));
					अवरोध;
				हाल IONIC_RX_FILTER_MATCH_MAC:
					netdev_info(lअगर->netdev, "Replay failed - %d: mac %pM\n",
						    err, ac->mac.addr);
					अवरोध;
				हाल IONIC_RX_FILTER_MATCH_MAC_VLAN:
					netdev_info(lअगर->netdev, "Replay failed - %d: vlan %d mac %pM\n",
						    err,
						    le16_to_cpu(ac->vlan.vlan),
						    ac->mac.addr);
					अवरोध;
				पूर्ण
				spin_lock_bh(&lअगर->rx_filters.lock);
				ionic_rx_filter_मुक्त(lअगर, f);
				spin_unlock_bh(&lअगर->rx_filters.lock);

				जारी;
			पूर्ण

			/* हटाओ from old id list, save new id in पंचांगp list */
			spin_lock_bh(&lअगर->rx_filters.lock);
			hlist_del(&f->by_id);
			spin_unlock_bh(&lअगर->rx_filters.lock);
			f->filter_id = le32_to_cpu(ctx.comp.rx_filter_add.filter_id);
			hlist_add_head(&f->by_id, &new_id_list);
		पूर्ण
	पूर्ण

	/* rebuild the by_id hash lists with the new filter ids */
	spin_lock_bh(&lअगर->rx_filters.lock);
	hlist_क्रम_each_entry_safe(f, पंचांगp, &new_id_list, by_id) अणु
		key = f->filter_id & IONIC_RX_FILTER_HLISTS_MASK;
		head = &lअगर->rx_filters.by_id[key];
		hlist_add_head(&f->by_id, head);
	पूर्ण
	spin_unlock_bh(&lअगर->rx_filters.lock);
पूर्ण

पूर्णांक ionic_rx_filters_init(काष्ठा ionic_lअगर *lअगर)
अणु
	अचिन्हित पूर्णांक i;

	spin_lock_init(&lअगर->rx_filters.lock);

	spin_lock_bh(&lअगर->rx_filters.lock);
	क्रम (i = 0; i < IONIC_RX_FILTER_HLISTS; i++) अणु
		INIT_HLIST_HEAD(&lअगर->rx_filters.by_hash[i]);
		INIT_HLIST_HEAD(&lअगर->rx_filters.by_id[i]);
	पूर्ण
	spin_unlock_bh(&lअगर->rx_filters.lock);

	वापस 0;
पूर्ण

व्योम ionic_rx_filters_deinit(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_rx_filter *f;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित पूर्णांक i;

	spin_lock_bh(&lअगर->rx_filters.lock);
	क्रम (i = 0; i < IONIC_RX_FILTER_HLISTS; i++) अणु
		head = &lअगर->rx_filters.by_id[i];
		hlist_क्रम_each_entry_safe(f, पंचांगp, head, by_id)
			ionic_rx_filter_मुक्त(lअगर, f);
	पूर्ण
	spin_unlock_bh(&lअगर->rx_filters.lock);
पूर्ण

पूर्णांक ionic_rx_filter_save(काष्ठा ionic_lअगर *lअगर, u32 flow_id, u16 rxq_index,
			 u32 hash, काष्ठा ionic_admin_ctx *ctx)
अणु
	काष्ठा device *dev = lअगर->ionic->dev;
	काष्ठा ionic_rx_filter_add_cmd *ac;
	काष्ठा ionic_rx_filter *f;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक key;

	ac = &ctx->cmd.rx_filter_add;

	चयन (le16_to_cpu(ac->match)) अणु
	हाल IONIC_RX_FILTER_MATCH_VLAN:
		key = le16_to_cpu(ac->vlan.vlan);
		अवरोध;
	हाल IONIC_RX_FILTER_MATCH_MAC:
		key = *(u32 *)ac->mac.addr;
		अवरोध;
	हाल IONIC_RX_FILTER_MATCH_MAC_VLAN:
		key = le16_to_cpu(ac->mac_vlan.vlan);
		अवरोध;
	हाल IONIC_RX_FILTER_STEER_PKTCLASS:
		key = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	f = devm_kzalloc(dev, माप(*f), GFP_KERNEL);
	अगर (!f)
		वापस -ENOMEM;

	f->flow_id = flow_id;
	f->filter_id = le32_to_cpu(ctx->comp.rx_filter_add.filter_id);
	f->rxq_index = rxq_index;
	स_नकल(&f->cmd, ac, माप(f->cmd));
	netdev_dbg(lअगर->netdev, "rx_filter add filter_id %d\n", f->filter_id);

	INIT_HLIST_NODE(&f->by_hash);
	INIT_HLIST_NODE(&f->by_id);

	spin_lock_bh(&lअगर->rx_filters.lock);

	key = hash_32(key, IONIC_RX_FILTER_HASH_BITS);
	head = &lअगर->rx_filters.by_hash[key];
	hlist_add_head(&f->by_hash, head);

	key = f->filter_id & IONIC_RX_FILTER_HLISTS_MASK;
	head = &lअगर->rx_filters.by_id[key];
	hlist_add_head(&f->by_id, head);

	spin_unlock_bh(&lअगर->rx_filters.lock);

	वापस 0;
पूर्ण

काष्ठा ionic_rx_filter *ionic_rx_filter_by_vlan(काष्ठा ionic_lअगर *lअगर, u16 vid)
अणु
	काष्ठा ionic_rx_filter *f;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक key;

	key = hash_32(vid, IONIC_RX_FILTER_HASH_BITS);
	head = &lअगर->rx_filters.by_hash[key];

	hlist_क्रम_each_entry(f, head, by_hash) अणु
		अगर (le16_to_cpu(f->cmd.match) != IONIC_RX_FILTER_MATCH_VLAN)
			जारी;
		अगर (le16_to_cpu(f->cmd.vlan.vlan) == vid)
			वापस f;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ionic_rx_filter *ionic_rx_filter_by_addr(काष्ठा ionic_lअगर *lअगर,
						स्थिर u8 *addr)
अणु
	काष्ठा ionic_rx_filter *f;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक key;

	key = hash_32(*(u32 *)addr, IONIC_RX_FILTER_HASH_BITS);
	head = &lअगर->rx_filters.by_hash[key];

	hlist_क्रम_each_entry(f, head, by_hash) अणु
		अगर (le16_to_cpu(f->cmd.match) != IONIC_RX_FILTER_MATCH_MAC)
			जारी;
		अगर (स_भेद(addr, f->cmd.mac.addr, ETH_ALEN) == 0)
			वापस f;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ionic_rx_filter *ionic_rx_filter_rxsteer(काष्ठा ionic_lअगर *lअगर)
अणु
	काष्ठा ionic_rx_filter *f;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक key;

	key = hash_32(0, IONIC_RX_FILTER_HASH_BITS);
	head = &lअगर->rx_filters.by_hash[key];

	hlist_क्रम_each_entry(f, head, by_hash) अणु
		अगर (le16_to_cpu(f->cmd.match) != IONIC_RX_FILTER_STEER_PKTCLASS)
			जारी;
		वापस f;
	पूर्ण

	वापस शून्य;
पूर्ण
