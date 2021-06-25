<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  include/linux/संकेतfd.h
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#अगर_अघोषित _UAPI_LINUX_SIGNALFD_H
#घोषणा _UAPI_LINUX_SIGNALFD_H

#समावेश <linux/types.h>
/* For O_CLOEXEC and O_NONBLOCK */
#समावेश <linux/fcntl.h>

/* Flags क्रम संकेतfd4.  */
#घोषणा SFD_CLOEXEC O_CLOEXEC
#घोषणा SFD_NONBLOCK O_NONBLOCK

काष्ठा संकेतfd_siginfo अणु
	__u32 ssi_signo;
	__s32 ssi_त्रुटि_सं;
	__s32 ssi_code;
	__u32 ssi_pid;
	__u32 ssi_uid;
	__s32 ssi_fd;
	__u32 ssi_tid;
	__u32 ssi_band;
	__u32 ssi_overrun;
	__u32 ssi_trapno;
	__s32 ssi_status;
	__s32 ssi_पूर्णांक;
	__u64 ssi_ptr;
	__u64 ssi_uसमय;
	__u64 ssi_sसमय;
	__u64 ssi_addr;
	__u16 ssi_addr_lsb;
	__u16 __pad2;
	__s32 ssi_syscall;
	__u64 ssi_call_addr;
	__u32 ssi_arch;

	/*
	 * Pad strcture to 128 bytes. Remember to update the
	 * pad size when you add new members. We use a fixed
	 * size काष्ठाure to aव्योम compatibility problems with
	 * future versions, and we leave extra space क्रम additional
	 * members. We use fixed size members because this strcture
	 * comes out of a पढ़ो(2) and we really करोn't want to have
	 * a compat on पढ़ो(2).
	 */
	__u8 __pad[28];
पूर्ण;



#पूर्ण_अगर /* _UAPI_LINUX_SIGNALFD_H */
