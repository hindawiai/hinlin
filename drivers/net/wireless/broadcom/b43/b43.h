<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_H_
#घोषणा B43_H_

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/ssb/ssb.h>
#समावेश <linux/completion.h>
#समावेश <net/mac80211.h>

#समावेश "debugfs.h"
#समावेश "leds.h"
#समावेश "rfkill.h"
#समावेश "bus.h"
#समावेश "lo.h"
#समावेश "phy_common.h"


#अगर_घोषित CONFIG_B43_DEBUG
# define B43_DEBUG	1
#अन्यथा
# define B43_DEBUG	0
#पूर्ण_अगर

/* MMIO offsets */
#घोषणा B43_MMIO_DMA0_REASON		0x20
#घोषणा B43_MMIO_DMA0_IRQ_MASK		0x24
#घोषणा B43_MMIO_DMA1_REASON		0x28
#घोषणा B43_MMIO_DMA1_IRQ_MASK		0x2C
#घोषणा B43_MMIO_DMA2_REASON		0x30
#घोषणा B43_MMIO_DMA2_IRQ_MASK		0x34
#घोषणा B43_MMIO_DMA3_REASON		0x38
#घोषणा B43_MMIO_DMA3_IRQ_MASK		0x3C
#घोषणा B43_MMIO_DMA4_REASON		0x40
#घोषणा B43_MMIO_DMA4_IRQ_MASK		0x44
#घोषणा B43_MMIO_DMA5_REASON		0x48
#घोषणा B43_MMIO_DMA5_IRQ_MASK		0x4C
#घोषणा B43_MMIO_MACCTL			0x120	/* MAC control */
#घोषणा B43_MMIO_MACCMD			0x124	/* MAC command */
#घोषणा B43_MMIO_GEN_IRQ_REASON		0x128
#घोषणा B43_MMIO_GEN_IRQ_MASK		0x12C
#घोषणा B43_MMIO_RAM_CONTROL		0x130
#घोषणा B43_MMIO_RAM_DATA		0x134
#घोषणा B43_MMIO_PS_STATUS		0x140
#घोषणा B43_MMIO_RADIO_HWENABLED_HI	0x158
#घोषणा B43_MMIO_MAC_HW_CAP		0x15C	/* MAC capabilities (corerev >= 13) */
#घोषणा B43_MMIO_SHM_CONTROL		0x160
#घोषणा B43_MMIO_SHM_DATA		0x164
#घोषणा B43_MMIO_SHM_DATA_UNALIGNED	0x166
#घोषणा B43_MMIO_XMITSTAT_0		0x170
#घोषणा B43_MMIO_XMITSTAT_1		0x174
#घोषणा B43_MMIO_REV3PLUS_TSF_LOW	0x180	/* core rev >= 3 only */
#घोषणा B43_MMIO_REV3PLUS_TSF_HIGH	0x184	/* core rev >= 3 only */
#घोषणा B43_MMIO_TSF_CFP_REP		0x188
#घोषणा B43_MMIO_TSF_CFP_START		0x18C
#घोषणा B43_MMIO_TSF_CFP_MAXDUR		0x190

/* 32-bit DMA */
#घोषणा B43_MMIO_DMA32_BASE0		0x200
#घोषणा B43_MMIO_DMA32_BASE1		0x220
#घोषणा B43_MMIO_DMA32_BASE2		0x240
#घोषणा B43_MMIO_DMA32_BASE3		0x260
#घोषणा B43_MMIO_DMA32_BASE4		0x280
#घोषणा B43_MMIO_DMA32_BASE5		0x2A0
/* 64-bit DMA */
#घोषणा B43_MMIO_DMA64_BASE0		0x200
#घोषणा B43_MMIO_DMA64_BASE1		0x240
#घोषणा B43_MMIO_DMA64_BASE2		0x280
#घोषणा B43_MMIO_DMA64_BASE3		0x2C0
#घोषणा B43_MMIO_DMA64_BASE4		0x300
#घोषणा B43_MMIO_DMA64_BASE5		0x340

/* PIO on core rev < 11 */
#घोषणा B43_MMIO_PIO_BASE0		0x300
#घोषणा B43_MMIO_PIO_BASE1		0x310
#घोषणा B43_MMIO_PIO_BASE2		0x320
#घोषणा B43_MMIO_PIO_BASE3		0x330
#घोषणा B43_MMIO_PIO_BASE4		0x340
#घोषणा B43_MMIO_PIO_BASE5		0x350
#घोषणा B43_MMIO_PIO_BASE6		0x360
#घोषणा B43_MMIO_PIO_BASE7		0x370
/* PIO on core rev >= 11 */
#घोषणा B43_MMIO_PIO11_BASE0		0x200
#घोषणा B43_MMIO_PIO11_BASE1		0x240
#घोषणा B43_MMIO_PIO11_BASE2		0x280
#घोषणा B43_MMIO_PIO11_BASE3		0x2C0
#घोषणा B43_MMIO_PIO11_BASE4		0x300
#घोषणा B43_MMIO_PIO11_BASE5		0x340

#घोषणा B43_MMIO_RADIO24_CONTROL	0x3D8	/* core rev >= 24 only */
#घोषणा B43_MMIO_RADIO24_DATA		0x3DA	/* core rev >= 24 only */
#घोषणा B43_MMIO_PHY_VER		0x3E0
#घोषणा B43_MMIO_PHY_RADIO		0x3E2
#घोषणा B43_MMIO_PHY0			0x3E6
#घोषणा B43_MMIO_ANTENNA		0x3E8
#घोषणा B43_MMIO_CHANNEL		0x3F0
#घोषणा B43_MMIO_CHANNEL_EXT		0x3F4
#घोषणा B43_MMIO_RADIO_CONTROL		0x3F6
#घोषणा B43_MMIO_RADIO_DATA_HIGH	0x3F8
#घोषणा B43_MMIO_RADIO_DATA_LOW		0x3FA
#घोषणा B43_MMIO_PHY_CONTROL		0x3FC
#घोषणा B43_MMIO_PHY_DATA		0x3FE
#घोषणा B43_MMIO_MACFILTER_CONTROL	0x420
#घोषणा B43_MMIO_MACFILTER_DATA		0x422
#घोषणा B43_MMIO_RCMTA_COUNT		0x43C
#घोषणा B43_MMIO_PSM_PHY_HDR		0x492
#घोषणा B43_MMIO_RADIO_HWENABLED_LO	0x49A
#घोषणा B43_MMIO_GPIO_CONTROL		0x49C
#घोषणा B43_MMIO_GPIO_MASK		0x49E
#घोषणा B43_MMIO_TXE0_CTL		0x500
#घोषणा B43_MMIO_TXE0_AUX		0x502
#घोषणा B43_MMIO_TXE0_TS_LOC		0x504
#घोषणा B43_MMIO_TXE0_TIME_OUT		0x506
#घोषणा B43_MMIO_TXE0_WM_0		0x508
#घोषणा B43_MMIO_TXE0_WM_1		0x50A
#घोषणा B43_MMIO_TXE0_PHYCTL		0x50C
#घोषणा B43_MMIO_TXE0_STATUS		0x50E
#घोषणा B43_MMIO_TXE0_MMPLCP0		0x510
#घोषणा B43_MMIO_TXE0_MMPLCP1		0x512
#घोषणा B43_MMIO_TXE0_PHYCTL1		0x514
#घोषणा B43_MMIO_XMTFIFODEF		0x520
#घोषणा B43_MMIO_XMTFIFO_FRAME_CNT	0x522	/* core rev>= 16 only */
#घोषणा B43_MMIO_XMTFIFO_BYTE_CNT	0x524	/* core rev>= 16 only */
#घोषणा B43_MMIO_XMTFIFO_HEAD		0x526	/* core rev>= 16 only */
#घोषणा B43_MMIO_XMTFIFO_RD_PTR		0x528	/* core rev>= 16 only */
#घोषणा B43_MMIO_XMTFIFO_WR_PTR		0x52A	/* core rev>= 16 only */
#घोषणा B43_MMIO_XMTFIFODEF1		0x52C	/* core rev>= 16 only */
#घोषणा B43_MMIO_XMTFIFOCMD		0x540
#घोषणा B43_MMIO_XMTFIFOFLUSH		0x542
#घोषणा B43_MMIO_XMTFIFOTHRESH		0x544
#घोषणा B43_MMIO_XMTFIFORDY		0x546
#घोषणा B43_MMIO_XMTFIFOPRIRDY		0x548
#घोषणा B43_MMIO_XMTFIFORQPRI		0x54A
#घोषणा B43_MMIO_XMTTPLATETXPTR		0x54C
#घोषणा B43_MMIO_XMTTPLATEPTR		0x550
#घोषणा B43_MMIO_SMPL_CLCT_STRPTR	0x552	/* core rev>= 22 only */
#घोषणा B43_MMIO_SMPL_CLCT_STPPTR	0x554	/* core rev>= 22 only */
#घोषणा B43_MMIO_SMPL_CLCT_CURPTR	0x556	/* core rev>= 22 only */
#घोषणा B43_MMIO_XMTTPLATEDATALO	0x560
#घोषणा B43_MMIO_XMTTPLATEDATAHI	0x562
#घोषणा B43_MMIO_XMTSEL			0x568
#घोषणा B43_MMIO_XMTTXCNT		0x56A
#घोषणा B43_MMIO_XMTTXSHMADDR		0x56C
#घोषणा B43_MMIO_TSF_CFP_START_LOW	0x604
#घोषणा B43_MMIO_TSF_CFP_START_HIGH	0x606
#घोषणा B43_MMIO_TSF_CFP_PRETBTT	0x612
#घोषणा B43_MMIO_TSF_CLK_FRAC_LOW	0x62E
#घोषणा B43_MMIO_TSF_CLK_FRAC_HIGH	0x630
#घोषणा B43_MMIO_TSF_0			0x632	/* core rev < 3 only */
#घोषणा B43_MMIO_TSF_1			0x634	/* core rev < 3 only */
#घोषणा B43_MMIO_TSF_2			0x636	/* core rev < 3 only */
#घोषणा B43_MMIO_TSF_3			0x638	/* core rev < 3 only */
#घोषणा B43_MMIO_RNG			0x65A
#घोषणा B43_MMIO_IFSSLOT		0x684	/* Interframe slot समय */
#घोषणा B43_MMIO_IFSCTL			0x688	/* Interframe space control */
#घोषणा B43_MMIO_IFSSTAT		0x690
#घोषणा B43_MMIO_IFSMEDBUSYCTL		0x692
#घोषणा B43_MMIO_IFTXDUR		0x694
#घोषणा  B43_MMIO_IFSCTL_USE_EDCF	0x0004
#घोषणा B43_MMIO_POWERUP_DELAY		0x6A8
#घोषणा B43_MMIO_BTCOEX_CTL		0x6B4 /* Bluetooth Coexistence Control */
#घोषणा B43_MMIO_BTCOEX_STAT		0x6B6 /* Bluetooth Coexistence Status */
#घोषणा B43_MMIO_BTCOEX_TXCTL		0x6B8 /* Bluetooth Coexistence Transmit Control */
#घोषणा B43_MMIO_WEPCTL			0x7C0

