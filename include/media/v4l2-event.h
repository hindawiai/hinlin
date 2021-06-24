<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * v4l2-event.h
 *
 * V4L2 events.
 *
 * Copyright (C) 2009--2010 Nokia Corporation.
 *
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित V4L2_EVENT_H
#घोषणा V4L2_EVENT_H

#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/रुको.h>

काष्ठा v4l2_fh;
काष्ठा v4l2_subdev;
काष्ठा v4l2_subscribed_event;
काष्ठा video_device;

/**
 * काष्ठा v4l2_kevent - Internal kernel event काष्ठा.
 * @list:	List node क्रम the v4l2_fh->available list.
 * @sev:	Poपूर्णांकer to parent v4l2_subscribed_event.
 * @event:	The event itself.
 * @ts:		The बारtamp of the event.
 */
काष्ठा v4l2_kevent अणु
	काष्ठा list_head	list;
	काष्ठा v4l2_subscribed_event *sev;
	काष्ठा v4l2_event	event;
	u64			ts;
पूर्ण;

/**
 * काष्ठा v4l2_subscribed_event_ops - Subscribed event operations.
 *
 * @add:	Optional callback, called when a new listener is added
 * @del:	Optional callback, called when a listener stops listening
 * @replace:	Optional callback that can replace event 'old' with event 'new'.
 * @merge:	Optional callback that can merge event 'old' into event 'new'.
 */
काष्ठा v4l2_subscribed_event_ops अणु
	पूर्णांक  (*add)(काष्ठा v4l2_subscribed_event *sev, अचिन्हित पूर्णांक elems);
	व्योम (*del)(काष्ठा v4l2_subscribed_event *sev);
	व्योम (*replace)(काष्ठा v4l2_event *old, स्थिर काष्ठा v4l2_event *new);
	व्योम (*merge)(स्थिर काष्ठा v4l2_event *old, काष्ठा v4l2_event *new);
पूर्ण;

/**
 * काष्ठा v4l2_subscribed_event - Internal काष्ठा representing a subscribed
 *		event.
 *
 * @list:	List node क्रम the v4l2_fh->subscribed list.
 * @type:	Event type.
 * @id:	Associated object ID (e.g. control ID). 0 अगर there isn't any.
 * @flags:	Copy of v4l2_event_subscription->flags.
 * @fh:	Filehandle that subscribed to this event.
 * @node:	List node that hooks पूर्णांकo the object's event list
 *		(अगर there is one).
 * @ops:	v4l2_subscribed_event_ops
 * @elems:	The number of elements in the events array.
 * @first:	The index of the events containing the oldest available event.
 * @in_use:	The number of queued events.
 * @events:	An array of @elems events.
 */
काष्ठा v4l2_subscribed_event अणु
	काष्ठा list_head	list;
	u32			type;
	u32			id;
	u32			flags;
	काष्ठा v4l2_fh		*fh;
	काष्ठा list_head	node;
	स्थिर काष्ठा v4l2_subscribed_event_ops *ops;
	अचिन्हित पूर्णांक		elems;
	अचिन्हित पूर्णांक		first;
	अचिन्हित पूर्णांक		in_use;
	काष्ठा v4l2_kevent	events[];
पूर्ण;

/**
 * v4l2_event_dequeue - Dequeue events from video device.
 *
 * @fh: poपूर्णांकer to काष्ठा v4l2_fh
 * @event: poपूर्णांकer to काष्ठा v4l2_event
 * @nonblocking: अगर not zero, रुकोs क्रम an event to arrive
 */
पूर्णांक v4l2_event_dequeue(काष्ठा v4l2_fh *fh, काष्ठा v4l2_event *event,
		       पूर्णांक nonblocking);

/**
 * v4l2_event_queue - Queue events to video device.
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 * @ev: poपूर्णांकer to &काष्ठा v4l2_event
 *
 * The event will be queued क्रम all &काष्ठा v4l2_fh file handlers.
 *
 * .. note::
 *    The driver's only responsibility is to fill in the type and the data
 *    fields. The other fields will be filled in by V4L2.
 */
