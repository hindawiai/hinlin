<शैली गुरु>
/* typhoon.c: A Linux Ethernet device driver क्रम 3Com 3CR990 family of NICs */
/*
	Written 2002-2004 by David Dillow <dave@thedillows.org>
	Based on code written 1998-2000 by Donald Becker <becker@scyld.com> and
	Linux 2.2.x driver by David P. McLean <davidpmclean@yahoo.com>.

	This software may be used and distributed according to the terms of
	the GNU General Public License (GPL), incorporated herein by reference.
	Drivers based on or derived from this code fall under the GPL and must
	retain the authorship, copyright and license notice.  This file is not
	a complete program and may only be used when the entire operating
	प्रणाली is licensed under the GPL.

	This software is available on a खुला web site. It may enable
	cryptographic capabilities of the 3Com hardware, and may be
	exported from the United States under License Exception "TSU"
	pursuant to 15 C.F.R. Section 740.13(e).

	This work was funded by the National Library of Medicine under
	the Deparपंचांगent of Energy project number 0274DD06D1 and NLM project
	number Y1-LM-2015-01.

	This driver is deचिन्हित क्रम the 3Com 3CR990 Family of cards with the
	3XP Processor. It has been tested on x86 and sparc64.

	KNOWN ISSUES:
	*) Cannot DMA Rx packets to a 2 byte aligned address. Also firmware
		issue. Hopefully 3Com will fix it.
	*) Waiting क्रम a command response takes 8ms due to non-preemptable
		polling. Only signअगरicant क्रम getting stats and creating
		SAs, but an ugly wart never the less.

	TODO:
	*) Doesn't do IPSEC offloading. Yet. Keep yer pants on, it's coming.
	*) Add more support क्रम ethtool (especially क्रम NIC stats)
	*) Allow disabling of RX checksum offloading
	*) Fix MAC changing to work जबतक the पूर्णांकerface is up
		(Need to put commands on the TX ring, which changes
		the locking)
	*) Add in FCS to अणुrx,txपूर्ण_bytes, since the hardware करोesn't. See
		http://oss.sgi.com/cgi-bin/mesg.cgi?a=netdev&i=20031215152211.7003fe8e.rddunlap%40osdl.org
*/

/* Set the copy अवरोधpoपूर्णांक क्रम the copy-only-tiny-frames scheme.
 * Setting to > 1518 effectively disables this feature.
 */
अटल पूर्णांक rx_copyअवरोध = 200;

/* Should we use MMIO or Port IO?
 * 0: Port IO
 * 1: MMIO
 * 2: Try MMIO, fallback to Port IO
 */
अटल अचिन्हित पूर्णांक use_mmio = 2;

/* end user-configurable values */

/* Maximum number of multicast addresses to filter (vs. rx-all-multicast).
 */
अटल स्थिर पूर्णांक multicast_filter_limit = 32;

/* Operational parameters that are set at compile समय. */

/* Keep the ring sizes a घातer of two क्रम compile efficiency.
 * The compiler will convert <अचिन्हित>'%'<2^N> पूर्णांकo a bit mask.
 * Making the Tx ring too large decreases the effectiveness of channel
 * bonding and packet priority.
 * There are no ill effects from too-large receive rings.
 *
 * We करोn't currently use the Hi Tx ring so, don't make it very big.
 *
 * Beware that अगर we start using the Hi Tx ring, we will need to change
 * typhoon_num_मुक्त_tx() and typhoon_tx_complete() to account क्रम that.
 */
#घोषणा TXHI_ENTRIES		2
#घोषणा TXLO_ENTRIES		128
#घोषणा RX_ENTRIES		32
#घोषणा COMMAND_ENTRIES		16
#घोषणा RESPONSE_ENTRIES	32

#घोषणा COMMAND_RING_SIZE	(COMMAND_ENTRIES * माप(काष्ठा cmd_desc))
#घोषणा RESPONSE_RING_SIZE	(RESPONSE_ENTRIES * माप(काष्ठा resp_desc))

/* The 3XP will preload and हटाओ 64 entries from the मुक्त buffer
 * list, and we need one entry to keep the ring from wrapping, so
 * to keep this a घातer of two, we use 128 entries.
 */
#घोषणा RXFREE_ENTRIES		128
#घोषणा RXENT_ENTRIES		(RXFREE_ENTRIES - 1)

/* Operational parameters that usually are not changed. */

/* Time in jअगरfies beक्रमe concluding the transmitter is hung. */
#घोषणा TX_TIMEOUT  (2*HZ)

#घोषणा PKT_BUF_SZ		1536
#घोषणा FIRMWARE_NAME		"3com/typhoon.bin"

#घोषणा pr_fmt(fmt)		KBUILD_MODNAME " " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crc32.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/in6.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>

#समावेश "typhoon.h"

MODULE_AUTHOR("David Dillow <dave@thedillows.org>");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(FIRMWARE_NAME);
MODULE_DESCRIPTION("3Com Typhoon Family (3C990, 3CR990, and variants)");
MODULE_PARM_DESC(rx_copyअवरोध, "Packets smaller than this are copied and "
			       "the buffer given back to the NIC. Default "
			       "is 200.");
MODULE_PARM_DESC(use_mmio, "Use MMIO (1) or PIO(0) to access the NIC. "
			   "Default is to try MMIO and fallback to PIO.");
module_param(rx_copyअवरोध, पूर्णांक, 0);
module_param(use_mmio, पूर्णांक, 0);

#अगर defined(NETIF_F_TSO) && MAX_SKB_FRAGS > 32
#warning Typhoon only supports 32 entries in its SG list क्रम TSO, disabling TSO
#अघोषित NETIF_F_TSO
#पूर्ण_अगर

#अगर TXLO_ENTRIES <= (2 * MAX_SKB_FRAGS)
#त्रुटि TX ring too small!
#पूर्ण_अगर

काष्ठा typhoon_card_info अणु
	स्थिर अक्षर *name;
	स्थिर पूर्णांक capabilities;
पूर्ण;

#घोषणा TYPHOON_CRYPTO_NONE		0x00
#घोषणा TYPHOON_CRYPTO_DES		0x01
#घोषणा TYPHOON_CRYPTO_3DES		0x02
#घोषणा	TYPHOON_CRYPTO_VARIABLE		0x04
#घोषणा TYPHOON_FIBER			0x08
#घोषणा TYPHOON_WAKEUP_NEEDS_RESET	0x10

क्रमागत typhoon_cards अणु
	TYPHOON_TX = 0, TYPHOON_TX95, TYPHOON_TX97, TYPHOON_SVR,
	TYPHOON_SVR95, TYPHOON_SVR97, TYPHOON_TXM, TYPHOON_BSVR,
	TYPHOON_FX95, TYPHOON_FX97, TYPHOON_FX95SVR, TYPHOON_FX97SVR,
	TYPHOON_FXM,
पूर्ण;

/* directly indexed by क्रमागत typhoon_cards, above */
अटल काष्ठा typhoon_card_info typhoon_card_info[] = अणु
	अणु "3Com Typhoon (3C990-TX)",
		TYPHOON_CRYPTO_NONEपूर्ण,
	अणु "3Com Typhoon (3CR990-TX-95)",
		TYPHOON_CRYPTO_DESपूर्ण,
	अणु "3Com Typhoon (3CR990-TX-97)",
	 	TYPHOON_CRYPTO_DES | TYPHOON_CRYPTO_3DESपूर्ण,
	अणु "3Com Typhoon (3C990SVR)",
		TYPHOON_CRYPTO_NONEपूर्ण,
	अणु "3Com Typhoon (3CR990SVR95)",
		TYPHOON_CRYPTO_DESपूर्ण,
	अणु "3Com Typhoon (3CR990SVR97)",
	 	TYPHOON_CRYPTO_DES | TYPHOON_CRYPTO_3DESपूर्ण,
	अणु "3Com Typhoon2 (3C990B-TX-M)",
		TYPHOON_CRYPTO_VARIABLEपूर्ण,
	अणु "3Com Typhoon2 (3C990BSVR)",
		TYPHOON_CRYPTO_VARIABLEपूर्ण,
	अणु "3Com Typhoon (3CR990-FX-95)",
		TYPHOON_CRYPTO_DES | TYPHOON_FIBERपूर्ण,
	अणु "3Com Typhoon (3CR990-FX-97)",
	 	TYPHOON_CRYPTO_DES | TYPHOON_CRYPTO_3DES | TYPHOON_FIBERपूर्ण,
	अणु "3Com Typhoon (3CR990-FX-95 Server)",
	 	TYPHOON_CRYPTO_DES | TYPHOON_FIBERपूर्ण,
	अणु "3Com Typhoon (3CR990-FX-97 Server)",
	 	TYPHOON_CRYPTO_DES | TYPHOON_CRYPTO_3DES | TYPHOON_FIBERपूर्ण,
	अणु "3Com Typhoon2 (3C990B-FX-97)",
		TYPHOON_CRYPTO_VARIABLE | TYPHOON_FIBERपूर्ण,
पूर्ण;

/* Notes on the new subप्रणाली numbering scheme:
 * bits 0-1 indicate crypto capabilities: (0) variable, (1) DES, or (2) 3DES
 * bit 4 indicates अगर this card has secured firmware (we करोn't support it)
 * bit 8 indicates अगर this is a (0) copper or (1) fiber card
 * bits 12-16 indicate card type: (0) client and (1) server
 */
अटल स्थिर काष्ठा pci_device_id typhoon_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0,TYPHOON_TX पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990_TX_95,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, TYPHOON_TX95 पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990_TX_97,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, TYPHOON_TX97 पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990B,
	  PCI_ANY_ID, 0x1000, 0, 0, TYPHOON_TXM पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990B,
	  PCI_ANY_ID, 0x1102, 0, 0, TYPHOON_FXM पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990B,
	  PCI_ANY_ID, 0x2000, 0, 0, TYPHOON_BSVR पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990_FX,
	  PCI_ANY_ID, 0x1101, 0, 0, TYPHOON_FX95 पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990_FX,
	  PCI_ANY_ID, 0x1102, 0, 0, TYPHOON_FX97 पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990_FX,
	  PCI_ANY_ID, 0x2101, 0, 0, TYPHOON_FX95SVR पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990_FX,
	  PCI_ANY_ID, 0x2102, 0, 0, TYPHOON_FX97SVR पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990SVR95,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, TYPHOON_SVR95 पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990SVR97,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, TYPHOON_SVR97 पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3CR990SVR,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, TYPHOON_SVR पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, typhoon_pci_tbl);

/* Define the shared memory area
 * Align everything the 3XP will normally be using.
 * We'll need to move/align txHi अगर we start using that ring.
 */
#घोषणा __3xp_aligned	____cacheline_aligned
काष्ठा typhoon_shared अणु
	काष्ठा typhoon_पूर्णांकerface	अगरace;
	काष्ठा typhoon_indexes		indexes			__3xp_aligned;
	काष्ठा tx_desc			txLo[TXLO_ENTRIES] 	__3xp_aligned;
	काष्ठा rx_desc			rxLo[RX_ENTRIES]	__3xp_aligned;
	काष्ठा rx_desc			rxHi[RX_ENTRIES]	__3xp_aligned;
	काष्ठा cmd_desc			cmd[COMMAND_ENTRIES]	__3xp_aligned;
	काष्ठा resp_desc		resp[RESPONSE_ENTRIES]	__3xp_aligned;
	काष्ठा rx_मुक्त			rxBuff[RXFREE_ENTRIES]	__3xp_aligned;
	u32				zeroWord;
	काष्ठा tx_desc			txHi[TXHI_ENTRIES];
पूर्ण __packed;

काष्ठा rxbuff_ent अणु
	काष्ठा sk_buff *skb;
	dma_addr_t	dma_addr;
पूर्ण;

काष्ठा typhoon अणु
	/* Tx cache line section */
	काष्ठा transmit_ring 	txLoRing	____cacheline_aligned;
	काष्ठा pci_dev *	tx_pdev;
	व्योम __iomem		*tx_ioaddr;
	u32			txlo_dma_addr;

	/* Irq/Rx cache line section */
	व्योम __iomem		*ioaddr		____cacheline_aligned;
	काष्ठा typhoon_indexes *indexes;
	u8			aरुकोing_resp;
	u8			duplex;
	u8			speed;
	u8			card_state;
	काष्ठा basic_ring	rxLoRing;
	काष्ठा pci_dev *	pdev;
	काष्ठा net_device *	dev;
	काष्ठा napi_काष्ठा	napi;
	काष्ठा basic_ring	rxHiRing;
	काष्ठा basic_ring	rxBuffRing;
	काष्ठा rxbuff_ent	rxbuffers[RXENT_ENTRIES];

	/* general section */
	spinlock_t		command_lock	____cacheline_aligned;
	काष्ठा basic_ring	cmdRing;
	काष्ठा basic_ring	respRing;
	काष्ठा net_device_stats	stats_saved;
	काष्ठा typhoon_shared *	shared;
	dma_addr_t		shared_dma;
	__le16			xcvr_select;
	__le16			wol_events;
	__le32			offload;

	/* unused stuff (future use) */
	पूर्णांक			capabilities;
	काष्ठा transmit_ring 	txHiRing;
