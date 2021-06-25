<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
#अगर_अघोषित __IBMPHP_H
#घोषणा __IBMPHP_H

/*
 * IBM Hot Plug Controller Driver
 *
 * Written By: Jyoti Shah, Tong Yu, Irene Zubarev, IBM Corporation
 *
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 * Copyright (C) 2001-2003 IBM Corp.
 *
 * All rights reserved.
 *
 * Send feedback to <gregkh@us.ibm.com>
 *
 */

#समावेश <linux/pci_hotplug.h>

बाह्य पूर्णांक ibmphp_debug;

#अगर !defined(MODULE)
	#घोषणा MY_NAME "ibmphpd"
#अन्यथा
	#घोषणा MY_NAME THIS_MODULE->name
#पूर्ण_अगर
#घोषणा debug(fmt, arg...) करो अणु अगर (ibmphp_debug == 1) prपूर्णांकk(KERN_DEBUG "%s: " fmt, MY_NAME, ## arg); पूर्ण जबतक (0)
#घोषणा debug_pci(fmt, arg...) करो अणु अगर (ibmphp_debug) prपूर्णांकk(KERN_DEBUG "%s: " fmt, MY_NAME, ## arg); पूर्ण जबतक (0)
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा info(क्रमmat, arg...) prपूर्णांकk(KERN_INFO "%s: " क्रमmat, MY_NAME, ## arg)
#घोषणा warn(क्रमmat, arg...) prपूर्णांकk(KERN_WARNING "%s: " क्रमmat, MY_NAME, ## arg)


/* EBDA stuff */

/***********************************************************
* SLOT CAPABILITY                                          *
***********************************************************/

#घोषणा EBDA_SLOT_133_MAX		0x20
#घोषणा EBDA_SLOT_100_MAX		0x10
#घोषणा EBDA_SLOT_66_MAX		0x02
#घोषणा EBDA_SLOT_PCIX_CAP		0x08


/************************************************************
*  RESOURCE TYPE                                             *
************************************************************/

#घोषणा EBDA_RSRC_TYPE_MASK		0x03
#घोषणा EBDA_IO_RSRC_TYPE		0x00
#घोषणा EBDA_MEM_RSRC_TYPE		0x01
#घोषणा EBDA_PFM_RSRC_TYPE		0x03
#घोषणा EBDA_RES_RSRC_TYPE		0x02


/*************************************************************
*  IO RESTRICTION TYPE                                       *
*************************************************************/

#घोषणा EBDA_IO_RESTRI_MASK		0x0c
#घोषणा EBDA_NO_RESTRI			0x00
#घोषणा EBDA_AVO_VGA_ADDR		0x04
#घोषणा EBDA_AVO_VGA_ADDR_AND_ALIA	0x08
#घोषणा EBDA_AVO_ISA_ADDR		0x0c


/**************************************************************
*  DEVICE TYPE DEF                                            *
**************************************************************/

#घोषणा EBDA_DEV_TYPE_MASK		0x10
#घोषणा EBDA_PCI_DEV			0x10
#घोषणा EBDA_NON_PCI_DEV		0x00


/***************************************************************
*  PRIMARY DEF DEFINITION                                      *
***************************************************************/

#घोषणा EBDA_PRI_DEF_MASK		0x20
#घोषणा EBDA_PRI_PCI_BUS_INFO		0x20
#घोषणा EBDA_NORM_DEV_RSRC_INFO		0x00


//--------------------------------------------------------------
// RIO TABLE DATA STRUCTURE
//--------------------------------------------------------------

काष्ठा rio_table_hdr अणु
	u8 ver_num;
	u8 scal_count;
	u8 riodev_count;
	u16 offset;
पूर्ण;

//-------------------------------------------------------------
// SCALABILITY DETAIL
//-------------------------------------------------------------

काष्ठा scal_detail अणु
	u8 node_id;
	u32 cbar;
	u8 port0_node_connect;
	u8 port0_port_connect;
	u8 port1_node_connect;
	u8 port1_port_connect;
	u8 port2_node_connect;
	u8 port2_port_connect;
	u8 chassis_num;
//	काष्ठा list_head scal_detail_list;
पूर्ण;

//--------------------------------------------------------------
// RIO DETAIL
//--------------------------------------------------------------

काष्ठा rio_detail अणु
	u8 rio_node_id;
	u32 bbar;
	u8 rio_type;
	u8 owner_id;
	u8 port0_node_connect;
	u8 port0_port_connect;
	u8 port1_node_connect;
	u8 port1_port_connect;
	u8 first_slot_num;
	u8 status;
	u8 wpindex;
	u8 chassis_num;
	काष्ठा list_head rio_detail_list;
पूर्ण;

काष्ठा opt_rio अणु
	u8 rio_type;
	u8 chassis_num;
	u8 first_slot_num;
	u8 middle_num;
	काष्ठा list_head opt_rio_list;
पूर्ण;

काष्ठा opt_rio_lo अणु
	u8 rio_type;
	u8 chassis_num;
	u8 first_slot_num;
	u8 middle_num;
	u8 pack_count;
	काष्ठा list_head opt_rio_lo_list;
पूर्ण;

/****************************************************************
*  HPC DESCRIPTOR NODE                                          *
****************************************************************/

काष्ठा ebda_hpc_list अणु
	u8 क्रमmat;
	u16 num_ctlrs;
	लघु phys_addr;
//      काष्ठा list_head ebda_hpc_list;
पूर्ण;
/*****************************************************************
*   IN HPC DATA STRUCTURE, THE ASSOCIATED SLOT AND BUS           *
*   STRUCTURE                                                    *
*****************************************************************/

काष्ठा ebda_hpc_slot अणु
	u8 slot_num;
	u32 slot_bus_num;
	u8 ctl_index;
	u8 slot_cap;
पूर्ण;

काष्ठा ebda_hpc_bus अणु
	u32 bus_num;
	u8 slots_at_33_conv;
	u8 slots_at_66_conv;
	u8 slots_at_66_pcix;
	u8 slots_at_100_pcix;
	u8 slots_at_133_pcix;
पूर्ण;


/********************************************************************
*   THREE TYPE OF HOT PLUG CONTROLLER                                *
********************************************************************/

काष्ठा isa_ctlr_access अणु
	u16 io_start;
	u16 io_end;
पूर्ण;

काष्ठा pci_ctlr_access अणु
	u8 bus;
	u8 dev_fun;
पूर्ण;

काष्ठा wpeg_i2c_ctlr_access अणु
	uदीर्घ wpegbbar;
	u8 i2c_addr;
पूर्ण;

#घोषणा HPC_DEVICE_ID		0x0246
#घोषणा HPC_SUBSYSTEM_ID	0x0247
#घोषणा HPC_PCI_OFFSET		0x40
/*************************************************************************
*   RSTC DESCRIPTOR NODE                                                 *
*************************************************************************/

काष्ठा ebda_rsrc_list अणु
	u8 क्रमmat;
	u16 num_entries;
	u16 phys_addr;
	काष्ठा ebda_rsrc_list *next;
पूर्ण;


/***************************************************************************
*   PCI RSRC NODE                                                          *
***************************************************************************/

काष्ठा ebda_pci_rsrc अणु
	u8 rsrc_type;
	u8 bus_num;
	u8 dev_fun;
	u32 start_addr;
	u32 end_addr;
	u8 marked;	/* क्रम NVRAM */
	काष्ठा list_head ebda_pci_rsrc_list;
पूर्ण;


/***********************************************************
* BUS_INFO DATE STRUCTURE                                  *
***********************************************************/

काष्ठा bus_info अणु
	u8 slot_min;
	u8 slot_max;
	u8 slot_count;
	u8 busno;
	u8 controller_id;
	u8 current_speed;
	u8 current_bus_mode;
	u8 index;
	u8 slots_at_33_conv;
	u8 slots_at_66_conv;
	u8 slots_at_66_pcix;
	u8 slots_at_100_pcix;
	u8 slots_at_133_pcix;
	काष्ठा list_head bus_info_list;
पूर्ण;


/***********************************************************
* GLOBAL VARIABLES                                         *
***********************************************************/
बाह्य काष्ठा list_head ibmphp_ebda_pci_rsrc_head;
बाह्य काष्ठा list_head ibmphp_slot_head;
/***********************************************************
* FUNCTION PROTOTYPES                                      *
***********************************************************/

व्योम ibmphp_मुक्त_ebda_hpc_queue(व्योम);
पूर्णांक ibmphp_access_ebda(व्योम);
काष्ठा slot *ibmphp_get_slot_from_physical_num(u8);
पूर्णांक ibmphp_get_total_hp_slots(व्योम);
व्योम ibmphp_मुक्त_ibm_slot(काष्ठा slot *);
व्योम ibmphp_मुक्त_bus_info_queue(व्योम);
व्योम ibmphp_मुक्त_ebda_pci_rsrc_queue(व्योम);
काष्ठा bus_info *ibmphp_find_same_bus_num(u32);
पूर्णांक ibmphp_get_bus_index(u8);
u16 ibmphp_get_total_controllers(व्योम);
पूर्णांक ibmphp_रेजिस्टर_pci(व्योम);

/* passed parameters */
#घोषणा MEM		0
#घोषणा IO		1
#घोषणा PFMEM		2

/* bit masks */
#घोषणा RESTYPE		0x03
#घोषणा IOMASK		0x00	/* will need to take its complement */
#घोषणा MMASK		0x01
#घोषणा PFMASK		0x03
#घोषणा PCIDEVMASK	0x10	/* we should always have PCI devices */
#घोषणा PRIMARYBUSMASK	0x20

/* pci specअगरic defines */
#घोषणा PCI_VENDOR_ID_NOTVALID		0xFFFF
#घोषणा PCI_HEADER_TYPE_MULTIDEVICE	0x80
#घोषणा PCI_HEADER_TYPE_MULTIBRIDGE	0x81

#घोषणा LATENCY		0x64
#घोषणा CACHE		64
#घोषणा DEVICEENABLE	0x015F		/* CPQ has 0x0157 */

#घोषणा IOBRIDGE	0x1000		/* 4k */
#घोषणा MEMBRIDGE	0x100000	/* 1M */

/* irqs */
#घोषणा SCSI_IRQ	0x09
#घोषणा LAN_IRQ		0x0A
#घोषणा OTHER_IRQ	0x0B

/* Data Structures */

/* type is of the क्रमm x x xx xx
 *                     | |  |  |_ 00 - I/O, 01 - Memory, 11 - PFMemory
 *                     | |  - 00 - No Restrictions, 01 - Aव्योम VGA, 10 - Aव्योम
 *                     | |    VGA and their aliases, 11 - Aव्योम ISA
 *                     | - 1 - PCI device, 0 - non pci device
 *                     - 1 - Primary PCI Bus Inक्रमmation (0 अगर Normal device)
 * the IO restrictions [2:3] are only क्रम primary buses
 */


/* we need this काष्ठा because there could be several resource blocks
 * allocated per primary bus in the EBDA
 */
काष्ठा range_node अणु
	पूर्णांक rangeno;
	u32 start;
	u32 end;
	काष्ठा range_node *next;
पूर्ण;

काष्ठा bus_node अणु
	u8 busno;
	पूर्णांक noIORanges;
	काष्ठा range_node *rangeIO;
	पूर्णांक noMemRanges;
	काष्ठा range_node *rangeMem;
	पूर्णांक noPFMemRanges;
	काष्ठा range_node *rangePFMem;
	पूर्णांक needIOUpdate;
	पूर्णांक needMemUpdate;
	पूर्णांक needPFMemUpdate;
	काष्ठा resource_node *firstIO;	/* first IO resource on the Bus */
	काष्ठा resource_node *firstMem;	/* first memory resource on the Bus */
	काष्ठा resource_node *firstPFMem;	/* first prefetchable memory resource on the Bus */
	काष्ठा resource_node *firstPFMemFromMem;	/* when run out of pfmem available, taking from Mem */
	काष्ठा list_head bus_list;
पूर्ण;

काष्ठा resource_node अणु
	पूर्णांक rangeno;
	u8 busno;
	u8 devfunc;
	u32 start;
	u32 end;
	u32 len;
	पूर्णांक type;		/* MEM, IO, PFMEM */
	u8 fromMem;		/* this is to indicate that the range is from
				 * from the Memory bucket rather than from PFMem */
	काष्ठा resource_node *next;
	काष्ठा resource_node *nextRange;	/* क्रम the other mem range on bus */
पूर्ण;

काष्ठा res_needed अणु
	u32 mem;
	u32 pfmem;
	u32 io;
	u8 not_correct;		/* needed क्रम वापस */
	पूर्णांक devices[32];	/* क्रम device numbers behind this bridge */
पूर्ण;

/* functions */

पूर्णांक ibmphp_rsrc_init(व्योम);
पूर्णांक ibmphp_add_resource(काष्ठा resource_node *);
पूर्णांक ibmphp_हटाओ_resource(काष्ठा resource_node *);
पूर्णांक ibmphp_find_resource(काष्ठा bus_node *, u32, काष्ठा resource_node **, पूर्णांक);
पूर्णांक ibmphp_check_resource(काष्ठा resource_node *, u8);
पूर्णांक ibmphp_हटाओ_bus(काष्ठा bus_node *, u8);
व्योम ibmphp_मुक्त_resources(व्योम);
पूर्णांक ibmphp_add_pfmem_from_mem(काष्ठा resource_node *);
काष्ठा bus_node *ibmphp_find_res_bus(u8);
व्योम ibmphp_prपूर्णांक_test(व्योम);	/* क्रम debugging purposes */

पूर्णांक ibmphp_hpc_पढ़ोslot(काष्ठा slot *, u8, u8 *);
पूर्णांक ibmphp_hpc_ग_लिखोslot(काष्ठा slot *, u8);
व्योम ibmphp_lock_operations(व्योम);
व्योम ibmphp_unlock_operations(व्योम);
पूर्णांक ibmphp_hpc_start_poll_thपढ़ो(व्योम);
व्योम ibmphp_hpc_stop_poll_thपढ़ो(व्योम);

//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// HPC वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_ERROR			0xFF

//-----------------------------------------------------------------------------
// BUS INFO
//-----------------------------------------------------------------------------
#घोषणा BUS_SPEED			0x30
#घोषणा BUS_MODE			0x40
#घोषणा BUS_MODE_PCIX			0x01
#घोषणा BUS_MODE_PCI			0x00
#घोषणा BUS_SPEED_2			0x20
#घोषणा BUS_SPEED_1			0x10
#घोषणा BUS_SPEED_33			0x00
#घोषणा BUS_SPEED_66			0x01
#घोषणा BUS_SPEED_100			0x02
#घोषणा BUS_SPEED_133			0x03
#घोषणा BUS_SPEED_66PCIX		0x04
#घोषणा BUS_SPEED_66UNKNOWN		0x05
#घोषणा BUS_STATUS_AVAILABLE		0x01
#घोषणा BUS_CONTROL_AVAILABLE		0x02
#घोषणा SLOT_LATCH_REGS_SUPPORTED	0x10

#घोषणा PRGM_MODEL_REV_LEVEL		0xF0
#घोषणा MAX_ADAPTER_NONE		0x09

//----------------------------------------------------------------------------
// HPC 'write' operations/commands
//----------------------------------------------------------------------------
//	Command			Code	State	Write to reg
//					Machine	at index
//-------------------------	----	-------	------------
#घोषणा HPC_CTLR_ENABLEIRQ	0x00	// N	15
#घोषणा HPC_CTLR_DISABLEIRQ	0x01	// N	15
#घोषणा HPC_SLOT_OFF		0x02	// Y	0-14
#घोषणा HPC_SLOT_ON		0x03	// Y	0-14
#घोषणा HPC_SLOT_ATTNOFF	0x04	// N	0-14
#घोषणा HPC_SLOT_ATTNON		0x05	// N	0-14
#घोषणा HPC_CTLR_CLEARIRQ	0x06	// N	15
#घोषणा HPC_CTLR_RESET		0x07	// Y	15
#घोषणा HPC_CTLR_IRQSTEER	0x08	// N	15
#घोषणा HPC_BUS_33CONVMODE	0x09	// Y	31-34
#घोषणा HPC_BUS_66CONVMODE	0x0A	// Y	31-34
#घोषणा HPC_BUS_66PCIXMODE	0x0B	// Y	31-34
#घोषणा HPC_BUS_100PCIXMODE	0x0C	// Y	31-34
#घोषणा HPC_BUS_133PCIXMODE	0x0D	// Y	31-34
#घोषणा HPC_ALLSLOT_OFF		0x11	// Y	15
#घोषणा HPC_ALLSLOT_ON		0x12	// Y	15
#घोषणा HPC_SLOT_BLINKLED	0x13	// N	0-14

//----------------------------------------------------------------------------
// पढ़ो commands
//----------------------------------------------------------------------------
#घोषणा READ_SLOTSTATUS		0x01
#घोषणा READ_EXTSLOTSTATUS	0x02
#घोषणा READ_BUSSTATUS		0x03
#घोषणा READ_CTLRSTATUS		0x04
#घोषणा READ_ALLSTAT		0x05
#घोषणा READ_ALLSLOT		0x06
#घोषणा READ_SLOTLATCHLOWREG	0x07
#घोषणा READ_REVLEVEL		0x08
#घोषणा READ_HPCOPTIONS		0x09
//----------------------------------------------------------------------------
// slot status
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_POWER		0x01
#घोषणा HPC_SLOT_CONNECT	0x02
#घोषणा HPC_SLOT_ATTN		0x04
#घोषणा HPC_SLOT_PRSNT2		0x08
#घोषणा HPC_SLOT_PRSNT1		0x10
#घोषणा HPC_SLOT_PWRGD		0x20
#घोषणा HPC_SLOT_BUS_SPEED	0x40
#घोषणा HPC_SLOT_LATCH		0x80

//----------------------------------------------------------------------------
// HPC_SLOT_POWER status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_POWER_OFF	0x00
#घोषणा HPC_SLOT_POWER_ON	0x01

//----------------------------------------------------------------------------
// HPC_SLOT_CONNECT status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_CONNECTED	0x00
#घोषणा HPC_SLOT_DISCONNECTED	0x01

//----------------------------------------------------------------------------
// HPC_SLOT_ATTN status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_ATTN_OFF	0x00
#घोषणा HPC_SLOT_ATTN_ON	0x01
#घोषणा HPC_SLOT_ATTN_BLINK	0x02

//----------------------------------------------------------------------------
// HPC_SLOT_PRSNT status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_EMPTY		0x00
#घोषणा HPC_SLOT_PRSNT_7	0x01
#घोषणा HPC_SLOT_PRSNT_15	0x02
#घोषणा HPC_SLOT_PRSNT_25	0x03

//----------------------------------------------------------------------------
// HPC_SLOT_PWRGD status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_PWRGD_FAULT_NONE	0x00
#घोषणा HPC_SLOT_PWRGD_GOOD		0x01

//----------------------------------------------------------------------------
// HPC_SLOT_BUS_SPEED status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_BUS_SPEED_OK	0x00
#घोषणा HPC_SLOT_BUS_SPEED_MISM	0x01

//----------------------------------------------------------------------------
// HPC_SLOT_LATCH status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_LATCH_OPEN	0x01	// NOTE : in PCI spec bit off = खोलो
#घोषणा HPC_SLOT_LATCH_CLOSED	0x00	// NOTE : in PCI spec bit on  = बंदd


//----------------------------------------------------------------------------
// extended slot status
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_PCIX		0x01
#घोषणा HPC_SLOT_SPEED1		0x02
#घोषणा HPC_SLOT_SPEED2		0x04
#घोषणा HPC_SLOT_BLINK_ATTN	0x08
#घोषणा HPC_SLOT_RSRVD1		0x10
#घोषणा HPC_SLOT_RSRVD2		0x20
#घोषणा HPC_SLOT_BUS_MODE	0x40
#घोषणा HPC_SLOT_RSRVD3		0x80

//----------------------------------------------------------------------------
// HPC_XSLOT_PCIX_CAP status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_PCIX_NO	0x00
#घोषणा HPC_SLOT_PCIX_YES	0x01

//----------------------------------------------------------------------------
// HPC_XSLOT_SPEED status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_SPEED_33	0x00
#घोषणा HPC_SLOT_SPEED_66	0x01
#घोषणा HPC_SLOT_SPEED_133	0x02

//----------------------------------------------------------------------------
// HPC_XSLOT_ATTN_BLINK status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_ATTN_BLINK_OFF	0x00
#घोषणा HPC_SLOT_ATTN_BLINK_ON	0x01

//----------------------------------------------------------------------------
// HPC_XSLOT_BUS_MODE status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_SLOT_BUS_MODE_OK	0x00
#घोषणा HPC_SLOT_BUS_MODE_MISM	0x01

//----------------------------------------------------------------------------
// Controller status
//----------------------------------------------------------------------------
#घोषणा HPC_CTLR_WORKING	0x01
#घोषणा HPC_CTLR_FINISHED	0x02
#घोषणा HPC_CTLR_RESULT0	0x04
#घोषणा HPC_CTLR_RESULT1	0x08
#घोषणा HPC_CTLR_RESULE2	0x10
#घोषणा HPC_CTLR_RESULT3	0x20
#घोषणा HPC_CTLR_IRQ_ROUTG	0x40
#घोषणा HPC_CTLR_IRQ_PENDG	0x80

//----------------------------------------------------------------------------
// HPC_CTLR_WORKING status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_CTLR_WORKING_NO	0x00
#घोषणा HPC_CTLR_WORKING_YES	0x01

//----------------------------------------------------------------------------
// HPC_CTLR_FINISHED status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_CTLR_FINISHED_NO	0x00
#घोषणा HPC_CTLR_FINISHED_YES	0x01

//----------------------------------------------------------------------------
// HPC_CTLR_RESULT status वापस codes
//----------------------------------------------------------------------------
#घोषणा HPC_CTLR_RESULT_SUCCESS	0x00
#घोषणा HPC_CTLR_RESULT_FAILED	0x01
#घोषणा HPC_CTLR_RESULT_RSVD	0x02
#घोषणा HPC_CTLR_RESULT_NORESP	0x03


//----------------------------------------------------------------------------
// macro क्रम slot info
//----------------------------------------------------------------------------
#घोषणा SLOT_POWER(s)	((u8) ((s & HPC_SLOT_POWER) \
	? HPC_SLOT_POWER_ON : HPC_SLOT_POWER_OFF))