/* SPROM boardflags_lo values */
#घोषणा B43_BFL_BTCOEXIST		0x0001	/* implements Bluetooth coexistance */
#घोषणा B43_BFL_PACTRL			0x0002	/* GPIO 9 controlling the PA */
#घोषणा B43_BFL_AIRLINEMODE		0x0004	/* implements GPIO 13 radio disable indication */
#घोषणा B43_BFL_RSSI			0x0008	/* software calculates nrssi slope. */
#घोषणा B43_BFL_ENETSPI			0x0010	/* has ephy roboचयन spi */
#घोषणा B43_BFL_XTAL_NOSLOW		0x0020	/* no slow घड़ी available */
#घोषणा B43_BFL_CCKHIPWR		0x0040	/* can करो high घातer CCK transmission */
#घोषणा B43_BFL_ENETADM			0x0080	/* has ADMtek चयन */
#घोषणा B43_BFL_ENETVLAN		0x0100	/* can करो vlan */
#घोषणा B43_BFL_AFTERBURNER		0x0200	/* supports Afterburner mode */
#घोषणा B43_BFL_NOPCI			0x0400	/* leaves PCI भग्नing */
#घोषणा B43_BFL_FEM			0x0800	/* supports the Front End Module */
#घोषणा B43_BFL_EXTLNA			0x1000	/* has an बाह्यal LNA */
#घोषणा B43_BFL_HGPA			0x2000	/* had high gain PA */
#घोषणा B43_BFL_BTCMOD			0x4000	/* BFL_BTCOEXIST is given in alternate GPIOs */
#घोषणा B43_BFL_ALTIQ			0x8000	/* alternate I/Q settings */

/* SPROM boardflags_hi values */
#घोषणा B43_BFH_NOPA			0x0001	/* has no PA */
#घोषणा B43_BFH_RSSIINV			0x0002	/* RSSI uses positive slope (not TSSI) */
#घोषणा B43_BFH_PAREF			0x0004	/* uses the PARef LDO */
#घोषणा B43_BFH_3TSWITCH		0x0008	/* uses a triple throw चयन shared
						 * with bluetooth */
#घोषणा B43_BFH_PHASESHIFT		0x0010	/* can support phase shअगरter */
#घोषणा B43_BFH_BUCKBOOST		0x0020	/* has buck/booster */
#घोषणा B43_BFH_FEM_BT			0x0040	/* has FEM and चयन to share antenna
						 * with bluetooth */
#घोषणा B43_BFH_NOCBUCK			0x0080
#घोषणा B43_BFH_PALDO			0x0200
#घोषणा B43_BFH_EXTLNA_5GHZ		0x1000	/* has an बाह्यal LNA (5GHz mode) */

/* SPROM boardflags2_lo values */
#घोषणा B43_BFL2_RXBB_INT_REG_DIS	0x0001	/* बाह्यal RX BB regulator present */
#घोषणा B43_BFL2_APLL_WAR		0x0002	/* alternative A-band PLL settings implemented */
#घोषणा B43_BFL2_TXPWRCTRL_EN 		0x0004	/* permits enabling TX Power Control */
#घोषणा B43_BFL2_2X4_DIV		0x0008	/* 2x4 भागersity चयन */
#घोषणा B43_BFL2_5G_PWRGAIN		0x0010	/* supports 5G band घातer gain */
#घोषणा B43_BFL2_PCIEWAR_OVR		0x0020	/* overrides ASPM and Clkreq settings */
#घोषणा B43_BFL2_CAESERS_BRD		0x0040	/* is Caesers board (unused) */
#घोषणा B43_BFL2_BTC3WIRE		0x0080	/* used 3-wire bluetooth coexist */
#घोषणा B43_BFL2_SKWRKFEM_BRD		0x0100	/* 4321mcm93 uses Skyworks FEM */
#घोषणा B43_BFL2_SPUR_WAR		0x0200	/* has a workaround क्रम घड़ी-harmonic spurs */
#घोषणा B43_BFL2_GPLL_WAR		0x0400	/* altenative G-band PLL settings implemented */
#घोषणा B43_BFL2_SINGLEANT_CCK		0x1000
#घोषणा B43_BFL2_2G_SPUR_WAR		0x2000

/* SPROM boardflags2_hi values */
#घोषणा B43_BFH2_GPLL_WAR2		0x0001
#घोषणा B43_BFH2_IPALVLSHIFT_3P3	0x0002
#घोषणा B43_BFH2_INTERNDET_TXIQCAL	0x0004
#घोषणा B43_BFH2_XTALBUFOUTEN		0x0008

/* GPIO रेजिस्टर offset, in both ChipCommon and PCI core. */
#घोषणा B43_GPIO_CONTROL		0x6c

/* SHM Routing */
क्रमागत अणु
	B43_SHM_UCODE,		/* Microcode memory */
	B43_SHM_SHARED,		/* Shared memory */
	B43_SHM_SCRATCH,	/* Scratch memory */
	B43_SHM_HW,		/* Internal hardware रेजिस्टर */
	B43_SHM_RCMTA,		/* Receive match transmitter address (rev >= 5 only) */
पूर्ण;
/* SHM Routing modअगरiers */
#घोषणा B43_SHM_AUTOINC_R		0x0200	/* Auto-increment address on पढ़ो */
#घोषणा B43_SHM_AUTOINC_W		0x0100	/* Auto-increment address on ग_लिखो */
#घोषणा B43_SHM_AUTOINC_RW		(B43_SHM_AUTOINC_R | \
					 B43_SHM_AUTOINC_W)

