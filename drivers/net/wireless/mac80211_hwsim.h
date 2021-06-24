<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * mac80211_hwsim - software simulator of 802.11 radio(s) क्रम mac80211
 * Copyright (c) 2008, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2011, Javier Lopez <jlopex@gmail.com>
 * Copyright (C) 2020 Intel Corporation
 */

#अगर_अघोषित __MAC80211_HWSIM_H
#घोषणा __MAC80211_HWSIM_H

/**
 * क्रमागत hwsim_tx_control_flags - flags to describe transmission info/status
 *
 * These flags are used to give the wmediumd extra inक्रमmation in order to
 * modअगरy its behavior क्रम each frame
 *
 * @HWSIM_TX_CTL_REQ_TX_STATUS: require TX status callback क्रम this frame.
 * @HWSIM_TX_CTL_NO_ACK: tell the wmediumd not to रुको क्रम an ack
 * @HWSIM_TX_STAT_ACK: Frame was acknowledged
 *
 */
क्रमागत hwsim_tx_control_flags अणु
	HWSIM_TX_CTL_REQ_TX_STATUS		= BIT(0),
	HWSIM_TX_CTL_NO_ACK			= BIT(1),
	HWSIM_TX_STAT_ACK			= BIT(2),
पूर्ण;

/**
 * DOC: Frame transmission/registration support
 *
 * Frame transmission and registration support exists to allow userspace
 * entities such as wmediumd to receive and process all broadcasted
 * frames from a mac80211_hwsim radio device.
 *
 * This allow user space applications to decide अगर the frame should be
 * dropped or not and implement a wireless medium simulator at user space.
 *
 * Registration is करोne by sending a रेजिस्टर message to the driver and
 * will be स्वतःmatically unरेजिस्टरed अगर the user application करोesn't
 * responds to sent frames.
 * Once रेजिस्टरed the user application has to take responsibility of
 * broadcasting the frames to all listening mac80211_hwsim radio
 * पूर्णांकerfaces.
 *
 * For more technical details, see the corresponding command descriptions
 * below.
 */

/**
 * क्रमागत hwsim_commands - supported hwsim commands
 *
 * @HWSIM_CMD_UNSPEC: unspecअगरied command to catch errors
 *
 * @HWSIM_CMD_REGISTER: request to रेजिस्टर and received all broadcasted
 *	frames by any mac80211_hwsim radio device.
 * @HWSIM_CMD_FRAME: send/receive a broadcasted frame from/to kernel/user
 *	space, uses:
 *	%HWSIM_ATTR_ADDR_TRANSMITTER, %HWSIM_ATTR_ADDR_RECEIVER,
 *	%HWSIM_ATTR_FRAME, %HWSIM_ATTR_FLAGS, %HWSIM_ATTR_RX_RATE,
 *	%HWSIM_ATTR_SIGNAL, %HWSIM_ATTR_COOKIE, %HWSIM_ATTR_FREQ (optional)
 * @HWSIM_CMD_TX_INFO_FRAME: Transmission info report from user space to
 *	kernel, uses:
 *	%HWSIM_ATTR_ADDR_TRANSMITTER, %HWSIM_ATTR_FLAGS,
 *	%HWSIM_ATTR_TX_INFO, %WSIM_ATTR_TX_INFO_FLAGS,
 *	%HWSIM_ATTR_SIGNAL, %HWSIM_ATTR_COOKIE
 * @HWSIM_CMD_NEW_RADIO: create a new radio with the given parameters,
 *	वापसs the radio ID (>= 0) or negative on errors, अगर successful
 *	then multicast the result, uses optional parameter:
 *	%HWSIM_ATTR_REG_STRICT_REG, %HWSIM_ATTR_SUPPORT_P2P_DEVICE,
 *	%HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE, %HWSIM_ATTR_CHANNELS,
 *	%HWSIM_ATTR_NO_VIF, %HWSIM_ATTR_RADIO_NAME, %HWSIM_ATTR_USE_CHANCTX,
 *	%HWSIM_ATTR_REG_HINT_ALPHA2, %HWSIM_ATTR_REG_CUSTOM_REG,
 *	%HWSIM_ATTR_PERM_ADDR
 * @HWSIM_CMD_DEL_RADIO: destroy a radio, reply is multicasted
 * @HWSIM_CMD_GET_RADIO: fetch inक्रमmation about existing radios, uses:
 *	%HWSIM_ATTR_RADIO_ID
 * @HWSIM_CMD_ADD_MAC_ADDR: add a receive MAC address (given in the
 *	%HWSIM_ATTR_ADDR_RECEIVER attribute) to a device identअगरied by
 *	%HWSIM_ATTR_ADDR_TRANSMITTER. This lets wmediumd क्रमward frames
 *	to this receiver address क्रम a given station.
 * @HWSIM_CMD_DEL_MAC_ADDR: हटाओ the MAC address again, the attributes
 *	are the same as to @HWSIM_CMD_ADD_MAC_ADDR.
 * @__HWSIM_CMD_MAX: क्रमागत limit
 */
