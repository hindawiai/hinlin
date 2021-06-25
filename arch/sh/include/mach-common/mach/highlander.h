<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_RENESAS_R7780RP_H
#घोषणा __ASM_SH_RENESAS_R7780RP_H

/* Box specअगरic addresses.  */
#घोषणा PA_NORFLASH_ADDR	0x00000000
#घोषणा PA_NORFLASH_SIZE	0x04000000

#अगर defined(CONFIG_SH_R7780MP)
#घोषणा PA_BCR          0xa4000000      /* FPGA */
#घोषणा PA_SDPOW	(-1)

#घोषणा PA_IRLMSK       (PA_BCR+0x0000) /* Interrupt Mask control */
#घोषणा PA_IRLMON       (PA_BCR+0x0002) /* Interrupt Status control */
#घोषणा PA_IRLPRI1      (PA_BCR+0x0004) /* Interrupt Priorty 1 */
#घोषणा PA_IRLPRI2      (PA_BCR+0x0006) /* Interrupt Priorty 2 */
#घोषणा PA_IRLPRI3      (PA_BCR+0x0008) /* Interrupt Priorty 3 */
#घोषणा PA_IRLPRI4      (PA_BCR+0x000a) /* Interrupt Priorty 4 */
#घोषणा PA_RSTCTL       (PA_BCR+0x000c) /* Reset Control */
#घोषणा PA_PCIBD        (PA_BCR+0x000e) /* PCI Board detect control */
#घोषणा PA_PCICD        (PA_BCR+0x0010) /* PCI Connector detect control */
#घोषणा PA_EXTGIO       (PA_BCR+0x0016) /* Extension GPIO Control */
#घोषणा PA_IVDRMON      (PA_BCR+0x0018) /* iVDR Moniter control */
#घोषणा PA_IVDRCTL      (PA_BCR+0x001a) /* iVDR control */
#घोषणा PA_OBLED        (PA_BCR+0x001c) /* On Board LED control */
#घोषणा PA_OBSW         (PA_BCR+0x001e) /* On Board Switch control */
#घोषणा PA_AUDIOSEL     (PA_BCR+0x0020) /* Sound Interface Select control */
#घोषणा PA_EXTPLR       (PA_BCR+0x001e) /* Extension Pin Polarity control */
#घोषणा PA_TPCTL        (PA_BCR+0x0100) /* Touch Panel Access control */
#घोषणा PA_TPDCKCTL     (PA_BCR+0x0102) /* Touch Panel Access data control */
#घोषणा PA_TPCTLCLR     (PA_BCR+0x0104) /* Touch Panel Access control */
#घोषणा PA_TPXPOS       (PA_BCR+0x0106) /* Touch Panel X position control */
#घोषणा PA_TPYPOS       (PA_BCR+0x0108) /* Touch Panel Y position control */
#घोषणा PA_DBSW         (PA_BCR+0x0200) /* Debug Board Switch control */
#घोषणा PA_CFCTL        (PA_BCR+0x0300) /* CF Timing control */
#घोषणा PA_CFPOW        (PA_BCR+0x0302) /* CF Power control */
#घोषणा PA_CFCDINTCLR   (PA_BCR+0x0304) /* CF Insert Interrupt clear */
#घोषणा PA_SCSMR0       (PA_BCR+0x0400) /* SCIF0 Serial mode control */
#घोषणा PA_SCBRR0       (PA_BCR+0x0404) /* SCIF0 Bit rate control */
#घोषणा PA_SCSCR0       (PA_BCR+0x0408) /* SCIF0 Serial control */
#घोषणा PA_SCFTDR0      (PA_BCR+0x040c) /* SCIF0 Send FIFO control */
#घोषणा PA_SCFSR0       (PA_BCR+0x0410) /* SCIF0 Serial status control */
#घोषणा PA_SCFRDR0      (PA_BCR+0x0414) /* SCIF0 Receive FIFO control */
#घोषणा PA_SCFCR0       (PA_BCR+0x0418) /* SCIF0 FIFO control */
#घोषणा PA_SCTFDR0      (PA_BCR+0x041c) /* SCIF0 Send FIFO data control */
#घोषणा PA_SCRFDR0      (PA_BCR+0x0420) /* SCIF0 Receive FIFO data control */
#घोषणा PA_SCSPTR0      (PA_BCR+0x0424) /* SCIF0 Serial Port control */
#घोषणा PA_SCLSR0       (PA_BCR+0x0428) /* SCIF0 Line Status control */
#घोषणा PA_SCRER0       (PA_BCR+0x042c) /* SCIF0 Serial Error control */
#घोषणा PA_SCSMR1       (PA_BCR+0x0500) /* SCIF1 Serial mode control */
#घोषणा PA_SCBRR1       (PA_BCR+0x0504) /* SCIF1 Bit rate control */
#घोषणा PA_SCSCR1       (PA_BCR+0x0508) /* SCIF1 Serial control */
#घोषणा PA_SCFTDR1      (PA_BCR+0x050c) /* SCIF1 Send FIFO control */
#घोषणा PA_SCFSR1       (PA_BCR+0x0510) /* SCIF1 Serial status control */
#घोषणा PA_SCFRDR1      (PA_BCR+0x0514) /* SCIF1 Receive FIFO control */
#घोषणा PA_SCFCR1       (PA_BCR+0x0518) /* SCIF1 FIFO control */
#घोषणा PA_SCTFDR1      (PA_BCR+0x051c) /* SCIF1 Send FIFO data control */
#घोषणा PA_SCRFDR1      (PA_BCR+0x0520) /* SCIF1 Receive FIFO data control */
#घोषणा PA_SCSPTR1      (PA_BCR+0x0524) /* SCIF1 Serial Port control */
#घोषणा PA_SCLSR1       (PA_BCR+0x0528) /* SCIF1 Line Status control */
#घोषणा PA_SCRER1       (PA_BCR+0x052c) /* SCIF1 Serial Error control */
#घोषणा PA_SMCR         (PA_BCR+0x0600) /* 2-wire Serial control */
#घोषणा PA_SMSMADR      (PA_BCR+0x0602) /* 2-wire Serial Slave control */
#घोषणा PA_SMMR         (PA_BCR+0x0604) /* 2-wire Serial Mode control */
#घोषणा PA_SMSADR1      (PA_BCR+0x0606) /* 2-wire Serial Address1 control */
#घोषणा PA_SMTRDR1      (PA_BCR+0x0646) /* 2-wire Serial Data1 control */
#घोषणा PA_VERREG       (PA_BCR+0x0700) /* FPGA Version Register */
#घोषणा PA_POFF         (PA_BCR+0x0800) /* System Power Off control */
#घोषणा PA_PMR          (PA_BCR+0x0900) /*  */