/* Misc SHM_SHARED offsets */
#घोषणा B43_SHM_SH_WLCOREREV		0x0016	/* 802.11 core revision */
#घोषणा B43_SHM_SH_PCTLWDPOS		0x0008
#घोषणा B43_SHM_SH_RXPADOFF		0x0034	/* RX Padding data offset (PIO only) */
#घोषणा B43_SHM_SH_FWCAPA		0x0042	/* Firmware capabilities (Opensource firmware only) */
#घोषणा B43_SHM_SH_PHYVER		0x0050	/* PHY version */
#घोषणा B43_SHM_SH_PHYTYPE		0x0052	/* PHY type */
#घोषणा B43_SHM_SH_ANTSWAP		0x005C	/* Antenna swap threshold */
#घोषणा B43_SHM_SH_HOSTF1		0x005E	/* Hostflags 1 क्रम ucode options */
#घोषणा B43_SHM_SH_HOSTF2		0x0060	/* Hostflags 2 क्रम ucode options */
#घोषणा B43_SHM_SH_HOSTF3		0x0062	/* Hostflags 3 क्रम ucode options */
#घोषणा B43_SHM_SH_RFATT		0x0064	/* Current radio attenuation value */
#घोषणा B43_SHM_SH_RADAR		0x0066	/* Radar रेजिस्टर */
#घोषणा B43_SHM_SH_PHYTXNOI		0x006E	/* PHY noise directly after TX (lower 8bit only) */
#घोषणा B43_SHM_SH_RFRXSP1		0x0072	/* RF RX SP Register 1 */
#घोषणा B43_SHM_SH_HOSTF4		0x0078	/* Hostflags 4 क्रम ucode options */
#घोषणा B43_SHM_SH_CHAN			0x00A0	/* Current channel (low 8bit only) */
#घोषणा  B43_SHM_SH_CHAN_5GHZ		0x0100	/* Bit set, अगर 5 Ghz channel */
#घोषणा  B43_SHM_SH_CHAN_40MHZ		0x0200	/* Bit set, अगर 40 Mhz channel width */
#घोषणा B43_SHM_SH_MACHW_L		0x00C0	/* Location where the ucode expects the MAC capabilities */
#घोषणा B43_SHM_SH_MACHW_H		0x00C2	/* Location where the ucode expects the MAC capabilities */
#घोषणा B43_SHM_SH_HOSTF5		0x00D4	/* Hostflags 5 क्रम ucode options */
#घोषणा B43_SHM_SH_BCMCFIFOID		0x0108	/* Last posted cookie to the bcast/mcast FIFO */
/* TSSI inक्रमmation */
#घोषणा B43_SHM_SH_TSSI_CCK		0x0058	/* TSSI क्रम last 4 CCK frames (32bit) */
#घोषणा B43_SHM_SH_TSSI_OFDM_A		0x0068	/* TSSI क्रम last 4 OFDM frames (32bit) */
#घोषणा B43_SHM_SH_TSSI_OFDM_G		0x0070	/* TSSI क्रम last 4 OFDM frames (32bit) */
#घोषणा  B43_TSSI_MAX			0x7F	/* Max value क्रम one TSSI value */
/* SHM_SHARED TX FIFO variables */
#घोषणा B43_SHM_SH_SIZE01		0x0098	/* TX FIFO size क्रम FIFO 0 (low) and 1 (high) */
#घोषणा B43_SHM_SH_SIZE23		0x009A	/* TX FIFO size क्रम FIFO 2 and 3 */
#घोषणा B43_SHM_SH_SIZE45		0x009C	/* TX FIFO size क्रम FIFO 4 and 5 */
#घोषणा B43_SHM_SH_SIZE67		0x009E	/* TX FIFO size क्रम FIFO 6 and 7 */
/* SHM_SHARED background noise */
#घोषणा B43_SHM_SH_JSSI0		0x0088	/* Measure JSSI 0 */
#घोषणा B43_SHM_SH_JSSI1		0x008A	/* Measure JSSI 1 */
#घोषणा B43_SHM_SH_JSSIAUX		0x008C	/* Measure JSSI AUX */
/* SHM_SHARED crypto engine */
#घोषणा B43_SHM_SH_DEFAULTIV		0x003C	/* Default IV location */
#घोषणा B43_SHM_SH_NRRXTRANS		0x003E	/* # of soft RX transmitter addresses (max 8) */
#घोषणा B43_SHM_SH_KTP			0x0056	/* Key table poपूर्णांकer */
#घोषणा B43_SHM_SH_TKIPTSCTTAK		0x0318
#घोषणा B43_SHM_SH_KEYIDXBLOCK		0x05D4	/* Key index/algorithm block (v4 firmware) */
#घोषणा B43_SHM_SH_PSM			0x05F4	/* PSM transmitter address match block (rev < 5) */
/* SHM_SHARED WME variables */
#घोषणा B43_SHM_SH_EDCFSTAT		0x000E	/* EDCF status */
#घोषणा B43_SHM_SH_TXFCUR		0x0030	/* TXF current index */
#घोषणा B43_SHM_SH_EDCFQ		0x0240	/* EDCF Q info */
/* SHM_SHARED घातersave mode related */
#घोषणा B43_SHM_SH_SLOTT		0x0010	/* Slot समय */
#घोषणा B43_SHM_SH_DTIMPER		0x0012	/* DTIM period */
#घोषणा B43_SHM_SH_NOSLPZNATDTIM	0x004C	/* NOSLPZNAT DTIM */
/* SHM_SHARED beacon/AP variables */
#घोषणा B43_SHM_SH_BT_BASE0		0x0068	/* Beacon ढाँचा base 0 */
#घोषणा B43_SHM_SH_BTL0			0x0018	/* Beacon ढाँचा length 0 */
#घोषणा B43_SHM_SH_BT_BASE1		0x0468	/* Beacon ढाँचा base 1 */
#घोषणा B43_SHM_SH_BTL1			0x001A	/* Beacon ढाँचा length 1 */
#घोषणा B43_SHM_SH_BTSFOFF		0x001C	/* Beacon TSF offset */
#घोषणा B43_SHM_SH_TIMBPOS		0x001E	/* TIM B position in beacon */
#घोषणा B43_SHM_SH_DTIMP		0x0012	/* DTIP period */
#घोषणा B43_SHM_SH_MCASTCOOKIE		0x00A8	/* Last bcast/mcast frame ID */
#घोषणा B43_SHM_SH_SFFBLIM		0x0044	/* Short frame fallback retry limit */
#घोषणा B43_SHM_SH_LFFBLIM		0x0046	/* Long frame fallback retry limit */
#घोषणा B43_SHM_SH_BEACPHYCTL		0x0054	/* Beacon PHY TX control word (see PHY TX control) */
#घोषणा B43_SHM_SH_EXTNPHYCTL		0x00B0	/* Extended bytes क्रम beacon PHY control (N) */
#घोषणा B43_SHM_SH_BCN_LI		0x00B6	/* beacon listen पूर्णांकerval */
/* SHM_SHARED ACK/CTS control */
#घोषणा B43_SHM_SH_ACKCTSPHYCTL		0x0022	/* ACK/CTS PHY control word (see PHY TX control) */
/* SHM_SHARED probe response variables */
#घोषणा B43_SHM_SH_PRSSID		0x0160	/* Probe Response SSID */
#घोषणा B43_SHM_SH_PRSSIDLEN		0x0048	/* Probe Response SSID length */
#घोषणा B43_SHM_SH_PRTLEN		0x004A	/* Probe Response ढाँचा length */
#घोषणा B43_SHM_SH_PRMAXTIME		0x0074	/* Probe Response max समय */
#घोषणा B43_SHM_SH_PRPHYCTL		0x0188	/* Probe Response PHY TX control word */
/* SHM_SHARED rate tables */
#घोषणा B43_SHM_SH_OFDMसूचीECT		0x01C0	/* Poपूर्णांकer to OFDM direct map */
#घोषणा B43_SHM_SH_OFDMBASIC		0x01E0	/* Poपूर्णांकer to OFDM basic rate map */
#घोषणा B43_SHM_SH_CCKसूचीECT		0x0200	/* Poपूर्णांकer to CCK direct map */
#घोषणा B43_SHM_SH_CCKBASIC		0x0220	/* Poपूर्णांकer to CCK basic rate map */
/* SHM_SHARED microcode soft रेजिस्टरs */
#घोषणा B43_SHM_SH_UCODEREV		0x0000	/* Microcode revision */
#घोषणा B43_SHM_SH_UCODEPATCH		0x0002	/* Microcode patchlevel */
#घोषणा B43_SHM_SH_UCODEDATE		0x0004	/* Microcode date */
#घोषणा B43_SHM_SH_UCODETIME		0x0006	/* Microcode समय */
#घोषणा B43_SHM_SH_UCODESTAT		0x0040	/* Microcode debug status code */
#घोषणा  B43_SHM_SH_UCODESTAT_INVALID	0
#घोषणा  B43_SHM_SH_UCODESTAT_INIT	1
#घोषणा  B43_SHM_SH_UCODESTAT_ACTIVE	2
#घोषणा  B43_SHM_SH_UCODESTAT_SUSP	3	/* suspended */
#घोषणा  B43_SHM_SH_UCODESTAT_SLEEP	4	/* asleep (PS) */
#घोषणा B43_SHM_SH_MAXBFRAMES		0x0080	/* Maximum number of frames in a burst */
#घोषणा B43_SHM_SH_SPUWKUP		0x0094	/* pre-wakeup क्रम synth PU in us */
#घोषणा B43_SHM_SH_PRETBTT		0x0096	/* pre-TBTT in us */
/* SHM_SHARED tx iq workarounds */
#घोषणा B43_SHM_SH_NPHY_TXIQW0		0x0700
#घोषणा B43_SHM_SH_NPHY_TXIQW1		0x0702
#घोषणा B43_SHM_SH_NPHY_TXIQW2		0x0704
#घोषणा B43_SHM_SH_NPHY_TXIQW3		0x0706
/* SHM_SHARED tx pwr ctrl */
#घोषणा B43_SHM_SH_NPHY_TXPWR_INDX0	0x0708
#घोषणा B43_SHM_SH_NPHY_TXPWR_INDX1	0x070E

