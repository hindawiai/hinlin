<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* audit.h -- Auditing support
 *
 * Copyright 2003-2004 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Written by Rickard E. (Rik) Faith <faith@redhat.com>
 *
 */

#अगर_अघोषित _UAPI_LINUX_AUDIT_H_
#घोषणा _UAPI_LINUX_AUDIT_H_

#समावेश <linux/types.h>
#समावेश <linux/elf-em.h>

/* The netlink messages क्रम the audit प्रणाली is भागided पूर्णांकo blocks:
 * 1000 - 1099 are क्रम commanding the audit प्रणाली
 * 1100 - 1199 user space trusted application messages
 * 1200 - 1299 messages पूर्णांकernal to the audit daemon
 * 1300 - 1399 audit event messages
 * 1400 - 1499 SE Linux use
 * 1500 - 1599 kernel LSPP events
 * 1600 - 1699 kernel crypto events
 * 1700 - 1799 kernel anomaly records
 * 1800 - 1899 kernel पूर्णांकegrity events
 * 1900 - 1999 future kernel use
 * 2000 is क्रम otherwise unclassअगरied kernel audit messages (legacy)
 * 2001 - 2099 unused (kernel)
 * 2100 - 2199 user space anomaly records
 * 2200 - 2299 user space actions taken in response to anomalies
 * 2300 - 2399 user space generated LSPP events
 * 2400 - 2499 user space crypto events
 * 2500 - 2999 future user space (maybe पूर्णांकegrity labels and related events)
 *
 * Messages from 1000-1199 are bi-directional. 1200-1299 & 2100 - 2999 are
 * exclusively user space. 1300-2099 is kernel --> user space 
 * communication.
 */
#घोषणा AUDIT_GET		1000	/* Get status */
#घोषणा AUDIT_SET		1001	/* Set status (enable/disable/auditd) */
#घोषणा AUDIT_LIST		1002	/* List syscall rules -- deprecated */
#घोषणा AUDIT_ADD		1003	/* Add syscall rule -- deprecated */
#घोषणा AUDIT_DEL		1004	/* Delete syscall rule -- deprecated */
#घोषणा AUDIT_USER		1005	/* Message from userspace -- deprecated */
#घोषणा AUDIT_LOGIN		1006	/* Define the login id and inक्रमmation */
#घोषणा AUDIT_WATCH_INS		1007	/* Insert file/dir watch entry */
#घोषणा AUDIT_WATCH_REM		1008	/* Remove file/dir watch entry */
#घोषणा AUDIT_WATCH_LIST	1009	/* List all file/dir watches */
#घोषणा AUDIT_SIGNAL_INFO	1010	/* Get info about sender of संकेत to auditd */
#घोषणा AUDIT_ADD_RULE		1011	/* Add syscall filtering rule */
#घोषणा AUDIT_DEL_RULE		1012	/* Delete syscall filtering rule */
#घोषणा AUDIT_LIST_RULES	1013	/* List syscall filtering rules */
#घोषणा AUDIT_TRIM		1014	/* Trim junk from watched tree */
#घोषणा AUDIT_MAKE_EQUIV	1015	/* Append to watched tree */
#घोषणा AUDIT_TTY_GET		1016	/* Get TTY auditing status */
#घोषणा AUDIT_TTY_SET		1017	/* Set TTY auditing status */
#घोषणा AUDIT_SET_FEATURE	1018	/* Turn an audit feature on or off */
#घोषणा AUDIT_GET_FEATURE	1019	/* Get which features are enabled */

#घोषणा AUDIT_FIRST_USER_MSG	1100	/* Userspace messages mostly unपूर्णांकeresting to kernel */
#घोषणा AUDIT_USER_AVC		1107	/* We filter this dअगरferently */
#घोषणा AUDIT_USER_TTY		1124	/* Non-ICANON TTY input meaning */
#घोषणा AUDIT_LAST_USER_MSG	1199
#घोषणा AUDIT_FIRST_USER_MSG2	2100	/* More user space messages */
#घोषणा AUDIT_LAST_USER_MSG2	2999
 