पूर्ण;

क्रमागत completion_रुको_values अणु
	NoWait = 0, WaitNoSleep, WaitSleep,
पूर्ण;

/* These are the values क्रम the typhoon.card_state variable.
 * These determine where the statistics will come from in get_stats().
 * The sleep image करोes not support the statistics we need.
 */
क्रमागत state_values अणु
	Sleeping = 0, Running,
पूर्ण;

/* PCI ग_लिखोs are not guaranteed to be posted in order, but outstanding ग_लिखोs
 * cannot pass a पढ़ो, so this क्रमces current ग_लिखोs to post.
 */
#घोषणा typhoon_post_pci_ग_लिखोs(x) \
	करो अणु अगर (likely(use_mmio)) ioपढ़ो32(x+TYPHOON_REG_HEARTBEAT); पूर्ण जबतक (0)

/* We'll रुको up to six seconds क्रम a reset, and half a second normally.
 */
#घोषणा TYPHOON_UDELAY			50
#घोषणा TYPHOON_RESET_TIMEOUT_SLEEP	(6 * HZ)
#घोषणा TYPHOON_RESET_TIMEOUT_NOSLEEP	((6 * 1000000) / TYPHOON_UDELAY)
#घोषणा TYPHOON_WAIT_TIMEOUT		((1000000 / 2) / TYPHOON_UDELAY)

#अगर defined(NETIF_F_TSO)
#घोषणा skb_tso_size(x)		(skb_shinfo(x)->gso_size)
#घोषणा TSO_NUM_DESCRIPTORS	2
#घोषणा TSO_OFFLOAD_ON		TYPHOON_OFFLOAD_TCP_SEGMENT
#अन्यथा
#घोषणा NETIF_F_TSO 		0
#घोषणा skb_tso_size(x) 	0
#घोषणा TSO_NUM_DESCRIPTORS	0
#घोषणा TSO_OFFLOAD_ON		0
#पूर्ण_अगर

अटल अंतरभूत व्योम
typhoon_inc_index(u32 *index, स्थिर पूर्णांक count, स्थिर पूर्णांक num_entries)
अणु
	/* Increment a ring index -- we can use this क्रम all rings execept
	 * the Rx rings, as they use dअगरferent size descriptors
	 * otherwise, everything is the same size as a cmd_desc
	 */
	*index += count * माप(काष्ठा cmd_desc);
	*index %= num_entries * माप(काष्ठा cmd_desc);
पूर्ण

अटल अंतरभूत व्योम
typhoon_inc_cmd_index(u32 *index, स्थिर पूर्णांक count)
अणु
	typhoon_inc_index(index, count, COMMAND_ENTRIES);
पूर्ण

अटल अंतरभूत व्योम
typhoon_inc_resp_index(u32 *index, स्थिर पूर्णांक count)
अणु
	typhoon_inc_index(index, count, RESPONSE_ENTRIES);
पूर्ण

अटल अंतरभूत व्योम
typhoon_inc_rxमुक्त_index(u32 *index, स्थिर पूर्णांक count)
अणु
	typhoon_inc_index(index, count, RXFREE_ENTRIES);
पूर्ण

अटल अंतरभूत व्योम
typhoon_inc_tx_index(u32 *index, स्थिर पूर्णांक count)
अणु
	/* अगर we start using the Hi Tx ring, this needs updating */
	typhoon_inc_index(index, count, TXLO_ENTRIES);
पूर्ण

अटल अंतरभूत व्योम
typhoon_inc_rx_index(u32 *index, स्थिर पूर्णांक count)
अणु
	/* माप(काष्ठा rx_desc) != माप(काष्ठा cmd_desc) */
	*index += count * माप(काष्ठा rx_desc);
	*index %= RX_ENTRIES * माप(काष्ठा rx_desc);
पूर्ण

अटल पूर्णांक
typhoon_reset(व्योम __iomem *ioaddr, पूर्णांक रुको_type)
अणु
	पूर्णांक i, err = 0;
	पूर्णांक समयout;

	अगर (रुको_type == WaitNoSleep)
		समयout = TYPHOON_RESET_TIMEOUT_NOSLEEP;
	अन्यथा
		समयout = TYPHOON_RESET_TIMEOUT_SLEEP;

	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_MASK);
	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_STATUS);

	ioग_लिखो32(TYPHOON_RESET_ALL, ioaddr + TYPHOON_REG_SOFT_RESET);
	typhoon_post_pci_ग_लिखोs(ioaddr);
	udelay(1);
	ioग_लिखो32(TYPHOON_RESET_NONE, ioaddr + TYPHOON_REG_SOFT_RESET);

	अगर (रुको_type != NoWait) अणु
		क्रम (i = 0; i < समयout; i++) अणु
			अगर (ioपढ़ो32(ioaddr + TYPHOON_REG_STATUS) ==
			   TYPHOON_STATUS_WAITING_FOR_HOST)
				जाओ out;

			अगर (रुको_type == WaitSleep)
				schedule_समयout_unपूर्णांकerruptible(1);
			अन्यथा
				udelay(TYPHOON_UDELAY);
		पूर्ण

		err = -ETIMEDOUT;
	पूर्ण

out:
	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_MASK);
	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_STATUS);

	/* The 3XP seems to need a little extra समय to complete the load
	 * of the sleep image beक्रमe we can reliably boot it. Failure to
	 * करो this occasionally results in a hung adapter after boot in
	 * typhoon_init_one() जबतक trying to पढ़ो the MAC address or
	 * putting the card to sleep. 3Com's driver रुकोs 5ms, but
	 * that seems to be overसमाप्त. However, अगर we can sleep, we might
	 * as well give it that much समय. Otherwise, we'll give it 500us,
	 * which should be enough (I've see it work well at 100us, but still
	 * saw occasional problems.)
	 */
	अगर (रुको_type == WaitSleep)
		msleep(5);
	अन्यथा
		udelay(500);
	वापस err;
पूर्ण

अटल पूर्णांक
typhoon_रुको_status(व्योम __iomem *ioaddr, u32 रुको_value)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < TYPHOON_WAIT_TIMEOUT; i++) अणु
		अगर (ioपढ़ो32(ioaddr + TYPHOON_REG_STATUS) == रुको_value)
			जाओ out;
		udelay(TYPHOON_UDELAY);
	पूर्ण

	err = -ETIMEDOUT;

out:
	वापस err;
पूर्ण

अटल अंतरभूत व्योम
typhoon_media_status(काष्ठा net_device *dev, काष्ठा resp_desc *resp)
अणु
	अगर (resp->parm1 & TYPHOON_MEDIA_STAT_NO_LINK)
		netअगर_carrier_off(dev);
	अन्यथा
		netअगर_carrier_on(dev);
पूर्ण

