<शैली गुरु>
#अगर_अघोषित __PARISC_PATPDC_H
#घोषणा __PARISC_PATPDC_H

/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright 2000 (c) Hewlett Packard (Paul Bame <bame()spam.parisc-linux.org>)
 * Copyright 2000,2004 (c) Grant Grundler <grundler()nahspam.parisc-linux.org>
 */


#घोषणा PDC_PAT_CELL           	64L   /* Interface क्रम gaining and 
                                         * manipulatin g cell state within PD */
#घोषणा PDC_PAT_CELL_GET_NUMBER    0L   /* Return Cell number */
#घोषणा PDC_PAT_CELL_GET_INFO      1L   /* Returns info about Cell */
#घोषणा PDC_PAT_CELL_MODULE        2L   /* Returns info about Module */
#घोषणा PDC_PAT_CELL_SET_ATTENTION 9L   /* Set Cell Attention indicator */
#घोषणा PDC_PAT_CELL_NUMBER_TO_LOC 10L   /* Cell Number -> Location */
#घोषणा PDC_PAT_CELL_WALK_FABRIC   11L   /* Walk the Fabric */
#घोषणा PDC_PAT_CELL_GET_RDT_SIZE  12L   /* Return Route Distance Table Sizes */
#घोषणा PDC_PAT_CELL_GET_RDT       13L   /* Return Route Distance Tables */
#घोषणा PDC_PAT_CELL_GET_LOCAL_PDH_SZ 14L /* Read Local PDH Buffer Size */
#घोषणा PDC_PAT_CELL_SET_LOCAL_PDH    15L  /* Write Local PDH Buffer */
#घोषणा PDC_PAT_CELL_GET_REMOTE_PDH_SZ 16L /* Return Remote PDH Buffer Size */
#घोषणा PDC_PAT_CELL_GET_REMOTE_PDH 17L /* Read Remote PDH Buffer */
#घोषणा PDC_PAT_CELL_GET_DBG_INFO   128L  /* Return DBG Buffer Info */
#घोषणा PDC_PAT_CELL_CHANGE_ALIAS   129L  /* Change Non-Equivalent Alias Chacking */


/*
** Arg to PDC_PAT_CELL_MODULE memaddr[4]
**
** Addresses on the Merced Bus != all Runway Bus addresses.
** This is पूर्णांकended क्रम programming SBA/LBA chips range रेजिस्टरs.
*/
#घोषणा IO_VIEW      0UL
#घोषणा PA_VIEW      1UL

/* PDC_PAT_CELL_MODULE entity type values */
#घोषणा	PAT_ENTITY_CA	0	/* central agent */
#घोषणा	PAT_ENTITY_PROC	1	/* processor */
#घोषणा	PAT_ENTITY_MEM	2	/* memory controller */
#घोषणा	PAT_ENTITY_SBA	3	/* प्रणाली bus adapter */
#घोषणा	PAT_ENTITY_LBA	4	/* local bus adapter */
#घोषणा	PAT_ENTITY_PBC	5	/* processor bus converter */
#घोषणा	PAT_ENTITY_XBC	6	/* crossbar fabric connect */
#घोषणा	PAT_ENTITY_RC	7	/* fabric पूर्णांकerconnect */

/* PDC_PAT_CELL_MODULE address range type values */
#घोषणा PAT_PBNUM           0         /* PCI Bus Number */
#घोषणा PAT_LMMIO           1         /* < 4G MMIO Space */
#घोषणा PAT_GMMIO           2         /* > 4G MMIO Space */
#घोषणा PAT_NPIOP           3         /* Non Postable I/O Port Space */
#घोषणा PAT_PIOP            4         /* Postable I/O Port Space */
#घोषणा PAT_AHPA            5         /* Addional HPA Space */
#घोषणा PAT_UFO             6         /* HPA Space (UFO क्रम Mariposa) */
#घोषणा PAT_GNIP            7         /* GNI Reserved Space */



/* PDC PAT CHASSIS LOG -- Platक्रमm logging & क्रमward progress functions */

#घोषणा PDC_PAT_CHASSIS_LOG		65L
#घोषणा PDC_PAT_CHASSIS_WRITE_LOG    	0L /* Write Log Entry */
#घोषणा PDC_PAT_CHASSIS_READ_LOG     	1L /* Read  Log Entry */


/* PDC PAT COMPLEX */

#घोषणा PDC_PAT_COMPLEX			66L

