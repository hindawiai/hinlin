<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ethtool.h: Defines क्रम Linux ethtool.
 *
 * Copyright (C) 1998 David S. Miller (davem@redhat.com)
 * Copyright 2001 Jeff Garzik <jgarzik@pobox.com>
 * Portions Copyright 2001 Sun Microप्रणालीs (thockin@sun.com)
 * Portions Copyright 2002 Intel (eli.kupermann@पूर्णांकel.com,
 *                                christopher.leech@पूर्णांकel.com,
 *                                scott.feldman@पूर्णांकel.com)
 * Portions Copyright (C) Sun Microप्रणालीs 2008
 */
#अगर_अघोषित _LINUX_ETHTOOL_H
#घोषणा _LINUX_ETHTOOL_H

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/compat.h>
#समावेश <uapi/linux/ethtool.h>

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_ethtool_rx_flow_spec अणु
	u32		flow_type;
	जोड़ ethtool_flow_जोड़ h_u;
	काष्ठा ethtool_flow_ext h_ext;
	जोड़ ethtool_flow_जोड़ m_u;
	काष्ठा ethtool_flow_ext m_ext;
	compat_u64	ring_cookie;
	u32		location;
पूर्ण;

काष्ठा compat_ethtool_rxnfc अणु
	u32				cmd;
	u32				flow_type;
	compat_u64			data;
	काष्ठा compat_ethtool_rx_flow_spec fs;
	u32				rule_cnt;
	u32				rule_locs[];
पूर्ण;

#पूर्ण_अगर /* CONFIG_COMPAT */

#समावेश <linux/rculist.h>

/**
 * क्रमागत ethtool_phys_id_state - indicator state क्रम physical identअगरication
 * @ETHTOOL_ID_INACTIVE: Physical ID indicator should be deactivated
 * @ETHTOOL_ID_ACTIVE: Physical ID indicator should be activated
 * @ETHTOOL_ID_ON: LED should be turned on (used अगरf %ETHTOOL_ID_ACTIVE
 *	is not supported)
 * @ETHTOOL_ID_OFF: LED should be turned off (used अगरf %ETHTOOL_ID_ACTIVE
 *	is not supported)
 */
क्रमागत ethtool_phys_id_state अणु
	ETHTOOL_ID_INACTIVE,
	ETHTOOL_ID_ACTIVE,
	ETHTOOL_ID_ON,
	ETHTOOL_ID_OFF
पूर्ण;

क्रमागत अणु
	ETH_RSS_HASH_TOP_BIT, /* Configurable RSS hash function - Toeplitz */
	ETH_RSS_HASH_XOR_BIT, /* Configurable RSS hash function - Xor */
	ETH_RSS_HASH_CRC32_BIT, /* Configurable RSS hash function - Crc32 */

	/*
	 * Add your fresh new hash function bits above and remember to update
	 * rss_hash_func_strings[] in ethtool.c
	 */
	ETH_RSS_HASH_FUNCS_COUNT
पूर्ण;

#घोषणा __ETH_RSS_HASH_BIT(bit)	((u32)1 << (bit))
#घोषणा __ETH_RSS_HASH(name)	__ETH_RSS_HASH_BIT(ETH_RSS_HASH_##name##_BIT)

#घोषणा ETH_RSS_HASH_TOP	__ETH_RSS_HASH(TOP)
#घोषणा ETH_RSS_HASH_XOR	__ETH_RSS_HASH(XOR)
#घोषणा ETH_RSS_HASH_CRC32	__ETH_RSS_HASH(CRC32)

#घोषणा ETH_RSS_HASH_UNKNOWN	0
#घोषणा ETH_RSS_HASH_NO_CHANGE	0

काष्ठा net_device;
काष्ठा netlink_ext_ack;

/* Some generic methods drivers may use in their ethtool_ops */
u32 ethtool_op_get_link(काष्ठा net_device *dev);
पूर्णांक ethtool_op_get_ts_info(काष्ठा net_device *dev, काष्ठा ethtool_ts_info *eti);


/* Link extended state and substate. */
काष्ठा ethtool_link_ext_state_info अणु
	क्रमागत ethtool_link_ext_state link_ext_state;
	जोड़ अणु
		क्रमागत ethtool_link_ext_substate_स्वतःneg स्वतःneg;
		क्रमागत ethtool_link_ext_substate_link_training link_training;
		क्रमागत ethtool_link_ext_substate_link_logical_mismatch link_logical_mismatch;
		क्रमागत ethtool_link_ext_substate_bad_संकेत_पूर्णांकegrity bad_संकेत_पूर्णांकegrity;
		क्रमागत ethtool_link_ext_substate_cable_issue cable_issue;
		u8 __link_ext_substate;
	पूर्ण;
पूर्ण;

/**
 * ethtool_rxfh_indir_शेष - get शेष value क्रम RX flow hash indirection
 * @index: Index in RX flow hash indirection table
 * @n_rx_rings: Number of RX rings to use
 *
 * This function provides the शेष policy क्रम RX flow hash indirection.
 */
अटल अंतरभूत u32 ethtool_rxfh_indir_शेष(u32 index, u32 n_rx_rings)
अणु
	वापस index % n_rx_rings;
पूर्ण

/* declare a link mode biपंचांगap */
#घोषणा __ETHTOOL_DECLARE_LINK_MODE_MASK(name)		\
	DECLARE_BITMAP(name, __ETHTOOL_LINK_MODE_MASK_NBITS)

/* drivers must ignore base.cmd and base.link_mode_masks_nwords
 * fields, but they are allowed to overग_लिखो them (will be ignored).
 */
