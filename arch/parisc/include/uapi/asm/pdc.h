<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_PARISC_PDC_H
#घोषणा _UAPI_PARISC_PDC_H

/*
 *	PDC वापस values ...
 *	All PDC calls वापस a subset of these errors. 
 */

#घोषणा PDC_WARN		  3	/* Call completed with a warning */
#घोषणा PDC_REQ_ERR_1		  2	/* See above			 */
#घोषणा PDC_REQ_ERR_0		  1	/* Call would generate a requestor error */
#घोषणा PDC_OK			  0	/* Call completed successfully	*/
#घोषणा PDC_BAD_PROC		 -1	/* Called non-existent procedure*/
#घोषणा PDC_BAD_OPTION		 -2	/* Called with non-existent option */
#घोषणा PDC_ERROR		 -3	/* Call could not complete without an error */
#घोषणा PDC_NE_MOD		 -5	/* Module not found		*/
#घोषणा PDC_NE_CELL_MOD		 -7	/* Cell module not found	*/
#घोषणा PDC_NE_BOOTDEV		 -9	/* Cannot locate a console device or boot device */
#घोषणा PDC_INVALID_ARG		-10	/* Called with an invalid argument */
#घोषणा PDC_BUS_POW_WARN	-12	/* Call could not complete in allowed घातer budget */
#घोषणा PDC_NOT_NARROW		-17	/* Narrow mode not supported	*/

/*
 *	PDC entry poपूर्णांकs...
 */

#घोषणा PDC_POW_FAIL	1		/* perक्रमm a घातer-fail		*/
#घोषणा PDC_POW_FAIL_PREPARE	0	/* prepare क्रम घातerfail	*/

#घोषणा PDC_CHASSIS	2		/* PDC-chassis functions	*/
#घोषणा PDC_CHASSIS_DISP	0	/* update chassis display	*/
#घोषणा PDC_CHASSIS_WARN	1	/* वापस chassis warnings	*/
#घोषणा PDC_CHASSIS_DISPWARN	2	/* update&वापस chassis status */
#घोषणा PDC_RETURN_CHASSIS_INFO 128	/* HVERSION dependent: वापस chassis LED/LCD info  */

#घोषणा PDC_PIM         3               /* Get PIM data                 */
#घोषणा PDC_PIM_HPMC            0       /* Transfer HPMC data           */
#घोषणा PDC_PIM_RETURN_SIZE     1       /* Get Max buffer needed क्रम PIM*/
#घोषणा PDC_PIM_LPMC            2       /* Transfer HPMC data           */
#घोषणा PDC_PIM_SOFT_BOOT       3       /* Transfer Soft Boot data      */
#घोषणा PDC_PIM_TOC             4       /* Transfer TOC data            */

#घोषणा PDC_MODEL	4		/* PDC model inक्रमmation call	*/
#घोषणा PDC_MODEL_INFO		0	/* वापसs inक्रमmation 		*/
#घोषणा PDC_MODEL_BOOTID	1	/* set the BOOT_ID		*/
#घोषणा PDC_MODEL_VERSIONS	2	/* वापसs cpu-पूर्णांकernal versions*/
#घोषणा PDC_MODEL_SYSMODEL	3	/* वापस प्रणाली model info	*/
#घोषणा PDC_MODEL_ENSPEC	4	/* enable specअगरic option	*/
#घोषणा PDC_MODEL_DISPEC	5	/* disable specअगरic option	*/
#घोषणा PDC_MODEL_CPU_ID	6	/* वापसs cpu-id (only newer machines!) */
#घोषणा PDC_MODEL_CAPABILITIES	7	/* वापसs OS32/OS64-flags	*/
/* Values क्रम PDC_MODEL_CAPABILITIES non-equivalent भव aliasing support */
#घोषणा  PDC_MODEL_OS64			(1 << 0)
#घोषणा  PDC_MODEL_OS32			(1 << 1)
#घोषणा  PDC_MODEL_IOPसूची_FDC		(1 << 2)
#घोषणा  PDC_MODEL_NVA_MASK		(3 << 4)
#घोषणा  PDC_MODEL_NVA_SUPPORTED	(0 << 4)
#घोषणा  PDC_MODEL_NVA_SLOW		(1 << 4)
#घोषणा  PDC_MODEL_NVA_UNSUPPORTED	(3 << 4)
#घोषणा PDC_MODEL_GET_BOOT__OP	8	/* वापसs boot test options	*/
#घोषणा PDC_MODEL_SET_BOOT__OP	9	/* set boot test options	*/
#घोषणा PDC_MODEL_GET_PLATFORM_INFO 10	/* वापसs platक्रमm info	*/
#घोषणा PDC_MODEL_GET_INSTALL_KERNEL 11	/* वापसs kernel क्रम installation */

#घोषणा PA89_INSTRUCTION_SET	0x4	/* capabilities वापसed	*/
#घोषणा PA90_INSTRUCTION_SET	0x8

#घोषणा PDC_CACHE	5		/* वापस/set cache (& TLB) info*/
#घोषणा PDC_CACHE_INFO		0	/* वापसs inक्रमmation 		*/
#घोषणा PDC_CACHE_SET_COH	1	/* set coherence state		*/
#घोषणा PDC_CACHE_RET_SPID	2	/* वापसs space-ID bits	*/

