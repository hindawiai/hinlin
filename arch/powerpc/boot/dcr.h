<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_BOOT_DCR_H_
#घोषणा _PPC_BOOT_DCR_H_

#घोषणा mfdcr(rn) \
	(अणु	\
		अचिन्हित दीर्घ rval; \
		यंत्र अस्थिर("mfdcr %0,%1" : "=r"(rval) : "i"(rn)); \
		rval; \
	पूर्ण)
#घोषणा mtdcr(rn, val) \
	यंत्र अस्थिर("mtdcr %0,%1" : : "i"(rn), "r"(val))
#घोषणा mfdcrx(rn) \
	(अणु	\
		अचिन्हित दीर्घ rval; \
		यंत्र अस्थिर("mfdcrx %0,%1" : "=r"(rval) : "r"(rn)); \
		rval; \
	पूर्ण)
#घोषणा mtdcrx(rn, val) \
	(अणु	\
		यंत्र अस्थिर("mtdcrx %0,%1" : : "r"(rn), "r" (val)); \
	पूर्ण)

/* 440GP/440GX SDRAM controller DCRs */
#घोषणा DCRN_SDRAM0_CFGADDR				0x010
#घोषणा DCRN_SDRAM0_CFGDATA				0x011

#घोषणा SDRAM0_READ(offset) (अणु\
	mtdcr(DCRN_SDRAM0_CFGADDR, offset); \
	mfdcr(DCRN_SDRAM0_CFGDATA); पूर्ण)
#घोषणा SDRAM0_WRITE(offset, data) (अणु\
	mtdcr(DCRN_SDRAM0_CFGADDR, offset); \
	mtdcr(DCRN_SDRAM0_CFGDATA, data); पूर्ण)

#घोषणा 	SDRAM0_B0CR				0x40
#घोषणा 	SDRAM0_B1CR				0x44
#घोषणा 	SDRAM0_B2CR				0x48
#घोषणा 	SDRAM0_B3CR				0x4c

अटल स्थिर अचिन्हित दीर्घ sdram_bxcr[] = अणु SDRAM0_B0CR, SDRAM0_B1CR,
					    SDRAM0_B2CR, SDRAM0_B3CR पूर्ण;

#घोषणा			SDRAM_CONFIG_BANK_ENABLE        0x00000001
#घोषणा			SDRAM_CONFIG_SIZE_MASK          0x000e0000
#घोषणा			SDRAM_CONFIG_BANK_SIZE(reg)	\
	(0x00400000 << ((reg & SDRAM_CONFIG_SIZE_MASK) >> 17))

/* 440GP External Bus Controller (EBC) */
#घोषणा DCRN_EBC0_CFGADDR				0x012
#घोषणा DCRN_EBC0_CFGDATA				0x013
#घोषणा   EBC_NUM_BANKS					  8
#घोषणा   EBC_B0CR					  0x00
#घोषणा   EBC_B1CR					  0x01
#घोषणा   EBC_B2CR					  0x02
#घोषणा   EBC_B3CR					  0x03
#घोषणा   EBC_B4CR					  0x04
#घोषणा   EBC_B5CR					  0x05
#घोषणा   EBC_B6CR					  0x06
#घोषणा   EBC_B7CR					  0x07
#घोषणा   EBC_BXCR(n)					  (n)
#घोषणा	    EBC_BXCR_BAS				    0xfff00000
#घोषणा	    EBC_BXCR_BS				  	    0x000e0000
#घोषणा	    EBC_BXCR_BANK_SIZE(reg) \
	(0x100000 << (((reg) & EBC_BXCR_BS) >> 17))
