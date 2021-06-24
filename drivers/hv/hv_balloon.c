<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012, Microsoft Corporation.
 *
 * Author:
 *   K. Y. Srinivasan <kys@microsoft.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mman.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/completion.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/memory.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/percpu_counter.h>
#समावेश <linux/page_reporting.h>

#समावेश <linux/hyperv.h>
#समावेश <यंत्र/hyperv-tlfs.h>

#समावेश <यंत्र/mshyperv.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "hv_trace_balloon.h"

/*
 * We begin with definitions supporting the Dynamic Memory protocol
 * with the host.
 *
 * Begin protocol definitions.
 */



/*
 * Protocol versions. The low word is the minor version, the high word the major
 * version.
 *
 * History:
 * Initial version 1.0
 * Changed to 0.1 on 2009/03/25
 * Changes to 0.2 on 2009/05/14
 * Changes to 0.3 on 2009/12/03
 * Changed to 1.0 on 2011/04/05
 */

#घोषणा DYNMEM_MAKE_VERSION(Major, Minor) ((__u32)(((Major) << 16) | (Minor)))
#घोषणा DYNMEM_MAJOR_VERSION(Version) ((__u32)(Version) >> 16)
#घोषणा DYNMEM_MINOR_VERSION(Version) ((__u32)(Version) & 0xff)

क्रमागत अणु
	DYNMEM_PROTOCOL_VERSION_1 = DYNMEM_MAKE_VERSION(0, 3),
	DYNMEM_PROTOCOL_VERSION_2 = DYNMEM_MAKE_VERSION(1, 0),
	DYNMEM_PROTOCOL_VERSION_3 = DYNMEM_MAKE_VERSION(2, 0),

	DYNMEM_PROTOCOL_VERSION_WIN7 = DYNMEM_PROTOCOL_VERSION_1,
	DYNMEM_PROTOCOL_VERSION_WIN8 = DYNMEM_PROTOCOL_VERSION_2,
	DYNMEM_PROTOCOL_VERSION_WIN10 = DYNMEM_PROTOCOL_VERSION_3,

	DYNMEM_PROTOCOL_VERSION_CURRENT = DYNMEM_PROTOCOL_VERSION_WIN10
पूर्ण;



/*
 * Message Types
 */

क्रमागत dm_message_type अणु
	/*
	 * Version 0.3
	 */
	DM_ERROR			= 0,
	DM_VERSION_REQUEST		= 1,
	DM_VERSION_RESPONSE		= 2,
	DM_CAPABILITIES_REPORT		= 3,
	DM_CAPABILITIES_RESPONSE	= 4,
	DM_STATUS_REPORT		= 5,
	DM_BALLOON_REQUEST		= 6,
	DM_BALLOON_RESPONSE		= 7,
	DM_UNBALLOON_REQUEST		= 8,
	DM_UNBALLOON_RESPONSE		= 9,
	DM_MEM_HOT_ADD_REQUEST		= 10,
	DM_MEM_HOT_ADD_RESPONSE		= 11,
	DM_VERSION_03_MAX		= 11,
	/*
	 * Version 1.0.
	 */
	DM_INFO_MESSAGE			= 12,
	DM_VERSION_1_MAX		= 12
पूर्ण;


/*
 * Structures defining the dynamic memory management
 * protocol.
 */

जोड़ dm_version अणु
	काष्ठा अणु
		__u16 minor_version;
		__u16 major_version;
	पूर्ण;
	__u32 version;
पूर्ण __packed;


जोड़ dm_caps अणु
	काष्ठा अणु
		__u64 balloon:1;
		__u64 hot_add:1;
		/*
		 * To support guests that may have alignment
		 * limitations on hot-add, the guest can specअगरy
		 * its alignment requirements; a value of n
		 * represents an alignment of 2^n in mega bytes.
		 */
		__u64 hot_add_alignment:4;
		__u64 reservedz:58;
	पूर्ण cap_bits;
	__u64 caps;
पूर्ण __packed;

जोड़ dm_mem_page_range अणु
	काष्ठा  अणु
		/*
		 * The PFN number of the first page in the range.
		 * 40 bits is the architectural limit of a PFN
		 * number क्रम AMD64.
		 */
		__u64 start_page:40;
		/*
		 * The number of pages in the range.
		 */
		__u64 page_cnt:24;
	पूर्ण finfo;
	__u64  page_range;
पूर्ण __packed;



/*
 * The header क्रम all dynamic memory messages:
 *
 * type: Type of the message.
 * size: Size of the message in bytes; including the header.
 * trans_id: The guest is responsible क्रम manufacturing this ID.
 */

काष्ठा dm_header अणु
	__u16 type;
	__u16 size;
	__u32 trans_id;
पूर्ण __packed;

/*
 * A generic message क्रमmat क्रम dynamic memory.
 * Specअगरic message क्रमmats are defined later in the file.
 */

काष्ठा dm_message अणु
	काष्ठा dm_header hdr;
	__u8 data[]; /* enबंदd message */
पूर्ण __packed;


/*
 * Specअगरic message types supporting the dynamic memory protocol.
 */

/*
 * Version negotiation message. Sent from the guest to the host.
 * The guest is मुक्त to try dअगरferent versions until the host
 * accepts the version.
 *
 * dm_version: The protocol version requested.
 * is_last_attempt: If TRUE, this is the last version guest will request.
 * reservedz: Reserved field, set to zero.
 */

काष्ठा dm_version_request अणु
	काष्ठा dm_header hdr;
	जोड़ dm_version version;
	__u32 is_last_attempt:1;
	__u32 reservedz:31;
पूर्ण __packed;

/*
 * Version response message; Host to Guest and indicates
 * अगर the host has accepted the version sent by the guest.
 *
 * is_accepted: If TRUE, host has accepted the version and the guest
 * should proceed to the next stage of the protocol. FALSE indicates that
 * guest should re-try with a dअगरferent version.
 *
 * reservedz: Reserved field, set to zero.
 */

काष्ठा dm_version_response अणु
	काष्ठा dm_header hdr;
	__u64 is_accepted:1;
	__u64 reservedz:63;
पूर्ण __packed;

/*
 * Message reporting capabilities. This is sent from the guest to the
 * host.
 */

काष्ठा dm_capabilities अणु
	काष्ठा dm_header hdr;
	जोड़ dm_caps caps;
	__u64 min_page_cnt;
	__u64 max_page_number;
पूर्ण __packed;

/*
 * Response to the capabilities message. This is sent from the host to the
 * guest. This message notअगरies अगर the host has accepted the guest's
 * capabilities. If the host has not accepted, the guest must shutकरोwn
 * the service.
 *
 * is_accepted: Indicates अगर the host has accepted guest's capabilities.
 * reservedz: Must be 0.
 */

काष्ठा dm_capabilities_resp_msg अणु
	काष्ठा dm_header hdr;
	__u64 is_accepted:1;
	__u64 reservedz:63;
पूर्ण __packed;

/*
 * This message is used to report memory pressure from the guest.
 * This message is not part of any transaction and there is no
 * response to this message.
 *
 * num_avail: Available memory in pages.
 * num_committed: Committed memory in pages.
 * page_file_size: The accumulated size of all page files
 *		   in the प्रणाली in pages.
 * zero_मुक्त: The nunber of zero and मुक्त pages.
 * page_file_ग_लिखोs: The ग_लिखोs to the page file in pages.
 * io_dअगरf: An indicator of file cache efficiency or page file activity,
 *	    calculated as File Cache Page Fault Count - Page Read Count.
 *	    This value is in pages.
 *
 * Some of these metrics are Winकरोws specअगरic and क्रमtunately
 * the algorithm on the host side that computes the guest memory
 * pressure only uses num_committed value.
 */

काष्ठा dm_status अणु
	काष्ठा dm_header hdr;
	__u64 num_avail;
	__u64 num_committed;
	__u64 page_file_size;
	__u64 zero_मुक्त;
	__u32 page_file_ग_लिखोs;
	__u32 io_dअगरf;
पूर्ण __packed;


/*
 * Message to ask the guest to allocate memory - balloon up message.
 * This message is sent from the host to the guest. The guest may not be
 * able to allocate as much memory as requested.
 *
 * num_pages: number of pages to allocate.
 */

