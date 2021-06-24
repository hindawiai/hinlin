<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SSB_H_
#घोषणा LINUX_SSB_H_

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/ssb/ssb_regs.h>


काष्ठा pcmcia_device;
काष्ठा ssb_bus;
काष्ठा ssb_driver;

काष्ठा ssb_sprom_core_pwr_info अणु
	u8 itssi_2g, itssi_5g;
	u8 maxpwr_2g, maxpwr_5gl, maxpwr_5g, maxpwr_5gh;
	u16 pa_2g[4], pa_5gl[4], pa_5g[4], pa_5gh[4];
पूर्ण;

काष्ठा ssb_sprom अणु
	u8 revision;
	u8 il0mac[6] __aligned(माप(u16));	/* MAC address क्रम 802.11b/g */
	u8 et0mac[6] __aligned(माप(u16));	/* MAC address क्रम Ethernet */
	u8 et1mac[6] __aligned(माप(u16));	/* MAC address क्रम 802.11a */
	u8 et2mac[6] __aligned(माप(u16));	/* MAC address क्रम extra Ethernet */
	u8 et0phyaddr;		/* MII address क्रम enet0 */
	u8 et1phyaddr;		/* MII address क्रम enet1 */
	u8 et2phyaddr;		/* MII address क्रम enet2 */
	u8 et0mdcport;		/* MDIO क्रम enet0 */
	u8 et1mdcport;		/* MDIO क्रम enet1 */
	u8 et2mdcport;		/* MDIO क्रम enet2 */
	u16 dev_id;		/* Device ID overriding e.g. PCI ID */
	u16 board_rev;		/* Board revision number from SPROM. */
	u16 board_num;		/* Board number from SPROM. */
	u16 board_type;		/* Board type from SPROM. */
	u8 country_code;	/* Country Code */
	अक्षर alpha2[2];		/* Country Code as two अक्षरs like EU or US */
	u8 leddc_on_समय;	/* LED Powersave Duty Cycle On Count */
	u8 leddc_off_समय;	/* LED Powersave Duty Cycle Off Count */
	u8 ant_available_a;	/* 2GHz antenna available bits (up to 4) */
	u8 ant_available_bg;	/* 5GHz antenna available bits (up to 4) */
	u16 pa0b0;
	u16 pa0b1;
	u16 pa0b2;
	u16 pa1b0;
	u16 pa1b1;
	u16 pa1b2;
	u16 pa1lob0;
	u16 pa1lob1;
	u16 pa1lob2;
	u16 pa1hib0;
	u16 pa1hib1;
	u16 pa1hib2;
	u8 gpio0;		/* GPIO pin 0 */
	u8 gpio1;		/* GPIO pin 1 */
	u8 gpio2;		/* GPIO pin 2 */
	u8 gpio3;		/* GPIO pin 3 */
	u8 maxpwr_bg;		/* 2.4GHz Amplअगरier Max Power (in dBm Q5.2) */
	u8 maxpwr_al;		/* 5.2GHz Amplअगरier Max Power (in dBm Q5.2) */
	u8 maxpwr_a;		/* 5.3GHz Amplअगरier Max Power (in dBm Q5.2) */
	u8 maxpwr_ah;		/* 5.8GHz Amplअगरier Max Power (in dBm Q5.2) */
	u8 itssi_a;		/* Idle TSSI Target क्रम A-PHY */
	u8 itssi_bg;		/* Idle TSSI Target क्रम B/G-PHY */
	u8 tri2g;		/* 2.4GHz TX isolation */
	u8 tri5gl;		/* 5.2GHz TX isolation */
	u8 tri5g;		/* 5.3GHz TX isolation */
	u8 tri5gh;		/* 5.8GHz TX isolation */
	u8 txpid2g[4];		/* 2GHz TX घातer index */
	u8 txpid5gl[4];		/* 4.9 - 5.1GHz TX घातer index */
	u8 txpid5g[4];		/* 5.1 - 5.5GHz TX घातer index */
	u8 txpid5gh[4];		/* 5.5 - ...GHz TX घातer index */
	s8 rxpo2g;		/* 2GHz RX घातer offset */
	s8 rxpo5g;		/* 5GHz RX घातer offset */
	u8 rssisav2g;		/* 2GHz RSSI params */
	u8 rssismc2g;
	u8 rssismf2g;
	u8 bxa2g;		/* 2GHz BX arch */
	u8 rssisav5g;		/* 5GHz RSSI params */
	u8 rssismc5g;
	u8 rssismf5g;
	u8 bxa5g;		/* 5GHz BX arch */
	u16 cck2gpo;		/* CCK घातer offset */
	u32 ofdm2gpo;		/* 2.4GHz OFDM घातer offset */
	u32 ofdm5glpo;		/* 5.2GHz OFDM घातer offset */
	u32 ofdm5gpo;		/* 5.3GHz OFDM घातer offset */
	u32 ofdm5ghpo;		/* 5.8GHz OFDM घातer offset */
	u32 boardflags;
	u32 boardflags2;
	u32 boardflags3;
	/* TODO: Switch all drivers to new u32 fields and drop below ones */
	u16 boardflags_lo;	/* Board flags (bits 0-15) */
	u16 boardflags_hi;	/* Board flags (bits 16-31) */
	u16 boardflags2_lo;	/* Board flags (bits 32-47) */
	u16 boardflags2_hi;	/* Board flags (bits 48-63) */

	काष्ठा ssb_sprom_core_pwr_info core_pwr_info[4];

	/* Antenna gain values क्रम up to 4 antennas
	 * on each band. Values in dBm/4 (Q5.2). Negative gain means the
	 * loss in the connectors is bigger than the gain. */
	काष्ठा अणु
		s8 a0, a1, a2, a3;
	पूर्ण antenna_gain;

	काष्ठा अणु
		काष्ठा अणु
			u8 tssipos, extpa_gain, pdet_range, tr_iso, antswlut;
		पूर्ण ghz2;
		काष्ठा अणु
			u8 tssipos, extpa_gain, pdet_range, tr_iso, antswlut;
		पूर्ण ghz5;
	पूर्ण fem;

	u16 mcs2gpo[8];
	u16 mcs5gpo[8];
	u16 mcs5glpo[8];
	u16 mcs5ghpo[8];
	u8 opo;

	u8 rxgainerr2ga[3];
	u8 rxgainerr5gla[3];
	u8 rxgainerr5gma[3];
	u8 rxgainerr5gha[3];
	u8 rxgainerr5gua[3];

	u8 noiselvl2ga[3];
	u8 noiselvl5gla[3];
	u8 noiselvl5gma[3];
	u8 noiselvl5gha[3];
	u8 noiselvl5gua[3];

	u8 regrev;
	u8 txchain;
	u8 rxchain;
	u8 antचयन;
	u16 cddpo;
	u16 stbcpo;
	u16 bw40po;
	u16 bwduppo;

	u8 tempthresh;
	u8 tempoffset;
	u16 rawtempsense;
	u8 measघातer;
	u8 tempsense_slope;
	u8 tempcorrx;
	u8 tempsense_option;
	u8 freqoffset_corr;
	u8 iqcal_swp_dis;
	u8 hw_iqcal_en;
	u8 elna2g;
	u8 elna5g;
	u8 phycal_tempdelta;
	u8 temps_period;
	u8 temps_hysteresis;
	u8 measघातer1;
	u8 measघातer2;
	u8 pcieingress_war;

	/* घातer per rate from sromrev 9 */
	u16 cckbw202gpo;
	u16 cckbw20ul2gpo;
	u32 legofdmbw202gpo;
	u32 legofdmbw20ul2gpo;
	u32 legofdmbw205glpo;
	u32 legofdmbw20ul5glpo;
	u32 legofdmbw205gmpo;
	u32 legofdmbw20ul5gmpo;
	u32 legofdmbw205ghpo;
	u32 legofdmbw20ul5ghpo;
	u32 mcsbw202gpo;
	u32 mcsbw20ul2gpo;
	u32 mcsbw402gpo;
	u32 mcsbw205glpo;
	u32 mcsbw20ul5glpo;
	u32 mcsbw405glpo;
	u32 mcsbw205gmpo;
	u32 mcsbw20ul5gmpo;
	u32 mcsbw405gmpo;
	u32 mcsbw205ghpo;
	u32 mcsbw20ul5ghpo;
	u32 mcsbw405ghpo;
	u16 mcs32po;
	u16 legofdm40duppo;
	u8 sar2g;
	u8 sar5g;
