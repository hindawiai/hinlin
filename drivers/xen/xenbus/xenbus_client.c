<शैली गुरु>
/******************************************************************************
 * Client-facing पूर्णांकerface क्रम the Xenbus driver.  In other words, the
 * पूर्णांकerface between the Xenbus and the device-specअगरic code, be it the
 * frontend or the backend of that driver.
 *
 * Copyright (C) 2005 XenSource Ltd
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

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/event_channel.h>
#समावेश <xen/balloon.h>
#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/xen.h>
#समावेश <xen/features.h>

#समावेश "xenbus.h"

#घोषणा XENBUS_PAGES(_grants)	(DIV_ROUND_UP(_grants, XEN_PFN_PER_PAGE))

#घोषणा XENBUS_MAX_RING_PAGES	(XENBUS_PAGES(XENBUS_MAX_RING_GRANTS))

काष्ठा xenbus_map_node अणु
	काष्ठा list_head next;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा vm_काष्ठा *area;
		पूर्ण pv;
		काष्ठा अणु
			काष्ठा page *pages[XENBUS_MAX_RING_PAGES];
			अचिन्हित दीर्घ addrs[XENBUS_MAX_RING_GRANTS];
			व्योम *addr;
		पूर्ण hvm;
	पूर्ण;
	grant_handle_t handles[XENBUS_MAX_RING_GRANTS];
	अचिन्हित पूर्णांक   nr_handles;
पूर्ण;

काष्ठा map_ring_valloc अणु
	काष्ठा xenbus_map_node *node;

	/* Why करो we need two arrays? See comment of __xenbus_map_ring */
	अचिन्हित दीर्घ addrs[XENBUS_MAX_RING_GRANTS];
	phys_addr_t phys_addrs[XENBUS_MAX_RING_GRANTS];

	काष्ठा gnttab_map_grant_ref map[XENBUS_MAX_RING_GRANTS];
	काष्ठा gnttab_unmap_grant_ref unmap[XENBUS_MAX_RING_GRANTS];

	अचिन्हित पूर्णांक idx;
पूर्ण;

अटल DEFINE_SPINLOCK(xenbus_valloc_lock);
अटल LIST_HEAD(xenbus_valloc_pages);

काष्ठा xenbus_ring_ops अणु
	पूर्णांक (*map)(काष्ठा xenbus_device *dev, काष्ठा map_ring_valloc *info,
		   grant_ref_t *gnt_refs, अचिन्हित पूर्णांक nr_grefs,
		   व्योम **vaddr);
	पूर्णांक (*unmap)(काष्ठा xenbus_device *dev, व्योम *vaddr);
पूर्ण;

अटल स्थिर काष्ठा xenbus_ring_ops *ring_ops __पढ़ो_mostly;

स्थिर अक्षर *xenbus_strstate(क्रमागत xenbus_state state)
अणु
	अटल स्थिर अक्षर *स्थिर name[] = अणु
		[ XenbusStateUnknown      ] = "Unknown",
		[ XenbusStateInitialising ] = "Initialising",
		[ XenbusStateInitWait     ] = "InitWait",
		[ XenbusStateInitialised  ] = "Initialised",
		[ XenbusStateConnected    ] = "Connected",
		[ XenbusStateClosing      ] = "Closing",
		[ XenbusStateClosed	  ] = "Closed",
		[XenbusStateReconfiguring] = "Reconfiguring",
		[XenbusStateReconfigured] = "Reconfigured",
	पूर्ण;
	वापस (state < ARRAY_SIZE(name)) ? name[state] : "INVALID";
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_strstate);

/**
 * xenbus_watch_path - रेजिस्टर a watch
 * @dev: xenbus device
 * @path: path to watch
 * @watch: watch to रेजिस्टर
 * @callback: callback to रेजिस्टर
 *
 * Register a @watch on the given path, using the given xenbus_watch काष्ठाure
 * क्रम storage, and the given @callback function as the callback.  Return 0 on
 * success, or -त्रुटि_सं on error.  On success, the given @path will be saved as
 * @watch->node, and reमुख्यs the caller's to मुक्त.  On error, @watch->node will
 * be शून्य, the device will चयन to %XenbusStateClosing, and the error will
 * be saved in the store.
 */
