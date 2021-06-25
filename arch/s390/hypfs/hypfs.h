<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Hypervisor fileप्रणाली क्रम Linux on s390.
 *
 *    Copyright IBM Corp. 2006
 *    Author(s): Michael Holzheu <holzheu@de.ibm.com>
 */

#अगर_अघोषित _HYPFS_H_
#घोषणा _HYPFS_H_

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kref.h>
#समावेश <यंत्र/hypfs.h>

#घोषणा REG_खाता_MODE    0440
#घोषणा UPDATE_खाता_MODE 0220
#घोषणा सूची_MODE         0550

बाह्य काष्ठा dentry *hypfs_सूची_गढ़ो(काष्ठा dentry *parent, स्थिर अक्षर *name);

बाह्य काष्ठा dentry *hypfs_create_u64(काष्ठा dentry *dir, स्थिर अक्षर *name,
				       __u64 value);

बाह्य काष्ठा dentry *hypfs_create_str(काष्ठा dentry *dir, स्थिर अक्षर *name,
				       अक्षर *string);

/* LPAR Hypervisor */
बाह्य पूर्णांक hypfs_diag_init(व्योम);
बाह्य व्योम hypfs_diag_निकास(व्योम);
बाह्य पूर्णांक hypfs_diag_create_files(काष्ठा dentry *root);

/* VM Hypervisor */
बाह्य पूर्णांक hypfs_vm_init(व्योम);
बाह्य व्योम hypfs_vm_निकास(व्योम);
बाह्य पूर्णांक hypfs_vm_create_files(काष्ठा dentry *root);

/* VM diagnose 0c */
पूर्णांक hypfs_diag0c_init(व्योम);
व्योम hypfs_diag0c_निकास(व्योम);

/* Set Partition-Resource Parameter */
व्योम hypfs_sprp_init(व्योम);
व्योम hypfs_sprp_निकास(व्योम);

/* debugfs पूर्णांकerface */
काष्ठा hypfs_dbfs_file;

काष्ठा hypfs_dbfs_data अणु
	व्योम			*buf;
	व्योम			*buf_मुक्त_ptr;
	माप_प्रकार			size;
	काष्ठा hypfs_dbfs_file	*dbfs_file;
पूर्ण;

काष्ठा hypfs_dbfs_file अणु
	स्थिर अक्षर	*name;
	पूर्णांक		(*data_create)(व्योम **data, व्योम **data_मुक्त_ptr,
				       माप_प्रकार *size);
	व्योम		(*data_मुक्त)(स्थिर व्योम *buf_मुक्त_ptr);
	दीर्घ		(*unlocked_ioctl) (काष्ठा file *, अचिन्हित पूर्णांक,
					   अचिन्हित दीर्घ);

	/* Private data क्रम hypfs_dbfs.c */
	काष्ठा mutex		lock;
	काष्ठा dentry		*dentry;
पूर्ण;

बाह्य व्योम hypfs_dbfs_init(व्योम);
बाह्य व्योम hypfs_dbfs_निकास(व्योम);
बाह्य व्योम hypfs_dbfs_create_file(काष्ठा hypfs_dbfs_file *df);
बाह्य व्योम hypfs_dbfs_हटाओ_file(काष्ठा hypfs_dbfs_file *df);

#पूर्ण_अगर /* _HYPFS_H_ */
