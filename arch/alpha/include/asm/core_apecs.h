<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_APECS__H__
#घोषणा __ALPHA_APECS__H__

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

/*
 * APECS is the पूर्णांकernal name क्रम the 2107x chipset which provides
 * memory controller and PCI access क्रम the 21064 chip based प्रणालीs.
 *
 * This file is based on:
 *
 * DECchip 21071-AA and DECchip 21072-AA Core Logic Chipsets
 * Data Sheet
 *
 * EC-N0648-72
 *
 *
 * david.rusling@reo.mts.dec.com Initial Version.
 *
 */

/*
   An AVANTI *might* be an XL, and an XL has only 27 bits of ISA address
   that get passed through the PCI<->ISA bridge chip. So we've gotta use
   both winकरोws to max out the physical memory we can DMA to. Sigh...

   If we try a winकरोw at 0 क्रम 1GB as a work-around, we run पूर्णांकo conflicts
   with ISA/PCI bus memory which can't be relocated, like VGA aperture and
   BIOS ROMs. So we must put the winकरोws high enough to aव्योम these areas.

   We put winकरोw 1 at BUS 64Mb क्रम 64Mb, mapping physical 0 to 64Mb-1,
   and winकरोw 2 at BUS 1Gb क्रम 1Gb, mapping physical 0 to 1Gb-1.
   Yes, this करोes map 0 to 64Mb-1 twice, but only winकरोw 1 will actually
   be used क्रम that range (via virt_to_bus()).

   Note that we actually fudge the winकरोw 1 maximum as 48Mb instead of 64Mb,
   to keep virt_to_bus() from वापसing an address in the first winकरोw, क्रम
   a data area that goes beyond the 64Mb first DMA winकरोw.  Sigh...
   The fudge factor MUST match with <यंत्र/dma.h> MAX_DMA_ADDRESS, but
   we can't just use that here, because of header file looping... :-(

   Winकरोw 1 will be used क्रम all DMA from the ISA bus; yes, that करोes
   limit what memory an ISA floppy or sound card or Ethernet can touch, but
   it's also a known limitation on other platक्रमms as well. We use the
   same technique that is used on INTEL platक्रमms with similar limitation:
   set MAX_DMA_ADDRESS and clear some pages' DMAable flags during mem_init().
   We trust that any ISA bus device drivers will *always* ask क्रम DMAable
   memory explicitly via kदो_स्मृति()/get_मुक्त_pages() flags arguments.

   Note that most PCI bus devices' drivers करो *not* explicitly ask क्रम
   DMAable memory; they count on being able to DMA to any memory they
   get from kदो_स्मृति()/get_मुक्त_pages(). They will also use winकरोw 1 क्रम
   any physical memory accesses below 64Mb; the rest will be handled by
   winकरोw 2, maxing out at 1Gb of memory. I trust this is enough... :-)

   We hope that the area beक्रमe the first winकरोw is large enough so that
   there will be no overlap at the top end (64Mb). We *must* locate the
   PCI cards' memory just below window 1, so that there's still the
   possibility of being able to access it via SPARSE space. This is
   important क्रम cards such as the Matrox Millennium, whose Xserver
   wants to access memory-mapped रेजिस्टरs in byte and लघु lengths.

   Note that the XL is treated dअगरferently from the AVANTI, even though
   क्रम most other things they are identical. It didn't seem reasonable to
   make the AVANTI support pay क्रम the limitations of the XL. It is true,
   however, that an XL kernel will run on an AVANTI without problems.

   %%% All of this should be obviated by the ability to route
   everything through the iommu.
*/

/*
 * 21071-DA Control and Status रेजिस्टरs.
 * These are used क्रम PCI memory access.
 */
#घोषणा APECS_IOC_DCSR                  (IDENT_ADDR + 0x1A0000000UL)
#घोषणा APECS_IOC_PEAR                  (IDENT_ADDR + 0x1A0000020UL)
#घोषणा APECS_IOC_SEAR                  (IDENT_ADDR + 0x1A0000040UL)
#घोषणा APECS_IOC_DR1                   (IDENT_ADDR + 0x1A0000060UL)
#घोषणा APECS_IOC_DR2                   (IDENT_ADDR + 0x1A0000080UL)
#घोषणा APECS_IOC_DR3                   (IDENT_ADDR + 0x1A00000A0UL)

#घोषणा APECS_IOC_TB1R                  (IDENT_ADDR + 0x1A00000C0UL)
#घोषणा APECS_IOC_TB2R                  (IDENT_ADDR + 0x1A00000E0UL)

