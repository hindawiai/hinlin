<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-2-Clause) */
/*
    This file defines the kernel पूर्णांकerface of FUSE
    Copyright (C) 2001-2008  Miklos Szeredi <miklos@szeredi.hu>

    This program can be distributed under the terms of the GNU GPL.
    See the file COPYING.

    This -- and only this -- header file may also be distributed under
    the terms of the BSD Licence as follows:

    Copyright (C) 2001-2007 Miklos Szeredi. All rights reserved.

    Redistribution and use in source and binary क्रमms, with or without
    modअगरication, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary क्रमm must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       करोcumentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
    FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/

/*
 * This file defines the kernel पूर्णांकerface of FUSE
 *
 * Protocol changelog:
 *
 * 7.1:
 *  - add the following messages:
 *      FUSE_SETATTR, FUSE_SYMLINK, FUSE_MKNOD, FUSE_MKसूची, FUSE_UNLINK,
 *      FUSE_RMसूची, FUSE_RENAME, FUSE_LINK, FUSE_OPEN, FUSE_READ, FUSE_WRITE,
 *      FUSE_RELEASE, FUSE_FSYNC, FUSE_FLUSH, FUSE_SETXATTR, FUSE_GETXATTR,
 *      FUSE_LISTXATTR, FUSE_REMOVEXATTR, FUSE_OPENसूची, FUSE_READसूची,
 *      FUSE_RELEASEसूची
 *  - add padding to messages to accommodate 32-bit servers on 64-bit kernels
 *
 * 7.2:
 *  - add FOPEN_सूचीECT_IO and FOPEN_KEEP_CACHE flags
 *  - add FUSE_FSYNCसूची message
 *
 * 7.3:
 *  - add FUSE_ACCESS message
 *  - add FUSE_CREATE message
 *  - add filehandle to fuse_setattr_in
 *
 * 7.4:
 *  - add frsize to fuse_kstatfs
 *  - clean up request size limit checking
 *
 * 7.5:
 *  - add flags and max_ग_लिखो to fuse_init_out
 *
 * 7.6:
 *  - add max_पढ़ोahead to fuse_init_in and fuse_init_out
 *
 * 7.7:
 *  - add FUSE_INTERRUPT message
 *  - add POSIX file lock support
 *
 * 7.8:
 *  - add lock_owner and flags fields to fuse_release_in
 *  - add FUSE_BMAP message
 *  - add FUSE_DESTROY message
 *
 * 7.9:
 *  - new fuse_getattr_in input argument of GETATTR
 *  - add lk_flags in fuse_lk_in
 *  - add lock_owner field to fuse_setattr_in, fuse_पढ़ो_in and fuse_ग_लिखो_in
 *  - add blksize field to fuse_attr
 *  - add file flags field to fuse_पढ़ो_in and fuse_ग_लिखो_in
 *  - Add ATIME_NOW and MTIME_NOW flags to fuse_setattr_in
 *
 * 7.10
 *  - add nonseekable खोलो flag
 *
 * 7.11
 *  - add IOCTL message
 *  - add unsolicited notअगरication support
 *  - add POLL message and NOTIFY_POLL notअगरication
 *
 * 7.12
 *  - add umask flag to input argument of create, mknod and सूची_गढ़ो
 *  - add notअगरication messages क्रम invalidation of inodes and
 *    directory entries
 *
 * 7.13
 *  - make max number of background requests and congestion threshold
 *    tunables
 *
 * 7.14
 *  - add splice support to fuse device
 *
 * 7.15
 *  - add store notअगरy
 *  - add retrieve notअगरy
 *
 * 7.16
 *  - add BATCH_FORGET request
 *  - FUSE_IOCTL_UNRESTRICTED shall now वापस with array of 'काष्ठा
 *    fuse_ioctl_iovec' instead of ambiguous 'struct iovec'
 *  - add FUSE_IOCTL_32BIT flag
 *
 * 7.17
 *  - add FUSE_FLOCK_LOCKS and FUSE_RELEASE_FLOCK_UNLOCK
 *
 * 7.18
 *  - add FUSE_IOCTL_सूची flag
 *  - add FUSE_NOTIFY_DELETE
 *
 * 7.19
 *  - add FUSE_FALLOCATE
 *
 * 7.20
 *  - add FUSE_AUTO_INVAL_DATA
 *
 * 7.21
 *  - add FUSE_READसूचीPLUS
 *  - send the requested events in POLL request
 *
 * 7.22
 *  - add FUSE_ASYNC_DIO
 *
 * 7.23
 *  - add FUSE_WRITEBACK_CACHE
 *  - add समय_gran to fuse_init_out
 *  - add reserved space to fuse_init_out
 *  - add FATTR_CTIME
 *  - add स_समय and स_समयnsec to fuse_setattr_in
 *  - add FUSE_RENAME2 request
 *  - add FUSE_NO_OPEN_SUPPORT flag
 *
 *  7.24
 *  - add FUSE_LSEEK क्रम SEEK_HOLE and SEEK_DATA support
 *
 *  7.25
 *  - add FUSE_PARALLEL_सूचीOPS
 *
 *  7.26
 *  - add FUSE_HANDLE_KILLPRIV
 *  - add FUSE_POSIX_ACL
 *
 *  7.27
 *  - add FUSE_ABORT_ERROR
 *
 *  7.28
 *  - add FUSE_COPY_खाता_RANGE
 *  - add FOPEN_CACHE_सूची
 *  - add FUSE_MAX_PAGES, add max_pages to init_out
 *  - add FUSE_CACHE_SYMLINKS
 *
 *  7.29
 *  - add FUSE_NO_OPENसूची_SUPPORT flag
 *
 *  7.30
 *  - add FUSE_EXPLICIT_INVAL_DATA
 *  - add FUSE_IOCTL_COMPAT_X32
 *
 *  7.31
 *  - add FUSE_WRITE_KILL_PRIV flag
 *  - add FUSE_SETUPMAPPING and FUSE_REMOVEMAPPING
 *  - add map_alignment to fuse_init_out, add FUSE_MAP_ALIGNMENT flag
 *
 *  7.32
 *  - add flags to fuse_attr, add FUSE_ATTR_SUBMOUNT, add FUSE_SUBMOUNTS
 *
 *  7.33
 *  - add FUSE_HANDLE_KILLPRIV_V2, FUSE_WRITE_KILL_SUIDGID, FATTR_KILL_SUIDGID
 *  - add FUSE_OPEN_KILL_SUIDGID
 *  - extend fuse_setxattr_in, add FUSE_SETXATTR_EXT
 *  - add FUSE_SETXATTR_ACL_KILL_SGID
 */

