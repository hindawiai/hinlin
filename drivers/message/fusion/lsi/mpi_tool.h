<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2001-2008 LSI Corporation.
 *
 *
 *           Name:  mpi_tool.h
 *          Title:  MPI Toolbox काष्ठाures and definitions
 *  Creation Date:  July 30, 2001
 *
 *    mpi_tool.h Version:  01.05.03
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  08-08-01  01.02.01  Original release.
 *  08-29-01  01.02.02  Added DIAG_DATA_UPLOAD_HEADER and related defines.
 *  01-16-04  01.02.03  Added defines and काष्ठाures क्रम new tools
 *.                     MPI_TOOLBOX_ISTWI_READ_WRITE_TOOL and
 *                      MPI_TOOLBOX_FC_MANAGEMENT_TOOL.
 *  04-29-04  01.02.04  Added message काष्ठाures क्रम Diagnostic Buffer Post and
 *                      Diagnostic Release requests and replies.
 *  05-11-04  01.03.01  Original release क्रम MPI v1.3.
 *  08-19-04  01.05.01  Original release क्रम MPI v1.5.
 *  10-06-04  01.05.02  Added define क्रम MPI_DIAG_BUF_TYPE_COUNT.
 *  02-09-05  01.05.03  Added frame size option to FC management tool.
 *                      Added Beacon tool to the Toolbox.
 *  --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI_TOOL_H
#घोषणा MPI_TOOL_H

#घोषणा MPI_TOOLBOX_CLEAN_TOOL                      (0x00)
#घोषणा MPI_TOOLBOX_MEMORY_MOVE_TOOL                (0x01)
#घोषणा MPI_TOOLBOX_DIAG_DATA_UPLOAD_TOOL           (0x02)
#घोषणा MPI_TOOLBOX_ISTWI_READ_WRITE_TOOL           (0x03)
#घोषणा MPI_TOOLBOX_FC_MANAGEMENT_TOOL              (0x04)
#घोषणा MPI_TOOLBOX_BEACON_TOOL                     (0x05)


/****************************************************************************/
/* Toolbox reply                                                            */
/****************************************************************************/

प्रकार काष्ठा _MSG_TOOLBOX_REPLY
अणु
    U8                      Tool;                       /* 00h */
    U8                      Reserved;                   /* 01h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Reserved3;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
पूर्ण MSG_TOOLBOX_REPLY, MPI_POINTER PTR_MSG_TOOLBOX_REPLY,
  ToolboxReply_t, MPI_POINTER pToolboxReply_t;


/****************************************************************************/
/* Toolbox Clean Tool request                                               */
/****************************************************************************/

प्रकार काष्ठा _MSG_TOOLBOX_CLEAN_REQUEST
अणु
    U8                      Tool;                       /* 00h */
    U8                      Reserved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Flags;                      /* 0Ch */
पूर्ण MSG_TOOLBOX_CLEAN_REQUEST, MPI_POINTER PTR_MSG_TOOLBOX_CLEAN_REQUEST,
  ToolboxCleanRequest_t, MPI_POINTER pToolboxCleanRequest_t;

#घोषणा MPI_TOOLBOX_CLEAN_NVSRAM                    (0x00000001)
#घोषणा MPI_TOOLBOX_CLEAN_SEEPROM                   (0x00000002)
#घोषणा MPI_TOOLBOX_CLEAN_FLASH                     (0x00000004)
#घोषणा MPI_TOOLBOX_CLEAN_BOOTLOADER                (0x04000000)
#घोषणा MPI_TOOLBOX_CLEAN_FW_BACKUP                 (0x08000000)
#घोषणा MPI_TOOLBOX_CLEAN_FW_CURRENT                (0x10000000)
#घोषणा MPI_TOOLBOX_CLEAN_OTHER_PERSIST_PAGES       (0x20000000)
#घोषणा MPI_TOOLBOX_CLEAN_PERSIST_MANUFACT_PAGES    (0x40000000)
#घोषणा MPI_TOOLBOX_CLEAN_BOOT_SERVICES             (0x80000000)


