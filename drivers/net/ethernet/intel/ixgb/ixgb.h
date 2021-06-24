<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2008 Intel Corporation. */

#अगर_अघोषित _IXGB_H_
#घोषणा _IXGB_H_

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
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/list.h>
#समावेश <linux/reboot.h>
#समावेश <net/checksum.h>

#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>

#घोषणा BAR_0		0
#घोषणा BAR_1		1

काष्ठा ixgb_adapter;
#समावेश "ixgb_hw.h"
#समावेश "ixgb_ee.h"
#समावेश "ixgb_ids.h"

/* TX/RX descriptor defines */
#घोषणा DEFAULT_TXD      256
#घोषणा MAX_TXD         4096
#घोषणा MIN_TXD           64

/* hardware cannot reliably support more than 512 descriptors owned by
 * hardware descriptor cache otherwise an unreliable ring under heavy
 * receive load may result */
#घोषणा DEFAULT_RXD      512
#घोषणा MAX_RXD          512
#घोषणा MIN_RXD           64

/* Supported Rx Buffer Sizes */
#घोषणा IXGB_RXBUFFER_2048  2048
#घोषणा IXGB_RXBUFFER_4096  4096
#घोषणा IXGB_RXBUFFER_8192  8192
#घोषणा IXGB_RXBUFFER_16384 16384

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IXGB_RX_BUFFER_WRITE	8	/* Must be घातer of 2 */

/* wrapper around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer */
काष्ठा ixgb_buffer अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	अचिन्हित दीर्घ समय_stamp;
	u16 length;
	u16 next_to_watch;
	u16 mapped_as_page;
पूर्ण;

काष्ठा ixgb_desc_ring अणु
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
	काष्ठा ixgb_buffer *buffer_info;
पूर्ण;

#घोषणा IXGB_DESC_UNUSED(R) \
	((((R)->next_to_clean > (R)->next_to_use) ? 0 : (R)->count) + \
	(R)->next_to_clean - (R)->next_to_use - 1)

#घोषणा IXGB_GET_DESC(R, i, type)	(&(((काष्ठा type *)((R).desc))[i]))
#घोषणा IXGB_RX_DESC(R, i)		IXGB_GET_DESC(R, i, ixgb_rx_desc)
#घोषणा IXGB_TX_DESC(R, i)		IXGB_GET_DESC(R, i, ixgb_tx_desc)
#घोषणा IXGB_CONTEXT_DESC(R, i)	IXGB_GET_DESC(R, i, ixgb_context_desc)

/* board specअगरic निजी data काष्ठाure */

काष्ठा ixgb_adapter अणु
	काष्ठा समयr_list watchकरोg_समयr;
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u32 bd_number;
	u32 rx_buffer_len;
	u32 part_num;
	u16 link_speed;
	u16 link_duplex;
	काष्ठा work_काष्ठा tx_समयout_task;

	/* TX */
	काष्ठा ixgb_desc_ring tx_ring ____cacheline_aligned_in_smp;
	अचिन्हित पूर्णांक restart_queue;
	अचिन्हित दीर्घ समयo_start;
	u32 tx_cmd_type;
	u64 hw_csum_tx_good;
	u64 hw_csum_tx_error;
	u32 tx_पूर्णांक_delay;
	u32 tx_समयout_count;
	bool tx_पूर्णांक_delay_enable;
	bool detect_tx_hung;

	/* RX */
	काष्ठा ixgb_desc_ring rx_ring;
	u64 hw_csum_rx_error;
	u64 hw_csum_rx_good;
	u32 rx_पूर्णांक_delay;
	bool rx_csum;

	/* OS defined काष्ठाs */
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;

	/* काष्ठाs defined in ixgb_hw.h */
	काष्ठा ixgb_hw hw;
	u16 msg_enable;
	काष्ठा ixgb_hw_stats stats;
	u32 alloc_rx_buff_failed;
	bool have_msi;
	अचिन्हित दीर्घ flags;
पूर्ण;

क्रमागत ixgb_state_t अणु
	/* TBD
	__IXGB_TESTING,
	__IXGB_RESETTING,
	*/
	__IXGB_DOWN
पूर्ण;

/* Exported from other modules */
व्योम ixgb_check_options(काष्ठा ixgb_adapter *adapter);
व्योम ixgb_set_ethtool_ops(काष्ठा net_device *netdev);
बाह्य अक्षर ixgb_driver_name[];

व्योम ixgb_set_speed_duplex(काष्ठा net_device *netdev);

पूर्णांक ixgb_up(काष्ठा ixgb_adapter *adapter);
व्योम ixgb_करोwn(काष्ठा ixgb_adapter *adapter, bool समाप्त_watchकरोg);
व्योम ixgb_reset(काष्ठा ixgb_adapter *adapter);
पूर्णांक ixgb_setup_rx_resources(काष्ठा ixgb_adapter *adapter);
पूर्णांक ixgb_setup_tx_resources(काष्ठा ixgb_adapter *adapter);
व्योम ixgb_मुक्त_rx_resources(काष्ठा ixgb_adapter *adapter);
व्योम ixgb_मुक्त_tx_resources(काष्ठा ixgb_adapter *adapter);
व्योम ixgb_update_stats(काष्ठा ixgb_adapter *adapter);


#पूर्ण_अगर /* _IXGB_H_ */