#अगर_अघोषित _LINUX_FUSE_H
#घोषणा _LINUX_FUSE_H

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#अन्यथा
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर

/*
 * Version negotiation:
 *
 * Both the kernel and userspace send the version they support in the
 * INIT request and reply respectively.
 *
 * If the major versions match then both shall use the smallest
 * of the two minor versions क्रम communication.
 *
 * If the kernel supports a larger major version, then userspace shall
 * reply with the major version it supports, ignore the rest of the
 * INIT message and expect a new INIT message from the kernel with a
 * matching major version.
 *
 * If the library supports a larger major version, then it shall fall
 * back to the major protocol version sent by the kernel क्रम
 * communication and reply with that major version (and an arbitrary
 * supported minor version).
 */

/** Version number of this पूर्णांकerface */
#घोषणा FUSE_KERNEL_VERSION 7

/** Minor version number of this पूर्णांकerface */
#घोषणा FUSE_KERNEL_MINOR_VERSION 33

/** The node ID of the root inode */
#घोषणा FUSE_ROOT_ID 1

/* Make sure all काष्ठाures are padded to 64bit boundary, so 32bit
   userspace works under 64bit kernels */

काष्ठा fuse_attr अणु
	uपूर्णांक64_t	ino;
	uपूर्णांक64_t	size;
	uपूर्णांक64_t	blocks;
	uपूर्णांक64_t	aसमय;
	uपूर्णांक64_t	mसमय;
	uपूर्णांक64_t	स_समय;
	uपूर्णांक32_t	aसमयnsec;
	uपूर्णांक32_t	mसमयnsec;
	uपूर्णांक32_t	स_समयnsec;
	uपूर्णांक32_t	mode;
	uपूर्णांक32_t	nlink;
	uपूर्णांक32_t	uid;
	uपूर्णांक32_t	gid;
	uपूर्णांक32_t	rdev;
	uपूर्णांक32_t	blksize;
	uपूर्णांक32_t	flags;
पूर्ण;

काष्ठा fuse_kstatfs अणु
	uपूर्णांक64_t	blocks;
	uपूर्णांक64_t	bमुक्त;
	uपूर्णांक64_t	bavail;
	uपूर्णांक64_t	files;
	uपूर्णांक64_t	fमुक्त;
	uपूर्णांक32_t	bsize;
	uपूर्णांक32_t	namelen;
	uपूर्णांक32_t	frsize;
	uपूर्णांक32_t	padding;
	uपूर्णांक32_t	spare[6];
पूर्ण;

काष्ठा fuse_file_lock अणु
	uपूर्णांक64_t	start;
	uपूर्णांक64_t	end;
	uपूर्णांक32_t	type;
	uपूर्णांक32_t	pid; /* tgid */
पूर्ण;

