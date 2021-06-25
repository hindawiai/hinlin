<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * QUICC Engine (QE) Internal Memory Map.
 * The Internal Memory Map क्रम devices with QE on them. This
 * is the superset of all QE devices (8360, etc.).

 * Copyright (C) 2006. Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 */
#अगर_अघोषित _ASM_POWERPC_IMMAP_QE_H
#घोषणा _ASM_POWERPC_IMMAP_QE_H
#अगर_घोषित __KERNEL__

#समावेश <linux/kernel.h>
#समावेश <यंत्र/पन.स>

#घोषणा QE_IMMAP_SIZE	(1024 * 1024)	/* 1MB from 1MB+IMMR */

/* QE I-RAM */
काष्ठा qe_iram अणु
	__be32	iadd;		/* I-RAM Address Register */
	__be32	idata;		/* I-RAM Data Register */
	u8	res0[0x04];
	__be32	iपढ़ोy;		/* I-RAM Ready Register */
	u8	res1[0x70];
पूर्ण __attribute__ ((packed));

/* QE Interrupt Controller */
काष्ठा qe_ic_regs अणु
	__be32	qicr;
	__be32	qivec;
	__be32	qripnr;
	__be32	qipnr;
	__be32	qipxcc;
	__be32	qipycc;
	__be32	qipwcc;
	__be32	qipzcc;
	__be32	qimr;
	__be32	qrimr;
	__be32	qicnr;
	u8	res0[0x4];
	__be32	qiprta;
	__be32	qiprtb;
	u8	res1[0x4];
	__be32	qricr;
	u8	res2[0x20];
	__be32	qhivec;
	u8	res3[0x1C];
पूर्ण __attribute__ ((packed));

/* Communications Processor */
काष्ठा cp_qe अणु
	__be32	cecr;		/* QE command रेजिस्टर */
	__be32	ceccr;		/* QE controller configuration रेजिस्टर */
	__be32	cecdr;		/* QE command data रेजिस्टर */
	u8	res0[0xA];
	__be16	ceter;		/* QE समयr event रेजिस्टर */
	u8	res1[0x2];
	__be16	ceपंचांगr;		/* QE समयrs mask रेजिस्टर */
	__be32	cetscr;		/* QE समय-stamp समयr control रेजिस्टर */
	__be32	cetsr1;		/* QE समय-stamp रेजिस्टर 1 */
	__be32	cetsr2;		/* QE समय-stamp रेजिस्टर 2 */
	u8	res2[0x8];
	__be32	cevter;		/* QE भव tasks event रेजिस्टर */
	__be32	cevपंचांगr;		/* QE भव tasks mask रेजिस्टर */
	__be16	cercr;		/* QE RAM control रेजिस्टर */
	u8	res3[0x2];
	u8	res4[0x24];
	__be16	ceexe1;		/* QE बाह्यal request 1 event रेजिस्टर */
	u8	res5[0x2];
	__be16	ceexm1;		/* QE बाह्यal request 1 mask रेजिस्टर */
	u8	res6[0x2];
	__be16	ceexe2;		/* QE बाह्यal request 2 event रेजिस्टर */
	u8	res7[0x2];
	__be16	ceexm2;		/* QE बाह्यal request 2 mask रेजिस्टर */
	u8	res8[0x2];
	__be16	ceexe3;		/* QE बाह्यal request 3 event रेजिस्टर */
	u8	res9[0x2];
	__be16	ceexm3;		/* QE बाह्यal request 3 mask रेजिस्टर */
	u8	res10[0x2];
	__be16	ceexe4;		/* QE बाह्यal request 4 event रेजिस्टर */
	u8	res11[0x2];
	__be16	ceexm4;		/* QE बाह्यal request 4 mask रेजिस्टर */
	u8	res12[0x3A];
	__be32	ceurnr;		/* QE microcode revision number रेजिस्टर */
	u8	res13[0x244];
पूर्ण __attribute__ ((packed));

