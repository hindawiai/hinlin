<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_TSUNAMI__H__
#घोषणा __ALPHA_TSUNAMI__H__

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

/*
 * TSUNAMI/TYPHOON are the पूर्णांकernal names क्रम the core logic chipset which
 * provides memory controller and PCI access क्रम the 21264 based प्रणालीs.
 *
 * This file is based on:
 *
 * Tsunami System Programmers Manual
 * Preliminary, Chapters 2-5
 *
 */

/* XXX: Do we need to conditionalize on this?  */
#अगर_घोषित USE_48_BIT_KSEG
#घोषणा TS_BIAS 0x80000000000UL
#अन्यथा
#घोषणा TS_BIAS 0x10000000000UL
#पूर्ण_अगर

/*
 * CChip, DChip, and PChip रेजिस्टरs
 */

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित दीर्घ csr __attribute__((aligned(64)));
पूर्ण tsunami_64;

प्रकार काष्ठा अणु
	tsunami_64	csc;
	tsunami_64	mtr;
	tsunami_64	misc;
	tsunami_64	mpd;
	tsunami_64	aar0;
	tsunami_64	aar1;
	tsunami_64	aar2;
	tsunami_64	aar3;
	tsunami_64	dim0;
	tsunami_64	dim1;
	tsunami_64	dir0;
	tsunami_64	dir1;
	tsunami_64	drir;
	tsunami_64	prben;
	tsunami_64	iic;	/* a.k.a. iic0 */
	tsunami_64	wdr;	/* a.k.a. iic1 */
	tsunami_64	mpr0;
	tsunami_64	mpr1;
	tsunami_64	mpr2;
	tsunami_64	mpr3;
	tsunami_64	mctl;
	tsunami_64	__pad1;
	tsunami_64	ttr;
	tsunami_64	tdr;
	tsunami_64	dim2;
	tsunami_64	dim3;
	tsunami_64	dir2;
	tsunami_64	dir3;
	tsunami_64	iic2;
	tsunami_64	iic3;
पूर्ण tsunami_cchip;

प्रकार काष्ठा अणु
	tsunami_64	dsc;
	tsunami_64	str;
	tsunami_64	drev;
पूर्ण tsunami_dchip;

प्रकार काष्ठा अणु
	tsunami_64	wsba[4];
	tsunami_64	wsm[4];
	tsunami_64	tba[4];
	tsunami_64	pctl;
	tsunami_64	plat;
	tsunami_64	reserved;
	tsunami_64	लिखो_त्रुटि;
	tsunami_64	perrmask;
	tsunami_64	perrset;
	tsunami_64	tlbiv;
	tsunami_64	tlbia;
	tsunami_64	pmonctl;
	tsunami_64	pmoncnt;
पूर्ण tsunami_pchip;

#घोषणा TSUNAMI_cchip  ((tsunami_cchip *)(IDENT_ADDR+TS_BIAS+0x1A0000000UL))
#घोषणा TSUNAMI_dchip  ((tsunami_dchip *)(IDENT_ADDR+TS_BIAS+0x1B0000800UL))
#घोषणा TSUNAMI_pchip0 ((tsunami_pchip *)(IDENT_ADDR+TS_BIAS+0x180000000UL))
#घोषणा TSUNAMI_pchip1 ((tsunami_pchip *)(IDENT_ADDR+TS_BIAS+0x380000000UL))
बाह्य पूर्णांक TSUNAMI_bootcpu;

/*
 * TSUNAMI Pchip Error रेजिस्टर.
 */

#घोषणा लिखो_त्रुटि_m_lost 0x1
#घोषणा लिखो_त्रुटि_m_serr 0x2
#घोषणा लिखो_त्रुटि_m_perr 0x4
#घोषणा लिखो_त्रुटि_m_dcrto 0x8
#घोषणा लिखो_त्रुटि_m_sge 0x10
#घोषणा लिखो_त्रुटि_m_ape 0x20
#घोषणा लिखो_त्रुटि_m_ta 0x40
#घोषणा लिखो_त्रुटि_m_rdpe 0x80
#घोषणा लिखो_त्रुटि_m_nds 0x100
#घोषणा लिखो_त्रुटि_m_rto 0x200
#घोषणा लिखो_त्रुटि_m_uecc 0x400
#घोषणा लिखो_त्रुटि_m_cre 0x800
#घोषणा लिखो_त्रुटि_m_addrl 0xFFFFFFFF0000UL
#घोषणा लिखो_त्रुटि_m_addrh 0x7000000000000UL
#घोषणा लिखो_त्रुटि_m_cmd 0xF0000000000000UL
#घोषणा लिखो_त्रुटि_m_syn 0xFF00000000000000UL
जोड़ TPchipPERROR अणु   
	काष्ठा  अणु
		अचिन्हित पूर्णांक लिखो_त्रुटि_v_lost : 1;
		अचिन्हित लिखो_त्रुटि_v_serr : 1;
		अचिन्हित लिखो_त्रुटि_v_perr : 1;
		अचिन्हित लिखो_त्रुटि_v_dcrto : 1;
		अचिन्हित लिखो_त्रुटि_v_sge : 1;
		अचिन्हित लिखो_त्रुटि_v_ape : 1;
		अचिन्हित लिखो_त्रुटि_v_ta : 1;
		अचिन्हित लिखो_त्रुटि_v_rdpe : 1;
		अचिन्हित लिखो_त्रुटि_v_nds : 1;
		अचिन्हित लिखो_त्रुटि_v_rto : 1;
		अचिन्हित लिखो_त्रुटि_v_uecc : 1;
		अचिन्हित लिखो_त्रुटि_v_cre : 1;                 
		अचिन्हित लिखो_त्रुटि_v_rsvd1 : 4;
		अचिन्हित लिखो_त्रुटि_v_addrl : 32;
		अचिन्हित लिखो_त्रुटि_v_addrh : 3;
		अचिन्हित लिखो_त्रुटि_v_rsvd2 : 1;
		अचिन्हित लिखो_त्रुटि_v_cmd : 4;
		अचिन्हित लिखो_त्रुटि_v_syn : 8;
	पूर्ण लिखो_त्रुटि_r_bits;
	पूर्णांक लिखो_त्रुटि_q_whole [2];
