<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Mellanox Technologies Ltd.  All rights reserved.
 * Copyright (c) 2004, 2005 Infinicon Corporation.  All rights reserved.
 * Copyright (c) 2004, 2005 Intel Corporation.  All rights reserved.
 * Copyright (c) 2004, 2005 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2004-2007 Voltaire Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 * Copyright (c) 2014 Intel Corporation.  All rights reserved.
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

#समावेश <rdma/ib_smi.h>
#समावेश "smi.h"
#समावेश "opa_smi.h"

अटल क्रमागत smi_action __smi_handle_dr_smp_send(bool is_चयन, u32 port_num,
						u8 *hop_ptr, u8 hop_cnt,
						स्थिर u8 *initial_path,
						स्थिर u8 *वापस_path,
						u8 direction,
						bool dr_dlid_is_permissive,
						bool dr_slid_is_permissive)
अणु
	/* See section 14.2.2.2, Vol 1 IB spec */
	/* C14-6 -- valid hop_cnt values are from 0 to 63 */
	अगर (hop_cnt >= IB_SMP_MAX_PATH_HOPS)
		वापस IB_SMI_DISCARD;

	अगर (!direction) अणु
		/* C14-9:1 */
		अगर (hop_cnt && *hop_ptr == 0) अणु
			(*hop_ptr)++;
			वापस (initial_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-9:2 */
		अगर (*hop_ptr && *hop_ptr < hop_cnt) अणु
			अगर (!is_चयन)
				वापस IB_SMI_DISCARD;

			/* वापस_path set when received */
			(*hop_ptr)++;
			वापस (initial_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-9:3 -- We're at the end of the DR segment of path */
		अगर (*hop_ptr == hop_cnt) अणु
			/* वापस_path set when received */
			(*hop_ptr)++;
			वापस (is_चयन ||
				dr_dlid_is_permissive ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-9:4 -- hop_ptr = hop_cnt + 1 -> give to SMA/SM */
		/* C14-9:5 -- Fail unreasonable hop poपूर्णांकer */
		वापस (*hop_ptr == hop_cnt + 1 ? IB_SMI_HANDLE : IB_SMI_DISCARD);

	पूर्ण अन्यथा अणु
		/* C14-13:1 */
		अगर (hop_cnt && *hop_ptr == hop_cnt + 1) अणु
			(*hop_ptr)--;
			वापस (वापस_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-13:2 */
		अगर (2 <= *hop_ptr && *hop_ptr <= hop_cnt) अणु
			अगर (!is_चयन)
				वापस IB_SMI_DISCARD;

			(*hop_ptr)--;
			वापस (वापस_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-13:3 -- at the end of the DR segment of path */
		अगर (*hop_ptr == 1) अणु
			(*hop_ptr)--;
			/* C14-13:3 -- SMPs destined क्रम SM shouldn't be here */
			वापस (is_चयन ||
				dr_slid_is_permissive ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-13:4 -- hop_ptr = 0 -> should have gone to SM */
		अगर (*hop_ptr == 0)
			वापस IB_SMI_HANDLE;

		/* C14-13:5 -- Check क्रम unreasonable hop poपूर्णांकer */
		वापस IB_SMI_DISCARD;
	पूर्ण
पूर्ण

/*
 * Fixup a directed route SMP क्रम sending
 * Return IB_SMI_DISCARD अगर the SMP should be discarded
 */
क्रमागत smi_action smi_handle_dr_smp_send(काष्ठा ib_smp *smp,
				       bool is_चयन, u32 port_num)
अणु
	वापस __smi_handle_dr_smp_send(is_चयन, port_num,
					&smp->hop_ptr, smp->hop_cnt,
					smp->initial_path,
					smp->वापस_path,
					ib_get_smp_direction(smp),
					smp->dr_dlid == IB_LID_PERMISSIVE,
					smp->dr_slid == IB_LID_PERMISSIVE);
पूर्ण

क्रमागत smi_action opa_smi_handle_dr_smp_send(काष्ठा opa_smp *smp,
				       bool is_चयन, u32 port_num)
अणु
	वापस __smi_handle_dr_smp_send(is_चयन, port_num,
					&smp->hop_ptr, smp->hop_cnt,
					smp->route.dr.initial_path,
					smp->route.dr.वापस_path,
					opa_get_smp_direction(smp),
					smp->route.dr.dr_dlid ==
					OPA_LID_PERMISSIVE,
					smp->route.dr.dr_slid ==
					OPA_LID_PERMISSIVE);
पूर्ण

अटल क्रमागत smi_action __smi_handle_dr_smp_recv(bool is_चयन, u32 port_num,
						पूर्णांक phys_port_cnt,
						u8 *hop_ptr, u8 hop_cnt,
						स्थिर u8 *initial_path,
						u8 *वापस_path,
						u8 direction,
						bool dr_dlid_is_permissive,
						bool dr_slid_is_permissive)
अणु
	/* See section 14.2.2.2, Vol 1 IB spec */
	/* C14-6 -- valid hop_cnt values are from 0 to 63 */
	अगर (hop_cnt >= IB_SMP_MAX_PATH_HOPS)
		वापस IB_SMI_DISCARD;

	अगर (!direction) अणु
		/* C14-9:1 -- sender should have incremented hop_ptr */
		अगर (hop_cnt && *hop_ptr == 0)
			वापस IB_SMI_DISCARD;

		/* C14-9:2 -- पूर्णांकermediate hop */
		अगर (*hop_ptr && *hop_ptr < hop_cnt) अणु
			अगर (!is_चयन)
				वापस IB_SMI_DISCARD;

			वापस_path[*hop_ptr] = port_num;
			/* hop_ptr updated when sending */
			वापस (initial_path[*hop_ptr+1] <= phys_port_cnt ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-9:3 -- We're at the end of the DR segment of path */
		अगर (*hop_ptr == hop_cnt) अणु
			अगर (hop_cnt)
				वापस_path[*hop_ptr] = port_num;
			/* hop_ptr updated when sending */

			वापस (is_चयन ||
				dr_dlid_is_permissive ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-9:4 -- hop_ptr = hop_cnt + 1 -> give to SMA/SM */
		/* C14-9:5 -- fail unreasonable hop poपूर्णांकer */
		वापस (*hop_ptr == hop_cnt + 1 ? IB_SMI_HANDLE : IB_SMI_DISCARD);

	पूर्ण अन्यथा अणु

		/* C14-13:1 */
		अगर (hop_cnt && *hop_ptr == hop_cnt + 1) अणु
			(*hop_ptr)--;
			वापस (वापस_path[*hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-13:2 */
		अगर (2 <= *hop_ptr && *hop_ptr <= hop_cnt) अणु
			अगर (!is_चयन)
				वापस IB_SMI_DISCARD;

			/* hop_ptr updated when sending */
			वापस (वापस_path[*hop_ptr-1] <= phys_port_cnt ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-13:3 -- We're at the end of the DR segment of path */
		अगर (*hop_ptr == 1) अणु
			अगर (dr_slid_is_permissive) अणु
				/* giving SMP to SM - update hop_ptr */
				(*hop_ptr)--;
				वापस IB_SMI_HANDLE;
			पूर्ण
			/* hop_ptr updated when sending */
			वापस (is_चयन ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		पूर्ण

		/* C14-13:4 -- hop_ptr = 0 -> give to SM */
		/* C14-13:5 -- Check क्रम unreasonable hop poपूर्णांकer */
		वापस (*hop_ptr == 0 ? IB_SMI_HANDLE : IB_SMI_DISCARD);
	पूर्ण
पूर्ण

/*
 * Adjust inक्रमmation क्रम a received SMP
 * Return IB_SMI_DISCARD अगर the SMP should be dropped
 */
क्रमागत smi_action smi_handle_dr_smp_recv(काष्ठा ib_smp *smp, bool is_चयन,
				       u32 port_num, पूर्णांक phys_port_cnt)
अणु
	वापस __smi_handle_dr_smp_recv(is_चयन, port_num, phys_port_cnt,
					&smp->hop_ptr, smp->hop_cnt,
					smp->initial_path,
					smp->वापस_path,
					ib_get_smp_direction(smp),
					smp->dr_dlid == IB_LID_PERMISSIVE,
					smp->dr_slid == IB_LID_PERMISSIVE);
पूर्ण

/*
 * Adjust inक्रमmation क्रम a received SMP
 * Return IB_SMI_DISCARD अगर the SMP should be dropped
 */
क्रमागत smi_action opa_smi_handle_dr_smp_recv(काष्ठा opa_smp *smp, bool is_चयन,
					   u32 port_num, पूर्णांक phys_port_cnt)
अणु
	वापस __smi_handle_dr_smp_recv(is_चयन, port_num, phys_port_cnt,
					&smp->hop_ptr, smp->hop_cnt,
					smp->route.dr.initial_path,
					smp->route.dr.वापस_path,
					opa_get_smp_direction(smp),
					smp->route.dr.dr_dlid ==
					OPA_LID_PERMISSIVE,
					smp->route.dr.dr_slid ==
					OPA_LID_PERMISSIVE);
पूर्ण

अटल क्रमागत smi_क्रमward_action __smi_check_क्रमward_dr_smp(u8 hop_ptr, u8 hop_cnt,
							  u8 direction,
							  bool dr_dlid_is_permissive,
							  bool dr_slid_is_permissive)
अणु
	अगर (!direction) अणु
		/* C14-9:2 -- पूर्णांकermediate hop */
		अगर (hop_ptr && hop_ptr < hop_cnt)
			वापस IB_SMI_FORWARD;

		/* C14-9:3 -- at the end of the DR segment of path */
		अगर (hop_ptr == hop_cnt)
			वापस (dr_dlid_is_permissive ?
				IB_SMI_SEND : IB_SMI_LOCAL);

		/* C14-9:4 -- hop_ptr = hop_cnt + 1 -> give to SMA/SM */
		अगर (hop_ptr == hop_cnt + 1)
			वापस IB_SMI_SEND;
	पूर्ण अन्यथा अणु
		/* C14-13:2  -- पूर्णांकermediate hop */
		अगर (2 <= hop_ptr && hop_ptr <= hop_cnt)
			वापस IB_SMI_FORWARD;

		/* C14-13:3 -- at the end of the DR segment of path */
		अगर (hop_ptr == 1)
			वापस (!dr_slid_is_permissive ?
				IB_SMI_SEND : IB_SMI_LOCAL);
	पूर्ण
	वापस IB_SMI_LOCAL;

पूर्ण

क्रमागत smi_क्रमward_action smi_check_क्रमward_dr_smp(काष्ठा ib_smp *smp)
अणु
	वापस __smi_check_क्रमward_dr_smp(smp->hop_ptr, smp->hop_cnt,
					  ib_get_smp_direction(smp),
					  smp->dr_dlid == IB_LID_PERMISSIVE,
					  smp->dr_slid == IB_LID_PERMISSIVE);
पूर्ण

क्रमागत smi_क्रमward_action opa_smi_check_क्रमward_dr_smp(काष्ठा opa_smp *smp)
अणु
	वापस __smi_check_क्रमward_dr_smp(smp->hop_ptr, smp->hop_cnt,
					  opa_get_smp_direction(smp),
					  smp->route.dr.dr_dlid ==
					  OPA_LID_PERMISSIVE,
					  smp->route.dr.dr_slid ==
					  OPA_LID_PERMISSIVE);
पूर्ण

/*
 * Return the क्रमwarding port number from initial_path क्रम outgoing SMP and
 * from वापस_path क्रम वापसing SMP
 */
पूर्णांक smi_get_fwd_port(काष्ठा ib_smp *smp)
अणु
	वापस (!ib_get_smp_direction(smp) ? smp->initial_path[smp->hop_ptr+1] :
		smp->वापस_path[smp->hop_ptr-1]);
पूर्ण

/*
 * Return the क्रमwarding port number from initial_path क्रम outgoing SMP and
 * from वापस_path क्रम वापसing SMP
 */
पूर्णांक opa_smi_get_fwd_port(काष्ठा opa_smp *smp)
अणु
	वापस !opa_get_smp_direction(smp) ? smp->route.dr.initial_path[smp->hop_ptr+1] :
		smp->route.dr.वापस_path[smp->hop_ptr-1];
पूर्ण