/* SHM_SCRATCH offsets */
#घोषणा B43_SHM_SC_MINCONT		0x0003	/* Minimum contention winकरोw */
#घोषणा B43_SHM_SC_MAXCONT		0x0004	/* Maximum contention winकरोw */
#घोषणा B43_SHM_SC_CURCONT		0x0005	/* Current contention winकरोw */
#घोषणा B43_SHM_SC_SRLIMIT		0x0006	/* Short retry count limit */
#घोषणा B43_SHM_SC_LRLIMIT		0x0007	/* Long retry count limit */
#घोषणा B43_SHM_SC_DTIMC		0x0008	/* Current DTIM count */
#घोषणा B43_SHM_SC_BTL0LEN		0x0015	/* Beacon 0 ढाँचा length */
#घोषणा B43_SHM_SC_BTL1LEN		0x0016	/* Beacon 1 ढाँचा length */
#घोषणा B43_SHM_SC_SCFB			0x0017	/* Short frame transmit count threshold क्रम rate fallback */
#घोषणा B43_SHM_SC_LCFB			0x0018	/* Long frame transmit count threshold क्रम rate fallback */

/* Hardware Radio Enable masks */
#घोषणा B43_MMIO_RADIO_HWENABLED_HI_MASK (1 << 16)
#घोषणा B43_MMIO_RADIO_HWENABLED_LO_MASK (1 << 4)

/* HostFlags. See b43_hf_पढ़ो/ग_लिखो() */
#घोषणा B43_HF_ANTDIVHELP	0x000000000001ULL /* ucode antenna भाग helper */
#घोषणा B43_HF_SYMW		0x000000000002ULL /* G-PHY SYM workaround */
#घोषणा B43_HF_RXPULLW		0x000000000004ULL /* RX pullup workaround */
#घोषणा B43_HF_CCKBOOST		0x000000000008ULL /* 4dB CCK घातer boost (exclusive with OFDM boost) */
#घोषणा B43_HF_BTCOEX		0x000000000010ULL /* Bluetooth coexistance */
#घोषणा B43_HF_GDCW		0x000000000020ULL /* G-PHY DC canceller filter bw workaround */
#घोषणा B43_HF_OFDMPABOOST	0x000000000040ULL /* Enable PA gain boost क्रम OFDM */
#घोषणा B43_HF_ACPR		0x000000000080ULL /* Disable क्रम Japan, channel 14 */
#घोषणा B43_HF_EDCF		0x000000000100ULL /* on अगर WME and MAC suspended */
#घोषणा B43_HF_TSSIRPSMW	0x000000000200ULL /* TSSI reset PSM ucode workaround */
#घोषणा B43_HF_20IN40IQW	0x000000000200ULL /* 20 in 40 MHz I/Q workaround (rev >= 13 only) */
#घोषणा B43_HF_DSCRQ		0x000000000400ULL /* Disable slow घड़ी request in ucode */
#घोषणा B43_HF_ACIW		0x000000000800ULL /* ACI workaround: shअगरt bits by 2 on PHY CRS */
#घोषणा B43_HF_2060W		0x000000001000ULL /* 2060 radio workaround */
#घोषणा B43_HF_RADARW		0x000000002000ULL /* Radar workaround */
#घोषणा B43_HF_USEDEFKEYS	0x000000004000ULL /* Enable use of शेष keys */
#घोषणा B43_HF_AFTERBURNER	0x000000008000ULL /* Afterburner enabled */
#घोषणा B43_HF_BT4PRIOCOEX	0x000000010000ULL /* Bluetooth 4-priority coexistance */
#घोषणा B43_HF_FWKUP		0x000000020000ULL /* Fast wake-up ucode */
#घोषणा B43_HF_VCORECALC	0x000000040000ULL /* Force VCO recalculation when घातering up synthpu */
#घोषणा B43_HF_PCISCW		0x000000080000ULL /* PCI slow घड़ी workaround */
#घोषणा B43_HF_4318TSSI		0x000000200000ULL /* 4318 TSSI */
#घोषणा B43_HF_FBCMCFIFO	0x000000400000ULL /* Flush bcast/mcast FIFO immediately */
#घोषणा B43_HF_HWPCTL		0x000000800000ULL /* Enable hardwarre घातer control */
#घोषणा B43_HF_BTCOEXALT	0x000001000000ULL /* Bluetooth coexistance in alternate pins */
#घोषणा B43_HF_TXBTCHECK	0x000002000000ULL /* Bluetooth check during transmission */
#घोषणा B43_HF_SKCFPUP		0x000004000000ULL /* Skip CFP update */
#घोषणा B43_HF_N40W		0x000008000000ULL /* N PHY 40 MHz workaround (rev >= 13 only) */
#घोषणा B43_HF_ANTSEL		0x000020000000ULL /* Antenna selection (क्रम testing antenna भाग.) */
#घोषणा B43_HF_BT3COEXT		0x000020000000ULL /* Bluetooth 3-wire coexistence (rev >= 13 only) */
#घोषणा B43_HF_BTCANT		0x000040000000ULL /* Bluetooth coexistence (antenna mode) (rev >= 13 only) */
#घोषणा B43_HF_ANTSELEN		0x000100000000ULL /* Antenna selection enabled (rev >= 13 only) */
#घोषणा B43_HF_ANTSELMODE	0x000200000000ULL /* Antenna selection mode (rev >= 13 only) */
#घोषणा B43_HF_MLADVW		0x001000000000ULL /* N PHY ML ADV workaround (rev >= 13 only) */
#घोषणा B43_HF_PR45960W		0x080000000000ULL /* PR 45960 workaround (rev >= 13 only) */

/* Firmware capabilities field in SHM (Opensource firmware only) */
#घोषणा B43_FWCAPA_HWCRYPTO	0x0001
#घोषणा B43_FWCAPA_QOS		0x0002

/* MacFilter offsets. */
#घोषणा B43_MACFILTER_SELF		0x0000
#घोषणा B43_MACFILTER_BSSID		0x0003

/* PowerControl */
#घोषणा B43_PCTL_IN			0xB0
#घोषणा B43_PCTL_OUT			0xB4
#घोषणा B43_PCTL_OUTENABLE		0xB8
#घोषणा B43_PCTL_XTAL_POWERUP		0x40
#घोषणा B43_PCTL_PLL_POWERDOWN		0x80

/* PowerControl Clock Modes */
#घोषणा B43_PCTL_CLK_FAST		0x00
#घोषणा B43_PCTL_CLK_SLOW		0x01
#घोषणा B43_PCTL_CLK_DYNAMIC		0x02

#घोषणा B43_PCTL_FORCE_SLOW		0x0800
#घोषणा B43_PCTL_FORCE_PLL		0x1000
#घोषणा B43_PCTL_DYN_XTAL		0x2000

/* PHYVersioning */
#घोषणा B43_PHYTYPE_A			0x00
#घोषणा B43_PHYTYPE_B			0x01
#घोषणा B43_PHYTYPE_G			0x02
#घोषणा B43_PHYTYPE_N			0x04
#घोषणा B43_PHYTYPE_LP			0x05
#घोषणा B43_PHYTYPE_SSLPN		0x06
#घोषणा B43_PHYTYPE_HT			0x07
#घोषणा B43_PHYTYPE_LCN			0x08
#घोषणा B43_PHYTYPE_LCNXN		0x09
#घोषणा B43_PHYTYPE_LCN40		0x0a
#घोषणा B43_PHYTYPE_AC			0x0b

/* PHYRegisters */
#घोषणा B43_PHY_ILT_A_CTRL		0x0072
#घोषणा B43_PHY_ILT_A_DATA1		0x0073
#घोषणा B43_PHY_ILT_A_DATA2		0x0074
#घोषणा B43_PHY_G_LO_CONTROL		0x0810
#घोषणा B43_PHY_ILT_G_CTRL		0x0472
#घोषणा B43_PHY_ILT_G_DATA1		0x0473
#घोषणा B43_PHY_ILT_G_DATA2		0x0474
#घोषणा B43_PHY_A_PCTL			0x007B
#घोषणा B43_PHY_G_PCTL			0x0029
#घोषणा B43_PHY_A_CRS			0x0029
#घोषणा B43_PHY_RADIO_BITFIELD		0x0401
#घोषणा B43_PHY_G_CRS			0x0429
#घोषणा B43_PHY_NRSSILT_CTRL		0x0803
#घोषणा B43_PHY_NRSSILT_DATA		0x0804

