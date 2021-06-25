<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2000-2020 Broadcom Inc. All rights reserved.
 *
 *
 *          Name:  mpi2_ioc.h
 *         Title:  MPI IOC, Port, Event, FW Download, and FW Upload messages
 * Creation Date:  October 11, 2006
 *
 * mpi2_ioc.h Version:  02.00.37
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
 * 04-30-07  02.00.00  Corresponds to Fusion-MPT MPI Specअगरication Rev A.
 * 06-04-07  02.00.01  In IOCFacts Reply काष्ठाure, नामd MaxDevices to
 *                     MaxTarमाला_लो.
 *                     Added TotalImageSize field to FWDownload Request.
 *                     Added reserved words to FWUpload Request.
 * 06-26-07  02.00.02  Added IR Configuration Change List Event.
 * 08-31-07  02.00.03  Removed SystemReplyQueueDepth field from the IOCInit
 *                     request and replaced it with
 *                     ReplyDescriptorPostQueueDepth and ReplyFreeQueueDepth.
 *                     Replaced the MinReplyQueueDepth field of the IOCFacts
 *                     reply with MaxReplyDescriptorPostQueueDepth.
 *                     Added MPI2_RDPQ_DEPTH_MIN define to specअगरy the minimum
 *                     depth क्रम the Reply Descriptor Post Queue.
 *                     Added SASAddress field to Initiator Device Table
 *                     Overflow Event data.
 * 10-31-07  02.00.04  Added ReasonCode MPI2_EVENT_SAS_INIT_RC_NOT_RESPONDING
 *                     क्रम SAS Initiator Device Status Change Event data.
 *                     Modअगरied Reason Code defines क्रम SAS Topology Change
 *                     List Event data, including adding a bit क्रम PHY Vacant
 *                     status, and adding a mask क्रम the Reason Code.
 *                     Added define क्रम
 *                     MPI2_EVENT_SAS_TOPO_ES_DELAY_NOT_RESPONDING.
 *                     Added define क्रम MPI2_EXT_IMAGE_TYPE_MEGARAID.
 * 12-18-07  02.00.05  Added Boot Status defines क्रम the IOCExceptions field of
 *                     the IOCFacts Reply.
 *                     Removed MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER define.
 *                     Moved MPI2_VERSION_UNION to mpi2.h.
 *                     Changed MPI2_EVENT_NOTIFICATION_REQUEST to use masks
 *                     instead of enables, and added SASBroadcastPrimitiveMasks
 *                     field.
 *                     Added Log Entry Added Event and related काष्ठाure.
 * 02-29-08  02.00.06  Added define MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID.
 *                     Removed define MPI2_IOCFACTS_PROTOCOL_SMP_TARGET.
 *                     Added MaxVolumes and MaxPersistentEntries fields to
 *                     IOCFacts reply.
 *                     Added ProtocalFlags and IOCCapabilities fields to
 *                     MPI2_FW_IMAGE_HEADER.
 *                     Removed MPI2_PORTENABLE_FLAGS_ENABLE_SINGLE_PORT.
 * 03-03-08  02.00.07  Fixed MPI2_FW_IMAGE_HEADER by changing Reserved26 to
 *                     a U16 (from a U32).
 *                     Removed extra 's' from EventMasks name.
 * 06-27-08  02.00.08  Fixed an offset in a comment.
 * 10-02-08  02.00.09  Removed SystemReplyFrameSize from MPI2_IOC_INIT_REQUEST.
 *                     Removed CurReplyFrameSize from MPI2_IOC_FACTS_REPLY and
 *                     नामd MinReplyFrameSize to ReplyFrameSize.
 *                     Added MPI2_IOCFACTS_EXCEPT_IR_FOREIGN_CONFIG_MAX.
 *                     Added two new RAIDOperation values क्रम Integrated RAID
 *                     Operations Status Event data.
 *                     Added four new IR Configuration Change List Event data
 *                     ReasonCode values.
 *                     Added two new ReasonCode defines क्रम SAS Device Status
 *                     Change Event data.
 *                     Added three new DiscoveryStatus bits क्रम the SAS
 *                     Discovery event data.
 *                     Added Multiplexing Status Change bit to the PhyStatus
 *                     field of the SAS Topology Change List event data.
 *                     Removed define क्रम MPI2_INIT_IMAGE_BOOTFLAGS_XMEMCOPY.
 *                     BootFlags are now product-specअगरic.
 *                     Added defines क्रम the inभागdual signature bytes
 *                     क्रम MPI2_INIT_IMAGE_FOOTER.
 * 01-19-09  02.00.10  Added MPI2_IOCFACTS_CAPABILITY_EVENT_REPLAY define.
 *                     Added MPI2_EVENT_SAS_DISC_DS_DOWNSTREAM_INITIATOR
 *                     define.
 *                     Added MPI2_EVENT_SAS_DEV_STAT_RC_SATA_INIT_FAILURE
 *                     define.
 *                     Removed MPI2_EVENT_SAS_DISC_DS_SATA_INIT_FAILURE define.
 * 05-06-09  02.00.11  Added MPI2_IOCFACTS_CAPABILITY_RAID_ACCELERATOR define.
 *                     Added MPI2_IOCFACTS_CAPABILITY_MSI_X_INDEX define.
 *                     Added two new reason codes क्रम SAS Device Status Change
 *                     Event.
 *                     Added new event: SAS PHY Counter.
 * 07-30-09  02.00.12  Added GPIO Interrupt event define and काष्ठाure.
 *                     Added MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER define.
 *                     Added new product id family क्रम 2208.
 * 10-28-09  02.00.13  Added HostMSIxVectors field to MPI2_IOC_INIT_REQUEST.
 *                     Added MaxMSIxVectors field to MPI2_IOC_FACTS_REPLY.
 *                     Added MinDevHandle field to MPI2_IOC_FACTS_REPLY.
 *                     Added MPI2_IOCFACTS_CAPABILITY_HOST_BASED_DISCOVERY.
 *                     Added MPI2_EVENT_HOST_BASED_DISCOVERY_PHY define.
 *                     Added MPI2_EVENT_SAS_TOPO_ES_NO_EXPANDER define.
 *                     Added Host Based Discovery Phy Event data.
 *                     Added defines क्रम ProductID Product field
 *                     (MPI2_FW_HEADER_PID_).
 *                     Modअगरied values क्रम SAS ProductID Family
 *                     (MPI2_FW_HEADER_PID_FAMILY_).
 * 02-10-10  02.00.14  Added SAS Quiesce Event काष्ठाure and defines.
 *                     Added PowerManagementControl Request काष्ठाures and
 *                     defines.
 * 05-12-10  02.00.15  Marked Task Set Full Event as obsolete.
 *                     Added MPI2_EVENT_SAS_TOPO_LR_UNSUPPORTED_PHY define.
 * 11-10-10  02.00.16  Added MPI2_FW_DOWNLOAD_ITYPE_MIN_PRODUCT_SPECIFIC.
 * 02-23-11  02.00.17  Added SAS NOTIFY Primitive event, and added
 *                     SASNotअगरyPrimitiveMasks field to
 *                     MPI2_EVENT_NOTIFICATION_REQUEST.
 *                     Added Temperature Threshold Event.
 *                     Added Host Message Event.
 *                     Added Send Host Message request and reply.
 * 05-25-11  02.00.18  For Extended Image Header, added
 *                     MPI2_EXT_IMAGE_TYPE_MIN_PRODUCT_SPECIFIC and
 *                     MPI2_EXT_IMAGE_TYPE_MAX_PRODUCT_SPECIFIC defines.
 *                     Deprecated MPI2_EXT_IMAGE_TYPE_MAX define.
 * 08-24-11  02.00.19  Added PhysicalPort field to
 *                     MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE काष्ठाure.
 *                     Marked MPI2_PM_CONTROL_FEATURE_PCIE_LINK as obsolete.
 * 11-18-11  02.00.20  Incorporating additions क्रम MPI v2.5.
 * 03-29-12  02.00.21  Added a product specअगरic range to event values.
 * 07-26-12  02.00.22  Added MPI2_IOCFACTS_EXCEPT_PARTIAL_MEMORY_FAILURE.
 *                     Added ElapsedSeconds field to
 *                     MPI2_EVENT_DATA_IR_OPERATION_STATUS.
 * 08-19-13  02.00.23  For IOCInit, added MPI2_IOCINIT_MSGFLAG_RDPQ_ARRAY_MODE
 *			and MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY.
 *			Added MPI2_IOCFACTS_CAPABILITY_RDPQ_ARRAY_CAPABLE.
 *			Added MPI2_FW_DOWNLOAD_ITYPE_PUBLIC_KEY.
 *			Added Encrypted Hash Extended Image.
 * 12-05-13  02.00.24  Added MPI25_HASH_IMAGE_TYPE_BIOS.
 * 11-18-14  02.00.25  Updated copyright inक्रमmation.
 * 03-16-15  02.00.26  Updated क्रम MPI v2.6.
 *		       Added MPI2_EVENT_ACTIVE_CABLE_EXCEPTION and
 *		       MPI26_EVENT_DATA_ACTIVE_CABLE_EXCEPT.
 *                     Added MPI26_FW_HEADER_PID_FAMILY_3324_SAS and
 *                     MPI26_FW_HEADER_PID_FAMILY_3516_SAS.
 *                     Added MPI26_CTRL_OP_SHUTDOWN.
 * 08-25-15  02.00.27  Added IC ARCH Class based signature defines.
 *                     Added MPI26_EVENT_PCIE_ENUM_ES_RESOURCES_EXHAUSTED event.
 *                     Added ConigurationFlags field to IOCInit message to
 *                     support NVMe SGL क्रमmat control.
 *                     Added PCIe SRIOV support.
 * 02-17-16   02.00.28 Added SAS 4 22.5 gbs speed support.
 *                     Added PCIe 4 16.0 GT/sec speec support.
 *                     Removed AHCI support.
 *                     Removed SOP support.
 * 07-01-16   02.00.29 Added Archclass क्रम 4008 product.
 *                     Added IOCException MPI2_IOCFACTS_EXCEPT_PCIE_DISABLED
 * 08-23-16   02.00.30 Added new defines क्रम the ImageType field of FWDownload
 *                     Request Message.
 *                     Added new defines क्रम the ImageType field of FWUpload
 *                     Request Message.
 *                     Added new values क्रम the RegionType field in the Layout
 *                     Data sections of the FLASH Layout Extended Image Data.
 *                     Added new defines क्रम the ReasonCode field of
 *                     Active Cable Exception Event.
 *                     Added MPI2_EVENT_ENCL_DEVICE_STATUS_CHANGE and
 *                     MPI26_EVENT_DATA_ENCL_DEV_STATUS_CHANGE.
 * 11-23-16   02.00.31 Added MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR and
 *                     MPI25_EVENT_DATA_SAS_DEVICE_DISCOVERY_ERROR.
 * 02-02-17   02.00.32 Added MPI2_FW_DOWNLOAD_ITYPE_CBB_BACKUP.
 *                     Added MPI25_EVENT_DATA_ACTIVE_CABLE_EXCEPT and related
 *                     defines क्रम the ReasonCode field.
 * 06-13-17   02.00.33 Added MPI2_FW_DOWNLOAD_ITYPE_CPLD.
 * 09-29-17   02.00.34 Added MPI26_EVENT_PCIDEV_STAT_RC_PCIE_HOT_RESET_FAILED
 *                     to the ReasonCode field in PCIe Device Status Change
 *                     Event Data.
 * 07-22-18   02.00.35 Added FW_DOWNLOAD_ITYPE_CPLD and _PSOC.
 *                     Moved FW image definitions ionto new mpi2_image,h
 * 08-14-18   02.00.36 Fixed definition of MPI2_FW_DOWNLOAD_ITYPE_PSOC (0x16)
 * 09-07-18   02.00.37 Added MPI26_EVENT_PCIE_TOPO_PI_16_LANES
 * 10-02-19   02.00.38 Added MPI26_IOCINIT_CFGFLAGS_COREDUMP_ENABLE
 *                     Added MPI26_IOCFACTS_CAPABILITY_COREDUMP_ENABLED
 *                     Added MPI2_FW_DOWNLOAD_ITYPE_COREDUMP
 *                     Added MPI2_FW_UPLOAD_ITYPE_COREDUMP
 * --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI2_IOC_H
