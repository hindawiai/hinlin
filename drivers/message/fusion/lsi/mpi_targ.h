<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2000-2008 LSI Corporation.
 *
 *
 *           Name:  mpi_targ.h
 *          Title:  MPI Target mode messages and काष्ठाures
 *  Creation Date:  June 22, 2000
 *
 *    mpi_targ.h Version:  01.05.06
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Original release क्रम 0.10 spec dated 4/26/2000.
 *  06-06-00  01.00.01  Update version number क्रम 1.0 release.
 *  06-22-00  01.00.02  Added _MSG_TARGET_CMD_BUFFER_POST_REPLY काष्ठाure.
 *                      Corrected DECSRIPTOR typo to DESCRIPTOR.
 *  11-02-00  01.01.01  Original release क्रम post 1.0 work
 *                      Modअगरied target mode to use IoIndex instead of
 *                      HostIndex and IocIndex. Added Alias.
 *  01-09-01  01.01.02  Added defines क्रम TARGET_ASSIST_FLAGS_REPOST_CMD_BUFFER
 *                      and TARGET_STATUS_SEND_FLAGS_REPOST_CMD_BUFFER.
 *  02-20-01  01.01.03  Started using MPI_POINTER.
 *                      Added काष्ठाures क्रम MPI_TARGET_SCSI_SPI_CMD_BUFFER and
 *                      MPI_TARGET_FCP_CMD_BUFFER.
 *  03-27-01  01.01.04  Added काष्ठाure offset comments.
 *  08-08-01  01.02.01  Original release क्रम v1.2 work.
 *  09-28-01  01.02.02  Added काष्ठाure क्रम MPI_TARGET_SCSI_SPI_STATUS_IU.
 *                      Added PriorityReason field to some replies and
 *                      defined more PriorityReason codes.
 *                      Added some defines क्रम to support previous version
 *                      of MPI.
 *  10-04-01  01.02.03  Added PriorityReason to MSG_TARGET_ERROR_REPLY.
 *  11-01-01  01.02.04  Added define क्रम TARGET_STATUS_SEND_FLAGS_HIGH_PRIORITY.
 *  03-14-02  01.02.05  Modअगरied MPI_TARGET_FCP_RSP_BUFFER to get the proper
 *                      byte ordering.
 *  05-31-02  01.02.06  Modअगरied TARGET_MODE_REPLY_ALIAS_MASK to only include
 *                      one bit.
 *                      Added AliasIndex field to MPI_TARGET_FCP_CMD_BUFFER.
 *  09-16-02  01.02.07  Added flags क्रम confirmed completion.
 *                      Added PRIORITY_REASON_TARGET_BUSY.
 *  11-15-02  01.02.08  Added AliasID field to MPI_TARGET_SCSI_SPI_CMD_BUFFER.
 *  04-01-03  01.02.09  Added OptionalOxid field to MPI_TARGET_FCP_CMD_BUFFER.
 *  05-11-04  01.03.01  Original release क्रम MPI v1.3.
 *  08-19-04  01.05.01  Added new request message काष्ठाures क्रम
 *                      MSG_TARGET_CMD_BUF_POST_BASE_REQUEST,
 *                      MSG_TARGET_CMD_BUF_POST_LIST_REQUEST, and
 *                      MSG_TARGET_ASSIST_EXT_REQUEST.
 *                      Added new काष्ठाures क्रम SAS SSP Command buffer, SSP
 *                      Task buffer, and SSP Status IU.
 *  10-05-04  01.05.02  MSG_TARGET_CMD_BUFFER_POST_BASE_LIST_REPLY added.
 *  02-22-05  01.05.03  Changed a comment.
 *  03-11-05  01.05.04  Removed TargetAssistExtended Request.
 *  06-24-05  01.05.05  Added TargetAssistExtended काष्ठाures and defines.
 *  03-27-06  01.05.06  Added a comment.
 *  --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI_TARG_H
#घोषणा MPI_TARG_H


/******************************************************************************
*
*        S C S I    T a r g e t    M e s s a g e s
*
*******************************************************************************/

प्रकार काष्ठा _CMD_BUFFER_DESCRIPTOR
अणु
    U16                     IoIndex;                    /* 00h */
    U16                     Reserved;                   /* 02h */
    जोड़                                               /* 04h */
    अणु
        U32                 PhysicalAddress32;
        U64                 PhysicalAddress64;
    पूर्ण u;
