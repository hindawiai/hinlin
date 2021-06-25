<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx Ethernet चयन single-chip definition
 *
 * Copyright (c) 2008 Marvell Semiconductor
 */

#अगर_अघोषित _MV88E6XXX_CHIP_H
#घोषणा _MV88E6XXX_CHIP_H

#समावेश <linux/idr.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/phy.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>
#समावेश <net/dsa.h>

#घोषणा MV88E6XXX_N_FID		4096

/* PVT limits क्रम 4-bit port and 5-bit चयन */
#घोषणा MV88E6XXX_MAX_PVT_SWITCHES	32
#घोषणा MV88E6XXX_MAX_PVT_PORTS		16
#घोषणा MV88E6XXX_MAX_PVT_ENTRIES	\
	(MV88E6XXX_MAX_PVT_SWITCHES * MV88E6XXX_MAX_PVT_PORTS)

#घोषणा MV88E6XXX_MAX_GPIO	16

क्रमागत mv88e6xxx_egress_mode अणु
	MV88E6XXX_EGRESS_MODE_UNMODIFIED,
	MV88E6XXX_EGRESS_MODE_UNTAGGED,
	MV88E6XXX_EGRESS_MODE_TAGGED,
	MV88E6XXX_EGRESS_MODE_ETHERTYPE,
पूर्ण;

क्रमागत mv88e6xxx_egress_direction अणु
        MV88E6XXX_EGRESS_सूची_INGRESS,
        MV88E6XXX_EGRESS_सूची_EGRESS,
पूर्ण;

क्रमागत mv88e6xxx_frame_mode अणु
	MV88E6XXX_FRAME_MODE_NORMAL,
	MV88E6XXX_FRAME_MODE_DSA,
	MV88E6XXX_FRAME_MODE_PROVIDER,
	MV88E6XXX_FRAME_MODE_ETHERTYPE,
पूर्ण;

/* List of supported models */
क्रमागत mv88e6xxx_model अणु
	MV88E6085,
	MV88E6095,
	MV88E6097,
	MV88E6123,
	MV88E6131,
	MV88E6141,
	MV88E6161,
	MV88E6165,
	MV88E6171,
	MV88E6172,
	MV88E6175,
	MV88E6176,
	MV88E6185,
	MV88E6190,
	MV88E6190X,
	MV88E6191,
	MV88E6191X,
	MV88E6193X,
	MV88E6220,
	MV88E6240,
	MV88E6250,
	MV88E6290,
	MV88E6320,
	MV88E6321,
	MV88E6341,
	MV88E6350,
	MV88E6351,
	MV88E6352,
	MV88E6390,
	MV88E6390X,
	MV88E6393X,
पूर्ण;

क्रमागत mv88e6xxx_family अणु
	MV88E6XXX_FAMILY_NONE,
	MV88E6XXX_FAMILY_6065,	/* 6031 6035 6061 6065 */
	MV88E6XXX_FAMILY_6095,	/* 6092 6095 */
	MV88E6XXX_FAMILY_6097,	/* 6046 6085 6096 6097 */
	MV88E6XXX_FAMILY_6165,	/* 6123 6161 6165 */
	MV88E6XXX_FAMILY_6185,	/* 6108 6121 6122 6131 6152 6155 6182 6185 */
	MV88E6XXX_FAMILY_6250,	/* 6220 6250 */
	MV88E6XXX_FAMILY_6320,	/* 6320 6321 */
	MV88E6XXX_FAMILY_6341,	/* 6141 6341 */
	MV88E6XXX_FAMILY_6351,	/* 6171 6175 6350 6351 */
	MV88E6XXX_FAMILY_6352,	/* 6172 6176 6240 6352 */
	MV88E6XXX_FAMILY_6390,  /* 6190 6190X 6191 6290 6390 6390X */
	MV88E6XXX_FAMILY_6393,	/* 6191X 6193X 6393X */
पूर्ण;