पूर्ण;

/* Inक्रमmation about the PCB the circuitry is soldered on. */
काष्ठा ssb_boardinfo अणु
	u16 venकरोr;
	u16 type;
पूर्ण;


काष्ठा ssb_device;
/* Lowlevel पढ़ो/ग_लिखो operations on the device MMIO.
 * Internal, करोn't use that outside of ssb. */
काष्ठा ssb_bus_ops अणु
	u8 (*पढ़ो8)(काष्ठा ssb_device *dev, u16 offset);
	u16 (*पढ़ो16)(काष्ठा ssb_device *dev, u16 offset);
	u32 (*पढ़ो32)(काष्ठा ssb_device *dev, u16 offset);
	व्योम (*ग_लिखो8)(काष्ठा ssb_device *dev, u16 offset, u8 value);
	व्योम (*ग_लिखो16)(काष्ठा ssb_device *dev, u16 offset, u16 value);
	व्योम (*ग_लिखो32)(काष्ठा ssb_device *dev, u16 offset, u32 value);
#अगर_घोषित CONFIG_SSB_BLOCKIO
	व्योम (*block_पढ़ो)(काष्ठा ssb_device *dev, व्योम *buffer,
			   माप_प्रकार count, u16 offset, u8 reg_width);
	व्योम (*block_ग_लिखो)(काष्ठा ssb_device *dev, स्थिर व्योम *buffer,
			    माप_प्रकार count, u16 offset, u8 reg_width);
