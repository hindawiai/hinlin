<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007, 2008, 2009 Siemens AG
 *
 * Written by:
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 */

#अगर_अघोषित __NET_CFG802154_H
#घोषणा __NET_CFG802154_H

#समावेश <linux/ieee802154.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/bug.h>

#समावेश <net/nl802154.h>

काष्ठा wpan_phy;
काष्ठा wpan_phy_cca;

#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
काष्ठा ieee802154_llsec_device_key;
काष्ठा ieee802154_llsec_seclevel;
काष्ठा ieee802154_llsec_params;
काष्ठा ieee802154_llsec_device;
काष्ठा ieee802154_llsec_table;
काष्ठा ieee802154_llsec_key_id;
काष्ठा ieee802154_llsec_key;
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

काष्ठा cfg802154_ops अणु
	काष्ठा net_device * (*add_भव_पूर्णांकf_deprecated)(काष्ठा wpan_phy *wpan_phy,
							   स्थिर अक्षर *name,
							   अचिन्हित अक्षर name_assign_type,
							   पूर्णांक type);
	व्योम	(*del_भव_पूर्णांकf_deprecated)(काष्ठा wpan_phy *wpan_phy,
					       काष्ठा net_device *dev);
	पूर्णांक	(*suspend)(काष्ठा wpan_phy *wpan_phy);
	पूर्णांक	(*resume)(काष्ठा wpan_phy *wpan_phy);
	पूर्णांक	(*add_भव_पूर्णांकf)(काष्ठा wpan_phy *wpan_phy,
				    स्थिर अक्षर *name,
				    अचिन्हित अक्षर name_assign_type,
				    क्रमागत nl802154_अगरtype type,
				    __le64 extended_addr);
	पूर्णांक	(*del_भव_पूर्णांकf)(काष्ठा wpan_phy *wpan_phy,
				    काष्ठा wpan_dev *wpan_dev);
	पूर्णांक	(*set_channel)(काष्ठा wpan_phy *wpan_phy, u8 page, u8 channel);
	पूर्णांक	(*set_cca_mode)(काष्ठा wpan_phy *wpan_phy,
				स्थिर काष्ठा wpan_phy_cca *cca);
	पूर्णांक     (*set_cca_ed_level)(काष्ठा wpan_phy *wpan_phy, s32 ed_level);
	पूर्णांक     (*set_tx_घातer)(काष्ठा wpan_phy *wpan_phy, s32 घातer);
	पूर्णांक	(*set_pan_id)(काष्ठा wpan_phy *wpan_phy,
			      काष्ठा wpan_dev *wpan_dev, __le16 pan_id);
	पूर्णांक	(*set_लघु_addr)(काष्ठा wpan_phy *wpan_phy,
				  काष्ठा wpan_dev *wpan_dev, __le16 लघु_addr);
	पूर्णांक	(*set_backoff_exponent)(काष्ठा wpan_phy *wpan_phy,
					काष्ठा wpan_dev *wpan_dev, u8 min_be,
					u8 max_be);
	पूर्णांक	(*set_max_csma_backoffs)(काष्ठा wpan_phy *wpan_phy,
					 काष्ठा wpan_dev *wpan_dev,
					 u8 max_csma_backoffs);
	पूर्णांक	(*set_max_frame_retries)(काष्ठा wpan_phy *wpan_phy,
					 काष्ठा wpan_dev *wpan_dev,
					 s8 max_frame_retries);
	पूर्णांक	(*set_lbt_mode)(काष्ठा wpan_phy *wpan_phy,
				काष्ठा wpan_dev *wpan_dev, bool mode);
	पूर्णांक	(*set_ackreq_शेष)(काष्ठा wpan_phy *wpan_phy,
				      काष्ठा wpan_dev *wpan_dev, bool ackreq);
