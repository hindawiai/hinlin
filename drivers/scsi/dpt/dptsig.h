<शैली गुरु>
/*	BSDI dptsig.h,v 1.7 1998/06/03 19:15:00 karels Exp	*/

/*
 * Copyright (c) 1996-1999 Distributed Processing Technology Corporation
 * All rights reserved.
 *
 * Redistribution and use in source क्रमm, with or without modअगरication, are
 * permitted provided that redistributions of source code must retain the
 * above copyright notice, this list of conditions and the following disclaimer.
 *
 * This software is provided `as is' by Distributed Processing Technology and
 * any express or implied warranties, including, but not limited to, the
 * implied warranties of merchantability and fitness क्रम a particular purpose,
 * are disclaimed. In no event shall Distributed Processing Technology be
 * liable क्रम any direct, indirect, incidental, special, exemplary or
 * consequential damages (including, but not limited to, procurement of
 * substitute goods or services; loss of use, data, or profits; or business
 * पूर्णांकerruptions) however caused and on any theory of liability, whether in
 * contract, strict liability, or tort (including negligence or otherwise)
 * arising in any way out of the use of this driver software, even अगर advised
 * of the possibility of such damage.
 *
 */

#अगर_अघोषित __DPTSIG_H_
#घोषणा __DPTSIG_H_
#अगर_घोषित _SINIX_ADDON
#समावेश "dpt.h"
#पूर्ण_अगर
/* DPT SIGNATURE SPEC AND HEADER खाता                           */
/* Signature Version 1 (sorry no 'A')                           */

/* to make sure we are talking the same size under all OS's     */
प्रकार अचिन्हित अक्षर sigBYTE;
प्रकार अचिन्हित लघु sigWORD;
प्रकार अचिन्हित पूर्णांक sigINT;

/*
 * use sigWORDLittleEndian क्रम:
 *  dsCapabilities
 *  dsDeviceSupp
 *  dsAdapterSupp
 *  dsApplication
 * use sigLONGLittleEndian क्रम:
 *      dsOS
 * so that the sig can be standardised to Little Endian
 */
#अगर (defined(_DPT_BIG_ENDIAN))
# define sigWORDLittleEndian(x) ((((x)&0xFF)<<8)|(((x)>>8)&0xFF))
# define sigLONGLittleEndian(x) \
        ((((x)&0xFF)<<24) |             \
         (((x)&0xFF00)<<8) |    \
         (((x)&0xFF0000L)>>8) | \
         (((x)&0xFF000000L)>>24))
#अन्यथा
# define sigWORDLittleEndian(x) (x)
# define sigLONGLittleEndian(x) (x)
#पूर्ण_अगर

/* must make sure the काष्ठाure is not word or द्विगुन-word aligned      */
/* ---------------------------------------------------------------      */
/* Borland will ignore the following pragma:                            */
/* Word alignment is OFF by शेष.  If in the, IDE make               */
/* sure that Options | Compiler | Code Generation | Word Alignment      */
/* is not checked.  If using BCC, करो not use the -a option.             */

#अगर_अघोषित NO_PACK
#अगर defined (_DPT_AIX)
#आशय options align=packed
#अन्यथा
#आशय pack(1)
#पूर्ण_अगर  /* aix */
#पूर्ण_अगर
/* For the Macपूर्णांकosh */
#अगर_घोषित STRUCTALIGNMENTSUPPORTED
#आशय options align=mac68k
#पूर्ण_अगर


/* Current Signature Version - sigBYTE dsSigVersion; */
/* ------------------------------------------------------------------ */
#घोषणा SIG_VERSION 1

/* Processor Family - sigBYTE dsProcessorFamily;  DISTINCT VALUES */
/* ------------------------------------------------------------------ */
/* What type of processor the file is meant to run on. */
/* This will let us know whether to पढ़ो sigWORDs as high/low or low/high. */
#घोषणा PROC_INTEL      0x00    /* Intel 80x86/ia64 */
#घोषणा PROC_MOTOROLA   0x01    /* Motorola 68K */
#घोषणा PROC_MIPS4000   0x02    /* MIPS RISC 4000 */
#घोषणा PROC_ALPHA      0x03    /* DEC Alpha */
#घोषणा PROC_POWERPC    0x04    /* IBM Power PC */
#घोषणा PROC_i960       0x05    /* Intel i960 */
#घोषणा PROC_ULTRASPARC 0x06    /* SPARC processor */

