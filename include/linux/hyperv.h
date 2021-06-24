<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (c) 2011, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 *   K. Y. Srinivasan <kys@microsoft.com>
 */

#अगर_अघोषित _HYPERV_H
#घोषणा _HYPERV_H

#समावेश <uapi/linux/hyperv.h>

#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reciprocal_भाग.h>
#समावेश <यंत्र/hyperv-tlfs.h>

#घोषणा MAX_PAGE_BUFFER_COUNT				32
#घोषणा MAX_MULTIPAGE_BUFFER_COUNT			32 /* 128K */

#आशय pack(push, 1)

/*
 * Types क्रम GPADL, decides is how GPADL header is created.
 *
 * It करोesn't make much dअगरference between BUFFER and RING अगर PAGE_SIZE is the
 * same as HV_HYP_PAGE_SIZE.
 *
 * If PAGE_SIZE is bigger than HV_HYP_PAGE_SIZE, the headers of ring buffers
 * will be of PAGE_SIZE, however, only the first HV_HYP_PAGE will be put
 * पूर्णांकo gpadl, thereक्रमe the number क्रम HV_HYP_PAGE and the indexes of each
 * HV_HYP_PAGE will be dअगरferent between dअगरferent types of GPADL, क्रम example
 * अगर PAGE_SIZE is 64K:
 *
 * BUFFER:
 *
 * gva:    |--       64k      --|--       64k      --| ... |
 * gpa:    | 4k | 4k | ... | 4k | 4k | 4k | ... | 4k |
 * index:  0    1    2     15   16   17   18 .. 31   32 ...
 *         |    |    ...   |    |    |   ...    |   ...
 *         v    V          V    V    V          V
 * gpadl:  | 4k | 4k | ... | 4k | 4k | 4k | ... | 4k | ... |
 * index:  0    1    2 ... 15   16   17   18 .. 31   32 ...
 *
 * RING:
 *
 *         | header  |           data           | header  |     data      |
 * gva:    |-- 64k --|--       64k      --| ... |-- 64k --|-- 64k --| ... |
 * gpa:    | 4k | .. | 4k | 4k | ... | 4k | ... | 4k | .. | 4k | .. | ... |
 * index:  0    1    16   17   18    31   ...   n   n+1  n+16 ...         2n
 *         |         /    /          /          |         /               /
 *         |        /    /          /           |        /               /
 *         |       /    /   ...    /    ...     |       /      ...      /
 *         |      /    /          /             |      /               /
 *         |     /    /          /              |     /               /
 *         V    V    V          V               V    V               v
 * gpadl:  | 4k | 4k |   ...    |    ...        | 4k | 4k |  ...     |
 * index:  0    1    2   ...    16   ...       n-15 n-14 n-13  ...  2n-30
 */
क्रमागत hv_gpadl_type अणु
	HV_GPADL_BUFFER,
	HV_GPADL_RING
पूर्ण;

/* Single-page buffer */
काष्ठा hv_page_buffer अणु
	u32 len;
	u32 offset;
	u64 pfn;
पूर्ण;

/* Multiple-page buffer */
काष्ठा hv_multipage_buffer अणु
	/* Length and Offset determines the # of pfns in the array */
	u32 len;
	u32 offset;
	u64 pfn_array[MAX_MULTIPAGE_BUFFER_COUNT];
पूर्ण;

/*
 * Multiple-page buffer array; the pfn array is variable size:
 * The number of entries in the PFN array is determined by
 * "len" and "offset".
 */
काष्ठा hv_mpb_array अणु
	/* Length and Offset determines the # of pfns in the array */
	u32 len;
	u32 offset;
	u64 pfn_array[];
पूर्ण;

/* 0x18 includes the proprietary packet header */
#घोषणा MAX_PAGE_BUFFER_PACKET		(0x18 +			\
					(माप(काष्ठा hv_page_buffer) * \
					 MAX_PAGE_BUFFER_COUNT))
#घोषणा MAX_MULTIPAGE_BUFFER_PACKET	(0x18 +			\
					 माप(काष्ठा hv_multipage_buffer))


#आशय pack(pop)

काष्ठा hv_ring_buffer अणु
	/* Offset in bytes from the start of ring data below */
	u32 ग_लिखो_index;

	/* Offset in bytes from the start of ring data below */
	u32 पढ़ो_index;

	u32 पूर्णांकerrupt_mask;

	/*
	 * WS2012/Win8 and later versions of Hyper-V implement पूर्णांकerrupt
	 * driven flow management. The feature bit feat_pending_send_sz
	 * is set by the host on the host->guest ring buffer, and by the
	 * guest on the guest->host ring buffer.
	 *
	 * The meaning of the feature bit is a bit complex in that it has
	 * semantics that apply to both ring buffers.  If the guest sets
	 * the feature bit in the guest->host ring buffer, the guest is
	 * telling the host that:
	 * 1) It will set the pending_send_sz field in the guest->host ring
	 *    buffer when it is रुकोing क्रम space to become available, and
	 * 2) It will पढ़ो the pending_send_sz field in the host->guest
	 *    ring buffer and पूर्णांकerrupt the host when it मुक्तs enough space
	 *
	 * Similarly, अगर the host sets the feature bit in the host->guest
	 * ring buffer, the host is telling the guest that:
	 * 1) It will set the pending_send_sz field in the host->guest ring
	 *    buffer when it is रुकोing क्रम space to become available, and
	 * 2) It will पढ़ो the pending_send_sz field in the guest->host
	 *    ring buffer and पूर्णांकerrupt the guest when it मुक्तs enough space
	 *
	 * If either the guest or host करोes not set the feature bit that it
	 * owns, that guest or host must करो polling अगर it encounters a full
	 * ring buffer, and not संकेत the other end with an पूर्णांकerrupt.
	 */
	u32 pending_send_sz;
	u32 reserved1[12];
	जोड़ अणु
		काष्ठा अणु
			u32 feat_pending_send_sz:1;
		पूर्ण;
		u32 value;
	पूर्ण feature_bits;

	/* Pad it to PAGE_SIZE so that data starts on page boundary */
	u8	reserved2[PAGE_SIZE - 68];

	/*
	 * Ring data starts here + RingDataStartOffset
	 * !!! DO NOT place any fields below this !!!
	 */
	u8 buffer[];
पूर्ण __packed;

/* Calculate the proper size of a ringbuffer, it must be page-aligned */
#घोषणा VMBUS_RING_SIZE(payload_sz) PAGE_ALIGN(माप(काष्ठा hv_ring_buffer) + \
					       (payload_sz))

काष्ठा hv_ring_buffer_info अणु
	काष्ठा hv_ring_buffer *ring_buffer;
	u32 ring_size;			/* Include the shared header */
	काष्ठा reciprocal_value ring_size_भाग10_reciprocal;
	spinlock_t ring_lock;

	u32 ring_datasize;		/* < ring_size */
	u32 priv_पढ़ो_index;
	/*
	 * The ring buffer mutex lock. This lock prevents the ring buffer from
	 * being मुक्तd जबतक the ring buffer is being accessed.
	 */
	काष्ठा mutex ring_buffer_mutex;
पूर्ण;


अटल अंतरभूत u32 hv_get_bytes_to_पढ़ो(स्थिर काष्ठा hv_ring_buffer_info *rbi)
अणु
	u32 पढ़ो_loc, ग_लिखो_loc, dsize, पढ़ो;

	dsize = rbi->ring_datasize;
	पढ़ो_loc = rbi->ring_buffer->पढ़ो_index;
	ग_लिखो_loc = READ_ONCE(rbi->ring_buffer->ग_लिखो_index);

	पढ़ो = ग_लिखो_loc >= पढ़ो_loc ? (ग_लिखो_loc - पढ़ो_loc) :
		(dsize - पढ़ो_loc) + ग_लिखो_loc;

	वापस पढ़ो;
पूर्ण

अटल अंतरभूत u32 hv_get_bytes_to_ग_लिखो(स्थिर काष्ठा hv_ring_buffer_info *rbi)
अणु
	u32 पढ़ो_loc, ग_लिखो_loc, dsize, ग_लिखो;

	dsize = rbi->ring_datasize;
	पढ़ो_loc = READ_ONCE(rbi->ring_buffer->पढ़ो_index);
	ग_लिखो_loc = rbi->ring_buffer->ग_लिखो_index;

	ग_लिखो = ग_लिखो_loc >= पढ़ो_loc ? dsize - (ग_लिखो_loc - पढ़ो_loc) :
		पढ़ो_loc - ग_लिखो_loc;
	वापस ग_लिखो;
पूर्ण

अटल अंतरभूत u32 hv_get_avail_to_ग_लिखो_percent(
		स्थिर काष्ठा hv_ring_buffer_info *rbi)
