<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR CDDL-1.0) */
/* Copyright (C) 2010-2016 Oracle Corporation */

#अगर_अघोषित __VBOXGUEST_CORE_H__
#घोषणा __VBOXGUEST_CORE_H__

#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/vboxguest.h>
#समावेश "vmmdev.h"

/*
 * The मुख्यline kernel version (this version) of the vboxguest module
 * contained a bug where it defined VBGL_IOCTL_VMMDEV_REQUEST_BIG and
 * VBGL_IOCTL_LOG using _IOC(_IOC_READ | _IOC_WRITE, 'V', ...) instead
 * of _IO(V, ...) as the out of tree VirtualBox upstream version करोes.
 *
 * These _ALT definitions keep compatibility with the wrong defines the
 * मुख्यline kernel version used क्रम a जबतक.
 * Note the VirtualBox userspace bits have always been built against
 * VirtualBox upstream's headers, so this is likely not necessary. But
 * we must never अवरोध our ABI so we keep these around to be 100% sure.
 */
#घोषणा VBG_IOCTL_VMMDEV_REQUEST_BIG_ALT _IOC(_IOC_READ | _IOC_WRITE, 'V', 3, 0)
#घोषणा VBG_IOCTL_LOG_ALT(s)             _IOC(_IOC_READ | _IOC_WRITE, 'V', 9, s)

काष्ठा vbg_session;

/** VBox guest memory balloon. */
काष्ठा vbg_mem_balloon अणु
	/** Work handling VMMDEV_EVENT_BALLOON_CHANGE_REQUEST events */
	काष्ठा work_काष्ठा work;
	/** Pre-allocated vmmdev_memballoon_info req क्रम query */
	काष्ठा vmmdev_memballoon_info *get_req;
	/** Pre-allocated vmmdev_memballoon_change req क्रम inflate / deflate */
	काष्ठा vmmdev_memballoon_change *change_req;
	/** The current number of chunks in the balloon. */
	u32 chunks;
	/** The maximum number of chunks in the balloon. */
	u32 max_chunks;
	/**
	 * Array of poपूर्णांकers to page arrays. A page * array is allocated क्रम
	 * each chunk when inflating, and मुक्तd when the deflating.
	 */
	काष्ठा page ***pages;
पूर्ण;

/**
 * Per bit usage tracker क्रम a u32 mask.
 *
 * Used क्रम optimal handling of guest properties and event filter.
 */
काष्ठा vbg_bit_usage_tracker अणु
	/** Per bit usage counters. */
	u32 per_bit_usage[32];
	/** The current mask according to per_bit_usage. */
	u32 mask;
पूर्ण;

/** VBox guest device (data) extension. */
काष्ठा vbg_dev अणु
	काष्ठा device *dev;
	/** The base of the adapter I/O ports. */
	u16 io_port;
	/** Poपूर्णांकer to the mapping of the VMMDev adapter memory. */
	काष्ठा vmmdev_memory *mmio;
	/** Host version */
	अक्षर host_version[64];
	/** Host features */
	अचिन्हित पूर्णांक host_features;
	/**
	 * Dummy page and vmap address क्रम reserved kernel भव-address
	 * space क्रम the guest mappings, only used on hosts lacking vtx.
	 */
	काष्ठा page *guest_mappings_dummy_page;
	व्योम *guest_mappings;
	/** Spinlock protecting pending_events. */
	spinlock_t event_spinlock;
	/** Pपुनः_स्मृतिated काष्ठा vmmdev_events क्रम the IRQ handler. */
	काष्ठा vmmdev_events *ack_events_req;
	/** Wait-क्रम-event list क्रम thपढ़ोs रुकोing क्रम multiple events. */
	रुको_queue_head_t event_wq;
	/** Mask of pending events. */
	u32 pending_events;
	/** Wait-क्रम-event list क्रम thपढ़ोs रुकोing on HGCM async completion. */
	रुको_queue_head_t hgcm_wq;
	/** Pre-allocated hgcm cancel2 req. क्रम cancellation on समयout */
	काष्ठा vmmdev_hgcm_cancel2 *cancel_req;
	/** Mutex protecting cancel_req accesses */
	काष्ठा mutex cancel_req_mutex;
	/** Pre-allocated mouse-status request क्रम the input-device handling. */
	काष्ठा vmmdev_mouse_status *mouse_status_req;
	/** Input device क्रम reporting असल mouse coordinates to the guest. */
	काष्ठा input_dev *input;

	/** Memory balloon inक्रमmation. */
	काष्ठा vbg_mem_balloon mem_balloon;

	/** Lock क्रम session related items in vbg_dev and vbg_session */
	काष्ठा mutex session_mutex;
	/** Events we won't permit anyone to filter out. */
	u32 fixed_events;
	/**
	 * Usage counters क्रम the host events (excludes fixed events),
	 * Protected by session_mutex.
	 */
	काष्ठा vbg_bit_usage_tracker event_filter_tracker;
	/**
	 * The event filter last reported to the host (or UINT32_MAX).
	 * Protected by session_mutex.
	 */
	u32 event_filter_host;

	/**
	 * Guest capabilities which have been चयनed to acquire_mode.
	 */
	u32 acquire_mode_guest_caps;
	/**
	 * Guest capabilities acquired by vbg_acquire_session_capabilities().
	 * Only one session can acquire a capability at a समय.
	 */
	u32 acquired_guest_caps;
	/**
	 * Usage counters क्रम guest capabilities requested through
	 * vbg_set_session_capabilities(). Indexed by capability bit
	 * number, one count per session using a capability.
	 * Protected by session_mutex.
	 */
	काष्ठा vbg_bit_usage_tracker set_guest_caps_tracker;
	/**
	 * The guest capabilities last reported to the host (or UINT32_MAX).
	 * Protected by session_mutex.
	 */
	u32 guest_caps_host;

	/**
	 * Heartbeat समयr which fires with पूर्णांकerval
	 * cNsHearbeatInterval and its handler sends
	 * VMMDEVREQ_GUEST_HEARTBEAT to VMMDev.
	 */
	काष्ठा समयr_list heartbeat_समयr;
	/** Heartbeat समयr पूर्णांकerval in ms. */
	पूर्णांक heartbeat_पूर्णांकerval_ms;
	/** Pपुनः_स्मृतिated VMMDEVREQ_GUEST_HEARTBEAT request. */
	काष्ठा vmmdev_request_header *guest_heartbeat_req;

	/** "vboxguest" अक्षर-device */
	काष्ठा miscdevice misc_device;
	/** "vboxuser" अक्षर-device */
	काष्ठा miscdevice misc_device_user;
