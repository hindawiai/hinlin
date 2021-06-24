<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2010 - 2016 UNISYS CORPORATION
 * All rights reserved.
 */

#अगर_अघोषित __IOCHANNEL_H__
#घोषणा __IOCHANNEL_H__

/*
 * Everything needed क्रम IOPart-GuestPart communication is define in
 * this file. Note: Everything is OS-independent because this file is
 * used by Winकरोws, Linux and possible EFI drivers.
 *
 * Communication flow between the IOPart and GuestPart uses the channel headers
 * channel state. The following states are currently being used:
 *       UNINIT(All Zeroes), CHANNEL_ATTACHING, CHANNEL_ATTACHED, CHANNEL_OPENED
 *
 * Additional states will be used later. No locking is needed to चयन between
 * states due to the following rules:
 *
 *      1.  IOPart is only the only partition allowed to change from UNIT
 *      2.  IOPart is only the only partition allowed to change from
 *		CHANNEL_ATTACHING
 *      3.  GuestPart is only the only partition allowed to change from
 *		CHANNEL_ATTACHED
 *
 * The state changes are the following: IOPart sees the channel is in UNINIT,
 *        UNINIT -> CHANNEL_ATTACHING (perक्रमmed only by IOPart)
 *        CHANNEL_ATTACHING -> CHANNEL_ATTACHED (perक्रमmed only by IOPart)
 *        CHANNEL_ATTACHED -> CHANNEL_OPENED (perक्रमmed only by GuestPart)
 */

#समावेश <linux/uuid.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/visorbus.h>

/*
 * Must increment these whenever you insert or delete fields within this channel
 * काष्ठा. Also increment whenever you change the meaning of fields within this
 * channel काष्ठा so as to अवरोध pre-existing software. Note that you can
 * usually add fields to the END of the channel काष्ठा without needing to
 * increment this.
 */
#घोषणा VISOR_VHBA_CHANNEL_VERSIONID 2
#घोषणा VISOR_VNIC_CHANNEL_VERSIONID 2

/*
 * Everything necessary to handle SCSI & NIC traffic between Guest Partition and
 * IO Partition is defined below.
 */

/*
 * Define the two queues per data channel between iopart and ioguestparts.
 *	IOCHAN_TO_IOPART -- used by guest to 'insert' संकेतs to iopart.
 *	IOCHAN_FROM_IOPART -- used by guest to 'remove' संकेतs from IO part.
 */
#घोषणा IOCHAN_TO_IOPART 0
#घोषणा IOCHAN_FROM_IOPART 1

/* Size of cdb - i.e., SCSI cmnd */
#घोषणा MAX_CMND_SIZE 16

/* Unisys-specअगरic DMA direction values */
क्रमागत uis_dma_data_direction अणु
	UIS_DMA_BIसूचीECTIONAL = 0,
	UIS_DMA_TO_DEVICE = 1,
	UIS_DMA_FROM_DEVICE = 2,
	UIS_DMA_NONE = 3
पूर्ण;

#घोषणा MAX_SENSE_SIZE 64
#घोषणा MAX_PHYS_INFO 64

/*
 * क्रमागत net_types - Various types of network packets that can be sent in cmdrsp.
 * @NET_RCV_POST:	Submit buffer to hold receiving incoming packet.
 * @NET_RCV:		visornic -> uisnic. Incoming packet received.
 * @NET_XMIT:		uisnic -> visornic. For outgoing packet.
 * @NET_XMIT_DONE:	visornic -> uisnic. Outgoing packet xmitted.
 * @NET_RCV_ENBDIS:	uisnic -> visornic. Enable/Disable packet reception.
 * @NET_RCV_ENBDIS_ACK:	visornic -> uisnic. Acknowledge enable/disable packet.
 * @NET_RCV_PROMISC:	uisnic -> visornic. Enable/Disable promiscuous mode.
 * @NET_CONNECT_STATUS:	visornic -> uisnic. Indicate the loss or restoration of
 *			a network connection.
 * @NET_MACADDR:	uisnic -> visornic. Indicates the client has requested
 *			to update it's MAC address.
 * @NET_MACADDR_ACK:	MAC address acknowledge.
 */