/* QE Multiplexer */
काष्ठा qe_mux अणु
	__be32	cmxgcr;		/* CMX general घड़ी route रेजिस्टर */
	__be32	cmxsi1cr_l;	/* CMX SI1 घड़ी route low रेजिस्टर */
	__be32	cmxsi1cr_h;	/* CMX SI1 घड़ी route high रेजिस्टर */
	__be32	cmxsi1syr;	/* CMX SI1 SYNC route रेजिस्टर */
	__be32	cmxucr[4];	/* CMX UCCx घड़ी route रेजिस्टरs */
	__be32	cmxupcr;	/* CMX UPC घड़ी route रेजिस्टर */
	u8	res0[0x1C];
पूर्ण __attribute__ ((packed));

/* QE Timers */
काष्ठा qe_समयrs अणु
	u8	gtcfr1;		/* Timer 1 and Timer 2 global config रेजिस्टर*/
	u8	res0[0x3];
	u8	gtcfr2;		/* Timer 3 and समयr 4 global config रेजिस्टर*/
	u8	res1[0xB];
	__be16	gपंचांगdr1;		/* Timer 1 mode रेजिस्टर */
	__be16	gपंचांगdr2;		/* Timer 2 mode रेजिस्टर */
	__be16	gtrfr1;		/* Timer 1 reference रेजिस्टर */
	__be16	gtrfr2;		/* Timer 2 reference रेजिस्टर */
	__be16	gtcpr1;		/* Timer 1 capture रेजिस्टर */
	__be16	gtcpr2;		/* Timer 2 capture रेजिस्टर */
	__be16	gtcnr1;		/* Timer 1 counter */
	__be16	gtcnr2;		/* Timer 2 counter */
	__be16	gपंचांगdr3;		/* Timer 3 mode रेजिस्टर */
	__be16	gपंचांगdr4;		/* Timer 4 mode रेजिस्टर */
	__be16	gtrfr3;		/* Timer 3 reference रेजिस्टर */
	__be16	gtrfr4;		/* Timer 4 reference रेजिस्टर */
	__be16	gtcpr3;		/* Timer 3 capture रेजिस्टर */
	__be16	gtcpr4;		/* Timer 4 capture रेजिस्टर */
	__be16	gtcnr3;		/* Timer 3 counter */
	__be16	gtcnr4;		/* Timer 4 counter */
	__be16	gtevr1;		/* Timer 1 event रेजिस्टर */
	__be16	gtevr2;		/* Timer 2 event रेजिस्टर */
	__be16	gtevr3;		/* Timer 3 event रेजिस्टर */
	__be16	gtevr4;		/* Timer 4 event रेजिस्टर */
	__be16	gtps;		/* Timer 1 prescale रेजिस्टर */
	u8 res2[0x46];
पूर्ण __attribute__ ((packed));

/* BRG */
काष्ठा qe_brg अणु
	__be32	brgc[16];	/* BRG configuration रेजिस्टरs */
	u8	res0[0x40];
पूर्ण __attribute__ ((packed));

/* SPI */
काष्ठा spi अणु
	u8	res0[0x20];
	__be32	spmode;		/* SPI mode रेजिस्टर */
	u8	res1[0x2];
	u8	spie;		/* SPI event रेजिस्टर */
	u8	res2[0x1];
	u8	res3[0x2];
	u8	spim;		/* SPI mask रेजिस्टर */
	u8	res4[0x1];
	u8	res5[0x1];
	u8	spcom;		/* SPI command रेजिस्टर */
	u8	res6[0x2];
	__be32	spitd;		/* SPI transmit data रेजिस्टर (cpu mode) */
	__be32	spird;		/* SPI receive data रेजिस्टर (cpu mode) */
	u8	res7[0x8];
पूर्ण __attribute__ ((packed));