#घोषणा IRLCNTR1        (PA_BCR + 0)    /* Interrupt Control Register1 */
#घोषणा IVDR_CK_ON	8		/* iVDR Clock ON */

#या_अगर defined(CONFIG_SH_R7780RP)
#घोषणा PA_POFF		(-1)

#घोषणा PA_BCR		0xa5000000	/* FPGA */
#घोषणा	PA_IRLMSK	(PA_BCR+0x0000)	/* Interrupt Mask control */
#घोषणा PA_IRLMON	(PA_BCR+0x0002)	/* Interrupt Status control */
#घोषणा	PA_SDPOW	(PA_BCR+0x0004)	/* SD Power control */
#घोषणा	PA_RSTCTL	(PA_BCR+0x0006)	/* Device Reset control */
#घोषणा	PA_PCIBD	(PA_BCR+0x0008)	/* PCI Board detect control */
#घोषणा	PA_PCICD	(PA_BCR+0x000a)	/* PCI Connector detect control */
#घोषणा	PA_ZIGIO1	(PA_BCR+0x000c)	/* Zigbee IO control 1 */
#घोषणा	PA_ZIGIO2	(PA_BCR+0x000e)	/* Zigbee IO control 2 */
#घोषणा	PA_ZIGIO3	(PA_BCR+0x0010)	/* Zigbee IO control 3 */
#घोषणा	PA_ZIGIO4	(PA_BCR+0x0012)	/* Zigbee IO control 4 */
#घोषणा	PA_IVDRMON	(PA_BCR+0x0014)	/* iVDR Moniter control */
#घोषणा	PA_IVDRCTL	(PA_BCR+0x0016)	/* iVDR control */
#घोषणा PA_OBLED	(PA_BCR+0x0018)	/* On Board LED control */
#घोषणा PA_OBSW		(PA_BCR+0x001a)	/* On Board Switch control */
#घोषणा PA_AUDIOSEL	(PA_BCR+0x001c)	/* Sound Interface Select control */
#घोषणा PA_EXTPLR	(PA_BCR+0x001e)	/* Extension Pin Polarity control */
#घोषणा PA_TPCTL	(PA_BCR+0x0100)	/* Touch Panel Access control */
#घोषणा PA_TPDCKCTL	(PA_BCR+0x0102)	/* Touch Panel Access data control */
#घोषणा PA_TPCTLCLR	(PA_BCR+0x0104)	/* Touch Panel Access control */
#घोषणा PA_TPXPOS	(PA_BCR+0x0106)	/* Touch Panel X position control */
#घोषणा PA_TPYPOS	(PA_BCR+0x0108)	/* Touch Panel Y position control */
#घोषणा PA_DBDET	(PA_BCR+0x0200)	/* Debug Board detect control */
#घोषणा PA_DBDISPCTL	(PA_BCR+0x0202)	/* Debug Board Dot timing control */
#घोषणा PA_DBSW		(PA_BCR+0x0204)	/* Debug Board Switch control */
#घोषणा PA_CFCTL	(PA_BCR+0x0300)	/* CF Timing control */
#घोषणा PA_CFPOW	(PA_BCR+0x0302)	/* CF Power control */
#घोषणा PA_CFCDINTCLR	(PA_BCR+0x0304)	/* CF Insert Interrupt clear */
#घोषणा PA_SCSMR	(PA_BCR+0x0400)	/* SCIF Serial mode control */
#घोषणा PA_SCBRR	(PA_BCR+0x0402)	/* SCIF Bit rate control */
#घोषणा PA_SCSCR	(PA_BCR+0x0404)	/* SCIF Serial control */
#घोषणा PA_SCFDTR	(PA_BCR+0x0406)	/* SCIF Send FIFO control */
#घोषणा PA_SCFSR	(PA_BCR+0x0408)	/* SCIF Serial status control */
#घोषणा PA_SCFRDR	(PA_BCR+0x040a)	/* SCIF Receive FIFO control */
#घोषणा PA_SCFCR	(PA_BCR+0x040c)	/* SCIF FIFO control */
#घोषणा PA_SCFDR	(PA_BCR+0x040e)	/* SCIF FIFO data control */
#घोषणा PA_SCLSR	(PA_BCR+0x0412)	/* SCIF Line Status control */
#घोषणा PA_SMCR		(PA_BCR+0x0500)	/* 2-wire Serial control */
#घोषणा PA_SMSMADR	(PA_BCR+0x0502)	/* 2-wire Serial Slave control */
#घोषणा PA_SMMR		(PA_BCR+0x0504)	/* 2-wire Serial Mode control */
#घोषणा PA_SMSADR1	(PA_BCR+0x0506)	/* 2-wire Serial Address1 control */
#घोषणा PA_SMTRDR1	(PA_BCR+0x0546)	/* 2-wire Serial Data1 control */
#घोषणा PA_VERREG	(PA_BCR+0x0600)	/* FPGA Version Register */