क्रमागत net_types अणु
	NET_RCV_POST = 0,
	NET_RCV,
	NET_XMIT,
	NET_XMIT_DONE,
	NET_RCV_ENBDIS,
	NET_RCV_ENBDIS_ACK,
	/* Reception */
	NET_RCV_PROMISC,
	NET_CONNECT_STATUS,
	NET_MACADDR,
	NET_MACADDR_ACK,
पूर्ण;

/* Minimum eth data size */
#घोषणा ETH_MIN_DATA_SIZE 46
#घोषणा ETH_MIN_PACKET_SIZE (ETH_HLEN + ETH_MIN_DATA_SIZE)

/* Maximum data size */
#घोषणा VISOR_ETH_MAX_MTU 16384

#अगर_अघोषित MAX_MACADDR_LEN
/* Number of bytes in MAC address */
#घोषणा MAX_MACADDR_LEN 6
#पूर्ण_अगर

/* Various types of scsi task mgmt commands. */
क्रमागत task_mgmt_types अणु
	TASK_MGMT_ABORT_TASK = 1,
	TASK_MGMT_BUS_RESET,
	TASK_MGMT_LUN_RESET,
	TASK_MGMT_TARGET_RESET,
पूर्ण;

/* Various types of vdisk mgmt commands. */
क्रमागत vdisk_mgmt_types अणु
	VDISK_MGMT_ACQUIRE = 1,
	VDISK_MGMT_RELEASE,
पूर्ण;

काष्ठा phys_info अणु
	u64 pi_pfn;
	u16 pi_off;
	u16 pi_len;
पूर्ण __packed;

#घोषणा MIN_NUMSIGNALS 64

/* Structs with pragma pack. */

काष्ठा guest_phys_info अणु
	u64 address;
	u64 length;
पूर्ण __packed;

/*
 * काष्ठा uisscsi_dest
 * @channel: Bus number.
 * @id:      Target number.
 * @lun:     Logical unit number.
 */
काष्ठा uisscsi_dest अणु
	u32 channel;
	u32 id;
	u32 lun;
पूर्ण __packed;

काष्ठा vhba_wwnn अणु
	u32 wwnn1;
	u32 wwnn2;
पूर्ण __packed;

/*
 * काष्ठा vhba_config_max
 * @max_channel: Maximum channel क्रम devices attached to this bus.
 * @max_id:	 Maximum SCSI ID क्रम devices attached to bus.
 * @max_lun:	 Maximum SCSI LUN क्रम devices attached to bus.
 * @cmd_per_lun: Maximum number of outstanding commands per LUN.
 * @max_io_size: Maximum io size क्रम devices attached to this bus. Max io size
 *		 is often determined by the resource of the hba.
 *		 e.g Max scatter gather list length * page size / sector size.
 *
 * WARNING: Values stored in this काष्ठाure must contain maximum counts (not
 * maximum values).
 *
 * 20 bytes
 */
काष्ठा vhba_config_max अणु
	u32 max_channel;
	u32 max_id;
	u32 max_lun;
	u32 cmd_per_lun;
	u32 max_io_size;
पूर्ण __packed;

/*
 * काष्ठा uiscmdrsp_scsi
 *
 * @handle:		The handle to the cmd that was received. Send it back as
 *			is in the rsp packet.
 * @cmnd:		The cdb क्रम the command.
 * @bufflen:		Length of data to be transferred out or in.
 * @guest_phys_entries:	Number of entries in scatter-gather list.
 * @काष्ठा gpi_list:	Physical address inक्रमmation क्रम each fragment.
 * @data_dir:		Direction of the data, अगर any.
 * @काष्ठा vdest:	Identअगरies the भव hba, id, channel, lun to which
 *			cmd was sent.
 * @linuxstat:		Original Linux status used by Linux vdisk.
 * @scsistat:		The scsi status.
 * @addlstat:		Non-scsi status.
 * @sensebuf:		Sense info in हाल cmd failed. sensebuf holds the
 *			sense_data काष्ठा. See sense_data काष्ठा क्रम more
 *			details.
 * @*vdisk:		Poपूर्णांकer to the vdisk to clean up when IO completes.
 * @no_disk_result:	Used to वापस no disk inquiry result when
 *			no_disk_result is set to 1
 *			scsi.scsistat is SAM_STAT_GOOD
 *			scsi.addlstat is 0
 *			scsi.linuxstat is SAM_STAT_GOOD
 *			That is, there is NO error.
 */