#घोषणा MPI2_IOC_H

/*****************************************************************************
*
*              IOC Messages
*
*****************************************************************************/

/****************************************************************************
* IOCInit message
****************************************************************************/

/*IOCInit Request message */
प्रकार काष्ठा _MPI2_IOC_INIT_REQUEST अणु
	U8 WhoInit;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 MsgVersion;		/*0x0C */
	U16 HeaderVersion;	/*0x0E */
	U32 Reserved5;		/*0x10 */
	U16 ConfigurationFlags;	/* 0x14 */
	U8 HostPageSize;	/*0x16 */
	U8 HostMSIxVectors;	/*0x17 */
	U16 Reserved8;		/*0x18 */
	U16 SystemRequestFrameSize;	/*0x1A */
	U16 ReplyDescriptorPostQueueDepth;	/*0x1C */
	U16 ReplyFreeQueueDepth;	/*0x1E */
	U32 SenseBufferAddressHigh;	/*0x20 */
	U32 SystemReplyAddressHigh;	/*0x24 */
	U64 SystemRequestFrameBaseAddress;	/*0x28 */
	U64 ReplyDescriptorPostQueueAddress;	/*0x30 */
	U64 ReplyFreeQueueAddress;	/*0x38 */
	U64 TimeStamp;		/*0x40 */
पूर्ण MPI2_IOC_INIT_REQUEST, *PTR_MPI2_IOC_INIT_REQUEST,
	Mpi2IOCInitRequest_t, *pMpi2IOCInitRequest_t;

/*WhoInit values */
#घोषणा MPI2_WHOINIT_NOT_INITIALIZED            (0x00)
#घोषणा MPI2_WHOINIT_SYSTEM_BIOS                (0x01)
#घोषणा MPI2_WHOINIT_ROM_BIOS                   (0x02)
#घोषणा MPI2_WHOINIT_PCI_PEER                   (0x03)
#घोषणा MPI2_WHOINIT_HOST_DRIVER                (0x04)
#घोषणा MPI2_WHOINIT_MANUFACTURER               (0x05)

/* MsgFlags */
#घोषणा MPI2_IOCINIT_MSGFLAG_RDPQ_ARRAY_MODE    (0x01)


/*MsgVersion */
#घोषणा MPI2_IOCINIT_MSGVERSION_MAJOR_MASK      (0xFF00)
#घोषणा MPI2_IOCINIT_MSGVERSION_MAJOR_SHIFT     (8)
#घोषणा MPI2_IOCINIT_MSGVERSION_MINOR_MASK      (0x00FF)
#घोषणा MPI2_IOCINIT_MSGVERSION_MINOR_SHIFT     (0)

/*HeaderVersion */
#घोषणा MPI2_IOCINIT_HDRVERSION_UNIT_MASK       (0xFF00)
#घोषणा MPI2_IOCINIT_HDRVERSION_UNIT_SHIFT      (8)
#घोषणा MPI2_IOCINIT_HDRVERSION_DEV_MASK        (0x00FF)
#घोषणा MPI2_IOCINIT_HDRVERSION_DEV_SHIFT       (0)

/*ConfigurationFlags */
#घोषणा MPI26_IOCINIT_CFGFLAGS_NVME_SGL_FORMAT  (0x0001)
#घोषणा MPI26_IOCINIT_CFGFLAGS_COREDUMP_ENABLE  (0x0002)

/*minimum depth क्रम a Reply Descriptor Post Queue */
#घोषणा MPI2_RDPQ_DEPTH_MIN                     (16)

/* Reply Descriptor Post Queue Array Entry */
प्रकार काष्ठा _MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY अणु
	U64                 RDPQBaseAddress;                    /* 0x00 */
	U32                 Reserved1;                          /* 0x08 */
	U32                 Reserved2;                          /* 0x0C */
पूर्ण MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY,
*PTR_MPI2_IOC_INIT_RDPQ_ARRAY_ENTRY,
Mpi2IOCInitRDPQArrayEntry, *pMpi2IOCInitRDPQArrayEntry;


/*IOCInit Reply message */
प्रकार काष्ठा _MPI2_IOC_INIT_REPLY अणु
	U8 WhoInit;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 Reserved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
पूर्ण MPI2_IOC_INIT_REPLY, *PTR_MPI2_IOC_INIT_REPLY,
	Mpi2IOCInitReply_t, *pMpi2IOCInitReply_t;

/****************************************************************************
* IOCFacts message
****************************************************************************/

/*IOCFacts Request message */
प्रकार काष्ठा _MPI2_IOC_FACTS_REQUEST अणु
	U16 Reserved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
पूर्ण MPI2_IOC_FACTS_REQUEST, *PTR_MPI2_IOC_FACTS_REQUEST,
	Mpi2IOCFactsRequest_t, *pMpi2IOCFactsRequest_t;

/*IOCFacts Reply message */
प्रकार काष्ठा _MPI2_IOC_FACTS_REPLY अणु
	U16 MsgVersion;		/*0x00 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 HeaderVersion;	/*0x04 */
	U8 IOCNumber;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved1;		/*0x0A */
	U16 IOCExceptions;	/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
	U8 MaxChainDepth;	/*0x14 */
	U8 WhoInit;		/*0x15 */
	U8 NumberOfPorts;	/*0x16 */
	U8 MaxMSIxVectors;	/*0x17 */
	U16 RequestCredit;	/*0x18 */
	U16 ProductID;		/*0x1A */
	U32 IOCCapabilities;	/*0x1C */
	MPI2_VERSION_UNION FWVersion;	/*0x20 */
	U16 IOCRequestFrameSize;	/*0x24 */
	U16 IOCMaxChainSegmentSize;	/*0x26 */
	U16 MaxInitiators;	/*0x28 */
	U16 MaxTarमाला_लो;		/*0x2A */
	U16 MaxSasExpanders;	/*0x2C */
	U16 MaxEnclosures;	/*0x2E */
	U16 ProtocolFlags;	/*0x30 */
	U16 HighPriorityCredit;	/*0x32 */
	U16 MaxReplyDescriptorPostQueueDepth;	/*0x34 */
	U8 ReplyFrameSize;	/*0x36 */
	U8 MaxVolumes;		/*0x37 */
	U16 MaxDevHandle;	/*0x38 */
	U16 MaxPersistentEntries;	/*0x3A */
	U16 MinDevHandle;	/*0x3C */
	U8 CurrentHostPageSize;	/* 0x3E */
	U8 Reserved4;		/* 0x3F */
	U8 SGEModअगरierMask;	/*0x40 */
	U8 SGEModअगरierValue;	/*0x41 */
	U8 SGEModअगरierShअगरt;	/*0x42 */
	U8 Reserved5;		/*0x43 */
पूर्ण MPI2_IOC_FACTS_REPLY, *PTR_MPI2_IOC_FACTS_REPLY,
	Mpi2IOCFactsReply_t, *pMpi2IOCFactsReply_t;

/*MsgVersion */
#घोषणा MPI2_IOCFACTS_MSGVERSION_MAJOR_MASK             (0xFF00)
#घोषणा MPI2_IOCFACTS_MSGVERSION_MAJOR_SHIFT            (8)
#घोषणा MPI2_IOCFACTS_MSGVERSION_MINOR_MASK             (0x00FF)
#घोषणा MPI2_IOCFACTS_MSGVERSION_MINOR_SHIFT            (0)

/*HeaderVersion */
#घोषणा MPI2_IOCFACTS_HDRVERSION_UNIT_MASK              (0xFF00)
#घोषणा MPI2_IOCFACTS_HDRVERSION_UNIT_SHIFT             (8)
#घोषणा MPI2_IOCFACTS_HDRVERSION_DEV_MASK               (0x00FF)
#घोषणा MPI2_IOCFACTS_HDRVERSION_DEV_SHIFT              (0)

/*IOCExceptions */
#घोषणा MPI2_IOCFACTS_EXCEPT_PCIE_DISABLED              (0x0400)
#घोषणा MPI2_IOCFACTS_EXCEPT_PARTIAL_MEMORY_FAILURE     (0x0200)
#घोषणा MPI2_IOCFACTS_EXCEPT_IR_FOREIGN_CONFIG_MAX      (0x0100)

#घोषणा MPI2_IOCFACTS_EXCEPT_BOOTSTAT_MASK              (0x00E0)
#घोषणा MPI2_IOCFACTS_EXCEPT_BOOTSTAT_GOOD              (0x0000)
#घोषणा MPI2_IOCFACTS_EXCEPT_BOOTSTAT_BACKUP            (0x0020)
#घोषणा MPI2_IOCFACTS_EXCEPT_BOOTSTAT_RESTORED          (0x0040)
#घोषणा MPI2_IOCFACTS_EXCEPT_BOOTSTAT_CORRUPT_BACKUP    (0x0060)

#घोषणा MPI2_IOCFACTS_EXCEPT_METADATA_UNSUPPORTED       (0x0010)
#घोषणा MPI2_IOCFACTS_EXCEPT_MANUFACT_CHECKSUM_FAIL     (0x0008)
#घोषणा MPI2_IOCFACTS_EXCEPT_FW_CHECKSUM_FAIL           (0x0004)
#घोषणा MPI2_IOCFACTS_EXCEPT_RAID_CONFIG_INVALID        (0x0002)
#घोषणा MPI2_IOCFACTS_EXCEPT_CONFIG_CHECKSUM_FAIL       (0x0001)

/*defines क्रम WhoInit field are after the IOCInit Request */

/*ProductID field uses MPI2_FW_HEADER_PID_ */

/*IOCCapabilities */
#घोषणा MPI26_IOCFACTS_CAPABILITY_COREDUMP_ENABLED      (0x00200000)
#घोषणा MPI26_IOCFACTS_CAPABILITY_PCIE_SRIOV            (0x00100000)
#घोषणा MPI26_IOCFACTS_CAPABILITY_ATOMIC_REQ            (0x00080000)
#घोषणा MPI2_IOCFACTS_CAPABILITY_RDPQ_ARRAY_CAPABLE     (0x00040000)
#घोषणा MPI25_IOCFACTS_CAPABILITY_FAST_PATH_CAPABLE     (0x00020000)
#घोषणा MPI2_IOCFACTS_CAPABILITY_HOST_BASED_DISCOVERY   (0x00010000)
#घोषणा MPI2_IOCFACTS_CAPABILITY_MSI_X_INDEX            (0x00008000)
#घोषणा MPI2_IOCFACTS_CAPABILITY_RAID_ACCELERATOR       (0x00004000)
#घोषणा MPI2_IOCFACTS_CAPABILITY_EVENT_REPLAY           (0x00002000)
#घोषणा MPI2_IOCFACTS_CAPABILITY_INTEGRATED_RAID        (0x00001000)
#घोषणा MPI2_IOCFACTS_CAPABILITY_TLR                    (0x00000800)
#घोषणा MPI2_IOCFACTS_CAPABILITY_MULTICAST              (0x00000100)
#घोषणा MPI2_IOCFACTS_CAPABILITY_BIसूचीECTIONAL_TARGET   (0x00000080)
#घोषणा MPI2_IOCFACTS_CAPABILITY_EEDP                   (0x00000040)
#घोषणा MPI2_IOCFACTS_CAPABILITY_EXTENDED_BUFFER        (0x00000020)
#घोषणा MPI2_IOCFACTS_CAPABILITY_SNAPSHOT_BUFFER        (0x00000010)
#घोषणा MPI2_IOCFACTS_CAPABILITY_DIAG_TRACE_BUFFER      (0x00000008)
#घोषणा MPI2_IOCFACTS_CAPABILITY_TASK_SET_FULL_HANDLING (0x00000004)

/*ProtocolFlags */
#घोषणा MPI2_IOCFACTS_PROTOCOL_NVME_DEVICES             (0x0008)
#घोषणा MPI2_IOCFACTS_PROTOCOL_SCSI_INITIATOR           (0x0002)
#घोषणा MPI2_IOCFACTS_PROTOCOL_SCSI_TARGET              (0x0001)

/****************************************************************************
* PortFacts message
****************************************************************************/

/*PortFacts Request message */
प्रकार काष्ठा _MPI2_PORT_FACTS_REQUEST अणु
	U16 Reserved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 PortNumber;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved3;		/*0x0A */
