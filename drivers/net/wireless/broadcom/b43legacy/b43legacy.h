<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43legacy_H_
#घोषणा B43legacy_H_

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/atomic.h>
#समावेश <linux/पन.स>

#समावेश <linux/ssb/ssb.h>
#समावेश <linux/ssb/ssb_driver_chipcommon.h>
#समावेश <linux/completion.h>

#समावेश <net/mac80211.h>

#समावेश "debugfs.h"
#समावेश "leds.h"
#समावेश "rfkill.h"
#समावेश "phy.h"


#घोषणा B43legacy_IRQWAIT_MAX_RETRIES	20

/* MMIO offsets */
#घोषणा B43legacy_MMIO_DMA0_REASON	0x20
#घोषणा B43legacy_MMIO_DMA0_IRQ_MASK	0x24
#घोषणा B43legacy_MMIO_DMA1_REASON	0x28
#घोषणा B43legacy_MMIO_DMA1_IRQ_MASK	0x2C
#घोषणा B43legacy_MMIO_DMA2_REASON	0x30
#घोषणा B43legacy_MMIO_DMA2_IRQ_MASK	0x34
#घोषणा B43legacy_MMIO_DMA3_REASON	0x38
#घोषणा B43legacy_MMIO_DMA3_IRQ_MASK	0x3C
#घोषणा B43legacy_MMIO_DMA4_REASON	0x40
#घोषणा B43legacy_MMIO_DMA4_IRQ_MASK	0x44
#घोषणा B43legacy_MMIO_DMA5_REASON	0x48
#घोषणा B43legacy_MMIO_DMA5_IRQ_MASK	0x4C
#घोषणा B43legacy_MMIO_MACCTL		0x120	/* MAC control */
#घोषणा B43legacy_MMIO_MACCMD		0x124	/* MAC command */
#घोषणा B43legacy_MMIO_GEN_IRQ_REASON	0x128
#घोषणा B43legacy_MMIO_GEN_IRQ_MASK	0x12C
#घोषणा B43legacy_MMIO_RAM_CONTROL	0x130
#घोषणा B43legacy_MMIO_RAM_DATA		0x134
#घोषणा B43legacy_MMIO_PS_STATUS		0x140
#घोषणा B43legacy_MMIO_RADIO_HWENABLED_HI	0x158
#घोषणा B43legacy_MMIO_SHM_CONTROL	0x160
#घोषणा B43legacy_MMIO_SHM_DATA		0x164
#घोषणा B43legacy_MMIO_SHM_DATA_UNALIGNED	0x166
#घोषणा B43legacy_MMIO_XMITSTAT_0		0x170
#घोषणा B43legacy_MMIO_XMITSTAT_1		0x174
#घोषणा B43legacy_MMIO_REV3PLUS_TSF_LOW	0x180 /* core rev >= 3 only */
#घोषणा B43legacy_MMIO_REV3PLUS_TSF_HIGH	0x184 /* core rev >= 3 only */
#घोषणा B43legacy_MMIO_TSF_CFP_REP	0x188
#घोषणा B43legacy_MMIO_TSF_CFP_START	0x18C
/* 32-bit DMA */
#घोषणा B43legacy_MMIO_DMA32_BASE0	0x200
#घोषणा B43legacy_MMIO_DMA32_BASE1	0x220
#घोषणा B43legacy_MMIO_DMA32_BASE2	0x240
#घोषणा B43legacy_MMIO_DMA32_BASE3	0x260
#घोषणा B43legacy_MMIO_DMA32_BASE4	0x280
#घोषणा B43legacy_MMIO_DMA32_BASE5	0x2A0
/* 64-bit DMA */
#घोषणा B43legacy_MMIO_DMA64_BASE0	0x200
#घोषणा B43legacy_MMIO_DMA64_BASE1	0x240
#घोषणा B43legacy_MMIO_DMA64_BASE2	0x280
#घोषणा B43legacy_MMIO_DMA64_BASE3	0x2C0
#घोषणा B43legacy_MMIO_DMA64_BASE4	0x300
#घोषणा B43legacy_MMIO_DMA64_BASE5	0x340
/* PIO */
#घोषणा B43legacy_MMIO_PIO1_BASE		0x300
#घोषणा B43legacy_MMIO_PIO2_BASE		0x310
#घोषणा B43legacy_MMIO_PIO3_BASE		0x320
#घोषणा B43legacy_MMIO_PIO4_BASE		0x330

#घोषणा B43legacy_MMIO_PHY_VER		0x3E0
#घोषणा B43legacy_MMIO_PHY_RADIO		0x3E2
#घोषणा B43legacy_MMIO_PHY0		0x3E6
#घोषणा B43legacy_MMIO_ANTENNA		0x3E8
#घोषणा B43legacy_MMIO_CHANNEL		0x3F0
#घोषणा B43legacy_MMIO_CHANNEL_EXT	0x3F4
#घोषणा B43legacy_MMIO_RADIO_CONTROL	0x3F6
#घोषणा B43legacy_MMIO_RADIO_DATA_HIGH	0x3F8
#घोषणा B43legacy_MMIO_RADIO_DATA_LOW	0x3FA
#घोषणा B43legacy_MMIO_PHY_CONTROL	0x3FC
#घोषणा B43legacy_MMIO_PHY_DATA		0x3FE
#घोषणा B43legacy_MMIO_MACFILTER_CONTROL	0x420
#घोषणा B43legacy_MMIO_MACFILTER_DATA	0x422
#घोषणा B43legacy_MMIO_RCMTA_COUNT	0x43C /* Receive Match Transmitter Addr */
#घोषणा B43legacy_MMIO_RADIO_HWENABLED_LO	0x49A
#घोषणा B43legacy_MMIO_GPIO_CONTROL	0x49C
#घोषणा B43legacy_MMIO_GPIO_MASK		0x49E
#घोषणा B43legacy_MMIO_TSF_CFP_PRETBTT	0x612
#घोषणा B43legacy_MMIO_TSF_0		0x632 /* core rev < 3 only */
#घोषणा B43legacy_MMIO_TSF_1		0x634 /* core rev < 3 only */
#घोषणा B43legacy_MMIO_TSF_2		0x636 /* core rev < 3 only */
#घोषणा B43legacy_MMIO_TSF_3		0x638 /* core rev < 3 only */
#घोषणा B43legacy_MMIO_RNG		0x65A
#घोषणा B43legacy_MMIO_POWERUP_DELAY	0x6A8