#घोषणा AUDIT_DAEMON_START      1200    /* Daemon startup record */
#घोषणा AUDIT_DAEMON_END        1201    /* Daemon normal stop record */
#घोषणा AUDIT_DAEMON_ABORT      1202    /* Daemon error stop record */
#घोषणा AUDIT_DAEMON_CONFIG     1203    /* Daemon config change */

#घोषणा AUDIT_SYSCALL		1300	/* Syscall event */
/* #घोषणा AUDIT_FS_WATCH	1301	 * Deprecated */
#घोषणा AUDIT_PATH		1302	/* Filename path inक्रमmation */
#घोषणा AUDIT_IPC		1303	/* IPC record */
#घोषणा AUDIT_SOCKETCALL	1304	/* sys_socketcall arguments */
#घोषणा AUDIT_CONFIG_CHANGE	1305	/* Audit प्रणाली configuration change */
#घोषणा AUDIT_SOCKADDR		1306	/* sockaddr copied as syscall arg */
#घोषणा AUDIT_CWD		1307	/* Current working directory */
#घोषणा AUDIT_EXECVE		1309	/* execve arguments */
#घोषणा AUDIT_IPC_SET_PERM	1311	/* IPC new permissions record type */
#घोषणा AUDIT_MQ_OPEN		1312	/* POSIX MQ खोलो record type */
#घोषणा AUDIT_MQ_SENDRECV	1313	/* POSIX MQ send/receive record type */
#घोषणा AUDIT_MQ_NOTIFY		1314	/* POSIX MQ notअगरy record type */
#घोषणा AUDIT_MQ_GETSETATTR	1315	/* POSIX MQ get/set attribute record type */
#घोषणा AUDIT_KERNEL_OTHER	1316	/* For use by 3rd party modules */
#घोषणा AUDIT_FD_PAIR		1317    /* audit record क्रम pipe/socketpair */
#घोषणा AUDIT_OBJ_PID		1318	/* ptrace target */
#घोषणा AUDIT_TTY		1319	/* Input on an administrative TTY */
#घोषणा AUDIT_EOE		1320	/* End of multi-record event */
#घोषणा AUDIT_BPRM_FCAPS	1321	/* Inक्रमmation about fcaps increasing perms */
#घोषणा AUDIT_CAPSET		1322	/* Record showing argument to sys_capset */
#घोषणा AUDIT_MMAP		1323	/* Record showing descriptor and flags in mmap */
#घोषणा AUDIT_NETFILTER_PKT	1324	/* Packets traversing netfilter chains */
#घोषणा AUDIT_NETFILTER_CFG	1325	/* Netfilter chain modअगरications */
#घोषणा AUDIT_SECCOMP		1326	/* Secure Computing event */
#घोषणा AUDIT_PROCTITLE		1327	/* Proctitle emit event */
#घोषणा AUDIT_FEATURE_CHANGE	1328	/* audit log listing feature changes */
#घोषणा AUDIT_REPLACE		1329	/* Replace auditd अगर this packet unanswerd */
#घोषणा AUDIT_KERN_MODULE	1330	/* Kernel Module events */
#घोषणा AUDIT_FANOTIFY		1331	/* Fanotअगरy access decision */
#घोषणा AUDIT_TIME_INJOFFSET	1332	/* Timekeeping offset injected */
#घोषणा AUDIT_TIME_ADJNTPVAL	1333	/* NTP value adjusपंचांगent */
#घोषणा AUDIT_BPF		1334	/* BPF subप्रणाली */
#घोषणा AUDIT_EVENT_LISTENER	1335	/* Task joined multicast पढ़ो socket */

