<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000 Toshiba Corporation
 */
#अगर_अघोषित __ASM_TXX9_TX3927_H
#घोषणा __ASM_TXX9_TX3927_H

#घोषणा TX3927_REG_BASE 0xfffe0000UL
#घोषणा TX3927_REG_SIZE 0x00010000
#घोषणा TX3927_SDRAMC_REG	(TX3927_REG_BASE + 0x8000)
#घोषणा TX3927_ROMC_REG		(TX3927_REG_BASE + 0x9000)
#घोषणा TX3927_DMA_REG		(TX3927_REG_BASE + 0xb000)
#घोषणा TX3927_IRC_REG		(TX3927_REG_BASE + 0xc000)
#घोषणा TX3927_PCIC_REG		(TX3927_REG_BASE + 0xd000)
#घोषणा TX3927_CCFG_REG		(TX3927_REG_BASE + 0xe000)
#घोषणा TX3927_NR_TMR	3
#घोषणा TX3927_TMR_REG(ch)	(TX3927_REG_BASE + 0xf000 + (ch) * 0x100)
#घोषणा TX3927_NR_SIO	2
#घोषणा TX3927_SIO_REG(ch)	(TX3927_REG_BASE + 0xf300 + (ch) * 0x100)
#घोषणा TX3927_PIO_REG		(TX3927_REG_BASE + 0xf500)

काष्ठा tx3927_sdramc_reg अणु
	अस्थिर अचिन्हित दीर्घ cr[8];
	अस्थिर अचिन्हित दीर्घ tr[3];
	अस्थिर अचिन्हित दीर्घ cmd;
	अस्थिर अचिन्हित दीर्घ smrs[2];
पूर्ण;

काष्ठा tx3927_romc_reg अणु
	अस्थिर अचिन्हित दीर्घ cr[8];
पूर्ण;

काष्ठा tx3927_dma_reg अणु
	काष्ठा tx3927_dma_ch_reg अणु
		अस्थिर अचिन्हित दीर्घ cha;
		अस्थिर अचिन्हित दीर्घ sar;
		अस्थिर अचिन्हित दीर्घ dar;
		अस्थिर अचिन्हित दीर्घ cntr;
		अस्थिर अचिन्हित दीर्घ sair;
		अस्थिर अचिन्हित दीर्घ dair;
		अस्थिर अचिन्हित दीर्घ ccr;
		अस्थिर अचिन्हित दीर्घ csr;
	पूर्ण ch[4];
	अस्थिर अचिन्हित दीर्घ dbr[8];
	अस्थिर अचिन्हित दीर्घ tdhr;
	अस्थिर अचिन्हित दीर्घ mcr;
	अस्थिर अचिन्हित दीर्घ unused0;
पूर्ण;

#समावेश <यंत्र/byteorder.h>

#अगर_घोषित __BIG_ENDIAN
#घोषणा endian_def_s2(e1, e2)	\
	अस्थिर अचिन्हित लघु e1, e2
#घोषणा endian_def_sb2(e1, e2, e3)	\
	अस्थिर अचिन्हित लघु e1;अस्थिर अचिन्हित अक्षर e2, e3
#घोषणा endian_def_b2s(e1, e2, e3)	\
	अस्थिर अचिन्हित अक्षर e1, e2;अस्थिर अचिन्हित लघु e3
#घोषणा endian_def_b4(e1, e2, e3, e4)	\
	अस्थिर अचिन्हित अक्षर e1, e2, e3, e4
#अन्यथा
#घोषणा endian_def_s2(e1, e2)	\
	अस्थिर अचिन्हित लघु e2, e1
#घोषणा endian_def_sb2(e1, e2, e3)	\
	अस्थिर अचिन्हित अक्षर e3, e2;अस्थिर अचिन्हित लघु e1
#घोषणा endian_def_b2s(e1, e2, e3)	\
	अस्थिर अचिन्हित लघु e3;अस्थिर अचिन्हित अक्षर e2, e1
#घोषणा endian_def_b4(e1, e2, e3, e4)	\
	अस्थिर अचिन्हित अक्षर e4, e3, e2, e1
#पूर्ण_अगर

