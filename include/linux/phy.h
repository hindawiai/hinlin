<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Framework and drivers क्रम configuring and पढ़ोing dअगरferent PHYs
 * Based on code in sungem_phy.c and (दीर्घ-हटाओd) gianfar_phy.c
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __PHY_H
#घोषणा __PHY_H

#समावेश <linux/compiler.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/linkmode.h>
#समावेश <linux/netlink.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mii.h>
#समावेश <linux/mii_बारtamper.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/refcount.h>

#समावेश <linux/atomic.h>

#घोषणा PHY_DEFAULT_FEATURES	(SUPPORTED_Autoneg | \
				 SUPPORTED_TP | \
				 SUPPORTED_MII)

#घोषणा PHY_10BT_FEATURES	(SUPPORTED_10baseT_Half | \
				 SUPPORTED_10baseT_Full)

#घोषणा PHY_100BT_FEATURES	(SUPPORTED_100baseT_Half | \
				 SUPPORTED_100baseT_Full)

#घोषणा PHY_1000BT_FEATURES	(SUPPORTED_1000baseT_Half | \
				 SUPPORTED_1000baseT_Full)

बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_basic_features) __ro_after_init;
बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_basic_t1_features) __ro_after_init;
बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_gbit_features) __ro_after_init;
बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_gbit_fibre_features) __ro_after_init;
बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_gbit_all_ports_features) __ro_after_init;
बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_10gbit_features) __ro_after_init;
बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_10gbit_fec_features) __ro_after_init;
बाह्य __ETHTOOL_DECLARE_LINK_MODE_MASK(phy_10gbit_full_features) __ro_after_init;

#घोषणा PHY_BASIC_FEATURES ((अचिन्हित दीर्घ *)&phy_basic_features)
#घोषणा PHY_BASIC_T1_FEATURES ((अचिन्हित दीर्घ *)&phy_basic_t1_features)
#घोषणा PHY_GBIT_FEATURES ((अचिन्हित दीर्घ *)&phy_gbit_features)
#घोषणा PHY_GBIT_FIBRE_FEATURES ((अचिन्हित दीर्घ *)&phy_gbit_fibre_features)
#घोषणा PHY_GBIT_ALL_PORTS_FEATURES ((अचिन्हित दीर्घ *)&phy_gbit_all_ports_features)
#घोषणा PHY_10GBIT_FEATURES ((अचिन्हित दीर्घ *)&phy_10gbit_features)
#घोषणा PHY_10GBIT_FEC_FEATURES ((अचिन्हित दीर्घ *)&phy_10gbit_fec_features)
#घोषणा PHY_10GBIT_FULL_FEATURES ((अचिन्हित दीर्घ *)&phy_10gbit_full_features)

बाह्य स्थिर पूर्णांक phy_basic_ports_array[3];
बाह्य स्थिर पूर्णांक phy_fibre_port_array[1];
बाह्य स्थिर पूर्णांक phy_all_ports_features_array[7];
बाह्य स्थिर पूर्णांक phy_10_100_features_array[4];
बाह्य स्थिर पूर्णांक phy_basic_t1_features_array[2];
बाह्य स्थिर पूर्णांक phy_gbit_features_array[2];
बाह्य स्थिर पूर्णांक phy_10gbit_features_array[1];

/*
 * Set phydev->irq to PHY_POLL अगर पूर्णांकerrupts are not supported,
 * or not desired क्रम this PHY.  Set to PHY_MAC_INTERRUPT अगर
 * the attached MAC driver handles the पूर्णांकerrupt
 */
#घोषणा PHY_POLL		-1
#घोषणा PHY_MAC_INTERRUPT	-2

#घोषणा PHY_IS_INTERNAL		0x00000001
#घोषणा PHY_RST_AFTER_CLK_EN	0x00000002
#घोषणा PHY_POLL_CABLE_TEST	0x00000004
#घोषणा MDIO_DEVICE_IS_PHY	0x80000000

/**
 * क्रमागत phy_पूर्णांकerface_t - Interface Mode definitions
 *
 * @PHY_INTERFACE_MODE_NA: Not Applicable - करोn't touch
 * @PHY_INTERFACE_MODE_INTERNAL: No पूर्णांकerface, MAC and PHY combined
 * @PHY_INTERFACE_MODE_MII: Median-independent पूर्णांकerface
 * @PHY_INTERFACE_MODE_GMII: Gigabit median-independent पूर्णांकerface
 * @PHY_INTERFACE_MODE_SGMII: Serial gigabit media-independent पूर्णांकerface
 * @PHY_INTERFACE_MODE_TBI: Ten Bit Interface
 * @PHY_INTERFACE_MODE_REVMII: Reverse Media Independent Interface
 * @PHY_INTERFACE_MODE_RMII: Reduced Media Independent Interface
 * @PHY_INTERFACE_MODE_RGMII: Reduced gigabit media-independent पूर्णांकerface
 * @PHY_INTERFACE_MODE_RGMII_ID: RGMII with Internal RX+TX delay
 * @PHY_INTERFACE_MODE_RGMII_RXID: RGMII with Internal RX delay
 * @PHY_INTERFACE_MODE_RGMII_TXID: RGMII with Internal RX delay
 * @PHY_INTERFACE_MODE_RTBI: Reduced TBI
 * @PHY_INTERFACE_MODE_SMII: ??? MII
 * @PHY_INTERFACE_MODE_XGMII: 10 gigabit media-independent पूर्णांकerface
 * @PHY_INTERFACE_MODE_XLGMII:40 gigabit media-independent पूर्णांकerface
 * @PHY_INTERFACE_MODE_MOCA: Mulसमयdia over Coax
 * @PHY_INTERFACE_MODE_QSGMII: Quad SGMII
 * @PHY_INTERFACE_MODE_TRGMII: Turbo RGMII
 * @PHY_INTERFACE_MODE_100BASEX: 100 BaseX
 * @PHY_INTERFACE_MODE_1000BASEX: 1000 BaseX
 * @PHY_INTERFACE_MODE_2500BASEX: 2500 BaseX
 * @PHY_INTERFACE_MODE_5GBASER: 5G BaseR
 * @PHY_INTERFACE_MODE_RXAUI: Reduced XAUI
 * @PHY_INTERFACE_MODE_XAUI: 10 Gigabit Attachment Unit Interface
 * @PHY_INTERFACE_MODE_10GBASER: 10G BaseR
 * @PHY_INTERFACE_MODE_USXGMII:  Universal Serial 10GE MII
 * @PHY_INTERFACE_MODE_10GKR: 10GBASE-KR - with Clause 73 AN
 * @PHY_INTERFACE_MODE_MAX: Book keeping
 *
 * Describes the पूर्णांकerface between the MAC and PHY.
 */
प्रकार क्रमागत अणु
	PHY_INTERFACE_MODE_NA,
	PHY_INTERFACE_MODE_INTERNAL,
	PHY_INTERFACE_MODE_MII,
	PHY_INTERFACE_MODE_GMII,
	PHY_INTERFACE_MODE_SGMII,
	PHY_INTERFACE_MODE_TBI,
	PHY_INTERFACE_MODE_REVMII,
	PHY_INTERFACE_MODE_RMII,
	PHY_INTERFACE_MODE_RGMII,
	PHY_INTERFACE_MODE_RGMII_ID,
	PHY_INTERFACE_MODE_RGMII_RXID,
	PHY_INTERFACE_MODE_RGMII_TXID,
	PHY_INTERFACE_MODE_RTBI,
	PHY_INTERFACE_MODE_SMII,
	PHY_INTERFACE_MODE_XGMII,
	PHY_INTERFACE_MODE_XLGMII,
	PHY_INTERFACE_MODE_MOCA,
	PHY_INTERFACE_MODE_QSGMII,
	PHY_INTERFACE_MODE_TRGMII,
	PHY_INTERFACE_MODE_100BASEX,
	PHY_INTERFACE_MODE_1000BASEX,
	PHY_INTERFACE_MODE_2500BASEX,
	PHY_INTERFACE_MODE_5GBASER,
	PHY_INTERFACE_MODE_RXAUI,
	PHY_INTERFACE_MODE_XAUI,
	/* 10GBASE-R, XFI, SFI - single lane 10G Serdes */
	PHY_INTERFACE_MODE_10GBASER,
	PHY_INTERFACE_MODE_USXGMII,
	/* 10GBASE-KR - with Clause 73 AN */
	PHY_INTERFACE_MODE_10GKR,
	PHY_INTERFACE_MODE_MAX,
पूर्ण phy_पूर्णांकerface_t;

/*
 * phy_supported_speeds - वापस all speeds currently supported by a PHY device
 */
अचिन्हित पूर्णांक phy_supported_speeds(काष्ठा phy_device *phy,
				      अचिन्हित पूर्णांक *speeds,
				      अचिन्हित पूर्णांक size);

/**
 * phy_modes - map phy_पूर्णांकerface_t क्रमागत to device tree binding of phy-mode
 * @पूर्णांकerface: क्रमागत phy_पूर्णांकerface_t value
 *
 * Description: maps क्रमागत &phy_पूर्णांकerface_t defined in this file
 * पूर्णांकo the device tree binding of 'phy-mode', so that Ethernet
 * device driver can get PHY पूर्णांकerface from device tree.
 */
