<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * This पूर्णांकerface is used क्रम compatibility with old U-boots *ONLY*.
 * Please करो not imitate or extend this.
 */

/* 
 * Unक्रमtunately, the ESTeem Hotfoot board uses a mangled version of 
 * ppcboot.h क्रम historical reasons, and in the पूर्णांकerest of having a 
 * मुख्यline kernel boot on the production board+bootloader, this was the 
 * least-offensive solution.  Please direct all flames to:
 *
 *  Solomon Peachy <solomon@linux-wlan.com>
 *
 * (This header is identical to ppcboot.h except क्रम the 
 *  TARGET_HOTFOOT bits)
 */

/*
 * (C) Copyright 2000, 2001
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

#अगर_अघोषित __PPCBOOT_H__
#घोषणा __PPCBOOT_H__

/*
 * Board inक्रमmation passed to kernel from PPCBoot
 *
 * include/यंत्र-ppc/ppcboot.h
 */

#समावेश "types.h"

प्रकार काष्ठा bd_info अणु
	अचिन्हित दीर्घ	bi_memstart;	/* start of DRAM memory */
	अचिन्हित दीर्घ	bi_memsize;	/* size	 of DRAM memory in bytes */
	अचिन्हित दीर्घ	bi_flashstart;	/* start of FLASH memory */
	अचिन्हित दीर्घ	bi_flashsize;	/* size	 of FLASH memory */
	अचिन्हित दीर्घ	bi_flashoffset; /* reserved area क्रम startup monitor */
	अचिन्हित दीर्घ	bi_sramstart;	/* start of SRAM memory */
	अचिन्हित दीर्घ	bi_sramsize;	/* size	 of SRAM memory */
#अगर defined(TARGET_8xx) || defined(TARGET_CPM2) || defined(TARGET_85xx) ||\
	defined(TARGET_83xx)
	अचिन्हित दीर्घ	bi_immr_base;	/* base of IMMR रेजिस्टर */
#पूर्ण_अगर
#अगर defined(TARGET_PPC_MPC52xx)
	अचिन्हित दीर्घ   bi_mbar_base;   /* base of पूर्णांकernal रेजिस्टरs */
#पूर्ण_अगर
	अचिन्हित दीर्घ	bi_bootflags;	/* boot / reboot flag (क्रम LynxOS) */
	अचिन्हित दीर्घ	bi_ip_addr;	/* IP Address */
	अचिन्हित अक्षर	bi_enetaddr[6];	/* Ethernet address */
#अगर defined(TARGET_HOTFOOT)
	/* second onboard ethernet port */
	अचिन्हित अक्षर	bi_enet1addr[6];
#घोषणा HAVE_ENET1ADDR
#पूर्ण_अगर /* TARGET_HOOTFOOT */
	अचिन्हित लघु	bi_ethspeed;	/* Ethernet speed in Mbps */
	अचिन्हित दीर्घ	bi_पूर्णांकfreq;	/* Internal Freq, in MHz */
	अचिन्हित दीर्घ	bi_busfreq;	/* Bus Freq, in MHz */
#अगर defined(TARGET_CPM2)
	अचिन्हित दीर्घ	bi_cpmfreq;	/* CPM_CLK Freq, in MHz */
	अचिन्हित दीर्घ	bi_brgfreq;	/* BRG_CLK Freq, in MHz */
	अचिन्हित दीर्घ	bi_sccfreq;	/* SCC_CLK Freq, in MHz */
	अचिन्हित दीर्घ	bi_vco;		/* VCO Out from PLL, in MHz */
#पूर्ण_अगर
#अगर defined(TARGET_PPC_MPC52xx)
	अचिन्हित दीर्घ   bi_ipbfreq;     /* IPB Bus Freq, in MHz */
	अचिन्हित दीर्घ   bi_pcअगरreq;     /* PCI Bus Freq, in MHz */
#पूर्ण_अगर
	अचिन्हित दीर्घ	bi_baudrate;	/* Console Baudrate */
#अगर defined(TARGET_4xx)
	अचिन्हित अक्षर	bi_s_version[4];	/* Version of this काष्ठाure */
	अचिन्हित अक्षर	bi_r_version[32];	/* Version of the ROM (IBM) */
	अचिन्हित पूर्णांक	bi_procfreq;	/* CPU (Internal) Freq, in Hz */
	अचिन्हित पूर्णांक	bi_plb_busfreq;	/* PLB Bus speed, in Hz */
	अचिन्हित पूर्णांक	bi_pci_busfreq;	/* PCI Bus speed, in Hz */
	अचिन्हित अक्षर	bi_pci_enetaddr[6];	/* PCI Ethernet MAC address */
#पूर्ण_अगर
#अगर defined(TARGET_HOTFOOT)
	अचिन्हित पूर्णांक     bi_pllouta_freq;       /* PLL OUTA speed, in Hz */
#पूर्ण_अगर
#अगर defined(TARGET_HYMOD)
	hymod_conf_t	bi_hymod_conf;	/* hymod configuration inक्रमmation */
#पूर्ण_अगर
#अगर defined(TARGET_EVB64260) || defined(TARGET_405EP) || defined(TARGET_44x) || \
	defined(TARGET_85xx) ||	defined(TARGET_83xx) || defined(TARGET_HAS_ETH1)
	/* second onboard ethernet port */
	अचिन्हित अक्षर	bi_enet1addr[6];
#घोषणा HAVE_ENET1ADDR
#पूर्ण_अगर
#अगर defined(TARGET_EVB64260) || defined(TARGET_440GX) || \
    defined(TARGET_85xx) || defined(TARGET_HAS_ETH2)
	/* third onboard ethernet ports */
	अचिन्हित अक्षर	bi_enet2addr[6];
#घोषणा HAVE_ENET2ADDR
#पूर्ण_अगर
#अगर defined(TARGET_440GX) || defined(TARGET_HAS_ETH3)
	/* fourth onboard ethernet ports */
	अचिन्हित अक्षर	bi_enet3addr[6];
#घोषणा HAVE_ENET3ADDR
#पूर्ण_अगर
#अगर defined(TARGET_HOTFOOT)
        पूर्णांक             bi_phynum[2];           /* Determines phy mapping */
        पूर्णांक             bi_phymode[2];          /* Determines phy mode */
#पूर्ण_अगर
#अगर defined(TARGET_4xx)
	अचिन्हित पूर्णांक	bi_opbfreq;		/* OB घड़ी in Hz */
	पूर्णांक		bi_iic_fast[2];		/* Use fast i2c mode */
#पूर्ण_अगर
#अगर defined(TARGET_440GX)
	पूर्णांक		bi_phynum[4];		/* phy mapping */
	पूर्णांक		bi_phymode[4];		/* phy mode */
#पूर्ण_अगर
पूर्ण bd_t;

#घोषणा bi_tbfreq	bi_पूर्णांकfreq

#पूर्ण_अगर	/* __PPCBOOT_H__ */