अणु
	u32 avail_ग_लिखो = hv_get_bytes_to_ग_लिखो(rbi);

	वापस reciprocal_भागide(
			(avail_ग_लिखो  << 3) + (avail_ग_लिखो << 1),
			rbi->ring_size_भाग10_reciprocal);
पूर्ण

/*
 * VMBUS version is 32 bit entity broken up पूर्णांकo
 * two 16 bit quantities: major_number. minor_number.
 *
 * 0 . 13 (Winकरोws Server 2008)
 * 1 . 1  (Winकरोws 7)
 * 2 . 4  (Winकरोws 8)
 * 3 . 0  (Winकरोws 8 R2)
 * 4 . 0  (Winकरोws 10)
 * 4 . 1  (Winकरोws 10 RS3)
 * 5 . 0  (Newer Winकरोws 10)
 * 5 . 1  (Winकरोws 10 RS4)
 * 5 . 2  (Winकरोws Server 2019, RS5)
 * 5 . 3  (Winकरोws Server 2022)
 */

#घोषणा VERSION_WS2008  ((0 << 16) | (13))
#घोषणा VERSION_WIN7    ((1 << 16) | (1))
#घोषणा VERSION_WIN8    ((2 << 16) | (4))
#घोषणा VERSION_WIN8_1    ((3 << 16) | (0))
#घोषणा VERSION_WIN10 ((4 << 16) | (0))
#घोषणा VERSION_WIN10_V4_1 ((4 << 16) | (1))
#घोषणा VERSION_WIN10_V5 ((5 << 16) | (0))
#घोषणा VERSION_WIN10_V5_1 ((5 << 16) | (1))
#घोषणा VERSION_WIN10_V5_2 ((5 << 16) | (2))
#घोषणा VERSION_WIN10_V5_3 ((5 << 16) | (3))

/* Make maximum size of pipe payload of 16K */
#घोषणा MAX_PIPE_DATA_PAYLOAD		(माप(u8) * 16384)

/* Define PipeMode values. */
#घोषणा VMBUS_PIPE_TYPE_BYTE		0x00000000
#घोषणा VMBUS_PIPE_TYPE_MESSAGE		0x00000004

/* The size of the user defined data buffer क्रम non-pipe offers. */
#घोषणा MAX_USER_DEFINED_BYTES		120

/* The size of the user defined data buffer क्रम pipe offers. */
#घोषणा MAX_PIPE_USER_DEFINED_BYTES	116

/*
 * At the center of the Channel Management library is the Channel Offer. This
 * काष्ठा contains the fundamental inक्रमmation about an offer.
 */
काष्ठा vmbus_channel_offer अणु
	guid_t अगर_type;
	guid_t अगर_instance;

	/*
	 * These two fields are not currently used.
	 */
	u64 reserved1;
	u64 reserved2;

	u16 chn_flags;
	u16 mmio_megabytes;		/* in bytes * 1024 * 1024 */

	जोड़ अणु
		/* Non-pipes: The user has MAX_USER_DEFINED_BYTES bytes. */
		काष्ठा अणु
			अचिन्हित अक्षर user_def[MAX_USER_DEFINED_BYTES];
		पूर्ण std;

		/*
		 * Pipes:
		 * The following काष्ठाure is an पूर्णांकegrated pipe protocol, which
		 * is implemented on top of standard user-defined data. Pipe
		 * clients have MAX_PIPE_USER_DEFINED_BYTES left क्रम their own
		 * use.
		 */
		काष्ठा अणु
			u32  pipe_mode;
			अचिन्हित अक्षर user_def[MAX_PIPE_USER_DEFINED_BYTES];
		पूर्ण pipe;
	पूर्ण u;
	/*
	 * The sub_channel_index is defined in Win8: a value of zero means a
	 * primary channel and a value of non-zero means a sub-channel.
	 *
	 * Beक्रमe Win8, the field is reserved, meaning it's always zero.
	 */
	u16 sub_channel_index;
	u16 reserved3;
पूर्ण __packed;

/* Server Flags */
#घोषणा VMBUS_CHANNEL_ENUMERATE_DEVICE_INTERFACE	1
#घोषणा VMBUS_CHANNEL_SERVER_SUPPORTS_TRANSFER_PAGES	2
#घोषणा VMBUS_CHANNEL_SERVER_SUPPORTS_GPADLS		4
#घोषणा VMBUS_CHANNEL_NAMED_PIPE_MODE			0x10
#घोषणा VMBUS_CHANNEL_LOOPBACK_OFFER			0x100
#घोषणा VMBUS_CHANNEL_PARENT_OFFER			0x200
#घोषणा VMBUS_CHANNEL_REQUEST_MONITORED_NOTIFICATION	0x400
#घोषणा VMBUS_CHANNEL_TLNPI_PROVIDER_OFFER		0x2000

काष्ठा vmpacket_descriptor अणु
	u16 type;
	u16 offset8;
	u16 len8;
	u16 flags;
	u64 trans_id;
पूर्ण __packed;

काष्ठा vmpacket_header अणु
	u32 prev_pkt_start_offset;
	काष्ठा vmpacket_descriptor descriptor;
पूर्ण __packed;

काष्ठा vmtransfer_page_range अणु
	u32 byte_count;
	u32 byte_offset;
पूर्ण __packed;

काष्ठा vmtransfer_page_packet_header अणु
	काष्ठा vmpacket_descriptor d;
	u16 xfer_pageset_id;
	u8  sender_owns_set;
	u8 reserved;
	u32 range_cnt;
	काष्ठा vmtransfer_page_range ranges[1];
पूर्ण __packed;

काष्ठा vmgpadl_packet_header अणु
	काष्ठा vmpacket_descriptor d;
	u32 gpadl;
	u32 reserved;
पूर्ण __packed;

काष्ठा vmadd_हटाओ_transfer_page_set अणु
	काष्ठा vmpacket_descriptor d;
	u32 gpadl;
	u16 xfer_pageset_id;
	u16 reserved;
पूर्ण __packed;

/*
 * This काष्ठाure defines a range in guest physical space that can be made to
 * look भवly contiguous.
 */
काष्ठा gpa_range अणु
	u32 byte_count;
	u32 byte_offset;
	u64 pfn_array[];
पूर्ण;

/*
 * This is the क्रमmat क्रम an Establish Gpadl packet, which contains a handle by
 * which this GPADL will be known and a set of GPA ranges associated with it.
 * This can be converted to a MDL by the guest OS.  If there are multiple GPA
 * ranges, then the resulting MDL will be "chained," representing multiple VA
 * ranges.
 */
काष्ठा vmestablish_gpadl अणु
	काष्ठा vmpacket_descriptor d;
	u32 gpadl;
	u32 range_cnt;
	काष्ठा gpa_range range[1];
पूर्ण __packed;

/*
 * This is the क्रमmat क्रम a Tearकरोwn Gpadl packet, which indicates that the
 * GPADL handle in the Establish Gpadl packet will never be referenced again.
 */
काष्ठा vmtearकरोwn_gpadl अणु
	काष्ठा vmpacket_descriptor d;
	u32 gpadl;
	u32 reserved;	/* क्रम alignment to a 8-byte boundary */
पूर्ण __packed;

/*
 * This is the क्रमmat क्रम a GPA-Direct packet, which contains a set of GPA
 * ranges, in addition to commands and/or data.
 */
काष्ठा vmdata_gpa_direct अणु
	काष्ठा vmpacket_descriptor d;
	u32 reserved;
	u32 range_cnt;
	काष्ठा gpa_range range[1];
पूर्ण __packed;

/* This is the क्रमmat क्रम a Additional Data Packet. */
काष्ठा vmadditional_data अणु
	काष्ठा vmpacket_descriptor d;
	u64 total_bytes;
	u32 offset;
	u32 byte_cnt;
	अचिन्हित अक्षर data[1];
पूर्ण __packed;

जोड़ vmpacket_largest_possible_header अणु
	काष्ठा vmpacket_descriptor simple_hdr;
	काष्ठा vmtransfer_page_packet_header xfer_page_hdr;
	काष्ठा vmgpadl_packet_header gpadl_hdr;
	काष्ठा vmadd_हटाओ_transfer_page_set add_rm_xfer_page_hdr;
	काष्ठा vmestablish_gpadl establish_gpadl_hdr;
	काष्ठा vmtearकरोwn_gpadl tearकरोwn_gpadl_hdr;
	काष्ठा vmdata_gpa_direct data_gpa_direct_hdr;
पूर्ण;

#घोषणा VMPACKET_DATA_START_ADDRESS(__packet)	\
	(व्योम *)(((अचिन्हित अक्षर *)__packet) +	\
	 ((काष्ठा vmpacket_descriptor)__packet)->offset8 * 8)

