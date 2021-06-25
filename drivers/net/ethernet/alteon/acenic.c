<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * acenic.c: Linux driver क्रम the Alteon AceNIC Gigabit Ethernet card
 *           and other Tigon based cards.
 *
 * Copyright 1998-2002 by Jes Sorensen, <jes@trained-monkey.org>.
 *
 * Thanks to Alteon and 3Com क्रम providing hardware and करोcumentation
 * enabling me to ग_लिखो this driver.
 *
 * A mailing list क्रम discussing the use of this driver has been
 * setup, please subscribe to the lists अगर you have any questions
 * about the driver. Send mail to linux-acenic-help@sunsite.auc.dk to
 * see how to subscribe.
 *
 * Additional credits:
 *   Pete Wyckoff <wyckoff@ca.sandia.gov>: Initial Linux/Alpha and trace
 *       dump support. The trace dump support has not been
 *       पूर्णांकegrated yet however.
 *   Troy Benjegerdes: Big Endian (PPC) patches.
 *   Nate Stahl: Better out of memory handling and stats support.
 *   Aman Singla: Nasty race between पूर्णांकerrupt handler and tx code dealing
 *                with 'testing the tx_ret_csm and setting tx_full'
 *   David S. Miller <davem@redhat.com>: conversion to new PCI dma mapping
 *                                       infraकाष्ठाure and Sparc support
 *   Pierrick Pinasseau (CERN): For lending me an Ultra 5 to test the
 *                              driver under Linux/Sparc64
 *   Matt Domsch <Matt_Domsch@dell.com>: Detect Alteon 1000baseT cards
 *                                       ETHTOOL_GDRVINFO support
 *   Chip Salzenberg <chip@valinux.com>: Fix race condition between tx
 *                                       handler and बंद() cleanup.
 *   Ken Aaker <kdaaker@rchland.vnet.ibm.com>: Correct check क्रम whether
 *                                       memory mapped IO is enabled to
 *                                       make the driver work on RS/6000.
 *   Takayoshi Kouchi <kouchi@hpc.bs1.fc.nec.co.jp>: Identअगरying problem
 *                                       where the driver would disable
 *                                       bus master mode अगर it had to disable
 *                                       ग_लिखो and invalidate.
 *   Stephen Hack <stephen_hack@hp.com>: Fixed ace_set_mac_addr क्रम little
 *                                       endian प्रणालीs.
 *   Val Henson <vhenson@esscom.com>:    Reset Jumbo skb producer and
 *                                       rx producer index when
 *                                       flushing the Jumbo ring.
 *   Hans Grobler <grobh@sun.ac.za>:     Memory leak fixes in the
 *                                       driver init path.
 *   Grant Grundler <grundler@cup.hp.com>: PCI ग_लिखो posting fixes.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sockios.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/अगर_vlan.h>

#अगर_घोषित SIOCETHTOOL
#समावेश <linux/ethtool.h>
#पूर्ण_अगर

#समावेश <net/sock.h>
#समावेश <net/ip.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>


#घोषणा DRV_NAME "acenic"

#अघोषित INDEX_DEBUG

#अगर_घोषित CONFIG_ACENIC_OMIT_TIGON_I
#घोषणा ACE_IS_TIGON_I(ap)	0
#घोषणा ACE_TX_RING_ENTRIES(ap)	MAX_TX_RING_ENTRIES
#अन्यथा
#घोषणा ACE_IS_TIGON_I(ap)	(ap->version == 1)
#घोषणा ACE_TX_RING_ENTRIES(ap)	ap->tx_ring_entries
#पूर्ण_अगर

#अगर_अघोषित PCI_VENDOR_ID_ALTEON
#घोषणा PCI_VENDOR_ID_ALTEON		0x12ae
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_ALTEON_ACENIC_FIBRE
#घोषणा PCI_DEVICE_ID_ALTEON_ACENIC_FIBRE  0x0001
#घोषणा PCI_DEVICE_ID_ALTEON_ACENIC_COPPER 0x0002
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_3COM_3C985
#घोषणा PCI_DEVICE_ID_3COM_3C985	0x0001
#पूर्ण_अगर
#अगर_अघोषित PCI_VENDOR_ID_NETGEAR
#घोषणा PCI_VENDOR_ID_NETGEAR		0x1385
#घोषणा PCI_DEVICE_ID_NETGEAR_GA620	0x620a
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_NETGEAR_GA620T
#घोषणा PCI_DEVICE_ID_NETGEAR_GA620T	0x630a
#पूर्ण_अगर


/*
 * Farallon used the DEC venकरोr ID by mistake and they seem not
 * to care - stinky!
 */
#अगर_अघोषित PCI_DEVICE_ID_FARALLON_PN9000SX
#घोषणा PCI_DEVICE_ID_FARALLON_PN9000SX	0x1a
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_FARALLON_PN9100T
#घोषणा PCI_DEVICE_ID_FARALLON_PN9100T  0xfa
#पूर्ण_अगर
#अगर_अघोषित PCI_VENDOR_ID_SGI
#घोषणा PCI_VENDOR_ID_SGI		0x10a9
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_SGI_ACENIC
#घोषणा PCI_DEVICE_ID_SGI_ACENIC	0x0009
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id acenic_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_ALTEON, PCI_DEVICE_ID_ALTEON_ACENIC_FIBRE,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	अणु PCI_VENDOR_ID_ALTEON, PCI_DEVICE_ID_ALTEON_ACENIC_COPPER,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	अणु PCI_VENDOR_ID_3COM, PCI_DEVICE_ID_3COM_3C985,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	अणु PCI_VENDOR_ID_NETGEAR, PCI_DEVICE_ID_NETGEAR_GA620,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	अणु PCI_VENDOR_ID_NETGEAR, PCI_DEVICE_ID_NETGEAR_GA620T,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	/*
	 * Farallon used the DEC venकरोr ID on their cards incorrectly,
	 * then later Alteon's ID.
	 */
	अणु PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_FARALLON_PN9000SX,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	अणु PCI_VENDOR_ID_ALTEON, PCI_DEVICE_ID_FARALLON_PN9100T,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	अणु PCI_VENDOR_ID_SGI, PCI_DEVICE_ID_SGI_ACENIC,
	  PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_NETWORK_ETHERNET << 8, 0xffff00, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, acenic_pci_tbl);

#घोषणा ace_sync_irq(irq)	synchronize_irq(irq)

#अगर_अघोषित offset_in_page
#घोषणा offset_in_page(ptr)	((अचिन्हित दीर्घ)(ptr) & ~PAGE_MASK)
#पूर्ण_अगर

#घोषणा ACE_MAX_MOD_PARMS	8
#घोषणा BOARD_IDX_STATIC	0
#घोषणा BOARD_IDX_OVERFLOW	-1

#समावेश "acenic.h"

/*
 * These must be defined beक्रमe the firmware is included.
 */
#घोषणा MAX_TEXT_LEN	96*1024
#घोषणा MAX_RODATA_LEN	8*1024
#घोषणा MAX_DATA_LEN	2*1024

#अगर_अघोषित tigon2FwReleaseLocal
#घोषणा tigon2FwReleaseLocal 0
#पूर्ण_अगर

/*
 * This driver currently supports Tigon I and Tigon II based cards
 * including the Alteon AceNIC, the 3Com 3C985[B] and NetGear
 * GA620. The driver should also work on the SGI, DEC and Farallon
 * versions of the card, however I have not been able to test that
 * myself.
 *
 * This card is really neat, it supports receive hardware checksumming
 * and jumbo frames (up to 9000 bytes) and करोes a lot of work in the
 * firmware. Also the programming पूर्णांकerface is quite neat, except क्रम
 * the parts dealing with the i2c eeprom on the card ;-)
 *
 * Using jumbo frames:
 *
 * To enable jumbo frames, simply specअगरy an mtu between 1500 and 9000
 * bytes to अगरconfig. Jumbo frames can be enabled or disabled at any समय
 * by running `अगरconfig eth<X> mtu <MTU>' with <X> being the Ethernet
 * पूर्णांकerface number and <MTU> being the MTU value.
 *
 * Module parameters:
 *
 * When compiled as a loadable module, the driver allows क्रम a number
 * of module parameters to be specअगरied. The driver supports the
 * following module parameters:
 *
 *  trace=<val> - Firmware trace level. This requires special traced
 *                firmware to replace the firmware supplied with
 *                the driver - क्रम debugging purposes only.
 *
 *  link=<val>  - Link state. Normally you want to use the शेष link
 *                parameters set by the driver. This can be used to
 *                override these in हाल your चयन करोesn't negotiate
 *                the link properly. Valid values are:
 *         0x0001 - Force half duplex link.
 *         0x0002 - Do not negotiate line speed with the other end.
 *         0x0010 - 10Mbit/sec link.
 *         0x0020 - 100Mbit/sec link.
 *         0x0040 - 1000Mbit/sec link.
 *         0x0100 - Do not negotiate flow control.
 *         0x0200 - Enable RX flow control Y
 *         0x0400 - Enable TX flow control Y (Tigon II NICs only).
 *                Default value is 0x0270, ie. enable link+flow
 *                control negotiation. Negotiating the highest
 *                possible link speed with RX flow control enabled.
 *
 *                When disabling link speed negotiation, only one link
 *                speed is allowed to be specअगरied!
 *
 *  tx_coal_tick=<val> - number of coalescing घड़ी ticks (us) allowed
 *                to रुको क्रम more packets to arive beक्रमe
 *                पूर्णांकerrupting the host, from the समय the first
 *                packet arrives.
 *
 *  rx_coal_tick=<val> - number of coalescing घड़ी ticks (us) allowed
 *                to रुको क्रम more packets to arive in the transmit ring,
 *                beक्रमe पूर्णांकerrupting the host, after transmitting the
 *                first packet in the ring.
 *
 *  max_tx_desc=<val> - maximum number of transmit descriptors
 *                (packets) transmitted beक्रमe पूर्णांकerrupting the host.
 *
 *  max_rx_desc=<val> - maximum number of receive descriptors
 *                (packets) received beक्रमe पूर्णांकerrupting the host.
 *
 *  tx_ratio=<val> - 7 bit value (0 - 63) specअगरying the split in 64th
 *                increments of the NIC's on board memory to be used क्रम
 *                transmit and receive buffers. For the 1MB NIC app. 800KB
 *                is available, on the 1/2MB NIC app. 300KB is available.
 *                68KB will always be available as a minimum क्रम both
 *                directions. The शेष value is a 50/50 split.
 *  dis_pci_mem_inval=<val> - disable PCI memory ग_लिखो and invalidate
 *                operations, शेष (1) is to always disable this as
 *                that is what Alteon करोes on NT. I have not been able
 *                to measure any real perक्रमmance dअगरferences with
 *                this on my प्रणालीs. Set <val>=0 अगर you want to
 *                enable these operations.
 *
 * If you use more than one NIC, specअगरy the parameters क्रम the
 * inभागidual NICs with a comma, ie. trace=0,0x00001fff,0 you want to
 * run tracing on NIC #2 but not on NIC #1 and #3.
 *
 * TODO:
 *
 * - Proper multicast support.
 * - NIC dump support.
 * - More tuning parameters.
 *
 * The mini ring is not used under Linux and I am not sure it makes sense
 * to actually use it.
 *
 * New पूर्णांकerrupt handler strategy:
 *
 * The old पूर्णांकerrupt handler worked using the traditional method of
 * replacing an skbuff with a new one when a packet arrives. However
 * the rx rings करो not need to contain a अटल number of buffer
 * descriptors, thus it makes sense to move the memory allocation out
 * of the मुख्य पूर्णांकerrupt handler and करो it in a bottom half handler
 * and only allocate new buffers when the number of buffers in the
 * ring is below a certain threshold. In order to aव्योम starving the
 * NIC under heavy load it is however necessary to क्रमce allocation
 * when hitting a minimum threshold. The strategy क्रम alloction is as
 * follows:
 *
 *     RX_LOW_BUF_THRES    - allocate buffers in the bottom half
 *     RX_PANIC_LOW_THRES  - we are very low on buffers, allocate
 *                           the buffers in the पूर्णांकerrupt handler
 *     RX_RING_THRES       - maximum number of buffers in the rx ring
 *     RX_MINI_THRES       - maximum number of buffers in the mini ring
 *     RX_JUMBO_THRES      - maximum number of buffers in the jumbo ring
 *
 * One advantagous side effect of this allocation approach is that the
 * entire rx processing can be करोne without holding any spin lock
 * since the rx rings and रेजिस्टरs are totally independent of the tx
 * ring and its रेजिस्टरs.  This of course includes the kदो_स्मृति's of
 * new skb's. Thus start_xmit can run in parallel with rx processing
 * and the memory allocation on SMP प्रणालीs.
 *
 * Note that running the skb पुनः_स्मृतिation in a bottom half खोलोs up
 * another can of races which needs to be handled properly. In
 * particular it can happen that the पूर्णांकerrupt handler tries to run
 * the पुनः_स्मृतिation जबतक the bottom half is either running on another
 * CPU or was पूर्णांकerrupted on the same CPU. To get around this the
 * driver uses bitops to prevent the पुनः_स्मृतिation routines from being
 * reentered.
 *
 * TX handling can also be करोne without holding any spin lock, wheee
 * this is fun! since tx_ret_csm is only written to by the पूर्णांकerrupt
 * handler. The हाल to be aware of is when shutting करोwn the device
 * and cleaning up where it is necessary to make sure that
 * start_xmit() is not running जबतक this is happening. Well DaveM
 * inक्रमms me that this हाल is alपढ़ोy रक्षित against ... bye bye
 * Mr. Spin Lock, it was nice to know you.
 *
 * TX पूर्णांकerrupts are now partly disabled so the NIC will only generate
 * TX पूर्णांकerrupts क्रम the number of coal ticks, not क्रम the number of
 * TX packets in the queue. This should reduce the number of TX only,
 * ie. when no RX processing is करोne, पूर्णांकerrupts seen.
 */

/*
 * Threshold values क्रम RX buffer allocation - the low water marks क्रम
 * when to start refilling the rings are set to 75% of the ring
 * sizes. It seems to make sense to refill the rings entirely from the
 * पूर्णांकrrupt handler once it माला_लो below the panic threshold, that way
 * we करोn't risk that the refilling is moved to another CPU when the
 * one running the पूर्णांकerrupt handler just got the slab code hot in its
 * cache.
 */
#घोषणा RX_RING_SIZE		72
#घोषणा RX_MINI_SIZE		64
#घोषणा RX_JUMBO_SIZE		48

#घोषणा RX_PANIC_STD_THRES	16
#घोषणा RX_PANIC_STD_REFILL	(3*RX_PANIC_STD_THRES)/2
#घोषणा RX_LOW_STD_THRES	(3*RX_RING_SIZE)/4
#घोषणा RX_PANIC_MINI_THRES	12
#घोषणा RX_PANIC_MINI_REFILL	(3*RX_PANIC_MINI_THRES)/2
#घोषणा RX_LOW_MINI_THRES	(3*RX_MINI_SIZE)/4
#घोषणा RX_PANIC_JUMBO_THRES	6
#घोषणा RX_PANIC_JUMBO_REFILL	(3*RX_PANIC_JUMBO_THRES)/2
#घोषणा RX_LOW_JUMBO_THRES	(3*RX_JUMBO_SIZE)/4


/*
 * Size of the mini ring entries, basically these just should be big
 * enough to take TCP ACKs
 */
