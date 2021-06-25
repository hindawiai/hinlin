<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2000-2020 Broadcom Inc. All rights reserved.
 *
 *
 *          Name:  mpi2_raid.h
 *         Title:  MPI Integrated RAID messages and काष्ठाures
 * Creation Date:  April 26, 2007
 *
 *   mpi2_raid.h Version:  02.00.11
 *
 * Version History
 * ---------------
 *
 * Date      Version   Description
 * --------  --------  ------------------------------------------------------
 * 04-30-07  02.00.00  Corresponds to Fusion-MPT MPI Specअगरication Rev A.
 * 08-31-07  02.00.01  Modअगरications to RAID Action request and reply,
 *                     including the Actions and ActionData.
 * 02-29-08  02.00.02  Added MPI2_RAID_ACTION_ADATA_DISABL_FULL_REBUILD.
 * 05-21-08  02.00.03  Added MPI2_RAID_VOL_CREATION_NUM_PHYSDISKS so that
 *                     the PhysDisk array in MPI2_RAID_VOLUME_CREATION_STRUCT
 *                     can be sized by the build environment.
 * 07-30-09  02.00.04  Added proper define क्रम the Use Default Settings bit of
 *                     VolumeCreationFlags and marked the old one as obsolete.
 * 05-12-10  02.00.05  Added MPI2_RAID_VOL_FLAGS_OP_MDC define.
 * 08-24-10  02.00.06  Added MPI2_RAID_ACTION_COMPATIBILITY_CHECK aदीर्घ with
 *                     related काष्ठाures and defines.
 *                     Added product-specअगरic range to RAID Action values.
 * 11-18-11  02.00.07  Incorporating additions क्रम MPI v2.5.
 * 02-06-12  02.00.08  Added MPI2_RAID_ACTION_PHYSDISK_HIDDEN.
 * 07-26-12  02.00.09  Added ElapsedSeconds field to MPI2_RAID_VOL_INDICATOR.
 *                     Added MPI2_RAID_VOL_FLAGS_ELAPSED_SECONDS_VALID define.
 * 04-17-13  02.00.10  Added MPI25_RAID_ACTION_ADATA_ALLOW_PI.
 * 11-18-14  02.00.11  Updated copyright inक्रमmation.
 * --------------------------------------------------------------------------
 */

#अगर_अघोषित MPI2_RAID_H
#घोषणा MPI2_RAID_H

/*****************************************************************************
*
*              Integrated RAID Messages
*
*****************************************************************************/

/****************************************************************************
* RAID Action messages
****************************************************************************/

/* ActionDataWord defines क्रम use with MPI2_RAID_ACTION_CREATE_VOLUME action */
#घोषणा MPI25_RAID_ACTION_ADATA_ALLOW_PI            (0x80000000)

/*ActionDataWord defines क्रम use with MPI2_RAID_ACTION_DELETE_VOLUME action */
#घोषणा MPI2_RAID_ACTION_ADATA_KEEP_LBA0            (0x00000000)
#घोषणा MPI2_RAID_ACTION_ADATA_ZERO_LBA0            (0x00000001)

/*use MPI2_RAIDVOL0_SETTING_ defines from mpi2_cnfg.h क्रम
 *MPI2_RAID_ACTION_CHANGE_VOL_WRITE_CACHE action */

/*ActionDataWord defines क्रम use with
 *MPI2_RAID_ACTION_DISABLE_ALL_VOLUMES action */
#घोषणा MPI2_RAID_ACTION_ADATA_DISABL_FULL_REBUILD  (0x00000001)

/*ActionDataWord क्रम MPI2_RAID_ACTION_SET_RAID_FUNCTION_RATE Action */
प्रकार काष्ठा _MPI2_RAID_ACTION_RATE_DATA अणु
	U8 RateToChange;	/*0x00 */
	U8 RateOrMode;		/*0x01 */
	U16 DataScrubDuration;	/*0x02 */
पूर्ण MPI2_RAID_ACTION_RATE_DATA, *PTR_MPI2_RAID_ACTION_RATE_DATA,
	Mpi2RaidActionRateData_t, *pMpi2RaidActionRateData_t;

#घोषणा MPI2_RAID_ACTION_SET_RATE_RESYNC            (0x00)
#घोषणा MPI2_RAID_ACTION_SET_RATE_DATA_SCRUB        (0x01)
#घोषणा MPI2_RAID_ACTION_SET_RATE_POWERSAVE_MODE    (0x02)