/* PDC PAT CPU  -- CPU configuration within the protection करोमुख्य */

#घोषणा PDC_PAT_CPU                	67L
#घोषणा PDC_PAT_CPU_INFO            	0L /* Return CPU config info */
#घोषणा PDC_PAT_CPU_DELETE          	1L /* Delete CPU */
#घोषणा PDC_PAT_CPU_ADD             	2L /* Add    CPU */
#घोषणा PDC_PAT_CPU_GET_NUMBER      	3L /* Return CPU Number */
#घोषणा PDC_PAT_CPU_GET_HPA         	4L /* Return CPU HPA */
#घोषणा PDC_PAT_CPU_STOP            	5L /* Stop   CPU */
#घोषणा PDC_PAT_CPU_RENDEZVOUS      	6L /* Rendezvous CPU */
#घोषणा PDC_PAT_CPU_GET_CLOCK_INFO  	7L /* Return CPU Clock info */
#घोषणा PDC_PAT_CPU_GET_RENDEZVOUS_STATE 8L /* Return Rendezvous State */
#घोषणा PDC_PAT_CPU_PLUNGE_FABRIC 	128L /* Plunge Fabric */
#घोषणा PDC_PAT_CPU_UPDATE_CACHE_CLEANSING 129L /* Manipulate Cache 
                                                 * Cleansing Mode */
/*  PDC PAT EVENT -- Platक्रमm Events */

#घोषणा PDC_PAT_EVENT              	68L
#घोषणा PDC_PAT_EVENT_GET_CAPS     	0L /* Get Capabilities */
#घोषणा PDC_PAT_EVENT_SET_MODE     	1L /* Set Notअगरication Mode */
#घोषणा PDC_PAT_EVENT_SCAN         	2L /* Scan Event */
#घोषणा PDC_PAT_EVENT_HANDLE       	3L /* Handle Event */
#घोषणा PDC_PAT_EVENT_GET_NB_CALL  	4L /* Get Non-Blocking call Args */

/*  PDC PAT HPMC -- Cause processor to go पूर्णांकo spin loop, and रुको
 *  			क्रम wake up from Monarch Processor.
 */

#घोषणा PDC_PAT_HPMC               70L
#घोषणा PDC_PAT_HPMC_RENDEZ_CPU     0L /* go पूर्णांकo spin loop */
#घोषणा PDC_PAT_HPMC_SET_PARAMS     1L /* Allows OS to specअगरy पूर्णांकr which PDC 
                                        * will use to पूर्णांकerrupt OS during
                                        * machine check rendezvous */

/* parameters क्रम PDC_PAT_HPMC_SET_PARAMS: */
#घोषणा HPMC_SET_PARAMS_INTR 	    1L /* Rendezvous Interrupt */
#घोषणा HPMC_SET_PARAMS_WAKE 	    2L /* Wake up processor */


/*  PDC PAT IO  -- On-line services क्रम I/O modules */

#घोषणा PDC_PAT_IO                  71L
#घोषणा PDC_PAT_IO_GET_SLOT_STATUS   	5L /* Get Slot Status Info*/
#घोषणा PDC_PAT_IO_GET_LOC_FROM_HARDWARE 6L /* Get Physical Location from */
                                            /* Hardware Path */
#घोषणा PDC_PAT_IO_GET_HARDWARE_FROM_LOC 7L /* Get Hardware Path from 
                                             * Physical Location */
#घोषणा PDC_PAT_IO_GET_PCI_CONFIG_FROM_HW 11L /* Get PCI Configuration
                                               * Address from Hardware Path */
#घोषणा PDC_PAT_IO_GET_HW_FROM_PCI_CONFIG 12L /* Get Hardware Path 
                                               * from PCI Configuration Address */
#घोषणा PDC_PAT_IO_READ_HOST_BRIDGE_INFO 13L  /* Read Host Bridge State Info */
#घोषणा PDC_PAT_IO_CLEAR_HOST_BRIDGE_INFO 14L /* Clear Host Bridge State Info*/
#घोषणा PDC_PAT_IO_GET_PCI_ROUTING_TABLE_SIZE 15L /* Get PCI INT Routing Table 
                                                   * Size */
