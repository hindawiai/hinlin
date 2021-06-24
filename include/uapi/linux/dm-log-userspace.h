<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (C) 2006-2009 Red Hat, Inc.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित __DM_LOG_USERSPACE_H__
#घोषणा __DM_LOG_USERSPACE_H__

#समावेश <linux/types.h>
#समावेश <linux/dm-ioctl.h> /* For DM_UUID_LEN */

/*
 * The device-mapper userspace log module consists of a kernel component and
 * a user-space component.  The kernel component implements the API defined
 * in dm-dirty-log.h.  Its purpose is simply to pass the parameters and
 * वापस values of those API functions between kernel and user-space.
 *
 * Below are defined the 'request_types' - DM_ULOG_CTR, DM_ULOG_DTR, etc.
 * These request types represent the dअगरferent functions in the device-mapper
 * dirty log API.  Each of these is described in more detail below.
 *
 * The user-space program must listen क्रम requests from the kernel (representing
 * the various API functions) and process them.
 *
 * User-space begins by setting up the communication link (error checking
 * हटाओd क्रम clarity):
 *	fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_CONNECTOR);
 *	addr.nl_family = AF_NETLINK;
 *	addr.nl_groups = CN_IDX_DM;
 *	addr.nl_pid = 0;
 *	r = bind(fd, (काष्ठा sockaddr *) &addr, माप(addr));
 *	opt = addr.nl_groups;
 *	setsockopt(fd, SOL_NETLINK, NETLINK_ADD_MEMBERSHIP, &opt, माप(opt));
 *
 * User-space will then रुको to receive requests क्रमm the kernel, which it
 * will process as described below.  The requests are received in the क्रमm,
 * ((काष्ठा dm_ulog_request) + (additional data)).  Depending on the request
 * type, there may or may not be 'additional data'.  In the descriptions below,
 * you will see 'Payload-to-userspace' and 'Payload-to-kernel'.  The
 * 'Payload-to-userspace' is what the kernel sends in 'additional data' as
 * necessary parameters to complete the request.  The 'Payload-to-kernel' is
 * the 'additional data' वापसed to the kernel that contains the necessary
 * results of the request.  The 'data_size' field in the dm_ulog_request
 * काष्ठाure denotes the availability and amount of payload data.
 */

/*
 * DM_ULOG_CTR corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*ctr)(काष्ठा dm_dirty_log *log, काष्ठा dm_target *ti,
 *	      अचिन्हित argc, अक्षर **argv);
 *
 * Payload-to-userspace:
 *	A single string containing all the argv arguments separated by ' 's
 * Payload-to-kernel:
 *	A NUL-terminated string that is the name of the device that is used
 *	as the backing store क्रम the log data.  'dm_get_device' will be called
 *	on this device.  ('dm_put_device' will be called on this device
 *	स्वतःmatically after calling DM_ULOG_DTR.)  If there is no device needed
 *	क्रम log data, 'data_size' in the dm_ulog_request काष्ठा should be 0.
 *
 * The UUID contained in the dm_ulog_request काष्ठाure is the reference that
 * will be used by all request types to a specअगरic log.  The स्थिरructor must
 * record this association with the instance created.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field, filling the
 * data field with the log device अगर necessary, and setting 'data_size'
 * appropriately.
 */
#घोषणा DM_ULOG_CTR                    1

/*
 * DM_ULOG_DTR corresponds to (found in dm-dirty-log.h):
 * व्योम (*dtr)(काष्ठा dm_dirty_log *log);
 *
 * Payload-to-userspace:
 *	A single string containing all the argv arguments separated by ' 's
 * Payload-to-kernel:
 *	None.  ('data_size' in the dm_ulog_request काष्ठा should be 0.)
 *
 * The UUID contained in the dm_ulog_request काष्ठाure is all that is
 * necessary to identअगरy the log instance being destroyed.  There is no
 * payload data.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and clearing
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_DTR                    2

/*
 * DM_ULOG_PRESUSPEND corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*presuspend)(काष्ठा dm_dirty_log *log);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	None.
 *
 * The UUID contained in the dm_ulog_request काष्ठाure is all that is
 * necessary to identअगरy the log instance being presuspended.  There is no
 * payload data.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_PRESUSPEND             3

/*
 * DM_ULOG_POSTSUSPEND corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*postsuspend)(काष्ठा dm_dirty_log *log);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	None.
 *
 * The UUID contained in the dm_ulog_request काष्ठाure is all that is
 * necessary to identअगरy the log instance being postsuspended.  There is no
 * payload data.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_POSTSUSPEND            4

/*
 * DM_ULOG_RESUME corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*resume)(काष्ठा dm_dirty_log *log);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	None.
 *
 * The UUID contained in the dm_ulog_request काष्ठाure is all that is
 * necessary to identअगरy the log instance being resumed.  There is no
 * payload data.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_RESUME                 5

/*
 * DM_ULOG_GET_REGION_SIZE corresponds to (found in dm-dirty-log.h):
 * __u32 (*get_region_size)(काष्ठा dm_dirty_log *log);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	__u64 - contains the region size
 *
 * The region size is something that was determined at स्थिरructor समय.
 * It is वापसed in the payload area and 'data_size' is set to
 * reflect this.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field appropriately.
 */