#घोषणा AUDIT_AVC		1400	/* SE Linux avc denial or grant */
#घोषणा AUDIT_SELINUX_ERR	1401	/* Internal SE Linux Errors */
#घोषणा AUDIT_AVC_PATH		1402	/* dentry, vfsmount pair from avc */
#घोषणा AUDIT_MAC_POLICY_LOAD	1403	/* Policy file load */
#घोषणा AUDIT_MAC_STATUS	1404	/* Changed enक्रमcing,permissive,off */
#घोषणा AUDIT_MAC_CONFIG_CHANGE	1405	/* Changes to booleans */
#घोषणा AUDIT_MAC_UNLBL_ALLOW	1406	/* NetLabel: allow unlabeled traffic */
#घोषणा AUDIT_MAC_CIPSOV4_ADD	1407	/* NetLabel: add CIPSOv4 DOI entry */
#घोषणा AUDIT_MAC_CIPSOV4_DEL	1408	/* NetLabel: del CIPSOv4 DOI entry */
#घोषणा AUDIT_MAC_MAP_ADD	1409	/* NetLabel: add LSM करोमुख्य mapping */
#घोषणा AUDIT_MAC_MAP_DEL	1410	/* NetLabel: del LSM करोमुख्य mapping */
#घोषणा AUDIT_MAC_IPSEC_ADDSA	1411	/* Not used */
#घोषणा AUDIT_MAC_IPSEC_DELSA	1412	/* Not used  */
#घोषणा AUDIT_MAC_IPSEC_ADDSPD	1413	/* Not used */
#घोषणा AUDIT_MAC_IPSEC_DELSPD	1414	/* Not used */
#घोषणा AUDIT_MAC_IPSEC_EVENT	1415	/* Audit an IPSec event */
#घोषणा AUDIT_MAC_UNLBL_STCADD	1416	/* NetLabel: add a अटल label */
#घोषणा AUDIT_MAC_UNLBL_STCDEL	1417	/* NetLabel: del a अटल label */
#घोषणा AUDIT_MAC_CALIPSO_ADD	1418	/* NetLabel: add CALIPSO DOI entry */
#घोषणा AUDIT_MAC_CALIPSO_DEL	1419	/* NetLabel: del CALIPSO DOI entry */

#घोषणा AUDIT_FIRST_KERN_ANOM_MSG   1700
#घोषणा AUDIT_LAST_KERN_ANOM_MSG    1799
#घोषणा AUDIT_ANOM_PROMISCUOUS      1700 /* Device changed promiscuous mode */
#घोषणा AUDIT_ANOM_ABEND            1701 /* Process ended abnormally */
#घोषणा AUDIT_ANOM_LINK		    1702 /* Suspicious use of file links */
#घोषणा AUDIT_ANOM_CREAT	    1703 /* Suspicious file creation */
#घोषणा AUDIT_INTEGRITY_DATA	    1800 /* Data पूर्णांकegrity verअगरication */
#घोषणा AUDIT_INTEGRITY_METADATA    1801 /* Metadata पूर्णांकegrity verअगरication */
#घोषणा AUDIT_INTEGRITY_STATUS	    1802 /* Integrity enable status */
#घोषणा AUDIT_INTEGRITY_HASH	    1803 /* Integrity HASH type */
#घोषणा AUDIT_INTEGRITY_PCR	    1804 /* PCR invalidation msgs */
#घोषणा AUDIT_INTEGRITY_RULE	    1805 /* policy rule */
#घोषणा AUDIT_INTEGRITY_EVM_XATTR   1806 /* New EVM-covered xattr */
#घोषणा AUDIT_INTEGRITY_POLICY_RULE 1807 /* IMA policy rules */

#घोषणा AUDIT_KERNEL		2000	/* Asynchronous audit record. NOT A REQUEST. */

/* Rule flags */
#घोषणा AUDIT_FILTER_USER	0x00	/* Apply rule to user-generated messages */
#घोषणा AUDIT_FILTER_TASK	0x01	/* Apply rule at task creation (not syscall) */
#घोषणा AUDIT_FILTER_ENTRY	0x02	/* Apply rule at syscall entry */
#घोषणा AUDIT_FILTER_WATCH	0x03	/* Apply rule to file प्रणाली watches */
#घोषणा AUDIT_FILTER_EXIT	0x04	/* Apply rule at syscall निकास */
#घोषणा AUDIT_FILTER_EXCLUDE	0x05	/* Apply rule beक्रमe record creation */
#घोषणा AUDIT_FILTER_TYPE	AUDIT_FILTER_EXCLUDE /* obsolete misleading naming */
#घोषणा AUDIT_FILTER_FS		0x06	/* Apply rule at __audit_inode_child */

