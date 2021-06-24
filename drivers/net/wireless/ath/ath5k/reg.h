<शैली गुरु>
/*
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2007-2008 Michael Taylor <mike.taylor@apprion.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*
 * Register values क्रम Atheros 5210/5211/5212 cards from OpenBSD's ar5k
 * मुख्यtained by Reyk Floeter
 *
 * I tried to करोcument those रेजिस्टरs by looking at ar5k code, some
 * 802.11 (802.11e mostly) papers and by पढ़ोing various खुला available
 * Atheros presentations and papers like these:
 *
 * 5210 - http://nova.stanक्रमd.edu/~bbaas/ps/isscc2002_slides.pdf
 *
 * 5211 - http://www.hotchips.org/archives/hc14/3_Tue/16_mcfarland.pdf
 *
 * This file also contains रेजिस्टर values found on a memory dump of
 * Atheros's ART program (Atheros Radio Test), on ath9k, on legacy-hal
 * released by Atheros and on various debug messages found on the net.
 */

#समावेश "../reg.h"

/*====MAC DMA REGISTERS====*/

/*
 * AR5210-Specअगरic TXDP रेजिस्टरs
 * 5210 has only 2 transmit queues so no DCU/QCU, just
 * 2 transmit descriptor poपूर्णांकers...
 */
#घोषणा AR5K_NOQCU_TXDP0	0x0000		/* Queue 0 - data */
#घोषणा AR5K_NOQCU_TXDP1	0x0004		/* Queue 1 - beacons */

/*
 * Mac Control Register
 */
#घोषणा	AR5K_CR		0x0008			/* Register Address */
#घोषणा AR5K_CR_TXE0	0x00000001	/* TX Enable क्रम queue 0 on 5210 */
#घोषणा AR5K_CR_TXE1	0x00000002	/* TX Enable क्रम queue 1 on 5210 */
#घोषणा	AR5K_CR_RXE	0x00000004	/* RX Enable */
#घोषणा AR5K_CR_TXD0	0x00000008	/* TX Disable क्रम queue 0 on 5210 */
#घोषणा AR5K_CR_TXD1	0x00000010	/* TX Disable क्रम queue 1 on 5210 */
#घोषणा	AR5K_CR_RXD	0x00000020	/* RX Disable */
#घोषणा	AR5K_CR_SWI	0x00000040	/* Software Interrupt */

/*
 * RX Descriptor Poपूर्णांकer रेजिस्टर
 */
#घोषणा	AR5K_RXDP	0x000c

/*
 * Configuration and status रेजिस्टर
 */
#घोषणा	AR5K_CFG		0x0014			/* Register Address */
#घोषणा	AR5K_CFG_SWTD		0x00000001	/* Byte-swap TX descriptor (क्रम big endian archs) */
#घोषणा	AR5K_CFG_SWTB		0x00000002	/* Byte-swap TX buffer */
#घोषणा	AR5K_CFG_SWRD		0x00000004	/* Byte-swap RX descriptor */
#घोषणा	AR5K_CFG_SWRB		0x00000008	/* Byte-swap RX buffer */
#घोषणा	AR5K_CFG_SWRG		0x00000010	/* Byte-swap Register access */
#घोषणा AR5K_CFG_IBSS		0x00000020	/* 0-BSS, 1-IBSS [5211+] */
#घोषणा AR5K_CFG_PHY_OK		0x00000100	/* [5211+] */
#घोषणा AR5K_CFG_EEBS		0x00000200	/* EEPROM is busy */
#घोषणा	AR5K_CFG_CLKGD		0x00000400	/* Clock gated (Disable dynamic घड़ी) */
#घोषणा AR5K_CFG_TXCNT		0x00007800	/* Tx frame count (?) [5210] */
#घोषणा AR5K_CFG_TXCNT_S	11
#घोषणा AR5K_CFG_TXFSTAT	0x00008000	/* Tx frame status (?) [5210] */
#घोषणा AR5K_CFG_TXFSTRT	0x00010000	/* [5210] */
#घोषणा	AR5K_CFG_PCI_THRES	0x00060000	/* PCI Master req q threshold [5211+] */
#घोषणा	AR5K_CFG_PCI_THRES_S	17

/*
 * Interrupt enable रेजिस्टर
 */
#घोषणा AR5K_IER		0x0024		/* Register Address */
#घोषणा AR5K_IER_DISABLE	0x00000000	/* Disable card पूर्णांकerrupts */
#घोषणा AR5K_IER_ENABLE		0x00000001	/* Enable card पूर्णांकerrupts */


/*
 * 0x0028 is Beacon Control Register on 5210
 * and first RTS duration रेजिस्टर on 5211
 */

/*
 * Beacon control रेजिस्टर [5210]
 */
#घोषणा AR5K_BCR		0x0028		/* Register Address */
#घोषणा AR5K_BCR_AP		0x00000000	/* AP mode */
#घोषणा AR5K_BCR_ADHOC		0x00000001	/* Ad-Hoc mode */
#घोषणा AR5K_BCR_BDMAE		0x00000002	/* DMA enable */
#घोषणा AR5K_BCR_TQ1FV		0x00000004	/* Use Queue1 क्रम CAB traffic */
#घोषणा AR5K_BCR_TQ1V		0x00000008	/* Use Queue1 क्रम Beacon traffic */
#घोषणा AR5K_BCR_BCGET		0x00000010

/*
 * First RTS duration रेजिस्टर [5211]
 */
#घोषणा AR5K_RTSD0		0x0028		/* Register Address */
#घोषणा	AR5K_RTSD0_6		0x000000ff	/* 6Mb RTS duration mask (?) */
#घोषणा	AR5K_RTSD0_6_S		0		/* 6Mb RTS duration shअगरt (?) */
#घोषणा	AR5K_RTSD0_9		0x0000ff00	/* 9Mb*/
#घोषणा	AR5K_RTSD0_9_S		8
#घोषणा	AR5K_RTSD0_12		0x00ff0000	/* 12Mb*/
#घोषणा	AR5K_RTSD0_12_S		16
#घोषणा	AR5K_RTSD0_18		0xff000000	/* 16Mb*/
#घोषणा	AR5K_RTSD0_18_S		24


/*
 * 0x002c is Beacon Status Register on 5210
 * and second RTS duration रेजिस्टर on 5211
 */

/*
 * Beacon status रेजिस्टर [5210]
 *
 * As i can see in ar5k_ar5210_tx_start Reyk uses some of the values of BCR
 * क्रम this रेजिस्टर, so i guess TQ1V,TQ1FV and BDMAE have the same meaning
 * here and SNP/SNAP means "snapshot" (so this रेजिस्टर माला_लो synced with BCR).
 * So SNAPPEDBCRVALID should also stand क्रम "snapped BCR -values- valid", so i
 * नामd it to SNAPSHOTSVALID to make more sense. I really have no idea what
 * अन्यथा can it be. I also नामd SNPBCMD to SNPADHOC to match BCR.
 */
#घोषणा AR5K_BSR		0x002c			/* Register Address */
#घोषणा AR5K_BSR_BDLYSW		0x00000001	/* SW Beacon delay (?) */
#घोषणा AR5K_BSR_BDLYDMA	0x00000002	/* DMA Beacon delay (?) */
#घोषणा AR5K_BSR_TXQ1F		0x00000004	/* Beacon queue (1) finished */
#घोषणा AR5K_BSR_ATIMDLY	0x00000008	/* ATIM delay (?) */
#घोषणा AR5K_BSR_SNPADHOC	0x00000100	/* Ad-hoc mode set (?) */
#घोषणा AR5K_BSR_SNPBDMAE	0x00000200	/* Beacon DMA enabled (?) */
#घोषणा AR5K_BSR_SNPTQ1FV	0x00000400	/* Queue1 is used क्रम CAB traffic (?) */
#घोषणा AR5K_BSR_SNPTQ1V	0x00000800	/* Queue1 is used क्रम Beacon traffic (?) */
#घोषणा AR5K_BSR_SNAPSHOTSVALID	0x00001000	/* BCR snapshots are valid (?) */
#घोषणा AR5K_BSR_SWBA_CNT	0x00ff0000

/*
 * Second RTS duration रेजिस्टर [5211]
 */
#घोषणा AR5K_RTSD1		0x002c			/* Register Address */
#घोषणा	AR5K_RTSD1_24		0x000000ff	/* 24Mb */
#घोषणा	AR5K_RTSD1_24_S		0
#घोषणा	AR5K_RTSD1_36		0x0000ff00	/* 36Mb */
#घोषणा	AR5K_RTSD1_36_S		8
#घोषणा	AR5K_RTSD1_48		0x00ff0000	/* 48Mb */
#घोषणा	AR5K_RTSD1_48_S		16
#घोषणा	AR5K_RTSD1_54		0xff000000	/* 54Mb */
#घोषणा	AR5K_RTSD1_54_S		24


/*
 * Transmit configuration रेजिस्टर
 */
#घोषणा AR5K_TXCFG			0x0030			/* Register Address */
#घोषणा AR5K_TXCFG_SDMAMR		0x00000007	/* DMA size (पढ़ो) */
#घोषणा AR5K_TXCFG_SDMAMR_S		0
#घोषणा AR5K_TXCFG_B_MODE		0x00000008	/* Set b mode क्रम 5111 (enable 2111) */
#घोषणा AR5K_TXCFG_TXFSTP		0x00000008	/* TX DMA full Stop [5210] */
#घोषणा AR5K_TXCFG_TXFULL		0x000003f0	/* TX Trigger level mask */
#घोषणा AR5K_TXCFG_TXFULL_S		4
#घोषणा AR5K_TXCFG_TXFULL_0B		0x00000000
#घोषणा AR5K_TXCFG_TXFULL_64B		0x00000010
#घोषणा AR5K_TXCFG_TXFULL_128B		0x00000020
#घोषणा AR5K_TXCFG_TXFULL_192B		0x00000030
#घोषणा AR5K_TXCFG_TXFULL_256B		0x00000040
#घोषणा AR5K_TXCFG_TXCONT_EN		0x00000080
#घोषणा AR5K_TXCFG_DMASIZE		0x00000100	/* Flag क्रम passing DMA size [5210] */
#घोषणा AR5K_TXCFG_JUMBO_DESC_EN	0x00000400	/* Enable jumbo tx descriptors [5211+] */
#घोषणा AR5K_TXCFG_ADHOC_BCN_ATIM	0x00000800	/* Adhoc Beacon ATIM Policy */
#घोषणा AR5K_TXCFG_ATIM_WINDOW_DEF_DIS	0x00001000	/* Disable ATIM winकरोw defer [5211+] */
#घोषणा AR5K_TXCFG_RTSRND		0x00001000	/* [5211+] */
#घोषणा AR5K_TXCFG_FRMPAD_DIS		0x00002000	/* [5211+] */
#घोषणा AR5K_TXCFG_RDY_CBR_DIS		0x00004000	/* Ready समय CBR disable [5211+] */
#घोषणा AR5K_TXCFG_JUMBO_FRM_MODE	0x00008000	/* Jumbo frame mode [5211+] */
#घोषणा	AR5K_TXCFG_DCU_DBL_BUF_DIS	0x00008000	/* Disable द्विगुन buffering on DCU */
#घोषणा AR5K_TXCFG_DCU_CACHING_DIS	0x00010000	/* Disable DCU caching */

/*
 * Receive configuration रेजिस्टर
 */
#घोषणा AR5K_RXCFG		0x0034			/* Register Address */
#घोषणा AR5K_RXCFG_SDMAMW	0x00000007	/* DMA size (ग_लिखो) */
#घोषणा AR5K_RXCFG_SDMAMW_S	0
#घोषणा AR5K_RXCFG_ZLFDMA	0x00000008	/* Enable Zero-length frame DMA */
#घोषणा	AR5K_RXCFG_DEF_ANTENNA	0x00000010	/* Default antenna (?) */
#घोषणा AR5K_RXCFG_JUMBO_RXE	0x00000020	/* Enable jumbo rx descriptors [5211+] */
#घोषणा AR5K_RXCFG_JUMBO_WRAP	0x00000040	/* Wrap jumbo frames [5211+] */
#घोषणा AR5K_RXCFG_SLE_ENTRY	0x00000080	/* Sleep entry policy */

/*
 * Receive jumbo descriptor last address रेजिस्टर
 * Only found in 5211 (?)
 */
#घोषणा AR5K_RXJLA		0x0038

/*
 * MIB control रेजिस्टर
 */
#घोषणा AR5K_MIBC		0x0040			/* Register Address */
#घोषणा AR5K_MIBC_COW		0x00000001	/* Counter Overflow Warning */
#घोषणा AR5K_MIBC_FMC		0x00000002	/* Freeze MIB Counters  */
#घोषणा AR5K_MIBC_CMC		0x00000004	/* Clear MIB Counters  */
#घोषणा AR5K_MIBC_MCS		0x00000008	/* MIB counter strobe, increment all */

/*
 * Timeout prescale रेजिस्टर
 */
#घोषणा AR5K_TOPS		0x0044
#घोषणा	AR5K_TOPS_M		0x0000ffff

/*
 * Receive समयout रेजिस्टर (no frame received)
 */
#घोषणा AR5K_RXNOFRM		0x0048
#घोषणा	AR5K_RXNOFRM_M		0x000003ff

/*
 * Transmit समयout रेजिस्टर (no frame sent)
 */
#घोषणा AR5K_TXNOFRM		0x004c
#घोषणा	AR5K_TXNOFRM_M		0x000003ff
#घोषणा	AR5K_TXNOFRM_QCU	0x000ffc00
#घोषणा	AR5K_TXNOFRM_QCU_S	10

/*
 * Receive frame gap समयout रेजिस्टर
 */
#घोषणा AR5K_RPGTO		0x0050
#घोषणा AR5K_RPGTO_M		0x000003ff

/*
 * Receive frame count limit रेजिस्टर
 */
#घोषणा AR5K_RFCNT		0x0054
#घोषणा AR5K_RFCNT_M		0x0000001f	/* [5211+] (?) */
#घोषणा AR5K_RFCNT_RFCL		0x0000000f	/* [5210] */

/*
 * Misc settings रेजिस्टर
 * (reserved0-3)
 */
#घोषणा AR5K_MISC		0x0058			/* Register Address */
#घोषणा	AR5K_MISC_DMA_OBS_M	0x000001e0
#घोषणा	AR5K_MISC_DMA_OBS_S	5
#घोषणा	AR5K_MISC_MISC_OBS_M	0x00000e00
#घोषणा	AR5K_MISC_MISC_OBS_S	9
#घोषणा	AR5K_MISC_MAC_OBS_LSB_M	0x00007000
#घोषणा	AR5K_MISC_MAC_OBS_LSB_S	12
#घोषणा	AR5K_MISC_MAC_OBS_MSB_M	0x00038000
#घोषणा	AR5K_MISC_MAC_OBS_MSB_S	15
#घोषणा AR5K_MISC_LED_DECAY	0x001c0000	/* [5210] */
#घोषणा AR5K_MISC_LED_BLINK	0x00e00000	/* [5210] */

/*
 * QCU/DCU घड़ी gating रेजिस्टर (5311)
 * (reserved4-5)
 */
#घोषणा	AR5K_QCUDCU_CLKGT	0x005c			/* Register Address (?) */
#घोषणा	AR5K_QCUDCU_CLKGT_QCU	0x0000ffff	/* Mask क्रम QCU घड़ी */
#घोषणा	AR5K_QCUDCU_CLKGT_DCU	0x07ff0000	/* Mask क्रम DCU घड़ी */

/*
 * Interrupt Status Registers
 *
 * For 5210 there is only one status रेजिस्टर but क्रम
 * 5211/5212 we have one primary and 4 secondary रेजिस्टरs.
 * So we have AR5K_ISR क्रम 5210 and AR5K_PISR /SISRx क्रम 5211/5212.
 * Most of these bits are common क्रम all chipsets.
 *
 * NOTE: On 5211+ TXOK, TXDESC, TXERR, TXEOL and TXURN contain
 * the logical OR from per-queue पूर्णांकerrupt bits found on SISR रेजिस्टरs
 * (see below).
 */
#घोषणा AR5K_ISR		0x001c			/* Register Address [5210] */
#घोषणा AR5K_PISR		0x0080			/* Register Address [5211+] */
#घोषणा AR5K_ISR_RXOK		0x00000001	/* Frame successfully received */
#घोषणा AR5K_ISR_RXDESC		0x00000002	/* RX descriptor request */
#घोषणा AR5K_ISR_RXERR		0x00000004	/* Receive error */
#घोषणा AR5K_ISR_RXNOFRM	0x00000008	/* No frame received (receive समयout) */
#घोषणा AR5K_ISR_RXEOL		0x00000010	/* Empty RX descriptor */
#घोषणा AR5K_ISR_RXORN		0x00000020	/* Receive FIFO overrun */
#घोषणा AR5K_ISR_TXOK		0x00000040	/* Frame successfully transmitted */
#घोषणा AR5K_ISR_TXDESC		0x00000080	/* TX descriptor request */
#घोषणा AR5K_ISR_TXERR		0x00000100	/* Transmit error */
#घोषणा AR5K_ISR_TXNOFRM	0x00000200	/* No frame transmitted (transmit समयout)
						 * NOTE: We करोn't have per-queue info क्रम this
						 * one, but we can enable it per-queue through
						 * TXNOFRM_QCU field on TXNOFRM रेजिस्टर */
#घोषणा AR5K_ISR_TXEOL		0x00000400	/* Empty TX descriptor */
#घोषणा AR5K_ISR_TXURN		0x00000800	/* Transmit FIFO underrun */
#घोषणा AR5K_ISR_MIB		0x00001000	/* Update MIB counters */
#घोषणा AR5K_ISR_SWI		0x00002000	/* Software पूर्णांकerrupt */
#घोषणा AR5K_ISR_RXPHY		0x00004000	/* PHY error */
#घोषणा AR5K_ISR_RXKCM		0x00008000	/* RX Key cache miss */
#घोषणा AR5K_ISR_SWBA		0x00010000	/* Software beacon alert */
#घोषणा AR5K_ISR_BRSSI		0x00020000	/* Beacon rssi below threshold (?) */
#घोषणा AR5K_ISR_BMISS		0x00040000	/* Beacon missed */
#घोषणा AR5K_ISR_HIUERR		0x00080000	/* Host Interface Unit error [5211+]
						 * 'or' of MCABT, SSERR, DPERR from SISR2 */
#घोषणा AR5K_ISR_BNR		0x00100000	/* Beacon not पढ़ोy [5211+] */
#घोषणा AR5K_ISR_MCABT		0x00100000	/* Master Cycle Abort [5210] */
#घोषणा AR5K_ISR_RXCHIRP	0x00200000	/* CHIRP Received [5212+] */
#घोषणा AR5K_ISR_SSERR		0x00200000	/* Signaled System Error [5210] */
#घोषणा AR5K_ISR_DPERR		0x00400000	/* Bus parity error [5210] */
#घोषणा AR5K_ISR_RXDOPPLER	0x00400000	/* Doppler chirp received [5212+] */
#घोषणा AR5K_ISR_TIM		0x00800000	/* [5211+] */
#घोषणा AR5K_ISR_BCNMISC	0x00800000	/* Misc beacon related पूर्णांकerrupt
						 * 'or' of TIM, CAB_END, DTIM_SYNC, BCN_TIMEOUT,
						 * CAB_TIMEOUT and DTIM bits from SISR2 [5212+] */
#घोषणा AR5K_ISR_GPIO		0x01000000	/* GPIO (rf समाप्त) */
#घोषणा AR5K_ISR_QCBRORN	0x02000000	/* QCU CBR overrun [5211+] */
#घोषणा AR5K_ISR_QCBRURN	0x04000000	/* QCU CBR underrun [5211+] */
#घोषणा AR5K_ISR_QTRIG		0x08000000	/* QCU scheduling trigger [5211+] */

#घोषणा	AR5K_ISR_BITS_FROM_SISRS	(AR5K_ISR_TXOK | AR5K_ISR_TXDESC |\
					AR5K_ISR_TXERR | AR5K_ISR_TXEOL |\
					AR5K_ISR_TXURN | AR5K_ISR_HIUERR |\
					AR5K_ISR_BCNMISC | AR5K_ISR_QCBRORN |\
					AR5K_ISR_QCBRURN | AR5K_ISR_QTRIG)

