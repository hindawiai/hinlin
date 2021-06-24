<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * mc.h: Definitions क्रम SGI Memory Controller
 *
 * Copyright (C) 1996 David S. Miller
 * Copyright (C) 1999 Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */

#अगर_अघोषित _SGI_MC_H
#घोषणा _SGI_MC_H

काष्ठा sgimc_regs अणु
	u32 _unused0;
	अस्थिर u32 cpuctrl0;	/* CPU control रेजिस्टर 0, पढ़ोग_लिखो */
#घोषणा SGIMC_CCTRL0_REFS	0x0000000f /* REFS mask */
#घोषणा SGIMC_CCTRL0_EREFRESH	0x00000010 /* Memory refresh enable */
#घोषणा SGIMC_CCTRL0_EPERRGIO	0x00000020 /* GIO parity error enable */
#घोषणा SGIMC_CCTRL0_EPERRMEM	0x00000040 /* Main mem parity error enable */
#घोषणा SGIMC_CCTRL0_EPERRCPU	0x00000080 /* CPU bus parity error enable */
#घोषणा SGIMC_CCTRL0_WDOG	0x00000100 /* Watchकरोg समयr enable */
#घोषणा SGIMC_CCTRL0_SYSINIT	0x00000200 /* System init bit */
#घोषणा SGIMC_CCTRL0_GFXRESET	0x00000400 /* Graphics पूर्णांकerface reset */
#घोषणा SGIMC_CCTRL0_EISALOCK	0x00000800 /* Lock CPU from memory क्रम EISA */
#घोषणा SGIMC_CCTRL0_EPERRSCMD	0x00001000 /* SysCMD bus parity error enable */
#घोषणा SGIMC_CCTRL0_IENAB	0x00002000 /* Allow पूर्णांकerrupts from MC */
#घोषणा SGIMC_CCTRL0_ESNOOP	0x00004000 /* Snooping I/O enable */
#घोषणा SGIMC_CCTRL0_EPROMWR	0x00008000 /* Prom ग_लिखोs from cpu enable */
#घोषणा SGIMC_CCTRL0_WRESETPMEM 0x00010000 /* Perक्रमm warm reset, preserves mem */
#घोषणा SGIMC_CCTRL0_LENDIAN	0x00020000 /* Put MC in little-endian mode */
#घोषणा SGIMC_CCTRL0_WRESETDMEM 0x00040000 /* Warm reset, destroys mem contents */
#घोषणा SGIMC_CCTRL0_CMEMBADPAR 0x02000000 /* Generate bad perr from cpu to mem */
#घोषणा SGIMC_CCTRL0_R4KNOCHKPARR 0x04000000 /* Don't chk parity on mem data पढ़ोs */
#घोषणा SGIMC_CCTRL0_GIOBTOB	0x08000000 /* Allow GIO back to back ग_लिखोs */
	u32 _unused1;
	अस्थिर u32 cpuctrl1;	/* CPU control रेजिस्टर 1, पढ़ोग_लिखो */
#घोषणा SGIMC_CCTRL1_EGIOTIMEO	0x00000010 /* GIO bus समयout enable */
#घोषणा SGIMC_CCTRL1_FIXEDEHPC	0x00001000 /* Fixed HPC endianness */
#घोषणा SGIMC_CCTRL1_LITTLEHPC	0x00002000 /* Little endian HPC */
#घोषणा SGIMC_CCTRL1_FIXEDEEXP0 0x00004000 /* Fixed EXP0 endianness */
#घोषणा SGIMC_CCTRL1_LITTLEEXP0 0x00008000 /* Little endian EXP0 */
#घोषणा SGIMC_CCTRL1_FIXEDEEXP1 0x00010000 /* Fixed EXP1 endianness */
#घोषणा SGIMC_CCTRL1_LITTLEEXP1 0x00020000 /* Little endian EXP1 */

	u32 _unused2;
	अस्थिर u32 watchकरोgt; /* Watchकरोg reg rकरोnly, ग_लिखो clears */

	u32 _unused3;
	अस्थिर u32 प्रणालीid;	/* MC प्रणाली ID रेजिस्टर, पढ़ोonly */
#घोषणा SGIMC_SYSID_MASKREV	0x0000000f /* Revision of MC controller */
#घोषणा SGIMC_SYSID_EPRESENT	0x00000010 /* Indicates presence of EISA bus */

	u32 _unused4[3];
	अस्थिर u32 भागider;	/* Divider reg क्रम RPSS */

	u32 _unused5;
	u32 eeprom;		/* EEPROM byte reg क्रम r4k */
#घोषणा SGIMC_EEPROM_PRE	0x00000001 /* eeprom chip PRE pin निश्चितion */
#घोषणा SGIMC_EEPROM_CSEL	0x00000002 /* Active high, eeprom chip select */
#घोषणा SGIMC_EEPROM_SECLOCK	0x00000004 /* EEPROM serial घड़ी */
#घोषणा SGIMC_EEPROM_SDATAO	0x00000008 /* Serial EEPROM data-out */
#घोषणा SGIMC_EEPROM_SDATAI	0x00000010 /* Serial EEPROM data-in */

	u32 _unused6[3];
	अस्थिर u32 rcntpre;	/* Preload refresh counter */

	u32 _unused7;
	अस्थिर u32 rcounter;	/* Reaकरोnly refresh counter */

	u32 _unused8[13];
	अस्थिर u32 giopar;	/* Parameter word क्रम GIO64 */
