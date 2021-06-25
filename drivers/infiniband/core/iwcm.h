<शैली गुरु>
/*
 * Copyright (c) 2005 Network Appliance, Inc. All rights reserved.
 * Copyright (c) 2005 Open Grid Computing, Inc. All rights reserved.
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
#अगर_अघोषित IWCM_H
#घोषणा IWCM_H

क्रमागत iw_cm_state अणु
	IW_CM_STATE_IDLE,             /* unbound, inactive */
	IW_CM_STATE_LISTEN,           /* listen रुकोing क्रम connect */
	IW_CM_STATE_CONN_RECV,        /* inbound रुकोing क्रम user accept */
	IW_CM_STATE_CONN_SENT,        /* outbound रुकोing क्रम peer accept */
	IW_CM_STATE_ESTABLISHED,      /* established */
	IW_CM_STATE_CLOSING,	      /* disconnect */
	IW_CM_STATE_DESTROYING        /* object being deleted */
पूर्ण;

काष्ठा iwcm_id_निजी अणु
	काष्ठा iw_cm_id	id;
	क्रमागत iw_cm_state state;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_qp *qp;
	काष्ठा completion destroy_comp;
	रुको_queue_head_t connect_रुको;
	काष्ठा list_head work_list;
	spinlock_t lock;
	atomic_t refcount;
	काष्ठा list_head work_मुक्त_list;
पूर्ण;

#घोषणा IWCM_F_DROP_EVENTS	  1
#घोषणा IWCM_F_CONNECT_WAIT       2

#पूर्ण_अगर /* IWCM_H */