पूर्ण MPI2_PORT_FACTS_REQUEST, *PTR_MPI2_PORT_FACTS_REQUEST,
	Mpi2PortFactsRequest_t, *pMpi2PortFactsRequest_t;

/*PortFacts Reply message */
प्रकार काष्ठा _MPI2_PORT_FACTS_REPLY अणु
	U16 Reserved1;		/*0x00 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 PortNumber;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved3;		/*0x0A */
	U16 Reserved4;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
	U8 Reserved5;		/*0x14 */
	U8 PortType;		/*0x15 */
	U16 Reserved6;		/*0x16 */
	U16 MaxPostedCmdBuffers;	/*0x18 */
	U16 Reserved7;		/*0x1A */
पूर्ण MPI2_PORT_FACTS_REPLY, *PTR_MPI2_PORT_FACTS_REPLY,
	Mpi2PortFactsReply_t, *pMpi2PortFactsReply_t;

/*PortType values */
#घोषणा MPI2_PORTFACTS_PORTTYPE_INACTIVE            (0x00)
#घोषणा MPI2_PORTFACTS_PORTTYPE_FC                  (0x10)
#घोषणा MPI2_PORTFACTS_PORTTYPE_ISCSI               (0x20)
#घोषणा MPI2_PORTFACTS_PORTTYPE_SAS_PHYSICAL        (0x30)
#घोषणा MPI2_PORTFACTS_PORTTYPE_SAS_VIRTUAL         (0x31)
#घोषणा MPI2_PORTFACTS_PORTTYPE_TRI_MODE            (0x40)


/****************************************************************************
* PortEnable message
****************************************************************************/

/*PortEnable Request message */
प्रकार काष्ठा _MPI2_PORT_ENABLE_REQUEST अणु
	U16 Reserved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U8 Reserved2;		/*0x04 */
	U8 PortFlags;		/*0x05 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
पूर्ण MPI2_PORT_ENABLE_REQUEST, *PTR_MPI2_PORT_ENABLE_REQUEST,
	Mpi2PortEnableRequest_t, *pMpi2PortEnableRequest_t;

/*PortEnable Reply message */
प्रकार काष्ठा _MPI2_PORT_ENABLE_REPLY अणु
	U16 Reserved1;		/*0x00 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U8 Reserved2;		/*0x04 */
	U8 PortFlags;		/*0x05 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 Reserved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
पूर्ण MPI2_PORT_ENABLE_REPLY, *PTR_MPI2_PORT_ENABLE_REPLY,
	Mpi2PortEnableReply_t, *pMpi2PortEnableReply_t;

/****************************************************************************
* EventNotअगरication message
****************************************************************************/

/*EventNotअगरication Request message */
#घोषणा MPI2_EVENT_NOTIFY_EVENTMASK_WORDS           (4)

प्रकार काष्ठा _MPI2_EVENT_NOTIFICATION_REQUEST अणु
	U16 Reserved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U32 Reserved5;		/*0x0C */
	U32 Reserved6;		/*0x10 */
	U32 EventMasks[MPI2_EVENT_NOTIFY_EVENTMASK_WORDS];	/*0x14 */
	U16 SASBroadcastPrimitiveMasks;	/*0x24 */
	U16 SASNotअगरyPrimitiveMasks;	/*0x26 */
	U32 Reserved8;		/*0x28 */
पूर्ण MPI2_EVENT_NOTIFICATION_REQUEST,
	*PTR_MPI2_EVENT_NOTIFICATION_REQUEST,
	Mpi2EventNotअगरicationRequest_t,
	*pMpi2EventNotअगरicationRequest_t;

/*EventNotअगरication Reply message */
प्रकार काष्ठा _MPI2_EVENT_NOTIFICATION_REPLY अणु
	U16 EventDataLength;	/*0x00 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved1;		/*0x04 */
	U8 AckRequired;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved2;		/*0x0A */
	U16 Reserved3;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
	U16 Event;		/*0x14 */
	U16 Reserved4;		/*0x16 */
	U32 EventContext;	/*0x18 */
	U32 EventData[1];	/*0x1C */
पूर्ण MPI2_EVENT_NOTIFICATION_REPLY, *PTR_MPI2_EVENT_NOTIFICATION_REPLY,
	Mpi2EventNotअगरicationReply_t,
	*pMpi2EventNotअगरicationReply_t;

/*AckRequired */
#घोषणा MPI2_EVENT_NOTIFICATION_ACK_NOT_REQUIRED    (0x00)
#घोषणा MPI2_EVENT_NOTIFICATION_ACK_REQUIRED        (0x01)

/*Event */
#घोषणा MPI2_EVENT_LOG_DATA                         (0x0001)
#घोषणा MPI2_EVENT_STATE_CHANGE                     (0x0002)
#घोषणा MPI2_EVENT_HARD_RESET_RECEIVED              (0x0005)
#घोषणा MPI2_EVENT_EVENT_CHANGE                     (0x000A)
#घोषणा MPI2_EVENT_TASK_SET_FULL                    (0x000E)	/*obsolete */
#घोषणा MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE         (0x000F)
#घोषणा MPI2_EVENT_IR_OPERATION_STATUS              (0x0014)
#घोषणा MPI2_EVENT_SAS_DISCOVERY                    (0x0016)
#घोषणा MPI2_EVENT_SAS_BROADCAST_PRIMITIVE          (0x0017)
#घोषणा MPI2_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE    (0x0018)
#घोषणा MPI2_EVENT_SAS_INIT_TABLE_OVERFLOW          (0x0019)
#घोषणा MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST         (0x001C)
#घोषणा MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE    (0x001D)
#घोषणा MPI2_EVENT_ENCL_DEVICE_STATUS_CHANGE        (0x001D)
#घोषणा MPI2_EVENT_IR_VOLUME                        (0x001E)
#घोषणा MPI2_EVENT_IR_PHYSICAL_DISK                 (0x001F)
#घोषणा MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST     (0x0020)
#घोषणा MPI2_EVENT_LOG_ENTRY_ADDED                  (0x0021)
#घोषणा MPI2_EVENT_SAS_PHY_COUNTER                  (0x0022)
#घोषणा MPI2_EVENT_GPIO_INTERRUPT                   (0x0023)
#घोषणा MPI2_EVENT_HOST_BASED_DISCOVERY_PHY         (0x0024)
#घोषणा MPI2_EVENT_SAS_QUIESCE                      (0x0025)
#घोषणा MPI2_EVENT_SAS_NOTIFY_PRIMITIVE             (0x0026)
#घोषणा MPI2_EVENT_TEMP_THRESHOLD                   (0x0027)
#घोषणा MPI2_EVENT_HOST_MESSAGE                     (0x0028)
#घोषणा MPI2_EVENT_POWER_PERFORMANCE_CHANGE         (0x0029)
#घोषणा MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE        (0x0030)
#घोषणा MPI2_EVENT_PCIE_ENUMERATION                 (0x0031)
#घोषणा MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST        (0x0032)
#घोषणा MPI2_EVENT_PCIE_LINK_COUNTER                (0x0033)
#घोषणा MPI2_EVENT_ACTIVE_CABLE_EXCEPTION           (0x0034)
#घोषणा MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR       (0x0035)
#घोषणा MPI2_EVENT_MIN_PRODUCT_SPECIFIC             (0x006E)
#घोषणा MPI2_EVENT_MAX_PRODUCT_SPECIFIC             (0x007F)

/*Log Entry Added Event data */

/*the following काष्ठाure matches MPI2_LOG_0_ENTRY in mpi2_cnfg.h */
#घोषणा MPI2_EVENT_DATA_LOG_DATA_LENGTH             (0x1C)

प्रकार काष्ठा _MPI2_EVENT_DATA_LOG_ENTRY_ADDED अणु
	U64 TimeStamp;		/*0x00 */
	U32 Reserved1;		/*0x08 */
	U16 LogSequence;	/*0x0C */
	U16 LogEntryQualअगरier;	/*0x0E */
	U8 VP_ID;		/*0x10 */
	U8 VF_ID;		/*0x11 */
	U16 Reserved2;		/*0x12 */
	U8 LogData[MPI2_EVENT_DATA_LOG_DATA_LENGTH];	/*0x14 */
पूर्ण MPI2_EVENT_DATA_LOG_ENTRY_ADDED,
	*PTR_MPI2_EVENT_DATA_LOG_ENTRY_ADDED,
	Mpi2EventDataLogEntryAdded_t,
	*pMpi2EventDataLogEntryAdded_t;

/*GPIO Interrupt Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_GPIO_INTERRUPT अणु
	U8 GPIONum;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U16 Reserved2;		/*0x02 */
पूर्ण MPI2_EVENT_DATA_GPIO_INTERRUPT,
	*PTR_MPI2_EVENT_DATA_GPIO_INTERRUPT,
	Mpi2EventDataGpioInterrupt_t,
	*pMpi2EventDataGpioInterrupt_t;

/*Temperature Threshold Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_TEMPERATURE अणु
	U16 Status;		/*0x00 */
	U8 SensorNum;		/*0x02 */
	U8 Reserved1;		/*0x03 */
	U16 CurrentTemperature;	/*0x04 */
	U16 Reserved2;		/*0x06 */
	U32 Reserved3;		/*0x08 */
	U32 Reserved4;		/*0x0C */
पूर्ण MPI2_EVENT_DATA_TEMPERATURE,
	*PTR_MPI2_EVENT_DATA_TEMPERATURE,
	Mpi2EventDataTemperature_t, *pMpi2EventDataTemperature_t;

/*Temperature Threshold Event data Status bits */
#घोषणा MPI2_EVENT_TEMPERATURE3_EXCEEDED            (0x0008)
#घोषणा MPI2_EVENT_TEMPERATURE2_EXCEEDED            (0x0004)
#घोषणा MPI2_EVENT_TEMPERATURE1_EXCEEDED            (0x0002)
#घोषणा MPI2_EVENT_TEMPERATURE0_EXCEEDED            (0x0001)

/*Host Message Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_HOST_MESSAGE अणु
	U8 SourceVF_ID;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U16 Reserved2;		/*0x02 */
	U32 Reserved3;		/*0x04 */
	U32 HostData[1];	/*0x08 */
पूर्ण MPI2_EVENT_DATA_HOST_MESSAGE, *PTR_MPI2_EVENT_DATA_HOST_MESSAGE,
	Mpi2EventDataHostMessage_t, *pMpi2EventDataHostMessage_t;

/*Power Perक्रमmance Change Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_POWER_PERF_CHANGE अणु
	U8 CurrentPowerMode;	/*0x00 */
	U8 PreviousPowerMode;	/*0x01 */
	U16 Reserved1;		/*0x02 */
पूर्ण MPI2_EVENT_DATA_POWER_PERF_CHANGE,
	*PTR_MPI2_EVENT_DATA_POWER_PERF_CHANGE,
	Mpi2EventDataPowerPerfChange_t,
	*pMpi2EventDataPowerPerfChange_t;

/*defines क्रम CurrentPowerMode and PreviousPowerMode fields */
#घोषणा MPI2_EVENT_PM_INIT_MASK              (0xC0)
#घोषणा MPI2_EVENT_PM_INIT_UNAVAILABLE       (0x00)
#घोषणा MPI2_EVENT_PM_INIT_HOST              (0x40)
#घोषणा MPI2_EVENT_PM_INIT_IO_UNIT           (0x80)
#घोषणा MPI2_EVENT_PM_INIT_PCIE_DPA          (0xC0)

#घोषणा MPI2_EVENT_PM_MODE_MASK              (0x07)
#घोषणा MPI2_EVENT_PM_MODE_UNAVAILABLE       (0x00)
#घोषणा MPI2_EVENT_PM_MODE_UNKNOWN           (0x01)
#घोषणा MPI2_EVENT_PM_MODE_FULL_POWER        (0x04)
#घोषणा MPI2_EVENT_PM_MODE_REDUCED_POWER     (0x05)
#घोषणा MPI2_EVENT_PM_MODE_STANDBY           (0x06)

/* Active Cable Exception Event data */

प्रकार काष्ठा _MPI26_EVENT_DATA_ACTIVE_CABLE_EXCEPT अणु
	U32         ActiveCablePowerRequirement;        /* 0x00 */
	U8          ReasonCode;                         /* 0x04 */
	U8          ReceptacleID;                       /* 0x05 */
	U16         Reserved1;                          /* 0x06 */
