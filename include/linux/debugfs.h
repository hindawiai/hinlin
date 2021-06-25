<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  debugfs.h - a tiny little debug file प्रणाली
 *
 *  Copyright (C) 2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *  Copyright (C) 2004 IBM Inc.
 *
 *  debugfs is क्रम people to use instead of /proc or /sys.
 *  See Documentation/fileप्रणालीs/ क्रम more details.
 */

#अगर_अघोषित _DEBUGFS_H_
#घोषणा _DEBUGFS_H_

#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

काष्ठा device;
काष्ठा file_operations;

काष्ठा debugfs_blob_wrapper अणु
	व्योम *data;
	अचिन्हित दीर्घ size;
पूर्ण;

काष्ठा debugfs_reg32 अणु
	अक्षर *name;
	अचिन्हित दीर्घ offset;
पूर्ण;

काष्ठा debugfs_regset32 अणु
	स्थिर काष्ठा debugfs_reg32 *regs;
	पूर्णांक nregs;
	व्योम __iomem *base;
	काष्ठा device *dev;	/* Optional device क्रम Runसमय PM */
पूर्ण;

काष्ठा debugfs_u32_array अणु
	u32 *array;
	u32 n_elements;
पूर्ण;

बाह्य काष्ठा dentry *arch_debugfs_dir;

#घोषणा DEFINE_DEBUGFS_ATTRIBUTE(__fops, __get, __set, __fmt)		\
अटल पूर्णांक __fops ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	__simple_attr_check_क्रमmat(__fmt, 0ull);			\
	वापस simple_attr_खोलो(inode, file, __get, __set, __fmt);	\
पूर्ण									\
अटल स्थिर काष्ठा file_operations __fops = अणु				\
	.owner	 = THIS_MODULE,						\
	.खोलो	 = __fops ## _खोलो,					\
	.release = simple_attr_release,					\
	.पढ़ो	 = debugfs_attr_पढ़ो,					\
	.ग_लिखो	 = debugfs_attr_ग_लिखो,					\
	.llseek  = no_llseek,						\
पूर्ण

प्रकार काष्ठा vfsmount *(*debugfs_स्वतःmount_t)(काष्ठा dentry *, व्योम *);

#अगर defined(CONFIG_DEBUG_FS)

काष्ठा dentry *debugfs_lookup(स्थिर अक्षर *name, काष्ठा dentry *parent);

काष्ठा dentry *debugfs_create_file(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, व्योम *data,
				   स्थिर काष्ठा file_operations *fops);
काष्ठा dentry *debugfs_create_file_unsafe(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, व्योम *data,
				   स्थिर काष्ठा file_operations *fops);

व्योम debugfs_create_file_size(स्थिर अक्षर *name, umode_t mode,
			      काष्ठा dentry *parent, व्योम *data,
			      स्थिर काष्ठा file_operations *fops,
			      loff_t file_size);

काष्ठा dentry *debugfs_create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent);

काष्ठा dentry *debugfs_create_symlink(स्थिर अक्षर *name, काष्ठा dentry *parent,
				      स्थिर अक्षर *dest);

काष्ठा dentry *debugfs_create_स्वतःmount(स्थिर अक्षर *name,
					काष्ठा dentry *parent,
					debugfs_स्वतःmount_t f,
					व्योम *data);

व्योम debugfs_हटाओ(काष्ठा dentry *dentry);
#घोषणा debugfs_हटाओ_recursive debugfs_हटाओ

स्थिर काष्ठा file_operations *debugfs_real_fops(स्थिर काष्ठा file *filp);

पूर्णांक debugfs_file_get(काष्ठा dentry *dentry);
व्योम debugfs_file_put(काष्ठा dentry *dentry);

sमाप_प्रकार debugfs_attr_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *ppos);
sमाप_प्रकार debugfs_attr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार len, loff_t *ppos);

काष्ठा dentry *debugfs_नाम(काष्ठा dentry *old_dir, काष्ठा dentry *old_dentry,
                काष्ठा dentry *new_dir, स्थिर अक्षर *new_name);

व्योम debugfs_create_u8(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
		       u8 *value);
