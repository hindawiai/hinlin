<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * v4l2-event.c
 *
 * V4L2 events.
 *
 * Copyright (C) 2009--2010 Nokia Corporation.
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

अटल अचिन्हित sev_pos(स्थिर काष्ठा v4l2_subscribed_event *sev, अचिन्हित idx)
अणु
	idx += sev->first;
	वापस idx >= sev->elems ? idx - sev->elems : idx;
पूर्ण

अटल पूर्णांक __v4l2_event_dequeue(काष्ठा v4l2_fh *fh, काष्ठा v4l2_event *event)
अणु
	काष्ठा v4l2_kevent *kev;
	काष्ठा बारpec64 ts;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);

	अगर (list_empty(&fh->available)) अणु
		spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
		वापस -ENOENT;
	पूर्ण

	WARN_ON(fh->navailable == 0);

	kev = list_first_entry(&fh->available, काष्ठा v4l2_kevent, list);
	list_del(&kev->list);
	fh->navailable--;

	kev->event.pending = fh->navailable;
	*event = kev->event;
	ts = ns_to_बारpec64(kev->ts);
	event->बारtamp.tv_sec = ts.tv_sec;
	event->बारtamp.tv_nsec = ts.tv_nsec;
	kev->sev->first = sev_pos(kev->sev, 1);
	kev->sev->in_use--;

	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक v4l2_event_dequeue(काष्ठा v4l2_fh *fh, काष्ठा v4l2_event *event,
		       पूर्णांक nonblocking)
अणु
	पूर्णांक ret;

	अगर (nonblocking)
		वापस __v4l2_event_dequeue(fh, event);

	/* Release the vdev lock जबतक रुकोing */
	अगर (fh->vdev->lock)
		mutex_unlock(fh->vdev->lock);

	करो अणु
		ret = रुको_event_पूर्णांकerruptible(fh->रुको,
					       fh->navailable != 0);
		अगर (ret < 0)
			अवरोध;

		ret = __v4l2_event_dequeue(fh, event);
	पूर्ण जबतक (ret == -ENOENT);

	अगर (fh->vdev->lock)
		mutex_lock(fh->vdev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_dequeue);

/* Caller must hold fh->vdev->fh_lock! */
अटल काष्ठा v4l2_subscribed_event *v4l2_event_subscribed(
		काष्ठा v4l2_fh *fh, u32 type, u32 id)
अणु
	काष्ठा v4l2_subscribed_event *sev;

	निश्चित_spin_locked(&fh->vdev->fh_lock);

	list_क्रम_each_entry(sev, &fh->subscribed, list)
		अगर (sev->type == type && sev->id == id)
			वापस sev;

	वापस शून्य;
पूर्ण

अटल व्योम __v4l2_event_queue_fh(काष्ठा v4l2_fh *fh,
				  स्थिर काष्ठा v4l2_event *ev, u64 ts)
अणु
	काष्ठा v4l2_subscribed_event *sev;
	काष्ठा v4l2_kevent *kev;
	bool copy_payload = true;

	/* Are we subscribed? */
	sev = v4l2_event_subscribed(fh, ev->type, ev->id);
	अगर (sev == शून्य)
		वापस;

	/* Increase event sequence number on fh. */
	fh->sequence++;

	/* Do we have any मुक्त events? */
	अगर (sev->in_use == sev->elems) अणु
		/* no, हटाओ the oldest one */
		kev = sev->events + sev_pos(sev, 0);
		list_del(&kev->list);
		sev->in_use--;
		sev->first = sev_pos(sev, 1);
		fh->navailable--;
		अगर (sev->elems == 1) अणु
			अगर (sev->ops && sev->ops->replace) अणु
				sev->ops->replace(&kev->event, ev);
				copy_payload = false;
			पूर्ण
		पूर्ण अन्यथा अगर (sev->ops && sev->ops->merge) अणु
			काष्ठा v4l2_kevent *second_oldest =
				sev->events + sev_pos(sev, 0);
			sev->ops->merge(&kev->event, &second_oldest->event);
		पूर्ण
	पूर्ण

	/* Take one and fill it. */
	kev = sev->events + sev_pos(sev, sev->in_use);
	kev->event.type = ev->type;
	अगर (copy_payload)
		kev->event.u = ev->u;
	kev->event.id = ev->id;
	kev->ts = ts;
	kev->event.sequence = fh->sequence;
	sev->in_use++;
	list_add_tail(&kev->list, &fh->available);

	fh->navailable++;

	wake_up_all(&fh->रुको);
