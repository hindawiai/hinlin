<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_REGS_AC97_H
#घोषणा __ASM_ARCH_REGS_AC97_H

#समावेश <mach/hardware.h>

/*
 * AC97 Controller रेजिस्टरs
 */

#घोषणा POCR		__REG(0x40500000)  /* PCM Out Control Register */
#घोषणा POCR_FEIE	(1 << 3)	/* FIFO Error Interrupt Enable */
#घोषणा POCR_FSRIE	(1 << 1)	/* FIFO Service Request Interrupt Enable */

#घोषणा PICR		__REG(0x40500004)  /* PCM In Control Register */
#घोषणा PICR_FEIE	(1 << 3)	/* FIFO Error Interrupt Enable */
#घोषणा PICR_FSRIE	(1 << 1)	/* FIFO Service Request Interrupt Enable */

#घोषणा MCCR		__REG(0x40500008)  /* Mic In Control Register */
#घोषणा MCCR_FEIE	(1 << 3)	/* FIFO Error Interrupt Enable */
#घोषणा MCCR_FSRIE	(1 << 1)	/* FIFO Service Request Interrupt Enable */

#घोषणा GCR		__REG(0x4050000C)  /* Global Control Register */
#अगर_घोषित CONFIG_PXA3xx
#घोषणा GCR_CLKBPB	(1 << 31)	/* Internal घड़ी enable */
#पूर्ण_अगर
#घोषणा GCR_nDMAEN	(1 << 24)	/* non DMA Enable */
#घोषणा GCR_CDONE_IE	(1 << 19)	/* Command Done Interrupt Enable */
#घोषणा GCR_SDONE_IE	(1 << 18)	/* Status Done Interrupt Enable */
#घोषणा GCR_SECRDY_IEN	(1 << 9)	/* Secondary Ready Interrupt Enable */
#घोषणा GCR_PRIRDY_IEN	(1 << 8)	/* Primary Ready Interrupt Enable */
#घोषणा GCR_SECRES_IEN	(1 << 5)	/* Secondary Resume Interrupt Enable */
#घोषणा GCR_PRIRES_IEN	(1 << 4)	/* Primary Resume Interrupt Enable */
#घोषणा GCR_ACLINK_OFF	(1 << 3)	/* AC-link Shut Off */
#घोषणा GCR_WARM_RST	(1 << 2)	/* AC97 Warm Reset */
#घोषणा GCR_COLD_RST	(1 << 1)	/* AC'97 Cold Reset (0 = active) */
#घोषणा GCR_GIE		(1 << 0)	/* Codec GPI Interrupt Enable */

#घोषणा POSR		__REG(0x40500010)  /* PCM Out Status Register */
#घोषणा POSR_FIFOE	(1 << 4)	/* FIFO error */
#घोषणा POSR_FSR	(1 << 2)	/* FIFO Service Request */

#घोषणा PISR		__REG(0x40500014)  /* PCM In Status Register */
#घोषणा PISR_FIFOE	(1 << 4)	/* FIFO error */
#घोषणा PISR_EOC	(1 << 3)	/* DMA End-of-Chain (exclusive clear) */
#घोषणा PISR_FSR	(1 << 2)	/* FIFO Service Request */

#घोषणा MCSR		__REG(0x40500018)  /* Mic In Status Register */
#घोषणा MCSR_FIFOE	(1 << 4)	/* FIFO error */
#घोषणा MCSR_EOC	(1 << 3)	/* DMA End-of-Chain (exclusive clear) */
#घोषणा MCSR_FSR	(1 << 2)	/* FIFO Service Request */

#घोषणा GSR		__REG(0x4050001C)  /* Global Status Register */
#घोषणा GSR_CDONE	(1 << 19)	/* Command Done */
#घोषणा GSR_SDONE	(1 << 18)	/* Status Done */
#घोषणा GSR_RDCS	(1 << 15)	/* Read Completion Status */
#घोषणा GSR_BIT3SLT12	(1 << 14)	/* Bit 3 of slot 12 */
#घोषणा GSR_BIT2SLT12	(1 << 13)	/* Bit 2 of slot 12 */
#घोषणा GSR_BIT1SLT12	(1 << 12)	/* Bit 1 of slot 12 */
#घोषणा GSR_SECRES	(1 << 11)	/* Secondary Resume Interrupt */
#घोषणा GSR_PRIRES	(1 << 10)	/* Primary Resume Interrupt */
#घोषणा GSR_SCR		(1 << 9)	/* Secondary Codec Ready */
#घोषणा GSR_PCR		(1 << 8)	/*  Primary Codec Ready */
#घोषणा GSR_MCINT	(1 << 7)	/* Mic In Interrupt */
#घोषणा GSR_POINT	(1 << 6)	/* PCM Out Interrupt */
#घोषणा GSR_PIINT	(1 << 5)	/* PCM In Interrupt */
#घोषणा GSR_ACOFFD	(1 << 3)	/* AC-link Shut Off Done */
#घोषणा GSR_MOINT	(1 << 2)	/* Modem Out Interrupt */
#घोषणा GSR_MIINT	(1 << 1)	/* Modem In Interrupt */
#घोषणा GSR_GSCI	(1 << 0)	/* Codec GPI Status Change Interrupt */

#घोषणा CAR		__REG(0x40500020)  /* CODEC Access Register */
#घोषणा CAR_CAIP	(1 << 0)	/* Codec Access In Progress */

#घोषणा PCDR		__REG(0x40500040)  /* PCM FIFO Data Register */
#घोषणा MCDR		__REG(0x40500060)  /* Mic-in FIFO Data Register */

#घोषणा MOCR		__REG(0x40500100)  /* Modem Out Control Register */
#घोषणा MOCR_FEIE	(1 << 3)	/* FIFO Error */
#घोषणा MOCR_FSRIE	(1 << 1)	/* FIFO Service Request Interrupt Enable */

#घोषणा MICR		__REG(0x40500108)  /* Modem In Control Register */
#घोषणा MICR_FEIE	(1 << 3)	/* FIFO Error */
#घोषणा MICR_FSRIE	(1 << 1)	/* FIFO Service Request Interrupt Enable */

#घोषणा MOSR		__REG(0x40500110)  /* Modem Out Status Register */
#घोषणा MOSR_FIFOE	(1 << 4)	/* FIFO error */
#घोषणा MOSR_FSR	(1 << 2)	/* FIFO Service Request */

#घोषणा MISR		__REG(0x40500118)  /* Modem In Status Register */
#घोषणा MISR_FIFOE	(1 << 4)	/* FIFO error */
#घोषणा MISR_EOC	(1 << 3)	/* DMA End-of-Chain (exclusive clear) */
#घोषणा MISR_FSR	(1 << 2)	/* FIFO Service Request */

#घोषणा MODR		__REG(0x40500140)  /* Modem FIFO Data Register */

#घोषणा PAC_REG_BASE	__REG(0x40500200)  /* Primary Audio Codec */
#घोषणा SAC_REG_BASE	__REG(0x40500300)  /* Secondary Audio Codec */
#घोषणा PMC_REG_BASE	__REG(0x40500400)  /* Primary Modem Codec */
#घोषणा SMC_REG_BASE	__REG(0x40500500)  /* Secondary Modem Codec */

#पूर्ण_अगर /* __ASM_ARCH_REGS_AC97_H */