#घोषणा PDC_HPA		6		/* वापस HPA of processor	*/
#घोषणा PDC_HPA_PROCESSOR	0
#घोषणा PDC_HPA_MODULES		1

#घोषणा PDC_COPROC	7		/* Co-Processor (usually FP unit(s)) */
#घोषणा PDC_COPROC_CFG		0	/* Co-Processor Cfg (FP unit(s) enabled?) */

#घोषणा PDC_IODC	8		/* talk to IODC			*/
#घोषणा PDC_IODC_READ		0	/* पढ़ो IODC entry poपूर्णांक	*/
/*      PDC_IODC_RI_			 * INDEX parameter of PDC_IODC_READ */
#घोषणा PDC_IODC_RI_DATA_BYTES	0	/* IODC Data Bytes		*/
/*				1, 2	   obsolete - HVERSION dependent*/
#घोषणा PDC_IODC_RI_INIT	3	/* Initialize module		*/
#घोषणा PDC_IODC_RI_IO		4	/* Module input/output		*/
#घोषणा PDC_IODC_RI_SPA		5	/* Module input/output		*/
#घोषणा PDC_IODC_RI_CONFIG	6	/* Module input/output		*/
/*				7	  obsolete - HVERSION dependent */
#घोषणा PDC_IODC_RI_TEST	8	/* Module input/output		*/
#घोषणा PDC_IODC_RI_TLB		9	/* Module input/output		*/
#घोषणा PDC_IODC_NINIT		2	/* non-deकाष्ठाive init		*/
#घोषणा PDC_IODC_DINIT		3	/* deकाष्ठाive init		*/
#घोषणा PDC_IODC_MEMERR		4	/* check क्रम memory errors	*/
#घोषणा PDC_IODC_INDEX_DATA	0	/* get first 16 bytes from mod IODC */
#घोषणा PDC_IODC_BUS_ERROR	-4	/* bus error वापस value	*/
#घोषणा PDC_IODC_INVALID_INDEX	-5	/* invalid index वापस value	*/
#घोषणा PDC_IODC_COUNT		-6	/* count is too small		*/

#घोषणा PDC_TOD		9		/* समय-of-day घड़ी (TOD)	*/
#घोषणा PDC_TOD_READ		0	/* पढ़ो TOD			*/
#घोषणा PDC_TOD_WRITE		1	/* ग_लिखो TOD			*/
#घोषणा PDC_TOD_CALIBRATE	2	/* calibrate समयrs		*/

#घोषणा PDC_STABLE	10		/* stable storage (sprockets)	*/
#घोषणा PDC_STABLE_READ		0
#घोषणा PDC_STABLE_WRITE	1
#घोषणा PDC_STABLE_RETURN_SIZE	2
#घोषणा PDC_STABLE_VERIFY_CONTENTS 3
#घोषणा PDC_STABLE_INITIALIZE	4

#घोषणा PDC_NVOLATILE	11		/* often not implemented	*/
#घोषणा PDC_NVOLATILE_READ	0
#घोषणा PDC_NVOLATILE_WRITE	1
#घोषणा PDC_NVOLATILE_RETURN_SIZE 2
#घोषणा PDC_NVOLATILE_VERIFY_CONTENTS 3
#घोषणा PDC_NVOLATILE_INITIALIZE 4

#घोषणा PDC_ADD_VALID	12		/* Memory validation PDC call	*/
#घोषणा PDC_ADD_VALID_VERIFY	0	/* Make PDC_ADD_VALID verअगरy region */

#घोषणा PDC_DEBUG	14		/* Obsolete			*/

#घोषणा PDC_INSTR	15		/* get instr to invoke PDCE_CHECK() */

#घोषणा PDC_PROC	16		/* (sprockets)			*/

#घोषणा PDC_CONFIG	17		/* (sprockets)			*/
#घोषणा PDC_CONFIG_DECONFIG	0
#घोषणा PDC_CONFIG_DRECONFIG	1
#घोषणा PDC_CONFIG_DRETURN_CONFIG 2

#घोषणा PDC_BLOCK_TLB	18		/* manage hardware block-TLB	*/
#घोषणा PDC_BTLB_INFO		0	/* वापसs parameter 		*/
#घोषणा PDC_BTLB_INSERT		1	/* insert BTLB entry		*/
#घोषणा PDC_BTLB_PURGE		2	/* purge BTLB entries 		*/
#घोषणा PDC_BTLB_PURGE_ALL	3	/* purge all BTLB entries 	*/

#घोषणा PDC_TLB		19		/* manage hardware TLB miss handling */
#घोषणा PDC_TLB_INFO		0	/* वापसs parameter 		*/
#घोषणा PDC_TLB_SETUP		1	/* set up miss handling 	*/