#पूर्ण_अगर
पूर्ण;


/* Core-ID values. */
#घोषणा SSB_DEV_CHIPCOMMON	0x800
#घोषणा SSB_DEV_ILINE20		0x801
#घोषणा SSB_DEV_SDRAM		0x803
#घोषणा SSB_DEV_PCI		0x804
#घोषणा SSB_DEV_MIPS		0x805
#घोषणा SSB_DEV_ETHERNET	0x806
#घोषणा SSB_DEV_V90		0x807
#घोषणा SSB_DEV_USB11_HOSTDEV	0x808
#घोषणा SSB_DEV_ADSL		0x809
#घोषणा SSB_DEV_ILINE100	0x80A
#घोषणा SSB_DEV_IPSEC		0x80B
#घोषणा SSB_DEV_PCMCIA		0x80D
#घोषणा SSB_DEV_INTERNAL_MEM	0x80E
#घोषणा SSB_DEV_MEMC_SDRAM	0x80F
#घोषणा SSB_DEV_EXTIF		0x811
#घोषणा SSB_DEV_80211		0x812
#घोषणा SSB_DEV_MIPS_3302	0x816
#घोषणा SSB_DEV_USB11_HOST	0x817
#घोषणा SSB_DEV_USB11_DEV	0x818
#घोषणा SSB_DEV_USB20_HOST	0x819
#घोषणा SSB_DEV_USB20_DEV	0x81A
#घोषणा SSB_DEV_SDIO_HOST	0x81B
#घोषणा SSB_DEV_ROBOSWITCH	0x81C
#घोषणा SSB_DEV_PARA_ATA	0x81D
#घोषणा SSB_DEV_SATA_XORDMA	0x81E
#घोषणा SSB_DEV_ETHERNET_GBIT	0x81F
#घोषणा SSB_DEV_PCIE		0x820
#घोषणा SSB_DEV_MIMO_PHY	0x821
#घोषणा SSB_DEV_SRAM_CTRLR	0x822
#घोषणा SSB_DEV_MINI_MACPHY	0x823
#घोषणा SSB_DEV_ARM_1176	0x824
#घोषणा SSB_DEV_ARM_7TDMI	0x825
#घोषणा SSB_DEV_ARM_CM3		0x82A

/* Venकरोr-ID values */
#घोषणा SSB_VENDOR_BROADCOM	0x4243

/* Some kernel subप्रणालीs poke with dev->drvdata, so we must use the
 * following ugly workaround to get from काष्ठा device to काष्ठा ssb_device */
काष्ठा __ssb_dev_wrapper अणु
	काष्ठा device dev;
	काष्ठा ssb_device *sdev;
पूर्ण;