#घोषणा AUDIT_NR_FILTERS	7

#घोषणा AUDIT_FILTER_PREPEND	0x10	/* Prepend to front of list */

/* Rule actions */
#घोषणा AUDIT_NEVER    0	/* Do not build context अगर rule matches */
#घोषणा AUDIT_POSSIBLE 1	/* Build context अगर rule matches  */
#घोषणा AUDIT_ALWAYS   2	/* Generate audit record अगर rule matches */

/* Rule काष्ठाure sizes -- अगर these change, dअगरferent AUDIT_ADD and
 * AUDIT_LIST commands must be implemented. */
#घोषणा AUDIT_MAX_FIELDS   64
#घोषणा AUDIT_MAX_KEY_LEN  256
#घोषणा AUDIT_BITMASK_SIZE 64
#घोषणा AUDIT_WORD(nr) ((__u32)((nr)/32))
#घोषणा AUDIT_BIT(nr)  (1 << ((nr) - AUDIT_WORD(nr)*32))

#घोषणा AUDIT_SYSCALL_CLASSES 16
#घोषणा AUDIT_CLASS_सूची_WRITE 0
#घोषणा AUDIT_CLASS_सूची_WRITE_32 1
#घोषणा AUDIT_CLASS_CHATTR 2
#घोषणा AUDIT_CLASS_CHATTR_32 3
#घोषणा AUDIT_CLASS_READ 4
#घोषणा AUDIT_CLASS_READ_32 5
#घोषणा AUDIT_CLASS_WRITE 6
#घोषणा AUDIT_CLASS_WRITE_32 7
#घोषणा AUDIT_CLASS_SIGNAL 8
#घोषणा AUDIT_CLASS_SIGNAL_32 9

/* This biपंचांगask is used to validate user input.  It represents all bits that
 * are currently used in an audit field स्थिरant understood by the kernel.
 * If you are adding a new #घोषणा AUDIT_<whatever>, please ensure that
 * AUDIT_UNUSED_BITS is updated अगर need be. */
#घोषणा AUDIT_UNUSED_BITS	0x07FFFC00

/* AUDIT_FIELD_COMPARE rule list */
#घोषणा AUDIT_COMPARE_UID_TO_OBJ_UID	1
#घोषणा AUDIT_COMPARE_GID_TO_OBJ_GID	2
#घोषणा AUDIT_COMPARE_EUID_TO_OBJ_UID	3
#घोषणा AUDIT_COMPARE_EGID_TO_OBJ_GID	4
#घोषणा AUDIT_COMPARE_AUID_TO_OBJ_UID	5
#घोषणा AUDIT_COMPARE_SUID_TO_OBJ_UID	6
#घोषणा AUDIT_COMPARE_SGID_TO_OBJ_GID	7
#घोषणा AUDIT_COMPARE_FSUID_TO_OBJ_UID	8
#घोषणा AUDIT_COMPARE_FSGID_TO_OBJ_GID	9

#घोषणा AUDIT_COMPARE_UID_TO_AUID	10
#घोषणा AUDIT_COMPARE_UID_TO_EUID	11
#घोषणा AUDIT_COMPARE_UID_TO_FSUID	12
#घोषणा AUDIT_COMPARE_UID_TO_SUID	13

#घोषणा AUDIT_COMPARE_AUID_TO_FSUID	14
#घोषणा AUDIT_COMPARE_AUID_TO_SUID	15
#घोषणा AUDIT_COMPARE_AUID_TO_EUID	16

#घोषणा AUDIT_COMPARE_EUID_TO_SUID	17
#घोषणा AUDIT_COMPARE_EUID_TO_FSUID	18

#घोषणा AUDIT_COMPARE_SUID_TO_FSUID	19

#घोषणा AUDIT_COMPARE_GID_TO_EGID	20
#घोषणा AUDIT_COMPARE_GID_TO_FSGID	21
#घोषणा AUDIT_COMPARE_GID_TO_SGID	22

#घोषणा AUDIT_COMPARE_EGID_TO_FSGID	23
#घोषणा AUDIT_COMPARE_EGID_TO_SGID	24
#घोषणा AUDIT_COMPARE_SGID_TO_FSGID	25