/* SPROM boardflags_lo values */
#घोषणा B43legacy_BFL_PACTRL		0x0002
#घोषणा B43legacy_BFL_RSSI		0x0008
#घोषणा B43legacy_BFL_EXTLNA		0x1000

/* GPIO रेजिस्टर offset, in both ChipCommon and PCI core. */
#घोषणा B43legacy_GPIO_CONTROL		0x6c

/* SHM Routing */
#घोषणा	B43legacy_SHM_SHARED		0x0001
#घोषणा	B43legacy_SHM_WIRELESS		0x0002
#घोषणा	B43legacy_SHM_HW		0x0004
#घोषणा	B43legacy_SHM_UCODE		0x0300

/* SHM Routing modअगरiers */
#घोषणा B43legacy_SHM_AUTOINC_R		0x0200 /* Read Auto-increment */
#घोषणा B43legacy_SHM_AUTOINC_W		0x0100 /* Write Auto-increment */
#घोषणा B43legacy_SHM_AUTOINC_RW	(B43legacy_SHM_AUTOINC_R | \
					 B43legacy_SHM_AUTOINC_W)

/* Misc SHM_SHARED offsets */
#घोषणा B43legacy_SHM_SH_WLCOREREV	0x0016 /* 802.11 core revision */
#घोषणा B43legacy_SHM_SH_HOSTFLO	0x005E /* Hostflags ucode opts (low) */
#घोषणा B43legacy_SHM_SH_HOSTFHI	0x0060 /* Hostflags ucode opts (high) */
/* SHM_SHARED crypto engine */
#घोषणा B43legacy_SHM_SH_KEYIDXBLOCK	0x05D4 /* Key index/algorithm block */
/* SHM_SHARED beacon/AP variables */
#घोषणा B43legacy_SHM_SH_DTIMP		0x0012 /* DTIM period */
#घोषणा B43legacy_SHM_SH_BTL0		0x0018 /* Beacon ढाँचा length 0 */
#घोषणा B43legacy_SHM_SH_BTL1		0x001A /* Beacon ढाँचा length 1 */
#घोषणा B43legacy_SHM_SH_BTSFOFF	0x001C /* Beacon TSF offset */
#घोषणा B43legacy_SHM_SH_TIMPOS		0x001E /* TIM position in beacon */
#घोषणा B43legacy_SHM_SH_BEACPHYCTL	0x0054 /* Beacon PHY TX control word */
/* SHM_SHARED ACK/CTS control */
#घोषणा B43legacy_SHM_SH_ACKCTSPHYCTL	0x0022 /* ACK/CTS PHY control word */
/* SHM_SHARED probe response variables */
#घोषणा B43legacy_SHM_SH_PRTLEN		0x004A /* Probe Response ढाँचा length */
#घोषणा B43legacy_SHM_SH_PRMAXTIME	0x0074 /* Probe Response max समय */
#घोषणा B43legacy_SHM_SH_PRPHYCTL	0x0188 /* Probe Resp PHY TX control */
/* SHM_SHARED rate tables */
#घोषणा B43legacy_SHM_SH_OFDMसूचीECT	0x0480 /* Poपूर्णांकer to OFDM direct map */
#घोषणा B43legacy_SHM_SH_OFDMBASIC	0x04A0 /* Poपूर्णांकer to OFDM basic rate map */
#घोषणा B43legacy_SHM_SH_CCKसूचीECT	0x04C0 /* Poपूर्णांकer to CCK direct map */
#घोषणा B43legacy_SHM_SH_CCKBASIC	0x04E0 /* Poपूर्णांकer to CCK basic rate map */
/* SHM_SHARED microcode soft रेजिस्टरs */
#घोषणा B43legacy_SHM_SH_UCODEREV	0x0000 /* Microcode revision */
#घोषणा B43legacy_SHM_SH_UCODEPATCH	0x0002 /* Microcode patchlevel */
#घोषणा B43legacy_SHM_SH_UCODEDATE	0x0004 /* Microcode date */
#घोषणा B43legacy_SHM_SH_UCODETIME	0x0006 /* Microcode समय */
#घोषणा B43legacy_SHM_SH_SPUWKUP	0x0094 /* pre-wakeup क्रम synth PU in us */
#घोषणा B43legacy_SHM_SH_PRETBTT	0x0096 /* pre-TBTT in us */

#घोषणा B43legacy_UCODEFLAGS_OFFSET     0x005E

