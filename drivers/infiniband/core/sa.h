<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc.  All rights reserved.
 * Copyright (c) 2006 Intel Corporation.  All rights reserved.
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

#अगर_अघोषित SA_H
#घोषणा SA_H

#समावेश <rdma/ib_sa.h>

अटल अंतरभूत व्योम ib_sa_client_get(काष्ठा ib_sa_client *client)
अणु
	atomic_inc(&client->users);
पूर्ण

अटल अंतरभूत व्योम ib_sa_client_put(काष्ठा ib_sa_client *client)
अणु
	अगर (atomic_dec_and_test(&client->users))
		complete(&client->comp);
पूर्ण

पूर्णांक ib_sa_mcmember_rec_query(काष्ठा ib_sa_client *client,
			     काष्ठा ib_device *device, u32 port_num, u8 method,
			     काष्ठा ib_sa_mcmember_rec *rec,
			     ib_sa_comp_mask comp_mask,
			     अचिन्हित दीर्घ समयout_ms, gfp_t gfp_mask,
			     व्योम (*callback)(पूर्णांक status,
					      काष्ठा ib_sa_mcmember_rec *resp,
					      व्योम *context),
			     व्योम *context, काष्ठा ib_sa_query **sa_query);

पूर्णांक mcast_init(व्योम);
व्योम mcast_cleanup(व्योम);

#पूर्ण_अगर /* SA_H */