#घोषणा PDC_MEM		20		/* Manage memory		*/
#घोषणा PDC_MEM_MEMINFO		0	/* Return PDT info		*/
#घोषणा PDC_MEM_ADD_PAGE	1	/* Add page to PDT		*/
#घोषणा PDC_MEM_CLEAR_PDT	2	/* Clear PDT			*/
#घोषणा PDC_MEM_READ_PDT	3	/* Read PDT entry		*/
#घोषणा PDC_MEM_RESET_CLEAR	4	/* Reset PDT clear flag		*/
#घोषणा PDC_MEM_GOODMEM		5	/* Set good_mem value		*/
#घोषणा PDC_MEM_TABLE		128	/* Non contig mem map (sprockets) */
#घोषणा PDC_MEM_RETURN_ADDRESS_TABLE	PDC_MEM_TABLE
#घोषणा PDC_MEM_GET_MEMORY_SYSTEM_TABLES_SIZE	131
#घोषणा PDC_MEM_GET_MEMORY_SYSTEM_TABLES	132
#घोषणा PDC_MEM_GET_PHYSICAL_LOCATION_FROM_MEMORY_ADDRESS 133

#घोषणा PDC_MEM_RET_SBE_REPLACED	5	/* PDC_MEM वापस values */
#घोषणा PDC_MEM_RET_DUPLICATE_ENTRY	4
#घोषणा PDC_MEM_RET_BUF_SIZE_SMALL	1
#घोषणा PDC_MEM_RET_PDT_FULL		-11
#घोषणा PDC_MEM_RET_INVALID_PHYSICAL_LOCATION ~0ULL

#घोषणा PDC_PSW		21		/* Get/Set शेष System Mask  */
#घोषणा PDC_PSW_MASK		0	/* Return mask                  */
#घोषणा PDC_PSW_GET_DEFAULTS	1	/* Return शेषs              */
#घोषणा PDC_PSW_SET_DEFAULTS	2	/* Set शेष                  */
#घोषणा PDC_PSW_ENDIAN_BIT	1	/* set क्रम big endian           */
#घोषणा PDC_PSW_WIDE_BIT	2	/* set क्रम wide mode            */ 

#घोषणा PDC_SYSTEM_MAP	22		/* find प्रणाली modules		*/
#घोषणा PDC_FIND_MODULE 	0
#घोषणा PDC_FIND_ADDRESS	1
#घोषणा PDC_TRANSLATE_PATH	2

#घोषणा PDC_SOFT_POWER	23		/* soft घातer चयन		*/
#घोषणा PDC_SOFT_POWER_INFO	0	/* वापस info about the soft घातer चयन */
#घोषणा PDC_SOFT_POWER_ENABLE	1	/* enable/disable soft घातer चयन */

#घोषणा PDC_ALLOC	24		/* allocate अटल storage क्रम PDC & IODC */

#घोषणा PDC_CRASH_PREP	25		/* Prepare प्रणाली क्रम crash dump */
#घोषणा PDC_CRASH_DUMP		0	/* Do platक्रमm specअगरic preparations क्रम dump */
#घोषणा PDC_CRASH_LOG_CEC_ERROR 1	/* Dump hardware रेजिस्टरs	*/

#घोषणा PDC_SCSI_PARMS	26		/* Get and set SCSI parameters	*/
#घोषणा PDC_SCSI_GET_PARMS	0	/* Get SCSI parameters क्रम I/O device */
#घोषणा PDC_SCSI_SET_PARMS	1	/* Set SCSI parameters क्रम I/O device */

/* HVERSION dependent */

/* The PDC_MEM_MAP calls */
#घोषणा PDC_MEM_MAP	128		/* on s700: वापस page info	*/
#घोषणा PDC_MEM_MAP_HPA		0	/* वापसs hpa of a module	*/

#घोषणा PDC_EEPROM	129		/* EEPROM access		*/
#घोषणा PDC_EEPROM_READ_WORD	0
#घोषणा PDC_EEPROM_WRITE_WORD	1
#घोषणा PDC_EEPROM_READ_BYTE	2
#घोषणा PDC_EEPROM_WRITE_BYTE	3
#घोषणा PDC_EEPROM_EEPROM_PASSWORD -1000

#घोषणा PDC_NVM		130		/* NVM (non-अस्थिर memory) access */
#घोषणा PDC_NVM_READ_WORD	0
#घोषणा PDC_NVM_WRITE_WORD	1
#घोषणा PDC_NVM_READ_BYTE	2
#घोषणा PDC_NVM_WRITE_BYTE	3

#घोषणा PDC_SEED_ERROR	132		/* (sprockets)			*/

#घोषणा PDC_IO		135		/* log error info, reset IO प्रणाली */
#घोषणा PDC_IO_READ_AND_CLEAR_ERRORS	0
#घोषणा PDC_IO_RESET			1
#घोषणा PDC_IO_RESET_DEVICES		2
/* sets bits 6&7 (little endian) of the HcControl Register */
#घोषणा PDC_IO_USB_SUSPEND	0xC000000000000000
#घोषणा PDC_IO_EEPROM_IO_ERR_TABLE_FULL	-5	/* वापस value */
#घोषणा PDC_IO_NO_SUSPEND		-6	/* वापस value */

