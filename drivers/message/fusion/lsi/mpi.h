<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2000-2008 LSI Corporation.
 *
 *
 *           Name:  mpi.h
 *          Title:  MPI Message independent काष्ठाures and definitions
 *  Creation Date:  July 27, 2000
 *
 *    mpi.h Version:  01.05.16
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Original release क्रम 0.10 spec dated 4/26/2000.
 *  05-24-00  00.10.02  Added MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH definition.
 *  06-06-00  01.00.01  Update MPI_VERSION_MAJOR and MPI_VERSION_MINOR.
 *  06-22-00  01.00.02  Added MPI_IOCSTATUS_LAN_ definitions.
 *                      Removed LAN_SUSPEND function definition.
 *                      Added MPI_MSGFLAGS_CONTINUATION_REPLY definition.
 *  06-30-00  01.00.03  Added MPI_CONTEXT_REPLY_TYPE_LAN definition.
 *                      Added MPI_GET/SET_CONTEXT_REPLY_TYPE macros.
 *  07-27-00  01.00.04  Added MPI_FAULT_ definitions.
 *                      Removed MPI_IOCSTATUS_MSG/DATA_XFER_ERROR definitions.
 *                      Added MPI_IOCSTATUS_INTERNAL_ERROR definition.
 *                      Added MPI_IOCSTATUS_TARGET_XFER_COUNT_MISMATCH.
 *  11-02-00  01.01.01  Original release क्रम post 1.0 work.
 *  12-04-00  01.01.02  Added new function codes.
 *  01-09-01  01.01.03  Added more definitions to the प्रणाली पूर्णांकerface section
 *                      Added MPI_IOCSTATUS_TARGET_STS_DATA_NOT_SENT.
 *  01-25-01  01.01.04  Changed MPI_VERSION_MINOR from 0x00 to 0x01.
 *  02-20-01  01.01.05  Started using MPI_POINTER.
 *                      Fixed value क्रम MPI_DIAG_RW_ENABLE.
 *                      Added defines क्रम MPI_DIAG_PREVENT_IOC_BOOT and
 *                      MPI_DIAG_CLEAR_FLASH_BAD_SIG.
 *                      Obsoleted MPI_IOCSTATUS_TARGET_FC_ defines.
 *  02-27-01  01.01.06  Removed MPI_HOST_INDEX_REGISTER define.
 *                      Added function codes क्रम RAID.
 *  04-09-01  01.01.07  Added alternate define क्रम MPI_DOORBELL_ACTIVE,
 *                      MPI_DOORBELL_USED, to better match the spec.
 *  08-08-01  01.02.01  Original release क्रम v1.2 work.
 *                      Changed MPI_VERSION_MINOR from 0x01 to 0x02.
 *                      Added define MPI_FUNCTION_TOOLBOX.
 *  09-28-01  01.02.02  New function code MPI_SCSI_ENCLOSURE_PROCESSOR.
 *  11-01-01  01.02.03  Changed name to MPI_FUNCTION_SCSI_ENCLOSURE_PROCESSOR.
 *  03-14-02  01.02.04  Added MPI_HEADER_VERSION_ defines.
 *  05-31-02  01.02.05  Bumped MPI_HEADER_VERSION_UNIT.
 *  07-12-02  01.02.06  Added define क्रम MPI_FUNCTION_MAILBOX.
 *  09-16-02  01.02.07  Bumped value क्रम MPI_HEADER_VERSION_UNIT.
 *  11-15-02  01.02.08  Added define MPI_IOCSTATUS_TARGET_INVALID_IO_INDEX and
 *                      obsoleted define MPI_IOCSTATUS_TARGET_INVALID_IOCINDEX.
 *  04-01-03  01.02.09  New IOCStatus code: MPI_IOCSTATUS_FC_EXCHANGE_CANCELED
 *  06-26-03  01.02.10  Bumped MPI_HEADER_VERSION_UNIT value.
 *  01-16-04  01.02.11  Added define क्रम MPI_IOCLOGINFO_TYPE_SHIFT.
 *  04-29-04  01.02.12  Added function codes क्रम MPI_FUNCTION_DIAG_BUFFER_POST
 *                      and MPI_FUNCTION_DIAG_RELEASE.
 *                      Added MPI_IOCSTATUS_DIAGNOSTIC_RELEASED define.
 *                      Bumped MPI_HEADER_VERSION_UNIT value.
 *  05-11-04  01.03.01  Bumped MPI_VERSION_MINOR क्रम MPI v1.3.
 *                      Added codes क्रम Inband.
 *  08-19-04  01.05.01  Added defines क्रम Host Buffer Access Control करोorbell.
 *                      Added define क्रम offset of High Priority Request Queue.
 *                      Added new function codes and new IOCStatus codes.
 *                      Added a IOCLogInfo type of SAS.
 *  12-07-04  01.05.02  Bumped MPI_HEADER_VERSION_UNIT.
 *  12-09-04  01.05.03  Bumped MPI_HEADER_VERSION_UNIT.
 *  01-15-05  01.05.04  Bumped MPI_HEADER_VERSION_UNIT.
 *  02-09-05  01.05.05  Bumped MPI_HEADER_VERSION_UNIT.
 *  02-22-05  01.05.06  Bumped MPI_HEADER_VERSION_UNIT.
 *  03-11-05  01.05.07  Removed function codes क्रम SCSI IO 32 and
 *                      TargetAssistExtended requests.
 *                      Removed EEDP IOCStatus codes.
 *  06-24-05  01.05.08  Added function codes क्रम SCSI IO 32 and
 *                      TargetAssistExtended requests.
 *                      Added EEDP IOCStatus codes.
 *  08-03-05  01.05.09  Bumped MPI_HEADER_VERSION_UNIT.
 *  08-30-05  01.05.10  Added 2 new IOCStatus codes क्रम Target.
 *  03-27-06  01.05.11  Bumped MPI_HEADER_VERSION_UNIT.
 *  10-11-06  01.05.12  Bumped MPI_HEADER_VERSION_UNIT.
 *  05-24-07  01.05.13  Bumped MPI_HEADER_VERSION_UNIT.
 *  08-07-07  01.05.14  Bumped MPI_HEADER_VERSION_UNIT.
 *  01-15-08  01.05.15  Bumped MPI_HEADER_VERSION_UNIT.
 *  03-28-08  01.05.16  Bumped MPI_HEADER_VERSION_UNIT.
 *  --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI_H
