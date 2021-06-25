<शैली गुरु>
/*
*******************************************************************************
**        O.S   : Linux
**   खाता NAME  : arcmsr.h
**        BY    : Nick Cheng
**   Description: SCSI RAID Device Driver क्रम
**                ARECA RAID Host adapter
*******************************************************************************
** Copyright (C) 2002 - 2005, Areca Technology Corporation All rights reserved.
**
**     Web site: www.areca.com.tw
**       E-mail: support@areca.com.tw
**
** This program is मुक्त software; you can redistribute it and/or modअगरy
** it under the terms of the GNU General Public License version 2 as
** published by the Free Software Foundation.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License क्रम more details.
*******************************************************************************
** Redistribution and use in source and binary क्रमms, with or without
** modअगरication, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary क्रमm must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    करोcumentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to enकरोrse or promote products
**    derived from this software without specअगरic prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION)HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**(INCLUDING NEGLIGENCE OR OTHERWISE)ARISING IN ANY WAY OUT OF THE USE OF
** THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************
*/
#समावेश <linux/पूर्णांकerrupt.h>
काष्ठा device_attribute;
/*The limit of outstanding scsi command that firmware can handle*/
#घोषणा ARCMSR_MAX_FREECCB_NUM		1024
#घोषणा ARCMSR_MAX_OUTSTANDING_CMD	1024
#घोषणा ARCMSR_DEFAULT_OUTSTANDING_CMD	128
#घोषणा ARCMSR_MIN_OUTSTANDING_CMD	32
#घोषणा ARCMSR_DRIVER_VERSION		"v1.50.00.02-20200819"
#घोषणा ARCMSR_SCSI_INITIATOR_ID	255
#घोषणा ARCMSR_MAX_XFER_SECTORS		512
#घोषणा ARCMSR_MAX_XFER_SECTORS_B	4096
#घोषणा ARCMSR_MAX_XFER_SECTORS_C	304
#घोषणा ARCMSR_MAX_TARGETID		17
#घोषणा ARCMSR_MAX_TARGETLUN		8
#घोषणा ARCMSR_MAX_CMD_PERLUN		128
#घोषणा ARCMSR_DEFAULT_CMD_PERLUN	32
#घोषणा ARCMSR_MIN_CMD_PERLUN		1
#घोषणा ARCMSR_MAX_QBUFFER		4096
#घोषणा ARCMSR_DEFAULT_SG_ENTRIES	38
#घोषणा ARCMSR_MAX_HBB_POSTQUEUE	264
#घोषणा ARCMSR_MAX_ARC1214_POSTQUEUE	256
#घोषणा ARCMSR_MAX_ARC1214_DONEQUEUE	257
#घोषणा ARCMSR_MAX_HBE_DONEQUEUE	512
#घोषणा ARCMSR_MAX_XFER_LEN		0x26000 /* 152K */
#घोषणा ARCMSR_CDB_SG_PAGE_LENGTH	256
#घोषणा ARCMST_NUM_MSIX_VECTORS		4
#अगर_अघोषित PCI_DEVICE_ID_ARECA_1880
#घोषणा PCI_DEVICE_ID_ARECA_1880	0x1880
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_ARECA_1214
#घोषणा PCI_DEVICE_ID_ARECA_1214	0x1214
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_ARECA_1203
#घोषणा PCI_DEVICE_ID_ARECA_1203	0x1203
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_ARECA_1884
#घोषणा PCI_DEVICE_ID_ARECA_1884	0x1884
#पूर्ण_अगर
#घोषणा PCI_DEVICE_ID_ARECA_1886	0x188A
#घोषणा	ARCMSR_HOURS			(1000 * 60 * 60 * 4)
#घोषणा	ARCMSR_MINUTES			(1000 * 60 * 60)
#घोषणा ARCMSR_DEFAULT_TIMEOUT		90
/*
**********************************************************************************
**
**********************************************************************************
*/
#घोषणा ARC_SUCCESS	0
#घोषणा ARC_FAILURE	1
/*
*******************************************************************************
**        split 64bits dma addressing
*******************************************************************************
*/
#घोषणा dma_addr_hi32(addr)	(uपूर्णांक32_t) ((addr>>16)>>16)
#घोषणा dma_addr_lo32(addr)	(uपूर्णांक32_t) (addr & 0xffffffff)
/*
*******************************************************************************
**        MESSAGE CONTROL CODE
*******************************************************************************
*/
काष्ठा CMD_MESSAGE
अणु
      uपूर्णांक32_t HeaderLength;
      uपूर्णांक8_t  Signature[8];
      uपूर्णांक32_t Timeout;
      uपूर्णांक32_t ControlCode;
      uपूर्णांक32_t ReturnCode;
      uपूर्णांक32_t Length;
पूर्ण;
/*
*******************************************************************************
**        IOP Message Transfer Data क्रम user space
*******************************************************************************
*/
#घोषणा	ARCMSR_API_DATA_BUFLEN	1032
काष्ठा CMD_MESSAGE_FIELD
अणु
    काष्ठा CMD_MESSAGE			cmdmessage;
    uपूर्णांक8_t				messagedatabuffer[ARCMSR_API_DATA_BUFLEN];
पूर्ण;
/* IOP message transfer */
#घोषणा ARCMSR_MESSAGE_FAIL			0x0001
/* DeviceType */
#घोषणा ARECA_SATA_RAID				0x90000000
/* FunctionCode */
#घोषणा FUNCTION_READ_RQBUFFER			0x0801
#घोषणा FUNCTION_WRITE_WQBUFFER			0x0802
#घोषणा FUNCTION_CLEAR_RQBUFFER			0x0803
#घोषणा FUNCTION_CLEAR_WQBUFFER			0x0804
#घोषणा FUNCTION_CLEAR_ALLQBUFFER		0x0805
#घोषणा FUNCTION_RETURN_CODE_3F			0x0806
#घोषणा FUNCTION_SAY_HELLO			0x0807
#घोषणा FUNCTION_SAY_GOODBYE			0x0808
#घोषणा FUNCTION_FLUSH_ADAPTER_CACHE		0x0809
#घोषणा FUNCTION_GET_FIRMWARE_STATUS		0x080A
#घोषणा FUNCTION_HARDWARE_RESET			0x080B
/* ARECA IO CONTROL CODE*/
#घोषणा ARCMSR_MESSAGE_READ_RQBUFFER       \
	ARECA_SATA_RAID | FUNCTION_READ_RQBUFFER
#घोषणा ARCMSR_MESSAGE_WRITE_WQBUFFER      \
	ARECA_SATA_RAID | FUNCTION_WRITE_WQBUFFER
#घोषणा ARCMSR_MESSAGE_CLEAR_RQBUFFER      \
	ARECA_SATA_RAID | FUNCTION_CLEAR_RQBUFFER
#घोषणा ARCMSR_MESSAGE_CLEAR_WQBUFFER      \
	ARECA_SATA_RAID | FUNCTION_CLEAR_WQBUFFER
#घोषणा ARCMSR_MESSAGE_CLEAR_ALLQBUFFER    \
	ARECA_SATA_RAID | FUNCTION_CLEAR_ALLQBUFFER
#घोषणा ARCMSR_MESSAGE_RETURN_CODE_3F      \
	ARECA_SATA_RAID | FUNCTION_RETURN_CODE_3F
#घोषणा ARCMSR_MESSAGE_SAY_HELLO           \
	ARECA_SATA_RAID | FUNCTION_SAY_HELLO
#घोषणा ARCMSR_MESSAGE_SAY_GOODBYE         \
	ARECA_SATA_RAID | FUNCTION_SAY_GOODBYE
#घोषणा ARCMSR_MESSAGE_FLUSH_ADAPTER_CACHE \
	ARECA_SATA_RAID | FUNCTION_FLUSH_ADAPTER_CACHE
/* ARECA IOCTL ReturnCode */
#घोषणा ARCMSR_MESSAGE_RETURNCODE_OK		0x00000001
#घोषणा ARCMSR_MESSAGE_RETURNCODE_ERROR		0x00000006
#घोषणा ARCMSR_MESSAGE_RETURNCODE_3F		0x0000003F
#घोषणा ARCMSR_MESSAGE_RETURNCODE_BUS_HANG_ON	0x00000088
/*
*************************************************************
**   काष्ठाure क्रम holding DMA address data
*************************************************************
*/
#घोषणा IS_DMA64	(माप(dma_addr_t) == 8)
#घोषणा IS_SG64_ADDR	0x01000000 /* bit24 */
काष्ठा  SG32ENTRY
अणु
	__le32		length;
	__le32		address;