काष्ठा uiscmdrsp_scsi अणु
	u64 handle;
	u8 cmnd[MAX_CMND_SIZE];
	u32 bufflen;
	u16 guest_phys_entries;
	काष्ठा guest_phys_info gpi_list[MAX_PHYS_INFO];
	u32 data_dir;
	काष्ठा uisscsi_dest vdest;
	/* Needed to queue the rsp back to cmd originator. */
	पूर्णांक linuxstat;
	u8 scsistat;
	u8 addlstat;
#घोषणा ADDL_SEL_TIMEOUT 4
	/* The following fields are need to determine the result of command. */
	u8 sensebuf[MAX_SENSE_SIZE];
	व्योम *vdisk;
	पूर्णांक no_disk_result;
पूर्ण __packed;

/*
 * Defines to support sending correct inquiry result when no disk is
 * configured.
 *
 * From SCSI SPC2 -
 *
 * If the target is not capable of supporting a device on this logical unit, the
 * device server shall set this field to 7Fh (PERIPHERAL QUALIFIER set to 011b
 * and PERIPHERAL DEVICE TYPE set to 1Fh).
 *
 * The device server is capable of supporting the specअगरied peripheral device
 * type on this logical unit. However, the physical device is not currently
 * connected to this logical unit.
 */

/*
 * Peripheral qualअगरier of 0x3
 * Peripheral type of 0x1f
 * Specअगरies no device but target present
 */
#घोषणा DEV_NOT_CAPABLE 0x7f
/*
 * Peripheral qualअगरier of 0x1
 * Peripheral type of 0 - disk
 * Specअगरies device capable, but not present
 */
#घोषणा DEV_DISK_CAPABLE_NOT_PRESENT 0x20
/* HiSup = 1; shows support क्रम report luns must be वापसed क्रम lun 0. */
#घोषणा DEV_HISUPPORT 0x10

/*
 * Peripheral qualअगरier of 0x3
 * Peripheral type of 0x1f
 * Specअगरies no device but target present
 */
#घोषणा DEV_NOT_CAPABLE 0x7f
/*
 * Peripheral qualअगरier of 0x1
 * Peripheral type of 0 - disk
 * Specअगरies device capable, but not present
 */
#घोषणा DEV_DISK_CAPABLE_NOT_PRESENT 0x20
/* HiSup = 1; shows support क्रम report luns must be वापसed क्रम lun 0. */
#घोषणा DEV_HISUPPORT 0x10

/*
 * NOTE: Linux code assumes inquiry contains 36 bytes. Without checking length
 * in buf[4] some Linux code accesses bytes beyond 5 to retrieve venकरोr, product
 * and revision. Yikes! So let us always send back 36 bytes, the minimum क्रम
 * inquiry result.
 */
#घोषणा NO_DISK_INQUIRY_RESULT_LEN 36
/* 5 bytes minimum क्रम inquiry result */
#घोषणा MIN_INQUIRY_RESULT_LEN 5

/* SCSI device version क्रम no disk inquiry result */
/* indicates SCSI SPC2 (SPC3 is 5) */
#घोषणा SCSI_SPC2_VER 4

/* Struct and Defines to support sense inक्रमmation. */

/*
 * The following काष्ठा is वापसed in sensebuf field in uiscmdrsp_scsi. It is
 * initialized in exactly the manner that is recommended in Winकरोws (hence the
 * odd values).
 * When set, these fields will have the following values:
 * ErrorCode = 0x70		indicates current error
 * Valid = 1			indicates sense info is valid
 * SenseKey			contains sense key as defined by SCSI specs.
 * AdditionalSenseCode		contains sense key as defined by SCSI specs.
 * AdditionalSenseCodeQualअगरier	contains qualअगरier to sense code as defined by
 *				scsi करोcs.
 * AdditionalSenseLength	contains will be माप(sense_data)-8=10.
 */