#घोषणा MPI_H


/*****************************************************************************
*
*        M P I    V e r s i o n    D e f i n i t i o n s
*
*****************************************************************************/

#घोषणा MPI_VERSION_MAJOR                   (0x01)
#घोषणा MPI_VERSION_MINOR                   (0x05)
#घोषणा MPI_VERSION_MAJOR_MASK              (0xFF00)
#घोषणा MPI_VERSION_MAJOR_SHIFT             (8)
#घोषणा MPI_VERSION_MINOR_MASK              (0x00FF)
#घोषणा MPI_VERSION_MINOR_SHIFT             (0)
#घोषणा MPI_VERSION ((MPI_VERSION_MAJOR << MPI_VERSION_MAJOR_SHIFT) |   \
                                      MPI_VERSION_MINOR)

#घोषणा MPI_VERSION_01_00                   (0x0100)
#घोषणा MPI_VERSION_01_01                   (0x0101)
#घोषणा MPI_VERSION_01_02                   (0x0102)
#घोषणा MPI_VERSION_01_03                   (0x0103)
#घोषणा MPI_VERSION_01_05                   (0x0105)
/* Note: The major versions of 0xe0 through 0xff are reserved */

/* versioning क्रम this MPI header set */
#घोषणा MPI_HEADER_VERSION_UNIT             (0x13)
#घोषणा MPI_HEADER_VERSION_DEV              (0x00)
#घोषणा MPI_HEADER_VERSION_UNIT_MASK        (0xFF00)
#घोषणा MPI_HEADER_VERSION_UNIT_SHIFT       (8)
#घोषणा MPI_HEADER_VERSION_DEV_MASK         (0x00FF)
#घोषणा MPI_HEADER_VERSION_DEV_SHIFT        (0)
#घोषणा MPI_HEADER_VERSION ((MPI_HEADER_VERSION_UNIT << 8) | MPI_HEADER_VERSION_DEV)

/*****************************************************************************
*
*        I O C    S t a t e    D e f i n i t i o n s
*
*****************************************************************************/

#घोषणा MPI_IOC_STATE_RESET                 (0x00000000)
#घोषणा MPI_IOC_STATE_READY                 (0x10000000)
#घोषणा MPI_IOC_STATE_OPERATIONAL           (0x20000000)
#घोषणा MPI_IOC_STATE_FAULT                 (0x40000000)

#घोषणा MPI_IOC_STATE_MASK                  (0xF0000000)
#घोषणा MPI_IOC_STATE_SHIFT                 (28)

/* Fault state codes (product independent range 0x8000-0xFFFF) */

#घोषणा MPI_FAULT_REQUEST_MESSAGE_PCI_PARITY_ERROR  (0x8111)
#घोषणा MPI_FAULT_REQUEST_MESSAGE_PCI_BUS_FAULT     (0x8112)
#घोषणा MPI_FAULT_REPLY_MESSAGE_PCI_PARITY_ERROR    (0x8113)
#घोषणा MPI_FAULT_REPLY_MESSAGE_PCI_BUS_FAULT       (0x8114)
#घोषणा MPI_FAULT_DATA_SEND_PCI_PARITY_ERROR        (0x8115)
#घोषणा MPI_FAULT_DATA_SEND_PCI_BUS_FAULT           (0x8116)
#घोषणा MPI_FAULT_DATA_RECEIVE_PCI_PARITY_ERROR     (0x8117)
#घोषणा MPI_FAULT_DATA_RECEIVE_PCI_BUS_FAULT        (0x8118)


/*****************************************************************************
*
*        P C I    S y s t e m    I n t e r f a c e    R e g i s t e r s
*
*****************************************************************************/

/*
 * Defines क्रम working with the System Doorbell रेजिस्टर.
 * Values क्रम करोorbell function codes are included in the section that defines
 * all the function codes (further on in this file).
 */
#घोषणा MPI_DOORBELL_OFFSET                 (0x00000000)
#घोषणा MPI_DOORBELL_ACTIVE                 (0x08000000) /* DoorbellUsed */
#घोषणा MPI_DOORBELL_USED                   (MPI_DOORBELL_ACTIVE)
#घोषणा MPI_DOORBELL_ACTIVE_SHIFT           (27)
#घोषणा MPI_DOORBELL_WHO_INIT_MASK          (0x07000000)
#घोषणा MPI_DOORBELL_WHO_INIT_SHIFT         (24)
#घोषणा MPI_DOORBELL_FUNCTION_MASK          (0xFF000000)
#घोषणा MPI_DOORBELL_FUNCTION_SHIFT         (24)
#घोषणा MPI_DOORBELL_ADD_DWORDS_MASK        (0x00FF0000)
#घोषणा MPI_DOORBELL_ADD_DWORDS_SHIFT       (16)
#घोषणा MPI_DOORBELL_DATA_MASK              (0x0000FFFF)
#घोषणा MPI_DOORBELL_FUNCTION_SPECIFIC_MASK (0x0000FFFF)