#घोषणा PDC_PAT_IO_GET_PCI_ROUTING_TABLE  16L /* Get PCI INT Routing Table */
#घोषणा PDC_PAT_IO_GET_HINT_TABLE_SIZE 	17L /* Get Hपूर्णांक Table Size */
#घोषणा PDC_PAT_IO_GET_HINT_TABLE   	18L /* Get Hपूर्णांक Table */
#घोषणा PDC_PAT_IO_PCI_CONFIG_READ  	19L /* PCI Config Read */
#घोषणा PDC_PAT_IO_PCI_CONFIG_WRITE 	20L /* PCI Config Write */
#घोषणा PDC_PAT_IO_GET_NUM_IO_SLOTS 	21L /* Get Number of I/O Bay Slots in 
                                       		  * Cabinet */
#घोषणा PDC_PAT_IO_GET_LOC_IO_SLOTS 	22L /* Get Physical Location of I/O */
                                   		     /* Bay Slots in Cabinet */
#घोषणा PDC_PAT_IO_BAY_STATUS_INFO  	28L /* Get I/O Bay Slot Status Info */
#घोषणा PDC_PAT_IO_GET_PROC_VIEW        29L /* Get Processor view of IO address */
#घोषणा PDC_PAT_IO_PROG_SBA_सूची_RANGE   30L /* Program directed range */


/* PDC PAT MEM  -- Manage memory page deallocation */

#घोषणा PDC_PAT_MEM            72L
#घोषणा PDC_PAT_MEM_PD_INFO     	0L /* Return PDT info क्रम PD       */
#घोषणा PDC_PAT_MEM_PD_CLEAR    	1L /* Clear PDT क्रम PD             */
#घोषणा PDC_PAT_MEM_PD_READ     	2L /* Read PDT entries क्रम PD      */
#घोषणा PDC_PAT_MEM_PD_RESET    	3L /* Reset clear bit क्रम PD       */
#घोषणा PDC_PAT_MEM_CELL_INFO   	5L /* Return PDT info For Cell     */
#घोषणा PDC_PAT_MEM_CELL_CLEAR  	6L /* Clear PDT For Cell           */
#घोषणा PDC_PAT_MEM_CELL_READ   	7L /* Read PDT entries For Cell    */
#घोषणा PDC_PAT_MEM_CELL_RESET  	8L /* Reset clear bit For Cell     */
#घोषणा PDC_PAT_MEM_SETGM		9L /* Set Good Memory value        */
#घोषणा PDC_PAT_MEM_ADD_PAGE		10L /* ADDs a page to the cell      */
#घोषणा PDC_PAT_MEM_ADDRESS		11L /* Get Physical Location From   */
					    /* Memory Address               */
#घोषणा PDC_PAT_MEM_GET_TXT_SIZE   	12L /* Get Formatted Text Size   */
#घोषणा PDC_PAT_MEM_GET_PD_TXT     	13L /* Get PD Formatted Text     */
#घोषणा PDC_PAT_MEM_GET_CELL_TXT   	14L /* Get Cell Formatted Text   */
#घोषणा PDC_PAT_MEM_RD_STATE_INFO  	15L /* Read Mem Module State Info*/
#घोषणा PDC_PAT_MEM_CLR_STATE_INFO 	16L /*Clear Mem Module State Info*/
#घोषणा PDC_PAT_MEM_CLEAN_RANGE    	128L /*Clean Mem in specअगरic range*/
#घोषणा PDC_PAT_MEM_GET_TBL_SIZE   	131L /* Get Memory Table Size     */
#घोषणा PDC_PAT_MEM_GET_TBL        	132L /* Get Memory Table          */


/* PDC PAT NVOLATILE  --  Access Non-Volatile Memory */

#घोषणा PDC_PAT_NVOLATILE	73L
#घोषणा PDC_PAT_NVOLATILE_READ		0L /* Read Non-Volatile Memory   */
#घोषणा PDC_PAT_NVOLATILE_WRITE		1L /* Write Non-Volatile Memory  */
#घोषणा PDC_PAT_NVOLATILE_GET_SIZE	2L /* Return size of NVM         */
#घोषणा PDC_PAT_NVOLATILE_VERIFY	3L /* Verअगरy contents of NVM     */
#घोषणा PDC_PAT_NVOLATILE_INIT		4L /* Initialize NVM             */

/* PDC PAT PD */
#घोषणा PDC_PAT_PD		74L         /* Protection Doमुख्य Info   */
#घोषणा PDC_PAT_PD_GET_ADDR_MAP		0L  /* Get Address Map          */
#घोषणा PDC_PAT_PD_GET_PDC_INTERF_REV	1L  /* Get PDC Interface Revisions */

