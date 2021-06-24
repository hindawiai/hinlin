<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * Copyright (C) 2002 Andreas Gruenbacher <a.gruenbacher@computer.org>
 * Copyright (C) 2016 Red Hat, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License क्रम more details.
 *
 */

#अगर_अघोषित __UAPI_POSIX_ACL_XATTR_H
#घोषणा __UAPI_POSIX_ACL_XATTR_H

#समावेश <linux/types.h>

/* Supported ACL a_version fields */
#घोषणा POSIX_ACL_XATTR_VERSION	0x0002

/* An undefined entry e_id value */
#घोषणा ACL_UNDEFINED_ID	(-1)

काष्ठा posix_acl_xattr_entry अणु
	__le16			e_tag;
	__le16			e_perm;
	__le32			e_id;
पूर्ण;

काष्ठा posix_acl_xattr_header अणु
	__le32			a_version;
पूर्ण;

#पूर्ण_अगर	/* __UAPI_POSIX_ACL_XATTR_H */