/**
 * क्रमागत mv88e6xxx_edsa_support - Ethertype DSA tag support level
 * @MV88E6XXX_EDSA_UNSUPPORTED:  Device has no support क्रम EDSA tags
 * @MV88E6XXX_EDSA_UNDOCUMENTED: Documentation indicates that
 *                               egressing FORWARD frames with an EDSA
 *                               tag is reserved क्रम future use, but
 *                               empirical data shows that this mode
 *                               is supported.
 * @MV88E6XXX_EDSA_SUPPORTED:    EDSA tags are fully supported.
 */
क्रमागत mv88e6xxx_edsa_support अणु
	MV88E6XXX_EDSA_UNSUPPORTED = 0,
	MV88E6XXX_EDSA_UNDOCUMENTED,
	MV88E6XXX_EDSA_SUPPORTED,
पूर्ण;

काष्ठा mv88e6xxx_ops;

काष्ठा mv88e6xxx_info अणु
	क्रमागत mv88e6xxx_family family;
	u16 prod_num;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक num_databases;
	अचिन्हित पूर्णांक num_macs;
	अचिन्हित पूर्णांक num_ports;
	अचिन्हित पूर्णांक num_पूर्णांकernal_phys;
	अचिन्हित पूर्णांक num_gpio;
	अचिन्हित पूर्णांक max_vid;
	अचिन्हित पूर्णांक port_base_addr;
	अचिन्हित पूर्णांक phy_base_addr;
	अचिन्हित पूर्णांक global1_addr;
	अचिन्हित पूर्णांक global2_addr;
	अचिन्हित पूर्णांक age_समय_coeff;
	अचिन्हित पूर्णांक g1_irqs;
	अचिन्हित पूर्णांक g2_irqs;
	bool pvt;

	/* Mark certain ports as invalid. This is required क्रम example क्रम the
	 * MV88E6220 (which is in general a MV88E6250 with 7 ports) but the
	 * ports 2-4 are not routet to pins.
	 */
	अचिन्हित पूर्णांक invalid_port_mask;
	/* Multi-chip Addressing Mode.
	 * Some chips respond to only 2 रेजिस्टरs of its own SMI device address
	 * when it is non-zero, and use indirect access to पूर्णांकernal रेजिस्टरs.
	 */
	bool multi_chip;
	/* Dual-chip Addressing Mode
	 * Some chips respond to only half of the 32 SMI addresses,
	 * allowing two to coexist on the same SMI पूर्णांकerface.
	 */
	bool dual_chip;

	क्रमागत mv88e6xxx_edsa_support edsa_support;

	/* Mask क्रम FromPort and ToPort value of PortVec used in ATU Move
	 * operation. 0 means that the ATU Move operation is not supported.
	 */
	u8 atu_move_port_mask;
	स्थिर काष्ठा mv88e6xxx_ops *ops;

	/* Supports PTP */
	bool ptp_support;
पूर्ण;

काष्ठा mv88e6xxx_atu_entry अणु
	u8	state;
	bool	trunk;
	u16	portvec;
	u8	mac[ETH_ALEN];
पूर्ण;

काष्ठा mv88e6xxx_vtu_entry अणु
	u16	vid;
	u16	fid;
	u8	sid;
	bool	valid;
	u8	member[DSA_MAX_PORTS];
	u8	state[DSA_MAX_PORTS];
पूर्ण;

काष्ठा mv88e6xxx_bus_ops;
काष्ठा mv88e6xxx_irq_ops;
काष्ठा mv88e6xxx_gpio_ops;
काष्ठा mv88e6xxx_avb_ops;
काष्ठा mv88e6xxx_ptp_ops;

काष्ठा mv88e6xxx_irq अणु
	u16 masked;
	काष्ठा irq_chip chip;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक nirqs;
पूर्ण;

/* state flags क्रम mv88e6xxx_port_hwtstamp::state */
क्रमागत अणु
	MV88E6XXX_HWTSTAMP_ENABLED,
	MV88E6XXX_HWTSTAMP_TX_IN_PROGRESS,
पूर्ण;