काष्ठा dm_balloon अणु
	काष्ठा dm_header hdr;
	__u32 num_pages;
	__u32 reservedz;
पूर्ण __packed;


/*
 * Balloon response message; this message is sent from the guest
 * to the host in response to the balloon message.
 *
 * reservedz: Reserved; must be set to zero.
 * more_pages: If FALSE, this is the last message of the transaction.
 * अगर TRUE there will atleast one more message from the guest.
 *
 * range_count: The number of ranges in the range array.
 *
 * range_array: An array of page ranges वापसed to the host.
 *
 */

काष्ठा dm_balloon_response अणु
	काष्ठा dm_header hdr;
	__u32 reservedz;
	__u32 more_pages:1;
	__u32 range_count:31;
	जोड़ dm_mem_page_range range_array[];
पूर्ण __packed;

/*
 * Un-balloon message; this message is sent from the host
 * to the guest to give guest more memory.
 *
 * more_pages: If FALSE, this is the last message of the transaction.
 * अगर TRUE there will atleast one more message from the guest.
 *
 * reservedz: Reserved; must be set to zero.
 *
 * range_count: The number of ranges in the range array.
 *
 * range_array: An array of page ranges वापसed to the host.
 *
 */

काष्ठा dm_unballoon_request अणु
	काष्ठा dm_header hdr;
	__u32 more_pages:1;
	__u32 reservedz:31;
	__u32 range_count;
	जोड़ dm_mem_page_range range_array[];
पूर्ण __packed;

/*
 * Un-balloon response message; this message is sent from the guest
 * to the host in response to an unballoon request.
 *
 */

काष्ठा dm_unballoon_response अणु
	काष्ठा dm_header hdr;
पूर्ण __packed;


/*
 * Hot add request message. Message sent from the host to the guest.
 *
 * mem_range: Memory range to hot add.
 *
 */

काष्ठा dm_hot_add अणु
	काष्ठा dm_header hdr;
	जोड़ dm_mem_page_range range;
पूर्ण __packed;

/*
 * Hot add response message.
 * This message is sent by the guest to report the status of a hot add request.
 * If page_count is less than the requested page count, then the host should
 * assume all further hot add requests will fail, since this indicates that
 * the guest has hit an upper physical memory barrier.
 *
 * Hot adds may also fail due to low resources; in this हाल, the guest must
 * not complete this message until the hot add can succeed, and the host must
 * not send a new hot add request until the response is sent.
 * If VSC fails to hot add memory DYNMEM_NUMBER_OF_UNSUCCESSFUL_HOTADD_ATTEMPTS
 * बार it fails the request.
 *
 *
 * page_count: number of pages that were successfully hot added.
 *
 * result: result of the operation 1: success, 0: failure.
 *
 */

काष्ठा dm_hot_add_response अणु
	काष्ठा dm_header hdr;
	__u32 page_count;
	__u32 result;
पूर्ण __packed;

/*
 * Types of inक्रमmation sent from host to the guest.
 */

क्रमागत dm_info_type अणु
	INFO_TYPE_MAX_PAGE_CNT = 0,
	MAX_INFO_TYPE
पूर्ण;


/*
 * Header क्रम the inक्रमmation message.
 */

काष्ठा dm_info_header अणु
	क्रमागत dm_info_type type;
	__u32 data_size;
पूर्ण __packed;

/*
 * This message is sent from the host to the guest to pass
 * some relevant inक्रमmation (win8 addition).
 *
 * reserved: no used.
 * info_size: size of the inक्रमmation blob.
 * info: inक्रमmation blob.
 */

काष्ठा dm_info_msg अणु
	काष्ठा dm_header hdr;
	__u32 reserved;
	__u32 info_size;
	__u8  info[];
पूर्ण;

/*
 * End protocol definitions.
 */

/*
 * State to manage hot adding memory पूर्णांकo the guest.
 * The range start_pfn : end_pfn specअगरies the range
 * that the host has asked us to hot add. The range
 * start_pfn : ha_end_pfn specअगरies the range that we have
 * currently hot added. We hot add in multiples of 128M
 * chunks; it is possible that we may not be able to bring
 * online all the pages in the region. The range
 * covered_start_pfn:covered_end_pfn defines the pages that can
 * be brough online.
 */

काष्ठा hv_hotadd_state अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ covered_start_pfn;
	अचिन्हित दीर्घ covered_end_pfn;
	अचिन्हित दीर्घ ha_end_pfn;
	अचिन्हित दीर्घ end_pfn;
	/*
	 * A list of gaps.
	 */
	काष्ठा list_head gap_list;
पूर्ण;

काष्ठा hv_hotadd_gap अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ end_pfn;
पूर्ण;

काष्ठा balloon_state अणु
	__u32 num_pages;
	काष्ठा work_काष्ठा wrk;
पूर्ण;

काष्ठा hot_add_wrk अणु
	जोड़ dm_mem_page_range ha_page_range;
	जोड़ dm_mem_page_range ha_region_range;
	काष्ठा work_काष्ठा wrk;
पूर्ण;

अटल bool allow_hibernation;
अटल bool hot_add = true;
अटल bool करो_hot_add;
/*
 * Delay reporting memory pressure by
 * the specअगरied number of seconds.
 */
अटल uपूर्णांक pressure_report_delay = 45;

/*
 * The last समय we posted a pressure report to host.
 */
अटल अचिन्हित दीर्घ last_post_समय;

module_param(hot_add, bool, (S_IRUGO | S_IWUSR));
MODULE_PARM_DESC(hot_add, "If set attempt memory hot_add");

module_param(pressure_report_delay, uपूर्णांक, (S_IRUGO | S_IWUSR));
MODULE_PARM_DESC(pressure_report_delay, "Delay in secs in reporting pressure");
अटल atomic_t trans_id = ATOMIC_INIT(0);

अटल पूर्णांक dm_ring_size = 20 * 1024;

/*
 * Driver specअगरic state.
 */

क्रमागत hv_dm_state अणु
	DM_INITIALIZING = 0,
	DM_INITIALIZED,
	DM_BALLOON_UP,
	DM_BALLOON_DOWN,
	DM_HOT_ADD,
	DM_INIT_ERROR
पूर्ण;


अटल __u8 recv_buffer[HV_HYP_PAGE_SIZE];
अटल __u8 balloon_up_send_buffer[HV_HYP_PAGE_SIZE];
#घोषणा PAGES_IN_2M (2 * 1024 * 1024 / PAGE_SIZE)
#घोषणा HA_CHUNK (128 * 1024 * 1024 / PAGE_SIZE)

काष्ठा hv_dynmem_device अणु
	काष्ठा hv_device *dev;
	क्रमागत hv_dm_state state;
	काष्ठा completion host_event;
	काष्ठा completion config_event;

	/*
	 * Number of pages we have currently ballooned out.
	 */
	अचिन्हित पूर्णांक num_pages_ballooned;
	अचिन्हित पूर्णांक num_pages_onlined;
	अचिन्हित पूर्णांक num_pages_added;

	/*
	 * State to manage the ballooning (up) operation.
	 */
	काष्ठा balloon_state balloon_wrk;

	/*
	 * State to execute the "hot-add" operation.
	 */
	काष्ठा hot_add_wrk ha_wrk;

	/*
	 * This state tracks अगर the host has specअगरied a hot-add
	 * region.
	 */
	bool host_specअगरied_ha_region;

	/*
	 * State to synchronize hot-add.
	 */
	काष्ठा completion  ol_रुकोevent;
	/*
	 * This thपढ़ो handles hot-add
	 * requests from the host as well as notअगरying
	 * the host with regards to memory pressure in
	 * the guest.
	 */
	काष्ठा task_काष्ठा *thपढ़ो;

	/*
	 * Protects ha_region_list, num_pages_onlined counter and inभागidual
	 * regions from ha_region_list.
	 */
	spinlock_t ha_lock;

	/*
	 * A list of hot-add regions.
	 */
	काष्ठा list_head ha_region_list;

	/*
	 * We start with the highest version we can support
	 * and करोwngrade based on the host; we save here the
	 * next version to try.
	 */
	__u32 next_version;

	/*
	 * The negotiated version agreed by host.
	 */
	__u32 version;

	काष्ठा page_reporting_dev_info pr_dev_info;
