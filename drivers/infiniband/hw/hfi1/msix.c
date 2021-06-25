<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2018 - 2020 Intel Corporation.
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

#समावेश "hfi.h"
#समावेश "affinity.h"
#समावेश "sdma.h"
#समावेश "netdev.h"

/**
 * msix_initialize() - Calculate, request and configure MSIx IRQs
 * @dd: valid hfi1 devdata
 *
 */
पूर्णांक msix_initialize(काष्ठा hfi1_devdata *dd)
अणु
	u32 total;
	पूर्णांक ret;
	काष्ठा hfi1_msix_entry *entries;

	/*
	 * MSIx पूर्णांकerrupt count:
	 *	one क्रम the general, "slow path" पूर्णांकerrupt
	 *	one per used SDMA engine
	 *	one per kernel receive context
	 *	one क्रम each VNIC context
	 *      ...any new IRQs should be added here.
	 */
	total = 1 + dd->num_sdma + dd->n_krcv_queues + dd->num_netdev_contexts;

	अगर (total >= CCE_NUM_MSIX_VECTORS)
		वापस -EINVAL;

	ret = pci_alloc_irq_vectors(dd->pcidev, total, total, PCI_IRQ_MSIX);
	अगर (ret < 0) अणु
		dd_dev_err(dd, "pci_alloc_irq_vectors() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	entries = kसुस्मृति(total, माप(*dd->msix_info.msix_entries),
			  GFP_KERNEL);
	अगर (!entries) अणु
		pci_मुक्त_irq_vectors(dd->pcidev);
		वापस -ENOMEM;
	पूर्ण

	dd->msix_info.msix_entries = entries;
	spin_lock_init(&dd->msix_info.msix_lock);
	biपंचांगap_zero(dd->msix_info.in_use_msix, total);
	dd->msix_info.max_requested = total;
	dd_dev_info(dd, "%u MSI-X interrupts allocated\n", total);

	वापस 0;
पूर्ण

/**
 * msix_request_irq() - Allocate a मुक्त MSIx IRQ
 * @dd: valid devdata
 * @arg: context inक्रमmation क्रम the IRQ
 * @handler: IRQ handler
 * @thपढ़ो: IRQ thपढ़ो handler (could be शून्य)
 * @type: affपूर्णांकy IRQ type
 * @name: IRQ name
 *
 * Allocated an MSIx vector अगर available, and then create the appropriate
 * meta data needed to keep track of the pci IRQ request.
 *
 * Return:
 *   < 0   Error
 *   >= 0  MSIx vector
 *
 */
अटल पूर्णांक msix_request_irq(काष्ठा hfi1_devdata *dd, व्योम *arg,
			    irq_handler_t handler, irq_handler_t thपढ़ो,
			    क्रमागत irq_type type, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ nr;
	पूर्णांक irq;
	पूर्णांक ret;
	काष्ठा hfi1_msix_entry *me;

	/* Allocate an MSIx vector */
	spin_lock(&dd->msix_info.msix_lock);
	nr = find_first_zero_bit(dd->msix_info.in_use_msix,
				 dd->msix_info.max_requested);
	अगर (nr < dd->msix_info.max_requested)
		__set_bit(nr, dd->msix_info.in_use_msix);
	spin_unlock(&dd->msix_info.msix_lock);

	अगर (nr == dd->msix_info.max_requested)
		वापस -ENOSPC;

	अगर (type < IRQ_SDMA || type >= IRQ_OTHER)
		वापस -EINVAL;

	irq = pci_irq_vector(dd->pcidev, nr);
	ret = pci_request_irq(dd->pcidev, nr, handler, thपढ़ो, arg, name);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "%s: request for IRQ %d failed, MSIx %lx, err %d\n",
			   name, irq, nr, ret);
		spin_lock(&dd->msix_info.msix_lock);
		__clear_bit(nr, dd->msix_info.in_use_msix);
		spin_unlock(&dd->msix_info.msix_lock);
		वापस ret;
	पूर्ण

	/*
	 * assign arg after pci_request_irq call, so it will be
	 * cleaned up
	 */
	me = &dd->msix_info.msix_entries[nr];
	me->irq = irq;
	me->arg = arg;
	me->type = type;

	/* This is a request, so a failure is not fatal */
	ret = hfi1_get_irq_affinity(dd, me);
	अगर (ret)
		dd_dev_err(dd, "%s: unable to pin IRQ %d\n", name, ret);

	वापस nr;