काष्ठा mv88e6xxx_port_hwtstamp अणु
	/* Port index */
	पूर्णांक port_id;

	/* Timestamping state */
	अचिन्हित दीर्घ state;

	/* Resources क्रम receive बारtamping */
	काष्ठा sk_buff_head rx_queue;
	काष्ठा sk_buff_head rx_queue2;

	/* Resources क्रम transmit बारtamping */
	अचिन्हित दीर्घ tx_tstamp_start;
	काष्ठा sk_buff *tx_skb;
	u16 tx_seq_id;

	/* Current बारtamp configuration */
	काष्ठा hwtstamp_config tstamp_config;
पूर्ण;

क्रमागत mv88e6xxx_policy_mapping अणु
	MV88E6XXX_POLICY_MAPPING_DA,
	MV88E6XXX_POLICY_MAPPING_SA,
	MV88E6XXX_POLICY_MAPPING_VTU,
	MV88E6XXX_POLICY_MAPPING_ETYPE,
	MV88E6XXX_POLICY_MAPPING_PPPOE,
	MV88E6XXX_POLICY_MAPPING_VBAS,
	MV88E6XXX_POLICY_MAPPING_OPT82,
	MV88E6XXX_POLICY_MAPPING_UDP,
पूर्ण;

क्रमागत mv88e6xxx_policy_action अणु
	MV88E6XXX_POLICY_ACTION_NORMAL,
	MV88E6XXX_POLICY_ACTION_MIRROR,
	MV88E6XXX_POLICY_ACTION_TRAP,
	MV88E6XXX_POLICY_ACTION_DISCARD,
पूर्ण;

काष्ठा mv88e6xxx_policy अणु
	क्रमागत mv88e6xxx_policy_mapping mapping;
	क्रमागत mv88e6xxx_policy_action action;
	काष्ठा ethtool_rx_flow_spec fs;
	u8 addr[ETH_ALEN];
	पूर्णांक port;
	u16 vid;
पूर्ण;

काष्ठा mv88e6xxx_port अणु
	काष्ठा mv88e6xxx_chip *chip;
	पूर्णांक port;
	u64 serdes_stats[2];
	u64 atu_member_violation;
	u64 atu_miss_violation;
	u64 atu_full_violation;
	u64 vtu_member_violation;
	u64 vtu_miss_violation;
	phy_पूर्णांकerface_t पूर्णांकerface;
	u8 cmode;
	bool mirror_ingress;
	bool mirror_egress;
	अचिन्हित पूर्णांक serdes_irq;
	अक्षर serdes_irq_name[64];
	काष्ठा devlink_region *region;
पूर्ण;

क्रमागत mv88e6xxx_region_id अणु
	MV88E6XXX_REGION_GLOBAL1 = 0,
	MV88E6XXX_REGION_GLOBAL2,
	MV88E6XXX_REGION_ATU,
	MV88E6XXX_REGION_VTU,
	MV88E6XXX_REGION_PVT,

	_MV88E6XXX_REGION_MAX,
पूर्ण;

काष्ठा mv88e6xxx_region_priv अणु
	क्रमागत mv88e6xxx_region_id id;
पूर्ण;

