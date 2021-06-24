<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Wrapper functions क्रम accessing the file_काष्ठा fd array.
 */

#अगर_अघोषित __LINUX_खाता_H
#घोषणा __LINUX_खाता_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/posix_types.h>
#समावेश <linux/त्रुटिसं.स>

काष्ठा file;

बाह्य व्योम fput(काष्ठा file *);
बाह्य व्योम fput_many(काष्ठा file *, अचिन्हित पूर्णांक);

काष्ठा file_operations;
काष्ठा task_काष्ठा;
काष्ठा vfsmount;
काष्ठा dentry;
काष्ठा inode;
काष्ठा path;
बाह्य काष्ठा file *alloc_file_pseuकरो(काष्ठा inode *, काष्ठा vfsmount *,
	स्थिर अक्षर *, पूर्णांक flags, स्थिर काष्ठा file_operations *);
बाह्य काष्ठा file *alloc_file_clone(काष्ठा file *, पूर्णांक flags,
	स्थिर काष्ठा file_operations *);

अटल अंतरभूत व्योम fput_light(काष्ठा file *file, पूर्णांक fput_needed)
अणु
	अगर (fput_needed)
		fput(file);
पूर्ण

काष्ठा fd अणु
	काष्ठा file *file;
	अचिन्हित पूर्णांक flags;
पूर्ण;
#घोषणा FDPUT_FPUT       1
#घोषणा FDPUT_POS_UNLOCK 2

अटल अंतरभूत व्योम fdput(काष्ठा fd fd)
अणु
	अगर (fd.flags & FDPUT_FPUT)
		fput(fd.file);
पूर्ण

बाह्य काष्ठा file *fget(अचिन्हित पूर्णांक fd);
बाह्य काष्ठा file *fget_many(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक refs);
बाह्य काष्ठा file *fget_raw(अचिन्हित पूर्णांक fd);
बाह्य काष्ठा file *fget_task(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक fd);
बाह्य अचिन्हित दीर्घ __fdget(अचिन्हित पूर्णांक fd);
बाह्य अचिन्हित दीर्घ __fdget_raw(अचिन्हित पूर्णांक fd);
बाह्य अचिन्हित दीर्घ __fdget_pos(अचिन्हित पूर्णांक fd);
बाह्य व्योम __f_unlock_pos(काष्ठा file *);

अटल अंतरभूत काष्ठा fd __to_fd(अचिन्हित दीर्घ v)
अणु
	वापस (काष्ठा fd)अणु(काष्ठा file *)(v & ~3),v & 3पूर्ण;
पूर्ण

अटल अंतरभूत काष्ठा fd fdget(अचिन्हित पूर्णांक fd)
अणु
	वापस __to_fd(__fdget(fd));
पूर्ण

अटल अंतरभूत काष्ठा fd fdget_raw(अचिन्हित पूर्णांक fd)
अणु
	वापस __to_fd(__fdget_raw(fd));
पूर्ण

अटल अंतरभूत काष्ठा fd fdget_pos(पूर्णांक fd)
अणु
	वापस __to_fd(__fdget_pos(fd));
पूर्ण

अटल अंतरभूत व्योम fdput_pos(काष्ठा fd f)
अणु
	अगर (f.flags & FDPUT_POS_UNLOCK)
		__f_unlock_pos(f.file);
	fdput(f);
पूर्ण

बाह्य पूर्णांक f_dupfd(अचिन्हित पूर्णांक from, काष्ठा file *file, अचिन्हित flags);
बाह्य पूर्णांक replace_fd(अचिन्हित fd, काष्ठा file *file, अचिन्हित flags);
बाह्य व्योम set_बंद_on_exec(अचिन्हित पूर्णांक fd, पूर्णांक flag);
बाह्य bool get_बंद_on_exec(अचिन्हित पूर्णांक fd);
बाह्य पूर्णांक __get_unused_fd_flags(अचिन्हित flags, अचिन्हित दीर्घ nofile);
बाह्य पूर्णांक get_unused_fd_flags(अचिन्हित flags);
बाह्य व्योम put_unused_fd(अचिन्हित पूर्णांक fd);

बाह्य व्योम fd_install(अचिन्हित पूर्णांक fd, काष्ठा file *file);

बाह्य पूर्णांक __receive_fd(काष्ठा file *file, पूर्णांक __user *ufd,
			अचिन्हित पूर्णांक o_flags);
अटल अंतरभूत पूर्णांक receive_fd_user(काष्ठा file *file, पूर्णांक __user *ufd,
				  अचिन्हित पूर्णांक o_flags)
अणु
	अगर (ufd == शून्य)
		वापस -EFAULT;
	वापस __receive_fd(file, ufd, o_flags);
पूर्ण
अटल अंतरभूत पूर्णांक receive_fd(काष्ठा file *file, अचिन्हित पूर्णांक o_flags)
अणु
	वापस __receive_fd(file, शून्य, o_flags);
पूर्ण
पूर्णांक receive_fd_replace(पूर्णांक new_fd, काष्ठा file *file, अचिन्हित पूर्णांक o_flags);

बाह्य व्योम flush_delayed_fput(व्योम);
बाह्य व्योम __fput_sync(काष्ठा file *);

बाह्य अचिन्हित पूर्णांक sysctl_nr_खोलो_min, sysctl_nr_खोलो_max;

#पूर्ण_अगर /* __LINUX_खाता_H */
