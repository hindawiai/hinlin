<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CFG802154_RDEV_OPS
#घोषणा __CFG802154_RDEV_OPS

#समावेश <net/cfg802154.h>

#समावेश "core.h"
#समावेश "trace.h"

अटल अंतरभूत काष्ठा net_device *
rdev_add_भव_पूर्णांकf_deprecated(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				 स्थिर अक्षर *name,
				 अचिन्हित अक्षर name_assign_type,
				 पूर्णांक type)
अणु
	वापस rdev->ops->add_भव_पूर्णांकf_deprecated(&rdev->wpan_phy, name,
						      name_assign_type, type);
पूर्ण

अटल अंतरभूत व्योम
rdev_del_भव_पूर्णांकf_deprecated(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev)
अणु
	rdev->ops->del_भव_पूर्णांकf_deprecated(&rdev->wpan_phy, dev);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_suspend(काष्ठा cfg802154_रेजिस्टरed_device *rdev)
अणु
	पूर्णांक ret;
	trace_802154_rdev_suspend(&rdev->wpan_phy);
	ret = rdev->ops->suspend(&rdev->wpan_phy);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_resume(काष्ठा cfg802154_रेजिस्टरed_device *rdev)
अणु
	पूर्णांक ret;
	trace_802154_rdev_resume(&rdev->wpan_phy);
	ret = rdev->ops->resume(&rdev->wpan_phy);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_add_भव_पूर्णांकf(काष्ठा cfg802154_रेजिस्टरed_device *rdev, अक्षर *name,
		      अचिन्हित अक्षर name_assign_type,
		      क्रमागत nl802154_अगरtype type, __le64 extended_addr)
अणु
	पूर्णांक ret;

	trace_802154_rdev_add_भव_पूर्णांकf(&rdev->wpan_phy, name, type,
					   extended_addr);
	ret = rdev->ops->add_भव_पूर्णांकf(&rdev->wpan_phy, name,
					  name_assign_type, type,
					  extended_addr);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_del_भव_पूर्णांकf(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		      काष्ठा wpan_dev *wpan_dev)
अणु
	पूर्णांक ret;

	trace_802154_rdev_del_भव_पूर्णांकf(&rdev->wpan_phy, wpan_dev);
	ret = rdev->ops->del_भव_पूर्णांकf(&rdev->wpan_phy, wpan_dev);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_channel(काष्ठा cfg802154_रेजिस्टरed_device *rdev, u8 page, u8 channel)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_channel(&rdev->wpan_phy, page, channel);
	ret = rdev->ops->set_channel(&rdev->wpan_phy, page, channel);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_cca_mode(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		  स्थिर काष्ठा wpan_phy_cca *cca)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_cca_mode(&rdev->wpan_phy, cca);
	ret = rdev->ops->set_cca_mode(&rdev->wpan_phy, cca);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_cca_ed_level(काष्ठा cfg802154_रेजिस्टरed_device *rdev, s32 ed_level)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_cca_ed_level(&rdev->wpan_phy, ed_level);
	ret = rdev->ops->set_cca_ed_level(&rdev->wpan_phy, ed_level);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_tx_घातer(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		  s32 घातer)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_tx_घातer(&rdev->wpan_phy, घातer);
	ret = rdev->ops->set_tx_घातer(&rdev->wpan_phy, घातer);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_pan_id(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		काष्ठा wpan_dev *wpan_dev, __le16 pan_id)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_pan_id(&rdev->wpan_phy, wpan_dev, pan_id);
	ret = rdev->ops->set_pan_id(&rdev->wpan_phy, wpan_dev, pan_id);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_लघु_addr(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		    काष्ठा wpan_dev *wpan_dev, __le16 लघु_addr)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_लघु_addr(&rdev->wpan_phy, wpan_dev, लघु_addr);
	ret = rdev->ops->set_लघु_addr(&rdev->wpan_phy, wpan_dev, लघु_addr);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_backoff_exponent(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			  काष्ठा wpan_dev *wpan_dev, u8 min_be, u8 max_be)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_backoff_exponent(&rdev->wpan_phy, wpan_dev,
					       min_be, max_be);
	ret = rdev->ops->set_backoff_exponent(&rdev->wpan_phy, wpan_dev,
					      min_be, max_be);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_max_csma_backoffs(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			   काष्ठा wpan_dev *wpan_dev, u8 max_csma_backoffs)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_csma_backoffs(&rdev->wpan_phy, wpan_dev,
					    max_csma_backoffs);
	ret = rdev->ops->set_max_csma_backoffs(&rdev->wpan_phy, wpan_dev,
					       max_csma_backoffs);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_max_frame_retries(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			   काष्ठा wpan_dev *wpan_dev, s8 max_frame_retries)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_max_frame_retries(&rdev->wpan_phy, wpan_dev,
						max_frame_retries);
	ret = rdev->ops->set_max_frame_retries(&rdev->wpan_phy, wpan_dev,
					       max_frame_retries);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_lbt_mode(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		  काष्ठा wpan_dev *wpan_dev, bool mode)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_lbt_mode(&rdev->wpan_phy, wpan_dev, mode);
	ret = rdev->ops->set_lbt_mode(&rdev->wpan_phy, wpan_dev, mode);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_ackreq_शेष(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			काष्ठा wpan_dev *wpan_dev, bool ackreq)