#घोषणा SLOT_CONNECT(s)	((u8) ((s & HPC_SLOT_CONNECT) \
	? HPC_SLOT_DISCONNECTED : HPC_SLOT_CONNECTED))

#घोषणा SLOT_ATTN(s, es)	((u8) ((es & HPC_SLOT_BLINK_ATTN) \
	? HPC_SLOT_ATTN_BLINK \
	: ((s & HPC_SLOT_ATTN) ? HPC_SLOT_ATTN_ON : HPC_SLOT_ATTN_OFF)))

#घोषणा SLOT_PRESENT(s)	((u8) ((s & HPC_SLOT_PRSNT1) \
	? ((s & HPC_SLOT_PRSNT2) ? HPC_SLOT_EMPTY : HPC_SLOT_PRSNT_15) \
	: ((s & HPC_SLOT_PRSNT2) ? HPC_SLOT_PRSNT_25 : HPC_SLOT_PRSNT_7)))

#घोषणा SLOT_PWRGD(s)	((u8) ((s & HPC_SLOT_PWRGD) \
	? HPC_SLOT_PWRGD_GOOD : HPC_SLOT_PWRGD_FAULT_NONE))

#घोषणा SLOT_BUS_SPEED(s)	((u8) ((s & HPC_SLOT_BUS_SPEED) \
	? HPC_SLOT_BUS_SPEED_MISM : HPC_SLOT_BUS_SPEED_OK))