पूर्णांक xenbus_watch_path(काष्ठा xenbus_device *dev, स्थिर अक्षर *path,
		      काष्ठा xenbus_watch *watch,
		      bool (*will_handle)(काष्ठा xenbus_watch *,
					  स्थिर अक्षर *, स्थिर अक्षर *),
		      व्योम (*callback)(काष्ठा xenbus_watch *,
				       स्थिर अक्षर *, स्थिर अक्षर *))
अणु
	पूर्णांक err;

	watch->node = path;
	watch->will_handle = will_handle;
	watch->callback = callback;

	err = रेजिस्टर_xenbus_watch(watch);

	अगर (err) अणु
		watch->node = शून्य;
		watch->will_handle = शून्य;
		watch->callback = शून्य;
		xenbus_dev_fatal(dev, err, "adding watch on %s", path);
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_watch_path);


/**
 * xenbus_watch_pathfmt - रेजिस्टर a watch on a प्र_लिखो-क्रमmatted path
 * @dev: xenbus device
 * @watch: watch to रेजिस्टर
 * @callback: callback to रेजिस्टर
 * @pathfmt: क्रमmat of path to watch
 *
 * Register a watch on the given @path, using the given xenbus_watch
 * काष्ठाure क्रम storage, and the given @callback function as the callback.
 * Return 0 on success, or -त्रुटि_सं on error.  On success, the watched path
 * (@path/@path2) will be saved as @watch->node, and becomes the caller's to
 * kमुक्त().  On error, watch->node will be शून्य, so the caller has nothing to
 * मुक्त, the device will चयन to %XenbusStateClosing, and the error will be
 * saved in the store.
 */
पूर्णांक xenbus_watch_pathfmt(काष्ठा xenbus_device *dev,
			 काष्ठा xenbus_watch *watch,
			 bool (*will_handle)(काष्ठा xenbus_watch *,
					स्थिर अक्षर *, स्थिर अक्षर *),
			 व्योम (*callback)(काष्ठा xenbus_watch *,
					  स्थिर अक्षर *, स्थिर अक्षर *),
			 स्थिर अक्षर *pathfmt, ...)
अणु
	पूर्णांक err;
	बहु_सूची ap;
	अक्षर *path;

	बहु_शुरू(ap, pathfmt);
	path = kvaप्र_लिखो(GFP_NOIO | __GFP_HIGH, pathfmt, ap);
	बहु_पूर्ण(ap);

	अगर (!path) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating path for watch");
		वापस -ENOMEM;
	पूर्ण
	err = xenbus_watch_path(dev, path, watch, will_handle, callback);

	अगर (err)
		kमुक्त(path);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_watch_pathfmt);

अटल व्योम xenbus_चयन_fatal(काष्ठा xenbus_device *, पूर्णांक, पूर्णांक,
				स्थिर अक्षर *, ...);

अटल पूर्णांक
__xenbus_चयन_state(काष्ठा xenbus_device *dev,
		      क्रमागत xenbus_state state, पूर्णांक depth)
अणु
	/* We check whether the state is currently set to the given value, and
	   अगर not, then the state is set.  We करोn't want to unconditionally
	   ग_लिखो the given state, because we करोn't want to fire watches
	   unnecessarily.  Furthermore, अगर the node has gone, we करोn't ग_लिखो
	   to it, as the device will be tearing करोwn, and we करोn't want to
	   resurrect that directory.

	   Note that, because of this cached value of our state, this
	   function will not take a caller's Xenstore transaction
	   (something it was trying to in the past) because dev->state
	   would not get reset अगर the transaction was पातed.
	 */

	काष्ठा xenbus_transaction xbt;
	पूर्णांक current_state;
	पूर्णांक err, पात;

	अगर (state == dev->state)
		वापस 0;