/* Specअगरic Minimim Processor - sigBYTE dsProcessor;    FLAG BITS */
/* ------------------------------------------------------------------ */
/* Dअगरferent bit definitions dependent on processor_family */

/* PROC_INTEL: */
#घोषणा PROC_8086       0x01    /* Intel 8086 */
#घोषणा PROC_286        0x02    /* Intel 80286 */
#घोषणा PROC_386        0x04    /* Intel 80386 */
#घोषणा PROC_486        0x08    /* Intel 80486 */
#घोषणा PROC_PENTIUM    0x10    /* Intel 586 aka P5 aka Pentium */
#घोषणा PROC_SEXIUM	0x20	/* Intel 686 aka P6 aka Pentium Pro or MMX */
#घोषणा PROC_IA64	0x40	/* Intel IA64 processor */

/* PROC_i960: */
#घोषणा PROC_960RX      0x01    /* Intel 80960RC/RD */
#घोषणा PROC_960HX      0x02    /* Intel 80960HA/HD/HT */

/* PROC_MOTOROLA: */
#घोषणा PROC_68000      0x01    /* Motorola 68000 */
#घोषणा PROC_68010	0x02	/* Motorola 68010 */
#घोषणा PROC_68020      0x04    /* Motorola 68020 */
#घोषणा PROC_68030      0x08    /* Motorola 68030 */
#घोषणा PROC_68040      0x10    /* Motorola 68040 */

/* PROC_POWERPC */
#घोषणा PROC_PPC601		0x01	/* PowerPC 601 */
#घोषणा PROC_PPC603		0x02	/* PowerPC 603 */
#घोषणा PROC_PPC604		0x04	/* PowerPC 604 */

/* PROC_MIPS4000: */
#घोषणा PROC_R4000      0x01    /* MIPS R4000 */

/* Filetype - sigBYTE dsFiletype;       DISTINCT VALUES */
/* ------------------------------------------------------------------ */
#घोषणा FT_EXECUTABLE   0       /* Executable Program */
#घोषणा FT_SCRIPT       1       /* Script/Batch File??? */
#घोषणा FT_HBADRVR      2       /* HBA Driver */
#घोषणा FT_OTHERDRVR    3       /* Other Driver */
#घोषणा FT_IFS          4       /* Installable Fileप्रणाली Driver */
#घोषणा FT_ENGINE       5       /* DPT Engine */
#घोषणा FT_COMPDRVR     6       /* Compressed Driver Disk */
#घोषणा FT_LANGUAGE     7       /* Foreign Language file */
#घोषणा FT_FIRMWARE     8       /* Downloadable or actual Firmware */
#घोषणा FT_COMMMODL     9       /* Communications Module */
#घोषणा FT_INT13        10      /* INT 13 style HBA Driver */
#घोषणा FT_HELPखाता     11      /* Help file */
#घोषणा FT_LOGGER       12      /* Event Logger */
#घोषणा FT_INSTALL      13      /* An Install Program */
#घोषणा FT_LIBRARY      14      /* Storage Manager Real-Mode Calls */
#घोषणा FT_RESOURCE	15	/* Storage Manager Resource File */
#घोषणा FT_MODEM_DB	16	/* Storage Manager Modem Database */

/* Filetype flags - sigBYTE dsFiletypeFlags;    FLAG BITS */
/* ------------------------------------------------------------------ */
#घोषणा FTF_DLL         0x01    /* Dynamic Link Library */
#घोषणा FTF_NLM         0x02    /* Netware Loadable Module */
#घोषणा FTF_OVERLAYS    0x04    /* Uses overlays */
#घोषणा FTF_DEBUG       0x08    /* Debug version */
#घोषणा FTF_TSR         0x10    /* TSR */
#घोषणा FTF_SYS         0x20    /* DOS Loadable driver */
#घोषणा FTF_PROTECTED   0x40    /* Runs in रक्षित mode */
#घोषणा FTF_APP_SPEC    0x80    /* Application Specअगरic */
#घोषणा FTF_ROM		(FTF_SYS|FTF_TSR)	/* Special Case */

