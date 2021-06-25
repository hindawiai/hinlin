<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This is <linux/capability.h>
 *
 * Andrew G. Morgan <morgan@kernel.org>
 * Alexander Kjeldaas <astor@guardian.no>
 * with help from Aleph1, Roland Buresund and Andrew Main.
 *
 * See here क्रम the libcap library ("POSIX draft" compliance):
 *
 * ftp://www.kernel.org/pub/linux/libs/security/linux-privs/kernel-2.6/
 */

#अगर_अघोषित _UAPI_LINUX_CAPABILITY_H
#घोषणा _UAPI_LINUX_CAPABILITY_H

#समावेश <linux/types.h>

/* User-level करो most of the mapping between kernel and user
   capabilities based on the version tag given by the kernel. The
   kernel might be somewhat backwards compatible, but करोn't bet on
   it. */

/* Note, cap_t, is defined by POSIX (draft) to be an "opaque" poपूर्णांकer to
   a set of three capability sets.  The transposition of 3*the
   following काष्ठाure to such a composite is better handled in a user
   library since the draft standard requires the use of दो_स्मृति/मुक्त
   etc.. */

#घोषणा _LINUX_CAPABILITY_VERSION_1  0x19980330
#घोषणा _LINUX_CAPABILITY_U32S_1     1

#घोषणा _LINUX_CAPABILITY_VERSION_2  0x20071026  /* deprecated - use v3 */
#घोषणा _LINUX_CAPABILITY_U32S_2     2

#घोषणा _LINUX_CAPABILITY_VERSION_3  0x20080522
#घोषणा _LINUX_CAPABILITY_U32S_3     2

प्रकार काष्ठा __user_cap_header_काष्ठा अणु
	__u32 version;
	पूर्णांक pid;
पूर्ण __user *cap_user_header_t;

प्रकार काष्ठा __user_cap_data_काष्ठा अणु
        __u32 effective;
        __u32 permitted;
        __u32 inheritable;
पूर्ण __user *cap_user_data_t;


#घोषणा VFS_CAP_REVISION_MASK	0xFF000000
#घोषणा VFS_CAP_REVISION_SHIFT	24
#घोषणा VFS_CAP_FLAGS_MASK	~VFS_CAP_REVISION_MASK
#घोषणा VFS_CAP_FLAGS_EFFECTIVE	0x000001

#घोषणा VFS_CAP_REVISION_1	0x01000000
#घोषणा VFS_CAP_U32_1           1
#घोषणा XATTR_CAPS_SZ_1         (माप(__le32)*(1 + 2*VFS_CAP_U32_1))

#घोषणा VFS_CAP_REVISION_2	0x02000000
#घोषणा VFS_CAP_U32_2           2
#घोषणा XATTR_CAPS_SZ_2         (माप(__le32)*(1 + 2*VFS_CAP_U32_2))

#घोषणा VFS_CAP_REVISION_3	0x03000000
#घोषणा VFS_CAP_U32_3           2
#घोषणा XATTR_CAPS_SZ_3         (माप(__le32)*(2 + 2*VFS_CAP_U32_3))

#घोषणा XATTR_CAPS_SZ           XATTR_CAPS_SZ_3
#घोषणा VFS_CAP_U32             VFS_CAP_U32_3
#घोषणा VFS_CAP_REVISION	VFS_CAP_REVISION_3

काष्ठा vfs_cap_data अणु
	__le32 magic_etc;            /* Little endian */
	काष्ठा अणु
		__le32 permitted;    /* Little endian */
		__le32 inheritable;  /* Little endian */
	पूर्ण data[VFS_CAP_U32];
पूर्ण;

/*
 * same as vfs_cap_data but with a rootid at the end
 */
काष्ठा vfs_ns_cap_data अणु
	__le32 magic_etc;
	काष्ठा अणु
		__le32 permitted;    /* Little endian */
		__le32 inheritable;  /* Little endian */
	पूर्ण data[VFS_CAP_U32];
	__le32 rootid;
पूर्ण;

#अगर_अघोषित __KERNEL__

/*
 * Backwardly compatible definition क्रम source code - trapped in a
 * 32-bit world. If you find you need this, please consider using
 * libcap to untrap yourself...
 */
