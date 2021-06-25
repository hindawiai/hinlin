<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_NFLOG_H
#घोषणा __LINUX_BRIDGE_EBT_NFLOG_H

#समावेश <linux/types.h>

#घोषणा EBT_NFLOG_MASK 0x0

#घोषणा EBT_NFLOG_PREFIX_SIZE 64
#घोषणा EBT_NFLOG_WATCHER "nflog"

#घोषणा EBT_NFLOG_DEFAULT_GROUP		0x1
#घोषणा EBT_NFLOG_DEFAULT_THRESHOLD	1

काष्ठा ebt_nflog_info अणु
	__u32 len;
	__u16 group;
	__u16 threshold;
	__u16 flags;
	__u16 pad;
	अक्षर prefix[EBT_NFLOG_PREFIX_SIZE];
पूर्ण;

#पूर्ण_अगर				/* __LINUX_BRIDGE_EBT_NFLOG_H */
