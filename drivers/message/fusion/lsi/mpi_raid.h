<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (c) 2001-2008 LSI Corporation.
 *
 *
 *           Name:  mpi_raid.h
 *          Title:  MPI RAID message and काष्ठाures
 *  Creation Date:  February 27, 2001
 *
 *    mpi_raid.h Version:  01.05.05
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  02-27-01  01.01.01  Original release क्रम this file.
 *  03-27-01  01.01.02  Added काष्ठाure offset comments.
 *  08-08-01  01.02.01  Original release क्रम v1.2 work.
 *  09-28-01  01.02.02  Major rework क्रम MPI v1.2 Integrated RAID changes.
 *  10-04-01  01.02.03  Added ActionData defines क्रम
 *                      MPI_RAID_ACTION_DELETE_VOLUME action.
 *  11-01-01  01.02.04  Added define क्रम MPI_RAID_ACTION_ADATA_DO_NOT_SYNC.
 *  03-14-02  01.02.05  Added define क्रम MPI_RAID_ACTION_ADATA_LOW_LEVEL_INIT.
 *  05-07-02  01.02.06  Added define क्रम MPI_RAID_ACTION_ACTIVATE_VOLUME,
 *                      MPI_RAID_ACTION_INACTIVATE_VOLUME, and
 *                      MPI_RAID_ACTION_ADATA_INACTIVATE_ALL.
 *  07-12-02  01.02.07  Added काष्ठाures क्रम Mailbox request and reply.
 *  11-15-02  01.02.08  Added missing MsgContext field to MSG_MAILBOX_REQUEST.
 *  04-01-03  01.02.09  New action data option flag क्रम
 *                      MPI_RAID_ACTION_DELETE_VOLUME.
 *  05-11-04  01.03.01  Original release क्रम MPI v1.3.
 *  08-19-04  01.05.01  Original release क्रम MPI v1.5.
 *  01-15-05  01.05.02  Added defines क्रम the two new RAID Actions क्रम
 *                      _SET_RESYNC_RATE and _SET_DATA_SCRUB_RATE.
 *  02-28-07  01.05.03  Added new RAID Action, Device FW Update Mode, and
 *                      associated defines.
 *  08-07-07  01.05.04  Added Disable Full Rebuild bit to the ActionDataWord
 *                      क्रम the RAID Action MPI_RAID_ACTION_DISABLE_VOLUME.
 *  01-15-08  01.05.05  Added define क्रम MPI_RAID_ACTION_SET_VOLUME_NAME.
 *  --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI_RAID_H
#घोषणा MPI_RAID_H


/******************************************************************************
*
*        R A I D    M e s s a g e s
*
*******************************************************************************/


/****************************************************************************/
/* RAID Action Request                                                      */
/****************************************************************************/

प्रकार काष्ठा _MSG_RAID_ACTION
अणु
    U8                      Action;             /* 00h */
    U8                      Reserved1;          /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U8                      VolumeID;           /* 04h */
    U8                      VolumeBus;          /* 05h */
    U8                      PhysDiskNum;        /* 06h */
    U8                      MsgFlags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U32                     Reserved2;          /* 0Ch */
    U32                     ActionDataWord;     /* 10h */
    SGE_SIMPLE_UNION        ActionDataSGE;      /* 14h */
पूर्ण MSG_RAID_ACTION_REQUEST, MPI_POINTER PTR_MSG_RAID_ACTION_REQUEST,
  MpiRaidActionRequest_t , MPI_POINTER pMpiRaidActionRequest_t;


/* RAID Action request Action values */