#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
	व्योम	(*get_llsec_table)(काष्ठा wpan_phy *wpan_phy,
				   काष्ठा wpan_dev *wpan_dev,
				   काष्ठा ieee802154_llsec_table **table);
	व्योम	(*lock_llsec_table)(काष्ठा wpan_phy *wpan_phy,
				    काष्ठा wpan_dev *wpan_dev);
	व्योम	(*unlock_llsec_table)(काष्ठा wpan_phy *wpan_phy,
				      काष्ठा wpan_dev *wpan_dev);
	/* TODO हटाओ locking/get table callbacks, this is part of the
	 * nl802154 पूर्णांकerface and should be accessible from ieee802154 layer.
	 */
	पूर्णांक	(*get_llsec_params)(काष्ठा wpan_phy *wpan_phy,
				    काष्ठा wpan_dev *wpan_dev,
				    काष्ठा ieee802154_llsec_params *params);
	पूर्णांक	(*set_llsec_params)(काष्ठा wpan_phy *wpan_phy,
				    काष्ठा wpan_dev *wpan_dev,
				    स्थिर काष्ठा ieee802154_llsec_params *params,
				    पूर्णांक changed);
	पूर्णांक	(*add_llsec_key)(काष्ठा wpan_phy *wpan_phy,
				 काष्ठा wpan_dev *wpan_dev,
				 स्थिर काष्ठा ieee802154_llsec_key_id *id,
				 स्थिर काष्ठा ieee802154_llsec_key *key);
	पूर्णांक	(*del_llsec_key)(काष्ठा wpan_phy *wpan_phy,
				 काष्ठा wpan_dev *wpan_dev,
				 स्थिर काष्ठा ieee802154_llsec_key_id *id);
	पूर्णांक	(*add_seclevel)(काष्ठा wpan_phy *wpan_phy,
				 काष्ठा wpan_dev *wpan_dev,
				 स्थिर काष्ठा ieee802154_llsec_seclevel *sl);
	पूर्णांक	(*del_seclevel)(काष्ठा wpan_phy *wpan_phy,
				 काष्ठा wpan_dev *wpan_dev,
				 स्थिर काष्ठा ieee802154_llsec_seclevel *sl);
	पूर्णांक	(*add_device)(काष्ठा wpan_phy *wpan_phy,
			      काष्ठा wpan_dev *wpan_dev,
			      स्थिर काष्ठा ieee802154_llsec_device *dev);
	पूर्णांक	(*del_device)(काष्ठा wpan_phy *wpan_phy,
			      काष्ठा wpan_dev *wpan_dev, __le64 extended_addr);
	पूर्णांक	(*add_devkey)(काष्ठा wpan_phy *wpan_phy,
			      काष्ठा wpan_dev *wpan_dev,
			      __le64 extended_addr,
			      स्थिर काष्ठा ieee802154_llsec_device_key *key);
	पूर्णांक	(*del_devkey)(काष्ठा wpan_phy *wpan_phy,
			      काष्ठा wpan_dev *wpan_dev,
			      __le64 extended_addr,
			      स्थिर काष्ठा ieee802154_llsec_device_key *key);
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */
पूर्ण;

अटल अंतरभूत bool
wpan_phy_supported_bool(bool b, क्रमागत nl802154_supported_bool_states st)
अणु
	चयन (st) अणु
	हाल NL802154_SUPPORTED_BOOL_TRUE:
		वापस b;
	हाल NL802154_SUPPORTED_BOOL_FALSE:
		वापस !b;
	हाल NL802154_SUPPORTED_BOOL_BOTH:
		वापस true;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस false;
पूर्ण

काष्ठा wpan_phy_supported अणु
	u32 channels[IEEE802154_MAX_PAGE + 1],
	    cca_modes, cca_opts, अगरtypes;
	क्रमागत nl802154_supported_bool_states lbt;
	u8 min_minbe, max_minbe, min_maxbe, max_maxbe,
	   min_csma_backoffs, max_csma_backoffs;
	s8 min_frame_retries, max_frame_retries;
	माप_प्रकार tx_घातers_size, cca_ed_levels_size;
	स्थिर s32 *tx_घातers, *cca_ed_levels;
पूर्ण;

काष्ठा wpan_phy_cca अणु
	क्रमागत nl802154_cca_modes mode;
	क्रमागत nl802154_cca_opts opt;
पूर्ण;

अटल अंतरभूत bool
wpan_phy_cca_cmp(स्थिर काष्ठा wpan_phy_cca *a, स्थिर काष्ठा wpan_phy_cca *b)
अणु
	अगर (a->mode != b->mode)
		वापस false;

	अगर (a->mode == NL802154_CCA_ENERGY_CARRIER)
		वापस a->opt == b->opt;

	वापस true;
