<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/***************************************************************************
 *                                                                         *
 *  Copyright (c) 2000-2008 LSI Corporation.  All rights reserved.         *
 *                                                                         *
 * Description                                                             *
 * ------------                                                            *
 * This include file contains SAS firmware पूर्णांकerface IOC Log Info codes    *
 *                                                                         *
 *-------------------------------------------------------------------------*
 */

#अगर_अघोषित IOPI_IOCLOGINFO_H_INCLUDED
#घोषणा IOPI_IOCLOGINFO_H_INCLUDED

#घोषणा SAS_LOGINFO_NEXUS_LOSS		0x31170000
#घोषणा SAS_LOGINFO_MASK		0xFFFF0000

/****************************************************************************/
/*  IOC LOGINFO defines, 0x00000000 - 0x0FFFFFFF                            */
/*  Format:                                                                 */
/*      Bits 31-28: MPI_IOCLOGINFO_TYPE_SAS (3)                             */
/*      Bits 27-24: IOC_LOGINFO_ORIGINATOR: 0=IOP, 1=PL, 2=IR               */
/*      Bits 23-16: LOGINFO_CODE                                            */
/*      Bits 15-0:  LOGINFO_CODE Specअगरic                                   */
/****************************************************************************/

/****************************************************************************/
/* IOC_LOGINFO_ORIGINATOR defines                                           */
/****************************************************************************/
#घोषणा IOC_LOGINFO_ORIGINATOR_IOP                      (0x00000000)
#घोषणा IOC_LOGINFO_ORIGINATOR_PL                       (0x01000000)
#घोषणा IOC_LOGINFO_ORIGINATOR_IR                       (0x02000000)

#घोषणा IOC_LOGINFO_ORIGINATOR_MASK                     (0x0F000000)

/****************************************************************************/
/* LOGINFO_CODE defines                                                     */
/****************************************************************************/
#घोषणा IOC_LOGINFO_CODE_MASK                           (0x00FF0000)
#घोषणा IOC_LOGINFO_CODE_SHIFT                          (16)

/****************************************************************************/
/* IOP LOGINFO_CODE defines, valid अगर IOC_LOGINFO_ORIGINATOR = IOP          */
/****************************************************************************/
#घोषणा IOP_LOGINFO_CODE_INVALID_SAS_ADDRESS                 (0x00010000)
#घोषणा IOP_LOGINFO_CODE_UNUSED2                             (0x00020000)
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE                 (0x00030000)
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE_RT              (0x00030100) /* Route Table Entry not found */
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE_PN              (0x00030200) /* Invalid Page Number */
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE_FORM            (0x00030300) /* Invalid FORM */
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE_PT              (0x00030400) /* Invalid Page Type */
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE_DNM             (0x00030500) /* Device Not Mapped */
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE_PERSIST         (0x00030600) /* Persistent Page not found */
#घोषणा IOP_LOGINFO_CODE_CONFIG_INVALID_PAGE_DEFAULT         (0x00030700) /* Default Page not found */

#घोषणा IOP_LOGINFO_CODE_FWUPLOAD_NO_FLASH_AVAILABLE         (0x0003E000) /* Tried to upload from flash, but there is none */
#घोषणा IOP_LOGINFO_CODE_FWUPLOAD_UNKNOWN_IMAGE_TYPE         (0x0003E001) /* ImageType field contents were invalid */
#घोषणा IOP_LOGINFO_CODE_FWUPLOAD_WRONG_IMAGE_SIZE           (0x0003E002) /* ImageSize field in TCSGE was bad/offset in MfgPg 4 was wrong */
#घोषणा IOP_LOGINFO_CODE_FWUPLOAD_ENTIRE_FLASH_UPLOAD_FAILED (0x0003E003) /* Error occurred जबतक attempting to upload the entire flash */
#घोषणा IOP_LOGINFO_CODE_FWUPLOAD_REGION_UPLOAD_FAILED       (0x0003E004) /* Error occurred जबतक attempting to upload single flash region */
#घोषणा IOP_LOGINFO_CODE_FWUPLOAD_DMA_FAILURE                (0x0003E005) /* Problem occurred जबतक DMAing FW to host memory */