व्योम debugfs_create_u16(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u16 *value);
व्योम debugfs_create_u32(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u32 *value);
व्योम debugfs_create_u64(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u64 *value);
काष्ठा dentry *debugfs_create_uदीर्घ(स्थिर अक्षर *name, umode_t mode,
				    काष्ठा dentry *parent, अचिन्हित दीर्घ *value);
व्योम debugfs_create_x8(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
		       u8 *value);
व्योम debugfs_create_x16(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u16 *value);
व्योम debugfs_create_x32(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u32 *value);
व्योम debugfs_create_x64(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u64 *value);
व्योम debugfs_create_माप_प्रकार(स्थिर अक्षर *name, umode_t mode,
			   काष्ठा dentry *parent, माप_प्रकार *value);
व्योम debugfs_create_atomic_t(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent, atomic_t *value);
काष्ठा dentry *debugfs_create_bool(स्थिर अक्षर *name, umode_t mode,
				  काष्ठा dentry *parent, bool *value);
व्योम debugfs_create_str(स्थिर अक्षर *name, umode_t mode,
			काष्ठा dentry *parent, अक्षर **value);

काष्ठा dentry *debugfs_create_blob(स्थिर अक्षर *name, umode_t mode,
				  काष्ठा dentry *parent,
				  काष्ठा debugfs_blob_wrapper *blob);

व्योम debugfs_create_regset32(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent,
			     काष्ठा debugfs_regset32 *regset);

व्योम debugfs_prपूर्णांक_regs32(काष्ठा seq_file *s, स्थिर काष्ठा debugfs_reg32 *regs,
			  पूर्णांक nregs, व्योम __iomem *base, अक्षर *prefix);

व्योम debugfs_create_u32_array(स्थिर अक्षर *name, umode_t mode,
			      काष्ठा dentry *parent,
			      काष्ठा debugfs_u32_array *array);

व्योम debugfs_create_devm_seqfile(काष्ठा device *dev, स्थिर अक्षर *name,
				 काष्ठा dentry *parent,
				 पूर्णांक (*पढ़ो_fn)(काष्ठा seq_file *s, व्योम *data));

bool debugfs_initialized(व्योम);

sमाप_प्रकार debugfs_पढ़ो_file_bool(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos);

sमाप_प्रकार debugfs_ग_लिखो_file_bool(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos);

sमाप_प्रकार debugfs_पढ़ो_file_str(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos);

#अन्यथा

#समावेश <linux/err.h>

/*
 * We करो not वापस शून्य from these functions अगर CONFIG_DEBUG_FS is not enabled
 * so users have a chance to detect अगर there was a real error or not.  We करोn't
 * want to duplicate the design decision mistakes of procfs and devfs again.
 */

अटल अंतरभूत काष्ठा dentry *debugfs_lookup(स्थिर अक्षर *name,
					    काष्ठा dentry *parent)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_file(स्थिर अक्षर *name, umode_t mode,
					काष्ठा dentry *parent, व्योम *data,
					स्थिर काष्ठा file_operations *fops)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_file_unsafe(स्थिर अक्षर *name,
					umode_t mode, काष्ठा dentry *parent,
					व्योम *data,
					स्थिर काष्ठा file_operations *fops)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम debugfs_create_file_size(स्थिर अक्षर *name, umode_t mode,
					    काष्ठा dentry *parent, व्योम *data,
					    स्थिर काष्ठा file_operations *fops,
					    loff_t file_size)
अणु पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_dir(स्थिर अक्षर *name,
						काष्ठा dentry *parent)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_symlink(स्थिर अक्षर *name,
						    काष्ठा dentry *parent,
						    स्थिर अक्षर *dest)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_स्वतःmount(स्थिर अक्षर *name,
					काष्ठा dentry *parent,
					debugfs_स्वतःmount_t f,
					व्योम *data)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम debugfs_हटाओ(काष्ठा dentry *dentry)
अणु पूर्ण

अटल अंतरभूत व्योम debugfs_हटाओ_recursive(काष्ठा dentry *dentry)
अणु पूर्ण

स्थिर काष्ठा file_operations *debugfs_real_fops(स्थिर काष्ठा file *filp);