#घोषणा AUDIT_MAX_FIELD_COMPARE		AUDIT_COMPARE_SGID_TO_FSGID

/* Rule fields */
				/* These are useful when checking the
				 * task काष्ठाure at task creation समय
				 * (AUDIT_PER_TASK).  */
#घोषणा AUDIT_PID	0
#घोषणा AUDIT_UID	1
#घोषणा AUDIT_EUID	2
#घोषणा AUDIT_SUID	3
#घोषणा AUDIT_FSUID	4
#घोषणा AUDIT_GID	5
#घोषणा AUDIT_EGID	6
#घोषणा AUDIT_SGID	7
#घोषणा AUDIT_FSGID	8
#घोषणा AUDIT_LOGINUID	9
#घोषणा AUDIT_PERS	10
#घोषणा AUDIT_ARCH	11
#घोषणा AUDIT_MSGTYPE	12
#घोषणा AUDIT_SUBJ_USER	13	/* security label user */
#घोषणा AUDIT_SUBJ_ROLE	14	/* security label role */
#घोषणा AUDIT_SUBJ_TYPE	15	/* security label type */
#घोषणा AUDIT_SUBJ_SEN	16	/* security label sensitivity label */
#घोषणा AUDIT_SUBJ_CLR	17	/* security label clearance label */
#घोषणा AUDIT_PPID	18
#घोषणा AUDIT_OBJ_USER	19
#घोषणा AUDIT_OBJ_ROLE	20
#घोषणा AUDIT_OBJ_TYPE	21
#घोषणा AUDIT_OBJ_LEV_LOW	22
#घोषणा AUDIT_OBJ_LEV_HIGH	23
#घोषणा AUDIT_LOGINUID_SET	24
#घोषणा AUDIT_SESSIONID	25	/* Session ID */
#घोषणा AUDIT_FSTYPE	26	/* FileSystem Type */

				/* These are ONLY useful when checking
				 * at syscall निकास समय (AUDIT_AT_EXIT). */
#घोषणा AUDIT_DEVMAJOR	100
#घोषणा AUDIT_DEVMINOR	101
#घोषणा AUDIT_INODE	102
#घोषणा AUDIT_EXIT	103
#घोषणा AUDIT_SUCCESS   104	/* निकास >= 0; value ignored */
#घोषणा AUDIT_WATCH	105
#घोषणा AUDIT_PERM	106
#घोषणा AUDIT_सूची	107
#घोषणा AUDIT_खाताTYPE	108
#घोषणा AUDIT_OBJ_UID	109
#घोषणा AUDIT_OBJ_GID	110
#घोषणा AUDIT_FIELD_COMPARE	111
#घोषणा AUDIT_EXE	112
#घोषणा AUDIT_SADDR_FAM	113

#घोषणा AUDIT_ARG0      200
#घोषणा AUDIT_ARG1      (AUDIT_ARG0+1)
#घोषणा AUDIT_ARG2      (AUDIT_ARG0+2)
#घोषणा AUDIT_ARG3      (AUDIT_ARG0+3)

#घोषणा AUDIT_FILTERKEY	210

#घोषणा AUDIT_NEGATE			0x80000000

/* These are the supported चालकs.
 *	4  2  1  8
 *	=  >  <  ?
 *	----------
 *	0  0  0	 0	00	nonsense
 *	0  0  0	 1	08	&  bit mask
 *	0  0  1	 0	10	<
 *	0  1  0	 0	20	>
 *	0  1  1	 0	30	!=
 *	1  0  0	 0	40	=
 *	1  0  0	 1	48	&=  bit test
 *	1  0  1	 0	50	<=
 *	1  1  0	 0	60	>=
 *	1  1  1	 1	78	all चालकs
 */