काष्ठा sense_data अणु
	u8 errorcode:7;
	u8 valid:1;
	u8 segment_number;
	u8 sense_key:4;
	u8 reserved:1;
	u8 incorrect_length:1;
	u8 end_of_media:1;
	u8 file_mark:1;
	u8 inक्रमmation[4];
	u8 additional_sense_length;
	u8 command_specअगरic_inक्रमmation[4];
	u8 additional_sense_code;
	u8 additional_sense_code_qualअगरier;
	u8 fru_code;
	u8 sense_key_specअगरic[3];
पूर्ण __packed;

/*
 * काष्ठा net_pkt_xmt
 * @len:		    Full length of data in the packet.
 * @num_frags:		    Number of fragments in frags containing data.
 * @काष्ठा phys_info frags: Physical page inक्रमmation.
 * @ethhdr:		    The ethernet header.
 * @काष्ठा lincsum:	    These are needed क्रम csum at uisnic end.
 *      @valid:	    1 = काष्ठा is valid - अन्यथा ignore.
 *      @hrawoffv:  1 = hwrafoff is valid.
 *      @nhrawoffv: 1 = nhwrafoff is valid.
 *      @protocol:  Specअगरies packet protocol.
 *      @csum:	    Value used to set skb->csum at IOPart.
 *      @hrawoff:   Value used to set skb->h.raw at IOPart. hrawoff poपूर्णांकs to
 *		    the start of the TRANSPORT LAYER HEADER.
 *      @nhrawoff:  Value used to set skb->nh.raw at IOPart. nhrawoff poपूर्णांकs to
 *		    the start of the NETWORK LAYER HEADER.
 *
 * NOTE:
 * The full packet is described in frags but the ethernet header is separately
 * kept in ethhdr so that uisnic करोesn't have "MAP" the guest memory to get to
 * the header. uisnic needs ethhdr to determine how to route the packet.
 */
काष्ठा net_pkt_xmt अणु
	पूर्णांक len;
	पूर्णांक num_frags;
	काष्ठा phys_info frags[MAX_PHYS_INFO];
	अक्षर ethhdr[ETH_HLEN];
	काष्ठा अणु
		u8 valid;
		u8 hrawoffv;
		u8 nhrawoffv;
		__be16 protocol;
		__wsum csum;
		u32 hrawoff;
		u32 nhrawoff;
	पूर्ण lincsum;
पूर्ण __packed;

काष्ठा net_pkt_xmtकरोne अणु
	/* Result of NET_XMIT */
	u32 xmt_करोne_result;
पूर्ण __packed;

/*
 * RCVPOST_BUF_SIZE must be at most page_size(4096) - cache_line_size (64) The
 * reason is because dev_skb_alloc which is used to generate RCV_POST skbs in
 * visornic requires that there is "overhead" in the buffer, and pads 16 bytes.
 * Use 1 full cache line size क्रम "overhead" so that transfers are optimized.
 * IOVM requires that a buffer be represented by 1 phys_info काष्ठाure
 * which can only cover page_size.
 */
#घोषणा RCVPOST_BUF_SIZE 4032
#घोषणा MAX_NET_RCV_CHAIN \
	((VISOR_ETH_MAX_MTU + ETH_HLEN + RCVPOST_BUF_SIZE - 1) \
	 / RCVPOST_BUF_SIZE)

/* rcv buf size must be large enough to include ethernet data len + ethernet
 * header len - we are choosing 2K because it is guaranteed to be describable.
 */
काष्ठा net_pkt_rcvpost अणु
	/* Physical page inक्रमmation क्रम the single fragment 2K rcv buf */
	काष्ठा phys_info frag;
	/*
	 * Ensures that receive posts are वापसed to the adapter which we sent
	 * them from originally.
	 */
	u64 unique_num;