#घोषणा _LINUX_CAPABILITY_VERSION  _LINUX_CAPABILITY_VERSION_1
#घोषणा _LINUX_CAPABILITY_U32S     _LINUX_CAPABILITY_U32S_1

#पूर्ण_अगर


/**
 ** POSIX-draft defined capabilities.
 **/

/* In a प्रणाली with the [_POSIX_CHOWN_RESTRICTED] option defined, this
   overrides the restriction of changing file ownership and group
   ownership. */

#घोषणा CAP_CHOWN            0

/* Override all DAC access, including ACL execute access अगर
   [_POSIX_ACL] is defined. Excluding DAC access covered by
   CAP_LINUX_IMMUTABLE. */

#घोषणा CAP_DAC_OVERRIDE     1

/* Overrides all DAC restrictions regarding पढ़ो and search on files
   and directories, including ACL restrictions अगर [_POSIX_ACL] is
   defined. Excluding DAC access covered by CAP_LINUX_IMMUTABLE. */

#घोषणा CAP_DAC_READ_SEARCH  2

/* Overrides all restrictions about allowed operations on files, where
   file owner ID must be equal to the user ID, except where CAP_FSETID
   is applicable. It करोesn't override MAC and DAC restrictions. */

#घोषणा CAP_FOWNER           3

/* Overrides the following restrictions that the effective user ID
   shall match the file owner ID when setting the S_ISUID and S_ISGID
   bits on that file; that the effective group ID (or one of the
   supplementary group IDs) shall match the file owner ID when setting
   the S_ISGID bit on that file; that the S_ISUID and S_ISGID bits are
   cleared on successful वापस from chown(2) (not implemented). */

#घोषणा CAP_FSETID           4

/* Overrides the restriction that the real or effective user ID of a
   process sending a संकेत must match the real or effective user ID
   of the process receiving the संकेत. */

#घोषणा CAP_KILL             5

/* Allows setgid(2) manipulation */
/* Allows setgroups(2) */
/* Allows क्रमged gids on socket credentials passing. */

#घोषणा CAP_SETGID           6

/* Allows set*uid(2) manipulation (including fsuid). */
/* Allows क्रमged pids on socket credentials passing. */

#घोषणा CAP_SETUID           7


/**
 ** Linux-specअगरic capabilities
 **/

/* Without VFS support क्रम capabilities:
 *   Transfer any capability in your permitted set to any pid,
 *   हटाओ any capability in your permitted set from any pid
 * With VFS support क्रम capabilities (neither of above, but)
 *   Add any capability from current's capability bounding set
 *       to the current process' inheritable set
 *   Allow taking bits out of capability bounding set
 *   Allow modअगरication of the securebits क्रम a process
 */

#घोषणा CAP_SETPCAP          8

/* Allow modअगरication of S_IMMUTABLE and S_APPEND file attributes */

#घोषणा CAP_LINUX_IMMUTABLE  9

/* Allows binding to TCP/UDP sockets below 1024 */
/* Allows binding to ATM VCIs below 32 */

#घोषणा CAP_NET_BIND_SERVICE 10

/* Allow broadcasting, listen to multicast */

#घोषणा CAP_NET_BROADCAST    11

/* Allow पूर्णांकerface configuration */
/* Allow administration of IP firewall, masquerading and accounting */
/* Allow setting debug option on sockets */
/* Allow modअगरication of routing tables */
/* Allow setting arbitrary process / process group ownership on
   sockets */
/* Allow binding to any address क्रम transparent proxying (also via NET_RAW) */
/* Allow setting TOS (type of service) */
/* Allow setting promiscuous mode */
/* Allow clearing driver statistics */
/* Allow multicasting */
/* Allow पढ़ो/ग_लिखो of device-specअगरic रेजिस्टरs */
/* Allow activation of ATM control sockets */

#घोषणा CAP_NET_ADMIN        12

/* Allow use of RAW sockets */
/* Allow use of PACKET sockets */
/* Allow binding to any address क्रम transparent proxying (also via NET_ADMIN) */

#घोषणा CAP_NET_RAW          13

