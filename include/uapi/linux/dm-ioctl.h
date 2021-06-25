<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (C) 2001 - 2003 Sistina Software (UK) Limited.
 * Copyright (C) 2004 - 2009 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित _LINUX_DM_IOCTL_V4_H
#घोषणा _LINUX_DM_IOCTL_V4_H

#समावेश <linux/types.h>

#घोषणा DM_सूची "mapper"		/* Slashes not supported */
#घोषणा DM_CONTROL_NODE "control"
#घोषणा DM_MAX_TYPE_NAME 16
#घोषणा DM_NAME_LEN 128
#घोषणा DM_UUID_LEN 129

/*
 * A traditional ioctl पूर्णांकerface क्रम the device mapper.
 *
 * Each device can have two tables associated with it, an
 * 'active' table which is the one currently used by io passing
 * through the device, and an 'inactive' one which is a table
 * that is being prepared as a replacement क्रम the 'active' one.
 *
 * DM_VERSION:
 * Just get the version inक्रमmation क्रम the ioctl पूर्णांकerface.
 *
 * DM_REMOVE_ALL:
 * Remove all dm devices, destroy all tables.  Only really used
 * क्रम debug.
 *
 * DM_LIST_DEVICES:
 * Get a list of all the dm device names.
 *
 * DM_DEV_CREATE:
 * Create a new device, neither the 'active' or 'inactive' table
 * slots will be filled.  The device will be in suspended state
 * after creation, however any io to the device will get errored
 * since it will be out-of-bounds.
 *
 * DM_DEV_REMOVE:
 * Remove a device, destroy any tables.
 *
 * DM_DEV_RENAME:
 * Rename a device or set its uuid अगर none was previously supplied.
 *
 * DM_SUSPEND:
 * This perक्रमms both suspend and resume, depending which flag is
 * passed in.
 * Suspend: This command will not वापस until all pending io to
 * the device has completed.  Further io will be deferred until
 * the device is resumed.
 * Resume: It is no दीर्घer an error to issue this command on an
 * unsuspended device.  If a table is present in the 'inactive'
 * slot, it will be moved to the active slot, then the old table
 * from the active slot will be _destroyed_.  Finally the device
 * is resumed.
 *
 * DM_DEV_STATUS:
 * Retrieves the status क्रम the table in the 'active' slot.
 *
 * DM_DEV_WAIT:
 * Wait क्रम a signअगरicant event to occur to the device.  This
 * could either be caused by an event triggered by one of the
 * tarमाला_लो of the table in the 'active' slot, or a table change.
 *
 * DM_TABLE_LOAD:
 * Load a table पूर्णांकo the 'inactive' slot क्रम the device.  The
 * device करोes _not_ need to be suspended prior to this command.
 *
 * DM_TABLE_CLEAR:
 * Destroy any table in the 'inactive' slot (ie. पात).
 *
 * DM_TABLE_DEPS:
 * Return a set of device dependencies क्रम the 'active' table.
 *
 * DM_TABLE_STATUS:
 * Return the tarमाला_लो status क्रम the 'active' table.
 *
 * DM_TARGET_MSG:
 * Pass a message string to the target at a specअगरic offset of a device.
 *
 * DM_DEV_SET_GEOMETRY:
 * Set the geometry of a device by passing in a string in this क्रमmat:
 *
 * "cylinders heads sectors_per_track start_sector"
 *
 * Beware that CHS geometry is nearly obsolete and only provided
 * क्रम compatibility with dm devices that can be booted by a PC
 * BIOS.  See काष्ठा hd_geometry क्रम range limits.  Also note that
 * the geometry is erased अगर the device size changes.
 */

/*
 * All ioctl arguments consist of a single chunk of memory, with
 * this काष्ठाure at the start.  If a uuid is specअगरied any
 * lookup (eg. क्रम a DM_INFO) will be करोne on that, *not* the
 * name.
 */
