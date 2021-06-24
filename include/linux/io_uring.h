<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _LINUX_IO_URING_H
#घोषणा _LINUX_IO_URING_H

#समावेश <linux/sched.h>
#समावेश <linux/xarray.h>

#अगर defined(CONFIG_IO_URING)
काष्ठा sock *io_uring_get_socket(काष्ठा file *file);
व्योम __io_uring_cancel(काष्ठा files_काष्ठा *files);
व्योम __io_uring_मुक्त(काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत व्योम io_uring_files_cancel(काष्ठा files_काष्ठा *files)
अणु
	अगर (current->io_uring)
		__io_uring_cancel(files);
पूर्ण
अटल अंतरभूत व्योम io_uring_task_cancel(व्योम)
अणु
	वापस io_uring_files_cancel(शून्य);
पूर्ण
अटल अंतरभूत व्योम io_uring_मुक्त(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->io_uring)
		__io_uring_मुक्त(tsk);
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा sock *io_uring_get_socket(काष्ठा file *file)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम io_uring_task_cancel(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम io_uring_files_cancel(काष्ठा files_काष्ठा *files)
अणु
पूर्ण
अटल अंतरभूत व्योम io_uring_मुक्त(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