पूर्ण__attribute__ ((packed));
काष्ठा  SG64ENTRY
अणु
	__le32		length;
	__le32		address;
	__le32		addresshigh;
पूर्ण__attribute__ ((packed));
/*
********************************************************************
**      Q Buffer of IOP Message Transfer
********************************************************************
*/
काष्ठा QBUFFER
अणु
	uपूर्णांक32_t      data_len;
	uपूर्णांक8_t       data[124];
पूर्ण;
/*
*******************************************************************************
**      FIRMWARE INFO क्रम Intel IOP R 80331 processor (Type A)
*******************************************************************************
*/
काष्ठा FIRMWARE_INFO
अणु
	uपूर्णांक32_t	signature;		/*0, 00-03*/
	uपूर्णांक32_t	request_len;		/*1, 04-07*/
	uपूर्णांक32_t	numbers_queue;		/*2, 08-11*/
	uपूर्णांक32_t	sdram_size;		/*3, 12-15*/
	uपूर्णांक32_t	ide_channels;		/*4, 16-19*/
	अक्षर		venकरोr[40];		/*5, 20-59*/
	अक्षर		model[8];		/*15, 60-67*/
	अक्षर		firmware_ver[16];     	/*17, 68-83*/
	अक्षर		device_map[16];		/*21, 84-99*/
	uपूर्णांक32_t	cfgVersion;		/*25,100-103 Added क्रम checking of new firmware capability*/
	uपूर्णांक8_t		cfgSerial[16];		/*26,104-119*/
	uपूर्णांक32_t	cfgPicStatus;		/*30,120-123*/
पूर्ण;
/* signature of set and get firmware config */
#घोषणा ARCMSR_SIGNATURE_GET_CONFIG		0x87974060
#घोषणा ARCMSR_SIGNATURE_SET_CONFIG		0x87974063
/* message code of inbound message रेजिस्टर */
#घोषणा ARCMSR_INBOUND_MESG0_NOP		0x00000000
#घोषणा ARCMSR_INBOUND_MESG0_GET_CONFIG		0x00000001
#घोषणा ARCMSR_INBOUND_MESG0_SET_CONFIG		0x00000002
#घोषणा ARCMSR_INBOUND_MESG0_ABORT_CMD		0x00000003
#घोषणा ARCMSR_INBOUND_MESG0_STOP_BGRB		0x00000004
#घोषणा ARCMSR_INBOUND_MESG0_FLUSH_CACHE	0x00000005
#घोषणा ARCMSR_INBOUND_MESG0_START_BGRB		0x00000006
#घोषणा ARCMSR_INBOUND_MESG0_CHK331PENDING	0x00000007
#घोषणा ARCMSR_INBOUND_MESG0_SYNC_TIMER		0x00000008
/* करोorbell पूर्णांकerrupt generator */
#घोषणा ARCMSR_INBOUND_DRIVER_DATA_WRITE_OK	0x00000001
#घोषणा ARCMSR_INBOUND_DRIVER_DATA_READ_OK	0x00000002
#घोषणा ARCMSR_OUTBOUND_IOP331_DATA_WRITE_OK	0x00000001
#घोषणा ARCMSR_OUTBOUND_IOP331_DATA_READ_OK	0x00000002
/* ccb areca cdb flag */
#घोषणा ARCMSR_CCBPOST_FLAG_SGL_BSIZE		0x80000000
#घोषणा ARCMSR_CCBPOST_FLAG_IAM_BIOS		0x40000000
#घोषणा ARCMSR_CCBREPLY_FLAG_IAM_BIOS		0x40000000
#घोषणा ARCMSR_CCBREPLY_FLAG_ERROR_MODE0	0x10000000
#घोषणा ARCMSR_CCBREPLY_FLAG_ERROR_MODE1	0x00000001
/* outbound firmware ok */
#घोषणा ARCMSR_OUTBOUND_MESG1_FIRMWARE_OK	0x80000000
/* ARC-1680 Bus Reset*/
#घोषणा ARCMSR_ARC1680_BUS_RESET		0x00000003
/* ARC-1880 Bus Reset*/
#घोषणा ARCMSR_ARC1880_RESET_ADAPTER		0x00000024
#घोषणा ARCMSR_ARC1880_DiagWrite_ENABLE		0x00000080

/*
************************************************************************
**                SPEC. क्रम Areca Type B adapter
************************************************************************
*/
/* ARECA HBB COMMAND क्रम its FIRMWARE */
/* winकरोw of "instruction flags" from driver to iop */
#घोषणा ARCMSR_DRV2IOP_DOORBELL                       0x00020400
#घोषणा ARCMSR_DRV2IOP_DOORBELL_MASK                  0x00020404
/* winकरोw of "instruction flags" from iop to driver */
#घोषणा ARCMSR_IOP2DRV_DOORBELL                       0x00020408
#घोषणा ARCMSR_IOP2DRV_DOORBELL_MASK                  0x0002040C
/* winकरोw of "instruction flags" from iop to driver */
#घोषणा ARCMSR_IOP2DRV_DOORBELL_1203                  0x00021870
#घोषणा ARCMSR_IOP2DRV_DOORBELL_MASK_1203             0x00021874
/* winकरोw of "instruction flags" from driver to iop */
#घोषणा ARCMSR_DRV2IOP_DOORBELL_1203                  0x00021878
#घोषणा ARCMSR_DRV2IOP_DOORBELL_MASK_1203             0x0002187C
/* ARECA FLAG LANGUAGE */
/* ioctl transfer */
#घोषणा ARCMSR_IOP2DRV_DATA_WRITE_OK                  0x00000001
/* ioctl transfer */
#घोषणा ARCMSR_IOP2DRV_DATA_READ_OK                   0x00000002
#घोषणा ARCMSR_IOP2DRV_CDB_DONE                       0x00000004
#घोषणा ARCMSR_IOP2DRV_MESSAGE_CMD_DONE               0x00000008

#घोषणा ARCMSR_DOORBELL_HANDLE_INT		      0x0000000F
#घोषणा ARCMSR_DOORBELL_INT_CLEAR_PATTERN   	      0xFF00FFF0
#घोषणा ARCMSR_MESSAGE_INT_CLEAR_PATTERN	      0xFF00FFF7
/* (ARCMSR_INBOUND_MESG0_GET_CONFIG<<16)|ARCMSR_DRV2IOP_MESSAGE_CMD_POSTED) */
#घोषणा ARCMSR_MESSAGE_GET_CONFIG		      0x00010008
/* (ARCMSR_INBOUND_MESG0_SET_CONFIG<<16)|ARCMSR_DRV2IOP_MESSAGE_CMD_POSTED) */
#घोषणा ARCMSR_MESSAGE_SET_CONFIG		      0x00020008
/* (ARCMSR_INBOUND_MESG0_ABORT_CMD<<16)|ARCMSR_DRV2IOP_MESSAGE_CMD_POSTED) */
#घोषणा ARCMSR_MESSAGE_ABORT_CMD		      0x00030008
/* (ARCMSR_INBOUND_MESG0_STOP_BGRB<<16)|ARCMSR_DRV2IOP_MESSAGE_CMD_POSTED) */
#घोषणा ARCMSR_MESSAGE_STOP_BGRB		      0x00040008
/* (ARCMSR_INBOUND_MESG0_FLUSH_CACHE<<16)|ARCMSR_DRV2IOP_MESSAGE_CMD_POSTED) */
#घोषणा ARCMSR_MESSAGE_FLUSH_CACHE                    0x00050008
/* (ARCMSR_INBOUND_MESG0_START_BGRB<<16)|ARCMSR_DRV2IOP_MESSAGE_CMD_POSTED) */
#घोषणा ARCMSR_MESSAGE_START_BGRB		      0x00060008
#घोषणा ARCMSR_MESSAGE_SYNC_TIMER		      0x00080008
#घोषणा ARCMSR_MESSAGE_START_DRIVER_MODE	      0x000E0008
#घोषणा ARCMSR_MESSAGE_SET_POST_WINDOW		      0x000F0008
#घोषणा ARCMSR_MESSAGE_ACTIVE_EOI_MODE		      0x00100008
/* ARCMSR_OUTBOUND_MESG1_FIRMWARE_OK */
#घोषणा ARCMSR_MESSAGE_FIRMWARE_OK		      0x80000000
/* ioctl transfer */
#घोषणा ARCMSR_DRV2IOP_DATA_WRITE_OK                  0x00000001
/* ioctl transfer */
#घोषणा ARCMSR_DRV2IOP_DATA_READ_OK                   0x00000002
#घोषणा ARCMSR_DRV2IOP_CDB_POSTED                     0x00000004
#घोषणा ARCMSR_DRV2IOP_MESSAGE_CMD_POSTED             0x00000008
#घोषणा ARCMSR_DRV2IOP_END_OF_INTERRUPT	              0x00000010

