<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) Freescale Semicondutor, Inc. 2006-2009. All rights reserved.
 *
 * Author: Shlomi Gridish <gridish@मुक्तscale.com>
 *
 * Description:
 * Internal header file क्रम UCC Gigabit Ethernet unit routines.
 *
 * Changelog:
 * Jun 28, 2006 Li Yang <LeoLi@मुक्तscale.com>
 * - Rearrange code and style fixes
 */
#अगर_अघोषित __UCC_GETH_H__
#घोषणा __UCC_GETH_H__

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/अगर_ether.h>

#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <soc/fsl/qe/ucc.h>
#समावेश <soc/fsl/qe/ucc_fast.h>

#घोषणा DRV_DESC "QE UCC Gigabit Ethernet Controller"
#घोषणा DRV_NAME "ucc_geth"

#घोषणा NUM_TX_QUEUES                   8
#घोषणा NUM_RX_QUEUES                   8
#घोषणा NUM_BDS_IN_PREFETCHED_BDS       4
#घोषणा TX_IP_OFFSET_ENTRY_MAX          8
#घोषणा NUM_OF_PADDRS                   4
#घोषणा ENET_INIT_PARAM_MAX_ENTRIES_RX  9
#घोषणा ENET_INIT_PARAM_MAX_ENTRIES_TX  8

काष्ठा ucc_geth अणु
	काष्ठा ucc_fast uccf;
	u8 res0[0x100 - माप(काष्ठा ucc_fast)];

	u32 maccfg1;		/* mac configuration reg. 1 */
	u32 maccfg2;		/* mac configuration reg. 2 */
	u32 ipgअगरg;		/* पूर्णांकerframe gap reg.  */
	u32 hafdup;		/* half-duplex reg.  */
	u8 res1[0x10];
	u8 miimng[0x18];	/* MII management काष्ठाure moved to _mii.h */
	u32 अगरctl;		/* पूर्णांकerface control reg */
	u32 अगरstat;		/* पूर्णांकerface statux reg */
	u32 macstnaddr1;	/* mac station address part 1 reg */
	u32 macstnaddr2;	/* mac station address part 2 reg */
	u8 res2[0x8];
	u32 uempr;		/* UCC Ethernet Mac parameter reg */
	u32 utbipar;		/* UCC tbi address reg */
	u16 uescr;		/* UCC Ethernet statistics control reg */
	u8 res3[0x180 - 0x15A];
	u32 tx64;		/* Total number of frames (including bad
				   frames) transmitted that were exactly of the
				   minimal length (64 क्रम un tagged, 68 क्रम
				   tagged, or with length exactly equal to the
				   parameter MINLength */
	u32 tx127;		/* Total number of frames (including bad
				   frames) transmitted that were between
				   MINLength (Including FCS length==4) and 127
				   octets */
	u32 tx255;		/* Total number of frames (including bad
				   frames) transmitted that were between 128
				   (Including FCS length==4) and 255 octets */
	u32 rx64;		/* Total number of frames received including
				   bad frames that were exactly of the mninimal
				   length (64 bytes) */
	u32 rx127;		/* Total number of frames (including bad
				   frames) received that were between MINLength
				   (Including FCS length==4) and 127 octets */
	u32 rx255;		/* Total number of frames (including bad
				   frames) received that were between 128
				   (Including FCS length==4) and 255 octets */
	u32 txok;		/* Total number of octets residing in frames
				   that where involved in successful
				   transmission */
	u16 txcf;		/* Total number of PAUSE control frames
				   transmitted by this MAC */
	u8 res4[0x2];
	u32 पंचांगca;		/* Total number of frames that were transmitted
				   successfully with the group address bit set
				   that are not broadcast frames */
	u32 tbca;		/* Total number of frames transmitted
				   successfully that had destination address
				   field equal to the broadcast address */
	u32 rxfok;		/* Total number of frames received OK */
	u32 rxbok;		/* Total number of octets received OK */
	u32 rbyt;		/* Total number of octets received including
				   octets in bad frames. Must be implemented in
				   HW because it includes octets in frames that
				   never even reach the UCC */
	u32 rmca;		/* Total number of frames that were received
				   successfully with the group address bit set
				   that are not broadcast frames */
	u32 rbca;		/* Total number of frames received successfully
				   that had destination address equal to the
				   broadcast address */
	u32 scar;		/* Statistics carry रेजिस्टर */
	u32 scam;		/* Statistics caryy mask रेजिस्टर */
	u8 res5[0x200 - 0x1c4];
पूर्ण __packed;

/* UCC GETH TEMODR Register */
#घोषणा TEMODER_TX_RMON_STATISTICS_ENABLE       0x0100	/* enable Tx statistics
							 */
#घोषणा TEMODER_SCHEDULER_ENABLE                0x2000	/* enable scheduler */
#घोषणा TEMODER_IP_CHECKSUM_GENERATE            0x0400	/* generate IPv4
							   checksums */
#घोषणा TEMODER_PERFORMANCE_OPTIMIZATION_MODE1  0x0200	/* enable perक्रमmance
							   optimization
							   enhancement (mode1) */
#घोषणा TEMODER_RMON_STATISTICS                 0x0100	/* enable tx statistics
							 */
#घोषणा TEMODER_NUM_OF_QUEUES_SHIFT             (15-15)	/* Number of queues <<
							   shअगरt */

/* UCC GETH TEMODR Register */
#घोषणा REMODER_RX_RMON_STATISTICS_ENABLE       0x00001000	/* enable Rx
								   statistics */
#घोषणा REMODER_RX_EXTENDED_FEATURES            0x80000000	/* enable
								   extended
								   features */
#घोषणा REMODER_VLAN_OPERATION_TAGGED_SHIFT     (31-9 )	/* vlan operation
							   tagged << shअगरt */
#घोषणा REMODER_VLAN_OPERATION_NON_TAGGED_SHIFT (31-10)	/* vlan operation non
							   tagged << shअगरt */
#घोषणा REMODER_RX_QOS_MODE_SHIFT               (31-15)	/* rx QoS mode << shअगरt
							 */
#घोषणा REMODER_RMON_STATISTICS                 0x00001000	/* enable rx
								   statistics */
#घोषणा REMODER_RX_EXTENDED_FILTERING           0x00000800	/* extended
								   filtering
								   vs.
								   mpc82xx-like
								   filtering */
#घोषणा REMODER_NUM_OF_QUEUES_SHIFT             (31-23)	/* Number of queues <<
							   shअगरt */
#घोषणा REMODER_DYNAMIC_MAX_FRAME_LENGTH        0x00000008	/* enable
								   dynamic max
								   frame length
								 */
#घोषणा REMODER_DYNAMIC_MIN_FRAME_LENGTH        0x00000004	/* enable
								   dynamic min
								   frame length
								 */
#घोषणा REMODER_IP_CHECKSUM_CHECK               0x00000002	/* check IPv4
								   checksums */
#घोषणा REMODER_IP_ADDRESS_ALIGNMENT            0x00000001	/* align ip
								   address to
								   4-byte
								   boundary */

/* UCC GETH Event Register */
#घोषणा UCCE_TXB   (UCC_GETH_UCCE_TXB7 | UCC_GETH_UCCE_TXB6 | \
		    UCC_GETH_UCCE_TXB5 | UCC_GETH_UCCE_TXB4 | \
		    UCC_GETH_UCCE_TXB3 | UCC_GETH_UCCE_TXB2 | \
		    UCC_GETH_UCCE_TXB1 | UCC_GETH_UCCE_TXB0)

#घोषणा UCCE_RXB   (UCC_GETH_UCCE_RXB7 | UCC_GETH_UCCE_RXB6 | \
		    UCC_GETH_UCCE_RXB5 | UCC_GETH_UCCE_RXB4 | \
		    UCC_GETH_UCCE_RXB3 | UCC_GETH_UCCE_RXB2 | \
		    UCC_GETH_UCCE_RXB1 | UCC_GETH_UCCE_RXB0)

