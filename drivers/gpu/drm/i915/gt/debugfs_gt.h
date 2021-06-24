<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित DEBUGFS_GT_H
#घोषणा DEBUGFS_GT_H

#समावेश <linux/file.h>

काष्ठा पूर्णांकel_gt;

#घोषणा DEFINE_GT_DEBUGFS_ATTRIBUTE(__name)				\
	अटल पूर्णांक __name ## _खोलो(काष्ठा inode *inode, काष्ठा file *file) \
अणु									\
	वापस single_खोलो(file, __name ## _show, inode->i_निजी);	\
पूर्ण									\
अटल स्थिर काष्ठा file_operations __name ## _fops = अणु			\
	.owner = THIS_MODULE,						\
	.खोलो = __name ## _खोलो,					\
	.पढ़ो = seq_पढ़ो,						\
	.llseek = seq_lseek,						\
	.release = single_release,					\
पूर्ण

व्योम debugfs_gt_रेजिस्टर(काष्ठा पूर्णांकel_gt *gt);

काष्ठा debugfs_gt_file अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *fops;
	bool (*eval)(व्योम *data);
पूर्ण;

व्योम पूर्णांकel_gt_debugfs_रेजिस्टर_files(काष्ठा dentry *root,
				     स्थिर काष्ठा debugfs_gt_file *files,
				     अचिन्हित दीर्घ count, व्योम *data);

#पूर्ण_अगर /* DEBUGFS_GT_H */