#घोषणा VMPACKET_DATA_LENGTH(__packet)		\
	((((काष्ठा vmpacket_descriptor)__packet)->len8 -	\
	  ((काष्ठा vmpacket_descriptor)__packet)->offset8) * 8)

#घोषणा VMPACKET_TRANSFER_MODE(__packet)	\
	(((काष्ठा IMPACT)__packet)->type)

क्रमागत vmbus_packet_type अणु
	VM_PKT_INVALID				= 0x0,
	VM_PKT_SYNCH				= 0x1,
	VM_PKT_ADD_XFER_PAGESET			= 0x2,
	VM_PKT_RM_XFER_PAGESET			= 0x3,
	VM_PKT_ESTABLISH_GPADL			= 0x4,
	VM_PKT_TEARDOWN_GPADL			= 0x5,
	VM_PKT_DATA_INBAND			= 0x6,
	VM_PKT_DATA_USING_XFER_PAGES		= 0x7,
	VM_PKT_DATA_USING_GPADL			= 0x8,
	VM_PKT_DATA_USING_GPA_सूचीECT		= 0x9,
	VM_PKT_CANCEL_REQUEST			= 0xa,
	VM_PKT_COMP				= 0xb,
	VM_PKT_DATA_USING_ADDITIONAL_PKT	= 0xc,
	VM_PKT_ADDITIONAL_DATA			= 0xd
पूर्ण;

#घोषणा VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED	1


/* Version 1 messages */
क्रमागत vmbus_channel_message_type अणु
	CHANNELMSG_INVALID			=  0,
	CHANNELMSG_OFFERCHANNEL		=  1,
	CHANNELMSG_RESCIND_CHANNELOFFER	=  2,
	CHANNELMSG_REQUESTOFFERS		=  3,
	CHANNELMSG_ALLOFFERS_DELIVERED	=  4,
	CHANNELMSG_OPENCHANNEL		=  5,
	CHANNELMSG_OPENCHANNEL_RESULT		=  6,
	CHANNELMSG_CLOSECHANNEL		=  7,
	CHANNELMSG_GPADL_HEADER		=  8,
	CHANNELMSG_GPADL_BODY			=  9,
	CHANNELMSG_GPADL_CREATED		= 10,
	CHANNELMSG_GPADL_TEARDOWN		= 11,
	CHANNELMSG_GPADL_TORNDOWN		= 12,
	CHANNELMSG_RELID_RELEASED		= 13,
	CHANNELMSG_INITIATE_CONTACT		= 14,
	CHANNELMSG_VERSION_RESPONSE		= 15,
	CHANNELMSG_UNLOAD			= 16,
	CHANNELMSG_UNLOAD_RESPONSE		= 17,
	CHANNELMSG_18				= 18,
	CHANNELMSG_19				= 19,
	CHANNELMSG_20				= 20,
	CHANNELMSG_TL_CONNECT_REQUEST		= 21,
	CHANNELMSG_MODIFYCHANNEL		= 22,
	CHANNELMSG_TL_CONNECT_RESULT		= 23,
	CHANNELMSG_MODIFYCHANNEL_RESPONSE	= 24,
	CHANNELMSG_COUNT
पूर्ण;

/* Hyper-V supports about 2048 channels, and the RELIDs start with 1. */
#घोषणा INVALID_RELID	U32_MAX

काष्ठा vmbus_channel_message_header अणु
	क्रमागत vmbus_channel_message_type msgtype;
	u32 padding;
पूर्ण __packed;

/* Query VMBus Version parameters */
काष्ठा vmbus_channel_query_vmbus_version अणु
	काष्ठा vmbus_channel_message_header header;
	u32 version;
पूर्ण __packed;

/* VMBus Version Supported parameters */
काष्ठा vmbus_channel_version_supported अणु
	काष्ठा vmbus_channel_message_header header;
	u8 version_supported;
पूर्ण __packed;

/* Offer Channel parameters */
काष्ठा vmbus_channel_offer_channel अणु
	काष्ठा vmbus_channel_message_header header;
	काष्ठा vmbus_channel_offer offer;
	u32 child_relid;
	u8 monitorid;
	/*
	 * win7 and beyond splits this field पूर्णांकo a bit field.
	 */
	u8 monitor_allocated:1;
	u8 reserved:7;
	/*
	 * These are new fields added in win7 and later.
	 * Do not access these fields without checking the
	 * negotiated protocol.
	 *
	 * If "is_dedicated_interrupt" is set, we must not set the
	 * associated bit in the channel biपंचांगap जबतक sending the
	 * पूर्णांकerrupt to the host.
	 *
	 * connection_id is to be used in संकेतing the host.
	 */
	u16 is_dedicated_पूर्णांकerrupt:1;
	u16 reserved1:15;
	u32 connection_id;
पूर्ण __packed;

/* Rescind Offer parameters */
काष्ठा vmbus_channel_rescind_offer अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
पूर्ण __packed;

अटल अंतरभूत u32
hv_ringbuffer_pending_size(स्थिर काष्ठा hv_ring_buffer_info *rbi)
अणु
	वापस rbi->ring_buffer->pending_send_sz;
पूर्ण

/*
 * Request Offer -- no parameters, SynIC message contains the partition ID
 * Set Snoop -- no parameters, SynIC message contains the partition ID
 * Clear Snoop -- no parameters, SynIC message contains the partition ID
 * All Offers Delivered -- no parameters, SynIC message contains the partition
 *		           ID
 * Flush Client -- no parameters, SynIC message contains the partition ID
 */

/* Open Channel parameters */
काष्ठा vmbus_channel_खोलो_channel अणु
	काष्ठा vmbus_channel_message_header header;

	/* Identअगरies the specअगरic VMBus channel that is being खोलोed. */
	u32 child_relid;

	/* ID making a particular खोलो request at a channel offer unique. */
	u32 खोलोid;

	/* GPADL क्रम the channel's ring buffer. */
	u32 ringbuffer_gpadlhandle;

	/*
	 * Starting with win8, this field will be used to specअगरy
	 * the target भव processor on which to deliver the पूर्णांकerrupt क्रम
	 * the host to guest communication.
	 * Prior to win8, incoming channel पूर्णांकerrupts would only
	 * be delivered on cpu 0. Setting this value to 0 would
	 * preserve the earlier behavior.
	 */
	u32 target_vp;

	/*
	 * The upstream ring buffer begins at offset zero in the memory
	 * described by RingBufferGpadlHandle. The करोwnstream ring buffer
	 * follows it at this offset (in pages).
	 */
	u32 करोwnstream_ringbuffer_pageoffset;

	/* User-specअगरic data to be passed aदीर्घ to the server endpoपूर्णांक. */
	अचिन्हित अक्षर userdata[MAX_USER_DEFINED_BYTES];
पूर्ण __packed;

/* Open Channel Result parameters */
काष्ठा vmbus_channel_खोलो_result अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
	u32 खोलोid;
	u32 status;
पूर्ण __packed;

/* Modअगरy Channel Result parameters */
काष्ठा vmbus_channel_modअगरychannel_response अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
	u32 status;
पूर्ण __packed;

/* Close channel parameters; */
काष्ठा vmbus_channel_बंद_channel अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
पूर्ण __packed;

/* Channel Message GPADL */
#घोषणा GPADL_TYPE_RING_BUFFER		1
#घोषणा GPADL_TYPE_SERVER_SAVE_AREA	2
#घोषणा GPADL_TYPE_TRANSACTION		8

/*
 * The number of PFNs in a GPADL message is defined by the number of
 * pages that would be spanned by ByteCount and ByteOffset.  If the
 * implied number of PFNs won't fit in this packet, there will be a
 * follow-up packet that contains more.
 */
काष्ठा vmbus_channel_gpadl_header अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
	u32 gpadl;
	u16 range_buflen;
	u16 rangecount;
	काष्ठा gpa_range range[];
पूर्ण __packed;

/* This is the followup packet that contains more PFNs. */
काष्ठा vmbus_channel_gpadl_body अणु
	काष्ठा vmbus_channel_message_header header;
	u32 msgnumber;
	u32 gpadl;
	u64 pfn[];
पूर्ण __packed;

काष्ठा vmbus_channel_gpadl_created अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
	u32 gpadl;
	u32 creation_status;
पूर्ण __packed;

काष्ठा vmbus_channel_gpadl_tearकरोwn अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
	u32 gpadl;
पूर्ण __packed;

काष्ठा vmbus_channel_gpadl_tornकरोwn अणु
	काष्ठा vmbus_channel_message_header header;
	u32 gpadl;
पूर्ण __packed;

काष्ठा vmbus_channel_relid_released अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
पूर्ण __packed;

