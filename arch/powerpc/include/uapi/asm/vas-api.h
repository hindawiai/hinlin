<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright 2019 IBM Corp.
 */

#अगर_अघोषित _UAPI_MISC_VAS_H
#घोषणा _UAPI_MISC_VAS_H

#समावेश <linux/types.h>

#समावेश <यंत्र/ioctl.h>

#घोषणा VAS_MAGIC	'v'
#घोषणा VAS_TX_WIN_OPEN	_IOW(VAS_MAGIC, 0x20, काष्ठा vas_tx_win_खोलो_attr)

काष्ठा vas_tx_win_खोलो_attr अणु
	__u32	version;
	__s16	vas_id;	/* specअगरic instance of vas or -1 क्रम शेष */
	__u16	reserved1;
	__u64	flags;	/* Future use */
	__u64	reserved2[6];
पूर्ण;

#पूर्ण_अगर /* _UAPI_MISC_VAS_H */