अटल अंतरभूत व्योम
typhoon_hello(काष्ठा typhoon *tp)
अणु
	काष्ठा basic_ring *ring = &tp->cmdRing;
	काष्ठा cmd_desc *cmd;

	/* We only get a hello request अगर we've not sent anything to the
	 * card in a दीर्घ जबतक. If the lock is held, then we're in the
	 * process of issuing a command, so we करोn't need to respond.
	 */
	अगर (spin_trylock(&tp->command_lock)) अणु
		cmd = (काष्ठा cmd_desc *)(ring->ringBase + ring->lastWrite);
		typhoon_inc_cmd_index(&ring->lastWrite, 1);

		INIT_COMMAND_NO_RESPONSE(cmd, TYPHOON_CMD_HELLO_RESP);
		wmb();
		ioग_लिखो32(ring->lastWrite, tp->ioaddr + TYPHOON_REG_CMD_READY);
		spin_unlock(&tp->command_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक
typhoon_process_response(काष्ठा typhoon *tp, पूर्णांक resp_size,
				काष्ठा resp_desc *resp_save)
अणु
	काष्ठा typhoon_indexes *indexes = tp->indexes;
	काष्ठा resp_desc *resp;
	u8 *base = tp->respRing.ringBase;
	पूर्णांक count, len, wrap_len;
	u32 cleared;
	u32 पढ़ोy;

	cleared = le32_to_cpu(indexes->respCleared);
	पढ़ोy = le32_to_cpu(indexes->respReady);
	जबतक (cleared != पढ़ोy) अणु
		resp = (काष्ठा resp_desc *)(base + cleared);
		count = resp->numDesc + 1;
		अगर (resp_save && resp->seqNo) अणु
			अगर (count > resp_size) अणु
				resp_save->flags = TYPHOON_RESP_ERROR;
				जाओ cleanup;
			पूर्ण

			wrap_len = 0;
			len = count * माप(*resp);
			अगर (unlikely(cleared + len > RESPONSE_RING_SIZE)) अणु
				wrap_len = cleared + len - RESPONSE_RING_SIZE;
				len = RESPONSE_RING_SIZE - cleared;
			पूर्ण

			स_नकल(resp_save, resp, len);
			अगर (unlikely(wrap_len)) अणु
				resp_save += len / माप(*resp);
				स_नकल(resp_save, base, wrap_len);
			पूर्ण

			resp_save = शून्य;
		पूर्ण अन्यथा अगर (resp->cmd == TYPHOON_CMD_READ_MEDIA_STATUS) अणु
			typhoon_media_status(tp->dev, resp);
		पूर्ण अन्यथा अगर (resp->cmd == TYPHOON_CMD_HELLO_RESP) अणु
			typhoon_hello(tp);
		पूर्ण अन्यथा अणु
			netdev_err(tp->dev,
				   "dumping unexpected response 0x%04x:%d:0x%02x:0x%04x:%08x:%08x\n",
				   le16_to_cpu(resp->cmd),
				   resp->numDesc, resp->flags,
				   le16_to_cpu(resp->parm1),
				   le32_to_cpu(resp->parm2),
				   le32_to_cpu(resp->parm3));
		पूर्ण

cleanup:
		typhoon_inc_resp_index(&cleared, count);
	पूर्ण

	indexes->respCleared = cpu_to_le32(cleared);
	wmb();
	वापस resp_save == शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक
typhoon_num_मुक्त(पूर्णांक lastWrite, पूर्णांक lastRead, पूर्णांक ringSize)
अणु
	/* this works क्रम all descriptors but rx_desc, as they are a
	 * dअगरferent size than the cmd_desc -- everyone अन्यथा is the same
	 */
	lastWrite /= माप(काष्ठा cmd_desc);
	lastRead /= माप(काष्ठा cmd_desc);
	वापस (ringSize + lastRead - lastWrite - 1) % ringSize;
पूर्ण

अटल अंतरभूत पूर्णांक
typhoon_num_मुक्त_cmd(काष्ठा typhoon *tp)
अणु
	पूर्णांक lastWrite = tp->cmdRing.lastWrite;
	पूर्णांक cmdCleared = le32_to_cpu(tp->indexes->cmdCleared);

	वापस typhoon_num_मुक्त(lastWrite, cmdCleared, COMMAND_ENTRIES);
पूर्ण

अटल अंतरभूत पूर्णांक
typhoon_num_मुक्त_resp(काष्ठा typhoon *tp)
अणु
	पूर्णांक respReady = le32_to_cpu(tp->indexes->respReady);
	पूर्णांक respCleared = le32_to_cpu(tp->indexes->respCleared);

	वापस typhoon_num_मुक्त(respReady, respCleared, RESPONSE_ENTRIES);
पूर्ण

अटल अंतरभूत पूर्णांक
typhoon_num_मुक्त_tx(काष्ठा transmit_ring *ring)
अणु
	/* अगर we start using the Hi Tx ring, this needs updating */
	वापस typhoon_num_मुक्त(ring->lastWrite, ring->lastRead, TXLO_ENTRIES);
पूर्ण

अटल पूर्णांक
typhoon_issue_command(काष्ठा typhoon *tp, पूर्णांक num_cmd, काष्ठा cmd_desc *cmd,
		      पूर्णांक num_resp, काष्ठा resp_desc *resp)
अणु
	काष्ठा typhoon_indexes *indexes = tp->indexes;
	काष्ठा basic_ring *ring = &tp->cmdRing;
	काष्ठा resp_desc local_resp;
	पूर्णांक i, err = 0;
	पूर्णांक got_resp;
	पूर्णांक मुक्तCmd, मुक्तResp;
	पूर्णांक len, wrap_len;

	spin_lock(&tp->command_lock);

	मुक्तCmd = typhoon_num_मुक्त_cmd(tp);
	मुक्तResp = typhoon_num_मुक्त_resp(tp);

	अगर (मुक्तCmd < num_cmd || मुक्तResp < num_resp) अणु
		netdev_err(tp->dev, "no descs for cmd, had (needed) %d (%d) cmd, %d (%d) resp\n",
			   मुक्तCmd, num_cmd, मुक्तResp, num_resp);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (cmd->flags & TYPHOON_CMD_RESPOND) अणु
		/* If we're expecting a response, but the caller hasn't given
		 * us a place to put it, we'll provide one.
		 */
		tp->aरुकोing_resp = 1;
		अगर (resp == शून्य) अणु
			resp = &local_resp;
			num_resp = 1;
		पूर्ण
	पूर्ण

	wrap_len = 0;
	len = num_cmd * माप(*cmd);
	अगर (unlikely(ring->lastWrite + len > COMMAND_RING_SIZE)) अणु
		wrap_len = ring->lastWrite + len - COMMAND_RING_SIZE;
		len = COMMAND_RING_SIZE - ring->lastWrite;
	पूर्ण

	स_नकल(ring->ringBase + ring->lastWrite, cmd, len);
	अगर (unlikely(wrap_len)) अणु
		काष्ठा cmd_desc *wrap_ptr = cmd;
		wrap_ptr += len / माप(*cmd);
		स_नकल(ring->ringBase, wrap_ptr, wrap_len);
	पूर्ण

	typhoon_inc_cmd_index(&ring->lastWrite, num_cmd);

	/* "I feel a presence... another warrior is on the mesa."
	 */
	wmb();
	ioग_लिखो32(ring->lastWrite, tp->ioaddr + TYPHOON_REG_CMD_READY);
	typhoon_post_pci_ग_लिखोs(tp->ioaddr);

	अगर ((cmd->flags & TYPHOON_CMD_RESPOND) == 0)
		जाओ out;

	/* Ugh. We'll be here about 8ms, spinning our thumbs, unable to
	 * preempt or करो anything other than take पूर्णांकerrupts. So, करोn't
	 * रुको क्रम a response unless you have to.
	 *
	 * I've thought about trying to sleep here, but we're called
	 * from many contexts that करोn't allow that. Also, given the way
	 * 3Com has implemented irq coalescing, we would likely समयout --
	 * this has been observed in real lअगरe!
	 *
	 * The big समाप्तer is we have to रुको to get stats from the card,
	 * though we could go to a periodic refresh of those अगर we करोn't
	 * mind them getting somewhat stale. The rest of the रुकोing
	 * commands occur during खोलो/बंद/suspend/resume, so they aren't
	 * समय critical. Creating SAs in the future will also have to
	 * रुको here.
	 */
	got_resp = 0;
	क्रम (i = 0; i < TYPHOON_WAIT_TIMEOUT && !got_resp; i++) अणु
		अगर (indexes->respCleared != indexes->respReady)
			got_resp = typhoon_process_response(tp, num_resp,
								resp);
		udelay(TYPHOON_UDELAY);
	पूर्ण

	अगर (!got_resp) अणु
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* Collect the error response even अगर we करोn't care about the
	 * rest of the response
	 */
	अगर (resp->flags & TYPHOON_RESP_ERROR)
		err = -EIO;

out:
	अगर (tp->aरुकोing_resp) अणु
		tp->aरुकोing_resp = 0;
		smp_wmb();

		/* Ugh. If a response was added to the ring between
		 * the call to typhoon_process_response() and the clearing
		 * of tp->aरुकोing_resp, we could have missed the पूर्णांकerrupt
		 * and it could hang in the ring an indeterminate amount of
		 * समय. So, check क्रम it, and पूर्णांकerrupt ourselves अगर this
		 * is the हाल.
		 */
		अगर (indexes->respCleared != indexes->respReady)
			ioग_लिखो32(1, tp->ioaddr + TYPHOON_REG_SELF_INTERRUPT);
	पूर्ण

	spin_unlock(&tp->command_lock);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम
typhoon_tso_fill(काष्ठा sk_buff *skb, काष्ठा transmit_ring *txRing,
			u32 ring_dma)
अणु
	काष्ठा tcpopt_desc *tcpd;
	u32 tcpd_offset = ring_dma;

	tcpd = (काष्ठा tcpopt_desc *) (txRing->ringBase + txRing->lastWrite);
	tcpd_offset += txRing->lastWrite;
	tcpd_offset += दुरत्व(काष्ठा tcpopt_desc, bytesTx);
	typhoon_inc_tx_index(&txRing->lastWrite, 1);

	tcpd->flags = TYPHOON_OPT_DESC | TYPHOON_OPT_TCP_SEG;
	tcpd->numDesc = 1;
	tcpd->mss_flags = cpu_to_le16(skb_tso_size(skb));
	tcpd->mss_flags |= TYPHOON_TSO_FIRST | TYPHOON_TSO_LAST;
	tcpd->respAddrLo = cpu_to_le32(tcpd_offset);
	tcpd->bytesTx = cpu_to_le32(skb->len);
	tcpd->status = 0;
पूर्ण

अटल netdev_tx_t
typhoon_start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);
	काष्ठा transmit_ring *txRing;
	काष्ठा tx_desc *txd, *first_txd;
	dma_addr_t skb_dma;
	पूर्णांक numDesc;

	/* we have two rings to choose from, but we only use txLo क्रम now
	 * If we start using the Hi ring as well, we'll need to update
	 * typhoon_stop_runसमय(), typhoon_पूर्णांकerrupt(), typhoon_num_मुक्त_tx(),
	 * and TXHI_ENTRIES to match, as well as update the TSO code below
	 * to get the right DMA address
	 */
	txRing = &tp->txLoRing;

	/* We need one descriptor क्रम each fragment of the sk_buff, plus the
	 * one क्रम the ->data area of it.
	 *
	 * The करोcs say a maximum of 16 fragment descriptors per TCP option
	 * descriptor, then make a new packet descriptor and option descriptor
	 * क्रम the next 16 fragments. The engineers say just an option
	 * descriptor is needed. I've tested up to 26 fragments with a single
	 * packet descriptor/option descriptor combo, so I use that क्रम now.
	 *
	 * If problems develop with TSO, check this first.
	 */
	numDesc = skb_shinfo(skb)->nr_frags + 1;
	अगर (skb_is_gso(skb))
		numDesc++;

	/* When checking क्रम मुक्त space in the ring, we need to also
	 * account क्रम the initial Tx descriptor, and we always must leave
	 * at least one descriptor unused in the ring so that it करोesn't
	 * wrap and look empty.
	 *
	 * The only समय we should loop here is when we hit the race
	 * between marking the queue awake and updating the cleared index.
	 * Just loop and it will appear. This comes from the acenic driver.
	 */
	जबतक (unlikely(typhoon_num_मुक्त_tx(txRing) < (numDesc + 2)))
		smp_rmb();

	first_txd = (काष्ठा tx_desc *) (txRing->ringBase + txRing->lastWrite);
	typhoon_inc_tx_index(&txRing->lastWrite, 1);

	first_txd->flags = TYPHOON_TX_DESC | TYPHOON_DESC_VALID;
	first_txd->numDesc = 0;
	first_txd->len = 0;
	first_txd->tx_addr = (u64)((अचिन्हित दीर्घ) skb);
	first_txd->processFlags = 0;

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		/* The 3XP will figure out अगर this is UDP/TCP */
		first_txd->processFlags |= TYPHOON_TX_PF_TCP_CHKSUM;
		first_txd->processFlags |= TYPHOON_TX_PF_UDP_CHKSUM;
		first_txd->processFlags |= TYPHOON_TX_PF_IP_CHKSUM;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		first_txd->processFlags |=
		    TYPHOON_TX_PF_INSERT_VLAN | TYPHOON_TX_PF_VLAN_PRIORITY;
		first_txd->processFlags |=
		    cpu_to_le32(htons(skb_vlan_tag_get(skb)) <<
				TYPHOON_TX_PF_VLAN_TAG_SHIFT);
	पूर्ण

	अगर (skb_is_gso(skb)) अणु
		first_txd->processFlags |= TYPHOON_TX_PF_TCP_SEGMENT;
		first_txd->numDesc++;

		typhoon_tso_fill(skb, txRing, tp->txlo_dma_addr);
	पूर्ण

	txd = (काष्ठा tx_desc *) (txRing->ringBase + txRing->lastWrite);
	typhoon_inc_tx_index(&txRing->lastWrite, 1);

	/* No need to worry about padding packet -- the firmware pads
	 * it with zeros to ETH_ZLEN क्रम us.
	 */
	अगर (skb_shinfo(skb)->nr_frags == 0) अणु
		skb_dma = dma_map_single(&tp->tx_pdev->dev, skb->data,
					 skb->len, DMA_TO_DEVICE);
		txd->flags = TYPHOON_FRAG_DESC | TYPHOON_DESC_VALID;
		txd->len = cpu_to_le16(skb->len);
		txd->frag.addr = cpu_to_le32(skb_dma);
		txd->frag.addrHi = 0;
		first_txd->numDesc++;
	पूर्ण अन्यथा अणु
		पूर्णांक i, len;

		len = skb_headlen(skb);
		skb_dma = dma_map_single(&tp->tx_pdev->dev, skb->data, len,
					 DMA_TO_DEVICE);
		txd->flags = TYPHOON_FRAG_DESC | TYPHOON_DESC_VALID;
		txd->len = cpu_to_le16(len);
		txd->frag.addr = cpu_to_le32(skb_dma);
		txd->frag.addrHi = 0;
		first_txd->numDesc++;

		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			व्योम *frag_addr;

			txd = (काष्ठा tx_desc *) (txRing->ringBase +
						txRing->lastWrite);
			typhoon_inc_tx_index(&txRing->lastWrite, 1);

			len = skb_frag_size(frag);
			frag_addr = skb_frag_address(frag);
			skb_dma = dma_map_single(&tp->tx_pdev->dev, frag_addr,
						 len, DMA_TO_DEVICE);
			txd->flags = TYPHOON_FRAG_DESC | TYPHOON_DESC_VALID;
			txd->len = cpu_to_le16(len);
			txd->frag.addr = cpu_to_le32(skb_dma);
			txd->frag.addrHi = 0;
			first_txd->numDesc++;
		पूर्ण
	पूर्ण

	/* Kick the 3XP
	 */
	wmb();
	ioग_लिखो32(txRing->lastWrite, tp->tx_ioaddr + txRing->ग_लिखोRegister);

	/* If we करोn't have room to put the worst हाल packet on the
	 * queue, then we must stop the queue. We need 2 extra
	 * descriptors -- one to prevent ring wrap, and one क्रम the
	 * Tx header.
	 */
	numDesc = MAX_SKB_FRAGS + TSO_NUM_DESCRIPTORS + 1;

	अगर (typhoon_num_मुक्त_tx(txRing) < (numDesc + 2)) अणु
		netअगर_stop_queue(dev);

		/* A Tx complete IRQ could have gotten between, making
		 * the ring मुक्त again. Only need to recheck here, since
		 * Tx is serialized.
		 */
		अगर (typhoon_num_मुक्त_tx(txRing) >= (numDesc + 2))
			netअगर_wake_queue(dev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम
typhoon_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);
	काष्ठा cmd_desc xp_cmd;
	u32 mc_filter[2];
	__le16 filter;

	filter = TYPHOON_RX_FILTER_सूचीECTED | TYPHOON_RX_FILTER_BROADCAST;
	अगर (dev->flags & IFF_PROMISC) अणु
		filter |= TYPHOON_RX_FILTER_PROMISCOUS;
	पूर्ण अन्यथा अगर ((netdev_mc_count(dev) > multicast_filter_limit) ||
		  (dev->flags & IFF_ALLMULTI)) अणु
		/* Too many to match, or accept all multicasts. */
		filter |= TYPHOON_RX_FILTER_ALL_MCAST;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;

		स_रखो(mc_filter, 0, माप(mc_filter));
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			पूर्णांक bit = ether_crc(ETH_ALEN, ha->addr) & 0x3f;
			mc_filter[bit >> 5] |= 1 << (bit & 0x1f);
		पूर्ण

		INIT_COMMAND_NO_RESPONSE(&xp_cmd,
					 TYPHOON_CMD_SET_MULTICAST_HASH);
		xp_cmd.parm1 = TYPHOON_MCAST_HASH_SET;
		xp_cmd.parm2 = cpu_to_le32(mc_filter[0]);
		xp_cmd.parm3 = cpu_to_le32(mc_filter[1]);
		typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);

		filter |= TYPHOON_RX_FILTER_MCAST_HASH;
	पूर्ण

	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_SET_RX_FILTER);
	xp_cmd.parm1 = filter;
	typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