अटल अंतरभूत स्थिर अक्षर *phy_modes(phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_NA:
		वापस "";
	हाल PHY_INTERFACE_MODE_INTERNAL:
		वापस "internal";
	हाल PHY_INTERFACE_MODE_MII:
		वापस "mii";
	हाल PHY_INTERFACE_MODE_GMII:
		वापस "gmii";
	हाल PHY_INTERFACE_MODE_SGMII:
		वापस "sgmii";
	हाल PHY_INTERFACE_MODE_TBI:
		वापस "tbi";
	हाल PHY_INTERFACE_MODE_REVMII:
		वापस "rev-mii";
	हाल PHY_INTERFACE_MODE_RMII:
		वापस "rmii";
	हाल PHY_INTERFACE_MODE_RGMII:
		वापस "rgmii";
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		वापस "rgmii-id";
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		वापस "rgmii-rxid";
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		वापस "rgmii-txid";
	हाल PHY_INTERFACE_MODE_RTBI:
		वापस "rtbi";
	हाल PHY_INTERFACE_MODE_SMII:
		वापस "smii";
	हाल PHY_INTERFACE_MODE_XGMII:
		वापस "xgmii";
	हाल PHY_INTERFACE_MODE_XLGMII:
		वापस "xlgmii";
	हाल PHY_INTERFACE_MODE_MOCA:
		वापस "moca";
	हाल PHY_INTERFACE_MODE_QSGMII:
		वापस "qsgmii";
	हाल PHY_INTERFACE_MODE_TRGMII:
		वापस "trgmii";
	हाल PHY_INTERFACE_MODE_1000BASEX:
		वापस "1000base-x";
	हाल PHY_INTERFACE_MODE_2500BASEX:
		वापस "2500base-x";
	हाल PHY_INTERFACE_MODE_5GBASER:
		वापस "5gbase-r";
	हाल PHY_INTERFACE_MODE_RXAUI:
		वापस "rxaui";
	हाल PHY_INTERFACE_MODE_XAUI:
		वापस "xaui";
	हाल PHY_INTERFACE_MODE_10GBASER:
		वापस "10gbase-r";
	हाल PHY_INTERFACE_MODE_USXGMII:
		वापस "usxgmii";
	हाल PHY_INTERFACE_MODE_10GKR:
		वापस "10gbase-kr";
	हाल PHY_INTERFACE_MODE_100BASEX:
		वापस "100base-x";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण


#घोषणा PHY_INIT_TIMEOUT	100000
#घोषणा PHY_FORCE_TIMEOUT	10

#घोषणा PHY_MAX_ADDR	32

/* Used when trying to connect to a specअगरic phy (mii bus id:phy device id) */
#घोषणा PHY_ID_FMT "%s:%02x"

#घोषणा MII_BUS_ID_SIZE	61

काष्ठा device;
काष्ठा phylink;
काष्ठा sfp_bus;
काष्ठा sfp_upstream_ops;
काष्ठा sk_buff;

/**
 * काष्ठा mdio_bus_stats - Statistics counters क्रम MDIO busses
 * @transfers: Total number of transfers, i.e. @ग_लिखोs + @पढ़ोs
 * @errors: Number of MDIO transfers that वापसed an error
 * @ग_लिखोs: Number of ग_लिखो transfers
 * @पढ़ोs: Number of पढ़ो transfers
 * @syncp: Synchronisation क्रम incrementing statistics
 */
काष्ठा mdio_bus_stats अणु
	u64_stats_t transfers;
	u64_stats_t errors;
	u64_stats_t ग_लिखोs;
	u64_stats_t पढ़ोs;
	/* Must be last, add new statistics above */
	काष्ठा u64_stats_sync syncp;
पूर्ण;

/**
 * काष्ठा phy_package_shared - Shared inक्रमmation in PHY packages
 * @addr: Common PHY address used to combine PHYs in one package
 * @refcnt: Number of PHYs connected to this shared data
 * @flags: Initialization of PHY package
 * @priv_size: Size of the shared निजी data @priv
 * @priv: Driver निजी data shared across a PHY package
 *
 * Represents a shared काष्ठाure between dअगरferent phydev's in the same
 * package, क्रम example a quad PHY. See phy_package_join() and
 * phy_package_leave().
 */
काष्ठा phy_package_shared अणु
	पूर्णांक addr;
	refcount_t refcnt;
	अचिन्हित दीर्घ flags;
	माप_प्रकार priv_size;

	/* निजी data poपूर्णांकer */
	/* note that this poपूर्णांकer is shared between dअगरferent phydevs and
	 * the user has to take care of appropriate locking. It is allocated
	 * and मुक्तd स्वतःmatically by phy_package_join() and
	 * phy_package_leave().
	 */
	व्योम *priv;
पूर्ण;

/* used as bit number in atomic bitops */
#घोषणा PHY_SHARED_F_INIT_DONE  0
#घोषणा PHY_SHARED_F_PROBE_DONE 1

/**
 * काष्ठा mii_bus - Represents an MDIO bus
 *
 * @owner: Who owns this device
 * @name: User मित्रly name क्रम this MDIO device, or driver name
 * @id: Unique identअगरier क्रम this bus, typical from bus hierarchy
 * @priv: Driver निजी data
 *
 * The Bus class क्रम PHYs.  Devices which provide access to
 * PHYs should रेजिस्टर using this काष्ठाure
 */
काष्ठा mii_bus अणु
	काष्ठा module *owner;
	स्थिर अक्षर *name;
	अक्षर id[MII_BUS_ID_SIZE];
	व्योम *priv;
	/** @पढ़ो: Perक्रमm a पढ़ो transfer on the bus */
	पूर्णांक (*पढ़ो)(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum);
	/** @ग_लिखो: Perक्रमm a ग_लिखो transfer on the bus */
	पूर्णांक (*ग_लिखो)(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum, u16 val);
	/** @reset: Perक्रमm a reset of the bus */
	पूर्णांक (*reset)(काष्ठा mii_bus *bus);

	/** @stats: Statistic counters per device on the bus */
	काष्ठा mdio_bus_stats stats[PHY_MAX_ADDR];

	/**
	 * @mdio_lock: A lock to ensure that only one thing can पढ़ो/ग_लिखो
	 * the MDIO bus at a समय
	 */
	काष्ठा mutex mdio_lock;

	/** @parent: Parent device of this bus */
	काष्ठा device *parent;
	/** @state: State of bus काष्ठाure */
	क्रमागत अणु
		MDIOBUS_ALLOCATED = 1,
		MDIOBUS_REGISTERED,
		MDIOBUS_UNREGISTERED,
		MDIOBUS_RELEASED,
	पूर्ण state;

	/** @dev: Kernel device representation */
	काष्ठा device dev;

	/** @mdio_map: list of all MDIO devices on bus */
	काष्ठा mdio_device *mdio_map[PHY_MAX_ADDR];

	/** @phy_mask: PHY addresses to be ignored when probing */
	u32 phy_mask;

	/** @phy_ignore_ta_mask: PHY addresses to ignore the TA/पढ़ो failure */
	u32 phy_ignore_ta_mask;

	/**
	 * @irq: An array of पूर्णांकerrupts, each PHY's पूर्णांकerrupt at the index
	 * matching its address
	 */
	पूर्णांक irq[PHY_MAX_ADDR];

	/** @reset_delay_us: GPIO reset pulse width in microseconds */
	पूर्णांक reset_delay_us;
	/** @reset_post_delay_us: GPIO reset deनिश्चित delay in microseconds */
	पूर्णांक reset_post_delay_us;
	/** @reset_gpiod: Reset GPIO descriptor poपूर्णांकer */
	काष्ठा gpio_desc *reset_gpiod;

	/** @probe_capabilities: bus capabilities, used क्रम probing */
	क्रमागत अणु
		MDIOBUS_NO_CAP = 0,
		MDIOBUS_C22,
		MDIOBUS_C45,
		MDIOBUS_C22_C45,
	पूर्ण probe_capabilities;

	/** @shared_lock: protect access to the shared element */
	काष्ठा mutex shared_lock;

	/** @shared: shared state across dअगरferent PHYs */
	काष्ठा phy_package_shared *shared[PHY_MAX_ADDR];
पूर्ण;
#घोषणा to_mii_bus(d) container_of(d, काष्ठा mii_bus, dev)

काष्ठा mii_bus *mdiobus_alloc_size(माप_प्रकार size);

/**
 * mdiobus_alloc - Allocate an MDIO bus काष्ठाure
 *
 * The पूर्णांकernal state of the MDIO bus will be set of MDIOBUS_ALLOCATED पढ़ोy
 * क्रम the driver to रेजिस्टर the bus.
 */
अटल अंतरभूत काष्ठा mii_bus *mdiobus_alloc(व्योम)
अणु
	वापस mdiobus_alloc_size(0);
पूर्ण

पूर्णांक __mdiobus_रेजिस्टर(काष्ठा mii_bus *bus, काष्ठा module *owner);
पूर्णांक __devm_mdiobus_रेजिस्टर(काष्ठा device *dev, काष्ठा mii_bus *bus,
			    काष्ठा module *owner);
#घोषणा mdiobus_रेजिस्टर(bus) __mdiobus_रेजिस्टर(bus, THIS_MODULE)
#घोषणा devm_mdiobus_रेजिस्टर(dev, bus) \
		__devm_mdiobus_रेजिस्टर(dev, bus, THIS_MODULE)

व्योम mdiobus_unरेजिस्टर(काष्ठा mii_bus *bus);
व्योम mdiobus_मुक्त(काष्ठा mii_bus *bus);
काष्ठा mii_bus *devm_mdiobus_alloc_size(काष्ठा device *dev, पूर्णांक माप_priv);
अटल अंतरभूत काष्ठा mii_bus *devm_mdiobus_alloc(काष्ठा device *dev)
अणु
	वापस devm_mdiobus_alloc_size(dev, 0);
पूर्ण

काष्ठा mii_bus *mdio_find_bus(स्थिर अक्षर *mdio_name);
काष्ठा phy_device *mdiobus_scan(काष्ठा mii_bus *bus, पूर्णांक addr);

#घोषणा PHY_INTERRUPT_DISABLED	false
#घोषणा PHY_INTERRUPT_ENABLED	true

/**
 * क्रमागत phy_state - PHY state machine states:
 *
 * @PHY_DOWN: PHY device and driver are not पढ़ोy क्रम anything.  probe
 * should be called अगर and only अगर the PHY is in this state,
 * given that the PHY device exists.
 * - PHY driver probe function will set the state to @PHY_READY
 *
 * @PHY_READY: PHY is पढ़ोy to send and receive packets, but the
 * controller is not.  By शेष, PHYs which करो not implement
 * probe will be set to this state by phy_probe().
 * - start will set the state to UP
 *
 * @PHY_UP: The PHY and attached device are पढ़ोy to करो work.
 * Interrupts should be started here.
 * - समयr moves to @PHY_NOLINK or @PHY_RUNNING
 *
 * @PHY_NOLINK: PHY is up, but not currently plugged in.
 * - irq or समयr will set @PHY_RUNNING अगर link comes back
 * - phy_stop moves to @PHY_HALTED
 *
 * @PHY_RUNNING: PHY is currently up, running, and possibly sending
 * and/or receiving packets
 * - irq or समयr will set @PHY_NOLINK अगर link goes करोwn
 * - phy_stop moves to @PHY_HALTED
 *
 * @PHY_CABLETEST: PHY is perक्रमming a cable test. Packet reception/sending
 * is not expected to work, carrier will be indicated as करोwn. PHY will be
 * poll once per second, or on पूर्णांकerrupt क्रम it current state.
 * Once complete, move to UP to restart the PHY.
 * - phy_stop पातs the running test and moves to @PHY_HALTED
 *
 * @PHY_HALTED: PHY is up, but no polling or पूर्णांकerrupts are करोne. Or
 * PHY is in an error state.
 * - phy_start moves to @PHY_UP
 */
क्रमागत phy_state अणु
	PHY_DOWN = 0,
	PHY_READY,
	PHY_HALTED,
	PHY_UP,
	PHY_RUNNING,
	PHY_NOLINK,
	PHY_CABLETEST,
पूर्ण;

#घोषणा MDIO_MMD_NUM 32

/**
 * काष्ठा phy_c45_device_ids - 802.3-c45 Device Identअगरiers
 * @devices_in_package: IEEE 802.3 devices in package रेजिस्टर value.
 * @mmds_present: bit vector of MMDs present.
 * @device_ids: The device identअगरer क्रम each present device.
 */
काष्ठा phy_c45_device_ids अणु
	u32 devices_in_package;
	u32 mmds_present;
	u32 device_ids[MDIO_MMD_NUM];
पूर्ण;

काष्ठा macsec_context;
काष्ठा macsec_ops;

/**
 * काष्ठा phy_device - An instance of a PHY
 *
 * @mdio: MDIO bus this PHY is on
 * @drv: Poपूर्णांकer to the driver क्रम this PHY instance
 * @phy_id: UID क्रम this device found during discovery
 * @c45_ids: 802.3-c45 Device Identअगरiers अगर is_c45.
 * @is_c45:  Set to true अगर this PHY uses clause 45 addressing.
 * @is_पूर्णांकernal: Set to true अगर this PHY is पूर्णांकernal to a MAC.
 * @is_pseuकरो_fixed_link: Set to true अगर this PHY is an Ethernet चयन, etc.
 * @is_gigabit_capable: Set to true अगर PHY supports 1000Mbps
 * @has_fixups: Set to true अगर this PHY has fixups/quirks.
 * @suspended: Set to true अगर this PHY has been suspended successfully.
 * @suspended_by_mdio_bus: Set to true अगर this PHY was suspended by MDIO bus.
 * @sysfs_links: Internal boolean tracking sysfs symbolic links setup/removal.
 * @loopback_enabled: Set true अगर this PHY has been loopbacked successfully.
 * @करोwnshअगरted_rate: Set true अगर link speed has been करोwnshअगरted.
 * @is_on_sfp_module: Set true अगर PHY is located on an SFP module.
 * @mac_managed_pm: Set true अगर MAC driver takes of suspending/resuming PHY
 * @state: State of the PHY क्रम management purposes
 * @dev_flags: Device-specअगरic flags used by the PHY driver.
 *		Bits [15:0] are मुक्त to use by the PHY driver to communicate
 *			    driver specअगरic behavior.
 *		Bits [23:16] are currently reserved क्रम future use.
 *		Bits [31:24] are reserved क्रम defining generic
 *			     PHY driver behavior.
 * @irq: IRQ number of the PHY's पूर्णांकerrupt (-1 अगर none)
 * @phy_समयr: The समयr क्रम handling the state machine
 * @phylink: Poपूर्णांकer to phylink instance क्रम this PHY
 * @sfp_bus_attached: Flag indicating whether the SFP bus has been attached
 * @sfp_bus: SFP bus attached to this PHY's fiber port
 * @attached_dev: The attached enet driver's device instance ptr
 * @adjust_link: Callback क्रम the enet controller to respond to changes: in the
 *               link state.
 * @phy_link_change: Callback क्रम phylink क्रम notअगरication of link change
 * @macsec_ops: MACsec offloading ops.
 *
 * @speed: Current link speed
 * @duplex: Current duplex
 * @port: Current port
 * @छोड़ो: Current छोड़ो
 * @asym_छोड़ो: Current asymmetric छोड़ो
 * @supported: Combined MAC/PHY supported linkmodes
 * @advertising: Currently advertised linkmodes
 * @adv_old: Saved advertised जबतक घातer saving क्रम WoL
 * @lp_advertising: Current link partner advertised linkmodes
 * @eee_broken_modes: Energy efficient ethernet modes which should be prohibited
 * @स्वतःneg: Flag स्वतःneg being used
 * @link: Current link state
 * @स्वतःneg_complete: Flag स्वतः negotiation of the link has completed
 * @mdix: Current crossover
 * @mdix_ctrl: User setting of crossover
 * @पूर्णांकerrupts: Flag पूर्णांकerrupts have been enabled
 * @पूर्णांकerface: क्रमागत phy_पूर्णांकerface_t value
 * @skb: Netlink message क्रम cable diagnostics
 * @nest: Netlink nest used क्रम cable diagnostics
 * @ehdr: nNtlink header क्रम cable diagnostics
 * @phy_led_triggers: Array of LED triggers
 * @phy_num_led_triggers: Number of triggers in @phy_led_triggers
 * @led_link_trigger: LED trigger क्रम link up/करोwn
 * @last_triggered: last LED trigger क्रम link speed
 * @master_slave_set: User requested master/slave configuration
 * @master_slave_get: Current master/slave advertisement
 * @master_slave_state: Current master/slave configuration
 * @mii_ts: Poपूर्णांकer to समय stamper callbacks
 * @lock:  Mutex क्रम serialization access to PHY
 * @state_queue: Work queue क्रम state machine
 * @shared: Poपूर्णांकer to निजी data shared by phys in one package
 * @priv: Poपूर्णांकer to driver निजी data
 *
 * पूर्णांकerrupts currently only supports enabled or disabled,
 * but could be changed in the future to support enabling
 * and disabling specअगरic पूर्णांकerrupts
 *
 * Contains some infraकाष्ठाure क्रम polling and पूर्णांकerrupt
 * handling, as well as handling shअगरts in PHY hardware state
 */
काष्ठा phy_device अणु
	काष्ठा mdio_device mdio;

	/* Inक्रमmation about the PHY type */
	/* And management functions */
	काष्ठा phy_driver *drv;

	u32 phy_id;

	काष्ठा phy_c45_device_ids c45_ids;
	अचिन्हित is_c45:1;
	अचिन्हित is_पूर्णांकernal:1;
	अचिन्हित is_pseuकरो_fixed_link:1;
	अचिन्हित is_gigabit_capable:1;
	अचिन्हित has_fixups:1;
	अचिन्हित suspended:1;
	अचिन्हित suspended_by_mdio_bus:1;
	अचिन्हित sysfs_links:1;
	अचिन्हित loopback_enabled:1;
	अचिन्हित करोwnshअगरted_rate:1;
	अचिन्हित is_on_sfp_module:1;
	अचिन्हित mac_managed_pm:1;

	अचिन्हित स्वतःneg:1;
	/* The most recently पढ़ो link state */
	अचिन्हित link:1;
	अचिन्हित स्वतःneg_complete:1;

	/* Interrupts are enabled */
	अचिन्हित पूर्णांकerrupts:1;

	क्रमागत phy_state state;

	u32 dev_flags;

	phy_पूर्णांकerface_t पूर्णांकerface;

	/*
	 * क्रमced speed & duplex (no स्वतःneg)
	 * partner speed & duplex & छोड़ो (स्वतःneg)
	 */
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक port;
	पूर्णांक छोड़ो;
	पूर्णांक asym_छोड़ो;
	u8 master_slave_get;
	u8 master_slave_set;
	u8 master_slave_state;

	/* Union of PHY and Attached devices' supported link modes */
	/* See ethtool.h क्रम more info */
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(advertising);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(lp_advertising);
	/* used with phy_speed_करोwn */
	__ETHTOOL_DECLARE_LINK_MODE_MASK(adv_old);

	/* Energy efficient ethernet modes which should be prohibited */
	u32 eee_broken_modes;

#अगर_घोषित CONFIG_LED_TRIGGER_PHY
	काष्ठा phy_led_trigger *phy_led_triggers;
	अचिन्हित पूर्णांक phy_num_led_triggers;
	काष्ठा phy_led_trigger *last_triggered;

	काष्ठा phy_led_trigger *led_link_trigger;
#पूर्ण_अगर

	/*
	 * Interrupt number क्रम this PHY
	 * -1 means no पूर्णांकerrupt
	 */
	पूर्णांक irq;

	/* निजी data poपूर्णांकer */
	/* For use by PHYs to मुख्यtain extra state */
	व्योम *priv;

	/* shared data poपूर्णांकer */
	/* For use by PHYs inside the same package that need a shared state. */
	काष्ठा phy_package_shared *shared;

	/* Reporting cable test results */
	काष्ठा sk_buff *skb;
	व्योम *ehdr;
	काष्ठा nlattr *nest;

	/* Interrupt and Polling infraकाष्ठाure */
	काष्ठा delayed_work state_queue;

	काष्ठा mutex lock;

	/* This may be modअगरied under the rtnl lock */
	bool sfp_bus_attached;
	काष्ठा sfp_bus *sfp_bus;
	काष्ठा phylink *phylink;
	काष्ठा net_device *attached_dev;
	काष्ठा mii_बारtamper *mii_ts;

	u8 mdix;
	u8 mdix_ctrl;

	व्योम (*phy_link_change)(काष्ठा phy_device *phydev, bool up);
	व्योम (*adjust_link)(काष्ठा net_device *dev);

#अगर IS_ENABLED(CONFIG_MACSEC)
	/* MACsec management functions */
	स्थिर काष्ठा macsec_ops *macsec_ops;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत काष्ठा phy_device *to_phy_device(स्थिर काष्ठा device *dev)
अणु
	वापस container_of(to_mdio_device(dev), काष्ठा phy_device, mdio);
पूर्ण

/**
 * काष्ठा phy_tdr_config - Configuration of a TDR raw test
 *
 * @first: Distance क्रम first data collection poपूर्णांक
 * @last: Distance क्रम last data collection poपूर्णांक
 * @step: Step between data collection poपूर्णांकs
 * @pair: Biपंचांगap of cable pairs to collect data क्रम
 *
 * A काष्ठाure containing possible configuration parameters
 * क्रम a TDR cable test. The driver करोes not need to implement
 * all the parameters, but should report what is actually used.
 * All distances are in cenसमयters.
 */
काष्ठा phy_tdr_config अणु
	u32 first;
	u32 last;
	u32 step;
	s8 pair;
पूर्ण;
#घोषणा PHY_PAIR_ALL -1

/**
 * काष्ठा phy_driver - Driver काष्ठाure क्रम a particular PHY type
 *
 * @mdiodrv: Data common to all MDIO devices
 * @phy_id: The result of पढ़ोing the UID रेजिस्टरs of this PHY
 *   type, and ANDing them with the phy_id_mask.  This driver
 *   only works क्रम PHYs with IDs which match this field
 * @name: The मित्रly name of this PHY type
 * @phy_id_mask: Defines the important bits of the phy_id
 * @features: A mandatory list of features (speed, duplex, etc)
 *   supported by this PHY
 * @flags: A bitfield defining certain other features this PHY
 *   supports (like पूर्णांकerrupts)
 * @driver_data: Static driver data
 *
 * All functions are optional. If config_aneg or पढ़ो_status
 * are not implemented, the phy core uses the genphy versions.
 * Note that none of these functions should be called from
 * पूर्णांकerrupt समय. The goal is क्रम the bus पढ़ो/ग_लिखो functions
 * to be able to block when the bus transaction is happening,
 * and be मुक्तd up by an पूर्णांकerrupt (The MPC85xx has this ability,
 * though it is not currently supported in the driver).
 */
काष्ठा phy_driver अणु
	काष्ठा mdio_driver_common mdiodrv;
	u32 phy_id;
	अक्षर *name;
	u32 phy_id_mask;
	स्थिर अचिन्हित दीर्घ * स्थिर features;
	u32 flags;
	स्थिर व्योम *driver_data;

	/**
	 * @soft_reset: Called to issue a PHY software reset
	 */
	पूर्णांक (*soft_reset)(काष्ठा phy_device *phydev);

	/**
	 * @config_init: Called to initialize the PHY,
	 * including after a reset
	 */
	पूर्णांक (*config_init)(काष्ठा phy_device *phydev);

	/**
	 * @probe: Called during discovery.  Used to set
	 * up device-specअगरic काष्ठाures, अगर any
	 */
	पूर्णांक (*probe)(काष्ठा phy_device *phydev);

	/**
	 * @get_features: Probe the hardware to determine what
	 * abilities it has.  Should only set phydev->supported.
	 */
	पूर्णांक (*get_features)(काष्ठा phy_device *phydev);

	/* PHY Power Management */
	/** @suspend: Suspend the hardware, saving state अगर needed */
	पूर्णांक (*suspend)(काष्ठा phy_device *phydev);
	/** @resume: Resume the hardware, restoring state अगर needed */
	पूर्णांक (*resume)(काष्ठा phy_device *phydev);

	/**
	 * @config_aneg: Configures the advertisement and resets
	 * स्वतःnegotiation अगर phydev->स्वतःneg is on,
	 * क्रमces the speed to the current settings in phydev
	 * अगर phydev->स्वतःneg is off
	 */
	पूर्णांक (*config_aneg)(काष्ठा phy_device *phydev);

	/** @aneg_करोne: Determines the स्वतः negotiation result */
	पूर्णांक (*aneg_करोne)(काष्ठा phy_device *phydev);

	/** @पढ़ो_status: Determines the negotiated speed and duplex */
	पूर्णांक (*पढ़ो_status)(काष्ठा phy_device *phydev);

	/**
	 * @config_पूर्णांकr: Enables or disables पूर्णांकerrupts.
	 * It should also clear any pending पूर्णांकerrupts prior to enabling the
	 * IRQs and after disabling them.
	 */
	पूर्णांक (*config_पूर्णांकr)(काष्ठा phy_device *phydev);

	/** @handle_पूर्णांकerrupt: Override शेष पूर्णांकerrupt handling */
	irqवापस_t (*handle_पूर्णांकerrupt)(काष्ठा phy_device *phydev);

	/** @हटाओ: Clears up any memory अगर needed */
	व्योम (*हटाओ)(काष्ठा phy_device *phydev);

	/**
	 * @match_phy_device: Returns true अगर this is a suitable
	 * driver क्रम the given phydev.	 If शून्य, matching is based on
	 * phy_id and phy_id_mask.
	 */
	पूर्णांक (*match_phy_device)(काष्ठा phy_device *phydev);

	/**
	 * @set_wol: Some devices (e.g. qnap TS-119P II) require PHY
	 * रेजिस्टर changes to enable Wake on LAN, so set_wol is
	 * provided to be called in the ethernet driver's set_wol
	 * function.
	 */
	पूर्णांक (*set_wol)(काष्ठा phy_device *dev, काष्ठा ethtool_wolinfo *wol);

	/**
	 * @get_wol: See set_wol, but क्रम checking whether Wake on LAN
	 * is enabled.
	 */
	व्योम (*get_wol)(काष्ठा phy_device *dev, काष्ठा ethtool_wolinfo *wol);

	/**
	 * @link_change_notअगरy: Called to inक्रमm a PHY device driver
	 * when the core is about to change the link state. This
	 * callback is supposed to be used as fixup hook क्रम drivers
	 * that need to take action when the link state
	 * changes. Drivers are by no means allowed to mess with the
	 * PHY device काष्ठाure in their implementations.
	 */
	व्योम (*link_change_notअगरy)(काष्ठा phy_device *dev);

	/**
	 * @पढ़ो_mmd: PHY specअगरic driver override क्रम पढ़ोing a MMD
	 * रेजिस्टर.  This function is optional क्रम PHY specअगरic
	 * drivers.  When not provided, the शेष MMD पढ़ो function
	 * will be used by phy_पढ़ो_mmd(), which will use either a
	 * direct पढ़ो क्रम Clause 45 PHYs or an indirect पढ़ो क्रम
	 * Clause 22 PHYs.  devnum is the MMD device number within the
	 * PHY device, regnum is the रेजिस्टर within the selected MMD
	 * device.
	 */
	पूर्णांक (*पढ़ो_mmd)(काष्ठा phy_device *dev, पूर्णांक devnum, u16 regnum);

	/**
	 * @ग_लिखो_mmd: PHY specअगरic driver override क्रम writing a MMD
	 * रेजिस्टर.  This function is optional क्रम PHY specअगरic
	 * drivers.  When not provided, the शेष MMD ग_लिखो function
	 * will be used by phy_ग_लिखो_mmd(), which will use either a
	 * direct ग_लिखो क्रम Clause 45 PHYs, or an indirect ग_लिखो क्रम
	 * Clause 22 PHYs.  devnum is the MMD device number within the
	 * PHY device, regnum is the रेजिस्टर within the selected MMD
	 * device.  val is the value to be written.
	 */
	पूर्णांक (*ग_लिखो_mmd)(काष्ठा phy_device *dev, पूर्णांक devnum, u16 regnum,
			 u16 val);

	/** @पढ़ो_page: Return the current PHY रेजिस्टर page number */
	पूर्णांक (*पढ़ो_page)(काष्ठा phy_device *dev);
	/** @ग_लिखो_page: Set the current PHY रेजिस्टर page number */
	पूर्णांक (*ग_लिखो_page)(काष्ठा phy_device *dev, पूर्णांक page);

	/**
	 * @module_info: Get the size and type of the eeprom contained
	 * within a plug-in module
	 */
	पूर्णांक (*module_info)(काष्ठा phy_device *dev,
			   काष्ठा ethtool_modinfo *modinfo);

	/**
	 * @module_eeprom: Get the eeprom inक्रमmation from the plug-in
	 * module
	 */
	पूर्णांक (*module_eeprom)(काष्ठा phy_device *dev,
			     काष्ठा ethtool_eeprom *ee, u8 *data);

	/** @cable_test_start: Start a cable test */
	पूर्णांक (*cable_test_start)(काष्ठा phy_device *dev);

	/**  @cable_test_tdr_start: Start a raw TDR cable test */
	पूर्णांक (*cable_test_tdr_start)(काष्ठा phy_device *dev,
				    स्थिर काष्ठा phy_tdr_config *config);

	/**
	 * @cable_test_get_status: Once per second, or on पूर्णांकerrupt,
	 * request the status of the test.
	 */
	पूर्णांक (*cable_test_get_status)(काष्ठा phy_device *dev, bool *finished);

	/* Get statistics from the PHY using ethtool */
	/** @get_sset_count: Number of statistic counters */
	पूर्णांक (*get_sset_count)(काष्ठा phy_device *dev);
	/** @get_strings: Names of the statistic counters */
	व्योम (*get_strings)(काष्ठा phy_device *dev, u8 *data);
	/** @get_stats: Return the statistic counter values */
	व्योम (*get_stats)(काष्ठा phy_device *dev,
			  काष्ठा ethtool_stats *stats, u64 *data);

	/* Get and Set PHY tunables */
	/** @get_tunable: Return the value of a tunable */
	पूर्णांक (*get_tunable)(काष्ठा phy_device *dev,
			   काष्ठा ethtool_tunable *tuna, व्योम *data);
	/** @set_tunable: Set the value of a tunable */
	पूर्णांक (*set_tunable)(काष्ठा phy_device *dev,
			    काष्ठा ethtool_tunable *tuna,
			    स्थिर व्योम *data);
	/** @set_loopback: Set the loopback mood of the PHY */
	पूर्णांक (*set_loopback)(काष्ठा phy_device *dev, bool enable);
	/** @get_sqi: Get the संकेत quality indication */
	पूर्णांक (*get_sqi)(काष्ठा phy_device *dev);
	/** @get_sqi_max: Get the maximum संकेत quality indication */
	पूर्णांक (*get_sqi_max)(काष्ठा phy_device *dev);
पूर्ण;
#घोषणा to_phy_driver(d) container_of(to_mdio_common_driver(d),		\
				      काष्ठा phy_driver, mdiodrv)

