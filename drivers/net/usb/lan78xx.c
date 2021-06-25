<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Microchip Technology
 */
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/linkmode.h>
#समावेश <linux/list.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/vxlan.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/microchipphy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश "lan78xx.h"

#घोषणा DRIVER_AUTHOR	"WOOJUNG HUH <woojung.huh@microchip.com>"
#घोषणा DRIVER_DESC	"LAN78XX USB 3.0 Gigabit Ethernet Devices"
#घोषणा DRIVER_NAME	"lan78xx"

#घोषणा TX_TIMEOUT_JIFFIES		(5 * HZ)
#घोषणा THROTTLE_JIFFIES		(HZ / 8)
#घोषणा UNLINK_TIMEOUT_MS		3

#घोषणा RX_MAX_QUEUE_MEMORY		(60 * 1518)

#घोषणा SS_USB_PKT_SIZE			(1024)
#घोषणा HS_USB_PKT_SIZE			(512)
#घोषणा FS_USB_PKT_SIZE			(64)

#घोषणा MAX_RX_FIFO_SIZE		(12 * 1024)
#घोषणा MAX_TX_FIFO_SIZE		(12 * 1024)
#घोषणा DEFAULT_BURST_CAP_SIZE		(MAX_TX_FIFO_SIZE)
#घोषणा DEFAULT_BULK_IN_DELAY		(0x0800)
#घोषणा MAX_SINGLE_PACKET_SIZE		(9000)
#घोषणा DEFAULT_TX_CSUM_ENABLE		(true)
#घोषणा DEFAULT_RX_CSUM_ENABLE		(true)
#घोषणा DEFAULT_TSO_CSUM_ENABLE		(true)
#घोषणा DEFAULT_VLAN_FILTER_ENABLE	(true)
#घोषणा DEFAULT_VLAN_RX_OFFLOAD		(true)
#घोषणा TX_OVERHEAD			(8)
#घोषणा RXW_PADDING			2

#घोषणा LAN78XX_USB_VENDOR_ID		(0x0424)
#घोषणा LAN7800_USB_PRODUCT_ID		(0x7800)
#घोषणा LAN7850_USB_PRODUCT_ID		(0x7850)
#घोषणा LAN7801_USB_PRODUCT_ID		(0x7801)
#घोषणा LAN78XX_EEPROM_MAGIC		(0x78A5)
#घोषणा LAN78XX_OTP_MAGIC		(0x78F3)

#घोषणा	MII_READ			1
#घोषणा	MII_WRITE			0

#घोषणा EEPROM_INDICATOR		(0xA5)
#घोषणा EEPROM_MAC_OFFSET		(0x01)
#घोषणा MAX_EEPROM_SIZE			512
#घोषणा OTP_INDICATOR_1			(0xF3)
#घोषणा OTP_INDICATOR_2			(0xF7)

#घोषणा WAKE_ALL			(WAKE_PHY | WAKE_UCAST | \
					 WAKE_MCAST | WAKE_BCAST | \
					 WAKE_ARP | WAKE_MAGIC)

/* USB related defines */
#घोषणा BULK_IN_PIPE			1
#घोषणा BULK_OUT_PIPE			2

/* शेष स्वतःsuspend delay (mSec)*/
#घोषणा DEFAULT_AUTOSUSPEND_DELAY	(10 * 1000)

/* statistic update पूर्णांकerval (mSec) */
#घोषणा STAT_UPDATE_TIMER		(1 * 1000)

/* defines पूर्णांकerrupts from पूर्णांकerrupt EP */
#घोषणा MAX_INT_EP			(32)
#घोषणा INT_EP_INTEP			(31)
#घोषणा INT_EP_OTP_WR_DONE		(28)
#घोषणा INT_EP_EEE_TX_LPI_START		(26)
#घोषणा INT_EP_EEE_TX_LPI_STOP		(25)
#घोषणा INT_EP_EEE_RX_LPI		(24)
#घोषणा INT_EP_MAC_RESET_TIMEOUT	(23)
#घोषणा INT_EP_RDFO			(22)
#घोषणा INT_EP_TXE			(21)
#घोषणा INT_EP_USB_STATUS		(20)
#घोषणा INT_EP_TX_DIS			(19)
#घोषणा INT_EP_RX_DIS			(18)
#घोषणा INT_EP_PHY			(17)
#घोषणा INT_EP_DP			(16)
#घोषणा INT_EP_MAC_ERR			(15)
#घोषणा INT_EP_TDFU			(14)
#घोषणा INT_EP_TDFO			(13)
#घोषणा INT_EP_UTX			(12)
#घोषणा INT_EP_GPIO_11			(11)
#घोषणा INT_EP_GPIO_10			(10)
#घोषणा INT_EP_GPIO_9			(9)
#घोषणा INT_EP_GPIO_8			(8)
#घोषणा INT_EP_GPIO_7			(7)
#घोषणा INT_EP_GPIO_6			(6)
#घोषणा INT_EP_GPIO_5			(5)
#घोषणा INT_EP_GPIO_4			(4)
#घोषणा INT_EP_GPIO_3			(3)
#घोषणा INT_EP_GPIO_2			(2)
#घोषणा INT_EP_GPIO_1			(1)
#घोषणा INT_EP_GPIO_0			(0)

अटल स्थिर अक्षर lan78xx_gstrings[][ETH_GSTRING_LEN] = अणु
	"RX FCS Errors",
	"RX Alignment Errors",
	"Rx Fragment Errors",
	"RX Jabber Errors",
	"RX Undersize Frame Errors",
	"RX Oversize Frame Errors",
	"RX Dropped Frames",
	"RX Unicast Byte Count",
	"RX Broadcast Byte Count",
	"RX Multicast Byte Count",
	"RX Unicast Frames",
	"RX Broadcast Frames",
	"RX Multicast Frames",
	"RX Pause Frames",
	"RX 64 Byte Frames",
	"RX 65 - 127 Byte Frames",
	"RX 128 - 255 Byte Frames",
	"RX 256 - 511 Bytes Frames",
	"RX 512 - 1023 Byte Frames",
	"RX 1024 - 1518 Byte Frames",
	"RX Greater 1518 Byte Frames",
	"EEE RX LPI Transitions",
	"EEE RX LPI Time",
	"TX FCS Errors",
	"TX Excess Deferral Errors",
	"TX Carrier Errors",
	"TX Bad Byte Count",
	"TX Single Collisions",
	"TX Multiple Collisions",
	"TX Excessive Collision",
	"TX Late Collisions",
	"TX Unicast Byte Count",
	"TX Broadcast Byte Count",
	"TX Multicast Byte Count",
	"TX Unicast Frames",
	"TX Broadcast Frames",
	"TX Multicast Frames",
	"TX Pause Frames",
	"TX 64 Byte Frames",
	"TX 65 - 127 Byte Frames",
	"TX 128 - 255 Byte Frames",
	"TX 256 - 511 Bytes Frames",
	"TX 512 - 1023 Byte Frames",
	"TX 1024 - 1518 Byte Frames",
	"TX Greater 1518 Byte Frames",
	"EEE TX LPI Transitions",
	"EEE TX LPI Time",
पूर्ण;

काष्ठा lan78xx_statstage अणु
	u32 rx_fcs_errors;
	u32 rx_alignment_errors;
	u32 rx_fragment_errors;
	u32 rx_jabber_errors;
	u32 rx_undersize_frame_errors;
	u32 rx_oversize_frame_errors;
	u32 rx_dropped_frames;
	u32 rx_unicast_byte_count;
	u32 rx_broadcast_byte_count;
	u32 rx_multicast_byte_count;
	u32 rx_unicast_frames;
	u32 rx_broadcast_frames;
	u32 rx_multicast_frames;
	u32 rx_छोड़ो_frames;
	u32 rx_64_byte_frames;
	u32 rx_65_127_byte_frames;
	u32 rx_128_255_byte_frames;
	u32 rx_256_511_bytes_frames;
	u32 rx_512_1023_byte_frames;
	u32 rx_1024_1518_byte_frames;
	u32 rx_greater_1518_byte_frames;
	u32 eee_rx_lpi_transitions;
	u32 eee_rx_lpi_समय;
	u32 tx_fcs_errors;
	u32 tx_excess_deferral_errors;
	u32 tx_carrier_errors;
	u32 tx_bad_byte_count;
	u32 tx_single_collisions;
	u32 tx_multiple_collisions;
	u32 tx_excessive_collision;
	u32 tx_late_collisions;
	u32 tx_unicast_byte_count;
	u32 tx_broadcast_byte_count;
	u32 tx_multicast_byte_count;
	u32 tx_unicast_frames;
	u32 tx_broadcast_frames;
	u32 tx_multicast_frames;
	u32 tx_छोड़ो_frames;
	u32 tx_64_byte_frames;
	u32 tx_65_127_byte_frames;
	u32 tx_128_255_byte_frames;
	u32 tx_256_511_bytes_frames;
	u32 tx_512_1023_byte_frames;
	u32 tx_1024_1518_byte_frames;
	u32 tx_greater_1518_byte_frames;
	u32 eee_tx_lpi_transitions;
	u32 eee_tx_lpi_समय;
पूर्ण;

काष्ठा lan78xx_statstage64 अणु
	u64 rx_fcs_errors;
	u64 rx_alignment_errors;
	u64 rx_fragment_errors;
	u64 rx_jabber_errors;
	u64 rx_undersize_frame_errors;
	u64 rx_oversize_frame_errors;
	u64 rx_dropped_frames;
	u64 rx_unicast_byte_count;
	u64 rx_broadcast_byte_count;
	u64 rx_multicast_byte_count;
	u64 rx_unicast_frames;
	u64 rx_broadcast_frames;
	u64 rx_multicast_frames;
	u64 rx_छोड़ो_frames;
	u64 rx_64_byte_frames;
	u64 rx_65_127_byte_frames;
	u64 rx_128_255_byte_frames;
	u64 rx_256_511_bytes_frames;
	u64 rx_512_1023_byte_frames;
	u64 rx_1024_1518_byte_frames;
	u64 rx_greater_1518_byte_frames;
	u64 eee_rx_lpi_transitions;
	u64 eee_rx_lpi_समय;
	u64 tx_fcs_errors;
	u64 tx_excess_deferral_errors;
	u64 tx_carrier_errors;
	u64 tx_bad_byte_count;
	u64 tx_single_collisions;
	u64 tx_multiple_collisions;
	u64 tx_excessive_collision;
	u64 tx_late_collisions;
	u64 tx_unicast_byte_count;
	u64 tx_broadcast_byte_count;
	u64 tx_multicast_byte_count;
	u64 tx_unicast_frames;
	u64 tx_broadcast_frames;
	u64 tx_multicast_frames;
	u64 tx_छोड़ो_frames;
	u64 tx_64_byte_frames;
	u64 tx_65_127_byte_frames;
	u64 tx_128_255_byte_frames;
	u64 tx_256_511_bytes_frames;
	u64 tx_512_1023_byte_frames;
	u64 tx_1024_1518_byte_frames;
	u64 tx_greater_1518_byte_frames;
	u64 eee_tx_lpi_transitions;
	u64 eee_tx_lpi_समय;
पूर्ण;

अटल u32 lan78xx_regs[] = अणु
	ID_REV,
	INT_STS,
	HW_CFG,
	PMT_CTL,
	E2P_CMD,
	E2P_DATA,
	USB_STATUS,
	VLAN_TYPE,
	MAC_CR,
	MAC_RX,
	MAC_TX,
	FLOW,
	ERR_STS,
	MII_ACC,
	MII_DATA,
	EEE_TX_LPI_REQ_DLY,
	EEE_TW_TX_SYS,
	EEE_TX_LPI_REM_DLY,
	WUCSR
पूर्ण;

#घोषणा PHY_REG_SIZE (32 * माप(u32))

काष्ठा lan78xx_net;

काष्ठा lan78xx_priv अणु
	काष्ठा lan78xx_net *dev;
	u32 rfe_ctl;
	u32 mchash_table[DP_SEL_VHF_HASH_LEN]; /* multicat hash table */
	u32 pfilter_table[NUM_OF_MAF][2]; /* perfect filter table */
	u32 vlan_table[DP_SEL_VHF_VLAN_LEN];
	काष्ठा mutex dataport_mutex; /* क्रम dataport access */
	spinlock_t rfe_ctl_lock; /* क्रम rfe रेजिस्टर access */
	काष्ठा work_काष्ठा set_multicast;
	काष्ठा work_काष्ठा set_vlan;
	u32 wol;
पूर्ण;

क्रमागत skb_state अणु
	illegal = 0,
	tx_start,
	tx_करोne,
	rx_start,
	rx_करोne,
	rx_cleanup,
	unlink_start
पूर्ण;

काष्ठा skb_data अणु		/* skb->cb is one of these */
	काष्ठा urb *urb;
	काष्ठा lan78xx_net *dev;
	क्रमागत skb_state state;
	माप_प्रकार length;
	पूर्णांक num_of_packet;
पूर्ण;

काष्ठा usb_context अणु
	काष्ठा usb_ctrlrequest req;
	काष्ठा lan78xx_net *dev;
पूर्ण;

#घोषणा EVENT_TX_HALT			0
#घोषणा EVENT_RX_HALT			1
#घोषणा EVENT_RX_MEMORY			2
#घोषणा EVENT_STS_SPLIT			3
#घोषणा EVENT_LINK_RESET		4
#घोषणा EVENT_RX_PAUSED			5
#घोषणा EVENT_DEV_WAKING		6
#घोषणा EVENT_DEV_ASLEEP		7
#घोषणा EVENT_DEV_OPEN			8
#घोषणा EVENT_STAT_UPDATE		9

काष्ठा statstage अणु
	काष्ठा mutex			access_lock;	/* क्रम stats access */
	काष्ठा lan78xx_statstage	saved;
	काष्ठा lan78xx_statstage	rollover_count;
	काष्ठा lan78xx_statstage	rollover_max;
	काष्ठा lan78xx_statstage64	curr_stat;
पूर्ण;

काष्ठा irq_करोमुख्य_data अणु
	काष्ठा irq_करोमुख्य	*irqकरोमुख्य;
	अचिन्हित पूर्णांक		phyirq;
	काष्ठा irq_chip		*irqchip;
	irq_flow_handler_t	irq_handler;
	u32			irqenable;
	काष्ठा mutex		irq_lock;		/* क्रम irq bus access */
पूर्ण;

काष्ठा lan78xx_net अणु
	काष्ठा net_device	*net;
	काष्ठा usb_device	*udev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;
	व्योम			*driver_priv;

	पूर्णांक			rx_qlen;
	पूर्णांक			tx_qlen;
	काष्ठा sk_buff_head	rxq;
	काष्ठा sk_buff_head	txq;
	काष्ठा sk_buff_head	करोne;
	काष्ठा sk_buff_head	rxq_छोड़ो;
	काष्ठा sk_buff_head	txq_pend;

	काष्ठा tasklet_काष्ठा	bh;
	काष्ठा delayed_work	wq;

	पूर्णांक			msg_enable;

	काष्ठा urb		*urb_पूर्णांकr;
	काष्ठा usb_anchor	deferred;

	काष्ठा mutex		phy_mutex; /* क्रम phy access */
	अचिन्हित		pipe_in, pipe_out, pipe_पूर्णांकr;

	u32			hard_mtu;	/* count any extra framing */
	माप_प्रकार			rx_urb_size;	/* size क्रम rx urbs */

	अचिन्हित दीर्घ		flags;

	रुको_queue_head_t	*रुको;
	अचिन्हित अक्षर		suspend_count;

	अचिन्हित		maxpacket;
	काष्ठा समयr_list	delay;
	काष्ठा समयr_list	stat_monitor;

	अचिन्हित दीर्घ		data[5];

	पूर्णांक			link_on;
	u8			mdix_ctrl;

	u32			chipid;
	u32			chiprev;
	काष्ठा mii_bus		*mdiobus;
	phy_पूर्णांकerface_t		पूर्णांकerface;

	पूर्णांक			fc_स्वतःneg;
	u8			fc_request_control;

	पूर्णांक			delta;
	काष्ठा statstage	stats;

	काष्ठा irq_करोमुख्य_data	करोमुख्य_data;
पूर्ण;

/* define बाह्यal phy id */
#घोषणा	PHY_LAN8835			(0x0007C130)
#घोषणा	PHY_KSZ9031RNX			(0x00221620)

/* use ethtool to change the level क्रम any given device */
अटल पूर्णांक msg_level = -1;
module_param(msg_level, पूर्णांक, 0);
MODULE_PARM_DESC(msg_level, "Override default message level");

अटल पूर्णांक lan78xx_पढ़ो_reg(काष्ठा lan78xx_net *dev, u32 index, u32 *data)
अणु
	u32 *buf = kदो_स्मृति(माप(u32), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
			      USB_VENDOR_REQUEST_READ_REGISTER,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, index, buf, 4, USB_CTRL_GET_TIMEOUT);
	अगर (likely(ret >= 0)) अणु
		le32_to_cpus(buf);
		*data = *buf;
	पूर्ण अन्यथा अणु
		netdev_warn(dev->net,
			    "Failed to read register index 0x%08x. ret = %d",
			    index, ret);
	पूर्ण

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_ग_लिखो_reg(काष्ठा lan78xx_net *dev, u32 index, u32 data)
अणु
	u32 *buf = kदो_स्मृति(माप(u32), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!buf)
		वापस -ENOMEM;

	*buf = data;
	cpu_to_le32s(buf);

	ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			      USB_VENDOR_REQUEST_WRITE_REGISTER,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, index, buf, 4, USB_CTRL_SET_TIMEOUT);
	अगर (unlikely(ret < 0)) अणु
		netdev_warn(dev->net,
			    "Failed to write register index 0x%08x. ret = %d",
			    index, ret);
	पूर्ण

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_पढ़ो_stats(काष्ठा lan78xx_net *dev,
			      काष्ठा lan78xx_statstage *data)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	काष्ठा lan78xx_statstage *stats;
	u32 *src;
	u32 *dst;

	stats = kदो_स्मृति(माप(*stats), GFP_KERNEL);
	अगर (!stats)
		वापस -ENOMEM;

	ret = usb_control_msg(dev->udev,
			      usb_rcvctrlpipe(dev->udev, 0),
			      USB_VENDOR_REQUEST_GET_STATS,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0,
			      0,
			      (व्योम *)stats,
			      माप(*stats),
			      USB_CTRL_SET_TIMEOUT);
	अगर (likely(ret >= 0)) अणु
		src = (u32 *)stats;
		dst = (u32 *)data;
		क्रम (i = 0; i < माप(*stats)/माप(u32); i++) अणु
			le32_to_cpus(&src[i]);
			dst[i] = src[i];
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_warn(dev->net,
			    "Failed to read stat ret = %d", ret);
	पूर्ण

	kमुक्त(stats);

	वापस ret;
पूर्ण