/****************************************************************************/
/* Toolbox Memory Move request                                              */
/****************************************************************************/

प्रकार काष्ठा _MSG_TOOLBOX_MEM_MOVE_REQUEST
अणु
    U8                      Tool;                       /* 00h */
    U8                      Reserved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    SGE_SIMPLE_UNION        SGL;                        /* 0Ch */
पूर्ण MSG_TOOLBOX_MEM_MOVE_REQUEST, MPI_POINTER PTR_MSG_TOOLBOX_MEM_MOVE_REQUEST,
  ToolboxMemMoveRequest_t, MPI_POINTER pToolboxMemMoveRequest_t;


/****************************************************************************/
/* Toolbox Diagnostic Data Upload request                                   */
/****************************************************************************/

प्रकार काष्ठा _MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST
अणु
    U8                      Tool;                       /* 00h */
    U8                      Reserved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     Flags;                      /* 0Ch */
    U32                     Reserved3;                  /* 10h */
    SGE_SIMPLE_UNION        SGL;                        /* 14h */
पूर्ण MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST, MPI_POINTER PTR_MSG_TOOLBOX_DIAG_DATA_UPLOAD_REQUEST,
  ToolboxDiagDataUploadRequest_t, MPI_POINTER pToolboxDiagDataUploadRequest_t;

प्रकार काष्ठा _DIAG_DATA_UPLOAD_HEADER
अणु
    U32                     DiagDataLength;             /* 00h */
    U8                      FormatCode;                 /* 04h */
    U8                      Reserved;                   /* 05h */
    U16                     Reserved1;                  /* 06h */
पूर्ण DIAG_DATA_UPLOAD_HEADER, MPI_POINTER PTR_DIAG_DATA_UPLOAD_HEADER,
  DiagDataUploadHeader_t, MPI_POINTER pDiagDataUploadHeader_t;

#घोषणा MPI_TB_DIAG_FORMAT_SCSI_PRINTF_1            (0x01)
#घोषणा MPI_TB_DIAG_FORMAT_SCSI_2                   (0x02)
#घोषणा MPI_TB_DIAG_FORMAT_SCSI_3                   (0x03)
#घोषणा MPI_TB_DIAG_FORMAT_FC_TRACE_1               (0x04)


/****************************************************************************/
/* Toolbox ISTWI Read Write request                                         */
/****************************************************************************/

प्रकार काष्ठा _MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST
अणु
    U8                      Tool;                       /* 00h */
    U8                      Reserved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      Flags;                      /* 0Ch */
    U8                      BusNum;                     /* 0Dh */
    U16                     Reserved3;                  /* 0Eh */
    U8                      NumAddressBytes;            /* 10h */
    U8                      Reserved4;                  /* 11h */
    U16                     DataLength;                 /* 12h */
    U8                      DeviceAddr;                 /* 14h */
    U8                      Addr1;                      /* 15h */
    U8                      Addr2;                      /* 16h */
    U8                      Addr3;                      /* 17h */
    U32                     Reserved5;                  /* 18h */
    SGE_SIMPLE_UNION        SGL;                        /* 1Ch */
पूर्ण MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST, MPI_POINTER PTR_MSG_TOOLBOX_ISTWI_READ_WRITE_REQUEST,
  ToolboxIstwiReadWriteRequest_t, MPI_POINTER pToolboxIstwiReadWriteRequest_t;

#घोषणा MPI_TB_ISTWI_FLAGS_WRITE                    (0x00)
#घोषणा MPI_TB_ISTWI_FLAGS_READ                     (0x01)


/****************************************************************************/
/* Toolbox FC Management request                                            */
/****************************************************************************/

/* ActionInfo क्रम Bus and TargetId */
प्रकार काष्ठा _MPI_TB_FC_MANAGE_BUS_TID_AI
अणु
    U16                     Reserved;                   /* 00h */
    U8                      Bus;                        /* 02h */
    U8                      TargetId;                   /* 03h */