#घोषणा APECS_IOC_PB1R                  (IDENT_ADDR + 0x1A0000100UL)
#घोषणा APECS_IOC_PB2R                  (IDENT_ADDR + 0x1A0000120UL)

#घोषणा APECS_IOC_PM1R                  (IDENT_ADDR + 0x1A0000140UL)
#घोषणा APECS_IOC_PM2R                  (IDENT_ADDR + 0x1A0000160UL)

#घोषणा APECS_IOC_HAXR0                 (IDENT_ADDR + 0x1A0000180UL)
#घोषणा APECS_IOC_HAXR1                 (IDENT_ADDR + 0x1A00001A0UL)
#घोषणा APECS_IOC_HAXR2                 (IDENT_ADDR + 0x1A00001C0UL)

#घोषणा APECS_IOC_PMLT                  (IDENT_ADDR + 0x1A00001E0UL)

#घोषणा APECS_IOC_TLBTAG0               (IDENT_ADDR + 0x1A0000200UL)
#घोषणा APECS_IOC_TLBTAG1               (IDENT_ADDR + 0x1A0000220UL)
#घोषणा APECS_IOC_TLBTAG2               (IDENT_ADDR + 0x1A0000240UL)
#घोषणा APECS_IOC_TLBTAG3               (IDENT_ADDR + 0x1A0000260UL)
#घोषणा APECS_IOC_TLBTAG4               (IDENT_ADDR + 0x1A0000280UL)
#घोषणा APECS_IOC_TLBTAG5               (IDENT_ADDR + 0x1A00002A0UL)
#घोषणा APECS_IOC_TLBTAG6               (IDENT_ADDR + 0x1A00002C0UL)
#घोषणा APECS_IOC_TLBTAG7               (IDENT_ADDR + 0x1A00002E0UL)

#घोषणा APECS_IOC_TLBDATA0              (IDENT_ADDR + 0x1A0000300UL)
#घोषणा APECS_IOC_TLBDATA1              (IDENT_ADDR + 0x1A0000320UL)
#घोषणा APECS_IOC_TLBDATA2              (IDENT_ADDR + 0x1A0000340UL)
#घोषणा APECS_IOC_TLBDATA3              (IDENT_ADDR + 0x1A0000360UL)
#घोषणा APECS_IOC_TLBDATA4              (IDENT_ADDR + 0x1A0000380UL)
#घोषणा APECS_IOC_TLBDATA5              (IDENT_ADDR + 0x1A00003A0UL)
#घोषणा APECS_IOC_TLBDATA6              (IDENT_ADDR + 0x1A00003C0UL)
#घोषणा APECS_IOC_TLBDATA7              (IDENT_ADDR + 0x1A00003E0UL)

#घोषणा APECS_IOC_TBIA                  (IDENT_ADDR + 0x1A0000400UL)


/*
 * 21071-CA Control and Status रेजिस्टरs.
 * These are used to program memory timing,
 *  configure memory and initialise the B-Cache.
 */
#घोषणा APECS_MEM_GCR		        (IDENT_ADDR + 0x180000000UL)
#घोषणा APECS_MEM_EDSR		        (IDENT_ADDR + 0x180000040UL)
#घोषणा APECS_MEM_TAR  		        (IDENT_ADDR + 0x180000060UL)
#घोषणा APECS_MEM_ELAR		        (IDENT_ADDR + 0x180000080UL)
#घोषणा APECS_MEM_EHAR  		(IDENT_ADDR + 0x1800000a0UL)
#घोषणा APECS_MEM_SFT_RST		(IDENT_ADDR + 0x1800000c0UL)
#घोषणा APECS_MEM_LDxLAR 		(IDENT_ADDR + 0x1800000e0UL)
#घोषणा APECS_MEM_LDxHAR 		(IDENT_ADDR + 0x180000100UL)
#घोषणा APECS_MEM_GTR    		(IDENT_ADDR + 0x180000200UL)
#घोषणा APECS_MEM_RTR    		(IDENT_ADDR + 0x180000220UL)
#घोषणा APECS_MEM_VFPR   		(IDENT_ADDR + 0x180000240UL)
#घोषणा APECS_MEM_PDLDR  		(IDENT_ADDR + 0x180000260UL)
#घोषणा APECS_MEM_PDhDR  		(IDENT_ADDR + 0x180000280UL)