पूर्ण CMD_BUFFER_DESCRIPTOR, MPI_POINTER PTR_CMD_BUFFER_DESCRIPTOR,
  CmdBufferDescriptor_t, MPI_POINTER pCmdBufferDescriptor_t;


/****************************************************************************/
/* Target Command Buffer Post Request                                       */
/****************************************************************************/

प्रकार काष्ठा _MSG_TARGET_CMD_BUFFER_POST_REQUEST
अणु
    U8                      BufferPostFlags;            /* 00h */
    U8                      BufferCount;                /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U8                      BufferLength;               /* 04h */
    U8                      Reserved;                   /* 05h */
    U8                      Reserved1;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    CMD_BUFFER_DESCRIPTOR   Buffer[1];                  /* 0Ch */
पूर्ण MSG_TARGET_CMD_BUFFER_POST_REQUEST, MPI_POINTER PTR_MSG_TARGET_CMD_BUFFER_POST_REQUEST,
  TargetCmdBufferPostRequest_t, MPI_POINTER pTargetCmdBufferPostRequest_t;

#घोषणा CMD_BUFFER_POST_FLAGS_PORT_MASK         (0x01)
#घोषणा CMD_BUFFER_POST_FLAGS_ADDR_MODE_MASK    (0x80)
#घोषणा CMD_BUFFER_POST_FLAGS_ADDR_MODE_32      (0)
#घोषणा CMD_BUFFER_POST_FLAGS_ADDR_MODE_64      (1)
#घोषणा CMD_BUFFER_POST_FLAGS_64_BIT_ADDR       (0x80)

#घोषणा CMD_BUFFER_POST_IO_INDEX_MASK           (0x00003FFF)
#घोषणा CMD_BUFFER_POST_IO_INDEX_MASK_0100      (0x000003FF) /* obsolete */


प्रकार काष्ठा _MSG_TARGET_CMD_BUFFER_POST_REPLY
अणु
    U8                      BufferPostFlags;            /* 00h */
    U8                      BufferCount;                /* 01h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U8                      BufferLength;               /* 04h */
    U8                      Reserved;                   /* 05h */
    U8                      Reserved1;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Reserved2;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
पूर्ण MSG_TARGET_CMD_BUFFER_POST_REPLY, MPI_POINTER PTR_MSG_TARGET_CMD_BUFFER_POST_REPLY,
  TargetCmdBufferPostReply_t, MPI_POINTER pTargetCmdBufferPostReply_t;

/* the following काष्ठाure is obsolete as of MPI v1.2 */
प्रकार काष्ठा _MSG_PRIORITY_CMD_RECEIVED_REPLY
अणु
    U16                     Reserved;                   /* 00h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      PriorityReason;             /* 0Ch */
    U8                      Reserved3;                  /* 0Dh */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
    U32                     ReplyWord;                  /* 14h */
पूर्ण MSG_PRIORITY_CMD_RECEIVED_REPLY, MPI_POINTER PTR_MSG_PRIORITY_CMD_RECEIVED_REPLY,
  PriorityCommandReceivedReply_t, MPI_POINTER pPriorityCommandReceivedReply_t;


प्रकार काष्ठा _MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY
अणु
    U16                     Reserved;                   /* 00h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      PriorityReason;             /* 0Ch */
    U8                      Reserved3;                  /* 0Dh */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
    U32                     ReplyWord;                  /* 14h */
पूर्ण MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY,
  MPI_POINTER PTR_MSG_TARGET_CMD_BUFFER_POST_ERROR_REPLY,
  TargetCmdBufferPostErrorReply_t, MPI_POINTER pTargetCmdBufferPostErrorReply_t;

#घोषणा PRIORITY_REASON_NO_DISCONNECT           (0x00)
#घोषणा PRIORITY_REASON_SCSI_TASK_MANAGEMENT    (0x01)
#घोषणा PRIORITY_REASON_CMD_PARITY_ERR          (0x02)
#घोषणा PRIORITY_REASON_MSG_OUT_PARITY_ERR      (0x03)
#घोषणा PRIORITY_REASON_LQ_CRC_ERR              (0x04)
#घोषणा PRIORITY_REASON_CMD_CRC_ERR             (0x05)
#घोषणा PRIORITY_REASON_PROTOCOL_ERR            (0x06)
#घोषणा PRIORITY_REASON_DATA_OUT_PARITY_ERR     (0x07)
#घोषणा PRIORITY_REASON_DATA_OUT_CRC_ERR        (0x08)
#घोषणा PRIORITY_REASON_TARGET_BUSY             (0x09)
#घोषणा PRIORITY_REASON_UNKNOWN                 (0xFF)