काष्ठा mv88e6xxx_chip अणु
	स्थिर काष्ठा mv88e6xxx_info *info;

	/* Currently configured tagging protocol */
	क्रमागत dsa_tag_protocol tag_protocol;

	/* The dsa_चयन this निजी काष्ठाure is related to */
	काष्ठा dsa_चयन *ds;

	/* The device this काष्ठाure is associated to */
	काष्ठा device *dev;

	/* This mutex protects the access to the चयन रेजिस्टरs */
	काष्ठा mutex reg_lock;

	/* The MII bus and the address on the bus that is used to
	 * communication with the चयन
	 */
	स्थिर काष्ठा mv88e6xxx_bus_ops *smi_ops;
	काष्ठा mii_bus *bus;
	पूर्णांक sw_addr;

	/* Handles स्वतःmatic disabling and re-enabling of the PHY
	 * polling unit.
	 */
	स्थिर काष्ठा mv88e6xxx_bus_ops *phy_ops;
	काष्ठा mutex		ppu_mutex;
	पूर्णांक			ppu_disabled;
	काष्ठा work_काष्ठा	ppu_work;
	काष्ठा समयr_list	ppu_समयr;

	/* This mutex serialises access to the statistics unit.
	 * Hold this mutex over snapshot + dump sequences.
	 */
	काष्ठा mutex	stats_mutex;

	/* A चयन may have a GPIO line tied to its reset pin. Parse
	 * this from the device tree, and use it beक्रमe perक्रमming
	 * चयन soft reset.
	 */
	काष्ठा gpio_desc *reset;

	/* set to size of eeprom अगर supported by the चयन */
	u32 eeprom_len;

	/* List of mdio busses */
	काष्ठा list_head mdios;

	/* Policy Control List IDs and rules */
	काष्ठा idr policies;

	/* There can be two पूर्णांकerrupt controllers, which are chained
	 * off a GPIO as पूर्णांकerrupt source
	 */
	काष्ठा mv88e6xxx_irq g1_irq;
	काष्ठा mv88e6xxx_irq g2_irq;
	पूर्णांक irq;
	अक्षर irq_name[64];
	पूर्णांक device_irq;
	अक्षर device_irq_name[64];
	पूर्णांक watchकरोg_irq;
	अक्षर watchकरोg_irq_name[64];

	पूर्णांक atu_prob_irq;
	अक्षर atu_prob_irq_name[64];
	पूर्णांक vtu_prob_irq;
	अक्षर vtu_prob_irq_name[64];
	काष्ठा kthपढ़ो_worker *kworker;
	काष्ठा kthपढ़ो_delayed_work irq_poll_work;

	/* GPIO resources */
	u8 gpio_data[2];

	/* This cyclecounter असलtracts the चयन PTP समय.
	 * reg_lock must be held क्रम any operation that पढ़ो()s.
	 */
	काष्ठा cyclecounter	tstamp_cc;
	काष्ठा समयcounter	tstamp_tc;
	काष्ठा delayed_work	overflow_work;

	काष्ठा ptp_घड़ी	*ptp_घड़ी;
	काष्ठा ptp_घड़ी_info	ptp_घड़ी_info;
	काष्ठा delayed_work	tai_event_work;
	काष्ठा ptp_pin_desc	pin_config[MV88E6XXX_MAX_GPIO];
	u16 trig_config;
	u16 evcap_config;
	u16 enable_count;

	/* Current ingress and egress monitor ports */
	पूर्णांक egress_dest_port;
	पूर्णांक ingress_dest_port;

	/* Per-port बारtamping resources. */
	काष्ठा mv88e6xxx_port_hwtstamp port_hwtstamp[DSA_MAX_PORTS];

	/* Array of port काष्ठाures. */
	काष्ठा mv88e6xxx_port ports[DSA_MAX_PORTS];

	/* devlink regions */
	काष्ठा devlink_region *regions[_MV88E6XXX_REGION_MAX];
पूर्ण;

काष्ठा mv88e6xxx_bus_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg, u16 *val);
	पूर्णांक (*ग_लिखो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg, u16 val);
पूर्ण;

काष्ठा mv88e6xxx_mdio_bus अणु
	काष्ठा mii_bus *bus;
	काष्ठा mv88e6xxx_chip *chip;
	काष्ठा list_head list;
	bool बाह्यal;
पूर्ण;

