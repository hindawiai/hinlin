<शैली गुरु>
/*
 * VMware PVSCSI header file
 *
 * Copyright (C) 2008-2014, VMware, Inc. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 */

#अगर_अघोषित _VMW_PVSCSI_H_
#घोषणा _VMW_PVSCSI_H_

#समावेश <linux/types.h>

#घोषणा PVSCSI_DRIVER_VERSION_STRING   "1.0.7.0-k"

#घोषणा PVSCSI_MAX_NUM_SG_ENTRIES_PER_SEGMENT 128

#घोषणा MASK(n)        ((1 << (n)) - 1)        /* make an n-bit mask */

#घोषणा PCI_DEVICE_ID_VMWARE_PVSCSI	0x07C0

/*
 * host adapter status/error codes
 */
क्रमागत HostBusAdapterStatus अणु
	BTSTAT_SUCCESS       = 0x00,  /* CCB complete normally with no errors */
	BTSTAT_LINKED_COMMAND_COMPLETED           = 0x0a,
	BTSTAT_LINKED_COMMAND_COMPLETED_WITH_FLAG = 0x0b,
	BTSTAT_DATA_UNDERRUN = 0x0c,
	BTSTAT_SELTIMEO      = 0x11,  /* SCSI selection समयout */
	BTSTAT_DATARUN       = 0x12,  /* data overrun/underrun */
	BTSTAT_BUSFREE       = 0x13,  /* unexpected bus मुक्त */
	BTSTAT_INVPHASE      = 0x14,  /* invalid bus phase or sequence
				       * requested by target */
	BTSTAT_LUNMISMATCH   = 0x17,  /* linked CCB has dअगरferent LUN from
				       * first CCB */
	BTSTAT_INVPARAM      = 0x1a,  /* invalid parameter in CCB or segment
				       * list */
	BTSTAT_SENSFAILED    = 0x1b,  /* स्वतः request sense failed */
	BTSTAT_TAGREJECT     = 0x1c,  /* SCSI II tagged queueing message
				       * rejected by target */
	BTSTAT_BADMSG        = 0x1d,  /* unsupported message received by the
				       * host adapter */
	BTSTAT_HAHARDWARE    = 0x20,  /* host adapter hardware failed */
	BTSTAT_NORESPONSE    = 0x21,  /* target did not respond to SCSI ATN,
				       * sent a SCSI RST */
	BTSTAT_SENTRST       = 0x22,  /* host adapter निश्चितed a SCSI RST */
	BTSTAT_RECVRST       = 0x23,  /* other SCSI devices निश्चितed a SCSI
				       * RST */
	BTSTAT_DISCONNECT    = 0x24,  /* target device reconnected improperly
				       * (w/o tag) */
	BTSTAT_BUSRESET      = 0x25,  /* host adapter issued BUS device reset */
	BTSTAT_ABORTQUEUE    = 0x26,  /* पात queue generated */
	BTSTAT_HASOFTWARE    = 0x27,  /* host adapter software error */
	BTSTAT_HATIMEOUT     = 0x30,  /* host adapter hardware समयout error */
	BTSTAT_SCSIPARITY    = 0x34,  /* SCSI parity error detected */
पूर्ण;

/*
 * SCSI device status values.
 */
क्रमागत ScsiDeviceStatus अणु
	SDSTAT_GOOD  = 0x00, /* No errors. */
	SDSTAT_CHECK = 0x02, /* Check condition. */
पूर्ण;

/*
 * Register offsets.
 *
 * These रेजिस्टरs are accessible both via i/o space and mm i/o.
 */