/* Bank x Base Address Register */
#घोषणा APECS_MEM_B0BAR  		(IDENT_ADDR + 0x180000800UL)
#घोषणा APECS_MEM_B1BAR  		(IDENT_ADDR + 0x180000820UL)
#घोषणा APECS_MEM_B2BAR  		(IDENT_ADDR + 0x180000840UL)
#घोषणा APECS_MEM_B3BAR  		(IDENT_ADDR + 0x180000860UL)
#घोषणा APECS_MEM_B4BAR  		(IDENT_ADDR + 0x180000880UL)
#घोषणा APECS_MEM_B5BAR  		(IDENT_ADDR + 0x1800008A0UL)
#घोषणा APECS_MEM_B6BAR  		(IDENT_ADDR + 0x1800008C0UL)
#घोषणा APECS_MEM_B7BAR  		(IDENT_ADDR + 0x1800008E0UL)
#घोषणा APECS_MEM_B8BAR  		(IDENT_ADDR + 0x180000900UL)

/* Bank x Configuration Register */
#घोषणा APECS_MEM_B0BCR  		(IDENT_ADDR + 0x180000A00UL)
#घोषणा APECS_MEM_B1BCR  		(IDENT_ADDR + 0x180000A20UL)
#घोषणा APECS_MEM_B2BCR  		(IDENT_ADDR + 0x180000A40UL)
#घोषणा APECS_MEM_B3BCR  		(IDENT_ADDR + 0x180000A60UL)
#घोषणा APECS_MEM_B4BCR  		(IDENT_ADDR + 0x180000A80UL)
#घोषणा APECS_MEM_B5BCR  		(IDENT_ADDR + 0x180000AA0UL)
#घोषणा APECS_MEM_B6BCR  		(IDENT_ADDR + 0x180000AC0UL)
#घोषणा APECS_MEM_B7BCR  		(IDENT_ADDR + 0x180000AE0UL)
#घोषणा APECS_MEM_B8BCR  		(IDENT_ADDR + 0x180000B00UL)

/* Bank x Timing Register A */
#घोषणा APECS_MEM_B0TRA  		(IDENT_ADDR + 0x180000C00UL)
#घोषणा APECS_MEM_B1TRA  		(IDENT_ADDR + 0x180000C20UL)
#घोषणा APECS_MEM_B2TRA  		(IDENT_ADDR + 0x180000C40UL)
#घोषणा APECS_MEM_B3TRA  		(IDENT_ADDR + 0x180000C60UL)
#घोषणा APECS_MEM_B4TRA  		(IDENT_ADDR + 0x180000C80UL)
#घोषणा APECS_MEM_B5TRA  		(IDENT_ADDR + 0x180000CA0UL)
#घोषणा APECS_MEM_B6TRA  		(IDENT_ADDR + 0x180000CC0UL)
#घोषणा APECS_MEM_B7TRA  		(IDENT_ADDR + 0x180000CE0UL)
#घोषणा APECS_MEM_B8TRA  		(IDENT_ADDR + 0x180000D00UL)

/* Bank x Timing Register B */
#घोषणा APECS_MEM_B0TRB                 (IDENT_ADDR + 0x180000E00UL)
#घोषणा APECS_MEM_B1TRB  		(IDENT_ADDR + 0x180000E20UL)
#घोषणा APECS_MEM_B2TRB  		(IDENT_ADDR + 0x180000E40UL)
#घोषणा APECS_MEM_B3TRB  		(IDENT_ADDR + 0x180000E60UL)
#घोषणा APECS_MEM_B4TRB  		(IDENT_ADDR + 0x180000E80UL)
#घोषणा APECS_MEM_B5TRB  		(IDENT_ADDR + 0x180000EA0UL)
#घोषणा APECS_MEM_B6TRB  		(IDENT_ADDR + 0x180000EC0UL)
#घोषणा APECS_MEM_B7TRB  		(IDENT_ADDR + 0x180000EE0UL)
#घोषणा APECS_MEM_B8TRB  		(IDENT_ADDR + 0x180000F00UL)


/*
 * Memory spaces:
 */
#घोषणा APECS_IACK_SC		        (IDENT_ADDR + 0x1b0000000UL)
#घोषणा APECS_CONF		        (IDENT_ADDR + 0x1e0000000UL)
#घोषणा APECS_IO			(IDENT_ADDR + 0x1c0000000UL)
#घोषणा APECS_SPARSE_MEM		(IDENT_ADDR + 0x200000000UL)
#घोषणा APECS_DENSE_MEM		        (IDENT_ADDR + 0x300000000UL)


