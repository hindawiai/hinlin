<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#समावेश "system.h"

#समावेश <यंत्र/unistd.h>

#समावेश "compiler.h"

व्योम __noवापस निकास(पूर्णांक n)
अणु
	syscall(__NR_निकास, n);
	__unreachable();
पूर्ण

sमाप_प्रकार ग_लिखो(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार size)
अणु
	वापस syscall(__NR_ग_लिखो, fd, buf, size);
पूर्ण
