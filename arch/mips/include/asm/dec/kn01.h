<शैली गुरु>
/*
 * Hardware info about DECstation DS2100/3100 प्रणालीs (otherwise known as
 * pmin/pmax or KN01).
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995,1996 by Paul M. Antoine, some code and definitions
 * are by courtesy of Chris Fraser.
 * Copyright (C) 2002, 2003, 2005  Maciej W. Rozycki
 */
#अगर_अघोषित __ASM_MIPS_DEC_KN01_H
#घोषणा __ASM_MIPS_DEC_KN01_H

#घोषणा KN01_SLOT_BASE	0x10000000
#घोषणा KN01_SLOT_SIZE	0x01000000

/*
 * Address ranges क्रम devices.
 */
#घोषणा KN01_PMASK	(0*KN01_SLOT_SIZE)	/* color plane mask */
#घोषणा KN01_PCC	(1*KN01_SLOT_SIZE)	/* PCC (DC503) cursor */
#घोषणा KN01_VDAC	(2*KN01_SLOT_SIZE)	/* color map */
#घोषणा KN01_RES_3	(3*KN01_SLOT_SIZE)	/* unused */
#घोषणा KN01_RES_4	(4*KN01_SLOT_SIZE)	/* unused */
#घोषणा KN01_RES_5	(5*KN01_SLOT_SIZE)	/* unused */
#घोषणा KN01_RES_6	(6*KN01_SLOT_SIZE)	/* unused */
#घोषणा KN01_ERRADDR	(7*KN01_SLOT_SIZE)	/* ग_लिखो error address */
#घोषणा KN01_LANCE	(8*KN01_SLOT_SIZE)	/* LANCE (Am7990) Ethernet */
#घोषणा KN01_LANCE_MEM	(9*KN01_SLOT_SIZE)	/* LANCE buffer memory */
#घोषणा KN01_SII	(10*KN01_SLOT_SIZE)	/* SII (DC7061) SCSI */
#घोषणा KN01_SII_MEM	(11*KN01_SLOT_SIZE)	/* SII buffer memory */
#घोषणा KN01_DZ11	(12*KN01_SLOT_SIZE)	/* DZ11 (DC7085) serial */
#घोषणा KN01_RTC	(13*KN01_SLOT_SIZE)	/* DS1287 RTC (bytes #0) */
#घोषणा KN01_ESAR	(13*KN01_SLOT_SIZE)	/* MAC address (bytes #1) */
#घोषणा KN01_CSR	(14*KN01_SLOT_SIZE)	/* प्रणाली ctrl & status reg */
#घोषणा KN01_SYS_ROM	(15*KN01_SLOT_SIZE)	/* प्रणाली board ROM */


/*
 * Frame buffer memory address.
 */
#घोषणा KN01_VFB_MEM	0x0fc00000

/*
 * CPU पूर्णांकerrupt bits.
 */
#घोषणा KN01_CPU_INR_BUS	6	/* memory, I/O bus पढ़ो/ग_लिखो errors */
#घोषणा KN01_CPU_INR_VIDEO	6	/* PCC area detect #2 */
#घोषणा KN01_CPU_INR_RTC	5	/* DS1287 RTC */
#घोषणा KN01_CPU_INR_DZ11	4	/* DZ11 (DC7085) serial */
#घोषणा KN01_CPU_INR_LANCE	3	/* LANCE (Am7990) Ethernet */
#घोषणा KN01_CPU_INR_SII	2	/* SII (DC7061) SCSI */


/*
 * System Control & Status Register bits.
 */
#घोषणा KN01_CSR_MNFMOD		(1<<15)	/* MNFMOD manufacturing jumper */
#घोषणा KN01_CSR_STATUS		(1<<14)	/* self-test result status output */
#घोषणा KN01_CSR_PARDIS		(1<<13)	/* parity error disable */
#घोषणा KN01_CSR_CRSRTST	(1<<12)	/* PCC test output */
#घोषणा KN01_CSR_MONO		(1<<11)	/* mono/color fb SIMM installed */
#घोषणा KN01_CSR_MEMERR		(1<<10)	/* ग_लिखो समयout error status & ack*/
#घोषणा KN01_CSR_VINT		(1<<9)	/* PCC area detect #2 status & ack */
#घोषणा KN01_CSR_TXDIS		(1<<8)	/* DZ11 transmit disable */
#घोषणा KN01_CSR_VBGTRG		(1<<2)	/* blue DAC voltage over green (r/o) */
#घोषणा KN01_CSR_VRGTRG		(1<<1)	/* red DAC voltage over green (r/o) */
#घोषणा KN01_CSR_VRGTRB		(1<<0)	/* red DAC voltage over blue (r/o) */
#घोषणा KN01_CSR_LEDS		(0xff<<0) /* ~diagnostic LEDs (w/o) */


#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

काष्ठा pt_regs;

बाह्य u16 cached_kn01_csr;

बाह्य व्योम dec_kn01_be_init(व्योम);
बाह्य पूर्णांक dec_kn01_be_handler(काष्ठा pt_regs *regs, पूर्णांक is_fixup);
बाह्य irqवापस_t dec_kn01_be_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MIPS_DEC_KN01_H */
