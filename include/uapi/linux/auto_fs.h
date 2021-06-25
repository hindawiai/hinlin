<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright 1997 Transmeta Corporation - All Rights Reserved
 * Copyright 1999-2000 Jeremy Fitzhardinge <jeremy@goop.org>
 * Copyright 2005-2006,2013,2017-2018 Ian Kent <raven@themaw.net>
 *
 * This file is part of the Linux kernel and is made available under
 * the terms of the GNU General Public License, version 2, or at your
 * option, any later version, incorporated herein by reference.
 *
 * ----------------------------------------------------------------------- */

#अगर_अघोषित _UAPI_LINUX_AUTO_FS_H
#घोषणा _UAPI_LINUX_AUTO_FS_H

#समावेश <linux/types.h>
#समावेश <linux/सीमा.स>
#अगर_अघोषित __KERNEL__
#समावेश <sys/ioctl.h>
#पूर्ण_अगर /* __KERNEL__ */

#घोषणा AUTOFS_PROTO_VERSION		5
#घोषणा AUTOFS_MIN_PROTO_VERSION	3
#घोषणा AUTOFS_MAX_PROTO_VERSION	5

#घोषणा AUTOFS_PROTO_SUBVERSION		5

/*
 * The रुको_queue_token (स्वतःfs_wqt_t) is part of a काष्ठाure which is passed
 * back to the kernel via ioctl from userspace. On architectures where 32- and
 * 64-bit userspace binaries can be executed it's important that the size of
 * स्वतःfs_wqt_t stays स्थिरant between 32- and 64-bit Linux kernels so that we
 * करो not अवरोध the binary ABI पूर्णांकerface by changing the काष्ठाure size.
 */
#अगर defined(__ia64__) || defined(__alpha__) /* pure 64bit architectures */
प्रकार अचिन्हित दीर्घ स्वतःfs_wqt_t;
#अन्यथा
प्रकार अचिन्हित पूर्णांक स्वतःfs_wqt_t;
#पूर्ण_अगर

/* Packet types */
#घोषणा स्वतःfs_ptype_missing	0	/* Missing entry (mount request) */
#घोषणा स्वतःfs_ptype_expire	1	/* Expire entry (umount request) */

काष्ठा स्वतःfs_packet_hdr अणु
	पूर्णांक proto_version;		/* Protocol version */
	पूर्णांक type;			/* Type of packet */
पूर्ण;

काष्ठा स्वतःfs_packet_missing अणु
	काष्ठा स्वतःfs_packet_hdr hdr;
	स्वतःfs_wqt_t रुको_queue_token;
	पूर्णांक len;
	अक्षर name[NAME_MAX+1];
पूर्ण;	

/* v3 expire (via ioctl) */
काष्ठा स्वतःfs_packet_expire अणु
	काष्ठा स्वतःfs_packet_hdr hdr;
	पूर्णांक len;
	अक्षर name[NAME_MAX+1];
पूर्ण;

#घोषणा AUTOFS_IOCTL 0x93

क्रमागत अणु
	AUTOFS_IOC_READY_CMD = 0x60,
	AUTOFS_IOC_FAIL_CMD,
	AUTOFS_IOC_CATATONIC_CMD,
	AUTOFS_IOC_PROTOVER_CMD,
	AUTOFS_IOC_SETTIMEOUT_CMD,
	AUTOFS_IOC_EXPIRE_CMD,
पूर्ण;

#घोषणा AUTOFS_IOC_READY        _IO(AUTOFS_IOCTL, AUTOFS_IOC_READY_CMD)
#घोषणा AUTOFS_IOC_FAIL         _IO(AUTOFS_IOCTL, AUTOFS_IOC_FAIL_CMD)
#घोषणा AUTOFS_IOC_CATATONIC    _IO(AUTOFS_IOCTL, AUTOFS_IOC_CATATONIC_CMD)
#घोषणा AUTOFS_IOC_PROTOVER     _IOR(AUTOFS_IOCTL, \
				     AUTOFS_IOC_PROTOVER_CMD, पूर्णांक)
#घोषणा AUTOFS_IOC_SETTIMEOUT32 _IOWR(AUTOFS_IOCTL, \
				      AUTOFS_IOC_SETTIMEOUT_CMD, \
				      compat_uदीर्घ_t)
#घोषणा AUTOFS_IOC_SETTIMEOUT   _IOWR(AUTOFS_IOCTL, \
				      AUTOFS_IOC_SETTIMEOUT_CMD, \
				      अचिन्हित दीर्घ)
#घोषणा AUTOFS_IOC_EXPIRE       _IOR(AUTOFS_IOCTL, \
				     AUTOFS_IOC_EXPIRE_CMD, \
				     काष्ठा स्वतःfs_packet_expire)

/* स्वतःfs version 4 and later definitions */

/* Mask क्रम expire behaviour */
#घोषणा AUTOFS_EXP_NORMAL		0x00
#घोषणा AUTOFS_EXP_IMMEDIATE		0x01
#घोषणा AUTOFS_EXP_LEAVES		0x02
#घोषणा AUTOFS_EXP_FORCED		0x04

#घोषणा AUTOFS_TYPE_ANY			0U
#घोषणा AUTOFS_TYPE_INसूचीECT		1U
#घोषणा AUTOFS_TYPE_सूचीECT		2U
#घोषणा AUTOFS_TYPE_OFFSET		4U

अटल अंतरभूत व्योम set_स्वतःfs_type_indirect(अचिन्हित पूर्णांक *type)
अणु
	*type = AUTOFS_TYPE_INसूचीECT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक स्वतःfs_type_indirect(अचिन्हित पूर्णांक type)