/****************************************************************************/
/* Target Command Buffer Post Base Request                                  */
/****************************************************************************/

प्रकार काष्ठा _MSG_TARGET_CMD_BUF_POST_BASE_REQUEST
अणु
    U8                      BufferPostFlags;            /* 00h */
    U8                      PortNumber;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     TotalCmdBuffers;            /* 04h */
    U8                      Reserved;                   /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Reserved1;                  /* 0Ch */
    U16                     CmdBufferLength;            /* 10h */
    U16                     NextCmdBufferOffset;        /* 12h */
    U32                     BaseAddressLow;             /* 14h */
    U32                     BaseAddressHigh;            /* 18h */
पूर्ण MSG_TARGET_CMD_BUF_POST_BASE_REQUEST,
  MPI_POINTER PTR__MSG_TARGET_CMD_BUF_POST_BASE_REQUEST,
  TargetCmdBufferPostBaseRequest_t,
  MPI_POINTER pTargetCmdBufferPostBaseRequest_t;

#घोषणा CMD_BUFFER_POST_BASE_FLAGS_AUTO_POST_ALL    (0x01)


प्रकार काष्ठा _MSG_TARGET_CMD_BUFFER_POST_BASE_LIST_REPLY
अणु
    U16                     Reserved;                   /* 00h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Reserved3;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
पूर्ण MSG_TARGET_CMD_BUFFER_POST_BASE_LIST_REPLY,
  MPI_POINTER PTR_MSG_TARGET_CMD_BUFFER_POST_BASE_LIST_REPLY,
  TargetCmdBufferPostBaseListReply_t,
  MPI_POINTER pTargetCmdBufferPostBaseListReply_t;


/****************************************************************************/
/* Target Command Buffer Post List Request                                  */
/****************************************************************************/

प्रकार काष्ठा _MSG_TARGET_CMD_BUF_POST_LIST_REQUEST
अणु
    U8                      Reserved;                   /* 00h */
    U8                      PortNumber;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     CmdBufferCount;             /* 04h */
    U8                      Reserved1;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Reserved2;                  /* 0Ch */
    U16                     IoIndex[2];                 /* 10h */
पूर्ण MSG_TARGET_CMD_BUF_POST_LIST_REQUEST,
  MPI_POINTER PTR_MSG_TARGET_CMD_BUF_POST_LIST_REQUEST,
  TargetCmdBufferPostListRequest_t,
  MPI_POINTER pTargetCmdBufferPostListRequest_t;


/****************************************************************************/
/* Command Buffer Formats (with 16 byte CDB)                                */
/****************************************************************************/

प्रकार काष्ठा _MPI_TARGET_FCP_CMD_BUFFER
अणु
    U8      FcpLun[8];                                  /* 00h */
    U8      FcpCntl[4];                                 /* 08h */
    U8      FcpCdb[16];                                 /* 0Ch */
    U32     FcpDl;                                      /* 1Ch */
    U8      AliasIndex;                                 /* 20h */
    U8      Reserved1;                                  /* 21h */
    U16     OptionalOxid;                               /* 22h */
पूर्ण MPI_TARGET_FCP_CMD_BUFFER, MPI_POINTER PTR_MPI_TARGET_FCP_CMD_BUFFER,
  MpiTargetFcpCmdBuffer, MPI_POINTER pMpiTargetFcpCmdBuffer;


प्रकार काष्ठा _MPI_TARGET_SCSI_SPI_CMD_BUFFER
अणु
    /* SPI L_Q inक्रमmation unit */
    U8      L_QType;                                    /* 00h */
    U8      Reserved;                                   /* 01h */
    U16     Tag;                                        /* 02h */
    U8      LogicalUnitNumber[8];                       /* 04h */
    U32     DataLength;                                 /* 0Ch */
    /* SPI command inक्रमmation unit */
    U8      ReservedFirstByteOfCommandIU;               /* 10h */
    U8      TaskAttribute;                              /* 11h */
    U8      TaskManagementFlags;                        /* 12h */
    U8      AdditionalCDBLength;                        /* 13h */
    U8      CDB[16];                                    /* 14h */
    /* Alias ID */
    U8      AliasID;                                    /* 24h */
    U8      Reserved1;                                  /* 25h */
    U16     Reserved2;                                  /* 26h */
