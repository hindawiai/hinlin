<शैली गुरु>
/*
 * Copyright 2000-2020 Broadcom Inc. All rights reserved.
 *
 *
 *          Name:  mpi2_pci.h
 *         Title:  MPI PCIe Attached Devices काष्ठाures and definitions.
 * Creation Date:  October 9, 2012
 *
 * mpi2_pci.h Version:  02.00.04
 *
 * NOTE: Names (प्रकारs, defines, etc.) beginning with an MPI25 or Mpi25
 *       prefix are क्रम use only on MPI v2.5 products, and must not be used
 *       with MPI v2.0 products. Unless otherwise noted, names beginning with
 *       MPI2 or Mpi2 are क्रम use with both MPI v2.0 and MPI v2.5 products.
 *
 * Version History
 * ---------------
 *
 * Date      Version   Description
 * --------  --------  ------------------------------------------------------
 * 03-16-15  02.00.00  Initial version.
 * 02-17-16  02.00.01  Removed AHCI support.
 *                     Removed SOP support.
 * 07-01-16  02.00.02  Added MPI26_NVME_FLAGS_FORCE_ADMIN_ERR_RESP to
 *                     NVME Encapsulated Request.
 * 07-22-18  02.00.03  Updted flags field क्रम NVME Encapsulated req
 * 12-17-18  02.00.04  Added MPI26_PCIE_DEVINFO_SCSI
 *			Shortten some defines to be compatible with DOS
 * --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI2_PCI_H
#घोषणा MPI2_PCI_H


/*
 *Values क्रम the PCIe DeviceInfo field used in PCIe Device Status Change Event
 *data and PCIe Configuration pages.
 */
#घोषणा MPI26_PCIE_DEVINFO_सूचीECT_ATTACH        (0x00000010)

#घोषणा MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE     (0x0000000F)
#घोषणा MPI26_PCIE_DEVINFO_NO_DEVICE            (0x00000000)
#घोषणा MPI26_PCIE_DEVINFO_PCI_SWITCH           (0x00000001)
#घोषणा MPI26_PCIE_DEVINFO_NVME                 (0x00000003)
#घोषणा MPI26_PCIE_DEVINFO_SCSI                 (0x00000004)

/****************************************************************************
*  NVMe Encapsulated message
****************************************************************************/

/*NVME Encapsulated Request Message */
प्रकार काष्ठा _MPI26_NVME_ENCAPSULATED_REQUEST अणु
	U16	DevHandle;                      /*0x00 */
	U8	ChainOffset;                    /*0x02 */
	U8	Function;                       /*0x03 */
	U16	EncapsulatedCommandLength;      /*0x04 */
	U8	Reserved1;                      /*0x06 */
	U8	MsgFlags;                       /*0x07 */
	U8	VP_ID;                          /*0x08 */
	U8	VF_ID;                          /*0x09 */
	U16	Reserved2;                      /*0x0A */
	U32	Reserved3;                      /*0x0C */
	U64	ErrorResponseBaseAddress;       /*0x10 */
	U16	ErrorResponseAllocationLength;  /*0x18 */
	U16	Flags;                          /*0x1A */
	U32	DataLength;                     /*0x1C */
	U8	NVMe_Command[4];                /*0x20 */

पूर्ण MPI26_NVME_ENCAPSULATED_REQUEST, *PTR_MPI26_NVME_ENCAPSULATED_REQUEST,
	Mpi26NVMeEncapsulatedRequest_t, *pMpi26NVMeEncapsulatedRequest_t;

/*defines क्रम the Flags field */
#घोषणा MPI26_NVME_FLAGS_FORCE_ADMIN_ERR_RESP       (0x0020)
/*Submission Queue Type*/
#घोषणा MPI26_NVME_FLAGS_SUBMISSIONQ_MASK           (0x0010)
#घोषणा MPI26_NVME_FLAGS_SUBMISSIONQ_IO             (0x0000)
#घोषणा MPI26_NVME_FLAGS_SUBMISSIONQ_ADMIN          (0x0010)
/*Error Response Address Space */
#घोषणा MPI26_NVME_FLAGS_ERR_RSP_ADDR_MASK          (0x000C)
#घोषणा MPI26_NVME_FLAGS_ERR_RSP_ADDR_SYSTEM        (0x0000)
#घोषणा MPI26_NVME_FLAGS_ERR_RSP_ADDR_IOCTL         (0x0008)
/* Data Direction*/
#घोषणा MPI26_NVME_FLAGS_DATAसूचीECTION_MASK         (0x0003)
#घोषणा MPI26_NVME_FLAGS_NODATATRANSFER             (0x0000)
#घोषणा MPI26_NVME_FLAGS_WRITE                      (0x0001)
#घोषणा MPI26_NVME_FLAGS_READ                       (0x0002)
#घोषणा MPI26_NVME_FLAGS_BIसूचीECTIONAL              (0x0003)


/*NVMe Encapuslated Reply Message */
प्रकार काष्ठा _MPI26_NVME_ENCAPSULATED_ERROR_REPLY अणु
	U16	DevHandle;                      /*0x00 */
	U8	MsgLength;                      /*0x02 */
	U8	Function;                       /*0x03 */
	U16	EncapsulatedCommandLength;      /*0x04 */
	U8	Reserved1;                      /*0x06 */
	U8	MsgFlags;                       /*0x07 */
	U8	VP_ID;                          /*0x08 */
	U8	VF_ID;                          /*0x09 */
	U16	Reserved2;                      /*0x0A */
	U16	Reserved3;                      /*0x0C */
	U16	IOCStatus;                      /*0x0E */
	U32	IOCLogInfo;                     /*0x10 */
	U16	ErrorResponseCount;             /*0x14 */
	U16	Reserved4;                      /*0x16 */
पूर्ण MPI26_NVME_ENCAPSULATED_ERROR_REPLY,
	*PTR_MPI26_NVME_ENCAPSULATED_ERROR_REPLY,
	Mpi26NVMeEncapsulatedErrorReply_t,
	*pMpi26NVMeEncapsulatedErrorReply_t;


#पूर्ण_अगर
