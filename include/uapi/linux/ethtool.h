<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
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

#अगर_अघोषित _UAPI_LINUX_ETHTOOL_H
#घोषणा _UAPI_LINUX_ETHTOOL_H

#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#अगर_अघोषित __KERNEL__
#समावेश <सीमा.स> /* क्रम पूर्णांक_उच्च */
#पूर्ण_अगर

/* All काष्ठाures exposed to userland should be defined such that they
 * have the same layout क्रम 32-bit and 64-bit userland.
 */

/* Note on reserved space.
 * Reserved fields must not be accessed directly by user space because
 * they may be replaced by a dअगरferent field in the future. They must
 * be initialized to zero beक्रमe making the request, e.g. via स_रखो
 * of the entire काष्ठाure or implicitly by not being set in a काष्ठाure
 * initializer.
 */

/**
 * काष्ठा ethtool_cmd - DEPRECATED, link control and status
 * This काष्ठाure is DEPRECATED, please use काष्ठा ethtool_link_settings.
 * @cmd: Command number = %ETHTOOL_GSET or %ETHTOOL_SSET
 * @supported: Biपंचांगask of %SUPPORTED_* flags क्रम the link modes,
 *	physical connectors and other link features क्रम which the
 *	पूर्णांकerface supports स्वतःnegotiation or स्वतः-detection.
 *	Read-only.
 * @advertising: Biपंचांगask of %ADVERTISED_* flags क्रम the link modes,
 *	physical connectors and other link features that are
 *	advertised through स्वतःnegotiation or enabled क्रम
 *	स्वतः-detection.
 * @speed: Low bits of the speed, 1Mb units, 0 to पूर्णांक_उच्च or SPEED_UNKNOWN
 * @duplex: Duplex mode; one of %DUPLEX_*
 * @port: Physical connector type; one of %PORT_*
 * @phy_address: MDIO address of PHY (transceiver); 0 or 255 अगर not
 *	applicable.  For clause 45 PHYs this is the PRTAD.
 * @transceiver: Historically used to distinguish dअगरferent possible
 *	PHY types, but not in a consistent way.  Deprecated.
 * @स्वतःneg: Enable/disable स्वतःnegotiation and स्वतः-detection;
 *	either %AUTONEG_DISABLE or %AUTONEG_ENABLE
 * @mdio_support: Biपंचांगask of %ETH_MDIO_SUPPORTS_* flags क्रम the MDIO
 *	protocols supported by the पूर्णांकerface; 0 अगर unknown.
 *	Read-only.
 * @maxtxpkt: Historically used to report TX IRQ coalescing; now
 *	obsoleted by &काष्ठा ethtool_coalesce.  Read-only; deprecated.
 * @maxrxpkt: Historically used to report RX IRQ coalescing; now
 *	obsoleted by &काष्ठा ethtool_coalesce.  Read-only; deprecated.
 * @speed_hi: High bits of the speed, 1Mb units, 0 to पूर्णांक_उच्च or SPEED_UNKNOWN
 * @eth_tp_mdix: Ethernet twisted-pair MDI(-X) status; one of
 *	%ETH_TP_MDI_*.  If the status is unknown or not applicable, the
 *	value will be %ETH_TP_MDI_INVALID.  Read-only.
 * @eth_tp_mdix_ctrl: Ethernet twisted pair MDI(-X) control; one of
 *	%ETH_TP_MDI_*.  If MDI(-X) control is not implemented, पढ़ोs
 *	yield %ETH_TP_MDI_INVALID and ग_लिखोs may be ignored or rejected.
 *	When written successfully, the link should be renegotiated अगर
 *	necessary.
 * @lp_advertising: Biपंचांगask of %ADVERTISED_* flags क्रम the link modes
 *	and other link features that the link partner advertised
 *	through स्वतःnegotiation; 0 अगर unknown or not applicable.
 *	Read-only.
 * @reserved: Reserved क्रम future use; see the note on reserved space.
 *
 * The link speed in Mbps is split between @speed and @speed_hi.  Use
 * the ethtool_cmd_speed() and ethtool_cmd_speed_set() functions to
 * access it.
 *
 * If स्वतःnegotiation is disabled, the speed and @duplex represent the
 * fixed link mode and are writable अगर the driver supports multiple
 * link modes.  If it is enabled then they are पढ़ो-only; अगर the link
 * is up they represent the negotiated link mode; अगर the link is करोwn,
 * the speed is 0, %SPEED_UNKNOWN or the highest enabled speed and
 * @duplex is %DUPLEX_UNKNOWN or the best enabled duplex mode.
 *
 * Some hardware पूर्णांकerfaces may have multiple PHYs and/or physical
 * connectors fitted or करो not allow the driver to detect which are
 * fitted.  For these पूर्णांकerfaces @port and/or @phy_address may be
 * writable, possibly dependent on @स्वतःneg being %AUTONEG_DISABLE.
 * Otherwise, attempts to ग_लिखो dअगरferent values may be ignored or
 * rejected.
 *
 * Users should assume that all fields not marked पढ़ो-only are
 * writable and subject to validation by the driver.  They should use
 * %ETHTOOL_GSET to get the current values beक्रमe making specअगरic
 * changes and then applying them with %ETHTOOL_SSET.
 *
 * Deprecated fields should be ignored by both users and drivers.
 */
काष्ठा ethtool_cmd अणु
	__u32	cmd;
	__u32	supported;
	__u32	advertising;
	__u16	speed;
	__u8	duplex;
	__u8	port;
	__u8	phy_address;
	__u8	transceiver;
	__u8	स्वतःneg;
	__u8	mdio_support;
	__u32	maxtxpkt;
	__u32	maxrxpkt;
	__u16	speed_hi;
	__u8	eth_tp_mdix;
	__u8	eth_tp_mdix_ctrl;
	__u32	lp_advertising;
	__u32	reserved[2];
पूर्ण;

अटल अंतरभूत व्योम ethtool_cmd_speed_set(काष्ठा ethtool_cmd *ep,
					 __u32 speed)
अणु
	ep->speed = (__u16)(speed & 0xFFFF);
	ep->speed_hi = (__u16)(speed >> 16);
पूर्ण

अटल अंतरभूत __u32 ethtool_cmd_speed(स्थिर काष्ठा ethtool_cmd *ep)
अणु
	वापस (ep->speed_hi << 16) | ep->speed;
पूर्ण

/* Device supports clause 22 रेजिस्टर access to PHY or peripherals
 * using the पूर्णांकerface defined in <linux/mii.h>.  This should not be
 * set अगर there are known to be no such peripherals present or अगर
 * the driver only emulates clause 22 रेजिस्टरs क्रम compatibility.
 */
#घोषणा ETH_MDIO_SUPPORTS_C22	1

/* Device supports clause 45 रेजिस्टर access to PHY or peripherals
 * using the पूर्णांकerface defined in <linux/mii.h> and <linux/mdपन.स>.
 * This should not be set अगर there are known to be no such peripherals
 * present.
 */
#घोषणा ETH_MDIO_SUPPORTS_C45	2

#घोषणा ETHTOOL_FWVERS_LEN	32
#घोषणा ETHTOOL_BUSINFO_LEN	32
#घोषणा ETHTOOL_EROMVERS_LEN	32

/**
 * काष्ठा ethtool_drvinfo - general driver and device inक्रमmation
 * @cmd: Command number = %ETHTOOL_GDRVINFO
 * @driver: Driver लघु name.  This should normally match the name
 *	in its bus driver काष्ठाure (e.g. pci_driver::name).  Must
 *	not be an empty string.
 * @version: Driver version string; may be an empty string
 * @fw_version: Firmware version string; may be an empty string
 * @erom_version: Expansion ROM version string; may be an empty string
 * @bus_info: Device bus address.  This should match the dev_name()
 *	string क्रम the underlying bus device, अगर there is one.  May be
 *	an empty string.
 * @reserved2: Reserved क्रम future use; see the note on reserved space.
 * @n_priv_flags: Number of flags valid क्रम %ETHTOOL_GPFLAGS and
 *	%ETHTOOL_SPFLAGS commands; also the number of strings in the
 *	%ETH_SS_PRIV_FLAGS set
 * @n_stats: Number of u64 statistics वापसed by the %ETHTOOL_GSTATS
 *	command; also the number of strings in the %ETH_SS_STATS set
 * @testinfo_len: Number of results वापसed by the %ETHTOOL_TEST
 *	command; also the number of strings in the %ETH_SS_TEST set
 * @eedump_len: Size of EEPROM accessible through the %ETHTOOL_GEEPROM
 *	and %ETHTOOL_SEEPROM commands, in bytes
 * @regdump_len: Size of रेजिस्टर dump वापसed by the %ETHTOOL_GREGS
 *	command, in bytes
 *
 * Users can use the %ETHTOOL_GSSET_INFO command to get the number of
 * strings in any string set (from Linux 2.6.34).
 *
 * Drivers should set at most @driver, @version, @fw_version and
 * @bus_info in their get_drvinfo() implementation.  The ethtool
 * core fills in the other fields using other driver operations.
 */
काष्ठा ethtool_drvinfo अणु
	__u32	cmd;
	अक्षर	driver[32];
	अक्षर	version[32];
	अक्षर	fw_version[ETHTOOL_FWVERS_LEN];
	अक्षर	bus_info[ETHTOOL_BUSINFO_LEN];
	अक्षर	erom_version[ETHTOOL_EROMVERS_LEN];
	अक्षर	reserved2[12];
	__u32	n_priv_flags;
	__u32	n_stats;
	__u32	testinfo_len;
	__u32	eedump_len;
	__u32	regdump_len;
पूर्ण;

#घोषणा SOPASS_MAX	6

/**
 * काष्ठा ethtool_wolinfo - Wake-On-Lan configuration
 * @cmd: Command number = %ETHTOOL_GWOL or %ETHTOOL_SWOL
 * @supported: Biपंचांगask of %WAKE_* flags क्रम supported Wake-On-Lan modes.
 *	Read-only.
 * @wolopts: Biपंचांगask of %WAKE_* flags क्रम enabled Wake-On-Lan modes.
 * @sopass: SecureOn(पंचांग) password; meaningful only अगर %WAKE_MAGICSECURE
 *	is set in @wolopts.
 */
काष्ठा ethtool_wolinfo अणु
	__u32	cmd;
	__u32	supported;
	__u32	wolopts;
	__u8	sopass[SOPASS_MAX];
पूर्ण;

/* क्रम passing single values */
काष्ठा ethtool_value अणु
	__u32	cmd;
	__u32	data;
पूर्ण;

#घोषणा PFC_STORM_PREVENTION_AUTO	0xffff
#घोषणा PFC_STORM_PREVENTION_DISABLE	0

क्रमागत tunable_id अणु
	ETHTOOL_ID_UNSPEC,
	ETHTOOL_RX_COPYBREAK,
	ETHTOOL_TX_COPYBREAK,
	ETHTOOL_PFC_PREVENTION_TOUT, /* समयout in msecs */
	/*
	 * Add your fresh new tunable attribute above and remember to update
	 * tunable_strings[] in net/core/ethtool.c
	 */
	__ETHTOOL_TUNABLE_COUNT,
पूर्ण;

क्रमागत tunable_type_id अणु
	ETHTOOL_TUNABLE_UNSPEC,
	ETHTOOL_TUNABLE_U8,
	ETHTOOL_TUNABLE_U16,
	ETHTOOL_TUNABLE_U32,
	ETHTOOL_TUNABLE_U64,
	ETHTOOL_TUNABLE_STRING,
	ETHTOOL_TUNABLE_S8,
	ETHTOOL_TUNABLE_S16,
	ETHTOOL_TUNABLE_S32,
	ETHTOOL_TUNABLE_S64,
पूर्ण;

काष्ठा ethtool_tunable अणु
	__u32	cmd;
	__u32	id;
	__u32	type_id;
	__u32	len;
	व्योम	*data[0];
पूर्ण;

#घोषणा DOWNSHIFT_DEV_DEFAULT_COUNT	0xff
#घोषणा DOWNSHIFT_DEV_DISABLE		0

/* Time in msecs after which link is reported as करोwn
 * 0 = lowest समय supported by the PHY
 * 0xff = off, link करोwn detection according to standard
 */
#घोषणा ETHTOOL_PHY_FAST_LINK_DOWN_ON	0
#घोषणा ETHTOOL_PHY_FAST_LINK_DOWN_OFF	0xff

/* Energy Detect Power Down (EDPD) is a feature supported by some PHYs, where
 * the PHY's RX & TX blocks are put पूर्णांकo a low-घातer mode when there is no
 * link detected (typically cable is un-plugged). For RX, only a minimal
 * link-detection is available, and क्रम TX the PHY wakes up to send link pulses
 * to aव्योम any lock-ups in हाल the peer PHY may also be running in EDPD mode.
 *
 * Some PHYs may support configuration of the wake-up पूर्णांकerval क्रम TX pulses,
 * and some PHYs may support only disabling TX pulses entirely. For the latter
 * a special value is required (ETHTOOL_PHY_EDPD_NO_TX) so that this can be
 * configured from userspace (should the user want it).
 *
 * The पूर्णांकerval units क्रम TX wake-up are in milliseconds, since this should
 * cover a reasonable range of पूर्णांकervals:
 *  - from 1 millisecond, which करोes not sound like much of a घातer-saver
 *  - to ~65 seconds which is quite a lot to रुको क्रम a link to come up when
 *    plugging a cable
 */
#घोषणा ETHTOOL_PHY_EDPD_DFLT_TX_MSECS		0xffff
#घोषणा ETHTOOL_PHY_EDPD_NO_TX			0xfffe
#घोषणा ETHTOOL_PHY_EDPD_DISABLE		0

क्रमागत phy_tunable_id अणु
	ETHTOOL_PHY_ID_UNSPEC,
	ETHTOOL_PHY_DOWNSHIFT,
	ETHTOOL_PHY_FAST_LINK_DOWN,
	ETHTOOL_PHY_EDPD,
	/*
	 * Add your fresh new phy tunable attribute above and remember to update
	 * phy_tunable_strings[] in net/core/ethtool.c
	 */
	__ETHTOOL_PHY_TUNABLE_COUNT,