/* values क्रम Host Buffer Access Control करोorbell function */
#घोषणा MPI_DB_HPBAC_VALUE_MASK             (0x0000F000)
#घोषणा MPI_DB_HPBAC_ENABLE_ACCESS          (0x01)
#घोषणा MPI_DB_HPBAC_DISABLE_ACCESS         (0x02)
#घोषणा MPI_DB_HPBAC_FREE_BUFFER            (0x03)


#घोषणा MPI_WRITE_SEQUENCE_OFFSET           (0x00000004)
#घोषणा MPI_WRSEQ_KEY_VALUE_MASK            (0x0000000F)
#घोषणा MPI_WRSEQ_1ST_KEY_VALUE             (0x04)
#घोषणा MPI_WRSEQ_2ND_KEY_VALUE             (0x0B)
#घोषणा MPI_WRSEQ_3RD_KEY_VALUE             (0x02)
#घोषणा MPI_WRSEQ_4TH_KEY_VALUE             (0x07)
#घोषणा MPI_WRSEQ_5TH_KEY_VALUE             (0x0D)

#घोषणा MPI_DIAGNOSTIC_OFFSET               (0x00000008)
#घोषणा MPI_DIAG_CLEAR_FLASH_BAD_SIG        (0x00000400)
#घोषणा MPI_DIAG_PREVENT_IOC_BOOT           (0x00000200)
#घोषणा MPI_DIAG_DRWE                       (0x00000080)
#घोषणा MPI_DIAG_FLASH_BAD_SIG              (0x00000040)
#घोषणा MPI_DIAG_RESET_HISTORY              (0x00000020)
#घोषणा MPI_DIAG_RW_ENABLE                  (0x00000010)
#घोषणा MPI_DIAG_RESET_ADAPTER              (0x00000004)
#घोषणा MPI_DIAG_DISABLE_ARM                (0x00000002)
#घोषणा MPI_DIAG_MEM_ENABLE                 (0x00000001)

#घोषणा MPI_TEST_BASE_ADDRESS_OFFSET        (0x0000000C)

#घोषणा MPI_DIAG_RW_DATA_OFFSET             (0x00000010)

#घोषणा MPI_DIAG_RW_ADDRESS_OFFSET          (0x00000014)

#घोषणा MPI_HOST_INTERRUPT_STATUS_OFFSET    (0x00000030)
#घोषणा MPI_HIS_IOP_DOORBELL_STATUS         (0x80000000)
#घोषणा MPI_HIS_REPLY_MESSAGE_INTERRUPT     (0x00000008)
#घोषणा MPI_HIS_DOORBELL_INTERRUPT          (0x00000001)

#घोषणा MPI_HOST_INTERRUPT_MASK_OFFSET      (0x00000034)
#घोषणा MPI_HIM_RIM                         (0x00000008)
#घोषणा MPI_HIM_DIM                         (0x00000001)

#घोषणा MPI_REQUEST_QUEUE_OFFSET            (0x00000040)
#घोषणा MPI_REQUEST_POST_FIFO_OFFSET        (0x00000040)

#घोषणा MPI_REPLY_QUEUE_OFFSET              (0x00000044)
#घोषणा MPI_REPLY_POST_FIFO_OFFSET          (0x00000044)
#घोषणा MPI_REPLY_FREE_FIFO_OFFSET          (0x00000044)

#घोषणा MPI_HI_PRI_REQUEST_QUEUE_OFFSET     (0x00000048)



/*****************************************************************************
*
*        M e s s a g e    F r a m e    D e s c r i p t o r s
*
*****************************************************************************/

#घोषणा MPI_REQ_MF_DESCRIPTOR_NB_MASK       (0x00000003)
#घोषणा MPI_REQ_MF_DESCRIPTOR_F_BIT         (0x00000004)
#घोषणा MPI_REQ_MF_DESCRIPTOR_ADDRESS_MASK  (0xFFFFFFF8)

#घोषणा MPI_ADDRESS_REPLY_A_BIT             (0x80000000)
#घोषणा MPI_ADDRESS_REPLY_ADDRESS_MASK      (0x7FFFFFFF)

#घोषणा MPI_CONTEXT_REPLY_A_BIT             (0x80000000)
#घोषणा MPI_CONTEXT_REPLY_TYPE_MASK         (0x60000000)
#घोषणा MPI_CONTEXT_REPLY_TYPE_SCSI_INIT    (0x00)
#घोषणा MPI_CONTEXT_REPLY_TYPE_SCSI_TARGET  (0x01)
#घोषणा MPI_CONTEXT_REPLY_TYPE_LAN          (0x02)
#घोषणा MPI_CONTEXT_REPLY_TYPE_SHIFT        (29)
#घोषणा MPI_CONTEXT_REPLY_CONTEXT_MASK      (0x1FFFFFFF)


/****************************************************************************/
/* Context Reply macros                                                     */
/****************************************************************************/

#घोषणा MPI_GET_CONTEXT_REPLY_TYPE(x)  (((x) & MPI_CONTEXT_REPLY_TYPE_MASK) \
                                          >> MPI_CONTEXT_REPLY_TYPE_SHIFT)