#घोषणा ACE_MINI_SIZE		100

#घोषणा ACE_MINI_बफ_मानE	ACE_MINI_SIZE
#घोषणा ACE_STD_बफ_मानE		(ACE_STD_MTU + ETH_HLEN + 4)
#घोषणा ACE_JUMBO_बफ_मानE	(ACE_JUMBO_MTU + ETH_HLEN + 4)

/*
 * There seems to be a magic dअगरference in the effect between 995 and 996
 * but little dअगरference between 900 and 995 ... no idea why.
 *
 * There is now a शेष set of tuning parameters which is set, depending
 * on whether or not the user enables Jumbo frames. It's assumed that अगर
 * Jumbo frames are enabled, the user wants optimal tuning क्रम that हाल.
 */
#घोषणा DEF_TX_COAL		400 /* 996 */
#घोषणा DEF_TX_MAX_DESC		60  /* was 40 */
#घोषणा DEF_RX_COAL		120 /* 1000 */
#घोषणा DEF_RX_MAX_DESC		25
#घोषणा DEF_TX_RATIO		21 /* 24 */

#घोषणा DEF_JUMBO_TX_COAL	20
#घोषणा DEF_JUMBO_TX_MAX_DESC	60
#घोषणा DEF_JUMBO_RX_COAL	30
#घोषणा DEF_JUMBO_RX_MAX_DESC	6
#घोषणा DEF_JUMBO_TX_RATIO	21

#अगर tigon2FwReleaseLocal < 20001118
/*
 * Standard firmware and early modअगरications duplicate
 * IRQ load without this flag (coal समयr is never reset).
 * Note that with this flag tx_coal should be less than
 * समय to xmit full tx ring.
 * 400usec is not so bad क्रम tx ring size of 128.
 */
#घोषणा TX_COAL_INTS_ONLY	1	/* worth it */
#अन्यथा
/*
 * With modअगरied firmware, this is not necessary, but still useful.
 */
#घोषणा TX_COAL_INTS_ONLY	1
#पूर्ण_अगर

#घोषणा DEF_TRACE		0
#घोषणा DEF_STAT		(2 * TICKS_PER_SEC)


अटल पूर्णांक link_state[ACE_MAX_MOD_PARMS];
अटल पूर्णांक trace[ACE_MAX_MOD_PARMS];
अटल पूर्णांक tx_coal_tick[ACE_MAX_MOD_PARMS];
अटल पूर्णांक rx_coal_tick[ACE_MAX_MOD_PARMS];
अटल पूर्णांक max_tx_desc[ACE_MAX_MOD_PARMS];
अटल पूर्णांक max_rx_desc[ACE_MAX_MOD_PARMS];
अटल पूर्णांक tx_ratio[ACE_MAX_MOD_PARMS];
अटल पूर्णांक dis_pci_mem_inval[ACE_MAX_MOD_PARMS] = अणु1, 1, 1, 1, 1, 1, 1, 1पूर्ण;

MODULE_AUTHOR("Jes Sorensen <jes@trained-monkey.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("AceNIC/3C985/GA620 Gigabit Ethernet driver");
#अगर_अघोषित CONFIG_ACENIC_OMIT_TIGON_I
MODULE_FIRMWARE("acenic/tg1.bin");
#पूर्ण_अगर
MODULE_FIRMWARE("acenic/tg2.bin");

module_param_array_named(link, link_state, पूर्णांक, शून्य, 0);
module_param_array(trace, पूर्णांक, शून्य, 0);
module_param_array(tx_coal_tick, पूर्णांक, शून्य, 0);
module_param_array(max_tx_desc, पूर्णांक, शून्य, 0);
module_param_array(rx_coal_tick, पूर्णांक, शून्य, 0);
module_param_array(max_rx_desc, पूर्णांक, शून्य, 0);
module_param_array(tx_ratio, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(link, "AceNIC/3C985/NetGear link state");
MODULE_PARM_DESC(trace, "AceNIC/3C985/NetGear firmware trace level");
MODULE_PARM_DESC(tx_coal_tick, "AceNIC/3C985/GA620 max clock ticks to wait from first tx descriptor arrives");
MODULE_PARM_DESC(max_tx_desc, "AceNIC/3C985/GA620 max number of transmit descriptors to wait");
MODULE_PARM_DESC(rx_coal_tick, "AceNIC/3C985/GA620 max clock ticks to wait from first rx descriptor arrives");
MODULE_PARM_DESC(max_rx_desc, "AceNIC/3C985/GA620 max number of receive descriptors to wait");
MODULE_PARM_DESC(tx_ratio, "AceNIC/3C985/GA620 ratio of NIC memory used for TX/RX descriptors (range 0-63)");


अटल स्थिर अक्षर version[] =
  "acenic.c: v0.92 08/05/2002  Jes Sorensen, linux-acenic@SunSITE.dk\n"
  "                            http://home.cern.ch/~jes/gige/acenic.html\n";

अटल पूर्णांक ace_get_link_ksettings(काष्ठा net_device *,
				  काष्ठा ethtool_link_ksettings *);
अटल पूर्णांक ace_set_link_ksettings(काष्ठा net_device *,
				  स्थिर काष्ठा ethtool_link_ksettings *);
अटल व्योम ace_get_drvinfo(काष्ठा net_device *, काष्ठा ethtool_drvinfo *);

अटल स्थिर काष्ठा ethtool_ops ace_ethtool_ops = अणु
	.get_drvinfo = ace_get_drvinfo,
	.get_link_ksettings = ace_get_link_ksettings,
	.set_link_ksettings = ace_set_link_ksettings,
पूर्ण;

अटल व्योम ace_watchकरोg(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

अटल स्थिर काष्ठा net_device_ops ace_netdev_ops = अणु
	.nकरो_खोलो		= ace_खोलो,
	.nकरो_stop		= ace_बंद,
	.nकरो_tx_समयout		= ace_watchकरोg,
	.nकरो_get_stats		= ace_get_stats,
	.nकरो_start_xmit		= ace_start_xmit,
	.nकरो_set_rx_mode	= ace_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= ace_set_mac_addr,
	.nकरो_change_mtu		= ace_change_mtu,
पूर्ण;

अटल पूर्णांक acenic_probe_one(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *dev;
	काष्ठा ace_निजी *ap;
	अटल पूर्णांक boards_found;

	dev = alloc_etherdev(माप(काष्ठा ace_निजी));
	अगर (dev == शून्य)
		वापस -ENOMEM;

	SET_NETDEV_DEV(dev, &pdev->dev);

	ap = netdev_priv(dev);
	ap->ndev = dev;
	ap->pdev = pdev;
	ap->name = pci_name(pdev);

	dev->features |= NETIF_F_SG | NETIF_F_IP_CSUM;
	dev->features |= NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;

	dev->watchकरोg_समयo = 5*HZ;
	dev->min_mtu = 0;
	dev->max_mtu = ACE_JUMBO_MTU;

	dev->netdev_ops = &ace_netdev_ops;
	dev->ethtool_ops = &ace_ethtool_ops;

	/* we only display this string ONCE */
	अगर (!boards_found)
		prपूर्णांकk(version);

	अगर (pci_enable_device(pdev))
		जाओ fail_मुक्त_netdev;

	/*
	 * Enable master mode beक्रमe we start playing with the
	 * pci_command word since pci_set_master() will modअगरy
	 * it.
	 */
	pci_set_master(pdev);

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &ap->pci_command);

	/* OpenFirmware on Mac's करोes not set this - DOH.. */
	अगर (!(ap->pci_command & PCI_COMMAND_MEMORY)) अणु
		prपूर्णांकk(KERN_INFO "%s: Enabling PCI Memory Mapped "
		       "access - was not enabled by BIOS/Firmware\n",
		       ap->name);
		ap->pci_command = ap->pci_command | PCI_COMMAND_MEMORY;
		pci_ग_लिखो_config_word(ap->pdev, PCI_COMMAND,
				      ap->pci_command);
		wmb();
	पूर्ण

	pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &ap->pci_latency);
	अगर (ap->pci_latency <= 0x40) अणु
		ap->pci_latency = 0x40;
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, ap->pci_latency);
	पूर्ण

	/*
	 * Remap the regs पूर्णांकo kernel space - this is abuse of
	 * dev->base_addr since it was means क्रम I/O port
	 * addresses but who gives a damn.
	 */
	dev->base_addr = pci_resource_start(pdev, 0);
	ap->regs = ioremap(dev->base_addr, 0x4000);
	अगर (!ap->regs) अणु
		prपूर्णांकk(KERN_ERR "%s:  Unable to map I/O register, "
		       "AceNIC %i will be disabled.\n",
		       ap->name, boards_found);
		जाओ fail_मुक्त_netdev;
	पूर्ण

	चयन(pdev->venकरोr) अणु
	हाल PCI_VENDOR_ID_ALTEON:
		अगर (pdev->device == PCI_DEVICE_ID_FARALLON_PN9100T) अणु
			prपूर्णांकk(KERN_INFO "%s: Farallon PN9100-T ",
			       ap->name);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_INFO "%s: Alteon AceNIC ",
			       ap->name);
		पूर्ण
		अवरोध;
	हाल PCI_VENDOR_ID_3COM:
		prपूर्णांकk(KERN_INFO "%s: 3Com 3C985 ", ap->name);
		अवरोध;
	हाल PCI_VENDOR_ID_NETGEAR:
		prपूर्णांकk(KERN_INFO "%s: NetGear GA620 ", ap->name);
		अवरोध;
	हाल PCI_VENDOR_ID_DEC:
		अगर (pdev->device == PCI_DEVICE_ID_FARALLON_PN9000SX) अणु
			prपूर्णांकk(KERN_INFO "%s: Farallon PN9000-SX ",
			       ap->name);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल PCI_VENDOR_ID_SGI:
		prपूर्णांकk(KERN_INFO "%s: SGI AceNIC ", ap->name);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "%s: Unknown AceNIC ", ap->name);
		अवरोध;
	पूर्ण

	prपूर्णांकk("Gigabit Ethernet at 0x%08lx, ", dev->base_addr);
	prपूर्णांकk("irq %d\n", pdev->irq);

#अगर_घोषित CONFIG_ACENIC_OMIT_TIGON_I
	अगर ((पढ़ोl(&ap->regs->HostCtrl) >> 28) == 4) अणु
		prपूर्णांकk(KERN_ERR "%s: Driver compiled without Tigon I"
		       " support - NIC disabled\n", dev->name);
		जाओ fail_uninit;
	पूर्ण
#पूर्ण_अगर

	अगर (ace_allocate_descriptors(dev))
		जाओ fail_मुक्त_netdev;

#अगर_घोषित MODULE
	अगर (boards_found >= ACE_MAX_MOD_PARMS)
		ap->board_idx = BOARD_IDX_OVERFLOW;
	अन्यथा
		ap->board_idx = boards_found;
#अन्यथा
	ap->board_idx = BOARD_IDX_STATIC;
#पूर्ण_अगर

	अगर (ace_init(dev))
		जाओ fail_मुक्त_netdev;

	अगर (रेजिस्टर_netdev(dev)) अणु
		prपूर्णांकk(KERN_ERR "acenic: device registration failed\n");
		जाओ fail_uninit;
	पूर्ण
	ap->name = dev->name;

	अगर (ap->pci_using_dac)
		dev->features |= NETIF_F_HIGHDMA;

	pci_set_drvdata(pdev, dev);

	boards_found++;
	वापस 0;

 fail_uninit:
	ace_init_cleanup(dev);
 fail_मुक्त_netdev:
	मुक्त_netdev(dev);
	वापस -ENODEV;
पूर्ण

अटल व्योम acenic_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	लघु i;

	unरेजिस्टर_netdev(dev);

	ग_लिखोl(पढ़ोl(&regs->CpuCtrl) | CPU_HALT, &regs->CpuCtrl);
	अगर (ap->version >= 2)
		ग_लिखोl(पढ़ोl(&regs->CpuBCtrl) | CPU_HALT, &regs->CpuBCtrl);

	/*
	 * This clears any pending पूर्णांकerrupts
	 */
	ग_लिखोl(1, &regs->Mb0Lo);
	पढ़ोl(&regs->CpuCtrl);	/* flush */

	/*
	 * Make sure no other CPUs are processing पूर्णांकerrupts
	 * on the card beक्रमe the buffers are being released.
	 * Otherwise one might experience some `पूर्णांकeresting'
	 * effects.
	 *
	 * Then release the RX buffers - jumbo buffers were
	 * alपढ़ोy released in ace_बंद().
	 */
	ace_sync_irq(dev->irq);

	क्रम (i = 0; i < RX_STD_RING_ENTRIES; i++) अणु
		काष्ठा sk_buff *skb = ap->skb->rx_std_skbuff[i].skb;

		अगर (skb) अणु
			काष्ठा ring_info *ringp;
			dma_addr_t mapping;

			ringp = &ap->skb->rx_std_skbuff[i];
			mapping = dma_unmap_addr(ringp, mapping);
			dma_unmap_page(&ap->pdev->dev, mapping,
				       ACE_STD_बफ_मानE, DMA_FROM_DEVICE);

			ap->rx_std_ring[i].size = 0;
			ap->skb->rx_std_skbuff[i].skb = शून्य;
			dev_kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	अगर (ap->version >= 2) अणु
		क्रम (i = 0; i < RX_MINI_RING_ENTRIES; i++) अणु
			काष्ठा sk_buff *skb = ap->skb->rx_mini_skbuff[i].skb;

			अगर (skb) अणु
				काष्ठा ring_info *ringp;
				dma_addr_t mapping;

				ringp = &ap->skb->rx_mini_skbuff[i];
				mapping = dma_unmap_addr(ringp,mapping);
				dma_unmap_page(&ap->pdev->dev, mapping,
					       ACE_MINI_बफ_मानE,
					       DMA_FROM_DEVICE);

				ap->rx_mini_ring[i].size = 0;
				ap->skb->rx_mini_skbuff[i].skb = शून्य;
				dev_kमुक्त_skb(skb);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < RX_JUMBO_RING_ENTRIES; i++) अणु
		काष्ठा sk_buff *skb = ap->skb->rx_jumbo_skbuff[i].skb;
		अगर (skb) अणु
			काष्ठा ring_info *ringp;
			dma_addr_t mapping;

			ringp = &ap->skb->rx_jumbo_skbuff[i];
			mapping = dma_unmap_addr(ringp, mapping);
			dma_unmap_page(&ap->pdev->dev, mapping,
				       ACE_JUMBO_बफ_मानE, DMA_FROM_DEVICE);

			ap->rx_jumbo_ring[i].size = 0;
			ap->skb->rx_jumbo_skbuff[i].skb = शून्य;
			dev_kमुक्त_skb(skb);
		पूर्ण
	पूर्ण

	ace_init_cleanup(dev);
	मुक्त_netdev(dev);
पूर्ण

अटल काष्ठा pci_driver acenic_pci_driver = अणु
	.name		= "acenic",
	.id_table	= acenic_pci_tbl,
	.probe		= acenic_probe_one,
	.हटाओ		= acenic_हटाओ_one,
पूर्ण;