पूर्ण

अटल पूर्णांक msix_request_rcd_irq_common(काष्ठा hfi1_ctxtdata *rcd,
				       irq_handler_t handler,
				       irq_handler_t thपढ़ो,
				       स्थिर अक्षर *name)
अणु
	पूर्णांक nr = msix_request_irq(rcd->dd, rcd, handler, thपढ़ो,
				  rcd->is_vnic ? IRQ_NETDEVCTXT : IRQ_RCVCTXT,
				  name);
	अगर (nr < 0)
		वापस nr;

	/*
	 * Set the पूर्णांकerrupt रेजिस्टर and mask क्रम this
	 * context's पूर्णांकerrupt.
	 */
	rcd->ireg = (IS_RCVAVAIL_START + rcd->ctxt) / 64;
	rcd->imask = ((u64)1) << ((IS_RCVAVAIL_START + rcd->ctxt) % 64);
	rcd->msix_पूर्णांकr = nr;
	remap_पूर्णांकr(rcd->dd, IS_RCVAVAIL_START + rcd->ctxt, nr);

	वापस 0;
पूर्ण

/**
 * msix_request_rcd_irq() - Helper function क्रम RCVAVAIL IRQs
 * @rcd: valid rcd context
 *
 */
पूर्णांक msix_request_rcd_irq(काष्ठा hfi1_ctxtdata *rcd)
अणु
	अक्षर name[MAX_NAME_SIZE];

	snम_लिखो(name, माप(name), DRIVER_NAME "_%d kctxt%d",
		 rcd->dd->unit, rcd->ctxt);

	वापस msix_request_rcd_irq_common(rcd, receive_context_पूर्णांकerrupt,
					   receive_context_thपढ़ो, name);
पूर्ण

/**
 * msix_netdev_request_rcd_irq  - Helper function क्रम RCVAVAIL IRQs
 * क्रम netdev context
 * @rcd: valid netdev contexti
 */
पूर्णांक msix_netdev_request_rcd_irq(काष्ठा hfi1_ctxtdata *rcd)
अणु
	अक्षर name[MAX_NAME_SIZE];

	snम_लिखो(name, माप(name), DRIVER_NAME "_%d nd kctxt%d",
		 rcd->dd->unit, rcd->ctxt);
	वापस msix_request_rcd_irq_common(rcd, receive_context_पूर्णांकerrupt_napi,
					   शून्य, name);
पूर्ण

/**
 * msix_request_sdma_irq  - Helper क्रम getting SDMA IRQ resources
 * @sde: valid sdma engine
 *
 */
पूर्णांक msix_request_sdma_irq(काष्ठा sdma_engine *sde)
अणु
	पूर्णांक nr;
	अक्षर name[MAX_NAME_SIZE];

	snम_लिखो(name, माप(name), DRIVER_NAME "_%d sdma%d",
		 sde->dd->unit, sde->this_idx);
	nr = msix_request_irq(sde->dd, sde, sdma_पूर्णांकerrupt, शून्य,
			      IRQ_SDMA, name);
	अगर (nr < 0)
		वापस nr;
	sde->msix_पूर्णांकr = nr;
	remap_sdma_पूर्णांकerrupts(sde->dd, sde->this_idx, nr);

	वापस 0;
पूर्ण

/**
 * msix_request_general_irq - Helper क्रम getting general IRQ
 * resources
 * @dd: valid device data
 */