#घोषणा check_counter_rollover(काष्ठा1, dev_stats, member) अणु	\
	अगर (काष्ठा1->member < dev_stats.saved.member)		\
		dev_stats.rollover_count.member++;		\
	पूर्ण

अटल व्योम lan78xx_check_stat_rollover(काष्ठा lan78xx_net *dev,
					काष्ठा lan78xx_statstage *stats)
अणु
	check_counter_rollover(stats, dev->stats, rx_fcs_errors);
	check_counter_rollover(stats, dev->stats, rx_alignment_errors);
	check_counter_rollover(stats, dev->stats, rx_fragment_errors);
	check_counter_rollover(stats, dev->stats, rx_jabber_errors);
	check_counter_rollover(stats, dev->stats, rx_undersize_frame_errors);
	check_counter_rollover(stats, dev->stats, rx_oversize_frame_errors);
	check_counter_rollover(stats, dev->stats, rx_dropped_frames);
	check_counter_rollover(stats, dev->stats, rx_unicast_byte_count);
	check_counter_rollover(stats, dev->stats, rx_broadcast_byte_count);
	check_counter_rollover(stats, dev->stats, rx_multicast_byte_count);
	check_counter_rollover(stats, dev->stats, rx_unicast_frames);
	check_counter_rollover(stats, dev->stats, rx_broadcast_frames);
	check_counter_rollover(stats, dev->stats, rx_multicast_frames);
	check_counter_rollover(stats, dev->stats, rx_छोड़ो_frames);
	check_counter_rollover(stats, dev->stats, rx_64_byte_frames);
	check_counter_rollover(stats, dev->stats, rx_65_127_byte_frames);
	check_counter_rollover(stats, dev->stats, rx_128_255_byte_frames);
	check_counter_rollover(stats, dev->stats, rx_256_511_bytes_frames);
	check_counter_rollover(stats, dev->stats, rx_512_1023_byte_frames);
	check_counter_rollover(stats, dev->stats, rx_1024_1518_byte_frames);
	check_counter_rollover(stats, dev->stats, rx_greater_1518_byte_frames);
	check_counter_rollover(stats, dev->stats, eee_rx_lpi_transitions);
	check_counter_rollover(stats, dev->stats, eee_rx_lpi_समय);
	check_counter_rollover(stats, dev->stats, tx_fcs_errors);
	check_counter_rollover(stats, dev->stats, tx_excess_deferral_errors);
	check_counter_rollover(stats, dev->stats, tx_carrier_errors);
	check_counter_rollover(stats, dev->stats, tx_bad_byte_count);
	check_counter_rollover(stats, dev->stats, tx_single_collisions);
	check_counter_rollover(stats, dev->stats, tx_multiple_collisions);
	check_counter_rollover(stats, dev->stats, tx_excessive_collision);
	check_counter_rollover(stats, dev->stats, tx_late_collisions);
	check_counter_rollover(stats, dev->stats, tx_unicast_byte_count);
	check_counter_rollover(stats, dev->stats, tx_broadcast_byte_count);
	check_counter_rollover(stats, dev->stats, tx_multicast_byte_count);
	check_counter_rollover(stats, dev->stats, tx_unicast_frames);
	check_counter_rollover(stats, dev->stats, tx_broadcast_frames);
	check_counter_rollover(stats, dev->stats, tx_multicast_frames);
	check_counter_rollover(stats, dev->stats, tx_छोड़ो_frames);
	check_counter_rollover(stats, dev->stats, tx_64_byte_frames);
	check_counter_rollover(stats, dev->stats, tx_65_127_byte_frames);
	check_counter_rollover(stats, dev->stats, tx_128_255_byte_frames);
	check_counter_rollover(stats, dev->stats, tx_256_511_bytes_frames);
	check_counter_rollover(stats, dev->stats, tx_512_1023_byte_frames);
	check_counter_rollover(stats, dev->stats, tx_1024_1518_byte_frames);
	check_counter_rollover(stats, dev->stats, tx_greater_1518_byte_frames);
	check_counter_rollover(stats, dev->stats, eee_tx_lpi_transitions);
	check_counter_rollover(stats, dev->stats, eee_tx_lpi_समय);

	स_नकल(&dev->stats.saved, stats, माप(काष्ठा lan78xx_statstage));
पूर्ण

अटल व्योम lan78xx_update_stats(काष्ठा lan78xx_net *dev)
अणु
	u32 *p, *count, *max;
	u64 *data;
	पूर्णांक i;
	काष्ठा lan78xx_statstage lan78xx_stats;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf) < 0)
		वापस;

	p = (u32 *)&lan78xx_stats;
	count = (u32 *)&dev->stats.rollover_count;
	max = (u32 *)&dev->stats.rollover_max;
	data = (u64 *)&dev->stats.curr_stat;

	mutex_lock(&dev->stats.access_lock);

	अगर (lan78xx_पढ़ो_stats(dev, &lan78xx_stats) > 0)
		lan78xx_check_stat_rollover(dev, &lan78xx_stats);

	क्रम (i = 0; i < (माप(lan78xx_stats) / (माप(u32))); i++)
		data[i] = (u64)p[i] + ((u64)count[i] * ((u64)max[i] + 1));

	mutex_unlock(&dev->stats.access_lock);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
पूर्ण

/* Loop until the पढ़ो is completed with समयout called with phy_mutex held */
अटल पूर्णांक lan78xx_phy_रुको_not_busy(काष्ठा lan78xx_net *dev)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = lan78xx_पढ़ो_reg(dev, MII_ACC, &val);
		अगर (unlikely(ret < 0))
			वापस -EIO;

		अगर (!(val & MII_ACC_MII_BUSY_))
			वापस 0;
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	वापस -EIO;
पूर्ण

अटल अंतरभूत u32 mii_access(पूर्णांक id, पूर्णांक index, पूर्णांक पढ़ो)
अणु
	u32 ret;

	ret = ((u32)id << MII_ACC_PHY_ADDR_SHIFT_) & MII_ACC_PHY_ADDR_MASK_;
	ret |= ((u32)index << MII_ACC_MIIRINDA_SHIFT_) & MII_ACC_MIIRINDA_MASK_;
	अगर (पढ़ो)
		ret |= MII_ACC_MII_READ_;
	अन्यथा
		ret |= MII_ACC_MII_WRITE_;
	ret |= MII_ACC_MII_BUSY_;

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_रुको_eeprom(काष्ठा lan78xx_net *dev)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = lan78xx_पढ़ो_reg(dev, E2P_CMD, &val);
		अगर (unlikely(ret < 0))
			वापस -EIO;

		अगर (!(val & E2P_CMD_EPC_BUSY_) ||
		    (val & E2P_CMD_EPC_TIMEOUT_))
			अवरोध;
		usleep_range(40, 100);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	अगर (val & (E2P_CMD_EPC_TIMEOUT_ | E2P_CMD_EPC_BUSY_)) अणु
		netdev_warn(dev->net, "EEPROM read operation timeout");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_eeprom_confirm_not_busy(काष्ठा lan78xx_net *dev)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;
	u32 val;
	पूर्णांक ret;

	करो अणु
		ret = lan78xx_पढ़ो_reg(dev, E2P_CMD, &val);
		अगर (unlikely(ret < 0))
			वापस -EIO;

		अगर (!(val & E2P_CMD_EPC_BUSY_))
			वापस 0;

		usleep_range(40, 100);
	पूर्ण जबतक (!समय_after(jअगरfies, start_समय + HZ));

	netdev_warn(dev->net, "EEPROM is busy");
	वापस -EIO;
पूर्ण

अटल पूर्णांक lan78xx_पढ़ो_raw_eeprom(काष्ठा lan78xx_net *dev, u32 offset,
				   u32 length, u8 *data)
अणु
	u32 val;
	u32 saved;
	पूर्णांक i, ret;
	पूर्णांक retval;

	/* depends on chip, some EEPROM pins are muxed with LED function.
	 * disable & restore LED function to access EEPROM.
	 */
	ret = lan78xx_पढ़ो_reg(dev, HW_CFG, &val);
	saved = val;
	अगर (dev->chipid == ID_REV_CHIP_ID_7800_) अणु
		val &= ~(HW_CFG_LED1_EN_ | HW_CFG_LED0_EN_);
		ret = lan78xx_ग_लिखो_reg(dev, HW_CFG, val);
	पूर्ण

	retval = lan78xx_eeprom_confirm_not_busy(dev);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < length; i++) अणु
		val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_READ_;
		val |= (offset & E2P_CMD_EPC_ADDR_MASK_);
		ret = lan78xx_ग_लिखो_reg(dev, E2P_CMD, val);
		अगर (unlikely(ret < 0)) अणु
			retval = -EIO;
			जाओ निकास;
		पूर्ण

		retval = lan78xx_रुको_eeprom(dev);
		अगर (retval < 0)
			जाओ निकास;

		ret = lan78xx_पढ़ो_reg(dev, E2P_DATA, &val);
		अगर (unlikely(ret < 0)) अणु
			retval = -EIO;
			जाओ निकास;
		पूर्ण

		data[i] = val & 0xFF;
		offset++;
	पूर्ण

	retval = 0;
निकास:
	अगर (dev->chipid == ID_REV_CHIP_ID_7800_)
		ret = lan78xx_ग_लिखो_reg(dev, HW_CFG, saved);

	वापस retval;
पूर्ण

अटल पूर्णांक lan78xx_पढ़ो_eeprom(काष्ठा lan78xx_net *dev, u32 offset,
			       u32 length, u8 *data)
अणु
	u8 sig;
	पूर्णांक ret;

	ret = lan78xx_पढ़ो_raw_eeprom(dev, 0, 1, &sig);
	अगर ((ret == 0) && (sig == EEPROM_INDICATOR))
		ret = lan78xx_पढ़ो_raw_eeprom(dev, offset, length, data);
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_ग_लिखो_raw_eeprom(काष्ठा lan78xx_net *dev, u32 offset,
				    u32 length, u8 *data)
अणु
	u32 val;
	u32 saved;
	पूर्णांक i, ret;
	पूर्णांक retval;

	/* depends on chip, some EEPROM pins are muxed with LED function.
	 * disable & restore LED function to access EEPROM.
	 */
	ret = lan78xx_पढ़ो_reg(dev, HW_CFG, &val);
	saved = val;
	अगर (dev->chipid == ID_REV_CHIP_ID_7800_) अणु
		val &= ~(HW_CFG_LED1_EN_ | HW_CFG_LED0_EN_);
		ret = lan78xx_ग_लिखो_reg(dev, HW_CFG, val);
	पूर्ण

	retval = lan78xx_eeprom_confirm_not_busy(dev);
	अगर (retval)
		जाओ निकास;

	/* Issue ग_लिखो/erase enable command */
	val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_EWEN_;
	ret = lan78xx_ग_लिखो_reg(dev, E2P_CMD, val);
	अगर (unlikely(ret < 0)) अणु
		retval = -EIO;
		जाओ निकास;
	पूर्ण

	retval = lan78xx_रुको_eeprom(dev);
	अगर (retval < 0)
		जाओ निकास;

	क्रम (i = 0; i < length; i++) अणु
		/* Fill data रेजिस्टर */
		val = data[i];
		ret = lan78xx_ग_लिखो_reg(dev, E2P_DATA, val);
		अगर (ret < 0) अणु
			retval = -EIO;
			जाओ निकास;
		पूर्ण

		/* Send "write" command */
		val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_WRITE_;
		val |= (offset & E2P_CMD_EPC_ADDR_MASK_);
		ret = lan78xx_ग_लिखो_reg(dev, E2P_CMD, val);
		अगर (ret < 0) अणु
			retval = -EIO;
			जाओ निकास;
		पूर्ण

		retval = lan78xx_रुको_eeprom(dev);
		अगर (retval < 0)
			जाओ निकास;

		offset++;
	पूर्ण

	retval = 0;
निकास:
	अगर (dev->chipid == ID_REV_CHIP_ID_7800_)
		ret = lan78xx_ग_लिखो_reg(dev, HW_CFG, saved);

	वापस retval;
पूर्ण

अटल पूर्णांक lan78xx_पढ़ो_raw_otp(काष्ठा lan78xx_net *dev, u32 offset,
				u32 length, u8 *data)
अणु
	पूर्णांक i;
	u32 buf;
	अचिन्हित दीर्घ समयout;

	lan78xx_पढ़ो_reg(dev, OTP_PWR_DN, &buf);

	अगर (buf & OTP_PWR_DN_PWRDN_N_) अणु
		/* clear it and रुको to be cleared */
		lan78xx_ग_लिखो_reg(dev, OTP_PWR_DN, 0);

		समयout = jअगरfies + HZ;
		करो अणु
			usleep_range(1, 10);
			lan78xx_पढ़ो_reg(dev, OTP_PWR_DN, &buf);
			अगर (समय_after(jअगरfies, समयout)) अणु
				netdev_warn(dev->net,
					    "timeout on OTP_PWR_DN");
				वापस -EIO;
			पूर्ण
		पूर्ण जबतक (buf & OTP_PWR_DN_PWRDN_N_);
	पूर्ण

	क्रम (i = 0; i < length; i++) अणु
		lan78xx_ग_लिखो_reg(dev, OTP_ADDR1,
					((offset + i) >> 8) & OTP_ADDR1_15_11);
		lan78xx_ग_लिखो_reg(dev, OTP_ADDR2,
					((offset + i) & OTP_ADDR2_10_3));

		lan78xx_ग_लिखो_reg(dev, OTP_FUNC_CMD, OTP_FUNC_CMD_READ_);
		lan78xx_ग_लिखो_reg(dev, OTP_CMD_GO, OTP_CMD_GO_GO_);

		समयout = jअगरfies + HZ;
		करो अणु
			udelay(1);
			lan78xx_पढ़ो_reg(dev, OTP_STATUS, &buf);
			अगर (समय_after(jअगरfies, समयout)) अणु
				netdev_warn(dev->net,
					    "timeout on OTP_STATUS");
				वापस -EIO;
			पूर्ण
		पूर्ण जबतक (buf & OTP_STATUS_BUSY_);

		lan78xx_पढ़ो_reg(dev, OTP_RD_DATA, &buf);

		data[i] = (u8)(buf & 0xFF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_ग_लिखो_raw_otp(काष्ठा lan78xx_net *dev, u32 offset,
				 u32 length, u8 *data)
अणु
	पूर्णांक i;
	u32 buf;
	अचिन्हित दीर्घ समयout;

	lan78xx_पढ़ो_reg(dev, OTP_PWR_DN, &buf);

	अगर (buf & OTP_PWR_DN_PWRDN_N_) अणु
		/* clear it and रुको to be cleared */
		lan78xx_ग_लिखो_reg(dev, OTP_PWR_DN, 0);

		समयout = jअगरfies + HZ;
		करो अणु
			udelay(1);
			lan78xx_पढ़ो_reg(dev, OTP_PWR_DN, &buf);
			अगर (समय_after(jअगरfies, समयout)) अणु
				netdev_warn(dev->net,
					    "timeout on OTP_PWR_DN completion");
				वापस -EIO;
			पूर्ण
		पूर्ण जबतक (buf & OTP_PWR_DN_PWRDN_N_);
	पूर्ण

	/* set to BYTE program mode */
	lan78xx_ग_लिखो_reg(dev, OTP_PRGM_MODE, OTP_PRGM_MODE_BYTE_);

	क्रम (i = 0; i < length; i++) अणु
		lan78xx_ग_लिखो_reg(dev, OTP_ADDR1,
					((offset + i) >> 8) & OTP_ADDR1_15_11);
		lan78xx_ग_लिखो_reg(dev, OTP_ADDR2,
					((offset + i) & OTP_ADDR2_10_3));
		lan78xx_ग_लिखो_reg(dev, OTP_PRGM_DATA, data[i]);
		lan78xx_ग_लिखो_reg(dev, OTP_TST_CMD, OTP_TST_CMD_PRGVRFY_);
		lan78xx_ग_लिखो_reg(dev, OTP_CMD_GO, OTP_CMD_GO_GO_);

		समयout = jअगरfies + HZ;
		करो अणु
			udelay(1);
			lan78xx_पढ़ो_reg(dev, OTP_STATUS, &buf);
			अगर (समय_after(jअगरfies, समयout)) अणु
				netdev_warn(dev->net,
					    "Timeout on OTP_STATUS completion");
				वापस -EIO;
			पूर्ण
		पूर्ण जबतक (buf & OTP_STATUS_BUSY_);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_पढ़ो_otp(काष्ठा lan78xx_net *dev, u32 offset,
			    u32 length, u8 *data)
अणु
	u8 sig;
	पूर्णांक ret;

	ret = lan78xx_पढ़ो_raw_otp(dev, 0, 1, &sig);

	अगर (ret == 0) अणु
		अगर (sig == OTP_INDICATOR_2)
			offset += 0x100;
		अन्यथा अगर (sig != OTP_INDICATOR_1)
			ret = -EINVAL;
		अगर (!ret)
			ret = lan78xx_पढ़ो_raw_otp(dev, offset, length, data);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_dataport_रुको_not_busy(काष्ठा lan78xx_net *dev)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < 100; i++) अणु
		u32 dp_sel;

		ret = lan78xx_पढ़ो_reg(dev, DP_SEL, &dp_sel);
		अगर (unlikely(ret < 0))
			वापस -EIO;

		अगर (dp_sel & DP_SEL_DPRDY_)
			वापस 0;

		usleep_range(40, 100);
	पूर्ण

	netdev_warn(dev->net, "lan78xx_dataport_wait_not_busy timed out");

	वापस -EIO;
पूर्ण

अटल पूर्णांक lan78xx_dataport_ग_लिखो(काष्ठा lan78xx_net *dev, u32 ram_select,
				  u32 addr, u32 length, u32 *buf)
