<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2006 Intel Corporation. */

/* Linux PRO/1000 Ethernet Driver मुख्य header file */

#अगर_अघोषित _E1000_H_
#घोषणा _E1000_H_

#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/capability.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/list.h>
#समावेश <linux/reboot.h>
#समावेश <net/checksum.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>

#घोषणा BAR_0		0
#घोषणा BAR_1		1

#घोषणा INTEL_E1000_ETHERNET_DEVICE(device_id) अणु\
	PCI_DEVICE(PCI_VENDOR_ID_INTEL, device_id)पूर्ण

काष्ठा e1000_adapter;

#समावेश "e1000_hw.h"

#घोषणा E1000_MAX_INTR			10

/*
 * Count क्रम polling __E1000_RESET condition every 10-20msec.
 */
#घोषणा E1000_CHECK_RESET_COUNT	50

/* TX/RX descriptor defines */
#घोषणा E1000_DEFAULT_TXD		256
#घोषणा E1000_MAX_TXD			256
#घोषणा E1000_MIN_TXD			48
#घोषणा E1000_MAX_82544_TXD		4096

#घोषणा E1000_DEFAULT_RXD		256
#घोषणा E1000_MAX_RXD			256
#घोषणा E1000_MIN_RXD			48
#घोषणा E1000_MAX_82544_RXD		4096

#घोषणा E1000_MIN_ITR_USECS		10 /* 100000 irq/sec */
#घोषणा E1000_MAX_ITR_USECS		10000 /* 100    irq/sec */

/* this is the size past which hardware will drop packets when setting LPE=0 */
#घोषणा MAXIMUM_ETHERNET_VLAN_SIZE	1522

/* Supported Rx Buffer Sizes */
#घोषणा E1000_RXBUFFER_128		128    /* Used क्रम packet split */
#घोषणा E1000_RXBUFFER_256		256    /* Used क्रम packet split */
#घोषणा E1000_RXBUFFER_512		512
#घोषणा E1000_RXBUFFER_1024		1024
#घोषणा E1000_RXBUFFER_2048		2048
#घोषणा E1000_RXBUFFER_4096		4096
#घोषणा E1000_RXBUFFER_8192		8192
#घोषणा E1000_RXBUFFER_16384		16384

/* SmartSpeed delimiters */
#घोषणा E1000_SMARTSPEED_DOWNSHIFT	3
#घोषणा E1000_SMARTSPEED_MAX		15

/* Packet Buffer allocations */
#घोषणा E1000_PBA_BYTES_SHIFT		0xA
#घोषणा E1000_TX_HEAD_ADDR_SHIFT	7
#घोषणा E1000_PBA_TX_MASK		0xFFFF0000

/* Flow Control Watermarks */
#घोषणा E1000_FC_HIGH_DIFF	0x1638 /* High: 5688 bytes below Rx FIFO size */
#घोषणा E1000_FC_LOW_DIFF	0x1640 /* Low:  5696 bytes below Rx FIFO size */

#घोषणा E1000_FC_PAUSE_TIME	0xFFFF /* छोड़ो क्रम the max or until send xon */

/* How many Tx Descriptors करो we need to call netअगर_wake_queue ? */
#घोषणा E1000_TX_QUEUE_WAKE	16
/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा E1000_RX_BUFFER_WRITE	16 /* Must be घातer of 2 */

#घोषणा AUTO_ALL_MODES		0
#घोषणा E1000_EEPROM_82544_APM	0x0004
#घोषणा E1000_EEPROM_APME	0x0400

#अगर_अघोषित E1000_MASTER_SLAVE
/* Switch to override PHY master/slave setting */
#घोषणा E1000_MASTER_SLAVE	e1000_ms_hw_शेष
#पूर्ण_अगर

#घोषणा E1000_MNG_VLAN_NONE	(-1)

/* wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा e1000_tx_buffer अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	अचिन्हित दीर्घ समय_stamp;
	u16 length;
	u16 next_to_watch;
	bool mapped_as_page;
	अचिन्हित लघु segs;
	अचिन्हित पूर्णांक bytecount;
पूर्ण;

काष्ठा e1000_rx_buffer अणु
	जोड़ अणु
		काष्ठा page *page; /* jumbo: alloc_page */
		u8 *data; /* अन्यथा, netdev_alloc_frag */
	पूर्ण rxbuf;
	dma_addr_t dma;
पूर्ण;