#घोषणा IOP_LOGINFO_CODE_DIAG_MSG_ERROR                      (0x00040000) /* Error handling diag msg - or'd with diag status */

#घोषणा IOP_LOGINFO_CODE_TASK_TERMINATED                     (0x00050000)

#घोषणा IOP_LOGINFO_CODE_ENCL_MGMT_READ_ACTION_ERR0R         (0x00060001) /* Read Action not supported क्रम SEP msg */
#घोषणा IOP_LOGINFO_CODE_ENCL_MGMT_INVALID_BUS_ID_ERR0R      (0x00060002) /* Invalid Bus/ID in SEP msg */

#घोषणा IOP_LOGINFO_CODE_TARGET_ASSIST_TERMINATED            (0x00070001)
#घोषणा IOP_LOGINFO_CODE_TARGET_STATUS_SEND_TERMINATED       (0x00070002)
#घोषणा IOP_LOGINFO_CODE_TARGET_MODE_ABORT_ALL_IO            (0x00070003)
#घोषणा IOP_LOGINFO_CODE_TARGET_MODE_ABORT_EXACT_IO          (0x00070004)
#घोषणा IOP_LOGINFO_CODE_TARGET_MODE_ABORT_EXACT_IO_REQ      (0x00070005)

#घोषणा IOP_LOGINFO_CODE_LOG_TIMESTAMP_EVENT                 (0x00080000)

/****************************************************************************/
/* PL LOGINFO_CODE defines, valid अगर IOC_LOGINFO_ORIGINATOR = PL            */
/****************************************************************************/
#घोषणा PL_LOGINFO_CODE_OPEN_FAILURE                         (0x00010000) /* see SUB_CODE_OPEN_FAIL_ below */

#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_NO_DEST_TIME_OUT       (0x00000001)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_PATHWAY_BLOCKED        (0x00000002)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RES_CONTINUE0          (0x00000003)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RES_CONTINUE1          (0x00000004)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RES_INITIALIZE0        (0x00000005)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RES_INITIALIZE1        (0x00000006)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RES_STOP0              (0x00000007)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RES_STOP1              (0x00000008)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RETRY                  (0x00000009)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_BREAK                  (0x0000000A)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_UNUSED_0B              (0x0000000B)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_OPEN_TIMEOUT_EXP       (0x0000000C)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_UNUSED_0D              (0x0000000D)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_DVTBLE_ACCSS_FAIL      (0x0000000E)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_BAD_DEST               (0x00000011)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RATE_NOT_SUPP          (0x00000012)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_PROT_NOT_SUPP          (0x00000013)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RESERVED_ABANDON0      (0x00000014)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RESERVED_ABANDON1      (0x00000015)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RESERVED_ABANDON2      (0x00000016)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_RESERVED_ABANDON3      (0x00000017)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_STP_RESOURCES_BSY      (0x00000018)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_WRONG_DESTINATION      (0x00000019)

#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_PATH_BLOCKED           (0x0000001B) /* Retry Timeout */
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAIL_AWT_MAXED              (0x0000001C) /* Retry Timeout */