अणु
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	u32 dp_sel;
	पूर्णांक i, ret;

	अगर (usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf) < 0)
			वापस 0;

	mutex_lock(&pdata->dataport_mutex);

	ret = lan78xx_dataport_रुको_not_busy(dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = lan78xx_पढ़ो_reg(dev, DP_SEL, &dp_sel);

	dp_sel &= ~DP_SEL_RSEL_MASK_;
	dp_sel |= ram_select;
	ret = lan78xx_ग_लिखो_reg(dev, DP_SEL, dp_sel);

	क्रम (i = 0; i < length; i++) अणु
		ret = lan78xx_ग_लिखो_reg(dev, DP_ADDR, addr + i);

		ret = lan78xx_ग_लिखो_reg(dev, DP_DATA, buf[i]);

		ret = lan78xx_ग_लिखो_reg(dev, DP_CMD, DP_CMD_WRITE_);

		ret = lan78xx_dataport_रुको_not_busy(dev);
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

करोne:
	mutex_unlock(&pdata->dataport_mutex);
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल व्योम lan78xx_set_addr_filter(काष्ठा lan78xx_priv *pdata,
				    पूर्णांक index, u8 addr[ETH_ALEN])
अणु
	u32 temp;

	अगर ((pdata) && (index > 0) && (index < NUM_OF_MAF)) अणु
		temp = addr[3];
		temp = addr[2] | (temp << 8);
		temp = addr[1] | (temp << 8);
		temp = addr[0] | (temp << 8);
		pdata->pfilter_table[index][1] = temp;
		temp = addr[5];
		temp = addr[4] | (temp << 8);
		temp |= MAF_HI_VALID_ | MAF_HI_TYPE_DST_;
		pdata->pfilter_table[index][0] = temp;
	पूर्ण
पूर्ण

/* वापसs hash bit number क्रम given MAC address */
अटल अंतरभूत u32 lan78xx_hash(अक्षर addr[ETH_ALEN])
अणु
	वापस (ether_crc(ETH_ALEN, addr) >> 23) & 0x1ff;
पूर्ण

अटल व्योम lan78xx_deferred_multicast_ग_लिखो(काष्ठा work_काष्ठा *param)
अणु
	काष्ठा lan78xx_priv *pdata =
			container_of(param, काष्ठा lan78xx_priv, set_multicast);
	काष्ठा lan78xx_net *dev = pdata->dev;
	पूर्णांक i;

	netअगर_dbg(dev, drv, dev->net, "deferred multicast write 0x%08x\n",
		  pdata->rfe_ctl);

	lan78xx_dataport_ग_लिखो(dev, DP_SEL_RSEL_VLAN_DA_, DP_SEL_VHF_VLAN_LEN,
			       DP_SEL_VHF_HASH_LEN, pdata->mchash_table);

	क्रम (i = 1; i < NUM_OF_MAF; i++) अणु
		lan78xx_ग_लिखो_reg(dev, MAF_HI(i), 0);
		lan78xx_ग_लिखो_reg(dev, MAF_LO(i),
					pdata->pfilter_table[i][1]);
		lan78xx_ग_लिखो_reg(dev, MAF_HI(i),
					pdata->pfilter_table[i][0]);
	पूर्ण

	lan78xx_ग_लिखो_reg(dev, RFE_CTL, pdata->rfe_ctl);
पूर्ण

अटल व्योम lan78xx_set_multicast(काष्ठा net_device *netdev)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&pdata->rfe_ctl_lock, flags);

	pdata->rfe_ctl &= ~(RFE_CTL_UCAST_EN_ | RFE_CTL_MCAST_EN_ |
			    RFE_CTL_DA_PERFECT_ | RFE_CTL_MCAST_HASH_);

	क्रम (i = 0; i < DP_SEL_VHF_HASH_LEN; i++)
			pdata->mchash_table[i] = 0;
	/* pfilter_table[0] has own HW address */
	क्रम (i = 1; i < NUM_OF_MAF; i++) अणु
			pdata->pfilter_table[i][0] =
			pdata->pfilter_table[i][1] = 0;
	पूर्ण

	pdata->rfe_ctl |= RFE_CTL_BCAST_EN_;

	अगर (dev->net->flags & IFF_PROMISC) अणु
		netअगर_dbg(dev, drv, dev->net, "promiscuous mode enabled");
		pdata->rfe_ctl |= RFE_CTL_MCAST_EN_ | RFE_CTL_UCAST_EN_;
	पूर्ण अन्यथा अणु
		अगर (dev->net->flags & IFF_ALLMULTI) अणु
			netअगर_dbg(dev, drv, dev->net,
				  "receive all multicast enabled");
			pdata->rfe_ctl |= RFE_CTL_MCAST_EN_;
		पूर्ण
	पूर्ण

	अगर (netdev_mc_count(dev->net)) अणु
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक i;

		netअगर_dbg(dev, drv, dev->net, "receive multicast hash filter");

		pdata->rfe_ctl |= RFE_CTL_DA_PERFECT_;

		i = 1;
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			/* set first 32 पूर्णांकo Perfect Filter */
			अगर (i < 33) अणु
				lan78xx_set_addr_filter(pdata, i, ha->addr);
			पूर्ण अन्यथा अणु
				u32 bitnum = lan78xx_hash(ha->addr);

				pdata->mchash_table[bitnum / 32] |=
							(1 << (bitnum % 32));
				pdata->rfe_ctl |= RFE_CTL_MCAST_HASH_;
			पूर्ण
			i++;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pdata->rfe_ctl_lock, flags);

	/* defer रेजिस्टर ग_लिखोs to a sleepable context */
	schedule_work(&pdata->set_multicast);
पूर्ण

अटल पूर्णांक lan78xx_update_flowcontrol(काष्ठा lan78xx_net *dev, u8 duplex,
				      u16 lcladv, u16 rmtadv)
अणु
	u32 flow = 0, fct_flow = 0;
	u8 cap;

	अगर (dev->fc_स्वतःneg)
		cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);
	अन्यथा
		cap = dev->fc_request_control;

	अगर (cap & FLOW_CTRL_TX)
		flow |= (FLOW_CR_TX_FCEN_ | 0xFFFF);

	अगर (cap & FLOW_CTRL_RX)
		flow |= FLOW_CR_RX_FCEN_;

	अगर (dev->udev->speed == USB_SPEED_SUPER)
		fct_flow = 0x817;
	अन्यथा अगर (dev->udev->speed == USB_SPEED_HIGH)
		fct_flow = 0x211;

	netअगर_dbg(dev, link, dev->net, "rx pause %s, tx pause %s",
		  (cap & FLOW_CTRL_RX ? "enabled" : "disabled"),
		  (cap & FLOW_CTRL_TX ? "enabled" : "disabled"));

	lan78xx_ग_लिखो_reg(dev, FCT_FLOW, fct_flow);

	/* threshold value should be set beक्रमe enabling flow */
	lan78xx_ग_लिखो_reg(dev, FLOW, flow);

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_link_reset(काष्ठा lan78xx_net *dev)
अणु
	काष्ठा phy_device *phydev = dev->net->phydev;
	काष्ठा ethtool_link_ksettings ecmd;
	पूर्णांक ladv, radv, ret;
	u32 buf;

	/* clear LAN78xx पूर्णांकerrupt status */
	ret = lan78xx_ग_लिखो_reg(dev, INT_STS, INT_STS_PHY_INT_);
	अगर (unlikely(ret < 0))
		वापस -EIO;

	phy_पढ़ो_status(phydev);

	अगर (!phydev->link && dev->link_on) अणु
		dev->link_on = false;

		/* reset MAC */
		ret = lan78xx_पढ़ो_reg(dev, MAC_CR, &buf);
		अगर (unlikely(ret < 0))
			वापस -EIO;
		buf |= MAC_CR_RST_;
		ret = lan78xx_ग_लिखो_reg(dev, MAC_CR, buf);
		अगर (unlikely(ret < 0))
			वापस -EIO;

		del_समयr(&dev->stat_monitor);
	पूर्ण अन्यथा अगर (phydev->link && !dev->link_on) अणु
		dev->link_on = true;

		phy_ethtool_ksettings_get(phydev, &ecmd);

		अगर (dev->udev->speed == USB_SPEED_SUPER) अणु
			अगर (ecmd.base.speed == 1000) अणु
				/* disable U2 */
				ret = lan78xx_पढ़ो_reg(dev, USB_CFG1, &buf);
				buf &= ~USB_CFG1_DEV_U2_INIT_EN_;
				ret = lan78xx_ग_लिखो_reg(dev, USB_CFG1, buf);
				/* enable U1 */
				ret = lan78xx_पढ़ो_reg(dev, USB_CFG1, &buf);
				buf |= USB_CFG1_DEV_U1_INIT_EN_;
				ret = lan78xx_ग_लिखो_reg(dev, USB_CFG1, buf);
			पूर्ण अन्यथा अणु
				/* enable U1 & U2 */
				ret = lan78xx_पढ़ो_reg(dev, USB_CFG1, &buf);
				buf |= USB_CFG1_DEV_U2_INIT_EN_;
				buf |= USB_CFG1_DEV_U1_INIT_EN_;
				ret = lan78xx_ग_लिखो_reg(dev, USB_CFG1, buf);
			पूर्ण
		पूर्ण

		ladv = phy_पढ़ो(phydev, MII_ADVERTISE);
		अगर (ladv < 0)
			वापस ladv;

		radv = phy_पढ़ो(phydev, MII_LPA);
		अगर (radv < 0)
			वापस radv;

		netअगर_dbg(dev, link, dev->net,
			  "speed: %u duplex: %d anadv: 0x%04x anlpa: 0x%04x",
			  ecmd.base.speed, ecmd.base.duplex, ladv, radv);

		ret = lan78xx_update_flowcontrol(dev, ecmd.base.duplex, ladv,
						 radv);

		अगर (!समयr_pending(&dev->stat_monitor)) अणु
			dev->delta = 1;
			mod_समयr(&dev->stat_monitor,
				  jअगरfies + STAT_UPDATE_TIMER);
		पूर्ण

		tasklet_schedule(&dev->bh);
	पूर्ण

	वापस ret;
पूर्ण

/* some work can't be करोne in tasklets, so we use keventd
 *
 * NOTE:  annoying asymmetry:  अगर it's active, schedule_work() fails,
 * but tasklet_schedule() करोesn't.	hope the failure is rare.
 */
अटल व्योम lan78xx_defer_kevent(काष्ठा lan78xx_net *dev, पूर्णांक work)
अणु
	set_bit(work, &dev->flags);
	अगर (!schedule_delayed_work(&dev->wq, 0))
		netdev_err(dev->net, "kevent %d may have been dropped\n", work);
पूर्ण

अटल व्योम lan78xx_status(काष्ठा lan78xx_net *dev, काष्ठा urb *urb)
अणु
	u32 पूर्णांकdata;

	अगर (urb->actual_length != 4) अणु
		netdev_warn(dev->net,
			    "unexpected urb length %d", urb->actual_length);
		वापस;
	पूर्ण

	पूर्णांकdata = get_unaligned_le32(urb->transfer_buffer);

	अगर (पूर्णांकdata & INT_ENP_PHY_INT) अणु
		netअगर_dbg(dev, link, dev->net, "PHY INTR: 0x%08x\n", पूर्णांकdata);
		lan78xx_defer_kevent(dev, EVENT_LINK_RESET);

		अगर (dev->करोमुख्य_data.phyirq > 0) अणु
			local_irq_disable();
			generic_handle_irq(dev->करोमुख्य_data.phyirq);
			local_irq_enable();
		पूर्ण
	पूर्ण अन्यथा
		netdev_warn(dev->net,
			    "unexpected interrupt: 0x%08x\n", पूर्णांकdata);
पूर्ण

अटल पूर्णांक lan78xx_ethtool_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	वापस MAX_EEPROM_SIZE;
पूर्ण

अटल पूर्णांक lan78xx_ethtool_get_eeprom(काष्ठा net_device *netdev,
				      काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret)
		वापस ret;

	ee->magic = LAN78XX_EEPROM_MAGIC;

	ret = lan78xx_पढ़ो_raw_eeprom(dev, ee->offset, ee->len, data);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_ethtool_set_eeprom(काष्ठा net_device *netdev,
				      काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret)
		वापस ret;

	/* Invalid EEPROM_INDICATOR at offset zero will result in a failure
	 * to load data from EEPROM
	 */
	अगर (ee->magic == LAN78XX_EEPROM_MAGIC)
		ret = lan78xx_ग_लिखो_raw_eeprom(dev, ee->offset, ee->len, data);
	अन्यथा अगर ((ee->magic == LAN78XX_OTP_MAGIC) &&
		 (ee->offset == 0) &&
		 (ee->len == 512) &&
		 (data[0] == OTP_INDICATOR_1))
		ret = lan78xx_ग_लिखो_raw_otp(dev, ee->offset, ee->len, data);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल व्योम lan78xx_get_strings(काष्ठा net_device *netdev, u32 stringset,
				u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS)
		स_नकल(data, lan78xx_gstrings, माप(lan78xx_gstrings));
पूर्ण

अटल पूर्णांक lan78xx_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	अगर (sset == ETH_SS_STATS)
		वापस ARRAY_SIZE(lan78xx_gstrings);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम lan78xx_get_stats(काष्ठा net_device *netdev,
			      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);

	lan78xx_update_stats(dev);

	mutex_lock(&dev->stats.access_lock);
	स_नकल(data, &dev->stats.curr_stat, माप(dev->stats.curr_stat));
	mutex_unlock(&dev->stats.access_lock);
पूर्ण

अटल व्योम lan78xx_get_wol(काष्ठा net_device *netdev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	पूर्णांक ret;
	u32 buf;
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);

	अगर (usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf) < 0)
			वापस;

	ret = lan78xx_पढ़ो_reg(dev, USB_CFG0, &buf);
	अगर (unlikely(ret < 0)) अणु
		wol->supported = 0;
		wol->wolopts = 0;
	पूर्ण अन्यथा अणु
		अगर (buf & USB_CFG_RMT_WKP_) अणु
			wol->supported = WAKE_ALL;
			wol->wolopts = pdata->wol;
		पूर्ण अन्यथा अणु
			wol->supported = 0;
			wol->wolopts = 0;
		पूर्ण
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
पूर्ण

अटल पूर्णांक lan78xx_set_wol(काष्ठा net_device *netdev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	अगर (wol->wolopts & ~WAKE_ALL)
		वापस -EINVAL;

	pdata->wol = wol->wolopts;

	device_set_wakeup_enable(&dev->udev->dev, (bool)wol->wolopts);

	phy_ethtool_set_wol(netdev->phydev, wol);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_get_eee(काष्ठा net_device *net, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	काष्ठा phy_device *phydev = net->phydev;
	पूर्णांक ret;
	u32 buf;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	ret = phy_ethtool_get_eee(phydev, edata);
	अगर (ret < 0)
		जाओ निकास;

	ret = lan78xx_पढ़ो_reg(dev, MAC_CR, &buf);
	अगर (buf & MAC_CR_EEE_EN_) अणु
		edata->eee_enabled = true;
		edata->eee_active = !!(edata->advertised &
				       edata->lp_advertised);
		edata->tx_lpi_enabled = true;
		/* EEE_TX_LPI_REQ_DLY & tx_lpi_समयr are same uSec unit */
		ret = lan78xx_पढ़ो_reg(dev, EEE_TX_LPI_REQ_DLY, &buf);
		edata->tx_lpi_समयr = buf;
	पूर्ण अन्यथा अणु
		edata->eee_enabled = false;
		edata->eee_active = false;
		edata->tx_lpi_enabled = false;
		edata->tx_lpi_समयr = 0;
	पूर्ण

	ret = 0;
निकास:
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_set_eee(काष्ठा net_device *net, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	पूर्णांक ret;
	u32 buf;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	अगर (edata->eee_enabled) अणु
		ret = lan78xx_पढ़ो_reg(dev, MAC_CR, &buf);
		buf |= MAC_CR_EEE_EN_;
		ret = lan78xx_ग_लिखो_reg(dev, MAC_CR, buf);

		phy_ethtool_set_eee(net->phydev, edata);

		buf = (u32)edata->tx_lpi_समयr;
		ret = lan78xx_ग_लिखो_reg(dev, EEE_TX_LPI_REQ_DLY, buf);
	पूर्ण अन्यथा अणु
		ret = lan78xx_पढ़ो_reg(dev, MAC_CR, &buf);
		buf &= ~MAC_CR_EEE_EN_;
		ret = lan78xx_ग_लिखो_reg(dev, MAC_CR, buf);
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस 0;
पूर्ण

अटल u32 lan78xx_get_link(काष्ठा net_device *net)
अणु
	phy_पढ़ो_status(net->phydev);

	वापस net->phydev->link;
पूर्ण

अटल व्योम lan78xx_get_drvinfo(काष्ठा net_device *net,
				काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);

	म_नकलन(info->driver, DRIVER_NAME, माप(info->driver));
	usb_make_path(dev->udev, info->bus_info, माप(info->bus_info));
पूर्ण

अटल u32 lan78xx_get_msglevel(काष्ठा net_device *net)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);

	वापस dev->msg_enable;
पूर्ण

अटल व्योम lan78xx_set_msglevel(काष्ठा net_device *net, u32 level)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);

	dev->msg_enable = level;
पूर्ण

अटल पूर्णांक lan78xx_get_link_ksettings(काष्ठा net_device *net,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	काष्ठा phy_device *phydev = net->phydev;
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	phy_ethtool_ksettings_get(phydev, cmd);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_set_link_ksettings(काष्ठा net_device *net,
				      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	काष्ठा phy_device *phydev = net->phydev;
	पूर्णांक ret = 0;
	पूर्णांक temp;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	/* change speed & duplex */
	ret = phy_ethtool_ksettings_set(phydev, cmd);

	अगर (!cmd->base.स्वतःneg) अणु
		/* क्रमce link करोwn */
		temp = phy_पढ़ो(phydev, MII_BMCR);
		phy_ग_लिखो(phydev, MII_BMCR, temp | BMCR_LOOPBACK);
		mdelay(1);
		phy_ग_लिखो(phydev, MII_BMCR, temp);
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल व्योम lan78xx_get_छोड़ो(काष्ठा net_device *net,
			      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	काष्ठा phy_device *phydev = net->phydev;
	काष्ठा ethtool_link_ksettings ecmd;

	phy_ethtool_ksettings_get(phydev, &ecmd);

	छोड़ो->स्वतःneg = dev->fc_स्वतःneg;

	अगर (dev->fc_request_control & FLOW_CTRL_TX)
		छोड़ो->tx_छोड़ो = 1;

	अगर (dev->fc_request_control & FLOW_CTRL_RX)
		छोड़ो->rx_छोड़ो = 1;
पूर्ण

अटल पूर्णांक lan78xx_set_छोड़ो(काष्ठा net_device *net,
			     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	काष्ठा phy_device *phydev = net->phydev;
	काष्ठा ethtool_link_ksettings ecmd;
	पूर्णांक ret;

	phy_ethtool_ksettings_get(phydev, &ecmd);

	अगर (छोड़ो->स्वतःneg && !ecmd.base.स्वतःneg) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	dev->fc_request_control = 0;
	अगर (छोड़ो->rx_छोड़ो)
		dev->fc_request_control |= FLOW_CTRL_RX;

	अगर (छोड़ो->tx_छोड़ो)
		dev->fc_request_control |= FLOW_CTRL_TX;

	अगर (ecmd.base.स्वतःneg) अणु
		__ETHTOOL_DECLARE_LINK_MODE_MASK(fc) = अणु 0, पूर्ण;
		u32 mii_adv;

		linkmode_clear_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				   ecmd.link_modes.advertising);
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				   ecmd.link_modes.advertising);
		mii_adv = (u32)mii_advertise_flowctrl(dev->fc_request_control);
		mii_adv_to_linkmode_adv_t(fc, mii_adv);
		linkmode_or(ecmd.link_modes.advertising, fc,
			    ecmd.link_modes.advertising);

		phy_ethtool_ksettings_set(phydev, &ecmd);
	पूर्ण

	dev->fc_स्वतःneg = छोड़ो->स्वतःneg;

	ret = 0;
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_get_regs_len(काष्ठा net_device *netdev)
अणु
	अगर (!netdev->phydev)
		वापस (माप(lan78xx_regs));
	अन्यथा
		वापस (माप(lan78xx_regs) + PHY_REG_SIZE);
पूर्ण

अटल व्योम
lan78xx_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs,
		 व्योम *buf)
अणु
	u32 *data = buf;
	पूर्णांक i, j;
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);

	/* Read Device/MAC रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(lan78xx_regs); i++)
		lan78xx_पढ़ो_reg(dev, lan78xx_regs[i], &data[i]);

	अगर (!netdev->phydev)
		वापस;

	/* Read PHY रेजिस्टरs */
	क्रम (j = 0; j < 32; i++, j++)
		data[i] = phy_पढ़ो(netdev->phydev, j);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops lan78xx_ethtool_ops = अणु
	.get_link	= lan78xx_get_link,
	.nway_reset	= phy_ethtool_nway_reset,
	.get_drvinfo	= lan78xx_get_drvinfo,
	.get_msglevel	= lan78xx_get_msglevel,
	.set_msglevel	= lan78xx_set_msglevel,
	.get_eeprom_len = lan78xx_ethtool_get_eeprom_len,
	.get_eeprom	= lan78xx_ethtool_get_eeprom,
	.set_eeprom	= lan78xx_ethtool_set_eeprom,
	.get_ethtool_stats = lan78xx_get_stats,
	.get_sset_count = lan78xx_get_sset_count,
	.get_strings	= lan78xx_get_strings,
	.get_wol	= lan78xx_get_wol,
	.set_wol	= lan78xx_set_wol,
	.get_ts_info	= ethtool_op_get_ts_info,
	.get_eee	= lan78xx_get_eee,
	.set_eee	= lan78xx_set_eee,
	.get_छोड़ोparam	= lan78xx_get_छोड़ो,
	.set_छोड़ोparam	= lan78xx_set_छोड़ो,
	.get_link_ksettings = lan78xx_get_link_ksettings,
	.set_link_ksettings = lan78xx_set_link_ksettings,
	.get_regs_len	= lan78xx_get_regs_len,
	.get_regs	= lan78xx_get_regs,
पूर्ण;

अटल व्योम lan78xx_init_mac_address(काष्ठा lan78xx_net *dev)
अणु
	u32 addr_lo, addr_hi;
	u8 addr[6];

	lan78xx_पढ़ो_reg(dev, RX_ADDRL, &addr_lo);
	lan78xx_पढ़ो_reg(dev, RX_ADDRH, &addr_hi);

	addr[0] = addr_lo & 0xFF;
	addr[1] = (addr_lo >> 8) & 0xFF;
	addr[2] = (addr_lo >> 16) & 0xFF;
	addr[3] = (addr_lo >> 24) & 0xFF;
	addr[4] = addr_hi & 0xFF;
	addr[5] = (addr_hi >> 8) & 0xFF;

	अगर (!is_valid_ether_addr(addr)) अणु
		अगर (!eth_platक्रमm_get_mac_address(&dev->udev->dev, addr)) अणु
			/* valid address present in Device Tree */
			netअगर_dbg(dev, अगरup, dev->net,
				  "MAC address read from Device Tree");
		पूर्ण अन्यथा अगर (((lan78xx_पढ़ो_eeprom(dev, EEPROM_MAC_OFFSET,
						 ETH_ALEN, addr) == 0) ||
			    (lan78xx_पढ़ो_otp(dev, EEPROM_MAC_OFFSET,
					      ETH_ALEN, addr) == 0)) &&
			   is_valid_ether_addr(addr)) अणु
			/* eeprom values are valid so use them */
			netअगर_dbg(dev, अगरup, dev->net,
				  "MAC address read from EEPROM");
		पूर्ण अन्यथा अणु
			/* generate अक्रमom MAC */
			eth_अक्रमom_addr(addr);
			netअगर_dbg(dev, अगरup, dev->net,
				  "MAC address set to random addr");
		पूर्ण

		addr_lo = addr[0] | (addr[1] << 8) |
			  (addr[2] << 16) | (addr[3] << 24);
		addr_hi = addr[4] | (addr[5] << 8);

		lan78xx_ग_लिखो_reg(dev, RX_ADDRL, addr_lo);
		lan78xx_ग_लिखो_reg(dev, RX_ADDRH, addr_hi);
	पूर्ण

	lan78xx_ग_लिखो_reg(dev, MAF_LO(0), addr_lo);
	lan78xx_ग_लिखो_reg(dev, MAF_HI(0), addr_hi | MAF_HI_VALID_);

	ether_addr_copy(dev->net->dev_addr, addr);
पूर्ण

/* MDIO पढ़ो and ग_लिखो wrappers क्रम phylib */
अटल पूर्णांक lan78xx_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक idx)
अणु
	काष्ठा lan78xx_net *dev = bus->priv;
	u32 val, addr;
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = lan78xx_phy_रुको_not_busy(dev);
	अगर (ret < 0)
		जाओ करोne;

	/* set the address, index & direction (पढ़ो from PHY) */
	addr = mii_access(phy_id, idx, MII_READ);
	ret = lan78xx_ग_लिखो_reg(dev, MII_ACC, addr);

	ret = lan78xx_phy_रुको_not_busy(dev);
	अगर (ret < 0)
		जाओ करोne;

	ret = lan78xx_पढ़ो_reg(dev, MII_DATA, &val);

	ret = (पूर्णांक)(val & 0xFFFF);