अटल व्योम ace_मुक्त_descriptors(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	पूर्णांक size;

	अगर (ap->rx_std_ring != शून्य) अणु
		size = (माप(काष्ठा rx_desc) *
			(RX_STD_RING_ENTRIES +
			 RX_JUMBO_RING_ENTRIES +
			 RX_MINI_RING_ENTRIES +
			 RX_RETURN_RING_ENTRIES));
		dma_मुक्त_coherent(&ap->pdev->dev, size, ap->rx_std_ring,
				  ap->rx_ring_base_dma);
		ap->rx_std_ring = शून्य;
		ap->rx_jumbo_ring = शून्य;
		ap->rx_mini_ring = शून्य;
		ap->rx_वापस_ring = शून्य;
	पूर्ण
	अगर (ap->evt_ring != शून्य) अणु
		size = (माप(काष्ठा event) * EVT_RING_ENTRIES);
		dma_मुक्त_coherent(&ap->pdev->dev, size, ap->evt_ring,
				  ap->evt_ring_dma);
		ap->evt_ring = शून्य;
	पूर्ण
	अगर (ap->tx_ring != शून्य && !ACE_IS_TIGON_I(ap)) अणु
		size = (माप(काष्ठा tx_desc) * MAX_TX_RING_ENTRIES);
		dma_मुक्त_coherent(&ap->pdev->dev, size, ap->tx_ring,
				  ap->tx_ring_dma);
	पूर्ण
	ap->tx_ring = शून्य;

	अगर (ap->evt_prd != शून्य) अणु
		dma_मुक्त_coherent(&ap->pdev->dev, माप(u32),
				  (व्योम *)ap->evt_prd, ap->evt_prd_dma);
		ap->evt_prd = शून्य;
	पूर्ण
	अगर (ap->rx_ret_prd != शून्य) अणु
		dma_मुक्त_coherent(&ap->pdev->dev, माप(u32),
				  (व्योम *)ap->rx_ret_prd, ap->rx_ret_prd_dma);
		ap->rx_ret_prd = शून्य;
	पूर्ण
	अगर (ap->tx_csm != शून्य) अणु
		dma_मुक्त_coherent(&ap->pdev->dev, माप(u32),
				  (व्योम *)ap->tx_csm, ap->tx_csm_dma);
		ap->tx_csm = शून्य;
	पूर्ण
पूर्ण


अटल पूर्णांक ace_allocate_descriptors(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	पूर्णांक size;

	size = (माप(काष्ठा rx_desc) *
		(RX_STD_RING_ENTRIES +
		 RX_JUMBO_RING_ENTRIES +
		 RX_MINI_RING_ENTRIES +
		 RX_RETURN_RING_ENTRIES));

	ap->rx_std_ring = dma_alloc_coherent(&ap->pdev->dev, size,
					     &ap->rx_ring_base_dma, GFP_KERNEL);
	अगर (ap->rx_std_ring == शून्य)
		जाओ fail;

	ap->rx_jumbo_ring = ap->rx_std_ring + RX_STD_RING_ENTRIES;
	ap->rx_mini_ring = ap->rx_jumbo_ring + RX_JUMBO_RING_ENTRIES;
	ap->rx_वापस_ring = ap->rx_mini_ring + RX_MINI_RING_ENTRIES;

	size = (माप(काष्ठा event) * EVT_RING_ENTRIES);

	ap->evt_ring = dma_alloc_coherent(&ap->pdev->dev, size,
					  &ap->evt_ring_dma, GFP_KERNEL);

	अगर (ap->evt_ring == शून्य)
		जाओ fail;

	/*
	 * Only allocate a host TX ring क्रम the Tigon II, the Tigon I
	 * has to use PCI रेजिस्टरs क्रम this ;-(
	 */
	अगर (!ACE_IS_TIGON_I(ap)) अणु
		size = (माप(काष्ठा tx_desc) * MAX_TX_RING_ENTRIES);

		ap->tx_ring = dma_alloc_coherent(&ap->pdev->dev, size,
						 &ap->tx_ring_dma, GFP_KERNEL);

		अगर (ap->tx_ring == शून्य)
			जाओ fail;
	पूर्ण

	ap->evt_prd = dma_alloc_coherent(&ap->pdev->dev, माप(u32),
					 &ap->evt_prd_dma, GFP_KERNEL);
	अगर (ap->evt_prd == शून्य)
		जाओ fail;

	ap->rx_ret_prd = dma_alloc_coherent(&ap->pdev->dev, माप(u32),
					    &ap->rx_ret_prd_dma, GFP_KERNEL);
	अगर (ap->rx_ret_prd == शून्य)
		जाओ fail;

	ap->tx_csm = dma_alloc_coherent(&ap->pdev->dev, माप(u32),
					&ap->tx_csm_dma, GFP_KERNEL);
	अगर (ap->tx_csm == शून्य)
		जाओ fail;

	वापस 0;

fail:
	/* Clean up. */
	ace_init_cleanup(dev);
	वापस 1;
पूर्ण


/*
 * Generic cleanup handling data allocated during init. Used when the
 * module is unloaded or अगर an error occurs during initialization
 */
अटल व्योम ace_init_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap;

	ap = netdev_priv(dev);

	ace_मुक्त_descriptors(dev);

	अगर (ap->info)
		dma_मुक्त_coherent(&ap->pdev->dev, माप(काष्ठा ace_info),
				  ap->info, ap->info_dma);
	kमुक्त(ap->skb);
	kमुक्त(ap->trace_buf);

	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);

	iounmap(ap->regs);
पूर्ण


/*
 * Commands are considered to be slow.
 */
अटल अंतरभूत व्योम ace_issue_cmd(काष्ठा ace_regs __iomem *regs, काष्ठा cmd *cmd)
अणु
	u32 idx;

	idx = पढ़ोl(&regs->CmdPrd);

	ग_लिखोl(*(u32 *)(cmd), &regs->CmdRng[idx]);
	idx = (idx + 1) % CMD_RING_ENTRIES;

	ग_लिखोl(idx, &regs->CmdPrd);
पूर्ण


अटल पूर्णांक ace_init(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap;
	काष्ठा ace_regs __iomem *regs;
	काष्ठा ace_info *info = शून्य;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ myjअगर;
	u64 पंचांगp_ptr;
	u32 tig_ver, mac1, mac2, पंचांगp, pci_state;
	पूर्णांक board_idx, ecode = 0;
	लघु i;
	अचिन्हित अक्षर cache_size;

	ap = netdev_priv(dev);
	regs = ap->regs;

	board_idx = ap->board_idx;

	/*
	 * aman@sgi.com - its useful to करो a NIC reset here to
	 * address the `Firmware not running' problem subsequent
	 * to any crashes involving the NIC
	 */
	ग_लिखोl(HW_RESET | (HW_RESET << 24), &regs->HostCtrl);
	पढ़ोl(&regs->HostCtrl);		/* PCI ग_लिखो posting */
	udelay(5);

	/*
	 * Don't access any other रेजिस्टरs beक्रमe this poपूर्णांक!
	 */
#अगर_घोषित __BIG_ENDIAN
	/*
	 * This will most likely need BYTE_SWAP once we चयन
	 * to using __raw_ग_लिखोl()
	 */
	ग_लिखोl((WORD_SWAP | CLR_INT | ((WORD_SWAP | CLR_INT) << 24)),
	       &regs->HostCtrl);
#अन्यथा
	ग_लिखोl((CLR_INT | WORD_SWAP | ((CLR_INT | WORD_SWAP) << 24)),
	       &regs->HostCtrl);
#पूर्ण_अगर
	पढ़ोl(&regs->HostCtrl);		/* PCI ग_लिखो posting */

	/*
	 * Stop the NIC CPU and clear pending पूर्णांकerrupts
	 */
	ग_लिखोl(पढ़ोl(&regs->CpuCtrl) | CPU_HALT, &regs->CpuCtrl);
	पढ़ोl(&regs->CpuCtrl);		/* PCI ग_लिखो posting */
	ग_लिखोl(0, &regs->Mb0Lo);

	tig_ver = पढ़ोl(&regs->HostCtrl) >> 28;

	चयन(tig_ver)अणु
#अगर_अघोषित CONFIG_ACENIC_OMIT_TIGON_I
	हाल 4:
	हाल 5:
		prपूर्णांकk(KERN_INFO "  Tigon I  (Rev. %i), Firmware: %i.%i.%i, ",
		       tig_ver, ap->firmware_major, ap->firmware_minor,
		       ap->firmware_fix);
		ग_लिखोl(0, &regs->LocalCtrl);
		ap->version = 1;
		ap->tx_ring_entries = TIGON_I_TX_RING_ENTRIES;
		अवरोध;
#पूर्ण_अगर
	हाल 6:
		prपूर्णांकk(KERN_INFO "  Tigon II (Rev. %i), Firmware: %i.%i.%i, ",
		       tig_ver, ap->firmware_major, ap->firmware_minor,
		       ap->firmware_fix);
		ग_लिखोl(पढ़ोl(&regs->CpuBCtrl) | CPU_HALT, &regs->CpuBCtrl);
		पढ़ोl(&regs->CpuBCtrl);		/* PCI ग_लिखो posting */
		/*
		 * The SRAM bank size करोes _not_ indicate the amount
		 * of memory on the card, it controls the _bank_ size!
		 * Ie. a 1MB AceNIC will have two banks of 512KB.
		 */
		ग_लिखोl(SRAM_BANK_512K, &regs->LocalCtrl);
		ग_लिखोl(SYNC_SRAM_TIMING, &regs->MiscCfg);
		ap->version = 2;
		ap->tx_ring_entries = MAX_TX_RING_ENTRIES;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "  Unsupported Tigon version detected "
		       "(%i)\n", tig_ver);
		ecode = -ENODEV;
		जाओ init_error;
	पूर्ण

	/*
	 * ModeStat _must_ be set after the SRAM settings as this change
	 * seems to corrupt the ModeStat and possible other रेजिस्टरs.
	 * The SRAM settings survive resets and setting it to the same
	 * value a second समय works as well. This is what caused the
	 * `Firmware not running' problem on the Tigon II.
	 */
#अगर_घोषित __BIG_ENDIAN
	ग_लिखोl(ACE_BYTE_SWAP_DMA | ACE_WARN | ACE_FATAL | ACE_BYTE_SWAP_BD |
	       ACE_WORD_SWAP_BD | ACE_NO_JUMBO_FRAG, &regs->ModeStat);
#अन्यथा
	ग_लिखोl(ACE_BYTE_SWAP_DMA | ACE_WARN | ACE_FATAL |
	       ACE_WORD_SWAP_BD | ACE_NO_JUMBO_FRAG, &regs->ModeStat);
#पूर्ण_अगर
	पढ़ोl(&regs->ModeStat);		/* PCI ग_लिखो posting */

	mac1 = 0;
	क्रम(i = 0; i < 4; i++) अणु
		पूर्णांक t;

		mac1 = mac1 << 8;
		t = पढ़ो_eeprom_byte(dev, 0x8c+i);
		अगर (t < 0) अणु
			ecode = -EIO;
			जाओ init_error;
		पूर्ण अन्यथा
			mac1 |= (t & 0xff);
	पूर्ण
	mac2 = 0;
	क्रम(i = 4; i < 8; i++) अणु
		पूर्णांक t;

		mac2 = mac2 << 8;
		t = पढ़ो_eeprom_byte(dev, 0x8c+i);
		अगर (t < 0) अणु
			ecode = -EIO;
			जाओ init_error;
		पूर्ण अन्यथा
			mac2 |= (t & 0xff);
	पूर्ण

	ग_लिखोl(mac1, &regs->MacAddrHi);
	ग_लिखोl(mac2, &regs->MacAddrLo);

	dev->dev_addr[0] = (mac1 >> 8) & 0xff;
	dev->dev_addr[1] = mac1 & 0xff;
	dev->dev_addr[2] = (mac2 >> 24) & 0xff;
	dev->dev_addr[3] = (mac2 >> 16) & 0xff;
	dev->dev_addr[4] = (mac2 >> 8) & 0xff;
	dev->dev_addr[5] = mac2 & 0xff;

	prपूर्णांकk("MAC: %pM\n", dev->dev_addr);

	/*
	 * Looks like this is necessary to deal with on all architectures,
	 * even this %$#%$# N440BX Intel based thing करोesn't get it right.
	 * Ie. having two NICs in the machine, one will have the cache
	 * line set at boot समय, the other will not.
	 */
	pdev = ap->pdev;
	pci_पढ़ो_config_byte(pdev, PCI_CACHE_LINE_SIZE, &cache_size);
	cache_size <<= 2;
	अगर (cache_size != SMP_CACHE_BYTES) अणु
		prपूर्णांकk(KERN_INFO "  PCI cache line size set incorrectly "
		       "(%i bytes) by BIOS/FW, ", cache_size);
		अगर (cache_size > SMP_CACHE_BYTES)
			prपूर्णांकk("expecting %i\n", SMP_CACHE_BYTES);
		अन्यथा अणु
			prपूर्णांकk("correcting to %i\n", SMP_CACHE_BYTES);
			pci_ग_लिखो_config_byte(pdev, PCI_CACHE_LINE_SIZE,
					      SMP_CACHE_BYTES >> 2);
		पूर्ण
	पूर्ण

	pci_state = पढ़ोl(&regs->PciState);
	prपूर्णांकk(KERN_INFO "  PCI bus width: %i bits, speed: %iMHz, "
	       "latency: %i clks\n",
	       	(pci_state & PCI_32BIT) ? 32 : 64,
		(pci_state & PCI_66MHZ) ? 66 : 33,
		ap->pci_latency);

	/*
	 * Set the max DMA transfer size. Seems that क्रम most प्रणालीs
	 * the perक्रमmance is better when no MAX parameter is
	 * set. However क्रम प्रणालीs enabling PCI ग_लिखो and invalidate,
	 * DMA ग_लिखोs must be set to the L1 cache line size to get
	 * optimal perक्रमmance.
	 *
	 * The शेष is now to turn the PCI ग_लिखो and invalidate off
	 * - that is what Alteon करोes क्रम NT.
	 */
	पंचांगp = READ_CMD_MEM | WRITE_CMD_MEM;
	अगर (ap->version >= 2) अणु
		पंचांगp |= (MEM_READ_MULTIPLE | (pci_state & PCI_66MHZ));
		/*
		 * Tuning parameters only supported क्रम 8 cards
		 */
		अगर (board_idx == BOARD_IDX_OVERFLOW ||
		    dis_pci_mem_inval[board_idx]) अणु
			अगर (ap->pci_command & PCI_COMMAND_INVALIDATE) अणु
				ap->pci_command &= ~PCI_COMMAND_INVALIDATE;
				pci_ग_लिखो_config_word(pdev, PCI_COMMAND,
						      ap->pci_command);
				prपूर्णांकk(KERN_INFO "  Disabling PCI memory "
				       "write and invalidate\n");
			पूर्ण
		पूर्ण अन्यथा अगर (ap->pci_command & PCI_COMMAND_INVALIDATE) अणु
			prपूर्णांकk(KERN_INFO "  PCI memory write & invalidate "
			       "enabled by BIOS, enabling counter measures\n");

			चयन(SMP_CACHE_BYTES) अणु
			हाल 16:
				पंचांगp |= DMA_WRITE_MAX_16;
				अवरोध;
			हाल 32:
				पंचांगp |= DMA_WRITE_MAX_32;
				अवरोध;
			हाल 64:
				पंचांगp |= DMA_WRITE_MAX_64;
				अवरोध;
			हाल 128:
				पंचांगp |= DMA_WRITE_MAX_128;
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_INFO "  Cache line size %i not "
				       "supported, PCI write and invalidate "
				       "disabled\n", SMP_CACHE_BYTES);
				ap->pci_command &= ~PCI_COMMAND_INVALIDATE;
				pci_ग_लिखो_config_word(pdev, PCI_COMMAND,
						      ap->pci_command);
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित __sparc__
	/*
	 * On this platक्रमm, we know what the best dma settings
	 * are.  We use 64-byte maximum bursts, because अगर we
	 * burst larger than the cache line size (or even cross
	 * a 64byte boundary in a single burst) the UltraSparc
	 * PCI controller will disconnect at 64-byte multiples.
	 *
	 * Read-multiple will be properly enabled above, and when
	 * set will give the PCI controller proper hपूर्णांकs about
	 * prefetching.
	 */
	पंचांगp &= ~DMA_READ_WRITE_MASK;
	पंचांगp |= DMA_READ_MAX_64;
	पंचांगp |= DMA_WRITE_MAX_64;
