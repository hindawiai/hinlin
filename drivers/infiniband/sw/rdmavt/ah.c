<शैली गुरु>
/*
 * Copyright(c) 2016 - 2019 Intel Corporation.
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

#समावेश <linux/slab.h>
#समावेश "ah.h"
#समावेश "vt.h" /* क्रम prपूर्णांकs */

/**
 * rvt_check_ah - validate the attributes of AH
 * @ibdev: the ib device
 * @ah_attr: the attributes of the AH
 *
 * If driver supports a more detailed check_ah function call back to it
 * otherwise just check the basics.
 *
 * Return: 0 on success
 */
पूर्णांक rvt_check_ah(काष्ठा ib_device *ibdev,
		 काष्ठा rdma_ah_attr *ah_attr)
अणु
	पूर्णांक err;
	पूर्णांक port_num = rdma_ah_get_port_num(ah_attr);
	काष्ठा ib_port_attr port_attr;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);
	u8 ah_flags = rdma_ah_get_ah_flags(ah_attr);
	u8 अटल_rate = rdma_ah_get_अटल_rate(ah_attr);

	err = ib_query_port(ibdev, port_num, &port_attr);
	अगर (err)
		वापस -EINVAL;
	अगर (port_num < 1 ||
	    port_num > ibdev->phys_port_cnt)
		वापस -EINVAL;
	अगर (अटल_rate != IB_RATE_PORT_CURRENT &&
	    ib_rate_to_mbps(अटल_rate) < 0)
		वापस -EINVAL;
	अगर ((ah_flags & IB_AH_GRH) &&
	    rdma_ah_पढ़ो_grh(ah_attr)->sgid_index >= port_attr.gid_tbl_len)
		वापस -EINVAL;
	अगर (rdi->driver_f.check_ah)
		वापस rdi->driver_f.check_ah(ibdev, ah_attr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rvt_check_ah);

/**
 * rvt_create_ah - create an address handle
 * @ibah: the IB address handle
 * @init_attr: the attributes of the AH
 * @udata: poपूर्णांकer to user's input output buffer inक्रमmation.
 *
 * This may be called from पूर्णांकerrupt context.
 *
 * Return: 0 on success
 */
पूर्णांक rvt_create_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_init_attr *init_attr,
		  काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_ah *ah = ibah_to_rvtah(ibah);
	काष्ठा rvt_dev_info *dev = ib_to_rvt(ibah->device);
	अचिन्हित दीर्घ flags;

	अगर (rvt_check_ah(ibah->device, init_attr->ah_attr))
		वापस -EINVAL;

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	अगर (dev->n_ahs_allocated == dev->dparms.props.max_ah) अणु
		spin_unlock_irqrestore(&dev->n_ahs_lock, flags);
		वापस -ENOMEM;
	पूर्ण

	dev->n_ahs_allocated++;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	rdma_copy_ah_attr(&ah->attr, init_attr->ah_attr);

	अगर (dev->driver_f.notअगरy_new_ah)
		dev->driver_f.notअगरy_new_ah(ibah->device,
					    init_attr->ah_attr, ah);

	वापस 0;
पूर्ण

/**
 * rvt_destroy_ah - Destroy an address handle
 * @ibah: address handle
 * @destroy_flags: destroy address handle flags (see क्रमागत rdma_destroy_ah_flags)
 * Return: 0 on success
 */
पूर्णांक rvt_destroy_ah(काष्ठा ib_ah *ibah, u32 destroy_flags)
अणु
	काष्ठा rvt_dev_info *dev = ib_to_rvt(ibah->device);
	काष्ठा rvt_ah *ah = ibah_to_rvtah(ibah);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	dev->n_ahs_allocated--;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	rdma_destroy_ah_attr(&ah->attr);
	वापस 0;
पूर्ण

/**
 * rvt_modअगरy_ah - modअगरy an ah with given attrs
 * @ibah: address handle to modअगरy
 * @ah_attr: attrs to apply
 *
 * Return: 0 on success
 */
पूर्णांक rvt_modअगरy_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा rvt_ah *ah = ibah_to_rvtah(ibah);

	अगर (rvt_check_ah(ibah->device, ah_attr))
		वापस -EINVAL;

	ah->attr = *ah_attr;

	वापस 0;
पूर्ण

/**
 * rvt_query_ah - वापस attrs क्रम ah
 * @ibah: address handle to query
 * @ah_attr: वापस info in this
 *
 * Return: always 0
 */
पूर्णांक rvt_query_ah(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा rvt_ah *ah = ibah_to_rvtah(ibah);

	*ah_attr = ah->attr;

	वापस 0;
पूर्ण