/* data tunnel buffer between user space program and its firmware */
/* user space data to iop 128bytes */
#घोषणा ARCMSR_MESSAGE_WBUFFER			      0x0000fe00
/* iop data to user space 128bytes */
#घोषणा ARCMSR_MESSAGE_RBUFFER			      0x0000ff00
/* iop message_rwbuffer क्रम message command */
#घोषणा ARCMSR_MESSAGE_RWBUFFER			      0x0000fa00

#घोषणा MEM_BASE0(x)	(u32 __iomem *)((अचिन्हित दीर्घ)acb->mem_base0 + x)
#घोषणा MEM_BASE1(x)	(u32 __iomem *)((अचिन्हित दीर्घ)acb->mem_base1 + x)
/* 
************************************************************************
**                SPEC. क्रम Areca HBC adapter
************************************************************************
*/
#घोषणा ARCMSR_HBC_ISR_THROTTLING_LEVEL		12
#घोषणा ARCMSR_HBC_ISR_MAX_DONE_QUEUE		20
/* Host Interrupt Mask */
#घोषणा ARCMSR_HBCMU_UTILITY_A_ISR_MASK		0x00000001 /* When clear, the Utility_A पूर्णांकerrupt routes to the host.*/
#घोषणा ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR_MASK	0x00000004 /* When clear, the General Outbound Doorbell पूर्णांकerrupt routes to the host.*/
#घोषणा ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR_MASK	0x00000008 /* When clear, the Outbound Post List FIFO Not Empty पूर्णांकerrupt routes to the host.*/
#घोषणा ARCMSR_HBCMU_ALL_INTMASKENABLE		0x0000000D /* disable all ISR */
/* Host Interrupt Status */
#घोषणा ARCMSR_HBCMU_UTILITY_A_ISR		0x00000001
	/*
	** Set when the Utility_A Interrupt bit is set in the Outbound Doorbell Register.
	** It clears by writing a 1 to the Utility_A bit in the Outbound Doorbell Clear Register or through स्वतःmatic clearing (अगर enabled).
	*/
#घोषणा ARCMSR_HBCMU_OUTBOUND_DOORBELL_ISR	0x00000004
	/*
	** Set अगर Outbound Doorbell रेजिस्टर bits 30:1 have a non-zero
	** value. This bit clears only when Outbound Doorbell bits
	** 30:1 are ALL clear. Only a ग_लिखो to the Outbound Doorbell
	** Clear रेजिस्टर clears bits in the Outbound Doorbell रेजिस्टर.
	*/
#घोषणा ARCMSR_HBCMU_OUTBOUND_POSTQUEUE_ISR	0x00000008
	/*
	** Set whenever the Outbound Post List Producer/Consumer
	** Register (FIFO) is not empty. It clears when the Outbound
	** Post List FIFO is empty.
	*/
#घोषणा ARCMSR_HBCMU_SAS_ALL_INT		0x00000010
	/*
	** This bit indicates a SAS पूर्णांकerrupt from a source बाह्यal to
	** the PCIe core. This bit is not maskable.
	*/
	/* DoorBell*/
#घोषणा ARCMSR_HBCMU_DRV2IOP_DATA_WRITE_OK			0x00000002
#घोषणा ARCMSR_HBCMU_DRV2IOP_DATA_READ_OK			0x00000004
	/*inbound message 0 पढ़ोy*/
#घोषणा ARCMSR_HBCMU_DRV2IOP_MESSAGE_CMD_DONE			0x00000008
	/*more than 12 request completed in a समय*/
#घोषणा ARCMSR_HBCMU_DRV2IOP_POSTQUEUE_THROTTLING		0x00000010
#घोषणा ARCMSR_HBCMU_IOP2DRV_DATA_WRITE_OK			0x00000002
	/*outbound DATA WRITE isr करोor bell clear*/
#घोषणा ARCMSR_HBCMU_IOP2DRV_DATA_WRITE_DOORBELL_CLEAR		0x00000002
#घोषणा ARCMSR_HBCMU_IOP2DRV_DATA_READ_OK			0x00000004
	/*outbound DATA READ isr करोor bell clear*/
#घोषणा ARCMSR_HBCMU_IOP2DRV_DATA_READ_DOORBELL_CLEAR		0x00000004
	/*outbound message 0 पढ़ोy*/
#घोषणा ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE			0x00000008
	/*outbound message cmd isr करोor bell clear*/
#घोषणा ARCMSR_HBCMU_IOP2DRV_MESSAGE_CMD_DONE_DOORBELL_CLEAR	0x00000008
	/*ARCMSR_HBAMU_MESSAGE_FIRMWARE_OK*/
#घोषणा ARCMSR_HBCMU_MESSAGE_FIRMWARE_OK			0x80000000
/*
*******************************************************************************
**                SPEC. क्रम Areca Type D adapter
*******************************************************************************
*/
#घोषणा ARCMSR_ARC1214_CHIP_ID				0x00004
#घोषणा ARCMSR_ARC1214_CPU_MEMORY_CONFIGURATION		0x00008
#घोषणा ARCMSR_ARC1214_I2_HOST_INTERRUPT_MASK		0x00034
#घोषणा ARCMSR_ARC1214_SAMPLE_RESET			0x00100
#घोषणा ARCMSR_ARC1214_RESET_REQUEST			0x00108
#घोषणा ARCMSR_ARC1214_MAIN_INTERRUPT_STATUS		0x00200
#घोषणा ARCMSR_ARC1214_PCIE_F0_INTERRUPT_ENABLE		0x0020C
#घोषणा ARCMSR_ARC1214_INBOUND_MESSAGE0			0x00400
#घोषणा ARCMSR_ARC1214_INBOUND_MESSAGE1			0x00404
#घोषणा ARCMSR_ARC1214_OUTBOUND_MESSAGE0		0x00420
#घोषणा ARCMSR_ARC1214_OUTBOUND_MESSAGE1		0x00424
#घोषणा ARCMSR_ARC1214_INBOUND_DOORBELL			0x00460
#घोषणा ARCMSR_ARC1214_OUTBOUND_DOORBELL		0x00480
#घोषणा ARCMSR_ARC1214_OUTBOUND_DOORBELL_ENABLE		0x00484
#घोषणा ARCMSR_ARC1214_INBOUND_LIST_BASE_LOW		0x01000
#घोषणा ARCMSR_ARC1214_INBOUND_LIST_BASE_HIGH		0x01004
#घोषणा ARCMSR_ARC1214_INBOUND_LIST_WRITE_POINTER	0x01018
#घोषणा ARCMSR_ARC1214_OUTBOUND_LIST_BASE_LOW		0x01060
#घोषणा ARCMSR_ARC1214_OUTBOUND_LIST_BASE_HIGH		0x01064
#घोषणा ARCMSR_ARC1214_OUTBOUND_LIST_COPY_POINTER	0x0106C
#घोषणा ARCMSR_ARC1214_OUTBOUND_LIST_READ_POINTER	0x01070
#घोषणा ARCMSR_ARC1214_OUTBOUND_INTERRUPT_CAUSE		0x01088
#घोषणा ARCMSR_ARC1214_OUTBOUND_INTERRUPT_ENABLE	0x0108C
#घोषणा ARCMSR_ARC1214_MESSAGE_WBUFFER			0x02000
#घोषणा ARCMSR_ARC1214_MESSAGE_RBUFFER			0x02100
#घोषणा ARCMSR_ARC1214_MESSAGE_RWBUFFER			0x02200
/* Host Interrupt Mask */
#घोषणा ARCMSR_ARC1214_ALL_INT_ENABLE			0x00001010
#घोषणा ARCMSR_ARC1214_ALL_INT_DISABLE			0x00000000
/* Host Interrupt Status */
#घोषणा ARCMSR_ARC1214_OUTBOUND_DOORBELL_ISR		0x00001000
#घोषणा ARCMSR_ARC1214_OUTBOUND_POSTQUEUE_ISR		0x00000010
/* DoorBell*/
#घोषणा ARCMSR_ARC1214_DRV2IOP_DATA_IN_READY		0x00000001
#घोषणा ARCMSR_ARC1214_DRV2IOP_DATA_OUT_READ		0x00000002
/*inbound message 0 पढ़ोy*/
#घोषणा ARCMSR_ARC1214_IOP2DRV_DATA_WRITE_OK		0x00000001
/*outbound DATA WRITE isr करोor bell clear*/
#घोषणा ARCMSR_ARC1214_IOP2DRV_DATA_READ_OK		0x00000002
/*outbound message 0 पढ़ोy*/
#घोषणा ARCMSR_ARC1214_IOP2DRV_MESSAGE_CMD_DONE		0x02000000
/*outbound message cmd isr करोor bell clear*/
/*ARCMSR_HBAMU_MESSAGE_FIRMWARE_OK*/
#घोषणा ARCMSR_ARC1214_MESSAGE_FIRMWARE_OK		0x80000000
#घोषणा ARCMSR_ARC1214_OUTBOUND_LIST_INTERRUPT_CLEAR	0x00000001
/*
*******************************************************************************
**                SPEC. क्रम Areca Type E adapter
*******************************************************************************
*/
#घोषणा ARCMSR_SIGNATURE_1884			0x188417D3