/**
 * Biपंचांगasks क्रम fuse_setattr_in.valid
 */
#घोषणा FATTR_MODE	(1 << 0)
#घोषणा FATTR_UID	(1 << 1)
#घोषणा FATTR_GID	(1 << 2)
#घोषणा FATTR_SIZE	(1 << 3)
#घोषणा FATTR_ATIME	(1 << 4)
#घोषणा FATTR_MTIME	(1 << 5)
#घोषणा FATTR_FH	(1 << 6)
#घोषणा FATTR_ATIME_NOW	(1 << 7)
#घोषणा FATTR_MTIME_NOW	(1 << 8)
#घोषणा FATTR_LOCKOWNER	(1 << 9)
#घोषणा FATTR_CTIME	(1 << 10)
#घोषणा FATTR_KILL_SUIDGID	(1 << 11)

/**
 * Flags वापसed by the OPEN request
 *
 * FOPEN_सूचीECT_IO: bypass page cache क्रम this खोलो file
 * FOPEN_KEEP_CACHE: करोn't invalidate the data cache on खोलो
 * FOPEN_NONSEEKABLE: the file is not seekable
 * FOPEN_CACHE_सूची: allow caching this directory
 * FOPEN_STREAM: the file is stream-like (no file position at all)
 */
#घोषणा FOPEN_सूचीECT_IO		(1 << 0)
#घोषणा FOPEN_KEEP_CACHE	(1 << 1)
#घोषणा FOPEN_NONSEEKABLE	(1 << 2)
#घोषणा FOPEN_CACHE_सूची		(1 << 3)
#घोषणा FOPEN_STREAM		(1 << 4)

/**
 * INIT request/reply flags
 *
 * FUSE_ASYNC_READ: asynchronous पढ़ो requests
 * FUSE_POSIX_LOCKS: remote locking क्रम POSIX file locks
 * FUSE_खाता_OPS: kernel sends file handle क्रम ख_स्थिति, etc... (not yet supported)
 * FUSE_ATOMIC_O_TRUNC: handles the O_TRUNC खोलो flag in the fileप्रणाली
 * FUSE_EXPORT_SUPPORT: fileप्रणाली handles lookups of "." and ".."
 * FUSE_BIG_WRITES: fileप्रणाली can handle ग_लिखो size larger than 4kB
 * FUSE_DONT_MASK: करोn't apply umask to file mode on create operations
 * FUSE_SPLICE_WRITE: kernel supports splice ग_लिखो on the device
 * FUSE_SPLICE_MOVE: kernel supports splice move on the device
 * FUSE_SPLICE_READ: kernel supports splice पढ़ो on the device
 * FUSE_FLOCK_LOCKS: remote locking क्रम BSD style file locks
 * FUSE_HAS_IOCTL_सूची: kernel supports ioctl on directories
 * FUSE_AUTO_INVAL_DATA: स्वतःmatically invalidate cached pages
 * FUSE_DO_READसूचीPLUS: करो READसूचीPLUS (READसूची+LOOKUP in one)
 * FUSE_READसूचीPLUS_AUTO: adaptive सूची_पढ़ोplus
 * FUSE_ASYNC_DIO: asynchronous direct I/O submission
 * FUSE_WRITEBACK_CACHE: use ग_लिखोback cache क्रम buffered ग_लिखोs
 * FUSE_NO_OPEN_SUPPORT: kernel supports zero-message खोलोs
 * FUSE_PARALLEL_सूचीOPS: allow parallel lookups and सूची_पढ़ो
 * FUSE_HANDLE_KILLPRIV: fs handles समाप्तing suid/sgid/cap on ग_लिखो/chown/trunc
 * FUSE_POSIX_ACL: fileप्रणाली supports posix acls
 * FUSE_ABORT_ERROR: पढ़ोing the device after पात वापसs ECONNABORTED
 * FUSE_MAX_PAGES: init_out.max_pages contains the max number of req pages
 * FUSE_CACHE_SYMLINKS: cache READLINK responses
 * FUSE_NO_OPENसूची_SUPPORT: kernel supports zero-message सूची_खोलो
 * FUSE_EXPLICIT_INVAL_DATA: only invalidate cached pages on explicit request
 * FUSE_MAP_ALIGNMENT: init_out.map_alignment contains log2(byte alignment) क्रम
 *		       foffset and moffset fields in काष्ठा
 *		       fuse_setupmapping_out and fuse_हटाओmapping_one.
 * FUSE_SUBMOUNTS: kernel supports स्वतः-mounting directory submounts
 * FUSE_HANDLE_KILLPRIV_V2: fs समाप्तs suid/sgid/cap on ग_लिखो/chown/trunc.
 *			Upon ग_लिखो/truncate suid/sgid is only समाप्तed अगर caller
 *			करोes not have CAP_FSETID. Additionally upon
 *			ग_लिखो/truncate sgid is समाप्तed only अगर file has group
 *			execute permission. (Same as Linux VFS behavior).
 * FUSE_SETXATTR_EXT:	Server supports extended काष्ठा fuse_setxattr_in
 */