#घोषणा PL_LOGINFO_CODE_INVALID_SGL                          (0x00020000)
#घोषणा PL_LOGINFO_CODE_WRONG_REL_OFF_OR_FRAME_LENGTH        (0x00030000)
#घोषणा PL_LOGINFO_CODE_FRAME_XFER_ERROR                     (0x00040000)
#घोषणा PL_LOGINFO_CODE_TX_FM_CONNECTED_LOW                  (0x00050000)
#घोषणा PL_LOGINFO_CODE_SATA_NON_NCQ_RW_ERR_BIT_SET          (0x00060000)
#घोषणा PL_LOGINFO_CODE_SATA_READ_LOG_RECEIVE_DATA_ERR       (0x00070000)
#घोषणा PL_LOGINFO_CODE_SATA_NCQ_FAIL_ALL_CMDS_AFTR_ERR      (0x00080000)
#घोषणा PL_LOGINFO_CODE_SATA_ERR_IN_RCV_SET_DEV_BIT_FIS      (0x00090000)
#घोषणा PL_LOGINFO_CODE_RX_FM_INVALID_MESSAGE                (0x000A0000)
#घोषणा PL_LOGINFO_CODE_RX_CTX_MESSAGE_VALID_ERROR           (0x000B0000)
#घोषणा PL_LOGINFO_CODE_RX_FM_CURRENT_FRAME_ERROR            (0x000C0000)
#घोषणा PL_LOGINFO_CODE_SATA_LINK_DOWN                       (0x000D0000)
#घोषणा PL_LOGINFO_CODE_DISCOVERY_SATA_INIT_W_IOS            (0x000E0000)
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE                  (0x000F0000)
#घोषणा PL_LOGINFO_CODE_CONFIG_PL_NOT_INITIALIZED            (0x000F0001) /* PL not yet initialized, can't करो config page req. */
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE_PT               (0x000F0100) /* Invalid Page Type */
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE_NUM_PHYS         (0x000F0200) /* Invalid Number of Phys */
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE_NOT_IMP          (0x000F0300) /* Case Not Handled */
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE_NO_DEV           (0x000F0400) /* No Device Found */
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE_FORM             (0x000F0500) /* Invalid FORM */
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE_PHY              (0x000F0600) /* Invalid Phy */
#घोषणा PL_LOGINFO_CODE_CONFIG_INVALID_PAGE_NO_OWNER         (0x000F0700) /* No Owner Found */
#घोषणा PL_LOGINFO_CODE_DSCVRY_SATA_INIT_TIMEOUT             (0x00100000)
#घोषणा PL_LOGINFO_CODE_RESET                                (0x00110000) /* See Sub-Codes below (PL_LOGINFO_SUB_CODE) */
#घोषणा PL_LOGINFO_CODE_ABORT                                (0x00120000) /* See Sub-Codes below  (PL_LOGINFO_SUB_CODE)*/
#घोषणा PL_LOGINFO_CODE_IO_NOT_YET_EXECUTED                  (0x00130000)
#घोषणा PL_LOGINFO_CODE_IO_EXECUTED                          (0x00140000)
#घोषणा PL_LOGINFO_CODE_PERS_RESV_OUT_NOT_AFFIL_OWNER        (0x00150000)
#घोषणा PL_LOGINFO_CODE_OPEN_TXDMA_ABORT                     (0x00160000)
#घोषणा PL_LOGINFO_CODE_IO_DEVICE_MISSING_DELAY_RETRY        (0x00170000)
#घोषणा PL_LOGINFO_CODE_IO_CANCELLED_DUE_TO_R_ERR            (0x00180000)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE                     (0x00000100)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_NO_DEST_TIMEOUT     (0x00000101)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_SATA_NEG_RATE_2HI   (0x00000102)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_RATE_NOT_SUPPORTED  (0x00000103)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_BREAK               (0x00000104)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_ZONE_VIOLATION      (0x00000114)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_ABANDON0            (0x00000114) /* Open Reject (Zone Violation) - available on SAS-2 devices */
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_ABANDON1            (0x00000115)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_ABANDON2            (0x00000116)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_ABANDON3            (0x00000117)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_ORR_TIMEOUT         (0x0000011A) /* Open Reject (Retry) Timeout */
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_PATH_BLOCKED        (0x0000011B)
#घोषणा PL_LOGINFO_SUB_CODE_OPEN_FAILURE_AWT_MAXED           (0x0000011C) /* Arbitration Wait Timer Maxed */

#घोषणा PL_LOGINFO_SUB_CODE_TARGET_BUS_RESET                 (0x00000120)
#घोषणा PL_LOGINFO_SUB_CODE_TRANSPORT_LAYER                  (0x00000130)  /* Leave lower nibble (1-f) reserved. */
#घोषणा PL_LOGINFO_SUB_CODE_PORT_LAYER                       (0x00000140)  /* Leave lower nibble (1-f) reserved. */