काष्ठा dm_ioctl अणु
	/*
	 * The version number is made up of three parts:
	 * major - no backward or क्रमward compatibility,
	 * minor - only backwards compatible,
	 * patch - both backwards and क्रमwards compatible.
	 *
	 * All clients of the ioctl पूर्णांकerface should fill in the
	 * version number of the पूर्णांकerface that they were
	 * compiled with.
	 *
	 * All recognised ioctl commands (ie. those that करोn't
	 * वापस -ENOTTY) fill out this field, even अगर the
	 * command failed.
	 */
	__u32 version[3];	/* in/out */
	__u32 data_size;	/* total size of data passed in
				 * including this काष्ठा */

	__u32 data_start;	/* offset to start of data
				 * relative to start of this काष्ठा */

	__u32 target_count;	/* in/out */
	__s32 खोलो_count;	/* out */
	__u32 flags;		/* in/out */

	/*
	 * event_nr holds either the event number (input and output) or the
	 * udev cookie value (input only).
	 * The DM_DEV_WAIT ioctl takes an event number as input.
	 * The DM_SUSPEND, DM_DEV_REMOVE and DM_DEV_RENAME ioctls
	 * use the field as a cookie to वापस in the DM_COOKIE
	 * variable with the uevents they issue.
	 * For output, the ioctls वापस the event number, not the cookie.
	 */
	__u32 event_nr;      	/* in/out */
	__u32 padding;

	__u64 dev;		/* in/out */

	अक्षर name[DM_NAME_LEN];	/* device name */
	अक्षर uuid[DM_UUID_LEN];	/* unique identअगरier क्रम
				 * the block device */
	अक्षर data[7];		/* padding or data */
पूर्ण;

/*
 * Used to specअगरy tables.  These काष्ठाures appear after the
 * dm_ioctl.
 */
काष्ठा dm_target_spec अणु
	__u64 sector_start;
	__u64 length;
	__s32 status;		/* used when पढ़ोing from kernel only */

	/*
	 * Location of the next dm_target_spec.
	 * - When specअगरying tarमाला_लो on a DM_TABLE_LOAD command, this value is
	 *   the number of bytes from the start of the "current" dm_target_spec
	 *   to the start of the "next" dm_target_spec.
	 * - When retrieving tarमाला_लो on a DM_TABLE_STATUS command, this value
	 *   is the number of bytes from the start of the first dm_target_spec
	 *   (that follows the dm_ioctl काष्ठा) to the start of the "next"
	 *   dm_target_spec.
	 */
	__u32 next;

	अक्षर target_type[DM_MAX_TYPE_NAME];

	/*
	 * Parameter string starts immediately after this object.
	 * Be careful to add padding after string to ensure correct
	 * alignment of subsequent dm_target_spec.
	 */
पूर्ण;

/*
 * Used to retrieve the target dependencies.
 */
काष्ठा dm_target_deps अणु
	__u32 count;	/* Array size */
	__u32 padding;	/* unused */
	__u64 dev[0];	/* out */
पूर्ण;

/*
 * Used to get a list of all dm devices.
 */
काष्ठा dm_name_list अणु
	__u64 dev;
	__u32 next;		/* offset to the next record from
				   the _start_ of this */
	अक्षर name[0];

	/*
	 * The following members can be accessed by taking a poपूर्णांकer that
	 * poपूर्णांकs immediately after the terminating zero अक्षरacter in "name"
	 * and aligning this poपूर्णांकer to next 8-byte boundary.
	 * Uuid is present अगर the flag DM_NAME_LIST_FLAG_HAS_UUID is set.
	 *
	 * __u32 event_nr;
	 * __u32 flags;
	 * अक्षर uuid[0];
	 */
पूर्ण;

#घोषणा DM_NAME_LIST_FLAG_HAS_UUID		1
#घोषणा DM_NAME_LIST_FLAG_DOESNT_HAVE_UUID	2

/*
 * Used to retrieve the target versions
 */
काष्ठा dm_target_versions अणु
        __u32 next;
        __u32 version[3];

        अक्षर name[0];
पूर्ण;

/*
 * Used to pass message to a target
 */