again:
	पात = 1;

	err = xenbus_transaction_start(&xbt);
	अगर (err) अणु
		xenbus_चयन_fatal(dev, depth, err, "starting transaction");
		वापस 0;
	पूर्ण

	err = xenbus_म_पूछो(xbt, dev->nodename, "state", "%d", &current_state);
	अगर (err != 1)
		जाओ पात;

	err = xenbus_म_लिखो(xbt, dev->nodename, "state", "%d", state);
	अगर (err) अणु
		xenbus_चयन_fatal(dev, depth, err, "writing new state");
		जाओ पात;
	पूर्ण

	पात = 0;
पात:
	err = xenbus_transaction_end(xbt, पात);
	अगर (err) अणु
		अगर (err == -EAGAIN && !पात)
			जाओ again;
		xenbus_चयन_fatal(dev, depth, err, "ending transaction");
	पूर्ण अन्यथा
		dev->state = state;

	वापस 0;
पूर्ण

/**
 * xenbus_चयन_state
 * @dev: xenbus device
 * @state: new state
 *
 * Advertise in the store a change of the given driver to the given new_state.
 * Return 0 on success, or -त्रुटि_सं on error.  On error, the device will चयन
 * to XenbusStateClosing, and the error will be saved in the store.
 */
पूर्णांक xenbus_चयन_state(काष्ठा xenbus_device *dev, क्रमागत xenbus_state state)
अणु
	वापस __xenbus_चयन_state(dev, state, 0);
पूर्ण

EXPORT_SYMBOL_GPL(xenbus_चयन_state);

पूर्णांक xenbus_frontend_बंदd(काष्ठा xenbus_device *dev)
अणु
	xenbus_चयन_state(dev, XenbusStateClosed);
	complete(&dev->करोwn);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_frontend_बंदd);

