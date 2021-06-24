<शैली गुरु>
#अगर_अघोषित DEF_RDMAVT_H
#घोषणा DEF_RDMAVT_H

/*
 * Copyright(c) 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <rdma/rdma_vt.h>
#समावेश <linux/pci.h>
#समावेश "pd.h"
#समावेश "qp.h"
#समावेश "ah.h"
#समावेश "mr.h"
#समावेश "srq.h"
#समावेश "mcast.h"
#समावेश "mmap.h"
#समावेश "cq.h"
#समावेश "mad.h"

#घोषणा rvt_pr_info(rdi, fmt, ...) \
	__rvt_pr_info(rdi->driver_f.get_pci_dev(rdi), \
		      rvt_get_ibdev_name(rdi), \
		      fmt, \
		      ##__VA_ARGS__)

#घोषणा rvt_pr_warn(rdi, fmt, ...) \
	__rvt_pr_warn(rdi->driver_f.get_pci_dev(rdi), \
		      rvt_get_ibdev_name(rdi), \
		      fmt, \
		      ##__VA_ARGS__)

#घोषणा rvt_pr_err(rdi, fmt, ...) \
	__rvt_pr_err(rdi->driver_f.get_pci_dev(rdi), \
		     rvt_get_ibdev_name(rdi), \
		     fmt, \
		     ##__VA_ARGS__)

#घोषणा rvt_pr_err_ratelimited(rdi, fmt, ...) \
	__rvt_pr_err_ratelimited((rdi)->driver_f.get_pci_dev(rdi), \
				 rvt_get_ibdev_name(rdi), \
				 fmt, \
				 ##__VA_ARGS__)

#घोषणा __rvt_pr_info(pdev, name, fmt, ...) \
	dev_info(&pdev->dev, "%s: " fmt, name, ##__VA_ARGS__)

#घोषणा __rvt_pr_warn(pdev, name, fmt, ...) \
	dev_warn(&pdev->dev, "%s: " fmt, name, ##__VA_ARGS__)

#घोषणा __rvt_pr_err(pdev, name, fmt, ...) \
	dev_err(&pdev->dev, "%s: " fmt, name, ##__VA_ARGS__)

#घोषणा __rvt_pr_err_ratelimited(pdev, name, fmt, ...) \
	dev_err_ratelimited(&(pdev)->dev, "%s: " fmt, name, ##__VA_ARGS__)

अटल अंतरभूत u32 ibport_num_to_idx(काष्ठा ib_device *ibdev, u32 port_num)
अणु
	वापस port_num - 1; /* IB ports start at 1 our arrays at 0 */
पूर्ण

#पूर्ण_अगर          /* DEF_RDMAVT_H */