क्रमागत अणु
	HWSIM_CMD_UNSPEC,
	HWSIM_CMD_REGISTER,
	HWSIM_CMD_FRAME,
	HWSIM_CMD_TX_INFO_FRAME,
	HWSIM_CMD_NEW_RADIO,
	HWSIM_CMD_DEL_RADIO,
	HWSIM_CMD_GET_RADIO,
	HWSIM_CMD_ADD_MAC_ADDR,
	HWSIM_CMD_DEL_MAC_ADDR,
	__HWSIM_CMD_MAX,
पूर्ण;
#घोषणा HWSIM_CMD_MAX (_HWSIM_CMD_MAX - 1)

#घोषणा HWSIM_CMD_CREATE_RADIO   HWSIM_CMD_NEW_RADIO
#घोषणा HWSIM_CMD_DESTROY_RADIO  HWSIM_CMD_DEL_RADIO

/**
 * क्रमागत hwsim_attrs - hwsim netlink attributes
 *
 * @HWSIM_ATTR_UNSPEC: unspecअगरied attribute to catch errors
 *
 * @HWSIM_ATTR_ADDR_RECEIVER: MAC address of the radio device that
 *	the frame is broadcasted to
 * @HWSIM_ATTR_ADDR_TRANSMITTER: MAC address of the radio device that
 *	the frame was broadcasted from
 * @HWSIM_ATTR_FRAME: Data array
 * @HWSIM_ATTR_FLAGS: mac80211 transmission flags, used to process
	properly the frame at user space
 * @HWSIM_ATTR_RX_RATE: estimated rx rate index क्रम this frame at user
	space
 * @HWSIM_ATTR_SIGNAL: estimated RX संकेत क्रम this frame at user
	space
 * @HWSIM_ATTR_TX_INFO: ieee80211_tx_rate array
 * @HWSIM_ATTR_COOKIE: sk_buff cookie to identअगरy the frame
 * @HWSIM_ATTR_CHANNELS: u32 attribute used with the %HWSIM_CMD_CREATE_RADIO
 *	command giving the number of channels supported by the new radio
 * @HWSIM_ATTR_RADIO_ID: u32 attribute used with %HWSIM_CMD_DESTROY_RADIO
 *	only to destroy a radio
 * @HWSIM_ATTR_REG_HINT_ALPHA2: alpha2 क्रम regulatoro driver hपूर्णांक
 *	(nla string, length 2)
 * @HWSIM_ATTR_REG_CUSTOM_REG: custom regulatory करोमुख्य index (u32 attribute)
 * @HWSIM_ATTR_REG_STRICT_REG: request REGULATORY_STRICT_REG (flag attribute)
 * @HWSIM_ATTR_SUPPORT_P2P_DEVICE: support P2P Device भव पूर्णांकerface (flag)
 * @HWSIM_ATTR_USE_CHANCTX: used with the %HWSIM_CMD_CREATE_RADIO
 *	command to क्रमce use of channel contexts even when only a
 *	single channel is supported
 * @HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE: used with the %HWSIM_CMD_CREATE_RADIO
 *	command to क्रमce radio removal when process that created the radio dies
 * @HWSIM_ATTR_RADIO_NAME: Name of radio, e.g. phy666
 * @HWSIM_ATTR_NO_VIF:  Do not create vअगर (wlanX) when creating radio.
 * @HWSIM_ATTR_FREQ: Frequency at which packet is transmitted or received.
 * @HWSIM_ATTR_TX_INFO_FLAGS: additional flags क्रम corresponding
 *	rates of %HWSIM_ATTR_TX_INFO
 * @HWSIM_ATTR_PERM_ADDR: permanent mac address of new radio
 * @HWSIM_ATTR_IFTYPE_SUPPORT: u32 attribute of supported पूर्णांकerface types bits
 * @HWSIM_ATTR_CIPHER_SUPPORT: u32 array of supported cipher types
 * @__HWSIM_ATTR_MAX: क्रमागत limit
 */


