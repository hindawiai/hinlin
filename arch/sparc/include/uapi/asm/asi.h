<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SPARC_ASI_H
#घोषणा _SPARC_ASI_H

/* asi.h:  Address Space Identअगरier values क्रम the sparc.
 *
 * Copyright (C) 1995,1996 David S. Miller (davem@caip.rutgers.edu)
 *
 * Pioneer work क्रम sun4m: Paul Hatchman (paul@sfe.com.au)
 * Joपूर्णांक edition क्रम sun4c+sun4m: Pete A. Zaitcev <zaitcev@ipmce.su>
 */

/* The first batch are क्रम the sun4c. */

#घोषणा ASI_शून्य1           0x00
#घोषणा ASI_शून्य2           0x01

/* sun4c and sun4 control रेजिस्टरs and mmu/vac ops */
#घोषणा ASI_CONTROL         0x02
#घोषणा ASI_SEGMAP          0x03
#घोषणा ASI_PTE             0x04
#घोषणा ASI_HWFLUSHSEG      0x05
#घोषणा ASI_HWFLUSHPAGE     0x06
#घोषणा ASI_REGMAP          0x06
#घोषणा ASI_HWFLUSHCONTEXT  0x07

#घोषणा ASI_USERTXT         0x08
#घोषणा ASI_KERNELTXT       0x09
#घोषणा ASI_USERDATA        0x0a
#घोषणा ASI_KERNELDATA      0x0b

/* VAC Cache flushing on sun4c and sun4 */
#घोषणा ASI_FLUSHSEG        0x0c
#घोषणा ASI_FLUSHPG         0x0d
#घोषणा ASI_FLUSHCTX        0x0e

/* SPARCstation-5: only 6 bits are decoded. */
/* wo = Write Only, rw = Read Write;        */
/* ss = Single Size, as = All Sizes;        */
#घोषणा ASI_M_RES00         0x00   /* Don't touch... */
#घोषणा ASI_M_UNA01         0x01   /* Same here... */
#घोषणा ASI_M_MXCC          0x02   /* Access to TI VIKING MXCC रेजिस्टरs */
#घोषणा ASI_M_FLUSH_PROBE   0x03   /* Reference MMU Flush/Probe; rw, ss */
#घोषणा ASI_M_MMUREGS       0x04   /* MMU Registers; rw, ss */
#घोषणा ASI_M_TLBDIAG       0x05   /* MMU TLB only Diagnostics */
#घोषणा ASI_M_DIAGS         0x06   /* Reference MMU Diagnostics */
#घोषणा ASI_M_IODIAG        0x07   /* MMU I/O TLB only Diagnostics */
#घोषणा ASI_M_USERTXT       0x08   /* Same as ASI_USERTXT; rw, as */
#घोषणा ASI_M_KERNELTXT     0x09   /* Same as ASI_KERNELTXT; rw, as */
#घोषणा ASI_M_USERDATA      0x0A   /* Same as ASI_USERDATA; rw, as */
#घोषणा ASI_M_KERNELDATA    0x0B   /* Same as ASI_KERNELDATA; rw, as */
#घोषणा ASI_M_TXTC_TAG      0x0C   /* Inकाष्ठाion Cache Tag; rw, ss */
#घोषणा ASI_M_TXTC_DATA     0x0D   /* Inकाष्ठाion Cache Data; rw, ss */
#घोषणा ASI_M_DATAC_TAG     0x0E   /* Data Cache Tag; rw, ss */
#घोषणा ASI_M_DATAC_DATA    0x0F   /* Data Cache Data; rw, ss */

/* The following cache flushing ASIs work only with the 'sta'
 * inकाष्ठाion. Results are unpredictable क्रम 'swap' and 'ldstuba',
 * so करोn't करो it.
 */

/* These ASI flushes affect बाह्यal caches too. */
#घोषणा ASI_M_FLUSH_PAGE    0x10   /* Flush I&D Cache Line (page); wo, ss */
#घोषणा ASI_M_FLUSH_SEG     0x11   /* Flush I&D Cache Line (seg); wo, ss */
#घोषणा ASI_M_FLUSH_REGION  0x12   /* Flush I&D Cache Line (region); wo, ss */
#घोषणा ASI_M_FLUSH_CTX     0x13   /* Flush I&D Cache Line (context); wo, ss */
#घोषणा ASI_M_FLUSH_USER    0x14   /* Flush I&D Cache Line (user); wo, ss */

