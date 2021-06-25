<शैली गुरु>
/******************************************************************************
 * xenbus.h
 *
 * Talks to Xen Store to figure out what devices we have.
 *
 * Copyright (C) 2005 Rusty Russell, IBM Corporation
 * Copyright (C) 2005 XenSource Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित _XEN_XENBUS_H
#घोषणा _XEN_XENBUS_H

#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/semaphore.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/पूर्णांकerface/io/xenbus.h>
#समावेश <xen/पूर्णांकerface/io/xs_wire.h>
#समावेश <xen/पूर्णांकerface/event_channel.h>

#घोषणा XENBUS_MAX_RING_GRANT_ORDER 4
#घोषणा XENBUS_MAX_RING_GRANTS      (1U << XENBUS_MAX_RING_GRANT_ORDER)

/* Register callback to watch this node. */
काष्ठा xenbus_watch
अणु
	काष्ठा list_head list;

	/* Path being watched. */
	स्थिर अक्षर *node;

	अचिन्हित पूर्णांक nr_pending;

	/*
	 * Called just beक्रमe enqueing new event जबतक a spinlock is held.
	 * The event will be discarded अगर this callback वापसs false.
	 */
	bool (*will_handle)(काष्ठा xenbus_watch *,
			      स्थिर अक्षर *path, स्थिर अक्षर *token);

	/* Callback (executed in a process context with no locks held). */
	व्योम (*callback)(काष्ठा xenbus_watch *,
			 स्थिर अक्षर *path, स्थिर अक्षर *token);
पूर्ण;


/* A xenbus device. */
काष्ठा xenbus_device अणु
	स्थिर अक्षर *devicetype;
	स्थिर अक्षर *nodename;
	स्थिर अक्षर *otherend;
	पूर्णांक otherend_id;
	काष्ठा xenbus_watch otherend_watch;
	काष्ठा device dev;
	क्रमागत xenbus_state state;
	काष्ठा completion करोwn;
	काष्ठा work_काष्ठा work;
	काष्ठा semaphore reclaim_sem;

	/* Event channel based statistics and settings. */
	atomic_t event_channels;
	atomic_t events;
	atomic_t spurious_events;
	atomic_t jअगरfies_eoi_delayed;
	अचिन्हित पूर्णांक spurious_threshold;
पूर्ण;

अटल अंतरभूत काष्ठा xenbus_device *to_xenbus_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा xenbus_device, dev);
पूर्ण

काष्ठा xenbus_device_id
अणु
	/* .../device/<device_type>/<identअगरier> */
	अक्षर devicetype[32]; 	/* General class of device. */
पूर्ण;

/* A xenbus driver. */
काष्ठा xenbus_driver अणु
	स्थिर अक्षर *name;       /* शेषs to ids[0].devicetype */
	स्थिर काष्ठा xenbus_device_id *ids;
	bool allow_rebind; /* aव्योम setting xenstore बंदd during हटाओ */
	पूर्णांक (*probe)(काष्ठा xenbus_device *dev,
		     स्थिर काष्ठा xenbus_device_id *id);
	व्योम (*otherend_changed)(काष्ठा xenbus_device *dev,
				 क्रमागत xenbus_state backend_state);
	पूर्णांक (*हटाओ)(काष्ठा xenbus_device *dev);
	पूर्णांक (*suspend)(काष्ठा xenbus_device *dev);
	पूर्णांक (*resume)(काष्ठा xenbus_device *dev);
	पूर्णांक (*uevent)(काष्ठा xenbus_device *, काष्ठा kobj_uevent_env *);
	काष्ठा device_driver driver;
	पूर्णांक (*पढ़ो_otherend_details)(काष्ठा xenbus_device *dev);
	पूर्णांक (*is_पढ़ोy)(काष्ठा xenbus_device *dev);
	व्योम (*reclaim_memory)(काष्ठा xenbus_device *dev);
पूर्ण;