#घोषणा MPI_SET_CONTEXT_REPLY_TYPE(x, typ)                                  \
            ((x) = ((x) & ~MPI_CONTEXT_REPLY_TYPE_MASK) |                   \
                            (((typ) << MPI_CONTEXT_REPLY_TYPE_SHIFT) &      \
                                        MPI_CONTEXT_REPLY_TYPE_MASK))


/*****************************************************************************
*
*        M e s s a g e    F u n c t i o n s
*              0x80 -> 0x8F reserved क्रम निजी message use per product
*
*
*****************************************************************************/

#घोषणा MPI_FUNCTION_SCSI_IO_REQUEST                (0x00)
#घोषणा MPI_FUNCTION_SCSI_TASK_MGMT                 (0x01)
#घोषणा MPI_FUNCTION_IOC_INIT                       (0x02)
#घोषणा MPI_FUNCTION_IOC_FACTS                      (0x03)
#घोषणा MPI_FUNCTION_CONFIG                         (0x04)
#घोषणा MPI_FUNCTION_PORT_FACTS                     (0x05)
#घोषणा MPI_FUNCTION_PORT_ENABLE                    (0x06)
#घोषणा MPI_FUNCTION_EVENT_NOTIFICATION             (0x07)
#घोषणा MPI_FUNCTION_EVENT_ACK                      (0x08)
#घोषणा MPI_FUNCTION_FW_DOWNLOAD                    (0x09)
#घोषणा MPI_FUNCTION_TARGET_CMD_BUFFER_POST         (0x0A)
#घोषणा MPI_FUNCTION_TARGET_ASSIST                  (0x0B)
#घोषणा MPI_FUNCTION_TARGET_STATUS_SEND             (0x0C)
#घोषणा MPI_FUNCTION_TARGET_MODE_ABORT              (0x0D)
#घोषणा MPI_FUNCTION_FC_LINK_SRVC_BUF_POST          (0x0E)
#घोषणा MPI_FUNCTION_FC_LINK_SRVC_RSP               (0x0F)
#घोषणा MPI_FUNCTION_FC_EX_LINK_SRVC_SEND           (0x10)
#घोषणा MPI_FUNCTION_FC_ABORT                       (0x11)
#घोषणा MPI_FUNCTION_FW_UPLOAD                      (0x12)
#घोषणा MPI_FUNCTION_FC_COMMON_TRANSPORT_SEND       (0x13)
#घोषणा MPI_FUNCTION_FC_PRIMITIVE_SEND              (0x14)

#घोषणा MPI_FUNCTION_RAID_ACTION                    (0x15)
#घोषणा MPI_FUNCTION_RAID_SCSI_IO_PASSTHROUGH       (0x16)

#घोषणा MPI_FUNCTION_TOOLBOX                        (0x17)

#घोषणा MPI_FUNCTION_SCSI_ENCLOSURE_PROCESSOR       (0x18)

#घोषणा MPI_FUNCTION_MAILBOX                        (0x19)

#घोषणा MPI_FUNCTION_SMP_PASSTHROUGH                (0x1A)
#घोषणा MPI_FUNCTION_SAS_IO_UNIT_CONTROL            (0x1B)
#घोषणा MPI_FUNCTION_SATA_PASSTHROUGH               (0x1C)

#घोषणा MPI_FUNCTION_DIAG_BUFFER_POST               (0x1D)
#घोषणा MPI_FUNCTION_DIAG_RELEASE                   (0x1E)

#घोषणा MPI_FUNCTION_SCSI_IO_32                     (0x1F)

#घोषणा MPI_FUNCTION_LAN_SEND                       (0x20)
#घोषणा MPI_FUNCTION_LAN_RECEIVE                    (0x21)
#घोषणा MPI_FUNCTION_LAN_RESET                      (0x22)

#घोषणा MPI_FUNCTION_TARGET_ASSIST_EXTENDED         (0x23)
#घोषणा MPI_FUNCTION_TARGET_CMD_BUF_BASE_POST       (0x24)
#घोषणा MPI_FUNCTION_TARGET_CMD_BUF_LIST_POST       (0x25)

#घोषणा MPI_FUNCTION_INBAND_BUFFER_POST             (0x28)
#घोषणा MPI_FUNCTION_INBAND_SEND                    (0x29)
#घोषणा MPI_FUNCTION_INBAND_RSP                     (0x2A)
#घोषणा MPI_FUNCTION_INBAND_ABORT                   (0x2B)

#घोषणा MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET         (0x40)
#घोषणा MPI_FUNCTION_IO_UNIT_RESET                  (0x41)
#घोषणा MPI_FUNCTION_HANDSHAKE                      (0x42)
#घोषणा MPI_FUNCTION_REPLY_FRAME_REMOVAL            (0x43)
#घोषणा MPI_FUNCTION_HOST_PAGEBUF_ACCESS_CONTROL    (0x44)


/* standard version क्रमmat */
प्रकार काष्ठा _MPI_VERSION_STRUCT
अणु
    U8                      Dev;                        /* 00h */
    U8                      Unit;                       /* 01h */
    U8                      Minor;                      /* 02h */
    U8                      Major;                      /* 03h */
पूर्ण MPI_VERSION_STRUCT, MPI_POINTER PTR_MPI_VERSION_STRUCT,
  MpiVersionStruct_t, MPI_POINTER pMpiVersionStruct;