/* Block-copy operations are available only on certain V8 cpus. */
#घोषणा ASI_M_BCOPY         0x17   /* Block copy */

/* These affect only the ICACHE and are Ross HyperSparc and TurboSparc specअगरic. */
#घोषणा ASI_M_IFLUSH_PAGE   0x18   /* Flush I Cache Line (page); wo, ss */
#घोषणा ASI_M_IFLUSH_SEG    0x19   /* Flush I Cache Line (seg); wo, ss */
#घोषणा ASI_M_IFLUSH_REGION 0x1A   /* Flush I Cache Line (region); wo, ss */
#घोषणा ASI_M_IFLUSH_CTX    0x1B   /* Flush I Cache Line (context); wo, ss */
#घोषणा ASI_M_IFLUSH_USER   0x1C   /* Flush I Cache Line (user); wo, ss */

/* Block-fill operations are available on certain V8 cpus */
#घोषणा ASI_M_BFILL         0x1F

/* This allows direct access to मुख्य memory, actually 0x20 to 0x2f are
 * the available ASI's for physical ram pass-through, but I don't have
 * any idea what the other ones करो....
 */

#घोषणा ASI_M_BYPASS       0x20   /* Reference MMU bypass; rw, as */
#घोषणा ASI_M_FBMEM        0x29   /* Graphics card frame buffer access */
#घोषणा ASI_M_VMEUS        0x2A   /* VME user 16-bit access */
#घोषणा ASI_M_VMEPS        0x2B   /* VME priv 16-bit access */
#घोषणा ASI_M_VMEUT        0x2C   /* VME user 32-bit access */
#घोषणा ASI_M_VMEPT        0x2D   /* VME priv 32-bit access */
#घोषणा ASI_M_SBUS         0x2E   /* Direct SBus access */
#घोषणा ASI_M_CTL          0x2F   /* Control Space (ECC and MXCC are here) */


/* This is ROSS HyperSparc only. */
#घोषणा ASI_M_FLUSH_IWHOLE 0x31   /* Flush entire ICACHE; wo, ss */

/* Tsunami/Viking/TurboSparc i/d cache flash clear. */
#घोषणा ASI_M_IC_FLCLEAR   0x36
#घोषणा ASI_M_DC_FLCLEAR   0x37

#घोषणा ASI_M_DCDR         0x39   /* Data Cache Diagnostics Register rw, ss */

#घोषणा ASI_M_VIKING_TMP1  0x40	  /* Emulation temporary 1 on Viking */
/* only available on SuperSparc I */
/* #घोषणा ASI_M_VIKING_TMP2  0x41 */  /* Emulation temporary 2 on Viking */

#घोषणा ASI_M_ACTION       0x4c   /* Breakpoपूर्णांक Action Register (GNU/Viking) */

/* LEON ASI */
#घोषणा ASI_LEON_NOCACHE        0x01

#घोषणा ASI_LEON_DCACHE_MISS    0x01

#घोषणा ASI_LEON_CACHEREGS      0x02
#घोषणा ASI_LEON_IFLUSH         0x10
#घोषणा ASI_LEON_DFLUSH         0x11

#घोषणा ASI_LEON_MMUFLUSH       0x18
#घोषणा ASI_LEON_MMUREGS        0x19
#घोषणा ASI_LEON_BYPASS         0x1c
#घोषणा ASI_LEON_FLUSH_PAGE     0x10

/* V9 Architecture mandary ASIs. */
#घोषणा ASI_N			0x04 /* Nucleus				*/
#घोषणा ASI_NL			0x0c /* Nucleus, little endian		*/
#घोषणा ASI_AIUP		0x10 /* Primary, user			*/
#घोषणा ASI_AIUS		0x11 /* Secondary, user			*/
#घोषणा ASI_AIUPL		0x18 /* Primary, user, little endian	*/
#घोषणा ASI_AIUSL		0x19 /* Secondary, user, little endian	*/
#घोषणा ASI_P			0x80 /* Primary, implicit		*/
#घोषणा ASI_S			0x81 /* Secondary, implicit		*/
#घोषणा ASI_PNF			0x82 /* Primary, no fault		*/
#घोषणा ASI_SNF			0x83 /* Secondary, no fault		*/
#घोषणा ASI_PL			0x88 /* Primary, implicit, l-endian	*/
#घोषणा ASI_SL			0x89 /* Secondary, implicit, l-endian	*/
#घोषणा ASI_PNFL		0x8a /* Primary, no fault, l-endian	*/
#घोषणा ASI_SNFL		0x8b /* Secondary, no fault, l-endian	*/

