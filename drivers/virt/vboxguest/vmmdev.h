<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR CDDL-1.0) */
/*
 * Virtual Device क्रम Guest <-> VMM/Host communication पूर्णांकerface
 *
 * Copyright (C) 2006-2016 Oracle Corporation
 */

#अगर_अघोषित __VBOX_VMMDEV_H__
#घोषणा __VBOX_VMMDEV_H__

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <linux/sizes.h>
#समावेश <linux/types.h>
#समावेश <linux/vbox_vmmdev_types.h>

/* Port क्रम generic request पूर्णांकerface (relative offset). */
#घोषणा VMMDEV_PORT_OFF_REQUEST                             0

/** Layout of VMMDEV RAM region that contains inक्रमmation क्रम guest. */
काष्ठा vmmdev_memory अणु
	/** The size of this काष्ठाure. */
	u32 size;
	/** The काष्ठाure version. (VMMDEV_MEMORY_VERSION) */
	u32 version;

	जोड़ अणु
		काष्ठा अणु
			/** Flag telling that VMMDev has events pending. */
			u8 have_events;
			/** Explicit padding, MBZ. */
			u8 padding[3];
		पूर्ण V1_04;

		काष्ठा अणु
			/** Pending events flags, set by host. */
			u32 host_events;
			/** Mask of events the guest wants, set by guest. */
			u32 guest_event_mask;
		पूर्ण V1_03;
	पूर्ण V;

	/* काष्ठा vbva_memory, not used */
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_memory, 8 + 8);

/** Version of vmmdev_memory काष्ठाure (vmmdev_memory::version). */
#घोषणा VMMDEV_MEMORY_VERSION   (1)

/* Host mouse capabilities has been changed. */
#घोषणा VMMDEV_EVENT_MOUSE_CAPABILITIES_CHANGED             BIT(0)
/* HGCM event. */
#घोषणा VMMDEV_EVENT_HGCM                                   BIT(1)
/* A display change request has been issued. */
#घोषणा VMMDEV_EVENT_DISPLAY_CHANGE_REQUEST                 BIT(2)
/* Credentials are available क्रम judgement. */
#घोषणा VMMDEV_EVENT_JUDGE_CREDENTIALS                      BIT(3)
/* The guest has been restored. */
#घोषणा VMMDEV_EVENT_RESTORED                               BIT(4)
/* Seamless mode state changed. */
#घोषणा VMMDEV_EVENT_SEAMLESS_MODE_CHANGE_REQUEST           BIT(5)
/* Memory balloon size changed. */
#घोषणा VMMDEV_EVENT_BALLOON_CHANGE_REQUEST                 BIT(6)
/* Statistics पूर्णांकerval changed. */
#घोषणा VMMDEV_EVENT_STATISTICS_INTERVAL_CHANGE_REQUEST     BIT(7)
/* VRDP status changed. */
#घोषणा VMMDEV_EVENT_VRDP                                   BIT(8)
/* New mouse position data available. */
#घोषणा VMMDEV_EVENT_MOUSE_POSITION_CHANGED                 BIT(9)
/* CPU hotplug event occurred. */
#घोषणा VMMDEV_EVENT_CPU_HOTPLUG                            BIT(10)
/* The mask of valid events, क्रम sanity checking. */
#घोषणा VMMDEV_EVENT_VALID_EVENT_MASK                       0x000007ffU

/*
 * Additions are allowed to work only अगर additions_major == vmmdev_current &&
 * additions_minor <= vmmdev_current. Additions version is reported to host
 * (VMMDev) by VMMDEVREQ_REPORT_GUEST_INFO.
 */
#घोषणा VMMDEV_VERSION                      0x00010004
#घोषणा VMMDEV_VERSION_MAJOR                (VMMDEV_VERSION >> 16)
#घोषणा VMMDEV_VERSION_MINOR                (VMMDEV_VERSION & 0xffff)

/* Maximum request packet size. */
#घोषणा VMMDEV_MAX_VMMDEVREQ_SIZE           1048576

/* Version of vmmdev_request_header काष्ठाure. */
#घोषणा VMMDEV_REQUEST_HEADER_VERSION       0x10001

/** काष्ठा vmmdev_request_header - Generic VMMDev request header. */
काष्ठा vmmdev_request_header अणु
	/** IN: Size of the काष्ठाure in bytes (including body). */
	u32 size;
	/** IN: Version of the काष्ठाure.  */
	u32 version;
	/** IN: Type of the request. */
	क्रमागत vmmdev_request_type request_type;
	/** OUT: Return code. */
	s32 rc;
	/** Reserved field no.1. MBZ. */
	u32 reserved1;
	/** IN: Requestor inक्रमmation (VMMDEV_REQUESTOR_*) */
	u32 requestor;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_request_header, 24);