#घोषणा PA_AX88796L	0xa5800400	/* AX88796L Area */
#घोषणा PA_SC1602BSLB	0xa6000000	/* SC1602BSLB Area */
#घोषणा PA_IDE_OFFSET	0x1f0		/* CF IDE Offset */
#घोषणा AX88796L_IO_BASE	0x1000	/* AX88796L IO Base Address */

#घोषणा IRLCNTR1	(PA_BCR + 0)	/* Interrupt Control Register1 */

#घोषणा IVDR_CK_ON	8		/* iVDR Clock ON */

#या_अगर defined(CONFIG_SH_R7785RP)
#घोषणा PA_BCR		0xa4000000	/* FPGA */
#घोषणा PA_SDPOW	(-1)

#घोषणा	PA_PCISCR	(PA_BCR+0x0000)
#घोषणा PA_IRLPRA	(PA_BCR+0x0002)
#घोषणा	PA_IRLPRB	(PA_BCR+0x0004)
#घोषणा	PA_IRLPRC	(PA_BCR+0x0006)
#घोषणा	PA_IRLPRD	(PA_BCR+0x0008)
#घोषणा IRLCNTR1	(PA_BCR+0x0010)
#घोषणा	PA_IRLPRE	(PA_BCR+0x000a)
#घोषणा	PA_IRLPRF	(PA_BCR+0x000c)
#घोषणा	PA_EXIRLCR	(PA_BCR+0x000e)
#घोषणा	PA_IRLMCR1	(PA_BCR+0x0010)
#घोषणा	PA_IRLMCR2	(PA_BCR+0x0012)
#घोषणा	PA_IRLSSR1	(PA_BCR+0x0014)
#घोषणा	PA_IRLSSR2	(PA_BCR+0x0016)
#घोषणा PA_CFTCR	(PA_BCR+0x0100)
#घोषणा PA_CFPCR	(PA_BCR+0x0102)
#घोषणा PA_PCICR	(PA_BCR+0x0110)
#घोषणा PA_IVDRCTL	(PA_BCR+0x0112)
#घोषणा PA_IVDRSR	(PA_BCR+0x0114)
#घोषणा PA_PDRSTCR	(PA_BCR+0x0116)
#घोषणा PA_POFF		(PA_BCR+0x0120)
#घोषणा PA_LCDCR	(PA_BCR+0x0130)
#घोषणा PA_TPCR		(PA_BCR+0x0140)
#घोषणा PA_TPCKCR	(PA_BCR+0x0142)
#घोषणा PA_TPRSTR	(PA_BCR+0x0144)
#घोषणा PA_TPXPDR	(PA_BCR+0x0146)
#घोषणा PA_TPYPDR	(PA_BCR+0x0148)
#घोषणा PA_GPIOPFR	(PA_BCR+0x0150)
#घोषणा PA_GPIODR	(PA_BCR+0x0152)
#घोषणा PA_OBLED	(PA_BCR+0x0154)
#घोषणा PA_SWSR		(PA_BCR+0x0156)
#घोषणा PA_VERREG	(PA_BCR+0x0158)
#घोषणा PA_SMCR		(PA_BCR+0x0200)
#घोषणा PA_SMSMADR	(PA_BCR+0x0202)
#घोषणा PA_SMMR		(PA_BCR+0x0204)
#घोषणा PA_SMSADR1	(PA_BCR+0x0206)
#घोषणा PA_SMSADR32	(PA_BCR+0x0244)
#घोषणा PA_SMTRDR1	(PA_BCR+0x0246)
#घोषणा PA_SMTRDR16	(PA_BCR+0x0264)
#घोषणा PA_CU3MDR	(PA_BCR+0x0300)
#घोषणा PA_CU5MDR	(PA_BCR+0x0302)
#घोषणा PA_MMSR		(PA_BCR+0x0400)

