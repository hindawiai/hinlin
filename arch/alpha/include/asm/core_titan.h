<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_TITAN__H__
#घोषणा __ALPHA_TITAN__H__

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

/*
 * TITAN is the पूर्णांकernal names क्रम a core logic chipset which provides
 * memory controller and PCI/AGP access क्रम 21264 based प्रणालीs.
 *
 * This file is based on:
 *
 * Titan Chipset Engineering Specअगरication
 * Revision 0.12
 * 13 July 1999
 *
 */

/* XXX: Do we need to conditionalize on this?  */
#अगर_घोषित USE_48_BIT_KSEG
#घोषणा TI_BIAS 0x80000000000UL
#अन्यथा
#घोषणा TI_BIAS 0x10000000000UL
#पूर्ण_अगर

/*
 * CChip, DChip, and PChip रेजिस्टरs
 */

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित दीर्घ csr __attribute__((aligned(64)));
पूर्ण titan_64;

प्रकार काष्ठा अणु
	titan_64	csc;
	titan_64	mtr;
	titan_64	misc;
	titan_64	mpd;
	titan_64	aar0;
	titan_64	aar1;
	titan_64	aar2;
	titan_64	aar3;
	titan_64	dim0;
	titan_64	dim1;
	titan_64	dir0;
	titan_64	dir1;
	titan_64	drir;
	titan_64	prben;
	titan_64	iic0;
	titan_64	iic1;
	titan_64	mpr0;
	titan_64	mpr1;
	titan_64	mpr2;
	titan_64	mpr3;
	titan_64	rsvd[2];
	titan_64	ttr;
	titan_64	tdr;
	titan_64	dim2;
	titan_64	dim3;
	titan_64	dir2;
	titan_64	dir3;
	titan_64	iic2;
	titan_64	iic3;
	titan_64	pwr;
	titan_64	reserved[17];
	titan_64	cmonctla;
	titan_64	cmonctlb;
	titan_64	cmoncnt01;
	titan_64	cmoncnt23;
	titan_64	cpen;
पूर्ण titan_cchip;

प्रकार काष्ठा अणु
	titan_64	dsc;
	titan_64	str;
	titan_64	drev;
	titan_64	dsc2;
पूर्ण titan_dchip;

प्रकार काष्ठा अणु
	titan_64	wsba[4];
	titan_64	wsm[4];
	titan_64	tba[4];
	titan_64	pctl;
	titan_64	plat;
	titan_64	reserved0[2];
	जोड़ अणु
		काष्ठा अणु
			titan_64	serror;
			titan_64	serren;
			titan_64	serrset;
			titan_64	reserved0;
			titan_64	gलिखो_त्रुटि;
			titan_64	gperren;
			titan_64	gperrset;
			titan_64	reserved1;
			titan_64	gtlbiv;
			titan_64	gtlbia;
			titan_64	reserved2[2];
			titan_64	sctl;
			titan_64	reserved3[3];
		पूर्ण g;
		काष्ठा अणु
			titan_64	agलिखो_त्रुटि;
			titan_64	agperren;
			titan_64	agperrset;
			titan_64	agplastwr;
			titan_64	aलिखो_त्रुटि;
			titan_64	aperren;
			titan_64	aperrset;
			titan_64	reserved0;
			titan_64	atlbiv;
			titan_64	atlbia;
			titan_64	reserved1[6];
		पूर्ण a;
	पूर्ण port_specअगरic;
	titan_64	sprst;
	titan_64	reserved1[31];
पूर्ण titan_pachip_port;

प्रकार काष्ठा अणु
	titan_pachip_port	g_port;
	titan_pachip_port	a_port;
पूर्ण titan_pachip;