/* SI */
काष्ठा si1 अणु
	__be16	sixmr1[4];	/* SI1 TDMx (x = A B C D) mode रेजिस्टर */
	u8	siglmr1_h;	/* SI1 global mode रेजिस्टर high */
	u8	res0[0x1];
	u8	sicmdr1_h;	/* SI1 command रेजिस्टर high */
	u8	res2[0x1];
	u8	sistr1_h;	/* SI1 status रेजिस्टर high */
	u8	res3[0x1];
	__be16	sirsr1_h;	/* SI1 RAM shaकरोw address रेजिस्टर high */
	u8	sitarc1;	/* SI1 RAM counter Tx TDMA */
	u8	sitbrc1;	/* SI1 RAM counter Tx TDMB */
	u8	sitcrc1;	/* SI1 RAM counter Tx TDMC */
	u8	sitdrc1;	/* SI1 RAM counter Tx TDMD */
	u8	sirarc1;	/* SI1 RAM counter Rx TDMA */
	u8	sirbrc1;	/* SI1 RAM counter Rx TDMB */
	u8	sircrc1;	/* SI1 RAM counter Rx TDMC */
	u8	sirdrc1;	/* SI1 RAM counter Rx TDMD */
	u8	res4[0x8];
	__be16	siemr1;		/* SI1 TDME mode रेजिस्टर 16 bits */
	__be16	sअगरmr1;		/* SI1 TDMF mode रेजिस्टर 16 bits */
	__be16	sigmr1;		/* SI1 TDMG mode रेजिस्टर 16 bits */
	__be16	sihmr1;		/* SI1 TDMH mode रेजिस्टर 16 bits */
	u8	siglmg1_l;	/* SI1 global mode रेजिस्टर low 8 bits */
	u8	res5[0x1];
	u8	sicmdr1_l;	/* SI1 command रेजिस्टर low 8 bits */
	u8	res6[0x1];
	u8	sistr1_l;	/* SI1 status रेजिस्टर low 8 bits */
	u8	res7[0x1];
	__be16	sirsr1_l;	/* SI1 RAM shaकरोw address रेजिस्टर low 16 bits*/
	u8	siterc1;	/* SI1 RAM counter Tx TDME 8 bits */
	u8	sitfrc1;	/* SI1 RAM counter Tx TDMF 8 bits */
	u8	sitgrc1;	/* SI1 RAM counter Tx TDMG 8 bits */
	u8	sithrc1;	/* SI1 RAM counter Tx TDMH 8 bits */
	u8	sirerc1;	/* SI1 RAM counter Rx TDME 8 bits */
	u8	sirfrc1;	/* SI1 RAM counter Rx TDMF 8 bits */
	u8	sirgrc1;	/* SI1 RAM counter Rx TDMG 8 bits */
	u8	sirhrc1;	/* SI1 RAM counter Rx TDMH 8 bits */
	u8	res8[0x8];
	__be32	siml1;		/* SI1 multअगरrame limit रेजिस्टर */
	u8	siedm1;		/* SI1 extended diagnostic mode रेजिस्टर */
	u8	res9[0xBB];
पूर्ण __attribute__ ((packed));

/* SI Routing Tables */
काष्ठा sir अणु
	u8 	tx[0x400];
	u8	rx[0x400];
	u8	res0[0x800];
पूर्ण __attribute__ ((packed));

/* USB Controller */
काष्ठा qe_usb_ctlr अणु
	u8	usb_usmod;
	u8	usb_usadr;
	u8	usb_uscom;
	u8	res1[1];
	__be16  usb_usep[4];
	u8	res2[4];
	__be16	usb_usber;
	u8	res3[2];
	__be16	usb_usbmr;
	u8	res4[1];
	u8	usb_usbs;
	__be16	usb_ussft;
	u8	res5[2];
	__be16	usb_usfrn;
	u8	res6[0x22];
पूर्ण __attribute__ ((packed));

/* MCC */
काष्ठा qe_mcc अणु
	__be32	mcce;		/* MCC event रेजिस्टर */
	__be32	mccm;		/* MCC mask रेजिस्टर */
	__be32	mccf;		/* MCC configuration रेजिस्टर */
	__be32	merl;		/* MCC emergency request level रेजिस्टर */
	u8	res0[0xF0];
पूर्ण __attribute__ ((packed));

/* QE UCC Slow */
काष्ठा ucc_slow अणु
	__be32	gumr_l;		/* UCCx general mode रेजिस्टर (low) */
	__be32	gumr_h;		/* UCCx general mode रेजिस्टर (high) */
	__be16	upsmr;		/* UCCx protocol-specअगरic mode रेजिस्टर */
	u8	res0[0x2];
	__be16	utodr;		/* UCCx transmit on demand रेजिस्टर */
	__be16	udsr;		/* UCCx data synchronization रेजिस्टर */
	__be16	ucce;		/* UCCx event रेजिस्टर */
	u8	res1[0x2];
	__be16	uccm;		/* UCCx mask रेजिस्टर */
	u8	res2[0x1];
	u8	uccs;		/* UCCx status रेजिस्टर */
	u8	res3[0x24];
	__be16	utpt;
	u8	res4[0x52];
	u8	guemr;		/* UCC general extended mode रेजिस्टर */