काष्ठा mv88e6xxx_ops अणु
	/* Switch Setup Errata, called early in the चयन setup to
	 * allow any errata actions to be perक्रमmed
	 */
	पूर्णांक (*setup_errata)(काष्ठा mv88e6xxx_chip *chip);

	पूर्णांक (*ieee_pri_map)(काष्ठा mv88e6xxx_chip *chip);
	पूर्णांक (*ip_pri_map)(काष्ठा mv88e6xxx_chip *chip);

	/* Ingress Rate Limit unit (IRL) operations */
	पूर्णांक (*irl_init_all)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

	पूर्णांक (*get_eeprom)(काष्ठा mv88e6xxx_chip *chip,
			  काष्ठा ethtool_eeprom *eeprom, u8 *data);
	पूर्णांक (*set_eeprom)(काष्ठा mv88e6xxx_chip *chip,
			  काष्ठा ethtool_eeprom *eeprom, u8 *data);

	पूर्णांक (*set_चयन_mac)(काष्ठा mv88e6xxx_chip *chip, u8 *addr);

	पूर्णांक (*phy_पढ़ो)(काष्ठा mv88e6xxx_chip *chip,
			काष्ठा mii_bus *bus,
			पूर्णांक addr, पूर्णांक reg, u16 *val);
	पूर्णांक (*phy_ग_लिखो)(काष्ठा mv88e6xxx_chip *chip,
			 काष्ठा mii_bus *bus,
			 पूर्णांक addr, पूर्णांक reg, u16 val);

	/* Priority Override Table operations */
	पूर्णांक (*pot_clear)(काष्ठा mv88e6xxx_chip *chip);

	/* PHY Polling Unit (PPU) operations */
	पूर्णांक (*ppu_enable)(काष्ठा mv88e6xxx_chip *chip);
	पूर्णांक (*ppu_disable)(काष्ठा mv88e6xxx_chip *chip);

	/* Switch Software Reset */
	पूर्णांक (*reset)(काष्ठा mv88e6xxx_chip *chip);

	/* RGMII Receive/Transmit Timing Control
	 * Add delay on PHY_INTERFACE_MODE_RGMII_*ID, no delay otherwise.
	 */
	पूर्णांक (*port_set_rgmii_delay)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    phy_पूर्णांकerface_t mode);

#घोषणा LINK_FORCED_DOWN	0
#घोषणा LINK_FORCED_UP		1
#घोषणा LINK_UNFORCED		-2

	/* Port's MAC link state
	 * Use LINK_FORCED_UP or LINK_FORCED_DOWN to क्रमce link up or करोwn,
	 * or LINK_UNFORCED क्रम normal link detection.
	 */
	पूर्णांक (*port_set_link)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक link);

	/* Synchronise the port link state with that of the SERDES
	 */
	पूर्णांक (*port_sync_link)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, अचिन्हित पूर्णांक mode, bool isup);

#घोषणा PAUSE_ON		1
#घोषणा PAUSE_OFF		0

	/* Enable/disable sending Pause */
	पूर्णांक (*port_set_छोड़ो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      पूर्णांक छोड़ो);