पूर्ण;

अटल काष्ठा hv_dynmem_device dm_device;

अटल व्योम post_status(काष्ठा hv_dynmem_device *dm);

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल अंतरभूत bool has_pfn_is_backed(काष्ठा hv_hotadd_state *has,
				     अचिन्हित दीर्घ pfn)
अणु
	काष्ठा hv_hotadd_gap *gap;

	/* The page is not backed. */
	अगर ((pfn < has->covered_start_pfn) || (pfn >= has->covered_end_pfn))
		वापस false;

	/* Check क्रम gaps. */
	list_क्रम_each_entry(gap, &has->gap_list, list) अणु
		अगर ((pfn >= gap->start_pfn) && (pfn < gap->end_pfn))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल अचिन्हित दीर्घ hv_page_offline_check(अचिन्हित दीर्घ start_pfn,
					   अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ pfn = start_pfn, count = 0;
	काष्ठा hv_hotadd_state *has;
	bool found;

	जबतक (pfn < start_pfn + nr_pages) अणु
		/*
		 * Search क्रम HAS which covers the pfn and when we find one
		 * count how many consequitive PFNs are covered.
		 */
		found = false;
		list_क्रम_each_entry(has, &dm_device.ha_region_list, list) अणु
			जबतक ((pfn >= has->start_pfn) &&
			       (pfn < has->end_pfn) &&
			       (pfn < start_pfn + nr_pages)) अणु
				found = true;
				अगर (has_pfn_is_backed(has, pfn))
					count++;
				pfn++;
			पूर्ण
		पूर्ण

		/*
		 * This PFN is not in any HAS (e.g. we're offlining a region
		 * which was present at boot), no need to account क्रम it. Go
		 * to the next one.
		 */
		अगर (!found)
			pfn++;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक hv_memory_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
			      व्योम *v)
अणु
	काष्ठा memory_notअगरy *mem = (काष्ठा memory_notअगरy *)v;
	अचिन्हित दीर्घ flags, pfn_count;

	चयन (val) अणु
	हाल MEM_ONLINE:
	हाल MEM_CANCEL_ONLINE:
		complete(&dm_device.ol_रुकोevent);
		अवरोध;

	हाल MEM_OFFLINE:
		spin_lock_irqsave(&dm_device.ha_lock, flags);
		pfn_count = hv_page_offline_check(mem->start_pfn,
						  mem->nr_pages);
		अगर (pfn_count <= dm_device.num_pages_onlined) अणु
			dm_device.num_pages_onlined -= pfn_count;
		पूर्ण अन्यथा अणु
			/*
			 * We're offlining more pages than we managed to online.
			 * This is unexpected. In any हाल करोn't let
			 * num_pages_onlined wrap around zero.
			 */
			WARN_ON_ONCE(1);
			dm_device.num_pages_onlined = 0;
		पूर्ण
		spin_unlock_irqrestore(&dm_device.ha_lock, flags);
		अवरोध;
	हाल MEM_GOING_ONLINE:
	हाल MEM_GOING_OFFLINE:
	हाल MEM_CANCEL_OFFLINE:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block hv_memory_nb = अणु
	.notअगरier_call = hv_memory_notअगरier,
	.priority = 0
पूर्ण;

/* Check अगर the particular page is backed and can be onlined and online it. */
अटल व्योम hv_page_online_one(काष्ठा hv_hotadd_state *has, काष्ठा page *pg)
अणु
	अगर (!has_pfn_is_backed(has, page_to_pfn(pg))) अणु
		अगर (!PageOffline(pg))
			__SetPageOffline(pg);
		वापस;
	पूर्ण
	अगर (PageOffline(pg))
		__ClearPageOffline(pg);

	/* This frame is currently backed; online the page. */
	generic_online_page(pg, 0);

	lockdep_निश्चित_held(&dm_device.ha_lock);
	dm_device.num_pages_onlined++;
पूर्ण

अटल व्योम hv_bring_pgs_online(काष्ठा hv_hotadd_state *has,
				अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ size)
अणु
	पूर्णांक i;

	pr_debug("Online %lu pages starting at pfn 0x%lx\n", size, start_pfn);
	क्रम (i = 0; i < size; i++)
		hv_page_online_one(has, pfn_to_page(start_pfn + i));
पूर्ण

अटल व्योम hv_mem_hot_add(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ pfn_count,
				काष्ठा hv_hotadd_state *has)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i, nid;
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ processed_pfn;
	अचिन्हित दीर्घ total_pfn = pfn_count;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < (size/HA_CHUNK); i++) अणु
		start_pfn = start + (i * HA_CHUNK);

		spin_lock_irqsave(&dm_device.ha_lock, flags);
		has->ha_end_pfn +=  HA_CHUNK;

		अगर (total_pfn > HA_CHUNK) अणु
			processed_pfn = HA_CHUNK;
			total_pfn -= HA_CHUNK;
		पूर्ण अन्यथा अणु
			processed_pfn = total_pfn;
			total_pfn = 0;
		पूर्ण

		has->covered_end_pfn +=  processed_pfn;
		spin_unlock_irqrestore(&dm_device.ha_lock, flags);

		reinit_completion(&dm_device.ol_रुकोevent);

		nid = memory_add_physaddr_to_nid(PFN_PHYS(start_pfn));
		ret = add_memory(nid, PFN_PHYS((start_pfn)),
				(HA_CHUNK << PAGE_SHIFT), MHP_MERGE_RESOURCE);

		अगर (ret) अणु
			pr_err("hot_add memory failed error is %d\n", ret);
			अगर (ret == -EEXIST) अणु
				/*
				 * This error indicates that the error
				 * is not a transient failure. This is the
				 * हाल where the guest's physical address map
				 * precludes hot adding memory. Stop all further
				 * memory hot-add.
				 */
				करो_hot_add = false;
			पूर्ण
			spin_lock_irqsave(&dm_device.ha_lock, flags);
			has->ha_end_pfn -= HA_CHUNK;
			has->covered_end_pfn -=  processed_pfn;
			spin_unlock_irqrestore(&dm_device.ha_lock, flags);
			अवरोध;
		पूर्ण

		/*
		 * Wait क्रम memory to get onlined. If the kernel onlined the
		 * memory when adding it, this will वापस directly. Otherwise,
		 * it will रुको क्रम user space to online the memory. This helps
		 * to aव्योम adding memory faster than it is getting onlined. As
		 * adding succeeded, it is ok to proceed even अगर the memory was
		 * not onlined in समय.
		 */
		रुको_क्रम_completion_समयout(&dm_device.ol_रुकोevent, 5 * HZ);
		post_status(&dm_device);
	पूर्ण
पूर्ण

अटल व्योम hv_online_page(काष्ठा page *pg, अचिन्हित पूर्णांक order)
अणु
	काष्ठा hv_hotadd_state *has;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ pfn = page_to_pfn(pg);

	spin_lock_irqsave(&dm_device.ha_lock, flags);
	list_क्रम_each_entry(has, &dm_device.ha_region_list, list) अणु
		/* The page beदीर्घs to a dअगरferent HAS. */
		अगर ((pfn < has->start_pfn) ||
				(pfn + (1UL << order) > has->end_pfn))
			जारी;

		hv_bring_pgs_online(has, pfn, 1UL << order);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dm_device.ha_lock, flags);
पूर्ण

अटल पूर्णांक pfn_covered(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ pfn_cnt)
अणु
	काष्ठा hv_hotadd_state *has;
	काष्ठा hv_hotadd_gap *gap;
	अचिन्हित दीर्घ residual, new_inc;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dm_device.ha_lock, flags);
	list_क्रम_each_entry(has, &dm_device.ha_region_list, list) अणु
		/*
		 * If the pfn range we are dealing with is not in the current
		 * "hot add block", move on.
		 */
		अगर (start_pfn < has->start_pfn || start_pfn >= has->end_pfn)
			जारी;

		/*
		 * If the current start pfn is not where the covered_end
		 * is, create a gap and update covered_end_pfn.
		 */
		अगर (has->covered_end_pfn != start_pfn) अणु
			gap = kzalloc(माप(काष्ठा hv_hotadd_gap), GFP_ATOMIC);
			अगर (!gap) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण

			INIT_LIST_HEAD(&gap->list);
			gap->start_pfn = has->covered_end_pfn;
			gap->end_pfn = start_pfn;
			list_add_tail(&gap->list, &has->gap_list);

			has->covered_end_pfn = start_pfn;
		पूर्ण

		/*
		 * If the current hot add-request extends beyond
		 * our current limit; extend it.
		 */
		अगर ((start_pfn + pfn_cnt) > has->end_pfn) अणु
			residual = (start_pfn + pfn_cnt - has->end_pfn);
			/*
			 * Extend the region by multiples of HA_CHUNK.
			 */
			new_inc = (residual / HA_CHUNK) * HA_CHUNK;
			अगर (residual % HA_CHUNK)
				new_inc += HA_CHUNK;

			has->end_pfn += new_inc;
		पूर्ण

		ret = 1;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dm_device.ha_lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ handle_pg_range(अचिन्हित दीर्घ pg_start,
					अचिन्हित दीर्घ pg_count)
