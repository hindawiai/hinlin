<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2018-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_CTX_H__
#घोषणा __LIMA_CTX_H__

#समावेश <linux/xarray.h>
#समावेश <linux/sched.h>

#समावेश "lima_device.h"

काष्ठा lima_ctx अणु
	काष्ठा kref refcnt;
	काष्ठा lima_device *dev;
	काष्ठा lima_sched_context context[lima_pipe_num];
	atomic_t guilty;

	/* debug info */
	अक्षर pname[TASK_COMM_LEN];
	pid_t pid;
पूर्ण;

काष्ठा lima_ctx_mgr अणु
	काष्ठा mutex lock;
	काष्ठा xarray handles;
पूर्ण;

पूर्णांक lima_ctx_create(काष्ठा lima_device *dev, काष्ठा lima_ctx_mgr *mgr, u32 *id);
पूर्णांक lima_ctx_मुक्त(काष्ठा lima_ctx_mgr *mgr, u32 id);
काष्ठा lima_ctx *lima_ctx_get(काष्ठा lima_ctx_mgr *mgr, u32 id);
व्योम lima_ctx_put(काष्ठा lima_ctx *ctx);
व्योम lima_ctx_mgr_init(काष्ठा lima_ctx_mgr *mgr);
व्योम lima_ctx_mgr_fini(काष्ठा lima_ctx_mgr *mgr);

#पूर्ण_अगर