/* Allow locking of shared memory segments */
/* Allow mlock and mlockall (which करोesn't really have anything to करो
   with IPC) */

#घोषणा CAP_IPC_LOCK         14

/* Override IPC ownership checks */

#घोषणा CAP_IPC_OWNER        15

/* Insert and हटाओ kernel modules - modअगरy kernel without limit */
#घोषणा CAP_SYS_MODULE       16

/* Allow ioperm/iopl access */
/* Allow sending USB messages to any device via /dev/bus/usb */

#घोषणा CAP_SYS_RAWIO        17

/* Allow use of chroot() */

#घोषणा CAP_SYS_CHROOT       18

/* Allow ptrace() of any process */

#घोषणा CAP_SYS_PTRACE       19

/* Allow configuration of process accounting */

#घोषणा CAP_SYS_PACCT        20

/* Allow configuration of the secure attention key */
/* Allow administration of the अक्रमom device */
/* Allow examination and configuration of disk quotas */
/* Allow setting the करोमुख्यname */
/* Allow setting the hostname */
/* Allow calling bdflush() */
/* Allow mount() and umount(), setting up new smb connection */
/* Allow some स्वतःfs root ioctls */
/* Allow nfsservctl */
/* Allow VM86_REQUEST_IRQ */
/* Allow to पढ़ो/ग_लिखो pci config on alpha */
/* Allow irix_prctl on mips (setstacksize) */
/* Allow flushing all cache on m68k (sys_cacheflush) */
/* Allow removing semaphores */
/* Used instead of CAP_CHOWN to "chown" IPC message queues, semaphores
   and shared memory */
/* Allow locking/unlocking of shared memory segment */
/* Allow turning swap on/off */
/* Allow क्रमged pids on socket credentials passing */
/* Allow setting पढ़ोahead and flushing buffers on block devices */
/* Allow setting geometry in floppy driver */
/* Allow turning DMA on/off in xd driver */
/* Allow administration of md devices (mostly the above, but some
   extra ioctls) */
/* Allow tuning the ide driver */
/* Allow access to the nvram device */
/* Allow administration of apm_bios, serial and bttv (TV) device */
/* Allow manufacturer commands in isdn CAPI support driver */
/* Allow पढ़ोing non-standardized portions of pci configuration space */
/* Allow DDI debug ioctl on sbpcd driver */
/* Allow setting up serial ports */
/* Allow sending raw qic-117 commands */
/* Allow enabling/disabling tagged queuing on SCSI controllers and sending
   arbitrary SCSI commands */
/* Allow setting encryption key on loopback fileप्रणाली */
/* Allow setting zone reclaim policy */
/* Allow everything under CAP_BPF and CAP_PERFMON क्रम backward compatibility */

#घोषणा CAP_SYS_ADMIN        21

/* Allow use of reboot() */

#घोषणा CAP_SYS_BOOT         22

/* Allow raising priority and setting priority on other (dअगरferent
   UID) processes */
/* Allow use of FIFO and round-robin (realसमय) scheduling on own
   processes and setting the scheduling algorithm used by another
   process. */
/* Allow setting cpu affinity on other processes */
/* Allow setting realसमय ioprio class */
/* Allow setting ioprio class on other processes */

#घोषणा CAP_SYS_NICE         23

/* Override resource limits. Set resource limits. */
/* Override quota limits. */
/* Override reserved space on ext2 fileप्रणाली */
/* Modअगरy data journaling mode on ext3 fileप्रणाली (uses journaling
   resources) */
/* NOTE: ext2 honors fsuid when checking क्रम resource overrides, so
   you can override using fsuid too */
/* Override size restrictions on IPC message queues */
/* Allow more than 64hz पूर्णांकerrupts from the real-समय घड़ी */
/* Override max number of consoles on console allocation */
/* Override max number of keymaps */
/* Control memory reclaim behavior */

#घोषणा CAP_SYS_RESOURCE     24

/* Allow manipulation of प्रणाली घड़ी */
/* Allow irix_sसमय on mips */
/* Allow setting the real-समय घड़ी */

#घोषणा CAP_SYS_TIME         25

/* Allow configuration of tty devices */
/* Allow vhangup() of tty */