/*
 * Secondary status रेजिस्टरs [5211+] (0 - 4)
 *
 * These give the status क्रम each QCU, only QCUs 0-9 are
 * represented.
 */
#घोषणा AR5K_SISR0		0x0084			/* Register Address [5211+] */
#घोषणा AR5K_SISR0_QCU_TXOK	0x000003ff	/* Mask क्रम QCU_TXOK */
#घोषणा AR5K_SISR0_QCU_TXOK_S	0
#घोषणा AR5K_SISR0_QCU_TXDESC	0x03ff0000	/* Mask क्रम QCU_TXDESC */
#घोषणा AR5K_SISR0_QCU_TXDESC_S	16

#घोषणा AR5K_SISR1		0x0088			/* Register Address [5211+] */
#घोषणा AR5K_SISR1_QCU_TXERR	0x000003ff	/* Mask क्रम QCU_TXERR */
#घोषणा AR5K_SISR1_QCU_TXERR_S	0
#घोषणा AR5K_SISR1_QCU_TXEOL	0x03ff0000	/* Mask क्रम QCU_TXEOL */
#घोषणा AR5K_SISR1_QCU_TXEOL_S	16

#घोषणा AR5K_SISR2		0x008c			/* Register Address [5211+] */
#घोषणा AR5K_SISR2_QCU_TXURN	0x000003ff	/* Mask क्रम QCU_TXURN */
#घोषणा	AR5K_SISR2_QCU_TXURN_S	0
#घोषणा	AR5K_SISR2_MCABT	0x00010000	/* Master Cycle Abort */
#घोषणा	AR5K_SISR2_SSERR	0x00020000	/* Signaled System Error */
#घोषणा	AR5K_SISR2_DPERR	0x00040000	/* Bus parity error */
#घोषणा	AR5K_SISR2_TIM		0x01000000	/* [5212+] */
#घोषणा	AR5K_SISR2_CAB_END	0x02000000	/* [5212+] */
#घोषणा	AR5K_SISR2_DTIM_SYNC	0x04000000	/* DTIM sync lost [5212+] */
#घोषणा	AR5K_SISR2_BCN_TIMEOUT	0x08000000	/* Beacon Timeout [5212+] */
#घोषणा	AR5K_SISR2_CAB_TIMEOUT	0x10000000	/* CAB Timeout [5212+] */
#घोषणा	AR5K_SISR2_DTIM		0x20000000	/* [5212+] */
#घोषणा	AR5K_SISR2_TSFOOR	0x80000000	/* TSF Out of range */

#घोषणा AR5K_SISR3		0x0090			/* Register Address [5211+] */
#घोषणा AR5K_SISR3_QCBRORN	0x000003ff	/* Mask क्रम QCBRORN */
#घोषणा AR5K_SISR3_QCBRORN_S	0
#घोषणा AR5K_SISR3_QCBRURN	0x03ff0000	/* Mask क्रम QCBRURN */
#घोषणा AR5K_SISR3_QCBRURN_S	16

#घोषणा AR5K_SISR4		0x0094			/* Register Address [5211+] */
#घोषणा AR5K_SISR4_QTRIG	0x000003ff	/* Mask क्रम QTRIG */
#घोषणा AR5K_SISR4_QTRIG_S	0

/*
 * Shaकरोw पढ़ो-and-clear पूर्णांकerrupt status रेजिस्टरs [5211+]
 */
#घोषणा AR5K_RAC_PISR		0x00c0		/* Read and clear PISR */
#घोषणा AR5K_RAC_SISR0		0x00c4		/* Read and clear SISR0 */
#घोषणा AR5K_RAC_SISR1		0x00c8		/* Read and clear SISR1 */
#घोषणा AR5K_RAC_SISR2		0x00cc		/* Read and clear SISR2 */
#घोषणा AR5K_RAC_SISR3		0x00d0		/* Read and clear SISR3 */
#घोषणा AR5K_RAC_SISR4		0x00d4		/* Read and clear SISR4 */

/*
 * Interrupt Mask Registers
 *
 * As with ISRs 5210 has one IMR (AR5K_IMR) and 5211/5212 has one primary
 * (AR5K_PIMR) and 4 secondary IMRs (AR5K_SIMRx). Note that ISR/IMR flags match.
 */
#घोषणा	AR5K_IMR		0x0020			/* Register Address [5210] */
#घोषणा AR5K_PIMR		0x00a0			/* Register Address [5211+] */
#घोषणा AR5K_IMR_RXOK		0x00000001	/* Frame successfully received*/
#घोषणा AR5K_IMR_RXDESC		0x00000002	/* RX descriptor request*/
#घोषणा AR5K_IMR_RXERR		0x00000004	/* Receive error*/
#घोषणा AR5K_IMR_RXNOFRM	0x00000008	/* No frame received (receive समयout)*/
#घोषणा AR5K_IMR_RXEOL		0x00000010	/* Empty RX descriptor*/
#घोषणा AR5K_IMR_RXORN		0x00000020	/* Receive FIFO overrun*/
#घोषणा AR5K_IMR_TXOK		0x00000040	/* Frame successfully transmitted*/
#घोषणा AR5K_IMR_TXDESC		0x00000080	/* TX descriptor request*/
#घोषणा AR5K_IMR_TXERR		0x00000100	/* Transmit error*/
#घोषणा AR5K_IMR_TXNOFRM	0x00000200	/* No frame transmitted (transmit समयout)*/
#घोषणा AR5K_IMR_TXEOL		0x00000400	/* Empty TX descriptor*/
#घोषणा AR5K_IMR_TXURN		0x00000800	/* Transmit FIFO underrun*/
#घोषणा AR5K_IMR_MIB		0x00001000	/* Update MIB counters*/
#घोषणा AR5K_IMR_SWI		0x00002000	/* Software पूर्णांकerrupt */
#घोषणा AR5K_IMR_RXPHY		0x00004000	/* PHY error*/
#घोषणा AR5K_IMR_RXKCM		0x00008000	/* RX Key cache miss */
#घोषणा AR5K_IMR_SWBA		0x00010000	/* Software beacon alert*/
#घोषणा AR5K_IMR_BRSSI		0x00020000	/* Beacon rssi below threshold (?) */
#घोषणा AR5K_IMR_BMISS		0x00040000	/* Beacon missed*/
#घोषणा AR5K_IMR_HIUERR		0x00080000	/* Host Interface Unit error [5211+] */
#घोषणा AR5K_IMR_BNR		0x00100000	/* Beacon not पढ़ोy [5211+] */
#घोषणा AR5K_IMR_MCABT		0x00100000	/* Master Cycle Abort [5210] */
#घोषणा AR5K_IMR_RXCHIRP	0x00200000	/* CHIRP Received [5212+]*/
#घोषणा AR5K_IMR_SSERR		0x00200000	/* Signaled System Error [5210] */
#घोषणा AR5K_IMR_DPERR		0x00400000	/* Det par Error (?) [5210] */
#घोषणा AR5K_IMR_RXDOPPLER	0x00400000	/* Doppler chirp received [5212+] */
#घोषणा AR5K_IMR_TIM		0x00800000	/* [5211+] */
#घोषणा AR5K_IMR_BCNMISC	0x00800000	/* 'or' of TIM, CAB_END, DTIM_SYNC, BCN_TIMEOUT,
						CAB_TIMEOUT and DTIM bits from SISR2 [5212+] */
#घोषणा AR5K_IMR_GPIO		0x01000000	/* GPIO (rf समाप्त)*/
#घोषणा AR5K_IMR_QCBRORN	0x02000000	/* QCU CBR overrun (?) [5211+] */
#घोषणा AR5K_IMR_QCBRURN	0x04000000	/* QCU CBR underrun (?) [5211+] */
#घोषणा AR5K_IMR_QTRIG		0x08000000	/* QCU scheduling trigger [5211+] */

/*
 * Secondary पूर्णांकerrupt mask रेजिस्टरs [5211+] (0 - 4)
 */
#घोषणा AR5K_SIMR0		0x00a4			/* Register Address [5211+] */
#घोषणा AR5K_SIMR0_QCU_TXOK	0x000003ff	/* Mask क्रम QCU_TXOK */
#घोषणा AR5K_SIMR0_QCU_TXOK_S	0
#घोषणा AR5K_SIMR0_QCU_TXDESC	0x03ff0000	/* Mask क्रम QCU_TXDESC */
#घोषणा AR5K_SIMR0_QCU_TXDESC_S	16

#घोषणा AR5K_SIMR1		0x00a8			/* Register Address [5211+] */
#घोषणा AR5K_SIMR1_QCU_TXERR	0x000003ff	/* Mask क्रम QCU_TXERR */
#घोषणा AR5K_SIMR1_QCU_TXERR_S	0
#घोषणा AR5K_SIMR1_QCU_TXEOL	0x03ff0000	/* Mask क्रम QCU_TXEOL */
#घोषणा AR5K_SIMR1_QCU_TXEOL_S	16

#घोषणा AR5K_SIMR2		0x00ac			/* Register Address [5211+] */
#घोषणा AR5K_SIMR2_QCU_TXURN	0x000003ff	/* Mask क्रम QCU_TXURN */
#घोषणा AR5K_SIMR2_QCU_TXURN_S	0
#घोषणा	AR5K_SIMR2_MCABT	0x00010000	/* Master Cycle Abort */
#घोषणा	AR5K_SIMR2_SSERR	0x00020000	/* Signaled System Error */
#घोषणा	AR5K_SIMR2_DPERR	0x00040000	/* Bus parity error */
#घोषणा	AR5K_SIMR2_TIM		0x01000000	/* [5212+] */
#घोषणा	AR5K_SIMR2_CAB_END	0x02000000	/* [5212+] */
#घोषणा	AR5K_SIMR2_DTIM_SYNC	0x04000000	/* DTIM Sync lost [5212+] */
#घोषणा	AR5K_SIMR2_BCN_TIMEOUT	0x08000000	/* Beacon Timeout [5212+] */
#घोषणा	AR5K_SIMR2_CAB_TIMEOUT	0x10000000	/* CAB Timeout [5212+] */
#घोषणा	AR5K_SIMR2_DTIM		0x20000000	/* [5212+] */
#घोषणा	AR5K_SIMR2_TSFOOR	0x80000000	/* TSF OOR (?) */

#घोषणा AR5K_SIMR3		0x00b0			/* Register Address [5211+] */
#घोषणा AR5K_SIMR3_QCBRORN	0x000003ff	/* Mask क्रम QCBRORN */
#घोषणा AR5K_SIMR3_QCBRORN_S	0
#घोषणा AR5K_SIMR3_QCBRURN	0x03ff0000	/* Mask क्रम QCBRURN */
#घोषणा AR5K_SIMR3_QCBRURN_S	16

#घोषणा AR5K_SIMR4		0x00b4			/* Register Address [5211+] */
#घोषणा AR5K_SIMR4_QTRIG	0x000003ff	/* Mask क्रम QTRIG */
#घोषणा AR5K_SIMR4_QTRIG_S	0

/*
 * DMA Debug रेजिस्टरs 0-7
 * 0xe0 - 0xfc
 */

/*
 * Decompression mask रेजिस्टरs [5212+]
 */
#घोषणा AR5K_DCM_ADDR		0x0400		/*Decompression mask address (index) */
#घोषणा AR5K_DCM_DATA		0x0404		/*Decompression mask data */

/*
 * Wake On Wireless pattern control रेजिस्टर [5212+]
 */
#घोषणा	AR5K_WOW_PCFG			0x0410			/* Register Address */
#घोषणा	AR5K_WOW_PCFG_PAT_MATCH_EN	0x00000001	/* Pattern match enable */
#घोषणा	AR5K_WOW_PCFG_LONG_FRAME_POL	0x00000002	/* Long frame policy */
#घोषणा	AR5K_WOW_PCFG_WOBMISS		0x00000004	/* Wake on bea(con) miss (?) */
#घोषणा	AR5K_WOW_PCFG_PAT_0_EN		0x00000100	/* Enable pattern 0 */
#घोषणा	AR5K_WOW_PCFG_PAT_1_EN		0x00000200	/* Enable pattern 1 */
#घोषणा	AR5K_WOW_PCFG_PAT_2_EN		0x00000400	/* Enable pattern 2 */
#घोषणा	AR5K_WOW_PCFG_PAT_3_EN		0x00000800	/* Enable pattern 3 */
#घोषणा	AR5K_WOW_PCFG_PAT_4_EN		0x00001000	/* Enable pattern 4 */
#घोषणा	AR5K_WOW_PCFG_PAT_5_EN		0x00002000	/* Enable pattern 5 */

/*
 * Wake On Wireless pattern index रेजिस्टर (?) [5212+]
 */
#घोषणा	AR5K_WOW_PAT_IDX	0x0414

/*
 * Wake On Wireless pattern data रेजिस्टर [5212+]
 */
#घोषणा	AR5K_WOW_PAT_DATA	0x0418			/* Register Address */
#घोषणा	AR5K_WOW_PAT_DATA_0_3_V	0x00000001	/* Pattern 0, 3 value */
#घोषणा	AR5K_WOW_PAT_DATA_1_4_V	0x00000100	/* Pattern 1, 4 value */
#घोषणा	AR5K_WOW_PAT_DATA_2_5_V	0x00010000	/* Pattern 2, 5 value */
#घोषणा	AR5K_WOW_PAT_DATA_0_3_M	0x01000000	/* Pattern 0, 3 mask */
#घोषणा	AR5K_WOW_PAT_DATA_1_4_M	0x04000000	/* Pattern 1, 4 mask */
#घोषणा	AR5K_WOW_PAT_DATA_2_5_M	0x10000000	/* Pattern 2, 5 mask */

/*
 * Decompression configuration रेजिस्टरs [5212+]
 */
#घोषणा AR5K_DCCFG		0x0420			/* Register Address */
#घोषणा AR5K_DCCFG_GLOBAL_EN	0x00000001	/* Enable decompression on all queues */
#घोषणा AR5K_DCCFG_BYPASS_EN	0x00000002	/* Bypass decompression */
#घोषणा AR5K_DCCFG_BCAST_EN	0x00000004	/* Enable decompression क्रम bcast frames */
#घोषणा AR5K_DCCFG_MCAST_EN	0x00000008	/* Enable decompression क्रम mcast frames */

/*
 * Compression configuration रेजिस्टरs [5212+]
 */
#घोषणा AR5K_CCFG		0x0600			/* Register Address */
#घोषणा	AR5K_CCFG_WINDOW_SIZE	0x00000007	/* Compression winकरोw size */
#घोषणा	AR5K_CCFG_CPC_EN	0x00000008	/* Enable perक्रमmance counters */

#घोषणा AR5K_CCFG_CCU		0x0604			/* Register Address */
#घोषणा AR5K_CCFG_CCU_CUP_EN	0x00000001	/* CCU Catchup enable */
#घोषणा AR5K_CCFG_CCU_CREDIT	0x00000002	/* CCU Credit (field) */
#घोषणा AR5K_CCFG_CCU_CD_THRES	0x00000080	/* CCU Cyc(lic?) debt threshold (field) */
#घोषणा AR5K_CCFG_CCU_CUP_LCNT	0x00010000	/* CCU Catchup lit(?) count */
#घोषणा	AR5K_CCFG_CCU_INIT	0x00100200	/* Initial value during reset */

/*
 * Compression perक्रमmance counter रेजिस्टरs [5212+]
 */
#घोषणा AR5K_CPC0		0x0610		/* Compression perक्रमmance counter 0 */
#घोषणा AR5K_CPC1		0x0614		/* Compression perक्रमmance counter 1*/
#घोषणा AR5K_CPC2		0x0618		/* Compression perक्रमmance counter 2 */
#घोषणा AR5K_CPC3		0x061c		/* Compression perक्रमmance counter 3 */
#घोषणा AR5K_CPCOVF		0x0620		/* Compression perक्रमmance overflow */


/*
 * Queue control unit (QCU) रेजिस्टरs [5211+]
 *
 * Card has 12 TX Queues but i see that only 0-9 are used (?)
 * both in binary HAL (see ah.h) and ar5k. Each queue has it's own
 * TXDP at addresses 0x0800 - 0x082c, a CBR (Constant Bit Rate)
 * configuration रेजिस्टर (0x08c0 - 0x08ec), a पढ़ोy समय configuration
 * रेजिस्टर (0x0900 - 0x092c), a misc configuration रेजिस्टर (0x09c0 -
 * 0x09ec) and a status रेजिस्टर (0x0a00 - 0x0a2c). We also have some
 * global रेजिस्टरs, QCU transmit enable/disable and "one shot arm (?)"
 * set/clear, which contain status क्रम all queues (we shअगरt by 1 क्रम each
 * queue). To access these रेजिस्टरs easily we define some macros here
 * that are used inside HAL. For more infos check out *_tx_queue functs.
 */

/*
 * Generic QCU Register access macros
 */
#घोषणा	AR5K_QUEUE_REG(_r, _q)		(((_q) << 2) + _r)
#घोषणा AR5K_QCU_GLOBAL_READ(_r, _q)	(AR5K_REG_READ(_r) & (1 << _q))
#घोषणा AR5K_QCU_GLOBAL_WRITE(_r, _q)	AR5K_REG_WRITE(_r, (1 << _q))

/*
 * QCU Transmit descriptor poपूर्णांकer रेजिस्टरs
 */
#घोषणा AR5K_QCU_TXDP_BASE	0x0800		/* Register Address - Queue0 TXDP */
#घोषणा AR5K_QUEUE_TXDP(_q)	AR5K_QUEUE_REG(AR5K_QCU_TXDP_BASE, _q)

/*
 * QCU Transmit enable रेजिस्टर
 */
#घोषणा AR5K_QCU_TXE		0x0840
#घोषणा AR5K_ENABLE_QUEUE(_q)	AR5K_QCU_GLOBAL_WRITE(AR5K_QCU_TXE, _q)
#घोषणा AR5K_QUEUE_ENABLED(_q)	AR5K_QCU_GLOBAL_READ(AR5K_QCU_TXE, _q)

/*
 * QCU Transmit disable रेजिस्टर
 */
#घोषणा AR5K_QCU_TXD		0x0880
#घोषणा AR5K_DISABLE_QUEUE(_q)	AR5K_QCU_GLOBAL_WRITE(AR5K_QCU_TXD, _q)
#घोषणा AR5K_QUEUE_DISABLED(_q)	AR5K_QCU_GLOBAL_READ(AR5K_QCU_TXD, _q)

/*
 * QCU Constant Bit Rate configuration रेजिस्टरs
 */
#घोषणा	AR5K_QCU_CBRCFG_BASE		0x08c0	/* Register Address - Queue0 CBRCFG */
#घोषणा	AR5K_QCU_CBRCFG_INTVAL		0x00ffffff	/* CBR Interval mask */
#घोषणा AR5K_QCU_CBRCFG_INTVAL_S	0
#घोषणा	AR5K_QCU_CBRCFG_ORN_THRES	0xff000000	/* CBR overrun threshold mask */
#घोषणा AR5K_QCU_CBRCFG_ORN_THRES_S	24
#घोषणा	AR5K_QUEUE_CBRCFG(_q)		AR5K_QUEUE_REG(AR5K_QCU_CBRCFG_BASE, _q)

/*
 * QCU Ready समय configuration रेजिस्टरs
 */
#घोषणा	AR5K_QCU_RDYTIMECFG_BASE	0x0900	/* Register Address - Queue0 RDYTIMECFG */
#घोषणा	AR5K_QCU_RDYTIMECFG_INTVAL	0x00ffffff	/* Ready समय पूर्णांकerval mask */
#घोषणा AR5K_QCU_RDYTIMECFG_INTVAL_S	0
#घोषणा	AR5K_QCU_RDYTIMECFG_ENABLE	0x01000000	/* Ready समय enable mask */
#घोषणा AR5K_QUEUE_RDYTIMECFG(_q)	AR5K_QUEUE_REG(AR5K_QCU_RDYTIMECFG_BASE, _q)

/*
 * QCU one shot arm set रेजिस्टरs
 */
#घोषणा	AR5K_QCU_ONESHOTARM_SET		0x0940	/* Register Address -QCU "one shot arm set (?)" */
#घोषणा	AR5K_QCU_ONESHOTARM_SET_M	0x0000ffff