/* RadioRegisters */
#घोषणा B43_RADIOCTL_ID			0x01

/* MAC Control bitfield */
#घोषणा B43_MACCTL_ENABLED		0x00000001	/* MAC Enabled */
#घोषणा B43_MACCTL_PSM_RUN		0x00000002	/* Run Microcode */
#घोषणा B43_MACCTL_PSM_JMP0		0x00000004	/* Microcode jump to 0 */
#घोषणा B43_MACCTL_SHM_ENABLED		0x00000100	/* SHM Enabled */
#घोषणा B43_MACCTL_SHM_UPPER		0x00000200	/* SHM Upper */
#घोषणा B43_MACCTL_IHR_ENABLED		0x00000400	/* IHR Region Enabled */
#घोषणा B43_MACCTL_PSM_DBG		0x00002000	/* Microcode debugging enabled */
#घोषणा B43_MACCTL_GPOUTSMSK		0x0000C000	/* GPOUT Select Mask */
#घोषणा B43_MACCTL_BE			0x00010000	/* Big Endian mode */
#घोषणा B43_MACCTL_INFRA		0x00020000	/* Infraकाष्ठाure mode */
#घोषणा B43_MACCTL_AP			0x00040000	/* AccessPoपूर्णांक mode */
#घोषणा B43_MACCTL_RADIOLOCK		0x00080000	/* Radio lock */
#घोषणा B43_MACCTL_BEACPROMISC		0x00100000	/* Beacon Promiscuous */
#घोषणा B43_MACCTL_KEEP_BADPLCP		0x00200000	/* Keep frames with bad PLCP */
#घोषणा B43_MACCTL_PHY_LOCK		0x00200000
#घोषणा B43_MACCTL_KEEP_CTL		0x00400000	/* Keep control frames */
#घोषणा B43_MACCTL_KEEP_BAD		0x00800000	/* Keep bad frames (FCS) */
#घोषणा B43_MACCTL_PROMISC		0x01000000	/* Promiscuous mode */
#घोषणा B43_MACCTL_HWPS			0x02000000	/* Hardware Power Saving */
#घोषणा B43_MACCTL_AWAKE		0x04000000	/* Device is awake */
#घोषणा B43_MACCTL_CLOSEDNET		0x08000000	/* Closed net (no SSID bcast) */
#घोषणा B43_MACCTL_TBTTHOLD		0x10000000	/* TBTT Hold */
#घोषणा B43_MACCTL_DISCTXSTAT		0x20000000	/* Discard TX status */
#घोषणा B43_MACCTL_DISCPMQ		0x40000000	/* Discard Power Management Queue */
#घोषणा B43_MACCTL_GMODE		0x80000000	/* G Mode */

/* MAC Command bitfield */
#घोषणा B43_MACCMD_BEACON0_VALID	0x00000001	/* Beacon 0 in ढाँचा RAM is busy/valid */
#घोषणा B43_MACCMD_BEACON1_VALID	0x00000002	/* Beacon 1 in ढाँचा RAM is busy/valid */
#घोषणा B43_MACCMD_DFQ_VALID		0x00000004	/* Directed frame queue valid (IBSS PS mode, ATIM) */
#घोषणा B43_MACCMD_CCA			0x00000008	/* Clear channel assessment */
#घोषणा B43_MACCMD_BGNOISE		0x00000010	/* Background noise */

/* B43_MMIO_PSM_PHY_HDR bits */
#घोषणा B43_PSM_HDR_MAC_PHY_RESET	0x00000001
#घोषणा B43_PSM_HDR_MAC_PHY_CLOCK_EN	0x00000002
#घोषणा B43_PSM_HDR_MAC_PHY_FORCE_CLK	0x00000004

/* See BCMA_CLKCTLST_EXTRESREQ and BCMA_CLKCTLST_EXTRESST */
#घोषणा B43_BCMA_CLKCTLST_80211_PLL_REQ	0x00000100
#घोषणा B43_BCMA_CLKCTLST_PHY_PLL_REQ	0x00000200
#घोषणा B43_BCMA_CLKCTLST_80211_PLL_ST	0x01000000
#घोषणा B43_BCMA_CLKCTLST_PHY_PLL_ST	0x02000000

/* BCMA 802.11 core specअगरic IO Control (BCMA_IOCTL) flags */
#घोषणा B43_BCMA_IOCTL_PHY_CLKEN	0x00000004	/* PHY Clock Enable */
#घोषणा B43_BCMA_IOCTL_PHY_RESET	0x00000008	/* PHY Reset */
#घोषणा B43_BCMA_IOCTL_MACPHYCLKEN	0x00000010	/* MAC PHY Clock Control Enable */
#घोषणा B43_BCMA_IOCTL_PLLREFSEL	0x00000020	/* PLL Frequency Reference Select */
#घोषणा B43_BCMA_IOCTL_PHY_BW		0x000000C0	/* PHY band width and घड़ी speed mask (N-PHY+ only?) */
#घोषणा  B43_BCMA_IOCTL_PHY_BW_10MHZ	0x00000000	/* 10 MHz bandwidth, 40 MHz PHY */
#घोषणा  B43_BCMA_IOCTL_PHY_BW_20MHZ	0x00000040	/* 20 MHz bandwidth, 80 MHz PHY */
#घोषणा  B43_BCMA_IOCTL_PHY_BW_40MHZ	0x00000080	/* 40 MHz bandwidth, 160 MHz PHY */
#घोषणा  B43_BCMA_IOCTL_PHY_BW_80MHZ	0x000000C0	/* 80 MHz bandwidth */
#घोषणा B43_BCMA_IOCTL_DAC		0x00000300	/* Highspeed DAC mode control field */
#घोषणा B43_BCMA_IOCTL_GMODE		0x00002000	/* G Mode Enable */

/* BCMA 802.11 core specअगरic IO status (BCMA_IOST) flags */
#घोषणा B43_BCMA_IOST_2G_PHY		0x00000001	/* 2.4G capable phy */
#घोषणा B43_BCMA_IOST_5G_PHY		0x00000002	/* 5G capable phy */
#घोषणा B43_BCMA_IOST_FASTCLKA		0x00000004	/* Fast Clock Available */
#घोषणा B43_BCMA_IOST_DUALB_PHY		0x00000008	/* Dualband phy */

/* 802.11 core specअगरic TM State Low (SSB_TMSLOW) flags */
#घोषणा B43_TMSLOW_GMODE		0x20000000	/* G Mode Enable */
#घोषणा B43_TMSLOW_PHY_BANDWIDTH	0x00C00000	/* PHY band width and घड़ी speed mask (N-PHY only) */
#घोषणा  B43_TMSLOW_PHY_BANDWIDTH_10MHZ	0x00000000	/* 10 MHz bandwidth, 40 MHz PHY */
#घोषणा  B43_TMSLOW_PHY_BANDWIDTH_20MHZ	0x00400000	/* 20 MHz bandwidth, 80 MHz PHY */
#घोषणा  B43_TMSLOW_PHY_BANDWIDTH_40MHZ	0x00800000	/* 40 MHz bandwidth, 160 MHz PHY */
#घोषणा B43_TMSLOW_PLLREFSEL		0x00200000	/* PLL Frequency Reference Select (rev >= 5) */
#घोषणा B43_TMSLOW_MACPHYCLKEN		0x00100000	/* MAC PHY Clock Control Enable (rev >= 5) */
#घोषणा B43_TMSLOW_PHYRESET		0x00080000	/* PHY Reset */
#घोषणा B43_TMSLOW_PHYCLKEN		0x00040000	/* PHY Clock Enable */

/* 802.11 core specअगरic TM State High (SSB_TMSHIGH) flags */
#घोषणा B43_TMSHIGH_DUALBAND_PHY	0x00080000	/* Dualband PHY available */
#घोषणा B43_TMSHIGH_FCLOCK		0x00040000	/* Fast Clock Available (rev >= 5) */
#घोषणा B43_TMSHIGH_HAVE_5GHZ_PHY	0x00020000	/* 5 GHz PHY available (rev >= 5) */
#घोषणा B43_TMSHIGH_HAVE_2GHZ_PHY	0x00010000	/* 2.4 GHz PHY available (rev >= 5) */