क्रमागत अणु
	HWSIM_ATTR_UNSPEC,
	HWSIM_ATTR_ADDR_RECEIVER,
	HWSIM_ATTR_ADDR_TRANSMITTER,
	HWSIM_ATTR_FRAME,
	HWSIM_ATTR_FLAGS,
	HWSIM_ATTR_RX_RATE,
	HWSIM_ATTR_SIGNAL,
	HWSIM_ATTR_TX_INFO,
	HWSIM_ATTR_COOKIE,
	HWSIM_ATTR_CHANNELS,
	HWSIM_ATTR_RADIO_ID,
	HWSIM_ATTR_REG_HINT_ALPHA2,
	HWSIM_ATTR_REG_CUSTOM_REG,
	HWSIM_ATTR_REG_STRICT_REG,
	HWSIM_ATTR_SUPPORT_P2P_DEVICE,
	HWSIM_ATTR_USE_CHANCTX,
	HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE,
	HWSIM_ATTR_RADIO_NAME,
	HWSIM_ATTR_NO_VIF,
	HWSIM_ATTR_FREQ,
	HWSIM_ATTR_PAD,
	HWSIM_ATTR_TX_INFO_FLAGS,
	HWSIM_ATTR_PERM_ADDR,
	HWSIM_ATTR_IFTYPE_SUPPORT,
	HWSIM_ATTR_CIPHER_SUPPORT,
	__HWSIM_ATTR_MAX,
पूर्ण;
#घोषणा HWSIM_ATTR_MAX (__HWSIM_ATTR_MAX - 1)

/**
 * काष्ठा hwsim_tx_rate - rate selection/status
 *
 * @idx: rate index to attempt to send with
 * @count: number of tries in this rate beक्रमe going to the next rate
 *
 * A value of -1 क्रम @idx indicates an invalid rate and, अगर used
 * in an array of retry rates, that no more rates should be tried.
 *
 * When used क्रम transmit status reporting, the driver should
 * always report the rate and number of retries used.
 *
 */
काष्ठा hwsim_tx_rate अणु
	s8 idx;
	u8 count;
पूर्ण __packed;