पूर्ण

अटल पूर्णांक
typhoon_करो_get_stats(काष्ठा typhoon *tp)
अणु
	काष्ठा net_device_stats *stats = &tp->dev->stats;
	काष्ठा net_device_stats *saved = &tp->stats_saved;
	काष्ठा cmd_desc xp_cmd;
	काष्ठा resp_desc xp_resp[7];
	काष्ठा stats_resp *s = (काष्ठा stats_resp *) xp_resp;
	पूर्णांक err;

	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_READ_STATS);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 7, xp_resp);
	अगर (err < 0)
		वापस err;

	/* 3Com's Linux driver uses txMultipleCollisions as it's
	 * collisions value, but there is some other collision info as well...
	 *
	 * The extra status reported would be a good candidate क्रम
	 * ethtool_ops->get_अणुstrings,statsपूर्ण()
	 */
	stats->tx_packets = le32_to_cpu(s->txPackets) +
			saved->tx_packets;
	stats->tx_bytes = le64_to_cpu(s->txBytes) +
			saved->tx_bytes;
	stats->tx_errors = le32_to_cpu(s->txCarrierLost) +
			saved->tx_errors;
	stats->tx_carrier_errors = le32_to_cpu(s->txCarrierLost) +
			saved->tx_carrier_errors;
	stats->collisions = le32_to_cpu(s->txMultipleCollisions) +
			saved->collisions;
	stats->rx_packets = le32_to_cpu(s->rxPacketsGood) +
			saved->rx_packets;
	stats->rx_bytes = le64_to_cpu(s->rxBytesGood) +
			saved->rx_bytes;
	stats->rx_fअगरo_errors = le32_to_cpu(s->rxFअगरoOverruns) +
			saved->rx_fअगरo_errors;
	stats->rx_errors = le32_to_cpu(s->rxFअगरoOverruns) +
			le32_to_cpu(s->BadSSD) + le32_to_cpu(s->rxCrcErrors) +
			saved->rx_errors;
	stats->rx_crc_errors = le32_to_cpu(s->rxCrcErrors) +
			saved->rx_crc_errors;
	stats->rx_length_errors = le32_to_cpu(s->rxOversized) +
			saved->rx_length_errors;
	tp->speed = (s->linkStatus & TYPHOON_LINK_100MBPS) ?
			SPEED_100 : SPEED_10;
	tp->duplex = (s->linkStatus & TYPHOON_LINK_FULL_DUPLEX) ?
			DUPLEX_FULL : DUPLEX_HALF;

	वापस 0;
पूर्ण

अटल काष्ठा net_device_stats *
typhoon_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &tp->dev->stats;
	काष्ठा net_device_stats *saved = &tp->stats_saved;

	smp_rmb();
	अगर (tp->card_state == Sleeping)
		वापस saved;

	अगर (typhoon_करो_get_stats(tp) < 0) अणु
		netdev_err(dev, "error getting stats\n");
		वापस saved;
	पूर्ण

	वापस stats;
पूर्ण

अटल व्योम
typhoon_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);
	काष्ठा pci_dev *pci_dev = tp->pdev;
	काष्ठा cmd_desc xp_cmd;
	काष्ठा resp_desc xp_resp[3];

	smp_rmb();
	अगर (tp->card_state == Sleeping) अणु
		strlcpy(info->fw_version, "Sleep image",
			माप(info->fw_version));
	पूर्ण अन्यथा अणु
		INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_READ_VERSIONS);
		अगर (typhoon_issue_command(tp, 1, &xp_cmd, 3, xp_resp) < 0) अणु
			strlcpy(info->fw_version, "Unknown runtime",
				माप(info->fw_version));
		पूर्ण अन्यथा अणु
			u32 sleep_ver = le32_to_cpu(xp_resp[0].parm2);
			snम_लिखो(info->fw_version, माप(info->fw_version),
				"%02x.%03x.%03x", sleep_ver >> 24,
				(sleep_ver >> 12) & 0xfff, sleep_ver & 0xfff);
		पूर्ण
	पूर्ण

	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(pci_dev), माप(info->bus_info));
पूर्ण

अटल पूर्णांक
typhoon_get_link_ksettings(काष्ठा net_device *dev,
			   काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);
	u32 supported, advertising = 0;

	supported = SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
				SUPPORTED_Autoneg;

	चयन (tp->xcvr_select) अणु
	हाल TYPHOON_XCVR_10HALF:
		advertising = ADVERTISED_10baseT_Half;
		अवरोध;
	हाल TYPHOON_XCVR_10FULL:
		advertising = ADVERTISED_10baseT_Full;
		अवरोध;
	हाल TYPHOON_XCVR_100HALF:
		advertising = ADVERTISED_100baseT_Half;
		अवरोध;
	हाल TYPHOON_XCVR_100FULL:
		advertising = ADVERTISED_100baseT_Full;
		अवरोध;
	हाल TYPHOON_XCVR_AUTONEG:
		advertising = ADVERTISED_10baseT_Half |
					    ADVERTISED_10baseT_Full |
					    ADVERTISED_100baseT_Half |
					    ADVERTISED_100baseT_Full |
					    ADVERTISED_Autoneg;
		अवरोध;
	पूर्ण

	अगर (tp->capabilities & TYPHOON_FIBER) अणु
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		cmd->base.port = PORT_FIBRE;
	पूर्ण अन्यथा अणु
		supported |= SUPPORTED_10baseT_Half |
		    			SUPPORTED_10baseT_Full |
					SUPPORTED_TP;
		advertising |= ADVERTISED_TP;
		cmd->base.port = PORT_TP;
	पूर्ण

	/* need to get stats to make these link speed/duplex valid */
	typhoon_करो_get_stats(tp);
	cmd->base.speed = tp->speed;
	cmd->base.duplex = tp->duplex;
	cmd->base.phy_address = 0;
	अगर (tp->xcvr_select == TYPHOON_XCVR_AUTONEG)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
typhoon_set_link_ksettings(काष्ठा net_device *dev,
			   स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);
	u32 speed = cmd->base.speed;
	काष्ठा cmd_desc xp_cmd;
	__le16 xcvr;
	पूर्णांक err;

	err = -EINVAL;
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		xcvr = TYPHOON_XCVR_AUTONEG;
	पूर्ण अन्यथा अणु
		अगर (cmd->base.duplex == DUPLEX_HALF) अणु
			अगर (speed == SPEED_10)
				xcvr = TYPHOON_XCVR_10HALF;
			अन्यथा अगर (speed == SPEED_100)
				xcvr = TYPHOON_XCVR_100HALF;
			अन्यथा
				जाओ out;
		पूर्ण अन्यथा अगर (cmd->base.duplex == DUPLEX_FULL) अणु
			अगर (speed == SPEED_10)
				xcvr = TYPHOON_XCVR_10FULL;
			अन्यथा अगर (speed == SPEED_100)
				xcvr = TYPHOON_XCVR_100FULL;
			अन्यथा
				जाओ out;
		पूर्ण अन्यथा
			जाओ out;
	पूर्ण

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_XCVR_SELECT);
	xp_cmd.parm1 = xcvr;
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ out;

	tp->xcvr_select = xcvr;
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		tp->speed = 0xff;	/* invalid */
		tp->duplex = 0xff;	/* invalid */
	पूर्ण अन्यथा अणु
		tp->speed = speed;
		tp->duplex = cmd->base.duplex;
	पूर्ण

out:
	वापस err;
पूर्ण

अटल व्योम
typhoon_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);

	wol->supported = WAKE_PHY | WAKE_MAGIC;
	wol->wolopts = 0;
	अगर (tp->wol_events & TYPHOON_WAKE_LINK_EVENT)
		wol->wolopts |= WAKE_PHY;
	अगर (tp->wol_events & TYPHOON_WAKE_MAGIC_PKT)
		wol->wolopts |= WAKE_MAGIC;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक
typhoon_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);

	अगर (wol->wolopts & ~(WAKE_PHY | WAKE_MAGIC))
		वापस -EINVAL;

	tp->wol_events = 0;
	अगर (wol->wolopts & WAKE_PHY)
		tp->wol_events |= TYPHOON_WAKE_LINK_EVENT;
	अगर (wol->wolopts & WAKE_MAGIC)
		tp->wol_events |= TYPHOON_WAKE_MAGIC_PKT;

	वापस 0;
पूर्ण

अटल व्योम
typhoon_get_ringparam(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *ering)
अणु
	ering->rx_max_pending = RXENT_ENTRIES;
	ering->tx_max_pending = TXLO_ENTRIES - 1;

	ering->rx_pending = RXENT_ENTRIES;
	ering->tx_pending = TXLO_ENTRIES - 1;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops typhoon_ethtool_ops = अणु
	.get_drvinfo		= typhoon_get_drvinfo,
	.get_wol		= typhoon_get_wol,
	.set_wol		= typhoon_set_wol,
	.get_link		= ethtool_op_get_link,
	.get_ringparam		= typhoon_get_ringparam,
	.get_link_ksettings	= typhoon_get_link_ksettings,
	.set_link_ksettings	= typhoon_set_link_ksettings,
पूर्ण;

अटल पूर्णांक
typhoon_रुको_पूर्णांकerrupt(व्योम __iomem *ioaddr)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < TYPHOON_WAIT_TIMEOUT; i++) अणु
		अगर (ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_STATUS) &
		   TYPHOON_INTR_BOOTCMD)
			जाओ out;
		udelay(TYPHOON_UDELAY);
	पूर्ण

	err = -ETIMEDOUT;

out:
	ioग_लिखो32(TYPHOON_INTR_BOOTCMD, ioaddr + TYPHOON_REG_INTR_STATUS);
	वापस err;
पूर्ण

#घोषणा shared_offset(x)	दुरत्व(काष्ठा typhoon_shared, x)

अटल व्योम
typhoon_init_पूर्णांकerface(काष्ठा typhoon *tp)
अणु
	काष्ठा typhoon_पूर्णांकerface *अगरace = &tp->shared->अगरace;
	dma_addr_t shared_dma;

	स_रखो(tp->shared, 0, माप(काष्ठा typhoon_shared));

	/* The *Hi members of अगरace are all init'd to zero by the स_रखो().
	 */
	shared_dma = tp->shared_dma + shared_offset(indexes);
	अगरace->ringIndex = cpu_to_le32(shared_dma);

	shared_dma = tp->shared_dma + shared_offset(txLo);
	अगरace->txLoAddr = cpu_to_le32(shared_dma);
	अगरace->txLoSize = cpu_to_le32(TXLO_ENTRIES * माप(काष्ठा tx_desc));

	shared_dma = tp->shared_dma + shared_offset(txHi);
	अगरace->txHiAddr = cpu_to_le32(shared_dma);
	अगरace->txHiSize = cpu_to_le32(TXHI_ENTRIES * माप(काष्ठा tx_desc));

	shared_dma = tp->shared_dma + shared_offset(rxBuff);
	अगरace->rxBuffAddr = cpu_to_le32(shared_dma);
	अगरace->rxBuffSize = cpu_to_le32(RXFREE_ENTRIES *
					माप(काष्ठा rx_मुक्त));

	shared_dma = tp->shared_dma + shared_offset(rxLo);
	अगरace->rxLoAddr = cpu_to_le32(shared_dma);
	अगरace->rxLoSize = cpu_to_le32(RX_ENTRIES * माप(काष्ठा rx_desc));

	shared_dma = tp->shared_dma + shared_offset(rxHi);
	अगरace->rxHiAddr = cpu_to_le32(shared_dma);
	अगरace->rxHiSize = cpu_to_le32(RX_ENTRIES * माप(काष्ठा rx_desc));

	shared_dma = tp->shared_dma + shared_offset(cmd);
	अगरace->cmdAddr = cpu_to_le32(shared_dma);
	अगरace->cmdSize = cpu_to_le32(COMMAND_RING_SIZE);

	shared_dma = tp->shared_dma + shared_offset(resp);
	अगरace->respAddr = cpu_to_le32(shared_dma);
	अगरace->respSize = cpu_to_le32(RESPONSE_RING_SIZE);

	shared_dma = tp->shared_dma + shared_offset(zeroWord);
	अगरace->zeroAddr = cpu_to_le32(shared_dma);

	tp->indexes = &tp->shared->indexes;
	tp->txLoRing.ringBase = (u8 *) tp->shared->txLo;
	tp->txHiRing.ringBase = (u8 *) tp->shared->txHi;
	tp->rxLoRing.ringBase = (u8 *) tp->shared->rxLo;
	tp->rxHiRing.ringBase = (u8 *) tp->shared->rxHi;
	tp->rxBuffRing.ringBase = (u8 *) tp->shared->rxBuff;
	tp->cmdRing.ringBase = (u8 *) tp->shared->cmd;
	tp->respRing.ringBase = (u8 *) tp->shared->resp;

	tp->txLoRing.ग_लिखोRegister = TYPHOON_REG_TX_LO_READY;
	tp->txHiRing.ग_लिखोRegister = TYPHOON_REG_TX_HI_READY;

	tp->txlo_dma_addr = le32_to_cpu(अगरace->txLoAddr);
	tp->card_state = Sleeping;

	tp->offload = TYPHOON_OFFLOAD_IP_CHKSUM | TYPHOON_OFFLOAD_TCP_CHKSUM;
	tp->offload |= TYPHOON_OFFLOAD_UDP_CHKSUM | TSO_OFFLOAD_ON;
	tp->offload |= TYPHOON_OFFLOAD_VLAN;

	spin_lock_init(&tp->command_lock);

	/* Force the ग_लिखोs to the shared memory area out beक्रमe continuing. */
	wmb();
