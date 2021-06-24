<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 WITH Linux-syscall-note */
/*
 * cn_proc.h - process events connector
 *
 * Copyright (C) Matt Helsley, IBM Corp. 2005
 * Based on cn_विभाजन.h by Nguyen Anh Quynh and Guillaume Thouvenin
 * Copyright (C) 2005 Nguyen Anh Quynh <aquynh@gmail.com>
 * Copyright (C) 2005 Guillaume Thouvenin <guillaume.thouvenin@bull.net>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#अगर_अघोषित _UAPICN_PROC_H
#घोषणा _UAPICN_PROC_H

#समावेश <linux/types.h>

/*
 * Userspace sends this क्रमागत to रेजिस्टर with the kernel that it is listening
 * क्रम events on the connector.
 */
क्रमागत proc_cn_mcast_op अणु
	PROC_CN_MCAST_LISTEN = 1,
	PROC_CN_MCAST_IGNORE = 2
पूर्ण;

/*
 * From the user's poपूर्णांक of view, the process
 * ID is the thपढ़ो group ID and thपढ़ो ID is the पूर्णांकernal
 * kernel "pid". So, fields are asचिन्हित as follow:
 *
 *  In user space     -  In  kernel space
 *
 * parent process ID  =  parent->tgid
 * parent thपढ़ो  ID  =  parent->pid
 * child  process ID  =  child->tgid
 * child  thपढ़ो  ID  =  child->pid
 */

काष्ठा proc_event अणु
	क्रमागत what अणु
		/* Use successive bits so the क्रमागतs can be used to record
		 * sets of events as well
		 */
		PROC_EVENT_NONE = 0x00000000,
		PROC_EVENT_FORK = 0x00000001,
		PROC_EVENT_EXEC = 0x00000002,
		PROC_EVENT_UID  = 0x00000004,
		PROC_EVENT_GID  = 0x00000040,
		PROC_EVENT_SID  = 0x00000080,
		PROC_EVENT_PTRACE = 0x00000100,
		PROC_EVENT_COMM = 0x00000200,
		/* "next" should be 0x00000400 */
		/* "last" is the last process event: निकास,
		 * जबतक "next to last" is coredumping event */
		PROC_EVENT_COREDUMP = 0x40000000,
		PROC_EVENT_EXIT = 0x80000000
	पूर्ण what;
	__u32 cpu;
	__u64 __attribute__((aligned(8))) बारtamp_ns;
		/* Number of nano seconds since प्रणाली boot */
	जोड़ अणु /* must be last field of proc_event काष्ठा */
		काष्ठा अणु
			__u32 err;
		पूर्ण ack;

		काष्ठा विभाजन_proc_event अणु
			__kernel_pid_t parent_pid;
			__kernel_pid_t parent_tgid;
			__kernel_pid_t child_pid;
			__kernel_pid_t child_tgid;
		पूर्ण विभाजन;

		काष्ठा exec_proc_event अणु
			__kernel_pid_t process_pid;
			__kernel_pid_t process_tgid;
		पूर्ण exec;

		काष्ठा id_proc_event अणु
			__kernel_pid_t process_pid;
			__kernel_pid_t process_tgid;
			जोड़ अणु
				__u32 ruid; /* task uid */
				__u32 rgid; /* task gid */
			पूर्ण r;
			जोड़ अणु
				__u32 euid;
				__u32 egid;
			पूर्ण e;
		पूर्ण id;

		काष्ठा sid_proc_event अणु
			__kernel_pid_t process_pid;
			__kernel_pid_t process_tgid;
		पूर्ण sid;

		काष्ठा ptrace_proc_event अणु
			__kernel_pid_t process_pid;
			__kernel_pid_t process_tgid;
			__kernel_pid_t tracer_pid;
			__kernel_pid_t tracer_tgid;
		पूर्ण ptrace;

		काष्ठा comm_proc_event अणु
			__kernel_pid_t process_pid;
			__kernel_pid_t process_tgid;
			अक्षर           comm[16];
		पूर्ण comm;

		काष्ठा coredump_proc_event अणु
			__kernel_pid_t process_pid;
			__kernel_pid_t process_tgid;
			__kernel_pid_t parent_pid;
			__kernel_pid_t parent_tgid;
		पूर्ण coredump;

		काष्ठा निकास_proc_event अणु
			__kernel_pid_t process_pid;
			__kernel_pid_t process_tgid;
			__u32 निकास_code, निकास_संकेत;
			__kernel_pid_t parent_pid;
			__kernel_pid_t parent_tgid;
		पूर्ण निकास;

	पूर्ण event_data;
पूर्ण;

#पूर्ण_अगर /* _UAPICN_PROC_H */