#घोषणा PDC_PAT_CAPABILITY_BIT_PDC_SERIALIZE	(1UL << 0)
#घोषणा PDC_PAT_CAPABILITY_BIT_PDC_POLLING	(1UL << 1)
#घोषणा PDC_PAT_CAPABILITY_BIT_PDC_NBC		(1UL << 2) /* non-blocking calls */
#घोषणा PDC_PAT_CAPABILITY_BIT_PDC_UFO		(1UL << 3)
#घोषणा PDC_PAT_CAPABILITY_BIT_PDC_IODC_32	(1UL << 4)
#घोषणा PDC_PAT_CAPABILITY_BIT_PDC_IODC_64	(1UL << 5)
#घोषणा PDC_PAT_CAPABILITY_BIT_PDC_HPMC_RENDEZ	(1UL << 6)
#घोषणा PDC_PAT_CAPABILITY_BIT_SIMULTANEOUS_PTLB (1UL << 7)

/* PDC_PAT_PD_GET_ADDR_MAP entry types */
#घोषणा PAT_MEMORY_DESCRIPTOR		1   

/* PDC_PAT_PD_GET_ADDR_MAP memory types */
#घोषणा PAT_MEMTYPE_MEMORY		0
#घोषणा PAT_MEMTYPE_FIRMWARE		4

/* PDC_PAT_PD_GET_ADDR_MAP memory usage */
#घोषणा PAT_MEMUSE_GENERAL		0
#घोषणा PAT_MEMUSE_GI			128
#घोषणा PAT_MEMUSE_GNI			129

/* PDC PAT REGISTER TOC */
#घोषणा PDC_PAT_REGISTER_TOC	75L
#घोषणा PDC_PAT_TOC_REGISTER_VECTOR	0L /* Register TOC Vector */
#घोषणा PDC_PAT_TOC_READ_VECTOR		1L /* Read TOC Vector     */

/* PDC PAT SYSTEM_INFO */
#घोषणा PDC_PAT_SYSTEM_INFO	76L
/* PDC_PAT_SYSTEM_INFO uses the same options as PDC_SYSTEM_INFO function. */

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_64BIT
#घोषणा is_pdc_pat()	(PDC_TYPE_PAT == pdc_type)
बाह्य पूर्णांक pdc_pat_get_irt_size(अचिन्हित दीर्घ *num_entries, अचिन्हित दीर्घ cell_num);
बाह्य पूर्णांक pdc_pat_get_irt(व्योम *r_addr, अचिन्हित दीर्घ cell_num);
#अन्यथा	/* ! CONFIG_64BIT */
/* No PAT support क्रम 32-bit kernels...sorry */
#घोषणा is_pdc_pat()	(0)
#घोषणा pdc_pat_get_irt_size(num_entries, cell_numn)	PDC_BAD_PROC
#घोषणा pdc_pat_get_irt(r_addr, cell_num)		PDC_BAD_PROC
#पूर्ण_अगर	/* ! CONFIG_64BIT */


काष्ठा pdc_pat_cell_num अणु
	अचिन्हित दीर्घ cell_num;
	अचिन्हित दीर्घ cell_loc;
पूर्ण;

काष्ठा pdc_pat_cpu_num अणु
	अचिन्हित दीर्घ cpu_num;
	अचिन्हित दीर्घ cpu_loc;
पूर्ण;

काष्ठा pdc_pat_mem_retinfo अणु /* PDC_PAT_MEM/PDC_PAT_MEM_PD_INFO (वापस info) */
	अचिन्हित पूर्णांक ke;	/* bit 0: memory inside good memory? */
	अचिन्हित पूर्णांक current_pdt_entries:16;
	अचिन्हित पूर्णांक max_pdt_entries:16;
	अचिन्हित दीर्घ Cs_biपंचांगap;
	अचिन्हित दीर्घ Ic_biपंचांगap;
	अचिन्हित दीर्घ good_mem;
	अचिन्हित दीर्घ first_dbe_loc; /* first location of द्विगुन bit error */
	अचिन्हित दीर्घ clear_समय; /* last PDT clear समय (since Jan 1970) */
पूर्ण;

काष्ठा pdc_pat_mem_cell_pdt_retinfo अणु /* PDC_PAT_MEM/PDC_PAT_MEM_CELL_INFO */
	u64 reserved:32;
	u64 cs:1;		/* clear status: cleared since the last call? */
	u64 current_pdt_entries:15;
	u64 ic:1;		/* पूर्णांकerleaving had to be changed ? */
	u64 max_pdt_entries:15;
	अचिन्हित दीर्घ good_mem;
	अचिन्हित दीर्घ first_dbe_loc; /* first location of द्विगुन bit error */
	अचिन्हित दीर्घ clear_समय; /* last PDT clear समय (since Jan 1970) */