पूर्ण MPI_TARGET_SCSI_SPI_CMD_BUFFER,
  MPI_POINTER PTR_MPI_TARGET_SCSI_SPI_CMD_BUFFER,
  MpiTargetScsiSpiCmdBuffer, MPI_POINTER pMpiTargetScsiSpiCmdBuffer;


प्रकार काष्ठा _MPI_TARGET_SSP_CMD_BUFFER
अणु
    U8      FrameType;                                  /* 00h */
    U8      Reserved1;                                  /* 01h */
    U16     Reserved2;                                  /* 02h */
    U16     InitiatorTag;                               /* 04h */
    U16     DevHandle;                                  /* 06h */
    /* COMMAND inक्रमmation unit starts here */
    U8      LogicalUnitNumber[8];                       /* 08h */
    U8      Reserved3;                                  /* 10h */
    U8      TaskAttribute; /* lower 3 bits */           /* 11h */
    U8      Reserved4;                                  /* 12h */
    U8      AdditionalCDBLength; /* upper 5 bits */     /* 13h */
    U8      CDB[16];                                    /* 14h */
    /* Additional CDB bytes extend past the CDB field */
पूर्ण MPI_TARGET_SSP_CMD_BUFFER, MPI_POINTER PTR_MPI_TARGET_SSP_CMD_BUFFER,
  MpiTargetSspCmdBuffer, MPI_POINTER pMpiTargetSspCmdBuffer;

प्रकार काष्ठा _MPI_TARGET_SSP_TASK_BUFFER
अणु
    U8      FrameType;                                  /* 00h */
    U8      Reserved1;                                  /* 01h */
    U16     Reserved2;                                  /* 02h */
    U16     InitiatorTag;                               /* 04h */
    U16     DevHandle;                                  /* 06h */
    /* TASK inक्रमmation unit starts here */
    U8      LogicalUnitNumber[8];                       /* 08h */
    U8      Reserved3;                                  /* 10h */
    U8      Reserved4;                                  /* 11h */
    U8      TaskManagementFunction;                     /* 12h */
    U8      Reserved5;                                  /* 13h */
    U16     ManagedTaskTag;                             /* 14h */
    U16     Reserved6;                                  /* 16h */
    U32     Reserved7;                                  /* 18h */
    U32     Reserved8;                                  /* 1Ch */
    U32     Reserved9;                                  /* 20h */
पूर्ण MPI_TARGET_SSP_TASK_BUFFER, MPI_POINTER PTR_MPI_TARGET_SSP_TASK_BUFFER,
  MpiTargetSspTaskBuffer, MPI_POINTER pMpiTargetSspTaskBuffer;


/****************************************************************************/
/* Target Assist Request                                                    */
/****************************************************************************/

प्रकार काष्ठा _MSG_TARGET_ASSIST_REQUEST
अणु
    U8                      StatusCode;                 /* 00h */
    U8                      TargetAssistFlags;          /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     QueueTag;                   /* 04h */
    U8                      Reserved;                   /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     ReplyWord;                  /* 0Ch */
    U8                      LUN[8];                     /* 10h */
    U32                     RelativeOffset;             /* 18h */
    U32                     DataLength;                 /* 1Ch */
    SGE_IO_UNION            SGL[1];                     /* 20h */
पूर्ण MSG_TARGET_ASSIST_REQUEST, MPI_POINTER PTR_MSG_TARGET_ASSIST_REQUEST,
  TargetAssistRequest_t, MPI_POINTER pTargetAssistRequest_t;

#घोषणा TARGET_ASSIST_FLAGS_DATA_सूचीECTION          (0x01)
#घोषणा TARGET_ASSIST_FLAGS_AUTO_STATUS             (0x02)
#घोषणा TARGET_ASSIST_FLAGS_HIGH_PRIORITY           (0x04)
#घोषणा TARGET_ASSIST_FLAGS_CONFIRMED               (0x08)
#घोषणा TARGET_ASSIST_FLAGS_REPOST_CMD_BUFFER       (0x80)

