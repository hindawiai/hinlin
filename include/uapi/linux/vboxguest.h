<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR CDDL-1.0) */
/*
 * VBoxGuest - VirtualBox Guest Additions Driver Interface.
 *
 * Copyright (C) 2006-2016 Oracle Corporation
 */

#अगर_अघोषित __UAPI_VBOXGUEST_H__
#घोषणा __UAPI_VBOXGUEST_H__

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/vbox_err.h>
#समावेश <linux/vbox_vmmdev_types.h>

/* Version of vbg_ioctl_hdr काष्ठाure. */
#घोषणा VBG_IOCTL_HDR_VERSION		0x10001
/* Default request type.  Use this क्रम non-VMMDev requests. */
#घोषणा VBG_IOCTL_HDR_TYPE_DEFAULT		0

/**
 * Common ioctl header.
 *
 * This is a mirror of vmmdev_request_header to prevent duplicating data and
 * needing to verअगरy things multiple बार.
 */
काष्ठा vbg_ioctl_hdr अणु
	/** IN: The request input size, and output size अगर size_out is zero. */
	__u32 size_in;
	/** IN: Structure version (VBG_IOCTL_HDR_VERSION) */
	__u32 version;
	/** IN: The VMMDev request type or VBG_IOCTL_HDR_TYPE_DEFAULT. */
	__u32 type;
	/**
	 * OUT: The VBox status code of the operation, out direction only.
	 * This is a VINF_ or VERR_ value as defined in vbox_err.h.
	 */
	__s32 rc;
	/** IN: Output size. Set to zero to use size_in as output size. */
	__u32 size_out;
	/** Reserved, MBZ. */
	__u32 reserved;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_hdr, 24);


/*
 * The VBoxGuest I/O control version.
 *
 * As usual, the high word contains the major version and changes to it
 * signअगरies incompatible changes.
 *
 * The lower word is the minor version number, it is increased when new
 * functions are added or existing changed in a backwards compatible manner.
 */
#घोषणा VBG_IOC_VERSION		0x00010000u

/**
 * VBG_IOCTL_DRIVER_VERSION_INFO data काष्ठाure
 *
 * Note VBG_IOCTL_DRIVER_VERSION_INFO may चयन the session to a backwards
 * compatible पूर्णांकerface version अगर uClientVersion indicates older client code.
 */
काष्ठा vbg_ioctl_driver_version_info अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			/** Requested पूर्णांकerface version (VBG_IOC_VERSION). */
			__u32 req_version;
			/**
			 * Minimum पूर्णांकerface version number (typically the
			 * major version part of VBG_IOC_VERSION).
			 */
			__u32 min_version;
			/** Reserved, MBZ. */
			__u32 reserved1;
			/** Reserved, MBZ. */
			__u32 reserved2;
		पूर्ण in;
		काष्ठा अणु
			/** Version क्रम this session (typ. VBG_IOC_VERSION). */
			__u32 session_version;
			/** Version of the IDC पूर्णांकerface (VBG_IOC_VERSION). */
			__u32 driver_version;
			/** The SVN revision of the driver, or 0. */
			__u32 driver_revision;
			/** Reserved \#1 (zero until defined). */
			__u32 reserved1;
			/** Reserved \#2 (zero until defined). */
			__u32 reserved2;
		पूर्ण out;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_driver_version_info, 24 + 20);

#घोषणा VBG_IOCTL_DRIVER_VERSION_INFO \
	_IOWR('V', 0, काष्ठा vbg_ioctl_driver_version_info)


/* IOCTL to perक्रमm a VMM Device request less than 1KB in size. */
#घोषणा VBG_IOCTL_VMMDEV_REQUEST(s)	_IOC(_IOC_READ | _IOC_WRITE, 'V', 2, s)


/* IOCTL to perक्रमm a VMM Device request larger then 1KB. */
#घोषणा VBG_IOCTL_VMMDEV_REQUEST_BIG	_IO('V', 3)


/** VBG_IOCTL_HGCM_CONNECT data काष्ठाure. */
काष्ठा vbg_ioctl_hgcm_connect अणु
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा vmmdev_hgcm_service_location loc;
		पूर्ण in;
		काष्ठा अणु
			__u32 client_id;
		पूर्ण out;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_hgcm_connect, 24 + 132);