#घोषणा FUSE_ASYNC_READ		(1 << 0)
#घोषणा FUSE_POSIX_LOCKS	(1 << 1)
#घोषणा FUSE_खाता_OPS		(1 << 2)
#घोषणा FUSE_ATOMIC_O_TRUNC	(1 << 3)
#घोषणा FUSE_EXPORT_SUPPORT	(1 << 4)
#घोषणा FUSE_BIG_WRITES		(1 << 5)
#घोषणा FUSE_DONT_MASK		(1 << 6)
#घोषणा FUSE_SPLICE_WRITE	(1 << 7)
#घोषणा FUSE_SPLICE_MOVE	(1 << 8)
#घोषणा FUSE_SPLICE_READ	(1 << 9)
#घोषणा FUSE_FLOCK_LOCKS	(1 << 10)
#घोषणा FUSE_HAS_IOCTL_सूची	(1 << 11)
#घोषणा FUSE_AUTO_INVAL_DATA	(1 << 12)
#घोषणा FUSE_DO_READसूचीPLUS	(1 << 13)
#घोषणा FUSE_READसूचीPLUS_AUTO	(1 << 14)
#घोषणा FUSE_ASYNC_DIO		(1 << 15)
#घोषणा FUSE_WRITEBACK_CACHE	(1 << 16)
#घोषणा FUSE_NO_OPEN_SUPPORT	(1 << 17)
#घोषणा FUSE_PARALLEL_सूचीOPS    (1 << 18)
#घोषणा FUSE_HANDLE_KILLPRIV	(1 << 19)
#घोषणा FUSE_POSIX_ACL		(1 << 20)
#घोषणा FUSE_ABORT_ERROR	(1 << 21)
#घोषणा FUSE_MAX_PAGES		(1 << 22)
#घोषणा FUSE_CACHE_SYMLINKS	(1 << 23)
#घोषणा FUSE_NO_OPENसूची_SUPPORT (1 << 24)
#घोषणा FUSE_EXPLICIT_INVAL_DATA (1 << 25)
#घोषणा FUSE_MAP_ALIGNMENT	(1 << 26)
#घोषणा FUSE_SUBMOUNTS		(1 << 27)
#घोषणा FUSE_HANDLE_KILLPRIV_V2	(1 << 28)
#घोषणा FUSE_SETXATTR_EXT	(1 << 29)

/**
 * CUSE INIT request/reply flags
 *
 * CUSE_UNRESTRICTED_IOCTL:  use unrestricted ioctl
 */
#घोषणा CUSE_UNRESTRICTED_IOCTL	(1 << 0)

/**
 * Release flags
 */
#घोषणा FUSE_RELEASE_FLUSH	(1 << 0)
#घोषणा FUSE_RELEASE_FLOCK_UNLOCK	(1 << 1)

/**
 * Getattr flags
 */
#घोषणा FUSE_GETATTR_FH		(1 << 0)

/**
 * Lock flags
 */
#घोषणा FUSE_LK_FLOCK		(1 << 0)

/**
 * WRITE flags
 *
 * FUSE_WRITE_CACHE: delayed ग_लिखो from page cache, file handle is guessed
 * FUSE_WRITE_LOCKOWNER: lock_owner field is valid
 * FUSE_WRITE_KILL_SUIDGID: समाप्त suid and sgid bits
 */
#घोषणा FUSE_WRITE_CACHE	(1 << 0)
#घोषणा FUSE_WRITE_LOCKOWNER	(1 << 1)
#घोषणा FUSE_WRITE_KILL_SUIDGID (1 << 2)

/* Obsolete alias; this flag implies समाप्तing suid/sgid only. */
#घोषणा FUSE_WRITE_KILL_PRIV	FUSE_WRITE_KILL_SUIDGID

/**
 * Read flags
 */
#घोषणा FUSE_READ_LOCKOWNER	(1 << 1)

/**
 * Ioctl flags
 *
 * FUSE_IOCTL_COMPAT: 32bit compat ioctl on 64bit machine
 * FUSE_IOCTL_UNRESTRICTED: not restricted to well-क्रमmed ioctls, retry allowed
 * FUSE_IOCTL_RETRY: retry with new iovecs
 * FUSE_IOCTL_32BIT: 32bit ioctl
 * FUSE_IOCTL_सूची: is a directory
 * FUSE_IOCTL_COMPAT_X32: x32 compat ioctl on 64bit machine (64bit समय_प्रकार)
 *
 * FUSE_IOCTL_MAX_IOV: maximum of in_iovecs + out_iovecs
 */
