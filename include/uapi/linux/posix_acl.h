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

#अगर_अघोषित __UAPI_POSIX_ACL_H
#घोषणा __UAPI_POSIX_ACL_H

#घोषणा ACL_UNDEFINED_ID	(-1)

/* a_type field in acl_user_posix_entry_t */
#घोषणा ACL_TYPE_ACCESS		(0x8000)
#घोषणा ACL_TYPE_DEFAULT	(0x4000)

/* e_tag entry in काष्ठा posix_acl_entry */
#घोषणा ACL_USER_OBJ		(0x01)
#घोषणा ACL_USER		(0x02)
#घोषणा ACL_GROUP_OBJ		(0x04)
#घोषणा ACL_GROUP		(0x08)
#घोषणा ACL_MASK		(0x10)
#घोषणा ACL_OTHER		(0x20)

/* permissions in the e_perm field */
#घोषणा ACL_READ		(0x04)
#घोषणा ACL_WRITE		(0x02)
#घोषणा ACL_EXECUTE		(0x01)

#पूर्ण_अगर  /* __UAPI_POSIX_ACL_H */