अटल अंतरभूत काष्ठा xenbus_driver *to_xenbus_driver(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा xenbus_driver, driver);
पूर्ण

पूर्णांक __must_check __xenbus_रेजिस्टर_frontend(काष्ठा xenbus_driver *drv,
					    काष्ठा module *owner,
					    स्थिर अक्षर *mod_name);
पूर्णांक __must_check __xenbus_रेजिस्टर_backend(काष्ठा xenbus_driver *drv,
					   काष्ठा module *owner,
					   स्थिर अक्षर *mod_name);

#घोषणा xenbus_रेजिस्टर_frontend(drv) \
	__xenbus_रेजिस्टर_frontend(drv, THIS_MODULE, KBUILD_MODNAME)
#घोषणा xenbus_रेजिस्टर_backend(drv) \
	__xenbus_रेजिस्टर_backend(drv, THIS_MODULE, KBUILD_MODNAME)

व्योम xenbus_unरेजिस्टर_driver(काष्ठा xenbus_driver *drv);

काष्ठा xenbus_transaction
अणु
	u32 id;
पूर्ण;

/* Nil transaction ID. */
#घोषणा XBT_NIL ((काष्ठा xenbus_transaction) अणु 0 पूर्ण)

अक्षर **xenbus_directory(काष्ठा xenbus_transaction t,
			स्थिर अक्षर *dir, स्थिर अक्षर *node, अचिन्हित पूर्णांक *num);
व्योम *xenbus_पढ़ो(काष्ठा xenbus_transaction t,
		  स्थिर अक्षर *dir, स्थिर अक्षर *node, अचिन्हित पूर्णांक *len);
पूर्णांक xenbus_ग_लिखो(काष्ठा xenbus_transaction t,
		 स्थिर अक्षर *dir, स्थिर अक्षर *node, स्थिर अक्षर *string);
पूर्णांक xenbus_सूची_गढ़ो(काष्ठा xenbus_transaction t,
		 स्थिर अक्षर *dir, स्थिर अक्षर *node);
पूर्णांक xenbus_exists(काष्ठा xenbus_transaction t,
		  स्थिर अक्षर *dir, स्थिर अक्षर *node);
पूर्णांक xenbus_rm(काष्ठा xenbus_transaction t, स्थिर अक्षर *dir, स्थिर अक्षर *node);
पूर्णांक xenbus_transaction_start(काष्ठा xenbus_transaction *t);
पूर्णांक xenbus_transaction_end(काष्ठा xenbus_transaction t, पूर्णांक पात);

/* Single पढ़ो and म_पूछो: वापसs -त्रुटि_सं or num scanned अगर > 0. */
__म_पूछो(4, 5)
पूर्णांक xenbus_म_पूछो(काष्ठा xenbus_transaction t,
		 स्थिर अक्षर *dir, स्थिर अक्षर *node, स्थिर अक्षर *fmt, ...);

/* Read an (optional) अचिन्हित value. */
अचिन्हित पूर्णांक xenbus_पढ़ो_अचिन्हित(स्थिर अक्षर *dir, स्थिर अक्षर *node,
				  अचिन्हित पूर्णांक शेष_val);

/* Single म_लिखो and ग_लिखो: वापसs -त्रुटि_सं or 0. */
__म_लिखो(4, 5)
पूर्णांक xenbus_म_लिखो(काष्ठा xenbus_transaction t,
		  स्थिर अक्षर *dir, स्थिर अक्षर *node, स्थिर अक्षर *fmt, ...);

/* Generic पढ़ो function: शून्य-terminated triples of name,
 * प्र_लिखो-style type string, and poपूर्णांकer. Returns 0 or त्रुटि_सं.*/
पूर्णांक xenbus_gather(काष्ठा xenbus_transaction t, स्थिर अक्षर *dir, ...);

/* notअगरer routines क्रम when the xenstore comes up */
बाह्य पूर्णांक xenstored_पढ़ोy;
पूर्णांक रेजिस्टर_xenstore_notअगरier(काष्ठा notअगरier_block *nb);
व्योम unरेजिस्टर_xenstore_notअगरier(काष्ठा notअगरier_block *nb);

