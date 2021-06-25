<शैली गुरु>
/*
** macपूर्णांकs.h -- Macपूर्णांकosh Linux पूर्णांकerrupt handling काष्ठाs and prototypes
**
** Copyright 1997 by Michael Schmitz
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
*/

#अगर_अघोषित _ASM_MACINTS_H_
#घोषणा _ASM_MACINTS_H_

#समावेश <यंत्र/irq.h>

/*
 * Base IRQ number क्रम all Mac68K पूर्णांकerrupt sources. Each source
 * has eight indexes (base -> base+7).
 */

#घोषणा VIA1_SOURCE_BASE	8
#घोषणा VIA2_SOURCE_BASE	16
#घोषणा PSC3_SOURCE_BASE	24
#घोषणा PSC4_SOURCE_BASE	32
#घोषणा PSC5_SOURCE_BASE	40
#घोषणा PSC6_SOURCE_BASE	48
#घोषणा NUBUS_SOURCE_BASE	56
#घोषणा BABOON_SOURCE_BASE	64

/*
 * Maximum IRQ number is BABOON_SOURCE_BASE + 7,
 * giving us IRQs up through 71
 */

#घोषणा NUM_MAC_SOURCES		72

/*
 * clean way to separate IRQ पूर्णांकo its source and index
 */

#घोषणा IRQ_SRC(irq)	(irq >> 3)
#घोषणा	IRQ_IDX(irq)	(irq & 7)

/* VIA1 पूर्णांकerrupts */
#घोषणा IRQ_VIA1_0	  (8)		/* one second पूर्णांक. */
#घोषणा IRQ_VIA1_1        (9)		/* VBlank पूर्णांक. */
#घोषणा IRQ_MAC_VBL	  IRQ_VIA1_1
#घोषणा IRQ_VIA1_2	  (10)		/* ADB SR shअगरts complete */
#घोषणा IRQ_MAC_ADB	  IRQ_VIA1_2
#घोषणा IRQ_MAC_ADB_SR	  IRQ_VIA1_2
#घोषणा IRQ_VIA1_3	  (11)		/* ADB SR CB2 ?? */
#घोषणा IRQ_MAC_ADB_SD	  IRQ_VIA1_3
#घोषणा IRQ_VIA1_4        (12)		/* ADB SR ext. घड़ी pulse */
#घोषणा IRQ_MAC_ADB_CL	  IRQ_VIA1_4
#घोषणा IRQ_VIA1_5	  (13)
#घोषणा IRQ_MAC_TIMER_2	  IRQ_VIA1_5
#घोषणा IRQ_VIA1_6	  (14)
#घोषणा IRQ_MAC_TIMER_1	  IRQ_VIA1_6
#घोषणा IRQ_VIA1_7        (15)

/* VIA2/RBV पूर्णांकerrupts */
#घोषणा IRQ_VIA2_0	  (16)
#घोषणा IRQ_MAC_SCSIDRQ	  IRQ_VIA2_0
#घोषणा IRQ_VIA2_1        (17)
#घोषणा IRQ_MAC_NUBUS	  IRQ_VIA2_1
#घोषणा IRQ_VIA2_2	  (18)
#घोषणा IRQ_VIA2_3	  (19)
#घोषणा IRQ_MAC_SCSI	  IRQ_VIA2_3
#घोषणा IRQ_VIA2_4        (20)
#घोषणा IRQ_VIA2_5	  (21)
#घोषणा IRQ_VIA2_6	  (22)
#घोषणा IRQ_VIA2_7        (23)

/* Level 3 (PSC, AV Macs only) पूर्णांकerrupts */
#घोषणा IRQ_PSC3_0	  (24)
#घोषणा IRQ_MAC_MACE	  IRQ_PSC3_0
#घोषणा IRQ_PSC3_1	  (25)
#घोषणा IRQ_PSC3_2	  (26)
#घोषणा IRQ_PSC3_3	  (27)

/* Level 4 (PSC, AV Macs only) पूर्णांकerrupts */
#घोषणा IRQ_PSC4_0	  (32)
#घोषणा IRQ_PSC4_1	  (33)
#घोषणा IRQ_MAC_SCC_A	  IRQ_PSC4_1
#घोषणा IRQ_PSC4_2	  (34)
#घोषणा IRQ_MAC_SCC_B	  IRQ_PSC4_2
#घोषणा IRQ_PSC4_3	  (35)
#घोषणा IRQ_MAC_MACE_DMA  IRQ_PSC4_3

/* OSS Level 4 पूर्णांकerrupts */
#घोषणा IRQ_MAC_SCC	  (33)

/* Level 5 (PSC, AV Macs only) पूर्णांकerrupts */
#घोषणा IRQ_PSC5_0	  (40)
#घोषणा IRQ_PSC5_1	  (41)
#घोषणा IRQ_PSC5_2	  (42)
#घोषणा IRQ_PSC5_3	  (43)

/* Level 6 (PSC, AV Macs only) पूर्णांकerrupts */
#घोषणा IRQ_PSC6_0	  (48)
#घोषणा IRQ_PSC6_1	  (49)
#घोषणा IRQ_PSC6_2	  (50)
#घोषणा IRQ_PSC6_3	  (51)

/* Nubus पूर्णांकerrupts (cascaded to VIA2) */
#घोषणा IRQ_NUBUS_9	  (56)
#घोषणा IRQ_NUBUS_A	  (57)
#घोषणा IRQ_NUBUS_B	  (58)
#घोषणा IRQ_NUBUS_C	  (59)
#घोषणा IRQ_NUBUS_D	  (60)
#घोषणा IRQ_NUBUS_E	  (61)
#घोषणा IRQ_NUBUS_F	  (62)

/* Baboon पूर्णांकerrupts (cascaded to nubus slot $C) */
#घोषणा IRQ_BABOON_0	  (64)
#घोषणा IRQ_BABOON_1	  (65)
#घोषणा IRQ_BABOON_2	  (66)
#घोषणा IRQ_BABOON_3	  (67)

#घोषणा SLOT2IRQ(x)	  (x + 47)
#घोषणा IRQ2SLOT(x)	  (x - 47)

#पूर्ण_अगर /* यंत्र/macपूर्णांकs.h */