#घोषणा SPEED_MAX		पूर्णांक_उच्च
#घोषणा SPEED_UNFORCED		-2
#घोषणा DUPLEX_UNFORCED		-2

	/* Port's MAC speed (in Mbps) and MAC duplex mode
	 *
	 * Depending on the chip, 10, 100, 200, 1000, 2500, 10000 are valid.
	 * Use SPEED_UNFORCED क्रम normal detection, SPEED_MAX क्रम max value.
	 *
	 * Use DUPLEX_HALF or DUPLEX_FULL to क्रमce half or full duplex,
	 * or DUPLEX_UNFORCED क्रम normal duplex detection.
	 */
	पूर्णांक (*port_set_speed_duplex)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक speed, पूर्णांक duplex);

	/* What पूर्णांकerface mode should be used क्रम maximum speed? */
	phy_पूर्णांकerface_t (*port_max_speed_mode)(पूर्णांक port);

	पूर्णांक (*port_tag_remap)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

	पूर्णांक (*port_set_policy)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			       क्रमागत mv88e6xxx_policy_mapping mapping,
			       क्रमागत mv88e6xxx_policy_action action);

	पूर्णांक (*port_set_frame_mode)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   क्रमागत mv88e6xxx_frame_mode mode);
	पूर्णांक (*port_set_ucast_flood)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    bool unicast);
	पूर्णांक (*port_set_mcast_flood)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    bool multicast);
	पूर्णांक (*port_set_ether_type)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   u16 etype);
	पूर्णांक (*port_set_jumbo_size)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   माप_प्रकार size);

	पूर्णांक (*port_egress_rate_limiting)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
	पूर्णांक (*port_छोड़ो_limit)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 in,
				u8 out);
	पूर्णांक (*port_disable_learn_limit)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
	पूर्णांक (*port_disable_pri_override)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
	पूर्णांक (*port_setup_message_port)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

	/* CMODE control what PHY mode the MAC will use, eg. SGMII, RGMII, etc.
	 * Some chips allow this to be configured on specअगरic ports.
	 */
	पूर्णांक (*port_set_cmode)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      phy_पूर्णांकerface_t mode);
	पूर्णांक (*port_get_cmode)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 *cmode);

	/* Some devices have a per port रेजिस्टर indicating what is
	 * the upstream port this port should क्रमward to.
	 */
	पूर्णांक (*port_set_upstream_port)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				      पूर्णांक upstream_port);

	/* Snapshot the statistics क्रम a port. The statistics can then
	 * be पढ़ो back a leisure but still with a consistent view.
	 */
	पूर्णांक (*stats_snapshot)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

	/* Set the histogram mode क्रम statistics, when the control रेजिस्टरs
	 * are separated out of the STATS_OP रेजिस्टर.
	 */
	पूर्णांक (*stats_set_histogram)(काष्ठा mv88e6xxx_chip *chip);

	/* Return the number of strings describing statistics */
	पूर्णांक (*stats_get_sset_count)(काष्ठा mv88e6xxx_chip *chip);
	पूर्णांक (*stats_get_strings)(काष्ठा mv88e6xxx_chip *chip,  uपूर्णांक8_t *data);
	पूर्णांक (*stats_get_stats)(काष्ठा mv88e6xxx_chip *chip,  पूर्णांक port,
			       uपूर्णांक64_t *data);
	पूर्णांक (*set_cpu_port)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
	पूर्णांक (*set_egress_port)(काष्ठा mv88e6xxx_chip *chip,
			       क्रमागत mv88e6xxx_egress_direction direction,
			       पूर्णांक port);

#घोषणा MV88E6XXX_CASCADE_PORT_NONE		0xe
#घोषणा MV88E6XXX_CASCADE_PORT_MULTIPLE		0xf

	पूर्णांक (*set_cascade_port)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

	स्थिर काष्ठा mv88e6xxx_irq_ops *watchकरोg_ops;

	पूर्णांक (*mgmt_rsvd2cpu)(काष्ठा mv88e6xxx_chip *chip);

	/* Power on/off a SERDES पूर्णांकerface */
	पूर्णांक (*serdes_घातer)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			    bool up);

	/* SERDES lane mapping */
	पूर्णांक (*serdes_get_lane)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

	पूर्णांक (*serdes_pcs_get_state)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक lane, काष्ठा phylink_link_state *state);
	पूर्णांक (*serdes_pcs_config)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 पूर्णांक lane, अचिन्हित पूर्णांक mode,
				 phy_पूर्णांकerface_t पूर्णांकerface,
				 स्थिर अचिन्हित दीर्घ *advertise);
	पूर्णांक (*serdes_pcs_an_restart)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक lane);
	पूर्णांक (*serdes_pcs_link_up)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  पूर्णांक lane, पूर्णांक speed, पूर्णांक duplex);

	/* SERDES पूर्णांकerrupt handling */
	अचिन्हित पूर्णांक (*serdes_irq_mapping)(काष्ठा mv88e6xxx_chip *chip,
					   पूर्णांक port);
	पूर्णांक (*serdes_irq_enable)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
				 bool enable);
	irqवापस_t (*serdes_irq_status)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					 पूर्णांक lane);

	/* Statistics from the SERDES पूर्णांकerface */
	पूर्णांक (*serdes_get_sset_count)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
	पूर्णांक (*serdes_get_strings)(काष्ठा mv88e6xxx_chip *chip,  पूर्णांक port,
				  uपूर्णांक8_t *data);
	पूर्णांक (*serdes_get_stats)(काष्ठा mv88e6xxx_chip *chip,  पूर्णांक port,
				uपूर्णांक64_t *data);

	/* SERDES रेजिस्टरs क्रम ethtool */
	पूर्णांक (*serdes_get_regs_len)(काष्ठा mv88e6xxx_chip *chip,  पूर्णांक port);
	व्योम (*serdes_get_regs)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				व्योम *_p);

	/* Address Translation Unit operations */
	पूर्णांक (*atu_get_hash)(काष्ठा mv88e6xxx_chip *chip, u8 *hash);
	पूर्णांक (*atu_set_hash)(काष्ठा mv88e6xxx_chip *chip, u8 hash);

	/* VLAN Translation Unit operations */
	पूर्णांक (*vtu_getnext)(काष्ठा mv88e6xxx_chip *chip,
			   काष्ठा mv88e6xxx_vtu_entry *entry);
	पूर्णांक (*vtu_loadpurge)(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry);

	/* GPIO operations */
	स्थिर काष्ठा mv88e6xxx_gpio_ops *gpio_ops;

	/* Interface to the AVB/PTP रेजिस्टरs */
	स्थिर काष्ठा mv88e6xxx_avb_ops *avb_ops;

	/* Remote Management Unit operations */
	पूर्णांक (*rmu_disable)(काष्ठा mv88e6xxx_chip *chip);

	/* Precision Time Protocol operations */
	स्थिर काष्ठा mv88e6xxx_ptp_ops *ptp_ops;

	/* Phylink */
	व्योम (*phylink_validate)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 अचिन्हित दीर्घ *mask,
				 काष्ठा phylink_link_state *state);

	/* Max Frame Size */
	पूर्णांक (*set_max_frame_size)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक mtu);