/**
 * काष्ठा vmmdev_mouse_status - Mouse status request काष्ठाure.
 *
 * Used by VMMDEVREQ_GET_MOUSE_STATUS and VMMDEVREQ_SET_MOUSE_STATUS.
 */
काष्ठा vmmdev_mouse_status अणु
	/** header */
	काष्ठा vmmdev_request_header header;
	/** Mouse feature mask. See VMMDEV_MOUSE_*. */
	u32 mouse_features;
	/** Mouse x position. */
	s32 poपूर्णांकer_pos_x;
	/** Mouse y position. */
	s32 poपूर्णांकer_pos_y;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_mouse_status, 24 + 12);

/* The guest can (== wants to) handle असलolute coordinates.  */
#घोषणा VMMDEV_MOUSE_GUEST_CAN_ABSOLUTE                     BIT(0)
/*
 * The host can (== wants to) send असलolute coordinates.
 * (Input not captured.)
 */
#घोषणा VMMDEV_MOUSE_HOST_WANTS_ABSOLUTE                    BIT(1)
/*
 * The guest can *NOT* चयन to software cursor and thereक्रमe depends on the
 * host cursor.
 *
 * When guest additions are installed and the host has promised to display the
 * cursor itself, the guest installs a hardware mouse driver. Don't ask the
 * guest to चयन to a software cursor then.
 */
#घोषणा VMMDEV_MOUSE_GUEST_NEEDS_HOST_CURSOR                BIT(2)
/* The host करोes NOT provide support क्रम drawing the cursor itself. */
#घोषणा VMMDEV_MOUSE_HOST_CANNOT_HWPOINTER                  BIT(3)
/* The guest can पढ़ो VMMDev events to find out about poपूर्णांकer movement */
#घोषणा VMMDEV_MOUSE_NEW_PROTOCOL                           BIT(4)
/*
 * If the guest changes the status of the VMMDEV_MOUSE_GUEST_NEEDS_HOST_CURSOR
 * bit, the host will honour this.
 */
#घोषणा VMMDEV_MOUSE_HOST_RECHECKS_NEEDS_HOST_CURSOR        BIT(5)
/*
 * The host supplies an असलolute poपूर्णांकing device.  The Guest Additions may
 * wish to use this to decide whether to install their own driver.
 */
#घोषणा VMMDEV_MOUSE_HOST_HAS_ABS_DEV                       BIT(6)

/* The minimum value our poपूर्णांकing device can वापस. */
#घोषणा VMMDEV_MOUSE_RANGE_MIN 0
/* The maximum value our poपूर्णांकing device can वापस. */
#घोषणा VMMDEV_MOUSE_RANGE_MAX 0xFFFF

/**
 * काष्ठा vmmdev_host_version - VirtualBox host version request काष्ठाure.
 *
 * VBG uses this to detect the precense of new features in the पूर्णांकerface.
 */
काष्ठा vmmdev_host_version अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** Major version. */
	u16 major;
	/** Minor version. */
	u16 minor;
	/** Build number. */
	u32 build;
	/** SVN revision. */
	u32 revision;
	/** Feature mask. */
	u32 features;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_host_version, 24 + 16);

/* Physical page lists are supported by HGCM. */
#घोषणा VMMDEV_HVF_HGCM_PHYS_PAGE_LIST  BIT(0)

/**
 * काष्ठा vmmdev_mask - Structure to set / clear bits in a mask used क्रम
 * VMMDEVREQ_SET_GUEST_CAPABILITIES and VMMDEVREQ_CTL_GUEST_FILTER_MASK.
 */
काष्ठा vmmdev_mask अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** Mask of bits to be set. */
	u32 or_mask;
	/** Mask of bits to be cleared. */
	u32 not_mask;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_mask, 24 + 8);

/* The guest supports seamless display rendering. */
#घोषणा VMMDEV_GUEST_SUPPORTS_SEAMLESS                      BIT(0)
/* The guest supports mapping guest to host winकरोws. */
#घोषणा VMMDEV_GUEST_SUPPORTS_GUEST_HOST_WINDOW_MAPPING     BIT(1)
/*
 * The guest graphical additions are active.
 * Used क्रम fast activation and deactivation of certain graphical operations
 * (e.g. resizing & seamless). The legacy VMMDEVREQ_REPORT_GUEST_CAPABILITIES
 * request sets this स्वतःmatically, but VMMDEVREQ_SET_GUEST_CAPABILITIES करोes
 * not.
 */
#घोषणा VMMDEV_GUEST_SUPPORTS_GRAPHICS                      BIT(2)
/* The mask of valid capabilities, क्रम sanity checking. */
#घोषणा VMMDEV_GUEST_CAPABILITIES_MASK                      0x00000007U