#पूर्ण_अगर
#अगर_घोषित __alpha__
	पंचांगp &= ~DMA_READ_WRITE_MASK;
	पंचांगp |= DMA_READ_MAX_128;
	/*
	 * All the करोcs say MUST NOT. Well, I did.
	 * Nothing terrible happens, अगर we load wrong size.
	 * Bit w&i still works better!
	 */
	पंचांगp |= DMA_WRITE_MAX_128;
#पूर्ण_अगर
	ग_लिखोl(पंचांगp, &regs->PciState);

#अगर 0
	/*
	 * The Host PCI bus controller driver has to set FBB.
	 * If all devices on that PCI bus support FBB, then the controller
	 * can enable FBB support in the Host PCI Bus controller (or on
	 * the PCI-PCI bridge अगर that applies).
	 * -ggg
	 */
	/*
	 * I have received reports from people having problems when this
	 * bit is enabled.
	 */
	अगर (!(ap->pci_command & PCI_COMMAND_FAST_BACK)) अणु
		prपूर्णांकk(KERN_INFO "  Enabling PCI Fast Back to Back\n");
		ap->pci_command |= PCI_COMMAND_FAST_BACK;
		pci_ग_लिखो_config_word(pdev, PCI_COMMAND, ap->pci_command);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Configure DMA attributes.
	 */
	अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(64))) अणु
		ap->pci_using_dac = 1;
	पूर्ण अन्यथा अगर (!dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		ap->pci_using_dac = 0;
	पूर्ण अन्यथा अणु
		ecode = -ENODEV;
		जाओ init_error;
	पूर्ण

	/*
	 * Initialize the generic info block and the command+event rings
	 * and the control blocks क्रम the transmit and receive rings
	 * as they need to be setup once and क्रम all.
	 */
	अगर (!(info = dma_alloc_coherent(&ap->pdev->dev, माप(काष्ठा ace_info),
					&ap->info_dma, GFP_KERNEL))) अणु
		ecode = -EAGAIN;
		जाओ init_error;
	पूर्ण
	ap->info = info;

	/*
	 * Get the memory क्रम the skb rings.
	 */
	अगर (!(ap->skb = kzalloc(माप(काष्ठा ace_skb), GFP_KERNEL))) अणु
		ecode = -EAGAIN;
		जाओ init_error;
	पूर्ण

	ecode = request_irq(pdev->irq, ace_पूर्णांकerrupt, IRQF_SHARED,
			    DRV_NAME, dev);
	अगर (ecode) अणु
		prपूर्णांकk(KERN_WARNING "%s: Requested IRQ %d is busy\n",
		       DRV_NAME, pdev->irq);
		जाओ init_error;
	पूर्ण अन्यथा
		dev->irq = pdev->irq;

#अगर_घोषित INDEX_DEBUG
	spin_lock_init(&ap->debug_lock);
	ap->last_tx = ACE_TX_RING_ENTRIES(ap) - 1;
	ap->last_std_rx = 0;
	ap->last_mini_rx = 0;
#पूर्ण_अगर

	ecode = ace_load_firmware(dev);
	अगर (ecode)
		जाओ init_error;

	ap->fw_running = 0;

	पंचांगp_ptr = ap->info_dma;
	ग_लिखोl(पंचांगp_ptr >> 32, &regs->InfoPtrHi);
	ग_लिखोl(पंचांगp_ptr & 0xffffffff, &regs->InfoPtrLo);

	स_रखो(ap->evt_ring, 0, EVT_RING_ENTRIES * माप(काष्ठा event));

	set_aceaddr(&info->evt_ctrl.rngptr, ap->evt_ring_dma);
	info->evt_ctrl.flags = 0;

	*(ap->evt_prd) = 0;
	wmb();
	set_aceaddr(&info->evt_prd_ptr, ap->evt_prd_dma);
	ग_लिखोl(0, &regs->EvtCsm);

	set_aceaddr(&info->cmd_ctrl.rngptr, 0x100);
	info->cmd_ctrl.flags = 0;
	info->cmd_ctrl.max_len = 0;

	क्रम (i = 0; i < CMD_RING_ENTRIES; i++)
		ग_लिखोl(0, &regs->CmdRng[i]);

	ग_लिखोl(0, &regs->CmdPrd);
	ग_लिखोl(0, &regs->CmdCsm);

	पंचांगp_ptr = ap->info_dma;
	पंचांगp_ptr += (अचिन्हित दीर्घ) &(((काष्ठा ace_info *)0)->s.stats);
	set_aceaddr(&info->stats2_ptr, (dma_addr_t) पंचांगp_ptr);

	set_aceaddr(&info->rx_std_ctrl.rngptr, ap->rx_ring_base_dma);
	info->rx_std_ctrl.max_len = ACE_STD_बफ_मानE;
	info->rx_std_ctrl.flags =
	  RCB_FLG_TCP_UDP_SUM | RCB_FLG_NO_PSEUDO_HDR | RCB_FLG_VLAN_ASSIST;

	स_रखो(ap->rx_std_ring, 0,
	       RX_STD_RING_ENTRIES * माप(काष्ठा rx_desc));

	क्रम (i = 0; i < RX_STD_RING_ENTRIES; i++)
		ap->rx_std_ring[i].flags = BD_FLG_TCP_UDP_SUM;

	ap->rx_std_skbprd = 0;
	atomic_set(&ap->cur_rx_bufs, 0);

	set_aceaddr(&info->rx_jumbo_ctrl.rngptr,
		    (ap->rx_ring_base_dma +
		     (माप(काष्ठा rx_desc) * RX_STD_RING_ENTRIES)));
	info->rx_jumbo_ctrl.max_len = 0;
	info->rx_jumbo_ctrl.flags =
	  RCB_FLG_TCP_UDP_SUM | RCB_FLG_NO_PSEUDO_HDR | RCB_FLG_VLAN_ASSIST;

	स_रखो(ap->rx_jumbo_ring, 0,
	       RX_JUMBO_RING_ENTRIES * माप(काष्ठा rx_desc));

	क्रम (i = 0; i < RX_JUMBO_RING_ENTRIES; i++)
		ap->rx_jumbo_ring[i].flags = BD_FLG_TCP_UDP_SUM | BD_FLG_JUMBO;

	ap->rx_jumbo_skbprd = 0;
	atomic_set(&ap->cur_jumbo_bufs, 0);

	स_रखो(ap->rx_mini_ring, 0,
	       RX_MINI_RING_ENTRIES * माप(काष्ठा rx_desc));

	अगर (ap->version >= 2) अणु
		set_aceaddr(&info->rx_mini_ctrl.rngptr,
			    (ap->rx_ring_base_dma +
			     (माप(काष्ठा rx_desc) *
			      (RX_STD_RING_ENTRIES +
			       RX_JUMBO_RING_ENTRIES))));
		info->rx_mini_ctrl.max_len = ACE_MINI_SIZE;
		info->rx_mini_ctrl.flags =
		  RCB_FLG_TCP_UDP_SUM|RCB_FLG_NO_PSEUDO_HDR|RCB_FLG_VLAN_ASSIST;

		क्रम (i = 0; i < RX_MINI_RING_ENTRIES; i++)
			ap->rx_mini_ring[i].flags =
				BD_FLG_TCP_UDP_SUM | BD_FLG_MINI;
	पूर्ण अन्यथा अणु
		set_aceaddr(&info->rx_mini_ctrl.rngptr, 0);
		info->rx_mini_ctrl.flags = RCB_FLG_RNG_DISABLE;
		info->rx_mini_ctrl.max_len = 0;
	पूर्ण

	ap->rx_mini_skbprd = 0;
	atomic_set(&ap->cur_mini_bufs, 0);

	set_aceaddr(&info->rx_वापस_ctrl.rngptr,
		    (ap->rx_ring_base_dma +
		     (माप(काष्ठा rx_desc) *
		      (RX_STD_RING_ENTRIES +
		       RX_JUMBO_RING_ENTRIES +
		       RX_MINI_RING_ENTRIES))));
	info->rx_वापस_ctrl.flags = 0;
	info->rx_वापस_ctrl.max_len = RX_RETURN_RING_ENTRIES;

	स_रखो(ap->rx_वापस_ring, 0,
	       RX_RETURN_RING_ENTRIES * माप(काष्ठा rx_desc));

	set_aceaddr(&info->rx_ret_prd_ptr, ap->rx_ret_prd_dma);
	*(ap->rx_ret_prd) = 0;

	ग_लिखोl(TX_RING_BASE, &regs->WinBase);

	अगर (ACE_IS_TIGON_I(ap)) अणु
		ap->tx_ring = (__क्रमce काष्ठा tx_desc *) regs->Winकरोw;
		क्रम (i = 0; i < (TIGON_I_TX_RING_ENTRIES
				 * माप(काष्ठा tx_desc)) / माप(u32); i++)
			ग_लिखोl(0, (__क्रमce व्योम __iomem *)ap->tx_ring  + i * 4);

		set_aceaddr(&info->tx_ctrl.rngptr, TX_RING_BASE);
	पूर्ण अन्यथा अणु
		स_रखो(ap->tx_ring, 0,
		       MAX_TX_RING_ENTRIES * माप(काष्ठा tx_desc));

		set_aceaddr(&info->tx_ctrl.rngptr, ap->tx_ring_dma);
	पूर्ण

	info->tx_ctrl.max_len = ACE_TX_RING_ENTRIES(ap);
	पंचांगp = RCB_FLG_TCP_UDP_SUM | RCB_FLG_NO_PSEUDO_HDR | RCB_FLG_VLAN_ASSIST;

	/*
	 * The Tigon I करोes not like having the TX ring in host memory ;-(
	 */
	अगर (!ACE_IS_TIGON_I(ap))
		पंचांगp |= RCB_FLG_TX_HOST_RING;
#अगर TX_COAL_INTS_ONLY
	पंचांगp |= RCB_FLG_COAL_INT_ONLY;
#पूर्ण_अगर
	info->tx_ctrl.flags = पंचांगp;

	set_aceaddr(&info->tx_csm_ptr, ap->tx_csm_dma);

	/*
	 * Potential item क्रम tuning parameter
	 */
#अगर 0 /* NO */
	ग_लिखोl(DMA_THRESH_16W, &regs->DmaReadCfg);
	ग_लिखोl(DMA_THRESH_16W, &regs->DmaWriteCfg);
#अन्यथा
	ग_लिखोl(DMA_THRESH_8W, &regs->DmaReadCfg);
	ग_लिखोl(DMA_THRESH_8W, &regs->DmaWriteCfg);
#पूर्ण_अगर

	ग_लिखोl(0, &regs->MaskInt);
	ग_लिखोl(1, &regs->IfIdx);
#अगर 0
	/*
	 * McKinley boxes करो not like us fiddling with AssistState
	 * this early
	 */
	ग_लिखोl(1, &regs->AssistState);
#पूर्ण_अगर

	ग_लिखोl(DEF_STAT, &regs->TuneStatTicks);
	ग_लिखोl(DEF_TRACE, &regs->TuneTrace);

	ace_set_rxtx_parms(dev, 0);

	अगर (board_idx == BOARD_IDX_OVERFLOW) अणु
		prपूर्णांकk(KERN_WARNING "%s: more than %i NICs detected, "
		       "ignoring module parameters!\n",
		       ap->name, ACE_MAX_MOD_PARMS);
	पूर्ण अन्यथा अगर (board_idx >= 0) अणु
		अगर (tx_coal_tick[board_idx])
			ग_लिखोl(tx_coal_tick[board_idx],
			       &regs->TuneTxCoalTicks);
		अगर (max_tx_desc[board_idx])
			ग_लिखोl(max_tx_desc[board_idx], &regs->TuneMaxTxDesc);

		अगर (rx_coal_tick[board_idx])
			ग_लिखोl(rx_coal_tick[board_idx],
			       &regs->TuneRxCoalTicks);
		अगर (max_rx_desc[board_idx])
			ग_लिखोl(max_rx_desc[board_idx], &regs->TuneMaxRxDesc);

		अगर (trace[board_idx])
			ग_लिखोl(trace[board_idx], &regs->TuneTrace);

		अगर ((tx_ratio[board_idx] > 0) && (tx_ratio[board_idx] < 64))
			ग_लिखोl(tx_ratio[board_idx], &regs->TxBufRat);
	पूर्ण

	/*
	 * Default link parameters
	 */
	पंचांगp = LNK_ENABLE | LNK_FULL_DUPLEX | LNK_1000MB | LNK_100MB |
		LNK_10MB | LNK_RX_FLOW_CTL_Y | LNK_NEG_FCTL | LNK_NEGOTIATE;
	अगर(ap->version >= 2)
		पंचांगp |= LNK_TX_FLOW_CTL_Y;

	/*
	 * Override link शेष parameters
	 */
	अगर ((board_idx >= 0) && link_state[board_idx]) अणु
		पूर्णांक option = link_state[board_idx];

		पंचांगp = LNK_ENABLE;

		अगर (option & 0x01) अणु
			prपूर्णांकk(KERN_INFO "%s: Setting half duplex link\n",
			       ap->name);
			पंचांगp &= ~LNK_FULL_DUPLEX;
		पूर्ण
		अगर (option & 0x02)
			पंचांगp &= ~LNK_NEGOTIATE;
		अगर (option & 0x10)
			पंचांगp |= LNK_10MB;
		अगर (option & 0x20)
			पंचांगp |= LNK_100MB;
		अगर (option & 0x40)
			पंचांगp |= LNK_1000MB;
		अगर ((option & 0x70) == 0) अणु
			prपूर्णांकk(KERN_WARNING "%s: No media speed specified, "
			       "forcing auto negotiation\n", ap->name);
			पंचांगp |= LNK_NEGOTIATE | LNK_1000MB |
				LNK_100MB | LNK_10MB;
		पूर्ण
		अगर ((option & 0x100) == 0)
			पंचांगp |= LNK_NEG_FCTL;
		अन्यथा
			prपूर्णांकk(KERN_INFO "%s: Disabling flow control "
			       "negotiation\n", ap->name);
		अगर (option & 0x200)
			पंचांगp |= LNK_RX_FLOW_CTL_Y;
		अगर ((option & 0x400) && (ap->version >= 2)) अणु
			prपूर्णांकk(KERN_INFO "%s: Enabling TX flow control\n",
			       ap->name);
			पंचांगp |= LNK_TX_FLOW_CTL_Y;
		पूर्ण
	पूर्ण

	ap->link = पंचांगp;
	ग_लिखोl(पंचांगp, &regs->TuneLink);
	अगर (ap->version >= 2)
		ग_लिखोl(पंचांगp, &regs->TuneFastLink);

	ग_लिखोl(ap->firmware_start, &regs->Pc);

	ग_लिखोl(0, &regs->Mb0Lo);

	/*
	 * Set tx_csm beक्रमe we start receiving पूर्णांकerrupts, otherwise
	 * the पूर्णांकerrupt handler might think it is supposed to process
	 * tx पूर्णांकs beक्रमe we are up and running, which may cause a null
	 * poपूर्णांकer access in the पूर्णांक handler.
	 */
	ap->cur_rx = 0;
	ap->tx_prd = *(ap->tx_csm) = ap->tx_ret_csm = 0;

	wmb();
	ace_set_txprd(regs, ap, 0);
	ग_लिखोl(0, &regs->RxRetCsm);

	/*
	 * Enable DMA engine now.
	 * If we करो this sooner, Mckinley box pukes.
	 * I assume it's because Tigon II DMA engine wants to check
	 * *something* even beक्रमe the CPU is started.
	 */
	ग_लिखोl(1, &regs->AssistState);  /* enable DMA */

	/*
	 * Start the NIC CPU
	 */
	ग_लिखोl(पढ़ोl(&regs->CpuCtrl) & ~(CPU_HALT|CPU_TRACE), &regs->CpuCtrl);
	पढ़ोl(&regs->CpuCtrl);

	/*
	 * Wait क्रम the firmware to spin up - max 3 seconds.
	 */
	myjअगर = jअगरfies + 3 * HZ;
	जबतक (समय_beक्रमe(jअगरfies, myjअगर) && !ap->fw_running)
		cpu_relax();

	अगर (!ap->fw_running) अणु
		prपूर्णांकk(KERN_ERR "%s: Firmware NOT running!\n", ap->name);

		ace_dump_trace(ap);
		ग_लिखोl(पढ़ोl(&regs->CpuCtrl) | CPU_HALT, &regs->CpuCtrl);
		पढ़ोl(&regs->CpuCtrl);

		/* aman@sgi.com - account क्रम badly behaving firmware/NIC:
		 * - have observed that the NIC may जारी to generate
		 *   पूर्णांकerrupts क्रम some reason; attempt to stop it - halt
		 *   second CPU क्रम Tigon II cards, and also clear Mb0
		 * - अगर we're a module, we'll fail to load अगर this was
		 *   the only GbE card in the प्रणाली => अगर the kernel करोes
		 *   see an पूर्णांकerrupt from the NIC, code to handle it is
		 *   gone and OOps! - so मुक्त_irq also
		 */
		अगर (ap->version >= 2)
			ग_लिखोl(पढ़ोl(&regs->CpuBCtrl) | CPU_HALT,
			       &regs->CpuBCtrl);
		ग_लिखोl(0, &regs->Mb0Lo);
		पढ़ोl(&regs->Mb0Lo);

		ecode = -EBUSY;
		जाओ init_error;
	पूर्ण

	/*
	 * We load the ring here as there seem to be no way to tell the
	 * firmware to wipe the ring without re-initializing it.
	 */
	अगर (!test_and_set_bit(0, &ap->std_refill_busy))
		ace_load_std_rx_ring(dev, RX_RING_SIZE);
	अन्यथा
		prपूर्णांकk(KERN_ERR "%s: Someone is busy refilling the RX ring\n",
		       ap->name);
	अगर (ap->version >= 2) अणु
		अगर (!test_and_set_bit(0, &ap->mini_refill_busy))
			ace_load_mini_rx_ring(dev, RX_MINI_SIZE);
		अन्यथा
			prपूर्णांकk(KERN_ERR "%s: Someone is busy refilling "
			       "the RX mini ring\n", ap->name);
	पूर्ण
	वापस 0;

 init_error:
	ace_init_cleanup(dev);
	वापस ecode;
पूर्ण


अटल व्योम ace_set_rxtx_parms(काष्ठा net_device *dev, पूर्णांक jumbo)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	पूर्णांक board_idx = ap->board_idx;

	अगर (board_idx >= 0) अणु
		अगर (!jumbo) अणु
			अगर (!tx_coal_tick[board_idx])
				ग_लिखोl(DEF_TX_COAL, &regs->TuneTxCoalTicks);
			अगर (!max_tx_desc[board_idx])
				ग_लिखोl(DEF_TX_MAX_DESC, &regs->TuneMaxTxDesc);
			अगर (!rx_coal_tick[board_idx])
				ग_लिखोl(DEF_RX_COAL, &regs->TuneRxCoalTicks);
			अगर (!max_rx_desc[board_idx])
				ग_लिखोl(DEF_RX_MAX_DESC, &regs->TuneMaxRxDesc);
			अगर (!tx_ratio[board_idx])
				ग_लिखोl(DEF_TX_RATIO, &regs->TxBufRat);
		पूर्ण अन्यथा अणु
			अगर (!tx_coal_tick[board_idx])
				ग_लिखोl(DEF_JUMBO_TX_COAL,
				       &regs->TuneTxCoalTicks);
			अगर (!max_tx_desc[board_idx])
				ग_लिखोl(DEF_JUMBO_TX_MAX_DESC,
				       &regs->TuneMaxTxDesc);
			अगर (!rx_coal_tick[board_idx])
				ग_लिखोl(DEF_JUMBO_RX_COAL,
				       &regs->TuneRxCoalTicks);
			अगर (!max_rx_desc[board_idx])
				ग_लिखोl(DEF_JUMBO_RX_MAX_DESC,
				       &regs->TuneMaxRxDesc);
			अगर (!tx_ratio[board_idx])
				ग_लिखोl(DEF_JUMBO_TX_RATIO, &regs->TxBufRat);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम ace_watchकरोg(काष्ठा net_device *data, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;

	/*
	 * We haven't received a stats update event क्रम more than 2.5
	 * seconds and there is data in the transmit queue, thus we
	 * assume the card is stuck.
	 */
	अगर (*ap->tx_csm != ap->tx_ret_csm) अणु
		prपूर्णांकk(KERN_WARNING "%s: Transmitter is stuck, %08x\n",
		       dev->name, (अचिन्हित पूर्णांक)पढ़ोl(&regs->HostCtrl));
		/* This can happen due to ieee flow control. */
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "%s: BUG... transmitter died. Kicking it.\n",
		       dev->name);
#अगर 0
		netअगर_wake_queue(dev);
#पूर्ण_अगर
	पूर्ण
पूर्ण


अटल व्योम ace_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ace_निजी *ap = from_tasklet(ap, t, ace_tasklet);
	काष्ठा net_device *dev = ap->ndev;
	पूर्णांक cur_size;

	cur_size = atomic_पढ़ो(&ap->cur_rx_bufs);
	अगर ((cur_size < RX_LOW_STD_THRES) &&
	    !test_and_set_bit(0, &ap->std_refill_busy)) अणु
#अगर_घोषित DEBUG
		prपूर्णांकk("refilling buffers (current %i)\n", cur_size);
#पूर्ण_अगर
		ace_load_std_rx_ring(dev, RX_RING_SIZE - cur_size);
	पूर्ण

	अगर (ap->version >= 2) अणु
		cur_size = atomic_पढ़ो(&ap->cur_mini_bufs);
		अगर ((cur_size < RX_LOW_MINI_THRES) &&
		    !test_and_set_bit(0, &ap->mini_refill_busy)) अणु
#अगर_घोषित DEBUG
			prपूर्णांकk("refilling mini buffers (current %i)\n",
			       cur_size);
#पूर्ण_अगर
			ace_load_mini_rx_ring(dev, RX_MINI_SIZE - cur_size);
		पूर्ण
	पूर्ण

	cur_size = atomic_पढ़ो(&ap->cur_jumbo_bufs);
	अगर (ap->jumbo && (cur_size < RX_LOW_JUMBO_THRES) &&
	    !test_and_set_bit(0, &ap->jumbo_refill_busy)) अणु
#अगर_घोषित DEBUG
		prपूर्णांकk("refilling jumbo buffers (current %i)\n", cur_size);
#पूर्ण_अगर
		ace_load_jumbo_rx_ring(dev, RX_JUMBO_SIZE - cur_size);
	पूर्ण
	ap->tasklet_pending = 0;
पूर्ण


/*
 * Copy the contents of the NIC's trace buffer to kernel memory.
 */
अटल व्योम ace_dump_trace(काष्ठा ace_निजी *ap)
अणु
#अगर 0
	अगर (!ap->trace_buf)
		अगर (!(ap->trace_buf = kदो_स्मृति(ACE_TRACE_SIZE, GFP_KERNEL)))
		    वापस;
#पूर्ण_अगर
पूर्ण


/*
 * Load the standard rx ring.
 *
 * Loading rings is safe without holding the spin lock since this is
 * करोne only beक्रमe the device is enabled, thus no पूर्णांकerrupts are
 * generated and by the पूर्णांकerrupt handler/tasklet handler.
 */
अटल व्योम ace_load_std_rx_ring(काष्ठा net_device *dev, पूर्णांक nr_bufs)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	लघु i, idx;


	prefetchw(&ap->cur_rx_bufs);

	idx = ap->rx_std_skbprd;

	क्रम (i = 0; i < nr_bufs; i++) अणु
		काष्ठा sk_buff *skb;
		काष्ठा rx_desc *rd;
		dma_addr_t mapping;

		skb = netdev_alloc_skb_ip_align(dev, ACE_STD_बफ_मानE);
		अगर (!skb)
			अवरोध;

		mapping = dma_map_page(&ap->pdev->dev,
				       virt_to_page(skb->data),
				       offset_in_page(skb->data),
				       ACE_STD_बफ_मानE, DMA_FROM_DEVICE);
		ap->skb->rx_std_skbuff[idx].skb = skb;
		dma_unmap_addr_set(&ap->skb->rx_std_skbuff[idx],
				   mapping, mapping);

		rd = &ap->rx_std_ring[idx];
		set_aceaddr(&rd->addr, mapping);
		rd->size = ACE_STD_बफ_मानE;
		rd->idx = idx;
		idx = (idx + 1) % RX_STD_RING_ENTRIES;
	पूर्ण

	अगर (!i)
		जाओ error_out;

	atomic_add(i, &ap->cur_rx_bufs);
	ap->rx_std_skbprd = idx;

	अगर (ACE_IS_TIGON_I(ap)) अणु
		काष्ठा cmd cmd;
		cmd.evt = C_SET_RX_PRD_IDX;
		cmd.code = 0;
		cmd.idx = ap->rx_std_skbprd;
		ace_issue_cmd(regs, &cmd);
	पूर्ण अन्यथा अणु
		ग_लिखोl(idx, &regs->RxStdPrd);
		wmb();
	पूर्ण

 out:
	clear_bit(0, &ap->std_refill_busy);
	वापस;

 error_out:
	prपूर्णांकk(KERN_INFO "Out of memory when allocating "
	       "standard receive buffers\n");
	जाओ out;
पूर्ण


अटल व्योम ace_load_mini_rx_ring(काष्ठा net_device *dev, पूर्णांक nr_bufs)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	लघु i, idx;

	prefetchw(&ap->cur_mini_bufs);

	idx = ap->rx_mini_skbprd;
	क्रम (i = 0; i < nr_bufs; i++) अणु
		काष्ठा sk_buff *skb;
		काष्ठा rx_desc *rd;
		dma_addr_t mapping;

		skb = netdev_alloc_skb_ip_align(dev, ACE_MINI_बफ_मानE);
		अगर (!skb)
			अवरोध;

		mapping = dma_map_page(&ap->pdev->dev,
				       virt_to_page(skb->data),
				       offset_in_page(skb->data),
				       ACE_MINI_बफ_मानE, DMA_FROM_DEVICE);
		ap->skb->rx_mini_skbuff[idx].skb = skb;
		dma_unmap_addr_set(&ap->skb->rx_mini_skbuff[idx],
				   mapping, mapping);

		rd = &ap->rx_mini_ring[idx];
		set_aceaddr(&rd->addr, mapping);
		rd->size = ACE_MINI_बफ_मानE;
		rd->idx = idx;
		idx = (idx + 1) % RX_MINI_RING_ENTRIES;
	पूर्ण

	अगर (!i)
		जाओ error_out;

	atomic_add(i, &ap->cur_mini_bufs);

	ap->rx_mini_skbprd = idx;

	ग_लिखोl(idx, &regs->RxMiniPrd);
	wmb();

 out:
	clear_bit(0, &ap->mini_refill_busy);
	वापस;
 error_out:
	prपूर्णांकk(KERN_INFO "Out of memory when allocating "
	       "mini receive buffers\n");
	जाओ out;
पूर्ण


/*
 * Load the jumbo rx ring, this may happen at any समय अगर the MTU
 * is changed to a value > 1500.
 */
अटल व्योम ace_load_jumbo_rx_ring(काष्ठा net_device *dev, पूर्णांक nr_bufs)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	लघु i, idx;

	idx = ap->rx_jumbo_skbprd;

	क्रम (i = 0; i < nr_bufs; i++) अणु
		काष्ठा sk_buff *skb;
		काष्ठा rx_desc *rd;
		dma_addr_t mapping;

		skb = netdev_alloc_skb_ip_align(dev, ACE_JUMBO_बफ_मानE);
		अगर (!skb)
			अवरोध;

		mapping = dma_map_page(&ap->pdev->dev,
				       virt_to_page(skb->data),
				       offset_in_page(skb->data),
				       ACE_JUMBO_बफ_मानE, DMA_FROM_DEVICE);
		ap->skb->rx_jumbo_skbuff[idx].skb = skb;
		dma_unmap_addr_set(&ap->skb->rx_jumbo_skbuff[idx],
				   mapping, mapping);

		rd = &ap->rx_jumbo_ring[idx];
		set_aceaddr(&rd->addr, mapping);
		rd->size = ACE_JUMBO_बफ_मानE;
		rd->idx = idx;
		idx = (idx + 1) % RX_JUMBO_RING_ENTRIES;
	पूर्ण

	अगर (!i)
		जाओ error_out;

	atomic_add(i, &ap->cur_jumbo_bufs);
	ap->rx_jumbo_skbprd = idx;

	अगर (ACE_IS_TIGON_I(ap)) अणु
		काष्ठा cmd cmd;
		cmd.evt = C_SET_RX_JUMBO_PRD_IDX;
		cmd.code = 0;
		cmd.idx = ap->rx_jumbo_skbprd;
		ace_issue_cmd(regs, &cmd);
	पूर्ण अन्यथा अणु
		ग_लिखोl(idx, &regs->RxJumboPrd);
		wmb();
	पूर्ण

 out:
	clear_bit(0, &ap->jumbo_refill_busy);
	वापस;
 error_out:
	अगर (net_ratelimit())
		prपूर्णांकk(KERN_INFO "Out of memory when allocating "
		       "jumbo receive buffers\n");
	जाओ out;
पूर्ण


/*
 * All events are considered to be slow (RX/TX पूर्णांकs करो not generate
 * events) and are handled here, outside the मुख्य पूर्णांकerrupt handler,
 * to reduce the size of the handler.
 */
अटल u32 ace_handle_event(काष्ठा net_device *dev, u32 evtcsm, u32 evtprd)
अणु
	काष्ठा ace_निजी *ap;

	ap = netdev_priv(dev);

	जबतक (evtcsm != evtprd) अणु
		चयन (ap->evt_ring[evtcsm].evt) अणु
		हाल E_FW_RUNNING:
			prपूर्णांकk(KERN_INFO "%s: Firmware up and running\n",
			       ap->name);
			ap->fw_running = 1;
			wmb();
			अवरोध;
		हाल E_STATS_UPDATED:
			अवरोध;
		हाल E_LNK_STATE:
		अणु
			u16 code = ap->evt_ring[evtcsm].code;
			चयन (code) अणु
			हाल E_C_LINK_UP:
			अणु
				u32 state = पढ़ोl(&ap->regs->GigLnkState);
				prपूर्णांकk(KERN_WARNING "%s: Optical link UP "
				       "(%s Duplex, Flow Control: %s%s)\n",
				       ap->name,
				       state & LNK_FULL_DUPLEX ? "Full":"Half",
				       state & LNK_TX_FLOW_CTL_Y ? "TX " : "",
				       state & LNK_RX_FLOW_CTL_Y ? "RX" : "");
				अवरोध;
			पूर्ण
			हाल E_C_LINK_DOWN:
				prपूर्णांकk(KERN_WARNING "%s: Optical link DOWN\n",
				       ap->name);
				अवरोध;
			हाल E_C_LINK_10_100:
				prपूर्णांकk(KERN_WARNING "%s: 10/100BaseT link "
				       "UP\n", ap->name);
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_ERR "%s: Unknown optical link "
				       "state %02x\n", ap->name, code);
			पूर्ण
			अवरोध;
		पूर्ण
		हाल E_ERROR:
			चयन(ap->evt_ring[evtcsm].code) अणु
			हाल E_C_ERR_INVAL_CMD:
				prपूर्णांकk(KERN_ERR "%s: invalid command error\n",
				       ap->name);
				अवरोध;
			हाल E_C_ERR_UNIMP_CMD:
				prपूर्णांकk(KERN_ERR "%s: unimplemented command "
				       "error\n", ap->name);
				अवरोध;
			हाल E_C_ERR_BAD_CFG:
				prपूर्णांकk(KERN_ERR "%s: bad config error\n",
				       ap->name);
				अवरोध;
			शेष:
				prपूर्णांकk(KERN_ERR "%s: unknown error %02x\n",
				       ap->name, ap->evt_ring[evtcsm].code);
			पूर्ण
			अवरोध;
		हाल E_RESET_JUMBO_RNG:
		अणु
			पूर्णांक i;
			क्रम (i = 0; i < RX_JUMBO_RING_ENTRIES; i++) अणु
				अगर (ap->skb->rx_jumbo_skbuff[i].skb) अणु
					ap->rx_jumbo_ring[i].size = 0;
					set_aceaddr(&ap->rx_jumbo_ring[i].addr, 0);
					dev_kमुक्त_skb(ap->skb->rx_jumbo_skbuff[i].skb);
					ap->skb->rx_jumbo_skbuff[i].skb = शून्य;
				पूर्ण
			पूर्ण

 			अगर (ACE_IS_TIGON_I(ap)) अणु
 				काष्ठा cmd cmd;
 				cmd.evt = C_SET_RX_JUMBO_PRD_IDX;
 				cmd.code = 0;
 				cmd.idx = 0;
 				ace_issue_cmd(ap->regs, &cmd);
 			पूर्ण अन्यथा अणु
 				ग_लिखोl(0, &((ap->regs)->RxJumboPrd));
 				wmb();
 			पूर्ण

			ap->jumbo = 0;
			ap->rx_jumbo_skbprd = 0;
			prपूर्णांकk(KERN_INFO "%s: Jumbo ring flushed\n",
			       ap->name);
			clear_bit(0, &ap->jumbo_refill_busy);
			अवरोध;
		पूर्ण
		शेष:
			prपूर्णांकk(KERN_ERR "%s: Unhandled event 0x%02x\n",
			       ap->name, ap->evt_ring[evtcsm].evt);
		पूर्ण
		evtcsm = (evtcsm + 1) % EVT_RING_ENTRIES;
	पूर्ण

	वापस evtcsm;