पूर्ण;                       

/*
 * TSUNAMI Pchip Winकरोw Space Base Address रेजिस्टर.
 */
#घोषणा wsba_m_ena 0x1                
#घोषणा wsba_m_sg 0x2
#घोषणा wsba_m_ptp 0x4
#घोषणा wsba_m_addr 0xFFF00000  
#घोषणा wmask_k_sz1gb 0x3FF00000                   
जोड़ TPchipWSBA अणु
	काष्ठा  अणु
		अचिन्हित wsba_v_ena : 1;
		अचिन्हित wsba_v_sg : 1;
		अचिन्हित wsba_v_ptp : 1;
		अचिन्हित wsba_v_rsvd1 : 17;
		अचिन्हित wsba_v_addr : 12;
		अचिन्हित wsba_v_rsvd2 : 32;
	पूर्ण wsba_r_bits;
	पूर्णांक wsba_q_whole [2];
पूर्ण;

/*
 * TSUNAMI Pchip Control Register
 */
#घोषणा pctl_m_fdsc 0x1
#घोषणा pctl_m_fbtb 0x2
#घोषणा pctl_m_thdis 0x4
#घोषणा pctl_m_chaindis 0x8
#घोषणा pctl_m_tgtlat 0x10
#घोषणा pctl_m_hole 0x20
#घोषणा pctl_m_mwin 0x40
#घोषणा pctl_m_arbena 0x80
#घोषणा pctl_m_prigrp 0x7F00
#घोषणा pctl_m_ppri 0x8000
#घोषणा pctl_m_rsvd1 0x30000
#घोषणा pctl_m_eccen 0x40000
#घोषणा pctl_m_padm 0x80000
#घोषणा pctl_m_cdqmax 0xF00000
#घोषणा pctl_m_rev 0xFF000000
#घोषणा pctl_m_crqmax 0xF00000000UL
#घोषणा pctl_m_ptpmax 0xF000000000UL
#घोषणा pctl_m_pclkx 0x30000000000UL
#घोषणा pctl_m_fdsdis 0x40000000000UL
#घोषणा pctl_m_fdwdis 0x80000000000UL
#घोषणा pctl_m_ptevrfy 0x100000000000UL
#घोषणा pctl_m_rpp 0x200000000000UL
#घोषणा pctl_m_pid 0xC00000000000UL
#घोषणा pctl_m_rsvd2 0xFFFF000000000000UL

जोड़ TPchipPCTL अणु
	काष्ठा अणु
		अचिन्हित pctl_v_fdsc : 1;
		अचिन्हित pctl_v_fbtb : 1;
		अचिन्हित pctl_v_thdis : 1;
		अचिन्हित pctl_v_chaindis : 1;
		अचिन्हित pctl_v_tgtlat : 1;
		अचिन्हित pctl_v_hole : 1;
		अचिन्हित pctl_v_mwin : 1;
		अचिन्हित pctl_v_arbena : 1;
		अचिन्हित pctl_v_prigrp : 7;
		अचिन्हित pctl_v_ppri : 1;
		अचिन्हित pctl_v_rsvd1 : 2;
		अचिन्हित pctl_v_eccen : 1;
		अचिन्हित pctl_v_padm : 1;
		अचिन्हित pctl_v_cdqmax : 4;
		अचिन्हित pctl_v_rev : 8;
		अचिन्हित pctl_v_crqmax : 4;
		अचिन्हित pctl_v_ptpmax : 4;
		अचिन्हित pctl_v_pclkx : 2;
		अचिन्हित pctl_v_fdsdis : 1;
		अचिन्हित pctl_v_fdwdis : 1;
		अचिन्हित pctl_v_ptevrfy : 1;
		अचिन्हित pctl_v_rpp : 1;
		अचिन्हित pctl_v_pid : 2;
		अचिन्हित pctl_v_rsvd2 : 16;
	पूर्ण pctl_r_bits;
	पूर्णांक pctl_q_whole [2];
