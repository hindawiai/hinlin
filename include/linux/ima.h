<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008 IBM Corporation
 * Author: Mimi Zohar <zohar@us.ibm.com>
 */

#अगर_अघोषित _LINUX_IMA_H
#घोषणा _LINUX_IMA_H

#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/fs.h>
#समावेश <linux/security.h>
#समावेश <linux/kexec.h>
काष्ठा linux_binprm;

#अगर_घोषित CONFIG_IMA
बाह्य पूर्णांक ima_bprm_check(काष्ठा linux_binprm *bprm);
बाह्य पूर्णांक ima_file_check(काष्ठा file *file, पूर्णांक mask);
बाह्य व्योम ima_post_create_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
				    काष्ठा inode *inode);
बाह्य व्योम ima_file_मुक्त(काष्ठा file *file);
बाह्य पूर्णांक ima_file_mmap(काष्ठा file *file, अचिन्हित दीर्घ prot);
बाह्य पूर्णांक ima_file_mprotect(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ prot);
बाह्य पूर्णांक ima_load_data(क्रमागत kernel_load_data_id id, bool contents);
बाह्य पूर्णांक ima_post_load_data(अक्षर *buf, loff_t size,
			      क्रमागत kernel_load_data_id id, अक्षर *description);
बाह्य पूर्णांक ima_पढ़ो_file(काष्ठा file *file, क्रमागत kernel_पढ़ो_file_id id,
			 bool contents);
बाह्य पूर्णांक ima_post_पढ़ो_file(काष्ठा file *file, व्योम *buf, loff_t size,
			      क्रमागत kernel_पढ़ो_file_id id);
बाह्य व्योम ima_post_path_mknod(काष्ठा user_namespace *mnt_userns,
				काष्ठा dentry *dentry);
बाह्य पूर्णांक ima_file_hash(काष्ठा file *file, अक्षर *buf, माप_प्रकार buf_size);
बाह्य पूर्णांक ima_inode_hash(काष्ठा inode *inode, अक्षर *buf, माप_प्रकार buf_size);
बाह्य व्योम ima_kexec_cmdline(पूर्णांक kernel_fd, स्थिर व्योम *buf, पूर्णांक size);
बाह्य व्योम ima_measure_critical_data(स्थिर अक्षर *event_label,
				      स्थिर अक्षर *event_name,
				      स्थिर व्योम *buf, माप_प्रकार buf_len,
				      bool hash);

#अगर_घोषित CONFIG_IMA_APPRAISE_BOOTPARAM
बाह्य व्योम ima_appउठाओ_parse_cmdline(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ima_appउठाओ_parse_cmdline(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IMA_KEXEC
बाह्य व्योम ima_add_kexec_buffer(काष्ठा kimage *image);
#पूर्ण_अगर

#अगर_घोषित CONFIG_IMA_SECURE_AND_OR_TRUSTED_BOOT
बाह्य bool arch_ima_get_secureboot(व्योम);
बाह्य स्थिर अक्षर * स्थिर *arch_get_ima_policy(व्योम);
#अन्यथा
अटल अंतरभूत bool arch_ima_get_secureboot(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत स्थिर अक्षर * स्थिर *arch_get_ima_policy(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अन्यथा
अटल अंतरभूत पूर्णांक ima_bprm_check(काष्ठा linux_binprm *bprm)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_file_check(काष्ठा file *file, पूर्णांक mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ima_post_create_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
					   काष्ठा inode *inode)
अणु
पूर्ण

अटल अंतरभूत व्योम ima_file_मुक्त(काष्ठा file *file)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक ima_file_mmap(काष्ठा file *file, अचिन्हित दीर्घ prot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_file_mprotect(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ prot)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_load_data(क्रमागत kernel_load_data_id id, bool contents)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_post_load_data(अक्षर *buf, loff_t size,
				     क्रमागत kernel_load_data_id id,
				     अक्षर *description)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_पढ़ो_file(काष्ठा file *file, क्रमागत kernel_पढ़ो_file_id id,
				bool contents)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_post_पढ़ो_file(काष्ठा file *file, व्योम *buf, loff_t size,
				     क्रमागत kernel_पढ़ो_file_id id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ima_post_path_mknod(काष्ठा user_namespace *mnt_userns,
				       काष्ठा dentry *dentry)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक ima_file_hash(काष्ठा file *file, अक्षर *buf, माप_प्रकार buf_size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ima_inode_hash(काष्ठा inode *inode, अक्षर *buf, माप_प्रकार buf_size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम ima_kexec_cmdline(पूर्णांक kernel_fd, स्थिर व्योम *buf, पूर्णांक size) अणुपूर्ण

अटल अंतरभूत व्योम ima_measure_critical_data(स्थिर अक्षर *event_label,
					     स्थिर अक्षर *event_name,
					     स्थिर व्योम *buf, माप_प्रकार buf_len,
					     bool hash) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_IMA */

#अगर_अघोषित CONFIG_IMA_KEXEC
काष्ठा kimage;

अटल अंतरभूत व्योम ima_add_kexec_buffer(काष्ठा kimage *image)
अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IMA_MEASURE_ASYMMETRIC_KEYS
बाह्य व्योम ima_post_key_create_or_update(काष्ठा key *keyring,
					  काष्ठा key *key,
					  स्थिर व्योम *payload, माप_प्रकार plen,
					  अचिन्हित दीर्घ flags, bool create);
#अन्यथा
अटल अंतरभूत व्योम ima_post_key_create_or_update(काष्ठा key *keyring,
						 काष्ठा key *key,
						 स्थिर व्योम *payload,
						 माप_प्रकार plen,
						 अचिन्हित दीर्घ flags,
						 bool create) अणुपूर्ण
#पूर्ण_अगर  /* CONFIG_IMA_MEASURE_ASYMMETRIC_KEYS */

#अगर_घोषित CONFIG_IMA_APPRAISE
बाह्य bool is_ima_appउठाओ_enabled(व्योम);
बाह्य व्योम ima_inode_post_setattr(काष्ठा user_namespace *mnt_userns,
				   काष्ठा dentry *dentry);
बाह्य पूर्णांक ima_inode_setxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name,
		       स्थिर व्योम *xattr_value, माप_प्रकार xattr_value_len);
बाह्य पूर्णांक ima_inode_हटाओxattr(काष्ठा dentry *dentry, स्थिर अक्षर *xattr_name);
#अन्यथा
अटल अंतरभूत bool is_ima_appउठाओ_enabled(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ima_inode_post_setattr(काष्ठा user_namespace *mnt_userns,
					  काष्ठा dentry *dentry)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक ima_inode_setxattr(काष्ठा dentry *dentry,
				     स्थिर अक्षर *xattr_name,
				     स्थिर व्योम *xattr_value,
				     माप_प्रकार xattr_value_len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ima_inode_हटाओxattr(काष्ठा dentry *dentry,
					स्थिर अक्षर *xattr_name)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_IMA_APPRAISE */

#अगर defined(CONFIG_IMA_APPRAISE) && defined(CONFIG_INTEGRITY_TRUSTED_KEYRING)
बाह्य bool ima_appउठाओ_signature(क्रमागत kernel_पढ़ो_file_id func);
#अन्यथा
अटल अंतरभूत bool ima_appउठाओ_signature(क्रमागत kernel_पढ़ो_file_id func)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_IMA_APPRAISE && CONFIG_INTEGRITY_TRUSTED_KEYRING */
#पूर्ण_अगर /* _LINUX_IMA_H */