#घोषणा SLOT_LATCH(s)	((u8) ((s & HPC_SLOT_LATCH) \
	? HPC_SLOT_LATCH_CLOSED : HPC_SLOT_LATCH_OPEN))

#घोषणा SLOT_PCIX(es)	((u8) ((es & HPC_SLOT_PCIX) \
	? HPC_SLOT_PCIX_YES : HPC_SLOT_PCIX_NO))

#घोषणा SLOT_SPEED(es)	((u8) ((es & HPC_SLOT_SPEED2) \
	? ((es & HPC_SLOT_SPEED1) ? HPC_SLOT_SPEED_133   \
				: HPC_SLOT_SPEED_66)   \
	: HPC_SLOT_SPEED_33))

#घोषणा SLOT_BUS_MODE(es)	((u8) ((es & HPC_SLOT_BUS_MODE) \
	? HPC_SLOT_BUS_MODE_MISM : HPC_SLOT_BUS_MODE_OK))

//--------------------------------------------------------------------------
// macro क्रम bus info
//---------------------------------------------------------------------------
#घोषणा CURRENT_BUS_SPEED(s)	((u8) (s & BUS_SPEED_2) \
	? ((s & BUS_SPEED_1) ? BUS_SPEED_133 : BUS_SPEED_100) \
	: ((s & BUS_SPEED_1) ? BUS_SPEED_66 : BUS_SPEED_33))