#घोषणा PHY_ANY_ID "MATCH ANY PHY"
#घोषणा PHY_ANY_UID 0xffffffff

#घोषणा PHY_ID_MATCH_EXACT(id) .phy_id = (id), .phy_id_mask = GENMASK(31, 0)
#घोषणा PHY_ID_MATCH_MODEL(id) .phy_id = (id), .phy_id_mask = GENMASK(31, 4)
#घोषणा PHY_ID_MATCH_VENDOR(id) .phy_id = (id), .phy_id_mask = GENMASK(31, 10)

/* A Structure क्रम boards to रेजिस्टर fixups with the PHY Lib */
काष्ठा phy_fixup अणु
	काष्ठा list_head list;
	अक्षर bus_id[MII_BUS_ID_SIZE + 3];
	u32 phy_uid;
	u32 phy_uid_mask;
	पूर्णांक (*run)(काष्ठा phy_device *phydev);
पूर्ण;

स्थिर अक्षर *phy_speed_to_str(पूर्णांक speed);
स्थिर अक्षर *phy_duplex_to_str(अचिन्हित पूर्णांक duplex);

/* A काष्ठाure क्रम mapping a particular speed and duplex
 * combination to a particular SUPPORTED and ADVERTISED value
 */
काष्ठा phy_setting अणु
	u32 speed;
	u8 duplex;
	u8 bit;
