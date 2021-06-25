<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Loopback IEEE 802.15.4 पूर्णांकerface
 *
 * Copyright 2007-2012 Siemens AG
 *
 * Written by:
 * Sergey Lapin <slapin@ossfans.org>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <net/mac802154.h>
#समावेश <net/cfg802154.h>

अटल पूर्णांक numlbs = 2;

अटल LIST_HEAD(fakelb_phys);
अटल DEFINE_MUTEX(fakelb_phys_lock);

अटल LIST_HEAD(fakelb_अगरup_phys);
अटल DEFINE_RWLOCK(fakelb_अगरup_phys_lock);

काष्ठा fakelb_phy अणु
	काष्ठा ieee802154_hw *hw;

	u8 page;
	u8 channel;

	bool suspended;

	काष्ठा list_head list;
	काष्ठा list_head list_अगरup;
पूर्ण;

अटल पूर्णांक fakelb_hw_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	WARN_ON(!level);
	*level = 0xbe;

	वापस 0;
पूर्ण

अटल पूर्णांक fakelb_hw_channel(काष्ठा ieee802154_hw *hw, u8 page, u8 channel)
अणु
	काष्ठा fakelb_phy *phy = hw->priv;

	ग_लिखो_lock_bh(&fakelb_अगरup_phys_lock);
	phy->page = page;
	phy->channel = channel;
	ग_लिखो_unlock_bh(&fakelb_अगरup_phys_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक fakelb_hw_xmit(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा fakelb_phy *current_phy = hw->priv, *phy;

	पढ़ो_lock_bh(&fakelb_अगरup_phys_lock);
	WARN_ON(current_phy->suspended);
	list_क्रम_each_entry(phy, &fakelb_अगरup_phys, list_अगरup) अणु
		अगर (current_phy == phy)
			जारी;

		अगर (current_phy->page == phy->page &&
		    current_phy->channel == phy->channel) अणु
			काष्ठा sk_buff *newskb = pskb_copy(skb, GFP_ATOMIC);

			अगर (newskb)
				ieee802154_rx_irqsafe(phy->hw, newskb, 0xcc);
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&fakelb_अगरup_phys_lock);

	ieee802154_xmit_complete(hw, skb, false);
	वापस 0;
पूर्ण

अटल पूर्णांक fakelb_hw_start(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा fakelb_phy *phy = hw->priv;

	ग_लिखो_lock_bh(&fakelb_अगरup_phys_lock);
	phy->suspended = false;
	list_add(&phy->list_अगरup, &fakelb_अगरup_phys);
	ग_लिखो_unlock_bh(&fakelb_अगरup_phys_lock);

	वापस 0;
पूर्ण

अटल व्योम fakelb_hw_stop(काष्ठा ieee802154_hw *hw)
अणु
	काष्ठा fakelb_phy *phy = hw->priv;

	ग_लिखो_lock_bh(&fakelb_अगरup_phys_lock);
	phy->suspended = true;
	list_del(&phy->list_अगरup);
	ग_लिखो_unlock_bh(&fakelb_अगरup_phys_lock);
पूर्ण

अटल पूर्णांक
fakelb_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, स्थिर bool on)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops fakelb_ops = अणु
	.owner = THIS_MODULE,
	.xmit_async = fakelb_hw_xmit,
	.ed = fakelb_hw_ed,
	.set_channel = fakelb_hw_channel,
	.start = fakelb_hw_start,
	.stop = fakelb_hw_stop,
	.set_promiscuous_mode = fakelb_set_promiscuous_mode,
पूर्ण;

/* Number of dummy devices to be set up by this module. */
module_param(numlbs, पूर्णांक, 0);
MODULE_PARM_DESC(numlbs, " number of pseudo devices");

अटल पूर्णांक fakelb_add_one(काष्ठा device *dev)
अणु
	काष्ठा ieee802154_hw *hw;
	काष्ठा fakelb_phy *phy;
	पूर्णांक err;

	hw = ieee802154_alloc_hw(माप(*phy), &fakelb_ops);
	अगर (!hw)
		वापस -ENOMEM;

	phy = hw->priv;
	phy->hw = hw;

	/* 868 MHz BPSK	802.15.4-2003 */
	hw->phy->supported.channels[0] |= 1;
	/* 915 MHz BPSK	802.15.4-2003 */
	hw->phy->supported.channels[0] |= 0x7fe;
	/* 2.4 GHz O-QPSK 802.15.4-2003 */
	hw->phy->supported.channels[0] |= 0x7FFF800;
	/* 868 MHz ASK 802.15.4-2006 */
	hw->phy->supported.channels[1] |= 1;
	/* 915 MHz ASK 802.15.4-2006 */
	hw->phy->supported.channels[1] |= 0x7fe;
	/* 868 MHz O-QPSK 802.15.4-2006 */
	hw->phy->supported.channels[2] |= 1;
	/* 915 MHz O-QPSK 802.15.4-2006 */
	hw->phy->supported.channels[2] |= 0x7fe;
	/* 2.4 GHz CSS 802.15.4a-2007 */
	hw->phy->supported.channels[3] |= 0x3fff;
	/* UWB Sub-gigahertz 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 1;
	/* UWB Low band 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 0x1e;
	/* UWB High band 802.15.4a-2007 */
	hw->phy->supported.channels[4] |= 0xffe0;
	/* 750 MHz O-QPSK 802.15.4c-2009 */
	hw->phy->supported.channels[5] |= 0xf;
	/* 750 MHz MPSK 802.15.4c-2009 */
	hw->phy->supported.channels[5] |= 0xf0;
	/* 950 MHz BPSK 802.15.4d-2009 */
	hw->phy->supported.channels[6] |= 0x3ff;
	/* 950 MHz GFSK 802.15.4d-2009 */
	hw->phy->supported.channels[6] |= 0x3ffc00;

	ieee802154_अक्रमom_extended_addr(&hw->phy->perm_extended_addr);
	/* fake phy channel 13 as शेष */
	hw->phy->current_channel = 13;
	phy->channel = hw->phy->current_channel;

	hw->flags = IEEE802154_HW_PROMISCUOUS;
	hw->parent = dev;

	err = ieee802154_रेजिस्टर_hw(hw);
	अगर (err)
		जाओ err_reg;

	mutex_lock(&fakelb_phys_lock);
	list_add_tail(&phy->list, &fakelb_phys);
	mutex_unlock(&fakelb_phys_lock);

	वापस 0;

err_reg:
	ieee802154_मुक्त_hw(phy->hw);
	वापस err;
पूर्ण

अटल व्योम fakelb_del(काष्ठा fakelb_phy *phy)
अणु
	list_del(&phy->list);

	ieee802154_unरेजिस्टर_hw(phy->hw);
	ieee802154_मुक्त_hw(phy->hw);
पूर्ण

अटल पूर्णांक fakelb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fakelb_phy *phy, *पंचांगp;
	पूर्णांक err, i;

	क्रम (i = 0; i < numlbs; i++) अणु
		err = fakelb_add_one(&pdev->dev);
		अगर (err < 0)
			जाओ err_slave;
	पूर्ण

	dev_info(&pdev->dev, "added %i fake ieee802154 hardware devices\n", numlbs);
	वापस 0;

err_slave:
	mutex_lock(&fakelb_phys_lock);
	list_क्रम_each_entry_safe(phy, पंचांगp, &fakelb_phys, list)
		fakelb_del(phy);
	mutex_unlock(&fakelb_phys_lock);
	वापस err;
पूर्ण

अटल पूर्णांक fakelb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fakelb_phy *phy, *पंचांगp;

	mutex_lock(&fakelb_phys_lock);
	list_क्रम_each_entry_safe(phy, पंचांगp, &fakelb_phys, list)
		fakelb_del(phy);
	mutex_unlock(&fakelb_phys_lock);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *ieee802154fake_dev;

अटल काष्ठा platक्रमm_driver ieee802154fake_driver = अणु
	.probe = fakelb_probe,
	.हटाओ = fakelb_हटाओ,
	.driver = अणु
			.name = "ieee802154fakelb",
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक fakelb_init_module(व्योम)
अणु
	ieee802154fake_dev = platक्रमm_device_रेजिस्टर_simple(
			     "ieee802154fakelb", -1, शून्य, 0);

	pr_warn("fakelb driver is marked as deprecated, please use mac802154_hwsim!\n");

	वापस platक्रमm_driver_रेजिस्टर(&ieee802154fake_driver);
पूर्ण

अटल __निकास व्योम fake_हटाओ_module(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ieee802154fake_driver);
	platक्रमm_device_unरेजिस्टर(ieee802154fake_dev);
पूर्ण

module_init(fakelb_init_module);
module_निकास(fake_हटाओ_module);
MODULE_LICENSE("GPL");