पूर्ण;


काष्ठा pdc_pat_mem_पढ़ो_pd_retinfo अणु /* PDC_PAT_MEM/PDC_PAT_MEM_PD_READ */
	अचिन्हित दीर्घ actual_count_bytes;
	अचिन्हित दीर्घ pdt_entries;
पूर्ण;

काष्ठा pdc_pat_mem_phys_mem_location अणु /* PDC_PAT_MEM/PDC_PAT_MEM_ADDRESS */
	u64 cabinet:8;
	u64 ign1:8;
	u64 ign2:8;
	u64 cell_slot:8;
	u64 ign3:8;
	u64 dimm_slot:8; /* DIMM slot, e.g. 0x1A, 0x2B, show user hex value! */
	u64 ign4:8;
	u64 source:4; /* क्रम mem: always 0x07 */
	u64 source_detail:4; /* क्रम mem: always 0x04 (SIMM or DIMM) */
पूर्ण;

काष्ठा pdc_pat_pd_addr_map_entry अणु
	अचिन्हित अक्षर entry_type;       /* 1 = Memory Descriptor Entry Type */
	अचिन्हित अक्षर reserve1[5];
	अचिन्हित अक्षर memory_type;
	अचिन्हित अक्षर memory_usage;
	अचिन्हित दीर्घ paddr;
	अचिन्हित पूर्णांक  pages;            /* Length in 4K pages */
	अचिन्हित पूर्णांक  reserve2;
	अचिन्हित दीर्घ cell_map;
पूर्ण;

/********************************************************************
* PDC_PAT_CELL[Return Cell Module] memaddr[0] conf_base_addr
* ----------------------------------------------------------
* Bit  0 to 51 - conf_base_addr
* Bit 52 to 62 - reserved
* Bit       63 - endianess bit
********************************************************************/
#घोषणा PAT_GET_CBA(value) ((value) & 0xfffffffffffff000UL)

/********************************************************************
* PDC_PAT_CELL[Return Cell Module] memaddr[1] mod_info
* ----------------------------------------------------
* Bit  0 to  7 - entity type
*    0 = central agent,            1 = processor,
*    2 = memory controller,        3 = प्रणाली bus adapter,
*    4 = local bus adapter,        5 = processor bus converter,
*    6 = crossbar fabric connect,  7 = fabric पूर्णांकerconnect,
*    8 to 254 reserved,            255 = unknown.
* Bit  8 to 15 - DVI
* Bit 16 to 23 - IOC functions
* Bit 24 to 39 - reserved
* Bit 40 to 63 - mod_pages
*    number of 4K pages a module occupies starting at conf_base_addr
********************************************************************/
#घोषणा PAT_GET_ENTITY(value)	(((value) >> 56) & 0xffUL)
#घोषणा PAT_GET_DVI(value)	(((value) >> 48) & 0xffUL)
#घोषणा PAT_GET_IOC(value)	(((value) >> 40) & 0xffUL)
#घोषणा PAT_GET_MOD_PAGES(value) ((value) & 0xffffffUL)


/*
** PDC_PAT_CELL_GET_INFO वापस block
*/
प्रकार काष्ठा pdc_pat_cell_info_rtn_block अणु
	अचिन्हित दीर्घ pdc_rev;
	अचिन्हित दीर्घ capabilities; /* see PDC_PAT_CAPABILITY_BIT_* */
	अचिन्हित दीर्घ reserved0[2];
	अचिन्हित दीर्घ cell_info;	/* 0x20 */
	अचिन्हित दीर्घ cell_phys_location;
	अचिन्हित दीर्घ cpu_info;
	अचिन्हित दीर्घ cpu_speed;
	अचिन्हित दीर्घ io_chassis_phys_location;
	अचिन्हित दीर्घ cell_io_inक्रमmation;
	अचिन्हित दीर्घ reserved1[2];
	अचिन्हित दीर्घ io_slot_info_size; /* 0x60 */
	काष्ठा अणु
		अचिन्हित दीर्घ header, info0, info1;
		अचिन्हित दीर्घ phys_loc, hw_path;
	पूर्ण io_slot[16];
	अचिन्हित दीर्घ cell_mem_size;	/* 0x2e8 */
	अचिन्हित दीर्घ cell_dimm_info_size;
	अचिन्हित दीर्घ dimm_info[16];
	अचिन्हित दीर्घ fabric_info_size;	/* 0x3f8 */
	काष्ठा अणु			/* 0x380 */
		अचिन्हित दीर्घ fabric_info_xbc_port;
		अचिन्हित दीर्घ rc_attached_to_xbc;
	पूर्ण xbc[8*4];