पूर्ण;

स्थिर काष्ठा phy_setting *
phy_lookup_setting(पूर्णांक speed, पूर्णांक duplex, स्थिर अचिन्हित दीर्घ *mask,
		   bool exact);
माप_प्रकार phy_speeds(अचिन्हित पूर्णांक *speeds, माप_प्रकार size,
		  अचिन्हित दीर्घ *mask);
व्योम of_set_phy_supported(काष्ठा phy_device *phydev);
व्योम of_set_phy_eee_broken(काष्ठा phy_device *phydev);
पूर्णांक phy_speed_करोwn_core(काष्ठा phy_device *phydev);

/**
 * phy_is_started - Convenience function to check whether PHY is started
 * @phydev: The phy_device काष्ठा
 */
अटल अंतरभूत bool phy_is_started(काष्ठा phy_device *phydev)
अणु
	वापस phydev->state >= PHY_UP;
पूर्ण

व्योम phy_resolve_aneg_छोड़ो(काष्ठा phy_device *phydev);
व्योम phy_resolve_aneg_linkmode(काष्ठा phy_device *phydev);
व्योम phy_check_करोwnshअगरt(काष्ठा phy_device *phydev);

/**
 * phy_पढ़ो - Convenience function क्रम पढ़ोing a given PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to पढ़ो
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
अटल अंतरभूत पूर्णांक phy_पढ़ो(काष्ठा phy_device *phydev, u32 regnum)
अणु
	वापस mdiobus_पढ़ो(phydev->mdio.bus, phydev->mdio.addr, regnum);
पूर्ण

#घोषणा phy_पढ़ो_poll_समयout(phydev, regnum, val, cond, sleep_us, \
				समयout_us, sleep_beक्रमe_पढ़ो) \
(अणु \
	पूर्णांक __ret = पढ़ो_poll_समयout(phy_पढ़ो, val, (cond) || val < 0, \
		sleep_us, समयout_us, sleep_beक्रमe_पढ़ो, phydev, regnum); \
	अगर (val <  0) \
		__ret = val; \
	अगर (__ret) \
		phydev_err(phydev, "%s failed: %d\n", __func__, __ret); \
	__ret; \
पूर्ण)


/**
 * __phy_पढ़ो - convenience function क्रम पढ़ोing a given PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to पढ़ो
 *
 * The caller must have taken the MDIO bus lock.
 */