/*
 * QCU one shot arm clear रेजिस्टरs
 */
#घोषणा	AR5K_QCU_ONESHOTARM_CLEAR	0x0980	/* Register Address -QCU "one shot arm clear (?)" */
#घोषणा	AR5K_QCU_ONESHOTARM_CLEAR_M	0x0000ffff

/*
 * QCU misc रेजिस्टरs
 */
#घोषणा AR5K_QCU_MISC_BASE		0x09c0			/* Register Address -Queue0 MISC */
#घोषणा	AR5K_QCU_MISC_FRSHED_M		0x0000000f	/* Frame scheduling mask */
#घोषणा	AR5K_QCU_MISC_FRSHED_ASAP		0	/* ASAP */
#घोषणा	AR5K_QCU_MISC_FRSHED_CBR		1	/* Constant Bit Rate */
#घोषणा	AR5K_QCU_MISC_FRSHED_DBA_GT		2	/* DMA Beacon alert gated */
#घोषणा	AR5K_QCU_MISC_FRSHED_TIM_GT		3	/* TIMT gated */
#घोषणा	AR5K_QCU_MISC_FRSHED_BCN_SENT_GT	4	/* Beacon sent gated */
#घोषणा	AR5K_QCU_MISC_ONESHOT_ENABLE	0x00000010	/* Oneshot enable */
#घोषणा	AR5K_QCU_MISC_CBREXP_DIS	0x00000020	/* Disable CBR expired counter (normal queue) */
#घोषणा	AR5K_QCU_MISC_CBREXP_BCN_DIS	0x00000040	/* Disable CBR expired counter (beacon queue) */
#घोषणा	AR5K_QCU_MISC_BCN_ENABLE	0x00000080	/* Enable Beacon use */
#घोषणा	AR5K_QCU_MISC_CBR_THRES_ENABLE	0x00000100	/* CBR expired threshold enabled */
#घोषणा	AR5K_QCU_MISC_RDY_VEOL_POLICY	0x00000200	/* TXE reset when RDYTIME expired or VEOL */
#घोषणा	AR5K_QCU_MISC_CBR_RESET_CNT	0x00000400	/* CBR threshold (counter) reset */
#घोषणा	AR5K_QCU_MISC_DCU_EARLY		0x00000800	/* DCU early termination */
#घोषणा AR5K_QCU_MISC_DCU_CMP_EN	0x00001000	/* Enable frame compression */
#घोषणा AR5K_QUEUE_MISC(_q)		AR5K_QUEUE_REG(AR5K_QCU_MISC_BASE, _q)


/*
 * QCU status रेजिस्टरs
 */
#घोषणा AR5K_QCU_STS_BASE	0x0a00			/* Register Address - Queue0 STS */
#घोषणा	AR5K_QCU_STS_FRMPENDCNT	0x00000003	/* Frames pending counter */
#घोषणा	AR5K_QCU_STS_CBREXPCNT	0x0000ff00	/* CBR expired counter */
#घोषणा	AR5K_QUEUE_STATUS(_q)	AR5K_QUEUE_REG(AR5K_QCU_STS_BASE, _q)

/*
 * QCU पढ़ोy समय shutकरोwn रेजिस्टर
 */
#घोषणा AR5K_QCU_RDYTIMESHDN	0x0a40
#घोषणा AR5K_QCU_RDYTIMESHDN_M	0x000003ff

/*
 * QCU compression buffer base रेजिस्टरs [5212+]
 */
#घोषणा AR5K_QCU_CBB_SELECT	0x0b00
#घोषणा AR5K_QCU_CBB_ADDR	0x0b04
#घोषणा AR5K_QCU_CBB_ADDR_S	9

/*
 * QCU compression buffer configuration रेजिस्टर [5212+]
 * (buffer size)
 */
#घोषणा AR5K_QCU_CBCFG		0x0b08



/*
 * Distributed Coordination Function (DCF) control unit (DCU)
 * रेजिस्टरs [5211+]
 *
 * These रेजिस्टरs control the various अक्षरacteristics of each queue
 * क्रम 802.11e (WME) compatibility so they go together with
 * QCU रेजिस्टरs in pairs. For each queue we have a QCU mask रेजिस्टर,
 * (0x1000 - 0x102c), a local-IFS settings रेजिस्टर (0x1040 - 0x106c),
 * a retry limit रेजिस्टर (0x1080 - 0x10ac), a channel समय रेजिस्टर
 * (0x10c0 - 0x10ec), a misc-settings रेजिस्टर (0x1100 - 0x112c) and
 * a sequence number रेजिस्टर (0x1140 - 0x116c). It seems that "global"
 * रेजिस्टरs here affect all queues (see use of DCU_GBL_IFS_SLOT in ar5k).
 * We use the same macros here क्रम easier रेजिस्टर access.
 *
 */

/*
 * DCU QCU mask रेजिस्टरs
 */
#घोषणा AR5K_DCU_QCUMASK_BASE	0x1000		/* Register Address -Queue0 DCU_QCUMASK */
#घोषणा AR5K_DCU_QCUMASK_M	0x000003ff
#घोषणा AR5K_QUEUE_QCUMASK(_q)	AR5K_QUEUE_REG(AR5K_DCU_QCUMASK_BASE, _q)

/*
 * DCU local Inter Frame Space settings रेजिस्टर
 */
#घोषणा AR5K_DCU_LCL_IFS_BASE		0x1040			/* Register Address -Queue0 DCU_LCL_IFS */
#घोषणा	AR5K_DCU_LCL_IFS_CW_MIN	        0x000003ff	/* Minimum Contention Winकरोw */
#घोषणा	AR5K_DCU_LCL_IFS_CW_MIN_S	0
#घोषणा	AR5K_DCU_LCL_IFS_CW_MAX	        0x000ffc00	/* Maximum Contention Winकरोw */
#घोषणा	AR5K_DCU_LCL_IFS_CW_MAX_S	10
#घोषणा	AR5K_DCU_LCL_IFS_AIFS		0x0ff00000	/* Arbitrated Interframe Space */
#घोषणा	AR5K_DCU_LCL_IFS_AIFS_S		20
#घोषणा	AR5K_DCU_LCL_IFS_AIFS_MAX	0xfc		/* Anything above that can cause DCU to hang */
#घोषणा	AR5K_QUEUE_DFS_LOCAL_IFS(_q)	AR5K_QUEUE_REG(AR5K_DCU_LCL_IFS_BASE, _q)

/*
 * DCU retry limit रेजिस्टरs
 * all these fields करोn't allow zero values
 */
#घोषणा AR5K_DCU_RETRY_LMT_BASE		0x1080			/* Register Address -Queue0 DCU_RETRY_LMT */
#घोषणा AR5K_DCU_RETRY_LMT_RTS		0x0000000f	/* RTS failure limit. Transmission fails अगर no CTS is received क्रम this number of बार */
#घोषणा AR5K_DCU_RETRY_LMT_RTS_S	0
#घोषणा AR5K_DCU_RETRY_LMT_STA_RTS	0x00003f00	/* STA RTS failure limit. If exceeded CW reset */
#घोषणा AR5K_DCU_RETRY_LMT_STA_RTS_S	8
#घोषणा AR5K_DCU_RETRY_LMT_STA_DATA	0x000fc000	/* STA data failure limit. If exceeded CW reset. */
#घोषणा AR5K_DCU_RETRY_LMT_STA_DATA_S	14
#घोषणा	AR5K_QUEUE_DFS_RETRY_LIMIT(_q)	AR5K_QUEUE_REG(AR5K_DCU_RETRY_LMT_BASE, _q)

/*
 * DCU channel समय रेजिस्टरs
 */
#घोषणा AR5K_DCU_CHAN_TIME_BASE		0x10c0			/* Register Address -Queue0 DCU_CHAN_TIME */
#घोषणा	AR5K_DCU_CHAN_TIME_DUR		0x000fffff	/* Channel समय duration */
#घोषणा	AR5K_DCU_CHAN_TIME_DUR_S	0
#घोषणा	AR5K_DCU_CHAN_TIME_ENABLE	0x00100000	/* Enable channel समय */
#घोषणा AR5K_QUEUE_DFS_CHANNEL_TIME(_q)	AR5K_QUEUE_REG(AR5K_DCU_CHAN_TIME_BASE, _q)

/*
 * DCU misc रेजिस्टरs [5211+]
 *
 * Note: Arbiter lockout control controls the
 * behaviour on low priority queues when we have multiple queues
 * with pending frames. Intra-frame lockout means we रुको until
 * the queue's current frame transmits (with post frame backoff and bursting)
 * beक्रमe we transmit anything अन्यथा and global lockout means we
 * रुको क्रम the whole queue to finish beक्रमe higher priority queues
 * can transmit (this is used on beacon and CAB queues).
 * No lockout means there is no special handling.
 */
#घोषणा AR5K_DCU_MISC_BASE		0x1100			/* Register Address -Queue0 DCU_MISC */
#घोषणा	AR5K_DCU_MISC_BACKOFF		0x0000003f	/* Mask क्रम backoff threshold */
#घोषणा	AR5K_DCU_MISC_ETS_RTS_POL	0x00000040	/* End of transmission series
							station RTS/data failure count
							reset policy (?) */
#घोषणा AR5K_DCU_MISC_ETS_CW_POL	0x00000080	/* End of transmission series
							CW reset policy */
#घोषणा	AR5K_DCU_MISC_FRAG_WAIT		0x00000100	/* Wait क्रम next fragment */
#घोषणा AR5K_DCU_MISC_BACKOFF_FRAG	0x00000200	/* Enable backoff जबतक bursting */
#घोषणा	AR5K_DCU_MISC_HCFPOLL_ENABLE	0x00000800	/* CF - Poll enable */
#घोषणा	AR5K_DCU_MISC_BACKOFF_PERSIST	0x00001000	/* Persistent backoff */
#घोषणा	AR5K_DCU_MISC_FRMPRFTCH_ENABLE	0x00002000	/* Enable frame pre-fetch */
#घोषणा	AR5K_DCU_MISC_VIRTCOL		0x0000c000	/* Mask क्रम Virtual Collision (?) */
#घोषणा	AR5K_DCU_MISC_VIRTCOL_NORMAL	0
#घोषणा	AR5K_DCU_MISC_VIRTCOL_IGNORE	1
#घोषणा	AR5K_DCU_MISC_BCN_ENABLE	0x00010000	/* Enable Beacon use */
#घोषणा	AR5K_DCU_MISC_ARBLOCK_CTL	0x00060000	/* Arbiter lockout control mask */
#घोषणा	AR5K_DCU_MISC_ARBLOCK_CTL_S	17
#घोषणा	AR5K_DCU_MISC_ARBLOCK_CTL_NONE		0	/* No arbiter lockout */
#घोषणा	AR5K_DCU_MISC_ARBLOCK_CTL_INTFRM	1	/* Intra-frame lockout */
#घोषणा	AR5K_DCU_MISC_ARBLOCK_CTL_GLOBAL	2	/* Global lockout */
#घोषणा	AR5K_DCU_MISC_ARBLOCK_IGNORE	0x00080000	/* Ignore Arbiter lockout */
#घोषणा	AR5K_DCU_MISC_SEQ_NUM_INCR_DIS	0x00100000	/* Disable sequence number increment */
#घोषणा	AR5K_DCU_MISC_POST_FR_BKOFF_DIS	0x00200000	/* Disable post-frame backoff */
#घोषणा	AR5K_DCU_MISC_VIRT_COLL_POLICY	0x00400000	/* Virtual Collision cw policy */
#घोषणा	AR5K_DCU_MISC_BLOWN_IFS_POLICY	0x00800000	/* Blown IFS policy (?) */
#घोषणा	AR5K_DCU_MISC_SEQNUM_CTL	0x01000000	/* Sequence number control (?) */
#घोषणा AR5K_QUEUE_DFS_MISC(_q)		AR5K_QUEUE_REG(AR5K_DCU_MISC_BASE, _q)

/*
 * DCU frame sequence number रेजिस्टरs
 */
#घोषणा AR5K_DCU_SEQNUM_BASE		0x1140
#घोषणा	AR5K_DCU_SEQNUM_M		0x00000fff
#घोषणा	AR5K_QUEUE_DCU_SEQNUM(_q)	AR5K_QUEUE_REG(AR5K_DCU_SEQNUM_BASE, _q)

/*
 * DCU global IFS SIFS रेजिस्टर
 */
#घोषणा AR5K_DCU_GBL_IFS_SIFS	0x1030
#घोषणा AR5K_DCU_GBL_IFS_SIFS_M	0x0000ffff

/*
 * DCU global IFS slot पूर्णांकerval रेजिस्टर
 */
#घोषणा AR5K_DCU_GBL_IFS_SLOT	0x1070
#घोषणा AR5K_DCU_GBL_IFS_SLOT_M	0x0000ffff

/*
 * DCU global IFS EIFS रेजिस्टर
 */
#घोषणा AR5K_DCU_GBL_IFS_EIFS	0x10b0
#घोषणा AR5K_DCU_GBL_IFS_EIFS_M	0x0000ffff

/*
 * DCU global IFS misc रेजिस्टर
 *
 * LFSR stands क्रम Linear Feedback Shअगरt Register
 * and it's used क्रम generating pseuकरो-अक्रमom
 * number sequences.
 *
 * (If i understand correctly, अक्रमom numbers are
 * used क्रम idle sensing -multiplied with cwmin/max etc-)
 */
#घोषणा AR5K_DCU_GBL_IFS_MISC			0x10f0			/* Register Address */
#घोषणा	AR5K_DCU_GBL_IFS_MISC_LFSR_SLICE	0x00000007	/* LFSR Slice Select */
#घोषणा	AR5K_DCU_GBL_IFS_MISC_TURBO_MODE	0x00000008	/* Turbo mode */
#घोषणा	AR5K_DCU_GBL_IFS_MISC_SIFS_DUR_USEC	0x000003f0	/* SIFS Duration mask */
#घोषणा	AR5K_DCU_GBL_IFS_MISC_SIFS_DUR_USEC_S	4
#घोषणा	AR5K_DCU_GBL_IFS_MISC_USEC_DUR		0x000ffc00	/* USEC Duration mask */
#घोषणा	AR5K_DCU_GBL_IFS_MISC_USEC_DUR_S	10
#घोषणा	AR5K_DCU_GBL_IFS_MISC_DCU_ARB_DELAY	0x00300000	/* DCU Arbiter delay mask */
#घोषणा AR5K_DCU_GBL_IFS_MISC_SIFS_CNT_RST	0x00400000	/* SIFS cnt reset policy (?) */
#घोषणा AR5K_DCU_GBL_IFS_MISC_AIFS_CNT_RST	0x00800000	/* AIFS cnt reset policy (?) */
#घोषणा AR5K_DCU_GBL_IFS_MISC_RND_LFSR_SL_DIS	0x01000000	/* Disable अक्रमom LFSR slice */

/*
 * DCU frame prefetch control रेजिस्टर
 */
#घोषणा AR5K_DCU_FP			0x1230			/* Register Address */
#घोषणा AR5K_DCU_FP_NOBURST_DCU_EN	0x00000001	/* Enable non-burst prefetch on DCU (?) */
#घोषणा AR5K_DCU_FP_NOBURST_EN		0x00000010	/* Enable non-burst prefetch (?) */
#घोषणा AR5K_DCU_FP_BURST_DCU_EN	0x00000020	/* Enable burst prefetch on DCU (?) */

/*
 * DCU transmit छोड़ो control/status रेजिस्टर
 */
#घोषणा AR5K_DCU_TXP		0x1270			/* Register Address */
#घोषणा	AR5K_DCU_TXP_M		0x000003ff	/* Tx छोड़ो mask */
#घोषणा	AR5K_DCU_TXP_STATUS	0x00010000	/* Tx छोड़ो status */

/*
 * DCU transmit filter table 0 (32 entries)
 * each entry contains a 32bit slice of the
 * 128bit tx filter क्रम each DCU (4 slices per DCU)
 */
#घोषणा AR5K_DCU_TX_FILTER_0_BASE	0x1038
#घोषणा	AR5K_DCU_TX_FILTER_0(_n)	(AR5K_DCU_TX_FILTER_0_BASE + (_n * 64))

/*
 * DCU transmit filter table 1 (16 entries)
 */
#घोषणा AR5K_DCU_TX_FILTER_1_BASE	0x103c
#घोषणा	AR5K_DCU_TX_FILTER_1(_n)	(AR5K_DCU_TX_FILTER_1_BASE + (_n * 64))

/*
 * DCU clear transmit filter रेजिस्टर
 */
#घोषणा AR5K_DCU_TX_FILTER_CLR	0x143c

/*
 * DCU set transmit filter रेजिस्टर
 */
#घोषणा AR5K_DCU_TX_FILTER_SET	0x147c

/*
 * Reset control रेजिस्टर
 */
#घोषणा AR5K_RESET_CTL		0x4000			/* Register Address */
#घोषणा AR5K_RESET_CTL_PCU	0x00000001	/* Protocol Control Unit reset */
#घोषणा AR5K_RESET_CTL_DMA	0x00000002	/* DMA (Rx/Tx) reset [5210] */
#घोषणा	AR5K_RESET_CTL_BASEBAND	0x00000002	/* Baseband reset [5211+] */
#घोषणा AR5K_RESET_CTL_MAC	0x00000004	/* MAC reset (PCU+Baseband ?) [5210] */
#घोषणा AR5K_RESET_CTL_PHY	0x00000008	/* PHY reset [5210] */
#घोषणा AR5K_RESET_CTL_PCI	0x00000010	/* PCI Core reset (पूर्णांकerrupts etc) */

/*
 * Sleep control रेजिस्टर
 */
#घोषणा AR5K_SLEEP_CTL			0x4004			/* Register Address */
#घोषणा AR5K_SLEEP_CTL_SLDUR		0x0000ffff	/* Sleep duration mask */
#घोषणा AR5K_SLEEP_CTL_SLDUR_S		0
#घोषणा AR5K_SLEEP_CTL_SLE		0x00030000	/* Sleep enable mask */
#घोषणा AR5K_SLEEP_CTL_SLE_S		16
#घोषणा AR5K_SLEEP_CTL_SLE_WAKE		0x00000000	/* Force chip awake */
#घोषणा AR5K_SLEEP_CTL_SLE_SLP		0x00010000	/* Force chip sleep */
#घोषणा AR5K_SLEEP_CTL_SLE_ALLOW	0x00020000	/* Normal sleep policy */
#घोषणा AR5K_SLEEP_CTL_SLE_UNITS	0x00000008	/* [5211+] */
#घोषणा AR5K_SLEEP_CTL_DUR_TIM_POL	0x00040000	/* Sleep duration timing policy */
#घोषणा AR5K_SLEEP_CTL_DUR_WRITE_POL	0x00080000	/* Sleep duration ग_लिखो policy */
#घोषणा AR5K_SLEEP_CTL_SLE_POL		0x00100000	/* Sleep policy mode */

/*
 * Interrupt pending रेजिस्टर
 */
#घोषणा AR5K_INTPEND	0x4008
#घोषणा AR5K_INTPEND_M	0x00000001

/*
 * Sleep क्रमce रेजिस्टर
 */
#घोषणा AR5K_SFR	0x400c
#घोषणा AR5K_SFR_EN	0x00000001

/*
 * PCI configuration रेजिस्टर
 * TODO: Fix LED stuff
 */