/** काष्ठा vmmdev_hypervisorinfo - Hypervisor info काष्ठाure. */
काष्ठा vmmdev_hypervisorinfo अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/**
	 * Guest भव address of proposed hypervisor start.
	 * Not used by VMMDEVREQ_GET_HYPERVISOR_INFO.
	 */
	u32 hypervisor_start;
	/** Hypervisor size in bytes. */
	u32 hypervisor_size;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_hypervisorinfo, 24 + 8);

/** काष्ठा vmmdev_events - Pending events काष्ठाure. */
काष्ठा vmmdev_events अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** OUT: Pending event mask. */
	u32 events;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_events, 24 + 4);

#घोषणा VMMDEV_OSTYPE_LINUX26		0x53000
#घोषणा VMMDEV_OSTYPE_X64		BIT(8)

/** काष्ठा vmmdev_guestinfo - Guest inक्रमmation report. */
काष्ठा vmmdev_guest_info अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/**
	 * The VMMDev पूर्णांकerface version expected by additions.
	 * *Deprecated*, करो not use anymore! Will be हटाओd.
	 */
	u32 पूर्णांकerface_version;
	/** Guest OS type. */
	u32 os_type;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_guest_info, 24 + 8);

#घोषणा VMMDEV_GUEST_INFO2_ADDITIONS_FEATURES_REQUESTOR_INFO	BIT(0)

/** काष्ठा vmmdev_guestinfo2 - Guest inक्रमmation report, version 2. */
काष्ठा vmmdev_guest_info2 अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** Major version. */
	u16 additions_major;
	/** Minor version. */
	u16 additions_minor;
	/** Build number. */
	u32 additions_build;
	/** SVN revision. */
	u32 additions_revision;
	/** Feature mask. */
	u32 additions_features;
	/**
	 * The पूर्णांकentional meaning of this field was:
	 * Some additional inक्रमmation, क्रम example 'Beta 1' or something like
	 * that.
	 *
	 * The way it was implemented was implemented: VBG_VERSION_STRING.
	 *
	 * This means the first three members are duplicated in this field (अगर
	 * the guest build config is sane). So, the user must check this and
	 * chop it off beक्रमe usage. There is, because of the Main code's blind
	 * trust in the field's content, no way back.
	 */
	अक्षर name[128];
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_guest_info2, 24 + 144);

क्रमागत vmmdev_guest_facility_type अणु
	VBOXGUEST_FACILITY_TYPE_UNKNOWN          = 0,
	VBOXGUEST_FACILITY_TYPE_VBOXGUEST_DRIVER = 20,
	/* VBoxGINA / VBoxCredProv / pam_vbox. */
	VBOXGUEST_FACILITY_TYPE_AUTO_LOGON       = 90,
	VBOXGUEST_FACILITY_TYPE_VBOX_SERVICE     = 100,
	/* VBoxTray (Winकरोws), VBoxClient (Linux, Unix). */
	VBOXGUEST_FACILITY_TYPE_VBOX_TRAY_CLIENT = 101,
	VBOXGUEST_FACILITY_TYPE_SEAMLESS         = 1000,
	VBOXGUEST_FACILITY_TYPE_GRAPHICS         = 1100,
	VBOXGUEST_FACILITY_TYPE_ALL              = 0x7ffffffe,
	/* Ensure the क्रमागत is a 32 bit data-type */
	VBOXGUEST_FACILITY_TYPE_SIZEHACK         = 0x7fffffff
पूर्ण;

क्रमागत vmmdev_guest_facility_status अणु
	VBOXGUEST_FACILITY_STATUS_INACTIVE    = 0,
	VBOXGUEST_FACILITY_STATUS_PAUSED      = 1,
	VBOXGUEST_FACILITY_STATUS_PRE_INIT    = 20,
	VBOXGUEST_FACILITY_STATUS_INIT        = 30,
	VBOXGUEST_FACILITY_STATUS_ACTIVE      = 50,
	VBOXGUEST_FACILITY_STATUS_TERMINATING = 100,
	VBOXGUEST_FACILITY_STATUS_TERMINATED  = 101,
	VBOXGUEST_FACILITY_STATUS_FAILED      = 800,
	VBOXGUEST_FACILITY_STATUS_UNKNOWN     = 999,
	/* Ensure the क्रमागत is a 32 bit data-type */
	VBOXGUEST_FACILITY_STATUS_SIZEHACK    = 0x7fffffff
पूर्ण;

/** काष्ठा vmmdev_guest_status - Guest Additions status काष्ठाure. */
काष्ठा vmmdev_guest_status अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** Facility the status is indicated क्रम. */
	क्रमागत vmmdev_guest_facility_type facility;
	/** Current guest status. */
	क्रमागत vmmdev_guest_facility_status status;
	/** Flags, not used at the moment. */
	u32 flags;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_guest_status, 24 + 12);