अटल अंतरभूत पूर्णांक __phy_पढ़ो(काष्ठा phy_device *phydev, u32 regnum)
अणु
	वापस __mdiobus_पढ़ो(phydev->mdio.bus, phydev->mdio.addr, regnum);
पूर्ण

/**
 * phy_ग_लिखो - Convenience function क्रम writing a given PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: value to ग_लिखो to @regnum
 *
 * NOTE: MUST NOT be called from पूर्णांकerrupt context,
 * because the bus पढ़ो/ग_लिखो functions may रुको क्रम an पूर्णांकerrupt
 * to conclude the operation.
 */
अटल अंतरभूत पूर्णांक phy_ग_लिखो(काष्ठा phy_device *phydev, u32 regnum, u16 val)
अणु
	वापस mdiobus_ग_लिखो(phydev->mdio.bus, phydev->mdio.addr, regnum, val);
पूर्ण

/**
 * __phy_ग_लिखो - Convenience function क्रम writing a given PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: value to ग_लिखो to @regnum
 *
 * The caller must have taken the MDIO bus lock.
 */
अटल अंतरभूत पूर्णांक __phy_ग_लिखो(काष्ठा phy_device *phydev, u32 regnum, u16 val)
अणु
	वापस __mdiobus_ग_लिखो(phydev->mdio.bus, phydev->mdio.addr, regnum,
			       val);
पूर्ण

/**
 * __phy_modअगरy_changed() - Convenience function क्रम modअगरying a PHY रेजिस्टर
 * @phydev: a poपूर्णांकer to a &काष्ठा phy_device
 * @regnum: रेजिस्टर number
 * @mask: bit mask of bits to clear
 * @set: bit mask of bits to set
 *
 * Unlocked helper function which allows a PHY रेजिस्टर to be modअगरied as
 * new रेजिस्टर value = (old रेजिस्टर value & ~mask) | set
 *
 * Returns negative त्रुटि_सं, 0 अगर there was no change, and 1 in हाल of change
 */
अटल अंतरभूत पूर्णांक __phy_modअगरy_changed(काष्ठा phy_device *phydev, u32 regnum,
				       u16 mask, u16 set)
अणु
	वापस __mdiobus_modअगरy_changed(phydev->mdio.bus, phydev->mdio.addr,
					regnum, mask, set);
पूर्ण

/*
 * phy_पढ़ो_mmd - Convenience function क्रम पढ़ोing a रेजिस्टर
 * from an MMD on a given PHY.
 */
पूर्णांक phy_पढ़ो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum);

/**
 * phy_पढ़ो_mmd_poll_समयout - Periodically poll a PHY रेजिस्टर until a
 *                             condition is met or a समयout occurs
 *
 * @phydev: The phy_device काष्ठा
 * @devaddr: The MMD to पढ़ो from
 * @regnum: The रेजिस्टर on the MMD to पढ़ो
 * @val: Variable to पढ़ो the रेजिस्टर पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @sleep_us: Maximum समय to sleep between पढ़ोs in us (0
 *            tight-loops).  Should be less than ~20ms since usleep_range
 *            is used (see Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 * @sleep_beक्रमe_पढ़ो: अगर it is true, sleep @sleep_us beक्रमe पढ़ो.
 * Returns 0 on success and -ETIMEDOUT upon a समयout. In either
 * हाल, the last पढ़ो value at @args is stored in @val. Must not
 * be called from atomic context अगर sleep_us or समयout_us are used.
 */
#घोषणा phy_पढ़ो_mmd_poll_समयout(phydev, devaddr, regnum, val, cond, \
				  sleep_us, समयout_us, sleep_beक्रमe_पढ़ो) \
(अणु \
	पूर्णांक __ret = पढ़ो_poll_समयout(phy_पढ़ो_mmd, val, (cond) || val < 0, \
				  sleep_us, समयout_us, sleep_beक्रमe_पढ़ो, \
				  phydev, devaddr, regnum); \
	अगर (val <  0) \
		__ret = val; \
	अगर (__ret) \
		phydev_err(phydev, "%s failed: %d\n", __func__, __ret); \
	__ret; \
पूर्ण)

/*
 * __phy_पढ़ो_mmd - Convenience function क्रम पढ़ोing a रेजिस्टर
 * from an MMD on a given PHY.
 */
पूर्णांक __phy_पढ़ो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum);

/*
 * phy_ग_लिखो_mmd - Convenience function क्रम writing a रेजिस्टर
 * on an MMD on a given PHY.
 */
पूर्णांक phy_ग_लिखो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum, u16 val);

/*
 * __phy_ग_लिखो_mmd - Convenience function क्रम writing a रेजिस्टर
 * on an MMD on a given PHY.
 */
पूर्णांक __phy_ग_लिखो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum, u16 val);

पूर्णांक __phy_modअगरy_changed(काष्ठा phy_device *phydev, u32 regnum, u16 mask,
			 u16 set);
पूर्णांक phy_modअगरy_changed(काष्ठा phy_device *phydev, u32 regnum, u16 mask,
		       u16 set);
पूर्णांक __phy_modअगरy(काष्ठा phy_device *phydev, u32 regnum, u16 mask, u16 set);
पूर्णांक phy_modअगरy(काष्ठा phy_device *phydev, u32 regnum, u16 mask, u16 set);

पूर्णांक __phy_modअगरy_mmd_changed(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
			     u16 mask, u16 set);
पूर्णांक phy_modअगरy_mmd_changed(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
			   u16 mask, u16 set);
पूर्णांक __phy_modअगरy_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
		     u16 mask, u16 set);
पूर्णांक phy_modअगरy_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u32 regnum,
		   u16 mask, u16 set);

/**
 * __phy_set_bits - Convenience function क्रम setting bits in a PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: bits to set
 *
 * The caller must have taken the MDIO bus lock.
 */
