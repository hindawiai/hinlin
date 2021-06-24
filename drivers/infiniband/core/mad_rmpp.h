<शैली गुरु>
/*
 * Copyright (c) 2005 Intel Inc. All rights reserved.
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

#अगर_अघोषित __MAD_RMPP_H__
#घोषणा __MAD_RMPP_H__

क्रमागत अणु
	IB_RMPP_RESULT_PROCESSED,
	IB_RMPP_RESULT_CONSUMED,
	IB_RMPP_RESULT_INTERNAL,
	IB_RMPP_RESULT_UNHANDLED
पूर्ण;

पूर्णांक ib_send_rmpp_mad(काष्ठा ib_mad_send_wr_निजी *mad_send_wr);

काष्ठा ib_mad_recv_wc *
ib_process_rmpp_recv_wc(काष्ठा ib_mad_agent_निजी *agent,
			काष्ठा ib_mad_recv_wc *mad_recv_wc);

पूर्णांक ib_process_rmpp_send_wc(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			    काष्ठा ib_mad_send_wc *mad_send_wc);

व्योम ib_rmpp_send_handler(काष्ठा ib_mad_send_wc *mad_send_wc);

व्योम ib_cancel_rmpp_recvs(काष्ठा ib_mad_agent_निजी *agent);

पूर्णांक ib_retry_rmpp(काष्ठा ib_mad_send_wr_निजी *mad_send_wr);

#पूर्ण_अगर	/* __MAD_RMPP_H__ */