काष्ठा ssb_device अणु
	/* Having a copy of the ops poपूर्णांकer in each dev काष्ठा
	 * is an optimization. */
	स्थिर काष्ठा ssb_bus_ops *ops;

	काष्ठा device *dev, *dma_dev;

	काष्ठा ssb_bus *bus;
	काष्ठा ssb_device_id id;

	u8 core_index;
	अचिन्हित पूर्णांक irq;

	/* Internal-only stuff follows. */
	व्योम *drvdata;		/* Per-device data */
	व्योम *devtypedata;	/* Per-devicetype (eg 802.11) data */
पूर्ण;

/* Go from काष्ठा device to काष्ठा ssb_device. */
अटल अंतरभूत
काष्ठा ssb_device * dev_to_ssb_dev(काष्ठा device *dev)
अणु
	काष्ठा __ssb_dev_wrapper *wrap;
	wrap = container_of(dev, काष्ठा __ssb_dev_wrapper, dev);
	वापस wrap->sdev;
पूर्ण

/* Device specअगरic user data */
अटल अंतरभूत
व्योम ssb_set_drvdata(काष्ठा ssb_device *dev, व्योम *data)
अणु
	dev->drvdata = data;
पूर्ण
अटल अंतरभूत
व्योम * ssb_get_drvdata(काष्ठा ssb_device *dev)
अणु
	वापस dev->drvdata;
पूर्ण

/* Devicetype specअगरic user data. This is per device-type (not per device) */
व्योम ssb_set_devtypedata(काष्ठा ssb_device *dev, व्योम *data);
अटल अंतरभूत
व्योम * ssb_get_devtypedata(काष्ठा ssb_device *dev)
अणु
	वापस dev->devtypedata;
पूर्ण


काष्ठा ssb_driver अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा ssb_device_id *id_table;

	पूर्णांक (*probe)(काष्ठा ssb_device *dev, स्थिर काष्ठा ssb_device_id *id);
	व्योम (*हटाओ)(काष्ठा ssb_device *dev);
	पूर्णांक (*suspend)(काष्ठा ssb_device *dev, pm_message_t state);
	पूर्णांक (*resume)(काष्ठा ssb_device *dev);
	व्योम (*shutकरोwn)(काष्ठा ssb_device *dev);

	काष्ठा device_driver drv;
पूर्ण;
#घोषणा drv_to_ssb_drv(_drv) container_of(_drv, काष्ठा ssb_driver, drv)

बाह्य पूर्णांक __ssb_driver_रेजिस्टर(काष्ठा ssb_driver *drv, काष्ठा module *owner);
#घोषणा ssb_driver_रेजिस्टर(drv) \
	__ssb_driver_रेजिस्टर(drv, THIS_MODULE)

बाह्य व्योम ssb_driver_unरेजिस्टर(काष्ठा ssb_driver *drv);




क्रमागत ssb_bustype अणु
	SSB_BUSTYPE_SSB,	/* This SSB bus is the प्रणाली bus */
	SSB_BUSTYPE_PCI,	/* SSB is connected to PCI bus */
	SSB_BUSTYPE_PCMCIA,	/* SSB is connected to PCMCIA bus */
	SSB_BUSTYPE_SDIO,	/* SSB is connected to SDIO bus */
पूर्ण;