अटल अंतरभूत पूर्णांक __phy_set_bits(काष्ठा phy_device *phydev, u32 regnum, u16 val)
अणु
	वापस __phy_modअगरy(phydev, regnum, 0, val);
पूर्ण

/**
 * __phy_clear_bits - Convenience function क्रम clearing bits in a PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: bits to clear
 *
 * The caller must have taken the MDIO bus lock.
 */
अटल अंतरभूत पूर्णांक __phy_clear_bits(काष्ठा phy_device *phydev, u32 regnum,
				   u16 val)
अणु
	वापस __phy_modअगरy(phydev, regnum, val, 0);
पूर्ण

/**
 * phy_set_bits - Convenience function क्रम setting bits in a PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: bits to set
 */
अटल अंतरभूत पूर्णांक phy_set_bits(काष्ठा phy_device *phydev, u32 regnum, u16 val)
अणु
	वापस phy_modअगरy(phydev, regnum, 0, val);
पूर्ण

/**
 * phy_clear_bits - Convenience function क्रम clearing bits in a PHY रेजिस्टर
 * @phydev: the phy_device काष्ठा
 * @regnum: रेजिस्टर number to ग_लिखो
 * @val: bits to clear
 */
अटल अंतरभूत पूर्णांक phy_clear_bits(काष्ठा phy_device *phydev, u32 regnum, u16 val)
अणु
	वापस phy_modअगरy(phydev, regnum, val, 0);
पूर्ण

/**
 * __phy_set_bits_mmd - Convenience function क्रम setting bits in a रेजिस्टर
 * on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @val: bits to set
 *
 * The caller must have taken the MDIO bus lock.
 */
अटल अंतरभूत पूर्णांक __phy_set_bits_mmd(काष्ठा phy_device *phydev, पूर्णांक devad,
		u32 regnum, u16 val)
अणु
	वापस __phy_modअगरy_mmd(phydev, devad, regnum, 0, val);
पूर्ण

/**
 * __phy_clear_bits_mmd - Convenience function क्रम clearing bits in a रेजिस्टर
 * on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @val: bits to clear
 *
 * The caller must have taken the MDIO bus lock.
 */
अटल अंतरभूत पूर्णांक __phy_clear_bits_mmd(काष्ठा phy_device *phydev, पूर्णांक devad,
		u32 regnum, u16 val)
अणु
	वापस __phy_modअगरy_mmd(phydev, devad, regnum, val, 0);
पूर्ण

/**
 * phy_set_bits_mmd - Convenience function क्रम setting bits in a रेजिस्टर
 * on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @val: bits to set
 */
अटल अंतरभूत पूर्णांक phy_set_bits_mmd(काष्ठा phy_device *phydev, पूर्णांक devad,
		u32 regnum, u16 val)
अणु
	वापस phy_modअगरy_mmd(phydev, devad, regnum, 0, val);
पूर्ण

/**
 * phy_clear_bits_mmd - Convenience function क्रम clearing bits in a रेजिस्टर
 * on MMD
 * @phydev: the phy_device काष्ठा
 * @devad: the MMD containing रेजिस्टर to modअगरy
 * @regnum: रेजिस्टर number to modअगरy
 * @val: bits to clear
 */
अटल अंतरभूत पूर्णांक phy_clear_bits_mmd(काष्ठा phy_device *phydev, पूर्णांक devad,
		u32 regnum, u16 val)
अणु
	वापस phy_modअगरy_mmd(phydev, devad, regnum, val, 0);
पूर्ण

/**
 * phy_पूर्णांकerrupt_is_valid - Convenience function क्रम testing a given PHY irq
 * @phydev: the phy_device काष्ठा
 *
 * NOTE: must be kept in sync with addition/removal of PHY_POLL and
 * PHY_MAC_INTERRUPT
 */
अटल अंतरभूत bool phy_पूर्णांकerrupt_is_valid(काष्ठा phy_device *phydev)
अणु
	वापस phydev->irq != PHY_POLL && phydev->irq != PHY_MAC_INTERRUPT;
पूर्ण

/**
 * phy_polling_mode - Convenience function क्रम testing whether polling is
 * used to detect PHY status changes
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_polling_mode(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->state == PHY_CABLETEST)
		अगर (phydev->drv->flags & PHY_POLL_CABLE_TEST)
			वापस true;

	वापस phydev->irq == PHY_POLL;
पूर्ण

/**
 * phy_has_hwtstamp - Tests whether a PHY समय stamp configuration.
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_has_hwtstamp(काष्ठा phy_device *phydev)
अणु
	वापस phydev && phydev->mii_ts && phydev->mii_ts->hwtstamp;
पूर्ण

/**
 * phy_has_rxtstamp - Tests whether a PHY supports receive समय stamping.
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_has_rxtstamp(काष्ठा phy_device *phydev)
अणु
	वापस phydev && phydev->mii_ts && phydev->mii_ts->rxtstamp;
पूर्ण

/**
 * phy_has_tsinfo - Tests whether a PHY reports समय stamping and/or
 * PTP hardware घड़ी capabilities.
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_has_tsinfo(काष्ठा phy_device *phydev)
अणु
	वापस phydev && phydev->mii_ts && phydev->mii_ts->ts_info;
पूर्ण

/**
 * phy_has_txtstamp - Tests whether a PHY supports transmit समय stamping.
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_has_txtstamp(काष्ठा phy_device *phydev)
अणु
	वापस phydev && phydev->mii_ts && phydev->mii_ts->txtstamp;
पूर्ण

अटल अंतरभूत पूर्णांक phy_hwtstamp(काष्ठा phy_device *phydev, काष्ठा अगरreq *अगरr)
अणु
	वापस phydev->mii_ts->hwtstamp(phydev->mii_ts, अगरr);
पूर्ण

अटल अंतरभूत bool phy_rxtstamp(काष्ठा phy_device *phydev, काष्ठा sk_buff *skb,
				पूर्णांक type)
अणु
	वापस phydev->mii_ts->rxtstamp(phydev->mii_ts, skb, type);
पूर्ण

अटल अंतरभूत पूर्णांक phy_ts_info(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_ts_info *tsinfo)
अणु
	वापस phydev->mii_ts->ts_info(phydev->mii_ts, tsinfo);
पूर्ण

अटल अंतरभूत व्योम phy_txtstamp(काष्ठा phy_device *phydev, काष्ठा sk_buff *skb,
				पूर्णांक type)
अणु
	phydev->mii_ts->txtstamp(phydev->mii_ts, skb, type);
पूर्ण

/**
 * phy_is_पूर्णांकernal - Convenience function क्रम testing अगर a PHY is पूर्णांकernal
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_is_पूर्णांकernal(काष्ठा phy_device *phydev)
अणु
	वापस phydev->is_पूर्णांकernal;
पूर्ण

/**
 * phy_on_sfp - Convenience function क्रम testing अगर a PHY is on an SFP module
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_on_sfp(काष्ठा phy_device *phydev)
अणु
	वापस phydev->is_on_sfp_module;
पूर्ण

/**
 * phy_पूर्णांकerface_mode_is_rgmii - Convenience function क्रम testing अगर a
 * PHY पूर्णांकerface mode is RGMII (all variants)
 * @mode: the &phy_पूर्णांकerface_t क्रमागत
 */
अटल अंतरभूत bool phy_पूर्णांकerface_mode_is_rgmii(phy_पूर्णांकerface_t mode)
अणु
	वापस mode >= PHY_INTERFACE_MODE_RGMII &&
		mode <= PHY_INTERFACE_MODE_RGMII_TXID;
पूर्ण;

/**
 * phy_पूर्णांकerface_mode_is_8023z() - करोes the PHY पूर्णांकerface mode use 802.3z
 *   negotiation
 * @mode: one of &क्रमागत phy_पूर्णांकerface_t
 *
 * Returns true अगर the PHY पूर्णांकerface mode uses the 16-bit negotiation
 * word as defined in 802.3z. (See 802.3-2015 37.2.1 Config_Reg encoding)
 */
अटल अंतरभूत bool phy_पूर्णांकerface_mode_is_8023z(phy_पूर्णांकerface_t mode)
अणु
	वापस mode == PHY_INTERFACE_MODE_1000BASEX ||
	       mode == PHY_INTERFACE_MODE_2500BASEX;
पूर्ण

/**
 * phy_पूर्णांकerface_is_rgmii - Convenience function क्रम testing अगर a PHY पूर्णांकerface
 * is RGMII (all variants)
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_पूर्णांकerface_is_rgmii(काष्ठा phy_device *phydev)
अणु
	वापस phy_पूर्णांकerface_mode_is_rgmii(phydev->पूर्णांकerface);
पूर्ण;

/**
 * phy_is_pseuकरो_fixed_link - Convenience function क्रम testing अगर this
 * PHY is the CPU port facing side of an Ethernet चयन, or similar.
 * @phydev: the phy_device काष्ठा
 */
अटल अंतरभूत bool phy_is_pseuकरो_fixed_link(काष्ठा phy_device *phydev)
अणु
	वापस phydev->is_pseuकरो_fixed_link;
पूर्ण

पूर्णांक phy_save_page(काष्ठा phy_device *phydev);
पूर्णांक phy_select_page(काष्ठा phy_device *phydev, पूर्णांक page);
पूर्णांक phy_restore_page(काष्ठा phy_device *phydev, पूर्णांक oldpage, पूर्णांक ret);
पूर्णांक phy_पढ़ो_paged(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum);
पूर्णांक phy_ग_लिखो_paged(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum, u16 val);
पूर्णांक phy_modअगरy_paged_changed(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum,
			     u16 mask, u16 set);
पूर्णांक phy_modअगरy_paged(काष्ठा phy_device *phydev, पूर्णांक page, u32 regnum,
		     u16 mask, u16 set);

काष्ठा phy_device *phy_device_create(काष्ठा mii_bus *bus, पूर्णांक addr, u32 phy_id,
				     bool is_c45,
				     काष्ठा phy_c45_device_ids *c45_ids);
