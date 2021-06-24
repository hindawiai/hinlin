<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */


#समावेश "msm_drv.h"
#समावेश "mdp_kms.h"


काष्ठा mdp_irq_रुको अणु
	काष्ठा mdp_irq irq;
	पूर्णांक count;
पूर्ण;

अटल DECLARE_WAIT_QUEUE_HEAD(रुको_event);

अटल DEFINE_SPINLOCK(list_lock);

अटल व्योम update_irq(काष्ठा mdp_kms *mdp_kms)
अणु
	काष्ठा mdp_irq *irq;
	uपूर्णांक32_t irqmask = mdp_kms->vblank_mask;

	निश्चित_spin_locked(&list_lock);

	list_क्रम_each_entry(irq, &mdp_kms->irq_list, node)
		irqmask |= irq->irqmask;

	mdp_kms->funcs->set_irqmask(mdp_kms, irqmask, mdp_kms->cur_irq_mask);
	mdp_kms->cur_irq_mask = irqmask;
पूर्ण

/* अगर an mdp_irq's irqmask has changed, such as when mdp5 crtc<->encoder
 * link changes, this must be called to figure out the new global irqmask
 */
व्योम mdp_irq_update(काष्ठा mdp_kms *mdp_kms)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&list_lock, flags);
	update_irq(mdp_kms);
	spin_unlock_irqrestore(&list_lock, flags);
पूर्ण

व्योम mdp_dispatch_irqs(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t status)
अणु
	काष्ठा mdp_irq *handler, *n;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list_lock, flags);
	mdp_kms->in_irq = true;
	list_क्रम_each_entry_safe(handler, n, &mdp_kms->irq_list, node) अणु
		अगर (handler->irqmask & status) अणु
			spin_unlock_irqrestore(&list_lock, flags);
			handler->irq(handler, handler->irqmask & status);
			spin_lock_irqsave(&list_lock, flags);
		पूर्ण
	पूर्ण
	mdp_kms->in_irq = false;
	update_irq(mdp_kms);
	spin_unlock_irqrestore(&list_lock, flags);

पूर्ण

व्योम mdp_update_vblank_mask(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t mask, bool enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&list_lock, flags);
	अगर (enable)
		mdp_kms->vblank_mask |= mask;
	अन्यथा
		mdp_kms->vblank_mask &= ~mask;
	update_irq(mdp_kms);
	spin_unlock_irqrestore(&list_lock, flags);
पूर्ण

अटल व्योम रुको_irq(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp_irq_रुको *रुको =
			container_of(irq, काष्ठा mdp_irq_रुको, irq);
	रुको->count--;
	wake_up_all(&रुको_event);
पूर्ण

व्योम mdp_irq_रुको(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t irqmask)
अणु
	काष्ठा mdp_irq_रुको रुको = अणु
		.irq = अणु
			.irq = रुको_irq,
			.irqmask = irqmask,
		पूर्ण,
		.count = 1,
	पूर्ण;
	mdp_irq_रेजिस्टर(mdp_kms, &रुको.irq);
	रुको_event_समयout(रुको_event, (रुको.count <= 0),
			msecs_to_jअगरfies(100));
	mdp_irq_unरेजिस्टर(mdp_kms, &रुको.irq);
पूर्ण

व्योम mdp_irq_रेजिस्टर(काष्ठा mdp_kms *mdp_kms, काष्ठा mdp_irq *irq)
अणु
	अचिन्हित दीर्घ flags;
	bool needs_update = false;

	spin_lock_irqsave(&list_lock, flags);

	अगर (!irq->रेजिस्टरed) अणु
		irq->रेजिस्टरed = true;
		list_add(&irq->node, &mdp_kms->irq_list);
		needs_update = !mdp_kms->in_irq;
	पूर्ण

	spin_unlock_irqrestore(&list_lock, flags);

	अगर (needs_update)
		mdp_irq_update(mdp_kms);
पूर्ण

व्योम mdp_irq_unरेजिस्टर(काष्ठा mdp_kms *mdp_kms, काष्ठा mdp_irq *irq)
अणु
	अचिन्हित दीर्घ flags;
	bool needs_update = false;

	spin_lock_irqsave(&list_lock, flags);

	अगर (irq->रेजिस्टरed) अणु
		irq->रेजिस्टरed = false;
		list_del(&irq->node);
		needs_update = !mdp_kms->in_irq;
	पूर्ण

	spin_unlock_irqrestore(&list_lock, flags);

	अगर (needs_update)
		mdp_irq_update(mdp_kms);
पूर्ण
