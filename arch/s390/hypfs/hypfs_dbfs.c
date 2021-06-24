<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hypervisor fileप्रणाली क्रम Linux on s390 - debugfs पूर्णांकerface
 *
 * Copyright IBM Corp. 2010
 * Author(s): Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश "hypfs.h"

अटल काष्ठा dentry *dbfs_dir;

अटल काष्ठा hypfs_dbfs_data *hypfs_dbfs_data_alloc(काष्ठा hypfs_dbfs_file *f)
अणु
	काष्ठा hypfs_dbfs_data *data;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस शून्य;
	data->dbfs_file = f;
	वापस data;
पूर्ण

अटल व्योम hypfs_dbfs_data_मुक्त(काष्ठा hypfs_dbfs_data *data)
अणु
	data->dbfs_file->data_मुक्त(data->buf_मुक्त_ptr);
	kमुक्त(data);
पूर्ण

अटल sमाप_प्रकार dbfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा hypfs_dbfs_data *data;
	काष्ठा hypfs_dbfs_file *df;
	sमाप_प्रकार rc;

	अगर (*ppos != 0)
		वापस 0;

	df = file_inode(file)->i_निजी;
	mutex_lock(&df->lock);
	data = hypfs_dbfs_data_alloc(df);
	अगर (!data) अणु
		mutex_unlock(&df->lock);
		वापस -ENOMEM;
	पूर्ण
	rc = df->data_create(&data->buf, &data->buf_मुक्त_ptr, &data->size);
	अगर (rc) अणु
		mutex_unlock(&df->lock);
		kमुक्त(data);
		वापस rc;
	पूर्ण
	mutex_unlock(&df->lock);

	rc = simple_पढ़ो_from_buffer(buf, size, ppos, data->buf, data->size);
	hypfs_dbfs_data_मुक्त(data);
	वापस rc;
पूर्ण

अटल दीर्घ dbfs_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा hypfs_dbfs_file *df = file_inode(file)->i_निजी;
	दीर्घ rc;

	mutex_lock(&df->lock);
	अगर (df->unlocked_ioctl)
		rc = df->unlocked_ioctl(file, cmd, arg);
	अन्यथा
		rc = -ENOTTY;
	mutex_unlock(&df->lock);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations dbfs_ops = अणु
	.पढ़ो		= dbfs_पढ़ो,
	.llseek		= no_llseek,
	.unlocked_ioctl = dbfs_ioctl,
पूर्ण;

व्योम hypfs_dbfs_create_file(काष्ठा hypfs_dbfs_file *df)
अणु
	df->dentry = debugfs_create_file(df->name, 0400, dbfs_dir, df,
					 &dbfs_ops);
	mutex_init(&df->lock);
पूर्ण

व्योम hypfs_dbfs_हटाओ_file(काष्ठा hypfs_dbfs_file *df)
अणु
	debugfs_हटाओ(df->dentry);
पूर्ण

व्योम hypfs_dbfs_init(व्योम)
अणु
	dbfs_dir = debugfs_create_dir("s390_hypfs", शून्य);
पूर्ण

व्योम hypfs_dbfs_निकास(व्योम)
अणु
	debugfs_हटाओ(dbfs_dir);
पूर्ण