करोne:
	mutex_unlock(&dev->phy_mutex);
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक idx,
				 u16 regval)
अणु
	काष्ठा lan78xx_net *dev = bus->priv;
	u32 val, addr;
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&dev->phy_mutex);

	/* confirm MII not busy */
	ret = lan78xx_phy_रुको_not_busy(dev);
	अगर (ret < 0)
		जाओ करोne;

	val = (u32)regval;
	ret = lan78xx_ग_लिखो_reg(dev, MII_DATA, val);

	/* set the address, index & direction (ग_लिखो to PHY) */
	addr = mii_access(phy_id, idx, MII_WRITE);
	ret = lan78xx_ग_लिखो_reg(dev, MII_ACC, addr);

	ret = lan78xx_phy_रुको_not_busy(dev);
	अगर (ret < 0)
		जाओ करोne;

करोne:
	mutex_unlock(&dev->phy_mutex);
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_mdio_init(काष्ठा lan78xx_net *dev)
अणु
	काष्ठा device_node *node;
	पूर्णांक ret;

	dev->mdiobus = mdiobus_alloc();
	अगर (!dev->mdiobus) अणु
		netdev_err(dev->net, "can't allocate MDIO bus\n");
		वापस -ENOMEM;
	पूर्ण

	dev->mdiobus->priv = (व्योम *)dev;
	dev->mdiobus->पढ़ो = lan78xx_mdiobus_पढ़ो;
	dev->mdiobus->ग_लिखो = lan78xx_mdiobus_ग_लिखो;
	dev->mdiobus->name = "lan78xx-mdiobus";
	dev->mdiobus->parent = &dev->udev->dev;

	snम_लिखो(dev->mdiobus->id, MII_BUS_ID_SIZE, "usb-%03d:%03d",
		 dev->udev->bus->busnum, dev->udev->devnum);

	चयन (dev->chipid) अणु
	हाल ID_REV_CHIP_ID_7800_:
	हाल ID_REV_CHIP_ID_7850_:
		/* set to पूर्णांकernal PHY id */
		dev->mdiobus->phy_mask = ~(1 << 1);
		अवरोध;
	हाल ID_REV_CHIP_ID_7801_:
		/* scan thru PHYAD[2..0] */
		dev->mdiobus->phy_mask = ~(0xFF);
		अवरोध;
	पूर्ण

	node = of_get_child_by_name(dev->udev->dev.of_node, "mdio");
	ret = of_mdiobus_रेजिस्टर(dev->mdiobus, node);
	of_node_put(node);
	अगर (ret) अणु
		netdev_err(dev->net, "can't register MDIO bus\n");
		जाओ निकास1;
	पूर्ण

	netdev_dbg(dev->net, "registered mdiobus bus %s\n", dev->mdiobus->id);
	वापस 0;
निकास1:
	mdiobus_मुक्त(dev->mdiobus);
	वापस ret;
पूर्ण

अटल व्योम lan78xx_हटाओ_mdio(काष्ठा lan78xx_net *dev)
अणु
	mdiobus_unरेजिस्टर(dev->mdiobus);
	mdiobus_मुक्त(dev->mdiobus);
पूर्ण

अटल व्योम lan78xx_link_status_change(काष्ठा net_device *net)
अणु
	काष्ठा phy_device *phydev = net->phydev;
	पूर्णांक temp;

	/* At क्रमced 100 F/H mode, chip may fail to set mode correctly
	 * when cable is चयनed between दीर्घ(~50+m) and लघु one.
	 * As workaround, set to 10 beक्रमe setting to 100
	 * at क्रमced 100 F/H mode.
	 */
	अगर (!phydev->स्वतःneg && (phydev->speed == 100)) अणु
		/* disable phy पूर्णांकerrupt */
		temp = phy_पढ़ो(phydev, LAN88XX_INT_MASK);
		temp &= ~LAN88XX_INT_MASK_MDINTPIN_EN_;
		phy_ग_लिखो(phydev, LAN88XX_INT_MASK, temp);

		temp = phy_पढ़ो(phydev, MII_BMCR);
		temp &= ~(BMCR_SPEED100 | BMCR_SPEED1000);
		phy_ग_लिखो(phydev, MII_BMCR, temp); /* set to 10 first */
		temp |= BMCR_SPEED100;
		phy_ग_लिखो(phydev, MII_BMCR, temp); /* set to 100 later */

		/* clear pending पूर्णांकerrupt generated जबतक workaround */
		temp = phy_पढ़ो(phydev, LAN88XX_INT_STS);

		/* enable phy पूर्णांकerrupt back */
		temp = phy_पढ़ो(phydev, LAN88XX_INT_MASK);
		temp |= LAN88XX_INT_MASK_MDINTPIN_EN_;
		phy_ग_लिखो(phydev, LAN88XX_INT_MASK, temp);
	पूर्ण
पूर्ण

अटल पूर्णांक irq_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
		   irq_hw_number_t hwirq)
अणु
	काष्ठा irq_करोमुख्य_data *data = d->host_data;

	irq_set_chip_data(irq, data);
	irq_set_chip_and_handler(irq, data->irqchip, data->irq_handler);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल व्योम irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops chip_करोमुख्य_ops = अणु
	.map	= irq_map,
	.unmap	= irq_unmap,
पूर्ण;

अटल व्योम lan78xx_irq_mask(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_करोमुख्य_data *data = irq_data_get_irq_chip_data(irqd);

	data->irqenable &= ~BIT(irqd_to_hwirq(irqd));
पूर्ण

अटल व्योम lan78xx_irq_unmask(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_करोमुख्य_data *data = irq_data_get_irq_chip_data(irqd);

	data->irqenable |= BIT(irqd_to_hwirq(irqd));
पूर्ण

अटल व्योम lan78xx_irq_bus_lock(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_करोमुख्य_data *data = irq_data_get_irq_chip_data(irqd);

	mutex_lock(&data->irq_lock);
पूर्ण

अटल व्योम lan78xx_irq_bus_sync_unlock(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_करोमुख्य_data *data = irq_data_get_irq_chip_data(irqd);
	काष्ठा lan78xx_net *dev =
			container_of(data, काष्ठा lan78xx_net, करोमुख्य_data);
	u32 buf;

	/* call रेजिस्टर access here because irq_bus_lock & irq_bus_sync_unlock
	 * are only two callbacks executed in non-atomic contex.
	 */
	lan78xx_पढ़ो_reg(dev, INT_EP_CTL, &buf);
	अगर (buf != data->irqenable)
		lan78xx_ग_लिखो_reg(dev, INT_EP_CTL, data->irqenable);

	mutex_unlock(&data->irq_lock);
पूर्ण

अटल काष्ठा irq_chip lan78xx_irqchip = अणु
	.name			= "lan78xx-irqs",
	.irq_mask		= lan78xx_irq_mask,
	.irq_unmask		= lan78xx_irq_unmask,
	.irq_bus_lock		= lan78xx_irq_bus_lock,
	.irq_bus_sync_unlock	= lan78xx_irq_bus_sync_unlock,
पूर्ण;

अटल पूर्णांक lan78xx_setup_irq_करोमुख्य(काष्ठा lan78xx_net *dev)
अणु
	काष्ठा device_node *of_node;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	अचिन्हित पूर्णांक irqmap = 0;
	u32 buf;
	पूर्णांक ret = 0;

	of_node = dev->udev->dev.parent->of_node;

	mutex_init(&dev->करोमुख्य_data.irq_lock);

	lan78xx_पढ़ो_reg(dev, INT_EP_CTL, &buf);
	dev->करोमुख्य_data.irqenable = buf;

	dev->करोमुख्य_data.irqchip = &lan78xx_irqchip;
	dev->करोमुख्य_data.irq_handler = handle_simple_irq;

	irqकरोमुख्य = irq_करोमुख्य_add_simple(of_node, MAX_INT_EP, 0,
					  &chip_करोमुख्य_ops, &dev->करोमुख्य_data);
	अगर (irqकरोमुख्य) अणु
		/* create mapping क्रम PHY पूर्णांकerrupt */
		irqmap = irq_create_mapping(irqकरोमुख्य, INT_EP_PHY);
		अगर (!irqmap) अणु
			irq_करोमुख्य_हटाओ(irqकरोमुख्य);

			irqकरोमुख्य = शून्य;
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	dev->करोमुख्य_data.irqकरोमुख्य = irqकरोमुख्य;
	dev->करोमुख्य_data.phyirq = irqmap;

	वापस ret;
पूर्ण

अटल व्योम lan78xx_हटाओ_irq_करोमुख्य(काष्ठा lan78xx_net *dev)
अणु
	अगर (dev->करोमुख्य_data.phyirq > 0) अणु
		irq_dispose_mapping(dev->करोमुख्य_data.phyirq);

		अगर (dev->करोमुख्य_data.irqकरोमुख्य)
			irq_करोमुख्य_हटाओ(dev->करोमुख्य_data.irqकरोमुख्य);
	पूर्ण
	dev->करोमुख्य_data.phyirq = 0;
	dev->करोमुख्य_data.irqकरोमुख्य = शून्य;
पूर्ण

अटल पूर्णांक lan8835_fixup(काष्ठा phy_device *phydev)
अणु
	पूर्णांक buf;
	काष्ठा lan78xx_net *dev = netdev_priv(phydev->attached_dev);

	/* LED2/PME_N/IRQ_N/RGMII_ID pin to IRQ_N mode */
	buf = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, 0x8010);
	buf &= ~0x1800;
	buf |= 0x0800;
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_PCS, 0x8010, buf);

	/* RGMII MAC TXC Delay Enable */
	lan78xx_ग_लिखो_reg(dev, MAC_RGMII_ID,
				MAC_RGMII_ID_TXC_DELAY_EN_);

	/* RGMII TX DLL Tune Adjust */
	lan78xx_ग_लिखो_reg(dev, RGMII_TX_BYP_DLL, 0x3D00);

	dev->पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_TXID;

	वापस 1;
पूर्ण

अटल पूर्णांक ksz9031rnx_fixup(काष्ठा phy_device *phydev)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(phydev->attached_dev);

	/* Micrel9301RNX PHY configuration */
	/* RGMII Control Signal Pad Skew */
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_WIS, 4, 0x0077);
	/* RGMII RX Data Pad Skew */
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_WIS, 5, 0x7777);
	/* RGMII RX Clock Pad Skew */
	phy_ग_लिखो_mmd(phydev, MDIO_MMD_WIS, 8, 0x1FF);

	dev->पूर्णांकerface = PHY_INTERFACE_MODE_RGMII_RXID;

	वापस 1;
पूर्ण

अटल काष्ठा phy_device *lan7801_phy_init(काष्ठा lan78xx_net *dev)
अणु
	u32 buf;
	पूर्णांक ret;
	काष्ठा fixed_phy_status fphy_status = अणु
		.link = 1,
		.speed = SPEED_1000,
		.duplex = DUPLEX_FULL,
	पूर्ण;
	काष्ठा phy_device *phydev;

	phydev = phy_find_first(dev->mdiobus);
	अगर (!phydev) अणु
		netdev_dbg(dev->net, "PHY Not Found!! Registering Fixed PHY\n");
		phydev = fixed_phy_रेजिस्टर(PHY_POLL, &fphy_status, शून्य);
		अगर (IS_ERR(phydev)) अणु
			netdev_err(dev->net, "No PHY/fixed_PHY found\n");
			वापस शून्य;
		पूर्ण
		netdev_dbg(dev->net, "Registered FIXED PHY\n");
		dev->पूर्णांकerface = PHY_INTERFACE_MODE_RGMII;
		ret = lan78xx_ग_लिखो_reg(dev, MAC_RGMII_ID,
					MAC_RGMII_ID_TXC_DELAY_EN_);
		ret = lan78xx_ग_लिखो_reg(dev, RGMII_TX_BYP_DLL, 0x3D00);
		ret = lan78xx_पढ़ो_reg(dev, HW_CFG, &buf);
		buf |= HW_CFG_CLK125_EN_;
		buf |= HW_CFG_REFCLK25_EN_;
		ret = lan78xx_ग_लिखो_reg(dev, HW_CFG, buf);
	पूर्ण अन्यथा अणु
		अगर (!phydev->drv) अणु
			netdev_err(dev->net, "no PHY driver found\n");
			वापस शून्य;
		पूर्ण
		dev->पूर्णांकerface = PHY_INTERFACE_MODE_RGMII;
		/* बाह्यal PHY fixup क्रम KSZ9031RNX */
		ret = phy_रेजिस्टर_fixup_क्रम_uid(PHY_KSZ9031RNX, 0xfffffff0,
						 ksz9031rnx_fixup);
		अगर (ret < 0) अणु
			netdev_err(dev->net, "Failed to register fixup for PHY_KSZ9031RNX\n");
			वापस शून्य;
		पूर्ण
		/* बाह्यal PHY fixup क्रम LAN8835 */
		ret = phy_रेजिस्टर_fixup_क्रम_uid(PHY_LAN8835, 0xfffffff0,
						 lan8835_fixup);
		अगर (ret < 0) अणु
			netdev_err(dev->net, "Failed to register fixup for PHY_LAN8835\n");
			वापस शून्य;
		पूर्ण
		/* add more बाह्यal PHY fixup here अगर needed */

		phydev->is_पूर्णांकernal = false;
	पूर्ण
	वापस phydev;
पूर्ण

