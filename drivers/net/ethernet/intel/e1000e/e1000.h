<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* Linux PRO/1000 Ethernet Driver मुख्य header file */

#अगर_अघोषित _E1000_H_
#घोषणा _E1000_H_

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/mii.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/pm_qos.h>
#समावेश "hw.h"

काष्ठा e1000_info;

#घोषणा e_dbg(क्रमmat, arg...) \
	netdev_dbg(hw->adapter->netdev, क्रमmat, ## arg)
#घोषणा e_err(क्रमmat, arg...) \
	netdev_err(adapter->netdev, क्रमmat, ## arg)
#घोषणा e_info(क्रमmat, arg...) \
	netdev_info(adapter->netdev, क्रमmat, ## arg)
#घोषणा e_warn(क्रमmat, arg...) \
	netdev_warn(adapter->netdev, क्रमmat, ## arg)
#घोषणा e_notice(क्रमmat, arg...) \
	netdev_notice(adapter->netdev, क्रमmat, ## arg)

/* Interrupt modes, as used by the IntMode parameter */
#घोषणा E1000E_INT_MODE_LEGACY		0
#घोषणा E1000E_INT_MODE_MSI		1
#घोषणा E1000E_INT_MODE_MSIX		2

/* Tx/Rx descriptor defines */
#घोषणा E1000_DEFAULT_TXD		256
#घोषणा E1000_MAX_TXD			4096
#घोषणा E1000_MIN_TXD			64

#घोषणा E1000_DEFAULT_RXD		256
#घोषणा E1000_MAX_RXD			4096
#घोषणा E1000_MIN_RXD			64

#घोषणा E1000_MIN_ITR_USECS		10 /* 100000 irq/sec */
#घोषणा E1000_MAX_ITR_USECS		10000 /* 100    irq/sec */

#घोषणा E1000_FC_PAUSE_TIME		0x0680 /* 858 usec */

/* How many Tx Descriptors करो we need to call netअगर_wake_queue ? */
/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा E1000_RX_BUFFER_WRITE		16 /* Must be घातer of 2 */

#घोषणा AUTO_ALL_MODES			0
#घोषणा E1000_EEPROM_APME		0x0400

#घोषणा E1000_MNG_VLAN_NONE		(-1)

#घोषणा DEFAULT_JUMBO			9234

/* Time to रुको beक्रमe putting the device पूर्णांकo D3 अगर there's no link (in ms). */
#घोषणा LINK_TIMEOUT		100

/* Count क्रम polling __E1000_RESET condition every 10-20msec.
 * Experimentation has shown the reset can take approximately 210msec.
 */
#घोषणा E1000_CHECK_RESET_COUNT		25

#घोषणा PCICFG_DESC_RING_STATUS		0xe4
#घोषणा FLUSH_DESC_REQUIRED		0x100

/* in the हाल of WTHRESH, it appears at least the 82571/2 hardware
 * ग_लिखोs back 4 descriptors when WTHRESH=5, and 3 descriptors when
 * WTHRESH=4, so a setting of 5 gives the most efficient bus
 * utilization but to aव्योम possible Tx stalls, set it to 1
 */
#घोषणा E1000_TXDCTL_DMA_BURST_ENABLE                          \
	(E1000_TXDCTL_GRAN | /* set descriptor granularity */  \
	 E1000_TXDCTL_COUNT_DESC |                             \
	 (1u << 16) | /* wthresh must be +1 more than desired */\
	 (1u << 8)  | /* hthresh */                             \
	 0x1f)        /* pthresh */

#घोषणा E1000_RXDCTL_DMA_BURST_ENABLE                          \
	(0x01000000 | /* set descriptor granularity */         \
	 (4u << 16) | /* set ग_लिखोback threshold    */         \
	 (4u << 8)  | /* set prefetch threshold     */         \
	 0x20)        /* set hthresh                */

#घोषणा E1000_TIDV_FPD BIT(31)
#घोषणा E1000_RDTR_FPD BIT(31)

क्रमागत e1000_boards अणु
	board_82571,
	board_82572,
	board_82573,
	board_82574,
	board_82583,
	board_80003es2lan,
	board_ich8lan,
	board_ich9lan,
	board_ich10lan,
	board_pchlan,
	board_pch2lan,
	board_pch_lpt,
	board_pch_spt,
	board_pch_cnp
पूर्ण;

काष्ठा e1000_ps_page अणु
	काष्ठा page *page;
	u64 dma; /* must be u64 - written to hw */
पूर्ण;

/* wrappers around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा e1000_buffer अणु
	dma_addr_t dma;
	काष्ठा sk_buff *skb;
	जोड़ अणु
		/* Tx */
		काष्ठा अणु
			अचिन्हित दीर्घ समय_stamp;
			u16 length;
			u16 next_to_watch;
			अचिन्हित पूर्णांक segs;
			अचिन्हित पूर्णांक bytecount;
			u16 mapped_as_page;
		पूर्ण;
		/* Rx */
		काष्ठा अणु
			/* arrays of page inक्रमmation क्रम packet split */
			काष्ठा e1000_ps_page *ps_pages;
			काष्ठा page *page;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा e1000_ring अणु
	काष्ठा e1000_adapter *adapter;	/* back poपूर्णांकer to adapter */
	व्योम *desc;			/* poपूर्णांकer to ring memory  */
	dma_addr_t dma;			/* phys address of ring    */
	अचिन्हित पूर्णांक size;		/* length of ring in bytes */
	अचिन्हित पूर्णांक count;		/* number of desc. in ring */

	u16 next_to_use;
	u16 next_to_clean;

	व्योम __iomem *head;
	व्योम __iomem *tail;

	/* array of buffer inक्रमmation काष्ठाs */
	काष्ठा e1000_buffer *buffer_info;

	अक्षर name[IFNAMSIZ + 5];
	u32 ims_val;
	u32 itr_val;
	व्योम __iomem *itr_रेजिस्टर;
	पूर्णांक set_itr;

	काष्ठा sk_buff *rx_skb_top;
पूर्ण;

/* PHY रेजिस्टर snapshot values */
काष्ठा e1000_phy_regs अणु
	u16 bmcr;		/* basic mode control रेजिस्टर    */
	u16 bmsr;		/* basic mode status रेजिस्टर     */
	u16 advertise;		/* स्वतः-negotiation advertisement */
	u16 lpa;		/* link partner ability रेजिस्टर  */
	u16 expansion;		/* स्वतः-negotiation expansion reg */
	u16 ctrl1000;		/* 1000BASE-T control रेजिस्टर    */
	u16 stat1000;		/* 1000BASE-T status रेजिस्टर     */
	u16 estatus;		/* extended status रेजिस्टर       */
पूर्ण;

/* board specअगरic निजी data काष्ठाure */
काष्ठा e1000_adapter अणु
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list phy_info_समयr;
	काष्ठा समयr_list blink_समयr;

	काष्ठा work_काष्ठा reset_task;
	काष्ठा work_काष्ठा watchकरोg_task;

	स्थिर काष्ठा e1000_info *ei;

	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u32 bd_number;
	u32 rx_buffer_len;
	u16 mng_vlan_id;
	u16 link_speed;
	u16 link_duplex;
	u16 eeprom_vers;

	/* track device up/करोwn/testing state */
	अचिन्हित दीर्घ state;

	/* Interrupt Throttle Rate */
	u32 itr;
	u32 itr_setting;
	u16 tx_itr;
	u16 rx_itr;

	/* Tx - one ring per active queue */
	काष्ठा e1000_ring *tx_ring ____cacheline_aligned_in_smp;
	u32 tx_fअगरo_limit;

	काष्ठा napi_काष्ठा napi;

	अचिन्हित पूर्णांक uncorr_errors;	/* uncorrectable ECC errors */
	अचिन्हित पूर्णांक corr_errors;	/* correctable ECC errors */
	अचिन्हित पूर्णांक restart_queue;
	u32 txd_cmd;

	bool detect_tx_hung;
	bool tx_hang_recheck;
	u8 tx_समयout_factor;

	u32 tx_पूर्णांक_delay;
	u32 tx_असल_पूर्णांक_delay;

	अचिन्हित पूर्णांक total_tx_bytes;
	अचिन्हित पूर्णांक total_tx_packets;
	अचिन्हित पूर्णांक total_rx_bytes;
	अचिन्हित पूर्णांक total_rx_packets;

	/* Tx stats */
	u64 tpt_old;
	u64 colc_old;
	u32 gotc;
	u64 gotc_old;
	u32 tx_समयout_count;
	u32 tx_fअगरo_head;
	u32 tx_head_addr;
	u32 tx_fअगरo_size;
	u32 tx_dma_failed;
	u32 tx_hwtstamp_समयouts;
	u32 tx_hwtstamp_skipped;

	/* Rx */
	bool (*clean_rx)(काष्ठा e1000_ring *ring, पूर्णांक *work_करोne,
			 पूर्णांक work_to_करो) ____cacheline_aligned_in_smp;
	व्योम (*alloc_rx_buf)(काष्ठा e1000_ring *ring, पूर्णांक cleaned_count,
			     gfp_t gfp);
	काष्ठा e1000_ring *rx_ring;

	u32 rx_पूर्णांक_delay;
	u32 rx_असल_पूर्णांक_delay;

	/* Rx stats */
	u64 hw_csum_err;
	u64 hw_csum_good;
	u64 rx_hdr_split;
	u32 gorc;
	u64 gorc_old;
	u32 alloc_rx_buff_failed;
	u32 rx_dma_failed;
	u32 rx_hwtstamp_cleared;

	अचिन्हित पूर्णांक rx_ps_pages;
	u16 rx_ps_bsize0;
	u32 max_frame_size;
	u32 min_frame_size;

	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;

	/* काष्ठाs defined in e1000_hw.h */
	काष्ठा e1000_hw hw;

	spinlock_t stats64_lock;	/* protects statistics counters */
	काष्ठा e1000_hw_stats stats;
	काष्ठा e1000_phy_info phy_info;
	काष्ठा e1000_phy_stats phy_stats;

	/* Snapshot of PHY रेजिस्टरs */
	काष्ठा e1000_phy_regs phy_regs;

	काष्ठा e1000_ring test_tx_ring;
	काष्ठा e1000_ring test_rx_ring;
	u32 test_icr;

	u32 msg_enable;
	अचिन्हित पूर्णांक num_vectors;
	काष्ठा msix_entry *msix_entries;
	पूर्णांक पूर्णांक_mode;
	u32 eiac_mask;

	u32 eeprom_wol;
	u32 wol;
	u32 pba;
	u32 max_hw_frame_size;

	bool fc_स्वतःneg;

	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक flags2;
	काष्ठा work_काष्ठा करोwnshअगरt_task;
	काष्ठा work_काष्ठा update_phy_task;
	काष्ठा work_काष्ठा prपूर्णांक_hang_task;

	पूर्णांक phy_hang_count;

	u16 tx_ring_count;
	u16 rx_ring_count;

	काष्ठा hwtstamp_config hwtstamp_config;
	काष्ठा delayed_work systim_overflow_work;
	काष्ठा sk_buff *tx_hwtstamp_skb;
	अचिन्हित दीर्घ tx_hwtstamp_start;
	काष्ठा work_काष्ठा tx_hwtstamp_work;
	spinlock_t systim_lock;	/* protects SYSTIML/H regsters */
	काष्ठा cyclecounter cc;
	काष्ठा समयcounter tc;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_info;
	काष्ठा pm_qos_request pm_qos_req;
	s32 ptp_delta;

	u16 eee_advert;
पूर्ण;

काष्ठा e1000_info अणु
	क्रमागत e1000_mac_type	mac;
	अचिन्हित पूर्णांक		flags;
	अचिन्हित पूर्णांक		flags2;
	u32			pba;
	u32			max_hw_frame_size;
	s32			(*get_variants)(काष्ठा e1000_adapter *);
	स्थिर काष्ठा e1000_mac_operations *mac_ops;
	स्थिर काष्ठा e1000_phy_operations *phy_ops;
	स्थिर काष्ठा e1000_nvm_operations *nvm_ops;
पूर्ण;

s32 e1000e_get_base_timinca(काष्ठा e1000_adapter *adapter, u32 *timinca);

/* The प्रणाली समय is मुख्यtained by a 64-bit counter comprised of the 32-bit
 * SYSTIMH and SYSTIML रेजिस्टरs.  How the counter increments (and thereक्रमe
 * its resolution) is based on the contents of the TIMINCA रेजिस्टर - it
 * increments every incperiod (bits 31:24) घड़ी ticks by incvalue (bits 23:0).
 * For the best accuracy, the incperiod should be as small as possible.  The
 * incvalue is scaled by a factor as large as possible (जबतक still fitting
 * in bits 23:0) so that relatively small घड़ी corrections can be made.
 *
 * As a result, a shअगरt of INCVALUE_SHIFT_n is used to fit a value of
 * INCVALUE_n पूर्णांकo the TIMINCA रेजिस्टर allowing 32+8+(24-INCVALUE_SHIFT_n)
 * bits to count nanoseconds leaving the rest क्रम fractional nonseconds.
 */
#घोषणा INCVALUE_96MHZ		125
#घोषणा INCVALUE_SHIFT_96MHZ	17
#घोषणा INCPERIOD_SHIFT_96MHZ	2
#घोषणा INCPERIOD_96MHZ		(12 >> INCPERIOD_SHIFT_96MHZ)

#घोषणा INCVALUE_25MHZ		40
#घोषणा INCVALUE_SHIFT_25MHZ	18
#घोषणा INCPERIOD_25MHZ		1

#घोषणा INCVALUE_24MHZ		125
#घोषणा INCVALUE_SHIFT_24MHZ	14
#घोषणा INCPERIOD_24MHZ		3

#घोषणा INCVALUE_38400KHZ	26
#घोषणा INCVALUE_SHIFT_38400KHZ	19
#घोषणा INCPERIOD_38400KHZ	1

/* Another drawback of scaling the incvalue by a large factor is the
 * 64-bit SYSTIM रेजिस्टर overflows more quickly.  This is dealt with
 * by simply पढ़ोing the घड़ी beक्रमe it overflows.
 *
 * Clock	ns bits	Overflows after
 * ~~~~~~	~~~~~~~	~~~~~~~~~~~~~~~
 * 96MHz	47-bit	2^(47-INCPERIOD_SHIFT_96MHz) / 10^9 / 3600 = 9.77 hrs
 * 25MHz	46-bit	2^46 / 10^9 / 3600 = 19.55 hours
 */
#घोषणा E1000_SYSTIM_OVERFLOW_PERIOD	(HZ * 60 * 60 * 4)
#घोषणा E1000_MAX_82574_SYSTIM_REREADS	50
#घोषणा E1000_82574_SYSTIM_EPSILON	(1ULL << 35ULL)

/* hardware capability, feature, and workaround flags */
#घोषणा FLAG_HAS_AMT                      BIT(0)
#घोषणा FLAG_HAS_FLASH                    BIT(1)
#घोषणा FLAG_HAS_HW_VLAN_FILTER           BIT(2)
#घोषणा FLAG_HAS_WOL                      BIT(3)
/* reserved BIT(4) */
#घोषणा FLAG_HAS_CTRLEXT_ON_LOAD          BIT(5)
#घोषणा FLAG_HAS_SWSM_ON_LOAD             BIT(6)
#घोषणा FLAG_HAS_JUMBO_FRAMES             BIT(7)
#घोषणा FLAG_READ_ONLY_NVM                BIT(8)
#घोषणा FLAG_IS_ICH                       BIT(9)
#घोषणा FLAG_HAS_MSIX                     BIT(10)
#घोषणा FLAG_HAS_SMART_POWER_DOWN         BIT(11)
#घोषणा FLAG_IS_QUAD_PORT_A               BIT(12)
#घोषणा FLAG_IS_QUAD_PORT                 BIT(13)
#घोषणा FLAG_HAS_HW_TIMESTAMP             BIT(14)
#घोषणा FLAG_APME_IN_WUC                  BIT(15)
#घोषणा FLAG_APME_IN_CTRL3                BIT(16)
#घोषणा FLAG_APME_CHECK_PORT_B            BIT(17)
#घोषणा FLAG_DISABLE_FC_PAUSE_TIME        BIT(18)
#घोषणा FLAG_NO_WAKE_UCAST                BIT(19)
#घोषणा FLAG_MNG_PT_ENABLED               BIT(20)
#घोषणा FLAG_RESET_OVERWRITES_LAA         BIT(21)
#घोषणा FLAG_TARC_SPEED_MODE_BIT          BIT(22)
#घोषणा FLAG_TARC_SET_BIT_ZERO            BIT(23)
#घोषणा FLAG_RX_NEEDS_RESTART             BIT(24)
#घोषणा FLAG_LSC_GIG_SPEED_DROP           BIT(25)
#घोषणा FLAG_SMART_POWER_DOWN             BIT(26)
#घोषणा FLAG_MSI_ENABLED                  BIT(27)
/* reserved BIT(28) */
#घोषणा FLAG_TSO_FORCE                    BIT(29)
#घोषणा FLAG_RESTART_NOW                  BIT(30)
#घोषणा FLAG_MSI_TEST_FAILED              BIT(31)

#घोषणा FLAG2_CRC_STRIPPING               BIT(0)
#घोषणा FLAG2_HAS_PHY_WAKEUP              BIT(1)
#घोषणा FLAG2_IS_DISCARDING               BIT(2)
#घोषणा FLAG2_DISABLE_ASPM_L1             BIT(3)
#घोषणा FLAG2_HAS_PHY_STATS               BIT(4)
#घोषणा FLAG2_HAS_EEE                     BIT(5)
#घोषणा FLAG2_DMA_BURST                   BIT(6)
#घोषणा FLAG2_DISABLE_ASPM_L0S            BIT(7)
#घोषणा FLAG2_DISABLE_AIM                 BIT(8)
#घोषणा FLAG2_CHECK_PHY_HANG              BIT(9)
#घोषणा FLAG2_NO_DISABLE_RX               BIT(10)
#घोषणा FLAG2_PCIM2PCI_ARBITER_WA         BIT(11)
#घोषणा FLAG2_DFLT_CRC_STRIPPING          BIT(12)
#घोषणा FLAG2_CHECK_RX_HWTSTAMP           BIT(13)
#घोषणा FLAG2_CHECK_SYSTIM_OVERFLOW       BIT(14)
#घोषणा FLAG2_ENABLE_S0IX_FLOWS           BIT(15)

#घोषणा E1000_RX_DESC_PS(R, i)	    \
	(&(((जोड़ e1000_rx_desc_packet_split *)((R).desc))[i]))
#घोषणा E1000_RX_DESC_EXT(R, i)	    \
	(&(((जोड़ e1000_rx_desc_extended *)((R).desc))[i]))
#घोषणा E1000_GET_DESC(R, i, type)	(&(((काष्ठा type *)((R).desc))[i]))
#घोषणा E1000_TX_DESC(R, i)		E1000_GET_DESC(R, i, e1000_tx_desc)
#घोषणा E1000_CONTEXT_DESC(R, i)	E1000_GET_DESC(R, i, e1000_context_desc)

क्रमागत e1000_state_t अणु
	__E1000_TESTING,
	__E1000_RESETTING,
	__E1000_ACCESS_SHARED_RESOURCE,
	__E1000_DOWN
पूर्ण;

क्रमागत latency_range अणु
	lowest_latency = 0,
	low_latency = 1,
	bulk_latency = 2,
	latency_invalid = 255
पूर्ण;

बाह्य अक्षर e1000e_driver_name[];

व्योम e1000e_check_options(काष्ठा e1000_adapter *adapter);
व्योम e1000e_set_ethtool_ops(काष्ठा net_device *netdev);

पूर्णांक e1000e_खोलो(काष्ठा net_device *netdev);
पूर्णांक e1000e_बंद(काष्ठा net_device *netdev);
व्योम e1000e_up(काष्ठा e1000_adapter *adapter);
व्योम e1000e_करोwn(काष्ठा e1000_adapter *adapter, bool reset);
व्योम e1000e_reinit_locked(काष्ठा e1000_adapter *adapter);
व्योम e1000e_reset(काष्ठा e1000_adapter *adapter);
व्योम e1000e_घातer_up_phy(काष्ठा e1000_adapter *adapter);
पूर्णांक e1000e_setup_rx_resources(काष्ठा e1000_ring *ring);
पूर्णांक e1000e_setup_tx_resources(काष्ठा e1000_ring *ring);
व्योम e1000e_मुक्त_rx_resources(काष्ठा e1000_ring *ring);
व्योम e1000e_मुक्त_tx_resources(काष्ठा e1000_ring *ring);
व्योम e1000e_get_stats64(काष्ठा net_device *netdev,
			काष्ठा rtnl_link_stats64 *stats);
व्योम e1000e_set_पूर्णांकerrupt_capability(काष्ठा e1000_adapter *adapter);
व्योम e1000e_reset_पूर्णांकerrupt_capability(काष्ठा e1000_adapter *adapter);
व्योम e1000e_get_hw_control(काष्ठा e1000_adapter *adapter);
व्योम e1000e_release_hw_control(काष्ठा e1000_adapter *adapter);
व्योम e1000e_ग_लिखो_itr(काष्ठा e1000_adapter *adapter, u32 itr);

बाह्य अचिन्हित पूर्णांक copyअवरोध;

बाह्य स्थिर काष्ठा e1000_info e1000_82571_info;
बाह्य स्थिर काष्ठा e1000_info e1000_82572_info;
बाह्य स्थिर काष्ठा e1000_info e1000_82573_info;
बाह्य स्थिर काष्ठा e1000_info e1000_82574_info;
बाह्य स्थिर काष्ठा e1000_info e1000_82583_info;
बाह्य स्थिर काष्ठा e1000_info e1000_ich8_info;
बाह्य स्थिर काष्ठा e1000_info e1000_ich9_info;
बाह्य स्थिर काष्ठा e1000_info e1000_ich10_info;
बाह्य स्थिर काष्ठा e1000_info e1000_pch_info;
बाह्य स्थिर काष्ठा e1000_info e1000_pch2_info;
बाह्य स्थिर काष्ठा e1000_info e1000_pch_lpt_info;
बाह्य स्थिर काष्ठा e1000_info e1000_pch_spt_info;
बाह्य स्थिर काष्ठा e1000_info e1000_pch_cnp_info;
बाह्य स्थिर काष्ठा e1000_info e1000_es2_info;

व्योम e1000e_ptp_init(काष्ठा e1000_adapter *adapter);
व्योम e1000e_ptp_हटाओ(काष्ठा e1000_adapter *adapter);

u64 e1000e_पढ़ो_systim(काष्ठा e1000_adapter *adapter,
		       काष्ठा ptp_प्रणाली_बारtamp *sts);

अटल अंतरभूत s32 e1000_phy_hw_reset(काष्ठा e1000_hw *hw)
अणु
	वापस hw->phy.ops.reset(hw);
पूर्ण

अटल अंतरभूत s32 e1e_rphy(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस hw->phy.ops.पढ़ो_reg(hw, offset, data);
पूर्ण

अटल अंतरभूत s32 e1e_rphy_locked(काष्ठा e1000_hw *hw, u32 offset, u16 *data)
अणु
	वापस hw->phy.ops.पढ़ो_reg_locked(hw, offset, data);
पूर्ण

अटल अंतरभूत s32 e1e_wphy(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस hw->phy.ops.ग_लिखो_reg(hw, offset, data);
पूर्ण

अटल अंतरभूत s32 e1e_wphy_locked(काष्ठा e1000_hw *hw, u32 offset, u16 data)
अणु
	वापस hw->phy.ops.ग_लिखो_reg_locked(hw, offset, data);
पूर्ण

व्योम e1000e_reload_nvm_generic(काष्ठा e1000_hw *hw);

अटल अंतरभूत s32 e1000e_पढ़ो_mac_addr(काष्ठा e1000_hw *hw)
अणु
	अगर (hw->mac.ops.पढ़ो_mac_addr)
		वापस hw->mac.ops.पढ़ो_mac_addr(hw);

	वापस e1000_पढ़ो_mac_addr_generic(hw);
पूर्ण

अटल अंतरभूत s32 e1000_validate_nvm_checksum(काष्ठा e1000_hw *hw)
अणु
	वापस hw->nvm.ops.validate(hw);
पूर्ण

अटल अंतरभूत s32 e1000e_update_nvm_checksum(काष्ठा e1000_hw *hw)
अणु
	वापस hw->nvm.ops.update(hw);
पूर्ण

अटल अंतरभूत s32 e1000_पढ़ो_nvm(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				 u16 *data)
अणु
	वापस hw->nvm.ops.पढ़ो(hw, offset, words, data);
पूर्ण

अटल अंतरभूत s32 e1000_ग_लिखो_nvm(काष्ठा e1000_hw *hw, u16 offset, u16 words,
				  u16 *data)
अणु
	वापस hw->nvm.ops.ग_लिखो(hw, offset, words, data);
पूर्ण

अटल अंतरभूत s32 e1000_get_phy_info(काष्ठा e1000_hw *hw)
अणु
	वापस hw->phy.ops.get_info(hw);
पूर्ण

अटल अंतरभूत u32 __er32(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(hw->hw_addr + reg);
पूर्ण

#घोषणा er32(reg)	__er32(hw, E1000_##reg)

व्योम __ew32(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ reg, u32 val);

#घोषणा ew32(reg, val)	__ew32(hw, E1000_##reg, (val))

#घोषणा e1e_flush()	er32(STATUS)

#घोषणा E1000_WRITE_REG_ARRAY(a, reg, offset, value) \
	(__ew32((a), (reg + ((offset) << 2)), (value)))

#घोषणा E1000_READ_REG_ARRAY(a, reg, offset) \
	(पढ़ोl((a)->hw_addr + reg + ((offset) << 2)))

#पूर्ण_अगर /* _E1000_H_ */
