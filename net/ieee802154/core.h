<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IEEE802154_CORE_H
#घोषणा __IEEE802154_CORE_H

#समावेश <net/cfg802154.h>

काष्ठा cfg802154_रेजिस्टरed_device अणु
	स्थिर काष्ठा cfg802154_ops *ops;
	काष्ठा list_head list;

	/* wpan_phy index, पूर्णांकernal only */
	पूर्णांक wpan_phy_idx;

	/* also रक्षित by devlist_mtx */
	पूर्णांक खोलोcount;
	रुको_queue_head_t dev_रुको;

	/* रक्षित by RTNL only */
	पूर्णांक num_running_अगरaces;

	/* associated wpan पूर्णांकerfaces, रक्षित by rtnl or RCU */
	काष्ठा list_head wpan_dev_list;
	पूर्णांक devlist_generation, wpan_dev_id;

	/* must be last because of the way we करो wpan_phy_priv(),
	 * and it should at least be aligned to NETDEV_ALIGN
	 */
	काष्ठा wpan_phy wpan_phy __aligned(NETDEV_ALIGN);
पूर्ण;

अटल अंतरभूत काष्ठा cfg802154_रेजिस्टरed_device *
wpan_phy_to_rdev(काष्ठा wpan_phy *wpan_phy)
अणु
	BUG_ON(!wpan_phy);
	वापस container_of(wpan_phy, काष्ठा cfg802154_रेजिस्टरed_device,
			    wpan_phy);
पूर्ण

बाह्य काष्ठा list_head cfg802154_rdev_list;
बाह्य पूर्णांक cfg802154_rdev_list_generation;

पूर्णांक cfg802154_चयन_netns(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			   काष्ठा net *net);
/* मुक्त object */
व्योम cfg802154_dev_मुक्त(काष्ठा cfg802154_रेजिस्टरed_device *rdev);
काष्ठा cfg802154_रेजिस्टरed_device *
cfg802154_rdev_by_wpan_phy_idx(पूर्णांक wpan_phy_idx);
काष्ठा wpan_phy *wpan_phy_idx_to_wpan_phy(पूर्णांक wpan_phy_idx);

#पूर्ण_अगर /* __IEEE802154_CORE_H */