अटल पूर्णांक lan78xx_phy_init(काष्ठा lan78xx_net *dev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(fc) = अणु 0, पूर्ण;
	पूर्णांक ret;
	u32 mii_adv;
	काष्ठा phy_device *phydev;

	चयन (dev->chipid) अणु
	हाल ID_REV_CHIP_ID_7801_:
		phydev = lan7801_phy_init(dev);
		अगर (!phydev) अणु
			netdev_err(dev->net, "lan7801: PHY Init Failed");
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल ID_REV_CHIP_ID_7800_:
	हाल ID_REV_CHIP_ID_7850_:
		phydev = phy_find_first(dev->mdiobus);
		अगर (!phydev) अणु
			netdev_err(dev->net, "no PHY found\n");
			वापस -EIO;
		पूर्ण
		phydev->is_पूर्णांकernal = true;
		dev->पूर्णांकerface = PHY_INTERFACE_MODE_GMII;
		अवरोध;

	शेष:
		netdev_err(dev->net, "Unknown CHIP ID found\n");
		वापस -EIO;
	पूर्ण

	/* अगर phyirq is not set, use polling mode in phylib */
	अगर (dev->करोमुख्य_data.phyirq > 0)
		phydev->irq = dev->करोमुख्य_data.phyirq;
	अन्यथा
		phydev->irq = 0;
	netdev_dbg(dev->net, "phydev->irq = %d\n", phydev->irq);

	/* set to AUTOMDIX */
	phydev->mdix = ETH_TP_MDI_AUTO;

	ret = phy_connect_direct(dev->net, phydev,
				 lan78xx_link_status_change,
				 dev->पूर्णांकerface);
	अगर (ret) अणु
		netdev_err(dev->net, "can't attach PHY to %s\n",
			   dev->mdiobus->id);
		अगर (dev->chipid == ID_REV_CHIP_ID_7801_) अणु
			अगर (phy_is_pseuकरो_fixed_link(phydev)) अणु
				fixed_phy_unरेजिस्टर(phydev);
			पूर्ण अन्यथा अणु
				phy_unरेजिस्टर_fixup_क्रम_uid(PHY_KSZ9031RNX,
							     0xfffffff0);
				phy_unरेजिस्टर_fixup_क्रम_uid(PHY_LAN8835,
							     0xfffffff0);
			पूर्ण
		पूर्ण
		वापस -EIO;
	पूर्ण

	/* MAC करोesn't support 1000T Half */
	phy_हटाओ_link_mode(phydev, ETHTOOL_LINK_MODE_1000baseT_Half_BIT);

	/* support both flow controls */
	dev->fc_request_control = (FLOW_CTRL_RX | FLOW_CTRL_TX);
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Pause_BIT,
			   phydev->advertising);
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			   phydev->advertising);
	mii_adv = (u32)mii_advertise_flowctrl(dev->fc_request_control);
	mii_adv_to_linkmode_adv_t(fc, mii_adv);
	linkmode_or(phydev->advertising, fc, phydev->advertising);

	अगर (phydev->mdio.dev.of_node) अणु
		u32 reg;
		पूर्णांक len;

		len = of_property_count_elems_of_size(phydev->mdio.dev.of_node,
						      "microchip,led-modes",
						      माप(u32));
		अगर (len >= 0) अणु
			/* Ensure the appropriate LEDs are enabled */
			lan78xx_पढ़ो_reg(dev, HW_CFG, &reg);
			reg &= ~(HW_CFG_LED0_EN_ |
				 HW_CFG_LED1_EN_ |
				 HW_CFG_LED2_EN_ |
				 HW_CFG_LED3_EN_);
			reg |= (len > 0) * HW_CFG_LED0_EN_ |
				(len > 1) * HW_CFG_LED1_EN_ |
				(len > 2) * HW_CFG_LED2_EN_ |
				(len > 3) * HW_CFG_LED3_EN_;
			lan78xx_ग_लिखो_reg(dev, HW_CFG, reg);
		पूर्ण
	पूर्ण

	genphy_config_aneg(phydev);

	dev->fc_स्वतःneg = phydev->स्वतःneg;

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_set_rx_max_frame_length(काष्ठा lan78xx_net *dev, पूर्णांक size)
अणु
	u32 buf;
	bool rxenabled;

	lan78xx_पढ़ो_reg(dev, MAC_RX, &buf);

	rxenabled = ((buf & MAC_RX_RXEN_) != 0);

	अगर (rxenabled) अणु
		buf &= ~MAC_RX_RXEN_;
		lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);
	पूर्ण

	/* add 4 to size क्रम FCS */
	buf &= ~MAC_RX_MAX_SIZE_MASK_;
	buf |= (((size + 4) << MAC_RX_MAX_SIZE_SHIFT_) & MAC_RX_MAX_SIZE_MASK_);

	lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);

	अगर (rxenabled) अणु
		buf |= MAC_RX_RXEN_;
		lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक unlink_urbs(काष्ठा lan78xx_net *dev, काष्ठा sk_buff_head *q)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित दीर्घ flags;
	पूर्णांक count = 0;

	spin_lock_irqsave(&q->lock, flags);
	जबतक (!skb_queue_empty(q)) अणु
		काष्ठा skb_data	*entry;
		काष्ठा urb *urb;
		पूर्णांक ret;

		skb_queue_walk(q, skb) अणु
			entry = (काष्ठा skb_data *)skb->cb;
			अगर (entry->state != unlink_start)
				जाओ found;
		पूर्ण
		अवरोध;
found:
		entry->state = unlink_start;
		urb = entry->urb;

		/* Get reference count of the URB to aव्योम it to be
		 * मुक्तd during usb_unlink_urb, which may trigger
		 * use-after-मुक्त problem inside usb_unlink_urb since
		 * usb_unlink_urb is always racing with .complete
		 * handler(include defer_bh).
		 */
		usb_get_urb(urb);
		spin_unlock_irqrestore(&q->lock, flags);
		/* during some PM-driven resume scenarios,
		 * these (async) unlinks complete immediately
		 */
		ret = usb_unlink_urb(urb);
		अगर (ret != -EINPROGRESS && ret != 0)
			netdev_dbg(dev->net, "unlink urb err, %d\n", ret);
		अन्यथा
			count++;
		usb_put_urb(urb);
		spin_lock_irqsave(&q->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&q->lock, flags);
	वापस count;
पूर्ण

अटल पूर्णांक lan78xx_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	पूर्णांक ll_mtu = new_mtu + netdev->hard_header_len;
	पूर्णांक old_hard_mtu = dev->hard_mtu;
	पूर्णांक old_rx_urb_size = dev->rx_urb_size;

	/* no second zero-length packet पढ़ो wanted after mtu-sized packets */
	अगर ((ll_mtu % dev->maxpacket) == 0)
		वापस -गलत_तर्क;

	lan78xx_set_rx_max_frame_length(dev, new_mtu + VLAN_ETH_HLEN);

	netdev->mtu = new_mtu;

	dev->hard_mtu = netdev->mtu + netdev->hard_header_len;
	अगर (dev->rx_urb_size == old_hard_mtu) अणु
		dev->rx_urb_size = dev->hard_mtu;
		अगर (dev->rx_urb_size > old_rx_urb_size) अणु
			अगर (netअगर_running(dev->net)) अणु
				unlink_urbs(dev, &dev->rxq);
				tasklet_schedule(&dev->bh);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_set_mac_addr(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;
	u32 addr_lo, addr_hi;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ether_addr_copy(netdev->dev_addr, addr->sa_data);

	addr_lo = netdev->dev_addr[0] |
		  netdev->dev_addr[1] << 8 |
		  netdev->dev_addr[2] << 16 |
		  netdev->dev_addr[3] << 24;
	addr_hi = netdev->dev_addr[4] |
		  netdev->dev_addr[5] << 8;

	lan78xx_ग_लिखो_reg(dev, RX_ADDRL, addr_lo);
	lan78xx_ग_लिखो_reg(dev, RX_ADDRH, addr_hi);

	/* Added to support MAC address changes */
	lan78xx_ग_लिखो_reg(dev, MAF_LO(0), addr_lo);
	lan78xx_ग_लिखो_reg(dev, MAF_HI(0), addr_hi | MAF_HI_VALID_);

	वापस 0;
पूर्ण

/* Enable or disable Rx checksum offload engine */
अटल पूर्णांक lan78xx_set_features(काष्ठा net_device *netdev,
				netdev_features_t features)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->rfe_ctl_lock, flags);

	अगर (features & NETIF_F_RXCSUM) अणु
		pdata->rfe_ctl |= RFE_CTL_TCPUDP_COE_ | RFE_CTL_IP_COE_;
		pdata->rfe_ctl |= RFE_CTL_ICMP_COE_ | RFE_CTL_IGMP_COE_;
	पूर्ण अन्यथा अणु
		pdata->rfe_ctl &= ~(RFE_CTL_TCPUDP_COE_ | RFE_CTL_IP_COE_);
		pdata->rfe_ctl &= ~(RFE_CTL_ICMP_COE_ | RFE_CTL_IGMP_COE_);
	पूर्ण

	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		pdata->rfe_ctl |= RFE_CTL_VLAN_STRIP_;
	अन्यथा
		pdata->rfe_ctl &= ~RFE_CTL_VLAN_STRIP_;

	अगर (features & NETIF_F_HW_VLAN_CTAG_FILTER)
		pdata->rfe_ctl |= RFE_CTL_VLAN_FILTER_;
	अन्यथा
		pdata->rfe_ctl &= ~RFE_CTL_VLAN_FILTER_;

	spin_unlock_irqrestore(&pdata->rfe_ctl_lock, flags);

	lan78xx_ग_लिखो_reg(dev, RFE_CTL, pdata->rfe_ctl);

	वापस 0;
पूर्ण

अटल व्योम lan78xx_deferred_vlan_ग_लिखो(काष्ठा work_काष्ठा *param)
अणु
	काष्ठा lan78xx_priv *pdata =
			container_of(param, काष्ठा lan78xx_priv, set_vlan);
	काष्ठा lan78xx_net *dev = pdata->dev;

	lan78xx_dataport_ग_लिखो(dev, DP_SEL_RSEL_VLAN_DA_, 0,
			       DP_SEL_VHF_VLAN_LEN, pdata->vlan_table);
पूर्ण

अटल पूर्णांक lan78xx_vlan_rx_add_vid(काष्ठा net_device *netdev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	u16 vid_bit_index;
	u16 vid_dword_index;

	vid_dword_index = (vid >> 5) & 0x7F;
	vid_bit_index = vid & 0x1F;

	pdata->vlan_table[vid_dword_index] |= (1 << vid_bit_index);

	/* defer रेजिस्टर ग_लिखोs to a sleepable context */
	schedule_work(&pdata->set_vlan);

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(netdev);
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	u16 vid_bit_index;
	u16 vid_dword_index;

	vid_dword_index = (vid >> 5) & 0x7F;
	vid_bit_index = vid & 0x1F;

	pdata->vlan_table[vid_dword_index] &= ~(1 << vid_bit_index);

	/* defer रेजिस्टर ग_लिखोs to a sleepable context */
	schedule_work(&pdata->set_vlan);

	वापस 0;
पूर्ण

अटल व्योम lan78xx_init_lपंचांग(काष्ठा lan78xx_net *dev)
अणु
	पूर्णांक ret;
	u32 buf;
	u32 regs[6] = अणु 0 पूर्ण;

	ret = lan78xx_पढ़ो_reg(dev, USB_CFG1, &buf);
	अगर (buf & USB_CFG1_LTM_ENABLE_) अणु
		u8 temp[2];
		/* Get values from EEPROM first */
		अगर (lan78xx_पढ़ो_eeprom(dev, 0x3F, 2, temp) == 0) अणु
			अगर (temp[0] == 24) अणु
				ret = lan78xx_पढ़ो_raw_eeprom(dev,
							      temp[1] * 2,
							      24,
							      (u8 *)regs);
				अगर (ret < 0)
					वापस;
			पूर्ण
		पूर्ण अन्यथा अगर (lan78xx_पढ़ो_otp(dev, 0x3F, 2, temp) == 0) अणु
			अगर (temp[0] == 24) अणु
				ret = lan78xx_पढ़ो_raw_otp(dev,
							   temp[1] * 2,
							   24,
							   (u8 *)regs);
				अगर (ret < 0)
					वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	lan78xx_ग_लिखो_reg(dev, LTM_BELT_IDLE0, regs[0]);
	lan78xx_ग_लिखो_reg(dev, LTM_BELT_IDLE1, regs[1]);
	lan78xx_ग_लिखो_reg(dev, LTM_BELT_ACT0, regs[2]);
	lan78xx_ग_लिखो_reg(dev, LTM_BELT_ACT1, regs[3]);
	lan78xx_ग_लिखो_reg(dev, LTM_INACTIVE0, regs[4]);
	lan78xx_ग_लिखो_reg(dev, LTM_INACTIVE1, regs[5]);
पूर्ण

अटल पूर्णांक lan78xx_reset(काष्ठा lan78xx_net *dev)
अणु
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	u32 buf;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समयout;
	u8 sig;

	ret = lan78xx_पढ़ो_reg(dev, HW_CFG, &buf);
	buf |= HW_CFG_LRST_;
	ret = lan78xx_ग_लिखो_reg(dev, HW_CFG, buf);

	समयout = jअगरfies + HZ;
	करो अणु
		mdelay(1);
		ret = lan78xx_पढ़ो_reg(dev, HW_CFG, &buf);
		अगर (समय_after(jअगरfies, समयout)) अणु
			netdev_warn(dev->net,
				    "timeout on completion of LiteReset");
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक (buf & HW_CFG_LRST_);

	lan78xx_init_mac_address(dev);

	/* save DEVID क्रम later usage */
	ret = lan78xx_पढ़ो_reg(dev, ID_REV, &buf);
	dev->chipid = (buf & ID_REV_CHIP_ID_MASK_) >> 16;
	dev->chiprev = buf & ID_REV_CHIP_REV_MASK_;

	/* Respond to the IN token with a NAK */
	ret = lan78xx_पढ़ो_reg(dev, USB_CFG0, &buf);
	buf |= USB_CFG_BIR_;
	ret = lan78xx_ग_लिखो_reg(dev, USB_CFG0, buf);

	/* Init LTM */
	lan78xx_init_lपंचांग(dev);

	अगर (dev->udev->speed == USB_SPEED_SUPER) अणु
		buf = DEFAULT_BURST_CAP_SIZE / SS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_BURST_CAP_SIZE;
		dev->rx_qlen = 4;
		dev->tx_qlen = 4;
	पूर्ण अन्यथा अगर (dev->udev->speed == USB_SPEED_HIGH) अणु
		buf = DEFAULT_BURST_CAP_SIZE / HS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_BURST_CAP_SIZE;
		dev->rx_qlen = RX_MAX_QUEUE_MEMORY / dev->rx_urb_size;
		dev->tx_qlen = RX_MAX_QUEUE_MEMORY / dev->hard_mtu;
	पूर्ण अन्यथा अणु
		buf = DEFAULT_BURST_CAP_SIZE / FS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_BURST_CAP_SIZE;
		dev->rx_qlen = 4;
		dev->tx_qlen = 4;
	पूर्ण

	ret = lan78xx_ग_लिखो_reg(dev, BURST_CAP, buf);
	ret = lan78xx_ग_लिखो_reg(dev, BULK_IN_DLY, DEFAULT_BULK_IN_DELAY);

	ret = lan78xx_पढ़ो_reg(dev, HW_CFG, &buf);
	buf |= HW_CFG_MEF_;
	ret = lan78xx_ग_लिखो_reg(dev, HW_CFG, buf);

	ret = lan78xx_पढ़ो_reg(dev, USB_CFG0, &buf);
	buf |= USB_CFG_BCE_;
	ret = lan78xx_ग_लिखो_reg(dev, USB_CFG0, buf);

	/* set FIFO sizes */
	buf = (MAX_RX_FIFO_SIZE - 512) / 512;
	ret = lan78xx_ग_लिखो_reg(dev, FCT_RX_FIFO_END, buf);

	buf = (MAX_TX_FIFO_SIZE - 512) / 512;
	ret = lan78xx_ग_लिखो_reg(dev, FCT_TX_FIFO_END, buf);

	ret = lan78xx_ग_लिखो_reg(dev, INT_STS, INT_STS_CLEAR_ALL_);
	ret = lan78xx_ग_लिखो_reg(dev, FLOW, 0);
	ret = lan78xx_ग_लिखो_reg(dev, FCT_FLOW, 0);

	/* Don't need rfe_ctl_lock during initialisation */
	ret = lan78xx_पढ़ो_reg(dev, RFE_CTL, &pdata->rfe_ctl);
	pdata->rfe_ctl |= RFE_CTL_BCAST_EN_ | RFE_CTL_DA_PERFECT_;
	ret = lan78xx_ग_लिखो_reg(dev, RFE_CTL, pdata->rfe_ctl);

	/* Enable or disable checksum offload engines */
	lan78xx_set_features(dev->net, dev->net->features);

	lan78xx_set_multicast(dev->net);

	/* reset PHY */
	ret = lan78xx_पढ़ो_reg(dev, PMT_CTL, &buf);
	buf |= PMT_CTL_PHY_RST_;
	ret = lan78xx_ग_लिखो_reg(dev, PMT_CTL, buf);

	समयout = jअगरfies + HZ;
	करो अणु
		mdelay(1);
		ret = lan78xx_पढ़ो_reg(dev, PMT_CTL, &buf);
		अगर (समय_after(jअगरfies, समयout)) अणु
			netdev_warn(dev->net, "timeout waiting for PHY Reset");
			वापस -EIO;
		पूर्ण
	पूर्ण जबतक ((buf & PMT_CTL_PHY_RST_) || !(buf & PMT_CTL_READY_));

	ret = lan78xx_पढ़ो_reg(dev, MAC_CR, &buf);
	/* LAN7801 only has RGMII mode */
	अगर (dev->chipid == ID_REV_CHIP_ID_7801_)
		buf &= ~MAC_CR_GMII_EN_;

	अगर (dev->chipid == ID_REV_CHIP_ID_7800_) अणु
		ret = lan78xx_पढ़ो_raw_eeprom(dev, 0, 1, &sig);
		अगर (!ret && sig != EEPROM_INDICATOR) अणु
			/* Implies there is no बाह्यal eeprom. Set mac speed */
			netdev_info(dev->net, "No External EEPROM. Setting MAC Speed\n");
			buf |= MAC_CR_AUTO_DUPLEX_ | MAC_CR_AUTO_SPEED_;
		पूर्ण
	पूर्ण
	ret = lan78xx_ग_लिखो_reg(dev, MAC_CR, buf);

	ret = lan78xx_पढ़ो_reg(dev, MAC_TX, &buf);
	buf |= MAC_TX_TXEN_;
	ret = lan78xx_ग_लिखो_reg(dev, MAC_TX, buf);

	ret = lan78xx_पढ़ो_reg(dev, FCT_TX_CTL, &buf);
	buf |= FCT_TX_CTL_EN_;
	ret = lan78xx_ग_लिखो_reg(dev, FCT_TX_CTL, buf);

	ret = lan78xx_set_rx_max_frame_length(dev,
					      dev->net->mtu + VLAN_ETH_HLEN);

	ret = lan78xx_पढ़ो_reg(dev, MAC_RX, &buf);
	buf |= MAC_RX_RXEN_;
	ret = lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);

	ret = lan78xx_पढ़ो_reg(dev, FCT_RX_CTL, &buf);
	buf |= FCT_RX_CTL_EN_;
	ret = lan78xx_ग_लिखो_reg(dev, FCT_RX_CTL, buf);

	वापस 0;
