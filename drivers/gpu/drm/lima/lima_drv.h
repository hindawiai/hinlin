<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_DRV_H__
#घोषणा __LIMA_DRV_H__

#समावेश <drm/drm_file.h>

#समावेश "lima_ctx.h"

बाह्य पूर्णांक lima_sched_समयout_ms;
बाह्य uपूर्णांक lima_heap_init_nr_pages;
बाह्य uपूर्णांक lima_max_error_tasks;
बाह्य uपूर्णांक lima_job_hang_limit;

काष्ठा lima_vm;
काष्ठा lima_bo;
काष्ठा lima_sched_task;

काष्ठा drm_lima_gem_submit_bo;

काष्ठा lima_drm_priv अणु
	काष्ठा lima_vm *vm;
	काष्ठा lima_ctx_mgr ctx_mgr;
पूर्ण;

काष्ठा lima_submit अणु
	काष्ठा lima_ctx *ctx;
	पूर्णांक pipe;
	u32 flags;

	काष्ठा drm_lima_gem_submit_bo *bos;
	काष्ठा lima_bo **lbos;
	u32 nr_bos;

	u32 in_sync[2];
	u32 out_sync;

	काष्ठा lima_sched_task *task;
पूर्ण;

अटल अंतरभूत काष्ठा lima_drm_priv *
to_lima_drm_priv(काष्ठा drm_file *file)
अणु
	वापस file->driver_priv;
पूर्ण

#पूर्ण_अगर