#घोषणा TITAN_cchip	((titan_cchip  *)(IDENT_ADDR+TI_BIAS+0x1A0000000UL))
#घोषणा TITAN_dchip    	((titan_dchip  *)(IDENT_ADDR+TI_BIAS+0x1B0000800UL))
#घोषणा TITAN_pachip0 	((titan_pachip *)(IDENT_ADDR+TI_BIAS+0x180000000UL))
#घोषणा TITAN_pachip1 	((titan_pachip *)(IDENT_ADDR+TI_BIAS+0x380000000UL))
बाह्य अचिन्हित TITAN_agp;
बाह्य पूर्णांक TITAN_bootcpu;

/*
 * TITAN PA-chip Winकरोw Space Base Address रेजिस्टर.
 * (WSBA[0-2])
 */
#घोषणा wsba_m_ena 0x1                
#घोषणा wsba_m_sg 0x2
#घोषणा wsba_m_addr 0xFFF00000  
#घोषणा wmask_k_sz1gb 0x3FF00000                   
जोड़ TPAchipWSBA अणु
	काष्ठा  अणु
		अचिन्हित wsba_v_ena : 1;
		अचिन्हित wsba_v_sg : 1;
		अचिन्हित wsba_v_rsvd1 : 18;
		अचिन्हित wsba_v_addr : 12;
		अचिन्हित wsba_v_rsvd2 : 32;
        पूर्ण wsba_r_bits;
	पूर्णांक wsba_q_whole [2];
पूर्ण;

/*
 * TITAN PA-chip Control Register
 * This definition covers both the G-Port GPCTL and the A-PORT APCTL.
 * Bits <51:0> are the same in both हालs. APCTL<63:52> are only 
 * applicable to AGP.
 */
#घोषणा pctl_m_fbtb 			0x00000001
#घोषणा pctl_m_thdis 			0x00000002
#घोषणा pctl_m_chaindis 		0x00000004
#घोषणा pctl_m_tgtlat 			0x00000018
#घोषणा pctl_m_hole  	  		0x00000020
#घोषणा pctl_m_mwin 	  		0x00000040
#घोषणा pctl_m_arbena 	  		0x00000080
#घोषणा pctl_m_prigrp 	  		0x0000FF00
#घोषणा pctl_m_ppri 	  		0x00010000
#घोषणा pctl_m_pcispd66  		0x00020000
#घोषणा pctl_m_cngstlt	  		0x003C0000
#घोषणा pctl_m_ptpdesten 		0x3FC00000
#घोषणा pctl_m_dpcen			0x40000000
#घोषणा pctl_m_apcen		0x0000000080000000UL
#घोषणा pctl_m_dcrtv		0x0000000300000000UL
#घोषणा pctl_m_en_stepping	0x0000000400000000UL
#घोषणा apctl_m_rsvd1		0x000FFFF800000000UL
#घोषणा apctl_m_agp_rate	0x0030000000000000UL
#घोषणा apctl_m_agp_sba_en	0x0040000000000000UL
#घोषणा apctl_m_agp_en		0x0080000000000000UL
#घोषणा apctl_m_rsvd2		0x0100000000000000UL
#घोषणा apctl_m_agp_present	0x0200000000000000UL
#घोषणा apctl_agp_hp_rd		0x1C00000000000000UL
#घोषणा apctl_agp_lp_rd		0xE000000000000000UL
#घोषणा gpctl_m_rsvd		0xFFFFFFF800000000UL
जोड़ TPAchipPCTL अणु
	काष्ठा अणु
		अचिन्हित pctl_v_fbtb : 1;		/* A/G [0]     */
		अचिन्हित pctl_v_thdis : 1;		/* A/G [1]     */
		अचिन्हित pctl_v_chaindis : 1;		/* A/G [2]     */
		अचिन्हित pctl_v_tgtlat : 2;		/* A/G [4:3]   */
		अचिन्हित pctl_v_hole : 1;		/* A/G [5]     */
		अचिन्हित pctl_v_mwin : 1;		/* A/G [6]     */
		अचिन्हित pctl_v_arbena : 1;		/* A/G [7]     */
		अचिन्हित pctl_v_prigrp : 8;		/* A/G [15:8]  */
		अचिन्हित pctl_v_ppri : 1;		/* A/G [16]    */
		अचिन्हित pctl_v_pcispd66 : 1;		/* A/G [17]    */
		अचिन्हित pctl_v_cngstlt : 4;		/* A/G [21:18] */
		अचिन्हित pctl_v_ptpdesten : 8;		/* A/G [29:22] */
		अचिन्हित pctl_v_dpcen : 1;		/* A/G [30]    */
		अचिन्हित pctl_v_apcen : 1;		/* A/G [31]    */
		अचिन्हित pctl_v_dcrtv : 2;		/* A/G [33:32] */
		अचिन्हित pctl_v_en_stepping :1;		/* A/G [34]    */
		अचिन्हित apctl_v_rsvd1 : 17;		/* A   [51:35] */
		अचिन्हित apctl_v_agp_rate : 2;		/* A   [53:52] */
		अचिन्हित apctl_v_agp_sba_en : 1;	/* A   [54]    */
		अचिन्हित apctl_v_agp_en : 1;		/* A   [55]    */
		अचिन्हित apctl_v_rsvd2 : 1;		/* A   [56]    */
		अचिन्हित apctl_v_agp_present : 1;	/* A   [57]    */
		अचिन्हित apctl_v_agp_hp_rd : 3;		/* A   [60:58] */
		अचिन्हित apctl_v_agp_lp_rd : 3;		/* A   [63:61] */
	पूर्ण pctl_r_bits;
	अचिन्हित पूर्णांक pctl_l_whole [2];
	अचिन्हित दीर्घ pctl_q_whole;