/* board_venकरोr */
#घोषणा SSB_BOARDVENDOR_BCM	0x14E4	/* Broadcom */
#घोषणा SSB_BOARDVENDOR_DELL	0x1028	/* Dell */
#घोषणा SSB_BOARDVENDOR_HP	0x0E11	/* HP */
/* board_type */
#घोषणा SSB_BOARD_BCM94301CB	0x0406
#घोषणा SSB_BOARD_BCM94301MP	0x0407
#घोषणा SSB_BOARD_BU4309	0x040A
#घोषणा SSB_BOARD_BCM94309CB	0x040B
#घोषणा SSB_BOARD_BCM4309MP	0x040C
#घोषणा SSB_BOARD_BU4306	0x0416
#घोषणा SSB_BOARD_BCM94306MP	0x0418
#घोषणा SSB_BOARD_BCM4309G	0x0421
#घोषणा SSB_BOARD_BCM4306CB	0x0417
#घोषणा SSB_BOARD_BCM94306PC	0x0425	/* pcmcia 3.3v 4306 card */
#घोषणा SSB_BOARD_BCM94306CBSG	0x042B	/* with SiGe PA */
#घोषणा SSB_BOARD_PCSG94306	0x042D	/* with SiGe PA */
#घोषणा SSB_BOARD_BU4704SD	0x042E	/* with sdram */
#घोषणा SSB_BOARD_BCM94704AGR	0x042F	/* dual 11a/11g Router */
#घोषणा SSB_BOARD_BCM94308MP	0x0430	/* 11a-only minipci */
#घोषणा SSB_BOARD_BU4318	0x0447
#घोषणा SSB_BOARD_CB4318	0x0448
#घोषणा SSB_BOARD_MPG4318	0x0449
#घोषणा SSB_BOARD_MP4318	0x044A
#घोषणा SSB_BOARD_SD4318	0x044B
#घोषणा SSB_BOARD_BCM94306P	0x044C	/* with SiGe */
#घोषणा SSB_BOARD_BCM94303MP	0x044E
#घोषणा SSB_BOARD_BCM94306MPM	0x0450
#घोषणा SSB_BOARD_BCM94306MPL	0x0453
#घोषणा SSB_BOARD_PC4303	0x0454	/* pcmcia */
#घोषणा SSB_BOARD_BCM94306MPLNA	0x0457
#घोषणा SSB_BOARD_BCM94306MPH	0x045B
#घोषणा SSB_BOARD_BCM94306PCIV	0x045C
#घोषणा SSB_BOARD_BCM94318MPGH	0x0463
#घोषणा SSB_BOARD_BU4311	0x0464
#घोषणा SSB_BOARD_BCM94311MC	0x0465
#घोषणा SSB_BOARD_BCM94311MCAG	0x0466
/* 4321 boards */
#घोषणा SSB_BOARD_BU4321	0x046B
#घोषणा SSB_BOARD_BU4321E	0x047C
#घोषणा SSB_BOARD_MP4321	0x046C
#घोषणा SSB_BOARD_CB2_4321	0x046D
#घोषणा SSB_BOARD_CB2_4321_AG	0x0066
#घोषणा SSB_BOARD_MC4321	0x046E
/* 4325 boards */
#घोषणा SSB_BOARD_BCM94325DEVBU	0x0490
#घोषणा SSB_BOARD_BCM94325BGABU	0x0491
#घोषणा SSB_BOARD_BCM94325SDGWB	0x0492
#घोषणा SSB_BOARD_BCM94325SDGMDL	0x04AA
#घोषणा SSB_BOARD_BCM94325SDGMDL2	0x04C6
#घोषणा SSB_BOARD_BCM94325SDGMDL3	0x04C9
#घोषणा SSB_BOARD_BCM94325SDABGWBA	0x04E1
/* 4322 boards */
#घोषणा SSB_BOARD_BCM94322MC	0x04A4
#घोषणा SSB_BOARD_BCM94322USB	0x04A8	/* dualband */
#घोषणा SSB_BOARD_BCM94322HM	0x04B0
#घोषणा SSB_BOARD_BCM94322USB2D	0x04Bf	/* single band discrete front end */
/* 4312 boards */
#घोषणा SSB_BOARD_BU4312	0x048A
#घोषणा SSB_BOARD_BCM4312MCGSG	0x04B5
/* chip_package */
#घोषणा SSB_CHIPPACK_BCM4712S	1	/* Small 200pin 4712 */
#घोषणा SSB_CHIPPACK_BCM4712M	2	/* Medium 225pin 4712 */
#घोषणा SSB_CHIPPACK_BCM4712L	0	/* Large 340pin 4712 */

#समावेश <linux/ssb/ssb_driver_chipcommon.h>
#समावेश <linux/ssb/ssb_driver_mips.h>
#समावेश <linux/ssb/ssb_driver_extअगर.h>
#समावेश <linux/ssb/ssb_driver_pci.h>