#घोषणा UCCE_RXF   (UCC_GETH_UCCE_RXF7 | UCC_GETH_UCCE_RXF6 | \
		    UCC_GETH_UCCE_RXF5 | UCC_GETH_UCCE_RXF4 | \
		    UCC_GETH_UCCE_RXF3 | UCC_GETH_UCCE_RXF2 | \
		    UCC_GETH_UCCE_RXF1 | UCC_GETH_UCCE_RXF0)

#घोषणा UCCE_OTHER (UCC_GETH_UCCE_SCAR | UCC_GETH_UCCE_GRA | \
		    UCC_GETH_UCCE_CBPR | UCC_GETH_UCCE_BSY | \
		    UCC_GETH_UCCE_RXC  | UCC_GETH_UCCE_TXC | UCC_GETH_UCCE_TXE)

#घोषणा UCCE_RX_EVENTS  (UCCE_RXF | UCC_GETH_UCCE_BSY)
#घोषणा UCCE_TX_EVENTS	(UCCE_TXB | UCC_GETH_UCCE_TXE)

/* TBI defines */
#घोषणा	ENET_TBI_MII_CR		0x00	/* Control */
#घोषणा	ENET_TBI_MII_SR		0x01	/* Status */
#घोषणा	ENET_TBI_MII_ANA	0x04	/* AN advertisement */
#घोषणा	ENET_TBI_MII_ANLPBPA	0x05	/* AN link partner base page ability */
#घोषणा	ENET_TBI_MII_ANEX	0x06	/* AN expansion */
#घोषणा	ENET_TBI_MII_ANNPT	0x07	/* AN next page transmit */
#घोषणा	ENET_TBI_MII_ANLPANP	0x08	/* AN link partner ability next page */
#घोषणा	ENET_TBI_MII_EXST	0x0F	/* Extended status */
#घोषणा	ENET_TBI_MII_JD		0x10	/* Jitter diagnostics */
#घोषणा	ENET_TBI_MII_TBICON	0x11	/* TBI control */

/* TBI MDIO रेजिस्टर bit fields*/
#घोषणा TBISR_LSTATUS          0x0004
#घोषणा TBICON_CLK_SELECT       0x0020
#घोषणा TBIANA_ASYMMETRIC_PAUSE 0x0100
#घोषणा TBIANA_SYMMETRIC_PAUSE  0x0080
#घोषणा TBIANA_HALF_DUPLEX      0x0040
#घोषणा TBIANA_FULL_DUPLEX      0x0020
#घोषणा TBICR_PHY_RESET         0x8000
#घोषणा TBICR_ANEG_ENABLE       0x1000
#घोषणा TBICR_RESTART_ANEG      0x0200
#घोषणा TBICR_FULL_DUPLEX       0x0100
#घोषणा TBICR_SPEED1_SET        0x0040

#घोषणा TBIANA_SETTINGS ( \
		TBIANA_ASYMMETRIC_PAUSE \
		| TBIANA_SYMMETRIC_PAUSE \
		| TBIANA_FULL_DUPLEX \
		)
#घोषणा TBICR_SETTINGS ( \
		TBICR_PHY_RESET \
		| TBICR_ANEG_ENABLE \
		| TBICR_FULL_DUPLEX \
		| TBICR_SPEED1_SET \
		)

/* UCC GETH MACCFG1 (MAC Configuration 1 Register) */
#घोषणा MACCFG1_FLOW_RX                         0x00000020	/* Flow Control
								   Rx */
#घोषणा MACCFG1_FLOW_TX                         0x00000010	/* Flow Control
								   Tx */
#घोषणा MACCFG1_ENABLE_SYNCHED_RX               0x00000008	/* Rx Enable
								   synchronized
								   to Rx stream
								 */
#घोषणा MACCFG1_ENABLE_RX                       0x00000004	/* Enable Rx */
#घोषणा MACCFG1_ENABLE_SYNCHED_TX               0x00000002	/* Tx Enable
								   synchronized
								   to Tx stream
								 */
#घोषणा MACCFG1_ENABLE_TX                       0x00000001	/* Enable Tx */

/* UCC GETH MACCFG2 (MAC Configuration 2 Register) */
#घोषणा MACCFG2_PREL_SHIFT                      (31 - 19)	/* Preamble
								   Length <<
								   shअगरt */
#घोषणा MACCFG2_PREL_MASK                       0x0000f000	/* Preamble
								   Length mask */
#घोषणा MACCFG2_SRP                             0x00000080	/* Soft Receive
								   Preamble */
#घोषणा MACCFG2_STP                             0x00000040	/* Soft
								   Transmit
								   Preamble */
#घोषणा MACCFG2_RESERVED_1                      0x00000020	/* Reserved -
								   must be set
								   to 1 */
#घोषणा MACCFG2_LC                              0x00000010	/* Length Check
								 */
#घोषणा MACCFG2_MPE                             0x00000008	/* Magic packet
								   detect */
#घोषणा MACCFG2_FDX                             0x00000001	/* Full Duplex */
#घोषणा MACCFG2_FDX_MASK                        0x00000001	/* Full Duplex
								   mask */
#घोषणा MACCFG2_PAD_CRC                         0x00000004
#घोषणा MACCFG2_CRC_EN                          0x00000002
#घोषणा MACCFG2_PAD_AND_CRC_MODE_NONE           0x00000000	/* Neither
								   Padding
								   लघु frames
								   nor CRC */
#घोषणा MACCFG2_PAD_AND_CRC_MODE_CRC_ONLY       0x00000002	/* Append CRC
								   only */
#घोषणा MACCFG2_PAD_AND_CRC_MODE_PAD_AND_CRC    0x00000004
#घोषणा MACCFG2_INTERFACE_MODE_NIBBLE           0x00000100	/* nibble mode
								   (MII/RMII/RGMII
								   10/100bps) */
#घोषणा MACCFG2_INTERFACE_MODE_BYTE             0x00000200	/* byte mode
								   (GMII/TBI/RTB/RGMII
								   1000bps ) */
#घोषणा MACCFG2_INTERFACE_MODE_MASK             0x00000300	/* mask
								   covering all
								   relevant
								   bits */

/* UCC GETH IPGIFG (Inter-frame Gap / Inter-Frame Gap Register) */
#घोषणा IPGIFG_NON_BACK_TO_BACK_IFG_PART1_SHIFT (31 -  7)	/* Non
								   back-to-back
								   पूर्णांकer frame
								   gap part 1.
								   << shअगरt */
#घोषणा IPGIFG_NON_BACK_TO_BACK_IFG_PART2_SHIFT (31 - 15)	/* Non
								   back-to-back
								   पूर्णांकer frame
								   gap part 2.
								   << shअगरt */
#घोषणा IPGIFG_MINIMUM_IFG_ENFORCEMENT_SHIFT    (31 - 23)	/* Mimimum IFG
								   Enक्रमcement
								   << shअगरt */
#घोषणा IPGIFG_BACK_TO_BACK_IFG_SHIFT           (31 - 31)	/* back-to-back
								   पूर्णांकer frame
								   gap << shअगरt
								 */
#घोषणा IPGIFG_NON_BACK_TO_BACK_IFG_PART1_MAX   127	/* Non back-to-back
							   पूर्णांकer frame gap part
							   1. max val */
#घोषणा IPGIFG_NON_BACK_TO_BACK_IFG_PART2_MAX   127	/* Non back-to-back
							   पूर्णांकer frame gap part
							   2. max val */
#घोषणा IPGIFG_MINIMUM_IFG_ENFORCEMENT_MAX      255	/* Mimimum IFG
							   Enक्रमcement max val */
#घोषणा IPGIFG_BACK_TO_BACK_IFG_MAX             127	/* back-to-back पूर्णांकer
							   frame gap max val */
#घोषणा IPGIFG_NBTB_CS_IPG_MASK                 0x7F000000
#घोषणा IPGIFG_NBTB_IPG_MASK                    0x007F0000
#घोषणा IPGIFG_MIN_IFG_MASK                     0x0000FF00
#घोषणा IPGIFG_BTB_IPG_MASK                     0x0000007F