#घोषणा PDC_BROADCAST_RESET 136		/* reset all processors		*/
#घोषणा PDC_DO_RESET		0	/* option: perक्रमm a broadcast reset */
#घोषणा PDC_DO_FIRM_TEST_RESET	1	/* Do broadcast reset with biपंचांगap */
#घोषणा PDC_BR_RECONFIGURATION	2	/* reset w/reconfiguration	*/
#घोषणा PDC_FIRM_TEST_MAGIC	0xab9ec36fUL    /* क्रम this reboot only	*/

#घोषणा PDC_LAN_STATION_ID 138		/* Hversion dependent mechanism क्रम */
#घोषणा PDC_LAN_STATION_ID_READ	0	/* getting the lan station address  */

#घोषणा	PDC_LAN_STATION_ID_SIZE	6

#घोषणा PDC_CHECK_RANGES 139		/* (sprockets)			*/

#घोषणा PDC_NV_SECTIONS	141		/* (sprockets)			*/

#घोषणा PDC_PERFORMANCE	142		/* perक्रमmance monitoring	*/

#घोषणा PDC_SYSTEM_INFO	143		/* प्रणाली inक्रमmation		*/
#घोषणा PDC_SYSINFO_RETURN_INFO_SIZE	0
#घोषणा PDC_SYSINFO_RRETURN_SYS_INFO	1
#घोषणा PDC_SYSINFO_RRETURN_ERRORS	2
#घोषणा PDC_SYSINFO_RRETURN_WARNINGS	3
#घोषणा PDC_SYSINFO_RETURN_REVISIONS	4
#घोषणा PDC_SYSINFO_RRETURN_DIAGNOSE	5
#घोषणा PDC_SYSINFO_RRETURN_HV_DIAGNOSE	1005

#घोषणा PDC_RDR		144		/* (sprockets)			*/
#घोषणा PDC_RDR_READ_BUFFER	0
#घोषणा PDC_RDR_READ_SINGLE	1
#घोषणा PDC_RDR_WRITE_SINGLE	2

#घोषणा PDC_INTRIGUE	145 		/* (sprockets)			*/
#घोषणा PDC_INTRIGUE_WRITE_BUFFER 	 0
#घोषणा PDC_INTRIGUE_GET_SCRATCH_बफ_मानE 1
#घोषणा PDC_INTRIGUE_START_CPU_COUNTERS	 2
#घोषणा PDC_INTRIGUE_STOP_CPU_COUNTERS	 3

#घोषणा PDC_STI		146 		/* STI access			*/
/* same as PDC_PCI_XXX values (see below) */

/* Legacy PDC definitions क्रम same stuff */
#घोषणा PDC_PCI_INDEX	147
#घोषणा PDC_PCI_INTERFACE_INFO		0
#घोषणा PDC_PCI_SLOT_INFO		1
#घोषणा PDC_PCI_INFLIGHT_BYTES		2
#घोषणा PDC_PCI_READ_CONFIG		3
#घोषणा PDC_PCI_WRITE_CONFIG		4
#घोषणा PDC_PCI_READ_PCI_IO		5
#घोषणा PDC_PCI_WRITE_PCI_IO		6
#घोषणा PDC_PCI_READ_CONFIG_DELAY	7
#घोषणा PDC_PCI_UPDATE_CONFIG_DELAY	8
#घोषणा PDC_PCI_PCI_PATH_TO_PCI_HPA	9
#घोषणा PDC_PCI_PCI_HPA_TO_PCI_PATH	10
#घोषणा PDC_PCI_PCI_PATH_TO_PCI_BUS	11
#घोषणा PDC_PCI_PCI_RESERVED		12
#घोषणा PDC_PCI_PCI_INT_ROUTE_SIZE	13
#घोषणा PDC_PCI_GET_INT_TBL_SIZE	PDC_PCI_PCI_INT_ROUTE_SIZE
#घोषणा PDC_PCI_PCI_INT_ROUTE		14
#घोषणा PDC_PCI_GET_INT_TBL		PDC_PCI_PCI_INT_ROUTE 
#घोषणा PDC_PCI_READ_MON_TYPE		15
#घोषणा PDC_PCI_WRITE_MON_TYPE		16

#घोषणा PDC_RELOCATE	149		/* (sprockets)			*/
#घोषणा PDC_RELOCATE_GET_RELOCINFO	0
#घोषणा PDC_RELOCATE_CHECKSUM		1
#घोषणा PDC_RELOCATE_RELOCATE		2

/* Get SCSI Interface Card info:  SDTR, SCSI ID, mode (SE vs LVD) */
#घोषणा PDC_INITIATOR	163
#घोषणा PDC_GET_INITIATOR	0
#घोषणा PDC_SET_INITIATOR	1
#घोषणा PDC_DELETE_INITIATOR	2
#घोषणा PDC_RETURN_TABLE_SIZE	3
#घोषणा PDC_RETURN_TABLE	4

#घोषणा PDC_LINK	165 		/* (sprockets)			*/
#घोषणा PDC_LINK_PCI_ENTRY_POINTS	0  /* list (Arg1) = 0 */
#घोषणा PDC_LINK_USB_ENTRY_POINTS	1  /* list (Arg1) = 1 */

/* cl_class
 * page 3-33 of IO-Firmware ARS
 * IODC ENTRY_INIT(Search first) RET[1]
 */
