<शैली गुरु>
/*****************************************************************************
 *                                                                           *
 * File: pm3393.c                                                            *
 * $Revision: 1.16 $                                                         *
 * $Date: 2005/05/14 00:59:32 $                                              *
 * Description:                                                              *
 *  PMC/SIERRA (pm3393) MAC-PHY functionality.                               *
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

#समावेश "common.h"
#समावेश "regs.h"
#समावेश "gmac.h"
#समावेश "elmer0.h"
#समावेश "suni1x10gexp_regs.h"

#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>

#घोषणा OFFSET(REG_ADDR)    ((REG_ADDR) << 2)

#घोषणा IPG 12
#घोषणा TXXG_CONF1_VAL ((IPG << SUNI1x10GEXP_BITOFF_TXXG_IPGT) | \
	SUNI1x10GEXP_BITMSK_TXXG_32BIT_ALIGN | SUNI1x10GEXP_BITMSK_TXXG_CRCEN | \
	SUNI1x10GEXP_BITMSK_TXXG_PADEN)
#घोषणा RXXG_CONF1_VAL (SUNI1x10GEXP_BITMSK_RXXG_PUREP | 0x14 | \
	SUNI1x10GEXP_BITMSK_RXXG_FLCHK | SUNI1x10GEXP_BITMSK_RXXG_CRC_STRIP)

/* Update statistics every 15 minutes */
#घोषणा STATS_TICK_SECS (15 * 60)

क्रमागत अणु                     /* RMON रेजिस्टरs */
	RxOctetsReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_1_LOW,
	RxUnicastFramesReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_4_LOW,
	RxMulticastFramesReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_5_LOW,
	RxBroadcastFramesReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_6_LOW,
	RxPAUSEMACCtrlFramesReceived = SUNI1x10GEXP_REG_MSTAT_COUNTER_8_LOW,
	RxFrameCheckSequenceErrors = SUNI1x10GEXP_REG_MSTAT_COUNTER_10_LOW,
	RxFramesLostDueToInternalMACErrors = SUNI1x10GEXP_REG_MSTAT_COUNTER_11_LOW,
	RxSymbolErrors = SUNI1x10GEXP_REG_MSTAT_COUNTER_12_LOW,
	RxInRangeLengthErrors = SUNI1x10GEXP_REG_MSTAT_COUNTER_13_LOW,
	RxFramesTooLongErrors = SUNI1x10GEXP_REG_MSTAT_COUNTER_15_LOW,
	RxJabbers = SUNI1x10GEXP_REG_MSTAT_COUNTER_16_LOW,
	RxFragments = SUNI1x10GEXP_REG_MSTAT_COUNTER_17_LOW,
	RxUndersizedFrames =  SUNI1x10GEXP_REG_MSTAT_COUNTER_18_LOW,
	RxJumboFramesReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_25_LOW,
	RxJumboOctetsReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_26_LOW,

	TxOctetsTransmittedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_33_LOW,
	TxFramesLostDueToInternalMACTransmissionError = SUNI1x10GEXP_REG_MSTAT_COUNTER_35_LOW,
	TxTransmitSystemError = SUNI1x10GEXP_REG_MSTAT_COUNTER_36_LOW,
	TxUnicastFramesTransmittedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_38_LOW,
	TxMulticastFramesTransmittedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_40_LOW,
	TxBroadcastFramesTransmittedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_42_LOW,
	TxPAUSEMACCtrlFramesTransmitted = SUNI1x10GEXP_REG_MSTAT_COUNTER_43_LOW,
	TxJumboFramesReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_51_LOW,
	TxJumboOctetsReceivedOK = SUNI1x10GEXP_REG_MSTAT_COUNTER_52_LOW
पूर्ण;

काष्ठा _cmac_instance अणु
	u8 enabled;
	u8 fc;
	u8 mac_addr[6];
पूर्ण;

अटल पूर्णांक pmपढ़ो(काष्ठा cmac *cmac, u32 reg, u32 * data32)
अणु
	t1_tpi_पढ़ो(cmac->adapter, OFFSET(reg), data32);
	वापस 0;
पूर्ण

अटल पूर्णांक pmग_लिखो(काष्ठा cmac *cmac, u32 reg, u32 data32)
अणु
	t1_tpi_ग_लिखो(cmac->adapter, OFFSET(reg), data32);
	वापस 0;
पूर्ण