#घोषणा SGIMC_GIOPAR_HPC64	0x00000001 /* HPC talks to GIO using 64-bits */
#घोषणा SGIMC_GIOPAR_GFX64	0x00000002 /* GFX talks to GIO using 64-bits */
#घोषणा SGIMC_GIOPAR_EXP064	0x00000004 /* EXP(slot0) talks using 64-bits */
#घोषणा SGIMC_GIOPAR_EXP164	0x00000008 /* EXP(slot1) talks using 64-bits */
#घोषणा SGIMC_GIOPAR_EISA64	0x00000010 /* EISA bus talks 64-bits to GIO */
#घोषणा SGIMC_GIOPAR_HPC264	0x00000020 /* 2nd HPX talks 64-bits to GIO */
#घोषणा SGIMC_GIOPAR_RTIMEGFX	0x00000040 /* GFX device has realसमय attr */
#घोषणा SGIMC_GIOPAR_RTIMEEXP0	0x00000080 /* EXP(slot0) has realसमय attr */
#घोषणा SGIMC_GIOPAR_RTIMEEXP1	0x00000100 /* EXP(slot1) has realसमय attr */
#घोषणा SGIMC_GIOPAR_MASTEREISA 0x00000200 /* EISA bus can act as bus master */
#घोषणा SGIMC_GIOPAR_ONEBUS	0x00000400 /* Exists one GIO64 pipelined bus */
#घोषणा SGIMC_GIOPAR_MASTERGFX	0x00000800 /* GFX can act as a bus master */
#घोषणा SGIMC_GIOPAR_MASTEREXP0 0x00001000 /* EXP(slot0) can bus master */
#घोषणा SGIMC_GIOPAR_MASTEREXP1 0x00002000 /* EXP(slot1) can bus master */
#घोषणा SGIMC_GIOPAR_PLINEEXP0	0x00004000 /* EXP(slot0) has pipeline attr */
#घोषणा SGIMC_GIOPAR_PLINEEXP1	0x00008000 /* EXP(slot1) has pipeline attr */

	u32 _unused9;
	अस्थिर u32 cputp;	/* CPU bus arb समय period */

	u32 _unused10[3];
	अस्थिर u32 lbursttp;	/* Time period क्रम दीर्घ bursts */

	/* MC chip can drive up to 4 bank 4 SIMMs each. All SIMMs in bank must
	 * be the same size. The size encoding क्रम supported SIMMs is bellow */
	u32 _unused11[9];
	अस्थिर u32 mconfig0;	/* Memory config रेजिस्टर zero */
	u32 _unused12;
	अस्थिर u32 mconfig1;	/* Memory config रेजिस्टर one */
#घोषणा SGIMC_MCONFIG_BASEADDR	0x000000ff /* Base address of bank*/
#घोषणा SGIMC_MCONFIG_RMASK	0x00001f00 /* Ram config biपंचांगask */
#घोषणा SGIMC_MCONFIG_BVALID	0x00002000 /* Bank is valid */
#घोषणा SGIMC_MCONFIG_SBANKS	0x00004000 /* Number of subbanks */

	u32 _unused13;
	अस्थिर u32 cmacc;	   /* Mem access config क्रम CPU */
	u32 _unused14;
	अस्थिर u32 gmacc;	   /* Mem access config क्रम GIO */

	/* This define applies to both cmacc and gmacc रेजिस्टरs above. */
#घोषणा SGIMC_MACC_ALIASBIG	0x20000000 /* 512MB home क्रम alias */

	/* Error address/status regs from GIO and CPU perspectives. */
	u32 _unused15;
	अस्थिर u32 cerr;	/* Error address reg क्रम CPU */
	u32 _unused16;
	अस्थिर u32 cstat;	/* Status reg क्रम CPU */
#घोषणा SGIMC_CSTAT_RD		0x00000100 /* पढ़ो parity error */
#घोषणा SGIMC_CSTAT_PAR		0x00000200 /* CPU parity error */
#घोषणा SGIMC_CSTAT_ADDR	0x00000400 /* memory bus error bad addr */
#घोषणा SGIMC_CSTAT_SYSAD_PAR	0x00000800 /* sysad parity error */
#घोषणा SGIMC_CSTAT_SYSCMD_PAR	0x00001000 /* syscmd parity error */
#घोषणा SGIMC_CSTAT_BAD_DATA	0x00002000 /* bad data identअगरier */
#घोषणा SGIMC_CSTAT_PAR_MASK	0x00001f00 /* parity error mask */
#घोषणा SGIMC_CSTAT_RD_PAR	(SGIMC_CSTAT_RD | SGIMC_CSTAT_PAR)

	u32 _unused17;
	अस्थिर u32 gerr;	/* Error address reg क्रम GIO */
	u32 _unused18;
	अस्थिर u32 gstat;	/* Status reg क्रम GIO */