#घोषणा PL_LOGINFO_SUB_CODE_INVALID_SGL                      (0x00000200)
#घोषणा PL_LOGINFO_SUB_CODE_WRONG_REL_OFF_OR_FRAME_LENGTH    (0x00000300)
#घोषणा PL_LOGINFO_SUB_CODE_FRAME_XFER_ERROR                 (0x00000400)
/* Bits 0-3 encode Transport Status Register (offset 0x08) */
/* Bit 0 is Status Bit 0: FrameXferErr */
/* Bit 1 & 2 are Status Bits 16 and 17: FrameXmitErrStatus */
/* Bit 3 is Status Bit 18 WriteDataLenghtGTDataLengthErr */

#घोषणा PL_LOGINFO_SUB_CODE_TX_FM_CONNECTED_LOW              (0x00000500)
#घोषणा PL_LOGINFO_SUB_CODE_SATA_NON_NCQ_RW_ERR_BIT_SET      (0x00000600)
#घोषणा PL_LOGINFO_SUB_CODE_SATA_READ_LOG_RECEIVE_DATA_ERR   (0x00000700)
#घोषणा PL_LOGINFO_SUB_CODE_SATA_NCQ_FAIL_ALL_CMDS_AFTR_ERR  (0x00000800)
#घोषणा PL_LOGINFO_SUB_CODE_SATA_ERR_IN_RCV_SET_DEV_BIT_FIS  (0x00000900)
#घोषणा PL_LOGINFO_SUB_CODE_RX_FM_INVALID_MESSAGE            (0x00000A00)
#घोषणा PL_LOGINFO_SUB_CODE_RX_CTX_MESSAGE_VALID_ERROR       (0x00000B00)
#घोषणा PL_LOGINFO_SUB_CODE_RX_FM_CURRENT_FRAME_ERROR        (0x00000C00)
#घोषणा PL_LOGINFO_SUB_CODE_SATA_LINK_DOWN                   (0x00000D00)
#घोषणा PL_LOGINFO_SUB_CODE_DISCOVERY_SATA_INIT_W_IOS        (0x00000E00)
#घोषणा PL_LOGINFO_SUB_CODE_DISCOVERY_REMOTE_SEP_RESET       (0x00000E01)
#घोषणा PL_LOGINFO_SUB_CODE_SECOND_OPEN                      (0x00000F00)
#घोषणा PL_LOGINFO_SUB_CODE_DSCVRY_SATA_INIT_TIMEOUT         (0x00001000)
#घोषणा PL_LOGINFO_SUB_CODE_BREAK_ON_SATA_CONNECTION         (0x00002000)
/* not currently used in मुख्यline */
#घोषणा PL_LOGINFO_SUB_CODE_BREAK_ON_STUCK_LINK              (0x00003000)
#घोषणा PL_LOGINFO_SUB_CODE_BREAK_ON_STUCK_LINK_AIP          (0x00004000)
#घोषणा PL_LOGINFO_SUB_CODE_BREAK_ON_INCOMPLETE_BREAK_RCVD   (0x00005000)

#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SMP_FRAME_FAILURE          (0x00200000) /* Can't get SMP Frame */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SMP_READ_ERROR             (0x00200010) /* Error occurred on SMP Read */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SMP_WRITE_ERROR            (0x00200020) /* Error occurred on SMP Write */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_NOT_SUPPORTED_ON_ENCL      (0x00200040) /* Encl Mgmt services not available क्रम this WWID */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_ADDR_MODE_NOT_SUPPORTED    (0x00200050) /* Address Mode not suppored */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_BAD_SLOT_NUM               (0x00200060) /* Invalid Slot Number in SEP Msg */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SGPIO_NOT_PRESENT          (0x00200070) /* SGPIO not present/enabled */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_GPIO_NOT_CONFIGURED        (0x00200080) /* GPIO not configured */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_GPIO_FRAME_ERROR           (0x00200090) /* GPIO can't allocate a frame */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_GPIO_CONFIG_PAGE_ERROR     (0x002000A0) /* GPIO failed config page request */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SES_FRAME_ALLOC_ERROR      (0x002000B0) /* Can't get frame क्रम SES command */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SES_IO_ERROR               (0x002000C0) /* I/O execution error */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SES_RETRIES_EXHAUSTED      (0x002000D0) /* SEP I/O retries exhausted */
#घोषणा PL_LOGINFO_CODE_ENCL_MGMT_SMP_FRAME_ALLOC_ERROR      (0x002000E0) /* Can't get frame क्रम SMP command */