पूर्ण __attribute__ ((packed));

/* QE UCC Fast */
काष्ठा ucc_fast अणु
	__be32	gumr;		/* UCCx general mode रेजिस्टर */
	__be32	upsmr;		/* UCCx protocol-specअगरic mode रेजिस्टर */
	__be16	utodr;		/* UCCx transmit on demand रेजिस्टर */
	u8	res0[0x2];
	__be16	udsr;		/* UCCx data synchronization रेजिस्टर */
	u8	res1[0x2];
	__be32	ucce;		/* UCCx event रेजिस्टर */
	__be32	uccm;		/* UCCx mask रेजिस्टर */
	u8	uccs;		/* UCCx status रेजिस्टर */
	u8	res2[0x7];
	__be32	urfb;		/* UCC receive FIFO base */
	__be16	urfs;		/* UCC receive FIFO size */
	u8	res3[0x2];
	__be16	urfet;		/* UCC receive FIFO emergency threshold */
	__be16	urfset;		/* UCC receive FIFO special emergency
				   threshold */
	__be32	utfb;		/* UCC transmit FIFO base */
	__be16	utfs;		/* UCC transmit FIFO size */
	u8	res4[0x2];
	__be16	utfet;		/* UCC transmit FIFO emergency threshold */
	u8	res5[0x2];
	__be16	utftt;		/* UCC transmit FIFO transmit threshold */
	u8	res6[0x2];
	__be16	utpt;		/* UCC transmit polling समयr */
	u8	res7[0x2];
	__be32	urtry;		/* UCC retry counter रेजिस्टर */
	u8	res8[0x4C];
	u8	guemr;		/* UCC general extended mode रेजिस्टर */
पूर्ण __attribute__ ((packed));

काष्ठा ucc अणु
	जोड़ अणु
		काष्ठा	ucc_slow slow;
		काष्ठा	ucc_fast fast;
		u8	res[0x200];	/* UCC blocks are 512 bytes each */
	पूर्ण;
पूर्ण __attribute__ ((packed));