पूर्ण;

/**
 * काष्ठा ethtool_regs - hardware रेजिस्टर dump
 * @cmd: Command number = %ETHTOOL_GREGS
 * @version: Dump क्रमmat version.  This is driver-specअगरic and may
 *	distinguish dअगरferent chips/revisions.  Drivers must use new
 *	version numbers whenever the dump क्रमmat changes in an
 *	incompatible way.
 * @len: On entry, the real length of @data.  On वापस, the number of
 *	bytes used.
 * @data: Buffer क्रम the रेजिस्टर dump
 *
 * Users should use %ETHTOOL_GDRVINFO to find the maximum length of
 * a रेजिस्टर dump क्रम the पूर्णांकerface.  They must allocate the buffer
 * immediately following this काष्ठाure.
 */
काष्ठा ethtool_regs अणु
	__u32	cmd;
	__u32	version;
	__u32	len;
	__u8	data[0];
पूर्ण;

/**
 * काष्ठा ethtool_eeprom - EEPROM dump
 * @cmd: Command number = %ETHTOOL_GEEPROM, %ETHTOOL_GMODULEEEPROM or
 *	%ETHTOOL_SEEPROM
 * @magic: A 'magic cookie' value to guard against accidental changes.
 *	The value passed in to %ETHTOOL_SEEPROM must match the value
 *	वापसed by %ETHTOOL_GEEPROM क्रम the same device.  This is
 *	unused when @cmd is %ETHTOOL_GMODULEEEPROM.
 * @offset: Offset within the EEPROM to begin पढ़ोing/writing, in bytes
 * @len: On entry, number of bytes to पढ़ो/ग_लिखो.  On successful
 *	वापस, number of bytes actually पढ़ो/written.  In हाल of
 *	error, this may indicate at what poपूर्णांक the error occurred.
 * @data: Buffer to पढ़ो/ग_लिखो from
 *
 * Users may use %ETHTOOL_GDRVINFO or %ETHTOOL_GMODULEINFO to find
 * the length of an on-board or module EEPROM, respectively.  They
 * must allocate the buffer immediately following this काष्ठाure.
 */
काष्ठा ethtool_eeprom अणु
	__u32	cmd;
	__u32	magic;
	__u32	offset;
	__u32	len;
	__u8	data[0];
पूर्ण;

/**
 * काष्ठा ethtool_eee - Energy Efficient Ethernet inक्रमmation
 * @cmd: ETHTOOL_अणुG,Sपूर्णEEE
 * @supported: Mask of %SUPPORTED_* flags क्रम the speed/duplex combinations
 *	क्रम which there is EEE support.
 * @advertised: Mask of %ADVERTISED_* flags क्रम the speed/duplex combinations
 *	advertised as eee capable.
 * @lp_advertised: Mask of %ADVERTISED_* flags क्रम the speed/duplex
 *	combinations advertised by the link partner as eee capable.
 * @eee_active: Result of the eee स्वतः negotiation.
 * @eee_enabled: EEE configured mode (enabled/disabled).
 * @tx_lpi_enabled: Whether the पूर्णांकerface should निश्चित its tx lpi, given
 *	that eee was negotiated.
 * @tx_lpi_समयr: Time in microseconds the पूर्णांकerface delays prior to निश्चितing
 *	its tx lpi (after reaching 'idle' state). Effective only when eee
 *	was negotiated and tx_lpi_enabled was set.
 * @reserved: Reserved क्रम future use; see the note on reserved space.
 */
काष्ठा ethtool_eee अणु
	__u32	cmd;
	__u32	supported;
	__u32	advertised;
	__u32	lp_advertised;
	__u32	eee_active;
	__u32	eee_enabled;
	__u32	tx_lpi_enabled;
	__u32	tx_lpi_समयr;
	__u32	reserved[2];
पूर्ण;

/**
 * काष्ठा ethtool_modinfo - plugin module eeprom inक्रमmation
 * @cmd: %ETHTOOL_GMODULEINFO
 * @type: Standard the module inक्रमmation conक्रमms to %ETH_MODULE_SFF_xxxx
 * @eeprom_len: Length of the eeprom
 * @reserved: Reserved क्रम future use; see the note on reserved space.
 *
 * This काष्ठाure is used to वापस the inक्रमmation to
 * properly size memory क्रम a subsequent call to %ETHTOOL_GMODULEEEPROM.
 * The type code indicates the eeprom data क्रमmat
 */
काष्ठा ethtool_modinfo अणु
	__u32   cmd;
	__u32   type;
	__u32   eeprom_len;
	__u32   reserved[8];
पूर्ण;

/**
 * काष्ठा ethtool_coalesce - coalescing parameters क्रम IRQs and stats updates
 * @cmd: ETHTOOL_अणुG,Sपूर्णCOALESCE
 * @rx_coalesce_usecs: How many usecs to delay an RX पूर्णांकerrupt after
 *	a packet arrives.
 * @rx_max_coalesced_frames: Maximum number of packets to receive
 *	beक्रमe an RX पूर्णांकerrupt.
 * @rx_coalesce_usecs_irq: Same as @rx_coalesce_usecs, except that
 *	this value applies जबतक an IRQ is being serviced by the host.
 * @rx_max_coalesced_frames_irq: Same as @rx_max_coalesced_frames,
 *	except that this value applies जबतक an IRQ is being serviced
 *	by the host.
 * @tx_coalesce_usecs: How many usecs to delay a TX पूर्णांकerrupt after
 *	a packet is sent.
 * @tx_max_coalesced_frames: Maximum number of packets to be sent
 *	beक्रमe a TX पूर्णांकerrupt.
 * @tx_coalesce_usecs_irq: Same as @tx_coalesce_usecs, except that
 *	this value applies जबतक an IRQ is being serviced by the host.
 * @tx_max_coalesced_frames_irq: Same as @tx_max_coalesced_frames,
 *	except that this value applies जबतक an IRQ is being serviced
 *	by the host.
 * @stats_block_coalesce_usecs: How many usecs to delay in-memory
 *	statistics block updates.  Some drivers करो not have an
 *	in-memory statistic block, and in such हालs this value is
 *	ignored.  This value must not be zero.
 * @use_adaptive_rx_coalesce: Enable adaptive RX coalescing.
 * @use_adaptive_tx_coalesce: Enable adaptive TX coalescing.
 * @pkt_rate_low: Threshold क्रम low packet rate (packets per second).
 * @rx_coalesce_usecs_low: How many usecs to delay an RX पूर्णांकerrupt after
 *	a packet arrives, when the packet rate is below @pkt_rate_low.
 * @rx_max_coalesced_frames_low: Maximum number of packets to be received
 *	beक्रमe an RX पूर्णांकerrupt, when the packet rate is below @pkt_rate_low.
 * @tx_coalesce_usecs_low: How many usecs to delay a TX पूर्णांकerrupt after
 *	a packet is sent, when the packet rate is below @pkt_rate_low.
 * @tx_max_coalesced_frames_low: Maximum nuumber of packets to be sent beक्रमe
 *	a TX पूर्णांकerrupt, when the packet rate is below @pkt_rate_low.
 * @pkt_rate_high: Threshold क्रम high packet rate (packets per second).
 * @rx_coalesce_usecs_high: How many usecs to delay an RX पूर्णांकerrupt after
 *	a packet arrives, when the packet rate is above @pkt_rate_high.
 * @rx_max_coalesced_frames_high: Maximum number of packets to be received
 *	beक्रमe an RX पूर्णांकerrupt, when the packet rate is above @pkt_rate_high.
 * @tx_coalesce_usecs_high: How many usecs to delay a TX पूर्णांकerrupt after
 *	a packet is sent, when the packet rate is above @pkt_rate_high.
 * @tx_max_coalesced_frames_high: Maximum number of packets to be sent beक्रमe
 *	a TX पूर्णांकerrupt, when the packet rate is above @pkt_rate_high.
 * @rate_sample_पूर्णांकerval: How often to करो adaptive coalescing packet rate
 *	sampling, measured in seconds.  Must not be zero.
 *
 * Each pair of (usecs, max_frames) fields specअगरies that पूर्णांकerrupts
 * should be coalesced until
 *	(usecs > 0 && समय_since_first_completion >= usecs) ||
 *	(max_frames > 0 && completed_frames >= max_frames)
 *
 * It is illegal to set both usecs and max_frames to zero as this
 * would cause पूर्णांकerrupts to never be generated.  To disable
 * coalescing, set usecs = 0 and max_frames = 1.
 *
 * Some implementations ignore the value of max_frames and use the
 * condition समय_since_first_completion >= usecs
 *
 * This is deprecated.  Drivers क्रम hardware that करोes not support
 * counting completions should validate that max_frames == !rx_usecs.
 *
 * Adaptive RX/TX coalescing is an algorithm implemented by some
 * drivers to improve latency under low packet rates and improve
 * throughput under high packet rates.  Some drivers only implement
 * one of RX or TX adaptive coalescing.  Anything not implemented by
 * the driver causes these values to be silently ignored.
 *
 * When the packet rate is below @pkt_rate_high but above
 * @pkt_rate_low (both measured in packets per second) the
 * normal अणुrx,txपूर्ण_* coalescing parameters are used.
 */
काष्ठा ethtool_coalesce अणु
	__u32	cmd;
	__u32	rx_coalesce_usecs;
	__u32	rx_max_coalesced_frames;
	__u32	rx_coalesce_usecs_irq;
	__u32	rx_max_coalesced_frames_irq;
	__u32	tx_coalesce_usecs;
	__u32	tx_max_coalesced_frames;
	__u32	tx_coalesce_usecs_irq;
	__u32	tx_max_coalesced_frames_irq;
	__u32	stats_block_coalesce_usecs;
	__u32	use_adaptive_rx_coalesce;
	__u32	use_adaptive_tx_coalesce;
	__u32	pkt_rate_low;
	__u32	rx_coalesce_usecs_low;
	__u32	rx_max_coalesced_frames_low;
	__u32	tx_coalesce_usecs_low;
	__u32	tx_max_coalesced_frames_low;
	__u32	pkt_rate_high;
	__u32	rx_coalesce_usecs_high;
	__u32	rx_max_coalesced_frames_high;
	__u32	tx_coalesce_usecs_high;
	__u32	tx_max_coalesced_frames_high;
	__u32	rate_sample_पूर्णांकerval;
पूर्ण;

/**
 * काष्ठा ethtool_ringparam - RX/TX ring parameters
 * @cmd: Command number = %ETHTOOL_GRINGPARAM or %ETHTOOL_SRINGPARAM
 * @rx_max_pending: Maximum supported number of pending entries per
 *	RX ring.  Read-only.
 * @rx_mini_max_pending: Maximum supported number of pending entries
 *	per RX mini ring.  Read-only.
 * @rx_jumbo_max_pending: Maximum supported number of pending entries
 *	per RX jumbo ring.  Read-only.
 * @tx_max_pending: Maximum supported number of pending entries per
 *	TX ring.  Read-only.
 * @rx_pending: Current maximum number of pending entries per RX ring
 * @rx_mini_pending: Current maximum number of pending entries per RX
 *	mini ring
 * @rx_jumbo_pending: Current maximum number of pending entries per RX
 *	jumbo ring
 * @tx_pending: Current maximum supported number of pending entries
 *	per TX ring
 *
 * If the पूर्णांकerface करोes not have separate RX mini and/or jumbo rings,
 * @rx_mini_max_pending and/or @rx_jumbo_max_pending will be 0.
 *
 * There may also be driver-dependent minimum values क्रम the number
 * of entries per ring.
 */
काष्ठा ethtool_ringparam अणु
	__u32	cmd;
	__u32	rx_max_pending;
	__u32	rx_mini_max_pending;
	__u32	rx_jumbo_max_pending;
	__u32	tx_max_pending;
	__u32	rx_pending;
	__u32	rx_mini_pending;
	__u32	rx_jumbo_pending;
	__u32	tx_pending;
पूर्ण;

/**
 * काष्ठा ethtool_channels - configuring number of network channel
 * @cmd: ETHTOOL_अणुG,Sपूर्णCHANNELS
 * @max_rx: Read only. Maximum number of receive channel the driver support.
 * @max_tx: Read only. Maximum number of transmit channel the driver support.
 * @max_other: Read only. Maximum number of other channel the driver support.
 * @max_combined: Read only. Maximum number of combined channel the driver
 *	support. Set of queues RX, TX or other.
 * @rx_count: Valid values are in the range 1 to the max_rx.
 * @tx_count: Valid values are in the range 1 to the max_tx.
 * @other_count: Valid values are in the range 1 to the max_other.
 * @combined_count: Valid values are in the range 1 to the max_combined.
 *
 * This can be used to configure RX, TX and other channels.
 */

काष्ठा ethtool_channels अणु
	__u32	cmd;
	__u32	max_rx;
	__u32	max_tx;
	__u32	max_other;
	__u32	max_combined;
	__u32	rx_count;
	__u32	tx_count;
	__u32	other_count;
	__u32	combined_count;
पूर्ण;

/**
 * काष्ठा ethtool_छोड़ोparam - Ethernet छोड़ो (flow control) parameters
 * @cmd: Command number = %ETHTOOL_GPAUSEPARAM or %ETHTOOL_SPAUSEPARAM
 * @स्वतःneg: Flag to enable स्वतःnegotiation of छोड़ो frame use
 * @rx_छोड़ो: Flag to enable reception of छोड़ो frames
 * @tx_छोड़ो: Flag to enable transmission of छोड़ो frames
 *
 * Drivers should reject a non-zero setting of @स्वतःneg when
 * स्वतःneogotiation is disabled (or not supported) क्रम the link.
 *
 * If the link is स्वतःnegotiated, drivers should use
 * mii_advertise_flowctrl() or similar code to set the advertised
 * छोड़ो frame capabilities based on the @rx_छोड़ो and @tx_छोड़ो flags,
 * even अगर @स्वतःneg is zero.  They should also allow the advertised
 * छोड़ो frame capabilities to be controlled directly through the
 * advertising field of &काष्ठा ethtool_cmd.
 *
 * If @स्वतःneg is non-zero, the MAC is configured to send and/or
 * receive छोड़ो frames according to the result of स्वतःnegotiation.
 * Otherwise, it is configured directly based on the @rx_छोड़ो and
 * @tx_छोड़ो flags.
 */