काष्ठा vmbus_channel_initiate_contact अणु
	काष्ठा vmbus_channel_message_header header;
	u32 vmbus_version_requested;
	u32 target_vcpu; /* The VCPU the host should respond to */
	जोड़ अणु
		u64 पूर्णांकerrupt_page;
		काष्ठा अणु
			u8	msg_sपूर्णांक;
			u8	padding1[3];
			u32	padding2;
		पूर्ण;
	पूर्ण;
	u64 monitor_page1;
	u64 monitor_page2;
पूर्ण __packed;

/* Hyper-V socket: guest's connect()-ing to host */
काष्ठा vmbus_channel_tl_connect_request अणु
	काष्ठा vmbus_channel_message_header header;
	guid_t guest_endpoपूर्णांक_id;
	guid_t host_service_id;
पूर्ण __packed;

/* Modअगरy Channel parameters, cf. vmbus_send_modअगरychannel() */
काष्ठा vmbus_channel_modअगरychannel अणु
	काष्ठा vmbus_channel_message_header header;
	u32 child_relid;
	u32 target_vp;
पूर्ण __packed;

काष्ठा vmbus_channel_version_response अणु
	काष्ठा vmbus_channel_message_header header;
	u8 version_supported;

	u8 connection_state;
	u16 padding;

	/*
	 * On new hosts that support VMBus protocol 5.0, we must use
	 * VMBUS_MESSAGE_CONNECTION_ID_4 क्रम the Initiate Contact Message,
	 * and क्रम subsequent messages, we must use the Message Connection ID
	 * field in the host-वापसed Version Response Message.
	 *
	 * On old hosts, we should always use VMBUS_MESSAGE_CONNECTION_ID (1).
	 */
	u32 msg_conn_id;
पूर्ण __packed;

क्रमागत vmbus_channel_state अणु
	CHANNEL_OFFER_STATE,
	CHANNEL_OPENING_STATE,
	CHANNEL_OPEN_STATE,
	CHANNEL_OPENED_STATE,
पूर्ण;

/*
 * Represents each channel msg on the vmbus connection This is a
 * variable-size data काष्ठाure depending on the msg type itself
 */
काष्ठा vmbus_channel_msginfo अणु
	/* Bookkeeping stuff */
	काष्ठा list_head msglistentry;

	/* So far, this is only used to handle gpadl body message */
	काष्ठा list_head submsglist;

	/* Synchronize the request/response अगर needed */
	काष्ठा completion  रुकोevent;
	काष्ठा vmbus_channel *रुकोing_channel;
	जोड़ अणु
		काष्ठा vmbus_channel_version_supported version_supported;
		काष्ठा vmbus_channel_खोलो_result खोलो_result;
		काष्ठा vmbus_channel_gpadl_tornकरोwn gpadl_tornकरोwn;
		काष्ठा vmbus_channel_gpadl_created gpadl_created;
		काष्ठा vmbus_channel_version_response version_response;
		काष्ठा vmbus_channel_modअगरychannel_response modअगरy_response;
	पूर्ण response;

	u32 msgsize;
	/*
	 * The channel message that goes out on the "wire".
	 * It will contain at minimum the VMBUS_CHANNEL_MESSAGE_HEADER header
	 */
	अचिन्हित अक्षर msg[];
पूर्ण;

काष्ठा vmbus_बंद_msg अणु
	काष्ठा vmbus_channel_msginfo info;
	काष्ठा vmbus_channel_बंद_channel msg;
पूर्ण;

/* Define connection identअगरier type. */
जोड़ hv_connection_id अणु
	u32 asu32;
	काष्ठा अणु
		u32 id:24;
		u32 reserved:8;
	पूर्ण u;
पूर्ण;

क्रमागत vmbus_device_type अणु
	HV_IDE = 0,
	HV_SCSI,
	HV_FC,
	HV_NIC,
	HV_ND,
	HV_PCIE,
	HV_FB,
	HV_KBD,
	HV_MOUSE,
	HV_KVP,
	HV_TS,
	HV_HB,
	HV_SHUTDOWN,
	HV_FCOPY,
	HV_BACKUP,
	HV_DM,
	HV_UNKNOWN,
पूर्ण;

/*
 * Provides request ids क्रम VMBus. Encapsulates guest memory
 * addresses and stores the next available slot in req_arr
 * to generate new ids in स्थिरant समय.
 */
काष्ठा vmbus_requestor अणु
	u64 *req_arr;
	अचिन्हित दीर्घ *req_biपंचांगap; /* is a given slot available? */
	u32 size;
	u64 next_request_id;
	spinlock_t req_lock; /* provides atomicity */
पूर्ण;

#घोषणा VMBUS_NO_RQSTOR U64_MAX
#घोषणा VMBUS_RQST_ERROR (U64_MAX - 1)
#घोषणा VMBUS_RQST_ID_NO_RESPONSE (U64_MAX - 2)

काष्ठा vmbus_device अणु
	u16  dev_type;
	guid_t guid;
	bool perf_device;
	bool allowed_in_isolated;
पूर्ण;

