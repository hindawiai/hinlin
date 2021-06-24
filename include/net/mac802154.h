<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * IEEE802.15.4-2003 specअगरication
 *
 * Copyright (C) 2007-2012 Siemens AG
 */
#अगर_अघोषित NET_MAC802154_H
#घोषणा NET_MAC802154_H

#समावेश <यंत्र/unaligned.h>
#समावेश <net/af_ieee802154.h>
#समावेश <linux/ieee802154.h>
#समावेश <linux/skbuff.h>

#समावेश <net/cfg802154.h>

/**
 * क्रमागत ieee802154_hw_addr_filt_flags - hardware address filtering flags
 *
 * The following flags are used to indicate changed address settings from
 * the stack to the hardware.
 *
 * @IEEE802154_AFILT_SADDR_CHANGED: Indicates that the लघु address will be
 *	change.
 *
 * @IEEE802154_AFILT_IEEEADDR_CHANGED: Indicates that the extended address
 *	will be change.
 *
 * @IEEE802154_AFILT_PANID_CHANGED: Indicates that the pan id will be change.
 *
 * @IEEE802154_AFILT_PANC_CHANGED: Indicates that the address filter will
 *	करो frame address filtering as a pan coordinator.
 */
क्रमागत ieee802154_hw_addr_filt_flags अणु
	IEEE802154_AFILT_SADDR_CHANGED		= BIT(0),
	IEEE802154_AFILT_IEEEADDR_CHANGED	= BIT(1),
	IEEE802154_AFILT_PANID_CHANGED		= BIT(2),
	IEEE802154_AFILT_PANC_CHANGED		= BIT(3),
पूर्ण;

/**
 * काष्ठा ieee802154_hw_addr_filt - hardware address filtering settings
 *
 * @pan_id: pan_id which should be set to the hardware address filter.
 *
 * @लघु_addr: लघु_addr which should be set to the hardware address filter.
 *
 * @ieee_addr: extended address which should be set to the hardware address
 *	filter.
 *
 * @pan_coord: boolean अगर hardware filtering should be operate as coordinator.
 */
काष्ठा ieee802154_hw_addr_filt अणु
	__le16	pan_id;
	__le16	लघु_addr;
	__le64	ieee_addr;
	bool	pan_coord;
पूर्ण;

/**
 * काष्ठा ieee802154_hw - ieee802154 hardware
 *
 * @extra_tx_headroom: headroom to reserve in each transmit skb क्रम use by the
 *	driver (e.g. क्रम transmit headers.)
 *
 * @flags: hardware flags, see &क्रमागत ieee802154_hw_flags
 *
 * @parent: parent device of the hardware.
 *
 * @priv: poपूर्णांकer to निजी area that was allocated क्रम driver use aदीर्घ with
 *	this काष्ठाure.
 *
 * @phy: This poपूर्णांकs to the &काष्ठा wpan_phy allocated क्रम this 802.15.4 PHY.
 */
काष्ठा ieee802154_hw अणु
	/* filled by the driver */
	पूर्णांक	extra_tx_headroom;
	u32	flags;
	काष्ठा	device *parent;
	व्योम	*priv;

	/* filled by mac802154 core */
	काष्ठा	wpan_phy *phy;
पूर्ण;

/**
 * क्रमागत ieee802154_hw_flags - hardware flags
 *
 * These flags are used to indicate hardware capabilities to
 * the stack. Generally, flags here should have their meaning
 * करोne in a way that the simplest hardware करोesn't need setting
 * any particular flags. There are some exceptions to this rule,
 * however, so you are advised to review these flags carefully.
 *
 * @IEEE802154_HW_TX_OMIT_CKSUM: Indicates that xmitter will add FCS on it's
 *	own.
 *
 * @IEEE802154_HW_LBT: Indicates that transceiver will support listen beक्रमe
 *	transmit.
 *
 * @IEEE802154_HW_CSMA_PARAMS: Indicates that transceiver will support csma
 *	parameters (max_be, min_be, backoff exponents).
 *
 * @IEEE802154_HW_FRAME_RETRIES: Indicates that transceiver will support ARET
 *	frame retries setting.
 *
 * @IEEE802154_HW_AFILT: Indicates that transceiver will support hardware
 *	address filter setting.
 *
 * @IEEE802154_HW_PROMISCUOUS: Indicates that transceiver will support
 *	promiscuous mode setting.
 *
 * @IEEE802154_HW_RX_OMIT_CKSUM: Indicates that receiver omits FCS.
 *
 * @IEEE802154_HW_RX_DROP_BAD_CKSUM: Indicates that receiver will not filter
 *	frames with bad checksum.
 */