#घोषणा FUSE_IOCTL_COMPAT	(1 << 0)
#घोषणा FUSE_IOCTL_UNRESTRICTED	(1 << 1)
#घोषणा FUSE_IOCTL_RETRY	(1 << 2)
#घोषणा FUSE_IOCTL_32BIT	(1 << 3)
#घोषणा FUSE_IOCTL_सूची		(1 << 4)
#घोषणा FUSE_IOCTL_COMPAT_X32	(1 << 5)

#घोषणा FUSE_IOCTL_MAX_IOV	256

/**
 * Poll flags
 *
 * FUSE_POLL_SCHEDULE_NOTIFY: request poll notअगरy
 */
#घोषणा FUSE_POLL_SCHEDULE_NOTIFY (1 << 0)

/**
 * Fsync flags
 *
 * FUSE_FSYNC_FDATASYNC: Sync data only, not metadata
 */
#घोषणा FUSE_FSYNC_FDATASYNC	(1 << 0)

/**
 * fuse_attr flags
 *
 * FUSE_ATTR_SUBMOUNT: Object is a submount root
 */
#घोषणा FUSE_ATTR_SUBMOUNT      (1 << 0)

/**
 * Open flags
 * FUSE_OPEN_KILL_SUIDGID: Kill suid and sgid अगर executable
 */
#घोषणा FUSE_OPEN_KILL_SUIDGID	(1 << 0)

/**
 * setxattr flags
 * FUSE_SETXATTR_ACL_KILL_SGID: Clear SGID when प्रणाली.posix_acl_access is set
 */
#घोषणा FUSE_SETXATTR_ACL_KILL_SGID	(1 << 0)

क्रमागत fuse_opcode अणु
	FUSE_LOOKUP		= 1,
	FUSE_FORGET		= 2,  /* no reply */
	FUSE_GETATTR		= 3,
	FUSE_SETATTR		= 4,
	FUSE_READLINK		= 5,
	FUSE_SYMLINK		= 6,
	FUSE_MKNOD		= 8,
	FUSE_MKसूची		= 9,
	FUSE_UNLINK		= 10,
	FUSE_RMसूची		= 11,
	FUSE_RENAME		= 12,
	FUSE_LINK		= 13,
	FUSE_OPEN		= 14,
	FUSE_READ		= 15,
	FUSE_WRITE		= 16,
	FUSE_STATFS		= 17,
	FUSE_RELEASE		= 18,
	FUSE_FSYNC		= 20,
	FUSE_SETXATTR		= 21,
	FUSE_GETXATTR		= 22,
	FUSE_LISTXATTR		= 23,
	FUSE_REMOVEXATTR	= 24,
	FUSE_FLUSH		= 25,
	FUSE_INIT		= 26,
	FUSE_OPENसूची		= 27,
	FUSE_READसूची		= 28,
	FUSE_RELEASEसूची		= 29,
	FUSE_FSYNCसूची		= 30,
	FUSE_GETLK		= 31,
	FUSE_SETLK		= 32,
	FUSE_SETLKW		= 33,
	FUSE_ACCESS		= 34,
	FUSE_CREATE		= 35,
	FUSE_INTERRUPT		= 36,
	FUSE_BMAP		= 37,
	FUSE_DESTROY		= 38,
	FUSE_IOCTL		= 39,
	FUSE_POLL		= 40,
	FUSE_NOTIFY_REPLY	= 41,
	FUSE_BATCH_FORGET	= 42,
	FUSE_FALLOCATE		= 43,
	FUSE_READसूचीPLUS	= 44,
	FUSE_RENAME2		= 45,
	FUSE_LSEEK		= 46,
	FUSE_COPY_खाता_RANGE	= 47,
	FUSE_SETUPMAPPING	= 48,
	FUSE_REMOVEMAPPING	= 49,

	/* CUSE specअगरic operations */
	CUSE_INIT		= 4096,

	/* Reserved opcodes: helpful to detect काष्ठाure endian-ness */
	CUSE_INIT_BSWAP_RESERVED	= 1048576,	/* CUSE_INIT << 8 */
	FUSE_INIT_BSWAP_RESERVED	= 436207616,	/* FUSE_INIT << 24 */
पूर्ण;

क्रमागत fuse_notअगरy_code अणु
	FUSE_NOTIFY_POLL   = 1,
	FUSE_NOTIFY_INVAL_INODE = 2,
	FUSE_NOTIFY_INVAL_ENTRY = 3,
	FUSE_NOTIFY_STORE = 4,
	FUSE_NOTIFY_RETRIEVE = 5,
	FUSE_NOTIFY_DELETE = 6,
	FUSE_NOTIFY_CODE_MAX,