#अगर IS_ENABLED(CONFIG_PHYLIB)
काष्ठा phy_device *get_phy_device(काष्ठा mii_bus *bus, पूर्णांक addr, bool is_c45);
पूर्णांक phy_device_रेजिस्टर(काष्ठा phy_device *phy);
व्योम phy_device_मुक्त(काष्ठा phy_device *phydev);
#अन्यथा
अटल अंतरभूत
काष्ठा phy_device *get_phy_device(काष्ठा mii_bus *bus, पूर्णांक addr, bool is_c45)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक phy_device_रेजिस्टर(काष्ठा phy_device *phy)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम phy_device_मुक्त(काष्ठा phy_device *phydev) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PHYLIB */
व्योम phy_device_हटाओ(काष्ठा phy_device *phydev);
पूर्णांक phy_init_hw(काष्ठा phy_device *phydev);
पूर्णांक phy_suspend(काष्ठा phy_device *phydev);
पूर्णांक phy_resume(काष्ठा phy_device *phydev);
पूर्णांक __phy_resume(काष्ठा phy_device *phydev);
पूर्णांक phy_loopback(काष्ठा phy_device *phydev, bool enable);
व्योम phy_sfp_attach(व्योम *upstream, काष्ठा sfp_bus *bus);
व्योम phy_sfp_detach(व्योम *upstream, काष्ठा sfp_bus *bus);
पूर्णांक phy_sfp_probe(काष्ठा phy_device *phydev,
	          स्थिर काष्ठा sfp_upstream_ops *ops);
काष्ठा phy_device *phy_attach(काष्ठा net_device *dev, स्थिर अक्षर *bus_id,
			      phy_पूर्णांकerface_t पूर्णांकerface);
काष्ठा phy_device *phy_find_first(काष्ठा mii_bus *bus);
पूर्णांक phy_attach_direct(काष्ठा net_device *dev, काष्ठा phy_device *phydev,
		      u32 flags, phy_पूर्णांकerface_t पूर्णांकerface);
पूर्णांक phy_connect_direct(काष्ठा net_device *dev, काष्ठा phy_device *phydev,
		       व्योम (*handler)(काष्ठा net_device *),
		       phy_पूर्णांकerface_t पूर्णांकerface);
काष्ठा phy_device *phy_connect(काष्ठा net_device *dev, स्थिर अक्षर *bus_id,
			       व्योम (*handler)(काष्ठा net_device *),
			       phy_पूर्णांकerface_t पूर्णांकerface);
व्योम phy_disconnect(काष्ठा phy_device *phydev);
व्योम phy_detach(काष्ठा phy_device *phydev);
व्योम phy_start(काष्ठा phy_device *phydev);
व्योम phy_stop(काष्ठा phy_device *phydev);
पूर्णांक phy_config_aneg(काष्ठा phy_device *phydev);
पूर्णांक phy_start_aneg(काष्ठा phy_device *phydev);
पूर्णांक phy_aneg_करोne(काष्ठा phy_device *phydev);
पूर्णांक phy_speed_करोwn(काष्ठा phy_device *phydev, bool sync);
पूर्णांक phy_speed_up(काष्ठा phy_device *phydev);

पूर्णांक phy_restart_aneg(काष्ठा phy_device *phydev);
पूर्णांक phy_reset_after_clk_enable(काष्ठा phy_device *phydev);

#अगर IS_ENABLED(CONFIG_PHYLIB)
पूर्णांक phy_start_cable_test(काष्ठा phy_device *phydev,
			 काष्ठा netlink_ext_ack *extack);
पूर्णांक phy_start_cable_test_tdr(काष्ठा phy_device *phydev,
			     काष्ठा netlink_ext_ack *extack,
			     स्थिर काष्ठा phy_tdr_config *config);
