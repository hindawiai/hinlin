<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
  File: linux/posix_acl_xattr.h

  Extended attribute प्रणाली call representation of Access Control Lists.

  Copyright (C) 2000 by Andreas Gruenbacher <a.gruenbacher@computer.org>
  Copyright (C) 2002 SGI - Silicon Graphics, Inc <linux-xfs@oss.sgi.com>
 */
#अगर_अघोषित _POSIX_ACL_XATTR_H
#घोषणा _POSIX_ACL_XATTR_H

#समावेश <uapi/linux/xattr.h>
#समावेश <uapi/linux/posix_acl_xattr.h>
#समावेश <linux/posix_acl.h>

अटल अंतरभूत माप_प्रकार
posix_acl_xattr_size(पूर्णांक count)
अणु
	वापस (माप(काष्ठा posix_acl_xattr_header) +
		(count * माप(काष्ठा posix_acl_xattr_entry)));
पूर्ण

अटल अंतरभूत पूर्णांक
posix_acl_xattr_count(माप_प्रकार size)
अणु
	अगर (size < माप(काष्ठा posix_acl_xattr_header))
		वापस -1;
	size -= माप(काष्ठा posix_acl_xattr_header);
	अगर (size % माप(काष्ठा posix_acl_xattr_entry))
		वापस -1;
	वापस size / माप(काष्ठा posix_acl_xattr_entry);
पूर्ण

#अगर_घोषित CONFIG_FS_POSIX_ACL
व्योम posix_acl_fix_xattr_from_user(काष्ठा user_namespace *mnt_userns,
				   व्योम *value, माप_प्रकार size);
व्योम posix_acl_fix_xattr_to_user(काष्ठा user_namespace *mnt_userns,
				 व्योम *value, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत व्योम posix_acl_fix_xattr_from_user(काष्ठा user_namespace *mnt_userns,
						 व्योम *value, माप_प्रकार size)
अणु
पूर्ण
अटल अंतरभूत व्योम posix_acl_fix_xattr_to_user(काष्ठा user_namespace *mnt_userns,
					       व्योम *value, माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा posix_acl *posix_acl_from_xattr(काष्ठा user_namespace *user_ns, 
				       स्थिर व्योम *value, माप_प्रकार size);
पूर्णांक posix_acl_to_xattr(काष्ठा user_namespace *user_ns,
		       स्थिर काष्ठा posix_acl *acl, व्योम *buffer, माप_प्रकार size);

बाह्य स्थिर काष्ठा xattr_handler posix_acl_access_xattr_handler;
बाह्य स्थिर काष्ठा xattr_handler posix_acl_शेष_xattr_handler;

#पूर्ण_अगर	/* _POSIX_ACL_XATTR_H */