#घोषणा AR5K_PCICFG			0x4010			/* Register Address */
#घोषणा AR5K_PCICFG_EEAE		0x00000001	/* Eeprom access enable [5210] */
#घोषणा AR5K_PCICFG_SLEEP_CLOCK_EN	0x00000002	/* Enable sleep घड़ी */
#घोषणा AR5K_PCICFG_CLKRUNEN		0x00000004	/* CLKRUN enable [5211+] */
#घोषणा AR5K_PCICFG_EESIZE		0x00000018	/* Mask क्रम EEPROM size [5211+] */
#घोषणा AR5K_PCICFG_EESIZE_S		3
#घोषणा AR5K_PCICFG_EESIZE_4K		0		/* 4K */
#घोषणा AR5K_PCICFG_EESIZE_8K		1		/* 8K */
#घोषणा AR5K_PCICFG_EESIZE_16K		2		/* 16K */
#घोषणा AR5K_PCICFG_EESIZE_FAIL		3		/* Failed to get size [5211+] */
#घोषणा AR5K_PCICFG_LED			0x00000060	/* Led status [5211+] */
#घोषणा AR5K_PCICFG_LED_NONE		0x00000000	/* Default [5211+] */
#घोषणा AR5K_PCICFG_LED_PEND		0x00000020	/* Scan / Auth pending */
#घोषणा AR5K_PCICFG_LED_ASSOC		0x00000040	/* Associated */
#घोषणा	AR5K_PCICFG_BUS_SEL		0x00000380	/* Mask क्रम "bus select" [5211+] (?) */
#घोषणा AR5K_PCICFG_CBEFIX_DIS		0x00000400	/* Disable CBE fix */
#घोषणा AR5K_PCICFG_SL_INTEN		0x00000800	/* Enable पूर्णांकerrupts when asleep */
#घोषणा AR5K_PCICFG_LED_BCTL		0x00001000	/* Led blink (?) [5210] */
#घोषणा AR5K_PCICFG_RETRY_FIX		0x00001000	/* Enable pci core retry fix */
#घोषणा AR5K_PCICFG_SL_INPEN		0x00002000	/* Sleep even with pending पूर्णांकerrupts*/
#घोषणा AR5K_PCICFG_SPWR_DN		0x00010000	/* Mask क्रम घातer status */
#घोषणा AR5K_PCICFG_LEDMODE		0x000e0000	/* Ledmode [5211+] */
#घोषणा AR5K_PCICFG_LEDMODE_PROP	0x00000000	/* Blink on standard traffic [5211+] */
#घोषणा AR5K_PCICFG_LEDMODE_PROM	0x00020000	/* Default mode (blink on any traffic) [5211+] */
#घोषणा AR5K_PCICFG_LEDMODE_PWR		0x00040000	/* Some other blinking mode  (?) [5211+] */
#घोषणा AR5K_PCICFG_LEDMODE_RAND	0x00060000	/* Ranकरोm blinking (?) [5211+] */
#घोषणा AR5K_PCICFG_LEDBLINK		0x00700000	/* Led blink rate */
#घोषणा AR5K_PCICFG_LEDBLINK_S		20
#घोषणा AR5K_PCICFG_LEDSLOW		0x00800000	/* Slowest led blink rate [5211+] */
#घोषणा AR5K_PCICFG_LEDSTATE				\
	(AR5K_PCICFG_LED | AR5K_PCICFG_LEDMODE |	\
	AR5K_PCICFG_LEDBLINK | AR5K_PCICFG_LEDSLOW)
#घोषणा	AR5K_PCICFG_SLEEP_CLOCK_RATE	0x03000000	/* Sleep घड़ी rate */
#घोषणा	AR5K_PCICFG_SLEEP_CLOCK_RATE_S	24

/*
 * "General Purpose Input/Output" (GPIO) control रेजिस्टर
 *
 * I'm not sure about this but after looking at the code
 * क्रम all chipsets here is what i got.
 *
 * We have 6 GPIOs (pins), each GPIO has 4 modes (2 bits)
 * Mode 0 -> always input
 * Mode 1 -> output when GPIODO क्रम this GPIO is set to 0
 * Mode 2 -> output when GPIODO क्रम this GPIO is set to 1
 * Mode 3 -> always output
 *
 * For more infos check out get_gpio/set_gpio and
 * set_gpio_input/set_gpio_output functs.
 * For more infos on gpio पूर्णांकerrupt check out set_gpio_पूर्णांकr.
 */
#घोषणा AR5K_NUM_GPIO	6

#घोषणा AR5K_GPIOCR		0x4014				/* Register Address */
#घोषणा AR5K_GPIOCR_INT_ENA	0x00008000		/* Enable GPIO पूर्णांकerrupt */
#घोषणा AR5K_GPIOCR_INT_SELL	0x00000000		/* Generate पूर्णांकerrupt when pin is low */
#घोषणा AR5K_GPIOCR_INT_SELH	0x00010000		/* Generate पूर्णांकerrupt when pin is high */
#घोषणा AR5K_GPIOCR_IN(n)	(0 << ((n) * 2))	/* Mode 0 क्रम pin n */
#घोषणा AR5K_GPIOCR_OUT0(n)	(1 << ((n) * 2))	/* Mode 1 क्रम pin n */
#घोषणा AR5K_GPIOCR_OUT1(n)	(2 << ((n) * 2))	/* Mode 2 क्रम pin n */
#घोषणा AR5K_GPIOCR_OUT(n)	(3 << ((n) * 2))	/* Mode 3 क्रम pin n */
#घोषणा AR5K_GPIOCR_INT_SEL(n)	((n) << 12)		/* Interrupt क्रम GPIO pin n */

/*
 * "General Purpose Input/Output" (GPIO) data output रेजिस्टर
 */
#घोषणा AR5K_GPIODO	0x4018

/*
 * "General Purpose Input/Output" (GPIO) data input रेजिस्टर
 */
#घोषणा AR5K_GPIODI	0x401c
#घोषणा AR5K_GPIODI_M	0x0000002f

/*
 * Silicon revision रेजिस्टर
 */
#घोषणा AR5K_SREV		0x4020			/* Register Address */
#घोषणा AR5K_SREV_REV		0x0000000f	/* Mask क्रम revision */
#घोषणा AR5K_SREV_REV_S		0
#घोषणा AR5K_SREV_VER		0x000000ff	/* Mask क्रम version */
#घोषणा AR5K_SREV_VER_S		4

/*
 * TXE ग_लिखो posting रेजिस्टर
 */
#घोषणा	AR5K_TXEPOST	0x4028

/*
 * QCU sleep mask
 */
#घोषणा	AR5K_QCU_SLEEP_MASK	0x402c

/* 0x4068 is compression buffer configuration
 * रेजिस्टर on 5414 and pm configuration रेजिस्टर
 * on 5424 and newer pci-e chips. */

/*
 * Compression buffer configuration
 * रेजिस्टर (enable/disable) [5414]
 */
#घोषणा AR5K_5414_CBCFG		0x4068
#घोषणा AR5K_5414_CBCFG_BUF_DIS	0x10	/* Disable buffer */

/*
 * PCI-E Power management configuration
 * and status रेजिस्टर [5424+]
 */
#घोषणा	AR5K_PCIE_PM_CTL		0x4068			/* Register address */
/* Only 5424 */
#घोषणा	AR5K_PCIE_PM_CTL_L1_WHEN_D2	0x00000001	/* enable PCIe core enter L1
							when d2_sleep_en is निश्चितed */
#घोषणा	AR5K_PCIE_PM_CTL_L0_L0S_CLEAR	0x00000002	/* Clear L0 and L0S counters */
#घोषणा	AR5K_PCIE_PM_CTL_L0_L0S_EN	0x00000004	/* Start L0 nd L0S counters */
#घोषणा	AR5K_PCIE_PM_CTL_LDRESET_EN	0x00000008	/* Enable reset when link goes
							करोwn */
/* Wake On Wireless */
#घोषणा	AR5K_PCIE_PM_CTL_PME_EN		0x00000010	/* PME Enable */
#घोषणा	AR5K_PCIE_PM_CTL_AUX_PWR_DET	0x00000020	/* Aux घातer detect */
#घोषणा	AR5K_PCIE_PM_CTL_PME_CLEAR	0x00000040	/* Clear PME */
#घोषणा	AR5K_PCIE_PM_CTL_PSM_D0		0x00000080
#घोषणा	AR5K_PCIE_PM_CTL_PSM_D1		0x00000100
#घोषणा	AR5K_PCIE_PM_CTL_PSM_D2		0x00000200
#घोषणा	AR5K_PCIE_PM_CTL_PSM_D3		0x00000400

/*
 * PCI-E Workaround enable रेजिस्टर
 */
#घोषणा	AR5K_PCIE_WAEN	0x407c

/*
 * PCI-E Serializer/Deserializer
 * रेजिस्टरs
 */
#घोषणा	AR5K_PCIE_SERDES	0x4080
#घोषणा	AR5K_PCIE_SERDES_RESET	0x4084

/*====EEPROM REGISTERS====*/

/*
 * EEPROM access रेजिस्टरs
 *
 * Here we got a dअगरference between 5210/5211-12
 * पढ़ो data रेजिस्टर क्रम 5210 is at 0x6800 and
 * status रेजिस्टर is at 0x6c00. There is also
 * no eeprom command रेजिस्टर on 5210 and the
 * offsets are dअगरferent.
 *
 * To पढ़ो eeprom data क्रम a specअगरic offset:
 * 5210 - enable eeprom access (AR5K_PCICFG_EEAE)
 *        पढ़ो AR5K_EEPROM_BASE +(4 * offset)
 *        check the eeprom status रेजिस्टर
 *        and पढ़ो eeprom data रेजिस्टर.
 *
 * 5211 - ग_लिखो offset to AR5K_EEPROM_BASE
 * 5212   ग_लिखो AR5K_EEPROM_CMD_READ on AR5K_EEPROM_CMD
 *        check the eeprom status रेजिस्टर
 *        and पढ़ो eeprom data रेजिस्टर.
 *
 * To ग_लिखो eeprom data क्रम a specअगरic offset:
 * 5210 - enable eeprom access (AR5K_PCICFG_EEAE)
 *        ग_लिखो data to AR5K_EEPROM_BASE +(4 * offset)
 *        check the eeprom status रेजिस्टर
 * 5211 - ग_लिखो AR5K_EEPROM_CMD_RESET on AR5K_EEPROM_CMD
 * 5212   ग_लिखो offset to AR5K_EEPROM_BASE
 *        ग_लिखो data to data रेजिस्टर
 *	  ग_लिखो AR5K_EEPROM_CMD_WRITE on AR5K_EEPROM_CMD
 *        check the eeprom status रेजिस्टर
 *
 * For more infos check eeprom_* functs and the ar5k.c
 * file posted in madwअगरi-devel mailing list.
 * http://sourceक्रमge.net/mailarchive/message.php?msg_id=8966525
 *
 */
#घोषणा AR5K_EEPROM_BASE	0x6000

/*
 * EEPROM data रेजिस्टर
 */
#घोषणा AR5K_EEPROM_DATA_5211	0x6004
#घोषणा AR5K_EEPROM_DATA_5210	0x6800
#घोषणा	AR5K_EEPROM_DATA	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_EEPROM_DATA_5210 : AR5K_EEPROM_DATA_5211)

/*
 * EEPROM command रेजिस्टर
 */
#घोषणा AR5K_EEPROM_CMD		0x6008			/* Register Address */
#घोषणा AR5K_EEPROM_CMD_READ	0x00000001	/* EEPROM पढ़ो */
#घोषणा AR5K_EEPROM_CMD_WRITE	0x00000002	/* EEPROM ग_लिखो */
#घोषणा AR5K_EEPROM_CMD_RESET	0x00000004	/* EEPROM reset */

/*
 * EEPROM status रेजिस्टर
 */
#घोषणा AR5K_EEPROM_STAT_5210	0x6c00			/* Register Address [5210] */
#घोषणा AR5K_EEPROM_STAT_5211	0x600c			/* Register Address [5211+] */
#घोषणा	AR5K_EEPROM_STATUS	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_EEPROM_STAT_5210 : AR5K_EEPROM_STAT_5211)
#घोषणा AR5K_EEPROM_STAT_RDERR	0x00000001	/* EEPROM पढ़ो failed */
#घोषणा AR5K_EEPROM_STAT_RDDONE	0x00000002	/* EEPROM पढ़ो successful */
#घोषणा AR5K_EEPROM_STAT_WRERR	0x00000004	/* EEPROM ग_लिखो failed */
#घोषणा AR5K_EEPROM_STAT_WRDONE	0x00000008	/* EEPROM ग_लिखो successful */

/*
 * EEPROM config रेजिस्टर
 */
#घोषणा AR5K_EEPROM_CFG			0x6010			/* Register Address */
#घोषणा AR5K_EEPROM_CFG_SIZE		0x00000003		/* Size determination override */
#घोषणा AR5K_EEPROM_CFG_SIZE_AUTO	0
#घोषणा AR5K_EEPROM_CFG_SIZE_4KBIT	1
#घोषणा AR5K_EEPROM_CFG_SIZE_8KBIT	2
#घोषणा AR5K_EEPROM_CFG_SIZE_16KBIT	3
#घोषणा AR5K_EEPROM_CFG_WR_WAIT_DIS	0x00000004	/* Disable ग_लिखो रुको */
#घोषणा AR5K_EEPROM_CFG_CLK_RATE	0x00000018	/* Clock rate */
#घोषणा AR5K_EEPROM_CFG_CLK_RATE_S		3
#घोषणा AR5K_EEPROM_CFG_CLK_RATE_156KHZ	0
#घोषणा AR5K_EEPROM_CFG_CLK_RATE_312KHZ	1
#घोषणा AR5K_EEPROM_CFG_CLK_RATE_625KHZ	2
#घोषणा AR5K_EEPROM_CFG_PROT_KEY	0x00ffff00      /* Protection key */
#घोषणा AR5K_EEPROM_CFG_PROT_KEY_S	8
#घोषणा AR5K_EEPROM_CFG_LIND_EN		0x01000000	/* Enable length indicator (?) */


/*
 * TODO: Wake On Wireless रेजिस्टरs
 * Range 0x7000 - 0x7ce0
 */

/*
 * Protocol Control Unit (PCU) रेजिस्टरs
 */
/*
 * Used क्रम checking initial रेजिस्टर ग_लिखोs
 * during channel reset (see reset func)
 */
#घोषणा AR5K_PCU_MIN	0x8000
#घोषणा AR5K_PCU_MAX	0x8fff

/*
 * First station id रेजिस्टर (Lower 32 bits of MAC address)
 */
#घोषणा AR5K_STA_ID0		0x8000
#घोषणा	AR5K_STA_ID0_ARRD_L32	0xffffffff

/*
 * Second station id रेजिस्टर (Upper 16 bits of MAC address + PCU settings)
 */
#घोषणा AR5K_STA_ID1			0x8004			/* Register Address */
#घोषणा	AR5K_STA_ID1_ADDR_U16		0x0000ffff	/* Upper 16 bits of MAC address */
#घोषणा AR5K_STA_ID1_AP			0x00010000	/* Set AP mode */
#घोषणा AR5K_STA_ID1_ADHOC		0x00020000	/* Set Ad-Hoc mode */
#घोषणा AR5K_STA_ID1_PWR_SV		0x00040000	/* Power save reporting */
#घोषणा AR5K_STA_ID1_NO_KEYSRCH		0x00080000	/* No key search */
#घोषणा AR5K_STA_ID1_NO_PSPOLL		0x00100000	/* No घातer save polling [5210] */
#घोषणा AR5K_STA_ID1_PCF_5211		0x00100000	/* Enable PCF on [5211+] */
#घोषणा AR5K_STA_ID1_PCF_5210		0x00200000	/* Enable PCF on [5210]*/
#घोषणा	AR5K_STA_ID1_PCF		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_STA_ID1_PCF_5210 : AR5K_STA_ID1_PCF_5211)
#घोषणा AR5K_STA_ID1_DEFAULT_ANTENNA	0x00200000	/* Use शेष antenna */
#घोषणा AR5K_STA_ID1_DESC_ANTENNA	0x00400000	/* Update antenna from descriptor */
#घोषणा AR5K_STA_ID1_RTS_DEF_ANTENNA	0x00800000	/* Use शेष antenna क्रम RTS */
#घोषणा AR5K_STA_ID1_ACKCTS_6MB		0x01000000	/* Rate to use क्रम ACK/CTS. 0: highest mandatory rate <= RX rate; 1: 1Mbps in B mode */
#घोषणा AR5K_STA_ID1_BASE_RATE_11B	0x02000000	/* 802.11b base rate. 0: 1, 2, 5.5 and 11Mbps; 1: 1 and 2Mbps. [5211+] */
#घोषणा AR5K_STA_ID1_SELFGEN_DEF_ANT	0x04000000	/* Use def. antenna क्रम self generated frames */
#घोषणा AR5K_STA_ID1_CRYPT_MIC_EN	0x08000000	/* Enable MIC */
#घोषणा AR5K_STA_ID1_KEYSRCH_MODE	0x10000000	/* Look up key when key id != 0 */
#घोषणा AR5K_STA_ID1_PRESERVE_SEQ_NUM	0x20000000	/* Preserve sequence number */
#घोषणा AR5K_STA_ID1_CBCIV_ENDIAN	0x40000000	/* ??? */
#घोषणा AR5K_STA_ID1_KEYSRCH_MCAST	0x80000000	/* Do key cache search क्रम mcast frames */

#घोषणा	AR5K_STA_ID1_ANTENNA_SETTINGS	(AR5K_STA_ID1_DEFAULT_ANTENNA | \
					AR5K_STA_ID1_DESC_ANTENNA | \
					AR5K_STA_ID1_RTS_DEF_ANTENNA | \
					AR5K_STA_ID1_SELFGEN_DEF_ANT)

/*
 * First BSSID रेजिस्टर (MAC address, lower 32bits)
 */
#घोषणा AR5K_BSS_ID0	0x8008

/*
 * Second BSSID रेजिस्टर (MAC address in upper 16 bits)
 *
 * AID: Association ID
 */
#घोषणा AR5K_BSS_ID1		0x800c
#घोषणा AR5K_BSS_ID1_AID	0xffff0000
#घोषणा AR5K_BSS_ID1_AID_S	16

/*
 * Backoff slot समय रेजिस्टर
 */
#घोषणा AR5K_SLOT_TIME	0x8010

/*
 * ACK/CTS समयout रेजिस्टर
 */
#घोषणा AR5K_TIME_OUT		0x8014			/* Register Address */
#घोषणा AR5K_TIME_OUT_ACK	0x00001fff	/* ACK समयout mask */
#घोषणा AR5K_TIME_OUT_ACK_S	0
#घोषणा AR5K_TIME_OUT_CTS	0x1fff0000	/* CTS समयout mask */
#घोषणा AR5K_TIME_OUT_CTS_S	16

/*
 * RSSI threshold रेजिस्टर
 */
#घोषणा AR5K_RSSI_THR			0x8018		/* Register Address */
#घोषणा AR5K_RSSI_THR_M			0x000000ff	/* Mask क्रम RSSI threshold [5211+] */
#घोषणा AR5K_RSSI_THR_BMISS_5210	0x00000700	/* Mask क्रम Beacon Missed threshold [5210] */
#घोषणा AR5K_RSSI_THR_BMISS_5210_S	8
#घोषणा AR5K_RSSI_THR_BMISS_5211	0x0000ff00	/* Mask क्रम Beacon Missed threshold [5211+] */
#घोषणा AR5K_RSSI_THR_BMISS_5211_S	8
#घोषणा	AR5K_RSSI_THR_BMISS		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_RSSI_THR_BMISS_5210 : AR5K_RSSI_THR_BMISS_5211)
#घोषणा	AR5K_RSSI_THR_BMISS_S		8

/*
 * 5210 has more PCU रेजिस्टरs because there is no QCU/DCU
 * so queue parameters are set here, this way a lot common
 * रेजिस्टरs have dअगरferent address क्रम 5210. To make things
 * easier we define a macro based on ah->ah_version क्रम common
 * रेजिस्टरs with dअगरferent addresses and common flags.
 */

/*
 * Retry limit रेजिस्टर
 *
 * Retry limit रेजिस्टर क्रम 5210 (no QCU/DCU so it's करोne in PCU)
 */
#घोषणा AR5K_NODCU_RETRY_LMT		0x801c			/* Register Address */
#घोषणा AR5K_NODCU_RETRY_LMT_SH_RETRY	0x0000000f	/* Short retry limit mask */
#घोषणा AR5K_NODCU_RETRY_LMT_SH_RETRY_S	0
#घोषणा AR5K_NODCU_RETRY_LMT_LG_RETRY	0x000000f0	/* Long retry mask */
#घोषणा AR5K_NODCU_RETRY_LMT_LG_RETRY_S	4
#घोषणा AR5K_NODCU_RETRY_LMT_SSH_RETRY	0x00003f00	/* Station लघु retry limit mask */
#घोषणा AR5K_NODCU_RETRY_LMT_SSH_RETRY_S	8
#घोषणा AR5K_NODCU_RETRY_LMT_SLG_RETRY	0x000fc000	/* Station दीर्घ retry limit mask */
#घोषणा AR5K_NODCU_RETRY_LMT_SLG_RETRY_S	14
#घोषणा AR5K_NODCU_RETRY_LMT_CW_MIN	0x3ff00000	/* Minimum contention winकरोw mask */
#घोषणा AR5K_NODCU_RETRY_LMT_CW_MIN_S	20

