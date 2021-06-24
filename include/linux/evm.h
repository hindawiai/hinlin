<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * evm.h
 *
 * Copyright (c) 2009 IBM Corporation
 * Author: Mimi Zohar <zohar@us.ibm.com>
 */

#अगर_अघोषित _LINUX_EVM_H
#घोषणा _LINUX_EVM_H

#समावेश <linux/पूर्णांकegrity.h>
#समावेश <linux/xattr.h>

काष्ठा पूर्णांकegrity_iपूर्णांक_cache;

#अगर_घोषित CONFIG_EVM
बाह्य पूर्णांक evm_set_key(व्योम *key, माप_प्रकार keylen);
बाह्य क्रमागत पूर्णांकegrity_status evm_verअगरyxattr(काष्ठा dentry *dentry,
					     स्थिर अक्षर *xattr_name,
					     व्योम *xattr_value,
					     माप_प्रकार xattr_value_len,
					     काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक);
बाह्य पूर्णांक evm_inode_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr);
बाह्य व्योम evm_inode_post_setattr(काष्ठा dentry *dentry, पूर्णांक ia_valid);
बाह्य पूर्णांक evm_inode_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
			      स्थिर व्योम *value, माप_प्रकार size);
बाह्य व्योम evm_inode_post_setxattr(काष्ठा dentry *dentry,
				    स्थिर अक्षर *xattr_name,
				    स्थिर व्योम *xattr_value,
				    माप_प्रकार xattr_value_len);
बाह्य पूर्णांक evm_inode_हटाओxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name);
बाह्य व्योम evm_inode_post_हटाओxattr(काष्ठा dentry *dentry,
				       स्थिर अक्षर *xattr_name);
बाह्य पूर्णांक evm_inode_init_security(काष्ठा inode *inode,
				   स्थिर काष्ठा xattr *xattr_array,
				   काष्ठा xattr *evm);
#अगर_घोषित CONFIG_FS_POSIX_ACL
बाह्य पूर्णांक posix_xattr_acl(स्थिर अक्षर *xattrname);
#अन्यथा
अटल अंतरभूत पूर्णांक posix_xattr_acl(स्थिर अक्षर *xattrname)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#अन्यथा

अटल अंतरभूत पूर्णांक evm_set_key(व्योम *key, माप_प्रकार keylen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#अगर_घोषित CONFIG_INTEGRITY
अटल अंतरभूत क्रमागत पूर्णांकegrity_status evm_verअगरyxattr(काष्ठा dentry *dentry,
						    स्थिर अक्षर *xattr_name,
						    व्योम *xattr_value,
						    माप_प्रकार xattr_value_len,
					काष्ठा पूर्णांकegrity_iपूर्णांक_cache *iपूर्णांक)
अणु
	वापस INTEGRITY_UNKNOWN;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक evm_inode_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम evm_inode_post_setattr(काष्ठा dentry *dentry, पूर्णांक ia_valid)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक evm_inode_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *name,
				     स्थिर व्योम *value, माप_प्रकार size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम evm_inode_post_setxattr(काष्ठा dentry *dentry,
					   स्थिर अक्षर *xattr_name,
					   स्थिर व्योम *xattr_value,
					   माप_प्रकार xattr_value_len)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक evm_inode_हटाओxattr(काष्ठा dentry *dentry,
					स्थिर अक्षर *xattr_name)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम evm_inode_post_हटाओxattr(काष्ठा dentry *dentry,
					      स्थिर अक्षर *xattr_name)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक evm_inode_init_security(काष्ठा inode *inode,
					  स्थिर काष्ठा xattr *xattr_array,
					  काष्ठा xattr *evm)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_EVM */
#पूर्ण_अगर /* LINUX_EVM_H */