पूर्ण

अटल व्योम
typhoon_init_rings(काष्ठा typhoon *tp)
अणु
	स_रखो(tp->indexes, 0, माप(काष्ठा typhoon_indexes));

	tp->txLoRing.lastWrite = 0;
	tp->txHiRing.lastWrite = 0;
	tp->rxLoRing.lastWrite = 0;
	tp->rxHiRing.lastWrite = 0;
	tp->rxBuffRing.lastWrite = 0;
	tp->cmdRing.lastWrite = 0;
	tp->respRing.lastWrite = 0;

	tp->txLoRing.lastRead = 0;
	tp->txHiRing.lastRead = 0;
पूर्ण

अटल स्थिर काष्ठा firmware *typhoon_fw;

अटल पूर्णांक
typhoon_request_firmware(काष्ठा typhoon *tp)
अणु
	स्थिर काष्ठा typhoon_file_header *fHdr;
	स्थिर काष्ठा typhoon_section_header *sHdr;
	स्थिर u8 *image_data;
	u32 numSections;
	u32 section_len;
	u32 reमुख्यing;
	पूर्णांक err;

	अगर (typhoon_fw)
		वापस 0;

	err = request_firmware(&typhoon_fw, FIRMWARE_NAME, &tp->pdev->dev);
	अगर (err) अणु
		netdev_err(tp->dev, "Failed to load firmware \"%s\"\n",
			   FIRMWARE_NAME);
		वापस err;
	पूर्ण

	image_data = typhoon_fw->data;
	reमुख्यing = typhoon_fw->size;
	अगर (reमुख्यing < माप(काष्ठा typhoon_file_header))
		जाओ invalid_fw;

	fHdr = (काष्ठा typhoon_file_header *) image_data;
	अगर (स_भेद(fHdr->tag, "TYPHOON", 8))
		जाओ invalid_fw;

	numSections = le32_to_cpu(fHdr->numSections);
	image_data += माप(काष्ठा typhoon_file_header);
	reमुख्यing -= माप(काष्ठा typhoon_file_header);

	जबतक (numSections--) अणु
		अगर (reमुख्यing < माप(काष्ठा typhoon_section_header))
			जाओ invalid_fw;

		sHdr = (काष्ठा typhoon_section_header *) image_data;
		image_data += माप(काष्ठा typhoon_section_header);
		section_len = le32_to_cpu(sHdr->len);

		अगर (reमुख्यing < section_len)
			जाओ invalid_fw;

		image_data += section_len;
		reमुख्यing -= section_len;
	पूर्ण

	वापस 0;

invalid_fw:
	netdev_err(tp->dev, "Invalid firmware image\n");
	release_firmware(typhoon_fw);
	typhoon_fw = शून्य;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
typhoon_करोwnload_firmware(काष्ठा typhoon *tp)
अणु
	व्योम __iomem *ioaddr = tp->ioaddr;
	काष्ठा pci_dev *pdev = tp->pdev;
	स्थिर काष्ठा typhoon_file_header *fHdr;
	स्थिर काष्ठा typhoon_section_header *sHdr;
	स्थिर u8 *image_data;
	व्योम *dpage;
	dma_addr_t dpage_dma;
	__sum16 csum;
	u32 irqEnabled;
	u32 irqMasked;
	u32 numSections;
	u32 section_len;
	u32 len;
	u32 load_addr;
	u32 hmac;
	पूर्णांक i;
	पूर्णांक err;

	image_data = typhoon_fw->data;
	fHdr = (काष्ठा typhoon_file_header *) image_data;

	/* Cannot just map the firmware image using dma_map_single() as
	 * the firmware is vदो_स्मृति()'d and may not be physically contiguous,
	 * so we allocate some coherent memory to copy the sections पूर्णांकo.
	 */
	err = -ENOMEM;
	dpage = dma_alloc_coherent(&pdev->dev, PAGE_SIZE, &dpage_dma, GFP_ATOMIC);
	अगर (!dpage) अणु
		netdev_err(tp->dev, "no DMA mem for firmware\n");
		जाओ err_out;
	पूर्ण

	irqEnabled = ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_ENABLE);
	ioग_लिखो32(irqEnabled | TYPHOON_INTR_BOOTCMD,
	       ioaddr + TYPHOON_REG_INTR_ENABLE);
	irqMasked = ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_MASK);
	ioग_लिखो32(irqMasked | TYPHOON_INTR_BOOTCMD,
	       ioaddr + TYPHOON_REG_INTR_MASK);

	err = -ETIMEDOUT;
	अगर (typhoon_रुको_status(ioaddr, TYPHOON_STATUS_WAITING_FOR_HOST) < 0) अणु
		netdev_err(tp->dev, "card ready timeout\n");
		जाओ err_out_irq;
	पूर्ण

	numSections = le32_to_cpu(fHdr->numSections);
	load_addr = le32_to_cpu(fHdr->startAddr);

	ioग_लिखो32(TYPHOON_INTR_BOOTCMD, ioaddr + TYPHOON_REG_INTR_STATUS);
	ioग_लिखो32(load_addr, ioaddr + TYPHOON_REG_DOWNLOAD_BOOT_ADDR);
	hmac = le32_to_cpu(fHdr->hmacDigest[0]);
	ioग_लिखो32(hmac, ioaddr + TYPHOON_REG_DOWNLOAD_HMAC_0);
	hmac = le32_to_cpu(fHdr->hmacDigest[1]);
	ioग_लिखो32(hmac, ioaddr + TYPHOON_REG_DOWNLOAD_HMAC_1);
	hmac = le32_to_cpu(fHdr->hmacDigest[2]);
	ioग_लिखो32(hmac, ioaddr + TYPHOON_REG_DOWNLOAD_HMAC_2);
	hmac = le32_to_cpu(fHdr->hmacDigest[3]);
	ioग_लिखो32(hmac, ioaddr + TYPHOON_REG_DOWNLOAD_HMAC_3);
	hmac = le32_to_cpu(fHdr->hmacDigest[4]);
	ioग_लिखो32(hmac, ioaddr + TYPHOON_REG_DOWNLOAD_HMAC_4);
	typhoon_post_pci_ग_लिखोs(ioaddr);
	ioग_लिखो32(TYPHOON_BOOTCMD_RUNTIME_IMAGE, ioaddr + TYPHOON_REG_COMMAND);

	image_data += माप(काष्ठा typhoon_file_header);

	/* The ioपढ़ो32() in typhoon_रुको_पूर्णांकerrupt() will क्रमce the
	 * last ग_लिखो to the command रेजिस्टर to post, so
	 * we करोn't need a typhoon_post_pci_ग_लिखोs() after it.
	 */
	क्रम (i = 0; i < numSections; i++) अणु
		sHdr = (काष्ठा typhoon_section_header *) image_data;
		image_data += माप(काष्ठा typhoon_section_header);
		load_addr = le32_to_cpu(sHdr->startAddr);
		section_len = le32_to_cpu(sHdr->len);

		जबतक (section_len) अणु
			len = min_t(u32, section_len, PAGE_SIZE);

			अगर (typhoon_रुको_पूर्णांकerrupt(ioaddr) < 0 ||
			   ioपढ़ो32(ioaddr + TYPHOON_REG_STATUS) !=
			   TYPHOON_STATUS_WAITING_FOR_SEGMENT) अणु
				netdev_err(tp->dev, "segment ready timeout\n");
				जाओ err_out_irq;
			पूर्ण

			/* Do an pseuकरो IPv4 checksum on the data -- first
			 * need to convert each u16 to cpu order beक्रमe
			 * summing. Fortunately, due to the properties of
			 * the checksum, we can करो this once, at the end.
			 */
			csum = csum_fold(csum_partial_copy_nocheck(image_data,
								   dpage, len));

			ioग_लिखो32(len, ioaddr + TYPHOON_REG_BOOT_LENGTH);
			ioग_लिखो32(le16_to_cpu((__क्रमce __le16)csum),
					ioaddr + TYPHOON_REG_BOOT_CHECKSUM);
			ioग_लिखो32(load_addr,
					ioaddr + TYPHOON_REG_BOOT_DEST_ADDR);
			ioग_लिखो32(0, ioaddr + TYPHOON_REG_BOOT_DATA_HI);
			ioग_लिखो32(dpage_dma, ioaddr + TYPHOON_REG_BOOT_DATA_LO);
			typhoon_post_pci_ग_लिखोs(ioaddr);
			ioग_लिखो32(TYPHOON_BOOTCMD_SEG_AVAILABLE,
					ioaddr + TYPHOON_REG_COMMAND);

			image_data += len;
			load_addr += len;
			section_len -= len;
		पूर्ण
	पूर्ण

	अगर (typhoon_रुको_पूर्णांकerrupt(ioaddr) < 0 ||
	   ioपढ़ो32(ioaddr + TYPHOON_REG_STATUS) !=
	   TYPHOON_STATUS_WAITING_FOR_SEGMENT) अणु
		netdev_err(tp->dev, "final segment ready timeout\n");
		जाओ err_out_irq;
	पूर्ण

	ioग_लिखो32(TYPHOON_BOOTCMD_DNLD_COMPLETE, ioaddr + TYPHOON_REG_COMMAND);

	अगर (typhoon_रुको_status(ioaddr, TYPHOON_STATUS_WAITING_FOR_BOOT) < 0) अणु
		netdev_err(tp->dev, "boot ready timeout, status 0x%0x\n",
			   ioपढ़ो32(ioaddr + TYPHOON_REG_STATUS));
		जाओ err_out_irq;
	पूर्ण

	err = 0;

err_out_irq:
	ioग_लिखो32(irqMasked, ioaddr + TYPHOON_REG_INTR_MASK);
	ioग_लिखो32(irqEnabled, ioaddr + TYPHOON_REG_INTR_ENABLE);

	dma_मुक्त_coherent(&pdev->dev, PAGE_SIZE, dpage, dpage_dma);

err_out:
	वापस err;
पूर्ण

अटल पूर्णांक
typhoon_boot_3XP(काष्ठा typhoon *tp, u32 initial_status)
अणु
	व्योम __iomem *ioaddr = tp->ioaddr;

	अगर (typhoon_रुको_status(ioaddr, initial_status) < 0) अणु
		netdev_err(tp->dev, "boot ready timeout\n");
		जाओ out_समयout;
	पूर्ण

	ioग_लिखो32(0, ioaddr + TYPHOON_REG_BOOT_RECORD_ADDR_HI);
	ioग_लिखो32(tp->shared_dma, ioaddr + TYPHOON_REG_BOOT_RECORD_ADDR_LO);
	typhoon_post_pci_ग_लिखोs(ioaddr);
	ioग_लिखो32(TYPHOON_BOOTCMD_REG_BOOT_RECORD,
				ioaddr + TYPHOON_REG_COMMAND);

	अगर (typhoon_रुको_status(ioaddr, TYPHOON_STATUS_RUNNING) < 0) अणु
		netdev_err(tp->dev, "boot finish timeout (status 0x%x)\n",
			   ioपढ़ो32(ioaddr + TYPHOON_REG_STATUS));
		जाओ out_समयout;
	पूर्ण

	/* Clear the Transmit and Command पढ़ोy रेजिस्टरs
	 */
	ioग_लिखो32(0, ioaddr + TYPHOON_REG_TX_HI_READY);
	ioग_लिखो32(0, ioaddr + TYPHOON_REG_CMD_READY);
	ioग_लिखो32(0, ioaddr + TYPHOON_REG_TX_LO_READY);
	typhoon_post_pci_ग_लिखोs(ioaddr);
	ioग_लिखो32(TYPHOON_BOOTCMD_BOOT, ioaddr + TYPHOON_REG_COMMAND);

	वापस 0;