पूर्णांक रेजिस्टर_xenbus_watch(काष्ठा xenbus_watch *watch);
व्योम unरेजिस्टर_xenbus_watch(काष्ठा xenbus_watch *watch);
व्योम xs_suspend(व्योम);
व्योम xs_resume(व्योम);
व्योम xs_suspend_cancel(व्योम);

काष्ठा work_काष्ठा;

#घोषणा XENBUS_IS_ERR_READ(str) (अणु			\
	अगर (!IS_ERR(str) && म_माप(str) == 0) अणु		\
		kमुक्त(str);				\
		str = ERR_PTR(-दुस्फल);			\
	पूर्ण						\
	IS_ERR(str);					\
पूर्ण)

#घोषणा XENBUS_EXIST_ERR(err) ((err) == -ENOENT || (err) == -दुस्फल)

पूर्णांक xenbus_watch_path(काष्ठा xenbus_device *dev, स्थिर अक्षर *path,
		      काष्ठा xenbus_watch *watch,
		      bool (*will_handle)(काष्ठा xenbus_watch *,
					  स्थिर अक्षर *, स्थिर अक्षर *),
		      व्योम (*callback)(काष्ठा xenbus_watch *,
				       स्थिर अक्षर *, स्थिर अक्षर *));
__म_लिखो(5, 6)
पूर्णांक xenbus_watch_pathfmt(काष्ठा xenbus_device *dev, काष्ठा xenbus_watch *watch,
			 bool (*will_handle)(काष्ठा xenbus_watch *,
					     स्थिर अक्षर *, स्थिर अक्षर *),
			 व्योम (*callback)(काष्ठा xenbus_watch *,
					  स्थिर अक्षर *, स्थिर अक्षर *),
			 स्थिर अक्षर *pathfmt, ...);

पूर्णांक xenbus_चयन_state(काष्ठा xenbus_device *dev, क्रमागत xenbus_state new_state);
पूर्णांक xenbus_grant_ring(काष्ठा xenbus_device *dev, व्योम *vaddr,
		      अचिन्हित पूर्णांक nr_pages, grant_ref_t *grefs);
पूर्णांक xenbus_map_ring_valloc(काष्ठा xenbus_device *dev, grant_ref_t *gnt_refs,
			   अचिन्हित पूर्णांक nr_grefs, व्योम **vaddr);

पूर्णांक xenbus_unmap_ring_vमुक्त(काष्ठा xenbus_device *dev, व्योम *vaddr);

पूर्णांक xenbus_alloc_evtchn(काष्ठा xenbus_device *dev, evtchn_port_t *port);
पूर्णांक xenbus_मुक्त_evtchn(काष्ठा xenbus_device *dev, evtchn_port_t port);

क्रमागत xenbus_state xenbus_पढ़ो_driver_state(स्थिर अक्षर *path);

__म_लिखो(3, 4)
व्योम xenbus_dev_error(काष्ठा xenbus_device *dev, पूर्णांक err, स्थिर अक्षर *fmt, ...);
__म_लिखो(3, 4)
व्योम xenbus_dev_fatal(काष्ठा xenbus_device *dev, पूर्णांक err, स्थिर अक्षर *fmt, ...);

स्थिर अक्षर *xenbus_strstate(क्रमागत xenbus_state state);
पूर्णांक xenbus_dev_is_online(काष्ठा xenbus_device *dev);
पूर्णांक xenbus_frontend_बंदd(काष्ठा xenbus_device *dev);

बाह्य स्थिर काष्ठा file_operations xen_xenbus_fops;
बाह्य काष्ठा xenstore_करोमुख्य_पूर्णांकerface *xen_store_पूर्णांकerface;
बाह्य पूर्णांक xen_store_evtchn;

#पूर्ण_अगर /* _XEN_XENBUS_H */
