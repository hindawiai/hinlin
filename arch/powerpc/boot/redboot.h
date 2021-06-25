<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_REDBOOT_H
#घोषणा _PPC_REDBOOT_H

//=========================================================================
// include/यंत्र-ppc/redboot.h
//   Copyright (c) 2002, 2003 Gary Thomas (<gary@mlbassoc.com>
//   Copyright (c) 1997 Dan Malek (dmalek@jlc.net)

//
// Board specअगरic details, as provided by RedBoot
//

/* A Board Inक्रमmation काष्ठाure that is given to a program when
 * RedBoot starts it up.  Note: not all fields make sense क्रम all
 * architectures and it's up to the platक्रमm specअगरic code to fill
 * in the details.
 */
प्रकार काष्ठा bd_info अणु
    अचिन्हित पूर्णांक   bi_tag;        /* Should be 0x42444944 "BDID" */
    अचिन्हित पूर्णांक   bi_size;       /* Size of this काष्ठाure */
    अचिन्हित पूर्णांक   bi_revision;   /* revision of this काष्ठाure */
    अचिन्हित पूर्णांक   bi_bdate;      /* bootstrap date, i.e. 0x19971106 */
    अचिन्हित पूर्णांक   bi_memstart;   /* Memory start address */
    अचिन्हित पूर्णांक   bi_memsize;    /* Memory (end) size in bytes */
    अचिन्हित पूर्णांक   bi_पूर्णांकfreq;    /* Internal Freq, in Hz */
    अचिन्हित पूर्णांक   bi_busfreq;    /* Bus Freq, in Hz */
    अचिन्हित पूर्णांक   bi_cpmfreq;    /* CPM Freq, in Hz */
    अचिन्हित पूर्णांक   bi_brgfreq;    /* BRG Freq, in Hz */
    अचिन्हित पूर्णांक   bi_vco;        /* VCO Out from PLL */
    अचिन्हित पूर्णांक   bi_pci_freq;   /* PCI Freq, in Hz */
    अचिन्हित पूर्णांक   bi_baudrate;   /* Default console baud rate */
    अचिन्हित पूर्णांक   bi_immr;       /* IMMR when called from boot rom */
    अचिन्हित अक्षर  bi_enetaddr[6];
    अचिन्हित पूर्णांक   bi_flashbase;  /* Physical address of FLASH memory */
    अचिन्हित पूर्णांक   bi_flashsize;  /* Length of FLASH memory */
    पूर्णांक            bi_flashwidth; /* Width (8,16,32,64) */
    अचिन्हित अक्षर *bi_cmdline;    /* Poपूर्णांकer to command line */
    अचिन्हित अक्षर  bi_esa[3][6];  /* Ethernet station addresses */
    अचिन्हित पूर्णांक   bi_ramdisk_begin, bi_ramdisk_end;
    काष्ठा अणु                      /* Inक्रमmation about [मुख्य] video screen */
        लघु x_res;              /*   Horizontal resolution in pixels */
        लघु y_res;              /*   Vertical resolution in pixels */
        लघु bpp;                /*   Bits/pixel */
        लघु mode;               /*   Type of pixels (packed, indexed) */
        अचिन्हित दीर्घ fb;         /*   Poपूर्णांकer to frame buffer (pixel) memory */
    पूर्ण bi_video;
    व्योम         (*bi_cअ_दो)(अक्षर);   /* Write a अक्षरacter to the RedBoot console */
    अक्षर         (*bi_cअ_लो)(व्योम);   /* Read a अक्षरacter from the RedBoot console */
    पूर्णांक          (*bi_ctstc)(व्योम);   /* Test क्रम input on the RedBoot console */
पूर्ण bd_t;

#घोषणा BI_REV 0x0102    /* Version 1.02 */

#घोषणा bi_pci_busfreq bi_pci_freq
#घोषणा bi_immr_base   bi_immr
#पूर्ण_अगर