out_समयout:
	वापस -ETIMEDOUT;
पूर्ण

अटल u32
typhoon_clean_tx(काष्ठा typhoon *tp, काष्ठा transmit_ring *txRing,
			अस्थिर __le32 * index)
अणु
	u32 lastRead = txRing->lastRead;
	काष्ठा tx_desc *tx;
	dma_addr_t skb_dma;
	पूर्णांक dma_len;
	पूर्णांक type;

	जबतक (lastRead != le32_to_cpu(*index)) अणु
		tx = (काष्ठा tx_desc *) (txRing->ringBase + lastRead);
		type = tx->flags & TYPHOON_TYPE_MASK;

		अगर (type == TYPHOON_TX_DESC) अणु
			/* This tx_desc describes a packet.
			 */
			अचिन्हित दीर्घ ptr = tx->tx_addr;
			काष्ठा sk_buff *skb = (काष्ठा sk_buff *) ptr;
			dev_kमुक्त_skb_irq(skb);
		पूर्ण अन्यथा अगर (type == TYPHOON_FRAG_DESC) अणु
			/* This tx_desc describes a memory mapping. Free it.
			 */
			skb_dma = (dma_addr_t) le32_to_cpu(tx->frag.addr);
			dma_len = le16_to_cpu(tx->len);
			dma_unmap_single(&tp->pdev->dev, skb_dma, dma_len,
					 DMA_TO_DEVICE);
		पूर्ण

		tx->flags = 0;
		typhoon_inc_tx_index(&lastRead, 1);
	पूर्ण

	वापस lastRead;
पूर्ण

अटल व्योम
typhoon_tx_complete(काष्ठा typhoon *tp, काष्ठा transmit_ring *txRing,
			अस्थिर __le32 * index)
अणु
	u32 lastRead;
	पूर्णांक numDesc = MAX_SKB_FRAGS + 1;

	/* This will need changing अगर we start to use the Hi Tx ring. */
	lastRead = typhoon_clean_tx(tp, txRing, index);
	अगर (netअगर_queue_stopped(tp->dev) && typhoon_num_मुक्त(txRing->lastWrite,
				lastRead, TXLO_ENTRIES) > (numDesc + 2))
		netअगर_wake_queue(tp->dev);

	txRing->lastRead = lastRead;
	smp_wmb();
पूर्ण

अटल व्योम
typhoon_recycle_rx_skb(काष्ठा typhoon *tp, u32 idx)
अणु
	काष्ठा typhoon_indexes *indexes = tp->indexes;
	काष्ठा rxbuff_ent *rxb = &tp->rxbuffers[idx];
	काष्ठा basic_ring *ring = &tp->rxBuffRing;
	काष्ठा rx_मुक्त *r;

	अगर ((ring->lastWrite + माप(*r)) % (RXFREE_ENTRIES * माप(*r)) ==
				le32_to_cpu(indexes->rxBuffCleared)) अणु
		/* no room in ring, just drop the skb
		 */
		dev_kमुक्त_skb_any(rxb->skb);
		rxb->skb = शून्य;
		वापस;
	पूर्ण

	r = (काष्ठा rx_मुक्त *) (ring->ringBase + ring->lastWrite);
	typhoon_inc_rxमुक्त_index(&ring->lastWrite, 1);
	r->virtAddr = idx;
	r->physAddr = cpu_to_le32(rxb->dma_addr);

	/* Tell the card about it */
	wmb();
	indexes->rxBuffReady = cpu_to_le32(ring->lastWrite);
पूर्ण

अटल पूर्णांक
typhoon_alloc_rx_skb(काष्ठा typhoon *tp, u32 idx)
अणु
	काष्ठा typhoon_indexes *indexes = tp->indexes;
	काष्ठा rxbuff_ent *rxb = &tp->rxbuffers[idx];
	काष्ठा basic_ring *ring = &tp->rxBuffRing;
	काष्ठा rx_मुक्त *r;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;

	rxb->skb = शून्य;

	अगर ((ring->lastWrite + माप(*r)) % (RXFREE_ENTRIES * माप(*r)) ==
				le32_to_cpu(indexes->rxBuffCleared))
		वापस -ENOMEM;

	skb = netdev_alloc_skb(tp->dev, PKT_BUF_SZ);
	अगर (!skb)
		वापस -ENOMEM;

#अगर 0
	/* Please, 3com, fix the firmware to allow DMA to a unaligned
	 * address! Pretty please?
	 */
	skb_reserve(skb, 2);
#पूर्ण_अगर

	dma_addr = dma_map_single(&tp->pdev->dev, skb->data, PKT_BUF_SZ,
				  DMA_FROM_DEVICE);

	/* Since no card करोes 64 bit DAC, the high bits will never
	 * change from zero.
	 */
	r = (काष्ठा rx_मुक्त *) (ring->ringBase + ring->lastWrite);
	typhoon_inc_rxमुक्त_index(&ring->lastWrite, 1);
	r->virtAddr = idx;
	r->physAddr = cpu_to_le32(dma_addr);
	rxb->skb = skb;
	rxb->dma_addr = dma_addr;

	/* Tell the card about it */
	wmb();
	indexes->rxBuffReady = cpu_to_le32(ring->lastWrite);
	वापस 0;
पूर्ण

अटल पूर्णांक
typhoon_rx(काष्ठा typhoon *tp, काष्ठा basic_ring *rxRing, अस्थिर __le32 * पढ़ोy,
	   अस्थिर __le32 * cleared, पूर्णांक budget)
अणु
	काष्ठा rx_desc *rx;
	काष्ठा sk_buff *skb, *new_skb;
	काष्ठा rxbuff_ent *rxb;
	dma_addr_t dma_addr;
	u32 local_पढ़ोy;
	u32 rxaddr;
	पूर्णांक pkt_len;
	u32 idx;
	__le32 csum_bits;
	पूर्णांक received;

	received = 0;
	local_पढ़ोy = le32_to_cpu(*पढ़ोy);
	rxaddr = le32_to_cpu(*cleared);
	जबतक (rxaddr != local_पढ़ोy && budget > 0) अणु
		rx = (काष्ठा rx_desc *) (rxRing->ringBase + rxaddr);
		idx = rx->addr;
		rxb = &tp->rxbuffers[idx];
		skb = rxb->skb;
		dma_addr = rxb->dma_addr;

		typhoon_inc_rx_index(&rxaddr, 1);

		अगर (rx->flags & TYPHOON_RX_ERROR) अणु
			typhoon_recycle_rx_skb(tp, idx);
			जारी;
		पूर्ण

		pkt_len = le16_to_cpu(rx->frameLen);

		अगर (pkt_len < rx_copyअवरोध &&
		   (new_skb = netdev_alloc_skb(tp->dev, pkt_len + 2)) != शून्य) अणु
			skb_reserve(new_skb, 2);
			dma_sync_single_क्रम_cpu(&tp->pdev->dev, dma_addr,
						PKT_BUF_SZ, DMA_FROM_DEVICE);
			skb_copy_to_linear_data(new_skb, skb->data, pkt_len);
			dma_sync_single_क्रम_device(&tp->pdev->dev, dma_addr,
						   PKT_BUF_SZ,
						   DMA_FROM_DEVICE);
			skb_put(new_skb, pkt_len);
			typhoon_recycle_rx_skb(tp, idx);
		पूर्ण अन्यथा अणु
			new_skb = skb;
			skb_put(new_skb, pkt_len);
			dma_unmap_single(&tp->pdev->dev, dma_addr, PKT_BUF_SZ,
					 DMA_FROM_DEVICE);
			typhoon_alloc_rx_skb(tp, idx);
		पूर्ण
		new_skb->protocol = eth_type_trans(new_skb, tp->dev);
		csum_bits = rx->rxStatus & (TYPHOON_RX_IP_CHK_GOOD |
			TYPHOON_RX_UDP_CHK_GOOD | TYPHOON_RX_TCP_CHK_GOOD);
		अगर (csum_bits ==
		   (TYPHOON_RX_IP_CHK_GOOD | TYPHOON_RX_TCP_CHK_GOOD) ||
		   csum_bits ==
		   (TYPHOON_RX_IP_CHK_GOOD | TYPHOON_RX_UDP_CHK_GOOD)) अणु
			new_skb->ip_summed = CHECKSUM_UNNECESSARY;
		पूर्ण अन्यथा
			skb_checksum_none_निश्चित(new_skb);

		अगर (rx->rxStatus & TYPHOON_RX_VLAN)
			__vlan_hwaccel_put_tag(new_skb, htons(ETH_P_8021Q),
					       ntohl(rx->vlanTag) & 0xffff);
		netअगर_receive_skb(new_skb);

		received++;
		budget--;
	पूर्ण
	*cleared = cpu_to_le32(rxaddr);

	वापस received;
पूर्ण

अटल व्योम
typhoon_fill_मुक्त_ring(काष्ठा typhoon *tp)
अणु
	u32 i;

	क्रम (i = 0; i < RXENT_ENTRIES; i++) अणु
		काष्ठा rxbuff_ent *rxb = &tp->rxbuffers[i];
		अगर (rxb->skb)
			जारी;
		अगर (typhoon_alloc_rx_skb(tp, i) < 0)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
typhoon_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा typhoon *tp = container_of(napi, काष्ठा typhoon, napi);
	काष्ठा typhoon_indexes *indexes = tp->indexes;
	पूर्णांक work_करोne;

	rmb();
	अगर (!tp->aरुकोing_resp && indexes->respReady != indexes->respCleared)
			typhoon_process_response(tp, 0, शून्य);

	अगर (le32_to_cpu(indexes->txLoCleared) != tp->txLoRing.lastRead)
		typhoon_tx_complete(tp, &tp->txLoRing, &indexes->txLoCleared);

	work_करोne = 0;

	अगर (indexes->rxHiCleared != indexes->rxHiReady) अणु
		work_करोne += typhoon_rx(tp, &tp->rxHiRing, &indexes->rxHiReady,
			   		&indexes->rxHiCleared, budget);
	पूर्ण

	अगर (indexes->rxLoCleared != indexes->rxLoReady) अणु
		work_करोne += typhoon_rx(tp, &tp->rxLoRing, &indexes->rxLoReady,
					&indexes->rxLoCleared, budget - work_करोne);
	पूर्ण

	अगर (le32_to_cpu(indexes->rxBuffCleared) == tp->rxBuffRing.lastWrite) अणु
		/* rxBuff ring is empty, try to fill it. */
		typhoon_fill_मुक्त_ring(tp);
	पूर्ण

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		ioग_लिखो32(TYPHOON_INTR_NONE,
				tp->ioaddr + TYPHOON_REG_INTR_MASK);
		typhoon_post_pci_ग_लिखोs(tp->ioaddr);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल irqवापस_t
