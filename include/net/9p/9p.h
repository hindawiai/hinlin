<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/net/9p/9p.h
 *
 * 9P protocol definitions.
 *
 *  Copyright (C) 2005 by Latchesar Ionkov <lucho@ionkov.net>
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#अगर_अघोषित NET_9P_H
#घोषणा NET_9P_H

/**
 * क्रमागत p9_debug_flags - bits क्रम mount समय debug parameter
 * @P9_DEBUG_ERROR: more verbose error messages including original error string
 * @P9_DEBUG_9P: 9P protocol tracing
 * @P9_DEBUG_VFS: VFS API tracing
 * @P9_DEBUG_CONV: protocol conversion tracing
 * @P9_DEBUG_MUX: trace management of concurrent transactions
 * @P9_DEBUG_TRANS: transport tracing
 * @P9_DEBUG_SLABS: memory management tracing
 * @P9_DEBUG_FCALL: verbose dump of protocol messages
 * @P9_DEBUG_FID: fid allocation/deallocation tracking
 * @P9_DEBUG_PKT: packet marshalling/unmarshalling
 * @P9_DEBUG_FSC: FS-cache tracing
 * @P9_DEBUG_VPKT: Verbose packet debugging (full packet dump)
 *
 * These flags are passed at mount समय to turn on various levels of
 * verbosity and tracing which will be output to the प्रणाली logs.
 */

क्रमागत p9_debug_flags अणु
	P9_DEBUG_ERROR = 	(1<<0),
	P9_DEBUG_9P = 		(1<<2),
	P9_DEBUG_VFS =		(1<<3),
	P9_DEBUG_CONV =		(1<<4),
	P9_DEBUG_MUX =		(1<<5),
	P9_DEBUG_TRANS =	(1<<6),
	P9_DEBUG_SLABS =      	(1<<7),
	P9_DEBUG_FCALL =	(1<<8),
	P9_DEBUG_FID =		(1<<9),
	P9_DEBUG_PKT =		(1<<10),
	P9_DEBUG_FSC =		(1<<11),
	P9_DEBUG_VPKT =		(1<<12),
पूर्ण;

#अगर_घोषित CONFIG_NET_9P_DEBUG
बाह्य अचिन्हित पूर्णांक p9_debug_level;
__म_लिखो(3, 4)
व्योम _p9_debug(क्रमागत p9_debug_flags level, स्थिर अक्षर *func,
	       स्थिर अक्षर *fmt, ...);