काष्ठा e1000_tx_ring अणु
	/* poपूर्णांकer to the descriptor ring memory */
	व्योम *desc;
	/* physical address of the descriptor ring */
	dma_addr_t dma;
	/* length of descriptor ring in bytes */
	अचिन्हित पूर्णांक size;
	/* number of descriptors in the ring */
	अचिन्हित पूर्णांक count;
	/* next descriptor to associate a buffer with */
	अचिन्हित पूर्णांक next_to_use;
	/* next descriptor to check क्रम DD status bit */
	अचिन्हित पूर्णांक next_to_clean;
	/* array of buffer inक्रमmation काष्ठाs */
	काष्ठा e1000_tx_buffer *buffer_info;

	u16 tdh;
	u16 tdt;
	bool last_tx_tso;
पूर्ण;

काष्ठा e1000_rx_ring अणु
	/* poपूर्णांकer to the descriptor ring memory */
	व्योम *desc;
	/* physical address of the descriptor ring */
	dma_addr_t dma;
	/* length of descriptor ring in bytes */
	अचिन्हित पूर्णांक size;
	/* number of descriptors in the ring */
	अचिन्हित पूर्णांक count;
	/* next descriptor to associate a buffer with */
	अचिन्हित पूर्णांक next_to_use;
	/* next descriptor to check क्रम DD status bit */
	अचिन्हित पूर्णांक next_to_clean;
	/* array of buffer inक्रमmation काष्ठाs */
	काष्ठा e1000_rx_buffer *buffer_info;
	काष्ठा sk_buff *rx_skb_top;

	/* cpu क्रम rx queue */
	पूर्णांक cpu;

	u16 rdh;
	u16 rdt;
पूर्ण;

#घोषणा E1000_DESC_UNUSED(R)						\
(अणु									\
	अचिन्हित पूर्णांक clean = smp_load_acquire(&(R)->next_to_clean);	\
	अचिन्हित पूर्णांक use = READ_ONCE((R)->next_to_use);			\
	(clean > use ? 0 : (R)->count) + clean - use - 1;		\
पूर्ण)

#घोषणा E1000_RX_DESC_EXT(R, i)						\
	(&(((जोड़ e1000_rx_desc_extended *)((R).desc))[i]))
#घोषणा E1000_GET_DESC(R, i, type)	(&(((काष्ठा type *)((R).desc))[i]))
#घोषणा E1000_RX_DESC(R, i)		E1000_GET_DESC(R, i, e1000_rx_desc)
#घोषणा E1000_TX_DESC(R, i)		E1000_GET_DESC(R, i, e1000_tx_desc)
#घोषणा E1000_CONTEXT_DESC(R, i)	E1000_GET_DESC(R, i, e1000_context_desc)

/* board specअगरic निजी data काष्ठाure */

काष्ठा e1000_adapter अणु
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u16 mng_vlan_id;
	u32 bd_number;
	u32 rx_buffer_len;
	u32 wol;
	u32 smartspeed;
	u32 en_mng_pt;
	u16 link_speed;
	u16 link_duplex;
	spinlock_t stats_lock;
	अचिन्हित पूर्णांक total_tx_bytes;
	अचिन्हित पूर्णांक total_tx_packets;
	अचिन्हित पूर्णांक total_rx_bytes;
	अचिन्हित पूर्णांक total_rx_packets;
	/* Interrupt Throttle Rate */
	u32 itr;
	u32 itr_setting;
	u16 tx_itr;
	u16 rx_itr;

	u8 fc_स्वतःneg;

	/* TX */
	काष्ठा e1000_tx_ring *tx_ring;      /* One per active queue */
	अचिन्हित पूर्णांक restart_queue;
	u32 txd_cmd;
	u32 tx_पूर्णांक_delay;
	u32 tx_असल_पूर्णांक_delay;
	u32 gotcl;
	u64 gotcl_old;
	u64 tpt_old;
	u64 colc_old;
	u32 tx_समयout_count;
	u32 tx_fअगरo_head;
	u32 tx_head_addr;
	u32 tx_fअगरo_size;
	u8  tx_समयout_factor;
	atomic_t tx_fअगरo_stall;
	bool pcix_82544;
	bool detect_tx_hung;
	bool dump_buffers;

	/* RX */
	bool (*clean_rx)(काष्ठा e1000_adapter *adapter,
			 काष्ठा e1000_rx_ring *rx_ring,
			 पूर्णांक *work_करोne, पूर्णांक work_to_करो);
	व्योम (*alloc_rx_buf)(काष्ठा e1000_adapter *adapter,
			     काष्ठा e1000_rx_ring *rx_ring,
			     पूर्णांक cleaned_count);
	काष्ठा e1000_rx_ring *rx_ring;      /* One per active queue */
	काष्ठा napi_काष्ठा napi;

	पूर्णांक num_tx_queues;
	पूर्णांक num_rx_queues;

	u64 hw_csum_err;
	u64 hw_csum_good;
	u32 alloc_rx_buff_failed;
	u32 rx_पूर्णांक_delay;
	u32 rx_असल_पूर्णांक_delay;
	bool rx_csum;
	u32 gorcl;
	u64 gorcl_old;

	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;

	/* काष्ठाs defined in e1000_hw.h */
	काष्ठा e1000_hw hw;
	काष्ठा e1000_hw_stats stats;
	काष्ठा e1000_phy_info phy_info;
	काष्ठा e1000_phy_stats phy_stats;

	u32 test_icr;
	काष्ठा e1000_tx_ring test_tx_ring;
	काष्ठा e1000_rx_ring test_rx_ring;

	पूर्णांक msg_enable;

	/* to not mess up cache alignment, always add to the bottom */
	bool tso_क्रमce;
	bool smart_घातer_करोwn;	/* phy smart घातer करोwn */
	bool quad_port_a;
	अचिन्हित दीर्घ flags;
	u32 eeprom_wol;

	/* क्रम ioport मुक्त */
	पूर्णांक bars;
	पूर्णांक need_ioport;

	bool discarding;

	काष्ठा work_काष्ठा reset_task;
	काष्ठा delayed_work watchकरोg_task;
	काष्ठा delayed_work fअगरo_stall_task;
	काष्ठा delayed_work phy_info_task;