क्रमागत PVSCSIRegOffset अणु
	PVSCSI_REG_OFFSET_COMMAND        =    0x0,
	PVSCSI_REG_OFFSET_COMMAND_DATA   =    0x4,
	PVSCSI_REG_OFFSET_COMMAND_STATUS =    0x8,
	PVSCSI_REG_OFFSET_LAST_STS_0     =  0x100,
	PVSCSI_REG_OFFSET_LAST_STS_1     =  0x104,
	PVSCSI_REG_OFFSET_LAST_STS_2     =  0x108,
	PVSCSI_REG_OFFSET_LAST_STS_3     =  0x10c,
	PVSCSI_REG_OFFSET_INTR_STATUS    = 0x100c,
	PVSCSI_REG_OFFSET_INTR_MASK      = 0x2010,
	PVSCSI_REG_OFFSET_KICK_NON_RW_IO = 0x3014,
	PVSCSI_REG_OFFSET_DEBUG          = 0x3018,
	PVSCSI_REG_OFFSET_KICK_RW_IO     = 0x4018,
पूर्ण;

/*
 * Virtual h/w commands.
 */

क्रमागत PVSCSICommands अणु
	PVSCSI_CMD_FIRST             = 0, /* has to be first */

	PVSCSI_CMD_ADAPTER_RESET     = 1,
	PVSCSI_CMD_ISSUE_SCSI        = 2,
	PVSCSI_CMD_SETUP_RINGS       = 3,
	PVSCSI_CMD_RESET_BUS         = 4,
	PVSCSI_CMD_RESET_DEVICE      = 5,
	PVSCSI_CMD_ABORT_CMD         = 6,
	PVSCSI_CMD_CONFIG            = 7,
	PVSCSI_CMD_SETUP_MSG_RING    = 8,
	PVSCSI_CMD_DEVICE_UNPLUG     = 9,
	PVSCSI_CMD_SETUP_REQCALLTHRESHOLD     = 10,

	PVSCSI_CMD_LAST              = 11  /* has to be last */
पूर्ण;

/*
 * Command descriptor क्रम PVSCSI_CMD_RESET_DEVICE --
 */

काष्ठा PVSCSICmdDescResetDevice अणु
	u32	target;
	u8	lun[8];
पूर्ण __packed;

/*
 * Command descriptor क्रम PVSCSI_CMD_CONFIG --
 */

काष्ठा PVSCSICmdDescConfigCmd अणु
	u64 cmpAddr;
	u64 configPageAddress;
	u32 configPageNum;
	u32 _pad;
पूर्ण __packed;

/*
 * Command descriptor क्रम PVSCSI_CMD_SETUP_REQCALLTHRESHOLD --
 */

काष्ठा PVSCSICmdDescSetupReqCall अणु
	u32 enable;
पूर्ण __packed;

क्रमागत PVSCSIConfigPageType अणु
	PVSCSI_CONFIG_PAGE_CONTROLLER = 0x1958,
	PVSCSI_CONFIG_PAGE_PHY        = 0x1959,
	PVSCSI_CONFIG_PAGE_DEVICE     = 0x195a,
पूर्ण;

क्रमागत PVSCSIConfigPageAddressType अणु
	PVSCSI_CONFIG_CONTROLLER_ADDRESS = 0x2120,
	PVSCSI_CONFIG_BUSTARGET_ADDRESS  = 0x2121,
	PVSCSI_CONFIG_PHY_ADDRESS        = 0x2122,
पूर्ण;

/*
 * Command descriptor क्रम PVSCSI_CMD_ABORT_CMD --
 *
 * - currently करोes not support specअगरying the LUN.
 * - _pad should be 0.
 */

काष्ठा PVSCSICmdDescAbortCmd अणु
	u64	context;
	u32	target;
	u32	_pad;
पूर्ण __packed;

/*
 * Command descriptor क्रम PVSCSI_CMD_SETUP_RINGS --
 *
 * Notes:
 * - reqRingNumPages and cmpRingNumPages need to be घातer of two.
 * - reqRingNumPages and cmpRingNumPages need to be dअगरferent from 0,
 * - reqRingNumPages and cmpRingNumPages need to be inferior to
 *   PVSCSI_SETUP_RINGS_MAX_NUM_PAGES.
 */

#घोषणा PVSCSI_SETUP_RINGS_MAX_NUM_PAGES        32
काष्ठा PVSCSICmdDescSetupRings अणु
	u32	reqRingNumPages;
	u32	cmpRingNumPages;
	u64	ringsStatePPN;
	u64	reqRingPPNs[PVSCSI_SETUP_RINGS_MAX_NUM_PAGES];
	u64	cmpRingPPNs[PVSCSI_SETUP_RINGS_MAX_NUM_PAGES];