काष्ठा ssb_bus अणु
	/* The MMIO area. */
	व्योम __iomem *mmio;

	स्थिर काष्ठा ssb_bus_ops *ops;

	/* The core currently mapped पूर्णांकo the MMIO winकरोw.
	 * Not valid on all host-buses. So करोn't use outside of SSB. */
	काष्ठा ssb_device *mapped_device;
	जोड़ अणु
		/* Currently mapped PCMCIA segment. (bustype == SSB_BUSTYPE_PCMCIA only) */
		u8 mapped_pcmcia_seg;
		/* Current SSB base address winकरोw क्रम SDIO. */
		u32 sdio_sbaddr;
	पूर्ण;
	/* Lock क्रम core and segment चयनing.
	 * On PCMCIA-host busses this is used to protect the whole MMIO access. */
	spinlock_t bar_lock;

	/* The host-bus this backplane is running on. */
	क्रमागत ssb_bustype bustype;
	/* Poपूर्णांकers to the host-bus. Check bustype beक्रमe using any of these poपूर्णांकers. */
	जोड़ अणु
		/* Poपूर्णांकer to the PCI bus (only valid अगर bustype == SSB_BUSTYPE_PCI). */
		काष्ठा pci_dev *host_pci;
		/* Poपूर्णांकer to the PCMCIA device (only अगर bustype == SSB_BUSTYPE_PCMCIA). */
		काष्ठा pcmcia_device *host_pcmcia;
		/* Poपूर्णांकer to the SDIO device (only अगर bustype == SSB_BUSTYPE_SDIO). */
		काष्ठा sdio_func *host_sdio;
	पूर्ण;

	/* See क्रमागत ssb_quirks */
	अचिन्हित पूर्णांक quirks;

#अगर_घोषित CONFIG_SSB_SPROM
	/* Mutex to protect the SPROM writing. */
	काष्ठा mutex sprom_mutex;
#पूर्ण_अगर

	/* ID inक्रमmation about the Chip. */
	u16 chip_id;
	u8 chip_rev;
	u16 sprom_offset;
	u16 sprom_size;		/* number of words in sprom */
	u8 chip_package;

	/* List of devices (cores) on the backplane. */
	काष्ठा ssb_device devices[SSB_MAX_NR_CORES];
	u8 nr_devices;

	/* Software ID number क्रम this bus. */
	अचिन्हित पूर्णांक busnumber;

	/* The ChipCommon device (अगर available). */
	काष्ठा ssb_chipcommon chipco;
	/* The PCI-core device (अगर available). */
	काष्ठा ssb_pcicore pcicore;
	/* The MIPS-core device (अगर available). */
	काष्ठा ssb_mipscore mipscore;
	/* The EXTअगर-core device (अगर available). */
	काष्ठा ssb_extअगर extअगर;

	/* The following काष्ठाure elements are not available in early
	 * SSB initialization. Though, they are available क्रम regular
	 * रेजिस्टरed drivers at any stage. So be careful when
	 * using them in the ssb core code. */

	/* ID inक्रमmation about the PCB. */
	काष्ठा ssb_boardinfo boardinfo;
	/* Contents of the SPROM. */
	काष्ठा ssb_sprom sprom;
	/* If the board has a cardbus slot, this is set to true. */
	bool has_cardbus_slot;

#अगर_घोषित CONFIG_SSB_EMBEDDED
	/* Lock क्रम GPIO रेजिस्टर access. */
	spinlock_t gpio_lock;
	काष्ठा platक्रमm_device *watchकरोg;
#पूर्ण_अगर /* EMBEDDED */
#अगर_घोषित CONFIG_SSB_DRIVER_GPIO
	काष्ठा gpio_chip gpio;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
#पूर्ण_अगर /* DRIVER_GPIO */

	/* Internal-only stuff follows. Do not touch. */
	काष्ठा list_head list;
	/* Is the bus alपढ़ोy घातered up? */
	bool घातered_up;
	पूर्णांक घातer_warn_count;
पूर्ण;

क्रमागत ssb_quirks अणु
	/* SDIO connected card requires perक्रमming a पढ़ो after writing a 32-bit value */
	SSB_QUIRK_SDIO_READ_AFTER_WRITE32	= (1 << 0),
पूर्ण;

/* The initialization-invariants. */
काष्ठा ssb_init_invariants अणु
	/* Versioning inक्रमmation about the PCB. */
	काष्ठा ssb_boardinfo boardinfo;
	/* The SPROM inक्रमmation. That's either stored in an
	 * EEPROM or NVRAM on the board. */
	काष्ठा ssb_sprom sprom;
	/* If the board has a cardbus slot, this is set to true. */
	bool has_cardbus_slot;