#घोषणा VMMDEV_MEMORY_BALLOON_CHUNK_SIZE             (1048576)
#घोषणा VMMDEV_MEMORY_BALLOON_CHUNK_PAGES            (1048576 / 4096)

/** काष्ठा vmmdev_memballoon_info - Memory-balloon info काष्ठाure. */
काष्ठा vmmdev_memballoon_info अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** Balloon size in megabytes. */
	u32 balloon_chunks;
	/** Guest ram size in megabytes. */
	u32 phys_mem_chunks;
	/**
	 * Setting this to VMMDEV_EVENT_BALLOON_CHANGE_REQUEST indicates that
	 * the request is a response to that event.
	 * (Don't confuse this with VMMDEVREQ_ACKNOWLEDGE_EVENTS.)
	 */
	u32 event_ack;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_memballoon_info, 24 + 12);

/** काष्ठा vmmdev_memballoon_change - Change the size of the balloon. */
काष्ठा vmmdev_memballoon_change अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** The number of pages in the array. */
	u32 pages;
	/** true = inflate, false = deflate.  */
	u32 inflate;
	/** Physical address (u64) of each page. */
	u64 phys_page[VMMDEV_MEMORY_BALLOON_CHUNK_PAGES];
पूर्ण;

/** काष्ठा vmmdev_ग_लिखो_core_dump - Write Core Dump request data. */
काष्ठा vmmdev_ग_लिखो_core_dump अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** Flags (reserved, MBZ). */
	u32 flags;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_ग_लिखो_core_dump, 24 + 4);

/** काष्ठा vmmdev_heartbeat - Heart beat check state काष्ठाure. */
काष्ठा vmmdev_heartbeat अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** OUT: Guest heartbeat पूर्णांकerval in nanosec. */
	u64 पूर्णांकerval_ns;
	/** Heartbeat check flag. */
	u8 enabled;
	/** Explicit padding, MBZ. */
	u8 padding[3];
पूर्ण __packed;
VMMDEV_ASSERT_SIZE(vmmdev_heartbeat, 24 + 12);

#घोषणा VMMDEV_HGCM_REQ_DONE      BIT(0)
#घोषणा VMMDEV_HGCM_REQ_CANCELLED BIT(1)

/** काष्ठा vmmdev_hgcmreq_header - vmmdev HGCM requests header. */
काष्ठा vmmdev_hgcmreq_header अणु
	/** Request header. */
	काष्ठा vmmdev_request_header header;

	/** HGCM flags. */
	u32 flags;

	/** Result code. */
	s32 result;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_hgcmreq_header, 24 + 8);

/** काष्ठा vmmdev_hgcm_connect - HGCM connect request काष्ठाure. */
काष्ठा vmmdev_hgcm_connect अणु
	/** HGCM request header. */
	काष्ठा vmmdev_hgcmreq_header header;

	/** IN: Description of service to connect to. */
	काष्ठा vmmdev_hgcm_service_location loc;

	/** OUT: Client identअगरier asचिन्हित by local instance of HGCM. */
	u32 client_id;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_hgcm_connect, 32 + 132 + 4);

/** काष्ठा vmmdev_hgcm_disconnect - HGCM disconnect request काष्ठाure. */
काष्ठा vmmdev_hgcm_disconnect अणु
	/** HGCM request header. */
	काष्ठा vmmdev_hgcmreq_header header;

	/** IN: Client identअगरier. */
	u32 client_id;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_hgcm_disconnect, 32 + 4);

#घोषणा VMMDEV_HGCM_MAX_PARMS 32

/** काष्ठा vmmdev_hgcm_call - HGCM call request काष्ठाure. */
काष्ठा vmmdev_hgcm_call अणु
	/* request header */
	काष्ठा vmmdev_hgcmreq_header header;

	/** IN: Client identअगरier. */
	u32 client_id;
	/** IN: Service function number. */
	u32 function;
	/** IN: Number of parameters. */
	u32 parm_count;
	/** Parameters follow in क्रमm: HGCMFunctionParameter32|64 parms[X]; */
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_hgcm_call, 32 + 12);

/**
 * काष्ठा vmmdev_hgcm_cancel2 - HGCM cancel request काष्ठाure, version 2.
 *
 * After the request header.rc will be:
 *
 * VINF_SUCCESS when cancelled.
 * VERR_NOT_FOUND अगर the specअगरied request cannot be found.
 * VERR_INVALID_PARAMETER अगर the address is invalid valid.
 */
काष्ठा vmmdev_hgcm_cancel2 अणु
	/** Header. */
	काष्ठा vmmdev_request_header header;
	/** The physical address of the request to cancel. */
	u32 phys_req_to_cancel;
पूर्ण;
VMMDEV_ASSERT_SIZE(vmmdev_hgcm_cancel2, 24 + 4);

#पूर्ण_अगर