पूर्ण;

क्रमागत e1000_state_t अणु
	__E1000_TESTING,
	__E1000_RESETTING,
	__E1000_DOWN,
	__E1000_DISABLED
पूर्ण;

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

काष्ठा net_device *e1000_get_hw_dev(काष्ठा e1000_hw *hw);
#घोषणा e_dbg(क्रमmat, arg...) \
	netdev_dbg(e1000_get_hw_dev(hw), क्रमmat, ## arg)
#घोषणा e_err(msglvl, क्रमmat, arg...) \
	netअगर_err(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#घोषणा e_info(msglvl, क्रमmat, arg...) \
	netअगर_info(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#घोषणा e_warn(msglvl, क्रमmat, arg...) \
	netअगर_warn(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#घोषणा e_notice(msglvl, क्रमmat, arg...) \
	netअगर_notice(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#घोषणा e_dev_info(क्रमmat, arg...) \
	dev_info(&adapter->pdev->dev, क्रमmat, ## arg)
#घोषणा e_dev_warn(क्रमmat, arg...) \
	dev_warn(&adapter->pdev->dev, क्रमmat, ## arg)
#घोषणा e_dev_err(क्रमmat, arg...) \
	dev_err(&adapter->pdev->dev, क्रमmat, ## arg)

बाह्य अक्षर e1000_driver_name[];

पूर्णांक e1000_खोलो(काष्ठा net_device *netdev);
पूर्णांक e1000_बंद(काष्ठा net_device *netdev);
पूर्णांक e1000_up(काष्ठा e1000_adapter *adapter);
व्योम e1000_करोwn(काष्ठा e1000_adapter *adapter);
व्योम e1000_reinit_locked(काष्ठा e1000_adapter *adapter);
व्योम e1000_reset(काष्ठा e1000_adapter *adapter);
पूर्णांक e1000_set_spd_dplx(काष्ठा e1000_adapter *adapter, u32 spd, u8 dplx);
पूर्णांक e1000_setup_all_rx_resources(काष्ठा e1000_adapter *adapter);
पूर्णांक e1000_setup_all_tx_resources(काष्ठा e1000_adapter *adapter);
व्योम e1000_मुक्त_all_rx_resources(काष्ठा e1000_adapter *adapter);
व्योम e1000_मुक्त_all_tx_resources(काष्ठा e1000_adapter *adapter);
व्योम e1000_update_stats(काष्ठा e1000_adapter *adapter);
bool e1000_has_link(काष्ठा e1000_adapter *adapter);
व्योम e1000_घातer_up_phy(काष्ठा e1000_adapter *);
व्योम e1000_set_ethtool_ops(काष्ठा net_device *netdev);
व्योम e1000_check_options(काष्ठा e1000_adapter *adapter);
अक्षर *e1000_get_hw_dev_name(काष्ठा e1000_hw *hw);

#पूर्ण_अगर /* _E1000_H_ */