/* Generic-Interrupt reasons. */
#घोषणा B43_IRQ_MAC_SUSPENDED		0x00000001
#घोषणा B43_IRQ_BEACON			0x00000002
#घोषणा B43_IRQ_TBTT_INDI		0x00000004
#घोषणा B43_IRQ_BEACON_TX_OK		0x00000008
#घोषणा B43_IRQ_BEACON_CANCEL		0x00000010
#घोषणा B43_IRQ_ATIM_END		0x00000020
#घोषणा B43_IRQ_PMQ			0x00000040
#घोषणा B43_IRQ_PIO_WORKAROUND		0x00000100
#घोषणा B43_IRQ_MAC_TXERR		0x00000200
#घोषणा B43_IRQ_PHY_TXERR		0x00000800
#घोषणा B43_IRQ_PMEVENT			0x00001000
#घोषणा B43_IRQ_TIMER0			0x00002000
#घोषणा B43_IRQ_TIMER1			0x00004000
#घोषणा B43_IRQ_DMA			0x00008000
#घोषणा B43_IRQ_TXFIFO_FLUSH_OK		0x00010000
#घोषणा B43_IRQ_CCA_MEASURE_OK		0x00020000
#घोषणा B43_IRQ_NOISESAMPLE_OK		0x00040000
#घोषणा B43_IRQ_UCODE_DEBUG		0x08000000
#घोषणा B43_IRQ_RFKILL			0x10000000
#घोषणा B43_IRQ_TX_OK			0x20000000
#घोषणा B43_IRQ_PHY_G_CHANGED		0x40000000
#घोषणा B43_IRQ_TIMEOUT			0x80000000

#घोषणा B43_IRQ_ALL			0xFFFFFFFF
#घोषणा B43_IRQ_MASKTEMPLATE		(B43_IRQ_TBTT_INDI | \
					 B43_IRQ_ATIM_END | \
					 B43_IRQ_PMQ | \
					 B43_IRQ_MAC_TXERR | \
					 B43_IRQ_PHY_TXERR | \
					 B43_IRQ_DMA | \
					 B43_IRQ_TXFIFO_FLUSH_OK | \
					 B43_IRQ_NOISESAMPLE_OK | \
					 B43_IRQ_UCODE_DEBUG | \
					 B43_IRQ_RFKILL | \
					 B43_IRQ_TX_OK)

/* The firmware रेजिस्टर to fetch the debug-IRQ reason from. */
#घोषणा B43_DEBUGIRQ_REASON_REG		63
/* Debug-IRQ reasons. */
#घोषणा B43_DEBUGIRQ_PANIC		0	/* The firmware panic'ed */
#घोषणा B43_DEBUGIRQ_DUMP_SHM		1	/* Dump shared SHM */
#घोषणा B43_DEBUGIRQ_DUMP_REGS		2	/* Dump the microcode रेजिस्टरs */
#घोषणा B43_DEBUGIRQ_MARKER		3	/* A "marker" was thrown by the firmware. */
#घोषणा B43_DEBUGIRQ_ACK		0xFFFF	/* The host ग_लिखोs that to ACK the IRQ */

/* The firmware रेजिस्टर that contains the "marker" line. */
#घोषणा B43_MARKER_ID_REG		2
#घोषणा B43_MARKER_LINE_REG		3

/* The firmware रेजिस्टर to fetch the panic reason from. */
#घोषणा B43_FWPANIC_REASON_REG		3
/* Firmware panic reason codes */
#घोषणा B43_FWPANIC_DIE			0 /* Firmware died. Don't स्वतः-restart it. */
#घोषणा B43_FWPANIC_RESTART		1 /* Firmware died. Schedule a controller reset. */

/* The firmware रेजिस्टर that contains the watchकरोg counter. */
#घोषणा B43_WATCHDOG_REG		1

/* Device specअगरic rate values.
 * The actual values defined here are (rate_in_mbps * 2).
 * Some code depends on this. Don't change it. */
#घोषणा B43_CCK_RATE_1MB		0x02
#घोषणा B43_CCK_RATE_2MB		0x04
#घोषणा B43_CCK_RATE_5MB		0x0B
#घोषणा B43_CCK_RATE_11MB		0x16
#घोषणा B43_OFDM_RATE_6MB		0x0C
#घोषणा B43_OFDM_RATE_9MB		0x12
#घोषणा B43_OFDM_RATE_12MB		0x18
#घोषणा B43_OFDM_RATE_18MB		0x24
#घोषणा B43_OFDM_RATE_24MB		0x30
#घोषणा B43_OFDM_RATE_36MB		0x48
#घोषणा B43_OFDM_RATE_48MB		0x60
#घोषणा B43_OFDM_RATE_54MB		0x6C
/* Convert a b43 rate value to a rate in 100kbps */
#घोषणा B43_RATE_TO_BASE100KBPS(rate)	(((rate) * 10) / 2)

#घोषणा B43_DEFAULT_SHORT_RETRY_LIMIT	7
#घोषणा B43_DEFAULT_LONG_RETRY_LIMIT	4

#घोषणा B43_PHY_TX_BADNESS_LIMIT	1000

/* Max size of a security key */
#घोषणा B43_SEC_KEYSIZE			16
/* Max number of group keys */
#घोषणा B43_NR_GROUP_KEYS		4
/* Max number of pairwise keys */
#घोषणा B43_NR_PAIRWISE_KEYS		50
/* Security algorithms. */
क्रमागत अणु
	B43_SEC_ALGO_NONE = 0,	/* unencrypted, as of TX header. */
	B43_SEC_ALGO_WEP40,
	B43_SEC_ALGO_TKIP,
	B43_SEC_ALGO_AES,
	B43_SEC_ALGO_WEP104,
	B43_SEC_ALGO_AES_LEGACY,
पूर्ण;

काष्ठा b43_dmaring;

/* The firmware file header */
#घोषणा B43_FW_TYPE_UCODE	'u'
#घोषणा B43_FW_TYPE_PCM		'p'
#घोषणा B43_FW_TYPE_IV		'i'
काष्ठा b43_fw_header अणु
	/* File type */
	u8 type;
	/* File क्रमmat version */
	u8 ver;
	u8 __padding[2];
	/* Size of the data. For ucode and PCM this is in bytes.
	 * For IV this is number-of-ivs. */
	__be32 size;
पूर्ण __packed;

/* Initial Value file क्रमmat */
#घोषणा B43_IV_OFFSET_MASK	0x7FFF
#घोषणा B43_IV_32BIT		0x8000
काष्ठा b43_iv अणु
	__be16 offset_size;
	जोड़ अणु
		__be16 d16;
		__be32 d32;
	पूर्ण data __packed;
पूर्ण __packed;


/* Data काष्ठाures क्रम DMA transmission, per 80211 core. */
काष्ठा b43_dma अणु
	काष्ठा b43_dmaring *tx_ring_AC_BK; /* Background */
	काष्ठा b43_dmaring *tx_ring_AC_BE; /* Best Efक्रमt */
	काष्ठा b43_dmaring *tx_ring_AC_VI; /* Video */
	काष्ठा b43_dmaring *tx_ring_AC_VO; /* Voice */
	काष्ठा b43_dmaring *tx_ring_mcast; /* Multicast */

	काष्ठा b43_dmaring *rx_ring;

	u32 translation; /* Routing bits */
	bool translation_in_low; /* Should translation bit go पूर्णांकo low addr? */
	bool parity; /* Check क्रम parity */
पूर्ण;

काष्ठा b43_pio_txqueue;
काष्ठा b43_pio_rxqueue;

/* Data काष्ठाures क्रम PIO transmission, per 80211 core. */
काष्ठा b43_pio अणु
	काष्ठा b43_pio_txqueue *tx_queue_AC_BK; /* Background */
	काष्ठा b43_pio_txqueue *tx_queue_AC_BE; /* Best Efक्रमt */
	काष्ठा b43_pio_txqueue *tx_queue_AC_VI; /* Video */
	काष्ठा b43_pio_txqueue *tx_queue_AC_VO; /* Voice */
	काष्ठा b43_pio_txqueue *tx_queue_mcast; /* Multicast */

	काष्ठा b43_pio_rxqueue *rx_queue;
पूर्ण;

/* Context inक्रमmation क्रम a noise calculation (Link Quality). */
काष्ठा b43_noise_calculation अणु
	bool calculation_running;
	u8 nr_samples;
	s8 samples[8][4];
पूर्ण;

काष्ठा b43_stats अणु
	u8 link_noise;
पूर्ण;

काष्ठा b43_key अणु
	/* If keyconf is शून्य, this key is disabled.
	 * keyconf is a cookie. Don't derefenrence it outside of the set_key
	 * path, because b43 करोesn't own it. */
	काष्ठा ieee80211_key_conf *keyconf;
	u8 algorithm;
पूर्ण;

/* SHM offsets to the QOS data काष्ठाures क्रम the 4 dअगरferent queues. */
#घोषणा B43_QOS_QUEUE_NUM	4
#घोषणा B43_QOS_PARAMS(queue)	(B43_SHM_SH_EDCFQ + \
				 (B43_NR_QOSPARAMS * माप(u16) * (queue)))