/*
 * Transmit latency रेजिस्टर
 */
#घोषणा AR5K_USEC_5210			0x8020			/* Register Address [5210] */
#घोषणा AR5K_USEC_5211			0x801c			/* Register Address [5211+] */
#घोषणा AR5K_USEC			(ah->ah_version == AR5K_AR5210 ? \
					AR5K_USEC_5210 : AR5K_USEC_5211)
#घोषणा AR5K_USEC_1			0x0000007f	/* घड़ी cycles क्रम 1us */
#घोषणा AR5K_USEC_1_S			0
#घोषणा AR5K_USEC_32			0x00003f80	/* घड़ी cycles क्रम 1us जबतक on 32MHz घड़ी */
#घोषणा AR5K_USEC_32_S			7
#घोषणा AR5K_USEC_TX_LATENCY_5211	0x007fc000
#घोषणा AR5K_USEC_TX_LATENCY_5211_S	14
#घोषणा AR5K_USEC_RX_LATENCY_5211	0x1f800000
#घोषणा AR5K_USEC_RX_LATENCY_5211_S	23
#घोषणा AR5K_USEC_TX_LATENCY_5210	0x000fc000	/* also क्रम 5311 */
#घोषणा AR5K_USEC_TX_LATENCY_5210_S	14
#घोषणा AR5K_USEC_RX_LATENCY_5210	0x03f00000	/* also क्रम 5311 */
#घोषणा AR5K_USEC_RX_LATENCY_5210_S	20

/*
 * PCU beacon control रेजिस्टर
 */
#घोषणा AR5K_BEACON_5210	0x8024			/*Register Address [5210] */
#घोषणा AR5K_BEACON_5211	0x8020			/*Register Address [5211+] */
#घोषणा AR5K_BEACON		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_BEACON_5210 : AR5K_BEACON_5211)
#घोषणा AR5K_BEACON_PERIOD	0x0000ffff	/* Mask क्रम beacon period */
#घोषणा AR5K_BEACON_PERIOD_S	0
#घोषणा AR5K_BEACON_TIM		0x007f0000	/* Mask क्रम TIM offset */
#घोषणा AR5K_BEACON_TIM_S	16
#घोषणा AR5K_BEACON_ENABLE	0x00800000	/* Enable beacons */
#घोषणा AR5K_BEACON_RESET_TSF	0x01000000	/* Force TSF reset */

/*
 * CFP period रेजिस्टर
 */
#घोषणा AR5K_CFP_PERIOD_5210	0x8028
#घोषणा AR5K_CFP_PERIOD_5211	0x8024
#घोषणा AR5K_CFP_PERIOD		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_CFP_PERIOD_5210 : AR5K_CFP_PERIOD_5211)

/*
 * Next beacon समय रेजिस्टर
 */
#घोषणा AR5K_TIMER0_5210	0x802c
#घोषणा AR5K_TIMER0_5211	0x8028
#घोषणा AR5K_TIMER0		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER0_5210 : AR5K_TIMER0_5211)

/*
 * Next DMA beacon alert रेजिस्टर
 */
#घोषणा AR5K_TIMER1_5210	0x8030
#घोषणा AR5K_TIMER1_5211	0x802c
#घोषणा AR5K_TIMER1		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER1_5210 : AR5K_TIMER1_5211)

/*
 * Next software beacon alert रेजिस्टर
 */
#घोषणा AR5K_TIMER2_5210	0x8034
#घोषणा AR5K_TIMER2_5211	0x8030
#घोषणा AR5K_TIMER2		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER2_5210 : AR5K_TIMER2_5211)

/*
 * Next ATIM winकरोw समय रेजिस्टर
 */
#घोषणा AR5K_TIMER3_5210	0x8038
#घोषणा AR5K_TIMER3_5211	0x8034
#घोषणा AR5K_TIMER3		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER3_5210 : AR5K_TIMER3_5211)


/*
 * 5210 First पूर्णांकer frame spacing रेजिस्टर (IFS)
 */
#घोषणा AR5K_IFS0		0x8040
#घोषणा AR5K_IFS0_SIFS		0x000007ff
#घोषणा AR5K_IFS0_SIFS_S	0
#घोषणा AR5K_IFS0_DIFS		0x007ff800
#घोषणा AR5K_IFS0_DIFS_S	11

/*
 * 5210 Second पूर्णांकer frame spacing रेजिस्टर (IFS)
 */
#घोषणा AR5K_IFS1		0x8044
#घोषणा AR5K_IFS1_PIFS		0x00000fff
#घोषणा AR5K_IFS1_PIFS_S	0
#घोषणा AR5K_IFS1_EIFS		0x03fff000
#घोषणा AR5K_IFS1_EIFS_S	12
#घोषणा AR5K_IFS1_CS_EN		0x04000000
#घोषणा AR5K_IFS1_CS_EN_S	26

/*
 * CFP duration रेजिस्टर
 */
#घोषणा AR5K_CFP_DUR_5210	0x8048
#घोषणा AR5K_CFP_DUR_5211	0x8038
#घोषणा AR5K_CFP_DUR		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_CFP_DUR_5210 : AR5K_CFP_DUR_5211)

/*
 * Receive filter रेजिस्टर
 */
#घोषणा AR5K_RX_FILTER_5210	0x804c			/* Register Address [5210] */
#घोषणा AR5K_RX_FILTER_5211	0x803c			/* Register Address [5211+] */
#घोषणा AR5K_RX_FILTER		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_RX_FILTER_5210 : AR5K_RX_FILTER_5211)
#घोषणा	AR5K_RX_FILTER_UCAST	0x00000001	/* Don't filter unicast frames */
#घोषणा	AR5K_RX_FILTER_MCAST	0x00000002	/* Don't filter multicast frames */
#घोषणा	AR5K_RX_FILTER_BCAST	0x00000004	/* Don't filter broadcast frames */
#घोषणा	AR5K_RX_FILTER_CONTROL	0x00000008	/* Don't filter control frames */
#घोषणा	AR5K_RX_FILTER_BEACON	0x00000010	/* Don't filter beacon frames */
#घोषणा	AR5K_RX_FILTER_PROM	0x00000020	/* Set promiscuous mode */
#घोषणा	AR5K_RX_FILTER_XRPOLL	0x00000040	/* Don't filter XR poll frame [5212+] */
#घोषणा	AR5K_RX_FILTER_PROBEREQ 0x00000080	/* Don't filter probe requests [5212+] */
#घोषणा	AR5K_RX_FILTER_PHYERR_5212	0x00000100	/* Don't filter phy errors [5212+] */
#घोषणा	AR5K_RX_FILTER_RADARERR_5212	0x00000200	/* Don't filter phy radar errors [5212+] */
#घोषणा AR5K_RX_FILTER_PHYERR_5211	0x00000040	/* [5211] */
#घोषणा AR5K_RX_FILTER_RADARERR_5211	0x00000080	/* [5211] */
#घोषणा AR5K_RX_FILTER_PHYERR  \
	((ah->ah_version == AR5K_AR5211 ? \
	AR5K_RX_FILTER_PHYERR_5211 : AR5K_RX_FILTER_PHYERR_5212))
#घोषणा        AR5K_RX_FILTER_RADARERR \
	((ah->ah_version == AR5K_AR5211 ? \
	AR5K_RX_FILTER_RADARERR_5211 : AR5K_RX_FILTER_RADARERR_5212))

/*
 * Multicast filter रेजिस्टर (lower 32 bits)
 */
#घोषणा AR5K_MCAST_FILTER0_5210	0x8050
#घोषणा AR5K_MCAST_FILTER0_5211	0x8040
#घोषणा AR5K_MCAST_FILTER0	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_MCAST_FILTER0_5210 : AR5K_MCAST_FILTER0_5211)

/*
 * Multicast filter रेजिस्टर (higher 16 bits)
 */
#घोषणा AR5K_MCAST_FILTER1_5210	0x8054
#घोषणा AR5K_MCAST_FILTER1_5211	0x8044
#घोषणा AR5K_MCAST_FILTER1	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_MCAST_FILTER1_5210 : AR5K_MCAST_FILTER1_5211)


/*
 * Transmit mask रेजिस्टर (lower 32 bits) [5210]
 */
#घोषणा AR5K_TX_MASK0	0x8058

/*
 * Transmit mask रेजिस्टर (higher 16 bits) [5210]
 */
#घोषणा AR5K_TX_MASK1	0x805c

/*
 * Clear transmit mask [5210]
 */
#घोषणा AR5K_CLR_TMASK	0x8060

/*
 * Trigger level रेजिस्टर (beक्रमe transmission) [5210]
 */
#घोषणा AR5K_TRIG_LVL	0x8064


/*
 * PCU Diagnostic रेजिस्टर
 *
 * Used क्रम tweaking/diagnostics.
 */
#घोषणा AR5K_DIAG_SW_5210		0x8068			/* Register Address [5210] */
#घोषणा AR5K_DIAG_SW_5211		0x8048			/* Register Address [5211+] */
#घोषणा AR5K_DIAG_SW			(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_5210 : AR5K_DIAG_SW_5211)
#घोषणा AR5K_DIAG_SW_DIS_WEP_ACK	0x00000001	/* Disable ACKs अगर WEP key is invalid */
#घोषणा AR5K_DIAG_SW_DIS_ACK		0x00000002	/* Disable ACKs */
#घोषणा AR5K_DIAG_SW_DIS_CTS		0x00000004	/* Disable CTSs */
#घोषणा AR5K_DIAG_SW_DIS_ENC		0x00000008	/* Disable HW encryption */
#घोषणा AR5K_DIAG_SW_DIS_DEC		0x00000010	/* Disable HW decryption */
#घोषणा AR5K_DIAG_SW_DIS_TX_5210	0x00000020	/* Disable transmit [5210] */
#घोषणा AR5K_DIAG_SW_DIS_RX_5210	0x00000040	/* Disable receive */
#घोषणा AR5K_DIAG_SW_DIS_RX_5211	0x00000020
#घोषणा	AR5K_DIAG_SW_DIS_RX		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_DIS_RX_5210 : AR5K_DIAG_SW_DIS_RX_5211)
#घोषणा AR5K_DIAG_SW_LOOP_BACK_5210	0x00000080	/* TX Data Loopback (i guess it goes with DIS_TX) [5210] */
#घोषणा AR5K_DIAG_SW_LOOP_BACK_5211	0x00000040
#घोषणा AR5K_DIAG_SW_LOOP_BACK		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_LOOP_BACK_5210 : AR5K_DIAG_SW_LOOP_BACK_5211)
#घोषणा AR5K_DIAG_SW_CORR_FCS_5210	0x00000100	/* Generate invalid TX FCS */
#घोषणा AR5K_DIAG_SW_CORR_FCS_5211	0x00000080
#घोषणा AR5K_DIAG_SW_CORR_FCS		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_CORR_FCS_5210 : AR5K_DIAG_SW_CORR_FCS_5211)
#घोषणा AR5K_DIAG_SW_CHAN_INFO_5210	0x00000200	/* Add 56 bytes of channel info beक्रमe the frame data in the RX buffer */
#घोषणा AR5K_DIAG_SW_CHAN_INFO_5211	0x00000100
#घोषणा AR5K_DIAG_SW_CHAN_INFO		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_CHAN_INFO_5210 : AR5K_DIAG_SW_CHAN_INFO_5211)
#घोषणा AR5K_DIAG_SW_EN_SCRAM_SEED_5210	0x00000400	/* Enable fixed scrambler seed */
#घोषणा AR5K_DIAG_SW_EN_SCRAM_SEED_5211	0x00000200
#घोषणा AR5K_DIAG_SW_EN_SCRAM_SEED	(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_EN_SCRAM_SEED_5210 : AR5K_DIAG_SW_EN_SCRAM_SEED_5211)
#घोषणा AR5K_DIAG_SW_ECO_ENABLE		0x00000400	/* [5211+] */
#घोषणा AR5K_DIAG_SW_SCVRAM_SEED	0x0003f800	/* [5210] */
#घोषणा AR5K_DIAG_SW_SCRAM_SEED_M	0x0001fc00	/* Scrambler seed mask */
#घोषणा AR5K_DIAG_SW_SCRAM_SEED_S	10
#घोषणा AR5K_DIAG_SW_DIS_SEQ_INC_5210	0x00040000	/* Disable seqnum increment (?)[5210] */
#घोषणा AR5K_DIAG_SW_FRAME_NV0_5210	0x00080000
#घोषणा AR5K_DIAG_SW_FRAME_NV0_5211	0x00020000	/* Accept frames of non-zero protocol number */
#घोषणा	AR5K_DIAG_SW_FRAME_NV0		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_FRAME_NV0_5210 : AR5K_DIAG_SW_FRAME_NV0_5211)
#घोषणा AR5K_DIAG_SW_OBSPT_M		0x000c0000	/* Observation poपूर्णांक select (?) */
#घोषणा AR5K_DIAG_SW_OBSPT_S		18
#घोषणा AR5K_DIAG_SW_RX_CLEAR_HIGH	0x00100000	/* Ignore carrier sense */
#घोषणा AR5K_DIAG_SW_IGNORE_CARR_SENSE	0x00200000	/* Ignore भव carrier sense */
#घोषणा AR5K_DIAG_SW_CHANNEL_IDLE_HIGH	0x00400000	/* Force channel idle high */
#घोषणा AR5K_DIAG_SW_PHEAR_ME		0x00800000	/* ??? */

/*
 * TSF (घड़ी) रेजिस्टर (lower 32 bits)
 */
#घोषणा AR5K_TSF_L32_5210	0x806c
#घोषणा AR5K_TSF_L32_5211	0x804c
#घोषणा	AR5K_TSF_L32		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TSF_L32_5210 : AR5K_TSF_L32_5211)

/*
 * TSF (घड़ी) रेजिस्टर (higher 32 bits)
 */
#घोषणा AR5K_TSF_U32_5210	0x8070
#घोषणा AR5K_TSF_U32_5211	0x8050
#घोषणा	AR5K_TSF_U32		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TSF_U32_5210 : AR5K_TSF_U32_5211)

/*
 * Last beacon बारtamp रेजिस्टर (Read Only)
 */
#घोषणा AR5K_LAST_TSTP	0x8080

/*
 * ADDAC test रेजिस्टर [5211+]
 */
#घोषणा AR5K_ADDAC_TEST			0x8054			/* Register Address */
#घोषणा AR5K_ADDAC_TEST_TXCONT		0x00000001	/* Test continuous tx */
#घोषणा AR5K_ADDAC_TEST_TST_MODE	0x00000002	/* Test mode */
#घोषणा AR5K_ADDAC_TEST_LOOP_EN		0x00000004	/* Enable loop */
#घोषणा AR5K_ADDAC_TEST_LOOP_LEN	0x00000008	/* Loop length (field) */
#घोषणा AR5K_ADDAC_TEST_USE_U8		0x00004000	/* Use upper 8 bits */
#घोषणा AR5K_ADDAC_TEST_MSB		0x00008000	/* State of MSB */
#घोषणा AR5K_ADDAC_TEST_TRIG_SEL	0x00010000	/* Trigger select */
#घोषणा AR5K_ADDAC_TEST_TRIG_PTY	0x00020000	/* Trigger polarity */
#घोषणा AR5K_ADDAC_TEST_RXCONT		0x00040000	/* Continuous capture */
#घोषणा AR5K_ADDAC_TEST_CAPTURE		0x00080000	/* Begin capture */
#घोषणा AR5K_ADDAC_TEST_TST_ARM		0x00100000	/* ARM rx buffer क्रम capture */

/*
 * Default antenna रेजिस्टर [5211+]
 */
#घोषणा AR5K_DEFAULT_ANTENNA	0x8058

/*
 * Frame control QoS mask रेजिस्टर (?) [5211+]
 * (FC_QOS_MASK)
 */
#घोषणा AR5K_FRAME_CTL_QOSM	0x805c

/*
 * Seq mask रेजिस्टर (?) [5211+]
 */
#घोषणा AR5K_SEQ_MASK	0x8060

/*
 * Retry count रेजिस्टर [5210]
 */
#घोषणा AR5K_RETRY_CNT		0x8084			/* Register Address [5210] */
#घोषणा AR5K_RETRY_CNT_SSH	0x0000003f	/* Station लघु retry count (?) */
#घोषणा AR5K_RETRY_CNT_SLG	0x00000fc0	/* Station दीर्घ retry count (?) */

/*
 * Back-off status रेजिस्टर [5210]
 */
#घोषणा AR5K_BACKOFF		0x8088			/* Register Address [5210] */
#घोषणा AR5K_BACKOFF_CW		0x000003ff	/* Backoff Contention Winकरोw (?) */
#घोषणा AR5K_BACKOFF_CNT	0x03ff0000	/* Backoff count (?) */



/*
 * NAV रेजिस्टर (current)
 */
#घोषणा AR5K_NAV_5210		0x808c
#घोषणा AR5K_NAV_5211		0x8084
#घोषणा	AR5K_NAV		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_NAV_5210 : AR5K_NAV_5211)

/*
 * MIB counters:
 *
 * max value is 0xc000, अगर this is reached we get a MIB पूर्णांकerrupt.
 * they can be controlled via AR5K_MIBC and are cleared on पढ़ो.
 */

/*
 * RTS success (MIB counter)
 */
#घोषणा AR5K_RTS_OK_5210	0x8090
#घोषणा AR5K_RTS_OK_5211	0x8088
#घोषणा	AR5K_RTS_OK		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_RTS_OK_5210 : AR5K_RTS_OK_5211)

/*
 * RTS failure (MIB counter)
 */
#घोषणा AR5K_RTS_FAIL_5210	0x8094
#घोषणा AR5K_RTS_FAIL_5211	0x808c
#घोषणा	AR5K_RTS_FAIL		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_RTS_FAIL_5210 : AR5K_RTS_FAIL_5211)

/*
 * ACK failure (MIB counter)
 */
#घोषणा AR5K_ACK_FAIL_5210	0x8098
#घोषणा AR5K_ACK_FAIL_5211	0x8090
#घोषणा	AR5K_ACK_FAIL		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_ACK_FAIL_5210 : AR5K_ACK_FAIL_5211)

/*
 * FCS failure (MIB counter)
 */
#घोषणा AR5K_FCS_FAIL_5210	0x809c
#घोषणा AR5K_FCS_FAIL_5211	0x8094
#घोषणा	AR5K_FCS_FAIL		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_FCS_FAIL_5210 : AR5K_FCS_FAIL_5211)

/*
 * Beacon count रेजिस्टर
 */
#घोषणा AR5K_BEACON_CNT_5210	0x80a0
#घोषणा AR5K_BEACON_CNT_5211	0x8098
#घोषणा	AR5K_BEACON_CNT		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_BEACON_CNT_5210 : AR5K_BEACON_CNT_5211)


/*===5212 Specअगरic PCU रेजिस्टरs===*/

/*
 * Transmit घातer control रेजिस्टर
 */
#घोषणा AR5K_TPC			0x80e8
#घोषणा AR5K_TPC_ACK			0x0000003f	/* ack frames */
#घोषणा AR5K_TPC_ACK_S			0
#घोषणा AR5K_TPC_CTS			0x00003f00	/* cts frames */
#घोषणा AR5K_TPC_CTS_S			8
#घोषणा AR5K_TPC_CHIRP			0x003f0000	/* chirp frames */
#घोषणा AR5K_TPC_CHIRP_S		16
#घोषणा AR5K_TPC_DOPPLER		0x0f000000	/* करोppler chirp span */
#घोषणा AR5K_TPC_DOPPLER_S		24

/*
 * XR (eXtended Range) mode रेजिस्टर
 */
