<शैली गुरु>
/*
 * Private include क्रम xenbus communications.
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

#अगर_अघोषित _XENBUS_XENBUS_H
#घोषणा _XENBUS_XENBUS_H

#समावेश <linux/mutex.h>
#समावेश <linux/uपन.स>
#समावेश <xen/xenbus.h>

#घोषणा XEN_BUS_ID_SIZE			20

काष्ठा xen_bus_type अणु
	अक्षर *root;
	अचिन्हित पूर्णांक levels;
	पूर्णांक (*get_bus_id)(अक्षर bus_id[XEN_BUS_ID_SIZE], स्थिर अक्षर *nodename);
	पूर्णांक (*probe)(काष्ठा xen_bus_type *bus, स्थिर अक्षर *type,
		     स्थिर अक्षर *dir);
	bool (*otherend_will_handle)(काष्ठा xenbus_watch *watch,
				     स्थिर अक्षर *path, स्थिर अक्षर *token);
	व्योम (*otherend_changed)(काष्ठा xenbus_watch *watch, स्थिर अक्षर *path,
				 स्थिर अक्षर *token);
	काष्ठा bus_type bus;
पूर्ण;

क्रमागत xenstore_init अणु
	XS_UNKNOWN,
	XS_PV,
	XS_HVM,
	XS_LOCAL,
पूर्ण;

काष्ठा xs_watch_event अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक len;
	काष्ठा xenbus_watch *handle;
	स्थिर अक्षर *path;
	स्थिर अक्षर *token;
	अक्षर body[];
पूर्ण;

क्रमागत xb_req_state अणु
	xb_req_state_queued,
	xb_req_state_रुको_reply,
	xb_req_state_got_reply,
	xb_req_state_पातed
पूर्ण;

काष्ठा xb_req_data अणु
	काष्ठा list_head list;
	रुको_queue_head_t wq;
	काष्ठा xsd_sockmsg msg;
	uपूर्णांक32_t caller_req_id;
	क्रमागत xsd_sockmsg_type type;
	अक्षर *body;
	स्थिर काष्ठा kvec *vec;
	पूर्णांक num_vecs;
	पूर्णांक err;
	क्रमागत xb_req_state state;
	bool user_req;
	व्योम (*cb)(काष्ठा xb_req_data *);
	व्योम *par;
पूर्ण;

बाह्य क्रमागत xenstore_init xen_store_करोमुख्य_type;
बाह्य स्थिर काष्ठा attribute_group *xenbus_dev_groups[];
बाह्य काष्ठा mutex xs_response_mutex;
बाह्य काष्ठा list_head xs_reply_list;
बाह्य काष्ठा list_head xb_ग_लिखो_list;
बाह्य रुको_queue_head_t xb_रुकोq;
बाह्य काष्ठा mutex xb_ग_लिखो_mutex;

पूर्णांक xs_init(व्योम);
पूर्णांक xb_init_comms(व्योम);
व्योम xb_deinit_comms(व्योम);
पूर्णांक xs_watch_msg(काष्ठा xs_watch_event *event);
व्योम xs_request_निकास(काष्ठा xb_req_data *req);

पूर्णांक xenbus_match(काष्ठा device *_dev, काष्ठा device_driver *_drv);
पूर्णांक xenbus_dev_probe(काष्ठा device *_dev);
पूर्णांक xenbus_dev_हटाओ(काष्ठा device *_dev);
पूर्णांक xenbus_रेजिस्टर_driver_common(काष्ठा xenbus_driver *drv,
				  काष्ठा xen_bus_type *bus,
				  काष्ठा module *owner,
				  स्थिर अक्षर *mod_name);
पूर्णांक xenbus_probe_node(काष्ठा xen_bus_type *bus,
		      स्थिर अक्षर *type,
		      स्थिर अक्षर *nodename);
पूर्णांक xenbus_probe_devices(काष्ठा xen_bus_type *bus);

व्योम xenbus_dev_changed(स्थिर अक्षर *node, काष्ठा xen_bus_type *bus);

पूर्णांक xenbus_dev_suspend(काष्ठा device *dev);
पूर्णांक xenbus_dev_resume(काष्ठा device *dev);
पूर्णांक xenbus_dev_cancel(काष्ठा device *dev);

व्योम xenbus_otherend_changed(काष्ठा xenbus_watch *watch,
			     स्थिर अक्षर *path, स्थिर अक्षर *token,
			     पूर्णांक ignore_on_shutकरोwn);

पूर्णांक xenbus_पढ़ो_otherend_details(काष्ठा xenbus_device *xendev,
				 अक्षर *id_node, अक्षर *path_node);

व्योम xenbus_ring_ops_init(व्योम);

पूर्णांक xenbus_dev_request_and_reply(काष्ठा xsd_sockmsg *msg, व्योम *par);
व्योम xenbus_dev_queue_reply(काष्ठा xb_req_data *req);

बाह्य अचिन्हित पूर्णांक xb_dev_generation_id;

#पूर्ण_अगर