#घोषणा MPI_RAID_ACTION_STATUS                      (0x00)
#घोषणा MPI_RAID_ACTION_INDICATOR_STRUCT            (0x01)
#घोषणा MPI_RAID_ACTION_CREATE_VOLUME               (0x02)
#घोषणा MPI_RAID_ACTION_DELETE_VOLUME               (0x03)
#घोषणा MPI_RAID_ACTION_DISABLE_VOLUME              (0x04)
#घोषणा MPI_RAID_ACTION_ENABLE_VOLUME               (0x05)
#घोषणा MPI_RAID_ACTION_QUIESCE_PHYS_IO             (0x06)
#घोषणा MPI_RAID_ACTION_ENABLE_PHYS_IO              (0x07)
#घोषणा MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS      (0x08)
#घोषणा MPI_RAID_ACTION_PHYSDISK_OFFLINE            (0x0A)
#घोषणा MPI_RAID_ACTION_PHYSDISK_ONLINE             (0x0B)
#घोषणा MPI_RAID_ACTION_CHANGE_PHYSDISK_SETTINGS    (0x0C)
#घोषणा MPI_RAID_ACTION_CREATE_PHYSDISK             (0x0D)
#घोषणा MPI_RAID_ACTION_DELETE_PHYSDISK             (0x0E)
#घोषणा MPI_RAID_ACTION_FAIL_PHYSDISK               (0x0F)
#घोषणा MPI_RAID_ACTION_REPLACE_PHYSDISK            (0x10)
#घोषणा MPI_RAID_ACTION_ACTIVATE_VOLUME             (0x11)
#घोषणा MPI_RAID_ACTION_INACTIVATE_VOLUME           (0x12)
#घोषणा MPI_RAID_ACTION_SET_RESYNC_RATE             (0x13)
#घोषणा MPI_RAID_ACTION_SET_DATA_SCRUB_RATE         (0x14)
#घोषणा MPI_RAID_ACTION_DEVICE_FW_UPDATE_MODE       (0x15)
#घोषणा MPI_RAID_ACTION_SET_VOLUME_NAME             (0x16)

/* ActionDataWord defines क्रम use with MPI_RAID_ACTION_CREATE_VOLUME action */
#घोषणा MPI_RAID_ACTION_ADATA_DO_NOT_SYNC           (0x00000001)
#घोषणा MPI_RAID_ACTION_ADATA_LOW_LEVEL_INIT        (0x00000002)

/* ActionDataWord defines क्रम use with MPI_RAID_ACTION_DELETE_VOLUME action */
#घोषणा MPI_RAID_ACTION_ADATA_KEEP_PHYS_DISKS       (0x00000000)
#घोषणा MPI_RAID_ACTION_ADATA_DEL_PHYS_DISKS        (0x00000001)

#घोषणा MPI_RAID_ACTION_ADATA_KEEP_LBA0             (0x00000000)
#घोषणा MPI_RAID_ACTION_ADATA_ZERO_LBA0             (0x00000002)

/* ActionDataWord defines क्रम use with MPI_RAID_ACTION_DISABLE_VOLUME action */
#घोषणा MPI_RAID_ACTION_ADATA_DISABLE_FULL_REBUILD  (0x00000001)

/* ActionDataWord defines क्रम use with MPI_RAID_ACTION_ACTIVATE_VOLUME action */
#घोषणा MPI_RAID_ACTION_ADATA_INACTIVATE_ALL        (0x00000001)

/* ActionDataWord defines क्रम use with MPI_RAID_ACTION_SET_RESYNC_RATE action */
#घोषणा MPI_RAID_ACTION_ADATA_RESYNC_RATE_MASK      (0x000000FF)

/* ActionDataWord defines क्रम use with MPI_RAID_ACTION_SET_DATA_SCRUB_RATE action */
#घोषणा MPI_RAID_ACTION_ADATA_DATA_SCRUB_RATE_MASK  (0x000000FF)

/* ActionDataWord defines क्रम use with MPI_RAID_ACTION_DEVICE_FW_UPDATE_MODE action */
#घोषणा MPI_RAID_ACTION_ADATA_ENABLE_FW_UPDATE          (0x00000001)
#घोषणा MPI_RAID_ACTION_ADATA_MASK_FW_UPDATE_TIMEOUT    (0x0000FF00)
#घोषणा MPI_RAID_ACTION_ADATA_SHIFT_FW_UPDATE_TIMEOUT   (8)


/* RAID Action reply message */

प्रकार काष्ठा _MSG_RAID_ACTION_REPLY
अणु
    U8                      Action;             /* 00h */
    U8                      Reserved;           /* 01h */
    U8                      MsgLength;          /* 02h */
    U8                      Function;           /* 03h */
    U8                      VolumeID;           /* 04h */
    U8                      VolumeBus;          /* 05h */
    U8                      PhysDiskNum;        /* 06h */
    U8                      MsgFlags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U16                     ActionStatus;       /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCLogInfo;         /* 10h */
    U32                     VolumeStatus;       /* 14h */
    U32                     ActionData;         /* 18h */
पूर्ण MSG_RAID_ACTION_REPLY, MPI_POINTER PTR_MSG_RAID_ACTION_REPLY,
  MpiRaidActionReply_t, MPI_POINTER pMpiRaidActionReply_t;


/* RAID Volume reply ActionStatus values */

#घोषणा MPI_RAID_ACTION_ASTATUS_SUCCESS             (0x0000)
#घोषणा MPI_RAID_ACTION_ASTATUS_INVALID_ACTION      (0x0001)
#घोषणा MPI_RAID_ACTION_ASTATUS_FAILURE             (0x0002)
#घोषणा MPI_RAID_ACTION_ASTATUS_IN_PROGRESS         (0x0003)