अणु
	अचिन्हित दीर्घ start_pfn = pg_start;
	अचिन्हित दीर्घ pfn_cnt = pg_count;
	अचिन्हित दीर्घ size;
	काष्ठा hv_hotadd_state *has;
	अचिन्हित दीर्घ pgs_ol = 0;
	अचिन्हित दीर्घ old_covered_state;
	अचिन्हित दीर्घ res = 0, flags;

	pr_debug("Hot adding %lu pages starting at pfn 0x%lx.\n", pg_count,
		pg_start);

	spin_lock_irqsave(&dm_device.ha_lock, flags);
	list_क्रम_each_entry(has, &dm_device.ha_region_list, list) अणु
		/*
		 * If the pfn range we are dealing with is not in the current
		 * "hot add block", move on.
		 */
		अगर (start_pfn < has->start_pfn || start_pfn >= has->end_pfn)
			जारी;

		old_covered_state = has->covered_end_pfn;

		अगर (start_pfn < has->ha_end_pfn) अणु
			/*
			 * This is the हाल where we are backing pages
			 * in an alपढ़ोy hot added region. Bring
			 * these pages online first.
			 */
			pgs_ol = has->ha_end_pfn - start_pfn;
			अगर (pgs_ol > pfn_cnt)
				pgs_ol = pfn_cnt;

			has->covered_end_pfn +=  pgs_ol;
			pfn_cnt -= pgs_ol;
			/*
			 * Check अगर the corresponding memory block is alपढ़ोy
			 * online. It is possible to observe काष्ठा pages still
			 * being uninitialized here so check section instead.
			 * In हाल the section is online we need to bring the
			 * rest of pfns (which were not backed previously)
			 * online too.
			 */
			अगर (start_pfn > has->start_pfn &&
			    online_section_nr(pfn_to_section_nr(start_pfn)))
				hv_bring_pgs_online(has, start_pfn, pgs_ol);

		पूर्ण

		अगर ((has->ha_end_pfn < has->end_pfn) && (pfn_cnt > 0)) अणु
			/*
			 * We have some residual hot add range
			 * that needs to be hot added; hot add
			 * it now. Hot add a multiple of
			 * of HA_CHUNK that fully covers the pages
			 * we have.
			 */
			size = (has->end_pfn - has->ha_end_pfn);
			अगर (pfn_cnt <= size) अणु
				size = ((pfn_cnt / HA_CHUNK) * HA_CHUNK);
				अगर (pfn_cnt % HA_CHUNK)
					size += HA_CHUNK;
			पूर्ण अन्यथा अणु
				pfn_cnt = size;
			पूर्ण
			spin_unlock_irqrestore(&dm_device.ha_lock, flags);
			hv_mem_hot_add(has->ha_end_pfn, size, pfn_cnt, has);
			spin_lock_irqsave(&dm_device.ha_lock, flags);
		पूर्ण
		/*
		 * If we managed to online any pages that were given to us,
		 * we declare success.
		 */
		res = has->covered_end_pfn - old_covered_state;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dm_device.ha_lock, flags);

	वापस res;
पूर्ण

अटल अचिन्हित दीर्घ process_hot_add(अचिन्हित दीर्घ pg_start,
					अचिन्हित दीर्घ pfn_cnt,
					अचिन्हित दीर्घ rg_start,
					अचिन्हित दीर्घ rg_size)
अणु
	काष्ठा hv_hotadd_state *ha_region = शून्य;
	पूर्णांक covered;
	अचिन्हित दीर्घ flags;

	अगर (pfn_cnt == 0)
		वापस 0;

	अगर (!dm_device.host_specअगरied_ha_region) अणु
		covered = pfn_covered(pg_start, pfn_cnt);
		अगर (covered < 0)
			वापस 0;

		अगर (covered)
			जाओ करो_pg_range;
	पूर्ण

	/*
	 * If the host has specअगरied a hot-add range; deal with it first.
	 */

	अगर (rg_size != 0) अणु
		ha_region = kzalloc(माप(काष्ठा hv_hotadd_state), GFP_KERNEL);
		अगर (!ha_region)
			वापस 0;

		INIT_LIST_HEAD(&ha_region->list);
		INIT_LIST_HEAD(&ha_region->gap_list);

		ha_region->start_pfn = rg_start;
		ha_region->ha_end_pfn = rg_start;
		ha_region->covered_start_pfn = pg_start;
		ha_region->covered_end_pfn = pg_start;
		ha_region->end_pfn = rg_start + rg_size;

		spin_lock_irqsave(&dm_device.ha_lock, flags);
		list_add_tail(&ha_region->list, &dm_device.ha_region_list);
		spin_unlock_irqrestore(&dm_device.ha_lock, flags);
	पूर्ण

करो_pg_range:
	/*
	 * Process the page range specअगरied; bringing them
	 * online अगर possible.
	 */
	वापस handle_pg_range(pg_start, pfn_cnt);
पूर्ण

#पूर्ण_अगर

अटल व्योम hot_add_req(काष्ठा work_काष्ठा *dummy)
अणु
	काष्ठा dm_hot_add_response resp;
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	अचिन्हित दीर्घ pg_start, pfn_cnt;
	अचिन्हित दीर्घ rg_start, rg_sz;
#पूर्ण_अगर
	काष्ठा hv_dynmem_device *dm = &dm_device;

	स_रखो(&resp, 0, माप(काष्ठा dm_hot_add_response));
	resp.hdr.type = DM_MEM_HOT_ADD_RESPONSE;
	resp.hdr.size = माप(काष्ठा dm_hot_add_response);

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	pg_start = dm->ha_wrk.ha_page_range.finfo.start_page;
	pfn_cnt = dm->ha_wrk.ha_page_range.finfo.page_cnt;

	rg_start = dm->ha_wrk.ha_region_range.finfo.start_page;
	rg_sz = dm->ha_wrk.ha_region_range.finfo.page_cnt;

	अगर ((rg_start == 0) && (!dm->host_specअगरied_ha_region)) अणु
		अचिन्हित दीर्घ region_size;
		अचिन्हित दीर्घ region_start;

		/*
		 * The host has not specअगरied the hot-add region.
		 * Based on the hot-add page range being specअगरied,
		 * compute a hot-add region that can cover the pages
		 * that need to be hot-added जबतक ensuring the alignment
		 * and size requirements of Linux as it relates to hot-add.
		 */
		region_start = pg_start;
		region_size = (pfn_cnt / HA_CHUNK) * HA_CHUNK;
		अगर (pfn_cnt % HA_CHUNK)
			region_size += HA_CHUNK;

		region_start = (pg_start / HA_CHUNK) * HA_CHUNK;

		rg_start = region_start;
		rg_sz = region_size;
	पूर्ण

	अगर (करो_hot_add)
		resp.page_count = process_hot_add(pg_start, pfn_cnt,
						rg_start, rg_sz);

	dm->num_pages_added += resp.page_count;