अटल अंतरभूत पूर्णांक debugfs_file_get(काष्ठा dentry *dentry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम debugfs_file_put(काष्ठा dentry *dentry)
अणु पूर्ण

अटल अंतरभूत sमाप_प्रकार debugfs_attr_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
					माप_प्रकार len, loff_t *ppos)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत sमाप_प्रकार debugfs_attr_ग_लिखो(काष्ठा file *file,
					स्थिर अक्षर __user *buf,
					माप_प्रकार len, loff_t *ppos)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_नाम(काष्ठा dentry *old_dir, काष्ठा dentry *old_dentry,
                काष्ठा dentry *new_dir, अक्षर *new_name)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम debugfs_create_u8(स्थिर अक्षर *name, umode_t mode,
				     काष्ठा dentry *parent, u8 *value) अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_u16(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent, u16 *value) अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_u32(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent, u32 *value) अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_u64(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent, u64 *value) अणु पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_uदीर्घ(स्थिर अक्षर *name,
						umode_t mode,
						काष्ठा dentry *parent,
						अचिन्हित दीर्घ *value)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम debugfs_create_x8(स्थिर अक्षर *name, umode_t mode,
				     काष्ठा dentry *parent, u8 *value) अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_x16(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent, u16 *value) अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_x32(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent, u32 *value) अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_x64(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent, u64 *value) अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_माप_प्रकार(स्थिर अक्षर *name, umode_t mode,
					 काष्ठा dentry *parent, माप_प्रकार *value)
अणु पूर्ण

अटल अंतरभूत व्योम debugfs_create_atomic_t(स्थिर अक्षर *name, umode_t mode,
					   काष्ठा dentry *parent,
					   atomic_t *value)
अणु पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_bool(स्थिर अक्षर *name, umode_t mode,
						 काष्ठा dentry *parent,
						 bool *value)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम debugfs_create_str(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent,
				      अक्षर **value)
अणु पूर्ण

अटल अंतरभूत काष्ठा dentry *debugfs_create_blob(स्थिर अक्षर *name, umode_t mode,
				  काष्ठा dentry *parent,
				  काष्ठा debugfs_blob_wrapper *blob)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम debugfs_create_regset32(स्थिर अक्षर *name, umode_t mode,
					   काष्ठा dentry *parent,
					   काष्ठा debugfs_regset32 *regset)
अणु
पूर्ण

अटल अंतरभूत व्योम debugfs_prपूर्णांक_regs32(काष्ठा seq_file *s, स्थिर काष्ठा debugfs_reg32 *regs,
			 पूर्णांक nregs, व्योम __iomem *base, अक्षर *prefix)
अणु
पूर्ण

अटल अंतरभूत bool debugfs_initialized(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम debugfs_create_u32_array(स्थिर अक्षर *name, umode_t mode,
					    काष्ठा dentry *parent,
					    काष्ठा debugfs_u32_array *array)
अणु
पूर्ण

अटल अंतरभूत व्योम debugfs_create_devm_seqfile(काष्ठा device *dev,
					       स्थिर अक्षर *name,
					       काष्ठा dentry *parent,
					       पूर्णांक (*पढ़ो_fn)(काष्ठा seq_file *s,
							      व्योम *data))
अणु
पूर्ण

अटल अंतरभूत sमाप_प्रकार debugfs_पढ़ो_file_bool(काष्ठा file *file,
					     अक्षर __user *user_buf,
					     माप_प्रकार count, loff_t *ppos)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत sमाप_प्रकार debugfs_ग_लिखो_file_bool(काष्ठा file *file,
					      स्थिर अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत sमाप_प्रकार debugfs_पढ़ो_file_str(काष्ठा file *file,
					    अक्षर __user *user_buf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर

/**
 * debugfs_create_xul - create a debugfs file that is used to पढ़ो and ग_लिखो an
 * अचिन्हित दीर्घ value, क्रमmatted in hexadecimal
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 */
अटल अंतरभूत व्योम debugfs_create_xul(स्थिर अक्षर *name, umode_t mode,
				      काष्ठा dentry *parent,
				      अचिन्हित दीर्घ *value)
अणु
	अगर (माप(*value) == माप(u32))
		debugfs_create_x32(name, mode, parent, (u32 *)value);
	अन्यथा
		debugfs_create_x64(name, mode, parent, (u64 *)value);
पूर्ण

#पूर्ण_अगर