काष्ठा dm_target_msg अणु
	__u64 sector;	/* Device sector */

	अक्षर message[0];
पूर्ण;

/*
 * If you change this make sure you make the corresponding change
 * to dm-ioctl.c:lookup_ioctl()
 */
क्रमागत अणु
	/* Top level cmds */
	DM_VERSION_CMD = 0,
	DM_REMOVE_ALL_CMD,
	DM_LIST_DEVICES_CMD,

	/* device level cmds */
	DM_DEV_CREATE_CMD,
	DM_DEV_REMOVE_CMD,
	DM_DEV_RENAME_CMD,
	DM_DEV_SUSPEND_CMD,
	DM_DEV_STATUS_CMD,
	DM_DEV_WAIT_CMD,

	/* Table level cmds */
	DM_TABLE_LOAD_CMD,
	DM_TABLE_CLEAR_CMD,
	DM_TABLE_DEPS_CMD,
	DM_TABLE_STATUS_CMD,

	/* Added later */
	DM_LIST_VERSIONS_CMD,
	DM_TARGET_MSG_CMD,
	DM_DEV_SET_GEOMETRY_CMD,
	DM_DEV_ARM_POLL_CMD,
	DM_GET_TARGET_VERSION_CMD,
पूर्ण;

#घोषणा DM_IOCTL 0xfd

#घोषणा DM_VERSION       _IOWR(DM_IOCTL, DM_VERSION_CMD, काष्ठा dm_ioctl)
#घोषणा DM_REMOVE_ALL    _IOWR(DM_IOCTL, DM_REMOVE_ALL_CMD, काष्ठा dm_ioctl)
#घोषणा DM_LIST_DEVICES  _IOWR(DM_IOCTL, DM_LIST_DEVICES_CMD, काष्ठा dm_ioctl)

#घोषणा DM_DEV_CREATE    _IOWR(DM_IOCTL, DM_DEV_CREATE_CMD, काष्ठा dm_ioctl)
#घोषणा DM_DEV_REMOVE    _IOWR(DM_IOCTL, DM_DEV_REMOVE_CMD, काष्ठा dm_ioctl)
#घोषणा DM_DEV_RENAME    _IOWR(DM_IOCTL, DM_DEV_RENAME_CMD, काष्ठा dm_ioctl)
#घोषणा DM_DEV_SUSPEND   _IOWR(DM_IOCTL, DM_DEV_SUSPEND_CMD, काष्ठा dm_ioctl)
#घोषणा DM_DEV_STATUS    _IOWR(DM_IOCTL, DM_DEV_STATUS_CMD, काष्ठा dm_ioctl)
#घोषणा DM_DEV_WAIT      _IOWR(DM_IOCTL, DM_DEV_WAIT_CMD, काष्ठा dm_ioctl)
#घोषणा DM_DEV_ARM_POLL  _IOWR(DM_IOCTL, DM_DEV_ARM_POLL_CMD, काष्ठा dm_ioctl)

#घोषणा DM_TABLE_LOAD    _IOWR(DM_IOCTL, DM_TABLE_LOAD_CMD, काष्ठा dm_ioctl)
#घोषणा DM_TABLE_CLEAR   _IOWR(DM_IOCTL, DM_TABLE_CLEAR_CMD, काष्ठा dm_ioctl)
#घोषणा DM_TABLE_DEPS    _IOWR(DM_IOCTL, DM_TABLE_DEPS_CMD, काष्ठा dm_ioctl)
#घोषणा DM_TABLE_STATUS  _IOWR(DM_IOCTL, DM_TABLE_STATUS_CMD, काष्ठा dm_ioctl)

#घोषणा DM_LIST_VERSIONS _IOWR(DM_IOCTL, DM_LIST_VERSIONS_CMD, काष्ठा dm_ioctl)
#घोषणा DM_GET_TARGET_VERSION _IOWR(DM_IOCTL, DM_GET_TARGET_VERSION_CMD, काष्ठा dm_ioctl)