पूर्ण;

/*
 * SERROR / SERREN / SERRSET
 */
जोड़ TPAchipSERR अणु
	काष्ठा अणु
		अचिन्हित serr_v_lost_uecc : 1;		/* [0]		*/
		अचिन्हित serr_v_uecc : 1;		/* [1]  	*/
		अचिन्हित serr_v_cre : 1;		/* [2]		*/
		अचिन्हित serr_v_nxio : 1;		/* [3]		*/
		अचिन्हित serr_v_lost_cre : 1;		/* [4]		*/
		अचिन्हित serr_v_rsvd0 : 10;		/* [14:5]	*/
		अचिन्हित serr_v_addr : 32;		/* [46:15]	*/
		अचिन्हित serr_v_rsvd1 : 5;		/* [51:47]	*/
		अचिन्हित serr_v_source : 2;		/* [53:52]	*/
		अचिन्हित serr_v_cmd : 2;		/* [55:54]	*/
		अचिन्हित serr_v_syn : 8;		/* [63:56]	*/
	पूर्ण serr_r_bits;
	अचिन्हित पूर्णांक serr_l_whole[2];
	अचिन्हित दीर्घ serr_q_whole;
पूर्ण;

/*
 * GPERROR / APERROR / GPERREN / APERREN / GPERRSET / APERRSET
 */