/* SpitFire and later extended ASIs.  The "(III)" marker designates
 * UltraSparc-III and later specअगरic ASIs.  The "(CMT)" marker designates
 * Chip Multi Thपढ़ोing specअगरic ASIs.  "(NG)" designates Niagara specअगरic
 * ASIs, "(4V)" designates SUN4V specअगरic ASIs.  "(NG4)" designates SPARC-T4
 * and later ASIs.
 */
#घोषणा ASI_MCD_PRIV_PRIMARY	0x02 /* (NG7) Privileged MCD version VA	*/
#घोषणा ASI_MCD_REAL		0x05 /* (NG7) Privileged MCD version PA	*/
#घोषणा ASI_PHYS_USE_EC		0x14 /* PADDR, E-cachable		*/
#घोषणा ASI_PHYS_BYPASS_EC_E	0x15 /* PADDR, E-bit			*/
#घोषणा ASI_BLK_AIUP_4V		0x16 /* (4V) Prim, user, block ld/st	*/
#घोषणा ASI_BLK_AIUS_4V		0x17 /* (4V) Sec, user, block ld/st	*/
#घोषणा ASI_PHYS_USE_EC_L	0x1c /* PADDR, E-cachable, little endian*/
#घोषणा ASI_PHYS_BYPASS_EC_E_L	0x1d /* PADDR, E-bit, little endian	*/
#घोषणा ASI_BLK_AIUP_L_4V	0x1e /* (4V) Prim, user, block, l-endian*/
#घोषणा ASI_BLK_AIUS_L_4V	0x1f /* (4V) Sec, user, block, l-endian	*/
#घोषणा ASI_SCRATCHPAD		0x20 /* (4V) Scratch Pad Registers	*/
#घोषणा ASI_MMU			0x21 /* (4V) MMU Context Registers	*/
#घोषणा ASI_BLK_INIT_QUAD_LDD_AIUS 0x23 /* (NG) init-store, twin load,
					 * secondary, user
					 */