पूर्ण MPI_TB_FC_MANAGE_BUS_TID_AI, MPI_POINTER PTR_MPI_TB_FC_MANAGE_BUS_TID_AI,
  MpiTbFcManageBusTidAi_t, MPI_POINTER pMpiTbFcManageBusTidAi_t;

/* ActionInfo क्रम port identअगरier */
प्रकार काष्ठा _MPI_TB_FC_MANAGE_PID_AI
अणु
    U32                     PortIdentअगरier;             /* 00h */
पूर्ण MPI_TB_FC_MANAGE_PID_AI, MPI_POINTER PTR_MPI_TB_FC_MANAGE_PID_AI,
  MpiTbFcManagePidAi_t, MPI_POINTER pMpiTbFcManagePidAi_t;

/* ActionInfo क्रम set max frame size */
प्रकार काष्ठा _MPI_TB_FC_MANAGE_FRAME_SIZE_AI
अणु
    U16                     FrameSize;                  /* 00h */
    U8                      PortNum;                    /* 02h */
    U8                      Reserved1;                  /* 03h */
पूर्ण MPI_TB_FC_MANAGE_FRAME_SIZE_AI, MPI_POINTER PTR_MPI_TB_FC_MANAGE_FRAME_SIZE_AI,
  MpiTbFcManageFrameSizeAi_t, MPI_POINTER pMpiTbFcManageFrameSizeAi_t;

/* जोड़ of ActionInfo */
प्रकार जोड़ _MPI_TB_FC_MANAGE_AI_UNION
अणु
    MPI_TB_FC_MANAGE_BUS_TID_AI     BusTid;
    MPI_TB_FC_MANAGE_PID_AI         Port;
    MPI_TB_FC_MANAGE_FRAME_SIZE_AI  FrameSize;
पूर्ण MPI_TB_FC_MANAGE_AI_UNION, MPI_POINTER PTR_MPI_TB_FC_MANAGE_AI_UNION,
  MpiTbFcManageAiUnion_t, MPI_POINTER pMpiTbFcManageAiUnion_t;

प्रकार काष्ठा _MSG_TOOLBOX_FC_MANAGE_REQUEST
अणु
    U8                          Tool;                   /* 00h */
    U8                          Reserved;               /* 01h */
    U8                          ChainOffset;            /* 02h */
    U8                          Function;               /* 03h */
    U16                         Reserved1;              /* 04h */
    U8                          Reserved2;              /* 06h */
    U8                          MsgFlags;               /* 07h */
    U32                         MsgContext;             /* 08h */
    U8                          Action;                 /* 0Ch */
    U8                          Reserved3;              /* 0Dh */
    U16                         Reserved4;              /* 0Eh */
    MPI_TB_FC_MANAGE_AI_UNION   ActionInfo;             /* 10h */
पूर्ण MSG_TOOLBOX_FC_MANAGE_REQUEST, MPI_POINTER PTR_MSG_TOOLBOX_FC_MANAGE_REQUEST,
  ToolboxFcManageRequest_t, MPI_POINTER pToolboxFcManageRequest_t;

/* defines क्रम the Action field */
#घोषणा MPI_TB_FC_MANAGE_ACTION_DISC_ALL            (0x00)
#घोषणा MPI_TB_FC_MANAGE_ACTION_DISC_PID            (0x01)
#घोषणा MPI_TB_FC_MANAGE_ACTION_DISC_BUS_TID        (0x02)
#घोषणा MPI_TB_FC_MANAGE_ACTION_SET_MAX_FRAME_SIZE  (0x03)


/****************************************************************************/
/* Toolbox Beacon Tool request                                               */
/****************************************************************************/

प्रकार काष्ठा _MSG_TOOLBOX_BEACON_REQUEST
अणु
    U8                      Tool;                       /* 00h */
    U8                      Reserved;                   /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U8                      ConnectNum;                 /* 0Ch */
    U8                      PortNum;                    /* 0Dh */
    U8                      Reserved3;                  /* 0Eh */
    U8                      Flags;                      /* 0Fh */
