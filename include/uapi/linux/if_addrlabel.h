<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * अगर_addrlabel.h - netlink पूर्णांकerface क्रम address labels
 *
 * Copyright (C)2007 USAGI/WIDE Project,  All Rights Reserved.
 *
 * Authors:
 *	YOSHIFUJI Hideaki @ USAGI/WIDE <yoshfuji@linux-ipv6.org>
 */

#अगर_अघोषित __LINUX_IF_ADDRLABEL_H
#घोषणा __LINUX_IF_ADDRLABEL_H

#समावेश <linux/types.h>

काष्ठा अगरaddrlblmsg अणु
	__u8		अगरal_family;		/* Address family */
	__u8		__अगरal_reserved;	/* Reserved */
	__u8		अगरal_prefixlen;		/* Prefix length */
	__u8		अगरal_flags;		/* Flags */
	__u32		अगरal_index;		/* Link index */
	__u32		अगरal_seq;		/* sequence number */
पूर्ण;

क्रमागत अणु
	IFAL_ADDRESS = 1,
	IFAL_LABEL = 2,
	__IFAL_MAX
पूर्ण;

#घोषणा IFAL_MAX	(__IFAL_MAX - 1)

#पूर्ण_अगर