#घोषणा CAP_SYS_TTY_CONFIG   26

/* Allow the privileged aspects of mknod() */

#घोषणा CAP_MKNOD            27

/* Allow taking of leases on files */

#घोषणा CAP_LEASE            28

/* Allow writing the audit log via unicast netlink socket */

#घोषणा CAP_AUDIT_WRITE      29

/* Allow configuration of audit via unicast netlink socket */

#घोषणा CAP_AUDIT_CONTROL    30

/* Set or हटाओ capabilities on files.
   Map uid=0 पूर्णांकo a child user namespace. */

#घोषणा CAP_SETFCAP	     31

/* Override MAC access.
   The base kernel enक्रमces no MAC policy.
   An LSM may enक्रमce a MAC policy, and अगर it करोes and it chooses
   to implement capability based overrides of that policy, this is
   the capability it should use to करो so. */

#घोषणा CAP_MAC_OVERRIDE     32

/* Allow MAC configuration or state changes.
   The base kernel requires no MAC configuration.
   An LSM may enक्रमce a MAC policy, and अगर it करोes and it chooses
   to implement capability based checks on modअगरications to that
   policy or the data required to मुख्यtain it, this is the
   capability it should use to करो so. */

#घोषणा CAP_MAC_ADMIN        33

/* Allow configuring the kernel's syslog (prपूर्णांकk behaviour) */

#घोषणा CAP_SYSLOG           34

/* Allow triggering something that will wake the प्रणाली */

#घोषणा CAP_WAKE_ALARM            35

/* Allow preventing प्रणाली suspends */

#घोषणा CAP_BLOCK_SUSPEND    36

/* Allow पढ़ोing the audit log via multicast netlink socket */

#घोषणा CAP_AUDIT_READ		37

/*
 * Allow प्रणाली perक्रमmance and observability privileged operations
 * using perf_events, i915_perf and other kernel subप्रणालीs
 */

#घोषणा CAP_PERFMON		38

/*
 * CAP_BPF allows the following BPF operations:
 * - Creating all types of BPF maps
 * - Advanced verअगरier features
 *   - Indirect variable access
 *   - Bounded loops
 *   - BPF to BPF function calls
 *   - Scalar precision tracking
 *   - Larger complनिकासy limits
 *   - Dead code elimination
 *   - And potentially other features
 * - Loading BPF Type Format (BTF) data
 * - Retrieve xlated and JITed code of BPF programs
 * - Use bpf_spin_lock() helper
 *
 * CAP_PERFMON relaxes the verअगरier checks further:
 * - BPF progs can use of poपूर्णांकer-to-पूर्णांकeger conversions
 * - speculation attack hardening measures are bypassed
 * - bpf_probe_पढ़ो to पढ़ो arbitrary kernel memory is allowed
 * - bpf_trace_prपूर्णांकk to prपूर्णांक kernel memory is allowed
 *
 * CAP_SYS_ADMIN is required to use bpf_probe_ग_लिखो_user.
 *
 * CAP_SYS_ADMIN is required to iterate प्रणाली wide loaded
 * programs, maps, links, BTFs and convert their IDs to file descriptors.
 *
 * CAP_PERFMON and CAP_BPF are required to load tracing programs.
 * CAP_NET_ADMIN and CAP_BPF are required to load networking programs.
 */
#घोषणा CAP_BPF			39


/* Allow checkpoपूर्णांक/restore related operations */
/* Allow PID selection during clone3() */
/* Allow writing to ns_last_pid */

#घोषणा CAP_CHECKPOINT_RESTORE	40

#घोषणा CAP_LAST_CAP         CAP_CHECKPOINT_RESTORE

#घोषणा cap_valid(x) ((x) >= 0 && (x) <= CAP_LAST_CAP)

/*
 * Bit location of each capability (used by user-space library and kernel)
 */

#घोषणा CAP_TO_INDEX(x)     ((x) >> 5)        /* 1 << 5 == bits in __u32 */
#घोषणा CAP_TO_MASK(x)      (1 << ((x) & 31)) /* mask क्रम indexed __u32 */


#पूर्ण_अगर /* _UAPI_LINUX_CAPABILITY_H */