पूर्ण MPI25_EVENT_DATA_ACTIVE_CABLE_EXCEPT,
	*PTR_MPI25_EVENT_DATA_ACTIVE_CABLE_EXCEPT,
	Mpi25EventDataActiveCableExcept_t,
	*pMpi25EventDataActiveCableExcept_t,
	MPI26_EVENT_DATA_ACTIVE_CABLE_EXCEPT,
	*PTR_MPI26_EVENT_DATA_ACTIVE_CABLE_EXCEPT,
	Mpi26EventDataActiveCableExcept_t,
	*pMpi26EventDataActiveCableExcept_t;

/*MPI2.5 defines क्रम the ReasonCode field */
#घोषणा MPI25_EVENT_ACTIVE_CABLE_INSUFFICIENT_POWER     (0x00)
#घोषणा MPI25_EVENT_ACTIVE_CABLE_PRESENT                (0x01)
#घोषणा MPI25_EVENT_ACTIVE_CABLE_DEGRADED               (0x02)

/* defines क्रम ReasonCode field */
#घोषणा MPI26_EVENT_ACTIVE_CABLE_INSUFFICIENT_POWER     (0x00)
#घोषणा MPI26_EVENT_ACTIVE_CABLE_PRESENT                (0x01)
#घोषणा MPI26_EVENT_ACTIVE_CABLE_DEGRADED               (0x02)

/*Hard Reset Received Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_HARD_RESET_RECEIVED अणु
	U8 Reserved1;		/*0x00 */
	U8 Port;		/*0x01 */
	U16 Reserved2;		/*0x02 */
पूर्ण MPI2_EVENT_DATA_HARD_RESET_RECEIVED,
	*PTR_MPI2_EVENT_DATA_HARD_RESET_RECEIVED,
	Mpi2EventDataHardResetReceived_t,
	*pMpi2EventDataHardResetReceived_t;

/*Task Set Full Event data */
/*  this event is obsolete */

प्रकार काष्ठा _MPI2_EVENT_DATA_TASK_SET_FULL अणु
	U16 DevHandle;		/*0x00 */
	U16 CurrentDepth;	/*0x02 */
पूर्ण MPI2_EVENT_DATA_TASK_SET_FULL, *PTR_MPI2_EVENT_DATA_TASK_SET_FULL,
	Mpi2EventDataTaskSetFull_t, *pMpi2EventDataTaskSetFull_t;

/*SAS Device Status Change Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE अणु
	U16 TaskTag;		/*0x00 */
	U8 ReasonCode;		/*0x02 */
	U8 PhysicalPort;	/*0x03 */
	U8 ASC;			/*0x04 */
	U8 ASCQ;		/*0x05 */
	U16 DevHandle;		/*0x06 */
	U32 Reserved2;		/*0x08 */
	U64 SASAddress;		/*0x0C */
	U8 LUN[8];		/*0x14 */
पूर्ण MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE,
	*PTR_MPI2_EVENT_DATA_SAS_DEVICE_STATUS_CHANGE,
	Mpi2EventDataSasDeviceStatusChange_t,
	*pMpi2EventDataSasDeviceStatusChange_t;

/*SAS Device Status Change Event data ReasonCode values */
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_SMART_DATA                           (0x05)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_UNSUPPORTED                          (0x07)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET                (0x08)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_TASK_ABORT_INTERNAL                  (0x09)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_ABORT_TASK_SET_INTERNAL              (0x0A)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_CLEAR_TASK_SET_INTERNAL              (0x0B)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_QUERY_TASK_INTERNAL                  (0x0C)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_ASYNC_NOTIFICATION                   (0x0D)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_CMP_INTERNAL_DEV_RESET               (0x0E)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_CMP_TASK_ABORT_INTERNAL              (0x0F)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_SATA_INIT_FAILURE                    (0x10)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_EXPANDER_REDUCED_FUNCTIONALITY       (0x11)
#घोषणा MPI2_EVENT_SAS_DEV_STAT_RC_CMP_EXPANDER_REDUCED_FUNCTIONALITY   (0x12)

/*Integrated RAID Operation Status Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_IR_OPERATION_STATUS अणु
	U16 VolDevHandle;	/*0x00 */
	U16 Reserved1;		/*0x02 */
	U8 RAIDOperation;	/*0x04 */
	U8 PercentComplete;	/*0x05 */
	U16 Reserved2;		/*0x06 */
	U32 ElapsedSeconds;	/*0x08 */
पूर्ण MPI2_EVENT_DATA_IR_OPERATION_STATUS,
	*PTR_MPI2_EVENT_DATA_IR_OPERATION_STATUS,
	Mpi2EventDataIrOperationStatus_t,
	*pMpi2EventDataIrOperationStatus_t;

/*Integrated RAID Operation Status Event data RAIDOperation values */
#घोषणा MPI2_EVENT_IR_RAIDOP_RESYNC                     (0x00)
#घोषणा MPI2_EVENT_IR_RAIDOP_ONLINE_CAP_EXPANSION       (0x01)
#घोषणा MPI2_EVENT_IR_RAIDOP_CONSISTENCY_CHECK          (0x02)
#घोषणा MPI2_EVENT_IR_RAIDOP_BACKGROUND_INIT            (0x03)
#घोषणा MPI2_EVENT_IR_RAIDOP_MAKE_DATA_CONSISTENT       (0x04)

/*Integrated RAID Volume Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_IR_VOLUME अणु
	U16 VolDevHandle;	/*0x00 */
	U8 ReasonCode;		/*0x02 */
	U8 Reserved1;		/*0x03 */
	U32 NewValue;		/*0x04 */
	U32 PreviousValue;	/*0x08 */
पूर्ण MPI2_EVENT_DATA_IR_VOLUME, *PTR_MPI2_EVENT_DATA_IR_VOLUME,
	Mpi2EventDataIrVolume_t, *pMpi2EventDataIrVolume_t;

/*Integrated RAID Volume Event data ReasonCode values */
#घोषणा MPI2_EVENT_IR_VOLUME_RC_SETTINGS_CHANGED        (0x01)
#घोषणा MPI2_EVENT_IR_VOLUME_RC_STATUS_FLAGS_CHANGED    (0x02)
#घोषणा MPI2_EVENT_IR_VOLUME_RC_STATE_CHANGED           (0x03)

/*Integrated RAID Physical Disk Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_IR_PHYSICAL_DISK अणु
	U16 Reserved1;		/*0x00 */
	U8 ReasonCode;		/*0x02 */
	U8 PhysDiskNum;		/*0x03 */
	U16 PhysDiskDevHandle;	/*0x04 */
	U16 Reserved2;		/*0x06 */
	U16 Slot;		/*0x08 */
	U16 EnclosureHandle;	/*0x0A */
	U32 NewValue;		/*0x0C */
	U32 PreviousValue;	/*0x10 */
पूर्ण MPI2_EVENT_DATA_IR_PHYSICAL_DISK,
	*PTR_MPI2_EVENT_DATA_IR_PHYSICAL_DISK,
	Mpi2EventDataIrPhysicalDisk_t,
	*pMpi2EventDataIrPhysicalDisk_t;

/*Integrated RAID Physical Disk Event data ReasonCode values */
#घोषणा MPI2_EVENT_IR_PHYSDISK_RC_SETTINGS_CHANGED      (0x01)
#घोषणा MPI2_EVENT_IR_PHYSDISK_RC_STATUS_FLAGS_CHANGED  (0x02)
#घोषणा MPI2_EVENT_IR_PHYSDISK_RC_STATE_CHANGED         (0x03)

/*Integrated RAID Configuration Change List Event data */

/*
 *Host code (drivers, BIOS, utilities, etc.) should leave this define set to
 *one and check NumElements at runसमय.
 */
#अगर_अघोषित MPI2_EVENT_IR_CONFIG_ELEMENT_COUNT
#घोषणा MPI2_EVENT_IR_CONFIG_ELEMENT_COUNT          (1)
#पूर्ण_अगर

प्रकार काष्ठा _MPI2_EVENT_IR_CONFIG_ELEMENT अणु
	U16 ElementFlags;	/*0x00 */
	U16 VolDevHandle;	/*0x02 */
	U8 ReasonCode;		/*0x04 */
	U8 PhysDiskNum;		/*0x05 */
	U16 PhysDiskDevHandle;	/*0x06 */
पूर्ण MPI2_EVENT_IR_CONFIG_ELEMENT, *PTR_MPI2_EVENT_IR_CONFIG_ELEMENT,
	Mpi2EventIrConfigElement_t, *pMpi2EventIrConfigElement_t;

/*IR Configuration Change List Event data ElementFlags values */
#घोषणा MPI2_EVENT_IR_CHANGE_EFLAGS_ELEMENT_TYPE_MASK   (0x000F)
#घोषणा MPI2_EVENT_IR_CHANGE_EFLAGS_VOLUME_ELEMENT      (0x0000)
#घोषणा MPI2_EVENT_IR_CHANGE_EFLAGS_VOLPHYSDISK_ELEMENT (0x0001)
#घोषणा MPI2_EVENT_IR_CHANGE_EFLAGS_HOTSPARE_ELEMENT    (0x0002)

/*IR Configuration Change List Event data ReasonCode values */
#घोषणा MPI2_EVENT_IR_CHANGE_RC_ADDED                   (0x01)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_REMOVED                 (0x02)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_NO_CHANGE               (0x03)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_HIDE                    (0x04)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_UNHIDE                  (0x05)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_VOLUME_CREATED          (0x06)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED          (0x07)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_PD_CREATED              (0x08)
#घोषणा MPI2_EVENT_IR_CHANGE_RC_PD_DELETED              (0x09)

प्रकार काष्ठा _MPI2_EVENT_DATA_IR_CONFIG_CHANGE_LIST अणु
	U8 NumElements;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 Reserved2;		/*0x02 */
	U8 ConfigNum;		/*0x03 */
	U32 Flags;		/*0x04 */
	MPI2_EVENT_IR_CONFIG_ELEMENT
		ConfigElement[MPI2_EVENT_IR_CONFIG_ELEMENT_COUNT];/*0x08 */
पूर्ण MPI2_EVENT_DATA_IR_CONFIG_CHANGE_LIST,
	*PTR_MPI2_EVENT_DATA_IR_CONFIG_CHANGE_LIST,
	Mpi2EventDataIrConfigChangeList_t,
	*pMpi2EventDataIrConfigChangeList_t;

/*IR Configuration Change List Event data Flags values */
#घोषणा MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG   (0x00000001)

/*SAS Discovery Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_DISCOVERY अणु
	U8 Flags;		/*0x00 */
	U8 ReasonCode;		/*0x01 */
	U8 PhysicalPort;	/*0x02 */
	U8 Reserved1;		/*0x03 */
	U32 DiscoveryStatus;	/*0x04 */
पूर्ण MPI2_EVENT_DATA_SAS_DISCOVERY,
	*PTR_MPI2_EVENT_DATA_SAS_DISCOVERY,
	Mpi2EventDataSasDiscovery_t, *pMpi2EventDataSasDiscovery_t;

/*SAS Discovery Event data Flags values */
#घोषणा MPI2_EVENT_SAS_DISC_DEVICE_CHANGE                   (0x02)
#घोषणा MPI2_EVENT_SAS_DISC_IN_PROGRESS                     (0x01)

/*SAS Discovery Event data ReasonCode values */
#घोषणा MPI2_EVENT_SAS_DISC_RC_STARTED                      (0x01)
#घोषणा MPI2_EVENT_SAS_DISC_RC_COMPLETED                    (0x02)

