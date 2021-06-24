<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MAC802154_DRIVER_OPS
#घोषणा __MAC802154_DRIVER_OPS

#समावेश <linux/types.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/mac802154.h>

#समावेश "ieee802154_i.h"
#समावेश "trace.h"

अटल अंतरभूत पूर्णांक
drv_xmit_async(काष्ठा ieee802154_local *local, काष्ठा sk_buff *skb)
अणु
	वापस local->ops->xmit_async(&local->hw, skb);
पूर्ण

अटल अंतरभूत पूर्णांक
drv_xmit_sync(काष्ठा ieee802154_local *local, काष्ठा sk_buff *skb)
अणु
	might_sleep();

	वापस local->ops->xmit_sync(&local->hw, skb);
पूर्ण

अटल अंतरभूत पूर्णांक drv_start(काष्ठा ieee802154_local *local)
अणु
	पूर्णांक ret;

	might_sleep();

	trace_802154_drv_start(local);
	local->started = true;
	smp_mb();
	ret = local->ops->start(&local->hw);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_stop(काष्ठा ieee802154_local *local)
अणु
	might_sleep();

	trace_802154_drv_stop(local);
	local->ops->stop(&local->hw);
	trace_802154_drv_वापस_व्योम(local);

	/* sync away all work on the tasklet beक्रमe clearing started */
	tasklet_disable(&local->tasklet);
	tasklet_enable(&local->tasklet);

	barrier();

	local->started = false;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_channel(काष्ठा ieee802154_local *local, u8 page, u8 channel)
अणु
	पूर्णांक ret;

	might_sleep();

	trace_802154_drv_set_channel(local, page, channel);
	ret = local->ops->set_channel(&local->hw, page, channel);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_tx_घातer(काष्ठा ieee802154_local *local, s32 mbm)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_txघातer) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	trace_802154_drv_set_tx_घातer(local, mbm);
	ret = local->ops->set_txघातer(&local->hw, mbm);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_cca_mode(काष्ठा ieee802154_local *local,
				   स्थिर काष्ठा wpan_phy_cca *cca)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_cca_mode) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	trace_802154_drv_set_cca_mode(local, cca);
	ret = local->ops->set_cca_mode(&local->hw, cca);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_lbt_mode(काष्ठा ieee802154_local *local, bool mode)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_lbt) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	trace_802154_drv_set_lbt_mode(local, mode);
	ret = local->ops->set_lbt(&local->hw, mode);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_cca_ed_level(काष्ठा ieee802154_local *local, s32 mbm)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_cca_ed_level) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	trace_802154_drv_set_cca_ed_level(local, mbm);
	ret = local->ops->set_cca_ed_level(&local->hw, mbm);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_pan_id(काष्ठा ieee802154_local *local, __le16 pan_id)
अणु
	काष्ठा ieee802154_hw_addr_filt filt;
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_hw_addr_filt) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	filt.pan_id = pan_id;

	trace_802154_drv_set_pan_id(local, pan_id);
	ret = local->ops->set_hw_addr_filt(&local->hw, &filt,
					    IEEE802154_AFILT_PANID_CHANGED);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_extended_addr(काष्ठा ieee802154_local *local, __le64 extended_addr)
अणु
	काष्ठा ieee802154_hw_addr_filt filt;
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_hw_addr_filt) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	filt.ieee_addr = extended_addr;

	trace_802154_drv_set_extended_addr(local, extended_addr);
	ret = local->ops->set_hw_addr_filt(&local->hw, &filt,
					    IEEE802154_AFILT_IEEEADDR_CHANGED);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_लघु_addr(काष्ठा ieee802154_local *local, __le16 लघु_addr)
अणु
	काष्ठा ieee802154_hw_addr_filt filt;
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_hw_addr_filt) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	filt.लघु_addr = लघु_addr;

	trace_802154_drv_set_लघु_addr(local, लघु_addr);
	ret = local->ops->set_hw_addr_filt(&local->hw, &filt,
					    IEEE802154_AFILT_SADDR_CHANGED);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_pan_coord(काष्ठा ieee802154_local *local, bool is_coord)
अणु
	काष्ठा ieee802154_hw_addr_filt filt;
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_hw_addr_filt) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	filt.pan_coord = is_coord;

	trace_802154_drv_set_pan_coord(local, is_coord);
	ret = local->ops->set_hw_addr_filt(&local->hw, &filt,
					    IEEE802154_AFILT_PANC_CHANGED);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_csma_params(काष्ठा ieee802154_local *local, u8 min_be, u8 max_be,
		    u8 max_csma_backoffs)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_csma_params) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	trace_802154_drv_set_csma_params(local, min_be, max_be,
					 max_csma_backoffs);
	ret = local->ops->set_csma_params(&local->hw, min_be, max_be,
					   max_csma_backoffs);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_max_frame_retries(काष्ठा ieee802154_local *local, s8 max_frame_retries)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_frame_retries) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	trace_802154_drv_set_max_frame_retries(local, max_frame_retries);
	ret = local->ops->set_frame_retries(&local->hw, max_frame_retries);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_set_promiscuous_mode(काष्ठा ieee802154_local *local, bool on)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!local->ops->set_promiscuous_mode) अणु
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	trace_802154_drv_set_promiscuous_mode(local, on);
	ret = local->ops->set_promiscuous_mode(&local->hw, on);
	trace_802154_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* __MAC802154_DRIVER_OPS */