अटल व्योम xenbus_va_dev_error(काष्ठा xenbus_device *dev, पूर्णांक err,
				स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	अचिन्हित पूर्णांक len;
	अक्षर *म_लिखो_buffer;
	अक्षर *path_buffer;

#घोषणा PRINTF_BUFFER_SIZE 4096

	म_लिखो_buffer = kदो_स्मृति(PRINTF_BUFFER_SIZE, GFP_KERNEL);
	अगर (!म_लिखो_buffer)
		वापस;

	len = प्र_लिखो(म_लिखो_buffer, "%i ", -err);
	vsnम_लिखो(म_लिखो_buffer + len, PRINTF_BUFFER_SIZE - len, fmt, ap);

	dev_err(&dev->dev, "%s\n", म_लिखो_buffer);

	path_buffer = kaप्र_लिखो(GFP_KERNEL, "error/%s", dev->nodename);
	अगर (path_buffer)
		xenbus_ग_लिखो(XBT_NIL, path_buffer, "error", म_लिखो_buffer);

	kमुक्त(म_लिखो_buffer);
	kमुक्त(path_buffer);
पूर्ण

/**
 * xenbus_dev_error
 * @dev: xenbus device
 * @err: error to report
 * @fmt: error message क्रमmat
 *
 * Report the given negative त्रुटि_सं पूर्णांकo the store, aदीर्घ with the given
 * क्रमmatted message.
 */
व्योम xenbus_dev_error(काष्ठा xenbus_device *dev, पूर्णांक err, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	xenbus_va_dev_error(dev, err, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_error);

/**
 * xenbus_dev_fatal
 * @dev: xenbus device
 * @err: error to report
 * @fmt: error message क्रमmat
 *
 * Equivalent to xenbus_dev_error(dev, err, fmt, args), followed by
 * xenbus_चयन_state(dev, XenbusStateClosing) to schedule an orderly
 * बंदकरोwn of this driver and its peer.
 */

व्योम xenbus_dev_fatal(काष्ठा xenbus_device *dev, पूर्णांक err, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	xenbus_va_dev_error(dev, err, fmt, ap);
	बहु_पूर्ण(ap);

	xenbus_चयन_state(dev, XenbusStateClosing);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_dev_fatal);

/**
 * Equivalent to xenbus_dev_fatal(dev, err, fmt, args), but helps
 * aव्योमing recursion within xenbus_चयन_state.
 */
अटल व्योम xenbus_चयन_fatal(काष्ठा xenbus_device *dev, पूर्णांक depth, पूर्णांक err,
				स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	xenbus_va_dev_error(dev, err, fmt, ap);
	बहु_पूर्ण(ap);

	अगर (!depth)
		__xenbus_चयन_state(dev, XenbusStateClosing, 1);
पूर्ण

/**
 * xenbus_grant_ring
 * @dev: xenbus device
 * @vaddr: starting भव address of the ring
 * @nr_pages: number of pages to be granted
 * @grefs: grant reference array to be filled in
 *
 * Grant access to the given @vaddr to the peer of the given device.
 * Then fill in @grefs with grant references.  Return 0 on success, or
 * -त्रुटि_सं on error.  On error, the device will चयन to
 * XenbusStateClosing, and the error will be saved in the store.
 */
पूर्णांक xenbus_grant_ring(काष्ठा xenbus_device *dev, व्योम *vaddr,
		      अचिन्हित पूर्णांक nr_pages, grant_ref_t *grefs)
अणु
	पूर्णांक err;
	पूर्णांक i, j;

	क्रम (i = 0; i < nr_pages; i++) अणु
		अचिन्हित दीर्घ gfn;

		अगर (is_vदो_स्मृति_addr(vaddr))
			gfn = pfn_to_gfn(vदो_स्मृति_to_pfn(vaddr));
		अन्यथा
			gfn = virt_to_gfn(vaddr);

		err = gnttab_grant_क्रमeign_access(dev->otherend_id, gfn, 0);
		अगर (err < 0) अणु
			xenbus_dev_fatal(dev, err,
					 "granting access to ring page");
			जाओ fail;
		पूर्ण
		grefs[i] = err;

		vaddr = vaddr + XEN_PAGE_SIZE;
	पूर्ण

	वापस 0;

fail:
	क्रम (j = 0; j < i; j++)
		gnttab_end_क्रमeign_access_ref(grefs[j], 0);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_grant_ring);


/**
 * Allocate an event channel क्रम the given xenbus_device, assigning the newly
 * created local port to *port.  Return 0 on success, or -त्रुटि_सं on error.  On
 * error, the device will चयन to XenbusStateClosing, and the error will be
 * saved in the store.
 */
पूर्णांक xenbus_alloc_evtchn(काष्ठा xenbus_device *dev, evtchn_port_t *port)
अणु
	काष्ठा evtchn_alloc_unbound alloc_unbound;
	पूर्णांक err;

	alloc_unbound.करोm = DOMID_SELF;
	alloc_unbound.remote_करोm = dev->otherend_id;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound,
					  &alloc_unbound);
	अगर (err)
		xenbus_dev_fatal(dev, err, "allocating event channel");
	अन्यथा
		*port = alloc_unbound.port;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_alloc_evtchn);


/**
 * Free an existing event channel. Returns 0 on success or -त्रुटि_सं on error.
 */
पूर्णांक xenbus_मुक्त_evtchn(काष्ठा xenbus_device *dev, evtchn_port_t port)
अणु
	काष्ठा evtchn_बंद बंद;
	पूर्णांक err;

	बंद.port = port;

	err = HYPERVISOR_event_channel_op(EVTCHNOP_बंद, &बंद);
	अगर (err)
		xenbus_dev_error(dev, err, "freeing event channel %u", port);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_मुक्त_evtchn);


