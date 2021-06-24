<शैली गुरु>
/*
 * Copyright (c) 2004 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004-2007 Voltaire Corporation.  All rights reserved.
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
 *
 */

#अगर_अघोषित __SMI_H_
#घोषणा __SMI_H_

#समावेश <rdma/ib_smi.h>

क्रमागत smi_action अणु
	IB_SMI_DISCARD,
	IB_SMI_HANDLE
पूर्ण;

क्रमागत smi_क्रमward_action अणु
	IB_SMI_LOCAL,	/* SMP should be completed up the stack */
	IB_SMI_SEND,	/* received DR SMP should be क्रमwarded to the send queue */
	IB_SMI_FORWARD	/* SMP should be क्रमwarded (क्रम चयनes only) */
पूर्ण;

क्रमागत smi_action smi_handle_dr_smp_recv(काष्ठा ib_smp *smp, bool is_चयन,
				       u32 port_num, पूर्णांक phys_port_cnt);
पूर्णांक smi_get_fwd_port(काष्ठा ib_smp *smp);
बाह्य क्रमागत smi_क्रमward_action smi_check_क्रमward_dr_smp(काष्ठा ib_smp *smp);
बाह्य क्रमागत smi_action smi_handle_dr_smp_send(काष्ठा ib_smp *smp,
					      bool is_चयन, u32 port_num);

/*
 * Return IB_SMI_HANDLE अगर the SMP should be handled by the local SMA/SM
 * via process_mad
 */
अटल अंतरभूत क्रमागत smi_action smi_check_local_smp(काष्ठा ib_smp *smp,
						  काष्ठा ib_device *device)
अणु
	/* C14-9:3 -- We're at the end of the DR segment of path */
	/* C14-9:4 -- Hop Poपूर्णांकer = Hop Count + 1 -> give to SMA/SM */
	वापस ((device->ops.process_mad &&
		!ib_get_smp_direction(smp) &&
		(smp->hop_ptr == smp->hop_cnt + 1)) ?
		IB_SMI_HANDLE : IB_SMI_DISCARD);
पूर्ण

/*
 * Return IB_SMI_HANDLE अगर the SMP should be handled by the local SMA/SM
 * via process_mad
 */
अटल अंतरभूत क्रमागत smi_action smi_check_local_वापसing_smp(काष्ठा ib_smp *smp,
						   काष्ठा ib_device *device)
अणु
	/* C14-13:3 -- We're at the end of the DR segment of path */
	/* C14-13:4 -- Hop Poपूर्णांकer == 0 -> give to SM */
	वापस ((device->ops.process_mad &&
		ib_get_smp_direction(smp) &&
		!smp->hop_ptr) ? IB_SMI_HANDLE : IB_SMI_DISCARD);
पूर्ण

#पूर्ण_अगर	/* __SMI_H_ */