#घोषणा AUDIT_BIT_MASK			0x08000000
#घोषणा AUDIT_LESS_THAN			0x10000000
#घोषणा AUDIT_GREATER_THAN		0x20000000
#घोषणा AUDIT_NOT_EQUAL			0x30000000
#घोषणा AUDIT_EQUAL			0x40000000
#घोषणा AUDIT_BIT_TEST			(AUDIT_BIT_MASK|AUDIT_EQUAL)
#घोषणा AUDIT_LESS_THAN_OR_EQUAL	(AUDIT_LESS_THAN|AUDIT_EQUAL)
#घोषणा AUDIT_GREATER_THAN_OR_EQUAL	(AUDIT_GREATER_THAN|AUDIT_EQUAL)
#घोषणा AUDIT_OPERATORS			(AUDIT_EQUAL|AUDIT_NOT_EQUAL|AUDIT_BIT_MASK)

क्रमागत अणु
	Audit_equal,
	Audit_not_equal,
	Audit_biपंचांगask,
	Audit_bittest,
	Audit_lt,
	Audit_gt,
	Audit_le,
	Audit_ge,
	Audit_bad
पूर्ण;

/* Status symbols */
						/* Mask values */
#घोषणा AUDIT_STATUS_ENABLED			0x0001
#घोषणा AUDIT_STATUS_FAILURE			0x0002
#घोषणा AUDIT_STATUS_PID			0x0004
#घोषणा AUDIT_STATUS_RATE_LIMIT		0x0008
#घोषणा AUDIT_STATUS_BACKLOG_LIMIT		0x0010
#घोषणा AUDIT_STATUS_BACKLOG_WAIT_TIME		0x0020
#घोषणा AUDIT_STATUS_LOST			0x0040
#घोषणा AUDIT_STATUS_BACKLOG_WAIT_TIME_ACTUAL	0x0080

#घोषणा AUDIT_FEATURE_BITMAP_BACKLOG_LIMIT	0x00000001
#घोषणा AUDIT_FEATURE_BITMAP_BACKLOG_WAIT_TIME	0x00000002
#घोषणा AUDIT_FEATURE_BITMAP_EXECUTABLE_PATH	0x00000004
#घोषणा AUDIT_FEATURE_BITMAP_EXCLUDE_EXTEND	0x00000008
#घोषणा AUDIT_FEATURE_BITMAP_SESSIONID_FILTER	0x00000010
#घोषणा AUDIT_FEATURE_BITMAP_LOST_RESET		0x00000020
#घोषणा AUDIT_FEATURE_BITMAP_FILTER_FS		0x00000040

#घोषणा AUDIT_FEATURE_BITMAP_ALL (AUDIT_FEATURE_BITMAP_BACKLOG_LIMIT | \
				  AUDIT_FEATURE_BITMAP_BACKLOG_WAIT_TIME | \
				  AUDIT_FEATURE_BITMAP_EXECUTABLE_PATH | \
				  AUDIT_FEATURE_BITMAP_EXCLUDE_EXTEND | \
				  AUDIT_FEATURE_BITMAP_SESSIONID_FILTER | \
				  AUDIT_FEATURE_BITMAP_LOST_RESET | \
				  AUDIT_FEATURE_BITMAP_FILTER_FS)

/* deprecated: AUDIT_VERSION_* */
#घोषणा AUDIT_VERSION_LATEST 		AUDIT_FEATURE_BITMAP_ALL
#घोषणा AUDIT_VERSION_BACKLOG_LIMIT	AUDIT_FEATURE_BITMAP_BACKLOG_LIMIT
#घोषणा AUDIT_VERSION_BACKLOG_WAIT_TIME	AUDIT_FEATURE_BITMAP_BACKLOG_WAIT_TIME

				/* Failure-to-log actions */
#घोषणा AUDIT_FAIL_SILENT	0
#घोषणा AUDIT_FAIL_PRINTK	1
#घोषणा AUDIT_FAIL_PANIC	2

/*
 * These bits disambiguate dअगरferent calling conventions that share an
 * ELF machine type, bitness, and endianness
 */
#घोषणा __AUDIT_ARCH_CONVENTION_MASK 0x30000000
#घोषणा __AUDIT_ARCH_CONVENTION_MIPS64_N32 0x20000000

/* distinguish syscall tables */
#घोषणा __AUDIT_ARCH_64BIT 0x80000000
#घोषणा __AUDIT_ARCH_LE	   0x40000000