#घोषणा PL_LOGINFO_DA_SEP_NOT_PRESENT                        (0x00200100) /* SEP not present when msg received */
#घोषणा PL_LOGINFO_DA_SEP_SINGLE_THREAD_ERROR                (0x00200101) /* Can only accept 1 msg at a समय */
#घोषणा PL_LOGINFO_DA_SEP_ISTWI_INTR_IN_IDLE_STATE           (0x00200102) /* ISTWI पूर्णांकerrupt recvd. जबतक IDLE */
#घोषणा PL_LOGINFO_DA_SEP_RECEIVED_NACK_FROM_SLAVE           (0x00200103) /* SEP NACK'd, it is busy */
#घोषणा PL_LOGINFO_DA_SEP_DID_NOT_RECEIVE_ACK                (0x00200104) /* SEP didn't rcv. ACK (Last Rcvd Bit = 1) */
#घोषणा PL_LOGINFO_DA_SEP_BAD_STATUS_HDR_CHKSUM              (0x00200105) /* SEP stopped or sent bad chksum in Hdr */
#घोषणा PL_LOGINFO_DA_SEP_STOP_ON_DATA                       (0x00200106) /* SEP stopped जबतक transferring data */
#घोषणा PL_LOGINFO_DA_SEP_STOP_ON_SENSE_DATA                 (0x00200107) /* SEP stopped जबतक transferring sense data */
#घोषणा PL_LOGINFO_DA_SEP_UNSUPPORTED_SCSI_STATUS_1          (0x00200108) /* SEP वापसed unknown scsi status */
#घोषणा PL_LOGINFO_DA_SEP_UNSUPPORTED_SCSI_STATUS_2          (0x00200109) /* SEP वापसed unknown scsi status */
#घोषणा PL_LOGINFO_DA_SEP_CHKSUM_ERROR_AFTER_STOP            (0x0020010A) /* SEP वापसed bad chksum after STOP */
#घोषणा PL_LOGINFO_DA_SEP_CHKSUM_ERROR_AFTER_STOP_GETDATA    (0x0020010B) /* SEP वापसed bad chksum after STOP जबतक gettin data*/
#घोषणा PL_LOGINFO_DA_SEP_UNSUPPORTED_COMMAND                (0x0020010C) /* SEP करोesn't support CDB opcode f/w location 1 */
#घोषणा PL_LOGINFO_DA_SEP_UNSUPPORTED_COMMAND_2              (0x0020010D) /* SEP करोesn't support CDB opcode f/w location 2 */
#घोषणा PL_LOGINFO_DA_SEP_UNSUPPORTED_COMMAND_3              (0x0020010E) /* SEP करोesn't support CDB opcode f/w location 3 */


/****************************************************************************/
/* IR LOGINFO_CODE defines, valid अगर IOC_LOGINFO_ORIGINATOR = IR            */
/****************************************************************************/
#घोषणा IR_LOGINFO_RAID_ACTION_ERROR                           (0x00010000)
#घोषणा IR_LOGINFO_CODE_UNUSED2                                (0x00020000)