/**
 * xenbus_map_ring_valloc
 * @dev: xenbus device
 * @gnt_refs: grant reference array
 * @nr_grefs: number of grant references
 * @vaddr: poपूर्णांकer to address to be filled out by mapping
 *
 * Map @nr_grefs pages of memory पूर्णांकo this करोमुख्य from another
 * करोमुख्य's grant table.  xenbus_map_ring_valloc allocates @nr_grefs
 * pages of भव address space, maps the pages to that address, and
 * sets *vaddr to that address.  Returns 0 on success, and -त्रुटि_सं on
 * error. If an error is वापसed, device will चयन to
 * XenbusStateClosing and the error message will be saved in XenStore.
 */
पूर्णांक xenbus_map_ring_valloc(काष्ठा xenbus_device *dev, grant_ref_t *gnt_refs,
			   अचिन्हित पूर्णांक nr_grefs, व्योम **vaddr)
अणु
	पूर्णांक err;
	काष्ठा map_ring_valloc *info;

	*vaddr = शून्य;

	अगर (nr_grefs > XENBUS_MAX_RING_GRANTS)
		वापस -EINVAL;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->node = kzalloc(माप(*info->node), GFP_KERNEL);
	अगर (!info->node)
		err = -ENOMEM;
	अन्यथा
		err = ring_ops->map(dev, info, gnt_refs, nr_grefs, vaddr);

	kमुक्त(info->node);
	kमुक्त(info);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_map_ring_valloc);

/* N.B. माप(phys_addr_t) करोesn't always equal to माप(अचिन्हित
 * दीर्घ), e.g. 32-on-64.  Caller is responsible क्रम preparing the
 * right array to feed पूर्णांकo this function */
अटल पूर्णांक __xenbus_map_ring(काष्ठा xenbus_device *dev,
			     grant_ref_t *gnt_refs,
			     अचिन्हित पूर्णांक nr_grefs,
			     grant_handle_t *handles,
			     काष्ठा map_ring_valloc *info,
			     अचिन्हित पूर्णांक flags,
			     bool *leaked)
अणु
	पूर्णांक i, j;

	अगर (nr_grefs > XENBUS_MAX_RING_GRANTS)
		वापस -EINVAL;

	क्रम (i = 0; i < nr_grefs; i++) अणु
		gnttab_set_map_op(&info->map[i], info->phys_addrs[i], flags,
				  gnt_refs[i], dev->otherend_id);
		handles[i] = INVALID_GRANT_HANDLE;
	पूर्ण

	gnttab_batch_map(info->map, i);

	क्रम (i = 0; i < nr_grefs; i++) अणु
		अगर (info->map[i].status != GNTST_okay) अणु
			xenbus_dev_fatal(dev, info->map[i].status,
					 "mapping in shared page %d from domain %d",
					 gnt_refs[i], dev->otherend_id);
			जाओ fail;
		पूर्ण अन्यथा
			handles[i] = info->map[i].handle;
	पूर्ण

	वापस 0;

 fail:
	क्रम (i = j = 0; i < nr_grefs; i++) अणु
		अगर (handles[i] != INVALID_GRANT_HANDLE) अणु
			gnttab_set_unmap_op(&info->unmap[j],
					    info->phys_addrs[i],
					    GNTMAP_host_map, handles[i]);
			j++;
		पूर्ण
	पूर्ण

	अगर (HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref, info->unmap, j))
		BUG();

	*leaked = false;
	क्रम (i = 0; i < j; i++) अणु
		अगर (info->unmap[i].status != GNTST_okay) अणु
			*leaked = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * xenbus_unmap_ring
 * @dev: xenbus device
 * @handles: grant handle array
 * @nr_handles: number of handles in the array
 * @vaddrs: addresses to unmap
 *
 * Unmap memory in this करोमुख्य that was imported from another करोमुख्य.
 * Returns 0 on success and वापसs GNTST_* on error
 * (see xen/include/पूर्णांकerface/grant_table.h).
 */
अटल पूर्णांक xenbus_unmap_ring(काष्ठा xenbus_device *dev, grant_handle_t *handles,
			     अचिन्हित पूर्णांक nr_handles, अचिन्हित दीर्घ *vaddrs)