पूर्ण MSG_TOOLBOX_BEACON_REQUEST, MPI_POINTER PTR_MSG_TOOLBOX_BEACON_REQUEST,
  ToolboxBeaconRequest_t, MPI_POINTER pToolboxBeaconRequest_t;

#घोषणा MPI_TOOLBOX_FLAGS_BEACON_MODE_OFF       (0x00)
#घोषणा MPI_TOOLBOX_FLAGS_BEACON_MODE_ON        (0x01)


/****************************************************************************/
/* Diagnostic Buffer Post request                                           */
/****************************************************************************/

प्रकार काष्ठा _MSG_DIAG_BUFFER_POST_REQUEST
अणु
    U8                      TraceLevel;                 /* 00h */
    U8                      BufferType;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved1;                  /* 04h */
    U8                      Reserved2;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U32                     ExtendedType;               /* 0Ch */
    U32                     BufferLength;               /* 10h */
    U32                     ProductSpecअगरic[4];         /* 14h */
    U32                     Reserved3;                  /* 24h */
    U64                     BufferAddress;              /* 28h */
पूर्ण MSG_DIAG_BUFFER_POST_REQUEST, MPI_POINTER PTR_MSG_DIAG_BUFFER_POST_REQUEST,
  DiagBufferPostRequest_t, MPI_POINTER pDiagBufferPostRequest_t;

#घोषणा MPI_DIAG_BUF_TYPE_TRACE                     (0x00)
#घोषणा MPI_DIAG_BUF_TYPE_SNAPSHOT                  (0x01)
#घोषणा MPI_DIAG_BUF_TYPE_EXTENDED                  (0x02)
/* count of the number of buffer types */
#घोषणा MPI_DIAG_BUF_TYPE_COUNT                     (0x03)

#घोषणा MPI_DIAG_EXTENDED_QTAG                      (0x00000001)


/* Diagnostic Buffer Post reply */
प्रकार काष्ठा _MSG_DIAG_BUFFER_POST_REPLY
अणु
    U8                      Reserved1;                  /* 00h */
    U8                      BufferType;                 /* 01h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved2;                  /* 04h */
    U8                      Reserved3;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Reserved4;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
    U32                     TransferLength;             /* 14h */
पूर्ण MSG_DIAG_BUFFER_POST_REPLY, MPI_POINTER PTR_MSG_DIAG_BUFFER_POST_REPLY,
  DiagBufferPostReply_t, MPI_POINTER pDiagBufferPostReply_t;


/****************************************************************************/
/* Diagnostic Release request                                               */
/****************************************************************************/

प्रकार काष्ठा _MSG_DIAG_RELEASE_REQUEST
अणु
    U8                      Reserved1;                  /* 00h */
    U8                      BufferType;                 /* 01h */
    U8                      ChainOffset;                /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved2;                  /* 04h */
    U8                      Reserved3;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
पूर्ण MSG_DIAG_RELEASE_REQUEST, MPI_POINTER PTR_MSG_DIAG_RELEASE_REQUEST,
  DiagReleaseRequest_t, MPI_POINTER pDiagReleaseRequest_t;


/* Diagnostic Release reply */
प्रकार काष्ठा _MSG_DIAG_RELEASE_REPLY
अणु
    U8                      Reserved1;                  /* 00h */
    U8                      BufferType;                 /* 01h */
    U8                      MsgLength;                  /* 02h */
    U8                      Function;                   /* 03h */
    U16                     Reserved2;                  /* 04h */
    U8                      Reserved3;                  /* 06h */
    U8                      MsgFlags;                   /* 07h */
    U32                     MsgContext;                 /* 08h */
    U16                     Reserved4;                  /* 0Ch */
    U16                     IOCStatus;                  /* 0Eh */
    U32                     IOCLogInfo;                 /* 10h */
पूर्ण MSG_DIAG_RELEASE_REPLY, MPI_POINTER PTR_MSG_DIAG_RELEASE_REPLY,
  DiagReleaseReply_t, MPI_POINTER pDiagReleaseReply_t;


#पूर्ण_अगर