पूर्ण

व्योम v4l2_event_queue(काष्ठा video_device *vdev, स्थिर काष्ठा v4l2_event *ev)
अणु
	काष्ठा v4l2_fh *fh;
	अचिन्हित दीर्घ flags;
	u64 ts;

	अगर (vdev == शून्य)
		वापस;

	ts = kसमय_get_ns();

	spin_lock_irqsave(&vdev->fh_lock, flags);

	list_क्रम_each_entry(fh, &vdev->fh_list, list)
		__v4l2_event_queue_fh(fh, ev, ts);

	spin_unlock_irqrestore(&vdev->fh_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_queue);

व्योम v4l2_event_queue_fh(काष्ठा v4l2_fh *fh, स्थिर काष्ठा v4l2_event *ev)
अणु
	अचिन्हित दीर्घ flags;
	u64 ts = kसमय_get_ns();

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	__v4l2_event_queue_fh(fh, ev, ts);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_queue_fh);

पूर्णांक v4l2_event_pending(काष्ठा v4l2_fh *fh)
अणु
	वापस fh->navailable;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_pending);

व्योम v4l2_event_wake_all(काष्ठा video_device *vdev)
अणु
	काष्ठा v4l2_fh *fh;
	अचिन्हित दीर्घ flags;

	अगर (!vdev)
		वापस;

	spin_lock_irqsave(&vdev->fh_lock, flags);

	list_क्रम_each_entry(fh, &vdev->fh_list, list)
		wake_up_all(&fh->रुको);

	spin_unlock_irqrestore(&vdev->fh_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_wake_all);

अटल व्योम __v4l2_event_unsubscribe(काष्ठा v4l2_subscribed_event *sev)
अणु
	काष्ठा v4l2_fh *fh = sev->fh;
	अचिन्हित पूर्णांक i;

	lockdep_निश्चित_held(&fh->subscribe_lock);
	निश्चित_spin_locked(&fh->vdev->fh_lock);

	/* Remove any pending events क्रम this subscription */
	क्रम (i = 0; i < sev->in_use; i++) अणु
		list_del(&sev->events[sev_pos(sev, i)].list);
		fh->navailable--;
	पूर्ण
	list_del(&sev->list);
पूर्ण

पूर्णांक v4l2_event_subscribe(काष्ठा v4l2_fh *fh,
			 स्थिर काष्ठा v4l2_event_subscription *sub, अचिन्हित elems,
			 स्थिर काष्ठा v4l2_subscribed_event_ops *ops)
अणु
	काष्ठा v4l2_subscribed_event *sev, *found_ev;
	अचिन्हित दीर्घ flags;
	अचिन्हित i;
	पूर्णांक ret = 0;

	अगर (sub->type == V4L2_EVENT_ALL)
		वापस -EINVAL;

	अगर (elems < 1)
		elems = 1;

	sev = kvzalloc(काष्ठा_size(sev, events, elems), GFP_KERNEL);
	अगर (!sev)
		वापस -ENOMEM;
	क्रम (i = 0; i < elems; i++)
		sev->events[i].sev = sev;
	sev->type = sub->type;
	sev->id = sub->id;
	sev->flags = sub->flags;
	sev->fh = fh;
	sev->ops = ops;
	sev->elems = elems;

	mutex_lock(&fh->subscribe_lock);

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);
	found_ev = v4l2_event_subscribed(fh, sub->type, sub->id);
	अगर (!found_ev)
		list_add(&sev->list, &fh->subscribed);
	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);

	अगर (found_ev) अणु
		/* Alपढ़ोy listening */
		kvमुक्त(sev);
	पूर्ण अन्यथा अगर (sev->ops && sev->ops->add) अणु
		ret = sev->ops->add(sev, elems);
		अगर (ret) अणु
			spin_lock_irqsave(&fh->vdev->fh_lock, flags);
			__v4l2_event_unsubscribe(sev);
			spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
			kvमुक्त(sev);
		पूर्ण
	पूर्ण

	mutex_unlock(&fh->subscribe_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_subscribe);