अणु
	काष्ठा gnttab_unmap_grant_ref unmap[XENBUS_MAX_RING_GRANTS];
	पूर्णांक i;
	पूर्णांक err;

	अगर (nr_handles > XENBUS_MAX_RING_GRANTS)
		वापस -EINVAL;

	क्रम (i = 0; i < nr_handles; i++)
		gnttab_set_unmap_op(&unmap[i], vaddrs[i],
				    GNTMAP_host_map, handles[i]);

	अगर (HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref, unmap, i))
		BUG();

	err = GNTST_okay;
	क्रम (i = 0; i < nr_handles; i++) अणु
		अगर (unmap[i].status != GNTST_okay) अणु
			xenbus_dev_error(dev, unmap[i].status,
					 "unmapping page at handle %d error %d",
					 handles[i], unmap[i].status);
			err = unmap[i].status;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम xenbus_map_ring_setup_grant_hvm(अचिन्हित दीर्घ gfn,
					    अचिन्हित पूर्णांक goffset,
					    अचिन्हित पूर्णांक len,
					    व्योम *data)
अणु
	काष्ठा map_ring_valloc *info = data;
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)gfn_to_virt(gfn);

	info->phys_addrs[info->idx] = vaddr;
	info->addrs[info->idx] = vaddr;

	info->idx++;
पूर्ण

अटल पूर्णांक xenbus_map_ring_hvm(काष्ठा xenbus_device *dev,
			       काष्ठा map_ring_valloc *info,
			       grant_ref_t *gnt_ref,
			       अचिन्हित पूर्णांक nr_grefs,
			       व्योम **vaddr)
अणु
	काष्ठा xenbus_map_node *node = info->node;
	पूर्णांक err;
	व्योम *addr;
	bool leaked = false;
	अचिन्हित पूर्णांक nr_pages = XENBUS_PAGES(nr_grefs);

	err = xen_alloc_unpopulated_pages(nr_pages, node->hvm.pages);
	अगर (err)
		जाओ out_err;

	gnttab_क्रमeach_grant(node->hvm.pages, nr_grefs,
			     xenbus_map_ring_setup_grant_hvm,
			     info);

	err = __xenbus_map_ring(dev, gnt_ref, nr_grefs, node->handles,
				info, GNTMAP_host_map, &leaked);
	node->nr_handles = nr_grefs;

	अगर (err)
		जाओ out_मुक्त_ballooned_pages;

	addr = vmap(node->hvm.pages, nr_pages, VM_MAP | VM_IOREMAP,
		    PAGE_KERNEL);
	अगर (!addr) अणु
		err = -ENOMEM;
		जाओ out_xenbus_unmap_ring;
	पूर्ण

	node->hvm.addr = addr;

	spin_lock(&xenbus_valloc_lock);
	list_add(&node->next, &xenbus_valloc_pages);
	spin_unlock(&xenbus_valloc_lock);

	*vaddr = addr;
	info->node = शून्य;

	वापस 0;

 out_xenbus_unmap_ring:
	अगर (!leaked)
		xenbus_unmap_ring(dev, node->handles, nr_grefs, info->addrs);
	अन्यथा
		pr_alert("leaking %p size %u page(s)",
			 addr, nr_pages);
 out_मुक्त_ballooned_pages:
	अगर (!leaked)
		xen_मुक्त_unpopulated_pages(nr_pages, node->hvm.pages);
 out_err:
	वापस err;
पूर्ण

/**
 * xenbus_unmap_ring_vमुक्त
 * @dev: xenbus device
 * @vaddr: addr to unmap
 *
 * Based on Rusty Russell's skeleton driver's unmap_page.
 * Unmap a page of memory in this करोमुख्य that was imported from another करोमुख्य.
 * Use xenbus_unmap_ring_vमुक्त अगर you mapped in your memory with
 * xenbus_map_ring_valloc (it will मुक्त the भव address space).
 * Returns 0 on success and वापसs GNTST_* on error
 * (see xen/include/पूर्णांकerface/grant_table.h).
 */
