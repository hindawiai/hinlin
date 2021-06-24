<शैली गुरु>
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
#समावेश <rdma/iw_cm.h>

पूर्णांक qedr_iw_connect(काष्ठा iw_cm_id *cm_id,
		    काष्ठा iw_cm_conn_param *conn_param);

पूर्णांक qedr_iw_create_listen(काष्ठा iw_cm_id *cm_id, पूर्णांक backlog);

पूर्णांक qedr_iw_destroy_listen(काष्ठा iw_cm_id *cm_id);

पूर्णांक qedr_iw_accept(काष्ठा iw_cm_id *cm_id, काष्ठा iw_cm_conn_param *conn_param);

पूर्णांक qedr_iw_reject(काष्ठा iw_cm_id *cm_id, स्थिर व्योम *pdata, u8 pdata_len);

व्योम qedr_iw_qp_add_ref(काष्ठा ib_qp *qp);

व्योम qedr_iw_qp_rem_ref(काष्ठा ib_qp *qp);

काष्ठा ib_qp *qedr_iw_get_qp(काष्ठा ib_device *dev, पूर्णांक qpn);