व्योम v4l2_event_unsubscribe_all(काष्ठा v4l2_fh *fh)
अणु
	काष्ठा v4l2_event_subscription sub;
	काष्ठा v4l2_subscribed_event *sev;
	अचिन्हित दीर्घ flags;

	करो अणु
		sev = शून्य;

		spin_lock_irqsave(&fh->vdev->fh_lock, flags);
		अगर (!list_empty(&fh->subscribed)) अणु
			sev = list_first_entry(&fh->subscribed,
					काष्ठा v4l2_subscribed_event, list);
			sub.type = sev->type;
			sub.id = sev->id;
		पूर्ण
		spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);
		अगर (sev)
			v4l2_event_unsubscribe(fh, &sub);
	पूर्ण जबतक (sev);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_unsubscribe_all);

पूर्णांक v4l2_event_unsubscribe(काष्ठा v4l2_fh *fh,
			   स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	काष्ठा v4l2_subscribed_event *sev;
	अचिन्हित दीर्घ flags;

	अगर (sub->type == V4L2_EVENT_ALL) अणु
		v4l2_event_unsubscribe_all(fh);
		वापस 0;
	पूर्ण

	mutex_lock(&fh->subscribe_lock);

	spin_lock_irqsave(&fh->vdev->fh_lock, flags);

	sev = v4l2_event_subscribed(fh, sub->type, sub->id);
	अगर (sev != शून्य)
		__v4l2_event_unsubscribe(sev);

	spin_unlock_irqrestore(&fh->vdev->fh_lock, flags);

	अगर (sev && sev->ops && sev->ops->del)
		sev->ops->del(sev);

	mutex_unlock(&fh->subscribe_lock);

	kvमुक्त(sev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_unsubscribe);

पूर्णांक v4l2_event_subdev_unsubscribe(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				  काष्ठा v4l2_event_subscription *sub)
अणु
	वापस v4l2_event_unsubscribe(fh, sub);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_event_subdev_unsubscribe);

अटल व्योम v4l2_event_src_replace(काष्ठा v4l2_event *old,
				स्थिर काष्ठा v4l2_event *new)
अणु
	u32 old_changes = old->u.src_change.changes;

	old->u.src_change = new->u.src_change;
	old->u.src_change.changes |= old_changes;
पूर्ण

अटल व्योम v4l2_event_src_merge(स्थिर काष्ठा v4l2_event *old,
				काष्ठा v4l2_event *new)
अणु
	new->u.src_change.changes |= old->u.src_change.changes;
पूर्ण

अटल स्थिर काष्ठा v4l2_subscribed_event_ops v4l2_event_src_ch_ops = अणु
	.replace = v4l2_event_src_replace,
	.merge = v4l2_event_src_merge,
पूर्ण;

पूर्णांक v4l2_src_change_event_subscribe(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub)
अणु
	अगर (sub->type == V4L2_EVENT_SOURCE_CHANGE)
		वापस v4l2_event_subscribe(fh, sub, 0, &v4l2_event_src_ch_ops);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_src_change_event_subscribe);

पूर्णांक v4l2_src_change_event_subdev_subscribe(काष्ठा v4l2_subdev *sd,
		काष्ठा v4l2_fh *fh, काष्ठा v4l2_event_subscription *sub)
अणु
	वापस v4l2_src_change_event_subscribe(fh, sub);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_src_change_event_subdev_subscribe);