#घोषणा	CL_शून्य		0	/* invalid */
#घोषणा	CL_RANDOM	1	/* अक्रमom access (as disk) */
#घोषणा	CL_SEQU		2	/* sequential access (as tape) */
#घोषणा	CL_DUPLEX	7	/* full-duplex poपूर्णांक-to-poपूर्णांक (RS-232, Net) */
#घोषणा	CL_KEYBD	8	/* half-duplex console (HIL Keyboard) */
#घोषणा	CL_DISPL	9	/* half-duplex console (display) */
#घोषणा	CL_FC		10	/* FiberChannel access media */

/* IODC ENTRY_INIT() */
#घोषणा ENTRY_INIT_SRCH_FRST	2
#घोषणा ENTRY_INIT_SRCH_NEXT	3
#घोषणा ENTRY_INIT_MOD_DEV	4
#घोषणा ENTRY_INIT_DEV		5
#घोषणा ENTRY_INIT_MOD		6
#घोषणा ENTRY_INIT_MSG		9

/* IODC ENTRY_IO() */
#घोषणा ENTRY_IO_BOOTIN		0
#घोषणा ENTRY_IO_BOOTOUT	1
#घोषणा ENTRY_IO_CIN		2
#घोषणा ENTRY_IO_COUT		3
#घोषणा ENTRY_IO_CLOSE		4
#घोषणा ENTRY_IO_GETMSG		9
#घोषणा ENTRY_IO_BBLOCK_IN	16
#घोषणा ENTRY_IO_BBLOCK_OUT	17

/* IODC ENTRY_SPA() */

/* IODC ENTRY_CONFIG() */

/* IODC ENTRY_TEST() */

/* IODC ENTRY_TLB() */

/* स्थिरants क्रम OS (NVM...) */
#घोषणा OS_ID_NONE		0	/* Undefined OS ID	*/
#घोषणा OS_ID_HPUX		1	/* HP-UX OS		*/
#घोषणा OS_ID_MPEXL		2	/* MPE XL OS		*/
#घोषणा OS_ID_OSF		3	/* OSF OS		*/
#घोषणा OS_ID_HPRT		4	/* HP-RT OS		*/
#घोषणा OS_ID_NOVEL		5	/* NOVELL OS		*/
#घोषणा OS_ID_LINUX		6	/* Linux		*/


/* स्थिरants क्रम PDC_CHASSIS */
#घोषणा OSTAT_OFF		0
#घोषणा OSTAT_FLT		1 
#घोषणा OSTAT_TEST		2
#घोषणा OSTAT_INIT		3
#घोषणा OSTAT_SHUT		4
#घोषणा OSTAT_WARN		5
#घोषणा OSTAT_RUN		6
#घोषणा OSTAT_ON		7

/* Page Zero स्थिरant offsets used by the HPMC handler */
#घोषणा BOOT_CONSOLE_HPA_OFFSET  0x3c0
#घोषणा BOOT_CONSOLE_SPA_OFFSET  0x3c4
#घोषणा BOOT_CONSOLE_PATH_OFFSET 0x3a8

/* size of the pdc_result buffer क्रम firmware.c */
#घोषणा NUM_PDC_RESULT	32

#अगर !defined(__ASSEMBLY__)

/* flags of the device_path */
#घोषणा	PF_AUTOBOOT	0x80
#घोषणा	PF_AUTOSEARCH	0x40
#घोषणा	PF_TIMER	0x0F

काष्ठा device_path अणु		/* page 1-69 */
	अचिन्हित अक्षर flags;	/* flags see above! */
	अचिन्हित अक्षर bc[6];	/* bus converter routing info */
	अचिन्हित अक्षर mod;
	अचिन्हित पूर्णांक  layers[6];/* device-specअगरic layer-info */
पूर्ण __attribute__((aligned(8))) ;

काष्ठा pz_device अणु
	काष्ठा	device_path dp;	/* see above */
	/* काष्ठा	iomod *hpa; */
	अचिन्हित पूर्णांक hpa;	/* HPA base address */
	/* अक्षर	*spa; */
	अचिन्हित पूर्णांक spa;	/* SPA base address */
	/* पूर्णांक	(*iodc_io)(काष्ठा iomod*, ...); */
	अचिन्हित पूर्णांक iodc_io;	/* device entry poपूर्णांक */
	लघु	pad;		/* reserved */
	अचिन्हित लघु cl_class;/* see below */
पूर्ण __attribute__((aligned(8))) ;