/* Standard Target Mode Reply message */
प्रकार काष्ठा _MSG_TARGET_ERROR_REPLY
अणु
    U16                     Reserved;                   /* 00h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      PriorityReason;             /* 0Ch */
    U8                      Reserved3;                  /* 0Dh */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
    U32                     ReplyWord;                  /* 14h */
    U32                     TransferCount;              /* 18h */
पूर्ण MSG_TARGET_ERROR_REPLY, MPI_POINTER PTR_MSG_TARGET_ERROR_REPLY,
  TargetErrorReply_t, MPI_POINTER pTargetErrorReply_t;


/****************************************************************************/
/* Target Assist Extended Request                                           */
/****************************************************************************/

प्रकार काष्ठा _MSG_TARGET_ASSIST_EXT_REQUEST
अणु
    U8                      StatusCode;                     /* 00h */
    U8                      TargetAssistFlags;              /* 01h */
    U8                      ChainOffset;                    /* 02h */
    U8                      Function;                       /* 03h */
    U16                     QueueTag;                       /* 04h */
    U8                      Reserved1;                      /* 06h */
    U8                      MsgFlags;                       /* 07h */
    U32                     MsgContext;                     /* 08h */
    U32                     ReplyWord;                      /* 0Ch */
    U8                      LUN[8];                         /* 10h */
    U32                     RelativeOffset;                 /* 18h */
    U32                     Reserved2;                      /* 1Ch */
    U32                     Reserved3;                      /* 20h */
    U32                     PrimaryReferenceTag;            /* 24h */
    U16                     PrimaryApplicationTag;          /* 28h */
    U16                     PrimaryApplicationTagMask;      /* 2Ah */
    U32                     Reserved4;                      /* 2Ch */
    U32                     DataLength;                     /* 30h */
    U32                     BidirectionalDataLength;        /* 34h */
    U32                     SecondaryReferenceTag;          /* 38h */
    U16                     SecondaryApplicationTag;        /* 3Ch */
    U16                     Reserved5;                      /* 3Eh */
    U16                     EEDPFlags;                      /* 40h */
    U16                     ApplicationTagTranslationMask;  /* 42h */
    U32                     EEDPBlockSize;                  /* 44h */
    U8                      SGLOffset0;                     /* 48h */
    U8                      SGLOffset1;                     /* 49h */
    U8                      SGLOffset2;                     /* 4Ah */
    U8                      SGLOffset3;                     /* 4Bh */
    U32                     Reserved6;                      /* 4Ch */
    SGE_IO_UNION            SGL[1];                         /* 50h */
पूर्ण MSG_TARGET_ASSIST_EXT_REQUEST, MPI_POINTER PTR_MSG_TARGET_ASSIST_EXT_REQUEST,
  TargetAssistExtRequest_t, MPI_POINTER pTargetAssistExtRequest_t;

/* see the defines after MSG_TARGET_ASSIST_REQUEST क्रम TargetAssistFlags */

/* defines क्रम the MsgFlags field */
#घोषणा TARGET_ASSIST_EXT_MSGFLAGS_BIसूचीECTIONAL        (0x20)
#घोषणा TARGET_ASSIST_EXT_MSGFLAGS_MULTICAST            (0x10)
#घोषणा TARGET_ASSIST_EXT_MSGFLAGS_SGL_OFFSET_CHAINS    (0x08)

/* defines क्रम the EEDPFlags field */
#घोषणा TARGET_ASSIST_EXT_EEDP_MASK_OP          (0x0007)
#घोषणा TARGET_ASSIST_EXT_EEDP_NOOP_OP          (0x0000)
#घोषणा TARGET_ASSIST_EXT_EEDP_CHK_OP           (0x0001)
#घोषणा TARGET_ASSIST_EXT_EEDP_STRIP_OP         (0x0002)
#घोषणा TARGET_ASSIST_EXT_EEDP_CHKRM_OP         (0x0003)
#घोषणा TARGET_ASSIST_EXT_EEDP_INSERT_OP        (0x0004)
#घोषणा TARGET_ASSIST_EXT_EEDP_REPLACE_OP       (0x0006)
#घोषणा TARGET_ASSIST_EXT_EEDP_CHKREGEN_OP      (0x0007)