typhoon_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा net_device *dev = dev_instance;
	काष्ठा typhoon *tp = netdev_priv(dev);
	व्योम __iomem *ioaddr = tp->ioaddr;
	u32 पूर्णांकr_status;

	पूर्णांकr_status = ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_STATUS);
	अगर (!(पूर्णांकr_status & TYPHOON_INTR_HOST_INT))
		वापस IRQ_NONE;

	ioग_लिखो32(पूर्णांकr_status, ioaddr + TYPHOON_REG_INTR_STATUS);

	अगर (napi_schedule_prep(&tp->napi)) अणु
		ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_MASK);
		typhoon_post_pci_ग_लिखोs(ioaddr);
		__napi_schedule(&tp->napi);
	पूर्ण अन्यथा अणु
		netdev_err(dev, "Error, poll already scheduled\n");
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
typhoon_मुक्त_rx_rings(काष्ठा typhoon *tp)
अणु
	u32 i;

	क्रम (i = 0; i < RXENT_ENTRIES; i++) अणु
		काष्ठा rxbuff_ent *rxb = &tp->rxbuffers[i];
		अगर (rxb->skb) अणु
			dma_unmap_single(&tp->pdev->dev, rxb->dma_addr,
					 PKT_BUF_SZ, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(rxb->skb);
			rxb->skb = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
typhoon_sleep_early(काष्ठा typhoon *tp, __le16 events)
अणु
	व्योम __iomem *ioaddr = tp->ioaddr;
	काष्ठा cmd_desc xp_cmd;
	पूर्णांक err;

	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_ENABLE_WAKE_EVENTS);
	xp_cmd.parm1 = events;
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0) अणु
		netdev_err(tp->dev, "typhoon_sleep(): wake events cmd err %d\n",
			   err);
		वापस err;
	पूर्ण

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_GOTO_SLEEP);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0) अणु
		netdev_err(tp->dev, "typhoon_sleep(): sleep cmd err %d\n", err);
		वापस err;
	पूर्ण

	अगर (typhoon_रुको_status(ioaddr, TYPHOON_STATUS_SLEEPING) < 0)
		वापस -ETIMEDOUT;

	/* Since we cannot monitor the status of the link जबतक sleeping,
	 * tell the world it went away.
	 */
	netअगर_carrier_off(tp->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
typhoon_sleep(काष्ठा typhoon *tp, pci_घातer_t state, __le16 events)
अणु
	पूर्णांक err;

	err = typhoon_sleep_early(tp, events);

	अगर (err)
		वापस err;

	pci_enable_wake(tp->pdev, state, 1);
	pci_disable_device(tp->pdev);
	वापस pci_set_घातer_state(tp->pdev, state);
पूर्ण

अटल पूर्णांक
typhoon_wakeup(काष्ठा typhoon *tp, पूर्णांक रुको_type)
अणु
	व्योम __iomem *ioaddr = tp->ioaddr;

	/* Post 2.x.x versions of the Sleep Image require a reset beक्रमe
	 * we can करोwnload the Runसमय Image. But let's not make users of
	 * the old firmware pay क्रम the reset.
	 */
	ioग_लिखो32(TYPHOON_BOOTCMD_WAKEUP, ioaddr + TYPHOON_REG_COMMAND);
	अगर (typhoon_रुको_status(ioaddr, TYPHOON_STATUS_WAITING_FOR_HOST) < 0 ||
			(tp->capabilities & TYPHOON_WAKEUP_NEEDS_RESET))
		वापस typhoon_reset(ioaddr, रुको_type);

	वापस 0;
पूर्ण

अटल पूर्णांक
typhoon_start_runसमय(काष्ठा typhoon *tp)
अणु
	काष्ठा net_device *dev = tp->dev;
	व्योम __iomem *ioaddr = tp->ioaddr;
	काष्ठा cmd_desc xp_cmd;
	पूर्णांक err;

	typhoon_init_rings(tp);
	typhoon_fill_मुक्त_ring(tp);

	err = typhoon_करोwnload_firmware(tp);
	अगर (err < 0) अणु
		netdev_err(tp->dev, "cannot load runtime on 3XP\n");
		जाओ error_out;
	पूर्ण

	अगर (typhoon_boot_3XP(tp, TYPHOON_STATUS_WAITING_FOR_BOOT) < 0) अणु
		netdev_err(tp->dev, "cannot boot 3XP\n");
		err = -EIO;
		जाओ error_out;
	पूर्ण

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_SET_MAX_PKT_SIZE);
	xp_cmd.parm1 = cpu_to_le16(PKT_BUF_SZ);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_SET_MAC_ADDRESS);
	xp_cmd.parm1 = cpu_to_le16(ntohs(*(__be16 *)&dev->dev_addr[0]));
	xp_cmd.parm2 = cpu_to_le32(ntohl(*(__be32 *)&dev->dev_addr[2]));
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	/* Disable IRQ coalescing -- we can reenable it when 3Com gives
	 * us some more inक्रमmation on how to control it.
	 */
	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_IRQ_COALESCE_CTRL);
	xp_cmd.parm1 = 0;
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_XCVR_SELECT);
	xp_cmd.parm1 = tp->xcvr_select;
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_VLAN_TYPE_WRITE);
	xp_cmd.parm1 = cpu_to_le16(ETH_P_8021Q);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_SET_OFFLOAD_TASKS);
	xp_cmd.parm2 = tp->offload;
	xp_cmd.parm3 = tp->offload;
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	typhoon_set_rx_mode(dev);

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_TX_ENABLE);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_RX_ENABLE);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);
	अगर (err < 0)
		जाओ error_out;

	tp->card_state = Running;
	smp_wmb();

	ioग_लिखो32(TYPHOON_INTR_ENABLE_ALL, ioaddr + TYPHOON_REG_INTR_ENABLE);
	ioग_लिखो32(TYPHOON_INTR_NONE, ioaddr + TYPHOON_REG_INTR_MASK);
	typhoon_post_pci_ग_लिखोs(ioaddr);

	वापस 0;

error_out:
	typhoon_reset(ioaddr, WaitNoSleep);
	typhoon_मुक्त_rx_rings(tp);
	typhoon_init_rings(tp);
	वापस err;
पूर्ण

अटल पूर्णांक
typhoon_stop_runसमय(काष्ठा typhoon *tp, पूर्णांक रुको_type)
अणु
	काष्ठा typhoon_indexes *indexes = tp->indexes;
	काष्ठा transmit_ring *txLo = &tp->txLoRing;
	व्योम __iomem *ioaddr = tp->ioaddr;
	काष्ठा cmd_desc xp_cmd;
	पूर्णांक i;

	/* Disable पूर्णांकerrupts early, since we can't schedule a poll
	 * when called with !netअगर_running(). This will be posted
	 * when we क्रमce the posting of the command.
	 */
	ioग_लिखो32(TYPHOON_INTR_NONE, ioaddr + TYPHOON_REG_INTR_ENABLE);

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_RX_DISABLE);
	typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);

	/* Wait 1/2 sec क्रम any outstanding transmits to occur
	 * We'll cleanup after the reset अगर this बार out.
	 */
	क्रम (i = 0; i < TYPHOON_WAIT_TIMEOUT; i++) अणु
		अगर (indexes->txLoCleared == cpu_to_le32(txLo->lastWrite))
			अवरोध;
		udelay(TYPHOON_UDELAY);
	पूर्ण

	अगर (i == TYPHOON_WAIT_TIMEOUT)
		netdev_err(tp->dev, "halt timed out waiting for Tx to complete\n");

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_TX_DISABLE);
	typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);

	/* save the statistics so when we bring the पूर्णांकerface up again,
	 * the values reported to userspace are correct.
	 */
	tp->card_state = Sleeping;
	smp_wmb();
	typhoon_करो_get_stats(tp);
	स_नकल(&tp->stats_saved, &tp->dev->stats, माप(काष्ठा net_device_stats));

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_HALT);
	typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य);

	अगर (typhoon_रुको_status(ioaddr, TYPHOON_STATUS_HALTED) < 0)
		netdev_err(tp->dev, "timed out waiting for 3XP to halt\n");

	अगर (typhoon_reset(ioaddr, रुको_type) < 0) अणु
		netdev_err(tp->dev, "unable to reset 3XP\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* cleanup any outstanding Tx packets */
	अगर (indexes->txLoCleared != cpu_to_le32(txLo->lastWrite)) अणु
		indexes->txLoCleared = cpu_to_le32(txLo->lastWrite);
		typhoon_clean_tx(tp, &tp->txLoRing, &indexes->txLoCleared);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
typhoon_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);

	अगर (typhoon_reset(tp->ioaddr, WaitNoSleep) < 0) अणु
		netdev_warn(dev, "could not reset in tx timeout\n");
		जाओ truly_dead;
	पूर्ण

	/* If we ever start using the Hi ring, it will need cleaning too */
	typhoon_clean_tx(tp, &tp->txLoRing, &tp->indexes->txLoCleared);
	typhoon_मुक्त_rx_rings(tp);

	अगर (typhoon_start_runसमय(tp) < 0) अणु
		netdev_err(dev, "could not start runtime in tx timeout\n");
		जाओ truly_dead;
        पूर्ण

	netअगर_wake_queue(dev);
	वापस;

truly_dead:
	/* Reset the hardware, and turn off carrier to aव्योम more समयouts */
	typhoon_reset(tp->ioaddr, NoWait);
	netअगर_carrier_off(dev);
पूर्ण

अटल पूर्णांक
typhoon_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);
	पूर्णांक err;

	err = typhoon_request_firmware(tp);
	अगर (err)
		जाओ out;

	pci_set_घातer_state(tp->pdev, PCI_D0);
	pci_restore_state(tp->pdev);

	err = typhoon_wakeup(tp, WaitSleep);
	अगर (err < 0) अणु
		netdev_err(dev, "unable to wakeup device\n");
		जाओ out_sleep;
	पूर्ण

	err = request_irq(dev->irq, typhoon_पूर्णांकerrupt, IRQF_SHARED,
				dev->name, dev);
	अगर (err < 0)
		जाओ out_sleep;

	napi_enable(&tp->napi);

	err = typhoon_start_runसमय(tp);
	अगर (err < 0) अणु
		napi_disable(&tp->napi);
		जाओ out_irq;
	पूर्ण

	netअगर_start_queue(dev);
	वापस 0;

out_irq:
	मुक्त_irq(dev->irq, dev);

out_sleep:
	अगर (typhoon_boot_3XP(tp, TYPHOON_STATUS_WAITING_FOR_HOST) < 0) अणु
		netdev_err(dev, "unable to reboot into sleep img\n");
		typhoon_reset(tp->ioaddr, NoWait);
		जाओ out;
	पूर्ण

	अगर (typhoon_sleep(tp, PCI_D3hot, 0) < 0)
		netdev_err(dev, "unable to go back to sleep\n");

out:
	वापस err;
पूर्ण

अटल पूर्णांक
typhoon_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा typhoon *tp = netdev_priv(dev);

	netअगर_stop_queue(dev);
	napi_disable(&tp->napi);

	अगर (typhoon_stop_runसमय(tp, WaitSleep) < 0)
		netdev_err(dev, "unable to stop runtime\n");

	/* Make sure there is no irq handler running on a dअगरferent CPU. */
	मुक्त_irq(dev->irq, dev);

	typhoon_मुक्त_rx_rings(tp);
	typhoon_init_rings(tp);

	अगर (typhoon_boot_3XP(tp, TYPHOON_STATUS_WAITING_FOR_HOST) < 0)
		netdev_err(dev, "unable to boot sleep image\n");

	अगर (typhoon_sleep(tp, PCI_D3hot, 0) < 0)
		netdev_err(dev, "unable to put card to sleep\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused
typhoon_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा typhoon *tp = netdev_priv(dev);

	/* If we're करोwn, resume when we are upped.
	 */
	अगर (!netअगर_running(dev))
		वापस 0;

	अगर (typhoon_wakeup(tp, WaitNoSleep) < 0) अणु
		netdev_err(dev, "critical: could not wake up in resume\n");
		जाओ reset;
	पूर्ण

	अगर (typhoon_start_runसमय(tp) < 0) अणु
		netdev_err(dev, "critical: could not start runtime in resume\n");
		जाओ reset;
	पूर्ण

	netअगर_device_attach(dev);
	वापस 0;

reset:
	typhoon_reset(tp->ioaddr, NoWait);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक __maybe_unused
typhoon_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा typhoon *tp = netdev_priv(dev);
	काष्ठा cmd_desc xp_cmd;

	/* If we're down, we're alपढ़ोy suspended.
	 */
	अगर (!netअगर_running(dev))
		वापस 0;

	/* TYPHOON_OFFLOAD_VLAN is always on now, so this करोesn't work */
	अगर (tp->wol_events & TYPHOON_WAKE_MAGIC_PKT)
		netdev_warn(dev, "cannot do WAKE_MAGIC with VLAN offloading\n");

	netअगर_device_detach(dev);

	अगर (typhoon_stop_runसमय(tp, WaitNoSleep) < 0) अणु
		netdev_err(dev, "unable to stop runtime\n");
		जाओ need_resume;
	पूर्ण

	typhoon_मुक्त_rx_rings(tp);
	typhoon_init_rings(tp);

	अगर (typhoon_boot_3XP(tp, TYPHOON_STATUS_WAITING_FOR_HOST) < 0) अणु
		netdev_err(dev, "unable to boot sleep image\n");
		जाओ need_resume;
	पूर्ण

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_SET_MAC_ADDRESS);
	xp_cmd.parm1 = cpu_to_le16(ntohs(*(__be16 *)&dev->dev_addr[0]));
	xp_cmd.parm2 = cpu_to_le32(ntohl(*(__be32 *)&dev->dev_addr[2]));
	अगर (typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य) < 0) अणु
		netdev_err(dev, "unable to set mac address in suspend\n");
		जाओ need_resume;
	पूर्ण

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_SET_RX_FILTER);
	xp_cmd.parm1 = TYPHOON_RX_FILTER_सूचीECTED | TYPHOON_RX_FILTER_BROADCAST;
	अगर (typhoon_issue_command(tp, 1, &xp_cmd, 0, शून्य) < 0) अणु
		netdev_err(dev, "unable to set rx filter in suspend\n");
		जाओ need_resume;
	पूर्ण

	अगर (typhoon_sleep_early(tp, tp->wol_events) < 0) अणु
		netdev_err(dev, "unable to put card to sleep\n");
		जाओ need_resume;
	पूर्ण

	device_wakeup_enable(dev_d);

	वापस 0;