पूर्ण __packed;

/*
 * काष्ठा net_pkt_rcv
 * @rcv_करोne_len:	Length of the received data.
 * @numrcvbufs:		Contains the incoming data. Guest side MUST chain these
 *			together.
 * @*rcvbuf:		List of chained rcvbufa. Each entry is a receive buffer
 *			provided by NET_RCV_POST. NOTE: First rcvbuf in the
 *			chain will also be provided in net.buf.
 * @unique_num:
 * @rcvs_dropped_delta:
 *
 * The number of rcvbuf that can be chained is based on max mtu and size of each
 * rcvbuf.
 */
काष्ठा net_pkt_rcv अणु
	u32 rcv_करोne_len;
	u8 numrcvbufs;
	व्योम *rcvbuf[MAX_NET_RCV_CHAIN];
	u64 unique_num;
	u32 rcvs_dropped_delta;
पूर्ण __packed;

काष्ठा net_pkt_enbdis अणु
	व्योम *context;
	/* 1 = enable, 0 = disable */
	u16 enable;
पूर्ण __packed;

काष्ठा net_pkt_macaddr अणु
	व्योम *context;
	/* 6 bytes */
	u8 macaddr[MAX_MACADDR_LEN];
पूर्ण __packed;

/*
 * काष्ठा uiscmdrsp_net - cmd rsp packet used क्रम VNIC network traffic.
 * @क्रमागत type:
 * @*buf:
 * @जोड़:
 *	@काष्ठा xmt:	 Used क्रम NET_XMIT.
 *	@काष्ठा xmtकरोne: Used क्रम NET_XMIT_DONE.
 *	@काष्ठा rcvpost: Used क्रम NET_RCV_POST.
 *	@काष्ठा rcv:	 Used क्रम NET_RCV.
 *	@काष्ठा enbdis:	 Used क्रम NET_RCV_ENBDIS, NET_RCV_ENBDIS_ACK,
 *			 NET_RCV_PROMSIC, and NET_CONNECT_STATUS.
 *	@काष्ठा macaddr:
 */
काष्ठा uiscmdrsp_net अणु
	क्रमागत net_types type;
	व्योम *buf;
	जोड़ अणु
		काष्ठा net_pkt_xmt xmt;
		काष्ठा net_pkt_xmtकरोne xmtकरोne;
		काष्ठा net_pkt_rcvpost rcvpost;
		काष्ठा net_pkt_rcv rcv;
		काष्ठा net_pkt_enbdis enbdis;
		काष्ठा net_pkt_macaddr macaddr;
	पूर्ण;
पूर्ण __packed;

/*
 * काष्ठा uiscmdrsp_scsitaskmgmt
 * @क्रमागत tasktype:	 The type of task.
 * @काष्ठा vdest:	 The vdisk क्रम which this task mgmt is generated.
 * @handle:		 This is a handle that the guest has saved off क्रम its
 *			 own use. The handle value is preserved by iopart and
 *			 वापसed as in task mgmt rsp.
 * @notअगरy_handle:	 For Linux guests, this is a poपूर्णांकer to रुको_queue_head
 *			 that a thपढ़ो is रुकोing on to see अगर the taskmgmt
 *			 command has completed. When the rsp is received by
 *			 guest, the thपढ़ो receiving the response uses this to
 *			 notअगरy the thपढ़ो रुकोing क्रम taskmgmt command
 *			 completion. It's value is preserved by iopart and
 *			 वापसed as in the task mgmt rsp.
 * @notअगरyresult_handle: This is a handle to the location in the guest where
 *			 the result of the taskmgmt command (result field) is
 *			 saved to when the response is handled. It's value is
 *			 preserved by iopart and वापसed as is in the task mgmt
 *			 rsp.
 * @result:		 Result of taskmgmt command - set by IOPart.
 */
काष्ठा uiscmdrsp_scsitaskmgmt अणु
	क्रमागत task_mgmt_types tasktype;
	काष्ठा uisscsi_dest vdest;
	u64 handle;
	u64 notअगरy_handle;
	u64 notअगरyresult_handle;
	अक्षर result;

