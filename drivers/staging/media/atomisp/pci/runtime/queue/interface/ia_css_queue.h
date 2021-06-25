<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __IA_CSS_QUEUE_H
#घोषणा __IA_CSS_QUEUE_H

#समावेश <platक्रमm_support.h>
#समावेश <type_support.h>

#समावेश "ia_css_queue_comm.h"
#समावेश "../src/queue_access.h"

/* Local Queue object descriptor */
काष्ठा ia_css_queue_local अणु
	ia_css_circbuf_desc_t *cb_desc; /*Circbuf desc क्रम local queues*/
	ia_css_circbuf_elem_t *cb_elems; /*Circbuf elements*/
पूर्ण;

प्रकार काष्ठा ia_css_queue_local ia_css_queue_local_t;

/* Handle क्रम queue object*/
प्रकार काष्ठा ia_css_queue ia_css_queue_t;

/*****************************************************************************
 * Queue Public APIs
 *****************************************************************************/
/* @brief Initialize a local queue instance.
 *
 * @param[out] qhandle. Handle to queue instance क्रम use with API
 * @param[in]  desc.   Descriptor with queue properties filled-in
 * @वापस     0      - Successful init of local queue instance.
 * @वापस     -EINVAL - Invalid argument.
 *
 */
पूर्णांक ia_css_queue_local_init(
    ia_css_queue_t *qhandle,
    ia_css_queue_local_t *desc);

/* @brief Initialize a remote queue instance
 *
 * @param[out] qhandle. Handle to queue instance क्रम use with API
 * @param[in]  desc.   Descriptor with queue properties filled-in
 * @वापस     0      - Successful init of remote queue instance.
 * @वापस     -EINVAL - Invalid argument.
 */
पूर्णांक ia_css_queue_remote_init(
    ia_css_queue_t *qhandle,
    ia_css_queue_remote_t *desc);

/* @brief Uninitialize a queue instance
 *
 * @param[in]  qhandle. Handle to queue instance
 * @वापस     0 - Successful uninit.
 *
 */
पूर्णांक ia_css_queue_uninit(
    ia_css_queue_t *qhandle);

/* @brief Enqueue an item in the queue instance
 *
 * @param[in]  qhandle. Handle to queue instance
 * @param[in]  item.    Object to be enqueued.
 * @वापस     0       - Successful enqueue.
 * @वापस     -EINVAL  - Invalid argument.
 * @वापस     -ENOBUFS - Queue is full.
 *
 */
पूर्णांक ia_css_queue_enqueue(
    ia_css_queue_t *qhandle,
    uपूर्णांक32_t item);

/* @brief Dequeue an item from the queue instance
 *
 * @param[in]  qhandle. Handle to queue instance
 * @param[out] item.    Object to be dequeued पूर्णांकo this item.

 * @वापस     0       - Successful dequeue.
 * @वापस     -EINVAL  - Invalid argument.
 * @वापस     -ENODATA - Queue is empty.
 *
 */
पूर्णांक ia_css_queue_dequeue(
    ia_css_queue_t *qhandle,
    uपूर्णांक32_t *item);

/* @brief Check अगर the queue is empty
 *
 * @param[in]  qhandle.  Handle to queue instance
 * @param[in]  is_empty  True अगर empty, False अगर not.
 * @वापस     0       - Successful access state.
 * @वापस     -EINVAL  - Invalid argument.
 * @वापस     -ENOSYS  - Function not implemented.
 *
 */
पूर्णांक ia_css_queue_is_empty(
    ia_css_queue_t *qhandle,
    bool *is_empty);

/* @brief Check अगर the queue is full
 *
 * @param[in]  qhandle.  Handle to queue instance
 * @param[in]  is_full   True अगर Full, False अगर not.
 * @वापस     0       - Successfully access state.
 * @वापस     -EINVAL  - Invalid argument.
 * @वापस     -ENOSYS  - Function not implemented.
 *
 */
पूर्णांक ia_css_queue_is_full(
    ia_css_queue_t *qhandle,
    bool *is_full);

/* @brief Get used space in the queue
 *
 * @param[in]  qhandle.  Handle to queue instance
 * @param[in]  size      Number of available elements in the queue
 * @वापस     0       - Successfully access state.
 * @वापस     -EINVAL  - Invalid argument.
 *
 */
पूर्णांक ia_css_queue_get_used_space(
    ia_css_queue_t *qhandle,
    uपूर्णांक32_t *size);

/* @brief Get मुक्त space in the queue
 *
 * @param[in]  qhandle.  Handle to queue instance
 * @param[in]  size      Number of मुक्त elements in the queue
 * @वापस     0       - Successfully access state.
 * @वापस     -EINVAL  - Invalid argument.
 *
 */
पूर्णांक ia_css_queue_get_मुक्त_space(
    ia_css_queue_t *qhandle,
    uपूर्णांक32_t *size);

/* @brief Peek at an element in the queue
 *
 * @param[in]  qhandle.  Handle to queue instance
 * @param[in]  offset   Offset of element to peek,
 *			 starting from head of queue
 * @param[in]  element   Value of element वापसed
 * @वापस     0       - Successfully access state.
 * @वापस     -EINVAL  - Invalid argument.
 *
 */
पूर्णांक ia_css_queue_peek(
    ia_css_queue_t *qhandle,
    u32 offset,
    uपूर्णांक32_t *element);

/* @brief Get the usable size क्रम the queue
 *
 * @param[in]  qhandle. Handle to queue instance
 * @param[out] size     Size value to be वापसed here.
 * @वापस     0       - Successful get size.
 * @वापस     -EINVAL  - Invalid argument.
 * @वापस     -ENOSYS  - Function not implemented.
 *
 */
पूर्णांक ia_css_queue_get_size(
    ia_css_queue_t *qhandle,
    uपूर्णांक32_t *size);

#पूर्ण_अगर /* __IA_CSS_QUEUE_H */
