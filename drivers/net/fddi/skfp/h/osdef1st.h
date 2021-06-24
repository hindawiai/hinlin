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

/* 
 * Operating प्रणाली-dependent definitions that have to be defined
 * beक्रमe any other header files are included.
 */

// HWM (HardWare Module) Definitions
// -----------------------

#समावेश <यंत्र/byteorder.h>

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा LITTLE_ENDIAN
#अन्यथा
#घोषणा BIG_ENDIAN
#पूर्ण_अगर

// this is set in the makefile
// #घोषणा PCI			/* only PCI adapters supported by this driver */
// #घोषणा MEM_MAPPED_IO	/* use memory mapped I/O */


#घोषणा USE_CAN_ADDR		/* DA and SA in MAC header are canonical. */

#घोषणा MB_OUTSIDE_SMC		/* SMT Mbufs outside of smc काष्ठा. */

// -----------------------


// SMT Definitions 
// -----------------------
#घोषणा SYNC	       		/* allow synchronous frames */

// #घोषणा SBA			/* Synchronous Bandwidth Allocator support */
				/* not available as मुक्त source */

#घोषणा ESS			/* SBA End Station Support */

#घोषणा	SMT_PANIC(smc, nr, msg)	prपूर्णांकk(KERN_INFO "SMT PANIC: code: %d, msg: %s\n",nr,msg)


#अगर_घोषित DEBUG
#घोषणा म_लिखो(s,args...) prपूर्णांकk(KERN_INFO s, ## args)
#पूर्ण_अगर

// #घोषणा HW_PTR	u_दीर्घ
// -----------------------



// HWM and OS-specअगरic buffer definitions
// -----------------------

// शेष number of receive buffers.
#घोषणा NUM_RECEIVE_BUFFERS		10

// शेष number of transmit buffers.
#घोषणा NUM_TRANSMIT_BUFFERS		10

// Number of SMT buffers (Mbufs).
#घोषणा NUM_SMT_BUF	4

// Number of TXDs क्रम asynchronous transmit queue.
#घोषणा HWM_ASYNC_TXD_COUNT	(NUM_TRANSMIT_BUFFERS + NUM_SMT_BUF)

// Number of TXDs क्रम synchronous transmit queue.
#घोषणा HWM_SYNC_TXD_COUNT	HWM_ASYNC_TXD_COUNT


// Number of RXDs क्रम receive queue #1.
// Note: Workaround क्रम ASIC Errata #7: One extra RXD is required.
#अगर (NUM_RECEIVE_BUFFERS > 100)
#घोषणा SMT_R1_RXD_COUNT	(1 + 100)
#अन्यथा
#घोषणा SMT_R1_RXD_COUNT	(1 + NUM_RECEIVE_BUFFERS)
#पूर्ण_अगर

// Number of RXDs क्रम receive queue #2.
#घोषणा SMT_R2_RXD_COUNT	0	// Not used.
// -----------------------



/*
 * OS-specअगरic part of the transmit/receive descriptor काष्ठाure (TXD/RXD).
 *
 * Note: The size of these काष्ठाures must follow this rule:
 *
 *	माप(काष्ठा) + 2*माप(व्योम*) == n * 16, n >= 1
 *
 * We use the dma_addr fields under Linux to keep track of the
 * DMA address of the packet data, क्रम later pci_unmap_single. -DaveM
 */

काष्ठा s_txd_os अणु	// os-specअगरic part of transmit descriptor
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
पूर्ण ;

काष्ठा s_rxd_os अणु	// os-specअगरic part of receive descriptor
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
पूर्ण ;


/*
 * So we करो not need to make too many modअगरications to the generic driver
 * parts, we take advantage of the AIX byte swapping macro पूर्णांकerface.
 */

#घोषणा AIX_REVERSE(x)		((u32)le32_to_cpu((u32)(x)))
#घोषणा MDR_REVERSE(x)		((u32)le32_to_cpu((u32)(x)))