पूर्ण;

/* The पढ़ो buffer is required to be at least 8k, but may be much larger */
#घोषणा FUSE_MIN_READ_BUFFER 8192

#घोषणा FUSE_COMPAT_ENTRY_OUT_SIZE 120

काष्ठा fuse_entry_out अणु
	uपूर्णांक64_t	nodeid;		/* Inode ID */
	uपूर्णांक64_t	generation;	/* Inode generation: nodeid:gen must
					   be unique क्रम the fs's lअगरeसमय */
	uपूर्णांक64_t	entry_valid;	/* Cache समयout क्रम the name */
	uपूर्णांक64_t	attr_valid;	/* Cache समयout क्रम the attributes */
	uपूर्णांक32_t	entry_valid_nsec;
	uपूर्णांक32_t	attr_valid_nsec;
	काष्ठा fuse_attr attr;
पूर्ण;

काष्ठा fuse_क्रमget_in अणु
	uपूर्णांक64_t	nlookup;
पूर्ण;

काष्ठा fuse_क्रमget_one अणु
	uपूर्णांक64_t	nodeid;
	uपूर्णांक64_t	nlookup;
पूर्ण;

काष्ठा fuse_batch_क्रमget_in अणु
	uपूर्णांक32_t	count;
	uपूर्णांक32_t	dummy;
पूर्ण;

काष्ठा fuse_getattr_in अणु
	uपूर्णांक32_t	getattr_flags;
	uपूर्णांक32_t	dummy;
	uपूर्णांक64_t	fh;
पूर्ण;

#घोषणा FUSE_COMPAT_ATTR_OUT_SIZE 96

काष्ठा fuse_attr_out अणु
	uपूर्णांक64_t	attr_valid;	/* Cache समयout क्रम the attributes */
	uपूर्णांक32_t	attr_valid_nsec;
	uपूर्णांक32_t	dummy;
	काष्ठा fuse_attr attr;
पूर्ण;

#घोषणा FUSE_COMPAT_MKNOD_IN_SIZE 8

काष्ठा fuse_mknod_in अणु
	uपूर्णांक32_t	mode;
	uपूर्णांक32_t	rdev;
	uपूर्णांक32_t	umask;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_सूची_गढ़ो_in अणु
	uपूर्णांक32_t	mode;
	uपूर्णांक32_t	umask;
पूर्ण;

काष्ठा fuse_नाम_in अणु
	uपूर्णांक64_t	newdir;
पूर्ण;

काष्ठा fuse_नाम2_in अणु
	uपूर्णांक64_t	newdir;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_link_in अणु
	uपूर्णांक64_t	oldnodeid;
पूर्ण;

काष्ठा fuse_setattr_in अणु
	uपूर्णांक32_t	valid;
	uपूर्णांक32_t	padding;
	uपूर्णांक64_t	fh;
	uपूर्णांक64_t	size;
	uपूर्णांक64_t	lock_owner;
	uपूर्णांक64_t	aसमय;
	uपूर्णांक64_t	mसमय;
	uपूर्णांक64_t	स_समय;
	uपूर्णांक32_t	aसमयnsec;
	uपूर्णांक32_t	mसमयnsec;
	uपूर्णांक32_t	स_समयnsec;
	uपूर्णांक32_t	mode;
	uपूर्णांक32_t	unused4;
	uपूर्णांक32_t	uid;
	uपूर्णांक32_t	gid;
	uपूर्णांक32_t	unused5;
पूर्ण;

काष्ठा fuse_खोलो_in अणु
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	खोलो_flags;	/* FUSE_OPEN_... */
पूर्ण;

काष्ठा fuse_create_in अणु
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	mode;
	uपूर्णांक32_t	umask;
	uपूर्णांक32_t	खोलो_flags;	/* FUSE_OPEN_... */
पूर्ण;

काष्ठा fuse_खोलो_out अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक32_t	खोलो_flags;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_release_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	release_flags;
	uपूर्णांक64_t	lock_owner;
पूर्ण;

काष्ठा fuse_flush_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक32_t	unused;
	uपूर्णांक32_t	padding;
	uपूर्णांक64_t	lock_owner;
पूर्ण;

काष्ठा fuse_पढ़ो_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक64_t	offset;
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	पढ़ो_flags;
	uपूर्णांक64_t	lock_owner;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	padding;
पूर्ण;

#घोषणा FUSE_COMPAT_WRITE_IN_SIZE 24

काष्ठा fuse_ग_लिखो_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक64_t	offset;
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	ग_लिखो_flags;
	uपूर्णांक64_t	lock_owner;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_ग_लिखो_out अणु
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	padding;
पूर्ण;