#घोषणा DM_ULOG_GET_REGION_SIZE        6

/*
 * DM_ULOG_IS_CLEAN corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*is_clean)(काष्ठा dm_dirty_log *log, region_t region);
 *
 * Payload-to-userspace:
 *	__u64 - the region to get clean status on
 * Payload-to-kernel:
 *	__s64  - 1 अगर clean, 0 otherwise
 *
 * Payload is माप(__u64) and contains the region क्रम which the clean
 * status is being made.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - filling the payload with 0 (not clean) or
 * 1 (clean), setting 'data_size' and 'error' appropriately.
 */
#घोषणा DM_ULOG_IS_CLEAN               7

/*
 * DM_ULOG_IN_SYNC corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*in_sync)(काष्ठा dm_dirty_log *log, region_t region,
 *		  पूर्णांक can_block);
 *
 * Payload-to-userspace:
 *	__u64 - the region to get sync status on
 * Payload-to-kernel:
 *	__s64 - 1 अगर in-sync, 0 otherwise
 *
 * Exactly the same as 'is_clean' above, except this समय asking "has the
 * region been recovered?" vs. "is the region not being modअगरied?"
 */
#घोषणा DM_ULOG_IN_SYNC                8

/*
 * DM_ULOG_FLUSH corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*flush)(काष्ठा dm_dirty_log *log);
 *
 * Payload-to-userspace:
 *	If the 'integrated_flush' directive is present in the स्थिरructor
 *	table, the payload is as same as DM_ULOG_MARK_REGION:
 *		__u64 [] - region(s) to mark
 *	अन्यथा
 *		None
 * Payload-to-kernel:
 *	None.
 *
 * If the 'integrated_flush' option was used during the creation of the
 * log, mark region requests are carried as payload in the flush request.
 * Piggybacking the mark requests in this way allows क्रम fewer communications
 * between kernel and userspace.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and clearing
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_FLUSH                  9

/*
 * DM_ULOG_MARK_REGION corresponds to (found in dm-dirty-log.h):
 * व्योम (*mark_region)(काष्ठा dm_dirty_log *log, region_t region);
 *
 * Payload-to-userspace:
 *	__u64 [] - region(s) to mark
 * Payload-to-kernel:
 *	None.
 *
 * Incoming payload contains the one or more regions to mark dirty.
 * The number of regions contained in the payload can be determined from
 * 'data_size/sizeof(__u64)'.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and clearing
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_MARK_REGION           10

/*
 * DM_ULOG_CLEAR_REGION corresponds to (found in dm-dirty-log.h):
 * व्योम (*clear_region)(काष्ठा dm_dirty_log *log, region_t region);
 *
 * Payload-to-userspace:
 *	__u64 [] - region(s) to clear
 * Payload-to-kernel:
 *	None.
 *
 * Incoming payload contains the one or more regions to mark clean.
 * The number of regions contained in the payload can be determined from
 * 'data_size/sizeof(__u64)'.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and clearing
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_CLEAR_REGION          11

/*
 * DM_ULOG_GET_RESYNC_WORK corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*get_resync_work)(काष्ठा dm_dirty_log *log, region_t *region);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	अणु
 *		__s64 i; -- 1 अगर recovery necessary, 0 otherwise
 *		__u64 r; -- The region to recover अगर i=1
 *	पूर्ण
 * 'data_size' should be set appropriately.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field appropriately.
 */
#घोषणा DM_ULOG_GET_RESYNC_WORK       12