#घोषणा TARGET_ASSIST_EXT_EEDP_PASS_REF_TAG     (0x0008)

#घोषणा TARGET_ASSIST_EXT_EEDP_T10_CHK_MASK     (0x0700)
#घोषणा TARGET_ASSIST_EXT_EEDP_T10_CHK_GUARD    (0x0100)
#घोषणा TARGET_ASSIST_EXT_EEDP_T10_CHK_APPTAG   (0x0200)
#घोषणा TARGET_ASSIST_EXT_EEDP_T10_CHK_REFTAG   (0x0400)
#घोषणा TARGET_ASSIST_EXT_EEDP_T10_CHK_SHIFT    (8)

#घोषणा TARGET_ASSIST_EXT_EEDP_INC_SEC_APPTAG   (0x1000)
#घोषणा TARGET_ASSIST_EXT_EEDP_INC_PRI_APPTAG   (0x2000)
#घोषणा TARGET_ASSIST_EXT_EEDP_INC_SEC_REFTAG   (0x4000)
#घोषणा TARGET_ASSIST_EXT_EEDP_INC_PRI_REFTAG   (0x8000)


/****************************************************************************/
/* Target Status Send Request                                               */
/****************************************************************************/

प्रकार काष्ठा _MSG_TARGET_STATUS_SEND_REQUEST
अणु
    U8                      StatusCode;                 /* 00h */
    U8                      StatusFlags;                /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     QueueTag;                   /* 04h */
    U8                      Reserved;                   /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     ReplyWord;                  /* 0Ch */
    U8                      LUN[8];                     /* 10h */
    SGE_SIMPLE_UNION        StatusDataSGE;              /* 18h */
पूर्ण MSG_TARGET_STATUS_SEND_REQUEST, MPI_POINTER PTR_MSG_TARGET_STATUS_SEND_REQUEST,
  TargetStatusSendRequest_t, MPI_POINTER pTargetStatusSendRequest_t;

#घोषणा TARGET_STATUS_SEND_FLAGS_AUTO_GOOD_STATUS   (0x01)
#घोषणा TARGET_STATUS_SEND_FLAGS_HIGH_PRIORITY      (0x04)
#घोषणा TARGET_STATUS_SEND_FLAGS_CONFIRMED          (0x08)
#घोषणा TARGET_STATUS_SEND_FLAGS_REPOST_CMD_BUFFER  (0x80)

/*
 * NOTE: FCP_RSP data is big-endian. When used on a little-endian प्रणाली, this
 * काष्ठाure properly orders the bytes.
 */
प्रकार काष्ठा _MPI_TARGET_FCP_RSP_BUFFER
अणु
    U8      Reserved0[8];                               /* 00h */
    U8      Reserved1[2];                               /* 08h */
    U8      FcpFlags;                                   /* 0Ah */
    U8      FcpStatus;                                  /* 0Bh */
    U32     FcpResid;                                   /* 0Ch */
    U32     FcpSenseLength;                             /* 10h */
    U32     FcpResponseLength;                          /* 14h */
    U8      FcpResponseData[8];                         /* 18h */
    U8      FcpSenseData[32]; /* Pad to 64 bytes */     /* 20h */
पूर्ण MPI_TARGET_FCP_RSP_BUFFER, MPI_POINTER PTR_MPI_TARGET_FCP_RSP_BUFFER,
  MpiTargetFcpRspBuffer, MPI_POINTER pMpiTargetFcpRspBuffer;

/*
 * NOTE: The SPI status IU is big-endian. When used on a little-endian प्रणाली,
 * this काष्ठाure properly orders the bytes.
 */
प्रकार काष्ठा _MPI_TARGET_SCSI_SPI_STATUS_IU
अणु
    U8      Reserved0;                                  /* 00h */
    U8      Reserved1;                                  /* 01h */
    U8      Valid;                                      /* 02h */
    U8      Status;                                     /* 03h */
    U32     SenseDataListLength;                        /* 04h */
    U32     PktFailuresListLength;                      /* 08h */
    U8      SenseData[52]; /* Pad the IU to 64 bytes */ /* 0Ch */
पूर्ण MPI_TARGET_SCSI_SPI_STATUS_IU, MPI_POINTER PTR_MPI_TARGET_SCSI_SPI_STATUS_IU,
  TargetScsiSpiStatusIU_t, MPI_POINTER pTargetScsiSpiStatusIU_t;