#घोषणा TASK_MGMT_FAILED 0
पूर्ण __packed;

/*
 * काष्ठा uiscmdrsp_disknotअगरy - Used by uissd to send disk add/हटाओ
 *				 notअगरications to Guest.
 * @add:     0-हटाओ, 1-add.
 * @*v_hba:  Channel info to route msg.
 * @channel: SCSI Path of Disk to added or हटाओd.
 * @id:	     SCSI Path of Disk to added or हटाओd.
 * @lun:     SCSI Path of Disk to added or हटाओd.
 *
 * Note that the vHba poपूर्णांकer is not used by the Client/Guest side.
 */
काष्ठा uiscmdrsp_disknotअगरy अणु
	u8 add;
	व्योम *v_hba;
	u32 channel, id, lun;
पूर्ण __packed;

/* Keeping cmd and rsp info in one काष्ठाure क्रम now cmd rsp packet क्रम SCSI */
काष्ठा uiscmdrsp अणु
	अक्षर cmdtype;
	/* Describes what type of inक्रमmation is in the काष्ठा */
#घोषणा CMD_SCSI_TYPE	      1
#घोषणा CMD_NET_TYPE	      2
#घोषणा CMD_SCSITASKMGMT_TYPE 3
#घोषणा CMD_NOTIFYGUEST_TYPE  4
	जोड़ अणु
		काष्ठा uiscmdrsp_scsi scsi;
		काष्ठा uiscmdrsp_net net;
		काष्ठा uiscmdrsp_scsitaskmgmt scsitaskmgmt;
		काष्ठा uiscmdrsp_disknotअगरy disknotअगरy;
	पूर्ण;
	/* Send the response when the cmd is करोne (scsi and scsittaskmgmt). */
	व्योम *निजी_data;
	/* General Purpose Queue Link */
	काष्ठा uiscmdrsp *next;
	/* Poपूर्णांकer to the nextactive commands */
	काष्ठा uiscmdrsp *activeQ_next;
	/* Poपूर्णांकer to the prevactive commands */
	काष्ठा uiscmdrsp *activeQ_prev;
पूर्ण __packed;

/* total = 28 bytes */
काष्ठा iochannel_vhba अणु
	/* 8 bytes */
	काष्ठा vhba_wwnn wwnn;
	/* 20 bytes */
	काष्ठा vhba_config_max max;
पूर्ण __packed;

काष्ठा iochannel_vnic अणु
	/* 6 bytes */
	u8 macaddr[6];
	/* 4 bytes */
	u32 num_rcv_bufs;
	/* 4 bytes */
	u32 mtu;
	/* 16 bytes */
	guid_t zone_guid;
पूर्ण __packed;

/*
 * This is just the header of the IO channel. It is assumed that directly after
 * this header there is a large region of memory which contains the command and
 * response queues as specअगरied in cmd_q and rsp_q SIGNAL_QUEUE_HEADERS.
 */
काष्ठा visor_io_channel अणु
	काष्ठा channel_header channel_header;
	काष्ठा संकेत_queue_header cmd_q;
	काष्ठा संकेत_queue_header rsp_q;
	जोड़ अणु
		काष्ठा iochannel_vhba vhba;
		काष्ठा iochannel_vnic vnic;
	पूर्ण __packed;

#घोषणा MAX_CLIENTSTRING_LEN 1024
	/* client_string is शून्य termimated so holds max-1 bytes */
	 u8 client_string[MAX_CLIENTSTRING_LEN];
पूर्ण __packed;

/* INLINE functions क्रम initializing and accessing I/O data channels. */
#घोषणा SIZखातापूर्ण_CMDRSP (64 * DIV_ROUND_UP(माप(काष्ठा uiscmdrsp), 64))

/* Use 4K page sizes when passing page info between Guest and IOPartition. */
#घोषणा PI_PAGE_SIZE 0x1000
#घोषणा PI_PAGE_MASK 0x0FFF

/* __IOCHANNEL_H__ */
#पूर्ण_अगर