/* OEM - sigBYTE dsOEM;         DISTINCT VALUES */
/* ------------------------------------------------------------------ */
#घोषणा OEM_DPT         0       /* DPT */
#घोषणा OEM_ATT         1       /* ATT */
#घोषणा OEM_NEC         2       /* NEC */
#घोषणा OEM_ALPHA       3       /* Alphatronix */
#घोषणा OEM_AST         4       /* AST */
#घोषणा OEM_OLIVETTI    5       /* Olivetti */
#घोषणा OEM_SNI         6       /* Siemens/Nixकरोrf */
#घोषणा OEM_SUN         7       /* SUN Microप्रणालीs */

/* Operating System  - sigLONG dsOS;    FLAG BITS */
/* ------------------------------------------------------------------ */
#घोषणा OS_DOS          0x00000001 /* PC/MS-DOS				*/
#घोषणा OS_WINDOWS      0x00000002 /* Microsoft Winकरोws 3.x		*/
#घोषणा OS_WINDOWS_NT   0x00000004 /* Microsoft Winकरोws NT		*/
#घोषणा OS_OS2M         0x00000008 /* OS/2 1.2.x,MS 1.3.0,IBM 1.3.x - Monolithic */
#घोषणा OS_OS2L         0x00000010 /* Microsoft OS/2 1.301 - LADDR	*/
#घोषणा OS_OS22x        0x00000020 /* IBM OS/2 2.x			*/
#घोषणा OS_NW286        0x00000040 /* Novell NetWare 286		*/
#घोषणा OS_NW386        0x00000080 /* Novell NetWare 386		*/
#घोषणा OS_GEN_UNIX     0x00000100 /* Generic Unix			*/
#घोषणा OS_SCO_UNIX     0x00000200 /* SCO Unix				*/
#घोषणा OS_ATT_UNIX     0x00000400 /* ATT Unix				*/
#घोषणा OS_UNIXWARE     0x00000800 /* USL Unix				*/
#घोषणा OS_INT_UNIX     0x00001000 /* Interactive Unix			*/
#घोषणा OS_SOLARIS      0x00002000 /* SunSoft Solaris			*/
#घोषणा OS_QNX          0x00004000 /* QNX क्रम Tom Moch			*/
#घोषणा OS_NEXTSTEP     0x00008000 /* NeXTSTEP/OPENSTEP/MACH		*/
#घोषणा OS_BANYAN       0x00010000 /* Banyan Vines			*/
#घोषणा OS_OLIVETTI_UNIX 0x00020000/* Olivetti Unix			*/
#घोषणा OS_MAC_OS	0x00040000 /* Mac OS				*/
#घोषणा OS_WINDOWS_95	0x00080000 /* Microsoft Winकरोws '95		*/
#घोषणा OS_NW4x		0x00100000 /* Novell Netware 4.x		*/
#घोषणा OS_BSDI_UNIX	0x00200000 /* BSDi Unix BSD/OS 2.0 and up	*/
#घोषणा OS_AIX_UNIX     0x00400000 /* AIX Unix				*/
#घोषणा OS_FREE_BSD	0x00800000 /* FreeBSD Unix			*/
#घोषणा OS_LINUX	0x01000000 /* Linux				*/
#घोषणा OS_DGUX_UNIX	0x02000000 /* Data General Unix			*/
#घोषणा OS_SINIX_N      0x04000000 /* SNI SINIX-N			*/
#घोषणा OS_PLAN9	0x08000000 /* ATT Plan 9			*/
#घोषणा OS_TSX		0x10000000 /* SNH TSX-32			*/

#घोषणा OS_OTHER        0x80000000 /* Other				*/