#घोषणा AUDIT_ARCH_AARCH64	(EM_AARCH64|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_ALPHA	(EM_ALPHA|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_ARCOMPACT	(EM_ARCOMPACT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_ARCOMPACTBE	(EM_ARCOMPACT)
#घोषणा AUDIT_ARCH_ARCV2	(EM_ARCV2|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_ARCV2BE	(EM_ARCV2)
#घोषणा AUDIT_ARCH_ARM		(EM_ARM|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_ARMEB	(EM_ARM)
#घोषणा AUDIT_ARCH_C6X		(EM_TI_C6000|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_C6XBE	(EM_TI_C6000)
#घोषणा AUDIT_ARCH_CRIS		(EM_CRIS|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_CSKY		(EM_CSKY|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_FRV		(EM_FRV)
#घोषणा AUDIT_ARCH_H8300	(EM_H8_300)
#घोषणा AUDIT_ARCH_HEXAGON	(EM_HEXAGON)
#घोषणा AUDIT_ARCH_I386		(EM_386|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_IA64		(EM_IA_64|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_M32R		(EM_M32R)
#घोषणा AUDIT_ARCH_M68K		(EM_68K)
#घोषणा AUDIT_ARCH_MICROBLAZE	(EM_MICROBLAZE)
#घोषणा AUDIT_ARCH_MIPS		(EM_MIPS)
#घोषणा AUDIT_ARCH_MIPSEL	(EM_MIPS|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_MIPS64	(EM_MIPS|__AUDIT_ARCH_64BIT)
#घोषणा AUDIT_ARCH_MIPS64N32	(EM_MIPS|__AUDIT_ARCH_64BIT|\
				 __AUDIT_ARCH_CONVENTION_MIPS64_N32)
#घोषणा AUDIT_ARCH_MIPSEL64	(EM_MIPS|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_MIPSEL64N32	(EM_MIPS|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE|\
				 __AUDIT_ARCH_CONVENTION_MIPS64_N32)
#घोषणा AUDIT_ARCH_NDS32	(EM_NDS32|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_NDS32BE	(EM_NDS32)
#घोषणा AUDIT_ARCH_NIOS2	(EM_ALTERA_NIOS2|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_OPENRISC	(EM_OPENRISC)
#घोषणा AUDIT_ARCH_PARISC	(EM_PARISC)
#घोषणा AUDIT_ARCH_PARISC64	(EM_PARISC|__AUDIT_ARCH_64BIT)
#घोषणा AUDIT_ARCH_PPC		(EM_PPC)
/* करो not define AUDIT_ARCH_PPCLE since it is not supported by audit */
#घोषणा AUDIT_ARCH_PPC64	(EM_PPC64|__AUDIT_ARCH_64BIT)
#घोषणा AUDIT_ARCH_PPC64LE	(EM_PPC64|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_RISCV32	(EM_RISCV|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_RISCV64	(EM_RISCV|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_S390		(EM_S390)
#घोषणा AUDIT_ARCH_S390X	(EM_S390|__AUDIT_ARCH_64BIT)
#घोषणा AUDIT_ARCH_SH		(EM_SH)
#घोषणा AUDIT_ARCH_SHEL		(EM_SH|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_SH64		(EM_SH|__AUDIT_ARCH_64BIT)
#घोषणा AUDIT_ARCH_SHEL64	(EM_SH|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_SPARC	(EM_SPARC)
#घोषणा AUDIT_ARCH_SPARC64	(EM_SPARCV9|__AUDIT_ARCH_64BIT)
#घोषणा AUDIT_ARCH_TILEGX	(EM_TILEGX|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_TILEGX32	(EM_TILEGX|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_TILEPRO	(EM_TILEPRO|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_UNICORE	(EM_UNICORE|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_X86_64	(EM_X86_64|__AUDIT_ARCH_64BIT|__AUDIT_ARCH_LE)
#घोषणा AUDIT_ARCH_XTENSA	(EM_XTENSA)