/* MultiPHY UTOPIA POS Controllers (UPC) */
काष्ठा upc अणु
	__be32	upgcr;		/* UTOPIA/POS general configuration रेजिस्टर */
	__be32	uplpa;		/* UTOPIA/POS last PHY address */
	__be32	uphec;		/* ATM HEC रेजिस्टर */
	__be32	upuc;		/* UTOPIA/POS UCC configuration */
	__be32	updc1;		/* UTOPIA/POS device 1 configuration */
	__be32	updc2;		/* UTOPIA/POS device 2 configuration */
	__be32	updc3;		/* UTOPIA/POS device 3 configuration */
	__be32	updc4;		/* UTOPIA/POS device 4 configuration */
	__be32	upstpa;		/* UTOPIA/POS STPA threshold */
	u8	res0[0xC];
	__be32	updrs1_h;	/* UTOPIA/POS device 1 rate select */
	__be32	updrs1_l;	/* UTOPIA/POS device 1 rate select */
	__be32	updrs2_h;	/* UTOPIA/POS device 2 rate select */
	__be32	updrs2_l;	/* UTOPIA/POS device 2 rate select */
	__be32	updrs3_h;	/* UTOPIA/POS device 3 rate select */
	__be32	updrs3_l;	/* UTOPIA/POS device 3 rate select */
	__be32	updrs4_h;	/* UTOPIA/POS device 4 rate select */
	__be32	updrs4_l;	/* UTOPIA/POS device 4 rate select */
	__be32	updrp1;		/* UTOPIA/POS device 1 receive priority low */
	__be32	updrp2;		/* UTOPIA/POS device 2 receive priority low */
	__be32	updrp3;		/* UTOPIA/POS device 3 receive priority low */
	__be32	updrp4;		/* UTOPIA/POS device 4 receive priority low */
	__be32	upde1;		/* UTOPIA/POS device 1 event */
	__be32	upde2;		/* UTOPIA/POS device 2 event */
	__be32	upde3;		/* UTOPIA/POS device 3 event */
	__be32	upde4;		/* UTOPIA/POS device 4 event */
	__be16	uprp1;
	__be16	uprp2;
	__be16	uprp3;
	__be16	uprp4;
	u8	res1[0x8];
	__be16	uptirr1_0;	/* Device 1 transmit पूर्णांकernal rate 0 */
	__be16	uptirr1_1;	/* Device 1 transmit पूर्णांकernal rate 1 */
	__be16	uptirr1_2;	/* Device 1 transmit पूर्णांकernal rate 2 */
	__be16	uptirr1_3;	/* Device 1 transmit पूर्णांकernal rate 3 */
	__be16	uptirr2_0;	/* Device 2 transmit पूर्णांकernal rate 0 */
	__be16	uptirr2_1;	/* Device 2 transmit पूर्णांकernal rate 1 */
	__be16	uptirr2_2;	/* Device 2 transmit पूर्णांकernal rate 2 */
	__be16	uptirr2_3;	/* Device 2 transmit पूर्णांकernal rate 3 */
	__be16	uptirr3_0;	/* Device 3 transmit पूर्णांकernal rate 0 */
	__be16	uptirr3_1;	/* Device 3 transmit पूर्णांकernal rate 1 */
	__be16	uptirr3_2;	/* Device 3 transmit पूर्णांकernal rate 2 */
	__be16	uptirr3_3;	/* Device 3 transmit पूर्णांकernal rate 3 */
	__be16	uptirr4_0;	/* Device 4 transmit पूर्णांकernal rate 0 */
	__be16	uptirr4_1;	/* Device 4 transmit पूर्णांकernal rate 1 */
	__be16	uptirr4_2;	/* Device 4 transmit पूर्णांकernal rate 2 */
	__be16	uptirr4_3;	/* Device 4 transmit पूर्णांकernal rate 3 */
	__be32	uper1;		/* Device 1 port enable रेजिस्टर */
	__be32	uper2;		/* Device 2 port enable रेजिस्टर */
	__be32	uper3;		/* Device 3 port enable रेजिस्टर */
	__be32	uper4;		/* Device 4 port enable रेजिस्टर */
	u8	res2[0x150];
पूर्ण __attribute__ ((packed));

/* SDMA */
काष्ठा sdma अणु
	__be32	sdsr;		/* Serial DMA status रेजिस्टर */
	__be32	sdmr;		/* Serial DMA mode रेजिस्टर */
	__be32	sdtr1;		/* SDMA प्रणाली bus threshold रेजिस्टर */
	__be32	sdtr2;		/* SDMA secondary bus threshold रेजिस्टर */
	__be32	sdhy1;		/* SDMA प्रणाली bus hysteresis रेजिस्टर */
	__be32	sdhy2;		/* SDMA secondary bus hysteresis रेजिस्टर */
	__be32	sdta1;		/* SDMA प्रणाली bus address रेजिस्टर */
	__be32	sdta2;		/* SDMA secondary bus address रेजिस्टर */
	__be32	sdपंचांग1;		/* SDMA प्रणाली bus MSNUM रेजिस्टर */
	__be32	sdपंचांग2;		/* SDMA secondary bus MSNUM रेजिस्टर */
	u8	res0[0x10];
	__be32	sdaqr;		/* SDMA address bus qualअगरy रेजिस्टर */
	__be32	sdaqmr;		/* SDMA address bus qualअगरy mask रेजिस्टर */
	u8	res1[0x4];
	__be32	sdebcr;		/* SDMA CAM entries base रेजिस्टर */
	u8	res2[0x38];
पूर्ण __attribute__ ((packed));

/* Debug Space */
काष्ठा dbg अणु
	__be32	bpdcr;		/* Breakpoपूर्णांक debug command रेजिस्टर */
	__be32	bpdsr;		/* Breakpoपूर्णांक debug status रेजिस्टर */
	__be32	bpdmr;		/* Breakpoपूर्णांक debug mask रेजिस्टर */
	__be32	bprmrr0;	/* Breakpoपूर्णांक request mode risc रेजिस्टर 0 */
	__be32	bprmrr1;	/* Breakpoपूर्णांक request mode risc रेजिस्टर 1 */
	u8	res0[0x8];
	__be32	bprmtr0;	/* Breakpoपूर्णांक request mode trb रेजिस्टर 0 */
	__be32	bprmtr1;	/* Breakpoपूर्णांक request mode trb रेजिस्टर 1 */
	u8	res1[0x8];
	__be32	bprmir;		/* Breakpoपूर्णांक request mode immediate रेजिस्टर */
	__be32	bprmsr;		/* Breakpoपूर्णांक request mode serial रेजिस्टर */
	__be32	bpemr;		/* Breakpoपूर्णांक निकास mode रेजिस्टर */
	u8	res2[0x48];