#घोषणा ARCMSR_HBEMU_DRV2IOP_DATA_WRITE_OK	0x00000002
#घोषणा ARCMSR_HBEMU_DRV2IOP_DATA_READ_OK	0x00000004
#घोषणा ARCMSR_HBEMU_DRV2IOP_MESSAGE_CMD_DONE	0x00000008

#घोषणा ARCMSR_HBEMU_IOP2DRV_DATA_WRITE_OK	0x00000002
#घोषणा ARCMSR_HBEMU_IOP2DRV_DATA_READ_OK	0x00000004
#घोषणा ARCMSR_HBEMU_IOP2DRV_MESSAGE_CMD_DONE	0x00000008

#घोषणा ARCMSR_HBEMU_MESSAGE_FIRMWARE_OK	0x80000000

#घोषणा ARCMSR_HBEMU_OUTBOUND_DOORBELL_ISR	0x00000001
#घोषणा ARCMSR_HBEMU_OUTBOUND_POSTQUEUE_ISR	0x00000008
#घोषणा ARCMSR_HBEMU_ALL_INTMASKENABLE		0x00000009

/* ARC-1884 करोorbell sync */
#घोषणा ARCMSR_HBEMU_DOORBELL_SYNC		0x100
#घोषणा ARCMSR_ARC188X_RESET_ADAPTER		0x00000004
#घोषणा ARCMSR_ARC1884_DiagWrite_ENABLE		0x00000080

/*
*******************************************************************************
**                SPEC. क्रम Areca Type F adapter
*******************************************************************************
*/
#घोषणा ARCMSR_SIGNATURE_1886			0x188617D3
// Doorbell and पूर्णांकerrupt definition are same as Type E adapter
/* ARC-1886 करोorbell sync */
#घोषणा ARCMSR_HBFMU_DOORBELL_SYNC		0x100
//set host rw buffer physical address at inbound message 0, 1 (low,high)
#घोषणा ARCMSR_HBFMU_DOORBELL_SYNC1		0x300
#घोषणा ARCMSR_HBFMU_MESSAGE_FIRMWARE_OK	0x80000000
#घोषणा ARCMSR_HBFMU_MESSAGE_NO_VOLUME_CHANGE	0x20000000

/*
*******************************************************************************
**    ARECA SCSI COMMAND DESCRIPTOR BLOCK size 0x1F8 (504)
*******************************************************************************
*/
काष्ठा ARCMSR_CDB
अणु
	uपूर्णांक8_t		Bus;
	uपूर्णांक8_t		TargetID;
	uपूर्णांक8_t		LUN;
	uपूर्णांक8_t		Function;
	uपूर्णांक8_t		CdbLength;
	uपूर्णांक8_t		sgcount;
	uपूर्णांक8_t		Flags;
#घोषणा ARCMSR_CDB_FLAG_SGL_BSIZE          0x01
#घोषणा ARCMSR_CDB_FLAG_BIOS               0x02
#घोषणा ARCMSR_CDB_FLAG_WRITE              0x04
#घोषणा ARCMSR_CDB_FLAG_SIMPLEQ            0x00
#घोषणा ARCMSR_CDB_FLAG_HEADQ              0x08
#घोषणा ARCMSR_CDB_FLAG_ORDEREDQ           0x10

	uपूर्णांक8_t		msgPages;
	uपूर्णांक32_t	msgContext;
	uपूर्णांक32_t	DataLength;
	uपूर्णांक8_t		Cdb[16];
	uपूर्णांक8_t		DeviceStatus;
#घोषणा ARCMSR_DEV_CHECK_CONDITION	    0x02
#घोषणा ARCMSR_DEV_SELECT_TIMEOUT	    0xF0
#घोषणा ARCMSR_DEV_ABORTED		    0xF1
#घोषणा ARCMSR_DEV_INIT_FAIL		    0xF2

	uपूर्णांक8_t		SenseData[15];
	जोड़
	अणु
		काष्ठा SG32ENTRY	sg32entry[1];
		काष्ठा SG64ENTRY	sg64entry[1];
	पूर्ण u;
पूर्ण;
/*
*******************************************************************************
**     Messaging Unit (MU) of the Intel R 80331 I/O processor(Type A) and Type B processor
*******************************************************************************
*/
काष्ठा MessageUnit_A
अणु
	uपूर्णांक32_t	resrved0[4];			/*0000 000F*/
	uपूर्णांक32_t	inbound_msgaddr0;		/*0010 0013*/
	uपूर्णांक32_t	inbound_msgaddr1;		/*0014 0017*/
	uपूर्णांक32_t	outbound_msgaddr0;		/*0018 001B*/
	uपूर्णांक32_t	outbound_msgaddr1;		/*001C 001F*/
	uपूर्णांक32_t	inbound_करोorbell;		/*0020 0023*/
	uपूर्णांक32_t	inbound_पूर्णांकstatus;		/*0024 0027*/
	uपूर्णांक32_t	inbound_पूर्णांकmask;		/*0028 002B*/
	uपूर्णांक32_t	outbound_करोorbell;		/*002C 002F*/
	uपूर्णांक32_t	outbound_पूर्णांकstatus;		/*0030 0033*/
	uपूर्णांक32_t	outbound_पूर्णांकmask;		/*0034 0037*/
	uपूर्णांक32_t	reserved1[2];			/*0038 003F*/
	uपूर्णांक32_t	inbound_queueport;		/*0040 0043*/
	uपूर्णांक32_t	outbound_queueport;     	/*0044 0047*/
	uपूर्णांक32_t	reserved2[2];			/*0048 004F*/
	uपूर्णांक32_t	reserved3[492];			/*0050 07FF 492*/
	uपूर्णांक32_t	reserved4[128];			/*0800 09FF 128*/
	uपूर्णांक32_t	message_rwbuffer[256];		/*0a00 0DFF 256*/
	uपूर्णांक32_t	message_wbuffer[32];		/*0E00 0E7F  32*/
	uपूर्णांक32_t	reserved5[32];			/*0E80 0EFF  32*/
	uपूर्णांक32_t	message_rbuffer[32];		/*0F00 0F7F  32*/
	uपूर्णांक32_t	reserved6[32];			/*0F80 0FFF  32*/
पूर्ण;

काष्ठा MessageUnit_B
अणु
	uपूर्णांक32_t	post_qbuffer[ARCMSR_MAX_HBB_POSTQUEUE];
	uपूर्णांक32_t	करोne_qbuffer[ARCMSR_MAX_HBB_POSTQUEUE];
	uपूर्णांक32_t	postq_index;
	uपूर्णांक32_t	करोneq_index;
	uपूर्णांक32_t	__iomem *drv2iop_करोorbell;
	uपूर्णांक32_t	__iomem *drv2iop_करोorbell_mask;
	uपूर्णांक32_t	__iomem *iop2drv_करोorbell;
	uपूर्णांक32_t	__iomem *iop2drv_करोorbell_mask;
	uपूर्णांक32_t	__iomem *message_rwbuffer;
	uपूर्णांक32_t	__iomem *message_wbuffer;
	uपूर्णांक32_t	__iomem *message_rbuffer;