/*
 * Bit definitions क्रम I/O Controller status रेजिस्टर 0:
 */
#घोषणा APECS_IOC_STAT0_CMD		0xf
#घोषणा APECS_IOC_STAT0_ERR		(1<<4)
#घोषणा APECS_IOC_STAT0_LOST		(1<<5)
#घोषणा APECS_IOC_STAT0_THIT		(1<<6)
#घोषणा APECS_IOC_STAT0_TREF		(1<<7)
#घोषणा APECS_IOC_STAT0_CODE_SHIFT	8
#घोषणा APECS_IOC_STAT0_CODE_MASK	0x7
#घोषणा APECS_IOC_STAT0_P_NBR_SHIFT	13
#घोषणा APECS_IOC_STAT0_P_NBR_MASK	0x7ffff

#घोषणा APECS_HAE_ADDRESS		APECS_IOC_HAXR1


/*
 * Data काष्ठाure क्रम handling APECS machine checks:
 */

काष्ठा el_apecs_mikasa_sysdata_mcheck
अणु
	अचिन्हित दीर्घ coma_gcr;
	अचिन्हित दीर्घ coma_edsr;
	अचिन्हित दीर्घ coma_ter;
	अचिन्हित दीर्घ coma_elar;
	अचिन्हित दीर्घ coma_ehar;
	अचिन्हित दीर्घ coma_ldlr;
	अचिन्हित दीर्घ coma_ldhr;
	अचिन्हित दीर्घ coma_base0;
	अचिन्हित दीर्घ coma_base1;
	अचिन्हित दीर्घ coma_base2;
	अचिन्हित दीर्घ coma_base3;
	अचिन्हित दीर्घ coma_cnfg0;
	अचिन्हित दीर्घ coma_cnfg1;
	अचिन्हित दीर्घ coma_cnfg2;
	अचिन्हित दीर्घ coma_cnfg3;
	अचिन्हित दीर्घ epic_dcsr;
	अचिन्हित दीर्घ epic_pear;
	अचिन्हित दीर्घ epic_sear;
	अचिन्हित दीर्घ epic_tbr1;
	अचिन्हित दीर्घ epic_tbr2;
	अचिन्हित दीर्घ epic_pbr1;
	अचिन्हित दीर्घ epic_pbr2;
	अचिन्हित दीर्घ epic_pmr1;
	अचिन्हित दीर्घ epic_pmr2;
	अचिन्हित दीर्घ epic_harx1;
	अचिन्हित दीर्घ epic_harx2;
	अचिन्हित दीर्घ epic_pmlt;
	अचिन्हित दीर्घ epic_tag0;
	अचिन्हित दीर्घ epic_tag1;
	अचिन्हित दीर्घ epic_tag2;
	अचिन्हित दीर्घ epic_tag3;
	अचिन्हित दीर्घ epic_tag4;
	अचिन्हित दीर्घ epic_tag5;
	अचिन्हित दीर्घ epic_tag6;
	अचिन्हित दीर्घ epic_tag7;
	अचिन्हित दीर्घ epic_data0;
	अचिन्हित दीर्घ epic_data1;
	अचिन्हित दीर्घ epic_data2;
	अचिन्हित दीर्घ epic_data3;
	अचिन्हित दीर्घ epic_data4;
	अचिन्हित दीर्घ epic_data5;
	अचिन्हित दीर्घ epic_data6;
	अचिन्हित दीर्घ epic_data7;

	अचिन्हित दीर्घ pceb_vid;
	अचिन्हित दीर्घ pceb_did;
	अचिन्हित दीर्घ pceb_revision;
	अचिन्हित दीर्घ pceb_command;
	अचिन्हित दीर्घ pceb_status;
	अचिन्हित दीर्घ pceb_latency;
	अचिन्हित दीर्घ pceb_control;
	अचिन्हित दीर्घ pceb_arbcon;
	अचिन्हित दीर्घ pceb_arbpri;

	अचिन्हित दीर्घ esc_id;
	अचिन्हित दीर्घ esc_revision;
	अचिन्हित दीर्घ esc_पूर्णांक0;
	अचिन्हित दीर्घ esc_पूर्णांक1;
	अचिन्हित दीर्घ esc_elcr0;
	अचिन्हित दीर्घ esc_elcr1;
	अचिन्हित दीर्घ esc_last_eisa;
	अचिन्हित दीर्घ esc_nmi_stat;

	अचिन्हित दीर्घ pci_ir;
	अचिन्हित दीर्घ pci_imr;
	अचिन्हित दीर्घ svr_mgr;