#पूर्ण_अगर
	/*
	 * The result field of the response काष्ठाure has the
	 * following semantics:
	 *
	 * 1. If all or some pages hot-added: Guest should वापस success.
	 *
	 * 2. If no pages could be hot-added:
	 *
	 * If the guest वापसs success, then the host
	 * will not attempt any further hot-add operations. This
	 * signअगरies a permanent failure.
	 *
	 * If the guest वापसs failure, then this failure will be
	 * treated as a transient failure and the host may retry the
	 * hot-add operation after some delay.
	 */
	अगर (resp.page_count > 0)
		resp.result = 1;
	अन्यथा अगर (!करो_hot_add)
		resp.result = 1;
	अन्यथा
		resp.result = 0;

	अगर (!करो_hot_add || resp.page_count == 0) अणु
		अगर (!allow_hibernation)
			pr_err("Memory hot add failed\n");
		अन्यथा
			pr_info("Ignore hot-add request!\n");
	पूर्ण

	dm->state = DM_INITIALIZED;
	resp.hdr.trans_id = atomic_inc_वापस(&trans_id);
	vmbus_sendpacket(dm->dev->channel, &resp,
			माप(काष्ठा dm_hot_add_response),
			(अचिन्हित दीर्घ)शून्य,
			VM_PKT_DATA_INBAND, 0);
पूर्ण

अटल व्योम process_info(काष्ठा hv_dynmem_device *dm, काष्ठा dm_info_msg *msg)
अणु
	काष्ठा dm_info_header *info_hdr;

	info_hdr = (काष्ठा dm_info_header *)msg->info;

	चयन (info_hdr->type) अणु
	हाल INFO_TYPE_MAX_PAGE_CNT:
		अगर (info_hdr->data_size == माप(__u64)) अणु
			__u64 *max_page_count = (__u64 *)&info_hdr[1];

			pr_info("Max. dynamic memory size: %llu MB\n",
				(*max_page_count) >> (20 - HV_HYP_PAGE_SHIFT));
		पूर्ण

		अवरोध;
	शेष:
		pr_warn("Received Unknown type: %d\n", info_hdr->type);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ compute_balloon_न्यूनमान(व्योम)
अणु
	अचिन्हित दीर्घ min_pages;
	अचिन्हित दीर्घ nr_pages = totalram_pages();
#घोषणा MB2PAGES(mb) ((mb) << (20 - PAGE_SHIFT))
	/* Simple continuous piecewiese linear function:
	 *  max MiB -> min MiB  gradient
	 *       0         0
	 *      16        16
	 *      32        24
	 *     128        72    (1/2)
	 *     512       168    (1/4)
	 *    2048       360    (1/8)
	 *    8192       744    (1/16)
	 *   32768      1512	(1/32)
	 */
	अगर (nr_pages < MB2PAGES(128))
		min_pages = MB2PAGES(8) + (nr_pages >> 1);
	अन्यथा अगर (nr_pages < MB2PAGES(512))
		min_pages = MB2PAGES(40) + (nr_pages >> 2);
	अन्यथा अगर (nr_pages < MB2PAGES(2048))
		min_pages = MB2PAGES(104) + (nr_pages >> 3);
	अन्यथा अगर (nr_pages < MB2PAGES(8192))
		min_pages = MB2PAGES(232) + (nr_pages >> 4);
	अन्यथा
		min_pages = MB2PAGES(488) + (nr_pages >> 5);
#अघोषित MB2PAGES
	वापस min_pages;
पूर्ण

/*
 * Post our status as it relates memory pressure to the
 * host. Host expects the guests to post this status
 * periodically at 1 second पूर्णांकervals.
 *
 * The metrics specअगरied in this protocol are very Winकरोws
 * specअगरic and so we cook up numbers here to convey our memory
 * pressure.
 */

अटल व्योम post_status(काष्ठा hv_dynmem_device *dm)
अणु
	काष्ठा dm_status status;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ last_post = last_post_समय;

	अगर (pressure_report_delay > 0) अणु
		--pressure_report_delay;
		वापस;
	पूर्ण

	अगर (!समय_after(now, (last_post_समय + HZ)))
		वापस;

	स_रखो(&status, 0, माप(काष्ठा dm_status));
	status.hdr.type = DM_STATUS_REPORT;
	status.hdr.size = माप(काष्ठा dm_status);
	status.hdr.trans_id = atomic_inc_वापस(&trans_id);

	/*
	 * The host expects the guest to report मुक्त and committed memory.
	 * Furthermore, the host expects the pressure inक्रमmation to include
	 * the ballooned out pages. For a given amount of memory that we are
	 * managing we need to compute a न्यूनमान below which we should not
	 * balloon. Compute this and add it to the pressure report.
	 * We also need to report all offline pages (num_pages_added -
	 * num_pages_onlined) as committed to the host, otherwise it can try
	 * asking us to balloon them out.
	 */
	status.num_avail = si_mem_available();
	status.num_committed = vm_memory_committed() +
		dm->num_pages_ballooned +
		(dm->num_pages_added > dm->num_pages_onlined ?
		 dm->num_pages_added - dm->num_pages_onlined : 0) +
		compute_balloon_न्यूनमान();

	trace_balloon_status(status.num_avail, status.num_committed,
			     vm_memory_committed(), dm->num_pages_ballooned,
			     dm->num_pages_added, dm->num_pages_onlined);
	/*
	 * If our transaction ID is no दीर्घer current, just करोn't
	 * send the status. This can happen अगर we were पूर्णांकerrupted
	 * after we picked our transaction ID.
	 */
	अगर (status.hdr.trans_id != atomic_पढ़ो(&trans_id))
		वापस;

	/*
	 * If the last post समय that we sampled has changed,
	 * we have raced, करोn't post the status.
	 */
	अगर (last_post != last_post_समय)
		वापस;

	last_post_समय = jअगरfies;
	vmbus_sendpacket(dm->dev->channel, &status,
				माप(काष्ठा dm_status),
				(अचिन्हित दीर्घ)शून्य,
				VM_PKT_DATA_INBAND, 0);

पूर्ण

अटल व्योम मुक्त_balloon_pages(काष्ठा hv_dynmem_device *dm,
			 जोड़ dm_mem_page_range *range_array)
अणु
	पूर्णांक num_pages = range_array->finfo.page_cnt;
	__u64 start_frame = range_array->finfo.start_page;
	काष्ठा page *pg;
	पूर्णांक i;

	क्रम (i = 0; i < num_pages; i++) अणु
		pg = pfn_to_page(i + start_frame);
		__ClearPageOffline(pg);
		__मुक्त_page(pg);
		dm->num_pages_ballooned--;
		adjust_managed_page_count(pg, 1);
	पूर्ण
पूर्ण



अटल अचिन्हित पूर्णांक alloc_balloon_pages(काष्ठा hv_dynmem_device *dm,
					अचिन्हित पूर्णांक num_pages,
					काष्ठा dm_balloon_response *bl_resp,
					पूर्णांक alloc_unit)
अणु
	अचिन्हित पूर्णांक i, j;
	काष्ठा page *pg;

	क्रम (i = 0; i < num_pages / alloc_unit; i++) अणु
		अगर (bl_resp->hdr.size + माप(जोड़ dm_mem_page_range) >
			HV_HYP_PAGE_SIZE)
			वापस i * alloc_unit;

		/*
		 * We execute this code in a thपढ़ो context. Furthermore,
		 * we करोn't want the kernel to try too hard.
		 */
		pg = alloc_pages(GFP_HIGHUSER | __GFP_NORETRY |
				__GFP_NOMEMALLOC | __GFP_NOWARN,
				get_order(alloc_unit << PAGE_SHIFT));

		अगर (!pg)
			वापस i * alloc_unit;

		dm->num_pages_ballooned += alloc_unit;

		/*
		 * If we allocatted 2M pages; split them so we
		 * can मुक्त them in any order we get.
		 */

		अगर (alloc_unit != 1)
			split_page(pg, get_order(alloc_unit << PAGE_SHIFT));

		/* mark all pages offline */
		क्रम (j = 0; j < alloc_unit; j++) अणु
			__SetPageOffline(pg + j);
			adjust_managed_page_count(pg + j, -1);
		पूर्ण

		bl_resp->range_count++;
		bl_resp->range_array[i].finfo.start_page =
			page_to_pfn(pg);
		bl_resp->range_array[i].finfo.page_cnt = alloc_unit;
		bl_resp->hdr.size += माप(जोड़ dm_mem_page_range);

	पूर्ण

	वापस i * alloc_unit;
पूर्ण

