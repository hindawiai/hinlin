<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित MTHCA_PROखाता_H
#घोषणा MTHCA_PROखाता_H

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"

काष्ठा mthca_profile अणु
	पूर्णांक num_qp;
	पूर्णांक rdb_per_qp;
	पूर्णांक num_srq;
	पूर्णांक num_cq;
	पूर्णांक num_mcg;
	पूर्णांक num_mpt;
	पूर्णांक num_mtt;
	पूर्णांक num_udav;
	पूर्णांक num_uar;
	पूर्णांक uarc_size;
	पूर्णांक fmr_reserved_mtts;
पूर्ण;

s64 mthca_make_profile(काष्ठा mthca_dev *mdev,
		       काष्ठा mthca_profile *request,
		       काष्ठा mthca_dev_lim *dev_lim,
		       काष्ठा mthca_init_hca_param *init_hca);

#पूर्ण_अगर /* MTHCA_PROखाता_H */