पूर्ण __packed;

/*
 * Command descriptor क्रम PVSCSI_CMD_SETUP_MSG_RING --
 *
 * Notes:
 * - this command was not supported in the initial revision of the h/w
 *   पूर्णांकerface. Beक्रमe using it, you need to check that it is supported by
 *   writing PVSCSI_CMD_SETUP_MSG_RING to the 'command' रेजिस्टर, then
 *   immediately after पढ़ो the 'command status' रेजिस्टर:
 *       * a value of -1 means that the cmd is NOT supported,
 *       * a value != -1 means that the cmd IS supported.
 *   If it's supported the 'command status' रेजिस्टर should वापस:
 *      माप(PVSCSICmdDescSetupMsgRing) / माप(u32).
 * - this command should be issued _after_ the usual SETUP_RINGS so that the
 *   RingsState page is alपढ़ोy setup. If not, the command is a nop.
 * - numPages needs to be a घातer of two,
 * - numPages needs to be dअगरferent from 0,
 * - _pad should be zero.
 */

#घोषणा PVSCSI_SETUP_MSG_RING_MAX_NUM_PAGES  16

काष्ठा PVSCSICmdDescSetupMsgRing अणु
	u32	numPages;
	u32	_pad;
	u64	ringPPNs[PVSCSI_SETUP_MSG_RING_MAX_NUM_PAGES];
पूर्ण __packed;

क्रमागत PVSCSIMsgType अणु
	PVSCSI_MSG_DEV_ADDED          = 0,
	PVSCSI_MSG_DEV_REMOVED        = 1,
	PVSCSI_MSG_LAST               = 2,
पूर्ण;

/*
 * Msg descriptor.
 *
 * माप(काष्ठा PVSCSIRingMsgDesc) == 128.
 *
 * - type is of type क्रमागत PVSCSIMsgType.
 * - the content of args depend on the type of event being delivered.
 */

काष्ठा PVSCSIRingMsgDesc अणु
	u32	type;
	u32	args[31];
पूर्ण __packed;

काष्ठा PVSCSIMsgDescDevStatusChanged अणु
	u32	type;  /* PVSCSI_MSG_DEV _ADDED / _REMOVED */
	u32	bus;
	u32	target;
	u8	lun[8];
	u32	pad[27];
पूर्ण __packed;

/*
 * Rings state.
 *
 * - the fields:
 *    . msgProdIdx,
 *    . msgConsIdx,
 *    . msgNumEntriesLog2,
 *   .. are only used once the SETUP_MSG_RING cmd has been issued.
 * - '_pad' helps to ensure that the msg related fields are on their own
 *   cache-line.
 */

काष्ठा PVSCSIRingsState अणु
	u32	reqProdIdx;
	u32	reqConsIdx;
	u32	reqNumEntriesLog2;

	u32	cmpProdIdx;
	u32	cmpConsIdx;
	u32	cmpNumEntriesLog2;

	u32	reqCallThreshold;

	u8	_pad[100];

	u32	msgProdIdx;
	u32	msgConsIdx;
	u32	msgNumEntriesLog2;
पूर्ण __packed;