पूर्ण pdc_pat_cell_info_rtn_block_t;


/* FIXME: mod[508] should really be a जोड़ of the various mod components */
काष्ठा pdc_pat_cell_mod_maddr_block अणु	/* PDC_PAT_CELL_MODULE */
	अचिन्हित दीर्घ cba;		/* func 0 cfg space address */
	अचिन्हित दीर्घ mod_info;		/* module inक्रमmation */
	अचिन्हित दीर्घ mod_location;	/* physical location of the module */
	काष्ठा hardware_path mod_path;	/* module path (device path - layers) */
	अचिन्हित दीर्घ mod[508];		/* PAT cell module components */
पूर्ण __attribute__((aligned(8))) ;

प्रकार काष्ठा pdc_pat_cell_mod_maddr_block pdc_pat_cell_mod_maddr_block_t;


बाह्य पूर्णांक pdc_pat_chassis_send_log(अचिन्हित दीर्घ status, अचिन्हित दीर्घ data);
बाह्य पूर्णांक pdc_pat_cell_get_number(काष्ठा pdc_pat_cell_num *cell_info);
बाह्य पूर्णांक pdc_pat_cell_info(काष्ठा pdc_pat_cell_info_rtn_block *info,
		अचिन्हित दीर्घ *actcnt, अचिन्हित दीर्घ offset,
		अचिन्हित दीर्घ cell_number);
बाह्य पूर्णांक pdc_pat_cell_module(अचिन्हित दीर्घ *actcnt, अचिन्हित दीर्घ ploc,
		अचिन्हित दीर्घ mod, अचिन्हित दीर्घ view_type, व्योम *mem_addr);
बाह्य पूर्णांक pdc_pat_cell_num_to_loc(व्योम *, अचिन्हित दीर्घ);

बाह्य पूर्णांक pdc_pat_cpu_get_number(काष्ठा pdc_pat_cpu_num *cpu_info, अचिन्हित दीर्घ hpa);

बाह्य पूर्णांक pdc_pat_pd_get_addr_map(अचिन्हित दीर्घ *actual_len, व्योम *mem_addr,
		अचिन्हित दीर्घ count, अचिन्हित दीर्घ offset);
बाह्य पूर्णांक pdc_pat_pd_get_pdc_revisions(अचिन्हित दीर्घ *legacy_rev,
		अचिन्हित दीर्घ *pat_rev, अचिन्हित दीर्घ *pdc_cap);

बाह्य पूर्णांक pdc_pat_io_pci_cfg_पढ़ो(अचिन्हित दीर्घ pci_addr, पूर्णांक pci_size, u32 *val); 
बाह्य पूर्णांक pdc_pat_io_pci_cfg_ग_लिखो(अचिन्हित दीर्घ pci_addr, पूर्णांक pci_size, u32 val); 

बाह्य पूर्णांक pdc_pat_mem_pdt_info(काष्ठा pdc_pat_mem_retinfo *rinfo);
बाह्य पूर्णांक pdc_pat_mem_pdt_cell_info(काष्ठा pdc_pat_mem_cell_pdt_retinfo *rinfo,
		अचिन्हित दीर्घ cell);
बाह्य पूर्णांक pdc_pat_mem_पढ़ो_cell_pdt(काष्ठा pdc_pat_mem_पढ़ो_pd_retinfo *pret,
		अचिन्हित दीर्घ *pdt_entries_ptr, अचिन्हित दीर्घ max_entries);
बाह्य पूर्णांक pdc_pat_mem_पढ़ो_pd_pdt(काष्ठा pdc_pat_mem_पढ़ो_pd_retinfo *pret,
		अचिन्हित दीर्घ *pdt_entries_ptr, अचिन्हित दीर्घ count,
		अचिन्हित दीर्घ offset);
बाह्य पूर्णांक pdc_pat_mem_get_dimm_phys_location(
                काष्ठा pdc_pat_mem_phys_mem_location *pret,
                अचिन्हित दीर्घ phys_addr);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* ! __PARISC_PATPDC_H */