#घोषणा AR5K_XRMODE			0x80c0			/* Register Address */
#घोषणा	AR5K_XRMODE_POLL_TYPE_M		0x0000003f	/* Mask क्रम Poll type (?) */
#घोषणा	AR5K_XRMODE_POLL_TYPE_S		0
#घोषणा	AR5K_XRMODE_POLL_SUBTYPE_M	0x0000003c	/* Mask क्रम Poll subtype (?) */
#घोषणा	AR5K_XRMODE_POLL_SUBTYPE_S	2
#घोषणा	AR5K_XRMODE_POLL_WAIT_ALL	0x00000080	/* Wait क्रम poll */
#घोषणा	AR5K_XRMODE_SIFS_DELAY		0x000fff00	/* Mask क्रम SIFS delay */
#घोषणा	AR5K_XRMODE_FRAME_HOLD_M	0xfff00000	/* Mask क्रम frame hold (?) */
#घोषणा	AR5K_XRMODE_FRAME_HOLD_S	20

/*
 * XR delay रेजिस्टर
 */
#घोषणा AR5K_XRDELAY			0x80c4			/* Register Address */
#घोषणा AR5K_XRDELAY_SLOT_DELAY_M	0x0000ffff	/* Mask क्रम slot delay */
#घोषणा AR5K_XRDELAY_SLOT_DELAY_S	0
#घोषणा AR5K_XRDELAY_CHIRP_DELAY_M	0xffff0000	/* Mask क्रम CHIRP data delay */
#घोषणा AR5K_XRDELAY_CHIRP_DELAY_S	16

/*
 * XR समयout रेजिस्टर
 */
#घोषणा AR5K_XRTIMEOUT			0x80c8			/* Register Address */
#घोषणा AR5K_XRTIMEOUT_CHIRP_M		0x0000ffff	/* Mask क्रम CHIRP समयout */
#घोषणा AR5K_XRTIMEOUT_CHIRP_S		0
#घोषणा AR5K_XRTIMEOUT_POLL_M		0xffff0000	/* Mask क्रम Poll समयout */
#घोषणा AR5K_XRTIMEOUT_POLL_S		16

/*
 * XR chirp रेजिस्टर
 */
#घोषणा AR5K_XRCHIRP			0x80cc			/* Register Address */
#घोषणा AR5K_XRCHIRP_SEND		0x00000001	/* Send CHIRP */
#घोषणा AR5K_XRCHIRP_GAP		0xffff0000	/* Mask क्रम CHIRP gap (?) */

/*
 * XR stomp रेजिस्टर
 */
#घोषणा AR5K_XRSTOMP			0x80d0			/* Register Address */
#घोषणा AR5K_XRSTOMP_TX			0x00000001	/* Stomp Tx (?) */
#घोषणा AR5K_XRSTOMP_RX			0x00000002	/* Stomp Rx (?) */
#घोषणा AR5K_XRSTOMP_TX_RSSI		0x00000004	/* Stomp Tx RSSI (?) */
#घोषणा AR5K_XRSTOMP_TX_BSSID		0x00000008	/* Stomp Tx BSSID (?) */
#घोषणा AR5K_XRSTOMP_DATA		0x00000010	/* Stomp data (?)*/
#घोषणा AR5K_XRSTOMP_RSSI_THRES		0x0000ff00	/* Mask क्रम XR RSSI threshold */

/*
 * First enhanced sleep रेजिस्टर
 */
#घोषणा AR5K_SLEEP0			0x80d4			/* Register Address */
#घोषणा AR5K_SLEEP0_NEXT_DTIM		0x0007ffff	/* Mask क्रम next DTIM (?) */
#घोषणा AR5K_SLEEP0_NEXT_DTIM_S		0
#घोषणा AR5K_SLEEP0_ASSUME_DTIM		0x00080000	/* Assume DTIM */
#घोषणा AR5K_SLEEP0_ENH_SLEEP_EN	0x00100000	/* Enable enhanced sleep control */
#घोषणा AR5K_SLEEP0_CABTO		0xff000000	/* Mask क्रम CAB Time Out */
#घोषणा AR5K_SLEEP0_CABTO_S		24

/*
 * Second enhanced sleep रेजिस्टर
 */
#घोषणा AR5K_SLEEP1			0x80d8			/* Register Address */
#घोषणा AR5K_SLEEP1_NEXT_TIM		0x0007ffff	/* Mask क्रम next TIM (?) */
#घोषणा AR5K_SLEEP1_NEXT_TIM_S		0
#घोषणा AR5K_SLEEP1_BEACON_TO		0xff000000	/* Mask क्रम Beacon Time Out */
#घोषणा AR5K_SLEEP1_BEACON_TO_S		24

/*
 * Third enhanced sleep रेजिस्टर
 */
#घोषणा AR5K_SLEEP2			0x80dc			/* Register Address */
#घोषणा AR5K_SLEEP2_TIM_PER		0x0000ffff	/* Mask क्रम TIM period (?) */
#घोषणा AR5K_SLEEP2_TIM_PER_S		0
#घोषणा AR5K_SLEEP2_DTIM_PER		0xffff0000	/* Mask क्रम DTIM period (?) */
#घोषणा AR5K_SLEEP2_DTIM_PER_S		16

/*
 * TX घातer control (TPC) रेजिस्टर
 *
 * XXX: PCDAC steps (0.5dBm) or dBm ?
 *
 */
#घोषणा AR5K_TXPC			0x80e8			/* Register Address */
#घोषणा AR5K_TXPC_ACK_M			0x0000003f	/* ACK tx घातer */
#घोषणा AR5K_TXPC_ACK_S			0
#घोषणा AR5K_TXPC_CTS_M			0x00003f00	/* CTS tx घातer */
#घोषणा AR5K_TXPC_CTS_S			8
#घोषणा AR5K_TXPC_CHIRP_M		0x003f0000	/* CHIRP tx घातer */
#घोषणा AR5K_TXPC_CHIRP_S		16
#घोषणा AR5K_TXPC_DOPPLER		0x0f000000	/* Doppler chirp span (?) */
#घोषणा AR5K_TXPC_DOPPLER_S		24

/*
 * Profile count रेजिस्टरs
 *
 * These रेजिस्टरs can be cleared and frozen with ATH5K_MIBC, but they करो not
 * generate a MIB पूर्णांकerrupt.
 * Instead of overflowing, they shअगरt by one bit to the right. All रेजिस्टरs
 * shअगरt together, i.e. when one reaches the max, all shअगरt at the same समय by
 * one bit to the right. This way we should always get consistent values.
 */
#घोषणा AR5K_PROFCNT_TX			0x80ec	/* Tx count */
#घोषणा AR5K_PROFCNT_RX			0x80f0	/* Rx count */
#घोषणा AR5K_PROFCNT_RXCLR		0x80f4	/* Busy count */
#घोषणा AR5K_PROFCNT_CYCLE		0x80f8	/* Cycle counter */

/*
 * Quiet period control रेजिस्टरs
 */
#घोषणा AR5K_QUIET_CTL1			0x80fc			/* Register Address */
#घोषणा AR5K_QUIET_CTL1_NEXT_QT_TSF	0x0000ffff	/* Next quiet period TSF (TU) */
#घोषणा AR5K_QUIET_CTL1_NEXT_QT_TSF_S	0
#घोषणा AR5K_QUIET_CTL1_QT_EN		0x00010000	/* Enable quiet period */
#घोषणा AR5K_QUIET_CTL1_ACK_CTS_EN	0x00020000	/* Send ACK/CTS during quiet period */

#घोषणा AR5K_QUIET_CTL2			0x8100			/* Register Address */
#घोषणा AR5K_QUIET_CTL2_QT_PER		0x0000ffff	/* Mask क्रम quiet period periodicity */
#घोषणा AR5K_QUIET_CTL2_QT_PER_S	0
#घोषणा AR5K_QUIET_CTL2_QT_DUR		0xffff0000	/* Mask क्रम quiet period duration */
#घोषणा AR5K_QUIET_CTL2_QT_DUR_S	16

/*
 * TSF parameter रेजिस्टर
 */
#घोषणा AR5K_TSF_PARM			0x8104			/* Register Address */
#घोषणा AR5K_TSF_PARM_INC		0x000000ff	/* Mask क्रम TSF increment */
#घोषणा AR5K_TSF_PARM_INC_S		0

/*
 * QoS NOACK policy
 */
#घोषणा AR5K_QOS_NOACK			0x8108			/* Register Address */
#घोषणा AR5K_QOS_NOACK_2BIT_VALUES	0x0000000f	/* ??? */
#घोषणा AR5K_QOS_NOACK_2BIT_VALUES_S	0
#घोषणा AR5K_QOS_NOACK_BIT_OFFSET	0x00000070	/* ??? */
#घोषणा AR5K_QOS_NOACK_BIT_OFFSET_S	4
#घोषणा AR5K_QOS_NOACK_BYTE_OFFSET	0x00000180	/* ??? */
#घोषणा AR5K_QOS_NOACK_BYTE_OFFSET_S	7

/*
 * PHY error filter रेजिस्टर
 */
#घोषणा AR5K_PHY_ERR_FIL		0x810c
#घोषणा AR5K_PHY_ERR_FIL_RADAR		0x00000020	/* Radar संकेत */
#घोषणा AR5K_PHY_ERR_FIL_OFDM		0x00020000	/* OFDM false detect (ANI) */
#घोषणा AR5K_PHY_ERR_FIL_CCK		0x02000000	/* CCK false detect (ANI) */

/*
 * XR latency रेजिस्टर
 */
#घोषणा AR5K_XRLAT_TX		0x8110

/*
 * ACK SIFS रेजिस्टर
 */
#घोषणा AR5K_ACKSIFS		0x8114			/* Register Address */
#घोषणा AR5K_ACKSIFS_INC	0x00000000	/* ACK SIFS Increment (field) */

/*
 * MIC QoS control रेजिस्टर (?)
 */
#घोषणा	AR5K_MIC_QOS_CTL		0x8118			/* Register Address */
#घोषणा	AR5K_MIC_QOS_CTL_OFF(_n)	(1 << (_n * 2))
#घोषणा	AR5K_MIC_QOS_CTL_MQ_EN		0x00010000	/* Enable MIC QoS */

/*
 * MIC QoS select रेजिस्टर (?)
 */
#घोषणा	AR5K_MIC_QOS_SEL		0x811c
#घोषणा	AR5K_MIC_QOS_SEL_OFF(_n)	(1 << (_n * 4))

/*
 * Misc mode control रेजिस्टर (?)
 */
#घोषणा	AR5K_MISC_MODE			0x8120			/* Register Address */
#घोषणा	AR5K_MISC_MODE_FBSSID_MATCH	0x00000001	/* Force BSSID match */
#घोषणा	AR5K_MISC_MODE_ACKSIFS_MEM	0x00000002	/* ACK SIFS memory (?) */
#घोषणा	AR5K_MISC_MODE_COMBINED_MIC	0x00000004	/* use rx/tx MIC key */
/* more bits */

/*
 * OFDM Filter counter
 */
#घोषणा	AR5K_OFDM_FIL_CNT		0x8124

/*
 * CCK Filter counter
 */
#घोषणा	AR5K_CCK_FIL_CNT		0x8128

/*
 * PHY Error Counters (same masks as AR5K_PHY_ERR_FIL)
 */
#घोषणा	AR5K_PHYERR_CNT1		0x812c
#घोषणा	AR5K_PHYERR_CNT1_MASK		0x8130

#घोषणा	AR5K_PHYERR_CNT2		0x8134
#घोषणा	AR5K_PHYERR_CNT2_MASK		0x8138

/* अगर the PHY Error Counters reach this maximum, we get MIB पूर्णांकerrupts */
#घोषणा ATH5K_PHYERR_CNT_MAX		0x00c00000

/*
 * TSF Threshold रेजिस्टर (?)
 */
#घोषणा	AR5K_TSF_THRES			0x813c

/*
 * TODO: Wake On Wireless रेजिस्टरs
 * Range: 0x8147 - 0x818c
 */

/*
 * Rate -> ACK SIFS mapping table (32 entries)
 */
#घोषणा	AR5K_RATE_ACKSIFS_BASE		0x8680			/* Register Address */
#घोषणा	AR5K_RATE_ACKSIFS(_n)		(AR5K_RATE_ACKSIFS_BSE + ((_n) << 2))
#घोषणा	AR5K_RATE_ACKSIFS_NORMAL	0x00000001	/* Normal SIFS (field) */
#घोषणा	AR5K_RATE_ACKSIFS_TURBO		0x00000400	/* Turbo SIFS (field) */

/*
 * Rate -> duration mapping table (32 entries)
 */
#घोषणा AR5K_RATE_DUR_BASE		0x8700
#घोषणा AR5K_RATE_DUR(_n)		(AR5K_RATE_DUR_BASE + ((_n) << 2))

/*
 * Rate -> db mapping table
 * (8 entries, each one has 4 8bit fields)
 */
#घोषणा AR5K_RATE2DB_BASE		0x87c0
#घोषणा AR5K_RATE2DB(_n)		(AR5K_RATE2DB_BASE + ((_n) << 2))

/*
 * db -> Rate mapping table
 * (8 entries, each one has 4 8bit fields)
 */
#घोषणा AR5K_DB2RATE_BASE		0x87e0
#घोषणा AR5K_DB2RATE(_n)		(AR5K_DB2RATE_BASE + ((_n) << 2))

/*===5212 end===*/

#घोषणा AR5K_KEYTABLE_SIZE_5210		64
#घोषणा AR5K_KEYTABLE_SIZE_5211		128

/*===PHY REGISTERS===*/

/*
 * PHY रेजिस्टरs start
 */
#घोषणा	AR5K_PHY_BASE			0x9800
#घोषणा	AR5K_PHY(_n)			(AR5K_PHY_BASE + ((_n) << 2))

/*
 * TST_2 (Misc config parameters)
 */
#घोषणा	AR5K_PHY_TST2			0x9800			/* Register Address */
#घोषणा AR5K_PHY_TST2_TRIG_SEL		0x00000007	/* Trigger select (?)*/
#घोषणा AR5K_PHY_TST2_TRIG		0x00000010	/* Trigger (?) */
#घोषणा AR5K_PHY_TST2_CBUS_MODE		0x00000060	/* Cardbus mode (?) */
#घोषणा AR5K_PHY_TST2_CLK32		0x00000400	/* CLK_OUT is CLK32 (32kHz बाह्यal) */
#घोषणा AR5K_PHY_TST2_CHANCOR_DUMP_EN	0x00000800	/* Enable Chancor dump (?) */
#घोषणा AR5K_PHY_TST2_EVEN_CHANCOR_DUMP	0x00001000	/* Even Chancor dump (?) */
#घोषणा AR5K_PHY_TST2_RFSILENT_EN	0x00002000	/* Enable RFSILENT */
#घोषणा AR5K_PHY_TST2_ALT_RFDATA	0x00004000	/* Alternate RFDATA (5-2GHz चयन ?) */
#घोषणा AR5K_PHY_TST2_MINI_OBS_EN	0x00008000	/* Enable mini OBS (?) */
#घोषणा AR5K_PHY_TST2_RX2_IS_RX5_INV	0x00010000	/* 2GHz rx path is the 5GHz path inverted (?) */
#घोषणा AR5K_PHY_TST2_SLOW_CLK160	0x00020000	/* Slow CLK160 (?) */
#घोषणा AR5K_PHY_TST2_AGC_OBS_SEL_3	0x00040000	/* AGC OBS Select 3 (?) */
#घोषणा AR5K_PHY_TST2_BBB_OBS_SEL	0x00080000	/* BB OBS Select (field ?) */
#घोषणा AR5K_PHY_TST2_ADC_OBS_SEL	0x00800000	/* ADC OBS Select (field ?) */
#घोषणा AR5K_PHY_TST2_RX_CLR_SEL	0x08000000	/* RX Clear Select (?) */
#घोषणा AR5K_PHY_TST2_FORCE_AGC_CLR	0x10000000	/* Force AGC clear (?) */
#घोषणा AR5K_PHY_SHIFT_2GHZ		0x00004007	/* Used to access 2GHz radios */
#घोषणा AR5K_PHY_SHIFT_5GHZ		0x00000007	/* Used to access 5GHz radios (शेष) */

/*
 * PHY frame control रेजिस्टर [5110] /turbo mode रेजिस्टर [5111+]
 *
 * There is another frame control रेजिस्टर क्रम [5111+]
 * at address 0x9944 (see below) but the 2 first flags
 * are common here between 5110 frame control रेजिस्टर
 * and [5111+] turbo mode रेजिस्टर, so this also works as
 * a "turbo mode register" क्रम 5110. We treat this one as
 * a frame control रेजिस्टर क्रम 5110 below.
 */
#घोषणा	AR5K_PHY_TURBO			0x9804			/* Register Address */
#घोषणा	AR5K_PHY_TURBO_MODE		0x00000001	/* Enable turbo mode */
#घोषणा	AR5K_PHY_TURBO_SHORT		0x00000002	/* Set लघु symbols to turbo mode */
#घोषणा	AR5K_PHY_TURBO_MIMO		0x00000004	/* Set turbo क्रम mimo */

/*
 * PHY agility command रेजिस्टर
 * (aka TST_1)
 */
#घोषणा	AR5K_PHY_AGC			0x9808			/* Register Address */
#घोषणा	AR5K_PHY_TST1			0x9808
#घोषणा	AR5K_PHY_AGC_DISABLE		0x08000000	/* Disable AGC to A2 (?)*/
#घोषणा	AR5K_PHY_TST1_TXHOLD		0x00003800	/* Set tx hold (?) */
#घोषणा	AR5K_PHY_TST1_TXSRC_SRC		0x00000002	/* Used with bit 7 (?) */
#घोषणा	AR5K_PHY_TST1_TXSRC_SRC_S	1
#घोषणा	AR5K_PHY_TST1_TXSRC_ALT		0x00000080	/* Set input to tsdac (?) */
#घोषणा	AR5K_PHY_TST1_TXSRC_ALT_S	7


/*
 * PHY timing रेजिस्टर 3 [5112+]
 */
#घोषणा	AR5K_PHY_TIMING_3		0x9814
#घोषणा	AR5K_PHY_TIMING_3_DSC_MAN	0xfffe0000
#घोषणा	AR5K_PHY_TIMING_3_DSC_MAN_S	17
#घोषणा	AR5K_PHY_TIMING_3_DSC_EXP	0x0001e000
#घोषणा	AR5K_PHY_TIMING_3_DSC_EXP_S	13

/*
 * PHY chip revision रेजिस्टर
 */
#घोषणा	AR5K_PHY_CHIP_ID		0x9818

/*
 * PHY activation रेजिस्टर
 */
#घोषणा	AR5K_PHY_ACT			0x981c			/* Register Address */
#घोषणा	AR5K_PHY_ACT_ENABLE		0x00000001	/* Activate PHY */
#घोषणा	AR5K_PHY_ACT_DISABLE		0x00000002	/* Deactivate PHY */

/*
 * PHY RF control रेजिस्टरs
 */
#घोषणा AR5K_PHY_RF_CTL2		0x9824			/* Register Address */
#घोषणा	AR5K_PHY_RF_CTL2_TXF2TXD_START	0x0000000f	/* TX frame to TX data start */
#घोषणा	AR5K_PHY_RF_CTL2_TXF2TXD_START_S	0

#घोषणा AR5K_PHY_RF_CTL3		0x9828			/* Register Address */
#घोषणा AR5K_PHY_RF_CTL3_TXE2XLNA_ON	0x0000ff00	/* TX end to XLNA on */
#घोषणा	AR5K_PHY_RF_CTL3_TXE2XLNA_ON_S	8

#घोषणा	AR5K_PHY_ADC_CTL			0x982c
#घोषणा	AR5K_PHY_ADC_CTL_INBUFGAIN_OFF		0x00000003
#घोषणा	AR5K_PHY_ADC_CTL_INBUFGAIN_OFF_S	0
#घोषणा	AR5K_PHY_ADC_CTL_PWD_DAC_OFF		0x00002000
#घोषणा	AR5K_PHY_ADC_CTL_PWD_BAND_GAP_OFF	0x00004000
#घोषणा	AR5K_PHY_ADC_CTL_PWD_ADC_OFF		0x00008000
#घोषणा	AR5K_PHY_ADC_CTL_INBUFGAIN_ON		0x00030000
#घोषणा	AR5K_PHY_ADC_CTL_INBUFGAIN_ON_S		16