काष्ठा tx3927_pcic_reg अणु
	endian_def_s2(did, vid);
	endian_def_s2(pcistat, pcicmd);
	endian_def_b4(cc, scc, rpli, rid);
	endian_def_b4(unused0, ht, mlt, cls);
	अस्थिर अचिन्हित दीर्घ ioba;		/* +10 */
	अस्थिर अचिन्हित दीर्घ mba;
	अस्थिर अचिन्हित दीर्घ unused1[5];
	endian_def_s2(svid, ssvid);
	अस्थिर अचिन्हित दीर्घ unused2;		/* +30 */
	endian_def_sb2(unused3, unused4, capptr);
	अस्थिर अचिन्हित दीर्घ unused5;
	endian_def_b4(ml, mg, ip, il);
	अस्थिर अचिन्हित दीर्घ unused6;		/* +40 */
	अस्थिर अचिन्हित दीर्घ istat;
	अस्थिर अचिन्हित दीर्घ iim;
	अस्थिर अचिन्हित दीर्घ rrt;
	अस्थिर अचिन्हित दीर्घ unused7[3];		/* +50 */
	अस्थिर अचिन्हित दीर्घ ipbmma;
	अस्थिर अचिन्हित दीर्घ ipbioma;		/* +60 */
	अस्थिर अचिन्हित दीर्घ ilbmma;
	अस्थिर अचिन्हित दीर्घ ilbioma;
	अस्थिर अचिन्हित दीर्घ unused8[9];
	अस्थिर अचिन्हित दीर्घ tc;		/* +90 */
	अस्थिर अचिन्हित दीर्घ tstat;
	अस्थिर अचिन्हित दीर्घ tim;
	अस्थिर अचिन्हित दीर्घ tccmd;
	अस्थिर अचिन्हित दीर्घ pcirrt;		/* +a0 */
	अस्थिर अचिन्हित दीर्घ pcirrt_cmd;
	अस्थिर अचिन्हित दीर्घ pcirrdt;
	अस्थिर अचिन्हित दीर्घ unused9[3];
	अस्थिर अचिन्हित दीर्घ tlboap;
	अस्थिर अचिन्हित दीर्घ tlbiap;
	अस्थिर अचिन्हित दीर्घ tlbmma;		/* +c0 */
	अस्थिर अचिन्हित दीर्घ tlbioma;
	अस्थिर अचिन्हित दीर्घ sc_msg;
	अस्थिर अचिन्हित दीर्घ sc_be;
	अस्थिर अचिन्हित दीर्घ tbl;		/* +d0 */
	अस्थिर अचिन्हित दीर्घ unused10[3];
	अस्थिर अचिन्हित दीर्घ pwmng;		/* +e0 */
	अस्थिर अचिन्हित दीर्घ pwmngs;
	अस्थिर अचिन्हित दीर्घ unused11[6];
	अस्थिर अचिन्हित दीर्घ req_trace;		/* +100 */
	अस्थिर अचिन्हित दीर्घ pbapmc;
	अस्थिर अचिन्हित दीर्घ pbapms;
	अस्थिर अचिन्हित दीर्घ pbapmim;
	अस्थिर अचिन्हित दीर्घ bm;		/* +110 */
	अस्थिर अचिन्हित दीर्घ cpcibrs;
	अस्थिर अचिन्हित दीर्घ cpcibgs;
	अस्थिर अचिन्हित दीर्घ pbacs;
	अस्थिर अचिन्हित दीर्घ iobas;		/* +120 */
	अस्थिर अचिन्हित दीर्घ mbas;
	अस्थिर अचिन्हित दीर्घ lbc;
	अस्थिर अचिन्हित दीर्घ lbstat;
	अस्थिर अचिन्हित दीर्घ lbim;		/* +130 */
	अस्थिर अचिन्हित दीर्घ pcistatim;
	अस्थिर अचिन्हित दीर्घ ica;
	अस्थिर अचिन्हित दीर्घ icd;
	अस्थिर अचिन्हित दीर्घ iiadp;		/* +140 */
	अस्थिर अचिन्हित दीर्घ iscdp;
	अस्थिर अचिन्हित दीर्घ mmas;
	अस्थिर अचिन्हित दीर्घ iomas;
	अस्थिर अचिन्हित दीर्घ ipciaddr;		/* +150 */
	अस्थिर अचिन्हित दीर्घ ipcidata;
	अस्थिर अचिन्हित दीर्घ ipcibe;