काष्ठा ethtool_छोड़ोparam अणु
	__u32	cmd;
	__u32	स्वतःneg;
	__u32	rx_छोड़ो;
	__u32	tx_छोड़ो;
पूर्ण;

/* Link extended state */
क्रमागत ethtool_link_ext_state अणु
	ETHTOOL_LINK_EXT_STATE_AUTONEG,
	ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
	ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
	ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
	ETHTOOL_LINK_EXT_STATE_NO_CABLE,
	ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
	ETHTOOL_LINK_EXT_STATE_EEPROM_ISSUE,
	ETHTOOL_LINK_EXT_STATE_CALIBRATION_FAILURE,
	ETHTOOL_LINK_EXT_STATE_POWER_BUDGET_EXCEEDED,
	ETHTOOL_LINK_EXT_STATE_OVERHEAT,
पूर्ण;

/* More inक्रमmation in addition to ETHTOOL_LINK_EXT_STATE_AUTONEG. */
क्रमागत ethtool_link_ext_substate_स्वतःneg अणु
	ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED = 1,
	ETHTOOL_LINK_EXT_SUBSTATE_AN_ACK_NOT_RECEIVED,
	ETHTOOL_LINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAILED,
	ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED_FORCE_MODE,
	ETHTOOL_LINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DURING_OVERRIDE,
	ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_HCD,
पूर्ण;

/* More inक्रमmation in addition to ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE.
 */
क्रमागत ethtool_link_ext_substate_link_training अणु
	ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_FRAME_LOCK_NOT_ACQUIRED = 1,
	ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_LINK_INHIBIT_TIMEOUT,
	ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_LINK_PARTNER_DID_NOT_SET_RECEIVER_READY,
	ETHTOOL_LINK_EXT_SUBSTATE_LT_REMOTE_FAULT,
पूर्ण;

/* More inक्रमmation in addition to ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH.
 */
क्रमागत ethtool_link_ext_substate_link_logical_mismatch अणु
	ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_BLOCK_LOCK = 1,
	ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_AM_LOCK,
	ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_GET_ALIGN_STATUS,
	ETHTOOL_LINK_EXT_SUBSTATE_LLM_FC_FEC_IS_NOT_LOCKED,
	ETHTOOL_LINK_EXT_SUBSTATE_LLM_RS_FEC_IS_NOT_LOCKED,
पूर्ण;

/* More inक्रमmation in addition to ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY.
 */
क्रमागत ethtool_link_ext_substate_bad_संकेत_पूर्णांकegrity अणु
	ETHTOOL_LINK_EXT_SUBSTATE_BSI_LARGE_NUMBER_OF_PHYSICAL_ERRORS = 1,
	ETHTOOL_LINK_EXT_SUBSTATE_BSI_UNSUPPORTED_RATE,
पूर्ण;

/* More inक्रमmation in addition to ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE. */
क्रमागत ethtool_link_ext_substate_cable_issue अणु
	ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLE = 1,
	ETHTOOL_LINK_EXT_SUBSTATE_CI_CABLE_TEST_FAILURE,
पूर्ण;

#घोषणा ETH_GSTRING_LEN		32

/**
 * क्रमागत ethtool_stringset - string set ID
 * @ETH_SS_TEST: Self-test result names, क्रम use with %ETHTOOL_TEST
 * @ETH_SS_STATS: Statistic names, क्रम use with %ETHTOOL_GSTATS
 * @ETH_SS_PRIV_FLAGS: Driver निजी flag names, क्रम use with
 *	%ETHTOOL_GPFLAGS and %ETHTOOL_SPFLAGS
 * @ETH_SS_NTUPLE_FILTERS: Previously used with %ETHTOOL_GRXNTUPLE;
 *	now deprecated
 * @ETH_SS_FEATURES: Device feature names
 * @ETH_SS_RSS_HASH_FUNCS: RSS hush function names
 * @ETH_SS_TUNABLES: tunable names
 * @ETH_SS_PHY_STATS: Statistic names, क्रम use with %ETHTOOL_GPHYSTATS
 * @ETH_SS_PHY_TUNABLES: PHY tunable names
 * @ETH_SS_LINK_MODES: link mode names
 * @ETH_SS_MSG_CLASSES: debug message class names
 * @ETH_SS_WOL_MODES: wake-on-lan modes
 * @ETH_SS_SOF_TIMESTAMPING: SOF_TIMESTAMPING_* flags
 * @ETH_SS_TS_TX_TYPES: बारtamping Tx types
 * @ETH_SS_TS_RX_FILTERS: बारtamping Rx filters
 * @ETH_SS_UDP_TUNNEL_TYPES: UDP tunnel types
 * @ETH_SS_STATS_STD: standardized stats
 * @ETH_SS_STATS_ETH_PHY: names of IEEE 802.3 PHY statistics
 * @ETH_SS_STATS_ETH_MAC: names of IEEE 802.3 MAC statistics
 * @ETH_SS_STATS_ETH_CTRL: names of IEEE 802.3 MAC Control statistics
 * @ETH_SS_STATS_RMON: names of RMON statistics
 *
 * @ETH_SS_COUNT: number of defined string sets
 */
क्रमागत ethtool_stringset अणु
	ETH_SS_TEST		= 0,
	ETH_SS_STATS,
	ETH_SS_PRIV_FLAGS,
	ETH_SS_NTUPLE_FILTERS,
	ETH_SS_FEATURES,
	ETH_SS_RSS_HASH_FUNCS,
	ETH_SS_TUNABLES,
	ETH_SS_PHY_STATS,
	ETH_SS_PHY_TUNABLES,
	ETH_SS_LINK_MODES,
	ETH_SS_MSG_CLASSES,
	ETH_SS_WOL_MODES,
	ETH_SS_SOF_TIMESTAMPING,
	ETH_SS_TS_TX_TYPES,
	ETH_SS_TS_RX_FILTERS,
	ETH_SS_UDP_TUNNEL_TYPES,
	ETH_SS_STATS_STD,
	ETH_SS_STATS_ETH_PHY,
	ETH_SS_STATS_ETH_MAC,
	ETH_SS_STATS_ETH_CTRL,
	ETH_SS_STATS_RMON,

	/* add new स्थिरants above here */
	ETH_SS_COUNT
पूर्ण;

/**
 * काष्ठा ethtool_gstrings - string set क्रम data tagging
 * @cmd: Command number = %ETHTOOL_GSTRINGS
 * @string_set: String set ID; one of &क्रमागत ethtool_stringset
 * @len: On वापस, the number of strings in the string set
 * @data: Buffer क्रम strings.  Each string is null-padded to a size of
 *	%ETH_GSTRING_LEN.
 *
 * Users must use %ETHTOOL_GSSET_INFO to find the number of strings in
 * the string set.  They must allocate a buffer of the appropriate
 * size immediately following this काष्ठाure.
 */
काष्ठा ethtool_gstrings अणु
	__u32	cmd;
	__u32	string_set;
	__u32	len;
	__u8	data[0];
पूर्ण;

/**
 * काष्ठा ethtool_sset_info - string set inक्रमmation
 * @cmd: Command number = %ETHTOOL_GSSET_INFO
 * @reserved: Reserved क्रम future use; see the note on reserved space.
 * @sset_mask: On entry, a biपंचांगask of string sets to query, with bits
 *	numbered according to &क्रमागत ethtool_stringset.  On वापस, a
 *	biपंचांगask of those string sets queried that are supported.
 * @data: Buffer क्रम string set sizes.  On वापस, this contains the
 *	size of each string set that was queried and supported, in
 *	order of ID.
 *
 * Example: The user passes in @sset_mask = 0x7 (sets 0, 1, 2) and on
 * वापस @sset_mask == 0x6 (sets 1, 2).  Then @data[0] contains the
 * size of set 1 and @data[1] contains the size of set 2.
 *
 * Users must allocate a buffer of the appropriate size (4 * number of
 * sets queried) immediately following this काष्ठाure.
 */
काष्ठा ethtool_sset_info अणु
	__u32	cmd;
	__u32	reserved;
	__u64	sset_mask;
	__u32	data[0];
पूर्ण;

/**
 * क्रमागत ethtool_test_flags - flags definition of ethtool_test
 * @ETH_TEST_FL_OFFLINE: अगर set perक्रमm online and offline tests, otherwise
 *	only online tests.
 * @ETH_TEST_FL_FAILED: Driver set this flag अगर test fails.
 * @ETH_TEST_FL_EXTERNAL_LB: Application request to perक्रमm बाह्यal loopback
 *	test.
 * @ETH_TEST_FL_EXTERNAL_LB_DONE: Driver perक्रमmed the बाह्यal loopback test
 */

क्रमागत ethtool_test_flags अणु
	ETH_TEST_FL_OFFLINE	= (1 << 0),
	ETH_TEST_FL_FAILED	= (1 << 1),
	ETH_TEST_FL_EXTERNAL_LB	= (1 << 2),
	ETH_TEST_FL_EXTERNAL_LB_DONE	= (1 << 3),
पूर्ण;

/**
 * काष्ठा ethtool_test - device self-test invocation
 * @cmd: Command number = %ETHTOOL_TEST
 * @flags: A biपंचांगask of flags from &क्रमागत ethtool_test_flags.  Some
 *	flags may be set by the user on entry; others may be set by
 *	the driver on वापस.
 * @reserved: Reserved क्रम future use; see the note on reserved space.
 * @len: On वापस, the number of test results
 * @data: Array of test results
 *
 * Users must use %ETHTOOL_GSSET_INFO or %ETHTOOL_GDRVINFO to find the
 * number of test results that will be वापसed.  They must allocate a
 * buffer of the appropriate size (8 * number of results) immediately
 * following this काष्ठाure.
 */
काष्ठा ethtool_test अणु
	__u32	cmd;
	__u32	flags;
	__u32	reserved;
	__u32	len;
	__u64	data[0];
पूर्ण;

/**
 * काष्ठा ethtool_stats - device-specअगरic statistics
 * @cmd: Command number = %ETHTOOL_GSTATS
 * @n_stats: On वापस, the number of statistics
 * @data: Array of statistics
 *
 * Users must use %ETHTOOL_GSSET_INFO or %ETHTOOL_GDRVINFO to find the
 * number of statistics that will be वापसed.  They must allocate a
 * buffer of the appropriate size (8 * number of statistics)
 * immediately following this काष्ठाure.
 */
काष्ठा ethtool_stats अणु
	__u32	cmd;
	__u32	n_stats;
	__u64	data[0];
पूर्ण;

/**
 * काष्ठा ethtool_perm_addr - permanent hardware address
 * @cmd: Command number = %ETHTOOL_GPERMADDR
 * @size: On entry, the size of the buffer.  On वापस, the size of the
 *	address.  The command fails अगर the buffer is too small.
 * @data: Buffer क्रम the address
 *
 * Users must allocate the buffer immediately following this काष्ठाure.
 * A buffer size of %MAX_ADDR_LEN should be sufficient क्रम any address
 * type.
 */
काष्ठा ethtool_perm_addr अणु
	__u32	cmd;
	__u32	size;
	__u8	data[0];
पूर्ण;

/* boolean flags controlling per-पूर्णांकerface behavior अक्षरacteristics.
 * When पढ़ोing, the flag indicates whether or not a certain behavior
 * is enabled/present.  When writing, the flag indicates whether
 * or not the driver should turn on (set) or off (clear) a behavior.
 *
 * Some behaviors may पढ़ो-only (unconditionally असलent or present).
 * If such is the हाल, वापस EINVAL in the set-flags operation अगर the
 * flag dअगरfers from the पढ़ो-only value.
 */
क्रमागत ethtool_flags अणु
	ETH_FLAG_TXVLAN		= (1 << 7),	/* TX VLAN offload enabled */
	ETH_FLAG_RXVLAN		= (1 << 8),	/* RX VLAN offload enabled */
	ETH_FLAG_LRO		= (1 << 15),	/* LRO is enabled */
	ETH_FLAG_NTUPLE		= (1 << 27),	/* N-tuple filters enabled */
	ETH_FLAG_RXHASH		= (1 << 28),
पूर्ण;

/* The following काष्ठाures are क्रम supporting RX network flow
 * classअगरication and RX n-tuple configuration. Note, all multibyte
 * fields, e.g., ip4src, ip4dst, psrc, pdst, spi, etc. are expected to
 * be in network byte order.
 */

/**
 * काष्ठा ethtool_tcpip4_spec - flow specअगरication क्रम TCP/IPv4 etc.
 * @ip4src: Source host
 * @ip4dst: Destination host
 * @psrc: Source port
 * @pdst: Destination port
 * @tos: Type-of-service
 *
 * This can be used to specअगरy a TCP/IPv4, UDP/IPv4 or SCTP/IPv4 flow.
 */
काष्ठा ethtool_tcpip4_spec अणु
	__be32	ip4src;
	__be32	ip4dst;
	__be16	psrc;
	__be16	pdst;
	__u8    tos;
पूर्ण;

/**
 * काष्ठा ethtool_ah_espip4_spec - flow specअगरication क्रम IPsec/IPv4
 * @ip4src: Source host
 * @ip4dst: Destination host
 * @spi: Security parameters index
 * @tos: Type-of-service
 *
 * This can be used to specअगरy an IPsec transport or tunnel over IPv4.
 */
काष्ठा ethtool_ah_espip4_spec अणु
	__be32	ip4src;
	__be32	ip4dst;
	__be32	spi;
	__u8    tos;
पूर्ण;

#घोषणा	ETH_RX_NFC_IP4	1

/**
 * काष्ठा ethtool_usrip4_spec - general flow specअगरication क्रम IPv4
 * @ip4src: Source host
 * @ip4dst: Destination host
 * @l4_4_bytes: First 4 bytes of transport (layer 4) header
 * @tos: Type-of-service
 * @ip_ver: Value must be %ETH_RX_NFC_IP4; mask must be 0
 * @proto: Transport protocol number; mask must be 0
 */
