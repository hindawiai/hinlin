<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2012 Siemens AG
 *
 * Written by:
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>

#समावेश <net/netlink.h>
#समावेश <net/nl802154.h>
#समावेश <net/mac802154.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/route.h>
#समावेश <net/cfg802154.h>

#समावेश "ieee802154_i.h"
#समावेश "cfg.h"

अटल व्योम ieee802154_tasklet_handler(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ieee802154_local *local = from_tasklet(local, t, tasklet);
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&local->skb_queue))) अणु
		चयन (skb->pkt_type) अणु
		हाल IEEE802154_RX_MSG:
			/* Clear skb->pkt_type in order to not confuse kernel
			 * netstack.
			 */
			skb->pkt_type = 0;
			ieee802154_rx(local, skb);
			अवरोध;
		शेष:
			WARN(1, "mac802154: Packet is of unknown type %d\n",
			     skb->pkt_type);
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा ieee802154_hw *
ieee802154_alloc_hw(माप_प्रकार priv_data_len, स्थिर काष्ठा ieee802154_ops *ops)
अणु
	काष्ठा wpan_phy *phy;
	काष्ठा ieee802154_local *local;
	माप_प्रकार priv_size;

	अगर (WARN_ON(!ops || !(ops->xmit_async || ops->xmit_sync) || !ops->ed ||
		    !ops->start || !ops->stop || !ops->set_channel))
		वापस शून्य;

	/* Ensure 32-byte alignment of our निजी data and hw निजी data.
	 * We use the wpan_phy priv data क्रम both our ieee802154_local and क्रम
	 * the driver's निजी data
	 *
	 * in memory it'll be like this:
	 *
	 * +-------------------------+
	 * | काष्ठा wpan_phy         |
	 * +-------------------------+
	 * | काष्ठा ieee802154_local |
	 * +-------------------------+
	 * | driver's निजी data   |
	 * +-------------------------+
	 *
	 * Due to ieee802154 layer isn't aware of driver and MAC काष्ठाures,
	 * so lets align them here.
	 */

	priv_size = ALIGN(माप(*local), NETDEV_ALIGN) + priv_data_len;

	phy = wpan_phy_new(&mac802154_config_ops, priv_size);
	अगर (!phy) अणु
		pr_err("failure to allocate master IEEE802.15.4 device\n");
		वापस शून्य;
	पूर्ण

	phy->privid = mac802154_wpan_phy_privid;

	local = wpan_phy_priv(phy);
	local->phy = phy;
	local->hw.phy = local->phy;
	local->hw.priv = (अक्षर *)local + ALIGN(माप(*local), NETDEV_ALIGN);
	local->ops = ops;

	INIT_LIST_HEAD(&local->पूर्णांकerfaces);
	mutex_init(&local->अगरlist_mtx);

	tasklet_setup(&local->tasklet, ieee802154_tasklet_handler);

	skb_queue_head_init(&local->skb_queue);

	INIT_WORK(&local->tx_work, ieee802154_xmit_worker);

	/* init supported flags with 802.15.4 शेष ranges */
	phy->supported.max_minbe = 8;
	phy->supported.min_maxbe = 3;
	phy->supported.max_maxbe = 8;
	phy->supported.min_frame_retries = 0;
	phy->supported.max_frame_retries = 7;
	phy->supported.max_csma_backoffs = 5;
	phy->supported.lbt = NL802154_SUPPORTED_BOOL_FALSE;

	/* always supported */
	phy->supported.अगरtypes = BIT(NL802154_IFTYPE_NODE);

	वापस &local->hw;
पूर्ण
EXPORT_SYMBOL(ieee802154_alloc_hw);