/*ActionDataWord क्रम MPI2_RAID_ACTION_START_RAID_FUNCTION Action */
प्रकार काष्ठा _MPI2_RAID_ACTION_START_RAID_FUNCTION अणु
	U8 RAIDFunction;	/*0x00 */
	U8 Flags;		/*0x01 */
	U16 Reserved1;		/*0x02 */
पूर्ण MPI2_RAID_ACTION_START_RAID_FUNCTION,
	*PTR_MPI2_RAID_ACTION_START_RAID_FUNCTION,
	Mpi2RaidActionStartRaidFunction_t,
	*pMpi2RaidActionStartRaidFunction_t;

/*defines क्रम the RAIDFunction field */
#घोषणा MPI2_RAID_ACTION_START_BACKGROUND_INIT      (0x00)
#घोषणा MPI2_RAID_ACTION_START_ONLINE_CAP_EXPANSION (0x01)
#घोषणा MPI2_RAID_ACTION_START_CONSISTENCY_CHECK    (0x02)

/*defines क्रम the Flags field */
#घोषणा MPI2_RAID_ACTION_START_NEW                  (0x00)
#घोषणा MPI2_RAID_ACTION_START_RESUME               (0x01)

/*ActionDataWord क्रम MPI2_RAID_ACTION_STOP_RAID_FUNCTION Action */
प्रकार काष्ठा _MPI2_RAID_ACTION_STOP_RAID_FUNCTION अणु
	U8 RAIDFunction;	/*0x00 */
	U8 Flags;		/*0x01 */
	U16 Reserved1;		/*0x02 */
पूर्ण MPI2_RAID_ACTION_STOP_RAID_FUNCTION,
	*PTR_MPI2_RAID_ACTION_STOP_RAID_FUNCTION,
	Mpi2RaidActionStopRaidFunction_t,
	*pMpi2RaidActionStopRaidFunction_t;

/*defines क्रम the RAIDFunction field */
#घोषणा MPI2_RAID_ACTION_STOP_BACKGROUND_INIT       (0x00)
#घोषणा MPI2_RAID_ACTION_STOP_ONLINE_CAP_EXPANSION  (0x01)
#घोषणा MPI2_RAID_ACTION_STOP_CONSISTENCY_CHECK     (0x02)

/*defines क्रम the Flags field */
#घोषणा MPI2_RAID_ACTION_STOP_ABORT                 (0x00)
#घोषणा MPI2_RAID_ACTION_STOP_PAUSE                 (0x01)

/*ActionDataWord क्रम MPI2_RAID_ACTION_CREATE_HOT_SPARE Action */
प्रकार काष्ठा _MPI2_RAID_ACTION_HOT_SPARE अणु
	U8 HotSparePool;	/*0x00 */
	U8 Reserved1;		/*0x01 */
	U16 DevHandle;		/*0x02 */
पूर्ण MPI2_RAID_ACTION_HOT_SPARE, *PTR_MPI2_RAID_ACTION_HOT_SPARE,
	Mpi2RaidActionHotSpare_t, *pMpi2RaidActionHotSpare_t;

/*ActionDataWord क्रम MPI2_RAID_ACTION_DEVICE_FW_UPDATE_MODE Action */
प्रकार काष्ठा _MPI2_RAID_ACTION_FW_UPDATE_MODE अणु
	U8 Flags;		/*0x00 */
	U8 DeviceFirmwareUpdateModeTimeout;	/*0x01 */
	U16 Reserved1;		/*0x02 */
पूर्ण MPI2_RAID_ACTION_FW_UPDATE_MODE,
	*PTR_MPI2_RAID_ACTION_FW_UPDATE_MODE,
	Mpi2RaidActionFwUpdateMode_t,
	*pMpi2RaidActionFwUpdateMode_t;

/*ActionDataWord defines क्रम use with
 *MPI2_RAID_ACTION_DEVICE_FW_UPDATE_MODE action */
#घोषणा MPI2_RAID_ACTION_ADATA_DISABLE_FW_UPDATE        (0x00)
#घोषणा MPI2_RAID_ACTION_ADATA_ENABLE_FW_UPDATE         (0x01)

प्रकार जोड़ _MPI2_RAID_ACTION_DATA अणु
	U32 Word;
	MPI2_RAID_ACTION_RATE_DATA Rates;
	MPI2_RAID_ACTION_START_RAID_FUNCTION StartRaidFunction;
	MPI2_RAID_ACTION_STOP_RAID_FUNCTION StopRaidFunction;
	MPI2_RAID_ACTION_HOT_SPARE HotSpare;
	MPI2_RAID_ACTION_FW_UPDATE_MODE FwUpdateMode;
