<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: common.h                                                            *
 * $Revision: 1.21 $                                                         *
 * $Date: 2005/06/22 00:43:25 $                                              *
 * Description:                                                              *
 *  part of the Chelsio 10Gb Ethernet Driver.                                *
 *                                                                           *
 * This program is मुक्त software; you can redistribute it and/or modअगरy      *
 * it under the terms of the GNU General Public License, version 2, as       *
 * published by the Free Software Foundation.                                *
 *                                                                           *
 * You should have received a copy of the GNU General Public License aदीर्घ   *
 * with this program; अगर not, see <http://www.gnu.org/licenses/>.            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED    *
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF      *
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.                     *
 *                                                                           *
 * http://www.chelsio.com                                                    *
 *                                                                           *
 * Copyright (c) 2003 - 2005 Chelsio Communications, Inc.                    *
 * All rights reserved.                                                      *
 *                                                                           *
 * Maपूर्णांकainers: मुख्यtainers@chelsio.com                                      *
 *                                                                           *
 * Authors: Dimitrios Michailidis   <dm@chelsio.com>                         *
 *          Tina Yang               <tainay@chelsio.com>                     *
 *          Felix Marti             <felix@chelsio.com>                      *
 *          Scott Barकरोne           <sbarकरोne@chelsio.com>                   *
 *          Kurt Ottaway            <kottaway@chelsio.com>                   *
 *          Frank DiMambro          <frank@chelsio.com>                      *
 *                                                                           *
 * History:                                                                  *
 *                                                                           *
 ****************************************************************************/

#घोषणा pr_fmt(fmt) "cxgb: " fmt

#अगर_अघोषित _CXGB_COMMON_H_
#घोषणा _CXGB_COMMON_H_

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/pci_ids.h>

#घोषणा DRV_DESCRIPTION "Chelsio 10Gb Ethernet Driver"
#घोषणा DRV_NAME "cxgb"

#घोषणा CH_DEVICE(devid, ssid, idx) \
	अणु PCI_VENDOR_ID_CHELSIO, devid, PCI_ANY_ID, ssid, 0, 0, idx पूर्ण

#घोषणा SUPPORTED_PAUSE       (1 << 13)
#घोषणा SUPPORTED_LOOPBACK    (1 << 15)

#घोषणा ADVERTISED_PAUSE      (1 << 13)
#घोषणा ADVERTISED_ASYM_PAUSE (1 << 14)

प्रकार काष्ठा adapter adapter_t;

काष्ठा t1_rx_mode अणु
       काष्ठा net_device *dev;
पूर्ण;

#घोषणा t1_rx_mode_promisc(rm)	(rm->dev->flags & IFF_PROMISC)
#घोषणा t1_rx_mode_allmulti(rm)	(rm->dev->flags & IFF_ALLMULTI)
#घोषणा t1_rx_mode_mc_cnt(rm)	(netdev_mc_count(rm->dev))
#घोषणा t1_get_netdev(rm)	(rm->dev)

#घोषणा	MAX_NPORTS 4
#घोषणा PORT_MASK ((1 << MAX_NPORTS) - 1)
#घोषणा NMTUS      8
#घोषणा TCB_SIZE   128

#घोषणा SPEED_INVALID 0xffff
#घोषणा DUPLEX_INVALID 0xff

/* Max frame size PM3393 can handle. Includes Ethernet header and CRC. */
#घोषणा PM3393_MAX_FRAME_SIZE 9600

#घोषणा VSC7326_MAX_MTU 9600

क्रमागत अणु
	CHBT_BOARD_N110,
	CHBT_BOARD_N210,
	CHBT_BOARD_7500,
	CHBT_BOARD_8000,
	CHBT_BOARD_CHT101,
	CHBT_BOARD_CHT110,
	CHBT_BOARD_CHT210,
	CHBT_BOARD_CHT204,
	CHBT_BOARD_CHT204V,
	CHBT_BOARD_CHT204E,
	CHBT_BOARD_CHN204,
	CHBT_BOARD_COUGAR,
	CHBT_BOARD_6800,
	CHBT_BOARD_SIMUL,
पूर्ण;

क्रमागत अणु
	CHBT_TERM_FPGA,
	CHBT_TERM_T1,
	CHBT_TERM_T2,
	CHBT_TERM_T3
पूर्ण;

क्रमागत अणु
	CHBT_MAC_CHELSIO_A,
	CHBT_MAC_IXF1010,
	CHBT_MAC_PM3393,
	CHBT_MAC_VSC7321,
	CHBT_MAC_DUMMY
पूर्ण;

क्रमागत अणु
	CHBT_PHY_88E1041,
	CHBT_PHY_88E1111,
	CHBT_PHY_88X2010,
	CHBT_PHY_XPAK,
	CHBT_PHY_MY3126,
	CHBT_PHY_8244,
	CHBT_PHY_DUMMY
पूर्ण;

क्रमागत अणु
	PAUSE_RX      = 1 << 0,
	PAUSE_TX      = 1 << 1,
	PAUSE_AUTONEG = 1 << 2
पूर्ण;