#घोषणा p9_debug(level, fmt, ...)			\
	_p9_debug(level, __func__, fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा p9_debug(level, fmt, ...)			\
	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

/**
 * क्रमागत p9_msg_t - 9P message types
 * @P9_TLERROR: not used
 * @P9_RLERROR: response क्रम any failed request क्रम 9P2000.L
 * @P9_TSTATFS: file प्रणाली status request
 * @P9_RSTATFS: file प्रणाली status response
 * @P9_TSYMLINK: make symlink request
 * @P9_RSYMLINK: make symlink response
 * @P9_TMKNOD: create a special file object request
 * @P9_RMKNOD: create a special file object response
 * @P9_TLCREATE: prepare a handle क्रम I/O on an new file क्रम 9P2000.L
 * @P9_RLCREATE: response with file access inक्रमmation क्रम 9P2000.L
 * @P9_TRENAME: नाम request
 * @P9_RRENAME: नाम response
 * @P9_TMKसूची: create a directory request
 * @P9_RMKसूची: create a directory response
 * @P9_TVERSION: version handshake request
 * @P9_RVERSION: version handshake response
 * @P9_TAUTH: request to establish authentication channel
 * @P9_RAUTH: response with authentication inक्रमmation
 * @P9_TATTACH: establish user access to file service
 * @P9_RATTACH: response with top level handle to file hierarchy
 * @P9_TERROR: not used
 * @P9_RERROR: response क्रम any failed request
 * @P9_TFLUSH: request to पात a previous request
 * @P9_RFLUSH: response when previous request has been cancelled
 * @P9_TWALK: descend a directory hierarchy
 * @P9_RWALK: response with new handle क्रम position within hierarchy
 * @P9_TOPEN: prepare a handle क्रम I/O on an existing file
 * @P9_ROPEN: response with file access inक्रमmation
 * @P9_TCREATE: prepare a handle क्रम I/O on a new file
 * @P9_RCREATE: response with file access inक्रमmation
 * @P9_TREAD: request to transfer data from a file or directory
 * @P9_RREAD: response with data requested
 * @P9_TWRITE: reuqest to transfer data to a file
 * @P9_RWRITE: response with out much data was transferred to file
 * @P9_TCLUNK: क्रमget about a handle to an entity within the file प्रणाली
 * @P9_RCLUNK: response when server has क्रमgotten about the handle
 * @P9_TREMOVE: request to हटाओ an entity from the hierarchy
 * @P9_RREMOVE: response when server has हटाओd the entity
 * @P9_TSTAT: request file entity attributes
 * @P9_RSTAT: response with file entity attributes
 * @P9_TWSTAT: request to update file entity attributes
 * @P9_RWSTAT: response when file entity attributes are updated
 *
 * There are 14 basic operations in 9P2000, paired as
 * requests and responses.  The one special हाल is ERROR
 * as there is no @P9_TERROR request क्रम clients to transmit to
 * the server, but the server may respond to any other request
 * with an @P9_RERROR.
 *
 * See Also: http://plan9.bell-द_असल.com/sys/man/5/INDEX.hपंचांगl
 */

क्रमागत p9_msg_t अणु
	P9_TLERROR = 6,
	P9_RLERROR,
	P9_TSTATFS = 8,
	P9_RSTATFS,
	P9_TLOPEN = 12,
	P9_RLOPEN,
	P9_TLCREATE = 14,
	P9_RLCREATE,
	P9_TSYMLINK = 16,
	P9_RSYMLINK,
	P9_TMKNOD = 18,
	P9_RMKNOD,
	P9_TRENAME = 20,
	P9_RRENAME,
	P9_TREADLINK = 22,
	P9_RREADLINK,
	P9_TGETATTR = 24,
	P9_RGETATTR,
	P9_TSETATTR = 26,
	P9_RSETATTR,
	P9_TXATTRWALK = 30,
	P9_RXATTRWALK,
	P9_TXATTRCREATE = 32,
	P9_RXATTRCREATE,
	P9_TREADसूची = 40,
	P9_RREADसूची,
	P9_TFSYNC = 50,
	P9_RFSYNC,
	P9_TLOCK = 52,
	P9_RLOCK,
	P9_TGETLOCK = 54,
	P9_RGETLOCK,
	P9_TLINK = 70,
	P9_RLINK,
	P9_TMKसूची = 72,
	P9_RMKसूची,
	P9_TRENAMEAT = 74,
	P9_RRENAMEAT,
	P9_TUNLINKAT = 76,
	P9_RUNLINKAT,
	P9_TVERSION = 100,
	P9_RVERSION,
	P9_TAUTH = 102,
	P9_RAUTH,
	P9_TATTACH = 104,
	P9_RATTACH,
	P9_TERROR = 106,
	P9_RERROR,
	P9_TFLUSH = 108,
	P9_RFLUSH,
	P9_TWALK = 110,
	P9_RWALK,
	P9_TOPEN = 112,
	P9_ROPEN,
	P9_TCREATE = 114,
	P9_RCREATE,
	P9_TREAD = 116,
	P9_RREAD,
	P9_TWRITE = 118,
	P9_RWRITE,
	P9_TCLUNK = 120,
	P9_RCLUNK,
	P9_TREMOVE = 122,
	P9_RREMOVE,
	P9_TSTAT = 124,
	P9_RSTAT,
	P9_TWSTAT = 126,
	P9_RWSTAT,
पूर्ण;

/**
 * क्रमागत p9_खोलो_mode_t - 9P खोलो modes
 * @P9_OREAD: खोलो file क्रम पढ़ोing only
 * @P9_OWRITE: खोलो file क्रम writing only
 * @P9_ORDWR: खोलो file क्रम पढ़ोing or writing
 * @P9_OEXEC: खोलो file क्रम execution
 * @P9_OTRUNC: truncate file to zero-length beक्रमe खोलोing it
 * @P9_OREXEC: बंद the file when an exec(2) प्रणाली call is made
 * @P9_ORCLOSE: हटाओ the file when the file is बंदd
 * @P9_OAPPEND: खोलो the file and seek to the end
 * @P9_OEXCL: only create a file, करो not खोलो it
 *
 * 9P खोलो modes dअगरfer slightly from Posix standard modes.
 * In particular, there are extra modes which specअगरy dअगरferent
 * semantic behaviors than may be available on standard Posix
 * प्रणालीs.  For example, @P9_OREXEC and @P9_ORCLOSE are modes that
 * most likely will not be issued from the Linux VFS client, but may
 * be supported by servers.
 *
 * See Also: http://plan9.bell-द_असल.com/magic/man2hपंचांगl/2/खोलो
 */

क्रमागत p9_खोलो_mode_t अणु
	P9_OREAD = 0x00,
	P9_OWRITE = 0x01,
	P9_ORDWR = 0x02,
	P9_OEXEC = 0x03,
	P9_OTRUNC = 0x10,
	P9_OREXEC = 0x20,
	P9_ORCLOSE = 0x40,
	P9_OAPPEND = 0x80,
	P9_OEXCL = 0x1000,
पूर्ण;

/**
 * क्रमागत p9_perm_t - 9P permissions
 * @P9_DMसूची: mode bit क्रम directories
 * @P9_DMAPPEND: mode bit क्रम is append-only
 * @P9_DMEXCL: mode bit क्रम excluse use (only one खोलो handle allowed)
 * @P9_DMMOUNT: mode bit क्रम mount poपूर्णांकs
 * @P9_DMAUTH: mode bit क्रम authentication file
 * @P9_DMTMP: mode bit क्रम non-backed-up files
 * @P9_DMSYMLINK: mode bit क्रम symbolic links (9P2000.u)
 * @P9_DMLINK: mode bit क्रम hard-link (9P2000.u)
 * @P9_DMDEVICE: mode bit क्रम device files (9P2000.u)
 * @P9_DMNAMEDPIPE: mode bit क्रम named pipe (9P2000.u)
 * @P9_DMSOCKET: mode bit क्रम socket (9P2000.u)
 * @P9_DMSETUID: mode bit क्रम setuid (9P2000.u)
 * @P9_DMSETGID: mode bit क्रम setgid (9P2000.u)
 * @P9_DMSETVTX: mode bit क्रम sticky bit (9P2000.u)
 *
 * 9P permissions dअगरfer slightly from Posix standard modes.
 *
 * See Also: http://plan9.bell-द_असल.com/magic/man2hपंचांगl/2/stat
 */
क्रमागत p9_perm_t अणु
	P9_DMसूची = 0x80000000,
	P9_DMAPPEND = 0x40000000,
	P9_DMEXCL = 0x20000000,
	P9_DMMOUNT = 0x10000000,
	P9_DMAUTH = 0x08000000,
	P9_DMTMP = 0x04000000,
/* 9P2000.u extensions */
	P9_DMSYMLINK = 0x02000000,
	P9_DMLINK = 0x01000000,
	P9_DMDEVICE = 0x00800000,
	P9_DMNAMEDPIPE = 0x00200000,
	P9_DMSOCKET = 0x00100000,
	P9_DMSETUID = 0x00080000,
	P9_DMSETGID = 0x00040000,
	P9_DMSETVTX = 0x00010000,
पूर्ण;

/* 9p2000.L खोलो flags */
#घोषणा P9_DOTL_RDONLY        00000000
#घोषणा P9_DOTL_WRONLY        00000001
#घोषणा P9_DOTL_RDWR          00000002
#घोषणा P9_DOTL_NOACCESS      00000003
#घोषणा P9_DOTL_CREATE        00000100
#घोषणा P9_DOTL_EXCL          00000200
#घोषणा P9_DOTL_NOCTTY        00000400
#घोषणा P9_DOTL_TRUNC         00001000
#घोषणा P9_DOTL_APPEND        00002000
#घोषणा P9_DOTL_NONBLOCK      00004000
#घोषणा P9_DOTL_DSYNC         00010000
#घोषणा P9_DOTL_FASYNC        00020000
#घोषणा P9_DOTL_सूचीECT        00040000
#घोषणा P9_DOTL_LARGEखाता     00100000
#घोषणा P9_DOTL_सूचीECTORY     00200000
#घोषणा P9_DOTL_NOFOLLOW      00400000
#घोषणा P9_DOTL_NOATIME       01000000
#घोषणा P9_DOTL_CLOEXEC       02000000
#घोषणा P9_DOTL_SYNC          04000000

/* 9p2000.L at flags */
#घोषणा P9_DOTL_AT_REMOVEसूची		0x200

/* 9p2000.L lock type */
#घोषणा P9_LOCK_TYPE_RDLCK 0
#घोषणा P9_LOCK_TYPE_WRLCK 1
#घोषणा P9_LOCK_TYPE_UNLCK 2

/**
 * क्रमागत p9_qid_t - QID types
 * @P9_QTसूची: directory
 * @P9_QTAPPEND: append-only
 * @P9_QTEXCL: excluse use (only one खोलो handle allowed)
 * @P9_QTMOUNT: mount poपूर्णांकs
 * @P9_QTAUTH: authentication file
 * @P9_QTTMP: non-backed-up files
 * @P9_QTSYMLINK: symbolic links (9P2000.u)
 * @P9_QTLINK: hard-link (9P2000.u)
 * @P9_QTखाता: normal files
 *
 * QID types are a subset of permissions - they are primarily
 * used to dअगरferentiate semantics क्रम a file प्रणाली entity via
 * a jump-table.  Their value is also the most signअगरicant 16 bits
 * of the permission_t
 *
 * See Also: http://plan9.bell-द_असल.com/magic/man2hपंचांगl/2/stat
 */
क्रमागत p9_qid_t अणु
	P9_QTसूची = 0x80,
	P9_QTAPPEND = 0x40,
	P9_QTEXCL = 0x20,
	P9_QTMOUNT = 0x10,
	P9_QTAUTH = 0x08,
	P9_QTTMP = 0x04,
	P9_QTSYMLINK = 0x02,
	P9_QTLINK = 0x01,
	P9_QTखाता = 0x00,
पूर्ण;

/* 9P Magic Numbers */
#घोषणा P9_NOTAG	(u16)(~0)
#घोषणा P9_NOFID	(u32)(~0)
#घोषणा P9_MAXWELEM	16

/* Minimal header size: size[4] type[1] tag[2] */
#घोषणा P9_HDRSZ	7

/* ample room क्रम Tग_लिखो/Rपढ़ो header */
#घोषणा P9_IOHDRSZ	24

/* Room क्रम सूची_पढ़ो header */
#घोषणा P9_READसूचीHDRSZ	24

/* size of header क्रम zero copy पढ़ो/ग_लिखो */
#घोषणा P9_ZC_HDR_SZ 4096

/**
 * काष्ठा p9_qid - file प्रणाली entity inक्रमmation
 * @type: 8-bit type &p9_qid_t
 * @version: 16-bit monotonically incrementing version number
 * @path: 64-bit per-server-unique ID क्रम a file प्रणाली element
 *
 * qids are identअगरiers used by 9P servers to track file प्रणाली
 * entities.  The type is used to dअगरferentiate semantics क्रम operations
 * on the entity (ie. पढ़ो means something dअगरferent on a directory than
 * on a file).  The path provides a server unique index क्रम an entity
 * (roughly analogous to an inode number), जबतक the version is updated
 * every समय a file is modअगरied and can be used to मुख्यtain cache
 * coherency between clients and serves.
 * Servers will often dअगरferentiate purely synthetic entities by setting
 * their version to 0, संकेतing that they should never be cached and
 * should be accessed synchronously.
 *
 * See Also://plan9.bell-द_असल.com/magic/man2hपंचांगl/2/stat
 */

काष्ठा p9_qid अणु
	u8 type;
	u32 version;
	u64 path;
पूर्ण;

/**
 * काष्ठा p9_wstat - file प्रणाली metadata inक्रमmation
 * @size: length prefix क्रम this stat काष्ठाure instance
 * @type: the type of the server (equivalent to a major number)
 * @dev: the sub-type of the server (equivalent to a minor number)
 * @qid: unique id from the server of type &p9_qid
 * @mode: Plan 9 क्रमmat permissions of type &p9_perm_t
 * @aसमय: Last access/पढ़ो समय
 * @mसमय: Last modअगरy/ग_लिखो समय
 * @length: file length
 * @name: last element of path (aka filename)
 * @uid: owner name
 * @gid: group owner
 * @muid: last modअगरier
 * @extension: area used to encode extended UNIX support
 * @n_uid: numeric user id of owner (part of 9p2000.u extension)
 * @n_gid: numeric group id (part of 9p2000.u extension)
 * @n_muid: numeric user id of laster modअगरier (part of 9p2000.u extension)
 *
 * See Also: http://plan9.bell-द_असल.com/magic/man2hपंचांगl/2/stat
 */

काष्ठा p9_wstat अणु
	u16 size;
	u16 type;
	u32 dev;
	काष्ठा p9_qid qid;
	u32 mode;
	u32 aसमय;
	u32 mसमय;
	u64 length;
	स्थिर अक्षर *name;
	स्थिर अक्षर *uid;
	स्थिर अक्षर *gid;
	स्थिर अक्षर *muid;
	अक्षर *extension;	/* 9p2000.u extensions */
	kuid_t n_uid;		/* 9p2000.u extensions */
	kgid_t n_gid;		/* 9p2000.u extensions */
	kuid_t n_muid;		/* 9p2000.u extensions */
पूर्ण;

काष्ठा p9_stat_करोtl अणु
	u64 st_result_mask;
	काष्ठा p9_qid qid;
	u32 st_mode;
	kuid_t st_uid;
	kgid_t st_gid;
	u64 st_nlink;
	u64 st_rdev;
	u64 st_size;
	u64 st_blksize;
	u64 st_blocks;
	u64 st_aसमय_sec;
	u64 st_aसमय_nsec;
	u64 st_mसमय_sec;
	u64 st_mसमय_nsec;
	u64 st_स_समय_sec;
	u64 st_स_समय_nsec;
	u64 st_bसमय_sec;
	u64 st_bसमय_nsec;
	u64 st_gen;
	u64 st_data_version;
पूर्ण;

#घोषणा P9_STATS_MODE		0x00000001ULL
#घोषणा P9_STATS_NLINK		0x00000002ULL
#घोषणा P9_STATS_UID		0x00000004ULL
#घोषणा P9_STATS_GID		0x00000008ULL
#घोषणा P9_STATS_RDEV		0x00000010ULL
#घोषणा P9_STATS_ATIME		0x00000020ULL
#घोषणा P9_STATS_MTIME		0x00000040ULL
#घोषणा P9_STATS_CTIME		0x00000080ULL
#घोषणा P9_STATS_INO		0x00000100ULL
#घोषणा P9_STATS_SIZE		0x00000200ULL
#घोषणा P9_STATS_BLOCKS		0x00000400ULL

#घोषणा P9_STATS_BTIME		0x00000800ULL
#घोषणा P9_STATS_GEN		0x00001000ULL
#घोषणा P9_STATS_DATA_VERSION	0x00002000ULL

#घोषणा P9_STATS_BASIC		0x000007ffULL /* Mask क्रम fields up to BLOCKS */
#घोषणा P9_STATS_ALL		0x00003fffULL /* Mask क्रम All fields above */

/**
 * काष्ठा p9_iattr_करोtl - P9 inode attribute क्रम setattr
 * @valid: bitfield specअगरying which fields are valid
 *         same as in काष्ठा iattr
 * @mode: File permission bits
 * @uid: user id of owner
 * @gid: group id
 * @size: File size
 * @aसमय_sec: Last access समय, seconds
 * @aसमय_nsec: Last access समय, nanoseconds
 * @mसमय_sec: Last modअगरication समय, seconds
 * @mसमय_nsec: Last modअगरication समय, nanoseconds
 */

काष्ठा p9_iattr_करोtl अणु
	u32 valid;
	u32 mode;
	kuid_t uid;
	kgid_t gid;
	u64 size;
	u64 aसमय_sec;
	u64 aसमय_nsec;
	u64 mसमय_sec;
	u64 mसमय_nsec;
पूर्ण;

#घोषणा P9_LOCK_SUCCESS 0
#घोषणा P9_LOCK_BLOCKED 1
#घोषणा P9_LOCK_ERROR 2
#घोषणा P9_LOCK_GRACE 3

#घोषणा P9_LOCK_FLAGS_BLOCK 1
#घोषणा P9_LOCK_FLAGS_RECLAIM 2

/* काष्ठा p9_flock: POSIX lock काष्ठाure
 * @type - type of lock
 * @flags - lock flags
 * @start - starting offset of the lock
 * @length - number of bytes
 * @proc_id - process id which wants to take lock
 * @client_id - client id
 */

काष्ठा p9_flock अणु
	u8 type;
	u32 flags;
	u64 start;
	u64 length;
	u32 proc_id;
	अक्षर *client_id;
पूर्ण;

/* काष्ठा p9_getlock: getlock काष्ठाure
 * @type - type of lock
 * @start - starting offset of the lock
 * @length - number of bytes
 * @proc_id - process id which wants to take lock
 * @client_id - client id
 */

काष्ठा p9_getlock अणु
	u8 type;
	u64 start;
	u64 length;
	u32 proc_id;
	अक्षर *client_id;
पूर्ण;

काष्ठा p9_rstatfs अणु
	u32 type;
	u32 bsize;
	u64 blocks;
	u64 bमुक्त;
	u64 bavail;
	u64 files;
	u64 fमुक्त;
	u64 fsid;
	u32 namelen;
पूर्ण;

/**
 * काष्ठा p9_fcall - primary packet काष्ठाure
 * @size: prefixed length of the काष्ठाure
 * @id: protocol operating identअगरier of type &p9_msg_t
 * @tag: transaction id of the request
 * @offset: used by marshalling routines to track current position in buffer
 * @capacity: used by marshalling routines to track total दो_स्मृति'd capacity
 * @sdata: payload
 *
 * &p9_fcall represents the काष्ठाure क्रम all 9P RPC
 * transactions.  Requests are packaged पूर्णांकo fcalls, and reponses
 * must be extracted from them.
 *
 * See Also: http://plan9.bell-द_असल.com/magic/man2hपंचांगl/2/fcall
 */

काष्ठा p9_fcall अणु
	u32 size;
	u8 id;
	u16 tag;

	माप_प्रकार offset;
	माप_प्रकार capacity;

	काष्ठा kmem_cache *cache;
	u8 *sdata;
पूर्ण;

पूर्णांक p9_errstr2त्रुटि_सं(अक्षर *errstr, पूर्णांक len);

पूर्णांक p9_error_init(व्योम);
पूर्णांक p9_trans_fd_init(व्योम);
व्योम p9_trans_fd_निकास(व्योम);
#पूर्ण_अगर /* NET_9P_H */