#घोषणा AUDIT_PERM_EXEC		1
#घोषणा AUDIT_PERM_WRITE	2
#घोषणा AUDIT_PERM_READ		4
#घोषणा AUDIT_PERM_ATTR		8

/* MAX_AUDIT_MESSAGE_LENGTH is set in audit:lib/libaudit.h as:
 * 8970 // PATH_MAX*2+CONTEXT_SIZE*2+11+256+1
 * max header+body+tailer: 44 + 29 + 32 + 262 + 7 + pad
 */
#घोषणा AUDIT_MESSAGE_TEXT_MAX	8560

/* Multicast Netlink socket groups (शेष up to 32) */
क्रमागत audit_nlgrps अणु
	AUDIT_NLGRP_NONE,	/* Group 0 not used */
	AUDIT_NLGRP_READLOG,	/* "best effort" पढ़ो only socket */
	__AUDIT_NLGRP_MAX
पूर्ण;
#घोषणा AUDIT_NLGRP_MAX                (__AUDIT_NLGRP_MAX - 1)

काष्ठा audit_status अणु
	__u32		mask;		/* Bit mask क्रम valid entries */
	__u32		enabled;	/* 1 = enabled, 0 = disabled */
	__u32		failure;	/* Failure-to-log action */
	__u32		pid;		/* pid of auditd process */
	__u32		rate_limit;	/* messages rate limit (per second) */
	__u32		backlog_limit;	/* रुकोing messages limit */
	__u32		lost;		/* messages lost */
	__u32		backlog;	/* messages रुकोing in queue */
	जोड़ अणु
		__u32	version;	/* deprecated: audit api version num */
		__u32	feature_biपंचांगap;	/* biपंचांगap of kernel audit features */
	पूर्ण;
	__u32		backlog_रुको_समय;/* message queue रुको समयout */
	__u32           backlog_रुको_समय_actual;/* समय spent रुकोing जबतक
						  * message limit exceeded
						  */
पूर्ण;

काष्ठा audit_features अणु
#घोषणा AUDIT_FEATURE_VERSION	1
	__u32	vers;
	__u32	mask;		/* which bits we are dealing with */
	__u32	features;	/* which feature to enable/disable */
	__u32	lock;		/* which features to lock */
पूर्ण;

#घोषणा AUDIT_FEATURE_ONLY_UNSET_LOGINUID	0
#घोषणा AUDIT_FEATURE_LOGINUID_IMMUTABLE	1
#घोषणा AUDIT_LAST_FEATURE			AUDIT_FEATURE_LOGINUID_IMMUTABLE

#घोषणा audit_feature_valid(x)		((x) >= 0 && (x) <= AUDIT_LAST_FEATURE)
#घोषणा AUDIT_FEATURE_TO_MASK(x)	(1 << ((x) & 31)) /* mask क्रम __u32 */

काष्ठा audit_tty_status अणु
	__u32		enabled;	/* 1 = enabled, 0 = disabled */
	__u32		log_passwd;	/* 1 = enabled, 0 = disabled */
पूर्ण;

#घोषणा AUDIT_UID_UNSET (अचिन्हित पूर्णांक)-1
#घोषणा AUDIT_SID_UNSET ((अचिन्हित पूर्णांक)-1)

/* audit_rule_data supports filter rules with both पूर्णांकeger and string
 * fields.  It corresponds with AUDIT_ADD_RULE, AUDIT_DEL_RULE and
 * AUDIT_LIST_RULES requests.
 */
काष्ठा audit_rule_data अणु
	__u32		flags;	/* AUDIT_PER_अणुTASK,CALLपूर्ण, AUDIT_PREPEND */
	__u32		action;	/* AUDIT_NEVER, AUDIT_POSSIBLE, AUDIT_ALWAYS */
	__u32		field_count;
	__u32		mask[AUDIT_BITMASK_SIZE]; /* syscall(s) affected */
	__u32		fields[AUDIT_MAX_FIELDS];
	__u32		values[AUDIT_MAX_FIELDS];
	__u32		fieldflags[AUDIT_MAX_FIELDS];
	__u32		buflen;	/* total length of string fields */
	अक्षर		buf[0];	/* string fields buffer */
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_AUDIT_H_ */
