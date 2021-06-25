<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2010-2012 Broadcom. All rights reserved. */

#अगर_अघोषित VCHIQ_IOCTLS_H
#घोषणा VCHIQ_IOCTLS_H

#समावेश <linux/ioctl.h>
#समावेश <linux/raspberrypi/vchiq.h>

#घोषणा VCHIQ_IOC_MAGIC 0xc4
#घोषणा VCHIQ_INVALID_HANDLE (~0)

काष्ठा vchiq_service_params अणु
	पूर्णांक fourcc;
	क्रमागत vchiq_status __user (*callback)(क्रमागत vchiq_reason reason,
				      काष्ठा vchiq_header *header,
				      अचिन्हित पूर्णांक handle,
				      व्योम *bulk_userdata);
	व्योम __user *userdata;
	लघु version;       /* Increment क्रम non-trivial changes */
	लघु version_min;   /* Update क्रम incompatible changes */
पूर्ण;

काष्ठा vchiq_create_service अणु
	काष्ठा vchiq_service_params params;
	पूर्णांक is_खोलो;
	पूर्णांक is_vchi;
	अचिन्हित पूर्णांक handle;       /* OUT */
पूर्ण;

काष्ठा vchiq_queue_message अणु
	अचिन्हित पूर्णांक handle;
	अचिन्हित पूर्णांक count;
	स्थिर काष्ठा vchiq_element __user *elements;
पूर्ण;

काष्ठा vchiq_queue_bulk_transfer अणु
	अचिन्हित पूर्णांक handle;
	व्योम __user *data;
	अचिन्हित पूर्णांक size;
	व्योम __user *userdata;
	क्रमागत vchiq_bulk_mode mode;
पूर्ण;

काष्ठा vchiq_completion_data अणु
	क्रमागत vchiq_reason reason;
	काष्ठा vchiq_header __user *header;
	व्योम __user *service_userdata;
	व्योम __user *bulk_userdata;
पूर्ण;

काष्ठा vchiq_aरुको_completion अणु
	अचिन्हित पूर्णांक count;
	काष्ठा vchiq_completion_data __user *buf;
	अचिन्हित पूर्णांक msgbufsize;
	अचिन्हित पूर्णांक msgbufcount; /* IN/OUT */
	व्योम * __user *msgbufs;
पूर्ण;

काष्ठा vchiq_dequeue_message अणु
	अचिन्हित पूर्णांक handle;
	पूर्णांक blocking;
	अचिन्हित पूर्णांक bufsize;
	व्योम __user *buf;
पूर्ण;

काष्ठा vchiq_get_config अणु
	अचिन्हित पूर्णांक config_size;
	काष्ठा vchiq_config __user *pconfig;
पूर्ण;

काष्ठा vchiq_set_service_option अणु
	अचिन्हित पूर्णांक handle;
	क्रमागत vchiq_service_option option;
	पूर्णांक value;
पूर्ण;

काष्ठा vchiq_dump_mem अणु
	व्योम     __user *virt_addr;
	माप_प्रकार    num_bytes;
पूर्ण;

#घोषणा VCHIQ_IOC_CONNECT              _IO(VCHIQ_IOC_MAGIC,   0)
#घोषणा VCHIQ_IOC_SHUTDOWN             _IO(VCHIQ_IOC_MAGIC,   1)
#घोषणा VCHIQ_IOC_CREATE_SERVICE \
	_IOWR(VCHIQ_IOC_MAGIC, 2, काष्ठा vchiq_create_service)
#घोषणा VCHIQ_IOC_REMOVE_SERVICE       _IO(VCHIQ_IOC_MAGIC,   3)
#घोषणा VCHIQ_IOC_QUEUE_MESSAGE \
	_IOW(VCHIQ_IOC_MAGIC,  4, काष्ठा vchiq_queue_message)
#घोषणा VCHIQ_IOC_QUEUE_BULK_TRANSMIT \
	_IOWR(VCHIQ_IOC_MAGIC, 5, काष्ठा vchiq_queue_bulk_transfer)
#घोषणा VCHIQ_IOC_QUEUE_BULK_RECEIVE \
	_IOWR(VCHIQ_IOC_MAGIC, 6, काष्ठा vchiq_queue_bulk_transfer)
#घोषणा VCHIQ_IOC_AWAIT_COMPLETION \
	_IOWR(VCHIQ_IOC_MAGIC, 7, काष्ठा vchiq_aरुको_completion)
#घोषणा VCHIQ_IOC_DEQUEUE_MESSAGE \
	_IOWR(VCHIQ_IOC_MAGIC, 8, काष्ठा vchiq_dequeue_message)
#घोषणा VCHIQ_IOC_GET_CLIENT_ID        _IO(VCHIQ_IOC_MAGIC,   9)
#घोषणा VCHIQ_IOC_GET_CONFIG \
	_IOWR(VCHIQ_IOC_MAGIC, 10, काष्ठा vchiq_get_config)
#घोषणा VCHIQ_IOC_CLOSE_SERVICE        _IO(VCHIQ_IOC_MAGIC,   11)
#घोषणा VCHIQ_IOC_USE_SERVICE          _IO(VCHIQ_IOC_MAGIC,   12)
#घोषणा VCHIQ_IOC_RELEASE_SERVICE      _IO(VCHIQ_IOC_MAGIC,   13)
#घोषणा VCHIQ_IOC_SET_SERVICE_OPTION \
	_IOW(VCHIQ_IOC_MAGIC,  14, काष्ठा vchiq_set_service_option)
#घोषणा VCHIQ_IOC_DUMP_PHYS_MEM \
	_IOW(VCHIQ_IOC_MAGIC,  15, काष्ठा vchiq_dump_mem)
#घोषणा VCHIQ_IOC_LIB_VERSION          _IO(VCHIQ_IOC_MAGIC,   16)
#घोषणा VCHIQ_IOC_CLOSE_DELIVERED      _IO(VCHIQ_IOC_MAGIC,   17)
#घोषणा VCHIQ_IOC_MAX                  17

#पूर्ण_अगर