/* Port reset. */
अटल पूर्णांक pm3393_reset(काष्ठा cmac *cmac)
अणु
	वापस 0;
पूर्ण

/*
 * Enable पूर्णांकerrupts क्रम the PM3393
 *
 *	1. Enable PM3393 BLOCK पूर्णांकerrupts.
 *	2. Enable PM3393 Master Interrupt bit(INTE)
 *	3. Enable ELMER's PM3393 bit.
 *	4. Enable Terminator बाह्यal पूर्णांकerrupt.
 */
अटल पूर्णांक pm3393_पूर्णांकerrupt_enable(काष्ठा cmac *cmac)
अणु
	u32 pl_पूर्णांकr;

	/* PM3393 - Enabling all hardware block पूर्णांकerrupts.
	 */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_ENABLE, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_XRF_INTERRUPT_ENABLE, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_ENABLE, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXOAM_INTERRUPT_ENABLE, 0xffff);

	/* Don't पूर्णांकerrupt on statistics overflow, we are polling */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_0, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_1, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_2, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_3, 0);

	pmग_लिखो(cmac, SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_ENABLE, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_PL4ODP_INTERRUPT_MASK, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_XTEF_INTERRUPT_ENABLE, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXOAM_INTERRUPT_ENABLE, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_3, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_MASK, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_3, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_PL4IDU_INTERRUPT_MASK, 0xffff);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_ENABLE, 0xffff);

	/* PM3393 - Global पूर्णांकerrupt enable
	 */
	/* TBD XXX Disable क्रम now until we figure out why error पूर्णांकerrupts keep निश्चितing. */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_GLOBAL_INTERRUPT_ENABLE,
		0 /*SUNI1x10GEXP_BITMSK_TOP_INTE */ );

	/* TERMINATOR - PL_INTERUPTS_EXT */
	pl_पूर्णांकr = पढ़ोl(cmac->adapter->regs + A_PL_ENABLE);
	pl_पूर्णांकr |= F_PL_INTR_EXT;
	ग_लिखोl(pl_पूर्णांकr, cmac->adapter->regs + A_PL_ENABLE);
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_पूर्णांकerrupt_disable(काष्ठा cmac *cmac)
अणु
	u32 elmer;

	/* PM3393 - Enabling HW पूर्णांकerrupt blocks. */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_ENABLE, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_XRF_INTERRUPT_ENABLE, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_ENABLE, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXOAM_INTERRUPT_ENABLE, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_0, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_1, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_2, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_INTERRUPT_MASK_3, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_ENABLE, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_PL4ODP_INTERRUPT_MASK, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_XTEF_INTERRUPT_ENABLE, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXOAM_INTERRUPT_ENABLE, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_3, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_MASK, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_3, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_PL4IDU_INTERRUPT_MASK, 0);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_ENABLE, 0);

	/* PM3393 - Global पूर्णांकerrupt enable */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_GLOBAL_INTERRUPT_ENABLE, 0);

	/* ELMER - External chip पूर्णांकerrupts. */
	t1_tpi_पढ़ो(cmac->adapter, A_ELMER0_INT_ENABLE, &elmer);
	elmer &= ~ELMER0_GP_BIT1;
	t1_tpi_ग_लिखो(cmac->adapter, A_ELMER0_INT_ENABLE, elmer);

	/* TERMINATOR - PL_INTERUPTS_EXT */
	/* DO NOT DISABLE TERMINATOR's EXTERNAL INTERRUPTS. ANOTHER CHIP
	 * COULD WANT THEM ENABLED. We disable PM3393 at the ELMER level.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_पूर्णांकerrupt_clear(काष्ठा cmac *cmac)
अणु
	u32 elmer;
	u32 pl_पूर्णांकr;
	u32 val32;

	/* PM3393 - Clearing HW पूर्णांकerrupt blocks. Note, this assumes
	 *          bit WCIMODE=0 क्रम a clear-on-पढ़ो.
	 */
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_SERDES_3125_INTERRUPT_STATUS, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_XRF_INTERRUPT_STATUS, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_XRF_DIAG_INTERRUPT_STATUS, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_RXOAM_INTERRUPT_STATUS, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_PL4ODP_INTERRUPT, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_XTEF_INTERRUPT_STATUS, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_IFLX_FIFO_OVERFLOW_INTERRUPT, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_TXOAM_INTERRUPT_STATUS, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_RXXG_INTERRUPT, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_TXXG_INTERRUPT, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_PL4IDU_INTERRUPT, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_EFLX_FIFO_OVERFLOW_ERROR_INDICATION,
	       &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_STATUS, &val32);
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_PL4IO_LOCK_DETECT_CHANGE, &val32);

	/* PM3393 - Global पूर्णांकerrupt status
	 */
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_MASTER_INTERRUPT_STATUS, &val32);

	/* ELMER - External chip पूर्णांकerrupts.
	 */
	t1_tpi_पढ़ो(cmac->adapter, A_ELMER0_INT_CAUSE, &elmer);
	elmer |= ELMER0_GP_BIT1;
	t1_tpi_ग_लिखो(cmac->adapter, A_ELMER0_INT_CAUSE, elmer);

	/* TERMINATOR - PL_INTERUPTS_EXT
	 */
	pl_पूर्णांकr = पढ़ोl(cmac->adapter->regs + A_PL_CAUSE);
	pl_पूर्णांकr |= F_PL_INTR_EXT;
	ग_लिखोl(pl_पूर्णांकr, cmac->adapter->regs + A_PL_CAUSE);

	वापस 0;