/* UCC GETH HAFDUP (Half Duplex Register) */
#घोषणा HALFDUP_ALT_BEB_TRUNCATION_SHIFT        (31 - 11)	/* Alternate
								   Binary
								   Exponential
								   Backoff
								   Truncation
								   << shअगरt */
#घोषणा HALFDUP_ALT_BEB_TRUNCATION_MAX          0xf	/* Alternate Binary
							   Exponential Backoff
							   Truncation max val */
#घोषणा HALFDUP_ALT_BEB                         0x00080000	/* Alternate
								   Binary
								   Exponential
								   Backoff */
#घोषणा HALFDUP_BACK_PRESSURE_NO_BACKOFF        0x00040000	/* Back
								   pressure no
								   backoff */
#घोषणा HALFDUP_NO_BACKOFF                      0x00020000	/* No Backoff */
#घोषणा HALFDUP_EXCESSIVE_DEFER                 0x00010000	/* Excessive
								   Defer */
#घोषणा HALFDUP_MAX_RETRANSMISSION_SHIFT        (31 - 19)	/* Maximum
								   Retransmission
								   << shअगरt */
#घोषणा HALFDUP_MAX_RETRANSMISSION_MAX          0xf	/* Maximum
							   Retransmission max
							   val */
#घोषणा HALFDUP_COLLISION_WINDOW_SHIFT          (31 - 31)	/* Collision
								   Winकरोw <<
								   shअगरt */
#घोषणा HALFDUP_COLLISION_WINDOW_MAX            0x3f	/* Collision Winकरोw max
							   val */
#घोषणा HALFDUP_ALT_BEB_TR_MASK                 0x00F00000
#घोषणा HALFDUP_RETRANS_MASK                    0x0000F000
#घोषणा HALFDUP_COL_WINDOW_MASK                 0x0000003F

/* UCC GETH UCCS (Ethernet Status Register) */
#घोषणा UCCS_BPR                                0x02	/* Back pressure (in
							   half duplex mode) */
#घोषणा UCCS_PAU                                0x02	/* Pause state (in full
							   duplex mode) */
#घोषणा UCCS_MPD                                0x01	/* Magic Packet
							   Detected */

/* UCC GETH IFSTAT (Interface Status Register) */
#घोषणा IFSTAT_EXCESS_DEFER                     0x00000200	/* Excessive
								   transmission
								   defer */

/* UCC GETH MACSTNADDR1 (Station Address Part 1 Register) */
#घोषणा MACSTNADDR1_OCTET_6_SHIFT               (31 -  7)	/* Station
								   address 6th
								   octet <<
								   shअगरt */
#घोषणा MACSTNADDR1_OCTET_5_SHIFT               (31 - 15)	/* Station
								   address 5th
								   octet <<
								   shअगरt */
#घोषणा MACSTNADDR1_OCTET_4_SHIFT               (31 - 23)	/* Station
								   address 4th
								   octet <<
								   shअगरt */
#घोषणा MACSTNADDR1_OCTET_3_SHIFT               (31 - 31)	/* Station
								   address 3rd
								   octet <<
								   shअगरt */

/* UCC GETH MACSTNADDR2 (Station Address Part 2 Register) */
#घोषणा MACSTNADDR2_OCTET_2_SHIFT               (31 -  7)	/* Station
								   address 2nd
								   octet <<
								   shअगरt */
#घोषणा MACSTNADDR2_OCTET_1_SHIFT               (31 - 15)	/* Station
								   address 1st
								   octet <<
								   shअगरt */

/* UCC GETH UEMPR (Ethernet Mac Parameter Register) */
#घोषणा UEMPR_PAUSE_TIME_VALUE_SHIFT            (31 - 15)	/* Pause समय
								   value <<
								   shअगरt */
#घोषणा UEMPR_EXTENDED_PAUSE_TIME_VALUE_SHIFT   (31 - 31)	/* Extended
								   छोड़ो समय
								   value <<
								   shअगरt */

/* UCC GETH UTBIPAR (Ten Bit Interface Physical Address Register) */
#घोषणा UTBIPAR_PHY_ADDRESS_SHIFT               (31 - 31)	/* Phy address
								   << shअगरt */
#घोषणा UTBIPAR_PHY_ADDRESS_MASK                0x0000001f	/* Phy address
								   mask */

/* UCC GETH UESCR (Ethernet Statistics Control Register) */
#घोषणा UESCR_AUTOZ                             0x8000	/* Automatically zero
							   addressed
							   statistical counter
							   values */
#घोषणा UESCR_CLRCNT                            0x4000	/* Clear all statistics
							   counters */
#घोषणा UESCR_MAXCOV_SHIFT                      (15 -  7)	/* Max
								   Coalescing
								   Value <<
								   shअगरt */
#घोषणा UESCR_SCOV_SHIFT                        (15 - 15)	/* Status
								   Coalescing
								   Value <<
								   shअगरt */

/* UCC GETH UDSR (Data Synchronization Register) */
#घोषणा UDSR_MAGIC                              0x067E

काष्ठा ucc_geth_thपढ़ो_data_tx अणु
	u8 res0[104];
पूर्ण __packed;

काष्ठा ucc_geth_thपढ़ो_data_rx अणु
	u8 res0[40];
पूर्ण __packed;

/* Send Queue Queue-Descriptor */
काष्ठा ucc_geth_send_queue_qd अणु
	u32 bd_ring_base;	/* poपूर्णांकer to BD ring base address */
	u8 res0[0x8];
	u32 last_bd_completed_address;/* initialize to last entry in BD ring */
	u8 res1[0x30];
पूर्ण __packed;

काष्ठा ucc_geth_send_queue_mem_region अणु
	काष्ठा ucc_geth_send_queue_qd sqqd[NUM_TX_QUEUES];
पूर्ण __packed;

काष्ठा ucc_geth_thपढ़ो_tx_pram अणु
	u8 res0[64];
पूर्ण __packed;

काष्ठा ucc_geth_thपढ़ो_rx_pram अणु
	u8 res0[128];
पूर्ण __packed;

#घोषणा THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING        64
#घोषणा THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING_8      64
#घोषणा THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING_16     96

काष्ठा ucc_geth_scheduler अणु
	u16 cpucount0;		/* CPU packet counter */
	u16 cpucount1;		/* CPU packet counter */
	u16 cecount0;		/* QE packet counter */
	u16 cecount1;		/* QE packet counter */
	u16 cpucount2;		/* CPU packet counter */
	u16 cpucount3;		/* CPU packet counter */
	u16 cecount2;		/* QE packet counter */
	u16 cecount3;		/* QE packet counter */
	u16 cpucount4;		/* CPU packet counter */
	u16 cpucount5;		/* CPU packet counter */
	u16 cecount4;		/* QE packet counter */
	u16 cecount5;		/* QE packet counter */
	u16 cpucount6;		/* CPU packet counter */
	u16 cpucount7;		/* CPU packet counter */
	u16 cecount6;		/* QE packet counter */
	u16 cecount7;		/* QE packet counter */
	u32 weightstatus[NUM_TX_QUEUES];	/* accumulated weight factor */
	u32 rtsrshaकरोw;		/* temporary variable handled by QE */
	u32 समय;		/* temporary variable handled by QE */
	u32 ttl;		/* temporary variable handled by QE */
	u32 mblपूर्णांकerval;	/* max burst length पूर्णांकerval */
	u16 nortsrbyteसमय;	/* normalized value of byte समय in tsr units */
	u8 fracsiz;		/* radix 2 log value of denom. of
				   NorTSRByteTime */
	u8 res0[1];
	u8 strictpriorityq;	/* Strict Priority Mask रेजिस्टर */
	u8 txasap;		/* Transmit ASAP रेजिस्टर */
	u8 extrabw;		/* Extra BandWidth रेजिस्टर */
	u8 oldwfqmask;		/* temporary variable handled by QE */
	u8 weightfactor[NUM_TX_QUEUES];
				      /**< weight factor क्रम queues   */
	u32 minw;		/* temporary variable handled by QE */
	u8 res1[0x70 - 0x64];