#घोषणा AR5K_PHY_RF_CTL4		0x9834			/* Register Address */
#घोषणा AR5K_PHY_RF_CTL4_TXF2XPA_A_ON	0x00000001	/* TX frame to XPA A on (field) */
#घोषणा AR5K_PHY_RF_CTL4_TXF2XPA_B_ON	0x00000100	/* TX frame to XPA B on (field) */
#घोषणा	AR5K_PHY_RF_CTL4_TXE2XPA_A_OFF	0x00010000	/* TX end to XPA A off (field) */
#घोषणा AR5K_PHY_RF_CTL4_TXE2XPA_B_OFF	0x01000000	/* TX end to XPA B off (field) */

/*
 * Pre-Amplअगरier control रेजिस्टर
 * (XPA -> बाह्यal pre-amplअगरier)
 */
#घोषणा	AR5K_PHY_PA_CTL			0x9838			/* Register Address */
#घोषणा	AR5K_PHY_PA_CTL_XPA_A_HI	0x00000001	/* XPA A high (?) */
#घोषणा	AR5K_PHY_PA_CTL_XPA_B_HI	0x00000002	/* XPA B high (?) */
#घोषणा	AR5K_PHY_PA_CTL_XPA_A_EN	0x00000004	/* Enable XPA A */
#घोषणा	AR5K_PHY_PA_CTL_XPA_B_EN	0x00000008	/* Enable XPA B */

/*
 * PHY settling रेजिस्टर
 */
#घोषणा AR5K_PHY_SETTLING		0x9844			/* Register Address */
#घोषणा	AR5K_PHY_SETTLING_AGC		0x0000007f	/* AGC settling समय */
#घोषणा	AR5K_PHY_SETTLING_AGC_S		0
#घोषणा	AR5K_PHY_SETTLING_SWITCH	0x00003f80	/* Switch settling समय */
#घोषणा	AR5K_PHY_SETTLING_SWITCH_S	7

/*
 * PHY Gain रेजिस्टरs
 */
#घोषणा AR5K_PHY_GAIN			0x9848			/* Register Address */
#घोषणा	AR5K_PHY_GAIN_TXRX_ATTEN	0x0003f000	/* TX-RX Attenuation */
#घोषणा	AR5K_PHY_GAIN_TXRX_ATTEN_S	12
#घोषणा	AR5K_PHY_GAIN_TXRX_RF_MAX	0x007c0000
#घोषणा	AR5K_PHY_GAIN_TXRX_RF_MAX_S	18

#घोषणा	AR5K_PHY_GAIN_OFFSET		0x984c			/* Register Address */
#घोषणा	AR5K_PHY_GAIN_OFFSET_RXTX_FLAG	0x00020000	/* RX-TX flag (?) */

/*
 * Desired ADC/PGA size रेजिस्टर
 * (क्रम more infos पढ़ो ANI patent)
 */
#घोषणा AR5K_PHY_DESIRED_SIZE		0x9850			/* Register Address */
#घोषणा	AR5K_PHY_DESIRED_SIZE_ADC	0x000000ff	/* ADC desired size */
#घोषणा	AR5K_PHY_DESIRED_SIZE_ADC_S	0
#घोषणा	AR5K_PHY_DESIRED_SIZE_PGA	0x0000ff00	/* PGA desired size */
#घोषणा	AR5K_PHY_DESIRED_SIZE_PGA_S	8
#घोषणा	AR5K_PHY_DESIRED_SIZE_TOT	0x0ff00000	/* Total desired size */
#घोषणा	AR5K_PHY_DESIRED_SIZE_TOT_S	20

/*
 * PHY संकेत रेजिस्टर
 * (क्रम more infos पढ़ो ANI patent)
 */
#घोषणा	AR5K_PHY_SIG			0x9858			/* Register Address */
#घोषणा	AR5K_PHY_SIG_FIRSTEP		0x0003f000	/* FIRSTEP */
#घोषणा	AR5K_PHY_SIG_FIRSTEP_S		12
#घोषणा	AR5K_PHY_SIG_FIRPWR		0x03fc0000	/* FIPWR */
#घोषणा	AR5K_PHY_SIG_FIRPWR_S		18

/*
 * PHY coarse agility control रेजिस्टर
 * (क्रम more infos पढ़ो ANI patent)
 */
#घोषणा	AR5K_PHY_AGCCOARSE		0x985c			/* Register Address */
#घोषणा	AR5K_PHY_AGCCOARSE_LO		0x00007f80	/* AGC Coarse low */
#घोषणा	AR5K_PHY_AGCCOARSE_LO_S		7
#घोषणा	AR5K_PHY_AGCCOARSE_HI		0x003f8000	/* AGC Coarse high */
#घोषणा	AR5K_PHY_AGCCOARSE_HI_S		15

/*
 * PHY agility control रेजिस्टर
 */
#घोषणा	AR5K_PHY_AGCCTL			0x9860			/* Register address */
#घोषणा	AR5K_PHY_AGCCTL_CAL		0x00000001	/* Enable PHY calibration */
#घोषणा	AR5K_PHY_AGCCTL_NF		0x00000002	/* Enable Noise Floor calibration */
#घोषणा	AR5K_PHY_AGCCTL_OFDM_DIV_DIS	0x00000008	/* Disable antenna भागersity on OFDM modes */
#घोषणा	AR5K_PHY_AGCCTL_NF_EN		0x00008000	/* Enable nf calibration to happen (?) */
#घोषणा	AR5K_PHY_AGCTL_FLTR_CAL		0x00010000	/* Allow filter calibration (?) */
#घोषणा	AR5K_PHY_AGCCTL_NF_NOUPDATE	0x00020000	/* Don't update nf स्वतःmatically */

/*
 * PHY noise न्यूनमान status रेजिस्टर (CCA = Clear Channel Assessment)
 */
#घोषणा AR5K_PHY_NF			0x9864			/* Register address */
#घोषणा AR5K_PHY_NF_M			0x000001ff	/* Noise न्यूनमान, written to hardware in 1/2 dBm units */
#घोषणा AR5K_PHY_NF_SVAL(_n)           (((_n) & AR5K_PHY_NF_M) | (1 << 9))
#घोषणा	AR5K_PHY_NF_THRESH62		0x0007f000	/* Thresh62 -check ANI patent- (field) */
#घोषणा	AR5K_PHY_NF_THRESH62_S		12
#घोषणा	AR5K_PHY_NF_MINCCA_PWR		0x0ff80000	/* Minimum measured noise level, पढ़ो from hardware in 1 dBm units */
#घोषणा	AR5K_PHY_NF_MINCCA_PWR_S	19

/*
 * PHY ADC saturation रेजिस्टर [5110]
 */
#घोषणा	AR5K_PHY_ADCSAT			0x9868
#घोषणा	AR5K_PHY_ADCSAT_ICNT		0x0001f800
#घोषणा	AR5K_PHY_ADCSAT_ICNT_S		11
#घोषणा	AR5K_PHY_ADCSAT_THR		0x000007e0
#घोषणा	AR5K_PHY_ADCSAT_THR_S		5

/*
 * PHY Weak ofdm संकेत detection threshold रेजिस्टरs (ANI) [5212+]
 */

/* High thresholds */
#घोषणा AR5K_PHY_WEAK_OFDM_HIGH_THR		0x9868
#घोषणा AR5K_PHY_WEAK_OFDM_HIGH_THR_M2_COUNT	0x0000001f
#घोषणा AR5K_PHY_WEAK_OFDM_HIGH_THR_M2_COUNT_S	0
#घोषणा AR5K_PHY_WEAK_OFDM_HIGH_THR_M1		0x00fe0000
#घोषणा AR5K_PHY_WEAK_OFDM_HIGH_THR_M1_S	17
#घोषणा AR5K_PHY_WEAK_OFDM_HIGH_THR_M2		0x7f000000
#घोषणा AR5K_PHY_WEAK_OFDM_HIGH_THR_M2_S	24

/* Low thresholds */
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR		0x986c
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR_SELFCOR_EN	0x00000001
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR_M2_COUNT	0x00003f00
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR_M2_COUNT_S	8
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR_M1		0x001fc000
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR_M1_S		14
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR_M2		0x0fe00000
#घोषणा AR5K_PHY_WEAK_OFDM_LOW_THR_M2_S		21


/*
 * PHY sleep रेजिस्टरs [5112+]
 */
#घोषणा AR5K_PHY_SCR			0x9870

#घोषणा AR5K_PHY_SLMT			0x9874
#घोषणा AR5K_PHY_SLMT_32MHZ		0x0000007f

#घोषणा AR5K_PHY_SCAL			0x9878
#घोषणा AR5K_PHY_SCAL_32MHZ		0x0000000e
#घोषणा	AR5K_PHY_SCAL_32MHZ_5311	0x00000008
#घोषणा	AR5K_PHY_SCAL_32MHZ_2417	0x0000000a
#घोषणा	AR5K_PHY_SCAL_32MHZ_HB63	0x00000032

/*
 * PHY PLL (Phase Locked Loop) control रेजिस्टर
 */
#घोषणा	AR5K_PHY_PLL			0x987c
#घोषणा	AR5K_PHY_PLL_20MHZ		0x00000013	/* For half rate (?) */
/* 40MHz -> 5GHz band */
#घोषणा	AR5K_PHY_PLL_40MHZ_5211		0x00000018
#घोषणा	AR5K_PHY_PLL_40MHZ_5212		0x000000aa
#घोषणा	AR5K_PHY_PLL_40MHZ_5413		0x00000004
#घोषणा	AR5K_PHY_PLL_40MHZ		(ah->ah_version == AR5K_AR5211 ? \
					AR5K_PHY_PLL_40MHZ_5211 : AR5K_PHY_PLL_40MHZ_5212)
/* 44MHz -> 2.4GHz band */
#घोषणा	AR5K_PHY_PLL_44MHZ_5211		0x00000019
#घोषणा	AR5K_PHY_PLL_44MHZ_5212		0x000000ab
#घोषणा	AR5K_PHY_PLL_44MHZ		(ah->ah_version == AR5K_AR5211 ? \
					AR5K_PHY_PLL_44MHZ_5211 : AR5K_PHY_PLL_44MHZ_5212)

#घोषणा AR5K_PHY_PLL_RF5111		0x00000000
#घोषणा AR5K_PHY_PLL_RF5112		0x00000040
#घोषणा	AR5K_PHY_PLL_HALF_RATE		0x00000100
#घोषणा	AR5K_PHY_PLL_QUARTER_RATE	0x00000200

/*
 * RF Buffer रेजिस्टर
 *
 * It's obvious from the code that 0x989c is the buffer रेजिस्टर but
 * क्रम the other special रेजिस्टरs that we ग_लिखो to after sending each
 * packet, i have no idea. So I'll name them BUFFER_CONTROL_X रेजिस्टरs
 * क्रम now. It's पूर्णांकeresting that they are also used क्रम some other operations.
 */

#घोषणा AR5K_RF_BUFFER			0x989c
#घोषणा AR5K_RF_BUFFER_CONTROL_0	0x98c0	/* Channel on 5110 */
#घोषणा AR5K_RF_BUFFER_CONTROL_1	0x98c4	/* Bank 7 on 5112 */
#घोषणा AR5K_RF_BUFFER_CONTROL_2	0x98cc	/* Bank 7 on 5111 */

#घोषणा AR5K_RF_BUFFER_CONTROL_3	0x98d0	/* Bank 2 on 5112 */
						/* Channel set on 5111 */
						/* Used to पढ़ो radio revision*/

#घोषणा AR5K_RF_BUFFER_CONTROL_4	0x98d4  /* RF Stage रेजिस्टर on 5110 */
						/* Bank 0,1,2,6 on 5111 */
						/* Bank 1 on 5112 */
						/* Used during activation on 5111 */

#घोषणा AR5K_RF_BUFFER_CONTROL_5	0x98d8	/* Bank 3 on 5111 */
						/* Used during activation on 5111 */
						/* Channel on 5112 */
						/* Bank 6 on 5112 */

#घोषणा AR5K_RF_BUFFER_CONTROL_6	0x98dc	/* Bank 3 on 5112 */

/*
 * PHY RF stage रेजिस्टर [5210]
 */
#घोषणा AR5K_PHY_RFSTG			0x98d4
#घोषणा AR5K_PHY_RFSTG_DISABLE		0x00000021

/*
 * BIN masks (?)
 */
#घोषणा	AR5K_PHY_BIN_MASK_1	0x9900
#घोषणा	AR5K_PHY_BIN_MASK_2	0x9904
#घोषणा	AR5K_PHY_BIN_MASK_3	0x9908

#घोषणा	AR5K_PHY_BIN_MASK_CTL		0x990c
#घोषणा	AR5K_PHY_BIN_MASK_CTL_MASK_4	0x00003fff
#घोषणा	AR5K_PHY_BIN_MASK_CTL_MASK_4_S	0
#घोषणा	AR5K_PHY_BIN_MASK_CTL_RATE	0xff000000
#घोषणा	AR5K_PHY_BIN_MASK_CTL_RATE_S	24

/*
 * PHY Antenna control रेजिस्टर
 */
#घोषणा AR5K_PHY_ANT_CTL		0x9910			/* Register Address */
#घोषणा	AR5K_PHY_ANT_CTL_TXRX_EN	0x00000001	/* Enable TX/RX (?) */
#घोषणा	AR5K_PHY_ANT_CTL_SECTORED_ANT	0x00000004	/* Sectored Antenna */
#घोषणा	AR5K_PHY_ANT_CTL_HITUNE5	0x00000008	/* Hitune5 (?) */
#घोषणा	AR5K_PHY_ANT_CTL_SWTABLE_IDLE	0x000003f0	/* Switch table idle (?) */
#घोषणा	AR5K_PHY_ANT_CTL_SWTABLE_IDLE_S	4

/*
 * PHY receiver delay रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_RX_DELAY		0x9914			/* Register Address */
#घोषणा	AR5K_PHY_RX_DELAY_M		0x00003fff	/* Mask क्रम RX activate to receive delay (/100ns) */

/*
 * PHY max rx length रेजिस्टर (?) [5111]
 */
#घोषणा	AR5K_PHY_MAX_RX_LEN		0x991c

/*
 * PHY timing रेजिस्टर 4
 * I(nphase)/Q(adrature) calibration रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_IQ			0x9920			/* Register Address */
#घोषणा	AR5K_PHY_IQ_CORR_Q_Q_COFF	0x0000001f	/* Mask क्रम q correction info */
#घोषणा	AR5K_PHY_IQ_CORR_Q_Q_COFF_S	0
#घोषणा	AR5K_PHY_IQ_CORR_Q_I_COFF	0x000007e0	/* Mask क्रम i correction info */
#घोषणा	AR5K_PHY_IQ_CORR_Q_I_COFF_S	5
#घोषणा	AR5K_PHY_IQ_CORR_ENABLE		0x00000800	/* Enable i/q correction */
#घोषणा	AR5K_PHY_IQ_CAL_NUM_LOG_MAX	0x0000f000	/* Mask क्रम max number of samples in log scale */
#घोषणा	AR5K_PHY_IQ_CAL_NUM_LOG_MAX_S	12
#घोषणा	AR5K_PHY_IQ_RUN			0x00010000	/* Run i/q calibration */
#घोषणा	AR5K_PHY_IQ_USE_PT_DF		0x00020000	/* Use pilot track df (?) */
#घोषणा	AR5K_PHY_IQ_EARLY_TRIG_THR	0x00200000	/* Early trigger threshold (?) (field) */
#घोषणा	AR5K_PHY_IQ_PILOT_MASK_EN	0x10000000	/* Enable pilot mask (?) */
#घोषणा	AR5K_PHY_IQ_CHAN_MASK_EN	0x20000000	/* Enable channel mask (?) */
#घोषणा	AR5K_PHY_IQ_SPUR_FILT_EN	0x40000000	/* Enable spur filter */
#घोषणा	AR5K_PHY_IQ_SPUR_RSSI_EN	0x80000000	/* Enable spur rssi */

/*
 * PHY timing रेजिस्टर 5
 * OFDM Self-correlator Cyclic RSSI threshold params
 * (Check out bb_cycpwr_thr1 on ANI patent)
 */
#घोषणा	AR5K_PHY_OFDM_SELFCORR			0x9924			/* Register Address */
#घोषणा	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1_EN	0x00000001	/* Enable cyclic RSSI thr 1 */
#घोषणा	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1	0x000000fe	/* Mask क्रम Cyclic RSSI threshold 1 */
#घोषणा	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1_S	1
#घोषणा	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR3	0x00000100	/* Cyclic RSSI threshold 3 (field) (?) */
#घोषणा	AR5K_PHY_OFDM_SELFCORR_RSSI_1ATHR_EN	0x00008000	/* Enable 1A RSSI threshold (?) */
#घोषणा	AR5K_PHY_OFDM_SELFCORR_RSSI_1ATHR	0x00010000	/* 1A RSSI threshold (field) (?) */
#घोषणा	AR5K_PHY_OFDM_SELFCORR_LSCTHR_HIRSSI	0x00800000	/* Long sc threshold hi rssi (?) */

/*
 * PHY-only warm reset रेजिस्टर
 */
#घोषणा	AR5K_PHY_WARM_RESET		0x9928

/*
 * PHY-only control रेजिस्टर
 */
#घोषणा AR5K_PHY_CTL			0x992c			/* Register Address */
#घोषणा	AR5K_PHY_CTL_RX_DRAIN_RATE	0x00000001	/* RX drain rate (?) */
#घोषणा	AR5K_PHY_CTL_LATE_TX_SIG_SYM	0x00000002	/* Late tx संकेत symbol (?) */
#घोषणा	AR5K_PHY_CTL_GEN_SCRAMBLER	0x00000004	/* Generate scrambler */
#घोषणा	AR5K_PHY_CTL_TX_ANT_SEL		0x00000008	/* TX antenna select */
#घोषणा	AR5K_PHY_CTL_TX_ANT_STATIC	0x00000010	/* Static TX antenna */
#घोषणा	AR5K_PHY_CTL_RX_ANT_SEL		0x00000020	/* RX antenna select */
#घोषणा	AR5K_PHY_CTL_RX_ANT_STATIC	0x00000040	/* Static RX antenna */
#घोषणा	AR5K_PHY_CTL_LOW_FREQ_SLE_EN	0x00000080	/* Enable low freq sleep */

/*
 * PHY PAPD probe रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_PAPD_PROBE		0x9930
#घोषणा	AR5K_PHY_PAPD_PROBE_SH_HI_PAR	0x00000001
#घोषणा	AR5K_PHY_PAPD_PROBE_PCDAC_BIAS	0x00000002
#घोषणा	AR5K_PHY_PAPD_PROBE_COMP_GAIN	0x00000040
#घोषणा	AR5K_PHY_PAPD_PROBE_TXPOWER	0x00007e00
#घोषणा	AR5K_PHY_PAPD_PROBE_TXPOWER_S	9
#घोषणा	AR5K_PHY_PAPD_PROBE_TX_NEXT	0x00008000
#घोषणा	AR5K_PHY_PAPD_PROBE_PREDIST_EN	0x00010000
#घोषणा	AR5K_PHY_PAPD_PROBE_TYPE	0x01800000	/* [5112+] */
#घोषणा	AR5K_PHY_PAPD_PROBE_TYPE_S	23
#घोषणा	AR5K_PHY_PAPD_PROBE_TYPE_OFDM	0
#घोषणा	AR5K_PHY_PAPD_PROBE_TYPE_XR	1
#घोषणा	AR5K_PHY_PAPD_PROBE_TYPE_CCK	2
#घोषणा	AR5K_PHY_PAPD_PROBE_GAINF	0xfe000000
#घोषणा	AR5K_PHY_PAPD_PROBE_GAINF_S	25
#घोषणा	AR5K_PHY_PAPD_PROBE_INI_5111	0x00004883	/* [5212+] */
#घोषणा	AR5K_PHY_PAPD_PROBE_INI_5112	0x00004882	/* [5212+] */

/*
 * PHY TX rate घातer रेजिस्टरs [5112+]
 */