पूर्ण

/* Interrupt handler */
अटल पूर्णांक pm3393_पूर्णांकerrupt_handler(काष्ठा cmac *cmac)
अणु
	u32 master_पूर्णांकr_status;

	/* Read the master पूर्णांकerrupt status रेजिस्टर. */
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_MASTER_INTERRUPT_STATUS,
	       &master_पूर्णांकr_status);
	अगर (netअगर_msg_पूर्णांकr(cmac->adapter))
		dev_dbg(&cmac->adapter->pdev->dev, "PM3393 intr cause 0x%x\n",
			master_पूर्णांकr_status);

	/* TBD XXX Lets just clear everything क्रम now */
	pm3393_पूर्णांकerrupt_clear(cmac);

	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_enable(काष्ठा cmac *cmac, पूर्णांक which)
अणु
	अगर (which & MAC_सूचीECTION_RX)
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_1,
			(RXXG_CONF1_VAL | SUNI1x10GEXP_BITMSK_RXXG_RXEN));

	अगर (which & MAC_सूचीECTION_TX) अणु
		u32 val = TXXG_CONF1_VAL | SUNI1x10GEXP_BITMSK_TXXG_TXEN0;

		अगर (cmac->instance->fc & PAUSE_RX)
			val |= SUNI1x10GEXP_BITMSK_TXXG_FCRX;
		अगर (cmac->instance->fc & PAUSE_TX)
			val |= SUNI1x10GEXP_BITMSK_TXXG_FCTX;
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_1, val);
	पूर्ण

	cmac->instance->enabled |= which;
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_enable_port(काष्ठा cmac *cmac, पूर्णांक which)
अणु
	/* Clear port statistics */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_MSTAT_CONTROL,
		SUNI1x10GEXP_BITMSK_MSTAT_CLEAR);
	udelay(2);
	स_रखो(&cmac->stats, 0, माप(काष्ठा cmac_statistics));

	pm3393_enable(cmac, which);

	/*
	 * XXX This should be करोne by the PHY and preferably not at all.
	 * The PHY करोesn't give us link status indication on its own so have
	 * the link management code query it instead.
	 */
	t1_link_changed(cmac->adapter, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_disable(काष्ठा cmac *cmac, पूर्णांक which)
अणु
	अगर (which & MAC_सूचीECTION_RX)
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_1, RXXG_CONF1_VAL);
	अगर (which & MAC_सूचीECTION_TX)
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_1, TXXG_CONF1_VAL);

	/*
	 * The disable is graceful. Give the PM3393 समय.  Can't रुको very
	 * दीर्घ here, we may be holding locks.
	 */
	udelay(20);

	cmac->instance->enabled &= ~which;
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_loopback_enable(काष्ठा cmac *cmac)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_loopback_disable(काष्ठा cmac *cmac)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_set_mtu(काष्ठा cmac *cmac, पूर्णांक mtu)
अणु
	पूर्णांक enabled = cmac->instance->enabled;

	mtu += ETH_HLEN + ETH_FCS_LEN;

	/* Disable Rx/Tx MAC beक्रमe configuring it. */
	अगर (enabled)
		pm3393_disable(cmac, MAC_सूचीECTION_RX | MAC_सूचीECTION_TX);

	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MAX_FRAME_LENGTH, mtu);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_MAX_FRAME_SIZE, mtu);

	अगर (enabled)
		pm3393_enable(cmac, enabled);
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_set_rx_mode(काष्ठा cmac *cmac, काष्ठा t1_rx_mode *rm)
अणु
	पूर्णांक enabled = cmac->instance->enabled & MAC_सूचीECTION_RX;
	u32 rx_mode;

	/* Disable MAC RX beक्रमe reconfiguring it */
	अगर (enabled)
		pm3393_disable(cmac, MAC_सूचीECTION_RX);

	pmपढ़ो(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_2, &rx_mode);
	rx_mode &= ~(SUNI1x10GEXP_BITMSK_RXXG_PMODE |
		     SUNI1x10GEXP_BITMSK_RXXG_MHASH_EN);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_2,
		(u16)rx_mode);

	अगर (t1_rx_mode_promisc(rm)) अणु
		/* Promiscuous mode. */
		rx_mode |= SUNI1x10GEXP_BITMSK_RXXG_PMODE;
	पूर्ण
	अगर (t1_rx_mode_allmulti(rm)) अणु
		/* Accept all multicast. */
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_LOW, 0xffff);
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDLOW, 0xffff);
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDHIGH, 0xffff);
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_HIGH, 0xffff);
		rx_mode |= SUNI1x10GEXP_BITMSK_RXXG_MHASH_EN;
	पूर्ण अन्यथा अगर (t1_rx_mode_mc_cnt(rm)) अणु
		/* Accept one or more multicast(s). */
		काष्ठा netdev_hw_addr *ha;
		पूर्णांक bit;
		u16 mc_filter[4] = अणु 0, पूर्ण;

		netdev_क्रम_each_mc_addr(ha, t1_get_netdev(rm)) अणु
			/* bit[23:28] */
			bit = (ether_crc(ETH_ALEN, ha->addr) >> 23) & 0x3f;
			mc_filter[bit >> 4] |= 1 << (bit & 0xf);
		पूर्ण
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_LOW, mc_filter[0]);
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDLOW, mc_filter[1]);
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_MIDHIGH, mc_filter[2]);
		pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_MULTICAST_HASH_HIGH, mc_filter[3]);
		rx_mode |= SUNI1x10GEXP_BITMSK_RXXG_MHASH_EN;
	पूर्ण

	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_2, (u16)rx_mode);

	अगर (enabled)
		pm3393_enable(cmac, MAC_सूचीECTION_RX);

	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_get_speed_duplex_fc(काष्ठा cmac *cmac, पूर्णांक *speed,
				      पूर्णांक *duplex, पूर्णांक *fc)