पूर्ण;

/** The VBoxGuest per session data. */
काष्ठा vbg_session अणु
	/** Poपूर्णांकer to the device extension. */
	काष्ठा vbg_dev *gdev;

	/**
	 * Array containing HGCM client IDs associated with this session.
	 * These will be स्वतःmatically disconnected when the session is बंदd.
	 * Protected by vbg_gdev.session_mutex.
	 */
	u32 hgcm_client_ids[64];
	/**
	 * Host events requested by the session.
	 * An event type requested in any guest session will be added to the
	 * host filter. Protected by vbg_gdev.session_mutex.
	 */
	u32 event_filter;
	/**
	 * Guest capabilities acquired by vbg_acquire_session_capabilities().
	 * Only one session can acquire a capability at a समय.
	 */
	u32 acquired_guest_caps;
	/**
	 * Guest capabilities set through vbg_set_session_capabilities().
	 * A capability claimed by any guest session will be reported to the
	 * host. Protected by vbg_gdev.session_mutex.
	 */
	u32 set_guest_caps;
	/** VMMDEV_REQUESTOR_* flags */
	u32 requestor;
	/** Set on CANCEL_ALL_WAITEVENTS, रक्षित by vbg_devevent_spinlock. */
	bool cancel_रुकोers;
पूर्ण;

पूर्णांक  vbg_core_init(काष्ठा vbg_dev *gdev, u32 fixed_events);
व्योम vbg_core_निकास(काष्ठा vbg_dev *gdev);
काष्ठा vbg_session *vbg_core_खोलो_session(काष्ठा vbg_dev *gdev, u32 requestor);
व्योम vbg_core_बंद_session(काष्ठा vbg_session *session);
पूर्णांक  vbg_core_ioctl(काष्ठा vbg_session *session, अचिन्हित पूर्णांक req, व्योम *data);
पूर्णांक  vbg_core_set_mouse_status(काष्ठा vbg_dev *gdev, u32 features);

irqवापस_t vbg_core_isr(पूर्णांक irq, व्योम *dev_id);

व्योम vbg_linux_mouse_event(काष्ठा vbg_dev *gdev);

/* Private (non exported) functions क्रमm vboxguest_utils.c */
व्योम *vbg_req_alloc(माप_प्रकार len, क्रमागत vmmdev_request_type req_type,
		    u32 requestor);
व्योम vbg_req_मुक्त(व्योम *req, माप_प्रकार len);
पूर्णांक vbg_req_perक्रमm(काष्ठा vbg_dev *gdev, व्योम *req);
पूर्णांक vbg_hgcm_call32(
	काष्ठा vbg_dev *gdev, u32 requestor, u32 client_id, u32 function,
	u32 समयout_ms, काष्ठा vmmdev_hgcm_function_parameter32 *parm32,
	u32 parm_count, पूर्णांक *vbox_status);

#पूर्ण_अगर