काष्ठा vmbus_channel अणु
	काष्ठा list_head listentry;

	काष्ठा hv_device *device_obj;

	क्रमागत vmbus_channel_state state;

	काष्ठा vmbus_channel_offer_channel offermsg;
	/*
	 * These are based on the OfferMsg.MonitorId.
	 * Save it here क्रम easy access.
	 */
	u8 monitor_grp;
	u8 monitor_bit;

	bool rescind; /* got rescind msg */
	bool rescind_ref; /* got rescind msg, got channel reference */
	काष्ठा completion rescind_event;

	u32 ringbuffer_gpadlhandle;

	/* Allocated memory क्रम ring buffer */
	काष्ठा page *ringbuffer_page;
	u32 ringbuffer_pagecount;
	u32 ringbuffer_send_offset;
	काष्ठा hv_ring_buffer_info outbound;	/* send to parent */
	काष्ठा hv_ring_buffer_info inbound;	/* receive from parent */

	काष्ठा vmbus_बंद_msg बंद_msg;

	/* Statistics */
	u64	पूर्णांकerrupts;	/* Host to Guest पूर्णांकerrupts */
	u64	sig_events;	/* Guest to Host events */

	/*
	 * Guest to host पूर्णांकerrupts caused by the outbound ring buffer changing
	 * from empty to not empty.
	 */
	u64 पूर्णांकr_out_empty;

	/*
	 * Indicates that a full outbound ring buffer was encountered. The flag
	 * is set to true when a full outbound ring buffer is encountered and
	 * set to false when a ग_लिखो to the outbound ring buffer is completed.
	 */
	bool out_full_flag;

	/* Channel callback's invoked in softirq context */
	काष्ठा tasklet_काष्ठा callback_event;
	व्योम (*onchannel_callback)(व्योम *context);
	व्योम *channel_callback_context;

	व्योम (*change_target_cpu_callback)(काष्ठा vmbus_channel *channel,
			u32 old, u32 new);

	/*
	 * Synchronize channel scheduling and channel removal; see the अंतरभूत
	 * comments in vmbus_chan_sched() and vmbus_reset_channel_cb().
	 */
	spinlock_t sched_lock;

	/*
	 * A channel can be marked क्रम one of three modes of पढ़ोing:
	 *   BATCHED - callback called from taslket and should पढ़ो
	 *            channel until empty. Interrupts from the host
	 *            are masked जबतक पढ़ो is in process (शेष).
	 *   सूचीECT - callback called from tasklet (softirq).
	 *   ISR - callback called in पूर्णांकerrupt context and must
	 *         invoke its own deferred processing.
	 *         Host पूर्णांकerrupts are disabled and must be re-enabled
	 *         when ring is empty.
	 */
	क्रमागत hv_callback_mode अणु
		HV_CALL_BATCHED,
		HV_CALL_सूचीECT,
		HV_CALL_ISR
	पूर्ण callback_mode;

	bool is_dedicated_पूर्णांकerrupt;
	u64 sig_event;

	/*
	 * Starting with win8, this field will be used to specअगरy the
	 * target CPU on which to deliver the पूर्णांकerrupt क्रम the host
	 * to guest communication.
	 *
	 * Prior to win8, incoming channel पूर्णांकerrupts would only be
	 * delivered on CPU 0. Setting this value to 0 would preserve
	 * the earlier behavior.
	 */
	u32 target_cpu;
	/*
	 * Support क्रम sub-channels. For high perक्रमmance devices,
	 * it will be useful to have multiple sub-channels to support
	 * a scalable communication infraकाष्ठाure with the host.
	 * The support क्रम sub-channels is implemented as an extension
	 * to the current infraकाष्ठाure.
	 * The initial offer is considered the primary channel and this
	 * offer message will indicate अगर the host supports sub-channels.
	 * The guest is मुक्त to ask क्रम sub-channels to be offered and can
	 * खोलो these sub-channels as a normal "primary" channel. However,
	 * all sub-channels will have the same type and instance guids as the
	 * primary channel. Requests sent on a given channel will result in a
	 * response on the same channel.
	 */

	/*
	 * Sub-channel creation callback. This callback will be called in
	 * process context when a sub-channel offer is received from the host.
	 * The guest can खोलो the sub-channel in the context of this callback.
	 */
	व्योम (*sc_creation_callback)(काष्ठा vmbus_channel *new_sc);

	/*
	 * Channel rescind callback. Some channels (the hvsock ones), need to
	 * रेजिस्टर a callback which is invoked in vmbus_onoffer_rescind().
	 */
	व्योम (*chn_rescind_callback)(काष्ठा vmbus_channel *channel);

	/*
	 * All Sub-channels of a primary channel are linked here.
	 */
	काष्ठा list_head sc_list;
	/*
	 * The primary channel this sub-channel beदीर्घs to.
	 * This will be शून्य क्रम the primary channel.
	 */
	काष्ठा vmbus_channel *primary_channel;
	/*
	 * Support per-channel state क्रम use by vmbus drivers.
	 */
	व्योम *per_channel_state;

	/*
	 * Defer मुक्तing channel until after all cpu's have
	 * gone through grace period.
	 */
	काष्ठा rcu_head rcu;

	/*
	 * For sysfs per-channel properties.
	 */
	काष्ठा kobject			kobj;

	/*
	 * For perक्रमmance critical channels (storage, networking
	 * etc,), Hyper-V has a mechanism to enhance the throughput
	 * at the expense of latency:
	 * When the host is to be संकेतed, we just set a bit in a shared page
	 * and this bit will be inspected by the hypervisor within a certain
	 * winकरोw and अगर the bit is set, the host will be संकेतed. The winकरोw
	 * of समय is the monitor latency - currently around 100 usecs. This
	 * mechanism improves throughput by:
	 *
	 * A) Making the host more efficient - each समय it wakes up,
	 *    potentially it will process morev number of packets. The
	 *    monitor latency allows a batch to build up.
	 * B) By deferring the hypercall to संकेत, we will also minimize
	 *    the पूर्णांकerrupts.
	 *
	 * Clearly, these optimizations improve throughput at the expense of
	 * latency. Furthermore, since the channel is shared क्रम both
	 * control and data messages, control messages currently suffer
	 * unnecessary latency adversely impacting perक्रमmance and boot
	 * समय. To fix this issue, permit tagging the channel as being
	 * in "low latency" mode. In this mode, we will bypass the monitor
	 * mechanism.
	 */
	bool low_latency;

	bool probe_करोne;

	/*
	 * Cache the device ID here क्रम easy access; this is useful, in
	 * particular, in situations where the channel's device_obj has
	 * not been allocated/initialized yet.
	 */
	u16 device_id;

	/*
	 * We must offload the handling of the primary/sub channels
	 * from the single-thपढ़ोed vmbus_connection.work_queue to
	 * two dअगरferent workqueue, otherwise we can block
	 * vmbus_connection.work_queue and hang: see vmbus_process_offer().
	 */
	काष्ठा work_काष्ठा add_channel_work;

	/*
	 * Guest to host पूर्णांकerrupts caused by the inbound ring buffer changing
	 * from full to not full जबतक a packet is रुकोing.
	 */
	u64 पूर्णांकr_in_full;

	/*
	 * The total number of ग_लिखो operations that encountered a full
	 * outbound ring buffer.
	 */
	u64 out_full_total;

	/*
	 * The number of ग_लिखो operations that were the first to encounter a
	 * full outbound ring buffer.
	 */
	u64 out_full_first;

	/* enabling/disabling fuzz testing on the channel (शेष is false)*/
	bool fuzz_testing_state;

	/*
	 * Interrupt delay will delay the guest from emptying the ring buffer
	 * क्रम a specअगरic amount of समय. The delay is in microseconds and will
	 * be between 1 to a maximum of 1000, its शेष is 0 (no delay).
	 * The  Message delay will delay guest पढ़ोing on a per message basis
	 * in microseconds between 1 to 1000 with the शेष being 0
	 * (no delay).
	 */
	u32 fuzz_testing_पूर्णांकerrupt_delay;
	u32 fuzz_testing_message_delay;

	/* request/transaction ids क्रम VMBus */
	काष्ठा vmbus_requestor requestor;
	u32 rqstor_size;
पूर्ण;

u64 vmbus_next_request_id(काष्ठा vmbus_requestor *rqstor, u64 rqst_addr);
u64 vmbus_request_addr(काष्ठा vmbus_requestor *rqstor, u64 trans_id);

अटल अंतरभूत bool is_hvsock_channel(स्थिर काष्ठा vmbus_channel *c)
अणु
	वापस !!(c->offermsg.offer.chn_flags &
		  VMBUS_CHANNEL_TLNPI_PROVIDER_OFFER);
पूर्ण

अटल अंतरभूत bool is_sub_channel(स्थिर काष्ठा vmbus_channel *c)
अणु
	वापस c->offermsg.offer.sub_channel_index != 0;
पूर्ण

अटल अंतरभूत व्योम set_channel_पढ़ो_mode(काष्ठा vmbus_channel *c,
					क्रमागत hv_callback_mode mode)
अणु
	c->callback_mode = mode;
पूर्ण

अटल अंतरभूत व्योम set_per_channel_state(काष्ठा vmbus_channel *c, व्योम *s)
अणु
	c->per_channel_state = s;
पूर्ण

अटल अंतरभूत व्योम *get_per_channel_state(काष्ठा vmbus_channel *c)
अणु
	वापस c->per_channel_state;
पूर्ण

अटल अंतरभूत व्योम set_channel_pending_send_size(काष्ठा vmbus_channel *c,
						 u32 size)
अणु
	अचिन्हित दीर्घ flags;

	अगर (size) अणु
		spin_lock_irqsave(&c->outbound.ring_lock, flags);
		++c->out_full_total;

		अगर (!c->out_full_flag) अणु
			++c->out_full_first;
			c->out_full_flag = true;
		पूर्ण
		spin_unlock_irqrestore(&c->outbound.ring_lock, flags);
	पूर्ण अन्यथा अणु
		c->out_full_flag = false;
	पूर्ण

	c->outbound.ring_buffer->pending_send_sz = size;
पूर्ण

अटल अंतरभूत व्योम set_low_latency_mode(काष्ठा vmbus_channel *c)
अणु
	c->low_latency = true;
पूर्ण

अटल अंतरभूत व्योम clear_low_latency_mode(काष्ठा vmbus_channel *c)
अणु
	c->low_latency = false;
पूर्ण

व्योम vmbus_onmessage(काष्ठा vmbus_channel_message_header *hdr);

पूर्णांक vmbus_request_offers(व्योम);

/*
 * APIs क्रम managing sub-channels.
 */

व्योम vmbus_set_sc_create_callback(काष्ठा vmbus_channel *primary_channel,
			व्योम (*sc_cr_cb)(काष्ठा vmbus_channel *new_sc));

व्योम vmbus_set_chn_rescind_callback(काष्ठा vmbus_channel *channel,
		व्योम (*chn_rescind_cb)(काष्ठा vmbus_channel *));

/*
 * Check अगर sub-channels have alपढ़ोy been offerred. This API will be useful
 * when the driver is unloaded after establishing sub-channels. In this हाल,
 * when the driver is re-loaded, the driver would have to check अगर the
 * subchannels have alपढ़ोy been established beक्रमe attempting to request
 * the creation of sub-channels.
 * This function वापसs TRUE to indicate that subchannels have alपढ़ोy been
 * created.
 * This function should be invoked after setting the callback function क्रम
 * sub-channel creation.
 */
bool vmbus_are_subchannels_present(काष्ठा vmbus_channel *primary);

/* The क्रमmat must be the same as काष्ठा vmdata_gpa_direct */
काष्ठा vmbus_channel_packet_page_buffer अणु
	u16 type;
	u16 dataoffset8;
	u16 length8;
	u16 flags;
	u64 transactionid;
	u32 reserved;
	u32 rangecount;
	काष्ठा hv_page_buffer range[MAX_PAGE_BUFFER_COUNT];
पूर्ण __packed;

/* The क्रमmat must be the same as काष्ठा vmdata_gpa_direct */
काष्ठा vmbus_channel_packet_multipage_buffer अणु
	u16 type;
	u16 dataoffset8;
	u16 length8;
	u16 flags;
	u64 transactionid;
	u32 reserved;
	u32 rangecount;		/* Always 1 in this हाल */
	काष्ठा hv_multipage_buffer range;
पूर्ण __packed;