#घोषणा	AR5K_PHY_TXPOWER_RATE1			0x9934
#घोषणा	AR5K_PHY_TXPOWER_RATE2			0x9938
#घोषणा	AR5K_PHY_TXPOWER_RATE_MAX		0x993c
#घोषणा	AR5K_PHY_TXPOWER_RATE_MAX_TPC_ENABLE	0x00000040
#घोषणा	AR5K_PHY_TXPOWER_RATE3			0xa234
#घोषणा	AR5K_PHY_TXPOWER_RATE4			0xa238

/*
 * PHY frame control रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_FRAME_CTL_5210		0x9804
#घोषणा	AR5K_PHY_FRAME_CTL_5211		0x9944
#घोषणा	AR5K_PHY_FRAME_CTL		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_PHY_FRAME_CTL_5210 : AR5K_PHY_FRAME_CTL_5211)
/*---[5111+]---*/
#घोषणा	AR5K_PHY_FRAME_CTL_WIN_LEN	0x00000003	/* Force winकरोw length (?) */
#घोषणा	AR5K_PHY_FRAME_CTL_WIN_LEN_S	0
#घोषणा	AR5K_PHY_FRAME_CTL_TX_CLIP	0x00000038	/* Mask क्रम tx clip (?) */
#घोषणा	AR5K_PHY_FRAME_CTL_TX_CLIP_S	3
#घोषणा	AR5K_PHY_FRAME_CTL_PREP_CHINFO	0x00010000	/* Prepend chan info */
#घोषणा	AR5K_PHY_FRAME_CTL_EMU		0x80000000
#घोषणा	AR5K_PHY_FRAME_CTL_EMU_S	31
/*---[5110/5111]---*/
#घोषणा	AR5K_PHY_FRAME_CTL_TIMING_ERR	0x01000000	/* PHY timing error */
#घोषणा	AR5K_PHY_FRAME_CTL_PARITY_ERR	0x02000000	/* Parity error */
#घोषणा	AR5K_PHY_FRAME_CTL_ILLRATE_ERR	0x04000000	/* Illegal rate */
#घोषणा	AR5K_PHY_FRAME_CTL_ILLLEN_ERR	0x08000000	/* Illegal length */
#घोषणा	AR5K_PHY_FRAME_CTL_SERVICE_ERR	0x20000000
#घोषणा	AR5K_PHY_FRAME_CTL_TXURN_ERR	0x40000000	/* TX underrun */
#घोषणा AR5K_PHY_FRAME_CTL_INI	\
			(AR5K_PHY_FRAME_CTL_SERVICE_ERR | \
			 AR5K_PHY_FRAME_CTL_TXURN_ERR | \
			 AR5K_PHY_FRAME_CTL_ILLLEN_ERR | \
			 AR5K_PHY_FRAME_CTL_ILLRATE_ERR | \
			 AR5K_PHY_FRAME_CTL_PARITY_ERR | \
			 AR5K_PHY_FRAME_CTL_TIMING_ERR)

/*
 * PHY Tx Power adjusपंचांगent रेजिस्टर [5212A+]
 */
#घोषणा	AR5K_PHY_TX_PWR_ADJ			0x994c
#घोषणा	AR5K_PHY_TX_PWR_ADJ_CCK_GAIN_DELTA	0x00000fc0
#घोषणा	AR5K_PHY_TX_PWR_ADJ_CCK_GAIN_DELTA_S	6
#घोषणा	AR5K_PHY_TX_PWR_ADJ_CCK_PCDAC_INDEX	0x00fc0000
#घोषणा	AR5K_PHY_TX_PWR_ADJ_CCK_PCDAC_INDEX_S	18

/*
 * PHY radar detection रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_RADAR			0x9954
#घोषणा	AR5K_PHY_RADAR_ENABLE		0x00000001
#घोषणा	AR5K_PHY_RADAR_DISABLE		0x00000000
#घोषणा AR5K_PHY_RADAR_INBANDTHR	0x0000003e	/* Inband threshold
							5-bits, units unknown अणु0..31पूर्ण
							(? MHz ?) */
#घोषणा AR5K_PHY_RADAR_INBANDTHR_S	1

#घोषणा AR5K_PHY_RADAR_PRSSI_THR	0x00000fc0	/* Pulse RSSI/SNR threshold
							6-bits, dBm range अणु0..63पूर्ण
							in dBm units. */
#घोषणा AR5K_PHY_RADAR_PRSSI_THR_S	6

#घोषणा AR5K_PHY_RADAR_PHEIGHT_THR	0x0003f000	/* Pulse height threshold
							6-bits, dBm range अणु0..63पूर्ण
							in dBm units. */
#घोषणा AR5K_PHY_RADAR_PHEIGHT_THR_S	12

#घोषणा AR5K_PHY_RADAR_RSSI_THR		0x00fc0000	/* Radar RSSI/SNR threshold.
							6-bits, dBm range अणु0..63पूर्ण
							in dBm units. */
#घोषणा AR5K_PHY_RADAR_RSSI_THR_S	18

#घोषणा AR5K_PHY_RADAR_FIRPWR_THR	0x7f000000	/* Finite Impulse Response
							filter घातer out threshold.
							7-bits, standard घातer range
							अणु0..127पूर्ण in 1/2 dBm units. */
#घोषणा AR5K_PHY_RADAR_FIRPWR_THRS	24

/*
 * PHY antenna चयन table रेजिस्टरs
 */
#घोषणा AR5K_PHY_ANT_SWITCH_TABLE_0	0x9960
#घोषणा AR5K_PHY_ANT_SWITCH_TABLE_1	0x9964

/*
 * PHY Noise न्यूनमान threshold
 */
#घोषणा AR5K_PHY_NFTHRES		0x9968

/*
 * Sigma Delta रेजिस्टर (?) [5213]
 */
#घोषणा AR5K_PHY_SIGMA_DELTA		0x996C
#घोषणा AR5K_PHY_SIGMA_DELTA_ADC_SEL	0x00000003
#घोषणा AR5K_PHY_SIGMA_DELTA_ADC_SEL_S	0
#घोषणा AR5K_PHY_SIGMA_DELTA_FILT2	0x000000f8
#घोषणा AR5K_PHY_SIGMA_DELTA_FILT2_S	3
#घोषणा AR5K_PHY_SIGMA_DELTA_FILT1	0x00001f00
#घोषणा AR5K_PHY_SIGMA_DELTA_FILT1_S	8
#घोषणा AR5K_PHY_SIGMA_DELTA_ADC_CLIP	0x01ffe000
#घोषणा AR5K_PHY_SIGMA_DELTA_ADC_CLIP_S	13

/*
 * RF restart रेजिस्टर [5112+] (?)
 */
#घोषणा AR5K_PHY_RESTART		0x9970		/* restart */
#घोषणा AR5K_PHY_RESTART_DIV_GC		0x001c0000	/* Fast भागersity gc_limit (?) */
#घोषणा AR5K_PHY_RESTART_DIV_GC_S	18

/*
 * RF Bus access request रेजिस्टर (क्रम synth-only channel चयनing)
 */
#घोषणा AR5K_PHY_RFBUS_REQ		0x997C
#घोषणा AR5K_PHY_RFBUS_REQ_REQUEST	0x00000001

/*
 * Spur mitigation masks (?)
 */
#घोषणा AR5K_PHY_TIMING_7		0x9980
#घोषणा AR5K_PHY_TIMING_8		0x9984
#घोषणा AR5K_PHY_TIMING_8_PILOT_MASK_2		0x000fffff
#घोषणा AR5K_PHY_TIMING_8_PILOT_MASK_2_S	0

#घोषणा AR5K_PHY_BIN_MASK2_1		0x9988
#घोषणा AR5K_PHY_BIN_MASK2_2		0x998c
#घोषणा AR5K_PHY_BIN_MASK2_3		0x9990

#घोषणा AR5K_PHY_BIN_MASK2_4		0x9994
#घोषणा AR5K_PHY_BIN_MASK2_4_MASK_4	0x00003fff
#घोषणा AR5K_PHY_BIN_MASK2_4_MASK_4_S	0

#घोषणा AR5K_PHY_TIMING_9			0x9998
#घोषणा AR5K_PHY_TIMING_10			0x999c
#घोषणा AR5K_PHY_TIMING_10_PILOT_MASK_2		0x000fffff
#घोषणा AR5K_PHY_TIMING_10_PILOT_MASK_2_S	0

/*
 * Spur mitigation control
 */
#घोषणा AR5K_PHY_TIMING_11			0x99a0		/* Register address */
#घोषणा AR5K_PHY_TIMING_11_SPUR_DELTA_PHASE	0x000fffff	/* Spur delta phase */
#घोषणा AR5K_PHY_TIMING_11_SPUR_DELTA_PHASE_S	0
#घोषणा AR5K_PHY_TIMING_11_SPUR_FREQ_SD		0x3ff00000	/* Freq sigma delta */
#घोषणा AR5K_PHY_TIMING_11_SPUR_FREQ_SD_S	20
#घोषणा AR5K_PHY_TIMING_11_USE_SPUR_IN_AGC	0x40000000	/* Spur filter in AGC detector */
#घोषणा AR5K_PHY_TIMING_11_USE_SPUR_IN_SELFCOR	0x80000000	/* Spur filter in OFDM self correlator */

/*
 * Gain tables
 */
#घोषणा	AR5K_BB_GAIN_BASE		0x9b00	/* BaseBand Amplअगरier Gain table base address */
#घोषणा AR5K_BB_GAIN(_n)		(AR5K_BB_GAIN_BASE + ((_n) << 2))
#घोषणा	AR5K_RF_GAIN_BASE		0x9a00	/* RF Amplअगरier Gain table base address */
#घोषणा AR5K_RF_GAIN(_n)		(AR5K_RF_GAIN_BASE + ((_n) << 2))

/*
 * PHY timing IQ calibration result रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_IQRES_CAL_PWR_I	0x9c10	/* I (Inphase) घातer value */
#घोषणा	AR5K_PHY_IQRES_CAL_PWR_Q	0x9c14	/* Q (Quadrature) घातer value */
#घोषणा	AR5K_PHY_IQRES_CAL_CORR		0x9c18	/* I/Q Correlation */

/*
 * PHY current RSSI रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_CURRENT_RSSI	0x9c1c

/*
 * PHY RF Bus grant रेजिस्टर
 */
#घोषणा	AR5K_PHY_RFBUS_GRANT	0x9c20
#घोषणा	AR5K_PHY_RFBUS_GRANT_OK	0x00000001

/*
 * PHY ADC test रेजिस्टर
 */
#घोषणा	AR5K_PHY_ADC_TEST	0x9c24
#घोषणा	AR5K_PHY_ADC_TEST_I	0x00000001
#घोषणा	AR5K_PHY_ADC_TEST_Q	0x00000200

/*
 * PHY DAC test रेजिस्टर
 */
#घोषणा	AR5K_PHY_DAC_TEST	0x9c28
#घोषणा	AR5K_PHY_DAC_TEST_I	0x00000001
#घोषणा	AR5K_PHY_DAC_TEST_Q	0x00000200

/*
 * PHY PTAT रेजिस्टर (?)
 */
#घोषणा	AR5K_PHY_PTAT		0x9c2c

/*
 * PHY Illegal TX rate रेजिस्टर [5112+]
 */
#घोषणा	AR5K_PHY_BAD_TX_RATE	0x9c30

/*
 * PHY SPUR Power रेजिस्टर [5112+]
 */
#घोषणा	AR5K_PHY_SPUR_PWR	0x9c34			/* Register Address */
#घोषणा	AR5K_PHY_SPUR_PWR_I	0x00000001	/* SPUR Power estimate क्रम I (field) */
#घोषणा	AR5K_PHY_SPUR_PWR_Q	0x00000100	/* SPUR Power estimate क्रम Q (field) */
#घोषणा	AR5K_PHY_SPUR_PWR_FILT	0x00010000	/* Power with SPUR हटाओd (field) */

/*
 * PHY Channel status रेजिस्टर [5112+] (?)
 */
#घोषणा	AR5K_PHY_CHAN_STATUS		0x9c38
#घोषणा	AR5K_PHY_CHAN_STATUS_BT_ACT	0x00000001
#घोषणा	AR5K_PHY_CHAN_STATUS_RX_CLR_RAW	0x00000002
#घोषणा	AR5K_PHY_CHAN_STATUS_RX_CLR_MAC	0x00000004
#घोषणा	AR5K_PHY_CHAN_STATUS_RX_CLR_PAP	0x00000008

/*
 * Heavy clip enable रेजिस्टर
 */
#घोषणा	AR5K_PHY_HEAVY_CLIP_ENABLE	0x99e0

/*
 * PHY घड़ी sleep रेजिस्टरs [5112+]
 */
#घोषणा AR5K_PHY_SCLOCK			0x99f0
#घोषणा AR5K_PHY_SCLOCK_32MHZ		0x0000000c
#घोषणा AR5K_PHY_SDELAY			0x99f4
#घोषणा AR5K_PHY_SDELAY_32MHZ		0x000000ff
#घोषणा AR5K_PHY_SPENDING		0x99f8


/*
 * PHY PAPD I (घातer?) table (?)
 * (92! entries)
 */
#घोषणा	AR5K_PHY_PAPD_I_BASE	0xa000
#घोषणा	AR5K_PHY_PAPD_I(_n)	(AR5K_PHY_PAPD_I_BASE + ((_n) << 2))

/*
 * PHY PCDAC TX घातer table
 */
#घोषणा	AR5K_PHY_PCDAC_TXPOWER_BASE	0xa180
#घोषणा	AR5K_PHY_PCDAC_TXPOWER(_n)	(AR5K_PHY_PCDAC_TXPOWER_BASE + ((_n) << 2))

/*
 * PHY mode रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_MODE			0x0a200			/* Register Address */
#घोषणा	AR5K_PHY_MODE_MOD		0x00000001	/* PHY Modulation bit */
#घोषणा AR5K_PHY_MODE_MOD_OFDM		0
#घोषणा AR5K_PHY_MODE_MOD_CCK		1
#घोषणा AR5K_PHY_MODE_FREQ		0x00000002	/* Freq mode bit */
#घोषणा	AR5K_PHY_MODE_FREQ_5GHZ		0
#घोषणा	AR5K_PHY_MODE_FREQ_2GHZ		2
#घोषणा AR5K_PHY_MODE_MOD_DYN		0x00000004	/* Enable Dynamic OFDM/CCK mode [5112+] */
#घोषणा AR5K_PHY_MODE_RAD		0x00000008	/* [5212+] */
#घोषणा AR5K_PHY_MODE_RAD_RF5111	0
#घोषणा AR5K_PHY_MODE_RAD_RF5112	8
#घोषणा AR5K_PHY_MODE_XR		0x00000010	/* Enable XR mode [5112+] */
#घोषणा	AR5K_PHY_MODE_HALF_RATE		0x00000020	/* Enable Half rate (test) */
#घोषणा	AR5K_PHY_MODE_QUARTER_RATE	0x00000040	/* Enable Quarter rat (test) */

/*
 * PHY CCK transmit control रेजिस्टर [5111+ (?)]
 */
#घोषणा AR5K_PHY_CCKTXCTL		0xa204
#घोषणा AR5K_PHY_CCKTXCTL_WORLD		0x00000000
#घोषणा AR5K_PHY_CCKTXCTL_JAPAN		0x00000010
#घोषणा	AR5K_PHY_CCKTXCTL_SCRAMBLER_DIS	0x00000001
#घोषणा	AR5K_PHY_CCKTXCTK_DAC_SCALE	0x00000004

/*
 * PHY CCK Cross-correlator Barker RSSI threshold रेजिस्टर [5212+]
 */
#घोषणा AR5K_PHY_CCK_CROSSCORR			0xa208
#घोषणा AR5K_PHY_CCK_CROSSCORR_WEAK_SIG_THR	0x0000003f
#घोषणा AR5K_PHY_CCK_CROSSCORR_WEAK_SIG_THR_S	0

/* Same address is used क्रम antenna भागersity activation */
#घोषणा	AR5K_PHY_FAST_ANT_DIV		0xa208
#घोषणा	AR5K_PHY_FAST_ANT_DIV_EN	0x00002000

/*
 * PHY 2GHz gain रेजिस्टर [5111+]
 */
#घोषणा	AR5K_PHY_GAIN_2GHZ			0xa20c
#घोषणा	AR5K_PHY_GAIN_2GHZ_MARGIN_TXRX		0x00fc0000
#घोषणा	AR5K_PHY_GAIN_2GHZ_MARGIN_TXRX_S	18
#घोषणा	AR5K_PHY_GAIN_2GHZ_INI_5111		0x6480416c

#घोषणा	AR5K_PHY_CCK_RX_CTL_4			0xa21c
#घोषणा	AR5K_PHY_CCK_RX_CTL_4_FREQ_EST_SHORT	0x01f80000
#घोषणा	AR5K_PHY_CCK_RX_CTL_4_FREQ_EST_SHORT_S	19

#घोषणा	AR5K_PHY_DAG_CCK_CTL			0xa228
#घोषणा	AR5K_PHY_DAG_CCK_CTL_EN_RSSI_THR	0x00000200
#घोषणा	AR5K_PHY_DAG_CCK_CTL_RSSI_THR		0x0001fc00
#घोषणा	AR5K_PHY_DAG_CCK_CTL_RSSI_THR_S		10

#घोषणा	AR5K_PHY_FAST_ADC	0xa24c

#घोषणा	AR5K_PHY_BLUETOOTH	0xa254

/*
 * Transmit Power Control रेजिस्टर
 * [2413+]
 */
#घोषणा	AR5K_PHY_TPC_RG1		0xa258
#घोषणा	AR5K_PHY_TPC_RG1_NUM_PD_GAIN	0x0000c000
#घोषणा	AR5K_PHY_TPC_RG1_NUM_PD_GAIN_S	14
#घोषणा AR5K_PHY_TPC_RG1_PDGAIN_1	0x00030000
#घोषणा AR5K_PHY_TPC_RG1_PDGAIN_1_S	16
#घोषणा AR5K_PHY_TPC_RG1_PDGAIN_2	0x000c0000
#घोषणा AR5K_PHY_TPC_RG1_PDGAIN_2_S	18
#घोषणा AR5K_PHY_TPC_RG1_PDGAIN_3	0x00300000
#घोषणा AR5K_PHY_TPC_RG1_PDGAIN_3_S	20

#घोषणा	AR5K_PHY_TPC_RG5			0xa26C
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP	0x0000000F
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP_S	0
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_1	0x000003F0
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_1_S	4
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_2	0x0000FC00
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_2_S	10
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_3	0x003F0000
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_3_S	16
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_4	0x0FC00000
#घोषणा	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_4_S	22

/*
 * PHY PDADC Tx घातer table
 */
#घोषणा AR5K_PHY_PDADC_TXPOWER_BASE	0xa280
#घोषणा	AR5K_PHY_PDADC_TXPOWER(_n)	(AR5K_PHY_PDADC_TXPOWER_BASE + ((_n) << 2))

/*
 * Platक्रमm रेजिस्टरs क्रम WiSoC
 */
#घोषणा AR5K_AR5312_RESET		0xbc003020
#घोषणा AR5K_AR5312_RESET_BB0_COLD	0x00000004
#घोषणा AR5K_AR5312_RESET_BB1_COLD	0x00000200
#घोषणा AR5K_AR5312_RESET_WMAC0		0x00002000
#घोषणा AR5K_AR5312_RESET_BB0_WARM	0x00004000
#घोषणा AR5K_AR5312_RESET_WMAC1		0x00020000
#घोषणा AR5K_AR5312_RESET_BB1_WARM	0x00040000

#घोषणा AR5K_AR5312_ENABLE		0xbc003080
#घोषणा AR5K_AR5312_ENABLE_WLAN0    0x00000001
#घोषणा AR5K_AR5312_ENABLE_WLAN1    0x00000008

#घोषणा AR5K_AR2315_RESET		0xb1000004
#घोषणा AR5K_AR2315_RESET_WMAC		0x00000001
#घोषणा AR5K_AR2315_RESET_BB_WARM	0x00000002

#घोषणा AR5K_AR2315_AHB_ARB_CTL		0xb1000008
#घोषणा AR5K_AR2315_AHB_ARB_CTL_WLAN	0x00000002

#घोषणा AR5K_AR2315_BYTESWAP	0xb100000c
#घोषणा AR5K_AR2315_BYTESWAP_WMAC	0x00000002