पूर्ण __packed;

काष्ठा ucc_geth_tx_firmware_statistics_pram अणु
	u32 sicoltx;		/* single collision */
	u32 mulcoltx;		/* multiple collision */
	u32 latecoltxfr;	/* late collision */
	u32 frपातduecol;	/* frames पातed due to transmit collision */
	u32 frlostinmactxer;	/* frames lost due to पूर्णांकernal MAC error
				   transmission that are not counted on any
				   other counter */
	u32 carriersenseertx;	/* carrier sense error */
	u32 frtxok;		/* frames transmitted OK */
	u32 txfrexcessivedefer;	/* frames with defferal समय greater than
				   specअगरied threshold */
	u32 txpkts256;		/* total packets (including bad) between 256
				   and 511 octets */
	u32 txpkts512;		/* total packets (including bad) between 512
				   and 1023 octets */
	u32 txpkts1024;		/* total packets (including bad) between 1024
				   and 1518 octets */
	u32 txpktsjumbo;	/* total packets (including bad) between 1024
				   and MAXLength octets */
पूर्ण __packed;

काष्ठा ucc_geth_rx_firmware_statistics_pram अणु
	u32 frrxfcser;		/* frames with crc error */
	u32 fraligner;		/* frames with alignment error */
	u32 inrangelenrxer;	/* in range length error */
	u32 outrangelenrxer;	/* out of range length error */
	u32 frtooदीर्घ;		/* frame too दीर्घ */
	u32 runt;		/* runt */
	u32 veryदीर्घevent;	/* very दीर्घ event */
	u32 symbolerror;	/* symbol error */
	u32 dropbsy;		/* drop because of BD not पढ़ोy */
	u8 res0[0x8];
	u32 mismatchdrop;	/* drop because of MAC filtering (e.g. address
				   or type mismatch) */
	u32 underpkts;		/* total frames less than 64 octets */
	u32 pkts256;		/* total frames (including bad) between 256 and
				   511 octets */
	u32 pkts512;		/* total frames (including bad) between 512 and
				   1023 octets */
	u32 pkts1024;		/* total frames (including bad) between 1024
				   and 1518 octets */
	u32 pktsjumbo;		/* total frames (including bad) between 1024
				   and MAXLength octets */
	u32 frlossinmacer;	/* frames lost because of पूर्णांकernal MAC error
				   that is not counted in any other counter */
	u32 छोड़ोfr;		/* छोड़ो frames */
	u8 res1[0x4];
	u32 हटाओvlan;		/* total frames that had their VLAN tag हटाओd
				 */
	u32 replacevlan;	/* total frames that had their VLAN tag
				   replaced */
	u32 insertvlan;		/* total frames that had their VLAN tag
				   inserted */
पूर्ण __packed;

काष्ठा ucc_geth_rx_पूर्णांकerrupt_coalescing_entry अणु
	u32 पूर्णांकerruptcoalescingmaxvalue;	/* पूर्णांकerrupt coalescing max
						   value */
	u32 पूर्णांकerruptcoalescingcounter;	/* पूर्णांकerrupt coalescing counter,
					   initialize to
					   पूर्णांकerruptcoalescingmaxvalue */
पूर्ण __packed;

काष्ठा ucc_geth_rx_पूर्णांकerrupt_coalescing_table अणु
	काष्ठा ucc_geth_rx_पूर्णांकerrupt_coalescing_entry coalescingentry[NUM_RX_QUEUES];
				       /**< पूर्णांकerrupt coalescing entry */
पूर्ण __packed;

काष्ठा ucc_geth_rx_prefetched_bds अणु
	काष्ठा qe_bd bd[NUM_BDS_IN_PREFETCHED_BDS];	/* prefetched bd */
पूर्ण __packed;

काष्ठा ucc_geth_rx_bd_queues_entry अणु
	u32 bdbaseptr;		/* BD base poपूर्णांकer */
	u32 bdptr;		/* BD poपूर्णांकer */
	u32 बाह्यalbdbaseptr;	/* बाह्यal BD base poपूर्णांकer */
	u32 बाह्यalbdptr;	/* बाह्यal BD poपूर्णांकer */
पूर्ण __packed;

काष्ठा ucc_geth_tx_global_pram अणु
	u16 temoder;
	u8 res0[0x38 - 0x02];
	u32 sqptr;		/* a base poपूर्णांकer to send queue memory region */
	u32 schedulerbasepoपूर्णांकer;	/* a base poपूर्णांकer to scheduler memory
					   region */
	u32 txrmonbaseptr;	/* base poपूर्णांकer to Tx RMON statistics counter */
	u32 tstate;		/* tx पूर्णांकernal state. High byte contains
				   function code */
	u8 iphoffset[TX_IP_OFFSET_ENTRY_MAX];
	u32 vtagtable[0x8];	/* 8 4-byte VLAN tags */
	u32 tqptr;		/* a base poपूर्णांकer to the Tx Queues Memory
				   Region */
	u8 res2[0x78 - 0x74];
	u64 snums_en;
	u32 l2l3baseptr;	/* top byte consists of a few other bit fields */

	u16 mtu[8];
	u8 res3[0xa8 - 0x94];
	u32 wrrtablebase;	/* top byte is reserved */
	u8 res4[0xc0 - 0xac];
पूर्ण __packed;

/* काष्ठाure representing Extended Filtering Global Parameters in PRAM */
काष्ठा ucc_geth_exf_global_pram अणु
	u32 l2pcdptr;		/* inभागidual address filter, high */
	u8 res0[0x10 - 0x04];
पूर्ण __packed;

काष्ठा ucc_geth_rx_global_pram अणु
	u32 remoder;		/* ethernet mode reg. */
	u32 rqptr;		/* base poपूर्णांकer to the Rx Queues Memory Region*/
	u32 res0[0x1];
	u8 res1[0x20 - 0xC];
	u16 typeorlen;		/* cutoff poपूर्णांक less than which, type/len field
				   is considered length */
	u8 res2[0x1];
	u8 rxgstpack;		/* acknowledgement on GRACEFUL STOP RX command*/
	u32 rxrmonbaseptr;	/* base poपूर्णांकer to Rx RMON statistics counter */
	u8 res3[0x30 - 0x28];
	u32 पूर्णांकcoalescingptr;	/* Interrupt coalescing table poपूर्णांकer */
	u8 res4[0x36 - 0x34];
	u8 rstate;		/* rx पूर्णांकernal state. High byte contains
				   function code */
	u8 res5[0x46 - 0x37];
	u16 mrblr;		/* max receive buffer length reg. */
	u32 rbdqptr;		/* base poपूर्णांकer to RxBD parameter table
				   description */
	u16 mflr;		/* max frame length reg. */
	u16 minflr;		/* min frame length reg. */
	u16 maxd1;		/* max dma1 length reg. */
	u16 maxd2;		/* max dma2 length reg. */
	u32 ecamptr;		/* बाह्यal CAM address */
	u32 l2qt;		/* VLAN priority mapping table. */
	u32 l3qt[0x8];		/* IP priority mapping table. */
	u16 vlantype;		/* vlan type */
	u16 vlantci;		/* शेष vlan tci */
	u8 addressfiltering[64];	/* address filtering data काष्ठाure */
	u32 exfGlobalParam;	/* base address क्रम extended filtering global
				   parameters */
	u8 res6[0x100 - 0xC4];	/* Initialize to zero */
पूर्ण __packed;

#घोषणा GRACEFUL_STOP_ACKNOWLEDGE_RX            0x01

/* काष्ठाure representing InitEnet command */
काष्ठा ucc_geth_init_pram अणु
	u8 resinit1;
	u8 resinit2;
	u8 resinit3;
	u8 resinit4;
	u16 resinit5;
	u8 res1[0x1];
	u8 largestबाह्यallookupkeysize;
	u32 rgftgfrxglobal;
	u32 rxthपढ़ो[ENET_INIT_PARAM_MAX_ENTRIES_RX];	/* rx thपढ़ोs */
	u8 res2[0x38 - 0x30];
	u32 txglobal;		/* tx global */
	u32 txthपढ़ो[ENET_INIT_PARAM_MAX_ENTRIES_TX];	/* tx thपढ़ोs */
	u8 res3[0x1];