/*SAS Discovery Event data DiscoveryStatus values */
#घोषणा MPI2_EVENT_SAS_DISC_DS_MAX_ENCLOSURES_EXCEED            (0x80000000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_MAX_EXPANDERS_EXCEED             (0x40000000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_MAX_DEVICES_EXCEED               (0x20000000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_MAX_TOPO_PHYS_EXCEED             (0x10000000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_DOWNSTREAM_INITIATOR             (0x08000000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_MULTI_SUBTRACTIVE_SUBTRACTIVE    (0x00008000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_EXP_MULTI_SUBTRACTIVE            (0x00004000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_MULTI_PORT_DOMAIN                (0x00002000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_TABLE_TO_SUBTRACTIVE_LINK        (0x00001000)
#घोषणा MPI2_EVENT_SAS_DISC_DS_UNSUPPORTED_DEVICE               (0x00000800)
#घोषणा MPI2_EVENT_SAS_DISC_DS_TABLE_LINK                       (0x00000400)
#घोषणा MPI2_EVENT_SAS_DISC_DS_SUBTRACTIVE_LINK                 (0x00000200)
#घोषणा MPI2_EVENT_SAS_DISC_DS_SMP_CRC_ERROR                    (0x00000100)
#घोषणा MPI2_EVENT_SAS_DISC_DS_SMP_FUNCTION_FAILED              (0x00000080)
#घोषणा MPI2_EVENT_SAS_DISC_DS_INDEX_NOT_EXIST                  (0x00000040)
#घोषणा MPI2_EVENT_SAS_DISC_DS_OUT_ROUTE_ENTRIES                (0x00000020)
#घोषणा MPI2_EVENT_SAS_DISC_DS_SMP_TIMEOUT                      (0x00000010)
#घोषणा MPI2_EVENT_SAS_DISC_DS_MULTIPLE_PORTS                   (0x00000004)
#घोषणा MPI2_EVENT_SAS_DISC_DS_UNADDRESSABLE_DEVICE             (0x00000002)
#घोषणा MPI2_EVENT_SAS_DISC_DS_LOOP_DETECTED                    (0x00000001)

/*SAS Broadcast Primitive Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_BROADCAST_PRIMITIVE अणु
	U8 PhyNum;		/*0x00 */
	U8 Port;		/*0x01 */
	U8 PortWidth;		/*0x02 */
	U8 Primitive;		/*0x03 */
पूर्ण MPI2_EVENT_DATA_SAS_BROADCAST_PRIMITIVE,
	*PTR_MPI2_EVENT_DATA_SAS_BROADCAST_PRIMITIVE,
	Mpi2EventDataSasBroadcastPrimitive_t,
	*pMpi2EventDataSasBroadcastPrimitive_t;

/*defines क्रम the Primitive field */
#घोषणा MPI2_EVENT_PRIMITIVE_CHANGE                         (0x01)
#घोषणा MPI2_EVENT_PRIMITIVE_SES                            (0x02)
#घोषणा MPI2_EVENT_PRIMITIVE_EXPANDER                       (0x03)
#घोषणा MPI2_EVENT_PRIMITIVE_ASYNCHRONOUS_EVENT             (0x04)
#घोषणा MPI2_EVENT_PRIMITIVE_RESERVED3                      (0x05)
#घोषणा MPI2_EVENT_PRIMITIVE_RESERVED4                      (0x06)
#घोषणा MPI2_EVENT_PRIMITIVE_CHANGE0_RESERVED               (0x07)
#घोषणा MPI2_EVENT_PRIMITIVE_CHANGE1_RESERVED               (0x08)

/*SAS Notअगरy Primitive Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_NOTIFY_PRIMITIVE अणु
	U8 PhyNum;		/*0x00 */
	U8 Port;		/*0x01 */
	U8 Reserved1;		/*0x02 */
	U8 Primitive;		/*0x03 */
पूर्ण MPI2_EVENT_DATA_SAS_NOTIFY_PRIMITIVE,
	*PTR_MPI2_EVENT_DATA_SAS_NOTIFY_PRIMITIVE,
	Mpi2EventDataSasNotअगरyPrimitive_t,
	*pMpi2EventDataSasNotअगरyPrimitive_t;

/*defines क्रम the Primitive field */
#घोषणा MPI2_EVENT_NOTIFY_ENABLE_SPINUP                     (0x01)
#घोषणा MPI2_EVENT_NOTIFY_POWER_LOSS_EXPECTED               (0x02)
#घोषणा MPI2_EVENT_NOTIFY_RESERVED1                         (0x03)
#घोषणा MPI2_EVENT_NOTIFY_RESERVED2                         (0x04)

/*SAS Initiator Device Status Change Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE अणु
	U8 ReasonCode;		/*0x00 */
	U8 PhysicalPort;	/*0x01 */
	U16 DevHandle;		/*0x02 */
	U64 SASAddress;		/*0x04 */
पूर्ण MPI2_EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE,
	*PTR_MPI2_EVENT_DATA_SAS_INIT_DEV_STATUS_CHANGE,
	Mpi2EventDataSasInitDevStatusChange_t,
	*pMpi2EventDataSasInitDevStatusChange_t;

/*SAS Initiator Device Status Change event ReasonCode values */
#घोषणा MPI2_EVENT_SAS_INIT_RC_ADDED                (0x01)
#घोषणा MPI2_EVENT_SAS_INIT_RC_NOT_RESPONDING       (0x02)

/*SAS Initiator Device Table Overflow Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_INIT_TABLE_OVERFLOW अणु
	U16 MaxInit;		/*0x00 */
	U16 CurrentInit;	/*0x02 */
	U64 SASAddress;		/*0x04 */
पूर्ण MPI2_EVENT_DATA_SAS_INIT_TABLE_OVERFLOW,
	*PTR_MPI2_EVENT_DATA_SAS_INIT_TABLE_OVERFLOW,
	Mpi2EventDataSasInitTableOverflow_t,
	*pMpi2EventDataSasInitTableOverflow_t;

/*SAS Topology Change List Event data */

/*
 *Host code (drivers, BIOS, utilities, etc.) should leave this define set to
 *one and check NumEntries at runसमय.
 */
#अगर_अघोषित MPI2_EVENT_SAS_TOPO_PHY_COUNT
#घोषणा MPI2_EVENT_SAS_TOPO_PHY_COUNT           (1)
#पूर्ण_अगर

प्रकार काष्ठा _MPI2_EVENT_SAS_TOPO_PHY_ENTRY अणु
	U16 AttachedDevHandle;	/*0x00 */
	U8 LinkRate;		/*0x02 */
	U8 PhyStatus;		/*0x03 */
पूर्ण MPI2_EVENT_SAS_TOPO_PHY_ENTRY, *PTR_MPI2_EVENT_SAS_TOPO_PHY_ENTRY,
	Mpi2EventSasTopoPhyEntry_t, *pMpi2EventSasTopoPhyEntry_t;

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_TOPOLOGY_CHANGE_LIST अणु
	U16 EnclosureHandle;	/*0x00 */
	U16 ExpanderDevHandle;	/*0x02 */
	U8 NumPhys;		/*0x04 */
	U8 Reserved1;		/*0x05 */
	U16 Reserved2;		/*0x06 */
	U8 NumEntries;		/*0x08 */
	U8 StartPhyNum;		/*0x09 */
	U8 ExpStatus;		/*0x0A */
	U8 PhysicalPort;	/*0x0B */
	MPI2_EVENT_SAS_TOPO_PHY_ENTRY
	PHY[MPI2_EVENT_SAS_TOPO_PHY_COUNT];	/*0x0C */
पूर्ण MPI2_EVENT_DATA_SAS_TOPOLOGY_CHANGE_LIST,
	*PTR_MPI2_EVENT_DATA_SAS_TOPOLOGY_CHANGE_LIST,
	Mpi2EventDataSasTopologyChangeList_t,
	*pMpi2EventDataSasTopologyChangeList_t;

/*values क्रम the ExpStatus field */
#घोषणा MPI2_EVENT_SAS_TOPO_ES_NO_EXPANDER                  (0x00)
#घोषणा MPI2_EVENT_SAS_TOPO_ES_ADDED                        (0x01)
#घोषणा MPI2_EVENT_SAS_TOPO_ES_NOT_RESPONDING               (0x02)
#घोषणा MPI2_EVENT_SAS_TOPO_ES_RESPONDING                   (0x03)
#घोषणा MPI2_EVENT_SAS_TOPO_ES_DELAY_NOT_RESPONDING         (0x04)

/*defines क्रम the LinkRate field */
#घोषणा MPI2_EVENT_SAS_TOPO_LR_CURRENT_MASK                 (0xF0)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_CURRENT_SHIFT                (4)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_PREV_MASK                    (0x0F)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_PREV_SHIFT                   (0)

#घोषणा MPI2_EVENT_SAS_TOPO_LR_UNKNOWN_LINK_RATE            (0x00)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_PHY_DISABLED                 (0x01)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_NEGOTIATION_FAILED           (0x02)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_SATA_OOB_COMPLETE            (0x03)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_PORT_SELECTOR                (0x04)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_SMP_RESET_IN_PROGRESS        (0x05)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_UNSUPPORTED_PHY              (0x06)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_RATE_1_5                     (0x08)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_RATE_3_0                     (0x09)
#घोषणा MPI2_EVENT_SAS_TOPO_LR_RATE_6_0                     (0x0A)
#घोषणा MPI25_EVENT_SAS_TOPO_LR_RATE_12_0                   (0x0B)
#घोषणा MPI26_EVENT_SAS_TOPO_LR_RATE_22_5                   (0x0C)

/*values क्रम the PhyStatus field */
#घोषणा MPI2_EVENT_SAS_TOPO_PHYSTATUS_VACANT                (0x80)
#घोषणा MPI2_EVENT_SAS_TOPO_PS_MULTIPLEX_CHANGE             (0x10)
/*values क्रम the PhyStatus ReasonCode sub-field */
#घोषणा MPI2_EVENT_SAS_TOPO_RC_MASK                         (0x0F)
#घोषणा MPI2_EVENT_SAS_TOPO_RC_TARG_ADDED                   (0x01)
#घोषणा MPI2_EVENT_SAS_TOPO_RC_TARG_NOT_RESPONDING          (0x02)
#घोषणा MPI2_EVENT_SAS_TOPO_RC_PHY_CHANGED                  (0x03)
#घोषणा MPI2_EVENT_SAS_TOPO_RC_NO_CHANGE                    (0x04)
#घोषणा MPI2_EVENT_SAS_TOPO_RC_DELAY_NOT_RESPONDING         (0x05)

/*SAS Enclosure Device Status Change Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_ENCL_DEV_STATUS_CHANGE अणु
	U16 EnclosureHandle;	/*0x00 */
	U8 ReasonCode;		/*0x02 */
	U8 PhysicalPort;	/*0x03 */
	U64 EnclosureLogicalID;	/*0x04 */
	U16 NumSlots;		/*0x0C */
	U16 StartSlot;		/*0x0E */
	U32 PhyBits;		/*0x10 */
पूर्ण MPI2_EVENT_DATA_SAS_ENCL_DEV_STATUS_CHANGE,
	*PTR_MPI2_EVENT_DATA_SAS_ENCL_DEV_STATUS_CHANGE,
	Mpi2EventDataSasEnclDevStatusChange_t,
	*pMpi2EventDataSasEnclDevStatusChange_t,
	MPI26_EVENT_DATA_ENCL_DEV_STATUS_CHANGE,
	*PTR_MPI26_EVENT_DATA_ENCL_DEV_STATUS_CHANGE,
	Mpi26EventDataEnclDevStatusChange_t,
	*pMpi26EventDataEnclDevStatusChange_t;

/*SAS Enclosure Device Status Change event ReasonCode values */
#घोषणा MPI2_EVENT_SAS_ENCL_RC_ADDED                (0x01)
#घोषणा MPI2_EVENT_SAS_ENCL_RC_NOT_RESPONDING       (0x02)

/*Enclosure Device Status Change event ReasonCode values */
#घोषणा MPI26_EVENT_ENCL_RC_ADDED                   (0x01)
#घोषणा MPI26_EVENT_ENCL_RC_NOT_RESPONDING          (0x02)


प्रकार काष्ठा _MPI25_EVENT_DATA_SAS_DEVICE_DISCOVERY_ERROR अणु
	U16	DevHandle;                  /*0x00 */
	U8	ReasonCode;                 /*0x02 */
	U8	PhysicalPort;               /*0x03 */
	U32	Reserved1[2];               /*0x04 */
	U64	SASAddress;                 /*0x0C */
	U32	Reserved2[2];               /*0x14 */
पूर्ण MPI25_EVENT_DATA_SAS_DEVICE_DISCOVERY_ERROR,
	*PTR_MPI25_EVENT_DATA_SAS_DEVICE_DISCOVERY_ERROR,
	Mpi25EventDataSasDeviceDiscoveryError_t,
	*pMpi25EventDataSasDeviceDiscoveryError_t;