/* Hardware Radio Enable masks */
#घोषणा B43legacy_MMIO_RADIO_HWENABLED_HI_MASK (1 << 16)
#घोषणा B43legacy_MMIO_RADIO_HWENABLED_LO_MASK (1 << 4)

/* HostFlags. See b43legacy_hf_पढ़ो/ग_लिखो() */
#घोषणा B43legacy_HF_SYMW		0x00000002 /* G-PHY SYM workaround */
#घोषणा B43legacy_HF_GDCW		0x00000020 /* G-PHY DV cancel filter */
#घोषणा B43legacy_HF_OFDMPABOOST	0x00000040 /* Enable PA boost OFDM */
#घोषणा B43legacy_HF_EDCF		0x00000100 /* on अगर WME/MAC suspended */

/* MacFilter offsets. */
#घोषणा B43legacy_MACFILTER_SELF	0x0000
#घोषणा B43legacy_MACFILTER_BSSID	0x0003
#घोषणा B43legacy_MACFILTER_MAC		0x0010

/* PHYVersioning */
#घोषणा B43legacy_PHYTYPE_B		0x01
#घोषणा B43legacy_PHYTYPE_G		0x02

/* PHYRegisters */
#घोषणा B43legacy_PHY_G_LO_CONTROL	0x0810
#घोषणा B43legacy_PHY_ILT_G_CTRL	0x0472
#घोषणा B43legacy_PHY_ILT_G_DATA1	0x0473
#घोषणा B43legacy_PHY_ILT_G_DATA2	0x0474
#घोषणा B43legacy_PHY_G_PCTL		0x0029
#घोषणा B43legacy_PHY_RADIO_BITFIELD	0x0401
#घोषणा B43legacy_PHY_G_CRS		0x0429
#घोषणा B43legacy_PHY_NRSSILT_CTRL	0x0803
#घोषणा B43legacy_PHY_NRSSILT_DATA	0x0804

/* RadioRegisters */
#घोषणा B43legacy_RADIOCTL_ID		0x01

/* MAC Control bitfield */
#घोषणा B43legacy_MACCTL_ENABLED	0x00000001 /* MAC Enabled */
#घोषणा B43legacy_MACCTL_PSM_RUN	0x00000002 /* Run Microcode */
#घोषणा B43legacy_MACCTL_PSM_JMP0	0x00000004 /* Microcode jump to 0 */
#घोषणा B43legacy_MACCTL_SHM_ENABLED	0x00000100 /* SHM Enabled */
#घोषणा B43legacy_MACCTL_IHR_ENABLED	0x00000400 /* IHR Region Enabled */
#घोषणा B43legacy_MACCTL_BE		0x00010000 /* Big Endian mode */
#घोषणा B43legacy_MACCTL_INFRA		0x00020000 /* Infraकाष्ठाure mode */
#घोषणा B43legacy_MACCTL_AP		0x00040000 /* AccessPoपूर्णांक mode */
#घोषणा B43legacy_MACCTL_RADIOLOCK	0x00080000 /* Radio lock */
#घोषणा B43legacy_MACCTL_BEACPROMISC	0x00100000 /* Beacon Promiscuous */
#घोषणा B43legacy_MACCTL_KEEP_BADPLCP	0x00200000 /* Keep bad PLCP frames */
#घोषणा B43legacy_MACCTL_KEEP_CTL	0x00400000 /* Keep control frames */
#घोषणा B43legacy_MACCTL_KEEP_BAD	0x00800000 /* Keep bad frames (FCS) */
#घोषणा B43legacy_MACCTL_PROMISC	0x01000000 /* Promiscuous mode */
#घोषणा B43legacy_MACCTL_HWPS		0x02000000 /* Hardware Power Saving */
#घोषणा B43legacy_MACCTL_AWAKE		0x04000000 /* Device is awake */
#घोषणा B43legacy_MACCTL_TBTTHOLD	0x10000000 /* TBTT Hold */
#घोषणा B43legacy_MACCTL_GMODE		0x80000000 /* G Mode */

/* MAC Command bitfield */
#घोषणा B43legacy_MACCMD_BEACON0_VALID	0x00000001 /* Beacon 0 in ढाँचा RAM is busy/valid */
#घोषणा B43legacy_MACCMD_BEACON1_VALID	0x00000002 /* Beacon 1 in ढाँचा RAM is busy/valid */
#घोषणा B43legacy_MACCMD_DFQ_VALID	0x00000004 /* Directed frame queue valid (IBSS PS mode, ATIM) */
#घोषणा B43legacy_MACCMD_CCA		0x00000008 /* Clear channel assessment */
#घोषणा B43legacy_MACCMD_BGNOISE	0x00000010 /* Background noise */

/* 802.11 core specअगरic TM State Low flags */
#घोषणा B43legacy_TMSLOW_GMODE		0x20000000 /* G Mode Enable */
#घोषणा B43legacy_TMSLOW_PLLREFSEL	0x00200000 /* PLL Freq Ref Select */
#घोषणा B43legacy_TMSLOW_MACPHYCLKEN	0x00100000 /* MAC PHY Clock Ctrl Enbl */
#घोषणा B43legacy_TMSLOW_PHYRESET	0x00080000 /* PHY Reset */
#घोषणा B43legacy_TMSLOW_PHYCLKEN	0x00040000 /* PHY Clock Enable */

/* 802.11 core specअगरic TM State High flags */
#घोषणा B43legacy_TMSHIGH_FCLOCK	0x00040000 /* Fast Clock Available */
#घोषणा B43legacy_TMSHIGH_GPHY		0x00010000 /* G-PHY avail (rev >= 5) */