#घोषणा SGIMC_GSTAT_RD		0x00000100 /* पढ़ो parity error */
#घोषणा SGIMC_GSTAT_WR		0x00000200 /* ग_लिखो parity error */
#घोषणा SGIMC_GSTAT_TIME	0x00000400 /* GIO bus समयd out */
#घोषणा SGIMC_GSTAT_PROM	0x00000800 /* ग_लिखो to PROM when PROM_EN not set */
#घोषणा SGIMC_GSTAT_ADDR	0x00001000 /* parity error on addr cycle */
#घोषणा SGIMC_GSTAT_BC		0x00002000 /* parity error on byte count cycle */
#घोषणा SGIMC_GSTAT_PIO_RD	0x00004000 /* पढ़ो data parity on pio */
#घोषणा SGIMC_GSTAT_PIO_WR	0x00008000 /* ग_लिखो data parity on pio */

	/* Special hard bus locking रेजिस्टरs. */
	u32 _unused19;
	अस्थिर u32 syssembit;		/* Uni-bit प्रणाली semaphore */
	u32 _unused20;
	अस्थिर u32 mlock;		/* Global GIO memory access lock */
	u32 _unused21;
	अस्थिर u32 elock;		/* Locks EISA from GIO accesses */

	/* GIO dma control रेजिस्टरs. */
	u32 _unused22[15];
	अस्थिर u32 gio_dma_trans;	/* DMA mask to translation GIO addrs */
	u32 _unused23;
	अस्थिर u32 gio_dma_sbits;	/* DMA GIO addr substitution bits */
	u32 _unused24;
	अस्थिर u32 dma_पूर्णांकr_cause;	/* DMA IRQ cause indicator bits */
	u32 _unused25;
	अस्थिर u32 dma_ctrl;		/* Main DMA control reg */

	/* DMA TLB entry 0 */
	u32 _unused26[5];
	अस्थिर u32 dtlb_hi0;
	u32 _unused27;
	अस्थिर u32 dtlb_lo0;

	/* DMA TLB entry 1 */
	u32 _unused28;
	अस्थिर u32 dtlb_hi1;
	u32 _unused29;
	अस्थिर u32 dtlb_lo1;

	/* DMA TLB entry 2 */
	u32 _unused30;
	अस्थिर u32 dtlb_hi2;
	u32 _unused31;
	अस्थिर u32 dtlb_lo2;

	/* DMA TLB entry 3 */
	u32 _unused32;
	अस्थिर u32 dtlb_hi3;
	u32 _unused33;
	अस्थिर u32 dtlb_lo3;

	u32 _unused34[0x0392];

	u32 _unused35;
	अस्थिर u32 rpsscounter;	/* Chirps at 100ns */

	u32 _unused36[0x1000/4-2*4];

	u32 _unused37;
	अस्थिर u32 maddronly;		/* Address DMA goes at */
	u32 _unused38;
	अस्थिर u32 maddrpdeflts;	/* Same as above, plus set शेषs */
	u32 _unused39;
	अस्थिर u32 dmasz;		/* DMA count */
	u32 _unused40;
	अस्थिर u32 ssize;		/* DMA stride size */
	u32 _unused41;
	अस्थिर u32 gmaddronly;	/* Set GIO DMA but करोn't start trans */
	u32 _unused42;
	अस्थिर u32 dmaddnpgo;		/* Set GIO DMA addr + start transfer */
	u32 _unused43;
	अस्थिर u32 dmamode;		/* DMA mode config bit settings */
	u32 _unused44;
	अस्थिर u32 dmaccount;		/* Zoom and byte count क्रम DMA */
	u32 _unused45;
	अस्थिर u32 dmastart;		/* Pedal to the metal. */
	u32 _unused46;
	अस्थिर u32 dmarunning;	/* DMA op is in progress */
	u32 _unused47;
	अस्थिर u32 maddrdefstart;	/* Set dma addr, शेषs, and kick it */
पूर्ण;

बाह्य काष्ठा sgimc_regs *sgimc;
#घोषणा SGIMC_BASE		0x1fa00000	/* physical */

/* Base location of the two ram banks found in IP2[0268] machines. */
#घोषणा SGIMC_SEG0_BADDR	0x08000000
#घोषणा SGIMC_SEG1_BADDR	0x20000000

/* Maximum size of the above banks are per machine. */
#घोषणा SGIMC_SEG0_SIZE_ALL		0x10000000 /* 256MB */
#घोषणा SGIMC_SEG1_SIZE_IP20_IP22	0x08000000 /* 128MB */
#घोषणा SGIMC_SEG1_SIZE_IP26_IP28	0x20000000 /* 512MB */

बाह्य व्योम sgimc_init(व्योम);

#पूर्ण_अगर /* _SGI_MC_H */