अणु
	वापस (type == AUTOFS_TYPE_INसूचीECT);
पूर्ण

अटल अंतरभूत व्योम set_स्वतःfs_type_direct(अचिन्हित पूर्णांक *type)
अणु
	*type = AUTOFS_TYPE_सूचीECT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक स्वतःfs_type_direct(अचिन्हित पूर्णांक type)
अणु
	वापस (type == AUTOFS_TYPE_सूचीECT);
पूर्ण

अटल अंतरभूत व्योम set_स्वतःfs_type_offset(अचिन्हित पूर्णांक *type)
अणु
	*type = AUTOFS_TYPE_OFFSET;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक स्वतःfs_type_offset(अचिन्हित पूर्णांक type)
अणु
	वापस (type == AUTOFS_TYPE_OFFSET);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक स्वतःfs_type_trigger(अचिन्हित पूर्णांक type)
अणु
	वापस (type == AUTOFS_TYPE_सूचीECT || type == AUTOFS_TYPE_OFFSET);
पूर्ण

/*
 * This isn't really a type as we use it to say "no type set" to
 * indicate we want to search क्रम "any" mount in the
 * स्वतःfs_dev_ioctl_ismountpoपूर्णांक() device ioctl function.
 */
अटल अंतरभूत व्योम set_स्वतःfs_type_any(अचिन्हित पूर्णांक *type)
अणु
	*type = AUTOFS_TYPE_ANY;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक स्वतःfs_type_any(अचिन्हित पूर्णांक type)
अणु
	वापस (type == AUTOFS_TYPE_ANY);
पूर्ण

/* Daemon notअगरication packet types */
क्रमागत स्वतःfs_notअगरy अणु
	NFY_NONE,
	NFY_MOUNT,
	NFY_EXPIRE
पूर्ण;

/* Kernel protocol version 4 packet types */

/* Expire entry (umount request) */
#घोषणा स्वतःfs_ptype_expire_multi	2

/* Kernel protocol version 5 packet types */

/* Indirect mount missing and expire requests. */
#घोषणा स्वतःfs_ptype_missing_indirect	3
#घोषणा स्वतःfs_ptype_expire_indirect	4

/* Direct mount missing and expire requests */
#घोषणा स्वतःfs_ptype_missing_direct	5
#घोषणा स्वतःfs_ptype_expire_direct	6

/* v4 multi expire (via pipe) */
काष्ठा स्वतःfs_packet_expire_multi अणु
	काष्ठा स्वतःfs_packet_hdr hdr;
	स्वतःfs_wqt_t रुको_queue_token;
	पूर्णांक len;
	अक्षर name[NAME_MAX+1];
पूर्ण;

जोड़ स्वतःfs_packet_जोड़ अणु
	काष्ठा स्वतःfs_packet_hdr hdr;
	काष्ठा स्वतःfs_packet_missing missing;
	काष्ठा स्वतःfs_packet_expire expire;
	काष्ठा स्वतःfs_packet_expire_multi expire_multi;
पूर्ण;

/* स्वतःfs v5 common packet काष्ठा */
काष्ठा स्वतःfs_v5_packet अणु
	काष्ठा स्वतःfs_packet_hdr hdr;
	स्वतःfs_wqt_t रुको_queue_token;
	__u32 dev;
	__u64 ino;
	__u32 uid;
	__u32 gid;
	__u32 pid;
	__u32 tgid;
	__u32 len;
	अक्षर name[NAME_MAX+1];
पूर्ण;

प्रकार काष्ठा स्वतःfs_v5_packet स्वतःfs_packet_missing_indirect_t;
प्रकार काष्ठा स्वतःfs_v5_packet स्वतःfs_packet_expire_indirect_t;
प्रकार काष्ठा स्वतःfs_v5_packet स्वतःfs_packet_missing_direct_t;
प्रकार काष्ठा स्वतःfs_v5_packet स्वतःfs_packet_expire_direct_t;

जोड़ स्वतःfs_v5_packet_जोड़ अणु
	काष्ठा स्वतःfs_packet_hdr hdr;
	काष्ठा स्वतःfs_v5_packet v5_packet;
	स्वतःfs_packet_missing_indirect_t missing_indirect;
	स्वतःfs_packet_expire_indirect_t expire_indirect;
	स्वतःfs_packet_missing_direct_t missing_direct;
	स्वतःfs_packet_expire_direct_t expire_direct;
पूर्ण;

क्रमागत अणु
	AUTOFS_IOC_EXPIRE_MULTI_CMD = 0x66, /* AUTOFS_IOC_EXPIRE_CMD + 1 */
	AUTOFS_IOC_PROTOSUBVER_CMD,
	AUTOFS_IOC_ASKUMOUNT_CMD = 0x70, /* AUTOFS_DEV_IOCTL_VERSION_CMD - 1 */
पूर्ण;

#घोषणा AUTOFS_IOC_EXPIRE_MULTI		_IOW(AUTOFS_IOCTL, \
					     AUTOFS_IOC_EXPIRE_MULTI_CMD, पूर्णांक)
#घोषणा AUTOFS_IOC_PROTOSUBVER		_IOR(AUTOFS_IOCTL, \
					     AUTOFS_IOC_PROTOSUBVER_CMD, पूर्णांक)
#घोषणा AUTOFS_IOC_ASKUMOUNT		_IOR(AUTOFS_IOCTL, \
					     AUTOFS_IOC_ASKUMOUNT_CMD, पूर्णांक)

#पूर्ण_अगर /* _UAPI_LINUX_AUTO_FS_H */
