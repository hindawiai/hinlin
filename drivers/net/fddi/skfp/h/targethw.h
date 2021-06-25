<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

#अगर_अघोषित	_TARGETHW_
#घोषणा _TARGETHW_

	/*
	 *  PCI Watermark definition
	 */
#अगर_घोषित	PCI
#घोषणा	RX_WATERMARK	24
#घोषणा TX_WATERMARK	24
#घोषणा SK_ML_ID_1	0x20
#घोषणा SK_ML_ID_2	0x30
#पूर्ण_अगर

#समावेश	"skfbi.h"
#अगर_अघोषित TAG_MODE	
#समावेश	"fplus.h"
#अन्यथा
#समावेश	"fplustm.h"
#पूर्ण_अगर

#अगर_अघोषित	HW_PTR
#घोषणा HW_PTR  व्योम __iomem *
#पूर्ण_अगर

#अगर_घोषित MULT_OEM
#घोषणा	OI_STAT_LAST		0	/* end of OEM data base */
#घोषणा	OI_STAT_PRESENT		1	/* entry present but not empty */
#घोषणा	OI_STAT_VALID		2	/* holds valid ID, but is not active */ 
#घोषणा	OI_STAT_ACTIVE		3	/* holds valid ID, entry is active */
					/* active = adapter is supported */

/* Memory representation of IDs must match representation in adapter. */
काष्ठा	s_oem_ids अणु
	u_अक्षर	oi_status ;		/* Stat: last, present, valid, active */
	u_अक्षर	oi_mark[5] ;		/* "PID00" .. "PID07" ..	*/
	u_अक्षर 	oi_id[4] ;		/* id bytes, representation as	*/
					/* defined by hardware,		*/	
#अगर_घोषित PCI
	u_अक्षर 	oi_sub_id[4] ;		/* sub id bytes, representation as */
					/* defined by hardware,		*/
#पूर्ण_अगर
पूर्ण ;
#पूर्ण_अगर	/* MULT_OEM */


काष्ठा s_smt_hw अणु
	/*
	 * global
	 */
	HW_PTR	iop ;			/* IO base address */
	लघु	dma ;			/* DMA channel */
	लघु	irq ;			/* IRQ level */
	लघु	eprom ;			/* FLASH prom */

#अगर_अघोषित SYNC
	u_लघु	n_a_send ;		/* pending send requests */
#पूर्ण_अगर

#अगर	defined(PCI)
	लघु	slot ;			/* slot number */
	लघु   max_slots ;		/* maximum number of slots */
	लघु	wकरोg_used ;		/* TRUE अगर the watch करोg is used */
#पूर्ण_अगर

#अगर_घोषित	PCI
	u_लघु	pci_handle ;		/* handle to access the BIOS func */
	u_दीर्घ	is_imask ;		/* पूर्णांक maske क्रम the पूर्णांक source reg */
	u_दीर्घ	phys_mem_addr ;		/* physical memory address */
	u_लघु	mc_dummy ;		/* work around क्रम MC compiler bug */	
	/*
	 * state of the hardware
	 */
	u_लघु hw_state ;		/* started or stopped */

#घोषणा	STARTED		1
#घोषणा	STOPPED		0

	पूर्णांक	hw_is_64bit ;		/* करोes we have a 64 bit adapter */
#पूर्ण_अगर

#अगर_घोषित	TAG_MODE
	u_दीर्घ	pci_fix_value ;		/* value parsed by PCIFIX */
#पूर्ण_अगर

	/*
	 * hwt.c
	 */
	u_दीर्घ	t_start ;		/* HWT start */
	u_दीर्घ	t_stop ;		/* HWT stop */
	u_लघु	समयr_activ ;		/* HWT समयr active */

	/*
	 * PIC
	 */
	u_अक्षर	pic_a1 ;
	u_अक्षर	pic_21 ;

	/*
	 * GENERIC ; करो not modअगरy beyond this line
	 */

	/*
	 * physical and canonical address
	 */
	काष्ठा fddi_addr fddi_home_addr ;
	काष्ठा fddi_addr fddi_canon_addr ;
	काष्ठा fddi_addr fddi_phys_addr ;

	/*
	 * mac variables
	 */
	काष्ठा mac_parameter mac_pa ;	/* पंचांगin, पंचांगax, tvx, treq .. */
	काष्ठा mac_counter mac_ct ;	/* recv., lost, error  */
	u_लघु	mac_ring_is_up ;	/* ring is up flag */

	काष्ठा s_smt_fp	fp ;		/* क्रमmac+ */

#अगर_घोषित MULT_OEM
	काष्ठा s_oem_ids *oem_id ;	/* poपूर्णांकer to selected id */
	पूर्णांक oem_min_status ;		/* IDs to take care of */
#पूर्ण_अगर	/* MULT_OEM */

पूर्ण ;
#पूर्ण_अगर
