<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1

#समावेश "namespaces.h"
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

पूर्णांक setns(पूर्णांक fd, पूर्णांक nstype)
अणु
	वापस syscall(__NR_setns, fd, nstype);
पूर्ण