काष्ठा ethtool_usrip4_spec अणु
	__be32	ip4src;
	__be32	ip4dst;
	__be32	l4_4_bytes;
	__u8    tos;
	__u8    ip_ver;
	__u8    proto;
पूर्ण;

/**
 * काष्ठा ethtool_tcpip6_spec - flow specअगरication क्रम TCP/IPv6 etc.
 * @ip6src: Source host
 * @ip6dst: Destination host
 * @psrc: Source port
 * @pdst: Destination port
 * @tclass: Traffic Class
 *
 * This can be used to specअगरy a TCP/IPv6, UDP/IPv6 or SCTP/IPv6 flow.
 */
काष्ठा ethtool_tcpip6_spec अणु
	__be32	ip6src[4];
	__be32	ip6dst[4];
	__be16	psrc;
	__be16	pdst;
	__u8    tclass;
पूर्ण;

/**
 * काष्ठा ethtool_ah_espip6_spec - flow specअगरication क्रम IPsec/IPv6
 * @ip6src: Source host
 * @ip6dst: Destination host
 * @spi: Security parameters index
 * @tclass: Traffic Class
 *
 * This can be used to specअगरy an IPsec transport or tunnel over IPv6.
 */
काष्ठा ethtool_ah_espip6_spec अणु
	__be32	ip6src[4];
	__be32	ip6dst[4];
	__be32	spi;
	__u8    tclass;
पूर्ण;

/**
 * काष्ठा ethtool_usrip6_spec - general flow specअगरication क्रम IPv6
 * @ip6src: Source host
 * @ip6dst: Destination host
 * @l4_4_bytes: First 4 bytes of transport (layer 4) header
 * @tclass: Traffic Class
 * @l4_proto: Transport protocol number (nexthdr after any Extension Headers)
 */
काष्ठा ethtool_usrip6_spec अणु
	__be32	ip6src[4];
	__be32	ip6dst[4];
	__be32	l4_4_bytes;
	__u8    tclass;
	__u8    l4_proto;
पूर्ण;

जोड़ ethtool_flow_जोड़ अणु
	काष्ठा ethtool_tcpip4_spec		tcp_ip4_spec;
	काष्ठा ethtool_tcpip4_spec		udp_ip4_spec;
	काष्ठा ethtool_tcpip4_spec		sctp_ip4_spec;
	काष्ठा ethtool_ah_espip4_spec		ah_ip4_spec;
	काष्ठा ethtool_ah_espip4_spec		esp_ip4_spec;
	काष्ठा ethtool_usrip4_spec		usr_ip4_spec;
	काष्ठा ethtool_tcpip6_spec		tcp_ip6_spec;
	काष्ठा ethtool_tcpip6_spec		udp_ip6_spec;
	काष्ठा ethtool_tcpip6_spec		sctp_ip6_spec;
	काष्ठा ethtool_ah_espip6_spec		ah_ip6_spec;
	काष्ठा ethtool_ah_espip6_spec		esp_ip6_spec;
	काष्ठा ethtool_usrip6_spec		usr_ip6_spec;
	काष्ठा ethhdr				ether_spec;
	__u8					hdata[52];
पूर्ण;

/**
 * काष्ठा ethtool_flow_ext - additional RX flow fields
 * @h_dest: destination MAC address
 * @vlan_etype: VLAN EtherType
 * @vlan_tci: VLAN tag control inक्रमmation
 * @data: user defined data
 * @padding: Reserved क्रम future use; see the note on reserved space.
 *
 * Note, @vlan_etype, @vlan_tci, and @data are only valid अगर %FLOW_EXT
 * is set in &काष्ठा ethtool_rx_flow_spec @flow_type.
 * @h_dest is valid अगर %FLOW_MAC_EXT is set.
 */
काष्ठा ethtool_flow_ext अणु
	__u8		padding[2];
	अचिन्हित अक्षर	h_dest[ETH_ALEN];
	__be16		vlan_etype;
	__be16		vlan_tci;
	__be32		data[2];
पूर्ण;

/**
 * काष्ठा ethtool_rx_flow_spec - classअगरication rule क्रम RX flows
 * @flow_type: Type of match to perक्रमm, e.g. %TCP_V4_FLOW
 * @h_u: Flow fields to match (dependent on @flow_type)
 * @h_ext: Additional fields to match
 * @m_u: Masks क्रम flow field bits to be matched
 * @m_ext: Masks क्रम additional field bits to be matched
 *	Note, all additional fields must be ignored unless @flow_type
 *	includes the %FLOW_EXT or %FLOW_MAC_EXT flag
 *	(see &काष्ठा ethtool_flow_ext description).
 * @ring_cookie: RX ring/queue index to deliver to, or %RX_CLS_FLOW_DISC
 *	अगर packets should be discarded, or %RX_CLS_FLOW_WAKE अगर the
 *	packets should be used क्रम Wake-on-LAN with %WAKE_FILTER
 * @location: Location of rule in the table.  Locations must be
 *	numbered such that a flow matching multiple rules will be
 *	classअगरied according to the first (lowest numbered) rule.
 */
काष्ठा ethtool_rx_flow_spec अणु
	__u32		flow_type;
	जोड़ ethtool_flow_जोड़ h_u;
	काष्ठा ethtool_flow_ext h_ext;
	जोड़ ethtool_flow_जोड़ m_u;
	काष्ठा ethtool_flow_ext m_ext;
	__u64		ring_cookie;
	__u32		location;
पूर्ण;

/* How rings are laid out when accessing भव functions or
 * offloaded queues is device specअगरic. To allow users to करो flow
 * steering and specअगरy these queues the ring cookie is partitioned
 * पूर्णांकo a 32bit queue index with an 8 bit भव function id.
 * This also leaves the 3bytes क्रम further specअगरiers. It is possible
 * future devices may support more than 256 भव functions अगर
 * devices start supporting PCIe w/ARI. However at the moment I
 * करो not know of any devices that support this so I करो not reserve
 * space क्रम this at this समय. If a future patch consumes the next
 * byte it should be aware of this possibility.
 */
#घोषणा ETHTOOL_RX_FLOW_SPEC_RING	0x00000000FFFFFFFFLL
#घोषणा ETHTOOL_RX_FLOW_SPEC_RING_VF	0x000000FF00000000LL
#घोषणा ETHTOOL_RX_FLOW_SPEC_RING_VF_OFF 32
अटल अंतरभूत __u64 ethtool_get_flow_spec_ring(__u64 ring_cookie)
अणु
	वापस ETHTOOL_RX_FLOW_SPEC_RING & ring_cookie;
पूर्ण

अटल अंतरभूत __u64 ethtool_get_flow_spec_ring_vf(__u64 ring_cookie)
अणु
	वापस (ETHTOOL_RX_FLOW_SPEC_RING_VF & ring_cookie) >>
				ETHTOOL_RX_FLOW_SPEC_RING_VF_OFF;
पूर्ण

/**
 * काष्ठा ethtool_rxnfc - command to get or set RX flow classअगरication rules
 * @cmd: Specअगरic command number - %ETHTOOL_GRXFH, %ETHTOOL_SRXFH,
 *	%ETHTOOL_GRXRINGS, %ETHTOOL_GRXCLSRLCNT, %ETHTOOL_GRXCLSRULE,
 *	%ETHTOOL_GRXCLSRLALL, %ETHTOOL_SRXCLSRLDEL or %ETHTOOL_SRXCLSRLINS
 * @flow_type: Type of flow to be affected, e.g. %TCP_V4_FLOW
 * @data: Command-dependent value
 * @fs: Flow classअगरication rule
 * @rss_context: RSS context to be affected
 * @rule_cnt: Number of rules to be affected
 * @rule_locs: Array of used rule locations
 *
 * For %ETHTOOL_GRXFH and %ETHTOOL_SRXFH, @data is a biपंचांगask indicating
 * the fields included in the flow hash, e.g. %RXH_IP_SRC.  The following
 * काष्ठाure fields must not be used, except that अगर @flow_type includes
 * the %FLOW_RSS flag, then @rss_context determines which RSS context to
 * act on.
 *
 * For %ETHTOOL_GRXRINGS, @data is set to the number of RX rings/queues
 * on वापस.
 *
 * For %ETHTOOL_GRXCLSRLCNT, @rule_cnt is set to the number of defined
 * rules on वापस.  If @data is non-zero on वापस then it is the
 * size of the rule table, plus the flag %RX_CLS_LOC_SPECIAL अगर the
 * driver supports any special location values.  If that flag is not
 * set in @data then special location values should not be used.
 *
 * For %ETHTOOL_GRXCLSRULE, @fs.@location specअगरies the location of an
 * existing rule on entry and @fs contains the rule on वापस; अगर
 * @fs.@flow_type includes the %FLOW_RSS flag, then @rss_context is
 * filled with the RSS context ID associated with the rule.
 *
 * For %ETHTOOL_GRXCLSRLALL, @rule_cnt specअगरies the array size of the
 * user buffer क्रम @rule_locs on entry.  On वापस, @data is the size
 * of the rule table, @rule_cnt is the number of defined rules, and
 * @rule_locs contains the locations of the defined rules.  Drivers
 * must use the second parameter to get_rxnfc() instead of @rule_locs.
 *
 * For %ETHTOOL_SRXCLSRLINS, @fs specअगरies the rule to add or update.
 * @fs.@location either specअगरies the location to use or is a special
 * location value with %RX_CLS_LOC_SPECIAL flag set.  On वापस,
 * @fs.@location is the actual rule location.  If @fs.@flow_type
 * includes the %FLOW_RSS flag, @rss_context is the RSS context ID to
 * use क्रम flow spपढ़ोing traffic which matches this rule.  The value
 * from the rxfh indirection table will be added to @fs.@ring_cookie
 * to choose which ring to deliver to.
 *
 * For %ETHTOOL_SRXCLSRLDEL, @fs.@location specअगरies the location of an
 * existing rule on entry.
 *
 * A driver supporting the special location values क्रम
 * %ETHTOOL_SRXCLSRLINS may add the rule at any suitable unused
 * location, and may हटाओ a rule at a later location (lower
 * priority) that matches exactly the same set of flows.  The special
 * values are %RX_CLS_LOC_ANY, selecting any location;
 * %RX_CLS_LOC_FIRST, selecting the first suitable location (maximum
 * priority); and %RX_CLS_LOC_LAST, selecting the last suitable
 * location (minimum priority).  Additional special values may be
 * defined in future and drivers must वापस -%EINVAL क्रम any
 * unrecognised value.
 */
काष्ठा ethtool_rxnfc अणु
	__u32				cmd;
	__u32				flow_type;
	__u64				data;
	काष्ठा ethtool_rx_flow_spec	fs;
	जोड़ अणु
		__u32			rule_cnt;
		__u32			rss_context;
	पूर्ण;
	__u32				rule_locs[0];
पूर्ण;


/**
 * काष्ठा ethtool_rxfh_indir - command to get or set RX flow hash indirection
 * @cmd: Specअगरic command number - %ETHTOOL_GRXFHINसूची or %ETHTOOL_SRXFHINसूची
 * @size: On entry, the array size of the user buffer, which may be zero.
 *	On वापस from %ETHTOOL_GRXFHINसूची, the array size of the hardware
 *	indirection table.
 * @ring_index: RX ring/queue index क्रम each hash value
 *
 * For %ETHTOOL_GRXFHINसूची, a @size of zero means that only the size
 * should be वापसed.  For %ETHTOOL_SRXFHINसूची, a @size of zero means
 * the table should be reset to शेष values.  This last feature
 * is not supported by the original implementations.
 */
काष्ठा ethtool_rxfh_indir अणु
	__u32	cmd;
	__u32	size;
	__u32	ring_index[0];
पूर्ण;

/**
 * काष्ठा ethtool_rxfh - command to get/set RX flow hash indir or/and hash key.
 * @cmd: Specअगरic command number - %ETHTOOL_GRSSH or %ETHTOOL_SRSSH
 * @rss_context: RSS context identअगरier.  Context 0 is the शेष क्रम normal
 *	traffic; other contexts can be referenced as the destination क्रम RX flow
 *	classअगरication rules.  %ETH_RXFH_CONTEXT_ALLOC is used with command
 *	%ETHTOOL_SRSSH to allocate a new RSS context; on वापस this field will
 *	contain the ID of the newly allocated context.
 * @indir_size: On entry, the array size of the user buffer क्रम the
 *	indirection table, which may be zero, or (क्रम %ETHTOOL_SRSSH),
 *	%ETH_RXFH_INसूची_NO_CHANGE.  On वापस from %ETHTOOL_GRSSH,
 *	the array size of the hardware indirection table.
 * @key_size: On entry, the array size of the user buffer क्रम the hash key,
 *	which may be zero.  On वापस from %ETHTOOL_GRSSH, the size of the
 *	hardware hash key.
 * @hfunc: Defines the current RSS hash function used by HW (or to be set to).
 *	Valid values are one of the %ETH_RSS_HASH_*.
 * @rsvd8: Reserved क्रम future use; see the note on reserved space.
 * @rsvd32: Reserved क्रम future use; see the note on reserved space.
 * @rss_config: RX ring/queue index क्रम each hash value i.e., indirection table
 *	of @indir_size __u32 elements, followed by hash key of @key_size
 *	bytes.
 *
 * For %ETHTOOL_GRSSH, a @indir_size and key_size of zero means that only the
 * size should be वापसed.  For %ETHTOOL_SRSSH, an @indir_size of
 * %ETH_RXFH_INसूची_NO_CHANGE means that indir table setting is not requested
 * and a @indir_size of zero means the indir table should be reset to शेष
 * values (अगर @rss_context == 0) or that the RSS context should be deleted.
 * An hfunc of zero means that hash function setting is not requested.
 */
काष्ठा ethtool_rxfh अणु
	__u32   cmd;
	__u32	rss_context;
	__u32   indir_size;
	__u32   key_size;
	__u8	hfunc;
	__u8	rsvd8[3];
	__u32	rsvd32;
	__u32   rss_config[0];