पूर्ण;

काष्ठा mv88e6xxx_irq_ops अणु
	/* Action to be perक्रमmed when the पूर्णांकerrupt happens */
	पूर्णांक (*irq_action)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक irq);
	/* Setup the hardware to generate the पूर्णांकerrupt */
	पूर्णांक (*irq_setup)(काष्ठा mv88e6xxx_chip *chip);
	/* Reset the hardware to stop generating the पूर्णांकerrupt */
	व्योम (*irq_मुक्त)(काष्ठा mv88e6xxx_chip *chip);
पूर्ण;

काष्ठा mv88e6xxx_gpio_ops अणु
	/* Get/set data on GPIO pin */
	पूर्णांक (*get_data)(काष्ठा mv88e6xxx_chip *chip, अचिन्हित पूर्णांक pin);
	पूर्णांक (*set_data)(काष्ठा mv88e6xxx_chip *chip, अचिन्हित पूर्णांक pin,
			पूर्णांक value);

	/* get/set GPIO direction */
	पूर्णांक (*get_dir)(काष्ठा mv88e6xxx_chip *chip, अचिन्हित पूर्णांक pin);
	पूर्णांक (*set_dir)(काष्ठा mv88e6xxx_chip *chip, अचिन्हित पूर्णांक pin,
		       bool input);

	/* get/set GPIO pin control */
	पूर्णांक (*get_pctl)(काष्ठा mv88e6xxx_chip *chip, अचिन्हित पूर्णांक pin,
			पूर्णांक *func);
	पूर्णांक (*set_pctl)(काष्ठा mv88e6xxx_chip *chip, अचिन्हित पूर्णांक pin,
			पूर्णांक func);
पूर्ण;

काष्ठा mv88e6xxx_avb_ops अणु
	/* Access port-scoped Precision Time Protocol रेजिस्टरs */
	पूर्णांक (*port_ptp_पढ़ो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक addr,
			     u16 *data, पूर्णांक len);
	पूर्णांक (*port_ptp_ग_लिखो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक addr,
			      u16 data);

	/* Access global Precision Time Protocol रेजिस्टरs */
	पूर्णांक (*ptp_पढ़ो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, u16 *data,
			पूर्णांक len);
	पूर्णांक (*ptp_ग_लिखो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, u16 data);

	/* Access global Time Application Interface रेजिस्टरs */
	पूर्णांक (*tai_पढ़ो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, u16 *data,
			पूर्णांक len);
	पूर्णांक (*tai_ग_लिखो)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, u16 data);