/* RAID Volume reply RAID Volume Indicator काष्ठाure */

प्रकार काष्ठा _MPI_RAID_VOL_INDICATOR
अणु
    U64                     TotalBlocks;        /* 00h */
    U64                     BlocksReमुख्यing;    /* 08h */
पूर्ण MPI_RAID_VOL_INDICATOR, MPI_POINTER PTR_MPI_RAID_VOL_INDICATOR,
  MpiRaidVolIndicator_t, MPI_POINTER pMpiRaidVolIndicator_t;


/****************************************************************************/
/* SCSI IO RAID Passthrough Request                                         */
/****************************************************************************/

प्रकार काष्ठा _MSG_SCSI_IO_RAID_PT_REQUEST
अणु
    U8                      PhysDiskNum;        /* 00h */
    U8                      Reserved1;          /* 01h */
    U8                      ChainOffset;        /* 02h */
    U8                      Function;           /* 03h */
    U8                      CDBLength;          /* 04h */
    U8                      SenseBufferLength;  /* 05h */
    U8                      Reserved2;          /* 06h */
    U8                      MsgFlags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      LUN[8];             /* 0Ch */
    U32                     Control;            /* 14h */
    U8                      CDB[16];            /* 18h */
    U32                     DataLength;         /* 28h */
    U32                     SenseBufferLowAddr; /* 2Ch */
    SGE_IO_UNION            SGL;                /* 30h */
पूर्ण MSG_SCSI_IO_RAID_PT_REQUEST, MPI_POINTER PTR_MSG_SCSI_IO_RAID_PT_REQUEST,
  SCSIIORaidPassthroughRequest_t, MPI_POINTER pSCSIIORaidPassthroughRequest_t;


/* SCSI IO RAID Passthrough reply काष्ठाure */

प्रकार काष्ठा _MSG_SCSI_IO_RAID_PT_REPLY
अणु
    U8                      PhysDiskNum;        /* 00h */
    U8                      Reserved1;          /* 01h */
    U8                      MsgLength;          /* 02h */
    U8                      Function;           /* 03h */
    U8                      CDBLength;          /* 04h */
    U8                      SenseBufferLength;  /* 05h */
    U8                      Reserved2;          /* 06h */
    U8                      MsgFlags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U8                      SCSIStatus;         /* 0Ch */
    U8                      SCSIState;          /* 0Dh */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCLogInfo;         /* 10h */
    U32                     TransferCount;      /* 14h */
    U32                     SenseCount;         /* 18h */
    U32                     ResponseInfo;       /* 1Ch */
पूर्ण MSG_SCSI_IO_RAID_PT_REPLY, MPI_POINTER PTR_MSG_SCSI_IO_RAID_PT_REPLY,
  SCSIIORaidPassthroughReply_t, MPI_POINTER pSCSIIORaidPassthroughReply_t;


/****************************************************************************/
/* Mailbox reqeust काष्ठाure */
/****************************************************************************/

प्रकार काष्ठा _MSG_MAILBOX_REQUEST
अणु
    U16                     Reserved1;
    U8                      ChainOffset;
    U8                      Function;
    U16                     Reserved2;
    U8                      Reserved3;
    U8                      MsgFlags;
    U32                     MsgContext;
    U8                      Command[10];
    U16                     Reserved4;
    SGE_IO_UNION            SGL;
पूर्ण MSG_MAILBOX_REQUEST, MPI_POINTER PTR_MSG_MAILBOX_REQUEST,
  MailboxRequest_t, MPI_POINTER pMailboxRequest_t;


/* Mailbox reply काष्ठाure */
प्रकार काष्ठा _MSG_MAILBOX_REPLY
अणु
    U16                     Reserved1;          /* 00h */
    U8                      MsgLength;          /* 02h */
    U8                      Function;           /* 03h */
    U16                     Reserved2;          /* 04h */
    U8                      Reserved3;          /* 06h */
    U8                      MsgFlags;           /* 07h */
    U32                     MsgContext;         /* 08h */
    U16                     MailboxStatus;      /* 0Ch */
    U16                     IOCStatus;          /* 0Eh */
    U32                     IOCLogInfo;         /* 10h */
    U32                     Reserved4;          /* 14h */
पूर्ण MSG_MAILBOX_REPLY, MPI_POINTER PTR_MSG_MAILBOX_REPLY,
  MailboxReply_t, MPI_POINTER pMailboxReply_t;

#पूर्ण_अगर