पूर्ण


अटल व्योम ace_rx_पूर्णांक(काष्ठा net_device *dev, u32 rxretprd, u32 rxretcsm)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	u32 idx;
	पूर्णांक mini_count = 0, std_count = 0;

	idx = rxretcsm;

	prefetchw(&ap->cur_rx_bufs);
	prefetchw(&ap->cur_mini_bufs);

	जबतक (idx != rxretprd) अणु
		काष्ठा ring_info *rip;
		काष्ठा sk_buff *skb;
		काष्ठा rx_desc *retdesc;
		u32 skbidx;
		पूर्णांक bd_flags, desc_type, mapsize;
		u16 csum;


		/* make sure the rx descriptor isn't पढ़ो beक्रमe rxretprd */
		अगर (idx == rxretcsm)
			rmb();

		retdesc = &ap->rx_वापस_ring[idx];
		skbidx = retdesc->idx;
		bd_flags = retdesc->flags;
		desc_type = bd_flags & (BD_FLG_JUMBO | BD_FLG_MINI);

		चयन(desc_type) अणु
			/*
			 * Normal frames करो not have any flags set
			 *
			 * Mini and normal frames arrive frequently,
			 * so use a local counter to aव्योम करोing
			 * atomic operations क्रम each packet arriving.
			 */
		हाल 0:
			rip = &ap->skb->rx_std_skbuff[skbidx];
			mapsize = ACE_STD_बफ_मानE;
			std_count++;
			अवरोध;
		हाल BD_FLG_JUMBO:
			rip = &ap->skb->rx_jumbo_skbuff[skbidx];
			mapsize = ACE_JUMBO_बफ_मानE;
			atomic_dec(&ap->cur_jumbo_bufs);
			अवरोध;
		हाल BD_FLG_MINI:
			rip = &ap->skb->rx_mini_skbuff[skbidx];
			mapsize = ACE_MINI_बफ_मानE;
			mini_count++;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "%s: unknown frame type (0x%02x) "
			       "returned by NIC\n", dev->name,
			       retdesc->flags);
			जाओ error;
		पूर्ण

		skb = rip->skb;
		rip->skb = शून्य;
		dma_unmap_page(&ap->pdev->dev, dma_unmap_addr(rip, mapping),
			       mapsize, DMA_FROM_DEVICE);
		skb_put(skb, retdesc->size);

		/*
		 * Fly baby, fly!
		 */
		csum = retdesc->tcp_udp_csum;

		skb->protocol = eth_type_trans(skb, dev);

		/*
		 * Instead of क्रमcing the poor tigon mips cpu to calculate
		 * pseuकरो hdr checksum, we करो this ourselves.
		 */
		अगर (bd_flags & BD_FLG_TCP_UDP_SUM) अणु
			skb->csum = htons(csum);
			skb->ip_summed = CHECKSUM_COMPLETE;
		पूर्ण अन्यथा अणु
			skb_checksum_none_निश्चित(skb);
		पूर्ण

		/* send it up */
		अगर ((bd_flags & BD_FLG_VLAN_TAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), retdesc->vlan);
		netअगर_rx(skb);

		dev->stats.rx_packets++;
		dev->stats.rx_bytes += retdesc->size;

		idx = (idx + 1) % RX_RETURN_RING_ENTRIES;
	पूर्ण

	atomic_sub(std_count, &ap->cur_rx_bufs);
	अगर (!ACE_IS_TIGON_I(ap))
		atomic_sub(mini_count, &ap->cur_mini_bufs);

 out:
	/*
	 * According to the करोcumentation RxRetCsm is obsolete with
	 * the 12.3.x Firmware - my Tigon I NICs seem to disagree!
	 */
	अगर (ACE_IS_TIGON_I(ap)) अणु
		ग_लिखोl(idx, &ap->regs->RxRetCsm);
	पूर्ण
	ap->cur_rx = idx;

	वापस;
 error:
	idx = rxretprd;
	जाओ out;