अणु
	अगर (speed)
		*speed = SPEED_10000;
	अगर (duplex)
		*duplex = DUPLEX_FULL;
	अगर (fc)
		*fc = cmac->instance->fc;
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_set_speed_duplex_fc(काष्ठा cmac *cmac, पूर्णांक speed, पूर्णांक duplex,
				      पूर्णांक fc)
अणु
	अगर (speed >= 0 && speed != SPEED_10000)
		वापस -1;
	अगर (duplex >= 0 && duplex != DUPLEX_FULL)
		वापस -1;
	अगर (fc & ~(PAUSE_TX | PAUSE_RX))
		वापस -1;

	अगर (fc != cmac->instance->fc) अणु
		cmac->instance->fc = (u8) fc;
		अगर (cmac->instance->enabled & MAC_सूचीECTION_TX)
			pm3393_enable(cmac, MAC_सूचीECTION_TX);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा RMON_UPDATE(mac, name, stat_name) \
अणु \
	t1_tpi_पढ़ो((mac)->adapter, OFFSET(name), &val0);     \
	t1_tpi_पढ़ो((mac)->adapter, OFFSET((name)+1), &val1); \
	t1_tpi_पढ़ो((mac)->adapter, OFFSET((name)+2), &val2); \
	(mac)->stats.stat_name = (u64)(val0 & 0xffff) | \
				 ((u64)(val1 & 0xffff) << 16) | \
				 ((u64)(val2 & 0xff) << 32) | \
				 ((mac)->stats.stat_name & \
					0xffffff0000000000ULL); \
	अगर (ro & \
	    (1ULL << ((name - SUNI1x10GEXP_REG_MSTAT_COUNTER_0_LOW) >> 2))) \
		(mac)->stats.stat_name += 1ULL << 40; \