प्रकार जोड़ _MPI_VERSION_FORMAT
अणु
    MPI_VERSION_STRUCT      Struct;
    U32                     Word;
पूर्ण MPI_VERSION_FORMAT, MPI_POINTER PTR_MPI_VERSION_FORMAT,
  MpiVersionFormat_t, MPI_POINTER pMpiVersionFormat_t;


/*****************************************************************************
*
*        S c a t t e r    G a t h e r    E l e m e n t s
*
*****************************************************************************/

/****************************************************************************/
/*  Simple element काष्ठाures                                               */
/****************************************************************************/

प्रकार काष्ठा _SGE_SIMPLE32
अणु
    U32                     FlagsLength;
    U32                     Address;
पूर्ण SGE_SIMPLE32, MPI_POINTER PTR_SGE_SIMPLE32,
  SGESimple32_t, MPI_POINTER pSGESimple32_t;

प्रकार काष्ठा _SGE_SIMPLE64
अणु
    U32                     FlagsLength;
    U64                     Address;
पूर्ण SGE_SIMPLE64, MPI_POINTER PTR_SGE_SIMPLE64,
  SGESimple64_t, MPI_POINTER pSGESimple64_t;

प्रकार काष्ठा _SGE_SIMPLE_UNION
अणु
    U32                     FlagsLength;
    जोड़
    अणु
        U32                 Address32;
        U64                 Address64;
    पूर्णu;
पूर्ण SGE_SIMPLE_UNION, MPI_POINTER PTR_SGE_SIMPLE_UNION,
  SGESimpleUnion_t, MPI_POINTER pSGESimpleUnion_t;

/****************************************************************************/
/*  Chain element काष्ठाures                                                */
/****************************************************************************/

प्रकार काष्ठा _SGE_CHAIN32
अणु
    U16                     Length;
    U8                      NextChainOffset;
    U8                      Flags;
    U32                     Address;
पूर्ण SGE_CHAIN32, MPI_POINTER PTR_SGE_CHAIN32,
  SGEChain32_t, MPI_POINTER pSGEChain32_t;

प्रकार काष्ठा _SGE_CHAIN64
अणु
    U16                     Length;
    U8                      NextChainOffset;
    U8                      Flags;
    U64                     Address;
पूर्ण SGE_CHAIN64, MPI_POINTER PTR_SGE_CHAIN64,
  SGEChain64_t, MPI_POINTER pSGEChain64_t;

प्रकार काष्ठा _SGE_CHAIN_UNION
अणु
    U16                     Length;
    U8                      NextChainOffset;
    U8                      Flags;
    जोड़
    अणु
        U32                 Address32;
        U64                 Address64;
    पूर्णu;
पूर्ण SGE_CHAIN_UNION, MPI_POINTER PTR_SGE_CHAIN_UNION,
  SGEChainUnion_t, MPI_POINTER pSGEChainUnion_t;

/****************************************************************************/
/*  Transaction Context element                                             */
/****************************************************************************/

प्रकार काष्ठा _SGE_TRANSACTION32
अणु
    U8                      Reserved;
    U8                      ContextSize;
    U8                      DetailsLength;
    U8                      Flags;
    U32                     TransactionContext;
    U32                     TransactionDetails[];
पूर्ण SGE_TRANSACTION32, MPI_POINTER PTR_SGE_TRANSACTION32,
  SGETransaction32_t, MPI_POINTER pSGETransaction32_t;

प्रकार काष्ठा _SGE_TRANSACTION64
अणु
    U8                      Reserved;
    U8                      ContextSize;
    U8                      DetailsLength;
    U8                      Flags;
    U32                     TransactionContext[2];
    U32                     TransactionDetails[1];
पूर्ण SGE_TRANSACTION64, MPI_POINTER PTR_SGE_TRANSACTION64,
  SGETransaction64_t, MPI_POINTER pSGETransaction64_t;

प्रकार काष्ठा _SGE_TRANSACTION96
अणु
    U8                      Reserved;
    U8                      ContextSize;
    U8                      DetailsLength;
    U8                      Flags;
    U32                     TransactionContext[3];
    U32                     TransactionDetails[1];
पूर्ण SGE_TRANSACTION96, MPI_POINTER PTR_SGE_TRANSACTION96,
  SGETransaction96_t, MPI_POINTER pSGETransaction96_t;

प्रकार काष्ठा _SGE_TRANSACTION128
अणु
    U8                      Reserved;
    U8                      ContextSize;
    U8                      DetailsLength;
    U8                      Flags;
    U32                     TransactionContext[4];
    U32                     TransactionDetails[1];
पूर्ण SGE_TRANSACTION128, MPI_POINTER PTR_SGE_TRANSACTION128,
  SGETransaction_t128, MPI_POINTER pSGETransaction_t128;

प्रकार काष्ठा _SGE_TRANSACTION_UNION
अणु
    U8                      Reserved;
    U8                      ContextSize;
    U8                      DetailsLength;
    U8                      Flags;
    जोड़
    अणु
        U32                 TransactionContext32[1];
        U32                 TransactionContext64[2];
        U32                 TransactionContext96[3];
        U32                 TransactionContext128[4];
    पूर्णu;
    U32                     TransactionDetails[1];
पूर्ण SGE_TRANSACTION_UNION, MPI_POINTER PTR_SGE_TRANSACTION_UNION,
  SGETransactionUnion_t, MPI_POINTER pSGETransactionUnion_t;


/****************************************************************************/
/*  SGE IO types जोड़  क्रम IO SGL's                                        */
/****************************************************************************/