#अन्यथा
अटल अंतरभूत
पूर्णांक phy_start_cable_test(काष्ठा phy_device *phydev,
			 काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG(extack, "Kernel not compiled with PHYLIB support");
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत
पूर्णांक phy_start_cable_test_tdr(काष्ठा phy_device *phydev,
			     काष्ठा netlink_ext_ack *extack,
			     स्थिर काष्ठा phy_tdr_config *config)
अणु
	NL_SET_ERR_MSG(extack, "Kernel not compiled with PHYLIB support");
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

पूर्णांक phy_cable_test_result(काष्ठा phy_device *phydev, u8 pair, u16 result);
पूर्णांक phy_cable_test_fault_length(काष्ठा phy_device *phydev, u8 pair,
				u16 cm);

अटल अंतरभूत व्योम phy_device_reset(काष्ठा phy_device *phydev, पूर्णांक value)
अणु
	mdio_device_reset(&phydev->mdio, value);
पूर्ण

#घोषणा phydev_err(_phydev, क्रमmat, args...)	\
	dev_err(&_phydev->mdio.dev, क्रमmat, ##args)

#घोषणा phydev_info(_phydev, क्रमmat, args...)	\
	dev_info(&_phydev->mdio.dev, क्रमmat, ##args)

#घोषणा phydev_warn(_phydev, क्रमmat, args...)	\
	dev_warn(&_phydev->mdio.dev, क्रमmat, ##args)

#घोषणा phydev_dbg(_phydev, क्रमmat, args...)	\
	dev_dbg(&_phydev->mdio.dev, क्रमmat, ##args)

अटल अंतरभूत स्थिर अक्षर *phydev_name(स्थिर काष्ठा phy_device *phydev)
अणु
	वापस dev_name(&phydev->mdio.dev);
पूर्ण

अटल अंतरभूत व्योम phy_lock_mdio_bus(काष्ठा phy_device *phydev)
अणु
	mutex_lock(&phydev->mdio.bus->mdio_lock);
पूर्ण

अटल अंतरभूत व्योम phy_unlock_mdio_bus(काष्ठा phy_device *phydev)
अणु
	mutex_unlock(&phydev->mdio.bus->mdio_lock);
पूर्ण

व्योम phy_attached_prपूर्णांक(काष्ठा phy_device *phydev, स्थिर अक्षर *fmt, ...)
	__म_लिखो(2, 3);
अक्षर *phy_attached_info_irq(काष्ठा phy_device *phydev)
	__दो_स्मृति;
व्योम phy_attached_info(काष्ठा phy_device *phydev);

/* Clause 22 PHY */
पूर्णांक genphy_पढ़ो_abilities(काष्ठा phy_device *phydev);
पूर्णांक genphy_setup_क्रमced(काष्ठा phy_device *phydev);
पूर्णांक genphy_restart_aneg(काष्ठा phy_device *phydev);
पूर्णांक genphy_check_and_restart_aneg(काष्ठा phy_device *phydev, bool restart);
पूर्णांक genphy_config_eee_advert(काष्ठा phy_device *phydev);
पूर्णांक __genphy_config_aneg(काष्ठा phy_device *phydev, bool changed);
पूर्णांक genphy_aneg_करोne(काष्ठा phy_device *phydev);
पूर्णांक genphy_update_link(काष्ठा phy_device *phydev);
पूर्णांक genphy_पढ़ो_lpa(काष्ठा phy_device *phydev);
पूर्णांक genphy_पढ़ो_status_fixed(काष्ठा phy_device *phydev);
पूर्णांक genphy_पढ़ो_status(काष्ठा phy_device *phydev);
पूर्णांक genphy_suspend(काष्ठा phy_device *phydev);
पूर्णांक genphy_resume(काष्ठा phy_device *phydev);
पूर्णांक genphy_loopback(काष्ठा phy_device *phydev, bool enable);
पूर्णांक genphy_soft_reset(काष्ठा phy_device *phydev);
irqवापस_t genphy_handle_पूर्णांकerrupt_no_ack(काष्ठा phy_device *phydev);

अटल अंतरभूत पूर्णांक genphy_config_aneg(काष्ठा phy_device *phydev)
अणु
	वापस __genphy_config_aneg(phydev, false);
पूर्ण

अटल अंतरभूत पूर्णांक genphy_no_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
पूर्णांक genphy_पढ़ो_mmd_unsupported(काष्ठा phy_device *phdev, पूर्णांक devad,
				u16 regnum);
पूर्णांक genphy_ग_लिखो_mmd_unsupported(काष्ठा phy_device *phdev, पूर्णांक devnum,
				 u16 regnum, u16 val);

/* Clause 37 */
पूर्णांक genphy_c37_config_aneg(काष्ठा phy_device *phydev);
पूर्णांक genphy_c37_पढ़ो_status(काष्ठा phy_device *phydev);

/* Clause 45 PHY */
पूर्णांक genphy_c45_restart_aneg(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_check_and_restart_aneg(काष्ठा phy_device *phydev, bool restart);
पूर्णांक genphy_c45_aneg_करोne(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_पढ़ो_link(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_पढ़ो_lpa(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_पढ़ो_pma(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_pma_setup_क्रमced(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_an_config_aneg(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_an_disable_aneg(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_पढ़ो_mdix(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_pma_पढ़ो_abilities(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_पढ़ो_status(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_config_aneg(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_loopback(काष्ठा phy_device *phydev, bool enable);
पूर्णांक genphy_c45_pma_resume(काष्ठा phy_device *phydev);
पूर्णांक genphy_c45_pma_suspend(काष्ठा phy_device *phydev);

/* Generic C45 PHY driver */
बाह्य काष्ठा phy_driver genphy_c45_driver;

/* The gen10g_* functions are the old Clause 45 stub */
पूर्णांक gen10g_config_aneg(काष्ठा phy_device *phydev);

अटल अंतरभूत पूर्णांक phy_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	अगर (!phydev->drv)
		वापस -EIO;

	अगर (phydev->drv->पढ़ो_status)
		वापस phydev->drv->पढ़ो_status(phydev);
	अन्यथा
		वापस genphy_पढ़ो_status(phydev);
पूर्ण

व्योम phy_driver_unरेजिस्टर(काष्ठा phy_driver *drv);
व्योम phy_drivers_unरेजिस्टर(काष्ठा phy_driver *drv, पूर्णांक n);
पूर्णांक phy_driver_रेजिस्टर(काष्ठा phy_driver *new_driver, काष्ठा module *owner);
पूर्णांक phy_drivers_रेजिस्टर(काष्ठा phy_driver *new_driver, पूर्णांक n,
			 काष्ठा module *owner);
व्योम phy_error(काष्ठा phy_device *phydev);
व्योम phy_state_machine(काष्ठा work_काष्ठा *work);
व्योम phy_queue_state_machine(काष्ठा phy_device *phydev, अचिन्हित दीर्घ jअगरfies);
व्योम phy_trigger_machine(काष्ठा phy_device *phydev);
व्योम phy_mac_पूर्णांकerrupt(काष्ठा phy_device *phydev);
व्योम phy_start_machine(काष्ठा phy_device *phydev);
व्योम phy_stop_machine(काष्ठा phy_device *phydev);
व्योम phy_ethtool_ksettings_get(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक phy_ethtool_ksettings_set(काष्ठा phy_device *phydev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक phy_mii_ioctl(काष्ठा phy_device *phydev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
पूर्णांक phy_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
पूर्णांक phy_करो_ioctl_running(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
पूर्णांक phy_disable_पूर्णांकerrupts(काष्ठा phy_device *phydev);
व्योम phy_request_पूर्णांकerrupt(काष्ठा phy_device *phydev);
व्योम phy_मुक्त_पूर्णांकerrupt(काष्ठा phy_device *phydev);
व्योम phy_prपूर्णांक_status(काष्ठा phy_device *phydev);
पूर्णांक phy_set_max_speed(काष्ठा phy_device *phydev, u32 max_speed);
व्योम phy_हटाओ_link_mode(काष्ठा phy_device *phydev, u32 link_mode);
व्योम phy_advertise_supported(काष्ठा phy_device *phydev);
व्योम phy_support_sym_छोड़ो(काष्ठा phy_device *phydev);
व्योम phy_support_asym_छोड़ो(काष्ठा phy_device *phydev);
व्योम phy_set_sym_छोड़ो(काष्ठा phy_device *phydev, bool rx, bool tx,
		       bool स्वतःneg);
व्योम phy_set_asym_छोड़ो(काष्ठा phy_device *phydev, bool rx, bool tx);
bool phy_validate_छोड़ो(काष्ठा phy_device *phydev,
			काष्ठा ethtool_छोड़ोparam *pp);
व्योम phy_get_छोड़ो(काष्ठा phy_device *phydev, bool *tx_छोड़ो, bool *rx_छोड़ो);

s32 phy_get_पूर्णांकernal_delay(काष्ठा phy_device *phydev, काष्ठा device *dev,
			   स्थिर पूर्णांक *delay_values, पूर्णांक size, bool is_rx);

व्योम phy_resolve_छोड़ो(अचिन्हित दीर्घ *local_adv, अचिन्हित दीर्घ *partner_adv,
		       bool *tx_छोड़ो, bool *rx_छोड़ो);

पूर्णांक phy_रेजिस्टर_fixup(स्थिर अक्षर *bus_id, u32 phy_uid, u32 phy_uid_mask,
		       पूर्णांक (*run)(काष्ठा phy_device *));
पूर्णांक phy_रेजिस्टर_fixup_क्रम_id(स्थिर अक्षर *bus_id,
			      पूर्णांक (*run)(काष्ठा phy_device *));
पूर्णांक phy_रेजिस्टर_fixup_क्रम_uid(u32 phy_uid, u32 phy_uid_mask,
			       पूर्णांक (*run)(काष्ठा phy_device *));

पूर्णांक phy_unरेजिस्टर_fixup(स्थिर अक्षर *bus_id, u32 phy_uid, u32 phy_uid_mask);
पूर्णांक phy_unरेजिस्टर_fixup_क्रम_id(स्थिर अक्षर *bus_id);
पूर्णांक phy_unरेजिस्टर_fixup_क्रम_uid(u32 phy_uid, u32 phy_uid_mask);

पूर्णांक phy_init_eee(काष्ठा phy_device *phydev, bool clk_stop_enable);
पूर्णांक phy_get_eee_err(काष्ठा phy_device *phydev);
पूर्णांक phy_ethtool_set_eee(काष्ठा phy_device *phydev, काष्ठा ethtool_eee *data);
पूर्णांक phy_ethtool_get_eee(काष्ठा phy_device *phydev, काष्ठा ethtool_eee *data);
पूर्णांक phy_ethtool_set_wol(काष्ठा phy_device *phydev, काष्ठा ethtool_wolinfo *wol);
व्योम phy_ethtool_get_wol(काष्ठा phy_device *phydev,
			 काष्ठा ethtool_wolinfo *wol);
पूर्णांक phy_ethtool_get_link_ksettings(काष्ठा net_device *ndev,
				   काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक phy_ethtool_set_link_ksettings(काष्ठा net_device *ndev,
				   स्थिर काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक phy_ethtool_nway_reset(काष्ठा net_device *ndev);
पूर्णांक phy_package_join(काष्ठा phy_device *phydev, पूर्णांक addr, माप_प्रकार priv_size);
व्योम phy_package_leave(काष्ठा phy_device *phydev);
पूर्णांक devm_phy_package_join(काष्ठा device *dev, काष्ठा phy_device *phydev,
			  पूर्णांक addr, माप_प्रकार priv_size);

#अगर IS_ENABLED(CONFIG_PHYLIB)
पूर्णांक __init mdio_bus_init(व्योम);
व्योम mdio_bus_निकास(व्योम);
#पूर्ण_अगर

पूर्णांक phy_ethtool_get_strings(काष्ठा phy_device *phydev, u8 *data);
पूर्णांक phy_ethtool_get_sset_count(काष्ठा phy_device *phydev);
पूर्णांक phy_ethtool_get_stats(काष्ठा phy_device *phydev,
			  काष्ठा ethtool_stats *stats, u64 *data);

अटल अंतरभूत पूर्णांक phy_package_पढ़ो(काष्ठा phy_device *phydev, u32 regnum)
अणु
	काष्ठा phy_package_shared *shared = phydev->shared;

	अगर (!shared)
		वापस -EIO;

	वापस mdiobus_पढ़ो(phydev->mdio.bus, shared->addr, regnum);
पूर्ण

अटल अंतरभूत पूर्णांक __phy_package_पढ़ो(काष्ठा phy_device *phydev, u32 regnum)
अणु
	काष्ठा phy_package_shared *shared = phydev->shared;

	अगर (!shared)
		वापस -EIO;

	वापस __mdiobus_पढ़ो(phydev->mdio.bus, shared->addr, regnum);
पूर्ण

अटल अंतरभूत पूर्णांक phy_package_ग_लिखो(काष्ठा phy_device *phydev,
				    u32 regnum, u16 val)
अणु
	काष्ठा phy_package_shared *shared = phydev->shared;

	अगर (!shared)
		वापस -EIO;

	वापस mdiobus_ग_लिखो(phydev->mdio.bus, shared->addr, regnum, val);
पूर्ण

अटल अंतरभूत पूर्णांक __phy_package_ग_लिखो(काष्ठा phy_device *phydev,
				      u32 regnum, u16 val)
अणु
	काष्ठा phy_package_shared *shared = phydev->shared;

	अगर (!shared)
		वापस -EIO;

	वापस __mdiobus_ग_लिखो(phydev->mdio.bus, shared->addr, regnum, val);
पूर्ण

अटल अंतरभूत bool __phy_package_set_once(काष्ठा phy_device *phydev,
					  अचिन्हित पूर्णांक b)
अणु
	काष्ठा phy_package_shared *shared = phydev->shared;

	अगर (!shared)
		वापस false;

	वापस !test_and_set_bit(b, &shared->flags);
पूर्ण

अटल अंतरभूत bool phy_package_init_once(काष्ठा phy_device *phydev)
अणु
	वापस __phy_package_set_once(phydev, PHY_SHARED_F_INIT_DONE);
पूर्ण

अटल अंतरभूत bool phy_package_probe_once(काष्ठा phy_device *phydev)
अणु
	वापस __phy_package_set_once(phydev, PHY_SHARED_F_PROBE_DONE);
पूर्ण

बाह्य काष्ठा bus_type mdio_bus_type;

काष्ठा mdio_board_info अणु
	स्थिर अक्षर	*bus_id;
	अक्षर		modalias[MDIO_NAME_SIZE];
	पूर्णांक		mdio_addr;
	स्थिर व्योम	*platक्रमm_data;
पूर्ण;

#अगर IS_ENABLED(CONFIG_MDIO_DEVICE)
पूर्णांक mdiobus_रेजिस्टर_board_info(स्थिर काष्ठा mdio_board_info *info,
				अचिन्हित पूर्णांक n);
#अन्यथा
अटल अंतरभूत पूर्णांक mdiobus_रेजिस्टर_board_info(स्थिर काष्ठा mdio_board_info *i,
					      अचिन्हित पूर्णांक n)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर


/**
 * phy_module_driver() - Helper macro क्रम रेजिस्टरing PHY drivers
 * @__phy_drivers: array of PHY drivers to रेजिस्टर
 * @__count: Numbers of members in array
 *
 * Helper macro क्रम PHY drivers which करो not करो anything special in module
 * init/निकास. Each module may only use this macro once, and calling it
 * replaces module_init() and module_निकास().
 */
#घोषणा phy_module_driver(__phy_drivers, __count)			\
अटल पूर्णांक __init phy_module_init(व्योम)					\
अणु									\
	वापस phy_drivers_रेजिस्टर(__phy_drivers, __count, THIS_MODULE); \
पूर्ण									\
module_init(phy_module_init);						\
अटल व्योम __निकास phy_module_निकास(व्योम)				\
अणु									\
	phy_drivers_unरेजिस्टर(__phy_drivers, __count);			\
पूर्ण									\
module_निकास(phy_module_निकास)

#घोषणा module_phy_driver(__phy_drivers)				\
	phy_module_driver(__phy_drivers, ARRAY_SIZE(__phy_drivers))

bool phy_driver_is_genphy(काष्ठा phy_device *phydev);
bool phy_driver_is_genphy_10g(काष्ठा phy_device *phydev);

#पूर्ण_अगर /* __PHY_H */