पूर्ण;
#घोषणा ETH_RXFH_CONTEXT_ALLOC		0xffffffff
#घोषणा ETH_RXFH_INसूची_NO_CHANGE	0xffffffff

/**
 * काष्ठा ethtool_rx_ntuple_flow_spec - specअगरication क्रम RX flow filter
 * @flow_type: Type of match to perक्रमm, e.g. %TCP_V4_FLOW
 * @h_u: Flow field values to match (dependent on @flow_type)
 * @m_u: Masks क्रम flow field value bits to be ignored
 * @vlan_tag: VLAN tag to match
 * @vlan_tag_mask: Mask क्रम VLAN tag bits to be ignored
 * @data: Driver-dependent data to match
 * @data_mask: Mask क्रम driver-dependent data bits to be ignored
 * @action: RX ring/queue index to deliver to (non-negative) or other action
 *	(negative, e.g. %ETHTOOL_RXNTUPLE_ACTION_DROP)
 *
 * For flow types %TCP_V4_FLOW, %UDP_V4_FLOW and %SCTP_V4_FLOW, where
 * a field value and mask are both zero this is treated as अगर all mask
 * bits are set i.e. the field is ignored.
 */
काष्ठा ethtool_rx_ntuple_flow_spec अणु
	__u32		 flow_type;
	जोड़ अणु
		काष्ठा ethtool_tcpip4_spec		tcp_ip4_spec;
		काष्ठा ethtool_tcpip4_spec		udp_ip4_spec;
		काष्ठा ethtool_tcpip4_spec		sctp_ip4_spec;
		काष्ठा ethtool_ah_espip4_spec		ah_ip4_spec;
		काष्ठा ethtool_ah_espip4_spec		esp_ip4_spec;
		काष्ठा ethtool_usrip4_spec		usr_ip4_spec;
		काष्ठा ethhdr				ether_spec;
		__u8					hdata[72];
	पूर्ण h_u, m_u;

	__u16	        vlan_tag;
	__u16	        vlan_tag_mask;
	__u64		data;
	__u64		data_mask;

	__s32		action;
#घोषणा ETHTOOL_RXNTUPLE_ACTION_DROP	(-1)	/* drop packet */
#घोषणा ETHTOOL_RXNTUPLE_ACTION_CLEAR	(-2)	/* clear filter */
पूर्ण;

/**
 * काष्ठा ethtool_rx_ntuple - command to set or clear RX flow filter
 * @cmd: Command number - %ETHTOOL_SRXNTUPLE
 * @fs: Flow filter specअगरication
 */
काष्ठा ethtool_rx_ntuple अणु
	__u32					cmd;
	काष्ठा ethtool_rx_ntuple_flow_spec	fs;
पूर्ण;

#घोषणा ETHTOOL_FLASH_MAX_खाताNAME	128
क्रमागत ethtool_flash_op_type अणु
	ETHTOOL_FLASH_ALL_REGIONS	= 0,
पूर्ण;

/* क्रम passing firmware flashing related parameters */
काष्ठा ethtool_flash अणु
	__u32	cmd;
	__u32	region;
	अक्षर	data[ETHTOOL_FLASH_MAX_खाताNAME];
पूर्ण;

/**
 * काष्ठा ethtool_dump - used क्रम retrieving, setting device dump
 * @cmd: Command number - %ETHTOOL_GET_DUMP_FLAG, %ETHTOOL_GET_DUMP_DATA, or
 * 	%ETHTOOL_SET_DUMP
 * @version: FW version of the dump, filled in by driver
 * @flag: driver dependent flag क्रम dump setting, filled in by driver during
 *        get and filled in by ethtool क्रम set operation.
 *        flag must be initialized by macro ETH_FW_DUMP_DISABLE value when
 *        firmware dump is disabled.
 * @len: length of dump data, used as the length of the user buffer on entry to
 * 	 %ETHTOOL_GET_DUMP_DATA and this is वापसed as dump length by driver
 * 	 क्रम %ETHTOOL_GET_DUMP_FLAG command
 * @data: data collected क्रम get dump data operation
 */
काष्ठा ethtool_dump अणु
	__u32	cmd;
	__u32	version;
	__u32	flag;
	__u32	len;
	__u8	data[0];
पूर्ण;

#घोषणा ETH_FW_DUMP_DISABLE 0

/* क्रम वापसing and changing feature sets */

/**
 * काष्ठा ethtool_get_features_block - block with state of 32 features
 * @available: mask of changeable features
 * @requested: mask of features requested to be enabled अगर possible
 * @active: mask of currently enabled features
 * @never_changed: mask of features not changeable क्रम any device
 */
काष्ठा ethtool_get_features_block अणु
	__u32	available;
	__u32	requested;
	__u32	active;
	__u32	never_changed;
पूर्ण;

/**
 * काष्ठा ethtool_gfeatures - command to get state of device's features
 * @cmd: command number = %ETHTOOL_GFEATURES
 * @size: On entry, the number of elements in the features[] array;
 *	on वापस, the number of elements in features[] needed to hold
 *	all features
 * @features: state of features
 */
काष्ठा ethtool_gfeatures अणु
	__u32	cmd;
	__u32	size;
	काष्ठा ethtool_get_features_block features[0];
पूर्ण;

/**
 * काष्ठा ethtool_set_features_block - block with request क्रम 32 features
 * @valid: mask of features to be changed
 * @requested: values of features to be changed
 */
काष्ठा ethtool_set_features_block अणु
	__u32	valid;
	__u32	requested;
पूर्ण;

/**
 * काष्ठा ethtool_sfeatures - command to request change in device's features
 * @cmd: command number = %ETHTOOL_SFEATURES
 * @size: array size of the features[] array
 * @features: feature change masks
 */
काष्ठा ethtool_sfeatures अणु
	__u32	cmd;
	__u32	size;
	काष्ठा ethtool_set_features_block features[0];
पूर्ण;

/**
 * काष्ठा ethtool_ts_info - holds a device's बारtamping and PHC association
 * @cmd: command number = %ETHTOOL_GET_TS_INFO
 * @so_बारtamping: bit mask of the sum of the supported SO_TIMESTAMPING flags
 * @phc_index: device index of the associated PHC, or -1 अगर there is none
 * @tx_types: bit mask of the supported hwtstamp_tx_types क्रमागतeration values
 * @tx_reserved: Reserved क्रम future use; see the note on reserved space.
 * @rx_filters: bit mask of the supported hwtstamp_rx_filters क्रमागतeration values
 * @rx_reserved: Reserved क्रम future use; see the note on reserved space.
 *
 * The bits in the 'tx_types' and 'rx_filters' fields correspond to
 * the 'hwtstamp_tx_types' and 'hwtstamp_rx_filters' क्रमागतeration values,
 * respectively.  For example, अगर the device supports HWTSTAMP_TX_ON,
 * then (1 << HWTSTAMP_TX_ON) in 'tx_types' will be set.
 *
 * Drivers should only report the filters they actually support without
 * upscaling in the SIOCSHWTSTAMP ioctl. If the SIOCSHWSTAMP request क्रम
 * HWTSTAMP_FILTER_V1_SYNC is supported by HWTSTAMP_FILTER_V1_EVENT, then the
 * driver should only report HWTSTAMP_FILTER_V1_EVENT in this op.
 */
काष्ठा ethtool_ts_info अणु
	__u32	cmd;
	__u32	so_बारtamping;
	__s32	phc_index;
	__u32	tx_types;
	__u32	tx_reserved[3];
	__u32	rx_filters;
	__u32	rx_reserved[3];
पूर्ण;

/*
 * %ETHTOOL_SFEATURES changes features present in features[].valid to the
 * values of corresponding bits in features[].requested. Bits in .requested
 * not set in .valid or not changeable are ignored.
 *
 * Returns %EINVAL when .valid contains undefined or never-changeable bits
 * or size is not equal to required number of features words (32-bit blocks).
 * Returns >= 0 अगर request was completed; bits set in the value mean:
 *   %ETHTOOL_F_UNSUPPORTED - there were bits set in .valid that are not
 *	changeable (not present in %ETHTOOL_GFEATURES' features[].available)
 *	those bits were ignored.
 *   %ETHTOOL_F_WISH - some or all changes requested were recorded but the
 *      resulting state of bits masked by .valid is not equal to .requested.
 *      Probably there are other device-specअगरic स्थिरraपूर्णांकs on some features
 *      in the set. When %ETHTOOL_F_UNSUPPORTED is set, .valid is considered
 *      here as though ignored bits were cleared.
 *   %ETHTOOL_F_COMPAT - some or all changes requested were made by calling
 *      compatibility functions. Requested offload state cannot be properly
 *      managed by kernel.
 *
 * Meaning of bits in the masks are obtained by %ETHTOOL_GSSET_INFO (number of
 * bits in the arrays - always multiple of 32) and %ETHTOOL_GSTRINGS commands
 * क्रम ETH_SS_FEATURES string set. First entry in the table corresponds to least
 * signअगरicant bit in features[0] fields. Empty strings mark undefined features.
 */
क्रमागत ethtool_sfeatures_retval_bits अणु
	ETHTOOL_F_UNSUPPORTED__BIT,
	ETHTOOL_F_WISH__BIT,
	ETHTOOL_F_COMPAT__BIT,
पूर्ण;

#घोषणा ETHTOOL_F_UNSUPPORTED   (1 << ETHTOOL_F_UNSUPPORTED__BIT)
#घोषणा ETHTOOL_F_WISH          (1 << ETHTOOL_F_WISH__BIT)
#घोषणा ETHTOOL_F_COMPAT        (1 << ETHTOOL_F_COMPAT__BIT)

#घोषणा MAX_NUM_QUEUE		4096

/**
 * काष्ठा ethtool_per_queue_op - apply sub command to the queues in mask.
 * @cmd: ETHTOOL_PERQUEUE
 * @sub_command: the sub command which apply to each queues
 * @queue_mask: Biपंचांगap of the queues which sub command apply to
 * @data: A complete command काष्ठाure following क्रम each of the queues addressed
 */
काष्ठा ethtool_per_queue_op अणु
	__u32	cmd;
	__u32	sub_command;
	__u32	queue_mask[__KERNEL_DIV_ROUND_UP(MAX_NUM_QUEUE, 32)];
	अक्षर	data[];
पूर्ण;

/**
 * काष्ठा ethtool_fecparam - Ethernet Forward Error Correction parameters
 * @cmd: Command number = %ETHTOOL_GFECPARAM or %ETHTOOL_SFECPARAM
 * @active_fec: FEC mode which is active on the port, single bit set, GET only.
 * @fec: Biपंचांगask of configured FEC modes.
 * @reserved: Reserved क्रम future extensions, ignore on GET, ग_लिखो 0 क्रम SET.
 *
 * Note that @reserved was never validated on input and ethtool user space
 * left it uninitialized when calling SET. Hence going क्रमward it can only be
 * used to वापस a value to userspace with GET.
 *
 * FEC modes supported by the device can be पढ़ो via %ETHTOOL_GLINKSETTINGS.
 * FEC settings are configured by link स्वतःnegotiation whenever it's enabled.
 * With स्वतःneg on %ETHTOOL_GFECPARAM can be used to पढ़ो the current mode.
 *
 * When स्वतःneg is disabled %ETHTOOL_SFECPARAM controls the FEC settings.
 * It is recommended that drivers only accept a single bit set in @fec.
 * When multiple bits are set in @fec drivers may pick mode in an implementation
 * dependent way. Drivers should reject mixing %ETHTOOL_FEC_AUTO_BIT with other
 * FEC modes, because it's unclear whether in this हाल other modes स्थिरrain
 * AUTO or are independent choices.
 * Drivers must reject SET requests अगर they support none of the requested modes.
 *
 * If device करोes not support FEC drivers may use %ETHTOOL_FEC_NONE instead
 * of वापसing %EOPNOTSUPP from %ETHTOOL_GFECPARAM.
 *
 * See क्रमागत ethtool_fec_config_bits क्रम definition of valid bits क्रम both
 * @fec and @active_fec.
 */
काष्ठा ethtool_fecparam अणु
	__u32   cmd;
	/* biपंचांगask of FEC modes */
	__u32   active_fec;
	__u32   fec;
	__u32   reserved;
पूर्ण;

/**
 * क्रमागत ethtool_fec_config_bits - flags definition of ethtool_fec_configuration
 * @ETHTOOL_FEC_NONE_BIT: FEC mode configuration is not supported. Should not
 *			be used together with other bits. GET only.
 * @ETHTOOL_FEC_AUTO_BIT: Select शेष/best FEC mode स्वतःmatically, usually
 *			based link mode and SFP parameters पढ़ो from module's
 *			EEPROM. This bit करोes _not_ mean स्वतःnegotiation.
 * @ETHTOOL_FEC_OFF_BIT: No FEC Mode
 * @ETHTOOL_FEC_RS_BIT: Reed-Solomon FEC Mode
 * @ETHTOOL_FEC_BASER_BIT: Base-R/Reed-Solomon FEC Mode
 * @ETHTOOL_FEC_LLRS_BIT: Low Latency Reed Solomon FEC Mode (25G/50G Ethernet
 *			Consortium)
 */
क्रमागत ethtool_fec_config_bits अणु
	ETHTOOL_FEC_NONE_BIT,
	ETHTOOL_FEC_AUTO_BIT,
	ETHTOOL_FEC_OFF_BIT,
	ETHTOOL_FEC_RS_BIT,
	ETHTOOL_FEC_BASER_BIT,
	ETHTOOL_FEC_LLRS_BIT,
पूर्ण;

#घोषणा ETHTOOL_FEC_NONE		(1 << ETHTOOL_FEC_NONE_BIT)
#घोषणा ETHTOOL_FEC_AUTO		(1 << ETHTOOL_FEC_AUTO_BIT)
#घोषणा ETHTOOL_FEC_OFF			(1 << ETHTOOL_FEC_OFF_BIT)
#घोषणा ETHTOOL_FEC_RS			(1 << ETHTOOL_FEC_RS_BIT)
#घोषणा ETHTOOL_FEC_BASER		(1 << ETHTOOL_FEC_BASER_BIT)
#घोषणा ETHTOOL_FEC_LLRS		(1 << ETHTOOL_FEC_LLRS_BIT)