पूर्ण MPI2_RAID_ACTION_DATA, *PTR_MPI2_RAID_ACTION_DATA,
	Mpi2RaidActionData_t, *pMpi2RaidActionData_t;

/*RAID Action Request Message */
प्रकार काष्ठा _MPI2_RAID_ACTION_REQUEST अणु
	U8 Action;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 ChainOffset;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 VolDevHandle;	/*0x04 */
	U8 PhysDiskNum;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved2;		/*0x0A */
	U32 Reserved3;		/*0x0C */
	MPI2_RAID_ACTION_DATA ActionDataWord;	/*0x10 */
	MPI2_SGE_SIMPLE_UNION ActionDataSGE;	/*0x14 */
पूर्ण MPI2_RAID_ACTION_REQUEST, *PTR_MPI2_RAID_ACTION_REQUEST,
	Mpi2RaidActionRequest_t, *pMpi2RaidActionRequest_t;

/*RAID Action request Action values */

#घोषणा MPI2_RAID_ACTION_INDICATOR_STRUCT           (0x01)
#घोषणा MPI2_RAID_ACTION_CREATE_VOLUME              (0x02)
#घोषणा MPI2_RAID_ACTION_DELETE_VOLUME              (0x03)
#घोषणा MPI2_RAID_ACTION_DISABLE_ALL_VOLUMES        (0x04)
#घोषणा MPI2_RAID_ACTION_ENABLE_ALL_VOLUMES         (0x05)
#घोषणा MPI2_RAID_ACTION_PHYSDISK_OFFLINE           (0x0A)
#घोषणा MPI2_RAID_ACTION_PHYSDISK_ONLINE            (0x0B)
#घोषणा MPI2_RAID_ACTION_FAIL_PHYSDISK              (0x0F)
#घोषणा MPI2_RAID_ACTION_ACTIVATE_VOLUME            (0x11)
#घोषणा MPI2_RAID_ACTION_DEVICE_FW_UPDATE_MODE      (0x15)
#घोषणा MPI2_RAID_ACTION_CHANGE_VOL_WRITE_CACHE     (0x17)
#घोषणा MPI2_RAID_ACTION_SET_VOLUME_NAME            (0x18)
#घोषणा MPI2_RAID_ACTION_SET_RAID_FUNCTION_RATE     (0x19)
#घोषणा MPI2_RAID_ACTION_ENABLE_FAILED_VOLUME       (0x1C)
#घोषणा MPI2_RAID_ACTION_CREATE_HOT_SPARE           (0x1D)
#घोषणा MPI2_RAID_ACTION_DELETE_HOT_SPARE           (0x1E)
#घोषणा MPI2_RAID_ACTION_SYSTEM_SHUTDOWN_INITIATED  (0x20)
#घोषणा MPI2_RAID_ACTION_START_RAID_FUNCTION        (0x21)
#घोषणा MPI2_RAID_ACTION_STOP_RAID_FUNCTION         (0x22)
#घोषणा MPI2_RAID_ACTION_COMPATIBILITY_CHECK        (0x23)
#घोषणा MPI2_RAID_ACTION_PHYSDISK_HIDDEN            (0x24)
#घोषणा MPI2_RAID_ACTION_MIN_PRODUCT_SPECIFIC       (0x80)
#घोषणा MPI2_RAID_ACTION_MAX_PRODUCT_SPECIFIC       (0xFF)

/*RAID Volume Creation Structure */

/*
 *The following define can be customized क्रम the targeted product.
 */
#अगर_अघोषित MPI2_RAID_VOL_CREATION_NUM_PHYSDISKS
#घोषणा MPI2_RAID_VOL_CREATION_NUM_PHYSDISKS        (1)
#पूर्ण_अगर

प्रकार काष्ठा _MPI2_RAID_VOLUME_PHYSDISK अणु
	U8 RAIDSetNum;		/*0x00 */
	U8 PhysDiskMap;		/*0x01 */
	U16 PhysDiskDevHandle;	/*0x02 */
पूर्ण MPI2_RAID_VOLUME_PHYSDISK, *PTR_MPI2_RAID_VOLUME_PHYSDISK,
	Mpi2RaidVolumePhysDisk_t, *pMpi2RaidVolumePhysDisk_t;

/*defines क्रम the PhysDiskMap field */
#घोषणा MPI2_RAIDACTION_PHYSDISK_PRIMARY            (0x01)
#घोषणा MPI2_RAIDACTION_PHYSDISK_SECONDARY          (0x02)

