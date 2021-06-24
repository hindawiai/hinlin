<शैली गुरु>
/*
 * Copyright IBM Corporation, 2010
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#अगर_अघोषित FS_9P_XATTR_H
#घोषणा FS_9P_XATTR_H

#समावेश <linux/xattr.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

बाह्य स्थिर काष्ठा xattr_handler *v9fs_xattr_handlers[];
बाह्य स्थिर काष्ठा xattr_handler v9fs_xattr_acl_access_handler;
बाह्य स्थिर काष्ठा xattr_handler v9fs_xattr_acl_शेष_handler;

बाह्य sमाप_प्रकार v9fs_fid_xattr_get(काष्ठा p9_fid *, स्थिर अक्षर *,
				  व्योम *, माप_प्रकार);
बाह्य sमाप_प्रकार v9fs_xattr_get(काष्ठा dentry *, स्थिर अक्षर *,
			      व्योम *, माप_प्रकार);
बाह्य पूर्णांक v9fs_fid_xattr_set(काष्ठा p9_fid *, स्थिर अक्षर *,
			  स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य पूर्णांक v9fs_xattr_set(काष्ठा dentry *, स्थिर अक्षर *,
			  स्थिर व्योम *, माप_प्रकार, पूर्णांक);
बाह्य sमाप_प्रकार v9fs_listxattr(काष्ठा dentry *, अक्षर *, माप_प्रकार);
#पूर्ण_अगर /* FS_9P_XATTR_H */