पूर्ण;
/* Type of function to fetch the invariants. */
प्रकार पूर्णांक (*ssb_invariants_func_t)(काष्ठा ssb_bus *bus,
				     काष्ठा ssb_init_invariants *iv);

/* Register SoC bus. */
बाह्य पूर्णांक ssb_bus_host_soc_रेजिस्टर(काष्ठा ssb_bus *bus,
				     अचिन्हित दीर्घ baseaddr);
#अगर_घोषित CONFIG_SSB_PCIHOST
बाह्य पूर्णांक ssb_bus_pcibus_रेजिस्टर(काष्ठा ssb_bus *bus,
				   काष्ठा pci_dev *host_pci);
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */
#अगर_घोषित CONFIG_SSB_PCMCIAHOST
बाह्य पूर्णांक ssb_bus_pcmciabus_रेजिस्टर(काष्ठा ssb_bus *bus,
				      काष्ठा pcmcia_device *pcmcia_dev,
				      अचिन्हित दीर्घ baseaddr);
#पूर्ण_अगर /* CONFIG_SSB_PCMCIAHOST */
#अगर_घोषित CONFIG_SSB_SDIOHOST
बाह्य पूर्णांक ssb_bus_sdiobus_रेजिस्टर(काष्ठा ssb_bus *bus,
				    काष्ठा sdio_func *sdio_func,
				    अचिन्हित पूर्णांक quirks);
#पूर्ण_अगर /* CONFIG_SSB_SDIOHOST */


बाह्य व्योम ssb_bus_unरेजिस्टर(काष्ठा ssb_bus *bus);

/* Does the device have an SPROM? */
बाह्य bool ssb_is_sprom_available(काष्ठा ssb_bus *bus);

/* Set a fallback SPROM.
 * See kकरोc at the function definition क्रम complete करोcumentation. */
बाह्य पूर्णांक ssb_arch_रेजिस्टर_fallback_sprom(
		पूर्णांक (*sprom_callback)(काष्ठा ssb_bus *bus,
		काष्ठा ssb_sprom *out));

/* Suspend a SSB bus.
 * Call this from the parent bus suspend routine. */
बाह्य पूर्णांक ssb_bus_suspend(काष्ठा ssb_bus *bus);
/* Resume a SSB bus.
 * Call this from the parent bus resume routine. */
बाह्य पूर्णांक ssb_bus_resume(काष्ठा ssb_bus *bus);

बाह्य u32 ssb_घड़ीspeed(काष्ठा ssb_bus *bus);

/* Is the device enabled in hardware? */
पूर्णांक ssb_device_is_enabled(काष्ठा ssb_device *dev);
/* Enable a device and pass device-specअगरic SSB_TMSLOW flags.
 * If no device-specअगरic flags are available, use 0. */
व्योम ssb_device_enable(काष्ठा ssb_device *dev, u32 core_specअगरic_flags);
/* Disable a device in hardware and pass SSB_TMSLOW flags (अगर any). */
व्योम ssb_device_disable(काष्ठा ssb_device *dev, u32 core_specअगरic_flags);


/* Device MMIO रेजिस्टर पढ़ो/ग_लिखो functions. */
अटल अंतरभूत u8 ssb_पढ़ो8(काष्ठा ssb_device *dev, u16 offset)
अणु
	वापस dev->ops->पढ़ो8(dev, offset);
पूर्ण
अटल अंतरभूत u16 ssb_पढ़ो16(काष्ठा ssb_device *dev, u16 offset)
अणु
	वापस dev->ops->पढ़ो16(dev, offset);
पूर्ण
अटल अंतरभूत u32 ssb_पढ़ो32(काष्ठा ssb_device *dev, u16 offset)
अणु
	वापस dev->ops->पढ़ो32(dev, offset);
पूर्ण
अटल अंतरभूत व्योम ssb_ग_लिखो8(काष्ठा ssb_device *dev, u16 offset, u8 value)
अणु
	dev->ops->ग_लिखो8(dev, offset, value);
पूर्ण
अटल अंतरभूत व्योम ssb_ग_लिखो16(काष्ठा ssb_device *dev, u16 offset, u16 value)
अणु
	dev->ops->ग_लिखो16(dev, offset, value);