पूर्ण;

काष्ठा tx3927_ccfg_reg अणु
	अस्थिर अचिन्हित दीर्घ ccfg;
	अस्थिर अचिन्हित दीर्घ crir;
	अस्थिर अचिन्हित दीर्घ pcfg;
	अस्थिर अचिन्हित दीर्घ tear;
	अस्थिर अचिन्हित दीर्घ pdcr;
पूर्ण;

/*
 * SDRAMC
 */

/*
 * ROMC
 */

/*
 * DMA
 */
/* bits क्रम MCR */
#घोषणा TX3927_DMA_MCR_EIS(ch)	(0x10000000<<(ch))
#घोषणा TX3927_DMA_MCR_DIS(ch)	(0x01000000<<(ch))
#घोषणा TX3927_DMA_MCR_RSFIF	0x00000080
#घोषणा TX3927_DMA_MCR_FIFUM(ch)	(0x00000008<<(ch))
#घोषणा TX3927_DMA_MCR_LE	0x00000004
#घोषणा TX3927_DMA_MCR_RPRT	0x00000002
#घोषणा TX3927_DMA_MCR_MSTEN	0x00000001

/* bits क्रम CCRn */
#घोषणा TX3927_DMA_CCR_DBINH	0x04000000
#घोषणा TX3927_DMA_CCR_SBINH	0x02000000
#घोषणा TX3927_DMA_CCR_CHRST	0x01000000
#घोषणा TX3927_DMA_CCR_RVBYTE	0x00800000
#घोषणा TX3927_DMA_CCR_ACKPOL	0x00400000
#घोषणा TX3927_DMA_CCR_REQPL	0x00200000
#घोषणा TX3927_DMA_CCR_EGREQ	0x00100000
#घोषणा TX3927_DMA_CCR_CHDN	0x00080000
#घोषणा TX3927_DMA_CCR_DNCTL	0x00060000
#घोषणा TX3927_DMA_CCR_EXTRQ	0x00010000
#घोषणा TX3927_DMA_CCR_INTRQD	0x0000e000
#घोषणा TX3927_DMA_CCR_INTENE	0x00001000
#घोषणा TX3927_DMA_CCR_INTENC	0x00000800
#घोषणा TX3927_DMA_CCR_INTENT	0x00000400
#घोषणा TX3927_DMA_CCR_CHNEN	0x00000200
#घोषणा TX3927_DMA_CCR_XFACT	0x00000100
#घोषणा TX3927_DMA_CCR_SNOP	0x00000080
#घोषणा TX3927_DMA_CCR_DSTINC	0x00000040
#घोषणा TX3927_DMA_CCR_SRCINC	0x00000020
#घोषणा TX3927_DMA_CCR_XFSZ(order)	(((order) << 2) & 0x0000001c)
#घोषणा TX3927_DMA_CCR_XFSZ_1W	TX3927_DMA_CCR_XFSZ(2)
#घोषणा TX3927_DMA_CCR_XFSZ_4W	TX3927_DMA_CCR_XFSZ(4)
#घोषणा TX3927_DMA_CCR_XFSZ_8W	TX3927_DMA_CCR_XFSZ(5)
#घोषणा TX3927_DMA_CCR_XFSZ_16W TX3927_DMA_CCR_XFSZ(6)
#घोषणा TX3927_DMA_CCR_XFSZ_32W TX3927_DMA_CCR_XFSZ(7)
#घोषणा TX3927_DMA_CCR_MEMIO	0x00000002
#घोषणा TX3927_DMA_CCR_ONEAD	0x00000001

/* bits क्रम CSRn */
#घोषणा TX3927_DMA_CSR_CHNACT	0x00000100
#घोषणा TX3927_DMA_CSR_ABCHC	0x00000080
#घोषणा TX3927_DMA_CSR_NCHNC	0x00000040
#घोषणा TX3927_DMA_CSR_NTRNFC	0x00000020
#घोषणा TX3927_DMA_CSR_EXTDN	0x00000010
#घोषणा TX3927_DMA_CSR_CFERR	0x00000008
#घोषणा TX3927_DMA_CSR_CHERR	0x00000004
#घोषणा TX3927_DMA_CSR_DESERR	0x00000002
#घोषणा TX3927_DMA_CSR_SORERR	0x00000001