क्रमागत ieee802154_hw_flags अणु
	IEEE802154_HW_TX_OMIT_CKSUM	= BIT(0),
	IEEE802154_HW_LBT		= BIT(1),
	IEEE802154_HW_CSMA_PARAMS	= BIT(2),
	IEEE802154_HW_FRAME_RETRIES	= BIT(3),
	IEEE802154_HW_AFILT		= BIT(4),
	IEEE802154_HW_PROMISCUOUS	= BIT(5),
	IEEE802154_HW_RX_OMIT_CKSUM	= BIT(6),
	IEEE802154_HW_RX_DROP_BAD_CKSUM	= BIT(7),
पूर्ण;

/* Indicates that receiver omits FCS and xmitter will add FCS on it's own. */
#घोषणा IEEE802154_HW_OMIT_CKSUM	(IEEE802154_HW_TX_OMIT_CKSUM | \
					 IEEE802154_HW_RX_OMIT_CKSUM)

/* काष्ठा ieee802154_ops - callbacks from mac802154 to the driver
 *
 * This काष्ठाure contains various callbacks that the driver may
 * handle or, in some हालs, must handle, क्रम example to transmit
 * a frame.
 *
 * start: Handler that 802.15.4 module calls क्रम device initialization.
 *	  This function is called beक्रमe the first पूर्णांकerface is attached.
 *
 * stop:  Handler that 802.15.4 module calls क्रम device cleanup.
 *	  This function is called after the last पूर्णांकerface is हटाओd.
 *
 * xmit_sync:
 *	  Handler that 802.15.4 module calls क्रम each transmitted frame.
 *	  skb cntains the buffer starting from the IEEE 802.15.4 header.
 *	  The low-level driver should send the frame based on available
 *	  configuration. This is called by a workqueue and useful क्रम
 *	  synchronous 802.15.4 drivers.
 *	  This function should वापस zero or negative त्रुटि_सं.
 *
 *	  WARNING:
 *	  This will be deprecated soon. We करोn't accept synced xmit callbacks
 *	  drivers anymore.
 *
 * xmit_async:
 *	  Handler that 802.15.4 module calls क्रम each transmitted frame.
 *	  skb cntains the buffer starting from the IEEE 802.15.4 header.
 *	  The low-level driver should send the frame based on available
 *	  configuration.
 *	  This function should वापस zero or negative त्रुटि_सं.
 *
 * ed:    Handler that 802.15.4 module calls क्रम Energy Detection.
 *	  This function should place the value क्रम detected energy
 *	  (usually device-dependant) in the level poपूर्णांकer and वापस
 *	  either zero or negative त्रुटि_सं. Called with pib_lock held.
 *
 * set_channel:
 * 	  Set radio क्रम listening on specअगरic channel.
 *	  Set the device क्रम listening on specअगरied channel.
 *	  Returns either zero, or negative त्रुटि_सं. Called with pib_lock held.
 *
 * set_hw_addr_filt:
 *	  Set radio क्रम listening on specअगरic address.
 *	  Set the device क्रम listening on specअगरied address.
 *	  Returns either zero, or negative त्रुटि_सं.
 *
 * set_txघातer:
 *	  Set radio transmit घातer in mBm. Called with pib_lock held.
 *	  Returns either zero, or negative त्रुटि_सं.
 *
 * set_lbt
 *	  Enables or disables listen beक्रमe talk on the device. Called with
 *	  pib_lock held.
 *	  Returns either zero, or negative त्रुटि_सं.
 *
 * set_cca_mode
 *	  Sets the CCA mode used by the device. Called with pib_lock held.
 *	  Returns either zero, or negative त्रुटि_सं.
 *
 * set_cca_ed_level
 *	  Sets the CCA energy detection threshold in mBm. Called with pib_lock
 *	  held.
 *	  Returns either zero, or negative त्रुटि_सं.
 *
 * set_csma_params
 *	  Sets the CSMA parameter set क्रम the PHY. Called with pib_lock held.
 *	  Returns either zero, or negative त्रुटि_सं.
 *
 * set_frame_retries
 *	  Sets the retransmission attempt limit. Called with pib_lock held.
 *	  Returns either zero, or negative त्रुटि_सं.
 *
 * set_promiscuous_mode
 *	  Enables or disable promiscuous mode.
 */