#घोषणा B43legacy_UCODEFLAG_AUTODIV       0x0001

/* Generic-Interrupt reasons. */
#घोषणा B43legacy_IRQ_MAC_SUSPENDED	0x00000001
#घोषणा B43legacy_IRQ_BEACON		0x00000002
#घोषणा B43legacy_IRQ_TBTT_INDI		0x00000004 /* Target Beacon Transmit Time */
#घोषणा B43legacy_IRQ_BEACON_TX_OK	0x00000008
#घोषणा B43legacy_IRQ_BEACON_CANCEL	0x00000010
#घोषणा B43legacy_IRQ_ATIM_END		0x00000020
#घोषणा B43legacy_IRQ_PMQ		0x00000040
#घोषणा B43legacy_IRQ_PIO_WORKAROUND	0x00000100
#घोषणा B43legacy_IRQ_MAC_TXERR		0x00000200
#घोषणा B43legacy_IRQ_PHY_TXERR		0x00000800
#घोषणा B43legacy_IRQ_PMEVENT		0x00001000
#घोषणा B43legacy_IRQ_TIMER0		0x00002000
#घोषणा B43legacy_IRQ_TIMER1		0x00004000
#घोषणा B43legacy_IRQ_DMA		0x00008000
#घोषणा B43legacy_IRQ_TXFIFO_FLUSH_OK	0x00010000
#घोषणा B43legacy_IRQ_CCA_MEASURE_OK	0x00020000
#घोषणा B43legacy_IRQ_NOISESAMPLE_OK	0x00040000
#घोषणा B43legacy_IRQ_UCODE_DEBUG	0x08000000
#घोषणा B43legacy_IRQ_RFKILL		0x10000000
#घोषणा B43legacy_IRQ_TX_OK		0x20000000
#घोषणा B43legacy_IRQ_PHY_G_CHANGED	0x40000000
#घोषणा B43legacy_IRQ_TIMEOUT		0x80000000

#घोषणा B43legacy_IRQ_ALL		0xFFFFFFFF
#घोषणा B43legacy_IRQ_MASKTEMPLATE	(B43legacy_IRQ_MAC_SUSPENDED |	\
					 B43legacy_IRQ_TBTT_INDI |	\
					 B43legacy_IRQ_ATIM_END |	\
					 B43legacy_IRQ_PMQ |		\
					 B43legacy_IRQ_MAC_TXERR |	\
					 B43legacy_IRQ_PHY_TXERR |	\
					 B43legacy_IRQ_DMA |		\
					 B43legacy_IRQ_TXFIFO_FLUSH_OK | \
					 B43legacy_IRQ_NOISESAMPLE_OK | \
					 B43legacy_IRQ_UCODE_DEBUG |	\
					 B43legacy_IRQ_RFKILL |		\
					 B43legacy_IRQ_TX_OK)

/* Device specअगरic rate values.
 * The actual values defined here are (rate_in_mbps * 2).
 * Some code depends on this. Don't change it. */
#घोषणा B43legacy_CCK_RATE_1MB		2
#घोषणा B43legacy_CCK_RATE_2MB		4
#घोषणा B43legacy_CCK_RATE_5MB		11
#घोषणा B43legacy_CCK_RATE_11MB		22
#घोषणा B43legacy_OFDM_RATE_6MB		12
#घोषणा B43legacy_OFDM_RATE_9MB		18
#घोषणा B43legacy_OFDM_RATE_12MB	24
#घोषणा B43legacy_OFDM_RATE_18MB	36
#घोषणा B43legacy_OFDM_RATE_24MB	48
#घोषणा B43legacy_OFDM_RATE_36MB	72
#घोषणा B43legacy_OFDM_RATE_48MB	96
#घोषणा B43legacy_OFDM_RATE_54MB	108
/* Convert a b43legacy rate value to a rate in 100kbps */
#घोषणा B43legacy_RATE_TO_100KBPS(rate)	(((rate) * 10) / 2)


#घोषणा B43legacy_DEFAULT_SHORT_RETRY_LIMIT	7
#घोषणा B43legacy_DEFAULT_LONG_RETRY_LIMIT	4

#घोषणा B43legacy_PHY_TX_BADNESS_LIMIT		1000

/* Max size of a security key */
#घोषणा B43legacy_SEC_KEYSIZE		16
/* Security algorithms. */
क्रमागत अणु
	B43legacy_SEC_ALGO_NONE = 0, /* unencrypted, as of TX header. */
	B43legacy_SEC_ALGO_WEP40,
	B43legacy_SEC_ALGO_TKIP,
	B43legacy_SEC_ALGO_AES,
	B43legacy_SEC_ALGO_WEP104,
	B43legacy_SEC_ALGO_AES_LEGACY,
पूर्ण;

/* Core Inक्रमmation Registers */
#घोषणा B43legacy_CIR_BASE                0xf00
#घोषणा B43legacy_CIR_SBTPSFLAG           (B43legacy_CIR_BASE + 0x18)
#घोषणा B43legacy_CIR_SBIMSTATE           (B43legacy_CIR_BASE + 0x90)
#घोषणा B43legacy_CIR_SBINTVEC            (B43legacy_CIR_BASE + 0x94)
#घोषणा B43legacy_CIR_SBTMSTATELOW        (B43legacy_CIR_BASE + 0x98)
#घोषणा B43legacy_CIR_SBTMSTATEHIGH       (B43legacy_CIR_BASE + 0x9c)
#घोषणा B43legacy_CIR_SBIMCONFIGLOW       (B43legacy_CIR_BASE + 0xa8)
#घोषणा B43legacy_CIR_SB_ID_HI            (B43legacy_CIR_BASE + 0xfc)