काष्ठा zeropage अणु
	/* [0x000] initialize vectors (VEC) */
	अचिन्हित पूर्णांक	vec_special;		/* must be zero */
	/* पूर्णांक	(*vec_घात_fail)(व्योम);*/
	अचिन्हित पूर्णांक	vec_घात_fail; /* घातer failure handler */
	/* पूर्णांक	(*vec_toc)(व्योम); */
	अचिन्हित पूर्णांक	vec_toc;
	अचिन्हित पूर्णांक	vec_toclen;
	/* पूर्णांक	(*vec_rendz)(व्योम); */
	अचिन्हित पूर्णांक vec_rendz;
	पूर्णांक	vec_घात_fail_flen;
	पूर्णांक	vec_pad[10];		
	
	/* [0x040] reserved processor dependent */
	पूर्णांक	pad0[112];

	/* [0x200] reserved */
	पूर्णांक	pad1[84];

	/* [0x350] memory configuration (MC) */
	पूर्णांक	memc_cont;		/* contiguous mem size (bytes) */
	पूर्णांक	memc_phsize;		/* physical memory size */
	पूर्णांक	memc_adsize;		/* additional mem size, bytes of SPA space used by PDC */
	अचिन्हित पूर्णांक mem_pdc_hi;	/* used क्रम 64-bit */

	/* [0x360] various parameters क्रम the boot-CPU */
	/* अचिन्हित पूर्णांक *mem_booterr[8]; */
	अचिन्हित पूर्णांक mem_booterr[8];	/* ptr to boot errors */
	अचिन्हित पूर्णांक mem_मुक्त;		/* first location, where OS can be loaded */
	/* काष्ठा iomod *mem_hpa; */
	अचिन्हित पूर्णांक mem_hpa;		/* HPA of the boot-CPU */
	/* पूर्णांक (*mem_pdc)(पूर्णांक, ...); */
	अचिन्हित पूर्णांक mem_pdc;		/* PDC entry poपूर्णांक */
	अचिन्हित पूर्णांक mem_10msec;	/* number of घड़ी ticks in 10msec */

	/* [0x390] initial memory module (IMM) */
	/* काष्ठा iomod *imm_hpa; */
	अचिन्हित पूर्णांक imm_hpa;		/* HPA of the IMM */
	पूर्णांक	imm_soft_boot;		/* 0 = was hard boot, 1 = was soft boot */
	अचिन्हित पूर्णांक	imm_spa_size;		/* SPA size of the IMM in bytes */
	अचिन्हित पूर्णांक	imm_max_mem;		/* bytes of mem in IMM */

	/* [0x3A0] boot console, display device and keyboard */
	काष्ठा pz_device mem_cons;	/* description of console device */
	काष्ठा pz_device mem_boot;	/* description of boot device */
	काष्ठा pz_device mem_kbd;	/* description of keyboard device */

	/* [0x430] reserved */
	पूर्णांक	pad430[116];

	/* [0x600] processor dependent */
	अचिन्हित पूर्णांक pad600[1];
	अचिन्हित पूर्णांक proc_sti;		/* poपूर्णांकer to STI ROM */
	अचिन्हित पूर्णांक pad608[126];
पूर्ण;

काष्ठा pdc_chassis_info अणु       /* क्रम PDC_CHASSIS_INFO */
	अचिन्हित दीर्घ actcnt;   /* actual number of bytes वापसed */
	अचिन्हित दीर्घ maxcnt;   /* maximum number of bytes that could be वापसed */
पूर्ण;

काष्ठा pdc_coproc_cfg अणु         /* क्रम PDC_COPROC_CFG */
        अचिन्हित दीर्घ ccr_functional;
        अचिन्हित दीर्घ ccr_present;
        अचिन्हित दीर्घ revision;
        अचिन्हित दीर्घ model;
पूर्ण;

काष्ठा pdc_model अणु		/* क्रम PDC_MODEL */
	अचिन्हित दीर्घ hversion;
	अचिन्हित दीर्घ sversion;
	अचिन्हित दीर्घ hw_id;
	अचिन्हित दीर्घ boot_id;
	अचिन्हित दीर्घ sw_id;
	अचिन्हित दीर्घ sw_cap;
	अचिन्हित दीर्घ arch_rev;
	अचिन्हित दीर्घ pot_key;
	अचिन्हित दीर्घ curr_key;
पूर्ण;

काष्ठा pdc_cache_cf अणु		/* क्रम PDC_CACHE  (I/D-caches) */
    अचिन्हित दीर्घ
#अगर_घोषित __LP64__
		cc_padW:32,
#पूर्ण_अगर
		cc_alias: 4,	/* alias boundaries क्रम भव addresses   */
		cc_block: 4,	/* to determine most efficient stride */
		cc_line	: 3,	/* maximum amount written back as a result of store (multiple of 16 bytes) */
		cc_shअगरt: 2,	/* how much to shअगरt cc_block left */
		cc_wt	: 1,	/* 0 = WT-Dcache, 1 = WB-Dcache */
		cc_sh	: 2,	/* 0 = separate I/D-cache, अन्यथा shared I/D-cache */
		cc_cst  : 3,	/* 0 = incoherent D-cache, 1=coherent D-cache */
		cc_pad1 : 10,	/* reserved */
		cc_hv   : 3;	/* hversion dependent */
पूर्ण;

काष्ठा pdc_tlb_cf अणु		/* क्रम PDC_CACHE (I/D-TLB's) */
    अचिन्हित दीर्घ tc_pad0:12,	/* reserved */
#अगर_घोषित __LP64__
		tc_padW:32,