पूर्ण;
/*
*********************************************************************
** LSI
*********************************************************************
*/
काष्ठा MessageUnit_Cअणु
	uपूर्णांक32_t	message_unit_status;			/*0000 0003*/
	uपूर्णांक32_t	slave_error_attribute;			/*0004 0007*/
	uपूर्णांक32_t	slave_error_address;			/*0008 000B*/
	uपूर्णांक32_t	posted_outbound_करोorbell;		/*000C 000F*/
	uपूर्णांक32_t	master_error_attribute;			/*0010 0013*/
	uपूर्णांक32_t	master_error_address_low;		/*0014 0017*/
	uपूर्णांक32_t	master_error_address_high;		/*0018 001B*/
	uपूर्णांक32_t	hcb_size;				/*001C 001F*/
	uपूर्णांक32_t	inbound_करोorbell;			/*0020 0023*/
	uपूर्णांक32_t	diagnostic_rw_data;			/*0024 0027*/
	uपूर्णांक32_t	diagnostic_rw_address_low;		/*0028 002B*/
	uपूर्णांक32_t	diagnostic_rw_address_high;		/*002C 002F*/
	uपूर्णांक32_t	host_पूर्णांक_status;			/*0030 0033*/
	uपूर्णांक32_t	host_पूर्णांक_mask;				/*0034 0037*/
	uपूर्णांक32_t	dcr_data;				/*0038 003B*/
	uपूर्णांक32_t	dcr_address;				/*003C 003F*/
	uपूर्णांक32_t	inbound_queueport;			/*0040 0043*/
	uपूर्णांक32_t	outbound_queueport;			/*0044 0047*/
	uपूर्णांक32_t	hcb_pci_address_low;			/*0048 004B*/
	uपूर्णांक32_t	hcb_pci_address_high;			/*004C 004F*/
	uपूर्णांक32_t	iop_पूर्णांक_status;				/*0050 0053*/
	uपूर्णांक32_t	iop_पूर्णांक_mask;				/*0054 0057*/
	uपूर्णांक32_t	iop_inbound_queue_port;			/*0058 005B*/
	uपूर्णांक32_t	iop_outbound_queue_port;		/*005C 005F*/
	uपूर्णांक32_t	inbound_मुक्त_list_index;		/*0060 0063*/
	uपूर्णांक32_t	inbound_post_list_index;		/*0064 0067*/
	uपूर्णांक32_t	outbound_मुक्त_list_index;		/*0068 006B*/
	uपूर्णांक32_t	outbound_post_list_index;		/*006C 006F*/
	uपूर्णांक32_t	inbound_करोorbell_clear;			/*0070 0073*/
	uपूर्णांक32_t	i2o_message_unit_control;		/*0074 0077*/
	uपूर्णांक32_t	last_used_message_source_address_low;	/*0078 007B*/
	uपूर्णांक32_t	last_used_message_source_address_high;	/*007C 007F*/
	uपूर्णांक32_t	pull_mode_data_byte_count[4];		/*0080 008F*/
	uपूर्णांक32_t	message_dest_address_index;		/*0090 0093*/
	uपूर्णांक32_t	करोne_queue_not_empty_पूर्णांक_counter_समयr;	/*0094 0097*/
	uपूर्णांक32_t	utility_A_पूर्णांक_counter_समयr;		/*0098 009B*/
	uपूर्णांक32_t	outbound_करोorbell;			/*009C 009F*/
	uपूर्णांक32_t	outbound_करोorbell_clear;		/*00A0 00A3*/
	uपूर्णांक32_t	message_source_address_index;		/*00A4 00A7*/
	uपूर्णांक32_t	message_करोne_queue_index;		/*00A8 00AB*/
	uपूर्णांक32_t	reserved0;				/*00AC 00AF*/
	uपूर्णांक32_t	inbound_msgaddr0;			/*00B0 00B3*/
	uपूर्णांक32_t	inbound_msgaddr1;			/*00B4 00B7*/
	uपूर्णांक32_t	outbound_msgaddr0;			/*00B8 00BB*/
	uपूर्णांक32_t	outbound_msgaddr1;			/*00BC 00BF*/
	uपूर्णांक32_t	inbound_queueport_low;			/*00C0 00C3*/
	uपूर्णांक32_t	inbound_queueport_high;			/*00C4 00C7*/
	uपूर्णांक32_t	outbound_queueport_low;			/*00C8 00CB*/
	uपूर्णांक32_t	outbound_queueport_high;		/*00CC 00CF*/
	uपूर्णांक32_t	iop_inbound_queue_port_low;		/*00D0 00D3*/
	uपूर्णांक32_t	iop_inbound_queue_port_high;		/*00D4 00D7*/
	uपूर्णांक32_t	iop_outbound_queue_port_low;		/*00D8 00DB*/
	uपूर्णांक32_t	iop_outbound_queue_port_high;		/*00DC 00DF*/
	uपूर्णांक32_t	message_dest_queue_port_low;		/*00E0 00E3*/
	uपूर्णांक32_t	message_dest_queue_port_high;		/*00E4 00E7*/
	uपूर्णांक32_t	last_used_message_dest_address_low;	/*00E8 00EB*/
	uपूर्णांक32_t	last_used_message_dest_address_high;	/*00EC 00EF*/
	uपूर्णांक32_t	message_करोne_queue_base_address_low;	/*00F0 00F3*/
	uपूर्णांक32_t	message_करोne_queue_base_address_high;	/*00F4 00F7*/
	uपूर्णांक32_t	host_diagnostic;			/*00F8 00FB*/
	uपूर्णांक32_t	ग_लिखो_sequence;				/*00FC 00FF*/
	uपूर्णांक32_t	reserved1[34];				/*0100 0187*/
	uपूर्णांक32_t	reserved2[1950];			/*0188 1FFF*/
	uपूर्णांक32_t	message_wbuffer[32];			/*2000 207F*/
	uपूर्णांक32_t	reserved3[32];				/*2080 20FF*/
	uपूर्णांक32_t	message_rbuffer[32];			/*2100 217F*/
	uपूर्णांक32_t	reserved4[32];				/*2180 21FF*/
	uपूर्णांक32_t	msgcode_rwbuffer[256];			/*2200 23FF*/
पूर्ण;
/*
*********************************************************************
**     Messaging Unit (MU) of Type D processor
*********************************************************************
*/
काष्ठा InBound_SRB अणु
	uपूर्णांक32_t addressLow; /* poपूर्णांकer to SRB block */
	uपूर्णांक32_t addressHigh;
	uपूर्णांक32_t length; /* in DWORDs */
	uपूर्णांक32_t reserved0;
पूर्ण;

काष्ठा OutBound_SRB अणु
	uपूर्णांक32_t addressLow; /* poपूर्णांकer to SRB block */
	uपूर्णांक32_t addressHigh;
पूर्ण;

काष्ठा MessageUnit_D अणु
	काष्ठा InBound_SRB	post_qbuffer[ARCMSR_MAX_ARC1214_POSTQUEUE];
	अस्थिर काष्ठा OutBound_SRB
				करोne_qbuffer[ARCMSR_MAX_ARC1214_DONEQUEUE];
	u16 postq_index;
	अस्थिर u16 करोneq_index;
	u32 __iomem *chip_id;			/* 0x00004 */
	u32 __iomem *cpu_mem_config;		/* 0x00008 */
	u32 __iomem *i2o_host_पूर्णांकerrupt_mask;	/* 0x00034 */
	u32 __iomem *sample_at_reset;		/* 0x00100 */
	u32 __iomem *reset_request;		/* 0x00108 */
	u32 __iomem *host_पूर्णांक_status;		/* 0x00200 */
	u32 __iomem *pcief0_पूर्णांक_enable;		/* 0x0020C */
	u32 __iomem *inbound_msgaddr0;		/* 0x00400 */
	u32 __iomem *inbound_msgaddr1;		/* 0x00404 */
	u32 __iomem *outbound_msgaddr0;		/* 0x00420 */
	u32 __iomem *outbound_msgaddr1;		/* 0x00424 */
	u32 __iomem *inbound_करोorbell;		/* 0x00460 */
	u32 __iomem *outbound_करोorbell;		/* 0x00480 */
	u32 __iomem *outbound_करोorbell_enable;	/* 0x00484 */
	u32 __iomem *inboundlist_base_low;	/* 0x01000 */
	u32 __iomem *inboundlist_base_high;	/* 0x01004 */
	u32 __iomem *inboundlist_ग_लिखो_poपूर्णांकer;	/* 0x01018 */
	u32 __iomem *outboundlist_base_low;	/* 0x01060 */
	u32 __iomem *outboundlist_base_high;	/* 0x01064 */
	u32 __iomem *outboundlist_copy_poपूर्णांकer;	/* 0x0106C */
	u32 __iomem *outboundlist_पढ़ो_poपूर्णांकer;	/* 0x01070 0x01072 */
	u32 __iomem *outboundlist_पूर्णांकerrupt_cause;	/* 0x1088 */
	u32 __iomem *outboundlist_पूर्णांकerrupt_enable;	/* 0x108C */
	u32 __iomem *message_wbuffer;		/* 0x2000 */
	u32 __iomem *message_rbuffer;		/* 0x2100 */
	u32 __iomem *msgcode_rwbuffer;		/* 0x2200 */