पूर्ण

अटल स्थिर काष्ठा cmac_statistics *pm3393_update_statistics(काष्ठा cmac *mac,
							      पूर्णांक flag)
अणु
	u64	ro;
	u32	val0, val1, val2, val3;

	/* Snap the counters */
	pmग_लिखो(mac, SUNI1x10GEXP_REG_MSTAT_CONTROL,
		SUNI1x10GEXP_BITMSK_MSTAT_SNAP);

	/* Counter rollover, clear on पढ़ो */
	pmपढ़ो(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_0, &val0);
	pmपढ़ो(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_1, &val1);
	pmपढ़ो(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_2, &val2);
	pmपढ़ो(mac, SUNI1x10GEXP_REG_MSTAT_COUNTER_ROLLOVER_3, &val3);
	ro = ((u64)val0 & 0xffff) | (((u64)val1 & 0xffff) << 16) |
		(((u64)val2 & 0xffff) << 32) | (((u64)val3 & 0xffff) << 48);

	/* Rx stats */
	RMON_UPDATE(mac, RxOctetsReceivedOK, RxOctetsOK);
	RMON_UPDATE(mac, RxUnicastFramesReceivedOK, RxUnicastFramesOK);
	RMON_UPDATE(mac, RxMulticastFramesReceivedOK, RxMulticastFramesOK);
	RMON_UPDATE(mac, RxBroadcastFramesReceivedOK, RxBroadcastFramesOK);
	RMON_UPDATE(mac, RxPAUSEMACCtrlFramesReceived, RxPauseFrames);
	RMON_UPDATE(mac, RxFrameCheckSequenceErrors, RxFCSErrors);
	RMON_UPDATE(mac, RxFramesLostDueToInternalMACErrors,
				RxInternalMACRcvError);
	RMON_UPDATE(mac, RxSymbolErrors, RxSymbolErrors);
	RMON_UPDATE(mac, RxInRangeLengthErrors, RxInRangeLengthErrors);
	RMON_UPDATE(mac, RxFramesTooLongErrors , RxFrameTooLongErrors);
	RMON_UPDATE(mac, RxJabbers, RxJabberErrors);
	RMON_UPDATE(mac, RxFragments, RxRuntErrors);
	RMON_UPDATE(mac, RxUndersizedFrames, RxRuntErrors);
	RMON_UPDATE(mac, RxJumboFramesReceivedOK, RxJumboFramesOK);
	RMON_UPDATE(mac, RxJumboOctetsReceivedOK, RxJumboOctetsOK);

	/* Tx stats */
	RMON_UPDATE(mac, TxOctetsTransmittedOK, TxOctetsOK);
	RMON_UPDATE(mac, TxFramesLostDueToInternalMACTransmissionError,
				TxInternalMACXmitError);
	RMON_UPDATE(mac, TxTransmitSystemError, TxFCSErrors);
	RMON_UPDATE(mac, TxUnicastFramesTransmittedOK, TxUnicastFramesOK);
	RMON_UPDATE(mac, TxMulticastFramesTransmittedOK, TxMulticastFramesOK);
	RMON_UPDATE(mac, TxBroadcastFramesTransmittedOK, TxBroadcastFramesOK);
	RMON_UPDATE(mac, TxPAUSEMACCtrlFramesTransmitted, TxPauseFrames);
	RMON_UPDATE(mac, TxJumboFramesReceivedOK, TxJumboFramesOK);
	RMON_UPDATE(mac, TxJumboOctetsReceivedOK, TxJumboOctetsOK);

	वापस &mac->stats;
पूर्ण

अटल पूर्णांक pm3393_macaddress_get(काष्ठा cmac *cmac, u8 mac_addr[6])
अणु
	स_नकल(mac_addr, cmac->instance->mac_addr, ETH_ALEN);
	वापस 0;
पूर्ण