/*SAS Device Discovery Error Event data ReasonCode values */
#घोषणा MPI25_EVENT_SAS_DISC_ERR_SMP_FAILED         (0x01)
#घोषणा MPI25_EVENT_SAS_DISC_ERR_SMP_TIMEOUT        (0x02)

/*SAS PHY Counter Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_PHY_COUNTER अणु
	U64 TimeStamp;		/*0x00 */
	U32 Reserved1;		/*0x08 */
	U8 PhyEventCode;	/*0x0C */
	U8 PhyNum;		/*0x0D */
	U16 Reserved2;		/*0x0E */
	U32 PhyEventInfo;	/*0x10 */
	U8 CounterType;		/*0x14 */
	U8 ThresholdWinकरोw;	/*0x15 */
	U8 TimeUnits;		/*0x16 */
	U8 Reserved3;		/*0x17 */
	U32 EventThreshold;	/*0x18 */
	U16 ThresholdFlags;	/*0x1C */
	U16 Reserved4;		/*0x1E */
पूर्ण MPI2_EVENT_DATA_SAS_PHY_COUNTER,
	*PTR_MPI2_EVENT_DATA_SAS_PHY_COUNTER,
	Mpi2EventDataSasPhyCounter_t,
	*pMpi2EventDataSasPhyCounter_t;

/*use MPI2_SASPHY3_EVENT_CODE_ values from mpi2_cnfg.h
 *क्रम the PhyEventCode field */

/*use MPI2_SASPHY3_COUNTER_TYPE_ values from mpi2_cnfg.h
 *क्रम the CounterType field */

/*use MPI2_SASPHY3_TIME_UNITS_ values from mpi2_cnfg.h
 *क्रम the TimeUnits field */

/*use MPI2_SASPHY3_TFLAGS_ values from mpi2_cnfg.h
 *क्रम the ThresholdFlags field */

/*SAS Quiesce Event data */

प्रकार काष्ठा _MPI2_EVENT_DATA_SAS_QUIESCE अणु
	U8 ReasonCode;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U16 Reserved2;		/*0x02 */
	U32 Reserved3;		/*0x04 */
पूर्ण MPI2_EVENT_DATA_SAS_QUIESCE,
	*PTR_MPI2_EVENT_DATA_SAS_QUIESCE,
	Mpi2EventDataSasQuiesce_t, *pMpi2EventDataSasQuiesce_t;

/*SAS Quiesce Event data ReasonCode values */
#घोषणा MPI2_EVENT_SAS_QUIESCE_RC_STARTED                   (0x01)
#घोषणा MPI2_EVENT_SAS_QUIESCE_RC_COMPLETED                 (0x02)

/*Host Based Discovery Phy Event data */

प्रकार काष्ठा _MPI2_EVENT_HBD_PHY_SAS अणु
	U8 Flags;		/*0x00 */
	U8 NegotiatedLinkRate;	/*0x01 */
	U8 PhyNum;		/*0x02 */
	U8 PhysicalPort;	/*0x03 */
	U32 Reserved1;		/*0x04 */
	U8 InitialFrame[28];	/*0x08 */
पूर्ण MPI2_EVENT_HBD_PHY_SAS, *PTR_MPI2_EVENT_HBD_PHY_SAS,
	Mpi2EventHbdPhySas_t, *pMpi2EventHbdPhySas_t;

/*values क्रम the Flags field */
#घोषणा MPI2_EVENT_HBD_SAS_FLAGS_FRAME_VALID        (0x02)
#घोषणा MPI2_EVENT_HBD_SAS_FLAGS_SATA_FRAME         (0x01)

/*use MPI2_SAS_NEG_LINK_RATE_ defines from mpi2_cnfg.h
 *क्रम the NegotiatedLinkRate field */

प्रकार जोड़ _MPI2_EVENT_HBD_DESCRIPTOR अणु
	MPI2_EVENT_HBD_PHY_SAS Sas;
पूर्ण MPI2_EVENT_HBD_DESCRIPTOR, *PTR_MPI2_EVENT_HBD_DESCRIPTOR,
	Mpi2EventHbdDescriptor_t, *pMpi2EventHbdDescriptor_t;

प्रकार काष्ठा _MPI2_EVENT_DATA_HBD_PHY अणु
	U8 DescriptorType;	/*0x00 */
	U8 Reserved1;		/*0x01 */
	U16 Reserved2;		/*0x02 */
	U32 Reserved3;		/*0x04 */
	MPI2_EVENT_HBD_DESCRIPTOR Descriptor;	/*0x08 */
पूर्ण MPI2_EVENT_DATA_HBD_PHY, *PTR_MPI2_EVENT_DATA_HBD_PHY,
	Mpi2EventDataHbdPhy_t,
	*pMpi2EventDataMpi2EventDataHbdPhy_t;

/*values क्रम the DescriptorType field */
#घोषणा MPI2_EVENT_HBD_DT_SAS               (0x01)


/*PCIe Device Status Change Event data (MPI v2.6 and later) */

प्रकार काष्ठा _MPI26_EVENT_DATA_PCIE_DEVICE_STATUS_CHANGE अणु
	U16	TaskTag;                        /*0x00 */
	U8	ReasonCode;                     /*0x02 */
	U8	PhysicalPort;                   /*0x03 */
	U8	ASC;                            /*0x04 */
	U8	ASCQ;                           /*0x05 */
	U16	DevHandle;                      /*0x06 */
	U32	Reserved2;                      /*0x08 */
	U64	WWID;                           /*0x0C */
	U8	LUN[8];                         /*0x14 */
पूर्ण MPI26_EVENT_DATA_PCIE_DEVICE_STATUS_CHANGE,
	*PTR_MPI26_EVENT_DATA_PCIE_DEVICE_STATUS_CHANGE,
	Mpi26EventDataPCIeDeviceStatusChange_t,
	*pMpi26EventDataPCIeDeviceStatusChange_t;

/*PCIe Device Status Change Event data ReasonCode values */
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_SMART_DATA                           (0x05)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_UNSUPPORTED                          (0x07)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_INTERNAL_DEVICE_RESET                (0x08)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_TASK_ABORT_INTERNAL                  (0x09)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_ABORT_TASK_SET_INTERNAL              (0x0A)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_CLEAR_TASK_SET_INTERNAL              (0x0B)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_QUERY_TASK_INTERNAL                  (0x0C)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_ASYNC_NOTIFICATION                   (0x0D)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_CMP_INTERNAL_DEV_RESET               (0x0E)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_CMP_TASK_ABORT_INTERNAL              (0x0F)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_DEV_INIT_FAILURE                     (0x10)
#घोषणा MPI26_EVENT_PCIDEV_STAT_RC_PCIE_HOT_RESET_FAILED                (0x11)


/*PCIe Enumeration Event data (MPI v2.6 and later) */

प्रकार काष्ठा _MPI26_EVENT_DATA_PCIE_ENUMERATION अणु
	U8	Flags;                      /*0x00 */
	U8	ReasonCode;                 /*0x01 */
	U8	PhysicalPort;               /*0x02 */
	U8	Reserved1;                  /*0x03 */
	U32	EnumerationStatus;          /*0x04 */
पूर्ण MPI26_EVENT_DATA_PCIE_ENUMERATION,
	*PTR_MPI26_EVENT_DATA_PCIE_ENUMERATION,
	Mpi26EventDataPCIeEnumeration_t,
	*pMpi26EventDataPCIeEnumeration_t;

/*PCIe Enumeration Event data Flags values */
#घोषणा MPI26_EVENT_PCIE_ENUM_DEVICE_CHANGE                 (0x02)
#घोषणा MPI26_EVENT_PCIE_ENUM_IN_PROGRESS                   (0x01)

/*PCIe Enumeration Event data ReasonCode values */
#घोषणा MPI26_EVENT_PCIE_ENUM_RC_STARTED                    (0x01)
#घोषणा MPI26_EVENT_PCIE_ENUM_RC_COMPLETED                  (0x02)

/*PCIe Enumeration Event data EnumerationStatus values */
#घोषणा MPI26_EVENT_PCIE_ENUM_ES_MAX_SWITCHES_EXCEED            (0x40000000)
#घोषणा MPI26_EVENT_PCIE_ENUM_ES_MAX_DEVICES_EXCEED             (0x20000000)
#घोषणा MPI26_EVENT_PCIE_ENUM_ES_RESOURCES_EXHAUSTED            (0x10000000)


/*PCIe Topology Change List Event data (MPI v2.6 and later) */

/*
 *Host code (drivers, BIOS, utilities, etc.) should leave this define set to
 *one and check NumEntries at runसमय.
 */
#अगर_अघोषित MPI26_EVENT_PCIE_TOPO_PORT_COUNT
#घोषणा MPI26_EVENT_PCIE_TOPO_PORT_COUNT        (1)
#पूर्ण_अगर

प्रकार काष्ठा _MPI26_EVENT_PCIE_TOPO_PORT_ENTRY अणु
	U16	AttachedDevHandle;      /*0x00 */
	U8	PortStatus;             /*0x02 */
	U8	Reserved1;              /*0x03 */
	U8	CurrentPortInfo;        /*0x04 */
	U8	Reserved2;              /*0x05 */
	U8	PreviousPortInfo;       /*0x06 */
	U8	Reserved3;              /*0x07 */
पूर्ण MPI26_EVENT_PCIE_TOPO_PORT_ENTRY,
	*PTR_MPI26_EVENT_PCIE_TOPO_PORT_ENTRY,
	Mpi26EventPCIeTopoPortEntry_t,
	*pMpi26EventPCIeTopoPortEntry_t;

/*PCIe Topology Change List Event data PortStatus values */
#घोषणा MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED                  (0x01)
#घोषणा MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING             (0x02)
#घोषणा MPI26_EVENT_PCIE_TOPO_PS_PORT_CHANGED               (0x03)
#घोषणा MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE                  (0x04)
#घोषणा MPI26_EVENT_PCIE_TOPO_PS_DELAY_NOT_RESPONDING       (0x05)

/*PCIe Topology Change List Event data defines क्रम CurrentPortInfo and
 *PreviousPortInfo
 */
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_LANE_MASK                  (0xF0)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_LANES_UNKNOWN              (0x00)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_1_LANE                     (0x10)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_2_LANES                    (0x20)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_4_LANES                    (0x30)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_8_LANES                    (0x40)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_16_LANES                   (0x50)

#घोषणा MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK                  (0x0F)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_RATE_UNKNOWN               (0x00)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_RATE_DISABLED              (0x01)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_RATE_2_5                   (0x02)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_RATE_5_0                   (0x03)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_RATE_8_0                   (0x04)
#घोषणा MPI26_EVENT_PCIE_TOPO_PI_RATE_16_0                  (0x05)

प्रकार काष्ठा _MPI26_EVENT_DATA_PCIE_TOPOLOGY_CHANGE_LIST अणु
	U16	EnclosureHandle;        /*0x00 */
	U16	SwitchDevHandle;        /*0x02 */
	U8	NumPorts;               /*0x04 */
	U8	Reserved1;              /*0x05 */
	U16	Reserved2;              /*0x06 */
	U8	NumEntries;             /*0x08 */
	U8	StartPortNum;           /*0x09 */
	U8	SwitchStatus;           /*0x0A */
	U8	PhysicalPort;           /*0x0B */
	MPI26_EVENT_PCIE_TOPO_PORT_ENTRY
		PortEntry[MPI26_EVENT_PCIE_TOPO_PORT_COUNT]; /*0x0C */
पूर्ण MPI26_EVENT_DATA_PCIE_TOPOLOGY_CHANGE_LIST,
	*PTR_MPI26_EVENT_DATA_PCIE_TOPOLOGY_CHANGE_LIST,
	Mpi26EventDataPCIeTopologyChangeList_t,
	*pMpi26EventDataPCIeTopologyChangeList_t;

/*PCIe Topology Change List Event data SwitchStatus values */
#घोषणा MPI26_EVENT_PCIE_TOPO_SS_NO_PCIE_SWITCH             (0x00)
#घोषणा MPI26_EVENT_PCIE_TOPO_SS_ADDED                      (0x01)
#घोषणा MPI26_EVENT_PCIE_TOPO_SS_NOT_RESPONDING             (0x02)
#घोषणा MPI26_EVENT_PCIE_TOPO_SS_RESPONDING                 (0x03)
#घोषणा MPI26_EVENT_PCIE_TOPO_SS_DELAY_NOT_RESPONDING       (0x04)