पूर्ण;
/*
*********************************************************************
**     Messaging Unit (MU) of Type E processor(LSI)
*********************************************************************
*/
काष्ठा MessageUnit_Eअणु
	uपूर्णांक32_t	iobound_करोorbell;			/*0000 0003*/
	uपूर्णांक32_t	ग_लिखो_sequence_3xxx;			/*0004 0007*/
	uपूर्णांक32_t	host_diagnostic_3xxx;			/*0008 000B*/
	uपूर्णांक32_t	posted_outbound_करोorbell;		/*000C 000F*/
	uपूर्णांक32_t	master_error_attribute;			/*0010 0013*/
	uपूर्णांक32_t	master_error_address_low;		/*0014 0017*/
	uपूर्णांक32_t	master_error_address_high;		/*0018 001B*/
	uपूर्णांक32_t	hcb_size;				/*001C 001F*/
	uपूर्णांक32_t	inbound_करोorbell;			/*0020 0023*/
	uपूर्णांक32_t	diagnostic_rw_data;			/*0024 0027*/
	uपूर्णांक32_t	diagnostic_rw_address_low;		/*0028 002B*/
	uपूर्णांक32_t	diagnostic_rw_address_high;		/*002C 002F*/
	uपूर्णांक32_t	host_पूर्णांक_status;			/*0030 0033*/
	uपूर्णांक32_t	host_पूर्णांक_mask;				/*0034 0037*/
	uपूर्णांक32_t	dcr_data;				/*0038 003B*/
	uपूर्णांक32_t	dcr_address;				/*003C 003F*/
	uपूर्णांक32_t	inbound_queueport;			/*0040 0043*/
	uपूर्णांक32_t	outbound_queueport;			/*0044 0047*/
	uपूर्णांक32_t	hcb_pci_address_low;			/*0048 004B*/
	uपूर्णांक32_t	hcb_pci_address_high;			/*004C 004F*/
	uपूर्णांक32_t	iop_पूर्णांक_status;				/*0050 0053*/
	uपूर्णांक32_t	iop_पूर्णांक_mask;				/*0054 0057*/
	uपूर्णांक32_t	iop_inbound_queue_port;			/*0058 005B*/
	uपूर्णांक32_t	iop_outbound_queue_port;		/*005C 005F*/
	uपूर्णांक32_t	inbound_मुक्त_list_index;		/*0060 0063*/
	uपूर्णांक32_t	inbound_post_list_index;		/*0064 0067*/
	uपूर्णांक32_t	reply_post_producer_index;		/*0068 006B*/
	uपूर्णांक32_t	reply_post_consumer_index;		/*006C 006F*/
	uपूर्णांक32_t	inbound_करोorbell_clear;			/*0070 0073*/
	uपूर्णांक32_t	i2o_message_unit_control;		/*0074 0077*/
	uपूर्णांक32_t	last_used_message_source_address_low;	/*0078 007B*/
	uपूर्णांक32_t	last_used_message_source_address_high;	/*007C 007F*/
	uपूर्णांक32_t	pull_mode_data_byte_count[4];		/*0080 008F*/
	uपूर्णांक32_t	message_dest_address_index;		/*0090 0093*/
	uपूर्णांक32_t	करोne_queue_not_empty_पूर्णांक_counter_समयr;	/*0094 0097*/
	uपूर्णांक32_t	utility_A_पूर्णांक_counter_समयr;		/*0098 009B*/
	uपूर्णांक32_t	outbound_करोorbell;			/*009C 009F*/
	uपूर्णांक32_t	outbound_करोorbell_clear;		/*00A0 00A3*/
	uपूर्णांक32_t	message_source_address_index;		/*00A4 00A7*/
	uपूर्णांक32_t	message_करोne_queue_index;		/*00A8 00AB*/
	uपूर्णांक32_t	reserved0;				/*00AC 00AF*/
	uपूर्णांक32_t	inbound_msgaddr0;			/*00B0 00B3*/
	uपूर्णांक32_t	inbound_msgaddr1;			/*00B4 00B7*/
	uपूर्णांक32_t	outbound_msgaddr0;			/*00B8 00BB*/
	uपूर्णांक32_t	outbound_msgaddr1;			/*00BC 00BF*/
	uपूर्णांक32_t	inbound_queueport_low;			/*00C0 00C3*/
	uपूर्णांक32_t	inbound_queueport_high;			/*00C4 00C7*/
	uपूर्णांक32_t	outbound_queueport_low;			/*00C8 00CB*/
	uपूर्णांक32_t	outbound_queueport_high;		/*00CC 00CF*/
	uपूर्णांक32_t	iop_inbound_queue_port_low;		/*00D0 00D3*/
	uपूर्णांक32_t	iop_inbound_queue_port_high;		/*00D4 00D7*/
	uपूर्णांक32_t	iop_outbound_queue_port_low;		/*00D8 00DB*/
	uपूर्णांक32_t	iop_outbound_queue_port_high;		/*00DC 00DF*/
	uपूर्णांक32_t	message_dest_queue_port_low;		/*00E0 00E3*/
	uपूर्णांक32_t	message_dest_queue_port_high;		/*00E4 00E7*/
	uपूर्णांक32_t	last_used_message_dest_address_low;	/*00E8 00EB*/
	uपूर्णांक32_t	last_used_message_dest_address_high;	/*00EC 00EF*/
	uपूर्णांक32_t	message_करोne_queue_base_address_low;	/*00F0 00F3*/
	uपूर्णांक32_t	message_करोne_queue_base_address_high;	/*00F4 00F7*/
	uपूर्णांक32_t	host_diagnostic;			/*00F8 00FB*/
	uपूर्णांक32_t	ग_लिखो_sequence;				/*00FC 00FF*/
	uपूर्णांक32_t	reserved1[34];				/*0100 0187*/
	uपूर्णांक32_t	reserved2[1950];			/*0188 1FFF*/
	uपूर्णांक32_t	message_wbuffer[32];			/*2000 207F*/
	uपूर्णांक32_t	reserved3[32];				/*2080 20FF*/
	uपूर्णांक32_t	message_rbuffer[32];			/*2100 217F*/
	uपूर्णांक32_t	reserved4[32];				/*2180 21FF*/
	uपूर्णांक32_t	msgcode_rwbuffer[256];			/*2200 23FF*/
पूर्ण;