/* Capabilities - sigWORD dsCapabilities;        FLAG BITS */
/* ------------------------------------------------------------------ */
#घोषणा CAP_RAID0       0x0001  /* RAID-0 */
#घोषणा CAP_RAID1       0x0002  /* RAID-1 */
#घोषणा CAP_RAID3       0x0004  /* RAID-3 */
#घोषणा CAP_RAID5       0x0008  /* RAID-5 */
#घोषणा CAP_SPAN        0x0010  /* Spanning */
#घोषणा CAP_PASS        0x0020  /* Provides passthrough */
#घोषणा CAP_OVERLAP     0x0040  /* Passthrough supports overlapped commands */
#घोषणा CAP_ASPI        0x0080  /* Supports ASPI Command Requests */
#घोषणा CAP_ABOVE16MB   0x0100  /* ISA Driver supports greater than 16MB */
#घोषणा CAP_EXTEND      0x8000  /* Extended info appears after description */
#अगर_घोषित SNI_MIPS
#घोषणा CAP_CACHEMODE   0x1000  /* dpt_क्रमce_cache is set in driver */
#पूर्ण_अगर

/* Devices Supported - sigWORD dsDeviceSupp;    FLAG BITS */
/* ------------------------------------------------------------------ */
#घोषणा DEV_DASD        0x0001  /* DASD (hard drives) */
#घोषणा DEV_TAPE        0x0002  /* Tape drives */
#घोषणा DEV_PRINTER     0x0004  /* Prपूर्णांकers */
#घोषणा DEV_PROC        0x0008  /* Processors */
#घोषणा DEV_WORM        0x0010  /* WORM drives */
#घोषणा DEV_CDROM       0x0020  /* CD-ROM drives */
#घोषणा DEV_SCANNER     0x0040  /* Scanners */
#घोषणा DEV_OPTICAL     0x0080  /* Optical Drives */
#घोषणा DEV_JUKEBOX     0x0100  /* Jukebox */
#घोषणा DEV_COMM        0x0200  /* Communications Devices */
#घोषणा DEV_OTHER       0x0400  /* Other Devices */
#घोषणा DEV_ALL         0xFFFF  /* All SCSI Devices */

/* Adapters Families Supported - sigWORD dsAdapterSupp; FLAG BITS */
/* ------------------------------------------------------------------ */
#घोषणा ADF_2001        0x0001  /* PM2001           */
#घोषणा ADF_2012A       0x0002  /* PM2012A          */
#घोषणा ADF_PLUS_ISA    0x0004  /* PM2011,PM2021    */
#घोषणा ADF_PLUS_EISA   0x0008  /* PM2012B,PM2022   */
#घोषणा ADF_SC3_ISA	0x0010  /* PM2021           */
#घोषणा ADF_SC3_EISA	0x0020  /* PM2022,PM2122, etc */
#घोषणा ADF_SC3_PCI	0x0040  /* SmartCache III PCI */
#घोषणा ADF_SC4_ISA	0x0080  /* SmartCache IV ISA */
#घोषणा ADF_SC4_EISA	0x0100  /* SmartCache IV EISA */
#घोषणा ADF_SC4_PCI	0x0200	/* SmartCache IV PCI */
#घोषणा ADF_SC5_PCI	0x0400	/* Fअगरth Generation I2O products */
/*
 *	Combinations of products
 */
#घोषणा ADF_ALL_2000	(ADF_2001|ADF_2012A)
#घोषणा ADF_ALL_PLUS	(ADF_PLUS_ISA|ADF_PLUS_EISA)
#घोषणा ADF_ALL_SC3	(ADF_SC3_ISA|ADF_SC3_EISA|ADF_SC3_PCI)
#घोषणा ADF_ALL_SC4	(ADF_SC4_ISA|ADF_SC4_EISA|ADF_SC4_PCI)
#घोषणा ADF_ALL_SC5	(ADF_SC5_PCI)
/* All EATA Cacheing Products */
#घोषणा ADF_ALL_CACHE	(ADF_ALL_PLUS|ADF_ALL_SC3|ADF_ALL_SC4)
/* All EATA Bus Mastering Products */
#घोषणा ADF_ALL_MASTER	(ADF_2012A|ADF_ALL_CACHE)
/* All EATA Adapter Products */
#घोषणा ADF_ALL_EATA	(ADF_2001|ADF_ALL_MASTER)
#घोषणा ADF_ALL		ADF_ALL_EATA