पूर्ण;

काष्ठा mv88e6xxx_ptp_ops अणु
	u64 (*घड़ी_पढ़ो)(स्थिर काष्ठा cyclecounter *cc);
	पूर्णांक (*ptp_enable)(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on);
	पूर्णांक (*ptp_verअगरy)(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
			  क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan);
	व्योम (*event_work)(काष्ठा work_काष्ठा *ugly);
	पूर्णांक (*port_enable)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
	पूर्णांक (*port_disable)(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
	पूर्णांक (*global_enable)(काष्ठा mv88e6xxx_chip *chip);
	पूर्णांक (*global_disable)(काष्ठा mv88e6xxx_chip *chip);
	पूर्णांक n_ext_ts;
	पूर्णांक arr0_sts_reg;
	पूर्णांक arr1_sts_reg;
	पूर्णांक dep_sts_reg;
	u32 rx_filters;
	u32 cc_shअगरt;
	u32 cc_mult;
	u32 cc_mult_num;
	u32 cc_mult_dem;
पूर्ण;

#घोषणा STATS_TYPE_PORT		BIT(0)
#घोषणा STATS_TYPE_BANK0	BIT(1)
#घोषणा STATS_TYPE_BANK1	BIT(2)

काष्ठा mv88e6xxx_hw_stat अणु
	अक्षर string[ETH_GSTRING_LEN];
	माप_प्रकार size;
	पूर्णांक reg;
	पूर्णांक type;
पूर्ण;

अटल अंतरभूत bool mv88e6xxx_has_pvt(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस chip->info->pvt;
पूर्ण

अटल अंतरभूत bool mv88e6xxx_has_lag(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस !!chip->info->global2_addr;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mv88e6xxx_num_databases(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस chip->info->num_databases;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mv88e6xxx_num_macs(काष्ठा  mv88e6xxx_chip *chip)
अणु
	वापस chip->info->num_macs;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mv88e6xxx_num_ports(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस chip->info->num_ports;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mv88e6xxx_max_vid(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस chip->info->max_vid;
पूर्ण

अटल अंतरभूत u16 mv88e6xxx_port_mask(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस GENMASK((s32)mv88e6xxx_num_ports(chip) - 1, 0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mv88e6xxx_num_gpio(काष्ठा mv88e6xxx_chip *chip)
अणु
	वापस chip->info->num_gpio;
पूर्ण

अटल अंतरभूत bool mv88e6xxx_is_invalid_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस (chip->info->invalid_port_mask & BIT(port)) != 0;
पूर्ण

पूर्णांक mv88e6xxx_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg, u16 *val);
पूर्णांक mv88e6xxx_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg, u16 val);
पूर्णांक mv88e6xxx_रुको_mask(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg,
			u16 mask, u16 val);
पूर्णांक mv88e6xxx_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक addr, पूर्णांक reg,
		       पूर्णांक bit, पूर्णांक val);
काष्ठा mii_bus *mv88e6xxx_शेष_mdio_bus(काष्ठा mv88e6xxx_chip *chip);

अटल अंतरभूत व्योम mv88e6xxx_reg_lock(काष्ठा mv88e6xxx_chip *chip)
अणु
	mutex_lock(&chip->reg_lock);
पूर्ण

अटल अंतरभूत व्योम mv88e6xxx_reg_unlock(काष्ठा mv88e6xxx_chip *chip)
अणु
	mutex_unlock(&chip->reg_lock);
पूर्ण

पूर्णांक mv88e6xxx_fid_map(काष्ठा mv88e6xxx_chip *chip, अचिन्हित दीर्घ *biपंचांगap);

#पूर्ण_अगर /* _MV88E6XXX_CHIP_H */