/* CMDs currently supported */
#घोषणा ETHTOOL_GSET		0x00000001 /* DEPRECATED, Get settings.
					    * Please use ETHTOOL_GLINKSETTINGS
					    */
#घोषणा ETHTOOL_SSET		0x00000002 /* DEPRECATED, Set settings.
					    * Please use ETHTOOL_SLINKSETTINGS
					    */
#घोषणा ETHTOOL_GDRVINFO	0x00000003 /* Get driver info. */
#घोषणा ETHTOOL_GREGS		0x00000004 /* Get NIC रेजिस्टरs. */
#घोषणा ETHTOOL_GWOL		0x00000005 /* Get wake-on-lan options. */
#घोषणा ETHTOOL_SWOL		0x00000006 /* Set wake-on-lan options. */
#घोषणा ETHTOOL_GMSGLVL		0x00000007 /* Get driver message level */
#घोषणा ETHTOOL_SMSGLVL		0x00000008 /* Set driver msg level. */
#घोषणा ETHTOOL_NWAY_RST	0x00000009 /* Restart स्वतःnegotiation. */
/* Get link status क्रम host, i.e. whether the पूर्णांकerface *and* the
 * physical port (अगर there is one) are up (ethtool_value). */
#घोषणा ETHTOOL_GLINK		0x0000000a
#घोषणा ETHTOOL_GEEPROM		0x0000000b /* Get EEPROM data */
#घोषणा ETHTOOL_SEEPROM		0x0000000c /* Set EEPROM data. */
#घोषणा ETHTOOL_GCOALESCE	0x0000000e /* Get coalesce config */
#घोषणा ETHTOOL_SCOALESCE	0x0000000f /* Set coalesce config. */
#घोषणा ETHTOOL_GRINGPARAM	0x00000010 /* Get ring parameters */
#घोषणा ETHTOOL_SRINGPARAM	0x00000011 /* Set ring parameters. */
#घोषणा ETHTOOL_GPAUSEPARAM	0x00000012 /* Get छोड़ो parameters */
#घोषणा ETHTOOL_SPAUSEPARAM	0x00000013 /* Set छोड़ो parameters. */
#घोषणा ETHTOOL_GRXCSUM		0x00000014 /* Get RX hw csum enable (ethtool_value) */
#घोषणा ETHTOOL_SRXCSUM		0x00000015 /* Set RX hw csum enable (ethtool_value) */
#घोषणा ETHTOOL_GTXCSUM		0x00000016 /* Get TX hw csum enable (ethtool_value) */
#घोषणा ETHTOOL_STXCSUM		0x00000017 /* Set TX hw csum enable (ethtool_value) */
#घोषणा ETHTOOL_GSG		0x00000018 /* Get scatter-gather enable
					    * (ethtool_value) */
#घोषणा ETHTOOL_SSG		0x00000019 /* Set scatter-gather enable
					    * (ethtool_value). */
#घोषणा ETHTOOL_TEST		0x0000001a /* execute NIC self-test. */
#घोषणा ETHTOOL_GSTRINGS	0x0000001b /* get specअगरied string set */
#घोषणा ETHTOOL_PHYS_ID		0x0000001c /* identअगरy the NIC */
#घोषणा ETHTOOL_GSTATS		0x0000001d /* get NIC-specअगरic statistics */
#घोषणा ETHTOOL_GTSO		0x0000001e /* Get TSO enable (ethtool_value) */
#घोषणा ETHTOOL_STSO		0x0000001f /* Set TSO enable (ethtool_value) */
#घोषणा ETHTOOL_GPERMADDR	0x00000020 /* Get permanent hardware address */
#घोषणा ETHTOOL_GUFO		0x00000021 /* Get UFO enable (ethtool_value) */
#घोषणा ETHTOOL_SUFO		0x00000022 /* Set UFO enable (ethtool_value) */
#घोषणा ETHTOOL_GGSO		0x00000023 /* Get GSO enable (ethtool_value) */
#घोषणा ETHTOOL_SGSO		0x00000024 /* Set GSO enable (ethtool_value) */
#घोषणा ETHTOOL_GFLAGS		0x00000025 /* Get flags biपंचांगap(ethtool_value) */
#घोषणा ETHTOOL_SFLAGS		0x00000026 /* Set flags biपंचांगap(ethtool_value) */
#घोषणा ETHTOOL_GPFLAGS		0x00000027 /* Get driver-निजी flags biपंचांगap */
#घोषणा ETHTOOL_SPFLAGS		0x00000028 /* Set driver-निजी flags biपंचांगap */

#घोषणा ETHTOOL_GRXFH		0x00000029 /* Get RX flow hash configuration */
#घोषणा ETHTOOL_SRXFH		0x0000002a /* Set RX flow hash configuration */
#घोषणा ETHTOOL_GGRO		0x0000002b /* Get GRO enable (ethtool_value) */
#घोषणा ETHTOOL_SGRO		0x0000002c /* Set GRO enable (ethtool_value) */
#घोषणा ETHTOOL_GRXRINGS	0x0000002d /* Get RX rings available क्रम LB */
#घोषणा ETHTOOL_GRXCLSRLCNT	0x0000002e /* Get RX class rule count */
#घोषणा ETHTOOL_GRXCLSRULE	0x0000002f /* Get RX classअगरication rule */
#घोषणा ETHTOOL_GRXCLSRLALL	0x00000030 /* Get all RX classअगरication rule */
#घोषणा ETHTOOL_SRXCLSRLDEL	0x00000031 /* Delete RX classअगरication rule */
#घोषणा ETHTOOL_SRXCLSRLINS	0x00000032 /* Insert RX classअगरication rule */
#घोषणा ETHTOOL_FLASHDEV	0x00000033 /* Flash firmware to device */
#घोषणा ETHTOOL_RESET		0x00000034 /* Reset hardware */
#घोषणा ETHTOOL_SRXNTUPLE	0x00000035 /* Add an n-tuple filter to device */
#घोषणा ETHTOOL_GRXNTUPLE	0x00000036 /* deprecated */
#घोषणा ETHTOOL_GSSET_INFO	0x00000037 /* Get string set info */
#घोषणा ETHTOOL_GRXFHINसूची	0x00000038 /* Get RX flow hash indir'n table */
#घोषणा ETHTOOL_SRXFHINसूची	0x00000039 /* Set RX flow hash indir'n table */

#घोषणा ETHTOOL_GFEATURES	0x0000003a /* Get device offload settings */
#घोषणा ETHTOOL_SFEATURES	0x0000003b /* Change device offload settings */
#घोषणा ETHTOOL_GCHANNELS	0x0000003c /* Get no of channels */
#घोषणा ETHTOOL_SCHANNELS	0x0000003d /* Set no of channels */
#घोषणा ETHTOOL_SET_DUMP	0x0000003e /* Set dump settings */
#घोषणा ETHTOOL_GET_DUMP_FLAG	0x0000003f /* Get dump settings */
#घोषणा ETHTOOL_GET_DUMP_DATA	0x00000040 /* Get dump data */
#घोषणा ETHTOOL_GET_TS_INFO	0x00000041 /* Get समय stamping and PHC info */
#घोषणा ETHTOOL_GMODULEINFO	0x00000042 /* Get plug-in module inक्रमmation */
#घोषणा ETHTOOL_GMODULEEEPROM	0x00000043 /* Get plug-in module eeprom */
#घोषणा ETHTOOL_GEEE		0x00000044 /* Get EEE settings */
#घोषणा ETHTOOL_SEEE		0x00000045 /* Set EEE settings */

#घोषणा ETHTOOL_GRSSH		0x00000046 /* Get RX flow hash configuration */
#घोषणा ETHTOOL_SRSSH		0x00000047 /* Set RX flow hash configuration */
#घोषणा ETHTOOL_GTUNABLE	0x00000048 /* Get tunable configuration */
#घोषणा ETHTOOL_STUNABLE	0x00000049 /* Set tunable configuration */
#घोषणा ETHTOOL_GPHYSTATS	0x0000004a /* get PHY-specअगरic statistics */

#घोषणा ETHTOOL_PERQUEUE	0x0000004b /* Set per queue options */

#घोषणा ETHTOOL_GLINKSETTINGS	0x0000004c /* Get ethtool_link_settings */
#घोषणा ETHTOOL_SLINKSETTINGS	0x0000004d /* Set ethtool_link_settings */
#घोषणा ETHTOOL_PHY_GTUNABLE	0x0000004e /* Get PHY tunable configuration */
#घोषणा ETHTOOL_PHY_STUNABLE	0x0000004f /* Set PHY tunable configuration */
#घोषणा ETHTOOL_GFECPARAM	0x00000050 /* Get FEC settings */
#घोषणा ETHTOOL_SFECPARAM	0x00000051 /* Set FEC settings */

/* compatibility with older code */
#घोषणा SPARC_ETH_GSET		ETHTOOL_GSET
#घोषणा SPARC_ETH_SSET		ETHTOOL_SSET

/* Link mode bit indices */
क्रमागत ethtool_link_mode_bit_indices अणु
	ETHTOOL_LINK_MODE_10baseT_Half_BIT	= 0,
	ETHTOOL_LINK_MODE_10baseT_Full_BIT	= 1,
	ETHTOOL_LINK_MODE_100baseT_Half_BIT	= 2,
	ETHTOOL_LINK_MODE_100baseT_Full_BIT	= 3,
	ETHTOOL_LINK_MODE_1000baseT_Half_BIT	= 4,
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT	= 5,
	ETHTOOL_LINK_MODE_Autoneg_BIT		= 6,
	ETHTOOL_LINK_MODE_TP_BIT		= 7,
	ETHTOOL_LINK_MODE_AUI_BIT		= 8,
	ETHTOOL_LINK_MODE_MII_BIT		= 9,
	ETHTOOL_LINK_MODE_FIBRE_BIT		= 10,
	ETHTOOL_LINK_MODE_BNC_BIT		= 11,
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT	= 12,
	ETHTOOL_LINK_MODE_Pause_BIT		= 13,
	ETHTOOL_LINK_MODE_Asym_Pause_BIT	= 14,
	ETHTOOL_LINK_MODE_2500baseX_Full_BIT	= 15,
	ETHTOOL_LINK_MODE_Backplane_BIT		= 16,
	ETHTOOL_LINK_MODE_1000baseKX_Full_BIT	= 17,
	ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT	= 18,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT	= 19,
	ETHTOOL_LINK_MODE_10000baseR_FEC_BIT	= 20,
	ETHTOOL_LINK_MODE_20000baseMLD2_Full_BIT = 21,
	ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT	= 22,
	ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT	= 23,
	ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT	= 24,
	ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT	= 25,
	ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT	= 26,
	ETHTOOL_LINK_MODE_56000baseKR4_Full_BIT	= 27,
	ETHTOOL_LINK_MODE_56000baseCR4_Full_BIT	= 28,
	ETHTOOL_LINK_MODE_56000baseSR4_Full_BIT	= 29,
	ETHTOOL_LINK_MODE_56000baseLR4_Full_BIT	= 30,
	ETHTOOL_LINK_MODE_25000baseCR_Full_BIT	= 31,

	/* Last allowed bit क्रम __ETHTOOL_LINK_MODE_LEGACY_MASK is bit
	 * 31. Please करो NOT define any SUPPORTED_* or ADVERTISED_*
	 * macro क्रम bits > 31. The only way to use indices > 31 is to
	 * use the new ETHTOOL_GLINKSETTINGS/ETHTOOL_SLINKSETTINGS API.
	 */

	ETHTOOL_LINK_MODE_25000baseKR_Full_BIT	= 32,
	ETHTOOL_LINK_MODE_25000baseSR_Full_BIT	= 33,
	ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT	= 34,
	ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT	= 35,
	ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT	= 36,
	ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT	= 37,
	ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT	= 38,
	ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT	= 39,
	ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT		= 40,
	ETHTOOL_LINK_MODE_1000baseX_Full_BIT	= 41,
	ETHTOOL_LINK_MODE_10000baseCR_Full_BIT	= 42,
	ETHTOOL_LINK_MODE_10000baseSR_Full_BIT	= 43,
	ETHTOOL_LINK_MODE_10000baseLR_Full_BIT	= 44,
	ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT	= 45,
	ETHTOOL_LINK_MODE_10000baseER_Full_BIT	= 46,
	ETHTOOL_LINK_MODE_2500baseT_Full_BIT	= 47,
	ETHTOOL_LINK_MODE_5000baseT_Full_BIT	= 48,

	ETHTOOL_LINK_MODE_FEC_NONE_BIT	= 49,
	ETHTOOL_LINK_MODE_FEC_RS_BIT	= 50,
	ETHTOOL_LINK_MODE_FEC_BASER_BIT	= 51,
	ETHTOOL_LINK_MODE_50000baseKR_Full_BIT		 = 52,
	ETHTOOL_LINK_MODE_50000baseSR_Full_BIT		 = 53,
	ETHTOOL_LINK_MODE_50000baseCR_Full_BIT		 = 54,
	ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT	 = 55,
	ETHTOOL_LINK_MODE_50000baseDR_Full_BIT		 = 56,
	ETHTOOL_LINK_MODE_100000baseKR2_Full_BIT	 = 57,
	ETHTOOL_LINK_MODE_100000baseSR2_Full_BIT	 = 58,
	ETHTOOL_LINK_MODE_100000baseCR2_Full_BIT	 = 59,
	ETHTOOL_LINK_MODE_100000baseLR2_ER2_FR2_Full_BIT = 60,
	ETHTOOL_LINK_MODE_100000baseDR2_Full_BIT	 = 61,
	ETHTOOL_LINK_MODE_200000baseKR4_Full_BIT	 = 62,
	ETHTOOL_LINK_MODE_200000baseSR4_Full_BIT	 = 63,
	ETHTOOL_LINK_MODE_200000baseLR4_ER4_FR4_Full_BIT = 64,
	ETHTOOL_LINK_MODE_200000baseDR4_Full_BIT	 = 65,
	ETHTOOL_LINK_MODE_200000baseCR4_Full_BIT	 = 66,
	ETHTOOL_LINK_MODE_100baseT1_Full_BIT		 = 67,
	ETHTOOL_LINK_MODE_1000baseT1_Full_BIT		 = 68,
	ETHTOOL_LINK_MODE_400000baseKR8_Full_BIT	 = 69,
	ETHTOOL_LINK_MODE_400000baseSR8_Full_BIT	 = 70,
	ETHTOOL_LINK_MODE_400000baseLR8_ER8_FR8_Full_BIT = 71,
	ETHTOOL_LINK_MODE_400000baseDR8_Full_BIT	 = 72,
	ETHTOOL_LINK_MODE_400000baseCR8_Full_BIT	 = 73,
	ETHTOOL_LINK_MODE_FEC_LLRS_BIT			 = 74,
	ETHTOOL_LINK_MODE_100000baseKR_Full_BIT		 = 75,
	ETHTOOL_LINK_MODE_100000baseSR_Full_BIT		 = 76,
	ETHTOOL_LINK_MODE_100000baseLR_ER_FR_Full_BIT	 = 77,
	ETHTOOL_LINK_MODE_100000baseCR_Full_BIT		 = 78,
	ETHTOOL_LINK_MODE_100000baseDR_Full_BIT		 = 79,
	ETHTOOL_LINK_MODE_200000baseKR2_Full_BIT	 = 80,
	ETHTOOL_LINK_MODE_200000baseSR2_Full_BIT	 = 81,
	ETHTOOL_LINK_MODE_200000baseLR2_ER2_FR2_Full_BIT = 82,
	ETHTOOL_LINK_MODE_200000baseDR2_Full_BIT	 = 83,
	ETHTOOL_LINK_MODE_200000baseCR2_Full_BIT	 = 84,
	ETHTOOL_LINK_MODE_400000baseKR4_Full_BIT	 = 85,
	ETHTOOL_LINK_MODE_400000baseSR4_Full_BIT	 = 86,
	ETHTOOL_LINK_MODE_400000baseLR4_ER4_FR4_Full_BIT = 87,
	ETHTOOL_LINK_MODE_400000baseDR4_Full_BIT	 = 88,
	ETHTOOL_LINK_MODE_400000baseCR4_Full_BIT	 = 89,
	ETHTOOL_LINK_MODE_100baseFX_Half_BIT		 = 90,
	ETHTOOL_LINK_MODE_100baseFX_Full_BIT		 = 91,
	/* must be last entry */
	__ETHTOOL_LINK_MODE_MASK_NBITS