पूर्ण;

/*
 * TSUNAMI Pchip Error Mask Register.
 */
#घोषणा perrmask_m_lost 0x1
#घोषणा perrmask_m_serr 0x2
#घोषणा perrmask_m_perr 0x4
#घोषणा perrmask_m_dcrto 0x8
#घोषणा perrmask_m_sge 0x10
#घोषणा perrmask_m_ape 0x20
#घोषणा perrmask_m_ta 0x40
#घोषणा perrmask_m_rdpe 0x80
#घोषणा perrmask_m_nds 0x100
#घोषणा perrmask_m_rto 0x200
#घोषणा perrmask_m_uecc 0x400
#घोषणा perrmask_m_cre 0x800
#घोषणा perrmask_m_rsvd 0xFFFFFFFFFFFFF000UL
जोड़ TPchipPERRMASK अणु   
	काष्ठा  अणु
		अचिन्हित पूर्णांक perrmask_v_lost : 1;
		अचिन्हित perrmask_v_serr : 1;
		अचिन्हित perrmask_v_perr : 1;
		अचिन्हित perrmask_v_dcrto : 1;
		अचिन्हित perrmask_v_sge : 1;
		अचिन्हित perrmask_v_ape : 1;
		अचिन्हित perrmask_v_ta : 1;
		अचिन्हित perrmask_v_rdpe : 1;
		अचिन्हित perrmask_v_nds : 1;
		अचिन्हित perrmask_v_rto : 1;
		अचिन्हित perrmask_v_uecc : 1;
		अचिन्हित perrmask_v_cre : 1;                 
		अचिन्हित perrmask_v_rsvd1 : 20;
		अचिन्हित perrmask_v_rsvd2 : 32;
	पूर्ण perrmask_r_bits;
	पूर्णांक perrmask_q_whole [2];
पूर्ण;                       

/*
 * Memory spaces:
 */
#घोषणा TSUNAMI_HOSE(h)		(((अचिन्हित दीर्घ)(h)) << 33)
#घोषणा TSUNAMI_BASE		(IDENT_ADDR + TS_BIAS)

#घोषणा TSUNAMI_MEM(h)		(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x000000000UL)
#घोषणा _TSUNAMI_IACK_SC(h)	(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1F8000000UL)
#घोषणा TSUNAMI_IO(h)		(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1FC000000UL)
#घोषणा TSUNAMI_CONF(h)		(TSUNAMI_BASE+TSUNAMI_HOSE(h) + 0x1FE000000UL)

#घोषणा TSUNAMI_IACK_SC		_TSUNAMI_IACK_SC(0) /* hack! */


/* 
 * The canonical non-remaped I/O and MEM addresses have these values
 * subtracted out.  This is arranged so that folks manipulating ISA
 * devices can use their familiar numbers and have them map to bus 0.
 */

#घोषणा TSUNAMI_IO_BIAS          TSUNAMI_IO(0)
#घोषणा TSUNAMI_MEM_BIAS         TSUNAMI_MEM(0)

/* The IO address space is larger than 0xffff */
#घोषणा TSUNAMI_IO_SPACE	(TSUNAMI_CONF(0) - TSUNAMI_IO(0))

/* Offset between ram physical addresses and pci64 DAC bus addresses.  */
#घोषणा TSUNAMI_DAC_OFFSET	(1UL << 40)

/*
 * Data काष्ठाure क्रम handling TSUNAMI machine checks:
 */
काष्ठा el_TSUNAMI_sysdata_mcheck अणु
पूर्ण;


#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * TSUNAMI, the 21??? PCI/memory support chipset क्रम the EV6 (21264)
 * can only use linear accesses to get at PCI memory and I/O spaces.
 */

/*
 * Memory functions.  all accesses are करोne through linear space.
 */
बाह्य व्योम __iomem *tsunami_ioporपंचांगap(अचिन्हित दीर्घ addr);
बाह्य व्योम __iomem *tsunami_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);
__EXTERN_INLINE पूर्णांक tsunami_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= TSUNAMI_BASE;
पूर्ण

__EXTERN_INLINE पूर्णांक tsunami_is_mmio(स्थिर अस्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	वापस (addr & 0x100000000UL) == 0;
पूर्ण

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		tsunami
#घोषणा tsunami_trivial_rw_bw	1
#घोषणा tsunami_trivial_rw_lq	1
#घोषणा tsunami_trivial_io_bw	1
#घोषणा tsunami_trivial_io_lq	1
#घोषणा tsunami_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_TSUNAMI__H__ */