पूर्णांक msix_request_general_irq(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक nr;
	अक्षर name[MAX_NAME_SIZE];

	snम_लिखो(name, माप(name), DRIVER_NAME "_%d", dd->unit);
	nr = msix_request_irq(dd, dd, general_पूर्णांकerrupt, शून्य, IRQ_GENERAL,
			      name);
	अगर (nr < 0)
		वापस nr;

	/* general पूर्णांकerrupt must be MSIx vector 0 */
	अगर (nr) अणु
		msix_मुक्त_irq(dd, (u8)nr);
		dd_dev_err(dd, "Invalid index %d for GENERAL IRQ\n", nr);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * enable_sdma_srcs - Helper to enable SDMA IRQ srcs
 * @dd: valid devdata काष्ठाure
 * @i: index of SDMA engine
 */
अटल व्योम enable_sdma_srcs(काष्ठा hfi1_devdata *dd, पूर्णांक i)
अणु
	set_पूर्णांकr_bits(dd, IS_SDMA_START + i, IS_SDMA_START + i, true);
	set_पूर्णांकr_bits(dd, IS_SDMA_PROGRESS_START + i,
		      IS_SDMA_PROGRESS_START + i, true);
	set_पूर्णांकr_bits(dd, IS_SDMA_IDLE_START + i, IS_SDMA_IDLE_START + i, true);
	set_पूर्णांकr_bits(dd, IS_SDMAENG_ERR_START + i, IS_SDMAENG_ERR_START + i,
		      true);
पूर्ण

/**
 * msix_request_irqs() - Allocate all MSIx IRQs
 * @dd: valid devdata काष्ठाure
 *
 * Helper function to request the used MSIx IRQs.
 *
 */
पूर्णांक msix_request_irqs(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	पूर्णांक ret = msix_request_general_irq(dd);

	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < dd->num_sdma; i++) अणु
		काष्ठा sdma_engine *sde = &dd->per_sdma[i];

		ret = msix_request_sdma_irq(sde);
		अगर (ret)
			वापस ret;
		enable_sdma_srcs(sde->dd, i);
	पूर्ण

	क्रम (i = 0; i < dd->n_krcv_queues; i++) अणु
		काष्ठा hfi1_ctxtdata *rcd = hfi1_rcd_get_by_index_safe(dd, i);

		अगर (rcd)
			ret = msix_request_rcd_irq(rcd);
		hfi1_rcd_put(rcd);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * msix_मुक्त_irq() - Free the specअगरied MSIx resources and IRQ
 * @dd: valid devdata
 * @msix_पूर्णांकr: MSIx vector to मुक्त.
 *
 */
व्योम msix_मुक्त_irq(काष्ठा hfi1_devdata *dd, u8 msix_पूर्णांकr)
अणु
	काष्ठा hfi1_msix_entry *me;

	अगर (msix_पूर्णांकr >= dd->msix_info.max_requested)
		वापस;

	me = &dd->msix_info.msix_entries[msix_पूर्णांकr];

	अगर (!me->arg) /* => no irq, no affinity */
		वापस;

	hfi1_put_irq_affinity(dd, me);
	pci_मुक्त_irq(dd->pcidev, msix_पूर्णांकr, me->arg);

	me->arg = शून्य;

	spin_lock(&dd->msix_info.msix_lock);
	__clear_bit(msix_पूर्णांकr, dd->msix_info.in_use_msix);
	spin_unlock(&dd->msix_info.msix_lock);
पूर्ण

/**
 * msix_clean_up_पूर्णांकerrupts  - Free all MSIx IRQ resources
 * @dd: valid device data data काष्ठाure
 *
 * Free the MSIx and associated PCI resources, अगर they have been allocated.
 */
व्योम msix_clean_up_पूर्णांकerrupts(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	काष्ठा hfi1_msix_entry *me = dd->msix_info.msix_entries;

	/* हटाओ irqs - must happen beक्रमe disabling/turning off */
	क्रम (i = 0; i < dd->msix_info.max_requested; i++, me++)
		msix_मुक्त_irq(dd, i);

	/* clean काष्ठाures */
	kमुक्त(dd->msix_info.msix_entries);
	dd->msix_info.msix_entries = शून्य;
	dd->msix_info.max_requested = 0;

	pci_मुक्त_irq_vectors(dd->pcidev);
पूर्ण

/**
 * msix_netdev_synchronize_irq - netdev IRQ synchronize
 * @dd: valid devdata
 */
व्योम msix_netdev_synchronize_irq(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	पूर्णांक ctxt_count = hfi1_netdev_ctxt_count(dd);

	क्रम (i = 0; i < ctxt_count; i++) अणु
		काष्ठा hfi1_ctxtdata *rcd = hfi1_netdev_get_ctxt(dd, i);
		काष्ठा hfi1_msix_entry *me;

		me = &dd->msix_info.msix_entries[rcd->msix_पूर्णांकr];

		synchronize_irq(me->irq);
	पूर्ण
पूर्ण