अटल व्योम balloon_up(काष्ठा work_काष्ठा *dummy)
अणु
	अचिन्हित पूर्णांक num_pages = dm_device.balloon_wrk.num_pages;
	अचिन्हित पूर्णांक num_ballooned = 0;
	काष्ठा dm_balloon_response *bl_resp;
	पूर्णांक alloc_unit;
	पूर्णांक ret;
	bool करोne = false;
	पूर्णांक i;
	दीर्घ avail_pages;
	अचिन्हित दीर्घ न्यूनमान;

	/*
	 * We will attempt 2M allocations. However, अगर we fail to
	 * allocate 2M chunks, we will go back to PAGE_SIZE allocations.
	 */
	alloc_unit = PAGES_IN_2M;

	avail_pages = si_mem_available();
	न्यूनमान = compute_balloon_न्यूनमान();

	/* Refuse to balloon below the न्यूनमान. */
	अगर (avail_pages < num_pages || avail_pages - num_pages < न्यूनमान) अणु
		pr_info("Balloon request will be partially fulfilled. %s\n",
			avail_pages < num_pages ? "Not enough memory." :
			"Balloon floor reached.");

		num_pages = avail_pages > न्यूनमान ? (avail_pages - न्यूनमान) : 0;
	पूर्ण

	जबतक (!करोne) अणु
		स_रखो(balloon_up_send_buffer, 0, HV_HYP_PAGE_SIZE);
		bl_resp = (काष्ठा dm_balloon_response *)balloon_up_send_buffer;
		bl_resp->hdr.type = DM_BALLOON_RESPONSE;
		bl_resp->hdr.size = माप(काष्ठा dm_balloon_response);
		bl_resp->more_pages = 1;

		num_pages -= num_ballooned;
		num_ballooned = alloc_balloon_pages(&dm_device, num_pages,
						    bl_resp, alloc_unit);

		अगर (alloc_unit != 1 && num_ballooned == 0) अणु
			alloc_unit = 1;
			जारी;
		पूर्ण

		अगर (num_ballooned == 0 || num_ballooned == num_pages) अणु
			pr_debug("Ballooned %u out of %u requested pages.\n",
				num_pages, dm_device.balloon_wrk.num_pages);

			bl_resp->more_pages = 0;
			करोne = true;
			dm_device.state = DM_INITIALIZED;
		पूर्ण

		/*
		 * We are pushing a lot of data through the channel;
		 * deal with transient failures caused because of the
		 * lack of space in the ring buffer.
		 */

		करो अणु
			bl_resp->hdr.trans_id = atomic_inc_वापस(&trans_id);
			ret = vmbus_sendpacket(dm_device.dev->channel,
						bl_resp,
						bl_resp->hdr.size,
						(अचिन्हित दीर्घ)शून्य,
						VM_PKT_DATA_INBAND, 0);

			अगर (ret == -EAGAIN)
				msleep(20);
			post_status(&dm_device);
		पूर्ण जबतक (ret == -EAGAIN);

		अगर (ret) अणु
			/*
			 * Free up the memory we allocatted.
			 */
			pr_err("Balloon response failed\n");

			क्रम (i = 0; i < bl_resp->range_count; i++)
				मुक्त_balloon_pages(&dm_device,
						 &bl_resp->range_array[i]);

			करोne = true;
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम balloon_करोwn(काष्ठा hv_dynmem_device *dm,
			काष्ठा dm_unballoon_request *req)
अणु
	जोड़ dm_mem_page_range *range_array = req->range_array;
	पूर्णांक range_count = req->range_count;
	काष्ठा dm_unballoon_response resp;
	पूर्णांक i;
	अचिन्हित पूर्णांक prev_pages_ballooned = dm->num_pages_ballooned;

	क्रम (i = 0; i < range_count; i++) अणु
		मुक्त_balloon_pages(dm, &range_array[i]);
		complete(&dm_device.config_event);
	पूर्ण

	pr_debug("Freed %u ballooned pages.\n",
		prev_pages_ballooned - dm->num_pages_ballooned);

	अगर (req->more_pages == 1)
		वापस;

	स_रखो(&resp, 0, माप(काष्ठा dm_unballoon_response));
	resp.hdr.type = DM_UNBALLOON_RESPONSE;
	resp.hdr.trans_id = atomic_inc_वापस(&trans_id);
	resp.hdr.size = माप(काष्ठा dm_unballoon_response);

	vmbus_sendpacket(dm_device.dev->channel, &resp,
				माप(काष्ठा dm_unballoon_response),
				(अचिन्हित दीर्घ)शून्य,
				VM_PKT_DATA_INBAND, 0);

	dm->state = DM_INITIALIZED;
पूर्ण

अटल व्योम balloon_onchannelcallback(व्योम *context);

अटल पूर्णांक dm_thपढ़ो_func(व्योम *dm_dev)
अणु
	काष्ठा hv_dynmem_device *dm = dm_dev;

	जबतक (!kthपढ़ो_should_stop()) अणु
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(
						&dm_device.config_event, 1*HZ);
		/*
		 * The host expects us to post inक्रमmation on the memory
		 * pressure every second.
		 */
		reinit_completion(&dm_device.config_event);
		post_status(dm);
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम version_resp(काष्ठा hv_dynmem_device *dm,
			काष्ठा dm_version_response *vresp)
अणु
	काष्ठा dm_version_request version_req;
	पूर्णांक ret;

	अगर (vresp->is_accepted) अणु
		/*
		 * We are करोne; wakeup the
		 * context रुकोing क्रम version
		 * negotiation.
		 */
		complete(&dm->host_event);
		वापस;
	पूर्ण
	/*
	 * If there are more versions to try, जारी
	 * with negotiations; अगर not
	 * shutकरोwn the service since we are not able
	 * to negotiate a suitable version number
	 * with the host.
	 */
	अगर (dm->next_version == 0)
		जाओ version_error;

	स_रखो(&version_req, 0, माप(काष्ठा dm_version_request));
	version_req.hdr.type = DM_VERSION_REQUEST;
	version_req.hdr.size = माप(काष्ठा dm_version_request);
	version_req.hdr.trans_id = atomic_inc_वापस(&trans_id);
	version_req.version.version = dm->next_version;
	dm->version = version_req.version.version;

	/*
	 * Set the next version to try in हाल current version fails.
	 * Win7 protocol ought to be the last one to try.
	 */
	चयन (version_req.version.version) अणु
	हाल DYNMEM_PROTOCOL_VERSION_WIN8:
		dm->next_version = DYNMEM_PROTOCOL_VERSION_WIN7;
		version_req.is_last_attempt = 0;
		अवरोध;
	शेष:
		dm->next_version = 0;
		version_req.is_last_attempt = 1;
	पूर्ण

	ret = vmbus_sendpacket(dm->dev->channel, &version_req,
				माप(काष्ठा dm_version_request),
				(अचिन्हित दीर्घ)शून्य,
				VM_PKT_DATA_INBAND, 0);

	अगर (ret)
		जाओ version_error;

	वापस;

version_error:
	dm->state = DM_INIT_ERROR;
	complete(&dm->host_event);
पूर्ण

अटल व्योम cap_resp(काष्ठा hv_dynmem_device *dm,
			काष्ठा dm_capabilities_resp_msg *cap_resp)
अणु
	अगर (!cap_resp->is_accepted) अणु
		pr_err("Capabilities not accepted by host\n");
		dm->state = DM_INIT_ERROR;
	पूर्ण
	complete(&dm->host_event);
पूर्ण