#घोषणा ASI_NUCLEUS_QUAD_LDD	0x24 /* Cachable, qword load		*/
#घोषणा ASI_QUEUE		0x25 /* (4V) Interrupt Queue Registers	*/
#घोषणा ASI_QUAD_LDD_PHYS_4V	0x26 /* (4V) Physical, qword load	*/
#घोषणा ASI_NUCLEUS_QUAD_LDD_L	0x2c /* Cachable, qword load, l-endian 	*/
#घोषणा ASI_QUAD_LDD_PHYS_L_4V	0x2e /* (4V) Phys, qword load, l-endian	*/
#घोषणा ASI_PCACHE_DATA_STATUS	0x30 /* (III) PCache data stat RAM diag	*/
#घोषणा ASI_PCACHE_DATA		0x31 /* (III) PCache data RAM diag	*/
#घोषणा ASI_PCACHE_TAG		0x32 /* (III) PCache tag RAM diag	*/
#घोषणा ASI_PCACHE_SNOOP_TAG	0x33 /* (III) PCache snoop tag RAM diag	*/
#घोषणा ASI_QUAD_LDD_PHYS	0x34 /* (III+) PADDR, qword load	*/
#घोषणा ASI_WCACHE_VALID_BITS	0x38 /* (III) WCache Valid Bits diag	*/
#घोषणा ASI_WCACHE_DATA		0x39 /* (III) WCache data RAM diag	*/
#घोषणा ASI_WCACHE_TAG		0x3a /* (III) WCache tag RAM diag	*/
#घोषणा ASI_WCACHE_SNOOP_TAG	0x3b /* (III) WCache snoop tag RAM diag	*/
#घोषणा ASI_QUAD_LDD_PHYS_L	0x3c /* (III+) PADDR, qw-load, l-endian	*/
#घोषणा ASI_SRAM_FAST_INIT	0x40 /* (III+) Fast SRAM init		*/
#घोषणा ASI_CORE_AVAILABLE	0x41 /* (CMT) LP Available		*/
#घोषणा ASI_CORE_ENABLE_STAT	0x41 /* (CMT) LP Enable Status		*/
#घोषणा ASI_CORE_ENABLE		0x41 /* (CMT) LP Enable RW		*/
#घोषणा ASI_XIR_STEERING	0x41 /* (CMT) XIR Steering RW		*/
#घोषणा ASI_CORE_RUNNING_RW	0x41 /* (CMT) LP Running RW		*/
#घोषणा ASI_CORE_RUNNING_W1S	0x41 /* (CMT) LP Running Write-One Set	*/
#घोषणा ASI_CORE_RUNNING_W1C	0x41 /* (CMT) LP Running Write-One Clr	*/
#घोषणा ASI_CORE_RUNNING_STAT	0x41 /* (CMT) LP Running Status		*/
#घोषणा ASI_CMT_ERROR_STEERING	0x41 /* (CMT) Error Steering RW		*/
#घोषणा ASI_DCACHE_INVALIDATE	0x42 /* (III) DCache Invalidate diag	*/
#घोषणा ASI_DCACHE_UTAG		0x43 /* (III) DCache uTag diag		*/
#घोषणा ASI_DCACHE_SNOOP_TAG	0x44 /* (III) DCache snoop tag RAM diag	*/
#घोषणा ASI_LSU_CONTROL		0x45 /* Load-store control unit		*/
#घोषणा ASI_DCU_CONTROL_REG	0x45 /* (III) DCache Unit Control reg	*/
#घोषणा ASI_DCACHE_DATA		0x46 /* DCache data-ram diag access	*/
#घोषणा ASI_DCACHE_TAG		0x47 /* Dcache tag/valid ram diag access*/
#घोषणा ASI_INTR_DISPATCH_STAT	0x48 /* IRQ vector dispatch status	*/
#घोषणा ASI_INTR_RECEIVE	0x49 /* IRQ vector receive status	*/
#घोषणा ASI_UPA_CONFIG		0x4a /* UPA config space		*/
#घोषणा ASI_JBUS_CONFIG		0x4a /* (IIIi) JBUS Config Register	*/
#घोषणा ASI_SAFARI_CONFIG	0x4a /* (III) Safari Config Register	*/
#घोषणा ASI_SAFARI_ADDRESS	0x4a /* (III) Safari Address Register	*/
#घोषणा ASI_ESTATE_ERROR_EN	0x4b /* E-cache error enable space	*/
#घोषणा ASI_AFSR		0x4c /* Async fault status रेजिस्टर	*/
#घोषणा ASI_AFAR		0x4d /* Async fault address रेजिस्टर	*/
#घोषणा ASI_EC_TAG_DATA		0x4e /* E-cache tag/valid ram diag acc	*/
#घोषणा ASI_IMMU		0x50 /* Insn-MMU मुख्य रेजिस्टर space	*/
#घोषणा ASI_IMMU_TSB_8KB_PTR	0x51 /* Insn-MMU 8KB TSB poपूर्णांकer reg	*/
#घोषणा ASI_IMMU_TSB_64KB_PTR	0x52 /* Insn-MMU 64KB TSB poपूर्णांकer reg	*/
#घोषणा ASI_ITLB_DATA_IN	0x54 /* Insn-MMU TLB data in reg	*/
#घोषणा ASI_ITLB_DATA_ACCESS	0x55 /* Insn-MMU TLB data access reg	*/
#घोषणा ASI_ITLB_TAG_READ	0x56 /* Insn-MMU TLB tag पढ़ो reg	*/
#घोषणा ASI_IMMU_DEMAP		0x57 /* Insn-MMU TLB demap		*/
#घोषणा ASI_DMMU		0x58 /* Data-MMU मुख्य रेजिस्टर space	*/
#घोषणा ASI_DMMU_TSB_8KB_PTR	0x59 /* Data-MMU 8KB TSB poपूर्णांकer reg	*/
#घोषणा ASI_DMMU_TSB_64KB_PTR	0x5a /* Data-MMU 16KB TSB poपूर्णांकer reg	*/
#घोषणा ASI_DMMU_TSB_सूचीECT_PTR	0x5b /* Data-MMU TSB direct poपूर्णांकer reg	*/
#घोषणा ASI_DTLB_DATA_IN	0x5c /* Data-MMU TLB data in reg	*/
#घोषणा ASI_DTLB_DATA_ACCESS	0x5d /* Data-MMU TLB data access reg	*/
#घोषणा ASI_DTLB_TAG_READ	0x5e /* Data-MMU TLB tag पढ़ो reg	*/
#घोषणा ASI_DMMU_DEMAP		0x5f /* Data-MMU TLB demap		*/
#घोषणा ASI_IIU_INST_TRAP	0x60 /* (III) Inकाष्ठाion Breakpoपूर्णांक	*/
#घोषणा ASI_INTR_ID		0x63 /* (CMT) Interrupt ID रेजिस्टर	*/
#घोषणा ASI_CORE_ID		0x63 /* (CMT) LP ID रेजिस्टर		*/
#घोषणा ASI_CESR_ID		0x63 /* (CMT) CESR ID रेजिस्टर		*/
#घोषणा ASI_IC_INSTR		0x66 /* Insn cache instrucion ram diag	*/
#घोषणा ASI_IC_TAG		0x67 /* Insn cache tag/valid ram diag 	*/
#घोषणा ASI_IC_STAG		0x68 /* (III) Insn cache snoop tag ram	*/
#घोषणा ASI_IC_PRE_DECODE	0x6e /* Insn cache pre-decode ram diag	*/
#घोषणा ASI_IC_NEXT_FIELD	0x6f /* Insn cache next-field ram diag	*/
#घोषणा ASI_BRPRED_ARRAY	0x6f /* (III) Branch Prediction RAM diag*/
#घोषणा ASI_BLK_AIUP		0x70 /* Primary, user, block load/store	*/
#घोषणा ASI_BLK_AIUS		0x71 /* Secondary, user, block ld/st	*/
#घोषणा ASI_MCU_CTRL_REG	0x72 /* (III) Memory controller regs	*/
#घोषणा ASI_EC_DATA		0x74 /* (III) E-cache data staging reg	*/
#घोषणा ASI_EC_CTRL		0x75 /* (III) E-cache control reg	*/
#घोषणा ASI_EC_W		0x76 /* E-cache diag ग_लिखो access	*/
#घोषणा ASI_UDB_ERROR_W		0x77 /* External UDB error regs W	*/
#घोषणा ASI_UDB_CONTROL_W	0x77 /* External UDB control regs W	*/
#घोषणा ASI_INTR_W		0x77 /* IRQ vector dispatch ग_लिखो	*/
#घोषणा ASI_INTR_DATAN_W	0x77 /* (III) Out irq vector data reg N	*/
#घोषणा ASI_INTR_DISPATCH_W	0x77 /* (III) Interrupt vector dispatch	*/
#घोषणा ASI_BLK_AIUPL		0x78 /* Primary, user, little, blk ld/st*/
#घोषणा ASI_BLK_AIUSL		0x79 /* Secondary, user, little, blk ld/st*/
#घोषणा ASI_EC_R		0x7e /* E-cache diag पढ़ो access	*/
#घोषणा ASI_UDBH_ERROR_R	0x7f /* External UDB error regs rd hi	*/
#घोषणा ASI_UDBL_ERROR_R	0x7f /* External UDB error regs rd low	*/
#घोषणा ASI_UDBH_CONTROL_R	0x7f /* External UDB control regs rd hi	*/
#घोषणा ASI_UDBL_CONTROL_R	0x7f /* External UDB control regs rd low*/
#घोषणा ASI_INTR_R		0x7f /* IRQ vector dispatch पढ़ो	*/
#घोषणा ASI_INTR_DATAN_R	0x7f /* (III) In irq vector data reg N	*/
#घोषणा ASI_MCD_PRIMARY		0x90 /* (NG7) MCD version load/store	*/
#घोषणा ASI_MCD_ST_BLKINIT_PRIMARY	\
				0x92 /* (NG7) MCD store BLKINIT primary	*/