#घोषणा CURRENT_BUS_MODE(s)	((u8) (s & BUS_MODE) ? BUS_MODE_PCIX : BUS_MODE_PCI)

#घोषणा READ_BUS_STATUS(s)	((u8) (s->options & BUS_STATUS_AVAILABLE))

#घोषणा READ_BUS_MODE(s)	((s->revision & PRGM_MODEL_REV_LEVEL) >= 0x20)

#घोषणा SET_BUS_STATUS(s)	((u8) (s->options & BUS_CONTROL_AVAILABLE))

#घोषणा READ_SLOT_LATCH(s)	((u8) (s->options & SLOT_LATCH_REGS_SUPPORTED))

//----------------------------------------------------------------------------
// macro क्रम controller info
//----------------------------------------------------------------------------
#घोषणा CTLR_WORKING(c) ((u8) ((c & HPC_CTLR_WORKING) \
	? HPC_CTLR_WORKING_YES : HPC_CTLR_WORKING_NO))
#घोषणा CTLR_FINISHED(c) ((u8) ((c & HPC_CTLR_FINISHED) \
	? HPC_CTLR_FINISHED_YES : HPC_CTLR_FINISHED_NO))
#घोषणा CTLR_RESULT(c) ((u8) ((c & HPC_CTLR_RESULT1)  \
	? ((c & HPC_CTLR_RESULT0) ? HPC_CTLR_RESULT_NORESP \
				: HPC_CTLR_RESULT_RSVD)  \
	: ((c & HPC_CTLR_RESULT0) ? HPC_CTLR_RESULT_FAILED \
				: HPC_CTLR_RESULT_SUCCESS)))

