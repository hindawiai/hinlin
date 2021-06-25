<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#अगर_अघोषित VCHIQ_H
#घोषणा VCHIQ_H

#घोषणा VCHIQ_MAKE_FOURCC(x0, x1, x2, x3) \
			(((x0) << 24) | ((x1) << 16) | ((x2) << 8) | (x3))

क्रमागत vchiq_reason अणु
	VCHIQ_SERVICE_OPENED,         /* service, -, -             */
	VCHIQ_SERVICE_CLOSED,         /* service, -, -             */
	VCHIQ_MESSAGE_AVAILABLE,      /* service, header, -        */
	VCHIQ_BULK_TRANSMIT_DONE,     /* service, -, bulk_userdata */
	VCHIQ_BULK_RECEIVE_DONE,      /* service, -, bulk_userdata */
	VCHIQ_BULK_TRANSMIT_ABORTED,  /* service, -, bulk_userdata */
	VCHIQ_BULK_RECEIVE_ABORTED    /* service, -, bulk_userdata */
पूर्ण;

क्रमागत vchiq_status अणु
	VCHIQ_ERROR   = -1,
	VCHIQ_SUCCESS = 0,
	VCHIQ_RETRY   = 1
पूर्ण;

क्रमागत vchiq_bulk_mode अणु
	VCHIQ_BULK_MODE_CALLBACK,
	VCHIQ_BULK_MODE_BLOCKING,
	VCHIQ_BULK_MODE_NOCALLBACK,
	VCHIQ_BULK_MODE_WAITING		/* Reserved क्रम पूर्णांकernal use */
पूर्ण;

क्रमागत vchiq_service_option अणु
	VCHIQ_SERVICE_OPTION_AUTOCLOSE,
	VCHIQ_SERVICE_OPTION_SLOT_QUOTA,
	VCHIQ_SERVICE_OPTION_MESSAGE_QUOTA,
	VCHIQ_SERVICE_OPTION_SYNCHRONOUS,
	VCHIQ_SERVICE_OPTION_TRACE
पूर्ण;

काष्ठा vchiq_header अणु
	/* The message identअगरier - opaque to applications. */
	पूर्णांक msgid;

	/* Size of message data. */
	अचिन्हित पूर्णांक size;

	अक्षर data[0];           /* message */
पूर्ण;

काष्ठा vchiq_element अणु
	स्थिर व्योम __user *data;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा vchiq_service_base अणु
	पूर्णांक fourcc;
	क्रमागत vchiq_status (*callback)(क्रमागत vchiq_reason reason,
				      काष्ठा vchiq_header *header,
				      अचिन्हित पूर्णांक handle,
				      व्योम *bulk_userdata);
	व्योम *userdata;
पूर्ण;

काष्ठा vchiq_completion_data_kernel अणु
	क्रमागत vchiq_reason reason;
	काष्ठा vchiq_header *header;
	व्योम *service_userdata;
	व्योम *bulk_userdata;
पूर्ण;

काष्ठा vchiq_service_params_kernel अणु
	पूर्णांक fourcc;
	क्रमागत vchiq_status (*callback)(क्रमागत vchiq_reason reason,
				      काष्ठा vchiq_header *header,
				      अचिन्हित पूर्णांक handle,
				      व्योम *bulk_userdata);
	व्योम *userdata;
	लघु version;       /* Increment क्रम non-trivial changes */
	लघु version_min;   /* Update क्रम incompatible changes */
पूर्ण;

काष्ठा vchiq_instance;

बाह्य क्रमागत vchiq_status vchiq_initialise(काष्ठा vchiq_instance **pinstance);
बाह्य क्रमागत vchiq_status vchiq_shutकरोwn(काष्ठा vchiq_instance *instance);
बाह्य क्रमागत vchiq_status vchiq_connect(काष्ठा vchiq_instance *instance);
बाह्य क्रमागत vchiq_status vchiq_खोलो_service(काष्ठा vchiq_instance *instance,
	स्थिर काष्ठा vchiq_service_params_kernel *params,
	अचिन्हित पूर्णांक *pservice);
बाह्य क्रमागत vchiq_status vchiq_बंद_service(अचिन्हित पूर्णांक service);
बाह्य क्रमागत vchiq_status vchiq_use_service(अचिन्हित पूर्णांक service);
बाह्य क्रमागत vchiq_status vchiq_release_service(अचिन्हित पूर्णांक service);
बाह्य व्योम vchiq_msg_queue_push(अचिन्हित पूर्णांक handle, काष्ठा vchiq_header *header);
बाह्य व्योम           vchiq_release_message(अचिन्हित पूर्णांक service,
	काष्ठा vchiq_header *header);
बाह्य पूर्णांक vchiq_queue_kernel_message(अचिन्हित पूर्णांक handle, व्योम *data,
				      अचिन्हित पूर्णांक size);
बाह्य क्रमागत vchiq_status vchiq_bulk_transmit(अचिन्हित पूर्णांक service,
	स्थिर व्योम *data, अचिन्हित पूर्णांक size, व्योम *userdata,
	क्रमागत vchiq_bulk_mode mode);
बाह्य क्रमागत vchiq_status vchiq_bulk_receive(अचिन्हित पूर्णांक service,
	व्योम *data, अचिन्हित पूर्णांक size, व्योम *userdata,
	क्रमागत vchiq_bulk_mode mode);
बाह्य व्योम *vchiq_get_service_userdata(अचिन्हित पूर्णांक service);
बाह्य क्रमागत vchiq_status vchiq_get_peer_version(अचिन्हित पूर्णांक handle,
      लघु *peer_version);
बाह्य काष्ठा vchiq_header *vchiq_msg_hold(अचिन्हित पूर्णांक handle);

#पूर्ण_अगर /* VCHIQ_H */