#घोषणा FUSE_COMPAT_STATFS_SIZE 48

काष्ठा fuse_statfs_out अणु
	काष्ठा fuse_kstatfs st;
पूर्ण;

काष्ठा fuse_fsync_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक32_t	fsync_flags;
	uपूर्णांक32_t	padding;
पूर्ण;

#घोषणा FUSE_COMPAT_SETXATTR_IN_SIZE 8

काष्ठा fuse_setxattr_in अणु
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	setxattr_flags;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_getxattr_in अणु
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_getxattr_out अणु
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_lk_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक64_t	owner;
	काष्ठा fuse_file_lock lk;
	uपूर्णांक32_t	lk_flags;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_lk_out अणु
	काष्ठा fuse_file_lock lk;
पूर्ण;

काष्ठा fuse_access_in अणु
	uपूर्णांक32_t	mask;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_init_in अणु
	uपूर्णांक32_t	major;
	uपूर्णांक32_t	minor;
	uपूर्णांक32_t	max_पढ़ोahead;
	uपूर्णांक32_t	flags;
पूर्ण;

#घोषणा FUSE_COMPAT_INIT_OUT_SIZE 8
#घोषणा FUSE_COMPAT_22_INIT_OUT_SIZE 24

काष्ठा fuse_init_out अणु
	uपूर्णांक32_t	major;
	uपूर्णांक32_t	minor;
	uपूर्णांक32_t	max_पढ़ोahead;
	uपूर्णांक32_t	flags;
	uपूर्णांक16_t	max_background;
	uपूर्णांक16_t	congestion_threshold;
	uपूर्णांक32_t	max_ग_लिखो;
	uपूर्णांक32_t	समय_gran;
	uपूर्णांक16_t	max_pages;
	uपूर्णांक16_t	map_alignment;
	uपूर्णांक32_t	unused[8];
पूर्ण;

#घोषणा CUSE_INIT_INFO_MAX 4096

काष्ठा cuse_init_in अणु
	uपूर्णांक32_t	major;
	uपूर्णांक32_t	minor;
	uपूर्णांक32_t	unused;
	uपूर्णांक32_t	flags;
पूर्ण;

काष्ठा cuse_init_out अणु
	uपूर्णांक32_t	major;
	uपूर्णांक32_t	minor;
	uपूर्णांक32_t	unused;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	max_पढ़ो;
	uपूर्णांक32_t	max_ग_लिखो;
	uपूर्णांक32_t	dev_major;		/* अक्षरdev major */
	uपूर्णांक32_t	dev_minor;		/* अक्षरdev minor */
	uपूर्णांक32_t	spare[10];
पूर्ण;

काष्ठा fuse_पूर्णांकerrupt_in अणु
	uपूर्णांक64_t	unique;
पूर्ण;

काष्ठा fuse_bmap_in अणु
	uपूर्णांक64_t	block;
	uपूर्णांक32_t	blocksize;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_bmap_out अणु
	uपूर्णांक64_t	block;
पूर्ण;

काष्ठा fuse_ioctl_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	cmd;
	uपूर्णांक64_t	arg;
	uपूर्णांक32_t	in_size;
	uपूर्णांक32_t	out_size;
पूर्ण;

काष्ठा fuse_ioctl_iovec अणु
	uपूर्णांक64_t	base;
	uपूर्णांक64_t	len;
पूर्ण;

काष्ठा fuse_ioctl_out अणु
	पूर्णांक32_t		result;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	in_iovs;
	uपूर्णांक32_t	out_iovs;
पूर्ण;

काष्ठा fuse_poll_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक64_t	kh;
	uपूर्णांक32_t	flags;
	uपूर्णांक32_t	events;
पूर्ण;

काष्ठा fuse_poll_out अणु
	uपूर्णांक32_t	revents;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_notअगरy_poll_wakeup_out अणु
	uपूर्णांक64_t	kh;
पूर्ण;

काष्ठा fuse_fallocate_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक64_t	offset;
	uपूर्णांक64_t	length;
	uपूर्णांक32_t	mode;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_in_header अणु
	uपूर्णांक32_t	len;
	uपूर्णांक32_t	opcode;
	uपूर्णांक64_t	unique;
	uपूर्णांक64_t	nodeid;
	uपूर्णांक32_t	uid;
	uपूर्णांक32_t	gid;
	uपूर्णांक32_t	pid;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_out_header अणु
	uपूर्णांक32_t	len;
	पूर्णांक32_t		error;
	uपूर्णांक64_t	unique;
पूर्ण;

काष्ठा fuse_dirent अणु
	uपूर्णांक64_t	ino;
	uपूर्णांक64_t	off;
	uपूर्णांक32_t	namelen;
	uपूर्णांक32_t	type;
	अक्षर name[];