/*
 * IRC
 */
#घोषणा TX3927_IR_INT0	0
#घोषणा TX3927_IR_INT1	1
#घोषणा TX3927_IR_INT2	2
#घोषणा TX3927_IR_INT3	3
#घोषणा TX3927_IR_INT4	4
#घोषणा TX3927_IR_INT5	5
#घोषणा TX3927_IR_SIO0	6
#घोषणा TX3927_IR_SIO1	7
#घोषणा TX3927_IR_SIO(ch)	(6 + (ch))
#घोषणा TX3927_IR_DMA	8
#घोषणा TX3927_IR_PIO	9
#घोषणा TX3927_IR_PCI	10
#घोषणा TX3927_IR_TMR(ch)	(13 + (ch))
#घोषणा TX3927_NUM_IR	16

/*
 * PCIC
 */
/* bits क्रम PCICMD */
/* see PCI_COMMAND_XXX in linux/pci.h */

/* bits क्रम PCISTAT */
/* see PCI_STATUS_XXX in linux/pci.h */
#घोषणा PCI_STATUS_NEW_CAP	0x0010

/* bits क्रम ISTAT/IIM */
#घोषणा TX3927_PCIC_IIM_ALL	0x00001600

/* bits क्रम TC */
#घोषणा TX3927_PCIC_TC_OF16E	0x00000020
#घोषणा TX3927_PCIC_TC_IF8E	0x00000010
#घोषणा TX3927_PCIC_TC_OF8E	0x00000008

/* bits क्रम TSTAT/TIM */
#घोषणा TX3927_PCIC_TIM_ALL	0x0003ffff

/* bits क्रम IOBA/MBA */
/* see PCI_BASE_ADDRESS_XXX in linux/pci.h */

/* bits क्रम PBAPMC */
#घोषणा TX3927_PCIC_PBAPMC_RPBA 0x00000004
#घोषणा TX3927_PCIC_PBAPMC_PBAEN	0x00000002
#घोषणा TX3927_PCIC_PBAPMC_BMCEN	0x00000001

/* bits क्रम LBSTAT/LBIM */
#घोषणा TX3927_PCIC_LBIM_ALL	0x0000003e

/* bits क्रम PCISTATIM (see also PCI_STATUS_XXX in linux/pci.h */
#घोषणा TX3927_PCIC_PCISTATIM_ALL	0x0000f900

/* bits क्रम LBC */
#घोषणा TX3927_PCIC_LBC_IBSE	0x00004000
#घोषणा TX3927_PCIC_LBC_TIBSE	0x00002000
#घोषणा TX3927_PCIC_LBC_TMFBSE	0x00001000
#घोषणा TX3927_PCIC_LBC_HRST	0x00000800
#घोषणा TX3927_PCIC_LBC_SRST	0x00000400
#घोषणा TX3927_PCIC_LBC_EPCAD	0x00000200
#घोषणा TX3927_PCIC_LBC_MSDSE	0x00000100
#घोषणा TX3927_PCIC_LBC_CRR	0x00000080
#घोषणा TX3927_PCIC_LBC_ILMDE	0x00000040
#घोषणा TX3927_PCIC_LBC_ILIDE	0x00000020

#घोषणा TX3927_PCIC_IDSEL_AD_TO_SLOT(ad)	((ad) - 11)
#घोषणा TX3927_PCIC_MAX_DEVNU	TX3927_PCIC_IDSEL_AD_TO_SLOT(32)

/*
 * CCFG
 */
/* CCFG : Chip Configuration */
#घोषणा TX3927_CCFG_TLBOFF	0x00020000
#घोषणा TX3927_CCFG_BEOW	0x00010000
#घोषणा TX3927_CCFG_WR	0x00008000
#घोषणा TX3927_CCFG_TOE 0x00004000
#घोषणा TX3927_CCFG_PCIXARB	0x00002000
#घोषणा TX3927_CCFG_PCI3	0x00001000
#घोषणा TX3927_CCFG_PSNP	0x00000800
#घोषणा TX3927_CCFG_PPRI	0x00000400
#घोषणा TX3927_CCFG_PLLM	0x00000030
#घोषणा TX3927_CCFG_ENDIAN	0x00000004
#घोषणा TX3927_CCFG_HALT	0x00000002
#घोषणा TX3927_CCFG_ACEHOLD	0x00000001