प्रकार काष्ठा _SGE_IO_UNION
अणु
    जोड़
    अणु
        SGE_SIMPLE_UNION    Simple;
        SGE_CHAIN_UNION     Chain;
    पूर्ण u;
पूर्ण SGE_IO_UNION, MPI_POINTER PTR_SGE_IO_UNION,
  SGEIOUnion_t, MPI_POINTER pSGEIOUnion_t;

/****************************************************************************/
/*  SGE जोड़ क्रम SGL's with Simple and Transaction elements                */
/****************************************************************************/

प्रकार काष्ठा _SGE_TRANS_SIMPLE_UNION
अणु
    जोड़
    अणु
        SGE_SIMPLE_UNION        Simple;
        SGE_TRANSACTION_UNION   Transaction;
    पूर्ण u;
पूर्ण SGE_TRANS_SIMPLE_UNION, MPI_POINTER PTR_SGE_TRANS_SIMPLE_UNION,
  SGETransSimpleUnion_t, MPI_POINTER pSGETransSimpleUnion_t;

/****************************************************************************/
/*  All SGE types जोड़                                                     */
/****************************************************************************/

प्रकार काष्ठा _SGE_MPI_UNION
अणु
    जोड़
    अणु
        SGE_SIMPLE_UNION        Simple;
        SGE_CHAIN_UNION         Chain;
        SGE_TRANSACTION_UNION   Transaction;
    पूर्ण u;
पूर्ण SGE_MPI_UNION, MPI_POINTER PTR_SGE_MPI_UNION,
  MPI_SGE_UNION_t, MPI_POINTER pMPI_SGE_UNION_t,
  SGEAllUnion_t, MPI_POINTER pSGEAllUnion_t;


/****************************************************************************/
/*  SGE field definition and masks                                          */
/****************************************************************************/

/* Flags field bit definitions */

#घोषणा MPI_SGE_FLAGS_LAST_ELEMENT              (0x80)
#घोषणा MPI_SGE_FLAGS_END_OF_BUFFER             (0x40)
#घोषणा MPI_SGE_FLAGS_ELEMENT_TYPE_MASK         (0x30)
#घोषणा MPI_SGE_FLAGS_LOCAL_ADDRESS             (0x08)
#घोषणा MPI_SGE_FLAGS_सूचीECTION                 (0x04)
#घोषणा MPI_SGE_FLAGS_ADDRESS_SIZE              (0x02)
#घोषणा MPI_SGE_FLAGS_END_OF_LIST               (0x01)

#घोषणा MPI_SGE_FLAGS_SHIFT                     (24)

#घोषणा MPI_SGE_LENGTH_MASK                     (0x00FFFFFF)
#घोषणा MPI_SGE_CHAIN_LENGTH_MASK               (0x0000FFFF)

/* Element Type */

#घोषणा MPI_SGE_FLAGS_TRANSACTION_ELEMENT       (0x00)
#घोषणा MPI_SGE_FLAGS_SIMPLE_ELEMENT            (0x10)
#घोषणा MPI_SGE_FLAGS_CHAIN_ELEMENT             (0x30)
#घोषणा MPI_SGE_FLAGS_ELEMENT_MASK              (0x30)

/* Address location */

#घोषणा MPI_SGE_FLAGS_SYSTEM_ADDRESS            (0x00)

/* Direction */

#घोषणा MPI_SGE_FLAGS_IOC_TO_HOST               (0x00)
#घोषणा MPI_SGE_FLAGS_HOST_TO_IOC               (0x04)

/* Address Size */

#घोषणा MPI_SGE_FLAGS_32_BIT_ADDRESSING         (0x00)
#घोषणा MPI_SGE_FLAGS_64_BIT_ADDRESSING         (0x02)

/* Context Size */

#घोषणा MPI_SGE_FLAGS_32_BIT_CONTEXT            (0x00)
#घोषणा MPI_SGE_FLAGS_64_BIT_CONTEXT            (0x02)
#घोषणा MPI_SGE_FLAGS_96_BIT_CONTEXT            (0x04)
#घोषणा MPI_SGE_FLAGS_128_BIT_CONTEXT           (0x06)

#घोषणा MPI_SGE_CHAIN_OFFSET_MASK               (0x00FF0000)
#घोषणा MPI_SGE_CHAIN_OFFSET_SHIFT              (16)


/****************************************************************************/
/*  SGE operation Macros                                                    */
/****************************************************************************/

         /* SIMPLE FlagsLength manipulations... */
#घोषणा  MPI_SGE_SET_FLAGS(f)           ((U32)(f) << MPI_SGE_FLAGS_SHIFT)
#घोषणा  MPI_SGE_GET_FLAGS(fl)          (((fl) & ~MPI_SGE_LENGTH_MASK) >> MPI_SGE_FLAGS_SHIFT)
#घोषणा  MPI_SGE_LENGTH(fl)             ((fl) & MPI_SGE_LENGTH_MASK)
#घोषणा  MPI_SGE_CHAIN_LENGTH(fl)       ((fl) & MPI_SGE_CHAIN_LENGTH_MASK)

#घोषणा  MPI_SGE_SET_FLAGS_LENGTH(f,l)  (MPI_SGE_SET_FLAGS(f) | MPI_SGE_LENGTH(l))