/**
 * क्रमागत hwsim_tx_rate_flags - per-rate flags set by the rate control algorithm.
 *	Inspired by काष्ठाure mac80211_rate_control_flags. New flags may be
 *	appended, but old flags not deleted, to keep compatibility क्रम
 *	userspace.
 *
 * These flags are set by the Rate control algorithm क्रम each rate during tx,
 * in the @flags member of काष्ठा ieee80211_tx_rate.
 *
 * @MAC80211_HWSIM_TX_RC_USE_RTS_CTS: Use RTS/CTS exchange क्रम this rate.
 * @MAC80211_HWSIM_TX_RC_USE_CTS_PROTECT: CTS-to-self protection is required.
 *	This is set अगर the current BSS requires ERP protection.
 * @MAC80211_HWSIM_TX_RC_USE_SHORT_PREAMBLE: Use लघु preamble.
 * @MAC80211_HWSIM_TX_RC_MCS: HT rate.
 * @MAC80211_HWSIM_TX_RC_VHT_MCS: VHT MCS rate, in this हाल the idx field is
 *	split पूर्णांकo a higher 4 bits (Nss) and lower 4 bits (MCS number)
 * @MAC80211_HWSIM_TX_RC_GREEN_FIELD: Indicates whether this rate should be used
 *	in Greenfield mode.
 * @MAC80211_HWSIM_TX_RC_40_MHZ_WIDTH: Indicates अगर the Channel Width should be
 *	40 MHz.
 * @MAC80211_HWSIM_TX_RC_80_MHZ_WIDTH: Indicates 80 MHz transmission
 * @MAC80211_HWSIM_TX_RC_160_MHZ_WIDTH: Indicates 160 MHz transmission
 *	(80+80 isn't supported yet)
 * @MAC80211_HWSIM_TX_RC_DUP_DATA: The frame should be transmitted on both of
 *	the adjacent 20 MHz channels, अगर the current channel type is
 *	NL80211_CHAN_HT40MINUS or NL80211_CHAN_HT40PLUS.
 * @MAC80211_HWSIM_TX_RC_SHORT_GI: Short Guard पूर्णांकerval should be used क्रम this
 *	rate.
 */
क्रमागत hwsim_tx_rate_flags अणु
	MAC80211_HWSIM_TX_RC_USE_RTS_CTS		= BIT(0),
	MAC80211_HWSIM_TX_RC_USE_CTS_PROTECT		= BIT(1),
	MAC80211_HWSIM_TX_RC_USE_SHORT_PREAMBLE	= BIT(2),

	/* rate index is an HT/VHT MCS instead of an index */
	MAC80211_HWSIM_TX_RC_MCS			= BIT(3),
	MAC80211_HWSIM_TX_RC_GREEN_FIELD		= BIT(4),
	MAC80211_HWSIM_TX_RC_40_MHZ_WIDTH		= BIT(5),
	MAC80211_HWSIM_TX_RC_DUP_DATA		= BIT(6),
	MAC80211_HWSIM_TX_RC_SHORT_GI		= BIT(7),
	MAC80211_HWSIM_TX_RC_VHT_MCS			= BIT(8),
	MAC80211_HWSIM_TX_RC_80_MHZ_WIDTH		= BIT(9),
	MAC80211_HWSIM_TX_RC_160_MHZ_WIDTH		= BIT(10),
पूर्ण;

/**
 * काष्ठा hwsim_tx_rate - rate selection/status
 *
 * @idx: rate index to attempt to send with
 * @count: number of tries in this rate beक्रमe going to the next rate
 *
 * A value of -1 क्रम @idx indicates an invalid rate and, अगर used
 * in an array of retry rates, that no more rates should be tried.
 *
 * When used क्रम transmit status reporting, the driver should
 * always report the rate and number of retries used.
 *
 */
काष्ठा hwsim_tx_rate_flag अणु
	s8 idx;
	u16 flags;
पूर्ण __packed;

/**
 * DOC: Frame transmission support over virtio
 *
 * Frame transmission is also supported over virtio to allow communication
 * with बाह्यal entities.
 */

/**
 * क्रमागत hwsim_vqs - queues क्रम virtio frame transmission
 *
 * @HWSIM_VQ_TX: send frames to बाह्यal entity
 * @HWSIM_VQ_RX: receive frames and transmission info reports
 * @HWSIM_NUM_VQS: क्रमागत limit
 */
क्रमागत अणु
	HWSIM_VQ_TX,
	HWSIM_VQ_RX,
	HWSIM_NUM_VQS,
पूर्ण;
#पूर्ण_अगर /* __MAC80211_HWSIM_H */