व्योम ieee802154_मुक्त_hw(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा ieee802154_local *local = hw_to_local(hw);

	BUG_ON(!list_empty(&local->पूर्णांकerfaces));

	mutex_destroy(&local->अगरlist_mtx);

	wpan_phy_मुक्त(local->phy);
पूर्ण
EXPORT_SYMBOL(ieee802154_मुक्त_hw);

अटल व्योम ieee802154_setup_wpan_phy_pib(काष्ठा wpan_phy *wpan_phy)
अणु
	/* TODO warn on empty symbol_duration
	 * Should be करोne when all drivers sets this value.
	 */

	wpan_phy->lअगरs_period = IEEE802154_LIFS_PERIOD *
				wpan_phy->symbol_duration;
	wpan_phy->sअगरs_period = IEEE802154_SIFS_PERIOD *
				wpan_phy->symbol_duration;
पूर्ण

पूर्णांक ieee802154_रेजिस्टर_hw(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा ieee802154_local *local = hw_to_local(hw);
	काष्ठा net_device *dev;
	पूर्णांक rc = -ENOSYS;

	local->workqueue =
		create_singlethपढ़ो_workqueue(wpan_phy_name(local->phy));
	अगर (!local->workqueue) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	hrसमयr_init(&local->अगरs_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	local->अगरs_समयr.function = ieee802154_xmit_अगरs_समयr;

	wpan_phy_set_dev(local->phy, local->hw.parent);

	ieee802154_setup_wpan_phy_pib(local->phy);

	अगर (!(hw->flags & IEEE802154_HW_CSMA_PARAMS)) अणु
		local->phy->supported.min_csma_backoffs = 4;
		local->phy->supported.max_csma_backoffs = 4;
		local->phy->supported.min_maxbe = 5;
		local->phy->supported.max_maxbe = 5;
		local->phy->supported.min_minbe = 3;
		local->phy->supported.max_minbe = 3;
	पूर्ण

	अगर (!(hw->flags & IEEE802154_HW_FRAME_RETRIES)) अणु
		local->phy->supported.min_frame_retries = 3;
		local->phy->supported.max_frame_retries = 3;
	पूर्ण

	अगर (hw->flags & IEEE802154_HW_PROMISCUOUS)
		local->phy->supported.अगरtypes |= BIT(NL802154_IFTYPE_MONITOR);

	rc = wpan_phy_रेजिस्टर(local->phy);
	अगर (rc < 0)
		जाओ out_wq;

	rtnl_lock();

	dev = ieee802154_अगर_add(local, "wpan%d", NET_NAME_ENUM,
				NL802154_IFTYPE_NODE,
				cpu_to_le64(0x0000000000000000ULL));
	अगर (IS_ERR(dev)) अणु
		rtnl_unlock();
		rc = PTR_ERR(dev);
		जाओ out_phy;
	पूर्ण

	rtnl_unlock();

	वापस 0;

out_phy:
	wpan_phy_unरेजिस्टर(local->phy);
out_wq:
	destroy_workqueue(local->workqueue);
out:
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ieee802154_रेजिस्टर_hw);

व्योम ieee802154_unरेजिस्टर_hw(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा ieee802154_local *local = hw_to_local(hw);

	tasklet_समाप्त(&local->tasklet);
	flush_workqueue(local->workqueue);

	rtnl_lock();

	ieee802154_हटाओ_पूर्णांकerfaces(local);

	rtnl_unlock();

	destroy_workqueue(local->workqueue);
	wpan_phy_unरेजिस्टर(local->phy);
पूर्ण
EXPORT_SYMBOL(ieee802154_unरेजिस्टर_hw);

अटल पूर्णांक __init ieee802154_init(व्योम)
अणु
	वापस ieee802154_अगरace_init();
पूर्ण

अटल व्योम __निकास ieee802154_निकास(व्योम)
अणु
	ieee802154_अगरace_निकास();

	rcu_barrier();
पूर्ण

subsys_initcall(ieee802154_init);
module_निकास(ieee802154_निकास);

MODULE_DESCRIPTION("IEEE 802.15.4 subsystem");
MODULE_LICENSE("GPL v2");
