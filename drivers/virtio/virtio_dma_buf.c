<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dma-bufs क्रम virtio exported objects
 *
 * Copyright (C) 2020 Google, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/virtio_dma_buf.h>

/**
 * virtio_dma_buf_export - Creates a new dma-buf क्रम a virtio exported object
 * @exp_info: [in] see dma_buf_export(). ops MUST refer to a dma_buf_ops
 *	काष्ठा embedded in a virtio_dma_buf_ops.
 *
 * This wraps dma_buf_export() to allow virtio drivers to create a dma-buf
 * क्रम an virtio exported object that can be queried by other virtio drivers
 * क्रम the object's UUID.
 */
काष्ठा dma_buf *virtio_dma_buf_export
	(स्थिर काष्ठा dma_buf_export_info *exp_info)
अणु
	स्थिर काष्ठा virtio_dma_buf_ops *virtio_ops =
		container_of(exp_info->ops,
			     स्थिर काष्ठा virtio_dma_buf_ops, ops);

	अगर (!exp_info->ops ||
	    exp_info->ops->attach != &virtio_dma_buf_attach ||
	    !virtio_ops->get_uuid) अणु
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस dma_buf_export(exp_info);
पूर्ण
EXPORT_SYMBOL(virtio_dma_buf_export);

/**
 * virtio_dma_buf_attach - mandatory attach callback क्रम virtio dma-bufs
 */
पूर्णांक virtio_dma_buf_attach(काष्ठा dma_buf *dma_buf,
			  काष्ठा dma_buf_attachment *attach)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा virtio_dma_buf_ops *ops =
		container_of(dma_buf->ops,
			     स्थिर काष्ठा virtio_dma_buf_ops, ops);

	अगर (ops->device_attach) अणु
		ret = ops->device_attach(dma_buf, attach);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(virtio_dma_buf_attach);

/**
 * is_virtio_dma_buf - वापसs true अगर the given dma-buf is a virtio dma-buf
 * @dma_buf: buffer to query
 */
bool is_virtio_dma_buf(काष्ठा dma_buf *dma_buf)
अणु
	वापस dma_buf->ops->attach == &virtio_dma_buf_attach;
पूर्ण
EXPORT_SYMBOL(is_virtio_dma_buf);

/**
 * virtio_dma_buf_get_uuid - माला_लो a virtio dma-buf's exported object's uuid
 * @dma_buf: [in] buffer to query
 * @uuid: [out] the uuid
 *
 * Returns: 0 on success, negative on failure.
 */
पूर्णांक virtio_dma_buf_get_uuid(काष्ठा dma_buf *dma_buf,
			    uuid_t *uuid)
अणु
	स्थिर काष्ठा virtio_dma_buf_ops *ops =
		container_of(dma_buf->ops,
			     स्थिर काष्ठा virtio_dma_buf_ops, ops);

	अगर (!is_virtio_dma_buf(dma_buf))
		वापस -EINVAL;

	वापस ops->get_uuid(dma_buf, uuid);
पूर्ण
EXPORT_SYMBOL(virtio_dma_buf_get_uuid);

MODULE_LICENSE("GPL");