need_resume:
	typhoon_resume(dev_d);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक
typhoon_test_mmio(काष्ठा pci_dev *pdev)
अणु
	व्योम __iomem *ioaddr = pci_iomap(pdev, 1, 128);
	पूर्णांक mode = 0;
	u32 val;

	अगर (!ioaddr)
		जाओ out;

	अगर (ioपढ़ो32(ioaddr + TYPHOON_REG_STATUS) !=
				TYPHOON_STATUS_WAITING_FOR_HOST)
		जाओ out_unmap;

	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_MASK);
	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_STATUS);
	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_ENABLE);

	/* Ok, see अगर we can change our पूर्णांकerrupt status रेजिस्टर by
	 * sending ourselves an पूर्णांकerrupt. If so, then MMIO works.
	 * The 50usec delay is arbitrary -- it could probably be smaller.
	 */
	val = ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_STATUS);
	अगर ((val & TYPHOON_INTR_SELF) == 0) अणु
		ioग_लिखो32(1, ioaddr + TYPHOON_REG_SELF_INTERRUPT);
		ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_STATUS);
		udelay(50);
		val = ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_STATUS);
		अगर (val & TYPHOON_INTR_SELF)
			mode = 1;
	पूर्ण

	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_MASK);
	ioग_लिखो32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_STATUS);
	ioग_लिखो32(TYPHOON_INTR_NONE, ioaddr + TYPHOON_REG_INTR_ENABLE);
	ioपढ़ो32(ioaddr + TYPHOON_REG_INTR_STATUS);

out_unmap:
	pci_iounmap(pdev, ioaddr);

out:
	अगर (!mode)
		pr_info("%s: falling back to port IO\n", pci_name(pdev));
	वापस mode;
पूर्ण

अटल स्थिर काष्ठा net_device_ops typhoon_netdev_ops = अणु
	.nकरो_खोलो		= typhoon_खोलो,
	.nकरो_stop		= typhoon_बंद,
	.nकरो_start_xmit		= typhoon_start_tx,
	.nकरो_set_rx_mode	= typhoon_set_rx_mode,
	.nकरो_tx_समयout		= typhoon_tx_समयout,
	.nकरो_get_stats		= typhoon_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक
typhoon_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा typhoon *tp;
	पूर्णांक card_id = (पूर्णांक) ent->driver_data;
	व्योम __iomem *ioaddr;
	व्योम *shared;
	dma_addr_t shared_dma;
	काष्ठा cmd_desc xp_cmd;
	काष्ठा resp_desc xp_resp[3];
	पूर्णांक err = 0;
	स्थिर अक्षर *err_msg;

	dev = alloc_etherdev(माप(*tp));
	अगर (dev == शून्य) अणु
		err_msg = "unable to alloc new net device";
		err = -ENOMEM;
		जाओ error_out;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);

	err = pci_enable_device(pdev);
	अगर (err < 0) अणु
		err_msg = "unable to enable device";
		जाओ error_out_dev;
	पूर्ण

	err = pci_set_mwi(pdev);
	अगर (err < 0) अणु
		err_msg = "unable to set MWI";
		जाओ error_out_disable;
	पूर्ण

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err < 0) अणु
		err_msg = "No usable DMA configuration";
		जाओ error_out_mwi;
	पूर्ण

	/* sanity checks on IO and MMIO BARs
	 */
	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_IO)) अणु
		err_msg = "region #1 not a PCI IO resource, aborting";
		err = -ENODEV;
		जाओ error_out_mwi;
	पूर्ण
	अगर (pci_resource_len(pdev, 0) < 128) अणु
		err_msg = "Invalid PCI IO region size, aborting";
		err = -ENODEV;
		जाओ error_out_mwi;
	पूर्ण
	अगर (!(pci_resource_flags(pdev, 1) & IORESOURCE_MEM)) अणु
		err_msg = "region #1 not a PCI MMIO resource, aborting";
		err = -ENODEV;
		जाओ error_out_mwi;
	पूर्ण
	अगर (pci_resource_len(pdev, 1) < 128) अणु
		err_msg = "Invalid PCI MMIO region size, aborting";
		err = -ENODEV;
		जाओ error_out_mwi;
	पूर्ण

	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err < 0) अणु
		err_msg = "could not request regions";
		जाओ error_out_mwi;
	पूर्ण

	/* map our रेजिस्टरs
	 */
	अगर (use_mmio != 0 && use_mmio != 1)
		use_mmio = typhoon_test_mmio(pdev);

	ioaddr = pci_iomap(pdev, use_mmio, 128);
	अगर (!ioaddr) अणु
		err_msg = "cannot remap registers, aborting";
		err = -EIO;
		जाओ error_out_regions;
	पूर्ण

	/* allocate pci dma space क्रम rx and tx descriptor rings
	 */
	shared = dma_alloc_coherent(&pdev->dev, माप(काष्ठा typhoon_shared),
				    &shared_dma, GFP_KERNEL);
	अगर (!shared) अणु
		err_msg = "could not allocate DMA memory";
		err = -ENOMEM;
		जाओ error_out_remap;
	पूर्ण

	dev->irq = pdev->irq;
	tp = netdev_priv(dev);
	tp->shared = shared;
	tp->shared_dma = shared_dma;
	tp->pdev = pdev;
	tp->tx_pdev = pdev;
	tp->ioaddr = ioaddr;
	tp->tx_ioaddr = ioaddr;
	tp->dev = dev;

	/* Init sequence:
	 * 1) Reset the adapter to clear any bad juju
	 * 2) Reload the sleep image
	 * 3) Boot the sleep image
	 * 4) Get the hardware address.
	 * 5) Put the card to sleep.
	 */
	err = typhoon_reset(ioaddr, WaitSleep);
	अगर (err < 0) अणु
		err_msg = "could not reset 3XP";
		जाओ error_out_dma;
	पूर्ण

	/* Now that we've reset the 3XP and are sure it's not going to
	 * ग_लिखो all over memory, enable bus mastering, and save our
	 * state क्रम resuming after a suspend.
	 */
	pci_set_master(pdev);
	pci_save_state(pdev);

	typhoon_init_पूर्णांकerface(tp);
	typhoon_init_rings(tp);

	err = typhoon_boot_3XP(tp, TYPHOON_STATUS_WAITING_FOR_HOST);
	अगर (err < 0) अणु
		err_msg = "cannot boot 3XP sleep image";
		जाओ error_out_reset;
	पूर्ण

	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_READ_MAC_ADDRESS);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 1, xp_resp);
	अगर (err < 0) अणु
		err_msg = "cannot read MAC address";
		जाओ error_out_reset;
	पूर्ण

	*(__be16 *)&dev->dev_addr[0] = htons(le16_to_cpu(xp_resp[0].parm1));
	*(__be32 *)&dev->dev_addr[2] = htonl(le32_to_cpu(xp_resp[0].parm2));

	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		err_msg = "Could not obtain valid ethernet address, aborting";
		err = -EIO;
		जाओ error_out_reset;
	पूर्ण

	/* Read the Sleep Image version last, so the response is valid
	 * later when we prपूर्णांक out the version reported.
	 */
	INIT_COMMAND_WITH_RESPONSE(&xp_cmd, TYPHOON_CMD_READ_VERSIONS);
	err = typhoon_issue_command(tp, 1, &xp_cmd, 3, xp_resp);
	अगर (err < 0) अणु
		err_msg = "Could not get Sleep Image version";
		जाओ error_out_reset;
	पूर्ण

	tp->capabilities = typhoon_card_info[card_id].capabilities;
	tp->xcvr_select = TYPHOON_XCVR_AUTONEG;

	/* Typhoon 1.0 Sleep Images वापस one response descriptor to the
	 * READ_VERSIONS command. Those versions are OK after waking up
	 * from sleep without needing a reset. Typhoon 1.1+ Sleep Images
	 * seem to need a little extra help to get started. Since we करोn't
	 * know how to nudge it aदीर्घ, just kick it.
	 */
	अगर (xp_resp[0].numDesc != 0)
		tp->capabilities |= TYPHOON_WAKEUP_NEEDS_RESET;

	err = typhoon_sleep(tp, PCI_D3hot, 0);
	अगर (err < 0) अणु
		err_msg = "cannot put adapter to sleep";
		जाओ error_out_reset;
	पूर्ण

	/* The chip-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops		= &typhoon_netdev_ops;
	netअगर_napi_add(dev, &tp->napi, typhoon_poll, 16);
	dev->watchकरोg_समयo	= TX_TIMEOUT;

	dev->ethtool_ops = &typhoon_ethtool_ops;

	/* We can handle scatter gather, up to 16 entries, and
	 * we can करो IP checksumming (only version 4, करोh...)
	 *
	 * There's no way to turn off the RX VLAN offloading and stripping
	 * on the current 3XP firmware -- it करोes not respect the offload
	 * settings -- so we only allow the user to toggle the TX processing.
	 */
	dev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
		NETIF_F_HW_VLAN_CTAG_TX;
	dev->features = dev->hw_features |
		NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_RXCSUM;

	err = रेजिस्टर_netdev(dev);
	अगर (err < 0) अणु
		err_msg = "unable to register netdev";
		जाओ error_out_reset;
	पूर्ण

	pci_set_drvdata(pdev, dev);

	netdev_info(dev, "%s at %s 0x%llx, %pM\n",
		    typhoon_card_info[card_id].name,
		    use_mmio ? "MMIO" : "IO",
		    (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, use_mmio),
		    dev->dev_addr);

	/* xp_resp still contains the response to the READ_VERSIONS command.
	 * For debugging, let the user know what version he has.
	 */
	अगर (xp_resp[0].numDesc == 0) अणु
		/* This is the Typhoon 1.0 type Sleep Image, last 16 bits
		 * of version is Month/Day of build.
		 */
		u16 monthday = le32_to_cpu(xp_resp[0].parm2) & 0xffff;
		netdev_info(dev, "Typhoon 1.0 Sleep Image built %02u/%02u/2000\n",
			    monthday >> 8, monthday & 0xff);
	पूर्ण अन्यथा अगर (xp_resp[0].numDesc == 2) अणु
		/* This is the Typhoon 1.1+ type Sleep Image
		 */
		u32 sleep_ver = le32_to_cpu(xp_resp[0].parm2);
		u8 *ver_string = (u8 *) &xp_resp[1];
		ver_string[25] = 0;
		netdev_info(dev, "Typhoon 1.1+ Sleep Image version %02x.%03x.%03x %s\n",
			    sleep_ver >> 24, (sleep_ver >> 12) & 0xfff,
			    sleep_ver & 0xfff, ver_string);
	पूर्ण अन्यथा अणु
		netdev_warn(dev, "Unknown Sleep Image version (%u:%04x)\n",
			    xp_resp[0].numDesc, le32_to_cpu(xp_resp[0].parm2));
	पूर्ण

	वापस 0;

error_out_reset:
	typhoon_reset(ioaddr, NoWait);

error_out_dma:
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा typhoon_shared), shared,
			  shared_dma);
error_out_remap:
	pci_iounmap(pdev, ioaddr);
error_out_regions:
	pci_release_regions(pdev);
error_out_mwi:
	pci_clear_mwi(pdev);
error_out_disable:
	pci_disable_device(pdev);
error_out_dev:
	मुक्त_netdev(dev);
error_out:
	pr_err("%s: %s\n", pci_name(pdev), err_msg);
	वापस err;
पूर्ण

अटल व्योम
typhoon_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा typhoon *tp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	typhoon_reset(tp->ioaddr, NoWait);
	pci_iounmap(pdev, tp->ioaddr);
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा typhoon_shared),
			  tp->shared, tp->shared_dma);
	pci_release_regions(pdev);
	pci_clear_mwi(pdev);
	pci_disable_device(pdev);
	मुक्त_netdev(dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(typhoon_pm_ops, typhoon_suspend, typhoon_resume);

अटल काष्ठा pci_driver typhoon_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= typhoon_pci_tbl,
	.probe		= typhoon_init_one,
	.हटाओ		= typhoon_हटाओ_one,
	.driver.pm	= &typhoon_pm_ops,
पूर्ण;

अटल पूर्णांक __init
typhoon_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&typhoon_driver);
पूर्ण

अटल व्योम __निकास
typhoon_cleanup(व्योम)
अणु
	release_firmware(typhoon_fw);
	pci_unरेजिस्टर_driver(&typhoon_driver);
पूर्ण

module_init(typhoon_init);
module_निकास(typhoon_cleanup);