#पूर्ण_अगर
		tc_sh	: 2,	/* 0 = separate I/D-TLB, अन्यथा shared I/D-TLB */
		tc_hv   : 1,	/* HV */
		tc_page : 1,	/* 0 = 2K page-size-machine, 1 = 4k page size */
		tc_cst  : 3,	/* 0 = incoherent operations, अन्यथा coherent operations */
		tc_aid  : 5,	/* ITLB: width of access ids of processor (encoded!) */
		tc_sr   : 8;	/* ITLB: width of space-रेजिस्टरs (encoded) */
पूर्ण;

काष्ठा pdc_cache_info अणु		/* मुख्य-PDC_CACHE-काष्ठाure (caches & TLB's) */
	/* I-cache */
	अचिन्हित दीर्घ	ic_size;	/* size in bytes */
	काष्ठा pdc_cache_cf ic_conf;	/* configuration */
	अचिन्हित दीर्घ	ic_base;	/* base-addr */
	अचिन्हित दीर्घ	ic_stride;
	अचिन्हित दीर्घ	ic_count;
	अचिन्हित दीर्घ	ic_loop;
	/* D-cache */
	अचिन्हित दीर्घ	dc_size;	/* size in bytes */
	काष्ठा pdc_cache_cf dc_conf;	/* configuration */
	अचिन्हित दीर्घ	dc_base;	/* base-addr */
	अचिन्हित दीर्घ	dc_stride;
	अचिन्हित दीर्घ	dc_count;
	अचिन्हित दीर्घ	dc_loop;
	/* Inकाष्ठाion-TLB */
	अचिन्हित दीर्घ	it_size;	/* number of entries in I-TLB */
	काष्ठा pdc_tlb_cf it_conf;	/* I-TLB-configuration */
	अचिन्हित दीर्घ	it_sp_base;
	अचिन्हित दीर्घ	it_sp_stride;
	अचिन्हित दीर्घ	it_sp_count;
	अचिन्हित दीर्घ	it_off_base;
	अचिन्हित दीर्घ	it_off_stride;
	अचिन्हित दीर्घ	it_off_count;
	अचिन्हित दीर्घ	it_loop;
	/* data-TLB */
	अचिन्हित दीर्घ	dt_size;	/* number of entries in D-TLB */
	काष्ठा pdc_tlb_cf dt_conf;	/* D-TLB-configuration */
	अचिन्हित दीर्घ	dt_sp_base;
	अचिन्हित दीर्घ	dt_sp_stride;
	अचिन्हित दीर्घ	dt_sp_count;
	अचिन्हित दीर्घ	dt_off_base;
	अचिन्हित दीर्घ	dt_off_stride;
	अचिन्हित दीर्घ	dt_off_count;
	अचिन्हित दीर्घ	dt_loop;
पूर्ण;

/* Might need adjusपंचांगent to work with 64-bit firmware */
काष्ठा pdc_iodc अणु     /* PDC_IODC */
	अचिन्हित अक्षर   hversion_model;
	अचिन्हित अक्षर 	hversion;
	अचिन्हित अक्षर 	spa;
	अचिन्हित अक्षर 	type;
	अचिन्हित पूर्णांक	sversion_rev:4;
	अचिन्हित पूर्णांक	sversion_model:19;
	अचिन्हित पूर्णांक	sversion_opt:8;
	अचिन्हित अक्षर	rev;
	अचिन्हित अक्षर	dep;
	अचिन्हित अक्षर	features;
	अचिन्हित अक्षर	pad1;
	अचिन्हित पूर्णांक	checksum:16;
	अचिन्हित पूर्णांक	length:16;
	अचिन्हित पूर्णांक    pad[15];
पूर्ण __attribute__((aligned(8))) ;

/* no BLTBs in pa2.0 processors */
काष्ठा pdc_btlb_info_range अणु
	अचिन्हित अक्षर res00;
	अचिन्हित अक्षर num_i;
	अचिन्हित अक्षर num_d;
	अचिन्हित अक्षर num_comb;
पूर्ण;

काष्ठा pdc_btlb_info अणु	/* PDC_BLOCK_TLB, वापस of PDC_BTLB_INFO */
	अचिन्हित पूर्णांक min_size;	/* minimum size of BTLB in pages */
	अचिन्हित पूर्णांक max_size;	/* maximum size of BTLB in pages */
	काष्ठा pdc_btlb_info_range fixed_range_info;
	काष्ठा pdc_btlb_info_range variable_range_info;
पूर्ण;

काष्ठा pdc_mem_retinfo अणु /* PDC_MEM/PDC_MEM_MEMINFO (वापस info) */
	अचिन्हित दीर्घ pdt_size;
	अचिन्हित दीर्घ pdt_entries;
	अचिन्हित दीर्घ pdt_status;
	अचिन्हित दीर्घ first_dbe_loc;
	अचिन्हित दीर्घ good_mem;
पूर्ण;

काष्ठा pdc_mem_पढ़ो_pdt अणु /* PDC_MEM/PDC_MEM_READ_PDT (वापस info) */
	अचिन्हित दीर्घ pdt_entries;
पूर्ण;

#अगर_घोषित __LP64__
काष्ठा pdc_memory_table_raddr अणु /* PDC_MEM/PDC_MEM_TABLE (वापस info) */
	अचिन्हित दीर्घ entries_वापसed;
	अचिन्हित दीर्घ entries_total;