/*
 * Request descriptor.
 *
 * माप(RingReqDesc) = 128
 *
 * - context: is a unique identअगरier of a command. It could normally be any
 *   64bit value, however we currently store it in the serialNumber variable
 *   of काष्ठा SCSI_Command, so we have the following restrictions due to the
 *   way this field is handled in the vmkernel storage stack:
 *    * this value can't be 0,
 *    * the upper 32bit need to be 0 since serialNumber is as a u32.
 *   Currently tracked as PR 292060.
 * - dataLen: contains the total number of bytes that need to be transferred.
 * - dataAddr:
 *   * अगर PVSCSI_FLAG_CMD_WITH_SG_LIST is set: dataAddr is the PA of the first
 *     s/g table segment, each s/g segment is entirely contained on a single
 *     page of physical memory,
 *   * अगर PVSCSI_FLAG_CMD_WITH_SG_LIST is NOT set, then dataAddr is the PA of
 *     the buffer used क्रम the DMA transfer,
 * - flags:
 *   * PVSCSI_FLAG_CMD_WITH_SG_LIST: see dataAddr above,
 *   * PVSCSI_FLAG_CMD_सूची_NONE: no DMA involved,
 *   * PVSCSI_FLAG_CMD_सूची_TOHOST: transfer from device to मुख्य memory,
 *   * PVSCSI_FLAG_CMD_सूची_TODEVICE: transfer from मुख्य memory to device,
 *   * PVSCSI_FLAG_CMD_OUT_OF_BAND_CDB: reserved to handle CDBs larger than
 *     16bytes. To be specअगरied.
 * - vcpuHपूर्णांक: vcpuId of the processor that will be most likely रुकोing क्रम the
 *   completion of the i/o. For guest OSes that use lowest priority message
 *   delivery mode (such as winकरोws), we use this "hint" to deliver the
 *   completion action to the proper vcpu. For now, we can use the vcpuId of
 *   the processor that initiated the i/o as a likely candidate क्रम the vcpu
 *   that will be रुकोing क्रम the completion..
 * - bus should be 0: we currently only support bus 0 क्रम now.
 * - unused should be zero'd.
 */

#घोषणा PVSCSI_FLAG_CMD_WITH_SG_LIST        (1 << 0)
#घोषणा PVSCSI_FLAG_CMD_OUT_OF_BAND_CDB     (1 << 1)
#घोषणा PVSCSI_FLAG_CMD_सूची_NONE            (1 << 2)
#घोषणा PVSCSI_FLAG_CMD_सूची_TOHOST          (1 << 3)
#घोषणा PVSCSI_FLAG_CMD_सूची_TODEVICE        (1 << 4)

काष्ठा PVSCSIRingReqDesc अणु
	u64	context;
	u64	dataAddr;
	u64	dataLen;
	u64	senseAddr;
	u32	senseLen;
	u32	flags;
	u8	cdb[16];
	u8	cdbLen;
	u8	lun[8];
	u8	tag;
	u8	bus;
	u8	target;
	u8	vcpuHपूर्णांक;
	u8	unused[59];
पूर्ण __packed;

/*
 * Scatter-gather list management.
 *
 * As described above, when PVSCSI_FLAG_CMD_WITH_SG_LIST is set in the
 * RingReqDesc.flags, then RingReqDesc.dataAddr is the PA of the first s/g
 * table segment.
 *
 * - each segment of the s/g table contain a succession of काष्ठा
 *   PVSCSISGElement.
 * - each segment is entirely contained on a single physical page of memory.
 * - a "chain" s/g element has the flag PVSCSI_SGE_FLAG_CHAIN_ELEMENT set in
 *   PVSCSISGElement.flags and in this हाल:
 *     * addr is the PA of the next s/g segment,
 *     * length is undefined, assumed to be 0.
 */

काष्ठा PVSCSISGElement अणु
	u64	addr;
	u32	length;
	u32	flags;
पूर्ण __packed;

/*
 * Completion descriptor.
 *
 * माप(RingCmpDesc) = 32
 *
 * - context: identअगरier of the command. The same thing that was specअगरied
 *   under "context" as part of काष्ठा RingReqDesc at initiation समय,
 * - dataLen: number of bytes transferred क्रम the actual i/o operation,
 * - senseLen: number of bytes written पूर्णांकo the sense buffer,
 * - hostStatus: adapter status,
 * - scsiStatus: device status,
 * - _pad should be zero.
 */

काष्ठा PVSCSIRingCmpDesc अणु
	u64	context;
	u64	dataLen;
	u32	senseLen;
	u16	hostStatus;
	u16	scsiStatus;
	u32	_pad[2];
पूर्ण __packed;

काष्ठा PVSCSIConfigPageHeader अणु
	u32 pageNum;
	u16 numDwords;
	u16 hostStatus;
	u16 scsiStatus;
	u16 reserved[3];
पूर्ण __packed;