पूर्ण __packed;

#घोषणा ENET_INIT_PARAM_RGF_SHIFT               (32 - 4)
#घोषणा ENET_INIT_PARAM_TGF_SHIFT               (32 - 8)

#घोषणा ENET_INIT_PARAM_RISC_MASK               0x0000003f
#घोषणा ENET_INIT_PARAM_PTR_MASK                0x00ffffc0
#घोषणा ENET_INIT_PARAM_SNUM_MASK               0xff000000
#घोषणा ENET_INIT_PARAM_SNUM_SHIFT              24

#घोषणा ENET_INIT_PARAM_MAGIC_RES_INIT1         0x06
#घोषणा ENET_INIT_PARAM_MAGIC_RES_INIT2         0x30
#घोषणा ENET_INIT_PARAM_MAGIC_RES_INIT3         0xff
#घोषणा ENET_INIT_PARAM_MAGIC_RES_INIT4         0x00
#घोषणा ENET_INIT_PARAM_MAGIC_RES_INIT5         0x0400

/* काष्ठाure representing 82xx Address Filtering Enet Address in PRAM */
काष्ठा ucc_geth_82xx_enet_address अणु
	u8 res1[0x2];
	u16 h;			/* address (MSB) */
	u16 m;			/* address */
	u16 l;			/* address (LSB) */
पूर्ण __packed;

/* काष्ठाure representing 82xx Address Filtering PRAM */
काष्ठा ucc_geth_82xx_address_filtering_pram अणु
	u32 iaddr_h;		/* inभागidual address filter, high */
	u32 iaddr_l;		/* inभागidual address filter, low */
	u32 gaddr_h;		/* group address filter, high */
	u32 gaddr_l;		/* group address filter, low */
	काष्ठा ucc_geth_82xx_enet_address __iomem taddr;
	काष्ठा ucc_geth_82xx_enet_address __iomem paddr[NUM_OF_PADDRS];
	u8 res0[0x40 - 0x38];
पूर्ण __packed;

/* GETH Tx firmware statistics काष्ठाure, used when calling
   UCC_GETH_GetStatistics. */
काष्ठा ucc_geth_tx_firmware_statistics अणु
	u32 sicoltx;		/* single collision */
	u32 mulcoltx;		/* multiple collision */
	u32 latecoltxfr;	/* late collision */
	u32 frपातduecol;	/* frames पातed due to transmit collision */
	u32 frlostinmactxer;	/* frames lost due to पूर्णांकernal MAC error
				   transmission that are not counted on any
				   other counter */
	u32 carriersenseertx;	/* carrier sense error */
	u32 frtxok;		/* frames transmitted OK */
	u32 txfrexcessivedefer;	/* frames with defferal समय greater than
				   specअगरied threshold */
	u32 txpkts256;		/* total packets (including bad) between 256
				   and 511 octets */
	u32 txpkts512;		/* total packets (including bad) between 512
				   and 1023 octets */
	u32 txpkts1024;		/* total packets (including bad) between 1024
				   and 1518 octets */
	u32 txpktsjumbo;	/* total packets (including bad) between 1024
				   and MAXLength octets */
पूर्ण __packed;

/* GETH Rx firmware statistics काष्ठाure, used when calling
   UCC_GETH_GetStatistics. */
काष्ठा ucc_geth_rx_firmware_statistics अणु
	u32 frrxfcser;		/* frames with crc error */
	u32 fraligner;		/* frames with alignment error */
	u32 inrangelenrxer;	/* in range length error */
	u32 outrangelenrxer;	/* out of range length error */
	u32 frtooदीर्घ;		/* frame too दीर्घ */
	u32 runt;		/* runt */
	u32 veryदीर्घevent;	/* very दीर्घ event */
	u32 symbolerror;	/* symbol error */
	u32 dropbsy;		/* drop because of BD not पढ़ोy */
	u8 res0[0x8];
	u32 mismatchdrop;	/* drop because of MAC filtering (e.g. address
				   or type mismatch) */
	u32 underpkts;		/* total frames less than 64 octets */
	u32 pkts256;		/* total frames (including bad) between 256 and
				   511 octets */
	u32 pkts512;		/* total frames (including bad) between 512 and
				   1023 octets */
	u32 pkts1024;		/* total frames (including bad) between 1024
				   and 1518 octets */
	u32 pktsjumbo;		/* total frames (including bad) between 1024
				   and MAXLength octets */
	u32 frlossinmacer;	/* frames lost because of पूर्णांकernal MAC error
				   that is not counted in any other counter */
	u32 छोड़ोfr;		/* छोड़ो frames */
	u8 res1[0x4];
	u32 हटाओvlan;		/* total frames that had their VLAN tag हटाओd
				 */
	u32 replacevlan;	/* total frames that had their VLAN tag
				   replaced */
	u32 insertvlan;		/* total frames that had their VLAN tag
				   inserted */
पूर्ण __packed;

/* GETH hardware statistics काष्ठाure, used when calling
   UCC_GETH_GetStatistics. */
काष्ठा ucc_geth_hardware_statistics अणु
	u32 tx64;		/* Total number of frames (including bad
				   frames) transmitted that were exactly of the
				   minimal length (64 क्रम un tagged, 68 क्रम
				   tagged, or with length exactly equal to the
				   parameter MINLength */
	u32 tx127;		/* Total number of frames (including bad
				   frames) transmitted that were between
				   MINLength (Including FCS length==4) and 127
				   octets */
	u32 tx255;		/* Total number of frames (including bad
				   frames) transmitted that were between 128
				   (Including FCS length==4) and 255 octets */
	u32 rx64;		/* Total number of frames received including
				   bad frames that were exactly of the mninimal
				   length (64 bytes) */
	u32 rx127;		/* Total number of frames (including bad
				   frames) received that were between MINLength
				   (Including FCS length==4) and 127 octets */
	u32 rx255;		/* Total number of frames (including bad
				   frames) received that were between 128
				   (Including FCS length==4) and 255 octets */
	u32 txok;		/* Total number of octets residing in frames
				   that where involved in successful
				   transmission */
	u16 txcf;		/* Total number of PAUSE control frames
				   transmitted by this MAC */
	u32 पंचांगca;		/* Total number of frames that were transmitted
				   successfully with the group address bit set
				   that are not broadcast frames */
	u32 tbca;		/* Total number of frames transmitted
				   successfully that had destination address
				   field equal to the broadcast address */
	u32 rxfok;		/* Total number of frames received OK */
	u32 rxbok;		/* Total number of octets received OK */
	u32 rbyt;		/* Total number of octets received including
				   octets in bad frames. Must be implemented in
				   HW because it includes octets in frames that
				   never even reach the UCC */
	u32 rmca;		/* Total number of frames that were received
				   successfully with the group address bit set
				   that are not broadcast frames */
	u32 rbca;		/* Total number of frames received successfully
				   that had destination address equal to the
				   broadcast address */
पूर्ण __packed;

/* UCC GETH Tx errors वापसed via TxConf callback */
#घोषणा TX_ERRORS_DEF      0x0200
#घोषणा TX_ERRORS_EXDEF    0x0100
#घोषणा TX_ERRORS_LC       0x0080
#घोषणा TX_ERRORS_RL       0x0040
#घोषणा TX_ERRORS_RC_MASK  0x003C
#घोषणा TX_ERRORS_RC_SHIFT 2
#घोषणा TX_ERRORS_UN       0x0002
#घोषणा TX_ERRORS_CSL      0x0001

/* UCC GETH Rx errors वापसed via RxStore callback */
#घोषणा RX_ERRORS_CMR      0x0200
#घोषणा RX_ERRORS_M        0x0100
#घोषणा RX_ERRORS_BC       0x0080
#घोषणा RX_ERRORS_MC       0x0040