पूर्ण;

#घोषणा FUSE_NAME_OFFSET दुरत्व(काष्ठा fuse_dirent, name)
#घोषणा FUSE_सूचीENT_ALIGN(x) \
	(((x) + माप(uपूर्णांक64_t) - 1) & ~(माप(uपूर्णांक64_t) - 1))
#घोषणा FUSE_सूचीENT_SIZE(d) \
	FUSE_सूचीENT_ALIGN(FUSE_NAME_OFFSET + (d)->namelen)

काष्ठा fuse_direntplus अणु
	काष्ठा fuse_entry_out entry_out;
	काष्ठा fuse_dirent dirent;
पूर्ण;

#घोषणा FUSE_NAME_OFFSET_सूचीENTPLUS \
	दुरत्व(काष्ठा fuse_direntplus, dirent.name)
#घोषणा FUSE_सूचीENTPLUS_SIZE(d) \
	FUSE_सूचीENT_ALIGN(FUSE_NAME_OFFSET_सूचीENTPLUS + (d)->dirent.namelen)

काष्ठा fuse_notअगरy_inval_inode_out अणु
	uपूर्णांक64_t	ino;
	पूर्णांक64_t		off;
	पूर्णांक64_t		len;
पूर्ण;

काष्ठा fuse_notअगरy_inval_entry_out अणु
	uपूर्णांक64_t	parent;
	uपूर्णांक32_t	namelen;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_notअगरy_delete_out अणु
	uपूर्णांक64_t	parent;
	uपूर्णांक64_t	child;
	uपूर्णांक32_t	namelen;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_notअगरy_store_out अणु
	uपूर्णांक64_t	nodeid;
	uपूर्णांक64_t	offset;
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_notअगरy_retrieve_out अणु
	uपूर्णांक64_t	notअगरy_unique;
	uपूर्णांक64_t	nodeid;
	uपूर्णांक64_t	offset;
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	padding;
पूर्ण;

/* Matches the size of fuse_ग_लिखो_in */
काष्ठा fuse_notअगरy_retrieve_in अणु
	uपूर्णांक64_t	dummy1;
	uपूर्णांक64_t	offset;
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	dummy2;
	uपूर्णांक64_t	dummy3;
	uपूर्णांक64_t	dummy4;
पूर्ण;

/* Device ioctls: */
#घोषणा FUSE_DEV_IOC_MAGIC		229
#घोषणा FUSE_DEV_IOC_CLONE		_IOR(FUSE_DEV_IOC_MAGIC, 0, uपूर्णांक32_t)

काष्ठा fuse_lseek_in अणु
	uपूर्णांक64_t	fh;
	uपूर्णांक64_t	offset;
	uपूर्णांक32_t	whence;
	uपूर्णांक32_t	padding;
पूर्ण;

काष्ठा fuse_lseek_out अणु
	uपूर्णांक64_t	offset;
पूर्ण;

काष्ठा fuse_copy_file_range_in अणु
	uपूर्णांक64_t	fh_in;
	uपूर्णांक64_t	off_in;
	uपूर्णांक64_t	nodeid_out;
	uपूर्णांक64_t	fh_out;
	uपूर्णांक64_t	off_out;
	uपूर्णांक64_t	len;
	uपूर्णांक64_t	flags;
पूर्ण;

#घोषणा FUSE_SETUPMAPPING_FLAG_WRITE (1ull << 0)
#घोषणा FUSE_SETUPMAPPING_FLAG_READ (1ull << 1)
काष्ठा fuse_setupmapping_in अणु
	/* An alपढ़ोy खोलो handle */
	uपूर्णांक64_t	fh;
	/* Offset पूर्णांकo the file to start the mapping */
	uपूर्णांक64_t	foffset;
	/* Length of mapping required */
	uपूर्णांक64_t	len;
	/* Flags, FUSE_SETUPMAPPING_FLAG_* */
	uपूर्णांक64_t	flags;
	/* Offset in Memory Winकरोw */
	uपूर्णांक64_t	moffset;
पूर्ण;

काष्ठा fuse_हटाओmapping_in अणु
	/* number of fuse_हटाओmapping_one follows */
	uपूर्णांक32_t        count;
पूर्ण;

काष्ठा fuse_हटाओmapping_one अणु
	/* Offset पूर्णांकo the dax winकरोw start the unmapping */
	uपूर्णांक64_t        moffset;
	/* Length of mapping required */
	uपूर्णांक64_t	len;
पूर्ण;

#घोषणा FUSE_REMOVEMAPPING_MAX_ENTRY   \
		(PAGE_SIZE / माप(काष्ठा fuse_हटाओmapping_one))

#पूर्ण_अगर /* _LINUX_FUSE_H */