पूर्ण

/**
 * @WPAN_PHY_FLAG_TRANSMIT_POWER: Indicates that transceiver will support
 *	transmit घातer setting.
 * @WPAN_PHY_FLAG_CCA_ED_LEVEL: Indicates that transceiver will support cca ed
 *	level setting.
 * @WPAN_PHY_FLAG_CCA_MODE: Indicates that transceiver will support cca mode
 *	setting.
 */
क्रमागत wpan_phy_flags अणु
	WPAN_PHY_FLAG_TXPOWER		= BIT(1),
	WPAN_PHY_FLAG_CCA_ED_LEVEL	= BIT(2),
	WPAN_PHY_FLAG_CCA_MODE		= BIT(3),
पूर्ण;

काष्ठा wpan_phy अणु
	/* If multiple wpan_phys are रेजिस्टरed and you're handed e.g.
	 * a regular netdev with asचिन्हित ieee802154_ptr, you won't
	 * know whether it poपूर्णांकs to a wpan_phy your driver has रेजिस्टरed
	 * or not. Assign this to something global to your driver to
	 * help determine whether you own this wpan_phy or not.
	 */
	स्थिर व्योम *privid;

	u32 flags;

	/*
	 * This is a PIB according to 802.15.4-2011.
	 * We करो not provide timing-related variables, as they
	 * aren't used outside of driver
	 */
	u8 current_channel;
	u8 current_page;
	काष्ठा wpan_phy_supported supported;
	/* current transmit_घातer in mBm */
	s32 transmit_घातer;
	काष्ठा wpan_phy_cca cca;

	__le64 perm_extended_addr;

	/* current cca ed threshold in mBm */
	s32 cca_ed_level;

	/* PHY depended MAC PIB values */

	/* 802.15.4 acronym: Tdsym in usec */
	u8 symbol_duration;
	/* lअगरs and sअगरs periods timing */
	u16 lअगरs_period;
	u16 sअगरs_period;

	काष्ठा device dev;

	/* the network namespace this phy lives in currently */
	possible_net_t _net;

	अक्षर priv[] __aligned(NETDEV_ALIGN);
पूर्ण;

अटल अंतरभूत काष्ठा net *wpan_phy_net(काष्ठा wpan_phy *wpan_phy)
अणु
	वापस पढ़ो_pnet(&wpan_phy->_net);
पूर्ण

अटल अंतरभूत व्योम wpan_phy_net_set(काष्ठा wpan_phy *wpan_phy, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&wpan_phy->_net, net);
पूर्ण

काष्ठा ieee802154_addr अणु
	u8 mode;
	__le16 pan_id;
	जोड़ अणु
		__le16 लघु_addr;
		__le64 extended_addr;
	पूर्ण;
पूर्ण;

काष्ठा ieee802154_llsec_key_id अणु
	u8 mode;
	u8 id;
	जोड़ अणु
		काष्ठा ieee802154_addr device_addr;
		__le32 लघु_source;
		__le64 extended_source;
	पूर्ण;
पूर्ण;

#घोषणा IEEE802154_LLSEC_KEY_SIZE 16

काष्ठा ieee802154_llsec_key अणु
	u8 frame_types;
	u32 cmd_frame_ids;
	/* TODO replace with NL802154_KEY_SIZE */
	u8 key[IEEE802154_LLSEC_KEY_SIZE];
पूर्ण;

काष्ठा ieee802154_llsec_key_entry अणु
	काष्ठा list_head list;

	काष्ठा ieee802154_llsec_key_id id;
	काष्ठा ieee802154_llsec_key *key;
पूर्ण;

काष्ठा ieee802154_llsec_params अणु
	bool enabled;

	__be32 frame_counter;
	u8 out_level;
	काष्ठा ieee802154_llsec_key_id out_key;

	__le64 शेष_key_source;

	__le16 pan_id;
	__le64 hwaddr;
	__le64 coord_hwaddr;
	__le16 coord_लघुaddr;
पूर्ण;

काष्ठा ieee802154_llsec_table अणु
	काष्ठा list_head keys;
	काष्ठा list_head devices;
	काष्ठा list_head security_levels;
पूर्ण;

