<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019  Arm Limited
 * Original author: Dave Martin <Dave.Martin@arm.com>
 */

#अगर_अघोषित SIGNAL_H
#घोषणा SIGNAL_H

#समावेश <linux/संकेत.स>

#समावेश "system.h"

प्रकार __sighandler_t sighandler_t;

पूर्णांक sigemptyset(sigset_t *s);
पूर्णांक sigaddset(sigset_t *s, पूर्णांक n);
पूर्णांक sigaction(पूर्णांक n, काष्ठा sigaction *sa, स्थिर काष्ठा sigaction *old);
पूर्णांक sigprocmask(पूर्णांक how, स्थिर sigset_t *mask, sigset_t *old);

#पूर्ण_अगर /* ! SIGNAL_H */