पूर्ण


अटल अंतरभूत व्योम ace_tx_पूर्णांक(काष्ठा net_device *dev,
			      u32 txcsm, u32 idx)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);

	करो अणु
		काष्ठा sk_buff *skb;
		काष्ठा tx_ring_info *info;

		info = ap->skb->tx_skbuff + idx;
		skb = info->skb;

		अगर (dma_unmap_len(info, maplen)) अणु
			dma_unmap_page(&ap->pdev->dev,
				       dma_unmap_addr(info, mapping),
				       dma_unmap_len(info, maplen),
				       DMA_TO_DEVICE);
			dma_unmap_len_set(info, maplen, 0);
		पूर्ण

		अगर (skb) अणु
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += skb->len;
			dev_consume_skb_irq(skb);
			info->skb = शून्य;
		पूर्ण

		idx = (idx + 1) % ACE_TX_RING_ENTRIES(ap);
	पूर्ण जबतक (idx != txcsm);

	अगर (netअगर_queue_stopped(dev))
		netअगर_wake_queue(dev);

	wmb();
	ap->tx_ret_csm = txcsm;

	/* So... tx_ret_csm is advanced _after_ check क्रम device wakeup.
	 *
	 * We could try to make it beक्रमe. In this हाल we would get
	 * the following race condition: hard_start_xmit on other cpu
	 * enters after we advanced tx_ret_csm and fills space,
	 * which we have just मुक्तd, so that we make illegal device wakeup.
	 * There is no good way to workaround this (at entry
	 * to ace_start_xmit detects this condition and prevents
	 * ring corruption, but it is not a good workaround.)
	 *
	 * When tx_ret_csm is advanced after, we wake up device _only_
	 * अगर we really have some space in ring (though the core करोing
	 * hard_start_xmit can see full ring क्रम some period and has to
	 * synchronize.) Superb.
	 * BUT! We get another subtle race condition. hard_start_xmit
	 * may think that ring is full between wakeup and advancing
	 * tx_ret_csm and will stop device instantly! It is not so bad.
	 * We are guaranteed that there is something in ring, so that
	 * the next irq will resume transmission. To speedup this we could
	 * mark descriptor, which बंदs ring with BD_FLG_COAL_NOW
	 * (see ace_start_xmit).
	 *
	 * Well, this dilemma exists in all lock-मुक्त devices.
	 * We, following scheme used in drivers by Donald Becker,
	 * select the least dangerous.
	 *							--ANK
	 */
पूर्ण


अटल irqवापस_t ace_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	u32 idx;
	u32 txcsm, rxretcsm, rxretprd;
	u32 evtcsm, evtprd;

	/*
	 * In हाल of PCI shared पूर्णांकerrupts or spurious पूर्णांकerrupts,
	 * we want to make sure it is actually our पूर्णांकerrupt beक्रमe
	 * spending any समय in here.
	 */
	अगर (!(पढ़ोl(&regs->HostCtrl) & IN_INT))
		वापस IRQ_NONE;

	/*
	 * ACK पूर्णांकr now. Otherwise we will lose updates to rx_ret_prd,
	 * which happened _after_ rxretprd = *ap->rx_ret_prd; but beक्रमe
	 * ग_लिखोl(0, &regs->Mb0Lo).
	 *
	 * "IRQ avoidance" recommended in करोcs applies to IRQs served
	 * thपढ़ोs and it is wrong even क्रम that हाल.
	 */
	ग_लिखोl(0, &regs->Mb0Lo);
	पढ़ोl(&regs->Mb0Lo);

	/*
	 * There is no conflict between transmit handling in
	 * start_xmit and receive processing, thus there is no reason
	 * to take a spin lock क्रम RX handling. Wait until we start
	 * working on the other stuff - hey we करोn't need a spin lock
	 * anymore.
	 */
	rxretprd = *ap->rx_ret_prd;
	rxretcsm = ap->cur_rx;

	अगर (rxretprd != rxretcsm)
		ace_rx_पूर्णांक(dev, rxretprd, rxretcsm);

	txcsm = *ap->tx_csm;
	idx = ap->tx_ret_csm;

	अगर (txcsm != idx) अणु
		/*
		 * If each skb takes only one descriptor this check degenerates
		 * to identity, because new space has just been खोलोed.
		 * But अगर skbs are fragmented we must check that this index
		 * update releases enough of space, otherwise we just
		 * रुको क्रम device to make more work.
		 */
		अगर (!tx_ring_full(ap, txcsm, ap->tx_prd))
			ace_tx_पूर्णांक(dev, txcsm, idx);
	पूर्ण

	evtcsm = पढ़ोl(&regs->EvtCsm);
	evtprd = *ap->evt_prd;

	अगर (evtcsm != evtprd) अणु
		evtcsm = ace_handle_event(dev, evtcsm, evtprd);
		ग_लिखोl(evtcsm, &regs->EvtCsm);
	पूर्ण

	/*
	 * This has to go last in the पूर्णांकerrupt handler and run with
	 * the spin lock released ... what lock?
	 */
	अगर (netअगर_running(dev)) अणु
		पूर्णांक cur_size;
		पूर्णांक run_tasklet = 0;

		cur_size = atomic_पढ़ो(&ap->cur_rx_bufs);
		अगर (cur_size < RX_LOW_STD_THRES) अणु
			अगर ((cur_size < RX_PANIC_STD_THRES) &&
			    !test_and_set_bit(0, &ap->std_refill_busy)) अणु
#अगर_घोषित DEBUG
				prपूर्णांकk("low on std buffers %i\n", cur_size);
#पूर्ण_अगर
				ace_load_std_rx_ring(dev,
						     RX_RING_SIZE - cur_size);
			पूर्ण अन्यथा
				run_tasklet = 1;
		पूर्ण

		अगर (!ACE_IS_TIGON_I(ap)) अणु
			cur_size = atomic_पढ़ो(&ap->cur_mini_bufs);
			अगर (cur_size < RX_LOW_MINI_THRES) अणु
				अगर ((cur_size < RX_PANIC_MINI_THRES) &&
				    !test_and_set_bit(0,
						      &ap->mini_refill_busy)) अणु
#अगर_घोषित DEBUG
					prपूर्णांकk("low on mini buffers %i\n",
					       cur_size);
#पूर्ण_अगर
					ace_load_mini_rx_ring(dev,
							      RX_MINI_SIZE - cur_size);
				पूर्ण अन्यथा
					run_tasklet = 1;
			पूर्ण
		पूर्ण

		अगर (ap->jumbo) अणु
			cur_size = atomic_पढ़ो(&ap->cur_jumbo_bufs);
			अगर (cur_size < RX_LOW_JUMBO_THRES) अणु
				अगर ((cur_size < RX_PANIC_JUMBO_THRES) &&
				    !test_and_set_bit(0,
						      &ap->jumbo_refill_busy))अणु
#अगर_घोषित DEBUG
					prपूर्णांकk("low on jumbo buffers %i\n",
					       cur_size);
