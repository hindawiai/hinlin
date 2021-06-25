<शैली गुरु>
/*
 * Copyright (c) 2007, 2008 QLogic Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <linux/device.h>

काष्ठा qib_user_sdma_queue;

काष्ठा qib_user_sdma_queue *
qib_user_sdma_queue_create(काष्ठा device *dev, पूर्णांक unit, पूर्णांक port, पूर्णांक sport);
व्योम qib_user_sdma_queue_destroy(काष्ठा qib_user_sdma_queue *pq);

पूर्णांक qib_user_sdma_ग_लिखोv(काष्ठा qib_ctxtdata *pd,
			 काष्ठा qib_user_sdma_queue *pq,
			 स्थिर काष्ठा iovec *iov,
			 अचिन्हित दीर्घ dim);

पूर्णांक qib_user_sdma_make_progress(काष्ठा qib_pportdata *ppd,
				काष्ठा qib_user_sdma_queue *pq);

व्योम qib_user_sdma_queue_drain(काष्ठा qib_pportdata *ppd,
			       काष्ठा qib_user_sdma_queue *pq);

u32 qib_user_sdma_complete_counter(स्थिर काष्ठा qib_user_sdma_queue *pq);
u32 qib_user_sdma_inflight_counter(काष्ठा qib_user_sdma_queue *pq);