/* Transmit BD. These are in addition to values defined in uccf. */
#घोषणा T_VID      0x003c0000	/* insert VLAN id index mask. */
#घोषणा T_DEF      (((u32) TX_ERRORS_DEF     ) << 16)
#घोषणा T_EXDEF    (((u32) TX_ERRORS_EXDEF   ) << 16)
#घोषणा T_LC       (((u32) TX_ERRORS_LC      ) << 16)
#घोषणा T_RL       (((u32) TX_ERRORS_RL      ) << 16)
#घोषणा T_RC_MASK  (((u32) TX_ERRORS_RC_MASK ) << 16)
#घोषणा T_UN       (((u32) TX_ERRORS_UN      ) << 16)
#घोषणा T_CSL      (((u32) TX_ERRORS_CSL     ) << 16)
#घोषणा T_ERRORS_REPORT  (T_DEF | T_EXDEF | T_LC | T_RL | T_RC_MASK \
		| T_UN | T_CSL)	/* transmit errors to report */

/* Receive BD. These are in addition to values defined in uccf. */
#घोषणा R_LG    0x00200000	/* Frame length violation.  */
#घोषणा R_NO    0x00100000	/* Non-octet aligned frame.  */
#घोषणा R_SH    0x00080000	/* Short frame.  */
#घोषणा R_CR    0x00040000	/* CRC error.  */
#घोषणा R_OV    0x00020000	/* Overrun.  */
#घोषणा R_IPCH  0x00010000	/* IP checksum check failed. */
#घोषणा R_CMR   (((u32) RX_ERRORS_CMR  ) << 16)
#घोषणा R_M     (((u32) RX_ERRORS_M    ) << 16)
#घोषणा R_BC    (((u32) RX_ERRORS_BC   ) << 16)
#घोषणा R_MC    (((u32) RX_ERRORS_MC   ) << 16)
#घोषणा R_ERRORS_REPORT (R_CMR | R_M | R_BC | R_MC)	/* receive errors to
							   report */
#घोषणा R_ERRORS_FATAL  (R_LG  | R_NO | R_SH | R_CR | \
		R_OV | R_IPCH)	/* receive errors to discard */

/* Alignments */
#घोषणा UCC_GETH_RX_GLOBAL_PRAM_ALIGNMENT	256
#घोषणा UCC_GETH_TX_GLOBAL_PRAM_ALIGNMENT       128
#घोषणा UCC_GETH_THREAD_RX_PRAM_ALIGNMENT       128
#घोषणा UCC_GETH_THREAD_TX_PRAM_ALIGNMENT       64
#घोषणा UCC_GETH_THREAD_DATA_ALIGNMENT          256	/* spec gives values
							   based on num of
							   thपढ़ोs, but always
							   using the maximum is
							   easier */
#घोषणा UCC_GETH_SEND_QUEUE_QUEUE_DESCRIPTOR_ALIGNMENT	32
#घोषणा UCC_GETH_SCHEDULER_ALIGNMENT		8	/* This is a guess */
#घोषणा UCC_GETH_TX_STATISTICS_ALIGNMENT	4	/* This is a guess */
#घोषणा UCC_GETH_RX_STATISTICS_ALIGNMENT	4	/* This is a guess */
#घोषणा UCC_GETH_RX_INTERRUPT_COALESCING_ALIGNMENT	64
#घोषणा UCC_GETH_RX_BD_QUEUES_ALIGNMENT		8	/* This is a guess */
#घोषणा UCC_GETH_RX_PREFETCHED_BDS_ALIGNMENT	128	/* This is a guess */
#घोषणा UCC_GETH_RX_EXTENDED_FILTERING_GLOBAL_PARAMETERS_ALIGNMENT 8	/* This
									   is a
									   guess
									 */
#घोषणा UCC_GETH_RX_BD_RING_ALIGNMENT		32
#घोषणा UCC_GETH_TX_BD_RING_ALIGNMENT		32
#घोषणा UCC_GETH_MRBLR_ALIGNMENT		128
#घोषणा UCC_GETH_RX_BD_RING_SIZE_ALIGNMENT	4
#घोषणा UCC_GETH_TX_BD_RING_SIZE_MEMORY_ALIGNMENT	32
#घोषणा UCC_GETH_RX_DATA_BUF_ALIGNMENT		64

#घोषणा UCC_GETH_TAD_EF                         0x80
#घोषणा UCC_GETH_TAD_V                          0x40
#घोषणा UCC_GETH_TAD_REJ                        0x20
#घोषणा UCC_GETH_TAD_VTAG_OP_RIGHT_SHIFT        2
#घोषणा UCC_GETH_TAD_VTAG_OP_SHIFT              6
#घोषणा UCC_GETH_TAD_V_NON_VTAG_OP              0x20
#घोषणा UCC_GETH_TAD_RQOS_SHIFT                 0
#घोषणा UCC_GETH_TAD_V_PRIORITY_SHIFT           5
#घोषणा UCC_GETH_TAD_CFI                        0x10

#घोषणा UCC_GETH_VLAN_PRIORITY_MAX              8
#घोषणा UCC_GETH_IP_PRIORITY_MAX                64
#घोषणा UCC_GETH_TX_VTAG_TABLE_ENTRY_MAX        8
#घोषणा UCC_GETH_RX_BD_RING_SIZE_MIN            8
#घोषणा UCC_GETH_TX_BD_RING_SIZE_MIN            2
#घोषणा UCC_GETH_BD_RING_SIZE_MAX		0xffff

#घोषणा UCC_GETH_SIZE_OF_BD                     QE_SIZखातापूर्ण_BD

/* Driver definitions */
#घोषणा TX_BD_RING_LEN                          0x10
#घोषणा RX_BD_RING_LEN                          0x20

#घोषणा TX_RING_MOD_MASK(size)                  (size-1)
#घोषणा RX_RING_MOD_MASK(size)                  (size-1)

#घोषणा ENET_GROUP_ADDR                         0x01	/* Group address mask
							   क्रम ethernet
							   addresses */

#घोषणा TX_TIMEOUT                              (1*HZ)
#घोषणा PHY_INIT_TIMEOUT                        100000
#घोषणा PHY_CHANGE_TIME                         2

/* Fast Ethernet (10/100 Mbps) */
#घोषणा UCC_GETH_URFS_INIT                      512	/* Rx भव FIFO size
							 */
#घोषणा UCC_GETH_URFET_INIT                     256	/* 1/2 urfs */
#घोषणा UCC_GETH_URFSET_INIT                    384	/* 3/4 urfs */
#घोषणा UCC_GETH_UTFS_INIT                      512	/* Tx भव FIFO size
							 */
#घोषणा UCC_GETH_UTFET_INIT                     256	/* 1/2 utfs */
#घोषणा UCC_GETH_UTFTT_INIT                     256	/* 1/2 utfs
							   due to errata */
/* Gigabit Ethernet (1000 Mbps) */
#घोषणा UCC_GETH_URFS_GIGA_INIT                 4096/*2048*/	/* Rx भव
								   FIFO size */
#घोषणा UCC_GETH_URFET_GIGA_INIT                2048/*1024*/	/* 1/2 urfs */
#घोषणा UCC_GETH_URFSET_GIGA_INIT               3072/*1536*/	/* 3/4 urfs */
#घोषणा UCC_GETH_UTFS_GIGA_INIT                 4096/*2048*/	/* Tx भव
								   FIFO size */
#घोषणा UCC_GETH_UTFET_GIGA_INIT                2048/*1024*/	/* 1/2 utfs */
#घोषणा UCC_GETH_UTFTT_GIGA_INIT                4096/*0x40*/	/* Tx भव
								   FIFO size */

#घोषणा UCC_GETH_REMODER_INIT                   0	/* bits that must be
							   set */
#घोषणा UCC_GETH_TEMODER_INIT                   0xC000	/* bits that must */

/* Initial value क्रम UPSMR */
#घोषणा UCC_GETH_UPSMR_INIT                     UCC_GETH_UPSMR_RES1