// command that affect the state machine of HPC
#घोषणा NEEDTOCHECK_CMDSTATUS(c) ((c == HPC_SLOT_OFF)        || \
				  (c == HPC_SLOT_ON)         || \
				  (c == HPC_CTLR_RESET)      || \
				  (c == HPC_BUS_33CONVMODE)  || \
				  (c == HPC_BUS_66CONVMODE)  || \
				  (c == HPC_BUS_66PCIXMODE)  || \
				  (c == HPC_BUS_100PCIXMODE) || \
				  (c == HPC_BUS_133PCIXMODE) || \
				  (c == HPC_ALLSLOT_OFF)     || \
				  (c == HPC_ALLSLOT_ON))


/* Core part of the driver */

#घोषणा ENABLE		1
#घोषणा DISABLE		0

#घोषणा CARD_INFO	0x07
#घोषणा PCIX133		0x07
#घोषणा PCIX66		0x05
#घोषणा PCI66		0x04

बाह्य काष्ठा pci_bus *ibmphp_pci_bus;

/* Variables */

काष्ठा pci_func अणु
	काष्ठा pci_dev *dev;	/* from the OS */
	u8 busno;
	u8 device;
	u8 function;
	काष्ठा resource_node *io[6];
	काष्ठा resource_node *mem[6];
	काष्ठा resource_node *pfmem[6];
	काष्ठा pci_func *next;
	पूर्णांक devices[32];	/* क्रम bridge config */
	u8 irq[4];		/* क्रम पूर्णांकerrupt config */
	u8 bus;			/* flag क्रम unconfiguring, to say अगर PPB */
