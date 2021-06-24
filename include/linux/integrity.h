<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009 IBM Corporation
 * Author: Mimi Zohar <zohar@us.ibm.com>
 */

#अगर_अघोषित _LINUX_INTEGRITY_H
#घोषणा _LINUX_INTEGRITY_H

#समावेश <linux/fs.h>

क्रमागत पूर्णांकegrity_status अणु
	INTEGRITY_PASS = 0,
	INTEGRITY_PASS_IMMUTABLE,
	INTEGRITY_FAIL,
	INTEGRITY_NOLABEL,
	INTEGRITY_NOXATTRS,
	INTEGRITY_UNKNOWN,
पूर्ण;

/* List of EVM रक्षित security xattrs */
#अगर_घोषित CONFIG_INTEGRITY
बाह्य काष्ठा पूर्णांकegrity_iपूर्णांक_cache *पूर्णांकegrity_inode_get(काष्ठा inode *inode);
बाह्य व्योम पूर्णांकegrity_inode_मुक्त(काष्ठा inode *inode);
बाह्य व्योम __init पूर्णांकegrity_load_keys(व्योम);

#अन्यथा
अटल अंतरभूत काष्ठा पूर्णांकegrity_iपूर्णांक_cache *
				पूर्णांकegrity_inode_get(काष्ठा inode *inode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकegrity_inode_मुक्त(काष्ठा inode *inode)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकegrity_load_keys(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_INTEGRITY */

#अगर_घोषित CONFIG_INTEGRITY_ASYMMETRIC_KEYS

बाह्य पूर्णांक पूर्णांकegrity_kernel_module_request(अक्षर *kmod_name);

#अन्यथा

अटल अंतरभूत पूर्णांक पूर्णांकegrity_kernel_module_request(अक्षर *kmod_name)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_INTEGRITY_ASYMMETRIC_KEYS */

#पूर्ण_अगर /* _LINUX_INTEGRITY_H */
