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
 *	Operating प्रणाली specअगरic definitions क्रम driver and
 *	hardware module.
 */

#अगर_अघोषित	TARGETOS_H
#घोषणा TARGETOS_H


//-------- those should go पूर्णांकo include/linux/pci.h
#घोषणा PCI_VENDOR_ID_SK		0x1148
#घोषणा PCI_DEVICE_ID_SK_FP		0x4000
//--------



//-------- those should go पूर्णांकo include/linux/अगर_fddi.h
#घोषणा FDDI_MAC_HDR_LEN 13

#घोषणा FDDI_RII	0x01 /* routing inक्रमmation bit */
#घोषणा FDDI_RCF_सूची_BIT 0x80
#घोषणा FDDI_RCF_LEN_MASK 0x1f
#घोषणा FDDI_RCF_BROADCAST 0x8000
#घोषणा FDDI_RCF_LIMITED_BROADCAST 0xA000
#घोषणा FDDI_RCF_FRAME2K 0x20
#घोषणा FDDI_RCF_FRAME4K 0x30
//--------


#अघोषित ADDR

#समावेश <यंत्र/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/fddidevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/pci.h>

// is redefined by linux, but we need our definition
#अघोषित ADDR
#अगर_घोषित MEM_MAPPED_IO
#घोषणा	ADDR(a) (smc->hw.iop+(a))
#अन्यथा
#घोषणा	ADDR(a) (((a)>>7) ? (outp(smc->hw.iop+B0_RAP,(a)>>7), (smc->hw.iop+( ((a)&0x7F) | ((a)>>7 ? 0x80:0)) )) : (smc->hw.iop+(((a)&0x7F)|((a)>>7 ? 0x80:0))))
#पूर्ण_अगर

#समावेश "hwmtm.h"

#घोषणा TRUE  1
#घोषणा FALSE 0

// HWM Definitions
// -----------------------
#घोषणा FDDI_TRACE(string, arg1, arg2, arg3)	// Perक्रमmance analysis.
#अगर_घोषित PCI
#घोषणा NDD_TRACE(string, arg1, arg2, arg3)	// Perक्रमmance analysis.
#पूर्ण_अगर	// PCI
#घोषणा SMT_PAGESIZE	PAGE_SIZE	// Size of a memory page (घातer of 2).
// -----------------------


// SMT Definitions
// -----------------------
#घोषणा	TICKS_PER_SECOND	HZ
#घोषणा SMC_VERSION    		1
// -----------------------


// OS-Driver Definitions
// -----------------------
#घोषणा NO_ADDRESS 0xffe0	/* No Device (I/O) Address */
#घोषणा SKFP_MAX_NUM_BOARDS 8	/* maximum number of PCI boards */

#घोषणा SK_BUS_TYPE_PCI		0
#घोषणा SK_BUS_TYPE_EISA	1

#घोषणा FP_IO_LEN		256	/* length of IO area used */

#घोषणा u8	अचिन्हित अक्षर
#घोषणा u16	अचिन्हित लघु
#घोषणा u32	अचिन्हित पूर्णांक

#घोषणा MAX_TX_QUEUE_LEN	20 // number of packets queued by driver
#घोषणा MAX_FRAME_SIZE		4550

#घोषणा	RX_LOW_WATERMARK	NUM_RECEIVE_BUFFERS  / 2
#घोषणा TX_LOW_WATERMARK	NUM_TRANSMIT_BUFFERS - 2

/*
** Include the IOCTL stuff
*/
#समावेश <linux/sockios.h>

#घोषणा	SKFPIOCTL	SIOCDEVPRIVATE

काष्ठा s_skfp_ioctl अणु
	अचिन्हित लघु cmd;                /* Command to run */
	अचिन्हित लघु len;                /* Length of the data buffer */
	अचिन्हित अक्षर __user *data;        /* Poपूर्णांकer to the data buffer */
पूर्ण;

/* 
** Recognised ioctl commands क्रम the driver 
*/
#घोषणा SKFP_GET_STATS		0x05 /* Get the driver statistics */
#घोषणा SKFP_CLR_STATS		0x06 /* Zero out the driver statistics */

// The per-adapter driver काष्ठाure
काष्ठा s_smt_os अणु
	काष्ठा net_device *dev;
	काष्ठा net_device *next_module;
	u32	bus_type;		/* bus type (0 == PCI, 1 == EISA) */
	काष्ठा pci_dev 	pdev;		/* PCI device काष्ठाure */
	
	अचिन्हित दीर्घ base_addr;
	अचिन्हित अक्षर factory_mac_addr[8];
	uदीर्घ	SharedMemSize;
	uदीर्घ	SharedMemHeap;
	व्योम*	SharedMemAddr;
	dma_addr_t SharedMemDMA;

	uदीर्घ	QueueSkb;
	काष्ठा	sk_buff_head SendSkbQueue;

	uदीर्घ	MaxFrameSize;
	u8	ResetRequested;

	// MAC statistics काष्ठाure
	काष्ठा fddi_statistics MacStat;

	// receive पूर्णांकo this local buffer अगर no skb available
	// data will be not valid, because multiple RxDs can
	// poपूर्णांक here at the same समय, it must be at least
	// MAX_FRAME_SIZE bytes in size
	अचिन्हित अक्षर *LocalRxBuffer;
	dma_addr_t LocalRxBufferDMA;
	
	// Version (required by SMT module).
	u_दीर्घ smc_version ;

	// Required by Hardware Module (HWM).
	काष्ठा hw_modul hwm ;
	
	// For SMP-savety
	spinlock_t DriverLock;
	
पूर्ण;

प्रकार काष्ठा s_smt_os skfddi_priv;

#पूर्ण_अगर	 // _TARGETOS_