#घोषणा	    EBC_BXCR_BU				  	    0x00018000
#घोषणा	      EBC_BXCR_BU_OFF			  	      0x00000000
#घोषणा	      EBC_BXCR_BU_RO			  	      0x00008000
#घोषणा	      EBC_BXCR_BU_WO			  	      0x00010000
#घोषणा	      EBC_BXCR_BU_RW			  	      0x00018000
#घोषणा	    EBC_BXCR_BW				  	    0x00006000
#घोषणा   EBC_B0AP					  0x10
#घोषणा   EBC_B1AP					  0x11
#घोषणा   EBC_B2AP					  0x12
#घोषणा   EBC_B3AP					  0x13
#घोषणा   EBC_B4AP					  0x14
#घोषणा   EBC_B5AP					  0x15
#घोषणा   EBC_B6AP					  0x16
#घोषणा   EBC_B7AP					  0x17
#घोषणा   EBC_BXAP(n)					  (0x10+(n))
#घोषणा   EBC_BEAR					  0x20
#घोषणा   EBC_BESR					  0x21
#घोषणा   EBC_CFG					  0x23
#घोषणा   EBC_CID					  0x24

/* 440GP Clock, PM, chip control */
#घोषणा DCRN_CPC0_SR					0x0b0
#घोषणा DCRN_CPC0_ER					0x0b1
#घोषणा DCRN_CPC0_FR					0x0b2
#घोषणा DCRN_CPC0_SYS0					0x0e0
#घोषणा	  CPC0_SYS0_TUNE				  0xffc00000
#घोषणा	  CPC0_SYS0_FBDV_MASK				  0x003c0000
#घोषणा	  CPC0_SYS0_FWDVA_MASK				  0x00038000
#घोषणा	  CPC0_SYS0_FWDVB_MASK				  0x00007000
#घोषणा	  CPC0_SYS0_OPDV_MASK				  0x00000c00
#घोषणा	  CPC0_SYS0_EPDV_MASK				  0x00000300
/* Helper macros to compute the actual घड़ी भागider values from the
 * encodings in the CPC0 रेजिस्टर */
#घोषणा	  CPC0_SYS0_FBDV(reg) \
		((((((reg) & CPC0_SYS0_FBDV_MASK) >> 18) - 1) & 0xf) + 1)
#घोषणा	  CPC0_SYS0_FWDVA(reg) \
		(8 - (((reg) & CPC0_SYS0_FWDVA_MASK) >> 15))
#घोषणा	  CPC0_SYS0_FWDVB(reg) \
		(8 - (((reg) & CPC0_SYS0_FWDVB_MASK) >> 12))
#घोषणा	  CPC0_SYS0_OPDV(reg) \
		((((reg) & CPC0_SYS0_OPDV_MASK) >> 10) + 1)
#घोषणा	  CPC0_SYS0_EPDV(reg) \
		((((reg) & CPC0_SYS0_EPDV_MASK) >> 8) + 1)
#घोषणा	  CPC0_SYS0_EXTSL				  0x00000080
#घोषणा	  CPC0_SYS0_RW_MASK				  0x00000060
#घोषणा	  CPC0_SYS0_RL					  0x00000010
#घोषणा	  CPC0_SYS0_ZMIISL_MASK				  0x0000000c
#घोषणा	  CPC0_SYS0_BYPASS				  0x00000002
#घोषणा	  CPC0_SYS0_NTO1				  0x00000001
#घोषणा DCRN_CPC0_SYS1					0x0e1
#घोषणा DCRN_CPC0_CUST0					0x0e2
#घोषणा DCRN_CPC0_CUST1					0x0e3
#घोषणा DCRN_CPC0_STRP0					0x0e4
#घोषणा DCRN_CPC0_STRP1					0x0e5
#घोषणा DCRN_CPC0_STRP2					0x0e6
#घोषणा DCRN_CPC0_STRP3					0x0e7
#घोषणा DCRN_CPC0_GPIO					0x0e8
#घोषणा DCRN_CPC0_PLB					0x0e9
#घोषणा DCRN_CPC0_CR1					0x0ea
#घोषणा DCRN_CPC0_CR0					0x0eb
#घोषणा	  CPC0_CR0_SWE					  0x80000000
#घोषणा	  CPC0_CR0_CETE					  0x40000000
#घोषणा	  CPC0_CR0_U1FCS				  0x20000000
#घोषणा	  CPC0_CR0_U0DTE				  0x10000000
#घोषणा	  CPC0_CR0_U0DRE				  0x08000000
#घोषणा	  CPC0_CR0_U0DC					  0x04000000
#घोषणा	  CPC0_CR0_U1DTE				  0x02000000
#घोषणा	  CPC0_CR0_U1DRE				  0x01000000
#घोषणा	  CPC0_CR0_U1DC					  0x00800000
#घोषणा	  CPC0_CR0_U0EC					  0x00400000
#घोषणा	  CPC0_CR0_U1EC					  0x00200000
#घोषणा	  CPC0_CR0_UDIV_MASK				  0x001f0000
#घोषणा	  CPC0_CR0_UDIV(reg) \
		((((reg) & CPC0_CR0_UDIV_MASK) >> 16) + 1)