पूर्ण;

/* This क्रम the normal APECS machines.  */
काष्ठा el_apecs_sysdata_mcheck
अणु
	अचिन्हित दीर्घ coma_gcr;
	अचिन्हित दीर्घ coma_edsr;
	अचिन्हित दीर्घ coma_ter;
	अचिन्हित दीर्घ coma_elar;
	अचिन्हित दीर्घ coma_ehar;
	अचिन्हित दीर्घ coma_ldlr;
	अचिन्हित दीर्घ coma_ldhr;
	अचिन्हित दीर्घ coma_base0;
	अचिन्हित दीर्घ coma_base1;
	अचिन्हित दीर्घ coma_base2;
	अचिन्हित दीर्घ coma_cnfg0;
	अचिन्हित दीर्घ coma_cnfg1;
	अचिन्हित दीर्घ coma_cnfg2;
	अचिन्हित दीर्घ epic_dcsr;
	अचिन्हित दीर्घ epic_pear;
	अचिन्हित दीर्घ epic_sear;
	अचिन्हित दीर्घ epic_tbr1;
	अचिन्हित दीर्घ epic_tbr2;
	अचिन्हित दीर्घ epic_pbr1;
	अचिन्हित दीर्घ epic_pbr2;
	अचिन्हित दीर्घ epic_pmr1;
	अचिन्हित दीर्घ epic_pmr2;
	अचिन्हित दीर्घ epic_harx1;
	अचिन्हित दीर्घ epic_harx2;
	अचिन्हित दीर्घ epic_pmlt;
	अचिन्हित दीर्घ epic_tag0;
	अचिन्हित दीर्घ epic_tag1;
	अचिन्हित दीर्घ epic_tag2;
	अचिन्हित दीर्घ epic_tag3;
	अचिन्हित दीर्घ epic_tag4;
	अचिन्हित दीर्घ epic_tag5;
	अचिन्हित दीर्घ epic_tag6;
	अचिन्हित दीर्घ epic_tag7;
	अचिन्हित दीर्घ epic_data0;
	अचिन्हित दीर्घ epic_data1;
	अचिन्हित दीर्घ epic_data2;
	अचिन्हित दीर्घ epic_data3;
	अचिन्हित दीर्घ epic_data4;
	अचिन्हित दीर्घ epic_data5;
	अचिन्हित दीर्घ epic_data6;
	अचिन्हित दीर्घ epic_data7;
पूर्ण;

काष्ठा el_apecs_procdata
अणु
	अचिन्हित दीर्घ paltemp[32];  /* PAL TEMP REGS. */
	/* EV4-specअगरic fields */
	अचिन्हित दीर्घ exc_addr;     /* Address of excepting inकाष्ठाion. */
	अचिन्हित दीर्घ exc_sum;      /* Summary of arithmetic traps. */
	अचिन्हित दीर्घ exc_mask;     /* Exception mask (from exc_sum). */
	अचिन्हित दीर्घ iccsr;        /* IBox hardware enables. */
	अचिन्हित दीर्घ pal_base;     /* Base address क्रम PALcode. */
	अचिन्हित दीर्घ hier;         /* Hardware Interrupt Enable. */
	अचिन्हित दीर्घ hirr;         /* Hardware Interrupt Request. */
	अचिन्हित दीर्घ csr;          /* D-stream fault info. */
	अचिन्हित दीर्घ dc_stat;      /* D-cache status (ECC/Parity Err). */
	अचिन्हित दीर्घ dc_addr;      /* EV3 Phys Addr क्रम ECC/DPERR. */
	अचिन्हित दीर्घ abox_ctl;     /* ABox Control Register. */
	अचिन्हित दीर्घ biu_stat;     /* BIU Status. */
	अचिन्हित दीर्घ biu_addr;     /* BUI Address. */
	अचिन्हित दीर्घ biu_ctl;      /* BIU Control. */
	अचिन्हित दीर्घ fill_syndrome;/* For correcting ECC errors. */
	अचिन्हित दीर्घ fill_addr;    /* Cache block which was being पढ़ो */
	अचिन्हित दीर्घ va;           /* Effective VA of fault or miss. */
	अचिन्हित दीर्घ bc_tag;       /* Backup Cache Tag Probe Results.*/
