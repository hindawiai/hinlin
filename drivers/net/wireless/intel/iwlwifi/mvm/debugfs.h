<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 */
#घोषणा MVM_DEBUGFS_READ_खाता_OPS(name)					\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.पढ़ो = iwl_dbgfs_##name##_पढ़ो,				\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण

#घोषणा MVM_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)		\
अटल sमाप_प्रकार _iwl_dbgfs_##name##_ग_लिखो(काष्ठा file *file,		\
					 स्थिर अक्षर __user *user_buf,	\
					 माप_प्रकार count, loff_t *ppos)	\
अणु									\
	argtype *arg = file->निजी_data;				\
	अक्षर buf[buflen] = अणुपूर्ण;						\
	माप_प्रकार buf_size = min(count, माप(buf) -  1);			\
									\
	अगर (copy_from_user(buf, user_buf, buf_size))			\
		वापस -EFAULT;						\
									\
	वापस iwl_dbgfs_##name##_ग_लिखो(arg, buf, buf_size, ppos);	\
पूर्ण									\

#घोषणा _MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, buflen, argtype)		\
MVM_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)			\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.ग_लिखो = _iwl_dbgfs_##name##_ग_लिखो,				\
	.पढ़ो = iwl_dbgfs_##name##_पढ़ो,				\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;

#घोषणा _MVM_DEBUGFS_WRITE_खाता_OPS(name, buflen, argtype)		\
MVM_DEBUGFS_WRITE_WRAPPER(name, buflen, argtype)			\
अटल स्थिर काष्ठा file_operations iwl_dbgfs_##name##_ops = अणु		\
	.ग_लिखो = _iwl_dbgfs_##name##_ग_लिखो,				\
	.खोलो = simple_खोलो,						\
	.llseek = generic_file_llseek,					\
पूर्ण;