/*
 * NOTE: The SSP status IU is big-endian. When used on a little-endian प्रणाली,
 * this काष्ठाure properly orders the bytes.
 */
प्रकार काष्ठा _MPI_TARGET_SSP_RSP_IU
अणु
    U32     Reserved0[6]; /* reserved क्रम SSP header */ /* 00h */
    /* start of RESPONSE inक्रमmation unit */
    U32     Reserved1;                                  /* 18h */
    U32     Reserved2;                                  /* 1Ch */
    U16     Reserved3;                                  /* 20h */
    U8      DataPres; /* lower 2 bits */                /* 22h */
    U8      Status;                                     /* 23h */
    U32     Reserved4;                                  /* 24h */
    U32     SenseDataLength;                            /* 28h */
    U32     ResponseDataLength;                         /* 2Ch */
    U8      ResponseSenseData[4];                       /* 30h */
पूर्ण MPI_TARGET_SSP_RSP_IU, MPI_POINTER PTR_MPI_TARGET_SSP_RSP_IU,
  MpiTargetSspRspIu_t, MPI_POINTER pMpiTargetSspRspIu_t;


/****************************************************************************/
/* Target Mode Abort Request                                                */
/****************************************************************************/

प्रकार काष्ठा _MSG_TARGET_MODE_ABORT_REQUEST
अणु
    U8                      AbortType;                  /* 00h */
    U8                      Reserved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     ReplyWord;                  /* 0Ch */
    U32                     MsgContextToAbort;          /* 10h */
पूर्ण MSG_TARGET_MODE_ABORT, MPI_POINTER PTR_MSG_TARGET_MODE_ABORT,
  TargetModeAbort_t, MPI_POINTER pTargetModeAbort_t;

#घोषणा TARGET_MODE_ABORT_TYPE_ALL_CMD_BUFFERS      (0x00)
#घोषणा TARGET_MODE_ABORT_TYPE_ALL_IO               (0x01)
#घोषणा TARGET_MODE_ABORT_TYPE_EXACT_IO             (0x02)
#घोषणा TARGET_MODE_ABORT_TYPE_EXACT_IO_REQUEST     (0x03)

/* Target Mode Abort Reply */

प्रकार काष्ठा _MSG_TARGET_MODE_ABORT_REPLY
अणु
    U16                     Reserved;                   /* 00h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Reserved3;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
    U32                     AbortCount;                 /* 14h */
पूर्ण MSG_TARGET_MODE_ABORT_REPLY, MPI_POINTER PTR_MSG_TARGET_MODE_ABORT_REPLY,
  TargetModeAbortReply_t, MPI_POINTER pTargetModeAbortReply_t;


/****************************************************************************/
/* Target Mode Context Reply                                                */
/****************************************************************************/

#घोषणा TARGET_MODE_REPLY_IO_INDEX_MASK         (0x00003FFF)
#घोषणा TARGET_MODE_REPLY_IO_INDEX_SHIFT        (0)
#घोषणा TARGET_MODE_REPLY_INITIATOR_INDEX_MASK  (0x03FFC000)
#घोषणा TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT (14)
#घोषणा TARGET_MODE_REPLY_ALIAS_MASK            (0x04000000)
#घोषणा TARGET_MODE_REPLY_ALIAS_SHIFT           (26)
#घोषणा TARGET_MODE_REPLY_PORT_MASK             (0x10000000)
#घोषणा TARGET_MODE_REPLY_PORT_SHIFT            (28)


#घोषणा GET_IO_INDEX(x)     (((x) & TARGET_MODE_REPLY_IO_INDEX_MASK)           \
                                    >> TARGET_MODE_REPLY_IO_INDEX_SHIFT)

#घोषणा SET_IO_INDEX(t, i)                                                     \
            ((t) = ((t) & ~TARGET_MODE_REPLY_IO_INDEX_MASK) |                  \
                              (((i) << TARGET_MODE_REPLY_IO_INDEX_SHIFT) &     \
                                             TARGET_MODE_REPLY_IO_INDEX_MASK))

#घोषणा GET_INITIATOR_INDEX(x) (((x) & TARGET_MODE_REPLY_INITIATOR_INDEX_MASK) \
                                   >> TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT)