पूर्ण;


#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * Unlike Jensen, the APECS machines have no concept of local
 * I/O---everything goes over the PCI bus.
 *
 * There is plenty room क्रम optimization here.  In particular,
 * the Alpha's insb/insw/extb/extw should be useful in moving
 * data to/from the right byte-lanes.
 */

#घोषणा vip	अस्थिर पूर्णांक __क्रमce *
#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक __क्रमce *
#घोषणा vulp	अस्थिर अचिन्हित दीर्घ __क्रमce *

#घोषणा APECS_SET_HAE						\
	करो अणु							\
		अगर (addr >= (1UL << 24)) अणु			\
			अचिन्हित दीर्घ msb = addr & 0xf8000000;	\
			addr -= msb;				\
			set_hae(msb);				\
		पूर्ण						\
	पूर्ण जबतक (0)

__EXTERN_INLINE अचिन्हित पूर्णांक apecs_ioपढ़ो8(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ result, base_and_type;

	अगर (addr >= APECS_DENSE_MEM) अणु
		addr -= APECS_DENSE_MEM;
		APECS_SET_HAE;
		base_and_type = APECS_SPARSE_MEM + 0x00;
	पूर्ण अन्यथा अणु
		addr -= APECS_IO;
		base_and_type = APECS_IO + 0x00;
	पूर्ण

	result = *(vip) ((addr << 5) + base_and_type);
	वापस __kernel_extbl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम apecs_ioग_लिखो8(u8 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ w, base_and_type;

	अगर (addr >= APECS_DENSE_MEM) अणु
		addr -= APECS_DENSE_MEM;
		APECS_SET_HAE;
		base_and_type = APECS_SPARSE_MEM + 0x00;
	पूर्ण अन्यथा अणु
		addr -= APECS_IO;
		base_and_type = APECS_IO + 0x00;
	पूर्ण

	w = __kernel_insbl(b, addr & 3);
	*(vuip) ((addr << 5) + base_and_type) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक apecs_ioपढ़ो16(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ result, base_and_type;

	अगर (addr >= APECS_DENSE_MEM) अणु
		addr -= APECS_DENSE_MEM;
		APECS_SET_HAE;
		base_and_type = APECS_SPARSE_MEM + 0x08;
	पूर्ण अन्यथा अणु
		addr -= APECS_IO;
		base_and_type = APECS_IO + 0x08;
	पूर्ण

	result = *(vip) ((addr << 5) + base_and_type);
	वापस __kernel_extwl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम apecs_ioग_लिखो16(u16 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ w, base_and_type;

	अगर (addr >= APECS_DENSE_MEM) अणु
		addr -= APECS_DENSE_MEM;
		APECS_SET_HAE;
		base_and_type = APECS_SPARSE_MEM + 0x08;
	पूर्ण अन्यथा अणु
		addr -= APECS_IO;
		base_and_type = APECS_IO + 0x08;
	पूर्ण

	w = __kernel_inswl(b, addr & 3);
	*(vuip) ((addr << 5) + base_and_type) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक apecs_ioपढ़ो32(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr < APECS_DENSE_MEM)
		addr = ((addr - APECS_IO) << 5) + APECS_IO + 0x18;
	वापस *(vuip)addr;
पूर्ण

__EXTERN_INLINE व्योम apecs_ioग_लिखो32(u32 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr < APECS_DENSE_MEM)
		addr = ((addr - APECS_IO) << 5) + APECS_IO + 0x18;
	*(vuip)addr = b;
पूर्ण

__EXTERN_INLINE व्योम __iomem *apecs_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + APECS_IO);
पूर्ण

__EXTERN_INLINE व्योम __iomem *apecs_ioremap(अचिन्हित दीर्घ addr,
					    अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + APECS_DENSE_MEM);
पूर्ण

__EXTERN_INLINE पूर्णांक apecs_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= IDENT_ADDR + 0x180000000UL;
पूर्ण

__EXTERN_INLINE पूर्णांक apecs_is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr >= APECS_DENSE_MEM;
पूर्ण

#अघोषित APECS_SET_HAE

#अघोषित vip
#अघोषित vuip
#अघोषित vulp

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		apecs
#घोषणा apecs_trivial_io_bw	0
#घोषणा apecs_trivial_io_lq	0
#घोषणा apecs_trivial_rw_bw	2
#घोषणा apecs_trivial_rw_lq	1
#घोषणा apecs_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_APECS__H__ */