जोड़ TPAchipPERR अणु
	काष्ठा अणु
		अचिन्हित दीर्घ perr_v_lost : 1;	     	/* [0]		*/
		अचिन्हित दीर्घ perr_v_serr : 1;		/* [1]		*/
		अचिन्हित दीर्घ perr_v_perr : 1;		/* [2]		*/
		अचिन्हित दीर्घ perr_v_dcrto : 1;		/* [3]		*/
		अचिन्हित दीर्घ perr_v_sge : 1;		/* [4]		*/
		अचिन्हित दीर्घ perr_v_ape : 1;		/* [5]		*/
		अचिन्हित दीर्घ perr_v_ta : 1;		/* [6]		*/
		अचिन्हित दीर्घ perr_v_dpe : 1;		/* [7]		*/
		अचिन्हित दीर्घ perr_v_nds : 1;		/* [8]		*/
		अचिन्हित दीर्घ perr_v_iptpr : 1;		/* [9]		*/
		अचिन्हित दीर्घ perr_v_iptpw : 1;		/* [10] 	*/
		अचिन्हित दीर्घ perr_v_rsvd0 : 3;		/* [13:11]	*/
		अचिन्हित दीर्घ perr_v_addr : 33;		/* [46:14]	*/
		अचिन्हित दीर्घ perr_v_dac : 1;		/* [47]		*/
		अचिन्हित दीर्घ perr_v_mwin : 1;		/* [48]		*/
		अचिन्हित दीर्घ perr_v_rsvd1 : 3;		/* [51:49]	*/
		अचिन्हित दीर्घ perr_v_cmd : 4;		/* [55:52]	*/
		अचिन्हित दीर्घ perr_v_rsvd2 : 8;		/* [63:56]	*/
	पूर्ण perr_r_bits;
	अचिन्हित पूर्णांक perr_l_whole[2];
	अचिन्हित दीर्घ perr_q_whole;
पूर्ण;

/*
 * AGPERROR / AGPERREN / AGPERRSET
 */
जोड़ TPAchipAGPERR अणु
	काष्ठा अणु
		अचिन्हित agperr_v_lost : 1;		/* [0]		*/
		अचिन्हित agperr_v_lpqfull : 1;		/* [1]		*/
		अचिन्हित apgerr_v_hpqfull : 1;		/* [2]		*/
		अचिन्हित agperr_v_rescmd : 1;		/* [3]		*/
		अचिन्हित agperr_v_ipte : 1;		/* [4]		*/
		अचिन्हित agperr_v_ptp :	1;      	/* [5]		*/
		अचिन्हित agperr_v_nowinकरोw : 1;		/* [6]		*/
		अचिन्हित agperr_v_rsvd0 : 8;		/* [14:7]	*/
		अचिन्हित agperr_v_addr : 32;		/* [46:15]	*/
		अचिन्हित agperr_v_rsvd1 : 1;		/* [47]		*/
		अचिन्हित agperr_v_dac : 1;		/* [48]		*/
		अचिन्हित agperr_v_mwin : 1;		/* [49]		*/
		अचिन्हित agperr_v_cmd : 3;		/* [52:50]	*/
		अचिन्हित agperr_v_length : 6;		/* [58:53]	*/
		अचिन्हित agperr_v_fence : 1;		/* [59]		*/
		अचिन्हित agperr_v_rsvd2 : 4;		/* [63:60]	*/
	पूर्ण agperr_r_bits;
	अचिन्हित पूर्णांक agperr_l_whole[2];
	अचिन्हित दीर्घ agperr_q_whole;
पूर्ण;
/*
 * Memory spaces:
 * Hose numbers are asचिन्हित as follows:
 *		0 - pachip 0 / G Port
 *		1 - pachip 1 / G Port
 * 		2 - pachip 0 / A Port
 *      	3 - pachip 1 / A Port
 */
#घोषणा TITAN_HOSE_SHIFT       (33) 
#घोषणा TITAN_HOSE(h)		(((अचिन्हित दीर्घ)(h)) << TITAN_HOSE_SHIFT)
#घोषणा TITAN_BASE		(IDENT_ADDR + TI_BIAS)
#घोषणा TITAN_MEM(h)	     	(TITAN_BASE+TITAN_HOSE(h)+0x000000000UL)
#घोषणा _TITAN_IACK_SC(h)    	(TITAN_BASE+TITAN_HOSE(h)+0x1F8000000UL)
#घोषणा TITAN_IO(h)	     	(TITAN_BASE+TITAN_HOSE(h)+0x1FC000000UL)
#घोषणा TITAN_CONF(h)	     	(TITAN_BASE+TITAN_HOSE(h)+0x1FE000000UL)