#घोषणा IVDR_CK_ON	4		/* iVDR Clock ON */
#पूर्ण_अगर

#घोषणा HL_FPGA_IRQ_BASE	200
#घोषणा HL_NR_IRL		15

#घोषणा IRQ_AX88796		(HL_FPGA_IRQ_BASE + 0)
#घोषणा IRQ_CF			(HL_FPGA_IRQ_BASE + 1)
#घोषणा IRQ_PSW			(HL_FPGA_IRQ_BASE + 2)
#घोषणा IRQ_EXT0		(HL_FPGA_IRQ_BASE + 3)
#घोषणा IRQ_EXT1		(HL_FPGA_IRQ_BASE + 4)
#घोषणा IRQ_EXT2		(HL_FPGA_IRQ_BASE + 5)
#घोषणा IRQ_EXT3		(HL_FPGA_IRQ_BASE + 6)
#घोषणा IRQ_EXT4		(HL_FPGA_IRQ_BASE + 7)
#घोषणा IRQ_EXT5		(HL_FPGA_IRQ_BASE + 8)
#घोषणा IRQ_EXT6		(HL_FPGA_IRQ_BASE + 9)
#घोषणा IRQ_EXT7		(HL_FPGA_IRQ_BASE + 10)
#घोषणा IRQ_SMBUS		(HL_FPGA_IRQ_BASE + 11)
#घोषणा IRQ_TP			(HL_FPGA_IRQ_BASE + 12)
#घोषणा IRQ_RTC			(HL_FPGA_IRQ_BASE + 13)
#घोषणा IRQ_TH_ALERT		(HL_FPGA_IRQ_BASE + 14)
#घोषणा IRQ_SCIF0		(HL_FPGA_IRQ_BASE + 15)
#घोषणा IRQ_SCIF1		(HL_FPGA_IRQ_BASE + 16)

अचिन्हित अक्षर *highlander_plat_irq_setup(व्योम);

#अगर_घोषित CONFIG_SH_R7785RP
व्योम highlander_plat_pinmux_setup(व्योम);
#अन्यथा
#घोषणा highlander_plat_pinmux_setup()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर  /* __ASM_SH_RENESAS_R7780RP */