/* Amount of inक्रमmation passed करोwn क्रम Create Volume is too large */
#घोषणा IR_LOGINFO_VOLUME_CREATE_INVALID_LENGTH                (0x00010001)
/* Creation of duplicate volume attempted (Bus/Target ID checked) */
#घोषणा IR_LOGINFO_VOLUME_CREATE_DUPLICATE                     (0x00010002)
/* Creation failed due to maximum number of supported volumes exceeded */
#घोषणा IR_LOGINFO_VOLUME_CREATE_NO_SLOTS                      (0x00010003)
/* Creation failed due to DMA error in trying to पढ़ो from host */
#घोषणा IR_LOGINFO_VOLUME_CREATE_DMA_ERROR                     (0x00010004)
/* Creation failed due to invalid volume type passed करोwn */
#घोषणा IR_LOGINFO_VOLUME_CREATE_INVALID_VOLUME_TYPE           (0x00010005)
/* Creation failed due to error पढ़ोing MFG Page 4 */
#घोषणा IR_LOGINFO_VOLUME_MFG_PAGE4_ERROR                      (0x00010006)
/* Creation failed when trying to create पूर्णांकernal काष्ठाures */
#घोषणा IR_LOGINFO_VOLUME_INTERNAL_CONFIG_STRUCTURE_ERROR      (0x00010007)

/* Activation failed due to trying to activate an alपढ़ोy active volume */
#घोषणा IR_LOGINFO_VOLUME_ACTIVATING_AN_ACTIVE_VOLUME          (0x00010010)
/* Activation failed due to trying to active unsupported volume type  */
#घोषणा IR_LOGINFO_VOLUME_ACTIVATING_INVALID_VOLUME_TYPE       (0x00010011)
/* Activation failed due to trying to active too many volumes  */
#घोषणा IR_LOGINFO_VOLUME_ACTIVATING_TOO_MANY_VOLUMES          (0x00010012)
/* Activation failed due to Volume ID in use alपढ़ोy */
#घोषणा IR_LOGINFO_VOLUME_ACTIVATING_VOLUME_ID_IN_USE          (0x00010013)
/* Activation failed call to activateVolume वापसed failure */
#घोषणा IR_LOGINFO_VOLUME_ACTIVATE_VOLUME_FAILED               (0x00010014)
/* Activation failed trying to import the volume */
#घोषणा IR_LOGINFO_VOLUME_ACTIVATING_IMPORT_VOLUME_FAILED      (0x00010015)
/* Activation failed trying to import the volume */
#घोषणा IR_LOGINFO_VOLUME_ACTIVATING_TOO_MANY_PHYS_DISKS       (0x00010016)

/* Phys Disk failed, too many phys disks */
#घोषणा IR_LOGINFO_PHYSDISK_CREATE_TOO_MANY_DISKS              (0x00010020)
/* Amount of inक्रमmation passed करोwn क्रम Create Pnysdisk is too large */
#घोषणा IR_LOGINFO_PHYSDISK_CREATE_INVALID_LENGTH              (0x00010021)
/* Creation failed due to DMA error in trying to पढ़ो from host */
#घोषणा IR_LOGINFO_PHYSDISK_CREATE_DMA_ERROR                   (0x00010022)
/* Creation failed due to invalid Bus TargetID passed करोwn */
#घोषणा IR_LOGINFO_PHYSDISK_CREATE_BUS_TID_INVALID             (0x00010023)
/* Creation failed due to error in creating RAID Phys Disk Config Page */
#घोषणा IR_LOGINFO_PHYSDISK_CREATE_CONFIG_PAGE_ERROR           (0x00010024)