#घोषणा DCRN_CPC0_MIRQ0					0x0ec
#घोषणा DCRN_CPC0_MIRQ1					0x0ed
#घोषणा DCRN_CPC0_JTAGID				0x0ef

#घोषणा DCRN_MAL0_CFG					0x180
#घोषणा MAL_RESET 0x80000000

/* 440EP Clock/Power-on Reset regs */
#घोषणा DCRN_CPR0_ADDR	0xc
#घोषणा DCRN_CPR0_DATA	0xd
#घोषणा CPR0_PLLD0	0x60
#घोषणा CPR0_OPBD0	0xc0
#घोषणा CPR0_PERD0	0xe0
#घोषणा CPR0_PRIMBD0	0xa0
#घोषणा CPR0_SCPID	0x120
#घोषणा CPR0_PLLC0	0x40

/* 405GP Clocking/Power Management/Chip Control regs */
#घोषणा DCRN_CPC0_PLLMR 0xb0
#घोषणा DCRN_405_CPC0_CR0 0xb1
#घोषणा DCRN_405_CPC0_CR1 0xb2
#घोषणा DCRN_405_CPC0_PSR 0xb4

/* 405EP Clocking/Power Management/Chip Control regs */
#घोषणा DCRN_CPC0_PLLMR0  0xf0
#घोषणा DCRN_CPC0_PLLMR1  0xf4
#घोषणा DCRN_CPC0_UCR     0xf5

/* 440GX/405EX Clock Control reg */
#घोषणा DCRN_CPR0_CLKUPD				0x020
#घोषणा DCRN_CPR0_PLLC					0x040
#घोषणा DCRN_CPR0_PLLD					0x060
#घोषणा DCRN_CPR0_PRIMAD				0x080
#घोषणा DCRN_CPR0_PRIMBD				0x0a0
#घोषणा DCRN_CPR0_OPBD					0x0c0
#घोषणा DCRN_CPR0_PERD					0x0e0
#घोषणा DCRN_CPR0_MALD					0x100

#घोषणा DCRN_SDR0_CONFIG_ADDR 	0xe
#घोषणा DCRN_SDR0_CONFIG_DATA	0xf

/* SDR पढ़ो/ग_लिखो helper macros */
#घोषणा SDR0_READ(offset) (अणु\
	mtdcr(DCRN_SDR0_CONFIG_ADDR, offset); \
	mfdcr(DCRN_SDR0_CONFIG_DATA); पूर्ण)
#घोषणा SDR0_WRITE(offset, data) (अणु\
	mtdcr(DCRN_SDR0_CONFIG_ADDR, offset); \
	mtdcr(DCRN_SDR0_CONFIG_DATA, data); पूर्ण)

#घोषणा DCRN_SDR0_UART0		0x0120
#घोषणा DCRN_SDR0_UART1		0x0121
#घोषणा DCRN_SDR0_UART2		0x0122
#घोषणा DCRN_SDR0_UART3		0x0123


/* CPRs पढ़ो/ग_लिखो helper macros - based off include/यंत्र-ppc/ibm44x.h */

#घोषणा DCRN_CPR0_CFGADDR				0xc
#घोषणा DCRN_CPR0_CFGDATA				0xd

#घोषणा CPR0_READ(offset) (अणु\
	mtdcr(DCRN_CPR0_CFGADDR, offset); \
	mfdcr(DCRN_CPR0_CFGDATA); पूर्ण)
#घोषणा CPR0_WRITE(offset, data) (अणु\
	mtdcr(DCRN_CPR0_CFGADDR, offset); \
	mtdcr(DCRN_CPR0_CFGDATA, data); पूर्ण)



#पूर्ण_अगर	/* _PPC_BOOT_DCR_H_ */
