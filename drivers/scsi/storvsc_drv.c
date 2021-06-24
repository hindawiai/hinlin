<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *   K. Y. Srinivasan <kys@microsoft.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_devinfo.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_transport_fc.h>
#समावेश <scsi/scsi_transport.h>

/*
 * All wire protocol details (storage protocol between the guest and the host)
 * are consolidated here.
 *
 * Begin protocol definitions.
 */

/*
 * Version history:
 * V1 Beta: 0.1
 * V1 RC < 2008/1/31: 1.0
 * V1 RC > 2008/1/31:  2.0
 * Win7: 4.2
 * Win8: 5.1
 * Win8.1: 6.0
 * Win10: 6.2
 */

#घोषणा VMSTOR_PROTO_VERSION(MAJOR_, MINOR_)	((((MAJOR_) & 0xff) << 8) | \
						(((MINOR_) & 0xff)))

#घोषणा VMSTOR_PROTO_VERSION_WIN6	VMSTOR_PROTO_VERSION(2, 0)
#घोषणा VMSTOR_PROTO_VERSION_WIN7	VMSTOR_PROTO_VERSION(4, 2)
#घोषणा VMSTOR_PROTO_VERSION_WIN8	VMSTOR_PROTO_VERSION(5, 1)
#घोषणा VMSTOR_PROTO_VERSION_WIN8_1	VMSTOR_PROTO_VERSION(6, 0)
#घोषणा VMSTOR_PROTO_VERSION_WIN10	VMSTOR_PROTO_VERSION(6, 2)

/*  Packet काष्ठाure describing भव storage requests. */
क्रमागत vstor_packet_operation अणु
	VSTOR_OPERATION_COMPLETE_IO		= 1,
	VSTOR_OPERATION_REMOVE_DEVICE		= 2,
	VSTOR_OPERATION_EXECUTE_SRB		= 3,
	VSTOR_OPERATION_RESET_LUN		= 4,
	VSTOR_OPERATION_RESET_ADAPTER		= 5,
	VSTOR_OPERATION_RESET_BUS		= 6,
	VSTOR_OPERATION_BEGIN_INITIALIZATION	= 7,
	VSTOR_OPERATION_END_INITIALIZATION	= 8,
	VSTOR_OPERATION_QUERY_PROTOCOL_VERSION	= 9,
	VSTOR_OPERATION_QUERY_PROPERTIES	= 10,
	VSTOR_OPERATION_ENUMERATE_BUS		= 11,
	VSTOR_OPERATION_FCHBA_DATA              = 12,
	VSTOR_OPERATION_CREATE_SUB_CHANNELS     = 13,
	VSTOR_OPERATION_MAXIMUM                 = 13
पूर्ण;

/*
 * WWN packet क्रम Fibre Channel HBA
 */

काष्ठा hv_fc_wwn_packet अणु
	u8	primary_active;
	u8	reserved1[3];
	u8	primary_port_wwn[8];
	u8	primary_node_wwn[8];
	u8	secondary_port_wwn[8];
	u8	secondary_node_wwn[8];
पूर्ण;



/*
 * SRB Flag Bits
 */

#घोषणा SRB_FLAGS_QUEUE_ACTION_ENABLE		0x00000002
#घोषणा SRB_FLAGS_DISABLE_DISCONNECT		0x00000004
#घोषणा SRB_FLAGS_DISABLE_SYNCH_TRANSFER	0x00000008
#घोषणा SRB_FLAGS_BYPASS_FROZEN_QUEUE		0x00000010
#घोषणा SRB_FLAGS_DISABLE_AUTOSENSE		0x00000020
#घोषणा SRB_FLAGS_DATA_IN			0x00000040
#घोषणा SRB_FLAGS_DATA_OUT			0x00000080
#घोषणा SRB_FLAGS_NO_DATA_TRANSFER		0x00000000
#घोषणा SRB_FLAGS_UNSPECIFIED_सूचीECTION	(SRB_FLAGS_DATA_IN | SRB_FLAGS_DATA_OUT)
#घोषणा SRB_FLAGS_NO_QUEUE_FREEZE		0x00000100
#घोषणा SRB_FLAGS_ADAPTER_CACHE_ENABLE		0x00000200
#घोषणा SRB_FLAGS_FREE_SENSE_BUFFER		0x00000400

/*
 * This flag indicates the request is part of the workflow क्रम processing a D3.
 */
#घोषणा SRB_FLAGS_D3_PROCESSING			0x00000800
#घोषणा SRB_FLAGS_IS_ACTIVE			0x00010000
#घोषणा SRB_FLAGS_ALLOCATED_FROM_ZONE		0x00020000
#घोषणा SRB_FLAGS_SGLIST_FROM_POOL		0x00040000
#घोषणा SRB_FLAGS_BYPASS_LOCKED_QUEUE		0x00080000
#घोषणा SRB_FLAGS_NO_KEEP_AWAKE			0x00100000
#घोषणा SRB_FLAGS_PORT_DRIVER_ALLOCSENSE	0x00200000
#घोषणा SRB_FLAGS_PORT_DRIVER_SENSEHASPORT	0x00400000
#घोषणा SRB_FLAGS_DONT_START_NEXT_PACKET	0x00800000
#घोषणा SRB_FLAGS_PORT_DRIVER_RESERVED		0x0F000000
#घोषणा SRB_FLAGS_CLASS_DRIVER_RESERVED		0xF0000000

#घोषणा SP_UNTAGGED			((अचिन्हित अक्षर) ~0)
#घोषणा SRB_SIMPLE_TAG_REQUEST		0x20

/*
 * Platक्रमm neutral description of a scsi request -
 * this reमुख्यs the same across the ग_लिखो regardless of 32/64 bit
 * note: it's patterned off the SCSI_PASS_THROUGH काष्ठाure
 */
#घोषणा STORVSC_MAX_CMD_LEN			0x10

#घोषणा POST_WIN7_STORVSC_SENSE_BUFFER_SIZE	0x14
#घोषणा PRE_WIN8_STORVSC_SENSE_BUFFER_SIZE	0x12

#घोषणा STORVSC_SENSE_BUFFER_SIZE		0x14
#घोषणा STORVSC_MAX_BUF_LEN_WITH_PADDING	0x14

/*
 * Sense buffer size changed in win8; have a run-समय
 * variable to track the size we should use.  This value will
 * likely change during protocol negotiation but it is valid
 * to start by assuming pre-Win8.
 */
अटल पूर्णांक sense_buffer_size = PRE_WIN8_STORVSC_SENSE_BUFFER_SIZE;

/*
 * The storage protocol version is determined during the
 * initial exchange with the host.  It will indicate which
 * storage functionality is available in the host.
*/
अटल पूर्णांक vmstor_proto_version;

#घोषणा STORVSC_LOGGING_NONE	0
#घोषणा STORVSC_LOGGING_ERROR	1
#घोषणा STORVSC_LOGGING_WARN	2