/* The क्रमmat must be the same as काष्ठा vmdata_gpa_direct */
काष्ठा vmbus_packet_mpb_array अणु
	u16 type;
	u16 dataoffset8;
	u16 length8;
	u16 flags;
	u64 transactionid;
	u32 reserved;
	u32 rangecount;         /* Always 1 in this हाल */
	काष्ठा hv_mpb_array range;
पूर्ण __packed;

पूर्णांक vmbus_alloc_ring(काष्ठा vmbus_channel *channel,
		     u32 send_size, u32 recv_size);
व्योम vmbus_मुक्त_ring(काष्ठा vmbus_channel *channel);

पूर्णांक vmbus_connect_ring(काष्ठा vmbus_channel *channel,
		       व्योम (*onchannel_callback)(व्योम *context),
		       व्योम *context);
पूर्णांक vmbus_disconnect_ring(काष्ठा vmbus_channel *channel);

बाह्य पूर्णांक vmbus_खोलो(काष्ठा vmbus_channel *channel,
			    u32 send_ringbuffersize,
			    u32 recv_ringbuffersize,
			    व्योम *userdata,
			    u32 userdatalen,
			    व्योम (*onchannel_callback)(व्योम *context),
			    व्योम *context);

बाह्य व्योम vmbus_बंद(काष्ठा vmbus_channel *channel);

बाह्य पूर्णांक vmbus_sendpacket(काष्ठा vmbus_channel *channel,
				  व्योम *buffer,
				  u32 bufferLen,
				  u64 requestid,
				  क्रमागत vmbus_packet_type type,
				  u32 flags);

बाह्य पूर्णांक vmbus_sendpacket_pagebuffer(काष्ठा vmbus_channel *channel,
					    काष्ठा hv_page_buffer pagebuffers[],
					    u32 pagecount,
					    व्योम *buffer,
					    u32 bufferlen,
					    u64 requestid);

बाह्य पूर्णांक vmbus_sendpacket_mpb_desc(काष्ठा vmbus_channel *channel,
				     काष्ठा vmbus_packet_mpb_array *mpb,
				     u32 desc_size,
				     व्योम *buffer,
				     u32 bufferlen,
				     u64 requestid);

बाह्य पूर्णांक vmbus_establish_gpadl(काष्ठा vmbus_channel *channel,
				      व्योम *kbuffer,
				      u32 size,
				      u32 *gpadl_handle);

बाह्य पूर्णांक vmbus_tearकरोwn_gpadl(काष्ठा vmbus_channel *channel,
				     u32 gpadl_handle);

व्योम vmbus_reset_channel_cb(काष्ठा vmbus_channel *channel);

बाह्य पूर्णांक vmbus_recvpacket(काष्ठा vmbus_channel *channel,
				  व्योम *buffer,
				  u32 bufferlen,
				  u32 *buffer_actual_len,
				  u64 *requestid);

बाह्य पूर्णांक vmbus_recvpacket_raw(काष्ठा vmbus_channel *channel,
				     व्योम *buffer,
				     u32 bufferlen,
				     u32 *buffer_actual_len,
				     u64 *requestid);


बाह्य व्योम vmbus_onसमयr(अचिन्हित दीर्घ data);

/* Base driver object */
काष्ठा hv_driver अणु
	स्थिर अक्षर *name;

	/*
	 * A hvsock offer, which has a VMBUS_CHANNEL_TLNPI_PROVIDER_OFFER
	 * channel flag, actually करोesn't mean a synthetic device because the
	 * offer's अगर_type/अगर_instance can change क्रम every new hvsock
	 * connection.
	 *
	 * However, to facilitate the notअगरication of new-offer/rescind-offer
	 * from vmbus driver to hvsock driver, we can handle hvsock offer as
	 * a special vmbus device, and hence we need the below flag to
	 * indicate अगर the driver is the hvsock driver or not: we need to
	 * specially treat the hvosck offer & driver in vmbus_match().
	 */
	bool hvsock;

	/* the device type supported by this driver */
	guid_t dev_type;
	स्थिर काष्ठा hv_vmbus_device_id *id_table;

	काष्ठा device_driver driver;

	/* dynamic device GUID's */
	काष्ठा  अणु
		spinlock_t lock;
		काष्ठा list_head list;
	पूर्ण dynids;

	पूर्णांक (*probe)(काष्ठा hv_device *, स्थिर काष्ठा hv_vmbus_device_id *);
	पूर्णांक (*हटाओ)(काष्ठा hv_device *);
	व्योम (*shutकरोwn)(काष्ठा hv_device *);

	पूर्णांक (*suspend)(काष्ठा hv_device *);
	पूर्णांक (*resume)(काष्ठा hv_device *);

पूर्ण;

/* Base device object */
काष्ठा hv_device अणु
	/* the device type id of this device */
	guid_t dev_type;

	/* the device instance id of this device */
	guid_t dev_instance;
	u16 venकरोr_id;
	u16 device_id;

	काष्ठा device device;
	अक्षर *driver_override; /* Driver name to क्रमce a match */

	काष्ठा vmbus_channel *channel;
	काष्ठा kset	     *channels_kset;

	/* place holder to keep track of the dir क्रम hv device in debugfs */
	काष्ठा dentry *debug_dir;

पूर्ण;


अटल अंतरभूत काष्ठा hv_device *device_to_hv_device(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा hv_device, device);
पूर्ण

अटल अंतरभूत काष्ठा hv_driver *drv_to_hv_drv(काष्ठा device_driver *d)
अणु
	वापस container_of(d, काष्ठा hv_driver, driver);
पूर्ण

अटल अंतरभूत व्योम hv_set_drvdata(काष्ठा hv_device *dev, व्योम *data)
अणु
	dev_set_drvdata(&dev->device, data);
पूर्ण

अटल अंतरभूत व्योम *hv_get_drvdata(काष्ठा hv_device *dev)
अणु
	वापस dev_get_drvdata(&dev->device);
पूर्ण

काष्ठा hv_ring_buffer_debug_info अणु
	u32 current_पूर्णांकerrupt_mask;
	u32 current_पढ़ो_index;
	u32 current_ग_लिखो_index;
	u32 bytes_avail_toपढ़ो;
	u32 bytes_avail_toग_लिखो;
पूर्ण;


पूर्णांक hv_ringbuffer_get_debuginfo(काष्ठा hv_ring_buffer_info *ring_info,
				काष्ठा hv_ring_buffer_debug_info *debug_info);

/* Vmbus पूर्णांकerface */
#घोषणा vmbus_driver_रेजिस्टर(driver)	\
	__vmbus_driver_रेजिस्टर(driver, THIS_MODULE, KBUILD_MODNAME)
पूर्णांक __must_check __vmbus_driver_रेजिस्टर(काष्ठा hv_driver *hv_driver,
					 काष्ठा module *owner,
					 स्थिर अक्षर *mod_name);
व्योम vmbus_driver_unरेजिस्टर(काष्ठा hv_driver *hv_driver);

व्योम vmbus_hvsock_device_unरेजिस्टर(काष्ठा vmbus_channel *channel);

पूर्णांक vmbus_allocate_mmio(काष्ठा resource **new, काष्ठा hv_device *device_obj,
			resource_माप_प्रकार min, resource_माप_प्रकार max,
			resource_माप_प्रकार size, resource_माप_प्रकार align,
			bool fb_overlap_ok);
व्योम vmbus_मुक्त_mmio(resource_माप_प्रकार start, resource_माप_प्रकार size);

/*
 * GUID definitions of various offer types - services offered to the guest.
 */

/*
 * Network GUID
 * अणुf8615163-df3e-46c5-913f-f2d2f965ed0eपूर्ण
 */
#घोषणा HV_NIC_GUID \
	.guid = GUID_INIT(0xf8615163, 0xdf3e, 0x46c5, 0x91, 0x3f, \
			  0xf2, 0xd2, 0xf9, 0x65, 0xed, 0x0e)

/*
 * IDE GUID
 * अणु32412632-86cb-44a2-9b5c-50d1417354f5पूर्ण
 */
#घोषणा HV_IDE_GUID \
	.guid = GUID_INIT(0x32412632, 0x86cb, 0x44a2, 0x9b, 0x5c, \
			  0x50, 0xd1, 0x41, 0x73, 0x54, 0xf5)

/*
 * SCSI GUID
 * अणुba6163d9-04a1-4d29-b605-72e2ffb1dc7fपूर्ण
 */
#घोषणा HV_SCSI_GUID \
	.guid = GUID_INIT(0xba6163d9, 0x04a1, 0x4d29, 0xb6, 0x05, \
			  0x72, 0xe2, 0xff, 0xb1, 0xdc, 0x7f)

/*
 * Shutकरोwn GUID
 * अणु0e0b6031-5213-4934-818b-38d90ced39dbपूर्ण
 */