व्योम v4l2_event_queue(काष्ठा video_device *vdev, स्थिर काष्ठा v4l2_event *ev);

/**
 * v4l2_event_queue_fh - Queue events to video device.
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @ev: poपूर्णांकer to &काष्ठा v4l2_event
 *
 *
 * The event will be queued only क्रम the specअगरied &काष्ठा v4l2_fh file handler.
 *
 * .. note::
 *    The driver's only responsibility is to fill in the type and the data
 *    fields. The other fields will be filled in by V4L2.
 */
व्योम v4l2_event_queue_fh(काष्ठा v4l2_fh *fh, स्थिर काष्ठा v4l2_event *ev);

/**
 * v4l2_event_wake_all - Wake all filehandles.
 *
 * Used when unरेजिस्टरing a video device.
 *
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 */
व्योम v4l2_event_wake_all(काष्ठा video_device *vdev);

/**
 * v4l2_event_pending - Check अगर an event is available
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 *
 * Returns the number of pending events.
 */
पूर्णांक v4l2_event_pending(काष्ठा v4l2_fh *fh);

/**
 * v4l2_event_subscribe - Subscribes to an event
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @sub: poपूर्णांकer to &काष्ठा v4l2_event_subscription
 * @elems: size of the events queue
 * @ops: poपूर्णांकer to &v4l2_subscribed_event_ops
 *
 * .. note::
 *
 *    अगर @elems is zero, the framework will fill in a शेष value,
 *    with is currently 1 element.
 */
पूर्णांक v4l2_event_subscribe(काष्ठा v4l2_fh *fh,
			 स्थिर काष्ठा v4l2_event_subscription *sub,
			 अचिन्हित पूर्णांक elems,
			 स्थिर काष्ठा v4l2_subscribed_event_ops *ops);
/**
 * v4l2_event_unsubscribe - Unsubscribes to an event
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @sub: poपूर्णांकer to &काष्ठा v4l2_event_subscription
 */
पूर्णांक v4l2_event_unsubscribe(काष्ठा v4l2_fh *fh,
			   स्थिर काष्ठा v4l2_event_subscription *sub);
/**
 * v4l2_event_unsubscribe_all - Unsubscribes to all events
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 */
व्योम v4l2_event_unsubscribe_all(काष्ठा v4l2_fh *fh);

/**
 * v4l2_event_subdev_unsubscribe - Subdev variant of v4l2_event_unsubscribe()
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @sub: poपूर्णांकer to &काष्ठा v4l2_event_subscription
 *
 * .. note::
 *
 *	This function should be used क्रम the &काष्ठा v4l2_subdev_core_ops
 *	%unsubscribe_event field.
 */
पूर्णांक v4l2_event_subdev_unsubscribe(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_fh *fh,
				  काष्ठा v4l2_event_subscription *sub);
/**
 * v4l2_src_change_event_subscribe - helper function that calls
 *	v4l2_event_subscribe() अगर the event is %V4L2_EVENT_SOURCE_CHANGE.
 *
 * @fh: poपूर्णांकer to काष्ठा v4l2_fh
 * @sub: poपूर्णांकer to &काष्ठा v4l2_event_subscription
 */
पूर्णांक v4l2_src_change_event_subscribe(काष्ठा v4l2_fh *fh,
				    स्थिर काष्ठा v4l2_event_subscription *sub);
/**
 * v4l2_src_change_event_subdev_subscribe - Variant of v4l2_event_subscribe(),
 *	meant to subscribe only events of the type %V4L2_EVENT_SOURCE_CHANGE.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @sub: poपूर्णांकer to &काष्ठा v4l2_event_subscription
 */
पूर्णांक v4l2_src_change_event_subdev_subscribe(काष्ठा v4l2_subdev *sd,
					   काष्ठा v4l2_fh *fh,
					   काष्ठा v4l2_event_subscription *sub);
#पूर्ण_अगर /* V4L2_EVENT_H */
