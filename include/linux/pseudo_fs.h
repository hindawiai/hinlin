<शैली गुरु>
#अगर_अघोषित __LINUX_PSEUDO_FS__
#घोषणा __LINUX_PSEUDO_FS__

#समावेश <linux/fs_context.h>

काष्ठा pseuकरो_fs_context अणु
	स्थिर काष्ठा super_operations *ops;
	स्थिर काष्ठा xattr_handler **xattr;
	स्थिर काष्ठा dentry_operations *करोps;
	अचिन्हित दीर्घ magic;
पूर्ण;

काष्ठा pseuकरो_fs_context *init_pseuकरो(काष्ठा fs_context *fc,
				      अचिन्हित दीर्घ magic);

#पूर्ण_अगर