#घोषणा VBG_IOCTL_HGCM_CONNECT \
	_IOWR('V', 4, काष्ठा vbg_ioctl_hgcm_connect)


/** VBG_IOCTL_HGCM_DISCONNECT data काष्ठाure. */
काष्ठा vbg_ioctl_hgcm_disconnect अणु
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			__u32 client_id;
		पूर्ण in;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_hgcm_disconnect, 24 + 4);

#घोषणा VBG_IOCTL_HGCM_DISCONNECT \
	_IOWR('V', 5, काष्ठा vbg_ioctl_hgcm_disconnect)


/** VBG_IOCTL_HGCM_CALL data काष्ठाure. */
काष्ठा vbg_ioctl_hgcm_call अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	/** Input: The id of the caller. */
	__u32 client_id;
	/** Input: Function number. */
	__u32 function;
	/**
	 * Input: How दीर्घ to रुको (milliseconds) क्रम completion beक्रमe
	 * cancelling the call. Set to -1 to रुको indefinitely.
	 */
	__u32 समयout_ms;
	/** Interruptable flag, ignored क्रम userspace calls. */
	__u8 पूर्णांकerruptible;
	/** Explicit padding, MBZ. */
	__u8 reserved;
	/**
	 * Input: How many parameters following this काष्ठाure.
	 *
	 * The parameters are either HGCMFunctionParameter64 or 32,
	 * depending on whether we're receiving a 64-bit or 32-bit request.
	 *
	 * The current maximum is 61 parameters (given a 1KB max request size,
	 * and a 64-bit parameter size of 16 bytes).
	 */
	__u16 parm_count;
	/*
	 * Parameters follow in क्रमm:
	 * काष्ठा hgcm_function_parameter<32|64> parms[parm_count]
	 */
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_hgcm_call, 24 + 16);

#घोषणा VBG_IOCTL_HGCM_CALL_32(s)	_IOC(_IOC_READ | _IOC_WRITE, 'V', 6, s)
#घोषणा VBG_IOCTL_HGCM_CALL_64(s)	_IOC(_IOC_READ | _IOC_WRITE, 'V', 7, s)
#अगर __BITS_PER_LONG == 64
#घोषणा VBG_IOCTL_HGCM_CALL(s)		VBG_IOCTL_HGCM_CALL_64(s)
#अन्यथा
#घोषणा VBG_IOCTL_HGCM_CALL(s)		VBG_IOCTL_HGCM_CALL_32(s)
#पूर्ण_अगर


/** VBG_IOCTL_LOG data काष्ठाure. */
काष्ठा vbg_ioctl_log अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			/**
			 * The log message, this may be zero terminated. If it
			 * is not zero terminated then the length is determined
			 * from the input size.
			 */
			अक्षर msg[1];
		पूर्ण in;
	पूर्ण u;
पूर्ण;

#घोषणा VBG_IOCTL_LOG(s)		_IO('V', 9)


/** VBG_IOCTL_WAIT_FOR_EVENTS data काष्ठाure. */
काष्ठा vbg_ioctl_रुको_क्रम_events अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			/** Timeout in milliseconds. */
			__u32 समयout_ms;
			/** Events to रुको क्रम. */
			__u32 events;
		पूर्ण in;
		काष्ठा अणु
			/** Events that occurred. */
			__u32 events;
		पूर्ण out;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_रुको_क्रम_events, 24 + 8);

#घोषणा VBG_IOCTL_WAIT_FOR_EVENTS \
	_IOWR('V', 10, काष्ठा vbg_ioctl_रुको_क्रम_events)


/*
 * IOCTL to VBoxGuest to पूर्णांकerrupt (cancel) any pending
 * VBG_IOCTL_WAIT_FOR_EVENTS and वापस.
 *
 * Handled inside the vboxguest driver and not seen by the host at all.
 * After calling this, VBG_IOCTL_WAIT_FOR_EVENTS should no दीर्घer be called in
 * the same session. Any VBOXGUEST_IOCTL_WAITEVENT calls in the same session
 * करोne after calling this will directly निकास with -EINTR.
 */
#घोषणा VBG_IOCTL_INTERRUPT_ALL_WAIT_FOR_EVENTS \
	_IOWR('V', 11, काष्ठा vbg_ioctl_hdr)