काष्ठा ieee802154_llsec_seclevel अणु
	काष्ठा list_head list;

	u8 frame_type;
	u8 cmd_frame_id;
	bool device_override;
	u32 sec_levels;
पूर्ण;

काष्ठा ieee802154_llsec_device अणु
	काष्ठा list_head list;

	__le16 pan_id;
	__le16 लघु_addr;
	__le64 hwaddr;
	u32 frame_counter;
	bool seclevel_exempt;

	u8 key_mode;
	काष्ठा list_head keys;
पूर्ण;

काष्ठा ieee802154_llsec_device_key अणु
	काष्ठा list_head list;

	काष्ठा ieee802154_llsec_key_id key_id;
	u32 frame_counter;
पूर्ण;

काष्ठा wpan_dev_header_ops अणु
	/* TODO create callback currently assumes ieee802154_mac_cb inside
	 * skb->cb. This should be changed to give these inक्रमmation as
	 * parameter.
	 */
	पूर्णांक	(*create)(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  स्थिर काष्ठा ieee802154_addr *daddr,
			  स्थिर काष्ठा ieee802154_addr *saddr,
			  अचिन्हित पूर्णांक len);
पूर्ण;

काष्ठा wpan_dev अणु
	काष्ठा wpan_phy *wpan_phy;
	पूर्णांक अगरtype;

	/* the reमुख्यder of this काष्ठा should be निजी to cfg802154 */
	काष्ठा list_head list;
	काष्ठा net_device *netdev;

	स्थिर काष्ठा wpan_dev_header_ops *header_ops;

	/* lowpan पूर्णांकerface, set when the wpan_dev beदीर्घs to one lowpan_dev */
	काष्ठा net_device *lowpan_dev;

	u32 identअगरier;

	/* MAC PIB */
	__le16 pan_id;
	__le16 लघु_addr;
	__le64 extended_addr;

	/* MAC BSN field */
	atomic_t bsn;
	/* MAC DSN field */
	atomic_t dsn;

	u8 min_be;
	u8 max_be;
	u8 csma_retries;
	s8 frame_retries;

	bool lbt;

	bool promiscuous_mode;

	/* fallback क्रम acknowledgment bit setting */
	bool ackreq;
पूर्ण;

#घोषणा to_phy(_dev)	container_of(_dev, काष्ठा wpan_phy, dev)

अटल अंतरभूत पूर्णांक
wpan_dev_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		     स्थिर काष्ठा ieee802154_addr *daddr,
		     स्थिर काष्ठा ieee802154_addr *saddr,
		     अचिन्हित पूर्णांक len)
अणु
	काष्ठा wpan_dev *wpan_dev = dev->ieee802154_ptr;

	वापस wpan_dev->header_ops->create(skb, dev, daddr, saddr, len);
पूर्ण

काष्ठा wpan_phy *
wpan_phy_new(स्थिर काष्ठा cfg802154_ops *ops, माप_प्रकार priv_size);
अटल अंतरभूत व्योम wpan_phy_set_dev(काष्ठा wpan_phy *phy, काष्ठा device *dev)
अणु
	phy->dev.parent = dev;
पूर्ण

पूर्णांक wpan_phy_रेजिस्टर(काष्ठा wpan_phy *phy);
व्योम wpan_phy_unरेजिस्टर(काष्ठा wpan_phy *phy);
व्योम wpan_phy_मुक्त(काष्ठा wpan_phy *phy);
/* Same semantics as क्रम class_क्रम_each_device */
पूर्णांक wpan_phy_क्रम_each(पूर्णांक (*fn)(काष्ठा wpan_phy *phy, व्योम *data), व्योम *data);

अटल अंतरभूत व्योम *wpan_phy_priv(काष्ठा wpan_phy *phy)
अणु
	BUG_ON(!phy);
	वापस &phy->priv;
पूर्ण

काष्ठा wpan_phy *wpan_phy_find(स्थिर अक्षर *str);

अटल अंतरभूत व्योम wpan_phy_put(काष्ठा wpan_phy *phy)
अणु
	put_device(&phy->dev);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *wpan_phy_name(काष्ठा wpan_phy *phy)
अणु
	वापस dev_name(&phy->dev);
पूर्ण

#पूर्ण_अगर /* __NET_CFG802154_H */