#घोषणा SET_INITIATOR_INDEX(t, ii)                                             \
        ((t) = ((t) & ~TARGET_MODE_REPLY_INITIATOR_INDEX_MASK) |               \
                        (((ii) << TARGET_MODE_REPLY_INITIATOR_INDEX_SHIFT) &   \
                                      TARGET_MODE_REPLY_INITIATOR_INDEX_MASK))

#घोषणा GET_ALIAS(x) (((x) & TARGET_MODE_REPLY_ALIAS_MASK)                     \
                                               >> TARGET_MODE_REPLY_ALIAS_SHIFT)

#घोषणा SET_ALIAS(t, a)  ((t) = ((t) & ~TARGET_MODE_REPLY_ALIAS_MASK) |        \
                                    (((a) << TARGET_MODE_REPLY_ALIAS_SHIFT) &  \
                                                 TARGET_MODE_REPLY_ALIAS_MASK))

#घोषणा GET_PORT(x) (((x) & TARGET_MODE_REPLY_PORT_MASK)                       \
                                               >> TARGET_MODE_REPLY_PORT_SHIFT)

#घोषणा SET_PORT(t, p)  ((t) = ((t) & ~TARGET_MODE_REPLY_PORT_MASK) |          \
                                    (((p) << TARGET_MODE_REPLY_PORT_SHIFT) &   \
                                                  TARGET_MODE_REPLY_PORT_MASK))

/* the following obsolete values are क्रम MPI v1.0 support */
#घोषणा TARGET_MODE_REPLY_0100_MASK_HOST_INDEX       (0x000003FF)
#घोषणा TARGET_MODE_REPLY_0100_SHIFT_HOST_INDEX      (0)
#घोषणा TARGET_MODE_REPLY_0100_MASK_IOC_INDEX        (0x001FF800)
#घोषणा TARGET_MODE_REPLY_0100_SHIFT_IOC_INDEX       (11)
#घोषणा TARGET_MODE_REPLY_0100_PORT_MASK             (0x00400000)
#घोषणा TARGET_MODE_REPLY_0100_PORT_SHIFT            (22)
#घोषणा TARGET_MODE_REPLY_0100_MASK_INITIATOR_INDEX  (0x1F800000)
#घोषणा TARGET_MODE_REPLY_0100_SHIFT_INITIATOR_INDEX (23)

#घोषणा GET_HOST_INDEX_0100(x) (((x) & TARGET_MODE_REPLY_0100_MASK_HOST_INDEX) \
                                  >> TARGET_MODE_REPLY_0100_SHIFT_HOST_INDEX)

#घोषणा SET_HOST_INDEX_0100(t, hi)                                             \
            ((t) = ((t) & ~TARGET_MODE_REPLY_0100_MASK_HOST_INDEX) |           \
                         (((hi) << TARGET_MODE_REPLY_0100_SHIFT_HOST_INDEX) &  \
                                      TARGET_MODE_REPLY_0100_MASK_HOST_INDEX))

#घोषणा GET_IOC_INDEX_0100(x)   (((x) & TARGET_MODE_REPLY_0100_MASK_IOC_INDEX) \
                                  >> TARGET_MODE_REPLY_0100_SHIFT_IOC_INDEX)

#घोषणा SET_IOC_INDEX_0100(t, ii)                                              \
            ((t) = ((t) & ~TARGET_MODE_REPLY_0100_MASK_IOC_INDEX) |            \
                        (((ii) << TARGET_MODE_REPLY_0100_SHIFT_IOC_INDEX) &    \
                                     TARGET_MODE_REPLY_0100_MASK_IOC_INDEX))

#घोषणा GET_INITIATOR_INDEX_0100(x)                                            \
            (((x) & TARGET_MODE_REPLY_0100_MASK_INITIATOR_INDEX)               \
                              >> TARGET_MODE_REPLY_0100_SHIFT_INITIATOR_INDEX)

#घोषणा SET_INITIATOR_INDEX_0100(t, ii)                                        \
        ((t) = ((t) & ~TARGET_MODE_REPLY_0100_MASK_INITIATOR_INDEX) |          \
                   (((ii) << TARGET_MODE_REPLY_0100_SHIFT_INITIATOR_INDEX) &   \
                                TARGET_MODE_REPLY_0100_MASK_INITIATOR_INDEX))


#पूर्ण_अगर