पूर्ण;

काष्ठा slot अणु
	u8 bus;
	u8 device;
	u8 number;
	u8 real_physical_slot_num;
	u32 capabilities;
	u8 supported_speed;
	u8 supported_bus_mode;
	u8 flag;		/* this is क्रम disable slot and polling */
	u8 ctlr_index;
	काष्ठा hotplug_slot hotplug_slot;
	काष्ठा controller *ctrl;
	काष्ठा pci_func *func;
	u8 irq[4];
	पूर्णांक bit_mode;		/* 0 = 32, 1 = 64 */
	काष्ठा bus_info *bus_on;
	काष्ठा list_head ibm_slot_list;
	u8 status;
	u8 ext_status;
	u8 busstatus;
पूर्ण;

काष्ठा controller अणु
	काष्ठा ebda_hpc_slot *slots;
	काष्ठा ebda_hpc_bus *buses;
	काष्ठा pci_dev *ctrl_dev; /* in हाल where controller is PCI */
	u8 starting_slot_num;	/* starting and ending slot #'s this ctrl controls*/
	u8 ending_slot_num;
	u8 revision;
	u8 options;		/* which options HPC supports */
	u8 status;
	u8 ctlr_id;
	u8 slot_count;
	u8 bus_count;
	u8 ctlr_relative_id;
	u32 irq;
	जोड़ अणु
		काष्ठा isa_ctlr_access isa_ctlr;
		काष्ठा pci_ctlr_access pci_ctlr;
		काष्ठा wpeg_i2c_ctlr_access wpeg_ctlr;
	पूर्ण u;
	u8 ctlr_type;
	काष्ठा list_head ebda_hpc_list;
पूर्ण;

/* Functions */

पूर्णांक ibmphp_init_devno(काष्ठा slot **);	/* This function is called from EBDA, so we need it not be अटल */
पूर्णांक ibmphp_करो_disable_slot(काष्ठा slot *slot_cur);
पूर्णांक ibmphp_update_slot_info(काष्ठा slot *);	/* This function is called from HPC, so we need it to not be be अटल */
पूर्णांक ibmphp_configure_card(काष्ठा pci_func *, u8);
पूर्णांक ibmphp_unconfigure_card(काष्ठा slot **, पूर्णांक);
बाह्य स्थिर काष्ठा hotplug_slot_ops ibmphp_hotplug_slot_ops;

अटल अंतरभूत काष्ठा slot *to_slot(काष्ठा hotplug_slot *hotplug_slot)
अणु
	वापस container_of(hotplug_slot, काष्ठा slot, hotplug_slot);
पूर्ण

#पूर्ण_अगर				//__IBMPHP_H