पूर्ण

अटल व्योम lan78xx_init_stats(काष्ठा lan78xx_net *dev)
अणु
	u32 *p;
	पूर्णांक i;

	/* initialize क्रम stats update
	 * some counters are 20bits and some are 32bits
	 */
	p = (u32 *)&dev->stats.rollover_max;
	क्रम (i = 0; i < (माप(dev->stats.rollover_max) / (माप(u32))); i++)
		p[i] = 0xFFFFF;

	dev->stats.rollover_max.rx_unicast_byte_count = 0xFFFFFFFF;
	dev->stats.rollover_max.rx_broadcast_byte_count = 0xFFFFFFFF;
	dev->stats.rollover_max.rx_multicast_byte_count = 0xFFFFFFFF;
	dev->stats.rollover_max.eee_rx_lpi_transitions = 0xFFFFFFFF;
	dev->stats.rollover_max.eee_rx_lpi_समय = 0xFFFFFFFF;
	dev->stats.rollover_max.tx_unicast_byte_count = 0xFFFFFFFF;
	dev->stats.rollover_max.tx_broadcast_byte_count = 0xFFFFFFFF;
	dev->stats.rollover_max.tx_multicast_byte_count = 0xFFFFFFFF;
	dev->stats.rollover_max.eee_tx_lpi_transitions = 0xFFFFFFFF;
	dev->stats.rollover_max.eee_tx_lpi_समय = 0xFFFFFFFF;

	set_bit(EVENT_STAT_UPDATE, &dev->flags);
पूर्ण

अटल पूर्णांक lan78xx_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	पूर्णांक ret;

	ret = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (ret < 0)
		जाओ out;

	phy_start(net->phydev);

	netअगर_dbg(dev, अगरup, dev->net, "phy initialised successfully");

	/* क्रम Link Check */
	अगर (dev->urb_पूर्णांकr) अणु
		ret = usb_submit_urb(dev->urb_पूर्णांकr, GFP_KERNEL);
		अगर (ret < 0) अणु
			netअगर_err(dev, अगरup, dev->net,
				  "intr submit %d\n", ret);
			जाओ करोne;
		पूर्ण
	पूर्ण

	lan78xx_init_stats(dev);

	set_bit(EVENT_DEV_OPEN, &dev->flags);

	netअगर_start_queue(net);

	dev->link_on = false;

	lan78xx_defer_kevent(dev, EVENT_LINK_RESET);
करोne:
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

out:
	वापस ret;
पूर्ण

अटल व्योम lan78xx_terminate_urbs(काष्ठा lan78xx_net *dev)
अणु
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(unlink_wakeup);
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक temp;

	/* ensure there are no more active urbs */
	add_रुको_queue(&unlink_wakeup, &रुको);
	set_current_state(TASK_UNINTERRUPTIBLE);
	dev->रुको = &unlink_wakeup;
	temp = unlink_urbs(dev, &dev->txq) + unlink_urbs(dev, &dev->rxq);

	/* maybe रुको क्रम deletions to finish. */
	जबतक (!skb_queue_empty(&dev->rxq) &&
	       !skb_queue_empty(&dev->txq) &&
	       !skb_queue_empty(&dev->करोne)) अणु
		schedule_समयout(msecs_to_jअगरfies(UNLINK_TIMEOUT_MS));
		set_current_state(TASK_UNINTERRUPTIBLE);
		netअगर_dbg(dev, अगरकरोwn, dev->net,
			  "waited for %d urb completions\n", temp);
	पूर्ण
	set_current_state(TASK_RUNNING);
	dev->रुको = शून्य;
	हटाओ_रुको_queue(&unlink_wakeup, &रुको);
पूर्ण

अटल पूर्णांक lan78xx_stop(काष्ठा net_device *net)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);

	अगर (समयr_pending(&dev->stat_monitor))
		del_समयr_sync(&dev->stat_monitor);

	अगर (net->phydev)
		phy_stop(net->phydev);

	clear_bit(EVENT_DEV_OPEN, &dev->flags);
	netअगर_stop_queue(net);

	netअगर_info(dev, अगरकरोwn, dev->net,
		   "stop stats: rx/tx %lu/%lu, errs %lu/%lu\n",
		   net->stats.rx_packets, net->stats.tx_packets,
		   net->stats.rx_errors, net->stats.tx_errors);

	lan78xx_terminate_urbs(dev);

	usb_समाप्त_urb(dev->urb_पूर्णांकr);

	skb_queue_purge(&dev->rxq_छोड़ो);

	/* deferred work (task, समयr, softirq) must also stop.
	 * can't flush_scheduled_work() until we drop rtnl (later),
	 * अन्यथा workers could deadlock; so make workers a NOP.
	 */
	dev->flags = 0;
	cancel_delayed_work_sync(&dev->wq);
	tasklet_समाप्त(&dev->bh);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *lan78xx_tx_prep(काष्ठा lan78xx_net *dev,
				       काष्ठा sk_buff *skb, gfp_t flags)
अणु
	u32 tx_cmd_a, tx_cmd_b;
	व्योम *ptr;

	अगर (skb_cow_head(skb, TX_OVERHEAD)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	अगर (skb_linearize(skb)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	tx_cmd_a = (u32)(skb->len & TX_CMD_A_LEN_MASK_) | TX_CMD_A_FCS_;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		tx_cmd_a |= TX_CMD_A_IPE_ | TX_CMD_A_TPE_;

	tx_cmd_b = 0;
	अगर (skb_is_gso(skb)) अणु
		u16 mss = max(skb_shinfo(skb)->gso_size, TX_CMD_B_MSS_MIN_);

		tx_cmd_b = (mss << TX_CMD_B_MSS_SHIFT_) & TX_CMD_B_MSS_MASK_;

		tx_cmd_a |= TX_CMD_A_LSO_;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_cmd_a |= TX_CMD_A_IVTG_;
		tx_cmd_b |= skb_vlan_tag_get(skb) & TX_CMD_B_VTAG_MASK_;
	पूर्ण

	ptr = skb_push(skb, 8);
	put_unaligned_le32(tx_cmd_a, ptr);
	put_unaligned_le32(tx_cmd_b, ptr + 4);

	वापस skb;
पूर्ण

अटल क्रमागत skb_state defer_bh(काष्ठा lan78xx_net *dev, काष्ठा sk_buff *skb,
			       काष्ठा sk_buff_head *list, क्रमागत skb_state state)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत skb_state old_state;
	काष्ठा skb_data *entry = (काष्ठा skb_data *)skb->cb;

	spin_lock_irqsave(&list->lock, flags);
	old_state = entry->state;
	entry->state = state;

	__skb_unlink(skb, list);
	spin_unlock(&list->lock);
	spin_lock(&dev->करोne.lock);

	__skb_queue_tail(&dev->करोne, skb);
	अगर (skb_queue_len(&dev->करोne) == 1)
		tasklet_schedule(&dev->bh);
	spin_unlock_irqrestore(&dev->करोne.lock, flags);

	वापस old_state;
पूर्ण

अटल व्योम tx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा skb_data *entry = (काष्ठा skb_data *)skb->cb;
	काष्ठा lan78xx_net *dev = entry->dev;

	अगर (urb->status == 0) अणु
		dev->net->stats.tx_packets += entry->num_of_packet;
		dev->net->stats.tx_bytes += entry->length;
	पूर्ण अन्यथा अणु
		dev->net->stats.tx_errors++;

		चयन (urb->status) अणु
		हाल -EPIPE:
			lan78xx_defer_kevent(dev, EVENT_TX_HALT);
			अवरोध;

		/* software-driven पूर्णांकerface shutकरोwn */
		हाल -ECONNRESET:
		हाल -ESHUTDOWN:
			अवरोध;

		हाल -EPROTO:
		हाल -ETIME:
		हाल -EILSEQ:
			netअगर_stop_queue(dev->net);
			अवरोध;
		शेष:
			netअगर_dbg(dev, tx_err, dev->net,
				  "tx err %d\n", entry->urb->status);
			अवरोध;
		पूर्ण
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);

	defer_bh(dev, skb, &dev->txq, tx_करोne);
पूर्ण

अटल व्योम lan78xx_queue_skb(काष्ठा sk_buff_head *list,
			      काष्ठा sk_buff *newsk, क्रमागत skb_state state)
अणु
	काष्ठा skb_data *entry = (काष्ठा skb_data *)newsk->cb;

	__skb_queue_tail(list, newsk);
	entry->state = state;
पूर्ण

अटल netdev_tx_t
lan78xx_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *net)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);
	काष्ठा sk_buff *skb2 = शून्य;

	अगर (skb) अणु
		skb_tx_बारtamp(skb);
		skb2 = lan78xx_tx_prep(dev, skb, GFP_ATOMIC);
	पूर्ण

	अगर (skb2) अणु
		skb_queue_tail(&dev->txq_pend, skb2);

		/* throttle TX patch at slower than SUPER SPEED USB */
		अगर ((dev->udev->speed < USB_SPEED_SUPER) &&
		    (skb_queue_len(&dev->txq_pend) > 10))
			netअगर_stop_queue(net);
	पूर्ण अन्यथा अणु
		netअगर_dbg(dev, tx_err, dev->net,
			  "lan78xx_tx_prep return NULL\n");
		dev->net->stats.tx_errors++;
		dev->net->stats.tx_dropped++;
	पूर्ण

	tasklet_schedule(&dev->bh);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक lan78xx_bind(काष्ठा lan78xx_net *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा lan78xx_priv *pdata = शून्य;
	पूर्णांक ret;
	पूर्णांक i;

	dev->data[0] = (अचिन्हित दीर्घ)kzalloc(माप(*pdata), GFP_KERNEL);

	pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	अगर (!pdata) अणु
		netdev_warn(dev->net, "Unable to allocate lan78xx_priv");
		वापस -ENOMEM;
	पूर्ण

	pdata->dev = dev;

	spin_lock_init(&pdata->rfe_ctl_lock);
	mutex_init(&pdata->dataport_mutex);

	INIT_WORK(&pdata->set_multicast, lan78xx_deferred_multicast_ग_लिखो);

	क्रम (i = 0; i < DP_SEL_VHF_VLAN_LEN; i++)
		pdata->vlan_table[i] = 0;

	INIT_WORK(&pdata->set_vlan, lan78xx_deferred_vlan_ग_लिखो);

	dev->net->features = 0;

	अगर (DEFAULT_TX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_HW_CSUM;

	अगर (DEFAULT_RX_CSUM_ENABLE)
		dev->net->features |= NETIF_F_RXCSUM;

	अगर (DEFAULT_TSO_CSUM_ENABLE)
		dev->net->features |= NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_SG;

	अगर (DEFAULT_VLAN_RX_OFFLOAD)
		dev->net->features |= NETIF_F_HW_VLAN_CTAG_RX;

	अगर (DEFAULT_VLAN_FILTER_ENABLE)
		dev->net->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	dev->net->hw_features = dev->net->features;

	ret = lan78xx_setup_irq_करोमुख्य(dev);
	अगर (ret < 0) अणु
		netdev_warn(dev->net,
			    "lan78xx_setup_irq_domain() failed : %d", ret);
		जाओ out1;
	पूर्ण

	dev->net->hard_header_len += TX_OVERHEAD;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;

	/* Init all रेजिस्टरs */
	ret = lan78xx_reset(dev);
	अगर (ret) अणु
		netdev_warn(dev->net, "Registers INIT FAILED....");
		जाओ out2;
	पूर्ण

	ret = lan78xx_mdio_init(dev);
	अगर (ret) अणु
		netdev_warn(dev->net, "MDIO INIT FAILED.....");
		जाओ out2;
	पूर्ण

	dev->net->flags |= IFF_MULTICAST;

	pdata->wol = WAKE_MAGIC;

	वापस ret;

out2:
	lan78xx_हटाओ_irq_करोमुख्य(dev);

out1:
	netdev_warn(dev->net, "Bind routine FAILED");
	cancel_work_sync(&pdata->set_multicast);
	cancel_work_sync(&pdata->set_vlan);
	kमुक्त(pdata);
	वापस ret;
पूर्ण

अटल व्योम lan78xx_unbind(काष्ठा lan78xx_net *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);

	lan78xx_हटाओ_irq_करोमुख्य(dev);

	lan78xx_हटाओ_mdio(dev);

	अगर (pdata) अणु
		cancel_work_sync(&pdata->set_multicast);
		cancel_work_sync(&pdata->set_vlan);
		netअगर_dbg(dev, अगरकरोwn, dev->net, "free pdata");
		kमुक्त(pdata);
		pdata = शून्य;
		dev->data[0] = 0;
	पूर्ण
पूर्ण

अटल व्योम lan78xx_rx_csum_offload(काष्ठा lan78xx_net *dev,
				    काष्ठा sk_buff *skb,
				    u32 rx_cmd_a, u32 rx_cmd_b)
अणु
	/* HW Checksum offload appears to be flawed अगर used when not stripping
	 * VLAN headers. Drop back to S/W checksums under these conditions.
	 */
	अगर (!(dev->net->features & NETIF_F_RXCSUM) ||
	    unlikely(rx_cmd_a & RX_CMD_A_ICSM_) ||
	    ((rx_cmd_a & RX_CMD_A_FVTG_) &&
	     !(dev->net->features & NETIF_F_HW_VLAN_CTAG_RX))) अणु
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण अन्यथा अणु
		skb->csum = ntohs((u16)(rx_cmd_b >> RX_CMD_B_CSUM_SHIFT_));
		skb->ip_summed = CHECKSUM_COMPLETE;
	पूर्ण
पूर्ण

अटल व्योम lan78xx_rx_vlan_offload(काष्ठा lan78xx_net *dev,
				    काष्ठा sk_buff *skb,
				    u32 rx_cmd_a, u32 rx_cmd_b)
अणु
	अगर ((dev->net->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    (rx_cmd_a & RX_CMD_A_FVTG_))
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       (rx_cmd_b & 0xffff));
पूर्ण

अटल व्योम lan78xx_skb_वापस(काष्ठा lan78xx_net *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक status;

	अगर (test_bit(EVENT_RX_PAUSED, &dev->flags)) अणु
		skb_queue_tail(&dev->rxq_छोड़ो, skb);
		वापस;
	पूर्ण

	dev->net->stats.rx_packets++;
	dev->net->stats.rx_bytes += skb->len;

	skb->protocol = eth_type_trans(skb, dev->net);

	netअगर_dbg(dev, rx_status, dev->net, "< rx, len %zu, type 0x%x\n",
		  skb->len + माप(काष्ठा ethhdr), skb->protocol);
	स_रखो(skb->cb, 0, माप(काष्ठा skb_data));

	अगर (skb_defer_rx_बारtamp(skb))
		वापस;

	status = netअगर_rx(skb);
	अगर (status != NET_RX_SUCCESS)
		netअगर_dbg(dev, rx_err, dev->net,
			  "netif_rx status %d\n", status);
पूर्ण

अटल पूर्णांक lan78xx_rx(काष्ठा lan78xx_net *dev, काष्ठा sk_buff *skb)
अणु
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	जबतक (skb->len > 0) अणु
		u32 rx_cmd_a, rx_cmd_b, align_count, size;
		u16 rx_cmd_c;
		काष्ठा sk_buff *skb2;
		अचिन्हित अक्षर *packet;

		rx_cmd_a = get_unaligned_le32(skb->data);
		skb_pull(skb, माप(rx_cmd_a));

		rx_cmd_b = get_unaligned_le32(skb->data);
		skb_pull(skb, माप(rx_cmd_b));

		rx_cmd_c = get_unaligned_le16(skb->data);
		skb_pull(skb, माप(rx_cmd_c));

		packet = skb->data;

		/* get the packet length */
		size = (rx_cmd_a & RX_CMD_A_LEN_MASK_);
		align_count = (4 - ((size + RXW_PADDING) % 4)) % 4;

		अगर (unlikely(rx_cmd_a & RX_CMD_A_RED_)) अणु
			netअगर_dbg(dev, rx_err, dev->net,
				  "Error rx_cmd_a=0x%08x", rx_cmd_a);
		पूर्ण अन्यथा अणु
			/* last frame in this batch */
			अगर (skb->len == size) अणु
				lan78xx_rx_csum_offload(dev, skb,
							rx_cmd_a, rx_cmd_b);
				lan78xx_rx_vlan_offload(dev, skb,
							rx_cmd_a, rx_cmd_b);

				skb_trim(skb, skb->len - 4); /* हटाओ fcs */
				skb->truesize = size + माप(काष्ठा sk_buff);

				वापस 1;
			पूर्ण

			skb2 = skb_clone(skb, GFP_ATOMIC);
			अगर (unlikely(!skb2)) अणु
				netdev_warn(dev->net, "Error allocating skb");
				वापस 0;
			पूर्ण

			skb2->len = size;
			skb2->data = packet;
			skb_set_tail_poपूर्णांकer(skb2, size);

			lan78xx_rx_csum_offload(dev, skb2, rx_cmd_a, rx_cmd_b);
			lan78xx_rx_vlan_offload(dev, skb2, rx_cmd_a, rx_cmd_b);

			skb_trim(skb2, skb2->len - 4); /* हटाओ fcs */
			skb2->truesize = size + माप(काष्ठा sk_buff);

			lan78xx_skb_वापस(dev, skb2);
		पूर्ण

		skb_pull(skb, size);

		/* padding bytes beक्रमe the next frame starts */
		अगर (skb->len)
			skb_pull(skb, align_count);
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत व्योम rx_process(काष्ठा lan78xx_net *dev, काष्ठा sk_buff *skb)
अणु
	अगर (!lan78xx_rx(dev, skb)) अणु
		dev->net->stats.rx_errors++;
		जाओ करोne;
	पूर्ण

	अगर (skb->len) अणु
		lan78xx_skb_वापस(dev, skb);
		वापस;
	पूर्ण

	netअगर_dbg(dev, rx_err, dev->net, "drop\n");
	dev->net->stats.rx_errors++;
करोne:
	skb_queue_tail(&dev->करोne, skb);
पूर्ण

अटल व्योम rx_complete(काष्ठा urb *urb);

अटल पूर्णांक rx_submit(काष्ठा lan78xx_net *dev, काष्ठा urb *urb, gfp_t flags)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा skb_data *entry;
	अचिन्हित दीर्घ lockflags;
	माप_प्रकार size = dev->rx_urb_size;
	पूर्णांक ret = 0;

	skb = netdev_alloc_skb_ip_align(dev->net, size);
	अगर (!skb) अणु
		usb_मुक्त_urb(urb);
		वापस -ENOMEM;
	पूर्ण

	entry = (काष्ठा skb_data *)skb->cb;
	entry->urb = urb;
	entry->dev = dev;
	entry->length = 0;

	usb_fill_bulk_urb(urb, dev->udev, dev->pipe_in,
			  skb->data, size, rx_complete, skb);

	spin_lock_irqsave(&dev->rxq.lock, lockflags);

	अगर (netअगर_device_present(dev->net) &&
	    netअगर_running(dev->net) &&
	    !test_bit(EVENT_RX_HALT, &dev->flags) &&
	    !test_bit(EVENT_DEV_ASLEEP, &dev->flags)) अणु
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		चयन (ret) अणु
		हाल 0:
			lan78xx_queue_skb(&dev->rxq, skb, rx_start);
			अवरोध;
		हाल -EPIPE:
			lan78xx_defer_kevent(dev, EVENT_RX_HALT);
			अवरोध;
		हाल -ENODEV:
			netअगर_dbg(dev, अगरकरोwn, dev->net, "device gone\n");
			netअगर_device_detach(dev->net);
			अवरोध;
		हाल -EHOSTUNREACH:
			ret = -ENOLINK;
			अवरोध;
		शेष:
			netअगर_dbg(dev, rx_err, dev->net,
				  "rx submit, %d\n", ret);
			tasklet_schedule(&dev->bh);
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_dbg(dev, अगरकरोwn, dev->net, "rx: stopped\n");
		ret = -ENOLINK;
	पूर्ण
	spin_unlock_irqrestore(&dev->rxq.lock, lockflags);
	अगर (ret) अणु
		dev_kमुक्त_skb_any(skb);
		usb_मुक्त_urb(urb);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rx_complete(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff	*skb = (काष्ठा sk_buff *)urb->context;
	काष्ठा skb_data	*entry = (काष्ठा skb_data *)skb->cb;
	काष्ठा lan78xx_net *dev = entry->dev;
	पूर्णांक urb_status = urb->status;
	क्रमागत skb_state state;

	skb_put(skb, urb->actual_length);
	state = rx_करोne;
	entry->urb = शून्य;

	चयन (urb_status) अणु
	हाल 0:
		अगर (skb->len < dev->net->hard_header_len) अणु
			state = rx_cleanup;
			dev->net->stats.rx_errors++;
			dev->net->stats.rx_length_errors++;
			netअगर_dbg(dev, rx_err, dev->net,
				  "rx length %d\n", skb->len);
		पूर्ण
		usb_mark_last_busy(dev->udev);
		अवरोध;
	हाल -EPIPE:
		dev->net->stats.rx_errors++;
		lan78xx_defer_kevent(dev, EVENT_RX_HALT);
		fallthrough;
	हाल -ECONNRESET:				/* async unlink */
	हाल -ESHUTDOWN:				/* hardware gone */
		netअगर_dbg(dev, अगरकरोwn, dev->net,
			  "rx shutdown, code %d\n", urb_status);
		state = rx_cleanup;
		entry->urb = urb;
		urb = शून्य;
		अवरोध;
	हाल -EPROTO:
	हाल -ETIME:
	हाल -EILSEQ:
		dev->net->stats.rx_errors++;
		state = rx_cleanup;
		entry->urb = urb;
		urb = शून्य;
		अवरोध;

	/* data overrun ... flush fअगरo? */
	हाल -EOVERFLOW:
		dev->net->stats.rx_over_errors++;
		fallthrough;

	शेष:
		state = rx_cleanup;
		dev->net->stats.rx_errors++;
		netअगर_dbg(dev, rx_err, dev->net, "rx status %d\n", urb_status);
		अवरोध;
	पूर्ण

	state = defer_bh(dev, skb, &dev->rxq, state);

	अगर (urb) अणु
		अगर (netअगर_running(dev->net) &&
		    !test_bit(EVENT_RX_HALT, &dev->flags) &&
		    state != unlink_start) अणु
			rx_submit(dev, urb, GFP_ATOMIC);
			वापस;
		पूर्ण
		usb_मुक्त_urb(urb);
	पूर्ण
	netअगर_dbg(dev, rx_err, dev->net, "no read resubmitted\n");
पूर्ण

अटल व्योम lan78xx_tx_bh(काष्ठा lan78xx_net *dev)
अणु
	पूर्णांक length;
	काष्ठा urb *urb = शून्य;
	काष्ठा skb_data *entry;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff_head *tqp = &dev->txq_pend;
	काष्ठा sk_buff *skb, *skb2;
	पूर्णांक ret;
	पूर्णांक count, pos;
	पूर्णांक skb_totallen, pkt_cnt;

	skb_totallen = 0;
	pkt_cnt = 0;
	count = 0;
	length = 0;
	spin_lock_irqsave(&tqp->lock, flags);
	skb_queue_walk(tqp, skb) अणु
		अगर (skb_is_gso(skb)) अणु
			अगर (!skb_queue_is_first(tqp, skb)) अणु
				/* handle previous packets first */
				अवरोध;
			पूर्ण
			count = 1;
			length = skb->len - TX_OVERHEAD;
			__skb_unlink(skb, tqp);
			spin_unlock_irqrestore(&tqp->lock, flags);
			जाओ gso_skb;
		पूर्ण

		अगर ((skb_totallen + skb->len) > MAX_SINGLE_PACKET_SIZE)
			अवरोध;
		skb_totallen = skb->len + roundup(skb_totallen, माप(u32));
		pkt_cnt++;
	पूर्ण
	spin_unlock_irqrestore(&tqp->lock, flags);

	/* copy to a single skb */
	skb = alloc_skb(skb_totallen, GFP_ATOMIC);
	अगर (!skb)
		जाओ drop;

	skb_put(skb, skb_totallen);

	क्रम (count = pos = 0; count < pkt_cnt; count++) अणु
		skb2 = skb_dequeue(tqp);
		अगर (skb2) अणु
			length += (skb2->len - TX_OVERHEAD);
			स_नकल(skb->data + pos, skb2->data, skb2->len);
			pos += roundup(skb2->len, माप(u32));
			dev_kमुक्त_skb(skb2);
		पूर्ण
	पूर्ण

gso_skb:
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!urb)
		जाओ drop;

	entry = (काष्ठा skb_data *)skb->cb;
	entry->urb = urb;
	entry->dev = dev;
	entry->length = length;
	entry->num_of_packet = count;

	spin_lock_irqsave(&dev->txq.lock, flags);
	ret = usb_स्वतःpm_get_पूर्णांकerface_async(dev->पूर्णांकf);
	अगर (ret < 0) अणु
		spin_unlock_irqrestore(&dev->txq.lock, flags);
		जाओ drop;
	पूर्ण

	usb_fill_bulk_urb(urb, dev->udev, dev->pipe_out,
			  skb->data, skb->len, tx_complete, skb);

	अगर (length % dev->maxpacket == 0) अणु
		/* send USB_ZERO_PACKET */
		urb->transfer_flags |= URB_ZERO_PACKET;
	पूर्ण

#अगर_घोषित CONFIG_PM
	/* अगर this triggers the device is still a sleep */
	अगर (test_bit(EVENT_DEV_ASLEEP, &dev->flags)) अणु
		/* transmission will be करोne in resume */
		usb_anchor_urb(urb, &dev->deferred);
		/* no use to process more packets */
		netअगर_stop_queue(dev->net);
		usb_put_urb(urb);
		spin_unlock_irqrestore(&dev->txq.lock, flags);
		netdev_dbg(dev->net, "Delaying transmission for resumption\n");
		वापस;
	पूर्ण
#पूर्ण_अगर

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	चयन (ret) अणु
	हाल 0:
		netअगर_trans_update(dev->net);
		lan78xx_queue_skb(&dev->txq, skb, tx_start);
		अगर (skb_queue_len(&dev->txq) >= dev->tx_qlen)
			netअगर_stop_queue(dev->net);
		अवरोध;
	हाल -EPIPE:
		netअगर_stop_queue(dev->net);
		lan78xx_defer_kevent(dev, EVENT_TX_HALT);
		usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
		अवरोध;
	शेष:
		usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
		netअगर_dbg(dev, tx_err, dev->net,
			  "tx: submit urb err %d\n", ret);
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&dev->txq.lock, flags);

	अगर (ret) अणु
		netअगर_dbg(dev, tx_err, dev->net, "drop, code %d\n", ret);
drop:
		dev->net->stats.tx_dropped++;
		अगर (skb)
			dev_kमुक्त_skb_any(skb);
		usb_मुक्त_urb(urb);
	पूर्ण अन्यथा
		netअगर_dbg(dev, tx_queued, dev->net,
			  "> tx, len %d, type 0x%x\n", length, skb->protocol);
पूर्ण

अटल व्योम lan78xx_rx_bh(काष्ठा lan78xx_net *dev)
अणु
	काष्ठा urb *urb;
	पूर्णांक i;

	अगर (skb_queue_len(&dev->rxq) < dev->rx_qlen) अणु
		क्रम (i = 0; i < 10; i++) अणु
			अगर (skb_queue_len(&dev->rxq) >= dev->rx_qlen)
				अवरोध;
			urb = usb_alloc_urb(0, GFP_ATOMIC);
			अगर (urb)
				अगर (rx_submit(dev, urb, GFP_ATOMIC) == -ENOLINK)
					वापस;
		पूर्ण

		अगर (skb_queue_len(&dev->rxq) < dev->rx_qlen)
			tasklet_schedule(&dev->bh);
	पूर्ण
	अगर (skb_queue_len(&dev->txq) < dev->tx_qlen)
		netअगर_wake_queue(dev->net);
पूर्ण

अटल व्योम lan78xx_bh(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा lan78xx_net *dev = from_tasklet(dev, t, bh);
	काष्ठा sk_buff *skb;
	काष्ठा skb_data *entry;

	जबतक ((skb = skb_dequeue(&dev->करोne))) अणु
		entry = (काष्ठा skb_data *)(skb->cb);
		चयन (entry->state) अणु
		हाल rx_करोne:
			entry->state = rx_cleanup;
			rx_process(dev, skb);
			जारी;
		हाल tx_करोne:
			usb_मुक्त_urb(entry->urb);
			dev_kमुक्त_skb(skb);
			जारी;
		हाल rx_cleanup:
			usb_मुक्त_urb(entry->urb);
			dev_kमुक्त_skb(skb);
			जारी;
		शेष:
			netdev_dbg(dev->net, "skb state %d\n", entry->state);
			वापस;
		पूर्ण
	पूर्ण

	अगर (netअगर_device_present(dev->net) && netअगर_running(dev->net)) अणु
		/* reset update समयr delta */
		अगर (समयr_pending(&dev->stat_monitor) && (dev->delta != 1)) अणु
			dev->delta = 1;
			mod_समयr(&dev->stat_monitor,
				  jअगरfies + STAT_UPDATE_TIMER);
		पूर्ण

		अगर (!skb_queue_empty(&dev->txq_pend))
			lan78xx_tx_bh(dev);

		अगर (!समयr_pending(&dev->delay) &&
		    !test_bit(EVENT_RX_HALT, &dev->flags))
			lan78xx_rx_bh(dev);
	पूर्ण
पूर्ण

अटल व्योम lan78xx_delayedwork(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक status;
	काष्ठा lan78xx_net *dev;

	dev = container_of(work, काष्ठा lan78xx_net, wq.work);

	अगर (test_bit(EVENT_TX_HALT, &dev->flags)) अणु
		unlink_urbs(dev, &dev->txq);
		status = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0)
			जाओ fail_pipe;
		status = usb_clear_halt(dev->udev, dev->pipe_out);
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0 &&
		    status != -EPIPE &&
		    status != -ESHUTDOWN) अणु
			अगर (netअगर_msg_tx_err(dev))
fail_pipe:
				netdev_err(dev->net,
					   "can't clear tx halt, status %d\n",
					   status);
		पूर्ण अन्यथा अणु
			clear_bit(EVENT_TX_HALT, &dev->flags);
			अगर (status != -ESHUTDOWN)
				netअगर_wake_queue(dev->net);
		पूर्ण
	पूर्ण
	अगर (test_bit(EVENT_RX_HALT, &dev->flags)) अणु
		unlink_urbs(dev, &dev->rxq);
		status = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0)
				जाओ fail_halt;
		status = usb_clear_halt(dev->udev, dev->pipe_in);
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0 &&
		    status != -EPIPE &&
		    status != -ESHUTDOWN) अणु
			अगर (netअगर_msg_rx_err(dev))