/* Revisions of T1 chip */
क्रमागत अणु
	TERM_T1A   = 0,
	TERM_T1B   = 1,
	TERM_T2    = 3
पूर्ण;

काष्ठा sge_params अणु
	अचिन्हित पूर्णांक cmdQ_size[2];
	अचिन्हित पूर्णांक मुक्तlQ_size[2];
	अचिन्हित पूर्णांक large_buf_capacity;
	अचिन्हित पूर्णांक rx_coalesce_usecs;
	अचिन्हित पूर्णांक last_rx_coalesce_raw;
	अचिन्हित पूर्णांक शेष_rx_coalesce_usecs;
	अचिन्हित पूर्णांक sample_पूर्णांकerval_usecs;
	अचिन्हित पूर्णांक coalesce_enable;
	अचिन्हित पूर्णांक polling;
पूर्ण;

काष्ठा chelsio_pci_params अणु
	अचिन्हित लघु speed;
	अचिन्हित अक्षर  width;
	अचिन्हित अक्षर  is_pcix;
पूर्ण;

काष्ठा tp_params अणु
	अचिन्हित पूर्णांक pm_size;
	अचिन्हित पूर्णांक cm_size;
	अचिन्हित पूर्णांक pm_rx_base;
	अचिन्हित पूर्णांक pm_tx_base;
	अचिन्हित पूर्णांक pm_rx_pg_size;
	अचिन्हित पूर्णांक pm_tx_pg_size;
	अचिन्हित पूर्णांक pm_rx_num_pgs;
	अचिन्हित पूर्णांक pm_tx_num_pgs;
	अचिन्हित पूर्णांक rx_coalescing_size;
	अचिन्हित पूर्णांक use_5tuple_mode;
पूर्ण;

काष्ठा mc5_params अणु
	अचिन्हित पूर्णांक mode;       /* selects MC5 width */
	अचिन्हित पूर्णांक nservers;   /* size of server region */
	अचिन्हित पूर्णांक nroutes;    /* size of routing region */
पूर्ण;

/* Default MC5 region sizes */
#घोषणा DEFAULT_SERVER_REGION_LEN 256
#घोषणा DEFAULT_RT_REGION_LEN 1024

काष्ठा adapter_params अणु
	काष्ठा sge_params sge;
	काष्ठा mc5_params mc5;
	काष्ठा tp_params  tp;
	काष्ठा chelsio_pci_params pci;

	स्थिर काष्ठा board_info *brd_info;

	अचिन्हित लघु mtus[NMTUS];
	अचिन्हित पूर्णांक   nports;          /* # of ethernet ports */
	अचिन्हित पूर्णांक   stats_update_period;
	अचिन्हित लघु chip_revision;
	अचिन्हित अक्षर  chip_version;
	अचिन्हित अक्षर  is_asic;
	अचिन्हित अक्षर  has_msi;
पूर्ण;

काष्ठा link_config अणु
	अचिन्हित पूर्णांक   supported;        /* link capabilities */
	अचिन्हित पूर्णांक   advertising;      /* advertised capabilities */
	अचिन्हित लघु requested_speed;  /* speed user has requested */
	अचिन्हित लघु speed;            /* actual link speed */
	अचिन्हित अक्षर  requested_duplex; /* duplex user has requested */
	अचिन्हित अक्षर  duplex;           /* actual link duplex */
	अचिन्हित अक्षर  requested_fc;     /* flow control user has requested */
	अचिन्हित अक्षर  fc;               /* actual link flow control */
	अचिन्हित अक्षर  स्वतःneg;          /* स्वतःnegotiating? */
पूर्ण;

काष्ठा cmac;
काष्ठा cphy;

काष्ठा port_info अणु
	काष्ठा net_device *dev;
	काष्ठा cmac *mac;
	काष्ठा cphy *phy;
	काष्ठा link_config link_config;
पूर्ण;

काष्ठा sge;
काष्ठा peespi;

काष्ठा adapter अणु
	u8 __iomem *regs;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ रेजिस्टरed_device_map;
	अचिन्हित दीर्घ खोलो_device_map;
	अचिन्हित दीर्घ flags;

	स्थिर अक्षर *name;
	पूर्णांक msg_enable;
	u32 mmio_len;

	काष्ठा adapter_params params;

	/* Terminator modules. */
	काष्ठा sge    *sge;
	काष्ठा peespi *espi;
	काष्ठा petp   *tp;

	काष्ठा napi_काष्ठा napi;
	काष्ठा port_info port[MAX_NPORTS];
	काष्ठा delayed_work stats_update_task;
	काष्ठा समयr_list stats_update_समयr;

	spinlock_t tpi_lock;
	spinlock_t work_lock;
	spinlock_t mac_lock;

	/* guards async operations */
	spinlock_t async_lock ____cacheline_aligned;
	u32 pending_thपढ़ो_पूर्णांकr;
	u32 slow_पूर्णांकr_mask;
	पूर्णांक t1घातersave;
पूर्ण;

क्रमागत अणु                                           /* adapter flags */
	FULL_INIT_DONE        = 1 << 0,