#घोषणा UCC_GETH_MACCFG1_INIT                   0
#घोषणा UCC_GETH_MACCFG2_INIT                   (MACCFG2_RESERVED_1)

/* Ethernet Address Type. */
क्रमागत enet_addr_type अणु
	ENET_ADDR_TYPE_INDIVIDUAL,
	ENET_ADDR_TYPE_GROUP,
	ENET_ADDR_TYPE_BROADCAST
पूर्ण;

/* UCC GETH 82xx Ethernet Address Recognition Location */
क्रमागत ucc_geth_enet_address_recognition_location अणु
	UCC_GETH_ENET_ADDRESS_RECOGNITION_LOCATION_STATION_ADDRESS,/* station
								      address */
	UCC_GETH_ENET_ADDRESS_RECOGNITION_LOCATION_PADDR_FIRST,	/* additional
								   station
								   address
								   paddr1 */
	UCC_GETH_ENET_ADDRESS_RECOGNITION_LOCATION_PADDR2,	/* additional
								   station
								   address
								   paddr2 */
	UCC_GETH_ENET_ADDRESS_RECOGNITION_LOCATION_PADDR3,	/* additional
								   station
								   address
								   paddr3 */
	UCC_GETH_ENET_ADDRESS_RECOGNITION_LOCATION_PADDR_LAST,	/* additional
								   station
								   address
								   paddr4 */
	UCC_GETH_ENET_ADDRESS_RECOGNITION_LOCATION_GROUP_HASH,	/* group hash */
	UCC_GETH_ENET_ADDRESS_RECOGNITION_LOCATION_INDIVIDUAL_HASH /* inभागidual
								      hash */
पूर्ण;

/* UCC GETH vlan operation tagged */
क्रमागत ucc_geth_vlan_operation_tagged अणु
	UCC_GETH_VLAN_OPERATION_TAGGED_NOP = 0x0,	/* Tagged - nop */
	UCC_GETH_VLAN_OPERATION_TAGGED_REPLACE_VID_PORTION_OF_Q_TAG
		= 0x1,	/* Tagged - replace vid portion of q tag */
	UCC_GETH_VLAN_OPERATION_TAGGED_IF_VID0_REPLACE_VID_WITH_DEFAULT_VALUE
		= 0x2,	/* Tagged - अगर vid0 replace vid with शेष value  */
	UCC_GETH_VLAN_OPERATION_TAGGED_EXTRACT_Q_TAG_FROM_FRAME
		= 0x3	/* Tagged - extract q tag from frame */
पूर्ण;

/* UCC GETH vlan operation non-tagged */
क्रमागत ucc_geth_vlan_operation_non_tagged अणु
	UCC_GETH_VLAN_OPERATION_NON_TAGGED_NOP = 0x0,	/* Non tagged - nop */
	UCC_GETH_VLAN_OPERATION_NON_TAGGED_Q_TAG_INSERT = 0x1	/* Non tagged -
								   q tag insert
								 */
पूर्ण;

/* UCC GETH Rx Quality of Service Mode */
क्रमागत ucc_geth_qos_mode अणु
	UCC_GETH_QOS_MODE_DEFAULT = 0x0,	/* शेष queue */
	UCC_GETH_QOS_MODE_QUEUE_NUM_FROM_L2_CRITERIA = 0x1,	/* queue
								   determined
								   by L2
								   criteria */
	UCC_GETH_QOS_MODE_QUEUE_NUM_FROM_L3_CRITERIA = 0x2	/* queue
								   determined
								   by L3
								   criteria */
पूर्ण;

/* UCC GETH Statistics Gathering Mode - These are bit flags, 'or' them together
   क्रम combined functionality */
क्रमागत ucc_geth_statistics_gathering_mode अणु
	UCC_GETH_STATISTICS_GATHERING_MODE_NONE = 0x00000000,	/* No
								   statistics
								   gathering */
	UCC_GETH_STATISTICS_GATHERING_MODE_HARDWARE = 0x00000001,/* Enable
								    hardware
								    statistics
								    gathering
								  */
	UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_TX = 0x00000004,/*Enable
								      firmware
								      tx
								      statistics
								      gathering
								     */
	UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_RX = 0x00000008/* Enable
								      firmware
								      rx
								      statistics
								      gathering
								    */
पूर्ण;

/* UCC GETH Pad and CRC Mode - Note, Padding without CRC is not possible */
क्रमागत ucc_geth_maccfg2_pad_and_crc_mode अणु
	UCC_GETH_PAD_AND_CRC_MODE_NONE
		= MACCFG2_PAD_AND_CRC_MODE_NONE,	/* Neither Padding
							   लघु frames
							   nor CRC */
	UCC_GETH_PAD_AND_CRC_MODE_CRC_ONLY
		= MACCFG2_PAD_AND_CRC_MODE_CRC_ONLY,	/* Append
							   CRC only */
	UCC_GETH_PAD_AND_CRC_MODE_PAD_AND_CRC =
	    MACCFG2_PAD_AND_CRC_MODE_PAD_AND_CRC
पूर्ण;

/* UCC GETH upsmr Flow Control Mode */
क्रमागत ucc_geth_flow_control_mode अणु
	UPSMR_AUTOMATIC_FLOW_CONTROL_MODE_NONE = 0x00000000,	/* No स्वतःmatic
								   flow control
								 */
	UPSMR_AUTOMATIC_FLOW_CONTROL_MODE_PAUSE_WHEN_EMERGENCY
		= 0x00004000	/* Send छोड़ो frame when RxFIFO reaches its
				   emergency threshold */
पूर्ण;

/* UCC GETH number of thपढ़ोs */
क्रमागत ucc_geth_num_of_thपढ़ोs अणु
	UCC_GETH_NUM_OF_THREADS_1 = 0x1,	/* 1 */
	UCC_GETH_NUM_OF_THREADS_2 = 0x2,	/* 2 */
	UCC_GETH_NUM_OF_THREADS_4 = 0x0,	/* 4 */
	UCC_GETH_NUM_OF_THREADS_6 = 0x3,	/* 6 */
	UCC_GETH_NUM_OF_THREADS_8 = 0x4	/* 8 */
पूर्ण;

/* UCC GETH number of station addresses */
क्रमागत ucc_geth_num_of_station_addresses अणु
	UCC_GETH_NUM_OF_STATION_ADDRESSES_1,	/* 1 */
	UCC_GETH_NUM_OF_STATION_ADDRESSES_5	/* 5 */
पूर्ण;

/* UCC GETH 82xx Ethernet Address Container */
काष्ठा enet_addr_container अणु
	u8 address[ETH_ALEN];	/* ethernet address */
	क्रमागत ucc_geth_enet_address_recognition_location location;	/* location in
								   82xx address
								   recognition
								   hardware */
	काष्ठा list_head node;
पूर्ण;

#घोषणा ENET_ADDR_CONT_ENTRY(ptr) list_entry(ptr, काष्ठा enet_addr_container, node)

/* UCC GETH Termination Action Descriptor (TAD) काष्ठाure. */
काष्ठा ucc_geth_tad_params अणु
	पूर्णांक rx_non_dynamic_extended_features_mode;
	पूर्णांक reject_frame;
	क्रमागत ucc_geth_vlan_operation_tagged vtag_op;
	क्रमागत ucc_geth_vlan_operation_non_tagged vnontag_op;
	क्रमागत ucc_geth_qos_mode rqos;
	u8 vpri;
	u16 vid;
पूर्ण;