/*
*********************************************************************
**     Messaging Unit (MU) of Type F processor(LSI)
*********************************************************************
*/
काष्ठा MessageUnit_F अणु
	uपूर्णांक32_t	iobound_करोorbell;			/*0000 0003*/
	uपूर्णांक32_t	ग_लिखो_sequence_3xxx;			/*0004 0007*/
	uपूर्णांक32_t	host_diagnostic_3xxx;			/*0008 000B*/
	uपूर्णांक32_t	posted_outbound_करोorbell;		/*000C 000F*/
	uपूर्णांक32_t	master_error_attribute;			/*0010 0013*/
	uपूर्णांक32_t	master_error_address_low;		/*0014 0017*/
	uपूर्णांक32_t	master_error_address_high;		/*0018 001B*/
	uपूर्णांक32_t	hcb_size;				/*001C 001F*/
	uपूर्णांक32_t	inbound_करोorbell;			/*0020 0023*/
	uपूर्णांक32_t	diagnostic_rw_data;			/*0024 0027*/
	uपूर्णांक32_t	diagnostic_rw_address_low;		/*0028 002B*/
	uपूर्णांक32_t	diagnostic_rw_address_high;		/*002C 002F*/
	uपूर्णांक32_t	host_पूर्णांक_status;			/*0030 0033*/
	uपूर्णांक32_t	host_पूर्णांक_mask;				/*0034 0037*/
	uपूर्णांक32_t	dcr_data;				/*0038 003B*/
	uपूर्णांक32_t	dcr_address;				/*003C 003F*/
	uपूर्णांक32_t	inbound_queueport;			/*0040 0043*/
	uपूर्णांक32_t	outbound_queueport;			/*0044 0047*/
	uपूर्णांक32_t	hcb_pci_address_low;			/*0048 004B*/
	uपूर्णांक32_t	hcb_pci_address_high;			/*004C 004F*/
	uपूर्णांक32_t	iop_पूर्णांक_status;				/*0050 0053*/
	uपूर्णांक32_t	iop_पूर्णांक_mask;				/*0054 0057*/
	uपूर्णांक32_t	iop_inbound_queue_port;			/*0058 005B*/
	uपूर्णांक32_t	iop_outbound_queue_port;		/*005C 005F*/
	uपूर्णांक32_t	inbound_मुक्त_list_index;		/*0060 0063*/
	uपूर्णांक32_t	inbound_post_list_index;		/*0064 0067*/
	uपूर्णांक32_t	reply_post_producer_index;		/*0068 006B*/
	uपूर्णांक32_t	reply_post_consumer_index;		/*006C 006F*/
	uपूर्णांक32_t	inbound_करोorbell_clear;			/*0070 0073*/
	uपूर्णांक32_t	i2o_message_unit_control;		/*0074 0077*/
	uपूर्णांक32_t	last_used_message_source_address_low;	/*0078 007B*/
	uपूर्णांक32_t	last_used_message_source_address_high;	/*007C 007F*/
	uपूर्णांक32_t	pull_mode_data_byte_count[4];		/*0080 008F*/
	uपूर्णांक32_t	message_dest_address_index;		/*0090 0093*/
	uपूर्णांक32_t	करोne_queue_not_empty_पूर्णांक_counter_समयr;	/*0094 0097*/
	uपूर्णांक32_t	utility_A_पूर्णांक_counter_समयr;		/*0098 009B*/
	uपूर्णांक32_t	outbound_करोorbell;			/*009C 009F*/
	uपूर्णांक32_t	outbound_करोorbell_clear;		/*00A0 00A3*/
	uपूर्णांक32_t	message_source_address_index;		/*00A4 00A7*/
	uपूर्णांक32_t	message_करोne_queue_index;		/*00A8 00AB*/
	uपूर्णांक32_t	reserved0;				/*00AC 00AF*/
	uपूर्णांक32_t	inbound_msgaddr0;			/*00B0 00B3*/
	uपूर्णांक32_t	inbound_msgaddr1;			/*00B4 00B7*/
	uपूर्णांक32_t	outbound_msgaddr0;			/*00B8 00BB*/
	uपूर्णांक32_t	outbound_msgaddr1;			/*00BC 00BF*/
	uपूर्णांक32_t	inbound_queueport_low;			/*00C0 00C3*/
	uपूर्णांक32_t	inbound_queueport_high;			/*00C4 00C7*/
	uपूर्णांक32_t	outbound_queueport_low;			/*00C8 00CB*/
	uपूर्णांक32_t	outbound_queueport_high;		/*00CC 00CF*/
	uपूर्णांक32_t	iop_inbound_queue_port_low;		/*00D0 00D3*/
	uपूर्णांक32_t	iop_inbound_queue_port_high;		/*00D4 00D7*/
	uपूर्णांक32_t	iop_outbound_queue_port_low;		/*00D8 00DB*/
	uपूर्णांक32_t	iop_outbound_queue_port_high;		/*00DC 00DF*/
	uपूर्णांक32_t	message_dest_queue_port_low;		/*00E0 00E3*/
	uपूर्णांक32_t	message_dest_queue_port_high;		/*00E4 00E7*/
	uपूर्णांक32_t	last_used_message_dest_address_low;	/*00E8 00EB*/
	uपूर्णांक32_t	last_used_message_dest_address_high;	/*00EC 00EF*/
	uपूर्णांक32_t	message_करोne_queue_base_address_low;	/*00F0 00F3*/
	uपूर्णांक32_t	message_करोne_queue_base_address_high;	/*00F4 00F7*/
	uपूर्णांक32_t	host_diagnostic;			/*00F8 00FB*/
	uपूर्णांक32_t	ग_लिखो_sequence;				/*00FC 00FF*/
	uपूर्णांक32_t	reserved1[46];				/*0100 01B7*/
	uपूर्णांक32_t	reply_post_producer_index1;		/*01B8 01BB*/
	uपूर्णांक32_t	reply_post_consumer_index1;		/*01BC 01BF*/
पूर्ण;

#घोषणा	MESG_RW_BUFFER_SIZE	(256 * 3)

प्रकार काष्ठा deliver_completeQ अणु
	uपूर्णांक16_t	cmdFlag;
	uपूर्णांक16_t	cmdSMID;
	uपूर्णांक16_t	cmdLMID;        // reserved (0)
	uपूर्णांक16_t	cmdFlag2;       // reserved (0)
पूर्ण DeliverQ, CompletionQ, *pDeliver_Q, *pCompletion_Q;
/*
*******************************************************************************
**                 Adapter Control Block
*******************************************************************************
*/
काष्ठा AdapterControlBlock
अणु
	uपूर्णांक32_t		adapter_type;		/* adapter A,B..... */
#घोषणा ACB_ADAPTER_TYPE_A		0x00000000	/* hba I IOP */
#घोषणा ACB_ADAPTER_TYPE_B		0x00000001	/* hbb M IOP */
#घोषणा ACB_ADAPTER_TYPE_C		0x00000002	/* hbc L IOP */
#घोषणा ACB_ADAPTER_TYPE_D		0x00000003	/* hbd M IOP */
#घोषणा ACB_ADAPTER_TYPE_E		0x00000004	/* hba L IOP */
#घोषणा ACB_ADAPTER_TYPE_F		0x00000005	/* hba L IOP */
	u32			ioqueue_size;
	काष्ठा pci_dev *	pdev;
	काष्ठा Scsi_Host *	host;
	अचिन्हित दीर्घ		vir2phy_offset;
	/* Offset is used in making arc cdb physical to भव calculations */
	uपूर्णांक32_t		outbound_पूर्णांक_enable;
	uपूर्णांक32_t		cdb_phyaddr_hi32;
	uपूर्णांक32_t		reg_mu_acc_handle0;
	uपूर्णांक64_t		cdb_phyadd_hipart;
	spinlock_t		eh_lock;
	spinlock_t		ccblist_lock;
	spinlock_t		postq_lock;
	spinlock_t		करोneq_lock;
	spinlock_t		rqbuffer_lock;
	spinlock_t		wqbuffer_lock;
	जोड़ अणु
		काष्ठा MessageUnit_A __iomem *pmuA;
		काष्ठा MessageUnit_B 	*pmuB;
		काष्ठा MessageUnit_C __iomem *pmuC;
		काष्ठा MessageUnit_D 	*pmuD;
		काष्ठा MessageUnit_E __iomem *pmuE;
		काष्ठा MessageUnit_F __iomem *pmuF;
	पूर्ण;
	/* message unit ATU inbound base address0 */
	व्योम __iomem		*mem_base0;
	व्योम __iomem		*mem_base1;
	//0x000 - COMPORT_IN  (Host sent to ROC)
	uपूर्णांक32_t		*message_wbuffer;
	//0x100 - COMPORT_OUT (ROC sent to Host)
	uपूर्णांक32_t		*message_rbuffer;
	uपूर्णांक32_t		*msgcode_rwbuffer;	//0x200 - BIOS_AREA
	uपूर्णांक32_t		acb_flags;
	u16			dev_id;
	uपूर्णांक8_t			adapter_index;
#घोषणा ACB_F_SCSISTOPADAPTER         	0x0001
#घोषणा ACB_F_MSG_STOP_BGRB     	0x0002
/* stop RAID background rebuild */
#घोषणा ACB_F_MSG_START_BGRB          	0x0004
/* stop RAID background rebuild */
#घोषणा ACB_F_IOPDATA_OVERFLOW        	0x0008
/* iop message data rqbuffer overflow */
#घोषणा ACB_F_MESSAGE_WQBUFFER_CLEARED	0x0010
/* message clear wqbuffer */
#घोषणा ACB_F_MESSAGE_RQBUFFER_CLEARED  0x0020
/* message clear rqbuffer */
#घोषणा ACB_F_MESSAGE_WQBUFFER_READED   0x0040
#घोषणा ACB_F_BUS_RESET               	0x0080

#घोषणा ACB_F_IOP_INITED              	0x0100
/* iop init */
#घोषणा ACB_F_ABORT			0x0200
#घोषणा ACB_F_FIRMWARE_TRAP           	0x0400
#घोषणा ACB_F_ADAPTER_REMOVED		0x0800
#घोषणा ACB_F_MSG_GET_CONFIG		0x1000
	काष्ठा CommandControlBlock *	pccb_pool[ARCMSR_MAX_FREECCB_NUM];
	/* used क्रम memory मुक्त */
	काष्ठा list_head	ccb_मुक्त_list;
	/* head of मुक्त ccb list */

	atomic_t		ccboutstandingcount;
	/*The present outstanding command number that in the IOP that
					रुकोing क्रम being handled by FW*/

	व्योम *			dma_coherent;
	/* dma_coherent used क्रम memory मुक्त */
	dma_addr_t		dma_coherent_handle;
	/* dma_coherent_handle used क्रम memory मुक्त */
	dma_addr_t		dma_coherent_handle2;
	व्योम			*dma_coherent2;
	अचिन्हित पूर्णांक		uncache_size;
	uपूर्णांक8_t			rqbuffer[ARCMSR_MAX_QBUFFER];
	/* data collection buffer क्रम पढ़ो from 80331 */
	पूर्णांक32_t			rqbuf_getIndex;
	/* first of पढ़ो buffer  */
	पूर्णांक32_t			rqbuf_putIndex;
	/* last of पढ़ो buffer   */
	uपूर्णांक8_t			wqbuffer[ARCMSR_MAX_QBUFFER];
	/* data collection buffer क्रम ग_लिखो to 80331  */
	पूर्णांक32_t			wqbuf_getIndex;
	/* first of ग_लिखो buffer */
	पूर्णांक32_t			wqbuf_putIndex;
	/* last of ग_लिखो buffer  */
	uपूर्णांक8_t			devstate[ARCMSR_MAX_TARGETID][ARCMSR_MAX_TARGETLUN];
	/* id0 ..... id15, lun0...lun7 */