काष्ठा ieee802154_ops अणु
	काष्ठा module	*owner;
	पूर्णांक		(*start)(काष्ठा ieee802154_hw *hw);
	व्योम		(*stop)(काष्ठा ieee802154_hw *hw);
	पूर्णांक		(*xmit_sync)(काष्ठा ieee802154_hw *hw,
				     काष्ठा sk_buff *skb);
	पूर्णांक		(*xmit_async)(काष्ठा ieee802154_hw *hw,
				      काष्ठा sk_buff *skb);
	पूर्णांक		(*ed)(काष्ठा ieee802154_hw *hw, u8 *level);
	पूर्णांक		(*set_channel)(काष्ठा ieee802154_hw *hw, u8 page,
				       u8 channel);
	पूर्णांक		(*set_hw_addr_filt)(काष्ठा ieee802154_hw *hw,
					    काष्ठा ieee802154_hw_addr_filt *filt,
					    अचिन्हित दीर्घ changed);
	पूर्णांक		(*set_txघातer)(काष्ठा ieee802154_hw *hw, s32 mbm);
	पूर्णांक		(*set_lbt)(काष्ठा ieee802154_hw *hw, bool on);
	पूर्णांक		(*set_cca_mode)(काष्ठा ieee802154_hw *hw,
					स्थिर काष्ठा wpan_phy_cca *cca);
	पूर्णांक		(*set_cca_ed_level)(काष्ठा ieee802154_hw *hw, s32 mbm);
	पूर्णांक		(*set_csma_params)(काष्ठा ieee802154_hw *hw,
					   u8 min_be, u8 max_be, u8 retries);
	पूर्णांक		(*set_frame_retries)(काष्ठा ieee802154_hw *hw,
					     s8 retries);
	पूर्णांक             (*set_promiscuous_mode)(काष्ठा ieee802154_hw *hw,
						स्थिर bool on);
पूर्ण;

/**
 * ieee802154_get_fc_from_skb - get the frame control field from an skb
 * @skb: skb where the frame control field will be get from
 */
अटल अंतरभूत __le16 ieee802154_get_fc_from_skb(स्थिर काष्ठा sk_buff *skb)
अणु
	__le16 fc;

	/* check अगर we can fc at skb_mac_header of sk buffer */
	अगर (WARN_ON(!skb_mac_header_was_set(skb) ||
		    (skb_tail_poपूर्णांकer(skb) -
		     skb_mac_header(skb)) < IEEE802154_FC_LEN))
		वापस cpu_to_le16(0);

	स_नकल(&fc, skb_mac_header(skb), IEEE802154_FC_LEN);
	वापस fc;
पूर्ण

/**
 * ieee802154_skb_dst_pan - get the poपूर्णांकer to destination pan field
 * @fc: mac header frame control field
 * @skb: skb where the destination pan poपूर्णांकer will be get from
 */