#घोषणा ASI_PIC			0xb0 /* (NG4) PIC रेजिस्टरs		*/
#घोषणा ASI_PST8_P		0xc0 /* Primary, 8 8-bit, partial	*/
#घोषणा ASI_PST8_S		0xc1 /* Secondary, 8 8-bit, partial	*/
#घोषणा ASI_PST16_P		0xc2 /* Primary, 4 16-bit, partial	*/
#घोषणा ASI_PST16_S		0xc3 /* Secondary, 4 16-bit, partial	*/
#घोषणा ASI_PST32_P		0xc4 /* Primary, 2 32-bit, partial	*/
#घोषणा ASI_PST32_S		0xc5 /* Secondary, 2 32-bit, partial	*/
#घोषणा ASI_PST8_PL		0xc8 /* Primary, 8 8-bit, partial, L	*/
#घोषणा ASI_PST8_SL		0xc9 /* Secondary, 8 8-bit, partial, L	*/
#घोषणा ASI_PST16_PL		0xca /* Primary, 4 16-bit, partial, L	*/
#घोषणा ASI_PST16_SL		0xcb /* Secondary, 4 16-bit, partial, L	*/
#घोषणा ASI_PST32_PL		0xcc /* Primary, 2 32-bit, partial, L	*/
#घोषणा ASI_PST32_SL		0xcd /* Secondary, 2 32-bit, partial, L	*/
#घोषणा ASI_FL8_P		0xd0 /* Primary, 1 8-bit, fpu ld/st	*/
#घोषणा ASI_FL8_S		0xd1 /* Secondary, 1 8-bit, fpu ld/st	*/
#घोषणा ASI_FL16_P		0xd2 /* Primary, 1 16-bit, fpu ld/st	*/
#घोषणा ASI_FL16_S		0xd3 /* Secondary, 1 16-bit, fpu ld/st	*/
#घोषणा ASI_FL8_PL		0xd8 /* Primary, 1 8-bit, fpu ld/st, L	*/
#घोषणा ASI_FL8_SL		0xd9 /* Secondary, 1 8-bit, fpu ld/st, L*/
#घोषणा ASI_FL16_PL		0xda /* Primary, 1 16-bit, fpu ld/st, L	*/
#घोषणा ASI_FL16_SL		0xdb /* Secondary, 1 16-bit, fpu ld/st,L*/
#घोषणा ASI_BLK_COMMIT_P	0xe0 /* Primary, blk store commit	*/
#घोषणा ASI_BLK_COMMIT_S	0xe1 /* Secondary, blk store commit	*/
#घोषणा ASI_BLK_INIT_QUAD_LDD_P	0xe2 /* (NG) init-store, twin load,
				      * primary, implicit
				      */