काष्ठा ethtool_link_ksettings अणु
	काष्ठा ethtool_link_settings base;
	काष्ठा अणु
		__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
		__ETHTOOL_DECLARE_LINK_MODE_MASK(advertising);
		__ETHTOOL_DECLARE_LINK_MODE_MASK(lp_advertising);
	पूर्ण link_modes;
	u32	lanes;
पूर्ण;

/**
 * ethtool_link_ksettings_zero_link_mode - clear link_ksettings link mode mask
 *   @ptr : poपूर्णांकer to काष्ठा ethtool_link_ksettings
 *   @name : one of supported/advertising/lp_advertising
 */
#घोषणा ethtool_link_ksettings_zero_link_mode(ptr, name)		\
	biपंचांगap_zero((ptr)->link_modes.name, __ETHTOOL_LINK_MODE_MASK_NBITS)

/**
 * ethtool_link_ksettings_add_link_mode - set bit in link_ksettings
 * link mode mask
 *   @ptr : poपूर्णांकer to काष्ठा ethtool_link_ksettings
 *   @name : one of supported/advertising/lp_advertising
 *   @mode : one of the ETHTOOL_LINK_MODE_*_BIT
 * (not atomic, no bound checking)
 */
#घोषणा ethtool_link_ksettings_add_link_mode(ptr, name, mode)		\
	__set_bit(ETHTOOL_LINK_MODE_ ## mode ## _BIT, (ptr)->link_modes.name)

/**
 * ethtool_link_ksettings_del_link_mode - clear bit in link_ksettings
 * link mode mask
 *   @ptr : poपूर्णांकer to काष्ठा ethtool_link_ksettings
 *   @name : one of supported/advertising/lp_advertising
 *   @mode : one of the ETHTOOL_LINK_MODE_*_BIT
 * (not atomic, no bound checking)
 */
#घोषणा ethtool_link_ksettings_del_link_mode(ptr, name, mode)		\
	__clear_bit(ETHTOOL_LINK_MODE_ ## mode ## _BIT, (ptr)->link_modes.name)

/**
 * ethtool_link_ksettings_test_link_mode - test bit in ksettings link mode mask
 *   @ptr : poपूर्णांकer to काष्ठा ethtool_link_ksettings
 *   @name : one of supported/advertising/lp_advertising
 *   @mode : one of the ETHTOOL_LINK_MODE_*_BIT
 * (not atomic, no bound checking)
 *
 * Returns true/false.
 */
#घोषणा ethtool_link_ksettings_test_link_mode(ptr, name, mode)		\
	test_bit(ETHTOOL_LINK_MODE_ ## mode ## _BIT, (ptr)->link_modes.name)

बाह्य पूर्णांक
__ethtool_get_link_ksettings(काष्ठा net_device *dev,
			     काष्ठा ethtool_link_ksettings *link_ksettings);

/**
 * ethtool_पूर्णांकersect_link_masks - Given two link masks, AND them together
 * @dst: first mask and where result is stored
 * @src: second mask to पूर्णांकersect with
 *
 * Given two link mode masks, AND them together and save the result in dst.
 */
व्योम ethtool_पूर्णांकersect_link_masks(काष्ठा ethtool_link_ksettings *dst,
				  काष्ठा ethtool_link_ksettings *src);

व्योम ethtool_convert_legacy_u32_to_link_mode(अचिन्हित दीर्घ *dst,
					     u32 legacy_u32);

/* वापस false अगर src had higher bits set. lower bits always updated. */
bool ethtool_convert_link_mode_to_legacy_u32(u32 *legacy_u32,
				     स्थिर अचिन्हित दीर्घ *src);

#घोषणा ETHTOOL_COALESCE_RX_USECS		BIT(0)
#घोषणा ETHTOOL_COALESCE_RX_MAX_FRAMES		BIT(1)
#घोषणा ETHTOOL_COALESCE_RX_USECS_IRQ		BIT(2)
#घोषणा ETHTOOL_COALESCE_RX_MAX_FRAMES_IRQ	BIT(3)
#घोषणा ETHTOOL_COALESCE_TX_USECS		BIT(4)
#घोषणा ETHTOOL_COALESCE_TX_MAX_FRAMES		BIT(5)
#घोषणा ETHTOOL_COALESCE_TX_USECS_IRQ		BIT(6)
#घोषणा ETHTOOL_COALESCE_TX_MAX_FRAMES_IRQ	BIT(7)
#घोषणा ETHTOOL_COALESCE_STATS_BLOCK_USECS	BIT(8)
#घोषणा ETHTOOL_COALESCE_USE_ADAPTIVE_RX	BIT(9)
#घोषणा ETHTOOL_COALESCE_USE_ADAPTIVE_TX	BIT(10)
#घोषणा ETHTOOL_COALESCE_PKT_RATE_LOW		BIT(11)
#घोषणा ETHTOOL_COALESCE_RX_USECS_LOW		BIT(12)
#घोषणा ETHTOOL_COALESCE_RX_MAX_FRAMES_LOW	BIT(13)
#घोषणा ETHTOOL_COALESCE_TX_USECS_LOW		BIT(14)
#घोषणा ETHTOOL_COALESCE_TX_MAX_FRAMES_LOW	BIT(15)
#घोषणा ETHTOOL_COALESCE_PKT_RATE_HIGH		BIT(16)
#घोषणा ETHTOOL_COALESCE_RX_USECS_HIGH		BIT(17)
#घोषणा ETHTOOL_COALESCE_RX_MAX_FRAMES_HIGH	BIT(18)
#घोषणा ETHTOOL_COALESCE_TX_USECS_HIGH		BIT(19)
#घोषणा ETHTOOL_COALESCE_TX_MAX_FRAMES_HIGH	BIT(20)
#घोषणा ETHTOOL_COALESCE_RATE_SAMPLE_INTERVAL	BIT(21)
#घोषणा ETHTOOL_COALESCE_ALL_PARAMS		GENMASK(21, 0)

#घोषणा ETHTOOL_COALESCE_USECS						\
	(ETHTOOL_COALESCE_RX_USECS | ETHTOOL_COALESCE_TX_USECS)
#घोषणा ETHTOOL_COALESCE_MAX_FRAMES					\
	(ETHTOOL_COALESCE_RX_MAX_FRAMES | ETHTOOL_COALESCE_TX_MAX_FRAMES)
#घोषणा ETHTOOL_COALESCE_USECS_IRQ					\
	(ETHTOOL_COALESCE_RX_USECS_IRQ | ETHTOOL_COALESCE_TX_USECS_IRQ)
#घोषणा ETHTOOL_COALESCE_MAX_FRAMES_IRQ		\
	(ETHTOOL_COALESCE_RX_MAX_FRAMES_IRQ |	\
	 ETHTOOL_COALESCE_TX_MAX_FRAMES_IRQ)
#घोषणा ETHTOOL_COALESCE_USE_ADAPTIVE					\
	(ETHTOOL_COALESCE_USE_ADAPTIVE_RX | ETHTOOL_COALESCE_USE_ADAPTIVE_TX)
#घोषणा ETHTOOL_COALESCE_USECS_LOW_HIGH					\
	(ETHTOOL_COALESCE_RX_USECS_LOW | ETHTOOL_COALESCE_TX_USECS_LOW | \
	 ETHTOOL_COALESCE_RX_USECS_HIGH | ETHTOOL_COALESCE_TX_USECS_HIGH)
#घोषणा ETHTOOL_COALESCE_MAX_FRAMES_LOW_HIGH	\
	(ETHTOOL_COALESCE_RX_MAX_FRAMES_LOW |	\
	 ETHTOOL_COALESCE_TX_MAX_FRAMES_LOW |	\
	 ETHTOOL_COALESCE_RX_MAX_FRAMES_HIGH |	\
	 ETHTOOL_COALESCE_TX_MAX_FRAMES_HIGH)
#घोषणा ETHTOOL_COALESCE_PKT_RATE_RX_USECS				\
	(ETHTOOL_COALESCE_USE_ADAPTIVE_RX |				\
	 ETHTOOL_COALESCE_RX_USECS_LOW | ETHTOOL_COALESCE_RX_USECS_HIGH | \
	 ETHTOOL_COALESCE_PKT_RATE_LOW | ETHTOOL_COALESCE_PKT_RATE_HIGH | \
	 ETHTOOL_COALESCE_RATE_SAMPLE_INTERVAL)

#घोषणा ETHTOOL_STAT_NOT_SET	(~0ULL)

अटल अंतरभूत व्योम ethtool_stats_init(u64 *stats, अचिन्हित पूर्णांक n)
अणु
	जबतक (n--)
		stats[n] = ETHTOOL_STAT_NOT_SET;
पूर्ण

/* Basic IEEE 802.3 MAC statistics (30.3.1.1.*), not otherwise exposed
 * via a more targeted API.
 */
काष्ठा ethtool_eth_mac_stats अणु
	u64 FramesTransmittedOK;
	u64 SingleCollisionFrames;
	u64 MultipleCollisionFrames;
	u64 FramesReceivedOK;
	u64 FrameCheckSequenceErrors;
	u64 AlignmentErrors;
	u64 OctetsTransmittedOK;
	u64 FramesWithDeferredXmissions;
	u64 LateCollisions;
	u64 FramesAbortedDueToXSColls;
	u64 FramesLostDueToIntMACXmitError;
	u64 CarrierSenseErrors;
	u64 OctetsReceivedOK;
	u64 FramesLostDueToIntMACRcvError;
	u64 MulticastFramesXmittedOK;
	u64 BroadcastFramesXmittedOK;
	u64 FramesWithExcessiveDeferral;
	u64 MulticastFramesReceivedOK;
	u64 BroadcastFramesReceivedOK;
	u64 InRangeLengthErrors;
	u64 OutOfRangeLengthField;
	u64 FrameTooLongErrors;
पूर्ण;

/* Basic IEEE 802.3 PHY statistics (30.3.2.1.*), not otherwise exposed
 * via a more targeted API.
 */
काष्ठा ethtool_eth_phy_stats अणु
	u64 SymbolErrorDuringCarrier;
पूर्ण;

/* Basic IEEE 802.3 MAC Ctrl statistics (30.3.3.*), not otherwise exposed
 * via a more targeted API.
 */
काष्ठा ethtool_eth_ctrl_stats अणु
	u64 MACControlFramesTransmitted;
	u64 MACControlFramesReceived;
	u64 UnsupportedOpcodesReceived;
पूर्ण;

/**
 * काष्ठा ethtool_छोड़ो_stats - statistics क्रम IEEE 802.3x छोड़ो frames
 * @tx_छोड़ो_frames: transmitted छोड़ो frame count. Reported to user space
 *	as %ETHTOOL_A_PAUSE_STAT_TX_FRAMES.
 *
 *	Equivalent to `30.3.4.2 aPAUSEMACCtrlFramesTransmitted`
 *	from the standard.
 *
 * @rx_छोड़ो_frames: received छोड़ो frame count. Reported to user space
 *	as %ETHTOOL_A_PAUSE_STAT_RX_FRAMES. Equivalent to:
 *
 *	Equivalent to `30.3.4.3 aPAUSEMACCtrlFramesReceived`
 *	from the standard.
 */
काष्ठा ethtool_छोड़ो_stats अणु
	u64 tx_छोड़ो_frames;
	u64 rx_छोड़ो_frames;
पूर्ण;

#घोषणा ETHTOOL_MAX_LANES	8

/**
 * काष्ठा ethtool_fec_stats - statistics क्रम IEEE 802.3 FEC
 * @corrected_blocks: number of received blocks corrected by FEC
 *	Reported to user space as %ETHTOOL_A_FEC_STAT_CORRECTED.
 *
 *	Equivalent to `30.5.1.1.17 aFECCorrectedBlocks` from the standard.
 *
 * @uncorrectable_blocks: number of received blocks FEC was not able to correct
 *	Reported to user space as %ETHTOOL_A_FEC_STAT_UNCORR.
 *
 *	Equivalent to `30.5.1.1.18 aFECUncorrectableBlocks` from the standard.
 *
 * @corrected_bits: number of bits corrected by FEC
 *	Similar to @corrected_blocks but counts inभागidual bit changes,
 *	not entire FEC data blocks. This is a non-standard statistic.
 *	Reported to user space as %ETHTOOL_A_FEC_STAT_CORR_BITS.
 *
 * @lane: per-lane/PCS-instance counts as defined by the standard
 * @total: error counts क्रम the entire port, क्रम drivers incapable of reporting
 *	per-lane stats
 *
 * Drivers should fill in either only total or per-lane statistics, core
 * will take care of adding lane values up to produce the total.
 */
काष्ठा ethtool_fec_stats अणु
	काष्ठा ethtool_fec_stat अणु
		u64 total;
		u64 lanes[ETHTOOL_MAX_LANES];
	पूर्ण corrected_blocks, uncorrectable_blocks, corrected_bits;
पूर्ण;

/**
 * काष्ठा ethtool_rmon_hist_range - byte range क्रम histogram statistics
 * @low: low bound of the bucket (inclusive)
 * @high: high bound of the bucket (inclusive)
 */
काष्ठा ethtool_rmon_hist_range अणु
	u16 low;
	u16 high;
पूर्ण;

#घोषणा ETHTOOL_RMON_HIST_MAX	10

/**
 * काष्ठा ethtool_rmon_stats - selected RMON (RFC 2819) statistics
 * @undersize_pkts: Equivalent to `etherStatsUndersizePkts` from the RFC.
 * @oversize_pkts: Equivalent to `etherStatsOversizePkts` from the RFC.
 * @fragments: Equivalent to `etherStatsFragments` from the RFC.
 * @jabbers: Equivalent to `etherStatsJabbers` from the RFC.
 * @hist: Packet counter क्रम packet length buckets (e.g.
 *	`etherStatsPkts128to255Octets` from the RFC).
 * @hist_tx: Tx counters in similar क्रमm to @hist, not defined in the RFC.
 *
 * Selection of RMON (RFC 2819) statistics which are not exposed via dअगरferent
 * APIs, primarily the packet-length-based counters.
 * Unक्रमtunately dअगरferent designs choose dअगरferent buckets beyond
 * the 1024B mark (jumbo frame teritory), so the definition of the bucket
 * ranges is left to the driver.
 */
काष्ठा ethtool_rmon_stats अणु
	u64 undersize_pkts;
	u64 oversize_pkts;
	u64 fragments;
	u64 jabbers;

	u64 hist[ETHTOOL_RMON_HIST_MAX];
	u64 hist_tx[ETHTOOL_RMON_HIST_MAX];
पूर्ण;

#घोषणा ETH_MODULE_EEPROM_PAGE_LEN	128
#घोषणा ETH_MODULE_MAX_I2C_ADDRESS	0x7f

/**
 * काष्ठा ethtool_module_eeprom - EEPROM dump from specअगरied page
 * @offset: Offset within the specअगरied EEPROM page to begin पढ़ो, in bytes.
 * @length: Number of bytes to पढ़ो.
 * @page: Page number to पढ़ो from.
 * @bank: Page bank number to पढ़ो from, अगर applicable by EEPROM spec.
 * @i2c_address: I2C address of a page. Value less than 0x7f expected. Most
 *	EEPROMs use 0x50 or 0x51.
 * @data: Poपूर्णांकer to buffer with EEPROM data of @length size.
 *
 * This can be used to manage pages during EEPROM dump in ethtool and pass
 * required inक्रमmation to the driver.
 */
काष्ठा ethtool_module_eeprom अणु
	__u32	offset;
	__u32	length;
	__u8	page;
	__u8	bank;
	__u8	i2c_address;
	__u8	*data;
पूर्ण;

/**
 * काष्ठा ethtool_ops - optional netdev operations
 * @cap_link_lanes_supported: indicates अगर the driver supports lanes
 *	parameter.
 * @supported_coalesce_params: supported types of पूर्णांकerrupt coalescing.
 * @get_drvinfo: Report driver/device inक्रमmation.  Should only set the
 *	@driver, @version, @fw_version and @bus_info fields.  If not
 *	implemented, the @driver and @bus_info fields will be filled in
 *	according to the netdev's parent device.
 * @get_regs_len: Get buffer length required क्रम @get_regs
 * @get_regs: Get device रेजिस्टरs
 * @get_wol: Report whether Wake-on-Lan is enabled
 * @set_wol: Turn Wake-on-Lan on or off.  Returns a negative error code
 *	or zero.
 * @get_msglevel: Report driver message level.  This should be the value
 *	of the @msg_enable field used by netअगर logging functions.
 * @set_msglevel: Set driver message level
 * @nway_reset: Restart स्वतःnegotiation.  Returns a negative error code
 *	or zero.
 * @get_link: Report whether physical link is up.  Will only be called अगर
 *	the netdev is up.  Should usually be set to ethtool_op_get_link(),
 *	which uses netअगर_carrier_ok().
 * @get_link_ext_state: Report link extended state. Should set link_ext_state and
 *	link_ext_substate (link_ext_substate of 0 means link_ext_substate is unknown,
 *	करो not attach ext_substate attribute to netlink message). If link_ext_state
 *	and link_ext_substate are unknown, वापस -ENODATA. If not implemented,
 *	link_ext_state and link_ext_substate will not be sent to userspace.
 * @get_eeprom_len: Read range of EEPROM addresses क्रम validation of
 *	@get_eeprom and @set_eeprom requests.
 *	Returns 0 अगर device करोes not support EEPROM access.
 * @get_eeprom: Read data from the device EEPROM.
 *	Should fill in the magic field.  Don't need to check len क्रम zero
 *	or wraparound.  Fill in the data argument with the eeprom values
 *	from offset to offset + len.  Update len to the amount पढ़ो.
 *	Returns an error or zero.
 * @set_eeprom: Write data to the device EEPROM.
 *	Should validate the magic field.  Don't need to check len क्रम zero
 *	or wraparound.  Update len to the amount written.  Returns an error
 *	or zero.
 * @get_coalesce: Get पूर्णांकerrupt coalescing parameters.  Returns a negative
 *	error code or zero.
 * @set_coalesce: Set पूर्णांकerrupt coalescing parameters.  Supported coalescing
 *	types should be set in @supported_coalesce_params.
 *	Returns a negative error code or zero.
 * @get_ringparam: Report ring sizes
 * @set_ringparam: Set ring sizes.  Returns a negative error code or zero.
 * @get_छोड़ो_stats: Report छोड़ो frame statistics. Drivers must not zero
 *	statistics which they करोn't report. The stats काष्ठाure is initialized
 *	to ETHTOOL_STAT_NOT_SET indicating driver करोes not report statistics.
 * @get_छोड़ोparam: Report छोड़ो parameters
 * @set_छोड़ोparam: Set छोड़ो parameters.  Returns a negative error code
 *	or zero.
 * @self_test: Run specअगरied self-tests
 * @get_strings: Return a set of strings that describe the requested objects
 * @set_phys_id: Identअगरy the physical devices, e.g. by flashing an LED
 *	attached to it.  The implementation may update the indicator
 *	asynchronously or synchronously, but in either हाल it must वापस
 *	quickly.  It is initially called with the argument %ETHTOOL_ID_ACTIVE,
 *	and must either activate asynchronous updates and वापस zero, वापस
 *	a negative error or वापस a positive frequency क्रम synchronous
 *	indication (e.g. 1 क्रम one on/off cycle per second).  If it वापसs
 *	a frequency then it will be called again at पूर्णांकervals with the
 *	argument %ETHTOOL_ID_ON or %ETHTOOL_ID_OFF and should set the state of
 *	the indicator accordingly.  Finally, it is called with the argument
 *	%ETHTOOL_ID_INACTIVE and must deactivate the indicator.  Returns a
 *	negative error code or zero.
 * @get_ethtool_stats: Return extended statistics about the device.
 *	This is only useful अगर the device मुख्यtains statistics not
 *	included in &काष्ठा rtnl_link_stats64.
 * @begin: Function to be called beक्रमe any other operation.  Returns a
 *	negative error code or zero.
 * @complete: Function to be called after any other operation except
 *	@begin.  Will be called even अगर the other operation failed.
 * @get_priv_flags: Report driver-specअगरic feature flags.
 * @set_priv_flags: Set driver-specअगरic feature flags.  Returns a negative
 *	error code or zero.
 * @get_sset_count: Get number of strings that @get_strings will ग_लिखो.
 * @get_rxnfc: Get RX flow classअगरication rules.  Returns a negative
 *	error code or zero.
 * @set_rxnfc: Set RX flow classअगरication rules.  Returns a negative
 *	error code or zero.
 * @flash_device: Write a firmware image to device's flash memory.
 *	Returns a negative error code or zero.
 * @reset: Reset (part of) the device, as specअगरied by a biपंचांगask of
 *	flags from &क्रमागत ethtool_reset_flags.  Returns a negative
 *	error code or zero.
 * @get_rxfh_key_size: Get the size of the RX flow hash key.
 *	Returns zero अगर not supported क्रम this specअगरic device.
 * @get_rxfh_indir_size: Get the size of the RX flow hash indirection table.
 *	Returns zero अगर not supported क्रम this specअगरic device.
 * @get_rxfh: Get the contents of the RX flow hash indirection table, hash key
 *	and/or hash function.
 *	Returns a negative error code or zero.
 * @set_rxfh: Set the contents of the RX flow hash indirection table, hash
 *	key, and/or hash function.  Arguments which are set to %शून्य or zero
 *	will reमुख्य unchanged.
 *	Returns a negative error code or zero. An error code must be वापसed
 *	अगर at least one unsupported change was requested.
 * @get_rxfh_context: Get the contents of the RX flow hash indirection table,
 *	hash key, and/or hash function assiciated to the given rss context.
 *	Returns a negative error code or zero.
 * @set_rxfh_context: Create, हटाओ and configure RSS contexts. Allows setting
 *	the contents of the RX flow hash indirection table, hash key, and/or
 *	hash function associated to the given context. Arguments which are set
 *	to %शून्य or zero will reमुख्य unchanged.
 *	Returns a negative error code or zero. An error code must be वापसed
 *	अगर at least one unsupported change was requested.
 * @get_channels: Get number of channels.
 * @set_channels: Set number of channels.  Returns a negative error code or
 *	zero.
 * @get_dump_flag: Get dump flag indicating current dump length, version,
 * 		   and flag of the device.
 * @get_dump_data: Get dump data.
 * @set_dump: Set dump specअगरic flags to the device.
 * @get_ts_info: Get the समय stamping and PTP hardware घड़ी capabilities.
 *	Drivers supporting transmit समय stamps in software should set this to
 *	ethtool_op_get_ts_info().
 * @get_module_info: Get the size and type of the eeprom contained within
 *	a plug-in module.
 * @get_module_eeprom: Get the eeprom inक्रमmation from the plug-in module
 * @get_eee: Get Energy-Efficient (EEE) supported and status.
 * @set_eee: Set EEE status (enable/disable) as well as LPI समयrs.
 * @get_tunable: Read the value of a driver / device tunable.
 * @set_tunable: Set the value of a driver / device tunable.
 * @get_per_queue_coalesce: Get पूर्णांकerrupt coalescing parameters per queue.
 *	It must check that the given queue number is valid. If neither a RX nor
 *	a TX queue has this number, वापस -EINVAL. If only a RX queue or a TX
 *	queue has this number, set the inapplicable fields to ~0 and वापस 0.
 *	Returns a negative error code or zero.
 * @set_per_queue_coalesce: Set पूर्णांकerrupt coalescing parameters per queue.
 *	It must check that the given queue number is valid. If neither a RX nor
 *	a TX queue has this number, वापस -EINVAL. If only a RX queue or a TX
 *	queue has this number, ignore the inapplicable fields. Supported
 *	coalescing types should be set in @supported_coalesce_params.
 *	Returns a negative error code or zero.
 * @get_link_ksettings: Get various device settings including Ethernet link
 *	settings. The %cmd and %link_mode_masks_nwords fields should be
 *	ignored (use %__ETHTOOL_LINK_MODE_MASK_NBITS instead of the latter),
 *	any change to them will be overwritten by kernel. Returns a negative
 *	error code or zero.
 * @set_link_ksettings: Set various device settings including Ethernet link
 *	settings. The %cmd and %link_mode_masks_nwords fields should be
 *	ignored (use %__ETHTOOL_LINK_MODE_MASK_NBITS instead of the latter),
 *	any change to them will be overwritten by kernel. Returns a negative
 *	error code or zero.
 * @get_fec_stats: Report FEC statistics.
 *	Core will sum up per-lane stats to get the total.
 *	Drivers must not zero statistics which they करोn't report. The stats
 *	काष्ठाure is initialized to ETHTOOL_STAT_NOT_SET indicating driver करोes
 *	not report statistics.
 * @get_fecparam: Get the network device Forward Error Correction parameters.
 * @set_fecparam: Set the network device Forward Error Correction parameters.
 * @get_ethtool_phy_stats: Return extended statistics about the PHY device.
 *	This is only useful अगर the device मुख्यtains PHY statistics and
 *	cannot use the standard PHY library helpers.
 * @get_phy_tunable: Read the value of a PHY tunable.
 * @set_phy_tunable: Set the value of a PHY tunable.
 * @get_module_eeprom_by_page: Get a region of plug-in module EEPROM data from
 *	specअगरied page. Returns a negative error code or the amount of bytes
 *	पढ़ो.
 * @get_eth_phy_stats: Query some of the IEEE 802.3 PHY statistics.
 * @get_eth_mac_stats: Query some of the IEEE 802.3 MAC statistics.
 * @get_eth_ctrl_stats: Query some of the IEEE 802.3 MAC Ctrl statistics.
 * @get_rmon_stats: Query some of the RMON (RFC 2819) statistics.
 *	Set %ranges to a poपूर्णांकer to zero-terminated array of byte ranges.
 *
 * All operations are optional (i.e. the function poपूर्णांकer may be set
 * to %शून्य) and callers must take this पूर्णांकo account.  Callers must
 * hold the RTNL lock.
 *
 * See the काष्ठाures used by these operations क्रम further करोcumentation.
 * Note that क्रम all operations using a काष्ठाure ending with a zero-
 * length array, the array is allocated separately in the kernel and
 * is passed to the driver as an additional parameter.
 *
 * See &काष्ठा net_device and &काष्ठा net_device_ops क्रम करोcumentation
 * of the generic netdev features पूर्णांकerface.
 */
काष्ठा ethtool_ops अणु
	u32     cap_link_lanes_supported:1;
	u32	supported_coalesce_params;
	व्योम	(*get_drvinfo)(काष्ठा net_device *, काष्ठा ethtool_drvinfo *);
	पूर्णांक	(*get_regs_len)(काष्ठा net_device *);
	व्योम	(*get_regs)(काष्ठा net_device *, काष्ठा ethtool_regs *, व्योम *);
	व्योम	(*get_wol)(काष्ठा net_device *, काष्ठा ethtool_wolinfo *);
	पूर्णांक	(*set_wol)(काष्ठा net_device *, काष्ठा ethtool_wolinfo *);
	u32	(*get_msglevel)(काष्ठा net_device *);
	व्योम	(*set_msglevel)(काष्ठा net_device *, u32);
	पूर्णांक	(*nway_reset)(काष्ठा net_device *);
	u32	(*get_link)(काष्ठा net_device *);
	पूर्णांक	(*get_link_ext_state)(काष्ठा net_device *,
				      काष्ठा ethtool_link_ext_state_info *);
	पूर्णांक	(*get_eeprom_len)(काष्ठा net_device *);
	पूर्णांक	(*get_eeprom)(काष्ठा net_device *,
			      काष्ठा ethtool_eeprom *, u8 *);
	पूर्णांक	(*set_eeprom)(काष्ठा net_device *,
			      काष्ठा ethtool_eeprom *, u8 *);
	पूर्णांक	(*get_coalesce)(काष्ठा net_device *, काष्ठा ethtool_coalesce *);
	पूर्णांक	(*set_coalesce)(काष्ठा net_device *, काष्ठा ethtool_coalesce *);
	व्योम	(*get_ringparam)(काष्ठा net_device *,
				 काष्ठा ethtool_ringparam *);
	पूर्णांक	(*set_ringparam)(काष्ठा net_device *,
				 काष्ठा ethtool_ringparam *);
	व्योम	(*get_छोड़ो_stats)(काष्ठा net_device *dev,
				   काष्ठा ethtool_छोड़ो_stats *छोड़ो_stats);
	व्योम	(*get_छोड़ोparam)(काष्ठा net_device *,
				  काष्ठा ethtool_छोड़ोparam*);
	पूर्णांक	(*set_छोड़ोparam)(काष्ठा net_device *,
				  काष्ठा ethtool_छोड़ोparam*);
	व्योम	(*self_test)(काष्ठा net_device *, काष्ठा ethtool_test *, u64 *);
	व्योम	(*get_strings)(काष्ठा net_device *, u32 stringset, u8 *);
	पूर्णांक	(*set_phys_id)(काष्ठा net_device *, क्रमागत ethtool_phys_id_state);
	व्योम	(*get_ethtool_stats)(काष्ठा net_device *,
				     काष्ठा ethtool_stats *, u64 *);
	पूर्णांक	(*begin)(काष्ठा net_device *);
	व्योम	(*complete)(काष्ठा net_device *);
	u32	(*get_priv_flags)(काष्ठा net_device *);
	पूर्णांक	(*set_priv_flags)(काष्ठा net_device *, u32);
	पूर्णांक	(*get_sset_count)(काष्ठा net_device *, पूर्णांक);
	पूर्णांक	(*get_rxnfc)(काष्ठा net_device *,
			     काष्ठा ethtool_rxnfc *, u32 *rule_locs);
	पूर्णांक	(*set_rxnfc)(काष्ठा net_device *, काष्ठा ethtool_rxnfc *);
	पूर्णांक	(*flash_device)(काष्ठा net_device *, काष्ठा ethtool_flash *);
	पूर्णांक	(*reset)(काष्ठा net_device *, u32 *);
	u32	(*get_rxfh_key_size)(काष्ठा net_device *);
	u32	(*get_rxfh_indir_size)(काष्ठा net_device *);
	पूर्णांक	(*get_rxfh)(काष्ठा net_device *, u32 *indir, u8 *key,
			    u8 *hfunc);
	पूर्णांक	(*set_rxfh)(काष्ठा net_device *, स्थिर u32 *indir,
			    स्थिर u8 *key, स्थिर u8 hfunc);
	पूर्णांक	(*get_rxfh_context)(काष्ठा net_device *, u32 *indir, u8 *key,
				    u8 *hfunc, u32 rss_context);
	पूर्णांक	(*set_rxfh_context)(काष्ठा net_device *, स्थिर u32 *indir,
				    स्थिर u8 *key, स्थिर u8 hfunc,
				    u32 *rss_context, bool delete);
	व्योम	(*get_channels)(काष्ठा net_device *, काष्ठा ethtool_channels *);
	पूर्णांक	(*set_channels)(काष्ठा net_device *, काष्ठा ethtool_channels *);
	पूर्णांक	(*get_dump_flag)(काष्ठा net_device *, काष्ठा ethtool_dump *);
	पूर्णांक	(*get_dump_data)(काष्ठा net_device *,
				 काष्ठा ethtool_dump *, व्योम *);
	पूर्णांक	(*set_dump)(काष्ठा net_device *, काष्ठा ethtool_dump *);
	पूर्णांक	(*get_ts_info)(काष्ठा net_device *, काष्ठा ethtool_ts_info *);
	पूर्णांक     (*get_module_info)(काष्ठा net_device *,
				   काष्ठा ethtool_modinfo *);
	पूर्णांक     (*get_module_eeprom)(काष्ठा net_device *,
				     काष्ठा ethtool_eeprom *, u8 *);
	पूर्णांक	(*get_eee)(काष्ठा net_device *, काष्ठा ethtool_eee *);
	पूर्णांक	(*set_eee)(काष्ठा net_device *, काष्ठा ethtool_eee *);
	पूर्णांक	(*get_tunable)(काष्ठा net_device *,
			       स्थिर काष्ठा ethtool_tunable *, व्योम *);
	पूर्णांक	(*set_tunable)(काष्ठा net_device *,
			       स्थिर काष्ठा ethtool_tunable *, स्थिर व्योम *);
	पूर्णांक	(*get_per_queue_coalesce)(काष्ठा net_device *, u32,
					  काष्ठा ethtool_coalesce *);
	पूर्णांक	(*set_per_queue_coalesce)(काष्ठा net_device *, u32,
					  काष्ठा ethtool_coalesce *);
	पूर्णांक	(*get_link_ksettings)(काष्ठा net_device *,
				      काष्ठा ethtool_link_ksettings *);
	पूर्णांक	(*set_link_ksettings)(काष्ठा net_device *,
				      स्थिर काष्ठा ethtool_link_ksettings *);
	व्योम	(*get_fec_stats)(काष्ठा net_device *dev,
				 काष्ठा ethtool_fec_stats *fec_stats);
	पूर्णांक	(*get_fecparam)(काष्ठा net_device *,
				      काष्ठा ethtool_fecparam *);
	पूर्णांक	(*set_fecparam)(काष्ठा net_device *,
				      काष्ठा ethtool_fecparam *);
	व्योम	(*get_ethtool_phy_stats)(काष्ठा net_device *,
					 काष्ठा ethtool_stats *, u64 *);
	पूर्णांक	(*get_phy_tunable)(काष्ठा net_device *,
				   स्थिर काष्ठा ethtool_tunable *, व्योम *);
	पूर्णांक	(*set_phy_tunable)(काष्ठा net_device *,
				   स्थिर काष्ठा ethtool_tunable *, स्थिर व्योम *);
	पूर्णांक	(*get_module_eeprom_by_page)(काष्ठा net_device *dev,
					     स्थिर काष्ठा ethtool_module_eeprom *page,
					     काष्ठा netlink_ext_ack *extack);
	व्योम	(*get_eth_phy_stats)(काष्ठा net_device *dev,
				     काष्ठा ethtool_eth_phy_stats *phy_stats);
	व्योम	(*get_eth_mac_stats)(काष्ठा net_device *dev,
				     काष्ठा ethtool_eth_mac_stats *mac_stats);
	व्योम	(*get_eth_ctrl_stats)(काष्ठा net_device *dev,
				      काष्ठा ethtool_eth_ctrl_stats *ctrl_stats);
	व्योम	(*get_rmon_stats)(काष्ठा net_device *dev,
				  काष्ठा ethtool_rmon_stats *rmon_stats,
				  स्थिर काष्ठा ethtool_rmon_hist_range **ranges);
पूर्ण;

पूर्णांक ethtool_check_ops(स्थिर काष्ठा ethtool_ops *ops);

काष्ठा ethtool_rx_flow_rule अणु
	काष्ठा flow_rule	*rule;
	अचिन्हित दीर्घ		priv[];
पूर्ण;

काष्ठा ethtool_rx_flow_spec_input अणु
	स्थिर काष्ठा ethtool_rx_flow_spec	*fs;
	u32					rss_ctx;
पूर्ण;

काष्ठा ethtool_rx_flow_rule *
ethtool_rx_flow_rule_create(स्थिर काष्ठा ethtool_rx_flow_spec_input *input);
व्योम ethtool_rx_flow_rule_destroy(काष्ठा ethtool_rx_flow_rule *rule);

bool ethtool_virtdev_validate_cmd(स्थिर काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक ethtool_virtdev_set_link_ksettings(काष्ठा net_device *dev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd,
				       u32 *dev_speed, u8 *dev_duplex);

काष्ठा phy_device;
काष्ठा phy_tdr_config;

/**
 * काष्ठा ethtool_phy_ops - Optional PHY device options
 * @get_sset_count: Get number of strings that @get_strings will ग_लिखो.
 * @get_strings: Return a set of strings that describe the requested objects
 * @get_stats: Return extended statistics about the PHY device.
 * @start_cable_test: Start a cable test
 * @start_cable_test_tdr: Start a Time Doमुख्य Reflectometry cable test
 *
 * All operations are optional (i.e. the function poपूर्णांकer may be set to %शून्य)
 * and callers must take this पूर्णांकo account. Callers must hold the RTNL lock.
 */
काष्ठा ethtool_phy_ops अणु
	पूर्णांक (*get_sset_count)(काष्ठा phy_device *dev);
	पूर्णांक (*get_strings)(काष्ठा phy_device *dev, u8 *data);
	पूर्णांक (*get_stats)(काष्ठा phy_device *dev,
			 काष्ठा ethtool_stats *stats, u64 *data);
	पूर्णांक (*start_cable_test)(काष्ठा phy_device *phydev,
				काष्ठा netlink_ext_ack *extack);
	पूर्णांक (*start_cable_test_tdr)(काष्ठा phy_device *phydev,
				    काष्ठा netlink_ext_ack *extack,
				    स्थिर काष्ठा phy_tdr_config *config);
पूर्ण;

/**
 * ethtool_set_ethtool_phy_ops - Set the ethtool_phy_ops singleton
 * @ops: Ethtool PHY operations to set
 */
व्योम ethtool_set_ethtool_phy_ops(स्थिर काष्ठा ethtool_phy_ops *ops);

/**
 * ethtool_params_from_link_mode - Derive link parameters from a given link mode
 * @link_ksettings: Link parameters to be derived from the link mode
 * @link_mode: Link mode
 */
व्योम
ethtool_params_from_link_mode(काष्ठा ethtool_link_ksettings *link_ksettings,
			      क्रमागत ethtool_link_mode_bit_indices link_mode);

/**
 * ethtool_प्र_लिखो - Write क्रमmatted string to ethtool string data
 * @data: Poपूर्णांकer to start of string to update
 * @fmt: Format of string to ग_लिखो
 *
 * Write क्रमmatted string to data. Update data to poपूर्णांक at start of
 * next string.
 */
बाह्य __म_लिखो(2, 3) व्योम ethtool_प्र_लिखो(u8 **data, स्थिर अक्षर *fmt, ...);
#पूर्ण_अगर /* _LINUX_ETHTOOL_H */
