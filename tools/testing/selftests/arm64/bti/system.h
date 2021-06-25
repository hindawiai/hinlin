<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#अगर_अघोषित SYSTEM_H
#घोषणा SYSTEM_H

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>

प्रकार __kernel_माप_प्रकार माप_प्रकार;
प्रकार __kernel_sमाप_प्रकार sमाप_प्रकार;

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/unistd.h>

#समावेश "compiler.h"

दीर्घ syscall(पूर्णांक nr, ...);

व्योम __noवापस निकास(पूर्णांक n);
sमाप_प्रकार ग_लिखो(पूर्णांक fd, स्थिर व्योम *buf, माप_प्रकार size);

#पूर्ण_अगर /* ! SYSTEM_H */