पूर्ण;

#घोषणा __ETHTOOL_LINK_MODE_LEGACY_MASK(base_name)	\
	(1UL << (ETHTOOL_LINK_MODE_ ## base_name ## _BIT))

/* DEPRECATED macros. Please migrate to
 * ETHTOOL_GLINKSETTINGS/ETHTOOL_SLINKSETTINGS API. Please करो NOT
 * define any new SUPPORTED_* macro क्रम bits > 31.
 */
#घोषणा SUPPORTED_10baseT_Half		__ETHTOOL_LINK_MODE_LEGACY_MASK(10baseT_Half)
#घोषणा SUPPORTED_10baseT_Full		__ETHTOOL_LINK_MODE_LEGACY_MASK(10baseT_Full)
#घोषणा SUPPORTED_100baseT_Half		__ETHTOOL_LINK_MODE_LEGACY_MASK(100baseT_Half)
#घोषणा SUPPORTED_100baseT_Full		__ETHTOOL_LINK_MODE_LEGACY_MASK(100baseT_Full)
#घोषणा SUPPORTED_1000baseT_Half	__ETHTOOL_LINK_MODE_LEGACY_MASK(1000baseT_Half)
#घोषणा SUPPORTED_1000baseT_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(1000baseT_Full)
#घोषणा SUPPORTED_Autoneg		__ETHTOOL_LINK_MODE_LEGACY_MASK(Autoneg)
#घोषणा SUPPORTED_TP			__ETHTOOL_LINK_MODE_LEGACY_MASK(TP)
#घोषणा SUPPORTED_AUI			__ETHTOOL_LINK_MODE_LEGACY_MASK(AUI)
#घोषणा SUPPORTED_MII			__ETHTOOL_LINK_MODE_LEGACY_MASK(MII)
#घोषणा SUPPORTED_FIBRE			__ETHTOOL_LINK_MODE_LEGACY_MASK(FIBRE)
#घोषणा SUPPORTED_BNC			__ETHTOOL_LINK_MODE_LEGACY_MASK(BNC)
#घोषणा SUPPORTED_10000baseT_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseT_Full)
#घोषणा SUPPORTED_Pause			__ETHTOOL_LINK_MODE_LEGACY_MASK(Pause)
#घोषणा SUPPORTED_Asym_Pause		__ETHTOOL_LINK_MODE_LEGACY_MASK(Asym_Pause)
#घोषणा SUPPORTED_2500baseX_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(2500baseX_Full)
#घोषणा SUPPORTED_Backplane		__ETHTOOL_LINK_MODE_LEGACY_MASK(Backplane)
#घोषणा SUPPORTED_1000baseKX_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(1000baseKX_Full)
#घोषणा SUPPORTED_10000baseKX4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseKX4_Full)
#घोषणा SUPPORTED_10000baseKR_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseKR_Full)
#घोषणा SUPPORTED_10000baseR_FEC	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseR_FEC)
#घोषणा SUPPORTED_20000baseMLD2_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(20000baseMLD2_Full)
#घोषणा SUPPORTED_20000baseKR2_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(20000baseKR2_Full)
#घोषणा SUPPORTED_40000baseKR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseKR4_Full)
#घोषणा SUPPORTED_40000baseCR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseCR4_Full)
#घोषणा SUPPORTED_40000baseSR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseSR4_Full)
#घोषणा SUPPORTED_40000baseLR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseLR4_Full)
#घोषणा SUPPORTED_56000baseKR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseKR4_Full)
#घोषणा SUPPORTED_56000baseCR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseCR4_Full)
#घोषणा SUPPORTED_56000baseSR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseSR4_Full)
#घोषणा SUPPORTED_56000baseLR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseLR4_Full)
/* Please करो not define any new SUPPORTED_* macro क्रम bits > 31, see
 * notice above.
 */

/*
 * DEPRECATED macros. Please migrate to
 * ETHTOOL_GLINKSETTINGS/ETHTOOL_SLINKSETTINGS API. Please करो NOT
 * define any new ADERTISE_* macro क्रम bits > 31.
 */
#घोषणा ADVERTISED_10baseT_Half		__ETHTOOL_LINK_MODE_LEGACY_MASK(10baseT_Half)
#घोषणा ADVERTISED_10baseT_Full		__ETHTOOL_LINK_MODE_LEGACY_MASK(10baseT_Full)
#घोषणा ADVERTISED_100baseT_Half	__ETHTOOL_LINK_MODE_LEGACY_MASK(100baseT_Half)
#घोषणा ADVERTISED_100baseT_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(100baseT_Full)
#घोषणा ADVERTISED_1000baseT_Half	__ETHTOOL_LINK_MODE_LEGACY_MASK(1000baseT_Half)
#घोषणा ADVERTISED_1000baseT_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(1000baseT_Full)
#घोषणा ADVERTISED_Autoneg		__ETHTOOL_LINK_MODE_LEGACY_MASK(Autoneg)
#घोषणा ADVERTISED_TP			__ETHTOOL_LINK_MODE_LEGACY_MASK(TP)
#घोषणा ADVERTISED_AUI			__ETHTOOL_LINK_MODE_LEGACY_MASK(AUI)
#घोषणा ADVERTISED_MII			__ETHTOOL_LINK_MODE_LEGACY_MASK(MII)
#घोषणा ADVERTISED_FIBRE		__ETHTOOL_LINK_MODE_LEGACY_MASK(FIBRE)
#घोषणा ADVERTISED_BNC			__ETHTOOL_LINK_MODE_LEGACY_MASK(BNC)
#घोषणा ADVERTISED_10000baseT_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseT_Full)
#घोषणा ADVERTISED_Pause		__ETHTOOL_LINK_MODE_LEGACY_MASK(Pause)
#घोषणा ADVERTISED_Asym_Pause		__ETHTOOL_LINK_MODE_LEGACY_MASK(Asym_Pause)
#घोषणा ADVERTISED_2500baseX_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(2500baseX_Full)
#घोषणा ADVERTISED_Backplane		__ETHTOOL_LINK_MODE_LEGACY_MASK(Backplane)
#घोषणा ADVERTISED_1000baseKX_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(1000baseKX_Full)
#घोषणा ADVERTISED_10000baseKX4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseKX4_Full)
#घोषणा ADVERTISED_10000baseKR_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseKR_Full)
#घोषणा ADVERTISED_10000baseR_FEC	__ETHTOOL_LINK_MODE_LEGACY_MASK(10000baseR_FEC)
#घोषणा ADVERTISED_20000baseMLD2_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(20000baseMLD2_Full)
#घोषणा ADVERTISED_20000baseKR2_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(20000baseKR2_Full)
#घोषणा ADVERTISED_40000baseKR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseKR4_Full)
#घोषणा ADVERTISED_40000baseCR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseCR4_Full)
#घोषणा ADVERTISED_40000baseSR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseSR4_Full)
#घोषणा ADVERTISED_40000baseLR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(40000baseLR4_Full)
#घोषणा ADVERTISED_56000baseKR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseKR4_Full)
#घोषणा ADVERTISED_56000baseCR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseCR4_Full)
#घोषणा ADVERTISED_56000baseSR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseSR4_Full)
#घोषणा ADVERTISED_56000baseLR4_Full	__ETHTOOL_LINK_MODE_LEGACY_MASK(56000baseLR4_Full)
/* Please करो not define any new ADVERTISED_* macro क्रम bits > 31, see
 * notice above.
 */

/* The following are all involved in क्रमcing a particular link
 * mode क्रम the device क्रम setting things.  When getting the
 * devices settings, these indicate the current mode and whether
 * it was क्रमced up पूर्णांकo this mode or स्वतःnegotiated.
 */

/* The क्रमced speed, in units of 1Mb. All values 0 to पूर्णांक_उच्च are legal.
 * Update drivers/net/phy/phy.c:phy_speed_to_str() and
 * drivers/net/bonding/bond_3ad.c:__get_link_speed() when adding new values.
 */
#घोषणा SPEED_10		10
#घोषणा SPEED_100		100
#घोषणा SPEED_1000		1000
#घोषणा SPEED_2500		2500
#घोषणा SPEED_5000		5000
#घोषणा SPEED_10000		10000
#घोषणा SPEED_14000		14000
#घोषणा SPEED_20000		20000
#घोषणा SPEED_25000		25000
#घोषणा SPEED_40000		40000
#घोषणा SPEED_50000		50000
#घोषणा SPEED_56000		56000
#घोषणा SPEED_100000		100000
#घोषणा SPEED_200000		200000
#घोषणा SPEED_400000		400000

#घोषणा SPEED_UNKNOWN		-1

अटल अंतरभूत पूर्णांक ethtool_validate_speed(__u32 speed)
अणु
	वापस speed <= पूर्णांक_उच्च || speed == (__u32)SPEED_UNKNOWN;
पूर्ण

/* Duplex, half or full. */
#घोषणा DUPLEX_HALF		0x00
#घोषणा DUPLEX_FULL		0x01
#घोषणा DUPLEX_UNKNOWN		0xff

अटल अंतरभूत पूर्णांक ethtool_validate_duplex(__u8 duplex)
अणु
	चयन (duplex) अणु
	हाल DUPLEX_HALF:
	हाल DUPLEX_FULL:
	हाल DUPLEX_UNKNOWN:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MASTER_SLAVE_CFG_UNSUPPORTED		0
#घोषणा MASTER_SLAVE_CFG_UNKNOWN		1
#घोषणा MASTER_SLAVE_CFG_MASTER_PREFERRED	2
#घोषणा MASTER_SLAVE_CFG_SLAVE_PREFERRED	3
#घोषणा MASTER_SLAVE_CFG_MASTER_FORCE		4
#घोषणा MASTER_SLAVE_CFG_SLAVE_FORCE		5
#घोषणा MASTER_SLAVE_STATE_UNSUPPORTED		0
#घोषणा MASTER_SLAVE_STATE_UNKNOWN		1
#घोषणा MASTER_SLAVE_STATE_MASTER		2
#घोषणा MASTER_SLAVE_STATE_SLAVE		3
#घोषणा MASTER_SLAVE_STATE_ERR			4

/* Which connector port. */
#घोषणा PORT_TP			0x00
#घोषणा PORT_AUI		0x01
#घोषणा PORT_MII		0x02
#घोषणा PORT_FIBRE		0x03
#घोषणा PORT_BNC		0x04
#घोषणा PORT_DA			0x05
#घोषणा PORT_NONE		0xef
#घोषणा PORT_OTHER		0xff

/* Which transceiver to use. */
#घोषणा XCVR_INTERNAL		0x00 /* PHY and MAC are in the same package */
#घोषणा XCVR_EXTERNAL		0x01 /* PHY and MAC are in dअगरferent packages */
#घोषणा XCVR_DUMMY1		0x02
#घोषणा XCVR_DUMMY2		0x03
#घोषणा XCVR_DUMMY3		0x04

/* Enable or disable स्वतःnegotiation. */
#घोषणा AUTONEG_DISABLE		0x00
#घोषणा AUTONEG_ENABLE		0x01

/* MDI or MDI-X status/control - अगर MDI/MDI_X/AUTO is set then
 * the driver is required to renegotiate link
 */
#घोषणा ETH_TP_MDI_INVALID	0x00 /* status: unknown; control: unsupported */
#घोषणा ETH_TP_MDI		0x01 /* status: MDI;     control: क्रमce MDI */
#घोषणा ETH_TP_MDI_X		0x02 /* status: MDI-X;   control: क्रमce MDI-X */
#घोषणा ETH_TP_MDI_AUTO		0x03 /*                  control: स्वतः-select */

/* Wake-On-Lan options. */
#घोषणा WAKE_PHY		(1 << 0)
#घोषणा WAKE_UCAST		(1 << 1)
#घोषणा WAKE_MCAST		(1 << 2)
#घोषणा WAKE_BCAST		(1 << 3)
#घोषणा WAKE_ARP		(1 << 4)
#घोषणा WAKE_MAGIC		(1 << 5)
#घोषणा WAKE_MAGICSECURE	(1 << 6) /* only meaningful अगर WAKE_MAGIC */
#घोषणा WAKE_FILTER		(1 << 7)

#घोषणा WOL_MODE_COUNT		8

/* L2-L4 network traffic flow types */
#घोषणा	TCP_V4_FLOW	0x01	/* hash or spec (tcp_ip4_spec) */
#घोषणा	UDP_V4_FLOW	0x02	/* hash or spec (udp_ip4_spec) */
#घोषणा	SCTP_V4_FLOW	0x03	/* hash or spec (sctp_ip4_spec) */
#घोषणा	AH_ESP_V4_FLOW	0x04	/* hash only */
#घोषणा	TCP_V6_FLOW	0x05	/* hash or spec (tcp_ip6_spec; nfc only) */
#घोषणा	UDP_V6_FLOW	0x06	/* hash or spec (udp_ip6_spec; nfc only) */
#घोषणा	SCTP_V6_FLOW	0x07	/* hash or spec (sctp_ip6_spec; nfc only) */
#घोषणा	AH_ESP_V6_FLOW	0x08	/* hash only */
#घोषणा	AH_V4_FLOW	0x09	/* hash or spec (ah_ip4_spec) */
#घोषणा	ESP_V4_FLOW	0x0a	/* hash or spec (esp_ip4_spec) */
#घोषणा	AH_V6_FLOW	0x0b	/* hash or spec (ah_ip6_spec; nfc only) */
#घोषणा	ESP_V6_FLOW	0x0c	/* hash or spec (esp_ip6_spec; nfc only) */
#घोषणा	IPV4_USER_FLOW	0x0d	/* spec only (usr_ip4_spec) */
#घोषणा	IP_USER_FLOW	IPV4_USER_FLOW
#घोषणा	IPV6_USER_FLOW	0x0e	/* spec only (usr_ip6_spec; nfc only) */
#घोषणा	IPV4_FLOW	0x10	/* hash only */
#घोषणा	IPV6_FLOW	0x11	/* hash only */
#घोषणा	ETHER_FLOW	0x12	/* spec only (ether_spec) */
/* Flag to enable additional fields in काष्ठा ethtool_rx_flow_spec */
#घोषणा	FLOW_EXT	0x80000000
#घोषणा	FLOW_MAC_EXT	0x40000000
/* Flag to enable RSS spपढ़ोing of traffic matching rule (nfc only) */
#घोषणा	FLOW_RSS	0x20000000

/* L3-L4 network traffic flow hash options */
#घोषणा	RXH_L2DA	(1 << 1)
#घोषणा	RXH_VLAN	(1 << 2)
#घोषणा	RXH_L3_PROTO	(1 << 3)
#घोषणा	RXH_IP_SRC	(1 << 4)
#घोषणा	RXH_IP_DST	(1 << 5)
#घोषणा	RXH_L4_B_0_1	(1 << 6) /* src port in हाल of TCP/UDP/SCTP */
#घोषणा	RXH_L4_B_2_3	(1 << 7) /* dst port in हाल of TCP/UDP/SCTP */
#घोषणा	RXH_DISCARD	(1 << 31)

#घोषणा	RX_CLS_FLOW_DISC	0xffffffffffffffffULL
#घोषणा RX_CLS_FLOW_WAKE	0xfffffffffffffffeULL

/* Special RX classअगरication rule insert location values */
#घोषणा RX_CLS_LOC_SPECIAL	0x80000000	/* flag */
#घोषणा RX_CLS_LOC_ANY		0xffffffff
#घोषणा RX_CLS_LOC_FIRST	0xfffffffe
#घोषणा RX_CLS_LOC_LAST		0xfffffffd

/* EEPROM Standards क्रम plug in modules */
#घोषणा ETH_MODULE_SFF_8079		0x1
#घोषणा ETH_MODULE_SFF_8079_LEN		256
#घोषणा ETH_MODULE_SFF_8472		0x2
#घोषणा ETH_MODULE_SFF_8472_LEN		512
#घोषणा ETH_MODULE_SFF_8636		0x3
#घोषणा ETH_MODULE_SFF_8636_LEN		256
#घोषणा ETH_MODULE_SFF_8436		0x4
#घोषणा ETH_MODULE_SFF_8436_LEN		256

#घोषणा ETH_MODULE_SFF_8636_MAX_LEN     640
#घोषणा ETH_MODULE_SFF_8436_MAX_LEN     640

/* Reset flags */
/* The reset() operation must clear the flags क्रम the components which
 * were actually reset.  On successful वापस, the flags indicate the
 * components which were not reset, either because they करो not exist
 * in the hardware or because they cannot be reset independently.  The
 * driver must never reset any components that were not requested.
 */
क्रमागत ethtool_reset_flags अणु
	/* These flags represent components dedicated to the पूर्णांकerface
	 * the command is addressed to.  Shअगरt any flag left by
	 * ETH_RESET_SHARED_SHIFT to reset a shared component of the
	 * same type.
	 */
	ETH_RESET_MGMT		= 1 << 0,	/* Management processor */
	ETH_RESET_IRQ		= 1 << 1,	/* Interrupt requester */
	ETH_RESET_DMA		= 1 << 2,	/* DMA engine */
	ETH_RESET_FILTER	= 1 << 3,	/* Filtering/flow direction */
	ETH_RESET_OFFLOAD	= 1 << 4,	/* Protocol offload */
	ETH_RESET_MAC		= 1 << 5,	/* Media access controller */
	ETH_RESET_PHY		= 1 << 6,	/* Transceiver/PHY */
	ETH_RESET_RAM		= 1 << 7,	/* RAM shared between
						 * multiple components */
	ETH_RESET_AP		= 1 << 8,	/* Application processor */

	ETH_RESET_DEDICATED	= 0x0000ffff,	/* All components dedicated to
						 * this पूर्णांकerface */
	ETH_RESET_ALL		= 0xffffffff,	/* All components used by this
						 * पूर्णांकerface, even अगर shared */
पूर्ण;
#घोषणा ETH_RESET_SHARED_SHIFT	16


/**
 * काष्ठा ethtool_link_settings - link control and status
 *
 * IMPORTANT, Backward compatibility notice: When implementing new
 *	user-space tools, please first try %ETHTOOL_GLINKSETTINGS, and
 *	अगर it succeeds use %ETHTOOL_SLINKSETTINGS to change link
 *	settings; करो not use %ETHTOOL_SSET अगर %ETHTOOL_GLINKSETTINGS
 *	succeeded: stick to %ETHTOOL_GLINKSETTINGS/%SLINKSETTINGS in
 *	that हाल.  Conversely, अगर %ETHTOOL_GLINKSETTINGS fails, use
 *	%ETHTOOL_GSET to query and %ETHTOOL_SSET to change link
 *	settings; करो not use %ETHTOOL_SLINKSETTINGS अगर
 *	%ETHTOOL_GLINKSETTINGS failed: stick to
 *	%ETHTOOL_GSET/%ETHTOOL_SSET in that हाल.
 *
 * @cmd: Command number = %ETHTOOL_GLINKSETTINGS or %ETHTOOL_SLINKSETTINGS
 * @speed: Link speed (Mbps)
 * @duplex: Duplex mode; one of %DUPLEX_*
 * @port: Physical connector type; one of %PORT_*
 * @phy_address: MDIO address of PHY (transceiver); 0 or 255 अगर not
 *	applicable.  For clause 45 PHYs this is the PRTAD.
 * @स्वतःneg: Enable/disable स्वतःnegotiation and स्वतः-detection;
 *	either %AUTONEG_DISABLE or %AUTONEG_ENABLE
 * @mdio_support: Biपंचांगask of %ETH_MDIO_SUPPORTS_* flags क्रम the MDIO
 *	protocols supported by the पूर्णांकerface; 0 अगर unknown.
 *	Read-only.
 * @eth_tp_mdix: Ethernet twisted-pair MDI(-X) status; one of
 *	%ETH_TP_MDI_*.  If the status is unknown or not applicable, the
 *	value will be %ETH_TP_MDI_INVALID.  Read-only.
 * @eth_tp_mdix_ctrl: Ethernet twisted pair MDI(-X) control; one of
 *	%ETH_TP_MDI_*.  If MDI(-X) control is not implemented, पढ़ोs
 *	yield %ETH_TP_MDI_INVALID and ग_लिखोs may be ignored or rejected.
 *	When written successfully, the link should be renegotiated अगर
 *	necessary.
 * @link_mode_masks_nwords: Number of 32-bit words क्रम each of the
 *	supported, advertising, lp_advertising link mode biपंचांगaps. For
 *	%ETHTOOL_GLINKSETTINGS: on entry, number of words passed by user
 *	(>= 0); on वापस, अगर handshake in progress, negative अगर
 *	request size unsupported by kernel: असलolute value indicates
 *	kernel expected size and all the other fields but cmd
 *	are 0; otherwise (handshake completed), strictly positive
 *	to indicate size used by kernel and cmd field stays
 *	%ETHTOOL_GLINKSETTINGS, all other fields populated by driver. For
 *	%ETHTOOL_SLINKSETTINGS: must be valid on entry, ie. a positive
 *	value वापसed previously by %ETHTOOL_GLINKSETTINGS, otherwise
 *	refused. For drivers: ignore this field (use kernel's
 *	__ETHTOOL_LINK_MODE_MASK_NBITS instead), any change to it will
 *	be overwritten by kernel.
 * @supported: Biपंचांगap with each bit meaning given by
 *	%ethtool_link_mode_bit_indices क्रम the link modes, physical
 *	connectors and other link features क्रम which the पूर्णांकerface
 *	supports स्वतःnegotiation or स्वतः-detection.  Read-only.
 * @advertising: Biपंचांगap with each bit meaning given by
 *	%ethtool_link_mode_bit_indices क्रम the link modes, physical
 *	connectors and other link features that are advertised through
 *	स्वतःnegotiation or enabled क्रम स्वतः-detection.
 * @lp_advertising: Biपंचांगap with each bit meaning given by
 *	%ethtool_link_mode_bit_indices क्रम the link modes, and other
 *	link features that the link partner advertised through
 *	स्वतःnegotiation; 0 अगर unknown or not applicable.  Read-only.
 * @transceiver: Used to distinguish dअगरferent possible PHY types,
 *	reported consistently by PHYLIB.  Read-only.
 * @master_slave_cfg: Master/slave port mode.
 * @master_slave_state: Master/slave port state.
 * @reserved: Reserved क्रम future use; see the note on reserved space.
 * @reserved1: Reserved क्रम future use; see the note on reserved space.
 * @link_mode_masks: Variable length biपंचांगaps.
 *
 * If स्वतःnegotiation is disabled, the speed and @duplex represent the
 * fixed link mode and are writable अगर the driver supports multiple
 * link modes.  If it is enabled then they are पढ़ो-only; अगर the link
 * is up they represent the negotiated link mode; अगर the link is करोwn,
 * the speed is 0, %SPEED_UNKNOWN or the highest enabled speed and
 * @duplex is %DUPLEX_UNKNOWN or the best enabled duplex mode.
 *
 * Some hardware पूर्णांकerfaces may have multiple PHYs and/or physical
 * connectors fitted or करो not allow the driver to detect which are
 * fitted.  For these पूर्णांकerfaces @port and/or @phy_address may be
 * writable, possibly dependent on @स्वतःneg being %AUTONEG_DISABLE.
 * Otherwise, attempts to ग_लिखो dअगरferent values may be ignored or
 * rejected.
 *
 * Deprecated %ethtool_cmd fields transceiver, maxtxpkt and maxrxpkt
 * are not available in %ethtool_link_settings. These fields will be
 * always set to zero in %ETHTOOL_GSET reply and %ETHTOOL_SSET will
 * fail अगर any of them is set to non-zero value.
 *
 * Users should assume that all fields not marked पढ़ो-only are
 * writable and subject to validation by the driver.  They should use
 * %ETHTOOL_GLINKSETTINGS to get the current values beक्रमe making specअगरic
 * changes and then applying them with %ETHTOOL_SLINKSETTINGS.
 *
 * Drivers that implement %get_link_ksettings and/or
 * %set_link_ksettings should ignore the @cmd
 * and @link_mode_masks_nwords fields (any change to them overwritten
 * by kernel), and rely only on kernel's पूर्णांकernal
 * %__ETHTOOL_LINK_MODE_MASK_NBITS and
 * %ethtool_link_mode_mask_t. Drivers that implement
 * %set_link_ksettings() should validate all fields other than @cmd
 * and @link_mode_masks_nwords that are not described as पढ़ो-only or
 * deprecated, and must ignore all fields described as पढ़ो-only.
 */
काष्ठा ethtool_link_settings अणु
	__u32	cmd;
	__u32	speed;
	__u8	duplex;
	__u8	port;
	__u8	phy_address;
	__u8	स्वतःneg;
	__u8	mdio_support;
	__u8	eth_tp_mdix;
	__u8	eth_tp_mdix_ctrl;
	__s8	link_mode_masks_nwords;
	__u8	transceiver;
	__u8	master_slave_cfg;
	__u8	master_slave_state;
	__u8	reserved1[1];
	__u32	reserved[7];
	__u32	link_mode_masks[0];
	/* layout of link_mode_masks fields:
	 * __u32 map_supported[link_mode_masks_nwords];
	 * __u32 map_advertising[link_mode_masks_nwords];
	 * __u32 map_lp_advertising[link_mode_masks_nwords];
	 */
पूर्ण;
#पूर्ण_अगर /* _UAPI_LINUX_ETHTOOL_H */