पूर्ण;

काष्ठा pdc_memory_table अणु       /* PDC_MEM/PDC_MEM_TABLE (arguments) */
	अचिन्हित दीर्घ paddr;
	अचिन्हित पूर्णांक  pages;
	अचिन्हित पूर्णांक  reserved;
पूर्ण;
#पूर्ण_अगर /* __LP64__ */

काष्ठा pdc_प्रणाली_map_mod_info अणु /* PDC_SYSTEM_MAP/FIND_MODULE */
	अचिन्हित दीर्घ mod_addr;
	अचिन्हित दीर्घ mod_pgs;
	अचिन्हित दीर्घ add_addrs;
पूर्ण;

काष्ठा pdc_प्रणाली_map_addr_info अणु /* PDC_SYSTEM_MAP/FIND_ADDRESS */
	अचिन्हित दीर्घ mod_addr;
	अचिन्हित दीर्घ mod_pgs;
पूर्ण;

काष्ठा pdc_initiator अणु /* PDC_INITIATOR */
	पूर्णांक host_id;
	पूर्णांक factor;
	पूर्णांक width;
	पूर्णांक mode;
पूर्ण;

काष्ठा hardware_path अणु
	अक्षर  flags;	/* see bit definitions below */
	अक्षर  bc[6];	/* Bus Converter routing info to a specअगरic */
			/* I/O adaptor (< 0 means none, > 63 resvd) */
	अक्षर  mod;	/* fixed field of specअगरied module */
पूर्ण;

/*
 * Device path specअगरications used by PDC.
 */
काष्ठा pdc_module_path अणु
	काष्ठा hardware_path path;
	अचिन्हित पूर्णांक layers[6]; /* device-specअगरic info (ctlr #, unit # ...) */
पूर्ण;

/* Only used on some pre-PA2.0 boxes */
काष्ठा pdc_memory_map अणु		/* PDC_MEMORY_MAP */
	अचिन्हित दीर्घ hpa;	/* mod's रेजिस्टर set address */
	अचिन्हित दीर्घ more_pgs;	/* number of additional I/O pgs */
पूर्ण;

काष्ठा pdc_tod अणु
	अचिन्हित दीर्घ tod_sec;
	अचिन्हित दीर्घ tod_usec;
पूर्ण;

/* architected results from PDC_PIM/transfer hpmc on a PA1.1 machine */

काष्ठा pdc_hpmc_pim_11 अणु /* PDC_PIM */
	अचिन्हित पूर्णांक gr[32];
	अचिन्हित पूर्णांक cr[32];
	अचिन्हित पूर्णांक sr[8];
	अचिन्हित पूर्णांक iasq_back;
	अचिन्हित पूर्णांक iaoq_back;
	अचिन्हित पूर्णांक check_type;
	अचिन्हित पूर्णांक cpu_state;
	अचिन्हित पूर्णांक rsvd1;
	अचिन्हित पूर्णांक cache_check;
	अचिन्हित पूर्णांक tlb_check;
	अचिन्हित पूर्णांक bus_check;
	अचिन्हित पूर्णांक assists_check;
	अचिन्हित पूर्णांक rsvd2;
	अचिन्हित पूर्णांक assist_state;
	अचिन्हित पूर्णांक responder_addr;
	अचिन्हित पूर्णांक requestor_addr;
	अचिन्हित पूर्णांक path_info;
	अचिन्हित दीर्घ दीर्घ fr[32];
पूर्ण;

/*
 * architected results from PDC_PIM/transfer hpmc on a PA2.0 machine
 *
 * Note that PDC_PIM करोesn't care whether or not wide mode was enabled
 * so the results are dअगरferent on  PA1.1 vs. PA2.0 when in narrow mode.
 *
 * Note also that there are unarchitected results available, which
 * are hversion dependent. Do a "ser pim 0 hpmc" after rebooting, since
 * the firmware is probably the best way of prपूर्णांकing hversion dependent
 * data.
 */

काष्ठा pdc_hpmc_pim_20 अणु /* PDC_PIM */
	अचिन्हित दीर्घ दीर्घ gr[32];
	अचिन्हित दीर्घ दीर्घ cr[32];
	अचिन्हित दीर्घ दीर्घ sr[8];
	अचिन्हित दीर्घ दीर्घ iasq_back;
	अचिन्हित दीर्घ दीर्घ iaoq_back;
	अचिन्हित पूर्णांक check_type;
	अचिन्हित पूर्णांक cpu_state;
	अचिन्हित पूर्णांक cache_check;
	अचिन्हित पूर्णांक tlb_check;
	अचिन्हित पूर्णांक bus_check;
	अचिन्हित पूर्णांक assists_check;
	अचिन्हित पूर्णांक assist_state;
	अचिन्हित पूर्णांक path_info;
	अचिन्हित दीर्घ दीर्घ responder_addr;
	अचिन्हित दीर्घ दीर्घ requestor_addr;
	अचिन्हित दीर्घ दीर्घ fr[32];
पूर्ण;

#पूर्ण_अगर /* !defined(__ASSEMBLY__) */

#पूर्ण_अगर /* _UAPI_PARISC_PDC_H */