fail_halt:
				netdev_err(dev->net,
					   "can't clear rx halt, status %d\n",
					   status);
		पूर्ण अन्यथा अणु
			clear_bit(EVENT_RX_HALT, &dev->flags);
			tasklet_schedule(&dev->bh);
		पूर्ण
	पूर्ण

	अगर (test_bit(EVENT_LINK_RESET, &dev->flags)) अणु
		पूर्णांक ret = 0;

		clear_bit(EVENT_LINK_RESET, &dev->flags);
		status = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
		अगर (status < 0)
			जाओ skip_reset;
		अगर (lan78xx_link_reset(dev) < 0) अणु
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
skip_reset:
			netdev_info(dev->net, "link reset failed (%d)\n",
				    ret);
		पूर्ण अन्यथा अणु
			usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
		पूर्ण
	पूर्ण

	अगर (test_bit(EVENT_STAT_UPDATE, &dev->flags)) अणु
		lan78xx_update_stats(dev);

		clear_bit(EVENT_STAT_UPDATE, &dev->flags);

		mod_समयr(&dev->stat_monitor,
			  jअगरfies + (STAT_UPDATE_TIMER * dev->delta));

		dev->delta = min((dev->delta * 2), 50);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकr_complete(काष्ठा urb *urb)
अणु
	काष्ठा lan78xx_net *dev = urb->context;
	पूर्णांक status = urb->status;

	चयन (status) अणु
	/* success */
	हाल 0:
		lan78xx_status(dev, urb);
		अवरोध;

	/* software-driven पूर्णांकerface shutकरोwn */
	हाल -ENOENT:			/* urb समाप्तed */
	हाल -ESHUTDOWN:		/* hardware gone */
		netअगर_dbg(dev, अगरकरोwn, dev->net,
			  "intr shutdown, code %d\n", status);
		वापस;

	/* NOTE:  not throttling like RX/TX, since this endpoपूर्णांक
	 * alपढ़ोy polls infrequently
	 */
	शेष:
		netdev_dbg(dev->net, "intr status %d\n", status);
		अवरोध;
	पूर्ण

	अगर (!netअगर_running(dev->net))
		वापस;

	स_रखो(urb->transfer_buffer, 0, urb->transfer_buffer_length);
	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status != 0)
		netअगर_err(dev, समयr, dev->net,
			  "intr resubmit --> %d\n", status);
पूर्ण

अटल व्योम lan78xx_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा lan78xx_net *dev;
	काष्ठा usb_device *udev;
	काष्ठा net_device *net;
	काष्ठा phy_device *phydev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (!dev)
		वापस;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	net = dev->net;
	phydev = net->phydev;

	phy_unरेजिस्टर_fixup_क्रम_uid(PHY_KSZ9031RNX, 0xfffffff0);
	phy_unरेजिस्टर_fixup_क्रम_uid(PHY_LAN8835, 0xfffffff0);

	phy_disconnect(net->phydev);

	अगर (phy_is_pseuकरो_fixed_link(phydev))
		fixed_phy_unरेजिस्टर(phydev);

	unरेजिस्टर_netdev(net);

	cancel_delayed_work_sync(&dev->wq);

	usb_scuttle_anchored_urbs(&dev->deferred);

	lan78xx_unbind(dev, पूर्णांकf);

	usb_समाप्त_urb(dev->urb_पूर्णांकr);
	usb_मुक्त_urb(dev->urb_पूर्णांकr);

	मुक्त_netdev(net);
	usb_put_dev(udev);
पूर्ण