अटल व्योम balloon_onchannelcallback(व्योम *context)
अणु
	काष्ठा hv_device *dev = context;
	u32 recvlen;
	u64 requestid;
	काष्ठा dm_message *dm_msg;
	काष्ठा dm_header *dm_hdr;
	काष्ठा hv_dynmem_device *dm = hv_get_drvdata(dev);
	काष्ठा dm_balloon *bal_msg;
	काष्ठा dm_hot_add *ha_msg;
	जोड़ dm_mem_page_range *ha_pg_range;
	जोड़ dm_mem_page_range *ha_region;

	स_रखो(recv_buffer, 0, माप(recv_buffer));
	vmbus_recvpacket(dev->channel, recv_buffer,
			 HV_HYP_PAGE_SIZE, &recvlen, &requestid);

	अगर (recvlen > 0) अणु
		dm_msg = (काष्ठा dm_message *)recv_buffer;
		dm_hdr = &dm_msg->hdr;

		चयन (dm_hdr->type) अणु
		हाल DM_VERSION_RESPONSE:
			version_resp(dm,
				 (काष्ठा dm_version_response *)dm_msg);
			अवरोध;

		हाल DM_CAPABILITIES_RESPONSE:
			cap_resp(dm,
				 (काष्ठा dm_capabilities_resp_msg *)dm_msg);
			अवरोध;

		हाल DM_BALLOON_REQUEST:
			अगर (allow_hibernation) अणु
				pr_info("Ignore balloon-up request!\n");
				अवरोध;
			पूर्ण

			अगर (dm->state == DM_BALLOON_UP)
				pr_warn("Currently ballooning\n");
			bal_msg = (काष्ठा dm_balloon *)recv_buffer;
			dm->state = DM_BALLOON_UP;
			dm_device.balloon_wrk.num_pages = bal_msg->num_pages;
			schedule_work(&dm_device.balloon_wrk.wrk);
			अवरोध;

		हाल DM_UNBALLOON_REQUEST:
			अगर (allow_hibernation) अणु
				pr_info("Ignore balloon-down request!\n");
				अवरोध;
			पूर्ण

			dm->state = DM_BALLOON_DOWN;
			balloon_करोwn(dm,
				 (काष्ठा dm_unballoon_request *)recv_buffer);
			अवरोध;

		हाल DM_MEM_HOT_ADD_REQUEST:
			अगर (dm->state == DM_HOT_ADD)
				pr_warn("Currently hot-adding\n");
			dm->state = DM_HOT_ADD;
			ha_msg = (काष्ठा dm_hot_add *)recv_buffer;
			अगर (ha_msg->hdr.size == माप(काष्ठा dm_hot_add)) अणु
				/*
				 * This is a normal hot-add request specअगरying
				 * hot-add memory.
				 */
				dm->host_specअगरied_ha_region = false;
				ha_pg_range = &ha_msg->range;
				dm->ha_wrk.ha_page_range = *ha_pg_range;
				dm->ha_wrk.ha_region_range.page_range = 0;
			पूर्ण अन्यथा अणु
				/*
				 * Host is specअगरying that we first hot-add
				 * a region and then partially populate this
				 * region.
				 */
				dm->host_specअगरied_ha_region = true;
				ha_pg_range = &ha_msg->range;
				ha_region = &ha_pg_range[1];
				dm->ha_wrk.ha_page_range = *ha_pg_range;
				dm->ha_wrk.ha_region_range = *ha_region;
			पूर्ण
			schedule_work(&dm_device.ha_wrk.wrk);
			अवरोध;

		हाल DM_INFO_MESSAGE:
			process_info(dm, (काष्ठा dm_info_msg *)dm_msg);
			अवरोध;

		शेष:
			pr_warn("Unhandled message: type: %d\n", dm_hdr->type);

		पूर्ण
	पूर्ण

पूर्ण

