<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor ipc mediation function definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_IPC_H
#घोषणा __AA_IPC_H

#समावेश <linux/sched.h>

काष्ठा aa_profile;

#घोषणा AA_PTRACE_TRACE		MAY_WRITE
#घोषणा AA_PTRACE_READ		MAY_READ
#घोषणा AA_MAY_BE_TRACED	AA_MAY_APPEND
#घोषणा AA_MAY_BE_READ		AA_MAY_CREATE
#घोषणा PTRACE_PERM_SHIFT	2

#घोषणा AA_PTRACE_PERM_MASK (AA_PTRACE_READ | AA_PTRACE_TRACE | \
			     AA_MAY_BE_READ | AA_MAY_BE_TRACED)
#घोषणा AA_SIGNAL_PERM_MASK (MAY_READ | MAY_WRITE)

#घोषणा AA_SFS_SIG_MASK "hup int quit ill trap abrt bus fpe kill usr1 " \
	"segv usr2 pipe alrm term stkflt chld cont stop stp ttin ttou urg " \
	"xcpu xfsz vtalrm prof winch io pwr sys emt lost"

पूर्णांक aa_may_ptrace(काष्ठा aa_label *tracer, काष्ठा aa_label *tracee,
		  u32 request);
पूर्णांक aa_may_संकेत(काष्ठा aa_label *sender, काष्ठा aa_label *target, पूर्णांक sig);

#पूर्ण_अगर /* __AA_IPC_H */
