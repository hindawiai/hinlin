<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Floating proportions with flexible aging period
 *
 *  Copyright (C) 2011, SUSE, Jan Kara <jack@suse.cz>
 */

#अगर_अघोषित _LINUX_FLEX_PROPORTIONS_H
#घोषणा _LINUX_FLEX_PROPORTIONS_H

#समावेश <linux/percpu_counter.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/gfp.h>

/*
 * When maximum proportion of some event type is specअगरied, this is the
 * precision with which we allow limitting. Note that this creates an upper
 * bound on the number of events per period like
 *   ULदीर्घ_उच्च >> FPROP_FRAC_SHIFT.
 */
#घोषणा FPROP_FRAC_SHIFT 10
#घोषणा FPROP_FRAC_BASE (1UL << FPROP_FRAC_SHIFT)

/*
 * ---- Global proportion definitions ----
 */
काष्ठा fprop_global अणु
	/* Number of events in the current period */
	काष्ठा percpu_counter events;
	/* Current period */
	अचिन्हित पूर्णांक period;
	/* Synchronization with period transitions */
	seqcount_t sequence;
पूर्ण;

पूर्णांक fprop_global_init(काष्ठा fprop_global *p, gfp_t gfp);
व्योम fprop_global_destroy(काष्ठा fprop_global *p);
bool fprop_new_period(काष्ठा fprop_global *p, पूर्णांक periods);

/*
 *  ---- SINGLE ----
 */
काष्ठा fprop_local_single अणु
	/* the local events counter */
	अचिन्हित दीर्घ events;
	/* Period in which we last updated events */
	अचिन्हित पूर्णांक period;
	raw_spinlock_t lock;	/* Protect period and numerator */
पूर्ण;

#घोषणा INIT_FPROP_LOCAL_SINGLE(name)			\
अणु	.lock = __RAW_SPIN_LOCK_UNLOCKED(name.lock),	\
पूर्ण

पूर्णांक fprop_local_init_single(काष्ठा fprop_local_single *pl);
व्योम fprop_local_destroy_single(काष्ठा fprop_local_single *pl);
व्योम __fprop_inc_single(काष्ठा fprop_global *p, काष्ठा fprop_local_single *pl);
व्योम fprop_fraction_single(काष्ठा fprop_global *p,
	काष्ठा fprop_local_single *pl, अचिन्हित दीर्घ *numerator,
	अचिन्हित दीर्घ *denominator);

अटल अंतरभूत
व्योम fprop_inc_single(काष्ठा fprop_global *p, काष्ठा fprop_local_single *pl)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__fprop_inc_single(p, pl);
	local_irq_restore(flags);
पूर्ण

/*
 * ---- PERCPU ----
 */
काष्ठा fprop_local_percpu अणु
	/* the local events counter */
	काष्ठा percpu_counter events;
	/* Period in which we last updated events */
	अचिन्हित पूर्णांक period;
	raw_spinlock_t lock;	/* Protect period and numerator */
पूर्ण;

पूर्णांक fprop_local_init_percpu(काष्ठा fprop_local_percpu *pl, gfp_t gfp);
व्योम fprop_local_destroy_percpu(काष्ठा fprop_local_percpu *pl);
व्योम __fprop_inc_percpu(काष्ठा fprop_global *p, काष्ठा fprop_local_percpu *pl);
व्योम __fprop_inc_percpu_max(काष्ठा fprop_global *p, काष्ठा fprop_local_percpu *pl,
			    पूर्णांक max_frac);
व्योम fprop_fraction_percpu(काष्ठा fprop_global *p,
	काष्ठा fprop_local_percpu *pl, अचिन्हित दीर्घ *numerator,
	अचिन्हित दीर्घ *denominator);

अटल अंतरभूत
व्योम fprop_inc_percpu(काष्ठा fprop_global *p, काष्ठा fprop_local_percpu *pl)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__fprop_inc_percpu(p, pl);
	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर
