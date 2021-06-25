<शैली गुरु>
#अगर_अघोषित __LINUX_USERMODE_DRIVER_H__
#घोषणा __LINUX_USERMODE_DRIVER_H__

#समावेश <linux/umh.h>
#समावेश <linux/path.h>

काष्ठा umd_info अणु
	स्थिर अक्षर *driver_name;
	काष्ठा file *pipe_to_umh;
	काष्ठा file *pipe_from_umh;
	काष्ठा path wd;
	काष्ठा pid *tgid;
पूर्ण;
पूर्णांक umd_load_blob(काष्ठा umd_info *info, स्थिर व्योम *data, माप_प्रकार len);
पूर्णांक umd_unload_blob(काष्ठा umd_info *info);
पूर्णांक विभाजन_usermode_driver(काष्ठा umd_info *info);
व्योम umd_cleanup_helper(काष्ठा umd_info *info);

#पूर्ण_अगर /* __LINUX_USERMODE_DRIVER_H__ */
