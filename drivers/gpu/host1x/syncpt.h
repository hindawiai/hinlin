<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x Syncpoपूर्णांकs
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#अगर_अघोषित __HOST1X_SYNCPT_H
#घोषणा __HOST1X_SYNCPT_H

#समावेश <linux/atomic.h>
#समावेश <linux/host1x.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/sched.h>

#समावेश "intr.h"

काष्ठा host1x;

/* Reserved क्रम replacing an expired रुको with a NOP */
#घोषणा HOST1X_SYNCPT_RESERVED			0

काष्ठा host1x_syncpt_base अणु
	अचिन्हित पूर्णांक id;
	bool requested;
पूर्ण;

काष्ठा host1x_syncpt अणु
	काष्ठा kref ref;

	अचिन्हित पूर्णांक id;
	atomic_t min_val;
	atomic_t max_val;
	u32 base_val;
	स्थिर अक्षर *name;
	bool client_managed;
	काष्ठा host1x *host;
	काष्ठा host1x_syncpt_base *base;

	/* पूर्णांकerrupt data */
	काष्ठा host1x_syncpt_पूर्णांकr पूर्णांकr;
पूर्ण;

/* Initialize sync poपूर्णांक array  */
पूर्णांक host1x_syncpt_init(काष्ठा host1x *host);

/*  Free sync poपूर्णांक array */
व्योम host1x_syncpt_deinit(काष्ठा host1x *host);

/* Return number of sync poपूर्णांक supported. */
अचिन्हित पूर्णांक host1x_syncpt_nb_pts(काष्ठा host1x *host);

/* Return number of रुको bases supported. */
अचिन्हित पूर्णांक host1x_syncpt_nb_bases(काष्ठा host1x *host);

/* Return number of mlocks supported. */
अचिन्हित पूर्णांक host1x_syncpt_nb_mlocks(काष्ठा host1x *host);

/*
 * Check sync poपूर्णांक sanity. If max is larger than min, there have too many
 * sync poपूर्णांक increments.
 *
 * Client managed sync poपूर्णांक are not tracked.
 * */
अटल अंतरभूत bool host1x_syncpt_check_max(काष्ठा host1x_syncpt *sp, u32 real)
अणु
	u32 max;
	अगर (sp->client_managed)
		वापस true;
	max = host1x_syncpt_पढ़ो_max(sp);
	वापस (s32)(max - real) >= 0;
पूर्ण

/* Return true अगर sync poपूर्णांक is client managed. */
अटल अंतरभूत bool host1x_syncpt_client_managed(काष्ठा host1x_syncpt *sp)
अणु
	वापस sp->client_managed;
पूर्ण

/*
 * Returns true अगर syncpoपूर्णांक min == max, which means that there are no
 * outstanding operations.
 */
अटल अंतरभूत bool host1x_syncpt_idle(काष्ठा host1x_syncpt *sp)
अणु
	पूर्णांक min, max;
	smp_rmb();
	min = atomic_पढ़ो(&sp->min_val);
	max = atomic_पढ़ो(&sp->max_val);
	वापस (min == max);
पूर्ण

/* Load current value from hardware to the shaकरोw रेजिस्टर. */
u32 host1x_syncpt_load(काष्ठा host1x_syncpt *sp);

/* Check अगर the given syncpoपूर्णांक value has alपढ़ोy passed */
bool host1x_syncpt_is_expired(काष्ठा host1x_syncpt *sp, u32 thresh);

/* Save host1x sync poपूर्णांक state पूर्णांकo shaकरोw रेजिस्टरs. */
व्योम host1x_syncpt_save(काष्ठा host1x *host);

/* Reset host1x sync poपूर्णांक state from shaकरोw रेजिस्टरs. */
व्योम host1x_syncpt_restore(काष्ठा host1x *host);

/* Read current रुको base value पूर्णांकo shaकरोw रेजिस्टर and वापस it. */
u32 host1x_syncpt_load_रुको_base(काष्ठा host1x_syncpt *sp);

/* Indicate future operations by incrementing the sync poपूर्णांक max. */
u32 host1x_syncpt_incr_max(काष्ठा host1x_syncpt *sp, u32 incrs);

/* Check अगर sync poपूर्णांक id is valid. */
अटल अंतरभूत पूर्णांक host1x_syncpt_is_valid(काष्ठा host1x_syncpt *sp)
अणु
	वापस sp->id < host1x_syncpt_nb_pts(sp->host);
पूर्ण

#पूर्ण_अगर