/* PCFG : Pin Configuration */
#घोषणा TX3927_PCFG_SYSCLKEN	0x08000000
#घोषणा TX3927_PCFG_SDRCLKEN_ALL	0x07c00000
#घोषणा TX3927_PCFG_SDRCLKEN(ch)	(0x00400000<<(ch))
#घोषणा TX3927_PCFG_PCICLKEN_ALL	0x003c0000
#घोषणा TX3927_PCFG_PCICLKEN(ch)	(0x00040000<<(ch))
#घोषणा TX3927_PCFG_SELALL	0x0003ffff
#घोषणा TX3927_PCFG_SELCS	0x00020000
#घोषणा TX3927_PCFG_SELDSF	0x00010000
#घोषणा TX3927_PCFG_SELSIOC_ALL 0x0000c000
#घोषणा TX3927_PCFG_SELSIOC(ch) (0x00004000<<(ch))
#घोषणा TX3927_PCFG_SELSIO_ALL	0x00003000
#घोषणा TX3927_PCFG_SELSIO(ch)	(0x00001000<<(ch))
#घोषणा TX3927_PCFG_SELTMR_ALL	0x00000e00
#घोषणा TX3927_PCFG_SELTMR(ch)	(0x00000200<<(ch))
#घोषणा TX3927_PCFG_SELDONE	0x00000100
#घोषणा TX3927_PCFG_INTDMA_ALL	0x000000f0
#घोषणा TX3927_PCFG_INTDMA(ch)	(0x00000010<<(ch))
#घोषणा TX3927_PCFG_SELDMA_ALL	0x0000000f
#घोषणा TX3927_PCFG_SELDMA(ch)	(0x00000001<<(ch))

#घोषणा tx3927_sdramcptr	((काष्ठा tx3927_sdramc_reg *)TX3927_SDRAMC_REG)
#घोषणा tx3927_romcptr		((काष्ठा tx3927_romc_reg *)TX3927_ROMC_REG)
#घोषणा tx3927_dmaptr		((काष्ठा tx3927_dma_reg *)TX3927_DMA_REG)
#घोषणा tx3927_pcicptr		((काष्ठा tx3927_pcic_reg *)TX3927_PCIC_REG)
#घोषणा tx3927_ccfgptr		((काष्ठा tx3927_ccfg_reg *)TX3927_CCFG_REG)
#घोषणा tx3927_sioptr(ch)	((काष्ठा txx927_sio_reg *)TX3927_SIO_REG(ch))
#घोषणा tx3927_pioptr		((काष्ठा txx9_pio_reg __iomem *)TX3927_PIO_REG)

#घोषणा TX3927_REV_PCODE()	(tx3927_ccfgptr->crir >> 16)
#घोषणा TX3927_ROMC_BA(ch)	(tx3927_romcptr->cr[(ch)] & 0xfff00000)
#घोषणा TX3927_ROMC_SIZE(ch)	\
	(0x00100000 << ((tx3927_romcptr->cr[(ch)] >> 8) & 0xf))
#घोषणा TX3927_ROMC_WIDTH(ch)	(32 >> ((tx3927_romcptr->cr[(ch)] >> 7) & 0x1))

व्योम tx3927_wdt_init(व्योम);
व्योम tx3927_setup(व्योम);
व्योम tx3927_समय_init(अचिन्हित पूर्णांक evt_पंचांगrnr, अचिन्हित पूर्णांक src_पंचांगrnr);
व्योम tx3927_sio_init(अचिन्हित पूर्णांक sclk, अचिन्हित पूर्णांक cts_mask);
काष्ठा pci_controller;
व्योम tx3927_pcic_setup(काष्ठा pci_controller *channel,
		       अचिन्हित दीर्घ sdram_size, पूर्णांक extarb);
व्योम tx3927_setup_pcierr_irq(व्योम);
व्योम tx3927_irq_init(व्योम);
व्योम tx3927_mtd_init(पूर्णांक ch);

#पूर्ण_अगर /* __ASM_TXX9_TX3927_H */
