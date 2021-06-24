<शैली गुरु>
/*******************************************************************************
*
* Copyright (c) 2015-2016 Intel Corporation.  All rights reserved.
*
* This software is available to you under a choice of one of two
* licenses.  You may choose to be licensed under the terms of the GNU
* General Public License (GPL) Version 2, available from the file
* COPYING in the मुख्य directory of this source tree, or the
* OpenFabrics.org BSD license below:
*
*   Redistribution and use in source and binary क्रमms, with or
*   without modअगरication, are permitted provided that the following
*   conditions are met:
*
*    - Redistributions of source code must retain the above
*	copyright notice, this list of conditions and the following
*	disclaimer.
*
*    - Redistributions in binary क्रमm must reproduce the above
*	copyright notice, this list of conditions and the following
*	disclaimer in the करोcumentation and/or other materials
*	provided with the distribution.
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
*******************************************************************************/

#अगर_अघोषित I40IW_VF_H
#घोषणा I40IW_VF_H

काष्ठा i40iw_sc_cqp;

काष्ठा i40iw_manage_vf_pble_info अणु
	u32 sd_index;
	u16 first_pd_index;
	u16 pd_entry_cnt;
	u8 inv_pd_ent;
	u64 pd_pl_pba;
पूर्ण;

काष्ठा i40iw_vf_cqp_ops अणु
	क्रमागत i40iw_status_code (*manage_vf_pble_bp)(काष्ठा i40iw_sc_cqp *,
						    काष्ठा i40iw_manage_vf_pble_info *,
						    u64,
						    bool);
पूर्ण;

क्रमागत i40iw_status_code i40iw_manage_vf_pble_bp(काष्ठा i40iw_sc_cqp *cqp,
					       काष्ठा i40iw_manage_vf_pble_info *info,
					       u64 scratch,
					       bool post_sq);

बाह्य स्थिर काष्ठा i40iw_vf_cqp_ops iw_vf_cqp_ops;

#पूर्ण_अगर