पूर्णांक xenbus_unmap_ring_vमुक्त(काष्ठा xenbus_device *dev, व्योम *vaddr)
अणु
	वापस ring_ops->unmap(dev, vaddr);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_unmap_ring_vमुक्त);

#अगर_घोषित CONFIG_XEN_PV
अटल पूर्णांक map_ring_apply(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा map_ring_valloc *info = data;

	info->phys_addrs[info->idx++] = arbitrary_virt_to_machine(pte).maddr;
	वापस 0;
पूर्ण

अटल पूर्णांक xenbus_map_ring_pv(काष्ठा xenbus_device *dev,
			      काष्ठा map_ring_valloc *info,
			      grant_ref_t *gnt_refs,
			      अचिन्हित पूर्णांक nr_grefs,
			      व्योम **vaddr)
अणु
	काष्ठा xenbus_map_node *node = info->node;
	काष्ठा vm_काष्ठा *area;
	bool leaked = false;
	पूर्णांक err = -ENOMEM;

	area = get_vm_area(XEN_PAGE_SIZE * nr_grefs, VM_IOREMAP);
	अगर (!area)
		वापस -ENOMEM;
	अगर (apply_to_page_range(&init_mm, (अचिन्हित दीर्घ)area->addr,
				XEN_PAGE_SIZE * nr_grefs, map_ring_apply, info))
		जाओ failed;
	err = __xenbus_map_ring(dev, gnt_refs, nr_grefs, node->handles,
				info, GNTMAP_host_map | GNTMAP_contains_pte,
				&leaked);
	अगर (err)
		जाओ failed;

	node->nr_handles = nr_grefs;
	node->pv.area = area;

	spin_lock(&xenbus_valloc_lock);
	list_add(&node->next, &xenbus_valloc_pages);
	spin_unlock(&xenbus_valloc_lock);

	*vaddr = area->addr;
	info->node = शून्य;

	वापस 0;

failed:
	अगर (!leaked)
		मुक्त_vm_area(area);
	अन्यथा
		pr_alert("leaking VM area %p size %u page(s)", area, nr_grefs);

	वापस err;
पूर्ण

अटल पूर्णांक xenbus_unmap_ring_pv(काष्ठा xenbus_device *dev, व्योम *vaddr)
अणु
	काष्ठा xenbus_map_node *node;
	काष्ठा gnttab_unmap_grant_ref unmap[XENBUS_MAX_RING_GRANTS];
	अचिन्हित पूर्णांक level;
	पूर्णांक i;
	bool leaked = false;
	पूर्णांक err;

	spin_lock(&xenbus_valloc_lock);
	list_क्रम_each_entry(node, &xenbus_valloc_pages, next) अणु
		अगर (node->pv.area->addr == vaddr) अणु
			list_del(&node->next);
			जाओ found;
		पूर्ण
	पूर्ण
	node = शून्य;
 found:
	spin_unlock(&xenbus_valloc_lock);

	अगर (!node) अणु
		xenbus_dev_error(dev, -ENOENT,
				 "can't find mapped virtual address %p", vaddr);
		वापस GNTST_bad_virt_addr;
	पूर्ण

	क्रम (i = 0; i < node->nr_handles; i++) अणु
		अचिन्हित दीर्घ addr;

		स_रखो(&unmap[i], 0, माप(unmap[i]));
		addr = (अचिन्हित दीर्घ)vaddr + (XEN_PAGE_SIZE * i);
		unmap[i].host_addr = arbitrary_virt_to_machine(
			lookup_address(addr, &level)).maddr;
		unmap[i].dev_bus_addr = 0;
		unmap[i].handle = node->handles[i];
	पूर्ण

	अगर (HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref, unmap, i))
		BUG();

	err = GNTST_okay;
	leaked = false;
	क्रम (i = 0; i < node->nr_handles; i++) अणु
		अगर (unmap[i].status != GNTST_okay) अणु
			leaked = true;
			xenbus_dev_error(dev, unmap[i].status,
					 "unmapping page at handle %d error %d",
					 node->handles[i], unmap[i].status);
			err = unmap[i].status;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!leaked)
		मुक्त_vm_area(node->pv.area);
	अन्यथा
		pr_alert("leaking VM area %p size %u page(s)",
			 node->pv.area, node->nr_handles);

	kमुक्त(node);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा xenbus_ring_ops ring_ops_pv = अणु
	.map = xenbus_map_ring_pv,
	.unmap = xenbus_unmap_ring_pv,