काष्ठा PVSCSIConfigPageController अणु
	काष्ठा PVSCSIConfigPageHeader header;
	u64 nodeWWN; /* Device name as defined in the SAS spec. */
	u16 manufacturer[64];
	u16 serialNumber[64];
	u16 opromVersion[32];
	u16 hwVersion[32];
	u16 firmwareVersion[32];
	u32 numPhys;
	u8  useConsecutivePhyWWNs;
	u8  reserved[3];
पूर्ण __packed;

/*
 * Interrupt status / IRQ bits.
 */

#घोषणा PVSCSI_INTR_CMPL_0                 (1 << 0)
#घोषणा PVSCSI_INTR_CMPL_1                 (1 << 1)
#घोषणा PVSCSI_INTR_CMPL_MASK              MASK(2)

#घोषणा PVSCSI_INTR_MSG_0                  (1 << 2)
#घोषणा PVSCSI_INTR_MSG_1                  (1 << 3)
#घोषणा PVSCSI_INTR_MSG_MASK               (MASK(2) << 2)

#घोषणा PVSCSI_INTR_ALL_SUPPORTED          MASK(4)

/*
 * Number of MSI-X vectors supported.
 */
#घोषणा PVSCSI_MAX_INTRS        24

/*
 * Misc स्थिरants क्रम the rings.
 */

#घोषणा PVSCSI_MAX_NUM_PAGES_REQ_RING   PVSCSI_SETUP_RINGS_MAX_NUM_PAGES
#घोषणा PVSCSI_MAX_NUM_PAGES_CMP_RING   PVSCSI_SETUP_RINGS_MAX_NUM_PAGES
#घोषणा PVSCSI_MAX_NUM_PAGES_MSG_RING   PVSCSI_SETUP_MSG_RING_MAX_NUM_PAGES

#घोषणा PVSCSI_MAX_NUM_REQ_ENTRIES_PER_PAGE \
				(PAGE_SIZE / माप(काष्ठा PVSCSIRingReqDesc))

#घोषणा PVSCSI_MAX_REQ_QUEUE_DEPTH \
	(PVSCSI_MAX_NUM_PAGES_REQ_RING * PVSCSI_MAX_NUM_REQ_ENTRIES_PER_PAGE)

#घोषणा PVSCSI_MEM_SPACE_COMMAND_NUM_PAGES     1
#घोषणा PVSCSI_MEM_SPACE_INTR_STATUS_NUM_PAGES 1
#घोषणा PVSCSI_MEM_SPACE_MISC_NUM_PAGES        2
#घोषणा PVSCSI_MEM_SPACE_KICK_IO_NUM_PAGES     2
#घोषणा PVSCSI_MEM_SPACE_MSIX_NUM_PAGES        2

क्रमागत PVSCSIMemSpace अणु
	PVSCSI_MEM_SPACE_COMMAND_PAGE		= 0,
	PVSCSI_MEM_SPACE_INTR_STATUS_PAGE	= 1,
	PVSCSI_MEM_SPACE_MISC_PAGE		= 2,
	PVSCSI_MEM_SPACE_KICK_IO_PAGE		= 4,
	PVSCSI_MEM_SPACE_MSIX_TABLE_PAGE	= 6,
	PVSCSI_MEM_SPACE_MSIX_PBA_PAGE		= 7,
पूर्ण;

#घोषणा PVSCSI_MEM_SPACE_NUM_PAGES \
	(PVSCSI_MEM_SPACE_COMMAND_NUM_PAGES +       \
	 PVSCSI_MEM_SPACE_INTR_STATUS_NUM_PAGES +   \
	 PVSCSI_MEM_SPACE_MISC_NUM_PAGES +          \
	 PVSCSI_MEM_SPACE_KICK_IO_NUM_PAGES +       \
	 PVSCSI_MEM_SPACE_MSIX_NUM_PAGES)

#घोषणा PVSCSI_MEM_SPACE_SIZE        (PVSCSI_MEM_SPACE_NUM_PAGES * PAGE_SIZE)

#पूर्ण_अगर /* _VMW_PVSCSI_H_ */