#पूर्ण_अगर
					ace_load_jumbo_rx_ring(dev,
							       RX_JUMBO_SIZE - cur_size);
				पूर्ण अन्यथा
					run_tasklet = 1;
			पूर्ण
		पूर्ण
		अगर (run_tasklet && !ap->tasklet_pending) अणु
			ap->tasklet_pending = 1;
			tasklet_schedule(&ap->ace_tasklet);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ace_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	काष्ठा cmd cmd;

	अगर (!(ap->fw_running)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Firmware not running!\n", dev->name);
		वापस -EBUSY;
	पूर्ण

	ग_लिखोl(dev->mtu + ETH_HLEN + 4, &regs->IfMtu);

	cmd.evt = C_CLEAR_STATS;
	cmd.code = 0;
	cmd.idx = 0;
	ace_issue_cmd(regs, &cmd);

	cmd.evt = C_HOST_STATE;
	cmd.code = C_C_STACK_UP;
	cmd.idx = 0;
	ace_issue_cmd(regs, &cmd);

	अगर (ap->jumbo &&
	    !test_and_set_bit(0, &ap->jumbo_refill_busy))
		ace_load_jumbo_rx_ring(dev, RX_JUMBO_SIZE);

	अगर (dev->flags & IFF_PROMISC) अणु
		cmd.evt = C_SET_PROMISC_MODE;
		cmd.code = C_C_PROMISC_ENABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);

		ap->promisc = 1;
	पूर्णअन्यथा
		ap->promisc = 0;
	ap->mcast_all = 0;

#अगर 0
	cmd.evt = C_LNK_NEGOTIATION;
	cmd.code = 0;
	cmd.idx = 0;
	ace_issue_cmd(regs, &cmd);
#पूर्ण_अगर

	netअगर_start_queue(dev);

	/*
	 * Setup the bottom half rx ring refill handler
	 */
	tasklet_setup(&ap->ace_tasklet, ace_tasklet);
	वापस 0;
पूर्ण


अटल पूर्णांक ace_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	काष्ठा cmd cmd;
	अचिन्हित दीर्घ flags;
	लघु i;

	/*
	 * Without (or beक्रमe) releasing irq and stopping hardware, this
	 * is an असलolute non-sense, by the way. It will be reset instantly
	 * by the first irq.
	 */
	netअगर_stop_queue(dev);


	अगर (ap->promisc) अणु
		cmd.evt = C_SET_PROMISC_MODE;
		cmd.code = C_C_PROMISC_DISABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
		ap->promisc = 0;
	पूर्ण

	cmd.evt = C_HOST_STATE;
	cmd.code = C_C_STACK_DOWN;
	cmd.idx = 0;
	ace_issue_cmd(regs, &cmd);

	tasklet_समाप्त(&ap->ace_tasklet);

	/*
	 * Make sure one CPU is not processing packets जबतक
	 * buffers are being released by another.
	 */

	local_irq_save(flags);
	ace_mask_irq(dev);

	क्रम (i = 0; i < ACE_TX_RING_ENTRIES(ap); i++) अणु
		काष्ठा sk_buff *skb;
		काष्ठा tx_ring_info *info;

		info = ap->skb->tx_skbuff + i;
		skb = info->skb;

		अगर (dma_unmap_len(info, maplen)) अणु
			अगर (ACE_IS_TIGON_I(ap)) अणु
				/* NB: TIGON_1 is special, tx_ring is in io space */
				काष्ठा tx_desc __iomem *tx;
				tx = (__क्रमce काष्ठा tx_desc __iomem *) &ap->tx_ring[i];
				ग_लिखोl(0, &tx->addr.addrhi);
				ग_लिखोl(0, &tx->addr.addrlo);
				ग_लिखोl(0, &tx->flagsize);
			पूर्ण अन्यथा
				स_रखो(ap->tx_ring + i, 0,
				       माप(काष्ठा tx_desc));
			dma_unmap_page(&ap->pdev->dev,
				       dma_unmap_addr(info, mapping),
				       dma_unmap_len(info, maplen),
				       DMA_TO_DEVICE);
			dma_unmap_len_set(info, maplen, 0);
		पूर्ण
		अगर (skb) अणु
			dev_kमुक्त_skb(skb);
			info->skb = शून्य;
		पूर्ण
	पूर्ण

	अगर (ap->jumbo) अणु
		cmd.evt = C_RESET_JUMBO_RNG;
		cmd.code = 0;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
	पूर्ण

	ace_unmask_irq(dev);
	local_irq_restore(flags);

	वापस 0;
पूर्ण


अटल अंतरभूत dma_addr_t
ace_map_tx_skb(काष्ठा ace_निजी *ap, काष्ठा sk_buff *skb,
	       काष्ठा sk_buff *tail, u32 idx)
अणु
	dma_addr_t mapping;
	काष्ठा tx_ring_info *info;

	mapping = dma_map_page(&ap->pdev->dev, virt_to_page(skb->data),
			       offset_in_page(skb->data), skb->len,
			       DMA_TO_DEVICE);

	info = ap->skb->tx_skbuff + idx;
	info->skb = tail;
	dma_unmap_addr_set(info, mapping, mapping);
	dma_unmap_len_set(info, maplen, skb->len);
	वापस mapping;
पूर्ण


अटल अंतरभूत व्योम
ace_load_tx_bd(काष्ठा ace_निजी *ap, काष्ठा tx_desc *desc, u64 addr,
	       u32 flagsize, u32 vlan_tag)
अणु
#अगर !USE_TX_COAL_NOW
	flagsize &= ~BD_FLG_COAL_NOW;
#पूर्ण_अगर

	अगर (ACE_IS_TIGON_I(ap)) अणु
		काष्ठा tx_desc __iomem *io = (__क्रमce काष्ठा tx_desc __iomem *) desc;
		ग_लिखोl(addr >> 32, &io->addr.addrhi);
		ग_लिखोl(addr & 0xffffffff, &io->addr.addrlo);
		ग_लिखोl(flagsize, &io->flagsize);
		ग_लिखोl(vlan_tag, &io->vlanres);
	पूर्ण अन्यथा अणु
		desc->addr.addrhi = addr >> 32;
		desc->addr.addrlo = addr;
		desc->flagsize = flagsize;
		desc->vlanres = vlan_tag;
	पूर्ण
पूर्ण


अटल netdev_tx_t ace_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	काष्ठा tx_desc *desc;
	u32 idx, flagsize;
	अचिन्हित दीर्घ maxjअगरf = jअगरfies + 3*HZ;

restart:
	idx = ap->tx_prd;

	अगर (tx_ring_full(ap, ap->tx_ret_csm, idx))
		जाओ overflow;

	अगर (!skb_shinfo(skb)->nr_frags)	अणु
		dma_addr_t mapping;
		u32 vlan_tag = 0;

		mapping = ace_map_tx_skb(ap, skb, skb, idx);
		flagsize = (skb->len << 16) | (BD_FLG_END);
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			flagsize |= BD_FLG_TCP_UDP_SUM;
		अगर (skb_vlan_tag_present(skb)) अणु
			flagsize |= BD_FLG_VLAN_TAG;
			vlan_tag = skb_vlan_tag_get(skb);
		पूर्ण
		desc = ap->tx_ring + idx;
		idx = (idx + 1) % ACE_TX_RING_ENTRIES(ap);

		/* Look at ace_tx_पूर्णांक क्रम explanations. */
		अगर (tx_ring_full(ap, ap->tx_ret_csm, idx))
			flagsize |= BD_FLG_COAL_NOW;

		ace_load_tx_bd(ap, desc, mapping, flagsize, vlan_tag);
	पूर्ण अन्यथा अणु
		dma_addr_t mapping;
		u32 vlan_tag = 0;
		पूर्णांक i, len = 0;

		mapping = ace_map_tx_skb(ap, skb, शून्य, idx);
		flagsize = (skb_headlen(skb) << 16);
		अगर (skb->ip_summed == CHECKSUM_PARTIAL)
			flagsize |= BD_FLG_TCP_UDP_SUM;
		अगर (skb_vlan_tag_present(skb)) अणु
			flagsize |= BD_FLG_VLAN_TAG;
			vlan_tag = skb_vlan_tag_get(skb);
		पूर्ण

		ace_load_tx_bd(ap, ap->tx_ring + idx, mapping, flagsize, vlan_tag);

		idx = (idx + 1) % ACE_TX_RING_ENTRIES(ap);

		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
			काष्ठा tx_ring_info *info;

			len += skb_frag_size(frag);
			info = ap->skb->tx_skbuff + idx;
			desc = ap->tx_ring + idx;

			mapping = skb_frag_dma_map(&ap->pdev->dev, frag, 0,
						   skb_frag_size(frag),
						   DMA_TO_DEVICE);

			flagsize = skb_frag_size(frag) << 16;
			अगर (skb->ip_summed == CHECKSUM_PARTIAL)
				flagsize |= BD_FLG_TCP_UDP_SUM;
			idx = (idx + 1) % ACE_TX_RING_ENTRIES(ap);

			अगर (i == skb_shinfo(skb)->nr_frags - 1) अणु
				flagsize |= BD_FLG_END;
				अगर (tx_ring_full(ap, ap->tx_ret_csm, idx))
					flagsize |= BD_FLG_COAL_NOW;

				/*
				 * Only the last fragment मुक्तs
				 * the skb!
				 */
				info->skb = skb;
			पूर्ण अन्यथा अणु
				info->skb = शून्य;
			पूर्ण
			dma_unmap_addr_set(info, mapping, mapping);
			dma_unmap_len_set(info, maplen, skb_frag_size(frag));
			ace_load_tx_bd(ap, desc, mapping, flagsize, vlan_tag);
		पूर्ण
	पूर्ण

 	wmb();
 	ap->tx_prd = idx;
 	ace_set_txprd(regs, ap, idx);

	अगर (flagsize & BD_FLG_COAL_NOW) अणु
		netअगर_stop_queue(dev);

		/*
		 * A TX-descriptor producer (an IRQ) might have gotten
		 * between, making the ring मुक्त again. Since xmit is
		 * serialized, this is the only situation we have to
		 * re-test.
		 */
		अगर (!tx_ring_full(ap, ap->tx_ret_csm, idx))
			netअगर_wake_queue(dev);
	पूर्ण

	वापस NETDEV_TX_OK;

overflow:
	/*
	 * This race condition is unaव्योमable with lock-मुक्त drivers.
	 * We wake up the queue _beक्रमe_ tx_prd is advanced, so that we can
	 * enter hard_start_xmit too early, जबतक tx ring still looks बंदd.
	 * This happens ~1-4 बार per 100000 packets, so that we can allow
	 * to loop syncing to other CPU. Probably, we need an additional
	 * wmb() in ace_tx_पूर्णांकr as well.
	 *
	 * Note that this race is relieved by reserving one more entry
	 * in tx ring than it is necessary (see original non-SG driver).
	 * However, with SG we need to reserve 2*MAX_SKB_FRAGS+1, which
	 * is alपढ़ोy overसमाप्त.
	 *
	 * Alternative is to वापस with 1 not throttling queue. In this
	 * हाल loop becomes दीर्घer, no more useful effects.
	 */
	अगर (समय_beक्रमe(jअगरfies, maxjअगरf)) अणु
		barrier();
		cpu_relax();
		जाओ restart;
	पूर्ण

	/* The ring is stuck full. */
	prपूर्णांकk(KERN_WARNING "%s: Transmit ring stuck full\n", dev->name);
	वापस NETDEV_TX_BUSY;
पूर्ण


अटल पूर्णांक ace_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;

	ग_लिखोl(new_mtu + ETH_HLEN + 4, &regs->IfMtu);
	dev->mtu = new_mtu;

	अगर (new_mtu > ACE_STD_MTU) अणु
		अगर (!(ap->jumbo)) अणु
			prपूर्णांकk(KERN_INFO "%s: Enabling Jumbo frame "
			       "support\n", dev->name);
			ap->jumbo = 1;
			अगर (!test_and_set_bit(0, &ap->jumbo_refill_busy))
				ace_load_jumbo_rx_ring(dev, RX_JUMBO_SIZE);
			ace_set_rxtx_parms(dev, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (test_and_set_bit(0, &ap->jumbo_refill_busy));
		ace_sync_irq(dev->irq);
		ace_set_rxtx_parms(dev, 0);
		अगर (ap->jumbo) अणु
			काष्ठा cmd cmd;

			cmd.evt = C_RESET_JUMBO_RNG;
			cmd.code = 0;
			cmd.idx = 0;
			ace_issue_cmd(regs, &cmd);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ace_get_link_ksettings(काष्ठा net_device *dev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	u32 link;
	u32 supported;

	स_रखो(cmd, 0, माप(काष्ठा ethtool_link_ksettings));

	supported = (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
		     SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		     SUPPORTED_1000baseT_Half | SUPPORTED_1000baseT_Full |
		     SUPPORTED_Autoneg | SUPPORTED_FIBRE);

	cmd->base.port = PORT_FIBRE;

	link = पढ़ोl(&regs->GigLnkState);
	अगर (link & LNK_1000MB) अणु
		cmd->base.speed = SPEED_1000;
	पूर्ण अन्यथा अणु
		link = पढ़ोl(&regs->FastLnkState);
		अगर (link & LNK_100MB)
			cmd->base.speed = SPEED_100;
		अन्यथा अगर (link & LNK_10MB)
			cmd->base.speed = SPEED_10;
		अन्यथा
			cmd->base.speed = 0;
	पूर्ण
	अगर (link & LNK_FULL_DUPLEX)
		cmd->base.duplex = DUPLEX_FULL;
	अन्यथा
		cmd->base.duplex = DUPLEX_HALF;

	अगर (link & LNK_NEGOTIATE)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

#अगर 0
	/*
	 * Current काष्ठा ethtool_cmd is insufficient
	 */
	ecmd->trace = पढ़ोl(&regs->TuneTrace);

	ecmd->txcoal = पढ़ोl(&regs->TuneTxCoalTicks);
	ecmd->rxcoal = पढ़ोl(&regs->TuneRxCoalTicks);
#पूर्ण_अगर

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	वापस 0;
पूर्ण

अटल पूर्णांक ace_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	u32 link, speed;

	link = पढ़ोl(&regs->GigLnkState);
	अगर (link & LNK_1000MB)
		speed = SPEED_1000;
	अन्यथा अणु
		link = पढ़ोl(&regs->FastLnkState);
		अगर (link & LNK_100MB)
			speed = SPEED_100;
		अन्यथा अगर (link & LNK_10MB)
			speed = SPEED_10;
		अन्यथा
			speed = SPEED_100;
	पूर्ण

	link = LNK_ENABLE | LNK_1000MB | LNK_100MB | LNK_10MB |
		LNK_RX_FLOW_CTL_Y | LNK_NEG_FCTL;
	अगर (!ACE_IS_TIGON_I(ap))
		link |= LNK_TX_FLOW_CTL_Y;
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE)
		link |= LNK_NEGOTIATE;
	अगर (cmd->base.speed != speed) अणु
		link &= ~(LNK_1000MB | LNK_100MB | LNK_10MB);
		चयन (cmd->base.speed) अणु
		हाल SPEED_1000:
			link |= LNK_1000MB;
			अवरोध;
		हाल SPEED_100:
			link |= LNK_100MB;
			अवरोध;
		हाल SPEED_10:
			link |= LNK_10MB;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cmd->base.duplex == DUPLEX_FULL)
		link |= LNK_FULL_DUPLEX;

	अगर (link != ap->link) अणु
		काष्ठा cmd cmd;
		prपूर्णांकk(KERN_INFO "%s: Renegotiating link state\n",
		       dev->name);

		ap->link = link;
		ग_लिखोl(link, &regs->TuneLink);
		अगर (!ACE_IS_TIGON_I(ap))
			ग_लिखोl(link, &regs->TuneFastLink);
		wmb();

		cmd.evt = C_LNK_NEGOTIATION;
		cmd.code = 0;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ace_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);

	strlcpy(info->driver, "acenic", माप(info->driver));
	snम_लिखो(info->fw_version, माप(info->version), "%i.%i.%i",
		 ap->firmware_major, ap->firmware_minor, ap->firmware_fix);

	अगर (ap->pdev)
		strlcpy(info->bus_info, pci_name(ap->pdev),
			माप(info->bus_info));