/*PCIe Link Counter Event data (MPI v2.6 and later) */

प्रकार काष्ठा _MPI26_EVENT_DATA_PCIE_LINK_COUNTER अणु
	U64	TimeStamp;          /*0x00 */
	U32	Reserved1;          /*0x08 */
	U8	LinkEventCode;      /*0x0C */
	U8	LinkNum;            /*0x0D */
	U16	Reserved2;          /*0x0E */
	U32	LinkEventInfo;      /*0x10 */
	U8	CounterType;        /*0x14 */
	U8	ThresholdWinकरोw;    /*0x15 */
	U8	TimeUnits;          /*0x16 */
	U8	Reserved3;          /*0x17 */
	U32	EventThreshold;     /*0x18 */
	U16	ThresholdFlags;     /*0x1C */
	U16	Reserved4;          /*0x1E */
पूर्ण MPI26_EVENT_DATA_PCIE_LINK_COUNTER,
	*PTR_MPI26_EVENT_DATA_PCIE_LINK_COUNTER,
	Mpi26EventDataPcieLinkCounter_t, *pMpi26EventDataPcieLinkCounter_t;


/*use MPI26_PCIELINK3_EVTCODE_ values from mpi2_cnfg.h क्रम the LinkEventCode
 *field
 */

/*use MPI26_PCIELINK3_COUNTER_TYPE_ values from mpi2_cnfg.h क्रम the CounterType
 *field
 */

/*use MPI26_PCIELINK3_TIME_UNITS_ values from mpi2_cnfg.h क्रम the TimeUnits
 *field
 */

/*use MPI26_PCIELINK3_TFLAGS_ values from mpi2_cnfg.h क्रम the ThresholdFlags
 *field
 */

/****************************************************************************
* EventAck message
****************************************************************************/

/*EventAck Request message */
प्रकार काष्ठा _MPI2_EVENT_ACK_REQUEST अणु
	U16 Reserved1;		/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 Event;		/*0x0C */
	U16 Reserved5;		/*0x0E */
	U32 EventContext;	/*0x10 */
पूर्ण MPI2_EVENT_ACK_REQUEST, *PTR_MPI2_EVENT_ACK_REQUEST,
	Mpi2EventAckRequest_t, *pMpi2EventAckRequest_t;

/*EventAck Reply message */
प्रकार काष्ठा _MPI2_EVENT_ACK_REPLY अणु
	U16 Reserved1;		/*0x00 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 Reserved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
पूर्ण MPI2_EVENT_ACK_REPLY, *PTR_MPI2_EVENT_ACK_REPLY,
	Mpi2EventAckReply_t, *pMpi2EventAckReply_t;

/****************************************************************************
* SendHostMessage message
****************************************************************************/

/*SendHostMessage Request message */
प्रकार काष्ठा _MPI2_SEND_HOST_MESSAGE_REQUEST अणु
	U16 HostDataLength;	/*0x00 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved1;		/*0x04 */
	U8 Reserved2;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved3;		/*0x0A */
	U8 Reserved4;		/*0x0C */
	U8 DestVF_ID;		/*0x0D */
	U16 Reserved5;		/*0x0E */
	U32 Reserved6;		/*0x10 */
	U32 Reserved7;		/*0x14 */
	U32 Reserved8;		/*0x18 */
	U32 Reserved9;		/*0x1C */
	U32 Reserved10;		/*0x20 */
	U32 HostData[1];	/*0x24 */
पूर्ण MPI2_SEND_HOST_MESSAGE_REQUEST,
	*PTR_MPI2_SEND_HOST_MESSAGE_REQUEST,
	Mpi2SendHostMessageRequest_t,
	*pMpi2SendHostMessageRequest_t;

/*SendHostMessage Reply message */
प्रकार काष्ठा _MPI2_SEND_HOST_MESSAGE_REPLY अणु
	U16 HostDataLength;	/*0x00 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved1;		/*0x04 */
	U8 Reserved2;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved3;		/*0x0A */
	U16 Reserved4;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
पूर्ण MPI2_SEND_HOST_MESSAGE_REPLY, *PTR_MPI2_SEND_HOST_MESSAGE_REPLY,
	Mpi2SendHostMessageReply_t, *pMpi2SendHostMessageReply_t;

/****************************************************************************
* FWDownload message
****************************************************************************/

/*MPI v2.0 FWDownload Request message */
प्रकार काष्ठा _MPI2_FW_DOWNLOAD_REQUEST अणु
	U8 ImageType;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U32 TotalImageSize;	/*0x0C */
	U32 Reserved5;		/*0x10 */
	MPI2_MPI_SGE_UNION SGL;	/*0x14 */
पूर्ण MPI2_FW_DOWNLOAD_REQUEST, *PTR_MPI2_FW_DOWNLOAD_REQUEST,
	Mpi2FWDownloadRequest, *pMpi2FWDownloadRequest;

#घोषणा MPI2_FW_DOWNLOAD_MSGFLGS_LAST_SEGMENT   (0x01)

#घोषणा MPI2_FW_DOWNLOAD_ITYPE_FW                   (0x01)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_BIOS                 (0x02)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_MANUFACTURING        (0x06)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_CONFIG_1             (0x07)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_CONFIG_2             (0x08)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_MEGARAID             (0x09)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_COMPLETE             (0x0A)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_COMMON_BOOT_BLOCK    (0x0B)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_PUBLIC_KEY           (0x0C)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_CBB_BACKUP           (0x0D)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_SBR                  (0x0E)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_SBR_BACKUP           (0x0F)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_HIIM                 (0x10)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_HIIA                 (0x11)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_CTLR                 (0x12)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_IMR_FIRMWARE         (0x13)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_MR_NVDATA            (0x14)
/*MPI v2.6 and newer */
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_CPLD                 (0x15)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_PSOC                 (0x16)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_COREDUMP             (0x17)
#घोषणा MPI2_FW_DOWNLOAD_ITYPE_MIN_PRODUCT_SPECIFIC (0xF0)

/*MPI v2.0 FWDownload TransactionContext Element */
प्रकार काष्ठा _MPI2_FW_DOWNLOAD_TCSGE अणु
	U8 Reserved1;		/*0x00 */
	U8 ContextSize;		/*0x01 */
	U8 DetailsLength;	/*0x02 */
	U8 Flags;		/*0x03 */
	U32 Reserved2;		/*0x04 */
	U32 ImageOffset;	/*0x08 */
	U32 ImageSize;		/*0x0C */
पूर्ण MPI2_FW_DOWNLOAD_TCSGE, *PTR_MPI2_FW_DOWNLOAD_TCSGE,
	Mpi2FWDownloadTCSGE_t, *pMpi2FWDownloadTCSGE_t;

/*MPI v2.5 FWDownload Request message */
प्रकार काष्ठा _MPI25_FW_DOWNLOAD_REQUEST अणु
	U8 ImageType;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U32 TotalImageSize;	/*0x0C */
	U32 Reserved5;		/*0x10 */
	U32 Reserved6;		/*0x14 */
	U32 ImageOffset;	/*0x18 */
	U32 ImageSize;		/*0x1C */
	MPI25_SGE_IO_UNION SGL;	/*0x20 */
पूर्ण MPI25_FW_DOWNLOAD_REQUEST, *PTR_MPI25_FW_DOWNLOAD_REQUEST,
	Mpi25FWDownloadRequest, *pMpi25FWDownloadRequest;

/*FWDownload Reply message */
प्रकार काष्ठा _MPI2_FW_DOWNLOAD_REPLY अणु
	U8 ImageType;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 Reserved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
पूर्ण MPI2_FW_DOWNLOAD_REPLY, *PTR_MPI2_FW_DOWNLOAD_REPLY,
	Mpi2FWDownloadReply_t, *pMpi2FWDownloadReply_t;

/****************************************************************************
* FWUpload message
****************************************************************************/

/*MPI v2.0 FWUpload Request message */
प्रकार काष्ठा _MPI2_FW_UPLOAD_REQUEST अणु
	U8 ImageType;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U32 Reserved5;		/*0x0C */
	U32 Reserved6;		/*0x10 */
	MPI2_MPI_SGE_UNION SGL;	/*0x14 */
पूर्ण MPI2_FW_UPLOAD_REQUEST, *PTR_MPI2_FW_UPLOAD_REQUEST,
	Mpi2FWUploadRequest_t, *pMpi2FWUploadRequest_t;

#घोषणा MPI2_FW_UPLOAD_ITYPE_FW_CURRENT         (0x00)
#घोषणा MPI2_FW_UPLOAD_ITYPE_FW_FLASH           (0x01)
#घोषणा MPI2_FW_UPLOAD_ITYPE_BIOS_FLASH         (0x02)
#घोषणा MPI2_FW_UPLOAD_ITYPE_FW_BACKUP          (0x05)
#घोषणा MPI2_FW_UPLOAD_ITYPE_MANUFACTURING      (0x06)
#घोषणा MPI2_FW_UPLOAD_ITYPE_CONFIG_1           (0x07)
#घोषणा MPI2_FW_UPLOAD_ITYPE_CONFIG_2           (0x08)
#घोषणा MPI2_FW_UPLOAD_ITYPE_MEGARAID           (0x09)
#घोषणा MPI2_FW_UPLOAD_ITYPE_COMPLETE           (0x0A)
#घोषणा MPI2_FW_UPLOAD_ITYPE_COMMON_BOOT_BLOCK  (0x0B)
#घोषणा MPI2_FW_UPLOAD_ITYPE_CBB_BACKUP         (0x0D)
#घोषणा MPI2_FW_UPLOAD_ITYPE_SBR                (0x0E)
#घोषणा MPI2_FW_UPLOAD_ITYPE_SBR_BACKUP         (0x0F)
#घोषणा MPI2_FW_UPLOAD_ITYPE_HIIM               (0x10)
#घोषणा MPI2_FW_UPLOAD_ITYPE_HIIA               (0x11)
#घोषणा MPI2_FW_UPLOAD_ITYPE_CTLR               (0x12)
#घोषणा MPI2_FW_UPLOAD_ITYPE_IMR_FIRMWARE       (0x13)
#घोषणा MPI2_FW_UPLOAD_ITYPE_MR_NVDATA          (0x14)


/*MPI v2.0 FWUpload TransactionContext Element */
प्रकार काष्ठा _MPI2_FW_UPLOAD_TCSGE अणु
	U8 Reserved1;		/*0x00 */
	U8 ContextSize;		/*0x01 */
	U8 DetailsLength;	/*0x02 */
	U8 Flags;		/*0x03 */
	U32 Reserved2;		/*0x04 */
	U32 ImageOffset;	/*0x08 */
	U32 ImageSize;		/*0x0C */
पूर्ण MPI2_FW_UPLOAD_TCSGE, *PTR_MPI2_FW_UPLOAD_TCSGE,
	Mpi2FWUploadTCSGE_t, *pMpi2FWUploadTCSGE_t;

/*MPI v2.5 FWUpload Request message */
प्रकार काष्ठा _MPI25_FW_UPLOAD_REQUEST अणु
	U8 ImageType;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U32 Reserved5;		/*0x0C */
	U32 Reserved6;		/*0x10 */
	U32 Reserved7;		/*0x14 */
	U32 ImageOffset;	/*0x18 */
	U32 ImageSize;		/*0x1C */
	MPI25_SGE_IO_UNION SGL;	/*0x20 */
पूर्ण MPI25_FW_UPLOAD_REQUEST, *PTR_MPI25_FW_UPLOAD_REQUEST,
	Mpi25FWUploadRequest_t, *pMpi25FWUploadRequest_t;

/*FWUpload Reply message */
प्रकार काष्ठा _MPI2_FW_UPLOAD_REPLY अणु
	U8 ImageType;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 Reserved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
	U32 ActualImageSize;	/*0x14 */
पूर्ण MPI2_FW_UPLOAD_REPLY, *PTR_MPI2_FW_UPLOAD_REPLY,
	Mpi2FWUploadReply_t, *pMPi2FWUploadReply_t;


/****************************************************************************
* PowerManagementControl message
****************************************************************************/