/* Hyper-V only supports reporting 2MB pages or higher */
#घोषणा HV_MIN_PAGE_REPORTING_ORDER	9
#घोषणा HV_MIN_PAGE_REPORTING_LEN (HV_HYP_PAGE_SIZE << HV_MIN_PAGE_REPORTING_ORDER)
अटल पूर्णांक hv_मुक्त_page_report(काष्ठा page_reporting_dev_info *pr_dev_info,
		    काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक nents)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hv_memory_hपूर्णांक *hपूर्णांक;
	पूर्णांक i;
	u64 status;
	काष्ठा scatterlist *sg;

	WARN_ON_ONCE(nents > HV_MEMORY_Hपूर्णांक_उच्च_GPA_PAGE_RANGES);
	WARN_ON_ONCE(sgl->length < HV_MIN_PAGE_REPORTING_LEN);
	local_irq_save(flags);
	hपूर्णांक = *(काष्ठा hv_memory_hपूर्णांक **)this_cpu_ptr(hyperv_pcpu_input_arg);
	अगर (!hपूर्णांक) अणु
		local_irq_restore(flags);
		वापस -ENOSPC;
	पूर्ण

	hपूर्णांक->type = HV_EXT_MEMORY_HEAT_HINT_TYPE_COLD_DISCARD;
	hपूर्णांक->reserved = 0;
	क्रम_each_sg(sgl, sg, nents, i) अणु
		जोड़ hv_gpa_page_range *range;

		range = &hपूर्णांक->ranges[i];
		range->address_space = 0;
		/* page reporting only reports 2MB pages or higher */
		range->page.largepage = 1;
		range->page.additional_pages =
			(sg->length / HV_MIN_PAGE_REPORTING_LEN) - 1;
		range->page_size = HV_GPA_PAGE_RANGE_PAGE_SIZE_2MB;
		range->base_large_pfn =
			page_to_hvpfn(sg_page(sg)) >> HV_MIN_PAGE_REPORTING_ORDER;
	पूर्ण

	status = hv_करो_rep_hypercall(HV_EXT_CALL_MEMORY_HEAT_HINT, nents, 0,
				     hपूर्णांक, शून्य);
	local_irq_restore(flags);
	अगर ((status & HV_HYPERCALL_RESULT_MASK) != HV_STATUS_SUCCESS) अणु
		pr_err("Cold memory discard hypercall failed with status %llx\n",
			status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम enable_page_reporting(व्योम)
अणु
	पूर्णांक ret;

	/* Essentially, validating 'PAGE_REPORTING_MIN_ORDER' is big enough. */
	अगर (pageblock_order < HV_MIN_PAGE_REPORTING_ORDER) अणु
		pr_debug("Cold memory discard is only supported on 2MB pages and above\n");
		वापस;
	पूर्ण

	अगर (!hv_query_ext_cap(HV_EXT_CAPABILITY_MEMORY_COLD_DISCARD_HINT)) अणु
		pr_debug("Cold memory discard hint not supported by Hyper-V\n");
		वापस;
	पूर्ण

	BUILD_BUG_ON(PAGE_REPORTING_CAPACITY > HV_MEMORY_Hपूर्णांक_उच्च_GPA_PAGE_RANGES);
	dm_device.pr_dev_info.report = hv_मुक्त_page_report;
	ret = page_reporting_रेजिस्टर(&dm_device.pr_dev_info);
	अगर (ret < 0) अणु
		dm_device.pr_dev_info.report = शून्य;
		pr_err("Failed to enable cold memory discard: %d\n", ret);
	पूर्ण अन्यथा अणु
		pr_info("Cold memory discard hint enabled\n");
	पूर्ण
पूर्ण

अटल व्योम disable_page_reporting(व्योम)
अणु
	अगर (dm_device.pr_dev_info.report) अणु
		page_reporting_unरेजिस्टर(&dm_device.pr_dev_info);
		dm_device.pr_dev_info.report = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक balloon_connect_vsp(काष्ठा hv_device *dev)
अणु
	काष्ठा dm_version_request version_req;
	काष्ठा dm_capabilities cap_msg;
	अचिन्हित दीर्घ t;
	पूर्णांक ret;

	ret = vmbus_खोलो(dev->channel, dm_ring_size, dm_ring_size, शून्य, 0,
			 balloon_onchannelcallback, dev);
	अगर (ret)
		वापस ret;

	/*
	 * Initiate the hand shake with the host and negotiate
	 * a version that the host can support. We start with the
	 * highest version number and go करोwn अगर the host cannot
	 * support it.
	 */
	स_रखो(&version_req, 0, माप(काष्ठा dm_version_request));
	version_req.hdr.type = DM_VERSION_REQUEST;
	version_req.hdr.size = माप(काष्ठा dm_version_request);
	version_req.hdr.trans_id = atomic_inc_वापस(&trans_id);
	version_req.version.version = DYNMEM_PROTOCOL_VERSION_WIN10;
	version_req.is_last_attempt = 0;
	dm_device.version = version_req.version.version;

	ret = vmbus_sendpacket(dev->channel, &version_req,
			       माप(काष्ठा dm_version_request),
			       (अचिन्हित दीर्घ)शून्य, VM_PKT_DATA_INBAND, 0);
	अगर (ret)
		जाओ out;

	t = रुको_क्रम_completion_समयout(&dm_device.host_event, 5*HZ);
	अगर (t == 0) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/*
	 * If we could not negotiate a compatible version with the host
	 * fail the probe function.
	 */
	अगर (dm_device.state == DM_INIT_ERROR) अणु
		ret = -EPROTO;
		जाओ out;
	पूर्ण

	pr_info("Using Dynamic Memory protocol version %u.%u\n",
		DYNMEM_MAJOR_VERSION(dm_device.version),
		DYNMEM_MINOR_VERSION(dm_device.version));

	/*
	 * Now submit our capabilities to the host.
	 */
	स_रखो(&cap_msg, 0, माप(काष्ठा dm_capabilities));
	cap_msg.hdr.type = DM_CAPABILITIES_REPORT;
	cap_msg.hdr.size = माप(काष्ठा dm_capabilities);
	cap_msg.hdr.trans_id = atomic_inc_वापस(&trans_id);

	/*
	 * When hibernation (i.e. भव ACPI S4 state) is enabled, the host
	 * currently still requires the bits to be set, so we have to add code
	 * to fail the host's hot-add and balloon up/करोwn requests, अगर any.
	 */
	cap_msg.caps.cap_bits.balloon = 1;
	cap_msg.caps.cap_bits.hot_add = 1;

	/*
	 * Specअगरy our alignment requirements as it relates
	 * memory hot-add. Specअगरy 128MB alignment.
	 */
	cap_msg.caps.cap_bits.hot_add_alignment = 7;

	/*
	 * Currently the host करोes not use these
	 * values and we set them to what is करोne in the
	 * Winकरोws driver.
	 */
	cap_msg.min_page_cnt = 0;
	cap_msg.max_page_number = -1;

	ret = vmbus_sendpacket(dev->channel, &cap_msg,
			       माप(काष्ठा dm_capabilities),
			       (अचिन्हित दीर्घ)शून्य, VM_PKT_DATA_INBAND, 0);
	अगर (ret)
		जाओ out;

	t = रुको_क्रम_completion_समयout(&dm_device.host_event, 5*HZ);
	अगर (t == 0) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/*
	 * If the host करोes not like our capabilities,
	 * fail the probe function.
	 */
	अगर (dm_device.state == DM_INIT_ERROR) अणु
		ret = -EPROTO;
		जाओ out;
	पूर्ण

	वापस 0;
out:
	vmbus_बंद(dev->channel);
	वापस ret;
पूर्ण

अटल पूर्णांक balloon_probe(काष्ठा hv_device *dev,
			 स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	पूर्णांक ret;

	allow_hibernation = hv_is_hibernation_supported();
	अगर (allow_hibernation)
		hot_add = false;

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	करो_hot_add = hot_add;
#अन्यथा
	करो_hot_add = false;
#पूर्ण_अगर
	dm_device.dev = dev;
	dm_device.state = DM_INITIALIZING;
	dm_device.next_version = DYNMEM_PROTOCOL_VERSION_WIN8;
	init_completion(&dm_device.host_event);
	init_completion(&dm_device.config_event);
	INIT_LIST_HEAD(&dm_device.ha_region_list);
	spin_lock_init(&dm_device.ha_lock);
	INIT_WORK(&dm_device.balloon_wrk.wrk, balloon_up);
	INIT_WORK(&dm_device.ha_wrk.wrk, hot_add_req);
	dm_device.host_specअगरied_ha_region = false;

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	set_online_page_callback(&hv_online_page);
	init_completion(&dm_device.ol_रुकोevent);
	रेजिस्टर_memory_notअगरier(&hv_memory_nb);
#पूर्ण_अगर

	hv_set_drvdata(dev, &dm_device);

	ret = balloon_connect_vsp(dev);
	अगर (ret != 0)
		वापस ret;

	enable_page_reporting();
	dm_device.state = DM_INITIALIZED;

	dm_device.thपढ़ो =
		 kthपढ़ो_run(dm_thपढ़ो_func, &dm_device, "hv_balloon");
	अगर (IS_ERR(dm_device.thपढ़ो)) अणु
		ret = PTR_ERR(dm_device.thपढ़ो);
		जाओ probe_error;
	पूर्ण

	वापस 0;

probe_error:
	dm_device.state = DM_INIT_ERROR;
	dm_device.thपढ़ो  = शून्य;
	disable_page_reporting();
	vmbus_बंद(dev->channel);
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	unरेजिस्टर_memory_notअगरier(&hv_memory_nb);
	restore_online_page_callback(&hv_online_page);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल पूर्णांक balloon_हटाओ(काष्ठा hv_device *dev)
अणु
	काष्ठा hv_dynmem_device *dm = hv_get_drvdata(dev);
	काष्ठा hv_hotadd_state *has, *पंचांगp;
	काष्ठा hv_hotadd_gap *gap, *पंचांगp_gap;
	अचिन्हित दीर्घ flags;

	अगर (dm->num_pages_ballooned != 0)
		pr_warn("Ballooned pages: %d\n", dm->num_pages_ballooned);

	cancel_work_sync(&dm->balloon_wrk.wrk);
	cancel_work_sync(&dm->ha_wrk.wrk);

	kthपढ़ो_stop(dm->thपढ़ो);
	disable_page_reporting();
	vmbus_बंद(dev->channel);
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	unरेजिस्टर_memory_notअगरier(&hv_memory_nb);
	restore_online_page_callback(&hv_online_page);
#पूर्ण_अगर
	spin_lock_irqsave(&dm_device.ha_lock, flags);
	list_क्रम_each_entry_safe(has, पंचांगp, &dm->ha_region_list, list) अणु
		list_क्रम_each_entry_safe(gap, पंचांगp_gap, &has->gap_list, list) अणु
			list_del(&gap->list);
			kमुक्त(gap);
		पूर्ण
		list_del(&has->list);
		kमुक्त(has);
	पूर्ण
	spin_unlock_irqrestore(&dm_device.ha_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक balloon_suspend(काष्ठा hv_device *hv_dev)
अणु
	काष्ठा hv_dynmem_device *dm = hv_get_drvdata(hv_dev);

	tasklet_disable(&hv_dev->channel->callback_event);

	cancel_work_sync(&dm->balloon_wrk.wrk);
	cancel_work_sync(&dm->ha_wrk.wrk);

	अगर (dm->thपढ़ो) अणु
		kthपढ़ो_stop(dm->thपढ़ो);
		dm->thपढ़ो = शून्य;
		vmbus_बंद(hv_dev->channel);
	पूर्ण

	tasklet_enable(&hv_dev->channel->callback_event);

	वापस 0;

पूर्ण

अटल पूर्णांक balloon_resume(काष्ठा hv_device *dev)
अणु
	पूर्णांक ret;

	dm_device.state = DM_INITIALIZING;

	ret = balloon_connect_vsp(dev);

	अगर (ret != 0)
		जाओ out;

	dm_device.thपढ़ो =
		 kthपढ़ो_run(dm_thपढ़ो_func, &dm_device, "hv_balloon");
	अगर (IS_ERR(dm_device.thपढ़ो)) अणु
		ret = PTR_ERR(dm_device.thपढ़ो);
		dm_device.thपढ़ो = शून्य;
		जाओ बंद_channel;
	पूर्ण

	dm_device.state = DM_INITIALIZED;
	वापस 0;
बंद_channel:
	vmbus_बंद(dev->channel);
out:
	dm_device.state = DM_INIT_ERROR;
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	unरेजिस्टर_memory_notअगरier(&hv_memory_nb);
	restore_online_page_callback(&hv_online_page);
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	/* Dynamic Memory Class ID */
	/* 525074DC-8985-46e2-8057-A307DC18A502 */
	अणु HV_DM_GUID, पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vmbus, id_table);

अटल  काष्ठा hv_driver balloon_drv = अणु
	.name = "hv_balloon",
	.id_table = id_table,
	.probe =  balloon_probe,
	.हटाओ =  balloon_हटाओ,
	.suspend = balloon_suspend,
	.resume = balloon_resume,
	.driver = अणु
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init init_balloon_drv(व्योम)
अणु

	वापस vmbus_driver_रेजिस्टर(&balloon_drv);
पूर्ण

module_init(init_balloon_drv);

MODULE_DESCRIPTION("Hyper-V Balloon");
MODULE_LICENSE("GPL");