#घोषणा  MPI_pSGE_GET_FLAGS(psg)        MPI_SGE_GET_FLAGS((psg)->FlagsLength)
#घोषणा  MPI_pSGE_GET_LENGTH(psg)       MPI_SGE_LENGTH((psg)->FlagsLength)
#घोषणा  MPI_pSGE_SET_FLAGS_LENGTH(psg,f,l)  (psg)->FlagsLength = MPI_SGE_SET_FLAGS_LENGTH(f,l)
         /* CAUTION - The following are READ-MODIFY-WRITE! */
#घोषणा  MPI_pSGE_SET_FLAGS(psg,f)      (psg)->FlagsLength |= MPI_SGE_SET_FLAGS(f)
#घोषणा  MPI_pSGE_SET_LENGTH(psg,l)     (psg)->FlagsLength |= MPI_SGE_LENGTH(l)

#घोषणा  MPI_GET_CHAIN_OFFSET(x) ((x&MPI_SGE_CHAIN_OFFSET_MASK)>>MPI_SGE_CHAIN_OFFSET_SHIFT)



/*****************************************************************************
*
*        S t a n d a r d    M e s s a g e    S t r u c t u r e s
*
*****************************************************************************/

/****************************************************************************/
/* Standard message request header क्रम all request messages                 */
/****************************************************************************/

प्रकार काष्ठा _MSG_REQUEST_HEADER
अणु
    U8                      Reserved[2];      /* function specअगरic */
    U8                      ChainOffset;
    U8                      Function;
    U8                      Reserved1[3];     /* function specअगरic */
    U8                      MsgFlags;
    U32                     MsgContext;
पूर्ण MSG_REQUEST_HEADER, MPI_POINTER PTR_MSG_REQUEST_HEADER,
  MPIHeader_t, MPI_POINTER pMPIHeader_t;


/****************************************************************************/
/*  Default Reply                                                           */
/****************************************************************************/

प्रकार काष्ठा _MSG_DEFAULT_REPLY
अणु
    U8                      Reserved[2];      /* function specअगरic */
    U8                      MsgLength;
    U8                      Function;
    U8                      Reserved1[3];     /* function specअगरic */
    U8                      MsgFlags;
    U32                     MsgContext;
    U8                      Reserved2[2];     /* function specअगरic */
    U16                     IOCStatus;
    U32                     IOCLogInfo;
पूर्ण MSG_DEFAULT_REPLY, MPI_POINTER PTR_MSG_DEFAULT_REPLY,
  MPIDefaultReply_t, MPI_POINTER pMPIDefaultReply_t;


/* MsgFlags definition क्रम all replies */

#घोषणा MPI_MSGFLAGS_CONTINUATION_REPLY         (0x80)


/*****************************************************************************
*
*               I O C    S t a t u s   V a l u e s
*
*****************************************************************************/

/****************************************************************************/
/*  Common IOCStatus values क्रम all replies                                 */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_SUCCESS                   (0x0000)
#घोषणा MPI_IOCSTATUS_INVALID_FUNCTION          (0x0001)
#घोषणा MPI_IOCSTATUS_BUSY                      (0x0002)
#घोषणा MPI_IOCSTATUS_INVALID_SGL               (0x0003)
#घोषणा MPI_IOCSTATUS_INTERNAL_ERROR            (0x0004)
#घोषणा MPI_IOCSTATUS_RESERVED                  (0x0005)
#घोषणा MPI_IOCSTATUS_INSUFFICIENT_RESOURCES    (0x0006)
#घोषणा MPI_IOCSTATUS_INVALID_FIELD             (0x0007)
#घोषणा MPI_IOCSTATUS_INVALID_STATE             (0x0008)
#घोषणा MPI_IOCSTATUS_OP_STATE_NOT_SUPPORTED    (0x0009)

/****************************************************************************/
/*  Config IOCStatus values                                                 */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_CONFIG_INVALID_ACTION     (0x0020)
#घोषणा MPI_IOCSTATUS_CONFIG_INVALID_TYPE       (0x0021)
#घोषणा MPI_IOCSTATUS_CONFIG_INVALID_PAGE       (0x0022)
#घोषणा MPI_IOCSTATUS_CONFIG_INVALID_DATA       (0x0023)
#घोषणा MPI_IOCSTATUS_CONFIG_NO_DEFAULTS        (0x0024)
#घोषणा MPI_IOCSTATUS_CONFIG_CANT_COMMIT        (0x0025)

/****************************************************************************/
/*  SCSIIO Reply (SPI & FCP) initiator values                               */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_SCSI_RECOVERED_ERROR      (0x0040)
#घोषणा MPI_IOCSTATUS_SCSI_INVALID_BUS          (0x0041)
#घोषणा MPI_IOCSTATUS_SCSI_INVALID_TARGETID     (0x0042)
#घोषणा MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE     (0x0043)
#घोषणा MPI_IOCSTATUS_SCSI_DATA_OVERRUN         (0x0044)
#घोषणा MPI_IOCSTATUS_SCSI_DATA_UNDERRUN        (0x0045)
#घोषणा MPI_IOCSTATUS_SCSI_IO_DATA_ERROR        (0x0046)
#घोषणा MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR       (0x0047)
#घोषणा MPI_IOCSTATUS_SCSI_TASK_TERMINATED      (0x0048)
#घोषणा MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH    (0x0049)
#घोषणा MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED     (0x004A)
#घोषणा MPI_IOCSTATUS_SCSI_IOC_TERMINATED       (0x004B)
#घोषणा MPI_IOCSTATUS_SCSI_EXT_TERMINATED       (0x004C)