#घोषणा DM_TARGET_MSG	 _IOWR(DM_IOCTL, DM_TARGET_MSG_CMD, काष्ठा dm_ioctl)
#घोषणा DM_DEV_SET_GEOMETRY	_IOWR(DM_IOCTL, DM_DEV_SET_GEOMETRY_CMD, काष्ठा dm_ioctl)

#घोषणा DM_VERSION_MAJOR	4
#घोषणा DM_VERSION_MINOR	45
#घोषणा DM_VERSION_PATCHLEVEL	0
#घोषणा DM_VERSION_EXTRA	"-ioctl (2021-03-22)"

/* Status bits */
#घोषणा DM_READONLY_FLAG	(1 << 0) /* In/Out */
#घोषणा DM_SUSPEND_FLAG		(1 << 1) /* In/Out */
#घोषणा DM_PERSISTENT_DEV_FLAG	(1 << 3) /* In */

/*
 * Flag passed पूर्णांकo ioctl STATUS command to get table inक्रमmation
 * rather than current status.
 */
#घोषणा DM_STATUS_TABLE_FLAG	(1 << 4) /* In */

/*
 * Flags that indicate whether a table is present in either of
 * the two table slots that a device has.
 */
#घोषणा DM_ACTIVE_PRESENT_FLAG   (1 << 5) /* Out */
#घोषणा DM_INACTIVE_PRESENT_FLAG (1 << 6) /* Out */

/*
 * Indicates that the buffer passed in wasn't big enough क्रम the
 * results.
 */
#घोषणा DM_BUFFER_FULL_FLAG	(1 << 8) /* Out */

/*
 * This flag is now ignored.
 */
#घोषणा DM_SKIP_BDGET_FLAG	(1 << 9) /* In */

/*
 * Set this to aव्योम attempting to मुक्तze any fileप्रणाली when suspending.
 */
#घोषणा DM_SKIP_LOCKFS_FLAG	(1 << 10) /* In */

/*
 * Set this to suspend without flushing queued ios.
 * Also disables flushing uncommitted changes in the thin target beक्रमe
 * generating statistics क्रम DM_TABLE_STATUS and DM_DEV_WAIT.
 */
#घोषणा DM_NOFLUSH_FLAG		(1 << 11) /* In */

/*
 * If set, any table inक्रमmation वापसed will relate to the inactive
 * table instead of the live one.  Always check DM_INACTIVE_PRESENT_FLAG
 * is set beक्रमe using the data वापसed.
 */
#घोषणा DM_QUERY_INACTIVE_TABLE_FLAG	(1 << 12) /* In */

/*
 * If set, a uevent was generated क्रम which the caller may need to रुको.
 */
#घोषणा DM_UEVENT_GENERATED_FLAG	(1 << 13) /* Out */

/*
 * If set, नाम changes the uuid not the name.  Only permitted
 * अगर no uuid was previously supplied: an existing uuid cannot be changed.
 */
#घोषणा DM_UUID_FLAG			(1 << 14) /* In */

/*
 * If set, all buffers are wiped after use. Use when sending
 * or requesting sensitive data such as an encryption key.
 */
#घोषणा DM_SECURE_DATA_FLAG		(1 << 15) /* In */

/*
 * If set, a message generated output data.
 */
#घोषणा DM_DATA_OUT_FLAG		(1 << 16) /* Out */

/*
 * If set with DM_DEV_REMOVE or DM_REMOVE_ALL this indicates that अगर
 * the device cannot be हटाओd immediately because it is still in use
 * it should instead be scheduled क्रम removal when it माला_लो बंदd.
 *
 * On वापस from DM_DEV_REMOVE, DM_DEV_STATUS or other ioctls, this
 * flag indicates that the device is scheduled to be हटाओd when it
 * माला_लो बंदd.
 */
#घोषणा DM_DEFERRED_REMOVE		(1 << 17) /* In/Out */

/*
 * If set, the device is suspended पूर्णांकernally.
 */
#घोषणा DM_INTERNAL_SUSPEND_FLAG	(1 << 18) /* Out */

#पूर्ण_अगर				/* _LINUX_DM_IOCTL_H */
