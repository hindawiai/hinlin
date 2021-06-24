<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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

#अगर_अघोषित USNIC_IB_SYSFS_H_
#घोषणा USNIC_IB_SYSFS_H_

#समावेश "usnic_ib.h"

पूर्णांक usnic_ib_sysfs_रेजिस्टर_usdev(काष्ठा usnic_ib_dev *us_ibdev);
व्योम usnic_ib_sysfs_unरेजिस्टर_usdev(काष्ठा usnic_ib_dev *us_ibdev);
व्योम usnic_ib_sysfs_qpn_add(काष्ठा usnic_ib_qp_grp *qp_grp);
व्योम usnic_ib_sysfs_qpn_हटाओ(काष्ठा usnic_ib_qp_grp *qp_grp);

बाह्य स्थिर काष्ठा attribute_group usnic_attr_group;

#पूर्ण_अगर /* !USNIC_IB_SYSFS_H_ */