अणु
	पूर्णांक ret;

	trace_802154_rdev_set_ackreq_शेष(&rdev->wpan_phy, wpan_dev,
					     ackreq);
	ret = rdev->ops->set_ackreq_शेष(&rdev->wpan_phy, wpan_dev, ackreq);
	trace_802154_rdev_वापस_पूर्णांक(&rdev->wpan_phy, ret);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IEEE802154_NL802154_EXPERIMENTAL
/* TODO this is alपढ़ोy a nl802154, so move पूर्णांकo ieee802154 */
अटल अंतरभूत व्योम
rdev_get_llsec_table(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		     काष्ठा wpan_dev *wpan_dev,
		     काष्ठा ieee802154_llsec_table **table)
अणु
	rdev->ops->get_llsec_table(&rdev->wpan_phy, wpan_dev, table);
पूर्ण

अटल अंतरभूत व्योम
rdev_lock_llsec_table(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		      काष्ठा wpan_dev *wpan_dev)
अणु
	rdev->ops->lock_llsec_table(&rdev->wpan_phy, wpan_dev);
पूर्ण

अटल अंतरभूत व्योम
rdev_unlock_llsec_table(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
			काष्ठा wpan_dev *wpan_dev)
अणु
	rdev->ops->unlock_llsec_table(&rdev->wpan_phy, wpan_dev);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_get_llsec_params(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		      काष्ठा wpan_dev *wpan_dev,
		      काष्ठा ieee802154_llsec_params *params)
अणु
	वापस rdev->ops->get_llsec_params(&rdev->wpan_phy, wpan_dev, params);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_set_llsec_params(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		      काष्ठा wpan_dev *wpan_dev,
		      स्थिर काष्ठा ieee802154_llsec_params *params,
		      u32 changed)
अणु
	वापस rdev->ops->set_llsec_params(&rdev->wpan_phy, wpan_dev, params,
					   changed);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_add_llsec_key(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		   काष्ठा wpan_dev *wpan_dev,
		   स्थिर काष्ठा ieee802154_llsec_key_id *id,
		   स्थिर काष्ठा ieee802154_llsec_key *key)
अणु
	वापस rdev->ops->add_llsec_key(&rdev->wpan_phy, wpan_dev, id, key);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_del_llsec_key(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		   काष्ठा wpan_dev *wpan_dev,
		   स्थिर काष्ठा ieee802154_llsec_key_id *id)
अणु
	वापस rdev->ops->del_llsec_key(&rdev->wpan_phy, wpan_dev, id);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_add_seclevel(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		  काष्ठा wpan_dev *wpan_dev,
		  स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	वापस rdev->ops->add_seclevel(&rdev->wpan_phy, wpan_dev, sl);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_del_seclevel(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		  काष्ठा wpan_dev *wpan_dev,
		  स्थिर काष्ठा ieee802154_llsec_seclevel *sl)
अणु
	वापस rdev->ops->del_seclevel(&rdev->wpan_phy, wpan_dev, sl);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_add_device(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		काष्ठा wpan_dev *wpan_dev,
		स्थिर काष्ठा ieee802154_llsec_device *dev_desc)
अणु
	वापस rdev->ops->add_device(&rdev->wpan_phy, wpan_dev, dev_desc);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_del_device(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		काष्ठा wpan_dev *wpan_dev, __le64 extended_addr)
अणु
	वापस rdev->ops->del_device(&rdev->wpan_phy, wpan_dev, extended_addr);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_add_devkey(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		काष्ठा wpan_dev *wpan_dev, __le64 extended_addr,
		स्थिर काष्ठा ieee802154_llsec_device_key *devkey)
अणु
	वापस rdev->ops->add_devkey(&rdev->wpan_phy, wpan_dev, extended_addr,
				     devkey);
पूर्ण

अटल अंतरभूत पूर्णांक
rdev_del_devkey(काष्ठा cfg802154_रेजिस्टरed_device *rdev,
		काष्ठा wpan_dev *wpan_dev, __le64 extended_addr,
		स्थिर काष्ठा ieee802154_llsec_device_key *devkey)
अणु
	वापस rdev->ops->del_devkey(&rdev->wpan_phy, wpan_dev, extended_addr,
				     devkey);
पूर्ण
#पूर्ण_अगर /* CONFIG_IEEE802154_NL802154_EXPERIMENTAL */

#पूर्ण_अगर /* __CFG802154_RDEV_OPS */
