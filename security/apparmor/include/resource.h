<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor resource limits function definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __AA_RESOURCE_H
#घोषणा __AA_RESOURCE_H

#समावेश <linux/resource.h>
#समावेश <linux/sched.h>

#समावेश "apparmorfs.h"

काष्ठा aa_profile;

/* काष्ठा aa_rlimit - rlimit settings क्रम the profile
 * @mask: which hard limits to set
 * @limits: rlimit values that override task limits
 *
 * AppArmor rlimits are used to set confined task rlimits.  Only the
 * limits specअगरied in @mask will be controlled by apparmor.
 */
काष्ठा aa_rlimit अणु
	अचिन्हित पूर्णांक mask;
	काष्ठा rlimit limits[RLIM_NLIMITS];
पूर्ण;

बाह्य काष्ठा aa_sfs_entry aa_sfs_entry_rlimit[];

पूर्णांक aa_map_resource(पूर्णांक resource);
पूर्णांक aa_task_setrlimit(काष्ठा aa_label *label, काष्ठा task_काष्ठा *task,
		      अचिन्हित पूर्णांक resource, काष्ठा rlimit *new_rlim);

व्योम __aa_transition_rlimits(काष्ठा aa_label *old, काष्ठा aa_label *new);

अटल अंतरभूत व्योम aa_मुक्त_rlimit_rules(काष्ठा aa_rlimit *rlims)
अणु
	/* NOP */
पूर्ण

#पूर्ण_अगर /* __AA_RESOURCE_H */