प्रकार काष्ठा _MPI2_RAID_VOLUME_CREATION_STRUCT अणु
	U8 NumPhysDisks;	/*0x00 */
	U8 VolumeType;		/*0x01 */
	U16 Reserved1;		/*0x02 */
	U32 VolumeCreationFlags;	/*0x04 */
	U32 VolumeSettings;	/*0x08 */
	U8 Reserved2;		/*0x0C */
	U8 ResyncRate;		/*0x0D */
	U16 DataScrubDuration;	/*0x0E */
	U64 VolumeMaxLBA;	/*0x10 */
	U32 StripeSize;		/*0x18 */
	U8 Name[16];		/*0x1C */
	MPI2_RAID_VOLUME_PHYSDISK
		PhysDisk[MPI2_RAID_VOL_CREATION_NUM_PHYSDISKS];	/*0x2C */
पूर्ण MPI2_RAID_VOLUME_CREATION_STRUCT,
	*PTR_MPI2_RAID_VOLUME_CREATION_STRUCT,
	Mpi2RaidVolumeCreationStruct_t,
	*pMpi2RaidVolumeCreationStruct_t;

/*use MPI2_RAID_VOL_TYPE_ defines from mpi2_cnfg.h क्रम VolumeType */

/*defines क्रम the VolumeCreationFlags field */
#घोषणा MPI2_RAID_VOL_CREATION_DEFAULT_SETTINGS     (0x80000000)
#घोषणा MPI2_RAID_VOL_CREATION_BACKGROUND_INIT      (0x00000004)
#घोषणा MPI2_RAID_VOL_CREATION_LOW_LEVEL_INIT       (0x00000002)
#घोषणा MPI2_RAID_VOL_CREATION_MIGRATE_DATA         (0x00000001)
/*The following is an obsolete define.
 *It must be shअगरted left 24 bits in order to set the proper bit.
 */
#घोषणा MPI2_RAID_VOL_CREATION_USE_DEFAULT_SETTINGS (0x80)

/*RAID Online Capacity Expansion Structure */

प्रकार काष्ठा _MPI2_RAID_ONLINE_CAPACITY_EXPANSION अणु
	U32 Flags;		/*0x00 */
	U16 DevHandle0;		/*0x04 */
	U16 Reserved1;		/*0x06 */
	U16 DevHandle1;		/*0x08 */
	U16 Reserved2;		/*0x0A */
पूर्ण MPI2_RAID_ONLINE_CAPACITY_EXPANSION,
	*PTR_MPI2_RAID_ONLINE_CAPACITY_EXPANSION,
	Mpi2RaidOnlineCapacityExpansion_t,
	*pMpi2RaidOnlineCapacityExpansion_t;

/*RAID Compatibility Input Structure */

प्रकार काष्ठा _MPI2_RAID_COMPATIBILITY_INPUT_STRUCT अणु
	U16 SourceDevHandle;	/*0x00 */
	U16 CandidateDevHandle;	/*0x02 */
	U32 Flags;		/*0x04 */
	U32 Reserved1;		/*0x08 */
	U32 Reserved2;		/*0x0C */
पूर्ण MPI2_RAID_COMPATIBILITY_INPUT_STRUCT,
	*PTR_MPI2_RAID_COMPATIBILITY_INPUT_STRUCT,
	Mpi2RaidCompatibilityInputStruct_t,
	*pMpi2RaidCompatibilityInputStruct_t;

/*defines क्रम RAID Compatibility Structure Flags field */
#घोषणा MPI2_RAID_COMPAT_SOURCE_IS_VOLUME_FLAG      (0x00000002)
#घोषणा MPI2_RAID_COMPAT_REPORT_SOURCE_INFO_FLAG    (0x00000001)

/*RAID Volume Indicator Structure */

प्रकार काष्ठा _MPI2_RAID_VOL_INDICATOR अणु
	U64 TotalBlocks;	/*0x00 */
	U64 BlocksReमुख्यing;	/*0x08 */
	U32 Flags;		/*0x10 */
	U32 ElapsedSeconds;	/* 0x14 */
पूर्ण MPI2_RAID_VOL_INDICATOR, *PTR_MPI2_RAID_VOL_INDICATOR,
	Mpi2RaidVolIndicator_t, *pMpi2RaidVolIndicator_t;