अटल पूर्णांक pm3393_macaddress_set(काष्ठा cmac *cmac, u8 ma[6])
अणु
	u32 val, lo, mid, hi, enabled = cmac->instance->enabled;

	/*
	 * MAC addr: 00:07:43:00:13:09
	 *
	 * ma[5] = 0x09
	 * ma[4] = 0x13
	 * ma[3] = 0x00
	 * ma[2] = 0x43
	 * ma[1] = 0x07
	 * ma[0] = 0x00
	 *
	 * The PM3393 requires byte swapping and reverse order entry
	 * when programming MAC addresses:
	 *
	 * low_bits[15:0]    = ma[1]:ma[0]
	 * mid_bits[31:16]   = ma[3]:ma[2]
	 * high_bits[47:32]  = ma[5]:ma[4]
	 */

	/* Store local copy */
	स_नकल(cmac->instance->mac_addr, ma, ETH_ALEN);

	lo  = ((u32) ma[1] << 8) | (u32) ma[0];
	mid = ((u32) ma[3] << 8) | (u32) ma[2];
	hi  = ((u32) ma[5] << 8) | (u32) ma[4];

	/* Disable Rx/Tx MAC beक्रमe configuring it. */
	अगर (enabled)
		pm3393_disable(cmac, MAC_सूचीECTION_RX | MAC_सूचीECTION_TX);

	/* Set RXXG Station Address */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_SA_15_0, lo);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_SA_31_16, mid);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_SA_47_32, hi);

	/* Set TXXG Station Address */
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_SA_15_0, lo);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_SA_31_16, mid);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_TXXG_SA_47_32, hi);

	/* Setup Exact Match Filter 1 with our MAC address
	 *
	 * Must disable exact match filter beक्रमe configuring it.
	 */
	pmपढ़ो(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_0, &val);
	val &= 0xff0f;
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_0, val);

	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_EXACT_MATCH_ADDR_1_LOW, lo);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_EXACT_MATCH_ADDR_1_MID, mid);
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_EXACT_MATCH_ADDR_1_HIGH, hi);

	val |= 0x0090;
	pmग_लिखो(cmac, SUNI1x10GEXP_REG_RXXG_ADDRESS_FILTER_CONTROL_0, val);

	अगर (enabled)
		pm3393_enable(cmac, enabled);
	वापस 0;
पूर्ण

अटल व्योम pm3393_destroy(काष्ठा cmac *cmac)
अणु
	kमुक्त(cmac);
पूर्ण

अटल स्थिर काष्ठा cmac_ops pm3393_ops = अणु
	.destroy                 = pm3393_destroy,
	.reset                   = pm3393_reset,
	.पूर्णांकerrupt_enable        = pm3393_पूर्णांकerrupt_enable,
	.पूर्णांकerrupt_disable       = pm3393_पूर्णांकerrupt_disable,
	.पूर्णांकerrupt_clear         = pm3393_पूर्णांकerrupt_clear,
	.पूर्णांकerrupt_handler       = pm3393_पूर्णांकerrupt_handler,
	.enable                  = pm3393_enable_port,
	.disable                 = pm3393_disable,
	.loopback_enable         = pm3393_loopback_enable,
	.loopback_disable        = pm3393_loopback_disable,
	.set_mtu                 = pm3393_set_mtu,
	.set_rx_mode             = pm3393_set_rx_mode,
	.get_speed_duplex_fc     = pm3393_get_speed_duplex_fc,
	.set_speed_duplex_fc     = pm3393_set_speed_duplex_fc,
	.statistics_update       = pm3393_update_statistics,
	.macaddress_get          = pm3393_macaddress_get,
	.macaddress_set          = pm3393_macaddress_set
पूर्ण;

