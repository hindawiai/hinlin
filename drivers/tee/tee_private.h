<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015-2016, Linaro Limited
 */
#अगर_अघोषित TEE_PRIVATE_H
#घोषणा TEE_PRIVATE_H

#समावेश <linux/cdev.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>

/**
 * काष्ठा tee_shm_pool - shared memory pool
 * @निजी_mgr:	pool manager क्रम shared memory only between kernel
 *			and secure world
 * @dma_buf_mgr:	pool manager क्रम shared memory exported to user space
 */
काष्ठा tee_shm_pool अणु
	काष्ठा tee_shm_pool_mgr *निजी_mgr;
	काष्ठा tee_shm_pool_mgr *dma_buf_mgr;
पूर्ण;

#घोषणा TEE_DEVICE_FLAG_REGISTERED	0x1
#घोषणा TEE_MAX_DEV_NAME_LEN		32

/**
 * काष्ठा tee_device - TEE Device representation
 * @name:	name of device
 * @desc:	description of device
 * @id:		unique id of device
 * @flags:	represented by TEE_DEVICE_FLAG_REGISTERED above
 * @dev:	embedded basic device काष्ठाure
 * @cdev:	embedded cdev
 * @num_users:	number of active users of this device
 * @c_no_user:	completion used when unरेजिस्टरing the device
 * @mutex:	mutex protecting @num_users and @idr
 * @idr:	रेजिस्टर of user space shared memory objects allocated or
 *		रेजिस्टरed on this device
 * @pool:	shared memory pool
 */
काष्ठा tee_device अणु
	अक्षर name[TEE_MAX_DEV_NAME_LEN];
	स्थिर काष्ठा tee_desc *desc;
	पूर्णांक id;
	अचिन्हित पूर्णांक flags;

	काष्ठा device dev;
	काष्ठा cdev cdev;

	माप_प्रकार num_users;
	काष्ठा completion c_no_users;
	काष्ठा mutex mutex;	/* protects num_users and idr */

	काष्ठा idr idr;
	काष्ठा tee_shm_pool *pool;
पूर्ण;

पूर्णांक tee_shm_init(व्योम);

पूर्णांक tee_shm_get_fd(काष्ठा tee_shm *shm);

bool tee_device_get(काष्ठा tee_device *teedev);
व्योम tee_device_put(काष्ठा tee_device *teedev);

व्योम teedev_ctx_get(काष्ठा tee_context *ctx);
व्योम teedev_ctx_put(काष्ठा tee_context *ctx);

#पूर्ण_अगर /*TEE_PRIVATE_H*/