/*defines क्रम RAID Volume Indicator Flags field */
#घोषणा MPI2_RAID_VOL_FLAGS_ELAPSED_SECONDS_VALID   (0x80000000)
#घोषणा MPI2_RAID_VOL_FLAGS_OP_MASK                 (0x0000000F)
#घोषणा MPI2_RAID_VOL_FLAGS_OP_BACKGROUND_INIT      (0x00000000)
#घोषणा MPI2_RAID_VOL_FLAGS_OP_ONLINE_CAP_EXPANSION (0x00000001)
#घोषणा MPI2_RAID_VOL_FLAGS_OP_CONSISTENCY_CHECK    (0x00000002)
#घोषणा MPI2_RAID_VOL_FLAGS_OP_RESYNC               (0x00000003)
#घोषणा MPI2_RAID_VOL_FLAGS_OP_MDC                  (0x00000004)

/*RAID Compatibility Result Structure */

प्रकार काष्ठा _MPI2_RAID_COMPATIBILITY_RESULT_STRUCT अणु
	U8 State;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U16 Reserved2;		/*0x02 */
	U32 GenericAttributes;	/*0x04 */
	U32 OEMSpecअगरicAttributes;	/*0x08 */
	U32 Reserved3;		/*0x0C */
	U32 Reserved4;		/*0x10 */
पूर्ण MPI2_RAID_COMPATIBILITY_RESULT_STRUCT,
	*PTR_MPI2_RAID_COMPATIBILITY_RESULT_STRUCT,
	Mpi2RaidCompatibilityResultStruct_t,
	*pMpi2RaidCompatibilityResultStruct_t;

/*defines क्रम RAID Compatibility Result Structure State field */
#घोषणा MPI2_RAID_COMPAT_STATE_COMPATIBLE           (0x00)
#घोषणा MPI2_RAID_COMPAT_STATE_NOT_COMPATIBLE       (0x01)

/*defines क्रम RAID Compatibility Result Structure GenericAttributes field */
#घोषणा MPI2_RAID_COMPAT_GENATTRIB_4K_SECTOR            (0x00000010)

#घोषणा MPI2_RAID_COMPAT_GENATTRIB_MEDIA_MASK           (0x0000000C)
#घोषणा MPI2_RAID_COMPAT_GENATTRIB_SOLID_STATE_DRIVE    (0x00000008)
#घोषणा MPI2_RAID_COMPAT_GENATTRIB_HARD_DISK_DRIVE      (0x00000004)

#घोषणा MPI2_RAID_COMPAT_GENATTRIB_PROTOCOL_MASK        (0x00000003)
#घोषणा MPI2_RAID_COMPAT_GENATTRIB_SAS_PROTOCOL         (0x00000002)
#घोषणा MPI2_RAID_COMPAT_GENATTRIB_SATA_PROTOCOL        (0x00000001)

/*RAID Action Reply ActionData जोड़ */
प्रकार जोड़ _MPI2_RAID_ACTION_REPLY_DATA अणु
	U32 Word[6];
	MPI2_RAID_VOL_INDICATOR RaidVolumeIndicator;
	U16 VolDevHandle;
	U8 VolumeState;
	U8 PhysDiskNum;
	MPI2_RAID_COMPATIBILITY_RESULT_STRUCT RaidCompatibilityResult;
पूर्ण MPI2_RAID_ACTION_REPLY_DATA, *PTR_MPI2_RAID_ACTION_REPLY_DATA,
	Mpi2RaidActionReplyData_t, *pMpi2RaidActionReplyData_t;

/*use MPI2_RAIDVOL0_SETTING_ defines from mpi2_cnfg.h क्रम
 *MPI2_RAID_ACTION_CHANGE_VOL_WRITE_CACHE action */

/*RAID Action Reply Message */
प्रकार काष्ठा _MPI2_RAID_ACTION_REPLY अणु
	U8 Action;		/*0x00 */
	U8 Reserved1;		/*0x01 */
	U8 MsgLength;		/*0x02 */
	U8 Function;		/*0x03 */
	U16 VolDevHandle;	/*0x04 */
	U8 PhysDiskNum;		/*0x06 */
	U8 MsgFlags;		/*0x07 */
	U8 VP_ID;		/*0x08 */
	U8 VF_ID;		/*0x09 */
	U16 Reserved2;		/*0x0A */
	U16 Reserved3;		/*0x0C */
	U16 IOCStatus;		/*0x0E */
	U32 IOCLogInfo;		/*0x10 */
	MPI2_RAID_ACTION_REPLY_DATA ActionData;	/*0x14 */
पूर्ण MPI2_RAID_ACTION_REPLY, *PTR_MPI2_RAID_ACTION_REPLY,
	Mpi2RaidActionReply_t, *pMpi2RaidActionReply_t;

#पूर्ण_अगर