अटल काष्ठा cmac *pm3393_mac_create(adapter_t *adapter, पूर्णांक index)
अणु
	काष्ठा cmac *cmac;

	cmac = kzalloc(माप(*cmac) + माप(cmac_instance), GFP_KERNEL);
	अगर (!cmac)
		वापस शून्य;

	cmac->ops = &pm3393_ops;
	cmac->instance = (cmac_instance *) (cmac + 1);
	cmac->adapter = adapter;
	cmac->instance->fc = PAUSE_TX | PAUSE_RX;

	t1_tpi_ग_लिखो(adapter, OFFSET(0x0001), 0x00008000);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x0001), 0x00000000);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2308), 0x00009800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2305), 0x00001001);   /* PL4IO Enable */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2320), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2321), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2322), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2323), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2324), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2325), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2326), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2327), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2328), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2329), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x232a), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x232b), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x232c), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x232d), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x232e), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x232f), 0x00008800);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x230d), 0x00009c00);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2304), 0x00000202);	/* PL4IO Calendar Repetitions */

	t1_tpi_ग_लिखो(adapter, OFFSET(0x3200), 0x00008080);	/* EFLX Enable */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3210), 0x00000000);	/* EFLX Channel Deprovision */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3203), 0x00000000);	/* EFLX Low Limit */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3204), 0x00000040);	/* EFLX High Limit */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3205), 0x000002cc);	/* EFLX Almost Full */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3206), 0x00000199);	/* EFLX Almost Empty */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3207), 0x00000240);	/* EFLX Cut Through Threshold */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3202), 0x00000000);	/* EFLX Indirect Register Update */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3210), 0x00000001);	/* EFLX Channel Provision */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3208), 0x0000ffff);	/* EFLX Unकरोcumented */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x320a), 0x0000ffff);	/* EFLX Unकरोcumented */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x320c), 0x0000ffff);	/* EFLX enable overflow पूर्णांकerrupt The other bit are unकरोcumented */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x320e), 0x0000ffff);	/* EFLX Unकरोcumented */

	t1_tpi_ग_लिखो(adapter, OFFSET(0x2200), 0x0000c000);	/* IFLX Configuration - enable */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2201), 0x00000000);	/* IFLX Channel Deprovision */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x220e), 0x00000000);	/* IFLX Low Limit */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x220f), 0x00000100);	/* IFLX High Limit */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2210), 0x00000c00);	/* IFLX Almost Full Limit */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2211), 0x00000599);	/* IFLX Almost Empty Limit */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x220d), 0x00000000);	/* IFLX Indirect Register Update */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2201), 0x00000001);	/* IFLX Channel Provision */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2203), 0x0000ffff);	/* IFLX Unकरोcumented */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2205), 0x0000ffff);	/* IFLX Unकरोcumented */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2209), 0x0000ffff);	/* IFLX Enable overflow पूर्णांकerrupt.  The other bit are unकरोcumented */

	t1_tpi_ग_लिखो(adapter, OFFSET(0x2241), 0xfffffffe);	/* PL4MOS Unकरोcumented */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2242), 0x0000ffff);	/* PL4MOS Unकरोcumented */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2243), 0x00000008);	/* PL4MOS Starving Burst Size */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2244), 0x00000008);	/* PL4MOS Hungry Burst Size */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2245), 0x00000008);	/* PL4MOS Transfer Size */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2240), 0x00000005);	/* PL4MOS Disable */

	t1_tpi_ग_लिखो(adapter, OFFSET(0x2280), 0x00002103);	/* PL4ODP Training Repeat and SOP rule */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2284), 0x00000000);	/* PL4ODP MAX_T setting */

	t1_tpi_ग_लिखो(adapter, OFFSET(0x3280), 0x00000087);	/* PL4IDU Enable data क्रमward, port state machine. Set ALLOW_NON_ZERO_OLB */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x3282), 0x0000001f);	/* PL4IDU Enable Dip4 check error पूर्णांकerrupts */

	t1_tpi_ग_लिखो(adapter, OFFSET(0x3040), 0x0c32);	/* # TXXG Config */
	/* For T1 use समयr based Mac flow control. */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x304d), 0x8000);
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2040), 0x059c);	/* # RXXG Config */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2049), 0x0001);	/* # RXXG Cut Through */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x2070), 0x0000);	/* # Disable promiscuous mode */

	/* Setup Exact Match Filter 0 to allow broadcast packets.
	 */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x206e), 0x0000);	/* # Disable Match Enable bit */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x204a), 0xffff);	/* # low addr */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x204b), 0xffff);	/* # mid addr */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x204c), 0xffff);	/* # high addr */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x206e), 0x0009);	/* # Enable Match Enable bit */

	t1_tpi_ग_लिखो(adapter, OFFSET(0x0003), 0x0000);	/* # NO SOP/ PAD_EN setup */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x0100), 0x0ff0);	/* # RXEQB disabled */
	t1_tpi_ग_लिखो(adapter, OFFSET(0x0101), 0x0f0f);	/* # No Preemphasis */

	वापस cmac;
पूर्ण