/****************************************************************************/
/*  For use by SCSI Initiator and SCSI Target end-to-end data protection    */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_EEDP_GUARD_ERROR          (0x004D)
#घोषणा MPI_IOCSTATUS_EEDP_REF_TAG_ERROR        (0x004E)
#घोषणा MPI_IOCSTATUS_EEDP_APP_TAG_ERROR        (0x004F)


/****************************************************************************/
/*  SCSI Target values                                                      */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_TARGET_PRIORITY_IO         (0x0060)
#घोषणा MPI_IOCSTATUS_TARGET_INVALID_PORT        (0x0061)
#घोषणा MPI_IOCSTATUS_TARGET_INVALID_IOCINDEX    (0x0062)   /* obsolete name */
#घोषणा MPI_IOCSTATUS_TARGET_INVALID_IO_INDEX    (0x0062)
#घोषणा MPI_IOCSTATUS_TARGET_ABORTED             (0x0063)
#घोषणा MPI_IOCSTATUS_TARGET_NO_CONN_RETRYABLE   (0x0064)
#घोषणा MPI_IOCSTATUS_TARGET_NO_CONNECTION       (0x0065)
#घोषणा MPI_IOCSTATUS_TARGET_XFER_COUNT_MISMATCH (0x006A)
#घोषणा MPI_IOCSTATUS_TARGET_STS_DATA_NOT_SENT   (0x006B)
#घोषणा MPI_IOCSTATUS_TARGET_DATA_OFFSET_ERROR   (0x006D)
#घोषणा MPI_IOCSTATUS_TARGET_TOO_MUCH_WRITE_DATA (0x006E)
#घोषणा MPI_IOCSTATUS_TARGET_IU_TOO_SHORT        (0x006F)
#घोषणा MPI_IOCSTATUS_TARGET_ACK_NAK_TIMEOUT     (0x0070)
#घोषणा MPI_IOCSTATUS_TARGET_NAK_RECEIVED        (0x0071)

/****************************************************************************/
/*  Additional FCP target values (obsolete)                                 */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_TARGET_FC_ABORTED         (0x0066)    /* obsolete */
#घोषणा MPI_IOCSTATUS_TARGET_FC_RX_ID_INVALID   (0x0067)    /* obsolete */
#घोषणा MPI_IOCSTATUS_TARGET_FC_DID_INVALID     (0x0068)    /* obsolete */
#घोषणा MPI_IOCSTATUS_TARGET_FC_NODE_LOGGED_OUT (0x0069)    /* obsolete */

/****************************************************************************/
/*  Fibre Channel Direct Access values                                      */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_FC_ABORTED                (0x0066)
#घोषणा MPI_IOCSTATUS_FC_RX_ID_INVALID          (0x0067)
#घोषणा MPI_IOCSTATUS_FC_DID_INVALID            (0x0068)
#घोषणा MPI_IOCSTATUS_FC_NODE_LOGGED_OUT        (0x0069)
#घोषणा MPI_IOCSTATUS_FC_EXCHANGE_CANCELED      (0x006C)

/****************************************************************************/
/*  LAN values                                                              */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_LAN_DEVICE_NOT_FOUND      (0x0080)
#घोषणा MPI_IOCSTATUS_LAN_DEVICE_FAILURE        (0x0081)
#घोषणा MPI_IOCSTATUS_LAN_TRANSMIT_ERROR        (0x0082)
#घोषणा MPI_IOCSTATUS_LAN_TRANSMIT_ABORTED      (0x0083)
#घोषणा MPI_IOCSTATUS_LAN_RECEIVE_ERROR         (0x0084)
#घोषणा MPI_IOCSTATUS_LAN_RECEIVE_ABORTED       (0x0085)
#घोषणा MPI_IOCSTATUS_LAN_PARTIAL_PACKET        (0x0086)
#घोषणा MPI_IOCSTATUS_LAN_CANCELED              (0x0087)

/****************************************************************************/
/*  Serial Attached SCSI values                                             */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_SAS_SMP_REQUEST_FAILED    (0x0090)
#घोषणा MPI_IOCSTATUS_SAS_SMP_DATA_OVERRUN      (0x0091)

/****************************************************************************/
/*  Inband values                                                           */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_INBAND_ABORTED            (0x0098)
#घोषणा MPI_IOCSTATUS_INBAND_NO_CONNECTION      (0x0099)

/****************************************************************************/
/*  Diagnostic Tools values                                                 */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_DIAGNOSTIC_RELEASED       (0x00A0)


/****************************************************************************/
/*  IOCStatus flag to indicate that log info is available                   */
/****************************************************************************/

#घोषणा MPI_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE   (0x8000)
#घोषणा MPI_IOCSTATUS_MASK                      (0x7FFF)

/****************************************************************************/
/*  LogInfo Types                                                           */
/****************************************************************************/

#घोषणा MPI_IOCLOGINFO_TYPE_MASK                (0xF0000000)
#घोषणा MPI_IOCLOGINFO_TYPE_SHIFT               (28)
#घोषणा MPI_IOCLOGINFO_TYPE_NONE                (0x0)
#घोषणा MPI_IOCLOGINFO_TYPE_SCSI                (0x1)
#घोषणा MPI_IOCLOGINFO_TYPE_FC                  (0x2)
#घोषणा MPI_IOCLOGINFO_TYPE_SAS                 (0x3)
#घोषणा MPI_IOCLOGINFO_TYPE_ISCSI               (0x4)
#घोषणा MPI_IOCLOGINFO_LOG_DATA_MASK            (0x0FFFFFFF)


#पूर्ण_अगर