/* GETH protocol initialization काष्ठाure */
काष्ठा ucc_geth_info अणु
	काष्ठा ucc_fast_info uf_info;
	पूर्णांक ipCheckSumCheck;
	पूर्णांक ipCheckSumGenerate;
	पूर्णांक rxExtendedFiltering;
	u32 extendedFilteringChainPoपूर्णांकer;
	u16 typeorlen;
	पूर्णांक dynamicMaxFrameLength;
	पूर्णांक dynamicMinFrameLength;
	u8 nonBackToBackIfgPart1;
	u8 nonBackToBackIfgPart2;
	u8 miminumInterFrameGapEnक्रमcement;
	u8 backToBackInterFrameGap;
	पूर्णांक ipAddressAlignment;
	पूर्णांक lengthCheckRx;
	u32 mblपूर्णांकerval;
	u16 nortsrbyteसमय;
	u8 fracsiz;
	u8 strictpriorityq;
	u8 txasap;
	u8 extrabw;
	पूर्णांक miiPreambleSupress;
	u8 altBebTruncation;
	पूर्णांक altBeb;
	पूर्णांक backPressureNoBackoff;
	पूर्णांक noBackoff;
	पूर्णांक excessDefer;
	u8 maxRetransmission;
	u8 collisionWinकरोw;
	पूर्णांक pro;
	पूर्णांक cap;
	पूर्णांक rsh;
	पूर्णांक rlpb;
	पूर्णांक cam;
	पूर्णांक bro;
	पूर्णांक ecm;
	पूर्णांक receiveFlowControl;
	पूर्णांक transmitFlowControl;
	u8 maxGroupAddrInHash;
	u8 maxIndAddrInHash;
	u8 prel;
	u16 maxFrameLength;
	u16 minFrameLength;
	u16 maxD1Length;
	u16 maxD2Length;
	u16 vlantype;
	u16 vlantci;
	u32 ecamptr;
	u32 eventRegMask;
	u16 छोड़ोPeriod;
	u16 extensionField;
	काष्ठा device_node *phy_node;
	काष्ठा device_node *tbi_node;
	u8 weightfactor[NUM_TX_QUEUES];
	u8 पूर्णांकerruptcoalescingmaxvalue[NUM_RX_QUEUES];
	u8 l2qt[UCC_GETH_VLAN_PRIORITY_MAX];
	u8 l3qt[UCC_GETH_IP_PRIORITY_MAX];
	u32 vtagtable[UCC_GETH_TX_VTAG_TABLE_ENTRY_MAX];
	u8 iphoffset[TX_IP_OFFSET_ENTRY_MAX];
	u16 bdRingLenTx[NUM_TX_QUEUES];
	u16 bdRingLenRx[NUM_RX_QUEUES];
	क्रमागत ucc_geth_num_of_station_addresses numStationAddresses;
	क्रमागत qe_fltr_largest_बाह्यal_tbl_lookup_key_size
	    largestबाह्यallookupkeysize;
	क्रमागत ucc_geth_statistics_gathering_mode statisticsMode;
	क्रमागत ucc_geth_vlan_operation_tagged vlanOperationTagged;
	क्रमागत ucc_geth_vlan_operation_non_tagged vlanOperationNonTagged;
	क्रमागत ucc_geth_qos_mode rxQoSMode;
	क्रमागत ucc_geth_flow_control_mode aufc;
	क्रमागत ucc_geth_maccfg2_pad_and_crc_mode padAndCrc;
	क्रमागत ucc_geth_num_of_thपढ़ोs numThपढ़ोsTx;
	क्रमागत ucc_geth_num_of_thपढ़ोs numThपढ़ोsRx;
	अचिन्हित पूर्णांक riscTx;
	अचिन्हित पूर्णांक riscRx;
पूर्ण;

/* काष्ठाure representing UCC GETH */
काष्ठा ucc_geth_निजी अणु
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_fast_निजी *uccf;
	काष्ठा device *dev;
	काष्ठा net_device *ndev;
	काष्ठा napi_काष्ठा napi;
	काष्ठा work_काष्ठा समयout_work;
	काष्ठा ucc_geth __iomem *ug_regs;
	काष्ठा ucc_geth_init_pram *p_init_enet_param_shaकरोw;
	काष्ठा ucc_geth_exf_global_pram __iomem *p_exf_glbl_param;
	u32 exf_glbl_param_offset;
	काष्ठा ucc_geth_rx_global_pram __iomem *p_rx_glbl_pram;
	काष्ठा ucc_geth_tx_global_pram __iomem *p_tx_glbl_pram;
	काष्ठा ucc_geth_send_queue_mem_region __iomem *p_send_q_mem_reg;
	u32 send_q_mem_reg_offset;
	काष्ठा ucc_geth_thपढ़ो_data_tx __iomem *p_thपढ़ो_data_tx;
	u32 thपढ़ो_dat_tx_offset;
	काष्ठा ucc_geth_thपढ़ो_data_rx __iomem *p_thपढ़ो_data_rx;
	u32 thपढ़ो_dat_rx_offset;
	काष्ठा ucc_geth_scheduler __iomem *p_scheduler;
	u32 scheduler_offset;
	काष्ठा ucc_geth_tx_firmware_statistics_pram __iomem *p_tx_fw_statistics_pram;
	u32 tx_fw_statistics_pram_offset;
	काष्ठा ucc_geth_rx_firmware_statistics_pram __iomem *p_rx_fw_statistics_pram;
	u32 rx_fw_statistics_pram_offset;
	काष्ठा ucc_geth_rx_पूर्णांकerrupt_coalescing_table __iomem *p_rx_irq_coalescing_tbl;
	u32 rx_irq_coalescing_tbl_offset;
	काष्ठा ucc_geth_rx_bd_queues_entry __iomem *p_rx_bd_qs_tbl;
	u32 rx_bd_qs_tbl_offset;
	u8 __iomem *p_tx_bd_ring[NUM_TX_QUEUES];
	u8 __iomem *p_rx_bd_ring[NUM_RX_QUEUES];
	u8 __iomem *confBd[NUM_TX_QUEUES];
	u8 __iomem *txBd[NUM_TX_QUEUES];
	u8 __iomem *rxBd[NUM_RX_QUEUES];
	पूर्णांक badFrame[NUM_RX_QUEUES];
	u16 cpucount[NUM_TX_QUEUES];
	u16 __iomem *p_cpucount[NUM_TX_QUEUES];
	पूर्णांक indAddrRegUsed[NUM_OF_PADDRS];
	u8 paddr[NUM_OF_PADDRS][ETH_ALEN];	/* ethernet address */
	u8 numGroupAddrInHash;
	u8 numIndAddrInHash;
	u8 numIndAddrInReg;
	पूर्णांक rx_extended_features;
	पूर्णांक rx_non_dynamic_extended_features;
	काष्ठा list_head conf_skbs;
	काष्ठा list_head group_hash_q;
	काष्ठा list_head ind_hash_q;
	u32 saved_uccm;
	spinlock_t lock;
	/* poपूर्णांकers to arrays of skbuffs क्रम tx and rx */
	काष्ठा sk_buff **tx_skbuff[NUM_TX_QUEUES];
	काष्ठा sk_buff **rx_skbuff[NUM_RX_QUEUES];
	/* indices poपूर्णांकing to the next मुक्त sbk in skb arrays */
	u16 skb_curtx[NUM_TX_QUEUES];
	u16 skb_currx[NUM_RX_QUEUES];
	/* index of the first skb which hasn't been transmitted yet. */
	u16 skb_dirtytx[NUM_TX_QUEUES];

	काष्ठा ugeth_mii_info *mii_info;
	काष्ठा phy_device *phydev;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	पूर्णांक max_speed;
	uपूर्णांक32_t msg_enable;
	पूर्णांक oldspeed;
	पूर्णांक oldduplex;
	पूर्णांक oldlink;
	पूर्णांक wol_en;

	काष्ठा device_node *node;
पूर्ण;

व्योम uec_set_ethtool_ops(काष्ठा net_device *netdev);
पूर्णांक init_flow_control_params(u32 स्वतःmatic_flow_control_mode,
		पूर्णांक rx_flow_control_enable, पूर्णांक tx_flow_control_enable,
		u16 छोड़ो_period, u16 extension_field,
		u32 __iomem *upsmr_रेजिस्टर, u32 __iomem *uempr_रेजिस्टर,
		u32 __iomem *maccfg1_रेजिस्टर);


#पूर्ण_अगर				/* __UCC_GETH_H__ */