अटल पूर्णांक pm3393_mac_reset(adapter_t * adapter)
अणु
	u32 val;
	u32 x;
	u32 is_pl4_reset_finished;
	u32 is_pl4_outof_lock;
	u32 is_xaui_mabc_pll_locked;
	u32 successful_reset;
	पूर्णांक i;

	/* The following steps are required to properly reset
	 * the PM3393. This inक्रमmation is provided in the
	 * PM3393 datasheet (Issue 2: November 2002)
	 * section 13.1 -- Device Reset.
	 *
	 * The PM3393 has three types of components that are
	 * inभागidually reset:
	 *
	 * DRESETB      - Digital circuitry
	 * PL4_ARESETB  - PL4 analog circuitry
	 * XAUI_ARESETB - XAUI bus analog circuitry
	 *
	 * Steps to reset PM3393 using RSTB pin:
	 *
	 * 1. Assert RSTB pin low ( ग_लिखो 0 )
	 * 2. Wait at least 1ms to initiate a complete initialization of device.
	 * 3. Wait until all बाह्यal घड़ीs and REFSEL are stable.
	 * 4. Wait minimum of 1ms. (after बाह्यal घड़ीs and REFEL are stable)
	 * 5. De-निश्चित RSTB ( ग_लिखो 1 )
	 * 6. Wait until पूर्णांकernal समयrs to expires after ~14ms.
	 *    - Allows analog घड़ी synthesizer(PL4CSU) to stabilize to
	 *      selected reference frequency beक्रमe allowing the digital
	 *      portion of the device to operate.
	 * 7. Wait at least 200us क्रम XAUI पूर्णांकerface to stabilize.
	 * 8. Verअगरy the PM3393 came out of reset successfully.
	 *    Set successful reset flag अगर everything worked अन्यथा try again
	 *    a few more बार.
	 */

	successful_reset = 0;
	क्रम (i = 0; i < 3 && !successful_reset; i++) अणु
		/* 1 */
		t1_tpi_पढ़ो(adapter, A_ELMER0_GPO, &val);
		val &= ~1;
		t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);

		/* 2 */
		msleep(1);

		/* 3 */
		msleep(1);

		/* 4 */
		msleep(2 /*1 extra ms क्रम safety */ );

		/* 5 */
		val |= 1;
		t1_tpi_ग_लिखो(adapter, A_ELMER0_GPO, val);

		/* 6 */
		msleep(15 /*1 extra ms क्रम safety */ );

		/* 7 */
		msleep(1);

		/* 8 */

		/* Has PL4 analog block come out of reset correctly? */
		t1_tpi_पढ़ो(adapter, OFFSET(SUNI1x10GEXP_REG_DEVICE_STATUS), &val);
		is_pl4_reset_finished = (val & SUNI1x10GEXP_BITMSK_TOP_EXPIRED);

		/* TBD XXX SUNI1x10GEXP_BITMSK_TOP_PL4_IS_DOOL माला_लो locked later in the init sequence
		 *         figure out why? */

		/* Have all PL4 block घड़ीs locked? */
		x = (SUNI1x10GEXP_BITMSK_TOP_PL4_ID_DOOL
		     /*| SUNI1x10GEXP_BITMSK_TOP_PL4_IS_DOOL */  |
		     SUNI1x10GEXP_BITMSK_TOP_PL4_ID_ROOL |
		     SUNI1x10GEXP_BITMSK_TOP_PL4_IS_ROOL |
		     SUNI1x10GEXP_BITMSK_TOP_PL4_OUT_ROOL);
		is_pl4_outof_lock = (val & x);

		/* ??? If this fails, might be able to software reset the XAUI part
		 *     and try to recover... thus saving us from करोing another HW reset */
		/* Has the XAUI MABC PLL circuitry stablized? */
		is_xaui_mabc_pll_locked =
		    (val & SUNI1x10GEXP_BITMSK_TOP_SXRA_EXPIRED);

		successful_reset = (is_pl4_reset_finished && !is_pl4_outof_lock
				    && is_xaui_mabc_pll_locked);

		अगर (netअगर_msg_hw(adapter))
			dev_dbg(&adapter->pdev->dev,
				"PM3393 HW reset %d: pl4_reset 0x%x, val 0x%x, "
				"is_pl4_outof_lock 0x%x, xaui_locked 0x%x\n",
				i, is_pl4_reset_finished, val,
				is_pl4_outof_lock, is_xaui_mabc_pll_locked);
	पूर्ण
	वापस successful_reset ? 0 : 1;
पूर्ण

स्थिर काष्ठा gmac t1_pm3393_ops = अणु
	.stats_update_period = STATS_TICK_SECS,
	.create              = pm3393_mac_create,
	.reset               = pm3393_mac_reset,
पूर्ण;