#घोषणा ASI_BLK_INIT_QUAD_LDD_S	0xe3 /* (NG) init-store, twin load,
				      * secondary, implicit
				      */
#घोषणा ASI_BLK_P		0xf0 /* Primary, blk ld/st		*/
#घोषणा ASI_BLK_S		0xf1 /* Secondary, blk ld/st		*/
#घोषणा ASI_ST_BLKINIT_MRU_P	0xf2 /* (NG4) init-store, twin load,
				      * Most-Recently-Used, primary,
				      * implicit
				      */
#घोषणा ASI_ST_BLKINIT_MRU_S	0xf3 /* (NG4) init-store, twin load,
				      * Most-Recently-Used, secondary,
				      * implicit
				      */
#घोषणा ASI_BLK_PL		0xf8 /* Primary, blk ld/st, little	*/
#घोषणा ASI_BLK_SL		0xf9 /* Secondary, blk ld/st, little	*/
#घोषणा ASI_ST_BLKINIT_MRU_PL	0xfa /* (NG4) init-store, twin load,
				      * Most-Recently-Used, primary,
				      * implicit, little-endian
				      */
#घोषणा ASI_ST_BLKINIT_MRU_SL	0xfb /* (NG4) init-store, twin load,
				      * Most-Recently-Used, secondary,
				      * implicit, little-endian
				      */

#पूर्ण_अगर /* _SPARC_ASI_H */
