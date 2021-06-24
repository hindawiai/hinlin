<शैली गुरु>
/*
 * Will go away once libc support is there
 */
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/uपन.स>
#समावेश <संकेत.स>
#समावेश "liburing.h"

#अगर_घोषित __alpha__
/*
 * alpha is the only exception, all other architectures
 * have common numbers क्रम new प्रणाली calls.
 */
# अगरndef __NR_io_uring_setup
#  define __NR_io_uring_setup		535
# endअगर
# अगरndef __NR_io_uring_enter
#  define __NR_io_uring_enter		536
# endअगर
# अगरndef __NR_io_uring_रेजिस्टर
#  define __NR_io_uring_रेजिस्टर	537
# endअगर
#अन्यथा /* !__alpha__ */
# अगरndef __NR_io_uring_setup
#  define __NR_io_uring_setup		425
# endअगर
# अगरndef __NR_io_uring_enter
#  define __NR_io_uring_enter		426
# endअगर
# अगरndef __NR_io_uring_रेजिस्टर
#  define __NR_io_uring_रेजिस्टर	427
# endअगर
#पूर्ण_अगर

पूर्णांक io_uring_रेजिस्टर(पूर्णांक fd, अचिन्हित पूर्णांक opcode, व्योम *arg,
		      अचिन्हित पूर्णांक nr_args)
अणु
	वापस syscall(__NR_io_uring_रेजिस्टर, fd, opcode, arg, nr_args);
पूर्ण

पूर्णांक io_uring_setup(अचिन्हित पूर्णांक entries, काष्ठा io_uring_params *p)
अणु
	वापस syscall(__NR_io_uring_setup, entries, p);
पूर्ण

पूर्णांक io_uring_enter(पूर्णांक fd, अचिन्हित पूर्णांक to_submit, अचिन्हित पूर्णांक min_complete,
		   अचिन्हित पूर्णांक flags, sigset_t *sig)
अणु
	वापस syscall(__NR_io_uring_enter, fd, to_submit, min_complete,
			flags, sig, _NSIG / 8);
पूर्ण