#घोषणा HV_SHUTDOWN_GUID \
	.guid = GUID_INIT(0x0e0b6031, 0x5213, 0x4934, 0x81, 0x8b, \
			  0x38, 0xd9, 0x0c, 0xed, 0x39, 0xdb)

/*
 * Time Synch GUID
 * अणु9527E630-D0AE-497b-ADCE-E80AB0175CAFपूर्ण
 */
#घोषणा HV_TS_GUID \
	.guid = GUID_INIT(0x9527e630, 0xd0ae, 0x497b, 0xad, 0xce, \
			  0xe8, 0x0a, 0xb0, 0x17, 0x5c, 0xaf)

/*
 * Heartbeat GUID
 * अणु57164f39-9115-4e78-ab55-382f3bd5422dपूर्ण
 */
#घोषणा HV_HEART_BEAT_GUID \
	.guid = GUID_INIT(0x57164f39, 0x9115, 0x4e78, 0xab, 0x55, \
			  0x38, 0x2f, 0x3b, 0xd5, 0x42, 0x2d)

/*
 * KVP GUID
 * अणुa9a0f4e7-5a45-4d96-b827-8a841e8c03e6पूर्ण
 */
#घोषणा HV_KVP_GUID \
	.guid = GUID_INIT(0xa9a0f4e7, 0x5a45, 0x4d96, 0xb8, 0x27, \
			  0x8a, 0x84, 0x1e, 0x8c, 0x03, 0xe6)

/*
 * Dynamic memory GUID
 * अणु525074dc-8985-46e2-8057-a307dc18a502पूर्ण
 */
#घोषणा HV_DM_GUID \
	.guid = GUID_INIT(0x525074dc, 0x8985, 0x46e2, 0x80, 0x57, \
			  0xa3, 0x07, 0xdc, 0x18, 0xa5, 0x02)

/*
 * Mouse GUID
 * अणुcfa8b69e-5b4a-4cc0-b98b-8ba1a1f3f95aपूर्ण
 */
#घोषणा HV_MOUSE_GUID \
	.guid = GUID_INIT(0xcfa8b69e, 0x5b4a, 0x4cc0, 0xb9, 0x8b, \
			  0x8b, 0xa1, 0xa1, 0xf3, 0xf9, 0x5a)

/*
 * Keyboard GUID
 * अणुf912ad6d-2b17-48ea-bd65-f927a61c7684पूर्ण
 */
#घोषणा HV_KBD_GUID \
	.guid = GUID_INIT(0xf912ad6d, 0x2b17, 0x48ea, 0xbd, 0x65, \
			  0xf9, 0x27, 0xa6, 0x1c, 0x76, 0x84)

/*
 * VSS (Backup/Restore) GUID
 */
#घोषणा HV_VSS_GUID \
	.guid = GUID_INIT(0x35fa2e29, 0xea23, 0x4236, 0x96, 0xae, \
			  0x3a, 0x6e, 0xba, 0xcb, 0xa4, 0x40)
/*
 * Synthetic Video GUID
 * अणुDA0A7802-E377-4aac-8E77-0558EB1073F8पूर्ण
 */
#घोषणा HV_SYNTHVID_GUID \
	.guid = GUID_INIT(0xda0a7802, 0xe377, 0x4aac, 0x8e, 0x77, \
			  0x05, 0x58, 0xeb, 0x10, 0x73, 0xf8)

/*
 * Synthetic FC GUID
 * अणु2f9bcc4a-0069-4af3-b76b-6fd0be528cdaपूर्ण
 */
#घोषणा HV_SYNTHFC_GUID \
	.guid = GUID_INIT(0x2f9bcc4a, 0x0069, 0x4af3, 0xb7, 0x6b, \
			  0x6f, 0xd0, 0xbe, 0x52, 0x8c, 0xda)

/*
 * Guest File Copy Service
 * अणु34D14BE3-DEE4-41c8-9AE7-6B174977C192पूर्ण
 */

#घोषणा HV_FCOPY_GUID \
	.guid = GUID_INIT(0x34d14be3, 0xdee4, 0x41c8, 0x9a, 0xe7, \
			  0x6b, 0x17, 0x49, 0x77, 0xc1, 0x92)

/*
 * NetworkDirect. This is the guest RDMA service.
 * अणु8c2eaf3d-32a7-4b09-ab99-bd1f1c86b501पूर्ण
 */
#घोषणा HV_ND_GUID \
	.guid = GUID_INIT(0x8c2eaf3d, 0x32a7, 0x4b09, 0xab, 0x99, \
			  0xbd, 0x1f, 0x1c, 0x86, 0xb5, 0x01)

/*
 * PCI Express Pass Through
 * अणु44C4F61D-4444-4400-9D52-802E27EDE19Fपूर्ण
 */

#घोषणा HV_PCIE_GUID \
	.guid = GUID_INIT(0x44c4f61d, 0x4444, 0x4400, 0x9d, 0x52, \
			  0x80, 0x2e, 0x27, 0xed, 0xe1, 0x9f)

/*
 * Linux करोesn't support the 3 devices: the first two are क्रम
 * Automatic Virtual Machine Activation, and the third is क्रम
 * Remote Desktop Virtualization.
 * अणुf8e65716-3cb3-4a06-9a60-1889c5cccab5पूर्ण
 * अणु3375baf4-9e15-4b30-b765-67acb10d607bपूर्ण
 * अणु276aacf4-ac15-426c-98dd-7521ad3f01feपूर्ण
 */

#घोषणा HV_AVMA1_GUID \
	.guid = GUID_INIT(0xf8e65716, 0x3cb3, 0x4a06, 0x9a, 0x60, \
			  0x18, 0x89, 0xc5, 0xcc, 0xca, 0xb5)

#घोषणा HV_AVMA2_GUID \
	.guid = GUID_INIT(0x3375baf4, 0x9e15, 0x4b30, 0xb7, 0x65, \
			  0x67, 0xac, 0xb1, 0x0d, 0x60, 0x7b)

#घोषणा HV_RDV_GUID \
	.guid = GUID_INIT(0x276aacf4, 0xac15, 0x426c, 0x98, 0xdd, \
			  0x75, 0x21, 0xad, 0x3f, 0x01, 0xfe)

/*
 * Common header क्रम Hyper-V ICs
 */

#घोषणा ICMSGTYPE_NEGOTIATE		0
#घोषणा ICMSGTYPE_HEARTBEAT		1
#घोषणा ICMSGTYPE_KVPEXCHANGE		2
#घोषणा ICMSGTYPE_SHUTDOWN		3
#घोषणा ICMSGTYPE_TIMESYNC		4
#घोषणा ICMSGTYPE_VSS			5
#घोषणा ICMSGTYPE_FCOPY			7

#घोषणा ICMSGHDRFLAG_TRANSACTION	1
#घोषणा ICMSGHDRFLAG_REQUEST		2
#घोषणा ICMSGHDRFLAG_RESPONSE		4


/*
 * While we want to handle util services as regular devices,
 * there is only one instance of each of these services; so
 * we अटलally allocate the service specअगरic state.
 */

काष्ठा hv_util_service अणु
	u8 *recv_buffer;
	व्योम *channel;
	व्योम (*util_cb)(व्योम *);
	पूर्णांक (*util_init)(काष्ठा hv_util_service *);
	व्योम (*util_deinit)(व्योम);
	पूर्णांक (*util_pre_suspend)(व्योम);
	पूर्णांक (*util_pre_resume)(व्योम);
पूर्ण;

काष्ठा vmbuspipe_hdr अणु
	u32 flags;
	u32 msgsize;
पूर्ण __packed;

काष्ठा ic_version अणु
	u16 major;
	u16 minor;
पूर्ण __packed;

काष्ठा icmsg_hdr अणु
	काष्ठा ic_version icverframe;
	u16 icmsgtype;
	काष्ठा ic_version icvermsg;
	u16 icmsgsize;
	u32 status;
	u8 ictransaction_id;
	u8 icflags;
	u8 reserved[2];
पूर्ण __packed;

#घोषणा IC_VERSION_NEGOTIATION_MAX_VER_COUNT 100
#घोषणा ICMSG_HDR (माप(काष्ठा vmbuspipe_hdr) + माप(काष्ठा icmsg_hdr))
#घोषणा ICMSG_NEGOTIATE_PKT_SIZE(icframe_vercnt, icmsg_vercnt) \
	(ICMSG_HDR + माप(काष्ठा icmsg_negotiate) + \
	 (((icframe_vercnt) + (icmsg_vercnt)) * माप(काष्ठा ic_version)))

काष्ठा icmsg_negotiate अणु
	u16 icframe_vercnt;
	u16 icmsg_vercnt;
	u32 reserved;
	काष्ठा ic_version icversion_data[]; /* any size array */