पूर्ण;

काष्ठा mdio_ops;
काष्ठा gmac;
काष्ठा gphy;

काष्ठा board_info अणु
	अचिन्हित अक्षर           board;
	अचिन्हित अक्षर           port_number;
	अचिन्हित दीर्घ           caps;
	अचिन्हित अक्षर           chip_term;
	अचिन्हित अक्षर           chip_mac;
	अचिन्हित अक्षर           chip_phy;
	अचिन्हित पूर्णांक            घड़ी_core;
	अचिन्हित पूर्णांक            घड़ी_mc3;
	अचिन्हित पूर्णांक            घड़ी_mc4;
	अचिन्हित पूर्णांक            espi_nports;
	अचिन्हित पूर्णांक            घड़ी_elmer0;
	अचिन्हित अक्षर           mdio_mdien;
	अचिन्हित अक्षर           mdio_mdiinv;
	अचिन्हित अक्षर           mdio_mdc;
	अचिन्हित अक्षर           mdio_phybaseaddr;
	स्थिर काष्ठा gmac      *gmac;
	स्थिर काष्ठा gphy      *gphy;
	स्थिर काष्ठा mdio_ops  *mdio_ops;
	स्थिर अक्षर             *desc;
पूर्ण;

अटल अंतरभूत पूर्णांक t1_is_asic(स्थिर adapter_t *adapter)
अणु
	वापस adapter->params.is_asic;
पूर्ण

बाह्य स्थिर काष्ठा pci_device_id t1_pci_tbl[];

अटल अंतरभूत पूर्णांक adapter_matches_type(स्थिर adapter_t *adapter,
				       पूर्णांक version, पूर्णांक revision)
अणु
	वापस adapter->params.chip_version == version &&
	       adapter->params.chip_revision == revision;
पूर्ण

#घोषणा t1_is_T1B(adap) adapter_matches_type(adap, CHBT_TERM_T1, TERM_T1B)
#घोषणा is_T2(adap)     adapter_matches_type(adap, CHBT_TERM_T2, TERM_T2)

/* Returns true अगर an adapter supports VLAN acceleration and TSO */
अटल अंतरभूत पूर्णांक vlan_tso_capable(स्थिर adapter_t *adapter)
अणु
	वापस !t1_is_T1B(adapter);
पूर्ण

#घोषणा क्रम_each_port(adapter, iter) \
	क्रम (iter = 0; iter < (adapter)->params.nports; ++iter)

#घोषणा board_info(adapter) ((adapter)->params.brd_info)
#घोषणा is_10G(adapter) (board_info(adapter)->caps & SUPPORTED_10000baseT_Full)

अटल अंतरभूत अचिन्हित पूर्णांक core_ticks_per_usec(स्थिर adapter_t *adap)
अणु
	वापस board_info(adap)->घड़ी_core / 1000000;
पूर्ण

पूर्णांक __t1_tpi_पढ़ो(adapter_t *adapter, u32 addr, u32 *valp);
पूर्णांक __t1_tpi_ग_लिखो(adapter_t *adapter, u32 addr, u32 value);
पूर्णांक t1_tpi_ग_लिखो(adapter_t *adapter, u32 addr, u32 value);
पूर्णांक t1_tpi_पढ़ो(adapter_t *adapter, u32 addr, u32 *value);

व्योम t1_पूर्णांकerrupts_enable(adapter_t *adapter);
व्योम t1_पूर्णांकerrupts_disable(adapter_t *adapter);
व्योम t1_पूर्णांकerrupts_clear(adapter_t *adapter);
पूर्णांक t1_elmer0_ext_पूर्णांकr_handler(adapter_t *adapter);
irqवापस_t t1_slow_पूर्णांकr_handler(adapter_t *adapter);

पूर्णांक t1_link_start(काष्ठा cphy *phy, काष्ठा cmac *mac, काष्ठा link_config *lc);
स्थिर काष्ठा board_info *t1_get_board_info(अचिन्हित पूर्णांक board_id);
स्थिर काष्ठा board_info *t1_get_board_info_from_ids(अचिन्हित पूर्णांक devid,
						    अचिन्हित लघु ssid);
पूर्णांक t1_seeprom_पढ़ो(adapter_t *adapter, u32 addr, __le32 *data);
पूर्णांक t1_get_board_rev(adapter_t *adapter, स्थिर काष्ठा board_info *bi,
		     काष्ठा adapter_params *p);
पूर्णांक t1_init_hw_modules(adapter_t *adapter);
पूर्णांक t1_init_sw_modules(adapter_t *adapter, स्थिर काष्ठा board_info *bi);
व्योम t1_मुक्त_sw_modules(adapter_t *adapter);
व्योम t1_link_changed(adapter_t *adapter, पूर्णांक port_id);
व्योम t1_link_negotiated(adapter_t *adapter, पूर्णांक port_id, पूर्णांक link_stat,
			    पूर्णांक speed, पूर्णांक duplex, पूर्णांक छोड़ो);
#पूर्ण_अगर /* _CXGB_COMMON_H_ */