अटल व्योम lan78xx_tx_समयout(काष्ठा net_device *net, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा lan78xx_net *dev = netdev_priv(net);

	unlink_urbs(dev, &dev->txq);
	tasklet_schedule(&dev->bh);
पूर्ण

अटल netdev_features_t lan78xx_features_check(काष्ठा sk_buff *skb,
						काष्ठा net_device *netdev,
						netdev_features_t features)
अणु
	अगर (skb->len + TX_OVERHEAD > MAX_SINGLE_PACKET_SIZE)
		features &= ~NETIF_F_GSO_MASK;

	features = vlan_features_check(skb, features);
	features = vxlan_features_check(skb, features);

	वापस features;
पूर्ण

अटल स्थिर काष्ठा net_device_ops lan78xx_netdev_ops = अणु
	.nकरो_खोलो		= lan78xx_खोलो,
	.nकरो_stop		= lan78xx_stop,
	.nकरो_start_xmit		= lan78xx_start_xmit,
	.nकरो_tx_समयout		= lan78xx_tx_समयout,
	.nकरो_change_mtu		= lan78xx_change_mtu,
	.nकरो_set_mac_address	= lan78xx_set_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_set_rx_mode	= lan78xx_set_multicast,
	.nकरो_set_features	= lan78xx_set_features,
	.nकरो_vlan_rx_add_vid	= lan78xx_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= lan78xx_vlan_rx_समाप्त_vid,
	.nकरो_features_check	= lan78xx_features_check,
पूर्ण;

अटल व्योम lan78xx_stat_monitor(काष्ठा समयr_list *t)
अणु
	काष्ठा lan78xx_net *dev = from_समयr(dev, t, stat_monitor);

	lan78xx_defer_kevent(dev, EVENT_STAT_UPDATE);
पूर्ण

अटल पूर्णांक lan78xx_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_endpoपूर्णांक *ep_blkin, *ep_blkout, *ep_पूर्णांकr;
	काष्ठा lan78xx_net *dev;
	काष्ठा net_device *netdev;
	काष्ठा usb_device *udev;
	पूर्णांक ret;
	अचिन्हित maxp;
	अचिन्हित period;
	u8 *buf = शून्य;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	udev = usb_get_dev(udev);

	netdev = alloc_etherdev(माप(काष्ठा lan78xx_net));
	अगर (!netdev) अणु
		dev_err(&पूर्णांकf->dev, "Error: OOM\n");
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण

	/* netdev_prपूर्णांकk() needs this */
	SET_NETDEV_DEV(netdev, &पूर्णांकf->dev);

	dev = netdev_priv(netdev);
	dev->udev = udev;
	dev->पूर्णांकf = पूर्णांकf;
	dev->net = netdev;
	dev->msg_enable = netअगर_msg_init(msg_level, NETIF_MSG_DRV
					| NETIF_MSG_PROBE | NETIF_MSG_LINK);

	skb_queue_head_init(&dev->rxq);
	skb_queue_head_init(&dev->txq);
	skb_queue_head_init(&dev->करोne);
	skb_queue_head_init(&dev->rxq_छोड़ो);
	skb_queue_head_init(&dev->txq_pend);
	mutex_init(&dev->phy_mutex);

	tasklet_setup(&dev->bh, lan78xx_bh);
	INIT_DELAYED_WORK(&dev->wq, lan78xx_delayedwork);
	init_usb_anchor(&dev->deferred);

	netdev->netdev_ops = &lan78xx_netdev_ops;
	netdev->watchकरोg_समयo = TX_TIMEOUT_JIFFIES;
	netdev->ethtool_ops = &lan78xx_ethtool_ops;

	dev->delta = 1;
	समयr_setup(&dev->stat_monitor, lan78xx_stat_monitor, 0);

	mutex_init(&dev->stats.access_lock);

	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 3) अणु
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	dev->pipe_in = usb_rcvbulkpipe(udev, BULK_IN_PIPE);
	ep_blkin = usb_pipe_endpoपूर्णांक(udev, dev->pipe_in);
	अगर (!ep_blkin || !usb_endpoपूर्णांक_is_bulk_in(&ep_blkin->desc)) अणु
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	dev->pipe_out = usb_sndbulkpipe(udev, BULK_OUT_PIPE);
	ep_blkout = usb_pipe_endpoपूर्णांक(udev, dev->pipe_out);
	अगर (!ep_blkout || !usb_endpoपूर्णांक_is_bulk_out(&ep_blkout->desc)) अणु
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	ep_पूर्णांकr = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[2];
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(&ep_पूर्णांकr->desc)) अणु
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	dev->pipe_पूर्णांकr = usb_rcvपूर्णांकpipe(dev->udev,
					usb_endpoपूर्णांक_num(&ep_पूर्णांकr->desc));

	ret = lan78xx_bind(dev, पूर्णांकf);
	अगर (ret < 0)
		जाओ out2;

	अगर (netdev->mtu > (dev->hard_mtu - netdev->hard_header_len))
		netdev->mtu = dev->hard_mtu - netdev->hard_header_len;

	/* MTU range: 68 - 9000 */
	netdev->max_mtu = MAX_SINGLE_PACKET_SIZE;
	netअगर_set_gso_max_size(netdev, MAX_SINGLE_PACKET_SIZE - MAX_HEADER);

	period = ep_पूर्णांकr->desc.bInterval;
	maxp = usb_maxpacket(dev->udev, dev->pipe_पूर्णांकr, 0);
	buf = kदो_स्मृति(maxp, GFP_KERNEL);
	अगर (buf) अणु
		dev->urb_पूर्णांकr = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!dev->urb_पूर्णांकr) अणु
			ret = -ENOMEM;
			kमुक्त(buf);
			जाओ out3;
		पूर्ण अन्यथा अणु
			usb_fill_पूर्णांक_urb(dev->urb_पूर्णांकr, dev->udev,
					 dev->pipe_पूर्णांकr, buf, maxp,
					 पूर्णांकr_complete, dev, period);
			dev->urb_पूर्णांकr->transfer_flags |= URB_FREE_BUFFER;
		पूर्ण
	पूर्ण

	dev->maxpacket = usb_maxpacket(dev->udev, dev->pipe_out, 1);

	/* driver requires remote-wakeup capability during स्वतःsuspend. */
	पूर्णांकf->needs_remote_wakeup = 1;

	ret = lan78xx_phy_init(dev);
	अगर (ret < 0)
		जाओ out4;

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret != 0) अणु
		netअगर_err(dev, probe, netdev, "couldn't register the device\n");
		जाओ out5;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	ret = device_set_wakeup_enable(&udev->dev, true);

	 /* Default delay of 2sec has more overhead than advantage.
	  * Set to 10sec as शेष.
	  */
	pm_runसमय_set_स्वतःsuspend_delay(&udev->dev,
					 DEFAULT_AUTOSUSPEND_DELAY);

	वापस 0;

out5:
	phy_disconnect(netdev->phydev);
out4:
	usb_मुक्त_urb(dev->urb_पूर्णांकr);
out3:
	lan78xx_unbind(dev, पूर्णांकf);
out2:
	मुक्त_netdev(netdev);
out1:
	usb_put_dev(udev);

	वापस ret;
पूर्ण

अटल u16 lan78xx_wakeframe_crc16(स्थिर u8 *buf, पूर्णांक len)
अणु
	स्थिर u16 crc16poly = 0x8005;
	पूर्णांक i;
	u16 bit, crc, msb;
	u8 data;

	crc = 0xFFFF;
	क्रम (i = 0; i < len; i++) अणु
		data = *buf++;
		क्रम (bit = 0; bit < 8; bit++) अणु
			msb = crc >> 15;
			crc <<= 1;

			अगर (msb ^ (u16)(data & 1)) अणु
				crc ^= crc16poly;
				crc |= (u16)0x0001U;
			पूर्ण
			data >>= 1;
		पूर्ण
	पूर्ण

	वापस crc;
पूर्ण

अटल पूर्णांक lan78xx_set_suspend(काष्ठा lan78xx_net *dev, u32 wol)
अणु
	u32 buf;
	पूर्णांक mask_index;
	u16 crc;
	u32 temp_wucsr;
	u32 temp_pmt_ctl;
	स्थिर u8 ipv4_multicast[3] = अणु 0x01, 0x00, 0x5E पूर्ण;
	स्थिर u8 ipv6_multicast[3] = अणु 0x33, 0x33 पूर्ण;
	स्थिर u8 arp_type[2] = अणु 0x08, 0x06 पूर्ण;

	lan78xx_पढ़ो_reg(dev, MAC_TX, &buf);
	buf &= ~MAC_TX_TXEN_;
	lan78xx_ग_लिखो_reg(dev, MAC_TX, buf);
	lan78xx_पढ़ो_reg(dev, MAC_RX, &buf);
	buf &= ~MAC_RX_RXEN_;
	lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);

	lan78xx_ग_लिखो_reg(dev, WUCSR, 0);
	lan78xx_ग_लिखो_reg(dev, WUCSR2, 0);
	lan78xx_ग_लिखो_reg(dev, WK_SRC, 0xFFF1FF1FUL);

	temp_wucsr = 0;

	temp_pmt_ctl = 0;
	lan78xx_पढ़ो_reg(dev, PMT_CTL, &temp_pmt_ctl);
	temp_pmt_ctl &= ~PMT_CTL_RES_CLR_WKP_EN_;
	temp_pmt_ctl |= PMT_CTL_RES_CLR_WKP_STS_;

	क्रम (mask_index = 0; mask_index < NUM_OF_WUF_CFG; mask_index++)
		lan78xx_ग_लिखो_reg(dev, WUF_CFG(mask_index), 0);

	mask_index = 0;
	अगर (wol & WAKE_PHY) अणु
		temp_pmt_ctl |= PMT_CTL_PHY_WAKE_EN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	पूर्ण
	अगर (wol & WAKE_MAGIC) अणु
		temp_wucsr |= WUCSR_MPEN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_3_;
	पूर्ण
	अगर (wol & WAKE_BCAST) अणु
		temp_wucsr |= WUCSR_BCST_EN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	पूर्ण
	अगर (wol & WAKE_MCAST) अणु
		temp_wucsr |= WUCSR_WAKE_EN_;

		/* set WUF_CFG & WUF_MASK क्रम IPv4 Multicast */
		crc = lan78xx_wakeframe_crc16(ipv4_multicast, 3);
		lan78xx_ग_लिखो_reg(dev, WUF_CFG(mask_index),
					WUF_CFGX_EN_ |
					WUF_CFGX_TYPE_MCAST_ |
					(0 << WUF_CFGX_OFFSET_SHIFT_) |
					(crc & WUF_CFGX_CRC16_MASK_));

		lan78xx_ग_लिखो_reg(dev, WUF_MASK0(mask_index), 7);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK1(mask_index), 0);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK2(mask_index), 0);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK3(mask_index), 0);
		mask_index++;

		/* क्रम IPv6 Multicast */
		crc = lan78xx_wakeframe_crc16(ipv6_multicast, 2);
		lan78xx_ग_लिखो_reg(dev, WUF_CFG(mask_index),
					WUF_CFGX_EN_ |
					WUF_CFGX_TYPE_MCAST_ |
					(0 << WUF_CFGX_OFFSET_SHIFT_) |
					(crc & WUF_CFGX_CRC16_MASK_));

		lan78xx_ग_लिखो_reg(dev, WUF_MASK0(mask_index), 3);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK1(mask_index), 0);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK2(mask_index), 0);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK3(mask_index), 0);
		mask_index++;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	पूर्ण
	अगर (wol & WAKE_UCAST) अणु
		temp_wucsr |= WUCSR_PFDA_EN_;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	पूर्ण
	अगर (wol & WAKE_ARP) अणु
		temp_wucsr |= WUCSR_WAKE_EN_;

		/* set WUF_CFG & WUF_MASK
		 * क्रम packettype (offset 12,13) = ARP (0x0806)
		 */
		crc = lan78xx_wakeframe_crc16(arp_type, 2);
		lan78xx_ग_लिखो_reg(dev, WUF_CFG(mask_index),
					WUF_CFGX_EN_ |
					WUF_CFGX_TYPE_ALL_ |
					(0 << WUF_CFGX_OFFSET_SHIFT_) |
					(crc & WUF_CFGX_CRC16_MASK_));

		lan78xx_ग_लिखो_reg(dev, WUF_MASK0(mask_index), 0x3000);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK1(mask_index), 0);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK2(mask_index), 0);
		lan78xx_ग_लिखो_reg(dev, WUF_MASK3(mask_index), 0);
		mask_index++;

		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	पूर्ण

	lan78xx_ग_लिखो_reg(dev, WUCSR, temp_wucsr);

	/* when multiple WOL bits are set */
	अगर (hweight_दीर्घ((अचिन्हित दीर्घ)wol) > 1) अणु
		temp_pmt_ctl |= PMT_CTL_WOL_EN_;
		temp_pmt_ctl &= ~PMT_CTL_SUS_MODE_MASK_;
		temp_pmt_ctl |= PMT_CTL_SUS_MODE_0_;
	पूर्ण
	lan78xx_ग_लिखो_reg(dev, PMT_CTL, temp_pmt_ctl);

	/* clear WUPS */
	lan78xx_पढ़ो_reg(dev, PMT_CTL, &buf);
	buf |= PMT_CTL_WUPS_MASK_;
	lan78xx_ग_लिखो_reg(dev, PMT_CTL, buf);

	lan78xx_पढ़ो_reg(dev, MAC_RX, &buf);
	buf |= MAC_RX_RXEN_;
	lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा lan78xx_net *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा lan78xx_priv *pdata = (काष्ठा lan78xx_priv *)(dev->data[0]);
	u32 buf;
	पूर्णांक ret;

	अगर (!dev->suspend_count++) अणु
		spin_lock_irq(&dev->txq.lock);
		/* करोn't स्वतःsuspend जबतक transmitting */
		अगर ((skb_queue_len(&dev->txq) ||
		     skb_queue_len(&dev->txq_pend)) &&
			PMSG_IS_AUTO(message)) अणु
			spin_unlock_irq(&dev->txq.lock);
			ret = -EBUSY;
			जाओ out;
		पूर्ण अन्यथा अणु
			set_bit(EVENT_DEV_ASLEEP, &dev->flags);
			spin_unlock_irq(&dev->txq.lock);
		पूर्ण

		/* stop TX & RX */
		ret = lan78xx_पढ़ो_reg(dev, MAC_TX, &buf);
		buf &= ~MAC_TX_TXEN_;
		ret = lan78xx_ग_लिखो_reg(dev, MAC_TX, buf);
		ret = lan78xx_पढ़ो_reg(dev, MAC_RX, &buf);
		buf &= ~MAC_RX_RXEN_;
		ret = lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);

		/* empty out the rx and queues */
		netअगर_device_detach(dev->net);
		lan78xx_terminate_urbs(dev);
		usb_समाप्त_urb(dev->urb_पूर्णांकr);

		/* reattach */
		netअगर_device_attach(dev->net);
	पूर्ण

	अगर (test_bit(EVENT_DEV_ASLEEP, &dev->flags)) अणु
		del_समयr(&dev->stat_monitor);

		अगर (PMSG_IS_AUTO(message)) अणु
			/* स्वतः suspend (selective suspend) */
			ret = lan78xx_पढ़ो_reg(dev, MAC_TX, &buf);
			buf &= ~MAC_TX_TXEN_;
			ret = lan78xx_ग_लिखो_reg(dev, MAC_TX, buf);
			ret = lan78xx_पढ़ो_reg(dev, MAC_RX, &buf);
			buf &= ~MAC_RX_RXEN_;
			ret = lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);

			ret = lan78xx_ग_लिखो_reg(dev, WUCSR, 0);
			ret = lan78xx_ग_लिखो_reg(dev, WUCSR2, 0);
			ret = lan78xx_ग_लिखो_reg(dev, WK_SRC, 0xFFF1FF1FUL);

			/* set goodframe wakeup */
			ret = lan78xx_पढ़ो_reg(dev, WUCSR, &buf);

			buf |= WUCSR_RFE_WAKE_EN_;
			buf |= WUCSR_STORE_WAKE_;

			ret = lan78xx_ग_लिखो_reg(dev, WUCSR, buf);

			ret = lan78xx_पढ़ो_reg(dev, PMT_CTL, &buf);

			buf &= ~PMT_CTL_RES_CLR_WKP_EN_;
			buf |= PMT_CTL_RES_CLR_WKP_STS_;

			buf |= PMT_CTL_PHY_WAKE_EN_;
			buf |= PMT_CTL_WOL_EN_;
			buf &= ~PMT_CTL_SUS_MODE_MASK_;
			buf |= PMT_CTL_SUS_MODE_3_;

			ret = lan78xx_ग_लिखो_reg(dev, PMT_CTL, buf);

			ret = lan78xx_पढ़ो_reg(dev, PMT_CTL, &buf);

			buf |= PMT_CTL_WUPS_MASK_;

			ret = lan78xx_ग_लिखो_reg(dev, PMT_CTL, buf);

			ret = lan78xx_पढ़ो_reg(dev, MAC_RX, &buf);
			buf |= MAC_RX_RXEN_;
			ret = lan78xx_ग_लिखो_reg(dev, MAC_RX, buf);
		पूर्ण अन्यथा अणु
			lan78xx_set_suspend(dev, pdata->wol);
		पूर्ण
	पूर्ण

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक lan78xx_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा lan78xx_net *dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा sk_buff *skb;
	काष्ठा urb *res;
	पूर्णांक ret;
	u32 buf;

	अगर (!समयr_pending(&dev->stat_monitor)) अणु
		dev->delta = 1;
		mod_समयr(&dev->stat_monitor,
			  jअगरfies + STAT_UPDATE_TIMER);
	पूर्ण

	अगर (!--dev->suspend_count) अणु
		/* resume पूर्णांकerrupt URBs */
		अगर (dev->urb_पूर्णांकr && test_bit(EVENT_DEV_OPEN, &dev->flags))
				usb_submit_urb(dev->urb_पूर्णांकr, GFP_NOIO);

		spin_lock_irq(&dev->txq.lock);
		जबतक ((res = usb_get_from_anchor(&dev->deferred))) अणु
			skb = (काष्ठा sk_buff *)res->context;
			ret = usb_submit_urb(res, GFP_ATOMIC);
			अगर (ret < 0) अणु
				dev_kमुक्त_skb_any(skb);
				usb_मुक्त_urb(res);
				usb_स्वतःpm_put_पूर्णांकerface_async(dev->पूर्णांकf);
			पूर्ण अन्यथा अणु
				netअगर_trans_update(dev->net);
				lan78xx_queue_skb(&dev->txq, skb, tx_start);
			पूर्ण
		पूर्ण

		clear_bit(EVENT_DEV_ASLEEP, &dev->flags);
		spin_unlock_irq(&dev->txq.lock);

		अगर (test_bit(EVENT_DEV_OPEN, &dev->flags)) अणु
			अगर (!(skb_queue_len(&dev->txq) >= dev->tx_qlen))
				netअगर_start_queue(dev->net);
			tasklet_schedule(&dev->bh);
		पूर्ण
	पूर्ण

	ret = lan78xx_ग_लिखो_reg(dev, WUCSR2, 0);
	ret = lan78xx_ग_लिखो_reg(dev, WUCSR, 0);
	ret = lan78xx_ग_लिखो_reg(dev, WK_SRC, 0xFFF1FF1FUL);

	ret = lan78xx_ग_लिखो_reg(dev, WUCSR2, WUCSR2_NS_RCD_ |
					     WUCSR2_ARP_RCD_ |
					     WUCSR2_IPV6_TCPSYN_RCD_ |
					     WUCSR2_IPV4_TCPSYN_RCD_);

	ret = lan78xx_ग_लिखो_reg(dev, WUCSR, WUCSR_EEE_TX_WAKE_ |
					    WUCSR_EEE_RX_WAKE_ |
					    WUCSR_PFDA_FR_ |
					    WUCSR_RFE_WAKE_FR_ |
					    WUCSR_WUFR_ |
					    WUCSR_MPR_ |
					    WUCSR_BCST_FR_);

	ret = lan78xx_पढ़ो_reg(dev, MAC_TX, &buf);
	buf |= MAC_TX_TXEN_;
	ret = lan78xx_ग_लिखो_reg(dev, MAC_TX, buf);

	वापस 0;
पूर्ण

अटल पूर्णांक lan78xx_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा lan78xx_net *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	lan78xx_reset(dev);

	phy_start(dev->net->phydev);

	वापस lan78xx_resume(पूर्णांकf);
पूर्ण

अटल स्थिर काष्ठा usb_device_id products[] = अणु
	अणु
	/* LAN7800 USB Gigabit Ethernet Device */
	USB_DEVICE(LAN78XX_USB_VENDOR_ID, LAN7800_USB_PRODUCT_ID),
	पूर्ण,
	अणु
	/* LAN7850 USB Gigabit Ethernet Device */
	USB_DEVICE(LAN78XX_USB_VENDOR_ID, LAN7850_USB_PRODUCT_ID),
	पूर्ण,
	अणु
	/* LAN7801 USB Gigabit Ethernet Device */
	USB_DEVICE(LAN78XX_USB_VENDOR_ID, LAN7801_USB_PRODUCT_ID),
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver lan78xx_driver = अणु
	.name			= DRIVER_NAME,
	.id_table		= products,
	.probe			= lan78xx_probe,
	.disconnect		= lan78xx_disconnect,
	.suspend		= lan78xx_suspend,
	.resume			= lan78xx_resume,
	.reset_resume		= lan78xx_reset_resume,
	.supports_स्वतःsuspend	= 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(lan78xx_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