पूर्ण

/*
 * Set the hardware MAC address.
 */
अटल पूर्णांक ace_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	काष्ठा sockaddr *addr=p;
	u8 *da;
	काष्ठा cmd cmd;

	अगर(netअगर_running(dev))
		वापस -EBUSY;

	स_नकल(dev->dev_addr, addr->sa_data,dev->addr_len);

	da = (u8 *)dev->dev_addr;

	ग_लिखोl(da[0] << 8 | da[1], &regs->MacAddrHi);
	ग_लिखोl((da[2] << 24) | (da[3] << 16) | (da[4] << 8) | da[5],
	       &regs->MacAddrLo);

	cmd.evt = C_SET_MAC_ADDR;
	cmd.code = 0;
	cmd.idx = 0;
	ace_issue_cmd(regs, &cmd);

	वापस 0;
पूर्ण


अटल व्योम ace_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	काष्ठा cmd cmd;

	अगर ((dev->flags & IFF_ALLMULTI) && !(ap->mcast_all)) अणु
		cmd.evt = C_SET_MULTICAST_MODE;
		cmd.code = C_C_MCAST_ENABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
		ap->mcast_all = 1;
	पूर्ण अन्यथा अगर (ap->mcast_all) अणु
		cmd.evt = C_SET_MULTICAST_MODE;
		cmd.code = C_C_MCAST_DISABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
		ap->mcast_all = 0;
	पूर्ण

	अगर ((dev->flags & IFF_PROMISC) && !(ap->promisc)) अणु
		cmd.evt = C_SET_PROMISC_MODE;
		cmd.code = C_C_PROMISC_ENABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
		ap->promisc = 1;
	पूर्णअन्यथा अगर (!(dev->flags & IFF_PROMISC) && (ap->promisc)) अणु
		cmd.evt = C_SET_PROMISC_MODE;
		cmd.code = C_C_PROMISC_DISABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
		ap->promisc = 0;
	पूर्ण

	/*
	 * For the समय being multicast relies on the upper layers
	 * filtering it properly. The Firmware करोes not allow one to
	 * set the entire multicast list at a समय and keeping track of
	 * it here is going to be messy.
	 */
	अगर (!netdev_mc_empty(dev) && !ap->mcast_all) अणु
		cmd.evt = C_SET_MULTICAST_MODE;
		cmd.code = C_C_MCAST_ENABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
	पूर्णअन्यथा अगर (!ap->mcast_all) अणु
		cmd.evt = C_SET_MULTICAST_MODE;
		cmd.code = C_C_MCAST_DISABLE;
		cmd.idx = 0;
		ace_issue_cmd(regs, &cmd);
	पूर्ण
पूर्ण


अटल काष्ठा net_device_stats *ace_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_mac_stats __iomem *mac_stats =
		(काष्ठा ace_mac_stats __iomem *)ap->regs->Stats;

	dev->stats.rx_missed_errors = पढ़ोl(&mac_stats->drop_space);
	dev->stats.multicast = पढ़ोl(&mac_stats->kept_mc);
	dev->stats.collisions = पढ़ोl(&mac_stats->coll);

	वापस &dev->stats;
पूर्ण


अटल व्योम ace_copy(काष्ठा ace_regs __iomem *regs, स्थिर __be32 *src,
		     u32 dest, पूर्णांक size)
अणु
	व्योम __iomem *tdest;
	लघु tsize, i;

	अगर (size <= 0)
		वापस;

	जबतक (size > 0) अणु
		tsize = min_t(u32, ((~dest & (ACE_WINDOW_SIZE - 1)) + 1),
			    min_t(u32, size, ACE_WINDOW_SIZE));
		tdest = (व्योम __iomem *) &regs->Winकरोw +
			(dest & (ACE_WINDOW_SIZE - 1));
		ग_लिखोl(dest & ~(ACE_WINDOW_SIZE - 1), &regs->WinBase);
		क्रम (i = 0; i < (tsize / 4); i++) अणु
			/* Firmware is big-endian */
			ग_लिखोl(be32_to_cpup(src), tdest);
			src++;
			tdest += 4;
			dest += 4;
			size -= 4;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम ace_clear(काष्ठा ace_regs __iomem *regs, u32 dest, पूर्णांक size)
अणु
	व्योम __iomem *tdest;
	लघु tsize = 0, i;

	अगर (size <= 0)
		वापस;

	जबतक (size > 0) अणु
		tsize = min_t(u32, ((~dest & (ACE_WINDOW_SIZE - 1)) + 1),
				min_t(u32, size, ACE_WINDOW_SIZE));
		tdest = (व्योम __iomem *) &regs->Winकरोw +
			(dest & (ACE_WINDOW_SIZE - 1));
		ग_लिखोl(dest & ~(ACE_WINDOW_SIZE - 1), &regs->WinBase);

		क्रम (i = 0; i < (tsize / 4); i++) अणु
			ग_लिखोl(0, tdest + i*4);
		पूर्ण

		dest += tsize;
		size -= tsize;
	पूर्ण
पूर्ण


/*
 * Download the firmware पूर्णांकo the SRAM on the NIC
 *
 * This operation requires the NIC to be halted and is perक्रमmed with
 * पूर्णांकerrupts disabled and with the spinlock hold.
 */
अटल पूर्णांक ace_load_firmware(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fw_name = "acenic/tg2.bin";
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	स्थिर __be32 *fw_data;
	u32 load_addr;
	पूर्णांक ret;

	अगर (!(पढ़ोl(&regs->CpuCtrl) & CPU_HALTED)) अणु
		prपूर्णांकk(KERN_ERR "%s: trying to download firmware while the "
		       "CPU is running!\n", ap->name);
		वापस -EFAULT;
	पूर्ण

	अगर (ACE_IS_TIGON_I(ap))
		fw_name = "acenic/tg1.bin";

	ret = request_firmware(&fw, fw_name, &ap->pdev->dev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to load firmware \"%s\"\n",
		       ap->name, fw_name);
		वापस ret;
	पूर्ण

	fw_data = (व्योम *)fw->data;

	/* Firmware blob starts with version numbers, followed by
	   load and start address. Reमुख्यder is the blob to be loaded
	   contiguously from load address. We करोn't bother to represent
	   the BSS/SBSS sections any more, since we were clearing the
	   whole thing anyway. */
	ap->firmware_major = fw->data[0];
	ap->firmware_minor = fw->data[1];
	ap->firmware_fix = fw->data[2];

	ap->firmware_start = be32_to_cpu(fw_data[1]);
	अगर (ap->firmware_start < 0x4000 || ap->firmware_start >= 0x80000) अणु
		prपूर्णांकk(KERN_ERR "%s: bogus load address %08x in \"%s\"\n",
		       ap->name, ap->firmware_start, fw_name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	load_addr = be32_to_cpu(fw_data[2]);
	अगर (load_addr < 0x4000 || load_addr >= 0x80000) अणु
		prपूर्णांकk(KERN_ERR "%s: bogus load address %08x in \"%s\"\n",
		       ap->name, load_addr, fw_name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Do not try to clear more than 512KiB or we end up seeing
	 * funny things on NICs with only 512KiB SRAM
	 */
	ace_clear(regs, 0x2000, 0x80000-0x2000);
	ace_copy(regs, &fw_data[3], load_addr, fw->size-12);
 out:
	release_firmware(fw);
	वापस ret;
पूर्ण


/*
 * The eeprom on the AceNIC is an Aपंचांगel i2c EEPROM.
 *
 * Accessing the EEPROM is `पूर्णांकeresting' to say the least - don't पढ़ो
 * this code right after dinner.
 *
 * This is all about black magic and bit-banging the device .... I
 * wonder in what hospital they have put the guy who deचिन्हित the i2c
 * specs.
 *
 * Oh yes, this is only the beginning!
 *
 * Thanks to Stevarino Webinski क्रम helping tracking करोwn the bugs in the
 * code i2c पढ़ोout code by beta testing all my hacks.
 */
अटल व्योम eeprom_start(काष्ठा ace_regs __iomem *regs)
अणु
	u32 local;

	पढ़ोl(&regs->LocalCtrl);
	udelay(ACE_SHORT_DELAY);
	local = पढ़ोl(&regs->LocalCtrl);
	local |= EEPROM_DATA_OUT | EEPROM_WRITE_ENABLE;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	local |= EEPROM_CLK_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	local &= ~EEPROM_DATA_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	local &= ~EEPROM_CLK_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
पूर्ण


अटल व्योम eeprom_prep(काष्ठा ace_regs __iomem *regs, u8 magic)
अणु
	लघु i;
	u32 local;

	udelay(ACE_SHORT_DELAY);
	local = पढ़ोl(&regs->LocalCtrl);
	local &= ~EEPROM_DATA_OUT;
	local |= EEPROM_WRITE_ENABLE;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();

	क्रम (i = 0; i < 8; i++, magic <<= 1) अणु
		udelay(ACE_SHORT_DELAY);
		अगर (magic & 0x80)
			local |= EEPROM_DATA_OUT;
		अन्यथा
			local &= ~EEPROM_DATA_OUT;
		ग_लिखोl(local, &regs->LocalCtrl);
		पढ़ोl(&regs->LocalCtrl);
		mb();

		udelay(ACE_SHORT_DELAY);
		local |= EEPROM_CLK_OUT;
		ग_लिखोl(local, &regs->LocalCtrl);
		पढ़ोl(&regs->LocalCtrl);
		mb();
		udelay(ACE_SHORT_DELAY);
		local &= ~(EEPROM_CLK_OUT | EEPROM_DATA_OUT);
		ग_लिखोl(local, &regs->LocalCtrl);
		पढ़ोl(&regs->LocalCtrl);
		mb();
	पूर्ण
पूर्ण


अटल पूर्णांक eeprom_check_ack(काष्ठा ace_regs __iomem *regs)
अणु
	पूर्णांक state;
	u32 local;

	local = पढ़ोl(&regs->LocalCtrl);
	local &= ~EEPROM_WRITE_ENABLE;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_LONG_DELAY);
	local |= EEPROM_CLK_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	/* sample data in middle of high clk */
	state = (पढ़ोl(&regs->LocalCtrl) & EEPROM_DATA_IN) != 0;
	udelay(ACE_SHORT_DELAY);
	mb();
	ग_लिखोl(पढ़ोl(&regs->LocalCtrl) & ~EEPROM_CLK_OUT, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();

	वापस state;
पूर्ण


अटल व्योम eeprom_stop(काष्ठा ace_regs __iomem *regs)
अणु
	u32 local;

	udelay(ACE_SHORT_DELAY);
	local = पढ़ोl(&regs->LocalCtrl);
	local |= EEPROM_WRITE_ENABLE;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	local &= ~EEPROM_DATA_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	local |= EEPROM_CLK_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	local |= EEPROM_DATA_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_LONG_DELAY);
	local &= ~EEPROM_CLK_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	mb();
पूर्ण


/*
 * Read a whole byte from the EEPROM.
 */
अटल पूर्णांक पढ़ो_eeprom_byte(काष्ठा net_device *dev, अचिन्हित दीर्घ offset)
अणु
	काष्ठा ace_निजी *ap = netdev_priv(dev);
	काष्ठा ace_regs __iomem *regs = ap->regs;
	अचिन्हित दीर्घ flags;
	u32 local;
	पूर्णांक result = 0;
	लघु i;

	/*
	 * Don't take पूर्णांकerrupts on this CPU will bit banging
	 * the %#%#@$ I2C device
	 */
	local_irq_save(flags);

	eeprom_start(regs);

	eeprom_prep(regs, EEPROM_WRITE_SELECT);
	अगर (eeprom_check_ack(regs)) अणु
		local_irq_restore(flags);
		prपूर्णांकk(KERN_ERR "%s: Unable to sync eeprom\n", ap->name);
		result = -EIO;
		जाओ eeprom_पढ़ो_error;
	पूर्ण

	eeprom_prep(regs, (offset >> 8) & 0xff);
	अगर (eeprom_check_ack(regs)) अणु
		local_irq_restore(flags);
		prपूर्णांकk(KERN_ERR "%s: Unable to set address byte 0\n",
		       ap->name);
		result = -EIO;
		जाओ eeprom_पढ़ो_error;
	पूर्ण

	eeprom_prep(regs, offset & 0xff);
	अगर (eeprom_check_ack(regs)) अणु
		local_irq_restore(flags);
		prपूर्णांकk(KERN_ERR "%s: Unable to set address byte 1\n",
		       ap->name);
		result = -EIO;
		जाओ eeprom_पढ़ो_error;
	पूर्ण

	eeprom_start(regs);
	eeprom_prep(regs, EEPROM_READ_SELECT);
	अगर (eeprom_check_ack(regs)) अणु
		local_irq_restore(flags);
		prपूर्णांकk(KERN_ERR "%s: Unable to set READ_SELECT\n",
		       ap->name);
		result = -EIO;
		जाओ eeprom_पढ़ो_error;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		local = पढ़ोl(&regs->LocalCtrl);
		local &= ~EEPROM_WRITE_ENABLE;
		ग_लिखोl(local, &regs->LocalCtrl);
		पढ़ोl(&regs->LocalCtrl);
		udelay(ACE_LONG_DELAY);
		mb();
		local |= EEPROM_CLK_OUT;
		ग_लिखोl(local, &regs->LocalCtrl);
		पढ़ोl(&regs->LocalCtrl);
		mb();
		udelay(ACE_SHORT_DELAY);
		/* sample data mid high clk */
		result = (result << 1) |
			((पढ़ोl(&regs->LocalCtrl) & EEPROM_DATA_IN) != 0);
		udelay(ACE_SHORT_DELAY);
		mb();
		local = पढ़ोl(&regs->LocalCtrl);
		local &= ~EEPROM_CLK_OUT;
		ग_लिखोl(local, &regs->LocalCtrl);
		पढ़ोl(&regs->LocalCtrl);
		udelay(ACE_SHORT_DELAY);
		mb();
		अगर (i == 7) अणु
			local |= EEPROM_WRITE_ENABLE;
			ग_लिखोl(local, &regs->LocalCtrl);
			पढ़ोl(&regs->LocalCtrl);
			mb();
			udelay(ACE_SHORT_DELAY);
		पूर्ण
	पूर्ण

	local |= EEPROM_DATA_OUT;
	ग_लिखोl(local, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	ग_लिखोl(पढ़ोl(&regs->LocalCtrl) | EEPROM_CLK_OUT, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	udelay(ACE_LONG_DELAY);
	ग_लिखोl(पढ़ोl(&regs->LocalCtrl) & ~EEPROM_CLK_OUT, &regs->LocalCtrl);
	पढ़ोl(&regs->LocalCtrl);
	mb();
	udelay(ACE_SHORT_DELAY);
	eeprom_stop(regs);

	local_irq_restore(flags);
 out:
	वापस result;

 eeprom_पढ़ो_error:
	prपूर्णांकk(KERN_ERR "%s: Unable to read eeprom byte 0x%02lx\n",
	       ap->name, offset);
	जाओ out;
पूर्ण

module_pci_driver(acenic_pci_driver);
