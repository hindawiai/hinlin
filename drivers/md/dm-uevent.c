<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device Mapper Uevent Support (dm-uevent)
 *
 * Copyright IBM Corporation, 2007
 * 	Author: Mike Anderson <andmike@linux.vnet.ibm.com>
 */
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/kobject.h>
#समावेश <linux/dm-ioctl.h>
#समावेश <linux/export.h>

#समावेश "dm.h"
#समावेश "dm-uevent.h"

#घोषणा DM_MSG_PREFIX "uevent"

अटल स्थिर काष्ठा अणु
	क्रमागत dm_uevent_type type;
	क्रमागत kobject_action action;
	अक्षर *name;
पूर्ण _dm_uevent_type_names[] = अणु
	अणुDM_UEVENT_PATH_FAILED, KOBJ_CHANGE, "PATH_FAILED"पूर्ण,
	अणुDM_UEVENT_PATH_REINSTATED, KOBJ_CHANGE, "PATH_REINSTATED"पूर्ण,
पूर्ण;

अटल काष्ठा kmem_cache *_dm_event_cache;

काष्ठा dm_uevent अणु
	काष्ठा mapped_device *md;
	क्रमागत kobject_action action;
	काष्ठा kobj_uevent_env ku_env;
	काष्ठा list_head elist;
	अक्षर name[DM_NAME_LEN];
	अक्षर uuid[DM_UUID_LEN];
पूर्ण;

अटल व्योम dm_uevent_मुक्त(काष्ठा dm_uevent *event)
अणु
	kmem_cache_मुक्त(_dm_event_cache, event);
पूर्ण

अटल काष्ठा dm_uevent *dm_uevent_alloc(काष्ठा mapped_device *md)
अणु
	काष्ठा dm_uevent *event;

	event = kmem_cache_zalloc(_dm_event_cache, GFP_ATOMIC);
	अगर (!event)
		वापस शून्य;

	INIT_LIST_HEAD(&event->elist);
	event->md = md;

	वापस event;
पूर्ण

अटल काष्ठा dm_uevent *dm_build_path_uevent(काष्ठा mapped_device *md,
					      काष्ठा dm_target *ti,
					      क्रमागत kobject_action action,
					      स्थिर अक्षर *dm_action,
					      स्थिर अक्षर *path,
					      अचिन्हित nr_valid_paths)
अणु
	काष्ठा dm_uevent *event;

	event = dm_uevent_alloc(md);
	अगर (!event) अणु
		DMERR("%s: dm_uevent_alloc() failed", __func__);
		जाओ err_nomem;
	पूर्ण

	event->action = action;

	अगर (add_uevent_var(&event->ku_env, "DM_TARGET=%s", ti->type->name)) अणु
		DMERR("%s: add_uevent_var() for DM_TARGET failed",
		      __func__);
		जाओ err_add;
	पूर्ण

	अगर (add_uevent_var(&event->ku_env, "DM_ACTION=%s", dm_action)) अणु
		DMERR("%s: add_uevent_var() for DM_ACTION failed",
		      __func__);
		जाओ err_add;
	पूर्ण

	अगर (add_uevent_var(&event->ku_env, "DM_SEQNUM=%u",
			   dm_next_uevent_seq(md))) अणु
		DMERR("%s: add_uevent_var() for DM_SEQNUM failed",
		      __func__);
		जाओ err_add;
	पूर्ण

	अगर (add_uevent_var(&event->ku_env, "DM_PATH=%s", path)) अणु
		DMERR("%s: add_uevent_var() for DM_PATH failed", __func__);
		जाओ err_add;
	पूर्ण

	अगर (add_uevent_var(&event->ku_env, "DM_NR_VALID_PATHS=%d",
			   nr_valid_paths)) अणु
		DMERR("%s: add_uevent_var() for DM_NR_VALID_PATHS failed",
		      __func__);
		जाओ err_add;
	पूर्ण

	वापस event;

err_add:
	dm_uevent_मुक्त(event);
err_nomem:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * dm_send_uevents - send uevents क्रम given list
 *
 * @events:	list of events to send
 * @kobj:	kobject generating event
 *
 */
व्योम dm_send_uevents(काष्ठा list_head *events, काष्ठा kobject *kobj)
अणु
	पूर्णांक r;
	काष्ठा dm_uevent *event, *next;

	list_क्रम_each_entry_safe(event, next, events, elist) अणु
		list_del_init(&event->elist);

		/*
		 * When a device is being हटाओd this copy fails and we
		 * discard these unsent events.
		 */
		अगर (dm_copy_name_and_uuid(event->md, event->name,
					  event->uuid)) अणु
			DMINFO("%s: skipping sending uevent for lost device",
			       __func__);
			जाओ uevent_मुक्त;
		पूर्ण

		अगर (add_uevent_var(&event->ku_env, "DM_NAME=%s", event->name)) अणु
			DMERR("%s: add_uevent_var() for DM_NAME failed",
			      __func__);
			जाओ uevent_मुक्त;
		पूर्ण

		अगर (add_uevent_var(&event->ku_env, "DM_UUID=%s", event->uuid)) अणु
			DMERR("%s: add_uevent_var() for DM_UUID failed",
			      __func__);
			जाओ uevent_मुक्त;
		पूर्ण

		r = kobject_uevent_env(kobj, event->action, event->ku_env.envp);
		अगर (r)
			DMERR("%s: kobject_uevent_env failed", __func__);
uevent_मुक्त:
		dm_uevent_मुक्त(event);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dm_send_uevents);

/**
 * dm_path_uevent - called to create a new path event and queue it
 *
 * @event_type:	path event type क्रमागत
 * @ti:			poपूर्णांकer to a dm_target
 * @path:		string containing pathname
 * @nr_valid_paths:	number of valid paths reमुख्यing
 *
 */
व्योम dm_path_uevent(क्रमागत dm_uevent_type event_type, काष्ठा dm_target *ti,
		   स्थिर अक्षर *path, अचिन्हित nr_valid_paths)
अणु
	काष्ठा mapped_device *md = dm_table_get_md(ti->table);
	काष्ठा dm_uevent *event;

	अगर (event_type >= ARRAY_SIZE(_dm_uevent_type_names)) अणु
		DMERR("%s: Invalid event_type %d", __func__, event_type);
		वापस;
	पूर्ण

	event = dm_build_path_uevent(md, ti,
				     _dm_uevent_type_names[event_type].action,
				     _dm_uevent_type_names[event_type].name,
				     path, nr_valid_paths);
	अगर (IS_ERR(event))
		वापस;

	dm_uevent_add(md, &event->elist);
पूर्ण
EXPORT_SYMBOL_GPL(dm_path_uevent);

पूर्णांक dm_uevent_init(व्योम)
अणु
	_dm_event_cache = KMEM_CACHE(dm_uevent, 0);
	अगर (!_dm_event_cache)
		वापस -ENOMEM;

	DMINFO("version 1.0.3");

	वापस 0;
पूर्ण

व्योम dm_uevent_निकास(व्योम)
अणु
	kmem_cache_destroy(_dm_event_cache);
पूर्ण
