<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright 2008 Red Hat, Inc. All rights reserved.
 * Copyright 2008 Ian Kent <raven@themaw.net>
 *
 * This file is part of the Linux kernel and is made available under
 * the terms of the GNU General Public License, version 2, or at your
 * option, any later version, incorporated herein by reference.
 */

#अगर_अघोषित _UAPI_LINUX_AUTO_DEV_IOCTL_H
#घोषणा _UAPI_LINUX_AUTO_DEV_IOCTL_H

#समावेश <linux/स्वतः_fs.h>
#समावेश <linux/माला.स>

#घोषणा AUTOFS_DEVICE_NAME		"autofs"

#घोषणा AUTOFS_DEV_IOCTL_VERSION_MAJOR	1
#घोषणा AUTOFS_DEV_IOCTL_VERSION_MINOR	1

#घोषणा AUTOFS_DEV_IOCTL_SIZE		माप(काष्ठा स्वतःfs_dev_ioctl)

/*
 * An ioctl पूर्णांकerface क्रम स्वतःfs mount poपूर्णांक control.
 */

काष्ठा args_protover अणु
	__u32	version;
पूर्ण;

काष्ठा args_protosubver अणु
	__u32	sub_version;
पूर्ण;

काष्ठा args_खोलोmount अणु
	__u32	devid;
पूर्ण;

काष्ठा args_पढ़ोy अणु
	__u32	token;
पूर्ण;

काष्ठा args_fail अणु
	__u32	token;
	__s32	status;
पूर्ण;

काष्ठा args_setpipefd अणु
	__s32	pipefd;
पूर्ण;

काष्ठा args_समयout अणु
	__u64	समयout;
पूर्ण;

काष्ठा args_requester अणु
	__u32	uid;
	__u32	gid;
पूर्ण;

काष्ठा args_expire अणु
	__u32	how;
पूर्ण;

काष्ठा args_askumount अणु
	__u32	may_umount;
पूर्ण;

काष्ठा args_ismountpoपूर्णांक अणु
	जोड़ अणु
		काष्ठा args_in अणु
			__u32	type;
		पूर्ण in;
		काष्ठा args_out अणु
			__u32	devid;
			__u32	magic;
		पूर्ण out;
	पूर्ण;
पूर्ण;

/*
 * All the ioctls use this काष्ठाure.
 * When sending a path size must account क्रम the total length
 * of the chunk of memory otherwise it is the size of the
 * काष्ठाure.
 */

काष्ठा स्वतःfs_dev_ioctl अणु
	__u32 ver_major;
	__u32 ver_minor;
	__u32 size;		/* total size of data passed in
				 * including this काष्ठा */
	__s32 ioctlfd;		/* स्वतःmount command fd */

	/* Command parameters */

	जोड़ अणु
		काष्ठा args_protover		protover;
		काष्ठा args_protosubver		protosubver;
		काष्ठा args_खोलोmount		खोलोmount;
		काष्ठा args_पढ़ोy		पढ़ोy;
		काष्ठा args_fail		fail;
		काष्ठा args_setpipefd		setpipefd;
		काष्ठा args_समयout		समयout;
		काष्ठा args_requester		requester;
		काष्ठा args_expire		expire;
		काष्ठा args_askumount		askumount;
		काष्ठा args_ismountpoपूर्णांक	ismountpoपूर्णांक;
	पूर्ण;

	अक्षर path[0];
पूर्ण;

अटल अंतरभूत व्योम init_स्वतःfs_dev_ioctl(काष्ठा स्वतःfs_dev_ioctl *in)
अणु
	स_रखो(in, 0, AUTOFS_DEV_IOCTL_SIZE);
	in->ver_major = AUTOFS_DEV_IOCTL_VERSION_MAJOR;
	in->ver_minor = AUTOFS_DEV_IOCTL_VERSION_MINOR;
	in->size = AUTOFS_DEV_IOCTL_SIZE;
	in->ioctlfd = -1;
पूर्ण

क्रमागत अणु
	/* Get various version info */
	AUTOFS_DEV_IOCTL_VERSION_CMD = 0x71,
	AUTOFS_DEV_IOCTL_PROTOVER_CMD,
	AUTOFS_DEV_IOCTL_PROTOSUBVER_CMD,

	/* Open mount ioctl fd */
	AUTOFS_DEV_IOCTL_OPENMOUNT_CMD,

	/* Close mount ioctl fd */
	AUTOFS_DEV_IOCTL_CLOSEMOUNT_CMD,

	/* Mount/expire status वापसs */
	AUTOFS_DEV_IOCTL_READY_CMD,
	AUTOFS_DEV_IOCTL_FAIL_CMD,

	/* Activate/deactivate स्वतःfs mount */
	AUTOFS_DEV_IOCTL_SETPIPEFD_CMD,
	AUTOFS_DEV_IOCTL_CATATONIC_CMD,

	/* Expiry समयout */
	AUTOFS_DEV_IOCTL_TIMEOUT_CMD,

	/* Get mount last requesting uid and gid */
	AUTOFS_DEV_IOCTL_REQUESTER_CMD,

	/* Check क्रम eligible expire candidates */
	AUTOFS_DEV_IOCTL_EXPIRE_CMD,

	/* Request busy status */
	AUTOFS_DEV_IOCTL_ASKUMOUNT_CMD,

	/* Check अगर path is a mountpoपूर्णांक */
	AUTOFS_DEV_IOCTL_ISMOUNTPOINT_CMD,
पूर्ण;

#घोषणा AUTOFS_DEV_IOCTL_VERSION \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_VERSION_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_PROTOVER \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_PROTOVER_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_PROTOSUBVER \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_PROTOSUBVER_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_OPENMOUNT \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_OPENMOUNT_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_CLOSEMOUNT \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_CLOSEMOUNT_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_READY \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_READY_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_FAIL \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_FAIL_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_SETPIPEFD \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_SETPIPEFD_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_CATATONIC \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_CATATONIC_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_TIMEOUT \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_TIMEOUT_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_REQUESTER \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_REQUESTER_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_EXPIRE \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_EXPIRE_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_ASKUMOUNT \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_ASKUMOUNT_CMD, काष्ठा स्वतःfs_dev_ioctl)

#घोषणा AUTOFS_DEV_IOCTL_ISMOUNTPOINT \
	_IOWR(AUTOFS_IOCTL, \
	      AUTOFS_DEV_IOCTL_ISMOUNTPOINT_CMD, काष्ठा स्वतःfs_dev_ioctl)

#पूर्ण_अगर	/* _UAPI_LINUX_AUTO_DEV_IOCTL_H */