/* Application - sigWORD dsApplication;         FLAG BITS */
/* ------------------------------------------------------------------ */
#घोषणा APP_DPTMGR      0x0001  /* DPT Storage Manager */
#घोषणा APP_ENGINE      0x0002  /* DPT Engine */
#घोषणा APP_SYTOS       0x0004  /* Sytron Sytos Plus */
#घोषणा APP_CHEYENNE    0x0008  /* Cheyenne ARCServe + ARCSolo */
#घोषणा APP_MSCDEX      0x0010  /* Microsoft CD-ROM extensions */
#घोषणा APP_NOVABACK    0x0020  /* NovaStor Novaback */
#घोषणा APP_AIM         0x0040  /* Archive Inक्रमmation Manager */

/* Requirements - sigBYTE dsRequirements;         FLAG BITS             */
/* ------------------------------------------------------------------   */
#घोषणा REQ_SMARTROM    0x01    /* Requires SmartROM to be present      */
#घोषणा REQ_DPTDDL      0x02    /* Requires DPTDDL.SYS to be loaded     */
#घोषणा REQ_HBA_DRIVER  0x04    /* Requires an HBA driver to be loaded  */
#घोषणा REQ_ASPI_TRAN   0x08    /* Requires an ASPI Transport Modules   */
#घोषणा REQ_ENGINE      0x10    /* Requires a DPT Engine to be loaded   */
#घोषणा REQ_COMM_ENG    0x20    /* Requires a DPT Communications Engine */

/*
 * You may adjust dsDescription_size with an override to a value less than
 * 50 so that the काष्ठाure allocates less real space.
 */
#अगर (!defined(dsDescription_size))
# define dsDescription_size 50
#पूर्ण_अगर

प्रकार काष्ठा dpt_sig अणु
    अक्षर    dsSignature[6];      /* ALWAYS "dPtSiG" */
    sigBYTE dsSigVersion;        /* signature version (currently 1) */
    sigBYTE dsProcessorFamily;   /* what type of processor */
    sigBYTE dsProcessor;         /* precise processor */
    sigBYTE dsFiletype;          /* type of file */
    sigBYTE dsFiletypeFlags;     /* flags to specअगरy load type, etc. */
    sigBYTE dsOEM;               /* OEM file was created क्रम */
    sigINT  dsOS;                /* which Operating प्रणालीs */
    sigWORD dsCapabilities;      /* RAID levels, etc. */
    sigWORD dsDeviceSupp;        /* Types of SCSI devices supported */
    sigWORD dsAdapterSupp;       /* DPT adapter families supported */
    sigWORD dsApplication;       /* applications file is क्रम */
    sigBYTE dsRequirements;      /* Other driver dependencies */
    sigBYTE dsVersion;           /* 1 */
    sigBYTE dsRevision;          /* 'J' */
    sigBYTE dsSubRevision;       /* '9'   ' ' अगर N/A */
    sigBYTE dsMonth;             /* creation month */
    sigBYTE dsDay;               /* creation day */
    sigBYTE dsYear;              /* creation year since 1980 (1993=13) */
    /* description (शून्य terminated) */
    अक्षर  dsDescription[dsDescription_size];
पूर्ण dpt_sig_S;
/* 32 bytes minimum - with no description.  Put शून्य at description[0] */
/* 81 bytes maximum - with 49 अक्षरacter description plus शून्य. */

/* This line added at Roycroft's request */
/* Microsoft's NT compiler gets confused if you do a pack and don't */
/* restore it. */

#अगर_अघोषित NO_UNPACK
#अगर defined (_DPT_AIX)
#आशय options align=reset
#या_अगर defined (UNPACK_FOUR)
#आशय pack(4)
#अन्यथा
#आशय pack()
#पूर्ण_अगर  /* aix */
#पूर्ण_अगर
/* For the Macपूर्णांकosh */
#अगर_घोषित STRUCTALIGNMENTSUPPORTED
#आशय options align=reset
#पूर्ण_अगर

#पूर्ण_अगर