/* sbपंचांगstatehigh state flags */
#घोषणा B43legacy_SBTMSTATEHIGH_SERROR		0x00000001
#घोषणा B43legacy_SBTMSTATEHIGH_BUSY		0x00000004
#घोषणा B43legacy_SBTMSTATEHIGH_TIMEOUT		0x00000020
#घोषणा B43legacy_SBTMSTATEHIGH_G_PHY_AVAIL	0x00010000
#घोषणा B43legacy_SBTMSTATEHIGH_COREFLAGS	0x1FFF0000
#घोषणा B43legacy_SBTMSTATEHIGH_DMA64BIT	0x10000000
#घोषणा B43legacy_SBTMSTATEHIGH_GATEDCLK	0x20000000
#घोषणा B43legacy_SBTMSTATEHIGH_BISTFAILED	0x40000000
#घोषणा B43legacy_SBTMSTATEHIGH_BISTCOMPLETE	0x80000000

/* sbimstate flags */
#घोषणा B43legacy_SBIMSTATE_IB_ERROR		0x20000
#घोषणा B43legacy_SBIMSTATE_TIMEOUT		0x40000

#घोषणा PFX		KBUILD_MODNAME ": "
#अगर_घोषित निश्चित
# undef निश्चित
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43LEGACY_DEBUG
# define B43legacy_WARN_ON(x)	WARN_ON(x)
# define B43legacy_BUG_ON(expr)						\
	करो अणु								\
		अगर (unlikely((expr))) अणु					\
			prपूर्णांकk(KERN_INFO PFX "Test (%s) failed\n",	\
					      #expr);			\
			BUG_ON(expr);					\
		पूर्ण							\
	पूर्ण जबतक (0)
# define B43legacy_DEBUG	1
#अन्यथा
/* This will evaluate the argument even अगर debugging is disabled. */
अटल अंतरभूत bool __b43legacy_warn_on_dummy(bool x) अणु वापस x; पूर्ण
# define B43legacy_WARN_ON(x)	__b43legacy_warn_on_dummy(unlikely(!!(x)))
# define B43legacy_BUG_ON(x)	करो अणु /* nothing */ पूर्ण जबतक (0)
# define B43legacy_DEBUG	0
#पूर्ण_अगर


काष्ठा net_device;
काष्ठा pci_dev;
काष्ठा b43legacy_dmaring;
काष्ठा b43legacy_pioqueue;

/* The firmware file header */
#घोषणा B43legacy_FW_TYPE_UCODE	'u'
#घोषणा B43legacy_FW_TYPE_PCM	'p'
#घोषणा B43legacy_FW_TYPE_IV	'i'
काष्ठा b43legacy_fw_header अणु
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
#घोषणा B43legacy_IV_OFFSET_MASK	0x7FFF
#घोषणा B43legacy_IV_32BIT		0x8000
काष्ठा b43legacy_iv अणु
	__be16 offset_size;
	जोड़ अणु
		__be16 d16;
		__be32 d32;
	पूर्ण data __packed;
पूर्ण __packed;

#घोषणा B43legacy_PHYMODE(phytype)	(1 << (phytype))
#घोषणा B43legacy_PHYMODE_B		B43legacy_PHYMODE	\
					((B43legacy_PHYTYPE_B))
#घोषणा B43legacy_PHYMODE_G		B43legacy_PHYMODE	\
					((B43legacy_PHYTYPE_G))

/* Value pair to measure the LocalOscillator. */
काष्ठा b43legacy_lopair अणु
	s8 low;
	s8 high;
	u8 used:1;
पूर्ण;
#घोषणा B43legacy_LO_COUNT	(14*4)

काष्ठा b43legacy_phy अणु
	/* Possible PHYMODEs on this PHY */
	u8 possible_phymodes;
	/* GMODE bit enabled in MACCTL? */
	bool gmode;

	/* Analog Type */
	u8 analog;
	/* B43legacy_PHYTYPE_ */
	u8 type;
	/* PHY revision number. */
	u8 rev;

	u16 antenna_भागersity;
	u16 savedpctlreg;
	/* Radio versioning */
	u16 radio_manuf;	/* Radio manufacturer */
	u16 radio_ver;		/* Radio version */
	u8 calibrated:1;
	u8 radio_rev;		/* Radio revision */

	bool dyn_tssi_tbl;	/* tssi2dbm is kदो_स्मृति()ed. */

	/* ACI (adjacent channel पूर्णांकerference) flags. */
	bool aci_enable;
	bool aci_wlan_स्वतःmatic;
	bool aci_hw_rssi;

	/* Radio चयनed on/off */
	bool radio_on;
	काष्ठा अणु
		/* Values saved when turning the radio off.
		 * They are needed when turning it on again. */
		bool valid;
		u16 rfover;
		u16 rfoverval;
	पूर्ण radio_off_context;

	u16 minlowsig[2];
	u16 minlowsigpos[2];

	/* LO Measurement Data.
	 * Use b43legacy_get_lopair() to get a value.
	 */
	काष्ठा b43legacy_lopair *_lo_pairs;
	/* TSSI to dBm table in use */
	स्थिर s8 *tssi2dbm;
	/* idle TSSI value */
	s8 idle_tssi;
	/* Target idle TSSI */
	पूर्णांक tgt_idle_tssi;
	/* Current idle TSSI */
	पूर्णांक cur_idle_tssi;

	/* LocalOscillator control values. */
	काष्ठा b43legacy_txघातer_lo_control *lo_control;
	/* Values from b43legacy_calc_loopback_gain() */
	s16 max_lb_gain;	/* Maximum Loopback gain in hdB */
	s16 trsw_rx_gain;	/* TRSW RX gain in hdB */
	s16 lna_lod_gain;	/* LNA lod */
	s16 lna_gain;		/* LNA */
	s16 pga_gain;		/* PGA */

	/* Desired TX घातer level (in dBm). This is set by the user and
	 * adjusted in b43legacy_phy_xmitघातer(). */
	u8 घातer_level;

	/* Values from b43legacy_calc_loopback_gain() */
	u16 loopback_gain[2];

	/* TX Power control values. */
	/* B/G PHY */
	काष्ठा अणु
		/* Current Radio Attenuation क्रम TXघातer recalculation. */
		u16 rfatt;
		/* Current Baseband Attenuation क्रम TXघातer recalculation. */
		u16 bbatt;
		/* Current TXघातer control value क्रम TXघातer recalculation. */
		u16 txctl1;
		u16 txctl2;
	पूर्ण;
	/* A PHY */
	काष्ठा अणु
		u16 txpwr_offset;
	पूर्ण;

	/* Current Interference Mitigation mode */
	पूर्णांक पूर्णांकerभ_शेषe;
	/* Stack of saved values from the Interference Mitigation code.
	 * Each value in the stack is laid out as follows:
	 * bit 0-11:  offset
	 * bit 12-15: रेजिस्टर ID
	 * bit 16-32: value
	 * रेजिस्टर ID is: 0x1 PHY, 0x2 Radio, 0x3 ILT
	 */
#घोषणा B43legacy_INTERFSTACK_SIZE	26
	u32 पूर्णांकerfstack[B43legacy_INTERFSTACK_SIZE];

	/* Saved values from the NRSSI Slope calculation */
	s16 nrssi[2];
	s32 nrssislope;
	/* In memory nrssi lookup table. */
	s8 nrssi_lt[64];

	/* current channel */
	u8 channel;

	u16 lofcal;

	u16 initval;

	/* PHY TX errors counter. */
	atomic_t txerr_cnt;

#अगर B43legacy_DEBUG
	/* Manual TX-घातer control enabled? */
	bool manual_txघातer_control;
	/* PHY रेजिस्टरs locked by b43legacy_phy_lock()? */
	bool phy_locked;
#पूर्ण_अगर /* B43legacy_DEBUG */
पूर्ण;

/* Data काष्ठाures क्रम DMA transmission, per 80211 core. */
काष्ठा b43legacy_dma अणु
	काष्ठा b43legacy_dmaring *tx_ring0;
	काष्ठा b43legacy_dmaring *tx_ring1;
	काष्ठा b43legacy_dmaring *tx_ring2;
	काष्ठा b43legacy_dmaring *tx_ring3;
	काष्ठा b43legacy_dmaring *tx_ring4;
	काष्ठा b43legacy_dmaring *tx_ring5;

	काष्ठा b43legacy_dmaring *rx_ring0;
	काष्ठा b43legacy_dmaring *rx_ring3; /* only on core.rev < 5 */

	u32 translation; /* Routing bits */
पूर्ण;

/* Data काष्ठाures क्रम PIO transmission, per 80211 core. */
काष्ठा b43legacy_pio अणु
	काष्ठा b43legacy_pioqueue *queue0;
	काष्ठा b43legacy_pioqueue *queue1;
	काष्ठा b43legacy_pioqueue *queue2;
	काष्ठा b43legacy_pioqueue *queue3;
पूर्ण;

/* Context inक्रमmation क्रम a noise calculation (Link Quality). */
काष्ठा b43legacy_noise_calculation अणु
	u8 channel_at_start;
	bool calculation_running;
	u8 nr_samples;
	s8 samples[8][4];
पूर्ण;

काष्ठा b43legacy_stats अणु
	u8 link_noise;
	/* Store the last TX/RX बार here क्रम updating the leds. */
	अचिन्हित दीर्घ last_tx;
	अचिन्हित दीर्घ last_rx;
पूर्ण;

काष्ठा b43legacy_key अणु
	व्योम *keyconf;
	bool enabled;
	u8 algorithm;
पूर्ण;

#घोषणा B43legacy_QOS_QUEUE_NUM	4

काष्ठा b43legacy_wldev;

/* QOS parameters क्रम a queue. */
काष्ठा b43legacy_qos_params अणु
	/* The QOS parameters */
	काष्ठा ieee80211_tx_queue_params p;
पूर्ण;

/* Data काष्ठाure क्रम the WLAN parts (802.11 cores) of the b43legacy chip. */
काष्ठा b43legacy_wl अणु
	/* Poपूर्णांकer to the active wireless device on this chip */
	काष्ठा b43legacy_wldev *current_dev;
	/* Poपूर्णांकer to the ieee80211 hardware data काष्ठाure */
	काष्ठा ieee80211_hw *hw;

	spinlock_t irq_lock;		/* locks IRQ */
	काष्ठा mutex mutex;		/* locks wireless core state */
	spinlock_t leds_lock;		/* lock क्रम leds */

	/* firmware loading work */
	काष्ठा work_काष्ठा firmware_load;

	/* We can only have one operating पूर्णांकerface (802.11 core)
	 * at a समय. General inक्रमmation about this पूर्णांकerface follows.
	 */

	काष्ठा ieee80211_vअगर *vअगर;
	/* MAC address (can be शून्य). */
	u8 mac_addr[ETH_ALEN];
	/* Current BSSID (can be शून्य). */
	u8 bssid[ETH_ALEN];
	/* Interface type. (IEEE80211_IF_TYPE_XXX) */
	पूर्णांक अगर_type;
	/* Is the card operating in AP, STA or IBSS mode? */
	bool operating;
	/* filter flags */
	अचिन्हित पूर्णांक filter_flags;
	/* Stats about the wireless पूर्णांकerface */
	काष्ठा ieee80211_low_level_stats ieee_stats;

#अगर_घोषित CONFIG_B43LEGACY_HWRNG
	काष्ठा hwrng rng;
	u8 rng_initialized;
	अक्षर rng_name[30 + 1];
#पूर्ण_अगर

	/* List of all wireless devices on this chip */
	काष्ठा list_head devlist;
	u8 nr_devs;

	bool radiotap_enabled;
	bool radio_enabled;

	/* The beacon we are currently using (AP or IBSS mode).
	 * This beacon stuff is रक्षित by the irq_lock. */
	काष्ठा sk_buff *current_beacon;
	bool beacon0_uploaded;
	bool beacon1_uploaded;
	bool beacon_ढाँचाs_virgin; /* Never wrote the ढाँचाs? */
	काष्ठा work_काष्ठा beacon_update_trigger;
	/* The current QOS parameters क्रम the 4 queues. */
	काष्ठा b43legacy_qos_params qos_params[B43legacy_QOS_QUEUE_NUM];

	/* Packet transmit work */
	काष्ठा work_काष्ठा tx_work;

	/* Queue of packets to be transmitted. */
	काष्ठा sk_buff_head tx_queue[B43legacy_QOS_QUEUE_NUM];

	/* Flag that implement the queues stopping. */
	bool tx_queue_stopped[B43legacy_QOS_QUEUE_NUM];

पूर्ण;

/* Poपूर्णांकers to the firmware data and meta inक्रमmation about it. */
काष्ठा b43legacy_firmware अणु
	/* Microcode */
	स्थिर काष्ठा firmware *ucode;
	/* PCM code */
	स्थिर काष्ठा firmware *pcm;
	/* Initial MMIO values क्रम the firmware */
	स्थिर काष्ठा firmware *initvals;
	/* Initial MMIO values क्रम the firmware, band-specअगरic */
	स्थिर काष्ठा firmware *initvals_band;
	/* Firmware revision */
	u16 rev;
	/* Firmware patchlevel */
	u16 patch;
पूर्ण;

/* Device (802.11 core) initialization status. */
क्रमागत अणु
	B43legacy_STAT_UNINIT		= 0, /* Uninitialized. */
	B43legacy_STAT_INITIALIZED	= 1, /* Initialized, not yet started. */
	B43legacy_STAT_STARTED	= 2, /* Up and running. */
पूर्ण;
#घोषणा b43legacy_status(wldev)	atomic_पढ़ो(&(wldev)->__init_status)
#घोषणा b43legacy_set_status(wldev, stat)	करो अणु		\
		atomic_set(&(wldev)->__init_status, (stat));	\
		smp_wmb();					\
					पूर्ण जबतक (0)

/* *** ---   HOW LOCKING WORKS IN B43legacy   --- ***
 *
 * You should always acquire both, wl->mutex and wl->irq_lock unless:
 * - You करोn't need to acquire wl->irq_lock, अगर the पूर्णांकerface is stopped.
 * - You करोn't need to acquire wl->mutex in the IRQ handler, IRQ tasklet
 *   and packet TX path (and _ONLY_ there.)
 */

/* Data काष्ठाure क्रम one wireless device (802.11 core) */
काष्ठा b43legacy_wldev अणु
	काष्ठा ssb_device *dev;
	काष्ठा b43legacy_wl *wl;

	/* The device initialization status.
	 * Use b43legacy_status() to query. */
	atomic_t __init_status;
	/* Saved init status क्रम handling suspend. */
	पूर्णांक suspend_init_status;

	bool __using_pio;	/* Using pio rather than dma. */
	bool bad_frames_preempt;/* Use "Bad Frames Preemption". */
	bool dfq_valid;		/* Directed frame queue valid (IBSS PS mode, ATIM). */
	bool लघु_preamble;	/* TRUE अगर using लघु preamble. */
	bool radio_hw_enable;	/* State of radio hardware enable bit. */

	/* PHY/Radio device. */
	काष्ठा b43legacy_phy phy;
	जोड़ अणु
		/* DMA engines. */
		काष्ठा b43legacy_dma dma;
		/* PIO engines. */
		काष्ठा b43legacy_pio pio;
	पूर्ण;

	/* Various statistics about the physical device. */
	काष्ठा b43legacy_stats stats;

	/* The device LEDs. */
	काष्ठा b43legacy_led led_tx;
	काष्ठा b43legacy_led led_rx;
	काष्ठा b43legacy_led led_assoc;
	काष्ठा b43legacy_led led_radio;

	/* Reason code of the last पूर्णांकerrupt. */
	u32 irq_reason;
	u32 dma_reason[6];
	/* The currently active generic-पूर्णांकerrupt mask. */
	u32 irq_mask;
	/* Link Quality calculation context. */
	काष्ठा b43legacy_noise_calculation noisecalc;
	/* अगर > 0 MAC is suspended. अगर == 0 MAC is enabled. */
	पूर्णांक mac_suspended;

	/* Interrupt Service Routine tasklet (bottom-half) */
	काष्ठा tasklet_काष्ठा isr_tasklet;

	/* Periodic tasks */
	काष्ठा delayed_work periodic_work;
	अचिन्हित पूर्णांक periodic_state;

	काष्ठा work_काष्ठा restart_work;

	/* encryption/decryption */
	u16 ktp; /* Key table poपूर्णांकer */
	u8 max_nr_keys;
	काष्ठा b43legacy_key key[58];

	/* Firmware data */
	काष्ठा b43legacy_firmware fw;
	स्थिर काष्ठा firmware *fwp;	/* needed to pass fw poपूर्णांकer */

	/* completion काष्ठा क्रम firmware loading */
	काष्ठा completion fw_load_complete;

	/* Devicelist in काष्ठा b43legacy_wl (all 802.11 cores) */
	काष्ठा list_head list;

	/* Debugging stuff follows. */
#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	काष्ठा b43legacy_dfsentry *dfsentry;
#पूर्ण_अगर
पूर्ण;


अटल अंतरभूत
काष्ठा b43legacy_wl *hw_to_b43legacy_wl(काष्ठा ieee80211_hw *hw)
अणु
	वापस hw->priv;
पूर्ण

/* Helper function, which वापसs a boolean.
 * TRUE, अगर PIO is used; FALSE, अगर DMA is used.
 */
#अगर defined(CONFIG_B43LEGACY_DMA) && defined(CONFIG_B43LEGACY_PIO)
अटल अंतरभूत
पूर्णांक b43legacy_using_pio(काष्ठा b43legacy_wldev *dev)
अणु
	वापस dev->__using_pio;
पूर्ण
#या_अगर defined(CONFIG_B43LEGACY_DMA)
अटल अंतरभूत
पूर्णांक b43legacy_using_pio(काष्ठा b43legacy_wldev *dev)
अणु
	वापस 0;
पूर्ण
#या_अगर defined(CONFIG_B43LEGACY_PIO)
अटल अंतरभूत
पूर्णांक b43legacy_using_pio(काष्ठा b43legacy_wldev *dev)
अणु
	वापस 1;
पूर्ण
#अन्यथा
# error "Using neither DMA nor PIO? Confused..."
#पूर्ण_अगर


अटल अंतरभूत
काष्ठा b43legacy_wldev *dev_to_b43legacy_wldev(काष्ठा device *dev)
अणु
	काष्ठा ssb_device *ssb_dev = dev_to_ssb_dev(dev);
	वापस ssb_get_drvdata(ssb_dev);
पूर्ण

/* Is the device operating in a specअगरied mode (IEEE80211_IF_TYPE_XXX). */
अटल अंतरभूत
पूर्णांक b43legacy_is_mode(काष्ठा b43legacy_wl *wl, पूर्णांक type)
अणु
	वापस (wl->operating &&
		wl->अगर_type == type);
पूर्ण

अटल अंतरभूत
bool is_bcm_board_venकरोr(काष्ठा b43legacy_wldev *dev)
अणु
	वापस  (dev->dev->bus->boardinfo.venकरोr == PCI_VENDOR_ID_BROADCOM);
पूर्ण

अटल अंतरभूत
u16 b43legacy_पढ़ो16(काष्ठा b43legacy_wldev *dev, u16 offset)
अणु
	वापस ssb_पढ़ो16(dev->dev, offset);
पूर्ण

अटल अंतरभूत
व्योम b43legacy_ग_लिखो16(काष्ठा b43legacy_wldev *dev, u16 offset, u16 value)
अणु
	ssb_ग_लिखो16(dev->dev, offset, value);
पूर्ण

अटल अंतरभूत
u32 b43legacy_पढ़ो32(काष्ठा b43legacy_wldev *dev, u16 offset)
अणु
	वापस ssb_पढ़ो32(dev->dev, offset);
पूर्ण

अटल अंतरभूत
व्योम b43legacy_ग_लिखो32(काष्ठा b43legacy_wldev *dev, u16 offset, u32 value)
अणु
	ssb_ग_लिखो32(dev->dev, offset, value);
पूर्ण

अटल अंतरभूत
काष्ठा b43legacy_lopair *b43legacy_get_lopair(काष्ठा b43legacy_phy *phy,
					      u16 radio_attenuation,
					      u16 baseband_attenuation)
अणु
	वापस phy->_lo_pairs + (radio_attenuation
			+ 14 * (baseband_attenuation / 2));
पूर्ण



/* Message prपूर्णांकing */
__म_लिखो(2, 3)
व्योम b43legacyinfo(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम b43legacyerr(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम b43legacywarn(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...);
#अगर B43legacy_DEBUG
__म_लिखो(2, 3)
व्योम b43legacydbg(काष्ठा b43legacy_wl *wl, स्थिर अक्षर *fmt, ...);
#अन्यथा /* DEBUG */
# define b43legacydbg(wl, fmt...) करो अणु /* nothing */ पूर्ण जबतक (0)
#पूर्ण_अगर /* DEBUG */

/* Macros क्रम prपूर्णांकing a value in Q5.2 क्रमmat */
#घोषणा Q52_FMT		"%u.%u"
#घोषणा Q52_ARG(q52)	((q52) / 4), (((q52) & 3) * 100 / 4)

#पूर्ण_अगर /* B43legacy_H_ */