#घोषणा B43_QOS_BACKGROUND	B43_QOS_PARAMS(0)
#घोषणा B43_QOS_BESTEFFORT	B43_QOS_PARAMS(1)
#घोषणा B43_QOS_VIDEO		B43_QOS_PARAMS(2)
#घोषणा B43_QOS_VOICE		B43_QOS_PARAMS(3)

/* QOS parameter hardware data काष्ठाure offsets. */
#घोषणा B43_NR_QOSPARAMS	16
क्रमागत अणु
	B43_QOSPARAM_TXOP = 0,
	B43_QOSPARAM_CWMIN,
	B43_QOSPARAM_CWMAX,
	B43_QOSPARAM_CWCUR,
	B43_QOSPARAM_AIFS,
	B43_QOSPARAM_BSLOTS,
	B43_QOSPARAM_REGGAP,
	B43_QOSPARAM_STATUS,
पूर्ण;

/* QOS parameters क्रम a queue. */
काष्ठा b43_qos_params अणु
	/* The QOS parameters */
	काष्ठा ieee80211_tx_queue_params p;
पूर्ण;

काष्ठा b43_wl;

/* The type of the firmware file. */
क्रमागत b43_firmware_file_type अणु
	B43_FWTYPE_PROPRIETARY,
	B43_FWTYPE_OPENSOURCE,
	B43_NR_FWTYPES,
पूर्ण;

/* Context data क्रम fetching firmware. */
काष्ठा b43_request_fw_context अणु
	/* The device we are requesting the fw क्रम. */
	काष्ठा b43_wldev *dev;
	/* a poपूर्णांकer to the firmware object */
	स्थिर काष्ठा firmware *blob;
	/* The type of firmware to request. */
	क्रमागत b43_firmware_file_type req_type;
	/* Error messages क्रम each firmware type. */
	अक्षर errors[B43_NR_FWTYPES][128];
	/* Temporary buffer क्रम storing the firmware name. */
	अक्षर fwname[64];
	/* A fatal error occurred जबतक requesting. Firmware request
	 * can not जारी, as any other request will also fail. */
	पूर्णांक fatal_failure;
पूर्ण;

/* In-memory representation of a cached microcode file. */
काष्ठा b43_firmware_file अणु
	स्थिर अक्षर *filename;
	स्थिर काष्ठा firmware *data;
	/* Type of the firmware file name. Note that this करोes only indicate
	 * the type by the firmware name. NOT the file contents.
	 * If you want to check क्रम proprietary vs खोलोsource, use (काष्ठा b43_firmware)->खोलोsource
	 * instead! The (काष्ठा b43_firmware)->खोलोsource flag is derived from the actual firmware
	 * binary code, not just the filename.
	 */
	क्रमागत b43_firmware_file_type type;
पूर्ण;

क्रमागत b43_firmware_hdr_क्रमmat अणु
	B43_FW_HDR_598,
	B43_FW_HDR_410,
	B43_FW_HDR_351,
पूर्ण;

/* Poपूर्णांकers to the firmware data and meta inक्रमmation about it. */
काष्ठा b43_firmware अणु
	/* Microcode */
	काष्ठा b43_firmware_file ucode;
	/* PCM code */
	काष्ठा b43_firmware_file pcm;
	/* Initial MMIO values क्रम the firmware */
	काष्ठा b43_firmware_file initvals;
	/* Initial MMIO values क्रम the firmware, band-specअगरic */
	काष्ठा b43_firmware_file initvals_band;

	/* Firmware revision */
	u16 rev;
	/* Firmware patchlevel */
	u16 patch;

	/* Format of header used by firmware */
	क्रमागत b43_firmware_hdr_क्रमmat hdr_क्रमmat;

	/* Set to true, अगर we are using an खोलोsource firmware.
	 * Use this to check क्रम proprietary vs खोलोsource. */
	bool खोलोsource;
	/* Set to true, अगर the core needs a PCM firmware, but
	 * we failed to load one. This is always false क्रम
	 * core rev > 10, as these करोn't need PCM firmware. */
	bool pcm_request_failed;
पूर्ण;

क्रमागत b43_band अणु
	B43_BAND_2G = 0,
	B43_BAND_5G_LO = 1,
	B43_BAND_5G_MI = 2,
	B43_BAND_5G_HI = 3,
पूर्ण;

/* Device (802.11 core) initialization status. */
क्रमागत अणु
	B43_STAT_UNINIT = 0,	/* Uninitialized. */
	B43_STAT_INITIALIZED = 1,	/* Initialized, but not started, yet. */
	B43_STAT_STARTED = 2,	/* Up and running. */
पूर्ण;
#घोषणा b43_status(wldev)		atomic_पढ़ो(&(wldev)->__init_status)
#घोषणा b43_set_status(wldev, stat)	करो अणु			\
		atomic_set(&(wldev)->__init_status, (stat));	\
		smp_wmb();					\
					पूर्ण जबतक (0)

/* Data काष्ठाure क्रम one wireless device (802.11 core) */
काष्ठा b43_wldev अणु
	काष्ठा b43_bus_dev *dev;
	काष्ठा b43_wl *wl;
	/* a completion event काष्ठाure needed अगर this call is asynchronous */
	काष्ठा completion fw_load_complete;

	/* The device initialization status.
	 * Use b43_status() to query. */
	atomic_t __init_status;

	bool bad_frames_preempt;	/* Use "Bad Frames Preemption" (शेष off) */
	bool dfq_valid;		/* Directed frame queue valid (IBSS PS mode, ATIM) */
	bool radio_hw_enable;	/* saved state of radio hardware enabled state */
	bool qos_enabled;		/* TRUE, अगर QoS is used. */
	bool hwcrypto_enabled;		/* TRUE, अगर HW crypto acceleration is enabled. */
	bool use_pio;			/* TRUE अगर next init should use PIO */

	/* PHY/Radio device. */
	काष्ठा b43_phy phy;

	जोड़ अणु
		/* DMA engines. */
		काष्ठा b43_dma dma;
		/* PIO engines. */
		काष्ठा b43_pio pio;
	पूर्ण;
	/* Use b43_using_pio_transfers() to check whether we are using
	 * DMA or PIO data transfers. */
	bool __using_pio_transfers;

	/* Various statistics about the physical device. */
	काष्ठा b43_stats stats;

	/* Reason code of the last पूर्णांकerrupt. */
	u32 irq_reason;
	u32 dma_reason[6];
	/* The currently active generic-पूर्णांकerrupt mask. */
	u32 irq_mask;

	/* Link Quality calculation context. */
	काष्ठा b43_noise_calculation noisecalc;
	/* अगर > 0 MAC is suspended. अगर == 0 MAC is enabled. */
	पूर्णांक mac_suspended;

	/* Periodic tasks */
	काष्ठा delayed_work periodic_work;
	अचिन्हित पूर्णांक periodic_state;

	काष्ठा work_काष्ठा restart_work;

	/* encryption/decryption */
	u16 ktp;		/* Key table poपूर्णांकer */
	काष्ठा b43_key key[B43_NR_GROUP_KEYS * 2 + B43_NR_PAIRWISE_KEYS];

	/* Firmware data */
	काष्ठा b43_firmware fw;

	/* Devicelist in काष्ठा b43_wl (all 802.11 cores) */
	काष्ठा list_head list;

	/* Debugging stuff follows. */
#अगर_घोषित CONFIG_B43_DEBUG
	काष्ठा b43_dfsentry *dfsentry;
	अचिन्हित पूर्णांक irq_count;
	अचिन्हित पूर्णांक irq_bit_count[32];
	अचिन्हित पूर्णांक tx_count;
	अचिन्हित पूर्णांक rx_count;
#पूर्ण_अगर
पूर्ण;

/* Data काष्ठाure क्रम the WLAN parts (802.11 cores) of the b43 chip. */
काष्ठा b43_wl अणु
	/* Poपूर्णांकer to the active wireless device on this chip */
	काष्ठा b43_wldev *current_dev;
	/* Poपूर्णांकer to the ieee80211 hardware data काष्ठाure */
	काष्ठा ieee80211_hw *hw;

	/* Global driver mutex. Every operation must run with this mutex locked. */
	काष्ठा mutex mutex;
	/* Hard-IRQ spinlock. This lock protects things used in the hard-IRQ
	 * handler, only. This basically is just the IRQ mask रेजिस्टर. */
	spinlock_t hardirq_lock;

	/* Set this अगर we call ieee80211_रेजिस्टर_hw() and check अगर we call
	 * ieee80211_unरेजिस्टर_hw(). */
	bool hw_रेजिस्टरed;

	/* We can only have one operating पूर्णांकerface (802.11 core)
	 * at a समय. General inक्रमmation about this पूर्णांकerface follows.
	 */

	काष्ठा ieee80211_vअगर *vअगर;
	/* The MAC address of the operating पूर्णांकerface. */
	u8 mac_addr[ETH_ALEN];
	/* Current BSSID */
	u8 bssid[ETH_ALEN];
	/* Interface type. (NL80211_IFTYPE_XXX) */
	पूर्णांक अगर_type;
	/* Is the card operating in AP, STA or IBSS mode? */
	bool operating;
	/* filter flags */
	अचिन्हित पूर्णांक filter_flags;
	/* Stats about the wireless पूर्णांकerface */
	काष्ठा ieee80211_low_level_stats ieee_stats;

