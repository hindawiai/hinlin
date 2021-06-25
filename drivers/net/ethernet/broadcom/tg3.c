<शैली गुरु>
/*
 * tg3.c: Broadcom Tigon3 ethernet driver.
 *
 * Copyright (C) 2001, 2002, 2003, 2004 David S. Miller (davem@redhat.com)
 * Copyright (C) 2001, 2002, 2003 Jeff Garzik (jgarzik@pobox.com)
 * Copyright (C) 2004 Sun Microप्रणालीs Inc.
 * Copyright (C) 2005-2016 Broadcom Corporation.
 * Copyright (C) 2016-2017 Broadcom Limited.
 * Copyright (C) 2018 Broadcom. All Rights Reserved. The term "Broadcom"
 * refers to Broadcom Inc. and/or its subsidiaries.
 *
 * Firmware is:
 *	Derived from proprietary unpublished source code,
 *	Copyright (C) 2000-2016 Broadcom Corporation.
 *	Copyright (C) 2016-2017 Broadcom Ltd.
 *	Copyright (C) 2018 Broadcom. All Rights Reserved. The term "Broadcom"
 *	refers to Broadcom Inc. and/or its subsidiaries.
 *
 *	Permission is hereby granted क्रम the distribution of this firmware
 *	data in hexadecimal or equivalent क्रमmat, provided this copyright
 *	notice is accompanying it.
 */


#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/in.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ssb/ssb_driver_gige.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/crc32poly.h>

#समावेश <net/checksum.h>
#समावेश <net/ip.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

#समावेश <uapi/linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#घोषणा BAR_0	0
#घोषणा BAR_2	2

#समावेश "tg3.h"

/* Functions & macros to verअगरy TG3_FLAGS types */

अटल अंतरभूत पूर्णांक _tg3_flag(क्रमागत TG3_FLAGS flag, अचिन्हित दीर्घ *bits)
अणु
	वापस test_bit(flag, bits);
पूर्ण

अटल अंतरभूत व्योम _tg3_flag_set(क्रमागत TG3_FLAGS flag, अचिन्हित दीर्घ *bits)
अणु
	set_bit(flag, bits);
पूर्ण

अटल अंतरभूत व्योम _tg3_flag_clear(क्रमागत TG3_FLAGS flag, अचिन्हित दीर्घ *bits)
अणु
	clear_bit(flag, bits);
पूर्ण

#घोषणा tg3_flag(tp, flag)				\
	_tg3_flag(TG3_FLAG_##flag, (tp)->tg3_flags)
#घोषणा tg3_flag_set(tp, flag)				\
	_tg3_flag_set(TG3_FLAG_##flag, (tp)->tg3_flags)
#घोषणा tg3_flag_clear(tp, flag)			\
	_tg3_flag_clear(TG3_FLAG_##flag, (tp)->tg3_flags)

#घोषणा DRV_MODULE_NAME		"tg3"
/* DO NOT UPDATE TG3_*_NUM defines */
#घोषणा TG3_MAJ_NUM			3
#घोषणा TG3_MIN_NUM			137

#घोषणा RESET_KIND_SHUTDOWN	0
#घोषणा RESET_KIND_INIT		1
#घोषणा RESET_KIND_SUSPEND	2

#घोषणा TG3_DEF_RX_MODE		0
#घोषणा TG3_DEF_TX_MODE		0
#घोषणा TG3_DEF_MSG_ENABLE	  \
	(NETIF_MSG_DRV		| \
	 NETIF_MSG_PROBE	| \
	 NETIF_MSG_LINK		| \
	 NETIF_MSG_TIMER	| \
	 NETIF_MSG_IFDOWN	| \
	 NETIF_MSG_IFUP		| \
	 NETIF_MSG_RX_ERR	| \
	 NETIF_MSG_TX_ERR)

#घोषणा TG3_GRC_LCLCTL_PWRSW_DELAY	100

/* length of समय beक्रमe we decide the hardware is borked,
 * and dev->tx_समयout() should be called to fix the problem
 */

#घोषणा TG3_TX_TIMEOUT			(5 * HZ)

/* hardware minimum and maximum क्रम a single frame's data payload */
#घोषणा TG3_MIN_MTU			ETH_ZLEN
#घोषणा TG3_MAX_MTU(tp)	\
	(tg3_flag(tp, JUMBO_CAPABLE) ? 9000 : 1500)

/* These numbers seem to be hard coded in the NIC firmware somehow.
 * You can't change the ring sizes, but you can change where you place
 * them in the NIC onboard memory.
 */
#घोषणा TG3_RX_STD_RING_SIZE(tp) \
	(tg3_flag(tp, LRG_PROD_RING_CAP) ? \
	 TG3_RX_STD_MAX_SIZE_5717 : TG3_RX_STD_MAX_SIZE_5700)
#घोषणा TG3_DEF_RX_RING_PENDING		200
#घोषणा TG3_RX_JMB_RING_SIZE(tp) \
	(tg3_flag(tp, LRG_PROD_RING_CAP) ? \
	 TG3_RX_JMB_MAX_SIZE_5717 : TG3_RX_JMB_MAX_SIZE_5700)
#घोषणा TG3_DEF_RX_JUMBO_RING_PENDING	100

/* Do not place this n-ring entries value पूर्णांकo the tp काष्ठा itself,
 * we really want to expose these स्थिरants to GCC so that modulo et
 * al.  operations are करोne with shअगरts and masks instead of with
 * hw multiply/modulo inकाष्ठाions.  Another solution would be to
 * replace things like '% foo' with '& (foo - 1)'.
 */

#घोषणा TG3_TX_RING_SIZE		512
#घोषणा TG3_DEF_TX_RING_PENDING		(TG3_TX_RING_SIZE - 1)

#घोषणा TG3_RX_STD_RING_BYTES(tp) \
	(माप(काष्ठा tg3_rx_buffer_desc) * TG3_RX_STD_RING_SIZE(tp))
#घोषणा TG3_RX_JMB_RING_BYTES(tp) \
	(माप(काष्ठा tg3_ext_rx_buffer_desc) * TG3_RX_JMB_RING_SIZE(tp))
#घोषणा TG3_RX_RCB_RING_BYTES(tp) \
	(माप(काष्ठा tg3_rx_buffer_desc) * (tp->rx_ret_ring_mask + 1))
#घोषणा TG3_TX_RING_BYTES	(माप(काष्ठा tg3_tx_buffer_desc) * \
				 TG3_TX_RING_SIZE)
#घोषणा NEXT_TX(N)		(((N) + 1) & (TG3_TX_RING_SIZE - 1))

#घोषणा TG3_DMA_BYTE_ENAB		64

#घोषणा TG3_RX_STD_DMA_SZ		1536
#घोषणा TG3_RX_JMB_DMA_SZ		9046

#घोषणा TG3_RX_DMA_TO_MAP_SZ(x)		((x) + TG3_DMA_BYTE_ENAB)

#घोषणा TG3_RX_STD_MAP_SZ		TG3_RX_DMA_TO_MAP_SZ(TG3_RX_STD_DMA_SZ)
#घोषणा TG3_RX_JMB_MAP_SZ		TG3_RX_DMA_TO_MAP_SZ(TG3_RX_JMB_DMA_SZ)

#घोषणा TG3_RX_STD_BUFF_RING_SIZE(tp) \
	(माप(काष्ठा ring_info) * TG3_RX_STD_RING_SIZE(tp))

#घोषणा TG3_RX_JMB_BUFF_RING_SIZE(tp) \
	(माप(काष्ठा ring_info) * TG3_RX_JMB_RING_SIZE(tp))

/* Due to a hardware bug, the 5701 can only DMA to memory addresses
 * that are at least dword aligned when used in PCIX mode.  The driver
 * works around this bug by द्विगुन copying the packet.  This workaround
 * is built पूर्णांकo the normal द्विगुन copy length check क्रम efficiency.
 *
 * However, the द्विगुन copy is only necessary on those architectures
 * where unaligned memory accesses are inefficient.  For those architectures
 * where unaligned memory accesses incur little penalty, we can reपूर्णांकegrate
 * the 5701 in the normal rx path.  Doing so saves a device काष्ठाure
 * dereference by hardcoding the द्विगुन copy threshold in place.
 */
#घोषणा TG3_RX_COPY_THRESHOLD		256
#अगर NET_IP_ALIGN == 0 || defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	#घोषणा TG3_RX_COPY_THRESH(tp)	TG3_RX_COPY_THRESHOLD
#अन्यथा
	#घोषणा TG3_RX_COPY_THRESH(tp)	((tp)->rx_copy_thresh)
#पूर्ण_अगर

#अगर (NET_IP_ALIGN != 0)
#घोषणा TG3_RX_OFFSET(tp)	((tp)->rx_offset)
#अन्यथा
#घोषणा TG3_RX_OFFSET(tp)	(NET_SKB_PAD)
#पूर्ण_अगर

/* minimum number of मुक्त TX descriptors required to wake up TX process */
#घोषणा TG3_TX_WAKEUP_THRESH(tnapi)		((tnapi)->tx_pending / 4)
#घोषणा TG3_TX_BD_DMA_MAX_2K		2048
#घोषणा TG3_TX_BD_DMA_MAX_4K		4096

#घोषणा TG3_RAW_IP_ALIGN 2

#घोषणा TG3_MAX_UCAST_ADDR(tp) (tg3_flag((tp), ENABLE_ASF) ? 2 : 3)
#घोषणा TG3_UCAST_ADDR_IDX(tp) (tg3_flag((tp), ENABLE_ASF) ? 2 : 1)

#घोषणा TG3_FW_UPDATE_TIMEOUT_SEC	5
#घोषणा TG3_FW_UPDATE_FREQ_SEC		(TG3_FW_UPDATE_TIMEOUT_SEC / 2)

#घोषणा FIRMWARE_TG3		"tigon/tg3.bin"
#घोषणा FIRMWARE_TG357766	"tigon/tg357766.bin"
#घोषणा FIRMWARE_TG3TSO		"tigon/tg3_tso.bin"
#घोषणा FIRMWARE_TG3TSO5	"tigon/tg3_tso5.bin"

MODULE_AUTHOR("David S. Miller (davem@redhat.com) and Jeff Garzik (jgarzik@pobox.com)");
MODULE_DESCRIPTION("Broadcom Tigon3 ethernet driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_TG3);
MODULE_FIRMWARE(FIRMWARE_TG3TSO);
MODULE_FIRMWARE(FIRMWARE_TG3TSO5);

अटल पूर्णांक tg3_debug = -1;	/* -1 == use TG3_DEF_MSG_ENABLE as value */
module_param(tg3_debug, पूर्णांक, 0);
MODULE_PARM_DESC(tg3_debug, "Tigon3 bitmapped debugging message enable value");

#घोषणा TG3_DRV_DATA_FLAG_10_100_ONLY	0x0001
#घोषणा TG3_DRV_DATA_FLAG_5705_10_100	0x0002

अटल स्थिर काष्ठा pci_device_id tg3_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5700)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5701)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5702)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5703)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5704)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5702FE)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5705)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5705_2)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5705M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5705M_2)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5702X)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5703X)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5704S)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5702A3)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5703A3)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5782)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5788)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5789)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5901),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLY |
			TG3_DRV_DATA_FLAG_5705_10_100पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5901_2),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLY |
			TG3_DRV_DATA_FLAG_5705_10_100पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5704S_2)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5705F),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLY |
			TG3_DRV_DATA_FLAG_5705_10_100पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5721)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5722)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5750)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5751)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5751M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5751F),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5752)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5752M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5753)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5753M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5753F),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5754)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5754M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5755)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5755M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5756)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5786)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5787)पूर्ण,
	अणुPCI_DEVICE_SUB(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5787M,
			PCI_VENDOR_ID_LENOVO,
			TG3PCI_SUBDEVICE_ID_LENOVO_5787M),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5787M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5787F),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5714)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5714S)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5715)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5715S)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5780)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5780S)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5781)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5906)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5906M)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5784)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5764)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5723)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5761)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, PCI_DEVICE_ID_TIGON3_5761E)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5761S)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5761SE)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5785_G)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5785_F)पूर्ण,
	अणुPCI_DEVICE_SUB(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57780,
			PCI_VENDOR_ID_AI, TG3PCI_SUBDEVICE_ID_ACER_57780_A),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE_SUB(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57780,
			PCI_VENDOR_ID_AI, TG3PCI_SUBDEVICE_ID_ACER_57780_B),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57780)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57760)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57790),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57788)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5717)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5717_C)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5718)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57781)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57785)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57761)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57765)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57791),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57795),
	 .driver_data = TG3_DRV_DATA_FLAG_10_100_ONLYपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5719)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5720)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57762)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57766)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5762)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5725)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_5727)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57764)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57767)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57787)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57782)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_BROADCOM, TG3PCI_DEVICE_TIGON3_57786)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SYSKONNECT, PCI_DEVICE_ID_SYSKONNECT_9DXX)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SYSKONNECT, PCI_DEVICE_ID_SYSKONNECT_9MXX)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ALTIMA, PCI_DEVICE_ID_ALTIMA_AC1000)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ALTIMA, PCI_DEVICE_ID_ALTIMA_AC1001)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ALTIMA, PCI_DEVICE_ID_ALTIMA_AC1003)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_ALTIMA, PCI_DEVICE_ID_ALTIMA_AC9100)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_TIGON3)पूर्ण,
	अणुPCI_DEVICE(0x10cf, 0x11a2)पूर्ण, /* Fujitsu 1000base-SX with BCM5703SKHB */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, tg3_pci_tbl);

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "rx_octets" पूर्ण,
	अणु "rx_fragments" पूर्ण,
	अणु "rx_ucast_packets" पूर्ण,
	अणु "rx_mcast_packets" पूर्ण,
	अणु "rx_bcast_packets" पूर्ण,
	अणु "rx_fcs_errors" पूर्ण,
	अणु "rx_align_errors" पूर्ण,
	अणु "rx_xon_pause_rcvd" पूर्ण,
	अणु "rx_xoff_pause_rcvd" पूर्ण,
	अणु "rx_mac_ctrl_rcvd" पूर्ण,
	अणु "rx_xoff_entered" पूर्ण,
	अणु "rx_frame_too_long_errors" पूर्ण,
	अणु "rx_jabbers" पूर्ण,
	अणु "rx_undersize_packets" पूर्ण,
	अणु "rx_in_length_errors" पूर्ण,
	अणु "rx_out_length_errors" पूर्ण,
	अणु "rx_64_or_less_octet_packets" पूर्ण,
	अणु "rx_65_to_127_octet_packets" पूर्ण,
	अणु "rx_128_to_255_octet_packets" पूर्ण,
	अणु "rx_256_to_511_octet_packets" पूर्ण,
	अणु "rx_512_to_1023_octet_packets" पूर्ण,
	अणु "rx_1024_to_1522_octet_packets" पूर्ण,
	अणु "rx_1523_to_2047_octet_packets" पूर्ण,
	अणु "rx_2048_to_4095_octet_packets" पूर्ण,
	अणु "rx_4096_to_8191_octet_packets" पूर्ण,
	अणु "rx_8192_to_9022_octet_packets" पूर्ण,

	अणु "tx_octets" पूर्ण,
	अणु "tx_collisions" पूर्ण,

	अणु "tx_xon_sent" पूर्ण,
	अणु "tx_xoff_sent" पूर्ण,
	अणु "tx_flow_control" पूर्ण,
	अणु "tx_mac_errors" पूर्ण,
	अणु "tx_single_collisions" पूर्ण,
	अणु "tx_mult_collisions" पूर्ण,
	अणु "tx_deferred" पूर्ण,
	अणु "tx_excessive_collisions" पूर्ण,
	अणु "tx_late_collisions" पूर्ण,
	अणु "tx_collide_2times" पूर्ण,
	अणु "tx_collide_3times" पूर्ण,
	अणु "tx_collide_4times" पूर्ण,
	अणु "tx_collide_5times" पूर्ण,
	अणु "tx_collide_6times" पूर्ण,
	अणु "tx_collide_7times" पूर्ण,
	अणु "tx_collide_8times" पूर्ण,
	अणु "tx_collide_9times" पूर्ण,
	अणु "tx_collide_10times" पूर्ण,
	अणु "tx_collide_11times" पूर्ण,
	अणु "tx_collide_12times" पूर्ण,
	अणु "tx_collide_13times" पूर्ण,
	अणु "tx_collide_14times" पूर्ण,
	अणु "tx_collide_15times" पूर्ण,
	अणु "tx_ucast_packets" पूर्ण,
	अणु "tx_mcast_packets" पूर्ण,
	अणु "tx_bcast_packets" पूर्ण,
	अणु "tx_carrier_sense_errors" पूर्ण,
	अणु "tx_discards" पूर्ण,
	अणु "tx_errors" पूर्ण,

	अणु "dma_writeq_full" पूर्ण,
	अणु "dma_write_prioq_full" पूर्ण,
	अणु "rxbds_empty" पूर्ण,
	अणु "rx_discards" पूर्ण,
	अणु "rx_errors" पूर्ण,
	अणु "rx_threshold_hit" पूर्ण,

	अणु "dma_readq_full" पूर्ण,
	अणु "dma_read_prioq_full" पूर्ण,
	अणु "tx_comp_queue_full" पूर्ण,

	अणु "ring_set_send_prod_index" पूर्ण,
	अणु "ring_status_update" पूर्ण,
	अणु "nic_irqs" पूर्ण,
	अणु "nic_avoided_irqs" पूर्ण,
	अणु "nic_tx_threshold_hit" पूर्ण,

	अणु "mbuf_lwm_thresh_hit" पूर्ण,
पूर्ण;

#घोषणा TG3_NUM_STATS	ARRAY_SIZE(ethtool_stats_keys)
#घोषणा TG3_NVRAM_TEST		0
#घोषणा TG3_LINK_TEST		1
#घोषणा TG3_REGISTER_TEST	2
#घोषणा TG3_MEMORY_TEST		3
#घोषणा TG3_MAC_LOOPB_TEST	4
#घोषणा TG3_PHY_LOOPB_TEST	5
#घोषणा TG3_EXT_LOOPB_TEST	6
#घोषणा TG3_INTERRUPT_TEST	7


अटल स्थिर काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण ethtool_test_keys[] = अणु
	[TG3_NVRAM_TEST]	= अणु "nvram test        (online) " पूर्ण,
	[TG3_LINK_TEST]		= अणु "link test         (online) " पूर्ण,
	[TG3_REGISTER_TEST]	= अणु "register test     (offline)" पूर्ण,
	[TG3_MEMORY_TEST]	= अणु "memory test       (offline)" पूर्ण,
	[TG3_MAC_LOOPB_TEST]	= अणु "mac loopback test (offline)" पूर्ण,
	[TG3_PHY_LOOPB_TEST]	= अणु "phy loopback test (offline)" पूर्ण,
	[TG3_EXT_LOOPB_TEST]	= अणु "ext loopback test (offline)" पूर्ण,
	[TG3_INTERRUPT_TEST]	= अणु "interrupt test    (offline)" पूर्ण,
पूर्ण;

#घोषणा TG3_NUM_TEST	ARRAY_SIZE(ethtool_test_keys)


अटल व्योम tg3_ग_लिखो32(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	ग_लिखोl(val, tp->regs + off);
पूर्ण

अटल u32 tg3_पढ़ो32(काष्ठा tg3 *tp, u32 off)
अणु
	वापस पढ़ोl(tp->regs + off);
पूर्ण

अटल व्योम tg3_ape_ग_लिखो32(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	ग_लिखोl(val, tp->aperegs + off);
पूर्ण

अटल u32 tg3_ape_पढ़ो32(काष्ठा tg3 *tp, u32 off)
अणु
	वापस पढ़ोl(tp->aperegs + off);
पूर्ण

अटल व्योम tg3_ग_लिखो_indirect_reg32(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tp->indirect_lock, flags);
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_REG_BASE_ADDR, off);
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_REG_DATA, val);
	spin_unlock_irqrestore(&tp->indirect_lock, flags);
पूर्ण

अटल व्योम tg3_ग_लिखो_flush_reg32(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	ग_लिखोl(val, tp->regs + off);
	पढ़ोl(tp->regs + off);
पूर्ण

अटल u32 tg3_पढ़ो_indirect_reg32(काष्ठा tg3 *tp, u32 off)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&tp->indirect_lock, flags);
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_REG_BASE_ADDR, off);
	pci_पढ़ो_config_dword(tp->pdev, TG3PCI_REG_DATA, &val);
	spin_unlock_irqrestore(&tp->indirect_lock, flags);
	वापस val;
पूर्ण

अटल व्योम tg3_ग_लिखो_indirect_mbox(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	अगर (off == (MAILBOX_RCVRET_CON_IDX_0 + TG3_64BIT_REG_LOW)) अणु
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_RCV_RET_RING_CON_IDX +
				       TG3_64BIT_REG_LOW, val);
		वापस;
	पूर्ण
	अगर (off == TG3_RX_STD_PROD_IDX_REG) अणु
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_STD_RING_PROD_IDX +
				       TG3_64BIT_REG_LOW, val);
		वापस;
	पूर्ण

	spin_lock_irqsave(&tp->indirect_lock, flags);
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_REG_BASE_ADDR, off + 0x5600);
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_REG_DATA, val);
	spin_unlock_irqrestore(&tp->indirect_lock, flags);

	/* In indirect mode when disabling पूर्णांकerrupts, we also need
	 * to clear the पूर्णांकerrupt bit in the GRC local ctrl रेजिस्टर.
	 */
	अगर ((off == (MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW)) &&
	    (val == 0x1)) अणु
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MISC_LOCAL_CTRL,
				       tp->grc_local_ctrl|GRC_LCLCTRL_CLEARINT);
	पूर्ण
पूर्ण

अटल u32 tg3_पढ़ो_indirect_mbox(काष्ठा tg3 *tp, u32 off)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&tp->indirect_lock, flags);
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_REG_BASE_ADDR, off + 0x5600);
	pci_पढ़ो_config_dword(tp->pdev, TG3PCI_REG_DATA, &val);
	spin_unlock_irqrestore(&tp->indirect_lock, flags);
	वापस val;
पूर्ण

/* usec_रुको specअगरies the रुको समय in usec when writing to certain रेजिस्टरs
 * where it is unsafe to पढ़ो back the रेजिस्टर without some delay.
 * GRC_LOCAL_CTRL is one example अगर the GPIOs are toggled to चयन घातer.
 * TG3PCI_CLOCK_CTRL is another example अगर the घड़ी frequencies are changed.
 */
अटल व्योम _tw32_flush(काष्ठा tg3 *tp, u32 off, u32 val, u32 usec_रुको)
अणु
	अगर (tg3_flag(tp, PCIX_TARGET_HWBUG) || tg3_flag(tp, ICH_WORKAROUND))
		/* Non-posted methods */
		tp->ग_लिखो32(tp, off, val);
	अन्यथा अणु
		/* Posted method */
		tg3_ग_लिखो32(tp, off, val);
		अगर (usec_रुको)
			udelay(usec_रुको);
		tp->पढ़ो32(tp, off);
	पूर्ण
	/* Wait again after the पढ़ो क्रम the posted method to guarantee that
	 * the रुको समय is met.
	 */
	अगर (usec_रुको)
		udelay(usec_रुको);
पूर्ण

अटल अंतरभूत व्योम tw32_mailbox_flush(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	tp->ग_लिखो32_mbox(tp, off, val);
	अगर (tg3_flag(tp, FLUSH_POSTED_WRITES) ||
	    (!tg3_flag(tp, MBOX_WRITE_REORDER) &&
	     !tg3_flag(tp, ICH_WORKAROUND)))
		tp->पढ़ो32_mbox(tp, off);
पूर्ण

अटल व्योम tg3_ग_लिखो32_tx_mbox(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	व्योम __iomem *mbox = tp->regs + off;
	ग_लिखोl(val, mbox);
	अगर (tg3_flag(tp, TXD_MBOX_HWBUG))
		ग_लिखोl(val, mbox);
	अगर (tg3_flag(tp, MBOX_WRITE_REORDER) ||
	    tg3_flag(tp, FLUSH_POSTED_WRITES))
		पढ़ोl(mbox);
पूर्ण

अटल u32 tg3_पढ़ो32_mbox_5906(काष्ठा tg3 *tp, u32 off)
अणु
	वापस पढ़ोl(tp->regs + off + GRCMBOX_BASE);
पूर्ण

अटल व्योम tg3_ग_लिखो32_mbox_5906(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	ग_लिखोl(val, tp->regs + off + GRCMBOX_BASE);
पूर्ण

#घोषणा tw32_mailbox(reg, val)		tp->ग_लिखो32_mbox(tp, reg, val)
#घोषणा tw32_mailbox_f(reg, val)	tw32_mailbox_flush(tp, (reg), (val))
#घोषणा tw32_rx_mbox(reg, val)		tp->ग_लिखो32_rx_mbox(tp, reg, val)
#घोषणा tw32_tx_mbox(reg, val)		tp->ग_लिखो32_tx_mbox(tp, reg, val)
#घोषणा tr32_mailbox(reg)		tp->पढ़ो32_mbox(tp, reg)

#घोषणा tw32(reg, val)			tp->ग_लिखो32(tp, reg, val)
#घोषणा tw32_f(reg, val)		_tw32_flush(tp, (reg), (val), 0)
#घोषणा tw32_रुको_f(reg, val, us)	_tw32_flush(tp, (reg), (val), (us))
#घोषणा tr32(reg)			tp->पढ़ो32(tp, reg)

अटल व्योम tg3_ग_लिखो_mem(काष्ठा tg3 *tp, u32 off, u32 val)
अणु
	अचिन्हित दीर्घ flags;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906 &&
	    (off >= NIC_SRAM_STATS_BLK) && (off < NIC_SRAM_TX_BUFFER_DESC))
		वापस;

	spin_lock_irqsave(&tp->indirect_lock, flags);
	अगर (tg3_flag(tp, SRAM_USE_CONFIG)) अणु
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, off);
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_DATA, val);

		/* Always leave this as zero. */
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, 0);
	पूर्ण अन्यथा अणु
		tw32_f(TG3PCI_MEM_WIN_BASE_ADDR, off);
		tw32_f(TG3PCI_MEM_WIN_DATA, val);

		/* Always leave this as zero. */
		tw32_f(TG3PCI_MEM_WIN_BASE_ADDR, 0);
	पूर्ण
	spin_unlock_irqrestore(&tp->indirect_lock, flags);
पूर्ण

अटल व्योम tg3_पढ़ो_mem(काष्ठा tg3 *tp, u32 off, u32 *val)
अणु
	अचिन्हित दीर्घ flags;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906 &&
	    (off >= NIC_SRAM_STATS_BLK) && (off < NIC_SRAM_TX_BUFFER_DESC)) अणु
		*val = 0;
		वापस;
	पूर्ण

	spin_lock_irqsave(&tp->indirect_lock, flags);
	अगर (tg3_flag(tp, SRAM_USE_CONFIG)) अणु
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, off);
		pci_पढ़ो_config_dword(tp->pdev, TG3PCI_MEM_WIN_DATA, val);

		/* Always leave this as zero. */
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, 0);
	पूर्ण अन्यथा अणु
		tw32_f(TG3PCI_MEM_WIN_BASE_ADDR, off);
		*val = tr32(TG3PCI_MEM_WIN_DATA);

		/* Always leave this as zero. */
		tw32_f(TG3PCI_MEM_WIN_BASE_ADDR, 0);
	पूर्ण
	spin_unlock_irqrestore(&tp->indirect_lock, flags);
पूर्ण

अटल व्योम tg3_ape_lock_init(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	u32 regbase, bit;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5761)
		regbase = TG3_APE_LOCK_GRANT;
	अन्यथा
		regbase = TG3_APE_PER_LOCK_GRANT;

	/* Make sure the driver hasn't any stale locks. */
	क्रम (i = TG3_APE_LOCK_PHY0; i <= TG3_APE_LOCK_GPIO; i++) अणु
		चयन (i) अणु
		हाल TG3_APE_LOCK_PHY0:
		हाल TG3_APE_LOCK_PHY1:
		हाल TG3_APE_LOCK_PHY2:
		हाल TG3_APE_LOCK_PHY3:
			bit = APE_LOCK_GRANT_DRIVER;
			अवरोध;
		शेष:
			अगर (!tp->pci_fn)
				bit = APE_LOCK_GRANT_DRIVER;
			अन्यथा
				bit = 1 << tp->pci_fn;
		पूर्ण
		tg3_ape_ग_लिखो32(tp, regbase + 4 * i, bit);
	पूर्ण

पूर्ण

अटल पूर्णांक tg3_ape_lock(काष्ठा tg3 *tp, पूर्णांक locknum)
अणु
	पूर्णांक i, off;
	पूर्णांक ret = 0;
	u32 status, req, gnt, bit;

	अगर (!tg3_flag(tp, ENABLE_APE))
		वापस 0;

	चयन (locknum) अणु
	हाल TG3_APE_LOCK_GPIO:
		अगर (tg3_asic_rev(tp) == ASIC_REV_5761)
			वापस 0;
		fallthrough;
	हाल TG3_APE_LOCK_GRC:
	हाल TG3_APE_LOCK_MEM:
		अगर (!tp->pci_fn)
			bit = APE_LOCK_REQ_DRIVER;
		अन्यथा
			bit = 1 << tp->pci_fn;
		अवरोध;
	हाल TG3_APE_LOCK_PHY0:
	हाल TG3_APE_LOCK_PHY1:
	हाल TG3_APE_LOCK_PHY2:
	हाल TG3_APE_LOCK_PHY3:
		bit = APE_LOCK_REQ_DRIVER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5761) अणु
		req = TG3_APE_LOCK_REQ;
		gnt = TG3_APE_LOCK_GRANT;
	पूर्ण अन्यथा अणु
		req = TG3_APE_PER_LOCK_REQ;
		gnt = TG3_APE_PER_LOCK_GRANT;
	पूर्ण

	off = 4 * locknum;

	tg3_ape_ग_लिखो32(tp, req + off, bit);

	/* Wait क्रम up to 1 millisecond to acquire lock. */
	क्रम (i = 0; i < 100; i++) अणु
		status = tg3_ape_पढ़ो32(tp, gnt + off);
		अगर (status == bit)
			अवरोध;
		अगर (pci_channel_offline(tp->pdev))
			अवरोध;

		udelay(10);
	पूर्ण

	अगर (status != bit) अणु
		/* Revoke the lock request. */
		tg3_ape_ग_लिखो32(tp, gnt + off, bit);
		ret = -EBUSY;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम tg3_ape_unlock(काष्ठा tg3 *tp, पूर्णांक locknum)
अणु
	u32 gnt, bit;

	अगर (!tg3_flag(tp, ENABLE_APE))
		वापस;

	चयन (locknum) अणु
	हाल TG3_APE_LOCK_GPIO:
		अगर (tg3_asic_rev(tp) == ASIC_REV_5761)
			वापस;
		fallthrough;
	हाल TG3_APE_LOCK_GRC:
	हाल TG3_APE_LOCK_MEM:
		अगर (!tp->pci_fn)
			bit = APE_LOCK_GRANT_DRIVER;
		अन्यथा
			bit = 1 << tp->pci_fn;
		अवरोध;
	हाल TG3_APE_LOCK_PHY0:
	हाल TG3_APE_LOCK_PHY1:
	हाल TG3_APE_LOCK_PHY2:
	हाल TG3_APE_LOCK_PHY3:
		bit = APE_LOCK_GRANT_DRIVER;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5761)
		gnt = TG3_APE_LOCK_GRANT;
	अन्यथा
		gnt = TG3_APE_PER_LOCK_GRANT;

	tg3_ape_ग_लिखो32(tp, gnt + 4 * locknum, bit);
पूर्ण

अटल पूर्णांक tg3_ape_event_lock(काष्ठा tg3 *tp, u32 समयout_us)
अणु
	u32 apedata;

	जबतक (समयout_us) अणु
		अगर (tg3_ape_lock(tp, TG3_APE_LOCK_MEM))
			वापस -EBUSY;

		apedata = tg3_ape_पढ़ो32(tp, TG3_APE_EVENT_STATUS);
		अगर (!(apedata & APE_EVENT_STATUS_EVENT_PENDING))
			अवरोध;

		tg3_ape_unlock(tp, TG3_APE_LOCK_MEM);

		udelay(10);
		समयout_us -= (समयout_us > 10) ? 10 : समयout_us;
	पूर्ण

	वापस समयout_us ? 0 : -EBUSY;
पूर्ण

#अगर_घोषित CONFIG_TIGON3_HWMON
अटल पूर्णांक tg3_ape_रुको_क्रम_event(काष्ठा tg3 *tp, u32 समयout_us)
अणु
	u32 i, apedata;

	क्रम (i = 0; i < समयout_us / 10; i++) अणु
		apedata = tg3_ape_पढ़ो32(tp, TG3_APE_EVENT_STATUS);

		अगर (!(apedata & APE_EVENT_STATUS_EVENT_PENDING))
			अवरोध;

		udelay(10);
	पूर्ण

	वापस i == समयout_us / 10;
पूर्ण

अटल पूर्णांक tg3_ape_scratchpad_पढ़ो(काष्ठा tg3 *tp, u32 *data, u32 base_off,
				   u32 len)
अणु
	पूर्णांक err;
	u32 i, bufoff, msgoff, maxlen, apedata;

	अगर (!tg3_flag(tp, APE_HAS_NCSI))
		वापस 0;

	apedata = tg3_ape_पढ़ो32(tp, TG3_APE_SEG_SIG);
	अगर (apedata != APE_SEG_SIG_MAGIC)
		वापस -ENODEV;

	apedata = tg3_ape_पढ़ो32(tp, TG3_APE_FW_STATUS);
	अगर (!(apedata & APE_FW_STATUS_READY))
		वापस -EAGAIN;

	bufoff = tg3_ape_पढ़ो32(tp, TG3_APE_SEG_MSG_BUF_OFF) +
		 TG3_APE_SHMEM_BASE;
	msgoff = bufoff + 2 * माप(u32);
	maxlen = tg3_ape_पढ़ो32(tp, TG3_APE_SEG_MSG_BUF_LEN);

	जबतक (len) अणु
		u32 length;

		/* Cap xfer sizes to scratchpad limits. */
		length = (len > maxlen) ? maxlen : len;
		len -= length;

		apedata = tg3_ape_पढ़ो32(tp, TG3_APE_FW_STATUS);
		अगर (!(apedata & APE_FW_STATUS_READY))
			वापस -EAGAIN;

		/* Wait क्रम up to 1 msec क्रम APE to service previous event. */
		err = tg3_ape_event_lock(tp, 1000);
		अगर (err)
			वापस err;

		apedata = APE_EVENT_STATUS_DRIVER_EVNT |
			  APE_EVENT_STATUS_SCRTCHPD_READ |
			  APE_EVENT_STATUS_EVENT_PENDING;
		tg3_ape_ग_लिखो32(tp, TG3_APE_EVENT_STATUS, apedata);

		tg3_ape_ग_लिखो32(tp, bufoff, base_off);
		tg3_ape_ग_लिखो32(tp, bufoff + माप(u32), length);

		tg3_ape_unlock(tp, TG3_APE_LOCK_MEM);
		tg3_ape_ग_लिखो32(tp, TG3_APE_EVENT, APE_EVENT_1);

		base_off += length;

		अगर (tg3_ape_रुको_क्रम_event(tp, 30000))
			वापस -EAGAIN;

		क्रम (i = 0; length; i += 4, length -= 4) अणु
			u32 val = tg3_ape_पढ़ो32(tp, msgoff + i);
			स_नकल(data, &val, माप(u32));
			data++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tg3_ape_send_event(काष्ठा tg3 *tp, u32 event)
अणु
	पूर्णांक err;
	u32 apedata;

	apedata = tg3_ape_पढ़ो32(tp, TG3_APE_SEG_SIG);
	अगर (apedata != APE_SEG_SIG_MAGIC)
		वापस -EAGAIN;

	apedata = tg3_ape_पढ़ो32(tp, TG3_APE_FW_STATUS);
	अगर (!(apedata & APE_FW_STATUS_READY))
		वापस -EAGAIN;

	/* Wait क्रम up to 20 millisecond क्रम APE to service previous event. */
	err = tg3_ape_event_lock(tp, 20000);
	अगर (err)
		वापस err;

	tg3_ape_ग_लिखो32(tp, TG3_APE_EVENT_STATUS,
			event | APE_EVENT_STATUS_EVENT_PENDING);

	tg3_ape_unlock(tp, TG3_APE_LOCK_MEM);
	tg3_ape_ग_लिखो32(tp, TG3_APE_EVENT, APE_EVENT_1);

	वापस 0;
पूर्ण

अटल व्योम tg3_ape_driver_state_change(काष्ठा tg3 *tp, पूर्णांक kind)
अणु
	u32 event;
	u32 apedata;

	अगर (!tg3_flag(tp, ENABLE_APE))
		वापस;

	चयन (kind) अणु
	हाल RESET_KIND_INIT:
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_HEARTBEAT_COUNT, tp->ape_hb++);
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_SEG_SIG,
				APE_HOST_SEG_SIG_MAGIC);
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_SEG_LEN,
				APE_HOST_SEG_LEN_MAGIC);
		apedata = tg3_ape_पढ़ो32(tp, TG3_APE_HOST_INIT_COUNT);
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_INIT_COUNT, ++apedata);
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_DRIVER_ID,
			APE_HOST_DRIVER_ID_MAGIC(TG3_MAJ_NUM, TG3_MIN_NUM));
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_BEHAVIOR,
				APE_HOST_BEHAV_NO_PHYLOCK);
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_DRVR_STATE,
				    TG3_APE_HOST_DRVR_STATE_START);

		event = APE_EVENT_STATUS_STATE_START;
		अवरोध;
	हाल RESET_KIND_SHUTDOWN:
		अगर (device_may_wakeup(&tp->pdev->dev) &&
		    tg3_flag(tp, WOL_ENABLE)) अणु
			tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_WOL_SPEED,
					    TG3_APE_HOST_WOL_SPEED_AUTO);
			apedata = TG3_APE_HOST_DRVR_STATE_WOL;
		पूर्ण अन्यथा
			apedata = TG3_APE_HOST_DRVR_STATE_UNLOAD;

		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_DRVR_STATE, apedata);

		event = APE_EVENT_STATUS_STATE_UNLOAD;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	event |= APE_EVENT_STATUS_DRIVER_EVNT | APE_EVENT_STATUS_STATE_CHNGE;

	tg3_ape_send_event(tp, event);
पूर्ण

अटल व्योम tg3_send_ape_heartbeat(काष्ठा tg3 *tp,
				   अचिन्हित दीर्घ पूर्णांकerval)
अणु
	/* Check अगर hb पूर्णांकerval has exceeded */
	अगर (!tg3_flag(tp, ENABLE_APE) ||
	    समय_beक्रमe(jअगरfies, tp->ape_hb_jअगरfies + पूर्णांकerval))
		वापस;

	tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_HEARTBEAT_COUNT, tp->ape_hb++);
	tp->ape_hb_jअगरfies = jअगरfies;
पूर्ण

अटल व्योम tg3_disable_पूर्णांकs(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	tw32(TG3PCI_MISC_HOST_CTRL,
	     (tp->misc_host_ctrl | MISC_HOST_CTRL_MASK_PCI_INT));
	क्रम (i = 0; i < tp->irq_max; i++)
		tw32_mailbox_f(tp->napi[i].पूर्णांक_mbox, 0x00000001);
पूर्ण

अटल व्योम tg3_enable_पूर्णांकs(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	tp->irq_sync = 0;
	wmb();

	tw32(TG3PCI_MISC_HOST_CTRL,
	     (tp->misc_host_ctrl & ~MISC_HOST_CTRL_MASK_PCI_INT));

	tp->coal_now = tp->coalesce_mode | HOSTCC_MODE_ENABLE;
	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		tw32_mailbox_f(tnapi->पूर्णांक_mbox, tnapi->last_tag << 24);
		अगर (tg3_flag(tp, 1SHOT_MSI))
			tw32_mailbox_f(tnapi->पूर्णांक_mbox, tnapi->last_tag << 24);

		tp->coal_now |= tnapi->coal_now;
	पूर्ण

	/* Force an initial पूर्णांकerrupt */
	अगर (!tg3_flag(tp, TAGGED_STATUS) &&
	    (tp->napi[0].hw_status->status & SD_STATUS_UPDATED))
		tw32(GRC_LOCAL_CTRL, tp->grc_local_ctrl | GRC_LCLCTRL_SETINT);
	अन्यथा
		tw32(HOSTCC_MODE, tp->coal_now);

	tp->coal_now &= ~(tp->napi[0].coal_now | tp->napi[1].coal_now);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tg3_has_work(काष्ठा tg3_napi *tnapi)
अणु
	काष्ठा tg3 *tp = tnapi->tp;
	काष्ठा tg3_hw_status *sblk = tnapi->hw_status;
	अचिन्हित पूर्णांक work_exists = 0;

	/* check क्रम phy events */
	अगर (!(tg3_flag(tp, USE_LINKCHG_REG) || tg3_flag(tp, POLL_SERDES))) अणु
		अगर (sblk->status & SD_STATUS_LINK_CHG)
			work_exists = 1;
	पूर्ण

	/* check क्रम TX work to करो */
	अगर (sblk->idx[0].tx_consumer != tnapi->tx_cons)
		work_exists = 1;

	/* check क्रम RX work to करो */
	अगर (tnapi->rx_rcb_prod_idx &&
	    *(tnapi->rx_rcb_prod_idx) != tnapi->rx_rcb_ptr)
		work_exists = 1;

	वापस work_exists;
पूर्ण

/* tg3_पूर्णांक_reenable
 *  similar to tg3_enable_पूर्णांकs, but it accurately determines whether there
 *  is new work pending and can वापस without flushing the PIO ग_लिखो
 *  which reenables पूर्णांकerrupts
 */
अटल व्योम tg3_पूर्णांक_reenable(काष्ठा tg3_napi *tnapi)
अणु
	काष्ठा tg3 *tp = tnapi->tp;

	tw32_mailbox(tnapi->पूर्णांक_mbox, tnapi->last_tag << 24);

	/* When करोing tagged status, this work check is unnecessary.
	 * The last_tag we ग_लिखो above tells the chip which piece of
	 * work we've completed.
	 */
	अगर (!tg3_flag(tp, TAGGED_STATUS) && tg3_has_work(tnapi))
		tw32(HOSTCC_MODE, tp->coalesce_mode |
		     HOSTCC_MODE_ENABLE | tnapi->coal_now);
पूर्ण

अटल व्योम tg3_चयन_घड़ीs(काष्ठा tg3 *tp)
अणु
	u32 घड़ी_ctrl;
	u32 orig_घड़ी_ctrl;

	अगर (tg3_flag(tp, CPMU_PRESENT) || tg3_flag(tp, 5780_CLASS))
		वापस;

	घड़ी_ctrl = tr32(TG3PCI_CLOCK_CTRL);

	orig_घड़ी_ctrl = घड़ी_ctrl;
	घड़ी_ctrl &= (CLOCK_CTRL_FORCE_CLKRUN |
		       CLOCK_CTRL_CLKRUN_OENABLE |
		       0x1f);
	tp->pci_घड़ी_ctrl = घड़ी_ctrl;

	अगर (tg3_flag(tp, 5705_PLUS)) अणु
		अगर (orig_घड़ी_ctrl & CLOCK_CTRL_625_CORE) अणु
			tw32_रुको_f(TG3PCI_CLOCK_CTRL,
				    घड़ी_ctrl | CLOCK_CTRL_625_CORE, 40);
		पूर्ण
	पूर्ण अन्यथा अगर ((orig_घड़ी_ctrl & CLOCK_CTRL_44MHZ_CORE) != 0) अणु
		tw32_रुको_f(TG3PCI_CLOCK_CTRL,
			    घड़ी_ctrl |
			    (CLOCK_CTRL_44MHZ_CORE | CLOCK_CTRL_ALTCLK),
			    40);
		tw32_रुको_f(TG3PCI_CLOCK_CTRL,
			    घड़ी_ctrl | (CLOCK_CTRL_ALTCLK),
			    40);
	पूर्ण
	tw32_रुको_f(TG3PCI_CLOCK_CTRL, घड़ी_ctrl, 40);
पूर्ण

#घोषणा PHY_BUSY_LOOPS	5000

अटल पूर्णांक __tg3_पढ़ोphy(काष्ठा tg3 *tp, अचिन्हित पूर्णांक phy_addr, पूर्णांक reg,
			 u32 *val)
अणु
	u32 frame_val;
	अचिन्हित पूर्णांक loops;
	पूर्णांक ret;

	अगर ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) अणु
		tw32_f(MAC_MI_MODE,
		     (tp->mi_mode & ~MAC_MI_MODE_AUTO_POLL));
		udelay(80);
	पूर्ण

	tg3_ape_lock(tp, tp->phy_ape_lock);

	*val = 0x0;

	frame_val  = ((phy_addr << MI_COM_PHY_ADDR_SHIFT) &
		      MI_COM_PHY_ADDR_MASK);
	frame_val |= ((reg << MI_COM_REG_ADDR_SHIFT) &
		      MI_COM_REG_ADDR_MASK);
	frame_val |= (MI_COM_CMD_READ | MI_COM_START);

	tw32_f(MAC_MI_COM, frame_val);

	loops = PHY_BUSY_LOOPS;
	जबतक (loops != 0) अणु
		udelay(10);
		frame_val = tr32(MAC_MI_COM);

		अगर ((frame_val & MI_COM_BUSY) == 0) अणु
			udelay(5);
			frame_val = tr32(MAC_MI_COM);
			अवरोध;
		पूर्ण
		loops -= 1;
	पूर्ण

	ret = -EBUSY;
	अगर (loops != 0) अणु
		*val = frame_val & MI_COM_DATA_MASK;
		ret = 0;
	पूर्ण

	अगर ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) अणु
		tw32_f(MAC_MI_MODE, tp->mi_mode);
		udelay(80);
	पूर्ण

	tg3_ape_unlock(tp, tp->phy_ape_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tg3_पढ़ोphy(काष्ठा tg3 *tp, पूर्णांक reg, u32 *val)
अणु
	वापस __tg3_पढ़ोphy(tp, tp->phy_addr, reg, val);
पूर्ण

अटल पूर्णांक __tg3_ग_लिखोphy(काष्ठा tg3 *tp, अचिन्हित पूर्णांक phy_addr, पूर्णांक reg,
			  u32 val)
अणु
	u32 frame_val;
	अचिन्हित पूर्णांक loops;
	पूर्णांक ret;

	अगर ((tp->phy_flags & TG3_PHYFLG_IS_FET) &&
	    (reg == MII_CTRL1000 || reg == MII_TG3_AUX_CTRL))
		वापस 0;

	अगर ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) अणु
		tw32_f(MAC_MI_MODE,
		     (tp->mi_mode & ~MAC_MI_MODE_AUTO_POLL));
		udelay(80);
	पूर्ण

	tg3_ape_lock(tp, tp->phy_ape_lock);

	frame_val  = ((phy_addr << MI_COM_PHY_ADDR_SHIFT) &
		      MI_COM_PHY_ADDR_MASK);
	frame_val |= ((reg << MI_COM_REG_ADDR_SHIFT) &
		      MI_COM_REG_ADDR_MASK);
	frame_val |= (val & MI_COM_DATA_MASK);
	frame_val |= (MI_COM_CMD_WRITE | MI_COM_START);

	tw32_f(MAC_MI_COM, frame_val);

	loops = PHY_BUSY_LOOPS;
	जबतक (loops != 0) अणु
		udelay(10);
		frame_val = tr32(MAC_MI_COM);
		अगर ((frame_val & MI_COM_BUSY) == 0) अणु
			udelay(5);
			frame_val = tr32(MAC_MI_COM);
			अवरोध;
		पूर्ण
		loops -= 1;
	पूर्ण

	ret = -EBUSY;
	अगर (loops != 0)
		ret = 0;

	अगर ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) अणु
		tw32_f(MAC_MI_MODE, tp->mi_mode);
		udelay(80);
	पूर्ण

	tg3_ape_unlock(tp, tp->phy_ape_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tg3_ग_लिखोphy(काष्ठा tg3 *tp, पूर्णांक reg, u32 val)
अणु
	वापस __tg3_ग_लिखोphy(tp, tp->phy_addr, reg, val);
पूर्ण

अटल पूर्णांक tg3_phy_cl45_ग_लिखो(काष्ठा tg3 *tp, u32 devad, u32 addr, u32 val)
अणु
	पूर्णांक err;

	err = tg3_ग_लिखोphy(tp, MII_TG3_MMD_CTRL, devad);
	अगर (err)
		जाओ करोne;

	err = tg3_ग_लिखोphy(tp, MII_TG3_MMD_ADDRESS, addr);
	अगर (err)
		जाओ करोne;

	err = tg3_ग_लिखोphy(tp, MII_TG3_MMD_CTRL,
			   MII_TG3_MMD_CTRL_DATA_NOINC | devad);
	अगर (err)
		जाओ करोne;

	err = tg3_ग_लिखोphy(tp, MII_TG3_MMD_ADDRESS, val);

करोne:
	वापस err;
पूर्ण

अटल पूर्णांक tg3_phy_cl45_पढ़ो(काष्ठा tg3 *tp, u32 devad, u32 addr, u32 *val)
अणु
	पूर्णांक err;

	err = tg3_ग_लिखोphy(tp, MII_TG3_MMD_CTRL, devad);
	अगर (err)
		जाओ करोne;

	err = tg3_ग_लिखोphy(tp, MII_TG3_MMD_ADDRESS, addr);
	अगर (err)
		जाओ करोne;

	err = tg3_ग_लिखोphy(tp, MII_TG3_MMD_CTRL,
			   MII_TG3_MMD_CTRL_DATA_NOINC | devad);
	अगर (err)
		जाओ करोne;

	err = tg3_पढ़ोphy(tp, MII_TG3_MMD_ADDRESS, val);

करोne:
	वापस err;
पूर्ण

अटल पूर्णांक tg3_phydsp_पढ़ो(काष्ठा tg3 *tp, u32 reg, u32 *val)
अणु
	पूर्णांक err;

	err = tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS, reg);
	अगर (!err)
		err = tg3_पढ़ोphy(tp, MII_TG3_DSP_RW_PORT, val);

	वापस err;
पूर्ण

अटल पूर्णांक tg3_phydsp_ग_लिखो(काष्ठा tg3 *tp, u32 reg, u32 val)
अणु
	पूर्णांक err;

	err = tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS, reg);
	अगर (!err)
		err = tg3_ग_लिखोphy(tp, MII_TG3_DSP_RW_PORT, val);

	वापस err;
पूर्ण

अटल पूर्णांक tg3_phy_auxctl_पढ़ो(काष्ठा tg3 *tp, पूर्णांक reg, u32 *val)
अणु
	पूर्णांक err;

	err = tg3_ग_लिखोphy(tp, MII_TG3_AUX_CTRL,
			   (reg << MII_TG3_AUXCTL_MISC_RDSEL_SHIFT) |
			   MII_TG3_AUXCTL_SHDWSEL_MISC);
	अगर (!err)
		err = tg3_पढ़ोphy(tp, MII_TG3_AUX_CTRL, val);

	वापस err;
पूर्ण

अटल पूर्णांक tg3_phy_auxctl_ग_लिखो(काष्ठा tg3 *tp, पूर्णांक reg, u32 set)
अणु
	अगर (reg == MII_TG3_AUXCTL_SHDWSEL_MISC)
		set |= MII_TG3_AUXCTL_MISC_WREN;

	वापस tg3_ग_लिखोphy(tp, MII_TG3_AUX_CTRL, set | reg);
पूर्ण

अटल पूर्णांक tg3_phy_toggle_auxctl_smdsp(काष्ठा tg3 *tp, bool enable)
अणु
	u32 val;
	पूर्णांक err;

	err = tg3_phy_auxctl_पढ़ो(tp, MII_TG3_AUXCTL_SHDWSEL_AUXCTL, &val);

	अगर (err)
		वापस err;

	अगर (enable)
		val |= MII_TG3_AUXCTL_ACTL_SMDSP_ENA;
	अन्यथा
		val &= ~MII_TG3_AUXCTL_ACTL_SMDSP_ENA;

	err = tg3_phy_auxctl_ग_लिखो((tp), MII_TG3_AUXCTL_SHDWSEL_AUXCTL,
				   val | MII_TG3_AUXCTL_ACTL_TX_6DB);

	वापस err;
पूर्ण

अटल पूर्णांक tg3_phy_shdw_ग_लिखो(काष्ठा tg3 *tp, पूर्णांक reg, u32 val)
अणु
	वापस tg3_ग_लिखोphy(tp, MII_TG3_MISC_SHDW,
			    reg | val | MII_TG3_MISC_SHDW_WREN);
पूर्ण

अटल पूर्णांक tg3_bmcr_reset(काष्ठा tg3 *tp)
अणु
	u32 phy_control;
	पूर्णांक limit, err;

	/* OK, reset it, and poll the BMCR_RESET bit until it
	 * clears or we समय out.
	 */
	phy_control = BMCR_RESET;
	err = tg3_ग_लिखोphy(tp, MII_BMCR, phy_control);
	अगर (err != 0)
		वापस -EBUSY;

	limit = 5000;
	जबतक (limit--) अणु
		err = tg3_पढ़ोphy(tp, MII_BMCR, &phy_control);
		अगर (err != 0)
			वापस -EBUSY;

		अगर ((phy_control & BMCR_RESET) == 0) अणु
			udelay(40);
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण
	अगर (limit < 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_mdio_पढ़ो(काष्ठा mii_bus *bp, पूर्णांक mii_id, पूर्णांक reg)
अणु
	काष्ठा tg3 *tp = bp->priv;
	u32 val;

	spin_lock_bh(&tp->lock);

	अगर (__tg3_पढ़ोphy(tp, mii_id, reg, &val))
		val = -EIO;

	spin_unlock_bh(&tp->lock);

	वापस val;
पूर्ण

अटल पूर्णांक tg3_mdio_ग_लिखो(काष्ठा mii_bus *bp, पूर्णांक mii_id, पूर्णांक reg, u16 val)
अणु
	काष्ठा tg3 *tp = bp->priv;
	u32 ret = 0;

	spin_lock_bh(&tp->lock);

	अगर (__tg3_ग_लिखोphy(tp, mii_id, reg, val))
		ret = -EIO;

	spin_unlock_bh(&tp->lock);

	वापस ret;
पूर्ण

अटल व्योम tg3_mdio_config_5785(काष्ठा tg3 *tp)
अणु
	u32 val;
	काष्ठा phy_device *phydev;

	phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);
	चयन (phydev->drv->phy_id & phydev->drv->phy_id_mask) अणु
	हाल PHY_ID_BCM50610:
	हाल PHY_ID_BCM50610M:
		val = MAC_PHYCFG2_50610_LED_MODES;
		अवरोध;
	हाल PHY_ID_BCMAC131:
		val = MAC_PHYCFG2_AC131_LED_MODES;
		अवरोध;
	हाल PHY_ID_RTL8211C:
		val = MAC_PHYCFG2_RTL8211C_LED_MODES;
		अवरोध;
	हाल PHY_ID_RTL8201E:
		val = MAC_PHYCFG2_RTL8201E_LED_MODES;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (phydev->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII) अणु
		tw32(MAC_PHYCFG2, val);

		val = tr32(MAC_PHYCFG1);
		val &= ~(MAC_PHYCFG1_RGMII_INT |
			 MAC_PHYCFG1_RXCLK_TO_MASK | MAC_PHYCFG1_TXCLK_TO_MASK);
		val |= MAC_PHYCFG1_RXCLK_TIMEOUT | MAC_PHYCFG1_TXCLK_TIMEOUT;
		tw32(MAC_PHYCFG1, val);

		वापस;
	पूर्ण

	अगर (!tg3_flag(tp, RGMII_INBAND_DISABLE))
		val |= MAC_PHYCFG2_EMODE_MASK_MASK |
		       MAC_PHYCFG2_FMODE_MASK_MASK |
		       MAC_PHYCFG2_GMODE_MASK_MASK |
		       MAC_PHYCFG2_ACT_MASK_MASK   |
		       MAC_PHYCFG2_QUAL_MASK_MASK |
		       MAC_PHYCFG2_INBAND_ENABLE;

	tw32(MAC_PHYCFG2, val);

	val = tr32(MAC_PHYCFG1);
	val &= ~(MAC_PHYCFG1_RXCLK_TO_MASK | MAC_PHYCFG1_TXCLK_TO_MASK |
		 MAC_PHYCFG1_RGMII_EXT_RX_DEC | MAC_PHYCFG1_RGMII_SND_STAT_EN);
	अगर (!tg3_flag(tp, RGMII_INBAND_DISABLE)) अणु
		अगर (tg3_flag(tp, RGMII_EXT_IBND_RX_EN))
			val |= MAC_PHYCFG1_RGMII_EXT_RX_DEC;
		अगर (tg3_flag(tp, RGMII_EXT_IBND_TX_EN))
			val |= MAC_PHYCFG1_RGMII_SND_STAT_EN;
	पूर्ण
	val |= MAC_PHYCFG1_RXCLK_TIMEOUT | MAC_PHYCFG1_TXCLK_TIMEOUT |
	       MAC_PHYCFG1_RGMII_INT | MAC_PHYCFG1_TXC_DRV;
	tw32(MAC_PHYCFG1, val);

	val = tr32(MAC_EXT_RGMII_MODE);
	val &= ~(MAC_RGMII_MODE_RX_INT_B |
		 MAC_RGMII_MODE_RX_QUALITY |
		 MAC_RGMII_MODE_RX_ACTIVITY |
		 MAC_RGMII_MODE_RX_ENG_DET |
		 MAC_RGMII_MODE_TX_ENABLE |
		 MAC_RGMII_MODE_TX_LOWPWR |
		 MAC_RGMII_MODE_TX_RESET);
	अगर (!tg3_flag(tp, RGMII_INBAND_DISABLE)) अणु
		अगर (tg3_flag(tp, RGMII_EXT_IBND_RX_EN))
			val |= MAC_RGMII_MODE_RX_INT_B |
			       MAC_RGMII_MODE_RX_QUALITY |
			       MAC_RGMII_MODE_RX_ACTIVITY |
			       MAC_RGMII_MODE_RX_ENG_DET;
		अगर (tg3_flag(tp, RGMII_EXT_IBND_TX_EN))
			val |= MAC_RGMII_MODE_TX_ENABLE |
			       MAC_RGMII_MODE_TX_LOWPWR |
			       MAC_RGMII_MODE_TX_RESET;
	पूर्ण
	tw32(MAC_EXT_RGMII_MODE, val);
पूर्ण

अटल व्योम tg3_mdio_start(काष्ठा tg3 *tp)
अणु
	tp->mi_mode &= ~MAC_MI_MODE_AUTO_POLL;
	tw32_f(MAC_MI_MODE, tp->mi_mode);
	udelay(80);

	अगर (tg3_flag(tp, MDIOBUS_INITED) &&
	    tg3_asic_rev(tp) == ASIC_REV_5785)
		tg3_mdio_config_5785(tp);
पूर्ण

अटल पूर्णांक tg3_mdio_init(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	u32 reg;
	काष्ठा phy_device *phydev;

	अगर (tg3_flag(tp, 5717_PLUS)) अणु
		u32 is_serdes;

		tp->phy_addr = tp->pci_fn + 1;

		अगर (tg3_chip_rev_id(tp) != CHIPREV_ID_5717_A0)
			is_serdes = tr32(SG_DIG_STATUS) & SG_DIG_IS_SERDES;
		अन्यथा
			is_serdes = tr32(TG3_CPMU_PHY_STRAP) &
				    TG3_CPMU_PHY_STRAP_IS_SERDES;
		अगर (is_serdes)
			tp->phy_addr += 7;
	पूर्ण अन्यथा अगर (tg3_flag(tp, IS_SSB_CORE) && tg3_flag(tp, ROBOSWITCH)) अणु
		पूर्णांक addr;

		addr = ssb_gige_get_phyaddr(tp->pdev);
		अगर (addr < 0)
			वापस addr;
		tp->phy_addr = addr;
	पूर्ण अन्यथा
		tp->phy_addr = TG3_PHY_MII_ADDR;

	tg3_mdio_start(tp);

	अगर (!tg3_flag(tp, USE_PHYLIB) || tg3_flag(tp, MDIOBUS_INITED))
		वापस 0;

	tp->mdio_bus = mdiobus_alloc();
	अगर (tp->mdio_bus == शून्य)
		वापस -ENOMEM;

	tp->mdio_bus->name     = "tg3 mdio bus";
	snम_लिखो(tp->mdio_bus->id, MII_BUS_ID_SIZE, "%x",
		 (tp->pdev->bus->number << 8) | tp->pdev->devfn);
	tp->mdio_bus->priv     = tp;
	tp->mdio_bus->parent   = &tp->pdev->dev;
	tp->mdio_bus->पढ़ो     = &tg3_mdio_पढ़ो;
	tp->mdio_bus->ग_लिखो    = &tg3_mdio_ग_लिखो;
	tp->mdio_bus->phy_mask = ~(1 << tp->phy_addr);

	/* The bus registration will look क्रम all the PHYs on the mdio bus.
	 * Unक्रमtunately, it करोes not ensure the PHY is घातered up beक्रमe
	 * accessing the PHY ID रेजिस्टरs.  A chip reset is the
	 * quickest way to bring the device back to an operational state..
	 */
	अगर (tg3_पढ़ोphy(tp, MII_BMCR, &reg) || (reg & BMCR_PDOWN))
		tg3_bmcr_reset(tp);

	i = mdiobus_रेजिस्टर(tp->mdio_bus);
	अगर (i) अणु
		dev_warn(&tp->pdev->dev, "mdiobus_reg failed (0x%x)\n", i);
		mdiobus_मुक्त(tp->mdio_bus);
		वापस i;
	पूर्ण

	phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

	अगर (!phydev || !phydev->drv) अणु
		dev_warn(&tp->pdev->dev, "No PHY devices\n");
		mdiobus_unरेजिस्टर(tp->mdio_bus);
		mdiobus_मुक्त(tp->mdio_bus);
		वापस -ENODEV;
	पूर्ण

	चयन (phydev->drv->phy_id & phydev->drv->phy_id_mask) अणु
	हाल PHY_ID_BCM57780:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_GMII;
		phydev->dev_flags |= PHY_BRCM_AUTO_PWRDWN_ENABLE;
		अवरोध;
	हाल PHY_ID_BCM50610:
	हाल PHY_ID_BCM50610M:
		phydev->dev_flags |= PHY_BRCM_CLEAR_RGMII_MODE |
				     PHY_BRCM_RX_REFCLK_UNUSED |
				     PHY_BRCM_DIS_TXCRXC_NOENRGY |
				     PHY_BRCM_AUTO_PWRDWN_ENABLE;
		fallthrough;
	हाल PHY_ID_RTL8211C:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_RGMII;
		अवरोध;
	हाल PHY_ID_RTL8201E:
	हाल PHY_ID_BCMAC131:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_MII;
		phydev->dev_flags |= PHY_BRCM_AUTO_PWRDWN_ENABLE;
		tp->phy_flags |= TG3_PHYFLG_IS_FET;
		अवरोध;
	पूर्ण

	tg3_flag_set(tp, MDIOBUS_INITED);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5785)
		tg3_mdio_config_5785(tp);

	वापस 0;
पूर्ण

अटल व्योम tg3_mdio_fini(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, MDIOBUS_INITED)) अणु
		tg3_flag_clear(tp, MDIOBUS_INITED);
		mdiobus_unरेजिस्टर(tp->mdio_bus);
		mdiobus_मुक्त(tp->mdio_bus);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल अंतरभूत व्योम tg3_generate_fw_event(काष्ठा tg3 *tp)
अणु
	u32 val;

	val = tr32(GRC_RX_CPU_EVENT);
	val |= GRC_RX_CPU_DRIVER_EVENT;
	tw32_f(GRC_RX_CPU_EVENT, val);

	tp->last_event_jअगरfies = jअगरfies;
पूर्ण

#घोषणा TG3_FW_EVENT_TIMEOUT_USEC 2500

/* tp->lock is held. */
अटल व्योम tg3_रुको_क्रम_event_ack(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक delay_cnt;
	दीर्घ समय_reमुख्य;

	/* If enough समय has passed, no रुको is necessary. */
	समय_reमुख्य = (दीर्घ)(tp->last_event_jअगरfies + 1 +
		      usecs_to_jअगरfies(TG3_FW_EVENT_TIMEOUT_USEC)) -
		      (दीर्घ)jअगरfies;
	अगर (समय_reमुख्य < 0)
		वापस;

	/* Check अगर we can लघुen the रुको समय. */
	delay_cnt = jअगरfies_to_usecs(समय_reमुख्य);
	अगर (delay_cnt > TG3_FW_EVENT_TIMEOUT_USEC)
		delay_cnt = TG3_FW_EVENT_TIMEOUT_USEC;
	delay_cnt = (delay_cnt >> 3) + 1;

	क्रम (i = 0; i < delay_cnt; i++) अणु
		अगर (!(tr32(GRC_RX_CPU_EVENT) & GRC_RX_CPU_DRIVER_EVENT))
			अवरोध;
		अगर (pci_channel_offline(tp->pdev))
			अवरोध;

		udelay(8);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_phy_gather_ump_data(काष्ठा tg3 *tp, u32 *data)
अणु
	u32 reg, val;

	val = 0;
	अगर (!tg3_पढ़ोphy(tp, MII_BMCR, &reg))
		val = reg << 16;
	अगर (!tg3_पढ़ोphy(tp, MII_BMSR, &reg))
		val |= (reg & 0xffff);
	*data++ = val;

	val = 0;
	अगर (!tg3_पढ़ोphy(tp, MII_ADVERTISE, &reg))
		val = reg << 16;
	अगर (!tg3_पढ़ोphy(tp, MII_LPA, &reg))
		val |= (reg & 0xffff);
	*data++ = val;

	val = 0;
	अगर (!(tp->phy_flags & TG3_PHYFLG_MII_SERDES)) अणु
		अगर (!tg3_पढ़ोphy(tp, MII_CTRL1000, &reg))
			val = reg << 16;
		अगर (!tg3_पढ़ोphy(tp, MII_STAT1000, &reg))
			val |= (reg & 0xffff);
	पूर्ण
	*data++ = val;

	अगर (!tg3_पढ़ोphy(tp, MII_PHYADDR, &reg))
		val = reg << 16;
	अन्यथा
		val = 0;
	*data++ = val;
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_ump_link_report(काष्ठा tg3 *tp)
अणु
	u32 data[4];

	अगर (!tg3_flag(tp, 5780_CLASS) || !tg3_flag(tp, ENABLE_ASF))
		वापस;

	tg3_phy_gather_ump_data(tp, data);

	tg3_रुको_क्रम_event_ack(tp);

	tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_MBOX, FWCMD_NICDRV_LINK_UPDATE);
	tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_LEN_MBOX, 14);
	tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_DATA_MBOX + 0x0, data[0]);
	tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_DATA_MBOX + 0x4, data[1]);
	tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_DATA_MBOX + 0x8, data[2]);
	tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_DATA_MBOX + 0xc, data[3]);

	tg3_generate_fw_event(tp);
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_stop_fw(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, ENABLE_ASF) && !tg3_flag(tp, ENABLE_APE)) अणु
		/* Wait क्रम RX cpu to ACK the previous event. */
		tg3_रुको_क्रम_event_ack(tp);

		tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_MBOX, FWCMD_NICDRV_PAUSE_FW);

		tg3_generate_fw_event(tp);

		/* Wait क्रम RX cpu to ACK this event. */
		tg3_रुको_क्रम_event_ack(tp);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_ग_लिखो_sig_pre_reset(काष्ठा tg3 *tp, पूर्णांक kind)
अणु
	tg3_ग_लिखो_mem(tp, NIC_SRAM_FIRMWARE_MBOX,
		      NIC_SRAM_FIRMWARE_MBOX_MAGIC1);

	अगर (tg3_flag(tp, ASF_NEW_HANDSHAKE)) अणु
		चयन (kind) अणु
		हाल RESET_KIND_INIT:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_START);
			अवरोध;

		हाल RESET_KIND_SHUTDOWN:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_UNLOAD);
			अवरोध;

		हाल RESET_KIND_SUSPEND:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_SUSPEND);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_ग_लिखो_sig_post_reset(काष्ठा tg3 *tp, पूर्णांक kind)
अणु
	अगर (tg3_flag(tp, ASF_NEW_HANDSHAKE)) अणु
		चयन (kind) अणु
		हाल RESET_KIND_INIT:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_START_DONE);
			अवरोध;

		हाल RESET_KIND_SHUTDOWN:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_UNLOAD_DONE);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_ग_लिखो_sig_legacy(काष्ठा tg3 *tp, पूर्णांक kind)
अणु
	अगर (tg3_flag(tp, ENABLE_ASF)) अणु
		चयन (kind) अणु
		हाल RESET_KIND_INIT:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_START);
			अवरोध;

		हाल RESET_KIND_SHUTDOWN:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_UNLOAD);
			अवरोध;

		हाल RESET_KIND_SUSPEND:
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_DRV_STATE_MBOX,
				      DRV_STATE_SUSPEND);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_poll_fw(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	u32 val;

	अगर (tg3_flag(tp, NO_FWARE_REPORTED))
		वापस 0;

	अगर (tg3_flag(tp, IS_SSB_CORE)) अणु
		/* We करोn't use firmware. */
		वापस 0;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		/* Wait up to 20ms क्रम init करोne. */
		क्रम (i = 0; i < 200; i++) अणु
			अगर (tr32(VCPU_STATUS) & VCPU_STATUS_INIT_DONE)
				वापस 0;
			अगर (pci_channel_offline(tp->pdev))
				वापस -ENODEV;

			udelay(100);
		पूर्ण
		वापस -ENODEV;
	पूर्ण

	/* Wait क्रम firmware initialization to complete. */
	क्रम (i = 0; i < 100000; i++) अणु
		tg3_पढ़ो_mem(tp, NIC_SRAM_FIRMWARE_MBOX, &val);
		अगर (val == ~NIC_SRAM_FIRMWARE_MBOX_MAGIC1)
			अवरोध;
		अगर (pci_channel_offline(tp->pdev)) अणु
			अगर (!tg3_flag(tp, NO_FWARE_REPORTED)) अणु
				tg3_flag_set(tp, NO_FWARE_REPORTED);
				netdev_info(tp->dev, "No firmware running\n");
			पूर्ण

			अवरोध;
		पूर्ण

		udelay(10);
	पूर्ण

	/* Chip might not be fitted with firmware.  Some Sun onboard
	 * parts are configured like that.  So करोn't संकेत the समयout
	 * of the above loop as an error, but करो report the lack of
	 * running firmware once.
	 */
	अगर (i >= 100000 && !tg3_flag(tp, NO_FWARE_REPORTED)) अणु
		tg3_flag_set(tp, NO_FWARE_REPORTED);

		netdev_info(tp->dev, "No firmware running\n");
	पूर्ण

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_57765_A0) अणु
		/* The 57765 A0 needs a little more
		 * समय to करो some important work.
		 */
		mdelay(10);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tg3_link_report(काष्ठा tg3 *tp)
अणु
	अगर (!netअगर_carrier_ok(tp->dev)) अणु
		netअगर_info(tp, link, tp->dev, "Link is down\n");
		tg3_ump_link_report(tp);
	पूर्ण अन्यथा अगर (netअगर_msg_link(tp)) अणु
		netdev_info(tp->dev, "Link is up at %d Mbps, %s duplex\n",
			    (tp->link_config.active_speed == SPEED_1000 ?
			     1000 :
			     (tp->link_config.active_speed == SPEED_100 ?
			      100 : 10)),
			    (tp->link_config.active_duplex == DUPLEX_FULL ?
			     "full" : "half"));

		netdev_info(tp->dev, "Flow control is %s for TX and %s for RX\n",
			    (tp->link_config.active_flowctrl & FLOW_CTRL_TX) ?
			    "on" : "off",
			    (tp->link_config.active_flowctrl & FLOW_CTRL_RX) ?
			    "on" : "off");

		अगर (tp->phy_flags & TG3_PHYFLG_EEE_CAP)
			netdev_info(tp->dev, "EEE is %s\n",
				    tp->setlpicnt ? "enabled" : "disabled");

		tg3_ump_link_report(tp);
	पूर्ण

	tp->link_up = netअगर_carrier_ok(tp->dev);
पूर्ण

अटल u32 tg3_decode_flowctrl_1000T(u32 adv)
अणु
	u32 flowctrl = 0;

	अगर (adv & ADVERTISE_PAUSE_CAP) अणु
		flowctrl |= FLOW_CTRL_RX;
		अगर (!(adv & ADVERTISE_PAUSE_ASYM))
			flowctrl |= FLOW_CTRL_TX;
	पूर्ण अन्यथा अगर (adv & ADVERTISE_PAUSE_ASYM)
		flowctrl |= FLOW_CTRL_TX;

	वापस flowctrl;
पूर्ण

अटल u16 tg3_advert_flowctrl_1000X(u8 flow_ctrl)
अणु
	u16 miireg;

	अगर ((flow_ctrl & FLOW_CTRL_TX) && (flow_ctrl & FLOW_CTRL_RX))
		miireg = ADVERTISE_1000XPAUSE;
	अन्यथा अगर (flow_ctrl & FLOW_CTRL_TX)
		miireg = ADVERTISE_1000XPSE_ASYM;
	अन्यथा अगर (flow_ctrl & FLOW_CTRL_RX)
		miireg = ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM;
	अन्यथा
		miireg = 0;

	वापस miireg;
पूर्ण

अटल u32 tg3_decode_flowctrl_1000X(u32 adv)
अणु
	u32 flowctrl = 0;

	अगर (adv & ADVERTISE_1000XPAUSE) अणु
		flowctrl |= FLOW_CTRL_RX;
		अगर (!(adv & ADVERTISE_1000XPSE_ASYM))
			flowctrl |= FLOW_CTRL_TX;
	पूर्ण अन्यथा अगर (adv & ADVERTISE_1000XPSE_ASYM)
		flowctrl |= FLOW_CTRL_TX;

	वापस flowctrl;
पूर्ण

अटल u8 tg3_resolve_flowctrl_1000X(u16 lcladv, u16 rmtadv)
अणु
	u8 cap = 0;

	अगर (lcladv & rmtadv & ADVERTISE_1000XPAUSE) अणु
		cap = FLOW_CTRL_TX | FLOW_CTRL_RX;
	पूर्ण अन्यथा अगर (lcladv & rmtadv & ADVERTISE_1000XPSE_ASYM) अणु
		अगर (lcladv & ADVERTISE_1000XPAUSE)
			cap = FLOW_CTRL_RX;
		अगर (rmtadv & ADVERTISE_1000XPAUSE)
			cap = FLOW_CTRL_TX;
	पूर्ण

	वापस cap;
पूर्ण

अटल व्योम tg3_setup_flow_control(काष्ठा tg3 *tp, u32 lcladv, u32 rmtadv)
अणु
	u8 स्वतःneg;
	u8 flowctrl = 0;
	u32 old_rx_mode = tp->rx_mode;
	u32 old_tx_mode = tp->tx_mode;

	अगर (tg3_flag(tp, USE_PHYLIB))
		स्वतःneg = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr)->स्वतःneg;
	अन्यथा
		स्वतःneg = tp->link_config.स्वतःneg;

	अगर (स्वतःneg == AUTONEG_ENABLE && tg3_flag(tp, PAUSE_AUTONEG)) अणु
		अगर (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
			flowctrl = tg3_resolve_flowctrl_1000X(lcladv, rmtadv);
		अन्यथा
			flowctrl = mii_resolve_flowctrl_fdx(lcladv, rmtadv);
	पूर्ण अन्यथा
		flowctrl = tp->link_config.flowctrl;

	tp->link_config.active_flowctrl = flowctrl;

	अगर (flowctrl & FLOW_CTRL_RX)
		tp->rx_mode |= RX_MODE_FLOW_CTRL_ENABLE;
	अन्यथा
		tp->rx_mode &= ~RX_MODE_FLOW_CTRL_ENABLE;

	अगर (old_rx_mode != tp->rx_mode)
		tw32_f(MAC_RX_MODE, tp->rx_mode);

	अगर (flowctrl & FLOW_CTRL_TX)
		tp->tx_mode |= TX_MODE_FLOW_CTRL_ENABLE;
	अन्यथा
		tp->tx_mode &= ~TX_MODE_FLOW_CTRL_ENABLE;

	अगर (old_tx_mode != tp->tx_mode)
		tw32_f(MAC_TX_MODE, tp->tx_mode);
पूर्ण

अटल व्योम tg3_adjust_link(काष्ठा net_device *dev)
अणु
	u8 oldflowctrl, linkmesg = 0;
	u32 mac_mode, lcl_adv, rmt_adv;
	काष्ठा tg3 *tp = netdev_priv(dev);
	काष्ठा phy_device *phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

	spin_lock_bh(&tp->lock);

	mac_mode = tp->mac_mode & ~(MAC_MODE_PORT_MODE_MASK |
				    MAC_MODE_HALF_DUPLEX);

	oldflowctrl = tp->link_config.active_flowctrl;

	अगर (phydev->link) अणु
		lcl_adv = 0;
		rmt_adv = 0;

		अगर (phydev->speed == SPEED_100 || phydev->speed == SPEED_10)
			mac_mode |= MAC_MODE_PORT_MODE_MII;
		अन्यथा अगर (phydev->speed == SPEED_1000 ||
			 tg3_asic_rev(tp) != ASIC_REV_5785)
			mac_mode |= MAC_MODE_PORT_MODE_GMII;
		अन्यथा
			mac_mode |= MAC_MODE_PORT_MODE_MII;

		अगर (phydev->duplex == DUPLEX_HALF)
			mac_mode |= MAC_MODE_HALF_DUPLEX;
		अन्यथा अणु
			lcl_adv = mii_advertise_flowctrl(
				  tp->link_config.flowctrl);

			अगर (phydev->छोड़ो)
				rmt_adv = LPA_PAUSE_CAP;
			अगर (phydev->asym_छोड़ो)
				rmt_adv |= LPA_PAUSE_ASYM;
		पूर्ण

		tg3_setup_flow_control(tp, lcl_adv, rmt_adv);
	पूर्ण अन्यथा
		mac_mode |= MAC_MODE_PORT_MODE_GMII;

	अगर (mac_mode != tp->mac_mode) अणु
		tp->mac_mode = mac_mode;
		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5785) अणु
		अगर (phydev->speed == SPEED_10)
			tw32(MAC_MI_STAT,
			     MAC_MI_STAT_10MBPS_MODE |
			     MAC_MI_STAT_LNKSTAT_ATTN_ENAB);
		अन्यथा
			tw32(MAC_MI_STAT, MAC_MI_STAT_LNKSTAT_ATTN_ENAB);
	पूर्ण

	अगर (phydev->speed == SPEED_1000 && phydev->duplex == DUPLEX_HALF)
		tw32(MAC_TX_LENGTHS,
		     ((2 << TX_LENGTHS_IPG_CRS_SHIFT) |
		      (6 << TX_LENGTHS_IPG_SHIFT) |
		      (0xff << TX_LENGTHS_SLOT_TIME_SHIFT)));
	अन्यथा
		tw32(MAC_TX_LENGTHS,
		     ((2 << TX_LENGTHS_IPG_CRS_SHIFT) |
		      (6 << TX_LENGTHS_IPG_SHIFT) |
		      (32 << TX_LENGTHS_SLOT_TIME_SHIFT)));

	अगर (phydev->link != tp->old_link ||
	    phydev->speed != tp->link_config.active_speed ||
	    phydev->duplex != tp->link_config.active_duplex ||
	    oldflowctrl != tp->link_config.active_flowctrl)
		linkmesg = 1;

	tp->old_link = phydev->link;
	tp->link_config.active_speed = phydev->speed;
	tp->link_config.active_duplex = phydev->duplex;

	spin_unlock_bh(&tp->lock);

	अगर (linkmesg)
		tg3_link_report(tp);
पूर्ण

अटल पूर्णांक tg3_phy_init(काष्ठा tg3 *tp)
अणु
	काष्ठा phy_device *phydev;

	अगर (tp->phy_flags & TG3_PHYFLG_IS_CONNECTED)
		वापस 0;

	/* Bring the PHY back to a known state. */
	tg3_bmcr_reset(tp);

	phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

	/* Attach the MAC to the PHY. */
	phydev = phy_connect(tp->dev, phydev_name(phydev),
			     tg3_adjust_link, phydev->पूर्णांकerface);
	अगर (IS_ERR(phydev)) अणु
		dev_err(&tp->pdev->dev, "Could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	/* Mask with MAC supported features. */
	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_GMII:
	हाल PHY_INTERFACE_MODE_RGMII:
		अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) अणु
			phy_set_max_speed(phydev, SPEED_1000);
			phy_support_asym_छोड़ो(phydev);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल PHY_INTERFACE_MODE_MII:
		phy_set_max_speed(phydev, SPEED_100);
		phy_support_asym_छोड़ो(phydev);
		अवरोध;
	शेष:
		phy_disconnect(mdiobus_get_phy(tp->mdio_bus, tp->phy_addr));
		वापस -EINVAL;
	पूर्ण

	tp->phy_flags |= TG3_PHYFLG_IS_CONNECTED;

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

अटल व्योम tg3_phy_start(काष्ठा tg3 *tp)
अणु
	काष्ठा phy_device *phydev;

	अगर (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
		वापस;

	phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

	अगर (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER) अणु
		tp->phy_flags &= ~TG3_PHYFLG_IS_LOW_POWER;
		phydev->speed = tp->link_config.speed;
		phydev->duplex = tp->link_config.duplex;
		phydev->स्वतःneg = tp->link_config.स्वतःneg;
		ethtool_convert_legacy_u32_to_link_mode(
			phydev->advertising, tp->link_config.advertising);
	पूर्ण

	phy_start(phydev);

	phy_start_aneg(phydev);
पूर्ण

अटल व्योम tg3_phy_stop(काष्ठा tg3 *tp)
अणु
	अगर (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
		वापस;

	phy_stop(mdiobus_get_phy(tp->mdio_bus, tp->phy_addr));
पूर्ण

अटल व्योम tg3_phy_fini(काष्ठा tg3 *tp)
अणु
	अगर (tp->phy_flags & TG3_PHYFLG_IS_CONNECTED) अणु
		phy_disconnect(mdiobus_get_phy(tp->mdio_bus, tp->phy_addr));
		tp->phy_flags &= ~TG3_PHYFLG_IS_CONNECTED;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_phy_set_extloopbk(काष्ठा tg3 *tp)
अणु
	पूर्णांक err;
	u32 val;

	अगर (tp->phy_flags & TG3_PHYFLG_IS_FET)
		वापस 0;

	अगर ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5401) अणु
		/* Cannot करो पढ़ो-modअगरy-ग_लिखो on 5401 */
		err = tg3_phy_auxctl_ग_लिखो(tp,
					   MII_TG3_AUXCTL_SHDWSEL_AUXCTL,
					   MII_TG3_AUXCTL_ACTL_EXTLOOPBK |
					   0x4c20);
		जाओ करोne;
	पूर्ण

	err = tg3_phy_auxctl_पढ़ो(tp,
				  MII_TG3_AUXCTL_SHDWSEL_AUXCTL, &val);
	अगर (err)
		वापस err;

	val |= MII_TG3_AUXCTL_ACTL_EXTLOOPBK;
	err = tg3_phy_auxctl_ग_लिखो(tp,
				   MII_TG3_AUXCTL_SHDWSEL_AUXCTL, val);

करोne:
	वापस err;
पूर्ण

अटल व्योम tg3_phy_fet_toggle_apd(काष्ठा tg3 *tp, bool enable)
अणु
	u32 phytest;

	अगर (!tg3_पढ़ोphy(tp, MII_TG3_FET_TEST, &phytest)) अणु
		u32 phy;

		tg3_ग_लिखोphy(tp, MII_TG3_FET_TEST,
			     phytest | MII_TG3_FET_SHADOW_EN);
		अगर (!tg3_पढ़ोphy(tp, MII_TG3_FET_SHDW_AUXSTAT2, &phy)) अणु
			अगर (enable)
				phy |= MII_TG3_FET_SHDW_AUXSTAT2_APD;
			अन्यथा
				phy &= ~MII_TG3_FET_SHDW_AUXSTAT2_APD;
			tg3_ग_लिखोphy(tp, MII_TG3_FET_SHDW_AUXSTAT2, phy);
		पूर्ण
		tg3_ग_लिखोphy(tp, MII_TG3_FET_TEST, phytest);
	पूर्ण
पूर्ण

अटल व्योम tg3_phy_toggle_apd(काष्ठा tg3 *tp, bool enable)
अणु
	u32 reg;

	अगर (!tg3_flag(tp, 5705_PLUS) ||
	    (tg3_flag(tp, 5717_PLUS) &&
	     (tp->phy_flags & TG3_PHYFLG_MII_SERDES)))
		वापस;

	अगर (tp->phy_flags & TG3_PHYFLG_IS_FET) अणु
		tg3_phy_fet_toggle_apd(tp, enable);
		वापस;
	पूर्ण

	reg = MII_TG3_MISC_SHDW_SCR5_LPED |
	      MII_TG3_MISC_SHDW_SCR5_DLPTLM |
	      MII_TG3_MISC_SHDW_SCR5_SDTL |
	      MII_TG3_MISC_SHDW_SCR5_C125OE;
	अगर (tg3_asic_rev(tp) != ASIC_REV_5784 || !enable)
		reg |= MII_TG3_MISC_SHDW_SCR5_DLLAPD;

	tg3_phy_shdw_ग_लिखो(tp, MII_TG3_MISC_SHDW_SCR5_SEL, reg);


	reg = MII_TG3_MISC_SHDW_APD_WKTM_84MS;
	अगर (enable)
		reg |= MII_TG3_MISC_SHDW_APD_ENABLE;

	tg3_phy_shdw_ग_लिखो(tp, MII_TG3_MISC_SHDW_APD_SEL, reg);
पूर्ण

अटल व्योम tg3_phy_toggle_स्वतःmdix(काष्ठा tg3 *tp, bool enable)
अणु
	u32 phy;

	अगर (!tg3_flag(tp, 5705_PLUS) ||
	    (tp->phy_flags & TG3_PHYFLG_ANY_SERDES))
		वापस;

	अगर (tp->phy_flags & TG3_PHYFLG_IS_FET) अणु
		u32 ephy;

		अगर (!tg3_पढ़ोphy(tp, MII_TG3_FET_TEST, &ephy)) अणु
			u32 reg = MII_TG3_FET_SHDW_MISCCTRL;

			tg3_ग_लिखोphy(tp, MII_TG3_FET_TEST,
				     ephy | MII_TG3_FET_SHADOW_EN);
			अगर (!tg3_पढ़ोphy(tp, reg, &phy)) अणु
				अगर (enable)
					phy |= MII_TG3_FET_SHDW_MISCCTRL_MDIX;
				अन्यथा
					phy &= ~MII_TG3_FET_SHDW_MISCCTRL_MDIX;
				tg3_ग_लिखोphy(tp, reg, phy);
			पूर्ण
			tg3_ग_लिखोphy(tp, MII_TG3_FET_TEST, ephy);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		ret = tg3_phy_auxctl_पढ़ो(tp,
					  MII_TG3_AUXCTL_SHDWSEL_MISC, &phy);
		अगर (!ret) अणु
			अगर (enable)
				phy |= MII_TG3_AUXCTL_MISC_FORCE_AMDIX;
			अन्यथा
				phy &= ~MII_TG3_AUXCTL_MISC_FORCE_AMDIX;
			tg3_phy_auxctl_ग_लिखो(tp,
					     MII_TG3_AUXCTL_SHDWSEL_MISC, phy);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tg3_phy_set_wirespeed(काष्ठा tg3 *tp)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (tp->phy_flags & TG3_PHYFLG_NO_ETH_WIRE_SPEED)
		वापस;

	ret = tg3_phy_auxctl_पढ़ो(tp, MII_TG3_AUXCTL_SHDWSEL_MISC, &val);
	अगर (!ret)
		tg3_phy_auxctl_ग_लिखो(tp, MII_TG3_AUXCTL_SHDWSEL_MISC,
				     val | MII_TG3_AUXCTL_MISC_WIRESPD_EN);
पूर्ण

अटल व्योम tg3_phy_apply_otp(काष्ठा tg3 *tp)
अणु
	u32 otp, phy;

	अगर (!tp->phy_otp)
		वापस;

	otp = tp->phy_otp;

	अगर (tg3_phy_toggle_auxctl_smdsp(tp, true))
		वापस;

	phy = ((otp & TG3_OTP_AGCTGT_MASK) >> TG3_OTP_AGCTGT_SHIFT);
	phy |= MII_TG3_DSP_TAP1_AGCTGT_DFLT;
	tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_TAP1, phy);

	phy = ((otp & TG3_OTP_HPFFLTR_MASK) >> TG3_OTP_HPFFLTR_SHIFT) |
	      ((otp & TG3_OTP_HPFOVER_MASK) >> TG3_OTP_HPFOVER_SHIFT);
	tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_AADJ1CH0, phy);

	phy = ((otp & TG3_OTP_LPFDIS_MASK) >> TG3_OTP_LPFDIS_SHIFT);
	phy |= MII_TG3_DSP_AADJ1CH3_ADCCKADJ;
	tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_AADJ1CH3, phy);

	phy = ((otp & TG3_OTP_VDAC_MASK) >> TG3_OTP_VDAC_SHIFT);
	tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_EXP75, phy);

	phy = ((otp & TG3_OTP_10BTAMP_MASK) >> TG3_OTP_10BTAMP_SHIFT);
	tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_EXP96, phy);

	phy = ((otp & TG3_OTP_ROFF_MASK) >> TG3_OTP_ROFF_SHIFT) |
	      ((otp & TG3_OTP_RCOFF_MASK) >> TG3_OTP_RCOFF_SHIFT);
	tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_EXP97, phy);

	tg3_phy_toggle_auxctl_smdsp(tp, false);
पूर्ण

अटल व्योम tg3_eee_pull_config(काष्ठा tg3 *tp, काष्ठा ethtool_eee *eee)
अणु
	u32 val;
	काष्ठा ethtool_eee *dest = &tp->eee;

	अगर (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP))
		वापस;

	अगर (eee)
		dest = eee;

	अगर (tg3_phy_cl45_पढ़ो(tp, MDIO_MMD_AN, TG3_CL45_D7_EEERES_STAT, &val))
		वापस;

	/* Pull eee_active */
	अगर (val == TG3_CL45_D7_EEERES_STAT_LP_1000T ||
	    val == TG3_CL45_D7_EEERES_STAT_LP_100TX) अणु
		dest->eee_active = 1;
	पूर्ण अन्यथा
		dest->eee_active = 0;

	/* Pull lp advertised settings */
	अगर (tg3_phy_cl45_पढ़ो(tp, MDIO_MMD_AN, MDIO_AN_EEE_LPABLE, &val))
		वापस;
	dest->lp_advertised = mmd_eee_adv_to_ethtool_adv_t(val);

	/* Pull advertised and eee_enabled settings */
	अगर (tg3_phy_cl45_पढ़ो(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV, &val))
		वापस;
	dest->eee_enabled = !!val;
	dest->advertised = mmd_eee_adv_to_ethtool_adv_t(val);

	/* Pull tx_lpi_enabled */
	val = tr32(TG3_CPMU_EEE_MODE);
	dest->tx_lpi_enabled = !!(val & TG3_CPMU_EEEMD_LPI_IN_TX);

	/* Pull lpi समयr value */
	dest->tx_lpi_समयr = tr32(TG3_CPMU_EEE_DBTMR1) & 0xffff;
पूर्ण

अटल व्योम tg3_phy_eee_adjust(काष्ठा tg3 *tp, bool current_link_up)
अणु
	u32 val;

	अगर (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP))
		वापस;

	tp->setlpicnt = 0;

	अगर (tp->link_config.स्वतःneg == AUTONEG_ENABLE &&
	    current_link_up &&
	    tp->link_config.active_duplex == DUPLEX_FULL &&
	    (tp->link_config.active_speed == SPEED_100 ||
	     tp->link_config.active_speed == SPEED_1000)) अणु
		u32 eeectl;

		अगर (tp->link_config.active_speed == SPEED_1000)
			eeectl = TG3_CPMU_EEE_CTRL_EXIT_16_5_US;
		अन्यथा
			eeectl = TG3_CPMU_EEE_CTRL_EXIT_36_US;

		tw32(TG3_CPMU_EEE_CTRL, eeectl);

		tg3_eee_pull_config(tp, शून्य);
		अगर (tp->eee.eee_active)
			tp->setlpicnt = 2;
	पूर्ण

	अगर (!tp->setlpicnt) अणु
		अगर (current_link_up &&
		   !tg3_phy_toggle_auxctl_smdsp(tp, true)) अणु
			tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_TAP26, 0x0000);
			tg3_phy_toggle_auxctl_smdsp(tp, false);
		पूर्ण

		val = tr32(TG3_CPMU_EEE_MODE);
		tw32(TG3_CPMU_EEE_MODE, val & ~TG3_CPMU_EEEMD_LPI_ENABLE);
	पूर्ण
पूर्ण

अटल व्योम tg3_phy_eee_enable(काष्ठा tg3 *tp)
अणु
	u32 val;

	अगर (tp->link_config.active_speed == SPEED_1000 &&
	    (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	     tg3_asic_rev(tp) == ASIC_REV_5719 ||
	     tg3_flag(tp, 57765_CLASS)) &&
	    !tg3_phy_toggle_auxctl_smdsp(tp, true)) अणु
		val = MII_TG3_DSP_TAP26_ALNOKO |
		      MII_TG3_DSP_TAP26_RMRXSTO;
		tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_TAP26, val);
		tg3_phy_toggle_auxctl_smdsp(tp, false);
	पूर्ण

	val = tr32(TG3_CPMU_EEE_MODE);
	tw32(TG3_CPMU_EEE_MODE, val | TG3_CPMU_EEEMD_LPI_ENABLE);
पूर्ण

अटल पूर्णांक tg3_रुको_macro_करोne(काष्ठा tg3 *tp)
अणु
	पूर्णांक limit = 100;

	जबतक (limit--) अणु
		u32 पंचांगp32;

		अगर (!tg3_पढ़ोphy(tp, MII_TG3_DSP_CONTROL, &पंचांगp32)) अणु
			अगर ((पंचांगp32 & 0x1000) == 0)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (limit < 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_phy_ग_लिखो_and_check_testpat(काष्ठा tg3 *tp, पूर्णांक *resetp)
अणु
	अटल स्थिर u32 test_pat[4][6] = अणु
	अणु 0x00005555, 0x00000005, 0x00002aaa, 0x0000000a, 0x00003456, 0x00000003 पूर्ण,
	अणु 0x00002aaa, 0x0000000a, 0x00003333, 0x00000003, 0x0000789a, 0x00000005 पूर्ण,
	अणु 0x00005a5a, 0x00000005, 0x00002a6a, 0x0000000a, 0x00001bcd, 0x00000003 पूर्ण,
	अणु 0x00002a5a, 0x0000000a, 0x000033c3, 0x00000003, 0x00002ef1, 0x00000005 पूर्ण
	पूर्ण;
	पूर्णांक chan;

	क्रम (chan = 0; chan < 4; chan++) अणु
		पूर्णांक i;

		tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS,
			     (chan * 0x2000) | 0x0200);
		tg3_ग_लिखोphy(tp, MII_TG3_DSP_CONTROL, 0x0002);

		क्रम (i = 0; i < 6; i++)
			tg3_ग_लिखोphy(tp, MII_TG3_DSP_RW_PORT,
				     test_pat[chan][i]);

		tg3_ग_लिखोphy(tp, MII_TG3_DSP_CONTROL, 0x0202);
		अगर (tg3_रुको_macro_करोne(tp)) अणु
			*resetp = 1;
			वापस -EBUSY;
		पूर्ण

		tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS,
			     (chan * 0x2000) | 0x0200);
		tg3_ग_लिखोphy(tp, MII_TG3_DSP_CONTROL, 0x0082);
		अगर (tg3_रुको_macro_करोne(tp)) अणु
			*resetp = 1;
			वापस -EBUSY;
		पूर्ण

		tg3_ग_लिखोphy(tp, MII_TG3_DSP_CONTROL, 0x0802);
		अगर (tg3_रुको_macro_करोne(tp)) अणु
			*resetp = 1;
			वापस -EBUSY;
		पूर्ण

		क्रम (i = 0; i < 6; i += 2) अणु
			u32 low, high;

			अगर (tg3_पढ़ोphy(tp, MII_TG3_DSP_RW_PORT, &low) ||
			    tg3_पढ़ोphy(tp, MII_TG3_DSP_RW_PORT, &high) ||
			    tg3_रुको_macro_करोne(tp)) अणु
				*resetp = 1;
				वापस -EBUSY;
			पूर्ण
			low &= 0x7fff;
			high &= 0x000f;
			अगर (low != test_pat[chan][i] ||
			    high != test_pat[chan][i+1]) अणु
				tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS, 0x000b);
				tg3_ग_लिखोphy(tp, MII_TG3_DSP_RW_PORT, 0x4001);
				tg3_ग_लिखोphy(tp, MII_TG3_DSP_RW_PORT, 0x4005);

				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_phy_reset_chanpat(काष्ठा tg3 *tp)
अणु
	पूर्णांक chan;

	क्रम (chan = 0; chan < 4; chan++) अणु
		पूर्णांक i;

		tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS,
			     (chan * 0x2000) | 0x0200);
		tg3_ग_लिखोphy(tp, MII_TG3_DSP_CONTROL, 0x0002);
		क्रम (i = 0; i < 6; i++)
			tg3_ग_लिखोphy(tp, MII_TG3_DSP_RW_PORT, 0x000);
		tg3_ग_लिखोphy(tp, MII_TG3_DSP_CONTROL, 0x0202);
		अगर (tg3_रुको_macro_करोne(tp))
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_phy_reset_5703_4_5(काष्ठा tg3 *tp)
अणु
	u32 reg32, phy9_orig;
	पूर्णांक retries, करो_phy_reset, err;

	retries = 10;
	करो_phy_reset = 1;
	करो अणु
		अगर (करो_phy_reset) अणु
			err = tg3_bmcr_reset(tp);
			अगर (err)
				वापस err;
			करो_phy_reset = 0;
		पूर्ण

		/* Disable transmitter and पूर्णांकerrupt.  */
		अगर (tg3_पढ़ोphy(tp, MII_TG3_EXT_CTRL, &reg32))
			जारी;

		reg32 |= 0x3000;
		tg3_ग_लिखोphy(tp, MII_TG3_EXT_CTRL, reg32);

		/* Set full-duplex, 1000 mbps.  */
		tg3_ग_लिखोphy(tp, MII_BMCR,
			     BMCR_FULLDPLX | BMCR_SPEED1000);

		/* Set to master mode.  */
		अगर (tg3_पढ़ोphy(tp, MII_CTRL1000, &phy9_orig))
			जारी;

		tg3_ग_लिखोphy(tp, MII_CTRL1000,
			     CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER);

		err = tg3_phy_toggle_auxctl_smdsp(tp, true);
		अगर (err)
			वापस err;

		/* Block the PHY control access.  */
		tg3_phydsp_ग_लिखो(tp, 0x8005, 0x0800);

		err = tg3_phy_ग_लिखो_and_check_testpat(tp, &करो_phy_reset);
		अगर (!err)
			अवरोध;
	पूर्ण जबतक (--retries);

	err = tg3_phy_reset_chanpat(tp);
	अगर (err)
		वापस err;

	tg3_phydsp_ग_लिखो(tp, 0x8005, 0x0000);

	tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS, 0x8200);
	tg3_ग_लिखोphy(tp, MII_TG3_DSP_CONTROL, 0x0000);

	tg3_phy_toggle_auxctl_smdsp(tp, false);

	tg3_ग_लिखोphy(tp, MII_CTRL1000, phy9_orig);

	err = tg3_पढ़ोphy(tp, MII_TG3_EXT_CTRL, &reg32);
	अगर (err)
		वापस err;

	reg32 &= ~0x3000;
	tg3_ग_लिखोphy(tp, MII_TG3_EXT_CTRL, reg32);

	वापस 0;
पूर्ण

अटल व्योम tg3_carrier_off(काष्ठा tg3 *tp)
अणु
	netअगर_carrier_off(tp->dev);
	tp->link_up = false;
पूर्ण

अटल व्योम tg3_warn_mgmt_link_flap(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, ENABLE_ASF))
		netdev_warn(tp->dev,
			    "Management side-band traffic will be interrupted during phy settings change\n");
पूर्ण

/* This will reset the tigon3 PHY अगर there is no valid
 * link unless the FORCE argument is non-zero.
 */
अटल पूर्णांक tg3_phy_reset(काष्ठा tg3 *tp)
अणु
	u32 val, cpmuctrl;
	पूर्णांक err;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		val = tr32(GRC_MISC_CFG);
		tw32_f(GRC_MISC_CFG, val & ~GRC_MISC_CFG_EPHY_IDDQ);
		udelay(40);
	पूर्ण
	err  = tg3_पढ़ोphy(tp, MII_BMSR, &val);
	err |= tg3_पढ़ोphy(tp, MII_BMSR, &val);
	अगर (err != 0)
		वापस -EBUSY;

	अगर (netअगर_running(tp->dev) && tp->link_up) अणु
		netअगर_carrier_off(tp->dev);
		tg3_link_report(tp);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5703 ||
	    tg3_asic_rev(tp) == ASIC_REV_5704 ||
	    tg3_asic_rev(tp) == ASIC_REV_5705) अणु
		err = tg3_phy_reset_5703_4_5(tp);
		अगर (err)
			वापस err;
		जाओ out;
	पूर्ण

	cpmuctrl = 0;
	अगर (tg3_asic_rev(tp) == ASIC_REV_5784 &&
	    tg3_chip_rev(tp) != CHIPREV_5784_AX) अणु
		cpmuctrl = tr32(TG3_CPMU_CTRL);
		अगर (cpmuctrl & CPMU_CTRL_GPHY_10MB_RXONLY)
			tw32(TG3_CPMU_CTRL,
			     cpmuctrl & ~CPMU_CTRL_GPHY_10MB_RXONLY);
	पूर्ण

	err = tg3_bmcr_reset(tp);
	अगर (err)
		वापस err;

	अगर (cpmuctrl & CPMU_CTRL_GPHY_10MB_RXONLY) अणु
		val = MII_TG3_DSP_EXP8_AEDW | MII_TG3_DSP_EXP8_REJ2MHz;
		tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_EXP8, val);

		tw32(TG3_CPMU_CTRL, cpmuctrl);
	पूर्ण

	अगर (tg3_chip_rev(tp) == CHIPREV_5784_AX ||
	    tg3_chip_rev(tp) == CHIPREV_5761_AX) अणु
		val = tr32(TG3_CPMU_LSPD_1000MB_CLK);
		अगर ((val & CPMU_LSPD_1000MB_MACCLK_MASK) ==
		    CPMU_LSPD_1000MB_MACCLK_12_5) अणु
			val &= ~CPMU_LSPD_1000MB_MACCLK_MASK;
			udelay(40);
			tw32_f(TG3_CPMU_LSPD_1000MB_CLK, val);
		पूर्ण
	पूर्ण

	अगर (tg3_flag(tp, 5717_PLUS) &&
	    (tp->phy_flags & TG3_PHYFLG_MII_SERDES))
		वापस 0;

	tg3_phy_apply_otp(tp);

	अगर (tp->phy_flags & TG3_PHYFLG_ENABLE_APD)
		tg3_phy_toggle_apd(tp, true);
	अन्यथा
		tg3_phy_toggle_apd(tp, false);

out:
	अगर ((tp->phy_flags & TG3_PHYFLG_ADC_BUG) &&
	    !tg3_phy_toggle_auxctl_smdsp(tp, true)) अणु
		tg3_phydsp_ग_लिखो(tp, 0x201f, 0x2aaa);
		tg3_phydsp_ग_लिखो(tp, 0x000a, 0x0323);
		tg3_phy_toggle_auxctl_smdsp(tp, false);
	पूर्ण

	अगर (tp->phy_flags & TG3_PHYFLG_5704_A0_BUG) अणु
		tg3_ग_लिखोphy(tp, MII_TG3_MISC_SHDW, 0x8d68);
		tg3_ग_लिखोphy(tp, MII_TG3_MISC_SHDW, 0x8d68);
	पूर्ण

	अगर (tp->phy_flags & TG3_PHYFLG_BER_BUG) अणु
		अगर (!tg3_phy_toggle_auxctl_smdsp(tp, true)) अणु
			tg3_phydsp_ग_लिखो(tp, 0x000a, 0x310b);
			tg3_phydsp_ग_लिखो(tp, 0x201f, 0x9506);
			tg3_phydsp_ग_लिखो(tp, 0x401f, 0x14e2);
			tg3_phy_toggle_auxctl_smdsp(tp, false);
		पूर्ण
	पूर्ण अन्यथा अगर (tp->phy_flags & TG3_PHYFLG_JITTER_BUG) अणु
		अगर (!tg3_phy_toggle_auxctl_smdsp(tp, true)) अणु
			tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS, 0x000a);
			अगर (tp->phy_flags & TG3_PHYFLG_ADJUST_TRIM) अणु
				tg3_ग_लिखोphy(tp, MII_TG3_DSP_RW_PORT, 0x110b);
				tg3_ग_लिखोphy(tp, MII_TG3_TEST1,
					     MII_TG3_TEST1_TRIM_EN | 0x4);
			पूर्ण अन्यथा
				tg3_ग_लिखोphy(tp, MII_TG3_DSP_RW_PORT, 0x010b);

			tg3_phy_toggle_auxctl_smdsp(tp, false);
		पूर्ण
	पूर्ण

	/* Set Extended packet length bit (bit 14) on all chips that */
	/* support jumbo frames */
	अगर ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5401) अणु
		/* Cannot करो पढ़ो-modअगरy-ग_लिखो on 5401 */
		tg3_phy_auxctl_ग_लिखो(tp, MII_TG3_AUXCTL_SHDWSEL_AUXCTL, 0x4c20);
	पूर्ण अन्यथा अगर (tg3_flag(tp, JUMBO_CAPABLE)) अणु
		/* Set bit 14 with पढ़ो-modअगरy-ग_लिखो to preserve other bits */
		err = tg3_phy_auxctl_पढ़ो(tp,
					  MII_TG3_AUXCTL_SHDWSEL_AUXCTL, &val);
		अगर (!err)
			tg3_phy_auxctl_ग_लिखो(tp, MII_TG3_AUXCTL_SHDWSEL_AUXCTL,
					   val | MII_TG3_AUXCTL_ACTL_EXTPKTLEN);
	पूर्ण

	/* Set phy रेजिस्टर 0x10 bit 0 to high fअगरo elasticity to support
	 * jumbo frames transmission.
	 */
	अगर (tg3_flag(tp, JUMBO_CAPABLE)) अणु
		अगर (!tg3_पढ़ोphy(tp, MII_TG3_EXT_CTRL, &val))
			tg3_ग_लिखोphy(tp, MII_TG3_EXT_CTRL,
				     val | MII_TG3_EXT_CTRL_FIFO_ELASTIC);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		/* adjust output voltage */
		tg3_ग_लिखोphy(tp, MII_TG3_FET_PTEST, 0x12);
	पूर्ण

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5762_A0)
		tg3_phydsp_ग_लिखो(tp, 0xffb, 0x4000);

	tg3_phy_toggle_स्वतःmdix(tp, true);
	tg3_phy_set_wirespeed(tp);
	वापस 0;
पूर्ण

#घोषणा TG3_GPIO_MSG_DRVR_PRES		 0x00000001
#घोषणा TG3_GPIO_MSG_NEED_VAUX		 0x00000002
#घोषणा TG3_GPIO_MSG_MASK		 (TG3_GPIO_MSG_DRVR_PRES | \
					  TG3_GPIO_MSG_NEED_VAUX)
#घोषणा TG3_GPIO_MSG_ALL_DRVR_PRES_MASK \
	((TG3_GPIO_MSG_DRVR_PRES << 0) | \
	 (TG3_GPIO_MSG_DRVR_PRES << 4) | \
	 (TG3_GPIO_MSG_DRVR_PRES << 8) | \
	 (TG3_GPIO_MSG_DRVR_PRES << 12))

#घोषणा TG3_GPIO_MSG_ALL_NEED_VAUX_MASK \
	((TG3_GPIO_MSG_NEED_VAUX << 0) | \
	 (TG3_GPIO_MSG_NEED_VAUX << 4) | \
	 (TG3_GPIO_MSG_NEED_VAUX << 8) | \
	 (TG3_GPIO_MSG_NEED_VAUX << 12))

अटल अंतरभूत u32 tg3_set_function_status(काष्ठा tg3 *tp, u32 newstat)
अणु
	u32 status, shअगरt;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719)
		status = tg3_ape_पढ़ो32(tp, TG3_APE_GPIO_MSG);
	अन्यथा
		status = tr32(TG3_CPMU_DRV_STATUS);

	shअगरt = TG3_APE_GPIO_MSG_SHIFT + 4 * tp->pci_fn;
	status &= ~(TG3_GPIO_MSG_MASK << shअगरt);
	status |= (newstat << shअगरt);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719)
		tg3_ape_ग_लिखो32(tp, TG3_APE_GPIO_MSG, status);
	अन्यथा
		tw32(TG3_CPMU_DRV_STATUS, status);

	वापस status >> TG3_APE_GPIO_MSG_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक tg3_pwrsrc_चयन_to_vमुख्य(काष्ठा tg3 *tp)
अणु
	अगर (!tg3_flag(tp, IS_NIC))
		वापस 0;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720) अणु
		अगर (tg3_ape_lock(tp, TG3_APE_LOCK_GPIO))
			वापस -EIO;

		tg3_set_function_status(tp, TG3_GPIO_MSG_DRVR_PRES);

		tw32_रुको_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		tg3_ape_unlock(tp, TG3_APE_LOCK_GPIO);
	पूर्ण अन्यथा अणु
		tw32_रुको_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tg3_pwrsrc_die_with_vमुख्य(काष्ठा tg3 *tp)
अणु
	u32 grc_local_ctrl;

	अगर (!tg3_flag(tp, IS_NIC) ||
	    tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701)
		वापस;

	grc_local_ctrl = tp->grc_local_ctrl | GRC_LCLCTRL_GPIO_OE1;

	tw32_रुको_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl | GRC_LCLCTRL_GPIO_OUTPUT1,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);

	tw32_रुको_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);

	tw32_रुको_f(GRC_LOCAL_CTRL,
		    grc_local_ctrl | GRC_LCLCTRL_GPIO_OUTPUT1,
		    TG3_GRC_LCLCTL_PWRSW_DELAY);
पूर्ण

अटल व्योम tg3_pwrsrc_चयन_to_vaux(काष्ठा tg3 *tp)
अणु
	अगर (!tg3_flag(tp, IS_NIC))
		वापस;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701) अणु
		tw32_रुको_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl |
			    (GRC_LCLCTRL_GPIO_OE0 |
			     GRC_LCLCTRL_GPIO_OE1 |
			     GRC_LCLCTRL_GPIO_OE2 |
			     GRC_LCLCTRL_GPIO_OUTPUT0 |
			     GRC_LCLCTRL_GPIO_OUTPUT1),
			    TG3_GRC_LCLCTL_PWRSW_DELAY);
	पूर्ण अन्यथा अगर (tp->pdev->device == PCI_DEVICE_ID_TIGON3_5761 ||
		   tp->pdev->device == TG3PCI_DEVICE_TIGON3_5761S) अणु
		/* The 5761 non-e device swaps GPIO 0 and GPIO 2. */
		u32 grc_local_ctrl = GRC_LCLCTRL_GPIO_OE0 |
				     GRC_LCLCTRL_GPIO_OE1 |
				     GRC_LCLCTRL_GPIO_OE2 |
				     GRC_LCLCTRL_GPIO_OUTPUT0 |
				     GRC_LCLCTRL_GPIO_OUTPUT1 |
				     tp->grc_local_ctrl;
		tw32_रुको_f(GRC_LOCAL_CTRL, grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		grc_local_ctrl |= GRC_LCLCTRL_GPIO_OUTPUT2;
		tw32_रुको_f(GRC_LOCAL_CTRL, grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		grc_local_ctrl &= ~GRC_LCLCTRL_GPIO_OUTPUT0;
		tw32_रुको_f(GRC_LOCAL_CTRL, grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);
	पूर्ण अन्यथा अणु
		u32 no_gpio2;
		u32 grc_local_ctrl = 0;

		/* Workaround to prevent overdrawing Amps. */
		अगर (tg3_asic_rev(tp) == ASIC_REV_5714) अणु
			grc_local_ctrl |= GRC_LCLCTRL_GPIO_OE3;
			tw32_रुको_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl |
				    grc_local_ctrl,
				    TG3_GRC_LCLCTL_PWRSW_DELAY);
		पूर्ण

		/* On 5753 and variants, GPIO2 cannot be used. */
		no_gpio2 = tp->nic_sram_data_cfg &
			   NIC_SRAM_DATA_CFG_NO_GPIO2;

		grc_local_ctrl |= GRC_LCLCTRL_GPIO_OE0 |
				  GRC_LCLCTRL_GPIO_OE1 |
				  GRC_LCLCTRL_GPIO_OE2 |
				  GRC_LCLCTRL_GPIO_OUTPUT1 |
				  GRC_LCLCTRL_GPIO_OUTPUT2;
		अगर (no_gpio2) अणु
			grc_local_ctrl &= ~(GRC_LCLCTRL_GPIO_OE2 |
					    GRC_LCLCTRL_GPIO_OUTPUT2);
		पूर्ण
		tw32_रुको_f(GRC_LOCAL_CTRL,
			    tp->grc_local_ctrl | grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		grc_local_ctrl |= GRC_LCLCTRL_GPIO_OUTPUT0;

		tw32_रुको_f(GRC_LOCAL_CTRL,
			    tp->grc_local_ctrl | grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		अगर (!no_gpio2) अणु
			grc_local_ctrl &= ~GRC_LCLCTRL_GPIO_OUTPUT2;
			tw32_रुको_f(GRC_LOCAL_CTRL,
				    tp->grc_local_ctrl | grc_local_ctrl,
				    TG3_GRC_LCLCTL_PWRSW_DELAY);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tg3_frob_aux_घातer_5717(काष्ठा tg3 *tp, bool wol_enable)
अणु
	u32 msg = 0;

	/* Serialize घातer state transitions */
	अगर (tg3_ape_lock(tp, TG3_APE_LOCK_GPIO))
		वापस;

	अगर (tg3_flag(tp, ENABLE_ASF) || tg3_flag(tp, ENABLE_APE) || wol_enable)
		msg = TG3_GPIO_MSG_NEED_VAUX;

	msg = tg3_set_function_status(tp, msg);

	अगर (msg & TG3_GPIO_MSG_ALL_DRVR_PRES_MASK)
		जाओ करोne;

	अगर (msg & TG3_GPIO_MSG_ALL_NEED_VAUX_MASK)
		tg3_pwrsrc_चयन_to_vaux(tp);
	अन्यथा
		tg3_pwrsrc_die_with_vमुख्य(tp);

करोne:
	tg3_ape_unlock(tp, TG3_APE_LOCK_GPIO);
पूर्ण

अटल व्योम tg3_frob_aux_घातer(काष्ठा tg3 *tp, bool include_wol)
अणु
	bool need_vaux = false;

	/* The GPIOs करो something completely dअगरferent on 57765. */
	अगर (!tg3_flag(tp, IS_NIC) || tg3_flag(tp, 57765_CLASS))
		वापस;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720) अणु
		tg3_frob_aux_घातer_5717(tp, include_wol ?
					tg3_flag(tp, WOL_ENABLE) != 0 : 0);
		वापस;
	पूर्ण

	अगर (tp->pdev_peer && tp->pdev_peer != tp->pdev) अणु
		काष्ठा net_device *dev_peer;

		dev_peer = pci_get_drvdata(tp->pdev_peer);

		/* हटाओ_one() may have been run on the peer. */
		अगर (dev_peer) अणु
			काष्ठा tg3 *tp_peer = netdev_priv(dev_peer);

			अगर (tg3_flag(tp_peer, INIT_COMPLETE))
				वापस;

			अगर ((include_wol && tg3_flag(tp_peer, WOL_ENABLE)) ||
			    tg3_flag(tp_peer, ENABLE_ASF))
				need_vaux = true;
		पूर्ण
	पूर्ण

	अगर ((include_wol && tg3_flag(tp, WOL_ENABLE)) ||
	    tg3_flag(tp, ENABLE_ASF))
		need_vaux = true;

	अगर (need_vaux)
		tg3_pwrsrc_चयन_to_vaux(tp);
	अन्यथा
		tg3_pwrsrc_die_with_vमुख्य(tp);
पूर्ण

अटल पूर्णांक tg3_5700_link_polarity(काष्ठा tg3 *tp, u32 speed)
अणु
	अगर (tp->led_ctrl == LED_CTRL_MODE_PHY_2)
		वापस 1;
	अन्यथा अगर ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5411) अणु
		अगर (speed != SPEED_10)
			वापस 1;
	पूर्ण अन्यथा अगर (speed == SPEED_10)
		वापस 1;

	वापस 0;
पूर्ण

अटल bool tg3_phy_घातer_bug(काष्ठा tg3 *tp)
अणु
	चयन (tg3_asic_rev(tp)) अणु
	हाल ASIC_REV_5700:
	हाल ASIC_REV_5704:
		वापस true;
	हाल ASIC_REV_5780:
		अगर (tp->phy_flags & TG3_PHYFLG_MII_SERDES)
			वापस true;
		वापस false;
	हाल ASIC_REV_5717:
		अगर (!tp->pci_fn)
			वापस true;
		वापस false;
	हाल ASIC_REV_5719:
	हाल ASIC_REV_5720:
		अगर ((tp->phy_flags & TG3_PHYFLG_PHY_SERDES) &&
		    !tp->pci_fn)
			वापस true;
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tg3_phy_led_bug(काष्ठा tg3 *tp)
अणु
	चयन (tg3_asic_rev(tp)) अणु
	हाल ASIC_REV_5719:
	हाल ASIC_REV_5720:
		अगर ((tp->phy_flags & TG3_PHYFLG_MII_SERDES) &&
		    !tp->pci_fn)
			वापस true;
		वापस false;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम tg3_घातer_करोwn_phy(काष्ठा tg3 *tp, bool करो_low_घातer)
अणु
	u32 val;

	अगर (tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN)
		वापस;

	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES) अणु
		अगर (tg3_asic_rev(tp) == ASIC_REV_5704) अणु
			u32 sg_dig_ctrl = tr32(SG_DIG_CTRL);
			u32 serdes_cfg = tr32(MAC_SERDES_CFG);

			sg_dig_ctrl |=
				SG_DIG_USING_HW_AUTONEG | SG_DIG_SOFT_RESET;
			tw32(SG_DIG_CTRL, sg_dig_ctrl);
			tw32(MAC_SERDES_CFG, serdes_cfg | (1 << 15));
		पूर्ण
		वापस;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		tg3_bmcr_reset(tp);
		val = tr32(GRC_MISC_CFG);
		tw32_f(GRC_MISC_CFG, val | GRC_MISC_CFG_EPHY_IDDQ);
		udelay(40);
		वापस;
	पूर्ण अन्यथा अगर (tp->phy_flags & TG3_PHYFLG_IS_FET) अणु
		u32 phytest;
		अगर (!tg3_पढ़ोphy(tp, MII_TG3_FET_TEST, &phytest)) अणु
			u32 phy;

			tg3_ग_लिखोphy(tp, MII_ADVERTISE, 0);
			tg3_ग_लिखोphy(tp, MII_BMCR,
				     BMCR_ANENABLE | BMCR_ANRESTART);

			tg3_ग_लिखोphy(tp, MII_TG3_FET_TEST,
				     phytest | MII_TG3_FET_SHADOW_EN);
			अगर (!tg3_पढ़ोphy(tp, MII_TG3_FET_SHDW_AUXMODE4, &phy)) अणु
				phy |= MII_TG3_FET_SHDW_AUXMODE4_SBPD;
				tg3_ग_लिखोphy(tp,
					     MII_TG3_FET_SHDW_AUXMODE4,
					     phy);
			पूर्ण
			tg3_ग_लिखोphy(tp, MII_TG3_FET_TEST, phytest);
		पूर्ण
		वापस;
	पूर्ण अन्यथा अगर (करो_low_घातer) अणु
		अगर (!tg3_phy_led_bug(tp))
			tg3_ग_लिखोphy(tp, MII_TG3_EXT_CTRL,
				     MII_TG3_EXT_CTRL_FORCE_LED_OFF);

		val = MII_TG3_AUXCTL_PCTL_100TX_LPWR |
		      MII_TG3_AUXCTL_PCTL_SPR_ISOLATE |
		      MII_TG3_AUXCTL_PCTL_VREG_11V;
		tg3_phy_auxctl_ग_लिखो(tp, MII_TG3_AUXCTL_SHDWSEL_PWRCTL, val);
	पूर्ण

	/* The PHY should not be घातered करोwn on some chips because
	 * of bugs.
	 */
	अगर (tg3_phy_घातer_bug(tp))
		वापस;

	अगर (tg3_chip_rev(tp) == CHIPREV_5784_AX ||
	    tg3_chip_rev(tp) == CHIPREV_5761_AX) अणु
		val = tr32(TG3_CPMU_LSPD_1000MB_CLK);
		val &= ~CPMU_LSPD_1000MB_MACCLK_MASK;
		val |= CPMU_LSPD_1000MB_MACCLK_12_5;
		tw32_f(TG3_CPMU_LSPD_1000MB_CLK, val);
	पूर्ण

	tg3_ग_लिखोphy(tp, MII_BMCR, BMCR_PDOWN);
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_nvram_lock(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, NVRAM)) अणु
		पूर्णांक i;

		अगर (tp->nvram_lock_cnt == 0) अणु
			tw32(NVRAM_SWARB, SWARB_REQ_SET1);
			क्रम (i = 0; i < 8000; i++) अणु
				अगर (tr32(NVRAM_SWARB) & SWARB_GNT1)
					अवरोध;
				udelay(20);
			पूर्ण
			अगर (i == 8000) अणु
				tw32(NVRAM_SWARB, SWARB_REQ_CLR1);
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		tp->nvram_lock_cnt++;
	पूर्ण
	वापस 0;
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_nvram_unlock(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, NVRAM)) अणु
		अगर (tp->nvram_lock_cnt > 0)
			tp->nvram_lock_cnt--;
		अगर (tp->nvram_lock_cnt == 0)
			tw32_f(NVRAM_SWARB, SWARB_REQ_CLR1);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_enable_nvram_access(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, 5750_PLUS) && !tg3_flag(tp, PROTECTED_NVRAM)) अणु
		u32 nvaccess = tr32(NVRAM_ACCESS);

		tw32(NVRAM_ACCESS, nvaccess | ACCESS_ENABLE);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_disable_nvram_access(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, 5750_PLUS) && !tg3_flag(tp, PROTECTED_NVRAM)) अणु
		u32 nvaccess = tr32(NVRAM_ACCESS);

		tw32(NVRAM_ACCESS, nvaccess & ~ACCESS_ENABLE);
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_nvram_पढ़ो_using_eeprom(काष्ठा tg3 *tp,
					u32 offset, u32 *val)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	अगर (offset > EEPROM_ADDR_ADDR_MASK || (offset % 4) != 0)
		वापस -EINVAL;

	पंचांगp = tr32(GRC_EEPROM_ADDR) & ~(EEPROM_ADDR_ADDR_MASK |
					EEPROM_ADDR_DEVID_MASK |
					EEPROM_ADDR_READ);
	tw32(GRC_EEPROM_ADDR,
	     पंचांगp |
	     (0 << EEPROM_ADDR_DEVID_SHIFT) |
	     ((offset << EEPROM_ADDR_ADDR_SHIFT) &
	      EEPROM_ADDR_ADDR_MASK) |
	     EEPROM_ADDR_READ | EEPROM_ADDR_START);

	क्रम (i = 0; i < 1000; i++) अणु
		पंचांगp = tr32(GRC_EEPROM_ADDR);

		अगर (पंचांगp & EEPROM_ADDR_COMPLETE)
			अवरोध;
		msleep(1);
	पूर्ण
	अगर (!(पंचांगp & EEPROM_ADDR_COMPLETE))
		वापस -EBUSY;

	पंचांगp = tr32(GRC_EEPROM_DATA);

	/*
	 * The data will always be opposite the native endian
	 * क्रमmat.  Perक्रमm a blind byteswap to compensate.
	 */
	*val = swab32(पंचांगp);

	वापस 0;
पूर्ण

#घोषणा NVRAM_CMD_TIMEOUT 10000

अटल पूर्णांक tg3_nvram_exec_cmd(काष्ठा tg3 *tp, u32 nvram_cmd)
अणु
	पूर्णांक i;

	tw32(NVRAM_CMD, nvram_cmd);
	क्रम (i = 0; i < NVRAM_CMD_TIMEOUT; i++) अणु
		usleep_range(10, 40);
		अगर (tr32(NVRAM_CMD) & NVRAM_CMD_DONE) अणु
			udelay(10);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == NVRAM_CMD_TIMEOUT)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल u32 tg3_nvram_phys_addr(काष्ठा tg3 *tp, u32 addr)
अणु
	अगर (tg3_flag(tp, NVRAM) &&
	    tg3_flag(tp, NVRAM_BUFFERED) &&
	    tg3_flag(tp, FLASH) &&
	    !tg3_flag(tp, NO_NVRAM_ADDR_TRANS) &&
	    (tp->nvram_jedecnum == JEDEC_ATMEL))

		addr = ((addr / tp->nvram_pagesize) <<
			ATMEL_AT45DB0X1B_PAGE_POS) +
		       (addr % tp->nvram_pagesize);

	वापस addr;
पूर्ण

अटल u32 tg3_nvram_logical_addr(काष्ठा tg3 *tp, u32 addr)
अणु
	अगर (tg3_flag(tp, NVRAM) &&
	    tg3_flag(tp, NVRAM_BUFFERED) &&
	    tg3_flag(tp, FLASH) &&
	    !tg3_flag(tp, NO_NVRAM_ADDR_TRANS) &&
	    (tp->nvram_jedecnum == JEDEC_ATMEL))

		addr = ((addr >> ATMEL_AT45DB0X1B_PAGE_POS) *
			tp->nvram_pagesize) +
		       (addr & ((1 << ATMEL_AT45DB0X1B_PAGE_POS) - 1));

	वापस addr;
पूर्ण

/* NOTE: Data पढ़ो in from NVRAM is byteswapped according to
 * the byteswapping settings क्रम all other रेजिस्टर accesses.
 * tg3 devices are BE devices, so on a BE machine, the data
 * वापसed will be exactly as it is seen in NVRAM.  On a LE
 * machine, the 32-bit value will be byteswapped.
 */
अटल पूर्णांक tg3_nvram_पढ़ो(काष्ठा tg3 *tp, u32 offset, u32 *val)
अणु
	पूर्णांक ret;

	अगर (!tg3_flag(tp, NVRAM))
		वापस tg3_nvram_पढ़ो_using_eeprom(tp, offset, val);

	offset = tg3_nvram_phys_addr(tp, offset);

	अगर (offset > NVRAM_ADDR_MSK)
		वापस -EINVAL;

	ret = tg3_nvram_lock(tp);
	अगर (ret)
		वापस ret;

	tg3_enable_nvram_access(tp);

	tw32(NVRAM_ADDR, offset);
	ret = tg3_nvram_exec_cmd(tp, NVRAM_CMD_RD | NVRAM_CMD_GO |
		NVRAM_CMD_FIRST | NVRAM_CMD_LAST | NVRAM_CMD_DONE);

	अगर (ret == 0)
		*val = tr32(NVRAM_RDDATA);

	tg3_disable_nvram_access(tp);

	tg3_nvram_unlock(tp);

	वापस ret;
पूर्ण

/* Ensures NVRAM data is in bytestream क्रमmat. */
अटल पूर्णांक tg3_nvram_पढ़ो_be32(काष्ठा tg3 *tp, u32 offset, __be32 *val)
अणु
	u32 v;
	पूर्णांक res = tg3_nvram_पढ़ो(tp, offset, &v);
	अगर (!res)
		*val = cpu_to_be32(v);
	वापस res;
पूर्ण

अटल पूर्णांक tg3_nvram_ग_लिखो_block_using_eeprom(काष्ठा tg3 *tp,
				    u32 offset, u32 len, u8 *buf)
अणु
	पूर्णांक i, j, rc = 0;
	u32 val;

	क्रम (i = 0; i < len; i += 4) अणु
		u32 addr;
		__be32 data;

		addr = offset + i;

		स_नकल(&data, buf + i, 4);

		/*
		 * The SEEPROM पूर्णांकerface expects the data to always be opposite
		 * the native endian क्रमmat.  We accomplish this by reversing
		 * all the operations that would have been perक्रमmed on the
		 * data from a call to tg3_nvram_पढ़ो_be32().
		 */
		tw32(GRC_EEPROM_DATA, swab32(be32_to_cpu(data)));

		val = tr32(GRC_EEPROM_ADDR);
		tw32(GRC_EEPROM_ADDR, val | EEPROM_ADDR_COMPLETE);

		val &= ~(EEPROM_ADDR_ADDR_MASK | EEPROM_ADDR_DEVID_MASK |
			EEPROM_ADDR_READ);
		tw32(GRC_EEPROM_ADDR, val |
			(0 << EEPROM_ADDR_DEVID_SHIFT) |
			(addr & EEPROM_ADDR_ADDR_MASK) |
			EEPROM_ADDR_START |
			EEPROM_ADDR_WRITE);

		क्रम (j = 0; j < 1000; j++) अणु
			val = tr32(GRC_EEPROM_ADDR);

			अगर (val & EEPROM_ADDR_COMPLETE)
				अवरोध;
			msleep(1);
		पूर्ण
		अगर (!(val & EEPROM_ADDR_COMPLETE)) अणु
			rc = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* offset and length are dword aligned */
अटल पूर्णांक tg3_nvram_ग_लिखो_block_unbuffered(काष्ठा tg3 *tp, u32 offset, u32 len,
		u8 *buf)
अणु
	पूर्णांक ret = 0;
	u32 pagesize = tp->nvram_pagesize;
	u32 pagemask = pagesize - 1;
	u32 nvram_cmd;
	u8 *पंचांगp;

	पंचांगp = kदो_स्मृति(pagesize, GFP_KERNEL);
	अगर (पंचांगp == शून्य)
		वापस -ENOMEM;

	जबतक (len) अणु
		पूर्णांक j;
		u32 phy_addr, page_off, size;

		phy_addr = offset & ~pagemask;

		क्रम (j = 0; j < pagesize; j += 4) अणु
			ret = tg3_nvram_पढ़ो_be32(tp, phy_addr + j,
						  (__be32 *) (पंचांगp + j));
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (ret)
			अवरोध;

		page_off = offset & pagemask;
		size = pagesize;
		अगर (len < size)
			size = len;

		len -= size;

		स_नकल(पंचांगp + page_off, buf, size);

		offset = offset + (pagesize - page_off);

		tg3_enable_nvram_access(tp);

		/*
		 * Beक्रमe we can erase the flash page, we need
		 * to issue a special "write enable" command.
		 */
		nvram_cmd = NVRAM_CMD_WREN | NVRAM_CMD_GO | NVRAM_CMD_DONE;

		अगर (tg3_nvram_exec_cmd(tp, nvram_cmd))
			अवरोध;

		/* Erase the target page */
		tw32(NVRAM_ADDR, phy_addr);

		nvram_cmd = NVRAM_CMD_GO | NVRAM_CMD_DONE | NVRAM_CMD_WR |
			NVRAM_CMD_FIRST | NVRAM_CMD_LAST | NVRAM_CMD_ERASE;

		अगर (tg3_nvram_exec_cmd(tp, nvram_cmd))
			अवरोध;

		/* Issue another ग_लिखो enable to start the ग_लिखो. */
		nvram_cmd = NVRAM_CMD_WREN | NVRAM_CMD_GO | NVRAM_CMD_DONE;

		अगर (tg3_nvram_exec_cmd(tp, nvram_cmd))
			अवरोध;

		क्रम (j = 0; j < pagesize; j += 4) अणु
			__be32 data;

			data = *((__be32 *) (पंचांगp + j));

			tw32(NVRAM_WRDATA, be32_to_cpu(data));

			tw32(NVRAM_ADDR, phy_addr + j);

			nvram_cmd = NVRAM_CMD_GO | NVRAM_CMD_DONE |
				NVRAM_CMD_WR;

			अगर (j == 0)
				nvram_cmd |= NVRAM_CMD_FIRST;
			अन्यथा अगर (j == (pagesize - 4))
				nvram_cmd |= NVRAM_CMD_LAST;

			ret = tg3_nvram_exec_cmd(tp, nvram_cmd);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (ret)
			अवरोध;
	पूर्ण

	nvram_cmd = NVRAM_CMD_WRDI | NVRAM_CMD_GO | NVRAM_CMD_DONE;
	tg3_nvram_exec_cmd(tp, nvram_cmd);

	kमुक्त(पंचांगp);

	वापस ret;
पूर्ण

/* offset and length are dword aligned */
अटल पूर्णांक tg3_nvram_ग_लिखो_block_buffered(काष्ठा tg3 *tp, u32 offset, u32 len,
		u8 *buf)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < len; i += 4, offset += 4) अणु
		u32 page_off, phy_addr, nvram_cmd;
		__be32 data;

		स_नकल(&data, buf + i, 4);
		tw32(NVRAM_WRDATA, be32_to_cpu(data));

		page_off = offset % tp->nvram_pagesize;

		phy_addr = tg3_nvram_phys_addr(tp, offset);

		nvram_cmd = NVRAM_CMD_GO | NVRAM_CMD_DONE | NVRAM_CMD_WR;

		अगर (page_off == 0 || i == 0)
			nvram_cmd |= NVRAM_CMD_FIRST;
		अगर (page_off == (tp->nvram_pagesize - 4))
			nvram_cmd |= NVRAM_CMD_LAST;

		अगर (i == (len - 4))
			nvram_cmd |= NVRAM_CMD_LAST;

		अगर ((nvram_cmd & NVRAM_CMD_FIRST) ||
		    !tg3_flag(tp, FLASH) ||
		    !tg3_flag(tp, 57765_PLUS))
			tw32(NVRAM_ADDR, phy_addr);

		अगर (tg3_asic_rev(tp) != ASIC_REV_5752 &&
		    !tg3_flag(tp, 5755_PLUS) &&
		    (tp->nvram_jedecnum == JEDEC_ST) &&
		    (nvram_cmd & NVRAM_CMD_FIRST)) अणु
			u32 cmd;

			cmd = NVRAM_CMD_WREN | NVRAM_CMD_GO | NVRAM_CMD_DONE;
			ret = tg3_nvram_exec_cmd(tp, cmd);
			अगर (ret)
				अवरोध;
		पूर्ण
		अगर (!tg3_flag(tp, FLASH)) अणु
			/* We always करो complete word ग_लिखोs to eeprom. */
			nvram_cmd |= (NVRAM_CMD_FIRST | NVRAM_CMD_LAST);
		पूर्ण

		ret = tg3_nvram_exec_cmd(tp, nvram_cmd);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/* offset and length are dword aligned */
अटल पूर्णांक tg3_nvram_ग_लिखो_block(काष्ठा tg3 *tp, u32 offset, u32 len, u8 *buf)
अणु
	पूर्णांक ret;

	अगर (tg3_flag(tp, EEPROM_WRITE_PROT)) अणु
		tw32_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl &
		       ~GRC_LCLCTRL_GPIO_OUTPUT1);
		udelay(40);
	पूर्ण

	अगर (!tg3_flag(tp, NVRAM)) अणु
		ret = tg3_nvram_ग_लिखो_block_using_eeprom(tp, offset, len, buf);
	पूर्ण अन्यथा अणु
		u32 grc_mode;

		ret = tg3_nvram_lock(tp);
		अगर (ret)
			वापस ret;

		tg3_enable_nvram_access(tp);
		अगर (tg3_flag(tp, 5750_PLUS) && !tg3_flag(tp, PROTECTED_NVRAM))
			tw32(NVRAM_WRITE1, 0x406);

		grc_mode = tr32(GRC_MODE);
		tw32(GRC_MODE, grc_mode | GRC_MODE_NVRAM_WR_ENABLE);

		अगर (tg3_flag(tp, NVRAM_BUFFERED) || !tg3_flag(tp, FLASH)) अणु
			ret = tg3_nvram_ग_लिखो_block_buffered(tp, offset, len,
				buf);
		पूर्ण अन्यथा अणु
			ret = tg3_nvram_ग_लिखो_block_unbuffered(tp, offset, len,
				buf);
		पूर्ण

		grc_mode = tr32(GRC_MODE);
		tw32(GRC_MODE, grc_mode & ~GRC_MODE_NVRAM_WR_ENABLE);

		tg3_disable_nvram_access(tp);
		tg3_nvram_unlock(tp);
	पूर्ण

	अगर (tg3_flag(tp, EEPROM_WRITE_PROT)) अणु
		tw32_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl);
		udelay(40);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा RX_CPU_SCRATCH_BASE	0x30000
#घोषणा RX_CPU_SCRATCH_SIZE	0x04000
#घोषणा TX_CPU_SCRATCH_BASE	0x34000
#घोषणा TX_CPU_SCRATCH_SIZE	0x04000

/* tp->lock is held. */
अटल पूर्णांक tg3_छोड़ो_cpu(काष्ठा tg3 *tp, u32 cpu_base)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक iters = 10000;

	क्रम (i = 0; i < iters; i++) अणु
		tw32(cpu_base + CPU_STATE, 0xffffffff);
		tw32(cpu_base + CPU_MODE,  CPU_MODE_HALT);
		अगर (tr32(cpu_base + CPU_MODE) & CPU_MODE_HALT)
			अवरोध;
		अगर (pci_channel_offline(tp->pdev))
			वापस -EBUSY;
	पूर्ण

	वापस (i == iters) ? -EBUSY : 0;
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_rxcpu_छोड़ो(काष्ठा tg3 *tp)
अणु
	पूर्णांक rc = tg3_छोड़ो_cpu(tp, RX_CPU_BASE);

	tw32(RX_CPU_BASE + CPU_STATE, 0xffffffff);
	tw32_f(RX_CPU_BASE + CPU_MODE,  CPU_MODE_HALT);
	udelay(10);

	वापस rc;
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_txcpu_छोड़ो(काष्ठा tg3 *tp)
अणु
	वापस tg3_छोड़ो_cpu(tp, TX_CPU_BASE);
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_resume_cpu(काष्ठा tg3 *tp, u32 cpu_base)
अणु
	tw32(cpu_base + CPU_STATE, 0xffffffff);
	tw32_f(cpu_base + CPU_MODE,  0x00000000);
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_rxcpu_resume(काष्ठा tg3 *tp)
अणु
	tg3_resume_cpu(tp, RX_CPU_BASE);
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_halt_cpu(काष्ठा tg3 *tp, u32 cpu_base)
अणु
	पूर्णांक rc;

	BUG_ON(cpu_base == TX_CPU_BASE && tg3_flag(tp, 5705_PLUS));

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		u32 val = tr32(GRC_VCPU_EXT_CTRL);

		tw32(GRC_VCPU_EXT_CTRL, val | GRC_VCPU_EXT_CTRL_HALT_CPU);
		वापस 0;
	पूर्ण
	अगर (cpu_base == RX_CPU_BASE) अणु
		rc = tg3_rxcpu_छोड़ो(tp);
	पूर्ण अन्यथा अणु
		/*
		 * There is only an Rx CPU क्रम the 5750 derivative in the
		 * BCM4785.
		 */
		अगर (tg3_flag(tp, IS_SSB_CORE))
			वापस 0;

		rc = tg3_txcpu_छोड़ो(tp);
	पूर्ण

	अगर (rc) अणु
		netdev_err(tp->dev, "%s timed out, %s CPU\n",
			   __func__, cpu_base == RX_CPU_BASE ? "RX" : "TX");
		वापस -ENODEV;
	पूर्ण

	/* Clear firmware's nvram arbitration. */
	अगर (tg3_flag(tp, NVRAM))
		tw32(NVRAM_SWARB, SWARB_REQ_CLR0);
	वापस 0;
पूर्ण

अटल पूर्णांक tg3_fw_data_len(काष्ठा tg3 *tp,
			   स्थिर काष्ठा tg3_firmware_hdr *fw_hdr)
अणु
	पूर्णांक fw_len;

	/* Non fragmented firmware have one firmware header followed by a
	 * contiguous chunk of data to be written. The length field in that
	 * header is not the length of data to be written but the complete
	 * length of the bss. The data length is determined based on
	 * tp->fw->size minus headers.
	 *
	 * Fragmented firmware have a मुख्य header followed by multiple
	 * fragments. Each fragment is identical to non fragmented firmware
	 * with a firmware header followed by a contiguous chunk of data. In
	 * the मुख्य header, the length field is unused and set to 0xffffffff.
	 * In each fragment header the length is the entire size of that
	 * fragment i.e. fragment data + header length. Data length is
	 * thereक्रमe length field in the header minus TG3_FW_HDR_LEN.
	 */
	अगर (tp->fw_len == 0xffffffff)
		fw_len = be32_to_cpu(fw_hdr->len);
	अन्यथा
		fw_len = tp->fw->size;

	वापस (fw_len - TG3_FW_HDR_LEN) / माप(u32);
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_load_firmware_cpu(काष्ठा tg3 *tp, u32 cpu_base,
				 u32 cpu_scratch_base, पूर्णांक cpu_scratch_size,
				 स्थिर काष्ठा tg3_firmware_hdr *fw_hdr)
अणु
	पूर्णांक err, i;
	व्योम (*ग_लिखो_op)(काष्ठा tg3 *, u32, u32);
	पूर्णांक total_len = tp->fw->size;

	अगर (cpu_base == TX_CPU_BASE && tg3_flag(tp, 5705_PLUS)) अणु
		netdev_err(tp->dev,
			   "%s: Trying to load TX cpu firmware which is 5705\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (tg3_flag(tp, 5705_PLUS) && tg3_asic_rev(tp) != ASIC_REV_57766)
		ग_लिखो_op = tg3_ग_लिखो_mem;
	अन्यथा
		ग_लिखो_op = tg3_ग_लिखो_indirect_reg32;

	अगर (tg3_asic_rev(tp) != ASIC_REV_57766) अणु
		/* It is possible that bootcode is still loading at this poपूर्णांक.
		 * Get the nvram lock first beक्रमe halting the cpu.
		 */
		पूर्णांक lock_err = tg3_nvram_lock(tp);
		err = tg3_halt_cpu(tp, cpu_base);
		अगर (!lock_err)
			tg3_nvram_unlock(tp);
		अगर (err)
			जाओ out;

		क्रम (i = 0; i < cpu_scratch_size; i += माप(u32))
			ग_लिखो_op(tp, cpu_scratch_base + i, 0);
		tw32(cpu_base + CPU_STATE, 0xffffffff);
		tw32(cpu_base + CPU_MODE,
		     tr32(cpu_base + CPU_MODE) | CPU_MODE_HALT);
	पूर्ण अन्यथा अणु
		/* Subtract additional मुख्य header क्रम fragmented firmware and
		 * advance to the first fragment
		 */
		total_len -= TG3_FW_HDR_LEN;
		fw_hdr++;
	पूर्ण

	करो अणु
		u32 *fw_data = (u32 *)(fw_hdr + 1);
		क्रम (i = 0; i < tg3_fw_data_len(tp, fw_hdr); i++)
			ग_लिखो_op(tp, cpu_scratch_base +
				     (be32_to_cpu(fw_hdr->base_addr) & 0xffff) +
				     (i * माप(u32)),
				 be32_to_cpu(fw_data[i]));

		total_len -= be32_to_cpu(fw_hdr->len);

		/* Advance to next fragment */
		fw_hdr = (काष्ठा tg3_firmware_hdr *)
			 ((व्योम *)fw_hdr + be32_to_cpu(fw_hdr->len));
	पूर्ण जबतक (total_len > 0);

	err = 0;

out:
	वापस err;
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_छोड़ो_cpu_and_set_pc(काष्ठा tg3 *tp, u32 cpu_base, u32 pc)
अणु
	पूर्णांक i;
	स्थिर पूर्णांक iters = 5;

	tw32(cpu_base + CPU_STATE, 0xffffffff);
	tw32_f(cpu_base + CPU_PC, pc);

	क्रम (i = 0; i < iters; i++) अणु
		अगर (tr32(cpu_base + CPU_PC) == pc)
			अवरोध;
		tw32(cpu_base + CPU_STATE, 0xffffffff);
		tw32(cpu_base + CPU_MODE,  CPU_MODE_HALT);
		tw32_f(cpu_base + CPU_PC, pc);
		udelay(1000);
	पूर्ण

	वापस (i == iters) ? -EBUSY : 0;
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_load_5701_a0_firmware_fix(काष्ठा tg3 *tp)
अणु
	स्थिर काष्ठा tg3_firmware_hdr *fw_hdr;
	पूर्णांक err;

	fw_hdr = (काष्ठा tg3_firmware_hdr *)tp->fw->data;

	/* Firmware blob starts with version numbers, followed by
	   start address and length. We are setting complete length.
	   length = end_address_of_bss - start_address_of_text.
	   Reमुख्यder is the blob to be loaded contiguously
	   from start address. */

	err = tg3_load_firmware_cpu(tp, RX_CPU_BASE,
				    RX_CPU_SCRATCH_BASE, RX_CPU_SCRATCH_SIZE,
				    fw_hdr);
	अगर (err)
		वापस err;

	err = tg3_load_firmware_cpu(tp, TX_CPU_BASE,
				    TX_CPU_SCRATCH_BASE, TX_CPU_SCRATCH_SIZE,
				    fw_hdr);
	अगर (err)
		वापस err;

	/* Now startup only the RX cpu. */
	err = tg3_छोड़ो_cpu_and_set_pc(tp, RX_CPU_BASE,
				       be32_to_cpu(fw_hdr->base_addr));
	अगर (err) अणु
		netdev_err(tp->dev, "%s fails to set RX CPU PC, is %08x "
			   "should be %08x\n", __func__,
			   tr32(RX_CPU_BASE + CPU_PC),
				be32_to_cpu(fw_hdr->base_addr));
		वापस -ENODEV;
	पूर्ण

	tg3_rxcpu_resume(tp);

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_validate_rxcpu_state(काष्ठा tg3 *tp)
अणु
	स्थिर पूर्णांक iters = 1000;
	पूर्णांक i;
	u32 val;

	/* Wait क्रम boot code to complete initialization and enter service
	 * loop. It is then safe to करोwnload service patches
	 */
	क्रम (i = 0; i < iters; i++) अणु
		अगर (tr32(RX_CPU_HWBKPT) == TG3_SBROM_IN_SERVICE_LOOP)
			अवरोध;

		udelay(10);
	पूर्ण

	अगर (i == iters) अणु
		netdev_err(tp->dev, "Boot code not ready for service patches\n");
		वापस -EBUSY;
	पूर्ण

	val = tg3_पढ़ो_indirect_reg32(tp, TG3_57766_FW_HANDSHAKE);
	अगर (val & 0xff) अणु
		netdev_warn(tp->dev,
			    "Other patches exist. Not downloading EEE patch\n");
		वापस -EEXIST;
	पूर्ण

	वापस 0;
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_load_57766_firmware(काष्ठा tg3 *tp)
अणु
	काष्ठा tg3_firmware_hdr *fw_hdr;

	अगर (!tg3_flag(tp, NO_NVRAM))
		वापस;

	अगर (tg3_validate_rxcpu_state(tp))
		वापस;

	अगर (!tp->fw)
		वापस;

	/* This firmware blob has a dअगरferent क्रमmat than older firmware
	 * releases as given below. The मुख्य dअगरference is we have fragmented
	 * data to be written to non-contiguous locations.
	 *
	 * In the beginning we have a firmware header identical to other
	 * firmware which consists of version, base addr and length. The length
	 * here is unused and set to 0xffffffff.
	 *
	 * This is followed by a series of firmware fragments which are
	 * inभागidually identical to previous firmware. i.e. they have the
	 * firmware header and followed by data क्रम that fragment. The version
	 * field of the inभागidual fragment header is unused.
	 */

	fw_hdr = (काष्ठा tg3_firmware_hdr *)tp->fw->data;
	अगर (be32_to_cpu(fw_hdr->base_addr) != TG3_57766_FW_BASE_ADDR)
		वापस;

	अगर (tg3_rxcpu_छोड़ो(tp))
		वापस;

	/* tg3_load_firmware_cpu() will always succeed क्रम the 57766 */
	tg3_load_firmware_cpu(tp, 0, TG3_57766_FW_BASE_ADDR, 0, fw_hdr);

	tg3_rxcpu_resume(tp);
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_load_tso_firmware(काष्ठा tg3 *tp)
अणु
	स्थिर काष्ठा tg3_firmware_hdr *fw_hdr;
	अचिन्हित दीर्घ cpu_base, cpu_scratch_base, cpu_scratch_size;
	पूर्णांक err;

	अगर (!tg3_flag(tp, FW_TSO))
		वापस 0;

	fw_hdr = (काष्ठा tg3_firmware_hdr *)tp->fw->data;

	/* Firmware blob starts with version numbers, followed by
	   start address and length. We are setting complete length.
	   length = end_address_of_bss - start_address_of_text.
	   Reमुख्यder is the blob to be loaded contiguously
	   from start address. */

	cpu_scratch_size = tp->fw_len;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5705) अणु
		cpu_base = RX_CPU_BASE;
		cpu_scratch_base = NIC_SRAM_MBUF_POOL_BASE5705;
	पूर्ण अन्यथा अणु
		cpu_base = TX_CPU_BASE;
		cpu_scratch_base = TX_CPU_SCRATCH_BASE;
		cpu_scratch_size = TX_CPU_SCRATCH_SIZE;
	पूर्ण

	err = tg3_load_firmware_cpu(tp, cpu_base,
				    cpu_scratch_base, cpu_scratch_size,
				    fw_hdr);
	अगर (err)
		वापस err;

	/* Now startup the cpu. */
	err = tg3_छोड़ो_cpu_and_set_pc(tp, cpu_base,
				       be32_to_cpu(fw_hdr->base_addr));
	अगर (err) अणु
		netdev_err(tp->dev,
			   "%s fails to set CPU PC, is %08x should be %08x\n",
			   __func__, tr32(cpu_base + CPU_PC),
			   be32_to_cpu(fw_hdr->base_addr));
		वापस -ENODEV;
	पूर्ण

	tg3_resume_cpu(tp, cpu_base);
	वापस 0;
पूर्ण

/* tp->lock is held. */
अटल व्योम __tg3_set_one_mac_addr(काष्ठा tg3 *tp, u8 *mac_addr, पूर्णांक index)
अणु
	u32 addr_high, addr_low;

	addr_high = ((mac_addr[0] << 8) | mac_addr[1]);
	addr_low = ((mac_addr[2] << 24) | (mac_addr[3] << 16) |
		    (mac_addr[4] <<  8) | mac_addr[5]);

	अगर (index < 4) अणु
		tw32(MAC_ADDR_0_HIGH + (index * 8), addr_high);
		tw32(MAC_ADDR_0_LOW + (index * 8), addr_low);
	पूर्ण अन्यथा अणु
		index -= 4;
		tw32(MAC_EXTADDR_0_HIGH + (index * 8), addr_high);
		tw32(MAC_EXTADDR_0_LOW + (index * 8), addr_low);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम __tg3_set_mac_addr(काष्ठा tg3 *tp, bool skip_mac_1)
अणु
	u32 addr_high;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (i == 1 && skip_mac_1)
			जारी;
		__tg3_set_one_mac_addr(tp, tp->dev->dev_addr, i);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5703 ||
	    tg3_asic_rev(tp) == ASIC_REV_5704) अणु
		क्रम (i = 4; i < 16; i++)
			__tg3_set_one_mac_addr(tp, tp->dev->dev_addr, i);
	पूर्ण

	addr_high = (tp->dev->dev_addr[0] +
		     tp->dev->dev_addr[1] +
		     tp->dev->dev_addr[2] +
		     tp->dev->dev_addr[3] +
		     tp->dev->dev_addr[4] +
		     tp->dev->dev_addr[5]) &
		TX_BACKOFF_SEED_MASK;
	tw32(MAC_TX_BACKOFF_SEED, addr_high);
पूर्ण

अटल व्योम tg3_enable_रेजिस्टर_access(काष्ठा tg3 *tp)
अणु
	/*
	 * Make sure रेजिस्टर accesses (indirect or otherwise) will function
	 * correctly.
	 */
	pci_ग_लिखो_config_dword(tp->pdev,
			       TG3PCI_MISC_HOST_CTRL, tp->misc_host_ctrl);
पूर्ण

अटल पूर्णांक tg3_घातer_up(काष्ठा tg3 *tp)
अणु
	पूर्णांक err;

	tg3_enable_रेजिस्टर_access(tp);

	err = pci_set_घातer_state(tp->pdev, PCI_D0);
	अगर (!err) अणु
		/* Switch out of Vaux अगर it is a NIC */
		tg3_pwrsrc_चयन_to_vमुख्य(tp);
	पूर्ण अन्यथा अणु
		netdev_err(tp->dev, "Transition to D0 failed\n");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tg3_setup_phy(काष्ठा tg3 *, bool);

अटल पूर्णांक tg3_घातer_करोwn_prepare(काष्ठा tg3 *tp)
अणु
	u32 misc_host_ctrl;
	bool device_should_wake, करो_low_घातer;

	tg3_enable_रेजिस्टर_access(tp);

	/* Restore the CLKREQ setting. */
	अगर (tg3_flag(tp, CLKREQ_BUG))
		pcie_capability_set_word(tp->pdev, PCI_EXP_LNKCTL,
					 PCI_EXP_LNKCTL_CLKREQ_EN);

	misc_host_ctrl = tr32(TG3PCI_MISC_HOST_CTRL);
	tw32(TG3PCI_MISC_HOST_CTRL,
	     misc_host_ctrl | MISC_HOST_CTRL_MASK_PCI_INT);

	device_should_wake = device_may_wakeup(&tp->pdev->dev) &&
			     tg3_flag(tp, WOL_ENABLE);

	अगर (tg3_flag(tp, USE_PHYLIB)) अणु
		करो_low_घातer = false;
		अगर ((tp->phy_flags & TG3_PHYFLG_IS_CONNECTED) &&
		    !(tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)) अणु
			__ETHTOOL_DECLARE_LINK_MODE_MASK(advertising) = अणु 0, पूर्ण;
			काष्ठा phy_device *phydev;
			u32 phyid;

			phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

			tp->phy_flags |= TG3_PHYFLG_IS_LOW_POWER;

			tp->link_config.speed = phydev->speed;
			tp->link_config.duplex = phydev->duplex;
			tp->link_config.स्वतःneg = phydev->स्वतःneg;
			ethtool_convert_link_mode_to_legacy_u32(
				&tp->link_config.advertising,
				phydev->advertising);

			linkmode_set_bit(ETHTOOL_LINK_MODE_TP_BIT, advertising);
			linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT,
					 advertising);
			linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
					 advertising);
			linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
					 advertising);

			अगर (tg3_flag(tp, ENABLE_ASF) || device_should_wake) अणु
				अगर (tg3_flag(tp, WOL_SPEED_100MB)) अणु
					linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
							 advertising);
					linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
							 advertising);
					linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
							 advertising);
				पूर्ण अन्यथा अणु
					linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
							 advertising);
				पूर्ण
			पूर्ण

			linkmode_copy(phydev->advertising, advertising);
			phy_start_aneg(phydev);

			phyid = phydev->drv->phy_id & phydev->drv->phy_id_mask;
			अगर (phyid != PHY_ID_BCMAC131) अणु
				phyid &= PHY_BCM_OUI_MASK;
				अगर (phyid == PHY_BCM_OUI_1 ||
				    phyid == PHY_BCM_OUI_2 ||
				    phyid == PHY_BCM_OUI_3)
					करो_low_घातer = true;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		करो_low_घातer = true;

		अगर (!(tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER))
			tp->phy_flags |= TG3_PHYFLG_IS_LOW_POWER;

		अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES))
			tg3_setup_phy(tp, false);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		u32 val;

		val = tr32(GRC_VCPU_EXT_CTRL);
		tw32(GRC_VCPU_EXT_CTRL, val | GRC_VCPU_EXT_CTRL_DISABLE_WOL);
	पूर्ण अन्यथा अगर (!tg3_flag(tp, ENABLE_ASF)) अणु
		पूर्णांक i;
		u32 val;

		क्रम (i = 0; i < 200; i++) अणु
			tg3_पढ़ो_mem(tp, NIC_SRAM_FW_ASF_STATUS_MBOX, &val);
			अगर (val == ~NIC_SRAM_FIRMWARE_MBOX_MAGIC1)
				अवरोध;
			msleep(1);
		पूर्ण
	पूर्ण
	अगर (tg3_flag(tp, WOL_CAP))
		tg3_ग_लिखो_mem(tp, NIC_SRAM_WOL_MBOX, WOL_SIGNATURE |
						     WOL_DRV_STATE_SHUTDOWN |
						     WOL_DRV_WOL |
						     WOL_SET_MAGIC_PKT);

	अगर (device_should_wake) अणु
		u32 mac_mode;

		अगर (!(tp->phy_flags & TG3_PHYFLG_PHY_SERDES)) अणु
			अगर (करो_low_घातer &&
			    !(tp->phy_flags & TG3_PHYFLG_IS_FET)) अणु
				tg3_phy_auxctl_ग_लिखो(tp,
					       MII_TG3_AUXCTL_SHDWSEL_PWRCTL,
					       MII_TG3_AUXCTL_PCTL_WOL_EN |
					       MII_TG3_AUXCTL_PCTL_100TX_LPWR |
					       MII_TG3_AUXCTL_PCTL_CL_AB_TXDAC);
				udelay(40);
			पूर्ण

			अगर (tp->phy_flags & TG3_PHYFLG_MII_SERDES)
				mac_mode = MAC_MODE_PORT_MODE_GMII;
			अन्यथा अगर (tp->phy_flags &
				 TG3_PHYFLG_KEEP_LINK_ON_PWRDN) अणु
				अगर (tp->link_config.active_speed == SPEED_1000)
					mac_mode = MAC_MODE_PORT_MODE_GMII;
				अन्यथा
					mac_mode = MAC_MODE_PORT_MODE_MII;
			पूर्ण अन्यथा
				mac_mode = MAC_MODE_PORT_MODE_MII;

			mac_mode |= tp->mac_mode & MAC_MODE_LINK_POLARITY;
			अगर (tg3_asic_rev(tp) == ASIC_REV_5700) अणु
				u32 speed = tg3_flag(tp, WOL_SPEED_100MB) ?
					     SPEED_100 : SPEED_10;
				अगर (tg3_5700_link_polarity(tp, speed))
					mac_mode |= MAC_MODE_LINK_POLARITY;
				अन्यथा
					mac_mode &= ~MAC_MODE_LINK_POLARITY;
			पूर्ण
		पूर्ण अन्यथा अणु
			mac_mode = MAC_MODE_PORT_MODE_TBI;
		पूर्ण

		अगर (!tg3_flag(tp, 5750_PLUS))
			tw32(MAC_LED_CTRL, tp->led_ctrl);

		mac_mode |= MAC_MODE_MAGIC_PKT_ENABLE;
		अगर ((tg3_flag(tp, 5705_PLUS) && !tg3_flag(tp, 5780_CLASS)) &&
		    (tg3_flag(tp, ENABLE_ASF) || tg3_flag(tp, ENABLE_APE)))
			mac_mode |= MAC_MODE_KEEP_FRAME_IN_WOL;

		अगर (tg3_flag(tp, ENABLE_APE))
			mac_mode |= MAC_MODE_APE_TX_EN |
				    MAC_MODE_APE_RX_EN |
				    MAC_MODE_TDE_ENABLE;

		tw32_f(MAC_MODE, mac_mode);
		udelay(100);

		tw32_f(MAC_RX_MODE, RX_MODE_ENABLE);
		udelay(10);
	पूर्ण

	अगर (!tg3_flag(tp, WOL_SPEED_100MB) &&
	    (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	     tg3_asic_rev(tp) == ASIC_REV_5701)) अणु
		u32 base_val;

		base_val = tp->pci_घड़ी_ctrl;
		base_val |= (CLOCK_CTRL_RXCLK_DISABLE |
			     CLOCK_CTRL_TXCLK_DISABLE);

		tw32_रुको_f(TG3PCI_CLOCK_CTRL, base_val | CLOCK_CTRL_ALTCLK |
			    CLOCK_CTRL_PWRDOWN_PLL133, 40);
	पूर्ण अन्यथा अगर (tg3_flag(tp, 5780_CLASS) ||
		   tg3_flag(tp, CPMU_PRESENT) ||
		   tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		/* करो nothing */
	पूर्ण अन्यथा अगर (!(tg3_flag(tp, 5750_PLUS) && tg3_flag(tp, ENABLE_ASF))) अणु
		u32 newbits1, newbits2;

		अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
		    tg3_asic_rev(tp) == ASIC_REV_5701) अणु
			newbits1 = (CLOCK_CTRL_RXCLK_DISABLE |
				    CLOCK_CTRL_TXCLK_DISABLE |
				    CLOCK_CTRL_ALTCLK);
			newbits2 = newbits1 | CLOCK_CTRL_44MHZ_CORE;
		पूर्ण अन्यथा अगर (tg3_flag(tp, 5705_PLUS)) अणु
			newbits1 = CLOCK_CTRL_625_CORE;
			newbits2 = newbits1 | CLOCK_CTRL_ALTCLK;
		पूर्ण अन्यथा अणु
			newbits1 = CLOCK_CTRL_ALTCLK;
			newbits2 = newbits1 | CLOCK_CTRL_44MHZ_CORE;
		पूर्ण

		tw32_रुको_f(TG3PCI_CLOCK_CTRL, tp->pci_घड़ी_ctrl | newbits1,
			    40);

		tw32_रुको_f(TG3PCI_CLOCK_CTRL, tp->pci_घड़ी_ctrl | newbits2,
			    40);

		अगर (!tg3_flag(tp, 5705_PLUS)) अणु
			u32 newbits3;

			अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
			    tg3_asic_rev(tp) == ASIC_REV_5701) अणु
				newbits3 = (CLOCK_CTRL_RXCLK_DISABLE |
					    CLOCK_CTRL_TXCLK_DISABLE |
					    CLOCK_CTRL_44MHZ_CORE);
			पूर्ण अन्यथा अणु
				newbits3 = CLOCK_CTRL_44MHZ_CORE;
			पूर्ण

			tw32_रुको_f(TG3PCI_CLOCK_CTRL,
				    tp->pci_घड़ी_ctrl | newbits3, 40);
		पूर्ण
	पूर्ण

	अगर (!(device_should_wake) && !tg3_flag(tp, ENABLE_ASF))
		tg3_घातer_करोwn_phy(tp, करो_low_घातer);

	tg3_frob_aux_घातer(tp, true);

	/* Workaround क्रम unstable PLL घड़ी */
	अगर ((!tg3_flag(tp, IS_SSB_CORE)) &&
	    ((tg3_chip_rev(tp) == CHIPREV_5750_AX) ||
	     (tg3_chip_rev(tp) == CHIPREV_5750_BX))) अणु
		u32 val = tr32(0x7d00);

		val &= ~((1 << 16) | (1 << 4) | (1 << 2) | (1 << 1) | 1);
		tw32(0x7d00, val);
		अगर (!tg3_flag(tp, ENABLE_ASF)) अणु
			पूर्णांक err;

			err = tg3_nvram_lock(tp);
			tg3_halt_cpu(tp, RX_CPU_BASE);
			अगर (!err)
				tg3_nvram_unlock(tp);
		पूर्ण
	पूर्ण

	tg3_ग_लिखो_sig_post_reset(tp, RESET_KIND_SHUTDOWN);

	tg3_ape_driver_state_change(tp, RESET_KIND_SHUTDOWN);

	वापस 0;
पूर्ण

अटल व्योम tg3_घातer_करोwn(काष्ठा tg3 *tp)
अणु
	pci_wake_from_d3(tp->pdev, tg3_flag(tp, WOL_ENABLE));
	pci_set_घातer_state(tp->pdev, PCI_D3hot);
पूर्ण

अटल व्योम tg3_aux_stat_to_speed_duplex(काष्ठा tg3 *tp, u32 val, u32 *speed, u8 *duplex)
अणु
	चयन (val & MII_TG3_AUX_STAT_SPDMASK) अणु
	हाल MII_TG3_AUX_STAT_10HALF:
		*speed = SPEED_10;
		*duplex = DUPLEX_HALF;
		अवरोध;

	हाल MII_TG3_AUX_STAT_10FULL:
		*speed = SPEED_10;
		*duplex = DUPLEX_FULL;
		अवरोध;

	हाल MII_TG3_AUX_STAT_100HALF:
		*speed = SPEED_100;
		*duplex = DUPLEX_HALF;
		अवरोध;

	हाल MII_TG3_AUX_STAT_100FULL:
		*speed = SPEED_100;
		*duplex = DUPLEX_FULL;
		अवरोध;

	हाल MII_TG3_AUX_STAT_1000HALF:
		*speed = SPEED_1000;
		*duplex = DUPLEX_HALF;
		अवरोध;

	हाल MII_TG3_AUX_STAT_1000FULL:
		*speed = SPEED_1000;
		*duplex = DUPLEX_FULL;
		अवरोध;

	शेष:
		अगर (tp->phy_flags & TG3_PHYFLG_IS_FET) अणु
			*speed = (val & MII_TG3_AUX_STAT_100) ? SPEED_100 :
				 SPEED_10;
			*duplex = (val & MII_TG3_AUX_STAT_FULL) ? DUPLEX_FULL :
				  DUPLEX_HALF;
			अवरोध;
		पूर्ण
		*speed = SPEED_UNKNOWN;
		*duplex = DUPLEX_UNKNOWN;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_phy_स्वतःneg_cfg(काष्ठा tg3 *tp, u32 advertise, u32 flowctrl)
अणु
	पूर्णांक err = 0;
	u32 val, new_adv;

	new_adv = ADVERTISE_CSMA;
	new_adv |= ethtool_adv_to_mii_adv_t(advertise) & ADVERTISE_ALL;
	new_adv |= mii_advertise_flowctrl(flowctrl);

	err = tg3_ग_लिखोphy(tp, MII_ADVERTISE, new_adv);
	अगर (err)
		जाओ करोne;

	अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) अणु
		new_adv = ethtool_adv_to_mii_ctrl1000_t(advertise);

		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0 ||
		    tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B0)
			new_adv |= CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER;

		err = tg3_ग_लिखोphy(tp, MII_CTRL1000, new_adv);
		अगर (err)
			जाओ करोne;
	पूर्ण

	अगर (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP))
		जाओ करोne;

	tw32(TG3_CPMU_EEE_MODE,
	     tr32(TG3_CPMU_EEE_MODE) & ~TG3_CPMU_EEEMD_LPI_ENABLE);

	err = tg3_phy_toggle_auxctl_smdsp(tp, true);
	अगर (!err) अणु
		u32 err2;

		val = 0;
		/* Advertise 100-BaseTX EEE ability */
		अगर (advertise & ADVERTISED_100baseT_Full)
			val |= MDIO_AN_EEE_ADV_100TX;
		/* Advertise 1000-BaseT EEE ability */
		अगर (advertise & ADVERTISED_1000baseT_Full)
			val |= MDIO_AN_EEE_ADV_1000T;

		अगर (!tp->eee.eee_enabled) अणु
			val = 0;
			tp->eee.advertised = 0;
		पूर्ण अन्यथा अणु
			tp->eee.advertised = advertise &
					     (ADVERTISED_100baseT_Full |
					      ADVERTISED_1000baseT_Full);
		पूर्ण

		err = tg3_phy_cl45_ग_लिखो(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV, val);
		अगर (err)
			val = 0;

		चयन (tg3_asic_rev(tp)) अणु
		हाल ASIC_REV_5717:
		हाल ASIC_REV_57765:
		हाल ASIC_REV_57766:
		हाल ASIC_REV_5719:
			/* If we advertised any eee advertisements above... */
			अगर (val)
				val = MII_TG3_DSP_TAP26_ALNOKO |
				      MII_TG3_DSP_TAP26_RMRXSTO |
				      MII_TG3_DSP_TAP26_OPCSINPT;
			tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_TAP26, val);
			fallthrough;
		हाल ASIC_REV_5720:
		हाल ASIC_REV_5762:
			अगर (!tg3_phydsp_पढ़ो(tp, MII_TG3_DSP_CH34TP2, &val))
				tg3_phydsp_ग_लिखो(tp, MII_TG3_DSP_CH34TP2, val |
						 MII_TG3_DSP_CH34TP2_HIBW01);
		पूर्ण

		err2 = tg3_phy_toggle_auxctl_smdsp(tp, false);
		अगर (!err)
			err = err2;
	पूर्ण

करोne:
	वापस err;
पूर्ण

अटल व्योम tg3_phy_copper_begin(काष्ठा tg3 *tp)
अणु
	अगर (tp->link_config.स्वतःneg == AUTONEG_ENABLE ||
	    (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)) अणु
		u32 adv, fc;

		अगर ((tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER) &&
		    !(tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN)) अणु
			adv = ADVERTISED_10baseT_Half |
			      ADVERTISED_10baseT_Full;
			अगर (tg3_flag(tp, WOL_SPEED_100MB))
				adv |= ADVERTISED_100baseT_Half |
				       ADVERTISED_100baseT_Full;
			अगर (tp->phy_flags & TG3_PHYFLG_1G_ON_VAUX_OK) अणु
				अगर (!(tp->phy_flags &
				      TG3_PHYFLG_DISABLE_1G_HD_ADV))
					adv |= ADVERTISED_1000baseT_Half;
				adv |= ADVERTISED_1000baseT_Full;
			पूर्ण

			fc = FLOW_CTRL_TX | FLOW_CTRL_RX;
		पूर्ण अन्यथा अणु
			adv = tp->link_config.advertising;
			अगर (tp->phy_flags & TG3_PHYFLG_10_100_ONLY)
				adv &= ~(ADVERTISED_1000baseT_Half |
					 ADVERTISED_1000baseT_Full);

			fc = tp->link_config.flowctrl;
		पूर्ण

		tg3_phy_स्वतःneg_cfg(tp, adv, fc);

		अगर ((tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER) &&
		    (tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN)) अणु
			/* Normally during घातer करोwn we want to स्वतःnegotiate
			 * the lowest possible speed क्रम WOL. However, to aव्योम
			 * link flap, we leave it untouched.
			 */
			वापस;
		पूर्ण

		tg3_ग_लिखोphy(tp, MII_BMCR,
			     BMCR_ANENABLE | BMCR_ANRESTART);
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		u32 bmcr, orig_bmcr;

		tp->link_config.active_speed = tp->link_config.speed;
		tp->link_config.active_duplex = tp->link_config.duplex;

		अगर (tg3_asic_rev(tp) == ASIC_REV_5714) अणु
			/* With स्वतःneg disabled, 5715 only links up when the
			 * advertisement रेजिस्टर has the configured speed
			 * enabled.
			 */
			tg3_ग_लिखोphy(tp, MII_ADVERTISE, ADVERTISE_ALL);
		पूर्ण

		bmcr = 0;
		चयन (tp->link_config.speed) अणु
		शेष:
		हाल SPEED_10:
			अवरोध;

		हाल SPEED_100:
			bmcr |= BMCR_SPEED100;
			अवरोध;

		हाल SPEED_1000:
			bmcr |= BMCR_SPEED1000;
			अवरोध;
		पूर्ण

		अगर (tp->link_config.duplex == DUPLEX_FULL)
			bmcr |= BMCR_FULLDPLX;

		अगर (!tg3_पढ़ोphy(tp, MII_BMCR, &orig_bmcr) &&
		    (bmcr != orig_bmcr)) अणु
			tg3_ग_लिखोphy(tp, MII_BMCR, BMCR_LOOPBACK);
			क्रम (i = 0; i < 1500; i++) अणु
				u32 पंचांगp;

				udelay(10);
				अगर (tg3_पढ़ोphy(tp, MII_BMSR, &पंचांगp) ||
				    tg3_पढ़ोphy(tp, MII_BMSR, &पंचांगp))
					जारी;
				अगर (!(पंचांगp & BMSR_LSTATUS)) अणु
					udelay(40);
					अवरोध;
				पूर्ण
			पूर्ण
			tg3_ग_लिखोphy(tp, MII_BMCR, bmcr);
			udelay(40);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_phy_pull_config(काष्ठा tg3 *tp)
अणु
	पूर्णांक err;
	u32 val;

	err = tg3_पढ़ोphy(tp, MII_BMCR, &val);
	अगर (err)
		जाओ करोne;

	अगर (!(val & BMCR_ANENABLE)) अणु
		tp->link_config.स्वतःneg = AUTONEG_DISABLE;
		tp->link_config.advertising = 0;
		tg3_flag_clear(tp, PAUSE_AUTONEG);

		err = -EIO;

		चयन (val & (BMCR_SPEED1000 | BMCR_SPEED100)) अणु
		हाल 0:
			अगर (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
				जाओ करोne;

			tp->link_config.speed = SPEED_10;
			अवरोध;
		हाल BMCR_SPEED100:
			अगर (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
				जाओ करोne;

			tp->link_config.speed = SPEED_100;
			अवरोध;
		हाल BMCR_SPEED1000:
			अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) अणु
				tp->link_config.speed = SPEED_1000;
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			जाओ करोne;
		पूर्ण

		अगर (val & BMCR_FULLDPLX)
			tp->link_config.duplex = DUPLEX_FULL;
		अन्यथा
			tp->link_config.duplex = DUPLEX_HALF;

		tp->link_config.flowctrl = FLOW_CTRL_RX | FLOW_CTRL_TX;

		err = 0;
		जाओ करोne;
	पूर्ण

	tp->link_config.स्वतःneg = AUTONEG_ENABLE;
	tp->link_config.advertising = ADVERTISED_Autoneg;
	tg3_flag_set(tp, PAUSE_AUTONEG);

	अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) अणु
		u32 adv;

		err = tg3_पढ़ोphy(tp, MII_ADVERTISE, &val);
		अगर (err)
			जाओ करोne;

		adv = mii_adv_to_ethtool_adv_t(val & ADVERTISE_ALL);
		tp->link_config.advertising |= adv | ADVERTISED_TP;

		tp->link_config.flowctrl = tg3_decode_flowctrl_1000T(val);
	पूर्ण अन्यथा अणु
		tp->link_config.advertising |= ADVERTISED_FIBRE;
	पूर्ण

	अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) अणु
		u32 adv;

		अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) अणु
			err = tg3_पढ़ोphy(tp, MII_CTRL1000, &val);
			अगर (err)
				जाओ करोne;

			adv = mii_ctrl1000_to_ethtool_adv_t(val);
		पूर्ण अन्यथा अणु
			err = tg3_पढ़ोphy(tp, MII_ADVERTISE, &val);
			अगर (err)
				जाओ करोne;

			adv = tg3_decode_flowctrl_1000X(val);
			tp->link_config.flowctrl = adv;

			val &= (ADVERTISE_1000XHALF | ADVERTISE_1000XFULL);
			adv = mii_adv_to_ethtool_adv_x(val);
		पूर्ण

		tp->link_config.advertising |= adv;
	पूर्ण

करोne:
	वापस err;
पूर्ण

अटल पूर्णांक tg3_init_5401phy_dsp(काष्ठा tg3 *tp)
अणु
	पूर्णांक err;

	/* Turn off tap घातer management. */
	/* Set Extended packet length bit */
	err = tg3_phy_auxctl_ग_लिखो(tp, MII_TG3_AUXCTL_SHDWSEL_AUXCTL, 0x4c20);

	err |= tg3_phydsp_ग_लिखो(tp, 0x0012, 0x1804);
	err |= tg3_phydsp_ग_लिखो(tp, 0x0013, 0x1204);
	err |= tg3_phydsp_ग_लिखो(tp, 0x8006, 0x0132);
	err |= tg3_phydsp_ग_लिखो(tp, 0x8006, 0x0232);
	err |= tg3_phydsp_ग_लिखो(tp, 0x201f, 0x0a20);

	udelay(40);

	वापस err;
पूर्ण

अटल bool tg3_phy_eee_config_ok(काष्ठा tg3 *tp)
अणु
	काष्ठा ethtool_eee eee;

	अगर (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP))
		वापस true;

	tg3_eee_pull_config(tp, &eee);

	अगर (tp->eee.eee_enabled) अणु
		अगर (tp->eee.advertised != eee.advertised ||
		    tp->eee.tx_lpi_समयr != eee.tx_lpi_समयr ||
		    tp->eee.tx_lpi_enabled != eee.tx_lpi_enabled)
			वापस false;
	पूर्ण अन्यथा अणु
		/* EEE is disabled but we're advertising */
		अगर (eee.advertised)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool tg3_phy_copper_an_config_ok(काष्ठा tg3 *tp, u32 *lcladv)
अणु
	u32 advmsk, tgtadv, advertising;

	advertising = tp->link_config.advertising;
	tgtadv = ethtool_adv_to_mii_adv_t(advertising) & ADVERTISE_ALL;

	advmsk = ADVERTISE_ALL;
	अगर (tp->link_config.active_duplex == DUPLEX_FULL) अणु
		tgtadv |= mii_advertise_flowctrl(tp->link_config.flowctrl);
		advmsk |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
	पूर्ण

	अगर (tg3_पढ़ोphy(tp, MII_ADVERTISE, lcladv))
		वापस false;

	अगर ((*lcladv & advmsk) != tgtadv)
		वापस false;

	अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) अणु
		u32 tg3_ctrl;

		tgtadv = ethtool_adv_to_mii_ctrl1000_t(advertising);

		अगर (tg3_पढ़ोphy(tp, MII_CTRL1000, &tg3_ctrl))
			वापस false;

		अगर (tgtadv &&
		    (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0 ||
		     tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B0)) अणु
			tgtadv |= CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER;
			tg3_ctrl &= (ADVERTISE_1000HALF | ADVERTISE_1000FULL |
				     CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER);
		पूर्ण अन्यथा अणु
			tg3_ctrl &= (ADVERTISE_1000HALF | ADVERTISE_1000FULL);
		पूर्ण

		अगर (tg3_ctrl != tgtadv)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool tg3_phy_copper_fetch_rmtadv(काष्ठा tg3 *tp, u32 *rmtadv)
अणु
	u32 lpeth = 0;

	अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) अणु
		u32 val;

		अगर (tg3_पढ़ोphy(tp, MII_STAT1000, &val))
			वापस false;

		lpeth = mii_stat1000_to_ethtool_lpa_t(val);
	पूर्ण

	अगर (tg3_पढ़ोphy(tp, MII_LPA, rmtadv))
		वापस false;

	lpeth |= mii_lpa_to_ethtool_lpa_t(*rmtadv);
	tp->link_config.rmt_adv = lpeth;

	वापस true;
पूर्ण

अटल bool tg3_test_and_report_link_chg(काष्ठा tg3 *tp, bool curr_link_up)
अणु
	अगर (curr_link_up != tp->link_up) अणु
		अगर (curr_link_up) अणु
			netअगर_carrier_on(tp->dev);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(tp->dev);
			अगर (tp->phy_flags & TG3_PHYFLG_MII_SERDES)
				tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
		पूर्ण

		tg3_link_report(tp);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम tg3_clear_mac_status(काष्ठा tg3 *tp)
अणु
	tw32(MAC_EVENT, 0);

	tw32_f(MAC_STATUS,
	       MAC_STATUS_SYNC_CHANGED |
	       MAC_STATUS_CFG_CHANGED |
	       MAC_STATUS_MI_COMPLETION |
	       MAC_STATUS_LNKSTATE_CHANGED);
	udelay(40);
पूर्ण

अटल व्योम tg3_setup_eee(काष्ठा tg3 *tp)
अणु
	u32 val;

	val = TG3_CPMU_EEE_LNKIDL_PCIE_NL0 |
	      TG3_CPMU_EEE_LNKIDL_UART_IDL;
	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_57765_A0)
		val |= TG3_CPMU_EEE_LNKIDL_APE_TX_MT;

	tw32_f(TG3_CPMU_EEE_LNKIDL_CTRL, val);

	tw32_f(TG3_CPMU_EEE_CTRL,
	       TG3_CPMU_EEE_CTRL_EXIT_20_1_US);

	val = TG3_CPMU_EEEMD_ERLY_L1_XIT_DET |
	      (tp->eee.tx_lpi_enabled ? TG3_CPMU_EEEMD_LPI_IN_TX : 0) |
	      TG3_CPMU_EEEMD_LPI_IN_RX |
	      TG3_CPMU_EEEMD_EEE_ENABLE;

	अगर (tg3_asic_rev(tp) != ASIC_REV_5717)
		val |= TG3_CPMU_EEEMD_SND_IDX_DET_EN;

	अगर (tg3_flag(tp, ENABLE_APE))
		val |= TG3_CPMU_EEEMD_APE_TX_DET_EN;

	tw32_f(TG3_CPMU_EEE_MODE, tp->eee.eee_enabled ? val : 0);

	tw32_f(TG3_CPMU_EEE_DBTMR1,
	       TG3_CPMU_DBTMR1_PCIEXIT_2047US |
	       (tp->eee.tx_lpi_समयr & 0xffff));

	tw32_f(TG3_CPMU_EEE_DBTMR2,
	       TG3_CPMU_DBTMR2_APE_TX_2047US |
	       TG3_CPMU_DBTMR2_TXIDXEQ_2047US);
पूर्ण

अटल पूर्णांक tg3_setup_copper_phy(काष्ठा tg3 *tp, bool क्रमce_reset)
अणु
	bool current_link_up;
	u32 bmsr, val;
	u32 lcl_adv, rmt_adv;
	u32 current_speed;
	u8 current_duplex;
	पूर्णांक i, err;

	tg3_clear_mac_status(tp);

	अगर ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) अणु
		tw32_f(MAC_MI_MODE,
		     (tp->mi_mode & ~MAC_MI_MODE_AUTO_POLL));
		udelay(80);
	पूर्ण

	tg3_phy_auxctl_ग_लिखो(tp, MII_TG3_AUXCTL_SHDWSEL_PWRCTL, 0);

	/* Some third-party PHYs need to be reset on link going
	 * करोwn.
	 */
	अगर ((tg3_asic_rev(tp) == ASIC_REV_5703 ||
	     tg3_asic_rev(tp) == ASIC_REV_5704 ||
	     tg3_asic_rev(tp) == ASIC_REV_5705) &&
	    tp->link_up) अणु
		tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
		अगर (!tg3_पढ़ोphy(tp, MII_BMSR, &bmsr) &&
		    !(bmsr & BMSR_LSTATUS))
			क्रमce_reset = true;
	पूर्ण
	अगर (क्रमce_reset)
		tg3_phy_reset(tp);

	अगर ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5401) अणु
		tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
		अगर (tg3_पढ़ोphy(tp, MII_BMSR, &bmsr) ||
		    !tg3_flag(tp, INIT_COMPLETE))
			bmsr = 0;

		अगर (!(bmsr & BMSR_LSTATUS)) अणु
			err = tg3_init_5401phy_dsp(tp);
			अगर (err)
				वापस err;

			tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
			क्रम (i = 0; i < 1000; i++) अणु
				udelay(10);
				अगर (!tg3_पढ़ोphy(tp, MII_BMSR, &bmsr) &&
				    (bmsr & BMSR_LSTATUS)) अणु
					udelay(40);
					अवरोध;
				पूर्ण
			पूर्ण

			अगर ((tp->phy_id & TG3_PHY_ID_REV_MASK) ==
			    TG3_PHY_REV_BCM5401_B0 &&
			    !(bmsr & BMSR_LSTATUS) &&
			    tp->link_config.active_speed == SPEED_1000) अणु
				err = tg3_phy_reset(tp);
				अगर (!err)
					err = tg3_init_5401phy_dsp(tp);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0 ||
		   tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B0) अणु
		/* 5701 अणुA0,B0पूर्ण CRC bug workaround */
		tg3_ग_लिखोphy(tp, 0x15, 0x0a75);
		tg3_ग_लिखोphy(tp, MII_TG3_MISC_SHDW, 0x8c68);
		tg3_ग_लिखोphy(tp, MII_TG3_MISC_SHDW, 0x8d68);
		tg3_ग_लिखोphy(tp, MII_TG3_MISC_SHDW, 0x8c68);
	पूर्ण

	/* Clear pending पूर्णांकerrupts... */
	tg3_पढ़ोphy(tp, MII_TG3_ISTAT, &val);
	tg3_पढ़ोphy(tp, MII_TG3_ISTAT, &val);

	अगर (tp->phy_flags & TG3_PHYFLG_USE_MI_INTERRUPT)
		tg3_ग_लिखोphy(tp, MII_TG3_IMASK, ~MII_TG3_INT_LINKCHG);
	अन्यथा अगर (!(tp->phy_flags & TG3_PHYFLG_IS_FET))
		tg3_ग_लिखोphy(tp, MII_TG3_IMASK, ~0);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701) अणु
		अगर (tp->led_ctrl == LED_CTRL_MODE_PHY_1)
			tg3_ग_लिखोphy(tp, MII_TG3_EXT_CTRL,
				     MII_TG3_EXT_CTRL_LNK3_LED_MODE);
		अन्यथा
			tg3_ग_लिखोphy(tp, MII_TG3_EXT_CTRL, 0);
	पूर्ण

	current_link_up = false;
	current_speed = SPEED_UNKNOWN;
	current_duplex = DUPLEX_UNKNOWN;
	tp->phy_flags &= ~TG3_PHYFLG_MDIX_STATE;
	tp->link_config.rmt_adv = 0;

	अगर (tp->phy_flags & TG3_PHYFLG_CAPACITIVE_COUPLING) अणु
		err = tg3_phy_auxctl_पढ़ो(tp,
					  MII_TG3_AUXCTL_SHDWSEL_MISCTEST,
					  &val);
		अगर (!err && !(val & (1 << 10))) अणु
			tg3_phy_auxctl_ग_लिखो(tp,
					     MII_TG3_AUXCTL_SHDWSEL_MISCTEST,
					     val | (1 << 10));
			जाओ relink;
		पूर्ण
	पूर्ण

	bmsr = 0;
	क्रम (i = 0; i < 100; i++) अणु
		tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
		अगर (!tg3_पढ़ोphy(tp, MII_BMSR, &bmsr) &&
		    (bmsr & BMSR_LSTATUS))
			अवरोध;
		udelay(40);
	पूर्ण

	अगर (bmsr & BMSR_LSTATUS) अणु
		u32 aux_stat, bmcr;

		tg3_पढ़ोphy(tp, MII_TG3_AUX_STAT, &aux_stat);
		क्रम (i = 0; i < 2000; i++) अणु
			udelay(10);
			अगर (!tg3_पढ़ोphy(tp, MII_TG3_AUX_STAT, &aux_stat) &&
			    aux_stat)
				अवरोध;
		पूर्ण

		tg3_aux_stat_to_speed_duplex(tp, aux_stat,
					     &current_speed,
					     &current_duplex);

		bmcr = 0;
		क्रम (i = 0; i < 200; i++) अणु
			tg3_पढ़ोphy(tp, MII_BMCR, &bmcr);
			अगर (tg3_पढ़ोphy(tp, MII_BMCR, &bmcr))
				जारी;
			अगर (bmcr && bmcr != 0x7fff)
				अवरोध;
			udelay(10);
		पूर्ण

		lcl_adv = 0;
		rmt_adv = 0;

		tp->link_config.active_speed = current_speed;
		tp->link_config.active_duplex = current_duplex;

		अगर (tp->link_config.स्वतःneg == AUTONEG_ENABLE) अणु
			bool eee_config_ok = tg3_phy_eee_config_ok(tp);

			अगर ((bmcr & BMCR_ANENABLE) &&
			    eee_config_ok &&
			    tg3_phy_copper_an_config_ok(tp, &lcl_adv) &&
			    tg3_phy_copper_fetch_rmtadv(tp, &rmt_adv))
				current_link_up = true;

			/* EEE settings changes take effect only after a phy
			 * reset.  If we have skipped a reset due to Link Flap
			 * Aव्योमance being enabled, करो it now.
			 */
			अगर (!eee_config_ok &&
			    (tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN) &&
			    !क्रमce_reset) अणु
				tg3_setup_eee(tp);
				tg3_phy_reset(tp);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(bmcr & BMCR_ANENABLE) &&
			    tp->link_config.speed == current_speed &&
			    tp->link_config.duplex == current_duplex) अणु
				current_link_up = true;
			पूर्ण
		पूर्ण

		अगर (current_link_up &&
		    tp->link_config.active_duplex == DUPLEX_FULL) अणु
			u32 reg, bit;

			अगर (tp->phy_flags & TG3_PHYFLG_IS_FET) अणु
				reg = MII_TG3_FET_GEN_STAT;
				bit = MII_TG3_FET_GEN_STAT_MDIXSTAT;
			पूर्ण अन्यथा अणु
				reg = MII_TG3_EXT_STAT;
				bit = MII_TG3_EXT_STAT_MDIX;
			पूर्ण

			अगर (!tg3_पढ़ोphy(tp, reg, &val) && (val & bit))
				tp->phy_flags |= TG3_PHYFLG_MDIX_STATE;

			tg3_setup_flow_control(tp, lcl_adv, rmt_adv);
		पूर्ण
	पूर्ण

relink:
	अगर (!current_link_up || (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)) अणु
		tg3_phy_copper_begin(tp);

		अगर (tg3_flag(tp, ROBOSWITCH)) अणु
			current_link_up = true;
			/* FIXME: when BCM5325 चयन is used use 100 MBit/s */
			current_speed = SPEED_1000;
			current_duplex = DUPLEX_FULL;
			tp->link_config.active_speed = current_speed;
			tp->link_config.active_duplex = current_duplex;
		पूर्ण

		tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
		अगर ((!tg3_पढ़ोphy(tp, MII_BMSR, &bmsr) && (bmsr & BMSR_LSTATUS)) ||
		    (tp->mac_mode & MAC_MODE_PORT_INT_LPBACK))
			current_link_up = true;
	पूर्ण

	tp->mac_mode &= ~MAC_MODE_PORT_MODE_MASK;
	अगर (current_link_up) अणु
		अगर (tp->link_config.active_speed == SPEED_100 ||
		    tp->link_config.active_speed == SPEED_10)
			tp->mac_mode |= MAC_MODE_PORT_MODE_MII;
		अन्यथा
			tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;
	पूर्ण अन्यथा अगर (tp->phy_flags & TG3_PHYFLG_IS_FET)
		tp->mac_mode |= MAC_MODE_PORT_MODE_MII;
	अन्यथा
		tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;

	/* In order क्रम the 5750 core in BCM4785 chip to work properly
	 * in RGMII mode, the Led Control Register must be set up.
	 */
	अगर (tg3_flag(tp, RGMII_MODE)) अणु
		u32 led_ctrl = tr32(MAC_LED_CTRL);
		led_ctrl &= ~(LED_CTRL_1000MBPS_ON | LED_CTRL_100MBPS_ON);

		अगर (tp->link_config.active_speed == SPEED_10)
			led_ctrl |= LED_CTRL_LNKLED_OVERRIDE;
		अन्यथा अगर (tp->link_config.active_speed == SPEED_100)
			led_ctrl |= (LED_CTRL_LNKLED_OVERRIDE |
				     LED_CTRL_100MBPS_ON);
		अन्यथा अगर (tp->link_config.active_speed == SPEED_1000)
			led_ctrl |= (LED_CTRL_LNKLED_OVERRIDE |
				     LED_CTRL_1000MBPS_ON);

		tw32(MAC_LED_CTRL, led_ctrl);
		udelay(40);
	पूर्ण

	tp->mac_mode &= ~MAC_MODE_HALF_DUPLEX;
	अगर (tp->link_config.active_duplex == DUPLEX_HALF)
		tp->mac_mode |= MAC_MODE_HALF_DUPLEX;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5700) अणु
		अगर (current_link_up &&
		    tg3_5700_link_polarity(tp, tp->link_config.active_speed))
			tp->mac_mode |= MAC_MODE_LINK_POLARITY;
		अन्यथा
			tp->mac_mode &= ~MAC_MODE_LINK_POLARITY;
	पूर्ण

	/* ??? Without this setting Netgear GA302T PHY करोes not
	 * ??? send/receive packets...
	 */
	अगर ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5411 &&
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5700_ALTIMA) अणु
		tp->mi_mode |= MAC_MI_MODE_AUTO_POLL;
		tw32_f(MAC_MI_MODE, tp->mi_mode);
		udelay(80);
	पूर्ण

	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	tg3_phy_eee_adjust(tp, current_link_up);

	अगर (tg3_flag(tp, USE_LINKCHG_REG)) अणु
		/* Polled via समयr. */
		tw32_f(MAC_EVENT, 0);
	पूर्ण अन्यथा अणु
		tw32_f(MAC_EVENT, MAC_EVENT_LNKSTATE_CHANGED);
	पूर्ण
	udelay(40);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5700 &&
	    current_link_up &&
	    tp->link_config.active_speed == SPEED_1000 &&
	    (tg3_flag(tp, PCIX_MODE) || tg3_flag(tp, PCI_HIGH_SPEED))) अणु
		udelay(120);
		tw32_f(MAC_STATUS,
		     (MAC_STATUS_SYNC_CHANGED |
		      MAC_STATUS_CFG_CHANGED));
		udelay(40);
		tg3_ग_लिखो_mem(tp,
			      NIC_SRAM_FIRMWARE_MBOX,
			      NIC_SRAM_FIRMWARE_MBOX_MAGIC2);
	पूर्ण

	/* Prevent send BD corruption. */
	अगर (tg3_flag(tp, CLKREQ_BUG)) अणु
		अगर (tp->link_config.active_speed == SPEED_100 ||
		    tp->link_config.active_speed == SPEED_10)
			pcie_capability_clear_word(tp->pdev, PCI_EXP_LNKCTL,
						   PCI_EXP_LNKCTL_CLKREQ_EN);
		अन्यथा
			pcie_capability_set_word(tp->pdev, PCI_EXP_LNKCTL,
						 PCI_EXP_LNKCTL_CLKREQ_EN);
	पूर्ण

	tg3_test_and_report_link_chg(tp, current_link_up);

	वापस 0;
पूर्ण

काष्ठा tg3_fiber_aneginfo अणु
	पूर्णांक state;
#घोषणा ANEG_STATE_UNKNOWN		0
#घोषणा ANEG_STATE_AN_ENABLE		1
#घोषणा ANEG_STATE_RESTART_INIT		2
#घोषणा ANEG_STATE_RESTART		3
#घोषणा ANEG_STATE_DISABLE_LINK_OK	4
#घोषणा ANEG_STATE_ABILITY_DETECT_INIT	5
#घोषणा ANEG_STATE_ABILITY_DETECT	6
#घोषणा ANEG_STATE_ACK_DETECT_INIT	7
#घोषणा ANEG_STATE_ACK_DETECT		8
#घोषणा ANEG_STATE_COMPLETE_ACK_INIT	9
#घोषणा ANEG_STATE_COMPLETE_ACK		10
#घोषणा ANEG_STATE_IDLE_DETECT_INIT	11
#घोषणा ANEG_STATE_IDLE_DETECT		12
#घोषणा ANEG_STATE_LINK_OK		13
#घोषणा ANEG_STATE_NEXT_PAGE_WAIT_INIT	14
#घोषणा ANEG_STATE_NEXT_PAGE_WAIT	15

	u32 flags;
#घोषणा MR_AN_ENABLE		0x00000001
#घोषणा MR_RESTART_AN		0x00000002
#घोषणा MR_AN_COMPLETE		0x00000004
#घोषणा MR_PAGE_RX		0x00000008
#घोषणा MR_NP_LOADED		0x00000010
#घोषणा MR_TOGGLE_TX		0x00000020
#घोषणा MR_LP_ADV_FULL_DUPLEX	0x00000040
#घोषणा MR_LP_ADV_HALF_DUPLEX	0x00000080
#घोषणा MR_LP_ADV_SYM_PAUSE	0x00000100
#घोषणा MR_LP_ADV_ASYM_PAUSE	0x00000200
#घोषणा MR_LP_ADV_REMOTE_FAULT1	0x00000400
#घोषणा MR_LP_ADV_REMOTE_FAULT2	0x00000800
#घोषणा MR_LP_ADV_NEXT_PAGE	0x00001000
#घोषणा MR_TOGGLE_RX		0x00002000
#घोषणा MR_NP_RX		0x00004000

#घोषणा MR_LINK_OK		0x80000000

	अचिन्हित दीर्घ link_समय, cur_समय;

	u32 ability_match_cfg;
	पूर्णांक ability_match_count;

	अक्षर ability_match, idle_match, ack_match;

	u32 txconfig, rxconfig;
#घोषणा ANEG_CFG_NP		0x00000080
#घोषणा ANEG_CFG_ACK		0x00000040
#घोषणा ANEG_CFG_RF2		0x00000020
#घोषणा ANEG_CFG_RF1		0x00000010
#घोषणा ANEG_CFG_PS2		0x00000001
#घोषणा ANEG_CFG_PS1		0x00008000
#घोषणा ANEG_CFG_HD		0x00004000
#घोषणा ANEG_CFG_FD		0x00002000
#घोषणा ANEG_CFG_INVAL		0x00001f06

पूर्ण;
#घोषणा ANEG_OK		0
#घोषणा ANEG_DONE	1
#घोषणा ANEG_TIMER_ENAB	2
#घोषणा ANEG_FAILED	-1

#घोषणा ANEG_STATE_SETTLE_TIME	10000

अटल पूर्णांक tg3_fiber_aneg_smachine(काष्ठा tg3 *tp,
				   काष्ठा tg3_fiber_aneginfo *ap)
अणु
	u16 flowctrl;
	अचिन्हित दीर्घ delta;
	u32 rx_cfg_reg;
	पूर्णांक ret;

	अगर (ap->state == ANEG_STATE_UNKNOWN) अणु
		ap->rxconfig = 0;
		ap->link_समय = 0;
		ap->cur_समय = 0;
		ap->ability_match_cfg = 0;
		ap->ability_match_count = 0;
		ap->ability_match = 0;
		ap->idle_match = 0;
		ap->ack_match = 0;
	पूर्ण
	ap->cur_समय++;

	अगर (tr32(MAC_STATUS) & MAC_STATUS_RCVD_CFG) अणु
		rx_cfg_reg = tr32(MAC_RX_AUTO_NEG);

		अगर (rx_cfg_reg != ap->ability_match_cfg) अणु
			ap->ability_match_cfg = rx_cfg_reg;
			ap->ability_match = 0;
			ap->ability_match_count = 0;
		पूर्ण अन्यथा अणु
			अगर (++ap->ability_match_count > 1) अणु
				ap->ability_match = 1;
				ap->ability_match_cfg = rx_cfg_reg;
			पूर्ण
		पूर्ण
		अगर (rx_cfg_reg & ANEG_CFG_ACK)
			ap->ack_match = 1;
		अन्यथा
			ap->ack_match = 0;

		ap->idle_match = 0;
	पूर्ण अन्यथा अणु
		ap->idle_match = 1;
		ap->ability_match_cfg = 0;
		ap->ability_match_count = 0;
		ap->ability_match = 0;
		ap->ack_match = 0;

		rx_cfg_reg = 0;
	पूर्ण

	ap->rxconfig = rx_cfg_reg;
	ret = ANEG_OK;

	चयन (ap->state) अणु
	हाल ANEG_STATE_UNKNOWN:
		अगर (ap->flags & (MR_AN_ENABLE | MR_RESTART_AN))
			ap->state = ANEG_STATE_AN_ENABLE;

		fallthrough;
	हाल ANEG_STATE_AN_ENABLE:
		ap->flags &= ~(MR_AN_COMPLETE | MR_PAGE_RX);
		अगर (ap->flags & MR_AN_ENABLE) अणु
			ap->link_समय = 0;
			ap->cur_समय = 0;
			ap->ability_match_cfg = 0;
			ap->ability_match_count = 0;
			ap->ability_match = 0;
			ap->idle_match = 0;
			ap->ack_match = 0;

			ap->state = ANEG_STATE_RESTART_INIT;
		पूर्ण अन्यथा अणु
			ap->state = ANEG_STATE_DISABLE_LINK_OK;
		पूर्ण
		अवरोध;

	हाल ANEG_STATE_RESTART_INIT:
		ap->link_समय = ap->cur_समय;
		ap->flags &= ~(MR_NP_LOADED);
		ap->txconfig = 0;
		tw32(MAC_TX_AUTO_NEG, 0);
		tp->mac_mode |= MAC_MODE_SEND_CONFIGS;
		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);

		ret = ANEG_TIMER_ENAB;
		ap->state = ANEG_STATE_RESTART;

		fallthrough;
	हाल ANEG_STATE_RESTART:
		delta = ap->cur_समय - ap->link_समय;
		अगर (delta > ANEG_STATE_SETTLE_TIME)
			ap->state = ANEG_STATE_ABILITY_DETECT_INIT;
		अन्यथा
			ret = ANEG_TIMER_ENAB;
		अवरोध;

	हाल ANEG_STATE_DISABLE_LINK_OK:
		ret = ANEG_DONE;
		अवरोध;

	हाल ANEG_STATE_ABILITY_DETECT_INIT:
		ap->flags &= ~(MR_TOGGLE_TX);
		ap->txconfig = ANEG_CFG_FD;
		flowctrl = tg3_advert_flowctrl_1000X(tp->link_config.flowctrl);
		अगर (flowctrl & ADVERTISE_1000XPAUSE)
			ap->txconfig |= ANEG_CFG_PS1;
		अगर (flowctrl & ADVERTISE_1000XPSE_ASYM)
			ap->txconfig |= ANEG_CFG_PS2;
		tw32(MAC_TX_AUTO_NEG, ap->txconfig);
		tp->mac_mode |= MAC_MODE_SEND_CONFIGS;
		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);

		ap->state = ANEG_STATE_ABILITY_DETECT;
		अवरोध;

	हाल ANEG_STATE_ABILITY_DETECT:
		अगर (ap->ability_match != 0 && ap->rxconfig != 0)
			ap->state = ANEG_STATE_ACK_DETECT_INIT;
		अवरोध;

	हाल ANEG_STATE_ACK_DETECT_INIT:
		ap->txconfig |= ANEG_CFG_ACK;
		tw32(MAC_TX_AUTO_NEG, ap->txconfig);
		tp->mac_mode |= MAC_MODE_SEND_CONFIGS;
		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);

		ap->state = ANEG_STATE_ACK_DETECT;

		fallthrough;
	हाल ANEG_STATE_ACK_DETECT:
		अगर (ap->ack_match != 0) अणु
			अगर ((ap->rxconfig & ~ANEG_CFG_ACK) ==
			    (ap->ability_match_cfg & ~ANEG_CFG_ACK)) अणु
				ap->state = ANEG_STATE_COMPLETE_ACK_INIT;
			पूर्ण अन्यथा अणु
				ap->state = ANEG_STATE_AN_ENABLE;
			पूर्ण
		पूर्ण अन्यथा अगर (ap->ability_match != 0 &&
			   ap->rxconfig == 0) अणु
			ap->state = ANEG_STATE_AN_ENABLE;
		पूर्ण
		अवरोध;

	हाल ANEG_STATE_COMPLETE_ACK_INIT:
		अगर (ap->rxconfig & ANEG_CFG_INVAL) अणु
			ret = ANEG_FAILED;
			अवरोध;
		पूर्ण
		ap->flags &= ~(MR_LP_ADV_FULL_DUPLEX |
			       MR_LP_ADV_HALF_DUPLEX |
			       MR_LP_ADV_SYM_PAUSE |
			       MR_LP_ADV_ASYM_PAUSE |
			       MR_LP_ADV_REMOTE_FAULT1 |
			       MR_LP_ADV_REMOTE_FAULT2 |
			       MR_LP_ADV_NEXT_PAGE |
			       MR_TOGGLE_RX |
			       MR_NP_RX);
		अगर (ap->rxconfig & ANEG_CFG_FD)
			ap->flags |= MR_LP_ADV_FULL_DUPLEX;
		अगर (ap->rxconfig & ANEG_CFG_HD)
			ap->flags |= MR_LP_ADV_HALF_DUPLEX;
		अगर (ap->rxconfig & ANEG_CFG_PS1)
			ap->flags |= MR_LP_ADV_SYM_PAUSE;
		अगर (ap->rxconfig & ANEG_CFG_PS2)
			ap->flags |= MR_LP_ADV_ASYM_PAUSE;
		अगर (ap->rxconfig & ANEG_CFG_RF1)
			ap->flags |= MR_LP_ADV_REMOTE_FAULT1;
		अगर (ap->rxconfig & ANEG_CFG_RF2)
			ap->flags |= MR_LP_ADV_REMOTE_FAULT2;
		अगर (ap->rxconfig & ANEG_CFG_NP)
			ap->flags |= MR_LP_ADV_NEXT_PAGE;

		ap->link_समय = ap->cur_समय;

		ap->flags ^= (MR_TOGGLE_TX);
		अगर (ap->rxconfig & 0x0008)
			ap->flags |= MR_TOGGLE_RX;
		अगर (ap->rxconfig & ANEG_CFG_NP)
			ap->flags |= MR_NP_RX;
		ap->flags |= MR_PAGE_RX;

		ap->state = ANEG_STATE_COMPLETE_ACK;
		ret = ANEG_TIMER_ENAB;
		अवरोध;

	हाल ANEG_STATE_COMPLETE_ACK:
		अगर (ap->ability_match != 0 &&
		    ap->rxconfig == 0) अणु
			ap->state = ANEG_STATE_AN_ENABLE;
			अवरोध;
		पूर्ण
		delta = ap->cur_समय - ap->link_समय;
		अगर (delta > ANEG_STATE_SETTLE_TIME) अणु
			अगर (!(ap->flags & (MR_LP_ADV_NEXT_PAGE))) अणु
				ap->state = ANEG_STATE_IDLE_DETECT_INIT;
			पूर्ण अन्यथा अणु
				अगर ((ap->txconfig & ANEG_CFG_NP) == 0 &&
				    !(ap->flags & MR_NP_RX)) अणु
					ap->state = ANEG_STATE_IDLE_DETECT_INIT;
				पूर्ण अन्यथा अणु
					ret = ANEG_FAILED;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ANEG_STATE_IDLE_DETECT_INIT:
		ap->link_समय = ap->cur_समय;
		tp->mac_mode &= ~MAC_MODE_SEND_CONFIGS;
		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);

		ap->state = ANEG_STATE_IDLE_DETECT;
		ret = ANEG_TIMER_ENAB;
		अवरोध;

	हाल ANEG_STATE_IDLE_DETECT:
		अगर (ap->ability_match != 0 &&
		    ap->rxconfig == 0) अणु
			ap->state = ANEG_STATE_AN_ENABLE;
			अवरोध;
		पूर्ण
		delta = ap->cur_समय - ap->link_समय;
		अगर (delta > ANEG_STATE_SETTLE_TIME) अणु
			/* XXX another gem from the Broadcom driver :( */
			ap->state = ANEG_STATE_LINK_OK;
		पूर्ण
		अवरोध;

	हाल ANEG_STATE_LINK_OK:
		ap->flags |= (MR_AN_COMPLETE | MR_LINK_OK);
		ret = ANEG_DONE;
		अवरोध;

	हाल ANEG_STATE_NEXT_PAGE_WAIT_INIT:
		/* ??? unimplemented */
		अवरोध;

	हाल ANEG_STATE_NEXT_PAGE_WAIT:
		/* ??? unimplemented */
		अवरोध;

	शेष:
		ret = ANEG_FAILED;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fiber_स्वतःneg(काष्ठा tg3 *tp, u32 *txflags, u32 *rxflags)
अणु
	पूर्णांक res = 0;
	काष्ठा tg3_fiber_aneginfo aninfo;
	पूर्णांक status = ANEG_FAILED;
	अचिन्हित पूर्णांक tick;
	u32 पंचांगp;

	tw32_f(MAC_TX_AUTO_NEG, 0);

	पंचांगp = tp->mac_mode & ~MAC_MODE_PORT_MODE_MASK;
	tw32_f(MAC_MODE, पंचांगp | MAC_MODE_PORT_MODE_GMII);
	udelay(40);

	tw32_f(MAC_MODE, tp->mac_mode | MAC_MODE_SEND_CONFIGS);
	udelay(40);

	स_रखो(&aninfo, 0, माप(aninfo));
	aninfo.flags |= MR_AN_ENABLE;
	aninfo.state = ANEG_STATE_UNKNOWN;
	aninfo.cur_समय = 0;
	tick = 0;
	जबतक (++tick < 195000) अणु
		status = tg3_fiber_aneg_smachine(tp, &aninfo);
		अगर (status == ANEG_DONE || status == ANEG_FAILED)
			अवरोध;

		udelay(1);
	पूर्ण

	tp->mac_mode &= ~MAC_MODE_SEND_CONFIGS;
	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	*txflags = aninfo.txconfig;
	*rxflags = aninfo.flags;

	अगर (status == ANEG_DONE &&
	    (aninfo.flags & (MR_AN_COMPLETE | MR_LINK_OK |
			     MR_LP_ADV_FULL_DUPLEX)))
		res = 1;

	वापस res;
पूर्ण

अटल व्योम tg3_init_bcm8002(काष्ठा tg3 *tp)
अणु
	u32 mac_status = tr32(MAC_STATUS);
	पूर्णांक i;

	/* Reset when initting first समय or we have a link. */
	अगर (tg3_flag(tp, INIT_COMPLETE) &&
	    !(mac_status & MAC_STATUS_PCS_SYNCED))
		वापस;

	/* Set PLL lock range. */
	tg3_ग_लिखोphy(tp, 0x16, 0x8007);

	/* SW reset */
	tg3_ग_लिखोphy(tp, MII_BMCR, BMCR_RESET);

	/* Wait क्रम reset to complete. */
	/* XXX schedule_समयout() ... */
	क्रम (i = 0; i < 500; i++)
		udelay(10);

	/* Config mode; select PMA/Ch 1 regs. */
	tg3_ग_लिखोphy(tp, 0x10, 0x8411);

	/* Enable स्वतः-lock and comdet, select txclk क्रम tx. */
	tg3_ग_लिखोphy(tp, 0x11, 0x0a10);

	tg3_ग_लिखोphy(tp, 0x18, 0x00a0);
	tg3_ग_लिखोphy(tp, 0x16, 0x41ff);

	/* Assert and deनिश्चित POR. */
	tg3_ग_लिखोphy(tp, 0x13, 0x0400);
	udelay(40);
	tg3_ग_लिखोphy(tp, 0x13, 0x0000);

	tg3_ग_लिखोphy(tp, 0x11, 0x0a50);
	udelay(40);
	tg3_ग_लिखोphy(tp, 0x11, 0x0a10);

	/* Wait क्रम संकेत to stabilize */
	/* XXX schedule_समयout() ... */
	क्रम (i = 0; i < 15000; i++)
		udelay(10);

	/* Deselect the channel रेजिस्टर so we can पढ़ो the PHYID
	 * later.
	 */
	tg3_ग_लिखोphy(tp, 0x10, 0x8011);
पूर्ण

अटल bool tg3_setup_fiber_hw_स्वतःneg(काष्ठा tg3 *tp, u32 mac_status)
अणु
	u16 flowctrl;
	bool current_link_up;
	u32 sg_dig_ctrl, sg_dig_status;
	u32 serdes_cfg, expected_sg_dig_ctrl;
	पूर्णांक workaround, port_a;

	serdes_cfg = 0;
	expected_sg_dig_ctrl = 0;
	workaround = 0;
	port_a = 1;
	current_link_up = false;

	अगर (tg3_chip_rev_id(tp) != CHIPREV_ID_5704_A0 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5704_A1) अणु
		workaround = 1;
		अगर (tr32(TG3PCI_DUAL_MAC_CTRL) & DUAL_MAC_CTRL_ID)
			port_a = 0;

		/* preserve bits 0-11,13,14 क्रम संकेत pre-emphasis */
		/* preserve bits 20-23 क्रम voltage regulator */
		serdes_cfg = tr32(MAC_SERDES_CFG) & 0x00f06fff;
	पूर्ण

	sg_dig_ctrl = tr32(SG_DIG_CTRL);

	अगर (tp->link_config.स्वतःneg != AUTONEG_ENABLE) अणु
		अगर (sg_dig_ctrl & SG_DIG_USING_HW_AUTONEG) अणु
			अगर (workaround) अणु
				u32 val = serdes_cfg;

				अगर (port_a)
					val |= 0xc010000;
				अन्यथा
					val |= 0x4010000;
				tw32_f(MAC_SERDES_CFG, val);
			पूर्ण

			tw32_f(SG_DIG_CTRL, SG_DIG_COMMON_SETUP);
		पूर्ण
		अगर (mac_status & MAC_STATUS_PCS_SYNCED) अणु
			tg3_setup_flow_control(tp, 0, 0);
			current_link_up = true;
		पूर्ण
		जाओ out;
	पूर्ण

	/* Want स्वतः-negotiation.  */
	expected_sg_dig_ctrl = SG_DIG_USING_HW_AUTONEG | SG_DIG_COMMON_SETUP;

	flowctrl = tg3_advert_flowctrl_1000X(tp->link_config.flowctrl);
	अगर (flowctrl & ADVERTISE_1000XPAUSE)
		expected_sg_dig_ctrl |= SG_DIG_PAUSE_CAP;
	अगर (flowctrl & ADVERTISE_1000XPSE_ASYM)
		expected_sg_dig_ctrl |= SG_DIG_ASYM_PAUSE;

	अगर (sg_dig_ctrl != expected_sg_dig_ctrl) अणु
		अगर ((tp->phy_flags & TG3_PHYFLG_PARALLEL_DETECT) &&
		    tp->serdes_counter &&
		    ((mac_status & (MAC_STATUS_PCS_SYNCED |
				    MAC_STATUS_RCVD_CFG)) ==
		     MAC_STATUS_PCS_SYNCED)) अणु
			tp->serdes_counter--;
			current_link_up = true;
			जाओ out;
		पूर्ण
restart_स्वतःneg:
		अगर (workaround)
			tw32_f(MAC_SERDES_CFG, serdes_cfg | 0xc011000);
		tw32_f(SG_DIG_CTRL, expected_sg_dig_ctrl | SG_DIG_SOFT_RESET);
		udelay(5);
		tw32_f(SG_DIG_CTRL, expected_sg_dig_ctrl);

		tp->serdes_counter = SERDES_AN_TIMEOUT_5704S;
		tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
	पूर्ण अन्यथा अगर (mac_status & (MAC_STATUS_PCS_SYNCED |
				 MAC_STATUS_SIGNAL_DET)) अणु
		sg_dig_status = tr32(SG_DIG_STATUS);
		mac_status = tr32(MAC_STATUS);

		अगर ((sg_dig_status & SG_DIG_AUTONEG_COMPLETE) &&
		    (mac_status & MAC_STATUS_PCS_SYNCED)) अणु
			u32 local_adv = 0, remote_adv = 0;

			अगर (sg_dig_ctrl & SG_DIG_PAUSE_CAP)
				local_adv |= ADVERTISE_1000XPAUSE;
			अगर (sg_dig_ctrl & SG_DIG_ASYM_PAUSE)
				local_adv |= ADVERTISE_1000XPSE_ASYM;

			अगर (sg_dig_status & SG_DIG_PARTNER_PAUSE_CAPABLE)
				remote_adv |= LPA_1000XPAUSE;
			अगर (sg_dig_status & SG_DIG_PARTNER_ASYM_PAUSE)
				remote_adv |= LPA_1000XPAUSE_ASYM;

			tp->link_config.rmt_adv =
					   mii_adv_to_ethtool_adv_x(remote_adv);

			tg3_setup_flow_control(tp, local_adv, remote_adv);
			current_link_up = true;
			tp->serdes_counter = 0;
			tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
		पूर्ण अन्यथा अगर (!(sg_dig_status & SG_DIG_AUTONEG_COMPLETE)) अणु
			अगर (tp->serdes_counter)
				tp->serdes_counter--;
			अन्यथा अणु
				अगर (workaround) अणु
					u32 val = serdes_cfg;

					अगर (port_a)
						val |= 0xc010000;
					अन्यथा
						val |= 0x4010000;

					tw32_f(MAC_SERDES_CFG, val);
				पूर्ण

				tw32_f(SG_DIG_CTRL, SG_DIG_COMMON_SETUP);
				udelay(40);

				/* Link parallel detection - link is up */
				/* only अगर we have PCS_SYNC and not */
				/* receiving config code words */
				mac_status = tr32(MAC_STATUS);
				अगर ((mac_status & MAC_STATUS_PCS_SYNCED) &&
				    !(mac_status & MAC_STATUS_RCVD_CFG)) अणु
					tg3_setup_flow_control(tp, 0, 0);
					current_link_up = true;
					tp->phy_flags |=
						TG3_PHYFLG_PARALLEL_DETECT;
					tp->serdes_counter =
						SERDES_PARALLEL_DET_TIMEOUT;
				पूर्ण अन्यथा
					जाओ restart_स्वतःneg;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		tp->serdes_counter = SERDES_AN_TIMEOUT_5704S;
		tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
	पूर्ण

out:
	वापस current_link_up;
पूर्ण

अटल bool tg3_setup_fiber_by_hand(काष्ठा tg3 *tp, u32 mac_status)
अणु
	bool current_link_up = false;

	अगर (!(mac_status & MAC_STATUS_PCS_SYNCED))
		जाओ out;

	अगर (tp->link_config.स्वतःneg == AUTONEG_ENABLE) अणु
		u32 txflags, rxflags;
		पूर्णांक i;

		अगर (fiber_स्वतःneg(tp, &txflags, &rxflags)) अणु
			u32 local_adv = 0, remote_adv = 0;

			अगर (txflags & ANEG_CFG_PS1)
				local_adv |= ADVERTISE_1000XPAUSE;
			अगर (txflags & ANEG_CFG_PS2)
				local_adv |= ADVERTISE_1000XPSE_ASYM;

			अगर (rxflags & MR_LP_ADV_SYM_PAUSE)
				remote_adv |= LPA_1000XPAUSE;
			अगर (rxflags & MR_LP_ADV_ASYM_PAUSE)
				remote_adv |= LPA_1000XPAUSE_ASYM;

			tp->link_config.rmt_adv =
					   mii_adv_to_ethtool_adv_x(remote_adv);

			tg3_setup_flow_control(tp, local_adv, remote_adv);

			current_link_up = true;
		पूर्ण
		क्रम (i = 0; i < 30; i++) अणु
			udelay(20);
			tw32_f(MAC_STATUS,
			       (MAC_STATUS_SYNC_CHANGED |
				MAC_STATUS_CFG_CHANGED));
			udelay(40);
			अगर ((tr32(MAC_STATUS) &
			     (MAC_STATUS_SYNC_CHANGED |
			      MAC_STATUS_CFG_CHANGED)) == 0)
				अवरोध;
		पूर्ण

		mac_status = tr32(MAC_STATUS);
		अगर (!current_link_up &&
		    (mac_status & MAC_STATUS_PCS_SYNCED) &&
		    !(mac_status & MAC_STATUS_RCVD_CFG))
			current_link_up = true;
	पूर्ण अन्यथा अणु
		tg3_setup_flow_control(tp, 0, 0);

		/* Forcing 1000FD link up. */
		current_link_up = true;

		tw32_f(MAC_MODE, (tp->mac_mode | MAC_MODE_SEND_CONFIGS));
		udelay(40);

		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);
	पूर्ण

out:
	वापस current_link_up;
पूर्ण

अटल पूर्णांक tg3_setup_fiber_phy(काष्ठा tg3 *tp, bool क्रमce_reset)
अणु
	u32 orig_छोड़ो_cfg;
	u32 orig_active_speed;
	u8 orig_active_duplex;
	u32 mac_status;
	bool current_link_up;
	पूर्णांक i;

	orig_छोड़ो_cfg = tp->link_config.active_flowctrl;
	orig_active_speed = tp->link_config.active_speed;
	orig_active_duplex = tp->link_config.active_duplex;

	अगर (!tg3_flag(tp, HW_AUTONEG) &&
	    tp->link_up &&
	    tg3_flag(tp, INIT_COMPLETE)) अणु
		mac_status = tr32(MAC_STATUS);
		mac_status &= (MAC_STATUS_PCS_SYNCED |
			       MAC_STATUS_SIGNAL_DET |
			       MAC_STATUS_CFG_CHANGED |
			       MAC_STATUS_RCVD_CFG);
		अगर (mac_status == (MAC_STATUS_PCS_SYNCED |
				   MAC_STATUS_SIGNAL_DET)) अणु
			tw32_f(MAC_STATUS, (MAC_STATUS_SYNC_CHANGED |
					    MAC_STATUS_CFG_CHANGED));
			वापस 0;
		पूर्ण
	पूर्ण

	tw32_f(MAC_TX_AUTO_NEG, 0);

	tp->mac_mode &= ~(MAC_MODE_PORT_MODE_MASK | MAC_MODE_HALF_DUPLEX);
	tp->mac_mode |= MAC_MODE_PORT_MODE_TBI;
	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	अगर (tp->phy_id == TG3_PHY_ID_BCM8002)
		tg3_init_bcm8002(tp);

	/* Enable link change event even when serdes polling.  */
	tw32_f(MAC_EVENT, MAC_EVENT_LNKSTATE_CHANGED);
	udelay(40);

	current_link_up = false;
	tp->link_config.rmt_adv = 0;
	mac_status = tr32(MAC_STATUS);

	अगर (tg3_flag(tp, HW_AUTONEG))
		current_link_up = tg3_setup_fiber_hw_स्वतःneg(tp, mac_status);
	अन्यथा
		current_link_up = tg3_setup_fiber_by_hand(tp, mac_status);

	tp->napi[0].hw_status->status =
		(SD_STATUS_UPDATED |
		 (tp->napi[0].hw_status->status & ~SD_STATUS_LINK_CHG));

	क्रम (i = 0; i < 100; i++) अणु
		tw32_f(MAC_STATUS, (MAC_STATUS_SYNC_CHANGED |
				    MAC_STATUS_CFG_CHANGED));
		udelay(5);
		अगर ((tr32(MAC_STATUS) & (MAC_STATUS_SYNC_CHANGED |
					 MAC_STATUS_CFG_CHANGED |
					 MAC_STATUS_LNKSTATE_CHANGED)) == 0)
			अवरोध;
	पूर्ण

	mac_status = tr32(MAC_STATUS);
	अगर ((mac_status & MAC_STATUS_PCS_SYNCED) == 0) अणु
		current_link_up = false;
		अगर (tp->link_config.स्वतःneg == AUTONEG_ENABLE &&
		    tp->serdes_counter == 0) अणु
			tw32_f(MAC_MODE, (tp->mac_mode |
					  MAC_MODE_SEND_CONFIGS));
			udelay(1);
			tw32_f(MAC_MODE, tp->mac_mode);
		पूर्ण
	पूर्ण

	अगर (current_link_up) अणु
		tp->link_config.active_speed = SPEED_1000;
		tp->link_config.active_duplex = DUPLEX_FULL;
		tw32(MAC_LED_CTRL, (tp->led_ctrl |
				    LED_CTRL_LNKLED_OVERRIDE |
				    LED_CTRL_1000MBPS_ON));
	पूर्ण अन्यथा अणु
		tp->link_config.active_speed = SPEED_UNKNOWN;
		tp->link_config.active_duplex = DUPLEX_UNKNOWN;
		tw32(MAC_LED_CTRL, (tp->led_ctrl |
				    LED_CTRL_LNKLED_OVERRIDE |
				    LED_CTRL_TRAFFIC_OVERRIDE));
	पूर्ण

	अगर (!tg3_test_and_report_link_chg(tp, current_link_up)) अणु
		u32 now_छोड़ो_cfg = tp->link_config.active_flowctrl;
		अगर (orig_छोड़ो_cfg != now_छोड़ो_cfg ||
		    orig_active_speed != tp->link_config.active_speed ||
		    orig_active_duplex != tp->link_config.active_duplex)
			tg3_link_report(tp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_setup_fiber_mii_phy(काष्ठा tg3 *tp, bool क्रमce_reset)
अणु
	पूर्णांक err = 0;
	u32 bmsr, bmcr;
	u32 current_speed = SPEED_UNKNOWN;
	u8 current_duplex = DUPLEX_UNKNOWN;
	bool current_link_up = false;
	u32 local_adv, remote_adv, sgsr;

	अगर ((tg3_asic_rev(tp) == ASIC_REV_5719 ||
	     tg3_asic_rev(tp) == ASIC_REV_5720) &&
	     !tg3_पढ़ोphy(tp, SERDES_TG3_1000X_STATUS, &sgsr) &&
	     (sgsr & SERDES_TG3_SGMII_MODE)) अणु

		अगर (क्रमce_reset)
			tg3_phy_reset(tp);

		tp->mac_mode &= ~MAC_MODE_PORT_MODE_MASK;

		अगर (!(sgsr & SERDES_TG3_LINK_UP)) अणु
			tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;
		पूर्ण अन्यथा अणु
			current_link_up = true;
			अगर (sgsr & SERDES_TG3_SPEED_1000) अणु
				current_speed = SPEED_1000;
				tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;
			पूर्ण अन्यथा अगर (sgsr & SERDES_TG3_SPEED_100) अणु
				current_speed = SPEED_100;
				tp->mac_mode |= MAC_MODE_PORT_MODE_MII;
			पूर्ण अन्यथा अणु
				current_speed = SPEED_10;
				tp->mac_mode |= MAC_MODE_PORT_MODE_MII;
			पूर्ण

			अगर (sgsr & SERDES_TG3_FULL_DUPLEX)
				current_duplex = DUPLEX_FULL;
			अन्यथा
				current_duplex = DUPLEX_HALF;
		पूर्ण

		tw32_f(MAC_MODE, tp->mac_mode);
		udelay(40);

		tg3_clear_mac_status(tp);

		जाओ fiber_setup_करोne;
	पूर्ण

	tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;
	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	tg3_clear_mac_status(tp);

	अगर (क्रमce_reset)
		tg3_phy_reset(tp);

	tp->link_config.rmt_adv = 0;

	err |= tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
	err |= tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
	अगर (tg3_asic_rev(tp) == ASIC_REV_5714) अणु
		अगर (tr32(MAC_TX_STATUS) & TX_STATUS_LINK_UP)
			bmsr |= BMSR_LSTATUS;
		अन्यथा
			bmsr &= ~BMSR_LSTATUS;
	पूर्ण

	err |= tg3_पढ़ोphy(tp, MII_BMCR, &bmcr);

	अगर ((tp->link_config.स्वतःneg == AUTONEG_ENABLE) && !क्रमce_reset &&
	    (tp->phy_flags & TG3_PHYFLG_PARALLEL_DETECT)) अणु
		/* करो nothing, just check क्रम link up at the end */
	पूर्ण अन्यथा अगर (tp->link_config.स्वतःneg == AUTONEG_ENABLE) अणु
		u32 adv, newadv;

		err |= tg3_पढ़ोphy(tp, MII_ADVERTISE, &adv);
		newadv = adv & ~(ADVERTISE_1000XFULL | ADVERTISE_1000XHALF |
				 ADVERTISE_1000XPAUSE |
				 ADVERTISE_1000XPSE_ASYM |
				 ADVERTISE_SLCT);

		newadv |= tg3_advert_flowctrl_1000X(tp->link_config.flowctrl);
		newadv |= ethtool_adv_to_mii_adv_x(tp->link_config.advertising);

		अगर ((newadv != adv) || !(bmcr & BMCR_ANENABLE)) अणु
			tg3_ग_लिखोphy(tp, MII_ADVERTISE, newadv);
			bmcr |= BMCR_ANENABLE | BMCR_ANRESTART;
			tg3_ग_लिखोphy(tp, MII_BMCR, bmcr);

			tw32_f(MAC_EVENT, MAC_EVENT_LNKSTATE_CHANGED);
			tp->serdes_counter = SERDES_AN_TIMEOUT_5714S;
			tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;

			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 new_bmcr;

		bmcr &= ~BMCR_SPEED1000;
		new_bmcr = bmcr & ~(BMCR_ANENABLE | BMCR_FULLDPLX);

		अगर (tp->link_config.duplex == DUPLEX_FULL)
			new_bmcr |= BMCR_FULLDPLX;

		अगर (new_bmcr != bmcr) अणु
			/* BMCR_SPEED1000 is a reserved bit that needs
			 * to be set on ग_लिखो.
			 */
			new_bmcr |= BMCR_SPEED1000;

			/* Force a linkकरोwn */
			अगर (tp->link_up) अणु
				u32 adv;

				err |= tg3_पढ़ोphy(tp, MII_ADVERTISE, &adv);
				adv &= ~(ADVERTISE_1000XFULL |
					 ADVERTISE_1000XHALF |
					 ADVERTISE_SLCT);
				tg3_ग_लिखोphy(tp, MII_ADVERTISE, adv);
				tg3_ग_लिखोphy(tp, MII_BMCR, bmcr |
							   BMCR_ANRESTART |
							   BMCR_ANENABLE);
				udelay(10);
				tg3_carrier_off(tp);
			पूर्ण
			tg3_ग_लिखोphy(tp, MII_BMCR, new_bmcr);
			bmcr = new_bmcr;
			err |= tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
			err |= tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
			अगर (tg3_asic_rev(tp) == ASIC_REV_5714) अणु
				अगर (tr32(MAC_TX_STATUS) & TX_STATUS_LINK_UP)
					bmsr |= BMSR_LSTATUS;
				अन्यथा
					bmsr &= ~BMSR_LSTATUS;
			पूर्ण
			tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
		पूर्ण
	पूर्ण

	अगर (bmsr & BMSR_LSTATUS) अणु
		current_speed = SPEED_1000;
		current_link_up = true;
		अगर (bmcr & BMCR_FULLDPLX)
			current_duplex = DUPLEX_FULL;
		अन्यथा
			current_duplex = DUPLEX_HALF;

		local_adv = 0;
		remote_adv = 0;

		अगर (bmcr & BMCR_ANENABLE) अणु
			u32 common;

			err |= tg3_पढ़ोphy(tp, MII_ADVERTISE, &local_adv);
			err |= tg3_पढ़ोphy(tp, MII_LPA, &remote_adv);
			common = local_adv & remote_adv;
			अगर (common & (ADVERTISE_1000XHALF |
				      ADVERTISE_1000XFULL)) अणु
				अगर (common & ADVERTISE_1000XFULL)
					current_duplex = DUPLEX_FULL;
				अन्यथा
					current_duplex = DUPLEX_HALF;

				tp->link_config.rmt_adv =
					   mii_adv_to_ethtool_adv_x(remote_adv);
			पूर्ण अन्यथा अगर (!tg3_flag(tp, 5780_CLASS)) अणु
				/* Link is up via parallel detect */
			पूर्ण अन्यथा अणु
				current_link_up = false;
			पूर्ण
		पूर्ण
	पूर्ण

fiber_setup_करोne:
	अगर (current_link_up && current_duplex == DUPLEX_FULL)
		tg3_setup_flow_control(tp, local_adv, remote_adv);

	tp->mac_mode &= ~MAC_MODE_HALF_DUPLEX;
	अगर (tp->link_config.active_duplex == DUPLEX_HALF)
		tp->mac_mode |= MAC_MODE_HALF_DUPLEX;

	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	tw32_f(MAC_EVENT, MAC_EVENT_LNKSTATE_CHANGED);

	tp->link_config.active_speed = current_speed;
	tp->link_config.active_duplex = current_duplex;

	tg3_test_and_report_link_chg(tp, current_link_up);
	वापस err;
पूर्ण

अटल व्योम tg3_serdes_parallel_detect(काष्ठा tg3 *tp)
अणु
	अगर (tp->serdes_counter) अणु
		/* Give स्वतःneg समय to complete. */
		tp->serdes_counter--;
		वापस;
	पूर्ण

	अगर (!tp->link_up &&
	    (tp->link_config.स्वतःneg == AUTONEG_ENABLE)) अणु
		u32 bmcr;

		tg3_पढ़ोphy(tp, MII_BMCR, &bmcr);
		अगर (bmcr & BMCR_ANENABLE) अणु
			u32 phy1, phy2;

			/* Select shaकरोw रेजिस्टर 0x1f */
			tg3_ग_लिखोphy(tp, MII_TG3_MISC_SHDW, 0x7c00);
			tg3_पढ़ोphy(tp, MII_TG3_MISC_SHDW, &phy1);

			/* Select expansion पूर्णांकerrupt status रेजिस्टर */
			tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS,
					 MII_TG3_DSP_EXP1_INT_STAT);
			tg3_पढ़ोphy(tp, MII_TG3_DSP_RW_PORT, &phy2);
			tg3_पढ़ोphy(tp, MII_TG3_DSP_RW_PORT, &phy2);

			अगर ((phy1 & 0x10) && !(phy2 & 0x20)) अणु
				/* We have संकेत detect and not receiving
				 * config code words, link is up by parallel
				 * detection.
				 */

				bmcr &= ~BMCR_ANENABLE;
				bmcr |= BMCR_SPEED1000 | BMCR_FULLDPLX;
				tg3_ग_लिखोphy(tp, MII_BMCR, bmcr);
				tp->phy_flags |= TG3_PHYFLG_PARALLEL_DETECT;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (tp->link_up &&
		   (tp->link_config.स्वतःneg == AUTONEG_ENABLE) &&
		   (tp->phy_flags & TG3_PHYFLG_PARALLEL_DETECT)) अणु
		u32 phy2;

		/* Select expansion पूर्णांकerrupt status रेजिस्टर */
		tg3_ग_लिखोphy(tp, MII_TG3_DSP_ADDRESS,
				 MII_TG3_DSP_EXP1_INT_STAT);
		tg3_पढ़ोphy(tp, MII_TG3_DSP_RW_PORT, &phy2);
		अगर (phy2 & 0x20) अणु
			u32 bmcr;

			/* Config code words received, turn on स्वतःneg. */
			tg3_पढ़ोphy(tp, MII_BMCR, &bmcr);
			tg3_ग_लिखोphy(tp, MII_BMCR, bmcr | BMCR_ANENABLE);

			tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;

		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_setup_phy(काष्ठा tg3 *tp, bool क्रमce_reset)
अणु
	u32 val;
	पूर्णांक err;

	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)
		err = tg3_setup_fiber_phy(tp, क्रमce_reset);
	अन्यथा अगर (tp->phy_flags & TG3_PHYFLG_MII_SERDES)
		err = tg3_setup_fiber_mii_phy(tp, क्रमce_reset);
	अन्यथा
		err = tg3_setup_copper_phy(tp, क्रमce_reset);

	अगर (tg3_chip_rev(tp) == CHIPREV_5784_AX) अणु
		u32 scale;

		val = tr32(TG3_CPMU_CLCK_STAT) & CPMU_CLCK_STAT_MAC_CLCK_MASK;
		अगर (val == CPMU_CLCK_STAT_MAC_CLCK_62_5)
			scale = 65;
		अन्यथा अगर (val == CPMU_CLCK_STAT_MAC_CLCK_6_25)
			scale = 6;
		अन्यथा
			scale = 12;

		val = tr32(GRC_MISC_CFG) & ~GRC_MISC_CFG_PRESCALAR_MASK;
		val |= (scale << GRC_MISC_CFG_PRESCALAR_SHIFT);
		tw32(GRC_MISC_CFG, val);
	पूर्ण

	val = (2 << TX_LENGTHS_IPG_CRS_SHIFT) |
	      (6 << TX_LENGTHS_IPG_SHIFT);
	अगर (tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762)
		val |= tr32(MAC_TX_LENGTHS) &
		       (TX_LENGTHS_JMB_FRM_LEN_MSK |
			TX_LENGTHS_CNT_DWN_VAL_MSK);

	अगर (tp->link_config.active_speed == SPEED_1000 &&
	    tp->link_config.active_duplex == DUPLEX_HALF)
		tw32(MAC_TX_LENGTHS, val |
		     (0xff << TX_LENGTHS_SLOT_TIME_SHIFT));
	अन्यथा
		tw32(MAC_TX_LENGTHS, val |
		     (32 << TX_LENGTHS_SLOT_TIME_SHIFT));

	अगर (!tg3_flag(tp, 5705_PLUS)) अणु
		अगर (tp->link_up) अणु
			tw32(HOSTCC_STAT_COAL_TICKS,
			     tp->coal.stats_block_coalesce_usecs);
		पूर्ण अन्यथा अणु
			tw32(HOSTCC_STAT_COAL_TICKS, 0);
		पूर्ण
	पूर्ण

	अगर (tg3_flag(tp, ASPM_WORKAROUND)) अणु
		val = tr32(PCIE_PWR_MGMT_THRESH);
		अगर (!tp->link_up)
			val = (val & ~PCIE_PWR_MGMT_L1_THRESH_MSK) |
			      tp->pwrmgmt_thresh;
		अन्यथा
			val |= PCIE_PWR_MGMT_L1_THRESH_MSK;
		tw32(PCIE_PWR_MGMT_THRESH, val);
	पूर्ण

	वापस err;
पूर्ण

/* tp->lock must be held */
अटल u64 tg3_refclk_पढ़ो(काष्ठा tg3 *tp, काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	u64 stamp;

	ptp_पढ़ो_प्रणाली_prets(sts);
	stamp = tr32(TG3_EAV_REF_CLCK_LSB);
	ptp_पढ़ो_प्रणाली_postts(sts);
	stamp |= (u64)tr32(TG3_EAV_REF_CLCK_MSB) << 32;

	वापस stamp;
पूर्ण

/* tp->lock must be held */
अटल व्योम tg3_refclk_ग_लिखो(काष्ठा tg3 *tp, u64 newval)
अणु
	u32 घड़ी_ctl = tr32(TG3_EAV_REF_CLCK_CTL);

	tw32(TG3_EAV_REF_CLCK_CTL, घड़ी_ctl | TG3_EAV_REF_CLCK_CTL_STOP);
	tw32(TG3_EAV_REF_CLCK_LSB, newval & 0xffffffff);
	tw32(TG3_EAV_REF_CLCK_MSB, newval >> 32);
	tw32_f(TG3_EAV_REF_CLCK_CTL, घड़ी_ctl | TG3_EAV_REF_CLCK_CTL_RESUME);
पूर्ण

अटल अंतरभूत व्योम tg3_full_lock(काष्ठा tg3 *tp, पूर्णांक irq_sync);
अटल अंतरभूत व्योम tg3_full_unlock(काष्ठा tg3 *tp);
अटल पूर्णांक tg3_get_ts_info(काष्ठा net_device *dev, काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE;

	अगर (tg3_flag(tp, PTP_CAPABLE)) अणु
		info->so_बारtamping |= SOF_TIMESTAMPING_TX_HARDWARE |
					SOF_TIMESTAMPING_RX_HARDWARE |
					SOF_TIMESTAMPING_RAW_HARDWARE;
	पूर्ण

	अगर (tp->ptp_घड़ी)
		info->phc_index = ptp_घड़ी_index(tp->ptp_घड़ी);
	अन्यथा
		info->phc_index = -1;

	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
			   (1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			   (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT);
	वापस 0;
पूर्ण

अटल पूर्णांक tg3_ptp_adjfreq(काष्ठा ptp_घड़ी_info *ptp, s32 ppb)
अणु
	काष्ठा tg3 *tp = container_of(ptp, काष्ठा tg3, ptp_info);
	bool neg_adj = false;
	u32 correction = 0;

	अगर (ppb < 0) अणु
		neg_adj = true;
		ppb = -ppb;
	पूर्ण

	/* Frequency adjusपंचांगent is perक्रमmed using hardware with a 24 bit
	 * accumulator and a programmable correction value. On each clk, the
	 * correction value माला_लो added to the accumulator and when it
	 * overflows, the समय counter is incremented/decremented.
	 *
	 * So conversion from ppb to correction value is
	 *		ppb * (1 << 24) / 1000000000
	 */
	correction = भाग_u64((u64)ppb * (1 << 24), 1000000000ULL) &
		     TG3_EAV_REF_CLK_CORRECT_MASK;

	tg3_full_lock(tp, 0);

	अगर (correction)
		tw32(TG3_EAV_REF_CLK_CORRECT_CTL,
		     TG3_EAV_REF_CLK_CORRECT_EN |
		     (neg_adj ? TG3_EAV_REF_CLK_CORRECT_NEG : 0) | correction);
	अन्यथा
		tw32(TG3_EAV_REF_CLK_CORRECT_CTL, 0);

	tg3_full_unlock(tp);

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा tg3 *tp = container_of(ptp, काष्ठा tg3, ptp_info);

	tg3_full_lock(tp, 0);
	tp->ptp_adjust += delta;
	tg3_full_unlock(tp);

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_ptp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts,
			    काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	u64 ns;
	काष्ठा tg3 *tp = container_of(ptp, काष्ठा tg3, ptp_info);

	tg3_full_lock(tp, 0);
	ns = tg3_refclk_पढ़ो(tp, sts);
	ns += tp->ptp_adjust;
	tg3_full_unlock(tp);

	*ts = ns_to_बारpec64(ns);

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			   स्थिर काष्ठा बारpec64 *ts)
अणु
	u64 ns;
	काष्ठा tg3 *tp = container_of(ptp, काष्ठा tg3, ptp_info);

	ns = बारpec64_to_ns(ts);

	tg3_full_lock(tp, 0);
	tg3_refclk_ग_लिखो(tp, ns);
	tp->ptp_adjust = 0;
	tg3_full_unlock(tp);

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			  काष्ठा ptp_घड़ी_request *rq, पूर्णांक on)
अणु
	काष्ठा tg3 *tp = container_of(ptp, काष्ठा tg3, ptp_info);
	u32 घड़ी_ctl;
	पूर्णांक rval = 0;

	चयन (rq->type) अणु
	हाल PTP_CLK_REQ_PEROUT:
		/* Reject requests with unsupported flags */
		अगर (rq->perout.flags)
			वापस -EOPNOTSUPP;

		अगर (rq->perout.index != 0)
			वापस -EINVAL;

		tg3_full_lock(tp, 0);
		घड़ी_ctl = tr32(TG3_EAV_REF_CLCK_CTL);
		घड़ी_ctl &= ~TG3_EAV_CTL_TSYNC_GPIO_MASK;

		अगर (on) अणु
			u64 nsec;

			nsec = rq->perout.start.sec * 1000000000ULL +
			       rq->perout.start.nsec;

			अगर (rq->perout.period.sec || rq->perout.period.nsec) अणु
				netdev_warn(tp->dev,
					    "Device supports only a one-shot timesync output, period must be 0\n");
				rval = -EINVAL;
				जाओ err_out;
			पूर्ण

			अगर (nsec & (1ULL << 63)) अणु
				netdev_warn(tp->dev,
					    "Start value (nsec) is over limit. Maximum size of start is only 63 bits\n");
				rval = -EINVAL;
				जाओ err_out;
			पूर्ण

			tw32(TG3_EAV_WATCHDOG0_LSB, (nsec & 0xffffffff));
			tw32(TG3_EAV_WATCHDOG0_MSB,
			     TG3_EAV_WATCHDOG0_EN |
			     ((nsec >> 32) & TG3_EAV_WATCHDOG_MSB_MASK));

			tw32(TG3_EAV_REF_CLCK_CTL,
			     घड़ी_ctl | TG3_EAV_CTL_TSYNC_WDOG0);
		पूर्ण अन्यथा अणु
			tw32(TG3_EAV_WATCHDOG0_MSB, 0);
			tw32(TG3_EAV_REF_CLCK_CTL, घड़ी_ctl);
		पूर्ण

err_out:
		tg3_full_unlock(tp);
		वापस rval;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ptp_घड़ी_info tg3_ptp_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "tg3 clock",
	.max_adj	= 250000000,
	.n_alarm	= 0,
	.n_ext_ts	= 0,
	.n_per_out	= 1,
	.n_pins		= 0,
	.pps		= 0,
	.adjfreq	= tg3_ptp_adjfreq,
	.adjसमय	= tg3_ptp_adjसमय,
	.समय_लोx64	= tg3_ptp_समय_लोx,
	.समय_रखो64	= tg3_ptp_समय_रखो,
	.enable		= tg3_ptp_enable,
पूर्ण;

अटल व्योम tg3_hwघड़ी_प्रकारo_बारtamp(काष्ठा tg3 *tp, u64 hwघड़ी,
				     काष्ठा skb_shared_hwtstamps *बारtamp)
अणु
	स_रखो(बारtamp, 0, माप(काष्ठा skb_shared_hwtstamps));
	बारtamp->hwtstamp  = ns_to_kसमय((hwघड़ी & TG3_TSTAMP_MASK) +
					   tp->ptp_adjust);
पूर्ण

/* tp->lock must be held */
अटल व्योम tg3_ptp_init(काष्ठा tg3 *tp)
अणु
	अगर (!tg3_flag(tp, PTP_CAPABLE))
		वापस;

	/* Initialize the hardware घड़ी to the प्रणाली समय. */
	tg3_refclk_ग_लिखो(tp, kसमय_प्रकारo_ns(kसमय_get_real()));
	tp->ptp_adjust = 0;
	tp->ptp_info = tg3_ptp_caps;
पूर्ण

/* tp->lock must be held */
अटल व्योम tg3_ptp_resume(काष्ठा tg3 *tp)
अणु
	अगर (!tg3_flag(tp, PTP_CAPABLE))
		वापस;

	tg3_refclk_ग_लिखो(tp, kसमय_प्रकारo_ns(kसमय_get_real()) + tp->ptp_adjust);
	tp->ptp_adjust = 0;
पूर्ण

अटल व्योम tg3_ptp_fini(काष्ठा tg3 *tp)
अणु
	अगर (!tg3_flag(tp, PTP_CAPABLE) || !tp->ptp_घड़ी)
		वापस;

	ptp_घड़ी_unरेजिस्टर(tp->ptp_घड़ी);
	tp->ptp_घड़ी = शून्य;
	tp->ptp_adjust = 0;
पूर्ण

अटल अंतरभूत पूर्णांक tg3_irq_sync(काष्ठा tg3 *tp)
अणु
	वापस tp->irq_sync;
पूर्ण

अटल अंतरभूत व्योम tg3_rd32_loop(काष्ठा tg3 *tp, u32 *dst, u32 off, u32 len)
अणु
	पूर्णांक i;

	dst = (u32 *)((u8 *)dst + off);
	क्रम (i = 0; i < len; i += माप(u32))
		*dst++ = tr32(off + i);
पूर्ण

अटल व्योम tg3_dump_legacy_regs(काष्ठा tg3 *tp, u32 *regs)
अणु
	tg3_rd32_loop(tp, regs, TG3PCI_VENDOR, 0xb0);
	tg3_rd32_loop(tp, regs, MAILBOX_INTERRUPT_0, 0x200);
	tg3_rd32_loop(tp, regs, MAC_MODE, 0x4f0);
	tg3_rd32_loop(tp, regs, SNDDATAI_MODE, 0xe0);
	tg3_rd32_loop(tp, regs, SNDDATAC_MODE, 0x04);
	tg3_rd32_loop(tp, regs, SNDBDS_MODE, 0x80);
	tg3_rd32_loop(tp, regs, SNDBDI_MODE, 0x48);
	tg3_rd32_loop(tp, regs, SNDBDC_MODE, 0x04);
	tg3_rd32_loop(tp, regs, RCVLPC_MODE, 0x20);
	tg3_rd32_loop(tp, regs, RCVLPC_SELLST_BASE, 0x15c);
	tg3_rd32_loop(tp, regs, RCVDBDI_MODE, 0x0c);
	tg3_rd32_loop(tp, regs, RCVDBDI_JUMBO_BD, 0x3c);
	tg3_rd32_loop(tp, regs, RCVDBDI_BD_PROD_IDX_0, 0x44);
	tg3_rd32_loop(tp, regs, RCVDCC_MODE, 0x04);
	tg3_rd32_loop(tp, regs, RCVBDI_MODE, 0x20);
	tg3_rd32_loop(tp, regs, RCVCC_MODE, 0x14);
	tg3_rd32_loop(tp, regs, RCVLSC_MODE, 0x08);
	tg3_rd32_loop(tp, regs, MBFREE_MODE, 0x08);
	tg3_rd32_loop(tp, regs, HOSTCC_MODE, 0x100);

	अगर (tg3_flag(tp, SUPPORT_MSIX))
		tg3_rd32_loop(tp, regs, HOSTCC_RXCOL_TICKS_VEC1, 0x180);

	tg3_rd32_loop(tp, regs, MEMARB_MODE, 0x10);
	tg3_rd32_loop(tp, regs, BUFMGR_MODE, 0x58);
	tg3_rd32_loop(tp, regs, RDMAC_MODE, 0x08);
	tg3_rd32_loop(tp, regs, WDMAC_MODE, 0x08);
	tg3_rd32_loop(tp, regs, RX_CPU_MODE, 0x04);
	tg3_rd32_loop(tp, regs, RX_CPU_STATE, 0x04);
	tg3_rd32_loop(tp, regs, RX_CPU_PGMCTR, 0x04);
	tg3_rd32_loop(tp, regs, RX_CPU_HWBKPT, 0x04);

	अगर (!tg3_flag(tp, 5705_PLUS)) अणु
		tg3_rd32_loop(tp, regs, TX_CPU_MODE, 0x04);
		tg3_rd32_loop(tp, regs, TX_CPU_STATE, 0x04);
		tg3_rd32_loop(tp, regs, TX_CPU_PGMCTR, 0x04);
	पूर्ण

	tg3_rd32_loop(tp, regs, GRCMBOX_INTERRUPT_0, 0x110);
	tg3_rd32_loop(tp, regs, FTQ_RESET, 0x120);
	tg3_rd32_loop(tp, regs, MSGINT_MODE, 0x0c);
	tg3_rd32_loop(tp, regs, DMAC_MODE, 0x04);
	tg3_rd32_loop(tp, regs, GRC_MODE, 0x4c);

	अगर (tg3_flag(tp, NVRAM))
		tg3_rd32_loop(tp, regs, NVRAM_CMD, 0x24);
पूर्ण

अटल व्योम tg3_dump_state(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	u32 *regs;

	regs = kzalloc(TG3_REG_BLK_SIZE, GFP_ATOMIC);
	अगर (!regs)
		वापस;

	अगर (tg3_flag(tp, PCI_EXPRESS)) अणु
		/* Read up to but not including निजी PCI रेजिस्टरs */
		क्रम (i = 0; i < TG3_PCIE_TLDLPL_PORT; i += माप(u32))
			regs[i / माप(u32)] = tr32(i);
	पूर्ण अन्यथा
		tg3_dump_legacy_regs(tp, regs);

	क्रम (i = 0; i < TG3_REG_BLK_SIZE / माप(u32); i += 4) अणु
		अगर (!regs[i + 0] && !regs[i + 1] &&
		    !regs[i + 2] && !regs[i + 3])
			जारी;

		netdev_err(tp->dev, "0x%08x: 0x%08x, 0x%08x, 0x%08x, 0x%08x\n",
			   i * 4,
			   regs[i + 0], regs[i + 1], regs[i + 2], regs[i + 3]);
	पूर्ण

	kमुक्त(regs);

	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		/* SW status block */
		netdev_err(tp->dev,
			 "%d: Host status block [%08x:%08x:(%04x:%04x:%04x):(%04x:%04x)]\n",
			   i,
			   tnapi->hw_status->status,
			   tnapi->hw_status->status_tag,
			   tnapi->hw_status->rx_jumbo_consumer,
			   tnapi->hw_status->rx_consumer,
			   tnapi->hw_status->rx_mini_consumer,
			   tnapi->hw_status->idx[0].rx_producer,
			   tnapi->hw_status->idx[0].tx_consumer);

		netdev_err(tp->dev,
		"%d: NAPI info [%08x:%08x:(%04x:%04x:%04x):%04x:(%04x:%04x:%04x:%04x)]\n",
			   i,
			   tnapi->last_tag, tnapi->last_irq_tag,
			   tnapi->tx_prod, tnapi->tx_cons, tnapi->tx_pending,
			   tnapi->rx_rcb_ptr,
			   tnapi->prodring.rx_std_prod_idx,
			   tnapi->prodring.rx_std_cons_idx,
			   tnapi->prodring.rx_jmb_prod_idx,
			   tnapi->prodring.rx_jmb_cons_idx);
	पूर्ण
पूर्ण

/* This is called whenever we suspect that the प्रणाली chipset is re-
 * ordering the sequence of MMIO to the tx send mailbox. The symptom
 * is bogus tx completions. We try to recover by setting the
 * TG3_FLAG_MBOX_WRITE_REORDER flag and resetting the chip later
 * in the workqueue.
 */
अटल व्योम tg3_tx_recover(काष्ठा tg3 *tp)
अणु
	BUG_ON(tg3_flag(tp, MBOX_WRITE_REORDER) ||
	       tp->ग_लिखो32_tx_mbox == tg3_ग_लिखो_indirect_mbox);

	netdev_warn(tp->dev,
		    "The system may be re-ordering memory-mapped I/O "
		    "cycles to the network device, attempting to recover. "
		    "Please report the problem to the driver maintainer "
		    "and include system chipset information.\n");

	tg3_flag_set(tp, TX_RECOVERY_PENDING);
पूर्ण

अटल अंतरभूत u32 tg3_tx_avail(काष्ठा tg3_napi *tnapi)
अणु
	/* Tell compiler to fetch tx indices from memory. */
	barrier();
	वापस tnapi->tx_pending -
	       ((tnapi->tx_prod - tnapi->tx_cons) & (TG3_TX_RING_SIZE - 1));
पूर्ण

/* Tigon3 never reports partial packet sends.  So we करो not
 * need special logic to handle SKBs that have not had all
 * of their frags sent yet, like SunGEM करोes.
 */
अटल व्योम tg3_tx(काष्ठा tg3_napi *tnapi)
अणु
	काष्ठा tg3 *tp = tnapi->tp;
	u32 hw_idx = tnapi->hw_status->idx[0].tx_consumer;
	u32 sw_idx = tnapi->tx_cons;
	काष्ठा netdev_queue *txq;
	पूर्णांक index = tnapi - tp->napi;
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;

	अगर (tg3_flag(tp, ENABLE_TSS))
		index--;

	txq = netdev_get_tx_queue(tp->dev, index);

	जबतक (sw_idx != hw_idx) अणु
		काष्ठा tg3_tx_ring_info *ri = &tnapi->tx_buffers[sw_idx];
		काष्ठा sk_buff *skb = ri->skb;
		पूर्णांक i, tx_bug = 0;

		अगर (unlikely(skb == शून्य)) अणु
			tg3_tx_recover(tp);
			वापस;
		पूर्ण

		अगर (tnapi->tx_ring[sw_idx].len_flags & TXD_FLAG_HWTSTAMP) अणु
			काष्ठा skb_shared_hwtstamps बारtamp;
			u64 hwघड़ी = tr32(TG3_TX_TSTAMP_LSB);
			hwघड़ी |= (u64)tr32(TG3_TX_TSTAMP_MSB) << 32;

			tg3_hwघड़ी_प्रकारo_बारtamp(tp, hwघड़ी, &बारtamp);

			skb_tstamp_tx(skb, &बारtamp);
		पूर्ण

		pci_unmap_single(tp->pdev,
				 dma_unmap_addr(ri, mapping),
				 skb_headlen(skb),
				 PCI_DMA_TODEVICE);

		ri->skb = शून्य;

		जबतक (ri->fragmented) अणु
			ri->fragmented = false;
			sw_idx = NEXT_TX(sw_idx);
			ri = &tnapi->tx_buffers[sw_idx];
		पूर्ण

		sw_idx = NEXT_TX(sw_idx);

		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			ri = &tnapi->tx_buffers[sw_idx];
			अगर (unlikely(ri->skb != शून्य || sw_idx == hw_idx))
				tx_bug = 1;

			pci_unmap_page(tp->pdev,
				       dma_unmap_addr(ri, mapping),
				       skb_frag_size(&skb_shinfo(skb)->frags[i]),
				       PCI_DMA_TODEVICE);

			जबतक (ri->fragmented) अणु
				ri->fragmented = false;
				sw_idx = NEXT_TX(sw_idx);
				ri = &tnapi->tx_buffers[sw_idx];
			पूर्ण

			sw_idx = NEXT_TX(sw_idx);
		पूर्ण

		pkts_compl++;
		bytes_compl += skb->len;

		dev_consume_skb_any(skb);

		अगर (unlikely(tx_bug)) अणु
			tg3_tx_recover(tp);
			वापस;
		पूर्ण
	पूर्ण

	netdev_tx_completed_queue(txq, pkts_compl, bytes_compl);

	tnapi->tx_cons = sw_idx;

	/* Need to make the tx_cons update visible to tg3_start_xmit()
	 * beक्रमe checking क्रम netअगर_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that tg3_start_xmit()
	 * will miss it and cause the queue to be stopped क्रमever.
	 */
	smp_mb();

	अगर (unlikely(netअगर_tx_queue_stopped(txq) &&
		     (tg3_tx_avail(tnapi) > TG3_TX_WAKEUP_THRESH(tnapi)))) अणु
		__netअगर_tx_lock(txq, smp_processor_id());
		अगर (netअगर_tx_queue_stopped(txq) &&
		    (tg3_tx_avail(tnapi) > TG3_TX_WAKEUP_THRESH(tnapi)))
			netअगर_tx_wake_queue(txq);
		__netअगर_tx_unlock(txq);
	पूर्ण
पूर्ण

अटल व्योम tg3_frag_मुक्त(bool is_frag, व्योम *data)
अणु
	अगर (is_frag)
		skb_मुक्त_frag(data);
	अन्यथा
		kमुक्त(data);
पूर्ण

अटल व्योम tg3_rx_data_मुक्त(काष्ठा tg3 *tp, काष्ठा ring_info *ri, u32 map_sz)
अणु
	अचिन्हित पूर्णांक skb_size = SKB_DATA_ALIGN(map_sz + TG3_RX_OFFSET(tp)) +
		   SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	अगर (!ri->data)
		वापस;

	pci_unmap_single(tp->pdev, dma_unmap_addr(ri, mapping),
			 map_sz, PCI_DMA_FROMDEVICE);
	tg3_frag_मुक्त(skb_size <= PAGE_SIZE, ri->data);
	ri->data = शून्य;
पूर्ण


/* Returns size of skb allocated or < 0 on error.
 *
 * We only need to fill in the address because the other members
 * of the RX descriptor are invariant, see tg3_init_rings.
 *
 * Note the purposeful assymetry of cpu vs. chip accesses.  For
 * posting buffers we only dirty the first cache line of the RX
 * descriptor (containing the address).  Whereas क्रम the RX status
 * buffers the cpu only पढ़ोs the last cacheline of the RX descriptor
 * (to fetch the error flags, vlan tag, checksum, and opaque cookie).
 */
अटल पूर्णांक tg3_alloc_rx_data(काष्ठा tg3 *tp, काष्ठा tg3_rx_prodring_set *tpr,
			     u32 opaque_key, u32 dest_idx_unmasked,
			     अचिन्हित पूर्णांक *frag_size)
अणु
	काष्ठा tg3_rx_buffer_desc *desc;
	काष्ठा ring_info *map;
	u8 *data;
	dma_addr_t mapping;
	पूर्णांक skb_size, data_size, dest_idx;

	चयन (opaque_key) अणु
	हाल RXD_OPAQUE_RING_STD:
		dest_idx = dest_idx_unmasked & tp->rx_std_ring_mask;
		desc = &tpr->rx_std[dest_idx];
		map = &tpr->rx_std_buffers[dest_idx];
		data_size = tp->rx_pkt_map_sz;
		अवरोध;

	हाल RXD_OPAQUE_RING_JUMBO:
		dest_idx = dest_idx_unmasked & tp->rx_jmb_ring_mask;
		desc = &tpr->rx_jmb[dest_idx].std;
		map = &tpr->rx_jmb_buffers[dest_idx];
		data_size = TG3_RX_JMB_MAP_SZ;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Do not overग_लिखो any of the map or rp inक्रमmation
	 * until we are sure we can commit to a new buffer.
	 *
	 * Callers depend upon this behavior and assume that
	 * we leave everything unchanged अगर we fail.
	 */
	skb_size = SKB_DATA_ALIGN(data_size + TG3_RX_OFFSET(tp)) +
		   SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	अगर (skb_size <= PAGE_SIZE) अणु
		data = napi_alloc_frag(skb_size);
		*frag_size = skb_size;
	पूर्ण अन्यथा अणु
		data = kदो_स्मृति(skb_size, GFP_ATOMIC);
		*frag_size = 0;
	पूर्ण
	अगर (!data)
		वापस -ENOMEM;

	mapping = pci_map_single(tp->pdev,
				 data + TG3_RX_OFFSET(tp),
				 data_size,
				 PCI_DMA_FROMDEVICE);
	अगर (unlikely(pci_dma_mapping_error(tp->pdev, mapping))) अणु
		tg3_frag_मुक्त(skb_size <= PAGE_SIZE, data);
		वापस -EIO;
	पूर्ण

	map->data = data;
	dma_unmap_addr_set(map, mapping, mapping);

	desc->addr_hi = ((u64)mapping >> 32);
	desc->addr_lo = ((u64)mapping & 0xffffffff);

	वापस data_size;
पूर्ण

/* We only need to move over in the address because the other
 * members of the RX descriptor are invariant.  See notes above
 * tg3_alloc_rx_data क्रम full details.
 */
अटल व्योम tg3_recycle_rx(काष्ठा tg3_napi *tnapi,
			   काष्ठा tg3_rx_prodring_set *dpr,
			   u32 opaque_key, पूर्णांक src_idx,
			   u32 dest_idx_unmasked)
अणु
	काष्ठा tg3 *tp = tnapi->tp;
	काष्ठा tg3_rx_buffer_desc *src_desc, *dest_desc;
	काष्ठा ring_info *src_map, *dest_map;
	काष्ठा tg3_rx_prodring_set *spr = &tp->napi[0].prodring;
	पूर्णांक dest_idx;

	चयन (opaque_key) अणु
	हाल RXD_OPAQUE_RING_STD:
		dest_idx = dest_idx_unmasked & tp->rx_std_ring_mask;
		dest_desc = &dpr->rx_std[dest_idx];
		dest_map = &dpr->rx_std_buffers[dest_idx];
		src_desc = &spr->rx_std[src_idx];
		src_map = &spr->rx_std_buffers[src_idx];
		अवरोध;

	हाल RXD_OPAQUE_RING_JUMBO:
		dest_idx = dest_idx_unmasked & tp->rx_jmb_ring_mask;
		dest_desc = &dpr->rx_jmb[dest_idx].std;
		dest_map = &dpr->rx_jmb_buffers[dest_idx];
		src_desc = &spr->rx_jmb[src_idx].std;
		src_map = &spr->rx_jmb_buffers[src_idx];
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	dest_map->data = src_map->data;
	dma_unmap_addr_set(dest_map, mapping,
			   dma_unmap_addr(src_map, mapping));
	dest_desc->addr_hi = src_desc->addr_hi;
	dest_desc->addr_lo = src_desc->addr_lo;

	/* Ensure that the update to the skb happens after the physical
	 * addresses have been transferred to the new BD location.
	 */
	smp_wmb();

	src_map->data = शून्य;
पूर्ण

/* The RX ring scheme is composed of multiple rings which post fresh
 * buffers to the chip, and one special ring the chip uses to report
 * status back to the host.
 *
 * The special ring reports the status of received packets to the
 * host.  The chip करोes not ग_लिखो पूर्णांकo the original descriptor the
 * RX buffer was obtained from.  The chip simply takes the original
 * descriptor as provided by the host, updates the status and length
 * field, then ग_लिखोs this पूर्णांकo the next status ring entry.
 *
 * Each ring the host uses to post buffers to the chip is described
 * by a TG3_BDINFO entry in the chips SRAM area.  When a packet arrives,
 * it is first placed पूर्णांकo the on-chip ram.  When the packet's length
 * is known, it walks करोwn the TG3_BDINFO entries to select the ring.
 * Each TG3_BDINFO specअगरies a MAXLEN field and the first TG3_BDINFO
 * which is within the range of the new packet's length is chosen.
 *
 * The "separate ring for rx status" scheme may sound queer, but it makes
 * sense from a cache coherency perspective.  If only the host ग_लिखोs
 * to the buffer post rings, and only the chip ग_लिखोs to the rx status
 * rings, then cache lines never move beyond shared-modअगरied state.
 * If both the host and chip were to ग_लिखो पूर्णांकo the same ring, cache line
 * eviction could occur since both entities want it in an exclusive state.
 */
अटल पूर्णांक tg3_rx(काष्ठा tg3_napi *tnapi, पूर्णांक budget)
अणु
	काष्ठा tg3 *tp = tnapi->tp;
	u32 work_mask, rx_std_posted = 0;
	u32 std_prod_idx, jmb_prod_idx;
	u32 sw_idx = tnapi->rx_rcb_ptr;
	u16 hw_idx;
	पूर्णांक received;
	काष्ठा tg3_rx_prodring_set *tpr = &tnapi->prodring;

	hw_idx = *(tnapi->rx_rcb_prod_idx);
	/*
	 * We need to order the पढ़ो of hw_idx and the पढ़ो of
	 * the opaque cookie.
	 */
	rmb();
	work_mask = 0;
	received = 0;
	std_prod_idx = tpr->rx_std_prod_idx;
	jmb_prod_idx = tpr->rx_jmb_prod_idx;
	जबतक (sw_idx != hw_idx && budget > 0) अणु
		काष्ठा ring_info *ri;
		काष्ठा tg3_rx_buffer_desc *desc = &tnapi->rx_rcb[sw_idx];
		अचिन्हित पूर्णांक len;
		काष्ठा sk_buff *skb;
		dma_addr_t dma_addr;
		u32 opaque_key, desc_idx, *post_ptr;
		u8 *data;
		u64 tstamp = 0;

		desc_idx = desc->opaque & RXD_OPAQUE_INDEX_MASK;
		opaque_key = desc->opaque & RXD_OPAQUE_RING_MASK;
		अगर (opaque_key == RXD_OPAQUE_RING_STD) अणु
			ri = &tp->napi[0].prodring.rx_std_buffers[desc_idx];
			dma_addr = dma_unmap_addr(ri, mapping);
			data = ri->data;
			post_ptr = &std_prod_idx;
			rx_std_posted++;
		पूर्ण अन्यथा अगर (opaque_key == RXD_OPAQUE_RING_JUMBO) अणु
			ri = &tp->napi[0].prodring.rx_jmb_buffers[desc_idx];
			dma_addr = dma_unmap_addr(ri, mapping);
			data = ri->data;
			post_ptr = &jmb_prod_idx;
		पूर्ण अन्यथा
			जाओ next_pkt_nopost;

		work_mask |= opaque_key;

		अगर (desc->err_vlan & RXD_ERR_MASK) अणु
		drop_it:
			tg3_recycle_rx(tnapi, tpr, opaque_key,
				       desc_idx, *post_ptr);
		drop_it_no_recycle:
			/* Other statistics kept track of by card. */
			tp->rx_dropped++;
			जाओ next_pkt;
		पूर्ण

		prefetch(data + TG3_RX_OFFSET(tp));
		len = ((desc->idx_len & RXD_LEN_MASK) >> RXD_LEN_SHIFT) -
		      ETH_FCS_LEN;

		अगर ((desc->type_flags & RXD_FLAG_PTPSTAT_MASK) ==
		     RXD_FLAG_PTPSTAT_PTPV1 ||
		    (desc->type_flags & RXD_FLAG_PTPSTAT_MASK) ==
		     RXD_FLAG_PTPSTAT_PTPV2) अणु
			tstamp = tr32(TG3_RX_TSTAMP_LSB);
			tstamp |= (u64)tr32(TG3_RX_TSTAMP_MSB) << 32;
		पूर्ण

		अगर (len > TG3_RX_COPY_THRESH(tp)) अणु
			पूर्णांक skb_size;
			अचिन्हित पूर्णांक frag_size;

			skb_size = tg3_alloc_rx_data(tp, tpr, opaque_key,
						    *post_ptr, &frag_size);
			अगर (skb_size < 0)
				जाओ drop_it;

			pci_unmap_single(tp->pdev, dma_addr, skb_size,
					 PCI_DMA_FROMDEVICE);

			/* Ensure that the update to the data happens
			 * after the usage of the old DMA mapping.
			 */
			smp_wmb();

			ri->data = शून्य;

			skb = build_skb(data, frag_size);
			अगर (!skb) अणु
				tg3_frag_मुक्त(frag_size != 0, data);
				जाओ drop_it_no_recycle;
			पूर्ण
			skb_reserve(skb, TG3_RX_OFFSET(tp));
		पूर्ण अन्यथा अणु
			tg3_recycle_rx(tnapi, tpr, opaque_key,
				       desc_idx, *post_ptr);

			skb = netdev_alloc_skb(tp->dev,
					       len + TG3_RAW_IP_ALIGN);
			अगर (skb == शून्य)
				जाओ drop_it_no_recycle;

			skb_reserve(skb, TG3_RAW_IP_ALIGN);
			pci_dma_sync_single_क्रम_cpu(tp->pdev, dma_addr, len, PCI_DMA_FROMDEVICE);
			स_नकल(skb->data,
			       data + TG3_RX_OFFSET(tp),
			       len);
			pci_dma_sync_single_क्रम_device(tp->pdev, dma_addr, len, PCI_DMA_FROMDEVICE);
		पूर्ण

		skb_put(skb, len);
		अगर (tstamp)
			tg3_hwघड़ी_प्रकारo_बारtamp(tp, tstamp,
						 skb_hwtstamps(skb));

		अगर ((tp->dev->features & NETIF_F_RXCSUM) &&
		    (desc->type_flags & RXD_FLAG_TCPUDP_CSUM) &&
		    (((desc->ip_tcp_csum & RXD_TCPCSUM_MASK)
		      >> RXD_TCPCSUM_SHIFT) == 0xffff))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);

		skb->protocol = eth_type_trans(skb, tp->dev);

		अगर (len > (tp->dev->mtu + ETH_HLEN) &&
		    skb->protocol != htons(ETH_P_8021Q) &&
		    skb->protocol != htons(ETH_P_8021AD)) अणु
			dev_kमुक्त_skb_any(skb);
			जाओ drop_it_no_recycle;
		पूर्ण

		अगर (desc->type_flags & RXD_FLAG_VLAN &&
		    !(tp->rx_mode & RX_MODE_KEEP_VLAN_TAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       desc->err_vlan & RXD_VLAN_MASK);

		napi_gro_receive(&tnapi->napi, skb);

		received++;
		budget--;

next_pkt:
		(*post_ptr)++;

		अगर (unlikely(rx_std_posted >= tp->rx_std_max_post)) अणु
			tpr->rx_std_prod_idx = std_prod_idx &
					       tp->rx_std_ring_mask;
			tw32_rx_mbox(TG3_RX_STD_PROD_IDX_REG,
				     tpr->rx_std_prod_idx);
			work_mask &= ~RXD_OPAQUE_RING_STD;
			rx_std_posted = 0;
		पूर्ण
next_pkt_nopost:
		sw_idx++;
		sw_idx &= tp->rx_ret_ring_mask;

		/* Refresh hw_idx to see अगर there is new work */
		अगर (sw_idx == hw_idx) अणु
			hw_idx = *(tnapi->rx_rcb_prod_idx);
			rmb();
		पूर्ण
	पूर्ण

	/* ACK the status ring. */
	tnapi->rx_rcb_ptr = sw_idx;
	tw32_rx_mbox(tnapi->consmbox, sw_idx);

	/* Refill RX ring(s). */
	अगर (!tg3_flag(tp, ENABLE_RSS)) अणु
		/* Sync BD data beक्रमe updating mailbox */
		wmb();

		अगर (work_mask & RXD_OPAQUE_RING_STD) अणु
			tpr->rx_std_prod_idx = std_prod_idx &
					       tp->rx_std_ring_mask;
			tw32_rx_mbox(TG3_RX_STD_PROD_IDX_REG,
				     tpr->rx_std_prod_idx);
		पूर्ण
		अगर (work_mask & RXD_OPAQUE_RING_JUMBO) अणु
			tpr->rx_jmb_prod_idx = jmb_prod_idx &
					       tp->rx_jmb_ring_mask;
			tw32_rx_mbox(TG3_RX_JMB_PROD_IDX_REG,
				     tpr->rx_jmb_prod_idx);
		पूर्ण
	पूर्ण अन्यथा अगर (work_mask) अणु
		/* rx_std_buffers[] and rx_jmb_buffers[] entries must be
		 * updated beक्रमe the producer indices can be updated.
		 */
		smp_wmb();

		tpr->rx_std_prod_idx = std_prod_idx & tp->rx_std_ring_mask;
		tpr->rx_jmb_prod_idx = jmb_prod_idx & tp->rx_jmb_ring_mask;

		अगर (tnapi != &tp->napi[1]) अणु
			tp->rx_refill = true;
			napi_schedule(&tp->napi[1].napi);
		पूर्ण
	पूर्ण

	वापस received;
पूर्ण

अटल व्योम tg3_poll_link(काष्ठा tg3 *tp)
अणु
	/* handle link change and other phy events */
	अगर (!(tg3_flag(tp, USE_LINKCHG_REG) || tg3_flag(tp, POLL_SERDES))) अणु
		काष्ठा tg3_hw_status *sblk = tp->napi[0].hw_status;

		अगर (sblk->status & SD_STATUS_LINK_CHG) अणु
			sblk->status = SD_STATUS_UPDATED |
				       (sblk->status & ~SD_STATUS_LINK_CHG);
			spin_lock(&tp->lock);
			अगर (tg3_flag(tp, USE_PHYLIB)) अणु
				tw32_f(MAC_STATUS,
				     (MAC_STATUS_SYNC_CHANGED |
				      MAC_STATUS_CFG_CHANGED |
				      MAC_STATUS_MI_COMPLETION |
				      MAC_STATUS_LNKSTATE_CHANGED));
				udelay(40);
			पूर्ण अन्यथा
				tg3_setup_phy(tp, false);
			spin_unlock(&tp->lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_rx_prodring_xfer(काष्ठा tg3 *tp,
				काष्ठा tg3_rx_prodring_set *dpr,
				काष्ठा tg3_rx_prodring_set *spr)
अणु
	u32 si, di, cpycnt, src_prod_idx;
	पूर्णांक i, err = 0;

	जबतक (1) अणु
		src_prod_idx = spr->rx_std_prod_idx;

		/* Make sure updates to the rx_std_buffers[] entries and the
		 * standard producer index are seen in the correct order.
		 */
		smp_rmb();

		अगर (spr->rx_std_cons_idx == src_prod_idx)
			अवरोध;

		अगर (spr->rx_std_cons_idx < src_prod_idx)
			cpycnt = src_prod_idx - spr->rx_std_cons_idx;
		अन्यथा
			cpycnt = tp->rx_std_ring_mask + 1 -
				 spr->rx_std_cons_idx;

		cpycnt = min(cpycnt,
			     tp->rx_std_ring_mask + 1 - dpr->rx_std_prod_idx);

		si = spr->rx_std_cons_idx;
		di = dpr->rx_std_prod_idx;

		क्रम (i = di; i < di + cpycnt; i++) अणु
			अगर (dpr->rx_std_buffers[i].data) अणु
				cpycnt = i - di;
				err = -ENOSPC;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!cpycnt)
			अवरोध;

		/* Ensure that updates to the rx_std_buffers ring and the
		 * shaकरोwed hardware producer ring from tg3_recycle_skb() are
		 * ordered correctly WRT the skb check above.
		 */
		smp_rmb();

		स_नकल(&dpr->rx_std_buffers[di],
		       &spr->rx_std_buffers[si],
		       cpycnt * माप(काष्ठा ring_info));

		क्रम (i = 0; i < cpycnt; i++, di++, si++) अणु
			काष्ठा tg3_rx_buffer_desc *sbd, *dbd;
			sbd = &spr->rx_std[si];
			dbd = &dpr->rx_std[di];
			dbd->addr_hi = sbd->addr_hi;
			dbd->addr_lo = sbd->addr_lo;
		पूर्ण

		spr->rx_std_cons_idx = (spr->rx_std_cons_idx + cpycnt) &
				       tp->rx_std_ring_mask;
		dpr->rx_std_prod_idx = (dpr->rx_std_prod_idx + cpycnt) &
				       tp->rx_std_ring_mask;
	पूर्ण

	जबतक (1) अणु
		src_prod_idx = spr->rx_jmb_prod_idx;

		/* Make sure updates to the rx_jmb_buffers[] entries and
		 * the jumbo producer index are seen in the correct order.
		 */
		smp_rmb();

		अगर (spr->rx_jmb_cons_idx == src_prod_idx)
			अवरोध;

		अगर (spr->rx_jmb_cons_idx < src_prod_idx)
			cpycnt = src_prod_idx - spr->rx_jmb_cons_idx;
		अन्यथा
			cpycnt = tp->rx_jmb_ring_mask + 1 -
				 spr->rx_jmb_cons_idx;

		cpycnt = min(cpycnt,
			     tp->rx_jmb_ring_mask + 1 - dpr->rx_jmb_prod_idx);

		si = spr->rx_jmb_cons_idx;
		di = dpr->rx_jmb_prod_idx;

		क्रम (i = di; i < di + cpycnt; i++) अणु
			अगर (dpr->rx_jmb_buffers[i].data) अणु
				cpycnt = i - di;
				err = -ENOSPC;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!cpycnt)
			अवरोध;

		/* Ensure that updates to the rx_jmb_buffers ring and the
		 * shaकरोwed hardware producer ring from tg3_recycle_skb() are
		 * ordered correctly WRT the skb check above.
		 */
		smp_rmb();

		स_नकल(&dpr->rx_jmb_buffers[di],
		       &spr->rx_jmb_buffers[si],
		       cpycnt * माप(काष्ठा ring_info));

		क्रम (i = 0; i < cpycnt; i++, di++, si++) अणु
			काष्ठा tg3_rx_buffer_desc *sbd, *dbd;
			sbd = &spr->rx_jmb[si].std;
			dbd = &dpr->rx_jmb[di].std;
			dbd->addr_hi = sbd->addr_hi;
			dbd->addr_lo = sbd->addr_lo;
		पूर्ण

		spr->rx_jmb_cons_idx = (spr->rx_jmb_cons_idx + cpycnt) &
				       tp->rx_jmb_ring_mask;
		dpr->rx_jmb_prod_idx = (dpr->rx_jmb_prod_idx + cpycnt) &
				       tp->rx_jmb_ring_mask;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tg3_poll_work(काष्ठा tg3_napi *tnapi, पूर्णांक work_करोne, पूर्णांक budget)
अणु
	काष्ठा tg3 *tp = tnapi->tp;

	/* run TX completion thपढ़ो */
	अगर (tnapi->hw_status->idx[0].tx_consumer != tnapi->tx_cons) अणु
		tg3_tx(tnapi);
		अगर (unlikely(tg3_flag(tp, TX_RECOVERY_PENDING)))
			वापस work_करोne;
	पूर्ण

	अगर (!tnapi->rx_rcb_prod_idx)
		वापस work_करोne;

	/* run RX thपढ़ो, within the bounds set by NAPI.
	 * All RX "locking" is करोne by ensuring outside
	 * code synchronizes with tg3->napi.poll()
	 */
	अगर (*(tnapi->rx_rcb_prod_idx) != tnapi->rx_rcb_ptr)
		work_करोne += tg3_rx(tnapi, budget - work_करोne);

	अगर (tg3_flag(tp, ENABLE_RSS) && tnapi == &tp->napi[1]) अणु
		काष्ठा tg3_rx_prodring_set *dpr = &tp->napi[0].prodring;
		पूर्णांक i, err = 0;
		u32 std_prod_idx = dpr->rx_std_prod_idx;
		u32 jmb_prod_idx = dpr->rx_jmb_prod_idx;

		tp->rx_refill = false;
		क्रम (i = 1; i <= tp->rxq_cnt; i++)
			err |= tg3_rx_prodring_xfer(tp, dpr,
						    &tp->napi[i].prodring);

		wmb();

		अगर (std_prod_idx != dpr->rx_std_prod_idx)
			tw32_rx_mbox(TG3_RX_STD_PROD_IDX_REG,
				     dpr->rx_std_prod_idx);

		अगर (jmb_prod_idx != dpr->rx_jmb_prod_idx)
			tw32_rx_mbox(TG3_RX_JMB_PROD_IDX_REG,
				     dpr->rx_jmb_prod_idx);

		अगर (err)
			tw32_f(HOSTCC_MODE, tp->coal_now);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल अंतरभूत व्योम tg3_reset_task_schedule(काष्ठा tg3 *tp)
अणु
	अगर (!test_and_set_bit(TG3_FLAG_RESET_TASK_PENDING, tp->tg3_flags))
		schedule_work(&tp->reset_task);
पूर्ण

अटल अंतरभूत व्योम tg3_reset_task_cancel(काष्ठा tg3 *tp)
अणु
	अगर (test_and_clear_bit(TG3_FLAG_RESET_TASK_PENDING, tp->tg3_flags))
		cancel_work_sync(&tp->reset_task);
	tg3_flag_clear(tp, TX_RECOVERY_PENDING);
पूर्ण

अटल पूर्णांक tg3_poll_msix(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा tg3_napi *tnapi = container_of(napi, काष्ठा tg3_napi, napi);
	काष्ठा tg3 *tp = tnapi->tp;
	पूर्णांक work_करोne = 0;
	काष्ठा tg3_hw_status *sblk = tnapi->hw_status;

	जबतक (1) अणु
		work_करोne = tg3_poll_work(tnapi, work_करोne, budget);

		अगर (unlikely(tg3_flag(tp, TX_RECOVERY_PENDING)))
			जाओ tx_recovery;

		अगर (unlikely(work_करोne >= budget))
			अवरोध;

		/* tp->last_tag is used in tg3_पूर्णांक_reenable() below
		 * to tell the hw how much work has been processed,
		 * so we must पढ़ो it beक्रमe checking क्रम more work.
		 */
		tnapi->last_tag = sblk->status_tag;
		tnapi->last_irq_tag = tnapi->last_tag;
		rmb();

		/* check क्रम RX/TX work to करो */
		अगर (likely(sblk->idx[0].tx_consumer == tnapi->tx_cons &&
			   *(tnapi->rx_rcb_prod_idx) == tnapi->rx_rcb_ptr)) अणु

			/* This test here is not race मुक्त, but will reduce
			 * the number of पूर्णांकerrupts by looping again.
			 */
			अगर (tnapi == &tp->napi[1] && tp->rx_refill)
				जारी;

			napi_complete_करोne(napi, work_करोne);
			/* Reenable पूर्णांकerrupts. */
			tw32_mailbox(tnapi->पूर्णांक_mbox, tnapi->last_tag << 24);

			/* This test here is synchronized by napi_schedule()
			 * and napi_complete() to बंद the race condition.
			 */
			अगर (unlikely(tnapi == &tp->napi[1] && tp->rx_refill)) अणु
				tw32(HOSTCC_MODE, tp->coalesce_mode |
						  HOSTCC_MODE_ENABLE |
						  tnapi->coal_now);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	tg3_send_ape_heartbeat(tp, TG3_APE_HB_INTERVAL << 1);
	वापस work_करोne;

tx_recovery:
	/* work_करोne is guaranteed to be less than budget. */
	napi_complete(napi);
	tg3_reset_task_schedule(tp);
	वापस work_करोne;
पूर्ण

अटल व्योम tg3_process_error(काष्ठा tg3 *tp)
अणु
	u32 val;
	bool real_error = false;

	अगर (tg3_flag(tp, ERROR_PROCESSED))
		वापस;

	/* Check Flow Attention रेजिस्टर */
	val = tr32(HOSTCC_FLOW_ATTN);
	अगर (val & ~HOSTCC_FLOW_ATTN_MBUF_LWM) अणु
		netdev_err(tp->dev, "FLOW Attention error.  Resetting chip.\n");
		real_error = true;
	पूर्ण

	अगर (tr32(MSGINT_STATUS) & ~MSGINT_STATUS_MSI_REQ) अणु
		netdev_err(tp->dev, "MSI Status error.  Resetting chip.\n");
		real_error = true;
	पूर्ण

	अगर (tr32(RDMAC_STATUS) || tr32(WDMAC_STATUS)) अणु
		netdev_err(tp->dev, "DMA Status error.  Resetting chip.\n");
		real_error = true;
	पूर्ण

	अगर (!real_error)
		वापस;

	tg3_dump_state(tp);

	tg3_flag_set(tp, ERROR_PROCESSED);
	tg3_reset_task_schedule(tp);
पूर्ण

अटल पूर्णांक tg3_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा tg3_napi *tnapi = container_of(napi, काष्ठा tg3_napi, napi);
	काष्ठा tg3 *tp = tnapi->tp;
	पूर्णांक work_करोne = 0;
	काष्ठा tg3_hw_status *sblk = tnapi->hw_status;

	जबतक (1) अणु
		अगर (sblk->status & SD_STATUS_ERROR)
			tg3_process_error(tp);

		tg3_poll_link(tp);

		work_करोne = tg3_poll_work(tnapi, work_करोne, budget);

		अगर (unlikely(tg3_flag(tp, TX_RECOVERY_PENDING)))
			जाओ tx_recovery;

		अगर (unlikely(work_करोne >= budget))
			अवरोध;

		अगर (tg3_flag(tp, TAGGED_STATUS)) अणु
			/* tp->last_tag is used in tg3_पूर्णांक_reenable() below
			 * to tell the hw how much work has been processed,
			 * so we must पढ़ो it beक्रमe checking क्रम more work.
			 */
			tnapi->last_tag = sblk->status_tag;
			tnapi->last_irq_tag = tnapi->last_tag;
			rmb();
		पूर्ण अन्यथा
			sblk->status &= ~SD_STATUS_UPDATED;

		अगर (likely(!tg3_has_work(tnapi))) अणु
			napi_complete_करोne(napi, work_करोne);
			tg3_पूर्णांक_reenable(tnapi);
			अवरोध;
		पूर्ण
	पूर्ण

	tg3_send_ape_heartbeat(tp, TG3_APE_HB_INTERVAL << 1);
	वापस work_करोne;

tx_recovery:
	/* work_करोne is guaranteed to be less than budget. */
	napi_complete(napi);
	tg3_reset_task_schedule(tp);
	वापस work_करोne;
पूर्ण

अटल व्योम tg3_napi_disable(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	क्रम (i = tp->irq_cnt - 1; i >= 0; i--)
		napi_disable(&tp->napi[i].napi);
पूर्ण

अटल व्योम tg3_napi_enable(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tp->irq_cnt; i++)
		napi_enable(&tp->napi[i].napi);
पूर्ण

अटल व्योम tg3_napi_init(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	netअगर_napi_add(tp->dev, &tp->napi[0].napi, tg3_poll, 64);
	क्रम (i = 1; i < tp->irq_cnt; i++)
		netअगर_napi_add(tp->dev, &tp->napi[i].napi, tg3_poll_msix, 64);
पूर्ण

अटल व्योम tg3_napi_fini(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tp->irq_cnt; i++)
		netअगर_napi_del(&tp->napi[i].napi);
पूर्ण

अटल अंतरभूत व्योम tg3_netअगर_stop(काष्ठा tg3 *tp)
अणु
	netअगर_trans_update(tp->dev);	/* prevent tx समयout */
	tg3_napi_disable(tp);
	netअगर_carrier_off(tp->dev);
	netअगर_tx_disable(tp->dev);
पूर्ण

/* tp->lock must be held */
अटल अंतरभूत व्योम tg3_netअगर_start(काष्ठा tg3 *tp)
अणु
	tg3_ptp_resume(tp);

	/* NOTE: unconditional netअगर_tx_wake_all_queues is only
	 * appropriate so दीर्घ as all callers are assured to
	 * have मुक्त tx slots (such as after tg3_init_hw)
	 */
	netअगर_tx_wake_all_queues(tp->dev);

	अगर (tp->link_up)
		netअगर_carrier_on(tp->dev);

	tg3_napi_enable(tp);
	tp->napi[0].hw_status->status |= SD_STATUS_UPDATED;
	tg3_enable_पूर्णांकs(tp);
पूर्ण

अटल व्योम tg3_irq_quiesce(काष्ठा tg3 *tp)
	__releases(tp->lock)
	__acquires(tp->lock)
अणु
	पूर्णांक i;

	BUG_ON(tp->irq_sync);

	tp->irq_sync = 1;
	smp_mb();

	spin_unlock_bh(&tp->lock);

	क्रम (i = 0; i < tp->irq_cnt; i++)
		synchronize_irq(tp->napi[i].irq_vec);

	spin_lock_bh(&tp->lock);
पूर्ण

/* Fully shutकरोwn all tg3 driver activity अन्यथाwhere in the प्रणाली.
 * If irq_sync is non-zero, then the IRQ handler must be synchronized
 * with as well.  Most of the समय, this is not necessary except when
 * shutting करोwn the device.
 */
अटल अंतरभूत व्योम tg3_full_lock(काष्ठा tg3 *tp, पूर्णांक irq_sync)
अणु
	spin_lock_bh(&tp->lock);
	अगर (irq_sync)
		tg3_irq_quiesce(tp);
पूर्ण

अटल अंतरभूत व्योम tg3_full_unlock(काष्ठा tg3 *tp)
अणु
	spin_unlock_bh(&tp->lock);
पूर्ण

/* One-shot MSI handler - Chip स्वतःmatically disables पूर्णांकerrupt
 * after sending MSI so driver करोesn't have to करो it.
 */
अटल irqवापस_t tg3_msi_1shot(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tg3_napi *tnapi = dev_id;
	काष्ठा tg3 *tp = tnapi->tp;

	prefetch(tnapi->hw_status);
	अगर (tnapi->rx_rcb)
		prefetch(&tnapi->rx_rcb[tnapi->rx_rcb_ptr]);

	अगर (likely(!tg3_irq_sync(tp)))
		napi_schedule(&tnapi->napi);

	वापस IRQ_HANDLED;
पूर्ण

/* MSI ISR - No need to check क्रम पूर्णांकerrupt sharing and no need to
 * flush status block and पूर्णांकerrupt mailbox. PCI ordering rules
 * guarantee that MSI will arrive after the status block.
 */
अटल irqवापस_t tg3_msi(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tg3_napi *tnapi = dev_id;
	काष्ठा tg3 *tp = tnapi->tp;

	prefetch(tnapi->hw_status);
	अगर (tnapi->rx_rcb)
		prefetch(&tnapi->rx_rcb[tnapi->rx_rcb_ptr]);
	/*
	 * Writing any value to पूर्णांकr-mbox-0 clears PCI INTA# and
	 * chip-पूर्णांकernal पूर्णांकerrupt pending events.
	 * Writing non-zero to पूर्णांकr-mbox-0 additional tells the
	 * NIC to stop sending us irqs, engaging "in-intr-handler"
	 * event coalescing.
	 */
	tw32_mailbox(tnapi->पूर्णांक_mbox, 0x00000001);
	अगर (likely(!tg3_irq_sync(tp)))
		napi_schedule(&tnapi->napi);

	वापस IRQ_RETVAL(1);
पूर्ण

अटल irqवापस_t tg3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tg3_napi *tnapi = dev_id;
	काष्ठा tg3 *tp = tnapi->tp;
	काष्ठा tg3_hw_status *sblk = tnapi->hw_status;
	अचिन्हित पूर्णांक handled = 1;

	/* In INTx mode, it is possible क्रम the पूर्णांकerrupt to arrive at
	 * the CPU beक्रमe the status block posted prior to the पूर्णांकerrupt.
	 * Reading the PCI State रेजिस्टर will confirm whether the
	 * पूर्णांकerrupt is ours and will flush the status block.
	 */
	अगर (unlikely(!(sblk->status & SD_STATUS_UPDATED))) अणु
		अगर (tg3_flag(tp, CHIP_RESETTING) ||
		    (tr32(TG3PCI_PCISTATE) & PCISTATE_INT_NOT_ACTIVE)) अणु
			handled = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Writing any value to पूर्णांकr-mbox-0 clears PCI INTA# and
	 * chip-पूर्णांकernal पूर्णांकerrupt pending events.
	 * Writing non-zero to पूर्णांकr-mbox-0 additional tells the
	 * NIC to stop sending us irqs, engaging "in-intr-handler"
	 * event coalescing.
	 *
	 * Flush the mailbox to de-निश्चित the IRQ immediately to prevent
	 * spurious पूर्णांकerrupts.  The flush impacts perक्रमmance but
	 * excessive spurious पूर्णांकerrupts can be worse in some हालs.
	 */
	tw32_mailbox_f(MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW, 0x00000001);
	अगर (tg3_irq_sync(tp))
		जाओ out;
	sblk->status &= ~SD_STATUS_UPDATED;
	अगर (likely(tg3_has_work(tnapi))) अणु
		prefetch(&tnapi->rx_rcb[tnapi->rx_rcb_ptr]);
		napi_schedule(&tnapi->napi);
	पूर्ण अन्यथा अणु
		/* No work, shared पूर्णांकerrupt perhaps?  re-enable
		 * पूर्णांकerrupts, and flush that PCI ग_लिखो
		 */
		tw32_mailbox_f(MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW,
			       0x00000000);
	पूर्ण
out:
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल irqवापस_t tg3_पूर्णांकerrupt_tagged(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tg3_napi *tnapi = dev_id;
	काष्ठा tg3 *tp = tnapi->tp;
	काष्ठा tg3_hw_status *sblk = tnapi->hw_status;
	अचिन्हित पूर्णांक handled = 1;

	/* In INTx mode, it is possible क्रम the पूर्णांकerrupt to arrive at
	 * the CPU beक्रमe the status block posted prior to the पूर्णांकerrupt.
	 * Reading the PCI State रेजिस्टर will confirm whether the
	 * पूर्णांकerrupt is ours and will flush the status block.
	 */
	अगर (unlikely(sblk->status_tag == tnapi->last_irq_tag)) अणु
		अगर (tg3_flag(tp, CHIP_RESETTING) ||
		    (tr32(TG3PCI_PCISTATE) & PCISTATE_INT_NOT_ACTIVE)) अणु
			handled = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * writing any value to पूर्णांकr-mbox-0 clears PCI INTA# and
	 * chip-पूर्णांकernal पूर्णांकerrupt pending events.
	 * writing non-zero to पूर्णांकr-mbox-0 additional tells the
	 * NIC to stop sending us irqs, engaging "in-intr-handler"
	 * event coalescing.
	 *
	 * Flush the mailbox to de-निश्चित the IRQ immediately to prevent
	 * spurious पूर्णांकerrupts.  The flush impacts perक्रमmance but
	 * excessive spurious पूर्णांकerrupts can be worse in some हालs.
	 */
	tw32_mailbox_f(MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW, 0x00000001);

	/*
	 * In a shared पूर्णांकerrupt configuration, someबार other devices'
	 * पूर्णांकerrupts will scream.  We record the current status tag here
	 * so that the above check can report that the screaming पूर्णांकerrupts
	 * are unhandled.  Eventually they will be silenced.
	 */
	tnapi->last_irq_tag = sblk->status_tag;

	अगर (tg3_irq_sync(tp))
		जाओ out;

	prefetch(&tnapi->rx_rcb[tnapi->rx_rcb_ptr]);

	napi_schedule(&tnapi->napi);

out:
	वापस IRQ_RETVAL(handled);
पूर्ण

/* ISR क्रम पूर्णांकerrupt test */
अटल irqवापस_t tg3_test_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tg3_napi *tnapi = dev_id;
	काष्ठा tg3 *tp = tnapi->tp;
	काष्ठा tg3_hw_status *sblk = tnapi->hw_status;

	अगर ((sblk->status & SD_STATUS_UPDATED) ||
	    !(tr32(TG3PCI_PCISTATE) & PCISTATE_INT_NOT_ACTIVE)) अणु
		tg3_disable_पूर्णांकs(tp);
		वापस IRQ_RETVAL(1);
	पूर्ण
	वापस IRQ_RETVAL(0);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम tg3_poll_controller(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (tg3_irq_sync(tp))
		वापस;

	क्रम (i = 0; i < tp->irq_cnt; i++)
		tg3_पूर्णांकerrupt(tp->napi[i].irq_vec, &tp->napi[i]);
पूर्ण
#पूर्ण_अगर

अटल व्योम tg3_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (netअगर_msg_tx_err(tp)) अणु
		netdev_err(dev, "transmit timed out, resetting\n");
		tg3_dump_state(tp);
	पूर्ण

	tg3_reset_task_schedule(tp);
पूर्ण

/* Test क्रम DMA buffers crossing any 4GB boundaries: 4G, 8G, etc */
अटल अंतरभूत पूर्णांक tg3_4g_overflow_test(dma_addr_t mapping, पूर्णांक len)
अणु
	u32 base = (u32) mapping & 0xffffffff;

	वापस base + len + 8 < base;
पूर्ण

/* Test क्रम TSO DMA buffers that cross पूर्णांकo regions which are within MSS bytes
 * of any 4GB boundaries: 4G, 8G, etc
 */
अटल अंतरभूत पूर्णांक tg3_4g_tso_overflow_test(काष्ठा tg3 *tp, dma_addr_t mapping,
					   u32 len, u32 mss)
अणु
	अगर (tg3_asic_rev(tp) == ASIC_REV_5762 && mss) अणु
		u32 base = (u32) mapping & 0xffffffff;

		वापस ((base + len + (mss & 0x3fff)) < base);
	पूर्ण
	वापस 0;
पूर्ण

/* Test क्रम DMA addresses > 40-bit */
अटल अंतरभूत पूर्णांक tg3_40bit_overflow_test(काष्ठा tg3 *tp, dma_addr_t mapping,
					  पूर्णांक len)
अणु
#अगर defined(CONFIG_HIGHMEM) && (BITS_PER_LONG == 64)
	अगर (tg3_flag(tp, 40BIT_DMA_BUG))
		वापस ((u64) mapping + len) > DMA_BIT_MASK(40);
	वापस 0;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम tg3_tx_set_bd(काष्ठा tg3_tx_buffer_desc *txbd,
				 dma_addr_t mapping, u32 len, u32 flags,
				 u32 mss, u32 vlan)
अणु
	txbd->addr_hi = ((u64) mapping >> 32);
	txbd->addr_lo = ((u64) mapping & 0xffffffff);
	txbd->len_flags = (len << TXD_LEN_SHIFT) | (flags & 0x0000ffff);
	txbd->vlan_tag = (mss << TXD_MSS_SHIFT) | (vlan << TXD_VLAN_TAG_SHIFT);
पूर्ण

अटल bool tg3_tx_frag_set(काष्ठा tg3_napi *tnapi, u32 *entry, u32 *budget,
			    dma_addr_t map, u32 len, u32 flags,
			    u32 mss, u32 vlan)
अणु
	काष्ठा tg3 *tp = tnapi->tp;
	bool hwbug = false;

	अगर (tg3_flag(tp, SHORT_DMA_BUG) && len <= 8)
		hwbug = true;

	अगर (tg3_4g_overflow_test(map, len))
		hwbug = true;

	अगर (tg3_4g_tso_overflow_test(tp, map, len, mss))
		hwbug = true;

	अगर (tg3_40bit_overflow_test(tp, map, len))
		hwbug = true;

	अगर (tp->dma_limit) अणु
		u32 prvidx = *entry;
		u32 पंचांगp_flag = flags & ~TXD_FLAG_END;
		जबतक (len > tp->dma_limit && *budget) अणु
			u32 frag_len = tp->dma_limit;
			len -= tp->dma_limit;

			/* Aव्योम the 8byte DMA problem */
			अगर (len <= 8) अणु
				len += tp->dma_limit / 2;
				frag_len = tp->dma_limit / 2;
			पूर्ण

			tnapi->tx_buffers[*entry].fragmented = true;

			tg3_tx_set_bd(&tnapi->tx_ring[*entry], map,
				      frag_len, पंचांगp_flag, mss, vlan);
			*budget -= 1;
			prvidx = *entry;
			*entry = NEXT_TX(*entry);

			map += frag_len;
		पूर्ण

		अगर (len) अणु
			अगर (*budget) अणु
				tg3_tx_set_bd(&tnapi->tx_ring[*entry], map,
					      len, flags, mss, vlan);
				*budget -= 1;
				*entry = NEXT_TX(*entry);
			पूर्ण अन्यथा अणु
				hwbug = true;
				tnapi->tx_buffers[prvidx].fragmented = false;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		tg3_tx_set_bd(&tnapi->tx_ring[*entry], map,
			      len, flags, mss, vlan);
		*entry = NEXT_TX(*entry);
	पूर्ण

	वापस hwbug;
पूर्ण

अटल व्योम tg3_tx_skb_unmap(काष्ठा tg3_napi *tnapi, u32 entry, पूर्णांक last)
अणु
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा tg3_tx_ring_info *txb = &tnapi->tx_buffers[entry];

	skb = txb->skb;
	txb->skb = शून्य;

	pci_unmap_single(tnapi->tp->pdev,
			 dma_unmap_addr(txb, mapping),
			 skb_headlen(skb),
			 PCI_DMA_TODEVICE);

	जबतक (txb->fragmented) अणु
		txb->fragmented = false;
		entry = NEXT_TX(entry);
		txb = &tnapi->tx_buffers[entry];
	पूर्ण

	क्रम (i = 0; i <= last; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		entry = NEXT_TX(entry);
		txb = &tnapi->tx_buffers[entry];

		pci_unmap_page(tnapi->tp->pdev,
			       dma_unmap_addr(txb, mapping),
			       skb_frag_size(frag), PCI_DMA_TODEVICE);

		जबतक (txb->fragmented) अणु
			txb->fragmented = false;
			entry = NEXT_TX(entry);
			txb = &tnapi->tx_buffers[entry];
		पूर्ण
	पूर्ण
पूर्ण

/* Workaround 4GB and 40-bit hardware DMA bugs. */
अटल पूर्णांक tigon3_dma_hwbug_workaround(काष्ठा tg3_napi *tnapi,
				       काष्ठा sk_buff **pskb,
				       u32 *entry, u32 *budget,
				       u32 base_flags, u32 mss, u32 vlan)
अणु
	काष्ठा tg3 *tp = tnapi->tp;
	काष्ठा sk_buff *new_skb, *skb = *pskb;
	dma_addr_t new_addr = 0;
	पूर्णांक ret = 0;

	अगर (tg3_asic_rev(tp) != ASIC_REV_5701)
		new_skb = skb_copy(skb, GFP_ATOMIC);
	अन्यथा अणु
		पूर्णांक more_headroom = 4 - ((अचिन्हित दीर्घ)skb->data & 3);

		new_skb = skb_copy_expand(skb,
					  skb_headroom(skb) + more_headroom,
					  skb_tailroom(skb), GFP_ATOMIC);
	पूर्ण

	अगर (!new_skb) अणु
		ret = -1;
	पूर्ण अन्यथा अणु
		/* New SKB is guaranteed to be linear. */
		new_addr = pci_map_single(tp->pdev, new_skb->data, new_skb->len,
					  PCI_DMA_TODEVICE);
		/* Make sure the mapping succeeded */
		अगर (pci_dma_mapping_error(tp->pdev, new_addr)) अणु
			dev_kमुक्त_skb_any(new_skb);
			ret = -1;
		पूर्ण अन्यथा अणु
			u32 save_entry = *entry;

			base_flags |= TXD_FLAG_END;

			tnapi->tx_buffers[*entry].skb = new_skb;
			dma_unmap_addr_set(&tnapi->tx_buffers[*entry],
					   mapping, new_addr);

			अगर (tg3_tx_frag_set(tnapi, entry, budget, new_addr,
					    new_skb->len, base_flags,
					    mss, vlan)) अणु
				tg3_tx_skb_unmap(tnapi, save_entry, -1);
				dev_kमुक्त_skb_any(new_skb);
				ret = -1;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_consume_skb_any(skb);
	*pskb = new_skb;
	वापस ret;
पूर्ण

अटल bool tg3_tso_bug_gso_check(काष्ठा tg3_napi *tnapi, काष्ठा sk_buff *skb)
अणु
	/* Check अगर we will never have enough descriptors,
	 * as gso_segs can be more than current ring size
	 */
	वापस skb_shinfo(skb)->gso_segs < tnapi->tx_pending / 3;
पूर्ण

अटल netdev_tx_t tg3_start_xmit(काष्ठा sk_buff *, काष्ठा net_device *);

/* Use GSO to workaround all TSO packets that meet HW bug conditions
 * indicated in tg3_tx_frag_set()
 */
अटल पूर्णांक tg3_tso_bug(काष्ठा tg3 *tp, काष्ठा tg3_napi *tnapi,
		       काष्ठा netdev_queue *txq, काष्ठा sk_buff *skb)
अणु
	u32 frag_cnt_est = skb_shinfo(skb)->gso_segs * 3;
	काष्ठा sk_buff *segs, *seg, *next;

	/* Estimate the number of fragments in the worst हाल */
	अगर (unlikely(tg3_tx_avail(tnapi) <= frag_cnt_est)) अणु
		netअगर_tx_stop_queue(txq);

		/* netअगर_tx_stop_queue() must be करोne beक्रमe checking
		 * checking tx index in tg3_tx_avail() below, because in
		 * tg3_tx(), we update tx index beक्रमe checking क्रम
		 * netअगर_tx_queue_stopped().
		 */
		smp_mb();
		अगर (tg3_tx_avail(tnapi) <= frag_cnt_est)
			वापस NETDEV_TX_BUSY;

		netअगर_tx_wake_queue(txq);
	पूर्ण

	segs = skb_gso_segment(skb, tp->dev->features &
				    ~(NETIF_F_TSO | NETIF_F_TSO6));
	अगर (IS_ERR(segs) || !segs)
		जाओ tg3_tso_bug_end;

	skb_list_walk_safe(segs, seg, next) अणु
		skb_mark_not_on_list(seg);
		tg3_start_xmit(seg, tp->dev);
	पूर्ण

tg3_tso_bug_end:
	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

/* hard_start_xmit क्रम all devices */
अटल netdev_tx_t tg3_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	u32 len, entry, base_flags, mss, vlan = 0;
	u32 budget;
	पूर्णांक i = -1, would_hit_hwbug;
	dma_addr_t mapping;
	काष्ठा tg3_napi *tnapi;
	काष्ठा netdev_queue *txq;
	अचिन्हित पूर्णांक last;
	काष्ठा iphdr *iph = शून्य;
	काष्ठा tcphdr *tcph = शून्य;
	__sum16 tcp_csum = 0, ip_csum = 0;
	__be16 ip_tot_len = 0;

	txq = netdev_get_tx_queue(dev, skb_get_queue_mapping(skb));
	tnapi = &tp->napi[skb_get_queue_mapping(skb)];
	अगर (tg3_flag(tp, ENABLE_TSS))
		tnapi++;

	budget = tg3_tx_avail(tnapi);

	/* We are running in BH disabled context with netअगर_tx_lock
	 * and TX reclaim runs via tp->napi.poll inside of a software
	 * पूर्णांकerrupt.  Furthermore, IRQ processing runs lockless so we have
	 * no IRQ context deadlocks to worry about either.  Rejoice!
	 */
	अगर (unlikely(budget <= (skb_shinfo(skb)->nr_frags + 1))) अणु
		अगर (!netअगर_tx_queue_stopped(txq)) अणु
			netअगर_tx_stop_queue(txq);

			/* This is a hard error, log it. */
			netdev_err(dev,
				   "BUG! Tx Ring full when queue awake!\n");
		पूर्ण
		वापस NETDEV_TX_BUSY;
	पूर्ण

	entry = tnapi->tx_prod;
	base_flags = 0;

	mss = skb_shinfo(skb)->gso_size;
	अगर (mss) अणु
		u32 tcp_opt_len, hdr_len;

		अगर (skb_cow_head(skb, 0))
			जाओ drop;

		iph = ip_hdr(skb);
		tcp_opt_len = tcp_optlen(skb);

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb) - ETH_HLEN;

		/* HW/FW can not correctly segment packets that have been
		 * vlan encapsulated.
		 */
		अगर (skb->protocol == htons(ETH_P_8021Q) ||
		    skb->protocol == htons(ETH_P_8021AD)) अणु
			अगर (tg3_tso_bug_gso_check(tnapi, skb))
				वापस tg3_tso_bug(tp, tnapi, txq, skb);
			जाओ drop;
		पूर्ण

		अगर (!skb_is_gso_v6(skb)) अणु
			अगर (unlikely((ETH_HLEN + hdr_len) > 80) &&
			    tg3_flag(tp, TSO_BUG)) अणु
				अगर (tg3_tso_bug_gso_check(tnapi, skb))
					वापस tg3_tso_bug(tp, tnapi, txq, skb);
				जाओ drop;
			पूर्ण
			ip_csum = iph->check;
			ip_tot_len = iph->tot_len;
			iph->check = 0;
			iph->tot_len = htons(mss + hdr_len);
		पूर्ण

		base_flags |= (TXD_FLAG_CPU_PRE_DMA |
			       TXD_FLAG_CPU_POST_DMA);

		tcph = tcp_hdr(skb);
		tcp_csum = tcph->check;

		अगर (tg3_flag(tp, HW_TSO_1) ||
		    tg3_flag(tp, HW_TSO_2) ||
		    tg3_flag(tp, HW_TSO_3)) अणु
			tcph->check = 0;
			base_flags &= ~TXD_FLAG_TCPUDP_CSUM;
		पूर्ण अन्यथा अणु
			tcph->check = ~csum_tcpudp_magic(iph->saddr, iph->daddr,
							 0, IPPROTO_TCP, 0);
		पूर्ण

		अगर (tg3_flag(tp, HW_TSO_3)) अणु
			mss |= (hdr_len & 0xc) << 12;
			अगर (hdr_len & 0x10)
				base_flags |= 0x00000010;
			base_flags |= (hdr_len & 0x3e0) << 5;
		पूर्ण अन्यथा अगर (tg3_flag(tp, HW_TSO_2))
			mss |= hdr_len << 9;
		अन्यथा अगर (tg3_flag(tp, HW_TSO_1) ||
			 tg3_asic_rev(tp) == ASIC_REV_5705) अणु
			अगर (tcp_opt_len || iph->ihl > 5) अणु
				पूर्णांक tsflags;

				tsflags = (iph->ihl - 5) + (tcp_opt_len >> 2);
				mss |= (tsflags << 11);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tcp_opt_len || iph->ihl > 5) अणु
				पूर्णांक tsflags;

				tsflags = (iph->ihl - 5) + (tcp_opt_len >> 2);
				base_flags |= tsflags << 12;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		/* HW/FW can not correctly checksum packets that have been
		 * vlan encapsulated.
		 */
		अगर (skb->protocol == htons(ETH_P_8021Q) ||
		    skb->protocol == htons(ETH_P_8021AD)) अणु
			अगर (skb_checksum_help(skb))
				जाओ drop;
		पूर्ण अन्यथा  अणु
			base_flags |= TXD_FLAG_TCPUDP_CSUM;
		पूर्ण
	पूर्ण

	अगर (tg3_flag(tp, USE_JUMBO_BDFLAG) &&
	    !mss && skb->len > VLAN_ETH_FRAME_LEN)
		base_flags |= TXD_FLAG_JMB_PKT;

	अगर (skb_vlan_tag_present(skb)) अणु
		base_flags |= TXD_FLAG_VLAN;
		vlan = skb_vlan_tag_get(skb);
	पूर्ण

	अगर ((unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) &&
	    tg3_flag(tp, TX_TSTAMP_EN)) अणु
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
		base_flags |= TXD_FLAG_HWTSTAMP;
	पूर्ण

	len = skb_headlen(skb);

	mapping = pci_map_single(tp->pdev, skb->data, len, PCI_DMA_TODEVICE);
	अगर (pci_dma_mapping_error(tp->pdev, mapping))
		जाओ drop;


	tnapi->tx_buffers[entry].skb = skb;
	dma_unmap_addr_set(&tnapi->tx_buffers[entry], mapping, mapping);

	would_hit_hwbug = 0;

	अगर (tg3_flag(tp, 5701_DMA_BUG))
		would_hit_hwbug = 1;

	अगर (tg3_tx_frag_set(tnapi, &entry, &budget, mapping, len, base_flags |
			  ((skb_shinfo(skb)->nr_frags == 0) ? TXD_FLAG_END : 0),
			    mss, vlan)) अणु
		would_hit_hwbug = 1;
	पूर्ण अन्यथा अगर (skb_shinfo(skb)->nr_frags > 0) अणु
		u32 पंचांगp_mss = mss;

		अगर (!tg3_flag(tp, HW_TSO_1) &&
		    !tg3_flag(tp, HW_TSO_2) &&
		    !tg3_flag(tp, HW_TSO_3))
			पंचांगp_mss = 0;

		/* Now loop through additional data
		 * fragments, and queue them.
		 */
		last = skb_shinfo(skb)->nr_frags - 1;
		क्रम (i = 0; i <= last; i++) अणु
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			len = skb_frag_size(frag);
			mapping = skb_frag_dma_map(&tp->pdev->dev, frag, 0,
						   len, DMA_TO_DEVICE);

			tnapi->tx_buffers[entry].skb = शून्य;
			dma_unmap_addr_set(&tnapi->tx_buffers[entry], mapping,
					   mapping);
			अगर (dma_mapping_error(&tp->pdev->dev, mapping))
				जाओ dma_error;

			अगर (!budget ||
			    tg3_tx_frag_set(tnapi, &entry, &budget, mapping,
					    len, base_flags |
					    ((i == last) ? TXD_FLAG_END : 0),
					    पंचांगp_mss, vlan)) अणु
				would_hit_hwbug = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (would_hit_hwbug) अणु
		tg3_tx_skb_unmap(tnapi, tnapi->tx_prod, i);

		अगर (mss && tg3_tso_bug_gso_check(tnapi, skb)) अणु
			/* If it's a TSO packet, करो GSO instead of
			 * allocating and copying to a large linear SKB
			 */
			अगर (ip_tot_len) अणु
				iph->check = ip_csum;
				iph->tot_len = ip_tot_len;
			पूर्ण
			tcph->check = tcp_csum;
			वापस tg3_tso_bug(tp, tnapi, txq, skb);
		पूर्ण

		/* If the workaround fails due to memory/mapping
		 * failure, silently drop this packet.
		 */
		entry = tnapi->tx_prod;
		budget = tg3_tx_avail(tnapi);
		अगर (tigon3_dma_hwbug_workaround(tnapi, &skb, &entry, &budget,
						base_flags, mss, vlan))
			जाओ drop_noमुक्त;
	पूर्ण

	skb_tx_बारtamp(skb);
	netdev_tx_sent_queue(txq, skb->len);

	/* Sync BD data beक्रमe updating mailbox */
	wmb();

	tnapi->tx_prod = entry;
	अगर (unlikely(tg3_tx_avail(tnapi) <= (MAX_SKB_FRAGS + 1))) अणु
		netअगर_tx_stop_queue(txq);

		/* netअगर_tx_stop_queue() must be करोne beक्रमe checking
		 * checking tx index in tg3_tx_avail() below, because in
		 * tg3_tx(), we update tx index beक्रमe checking क्रम
		 * netअगर_tx_queue_stopped().
		 */
		smp_mb();
		अगर (tg3_tx_avail(tnapi) > TG3_TX_WAKEUP_THRESH(tnapi))
			netअगर_tx_wake_queue(txq);
	पूर्ण

	अगर (!netdev_xmit_more() || netअगर_xmit_stopped(txq)) अणु
		/* Packets are पढ़ोy, update Tx producer idx on card. */
		tw32_tx_mbox(tnapi->prodmbox, entry);
	पूर्ण

	वापस NETDEV_TX_OK;

dma_error:
	tg3_tx_skb_unmap(tnapi, tnapi->tx_prod, --i);
	tnapi->tx_buffers[tnapi->tx_prod].skb = शून्य;
drop:
	dev_kमुक्त_skb_any(skb);
drop_noमुक्त:
	tp->tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम tg3_mac_loopback(काष्ठा tg3 *tp, bool enable)
अणु
	अगर (enable) अणु
		tp->mac_mode &= ~(MAC_MODE_HALF_DUPLEX |
				  MAC_MODE_PORT_MODE_MASK);

		tp->mac_mode |= MAC_MODE_PORT_INT_LPBACK;

		अगर (!tg3_flag(tp, 5705_PLUS))
			tp->mac_mode |= MAC_MODE_LINK_POLARITY;

		अगर (tp->phy_flags & TG3_PHYFLG_10_100_ONLY)
			tp->mac_mode |= MAC_MODE_PORT_MODE_MII;
		अन्यथा
			tp->mac_mode |= MAC_MODE_PORT_MODE_GMII;
	पूर्ण अन्यथा अणु
		tp->mac_mode &= ~MAC_MODE_PORT_INT_LPBACK;

		अगर (tg3_flag(tp, 5705_PLUS) ||
		    (tp->phy_flags & TG3_PHYFLG_PHY_SERDES) ||
		    tg3_asic_rev(tp) == ASIC_REV_5700)
			tp->mac_mode &= ~MAC_MODE_LINK_POLARITY;
	पूर्ण

	tw32(MAC_MODE, tp->mac_mode);
	udelay(40);
पूर्ण

अटल पूर्णांक tg3_phy_lpbk_set(काष्ठा tg3 *tp, u32 speed, bool extlpbk)
अणु
	u32 val, bmcr, mac_mode, ptest = 0;

	tg3_phy_toggle_apd(tp, false);
	tg3_phy_toggle_स्वतःmdix(tp, false);

	अगर (extlpbk && tg3_phy_set_extloopbk(tp))
		वापस -EIO;

	bmcr = BMCR_FULLDPLX;
	चयन (speed) अणु
	हाल SPEED_10:
		अवरोध;
	हाल SPEED_100:
		bmcr |= BMCR_SPEED100;
		अवरोध;
	हाल SPEED_1000:
	शेष:
		अगर (tp->phy_flags & TG3_PHYFLG_IS_FET) अणु
			speed = SPEED_100;
			bmcr |= BMCR_SPEED100;
		पूर्ण अन्यथा अणु
			speed = SPEED_1000;
			bmcr |= BMCR_SPEED1000;
		पूर्ण
	पूर्ण

	अगर (extlpbk) अणु
		अगर (!(tp->phy_flags & TG3_PHYFLG_IS_FET)) अणु
			tg3_पढ़ोphy(tp, MII_CTRL1000, &val);
			val |= CTL1000_AS_MASTER |
			       CTL1000_ENABLE_MASTER;
			tg3_ग_लिखोphy(tp, MII_CTRL1000, val);
		पूर्ण अन्यथा अणु
			ptest = MII_TG3_FET_PTEST_TRIM_SEL |
				MII_TG3_FET_PTEST_TRIM_2;
			tg3_ग_लिखोphy(tp, MII_TG3_FET_PTEST, ptest);
		पूर्ण
	पूर्ण अन्यथा
		bmcr |= BMCR_LOOPBACK;

	tg3_ग_लिखोphy(tp, MII_BMCR, bmcr);

	/* The ग_लिखो needs to be flushed क्रम the FETs */
	अगर (tp->phy_flags & TG3_PHYFLG_IS_FET)
		tg3_पढ़ोphy(tp, MII_BMCR, &bmcr);

	udelay(40);

	अगर ((tp->phy_flags & TG3_PHYFLG_IS_FET) &&
	    tg3_asic_rev(tp) == ASIC_REV_5785) अणु
		tg3_ग_लिखोphy(tp, MII_TG3_FET_PTEST, ptest |
			     MII_TG3_FET_PTEST_FRC_TX_LINK |
			     MII_TG3_FET_PTEST_FRC_TX_LOCK);

		/* The ग_लिखो needs to be flushed क्रम the AC131 */
		tg3_पढ़ोphy(tp, MII_TG3_FET_PTEST, &val);
	पूर्ण

	/* Reset to prevent losing 1st rx packet पूर्णांकermittently */
	अगर ((tp->phy_flags & TG3_PHYFLG_MII_SERDES) &&
	    tg3_flag(tp, 5780_CLASS)) अणु
		tw32_f(MAC_RX_MODE, RX_MODE_RESET);
		udelay(10);
		tw32_f(MAC_RX_MODE, tp->rx_mode);
	पूर्ण

	mac_mode = tp->mac_mode &
		   ~(MAC_MODE_PORT_MODE_MASK | MAC_MODE_HALF_DUPLEX);
	अगर (speed == SPEED_1000)
		mac_mode |= MAC_MODE_PORT_MODE_GMII;
	अन्यथा
		mac_mode |= MAC_MODE_PORT_MODE_MII;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5700) अणु
		u32 masked_phy_id = tp->phy_id & TG3_PHY_ID_MASK;

		अगर (masked_phy_id == TG3_PHY_ID_BCM5401)
			mac_mode &= ~MAC_MODE_LINK_POLARITY;
		अन्यथा अगर (masked_phy_id == TG3_PHY_ID_BCM5411)
			mac_mode |= MAC_MODE_LINK_POLARITY;

		tg3_ग_लिखोphy(tp, MII_TG3_EXT_CTRL,
			     MII_TG3_EXT_CTRL_LNK3_LED_MODE);
	पूर्ण

	tw32(MAC_MODE, mac_mode);
	udelay(40);

	वापस 0;
पूर्ण

अटल व्योम tg3_set_loopback(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (features & NETIF_F_LOOPBACK) अणु
		अगर (tp->mac_mode & MAC_MODE_PORT_INT_LPBACK)
			वापस;

		spin_lock_bh(&tp->lock);
		tg3_mac_loopback(tp, true);
		netअगर_carrier_on(tp->dev);
		spin_unlock_bh(&tp->lock);
		netdev_info(dev, "Internal MAC loopback mode enabled.\n");
	पूर्ण अन्यथा अणु
		अगर (!(tp->mac_mode & MAC_MODE_PORT_INT_LPBACK))
			वापस;

		spin_lock_bh(&tp->lock);
		tg3_mac_loopback(tp, false);
		/* Force link status check */
		tg3_setup_phy(tp, true);
		spin_unlock_bh(&tp->lock);
		netdev_info(dev, "Internal MAC loopback mode disabled.\n");
	पूर्ण
पूर्ण

अटल netdev_features_t tg3_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (dev->mtu > ETH_DATA_LEN && tg3_flag(tp, 5780_CLASS))
		features &= ~NETIF_F_ALL_TSO;

	वापस features;
पूर्ण

अटल पूर्णांक tg3_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	netdev_features_t changed = dev->features ^ features;

	अगर ((changed & NETIF_F_LOOPBACK) && netअगर_running(dev))
		tg3_set_loopback(dev, features);

	वापस 0;
पूर्ण

अटल व्योम tg3_rx_prodring_मुक्त(काष्ठा tg3 *tp,
				 काष्ठा tg3_rx_prodring_set *tpr)
अणु
	पूर्णांक i;

	अगर (tpr != &tp->napi[0].prodring) अणु
		क्रम (i = tpr->rx_std_cons_idx; i != tpr->rx_std_prod_idx;
		     i = (i + 1) & tp->rx_std_ring_mask)
			tg3_rx_data_मुक्त(tp, &tpr->rx_std_buffers[i],
					tp->rx_pkt_map_sz);

		अगर (tg3_flag(tp, JUMBO_CAPABLE)) अणु
			क्रम (i = tpr->rx_jmb_cons_idx;
			     i != tpr->rx_jmb_prod_idx;
			     i = (i + 1) & tp->rx_jmb_ring_mask) अणु
				tg3_rx_data_मुक्त(tp, &tpr->rx_jmb_buffers[i],
						TG3_RX_JMB_MAP_SZ);
			पूर्ण
		पूर्ण

		वापस;
	पूर्ण

	क्रम (i = 0; i <= tp->rx_std_ring_mask; i++)
		tg3_rx_data_मुक्त(tp, &tpr->rx_std_buffers[i],
				tp->rx_pkt_map_sz);

	अगर (tg3_flag(tp, JUMBO_CAPABLE) && !tg3_flag(tp, 5780_CLASS)) अणु
		क्रम (i = 0; i <= tp->rx_jmb_ring_mask; i++)
			tg3_rx_data_मुक्त(tp, &tpr->rx_jmb_buffers[i],
					TG3_RX_JMB_MAP_SZ);
	पूर्ण
पूर्ण

/* Initialize rx rings क्रम packet processing.
 *
 * The chip has been shut करोwn and the driver detached from
 * the networking, so no पूर्णांकerrupts or new tx packets will
 * end up in the driver.  tp->अणुtx,पूर्णlock are held and thus
 * we may not sleep.
 */
अटल पूर्णांक tg3_rx_prodring_alloc(काष्ठा tg3 *tp,
				 काष्ठा tg3_rx_prodring_set *tpr)
अणु
	u32 i, rx_pkt_dma_sz;

	tpr->rx_std_cons_idx = 0;
	tpr->rx_std_prod_idx = 0;
	tpr->rx_jmb_cons_idx = 0;
	tpr->rx_jmb_prod_idx = 0;

	अगर (tpr != &tp->napi[0].prodring) अणु
		स_रखो(&tpr->rx_std_buffers[0], 0,
		       TG3_RX_STD_BUFF_RING_SIZE(tp));
		अगर (tpr->rx_jmb_buffers)
			स_रखो(&tpr->rx_jmb_buffers[0], 0,
			       TG3_RX_JMB_BUFF_RING_SIZE(tp));
		जाओ करोne;
	पूर्ण

	/* Zero out all descriptors. */
	स_रखो(tpr->rx_std, 0, TG3_RX_STD_RING_BYTES(tp));

	rx_pkt_dma_sz = TG3_RX_STD_DMA_SZ;
	अगर (tg3_flag(tp, 5780_CLASS) &&
	    tp->dev->mtu > ETH_DATA_LEN)
		rx_pkt_dma_sz = TG3_RX_JMB_DMA_SZ;
	tp->rx_pkt_map_sz = TG3_RX_DMA_TO_MAP_SZ(rx_pkt_dma_sz);

	/* Initialize invariants of the rings, we only set this
	 * stuff once.  This works because the card करोes not
	 * ग_लिखो पूर्णांकo the rx buffer posting rings.
	 */
	क्रम (i = 0; i <= tp->rx_std_ring_mask; i++) अणु
		काष्ठा tg3_rx_buffer_desc *rxd;

		rxd = &tpr->rx_std[i];
		rxd->idx_len = rx_pkt_dma_sz << RXD_LEN_SHIFT;
		rxd->type_flags = (RXD_FLAG_END << RXD_FLAGS_SHIFT);
		rxd->opaque = (RXD_OPAQUE_RING_STD |
			       (i << RXD_OPAQUE_INDEX_SHIFT));
	पूर्ण

	/* Now allocate fresh SKBs क्रम each rx ring. */
	क्रम (i = 0; i < tp->rx_pending; i++) अणु
		अचिन्हित पूर्णांक frag_size;

		अगर (tg3_alloc_rx_data(tp, tpr, RXD_OPAQUE_RING_STD, i,
				      &frag_size) < 0) अणु
			netdev_warn(tp->dev,
				    "Using a smaller RX standard ring. Only "
				    "%d out of %d buffers were allocated "
				    "successfully\n", i, tp->rx_pending);
			अगर (i == 0)
				जाओ initfail;
			tp->rx_pending = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tg3_flag(tp, JUMBO_CAPABLE) || tg3_flag(tp, 5780_CLASS))
		जाओ करोne;

	स_रखो(tpr->rx_jmb, 0, TG3_RX_JMB_RING_BYTES(tp));

	अगर (!tg3_flag(tp, JUMBO_RING_ENABLE))
		जाओ करोne;

	क्रम (i = 0; i <= tp->rx_jmb_ring_mask; i++) अणु
		काष्ठा tg3_rx_buffer_desc *rxd;

		rxd = &tpr->rx_jmb[i].std;
		rxd->idx_len = TG3_RX_JMB_DMA_SZ << RXD_LEN_SHIFT;
		rxd->type_flags = (RXD_FLAG_END << RXD_FLAGS_SHIFT) |
				  RXD_FLAG_JUMBO;
		rxd->opaque = (RXD_OPAQUE_RING_JUMBO |
		       (i << RXD_OPAQUE_INDEX_SHIFT));
	पूर्ण

	क्रम (i = 0; i < tp->rx_jumbo_pending; i++) अणु
		अचिन्हित पूर्णांक frag_size;

		अगर (tg3_alloc_rx_data(tp, tpr, RXD_OPAQUE_RING_JUMBO, i,
				      &frag_size) < 0) अणु
			netdev_warn(tp->dev,
				    "Using a smaller RX jumbo ring. Only %d "
				    "out of %d buffers were allocated "
				    "successfully\n", i, tp->rx_jumbo_pending);
			अगर (i == 0)
				जाओ initfail;
			tp->rx_jumbo_pending = i;
			अवरोध;
		पूर्ण
	पूर्ण

करोne:
	वापस 0;

initfail:
	tg3_rx_prodring_मुक्त(tp, tpr);
	वापस -ENOMEM;
पूर्ण

अटल व्योम tg3_rx_prodring_fini(काष्ठा tg3 *tp,
				 काष्ठा tg3_rx_prodring_set *tpr)
अणु
	kमुक्त(tpr->rx_std_buffers);
	tpr->rx_std_buffers = शून्य;
	kमुक्त(tpr->rx_jmb_buffers);
	tpr->rx_jmb_buffers = शून्य;
	अगर (tpr->rx_std) अणु
		dma_मुक्त_coherent(&tp->pdev->dev, TG3_RX_STD_RING_BYTES(tp),
				  tpr->rx_std, tpr->rx_std_mapping);
		tpr->rx_std = शून्य;
	पूर्ण
	अगर (tpr->rx_jmb) अणु
		dma_मुक्त_coherent(&tp->pdev->dev, TG3_RX_JMB_RING_BYTES(tp),
				  tpr->rx_jmb, tpr->rx_jmb_mapping);
		tpr->rx_jmb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_rx_prodring_init(काष्ठा tg3 *tp,
				काष्ठा tg3_rx_prodring_set *tpr)
अणु
	tpr->rx_std_buffers = kzalloc(TG3_RX_STD_BUFF_RING_SIZE(tp),
				      GFP_KERNEL);
	अगर (!tpr->rx_std_buffers)
		वापस -ENOMEM;

	tpr->rx_std = dma_alloc_coherent(&tp->pdev->dev,
					 TG3_RX_STD_RING_BYTES(tp),
					 &tpr->rx_std_mapping,
					 GFP_KERNEL);
	अगर (!tpr->rx_std)
		जाओ err_out;

	अगर (tg3_flag(tp, JUMBO_CAPABLE) && !tg3_flag(tp, 5780_CLASS)) अणु
		tpr->rx_jmb_buffers = kzalloc(TG3_RX_JMB_BUFF_RING_SIZE(tp),
					      GFP_KERNEL);
		अगर (!tpr->rx_jmb_buffers)
			जाओ err_out;

		tpr->rx_jmb = dma_alloc_coherent(&tp->pdev->dev,
						 TG3_RX_JMB_RING_BYTES(tp),
						 &tpr->rx_jmb_mapping,
						 GFP_KERNEL);
		अगर (!tpr->rx_jmb)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	tg3_rx_prodring_fini(tp, tpr);
	वापस -ENOMEM;
पूर्ण

/* Free up pending packets in all rx/tx rings.
 *
 * The chip has been shut करोwn and the driver detached from
 * the networking, so no पूर्णांकerrupts or new tx packets will
 * end up in the driver.  tp->अणुtx,पूर्णlock is not held and we are not
 * in an पूर्णांकerrupt context and thus may sleep.
 */
अटल व्योम tg3_मुक्त_rings(काष्ठा tg3 *tp)
अणु
	पूर्णांक i, j;

	क्रम (j = 0; j < tp->irq_cnt; j++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[j];

		tg3_rx_prodring_मुक्त(tp, &tnapi->prodring);

		अगर (!tnapi->tx_buffers)
			जारी;

		क्रम (i = 0; i < TG3_TX_RING_SIZE; i++) अणु
			काष्ठा sk_buff *skb = tnapi->tx_buffers[i].skb;

			अगर (!skb)
				जारी;

			tg3_tx_skb_unmap(tnapi, i,
					 skb_shinfo(skb)->nr_frags - 1);

			dev_consume_skb_any(skb);
		पूर्ण
		netdev_tx_reset_queue(netdev_get_tx_queue(tp->dev, j));
	पूर्ण
पूर्ण

/* Initialize tx/rx rings क्रम packet processing.
 *
 * The chip has been shut करोwn and the driver detached from
 * the networking, so no पूर्णांकerrupts or new tx packets will
 * end up in the driver.  tp->अणुtx,पूर्णlock are held and thus
 * we may not sleep.
 */
अटल पूर्णांक tg3_init_rings(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	/* Free up all the SKBs. */
	tg3_मुक्त_rings(tp);

	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		tnapi->last_tag = 0;
		tnapi->last_irq_tag = 0;
		tnapi->hw_status->status = 0;
		tnapi->hw_status->status_tag = 0;
		स_रखो(tnapi->hw_status, 0, TG3_HW_STATUS_SIZE);

		tnapi->tx_prod = 0;
		tnapi->tx_cons = 0;
		अगर (tnapi->tx_ring)
			स_रखो(tnapi->tx_ring, 0, TG3_TX_RING_BYTES);

		tnapi->rx_rcb_ptr = 0;
		अगर (tnapi->rx_rcb)
			स_रखो(tnapi->rx_rcb, 0, TG3_RX_RCB_RING_BYTES(tp));

		अगर (tnapi->prodring.rx_std &&
		    tg3_rx_prodring_alloc(tp, &tnapi->prodring)) अणु
			tg3_मुक्त_rings(tp);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tg3_mem_tx_release(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tp->irq_max; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		अगर (tnapi->tx_ring) अणु
			dma_मुक्त_coherent(&tp->pdev->dev, TG3_TX_RING_BYTES,
				tnapi->tx_ring, tnapi->tx_desc_mapping);
			tnapi->tx_ring = शून्य;
		पूर्ण

		kमुक्त(tnapi->tx_buffers);
		tnapi->tx_buffers = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_mem_tx_acquire(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	काष्ठा tg3_napi *tnapi = &tp->napi[0];

	/* If multivector TSS is enabled, vector 0 करोes not handle
	 * tx पूर्णांकerrupts.  Don't allocate any resources क्रम it.
	 */
	अगर (tg3_flag(tp, ENABLE_TSS))
		tnapi++;

	क्रम (i = 0; i < tp->txq_cnt; i++, tnapi++) अणु
		tnapi->tx_buffers = kसुस्मृति(TG3_TX_RING_SIZE,
					    माप(काष्ठा tg3_tx_ring_info),
					    GFP_KERNEL);
		अगर (!tnapi->tx_buffers)
			जाओ err_out;

		tnapi->tx_ring = dma_alloc_coherent(&tp->pdev->dev,
						    TG3_TX_RING_BYTES,
						    &tnapi->tx_desc_mapping,
						    GFP_KERNEL);
		अगर (!tnapi->tx_ring)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	tg3_mem_tx_release(tp);
	वापस -ENOMEM;
पूर्ण

अटल व्योम tg3_mem_rx_release(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tp->irq_max; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		tg3_rx_prodring_fini(tp, &tnapi->prodring);

		अगर (!tnapi->rx_rcb)
			जारी;

		dma_मुक्त_coherent(&tp->pdev->dev,
				  TG3_RX_RCB_RING_BYTES(tp),
				  tnapi->rx_rcb,
				  tnapi->rx_rcb_mapping);
		tnapi->rx_rcb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_mem_rx_acquire(काष्ठा tg3 *tp)
अणु
	अचिन्हित पूर्णांक i, limit;

	limit = tp->rxq_cnt;

	/* If RSS is enabled, we need a (dummy) producer ring
	 * set on vector zero.  This is the true hw prodring.
	 */
	अगर (tg3_flag(tp, ENABLE_RSS))
		limit++;

	क्रम (i = 0; i < limit; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		अगर (tg3_rx_prodring_init(tp, &tnapi->prodring))
			जाओ err_out;

		/* If multivector RSS is enabled, vector 0
		 * करोes not handle rx or tx पूर्णांकerrupts.
		 * Don't allocate any resources क्रम it.
		 */
		अगर (!i && tg3_flag(tp, ENABLE_RSS))
			जारी;

		tnapi->rx_rcb = dma_alloc_coherent(&tp->pdev->dev,
						   TG3_RX_RCB_RING_BYTES(tp),
						   &tnapi->rx_rcb_mapping,
						   GFP_KERNEL);
		अगर (!tnapi->rx_rcb)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	tg3_mem_rx_release(tp);
	वापस -ENOMEM;
पूर्ण

/*
 * Must not be invoked with पूर्णांकerrupt sources disabled and
 * the hardware shutकरोwn करोwn.
 */
अटल व्योम tg3_मुक्त_consistent(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		अगर (tnapi->hw_status) अणु
			dma_मुक्त_coherent(&tp->pdev->dev, TG3_HW_STATUS_SIZE,
					  tnapi->hw_status,
					  tnapi->status_mapping);
			tnapi->hw_status = शून्य;
		पूर्ण
	पूर्ण

	tg3_mem_rx_release(tp);
	tg3_mem_tx_release(tp);

	/* tp->hw_stats can be referenced safely:
	 *     1. under rtnl_lock
	 *     2. or under tp->lock अगर TG3_FLAG_INIT_COMPLETE is set.
	 */
	अगर (tp->hw_stats) अणु
		dma_मुक्त_coherent(&tp->pdev->dev, माप(काष्ठा tg3_hw_stats),
				  tp->hw_stats, tp->stats_mapping);
		tp->hw_stats = शून्य;
	पूर्ण
पूर्ण

/*
 * Must not be invoked with पूर्णांकerrupt sources disabled and
 * the hardware shutकरोwn करोwn.  Can sleep.
 */
अटल पूर्णांक tg3_alloc_consistent(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	tp->hw_stats = dma_alloc_coherent(&tp->pdev->dev,
					  माप(काष्ठा tg3_hw_stats),
					  &tp->stats_mapping, GFP_KERNEL);
	अगर (!tp->hw_stats)
		जाओ err_out;

	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];
		काष्ठा tg3_hw_status *sblk;

		tnapi->hw_status = dma_alloc_coherent(&tp->pdev->dev,
						      TG3_HW_STATUS_SIZE,
						      &tnapi->status_mapping,
						      GFP_KERNEL);
		अगर (!tnapi->hw_status)
			जाओ err_out;

		sblk = tnapi->hw_status;

		अगर (tg3_flag(tp, ENABLE_RSS)) अणु
			u16 *prodptr = शून्य;

			/*
			 * When RSS is enabled, the status block क्रमmat changes
			 * slightly.  The "rx_jumbo_consumer", "reserved",
			 * and "rx_mini_consumer" members get mapped to the
			 * other three rx वापस ring producer indexes.
			 */
			चयन (i) अणु
			हाल 1:
				prodptr = &sblk->idx[0].rx_producer;
				अवरोध;
			हाल 2:
				prodptr = &sblk->rx_jumbo_consumer;
				अवरोध;
			हाल 3:
				prodptr = &sblk->reserved;
				अवरोध;
			हाल 4:
				prodptr = &sblk->rx_mini_consumer;
				अवरोध;
			पूर्ण
			tnapi->rx_rcb_prod_idx = prodptr;
		पूर्ण अन्यथा अणु
			tnapi->rx_rcb_prod_idx = &sblk->idx[0].rx_producer;
		पूर्ण
	पूर्ण

	अगर (tg3_mem_tx_acquire(tp) || tg3_mem_rx_acquire(tp))
		जाओ err_out;

	वापस 0;

err_out:
	tg3_मुक्त_consistent(tp);
	वापस -ENOMEM;
पूर्ण

#घोषणा MAX_WAIT_CNT 1000

/* To stop a block, clear the enable bit and poll till it
 * clears.  tp->lock is held.
 */
अटल पूर्णांक tg3_stop_block(काष्ठा tg3 *tp, अचिन्हित दीर्घ ofs, u32 enable_bit, bool silent)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;

	अगर (tg3_flag(tp, 5705_PLUS)) अणु
		चयन (ofs) अणु
		हाल RCVLSC_MODE:
		हाल DMAC_MODE:
		हाल MBFREE_MODE:
		हाल BUFMGR_MODE:
		हाल MEMARB_MODE:
			/* We can't enable/disable these bits of the
			 * 5705/5750, just say success.
			 */
			वापस 0;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	val = tr32(ofs);
	val &= ~enable_bit;
	tw32_f(ofs, val);

	क्रम (i = 0; i < MAX_WAIT_CNT; i++) अणु
		अगर (pci_channel_offline(tp->pdev)) अणु
			dev_err(&tp->pdev->dev,
				"tg3_stop_block device offline, "
				"ofs=%lx enable_bit=%x\n",
				ofs, enable_bit);
			वापस -ENODEV;
		पूर्ण

		udelay(100);
		val = tr32(ofs);
		अगर ((val & enable_bit) == 0)
			अवरोध;
	पूर्ण

	अगर (i == MAX_WAIT_CNT && !silent) अणु
		dev_err(&tp->pdev->dev,
			"tg3_stop_block timed out, ofs=%lx enable_bit=%x\n",
			ofs, enable_bit);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_पात_hw(काष्ठा tg3 *tp, bool silent)
अणु
	पूर्णांक i, err;

	tg3_disable_पूर्णांकs(tp);

	अगर (pci_channel_offline(tp->pdev)) अणु
		tp->rx_mode &= ~(RX_MODE_ENABLE | TX_MODE_ENABLE);
		tp->mac_mode &= ~MAC_MODE_TDE_ENABLE;
		err = -ENODEV;
		जाओ err_no_dev;
	पूर्ण

	tp->rx_mode &= ~RX_MODE_ENABLE;
	tw32_f(MAC_RX_MODE, tp->rx_mode);
	udelay(10);

	err  = tg3_stop_block(tp, RCVBDI_MODE, RCVBDI_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, RCVLPC_MODE, RCVLPC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, RCVLSC_MODE, RCVLSC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, RCVDBDI_MODE, RCVDBDI_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, RCVDCC_MODE, RCVDCC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, RCVCC_MODE, RCVCC_MODE_ENABLE, silent);

	err |= tg3_stop_block(tp, SNDBDS_MODE, SNDBDS_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, SNDBDI_MODE, SNDBDI_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, SNDDATAI_MODE, SNDDATAI_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, RDMAC_MODE, RDMAC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, SNDDATAC_MODE, SNDDATAC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, DMAC_MODE, DMAC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, SNDBDC_MODE, SNDBDC_MODE_ENABLE, silent);

	tp->mac_mode &= ~MAC_MODE_TDE_ENABLE;
	tw32_f(MAC_MODE, tp->mac_mode);
	udelay(40);

	tp->tx_mode &= ~TX_MODE_ENABLE;
	tw32_f(MAC_TX_MODE, tp->tx_mode);

	क्रम (i = 0; i < MAX_WAIT_CNT; i++) अणु
		udelay(100);
		अगर (!(tr32(MAC_TX_MODE) & TX_MODE_ENABLE))
			अवरोध;
	पूर्ण
	अगर (i >= MAX_WAIT_CNT) अणु
		dev_err(&tp->pdev->dev,
			"%s timed out, TX_MODE_ENABLE will not clear "
			"MAC_TX_MODE=%08x\n", __func__, tr32(MAC_TX_MODE));
		err |= -ENODEV;
	पूर्ण

	err |= tg3_stop_block(tp, HOSTCC_MODE, HOSTCC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, WDMAC_MODE, WDMAC_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, MBFREE_MODE, MBFREE_MODE_ENABLE, silent);

	tw32(FTQ_RESET, 0xffffffff);
	tw32(FTQ_RESET, 0x00000000);

	err |= tg3_stop_block(tp, BUFMGR_MODE, BUFMGR_MODE_ENABLE, silent);
	err |= tg3_stop_block(tp, MEMARB_MODE, MEMARB_MODE_ENABLE, silent);

err_no_dev:
	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];
		अगर (tnapi->hw_status)
			स_रखो(tnapi->hw_status, 0, TG3_HW_STATUS_SIZE);
	पूर्ण

	वापस err;
पूर्ण

/* Save PCI command रेजिस्टर beक्रमe chip reset */
अटल व्योम tg3_save_pci_state(काष्ठा tg3 *tp)
अणु
	pci_पढ़ो_config_word(tp->pdev, PCI_COMMAND, &tp->pci_cmd);
पूर्ण

/* Restore PCI state after chip reset */
अटल व्योम tg3_restore_pci_state(काष्ठा tg3 *tp)
अणु
	u32 val;

	/* Re-enable indirect रेजिस्टर accesses. */
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MISC_HOST_CTRL,
			       tp->misc_host_ctrl);

	/* Set MAX PCI retry to zero. */
	val = (PCISTATE_ROM_ENABLE | PCISTATE_ROM_RETRY_ENABLE);
	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5704_A0 &&
	    tg3_flag(tp, PCIX_MODE))
		val |= PCISTATE_RETRY_SAME_DMA;
	/* Allow पढ़ोs and ग_लिखोs to the APE रेजिस्टर and memory space. */
	अगर (tg3_flag(tp, ENABLE_APE))
		val |= PCISTATE_ALLOW_APE_CTLSPC_WR |
		       PCISTATE_ALLOW_APE_SHMEM_WR |
		       PCISTATE_ALLOW_APE_PSPACE_WR;
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_PCISTATE, val);

	pci_ग_लिखो_config_word(tp->pdev, PCI_COMMAND, tp->pci_cmd);

	अगर (!tg3_flag(tp, PCI_EXPRESS)) अणु
		pci_ग_लिखो_config_byte(tp->pdev, PCI_CACHE_LINE_SIZE,
				      tp->pci_cacheline_sz);
		pci_ग_लिखो_config_byte(tp->pdev, PCI_LATENCY_TIMER,
				      tp->pci_lat_समयr);
	पूर्ण

	/* Make sure PCI-X relaxed ordering bit is clear. */
	अगर (tg3_flag(tp, PCIX_MODE)) अणु
		u16 pcix_cmd;

		pci_पढ़ो_config_word(tp->pdev, tp->pcix_cap + PCI_X_CMD,
				     &pcix_cmd);
		pcix_cmd &= ~PCI_X_CMD_ERO;
		pci_ग_लिखो_config_word(tp->pdev, tp->pcix_cap + PCI_X_CMD,
				      pcix_cmd);
	पूर्ण

	अगर (tg3_flag(tp, 5780_CLASS)) अणु

		/* Chip reset on 5780 will reset MSI enable bit,
		 * so need to restore it.
		 */
		अगर (tg3_flag(tp, USING_MSI)) अणु
			u16 ctrl;

			pci_पढ़ो_config_word(tp->pdev,
					     tp->msi_cap + PCI_MSI_FLAGS,
					     &ctrl);
			pci_ग_लिखो_config_word(tp->pdev,
					      tp->msi_cap + PCI_MSI_FLAGS,
					      ctrl | PCI_MSI_FLAGS_ENABLE);
			val = tr32(MSGINT_MODE);
			tw32(MSGINT_MODE, val | MSGINT_MODE_ENABLE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tg3_override_clk(काष्ठा tg3 *tp)
अणु
	u32 val;

	चयन (tg3_asic_rev(tp)) अणु
	हाल ASIC_REV_5717:
		val = tr32(TG3_CPMU_CLCK_ORIDE_ENABLE);
		tw32(TG3_CPMU_CLCK_ORIDE_ENABLE, val |
		     TG3_CPMU_MAC_ORIDE_ENABLE);
		अवरोध;

	हाल ASIC_REV_5719:
	हाल ASIC_REV_5720:
		tw32(TG3_CPMU_CLCK_ORIDE, CPMU_CLCK_ORIDE_MAC_ORIDE_EN);
		अवरोध;

	शेष:
		वापस;
	पूर्ण
पूर्ण

अटल व्योम tg3_restore_clk(काष्ठा tg3 *tp)
अणु
	u32 val;

	चयन (tg3_asic_rev(tp)) अणु
	हाल ASIC_REV_5717:
		val = tr32(TG3_CPMU_CLCK_ORIDE_ENABLE);
		tw32(TG3_CPMU_CLCK_ORIDE_ENABLE,
		     val & ~TG3_CPMU_MAC_ORIDE_ENABLE);
		अवरोध;

	हाल ASIC_REV_5719:
	हाल ASIC_REV_5720:
		val = tr32(TG3_CPMU_CLCK_ORIDE);
		tw32(TG3_CPMU_CLCK_ORIDE, val & ~CPMU_CLCK_ORIDE_MAC_ORIDE_EN);
		अवरोध;

	शेष:
		वापस;
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_chip_reset(काष्ठा tg3 *tp)
	__releases(tp->lock)
	__acquires(tp->lock)
अणु
	u32 val;
	व्योम (*ग_लिखो_op)(काष्ठा tg3 *, u32, u32);
	पूर्णांक i, err;

	अगर (!pci_device_is_present(tp->pdev))
		वापस -ENODEV;

	tg3_nvram_lock(tp);

	tg3_ape_lock(tp, TG3_APE_LOCK_GRC);

	/* No matching tg3_nvram_unlock() after this because
	 * chip reset below will unकरो the nvram lock.
	 */
	tp->nvram_lock_cnt = 0;

	/* GRC_MISC_CFG core घड़ी reset will clear the memory
	 * enable bit in PCI रेजिस्टर 4 and the MSI enable bit
	 * on some chips, so we save relevant रेजिस्टरs here.
	 */
	tg3_save_pci_state(tp);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5752 ||
	    tg3_flag(tp, 5755_PLUS))
		tw32(GRC_FASTBOOT_PC, 0);

	/*
	 * We must aव्योम the पढ़ोl() that normally takes place.
	 * It locks machines, causes machine checks, and other
	 * fun things.  So, temporarily disable the 5701
	 * hardware workaround, जबतक we करो the reset.
	 */
	ग_लिखो_op = tp->ग_लिखो32;
	अगर (ग_लिखो_op == tg3_ग_लिखो_flush_reg32)
		tp->ग_लिखो32 = tg3_ग_लिखो32;

	/* Prevent the irq handler from पढ़ोing or writing PCI रेजिस्टरs
	 * during chip reset when the memory enable bit in the PCI command
	 * रेजिस्टर may be cleared.  The chip करोes not generate पूर्णांकerrupt
	 * at this समय, but the irq handler may still be called due to irq
	 * sharing or irqpoll.
	 */
	tg3_flag_set(tp, CHIP_RESETTING);
	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];
		अगर (tnapi->hw_status) अणु
			tnapi->hw_status->status = 0;
			tnapi->hw_status->status_tag = 0;
		पूर्ण
		tnapi->last_tag = 0;
		tnapi->last_irq_tag = 0;
	पूर्ण
	smp_mb();

	tg3_full_unlock(tp);

	क्रम (i = 0; i < tp->irq_cnt; i++)
		synchronize_irq(tp->napi[i].irq_vec);

	tg3_full_lock(tp, 0);

	अगर (tg3_asic_rev(tp) == ASIC_REV_57780) अणु
		val = tr32(TG3_PCIE_LNKCTL) & ~TG3_PCIE_LNKCTL_L1_PLL_PD_EN;
		tw32(TG3_PCIE_LNKCTL, val | TG3_PCIE_LNKCTL_L1_PLL_PD_DIS);
	पूर्ण

	/* करो the reset */
	val = GRC_MISC_CFG_CORECLK_RESET;

	अगर (tg3_flag(tp, PCI_EXPRESS)) अणु
		/* Force PCIe 1.0a mode */
		अगर (tg3_asic_rev(tp) != ASIC_REV_5785 &&
		    !tg3_flag(tp, 57765_PLUS) &&
		    tr32(TG3_PCIE_PHY_TSTCTL) ==
		    (TG3_PCIE_PHY_TSTCTL_PCIE10 | TG3_PCIE_PHY_TSTCTL_PSCRAM))
			tw32(TG3_PCIE_PHY_TSTCTL, TG3_PCIE_PHY_TSTCTL_PSCRAM);

		अगर (tg3_chip_rev_id(tp) != CHIPREV_ID_5750_A0) अणु
			tw32(GRC_MISC_CFG, (1 << 29));
			val |= (1 << 29);
		पूर्ण
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		tw32(VCPU_STATUS, tr32(VCPU_STATUS) | VCPU_STATUS_DRV_RESET);
		tw32(GRC_VCPU_EXT_CTRL,
		     tr32(GRC_VCPU_EXT_CTRL) & ~GRC_VCPU_EXT_CTRL_HALT_CPU);
	पूर्ण

	/* Set the घड़ी to the highest frequency to aव्योम समयouts. With link
	 * aware mode, the घड़ी speed could be slow and bootcode करोes not
	 * complete within the expected समय. Override the घड़ी to allow the
	 * bootcode to finish sooner and then restore it.
	 */
	tg3_override_clk(tp);

	/* Manage gphy घातer क्रम all CPMU असलent PCIe devices. */
	अगर (tg3_flag(tp, 5705_PLUS) && !tg3_flag(tp, CPMU_PRESENT))
		val |= GRC_MISC_CFG_KEEP_GPHY_POWER;

	tw32(GRC_MISC_CFG, val);

	/* restore 5701 hardware bug workaround ग_लिखो method */
	tp->ग_लिखो32 = ग_लिखो_op;

	/* Unक्रमtunately, we have to delay beक्रमe the PCI पढ़ो back.
	 * Some 575X chips even will not respond to a PCI cfg access
	 * when the reset command is given to the chip.
	 *
	 * How करो these hardware designers expect things to work
	 * properly अगर the PCI ग_लिखो is posted क्रम a दीर्घ period
	 * of समय?  It is always necessary to have some method by
	 * which a रेजिस्टर पढ़ो back can occur to push the ग_लिखो
	 * out which करोes the reset.
	 *
	 * For most tg3 variants the trick below was working.
	 * Ho hum...
	 */
	udelay(120);

	/* Flush PCI posted ग_लिखोs.  The normal MMIO रेजिस्टरs
	 * are inaccessible at this समय so this is the only
	 * way to make this reliably (actually, this is no दीर्घer
	 * the हाल, see above).  I tried to use indirect
	 * रेजिस्टर पढ़ो/ग_लिखो but this upset some 5701 variants.
	 */
	pci_पढ़ो_config_dword(tp->pdev, PCI_COMMAND, &val);

	udelay(120);

	अगर (tg3_flag(tp, PCI_EXPRESS) && pci_is_pcie(tp->pdev)) अणु
		u16 val16;

		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5750_A0) अणु
			पूर्णांक j;
			u32 cfg_val;

			/* Wait क्रम link training to complete.  */
			क्रम (j = 0; j < 5000; j++)
				udelay(100);

			pci_पढ़ो_config_dword(tp->pdev, 0xc4, &cfg_val);
			pci_ग_लिखो_config_dword(tp->pdev, 0xc4,
					       cfg_val | (1 << 15));
		पूर्ण

		/* Clear the "no snoop" and "relaxed ordering" bits. */
		val16 = PCI_EXP_DEVCTL_RELAX_EN | PCI_EXP_DEVCTL_NOSNOOP_EN;
		/*
		 * Older PCIe devices only support the 128 byte
		 * MPS setting.  Enक्रमce the restriction.
		 */
		अगर (!tg3_flag(tp, CPMU_PRESENT))
			val16 |= PCI_EXP_DEVCTL_PAYLOAD;
		pcie_capability_clear_word(tp->pdev, PCI_EXP_DEVCTL, val16);

		/* Clear error status */
		pcie_capability_ग_लिखो_word(tp->pdev, PCI_EXP_DEVSTA,
				      PCI_EXP_DEVSTA_CED |
				      PCI_EXP_DEVSTA_NFED |
				      PCI_EXP_DEVSTA_FED |
				      PCI_EXP_DEVSTA_URD);
	पूर्ण

	tg3_restore_pci_state(tp);

	tg3_flag_clear(tp, CHIP_RESETTING);
	tg3_flag_clear(tp, ERROR_PROCESSED);

	val = 0;
	अगर (tg3_flag(tp, 5780_CLASS))
		val = tr32(MEMARB_MODE);
	tw32(MEMARB_MODE, val | MEMARB_MODE_ENABLE);

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5750_A3) अणु
		tg3_stop_fw(tp);
		tw32(0x5000, 0x400);
	पूर्ण

	अगर (tg3_flag(tp, IS_SSB_CORE)) अणु
		/*
		 * BCM4785: In order to aव्योम repercussions from using
		 * potentially defective पूर्णांकernal ROM, stop the Rx RISC CPU,
		 * which is not required.
		 */
		tg3_stop_fw(tp);
		tg3_halt_cpu(tp, RX_CPU_BASE);
	पूर्ण

	err = tg3_poll_fw(tp);
	अगर (err)
		वापस err;

	tw32(GRC_MODE, tp->grc_mode);

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5705_A0) अणु
		val = tr32(0xc4);

		tw32(0xc4, val | (1 << 15));
	पूर्ण

	अगर ((tp->nic_sram_data_cfg & NIC_SRAM_DATA_CFG_MINI_PCI) != 0 &&
	    tg3_asic_rev(tp) == ASIC_REV_5705) अणु
		tp->pci_घड़ी_ctrl |= CLOCK_CTRL_CLKRUN_OENABLE;
		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5705_A0)
			tp->pci_घड़ी_ctrl |= CLOCK_CTRL_FORCE_CLKRUN;
		tw32(TG3PCI_CLOCK_CTRL, tp->pci_घड़ी_ctrl);
	पूर्ण

	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES) अणु
		tp->mac_mode = MAC_MODE_PORT_MODE_TBI;
		val = tp->mac_mode;
	पूर्ण अन्यथा अगर (tp->phy_flags & TG3_PHYFLG_MII_SERDES) अणु
		tp->mac_mode = MAC_MODE_PORT_MODE_GMII;
		val = tp->mac_mode;
	पूर्ण अन्यथा
		val = 0;

	tw32_f(MAC_MODE, val);
	udelay(40);

	tg3_ape_unlock(tp, TG3_APE_LOCK_GRC);

	tg3_mdio_start(tp);

	अगर (tg3_flag(tp, PCI_EXPRESS) &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5750_A0 &&
	    tg3_asic_rev(tp) != ASIC_REV_5785 &&
	    !tg3_flag(tp, 57765_PLUS)) अणु
		val = tr32(0x7c00);

		tw32(0x7c00, val | (1 << 25));
	पूर्ण

	tg3_restore_clk(tp);

	/* Increase the core घड़ी speed to fix tx समयout issue क्रम 5762
	 * with 100Mbps link speed.
	 */
	अगर (tg3_asic_rev(tp) == ASIC_REV_5762) अणु
		val = tr32(TG3_CPMU_CLCK_ORIDE_ENABLE);
		tw32(TG3_CPMU_CLCK_ORIDE_ENABLE, val |
		     TG3_CPMU_MAC_ORIDE_ENABLE);
	पूर्ण

	/* Reprobe ASF enable state.  */
	tg3_flag_clear(tp, ENABLE_ASF);
	tp->phy_flags &= ~(TG3_PHYFLG_1G_ON_VAUX_OK |
			   TG3_PHYFLG_KEEP_LINK_ON_PWRDN);

	tg3_flag_clear(tp, ASF_NEW_HANDSHAKE);
	tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_SIG, &val);
	अगर (val == NIC_SRAM_DATA_SIG_MAGIC) अणु
		u32 nic_cfg;

		tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_CFG, &nic_cfg);
		अगर (nic_cfg & NIC_SRAM_DATA_CFG_ASF_ENABLE) अणु
			tg3_flag_set(tp, ENABLE_ASF);
			tp->last_event_jअगरfies = jअगरfies;
			अगर (tg3_flag(tp, 5750_PLUS))
				tg3_flag_set(tp, ASF_NEW_HANDSHAKE);

			tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_CFG_3, &nic_cfg);
			अगर (nic_cfg & NIC_SRAM_1G_ON_VAUX_OK)
				tp->phy_flags |= TG3_PHYFLG_1G_ON_VAUX_OK;
			अगर (nic_cfg & NIC_SRAM_LNK_FLAP_AVOID)
				tp->phy_flags |= TG3_PHYFLG_KEEP_LINK_ON_PWRDN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tg3_get_nstats(काष्ठा tg3 *, काष्ठा rtnl_link_stats64 *);
अटल व्योम tg3_get_estats(काष्ठा tg3 *, काष्ठा tg3_ethtool_stats *);
अटल व्योम __tg3_set_rx_mode(काष्ठा net_device *);

/* tp->lock is held. */
अटल पूर्णांक tg3_halt(काष्ठा tg3 *tp, पूर्णांक kind, bool silent)
अणु
	पूर्णांक err;

	tg3_stop_fw(tp);

	tg3_ग_लिखो_sig_pre_reset(tp, kind);

	tg3_पात_hw(tp, silent);
	err = tg3_chip_reset(tp);

	__tg3_set_mac_addr(tp, false);

	tg3_ग_लिखो_sig_legacy(tp, kind);
	tg3_ग_लिखो_sig_post_reset(tp, kind);

	अगर (tp->hw_stats) अणु
		/* Save the stats across chip resets... */
		tg3_get_nstats(tp, &tp->net_stats_prev);
		tg3_get_estats(tp, &tp->estats_prev);

		/* And make sure the next sample is new data */
		स_रखो(tp->hw_stats, 0, माप(काष्ठा tg3_hw_stats));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tg3_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक err = 0;
	bool skip_mac_1 = false;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	अगर (!netअगर_running(dev))
		वापस 0;

	अगर (tg3_flag(tp, ENABLE_ASF)) अणु
		u32 addr0_high, addr0_low, addr1_high, addr1_low;

		addr0_high = tr32(MAC_ADDR_0_HIGH);
		addr0_low = tr32(MAC_ADDR_0_LOW);
		addr1_high = tr32(MAC_ADDR_1_HIGH);
		addr1_low = tr32(MAC_ADDR_1_LOW);

		/* Skip MAC addr 1 अगर ASF is using it. */
		अगर ((addr0_high != addr1_high || addr0_low != addr1_low) &&
		    !(addr1_high == 0 && addr1_low == 0))
			skip_mac_1 = true;
	पूर्ण
	spin_lock_bh(&tp->lock);
	__tg3_set_mac_addr(tp, skip_mac_1);
	__tg3_set_rx_mode(dev);
	spin_unlock_bh(&tp->lock);

	वापस err;
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_set_bdinfo(काष्ठा tg3 *tp, u32 bdinfo_addr,
			   dma_addr_t mapping, u32 maxlen_flags,
			   u32 nic_addr)
अणु
	tg3_ग_लिखो_mem(tp,
		      (bdinfo_addr + TG3_BDINFO_HOST_ADDR + TG3_64BIT_REG_HIGH),
		      ((u64) mapping >> 32));
	tg3_ग_लिखो_mem(tp,
		      (bdinfo_addr + TG3_BDINFO_HOST_ADDR + TG3_64BIT_REG_LOW),
		      ((u64) mapping & 0xffffffff));
	tg3_ग_लिखो_mem(tp,
		      (bdinfo_addr + TG3_BDINFO_MAXLEN_FLAGS),
		       maxlen_flags);

	अगर (!tg3_flag(tp, 5705_PLUS))
		tg3_ग_लिखो_mem(tp,
			      (bdinfo_addr + TG3_BDINFO_NIC_ADDR),
			      nic_addr);
पूर्ण


अटल व्योम tg3_coal_tx_init(काष्ठा tg3 *tp, काष्ठा ethtool_coalesce *ec)
अणु
	पूर्णांक i = 0;

	अगर (!tg3_flag(tp, ENABLE_TSS)) अणु
		tw32(HOSTCC_TXCOL_TICKS, ec->tx_coalesce_usecs);
		tw32(HOSTCC_TXMAX_FRAMES, ec->tx_max_coalesced_frames);
		tw32(HOSTCC_TXCOAL_MAXF_INT, ec->tx_max_coalesced_frames_irq);
	पूर्ण अन्यथा अणु
		tw32(HOSTCC_TXCOL_TICKS, 0);
		tw32(HOSTCC_TXMAX_FRAMES, 0);
		tw32(HOSTCC_TXCOAL_MAXF_INT, 0);

		क्रम (; i < tp->txq_cnt; i++) अणु
			u32 reg;

			reg = HOSTCC_TXCOL_TICKS_VEC1 + i * 0x18;
			tw32(reg, ec->tx_coalesce_usecs);
			reg = HOSTCC_TXMAX_FRAMES_VEC1 + i * 0x18;
			tw32(reg, ec->tx_max_coalesced_frames);
			reg = HOSTCC_TXCOAL_MAXF_INT_VEC1 + i * 0x18;
			tw32(reg, ec->tx_max_coalesced_frames_irq);
		पूर्ण
	पूर्ण

	क्रम (; i < tp->irq_max - 1; i++) अणु
		tw32(HOSTCC_TXCOL_TICKS_VEC1 + i * 0x18, 0);
		tw32(HOSTCC_TXMAX_FRAMES_VEC1 + i * 0x18, 0);
		tw32(HOSTCC_TXCOAL_MAXF_INT_VEC1 + i * 0x18, 0);
	पूर्ण
पूर्ण

अटल व्योम tg3_coal_rx_init(काष्ठा tg3 *tp, काष्ठा ethtool_coalesce *ec)
अणु
	पूर्णांक i = 0;
	u32 limit = tp->rxq_cnt;

	अगर (!tg3_flag(tp, ENABLE_RSS)) अणु
		tw32(HOSTCC_RXCOL_TICKS, ec->rx_coalesce_usecs);
		tw32(HOSTCC_RXMAX_FRAMES, ec->rx_max_coalesced_frames);
		tw32(HOSTCC_RXCOAL_MAXF_INT, ec->rx_max_coalesced_frames_irq);
		limit--;
	पूर्ण अन्यथा अणु
		tw32(HOSTCC_RXCOL_TICKS, 0);
		tw32(HOSTCC_RXMAX_FRAMES, 0);
		tw32(HOSTCC_RXCOAL_MAXF_INT, 0);
	पूर्ण

	क्रम (; i < limit; i++) अणु
		u32 reg;

		reg = HOSTCC_RXCOL_TICKS_VEC1 + i * 0x18;
		tw32(reg, ec->rx_coalesce_usecs);
		reg = HOSTCC_RXMAX_FRAMES_VEC1 + i * 0x18;
		tw32(reg, ec->rx_max_coalesced_frames);
		reg = HOSTCC_RXCOAL_MAXF_INT_VEC1 + i * 0x18;
		tw32(reg, ec->rx_max_coalesced_frames_irq);
	पूर्ण

	क्रम (; i < tp->irq_max - 1; i++) अणु
		tw32(HOSTCC_RXCOL_TICKS_VEC1 + i * 0x18, 0);
		tw32(HOSTCC_RXMAX_FRAMES_VEC1 + i * 0x18, 0);
		tw32(HOSTCC_RXCOAL_MAXF_INT_VEC1 + i * 0x18, 0);
	पूर्ण
पूर्ण

अटल व्योम __tg3_set_coalesce(काष्ठा tg3 *tp, काष्ठा ethtool_coalesce *ec)
अणु
	tg3_coal_tx_init(tp, ec);
	tg3_coal_rx_init(tp, ec);

	अगर (!tg3_flag(tp, 5705_PLUS)) अणु
		u32 val = ec->stats_block_coalesce_usecs;

		tw32(HOSTCC_RXCOAL_TICK_INT, ec->rx_coalesce_usecs_irq);
		tw32(HOSTCC_TXCOAL_TICK_INT, ec->tx_coalesce_usecs_irq);

		अगर (!tp->link_up)
			val = 0;

		tw32(HOSTCC_STAT_COAL_TICKS, val);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_tx_rcbs_disable(काष्ठा tg3 *tp)
अणु
	u32 txrcb, limit;

	/* Disable all transmit rings but the first. */
	अगर (!tg3_flag(tp, 5705_PLUS))
		limit = NIC_SRAM_SEND_RCB + TG3_BDINFO_SIZE * 16;
	अन्यथा अगर (tg3_flag(tp, 5717_PLUS))
		limit = NIC_SRAM_SEND_RCB + TG3_BDINFO_SIZE * 4;
	अन्यथा अगर (tg3_flag(tp, 57765_CLASS) ||
		 tg3_asic_rev(tp) == ASIC_REV_5762)
		limit = NIC_SRAM_SEND_RCB + TG3_BDINFO_SIZE * 2;
	अन्यथा
		limit = NIC_SRAM_SEND_RCB + TG3_BDINFO_SIZE;

	क्रम (txrcb = NIC_SRAM_SEND_RCB + TG3_BDINFO_SIZE;
	     txrcb < limit; txrcb += TG3_BDINFO_SIZE)
		tg3_ग_लिखो_mem(tp, txrcb + TG3_BDINFO_MAXLEN_FLAGS,
			      BDINFO_FLAGS_DISABLED);
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_tx_rcbs_init(काष्ठा tg3 *tp)
अणु
	पूर्णांक i = 0;
	u32 txrcb = NIC_SRAM_SEND_RCB;

	अगर (tg3_flag(tp, ENABLE_TSS))
		i++;

	क्रम (; i < tp->irq_max; i++, txrcb += TG3_BDINFO_SIZE) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		अगर (!tnapi->tx_ring)
			जारी;

		tg3_set_bdinfo(tp, txrcb, tnapi->tx_desc_mapping,
			       (TG3_TX_RING_SIZE << BDINFO_FLAGS_MAXLEN_SHIFT),
			       NIC_SRAM_TX_BUFFER_DESC);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_rx_ret_rcbs_disable(काष्ठा tg3 *tp)
अणु
	u32 rxrcb, limit;

	/* Disable all receive वापस rings but the first. */
	अगर (tg3_flag(tp, 5717_PLUS))
		limit = NIC_SRAM_RCV_RET_RCB + TG3_BDINFO_SIZE * 17;
	अन्यथा अगर (!tg3_flag(tp, 5705_PLUS))
		limit = NIC_SRAM_RCV_RET_RCB + TG3_BDINFO_SIZE * 16;
	अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5755 ||
		 tg3_asic_rev(tp) == ASIC_REV_5762 ||
		 tg3_flag(tp, 57765_CLASS))
		limit = NIC_SRAM_RCV_RET_RCB + TG3_BDINFO_SIZE * 4;
	अन्यथा
		limit = NIC_SRAM_RCV_RET_RCB + TG3_BDINFO_SIZE;

	क्रम (rxrcb = NIC_SRAM_RCV_RET_RCB + TG3_BDINFO_SIZE;
	     rxrcb < limit; rxrcb += TG3_BDINFO_SIZE)
		tg3_ग_लिखो_mem(tp, rxrcb + TG3_BDINFO_MAXLEN_FLAGS,
			      BDINFO_FLAGS_DISABLED);
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_rx_ret_rcbs_init(काष्ठा tg3 *tp)
अणु
	पूर्णांक i = 0;
	u32 rxrcb = NIC_SRAM_RCV_RET_RCB;

	अगर (tg3_flag(tp, ENABLE_RSS))
		i++;

	क्रम (; i < tp->irq_max; i++, rxrcb += TG3_BDINFO_SIZE) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		अगर (!tnapi->rx_rcb)
			जारी;

		tg3_set_bdinfo(tp, rxrcb, tnapi->rx_rcb_mapping,
			       (tp->rx_ret_ring_mask + 1) <<
				BDINFO_FLAGS_MAXLEN_SHIFT, 0);
	पूर्ण
पूर्ण

/* tp->lock is held. */
अटल व्योम tg3_rings_reset(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	u32 stblk;
	काष्ठा tg3_napi *tnapi = &tp->napi[0];

	tg3_tx_rcbs_disable(tp);

	tg3_rx_ret_rcbs_disable(tp);

	/* Disable पूर्णांकerrupts */
	tw32_mailbox_f(tp->napi[0].पूर्णांक_mbox, 1);
	tp->napi[0].chk_msi_cnt = 0;
	tp->napi[0].last_rx_cons = 0;
	tp->napi[0].last_tx_cons = 0;

	/* Zero mailbox रेजिस्टरs. */
	अगर (tg3_flag(tp, SUPPORT_MSIX)) अणु
		क्रम (i = 1; i < tp->irq_max; i++) अणु
			tp->napi[i].tx_prod = 0;
			tp->napi[i].tx_cons = 0;
			अगर (tg3_flag(tp, ENABLE_TSS))
				tw32_mailbox(tp->napi[i].prodmbox, 0);
			tw32_rx_mbox(tp->napi[i].consmbox, 0);
			tw32_mailbox_f(tp->napi[i].पूर्णांक_mbox, 1);
			tp->napi[i].chk_msi_cnt = 0;
			tp->napi[i].last_rx_cons = 0;
			tp->napi[i].last_tx_cons = 0;
		पूर्ण
		अगर (!tg3_flag(tp, ENABLE_TSS))
			tw32_mailbox(tp->napi[0].prodmbox, 0);
	पूर्ण अन्यथा अणु
		tp->napi[0].tx_prod = 0;
		tp->napi[0].tx_cons = 0;
		tw32_mailbox(tp->napi[0].prodmbox, 0);
		tw32_rx_mbox(tp->napi[0].consmbox, 0);
	पूर्ण

	/* Make sure the NIC-based send BD rings are disabled. */
	अगर (!tg3_flag(tp, 5705_PLUS)) अणु
		u32 mbox = MAILBOX_SNDNIC_PROD_IDX_0 + TG3_64BIT_REG_LOW;
		क्रम (i = 0; i < 16; i++)
			tw32_tx_mbox(mbox + i * 8, 0);
	पूर्ण

	/* Clear status block in ram. */
	स_रखो(tnapi->hw_status, 0, TG3_HW_STATUS_SIZE);

	/* Set status block DMA address */
	tw32(HOSTCC_STATUS_BLK_HOST_ADDR + TG3_64BIT_REG_HIGH,
	     ((u64) tnapi->status_mapping >> 32));
	tw32(HOSTCC_STATUS_BLK_HOST_ADDR + TG3_64BIT_REG_LOW,
	     ((u64) tnapi->status_mapping & 0xffffffff));

	stblk = HOSTCC_STATBLCK_RING1;

	क्रम (i = 1, tnapi++; i < tp->irq_cnt; i++, tnapi++) अणु
		u64 mapping = (u64)tnapi->status_mapping;
		tw32(stblk + TG3_64BIT_REG_HIGH, mapping >> 32);
		tw32(stblk + TG3_64BIT_REG_LOW, mapping & 0xffffffff);
		stblk += 8;

		/* Clear status block in ram. */
		स_रखो(tnapi->hw_status, 0, TG3_HW_STATUS_SIZE);
	पूर्ण

	tg3_tx_rcbs_init(tp);
	tg3_rx_ret_rcbs_init(tp);
पूर्ण

अटल व्योम tg3_setup_rxbd_thresholds(काष्ठा tg3 *tp)
अणु
	u32 val, bdcache_maxcnt, host_rep_thresh, nic_rep_thresh;

	अगर (!tg3_flag(tp, 5750_PLUS) ||
	    tg3_flag(tp, 5780_CLASS) ||
	    tg3_asic_rev(tp) == ASIC_REV_5750 ||
	    tg3_asic_rev(tp) == ASIC_REV_5752 ||
	    tg3_flag(tp, 57765_PLUS))
		bdcache_maxcnt = TG3_SRAM_RX_STD_BDCACHE_SIZE_5700;
	अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5755 ||
		 tg3_asic_rev(tp) == ASIC_REV_5787)
		bdcache_maxcnt = TG3_SRAM_RX_STD_BDCACHE_SIZE_5755;
	अन्यथा
		bdcache_maxcnt = TG3_SRAM_RX_STD_BDCACHE_SIZE_5906;

	nic_rep_thresh = min(bdcache_maxcnt / 2, tp->rx_std_max_post);
	host_rep_thresh = max_t(u32, tp->rx_pending / 8, 1);

	val = min(nic_rep_thresh, host_rep_thresh);
	tw32(RCVBDI_STD_THRESH, val);

	अगर (tg3_flag(tp, 57765_PLUS))
		tw32(STD_REPLENISH_LWM, bdcache_maxcnt);

	अगर (!tg3_flag(tp, JUMBO_CAPABLE) || tg3_flag(tp, 5780_CLASS))
		वापस;

	bdcache_maxcnt = TG3_SRAM_RX_JMB_BDCACHE_SIZE_5700;

	host_rep_thresh = max_t(u32, tp->rx_jumbo_pending / 8, 1);

	val = min(bdcache_maxcnt / 2, host_rep_thresh);
	tw32(RCVBDI_JUMBO_THRESH, val);

	अगर (tg3_flag(tp, 57765_PLUS))
		tw32(JMB_REPLENISH_LWM, bdcache_maxcnt);
पूर्ण

अटल अंतरभूत u32 calc_crc(अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	u32 reg;
	u32 पंचांगp;
	पूर्णांक j, k;

	reg = 0xffffffff;

	क्रम (j = 0; j < len; j++) अणु
		reg ^= buf[j];

		क्रम (k = 0; k < 8; k++) अणु
			पंचांगp = reg & 0x01;

			reg >>= 1;

			अगर (पंचांगp)
				reg ^= CRC32_POLY_LE;
		पूर्ण
	पूर्ण

	वापस ~reg;
पूर्ण

अटल व्योम tg3_set_multi(काष्ठा tg3 *tp, अचिन्हित पूर्णांक accept_all)
अणु
	/* accept or reject all multicast frames */
	tw32(MAC_HASH_REG_0, accept_all ? 0xffffffff : 0);
	tw32(MAC_HASH_REG_1, accept_all ? 0xffffffff : 0);
	tw32(MAC_HASH_REG_2, accept_all ? 0xffffffff : 0);
	tw32(MAC_HASH_REG_3, accept_all ? 0xffffffff : 0);
पूर्ण

अटल व्योम __tg3_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	u32 rx_mode;

	rx_mode = tp->rx_mode & ~(RX_MODE_PROMISC |
				  RX_MODE_KEEP_VLAN_TAG);

#अगर !defined(CONFIG_VLAN_8021Q) && !defined(CONFIG_VLAN_8021Q_MODULE)
	/* When ASF is in use, we always keep the RX_MODE_KEEP_VLAN_TAG
	 * flag clear.
	 */
	अगर (!tg3_flag(tp, ENABLE_ASF))
		rx_mode |= RX_MODE_KEEP_VLAN_TAG;
#पूर्ण_अगर

	अगर (dev->flags & IFF_PROMISC) अणु
		/* Promiscuous mode. */
		rx_mode |= RX_MODE_PROMISC;
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		/* Accept all multicast. */
		tg3_set_multi(tp, 1);
	पूर्ण अन्यथा अगर (netdev_mc_empty(dev)) अणु
		/* Reject all multicast. */
		tg3_set_multi(tp, 0);
	पूर्ण अन्यथा अणु
		/* Accept one or more multicast(s). */
		काष्ठा netdev_hw_addr *ha;
		u32 mc_filter[4] = अणु 0, पूर्ण;
		u32 regidx;
		u32 bit;
		u32 crc;

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			crc = calc_crc(ha->addr, ETH_ALEN);
			bit = ~crc & 0x7f;
			regidx = (bit & 0x60) >> 5;
			bit &= 0x1f;
			mc_filter[regidx] |= (1 << bit);
		पूर्ण

		tw32(MAC_HASH_REG_0, mc_filter[0]);
		tw32(MAC_HASH_REG_1, mc_filter[1]);
		tw32(MAC_HASH_REG_2, mc_filter[2]);
		tw32(MAC_HASH_REG_3, mc_filter[3]);
	पूर्ण

	अगर (netdev_uc_count(dev) > TG3_MAX_UCAST_ADDR(tp)) अणु
		rx_mode |= RX_MODE_PROMISC;
	पूर्ण अन्यथा अगर (!(dev->flags & IFF_PROMISC)) अणु
		/* Add all entries पूर्णांकo to the mac addr filter list */
		पूर्णांक i = 0;
		काष्ठा netdev_hw_addr *ha;

		netdev_क्रम_each_uc_addr(ha, dev) अणु
			__tg3_set_one_mac_addr(tp, ha->addr,
					       i + TG3_UCAST_ADDR_IDX(tp));
			i++;
		पूर्ण
	पूर्ण

	अगर (rx_mode != tp->rx_mode) अणु
		tp->rx_mode = rx_mode;
		tw32_f(MAC_RX_MODE, rx_mode);
		udelay(10);
	पूर्ण
पूर्ण

अटल व्योम tg3_rss_init_dflt_indir_tbl(काष्ठा tg3 *tp, u32 qcnt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TG3_RSS_INसूची_TBL_SIZE; i++)
		tp->rss_ind_tbl[i] = ethtool_rxfh_indir_शेष(i, qcnt);
पूर्ण

अटल व्योम tg3_rss_check_indir_tbl(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	अगर (!tg3_flag(tp, SUPPORT_MSIX))
		वापस;

	अगर (tp->rxq_cnt == 1) अणु
		स_रखो(&tp->rss_ind_tbl[0], 0, माप(tp->rss_ind_tbl));
		वापस;
	पूर्ण

	/* Validate table against current IRQ count */
	क्रम (i = 0; i < TG3_RSS_INसूची_TBL_SIZE; i++) अणु
		अगर (tp->rss_ind_tbl[i] >= tp->rxq_cnt)
			अवरोध;
	पूर्ण

	अगर (i != TG3_RSS_INसूची_TBL_SIZE)
		tg3_rss_init_dflt_indir_tbl(tp, tp->rxq_cnt);
पूर्ण

अटल व्योम tg3_rss_ग_लिखो_indir_tbl(काष्ठा tg3 *tp)
अणु
	पूर्णांक i = 0;
	u32 reg = MAC_RSS_INसूची_TBL_0;

	जबतक (i < TG3_RSS_INसूची_TBL_SIZE) अणु
		u32 val = tp->rss_ind_tbl[i];
		i++;
		क्रम (; i % 8; i++) अणु
			val <<= 4;
			val |= tp->rss_ind_tbl[i];
		पूर्ण
		tw32(reg, val);
		reg += 4;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 tg3_lso_rd_dma_workaround_bit(काष्ठा tg3 *tp)
अणु
	अगर (tg3_asic_rev(tp) == ASIC_REV_5719)
		वापस TG3_LSO_RD_DMA_TX_LENGTH_WA_5719;
	अन्यथा
		वापस TG3_LSO_RD_DMA_TX_LENGTH_WA_5720;
पूर्ण

/* tp->lock is held. */
अटल पूर्णांक tg3_reset_hw(काष्ठा tg3 *tp, bool reset_phy)
अणु
	u32 val, rdmac_mode;
	पूर्णांक i, err, limit;
	काष्ठा tg3_rx_prodring_set *tpr = &tp->napi[0].prodring;

	tg3_disable_पूर्णांकs(tp);

	tg3_stop_fw(tp);

	tg3_ग_लिखो_sig_pre_reset(tp, RESET_KIND_INIT);

	अगर (tg3_flag(tp, INIT_COMPLETE))
		tg3_पात_hw(tp, 1);

	अगर ((tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN) &&
	    !(tp->phy_flags & TG3_PHYFLG_USER_CONFIGURED)) अणु
		tg3_phy_pull_config(tp);
		tg3_eee_pull_config(tp, शून्य);
		tp->phy_flags |= TG3_PHYFLG_USER_CONFIGURED;
	पूर्ण

	/* Enable MAC control of LPI */
	अगर (tp->phy_flags & TG3_PHYFLG_EEE_CAP)
		tg3_setup_eee(tp);

	अगर (reset_phy)
		tg3_phy_reset(tp);

	err = tg3_chip_reset(tp);
	अगर (err)
		वापस err;

	tg3_ग_लिखो_sig_legacy(tp, RESET_KIND_INIT);

	अगर (tg3_chip_rev(tp) == CHIPREV_5784_AX) अणु
		val = tr32(TG3_CPMU_CTRL);
		val &= ~(CPMU_CTRL_LINK_AWARE_MODE | CPMU_CTRL_LINK_IDLE_MODE);
		tw32(TG3_CPMU_CTRL, val);

		val = tr32(TG3_CPMU_LSPD_10MB_CLK);
		val &= ~CPMU_LSPD_10MB_MACCLK_MASK;
		val |= CPMU_LSPD_10MB_MACCLK_6_25;
		tw32(TG3_CPMU_LSPD_10MB_CLK, val);

		val = tr32(TG3_CPMU_LNK_AWARE_PWRMD);
		val &= ~CPMU_LNK_AWARE_MACCLK_MASK;
		val |= CPMU_LNK_AWARE_MACCLK_6_25;
		tw32(TG3_CPMU_LNK_AWARE_PWRMD, val);

		val = tr32(TG3_CPMU_HST_ACC);
		val &= ~CPMU_HST_ACC_MACCLK_MASK;
		val |= CPMU_HST_ACC_MACCLK_6_25;
		tw32(TG3_CPMU_HST_ACC, val);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_57780) अणु
		val = tr32(PCIE_PWR_MGMT_THRESH) & ~PCIE_PWR_MGMT_L1_THRESH_MSK;
		val |= PCIE_PWR_MGMT_EXT_ASPM_TMR_EN |
		       PCIE_PWR_MGMT_L1_THRESH_4MS;
		tw32(PCIE_PWR_MGMT_THRESH, val);

		val = tr32(TG3_PCIE_EIDLE_DELAY) & ~TG3_PCIE_EIDLE_DELAY_MASK;
		tw32(TG3_PCIE_EIDLE_DELAY, val | TG3_PCIE_EIDLE_DELAY_13_CLKS);

		tw32(TG3_CORR_ERR_STAT, TG3_CORR_ERR_STAT_CLEAR);

		val = tr32(TG3_PCIE_LNKCTL) & ~TG3_PCIE_LNKCTL_L1_PLL_PD_EN;
		tw32(TG3_PCIE_LNKCTL, val | TG3_PCIE_LNKCTL_L1_PLL_PD_DIS);
	पूर्ण

	अगर (tg3_flag(tp, L1PLLPD_EN)) अणु
		u32 grc_mode = tr32(GRC_MODE);

		/* Access the lower 1K of PL PCIE block रेजिस्टरs. */
		val = grc_mode & ~GRC_MODE_PCIE_PORT_MASK;
		tw32(GRC_MODE, val | GRC_MODE_PCIE_PL_SEL);

		val = tr32(TG3_PCIE_TLDLPL_PORT + TG3_PCIE_PL_LO_PHYCTL1);
		tw32(TG3_PCIE_TLDLPL_PORT + TG3_PCIE_PL_LO_PHYCTL1,
		     val | TG3_PCIE_PL_LO_PHYCTL1_L1PLLPD_EN);

		tw32(GRC_MODE, grc_mode);
	पूर्ण

	अगर (tg3_flag(tp, 57765_CLASS)) अणु
		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_57765_A0) अणु
			u32 grc_mode = tr32(GRC_MODE);

			/* Access the lower 1K of PL PCIE block रेजिस्टरs. */
			val = grc_mode & ~GRC_MODE_PCIE_PORT_MASK;
			tw32(GRC_MODE, val | GRC_MODE_PCIE_PL_SEL);

			val = tr32(TG3_PCIE_TLDLPL_PORT +
				   TG3_PCIE_PL_LO_PHYCTL5);
			tw32(TG3_PCIE_TLDLPL_PORT + TG3_PCIE_PL_LO_PHYCTL5,
			     val | TG3_PCIE_PL_LO_PHYCTL5_DIS_L2CLKREQ);

			tw32(GRC_MODE, grc_mode);
		पूर्ण

		अगर (tg3_chip_rev(tp) != CHIPREV_57765_AX) अणु
			u32 grc_mode;

			/* Fix transmit hangs */
			val = tr32(TG3_CPMU_PADRNG_CTL);
			val |= TG3_CPMU_PADRNG_CTL_RDIV2;
			tw32(TG3_CPMU_PADRNG_CTL, val);

			grc_mode = tr32(GRC_MODE);

			/* Access the lower 1K of DL PCIE block रेजिस्टरs. */
			val = grc_mode & ~GRC_MODE_PCIE_PORT_MASK;
			tw32(GRC_MODE, val | GRC_MODE_PCIE_DL_SEL);

			val = tr32(TG3_PCIE_TLDLPL_PORT +
				   TG3_PCIE_DL_LO_FTSMAX);
			val &= ~TG3_PCIE_DL_LO_FTSMAX_MSK;
			tw32(TG3_PCIE_TLDLPL_PORT + TG3_PCIE_DL_LO_FTSMAX,
			     val | TG3_PCIE_DL_LO_FTSMAX_VAL);

			tw32(GRC_MODE, grc_mode);
		पूर्ण

		val = tr32(TG3_CPMU_LSPD_10MB_CLK);
		val &= ~CPMU_LSPD_10MB_MACCLK_MASK;
		val |= CPMU_LSPD_10MB_MACCLK_6_25;
		tw32(TG3_CPMU_LSPD_10MB_CLK, val);
	पूर्ण

	/* This works around an issue with Athlon chipsets on
	 * B3 tigon3 silicon.  This bit has no effect on any
	 * other revision.  But करो not set this on PCI Express
	 * chips and करोn't even touch the घड़ीs अगर the CPMU is present.
	 */
	अगर (!tg3_flag(tp, CPMU_PRESENT)) अणु
		अगर (!tg3_flag(tp, PCI_EXPRESS))
			tp->pci_घड़ी_ctrl |= CLOCK_CTRL_DELAY_PCI_GRANT;
		tw32_f(TG3PCI_CLOCK_CTRL, tp->pci_घड़ी_ctrl);
	पूर्ण

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5704_A0 &&
	    tg3_flag(tp, PCIX_MODE)) अणु
		val = tr32(TG3PCI_PCISTATE);
		val |= PCISTATE_RETRY_SAME_DMA;
		tw32(TG3PCI_PCISTATE, val);
	पूर्ण

	अगर (tg3_flag(tp, ENABLE_APE)) अणु
		/* Allow पढ़ोs and ग_लिखोs to the
		 * APE रेजिस्टर and memory space.
		 */
		val = tr32(TG3PCI_PCISTATE);
		val |= PCISTATE_ALLOW_APE_CTLSPC_WR |
		       PCISTATE_ALLOW_APE_SHMEM_WR |
		       PCISTATE_ALLOW_APE_PSPACE_WR;
		tw32(TG3PCI_PCISTATE, val);
	पूर्ण

	अगर (tg3_chip_rev(tp) == CHIPREV_5704_BX) अणु
		/* Enable some hw fixes.  */
		val = tr32(TG3PCI_MSI_DATA);
		val |= (1 << 26) | (1 << 28) | (1 << 29);
		tw32(TG3PCI_MSI_DATA, val);
	पूर्ण

	/* Descriptor ring init may make accesses to the
	 * NIC SRAM area to setup the TX descriptors, so we
	 * can only करो this after the hardware has been
	 * successfully reset.
	 */
	err = tg3_init_rings(tp);
	अगर (err)
		वापस err;

	अगर (tg3_flag(tp, 57765_PLUS)) अणु
		val = tr32(TG3PCI_DMA_RW_CTRL) &
		      ~DMA_RWCTRL_DIS_CACHE_ALIGNMENT;
		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_57765_A0)
			val &= ~DMA_RWCTRL_CRDRDR_RDMA_MRRS_MSK;
		अगर (!tg3_flag(tp, 57765_CLASS) &&
		    tg3_asic_rev(tp) != ASIC_REV_5717 &&
		    tg3_asic_rev(tp) != ASIC_REV_5762)
			val |= DMA_RWCTRL_TAGGED_STAT_WA;
		tw32(TG3PCI_DMA_RW_CTRL, val | tp->dma_rwctrl);
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) != ASIC_REV_5784 &&
		   tg3_asic_rev(tp) != ASIC_REV_5761) अणु
		/* This value is determined during the probe समय DMA
		 * engine test, tg3_test_dma.
		 */
		tw32(TG3PCI_DMA_RW_CTRL, tp->dma_rwctrl);
	पूर्ण

	tp->grc_mode &= ~(GRC_MODE_HOST_SENDBDS |
			  GRC_MODE_4X_NIC_SEND_RINGS |
			  GRC_MODE_NO_TX_PHDR_CSUM |
			  GRC_MODE_NO_RX_PHDR_CSUM);
	tp->grc_mode |= GRC_MODE_HOST_SENDBDS;

	/* Pseuकरो-header checksum is करोne by hardware logic and not
	 * the offload processers, so make the chip करो the pseuकरो-
	 * header checksums on receive.  For transmit it is more
	 * convenient to करो the pseuकरो-header checksum in software
	 * as Linux करोes that on transmit क्रम us in all हालs.
	 */
	tp->grc_mode |= GRC_MODE_NO_TX_PHDR_CSUM;

	val = GRC_MODE_IRQ_ON_MAC_ATTN | GRC_MODE_HOST_STACKUP;
	अगर (tp->rxptpctl)
		tw32(TG3_RX_PTP_CTL,
		     tp->rxptpctl | TG3_RX_PTP_CTL_HWTS_INTERLOCK);

	अगर (tg3_flag(tp, PTP_CAPABLE))
		val |= GRC_MODE_TIME_SYNC_ENABLE;

	tw32(GRC_MODE, tp->grc_mode | val);

	/* On one of the AMD platक्रमm, MRRS is restricted to 4000 because of
	 * south bridge limitation. As a workaround, Driver is setting MRRS
	 * to 2048 instead of शेष 4096.
	 */
	अगर (tp->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DELL &&
	    tp->pdev->subप्रणाली_device == TG3PCI_SUBDEVICE_ID_DELL_5762) अणु
		val = tr32(TG3PCI_DEV_STATUS_CTRL) & ~MAX_READ_REQ_MASK;
		tw32(TG3PCI_DEV_STATUS_CTRL, val | MAX_READ_REQ_SIZE_2048);
	पूर्ण

	/* Setup the समयr prescalar रेजिस्टर.  Clock is always 66Mhz. */
	val = tr32(GRC_MISC_CFG);
	val &= ~0xff;
	val |= (65 << GRC_MISC_CFG_PRESCALAR_SHIFT);
	tw32(GRC_MISC_CFG, val);

	/* Initialize MBUF/DESC pool. */
	अगर (tg3_flag(tp, 5750_PLUS)) अणु
		/* Do nothing.  */
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) != ASIC_REV_5705) अणु
		tw32(BUFMGR_MB_POOL_ADDR, NIC_SRAM_MBUF_POOL_BASE);
		अगर (tg3_asic_rev(tp) == ASIC_REV_5704)
			tw32(BUFMGR_MB_POOL_SIZE, NIC_SRAM_MBUF_POOL_SIZE64);
		अन्यथा
			tw32(BUFMGR_MB_POOL_SIZE, NIC_SRAM_MBUF_POOL_SIZE96);
		tw32(BUFMGR_DMA_DESC_POOL_ADDR, NIC_SRAM_DMA_DESC_POOL_BASE);
		tw32(BUFMGR_DMA_DESC_POOL_SIZE, NIC_SRAM_DMA_DESC_POOL_SIZE);
	पूर्ण अन्यथा अगर (tg3_flag(tp, TSO_CAPABLE)) अणु
		पूर्णांक fw_len;

		fw_len = tp->fw_len;
		fw_len = (fw_len + (0x80 - 1)) & ~(0x80 - 1);
		tw32(BUFMGR_MB_POOL_ADDR,
		     NIC_SRAM_MBUF_POOL_BASE5705 + fw_len);
		tw32(BUFMGR_MB_POOL_SIZE,
		     NIC_SRAM_MBUF_POOL_SIZE5705 - fw_len - 0xa00);
	पूर्ण

	अगर (tp->dev->mtu <= ETH_DATA_LEN) अणु
		tw32(BUFMGR_MB_RDMA_LOW_WATER,
		     tp->bufmgr_config.mbuf_पढ़ो_dma_low_water);
		tw32(BUFMGR_MB_MACRX_LOW_WATER,
		     tp->bufmgr_config.mbuf_mac_rx_low_water);
		tw32(BUFMGR_MB_HIGH_WATER,
		     tp->bufmgr_config.mbuf_high_water);
	पूर्ण अन्यथा अणु
		tw32(BUFMGR_MB_RDMA_LOW_WATER,
		     tp->bufmgr_config.mbuf_पढ़ो_dma_low_water_jumbo);
		tw32(BUFMGR_MB_MACRX_LOW_WATER,
		     tp->bufmgr_config.mbuf_mac_rx_low_water_jumbo);
		tw32(BUFMGR_MB_HIGH_WATER,
		     tp->bufmgr_config.mbuf_high_water_jumbo);
	पूर्ण
	tw32(BUFMGR_DMA_LOW_WATER,
	     tp->bufmgr_config.dma_low_water);
	tw32(BUFMGR_DMA_HIGH_WATER,
	     tp->bufmgr_config.dma_high_water);

	val = BUFMGR_MODE_ENABLE | BUFMGR_MODE_ATTN_ENABLE;
	अगर (tg3_asic_rev(tp) == ASIC_REV_5719)
		val |= BUFMGR_MODE_NO_TX_UNDERRUN;
	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762 ||
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5719_A0 ||
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5720_A0)
		val |= BUFMGR_MODE_MBLOW_ATTN_ENAB;
	tw32(BUFMGR_MODE, val);
	क्रम (i = 0; i < 2000; i++) अणु
		अगर (tr32(BUFMGR_MODE) & BUFMGR_MODE_ENABLE)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (i >= 2000) अणु
		netdev_err(tp->dev, "%s cannot enable BUFMGR\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5906_A1)
		tw32(ISO_PKT_TX, (tr32(ISO_PKT_TX) & ~0x3) | 0x2);

	tg3_setup_rxbd_thresholds(tp);

	/* Initialize TG3_BDINFO's at:
	 *  RCVDBDI_STD_BD:	standard eth size rx ring
	 *  RCVDBDI_JUMBO_BD:	jumbo frame rx ring
	 *  RCVDBDI_MINI_BD:	small frame rx ring (??? करोes not work)
	 *
	 * like so:
	 *  TG3_BDINFO_HOST_ADDR:	high/low parts of DMA address of ring
	 *  TG3_BDINFO_MAXLEN_FLAGS:	(rx max buffer size << 16) |
	 *                              ring attribute flags
	 *  TG3_BDINFO_NIC_ADDR:	location of descriptors in nic SRAM
	 *
	 * Standard receive ring @ NIC_SRAM_RX_BUFFER_DESC, 512 entries.
	 * Jumbo receive ring @ NIC_SRAM_RX_JUMBO_BUFFER_DESC, 256 entries.
	 *
	 * The size of each ring is fixed in the firmware, but the location is
	 * configurable.
	 */
	tw32(RCVDBDI_STD_BD + TG3_BDINFO_HOST_ADDR + TG3_64BIT_REG_HIGH,
	     ((u64) tpr->rx_std_mapping >> 32));
	tw32(RCVDBDI_STD_BD + TG3_BDINFO_HOST_ADDR + TG3_64BIT_REG_LOW,
	     ((u64) tpr->rx_std_mapping & 0xffffffff));
	अगर (!tg3_flag(tp, 5717_PLUS))
		tw32(RCVDBDI_STD_BD + TG3_BDINFO_NIC_ADDR,
		     NIC_SRAM_RX_BUFFER_DESC);

	/* Disable the mini ring */
	अगर (!tg3_flag(tp, 5705_PLUS))
		tw32(RCVDBDI_MINI_BD + TG3_BDINFO_MAXLEN_FLAGS,
		     BDINFO_FLAGS_DISABLED);

	/* Program the jumbo buffer descriptor ring control
	 * blocks on those devices that have them.
	 */
	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5719_A0 ||
	    (tg3_flag(tp, JUMBO_CAPABLE) && !tg3_flag(tp, 5780_CLASS))) अणु

		अगर (tg3_flag(tp, JUMBO_RING_ENABLE)) अणु
			tw32(RCVDBDI_JUMBO_BD + TG3_BDINFO_HOST_ADDR + TG3_64BIT_REG_HIGH,
			     ((u64) tpr->rx_jmb_mapping >> 32));
			tw32(RCVDBDI_JUMBO_BD + TG3_BDINFO_HOST_ADDR + TG3_64BIT_REG_LOW,
			     ((u64) tpr->rx_jmb_mapping & 0xffffffff));
			val = TG3_RX_JMB_RING_SIZE(tp) <<
			      BDINFO_FLAGS_MAXLEN_SHIFT;
			tw32(RCVDBDI_JUMBO_BD + TG3_BDINFO_MAXLEN_FLAGS,
			     val | BDINFO_FLAGS_USE_EXT_RECV);
			अगर (!tg3_flag(tp, USE_JUMBO_BDFLAG) ||
			    tg3_flag(tp, 57765_CLASS) ||
			    tg3_asic_rev(tp) == ASIC_REV_5762)
				tw32(RCVDBDI_JUMBO_BD + TG3_BDINFO_NIC_ADDR,
				     NIC_SRAM_RX_JUMBO_BUFFER_DESC);
		पूर्ण अन्यथा अणु
			tw32(RCVDBDI_JUMBO_BD + TG3_BDINFO_MAXLEN_FLAGS,
			     BDINFO_FLAGS_DISABLED);
		पूर्ण

		अगर (tg3_flag(tp, 57765_PLUS)) अणु
			val = TG3_RX_STD_RING_SIZE(tp);
			val <<= BDINFO_FLAGS_MAXLEN_SHIFT;
			val |= (TG3_RX_STD_DMA_SZ << 2);
		पूर्ण अन्यथा
			val = TG3_RX_STD_DMA_SZ << BDINFO_FLAGS_MAXLEN_SHIFT;
	पूर्ण अन्यथा
		val = TG3_RX_STD_MAX_SIZE_5700 << BDINFO_FLAGS_MAXLEN_SHIFT;

	tw32(RCVDBDI_STD_BD + TG3_BDINFO_MAXLEN_FLAGS, val);

	tpr->rx_std_prod_idx = tp->rx_pending;
	tw32_rx_mbox(TG3_RX_STD_PROD_IDX_REG, tpr->rx_std_prod_idx);

	tpr->rx_jmb_prod_idx =
		tg3_flag(tp, JUMBO_RING_ENABLE) ? tp->rx_jumbo_pending : 0;
	tw32_rx_mbox(TG3_RX_JMB_PROD_IDX_REG, tpr->rx_jmb_prod_idx);

	tg3_rings_reset(tp);

	/* Initialize MAC address and backoff seed. */
	__tg3_set_mac_addr(tp, false);

	/* MTU + ethernet header + FCS + optional VLAN tag */
	tw32(MAC_RX_MTU_SIZE,
	     tp->dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);

	/* The slot समय is changed by tg3_setup_phy अगर we
	 * run at gigabit with half duplex.
	 */
	val = (2 << TX_LENGTHS_IPG_CRS_SHIFT) |
	      (6 << TX_LENGTHS_IPG_SHIFT) |
	      (32 << TX_LENGTHS_SLOT_TIME_SHIFT);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762)
		val |= tr32(MAC_TX_LENGTHS) &
		       (TX_LENGTHS_JMB_FRM_LEN_MSK |
			TX_LENGTHS_CNT_DWN_VAL_MSK);

	tw32(MAC_TX_LENGTHS, val);

	/* Receive rules. */
	tw32(MAC_RCV_RULE_CFG, RCV_RULE_CFG_DEFAULT_CLASS);
	tw32(RCVLPC_CONFIG, 0x0181);

	/* Calculate RDMAC_MODE setting early, we need it to determine
	 * the RCVLPC_STATE_ENABLE mask.
	 */
	rdmac_mode = (RDMAC_MODE_ENABLE | RDMAC_MODE_TGTABORT_ENAB |
		      RDMAC_MODE_MSTABORT_ENAB | RDMAC_MODE_PARITYERR_ENAB |
		      RDMAC_MODE_ADDROFLOW_ENAB | RDMAC_MODE_FIFOOFLOW_ENAB |
		      RDMAC_MODE_FIFOURUN_ENAB | RDMAC_MODE_FIFOOREAD_ENAB |
		      RDMAC_MODE_LNGREAD_ENAB);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717)
		rdmac_mode |= RDMAC_MODE_MULT_DMA_RD_DIS;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5784 ||
	    tg3_asic_rev(tp) == ASIC_REV_5785 ||
	    tg3_asic_rev(tp) == ASIC_REV_57780)
		rdmac_mode |= RDMAC_MODE_BD_SBD_CRPT_ENAB |
			      RDMAC_MODE_MBUF_RBD_CRPT_ENAB |
			      RDMAC_MODE_MBUF_SBD_CRPT_ENAB;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5705 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5705_A0) अणु
		अगर (tg3_flag(tp, TSO_CAPABLE) &&
		    tg3_asic_rev(tp) == ASIC_REV_5705) अणु
			rdmac_mode |= RDMAC_MODE_FIFO_SIZE_128;
		पूर्ण अन्यथा अगर (!(tr32(TG3PCI_PCISTATE) & PCISTATE_BUS_SPEED_HIGH) &&
			   !tg3_flag(tp, IS_5788)) अणु
			rdmac_mode |= RDMAC_MODE_FIFO_LONG_BURST;
		पूर्ण
	पूर्ण

	अगर (tg3_flag(tp, PCI_EXPRESS))
		rdmac_mode |= RDMAC_MODE_FIFO_LONG_BURST;

	अगर (tg3_asic_rev(tp) == ASIC_REV_57766) अणु
		tp->dma_limit = 0;
		अगर (tp->dev->mtu <= ETH_DATA_LEN) अणु
			rdmac_mode |= RDMAC_MODE_JMB_2K_MMRR;
			tp->dma_limit = TG3_TX_BD_DMA_MAX_2K;
		पूर्ण
	पूर्ण

	अगर (tg3_flag(tp, HW_TSO_1) ||
	    tg3_flag(tp, HW_TSO_2) ||
	    tg3_flag(tp, HW_TSO_3))
		rdmac_mode |= RDMAC_MODE_IPV4_LSO_EN;

	अगर (tg3_flag(tp, 57765_PLUS) ||
	    tg3_asic_rev(tp) == ASIC_REV_5785 ||
	    tg3_asic_rev(tp) == ASIC_REV_57780)
		rdmac_mode |= RDMAC_MODE_IPV6_LSO_EN;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762)
		rdmac_mode |= tr32(RDMAC_MODE) & RDMAC_MODE_H2BNC_VLAN_DET;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5761 ||
	    tg3_asic_rev(tp) == ASIC_REV_5784 ||
	    tg3_asic_rev(tp) == ASIC_REV_5785 ||
	    tg3_asic_rev(tp) == ASIC_REV_57780 ||
	    tg3_flag(tp, 57765_PLUS)) अणु
		u32 tgtreg;

		अगर (tg3_asic_rev(tp) == ASIC_REV_5762)
			tgtreg = TG3_RDMA_RSRVCTRL_REG2;
		अन्यथा
			tgtreg = TG3_RDMA_RSRVCTRL_REG;

		val = tr32(tgtreg);
		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5719_A0 ||
		    tg3_asic_rev(tp) == ASIC_REV_5762) अणु
			val &= ~(TG3_RDMA_RSRVCTRL_TXMRGN_MASK |
				 TG3_RDMA_RSRVCTRL_FIFO_LWM_MASK |
				 TG3_RDMA_RSRVCTRL_FIFO_HWM_MASK);
			val |= TG3_RDMA_RSRVCTRL_TXMRGN_320B |
			       TG3_RDMA_RSRVCTRL_FIFO_LWM_1_5K |
			       TG3_RDMA_RSRVCTRL_FIFO_HWM_1_5K;
		पूर्ण
		tw32(tgtreg, val | TG3_RDMA_RSRVCTRL_FIFO_OFLW_FIX);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762) अणु
		u32 tgtreg;

		अगर (tg3_asic_rev(tp) == ASIC_REV_5762)
			tgtreg = TG3_LSO_RD_DMA_CRPTEN_CTRL2;
		अन्यथा
			tgtreg = TG3_LSO_RD_DMA_CRPTEN_CTRL;

		val = tr32(tgtreg);
		tw32(tgtreg, val |
		     TG3_LSO_RD_DMA_CRPTEN_CTRL_BLEN_BD_4K |
		     TG3_LSO_RD_DMA_CRPTEN_CTRL_BLEN_LSO_4K);
	पूर्ण

	/* Receive/send statistics. */
	अगर (tg3_flag(tp, 5750_PLUS)) अणु
		val = tr32(RCVLPC_STATS_ENABLE);
		val &= ~RCVLPC_STATSENAB_DACK_FIX;
		tw32(RCVLPC_STATS_ENABLE, val);
	पूर्ण अन्यथा अगर ((rdmac_mode & RDMAC_MODE_FIFO_SIZE_128) &&
		   tg3_flag(tp, TSO_CAPABLE)) अणु
		val = tr32(RCVLPC_STATS_ENABLE);
		val &= ~RCVLPC_STATSENAB_LNGBRST_RFIX;
		tw32(RCVLPC_STATS_ENABLE, val);
	पूर्ण अन्यथा अणु
		tw32(RCVLPC_STATS_ENABLE, 0xffffff);
	पूर्ण
	tw32(RCVLPC_STATSCTRL, RCVLPC_STATSCTRL_ENABLE);
	tw32(SNDDATAI_STATSENAB, 0xffffff);
	tw32(SNDDATAI_STATSCTRL,
	     (SNDDATAI_SCTRL_ENABLE |
	      SNDDATAI_SCTRL_FASTUPD));

	/* Setup host coalescing engine. */
	tw32(HOSTCC_MODE, 0);
	क्रम (i = 0; i < 2000; i++) अणु
		अगर (!(tr32(HOSTCC_MODE) & HOSTCC_MODE_ENABLE))
			अवरोध;
		udelay(10);
	पूर्ण

	__tg3_set_coalesce(tp, &tp->coal);

	अगर (!tg3_flag(tp, 5705_PLUS)) अणु
		/* Status/statistics block address.  See tg3_समयr,
		 * the tg3_periodic_fetch_stats call there, and
		 * tg3_get_stats to see how this works क्रम 5705/5750 chips.
		 */
		tw32(HOSTCC_STATS_BLK_HOST_ADDR + TG3_64BIT_REG_HIGH,
		     ((u64) tp->stats_mapping >> 32));
		tw32(HOSTCC_STATS_BLK_HOST_ADDR + TG3_64BIT_REG_LOW,
		     ((u64) tp->stats_mapping & 0xffffffff));
		tw32(HOSTCC_STATS_BLK_NIC_ADDR, NIC_SRAM_STATS_BLK);

		tw32(HOSTCC_STATUS_BLK_NIC_ADDR, NIC_SRAM_STATUS_BLK);

		/* Clear statistics and status block memory areas */
		क्रम (i = NIC_SRAM_STATS_BLK;
		     i < NIC_SRAM_STATUS_BLK + TG3_HW_STATUS_SIZE;
		     i += माप(u32)) अणु
			tg3_ग_लिखो_mem(tp, i, 0);
			udelay(40);
		पूर्ण
	पूर्ण

	tw32(HOSTCC_MODE, HOSTCC_MODE_ENABLE | tp->coalesce_mode);

	tw32(RCVCC_MODE, RCVCC_MODE_ENABLE | RCVCC_MODE_ATTN_ENABLE);
	tw32(RCVLPC_MODE, RCVLPC_MODE_ENABLE);
	अगर (!tg3_flag(tp, 5705_PLUS))
		tw32(RCVLSC_MODE, RCVLSC_MODE_ENABLE | RCVLSC_MODE_ATTN_ENABLE);

	अगर (tp->phy_flags & TG3_PHYFLG_MII_SERDES) अणु
		tp->phy_flags &= ~TG3_PHYFLG_PARALLEL_DETECT;
		/* reset to prevent losing 1st rx packet पूर्णांकermittently */
		tw32_f(MAC_RX_MODE, RX_MODE_RESET);
		udelay(10);
	पूर्ण

	tp->mac_mode |= MAC_MODE_TXSTAT_ENABLE | MAC_MODE_RXSTAT_ENABLE |
			MAC_MODE_TDE_ENABLE | MAC_MODE_RDE_ENABLE |
			MAC_MODE_FHDE_ENABLE;
	अगर (tg3_flag(tp, ENABLE_APE))
		tp->mac_mode |= MAC_MODE_APE_TX_EN | MAC_MODE_APE_RX_EN;
	अगर (!tg3_flag(tp, 5705_PLUS) &&
	    !(tp->phy_flags & TG3_PHYFLG_PHY_SERDES) &&
	    tg3_asic_rev(tp) != ASIC_REV_5700)
		tp->mac_mode |= MAC_MODE_LINK_POLARITY;
	tw32_f(MAC_MODE, tp->mac_mode | MAC_MODE_RXSTAT_CLEAR | MAC_MODE_TXSTAT_CLEAR);
	udelay(40);

	/* tp->grc_local_ctrl is partially set up during tg3_get_invariants().
	 * If TG3_FLAG_IS_NIC is zero, we should पढ़ो the
	 * रेजिस्टर to preserve the GPIO settings क्रम LOMs. The GPIOs,
	 * whether used as inमाला_दो or outमाला_दो, are set by boot code after
	 * reset.
	 */
	अगर (!tg3_flag(tp, IS_NIC)) अणु
		u32 gpio_mask;

		gpio_mask = GRC_LCLCTRL_GPIO_OE0 | GRC_LCLCTRL_GPIO_OE1 |
			    GRC_LCLCTRL_GPIO_OE2 | GRC_LCLCTRL_GPIO_OUTPUT0 |
			    GRC_LCLCTRL_GPIO_OUTPUT1 | GRC_LCLCTRL_GPIO_OUTPUT2;

		अगर (tg3_asic_rev(tp) == ASIC_REV_5752)
			gpio_mask |= GRC_LCLCTRL_GPIO_OE3 |
				     GRC_LCLCTRL_GPIO_OUTPUT3;

		अगर (tg3_asic_rev(tp) == ASIC_REV_5755)
			gpio_mask |= GRC_LCLCTRL_GPIO_UART_SEL;

		tp->grc_local_ctrl &= ~gpio_mask;
		tp->grc_local_ctrl |= tr32(GRC_LOCAL_CTRL) & gpio_mask;

		/* GPIO1 must be driven high क्रम eeprom ग_लिखो protect */
		अगर (tg3_flag(tp, EEPROM_WRITE_PROT))
			tp->grc_local_ctrl |= (GRC_LCLCTRL_GPIO_OE1 |
					       GRC_LCLCTRL_GPIO_OUTPUT1);
	पूर्ण
	tw32_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl);
	udelay(100);

	अगर (tg3_flag(tp, USING_MSIX)) अणु
		val = tr32(MSGINT_MODE);
		val |= MSGINT_MODE_ENABLE;
		अगर (tp->irq_cnt > 1)
			val |= MSGINT_MODE_MULTIVEC_EN;
		अगर (!tg3_flag(tp, 1SHOT_MSI))
			val |= MSGINT_MODE_ONE_SHOT_DISABLE;
		tw32(MSGINT_MODE, val);
	पूर्ण

	अगर (!tg3_flag(tp, 5705_PLUS)) अणु
		tw32_f(DMAC_MODE, DMAC_MODE_ENABLE);
		udelay(40);
	पूर्ण

	val = (WDMAC_MODE_ENABLE | WDMAC_MODE_TGTABORT_ENAB |
	       WDMAC_MODE_MSTABORT_ENAB | WDMAC_MODE_PARITYERR_ENAB |
	       WDMAC_MODE_ADDROFLOW_ENAB | WDMAC_MODE_FIFOOFLOW_ENAB |
	       WDMAC_MODE_FIFOURUN_ENAB | WDMAC_MODE_FIFOOREAD_ENAB |
	       WDMAC_MODE_LNGREAD_ENAB);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5705 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5705_A0) अणु
		अगर (tg3_flag(tp, TSO_CAPABLE) &&
		    (tg3_chip_rev_id(tp) == CHIPREV_ID_5705_A1 ||
		     tg3_chip_rev_id(tp) == CHIPREV_ID_5705_A2)) अणु
			/* nothing */
		पूर्ण अन्यथा अगर (!(tr32(TG3PCI_PCISTATE) & PCISTATE_BUS_SPEED_HIGH) &&
			   !tg3_flag(tp, IS_5788)) अणु
			val |= WDMAC_MODE_RX_ACCEL;
		पूर्ण
	पूर्ण

	/* Enable host coalescing bug fix */
	अगर (tg3_flag(tp, 5755_PLUS))
		val |= WDMAC_MODE_STATUS_TAG_FIX;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5785)
		val |= WDMAC_MODE_BURST_ALL_DATA;

	tw32_f(WDMAC_MODE, val);
	udelay(40);

	अगर (tg3_flag(tp, PCIX_MODE)) अणु
		u16 pcix_cmd;

		pci_पढ़ो_config_word(tp->pdev, tp->pcix_cap + PCI_X_CMD,
				     &pcix_cmd);
		अगर (tg3_asic_rev(tp) == ASIC_REV_5703) अणु
			pcix_cmd &= ~PCI_X_CMD_MAX_READ;
			pcix_cmd |= PCI_X_CMD_READ_2K;
		पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5704) अणु
			pcix_cmd &= ~(PCI_X_CMD_MAX_SPLIT | PCI_X_CMD_MAX_READ);
			pcix_cmd |= PCI_X_CMD_READ_2K;
		पूर्ण
		pci_ग_लिखो_config_word(tp->pdev, tp->pcix_cap + PCI_X_CMD,
				      pcix_cmd);
	पूर्ण

	tw32_f(RDMAC_MODE, rdmac_mode);
	udelay(40);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720) अणु
		क्रम (i = 0; i < TG3_NUM_RDMA_CHANNELS; i++) अणु
			अगर (tr32(TG3_RDMA_LENGTH + (i << 2)) > TG3_MAX_MTU(tp))
				अवरोध;
		पूर्ण
		अगर (i < TG3_NUM_RDMA_CHANNELS) अणु
			val = tr32(TG3_LSO_RD_DMA_CRPTEN_CTRL);
			val |= tg3_lso_rd_dma_workaround_bit(tp);
			tw32(TG3_LSO_RD_DMA_CRPTEN_CTRL, val);
			tg3_flag_set(tp, 5719_5720_RDMA_BUG);
		पूर्ण
	पूर्ण

	tw32(RCVDCC_MODE, RCVDCC_MODE_ENABLE | RCVDCC_MODE_ATTN_ENABLE);
	अगर (!tg3_flag(tp, 5705_PLUS))
		tw32(MBFREE_MODE, MBFREE_MODE_ENABLE);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5761)
		tw32(SNDDATAC_MODE,
		     SNDDATAC_MODE_ENABLE | SNDDATAC_MODE_CDELAY);
	अन्यथा
		tw32(SNDDATAC_MODE, SNDDATAC_MODE_ENABLE);

	tw32(SNDBDC_MODE, SNDBDC_MODE_ENABLE | SNDBDC_MODE_ATTN_ENABLE);
	tw32(RCVBDI_MODE, RCVBDI_MODE_ENABLE | RCVBDI_MODE_RCB_ATTN_ENAB);
	val = RCVDBDI_MODE_ENABLE | RCVDBDI_MODE_INV_RING_SZ;
	अगर (tg3_flag(tp, LRG_PROD_RING_CAP))
		val |= RCVDBDI_MODE_LRG_RING_SZ;
	tw32(RCVDBDI_MODE, val);
	tw32(SNDDATAI_MODE, SNDDATAI_MODE_ENABLE);
	अगर (tg3_flag(tp, HW_TSO_1) ||
	    tg3_flag(tp, HW_TSO_2) ||
	    tg3_flag(tp, HW_TSO_3))
		tw32(SNDDATAI_MODE, SNDDATAI_MODE_ENABLE | 0x8);
	val = SNDBDI_MODE_ENABLE | SNDBDI_MODE_ATTN_ENABLE;
	अगर (tg3_flag(tp, ENABLE_TSS))
		val |= SNDBDI_MODE_MULTI_TXQ_EN;
	tw32(SNDBDI_MODE, val);
	tw32(SNDBDS_MODE, SNDBDS_MODE_ENABLE | SNDBDS_MODE_ATTN_ENABLE);

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0) अणु
		err = tg3_load_5701_a0_firmware_fix(tp);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_57766) अणु
		/* Ignore any errors क्रम the firmware करोwnload. If करोwnload
		 * fails, the device will operate with EEE disabled
		 */
		tg3_load_57766_firmware(tp);
	पूर्ण

	अगर (tg3_flag(tp, TSO_CAPABLE)) अणु
		err = tg3_load_tso_firmware(tp);
		अगर (err)
			वापस err;
	पूर्ण

	tp->tx_mode = TX_MODE_ENABLE;

	अगर (tg3_flag(tp, 5755_PLUS) ||
	    tg3_asic_rev(tp) == ASIC_REV_5906)
		tp->tx_mode |= TX_MODE_MBUF_LOCKUP_FIX;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762) अणु
		val = TX_MODE_JMB_FRM_LEN | TX_MODE_CNT_DN_MODE;
		tp->tx_mode &= ~val;
		tp->tx_mode |= tr32(MAC_TX_MODE) & val;
	पूर्ण

	tw32_f(MAC_TX_MODE, tp->tx_mode);
	udelay(100);

	अगर (tg3_flag(tp, ENABLE_RSS)) अणु
		u32 rss_key[10];

		tg3_rss_ग_लिखो_indir_tbl(tp);

		netdev_rss_key_fill(rss_key, 10 * माप(u32));

		क्रम (i = 0; i < 10 ; i++)
			tw32(MAC_RSS_HASH_KEY_0 + i*4, rss_key[i]);
	पूर्ण

	tp->rx_mode = RX_MODE_ENABLE;
	अगर (tg3_flag(tp, 5755_PLUS))
		tp->rx_mode |= RX_MODE_IPV6_CSUM_ENABLE;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5762)
		tp->rx_mode |= RX_MODE_IPV4_FRAG_FIX;

	अगर (tg3_flag(tp, ENABLE_RSS))
		tp->rx_mode |= RX_MODE_RSS_ENABLE |
			       RX_MODE_RSS_ITBL_HASH_BITS_7 |
			       RX_MODE_RSS_IPV6_HASH_EN |
			       RX_MODE_RSS_TCP_IPV6_HASH_EN |
			       RX_MODE_RSS_IPV4_HASH_EN |
			       RX_MODE_RSS_TCP_IPV4_HASH_EN;

	tw32_f(MAC_RX_MODE, tp->rx_mode);
	udelay(10);

	tw32(MAC_LED_CTRL, tp->led_ctrl);

	tw32(MAC_MI_STAT, MAC_MI_STAT_LNKSTAT_ATTN_ENAB);
	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES) अणु
		tw32_f(MAC_RX_MODE, RX_MODE_RESET);
		udelay(10);
	पूर्ण
	tw32_f(MAC_RX_MODE, tp->rx_mode);
	udelay(10);

	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES) अणु
		अगर ((tg3_asic_rev(tp) == ASIC_REV_5704) &&
		    !(tp->phy_flags & TG3_PHYFLG_SERDES_PREEMPHASIS)) अणु
			/* Set drive transmission level to 1.2V  */
			/* only अगर the संकेत pre-emphasis bit is not set  */
			val = tr32(MAC_SERDES_CFG);
			val &= 0xfffff000;
			val |= 0x880;
			tw32(MAC_SERDES_CFG, val);
		पूर्ण
		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5703_A1)
			tw32(MAC_SERDES_CFG, 0x616000);
	पूर्ण

	/* Prevent chip from dropping frames when flow control
	 * is enabled.
	 */
	अगर (tg3_flag(tp, 57765_CLASS))
		val = 1;
	अन्यथा
		val = 2;
	tw32_f(MAC_LOW_WMARK_MAX_RX_FRAME, val);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5704 &&
	    (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)) अणु
		/* Use hardware link स्वतः-negotiation */
		tg3_flag_set(tp, HW_AUTONEG);
	पूर्ण

	अगर ((tp->phy_flags & TG3_PHYFLG_MII_SERDES) &&
	    tg3_asic_rev(tp) == ASIC_REV_5714) अणु
		u32 पंचांगp;

		पंचांगp = tr32(SERDES_RX_CTRL);
		tw32(SERDES_RX_CTRL, पंचांगp | SERDES_RX_SIG_DETECT);
		tp->grc_local_ctrl &= ~GRC_LCLCTRL_USE_EXT_SIG_DETECT;
		tp->grc_local_ctrl |= GRC_LCLCTRL_USE_SIG_DETECT;
		tw32(GRC_LOCAL_CTRL, tp->grc_local_ctrl);
	पूर्ण

	अगर (!tg3_flag(tp, USE_PHYLIB)) अणु
		अगर (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)
			tp->phy_flags &= ~TG3_PHYFLG_IS_LOW_POWER;

		err = tg3_setup_phy(tp, false);
		अगर (err)
			वापस err;

		अगर (!(tp->phy_flags & TG3_PHYFLG_PHY_SERDES) &&
		    !(tp->phy_flags & TG3_PHYFLG_IS_FET)) अणु
			u32 पंचांगp;

			/* Clear CRC stats. */
			अगर (!tg3_पढ़ोphy(tp, MII_TG3_TEST1, &पंचांगp)) अणु
				tg3_ग_लिखोphy(tp, MII_TG3_TEST1,
					     पंचांगp | MII_TG3_TEST1_CRC_EN);
				tg3_पढ़ोphy(tp, MII_TG3_RXR_COUNTERS, &पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	__tg3_set_rx_mode(tp->dev);

	/* Initialize receive rules. */
	tw32(MAC_RCV_RULE_0,  0xc2000000 & RCV_RULE_DISABLE_MASK);
	tw32(MAC_RCV_VALUE_0, 0xffffffff & RCV_RULE_DISABLE_MASK);
	tw32(MAC_RCV_RULE_1,  0x86000004 & RCV_RULE_DISABLE_MASK);
	tw32(MAC_RCV_VALUE_1, 0xffffffff & RCV_RULE_DISABLE_MASK);

	अगर (tg3_flag(tp, 5705_PLUS) && !tg3_flag(tp, 5780_CLASS))
		limit = 8;
	अन्यथा
		limit = 16;
	अगर (tg3_flag(tp, ENABLE_ASF))
		limit -= 4;
	चयन (limit) अणु
	हाल 16:
		tw32(MAC_RCV_RULE_15,  0); tw32(MAC_RCV_VALUE_15,  0);
		fallthrough;
	हाल 15:
		tw32(MAC_RCV_RULE_14,  0); tw32(MAC_RCV_VALUE_14,  0);
		fallthrough;
	हाल 14:
		tw32(MAC_RCV_RULE_13,  0); tw32(MAC_RCV_VALUE_13,  0);
		fallthrough;
	हाल 13:
		tw32(MAC_RCV_RULE_12,  0); tw32(MAC_RCV_VALUE_12,  0);
		fallthrough;
	हाल 12:
		tw32(MAC_RCV_RULE_11,  0); tw32(MAC_RCV_VALUE_11,  0);
		fallthrough;
	हाल 11:
		tw32(MAC_RCV_RULE_10,  0); tw32(MAC_RCV_VALUE_10,  0);
		fallthrough;
	हाल 10:
		tw32(MAC_RCV_RULE_9,  0); tw32(MAC_RCV_VALUE_9,  0);
		fallthrough;
	हाल 9:
		tw32(MAC_RCV_RULE_8,  0); tw32(MAC_RCV_VALUE_8,  0);
		fallthrough;
	हाल 8:
		tw32(MAC_RCV_RULE_7,  0); tw32(MAC_RCV_VALUE_7,  0);
		fallthrough;
	हाल 7:
		tw32(MAC_RCV_RULE_6,  0); tw32(MAC_RCV_VALUE_6,  0);
		fallthrough;
	हाल 6:
		tw32(MAC_RCV_RULE_5,  0); tw32(MAC_RCV_VALUE_5,  0);
		fallthrough;
	हाल 5:
		tw32(MAC_RCV_RULE_4,  0); tw32(MAC_RCV_VALUE_4,  0);
		fallthrough;
	हाल 4:
		/* tw32(MAC_RCV_RULE_3,  0); tw32(MAC_RCV_VALUE_3,  0); */
	हाल 3:
		/* tw32(MAC_RCV_RULE_2,  0); tw32(MAC_RCV_VALUE_2,  0); */
	हाल 2:
	हाल 1:

	शेष:
		अवरोध;
	पूर्ण

	अगर (tg3_flag(tp, ENABLE_APE))
		/* Write our heartbeat update पूर्णांकerval to APE. */
		tg3_ape_ग_लिखो32(tp, TG3_APE_HOST_HEARTBEAT_INT_MS,
				APE_HOST_HEARTBEAT_INT_5SEC);

	tg3_ग_लिखो_sig_post_reset(tp, RESET_KIND_INIT);

	वापस 0;
पूर्ण

/* Called at device खोलो समय to get the chip पढ़ोy क्रम
 * packet processing.  Invoked with tp->lock held.
 */
अटल पूर्णांक tg3_init_hw(काष्ठा tg3 *tp, bool reset_phy)
अणु
	/* Chip may have been just घातered on. If so, the boot code may still
	 * be running initialization. Wait क्रम it to finish to aव्योम races in
	 * accessing the hardware.
	 */
	tg3_enable_रेजिस्टर_access(tp);
	tg3_poll_fw(tp);

	tg3_चयन_घड़ीs(tp);

	tw32(TG3PCI_MEM_WIN_BASE_ADDR, 0);

	वापस tg3_reset_hw(tp, reset_phy);
पूर्ण

#अगर_घोषित CONFIG_TIGON3_HWMON
अटल व्योम tg3_sd_scan_scratchpad(काष्ठा tg3 *tp, काष्ठा tg3_ocir *ocir)
अणु
	u32 off, len = TG3_OCIR_LEN;
	पूर्णांक i;

	क्रम (i = 0, off = 0; i < TG3_SD_NUM_RECS; i++, ocir++, off += len) अणु
		tg3_ape_scratchpad_पढ़ो(tp, (u32 *) ocir, off, len);

		अगर (ocir->signature != TG3_OCIR_SIG_MAGIC ||
		    !(ocir->version_flags & TG3_OCIR_FLAG_ACTIVE))
			स_रखो(ocir, 0, len);
	पूर्ण
पूर्ण

/* sysfs attributes क्रम hwmon */
अटल sमाप_प्रकार tg3_show_temp(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा tg3 *tp = dev_get_drvdata(dev);
	u32 temperature;

	spin_lock_bh(&tp->lock);
	tg3_ape_scratchpad_पढ़ो(tp, &temperature, attr->index,
				माप(temperature));
	spin_unlock_bh(&tp->lock);
	वापस प्र_लिखो(buf, "%u\n", temperature * 1000);
पूर्ण


अटल SENSOR_DEVICE_ATTR(temp1_input, 0444, tg3_show_temp, शून्य,
			  TG3_TEMP_SENSOR_OFFSET);
अटल SENSOR_DEVICE_ATTR(temp1_crit, 0444, tg3_show_temp, शून्य,
			  TG3_TEMP_CAUTION_OFFSET);
अटल SENSOR_DEVICE_ATTR(temp1_max, 0444, tg3_show_temp, शून्य,
			  TG3_TEMP_MAX_OFFSET);

अटल काष्ठा attribute *tg3_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(tg3);

अटल व्योम tg3_hwmon_बंद(काष्ठा tg3 *tp)
अणु
	अगर (tp->hwmon_dev) अणु
		hwmon_device_unरेजिस्टर(tp->hwmon_dev);
		tp->hwmon_dev = शून्य;
	पूर्ण
पूर्ण

अटल व्योम tg3_hwmon_खोलो(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;
	u32 size = 0;
	काष्ठा pci_dev *pdev = tp->pdev;
	काष्ठा tg3_ocir ocirs[TG3_SD_NUM_RECS];

	tg3_sd_scan_scratchpad(tp, ocirs);

	क्रम (i = 0; i < TG3_SD_NUM_RECS; i++) अणु
		अगर (!ocirs[i].src_data_length)
			जारी;

		size += ocirs[i].src_hdr_length;
		size += ocirs[i].src_data_length;
	पूर्ण

	अगर (!size)
		वापस;

	tp->hwmon_dev = hwmon_device_रेजिस्टर_with_groups(&pdev->dev, "tg3",
							  tp, tg3_groups);
	अगर (IS_ERR(tp->hwmon_dev)) अणु
		tp->hwmon_dev = शून्य;
		dev_err(&pdev->dev, "Cannot register hwmon device, aborting\n");
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tg3_hwmon_बंद(काष्ठा tg3 *tp) अणु पूर्ण
अटल अंतरभूत व्योम tg3_hwmon_खोलो(काष्ठा tg3 *tp) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_TIGON3_HWMON */


#घोषणा TG3_STAT_ADD32(PSTAT, REG) \
करो अणु	u32 __val = tr32(REG); \
	(PSTAT)->low += __val; \
	अगर ((PSTAT)->low < __val) \
		(PSTAT)->high += 1; \
पूर्ण जबतक (0)

अटल व्योम tg3_periodic_fetch_stats(काष्ठा tg3 *tp)
अणु
	काष्ठा tg3_hw_stats *sp = tp->hw_stats;

	अगर (!tp->link_up)
		वापस;

	TG3_STAT_ADD32(&sp->tx_octets, MAC_TX_STATS_OCTETS);
	TG3_STAT_ADD32(&sp->tx_collisions, MAC_TX_STATS_COLLISIONS);
	TG3_STAT_ADD32(&sp->tx_xon_sent, MAC_TX_STATS_XON_SENT);
	TG3_STAT_ADD32(&sp->tx_xoff_sent, MAC_TX_STATS_XOFF_SENT);
	TG3_STAT_ADD32(&sp->tx_mac_errors, MAC_TX_STATS_MAC_ERRORS);
	TG3_STAT_ADD32(&sp->tx_single_collisions, MAC_TX_STATS_SINGLE_COLLISIONS);
	TG3_STAT_ADD32(&sp->tx_mult_collisions, MAC_TX_STATS_MULT_COLLISIONS);
	TG3_STAT_ADD32(&sp->tx_deferred, MAC_TX_STATS_DEFERRED);
	TG3_STAT_ADD32(&sp->tx_excessive_collisions, MAC_TX_STATS_EXCESSIVE_COL);
	TG3_STAT_ADD32(&sp->tx_late_collisions, MAC_TX_STATS_LATE_COL);
	TG3_STAT_ADD32(&sp->tx_ucast_packets, MAC_TX_STATS_UCAST);
	TG3_STAT_ADD32(&sp->tx_mcast_packets, MAC_TX_STATS_MCAST);
	TG3_STAT_ADD32(&sp->tx_bcast_packets, MAC_TX_STATS_BCAST);
	अगर (unlikely(tg3_flag(tp, 5719_5720_RDMA_BUG) &&
		     (sp->tx_ucast_packets.low + sp->tx_mcast_packets.low +
		      sp->tx_bcast_packets.low) > TG3_NUM_RDMA_CHANNELS)) अणु
		u32 val;

		val = tr32(TG3_LSO_RD_DMA_CRPTEN_CTRL);
		val &= ~tg3_lso_rd_dma_workaround_bit(tp);
		tw32(TG3_LSO_RD_DMA_CRPTEN_CTRL, val);
		tg3_flag_clear(tp, 5719_5720_RDMA_BUG);
	पूर्ण

	TG3_STAT_ADD32(&sp->rx_octets, MAC_RX_STATS_OCTETS);
	TG3_STAT_ADD32(&sp->rx_fragments, MAC_RX_STATS_FRAGMENTS);
	TG3_STAT_ADD32(&sp->rx_ucast_packets, MAC_RX_STATS_UCAST);
	TG3_STAT_ADD32(&sp->rx_mcast_packets, MAC_RX_STATS_MCAST);
	TG3_STAT_ADD32(&sp->rx_bcast_packets, MAC_RX_STATS_BCAST);
	TG3_STAT_ADD32(&sp->rx_fcs_errors, MAC_RX_STATS_FCS_ERRORS);
	TG3_STAT_ADD32(&sp->rx_align_errors, MAC_RX_STATS_ALIGN_ERRORS);
	TG3_STAT_ADD32(&sp->rx_xon_छोड़ो_rcvd, MAC_RX_STATS_XON_PAUSE_RECVD);
	TG3_STAT_ADD32(&sp->rx_xoff_छोड़ो_rcvd, MAC_RX_STATS_XOFF_PAUSE_RECVD);
	TG3_STAT_ADD32(&sp->rx_mac_ctrl_rcvd, MAC_RX_STATS_MAC_CTRL_RECVD);
	TG3_STAT_ADD32(&sp->rx_xoff_entered, MAC_RX_STATS_XOFF_ENTERED);
	TG3_STAT_ADD32(&sp->rx_frame_too_दीर्घ_errors, MAC_RX_STATS_FRAME_TOO_LONG);
	TG3_STAT_ADD32(&sp->rx_jabbers, MAC_RX_STATS_JABBERS);
	TG3_STAT_ADD32(&sp->rx_undersize_packets, MAC_RX_STATS_UNDERSIZE);

	TG3_STAT_ADD32(&sp->rxbds_empty, RCVLPC_NO_RCV_BD_CNT);
	अगर (tg3_asic_rev(tp) != ASIC_REV_5717 &&
	    tg3_asic_rev(tp) != ASIC_REV_5762 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5719_A0 &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5720_A0) अणु
		TG3_STAT_ADD32(&sp->rx_discards, RCVLPC_IN_DISCARDS_CNT);
	पूर्ण अन्यथा अणु
		u32 val = tr32(HOSTCC_FLOW_ATTN);
		val = (val & HOSTCC_FLOW_ATTN_MBUF_LWM) ? 1 : 0;
		अगर (val) अणु
			tw32(HOSTCC_FLOW_ATTN, HOSTCC_FLOW_ATTN_MBUF_LWM);
			sp->rx_discards.low += val;
			अगर (sp->rx_discards.low < val)
				sp->rx_discards.high += 1;
		पूर्ण
		sp->mbuf_lwm_thresh_hit = sp->rx_discards;
	पूर्ण
	TG3_STAT_ADD32(&sp->rx_errors, RCVLPC_IN_ERRORS_CNT);
पूर्ण

अटल व्योम tg3_chk_missed_msi(काष्ठा tg3 *tp)
अणु
	u32 i;

	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		अगर (tg3_has_work(tnapi)) अणु
			अगर (tnapi->last_rx_cons == tnapi->rx_rcb_ptr &&
			    tnapi->last_tx_cons == tnapi->tx_cons) अणु
				अगर (tnapi->chk_msi_cnt < 1) अणु
					tnapi->chk_msi_cnt++;
					वापस;
				पूर्ण
				tg3_msi(0, tnapi);
			पूर्ण
		पूर्ण
		tnapi->chk_msi_cnt = 0;
		tnapi->last_rx_cons = tnapi->rx_rcb_ptr;
		tnapi->last_tx_cons = tnapi->tx_cons;
	पूर्ण
पूर्ण

अटल व्योम tg3_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tg3 *tp = from_समयr(tp, t, समयr);

	spin_lock(&tp->lock);

	अगर (tp->irq_sync || tg3_flag(tp, RESET_TASK_PENDING)) अणु
		spin_unlock(&tp->lock);
		जाओ restart_समयr;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_flag(tp, 57765_CLASS))
		tg3_chk_missed_msi(tp);

	अगर (tg3_flag(tp, FLUSH_POSTED_WRITES)) अणु
		/* BCM4785: Flush posted ग_लिखोs from GbE to host memory. */
		tr32(HOSTCC_MODE);
	पूर्ण

	अगर (!tg3_flag(tp, TAGGED_STATUS)) अणु
		/* All of this garbage is because when using non-tagged
		 * IRQ status the mailbox/status_block protocol the chip
		 * uses with the cpu is race prone.
		 */
		अगर (tp->napi[0].hw_status->status & SD_STATUS_UPDATED) अणु
			tw32(GRC_LOCAL_CTRL,
			     tp->grc_local_ctrl | GRC_LCLCTRL_SETINT);
		पूर्ण अन्यथा अणु
			tw32(HOSTCC_MODE, tp->coalesce_mode |
			     HOSTCC_MODE_ENABLE | HOSTCC_MODE_NOW);
		पूर्ण

		अगर (!(tr32(WDMAC_MODE) & WDMAC_MODE_ENABLE)) अणु
			spin_unlock(&tp->lock);
			tg3_reset_task_schedule(tp);
			जाओ restart_समयr;
		पूर्ण
	पूर्ण

	/* This part only runs once per second. */
	अगर (!--tp->समयr_counter) अणु
		अगर (tg3_flag(tp, 5705_PLUS))
			tg3_periodic_fetch_stats(tp);

		अगर (tp->setlpicnt && !--tp->setlpicnt)
			tg3_phy_eee_enable(tp);

		अगर (tg3_flag(tp, USE_LINKCHG_REG)) अणु
			u32 mac_stat;
			पूर्णांक phy_event;

			mac_stat = tr32(MAC_STATUS);

			phy_event = 0;
			अगर (tp->phy_flags & TG3_PHYFLG_USE_MI_INTERRUPT) अणु
				अगर (mac_stat & MAC_STATUS_MI_INTERRUPT)
					phy_event = 1;
			पूर्ण अन्यथा अगर (mac_stat & MAC_STATUS_LNKSTATE_CHANGED)
				phy_event = 1;

			अगर (phy_event)
				tg3_setup_phy(tp, false);
		पूर्ण अन्यथा अगर (tg3_flag(tp, POLL_SERDES)) अणु
			u32 mac_stat = tr32(MAC_STATUS);
			पूर्णांक need_setup = 0;

			अगर (tp->link_up &&
			    (mac_stat & MAC_STATUS_LNKSTATE_CHANGED)) अणु
				need_setup = 1;
			पूर्ण
			अगर (!tp->link_up &&
			    (mac_stat & (MAC_STATUS_PCS_SYNCED |
					 MAC_STATUS_SIGNAL_DET))) अणु
				need_setup = 1;
			पूर्ण
			अगर (need_setup) अणु
				अगर (!tp->serdes_counter) अणु
					tw32_f(MAC_MODE,
					     (tp->mac_mode &
					      ~MAC_MODE_PORT_MODE_MASK));
					udelay(40);
					tw32_f(MAC_MODE, tp->mac_mode);
					udelay(40);
				पूर्ण
				tg3_setup_phy(tp, false);
			पूर्ण
		पूर्ण अन्यथा अगर ((tp->phy_flags & TG3_PHYFLG_MII_SERDES) &&
			   tg3_flag(tp, 5780_CLASS)) अणु
			tg3_serdes_parallel_detect(tp);
		पूर्ण अन्यथा अगर (tg3_flag(tp, POLL_CPMU_LINK)) अणु
			u32 cpmu = tr32(TG3_CPMU_STATUS);
			bool link_up = !((cpmu & TG3_CPMU_STATUS_LINK_MASK) ==
					 TG3_CPMU_STATUS_LINK_MASK);

			अगर (link_up != tp->link_up)
				tg3_setup_phy(tp, false);
		पूर्ण

		tp->समयr_counter = tp->समयr_multiplier;
	पूर्ण

	/* Heartbeat is only sent once every 2 seconds.
	 *
	 * The heartbeat is to tell the ASF firmware that the host
	 * driver is still alive.  In the event that the OS crashes,
	 * ASF needs to reset the hardware to मुक्त up the FIFO space
	 * that may be filled with rx packets destined क्रम the host.
	 * If the FIFO is full, ASF will no दीर्घer function properly.
	 *
	 * Unपूर्णांकended resets have been reported on real समय kernels
	 * where the समयr करोesn't run on समय.  Netpoll will also have
	 * same problem.
	 *
	 * The new FWCMD_NICDRV_ALIVE3 command tells the ASF firmware
	 * to check the ring condition when the heartbeat is expiring
	 * beक्रमe करोing the reset.  This will prevent most unपूर्णांकended
	 * resets.
	 */
	अगर (!--tp->asf_counter) अणु
		अगर (tg3_flag(tp, ENABLE_ASF) && !tg3_flag(tp, ENABLE_APE)) अणु
			tg3_रुको_क्रम_event_ack(tp);

			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_MBOX,
				      FWCMD_NICDRV_ALIVE3);
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_LEN_MBOX, 4);
			tg3_ग_लिखो_mem(tp, NIC_SRAM_FW_CMD_DATA_MBOX,
				      TG3_FW_UPDATE_TIMEOUT_SEC);

			tg3_generate_fw_event(tp);
		पूर्ण
		tp->asf_counter = tp->asf_multiplier;
	पूर्ण

	/* Update the APE heartbeat every 5 seconds.*/
	tg3_send_ape_heartbeat(tp, TG3_APE_HB_INTERVAL);

	spin_unlock(&tp->lock);

restart_समयr:
	tp->समयr.expires = jअगरfies + tp->समयr_offset;
	add_समयr(&tp->समयr);
पूर्ण

अटल व्योम tg3_समयr_init(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, TAGGED_STATUS) &&
	    tg3_asic_rev(tp) != ASIC_REV_5717 &&
	    !tg3_flag(tp, 57765_CLASS))
		tp->समयr_offset = HZ;
	अन्यथा
		tp->समयr_offset = HZ / 10;

	BUG_ON(tp->समयr_offset > HZ);

	tp->समयr_multiplier = (HZ / tp->समयr_offset);
	tp->asf_multiplier = (HZ / tp->समयr_offset) *
			     TG3_FW_UPDATE_FREQ_SEC;

	समयr_setup(&tp->समयr, tg3_समयr, 0);
पूर्ण

अटल व्योम tg3_समयr_start(काष्ठा tg3 *tp)
अणु
	tp->asf_counter   = tp->asf_multiplier;
	tp->समयr_counter = tp->समयr_multiplier;

	tp->समयr.expires = jअगरfies + tp->समयr_offset;
	add_समयr(&tp->समयr);
पूर्ण

अटल व्योम tg3_समयr_stop(काष्ठा tg3 *tp)
अणु
	del_समयr_sync(&tp->समयr);
पूर्ण

/* Restart hardware after configuration changes, self-test, etc.
 * Invoked with tp->lock held.
 */
अटल पूर्णांक tg3_restart_hw(काष्ठा tg3 *tp, bool reset_phy)
	__releases(tp->lock)
	__acquires(tp->lock)
अणु
	पूर्णांक err;

	err = tg3_init_hw(tp, reset_phy);
	अगर (err) अणु
		netdev_err(tp->dev,
			   "Failed to re-initialize device, aborting\n");
		tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
		tg3_full_unlock(tp);
		tg3_समयr_stop(tp);
		tp->irq_sync = 0;
		tg3_napi_enable(tp);
		dev_बंद(tp->dev);
		tg3_full_lock(tp, 0);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम tg3_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tg3 *tp = container_of(work, काष्ठा tg3, reset_task);
	पूर्णांक err;

	rtnl_lock();
	tg3_full_lock(tp, 0);

	अगर (!netअगर_running(tp->dev)) अणु
		tg3_flag_clear(tp, RESET_TASK_PENDING);
		tg3_full_unlock(tp);
		rtnl_unlock();
		वापस;
	पूर्ण

	tg3_full_unlock(tp);

	tg3_phy_stop(tp);

	tg3_netअगर_stop(tp);

	tg3_full_lock(tp, 1);

	अगर (tg3_flag(tp, TX_RECOVERY_PENDING)) अणु
		tp->ग_लिखो32_tx_mbox = tg3_ग_लिखो32_tx_mbox;
		tp->ग_लिखो32_rx_mbox = tg3_ग_लिखो_flush_reg32;
		tg3_flag_set(tp, MBOX_WRITE_REORDER);
		tg3_flag_clear(tp, TX_RECOVERY_PENDING);
	पूर्ण

	tg3_halt(tp, RESET_KIND_SHUTDOWN, 0);
	err = tg3_init_hw(tp, true);
	अगर (err) अणु
		tg3_full_unlock(tp);
		tp->irq_sync = 0;
		tg3_napi_enable(tp);
		/* Clear this flag so that tg3_reset_task_cancel() will not
		 * call cancel_work_sync() and रुको क्रमever.
		 */
		tg3_flag_clear(tp, RESET_TASK_PENDING);
		dev_बंद(tp->dev);
		जाओ out;
	पूर्ण

	tg3_netअगर_start(tp);

	tg3_full_unlock(tp);

	अगर (!err)
		tg3_phy_start(tp);

	tg3_flag_clear(tp, RESET_TASK_PENDING);
out:
	rtnl_unlock();
पूर्ण

अटल पूर्णांक tg3_request_irq(काष्ठा tg3 *tp, पूर्णांक irq_num)
अणु
	irq_handler_t fn;
	अचिन्हित दीर्घ flags;
	अक्षर *name;
	काष्ठा tg3_napi *tnapi = &tp->napi[irq_num];

	अगर (tp->irq_cnt == 1)
		name = tp->dev->name;
	अन्यथा अणु
		name = &tnapi->irq_lbl[0];
		अगर (tnapi->tx_buffers && tnapi->rx_rcb)
			snम_लिखो(name, IFNAMSIZ,
				 "%s-txrx-%d", tp->dev->name, irq_num);
		अन्यथा अगर (tnapi->tx_buffers)
			snम_लिखो(name, IFNAMSIZ,
				 "%s-tx-%d", tp->dev->name, irq_num);
		अन्यथा अगर (tnapi->rx_rcb)
			snम_लिखो(name, IFNAMSIZ,
				 "%s-rx-%d", tp->dev->name, irq_num);
		अन्यथा
			snम_लिखो(name, IFNAMSIZ,
				 "%s-%d", tp->dev->name, irq_num);
		name[IFNAMSIZ-1] = 0;
	पूर्ण

	अगर (tg3_flag(tp, USING_MSI) || tg3_flag(tp, USING_MSIX)) अणु
		fn = tg3_msi;
		अगर (tg3_flag(tp, 1SHOT_MSI))
			fn = tg3_msi_1shot;
		flags = 0;
	पूर्ण अन्यथा अणु
		fn = tg3_पूर्णांकerrupt;
		अगर (tg3_flag(tp, TAGGED_STATUS))
			fn = tg3_पूर्णांकerrupt_tagged;
		flags = IRQF_SHARED;
	पूर्ण

	वापस request_irq(tnapi->irq_vec, fn, flags, name, tnapi);
पूर्ण

अटल पूर्णांक tg3_test_पूर्णांकerrupt(काष्ठा tg3 *tp)
अणु
	काष्ठा tg3_napi *tnapi = &tp->napi[0];
	काष्ठा net_device *dev = tp->dev;
	पूर्णांक err, i, पूर्णांकr_ok = 0;
	u32 val;

	अगर (!netअगर_running(dev))
		वापस -ENODEV;

	tg3_disable_पूर्णांकs(tp);

	मुक्त_irq(tnapi->irq_vec, tnapi);

	/*
	 * Turn off MSI one shot mode.  Otherwise this test has no
	 * observable way to know whether the पूर्णांकerrupt was delivered.
	 */
	अगर (tg3_flag(tp, 57765_PLUS)) अणु
		val = tr32(MSGINT_MODE) | MSGINT_MODE_ONE_SHOT_DISABLE;
		tw32(MSGINT_MODE, val);
	पूर्ण

	err = request_irq(tnapi->irq_vec, tg3_test_isr,
			  IRQF_SHARED, dev->name, tnapi);
	अगर (err)
		वापस err;

	tnapi->hw_status->status &= ~SD_STATUS_UPDATED;
	tg3_enable_पूर्णांकs(tp);

	tw32_f(HOSTCC_MODE, tp->coalesce_mode | HOSTCC_MODE_ENABLE |
	       tnapi->coal_now);

	क्रम (i = 0; i < 5; i++) अणु
		u32 पूर्णांक_mbox, misc_host_ctrl;

		पूर्णांक_mbox = tr32_mailbox(tnapi->पूर्णांक_mbox);
		misc_host_ctrl = tr32(TG3PCI_MISC_HOST_CTRL);

		अगर ((पूर्णांक_mbox != 0) ||
		    (misc_host_ctrl & MISC_HOST_CTRL_MASK_PCI_INT)) अणु
			पूर्णांकr_ok = 1;
			अवरोध;
		पूर्ण

		अगर (tg3_flag(tp, 57765_PLUS) &&
		    tnapi->hw_status->status_tag != tnapi->last_tag)
			tw32_mailbox_f(tnapi->पूर्णांक_mbox, tnapi->last_tag << 24);

		msleep(10);
	पूर्ण

	tg3_disable_पूर्णांकs(tp);

	मुक्त_irq(tnapi->irq_vec, tnapi);

	err = tg3_request_irq(tp, 0);

	अगर (err)
		वापस err;

	अगर (पूर्णांकr_ok) अणु
		/* Reenable MSI one shot mode. */
		अगर (tg3_flag(tp, 57765_PLUS) && tg3_flag(tp, 1SHOT_MSI)) अणु
			val = tr32(MSGINT_MODE) & ~MSGINT_MODE_ONE_SHOT_DISABLE;
			tw32(MSGINT_MODE, val);
		पूर्ण
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/* Returns 0 अगर MSI test succeeds or MSI test fails and INTx mode is
 * successfully restored
 */
अटल पूर्णांक tg3_test_msi(काष्ठा tg3 *tp)
अणु
	पूर्णांक err;
	u16 pci_cmd;

	अगर (!tg3_flag(tp, USING_MSI))
		वापस 0;

	/* Turn off SERR reporting in हाल MSI terminates with Master
	 * Abort.
	 */
	pci_पढ़ो_config_word(tp->pdev, PCI_COMMAND, &pci_cmd);
	pci_ग_लिखो_config_word(tp->pdev, PCI_COMMAND,
			      pci_cmd & ~PCI_COMMAND_SERR);

	err = tg3_test_पूर्णांकerrupt(tp);

	pci_ग_लिखो_config_word(tp->pdev, PCI_COMMAND, pci_cmd);

	अगर (!err)
		वापस 0;

	/* other failures */
	अगर (err != -EIO)
		वापस err;

	/* MSI test failed, go back to INTx mode */
	netdev_warn(tp->dev, "No interrupt was generated using MSI. Switching "
		    "to INTx mode. Please report this failure to the PCI "
		    "maintainer and include system chipset information\n");

	मुक्त_irq(tp->napi[0].irq_vec, &tp->napi[0]);

	pci_disable_msi(tp->pdev);

	tg3_flag_clear(tp, USING_MSI);
	tp->napi[0].irq_vec = tp->pdev->irq;

	err = tg3_request_irq(tp, 0);
	अगर (err)
		वापस err;

	/* Need to reset the chip because the MSI cycle may have terminated
	 * with Master Abort.
	 */
	tg3_full_lock(tp, 1);

	tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
	err = tg3_init_hw(tp, true);

	tg3_full_unlock(tp);

	अगर (err)
		मुक्त_irq(tp->napi[0].irq_vec, &tp->napi[0]);

	वापस err;
पूर्ण

अटल पूर्णांक tg3_request_firmware(काष्ठा tg3 *tp)
अणु
	स्थिर काष्ठा tg3_firmware_hdr *fw_hdr;

	अगर (request_firmware(&tp->fw, tp->fw_needed, &tp->pdev->dev)) अणु
		netdev_err(tp->dev, "Failed to load firmware \"%s\"\n",
			   tp->fw_needed);
		वापस -ENOENT;
	पूर्ण

	fw_hdr = (काष्ठा tg3_firmware_hdr *)tp->fw->data;

	/* Firmware blob starts with version numbers, followed by
	 * start address and _full_ length including BSS sections
	 * (which must be दीर्घer than the actual data, of course
	 */

	tp->fw_len = be32_to_cpu(fw_hdr->len);	/* includes bss */
	अगर (tp->fw_len < (tp->fw->size - TG3_FW_HDR_LEN)) अणु
		netdev_err(tp->dev, "bogus length %d in \"%s\"\n",
			   tp->fw_len, tp->fw_needed);
		release_firmware(tp->fw);
		tp->fw = शून्य;
		वापस -EINVAL;
	पूर्ण

	/* We no दीर्घer need firmware; we have it. */
	tp->fw_needed = शून्य;
	वापस 0;
पूर्ण

अटल u32 tg3_irq_count(काष्ठा tg3 *tp)
अणु
	u32 irq_cnt = max(tp->rxq_cnt, tp->txq_cnt);

	अगर (irq_cnt > 1) अणु
		/* We want as many rx rings enabled as there are cpus.
		 * In multiqueue MSI-X mode, the first MSI-X vector
		 * only deals with link पूर्णांकerrupts, etc, so we add
		 * one to the number of vectors we are requesting.
		 */
		irq_cnt = min_t(अचिन्हित, irq_cnt + 1, tp->irq_max);
	पूर्ण

	वापस irq_cnt;
पूर्ण

अटल bool tg3_enable_msix(काष्ठा tg3 *tp)
अणु
	पूर्णांक i, rc;
	काष्ठा msix_entry msix_ent[TG3_IRQ_MAX_VECS];

	tp->txq_cnt = tp->txq_req;
	tp->rxq_cnt = tp->rxq_req;
	अगर (!tp->rxq_cnt)
		tp->rxq_cnt = netअगर_get_num_शेष_rss_queues();
	अगर (tp->rxq_cnt > tp->rxq_max)
		tp->rxq_cnt = tp->rxq_max;

	/* Disable multiple TX rings by शेष.  Simple round-robin hardware
	 * scheduling of the TX rings can cause starvation of rings with
	 * small packets when other rings have TSO or jumbo packets.
	 */
	अगर (!tp->txq_req)
		tp->txq_cnt = 1;

	tp->irq_cnt = tg3_irq_count(tp);

	क्रम (i = 0; i < tp->irq_max; i++) अणु
		msix_ent[i].entry  = i;
		msix_ent[i].vector = 0;
	पूर्ण

	rc = pci_enable_msix_range(tp->pdev, msix_ent, 1, tp->irq_cnt);
	अगर (rc < 0) अणु
		वापस false;
	पूर्ण अन्यथा अगर (rc < tp->irq_cnt) अणु
		netdev_notice(tp->dev, "Requested %d MSI-X vectors, received %d\n",
			      tp->irq_cnt, rc);
		tp->irq_cnt = rc;
		tp->rxq_cnt = max(rc - 1, 1);
		अगर (tp->txq_cnt)
			tp->txq_cnt = min(tp->rxq_cnt, tp->txq_max);
	पूर्ण

	क्रम (i = 0; i < tp->irq_max; i++)
		tp->napi[i].irq_vec = msix_ent[i].vector;

	अगर (netअगर_set_real_num_rx_queues(tp->dev, tp->rxq_cnt)) अणु
		pci_disable_msix(tp->pdev);
		वापस false;
	पूर्ण

	अगर (tp->irq_cnt == 1)
		वापस true;

	tg3_flag_set(tp, ENABLE_RSS);

	अगर (tp->txq_cnt > 1)
		tg3_flag_set(tp, ENABLE_TSS);

	netअगर_set_real_num_tx_queues(tp->dev, tp->txq_cnt);

	वापस true;
पूर्ण

अटल व्योम tg3_पूर्णांकs_init(काष्ठा tg3 *tp)
अणु
	अगर ((tg3_flag(tp, SUPPORT_MSI) || tg3_flag(tp, SUPPORT_MSIX)) &&
	    !tg3_flag(tp, TAGGED_STATUS)) अणु
		/* All MSI supporting chips should support tagged
		 * status.  Assert that this is the हाल.
		 */
		netdev_warn(tp->dev,
			    "MSI without TAGGED_STATUS? Not using MSI\n");
		जाओ defcfg;
	पूर्ण

	अगर (tg3_flag(tp, SUPPORT_MSIX) && tg3_enable_msix(tp))
		tg3_flag_set(tp, USING_MSIX);
	अन्यथा अगर (tg3_flag(tp, SUPPORT_MSI) && pci_enable_msi(tp->pdev) == 0)
		tg3_flag_set(tp, USING_MSI);

	अगर (tg3_flag(tp, USING_MSI) || tg3_flag(tp, USING_MSIX)) अणु
		u32 msi_mode = tr32(MSGINT_MODE);
		अगर (tg3_flag(tp, USING_MSIX) && tp->irq_cnt > 1)
			msi_mode |= MSGINT_MODE_MULTIVEC_EN;
		अगर (!tg3_flag(tp, 1SHOT_MSI))
			msi_mode |= MSGINT_MODE_ONE_SHOT_DISABLE;
		tw32(MSGINT_MODE, msi_mode | MSGINT_MODE_ENABLE);
	पूर्ण
defcfg:
	अगर (!tg3_flag(tp, USING_MSIX)) अणु
		tp->irq_cnt = 1;
		tp->napi[0].irq_vec = tp->pdev->irq;
	पूर्ण

	अगर (tp->irq_cnt == 1) अणु
		tp->txq_cnt = 1;
		tp->rxq_cnt = 1;
		netअगर_set_real_num_tx_queues(tp->dev, 1);
		netअगर_set_real_num_rx_queues(tp->dev, 1);
	पूर्ण
पूर्ण

अटल व्योम tg3_पूर्णांकs_fini(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, USING_MSIX))
		pci_disable_msix(tp->pdev);
	अन्यथा अगर (tg3_flag(tp, USING_MSI))
		pci_disable_msi(tp->pdev);
	tg3_flag_clear(tp, USING_MSI);
	tg3_flag_clear(tp, USING_MSIX);
	tg3_flag_clear(tp, ENABLE_RSS);
	tg3_flag_clear(tp, ENABLE_TSS);
पूर्ण

अटल पूर्णांक tg3_start(काष्ठा tg3 *tp, bool reset_phy, bool test_irq,
		     bool init)
अणु
	काष्ठा net_device *dev = tp->dev;
	पूर्णांक i, err;

	/*
	 * Setup पूर्णांकerrupts first so we know how
	 * many NAPI resources to allocate
	 */
	tg3_पूर्णांकs_init(tp);

	tg3_rss_check_indir_tbl(tp);

	/* The placement of this call is tied
	 * to the setup and use of Host TX descriptors.
	 */
	err = tg3_alloc_consistent(tp);
	अगर (err)
		जाओ out_पूर्णांकs_fini;

	tg3_napi_init(tp);

	tg3_napi_enable(tp);

	क्रम (i = 0; i < tp->irq_cnt; i++) अणु
		err = tg3_request_irq(tp, i);
		अगर (err) अणु
			क्रम (i--; i >= 0; i--) अणु
				काष्ठा tg3_napi *tnapi = &tp->napi[i];

				मुक्त_irq(tnapi->irq_vec, tnapi);
			पूर्ण
			जाओ out_napi_fini;
		पूर्ण
	पूर्ण

	tg3_full_lock(tp, 0);

	अगर (init)
		tg3_ape_driver_state_change(tp, RESET_KIND_INIT);

	err = tg3_init_hw(tp, reset_phy);
	अगर (err) अणु
		tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
		tg3_मुक्त_rings(tp);
	पूर्ण

	tg3_full_unlock(tp);

	अगर (err)
		जाओ out_मुक्त_irq;

	अगर (test_irq && tg3_flag(tp, USING_MSI)) अणु
		err = tg3_test_msi(tp);

		अगर (err) अणु
			tg3_full_lock(tp, 0);
			tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
			tg3_मुक्त_rings(tp);
			tg3_full_unlock(tp);

			जाओ out_napi_fini;
		पूर्ण

		अगर (!tg3_flag(tp, 57765_PLUS) && tg3_flag(tp, USING_MSI)) अणु
			u32 val = tr32(PCIE_TRANSACTION_CFG);

			tw32(PCIE_TRANSACTION_CFG,
			     val | PCIE_TRANS_CFG_1SHOT_MSI);
		पूर्ण
	पूर्ण

	tg3_phy_start(tp);

	tg3_hwmon_खोलो(tp);

	tg3_full_lock(tp, 0);

	tg3_समयr_start(tp);
	tg3_flag_set(tp, INIT_COMPLETE);
	tg3_enable_पूर्णांकs(tp);

	tg3_ptp_resume(tp);

	tg3_full_unlock(tp);

	netअगर_tx_start_all_queues(dev);

	/*
	 * Reset loopback feature अगर it was turned on जबतक the device was करोwn
	 * make sure that it's installed properly now.
	 */
	अगर (dev->features & NETIF_F_LOOPBACK)
		tg3_set_loopback(dev, dev->features);

	वापस 0;

out_मुक्त_irq:
	क्रम (i = tp->irq_cnt - 1; i >= 0; i--) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];
		मुक्त_irq(tnapi->irq_vec, tnapi);
	पूर्ण

out_napi_fini:
	tg3_napi_disable(tp);
	tg3_napi_fini(tp);
	tg3_मुक्त_consistent(tp);

out_पूर्णांकs_fini:
	tg3_पूर्णांकs_fini(tp);

	वापस err;
पूर्ण

अटल व्योम tg3_stop(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	tg3_reset_task_cancel(tp);
	tg3_netअगर_stop(tp);

	tg3_समयr_stop(tp);

	tg3_hwmon_बंद(tp);

	tg3_phy_stop(tp);

	tg3_full_lock(tp, 1);

	tg3_disable_पूर्णांकs(tp);

	tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
	tg3_मुक्त_rings(tp);
	tg3_flag_clear(tp, INIT_COMPLETE);

	tg3_full_unlock(tp);

	क्रम (i = tp->irq_cnt - 1; i >= 0; i--) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];
		मुक्त_irq(tnapi->irq_vec, tnapi);
	पूर्ण

	tg3_पूर्णांकs_fini(tp);

	tg3_napi_fini(tp);

	tg3_मुक्त_consistent(tp);
पूर्ण

अटल पूर्णांक tg3_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक err;

	अगर (tp->pcierr_recovery) अणु
		netdev_err(dev, "Failed to open device. PCI error recovery "
			   "in progress\n");
		वापस -EAGAIN;
	पूर्ण

	अगर (tp->fw_needed) अणु
		err = tg3_request_firmware(tp);
		अगर (tg3_asic_rev(tp) == ASIC_REV_57766) अणु
			अगर (err) अणु
				netdev_warn(tp->dev, "EEE capability disabled\n");
				tp->phy_flags &= ~TG3_PHYFLG_EEE_CAP;
			पूर्ण अन्यथा अगर (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP)) अणु
				netdev_warn(tp->dev, "EEE capability restored\n");
				tp->phy_flags |= TG3_PHYFLG_EEE_CAP;
			पूर्ण
		पूर्ण अन्यथा अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0) अणु
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (err) अणु
			netdev_warn(tp->dev, "TSO capability disabled\n");
			tg3_flag_clear(tp, TSO_CAPABLE);
		पूर्ण अन्यथा अगर (!tg3_flag(tp, TSO_CAPABLE)) अणु
			netdev_notice(tp->dev, "TSO capability restored\n");
			tg3_flag_set(tp, TSO_CAPABLE);
		पूर्ण
	पूर्ण

	tg3_carrier_off(tp);

	err = tg3_घातer_up(tp);
	अगर (err)
		वापस err;

	tg3_full_lock(tp, 0);

	tg3_disable_पूर्णांकs(tp);
	tg3_flag_clear(tp, INIT_COMPLETE);

	tg3_full_unlock(tp);

	err = tg3_start(tp,
			!(tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN),
			true, true);
	अगर (err) अणु
		tg3_frob_aux_घातer(tp, false);
		pci_set_घातer_state(tp->pdev, PCI_D3hot);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tg3_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (tp->pcierr_recovery) अणु
		netdev_err(dev, "Failed to close device. PCI error recovery "
			   "in progress\n");
		वापस -EAGAIN;
	पूर्ण

	tg3_stop(tp);

	अगर (pci_device_is_present(tp->pdev)) अणु
		tg3_घातer_करोwn_prepare(tp);

		tg3_carrier_off(tp);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u64 get_stat64(tg3_stat64_t *val)
अणु
       वापस ((u64)val->high << 32) | ((u64)val->low);
पूर्ण

अटल u64 tg3_calc_crc_errors(काष्ठा tg3 *tp)
अणु
	काष्ठा tg3_hw_stats *hw_stats = tp->hw_stats;

	अगर (!(tp->phy_flags & TG3_PHYFLG_PHY_SERDES) &&
	    (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	     tg3_asic_rev(tp) == ASIC_REV_5701)) अणु
		u32 val;

		अगर (!tg3_पढ़ोphy(tp, MII_TG3_TEST1, &val)) अणु
			tg3_ग_लिखोphy(tp, MII_TG3_TEST1,
				     val | MII_TG3_TEST1_CRC_EN);
			tg3_पढ़ोphy(tp, MII_TG3_RXR_COUNTERS, &val);
		पूर्ण अन्यथा
			val = 0;

		tp->phy_crc_errors += val;

		वापस tp->phy_crc_errors;
	पूर्ण

	वापस get_stat64(&hw_stats->rx_fcs_errors);
पूर्ण

#घोषणा ESTAT_ADD(member) \
	estats->member =	old_estats->member + \
				get_stat64(&hw_stats->member)

अटल व्योम tg3_get_estats(काष्ठा tg3 *tp, काष्ठा tg3_ethtool_stats *estats)
अणु
	काष्ठा tg3_ethtool_stats *old_estats = &tp->estats_prev;
	काष्ठा tg3_hw_stats *hw_stats = tp->hw_stats;

	ESTAT_ADD(rx_octets);
	ESTAT_ADD(rx_fragments);
	ESTAT_ADD(rx_ucast_packets);
	ESTAT_ADD(rx_mcast_packets);
	ESTAT_ADD(rx_bcast_packets);
	ESTAT_ADD(rx_fcs_errors);
	ESTAT_ADD(rx_align_errors);
	ESTAT_ADD(rx_xon_छोड़ो_rcvd);
	ESTAT_ADD(rx_xoff_छोड़ो_rcvd);
	ESTAT_ADD(rx_mac_ctrl_rcvd);
	ESTAT_ADD(rx_xoff_entered);
	ESTAT_ADD(rx_frame_too_दीर्घ_errors);
	ESTAT_ADD(rx_jabbers);
	ESTAT_ADD(rx_undersize_packets);
	ESTAT_ADD(rx_in_length_errors);
	ESTAT_ADD(rx_out_length_errors);
	ESTAT_ADD(rx_64_or_less_octet_packets);
	ESTAT_ADD(rx_65_to_127_octet_packets);
	ESTAT_ADD(rx_128_to_255_octet_packets);
	ESTAT_ADD(rx_256_to_511_octet_packets);
	ESTAT_ADD(rx_512_to_1023_octet_packets);
	ESTAT_ADD(rx_1024_to_1522_octet_packets);
	ESTAT_ADD(rx_1523_to_2047_octet_packets);
	ESTAT_ADD(rx_2048_to_4095_octet_packets);
	ESTAT_ADD(rx_4096_to_8191_octet_packets);
	ESTAT_ADD(rx_8192_to_9022_octet_packets);

	ESTAT_ADD(tx_octets);
	ESTAT_ADD(tx_collisions);
	ESTAT_ADD(tx_xon_sent);
	ESTAT_ADD(tx_xoff_sent);
	ESTAT_ADD(tx_flow_control);
	ESTAT_ADD(tx_mac_errors);
	ESTAT_ADD(tx_single_collisions);
	ESTAT_ADD(tx_mult_collisions);
	ESTAT_ADD(tx_deferred);
	ESTAT_ADD(tx_excessive_collisions);
	ESTAT_ADD(tx_late_collisions);
	ESTAT_ADD(tx_collide_2बार);
	ESTAT_ADD(tx_collide_3बार);
	ESTAT_ADD(tx_collide_4बार);
	ESTAT_ADD(tx_collide_5बार);
	ESTAT_ADD(tx_collide_6बार);
	ESTAT_ADD(tx_collide_7बार);
	ESTAT_ADD(tx_collide_8बार);
	ESTAT_ADD(tx_collide_9बार);
	ESTAT_ADD(tx_collide_10बार);
	ESTAT_ADD(tx_collide_11बार);
	ESTAT_ADD(tx_collide_12बार);
	ESTAT_ADD(tx_collide_13बार);
	ESTAT_ADD(tx_collide_14बार);
	ESTAT_ADD(tx_collide_15बार);
	ESTAT_ADD(tx_ucast_packets);
	ESTAT_ADD(tx_mcast_packets);
	ESTAT_ADD(tx_bcast_packets);
	ESTAT_ADD(tx_carrier_sense_errors);
	ESTAT_ADD(tx_discards);
	ESTAT_ADD(tx_errors);

	ESTAT_ADD(dma_ग_लिखोq_full);
	ESTAT_ADD(dma_ग_लिखो_prioq_full);
	ESTAT_ADD(rxbds_empty);
	ESTAT_ADD(rx_discards);
	ESTAT_ADD(rx_errors);
	ESTAT_ADD(rx_threshold_hit);

	ESTAT_ADD(dma_पढ़ोq_full);
	ESTAT_ADD(dma_पढ़ो_prioq_full);
	ESTAT_ADD(tx_comp_queue_full);

	ESTAT_ADD(ring_set_send_prod_index);
	ESTAT_ADD(ring_status_update);
	ESTAT_ADD(nic_irqs);
	ESTAT_ADD(nic_aव्योमed_irqs);
	ESTAT_ADD(nic_tx_threshold_hit);

	ESTAT_ADD(mbuf_lwm_thresh_hit);
पूर्ण

अटल व्योम tg3_get_nstats(काष्ठा tg3 *tp, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा rtnl_link_stats64 *old_stats = &tp->net_stats_prev;
	काष्ठा tg3_hw_stats *hw_stats = tp->hw_stats;

	stats->rx_packets = old_stats->rx_packets +
		get_stat64(&hw_stats->rx_ucast_packets) +
		get_stat64(&hw_stats->rx_mcast_packets) +
		get_stat64(&hw_stats->rx_bcast_packets);

	stats->tx_packets = old_stats->tx_packets +
		get_stat64(&hw_stats->tx_ucast_packets) +
		get_stat64(&hw_stats->tx_mcast_packets) +
		get_stat64(&hw_stats->tx_bcast_packets);

	stats->rx_bytes = old_stats->rx_bytes +
		get_stat64(&hw_stats->rx_octets);
	stats->tx_bytes = old_stats->tx_bytes +
		get_stat64(&hw_stats->tx_octets);

	stats->rx_errors = old_stats->rx_errors +
		get_stat64(&hw_stats->rx_errors);
	stats->tx_errors = old_stats->tx_errors +
		get_stat64(&hw_stats->tx_errors) +
		get_stat64(&hw_stats->tx_mac_errors) +
		get_stat64(&hw_stats->tx_carrier_sense_errors) +
		get_stat64(&hw_stats->tx_discards);

	stats->multicast = old_stats->multicast +
		get_stat64(&hw_stats->rx_mcast_packets);
	stats->collisions = old_stats->collisions +
		get_stat64(&hw_stats->tx_collisions);

	stats->rx_length_errors = old_stats->rx_length_errors +
		get_stat64(&hw_stats->rx_frame_too_दीर्घ_errors) +
		get_stat64(&hw_stats->rx_undersize_packets);

	stats->rx_frame_errors = old_stats->rx_frame_errors +
		get_stat64(&hw_stats->rx_align_errors);
	stats->tx_पातed_errors = old_stats->tx_पातed_errors +
		get_stat64(&hw_stats->tx_discards);
	stats->tx_carrier_errors = old_stats->tx_carrier_errors +
		get_stat64(&hw_stats->tx_carrier_sense_errors);

	stats->rx_crc_errors = old_stats->rx_crc_errors +
		tg3_calc_crc_errors(tp);

	stats->rx_missed_errors = old_stats->rx_missed_errors +
		get_stat64(&hw_stats->rx_discards);

	stats->rx_dropped = tp->rx_dropped;
	stats->tx_dropped = tp->tx_dropped;
पूर्ण

अटल पूर्णांक tg3_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस TG3_REG_BLK_SIZE;
पूर्ण

अटल व्योम tg3_get_regs(काष्ठा net_device *dev,
		काष्ठा ethtool_regs *regs, व्योम *_p)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	regs->version = 0;

	स_रखो(_p, 0, TG3_REG_BLK_SIZE);

	अगर (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)
		वापस;

	tg3_full_lock(tp, 0);

	tg3_dump_legacy_regs(tp, (u32 *)_p);

	tg3_full_unlock(tp);
पूर्ण

अटल पूर्णांक tg3_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	वापस tp->nvram_size;
पूर्ण

अटल पूर्णांक tg3_get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक ret, cpmu_restore = 0;
	u8  *pd;
	u32 i, offset, len, b_offset, b_count, cpmu_val = 0;
	__be32 val;

	अगर (tg3_flag(tp, NO_NVRAM))
		वापस -EINVAL;

	offset = eeprom->offset;
	len = eeprom->len;
	eeprom->len = 0;

	eeprom->magic = TG3_EEPROM_MAGIC;

	/* Override घड़ी, link aware and link idle modes */
	अगर (tg3_flag(tp, CPMU_PRESENT)) अणु
		cpmu_val = tr32(TG3_CPMU_CTRL);
		अगर (cpmu_val & (CPMU_CTRL_LINK_AWARE_MODE |
				CPMU_CTRL_LINK_IDLE_MODE)) अणु
			tw32(TG3_CPMU_CTRL, cpmu_val &
					    ~(CPMU_CTRL_LINK_AWARE_MODE |
					     CPMU_CTRL_LINK_IDLE_MODE));
			cpmu_restore = 1;
		पूर्ण
	पूर्ण
	tg3_override_clk(tp);

	अगर (offset & 3) अणु
		/* adjusपंचांगents to start on required 4 byte boundary */
		b_offset = offset & 3;
		b_count = 4 - b_offset;
		अगर (b_count > len) अणु
			/* i.e. offset=1 len=2 */
			b_count = len;
		पूर्ण
		ret = tg3_nvram_पढ़ो_be32(tp, offset-b_offset, &val);
		अगर (ret)
			जाओ eeprom_करोne;
		स_नकल(data, ((अक्षर *)&val) + b_offset, b_count);
		len -= b_count;
		offset += b_count;
		eeprom->len += b_count;
	पूर्ण

	/* पढ़ो bytes up to the last 4 byte boundary */
	pd = &data[eeprom->len];
	क्रम (i = 0; i < (len - (len & 3)); i += 4) अणु
		ret = tg3_nvram_पढ़ो_be32(tp, offset + i, &val);
		अगर (ret) अणु
			अगर (i)
				i -= 4;
			eeprom->len += i;
			जाओ eeprom_करोne;
		पूर्ण
		स_नकल(pd + i, &val, 4);
		अगर (need_resched()) अणु
			अगर (संकेत_pending(current)) अणु
				eeprom->len += i;
				ret = -EINTR;
				जाओ eeprom_करोne;
			पूर्ण
			cond_resched();
		पूर्ण
	पूर्ण
	eeprom->len += i;

	अगर (len & 3) अणु
		/* पढ़ो last bytes not ending on 4 byte boundary */
		pd = &data[eeprom->len];
		b_count = len & 3;
		b_offset = offset + len - b_count;
		ret = tg3_nvram_पढ़ो_be32(tp, b_offset, &val);
		अगर (ret)
			जाओ eeprom_करोne;
		स_नकल(pd, &val, b_count);
		eeprom->len += b_count;
	पूर्ण
	ret = 0;

eeprom_करोne:
	/* Restore घड़ी, link aware and link idle modes */
	tg3_restore_clk(tp);
	अगर (cpmu_restore)
		tw32(TG3_CPMU_CTRL, cpmu_val);

	वापस ret;
पूर्ण

अटल पूर्णांक tg3_set_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक ret;
	u32 offset, len, b_offset, odd_len;
	u8 *buf;
	__be32 start = 0, end;

	अगर (tg3_flag(tp, NO_NVRAM) ||
	    eeprom->magic != TG3_EEPROM_MAGIC)
		वापस -EINVAL;

	offset = eeprom->offset;
	len = eeprom->len;

	अगर ((b_offset = (offset & 3))) अणु
		/* adjusपंचांगents to start on required 4 byte boundary */
		ret = tg3_nvram_पढ़ो_be32(tp, offset-b_offset, &start);
		अगर (ret)
			वापस ret;
		len += b_offset;
		offset &= ~3;
		अगर (len < 4)
			len = 4;
	पूर्ण

	odd_len = 0;
	अगर (len & 3) अणु
		/* adjusपंचांगents to end on required 4 byte boundary */
		odd_len = 1;
		len = (len + 3) & ~3;
		ret = tg3_nvram_पढ़ो_be32(tp, offset+len-4, &end);
		अगर (ret)
			वापस ret;
	पूर्ण

	buf = data;
	अगर (b_offset || odd_len) अणु
		buf = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
		अगर (b_offset)
			स_नकल(buf, &start, 4);
		अगर (odd_len)
			स_नकल(buf+len-4, &end, 4);
		स_नकल(buf + b_offset, data, eeprom->len);
	पूर्ण

	ret = tg3_nvram_ग_लिखो_block(tp, offset, len, buf);

	अगर (buf != data)
		kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक tg3_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	u32 supported, advertising;

	अगर (tg3_flag(tp, USE_PHYLIB)) अणु
		काष्ठा phy_device *phydev;
		अगर (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
			वापस -EAGAIN;
		phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);
		phy_ethtool_ksettings_get(phydev, cmd);

		वापस 0;
	पूर्ण

	supported = (SUPPORTED_Autoneg);

	अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY))
		supported |= (SUPPORTED_1000baseT_Half |
			      SUPPORTED_1000baseT_Full);

	अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) अणु
		supported |= (SUPPORTED_100baseT_Half |
			      SUPPORTED_100baseT_Full |
			      SUPPORTED_10baseT_Half |
			      SUPPORTED_10baseT_Full |
			      SUPPORTED_TP);
		cmd->base.port = PORT_TP;
	पूर्ण अन्यथा अणु
		supported |= SUPPORTED_FIBRE;
		cmd->base.port = PORT_FIBRE;
	पूर्ण
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	advertising = tp->link_config.advertising;
	अगर (tg3_flag(tp, PAUSE_AUTONEG)) अणु
		अगर (tp->link_config.flowctrl & FLOW_CTRL_RX) अणु
			अगर (tp->link_config.flowctrl & FLOW_CTRL_TX) अणु
				advertising |= ADVERTISED_Pause;
			पूर्ण अन्यथा अणु
				advertising |= ADVERTISED_Pause |
					ADVERTISED_Asym_Pause;
			पूर्ण
		पूर्ण अन्यथा अगर (tp->link_config.flowctrl & FLOW_CTRL_TX) अणु
			advertising |= ADVERTISED_Asym_Pause;
		पूर्ण
	पूर्ण
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	अगर (netअगर_running(dev) && tp->link_up) अणु
		cmd->base.speed = tp->link_config.active_speed;
		cmd->base.duplex = tp->link_config.active_duplex;
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.lp_advertising,
			tp->link_config.rmt_adv);

		अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) अणु
			अगर (tp->phy_flags & TG3_PHYFLG_MDIX_STATE)
				cmd->base.eth_tp_mdix = ETH_TP_MDI_X;
			अन्यथा
				cmd->base.eth_tp_mdix = ETH_TP_MDI;
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
	पूर्ण
	cmd->base.phy_address = tp->phy_addr;
	cmd->base.स्वतःneg = tp->link_config.स्वतःneg;
	वापस 0;
पूर्ण

अटल पूर्णांक tg3_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	u32 advertising;

	अगर (tg3_flag(tp, USE_PHYLIB)) अणु
		काष्ठा phy_device *phydev;
		अगर (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
			वापस -EAGAIN;
		phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);
		वापस phy_ethtool_ksettings_set(phydev, cmd);
	पूर्ण

	अगर (cmd->base.स्वतःneg != AUTONEG_ENABLE &&
	    cmd->base.स्वतःneg != AUTONEG_DISABLE)
		वापस -EINVAL;

	अगर (cmd->base.स्वतःneg == AUTONEG_DISABLE &&
	    cmd->base.duplex != DUPLEX_FULL &&
	    cmd->base.duplex != DUPLEX_HALF)
		वापस -EINVAL;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		u32 mask = ADVERTISED_Autoneg |
			   ADVERTISED_Pause |
			   ADVERTISED_Asym_Pause;

		अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY))
			mask |= ADVERTISED_1000baseT_Half |
				ADVERTISED_1000baseT_Full;

		अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES))
			mask |= ADVERTISED_100baseT_Half |
				ADVERTISED_100baseT_Full |
				ADVERTISED_10baseT_Half |
				ADVERTISED_10baseT_Full |
				ADVERTISED_TP;
		अन्यथा
			mask |= ADVERTISED_FIBRE;

		अगर (advertising & ~mask)
			वापस -EINVAL;

		mask &= (ADVERTISED_1000baseT_Half |
			 ADVERTISED_1000baseT_Full |
			 ADVERTISED_100baseT_Half |
			 ADVERTISED_100baseT_Full |
			 ADVERTISED_10baseT_Half |
			 ADVERTISED_10baseT_Full);

		advertising &= mask;
	पूर्ण अन्यथा अणु
		अगर (tp->phy_flags & TG3_PHYFLG_ANY_SERDES) अणु
			अगर (speed != SPEED_1000)
				वापस -EINVAL;

			अगर (cmd->base.duplex != DUPLEX_FULL)
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			अगर (speed != SPEED_100 &&
			    speed != SPEED_10)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	tg3_full_lock(tp, 0);

	tp->link_config.स्वतःneg = cmd->base.स्वतःneg;
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		tp->link_config.advertising = (advertising |
					      ADVERTISED_Autoneg);
		tp->link_config.speed = SPEED_UNKNOWN;
		tp->link_config.duplex = DUPLEX_UNKNOWN;
	पूर्ण अन्यथा अणु
		tp->link_config.advertising = 0;
		tp->link_config.speed = speed;
		tp->link_config.duplex = cmd->base.duplex;
	पूर्ण

	tp->phy_flags |= TG3_PHYFLG_USER_CONFIGURED;

	tg3_warn_mgmt_link_flap(tp);

	अगर (netअगर_running(dev))
		tg3_setup_phy(tp, true);

	tg3_full_unlock(tp);

	वापस 0;
पूर्ण

अटल व्योम tg3_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));
	strlcpy(info->fw_version, tp->fw_ver, माप(info->fw_version));
	strlcpy(info->bus_info, pci_name(tp->pdev), माप(info->bus_info));
पूर्ण

अटल व्योम tg3_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (tg3_flag(tp, WOL_CAP) && device_can_wakeup(&tp->pdev->dev))
		wol->supported = WAKE_MAGIC;
	अन्यथा
		wol->supported = 0;
	wol->wolopts = 0;
	अगर (tg3_flag(tp, WOL_ENABLE) && device_can_wakeup(&tp->pdev->dev))
		wol->wolopts = WAKE_MAGIC;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक tg3_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	काष्ठा device *dp = &tp->pdev->dev;

	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;
	अगर ((wol->wolopts & WAKE_MAGIC) &&
	    !(tg3_flag(tp, WOL_CAP) && device_can_wakeup(dp)))
		वापस -EINVAL;

	device_set_wakeup_enable(dp, wol->wolopts & WAKE_MAGIC);

	अगर (device_may_wakeup(dp))
		tg3_flag_set(tp, WOL_ENABLE);
	अन्यथा
		tg3_flag_clear(tp, WOL_ENABLE);

	वापस 0;
पूर्ण

अटल u32 tg3_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	वापस tp->msg_enable;
पूर्ण

अटल व्योम tg3_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	tp->msg_enable = value;
पूर्ण

अटल पूर्णांक tg3_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक r;

	अगर (!netअगर_running(dev))
		वापस -EAGAIN;

	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)
		वापस -EINVAL;

	tg3_warn_mgmt_link_flap(tp);

	अगर (tg3_flag(tp, USE_PHYLIB)) अणु
		अगर (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
			वापस -EAGAIN;
		r = phy_start_aneg(mdiobus_get_phy(tp->mdio_bus, tp->phy_addr));
	पूर्ण अन्यथा अणु
		u32 bmcr;

		spin_lock_bh(&tp->lock);
		r = -EINVAL;
		tg3_पढ़ोphy(tp, MII_BMCR, &bmcr);
		अगर (!tg3_पढ़ोphy(tp, MII_BMCR, &bmcr) &&
		    ((bmcr & BMCR_ANENABLE) ||
		     (tp->phy_flags & TG3_PHYFLG_PARALLEL_DETECT))) अणु
			tg3_ग_लिखोphy(tp, MII_BMCR, bmcr | BMCR_ANRESTART |
						   BMCR_ANENABLE);
			r = 0;
		पूर्ण
		spin_unlock_bh(&tp->lock);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम tg3_get_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	ering->rx_max_pending = tp->rx_std_ring_mask;
	अगर (tg3_flag(tp, JUMBO_RING_ENABLE))
		ering->rx_jumbo_max_pending = tp->rx_jmb_ring_mask;
	अन्यथा
		ering->rx_jumbo_max_pending = 0;

	ering->tx_max_pending = TG3_TX_RING_SIZE - 1;

	ering->rx_pending = tp->rx_pending;
	अगर (tg3_flag(tp, JUMBO_RING_ENABLE))
		ering->rx_jumbo_pending = tp->rx_jumbo_pending;
	अन्यथा
		ering->rx_jumbo_pending = 0;

	ering->tx_pending = tp->napi[0].tx_pending;
पूर्ण

अटल पूर्णांक tg3_set_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक i, irq_sync = 0, err = 0;
	bool reset_phy = false;

	अगर ((ering->rx_pending > tp->rx_std_ring_mask) ||
	    (ering->rx_jumbo_pending > tp->rx_jmb_ring_mask) ||
	    (ering->tx_pending > TG3_TX_RING_SIZE - 1) ||
	    (ering->tx_pending <= MAX_SKB_FRAGS) ||
	    (tg3_flag(tp, TSO_BUG) &&
	     (ering->tx_pending <= (MAX_SKB_FRAGS * 3))))
		वापस -EINVAL;

	अगर (netअगर_running(dev)) अणु
		tg3_phy_stop(tp);
		tg3_netअगर_stop(tp);
		irq_sync = 1;
	पूर्ण

	tg3_full_lock(tp, irq_sync);

	tp->rx_pending = ering->rx_pending;

	अगर (tg3_flag(tp, MAX_RXPEND_64) &&
	    tp->rx_pending > 63)
		tp->rx_pending = 63;

	अगर (tg3_flag(tp, JUMBO_RING_ENABLE))
		tp->rx_jumbo_pending = ering->rx_jumbo_pending;

	क्रम (i = 0; i < tp->irq_max; i++)
		tp->napi[i].tx_pending = ering->tx_pending;

	अगर (netअगर_running(dev)) अणु
		tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
		/* Reset PHY to aव्योम PHY lock up */
		अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
		    tg3_asic_rev(tp) == ASIC_REV_5719 ||
		    tg3_asic_rev(tp) == ASIC_REV_5720)
			reset_phy = true;

		err = tg3_restart_hw(tp, reset_phy);
		अगर (!err)
			tg3_netअगर_start(tp);
	पूर्ण

	tg3_full_unlock(tp);

	अगर (irq_sync && !err)
		tg3_phy_start(tp);

	वापस err;
पूर्ण

अटल व्योम tg3_get_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	eछोड़ो->स्वतःneg = !!tg3_flag(tp, PAUSE_AUTONEG);

	अगर (tp->link_config.flowctrl & FLOW_CTRL_RX)
		eछोड़ो->rx_छोड़ो = 1;
	अन्यथा
		eछोड़ो->rx_छोड़ो = 0;

	अगर (tp->link_config.flowctrl & FLOW_CTRL_TX)
		eछोड़ो->tx_छोड़ो = 1;
	अन्यथा
		eछोड़ो->tx_छोड़ो = 0;
पूर्ण

अटल पूर्णांक tg3_set_छोड़ोparam(काष्ठा net_device *dev, काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक err = 0;
	bool reset_phy = false;

	अगर (tp->link_config.स्वतःneg == AUTONEG_ENABLE)
		tg3_warn_mgmt_link_flap(tp);

	अगर (tg3_flag(tp, USE_PHYLIB)) अणु
		काष्ठा phy_device *phydev;

		phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);

		अगर (!phy_validate_छोड़ो(phydev, eछोड़ो))
			वापस -EINVAL;

		tp->link_config.flowctrl = 0;
		phy_set_asym_छोड़ो(phydev, eछोड़ो->rx_छोड़ो, eछोड़ो->tx_छोड़ो);
		अगर (eछोड़ो->rx_छोड़ो) अणु
			tp->link_config.flowctrl |= FLOW_CTRL_RX;

			अगर (eछोड़ो->tx_छोड़ो) अणु
				tp->link_config.flowctrl |= FLOW_CTRL_TX;
			पूर्ण
		पूर्ण अन्यथा अगर (eछोड़ो->tx_छोड़ो) अणु
			tp->link_config.flowctrl |= FLOW_CTRL_TX;
		पूर्ण

		अगर (eछोड़ो->स्वतःneg)
			tg3_flag_set(tp, PAUSE_AUTONEG);
		अन्यथा
			tg3_flag_clear(tp, PAUSE_AUTONEG);

		अगर (tp->phy_flags & TG3_PHYFLG_IS_CONNECTED) अणु
			अगर (phydev->स्वतःneg) अणु
				/* phy_set_asym_छोड़ो() will
				 * renegotiate the link to inक्रमm our
				 * link partner of our flow control
				 * settings, even अगर the flow control
				 * is क्रमced.  Let tg3_adjust_link()
				 * करो the final flow control setup.
				 */
				वापस 0;
			पूर्ण

			अगर (!eछोड़ो->स्वतःneg)
				tg3_setup_flow_control(tp, 0, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक irq_sync = 0;

		अगर (netअगर_running(dev)) अणु
			tg3_netअगर_stop(tp);
			irq_sync = 1;
		पूर्ण

		tg3_full_lock(tp, irq_sync);

		अगर (eछोड़ो->स्वतःneg)
			tg3_flag_set(tp, PAUSE_AUTONEG);
		अन्यथा
			tg3_flag_clear(tp, PAUSE_AUTONEG);
		अगर (eछोड़ो->rx_छोड़ो)
			tp->link_config.flowctrl |= FLOW_CTRL_RX;
		अन्यथा
			tp->link_config.flowctrl &= ~FLOW_CTRL_RX;
		अगर (eछोड़ो->tx_छोड़ो)
			tp->link_config.flowctrl |= FLOW_CTRL_TX;
		अन्यथा
			tp->link_config.flowctrl &= ~FLOW_CTRL_TX;

		अगर (netअगर_running(dev)) अणु
			tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
			/* Reset PHY to aव्योम PHY lock up */
			अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
			    tg3_asic_rev(tp) == ASIC_REV_5719 ||
			    tg3_asic_rev(tp) == ASIC_REV_5720)
				reset_phy = true;

			err = tg3_restart_hw(tp, reset_phy);
			अगर (!err)
				tg3_netअगर_start(tp);
		पूर्ण

		tg3_full_unlock(tp);
	पूर्ण

	tp->phy_flags |= TG3_PHYFLG_USER_CONFIGURED;

	वापस err;
पूर्ण

अटल पूर्णांक tg3_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस TG3_NUM_TEST;
	हाल ETH_SS_STATS:
		वापस TG3_NUM_STATS;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
			 u32 *rules __always_unused)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (!tg3_flag(tp, SUPPORT_MSIX))
		वापस -EOPNOTSUPP;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		अगर (netअगर_running(tp->dev))
			info->data = tp->rxq_cnt;
		अन्यथा अणु
			info->data = num_online_cpus();
			अगर (info->data > TG3_RSS_MAX_NUM_QS)
				info->data = TG3_RSS_MAX_NUM_QS;
		पूर्ण

		वापस 0;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 tg3_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	u32 size = 0;
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (tg3_flag(tp, SUPPORT_MSIX))
		size = TG3_RSS_INसूची_TBL_SIZE;

	वापस size;
पूर्ण

अटल पूर्णांक tg3_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key, u8 *hfunc)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (!indir)
		वापस 0;

	क्रम (i = 0; i < TG3_RSS_INसूची_TBL_SIZE; i++)
		indir[i] = tp->rss_ind_tbl[i];

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir, स्थिर u8 *key,
			स्थिर u8 hfunc)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	माप_प्रकार i;

	/* We require at least one supported parameter to be changed and no
	 * change in any of the unsupported parameters
	 */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;

	अगर (!indir)
		वापस 0;

	क्रम (i = 0; i < TG3_RSS_INसूची_TBL_SIZE; i++)
		tp->rss_ind_tbl[i] = indir[i];

	अगर (!netअगर_running(dev) || !tg3_flag(tp, ENABLE_RSS))
		वापस 0;

	/* It is legal to ग_लिखो the indirection
	 * table जबतक the device is running.
	 */
	tg3_full_lock(tp, 0);
	tg3_rss_ग_लिखो_indir_tbl(tp);
	tg3_full_unlock(tp);

	वापस 0;
पूर्ण

अटल व्योम tg3_get_channels(काष्ठा net_device *dev,
			     काष्ठा ethtool_channels *channel)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	u32 deflt_qs = netअगर_get_num_शेष_rss_queues();

	channel->max_rx = tp->rxq_max;
	channel->max_tx = tp->txq_max;

	अगर (netअगर_running(dev)) अणु
		channel->rx_count = tp->rxq_cnt;
		channel->tx_count = tp->txq_cnt;
	पूर्ण अन्यथा अणु
		अगर (tp->rxq_req)
			channel->rx_count = tp->rxq_req;
		अन्यथा
			channel->rx_count = min(deflt_qs, tp->rxq_max);

		अगर (tp->txq_req)
			channel->tx_count = tp->txq_req;
		अन्यथा
			channel->tx_count = min(deflt_qs, tp->txq_max);
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_set_channels(काष्ठा net_device *dev,
			    काष्ठा ethtool_channels *channel)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (!tg3_flag(tp, SUPPORT_MSIX))
		वापस -EOPNOTSUPP;

	अगर (channel->rx_count > tp->rxq_max ||
	    channel->tx_count > tp->txq_max)
		वापस -EINVAL;

	tp->rxq_req = channel->rx_count;
	tp->txq_req = channel->tx_count;

	अगर (!netअगर_running(dev))
		वापस 0;

	tg3_stop(tp);

	tg3_carrier_off(tp);

	tg3_start(tp, true, false, false);

	वापस 0;
पूर्ण

अटल व्योम tg3_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buf, &ethtool_stats_keys, माप(ethtool_stats_keys));
		अवरोध;
	हाल ETH_SS_TEST:
		स_नकल(buf, &ethtool_test_keys, माप(ethtool_test_keys));
		अवरोध;
	शेष:
		WARN_ON(1);	/* we need a WARN() */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_set_phys_id(काष्ठा net_device *dev,
			    क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 1;	/* cycle on/off once per second */

	हाल ETHTOOL_ID_ON:
		tw32(MAC_LED_CTRL, LED_CTRL_LNKLED_OVERRIDE |
		     LED_CTRL_1000MBPS_ON |
		     LED_CTRL_100MBPS_ON |
		     LED_CTRL_10MBPS_ON |
		     LED_CTRL_TRAFFIC_OVERRIDE |
		     LED_CTRL_TRAFFIC_BLINK |
		     LED_CTRL_TRAFFIC_LED);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		tw32(MAC_LED_CTRL, LED_CTRL_LNKLED_OVERRIDE |
		     LED_CTRL_TRAFFIC_OVERRIDE);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		tw32(MAC_LED_CTRL, tp->led_ctrl);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tg3_get_ethtool_stats(काष्ठा net_device *dev,
				   काष्ठा ethtool_stats *estats, u64 *पंचांगp_stats)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (tp->hw_stats)
		tg3_get_estats(tp, (काष्ठा tg3_ethtool_stats *)पंचांगp_stats);
	अन्यथा
		स_रखो(पंचांगp_stats, 0, माप(काष्ठा tg3_ethtool_stats));
पूर्ण

अटल __be32 *tg3_vpd_पढ़ोblock(काष्ठा tg3 *tp, u32 *vpdlen)
अणु
	पूर्णांक i;
	__be32 *buf;
	u32 offset = 0, len = 0;
	u32 magic, val;

	अगर (tg3_flag(tp, NO_NVRAM) || tg3_nvram_पढ़ो(tp, 0, &magic))
		वापस शून्य;

	अगर (magic == TG3_EEPROM_MAGIC) अणु
		क्रम (offset = TG3_NVM_सूची_START;
		     offset < TG3_NVM_सूची_END;
		     offset += TG3_NVM_सूचीENT_SIZE) अणु
			अगर (tg3_nvram_पढ़ो(tp, offset, &val))
				वापस शून्य;

			अगर ((val >> TG3_NVM_सूचीTYPE_SHIFT) ==
			    TG3_NVM_सूचीTYPE_EXTVPD)
				अवरोध;
		पूर्ण

		अगर (offset != TG3_NVM_सूची_END) अणु
			len = (val & TG3_NVM_सूचीTYPE_LENMSK) * 4;
			अगर (tg3_nvram_पढ़ो(tp, offset + 4, &offset))
				वापस शून्य;

			offset = tg3_nvram_logical_addr(tp, offset);
		पूर्ण

		अगर (!offset || !len) अणु
			offset = TG3_NVM_VPD_OFF;
			len = TG3_NVM_VPD_LEN;
		पूर्ण
	पूर्ण अन्यथा अणु
		len = TG3_NVM_PCI_VPD_MAX_LEN;
	पूर्ण

	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस शून्य;

	अगर (magic == TG3_EEPROM_MAGIC) अणु
		क्रम (i = 0; i < len; i += 4) अणु
			/* The data is in little-endian क्रमmat in NVRAM.
			 * Use the big-endian पढ़ो routines to preserve
			 * the byte order as it exists in NVRAM.
			 */
			अगर (tg3_nvram_पढ़ो_be32(tp, offset + i, &buf[i/4]))
				जाओ error;
		पूर्ण
		*vpdlen = len;
	पूर्ण अन्यथा अणु
		sमाप_प्रकार cnt;

		cnt = pci_पढ़ो_vpd(tp->pdev, 0, len, (u8 *)buf);
		अगर (cnt < 0)
			जाओ error;
		*vpdlen = cnt;
	पूर्ण

	वापस buf;

error:
	kमुक्त(buf);
	वापस शून्य;
पूर्ण

#घोषणा NVRAM_TEST_SIZE 0x100
#घोषणा NVRAM_SELFBOOT_FORMAT1_0_SIZE	0x14
#घोषणा NVRAM_SELFBOOT_FORMAT1_2_SIZE	0x18
#घोषणा NVRAM_SELFBOOT_FORMAT1_3_SIZE	0x1c
#घोषणा NVRAM_SELFBOOT_FORMAT1_4_SIZE	0x20
#घोषणा NVRAM_SELFBOOT_FORMAT1_5_SIZE	0x24
#घोषणा NVRAM_SELFBOOT_FORMAT1_6_SIZE	0x50
#घोषणा NVRAM_SELFBOOT_HW_SIZE 0x20
#घोषणा NVRAM_SELFBOOT_DATA_SIZE 0x1c

अटल पूर्णांक tg3_test_nvram(काष्ठा tg3 *tp)
अणु
	u32 csum, magic, len;
	__be32 *buf;
	पूर्णांक i, j, k, err = 0, size;

	अगर (tg3_flag(tp, NO_NVRAM))
		वापस 0;

	अगर (tg3_nvram_पढ़ो(tp, 0, &magic) != 0)
		वापस -EIO;

	अगर (magic == TG3_EEPROM_MAGIC)
		size = NVRAM_TEST_SIZE;
	अन्यथा अगर ((magic & TG3_EEPROM_MAGIC_FW_MSK) == TG3_EEPROM_MAGIC_FW) अणु
		अगर ((magic & TG3_EEPROM_SB_FORMAT_MASK) ==
		    TG3_EEPROM_SB_FORMAT_1) अणु
			चयन (magic & TG3_EEPROM_SB_REVISION_MASK) अणु
			हाल TG3_EEPROM_SB_REVISION_0:
				size = NVRAM_SELFBOOT_FORMAT1_0_SIZE;
				अवरोध;
			हाल TG3_EEPROM_SB_REVISION_2:
				size = NVRAM_SELFBOOT_FORMAT1_2_SIZE;
				अवरोध;
			हाल TG3_EEPROM_SB_REVISION_3:
				size = NVRAM_SELFBOOT_FORMAT1_3_SIZE;
				अवरोध;
			हाल TG3_EEPROM_SB_REVISION_4:
				size = NVRAM_SELFBOOT_FORMAT1_4_SIZE;
				अवरोध;
			हाल TG3_EEPROM_SB_REVISION_5:
				size = NVRAM_SELFBOOT_FORMAT1_5_SIZE;
				अवरोध;
			हाल TG3_EEPROM_SB_REVISION_6:
				size = NVRAM_SELFBOOT_FORMAT1_6_SIZE;
				अवरोध;
			शेष:
				वापस -EIO;
			पूर्ण
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर ((magic & TG3_EEPROM_MAGIC_HW_MSK) == TG3_EEPROM_MAGIC_HW)
		size = NVRAM_SELFBOOT_HW_SIZE;
	अन्यथा
		वापस -EIO;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	err = -EIO;
	क्रम (i = 0, j = 0; i < size; i += 4, j++) अणु
		err = tg3_nvram_पढ़ो_be32(tp, i, &buf[j]);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (i < size)
		जाओ out;

	/* Selfboot क्रमmat */
	magic = be32_to_cpu(buf[0]);
	अगर ((magic & TG3_EEPROM_MAGIC_FW_MSK) ==
	    TG3_EEPROM_MAGIC_FW) अणु
		u8 *buf8 = (u8 *) buf, csum8 = 0;

		अगर ((magic & TG3_EEPROM_SB_REVISION_MASK) ==
		    TG3_EEPROM_SB_REVISION_2) अणु
			/* For rev 2, the csum करोesn't include the MBA. */
			क्रम (i = 0; i < TG3_EEPROM_SB_F1R2_MBA_OFF; i++)
				csum8 += buf8[i];
			क्रम (i = TG3_EEPROM_SB_F1R2_MBA_OFF + 4; i < size; i++)
				csum8 += buf8[i];
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < size; i++)
				csum8 += buf8[i];
		पूर्ण

		अगर (csum8 == 0) अणु
			err = 0;
			जाओ out;
		पूर्ण

		err = -EIO;
		जाओ out;
	पूर्ण

	अगर ((magic & TG3_EEPROM_MAGIC_HW_MSK) ==
	    TG3_EEPROM_MAGIC_HW) अणु
		u8 data[NVRAM_SELFBOOT_DATA_SIZE];
		u8 parity[NVRAM_SELFBOOT_DATA_SIZE];
		u8 *buf8 = (u8 *) buf;

		/* Separate the parity bits and the data bytes.  */
		क्रम (i = 0, j = 0, k = 0; i < NVRAM_SELFBOOT_HW_SIZE; i++) अणु
			अगर ((i == 0) || (i == 8)) अणु
				पूर्णांक l;
				u8 msk;

				क्रम (l = 0, msk = 0x80; l < 7; l++, msk >>= 1)
					parity[k++] = buf8[i] & msk;
				i++;
			पूर्ण अन्यथा अगर (i == 16) अणु
				पूर्णांक l;
				u8 msk;

				क्रम (l = 0, msk = 0x20; l < 6; l++, msk >>= 1)
					parity[k++] = buf8[i] & msk;
				i++;

				क्रम (l = 0, msk = 0x80; l < 8; l++, msk >>= 1)
					parity[k++] = buf8[i] & msk;
				i++;
			पूर्ण
			data[j++] = buf8[i];
		पूर्ण

		err = -EIO;
		क्रम (i = 0; i < NVRAM_SELFBOOT_DATA_SIZE; i++) अणु
			u8 hw8 = hweight8(data[i]);

			अगर ((hw8 & 0x1) && parity[i])
				जाओ out;
			अन्यथा अगर (!(hw8 & 0x1) && !parity[i])
				जाओ out;
		पूर्ण
		err = 0;
		जाओ out;
	पूर्ण

	err = -EIO;

	/* Bootstrap checksum at offset 0x10 */
	csum = calc_crc((अचिन्हित अक्षर *) buf, 0x10);
	अगर (csum != le32_to_cpu(buf[0x10/4]))
		जाओ out;

	/* Manufacturing block starts at offset 0x74, checksum at 0xfc */
	csum = calc_crc((अचिन्हित अक्षर *) &buf[0x74/4], 0x88);
	अगर (csum != le32_to_cpu(buf[0xfc/4]))
		जाओ out;

	kमुक्त(buf);

	buf = tg3_vpd_पढ़ोblock(tp, &len);
	अगर (!buf)
		वापस -ENOMEM;

	i = pci_vpd_find_tag((u8 *)buf, len, PCI_VPD_LRDT_RO_DATA);
	अगर (i > 0) अणु
		j = pci_vpd_lrdt_size(&((u8 *)buf)[i]);
		अगर (j < 0)
			जाओ out;

		अगर (i + PCI_VPD_LRDT_TAG_SIZE + j > len)
			जाओ out;

		i += PCI_VPD_LRDT_TAG_SIZE;
		j = pci_vpd_find_info_keyword((u8 *)buf, i, j,
					      PCI_VPD_RO_KEYWORD_CHKSUM);
		अगर (j > 0) अणु
			u8 csum8 = 0;

			j += PCI_VPD_INFO_FLD_HDR_SIZE;

			क्रम (i = 0; i <= j; i++)
				csum8 += ((u8 *)buf)[i];

			अगर (csum8)
				जाओ out;
		पूर्ण
	पूर्ण

	err = 0;

out:
	kमुक्त(buf);
	वापस err;
पूर्ण

#घोषणा TG3_SERDES_TIMEOUT_SEC	2
#घोषणा TG3_COPPER_TIMEOUT_SEC	6

अटल पूर्णांक tg3_test_link(काष्ठा tg3 *tp)
अणु
	पूर्णांक i, max;

	अगर (!netअगर_running(tp->dev))
		वापस -ENODEV;

	अगर (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
		max = TG3_SERDES_TIMEOUT_SEC;
	अन्यथा
		max = TG3_COPPER_TIMEOUT_SEC;

	क्रम (i = 0; i < max; i++) अणु
		अगर (tp->link_up)
			वापस 0;

		अगर (msleep_पूर्णांकerruptible(1000))
			अवरोध;
	पूर्ण

	वापस -EIO;
पूर्ण

/* Only test the commonly used रेजिस्टरs */
अटल पूर्णांक tg3_test_रेजिस्टरs(काष्ठा tg3 *tp)
अणु
	पूर्णांक i, is_5705, is_5750;
	u32 offset, पढ़ो_mask, ग_लिखो_mask, val, save_val, पढ़ो_val;
	अटल काष्ठा अणु
		u16 offset;
		u16 flags;
#घोषणा TG3_FL_5705	0x1
#घोषणा TG3_FL_NOT_5705	0x2
#घोषणा TG3_FL_NOT_5788	0x4
#घोषणा TG3_FL_NOT_5750	0x8
		u32 पढ़ो_mask;
		u32 ग_लिखो_mask;
	पूर्ण reg_tbl[] = अणु
		/* MAC Control Registers */
		अणु MAC_MODE, TG3_FL_NOT_5705,
			0x00000000, 0x00ef6f8c पूर्ण,
		अणु MAC_MODE, TG3_FL_5705,
			0x00000000, 0x01ef6b8c पूर्ण,
		अणु MAC_STATUS, TG3_FL_NOT_5705,
			0x03800107, 0x00000000 पूर्ण,
		अणु MAC_STATUS, TG3_FL_5705,
			0x03800100, 0x00000000 पूर्ण,
		अणु MAC_ADDR_0_HIGH, 0x0000,
			0x00000000, 0x0000ffff पूर्ण,
		अणु MAC_ADDR_0_LOW, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु MAC_RX_MTU_SIZE, 0x0000,
			0x00000000, 0x0000ffff पूर्ण,
		अणु MAC_TX_MODE, 0x0000,
			0x00000000, 0x00000070 पूर्ण,
		अणु MAC_TX_LENGTHS, 0x0000,
			0x00000000, 0x00003fff पूर्ण,
		अणु MAC_RX_MODE, TG3_FL_NOT_5705,
			0x00000000, 0x000007fc पूर्ण,
		अणु MAC_RX_MODE, TG3_FL_5705,
			0x00000000, 0x000007dc पूर्ण,
		अणु MAC_HASH_REG_0, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु MAC_HASH_REG_1, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु MAC_HASH_REG_2, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु MAC_HASH_REG_3, 0x0000,
			0x00000000, 0xffffffff पूर्ण,

		/* Receive Data and Receive BD Initiator Control Registers. */
		अणु RCVDBDI_JUMBO_BD+0, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु RCVDBDI_JUMBO_BD+4, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु RCVDBDI_JUMBO_BD+8, TG3_FL_NOT_5705,
			0x00000000, 0x00000003 पूर्ण,
		अणु RCVDBDI_JUMBO_BD+0xc, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु RCVDBDI_STD_BD+0, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु RCVDBDI_STD_BD+4, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु RCVDBDI_STD_BD+8, 0x0000,
			0x00000000, 0xffff0002 पूर्ण,
		अणु RCVDBDI_STD_BD+0xc, 0x0000,
			0x00000000, 0xffffffff पूर्ण,

		/* Receive BD Initiator Control Registers. */
		अणु RCVBDI_STD_THRESH, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु RCVBDI_STD_THRESH, TG3_FL_5705,
			0x00000000, 0x000003ff पूर्ण,
		अणु RCVBDI_JUMBO_THRESH, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,

		/* Host Coalescing Control Registers. */
		अणु HOSTCC_MODE, TG3_FL_NOT_5705,
			0x00000000, 0x00000004 पूर्ण,
		अणु HOSTCC_MODE, TG3_FL_5705,
			0x00000000, 0x000000f6 पूर्ण,
		अणु HOSTCC_RXCOL_TICKS, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_RXCOL_TICKS, TG3_FL_5705,
			0x00000000, 0x000003ff पूर्ण,
		अणु HOSTCC_TXCOL_TICKS, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_TXCOL_TICKS, TG3_FL_5705,
			0x00000000, 0x000003ff पूर्ण,
		अणु HOSTCC_RXMAX_FRAMES, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_RXMAX_FRAMES, TG3_FL_5705 | TG3_FL_NOT_5788,
			0x00000000, 0x000000ff पूर्ण,
		अणु HOSTCC_TXMAX_FRAMES, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_TXMAX_FRAMES, TG3_FL_5705 | TG3_FL_NOT_5788,
			0x00000000, 0x000000ff पूर्ण,
		अणु HOSTCC_RXCOAL_TICK_INT, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_TXCOAL_TICK_INT, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_RXCOAL_MAXF_INT, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_RXCOAL_MAXF_INT, TG3_FL_5705 | TG3_FL_NOT_5788,
			0x00000000, 0x000000ff पूर्ण,
		अणु HOSTCC_TXCOAL_MAXF_INT, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_TXCOAL_MAXF_INT, TG3_FL_5705 | TG3_FL_NOT_5788,
			0x00000000, 0x000000ff पूर्ण,
		अणु HOSTCC_STAT_COAL_TICKS, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_STATS_BLK_HOST_ADDR, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_STATS_BLK_HOST_ADDR+4, TG3_FL_NOT_5705,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_STATUS_BLK_HOST_ADDR, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_STATUS_BLK_HOST_ADDR+4, 0x0000,
			0x00000000, 0xffffffff पूर्ण,
		अणु HOSTCC_STATS_BLK_NIC_ADDR, 0x0000,
			0xffffffff, 0x00000000 पूर्ण,
		अणु HOSTCC_STATUS_BLK_NIC_ADDR, 0x0000,
			0xffffffff, 0x00000000 पूर्ण,

		/* Buffer Manager Control Registers. */
		अणु BUFMGR_MB_POOL_ADDR, TG3_FL_NOT_5750,
			0x00000000, 0x007fff80 पूर्ण,
		अणु BUFMGR_MB_POOL_SIZE, TG3_FL_NOT_5750,
			0x00000000, 0x007fffff पूर्ण,
		अणु BUFMGR_MB_RDMA_LOW_WATER, 0x0000,
			0x00000000, 0x0000003f पूर्ण,
		अणु BUFMGR_MB_MACRX_LOW_WATER, 0x0000,
			0x00000000, 0x000001ff पूर्ण,
		अणु BUFMGR_MB_HIGH_WATER, 0x0000,
			0x00000000, 0x000001ff पूर्ण,
		अणु BUFMGR_DMA_DESC_POOL_ADDR, TG3_FL_NOT_5705,
			0xffffffff, 0x00000000 पूर्ण,
		अणु BUFMGR_DMA_DESC_POOL_SIZE, TG3_FL_NOT_5705,
			0xffffffff, 0x00000000 पूर्ण,

		/* Mailbox Registers */
		अणु GRCMBOX_RCVSTD_PROD_IDX+4, 0x0000,
			0x00000000, 0x000001ff पूर्ण,
		अणु GRCMBOX_RCVJUMBO_PROD_IDX+4, TG3_FL_NOT_5705,
			0x00000000, 0x000001ff पूर्ण,
		अणु GRCMBOX_RCVRET_CON_IDX_0+4, 0x0000,
			0x00000000, 0x000007ff पूर्ण,
		अणु GRCMBOX_SNDHOST_PROD_IDX_0+4, 0x0000,
			0x00000000, 0x000001ff पूर्ण,

		अणु 0xffff, 0x0000, 0x00000000, 0x00000000 पूर्ण,
	पूर्ण;

	is_5705 = is_5750 = 0;
	अगर (tg3_flag(tp, 5705_PLUS)) अणु
		is_5705 = 1;
		अगर (tg3_flag(tp, 5750_PLUS))
			is_5750 = 1;
	पूर्ण

	क्रम (i = 0; reg_tbl[i].offset != 0xffff; i++) अणु
		अगर (is_5705 && (reg_tbl[i].flags & TG3_FL_NOT_5705))
			जारी;

		अगर (!is_5705 && (reg_tbl[i].flags & TG3_FL_5705))
			जारी;

		अगर (tg3_flag(tp, IS_5788) &&
		    (reg_tbl[i].flags & TG3_FL_NOT_5788))
			जारी;

		अगर (is_5750 && (reg_tbl[i].flags & TG3_FL_NOT_5750))
			जारी;

		offset = (u32) reg_tbl[i].offset;
		पढ़ो_mask = reg_tbl[i].पढ़ो_mask;
		ग_लिखो_mask = reg_tbl[i].ग_लिखो_mask;

		/* Save the original रेजिस्टर content */
		save_val = tr32(offset);

		/* Determine the पढ़ो-only value. */
		पढ़ो_val = save_val & पढ़ो_mask;

		/* Write zero to the रेजिस्टर, then make sure the पढ़ो-only bits
		 * are not changed and the पढ़ो/ग_लिखो bits are all zeros.
		 */
		tw32(offset, 0);

		val = tr32(offset);

		/* Test the पढ़ो-only and पढ़ो/ग_लिखो bits. */
		अगर (((val & पढ़ो_mask) != पढ़ो_val) || (val & ग_लिखो_mask))
			जाओ out;

		/* Write ones to all the bits defined by RdMask and WrMask, then
		 * make sure the पढ़ो-only bits are not changed and the
		 * पढ़ो/ग_लिखो bits are all ones.
		 */
		tw32(offset, पढ़ो_mask | ग_लिखो_mask);

		val = tr32(offset);

		/* Test the पढ़ो-only bits. */
		अगर ((val & पढ़ो_mask) != पढ़ो_val)
			जाओ out;

		/* Test the पढ़ो/ग_लिखो bits. */
		अगर ((val & ग_लिखो_mask) != ग_लिखो_mask)
			जाओ out;

		tw32(offset, save_val);
	पूर्ण

	वापस 0;

out:
	अगर (netअगर_msg_hw(tp))
		netdev_err(tp->dev,
			   "Register test failed at offset %x\n", offset);
	tw32(offset, save_val);
	वापस -EIO;
पूर्ण

अटल पूर्णांक tg3_करो_mem_test(काष्ठा tg3 *tp, u32 offset, u32 len)
अणु
	अटल स्थिर u32 test_pattern[] = अणु 0x00000000, 0xffffffff, 0xaa55a55a पूर्ण;
	पूर्णांक i;
	u32 j;

	क्रम (i = 0; i < ARRAY_SIZE(test_pattern); i++) अणु
		क्रम (j = 0; j < len; j += 4) अणु
			u32 val;

			tg3_ग_लिखो_mem(tp, offset + j, test_pattern[i]);
			tg3_पढ़ो_mem(tp, offset + j, &val);
			अगर (val != test_pattern[i])
				वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tg3_test_memory(काष्ठा tg3 *tp)
अणु
	अटल काष्ठा mem_entry अणु
		u32 offset;
		u32 len;
	पूर्ण mem_tbl_570x[] = अणु
		अणु 0x00000000, 0x00b50पूर्ण,
		अणु 0x00002000, 0x1c000पूर्ण,
		अणु 0xffffffff, 0x00000पूर्ण
	पूर्ण, mem_tbl_5705[] = अणु
		अणु 0x00000100, 0x0000cपूर्ण,
		अणु 0x00000200, 0x00008पूर्ण,
		अणु 0x00004000, 0x00800पूर्ण,
		अणु 0x00006000, 0x01000पूर्ण,
		अणु 0x00008000, 0x02000पूर्ण,
		अणु 0x00010000, 0x0e000पूर्ण,
		अणु 0xffffffff, 0x00000पूर्ण
	पूर्ण, mem_tbl_5755[] = अणु
		अणु 0x00000200, 0x00008पूर्ण,
		अणु 0x00004000, 0x00800पूर्ण,
		अणु 0x00006000, 0x00800पूर्ण,
		अणु 0x00008000, 0x02000पूर्ण,
		अणु 0x00010000, 0x0c000पूर्ण,
		अणु 0xffffffff, 0x00000पूर्ण
	पूर्ण, mem_tbl_5906[] = अणु
		अणु 0x00000200, 0x00008पूर्ण,
		अणु 0x00004000, 0x00400पूर्ण,
		अणु 0x00006000, 0x00400पूर्ण,
		अणु 0x00008000, 0x01000पूर्ण,
		अणु 0x00010000, 0x01000पूर्ण,
		अणु 0xffffffff, 0x00000पूर्ण
	पूर्ण, mem_tbl_5717[] = अणु
		अणु 0x00000200, 0x00008पूर्ण,
		अणु 0x00010000, 0x0a000पूर्ण,
		अणु 0x00020000, 0x13c00पूर्ण,
		अणु 0xffffffff, 0x00000पूर्ण
	पूर्ण, mem_tbl_57765[] = अणु
		अणु 0x00000200, 0x00008पूर्ण,
		अणु 0x00004000, 0x00800पूर्ण,
		अणु 0x00006000, 0x09800पूर्ण,
		अणु 0x00010000, 0x0a000पूर्ण,
		अणु 0xffffffff, 0x00000पूर्ण
	पूर्ण;
	काष्ठा mem_entry *mem_tbl;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (tg3_flag(tp, 5717_PLUS))
		mem_tbl = mem_tbl_5717;
	अन्यथा अगर (tg3_flag(tp, 57765_CLASS) ||
		 tg3_asic_rev(tp) == ASIC_REV_5762)
		mem_tbl = mem_tbl_57765;
	अन्यथा अगर (tg3_flag(tp, 5755_PLUS))
		mem_tbl = mem_tbl_5755;
	अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5906)
		mem_tbl = mem_tbl_5906;
	अन्यथा अगर (tg3_flag(tp, 5705_PLUS))
		mem_tbl = mem_tbl_5705;
	अन्यथा
		mem_tbl = mem_tbl_570x;

	क्रम (i = 0; mem_tbl[i].offset != 0xffffffff; i++) अणु
		err = tg3_करो_mem_test(tp, mem_tbl[i].offset, mem_tbl[i].len);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

#घोषणा TG3_TSO_MSS		500

#घोषणा TG3_TSO_IP_HDR_LEN	20
#घोषणा TG3_TSO_TCP_HDR_LEN	20
#घोषणा TG3_TSO_TCP_OPT_LEN	12

अटल स्थिर u8 tg3_tso_header[] = अणु
0x08, 0x00,
0x45, 0x00, 0x00, 0x00,
0x00, 0x00, 0x40, 0x00,
0x40, 0x06, 0x00, 0x00,
0x0a, 0x00, 0x00, 0x01,
0x0a, 0x00, 0x00, 0x02,
0x0d, 0x00, 0xe0, 0x00,
0x00, 0x00, 0x01, 0x00,
0x00, 0x00, 0x02, 0x00,
0x80, 0x10, 0x10, 0x00,
0x14, 0x09, 0x00, 0x00,
0x01, 0x01, 0x08, 0x0a,
0x11, 0x11, 0x11, 0x11,
0x11, 0x11, 0x11, 0x11,
पूर्ण;

अटल पूर्णांक tg3_run_loopback(काष्ठा tg3 *tp, u32 pktsz, bool tso_loopback)
अणु
	u32 rx_start_idx, rx_idx, tx_idx, opaque_key;
	u32 base_flags = 0, mss = 0, desc_idx, coal_now, data_off, val;
	u32 budget;
	काष्ठा sk_buff *skb;
	u8 *tx_data, *rx_data;
	dma_addr_t map;
	पूर्णांक num_pkts, tx_len, rx_len, i, err;
	काष्ठा tg3_rx_buffer_desc *desc;
	काष्ठा tg3_napi *tnapi, *rnapi;
	काष्ठा tg3_rx_prodring_set *tpr = &tp->napi[0].prodring;

	tnapi = &tp->napi[0];
	rnapi = &tp->napi[0];
	अगर (tp->irq_cnt > 1) अणु
		अगर (tg3_flag(tp, ENABLE_RSS))
			rnapi = &tp->napi[1];
		अगर (tg3_flag(tp, ENABLE_TSS))
			tnapi = &tp->napi[1];
	पूर्ण
	coal_now = tnapi->coal_now | rnapi->coal_now;

	err = -EIO;

	tx_len = pktsz;
	skb = netdev_alloc_skb(tp->dev, tx_len);
	अगर (!skb)
		वापस -ENOMEM;

	tx_data = skb_put(skb, tx_len);
	स_नकल(tx_data, tp->dev->dev_addr, ETH_ALEN);
	स_रखो(tx_data + ETH_ALEN, 0x0, 8);

	tw32(MAC_RX_MTU_SIZE, tx_len + ETH_FCS_LEN);

	अगर (tso_loopback) अणु
		काष्ठा iphdr *iph = (काष्ठा iphdr *)&tx_data[ETH_HLEN];

		u32 hdr_len = TG3_TSO_IP_HDR_LEN + TG3_TSO_TCP_HDR_LEN +
			      TG3_TSO_TCP_OPT_LEN;

		स_नकल(tx_data + ETH_ALEN * 2, tg3_tso_header,
		       माप(tg3_tso_header));
		mss = TG3_TSO_MSS;

		val = tx_len - ETH_ALEN * 2 - माप(tg3_tso_header);
		num_pkts = DIV_ROUND_UP(val, TG3_TSO_MSS);

		/* Set the total length field in the IP header */
		iph->tot_len = htons((u16)(mss + hdr_len));

		base_flags = (TXD_FLAG_CPU_PRE_DMA |
			      TXD_FLAG_CPU_POST_DMA);

		अगर (tg3_flag(tp, HW_TSO_1) ||
		    tg3_flag(tp, HW_TSO_2) ||
		    tg3_flag(tp, HW_TSO_3)) अणु
			काष्ठा tcphdr *th;
			val = ETH_HLEN + TG3_TSO_IP_HDR_LEN;
			th = (काष्ठा tcphdr *)&tx_data[val];
			th->check = 0;
		पूर्ण अन्यथा
			base_flags |= TXD_FLAG_TCPUDP_CSUM;

		अगर (tg3_flag(tp, HW_TSO_3)) अणु
			mss |= (hdr_len & 0xc) << 12;
			अगर (hdr_len & 0x10)
				base_flags |= 0x00000010;
			base_flags |= (hdr_len & 0x3e0) << 5;
		पूर्ण अन्यथा अगर (tg3_flag(tp, HW_TSO_2))
			mss |= hdr_len << 9;
		अन्यथा अगर (tg3_flag(tp, HW_TSO_1) ||
			 tg3_asic_rev(tp) == ASIC_REV_5705) अणु
			mss |= (TG3_TSO_TCP_OPT_LEN << 9);
		पूर्ण अन्यथा अणु
			base_flags |= (TG3_TSO_TCP_OPT_LEN << 10);
		पूर्ण

		data_off = ETH_ALEN * 2 + माप(tg3_tso_header);
	पूर्ण अन्यथा अणु
		num_pkts = 1;
		data_off = ETH_HLEN;

		अगर (tg3_flag(tp, USE_JUMBO_BDFLAG) &&
		    tx_len > VLAN_ETH_FRAME_LEN)
			base_flags |= TXD_FLAG_JMB_PKT;
	पूर्ण

	क्रम (i = data_off; i < tx_len; i++)
		tx_data[i] = (u8) (i & 0xff);

	map = pci_map_single(tp->pdev, skb->data, tx_len, PCI_DMA_TODEVICE);
	अगर (pci_dma_mapping_error(tp->pdev, map)) अणु
		dev_kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	val = tnapi->tx_prod;
	tnapi->tx_buffers[val].skb = skb;
	dma_unmap_addr_set(&tnapi->tx_buffers[val], mapping, map);

	tw32_f(HOSTCC_MODE, tp->coalesce_mode | HOSTCC_MODE_ENABLE |
	       rnapi->coal_now);

	udelay(10);

	rx_start_idx = rnapi->hw_status->idx[0].rx_producer;

	budget = tg3_tx_avail(tnapi);
	अगर (tg3_tx_frag_set(tnapi, &val, &budget, map, tx_len,
			    base_flags | TXD_FLAG_END, mss, 0)) अणु
		tnapi->tx_buffers[val].skb = शून्य;
		dev_kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	tnapi->tx_prod++;

	/* Sync BD data beक्रमe updating mailbox */
	wmb();

	tw32_tx_mbox(tnapi->prodmbox, tnapi->tx_prod);
	tr32_mailbox(tnapi->prodmbox);

	udelay(10);

	/* 350 usec to allow enough समय on some 10/100 Mbps devices.  */
	क्रम (i = 0; i < 35; i++) अणु
		tw32_f(HOSTCC_MODE, tp->coalesce_mode | HOSTCC_MODE_ENABLE |
		       coal_now);

		udelay(10);

		tx_idx = tnapi->hw_status->idx[0].tx_consumer;
		rx_idx = rnapi->hw_status->idx[0].rx_producer;
		अगर ((tx_idx == tnapi->tx_prod) &&
		    (rx_idx == (rx_start_idx + num_pkts)))
			अवरोध;
	पूर्ण

	tg3_tx_skb_unmap(tnapi, tnapi->tx_prod - 1, -1);
	dev_kमुक्त_skb(skb);

	अगर (tx_idx != tnapi->tx_prod)
		जाओ out;

	अगर (rx_idx != rx_start_idx + num_pkts)
		जाओ out;

	val = data_off;
	जबतक (rx_idx != rx_start_idx) अणु
		desc = &rnapi->rx_rcb[rx_start_idx++];
		desc_idx = desc->opaque & RXD_OPAQUE_INDEX_MASK;
		opaque_key = desc->opaque & RXD_OPAQUE_RING_MASK;

		अगर ((desc->err_vlan & RXD_ERR_MASK) != 0 &&
		    (desc->err_vlan != RXD_ERR_ODD_NIBBLE_RCVD_MII))
			जाओ out;

		rx_len = ((desc->idx_len & RXD_LEN_MASK) >> RXD_LEN_SHIFT)
			 - ETH_FCS_LEN;

		अगर (!tso_loopback) अणु
			अगर (rx_len != tx_len)
				जाओ out;

			अगर (pktsz <= TG3_RX_STD_DMA_SZ - ETH_FCS_LEN) अणु
				अगर (opaque_key != RXD_OPAQUE_RING_STD)
					जाओ out;
			पूर्ण अन्यथा अणु
				अगर (opaque_key != RXD_OPAQUE_RING_JUMBO)
					जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर ((desc->type_flags & RXD_FLAG_TCPUDP_CSUM) &&
			   (desc->ip_tcp_csum & RXD_TCPCSUM_MASK)
			    >> RXD_TCPCSUM_SHIFT != 0xffff) अणु
			जाओ out;
		पूर्ण

		अगर (opaque_key == RXD_OPAQUE_RING_STD) अणु
			rx_data = tpr->rx_std_buffers[desc_idx].data;
			map = dma_unmap_addr(&tpr->rx_std_buffers[desc_idx],
					     mapping);
		पूर्ण अन्यथा अगर (opaque_key == RXD_OPAQUE_RING_JUMBO) अणु
			rx_data = tpr->rx_jmb_buffers[desc_idx].data;
			map = dma_unmap_addr(&tpr->rx_jmb_buffers[desc_idx],
					     mapping);
		पूर्ण अन्यथा
			जाओ out;

		pci_dma_sync_single_क्रम_cpu(tp->pdev, map, rx_len,
					    PCI_DMA_FROMDEVICE);

		rx_data += TG3_RX_OFFSET(tp);
		क्रम (i = data_off; i < rx_len; i++, val++) अणु
			अगर (*(rx_data + i) != (u8) (val & 0xff))
				जाओ out;
		पूर्ण
	पूर्ण

	err = 0;

	/* tg3_मुक्त_rings will unmap and मुक्त the rx_data */
out:
	वापस err;
पूर्ण

#घोषणा TG3_STD_LOOPBACK_FAILED		1
#घोषणा TG3_JMB_LOOPBACK_FAILED		2
#घोषणा TG3_TSO_LOOPBACK_FAILED		4
#घोषणा TG3_LOOPBACK_FAILED \
	(TG3_STD_LOOPBACK_FAILED | \
	 TG3_JMB_LOOPBACK_FAILED | \
	 TG3_TSO_LOOPBACK_FAILED)

अटल पूर्णांक tg3_test_loopback(काष्ठा tg3 *tp, u64 *data, bool करो_extlpbk)
अणु
	पूर्णांक err = -EIO;
	u32 eee_cap;
	u32 jmb_pkt_sz = 9000;

	अगर (tp->dma_limit)
		jmb_pkt_sz = tp->dma_limit - ETH_HLEN;

	eee_cap = tp->phy_flags & TG3_PHYFLG_EEE_CAP;
	tp->phy_flags &= ~TG3_PHYFLG_EEE_CAP;

	अगर (!netअगर_running(tp->dev)) अणु
		data[TG3_MAC_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		data[TG3_PHY_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		अगर (करो_extlpbk)
			data[TG3_EXT_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		जाओ करोne;
	पूर्ण

	err = tg3_reset_hw(tp, true);
	अगर (err) अणु
		data[TG3_MAC_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		data[TG3_PHY_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		अगर (करो_extlpbk)
			data[TG3_EXT_LOOPB_TEST] = TG3_LOOPBACK_FAILED;
		जाओ करोne;
	पूर्ण

	अगर (tg3_flag(tp, ENABLE_RSS)) अणु
		पूर्णांक i;

		/* Reroute all rx packets to the 1st queue */
		क्रम (i = MAC_RSS_INसूची_TBL_0;
		     i < MAC_RSS_INसूची_TBL_0 + TG3_RSS_INसूची_TBL_SIZE; i += 4)
			tw32(i, 0x0);
	पूर्ण

	/* HW errata - mac loopback fails in some हालs on 5780.
	 * Normal traffic and PHY loopback are not affected by
	 * errata.  Also, the MAC loopback test is deprecated क्रम
	 * all newer ASIC revisions.
	 */
	अगर (tg3_asic_rev(tp) != ASIC_REV_5780 &&
	    !tg3_flag(tp, CPMU_PRESENT)) अणु
		tg3_mac_loopback(tp, true);

		अगर (tg3_run_loopback(tp, ETH_FRAME_LEN, false))
			data[TG3_MAC_LOOPB_TEST] |= TG3_STD_LOOPBACK_FAILED;

		अगर (tg3_flag(tp, JUMBO_RING_ENABLE) &&
		    tg3_run_loopback(tp, jmb_pkt_sz + ETH_HLEN, false))
			data[TG3_MAC_LOOPB_TEST] |= TG3_JMB_LOOPBACK_FAILED;

		tg3_mac_loopback(tp, false);
	पूर्ण

	अगर (!(tp->phy_flags & TG3_PHYFLG_PHY_SERDES) &&
	    !tg3_flag(tp, USE_PHYLIB)) अणु
		पूर्णांक i;

		tg3_phy_lpbk_set(tp, 0, false);

		/* Wait क्रम link */
		क्रम (i = 0; i < 100; i++) अणु
			अगर (tr32(MAC_TX_STATUS) & TX_STATUS_LINK_UP)
				अवरोध;
			mdelay(1);
		पूर्ण

		अगर (tg3_run_loopback(tp, ETH_FRAME_LEN, false))
			data[TG3_PHY_LOOPB_TEST] |= TG3_STD_LOOPBACK_FAILED;
		अगर (tg3_flag(tp, TSO_CAPABLE) &&
		    tg3_run_loopback(tp, ETH_FRAME_LEN, true))
			data[TG3_PHY_LOOPB_TEST] |= TG3_TSO_LOOPBACK_FAILED;
		अगर (tg3_flag(tp, JUMBO_RING_ENABLE) &&
		    tg3_run_loopback(tp, jmb_pkt_sz + ETH_HLEN, false))
			data[TG3_PHY_LOOPB_TEST] |= TG3_JMB_LOOPBACK_FAILED;

		अगर (करो_extlpbk) अणु
			tg3_phy_lpbk_set(tp, 0, true);

			/* All link indications report up, but the hardware
			 * isn't really पढ़ोy क्रम about 20 msec.  Double it
			 * to be sure.
			 */
			mdelay(40);

			अगर (tg3_run_loopback(tp, ETH_FRAME_LEN, false))
				data[TG3_EXT_LOOPB_TEST] |=
							TG3_STD_LOOPBACK_FAILED;
			अगर (tg3_flag(tp, TSO_CAPABLE) &&
			    tg3_run_loopback(tp, ETH_FRAME_LEN, true))
				data[TG3_EXT_LOOPB_TEST] |=
							TG3_TSO_LOOPBACK_FAILED;
			अगर (tg3_flag(tp, JUMBO_RING_ENABLE) &&
			    tg3_run_loopback(tp, jmb_pkt_sz + ETH_HLEN, false))
				data[TG3_EXT_LOOPB_TEST] |=
							TG3_JMB_LOOPBACK_FAILED;
		पूर्ण

		/* Re-enable gphy स्वतःघातerकरोwn. */
		अगर (tp->phy_flags & TG3_PHYFLG_ENABLE_APD)
			tg3_phy_toggle_apd(tp, true);
	पूर्ण

	err = (data[TG3_MAC_LOOPB_TEST] | data[TG3_PHY_LOOPB_TEST] |
	       data[TG3_EXT_LOOPB_TEST]) ? -EIO : 0;

करोne:
	tp->phy_flags |= eee_cap;

	वापस err;
पूर्ण

अटल व्योम tg3_self_test(काष्ठा net_device *dev, काष्ठा ethtool_test *etest,
			  u64 *data)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	bool करोextlpbk = etest->flags & ETH_TEST_FL_EXTERNAL_LB;

	अगर (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER) अणु
		अगर (tg3_घातer_up(tp)) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			स_रखो(data, 1, माप(u64) * TG3_NUM_TEST);
			वापस;
		पूर्ण
		tg3_ape_driver_state_change(tp, RESET_KIND_INIT);
	पूर्ण

	स_रखो(data, 0, माप(u64) * TG3_NUM_TEST);

	अगर (tg3_test_nvram(tp) != 0) अणु
		etest->flags |= ETH_TEST_FL_FAILED;
		data[TG3_NVRAM_TEST] = 1;
	पूर्ण
	अगर (!करोextlpbk && tg3_test_link(tp)) अणु
		etest->flags |= ETH_TEST_FL_FAILED;
		data[TG3_LINK_TEST] = 1;
	पूर्ण
	अगर (etest->flags & ETH_TEST_FL_OFFLINE) अणु
		पूर्णांक err, err2 = 0, irq_sync = 0;

		अगर (netअगर_running(dev)) अणु
			tg3_phy_stop(tp);
			tg3_netअगर_stop(tp);
			irq_sync = 1;
		पूर्ण

		tg3_full_lock(tp, irq_sync);
		tg3_halt(tp, RESET_KIND_SUSPEND, 1);
		err = tg3_nvram_lock(tp);
		tg3_halt_cpu(tp, RX_CPU_BASE);
		अगर (!tg3_flag(tp, 5705_PLUS))
			tg3_halt_cpu(tp, TX_CPU_BASE);
		अगर (!err)
			tg3_nvram_unlock(tp);

		अगर (tp->phy_flags & TG3_PHYFLG_MII_SERDES)
			tg3_phy_reset(tp);

		अगर (tg3_test_रेजिस्टरs(tp) != 0) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			data[TG3_REGISTER_TEST] = 1;
		पूर्ण

		अगर (tg3_test_memory(tp) != 0) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			data[TG3_MEMORY_TEST] = 1;
		पूर्ण

		अगर (करोextlpbk)
			etest->flags |= ETH_TEST_FL_EXTERNAL_LB_DONE;

		अगर (tg3_test_loopback(tp, data, करोextlpbk))
			etest->flags |= ETH_TEST_FL_FAILED;

		tg3_full_unlock(tp);

		अगर (tg3_test_पूर्णांकerrupt(tp) != 0) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			data[TG3_INTERRUPT_TEST] = 1;
		पूर्ण

		tg3_full_lock(tp, 0);

		tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
		अगर (netअगर_running(dev)) अणु
			tg3_flag_set(tp, INIT_COMPLETE);
			err2 = tg3_restart_hw(tp, true);
			अगर (!err2)
				tg3_netअगर_start(tp);
		पूर्ण

		tg3_full_unlock(tp);

		अगर (irq_sync && !err2)
			tg3_phy_start(tp);
	पूर्ण
	अगर (tp->phy_flags & TG3_PHYFLG_IS_LOW_POWER)
		tg3_घातer_करोwn_prepare(tp);

पूर्ण

अटल पूर्णांक tg3_hwtstamp_set(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	काष्ठा hwtstamp_config sपंचांगpconf;

	अगर (!tg3_flag(tp, PTP_CAPABLE))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&sपंचांगpconf, अगरr->अगरr_data, माप(sपंचांगpconf)))
		वापस -EFAULT;

	अगर (sपंचांगpconf.flags)
		वापस -EINVAL;

	अगर (sपंचांगpconf.tx_type != HWTSTAMP_TX_ON &&
	    sपंचांगpconf.tx_type != HWTSTAMP_TX_OFF)
		वापस -दुस्फल;

	चयन (sपंचांगpconf.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		tp->rxptpctl = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V1_EN |
			       TG3_RX_PTP_CTL_ALL_V1_EVENTS;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V1_EN |
			       TG3_RX_PTP_CTL_SYNC_EVNT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V1_EN |
			       TG3_RX_PTP_CTL_DELAY_REQ;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_EN |
			       TG3_RX_PTP_CTL_ALL_V2_EVENTS;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_L2_EN |
			       TG3_RX_PTP_CTL_ALL_V2_EVENTS;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_L4_EN |
			       TG3_RX_PTP_CTL_ALL_V2_EVENTS;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_EN |
			       TG3_RX_PTP_CTL_SYNC_EVNT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_L2_EN |
			       TG3_RX_PTP_CTL_SYNC_EVNT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_L4_EN |
			       TG3_RX_PTP_CTL_SYNC_EVNT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_EN |
			       TG3_RX_PTP_CTL_DELAY_REQ;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_L2_EN |
			       TG3_RX_PTP_CTL_DELAY_REQ;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		tp->rxptpctl = TG3_RX_PTP_CTL_RX_PTP_V2_L4_EN |
			       TG3_RX_PTP_CTL_DELAY_REQ;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (netअगर_running(dev) && tp->rxptpctl)
		tw32(TG3_RX_PTP_CTL,
		     tp->rxptpctl | TG3_RX_PTP_CTL_HWTS_INTERLOCK);

	अगर (sपंचांगpconf.tx_type == HWTSTAMP_TX_ON)
		tg3_flag_set(tp, TX_TSTAMP_EN);
	अन्यथा
		tg3_flag_clear(tp, TX_TSTAMP_EN);

	वापस copy_to_user(अगरr->अगरr_data, &sपंचांगpconf, माप(sपंचांगpconf)) ?
		-EFAULT : 0;
पूर्ण

अटल पूर्णांक tg3_hwtstamp_get(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	काष्ठा hwtstamp_config sपंचांगpconf;

	अगर (!tg3_flag(tp, PTP_CAPABLE))
		वापस -EOPNOTSUPP;

	sपंचांगpconf.flags = 0;
	sपंचांगpconf.tx_type = (tg3_flag(tp, TX_TSTAMP_EN) ?
			    HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF);

	चयन (tp->rxptpctl) अणु
	हाल 0:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_NONE;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V1_EN | TG3_RX_PTP_CTL_ALL_V1_EVENTS:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V1_EN | TG3_RX_PTP_CTL_SYNC_EVNT:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_SYNC;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V1_EN | TG3_RX_PTP_CTL_DELAY_REQ:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_EN | TG3_RX_PTP_CTL_ALL_V2_EVENTS:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_L2_EN | TG3_RX_PTP_CTL_ALL_V2_EVENTS:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_L4_EN | TG3_RX_PTP_CTL_ALL_V2_EVENTS:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_EN | TG3_RX_PTP_CTL_SYNC_EVNT:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_SYNC;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_L2_EN | TG3_RX_PTP_CTL_SYNC_EVNT:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_SYNC;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_L4_EN | TG3_RX_PTP_CTL_SYNC_EVNT:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_SYNC;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_EN | TG3_RX_PTP_CTL_DELAY_REQ:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_DELAY_REQ;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_L2_EN | TG3_RX_PTP_CTL_DELAY_REQ:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ;
		अवरोध;
	हाल TG3_RX_PTP_CTL_RX_PTP_V2_L4_EN | TG3_RX_PTP_CTL_DELAY_REQ:
		sपंचांगpconf.rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -दुस्फल;
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &sपंचांगpconf, माप(sपंचांगpconf)) ?
		-EFAULT : 0;
पूर्ण

अटल पूर्णांक tg3_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक err;

	अगर (tg3_flag(tp, USE_PHYLIB)) अणु
		काष्ठा phy_device *phydev;
		अगर (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED))
			वापस -EAGAIN;
		phydev = mdiobus_get_phy(tp->mdio_bus, tp->phy_addr);
		वापस phy_mii_ioctl(phydev, अगरr, cmd);
	पूर्ण

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = tp->phy_addr;

		fallthrough;
	हाल SIOCGMIIREG: अणु
		u32 mii_regval;

		अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)
			अवरोध;			/* We have no PHY */

		अगर (!netअगर_running(dev))
			वापस -EAGAIN;

		spin_lock_bh(&tp->lock);
		err = __tg3_पढ़ोphy(tp, data->phy_id & 0x1f,
				    data->reg_num & 0x1f, &mii_regval);
		spin_unlock_bh(&tp->lock);

		data->val_out = mii_regval;

		वापस err;
	पूर्ण

	हाल SIOCSMIIREG:
		अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)
			अवरोध;			/* We have no PHY */

		अगर (!netअगर_running(dev))
			वापस -EAGAIN;

		spin_lock_bh(&tp->lock);
		err = __tg3_ग_लिखोphy(tp, data->phy_id & 0x1f,
				     data->reg_num & 0x1f, data->val_in);
		spin_unlock_bh(&tp->lock);

		वापस err;

	हाल SIOCSHWTSTAMP:
		वापस tg3_hwtstamp_set(dev, अगरr);

	हाल SIOCGHWTSTAMP:
		वापस tg3_hwtstamp_get(dev, अगरr);

	शेष:
		/* करो nothing */
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक tg3_get_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	स_नकल(ec, &tp->coal, माप(*ec));
	वापस 0;
पूर्ण

अटल पूर्णांक tg3_set_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	u32 max_rxcoal_tick_पूर्णांक = 0, max_txcoal_tick_पूर्णांक = 0;
	u32 max_stat_coal_ticks = 0, min_stat_coal_ticks = 0;

	अगर (!tg3_flag(tp, 5705_PLUS)) अणु
		max_rxcoal_tick_पूर्णांक = MAX_RXCOAL_TICK_INT;
		max_txcoal_tick_पूर्णांक = MAX_TXCOAL_TICK_INT;
		max_stat_coal_ticks = MAX_STAT_COAL_TICKS;
		min_stat_coal_ticks = MIN_STAT_COAL_TICKS;
	पूर्ण

	अगर ((ec->rx_coalesce_usecs > MAX_RXCOL_TICKS) ||
	    (!ec->rx_coalesce_usecs) ||
	    (ec->tx_coalesce_usecs > MAX_TXCOL_TICKS) ||
	    (!ec->tx_coalesce_usecs) ||
	    (ec->rx_max_coalesced_frames > MAX_RXMAX_FRAMES) ||
	    (ec->tx_max_coalesced_frames > MAX_TXMAX_FRAMES) ||
	    (ec->rx_coalesce_usecs_irq > max_rxcoal_tick_पूर्णांक) ||
	    (ec->tx_coalesce_usecs_irq > max_txcoal_tick_पूर्णांक) ||
	    (ec->rx_max_coalesced_frames_irq > MAX_RXCOAL_MAXF_INT) ||
	    (ec->tx_max_coalesced_frames_irq > MAX_TXCOAL_MAXF_INT) ||
	    (ec->stats_block_coalesce_usecs > max_stat_coal_ticks) ||
	    (ec->stats_block_coalesce_usecs < min_stat_coal_ticks))
		वापस -EINVAL;

	/* Only copy relevant parameters, ignore all others. */
	tp->coal.rx_coalesce_usecs = ec->rx_coalesce_usecs;
	tp->coal.tx_coalesce_usecs = ec->tx_coalesce_usecs;
	tp->coal.rx_max_coalesced_frames = ec->rx_max_coalesced_frames;
	tp->coal.tx_max_coalesced_frames = ec->tx_max_coalesced_frames;
	tp->coal.rx_coalesce_usecs_irq = ec->rx_coalesce_usecs_irq;
	tp->coal.tx_coalesce_usecs_irq = ec->tx_coalesce_usecs_irq;
	tp->coal.rx_max_coalesced_frames_irq = ec->rx_max_coalesced_frames_irq;
	tp->coal.tx_max_coalesced_frames_irq = ec->tx_max_coalesced_frames_irq;
	tp->coal.stats_block_coalesce_usecs = ec->stats_block_coalesce_usecs;

	अगर (netअगर_running(dev)) अणु
		tg3_full_lock(tp, 0);
		__tg3_set_coalesce(tp, &tp->coal);
		tg3_full_unlock(tp);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tg3_set_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP)) अणु
		netdev_warn(tp->dev, "Board does not support EEE!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (edata->advertised != tp->eee.advertised) अणु
		netdev_warn(tp->dev,
			    "Direct manipulation of EEE advertisement is not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (edata->tx_lpi_समयr > TG3_CPMU_DBTMR1_LNKIDLE_MAX) अणु
		netdev_warn(tp->dev,
			    "Maximal Tx Lpi timer supported is %#x(u)\n",
			    TG3_CPMU_DBTMR1_LNKIDLE_MAX);
		वापस -EINVAL;
	पूर्ण

	tp->eee = *edata;

	tp->phy_flags |= TG3_PHYFLG_USER_CONFIGURED;
	tg3_warn_mgmt_link_flap(tp);

	अगर (netअगर_running(tp->dev)) अणु
		tg3_full_lock(tp, 0);
		tg3_setup_eee(tp);
		tg3_phy_reset(tp);
		tg3_full_unlock(tp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tg3_get_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP)) अणु
		netdev_warn(tp->dev,
			    "Board does not support EEE!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	*edata = tp->eee;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops tg3_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USECS_IRQ |
				     ETHTOOL_COALESCE_MAX_FRAMES_IRQ |
				     ETHTOOL_COALESCE_STATS_BLOCK_USECS,
	.get_drvinfo		= tg3_get_drvinfo,
	.get_regs_len		= tg3_get_regs_len,
	.get_regs		= tg3_get_regs,
	.get_wol		= tg3_get_wol,
	.set_wol		= tg3_set_wol,
	.get_msglevel		= tg3_get_msglevel,
	.set_msglevel		= tg3_set_msglevel,
	.nway_reset		= tg3_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= tg3_get_eeprom_len,
	.get_eeprom		= tg3_get_eeprom,
	.set_eeprom		= tg3_set_eeprom,
	.get_ringparam		= tg3_get_ringparam,
	.set_ringparam		= tg3_set_ringparam,
	.get_छोड़ोparam		= tg3_get_छोड़ोparam,
	.set_छोड़ोparam		= tg3_set_छोड़ोparam,
	.self_test		= tg3_self_test,
	.get_strings		= tg3_get_strings,
	.set_phys_id		= tg3_set_phys_id,
	.get_ethtool_stats	= tg3_get_ethtool_stats,
	.get_coalesce		= tg3_get_coalesce,
	.set_coalesce		= tg3_set_coalesce,
	.get_sset_count		= tg3_get_sset_count,
	.get_rxnfc		= tg3_get_rxnfc,
	.get_rxfh_indir_size    = tg3_get_rxfh_indir_size,
	.get_rxfh		= tg3_get_rxfh,
	.set_rxfh		= tg3_set_rxfh,
	.get_channels		= tg3_get_channels,
	.set_channels		= tg3_set_channels,
	.get_ts_info		= tg3_get_ts_info,
	.get_eee		= tg3_get_eee,
	.set_eee		= tg3_set_eee,
	.get_link_ksettings	= tg3_get_link_ksettings,
	.set_link_ksettings	= tg3_set_link_ksettings,
पूर्ण;

अटल व्योम tg3_get_stats64(काष्ठा net_device *dev,
			    काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	spin_lock_bh(&tp->lock);
	अगर (!tp->hw_stats || !tg3_flag(tp, INIT_COMPLETE)) अणु
		*stats = tp->net_stats_prev;
		spin_unlock_bh(&tp->lock);
		वापस;
	पूर्ण

	tg3_get_nstats(tp, stats);
	spin_unlock_bh(&tp->lock);
पूर्ण

अटल व्योम tg3_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस;

	tg3_full_lock(tp, 0);
	__tg3_set_rx_mode(dev);
	tg3_full_unlock(tp);
पूर्ण

अटल अंतरभूत व्योम tg3_set_mtu(काष्ठा net_device *dev, काष्ठा tg3 *tp,
			       पूर्णांक new_mtu)
अणु
	dev->mtu = new_mtu;

	अगर (new_mtu > ETH_DATA_LEN) अणु
		अगर (tg3_flag(tp, 5780_CLASS)) अणु
			netdev_update_features(dev);
			tg3_flag_clear(tp, TSO_CAPABLE);
		पूर्ण अन्यथा अणु
			tg3_flag_set(tp, JUMBO_RING_ENABLE);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tg3_flag(tp, 5780_CLASS)) अणु
			tg3_flag_set(tp, TSO_CAPABLE);
			netdev_update_features(dev);
		पूर्ण
		tg3_flag_clear(tp, JUMBO_RING_ENABLE);
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक err;
	bool reset_phy = false;

	अगर (!netअगर_running(dev)) अणु
		/* We'll just catch it later when the
		 * device is up'd.
		 */
		tg3_set_mtu(dev, tp, new_mtu);
		वापस 0;
	पूर्ण

	tg3_phy_stop(tp);

	tg3_netअगर_stop(tp);

	tg3_set_mtu(dev, tp, new_mtu);

	tg3_full_lock(tp, 1);

	tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);

	/* Reset PHY, otherwise the पढ़ो DMA engine will be in a mode that
	 * अवरोधs all requests to 256 bytes.
	 */
	अगर (tg3_asic_rev(tp) == ASIC_REV_57766 ||
	    tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720)
		reset_phy = true;

	err = tg3_restart_hw(tp, reset_phy);

	अगर (!err)
		tg3_netअगर_start(tp);

	tg3_full_unlock(tp);

	अगर (!err)
		tg3_phy_start(tp);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops tg3_netdev_ops = अणु
	.nकरो_खोलो		= tg3_खोलो,
	.nकरो_stop		= tg3_बंद,
	.nकरो_start_xmit		= tg3_start_xmit,
	.nकरो_get_stats64	= tg3_get_stats64,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= tg3_set_rx_mode,
	.nकरो_set_mac_address	= tg3_set_mac_addr,
	.nकरो_करो_ioctl		= tg3_ioctl,
	.nकरो_tx_समयout		= tg3_tx_समयout,
	.nकरो_change_mtu		= tg3_change_mtu,
	.nकरो_fix_features	= tg3_fix_features,
	.nकरो_set_features	= tg3_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= tg3_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल व्योम tg3_get_eeprom_size(काष्ठा tg3 *tp)
अणु
	u32 cursize, val, magic;

	tp->nvram_size = EEPROM_CHIP_SIZE;

	अगर (tg3_nvram_पढ़ो(tp, 0, &magic) != 0)
		वापस;

	अगर ((magic != TG3_EEPROM_MAGIC) &&
	    ((magic & TG3_EEPROM_MAGIC_FW_MSK) != TG3_EEPROM_MAGIC_FW) &&
	    ((magic & TG3_EEPROM_MAGIC_HW_MSK) != TG3_EEPROM_MAGIC_HW))
		वापस;

	/*
	 * Size the chip by पढ़ोing offsets at increasing घातers of two.
	 * When we encounter our validation signature, we know the addressing
	 * has wrapped around, and thus have our chip size.
	 */
	cursize = 0x10;

	जबतक (cursize < tp->nvram_size) अणु
		अगर (tg3_nvram_पढ़ो(tp, cursize, &val) != 0)
			वापस;

		अगर (val == magic)
			अवरोध;

		cursize <<= 1;
	पूर्ण

	tp->nvram_size = cursize;
पूर्ण

अटल व्योम tg3_get_nvram_size(काष्ठा tg3 *tp)
अणु
	u32 val;

	अगर (tg3_flag(tp, NO_NVRAM) || tg3_nvram_पढ़ो(tp, 0, &val) != 0)
		वापस;

	/* Selfboot क्रमmat */
	अगर (val != TG3_EEPROM_MAGIC) अणु
		tg3_get_eeprom_size(tp);
		वापस;
	पूर्ण

	अगर (tg3_nvram_पढ़ो(tp, 0xf0, &val) == 0) अणु
		अगर (val != 0) अणु
			/* This is confusing.  We want to operate on the
			 * 16-bit value at offset 0xf2.  The tg3_nvram_पढ़ो()
			 * call will पढ़ो from NVRAM and byteswap the data
			 * according to the byteswapping settings क्रम all
			 * other रेजिस्टर accesses.  This ensures the data we
			 * want will always reside in the lower 16-bits.
			 * However, the data in NVRAM is in LE क्रमmat, which
			 * means the data from the NVRAM पढ़ो will always be
			 * opposite the endianness of the CPU.  The 16-bit
			 * byteswap then brings the data to CPU endianness.
			 */
			tp->nvram_size = swab16((u16)(val & 0x0000ffff)) * 1024;
			वापस;
		पूर्ण
	पूर्ण
	tp->nvram_size = TG3_NVRAM_SIZE_512KB;
पूर्ण

अटल व्योम tg3_get_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);
	अगर (nvcfg1 & NVRAM_CFG1_FLASHIF_ENAB) अणु
		tg3_flag_set(tp, FLASH);
	पूर्ण अन्यथा अणु
		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5750 ||
	    tg3_flag(tp, 5780_CLASS)) अणु
		चयन (nvcfg1 & NVRAM_CFG1_VENDOR_MASK) अणु
		हाल FLASH_VENDOR_ATMEL_FLASH_BUFFERED:
			tp->nvram_jedecnum = JEDEC_ATMEL;
			tp->nvram_pagesize = ATMEL_AT45DB0X1B_PAGE_SIZE;
			tg3_flag_set(tp, NVRAM_BUFFERED);
			अवरोध;
		हाल FLASH_VENDOR_ATMEL_FLASH_UNBUFFERED:
			tp->nvram_jedecnum = JEDEC_ATMEL;
			tp->nvram_pagesize = ATMEL_AT25F512_PAGE_SIZE;
			अवरोध;
		हाल FLASH_VENDOR_ATMEL_EEPROM:
			tp->nvram_jedecnum = JEDEC_ATMEL;
			tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;
			tg3_flag_set(tp, NVRAM_BUFFERED);
			अवरोध;
		हाल FLASH_VENDOR_ST:
			tp->nvram_jedecnum = JEDEC_ST;
			tp->nvram_pagesize = ST_M45PEX0_PAGE_SIZE;
			tg3_flag_set(tp, NVRAM_BUFFERED);
			अवरोध;
		हाल FLASH_VENDOR_SAIFUN:
			tp->nvram_jedecnum = JEDEC_SAIFUN;
			tp->nvram_pagesize = SAIFUN_SA25F0XX_PAGE_SIZE;
			अवरोध;
		हाल FLASH_VENDOR_SST_SMALL:
		हाल FLASH_VENDOR_SST_LARGE:
			tp->nvram_jedecnum = JEDEC_SST;
			tp->nvram_pagesize = SST_25VF0X0_PAGE_SIZE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tp->nvram_pagesize = ATMEL_AT45DB0X1B_PAGE_SIZE;
		tg3_flag_set(tp, NVRAM_BUFFERED);
	पूर्ण
पूर्ण

अटल व्योम tg3_nvram_get_pagesize(काष्ठा tg3 *tp, u32 nvmcfg1)
अणु
	चयन (nvmcfg1 & NVRAM_CFG1_5752PAGE_SIZE_MASK) अणु
	हाल FLASH_5752PAGE_SIZE_256:
		tp->nvram_pagesize = 256;
		अवरोध;
	हाल FLASH_5752PAGE_SIZE_512:
		tp->nvram_pagesize = 512;
		अवरोध;
	हाल FLASH_5752PAGE_SIZE_1K:
		tp->nvram_pagesize = 1024;
		अवरोध;
	हाल FLASH_5752PAGE_SIZE_2K:
		tp->nvram_pagesize = 2048;
		अवरोध;
	हाल FLASH_5752PAGE_SIZE_4K:
		tp->nvram_pagesize = 4096;
		अवरोध;
	हाल FLASH_5752PAGE_SIZE_264:
		tp->nvram_pagesize = 264;
		अवरोध;
	हाल FLASH_5752PAGE_SIZE_528:
		tp->nvram_pagesize = 528;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tg3_get_5752_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);

	/* NVRAM protection क्रम TPM */
	अगर (nvcfg1 & (1 << 27))
		tg3_flag_set(tp, PROTECTED_NVRAM);

	चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
	हाल FLASH_5752VENDOR_ATMEL_EEPROM_64KHZ:
	हाल FLASH_5752VENDOR_ATMEL_EEPROM_376KHZ:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		अवरोध;
	हाल FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		अवरोध;
	हाल FLASH_5752VENDOR_ST_M45PE10:
	हाल FLASH_5752VENDOR_ST_M45PE20:
	हाल FLASH_5752VENDOR_ST_M45PE40:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		अवरोध;
	पूर्ण

	अगर (tg3_flag(tp, FLASH)) अणु
		tg3_nvram_get_pagesize(tp, nvcfg1);
	पूर्ण अन्यथा अणु
		/* For eeprom, set pagesize to maximum eeprom size */
		tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
	पूर्ण
पूर्ण

अटल व्योम tg3_get_5755_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1, protect = 0;

	nvcfg1 = tr32(NVRAM_CFG1);

	/* NVRAM protection क्रम TPM */
	अगर (nvcfg1 & (1 << 27)) अणु
		tg3_flag_set(tp, PROTECTED_NVRAM);
		protect = 1;
	पूर्ण

	nvcfg1 &= NVRAM_CFG1_5752VENDOR_MASK;
	चयन (nvcfg1) अणु
	हाल FLASH_5755VENDOR_ATMEL_FLASH_1:
	हाल FLASH_5755VENDOR_ATMEL_FLASH_2:
	हाल FLASH_5755VENDOR_ATMEL_FLASH_3:
	हाल FLASH_5755VENDOR_ATMEL_FLASH_5:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 264;
		अगर (nvcfg1 == FLASH_5755VENDOR_ATMEL_FLASH_1 ||
		    nvcfg1 == FLASH_5755VENDOR_ATMEL_FLASH_5)
			tp->nvram_size = (protect ? 0x3e200 :
					  TG3_NVRAM_SIZE_512KB);
		अन्यथा अगर (nvcfg1 == FLASH_5755VENDOR_ATMEL_FLASH_2)
			tp->nvram_size = (protect ? 0x1f200 :
					  TG3_NVRAM_SIZE_256KB);
		अन्यथा
			tp->nvram_size = (protect ? 0x1f200 :
					  TG3_NVRAM_SIZE_128KB);
		अवरोध;
	हाल FLASH_5752VENDOR_ST_M45PE10:
	हाल FLASH_5752VENDOR_ST_M45PE20:
	हाल FLASH_5752VENDOR_ST_M45PE40:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 256;
		अगर (nvcfg1 == FLASH_5752VENDOR_ST_M45PE10)
			tp->nvram_size = (protect ?
					  TG3_NVRAM_SIZE_64KB :
					  TG3_NVRAM_SIZE_128KB);
		अन्यथा अगर (nvcfg1 == FLASH_5752VENDOR_ST_M45PE20)
			tp->nvram_size = (protect ?
					  TG3_NVRAM_SIZE_64KB :
					  TG3_NVRAM_SIZE_256KB);
		अन्यथा
			tp->nvram_size = (protect ?
					  TG3_NVRAM_SIZE_128KB :
					  TG3_NVRAM_SIZE_512KB);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tg3_get_5787_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);

	चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
	हाल FLASH_5787VENDOR_ATMEL_EEPROM_64KHZ:
	हाल FLASH_5787VENDOR_ATMEL_EEPROM_376KHZ:
	हाल FLASH_5787VENDOR_MICRO_EEPROM_64KHZ:
	हाल FLASH_5787VENDOR_MICRO_EEPROM_376KHZ:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		अवरोध;
	हाल FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED:
	हाल FLASH_5755VENDOR_ATMEL_FLASH_1:
	हाल FLASH_5755VENDOR_ATMEL_FLASH_2:
	हाल FLASH_5755VENDOR_ATMEL_FLASH_3:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 264;
		अवरोध;
	हाल FLASH_5752VENDOR_ST_M45PE10:
	हाल FLASH_5752VENDOR_ST_M45PE20:
	हाल FLASH_5752VENDOR_ST_M45PE40:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 256;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tg3_get_5761_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1, protect = 0;

	nvcfg1 = tr32(NVRAM_CFG1);

	/* NVRAM protection क्रम TPM */
	अगर (nvcfg1 & (1 << 27)) अणु
		tg3_flag_set(tp, PROTECTED_NVRAM);
		protect = 1;
	पूर्ण

	nvcfg1 &= NVRAM_CFG1_5752VENDOR_MASK;
	चयन (nvcfg1) अणु
	हाल FLASH_5761VENDOR_ATMEL_ADB021D:
	हाल FLASH_5761VENDOR_ATMEL_ADB041D:
	हाल FLASH_5761VENDOR_ATMEL_ADB081D:
	हाल FLASH_5761VENDOR_ATMEL_ADB161D:
	हाल FLASH_5761VENDOR_ATMEL_MDB021D:
	हाल FLASH_5761VENDOR_ATMEL_MDB041D:
	हाल FLASH_5761VENDOR_ATMEL_MDB081D:
	हाल FLASH_5761VENDOR_ATMEL_MDB161D:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);
		tp->nvram_pagesize = 256;
		अवरोध;
	हाल FLASH_5761VENDOR_ST_A_M45PE20:
	हाल FLASH_5761VENDOR_ST_A_M45PE40:
	हाल FLASH_5761VENDOR_ST_A_M45PE80:
	हाल FLASH_5761VENDOR_ST_A_M45PE16:
	हाल FLASH_5761VENDOR_ST_M_M45PE20:
	हाल FLASH_5761VENDOR_ST_M_M45PE40:
	हाल FLASH_5761VENDOR_ST_M_M45PE80:
	हाल FLASH_5761VENDOR_ST_M_M45PE16:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);
		tp->nvram_pagesize = 256;
		अवरोध;
	पूर्ण

	अगर (protect) अणु
		tp->nvram_size = tr32(NVRAM_ADDR_LOCKOUT);
	पूर्ण अन्यथा अणु
		चयन (nvcfg1) अणु
		हाल FLASH_5761VENDOR_ATMEL_ADB161D:
		हाल FLASH_5761VENDOR_ATMEL_MDB161D:
		हाल FLASH_5761VENDOR_ST_A_M45PE16:
		हाल FLASH_5761VENDOR_ST_M_M45PE16:
			tp->nvram_size = TG3_NVRAM_SIZE_2MB;
			अवरोध;
		हाल FLASH_5761VENDOR_ATMEL_ADB081D:
		हाल FLASH_5761VENDOR_ATMEL_MDB081D:
		हाल FLASH_5761VENDOR_ST_A_M45PE80:
		हाल FLASH_5761VENDOR_ST_M_M45PE80:
			tp->nvram_size = TG3_NVRAM_SIZE_1MB;
			अवरोध;
		हाल FLASH_5761VENDOR_ATMEL_ADB041D:
		हाल FLASH_5761VENDOR_ATMEL_MDB041D:
		हाल FLASH_5761VENDOR_ST_A_M45PE40:
		हाल FLASH_5761VENDOR_ST_M_M45PE40:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			अवरोध;
		हाल FLASH_5761VENDOR_ATMEL_ADB021D:
		हाल FLASH_5761VENDOR_ATMEL_MDB021D:
		हाल FLASH_5761VENDOR_ST_A_M45PE20:
		हाल FLASH_5761VENDOR_ST_M_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tg3_get_5906_nvram_info(काष्ठा tg3 *tp)
अणु
	tp->nvram_jedecnum = JEDEC_ATMEL;
	tg3_flag_set(tp, NVRAM_BUFFERED);
	tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;
पूर्ण

अटल व्योम tg3_get_57780_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);

	चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
	हाल FLASH_5787VENDOR_ATMEL_EEPROM_376KHZ:
	हाल FLASH_5787VENDOR_MICRO_EEPROM_376KHZ:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		वापस;
	हाल FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED:
	हाल FLASH_57780VENDOR_ATMEL_AT45DB011D:
	हाल FLASH_57780VENDOR_ATMEL_AT45DB011B:
	हाल FLASH_57780VENDOR_ATMEL_AT45DB021D:
	हाल FLASH_57780VENDOR_ATMEL_AT45DB021B:
	हाल FLASH_57780VENDOR_ATMEL_AT45DB041D:
	हाल FLASH_57780VENDOR_ATMEL_AT45DB041B:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
		हाल FLASH_5752VENDOR_ATMEL_FLASH_BUFFERED:
		हाल FLASH_57780VENDOR_ATMEL_AT45DB011D:
		हाल FLASH_57780VENDOR_ATMEL_AT45DB011B:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			अवरोध;
		हाल FLASH_57780VENDOR_ATMEL_AT45DB021D:
		हाल FLASH_57780VENDOR_ATMEL_AT45DB021B:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			अवरोध;
		हाल FLASH_57780VENDOR_ATMEL_AT45DB041D:
		हाल FLASH_57780VENDOR_ATMEL_AT45DB041B:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FLASH_5752VENDOR_ST_M45PE10:
	हाल FLASH_5752VENDOR_ST_M45PE20:
	हाल FLASH_5752VENDOR_ST_M45PE40:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
		हाल FLASH_5752VENDOR_ST_M45PE10:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			अवरोध;
		हाल FLASH_5752VENDOR_ST_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			अवरोध;
		हाल FLASH_5752VENDOR_ST_M45PE40:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		tg3_flag_set(tp, NO_NVRAM);
		वापस;
	पूर्ण

	tg3_nvram_get_pagesize(tp, nvcfg1);
	अगर (tp->nvram_pagesize != 264 && tp->nvram_pagesize != 528)
		tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);
पूर्ण


अटल व्योम tg3_get_5717_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1;

	nvcfg1 = tr32(NVRAM_CFG1);

	चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
	हाल FLASH_5717VENDOR_ATMEL_EEPROM:
	हाल FLASH_5717VENDOR_MICRO_EEPROM:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		वापस;
	हाल FLASH_5717VENDOR_ATMEL_MDB011D:
	हाल FLASH_5717VENDOR_ATMEL_ADB011B:
	हाल FLASH_5717VENDOR_ATMEL_ADB011D:
	हाल FLASH_5717VENDOR_ATMEL_MDB021D:
	हाल FLASH_5717VENDOR_ATMEL_ADB021B:
	हाल FLASH_5717VENDOR_ATMEL_ADB021D:
	हाल FLASH_5717VENDOR_ATMEL_45USPT:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
		हाल FLASH_5717VENDOR_ATMEL_MDB021D:
			/* Detect size with tg3_nvram_get_size() */
			अवरोध;
		हाल FLASH_5717VENDOR_ATMEL_ADB021B:
		हाल FLASH_5717VENDOR_ATMEL_ADB021D:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			अवरोध;
		शेष:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FLASH_5717VENDOR_ST_M_M25PE10:
	हाल FLASH_5717VENDOR_ST_A_M25PE10:
	हाल FLASH_5717VENDOR_ST_M_M45PE10:
	हाल FLASH_5717VENDOR_ST_A_M45PE10:
	हाल FLASH_5717VENDOR_ST_M_M25PE20:
	हाल FLASH_5717VENDOR_ST_A_M25PE20:
	हाल FLASH_5717VENDOR_ST_M_M45PE20:
	हाल FLASH_5717VENDOR_ST_A_M45PE20:
	हाल FLASH_5717VENDOR_ST_25USPT:
	हाल FLASH_5717VENDOR_ST_45USPT:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		चयन (nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK) अणु
		हाल FLASH_5717VENDOR_ST_M_M25PE20:
		हाल FLASH_5717VENDOR_ST_M_M45PE20:
			/* Detect size with tg3_nvram_get_size() */
			अवरोध;
		हाल FLASH_5717VENDOR_ST_A_M25PE20:
		हाल FLASH_5717VENDOR_ST_A_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			अवरोध;
		शेष:
			tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		tg3_flag_set(tp, NO_NVRAM);
		वापस;
	पूर्ण

	tg3_nvram_get_pagesize(tp, nvcfg1);
	अगर (tp->nvram_pagesize != 264 && tp->nvram_pagesize != 528)
		tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);
पूर्ण

अटल व्योम tg3_get_5720_nvram_info(काष्ठा tg3 *tp)
अणु
	u32 nvcfg1, nvmpinstrp, nv_status;

	nvcfg1 = tr32(NVRAM_CFG1);
	nvmpinstrp = nvcfg1 & NVRAM_CFG1_5752VENDOR_MASK;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5762) अणु
		अगर (!(nvcfg1 & NVRAM_CFG1_5762VENDOR_MASK)) अणु
			tg3_flag_set(tp, NO_NVRAM);
			वापस;
		पूर्ण

		चयन (nvmpinstrp) अणु
		हाल FLASH_5762_MX25L_100:
		हाल FLASH_5762_MX25L_200:
		हाल FLASH_5762_MX25L_400:
		हाल FLASH_5762_MX25L_800:
		हाल FLASH_5762_MX25L_160_320:
			tp->nvram_pagesize = 4096;
			tp->nvram_jedecnum = JEDEC_MACRONIX;
			tg3_flag_set(tp, NVRAM_BUFFERED);
			tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);
			tg3_flag_set(tp, FLASH);
			nv_status = tr32(NVRAM_AUTOSENSE_STATUS);
			tp->nvram_size =
				(1 << (nv_status >> AUTOSENSE_DEVID &
						AUTOSENSE_DEVID_MASK)
					<< AUTOSENSE_SIZE_IN_MB);
			वापस;

		हाल FLASH_5762_EEPROM_HD:
			nvmpinstrp = FLASH_5720_EEPROM_HD;
			अवरोध;
		हाल FLASH_5762_EEPROM_LD:
			nvmpinstrp = FLASH_5720_EEPROM_LD;
			अवरोध;
		हाल FLASH_5720VENDOR_M_ST_M45PE20:
			/* This pinstrap supports multiple sizes, so क्रमce it
			 * to पढ़ो the actual size from location 0xf0.
			 */
			nvmpinstrp = FLASH_5720VENDOR_ST_45USPT;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (nvmpinstrp) अणु
	हाल FLASH_5720_EEPROM_HD:
	हाल FLASH_5720_EEPROM_LD:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);

		nvcfg1 &= ~NVRAM_CFG1_COMPAT_BYPASS;
		tw32(NVRAM_CFG1, nvcfg1);
		अगर (nvmpinstrp == FLASH_5720_EEPROM_HD)
			tp->nvram_pagesize = ATMEL_AT24C512_CHIP_SIZE;
		अन्यथा
			tp->nvram_pagesize = ATMEL_AT24C02_CHIP_SIZE;
		वापस;
	हाल FLASH_5720VENDOR_M_ATMEL_DB011D:
	हाल FLASH_5720VENDOR_A_ATMEL_DB011B:
	हाल FLASH_5720VENDOR_A_ATMEL_DB011D:
	हाल FLASH_5720VENDOR_M_ATMEL_DB021D:
	हाल FLASH_5720VENDOR_A_ATMEL_DB021B:
	हाल FLASH_5720VENDOR_A_ATMEL_DB021D:
	हाल FLASH_5720VENDOR_M_ATMEL_DB041D:
	हाल FLASH_5720VENDOR_A_ATMEL_DB041B:
	हाल FLASH_5720VENDOR_A_ATMEL_DB041D:
	हाल FLASH_5720VENDOR_M_ATMEL_DB081D:
	हाल FLASH_5720VENDOR_A_ATMEL_DB081D:
	हाल FLASH_5720VENDOR_ATMEL_45USPT:
		tp->nvram_jedecnum = JEDEC_ATMEL;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		चयन (nvmpinstrp) अणु
		हाल FLASH_5720VENDOR_M_ATMEL_DB021D:
		हाल FLASH_5720VENDOR_A_ATMEL_DB021B:
		हाल FLASH_5720VENDOR_A_ATMEL_DB021D:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			अवरोध;
		हाल FLASH_5720VENDOR_M_ATMEL_DB041D:
		हाल FLASH_5720VENDOR_A_ATMEL_DB041B:
		हाल FLASH_5720VENDOR_A_ATMEL_DB041D:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			अवरोध;
		हाल FLASH_5720VENDOR_M_ATMEL_DB081D:
		हाल FLASH_5720VENDOR_A_ATMEL_DB081D:
			tp->nvram_size = TG3_NVRAM_SIZE_1MB;
			अवरोध;
		शेष:
			अगर (tg3_asic_rev(tp) != ASIC_REV_5762)
				tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FLASH_5720VENDOR_M_ST_M25PE10:
	हाल FLASH_5720VENDOR_M_ST_M45PE10:
	हाल FLASH_5720VENDOR_A_ST_M25PE10:
	हाल FLASH_5720VENDOR_A_ST_M45PE10:
	हाल FLASH_5720VENDOR_M_ST_M25PE20:
	हाल FLASH_5720VENDOR_M_ST_M45PE20:
	हाल FLASH_5720VENDOR_A_ST_M25PE20:
	हाल FLASH_5720VENDOR_A_ST_M45PE20:
	हाल FLASH_5720VENDOR_M_ST_M25PE40:
	हाल FLASH_5720VENDOR_M_ST_M45PE40:
	हाल FLASH_5720VENDOR_A_ST_M25PE40:
	हाल FLASH_5720VENDOR_A_ST_M45PE40:
	हाल FLASH_5720VENDOR_M_ST_M25PE80:
	हाल FLASH_5720VENDOR_M_ST_M45PE80:
	हाल FLASH_5720VENDOR_A_ST_M25PE80:
	हाल FLASH_5720VENDOR_A_ST_M45PE80:
	हाल FLASH_5720VENDOR_ST_25USPT:
	हाल FLASH_5720VENDOR_ST_45USPT:
		tp->nvram_jedecnum = JEDEC_ST;
		tg3_flag_set(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, FLASH);

		चयन (nvmpinstrp) अणु
		हाल FLASH_5720VENDOR_M_ST_M25PE20:
		हाल FLASH_5720VENDOR_M_ST_M45PE20:
		हाल FLASH_5720VENDOR_A_ST_M25PE20:
		हाल FLASH_5720VENDOR_A_ST_M45PE20:
			tp->nvram_size = TG3_NVRAM_SIZE_256KB;
			अवरोध;
		हाल FLASH_5720VENDOR_M_ST_M25PE40:
		हाल FLASH_5720VENDOR_M_ST_M45PE40:
		हाल FLASH_5720VENDOR_A_ST_M25PE40:
		हाल FLASH_5720VENDOR_A_ST_M45PE40:
			tp->nvram_size = TG3_NVRAM_SIZE_512KB;
			अवरोध;
		हाल FLASH_5720VENDOR_M_ST_M25PE80:
		हाल FLASH_5720VENDOR_M_ST_M45PE80:
		हाल FLASH_5720VENDOR_A_ST_M25PE80:
		हाल FLASH_5720VENDOR_A_ST_M45PE80:
			tp->nvram_size = TG3_NVRAM_SIZE_1MB;
			अवरोध;
		शेष:
			अगर (tg3_asic_rev(tp) != ASIC_REV_5762)
				tp->nvram_size = TG3_NVRAM_SIZE_128KB;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		tg3_flag_set(tp, NO_NVRAM);
		वापस;
	पूर्ण

	tg3_nvram_get_pagesize(tp, nvcfg1);
	अगर (tp->nvram_pagesize != 264 && tp->nvram_pagesize != 528)
		tg3_flag_set(tp, NO_NVRAM_ADDR_TRANS);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5762) अणु
		u32 val;

		अगर (tg3_nvram_पढ़ो(tp, 0, &val))
			वापस;

		अगर (val != TG3_EEPROM_MAGIC &&
		    (val & TG3_EEPROM_MAGIC_FW_MSK) != TG3_EEPROM_MAGIC_FW)
			tg3_flag_set(tp, NO_NVRAM);
	पूर्ण
पूर्ण

/* Chips other than 5700/5701 use the NVRAM क्रम fetching info. */
अटल व्योम tg3_nvram_init(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, IS_SSB_CORE)) अणु
		/* No NVRAM and EEPROM on the SSB Broadcom GigE core. */
		tg3_flag_clear(tp, NVRAM);
		tg3_flag_clear(tp, NVRAM_BUFFERED);
		tg3_flag_set(tp, NO_NVRAM);
		वापस;
	पूर्ण

	tw32_f(GRC_EEPROM_ADDR,
	     (EEPROM_ADDR_FSM_RESET |
	      (EEPROM_DEFAULT_CLOCK_PERIOD <<
	       EEPROM_ADDR_CLKPERD_SHIFT)));

	msleep(1);

	/* Enable seeprom accesses. */
	tw32_f(GRC_LOCAL_CTRL,
	     tr32(GRC_LOCAL_CTRL) | GRC_LCLCTRL_AUTO_SEEPROM);
	udelay(100);

	अगर (tg3_asic_rev(tp) != ASIC_REV_5700 &&
	    tg3_asic_rev(tp) != ASIC_REV_5701) अणु
		tg3_flag_set(tp, NVRAM);

		अगर (tg3_nvram_lock(tp)) अणु
			netdev_warn(tp->dev,
				    "Cannot get nvram lock, %s failed\n",
				    __func__);
			वापस;
		पूर्ण
		tg3_enable_nvram_access(tp);

		tp->nvram_size = 0;

		अगर (tg3_asic_rev(tp) == ASIC_REV_5752)
			tg3_get_5752_nvram_info(tp);
		अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5755)
			tg3_get_5755_nvram_info(tp);
		अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5787 ||
			 tg3_asic_rev(tp) == ASIC_REV_5784 ||
			 tg3_asic_rev(tp) == ASIC_REV_5785)
			tg3_get_5787_nvram_info(tp);
		अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5761)
			tg3_get_5761_nvram_info(tp);
		अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5906)
			tg3_get_5906_nvram_info(tp);
		अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_57780 ||
			 tg3_flag(tp, 57765_CLASS))
			tg3_get_57780_nvram_info(tp);
		अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
			 tg3_asic_rev(tp) == ASIC_REV_5719)
			tg3_get_5717_nvram_info(tp);
		अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5720 ||
			 tg3_asic_rev(tp) == ASIC_REV_5762)
			tg3_get_5720_nvram_info(tp);
		अन्यथा
			tg3_get_nvram_info(tp);

		अगर (tp->nvram_size == 0)
			tg3_get_nvram_size(tp);

		tg3_disable_nvram_access(tp);
		tg3_nvram_unlock(tp);

	पूर्ण अन्यथा अणु
		tg3_flag_clear(tp, NVRAM);
		tg3_flag_clear(tp, NVRAM_BUFFERED);

		tg3_get_eeprom_size(tp);
	पूर्ण
पूर्ण

काष्ठा subsys_tbl_ent अणु
	u16 subsys_venकरोr, subsys_devid;
	u32 phy_id;
पूर्ण;

अटल काष्ठा subsys_tbl_ent subsys_id_to_phy_id[] = अणु
	/* Broadcom boards. */
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95700A6, TG3_PHY_ID_BCM5401 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95701A5, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95700T6, TG3_PHY_ID_BCM8002 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95700A9, 0 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95701T1, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95701T8, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95701A7, 0 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95701A10, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95701A12, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95703AX1, TG3_PHY_ID_BCM5703 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_BROADCOM,
	  TG3PCI_SUBDEVICE_ID_BROADCOM_95703AX2, TG3_PHY_ID_BCM5703 पूर्ण,

	/* 3com boards. */
	अणु TG3PCI_SUBVENDOR_ID_3COM,
	  TG3PCI_SUBDEVICE_ID_3COM_3C996T, TG3_PHY_ID_BCM5401 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_3COM,
	  TG3PCI_SUBDEVICE_ID_3COM_3C996BT, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_3COM,
	  TG3PCI_SUBDEVICE_ID_3COM_3C996SX, 0 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_3COM,
	  TG3PCI_SUBDEVICE_ID_3COM_3C1000T, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_3COM,
	  TG3PCI_SUBDEVICE_ID_3COM_3C940BR01, TG3_PHY_ID_BCM5701 पूर्ण,

	/* DELL boards. */
	अणु TG3PCI_SUBVENDOR_ID_DELL,
	  TG3PCI_SUBDEVICE_ID_DELL_VIPER, TG3_PHY_ID_BCM5401 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_DELL,
	  TG3PCI_SUBDEVICE_ID_DELL_JAGUAR, TG3_PHY_ID_BCM5401 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_DELL,
	  TG3PCI_SUBDEVICE_ID_DELL_MERLOT, TG3_PHY_ID_BCM5411 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_DELL,
	  TG3PCI_SUBDEVICE_ID_DELL_SLIM_MERLOT, TG3_PHY_ID_BCM5411 पूर्ण,

	/* Compaq boards. */
	अणु TG3PCI_SUBVENDOR_ID_COMPAQ,
	  TG3PCI_SUBDEVICE_ID_COMPAQ_BANSHEE, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_COMPAQ,
	  TG3PCI_SUBDEVICE_ID_COMPAQ_BANSHEE_2, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_COMPAQ,
	  TG3PCI_SUBDEVICE_ID_COMPAQ_CHANGELING, 0 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_COMPAQ,
	  TG3PCI_SUBDEVICE_ID_COMPAQ_NC7780, TG3_PHY_ID_BCM5701 पूर्ण,
	अणु TG3PCI_SUBVENDOR_ID_COMPAQ,
	  TG3PCI_SUBDEVICE_ID_COMPAQ_NC7780_2, TG3_PHY_ID_BCM5701 पूर्ण,

	/* IBM boards. */
	अणु TG3PCI_SUBVENDOR_ID_IBM,
	  TG3PCI_SUBDEVICE_ID_IBM_5703SAX2, 0 पूर्ण
पूर्ण;

अटल काष्ठा subsys_tbl_ent *tg3_lookup_by_subsys(काष्ठा tg3 *tp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(subsys_id_to_phy_id); i++) अणु
		अगर ((subsys_id_to_phy_id[i].subsys_venकरोr ==
		     tp->pdev->subप्रणाली_venकरोr) &&
		    (subsys_id_to_phy_id[i].subsys_devid ==
		     tp->pdev->subप्रणाली_device))
			वापस &subsys_id_to_phy_id[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम tg3_get_eeprom_hw_cfg(काष्ठा tg3 *tp)
अणु
	u32 val;

	tp->phy_id = TG3_PHY_ID_INVALID;
	tp->led_ctrl = LED_CTRL_MODE_PHY_1;

	/* Assume an onboard device and WOL capable by शेष.  */
	tg3_flag_set(tp, EEPROM_WRITE_PROT);
	tg3_flag_set(tp, WOL_CAP);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		अगर (!(tr32(PCIE_TRANSACTION_CFG) & PCIE_TRANS_CFG_LOM)) अणु
			tg3_flag_clear(tp, EEPROM_WRITE_PROT);
			tg3_flag_set(tp, IS_NIC);
		पूर्ण
		val = tr32(VCPU_CFGSHDW);
		अगर (val & VCPU_CFGSHDW_ASPM_DBNC)
			tg3_flag_set(tp, ASPM_WORKAROUND);
		अगर ((val & VCPU_CFGSHDW_WOL_ENABLE) &&
		    (val & VCPU_CFGSHDW_WOL_MAGPKT)) अणु
			tg3_flag_set(tp, WOL_ENABLE);
			device_set_wakeup_enable(&tp->pdev->dev, true);
		पूर्ण
		जाओ करोne;
	पूर्ण

	tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_SIG, &val);
	अगर (val == NIC_SRAM_DATA_SIG_MAGIC) अणु
		u32 nic_cfg, led_cfg;
		u32 cfg2 = 0, cfg4 = 0, cfg5 = 0;
		u32 nic_phy_id, ver, eeprom_phy_id;
		पूर्णांक eeprom_phy_serdes = 0;

		tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_CFG, &nic_cfg);
		tp->nic_sram_data_cfg = nic_cfg;

		tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_VER, &ver);
		ver >>= NIC_SRAM_DATA_VER_SHIFT;
		अगर (tg3_asic_rev(tp) != ASIC_REV_5700 &&
		    tg3_asic_rev(tp) != ASIC_REV_5701 &&
		    tg3_asic_rev(tp) != ASIC_REV_5703 &&
		    (ver > 0) && (ver < 0x100))
			tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_CFG_2, &cfg2);

		अगर (tg3_asic_rev(tp) == ASIC_REV_5785)
			tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_CFG_4, &cfg4);

		अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
		    tg3_asic_rev(tp) == ASIC_REV_5719 ||
		    tg3_asic_rev(tp) == ASIC_REV_5720)
			tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_CFG_5, &cfg5);

		अगर ((nic_cfg & NIC_SRAM_DATA_CFG_PHY_TYPE_MASK) ==
		    NIC_SRAM_DATA_CFG_PHY_TYPE_FIBER)
			eeprom_phy_serdes = 1;

		tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_PHY_ID, &nic_phy_id);
		अगर (nic_phy_id != 0) अणु
			u32 id1 = nic_phy_id & NIC_SRAM_DATA_PHY_ID1_MASK;
			u32 id2 = nic_phy_id & NIC_SRAM_DATA_PHY_ID2_MASK;

			eeprom_phy_id  = (id1 >> 16) << 10;
			eeprom_phy_id |= (id2 & 0xfc00) << 16;
			eeprom_phy_id |= (id2 & 0x03ff) <<  0;
		पूर्ण अन्यथा
			eeprom_phy_id = 0;

		tp->phy_id = eeprom_phy_id;
		अगर (eeprom_phy_serdes) अणु
			अगर (!tg3_flag(tp, 5705_PLUS))
				tp->phy_flags |= TG3_PHYFLG_PHY_SERDES;
			अन्यथा
				tp->phy_flags |= TG3_PHYFLG_MII_SERDES;
		पूर्ण

		अगर (tg3_flag(tp, 5750_PLUS))
			led_cfg = cfg2 & (NIC_SRAM_DATA_CFG_LED_MODE_MASK |
				    SHASTA_EXT_LED_MODE_MASK);
		अन्यथा
			led_cfg = nic_cfg & NIC_SRAM_DATA_CFG_LED_MODE_MASK;

		चयन (led_cfg) अणु
		शेष:
		हाल NIC_SRAM_DATA_CFG_LED_MODE_PHY_1:
			tp->led_ctrl = LED_CTRL_MODE_PHY_1;
			अवरोध;

		हाल NIC_SRAM_DATA_CFG_LED_MODE_PHY_2:
			tp->led_ctrl = LED_CTRL_MODE_PHY_2;
			अवरोध;

		हाल NIC_SRAM_DATA_CFG_LED_MODE_MAC:
			tp->led_ctrl = LED_CTRL_MODE_MAC;

			/* Default to PHY_1_MODE अगर 0 (MAC_MODE) is
			 * पढ़ो on some older 5700/5701 bootcode.
			 */
			अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
			    tg3_asic_rev(tp) == ASIC_REV_5701)
				tp->led_ctrl = LED_CTRL_MODE_PHY_1;

			अवरोध;

		हाल SHASTA_EXT_LED_SHARED:
			tp->led_ctrl = LED_CTRL_MODE_SHARED;
			अगर (tg3_chip_rev_id(tp) != CHIPREV_ID_5750_A0 &&
			    tg3_chip_rev_id(tp) != CHIPREV_ID_5750_A1)
				tp->led_ctrl |= (LED_CTRL_MODE_PHY_1 |
						 LED_CTRL_MODE_PHY_2);

			अगर (tg3_flag(tp, 5717_PLUS) ||
			    tg3_asic_rev(tp) == ASIC_REV_5762)
				tp->led_ctrl |= LED_CTRL_BLINK_RATE_OVERRIDE |
						LED_CTRL_BLINK_RATE_MASK;

			अवरोध;

		हाल SHASTA_EXT_LED_MAC:
			tp->led_ctrl = LED_CTRL_MODE_SHASTA_MAC;
			अवरोध;

		हाल SHASTA_EXT_LED_COMBO:
			tp->led_ctrl = LED_CTRL_MODE_COMBO;
			अगर (tg3_chip_rev_id(tp) != CHIPREV_ID_5750_A0)
				tp->led_ctrl |= (LED_CTRL_MODE_PHY_1 |
						 LED_CTRL_MODE_PHY_2);
			अवरोध;

		पूर्ण

		अगर ((tg3_asic_rev(tp) == ASIC_REV_5700 ||
		     tg3_asic_rev(tp) == ASIC_REV_5701) &&
		    tp->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DELL)
			tp->led_ctrl = LED_CTRL_MODE_PHY_2;

		अगर (tg3_chip_rev(tp) == CHIPREV_5784_AX)
			tp->led_ctrl = LED_CTRL_MODE_PHY_1;

		अगर (nic_cfg & NIC_SRAM_DATA_CFG_EEPROM_WP) अणु
			tg3_flag_set(tp, EEPROM_WRITE_PROT);
			अगर ((tp->pdev->subप्रणाली_venकरोr ==
			     PCI_VENDOR_ID_ARIMA) &&
			    (tp->pdev->subप्रणाली_device == 0x205a ||
			     tp->pdev->subप्रणाली_device == 0x2063))
				tg3_flag_clear(tp, EEPROM_WRITE_PROT);
		पूर्ण अन्यथा अणु
			tg3_flag_clear(tp, EEPROM_WRITE_PROT);
			tg3_flag_set(tp, IS_NIC);
		पूर्ण

		अगर (nic_cfg & NIC_SRAM_DATA_CFG_ASF_ENABLE) अणु
			tg3_flag_set(tp, ENABLE_ASF);
			अगर (tg3_flag(tp, 5750_PLUS))
				tg3_flag_set(tp, ASF_NEW_HANDSHAKE);
		पूर्ण

		अगर ((nic_cfg & NIC_SRAM_DATA_CFG_APE_ENABLE) &&
		    tg3_flag(tp, 5750_PLUS))
			tg3_flag_set(tp, ENABLE_APE);

		अगर (tp->phy_flags & TG3_PHYFLG_ANY_SERDES &&
		    !(nic_cfg & NIC_SRAM_DATA_CFG_FIBER_WOL))
			tg3_flag_clear(tp, WOL_CAP);

		अगर (tg3_flag(tp, WOL_CAP) &&
		    (nic_cfg & NIC_SRAM_DATA_CFG_WOL_ENABLE)) अणु
			tg3_flag_set(tp, WOL_ENABLE);
			device_set_wakeup_enable(&tp->pdev->dev, true);
		पूर्ण

		अगर (cfg2 & (1 << 17))
			tp->phy_flags |= TG3_PHYFLG_CAPACITIVE_COUPLING;

		/* serdes संकेत pre-emphasis in रेजिस्टर 0x590 set by */
		/* bootcode अगर bit 18 is set */
		अगर (cfg2 & (1 << 18))
			tp->phy_flags |= TG3_PHYFLG_SERDES_PREEMPHASIS;

		अगर ((tg3_flag(tp, 57765_PLUS) ||
		     (tg3_asic_rev(tp) == ASIC_REV_5784 &&
		      tg3_chip_rev(tp) != CHIPREV_5784_AX)) &&
		    (cfg2 & NIC_SRAM_DATA_CFG_2_APD_EN))
			tp->phy_flags |= TG3_PHYFLG_ENABLE_APD;

		अगर (tg3_flag(tp, PCI_EXPRESS)) अणु
			u32 cfg3;

			tg3_पढ़ो_mem(tp, NIC_SRAM_DATA_CFG_3, &cfg3);
			अगर (tg3_asic_rev(tp) != ASIC_REV_5785 &&
			    !tg3_flag(tp, 57765_PLUS) &&
			    (cfg3 & NIC_SRAM_ASPM_DEBOUNCE))
				tg3_flag_set(tp, ASPM_WORKAROUND);
			अगर (cfg3 & NIC_SRAM_LNK_FLAP_AVOID)
				tp->phy_flags |= TG3_PHYFLG_KEEP_LINK_ON_PWRDN;
			अगर (cfg3 & NIC_SRAM_1G_ON_VAUX_OK)
				tp->phy_flags |= TG3_PHYFLG_1G_ON_VAUX_OK;
		पूर्ण

		अगर (cfg4 & NIC_SRAM_RGMII_INBAND_DISABLE)
			tg3_flag_set(tp, RGMII_INBAND_DISABLE);
		अगर (cfg4 & NIC_SRAM_RGMII_EXT_IBND_RX_EN)
			tg3_flag_set(tp, RGMII_EXT_IBND_RX_EN);
		अगर (cfg4 & NIC_SRAM_RGMII_EXT_IBND_TX_EN)
			tg3_flag_set(tp, RGMII_EXT_IBND_TX_EN);

		अगर (cfg5 & NIC_SRAM_DISABLE_1G_HALF_ADV)
			tp->phy_flags |= TG3_PHYFLG_DISABLE_1G_HD_ADV;
	पूर्ण
करोne:
	अगर (tg3_flag(tp, WOL_CAP))
		device_set_wakeup_enable(&tp->pdev->dev,
					 tg3_flag(tp, WOL_ENABLE));
	अन्यथा
		device_set_wakeup_capable(&tp->pdev->dev, false);
पूर्ण

अटल पूर्णांक tg3_ape_otp_पढ़ो(काष्ठा tg3 *tp, u32 offset, u32 *val)
अणु
	पूर्णांक i, err;
	u32 val2, off = offset * 8;

	err = tg3_nvram_lock(tp);
	अगर (err)
		वापस err;

	tg3_ape_ग_लिखो32(tp, TG3_APE_OTP_ADDR, off | APE_OTP_ADDR_CPU_ENABLE);
	tg3_ape_ग_लिखो32(tp, TG3_APE_OTP_CTRL, APE_OTP_CTRL_PROG_EN |
			APE_OTP_CTRL_CMD_RD | APE_OTP_CTRL_START);
	tg3_ape_पढ़ो32(tp, TG3_APE_OTP_CTRL);
	udelay(10);

	क्रम (i = 0; i < 100; i++) अणु
		val2 = tg3_ape_पढ़ो32(tp, TG3_APE_OTP_STATUS);
		अगर (val2 & APE_OTP_STATUS_CMD_DONE) अणु
			*val = tg3_ape_पढ़ो32(tp, TG3_APE_OTP_RD_DATA);
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण

	tg3_ape_ग_लिखो32(tp, TG3_APE_OTP_CTRL, 0);

	tg3_nvram_unlock(tp);
	अगर (val2 & APE_OTP_STATUS_CMD_DONE)
		वापस 0;

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक tg3_issue_otp_command(काष्ठा tg3 *tp, u32 cmd)
अणु
	पूर्णांक i;
	u32 val;

	tw32(OTP_CTRL, cmd | OTP_CTRL_OTP_CMD_START);
	tw32(OTP_CTRL, cmd);

	/* Wait क्रम up to 1 ms क्रम command to execute. */
	क्रम (i = 0; i < 100; i++) अणु
		val = tr32(OTP_STATUS);
		अगर (val & OTP_STATUS_CMD_DONE)
			अवरोध;
		udelay(10);
	पूर्ण

	वापस (val & OTP_STATUS_CMD_DONE) ? 0 : -EBUSY;
पूर्ण

/* Read the gphy configuration from the OTP region of the chip.  The gphy
 * configuration is a 32-bit value that straddles the alignment boundary.
 * We करो two 32-bit पढ़ोs and then shअगरt and merge the results.
 */
अटल u32 tg3_पढ़ो_otp_phycfg(काष्ठा tg3 *tp)
अणु
	u32 bhalf_otp, thalf_otp;

	tw32(OTP_MODE, OTP_MODE_OTP_THRU_GRC);

	अगर (tg3_issue_otp_command(tp, OTP_CTRL_OTP_CMD_INIT))
		वापस 0;

	tw32(OTP_ADDRESS, OTP_ADDRESS_MAGIC1);

	अगर (tg3_issue_otp_command(tp, OTP_CTRL_OTP_CMD_READ))
		वापस 0;

	thalf_otp = tr32(OTP_READ_DATA);

	tw32(OTP_ADDRESS, OTP_ADDRESS_MAGIC2);

	अगर (tg3_issue_otp_command(tp, OTP_CTRL_OTP_CMD_READ))
		वापस 0;

	bhalf_otp = tr32(OTP_READ_DATA);

	वापस ((thalf_otp & 0x0000ffff) << 16) | (bhalf_otp >> 16);
पूर्ण

अटल व्योम tg3_phy_init_link_config(काष्ठा tg3 *tp)
अणु
	u32 adv = ADVERTISED_Autoneg;

	अगर (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) अणु
		अगर (!(tp->phy_flags & TG3_PHYFLG_DISABLE_1G_HD_ADV))
			adv |= ADVERTISED_1000baseT_Half;
		adv |= ADVERTISED_1000baseT_Full;
	पूर्ण

	अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES))
		adv |= ADVERTISED_100baseT_Half |
		       ADVERTISED_100baseT_Full |
		       ADVERTISED_10baseT_Half |
		       ADVERTISED_10baseT_Full |
		       ADVERTISED_TP;
	अन्यथा
		adv |= ADVERTISED_FIBRE;

	tp->link_config.advertising = adv;
	tp->link_config.speed = SPEED_UNKNOWN;
	tp->link_config.duplex = DUPLEX_UNKNOWN;
	tp->link_config.स्वतःneg = AUTONEG_ENABLE;
	tp->link_config.active_speed = SPEED_UNKNOWN;
	tp->link_config.active_duplex = DUPLEX_UNKNOWN;

	tp->old_link = -1;
पूर्ण

अटल पूर्णांक tg3_phy_probe(काष्ठा tg3 *tp)
अणु
	u32 hw_phy_id_1, hw_phy_id_2;
	u32 hw_phy_id, hw_phy_id_masked;
	पूर्णांक err;

	/* flow control स्वतःnegotiation is शेष behavior */
	tg3_flag_set(tp, PAUSE_AUTONEG);
	tp->link_config.flowctrl = FLOW_CTRL_TX | FLOW_CTRL_RX;

	अगर (tg3_flag(tp, ENABLE_APE)) अणु
		चयन (tp->pci_fn) अणु
		हाल 0:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY0;
			अवरोध;
		हाल 1:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY1;
			अवरोध;
		हाल 2:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY2;
			अवरोध;
		हाल 3:
			tp->phy_ape_lock = TG3_APE_LOCK_PHY3;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!tg3_flag(tp, ENABLE_ASF) &&
	    !(tp->phy_flags & TG3_PHYFLG_ANY_SERDES) &&
	    !(tp->phy_flags & TG3_PHYFLG_10_100_ONLY))
		tp->phy_flags &= ~(TG3_PHYFLG_1G_ON_VAUX_OK |
				   TG3_PHYFLG_KEEP_LINK_ON_PWRDN);

	अगर (tg3_flag(tp, USE_PHYLIB))
		वापस tg3_phy_init(tp);

	/* Reading the PHY ID रेजिस्टर can conflict with ASF
	 * firmware access to the PHY hardware.
	 */
	err = 0;
	अगर (tg3_flag(tp, ENABLE_ASF) || tg3_flag(tp, ENABLE_APE)) अणु
		hw_phy_id = hw_phy_id_masked = TG3_PHY_ID_INVALID;
	पूर्ण अन्यथा अणु
		/* Now पढ़ो the physical PHY_ID from the chip and verअगरy
		 * that it is sane.  If it करोesn't look good, we fall back
		 * to either the hard-coded table based PHY_ID and failing
		 * that the value found in the eeprom area.
		 */
		err |= tg3_पढ़ोphy(tp, MII_PHYSID1, &hw_phy_id_1);
		err |= tg3_पढ़ोphy(tp, MII_PHYSID2, &hw_phy_id_2);

		hw_phy_id  = (hw_phy_id_1 & 0xffff) << 10;
		hw_phy_id |= (hw_phy_id_2 & 0xfc00) << 16;
		hw_phy_id |= (hw_phy_id_2 & 0x03ff) <<  0;

		hw_phy_id_masked = hw_phy_id & TG3_PHY_ID_MASK;
	पूर्ण

	अगर (!err && TG3_KNOWN_PHY_ID(hw_phy_id_masked)) अणु
		tp->phy_id = hw_phy_id;
		अगर (hw_phy_id_masked == TG3_PHY_ID_BCM8002)
			tp->phy_flags |= TG3_PHYFLG_PHY_SERDES;
		अन्यथा
			tp->phy_flags &= ~TG3_PHYFLG_PHY_SERDES;
	पूर्ण अन्यथा अणु
		अगर (tp->phy_id != TG3_PHY_ID_INVALID) अणु
			/* Do nothing, phy ID alपढ़ोy set up in
			 * tg3_get_eeprom_hw_cfg().
			 */
		पूर्ण अन्यथा अणु
			काष्ठा subsys_tbl_ent *p;

			/* No eeprom signature?  Try the hardcoded
			 * subsys device table.
			 */
			p = tg3_lookup_by_subsys(tp);
			अगर (p) अणु
				tp->phy_id = p->phy_id;
			पूर्ण अन्यथा अगर (!tg3_flag(tp, IS_SSB_CORE)) अणु
				/* For now we saw the IDs 0xbc050cd0,
				 * 0xbc050f80 and 0xbc050c30 on devices
				 * connected to an BCM4785 and there are
				 * probably more. Just assume that the phy is
				 * supported when it is connected to a SSB core
				 * क्रम now.
				 */
				वापस -ENODEV;
			पूर्ण

			अगर (!tp->phy_id ||
			    tp->phy_id == TG3_PHY_ID_BCM8002)
				tp->phy_flags |= TG3_PHYFLG_PHY_SERDES;
		पूर्ण
	पूर्ण

	अगर (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES) &&
	    (tg3_asic_rev(tp) == ASIC_REV_5719 ||
	     tg3_asic_rev(tp) == ASIC_REV_5720 ||
	     tg3_asic_rev(tp) == ASIC_REV_57766 ||
	     tg3_asic_rev(tp) == ASIC_REV_5762 ||
	     (tg3_asic_rev(tp) == ASIC_REV_5717 &&
	      tg3_chip_rev_id(tp) != CHIPREV_ID_5717_A0) ||
	     (tg3_asic_rev(tp) == ASIC_REV_57765 &&
	      tg3_chip_rev_id(tp) != CHIPREV_ID_57765_A0))) अणु
		tp->phy_flags |= TG3_PHYFLG_EEE_CAP;

		tp->eee.supported = SUPPORTED_100baseT_Full |
				    SUPPORTED_1000baseT_Full;
		tp->eee.advertised = ADVERTISED_100baseT_Full |
				     ADVERTISED_1000baseT_Full;
		tp->eee.eee_enabled = 1;
		tp->eee.tx_lpi_enabled = 1;
		tp->eee.tx_lpi_समयr = TG3_CPMU_DBTMR1_LNKIDLE_2047US;
	पूर्ण

	tg3_phy_init_link_config(tp);

	अगर (!(tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN) &&
	    !(tp->phy_flags & TG3_PHYFLG_ANY_SERDES) &&
	    !tg3_flag(tp, ENABLE_APE) &&
	    !tg3_flag(tp, ENABLE_ASF)) अणु
		u32 bmsr, dummy;

		tg3_पढ़ोphy(tp, MII_BMSR, &bmsr);
		अगर (!tg3_पढ़ोphy(tp, MII_BMSR, &bmsr) &&
		    (bmsr & BMSR_LSTATUS))
			जाओ skip_phy_reset;

		err = tg3_phy_reset(tp);
		अगर (err)
			वापस err;

		tg3_phy_set_wirespeed(tp);

		अगर (!tg3_phy_copper_an_config_ok(tp, &dummy)) अणु
			tg3_phy_स्वतःneg_cfg(tp, tp->link_config.advertising,
					    tp->link_config.flowctrl);

			tg3_ग_लिखोphy(tp, MII_BMCR,
				     BMCR_ANENABLE | BMCR_ANRESTART);
		पूर्ण
	पूर्ण

skip_phy_reset:
	अगर ((tp->phy_id & TG3_PHY_ID_MASK) == TG3_PHY_ID_BCM5401) अणु
		err = tg3_init_5401phy_dsp(tp);
		अगर (err)
			वापस err;

		err = tg3_init_5401phy_dsp(tp);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम tg3_पढ़ो_vpd(काष्ठा tg3 *tp)
अणु
	u8 *vpd_data;
	अचिन्हित पूर्णांक block_end, rosize, len;
	u32 vpdlen;
	पूर्णांक j, i = 0;

	vpd_data = (u8 *)tg3_vpd_पढ़ोblock(tp, &vpdlen);
	अगर (!vpd_data)
		जाओ out_no_vpd;

	i = pci_vpd_find_tag(vpd_data, vpdlen, PCI_VPD_LRDT_RO_DATA);
	अगर (i < 0)
		जाओ out_not_found;

	rosize = pci_vpd_lrdt_size(&vpd_data[i]);
	block_end = i + PCI_VPD_LRDT_TAG_SIZE + rosize;
	i += PCI_VPD_LRDT_TAG_SIZE;

	अगर (block_end > vpdlen)
		जाओ out_not_found;

	j = pci_vpd_find_info_keyword(vpd_data, i, rosize,
				      PCI_VPD_RO_KEYWORD_MFR_ID);
	अगर (j > 0) अणु
		len = pci_vpd_info_field_size(&vpd_data[j]);

		j += PCI_VPD_INFO_FLD_HDR_SIZE;
		अगर (j + len > block_end || len != 4 ||
		    स_भेद(&vpd_data[j], "1028", 4))
			जाओ partno;

		j = pci_vpd_find_info_keyword(vpd_data, i, rosize,
					      PCI_VPD_RO_KEYWORD_VENDOR0);
		अगर (j < 0)
			जाओ partno;

		len = pci_vpd_info_field_size(&vpd_data[j]);

		j += PCI_VPD_INFO_FLD_HDR_SIZE;
		अगर (j + len > block_end)
			जाओ partno;

		अगर (len >= माप(tp->fw_ver))
			len = माप(tp->fw_ver) - 1;
		स_रखो(tp->fw_ver, 0, माप(tp->fw_ver));
		snम_लिखो(tp->fw_ver, माप(tp->fw_ver), "%.*s bc ", len,
			 &vpd_data[j]);
	पूर्ण

partno:
	i = pci_vpd_find_info_keyword(vpd_data, i, rosize,
				      PCI_VPD_RO_KEYWORD_PARTNO);
	अगर (i < 0)
		जाओ out_not_found;

	len = pci_vpd_info_field_size(&vpd_data[i]);

	i += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (len > TG3_BPN_SIZE ||
	    (len + i) > vpdlen)
		जाओ out_not_found;

	स_नकल(tp->board_part_number, &vpd_data[i], len);

out_not_found:
	kमुक्त(vpd_data);
	अगर (tp->board_part_number[0])
		वापस;

out_no_vpd:
	अगर (tg3_asic_rev(tp) == ASIC_REV_5717) अणु
		अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_5717 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5717_C)
			म_नकल(tp->board_part_number, "BCM5717");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_5718)
			म_नकल(tp->board_part_number, "BCM5718");
		अन्यथा
			जाओ nomatch;
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_57780) अणु
		अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57780)
			म_नकल(tp->board_part_number, "BCM57780");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57760)
			म_नकल(tp->board_part_number, "BCM57760");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57790)
			म_नकल(tp->board_part_number, "BCM57790");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57788)
			म_नकल(tp->board_part_number, "BCM57788");
		अन्यथा
			जाओ nomatch;
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_57765) अणु
		अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57761)
			म_नकल(tp->board_part_number, "BCM57761");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57765)
			म_नकल(tp->board_part_number, "BCM57765");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57781)
			म_नकल(tp->board_part_number, "BCM57781");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57785)
			म_नकल(tp->board_part_number, "BCM57785");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57791)
			म_नकल(tp->board_part_number, "BCM57791");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57795)
			म_नकल(tp->board_part_number, "BCM57795");
		अन्यथा
			जाओ nomatch;
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_57766) अणु
		अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57762)
			म_नकल(tp->board_part_number, "BCM57762");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57766)
			म_नकल(tp->board_part_number, "BCM57766");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57782)
			म_नकल(tp->board_part_number, "BCM57782");
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57786)
			म_नकल(tp->board_part_number, "BCM57786");
		अन्यथा
			जाओ nomatch;
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		म_नकल(tp->board_part_number, "BCM95906");
	पूर्ण अन्यथा अणु
nomatch:
		म_नकल(tp->board_part_number, "none");
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_fw_img_is_valid(काष्ठा tg3 *tp, u32 offset)
अणु
	u32 val;

	अगर (tg3_nvram_पढ़ो(tp, offset, &val) ||
	    (val & 0xfc000000) != 0x0c000000 ||
	    tg3_nvram_पढ़ो(tp, offset + 4, &val) ||
	    val != 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम tg3_पढ़ो_bc_ver(काष्ठा tg3 *tp)
अणु
	u32 val, offset, start, ver_offset;
	पूर्णांक i, dst_off;
	bool newver = false;

	अगर (tg3_nvram_पढ़ो(tp, 0xc, &offset) ||
	    tg3_nvram_पढ़ो(tp, 0x4, &start))
		वापस;

	offset = tg3_nvram_logical_addr(tp, offset);

	अगर (tg3_nvram_पढ़ो(tp, offset, &val))
		वापस;

	अगर ((val & 0xfc000000) == 0x0c000000) अणु
		अगर (tg3_nvram_पढ़ो(tp, offset + 4, &val))
			वापस;

		अगर (val == 0)
			newver = true;
	पूर्ण

	dst_off = म_माप(tp->fw_ver);

	अगर (newver) अणु
		अगर (TG3_VER_SIZE - dst_off < 16 ||
		    tg3_nvram_पढ़ो(tp, offset + 8, &ver_offset))
			वापस;

		offset = offset + ver_offset - start;
		क्रम (i = 0; i < 16; i += 4) अणु
			__be32 v;
			अगर (tg3_nvram_पढ़ो_be32(tp, offset + i, &v))
				वापस;

			स_नकल(tp->fw_ver + dst_off + i, &v, माप(v));
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 major, minor;

		अगर (tg3_nvram_पढ़ो(tp, TG3_NVM_PTREV_BCVER, &ver_offset))
			वापस;

		major = (ver_offset & TG3_NVM_BCVER_MAJMSK) >>
			TG3_NVM_BCVER_MAJSFT;
		minor = ver_offset & TG3_NVM_BCVER_MINMSK;
		snम_लिखो(&tp->fw_ver[dst_off], TG3_VER_SIZE - dst_off,
			 "v%d.%02d", major, minor);
	पूर्ण
पूर्ण

अटल व्योम tg3_पढ़ो_hwsb_ver(काष्ठा tg3 *tp)
अणु
	u32 val, major, minor;

	/* Use native endian representation */
	अगर (tg3_nvram_पढ़ो(tp, TG3_NVM_HWSB_CFG1, &val))
		वापस;

	major = (val & TG3_NVM_HWSB_CFG1_MAJMSK) >>
		TG3_NVM_HWSB_CFG1_MAJSFT;
	minor = (val & TG3_NVM_HWSB_CFG1_MINMSK) >>
		TG3_NVM_HWSB_CFG1_MINSFT;

	snम_लिखो(&tp->fw_ver[0], 32, "sb v%d.%02d", major, minor);
पूर्ण

अटल व्योम tg3_पढ़ो_sb_ver(काष्ठा tg3 *tp, u32 val)
अणु
	u32 offset, major, minor, build;

	म_जोड़न(tp->fw_ver, "sb", TG3_VER_SIZE - म_माप(tp->fw_ver) - 1);

	अगर ((val & TG3_EEPROM_SB_FORMAT_MASK) != TG3_EEPROM_SB_FORMAT_1)
		वापस;

	चयन (val & TG3_EEPROM_SB_REVISION_MASK) अणु
	हाल TG3_EEPROM_SB_REVISION_0:
		offset = TG3_EEPROM_SB_F1R0_EDH_OFF;
		अवरोध;
	हाल TG3_EEPROM_SB_REVISION_2:
		offset = TG3_EEPROM_SB_F1R2_EDH_OFF;
		अवरोध;
	हाल TG3_EEPROM_SB_REVISION_3:
		offset = TG3_EEPROM_SB_F1R3_EDH_OFF;
		अवरोध;
	हाल TG3_EEPROM_SB_REVISION_4:
		offset = TG3_EEPROM_SB_F1R4_EDH_OFF;
		अवरोध;
	हाल TG3_EEPROM_SB_REVISION_5:
		offset = TG3_EEPROM_SB_F1R5_EDH_OFF;
		अवरोध;
	हाल TG3_EEPROM_SB_REVISION_6:
		offset = TG3_EEPROM_SB_F1R6_EDH_OFF;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (tg3_nvram_पढ़ो(tp, offset, &val))
		वापस;

	build = (val & TG3_EEPROM_SB_EDH_BLD_MASK) >>
		TG3_EEPROM_SB_EDH_BLD_SHFT;
	major = (val & TG3_EEPROM_SB_EDH_MAJ_MASK) >>
		TG3_EEPROM_SB_EDH_MAJ_SHFT;
	minor =  val & TG3_EEPROM_SB_EDH_MIN_MASK;

	अगर (minor > 99 || build > 26)
		वापस;

	offset = म_माप(tp->fw_ver);
	snम_लिखो(&tp->fw_ver[offset], TG3_VER_SIZE - offset,
		 " v%d.%02d", major, minor);

	अगर (build > 0) अणु
		offset = म_माप(tp->fw_ver);
		अगर (offset < TG3_VER_SIZE - 1)
			tp->fw_ver[offset] = 'a' + build - 1;
	पूर्ण
पूर्ण

अटल व्योम tg3_पढ़ो_mgmtfw_ver(काष्ठा tg3 *tp)
अणु
	u32 val, offset, start;
	पूर्णांक i, vlen;

	क्रम (offset = TG3_NVM_सूची_START;
	     offset < TG3_NVM_सूची_END;
	     offset += TG3_NVM_सूचीENT_SIZE) अणु
		अगर (tg3_nvram_पढ़ो(tp, offset, &val))
			वापस;

		अगर ((val >> TG3_NVM_सूचीTYPE_SHIFT) == TG3_NVM_सूचीTYPE_ASFINI)
			अवरोध;
	पूर्ण

	अगर (offset == TG3_NVM_सूची_END)
		वापस;

	अगर (!tg3_flag(tp, 5705_PLUS))
		start = 0x08000000;
	अन्यथा अगर (tg3_nvram_पढ़ो(tp, offset - 4, &start))
		वापस;

	अगर (tg3_nvram_पढ़ो(tp, offset + 4, &offset) ||
	    !tg3_fw_img_is_valid(tp, offset) ||
	    tg3_nvram_पढ़ो(tp, offset + 8, &val))
		वापस;

	offset += val - start;

	vlen = म_माप(tp->fw_ver);

	tp->fw_ver[vlen++] = ',';
	tp->fw_ver[vlen++] = ' ';

	क्रम (i = 0; i < 4; i++) अणु
		__be32 v;
		अगर (tg3_nvram_पढ़ो_be32(tp, offset, &v))
			वापस;

		offset += माप(v);

		अगर (vlen > TG3_VER_SIZE - माप(v)) अणु
			स_नकल(&tp->fw_ver[vlen], &v, TG3_VER_SIZE - vlen);
			अवरोध;
		पूर्ण

		स_नकल(&tp->fw_ver[vlen], &v, माप(v));
		vlen += माप(v);
	पूर्ण
पूर्ण

अटल व्योम tg3_probe_ncsi(काष्ठा tg3 *tp)
अणु
	u32 apedata;

	apedata = tg3_ape_पढ़ो32(tp, TG3_APE_SEG_SIG);
	अगर (apedata != APE_SEG_SIG_MAGIC)
		वापस;

	apedata = tg3_ape_पढ़ो32(tp, TG3_APE_FW_STATUS);
	अगर (!(apedata & APE_FW_STATUS_READY))
		वापस;

	अगर (tg3_ape_पढ़ो32(tp, TG3_APE_FW_FEATURES) & TG3_APE_FW_FEATURE_NCSI)
		tg3_flag_set(tp, APE_HAS_NCSI);
पूर्ण

अटल व्योम tg3_पढ़ो_dash_ver(काष्ठा tg3 *tp)
अणु
	पूर्णांक vlen;
	u32 apedata;
	अक्षर *fwtype;

	apedata = tg3_ape_पढ़ो32(tp, TG3_APE_FW_VERSION);

	अगर (tg3_flag(tp, APE_HAS_NCSI))
		fwtype = "NCSI";
	अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_5725)
		fwtype = "SMASH";
	अन्यथा
		fwtype = "DASH";

	vlen = म_माप(tp->fw_ver);

	snम_लिखो(&tp->fw_ver[vlen], TG3_VER_SIZE - vlen, " %s v%d.%d.%d.%d",
		 fwtype,
		 (apedata & APE_FW_VERSION_MAJMSK) >> APE_FW_VERSION_MAJSFT,
		 (apedata & APE_FW_VERSION_MINMSK) >> APE_FW_VERSION_MINSFT,
		 (apedata & APE_FW_VERSION_REVMSK) >> APE_FW_VERSION_REVSFT,
		 (apedata & APE_FW_VERSION_BLDMSK));
पूर्ण

अटल व्योम tg3_पढ़ो_otp_ver(काष्ठा tg3 *tp)
अणु
	u32 val, val2;

	अगर (tg3_asic_rev(tp) != ASIC_REV_5762)
		वापस;

	अगर (!tg3_ape_otp_पढ़ो(tp, OTP_ADDRESS_MAGIC0, &val) &&
	    !tg3_ape_otp_पढ़ो(tp, OTP_ADDRESS_MAGIC0 + 4, &val2) &&
	    TG3_OTP_MAGIC0_VALID(val)) अणु
		u64 val64 = (u64) val << 32 | val2;
		u32 ver = 0;
		पूर्णांक i, vlen;

		क्रम (i = 0; i < 7; i++) अणु
			अगर ((val64 & 0xff) == 0)
				अवरोध;
			ver = val64 & 0xff;
			val64 >>= 8;
		पूर्ण
		vlen = म_माप(tp->fw_ver);
		snम_लिखो(&tp->fw_ver[vlen], TG3_VER_SIZE - vlen, " .%02d", ver);
	पूर्ण
पूर्ण

अटल व्योम tg3_पढ़ो_fw_ver(काष्ठा tg3 *tp)
अणु
	u32 val;
	bool vpd_vers = false;

	अगर (tp->fw_ver[0] != 0)
		vpd_vers = true;

	अगर (tg3_flag(tp, NO_NVRAM)) अणु
		म_जोड़ो(tp->fw_ver, "sb");
		tg3_पढ़ो_otp_ver(tp);
		वापस;
	पूर्ण

	अगर (tg3_nvram_पढ़ो(tp, 0, &val))
		वापस;

	अगर (val == TG3_EEPROM_MAGIC)
		tg3_पढ़ो_bc_ver(tp);
	अन्यथा अगर ((val & TG3_EEPROM_MAGIC_FW_MSK) == TG3_EEPROM_MAGIC_FW)
		tg3_पढ़ो_sb_ver(tp, val);
	अन्यथा अगर ((val & TG3_EEPROM_MAGIC_HW_MSK) == TG3_EEPROM_MAGIC_HW)
		tg3_पढ़ो_hwsb_ver(tp);

	अगर (tg3_flag(tp, ENABLE_ASF)) अणु
		अगर (tg3_flag(tp, ENABLE_APE)) अणु
			tg3_probe_ncsi(tp);
			अगर (!vpd_vers)
				tg3_पढ़ो_dash_ver(tp);
		पूर्ण अन्यथा अगर (!vpd_vers) अणु
			tg3_पढ़ो_mgmtfw_ver(tp);
		पूर्ण
	पूर्ण

	tp->fw_ver[TG3_VER_SIZE - 1] = 0;
पूर्ण

अटल अंतरभूत u32 tg3_rx_ret_ring_size(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, LRG_PROD_RING_CAP))
		वापस TG3_RX_RET_MAX_SIZE_5717;
	अन्यथा अगर (tg3_flag(tp, JUMBO_CAPABLE) && !tg3_flag(tp, 5780_CLASS))
		वापस TG3_RX_RET_MAX_SIZE_5700;
	अन्यथा
		वापस TG3_RX_RET_MAX_SIZE_5705;
पूर्ण

अटल स्थिर काष्ठा pci_device_id tg3_ग_लिखो_reorder_chipsets[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_FE_GATE_700C) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_8131_BRIDGE) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8385_0) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_dev *tg3_find_peer(काष्ठा tg3 *tp)
अणु
	काष्ठा pci_dev *peer;
	अचिन्हित पूर्णांक func, devnr = tp->pdev->devfn & ~7;

	क्रम (func = 0; func < 8; func++) अणु
		peer = pci_get_slot(tp->pdev->bus, devnr | func);
		अगर (peer && peer != tp->pdev)
			अवरोध;
		pci_dev_put(peer);
	पूर्ण
	/* 5704 can be configured in single-port mode, set peer to
	 * tp->pdev in that हाल.
	 */
	अगर (!peer) अणु
		peer = tp->pdev;
		वापस peer;
	पूर्ण

	/*
	 * We करोn't need to keep the refcount elevated; there's no way
	 * to हटाओ one half of this device without removing the other
	 */
	pci_dev_put(peer);

	वापस peer;
पूर्ण

अटल व्योम tg3_detect_asic_rev(काष्ठा tg3 *tp, u32 misc_ctrl_reg)
अणु
	tp->pci_chip_rev_id = misc_ctrl_reg >> MISC_HOST_CTRL_CHIPREV_SHIFT;
	अगर (tg3_asic_rev(tp) == ASIC_REV_USE_PROD_ID_REG) अणु
		u32 reg;

		/* All devices that use the alternate
		 * ASIC REV location have a CPMU.
		 */
		tg3_flag_set(tp, CPMU_PRESENT);

		अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_5717 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5717_C ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5718 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5719 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5720 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_57767 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_57764 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5762 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5725 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5727 ||
		    tp->pdev->device == TG3PCI_DEVICE_TIGON3_57787)
			reg = TG3PCI_GEN2_PRODID_ASICREV;
		अन्यथा अगर (tp->pdev->device == TG3PCI_DEVICE_TIGON3_57781 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57785 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57761 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57765 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57791 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57795 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57762 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57766 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57782 ||
			 tp->pdev->device == TG3PCI_DEVICE_TIGON3_57786)
			reg = TG3PCI_GEN15_PRODID_ASICREV;
		अन्यथा
			reg = TG3PCI_PRODID_ASICREV;

		pci_पढ़ो_config_dword(tp->pdev, reg, &tp->pci_chip_rev_id);
	पूर्ण

	/* Wrong chip ID in 5752 A0. This code can be हटाओd later
	 * as A0 is not in production.
	 */
	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5752_A0_HW)
		tp->pci_chip_rev_id = CHIPREV_ID_5752_A0;

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5717_C0)
		tp->pci_chip_rev_id = CHIPREV_ID_5720_A0;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720)
		tg3_flag_set(tp, 5717_PLUS);

	अगर (tg3_asic_rev(tp) == ASIC_REV_57765 ||
	    tg3_asic_rev(tp) == ASIC_REV_57766)
		tg3_flag_set(tp, 57765_CLASS);

	अगर (tg3_flag(tp, 57765_CLASS) || tg3_flag(tp, 5717_PLUS) ||
	     tg3_asic_rev(tp) == ASIC_REV_5762)
		tg3_flag_set(tp, 57765_PLUS);

	/* Intentionally exclude ASIC_REV_5906 */
	अगर (tg3_asic_rev(tp) == ASIC_REV_5755 ||
	    tg3_asic_rev(tp) == ASIC_REV_5787 ||
	    tg3_asic_rev(tp) == ASIC_REV_5784 ||
	    tg3_asic_rev(tp) == ASIC_REV_5761 ||
	    tg3_asic_rev(tp) == ASIC_REV_5785 ||
	    tg3_asic_rev(tp) == ASIC_REV_57780 ||
	    tg3_flag(tp, 57765_PLUS))
		tg3_flag_set(tp, 5755_PLUS);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5780 ||
	    tg3_asic_rev(tp) == ASIC_REV_5714)
		tg3_flag_set(tp, 5780_CLASS);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5750 ||
	    tg3_asic_rev(tp) == ASIC_REV_5752 ||
	    tg3_asic_rev(tp) == ASIC_REV_5906 ||
	    tg3_flag(tp, 5755_PLUS) ||
	    tg3_flag(tp, 5780_CLASS))
		tg3_flag_set(tp, 5750_PLUS);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5705 ||
	    tg3_flag(tp, 5750_PLUS))
		tg3_flag_set(tp, 5705_PLUS);
पूर्ण

अटल bool tg3_10_100_only_device(काष्ठा tg3 *tp,
				   स्थिर काष्ठा pci_device_id *ent)
अणु
	u32 grc_misc_cfg = tr32(GRC_MISC_CFG) & GRC_MISC_CFG_BOARD_ID_MASK;

	अगर ((tg3_asic_rev(tp) == ASIC_REV_5703 &&
	     (grc_misc_cfg == 0x8000 || grc_misc_cfg == 0x4000)) ||
	    (tp->phy_flags & TG3_PHYFLG_IS_FET))
		वापस true;

	अगर (ent->driver_data & TG3_DRV_DATA_FLAG_10_100_ONLY) अणु
		अगर (tg3_asic_rev(tp) == ASIC_REV_5705) अणु
			अगर (ent->driver_data & TG3_DRV_DATA_FLAG_5705_10_100)
				वापस true;
		पूर्ण अन्यथा अणु
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tg3_get_invariants(काष्ठा tg3 *tp, स्थिर काष्ठा pci_device_id *ent)
अणु
	u32 misc_ctrl_reg;
	u32 pci_state_reg, grc_misc_cfg;
	u32 val;
	u16 pci_cmd;
	पूर्णांक err;

	/* Force memory ग_लिखो invalidate off.  If we leave it on,
	 * then on 5700_BX chips we have to enable a workaround.
	 * The workaround is to set the TG3PCI_DMA_RW_CTRL boundary
	 * to match the cacheline size.  The Broadcom driver have this
	 * workaround but turns MWI off all the बार so never uses
	 * it.  This seems to suggest that the workaround is insufficient.
	 */
	pci_पढ़ो_config_word(tp->pdev, PCI_COMMAND, &pci_cmd);
	pci_cmd &= ~PCI_COMMAND_INVALIDATE;
	pci_ग_लिखो_config_word(tp->pdev, PCI_COMMAND, pci_cmd);

	/* Important! -- Make sure रेजिस्टर accesses are byteswapped
	 * correctly.  Also, क्रम those chips that require it, make
	 * sure that indirect रेजिस्टर accesses are enabled beक्रमe
	 * the first operation.
	 */
	pci_पढ़ो_config_dword(tp->pdev, TG3PCI_MISC_HOST_CTRL,
			      &misc_ctrl_reg);
	tp->misc_host_ctrl |= (misc_ctrl_reg &
			       MISC_HOST_CTRL_CHIPREV);
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MISC_HOST_CTRL,
			       tp->misc_host_ctrl);

	tg3_detect_asic_rev(tp, misc_ctrl_reg);

	/* If we have 5702/03 A1 or A2 on certain ICH chipsets,
	 * we need to disable memory and use config. cycles
	 * only to access all रेजिस्टरs. The 5702/03 chips
	 * can mistakenly decode the special cycles from the
	 * ICH chipsets as memory ग_लिखो cycles, causing corruption
	 * of रेजिस्टर and memory space. Only certain ICH bridges
	 * will drive special cycles with non-zero data during the
	 * address phase which can fall within the 5703's address
	 * range. This is not an ICH bug as the PCI spec allows
	 * non-zero address during special cycles. However, only
	 * these ICH bridges are known to drive non-zero addresses
	 * during special cycles.
	 *
	 * Since special cycles करो not cross PCI bridges, we only
	 * enable this workaround अगर the 5703 is on the secondary
	 * bus of these ICH bridges.
	 */
	अगर ((tg3_chip_rev_id(tp) == CHIPREV_ID_5703_A1) ||
	    (tg3_chip_rev_id(tp) == CHIPREV_ID_5703_A2)) अणु
		अटल काष्ठा tg3_dev_id अणु
			u32	venकरोr;
			u32	device;
			u32	rev;
		पूर्ण ich_chipsets[] = अणु
			अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801AA_8,
			  PCI_ANY_ID पूर्ण,
			अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801AB_8,
			  PCI_ANY_ID पूर्ण,
			अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801BA_11,
			  0xa पूर्ण,
			अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801BA_6,
			  PCI_ANY_ID पूर्ण,
			अणु पूर्ण,
		पूर्ण;
		काष्ठा tg3_dev_id *pci_id = &ich_chipsets[0];
		काष्ठा pci_dev *bridge = शून्य;

		जबतक (pci_id->venकरोr != 0) अणु
			bridge = pci_get_device(pci_id->venकरोr, pci_id->device,
						bridge);
			अगर (!bridge) अणु
				pci_id++;
				जारी;
			पूर्ण
			अगर (pci_id->rev != PCI_ANY_ID) अणु
				अगर (bridge->revision > pci_id->rev)
					जारी;
			पूर्ण
			अगर (bridge->subordinate &&
			    (bridge->subordinate->number ==
			     tp->pdev->bus->number)) अणु
				tg3_flag_set(tp, ICH_WORKAROUND);
				pci_dev_put(bridge);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5701) अणु
		अटल काष्ठा tg3_dev_id अणु
			u32	venकरोr;
			u32	device;
		पूर्ण bridge_chipsets[] = अणु
			अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PXH_0 पूर्ण,
			अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PXH_1 पूर्ण,
			अणु पूर्ण,
		पूर्ण;
		काष्ठा tg3_dev_id *pci_id = &bridge_chipsets[0];
		काष्ठा pci_dev *bridge = शून्य;

		जबतक (pci_id->venकरोr != 0) अणु
			bridge = pci_get_device(pci_id->venकरोr,
						pci_id->device,
						bridge);
			अगर (!bridge) अणु
				pci_id++;
				जारी;
			पूर्ण
			अगर (bridge->subordinate &&
			    (bridge->subordinate->number <=
			     tp->pdev->bus->number) &&
			    (bridge->subordinate->busn_res.end >=
			     tp->pdev->bus->number)) अणु
				tg3_flag_set(tp, 5701_DMA_BUG);
				pci_dev_put(bridge);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* The EPB bridge inside 5714, 5715, and 5780 cannot support
	 * DMA addresses > 40-bit. This bridge may have other additional
	 * 57xx devices behind it in some 4-port NIC designs क्रम example.
	 * Any tg3 device found behind the bridge will also need the 40-bit
	 * DMA workaround.
	 */
	अगर (tg3_flag(tp, 5780_CLASS)) अणु
		tg3_flag_set(tp, 40BIT_DMA_BUG);
		tp->msi_cap = tp->pdev->msi_cap;
	पूर्ण अन्यथा अणु
		काष्ठा pci_dev *bridge = शून्य;

		करो अणु
			bridge = pci_get_device(PCI_VENDOR_ID_SERVERWORKS,
						PCI_DEVICE_ID_SERVERWORKS_EPB,
						bridge);
			अगर (bridge && bridge->subordinate &&
			    (bridge->subordinate->number <=
			     tp->pdev->bus->number) &&
			    (bridge->subordinate->busn_res.end >=
			     tp->pdev->bus->number)) अणु
				tg3_flag_set(tp, 40BIT_DMA_BUG);
				pci_dev_put(bridge);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (bridge);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5704 ||
	    tg3_asic_rev(tp) == ASIC_REV_5714)
		tp->pdev_peer = tg3_find_peer(tp);

	/* Determine TSO capabilities */
	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5719_A0)
		; /* Do nothing. HW bug. */
	अन्यथा अगर (tg3_flag(tp, 57765_PLUS))
		tg3_flag_set(tp, HW_TSO_3);
	अन्यथा अगर (tg3_flag(tp, 5755_PLUS) ||
		 tg3_asic_rev(tp) == ASIC_REV_5906)
		tg3_flag_set(tp, HW_TSO_2);
	अन्यथा अगर (tg3_flag(tp, 5750_PLUS)) अणु
		tg3_flag_set(tp, HW_TSO_1);
		tg3_flag_set(tp, TSO_BUG);
		अगर (tg3_asic_rev(tp) == ASIC_REV_5750 &&
		    tg3_chip_rev_id(tp) >= CHIPREV_ID_5750_C2)
			tg3_flag_clear(tp, TSO_BUG);
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) != ASIC_REV_5700 &&
		   tg3_asic_rev(tp) != ASIC_REV_5701 &&
		   tg3_chip_rev_id(tp) != CHIPREV_ID_5705_A0) अणु
		tg3_flag_set(tp, FW_TSO);
		tg3_flag_set(tp, TSO_BUG);
		अगर (tg3_asic_rev(tp) == ASIC_REV_5705)
			tp->fw_needed = FIRMWARE_TG3TSO5;
		अन्यथा
			tp->fw_needed = FIRMWARE_TG3TSO;
	पूर्ण

	/* Selectively allow TSO based on operating conditions */
	अगर (tg3_flag(tp, HW_TSO_1) ||
	    tg3_flag(tp, HW_TSO_2) ||
	    tg3_flag(tp, HW_TSO_3) ||
	    tg3_flag(tp, FW_TSO)) अणु
		/* For firmware TSO, assume ASF is disabled.
		 * We'll disable TSO later अगर we discover ASF
		 * is enabled in tg3_get_eeprom_hw_cfg().
		 */
		tg3_flag_set(tp, TSO_CAPABLE);
	पूर्ण अन्यथा अणु
		tg3_flag_clear(tp, TSO_CAPABLE);
		tg3_flag_clear(tp, TSO_BUG);
		tp->fw_needed = शून्य;
	पूर्ण

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0)
		tp->fw_needed = FIRMWARE_TG3;

	अगर (tg3_asic_rev(tp) == ASIC_REV_57766)
		tp->fw_needed = FIRMWARE_TG357766;

	tp->irq_max = 1;

	अगर (tg3_flag(tp, 5750_PLUS)) अणु
		tg3_flag_set(tp, SUPPORT_MSI);
		अगर (tg3_chip_rev(tp) == CHIPREV_5750_AX ||
		    tg3_chip_rev(tp) == CHIPREV_5750_BX ||
		    (tg3_asic_rev(tp) == ASIC_REV_5714 &&
		     tg3_chip_rev_id(tp) <= CHIPREV_ID_5714_A2 &&
		     tp->pdev_peer == tp->pdev))
			tg3_flag_clear(tp, SUPPORT_MSI);

		अगर (tg3_flag(tp, 5755_PLUS) ||
		    tg3_asic_rev(tp) == ASIC_REV_5906) अणु
			tg3_flag_set(tp, 1SHOT_MSI);
		पूर्ण

		अगर (tg3_flag(tp, 57765_PLUS)) अणु
			tg3_flag_set(tp, SUPPORT_MSIX);
			tp->irq_max = TG3_IRQ_MAX_VECS;
		पूर्ण
	पूर्ण

	tp->txq_max = 1;
	tp->rxq_max = 1;
	अगर (tp->irq_max > 1) अणु
		tp->rxq_max = TG3_RSS_MAX_NUM_QS;
		tg3_rss_init_dflt_indir_tbl(tp, TG3_RSS_MAX_NUM_QS);

		अगर (tg3_asic_rev(tp) == ASIC_REV_5719 ||
		    tg3_asic_rev(tp) == ASIC_REV_5720)
			tp->txq_max = tp->irq_max - 1;
	पूर्ण

	अगर (tg3_flag(tp, 5755_PLUS) ||
	    tg3_asic_rev(tp) == ASIC_REV_5906)
		tg3_flag_set(tp, SHORT_DMA_BUG);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5719)
		tp->dma_limit = TG3_TX_BD_DMA_MAX_4K;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762)
		tg3_flag_set(tp, LRG_PROD_RING_CAP);

	अगर (tg3_flag(tp, 57765_PLUS) &&
	    tg3_chip_rev_id(tp) != CHIPREV_ID_5719_A0)
		tg3_flag_set(tp, USE_JUMBO_BDFLAG);

	अगर (!tg3_flag(tp, 5705_PLUS) ||
	    tg3_flag(tp, 5780_CLASS) ||
	    tg3_flag(tp, USE_JUMBO_BDFLAG))
		tg3_flag_set(tp, JUMBO_CAPABLE);

	pci_पढ़ो_config_dword(tp->pdev, TG3PCI_PCISTATE,
			      &pci_state_reg);

	अगर (pci_is_pcie(tp->pdev)) अणु
		u16 lnkctl;

		tg3_flag_set(tp, PCI_EXPRESS);

		pcie_capability_पढ़ो_word(tp->pdev, PCI_EXP_LNKCTL, &lnkctl);
		अगर (lnkctl & PCI_EXP_LNKCTL_CLKREQ_EN) अणु
			अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
				tg3_flag_clear(tp, HW_TSO_2);
				tg3_flag_clear(tp, TSO_CAPABLE);
			पूर्ण
			अगर (tg3_asic_rev(tp) == ASIC_REV_5784 ||
			    tg3_asic_rev(tp) == ASIC_REV_5761 ||
			    tg3_chip_rev_id(tp) == CHIPREV_ID_57780_A0 ||
			    tg3_chip_rev_id(tp) == CHIPREV_ID_57780_A1)
				tg3_flag_set(tp, CLKREQ_BUG);
		पूर्ण अन्यथा अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5717_A0) अणु
			tg3_flag_set(tp, L1PLLPD_EN);
		पूर्ण
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5785) अणु
		/* BCM5785 devices are effectively PCIe devices, and should
		 * follow PCIe codepaths, but करो not have a PCIe capabilities
		 * section.
		 */
		tg3_flag_set(tp, PCI_EXPRESS);
	पूर्ण अन्यथा अगर (!tg3_flag(tp, 5705_PLUS) ||
		   tg3_flag(tp, 5780_CLASS)) अणु
		tp->pcix_cap = pci_find_capability(tp->pdev, PCI_CAP_ID_PCIX);
		अगर (!tp->pcix_cap) अणु
			dev_err(&tp->pdev->dev,
				"Cannot find PCI-X capability, aborting\n");
			वापस -EIO;
		पूर्ण

		अगर (!(pci_state_reg & PCISTATE_CONV_PCI_MODE))
			tg3_flag_set(tp, PCIX_MODE);
	पूर्ण

	/* If we have an AMD 762 or VIA K8T800 chipset, ग_लिखो
	 * reordering to the mailbox रेजिस्टरs करोne by the host
	 * controller can cause major troubles.  We पढ़ो back from
	 * every mailbox रेजिस्टर ग_लिखो to क्रमce the ग_लिखोs to be
	 * posted to the chip in order.
	 */
	अगर (pci_dev_present(tg3_ग_लिखो_reorder_chipsets) &&
	    !tg3_flag(tp, PCI_EXPRESS))
		tg3_flag_set(tp, MBOX_WRITE_REORDER);

	pci_पढ़ो_config_byte(tp->pdev, PCI_CACHE_LINE_SIZE,
			     &tp->pci_cacheline_sz);
	pci_पढ़ो_config_byte(tp->pdev, PCI_LATENCY_TIMER,
			     &tp->pci_lat_समयr);
	अगर (tg3_asic_rev(tp) == ASIC_REV_5703 &&
	    tp->pci_lat_समयr < 64) अणु
		tp->pci_lat_समयr = 64;
		pci_ग_लिखो_config_byte(tp->pdev, PCI_LATENCY_TIMER,
				      tp->pci_lat_समयr);
	पूर्ण

	/* Important! -- It is critical that the PCI-X hw workaround
	 * situation is decided beक्रमe the first MMIO रेजिस्टर access.
	 */
	अगर (tg3_chip_rev(tp) == CHIPREV_5700_BX) अणु
		/* 5700 BX chips need to have their TX producer index
		 * mailboxes written twice to workaround a bug.
		 */
		tg3_flag_set(tp, TXD_MBOX_HWBUG);

		/* If we are in PCI-X mode, enable रेजिस्टर ग_लिखो workaround.
		 *
		 * The workaround is to use indirect रेजिस्टर accesses
		 * क्रम all chip ग_लिखोs not to mailbox रेजिस्टरs.
		 */
		अगर (tg3_flag(tp, PCIX_MODE)) अणु
			u32 pm_reg;

			tg3_flag_set(tp, PCIX_TARGET_HWBUG);

			/* The chip can have it's घातer management PCI config
			 * space रेजिस्टरs clobbered due to this bug.
			 * So explicitly क्रमce the chip पूर्णांकo D0 here.
			 */
			pci_पढ़ो_config_dword(tp->pdev,
					      tp->pdev->pm_cap + PCI_PM_CTRL,
					      &pm_reg);
			pm_reg &= ~PCI_PM_CTRL_STATE_MASK;
			pm_reg |= PCI_PM_CTRL_PME_ENABLE | 0 /* D0 */;
			pci_ग_लिखो_config_dword(tp->pdev,
					       tp->pdev->pm_cap + PCI_PM_CTRL,
					       pm_reg);

			/* Also, क्रमce SERR#/PERR# in PCI command. */
			pci_पढ़ो_config_word(tp->pdev, PCI_COMMAND, &pci_cmd);
			pci_cmd |= PCI_COMMAND_PARITY | PCI_COMMAND_SERR;
			pci_ग_लिखो_config_word(tp->pdev, PCI_COMMAND, pci_cmd);
		पूर्ण
	पूर्ण

	अगर ((pci_state_reg & PCISTATE_BUS_SPEED_HIGH) != 0)
		tg3_flag_set(tp, PCI_HIGH_SPEED);
	अगर ((pci_state_reg & PCISTATE_BUS_32BIT) != 0)
		tg3_flag_set(tp, PCI_32BIT);

	/* Chip-specअगरic fixup from Broadcom driver */
	अगर ((tg3_chip_rev_id(tp) == CHIPREV_ID_5704_A0) &&
	    (!(pci_state_reg & PCISTATE_RETRY_SAME_DMA))) अणु
		pci_state_reg |= PCISTATE_RETRY_SAME_DMA;
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_PCISTATE, pci_state_reg);
	पूर्ण

	/* Default fast path रेजिस्टर access methods */
	tp->पढ़ो32 = tg3_पढ़ो32;
	tp->ग_लिखो32 = tg3_ग_लिखो32;
	tp->पढ़ो32_mbox = tg3_पढ़ो32;
	tp->ग_लिखो32_mbox = tg3_ग_लिखो32;
	tp->ग_लिखो32_tx_mbox = tg3_ग_लिखो32;
	tp->ग_लिखो32_rx_mbox = tg3_ग_लिखो32;

	/* Various workaround रेजिस्टर access methods */
	अगर (tg3_flag(tp, PCIX_TARGET_HWBUG))
		tp->ग_लिखो32 = tg3_ग_लिखो_indirect_reg32;
	अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5701 ||
		 (tg3_flag(tp, PCI_EXPRESS) &&
		  tg3_chip_rev_id(tp) == CHIPREV_ID_5750_A0)) अणु
		/*
		 * Back to back रेजिस्टर ग_लिखोs can cause problems on these
		 * chips, the workaround is to पढ़ो back all reg ग_लिखोs
		 * except those to mailbox regs.
		 *
		 * See tg3_ग_लिखो_indirect_reg32().
		 */
		tp->ग_लिखो32 = tg3_ग_लिखो_flush_reg32;
	पूर्ण

	अगर (tg3_flag(tp, TXD_MBOX_HWBUG) || tg3_flag(tp, MBOX_WRITE_REORDER)) अणु
		tp->ग_लिखो32_tx_mbox = tg3_ग_लिखो32_tx_mbox;
		अगर (tg3_flag(tp, MBOX_WRITE_REORDER))
			tp->ग_लिखो32_rx_mbox = tg3_ग_लिखो_flush_reg32;
	पूर्ण

	अगर (tg3_flag(tp, ICH_WORKAROUND)) अणु
		tp->पढ़ो32 = tg3_पढ़ो_indirect_reg32;
		tp->ग_लिखो32 = tg3_ग_लिखो_indirect_reg32;
		tp->पढ़ो32_mbox = tg3_पढ़ो_indirect_mbox;
		tp->ग_लिखो32_mbox = tg3_ग_लिखो_indirect_mbox;
		tp->ग_लिखो32_tx_mbox = tg3_ग_लिखो_indirect_mbox;
		tp->ग_लिखो32_rx_mbox = tg3_ग_लिखो_indirect_mbox;

		iounmap(tp->regs);
		tp->regs = शून्य;

		pci_पढ़ो_config_word(tp->pdev, PCI_COMMAND, &pci_cmd);
		pci_cmd &= ~PCI_COMMAND_MEMORY;
		pci_ग_लिखो_config_word(tp->pdev, PCI_COMMAND, pci_cmd);
	पूर्ण
	अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
		tp->पढ़ो32_mbox = tg3_पढ़ो32_mbox_5906;
		tp->ग_लिखो32_mbox = tg3_ग_लिखो32_mbox_5906;
		tp->ग_लिखो32_tx_mbox = tg3_ग_लिखो32_mbox_5906;
		tp->ग_लिखो32_rx_mbox = tg3_ग_लिखो32_mbox_5906;
	पूर्ण

	अगर (tp->ग_लिखो32 == tg3_ग_लिखो_indirect_reg32 ||
	    (tg3_flag(tp, PCIX_MODE) &&
	     (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	      tg3_asic_rev(tp) == ASIC_REV_5701)))
		tg3_flag_set(tp, SRAM_USE_CONFIG);

	/* The memory arbiter has to be enabled in order क्रम SRAM accesses
	 * to succeed.  Normally on घातerup the tg3 chip firmware will make
	 * sure it is enabled, but other entities such as प्रणाली netboot
	 * code might disable it.
	 */
	val = tr32(MEMARB_MODE);
	tw32(MEMARB_MODE, val | MEMARB_MODE_ENABLE);

	tp->pci_fn = PCI_FUNC(tp->pdev->devfn) & 3;
	अगर (tg3_asic_rev(tp) == ASIC_REV_5704 ||
	    tg3_flag(tp, 5780_CLASS)) अणु
		अगर (tg3_flag(tp, PCIX_MODE)) अणु
			pci_पढ़ो_config_dword(tp->pdev,
					      tp->pcix_cap + PCI_X_STATUS,
					      &val);
			tp->pci_fn = val & 0x7;
		पूर्ण
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
		   tg3_asic_rev(tp) == ASIC_REV_5719 ||
		   tg3_asic_rev(tp) == ASIC_REV_5720) अणु
		tg3_पढ़ो_mem(tp, NIC_SRAM_CPMU_STATUS, &val);
		अगर ((val & NIC_SRAM_CPMUSTAT_SIG_MSK) != NIC_SRAM_CPMUSTAT_SIG)
			val = tr32(TG3_CPMU_STATUS);

		अगर (tg3_asic_rev(tp) == ASIC_REV_5717)
			tp->pci_fn = (val & TG3_CPMU_STATUS_FMSK_5717) ? 1 : 0;
		अन्यथा
			tp->pci_fn = (val & TG3_CPMU_STATUS_FMSK_5719) >>
				     TG3_CPMU_STATUS_FSHFT_5719;
	पूर्ण

	अगर (tg3_flag(tp, FLUSH_POSTED_WRITES)) अणु
		tp->ग_लिखो32_tx_mbox = tg3_ग_लिखो_flush_reg32;
		tp->ग_लिखो32_rx_mbox = tg3_ग_लिखो_flush_reg32;
	पूर्ण

	/* Get eeprom hw config beक्रमe calling tg3_set_घातer_state().
	 * In particular, the TG3_FLAG_IS_NIC flag must be
	 * determined beक्रमe calling tg3_set_घातer_state() so that
	 * we know whether or not to चयन out of Vaux घातer.
	 * When the flag is set, it means that GPIO1 is used क्रम eeprom
	 * ग_लिखो protect and also implies that it is a LOM where GPIOs
	 * are not used to चयन घातer.
	 */
	tg3_get_eeprom_hw_cfg(tp);

	अगर (tg3_flag(tp, FW_TSO) && tg3_flag(tp, ENABLE_ASF)) अणु
		tg3_flag_clear(tp, TSO_CAPABLE);
		tg3_flag_clear(tp, TSO_BUG);
		tp->fw_needed = शून्य;
	पूर्ण

	अगर (tg3_flag(tp, ENABLE_APE)) अणु
		/* Allow पढ़ोs and ग_लिखोs to the
		 * APE रेजिस्टर and memory space.
		 */
		pci_state_reg |= PCISTATE_ALLOW_APE_CTLSPC_WR |
				 PCISTATE_ALLOW_APE_SHMEM_WR |
				 PCISTATE_ALLOW_APE_PSPACE_WR;
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_PCISTATE,
				       pci_state_reg);

		tg3_ape_lock_init(tp);
		tp->ape_hb_पूर्णांकerval =
			msecs_to_jअगरfies(APE_HOST_HEARTBEAT_INT_5SEC);
	पूर्ण

	/* Set up tp->grc_local_ctrl beक्रमe calling
	 * tg3_pwrsrc_चयन_to_vमुख्य().  GPIO1 driven high
	 * will bring 5700's बाह्यal PHY out of reset.
	 * It is also used as eeprom ग_लिखो protect on LOMs.
	 */
	tp->grc_local_ctrl = GRC_LCLCTRL_INT_ON_ATTN | GRC_LCLCTRL_AUTO_SEEPROM;
	अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_flag(tp, EEPROM_WRITE_PROT))
		tp->grc_local_ctrl |= (GRC_LCLCTRL_GPIO_OE1 |
				       GRC_LCLCTRL_GPIO_OUTPUT1);
	/* Unused GPIO3 must be driven as output on 5752 because there
	 * are no pull-up resistors on unused GPIO pins.
	 */
	अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5752)
		tp->grc_local_ctrl |= GRC_LCLCTRL_GPIO_OE3;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5755 ||
	    tg3_asic_rev(tp) == ASIC_REV_57780 ||
	    tg3_flag(tp, 57765_CLASS))
		tp->grc_local_ctrl |= GRC_LCLCTRL_GPIO_UART_SEL;

	अगर (tp->pdev->device == PCI_DEVICE_ID_TIGON3_5761 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5761S) अणु
		/* Turn off the debug UART. */
		tp->grc_local_ctrl |= GRC_LCLCTRL_GPIO_UART_SEL;
		अगर (tg3_flag(tp, IS_NIC))
			/* Keep VMain घातer. */
			tp->grc_local_ctrl |= GRC_LCLCTRL_GPIO_OE0 |
					      GRC_LCLCTRL_GPIO_OUTPUT0;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5762)
		tp->grc_local_ctrl |=
			tr32(GRC_LOCAL_CTRL) & GRC_LCLCTRL_GPIO_UART_SEL;

	/* Switch out of Vaux अगर it is a NIC */
	tg3_pwrsrc_चयन_to_vमुख्य(tp);

	/* Derive initial jumbo mode from MTU asचिन्हित in
	 * ether_setup() via the alloc_etherdev() call
	 */
	अगर (tp->dev->mtu > ETH_DATA_LEN && !tg3_flag(tp, 5780_CLASS))
		tg3_flag_set(tp, JUMBO_RING_ENABLE);

	/* Determine WakeOnLan speed to use. */
	अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0 ||
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B0 ||
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B2) अणु
		tg3_flag_clear(tp, WOL_SPEED_100MB);
	पूर्ण अन्यथा अणु
		tg3_flag_set(tp, WOL_SPEED_100MB);
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5906)
		tp->phy_flags |= TG3_PHYFLG_IS_FET;

	/* A few boards करोn't want Ethernet@WireSpeed phy feature */
	अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    (tg3_asic_rev(tp) == ASIC_REV_5705 &&
	     (tg3_chip_rev_id(tp) != CHIPREV_ID_5705_A0) &&
	     (tg3_chip_rev_id(tp) != CHIPREV_ID_5705_A1)) ||
	    (tp->phy_flags & TG3_PHYFLG_IS_FET) ||
	    (tp->phy_flags & TG3_PHYFLG_ANY_SERDES))
		tp->phy_flags |= TG3_PHYFLG_NO_ETH_WIRE_SPEED;

	अगर (tg3_chip_rev(tp) == CHIPREV_5703_AX ||
	    tg3_chip_rev(tp) == CHIPREV_5704_AX)
		tp->phy_flags |= TG3_PHYFLG_ADC_BUG;
	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5704_A0)
		tp->phy_flags |= TG3_PHYFLG_5704_A0_BUG;

	अगर (tg3_flag(tp, 5705_PLUS) &&
	    !(tp->phy_flags & TG3_PHYFLG_IS_FET) &&
	    tg3_asic_rev(tp) != ASIC_REV_5785 &&
	    tg3_asic_rev(tp) != ASIC_REV_57780 &&
	    !tg3_flag(tp, 57765_PLUS)) अणु
		अगर (tg3_asic_rev(tp) == ASIC_REV_5755 ||
		    tg3_asic_rev(tp) == ASIC_REV_5787 ||
		    tg3_asic_rev(tp) == ASIC_REV_5784 ||
		    tg3_asic_rev(tp) == ASIC_REV_5761) अणु
			अगर (tp->pdev->device != PCI_DEVICE_ID_TIGON3_5756 &&
			    tp->pdev->device != PCI_DEVICE_ID_TIGON3_5722)
				tp->phy_flags |= TG3_PHYFLG_JITTER_BUG;
			अगर (tp->pdev->device == PCI_DEVICE_ID_TIGON3_5755M)
				tp->phy_flags |= TG3_PHYFLG_ADJUST_TRIM;
		पूर्ण अन्यथा
			tp->phy_flags |= TG3_PHYFLG_BER_BUG;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5784 &&
	    tg3_chip_rev(tp) != CHIPREV_5784_AX) अणु
		tp->phy_otp = tg3_पढ़ो_otp_phycfg(tp);
		अगर (tp->phy_otp == 0)
			tp->phy_otp = TG3_OTP_DEFAULT;
	पूर्ण

	अगर (tg3_flag(tp, CPMU_PRESENT))
		tp->mi_mode = MAC_MI_MODE_500KHZ_CONST;
	अन्यथा
		tp->mi_mode = MAC_MI_MODE_BASE;

	tp->coalesce_mode = 0;
	अगर (tg3_chip_rev(tp) != CHIPREV_5700_AX &&
	    tg3_chip_rev(tp) != CHIPREV_5700_BX)
		tp->coalesce_mode |= HOSTCC_MODE_32BYTE;

	/* Set these bits to enable statistics workaround. */
	अगर (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762 ||
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5719_A0 ||
	    tg3_chip_rev_id(tp) == CHIPREV_ID_5720_A0) अणु
		tp->coalesce_mode |= HOSTCC_MODE_ATTN;
		tp->grc_mode |= GRC_MODE_IRQ_ON_FLOW_ATTN;
	पूर्ण

	अगर (tg3_asic_rev(tp) == ASIC_REV_5785 ||
	    tg3_asic_rev(tp) == ASIC_REV_57780)
		tg3_flag_set(tp, USE_PHYLIB);

	err = tg3_mdio_init(tp);
	अगर (err)
		वापस err;

	/* Initialize data/descriptor byte/word swapping. */
	val = tr32(GRC_MODE);
	अगर (tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762)
		val &= (GRC_MODE_BYTE_SWAP_B2HRX_DATA |
			GRC_MODE_WORD_SWAP_B2HRX_DATA |
			GRC_MODE_B2HRX_ENABLE |
			GRC_MODE_HTX2B_ENABLE |
			GRC_MODE_HOST_STACKUP);
	अन्यथा
		val &= GRC_MODE_HOST_STACKUP;

	tw32(GRC_MODE, val | tp->grc_mode);

	tg3_चयन_घड़ीs(tp);

	/* Clear this out क्रम sanity. */
	tw32(TG3PCI_MEM_WIN_BASE_ADDR, 0);

	/* Clear TG3PCI_REG_BASE_ADDR to prevent hangs. */
	tw32(TG3PCI_REG_BASE_ADDR, 0);

	pci_पढ़ो_config_dword(tp->pdev, TG3PCI_PCISTATE,
			      &pci_state_reg);
	अगर ((pci_state_reg & PCISTATE_CONV_PCI_MODE) == 0 &&
	    !tg3_flag(tp, PCIX_TARGET_HWBUG)) अणु
		अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5701_A0 ||
		    tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B0 ||
		    tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B2 ||
		    tg3_chip_rev_id(tp) == CHIPREV_ID_5701_B5) अणु
			व्योम __iomem *sram_base;

			/* Write some dummy words पूर्णांकo the SRAM status block
			 * area, see अगर it पढ़ोs back correctly.  If the वापस
			 * value is bad, क्रमce enable the PCIX workaround.
			 */
			sram_base = tp->regs + NIC_SRAM_WIN_BASE + NIC_SRAM_STATS_BLK;

			ग_लिखोl(0x00000000, sram_base);
			ग_लिखोl(0x00000000, sram_base + 4);
			ग_लिखोl(0xffffffff, sram_base + 4);
			अगर (पढ़ोl(sram_base) != 0x00000000)
				tg3_flag_set(tp, PCIX_TARGET_HWBUG);
		पूर्ण
	पूर्ण

	udelay(50);
	tg3_nvram_init(tp);

	/* If the device has an NVRAM, no need to load patch firmware */
	अगर (tg3_asic_rev(tp) == ASIC_REV_57766 &&
	    !tg3_flag(tp, NO_NVRAM))
		tp->fw_needed = शून्य;

	grc_misc_cfg = tr32(GRC_MISC_CFG);
	grc_misc_cfg &= GRC_MISC_CFG_BOARD_ID_MASK;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5705 &&
	    (grc_misc_cfg == GRC_MISC_CFG_BOARD_ID_5788 ||
	     grc_misc_cfg == GRC_MISC_CFG_BOARD_ID_5788M))
		tg3_flag_set(tp, IS_5788);

	अगर (!tg3_flag(tp, IS_5788) &&
	    tg3_asic_rev(tp) != ASIC_REV_5700)
		tg3_flag_set(tp, TAGGED_STATUS);
	अगर (tg3_flag(tp, TAGGED_STATUS)) अणु
		tp->coalesce_mode |= (HOSTCC_MODE_CLRTICK_RXBD |
				      HOSTCC_MODE_CLRTICK_TXBD);

		tp->misc_host_ctrl |= MISC_HOST_CTRL_TAGGED_STATUS;
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MISC_HOST_CTRL,
				       tp->misc_host_ctrl);
	पूर्ण

	/* Preserve the APE MAC_MODE bits */
	अगर (tg3_flag(tp, ENABLE_APE))
		tp->mac_mode = MAC_MODE_APE_TX_EN | MAC_MODE_APE_RX_EN;
	अन्यथा
		tp->mac_mode = 0;

	अगर (tg3_10_100_only_device(tp, ent))
		tp->phy_flags |= TG3_PHYFLG_10_100_ONLY;

	err = tg3_phy_probe(tp);
	अगर (err) अणु
		dev_err(&tp->pdev->dev, "phy probe failed, err %d\n", err);
		/* ... but करो not वापस immediately ... */
		tg3_mdio_fini(tp);
	पूर्ण

	tg3_पढ़ो_vpd(tp);
	tg3_पढ़ो_fw_ver(tp);

	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES) अणु
		tp->phy_flags &= ~TG3_PHYFLG_USE_MI_INTERRUPT;
	पूर्ण अन्यथा अणु
		अगर (tg3_asic_rev(tp) == ASIC_REV_5700)
			tp->phy_flags |= TG3_PHYFLG_USE_MI_INTERRUPT;
		अन्यथा
			tp->phy_flags &= ~TG3_PHYFLG_USE_MI_INTERRUPT;
	पूर्ण

	/* 5700 अणुAX,BXपूर्ण chips have a broken status block link
	 * change bit implementation, so we must use the
	 * status रेजिस्टर in those हालs.
	 */
	अगर (tg3_asic_rev(tp) == ASIC_REV_5700)
		tg3_flag_set(tp, USE_LINKCHG_REG);
	अन्यथा
		tg3_flag_clear(tp, USE_LINKCHG_REG);

	/* The led_ctrl is set during tg3_phy_probe, here we might
	 * have to क्रमce the link status polling mechanism based
	 * upon subप्रणाली IDs.
	 */
	अगर (tp->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_DELL &&
	    tg3_asic_rev(tp) == ASIC_REV_5701 &&
	    !(tp->phy_flags & TG3_PHYFLG_PHY_SERDES)) अणु
		tp->phy_flags |= TG3_PHYFLG_USE_MI_INTERRUPT;
		tg3_flag_set(tp, USE_LINKCHG_REG);
	पूर्ण

	/* For all SERDES we poll the MAC status रेजिस्टर. */
	अगर (tp->phy_flags & TG3_PHYFLG_PHY_SERDES)
		tg3_flag_set(tp, POLL_SERDES);
	अन्यथा
		tg3_flag_clear(tp, POLL_SERDES);

	अगर (tg3_flag(tp, ENABLE_APE) && tg3_flag(tp, ENABLE_ASF))
		tg3_flag_set(tp, POLL_CPMU_LINK);

	tp->rx_offset = NET_SKB_PAD + NET_IP_ALIGN;
	tp->rx_copy_thresh = TG3_RX_COPY_THRESHOLD;
	अगर (tg3_asic_rev(tp) == ASIC_REV_5701 &&
	    tg3_flag(tp, PCIX_MODE)) अणु
		tp->rx_offset = NET_SKB_PAD;
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
		tp->rx_copy_thresh = ~(u16)0;
#पूर्ण_अगर
	पूर्ण

	tp->rx_std_ring_mask = TG3_RX_STD_RING_SIZE(tp) - 1;
	tp->rx_jmb_ring_mask = TG3_RX_JMB_RING_SIZE(tp) - 1;
	tp->rx_ret_ring_mask = tg3_rx_ret_ring_size(tp) - 1;

	tp->rx_std_max_post = tp->rx_std_ring_mask + 1;

	/* Increment the rx prod index on the rx std ring by at most
	 * 8 क्रम these chips to workaround hw errata.
	 */
	अगर (tg3_asic_rev(tp) == ASIC_REV_5750 ||
	    tg3_asic_rev(tp) == ASIC_REV_5752 ||
	    tg3_asic_rev(tp) == ASIC_REV_5755)
		tp->rx_std_max_post = 8;

	अगर (tg3_flag(tp, ASPM_WORKAROUND))
		tp->pwrmgmt_thresh = tr32(PCIE_PWR_MGMT_THRESH) &
				     PCIE_PWR_MGMT_L1_THRESH_MSK;

	वापस err;
पूर्ण

अटल पूर्णांक tg3_get_device_address(काष्ठा tg3 *tp)
अणु
	काष्ठा net_device *dev = tp->dev;
	u32 hi, lo, mac_offset;
	पूर्णांक addr_ok = 0;
	पूर्णांक err;

	अगर (!eth_platक्रमm_get_mac_address(&tp->pdev->dev, dev->dev_addr))
		वापस 0;

	अगर (tg3_flag(tp, IS_SSB_CORE)) अणु
		err = ssb_gige_get_macaddr(tp->pdev, &dev->dev_addr[0]);
		अगर (!err && is_valid_ether_addr(&dev->dev_addr[0]))
			वापस 0;
	पूर्ण

	mac_offset = 0x7c;
	अगर (tg3_asic_rev(tp) == ASIC_REV_5704 ||
	    tg3_flag(tp, 5780_CLASS)) अणु
		अगर (tr32(TG3PCI_DUAL_MAC_CTRL) & DUAL_MAC_CTRL_ID)
			mac_offset = 0xcc;
		अगर (tg3_nvram_lock(tp))
			tw32_f(NVRAM_CMD, NVRAM_CMD_RESET);
		अन्यथा
			tg3_nvram_unlock(tp);
	पूर्ण अन्यथा अगर (tg3_flag(tp, 5717_PLUS)) अणु
		अगर (tp->pci_fn & 1)
			mac_offset = 0xcc;
		अगर (tp->pci_fn > 1)
			mac_offset += 0x18c;
	पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5906)
		mac_offset = 0x10;

	/* First try to get it from MAC address mailbox. */
	tg3_पढ़ो_mem(tp, NIC_SRAM_MAC_ADDR_HIGH_MBOX, &hi);
	अगर ((hi >> 16) == 0x484b) अणु
		dev->dev_addr[0] = (hi >>  8) & 0xff;
		dev->dev_addr[1] = (hi >>  0) & 0xff;

		tg3_पढ़ो_mem(tp, NIC_SRAM_MAC_ADDR_LOW_MBOX, &lo);
		dev->dev_addr[2] = (lo >> 24) & 0xff;
		dev->dev_addr[3] = (lo >> 16) & 0xff;
		dev->dev_addr[4] = (lo >>  8) & 0xff;
		dev->dev_addr[5] = (lo >>  0) & 0xff;

		/* Some old bootcode may report a 0 MAC address in SRAM */
		addr_ok = is_valid_ether_addr(&dev->dev_addr[0]);
	पूर्ण
	अगर (!addr_ok) अणु
		/* Next, try NVRAM. */
		अगर (!tg3_flag(tp, NO_NVRAM) &&
		    !tg3_nvram_पढ़ो_be32(tp, mac_offset + 0, &hi) &&
		    !tg3_nvram_पढ़ो_be32(tp, mac_offset + 4, &lo)) अणु
			स_नकल(&dev->dev_addr[0], ((अक्षर *)&hi) + 2, 2);
			स_नकल(&dev->dev_addr[2], (अक्षर *)&lo, माप(lo));
		पूर्ण
		/* Finally just fetch it out of the MAC control regs. */
		अन्यथा अणु
			hi = tr32(MAC_ADDR_0_HIGH);
			lo = tr32(MAC_ADDR_0_LOW);

			dev->dev_addr[5] = lo & 0xff;
			dev->dev_addr[4] = (lo >> 8) & 0xff;
			dev->dev_addr[3] = (lo >> 16) & 0xff;
			dev->dev_addr[2] = (lo >> 24) & 0xff;
			dev->dev_addr[1] = hi & 0xff;
			dev->dev_addr[0] = (hi >> 8) & 0xff;
		पूर्ण
	पूर्ण

	अगर (!is_valid_ether_addr(&dev->dev_addr[0]))
		वापस -EINVAL;
	वापस 0;
पूर्ण

#घोषणा BOUNDARY_SINGLE_CACHELINE	1
#घोषणा BOUNDARY_MULTI_CACHELINE	2

अटल u32 tg3_calc_dma_bndry(काष्ठा tg3 *tp, u32 val)
अणु
	पूर्णांक cacheline_size;
	u8 byte;
	पूर्णांक goal;

	pci_पढ़ो_config_byte(tp->pdev, PCI_CACHE_LINE_SIZE, &byte);
	अगर (byte == 0)
		cacheline_size = 1024;
	अन्यथा
		cacheline_size = (पूर्णांक) byte * 4;

	/* On 5703 and later chips, the boundary bits have no
	 * effect.
	 */
	अगर (tg3_asic_rev(tp) != ASIC_REV_5700 &&
	    tg3_asic_rev(tp) != ASIC_REV_5701 &&
	    !tg3_flag(tp, PCI_EXPRESS))
		जाओ out;

#अगर defined(CONFIG_PPC64) || defined(CONFIG_IA64) || defined(CONFIG_PARISC)
	goal = BOUNDARY_MULTI_CACHELINE;
#अन्यथा
#अगर defined(CONFIG_SPARC64) || defined(CONFIG_ALPHA)
	goal = BOUNDARY_SINGLE_CACHELINE;
#अन्यथा
	goal = 0;
#पूर्ण_अगर
#पूर्ण_अगर

	अगर (tg3_flag(tp, 57765_PLUS)) अणु
		val = goal ? 0 : DMA_RWCTRL_DIS_CACHE_ALIGNMENT;
		जाओ out;
	पूर्ण

	अगर (!goal)
		जाओ out;

	/* PCI controllers on most RISC प्रणालीs tend to disconnect
	 * when a device tries to burst across a cache-line boundary.
	 * Thereक्रमe, letting tg3 करो so just wastes PCI bandwidth.
	 *
	 * Unक्रमtunately, क्रम PCI-E there are only limited
	 * ग_लिखो-side controls क्रम this, and thus क्रम पढ़ोs
	 * we will still get the disconnects.  We'll also waste
	 * these PCI cycles क्रम both पढ़ो and ग_लिखो क्रम chips
	 * other than 5700 and 5701 which करो not implement the
	 * boundary bits.
	 */
	अगर (tg3_flag(tp, PCIX_MODE) && !tg3_flag(tp, PCI_EXPRESS)) अणु
		चयन (cacheline_size) अणु
		हाल 16:
		हाल 32:
		हाल 64:
		हाल 128:
			अगर (goal == BOUNDARY_SINGLE_CACHELINE) अणु
				val |= (DMA_RWCTRL_READ_BNDRY_128_PCIX |
					DMA_RWCTRL_WRITE_BNDRY_128_PCIX);
			पूर्ण अन्यथा अणु
				val |= (DMA_RWCTRL_READ_BNDRY_384_PCIX |
					DMA_RWCTRL_WRITE_BNDRY_384_PCIX);
			पूर्ण
			अवरोध;

		हाल 256:
			val |= (DMA_RWCTRL_READ_BNDRY_256_PCIX |
				DMA_RWCTRL_WRITE_BNDRY_256_PCIX);
			अवरोध;

		शेष:
			val |= (DMA_RWCTRL_READ_BNDRY_384_PCIX |
				DMA_RWCTRL_WRITE_BNDRY_384_PCIX);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (tg3_flag(tp, PCI_EXPRESS)) अणु
		चयन (cacheline_size) अणु
		हाल 16:
		हाल 32:
		हाल 64:
			अगर (goal == BOUNDARY_SINGLE_CACHELINE) अणु
				val &= ~DMA_RWCTRL_WRITE_BNDRY_DISAB_PCIE;
				val |= DMA_RWCTRL_WRITE_BNDRY_64_PCIE;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 128:
		शेष:
			val &= ~DMA_RWCTRL_WRITE_BNDRY_DISAB_PCIE;
			val |= DMA_RWCTRL_WRITE_BNDRY_128_PCIE;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cacheline_size) अणु
		हाल 16:
			अगर (goal == BOUNDARY_SINGLE_CACHELINE) अणु
				val |= (DMA_RWCTRL_READ_BNDRY_16 |
					DMA_RWCTRL_WRITE_BNDRY_16);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 32:
			अगर (goal == BOUNDARY_SINGLE_CACHELINE) अणु
				val |= (DMA_RWCTRL_READ_BNDRY_32 |
					DMA_RWCTRL_WRITE_BNDRY_32);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 64:
			अगर (goal == BOUNDARY_SINGLE_CACHELINE) अणु
				val |= (DMA_RWCTRL_READ_BNDRY_64 |
					DMA_RWCTRL_WRITE_BNDRY_64);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 128:
			अगर (goal == BOUNDARY_SINGLE_CACHELINE) अणु
				val |= (DMA_RWCTRL_READ_BNDRY_128 |
					DMA_RWCTRL_WRITE_BNDRY_128);
				अवरोध;
			पूर्ण
			fallthrough;
		हाल 256:
			val |= (DMA_RWCTRL_READ_BNDRY_256 |
				DMA_RWCTRL_WRITE_BNDRY_256);
			अवरोध;
		हाल 512:
			val |= (DMA_RWCTRL_READ_BNDRY_512 |
				DMA_RWCTRL_WRITE_BNDRY_512);
			अवरोध;
		हाल 1024:
		शेष:
			val |= (DMA_RWCTRL_READ_BNDRY_1024 |
				DMA_RWCTRL_WRITE_BNDRY_1024);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस val;
पूर्ण

अटल पूर्णांक tg3_करो_test_dma(काष्ठा tg3 *tp, u32 *buf, dma_addr_t buf_dma,
			   पूर्णांक size, bool to_device)
अणु
	काष्ठा tg3_पूर्णांकernal_buffer_desc test_desc;
	u32 sram_dma_descs;
	पूर्णांक i, ret;

	sram_dma_descs = NIC_SRAM_DMA_DESC_POOL_BASE;

	tw32(FTQ_RCVBD_COMP_FIFO_ENQDEQ, 0);
	tw32(FTQ_RCVDATA_COMP_FIFO_ENQDEQ, 0);
	tw32(RDMAC_STATUS, 0);
	tw32(WDMAC_STATUS, 0);

	tw32(BUFMGR_MODE, 0);
	tw32(FTQ_RESET, 0);

	test_desc.addr_hi = ((u64) buf_dma) >> 32;
	test_desc.addr_lo = buf_dma & 0xffffffff;
	test_desc.nic_mbuf = 0x00002100;
	test_desc.len = size;

	/*
	 * HP ZX1 was seeing test failures क्रम 5701 cards running at 33Mhz
	 * the *second* समय the tg3 driver was getting loaded after an
	 * initial scan.
	 *
	 * Broadcom tells me:
	 *   ...the DMA engine is connected to the GRC block and a DMA
	 *   reset may affect the GRC block in some unpredictable way...
	 *   The behavior of resets to inभागidual blocks has not been tested.
	 *
	 * Broadcom noted the GRC reset will also reset all sub-components.
	 */
	अगर (to_device) अणु
		test_desc.cqid_sqid = (13 << 8) | 2;

		tw32_f(RDMAC_MODE, RDMAC_MODE_ENABLE);
		udelay(40);
	पूर्ण अन्यथा अणु
		test_desc.cqid_sqid = (16 << 8) | 7;

		tw32_f(WDMAC_MODE, WDMAC_MODE_ENABLE);
		udelay(40);
	पूर्ण
	test_desc.flags = 0x00000005;

	क्रम (i = 0; i < (माप(test_desc) / माप(u32)); i++) अणु
		u32 val;

		val = *(((u32 *)&test_desc) + i);
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR,
				       sram_dma_descs + (i * माप(u32)));
		pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_DATA, val);
	पूर्ण
	pci_ग_लिखो_config_dword(tp->pdev, TG3PCI_MEM_WIN_BASE_ADDR, 0);

	अगर (to_device)
		tw32(FTQ_DMA_HIGH_READ_FIFO_ENQDEQ, sram_dma_descs);
	अन्यथा
		tw32(FTQ_DMA_HIGH_WRITE_FIFO_ENQDEQ, sram_dma_descs);

	ret = -ENODEV;
	क्रम (i = 0; i < 40; i++) अणु
		u32 val;

		अगर (to_device)
			val = tr32(FTQ_RCVBD_COMP_FIFO_ENQDEQ);
		अन्यथा
			val = tr32(FTQ_RCVDATA_COMP_FIFO_ENQDEQ);
		अगर ((val & 0xffff) == sram_dma_descs) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		udelay(100);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा TEST_BUFFER_SIZE	0x2000

अटल स्थिर काष्ठा pci_device_id tg3_dma_रुको_state_chipsets[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_UNI_N_PCI15) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक tg3_test_dma(काष्ठा tg3 *tp)
अणु
	dma_addr_t buf_dma;
	u32 *buf, saved_dma_rwctrl;
	पूर्णांक ret = 0;

	buf = dma_alloc_coherent(&tp->pdev->dev, TEST_BUFFER_SIZE,
				 &buf_dma, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out_noमुक्त;
	पूर्ण

	tp->dma_rwctrl = ((0x7 << DMA_RWCTRL_PCI_WRITE_CMD_SHIFT) |
			  (0x6 << DMA_RWCTRL_PCI_READ_CMD_SHIFT));

	tp->dma_rwctrl = tg3_calc_dma_bndry(tp, tp->dma_rwctrl);

	अगर (tg3_flag(tp, 57765_PLUS))
		जाओ out;

	अगर (tg3_flag(tp, PCI_EXPRESS)) अणु
		/* DMA पढ़ो watermark not used on PCIE */
		tp->dma_rwctrl |= 0x00180000;
	पूर्ण अन्यथा अगर (!tg3_flag(tp, PCIX_MODE)) अणु
		अगर (tg3_asic_rev(tp) == ASIC_REV_5705 ||
		    tg3_asic_rev(tp) == ASIC_REV_5750)
			tp->dma_rwctrl |= 0x003f0000;
		अन्यथा
			tp->dma_rwctrl |= 0x003f000f;
	पूर्ण अन्यथा अणु
		अगर (tg3_asic_rev(tp) == ASIC_REV_5703 ||
		    tg3_asic_rev(tp) == ASIC_REV_5704) अणु
			u32 ccval = (tr32(TG3PCI_CLOCK_CTRL) & 0x1f);
			u32 पढ़ो_water = 0x7;

			/* If the 5704 is behind the EPB bridge, we can
			 * करो the less restrictive ONE_DMA workaround क्रम
			 * better perक्रमmance.
			 */
			अगर (tg3_flag(tp, 40BIT_DMA_BUG) &&
			    tg3_asic_rev(tp) == ASIC_REV_5704)
				tp->dma_rwctrl |= 0x8000;
			अन्यथा अगर (ccval == 0x6 || ccval == 0x7)
				tp->dma_rwctrl |= DMA_RWCTRL_ONE_DMA;

			अगर (tg3_asic_rev(tp) == ASIC_REV_5703)
				पढ़ो_water = 4;
			/* Set bit 23 to enable PCIX hw bug fix */
			tp->dma_rwctrl |=
				(पढ़ो_water << DMA_RWCTRL_READ_WATER_SHIFT) |
				(0x3 << DMA_RWCTRL_WRITE_WATER_SHIFT) |
				(1 << 23);
		पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5780) अणु
			/* 5780 always in PCIX mode */
			tp->dma_rwctrl |= 0x00144000;
		पूर्ण अन्यथा अगर (tg3_asic_rev(tp) == ASIC_REV_5714) अणु
			/* 5714 always in PCIX mode */
			tp->dma_rwctrl |= 0x00148000;
		पूर्ण अन्यथा अणु
			tp->dma_rwctrl |= 0x001b000f;
		पूर्ण
	पूर्ण
	अगर (tg3_flag(tp, ONE_DMA_AT_ONCE))
		tp->dma_rwctrl |= DMA_RWCTRL_ONE_DMA;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5703 ||
	    tg3_asic_rev(tp) == ASIC_REV_5704)
		tp->dma_rwctrl &= 0xfffffff0;

	अगर (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701) अणु
		/* Remove this अगर it causes problems क्रम some boards. */
		tp->dma_rwctrl |= DMA_RWCTRL_USE_MEM_READ_MULT;

		/* On 5700/5701 chips, we need to set this bit.
		 * Otherwise the chip will issue cacheline transactions
		 * to streamable DMA memory with not all the byte
		 * enables turned on.  This is an error on several
		 * RISC PCI controllers, in particular sparc64.
		 *
		 * On 5703/5704 chips, this bit has been reasचिन्हित
		 * a dअगरferent meaning.  In particular, it is used
		 * on those chips to enable a PCI-X workaround.
		 */
		tp->dma_rwctrl |= DMA_RWCTRL_ASSERT_ALL_BE;
	पूर्ण

	tw32(TG3PCI_DMA_RW_CTRL, tp->dma_rwctrl);


	अगर (tg3_asic_rev(tp) != ASIC_REV_5700 &&
	    tg3_asic_rev(tp) != ASIC_REV_5701)
		जाओ out;

	/* It is best to perक्रमm DMA test with maximum ग_लिखो burst size
	 * to expose the 5700/5701 ग_लिखो DMA bug.
	 */
	saved_dma_rwctrl = tp->dma_rwctrl;
	tp->dma_rwctrl &= ~DMA_RWCTRL_WRITE_BNDRY_MASK;
	tw32(TG3PCI_DMA_RW_CTRL, tp->dma_rwctrl);

	जबतक (1) अणु
		u32 *p = buf, i;

		क्रम (i = 0; i < TEST_BUFFER_SIZE / माप(u32); i++)
			p[i] = i;

		/* Send the buffer to the chip. */
		ret = tg3_करो_test_dma(tp, buf, buf_dma, TEST_BUFFER_SIZE, true);
		अगर (ret) अणु
			dev_err(&tp->pdev->dev,
				"%s: Buffer write failed. err = %d\n",
				__func__, ret);
			अवरोध;
		पूर्ण

		/* Now पढ़ो it back. */
		ret = tg3_करो_test_dma(tp, buf, buf_dma, TEST_BUFFER_SIZE, false);
		अगर (ret) अणु
			dev_err(&tp->pdev->dev, "%s: Buffer read failed. "
				"err = %d\n", __func__, ret);
			अवरोध;
		पूर्ण

		/* Verअगरy it. */
		क्रम (i = 0; i < TEST_BUFFER_SIZE / माप(u32); i++) अणु
			अगर (p[i] == i)
				जारी;

			अगर ((tp->dma_rwctrl & DMA_RWCTRL_WRITE_BNDRY_MASK) !=
			    DMA_RWCTRL_WRITE_BNDRY_16) अणु
				tp->dma_rwctrl &= ~DMA_RWCTRL_WRITE_BNDRY_MASK;
				tp->dma_rwctrl |= DMA_RWCTRL_WRITE_BNDRY_16;
				tw32(TG3PCI_DMA_RW_CTRL, tp->dma_rwctrl);
				अवरोध;
			पूर्ण अन्यथा अणु
				dev_err(&tp->pdev->dev,
					"%s: Buffer corrupted on read back! "
					"(%d != %d)\n", __func__, p[i], i);
				ret = -ENODEV;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (i == (TEST_BUFFER_SIZE / माप(u32))) अणु
			/* Success. */
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर ((tp->dma_rwctrl & DMA_RWCTRL_WRITE_BNDRY_MASK) !=
	    DMA_RWCTRL_WRITE_BNDRY_16) अणु
		/* DMA test passed without adjusting DMA boundary,
		 * now look क्रम chipsets that are known to expose the
		 * DMA bug without failing the test.
		 */
		अगर (pci_dev_present(tg3_dma_रुको_state_chipsets)) अणु
			tp->dma_rwctrl &= ~DMA_RWCTRL_WRITE_BNDRY_MASK;
			tp->dma_rwctrl |= DMA_RWCTRL_WRITE_BNDRY_16;
		पूर्ण अन्यथा अणु
			/* Safe to use the calculated DMA boundary. */
			tp->dma_rwctrl = saved_dma_rwctrl;
		पूर्ण

		tw32(TG3PCI_DMA_RW_CTRL, tp->dma_rwctrl);
	पूर्ण

out:
	dma_मुक्त_coherent(&tp->pdev->dev, TEST_BUFFER_SIZE, buf, buf_dma);
out_noमुक्त:
	वापस ret;
पूर्ण

अटल व्योम tg3_init_bufmgr_config(काष्ठा tg3 *tp)
अणु
	अगर (tg3_flag(tp, 57765_PLUS)) अणु
		tp->bufmgr_config.mbuf_पढ़ो_dma_low_water =
			DEFAULT_MB_RDMA_LOW_WATER_5705;
		tp->bufmgr_config.mbuf_mac_rx_low_water =
			DEFAULT_MB_MACRX_LOW_WATER_57765;
		tp->bufmgr_config.mbuf_high_water =
			DEFAULT_MB_HIGH_WATER_57765;

		tp->bufmgr_config.mbuf_पढ़ो_dma_low_water_jumbo =
			DEFAULT_MB_RDMA_LOW_WATER_5705;
		tp->bufmgr_config.mbuf_mac_rx_low_water_jumbo =
			DEFAULT_MB_MACRX_LOW_WATER_JUMBO_57765;
		tp->bufmgr_config.mbuf_high_water_jumbo =
			DEFAULT_MB_HIGH_WATER_JUMBO_57765;
	पूर्ण अन्यथा अगर (tg3_flag(tp, 5705_PLUS)) अणु
		tp->bufmgr_config.mbuf_पढ़ो_dma_low_water =
			DEFAULT_MB_RDMA_LOW_WATER_5705;
		tp->bufmgr_config.mbuf_mac_rx_low_water =
			DEFAULT_MB_MACRX_LOW_WATER_5705;
		tp->bufmgr_config.mbuf_high_water =
			DEFAULT_MB_HIGH_WATER_5705;
		अगर (tg3_asic_rev(tp) == ASIC_REV_5906) अणु
			tp->bufmgr_config.mbuf_mac_rx_low_water =
				DEFAULT_MB_MACRX_LOW_WATER_5906;
			tp->bufmgr_config.mbuf_high_water =
				DEFAULT_MB_HIGH_WATER_5906;
		पूर्ण

		tp->bufmgr_config.mbuf_पढ़ो_dma_low_water_jumbo =
			DEFAULT_MB_RDMA_LOW_WATER_JUMBO_5780;
		tp->bufmgr_config.mbuf_mac_rx_low_water_jumbo =
			DEFAULT_MB_MACRX_LOW_WATER_JUMBO_5780;
		tp->bufmgr_config.mbuf_high_water_jumbo =
			DEFAULT_MB_HIGH_WATER_JUMBO_5780;
	पूर्ण अन्यथा अणु
		tp->bufmgr_config.mbuf_पढ़ो_dma_low_water =
			DEFAULT_MB_RDMA_LOW_WATER;
		tp->bufmgr_config.mbuf_mac_rx_low_water =
			DEFAULT_MB_MACRX_LOW_WATER;
		tp->bufmgr_config.mbuf_high_water =
			DEFAULT_MB_HIGH_WATER;

		tp->bufmgr_config.mbuf_पढ़ो_dma_low_water_jumbo =
			DEFAULT_MB_RDMA_LOW_WATER_JUMBO;
		tp->bufmgr_config.mbuf_mac_rx_low_water_jumbo =
			DEFAULT_MB_MACRX_LOW_WATER_JUMBO;
		tp->bufmgr_config.mbuf_high_water_jumbo =
			DEFAULT_MB_HIGH_WATER_JUMBO;
	पूर्ण

	tp->bufmgr_config.dma_low_water = DEFAULT_DMA_LOW_WATER;
	tp->bufmgr_config.dma_high_water = DEFAULT_DMA_HIGH_WATER;
पूर्ण

अटल अक्षर *tg3_phy_string(काष्ठा tg3 *tp)
अणु
	चयन (tp->phy_id & TG3_PHY_ID_MASK) अणु
	हाल TG3_PHY_ID_BCM5400:	वापस "5400";
	हाल TG3_PHY_ID_BCM5401:	वापस "5401";
	हाल TG3_PHY_ID_BCM5411:	वापस "5411";
	हाल TG3_PHY_ID_BCM5701:	वापस "5701";
	हाल TG3_PHY_ID_BCM5703:	वापस "5703";
	हाल TG3_PHY_ID_BCM5704:	वापस "5704";
	हाल TG3_PHY_ID_BCM5705:	वापस "5705";
	हाल TG3_PHY_ID_BCM5750:	वापस "5750";
	हाल TG3_PHY_ID_BCM5752:	वापस "5752";
	हाल TG3_PHY_ID_BCM5714:	वापस "5714";
	हाल TG3_PHY_ID_BCM5780:	वापस "5780";
	हाल TG3_PHY_ID_BCM5755:	वापस "5755";
	हाल TG3_PHY_ID_BCM5787:	वापस "5787";
	हाल TG3_PHY_ID_BCM5784:	वापस "5784";
	हाल TG3_PHY_ID_BCM5756:	वापस "5722/5756";
	हाल TG3_PHY_ID_BCM5906:	वापस "5906";
	हाल TG3_PHY_ID_BCM5761:	वापस "5761";
	हाल TG3_PHY_ID_BCM5718C:	वापस "5718C";
	हाल TG3_PHY_ID_BCM5718S:	वापस "5718S";
	हाल TG3_PHY_ID_BCM57765:	वापस "57765";
	हाल TG3_PHY_ID_BCM5719C:	वापस "5719C";
	हाल TG3_PHY_ID_BCM5720C:	वापस "5720C";
	हाल TG3_PHY_ID_BCM5762:	वापस "5762C";
	हाल TG3_PHY_ID_BCM8002:	वापस "8002/serdes";
	हाल 0:			वापस "serdes";
	शेष:		वापस "unknown";
	पूर्ण
पूर्ण

अटल अक्षर *tg3_bus_string(काष्ठा tg3 *tp, अक्षर *str)
अणु
	अगर (tg3_flag(tp, PCI_EXPRESS)) अणु
		म_नकल(str, "PCI Express");
		वापस str;
	पूर्ण अन्यथा अगर (tg3_flag(tp, PCIX_MODE)) अणु
		u32 घड़ी_ctrl = tr32(TG3PCI_CLOCK_CTRL) & 0x1f;

		म_नकल(str, "PCIX:");

		अगर ((घड़ी_ctrl == 7) ||
		    ((tr32(GRC_MISC_CFG) & GRC_MISC_CFG_BOARD_ID_MASK) ==
		     GRC_MISC_CFG_BOARD_ID_5704CIOBE))
			म_जोड़ो(str, "133MHz");
		अन्यथा अगर (घड़ी_ctrl == 0)
			म_जोड़ो(str, "33MHz");
		अन्यथा अगर (घड़ी_ctrl == 2)
			म_जोड़ो(str, "50MHz");
		अन्यथा अगर (घड़ी_ctrl == 4)
			म_जोड़ो(str, "66MHz");
		अन्यथा अगर (घड़ी_ctrl == 6)
			म_जोड़ो(str, "100MHz");
	पूर्ण अन्यथा अणु
		म_नकल(str, "PCI:");
		अगर (tg3_flag(tp, PCI_HIGH_SPEED))
			म_जोड़ो(str, "66MHz");
		अन्यथा
			म_जोड़ो(str, "33MHz");
	पूर्ण
	अगर (tg3_flag(tp, PCI_32BIT))
		म_जोड़ो(str, ":32-bit");
	अन्यथा
		म_जोड़ो(str, ":64-bit");
	वापस str;
पूर्ण

अटल व्योम tg3_init_coal(काष्ठा tg3 *tp)
अणु
	काष्ठा ethtool_coalesce *ec = &tp->coal;

	स_रखो(ec, 0, माप(*ec));
	ec->cmd = ETHTOOL_GCOALESCE;
	ec->rx_coalesce_usecs = LOW_RXCOL_TICKS;
	ec->tx_coalesce_usecs = LOW_TXCOL_TICKS;
	ec->rx_max_coalesced_frames = LOW_RXMAX_FRAMES;
	ec->tx_max_coalesced_frames = LOW_TXMAX_FRAMES;
	ec->rx_coalesce_usecs_irq = DEFAULT_RXCOAL_TICK_INT;
	ec->tx_coalesce_usecs_irq = DEFAULT_TXCOAL_TICK_INT;
	ec->rx_max_coalesced_frames_irq = DEFAULT_RXCOAL_MAXF_INT;
	ec->tx_max_coalesced_frames_irq = DEFAULT_TXCOAL_MAXF_INT;
	ec->stats_block_coalesce_usecs = DEFAULT_STAT_COAL_TICKS;

	अगर (tp->coalesce_mode & (HOSTCC_MODE_CLRTICK_RXBD |
				 HOSTCC_MODE_CLRTICK_TXBD)) अणु
		ec->rx_coalesce_usecs = LOW_RXCOL_TICKS_CLRTCKS;
		ec->rx_coalesce_usecs_irq = DEFAULT_RXCOAL_TICK_INT_CLRTCKS;
		ec->tx_coalesce_usecs = LOW_TXCOL_TICKS_CLRTCKS;
		ec->tx_coalesce_usecs_irq = DEFAULT_TXCOAL_TICK_INT_CLRTCKS;
	पूर्ण

	अगर (tg3_flag(tp, 5705_PLUS)) अणु
		ec->rx_coalesce_usecs_irq = 0;
		ec->tx_coalesce_usecs_irq = 0;
		ec->stats_block_coalesce_usecs = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tg3_init_one(काष्ठा pci_dev *pdev,
				  स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा tg3 *tp;
	पूर्णांक i, err;
	u32 sndmbx, rcvmbx, पूर्णांकmbx;
	अक्षर str[40];
	u64 dma_mask, persist_dma_mask;
	netdev_features_t features = 0;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, DRV_MODULE_NAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		जाओ err_out_disable_pdev;
	पूर्ण

	pci_set_master(pdev);

	dev = alloc_etherdev_mq(माप(*tp), TG3_IRQ_MAX_VECS);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_res;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);

	tp = netdev_priv(dev);
	tp->pdev = pdev;
	tp->dev = dev;
	tp->rx_mode = TG3_DEF_RX_MODE;
	tp->tx_mode = TG3_DEF_TX_MODE;
	tp->irq_sync = 1;
	tp->pcierr_recovery = false;

	अगर (tg3_debug > 0)
		tp->msg_enable = tg3_debug;
	अन्यथा
		tp->msg_enable = TG3_DEF_MSG_ENABLE;

	अगर (pdev_is_ssb_gige_core(pdev)) अणु
		tg3_flag_set(tp, IS_SSB_CORE);
		अगर (ssb_gige_must_flush_posted_ग_लिखोs(pdev))
			tg3_flag_set(tp, FLUSH_POSTED_WRITES);
		अगर (ssb_gige_one_dma_at_once(pdev))
			tg3_flag_set(tp, ONE_DMA_AT_ONCE);
		अगर (ssb_gige_have_roboचयन(pdev)) अणु
			tg3_flag_set(tp, USE_PHYLIB);
			tg3_flag_set(tp, ROBOSWITCH);
		पूर्ण
		अगर (ssb_gige_is_rgmii(pdev))
			tg3_flag_set(tp, RGMII_MODE);
	पूर्ण

	/* The word/byte swap controls here control रेजिस्टर access byte
	 * swapping.  DMA data byte swapping is controlled in the GRC_MODE
	 * setting below.
	 */
	tp->misc_host_ctrl =
		MISC_HOST_CTRL_MASK_PCI_INT |
		MISC_HOST_CTRL_WORD_SWAP |
		MISC_HOST_CTRL_INसूची_ACCESS |
		MISC_HOST_CTRL_PCISTATE_RW;

	/* The NONFRM (non-frame) byte/word swap controls take effect
	 * on descriptor entries, anything which isn't packet data.
	 *
	 * The StrongARM chips on the board (one क्रम tx, one क्रम rx)
	 * are running in big-endian mode.
	 */
	tp->grc_mode = (GRC_MODE_WSWAP_DATA | GRC_MODE_BSWAP_DATA |
			GRC_MODE_WSWAP_NONFRM_DATA);
#अगर_घोषित __BIG_ENDIAN
	tp->grc_mode |= GRC_MODE_BSWAP_NONFRM_DATA;
#पूर्ण_अगर
	spin_lock_init(&tp->lock);
	spin_lock_init(&tp->indirect_lock);
	INIT_WORK(&tp->reset_task, tg3_reset_task);

	tp->regs = pci_ioremap_bar(pdev, BAR_0);
	अगर (!tp->regs) अणु
		dev_err(&pdev->dev, "Cannot map device registers, aborting\n");
		err = -ENOMEM;
		जाओ err_out_मुक्त_dev;
	पूर्ण

	अगर (tp->pdev->device == PCI_DEVICE_ID_TIGON3_5761 ||
	    tp->pdev->device == PCI_DEVICE_ID_TIGON3_5761E ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5761S ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5761SE ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5717 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5717_C ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5718 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5719 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5720 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_57767 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_57764 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5762 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5725 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_5727 ||
	    tp->pdev->device == TG3PCI_DEVICE_TIGON3_57787) अणु
		tg3_flag_set(tp, ENABLE_APE);
		tp->aperegs = pci_ioremap_bar(pdev, BAR_2);
		अगर (!tp->aperegs) अणु
			dev_err(&pdev->dev,
				"Cannot map APE registers, aborting\n");
			err = -ENOMEM;
			जाओ err_out_iounmap;
		पूर्ण
	पूर्ण

	tp->rx_pending = TG3_DEF_RX_RING_PENDING;
	tp->rx_jumbo_pending = TG3_DEF_RX_JUMBO_RING_PENDING;

	dev->ethtool_ops = &tg3_ethtool_ops;
	dev->watchकरोg_समयo = TG3_TX_TIMEOUT;
	dev->netdev_ops = &tg3_netdev_ops;
	dev->irq = pdev->irq;

	err = tg3_get_invariants(tp, ent);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Problem fetching invariants of chip, aborting\n");
		जाओ err_out_apeunmap;
	पूर्ण

	/* The EPB bridge inside 5714, 5715, and 5780 and any
	 * device behind the EPB cannot support DMA addresses > 40-bit.
	 * On 64-bit प्रणालीs with IOMMU, use 40-bit dma_mask.
	 * On 64-bit प्रणालीs without IOMMU, use 64-bit dma_mask and
	 * करो DMA address check in tg3_start_xmit().
	 */
	अगर (tg3_flag(tp, IS_5788))
		persist_dma_mask = dma_mask = DMA_BIT_MASK(32);
	अन्यथा अगर (tg3_flag(tp, 40BIT_DMA_BUG)) अणु
		persist_dma_mask = dma_mask = DMA_BIT_MASK(40);
#अगर_घोषित CONFIG_HIGHMEM
		dma_mask = DMA_BIT_MASK(64);
#पूर्ण_अगर
	पूर्ण अन्यथा
		persist_dma_mask = dma_mask = DMA_BIT_MASK(64);

	/* Configure DMA attributes. */
	अगर (dma_mask > DMA_BIT_MASK(32)) अणु
		err = pci_set_dma_mask(pdev, dma_mask);
		अगर (!err) अणु
			features |= NETIF_F_HIGHDMA;
			err = pci_set_consistent_dma_mask(pdev,
							  persist_dma_mask);
			अगर (err < 0) अणु
				dev_err(&pdev->dev, "Unable to obtain 64 bit "
					"DMA for consistent allocations\n");
				जाओ err_out_apeunmap;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (err || dma_mask == DMA_BIT_MASK(32)) अणु
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"No usable DMA configuration, aborting\n");
			जाओ err_out_apeunmap;
		पूर्ण
	पूर्ण

	tg3_init_bufmgr_config(tp);

	/* 5700 B0 chips करो not support checksumming correctly due
	 * to hardware bugs.
	 */
	अगर (tg3_chip_rev_id(tp) != CHIPREV_ID_5700_B0) अणु
		features |= NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_RXCSUM;

		अगर (tg3_flag(tp, 5755_PLUS))
			features |= NETIF_F_IPV6_CSUM;
	पूर्ण

	/* TSO is on by शेष on chips that support hardware TSO.
	 * Firmware TSO on older chips gives lower perक्रमmance, so it
	 * is off by शेष, but can be enabled using ethtool.
	 */
	अगर ((tg3_flag(tp, HW_TSO_1) ||
	     tg3_flag(tp, HW_TSO_2) ||
	     tg3_flag(tp, HW_TSO_3)) &&
	    (features & NETIF_F_IP_CSUM))
		features |= NETIF_F_TSO;
	अगर (tg3_flag(tp, HW_TSO_2) || tg3_flag(tp, HW_TSO_3)) अणु
		अगर (features & NETIF_F_IPV6_CSUM)
			features |= NETIF_F_TSO6;
		अगर (tg3_flag(tp, HW_TSO_3) ||
		    tg3_asic_rev(tp) == ASIC_REV_5761 ||
		    (tg3_asic_rev(tp) == ASIC_REV_5784 &&
		     tg3_chip_rev(tp) != CHIPREV_5784_AX) ||
		    tg3_asic_rev(tp) == ASIC_REV_5785 ||
		    tg3_asic_rev(tp) == ASIC_REV_57780)
			features |= NETIF_F_TSO_ECN;
	पूर्ण

	dev->features |= features | NETIF_F_HW_VLAN_CTAG_TX |
			 NETIF_F_HW_VLAN_CTAG_RX;
	dev->vlan_features |= features;

	/*
	 * Add loopback capability only क्रम a subset of devices that support
	 * MAC-LOOPBACK. Eventually this need to be enhanced to allow INT-PHY
	 * loopback क्रम the reमुख्यing devices.
	 */
	अगर (tg3_asic_rev(tp) != ASIC_REV_5780 &&
	    !tg3_flag(tp, CPMU_PRESENT))
		/* Add the loopback capability */
		features |= NETIF_F_LOOPBACK;

	dev->hw_features |= features;
	dev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 60 - 9000 or 1500, depending on hardware */
	dev->min_mtu = TG3_MIN_MTU;
	dev->max_mtu = TG3_MAX_MTU(tp);

	अगर (tg3_chip_rev_id(tp) == CHIPREV_ID_5705_A1 &&
	    !tg3_flag(tp, TSO_CAPABLE) &&
	    !(tr32(TG3PCI_PCISTATE) & PCISTATE_BUS_SPEED_HIGH)) अणु
		tg3_flag_set(tp, MAX_RXPEND_64);
		tp->rx_pending = 63;
	पूर्ण

	err = tg3_get_device_address(tp);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Could not obtain valid ethernet address, aborting\n");
		जाओ err_out_apeunmap;
	पूर्ण

	पूर्णांकmbx = MAILBOX_INTERRUPT_0 + TG3_64BIT_REG_LOW;
	rcvmbx = MAILBOX_RCVRET_CON_IDX_0 + TG3_64BIT_REG_LOW;
	sndmbx = MAILBOX_SNDHOST_PROD_IDX_0 + TG3_64BIT_REG_LOW;
	क्रम (i = 0; i < tp->irq_max; i++) अणु
		काष्ठा tg3_napi *tnapi = &tp->napi[i];

		tnapi->tp = tp;
		tnapi->tx_pending = TG3_DEF_TX_RING_PENDING;

		tnapi->पूर्णांक_mbox = पूर्णांकmbx;
		अगर (i <= 4)
			पूर्णांकmbx += 0x8;
		अन्यथा
			पूर्णांकmbx += 0x4;

		tnapi->consmbox = rcvmbx;
		tnapi->prodmbox = sndmbx;

		अगर (i)
			tnapi->coal_now = HOSTCC_MODE_COAL_VEC1_NOW << (i - 1);
		अन्यथा
			tnapi->coal_now = HOSTCC_MODE_NOW;

		अगर (!tg3_flag(tp, SUPPORT_MSIX))
			अवरोध;

		/*
		 * If we support MSIX, we'll be using RSS.  If we're using
		 * RSS, the first vector only handles link पूर्णांकerrupts and the
		 * reमुख्यing vectors handle rx and tx पूर्णांकerrupts.  Reuse the
		 * mailbox values क्रम the next iteration.  The values we setup
		 * above are still useful क्रम the single vectored mode.
		 */
		अगर (!i)
			जारी;

		rcvmbx += 0x8;

		अगर (sndmbx & 0x4)
			sndmbx -= 0x4;
		अन्यथा
			sndmbx += 0xc;
	पूर्ण

	/*
	 * Reset chip in हाल UNDI or EFI driver did not shutकरोwn
	 * DMA self test will enable WDMAC and we'll see (spurious)
	 * pending DMA on the PCI bus at that poपूर्णांक.
	 */
	अगर ((tr32(HOSTCC_MODE) & HOSTCC_MODE_ENABLE) ||
	    (tr32(WDMAC_MODE) & WDMAC_MODE_ENABLE)) अणु
		tg3_full_lock(tp, 0);
		tw32(MEMARB_MODE, MEMARB_MODE_ENABLE);
		tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
		tg3_full_unlock(tp);
	पूर्ण

	err = tg3_test_dma(tp);
	अगर (err) अणु
		dev_err(&pdev->dev, "DMA engine test failed, aborting\n");
		जाओ err_out_apeunmap;
	पूर्ण

	tg3_init_coal(tp);

	pci_set_drvdata(pdev, dev);

	अगर (tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720 ||
	    tg3_asic_rev(tp) == ASIC_REV_5762)
		tg3_flag_set(tp, PTP_CAPABLE);

	tg3_समयr_init(tp);

	tg3_carrier_off(tp);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot register net device, aborting\n");
		जाओ err_out_apeunmap;
	पूर्ण

	अगर (tg3_flag(tp, PTP_CAPABLE)) अणु
		tg3_ptp_init(tp);
		tp->ptp_घड़ी = ptp_घड़ी_रेजिस्टर(&tp->ptp_info,
						   &tp->pdev->dev);
		अगर (IS_ERR(tp->ptp_घड़ी))
			tp->ptp_घड़ी = शून्य;
	पूर्ण

	netdev_info(dev, "Tigon3 [partno(%s) rev %04x] (%s) MAC address %pM\n",
		    tp->board_part_number,
		    tg3_chip_rev_id(tp),
		    tg3_bus_string(tp, str),
		    dev->dev_addr);

	अगर (!(tp->phy_flags & TG3_PHYFLG_IS_CONNECTED)) अणु
		अक्षर *ethtype;

		अगर (tp->phy_flags & TG3_PHYFLG_10_100_ONLY)
			ethtype = "10/100Base-TX";
		अन्यथा अगर (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
			ethtype = "1000Base-SX";
		अन्यथा
			ethtype = "10/100/1000Base-T";

		netdev_info(dev, "attached PHY is %s (%s Ethernet) "
			    "(WireSpeed[%d], EEE[%d])\n",
			    tg3_phy_string(tp), ethtype,
			    (tp->phy_flags & TG3_PHYFLG_NO_ETH_WIRE_SPEED) == 0,
			    (tp->phy_flags & TG3_PHYFLG_EEE_CAP) != 0);
	पूर्ण

	netdev_info(dev, "RXcsums[%d] LinkChgREG[%d] MIirq[%d] ASF[%d] TSOcap[%d]\n",
		    (dev->features & NETIF_F_RXCSUM) != 0,
		    tg3_flag(tp, USE_LINKCHG_REG) != 0,
		    (tp->phy_flags & TG3_PHYFLG_USE_MI_INTERRUPT) != 0,
		    tg3_flag(tp, ENABLE_ASF) != 0,
		    tg3_flag(tp, TSO_CAPABLE) != 0);
	netdev_info(dev, "dma_rwctrl[%08x] dma_mask[%d-bit]\n",
		    tp->dma_rwctrl,
		    pdev->dma_mask == DMA_BIT_MASK(32) ? 32 :
		    ((u64)pdev->dma_mask) == DMA_BIT_MASK(40) ? 40 : 64);

	pci_save_state(pdev);

	वापस 0;

err_out_apeunmap:
	अगर (tp->aperegs) अणु
		iounmap(tp->aperegs);
		tp->aperegs = शून्य;
	पूर्ण

err_out_iounmap:
	अगर (tp->regs) अणु
		iounmap(tp->regs);
		tp->regs = शून्य;
	पूर्ण

err_out_मुक्त_dev:
	मुक्त_netdev(dev);

err_out_मुक्त_res:
	pci_release_regions(pdev);

err_out_disable_pdev:
	अगर (pci_is_enabled(pdev))
		pci_disable_device(pdev);
	वापस err;
पूर्ण

अटल व्योम tg3_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		काष्ठा tg3 *tp = netdev_priv(dev);

		tg3_ptp_fini(tp);

		release_firmware(tp->fw);

		tg3_reset_task_cancel(tp);

		अगर (tg3_flag(tp, USE_PHYLIB)) अणु
			tg3_phy_fini(tp);
			tg3_mdio_fini(tp);
		पूर्ण

		unरेजिस्टर_netdev(dev);
		अगर (tp->aperegs) अणु
			iounmap(tp->aperegs);
			tp->aperegs = शून्य;
		पूर्ण
		अगर (tp->regs) अणु
			iounmap(tp->regs);
			tp->regs = शून्य;
		पूर्ण
		मुक्त_netdev(dev);
		pci_release_regions(pdev);
		pci_disable_device(pdev);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tg3_suspend(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक err = 0;

	rtnl_lock();

	अगर (!netअगर_running(dev))
		जाओ unlock;

	tg3_reset_task_cancel(tp);
	tg3_phy_stop(tp);
	tg3_netअगर_stop(tp);

	tg3_समयr_stop(tp);

	tg3_full_lock(tp, 1);
	tg3_disable_पूर्णांकs(tp);
	tg3_full_unlock(tp);

	netअगर_device_detach(dev);

	tg3_full_lock(tp, 0);
	tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
	tg3_flag_clear(tp, INIT_COMPLETE);
	tg3_full_unlock(tp);

	err = tg3_घातer_करोwn_prepare(tp);
	अगर (err) अणु
		पूर्णांक err2;

		tg3_full_lock(tp, 0);

		tg3_flag_set(tp, INIT_COMPLETE);
		err2 = tg3_restart_hw(tp, true);
		अगर (err2)
			जाओ out;

		tg3_समयr_start(tp);

		netअगर_device_attach(dev);
		tg3_netअगर_start(tp);

out:
		tg3_full_unlock(tp);

		अगर (!err2)
			tg3_phy_start(tp);
	पूर्ण

unlock:
	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक tg3_resume(काष्ठा device *device)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(device);
	काष्ठा tg3 *tp = netdev_priv(dev);
	पूर्णांक err = 0;

	rtnl_lock();

	अगर (!netअगर_running(dev))
		जाओ unlock;

	netअगर_device_attach(dev);

	tg3_full_lock(tp, 0);

	tg3_ape_driver_state_change(tp, RESET_KIND_INIT);

	tg3_flag_set(tp, INIT_COMPLETE);
	err = tg3_restart_hw(tp,
			     !(tp->phy_flags & TG3_PHYFLG_KEEP_LINK_ON_PWRDN));
	अगर (err)
		जाओ out;

	tg3_समयr_start(tp);

	tg3_netअगर_start(tp);

out:
	tg3_full_unlock(tp);

	अगर (!err)
		tg3_phy_start(tp);

unlock:
	rtnl_unlock();
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(tg3_pm_ops, tg3_suspend, tg3_resume);

अटल व्योम tg3_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा tg3 *tp = netdev_priv(dev);

	rtnl_lock();
	netअगर_device_detach(dev);

	अगर (netअगर_running(dev))
		dev_बंद(dev);

	अगर (प्रणाली_state == SYSTEM_POWER_OFF)
		tg3_घातer_करोwn(tp);

	rtnl_unlock();
पूर्ण

/**
 * tg3_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t tg3_io_error_detected(काष्ठा pci_dev *pdev,
					      pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा tg3 *tp = netdev_priv(netdev);
	pci_ers_result_t err = PCI_ERS_RESULT_NEED_RESET;

	netdev_info(netdev, "PCI I/O error detected\n");

	rtnl_lock();

	/* Could be second call or maybe we करोn't have netdev yet */
	अगर (!netdev || tp->pcierr_recovery || !netअगर_running(netdev))
		जाओ करोne;

	/* We needn't recover from permanent error */
	अगर (state == pci_channel_io_frozen)
		tp->pcierr_recovery = true;

	tg3_phy_stop(tp);

	tg3_netअगर_stop(tp);

	tg3_समयr_stop(tp);

	/* Want to make sure that the reset task करोesn't run */
	tg3_reset_task_cancel(tp);

	netअगर_device_detach(netdev);

	/* Clean up software state, even अगर MMIO is blocked */
	tg3_full_lock(tp, 0);
	tg3_halt(tp, RESET_KIND_SHUTDOWN, 0);
	tg3_full_unlock(tp);

करोne:
	अगर (state == pci_channel_io_perm_failure) अणु
		अगर (netdev) अणु
			tg3_napi_enable(tp);
			dev_बंद(netdev);
		पूर्ण
		err = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pci_disable_device(pdev);
	पूर्ण

	rtnl_unlock();

	वापस err;
पूर्ण

/**
 * tg3_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot.
 * At this poपूर्णांक, the card has exprienced a hard reset,
 * followed by fixups by BIOS, and has its config space
 * set up identically to what it was at cold boot.
 */
अटल pci_ers_result_t tg3_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा tg3 *tp = netdev_priv(netdev);
	pci_ers_result_t rc = PCI_ERS_RESULT_DISCONNECT;
	पूर्णांक err;

	rtnl_lock();

	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		जाओ करोne;
	पूर्ण

	pci_set_master(pdev);
	pci_restore_state(pdev);
	pci_save_state(pdev);

	अगर (!netdev || !netअगर_running(netdev)) अणु
		rc = PCI_ERS_RESULT_RECOVERED;
		जाओ करोne;
	पूर्ण

	err = tg3_घातer_up(tp);
	अगर (err)
		जाओ करोne;

	rc = PCI_ERS_RESULT_RECOVERED;

करोne:
	अगर (rc != PCI_ERS_RESULT_RECOVERED && netdev && netअगर_running(netdev)) अणु
		tg3_napi_enable(tp);
		dev_बंद(netdev);
	पूर्ण
	rtnl_unlock();

	वापस rc;
पूर्ण

/**
 * tg3_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells
 * us that its OK to resume normal operation.
 */
अटल व्योम tg3_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा tg3 *tp = netdev_priv(netdev);
	पूर्णांक err;

	rtnl_lock();

	अगर (!netdev || !netअगर_running(netdev))
		जाओ करोne;

	tg3_full_lock(tp, 0);
	tg3_ape_driver_state_change(tp, RESET_KIND_INIT);
	tg3_flag_set(tp, INIT_COMPLETE);
	err = tg3_restart_hw(tp, true);
	अगर (err) अणु
		tg3_full_unlock(tp);
		netdev_err(netdev, "Cannot restart hardware after reset.\n");
		जाओ करोne;
	पूर्ण

	netअगर_device_attach(netdev);

	tg3_समयr_start(tp);

	tg3_netअगर_start(tp);

	tg3_full_unlock(tp);

	tg3_phy_start(tp);

करोne:
	tp->pcierr_recovery = false;
	rtnl_unlock();
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers tg3_err_handler = अणु
	.error_detected	= tg3_io_error_detected,
	.slot_reset	= tg3_io_slot_reset,
	.resume		= tg3_io_resume
पूर्ण;

अटल काष्ठा pci_driver tg3_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= tg3_pci_tbl,
	.probe		= tg3_init_one,
	.हटाओ		= tg3_हटाओ_one,
	.err_handler	= &tg3_err_handler,
	.driver.pm	= &tg3_pm_ops,
	.shutकरोwn	= tg3_shutकरोwn,
पूर्ण;

module_pci_driver(tg3_driver);