/** VBG_IOCTL_CHANGE_FILTER_MASK data काष्ठाure. */
काष्ठा vbg_ioctl_change_filter अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			/** Flags to set. */
			__u32 or_mask;
			/** Flags to हटाओ. */
			__u32 not_mask;
		पूर्ण in;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_change_filter, 24 + 8);

/* IOCTL to VBoxGuest to control the event filter mask. */
#घोषणा VBG_IOCTL_CHANGE_FILTER_MASK \
	_IOWR('V', 12, काष्ठा vbg_ioctl_change_filter)


/** VBG_IOCTL_ACQUIRE_GUEST_CAPABILITIES data काष्ठाure. */
काष्ठा vbg_ioctl_acquire_guest_caps अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			/** Flags (VBGL_IOC_AGC_FLAGS_XXX). */
			__u32 flags;
			/** Capabilities to set (VMMDEV_GUEST_SUPPORTS_XXX). */
			__u32 or_mask;
			/** Capabilities to drop (VMMDEV_GUEST_SUPPORTS_XXX). */
			__u32 not_mask;
		पूर्ण in;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_acquire_guest_caps, 24 + 12);

#घोषणा VBGL_IOC_AGC_FLAGS_CONFIG_ACQUIRE_MODE		0x00000001
#घोषणा VBGL_IOC_AGC_FLAGS_VALID_MASK			0x00000001

#घोषणा VBG_IOCTL_ACQUIRE_GUEST_CAPABILITIES \
	_IOWR('V', 13, काष्ठा vbg_ioctl_acquire_guest_caps)


/** VBG_IOCTL_CHANGE_GUEST_CAPABILITIES data काष्ठाure. */
काष्ठा vbg_ioctl_set_guest_caps अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			/** Capabilities to set (VMMDEV_GUEST_SUPPORTS_XXX). */
			__u32 or_mask;
			/** Capabilities to drop (VMMDEV_GUEST_SUPPORTS_XXX). */
			__u32 not_mask;
		पूर्ण in;
		काष्ठा अणु
			/** Capabilities held by the session after the call. */
			__u32 session_caps;
			/** Capabilities क्रम all the sessions after the call. */
			__u32 global_caps;
		पूर्ण out;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_set_guest_caps, 24 + 8);

#घोषणा VBG_IOCTL_CHANGE_GUEST_CAPABILITIES \
	_IOWR('V', 14, काष्ठा vbg_ioctl_set_guest_caps)


/** VBG_IOCTL_CHECK_BALLOON data काष्ठाure. */
काष्ठा vbg_ioctl_check_balloon अणु
	/** The header. */
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			/** The size of the balloon in chunks of 1MB. */
			__u32 balloon_chunks;
			/**
			 * false = handled in R0, no further action required.
			 *  true = allocate balloon memory in R3.
			 */
			__u8 handle_in_r3;
			/** Explicit padding, MBZ. */
			__u8 padding[3];
		पूर्ण out;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_check_balloon, 24 + 8);

/*
 * IOCTL to check memory ballooning.
 *
 * The guest kernel module will ask the host क्रम the current size of the
 * balloon and adjust the size. Or it will set handle_in_r3 = true and R3 is
 * responsible क्रम allocating memory and calling VBG_IOCTL_CHANGE_BALLOON.
 */
#घोषणा VBG_IOCTL_CHECK_BALLOON \
	_IOWR('V', 17, काष्ठा vbg_ioctl_check_balloon)


/** VBG_IOCTL_WRITE_CORE_DUMP data काष्ठाure. */
काष्ठा vbg_ioctl_ग_लिखो_coredump अणु
	काष्ठा vbg_ioctl_hdr hdr;
	जोड़ अणु
		काष्ठा अणु
			__u32 flags; /** Flags (reserved, MBZ). */
		पूर्ण in;
	पूर्ण u;
पूर्ण;
VMMDEV_ASSERT_SIZE(vbg_ioctl_ग_लिखो_coredump, 24 + 4);

#घोषणा VBG_IOCTL_WRITE_CORE_DUMP \
	_IOWR('V', 19, काष्ठा vbg_ioctl_ग_लिखो_coredump)

#पूर्ण_अगर