#घोषणा TITAN_HOSE_MASK		TITAN_HOSE(3)
#घोषणा TITAN_IACK_SC	     	_TITAN_IACK_SC(0) /* hack! */

/* 
 * The canonical non-remaped I/O and MEM addresses have these values
 * subtracted out.  This is arranged so that folks manipulating ISA
 * devices can use their familiar numbers and have them map to bus 0.
 */

#घोषणा TITAN_IO_BIAS		TITAN_IO(0)
#घोषणा TITAN_MEM_BIAS		TITAN_MEM(0)

/* The IO address space is larger than 0xffff */
#घोषणा TITAN_IO_SPACE		(TITAN_CONF(0) - TITAN_IO(0))

/* TIG Space */
#घोषणा TITAN_TIG_SPACE		(TITAN_BASE + 0x100000000UL)

/* Offset between ram physical addresses and pci64 DAC bus addresses.  */
/* ??? Just a guess.  Ought to confirm it hasn't been moved.  */
#घोषणा TITAN_DAC_OFFSET	(1UL << 40)

/*
 * Data काष्ठाure क्रम handling TITAN machine checks:
 */
#घोषणा SCB_Q_SYSERR	0x620
#घोषणा SCB_Q_PROCERR	0x630
#घोषणा SCB_Q_SYSMCHK	0x660
#घोषणा SCB_Q_PROCMCHK	0x670
#घोषणा SCB_Q_SYSEVENT	0x680	/* environmental / प्रणाली management */
काष्ठा el_TITAN_sysdata_mcheck अणु
	u64 summary;	/* 0x00 */
	u64 c_dirx;	/* 0x08 */
	u64 c_misc;	/* 0x10 */
	u64 p0_serror;	/* 0x18 */
	u64 p0_gलिखो_त्रुटि; /* 0x20 */
	u64 p0_aलिखो_त्रुटि; /* 0x28 */
	u64 p0_agलिखो_त्रुटि;/* 0x30 */
	u64 p1_serror;	/* 0x38 */
	u64 p1_gलिखो_त्रुटि; /* 0x40 */
	u64 p1_aलिखो_त्रुटि; /* 0x48 */
	u64 p1_agलिखो_त्रुटि;/* 0x50 */
पूर्ण;

/*
 * System area क्रम a निजीer 680 environmental/प्रणाली management mcheck 
 */
काष्ठा el_PRIVATEER_envdata_mcheck अणु
	u64 summary;	/* 0x00 */
	u64 c_dirx;	/* 0x08 */
	u64 smir;	/* 0x10 */
	u64 cpuir;	/* 0x18 */
	u64 psir;	/* 0x20 */
	u64 fault;	/* 0x28 */
	u64 sys_करोors;	/* 0x30 */
	u64 temp_warn;	/* 0x38 */
	u64 fan_ctrl;	/* 0x40 */
	u64 code;	/* 0x48 */
	u64 reserved;	/* 0x50 */
पूर्ण;

#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * TITAN, a 21??? PCI/memory support chipset क्रम the EV6 (21264)
 * can only use linear accesses to get at PCI/AGP memory and I/O spaces.
 */

/*
 * Memory functions.  all accesses are करोne through linear space.
 */
बाह्य व्योम __iomem *titan_ioporपंचांगap(अचिन्हित दीर्घ addr);
बाह्य व्योम __iomem *titan_ioremap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size);
बाह्य व्योम titan_iounmap(अस्थिर व्योम __iomem *addr);

__EXTERN_INLINE पूर्णांक titan_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= TITAN_BASE;
पूर्ण

बाह्य पूर्णांक titan_is_mmio(स्थिर अस्थिर व्योम __iomem *addr);

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		titan
#घोषणा titan_trivial_rw_bw	1
#घोषणा titan_trivial_rw_lq	1
#घोषणा titan_trivial_io_bw	1
#घोषणा titan_trivial_io_lq	1
#घोषणा titan_trivial_iounmap	0
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_TITAN__H__ */