/*PowerManagementControl Request message */
प्रकार काष्ठा _MPI2_PWR_MGMT_CONTROL_REQUEST अणु
	U8 Feature;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U8 Parameter1;		/*0x0C */
	U8 Parameter2;		/*0x0D */
	U8 Parameter3;		/*0x0E */
	U8 Parameter4;		/*0x0F */
	U32 Reserved5;		/*0x10 */
	U32 Reserved6;		/*0x14 */
पूर्ण MPI2_PWR_MGMT_CONTROL_REQUEST, *PTR_MPI2_PWR_MGMT_CONTROL_REQUEST,
	Mpi2PwrMgmtControlRequest_t, *pMpi2PwrMgmtControlRequest_t;

/*defines क्रम the Feature field */
#घोषणा MPI2_PM_CONTROL_FEATURE_DA_PHY_POWER_COND       (0x01)
#घोषणा MPI2_PM_CONTROL_FEATURE_PORT_WIDTH_MODULATION   (0x02)
#घोषणा MPI2_PM_CONTROL_FEATURE_PCIE_LINK               (0x03)	/*obsolete */
#घोषणा MPI2_PM_CONTROL_FEATURE_IOC_SPEED               (0x04)
#घोषणा MPI2_PM_CONTROL_FEATURE_GLOBAL_PWR_MGMT_MODE    (0x05)
#घोषणा MPI2_PM_CONTROL_FEATURE_MIN_PRODUCT_SPECIFIC    (0x80)
#घोषणा MPI2_PM_CONTROL_FEATURE_MAX_PRODUCT_SPECIFIC    (0xFF)

/*parameter usage क्रम the MPI2_PM_CONTROL_FEATURE_DA_PHY_POWER_COND Feature */
/*Parameter1 contains a PHY number */
/*Parameter2 indicates घातer condition action using these defines */
#घोषणा MPI2_PM_CONTROL_PARAM2_PARTIAL                  (0x01)
#घोषणा MPI2_PM_CONTROL_PARAM2_SLUMBER                  (0x02)
#घोषणा MPI2_PM_CONTROL_PARAM2_EXIT_PWR_MGMT            (0x03)
/*Parameter3 and Parameter4 are reserved */

/*parameter usage क्रम the MPI2_PM_CONTROL_FEATURE_PORT_WIDTH_MODULATION
 * Feature */
/*Parameter1 contains SAS port width modulation group number */
/*Parameter2 indicates IOC action using these defines */
#घोषणा MPI2_PM_CONTROL_PARAM2_REQUEST_OWNERSHIP        (0x01)
#घोषणा MPI2_PM_CONTROL_PARAM2_CHANGE_MODULATION        (0x02)
#घोषणा MPI2_PM_CONTROL_PARAM2_RELINQUISH_OWNERSHIP     (0x03)
/*Parameter3 indicates desired modulation level using these defines */
#घोषणा MPI2_PM_CONTROL_PARAM3_25_PERCENT               (0x00)
#घोषणा MPI2_PM_CONTROL_PARAM3_50_PERCENT               (0x01)
#घोषणा MPI2_PM_CONTROL_PARAM3_75_PERCENT               (0x02)
#घोषणा MPI2_PM_CONTROL_PARAM3_100_PERCENT              (0x03)
/*Parameter4 is reserved */

/*this next set (_PCIE_LINK) is obsolete */
/*parameter usage क्रम the MPI2_PM_CONTROL_FEATURE_PCIE_LINK Feature */
/*Parameter1 indicates desired PCIe link speed using these defines */
#घोषणा MPI2_PM_CONTROL_PARAM1_PCIE_2_5_GBPS            (0x00)	/*obsolete */
#घोषणा MPI2_PM_CONTROL_PARAM1_PCIE_5_0_GBPS            (0x01)	/*obsolete */
#घोषणा MPI2_PM_CONTROL_PARAM1_PCIE_8_0_GBPS            (0x02)	/*obsolete */
/*Parameter2 indicates desired PCIe link width using these defines */
#घोषणा MPI2_PM_CONTROL_PARAM2_WIDTH_X1                 (0x01)	/*obsolete */
#घोषणा MPI2_PM_CONTROL_PARAM2_WIDTH_X2                 (0x02)	/*obsolete */
#घोषणा MPI2_PM_CONTROL_PARAM2_WIDTH_X4                 (0x04)	/*obsolete */
#घोषणा MPI2_PM_CONTROL_PARAM2_WIDTH_X8                 (0x08)	/*obsolete */
/*Parameter3 and Parameter4 are reserved */

/*parameter usage क्रम the MPI2_PM_CONTROL_FEATURE_IOC_SPEED Feature */
/*Parameter1 indicates desired IOC hardware घड़ी speed using these defines */
#घोषणा MPI2_PM_CONTROL_PARAM1_FULL_IOC_SPEED           (0x01)
#घोषणा MPI2_PM_CONTROL_PARAM1_HALF_IOC_SPEED           (0x02)
#घोषणा MPI2_PM_CONTROL_PARAM1_QUARTER_IOC_SPEED        (0x04)
#घोषणा MPI2_PM_CONTROL_PARAM1_EIGHTH_IOC_SPEED         (0x08)
/*Parameter2, Parameter3, and Parameter4 are reserved */

/*parameter usage क्रम the MPI2_PM_CONTROL_FEATURE_GLOBAL_PWR_MGMT_MODE Feature*/
/*Parameter1 indicates host action regarding global घातer management mode */
#घोषणा MPI2_PM_CONTROL_PARAM1_TAKE_CONTROL             (0x01)
#घोषणा MPI2_PM_CONTROL_PARAM1_CHANGE_GLOBAL_MODE       (0x02)
#घोषणा MPI2_PM_CONTROL_PARAM1_RELEASE_CONTROL          (0x03)
/*Parameter2 indicates the requested global घातer management mode */
#घोषणा MPI2_PM_CONTROL_PARAM2_FULL_PWR_PERF            (0x01)
#घोषणा MPI2_PM_CONTROL_PARAM2_REDUCED_PWR_PERF         (0x08)
#घोषणा MPI2_PM_CONTROL_PARAM2_STANDBY                  (0x40)
/*Parameter3 and Parameter4 are reserved */

/*PowerManagementControl Reply message */
प्रकार काष्ठा _MPI2_PWR_MGMT_CONTROL_REPLY अणु
	U8 Feature;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 Reserved2;		/*0x04 */
	U8 Reserved3;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved4;		/*0x0A */
	U16 Reserved5;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
पूर्ण MPI2_PWR_MGMT_CONTROL_REPLY, *PTR_MPI2_PWR_MGMT_CONTROL_REPLY,
	Mpi2PwrMgmtControlReply_t, *pMpi2PwrMgmtControlReply_t;

/****************************************************************************
*  IO Unit Control messages (MPI v2.6 and later only.)
****************************************************************************/

/* IO Unit Control Request Message */
प्रकार काष्ठा _MPI26_IOUNIT_CONTROL_REQUEST अणु
	U8                      Operation;          /* 0x00 */
	U8                      Reserved1;          /* 0x01 */
	U8                      ChainOffset;        /* 0x02 */
	U8                      Function;           /* 0x03 */
	U16                     DevHandle;          /* 0x04 */
	U8                      IOCParameter;       /* 0x06 */
	U8                      MsgFlags;           /* 0x07 */
	U8                      VP_ID;              /* 0x08 */
	U8                      VF_ID;              /* 0x09 */
	U16                     Reserved3;          /* 0x0A */
	U16                     Reserved4;          /* 0x0C */
	U8                      PhyNum;             /* 0x0E */
	U8                      PrimFlags;          /* 0x0F */
	U32                     Primitive;          /* 0x10 */
	U8                      LookupMethod;       /* 0x14 */
	U8                      Reserved5;          /* 0x15 */
	U16                     SlotNumber;         /* 0x16 */
	U64                     LookupAddress;      /* 0x18 */
	U32                     IOCParameterValue;  /* 0x20 */
	U32                     Reserved7;          /* 0x24 */
	U32                     Reserved8;          /* 0x28 */
पूर्ण MPI26_IOUNIT_CONTROL_REQUEST,
	*PTR_MPI26_IOUNIT_CONTROL_REQUEST,
	Mpi26IoUnitControlRequest_t,
	*pMpi26IoUnitControlRequest_t;

/* values क्रम the Operation field */
#घोषणा MPI26_CTRL_OP_CLEAR_ALL_PERSISTENT              (0x02)
#घोषणा MPI26_CTRL_OP_SAS_PHY_LINK_RESET                (0x06)
#घोषणा MPI26_CTRL_OP_SAS_PHY_HARD_RESET                (0x07)
#घोषणा MPI26_CTRL_OP_PHY_CLEAR_ERROR_LOG               (0x08)
#घोषणा MPI26_CTRL_OP_LINK_CLEAR_ERROR_LOG              (0x09)
#घोषणा MPI26_CTRL_OP_SAS_SEND_PRIMITIVE                (0x0A)
#घोषणा MPI26_CTRL_OP_FORCE_FULL_DISCOVERY              (0x0B)
#घोषणा MPI26_CTRL_OP_REMOVE_DEVICE                     (0x0D)
#घोषणा MPI26_CTRL_OP_LOOKUP_MAPPING                    (0x0E)
#घोषणा MPI26_CTRL_OP_SET_IOC_PARAMETER                 (0x0F)
#घोषणा MPI26_CTRL_OP_ENABLE_FP_DEVICE                  (0x10)
#घोषणा MPI26_CTRL_OP_DISABLE_FP_DEVICE                 (0x11)
#घोषणा MPI26_CTRL_OP_ENABLE_FP_ALL                     (0x12)
#घोषणा MPI26_CTRL_OP_DISABLE_FP_ALL                    (0x13)
#घोषणा MPI26_CTRL_OP_DEV_ENABLE_NCQ                    (0x14)
#घोषणा MPI26_CTRL_OP_DEV_DISABLE_NCQ                   (0x15)
#घोषणा MPI26_CTRL_OP_SHUTDOWN                          (0x16)
#घोषणा MPI26_CTRL_OP_DEV_ENABLE_PERSIST_CONNECTION     (0x17)
#घोषणा MPI26_CTRL_OP_DEV_DISABLE_PERSIST_CONNECTION    (0x18)
#घोषणा MPI26_CTRL_OP_DEV_CLOSE_PERSIST_CONNECTION      (0x19)
#घोषणा MPI26_CTRL_OP_ENABLE_NVME_SGL_FORMAT            (0x1A)
#घोषणा MPI26_CTRL_OP_DISABLE_NVME_SGL_FORMAT           (0x1B)
#घोषणा MPI26_CTRL_OP_PRODUCT_SPECIFIC_MIN              (0x80)

/* values क्रम the PrimFlags field */
#घोषणा MPI26_CTRL_PRIMFLAGS_SINGLE                     (0x08)
#घोषणा MPI26_CTRL_PRIMFLAGS_TRIPLE                     (0x02)
#घोषणा MPI26_CTRL_PRIMFLAGS_REDUNDANT                  (0x01)

/* values क्रम the LookupMethod field */
#घोषणा MPI26_CTRL_LOOKUP_METHOD_WWID_ADDRESS           (0x01)
#घोषणा MPI26_CTRL_LOOKUP_METHOD_ENCLOSURE_SLOT         (0x02)
#घोषणा MPI26_CTRL_LOOKUP_METHOD_SAS_DEVICE_NAME        (0x03)


/* IO Unit Control Reply Message */
प्रकार काष्ठा _MPI26_IOUNIT_CONTROL_REPLY अणु
	U8                      Operation;          /* 0x00 */
	U8                      Reserved1;          /* 0x01 */
	U8                      MsgLength;          /* 0x02 */
	U8                      Function;           /* 0x03 */
	U16                     DevHandle;          /* 0x04 */
	U8                      IOCParameter;       /* 0x06 */
	U8                      MsgFlags;           /* 0x07 */
	U8                      VP_ID;              /* 0x08 */
	U8                      VF_ID;              /* 0x09 */
	U16                     Reserved3;          /* 0x0A */
	U16                     Reserved4;          /* 0x0C */
	U16                     IOCStatus;          /* 0x0E */
	U32                     IOCLogInfo;         /* 0x10 */
पूर्ण MPI26_IOUNIT_CONTROL_REPLY,
	*PTR_MPI26_IOUNIT_CONTROL_REPLY,
	Mpi26IoUnitControlReply_t,
	*pMpi26IoUnitControlReply_t;


#पूर्ण_अगर