पूर्ण;
#पूर्ण_अगर

काष्ठा unmap_ring_hvm
अणु
	अचिन्हित पूर्णांक idx;
	अचिन्हित दीर्घ addrs[XENBUS_MAX_RING_GRANTS];
पूर्ण;

अटल व्योम xenbus_unmap_ring_setup_grant_hvm(अचिन्हित दीर्घ gfn,
					      अचिन्हित पूर्णांक goffset,
					      अचिन्हित पूर्णांक len,
					      व्योम *data)
अणु
	काष्ठा unmap_ring_hvm *info = data;

	info->addrs[info->idx] = (अचिन्हित दीर्घ)gfn_to_virt(gfn);

	info->idx++;
पूर्ण

अटल पूर्णांक xenbus_unmap_ring_hvm(काष्ठा xenbus_device *dev, व्योम *vaddr)
अणु
	पूर्णांक rv;
	काष्ठा xenbus_map_node *node;
	व्योम *addr;
	काष्ठा unmap_ring_hvm info = अणु
		.idx = 0,
	पूर्ण;
	अचिन्हित पूर्णांक nr_pages;

	spin_lock(&xenbus_valloc_lock);
	list_क्रम_each_entry(node, &xenbus_valloc_pages, next) अणु
		addr = node->hvm.addr;
		अगर (addr == vaddr) अणु
			list_del(&node->next);
			जाओ found;
		पूर्ण
	पूर्ण
	node = addr = शून्य;
 found:
	spin_unlock(&xenbus_valloc_lock);

	अगर (!node) अणु
		xenbus_dev_error(dev, -ENOENT,
				 "can't find mapped virtual address %p", vaddr);
		वापस GNTST_bad_virt_addr;
	पूर्ण

	nr_pages = XENBUS_PAGES(node->nr_handles);

	gnttab_क्रमeach_grant(node->hvm.pages, node->nr_handles,
			     xenbus_unmap_ring_setup_grant_hvm,
			     &info);

	rv = xenbus_unmap_ring(dev, node->handles, node->nr_handles,
			       info.addrs);
	अगर (!rv) अणु
		vunmap(vaddr);
		xen_मुक्त_unpopulated_pages(nr_pages, node->hvm.pages);
	पूर्ण
	अन्यथा
		WARN(1, "Leaking %p, size %u page(s)\n", vaddr, nr_pages);

	kमुक्त(node);
	वापस rv;
पूर्ण

/**
 * xenbus_पढ़ो_driver_state
 * @path: path क्रम driver
 *
 * Return the state of the driver rooted at the given store path, or
 * XenbusStateUnknown अगर no state can be पढ़ो.
 */
क्रमागत xenbus_state xenbus_पढ़ो_driver_state(स्थिर अक्षर *path)
अणु
	क्रमागत xenbus_state result;
	पूर्णांक err = xenbus_gather(XBT_NIL, path, "state", "%d", &result, शून्य);
	अगर (err)
		result = XenbusStateUnknown;

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_पढ़ो_driver_state);

अटल स्थिर काष्ठा xenbus_ring_ops ring_ops_hvm = अणु
	.map = xenbus_map_ring_hvm,
	.unmap = xenbus_unmap_ring_hvm,
पूर्ण;

व्योम __init xenbus_ring_ops_init(व्योम)
अणु
#अगर_घोषित CONFIG_XEN_PV
	अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap))
		ring_ops = &ring_ops_pv;
	अन्यथा
#पूर्ण_अगर
		ring_ops = &ring_ops_hvm;
पूर्ण
