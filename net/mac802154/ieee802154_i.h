<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007-2012 Siemens AG
 *
 * Written by:
 * Pavel Smolenskiy <pavel.smolenskiy@gmail.com>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */
#अगर_अघोषित __IEEE802154_I_H
#घोषणा __IEEE802154_I_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hrसमयr.h>
#समावेश <net/cfg802154.h>
#समावेश <net/mac802154.h>
#समावेश <net/nl802154.h>
#समावेश <net/ieee802154_netdev.h>

#समावेश "llsec.h"

/* mac802154 device निजी data */
काष्ठा ieee802154_local अणु
	काष्ठा ieee802154_hw hw;
	स्थिर काष्ठा ieee802154_ops *ops;

	/* ieee802154 phy */
	काष्ठा wpan_phy *phy;

	पूर्णांक खोलो_count;

	/* As in mac80211 slaves list is modअगरied:
	 * 1) under the RTNL
	 * 2) रक्षित by slaves_mtx;
	 * 3) in an RCU manner
	 *
	 * So atomic पढ़ोers can use any of this protection methods.
	 */
	काष्ठा list_head	पूर्णांकerfaces;
	काष्ठा mutex		अगरlist_mtx;

	/* This one is used क्रम scanning and other jobs not to be पूर्णांकerfered
	 * with serial driver.
	 */
	काष्ठा workqueue_काष्ठा	*workqueue;

	काष्ठा hrसमयr अगरs_समयr;

	bool started;
	bool suspended;

	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा sk_buff_head skb_queue;

	काष्ठा sk_buff *tx_skb;
	काष्ठा work_काष्ठा tx_work;
पूर्ण;

क्रमागत अणु
	IEEE802154_RX_MSG        = 1,
पूर्ण;

क्रमागत ieee802154_sdata_state_bits अणु
	SDATA_STATE_RUNNING,
पूर्ण;

/* Slave पूर्णांकerface definition.
 *
 * Slaves represent typical network पूर्णांकerfaces available from userspace.
 * Each ieee802154 device/transceiver may have several slaves and able
 * to be associated with several networks at the same समय.
 */
काष्ठा ieee802154_sub_अगर_data अणु
	काष्ठा list_head list; /* the ieee802154_priv->slaves list */

	काष्ठा wpan_dev wpan_dev;

	काष्ठा ieee802154_local *local;
	काष्ठा net_device *dev;

	अचिन्हित दीर्घ state;
	अक्षर name[IFNAMSIZ];

	/* protects sec from concurrent access by netlink. access by
	 * encrypt/decrypt/header_create safe without additional protection.
	 */
	काष्ठा mutex sec_mtx;

	काष्ठा mac802154_llsec sec;
पूर्ण;

/* utility functions/स्थिरants */
बाह्य स्थिर व्योम *स्थिर mac802154_wpan_phy_privid; /*  क्रम wpan_phy privid */

अटल अंतरभूत काष्ठा ieee802154_local *
hw_to_local(काष्ठा ieee802154_hw *hw)
अणु
	वापस container_of(hw, काष्ठा ieee802154_local, hw);
पूर्ण

अटल अंतरभूत काष्ठा ieee802154_sub_अगर_data *
IEEE802154_DEV_TO_SUB_IF(स्थिर काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

अटल अंतरभूत काष्ठा ieee802154_sub_अगर_data *
IEEE802154_WPAN_DEV_TO_SUB_IF(काष्ठा wpan_dev *wpan_dev)
अणु
	वापस container_of(wpan_dev, काष्ठा ieee802154_sub_अगर_data, wpan_dev);
पूर्ण

अटल अंतरभूत bool
ieee802154_sdata_running(काष्ठा ieee802154_sub_अगर_data *sdata)
अणु
	वापस test_bit(SDATA_STATE_RUNNING, &sdata->state);
पूर्ण

बाह्य काष्ठा ieee802154_mlme_ops mac802154_mlme_wpan;

व्योम ieee802154_rx(काष्ठा ieee802154_local *local, काष्ठा sk_buff *skb);
व्योम ieee802154_xmit_worker(काष्ठा work_काष्ठा *work);
netdev_tx_t
ieee802154_monitor_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
netdev_tx_t
ieee802154_subअगर_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
क्रमागत hrसमयr_restart ieee802154_xmit_अगरs_समयr(काष्ठा hrसमयr *समयr);

/* MIB callbacks */
व्योम mac802154_dev_set_page_channel(काष्ठा net_device *dev, u8 page, u8 chan);

पूर्णांक mac802154_get_params(काष्ठा net_device *dev,
			 काष्ठा ieee802154_llsec_params *params);
पूर्णांक mac802154_set_params(काष्ठा net_device *dev,
			 स्थिर काष्ठा ieee802154_llsec_params *params,
			 पूर्णांक changed);

पूर्णांक mac802154_add_key(काष्ठा net_device *dev,
		      स्थिर काष्ठा ieee802154_llsec_key_id *id,
		      स्थिर काष्ठा ieee802154_llsec_key *key);
पूर्णांक mac802154_del_key(काष्ठा net_device *dev,
		      स्थिर काष्ठा ieee802154_llsec_key_id *id);

पूर्णांक mac802154_add_dev(काष्ठा net_device *dev,
		      स्थिर काष्ठा ieee802154_llsec_device *llsec_dev);
पूर्णांक mac802154_del_dev(काष्ठा net_device *dev, __le64 dev_addr);

पूर्णांक mac802154_add_devkey(काष्ठा net_device *dev,
			 __le64 device_addr,
			 स्थिर काष्ठा ieee802154_llsec_device_key *key);
पूर्णांक mac802154_del_devkey(काष्ठा net_device *dev,
			 __le64 device_addr,
			 स्थिर काष्ठा ieee802154_llsec_device_key *key);

पूर्णांक mac802154_add_seclevel(काष्ठा net_device *dev,
			   स्थिर काष्ठा ieee802154_llsec_seclevel *sl);
पूर्णांक mac802154_del_seclevel(काष्ठा net_device *dev,
			   स्थिर काष्ठा ieee802154_llsec_seclevel *sl);

व्योम mac802154_lock_table(काष्ठा net_device *dev);
व्योम mac802154_get_table(काष्ठा net_device *dev,
			 काष्ठा ieee802154_llsec_table **t);
व्योम mac802154_unlock_table(काष्ठा net_device *dev);

पूर्णांक mac802154_wpan_update_llsec(काष्ठा net_device *dev);

/* पूर्णांकerface handling */
पूर्णांक ieee802154_अगरace_init(व्योम);
व्योम ieee802154_अगरace_निकास(व्योम);
व्योम ieee802154_अगर_हटाओ(काष्ठा ieee802154_sub_अगर_data *sdata);
काष्ठा net_device *
ieee802154_अगर_add(काष्ठा ieee802154_local *local, स्थिर अक्षर *name,
		  अचिन्हित अक्षर name_assign_type, क्रमागत nl802154_अगरtype type,
		  __le64 extended_addr);
व्योम ieee802154_हटाओ_पूर्णांकerfaces(काष्ठा ieee802154_local *local);
व्योम ieee802154_stop_device(काष्ठा ieee802154_local *local);

#पूर्ण_अगर /* __IEEE802154_I_H */