पूर्ण __packed;

काष्ठा shutकरोwn_msg_data अणु
	u32 reason_code;
	u32 समयout_seconds;
	u32 flags;
	u8  display_message[2048];
पूर्ण __packed;

काष्ठा heartbeat_msg_data अणु
	u64 seq_num;
	u32 reserved[8];
पूर्ण __packed;

/* Time Sync IC defs */
#घोषणा ICTIMESYNCFLAG_PROBE	0
#घोषणा ICTIMESYNCFLAG_SYNC	1
#घोषणा ICTIMESYNCFLAG_SAMPLE	2

#अगर_घोषित __x86_64__
#घोषणा WLTIMEDELTA	116444736000000000L	/* in 100ns unit */
#अन्यथा
#घोषणा WLTIMEDELTA	116444736000000000LL
#पूर्ण_अगर

काष्ठा iस_समयsync_data अणु
	u64 parentसमय;
	u64 childसमय;
	u64 roundtripसमय;
	u8 flags;
पूर्ण __packed;

काष्ठा iस_समयsync_ref_data अणु
	u64 parentसमय;
	u64 vmreferenceसमय;
	u8 flags;
	अक्षर leapflags;
	अक्षर stratum;
	u8 reserved[3];
पूर्ण __packed;

काष्ठा hyperv_service_callback अणु
	u8 msg_type;
	अक्षर *log_msg;
	guid_t data;
	काष्ठा vmbus_channel *channel;
	व्योम (*callback)(व्योम *context);
पूर्ण;

#घोषणा MAX_SRV_VER	0x7ffffff
बाह्य bool vmbus_prep_negotiate_resp(काष्ठा icmsg_hdr *icmsghdrp, u8 *buf, u32 buflen,
				स्थिर पूर्णांक *fw_version, पूर्णांक fw_vercnt,
				स्थिर पूर्णांक *srv_version, पूर्णांक srv_vercnt,
				पूर्णांक *nego_fw_version, पूर्णांक *nego_srv_version);

व्योम hv_process_channel_removal(काष्ठा vmbus_channel *channel);

व्योम vmbus_setevent(काष्ठा vmbus_channel *channel);
/*
 * Negotiated version with the Host.
 */

बाह्य __u32 vmbus_proto_version;

पूर्णांक vmbus_send_tl_connect_request(स्थिर guid_t *shv_guest_servie_id,
				  स्थिर guid_t *shv_host_servie_id);
पूर्णांक vmbus_send_modअगरychannel(काष्ठा vmbus_channel *channel, u32 target_vp);
व्योम vmbus_set_event(काष्ठा vmbus_channel *channel);

/* Get the start of the ring buffer. */
अटल अंतरभूत व्योम *
hv_get_ring_buffer(स्थिर काष्ठा hv_ring_buffer_info *ring_info)
अणु
	वापस ring_info->ring_buffer->buffer;
पूर्ण

/*
 * Mask off host पूर्णांकerrupt callback notअगरications
 */
अटल अंतरभूत व्योम hv_begin_पढ़ो(काष्ठा hv_ring_buffer_info *rbi)
अणु
	rbi->ring_buffer->पूर्णांकerrupt_mask = 1;

	/* make sure mask update is not reordered */
	virt_mb();
पूर्ण

/*
 * Re-enable host callback and वापस number of outstanding bytes
 */
अटल अंतरभूत u32 hv_end_पढ़ो(काष्ठा hv_ring_buffer_info *rbi)
अणु

	rbi->ring_buffer->पूर्णांकerrupt_mask = 0;

	/* make sure mask update is not reordered */
	virt_mb();

	/*
	 * Now check to see अगर the ring buffer is still empty.
	 * If it is not, we raced and we need to process new
	 * incoming messages.
	 */
	वापस hv_get_bytes_to_पढ़ो(rbi);
पूर्ण

/*
 * An API to support in-place processing of incoming VMBUS packets.
 */

/* Get data payload associated with descriptor */
अटल अंतरभूत व्योम *hv_pkt_data(स्थिर काष्ठा vmpacket_descriptor *desc)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)desc + (desc->offset8 << 3));
पूर्ण

/* Get data size associated with descriptor */
अटल अंतरभूत u32 hv_pkt_datalen(स्थिर काष्ठा vmpacket_descriptor *desc)
अणु
	वापस (desc->len8 << 3) - (desc->offset8 << 3);
पूर्ण


काष्ठा vmpacket_descriptor *
hv_pkt_iter_first(काष्ठा vmbus_channel *channel);

काष्ठा vmpacket_descriptor *
__hv_pkt_iter_next(काष्ठा vmbus_channel *channel,
		   स्थिर काष्ठा vmpacket_descriptor *pkt);

व्योम hv_pkt_iter_बंद(काष्ठा vmbus_channel *channel);

/*
 * Get next packet descriptor from iterator
 * If at end of list, वापस शून्य and update host.
 */
अटल अंतरभूत काष्ठा vmpacket_descriptor *
hv_pkt_iter_next(काष्ठा vmbus_channel *channel,
		 स्थिर काष्ठा vmpacket_descriptor *pkt)
अणु
	काष्ठा vmpacket_descriptor *nxt;

	nxt = __hv_pkt_iter_next(channel, pkt);
	अगर (!nxt)
		hv_pkt_iter_बंद(channel);

	वापस nxt;
पूर्ण

#घोषणा क्रमeach_vmbus_pkt(pkt, channel) \
	क्रम (pkt = hv_pkt_iter_first(channel); pkt; \
	    pkt = hv_pkt_iter_next(channel, pkt))

/*
 * Interface क्रम passing data between SR-IOV PF and VF drivers. The VF driver
 * sends requests to पढ़ो and ग_लिखो blocks. Each block must be 128 bytes or
 * smaller. Optionally, the VF driver can रेजिस्टर a callback function which
 * will be invoked when the host says that one or more of the first 64 block
 * IDs is "invalid" which means that the VF driver should reपढ़ो them.
 */
#घोषणा HV_CONFIG_BLOCK_SIZE_MAX 128

पूर्णांक hyperv_पढ़ो_cfg_blk(काष्ठा pci_dev *dev, व्योम *buf, अचिन्हित पूर्णांक buf_len,
			अचिन्हित पूर्णांक block_id, अचिन्हित पूर्णांक *bytes_वापसed);
पूर्णांक hyperv_ग_लिखो_cfg_blk(काष्ठा pci_dev *dev, व्योम *buf, अचिन्हित पूर्णांक len,
			 अचिन्हित पूर्णांक block_id);
पूर्णांक hyperv_reg_block_invalidate(काष्ठा pci_dev *dev, व्योम *context,
				व्योम (*block_invalidate)(व्योम *context,
							 u64 block_mask));

काष्ठा hyperv_pci_block_ops अणु
	पूर्णांक (*पढ़ो_block)(काष्ठा pci_dev *dev, व्योम *buf, अचिन्हित पूर्णांक buf_len,
			  अचिन्हित पूर्णांक block_id, अचिन्हित पूर्णांक *bytes_वापसed);
	पूर्णांक (*ग_लिखो_block)(काष्ठा pci_dev *dev, व्योम *buf, अचिन्हित पूर्णांक len,
			   अचिन्हित पूर्णांक block_id);
	पूर्णांक (*reg_blk_invalidate)(काष्ठा pci_dev *dev, व्योम *context,
				  व्योम (*block_invalidate)(व्योम *context,
							   u64 block_mask));
पूर्ण;

बाह्य काष्ठा hyperv_pci_block_ops hvpci_block_ops;

अटल अंतरभूत अचिन्हित दीर्घ virt_to_hvpfn(व्योम *addr)
अणु
	phys_addr_t paddr;

	अगर (is_vदो_स्मृति_addr(addr))
		paddr = page_to_phys(vदो_स्मृति_to_page(addr)) +
				     offset_in_page(addr);
	अन्यथा
		paddr = __pa(addr);

	वापस  paddr >> HV_HYP_PAGE_SHIFT;
पूर्ण

#घोषणा NR_HV_HYP_PAGES_IN_PAGE	(PAGE_SIZE / HV_HYP_PAGE_SIZE)
#घोषणा offset_in_hvpage(ptr)	((अचिन्हित दीर्घ)(ptr) & ~HV_HYP_PAGE_MASK)
#घोषणा HVPFN_UP(x)	(((x) + HV_HYP_PAGE_SIZE-1) >> HV_HYP_PAGE_SHIFT)
#घोषणा HVPFN_DOWN(x)	((x) >> HV_HYP_PAGE_SHIFT)
#घोषणा page_to_hvpfn(page)	(page_to_pfn(page) * NR_HV_HYP_PAGES_IN_PAGE)

#पूर्ण_अगर /* _HYPERV_H */