/* Compatibility Error : IR Disabled */
#घोषणा IR_LOGINFO_COMPAT_ERROR_RAID_DISABLED                  (0x00010030)
/* Compatibility Error : Inquiry Command failed */
#घोषणा IR_LOGINFO_COMPAT_ERROR_INQUIRY_FAILED                 (0x00010031)
/* Compatibility Error : Device not direct access device */
#घोषणा IR_LOGINFO_COMPAT_ERROR_NOT_सूचीECT_ACCESS              (0x00010032)
/* Compatibility Error : Removable device found */
#घोषणा IR_LOGINFO_COMPAT_ERROR_REMOVABLE_FOUND                (0x00010033)
/* Compatibility Error : Device SCSI Version not 2 or higher */
#घोषणा IR_LOGINFO_COMPAT_ERROR_NEED_SCSI_2_OR_HIGHER          (0x00010034)
/* Compatibility Error : SATA device, 48 BIT LBA not supported */
#घोषणा IR_LOGINFO_COMPAT_ERROR_SATA_48BIT_LBA_NOT_SUPPORTED   (0x00010035)
/* Compatibility Error : Device करोes not have 512 byte block sizes */
#घोषणा IR_LOGINFO_COMPAT_ERROR_DEVICE_NOT_512_BYTE_BLOCK      (0x00010036)
/* Compatibility Error : Volume Type check failed */
#घोषणा IR_LOGINFO_COMPAT_ERROR_VOLUME_TYPE_CHECK_FAILED       (0x00010037)
/* Compatibility Error : Volume Type is unsupported by FW */
#घोषणा IR_LOGINFO_COMPAT_ERROR_UNSUPPORTED_VOLUME_TYPE        (0x00010038)
/* Compatibility Error : Disk drive too small क्रम use in volume */
#घोषणा IR_LOGINFO_COMPAT_ERROR_DISK_TOO_SMALL                 (0x00010039)
/* Compatibility Error : Phys disk क्रम Create Volume not found */
#घोषणा IR_LOGINFO_COMPAT_ERROR_PHYS_DISK_NOT_FOUND            (0x0001003A)
/* Compatibility Error : membership count error, too many or too few disks क्रम volume type */
#घोषणा IR_LOGINFO_COMPAT_ERROR_MEMBERSHIP_COUNT               (0x0001003B)
/* Compatibility Error : Disk stripe sizes must be 64KB */
#घोषणा IR_LOGINFO_COMPAT_ERROR_NON_64K_STRIPE_SIZE            (0x0001003C)
/* Compatibility Error : IME size limited to < 2TB */
#घोषणा IR_LOGINFO_COMPAT_ERROR_IME_VOL_NOT_CURRENTLY_SUPPORTED (0x0001003D)

/* Device Firmware Update: DFU can only be started once */
#घोषणा IR_LOGINFO_DEV_FW_UPDATE_ERR_DFU_IN_PROGRESS            (0x00010050)
/* Device Firmware Update: Volume must be Optimal/Active/non-Quiesced */
#घोषणा IR_LOGINFO_DEV_FW_UPDATE_ERR_DEVICE_IN_INVALID_STATE    (0x00010051)
/* Device Firmware Update: DFU Timeout cannot be zero */
#घोषणा IR_LOGINFO_DEV_FW_UPDATE_ERR_INVALID_TIMEOUT            (0x00010052)
/* Device Firmware Update: CREATE TIMER FAILED */
#घोषणा IR_LOGINFO_DEV_FW_UPDATE_ERR_NO_TIMERS                  (0x00010053)
/* Device Firmware Update: Failed to पढ़ो SAS_IO_UNIT_PG_1 */
#घोषणा IR_LOGINFO_DEV_FW_UPDATE_ERR_READING_CFG_PAGE           (0x00010054)
/* Device Firmware Update: Invalid SAS_IO_UNIT_PG_1 value(s) */
#घोषणा IR_LOGINFO_DEV_FW_UPDATE_ERR_PORT_IO_TIMEOUTS_REQUIRED  (0x00010055)
/* Device Firmware Update: Unable to allocate memory क्रम page */
#घोषणा IR_LOGINFO_DEV_FW_UPDATE_ERR_ALLOC_CFG_PAGE             (0x00010056)


/****************************************************************************/
/* Defines क्रम convenience                                                  */
/****************************************************************************/
#घोषणा IOC_LOGINFO_PREFIX_IOP                          ((MPI_IOCLOGINFO_TYPE_SAS << MPI_IOCLOGINFO_TYPE_SHIFT) | IOC_LOGINFO_ORIGINATOR_IOP)
#घोषणा IOC_LOGINFO_PREFIX_PL                           ((MPI_IOCLOGINFO_TYPE_SAS << MPI_IOCLOGINFO_TYPE_SHIFT) | IOC_LOGINFO_ORIGINATOR_PL)
#घोषणा IOC_LOGINFO_PREFIX_IR                           ((MPI_IOCLOGINFO_TYPE_SAS << MPI_IOCLOGINFO_TYPE_SHIFT) | IOC_LOGINFO_ORIGINATOR_IR)

#पूर्ण_अगर /* end of file */