अटल अंतरभूत अचिन्हित अक्षर *ieee802154_skb_dst_pan(__le16 fc,
						    स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *dst_pan;

	चयन (ieee802154_daddr_mode(fc)) अणु
	हाल cpu_to_le16(IEEE802154_FCTL_ADDR_NONE):
		dst_pan = शून्य;
		अवरोध;
	हाल cpu_to_le16(IEEE802154_FCTL_DADDR_SHORT):
	हाल cpu_to_le16(IEEE802154_FCTL_DADDR_EXTENDED):
		dst_pan = skb_mac_header(skb) +
			  IEEE802154_FC_LEN +
			  IEEE802154_SEQ_LEN;
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid addr mode detected");
		dst_pan = शून्य;
		अवरोध;
	पूर्ण

	वापस dst_pan;
पूर्ण

/**
 * ieee802154_skb_src_pan - get the poपूर्णांकer to source pan field
 * @fc: mac header frame control field
 * @skb: skb where the source pan poपूर्णांकer will be get from
 */
अटल अंतरभूत अचिन्हित अक्षर *ieee802154_skb_src_pan(__le16 fc,
						    स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *src_pan;

	चयन (ieee802154_saddr_mode(fc)) अणु
	हाल cpu_to_le16(IEEE802154_FCTL_ADDR_NONE):
		src_pan = शून्य;
		अवरोध;
	हाल cpu_to_le16(IEEE802154_FCTL_SADDR_SHORT):
	हाल cpu_to_le16(IEEE802154_FCTL_SADDR_EXTENDED):
		/* अगर पूर्णांकra-pan and source addr mode is non none,
		 * then source pan id is equal destination pan id.
		 */
		अगर (ieee802154_is_पूर्णांकra_pan(fc)) अणु
			src_pan = ieee802154_skb_dst_pan(fc, skb);
			अवरोध;
		पूर्ण

		चयन (ieee802154_daddr_mode(fc)) अणु
		हाल cpu_to_le16(IEEE802154_FCTL_ADDR_NONE):
			src_pan = skb_mac_header(skb) +
				  IEEE802154_FC_LEN +
				  IEEE802154_SEQ_LEN;
			अवरोध;
		हाल cpu_to_le16(IEEE802154_FCTL_DADDR_SHORT):
			src_pan = skb_mac_header(skb) +
				  IEEE802154_FC_LEN +
				  IEEE802154_SEQ_LEN +
				  IEEE802154_PAN_ID_LEN +
				  IEEE802154_SHORT_ADDR_LEN;
			अवरोध;
		हाल cpu_to_le16(IEEE802154_FCTL_DADDR_EXTENDED):
			src_pan = skb_mac_header(skb) +
				  IEEE802154_FC_LEN +
				  IEEE802154_SEQ_LEN +
				  IEEE802154_PAN_ID_LEN +
				  IEEE802154_EXTENDED_ADDR_LEN;
			अवरोध;
		शेष:
			WARN_ONCE(1, "invalid addr mode detected");
			src_pan = शून्य;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ONCE(1, "invalid addr mode detected");
		src_pan = शून्य;
		अवरोध;
	पूर्ण

	वापस src_pan;
पूर्ण

/**
 * ieee802154_skb_is_पूर्णांकra_pan_addressing - checks whenever the mac addressing
 *	is an पूर्णांकra pan communication
 * @fc: mac header frame control field
 * @skb: skb where the source and destination pan should be get from
 */
अटल अंतरभूत bool ieee802154_skb_is_पूर्णांकra_pan_addressing(__le16 fc,
							  स्थिर काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *dst_pan = ieee802154_skb_dst_pan(fc, skb),
		      *src_pan = ieee802154_skb_src_pan(fc, skb);

	/* अगर one is शून्य is no पूर्णांकra pan addressing */
	अगर (!dst_pan || !src_pan)
		वापस false;

	वापस !स_भेद(dst_pan, src_pan, IEEE802154_PAN_ID_LEN);
पूर्ण

/**
 * ieee802154_be64_to_le64 - copies and convert be64 to le64
 * @le64_dst: le64 destination poपूर्णांकer
 * @be64_src: be64 source poपूर्णांकer
 */
अटल अंतरभूत व्योम ieee802154_be64_to_le64(व्योम *le64_dst, स्थिर व्योम *be64_src)
अणु
	put_unaligned_le64(get_unaligned_be64(be64_src), le64_dst);
पूर्ण

/**
 * ieee802154_le64_to_be64 - copies and convert le64 to be64
 * @be64_dst: be64 destination poपूर्णांकer
 * @le64_src: le64 source poपूर्णांकer
 */
अटल अंतरभूत व्योम ieee802154_le64_to_be64(व्योम *be64_dst, स्थिर व्योम *le64_src)
अणु
	put_unaligned_be64(get_unaligned_le64(le64_src), be64_dst);
पूर्ण

/**
 * ieee802154_le16_to_be16 - copies and convert le16 to be16
 * @be16_dst: be16 destination poपूर्णांकer
 * @le16_src: le16 source poपूर्णांकer
 */
अटल अंतरभूत व्योम ieee802154_le16_to_be16(व्योम *be16_dst, स्थिर व्योम *le16_src)
अणु
	put_unaligned_be16(get_unaligned_le16(le16_src), be16_dst);
पूर्ण

/**
 * ieee802154_be16_to_le16 - copies and convert be16 to le16
 * @le16_dst: le16 destination poपूर्णांकer
 * @be16_src: be16 source poपूर्णांकer
 */
अटल अंतरभूत व्योम ieee802154_be16_to_le16(व्योम *le16_dst, स्थिर व्योम *be16_src)
अणु
	put_unaligned_le16(get_unaligned_be16(be16_src), le16_dst);
पूर्ण

/**
 * ieee802154_alloc_hw - Allocate a new hardware device
 *
 * This must be called once क्रम each hardware device. The वापसed poपूर्णांकer
 * must be used to refer to this device when calling other functions.
 * mac802154 allocates a निजी data area क्रम the driver poपूर्णांकed to by
 * @priv in &काष्ठा ieee802154_hw, the size of this area is given as
 * @priv_data_len.
 *
 * @priv_data_len: length of निजी data
 * @ops: callbacks क्रम this device
 *
 * Return: A poपूर्णांकer to the new hardware device, or %शून्य on error.
 */
काष्ठा ieee802154_hw *
ieee802154_alloc_hw(माप_प्रकार priv_data_len, स्थिर काष्ठा ieee802154_ops *ops);

/**
 * ieee802154_मुक्त_hw - मुक्त hardware descriptor
 *
 * This function मुक्तs everything that was allocated, including the
 * निजी data क्रम the driver. You must call ieee802154_unरेजिस्टर_hw()
 * beक्रमe calling this function.
 *
 * @hw: the hardware to मुक्त
 */
व्योम ieee802154_मुक्त_hw(काष्ठा ieee802154_hw *hw);

/**
 * ieee802154_रेजिस्टर_hw - Register hardware device
 *
 * You must call this function beक्रमe any other functions in
 * mac802154. Note that beक्रमe a hardware can be रेजिस्टरed, you
 * need to fill the contained wpan_phy's inक्रमmation.
 *
 * @hw: the device to रेजिस्टर as वापसed by ieee802154_alloc_hw()
 *
 * Return: 0 on success. An error code otherwise.
 */
पूर्णांक ieee802154_रेजिस्टर_hw(काष्ठा ieee802154_hw *hw);

/**
 * ieee802154_unरेजिस्टर_hw - Unरेजिस्टर a hardware device
 *
 * This function inकाष्ठाs mac802154 to मुक्त allocated resources
 * and unरेजिस्टर netdevices from the networking subप्रणाली.
 *
 * @hw: the hardware to unरेजिस्टर
 */
व्योम ieee802154_unरेजिस्टर_hw(काष्ठा ieee802154_hw *hw);

/**
 * ieee802154_rx_irqsafe - receive frame
 *
 * Like ieee802154_rx() but can be called in IRQ context
 * (पूर्णांकernally defers to a tasklet.)
 *
 * @hw: the hardware this frame came in on
 * @skb: the buffer to receive, owned by mac802154 after this call
 * @lqi: link quality indicator
 */
व्योम ieee802154_rx_irqsafe(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb,
			   u8 lqi);
/**
 * ieee802154_wake_queue - wake ieee802154 queue
 * @hw: poपूर्णांकer as obtained from ieee802154_alloc_hw().
 *
 * Drivers should use this function instead of netअगर_wake_queue.
 */
व्योम ieee802154_wake_queue(काष्ठा ieee802154_hw *hw);

/**
 * ieee802154_stop_queue - stop ieee802154 queue
 * @hw: poपूर्णांकer as obtained from ieee802154_alloc_hw().
 *
 * Drivers should use this function instead of netअगर_stop_queue.
 */
व्योम ieee802154_stop_queue(काष्ठा ieee802154_hw *hw);

/**
 * ieee802154_xmit_complete - frame transmission complete
 *
 * @hw: poपूर्णांकer as obtained from ieee802154_alloc_hw().
 * @skb: buffer क्रम transmission
 * @अगरs_handling: indicate पूर्णांकerframe space handling
 */
व्योम ieee802154_xmit_complete(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb,
			      bool अगरs_handling);

#पूर्ण_अगर /* NET_MAC802154_H */