#अगर_घोषित CONFIG_B43_HWRNG
	काष्ठा hwrng rng;
	bool rng_initialized;
	अक्षर rng_name[30 + 1];
#पूर्ण_अगर /* CONFIG_B43_HWRNG */

	bool radiotap_enabled;
	bool radio_enabled;

	/* The beacon we are currently using (AP or IBSS mode). */
	काष्ठा sk_buff *current_beacon;
	bool beacon0_uploaded;
	bool beacon1_uploaded;
	bool beacon_ढाँचाs_virgin; /* Never wrote the ढाँचाs? */
	काष्ठा work_काष्ठा beacon_update_trigger;
	spinlock_t beacon_lock;

	/* The current QOS parameters क्रम the 4 queues. */
	काष्ठा b43_qos_params qos_params[B43_QOS_QUEUE_NUM];

	/* Work क्रम adjusपंचांगent of the transmission घातer.
	 * This is scheduled when we determine that the actual TX output
	 * घातer करोesn't match what we want. */
	काष्ठा work_काष्ठा txघातer_adjust_work;

	/* Packet transmit work */
	काष्ठा work_काष्ठा tx_work;

	/* Queue of packets to be transmitted. */
	काष्ठा sk_buff_head tx_queue[B43_QOS_QUEUE_NUM];

	/* Flag that implement the queues stopping. */
	bool tx_queue_stopped[B43_QOS_QUEUE_NUM];

	/* firmware loading work */
	काष्ठा work_काष्ठा firmware_load;

	/* The device LEDs. */
	काष्ठा b43_leds leds;

	/* Kदो_स्मृति'ed scratch space क्रम PIO TX/RX. Protected by wl->mutex. */
	u8 pio_scratchspace[118] __attribute__((__aligned__(8)));
	u8 pio_tailspace[4] __attribute__((__aligned__(8)));
पूर्ण;

अटल अंतरभूत काष्ठा b43_wl *hw_to_b43_wl(काष्ठा ieee80211_hw *hw)
अणु
	वापस hw->priv;
पूर्ण

अटल अंतरभूत काष्ठा b43_wldev *dev_to_b43_wldev(काष्ठा device *dev)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	वापस ssb_get_drvdata(ssb_dev);
पूर्ण

/* Is the device operating in a specअगरied mode (NL80211_IFTYPE_XXX). */
अटल अंतरभूत पूर्णांक b43_is_mode(काष्ठा b43_wl *wl, पूर्णांक type)
अणु
	वापस (wl->operating && wl->अगर_type == type);
पूर्ण

/**
 * b43_current_band - Returns the currently used band.
 * Returns one of NL80211_BAND_2GHZ and NL80211_BAND_5GHZ.
 */
अटल अंतरभूत क्रमागत nl80211_band b43_current_band(काष्ठा b43_wl *wl)
अणु
	वापस wl->hw->conf.chandef.chan->band;
पूर्ण

अटल अंतरभूत पूर्णांक b43_bus_may_घातerकरोwn(काष्ठा b43_wldev *wldev)
अणु
	वापस wldev->dev->bus_may_घातerकरोwn(wldev->dev);
पूर्ण
अटल अंतरभूत पूर्णांक b43_bus_घातerup(काष्ठा b43_wldev *wldev, bool dynamic_pctl)
अणु
	वापस wldev->dev->bus_घातerup(wldev->dev, dynamic_pctl);
पूर्ण
अटल अंतरभूत पूर्णांक b43_device_is_enabled(काष्ठा b43_wldev *wldev)
अणु
	वापस wldev->dev->device_is_enabled(wldev->dev);
पूर्ण
अटल अंतरभूत व्योम b43_device_enable(काष्ठा b43_wldev *wldev,
				     u32 core_specअगरic_flags)
अणु
	wldev->dev->device_enable(wldev->dev, core_specअगरic_flags);
पूर्ण
अटल अंतरभूत व्योम b43_device_disable(काष्ठा b43_wldev *wldev,
				      u32 core_specअगरic_flags)
अणु
	wldev->dev->device_disable(wldev->dev, core_specअगरic_flags);
पूर्ण

अटल अंतरभूत u16 b43_पढ़ो16(काष्ठा b43_wldev *dev, u16 offset)
अणु
	वापस dev->dev->पढ़ो16(dev->dev, offset);
पूर्ण

अटल अंतरभूत व्योम b43_ग_लिखो16(काष्ठा b43_wldev *dev, u16 offset, u16 value)
अणु
	dev->dev->ग_लिखो16(dev->dev, offset, value);
पूर्ण

/* To optimize this check क्रम flush_ग_लिखोs on BCM47XX_BCMA only. */
अटल अंतरभूत व्योम b43_ग_लिखो16f(काष्ठा b43_wldev *dev, u16 offset, u16 value)
अणु
	b43_ग_लिखो16(dev, offset, value);
#अगर defined(CONFIG_BCM47XX_BCMA)
	अगर (dev->dev->flush_ग_लिखोs)
		b43_पढ़ो16(dev, offset);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम b43_maskset16(काष्ठा b43_wldev *dev, u16 offset, u16 mask,
				 u16 set)
अणु
	b43_ग_लिखो16(dev, offset, (b43_पढ़ो16(dev, offset) & mask) | set);
पूर्ण

अटल अंतरभूत u32 b43_पढ़ो32(काष्ठा b43_wldev *dev, u16 offset)
अणु
	वापस dev->dev->पढ़ो32(dev->dev, offset);
पूर्ण

अटल अंतरभूत व्योम b43_ग_लिखो32(काष्ठा b43_wldev *dev, u16 offset, u32 value)
अणु
	dev->dev->ग_लिखो32(dev->dev, offset, value);
पूर्ण

अटल अंतरभूत व्योम b43_maskset32(काष्ठा b43_wldev *dev, u16 offset, u32 mask,
				 u32 set)
अणु
	b43_ग_लिखो32(dev, offset, (b43_पढ़ो32(dev, offset) & mask) | set);
पूर्ण

अटल अंतरभूत व्योम b43_block_पढ़ो(काष्ठा b43_wldev *dev, व्योम *buffer,
				 माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	dev->dev->block_पढ़ो(dev->dev, buffer, count, offset, reg_width);
पूर्ण

अटल अंतरभूत व्योम b43_block_ग_लिखो(काष्ठा b43_wldev *dev, स्थिर व्योम *buffer,
				   माप_प्रकार count, u16 offset, u8 reg_width)
अणु
	dev->dev->block_ग_लिखो(dev->dev, buffer, count, offset, reg_width);
पूर्ण

अटल अंतरभूत bool b43_using_pio_transfers(काष्ठा b43_wldev *dev)
अणु
	वापस dev->__using_pio_transfers;
पूर्ण

/* Message prपूर्णांकing */
__म_लिखो(2, 3) व्योम b43info(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम b43err(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम b43warn(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम b43dbg(काष्ठा b43_wl *wl, स्थिर अक्षर *fmt, ...);


/* A WARN_ON variant that vanishes when b43 debugging is disabled.
 * This _also_ evaluates the arg with debugging disabled. */
#अगर B43_DEBUG
# define B43_WARN_ON(x)	WARN_ON(x)
#अन्यथा
अटल अंतरभूत bool __b43_warn_on_dummy(bool x) अणु वापस x; पूर्ण
# define B43_WARN_ON(x)	__b43_warn_on_dummy(unlikely(!!(x)))
#पूर्ण_अगर

/* Convert an पूर्णांकeger to a Q5.2 value */
#घोषणा INT_TO_Q52(i)	((i) << 2)
/* Convert a Q5.2 value to an पूर्णांकeger (precision loss!) */
#घोषणा Q52_TO_INT(q52)	((q52) >> 2)
/* Macros क्रम prपूर्णांकing a value in Q5.2 क्रमmat */
#घोषणा Q52_FMT		"%u.%u"
#घोषणा Q52_ARG(q52)	Q52_TO_INT(q52), ((((q52) & 0x3) * 100) / 4)

#पूर्ण_अगर /* B43_H_ */