पूर्ण
अटल अंतरभूत व्योम ssb_ग_लिखो32(काष्ठा ssb_device *dev, u16 offset, u32 value)
अणु
	dev->ops->ग_लिखो32(dev, offset, value);
पूर्ण
#अगर_घोषित CONFIG_SSB_BLOCKIO
अटल अंतरभूत व्योम ssb_block_पढ़ो(काष्ठा ssb_device *dev, व्योम *buffer,
				  माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	dev->ops->block_पढ़ो(dev, buffer, count, offset, reg_width);
पूर्ण

अटल अंतरभूत व्योम ssb_block_ग_लिखो(काष्ठा ssb_device *dev, स्थिर व्योम *buffer,
				   माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	dev->ops->block_ग_लिखो(dev, buffer, count, offset, reg_width);
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_BLOCKIO */


/* The SSB DMA API. Use this API क्रम any DMA operation on the device.
 * This API basically is a wrapper that calls the correct DMA API क्रम
 * the host device type the SSB device is attached to. */

/* Translation (routing) bits that need to be ORed to DMA
 * addresses beक्रमe they are given to a device. */
बाह्य u32 ssb_dma_translation(काष्ठा ssb_device *dev);
#घोषणा SSB_DMA_TRANSLATION_MASK	0xC0000000
#घोषणा SSB_DMA_TRANSLATION_SHIFT	30

अटल अंतरभूत व्योम __cold __ssb_dma_not_implemented(काष्ठा ssb_device *dev)
अणु
#अगर_घोषित CONFIG_SSB_DEBUG
	prपूर्णांकk(KERN_ERR "SSB: BUG! Calling DMA API for "
	       "unsupported bustype %d\n", dev->bus->bustype);
#पूर्ण_अगर /* DEBUG */
पूर्ण

#अगर_घोषित CONFIG_SSB_PCIHOST
/* PCI-host wrapper driver */
बाह्य पूर्णांक ssb_pcihost_रेजिस्टर(काष्ठा pci_driver *driver);
अटल अंतरभूत व्योम ssb_pcihost_unरेजिस्टर(काष्ठा pci_driver *driver)
अणु
	pci_unरेजिस्टर_driver(driver);
पूर्ण

अटल अंतरभूत
व्योम ssb_pcihost_set_घातer_state(काष्ठा ssb_device *sdev, pci_घातer_t state)
अणु
	अगर (sdev->bus->bustype == SSB_BUSTYPE_PCI)
		pci_set_घातer_state(sdev->bus->host_pci, state);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ssb_pcihost_unरेजिस्टर(काष्ठा pci_driver *driver)
अणु
पूर्ण

अटल अंतरभूत
व्योम ssb_pcihost_set_घातer_state(काष्ठा ssb_device *sdev, pci_घातer_t state)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_PCIHOST */


/* If a driver is shutकरोwn or suspended, call this to संकेत
 * that the bus may be completely घातered करोwn. SSB will decide,
 * अगर it's really समय to घातer करोwn the bus, based on अगर there
 * are other devices that want to run. */
बाह्य पूर्णांक ssb_bus_may_घातerकरोwn(काष्ठा ssb_bus *bus);
/* Beक्रमe initializing and enabling a device, call this to घातer-up the bus.
 * If you want to allow use of dynamic-घातer-control, pass the flag.
 * Otherwise अटल always-on घातercontrol will be used. */
बाह्य पूर्णांक ssb_bus_घातerup(काष्ठा ssb_bus *bus, bool dynamic_pctl);

बाह्य व्योम ssb_commit_settings(काष्ठा ssb_bus *bus);

/* Various helper functions */
बाह्य u32 ssb_admatch_base(u32 adm);
बाह्य u32 ssb_admatch_size(u32 adm);

/* PCI device mapping and fixup routines.
 * Called from the architecture pcibios init code.
 * These are only available on SSB_EMBEDDED configurations. */
#अगर_घोषित CONFIG_SSB_EMBEDDED
पूर्णांक ssb_pcibios_plat_dev_init(काष्ठा pci_dev *dev);
पूर्णांक ssb_pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin);
#पूर्ण_अगर /* CONFIG_SSB_EMBEDDED */

#पूर्ण_अगर /* LINUX_SSB_H_ */