पूर्ण __attribute__ ((packed));

/*
 * RISC Special Registers (Trap and Breakpoपूर्णांक).  These are described in
 * the QE Developer's Handbook.
 */
काष्ठा rsp अणु
	__be32 tibcr[16];	/* Trap/inकाष्ठाion अवरोधpoपूर्णांक control regs */
	u8 res0[64];
	__be32 ibcr0;
	__be32 ibs0;
	__be32 ibcnr0;
	u8 res1[4];
	__be32 ibcr1;
	__be32 ibs1;
	__be32 ibcnr1;
	__be32 npcr;
	__be32 dbcr;
	__be32 dbar;
	__be32 dbamr;
	__be32 dbsr;
	__be32 dbcnr;
	u8 res2[12];
	__be32 dbdr_h;
	__be32 dbdr_l;
	__be32 dbdmr_h;
	__be32 dbdmr_l;
	__be32 bsr;
	__be32 bor;
	__be32 bior;
	u8 res3[4];
	__be32 iatr[4];
	__be32 eccr;		/* Exception control configuration रेजिस्टर */
	__be32 eicr;
	u8 res4[0x100-0xf8];
पूर्ण __attribute__ ((packed));

काष्ठा qe_immap अणु
	काष्ठा qe_iram		iram;		/* I-RAM */
	काष्ठा qe_ic_regs	ic;		/* Interrupt Controller */
	काष्ठा cp_qe		cp;		/* Communications Processor */
	काष्ठा qe_mux		qmx;		/* QE Multiplexer */
	काष्ठा qe_समयrs	qet;		/* QE Timers */
	काष्ठा spi		spi[0x2];	/* spi */
	काष्ठा qe_mcc		mcc;		/* mcc */
	काष्ठा qe_brg		brg;		/* brg */
	काष्ठा qe_usb_ctlr	usb;		/* USB */
	काष्ठा si1		si1;		/* SI */
	u8			res11[0x800];
	काष्ठा sir		sir;		/* SI Routing Tables */
	काष्ठा ucc		ucc1;		/* ucc1 */
	काष्ठा ucc		ucc3;		/* ucc3 */
	काष्ठा ucc		ucc5;		/* ucc5 */
	काष्ठा ucc		ucc7;		/* ucc7 */
	u8			res12[0x600];
	काष्ठा upc		upc1;		/* MultiPHY UTOPIA POS Ctrlr 1*/
	काष्ठा ucc		ucc2;		/* ucc2 */
	काष्ठा ucc		ucc4;		/* ucc4 */
	काष्ठा ucc		ucc6;		/* ucc6 */
	काष्ठा ucc		ucc8;		/* ucc8 */
	u8			res13[0x600];
	काष्ठा upc		upc2;		/* MultiPHY UTOPIA POS Ctrlr 2*/
	काष्ठा sdma		sdma;		/* SDMA */
	काष्ठा dbg		dbg;		/* 0x104080 - 0x1040FF
						   Debug Space */
	काष्ठा rsp		rsp[0x2];	/* 0x104100 - 0x1042FF
						   RISC Special Registers
						   (Trap and Breakpoपूर्णांक) */
	u8			res14[0x300];	/* 0x104300 - 0x1045FF */
	u8			res15[0x3A00];	/* 0x104600 - 0x107FFF */
	u8			res16[0x8000];	/* 0x108000 - 0x110000 */
	u8			muram[0xC000];	/* 0x110000 - 0x11C000
						   Multi-user RAM */
	u8			res17[0x24000];	/* 0x11C000 - 0x140000 */
	u8			res18[0xC0000];	/* 0x140000 - 0x200000 */
पूर्ण __attribute__ ((packed));

बाह्य काष्ठा qe_immap __iomem *qe_immr;

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_IMMAP_QE_H */