अटल पूर्णांक logging_level = STORVSC_LOGGING_ERROR;
module_param(logging_level, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(logging_level,
	"Logging level, 0 - None, 1 - Error (default), 2 - Warning.");

अटल अंतरभूत bool करो_logging(पूर्णांक level)
अणु
	वापस logging_level >= level;
पूर्ण

#घोषणा storvsc_log(dev, level, fmt, ...)			\
करो अणु								\
	अगर (करो_logging(level))					\
		dev_warn(&(dev)->device, fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

काष्ठा vmscsi_win8_extension अणु
	/*
	 * The following were added in Winकरोws 8
	 */
	u16 reserve;
	u8  queue_tag;
	u8  queue_action;
	u32 srb_flags;
	u32 समय_out_value;
	u32 queue_sort_ey;
पूर्ण __packed;

काष्ठा vmscsi_request अणु
	u16 length;
	u8 srb_status;
	u8 scsi_status;

	u8  port_number;
	u8  path_id;
	u8  target_id;
	u8  lun;

	u8  cdb_length;
	u8  sense_info_length;
	u8  data_in;
	u8  reserved;

	u32 data_transfer_length;

	जोड़ अणु
		u8 cdb[STORVSC_MAX_CMD_LEN];
		u8 sense_data[STORVSC_SENSE_BUFFER_SIZE];
		u8 reserved_array[STORVSC_MAX_BUF_LEN_WITH_PADDING];
	पूर्ण;
	/*
	 * The following was added in win8.
	 */
	काष्ठा vmscsi_win8_extension win8_extension;

पूर्ण __attribute((packed));

/*
 * The list of storage protocols in order of preference.
 */
काष्ठा vmstor_protocol अणु
	पूर्णांक protocol_version;
	पूर्णांक sense_buffer_size;
	पूर्णांक vmscsi_size_delta;
पूर्ण;


अटल स्थिर काष्ठा vmstor_protocol vmstor_protocols[] = अणु
	अणु
		VMSTOR_PROTO_VERSION_WIN10,
		POST_WIN7_STORVSC_SENSE_BUFFER_SIZE,
		0
	पूर्ण,
	अणु
		VMSTOR_PROTO_VERSION_WIN8_1,
		POST_WIN7_STORVSC_SENSE_BUFFER_SIZE,
		0
	पूर्ण,
	अणु
		VMSTOR_PROTO_VERSION_WIN8,
		POST_WIN7_STORVSC_SENSE_BUFFER_SIZE,
		0
	पूर्ण,
	अणु
		VMSTOR_PROTO_VERSION_WIN7,
		PRE_WIN8_STORVSC_SENSE_BUFFER_SIZE,
		माप(काष्ठा vmscsi_win8_extension),
	पूर्ण,
	अणु
		VMSTOR_PROTO_VERSION_WIN6,
		PRE_WIN8_STORVSC_SENSE_BUFFER_SIZE,
		माप(काष्ठा vmscsi_win8_extension),
	पूर्ण
पूर्ण;


/*
 * This काष्ठाure is sent during the initialization phase to get the dअगरferent
 * properties of the channel.
 */

#घोषणा STORAGE_CHANNEL_SUPPORTS_MULTI_CHANNEL		0x1

काष्ठा vmstorage_channel_properties अणु
	u32 reserved;
	u16 max_channel_cnt;
	u16 reserved1;

	u32 flags;
	u32   max_transfer_bytes;

	u64  reserved2;
पूर्ण __packed;

/*  This काष्ठाure is sent during the storage protocol negotiations. */
काष्ठा vmstorage_protocol_version अणु
	/* Major (MSW) and minor (LSW) version numbers. */
	u16 major_minor;

	/*
	 * Revision number is स्वतः-incremented whenever this file is changed
	 * (See FILL_VMSTOR_REVISION macro above).  Mismatch करोes not
	 * definitely indicate incompatibility--but it करोes indicate mismatched
	 * builds.
	 * This is only used on the winकरोws side. Just set it to 0.
	 */
	u16 revision;
पूर्ण __packed;

/* Channel Property Flags */
#घोषणा STORAGE_CHANNEL_REMOVABLE_FLAG		0x1
#घोषणा STORAGE_CHANNEL_EMULATED_IDE_FLAG	0x2

काष्ठा vstor_packet अणु
	/* Requested operation type */
	क्रमागत vstor_packet_operation operation;

	/*  Flags - see below क्रम values */
	u32 flags;

	/* Status of the request वापसed from the server side. */
	u32 status;

	/* Data payload area */
	जोड़ अणु
		/*
		 * Structure used to क्रमward SCSI commands from the
		 * client to the server.
		 */
		काष्ठा vmscsi_request vm_srb;

		/* Structure used to query channel properties. */
		काष्ठा vmstorage_channel_properties storage_channel_properties;

		/* Used during version negotiations. */
		काष्ठा vmstorage_protocol_version version;

		/* Fibre channel address packet */
		काष्ठा hv_fc_wwn_packet wwn_packet;

		/* Number of sub-channels to create */
		u16 sub_channel_count;

		/* This will be the maximum of the जोड़ members */
		u8  buffer[0x34];
	पूर्ण;
पूर्ण __packed;

/*
 * Packet Flags:
 *
 * This flag indicates that the server should send back a completion क्रम this
 * packet.
 */

#घोषणा REQUEST_COMPLETION_FLAG	0x1

/* Matches Winकरोws-end */
क्रमागत storvsc_request_type अणु
	WRITE_TYPE = 0,
	READ_TYPE,
	UNKNOWN_TYPE,
पूर्ण;

/*
 * SRB status codes and masks; a subset of the codes used here.
 */

#घोषणा SRB_STATUS_AUTOSENSE_VALID	0x80
#घोषणा SRB_STATUS_QUEUE_FROZEN		0x40
#घोषणा SRB_STATUS_INVALID_LUN	0x20
#घोषणा SRB_STATUS_SUCCESS	0x01
#घोषणा SRB_STATUS_ABORTED	0x02
#घोषणा SRB_STATUS_ERROR	0x04
#घोषणा SRB_STATUS_DATA_OVERRUN	0x12

#घोषणा SRB_STATUS(status) \
	(status & ~(SRB_STATUS_AUTOSENSE_VALID | SRB_STATUS_QUEUE_FROZEN))
/*
 * This is the end of Protocol specअगरic defines.
 */

अटल पूर्णांक storvsc_ringbuffer_size = (128 * 1024);
अटल u32 max_outstanding_req_per_channel;
अटल पूर्णांक storvsc_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक queue_depth);

अटल पूर्णांक storvsc_vcpus_per_sub_channel = 4;
अटल अचिन्हित पूर्णांक storvsc_max_hw_queues;

module_param(storvsc_ringbuffer_size, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(storvsc_ringbuffer_size, "Ring buffer size (bytes)");

module_param(storvsc_max_hw_queues, uपूर्णांक, 0644);
MODULE_PARM_DESC(storvsc_max_hw_queues, "Maximum number of hardware queues");

module_param(storvsc_vcpus_per_sub_channel, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(storvsc_vcpus_per_sub_channel, "Ratio of VCPUs to subchannels");

अटल पूर्णांक ring_avail_percent_lowater = 10;
module_param(ring_avail_percent_lowater, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ring_avail_percent_lowater,
		"Select a channel if available ring size > this in percent");

/*
 * Timeout in seconds क्रम all devices managed by this driver.
 */
अटल पूर्णांक storvsc_समयout = 180;

#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
अटल काष्ठा scsi_transport_ढाँचा *fc_transport_ढाँचा;
#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा scsi_driver;
अटल व्योम storvsc_on_channel_callback(व्योम *context);

#घोषणा STORVSC_MAX_LUNS_PER_TARGET			255
#घोषणा STORVSC_MAX_TARGETS				2
#घोषणा STORVSC_MAX_CHANNELS				8

#घोषणा STORVSC_FC_MAX_LUNS_PER_TARGET			255
#घोषणा STORVSC_FC_MAX_TARGETS				128
#घोषणा STORVSC_FC_MAX_CHANNELS				8

#घोषणा STORVSC_IDE_MAX_LUNS_PER_TARGET			64
#घोषणा STORVSC_IDE_MAX_TARGETS				1
#घोषणा STORVSC_IDE_MAX_CHANNELS			1

काष्ठा storvsc_cmd_request अणु
	काष्ठा scsi_cmnd *cmd;

	काष्ठा hv_device *device;

	/* Synchronize the request/response अगर needed */
	काष्ठा completion रुको_event;

	काष्ठा vmbus_channel_packet_multipage_buffer mpb;
	काष्ठा vmbus_packet_mpb_array *payload;
	u32 payload_sz;

	काष्ठा vstor_packet vstor_packet;
पूर्ण;


/* A storvsc device is a device object that contains a vmbus channel */
काष्ठा storvsc_device अणु
	काष्ठा hv_device *device;

	bool	 destroy;
	bool	 drain_notअगरy;
	atomic_t num_outstanding_req;
	काष्ठा Scsi_Host *host;

	रुको_queue_head_t रुकोing_to_drain;

	/*
	 * Each unique Port/Path/Target represents 1 channel ie scsi
	 * controller. In reality, the pathid, targetid is always 0
	 * and the port is set by us
	 */
	अचिन्हित पूर्णांक port_number;
	अचिन्हित अक्षर path_id;
	अचिन्हित अक्षर target_id;

	/*
	 * The size of the vmscsi_request has changed in win8. The
	 * additional size is because of new elements added to the
	 * काष्ठाure. These elements are valid only when we are talking
	 * to a win8 host.
	 * Track the correction to size we need to apply. This value
	 * will likely change during protocol negotiation but it is
	 * valid to start by assuming pre-Win8.
	 */
	पूर्णांक vmscsi_size_delta;

	/*
	 * Max I/O, the device can support.
	 */
	u32   max_transfer_bytes;
	/*
	 * Number of sub-channels we will खोलो.
	 */
	u16 num_sc;
	काष्ठा vmbus_channel **stor_chns;
	/*
	 * Mask of CPUs bound to subchannels.
	 */
	काष्ठा cpumask alloced_cpus;
	/*
	 * Serializes modअगरications of stor_chns[] from storvsc_करो_io()
	 * and storvsc_change_target_cpu().
	 */
	spinlock_t lock;
	/* Used क्रम vsc/vsp channel reset process */
	काष्ठा storvsc_cmd_request init_request;
	काष्ठा storvsc_cmd_request reset_request;
	/*
	 * Currently active port and node names क्रम FC devices.
	 */
	u64 node_name;
	u64 port_name;
#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	काष्ठा fc_rport *rport;
#पूर्ण_अगर
पूर्ण;

काष्ठा hv_host_device अणु
	काष्ठा hv_device *dev;
	अचिन्हित पूर्णांक port;
	अचिन्हित अक्षर path;
	अचिन्हित अक्षर target;
	काष्ठा workqueue_काष्ठा *handle_error_wq;
	काष्ठा work_काष्ठा host_scan_work;
	काष्ठा Scsi_Host *host;
पूर्ण;

काष्ठा storvsc_scan_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा Scsi_Host *host;
	u8 lun;
	u8 tgt_id;
पूर्ण;

अटल व्योम storvsc_device_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा storvsc_scan_work *wrk;
	काष्ठा scsi_device *sdev;

	wrk = container_of(work, काष्ठा storvsc_scan_work, work);

	sdev = scsi_device_lookup(wrk->host, 0, wrk->tgt_id, wrk->lun);
	अगर (!sdev)
		जाओ करोne;
	scsi_rescan_device(&sdev->sdev_gendev);
	scsi_device_put(sdev);

करोne:
	kमुक्त(wrk);
पूर्ण

अटल व्योम storvsc_host_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा scsi_device *sdev;
	काष्ठा hv_host_device *host_device =
		container_of(work, काष्ठा hv_host_device, host_scan_work);

	host = host_device->host;
	/*
	 * Beक्रमe scanning the host, first check to see अगर any of the
	 * currrently known devices have been hot हटाओd. We issue a
	 * "unit ready" command against all currently known devices.
	 * This I/O will result in an error क्रम devices that have been
	 * हटाओd. As part of handling the I/O error, we हटाओ the device.
	 *
	 * When a LUN is added or हटाओd, the host sends us a संकेत to
	 * scan the host. Thus we are क्रमced to discover the LUNs that
	 * may have been हटाओd this way.
	 */
	mutex_lock(&host->scan_mutex);
	shost_क्रम_each_device(sdev, host)
		scsi_test_unit_पढ़ोy(sdev, 1, 1, शून्य);
	mutex_unlock(&host->scan_mutex);
	/*
	 * Now scan the host to discover LUNs that may have been added.
	 */
	scsi_scan_host(host);
पूर्ण

अटल व्योम storvsc_हटाओ_lun(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा storvsc_scan_work *wrk;
	काष्ठा scsi_device *sdev;

	wrk = container_of(work, काष्ठा storvsc_scan_work, work);
	अगर (!scsi_host_get(wrk->host))
		जाओ करोne;

	sdev = scsi_device_lookup(wrk->host, 0, wrk->tgt_id, wrk->lun);

	अगर (sdev) अणु
		scsi_हटाओ_device(sdev);
		scsi_device_put(sdev);
	पूर्ण
	scsi_host_put(wrk->host);

करोne:
	kमुक्त(wrk);
पूर्ण


/*
 * We can get incoming messages from the host that are not in response to
 * messages that we have sent out. An example of this would be messages
 * received by the guest to notअगरy dynamic addition/removal of LUNs. To
 * deal with potential race conditions where the driver may be in the
 * midst of being unloaded when we might receive an unsolicited message
 * from the host, we have implemented a mechanism to gurantee sequential
 * consistency:
 *
 * 1) Once the device is marked as being destroyed, we will fail all
 *    outgoing messages.
 * 2) We permit incoming messages when the device is being destroyed,
 *    only to properly account क्रम messages alपढ़ोy sent out.
 */

अटल अंतरभूत काष्ठा storvsc_device *get_out_stor_device(
					काष्ठा hv_device *device)
अणु
	काष्ठा storvsc_device *stor_device;

	stor_device = hv_get_drvdata(device);

	अगर (stor_device && stor_device->destroy)
		stor_device = शून्य;

	वापस stor_device;
पूर्ण


अटल अंतरभूत व्योम storvsc_रुको_to_drain(काष्ठा storvsc_device *dev)
अणु
	dev->drain_notअगरy = true;
	रुको_event(dev->रुकोing_to_drain,
		   atomic_पढ़ो(&dev->num_outstanding_req) == 0);
	dev->drain_notअगरy = false;
पूर्ण

अटल अंतरभूत काष्ठा storvsc_device *get_in_stor_device(
					काष्ठा hv_device *device)
अणु
	काष्ठा storvsc_device *stor_device;

	stor_device = hv_get_drvdata(device);

	अगर (!stor_device)
		जाओ get_in_err;

	/*
	 * If the device is being destroyed; allow incoming
	 * traffic only to cleanup outstanding requests.
	 */

	अगर (stor_device->destroy  &&
		(atomic_पढ़ो(&stor_device->num_outstanding_req) == 0))
		stor_device = शून्य;

get_in_err:
	वापस stor_device;

पूर्ण

अटल व्योम storvsc_change_target_cpu(काष्ठा vmbus_channel *channel, u32 old,
				      u32 new)
अणु
	काष्ठा storvsc_device *stor_device;
	काष्ठा vmbus_channel *cur_chn;
	bool old_is_alloced = false;
	काष्ठा hv_device *device;
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;

	device = channel->primary_channel ?
			channel->primary_channel->device_obj
				: channel->device_obj;
	stor_device = get_out_stor_device(device);
	अगर (!stor_device)
		वापस;

	/* See storvsc_करो_io() -> get_og_chn(). */
	spin_lock_irqsave(&stor_device->lock, flags);

	/*
	 * Determines अगर the storvsc device has other channels asचिन्हित to
	 * the "old" CPU to update the alloced_cpus mask and the stor_chns
	 * array.
	 */
	अगर (device->channel != channel && device->channel->target_cpu == old) अणु
		cur_chn = device->channel;
		old_is_alloced = true;
		जाओ old_is_alloced;
	पूर्ण
	list_क्रम_each_entry(cur_chn, &device->channel->sc_list, sc_list) अणु
		अगर (cur_chn == channel)
			जारी;
		अगर (cur_chn->target_cpu == old) अणु
			old_is_alloced = true;
			जाओ old_is_alloced;
		पूर्ण
	पूर्ण

old_is_alloced:
	अगर (old_is_alloced)
		WRITE_ONCE(stor_device->stor_chns[old], cur_chn);
	अन्यथा
		cpumask_clear_cpu(old, &stor_device->alloced_cpus);

	/* "Flush" the stor_chns array. */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (stor_device->stor_chns[cpu] && !cpumask_test_cpu(
					cpu, &stor_device->alloced_cpus))
			WRITE_ONCE(stor_device->stor_chns[cpu], शून्य);
	पूर्ण

	WRITE_ONCE(stor_device->stor_chns[new], channel);
	cpumask_set_cpu(new, &stor_device->alloced_cpus);

	spin_unlock_irqrestore(&stor_device->lock, flags);
पूर्ण

अटल व्योम handle_sc_creation(काष्ठा vmbus_channel *new_sc)
अणु
	काष्ठा hv_device *device = new_sc->primary_channel->device_obj;
	काष्ठा device *dev = &device->device;
	काष्ठा storvsc_device *stor_device;
	काष्ठा vmstorage_channel_properties props;
	पूर्णांक ret;

	stor_device = get_out_stor_device(device);
	अगर (!stor_device)
		वापस;

	स_रखो(&props, 0, माप(काष्ठा vmstorage_channel_properties));

	/*
	 * The size of vmbus_requestor is an upper bound on the number of requests
	 * that can be in-progress at any one समय across all channels.
	 */
	new_sc->rqstor_size = scsi_driver.can_queue;

	ret = vmbus_खोलो(new_sc,
			 storvsc_ringbuffer_size,
			 storvsc_ringbuffer_size,
			 (व्योम *)&props,
			 माप(काष्ठा vmstorage_channel_properties),
			 storvsc_on_channel_callback, new_sc);

	/* In हाल vmbus_खोलो() fails, we करोn't use the sub-channel. */
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to open sub-channel: err=%d\n", ret);
		वापस;
	पूर्ण

	new_sc->change_target_cpu_callback = storvsc_change_target_cpu;

	/* Add the sub-channel to the array of available channels. */
	stor_device->stor_chns[new_sc->target_cpu] = new_sc;
	cpumask_set_cpu(new_sc->target_cpu, &stor_device->alloced_cpus);
पूर्ण

अटल व्योम  handle_multichannel_storage(काष्ठा hv_device *device, पूर्णांक max_chns)
अणु
	काष्ठा device *dev = &device->device;
	काष्ठा storvsc_device *stor_device;
	पूर्णांक num_sc;
	काष्ठा storvsc_cmd_request *request;
	काष्ठा vstor_packet *vstor_packet;
	पूर्णांक ret, t;

	/*
	 * If the number of CPUs is artअगरicially restricted, such as
	 * with maxcpus=1 on the kernel boot line, Hyper-V could offer
	 * sub-channels >= the number of CPUs. These sub-channels
	 * should not be created. The primary channel is alपढ़ोy created
	 * and asचिन्हित to one CPU, so check against # CPUs - 1.
	 */
	num_sc = min((पूर्णांक)(num_online_cpus() - 1), max_chns);
	अगर (!num_sc)
		वापस;

	stor_device = get_out_stor_device(device);
	अगर (!stor_device)
		वापस;

	stor_device->num_sc = num_sc;
	request = &stor_device->init_request;
	vstor_packet = &request->vstor_packet;

	/*
	 * Establish a handler क्रम dealing with subchannels.
	 */
	vmbus_set_sc_create_callback(device->channel, handle_sc_creation);

	/*
	 * Request the host to create sub-channels.
	 */
	स_रखो(request, 0, माप(काष्ठा storvsc_cmd_request));
	init_completion(&request->रुको_event);
	vstor_packet->operation = VSTOR_OPERATION_CREATE_SUB_CHANNELS;
	vstor_packet->flags = REQUEST_COMPLETION_FLAG;
	vstor_packet->sub_channel_count = num_sc;

	ret = vmbus_sendpacket(device->channel, vstor_packet,
			       (माप(काष्ठा vstor_packet) -
			       stor_device->vmscsi_size_delta),
			       (अचिन्हित दीर्घ)request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);

	अगर (ret != 0) अणु
		dev_err(dev, "Failed to create sub-channel: err=%d\n", ret);
		वापस;
	पूर्ण

	t = रुको_क्रम_completion_समयout(&request->रुको_event, 10*HZ);
	अगर (t == 0) अणु
		dev_err(dev, "Failed to create sub-channel: timed out\n");
		वापस;
	पूर्ण

	अगर (vstor_packet->operation != VSTOR_OPERATION_COMPLETE_IO ||
	    vstor_packet->status != 0) अणु
		dev_err(dev, "Failed to create sub-channel: op=%d, sts=%d\n",
			vstor_packet->operation, vstor_packet->status);
		वापस;
	पूर्ण

	/*
	 * We need to करो nothing here, because vmbus_process_offer()
	 * invokes channel->sc_creation_callback, which will खोलो and use
	 * the sub-channel(s).
	 */
पूर्ण

अटल व्योम cache_wwn(काष्ठा storvsc_device *stor_device,
		      काष्ठा vstor_packet *vstor_packet)
अणु
	/*
	 * Cache the currently active port and node ww names.
	 */
	अगर (vstor_packet->wwn_packet.primary_active) अणु
		stor_device->node_name =
			wwn_to_u64(vstor_packet->wwn_packet.primary_node_wwn);
		stor_device->port_name =
			wwn_to_u64(vstor_packet->wwn_packet.primary_port_wwn);
	पूर्ण अन्यथा अणु
		stor_device->node_name =
			wwn_to_u64(vstor_packet->wwn_packet.secondary_node_wwn);
		stor_device->port_name =
			wwn_to_u64(vstor_packet->wwn_packet.secondary_port_wwn);
	पूर्ण
पूर्ण


अटल पूर्णांक storvsc_execute_vstor_op(काष्ठा hv_device *device,
				    काष्ठा storvsc_cmd_request *request,
				    bool status_check)
अणु
	काष्ठा storvsc_device *stor_device;
	काष्ठा vstor_packet *vstor_packet;
	पूर्णांक ret, t;

	stor_device = get_out_stor_device(device);
	अगर (!stor_device)
		वापस -ENODEV;

	vstor_packet = &request->vstor_packet;

	init_completion(&request->रुको_event);
	vstor_packet->flags = REQUEST_COMPLETION_FLAG;

	ret = vmbus_sendpacket(device->channel, vstor_packet,
			       (माप(काष्ठा vstor_packet) -
			       stor_device->vmscsi_size_delta),
			       (अचिन्हित दीर्घ)request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret != 0)
		वापस ret;

	t = रुको_क्रम_completion_समयout(&request->रुको_event, 5*HZ);
	अगर (t == 0)
		वापस -ETIMEDOUT;

	अगर (!status_check)
		वापस ret;

	अगर (vstor_packet->operation != VSTOR_OPERATION_COMPLETE_IO ||
	    vstor_packet->status != 0)
		वापस -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक storvsc_channel_init(काष्ठा hv_device *device, bool is_fc)
अणु
	काष्ठा storvsc_device *stor_device;
	काष्ठा storvsc_cmd_request *request;
	काष्ठा vstor_packet *vstor_packet;
	पूर्णांक ret, i;
	पूर्णांक max_chns;
	bool process_sub_channels = false;

	stor_device = get_out_stor_device(device);
	अगर (!stor_device)
		वापस -ENODEV;

	request = &stor_device->init_request;
	vstor_packet = &request->vstor_packet;

	/*
	 * Now, initiate the vsc/vsp initialization protocol on the खोलो
	 * channel
	 */
	स_रखो(request, 0, माप(काष्ठा storvsc_cmd_request));
	vstor_packet->operation = VSTOR_OPERATION_BEGIN_INITIALIZATION;
	ret = storvsc_execute_vstor_op(device, request, true);
	अगर (ret)
		वापस ret;
	/*
	 * Query host supported protocol version.
	 */

	क्रम (i = 0; i < ARRAY_SIZE(vmstor_protocols); i++) अणु
		/* reuse the packet क्रम version range supported */
		स_रखो(vstor_packet, 0, माप(काष्ठा vstor_packet));
		vstor_packet->operation =
			VSTOR_OPERATION_QUERY_PROTOCOL_VERSION;

		vstor_packet->version.major_minor =
			vmstor_protocols[i].protocol_version;

		/*
		 * The revision number is only used in Winकरोws; set it to 0.
		 */
		vstor_packet->version.revision = 0;
		ret = storvsc_execute_vstor_op(device, request, false);
		अगर (ret != 0)
			वापस ret;

		अगर (vstor_packet->operation != VSTOR_OPERATION_COMPLETE_IO)
			वापस -EINVAL;

		अगर (vstor_packet->status == 0) अणु
			vmstor_proto_version =
				vmstor_protocols[i].protocol_version;

			sense_buffer_size =
				vmstor_protocols[i].sense_buffer_size;

			stor_device->vmscsi_size_delta =
				vmstor_protocols[i].vmscsi_size_delta;

			अवरोध;
		पूर्ण
	पूर्ण

	अगर (vstor_packet->status != 0)
		वापस -EINVAL;


	स_रखो(vstor_packet, 0, माप(काष्ठा vstor_packet));
	vstor_packet->operation = VSTOR_OPERATION_QUERY_PROPERTIES;
	ret = storvsc_execute_vstor_op(device, request, true);
	अगर (ret != 0)
		वापस ret;

	/*
	 * Check to see अगर multi-channel support is there.
	 * Hosts that implement protocol version of 5.1 and above
	 * support multi-channel.
	 */
	max_chns = vstor_packet->storage_channel_properties.max_channel_cnt;

	/*
	 * Allocate state to manage the sub-channels.
	 * We allocate an array based on the numbers of possible CPUs
	 * (Hyper-V करोes not support cpu online/offline).
	 * This Array will be sparseley populated with unique
	 * channels - primary + sub-channels.
	 * We will however populate all the slots to evenly distribute
	 * the load.
	 */
	stor_device->stor_chns = kसुस्मृति(num_possible_cpus(), माप(व्योम *),
					 GFP_KERNEL);
	अगर (stor_device->stor_chns == शून्य)
		वापस -ENOMEM;

	device->channel->change_target_cpu_callback = storvsc_change_target_cpu;

	stor_device->stor_chns[device->channel->target_cpu] = device->channel;
	cpumask_set_cpu(device->channel->target_cpu,
			&stor_device->alloced_cpus);

	अगर (vmstor_proto_version >= VMSTOR_PROTO_VERSION_WIN8) अणु
		अगर (vstor_packet->storage_channel_properties.flags &
		    STORAGE_CHANNEL_SUPPORTS_MULTI_CHANNEL)
			process_sub_channels = true;
	पूर्ण
	stor_device->max_transfer_bytes =
		vstor_packet->storage_channel_properties.max_transfer_bytes;

	अगर (!is_fc)
		जाओ करोne;

	/*
	 * For FC devices retrieve FC HBA data.
	 */
	स_रखो(vstor_packet, 0, माप(काष्ठा vstor_packet));
	vstor_packet->operation = VSTOR_OPERATION_FCHBA_DATA;
	ret = storvsc_execute_vstor_op(device, request, true);
	अगर (ret != 0)
		वापस ret;

	/*
	 * Cache the currently active port and node ww names.
	 */
	cache_wwn(stor_device, vstor_packet);

करोne:

	स_रखो(vstor_packet, 0, माप(काष्ठा vstor_packet));
	vstor_packet->operation = VSTOR_OPERATION_END_INITIALIZATION;
	ret = storvsc_execute_vstor_op(device, request, true);
	अगर (ret != 0)
		वापस ret;

	अगर (process_sub_channels)
		handle_multichannel_storage(device, max_chns);

	वापस ret;
पूर्ण

अटल व्योम storvsc_handle_error(काष्ठा vmscsi_request *vm_srb,
				काष्ठा scsi_cmnd *scmnd,
				काष्ठा Scsi_Host *host,
				u8 asc, u8 ascq)
अणु
	काष्ठा storvsc_scan_work *wrk;
	व्योम (*process_err_fn)(काष्ठा work_काष्ठा *work);
	काष्ठा hv_host_device *host_dev = shost_priv(host);
	bool करो_work = false;

	चयन (SRB_STATUS(vm_srb->srb_status)) अणु
	हाल SRB_STATUS_ERROR:
		/*
		 * Let upper layer deal with error when
		 * sense message is present.
		 */

		अगर (vm_srb->srb_status & SRB_STATUS_AUTOSENSE_VALID)
			अवरोध;
		/*
		 * If there is an error; offline the device since all
		 * error recovery strategies would have alपढ़ोy been
		 * deployed on the host side. However, अगर the command
		 * were a pass-through command deal with it appropriately.
		 */
		चयन (scmnd->cmnd[0]) अणु
		हाल ATA_16:
		हाल ATA_12:
			set_host_byte(scmnd, DID_PASSTHROUGH);
			अवरोध;
		/*
		 * On Some Winकरोws hosts TEST_UNIT_READY command can वापस
		 * SRB_STATUS_ERROR, let the upper level code deal with it
		 * based on the sense inक्रमmation.
		 */
		हाल TEST_UNIT_READY:
			अवरोध;
		शेष:
			set_host_byte(scmnd, DID_ERROR);
		पूर्ण
		अवरोध;
	हाल SRB_STATUS_INVALID_LUN:
		set_host_byte(scmnd, DID_NO_CONNECT);
		करो_work = true;
		process_err_fn = storvsc_हटाओ_lun;
		अवरोध;
	हाल SRB_STATUS_ABORTED:
		अगर (vm_srb->srb_status & SRB_STATUS_AUTOSENSE_VALID &&
		    (asc == 0x2a) && (ascq == 0x9)) अणु
			करो_work = true;
			process_err_fn = storvsc_device_scan;
			/*
			 * Retry the I/O that triggered this.
			 */
			set_host_byte(scmnd, DID_REQUEUE);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!करो_work)
		वापस;

	/*
	 * We need to schedule work to process this error; schedule it.
	 */
	wrk = kदो_स्मृति(माप(काष्ठा storvsc_scan_work), GFP_ATOMIC);
	अगर (!wrk) अणु
		set_host_byte(scmnd, DID_TARGET_FAILURE);
		वापस;
	पूर्ण

	wrk->host = host;
	wrk->lun = vm_srb->lun;
	wrk->tgt_id = vm_srb->target_id;
	INIT_WORK(&wrk->work, process_err_fn);
	queue_work(host_dev->handle_error_wq, &wrk->work);
पूर्ण


अटल व्योम storvsc_command_completion(काष्ठा storvsc_cmd_request *cmd_request,
				       काष्ठा storvsc_device *stor_dev)
अणु
	काष्ठा scsi_cmnd *scmnd = cmd_request->cmd;
	काष्ठा scsi_sense_hdr sense_hdr;
	काष्ठा vmscsi_request *vm_srb;
	u32 data_transfer_length;
	काष्ठा Scsi_Host *host;
	u32 payload_sz = cmd_request->payload_sz;
	व्योम *payload = cmd_request->payload;

	host = stor_dev->host;

	vm_srb = &cmd_request->vstor_packet.vm_srb;
	data_transfer_length = vm_srb->data_transfer_length;

	scmnd->result = vm_srb->scsi_status;

	अगर (scmnd->result) अणु
		अगर (scsi_normalize_sense(scmnd->sense_buffer,
				SCSI_SENSE_BUFFERSIZE, &sense_hdr) &&
		    !(sense_hdr.sense_key == NOT_READY &&
				 sense_hdr.asc == 0x03A) &&
		    करो_logging(STORVSC_LOGGING_ERROR))
			scsi_prपूर्णांक_sense_hdr(scmnd->device, "storvsc",
					     &sense_hdr);
	पूर्ण

	अगर (vm_srb->srb_status != SRB_STATUS_SUCCESS) अणु
		storvsc_handle_error(vm_srb, scmnd, host, sense_hdr.asc,
					 sense_hdr.ascq);
		/*
		 * The Winकरोws driver set data_transfer_length on
		 * SRB_STATUS_DATA_OVERRUN. On other errors, this value
		 * is untouched.  In these हालs we set it to 0.
		 */
		अगर (vm_srb->srb_status != SRB_STATUS_DATA_OVERRUN)
			data_transfer_length = 0;
	पूर्ण

	/* Validate data_transfer_length (from Hyper-V) */
	अगर (data_transfer_length > cmd_request->payload->range.len)
		data_transfer_length = cmd_request->payload->range.len;

	scsi_set_resid(scmnd,
		cmd_request->payload->range.len - data_transfer_length);

	scmnd->scsi_करोne(scmnd);

	अगर (payload_sz >
		माप(काष्ठा vmbus_channel_packet_multipage_buffer))
		kमुक्त(payload);
पूर्ण

अटल व्योम storvsc_on_io_completion(काष्ठा storvsc_device *stor_device,
				  काष्ठा vstor_packet *vstor_packet,
				  काष्ठा storvsc_cmd_request *request)
अणु
	काष्ठा vstor_packet *stor_pkt;
	काष्ठा hv_device *device = stor_device->device;

	stor_pkt = &request->vstor_packet;

	/*
	 * The current SCSI handling on the host side करोes
	 * not correctly handle:
	 * INQUIRY command with page code parameter set to 0x80
	 * MODE_SENSE command with cmd[2] == 0x1c
	 *
	 * Setup srb and scsi status so this won't be fatal.
	 * We करो this so we can distinguish truly fatal failues
	 * (srb status == 0x4) and off-line the device in that हाल.
	 */

	अगर ((stor_pkt->vm_srb.cdb[0] == INQUIRY) ||
	   (stor_pkt->vm_srb.cdb[0] == MODE_SENSE)) अणु
		vstor_packet->vm_srb.scsi_status = 0;
		vstor_packet->vm_srb.srb_status = SRB_STATUS_SUCCESS;
	पूर्ण


	/* Copy over the status...etc */
	stor_pkt->vm_srb.scsi_status = vstor_packet->vm_srb.scsi_status;
	stor_pkt->vm_srb.srb_status = vstor_packet->vm_srb.srb_status;

	/* Validate sense_info_length (from Hyper-V) */
	अगर (vstor_packet->vm_srb.sense_info_length > sense_buffer_size)
		vstor_packet->vm_srb.sense_info_length = sense_buffer_size;

	stor_pkt->vm_srb.sense_info_length =
	vstor_packet->vm_srb.sense_info_length;

	अगर (vstor_packet->vm_srb.scsi_status != 0 ||
	    vstor_packet->vm_srb.srb_status != SRB_STATUS_SUCCESS)
		storvsc_log(device, STORVSC_LOGGING_WARN,
			"cmd 0x%x scsi status 0x%x srb status 0x%x\n",
			stor_pkt->vm_srb.cdb[0],
			vstor_packet->vm_srb.scsi_status,
			vstor_packet->vm_srb.srb_status);

	अगर ((vstor_packet->vm_srb.scsi_status & 0xFF) == 0x02) अणु
		/* CHECK_CONDITION */
		अगर (vstor_packet->vm_srb.srb_status &
			SRB_STATUS_AUTOSENSE_VALID) अणु
			/* स्वतःsense data available */

			storvsc_log(device, STORVSC_LOGGING_WARN,
				"stor pkt %p autosense data valid - len %d\n",
				request, vstor_packet->vm_srb.sense_info_length);

			स_नकल(request->cmd->sense_buffer,
			       vstor_packet->vm_srb.sense_data,
			       vstor_packet->vm_srb.sense_info_length);

		पूर्ण
	पूर्ण

	stor_pkt->vm_srb.data_transfer_length =
	vstor_packet->vm_srb.data_transfer_length;

	storvsc_command_completion(request, stor_device);

	अगर (atomic_dec_and_test(&stor_device->num_outstanding_req) &&
		stor_device->drain_notअगरy)
		wake_up(&stor_device->रुकोing_to_drain);


पूर्ण

अटल व्योम storvsc_on_receive(काष्ठा storvsc_device *stor_device,
			     काष्ठा vstor_packet *vstor_packet,
			     काष्ठा storvsc_cmd_request *request)
अणु
	काष्ठा hv_host_device *host_dev;
	चयन (vstor_packet->operation) अणु
	हाल VSTOR_OPERATION_COMPLETE_IO:
		storvsc_on_io_completion(stor_device, vstor_packet, request);
		अवरोध;

	हाल VSTOR_OPERATION_REMOVE_DEVICE:
	हाल VSTOR_OPERATION_ENUMERATE_BUS:
		host_dev = shost_priv(stor_device->host);
		queue_work(
			host_dev->handle_error_wq, &host_dev->host_scan_work);
		अवरोध;

	हाल VSTOR_OPERATION_FCHBA_DATA:
		cache_wwn(stor_device, vstor_packet);
#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
		fc_host_node_name(stor_device->host) = stor_device->node_name;
		fc_host_port_name(stor_device->host) = stor_device->port_name;
#पूर्ण_अगर
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम storvsc_on_channel_callback(व्योम *context)
अणु
	काष्ठा vmbus_channel *channel = (काष्ठा vmbus_channel *)context;
	स्थिर काष्ठा vmpacket_descriptor *desc;
	काष्ठा hv_device *device;
	काष्ठा storvsc_device *stor_device;

	अगर (channel->primary_channel != शून्य)
		device = channel->primary_channel->device_obj;
	अन्यथा
		device = channel->device_obj;

	stor_device = get_in_stor_device(device);
	अगर (!stor_device)
		वापस;

	क्रमeach_vmbus_pkt(desc, channel) अणु
		व्योम *packet = hv_pkt_data(desc);
		काष्ठा storvsc_cmd_request *request;
		u64 cmd_rqst;

		cmd_rqst = vmbus_request_addr(&channel->requestor,
					      desc->trans_id);
		अगर (cmd_rqst == VMBUS_RQST_ERROR) अणु
			dev_err(&device->device,
				"Incorrect transaction id\n");
			जारी;
		पूर्ण

		request = (काष्ठा storvsc_cmd_request *)(अचिन्हित दीर्घ)cmd_rqst;

		अगर (hv_pkt_datalen(desc) < माप(काष्ठा vstor_packet) -
				stor_device->vmscsi_size_delta) अणु
			dev_err(&device->device, "Invalid packet len\n");
			जारी;
		पूर्ण

		अगर (request == &stor_device->init_request ||
		    request == &stor_device->reset_request) अणु
			स_नकल(&request->vstor_packet, packet,
			       (माप(काष्ठा vstor_packet) - stor_device->vmscsi_size_delta));
			complete(&request->रुको_event);
		पूर्ण अन्यथा अणु
			storvsc_on_receive(stor_device, packet, request);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक storvsc_connect_to_vsp(काष्ठा hv_device *device, u32 ring_size,
				  bool is_fc)
अणु
	काष्ठा vmstorage_channel_properties props;
	पूर्णांक ret;

	स_रखो(&props, 0, माप(काष्ठा vmstorage_channel_properties));

	/*
	 * The size of vmbus_requestor is an upper bound on the number of requests
	 * that can be in-progress at any one समय across all channels.
	 */
	device->channel->rqstor_size = scsi_driver.can_queue;

	ret = vmbus_खोलो(device->channel,
			 ring_size,
			 ring_size,
			 (व्योम *)&props,
			 माप(काष्ठा vmstorage_channel_properties),
			 storvsc_on_channel_callback, device->channel);

	अगर (ret != 0)
		वापस ret;

	ret = storvsc_channel_init(device, is_fc);

	वापस ret;
पूर्ण

अटल पूर्णांक storvsc_dev_हटाओ(काष्ठा hv_device *device)
अणु
	काष्ठा storvsc_device *stor_device;

	stor_device = hv_get_drvdata(device);

	stor_device->destroy = true;

	/* Make sure flag is set beक्रमe रुकोing */
	wmb();

	/*
	 * At this poपूर्णांक, all outbound traffic should be disable. We
	 * only allow inbound traffic (responses) to proceed so that
	 * outstanding requests can be completed.
	 */

	storvsc_रुको_to_drain(stor_device);

	/*
	 * Since we have alपढ़ोy drained, we करोn't need to busy रुको
	 * as was करोne in final_release_stor_device()
	 * Note that we cannot set the ext poपूर्णांकer to शून्य until
	 * we have drained - to drain the outgoing packets, we need to
	 * allow incoming packets.
	 */
	hv_set_drvdata(device, शून्य);

	/* Close the channel */
	vmbus_बंद(device->channel);

	kमुक्त(stor_device->stor_chns);
	kमुक्त(stor_device);
	वापस 0;
पूर्ण

अटल काष्ठा vmbus_channel *get_og_chn(काष्ठा storvsc_device *stor_device,
					u16 q_num)
अणु
	u16 slot = 0;
	u16 hash_qnum;
	स्थिर काष्ठा cpumask *node_mask;
	पूर्णांक num_channels, tgt_cpu;

	अगर (stor_device->num_sc == 0) अणु
		stor_device->stor_chns[q_num] = stor_device->device->channel;
		वापस stor_device->device->channel;
	पूर्ण

	/*
	 * Our channel array is sparsley populated and we
	 * initiated I/O on a processor/hw-q that करोes not
	 * currently have a designated channel. Fix this.
	 * The strategy is simple:
	 * I. Ensure NUMA locality
	 * II. Distribute evenly (best efक्रमt)
	 */

	node_mask = cpumask_of_node(cpu_to_node(q_num));

	num_channels = 0;
	क्रम_each_cpu(tgt_cpu, &stor_device->alloced_cpus) अणु
		अगर (cpumask_test_cpu(tgt_cpu, node_mask))
			num_channels++;
	पूर्ण
	अगर (num_channels == 0) अणु
		stor_device->stor_chns[q_num] = stor_device->device->channel;
		वापस stor_device->device->channel;
	पूर्ण

	hash_qnum = q_num;
	जबतक (hash_qnum >= num_channels)
		hash_qnum -= num_channels;

	क्रम_each_cpu(tgt_cpu, &stor_device->alloced_cpus) अणु
		अगर (!cpumask_test_cpu(tgt_cpu, node_mask))
			जारी;
		अगर (slot == hash_qnum)
			अवरोध;
		slot++;
	पूर्ण

	stor_device->stor_chns[q_num] = stor_device->stor_chns[tgt_cpu];

	वापस stor_device->stor_chns[q_num];
पूर्ण


अटल पूर्णांक storvsc_करो_io(काष्ठा hv_device *device,
			 काष्ठा storvsc_cmd_request *request, u16 q_num)
अणु
	काष्ठा storvsc_device *stor_device;
	काष्ठा vstor_packet *vstor_packet;
	काष्ठा vmbus_channel *outgoing_channel, *channel;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	स्थिर काष्ठा cpumask *node_mask;
	पूर्णांक tgt_cpu;

	vstor_packet = &request->vstor_packet;
	stor_device = get_out_stor_device(device);

	अगर (!stor_device)
		वापस -ENODEV;


	request->device  = device;
	/*
	 * Select an appropriate channel to send the request out.
	 */
	/* See storvsc_change_target_cpu(). */
	outgoing_channel = READ_ONCE(stor_device->stor_chns[q_num]);
	अगर (outgoing_channel != शून्य) अणु
		अगर (outgoing_channel->target_cpu == q_num) अणु
			/*
			 * Ideally, we want to pick a dअगरferent channel अगर
			 * available on the same NUMA node.
			 */
			node_mask = cpumask_of_node(cpu_to_node(q_num));
			क्रम_each_cpu_wrap(tgt_cpu,
				 &stor_device->alloced_cpus, q_num + 1) अणु
				अगर (!cpumask_test_cpu(tgt_cpu, node_mask))
					जारी;
				अगर (tgt_cpu == q_num)
					जारी;
				channel = READ_ONCE(
					stor_device->stor_chns[tgt_cpu]);
				अगर (channel == शून्य)
					जारी;
				अगर (hv_get_avail_to_ग_लिखो_percent(
							&channel->outbound)
						> ring_avail_percent_lowater) अणु
					outgoing_channel = channel;
					जाओ found_channel;
				पूर्ण
			पूर्ण

			/*
			 * All the other channels on the same NUMA node are
			 * busy. Try to use the channel on the current CPU
			 */
			अगर (hv_get_avail_to_ग_लिखो_percent(
						&outgoing_channel->outbound)
					> ring_avail_percent_lowater)
				जाओ found_channel;

			/*
			 * If we reach here, all the channels on the current
			 * NUMA node are busy. Try to find a channel in
			 * other NUMA nodes
			 */
			क्रम_each_cpu(tgt_cpu, &stor_device->alloced_cpus) अणु
				अगर (cpumask_test_cpu(tgt_cpu, node_mask))
					जारी;
				channel = READ_ONCE(
					stor_device->stor_chns[tgt_cpu]);
				अगर (channel == शून्य)
					जारी;
				अगर (hv_get_avail_to_ग_लिखो_percent(
							&channel->outbound)
						> ring_avail_percent_lowater) अणु
					outgoing_channel = channel;
					जाओ found_channel;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&stor_device->lock, flags);
		outgoing_channel = stor_device->stor_chns[q_num];
		अगर (outgoing_channel != शून्य) अणु
			spin_unlock_irqrestore(&stor_device->lock, flags);
			जाओ found_channel;
		पूर्ण
		outgoing_channel = get_og_chn(stor_device, q_num);
		spin_unlock_irqrestore(&stor_device->lock, flags);
	पूर्ण

found_channel:
	vstor_packet->flags |= REQUEST_COMPLETION_FLAG;

	vstor_packet->vm_srb.length = (माप(काष्ठा vmscsi_request) -
					stor_device->vmscsi_size_delta);


	vstor_packet->vm_srb.sense_info_length = sense_buffer_size;


	vstor_packet->vm_srb.data_transfer_length =
	request->payload->range.len;

	vstor_packet->operation = VSTOR_OPERATION_EXECUTE_SRB;

	अगर (request->payload->range.len) अणु

		ret = vmbus_sendpacket_mpb_desc(outgoing_channel,
				request->payload, request->payload_sz,
				vstor_packet,
				(माप(काष्ठा vstor_packet) -
				stor_device->vmscsi_size_delta),
				(अचिन्हित दीर्घ)request);
	पूर्ण अन्यथा अणु
		ret = vmbus_sendpacket(outgoing_channel, vstor_packet,
			       (माप(काष्ठा vstor_packet) -
				stor_device->vmscsi_size_delta),
			       (अचिन्हित दीर्घ)request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	पूर्ण

	अगर (ret != 0)
		वापस ret;

	atomic_inc(&stor_device->num_outstanding_req);

	वापस ret;
पूर्ण

अटल पूर्णांक storvsc_device_alloc(काष्ठा scsi_device *sdevice)
अणु
	/*
	 * Set blist flag to permit the पढ़ोing of the VPD pages even when
	 * the target may claim SPC-2 compliance. MSFT tarमाला_लो currently
	 * claim SPC-2 compliance जबतक they implement post SPC-2 features.
	 * With this flag we can correctly handle WRITE_SAME_16 issues.
	 *
	 * Hypervisor reports SCSI_UNKNOWN type क्रम DVD ROM device but
	 * still supports REPORT LUN.
	 */
	sdevice->sdev_bflags = BLIST_REPORTLUN2 | BLIST_TRY_VPD_PAGES;

	वापस 0;
पूर्ण

अटल पूर्णांक storvsc_device_configure(काष्ठा scsi_device *sdevice)
अणु
	blk_queue_rq_समयout(sdevice->request_queue, (storvsc_समयout * HZ));

	sdevice->no_ग_लिखो_same = 1;

	/*
	 * If the host is WIN8 or WIN8 R2, claim conक्रमmance to SPC-3
	 * अगर the device is a MSFT भव device.  If the host is
	 * WIN10 or newer, allow ग_लिखो_same.
	 */
	अगर (!म_भेदन(sdevice->venकरोr, "Msft", 4)) अणु
		चयन (vmstor_proto_version) अणु
		हाल VMSTOR_PROTO_VERSION_WIN8:
		हाल VMSTOR_PROTO_VERSION_WIN8_1:
			sdevice->scsi_level = SCSI_SPC_3;
			अवरोध;
		पूर्ण

		अगर (vmstor_proto_version >= VMSTOR_PROTO_VERSION_WIN10)
			sdevice->no_ग_लिखो_same = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक storvsc_get_chs(काष्ठा scsi_device *sdev, काष्ठा block_device * bdev,
			   sector_t capacity, पूर्णांक *info)
अणु
	sector_t nsect = capacity;
	sector_t cylinders = nsect;
	पूर्णांक heads, sectors_pt;

	/*
	 * We are making up these values; let us keep it simple.
	 */
	heads = 0xff;
	sectors_pt = 0x3f;      /* Sectors per track */
	sector_भाग(cylinders, heads * sectors_pt);
	अगर ((sector_t)(cylinders + 1) * heads * sectors_pt < nsect)
		cylinders = 0xffff;

	info[0] = heads;
	info[1] = sectors_pt;
	info[2] = (पूर्णांक)cylinders;

	वापस 0;
पूर्ण

अटल पूर्णांक storvsc_host_reset_handler(काष्ठा scsi_cmnd *scmnd)
अणु
	काष्ठा hv_host_device *host_dev = shost_priv(scmnd->device->host);
	काष्ठा hv_device *device = host_dev->dev;

	काष्ठा storvsc_device *stor_device;
	काष्ठा storvsc_cmd_request *request;
	काष्ठा vstor_packet *vstor_packet;
	पूर्णांक ret, t;

	stor_device = get_out_stor_device(device);
	अगर (!stor_device)
		वापस FAILED;

	request = &stor_device->reset_request;
	vstor_packet = &request->vstor_packet;
	स_रखो(vstor_packet, 0, माप(काष्ठा vstor_packet));

	init_completion(&request->रुको_event);

	vstor_packet->operation = VSTOR_OPERATION_RESET_BUS;
	vstor_packet->flags = REQUEST_COMPLETION_FLAG;
	vstor_packet->vm_srb.path_id = stor_device->path_id;

	ret = vmbus_sendpacket(device->channel, vstor_packet,
			       (माप(काष्ठा vstor_packet) -
				stor_device->vmscsi_size_delta),
			       (अचिन्हित दीर्घ)&stor_device->reset_request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	अगर (ret != 0)
		वापस FAILED;

	t = रुको_क्रम_completion_समयout(&request->रुको_event, 5*HZ);
	अगर (t == 0)
		वापस TIMEOUT_ERROR;


	/*
	 * At this poपूर्णांक, all outstanding requests in the adapter
	 * should have been flushed out and वापस to us
	 * There is a potential race here where the host may be in
	 * the process of responding when we वापस from here.
	 * Just रुको क्रम all in-transit packets to be accounted क्रम
	 * beक्रमe we वापस from here.
	 */
	storvsc_रुको_to_drain(stor_device);

	वापस SUCCESS;
पूर्ण

/*
 * The host guarantees to respond to each command, although I/O latencies might
 * be unbounded on Azure.  Reset the समयr unconditionally to give the host a
 * chance to perक्रमm EH.
 */
अटल क्रमागत blk_eh_समयr_वापस storvsc_eh_समयd_out(काष्ठा scsi_cmnd *scmnd)
अणु
#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	अगर (scmnd->device->host->transportt == fc_transport_ढाँचा)
		वापस fc_eh_समयd_out(scmnd);
#पूर्ण_अगर
	वापस BLK_EH_RESET_TIMER;
पूर्ण

अटल bool storvsc_scsi_cmd_ok(काष्ठा scsi_cmnd *scmnd)
अणु
	bool allowed = true;
	u8 scsi_op = scmnd->cmnd[0];

	चयन (scsi_op) अणु
	/* the host करोes not handle WRITE_SAME, log accident usage */
	हाल WRITE_SAME:
	/*
	 * smartd sends this command and the host करोes not handle
	 * this. So, करोn't send it.
	 */
	हाल SET_WINDOW:
		scmnd->result = DID_ERROR << 16;
		allowed = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस allowed;
पूर्ण

अटल पूर्णांक storvsc_queuecommand(काष्ठा Scsi_Host *host, काष्ठा scsi_cmnd *scmnd)
अणु
	पूर्णांक ret;
	काष्ठा hv_host_device *host_dev = shost_priv(host);
	काष्ठा hv_device *dev = host_dev->dev;
	काष्ठा storvsc_cmd_request *cmd_request = scsi_cmd_priv(scmnd);
	पूर्णांक i;
	काष्ठा scatterlist *sgl;
	अचिन्हित पूर्णांक sg_count;
	काष्ठा vmscsi_request *vm_srb;
	काष्ठा vmbus_packet_mpb_array  *payload;
	u32 payload_sz;
	u32 length;

	अगर (vmstor_proto_version <= VMSTOR_PROTO_VERSION_WIN8) अणु
		/*
		 * On legacy hosts filter unimplemented commands.
		 * Future hosts are expected to correctly handle
		 * unsupported commands. Furthermore, it is
		 * possible that some of the currently
		 * unsupported commands maybe supported in
		 * future versions of the host.
		 */
		अगर (!storvsc_scsi_cmd_ok(scmnd)) अणु
			scmnd->scsi_करोne(scmnd);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Setup the cmd request */
	cmd_request->cmd = scmnd;

	स_रखो(&cmd_request->vstor_packet, 0, माप(काष्ठा vstor_packet));
	vm_srb = &cmd_request->vstor_packet.vm_srb;
	vm_srb->win8_extension.समय_out_value = 60;

	vm_srb->win8_extension.srb_flags |=
		SRB_FLAGS_DISABLE_SYNCH_TRANSFER;

	अगर (scmnd->device->tagged_supported) अणु
		vm_srb->win8_extension.srb_flags |=
		(SRB_FLAGS_QUEUE_ACTION_ENABLE | SRB_FLAGS_NO_QUEUE_FREEZE);
		vm_srb->win8_extension.queue_tag = SP_UNTAGGED;
		vm_srb->win8_extension.queue_action = SRB_SIMPLE_TAG_REQUEST;
	पूर्ण

	/* Build the SRB */
	चयन (scmnd->sc_data_direction) अणु
	हाल DMA_TO_DEVICE:
		vm_srb->data_in = WRITE_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_DATA_OUT;
		अवरोध;
	हाल DMA_FROM_DEVICE:
		vm_srb->data_in = READ_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_DATA_IN;
		अवरोध;
	हाल DMA_NONE:
		vm_srb->data_in = UNKNOWN_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_NO_DATA_TRANSFER;
		अवरोध;
	शेष:
		/*
		 * This is DMA_BIसूचीECTIONAL or something अन्यथा we are never
		 * supposed to see here.
		 */
		WARN(1, "Unexpected data direction: %d\n",
		     scmnd->sc_data_direction);
		वापस -EINVAL;
	पूर्ण


	vm_srb->port_number = host_dev->port;
	vm_srb->path_id = scmnd->device->channel;
	vm_srb->target_id = scmnd->device->id;
	vm_srb->lun = scmnd->device->lun;

	vm_srb->cdb_length = scmnd->cmd_len;

	स_नकल(vm_srb->cdb, scmnd->cmnd, vm_srb->cdb_length);

	sgl = (काष्ठा scatterlist *)scsi_sglist(scmnd);
	sg_count = scsi_sg_count(scmnd);

	length = scsi_bufflen(scmnd);
	payload = (काष्ठा vmbus_packet_mpb_array *)&cmd_request->mpb;
	payload_sz = माप(cmd_request->mpb);

	अगर (sg_count) अणु
		अचिन्हित पूर्णांक hvpgoff, hvpfns_to_add;
		अचिन्हित दीर्घ offset_in_hvpg = offset_in_hvpage(sgl->offset);
		अचिन्हित पूर्णांक hvpg_count = HVPFN_UP(offset_in_hvpg + length);
		u64 hvpfn;

		अगर (hvpg_count > MAX_PAGE_BUFFER_COUNT) अणु

			payload_sz = (hvpg_count * माप(u64) +
				      माप(काष्ठा vmbus_packet_mpb_array));
			payload = kzalloc(payload_sz, GFP_ATOMIC);
			अगर (!payload)
				वापस SCSI_MLQUEUE_DEVICE_BUSY;
		पूर्ण

		payload->range.len = length;
		payload->range.offset = offset_in_hvpg;


		क्रम (i = 0; sgl != शून्य; sgl = sg_next(sgl)) अणु
			/*
			 * Init values क्रम the current sgl entry. hvpgoff
			 * and hvpfns_to_add are in units of Hyper-V size
			 * pages. Handling the PAGE_SIZE != HV_HYP_PAGE_SIZE
			 * हाल also handles values of sgl->offset that are
			 * larger than PAGE_SIZE. Such offsets are handled
			 * even on other than the first sgl entry, provided
			 * they are a multiple of PAGE_SIZE.
			 */
			hvpgoff = HVPFN_DOWN(sgl->offset);
			hvpfn = page_to_hvpfn(sg_page(sgl)) + hvpgoff;
			hvpfns_to_add =	HVPFN_UP(sgl->offset + sgl->length) -
						hvpgoff;

			/*
			 * Fill the next portion of the PFN array with
			 * sequential Hyper-V PFNs क्रम the continguous physical
			 * memory described by the sgl entry. The end of the
			 * last sgl should be reached at the same समय that
			 * the PFN array is filled.
			 */
			जबतक (hvpfns_to_add--)
				payload->range.pfn_array[i++] =	hvpfn++;
		पूर्ण
	पूर्ण

	cmd_request->payload = payload;
	cmd_request->payload_sz = payload_sz;

	/* Invokes the vsc to start an IO */
	ret = storvsc_करो_io(dev, cmd_request, get_cpu());
	put_cpu();

	अगर (ret == -EAGAIN) अणु
		अगर (payload_sz > माप(cmd_request->mpb))
			kमुक्त(payload);
		/* no more space */
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा scsi_driver = अणु
	.module	=		THIS_MODULE,
	.name =			"storvsc_host_t",
	.cmd_size =             माप(काष्ठा storvsc_cmd_request),
	.bios_param =		storvsc_get_chs,
	.queuecommand =		storvsc_queuecommand,
	.eh_host_reset_handler =	storvsc_host_reset_handler,
	.proc_name =		"storvsc_host",
	.eh_समयd_out =		storvsc_eh_समयd_out,
	.slave_alloc =		storvsc_device_alloc,
	.slave_configure =	storvsc_device_configure,
	.cmd_per_lun =		2048,
	.this_id =		-1,
	/* Ensure there are no gaps in presented sgls */
	.virt_boundary_mask =	PAGE_SIZE-1,
	.no_ग_लिखो_same =	1,
	.track_queue_depth =	1,
	.change_queue_depth =	storvsc_change_queue_depth,
पूर्ण;

क्रमागत अणु
	SCSI_GUID,
	IDE_GUID,
	SFC_GUID,
पूर्ण;

अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	/* SCSI guid */
	अणु HV_SCSI_GUID,
	  .driver_data = SCSI_GUID
	पूर्ण,
	/* IDE guid */
	अणु HV_IDE_GUID,
	  .driver_data = IDE_GUID
	पूर्ण,
	/* Fibre Channel GUID */
	अणु
	  HV_SYNTHFC_GUID,
	  .driver_data = SFC_GUID
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vmbus, id_table);

अटल स्थिर काष्ठा अणु guid_t guid; पूर्ण fc_guid = अणु HV_SYNTHFC_GUID पूर्ण;

अटल bool hv_dev_is_fc(काष्ठा hv_device *hv_dev)
अणु
	वापस guid_equal(&fc_guid.guid, &hv_dev->dev_type);
पूर्ण

अटल पूर्णांक storvsc_probe(काष्ठा hv_device *device,
			स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	पूर्णांक ret;
	पूर्णांक num_cpus = num_online_cpus();
	पूर्णांक num_present_cpus = num_present_cpus();
	काष्ठा Scsi_Host *host;
	काष्ठा hv_host_device *host_dev;
	bool dev_is_ide = ((dev_id->driver_data == IDE_GUID) ? true : false);
	bool is_fc = ((dev_id->driver_data == SFC_GUID) ? true : false);
	पूर्णांक target = 0;
	काष्ठा storvsc_device *stor_device;
	पूर्णांक max_luns_per_target;
	पूर्णांक max_tarमाला_लो;
	पूर्णांक max_channels;
	पूर्णांक max_sub_channels = 0;

	/*
	 * Based on the winकरोws host we are running on,
	 * set state to properly communicate with the host.
	 */

	अगर (vmbus_proto_version < VERSION_WIN8) अणु
		max_luns_per_target = STORVSC_IDE_MAX_LUNS_PER_TARGET;
		max_tarमाला_लो = STORVSC_IDE_MAX_TARGETS;
		max_channels = STORVSC_IDE_MAX_CHANNELS;
	पूर्ण अन्यथा अणु
		max_luns_per_target = STORVSC_MAX_LUNS_PER_TARGET;
		max_tarमाला_लो = STORVSC_MAX_TARGETS;
		max_channels = STORVSC_MAX_CHANNELS;
		/*
		 * On Winकरोws8 and above, we support sub-channels क्रम storage
		 * on SCSI and FC controllers.
		 * The number of sub-channels offerred is based on the number of
		 * VCPUs in the guest.
		 */
		अगर (!dev_is_ide)
			max_sub_channels =
				(num_cpus - 1) / storvsc_vcpus_per_sub_channel;
	पूर्ण

	scsi_driver.can_queue = max_outstanding_req_per_channel *
				(max_sub_channels + 1) *
				(100 - ring_avail_percent_lowater) / 100;

	host = scsi_host_alloc(&scsi_driver,
			       माप(काष्ठा hv_host_device));
	अगर (!host)
		वापस -ENOMEM;

	host_dev = shost_priv(host);
	स_रखो(host_dev, 0, माप(काष्ठा hv_host_device));

	host_dev->port = host->host_no;
	host_dev->dev = device;
	host_dev->host = host;


	stor_device = kzalloc(माप(काष्ठा storvsc_device), GFP_KERNEL);
	अगर (!stor_device) अणु
		ret = -ENOMEM;
		जाओ err_out0;
	पूर्ण

	stor_device->destroy = false;
	init_रुकोqueue_head(&stor_device->रुकोing_to_drain);
	stor_device->device = device;
	stor_device->host = host;
	stor_device->vmscsi_size_delta = माप(काष्ठा vmscsi_win8_extension);
	spin_lock_init(&stor_device->lock);
	hv_set_drvdata(device, stor_device);

	stor_device->port_number = host->host_no;
	ret = storvsc_connect_to_vsp(device, storvsc_ringbuffer_size, is_fc);
	अगर (ret)
		जाओ err_out1;

	host_dev->path = stor_device->path_id;
	host_dev->target = stor_device->target_id;

	चयन (dev_id->driver_data) अणु
	हाल SFC_GUID:
		host->max_lun = STORVSC_FC_MAX_LUNS_PER_TARGET;
		host->max_id = STORVSC_FC_MAX_TARGETS;
		host->max_channel = STORVSC_FC_MAX_CHANNELS - 1;
#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
		host->transportt = fc_transport_ढाँचा;
#पूर्ण_अगर
		अवरोध;

	हाल SCSI_GUID:
		host->max_lun = max_luns_per_target;
		host->max_id = max_tarमाला_लो;
		host->max_channel = max_channels - 1;
		अवरोध;

	शेष:
		host->max_lun = STORVSC_IDE_MAX_LUNS_PER_TARGET;
		host->max_id = STORVSC_IDE_MAX_TARGETS;
		host->max_channel = STORVSC_IDE_MAX_CHANNELS - 1;
		अवरोध;
	पूर्ण
	/* max cmd length */
	host->max_cmd_len = STORVSC_MAX_CMD_LEN;

	/*
	 * set the table size based on the info we got
	 * from the host.
	 */
	host->sg_tablesize = (stor_device->max_transfer_bytes >> PAGE_SHIFT);
	/*
	 * For non-IDE disks, the host supports multiple channels.
	 * Set the number of HW queues we are supporting.
	 */
	अगर (!dev_is_ide) अणु
		अगर (storvsc_max_hw_queues > num_present_cpus) अणु
			storvsc_max_hw_queues = 0;
			storvsc_log(device, STORVSC_LOGGING_WARN,
				"Resetting invalid storvsc_max_hw_queues value to default.\n");
		पूर्ण
		अगर (storvsc_max_hw_queues)
			host->nr_hw_queues = storvsc_max_hw_queues;
		अन्यथा
			host->nr_hw_queues = num_present_cpus;
	पूर्ण

	/*
	 * Set the error handler work queue.
	 */
	host_dev->handle_error_wq =
			alloc_ordered_workqueue("storvsc_error_wq_%d",
						WQ_MEM_RECLAIM,
						host->host_no);
	अगर (!host_dev->handle_error_wq) अणु
		ret = -ENOMEM;
		जाओ err_out2;
	पूर्ण
	INIT_WORK(&host_dev->host_scan_work, storvsc_host_scan);
	/* Register the HBA and start the scsi bus scan */
	ret = scsi_add_host(host, &device->device);
	अगर (ret != 0)
		जाओ err_out3;

	अगर (!dev_is_ide) अणु
		scsi_scan_host(host);
	पूर्ण अन्यथा अणु
		target = (device->dev_instance.b[5] << 8 |
			 device->dev_instance.b[4]);
		ret = scsi_add_device(host, 0, target, 0);
		अगर (ret)
			जाओ err_out4;
	पूर्ण
#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	अगर (host->transportt == fc_transport_ढाँचा) अणु
		काष्ठा fc_rport_identअगरiers ids = अणु
			.roles = FC_PORT_ROLE_FCP_DUMMY_INITIATOR,
		पूर्ण;

		fc_host_node_name(host) = stor_device->node_name;
		fc_host_port_name(host) = stor_device->port_name;
		stor_device->rport = fc_remote_port_add(host, 0, &ids);
		अगर (!stor_device->rport) अणु
			ret = -ENOMEM;
			जाओ err_out4;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;

err_out4:
	scsi_हटाओ_host(host);

err_out3:
	destroy_workqueue(host_dev->handle_error_wq);

err_out2:
	/*
	 * Once we have connected with the host, we would need to
	 * to invoke storvsc_dev_हटाओ() to rollback this state and
	 * this call also मुक्तs up the stor_device; hence the jump around
	 * err_out1 label.
	 */
	storvsc_dev_हटाओ(device);
	जाओ err_out0;

err_out1:
	kमुक्त(stor_device->stor_chns);
	kमुक्त(stor_device);

err_out0:
	scsi_host_put(host);
	वापस ret;
पूर्ण

/* Change a scsi target's queue depth */
अटल पूर्णांक storvsc_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक queue_depth)
अणु
	अगर (queue_depth > scsi_driver.can_queue)
		queue_depth = scsi_driver.can_queue;

	वापस scsi_change_queue_depth(sdev, queue_depth);
पूर्ण

अटल पूर्णांक storvsc_हटाओ(काष्ठा hv_device *dev)
अणु
	काष्ठा storvsc_device *stor_device = hv_get_drvdata(dev);
	काष्ठा Scsi_Host *host = stor_device->host;
	काष्ठा hv_host_device *host_dev = shost_priv(host);

#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	अगर (host->transportt == fc_transport_ढाँचा) अणु
		fc_remote_port_delete(stor_device->rport);
		fc_हटाओ_host(host);
	पूर्ण
#पूर्ण_अगर
	destroy_workqueue(host_dev->handle_error_wq);
	scsi_हटाओ_host(host);
	storvsc_dev_हटाओ(dev);
	scsi_host_put(host);

	वापस 0;
पूर्ण

अटल पूर्णांक storvsc_suspend(काष्ठा hv_device *hv_dev)
अणु
	काष्ठा storvsc_device *stor_device = hv_get_drvdata(hv_dev);
	काष्ठा Scsi_Host *host = stor_device->host;
	काष्ठा hv_host_device *host_dev = shost_priv(host);

	storvsc_रुको_to_drain(stor_device);

	drain_workqueue(host_dev->handle_error_wq);

	vmbus_बंद(hv_dev->channel);

	kमुक्त(stor_device->stor_chns);
	stor_device->stor_chns = शून्य;

	cpumask_clear(&stor_device->alloced_cpus);

	वापस 0;
पूर्ण

अटल पूर्णांक storvsc_resume(काष्ठा hv_device *hv_dev)
अणु
	पूर्णांक ret;

	ret = storvsc_connect_to_vsp(hv_dev, storvsc_ringbuffer_size,
				     hv_dev_is_fc(hv_dev));
	वापस ret;
पूर्ण

अटल काष्ठा hv_driver storvsc_drv = अणु
	.name = KBUILD_MODNAME,
	.id_table = id_table,
	.probe = storvsc_probe,
	.हटाओ = storvsc_हटाओ,
	.suspend = storvsc_suspend,
	.resume = storvsc_resume,
	.driver = अणु
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
अटल काष्ठा fc_function_ढाँचा fc_transport_functions = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init storvsc_drv_init(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * Divide the ring buffer data size (which is 1 page less
	 * than the ring buffer size since that page is reserved क्रम
	 * the ring buffer indices) by the max request size (which is
	 * vmbus_channel_packet_multipage_buffer + काष्ठा vstor_packet + u64)
	 *
	 * The computation underestimates max_outstanding_req_per_channel
	 * क्रम Win7 and older hosts because it करोes not take पूर्णांकo account
	 * the vmscsi_size_delta correction to the max request size.
	 */
	max_outstanding_req_per_channel =
		((storvsc_ringbuffer_size - PAGE_SIZE) /
		ALIGN(MAX_MULTIPAGE_BUFFER_PACKET +
		माप(काष्ठा vstor_packet) + माप(u64),
		माप(u64)));

#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	fc_transport_ढाँचा = fc_attach_transport(&fc_transport_functions);
	अगर (!fc_transport_ढाँचा)
		वापस -ENODEV;
#पूर्ण_अगर

	ret = vmbus_driver_रेजिस्टर(&storvsc_drv);

#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	अगर (ret)
		fc_release_transport(fc_transport_ढाँचा);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल व्योम __निकास storvsc_drv_निकास(व्योम)
अणु
	vmbus_driver_unरेजिस्टर(&storvsc_drv);
#अगर IS_ENABLED(CONFIG_SCSI_FC_ATTRS)
	fc_release_transport(fc_transport_ढाँचा);
#पूर्ण_अगर
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Microsoft Hyper-V virtual storage driver");
module_init(storvsc_drv_init);
module_निकास(storvsc_drv_निकास);