#घोषणा ARECA_RAID_GONE			0x55
#घोषणा ARECA_RAID_GOOD			0xaa
	uपूर्णांक32_t		num_resets;
	uपूर्णांक32_t		num_पातs;
	uपूर्णांक32_t		signature;
	uपूर्णांक32_t		firm_request_len;
	uपूर्णांक32_t		firm_numbers_queue;
	uपूर्णांक32_t		firm_sdram_size;
	uपूर्णांक32_t		firm_hd_channels;
	uपूर्णांक32_t		firm_cfg_version;
	अक्षर			firm_model[12];
	अक्षर			firm_version[20];
	अक्षर			device_map[20];			/*21,84-99*/
	काष्ठा work_काष्ठा 	arcmsr_करो_message_isr_bh;
	काष्ठा समयr_list	eternal_समयr;
	अचिन्हित लघु		fw_flag;
#घोषणा	FW_NORMAL			0x0000
#घोषणा	FW_BOG				0x0001
#घोषणा	FW_DEADLOCK			0x0010
	uपूर्णांक32_t		maxOutstanding;
	पूर्णांक			vector_count;
	uपूर्णांक32_t		maxFreeCCB;
	काष्ठा समयr_list	refresh_समयr;
	uपूर्णांक32_t		करोneq_index;
	uपूर्णांक32_t		ccbsize;
	uपूर्णांक32_t		in_करोorbell;
	uपूर्णांक32_t		out_करोorbell;
	uपूर्णांक32_t		completionQ_entry;
	pCompletion_Q		pCompletionQ;
	uपूर्णांक32_t		completeQ_size;
पूर्ण;/* HW_DEVICE_EXTENSION */
/*
*******************************************************************************
**                   Command Control Block
**             this CCB length must be 32 bytes boundary
*******************************************************************************
*/
काष्ठा CommandControlBlockअणु
	/*x32:माप काष्ठा_CCB=(64+60)byte, x64:माप काष्ठा_CCB=(64+60)byte*/
	काष्ठा list_head		list;		/*x32: 8byte, x64: 16byte*/
	काष्ठा scsi_cmnd		*pcmd;		/*8 bytes poपूर्णांकer of linux scsi command */
	काष्ठा AdapterControlBlock	*acb;		/*x32: 4byte, x64: 8byte*/
	अचिन्हित दीर्घ			cdb_phyaddr;	/*x32: 4byte, x64: 8byte*/
	uपूर्णांक32_t			arc_cdb_size;	/*x32:4byte,x64:4byte*/
	uपूर्णांक16_t			ccb_flags;	/*x32: 2byte, x64: 2byte*/
#घोषणा	CCB_FLAG_READ		0x0000
#घोषणा	CCB_FLAG_WRITE		0x0001
#घोषणा	CCB_FLAG_ERROR		0x0002
#घोषणा	CCB_FLAG_FLUSHCACHE	0x0004
#घोषणा	CCB_FLAG_MASTER_ABORTED	0x0008
	uपूर्णांक16_t                        startकरोne;	/*x32:2byte,x32:2byte*/
#घोषणा	ARCMSR_CCB_DONE		0x0000
#घोषणा	ARCMSR_CCB_START	0x55AA
#घोषणा	ARCMSR_CCB_ABORTED	0xAA55
#घोषणा	ARCMSR_CCB_ILLEGAL	0xFFFF
	uपूर्णांक32_t			smid;
#अगर BITS_PER_LONG == 64
	/*  ======================512+64 bytes========================  */
		uपूर्णांक32_t		reserved[3];	/*12 byte*/
#अन्यथा
	/*  ======================512+32 bytes========================  */
		uपूर्णांक32_t		reserved[8];	/*32  byte*/
#पूर्ण_अगर
	/*  =======================================================   */
	काष्ठा ARCMSR_CDB		arcmsr_cdb;
पूर्ण;
/*
*******************************************************************************
**    ARECA SCSI sense data
*******************************************************************************
*/
काष्ठा SENSE_DATA
अणु
	uपूर्णांक8_t				ErrorCode:7;
#घोषणा SCSI_SENSE_CURRENT_ERRORS	0x70
#घोषणा SCSI_SENSE_DEFERRED_ERRORS	0x71
	uपूर्णांक8_t				Valid:1;
	uपूर्णांक8_t				SegmentNumber;
	uपूर्णांक8_t				SenseKey:4;
	uपूर्णांक8_t				Reserved:1;
	uपूर्णांक8_t				IncorrectLength:1;
	uपूर्णांक8_t				EndOfMedia:1;
	uपूर्णांक8_t				FileMark:1;
	uपूर्णांक8_t				Inक्रमmation[4];
	uपूर्णांक8_t				AdditionalSenseLength;
	uपूर्णांक8_t				CommandSpecअगरicInक्रमmation[4];
	uपूर्णांक8_t				AdditionalSenseCode;
	uपूर्णांक8_t				AdditionalSenseCodeQualअगरier;
	uपूर्णांक8_t				FieldReplaceableUnitCode;
	uपूर्णांक8_t				SenseKeySpecअगरic[3];
पूर्ण;
/*
*******************************************************************************
**  Outbound Interrupt Status Register - OISR
*******************************************************************************
*/
#घोषणा	ARCMSR_MU_OUTBOUND_INTERRUPT_STATUS_REG	0x30
#घोषणा	ARCMSR_MU_OUTBOUND_PCI_INT		0x10
#घोषणा	ARCMSR_MU_OUTBOUND_POSTQUEUE_INT	0x08
#घोषणा	ARCMSR_MU_OUTBOUND_DOORBELL_INT		0x04
#घोषणा	ARCMSR_MU_OUTBOUND_MESSAGE1_INT		0x02
#घोषणा	ARCMSR_MU_OUTBOUND_MESSAGE0_INT		0x01
#घोषणा	ARCMSR_MU_OUTBOUND_HANDLE_INT                     \
                    (ARCMSR_MU_OUTBOUND_MESSAGE0_INT      \
                     |ARCMSR_MU_OUTBOUND_MESSAGE1_INT     \
                     |ARCMSR_MU_OUTBOUND_DOORBELL_INT     \
                     |ARCMSR_MU_OUTBOUND_POSTQUEUE_INT    \
                     |ARCMSR_MU_OUTBOUND_PCI_INT)
/*
*******************************************************************************
**  Outbound Interrupt Mask Register - OIMR
*******************************************************************************
*/
#घोषणा	ARCMSR_MU_OUTBOUND_INTERRUPT_MASK_REG		0x34
#घोषणा	ARCMSR_MU_OUTBOUND_PCI_INTMASKENABLE		0x10
#घोषणा	ARCMSR_MU_OUTBOUND_POSTQUEUE_INTMASKENABLE	0x08
#घोषणा	ARCMSR_MU_OUTBOUND_DOORBELL_INTMASKENABLE	0x04
#घोषणा	ARCMSR_MU_OUTBOUND_MESSAGE1_INTMASKENABLE	0x02
#घोषणा	ARCMSR_MU_OUTBOUND_MESSAGE0_INTMASKENABLE	0x01
#घोषणा	ARCMSR_MU_OUTBOUND_ALL_INTMASKENABLE		0x1F

बाह्य व्योम arcmsr_ग_लिखो_ioctldata2iop(काष्ठा AdapterControlBlock *);
बाह्य uपूर्णांक32_t arcmsr_Read_iop_rqbuffer_data(काष्ठा AdapterControlBlock *,
	काष्ठा QBUFFER __iomem *);
बाह्य व्योम arcmsr_clear_iop2drv_rqueue_buffer(काष्ठा AdapterControlBlock *);
बाह्य काष्ठा QBUFFER __iomem *arcmsr_get_iop_rqbuffer(काष्ठा AdapterControlBlock *);
बाह्य काष्ठा device_attribute *arcmsr_host_attrs[];
बाह्य पूर्णांक arcmsr_alloc_sysfs_attr(काष्ठा AdapterControlBlock *);
व्योम arcmsr_मुक्त_sysfs_attr(काष्ठा AdapterControlBlock *acb);