/*
 * DM_ULOG_SET_REGION_SYNC corresponds to (found in dm-dirty-log.h):
 * व्योम (*set_region_sync)(काष्ठा dm_dirty_log *log,
 *			   region_t region, पूर्णांक in_sync);
 *
 * Payload-to-userspace:
 *	अणु
 *		__u64 - region to set sync state on
 *		__s64  - 0 अगर not-in-sync, 1 अगर in-sync
 *	पूर्ण
 * Payload-to-kernel:
 *	None.
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and clearing
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_SET_REGION_SYNC       13

/*
 * DM_ULOG_GET_SYNC_COUNT corresponds to (found in dm-dirty-log.h):
 * region_t (*get_sync_count)(काष्ठा dm_dirty_log *log);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	__u64 - the number of in-sync regions
 *
 * No incoming payload.  Kernel-bound payload contains the number of
 * regions that are in-sync (in a माप_प्रकार).
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_GET_SYNC_COUNT        14

/*
 * DM_ULOG_STATUS_INFO corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*status)(काष्ठा dm_dirty_log *log, STATUSTYPE_INFO,
 *		 अक्षर *result, अचिन्हित maxlen);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	Character string containing STATUSTYPE_INFO
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_STATUS_INFO           15

/*
 * DM_ULOG_STATUS_TABLE corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*status)(काष्ठा dm_dirty_log *log, STATUSTYPE_TABLE,
 *		 अक्षर *result, अचिन्हित maxlen);
 *
 * Payload-to-userspace:
 *	None.
 * Payload-to-kernel:
 *	Character string containing STATUSTYPE_TABLE
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_STATUS_TABLE          16

/*
 * DM_ULOG_IS_REMOTE_RECOVERING corresponds to (found in dm-dirty-log.h):
 * पूर्णांक (*is_remote_recovering)(काष्ठा dm_dirty_log *log, region_t region);
 *
 * Payload-to-userspace:
 *	__u64 - region to determine recovery status on
 * Payload-to-kernel:
 *	अणु
 *		__s64 is_recovering;  -- 0 अगर no, 1 अगर yes
 *		__u64 in_sync_hपूर्णांक;  -- lowest region still needing resync
 *	पूर्ण
 *
 * When the request has been processed, user-space must वापस the
 * dm_ulog_request to the kernel - setting the 'error' field and
 * 'data_size' appropriately.
 */
#घोषणा DM_ULOG_IS_REMOTE_RECOVERING  17

/*
 * (DM_ULOG_REQUEST_MASK & request_type) to get the request type
 *
 * Payload-to-userspace:
 *	A single string containing all the argv arguments separated by ' 's
 * Payload-to-kernel:
 *	None.  ('data_size' in the dm_ulog_request काष्ठा should be 0.)
 *
 * We are reserving 8 bits of the 32-bit 'request_type' field क्रम the
 * various request types above.  The reमुख्यing 24-bits are currently
 * set to zero and are reserved क्रम future use and compatibility concerns.
 *
 * User-space should always use DM_ULOG_REQUEST_TYPE to acquire the
 * request type from the 'request_type' field to मुख्यtain क्रमward compatibility.
 */
#घोषणा DM_ULOG_REQUEST_MASK 0xFF
#घोषणा DM_ULOG_REQUEST_TYPE(request_type) \
	(DM_ULOG_REQUEST_MASK & (request_type))

/*
 * DM_ULOG_REQUEST_VERSION is incremented when there is a
 * change to the way inक्रमmation is passed between kernel
 * and userspace.  This could be a काष्ठाure change of
 * dm_ulog_request or a change in the way requests are
 * issued/handled.  Changes are outlined here:
 *	version 1:  Initial implementation
 *	version 2:  DM_ULOG_CTR allowed to वापस a string containing a
 *	            device name that is to be रेजिस्टरed with DM via
 *	            'dm_get_device'.
 *	version 3:  DM_ULOG_FLUSH is capable of carrying payload क्रम marking
 *		    regions.  This "integrated flush" reduces the number of
 *		    requests between the kernel and userspace by effectively
 *		    merging 'mark' and 'flush' requests.  A स्थिरructor table
 *		    argument ('integrated_flush') is required to turn this
 *		    feature on, so it is backwards compatible with older
 *		    userspace versions.
 */
#घोषणा DM_ULOG_REQUEST_VERSION 3

काष्ठा dm_ulog_request अणु
	/*
	 * The local unique identअगरier (luid) and the universally unique
	 * identअगरier (uuid) are used to tie a request to a specअगरic
	 * mirror log.  A single machine log could probably make due with
	 * just the 'luid', but a cluster-aware log must use the 'uuid' and
	 * the 'luid'.  The uuid is what is required क्रम node to node
	 * communication concerning a particular log, but the 'luid' helps
	 * dअगरferentiate between logs that are being swapped and have the
	 * same 'uuid'.  (Think "live" and "inactive" device-mapper tables.)
	 */
	__u64 luid;
	अक्षर uuid[DM_UUID_LEN];
	अक्षर padding[3];        /* Padding because DM_UUID_LEN = 129 */

	__u32 version;       /* See DM_ULOG_REQUEST_VERSION */
	__s32 error;          /* Used to report back processing errors */

	__u32 seq;           /* Sequence number क्रम request */
	__u32 request_type;  /* DM_ULOG_* defined above */
	__u32 data_size;     /* How much data (not including this काष्ठा) */

	अक्षर data[0];
पूर्ण;

#पूर्ण_अगर /* __DM_LOG_USERSPACE_H__ */
