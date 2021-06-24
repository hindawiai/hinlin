<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005-2008 Red Hat, Inc.  All rights reserved.
 */
#अगर_अघोषित __DLM_PLOCK_DOT_H__
#घोषणा __DLM_PLOCK_DOT_H__

#समावेश <uapi/linux/dlm_plock.h>

पूर्णांक dlm_posix_lock(dlm_lockspace_t *lockspace, u64 number, काष्ठा file *file,
		पूर्णांक cmd, काष्ठा file_lock *fl);
पूर्णांक dlm_posix_unlock(dlm_lockspace_t *lockspace, u64 number, काष्ठा file *file,
		काष्ठा file_lock *fl);
पूर्णांक dlm_posix_get(dlm_lockspace_t *lockspace, u64 number, काष्ठा file *file,
		काष्ठा file_lock *fl);
#पूर्ण_अगर
