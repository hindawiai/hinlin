<शैली गुरु>
/*
 * Copyright(c) 2015 - 2020 Intel Corporation.
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

#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/xarray.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/numa.h>
#समावेश <rdma/rdma_vt.h>

#समावेश "hfi.h"
#समावेश "device.h"
#समावेश "common.h"
#समावेश "trace.h"
#समावेश "mad.h"
#समावेश "sdma.h"
#समावेश "debugfs.h"
#समावेश "verbs.h"
#समावेश "aspm.h"
#समावेश "affinity.h"
#समावेश "vnic.h"
#समावेश "exp_rcv.h"
#समावेश "netdev.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) DRIVER_NAME ": " fmt

/*
 * min buffers we want to have per context, after driver
 */
#घोषणा HFI1_MIN_USER_CTXT_BUFCNT 7

#घोषणा HFI1_MIN_EAGER_BUFFER_SIZE (4 * 1024) /* 4KB */
#घोषणा HFI1_MAX_EAGER_BUFFER_SIZE (256 * 1024) /* 256KB */

#घोषणा NUM_IB_PORTS 1

/*
 * Number of user receive contexts we are configured to use (to allow क्रम more
 * pio buffers per ctxt, etc.)  Zero means use one user context per CPU.
 */
पूर्णांक num_user_contexts = -1;
module_param_named(num_user_contexts, num_user_contexts, पूर्णांक, 0444);
MODULE_PARM_DESC(
	num_user_contexts, "Set max number of user contexts to use (default: -1 will use the real (non-HT) CPU count)");

uपूर्णांक krcvqs[RXE_NUM_DATA_VL];
पूर्णांक krcvqsset;
module_param_array(krcvqs, uपूर्णांक, &krcvqsset, S_IRUGO);
MODULE_PARM_DESC(krcvqs, "Array of the number of non-control kernel receive queues by VL");

/* computed based on above array */
अचिन्हित दीर्घ n_krcvqs;

अटल अचिन्हित hfi1_rcvarr_split = 25;
module_param_named(rcvarr_split, hfi1_rcvarr_split, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcvarr_split, "Percent of context's RcvArray entries used for Eager buffers");

अटल uपूर्णांक eager_buffer_size = (8 << 20); /* 8MB */
module_param(eager_buffer_size, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(eager_buffer_size, "Size of the eager buffers, default: 8MB");

अटल uपूर्णांक rcvhdrcnt = 2048; /* 2x the max eager buffer count */
module_param_named(rcvhdrcnt, rcvhdrcnt, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(rcvhdrcnt, "Receive header queue count (default 2048)");

अटल uपूर्णांक hfi1_hdrq_entsize = 32;
module_param_named(hdrq_entsize, hfi1_hdrq_entsize, uपूर्णांक, 0444);
MODULE_PARM_DESC(hdrq_entsize, "Size of header queue entries: 2 - 8B, 16 - 64B, 32 - 128B (default)");

अचिन्हित पूर्णांक user_credit_वापस_threshold = 33;	/* शेष is 33% */
module_param(user_credit_वापस_threshold, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(user_credit_वापस_threshold, "Credit return threshold for user send contexts, return when unreturned credits passes this many blocks (in percent of allocated blocks, 0 is off)");

DEFINE_XARRAY_FLAGS(hfi1_dev_table, XA_FLAGS_ALLOC | XA_FLAGS_LOCK_IRQ);

अटल पूर्णांक hfi1_create_kctxt(काष्ठा hfi1_devdata *dd,
			     काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	पूर्णांक ret;

	/* Control context has to be always 0 */
	BUILD_BUG_ON(HFI1_CTRL_CTXT != 0);

	ret = hfi1_create_ctxtdata(ppd, dd->node, &rcd);
	अगर (ret < 0) अणु
		dd_dev_err(dd, "Kernel receive context allocation failed\n");
		वापस ret;
	पूर्ण

	/*
	 * Set up the kernel context flags here and now because they use
	 * शेष values क्रम all receive side memories.  User contexts will
	 * be handled as they are created.
	 */
	rcd->flags = HFI1_CAP_KGET(MULTI_PKT_EGR) |
		HFI1_CAP_KGET(NODROP_RHQ_FULL) |
		HFI1_CAP_KGET(NODROP_EGR_FULL) |
		HFI1_CAP_KGET(DMA_RTAIL);

	/* Control context must use DMA_RTAIL */
	अगर (rcd->ctxt == HFI1_CTRL_CTXT)
		rcd->flags |= HFI1_CAP_DMA_RTAIL;
	rcd->fast_handler = get_dma_rtail_setting(rcd) ?
				handle_receive_पूर्णांकerrupt_dma_rtail :
				handle_receive_पूर्णांकerrupt_nodma_rtail;
	rcd->slow_handler = handle_receive_पूर्णांकerrupt;

	hfi1_set_seq_cnt(rcd, 1);

	rcd->sc = sc_alloc(dd, SC_ACK, rcd->rcvhdrqentsize, dd->node);
	अगर (!rcd->sc) अणु
		dd_dev_err(dd, "Kernel send context allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	hfi1_init_ctxt(rcd->sc);

	वापस 0;
पूर्ण

/*
 * Create the receive context array and one or more kernel contexts
 */
पूर्णांक hfi1_create_kctxts(काष्ठा hfi1_devdata *dd)
अणु
	u16 i;
	पूर्णांक ret;

	dd->rcd = kसुस्मृति_node(dd->num_rcv_contexts, माप(*dd->rcd),
			       GFP_KERNEL, dd->node);
	अगर (!dd->rcd)
		वापस -ENOMEM;

	क्रम (i = 0; i < dd->first_dyn_alloc_ctxt; ++i) अणु
		ret = hfi1_create_kctxt(dd, dd->pport);
		अगर (ret)
			जाओ bail;
	पूर्ण

	वापस 0;
bail:
	क्रम (i = 0; dd->rcd && i < dd->first_dyn_alloc_ctxt; ++i)
		hfi1_मुक्त_ctxt(dd->rcd[i]);

	/* All the contexts should be मुक्तd, मुक्त the array */
	kमुक्त(dd->rcd);
	dd->rcd = शून्य;
	वापस ret;
पूर्ण

/*
 * Helper routines क्रम the receive context reference count (rcd and uctxt).
 */
अटल व्योम hfi1_rcd_init(काष्ठा hfi1_ctxtdata *rcd)
अणु
	kref_init(&rcd->kref);
पूर्ण

/**
 * hfi1_rcd_मुक्त - When reference is zero clean up.
 * @kref: poपूर्णांकer to an initialized rcd data काष्ठाure
 *
 */
अटल व्योम hfi1_rcd_मुक्त(काष्ठा kref *kref)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hfi1_ctxtdata *rcd =
		container_of(kref, काष्ठा hfi1_ctxtdata, kref);

	spin_lock_irqsave(&rcd->dd->uctxt_lock, flags);
	rcd->dd->rcd[rcd->ctxt] = शून्य;
	spin_unlock_irqrestore(&rcd->dd->uctxt_lock, flags);

	hfi1_मुक्त_ctxtdata(rcd->dd, rcd);

	kमुक्त(rcd);
पूर्ण

/**
 * hfi1_rcd_put - decrement reference क्रम rcd
 * @rcd: poपूर्णांकer to an initialized rcd data काष्ठाure
 *
 * Use this to put a reference after the init.
 */
पूर्णांक hfi1_rcd_put(काष्ठा hfi1_ctxtdata *rcd)
अणु
	अगर (rcd)
		वापस kref_put(&rcd->kref, hfi1_rcd_मुक्त);

	वापस 0;
पूर्ण

/**
 * hfi1_rcd_get - increment reference क्रम rcd
 * @rcd: poपूर्णांकer to an initialized rcd data काष्ठाure
 *
 * Use this to get a reference after the init.
 *
 * Return : reflect kref_get_unless_zero(), which वापसs non-zero on
 * increment, otherwise 0.
 */
पूर्णांक hfi1_rcd_get(काष्ठा hfi1_ctxtdata *rcd)
अणु
	वापस kref_get_unless_zero(&rcd->kref);
पूर्ण

/**
 * allocate_rcd_index - allocate an rcd index from the rcd array
 * @dd: poपूर्णांकer to a valid devdata काष्ठाure
 * @rcd: rcd data काष्ठाure to assign
 * @index: poपूर्णांकer to index that is allocated
 *
 * Find an empty index in the rcd array, and assign the given rcd to it.
 * If the array is full, we are EBUSY.
 *
 */
अटल पूर्णांक allocate_rcd_index(काष्ठा hfi1_devdata *dd,
			      काष्ठा hfi1_ctxtdata *rcd, u16 *index)
अणु
	अचिन्हित दीर्घ flags;
	u16 ctxt;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	क्रम (ctxt = 0; ctxt < dd->num_rcv_contexts; ctxt++)
		अगर (!dd->rcd[ctxt])
			अवरोध;

	अगर (ctxt < dd->num_rcv_contexts) अणु
		rcd->ctxt = ctxt;
		dd->rcd[ctxt] = rcd;
		hfi1_rcd_init(rcd);
	पूर्ण
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	अगर (ctxt >= dd->num_rcv_contexts)
		वापस -EBUSY;

	*index = ctxt;

	वापस 0;
पूर्ण

/**
 * hfi1_rcd_get_by_index_safe - validate the ctxt index beक्रमe accessing the
 * array
 * @dd: poपूर्णांकer to a valid devdata काष्ठाure
 * @ctxt: the index of an possilbe rcd
 *
 * This is a wrapper क्रम hfi1_rcd_get_by_index() to validate that the given
 * ctxt index is valid.
 *
 * The caller is responsible क्रम making the _put().
 *
 */
काष्ठा hfi1_ctxtdata *hfi1_rcd_get_by_index_safe(काष्ठा hfi1_devdata *dd,
						 u16 ctxt)
अणु
	अगर (ctxt < dd->num_rcv_contexts)
		वापस hfi1_rcd_get_by_index(dd, ctxt);

	वापस शून्य;
पूर्ण

/**
 * hfi1_rcd_get_by_index
 * @dd: poपूर्णांकer to a valid devdata काष्ठाure
 * @ctxt: the index of an possilbe rcd
 *
 * We need to protect access to the rcd array.  If access is needed to
 * one or more index, get the protecting spinlock and then increment the
 * kref.
 *
 * The caller is responsible क्रम making the _put().
 *
 */
काष्ठा hfi1_ctxtdata *hfi1_rcd_get_by_index(काष्ठा hfi1_devdata *dd, u16 ctxt)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hfi1_ctxtdata *rcd = शून्य;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	अगर (dd->rcd[ctxt]) अणु
		rcd = dd->rcd[ctxt];
		अगर (!hfi1_rcd_get(rcd))
			rcd = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	वापस rcd;
पूर्ण

/*
 * Common code क्रम user and kernel context create and setup.
 * NOTE: the initial kref is करोne here (hf1_rcd_init()).
 */
पूर्णांक hfi1_create_ctxtdata(काष्ठा hfi1_pportdata *ppd, पूर्णांक numa,
			 काष्ठा hfi1_ctxtdata **context)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा hfi1_ctxtdata *rcd;
	अचिन्हित kctxt_ngroups = 0;
	u32 base;

	अगर (dd->rcv_entries.nctxt_extra >
	    dd->num_rcv_contexts - dd->first_dyn_alloc_ctxt)
		kctxt_ngroups = (dd->rcv_entries.nctxt_extra -
			 (dd->num_rcv_contexts - dd->first_dyn_alloc_ctxt));
	rcd = kzalloc_node(माप(*rcd), GFP_KERNEL, numa);
	अगर (rcd) अणु
		u32 rcvtids, max_entries;
		u16 ctxt;
		पूर्णांक ret;

		ret = allocate_rcd_index(dd, rcd, &ctxt);
		अगर (ret) अणु
			*context = शून्य;
			kमुक्त(rcd);
			वापस ret;
		पूर्ण

		INIT_LIST_HEAD(&rcd->qp_रुको_list);
		hfi1_exp_tid_group_init(rcd);
		rcd->ppd = ppd;
		rcd->dd = dd;
		rcd->numa_id = numa;
		rcd->rcv_array_groups = dd->rcv_entries.ngroups;
		rcd->rhf_rcv_function_map = normal_rhf_rcv_functions;
		rcd->msix_पूर्णांकr = CCE_NUM_MSIX_VECTORS;

		mutex_init(&rcd->exp_mutex);
		spin_lock_init(&rcd->exp_lock);
		INIT_LIST_HEAD(&rcd->flow_queue.queue_head);
		INIT_LIST_HEAD(&rcd->rarr_queue.queue_head);

		hfi1_cdbg(PROC, "setting up context %u\n", rcd->ctxt);

		/*
		 * Calculate the context's RcvArray entry starting poपूर्णांक.
		 * We करो this here because we have to take पूर्णांकo account all
		 * the RcvArray entries that previous context would have
		 * taken and we have to account क्रम any extra groups asचिन्हित
		 * to the अटल (kernel) or dynamic (vnic/user) contexts.
		 */
		अगर (ctxt < dd->first_dyn_alloc_ctxt) अणु
			अगर (ctxt < kctxt_ngroups) अणु
				base = ctxt * (dd->rcv_entries.ngroups + 1);
				rcd->rcv_array_groups++;
			पूर्ण अन्यथा अणु
				base = kctxt_ngroups +
					(ctxt * dd->rcv_entries.ngroups);
			पूर्ण
		पूर्ण अन्यथा अणु
			u16 ct = ctxt - dd->first_dyn_alloc_ctxt;

			base = ((dd->n_krcv_queues * dd->rcv_entries.ngroups) +
				kctxt_ngroups);
			अगर (ct < dd->rcv_entries.nctxt_extra) अणु
				base += ct * (dd->rcv_entries.ngroups + 1);
				rcd->rcv_array_groups++;
			पूर्ण अन्यथा अणु
				base += dd->rcv_entries.nctxt_extra +
					(ct * dd->rcv_entries.ngroups);
			पूर्ण
		पूर्ण
		rcd->eager_base = base * dd->rcv_entries.group_size;

		rcd->rcvhdrq_cnt = rcvhdrcnt;
		rcd->rcvhdrqentsize = hfi1_hdrq_entsize;
		rcd->rhf_offset =
			rcd->rcvhdrqentsize - माप(u64) / माप(u32);
		/*
		 * Simple Eager buffer allocation: we have alपढ़ोy pre-allocated
		 * the number of RcvArray entry groups. Each ctxtdata काष्ठाure
		 * holds the number of groups क्रम that context.
		 *
		 * To follow CSR requirements and मुख्यtain cacheline alignment,
		 * make sure all sizes and bases are multiples of group_size.
		 *
		 * The expected entry count is what is left after assigning
		 * eager.
		 */
		max_entries = rcd->rcv_array_groups *
			dd->rcv_entries.group_size;
		rcvtids = ((max_entries * hfi1_rcvarr_split) / 100);
		rcd->egrbufs.count = round_करोwn(rcvtids,
						dd->rcv_entries.group_size);
		अगर (rcd->egrbufs.count > MAX_EAGER_ENTRIES) अणु
			dd_dev_err(dd, "ctxt%u: requested too many RcvArray entries.\n",
				   rcd->ctxt);
			rcd->egrbufs.count = MAX_EAGER_ENTRIES;
		पूर्ण
		hfi1_cdbg(PROC,
			  "ctxt%u: max Eager buffer RcvArray entries: %u\n",
			  rcd->ctxt, rcd->egrbufs.count);

		/*
		 * Allocate array that will hold the eager buffer accounting
		 * data.
		 * This will allocate the maximum possible buffer count based
		 * on the value of the RcvArray split parameter.
		 * The resulting value will be rounded करोwn to the बंदst
		 * multiple of dd->rcv_entries.group_size.
		 */
		rcd->egrbufs.buffers =
			kसुस्मृति_node(rcd->egrbufs.count,
				     माप(*rcd->egrbufs.buffers),
				     GFP_KERNEL, numa);
		अगर (!rcd->egrbufs.buffers)
			जाओ bail;
		rcd->egrbufs.rcvtids =
			kसुस्मृति_node(rcd->egrbufs.count,
				     माप(*rcd->egrbufs.rcvtids),
				     GFP_KERNEL, numa);
		अगर (!rcd->egrbufs.rcvtids)
			जाओ bail;
		rcd->egrbufs.size = eager_buffer_size;
		/*
		 * The size of the buffers programmed पूर्णांकo the RcvArray
		 * entries needs to be big enough to handle the highest
		 * MTU supported.
		 */
		अगर (rcd->egrbufs.size < hfi1_max_mtu) अणु
			rcd->egrbufs.size = __roundup_घात_of_two(hfi1_max_mtu);
			hfi1_cdbg(PROC,
				  "ctxt%u: eager bufs size too small. Adjusting to %u\n",
				    rcd->ctxt, rcd->egrbufs.size);
		पूर्ण
		rcd->egrbufs.rcvtid_size = HFI1_MAX_EAGER_BUFFER_SIZE;

		/* Applicable only क्रम अटलally created kernel contexts */
		अगर (ctxt < dd->first_dyn_alloc_ctxt) अणु
			rcd->opstats = kzalloc_node(माप(*rcd->opstats),
						    GFP_KERNEL, numa);
			अगर (!rcd->opstats)
				जाओ bail;

			/* Initialize TID flow generations क्रम the context */
			hfi1_kern_init_ctxt_generations(rcd);
		पूर्ण

		*context = rcd;
		वापस 0;
	पूर्ण

bail:
	*context = शून्य;
	hfi1_मुक्त_ctxt(rcd);
	वापस -ENOMEM;
पूर्ण

/**
 * hfi1_मुक्त_ctxt
 * @rcd: poपूर्णांकer to an initialized rcd data काष्ठाure
 *
 * This wrapper is the मुक्त function that matches hfi1_create_ctxtdata().
 * When a context is करोne being used (kernel or user), this function is called
 * क्रम the "final" put to match the kref init from hf1i_create_ctxtdata().
 * Other users of the context करो a get/put sequence to make sure that the
 * काष्ठाure isn't हटाओd जबतक in use.
 */
व्योम hfi1_मुक्त_ctxt(काष्ठा hfi1_ctxtdata *rcd)
अणु
	hfi1_rcd_put(rcd);
पूर्ण

/*
 * Select the largest ccti value over all SLs to determine the पूर्णांकra-
 * packet gap क्रम the link.
 *
 * called with cca_समयr_lock held (to protect access to cca_समयr
 * array), and rcu_पढ़ो_lock() (to protect access to cc_state).
 */
व्योम set_link_ipg(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा cc_state *cc_state;
	पूर्णांक i;
	u16 cce, ccti_limit, max_ccti = 0;
	u16 shअगरt, mult;
	u64 src;
	u32 current_egress_rate; /* Mbits /sec */
	u32 max_pkt_समय;
	/*
	 * max_pkt_समय is the maximum packet egress समय in units
	 * of the fabric घड़ी period 1/(805 MHz).
	 */

	cc_state = get_cc_state(ppd);

	अगर (!cc_state)
		/*
		 * This should _never_ happen - rcu_पढ़ो_lock() is held,
		 * and set_link_ipg() should not be called अगर cc_state
		 * is शून्य.
		 */
		वापस;

	क्रम (i = 0; i < OPA_MAX_SLS; i++) अणु
		u16 ccti = ppd->cca_समयr[i].ccti;

		अगर (ccti > max_ccti)
			max_ccti = ccti;
	पूर्ण

	ccti_limit = cc_state->cct.ccti_limit;
	अगर (max_ccti > ccti_limit)
		max_ccti = ccti_limit;

	cce = cc_state->cct.entries[max_ccti].entry;
	shअगरt = (cce & 0xc000) >> 14;
	mult = (cce & 0x3fff);

	current_egress_rate = active_egress_rate(ppd);

	max_pkt_समय = egress_cycles(ppd->ibmaxlen, current_egress_rate);

	src = (max_pkt_समय >> shअगरt) * mult;

	src &= SEND_STATIC_RATE_CONTROL_CSR_SRC_RELOAD_SMASK;
	src <<= SEND_STATIC_RATE_CONTROL_CSR_SRC_RELOAD_SHIFT;

	ग_लिखो_csr(dd, SEND_STATIC_RATE_CONTROL, src);
पूर्ण

अटल क्रमागत hrसमयr_restart cca_समयr_fn(काष्ठा hrसमयr *t)
अणु
	काष्ठा cca_समयr *cca_समयr;
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक sl;
	u16 ccti_समयr, ccti_min;
	काष्ठा cc_state *cc_state;
	अचिन्हित दीर्घ flags;
	क्रमागत hrसमयr_restart ret = HRTIMER_NORESTART;

	cca_समयr = container_of(t, काष्ठा cca_समयr, hrसमयr);
	ppd = cca_समयr->ppd;
	sl = cca_समयr->sl;

	rcu_पढ़ो_lock();

	cc_state = get_cc_state(ppd);

	अगर (!cc_state) अणु
		rcu_पढ़ो_unlock();
		वापस HRTIMER_NORESTART;
	पूर्ण

	/*
	 * 1) decrement ccti क्रम SL
	 * 2) calculate IPG क्रम link (set_link_ipg())
	 * 3) restart समयr, unless ccti is at min value
	 */

	ccti_min = cc_state->cong_setting.entries[sl].ccti_min;
	ccti_समयr = cc_state->cong_setting.entries[sl].ccti_समयr;

	spin_lock_irqsave(&ppd->cca_समयr_lock, flags);

	अगर (cca_समयr->ccti > ccti_min) अणु
		cca_समयr->ccti--;
		set_link_ipg(ppd);
	पूर्ण

	अगर (cca_समयr->ccti > ccti_min) अणु
		अचिन्हित दीर्घ nsec = 1024 * ccti_समयr;
		/* ccti_समयr is in units of 1.024 usec */
		hrसमयr_क्रमward_now(t, ns_to_kसमय(nsec));
		ret = HRTIMER_RESTART;
	पूर्ण

	spin_unlock_irqrestore(&ppd->cca_समयr_lock, flags);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/*
 * Common code क्रम initializing the physical port काष्ठाure.
 */
व्योम hfi1_init_pportdata(काष्ठा pci_dev *pdev, काष्ठा hfi1_pportdata *ppd,
			 काष्ठा hfi1_devdata *dd, u8 hw_pidx, u32 port)
अणु
	पूर्णांक i;
	uपूर्णांक शेष_pkey_idx;
	काष्ठा cc_state *cc_state;

	ppd->dd = dd;
	ppd->hw_pidx = hw_pidx;
	ppd->port = port; /* IB port number, not index */
	ppd->prev_link_width = LINK_WIDTH_DEFAULT;
	/*
	 * There are C_VL_COUNT number of PortVLXmitWait counters.
	 * Adding 1 to C_VL_COUNT to include the PortXmitWait counter.
	 */
	क्रम (i = 0; i < C_VL_COUNT + 1; i++) अणु
		ppd->port_vl_xmit_रुको_last[i] = 0;
		ppd->vl_xmit_flit_cnt[i] = 0;
	पूर्ण

	शेष_pkey_idx = 1;

	ppd->pkeys[शेष_pkey_idx] = DEFAULT_P_KEY;
	ppd->part_enक्रमce |= HFI1_PART_ENFORCE_IN;

	अगर (loopback) अणु
		dd_dev_err(dd, "Faking data partition 0x8001 in idx %u\n",
			   !शेष_pkey_idx);
		ppd->pkeys[!शेष_pkey_idx] = 0x8001;
	पूर्ण

	INIT_WORK(&ppd->link_vc_work, handle_verअगरy_cap);
	INIT_WORK(&ppd->link_up_work, handle_link_up);
	INIT_WORK(&ppd->link_करोwn_work, handle_link_करोwn);
	INIT_WORK(&ppd->मुक्तze_work, handle_मुक्तze);
	INIT_WORK(&ppd->link_करोwngrade_work, handle_link_करोwngrade);
	INIT_WORK(&ppd->sma_message_work, handle_sma_message);
	INIT_WORK(&ppd->link_bounce_work, handle_link_bounce);
	INIT_DELAYED_WORK(&ppd->start_link_work, handle_start_link);
	INIT_WORK(&ppd->linkstate_active_work, receive_पूर्णांकerrupt_work);
	INIT_WORK(&ppd->qsfp_info.qsfp_work, qsfp_event);

	mutex_init(&ppd->hls_lock);
	spin_lock_init(&ppd->qsfp_info.qsfp_lock);

	ppd->qsfp_info.ppd = ppd;
	ppd->sm_trap_qp = 0x0;
	ppd->sa_qp = 0x1;

	ppd->hfi1_wq = शून्य;

	spin_lock_init(&ppd->cca_समयr_lock);

	क्रम (i = 0; i < OPA_MAX_SLS; i++) अणु
		hrसमयr_init(&ppd->cca_समयr[i].hrसमयr, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		ppd->cca_समयr[i].ppd = ppd;
		ppd->cca_समयr[i].sl = i;
		ppd->cca_समयr[i].ccti = 0;
		ppd->cca_समयr[i].hrसमयr.function = cca_समयr_fn;
	पूर्ण

	ppd->cc_max_table_entries = IB_CC_TABLE_CAP_DEFAULT;

	spin_lock_init(&ppd->cc_state_lock);
	spin_lock_init(&ppd->cc_log_lock);
	cc_state = kzalloc(माप(*cc_state), GFP_KERNEL);
	RCU_INIT_POINTER(ppd->cc_state, cc_state);
	अगर (!cc_state)
		जाओ bail;
	वापस;

bail:
	dd_dev_err(dd, "Congestion Control Agent disabled for port %d\n", port);
पूर्ण

/*
 * Do initialization क्रम device that is only needed on
 * first detect, not on resets.
 */
अटल पूर्णांक loadसमय_init(काष्ठा hfi1_devdata *dd)
अणु
	वापस 0;
पूर्ण

/**
 * init_after_reset - re-initialize after a reset
 * @dd: the hfi1_ib device
 *
 * sanity check at least some of the values after reset, and
 * ensure no receive or transmit (explicitly, in हाल reset
 * failed
 */
अटल पूर्णांक init_after_reset(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	काष्ठा hfi1_ctxtdata *rcd;
	/*
	 * Ensure chip करोes no sends or receives, tail updates, or
	 * pioavail updates जबतक we re-initialize.  This is mostly
	 * क्रम the driver data काष्ठाures, not chip रेजिस्टरs.
	 */
	क्रम (i = 0; i < dd->num_rcv_contexts; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_DIS |
			     HFI1_RCVCTRL_INTRAVAIL_DIS |
			     HFI1_RCVCTRL_TAILUPD_DIS, rcd);
		hfi1_rcd_put(rcd);
	पूर्ण
	pio_send_control(dd, PSC_GLOBAL_DISABLE);
	क्रम (i = 0; i < dd->num_send_contexts; i++)
		sc_disable(dd->send_contexts[i].sc);

	वापस 0;
पूर्ण

अटल व्योम enable_chip(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	u32 rcvmask;
	u16 i;

	/* enable PIO send */
	pio_send_control(dd, PSC_GLOBAL_ENABLE);

	/*
	 * Enable kernel ctxts' receive and receive पूर्णांकerrupt.
	 * Other ctxts करोne as user खोलोs and initializes them.
	 */
	क्रम (i = 0; i < dd->first_dyn_alloc_ctxt; ++i) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (!rcd)
			जारी;
		rcvmask = HFI1_RCVCTRL_CTXT_ENB | HFI1_RCVCTRL_INTRAVAIL_ENB;
		rcvmask |= HFI1_CAP_KGET_MASK(rcd->flags, DMA_RTAIL) ?
			HFI1_RCVCTRL_TAILUPD_ENB : HFI1_RCVCTRL_TAILUPD_DIS;
		अगर (!HFI1_CAP_KGET_MASK(rcd->flags, MULTI_PKT_EGR))
			rcvmask |= HFI1_RCVCTRL_ONE_PKT_EGR_ENB;
		अगर (HFI1_CAP_KGET_MASK(rcd->flags, NODROP_RHQ_FULL))
			rcvmask |= HFI1_RCVCTRL_NO_RHQ_DROP_ENB;
		अगर (HFI1_CAP_KGET_MASK(rcd->flags, NODROP_EGR_FULL))
			rcvmask |= HFI1_RCVCTRL_NO_EGR_DROP_ENB;
		अगर (HFI1_CAP_IS_KSET(TID_RDMA))
			rcvmask |= HFI1_RCVCTRL_TIDFLOW_ENB;
		hfi1_rcvctrl(dd, rcvmask, rcd);
		sc_enable(rcd->sc);
		hfi1_rcd_put(rcd);
	पूर्ण
पूर्ण

/**
 * create_workqueues - create per port workqueues
 * @dd: the hfi1_ib device
 */
अटल पूर्णांक create_workqueues(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक pidx;
	काष्ठा hfi1_pportdata *ppd;

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (!ppd->hfi1_wq) अणु
			ppd->hfi1_wq =
				alloc_workqueue(
				    "hfi%d_%d",
				    WQ_SYSFS | WQ_HIGHPRI | WQ_CPU_INTENSIVE |
				    WQ_MEM_RECLAIM,
				    HFI1_MAX_ACTIVE_WORKQUEUE_ENTRIES,
				    dd->unit, pidx);
			अगर (!ppd->hfi1_wq)
				जाओ wq_error;
		पूर्ण
		अगर (!ppd->link_wq) अणु
			/*
			 * Make the link workqueue single-thपढ़ोed to enक्रमce
			 * serialization.
			 */
			ppd->link_wq =
				alloc_workqueue(
				    "hfi_link_%d_%d",
				    WQ_SYSFS | WQ_MEM_RECLAIM | WQ_UNBOUND,
				    1, /* max_active */
				    dd->unit, pidx);
			अगर (!ppd->link_wq)
				जाओ wq_error;
		पूर्ण
	पूर्ण
	वापस 0;
wq_error:
	pr_err("alloc_workqueue failed for port %d\n", pidx + 1);
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (ppd->hfi1_wq) अणु
			destroy_workqueue(ppd->hfi1_wq);
			ppd->hfi1_wq = शून्य;
		पूर्ण
		अगर (ppd->link_wq) अणु
			destroy_workqueue(ppd->link_wq);
			ppd->link_wq = शून्य;
		पूर्ण
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/**
 * destroy_workqueues - destroy per port workqueues
 * @dd: the hfi1_ib device
 */
अटल व्योम destroy_workqueues(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक pidx;
	काष्ठा hfi1_pportdata *ppd;

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;

		अगर (ppd->hfi1_wq) अणु
			destroy_workqueue(ppd->hfi1_wq);
			ppd->hfi1_wq = शून्य;
		पूर्ण
		अगर (ppd->link_wq) अणु
			destroy_workqueue(ppd->link_wq);
			ppd->link_wq = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * enable_general_पूर्णांकr() - Enable the IRQs that will be handled by the
 * general पूर्णांकerrupt handler.
 * @dd: valid devdata
 *
 */
अटल व्योम enable_general_पूर्णांकr(काष्ठा hfi1_devdata *dd)
अणु
	set_पूर्णांकr_bits(dd, CCE_ERR_INT, MISC_ERR_INT, true);
	set_पूर्णांकr_bits(dd, PIO_ERR_INT, TXE_ERR_INT, true);
	set_पूर्णांकr_bits(dd, IS_SENDCTXT_ERR_START, IS_SENDCTXT_ERR_END, true);
	set_पूर्णांकr_bits(dd, PBC_INT, GPIO_ASSERT_INT, true);
	set_पूर्णांकr_bits(dd, TCRIT_INT, TCRIT_INT, true);
	set_पूर्णांकr_bits(dd, IS_DC_START, IS_DC_END, true);
	set_पूर्णांकr_bits(dd, IS_SENDCREDIT_START, IS_SENDCREDIT_END, true);
पूर्ण

/**
 * hfi1_init - करो the actual initialization sequence on the chip
 * @dd: the hfi1_ib device
 * @reinit: re-initializing, so करोn't allocate new memory
 *
 * Do the actual initialization sequence on the chip.  This is करोne
 * both from the init routine called from the PCI infraकाष्ठाure, and
 * when we reset the chip, or detect that it was reset पूर्णांकernally,
 * or it's administratively re-enabled.
 *
 * Memory allocation here and in called routines is only करोne in
 * the first हाल (reinit == 0).  We have to be careful, because even
 * without memory allocation, we need to re-ग_लिखो all the chip रेजिस्टरs
 * TIDs, etc. after the reset or enable has completed.
 */
पूर्णांक hfi1_init(काष्ठा hfi1_devdata *dd, पूर्णांक reinit)
अणु
	पूर्णांक ret = 0, pidx, lastfail = 0;
	अचिन्हित दीर्घ len;
	u16 i;
	काष्ठा hfi1_ctxtdata *rcd;
	काष्ठा hfi1_pportdata *ppd;

	/* Set up send low level handlers */
	dd->process_pio_send = hfi1_verbs_send_pio;
	dd->process_dma_send = hfi1_verbs_send_dma;
	dd->pio_अंतरभूत_send = pio_copy;
	dd->process_vnic_dma_send = hfi1_vnic_send_dma;

	अगर (is_ax(dd)) अणु
		atomic_set(&dd->drop_packet, DROP_PACKET_ON);
		dd->करो_drop = true;
	पूर्ण अन्यथा अणु
		atomic_set(&dd->drop_packet, DROP_PACKET_OFF);
		dd->करो_drop = false;
	पूर्ण

	/* make sure the link is not "up" */
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		ppd->linkup = 0;
	पूर्ण

	अगर (reinit)
		ret = init_after_reset(dd);
	अन्यथा
		ret = loadसमय_init(dd);
	अगर (ret)
		जाओ करोne;

	/* allocate dummy tail memory क्रम all receive contexts */
	dd->rcvhdrtail_dummy_kvaddr = dma_alloc_coherent(&dd->pcidev->dev,
							 माप(u64),
							 &dd->rcvhdrtail_dummy_dma,
							 GFP_KERNEL);

	अगर (!dd->rcvhdrtail_dummy_kvaddr) अणु
		dd_dev_err(dd, "cannot allocate dummy tail memory\n");
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* dd->rcd can be शून्य अगर early initialization failed */
	क्रम (i = 0; dd->rcd && i < dd->first_dyn_alloc_ctxt; ++i) अणु
		/*
		 * Set up the (kernel) rcvhdr queue and egr TIDs.  If करोing
		 * re-init, the simplest way to handle this is to मुक्त
		 * existing, and re-allocate.
		 * Need to re-create rest of ctxt 0 ctxtdata as well.
		 */
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (!rcd)
			जारी;

		rcd->करो_पूर्णांकerrupt = &handle_receive_पूर्णांकerrupt;

		lastfail = hfi1_create_rcvhdrq(dd, rcd);
		अगर (!lastfail)
			lastfail = hfi1_setup_eagerbufs(rcd);
		अगर (!lastfail)
			lastfail = hfi1_kern_exp_rcv_init(rcd, reinit);
		अगर (lastfail) अणु
			dd_dev_err(dd,
				   "failed to allocate kernel ctxt's rcvhdrq and/or egr bufs\n");
			ret = lastfail;
		पूर्ण
		/* enable IRQ */
		hfi1_rcd_put(rcd);
	पूर्ण

	/* Allocate enough memory क्रम user event notअगरication. */
	len = PAGE_ALIGN(chip_rcv_contexts(dd) * HFI1_MAX_SHARED_CTXTS *
			 माप(*dd->events));
	dd->events = vदो_स्मृति_user(len);
	अगर (!dd->events)
		dd_dev_err(dd, "Failed to allocate user events page\n");
	/*
	 * Allocate a page क्रम device and port status.
	 * Page will be shared amongst all user processes.
	 */
	dd->status = vदो_स्मृति_user(PAGE_SIZE);
	अगर (!dd->status)
		dd_dev_err(dd, "Failed to allocate dev status page\n");
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (dd->status)
			/* Currently, we only have one port */
			ppd->statusp = &dd->status->port;

		set_mtu(ppd);
	पूर्ण

	/* enable chip even अगर we have an error, so we can debug cause */
	enable_chip(dd);

करोne:
	/*
	 * Set status even अगर port serdes is not initialized
	 * so that diags will work.
	 */
	अगर (dd->status)
		dd->status->dev |= HFI1_STATUS_CHIP_PRESENT |
			HFI1_STATUS_INITTED;
	अगर (!ret) अणु
		/* enable all पूर्णांकerrupts from the chip */
		enable_general_पूर्णांकr(dd);
		init_qsfp_पूर्णांक(dd);

		/* chip is OK क्रम user apps; mark it as initialized */
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
			ppd = dd->pport + pidx;

			/*
			 * start the serdes - must be after पूर्णांकerrupts are
			 * enabled so we are notअगरied when the link goes up
			 */
			lastfail = bringup_serdes(ppd);
			अगर (lastfail)
				dd_dev_info(dd,
					    "Failed to bring up port %u\n",
					    ppd->port);

			/*
			 * Set status even अगर port serdes is not initialized
			 * so that diags will work.
			 */
			अगर (ppd->statusp)
				*ppd->statusp |= HFI1_STATUS_CHIP_PRESENT |
							HFI1_STATUS_INITTED;
			अगर (!ppd->link_speed_enabled)
				जारी;
		पूर्ण
	पूर्ण

	/* अगर ret is non-zero, we probably should करो some cleanup here... */
	वापस ret;
पूर्ण

काष्ठा hfi1_devdata *hfi1_lookup(पूर्णांक unit)
अणु
	वापस xa_load(&hfi1_dev_table, unit);
पूर्ण

/*
 * Stop the समयrs during unit shutकरोwn, or after an error late
 * in initialization.
 */
अटल व्योम stop_समयrs(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd;
	पूर्णांक pidx;

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		अगर (ppd->led_override_समयr.function) अणु
			del_समयr_sync(&ppd->led_override_समयr);
			atomic_set(&ppd->led_override_समयr_active, 0);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * shutकरोwn_device - shut करोwn a device
 * @dd: the hfi1_ib device
 *
 * This is called to make the device quiet when we are about to
 * unload the driver, and also when the device is administratively
 * disabled.   It करोes not मुक्त any data काष्ठाures.
 * Everything it करोes has to be setup again by hfi1_init(dd, 1)
 */
अटल व्योम shutकरोwn_device(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_ctxtdata *rcd;
	अचिन्हित pidx;
	पूर्णांक i;

	अगर (dd->flags & HFI1_SHUTDOWN)
		वापस;
	dd->flags |= HFI1_SHUTDOWN;

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;

		ppd->linkup = 0;
		अगर (ppd->statusp)
			*ppd->statusp &= ~(HFI1_STATUS_IB_CONF |
					   HFI1_STATUS_IB_READY);
	पूर्ण
	dd->flags &= ~HFI1_INITTED;

	/* mask and clean up पूर्णांकerrupts */
	set_पूर्णांकr_bits(dd, IS_FIRST_SOURCE, IS_LAST_SOURCE, false);
	msix_clean_up_पूर्णांकerrupts(dd);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;
		क्रम (i = 0; i < dd->num_rcv_contexts; i++) अणु
			rcd = hfi1_rcd_get_by_index(dd, i);
			hfi1_rcvctrl(dd, HFI1_RCVCTRL_TAILUPD_DIS |
				     HFI1_RCVCTRL_CTXT_DIS |
				     HFI1_RCVCTRL_INTRAVAIL_DIS |
				     HFI1_RCVCTRL_PKEY_DIS |
				     HFI1_RCVCTRL_ONE_PKT_EGR_DIS, rcd);
			hfi1_rcd_put(rcd);
		पूर्ण
		/*
		 * Gracefully stop all sends allowing any in progress to
		 * trickle out first.
		 */
		क्रम (i = 0; i < dd->num_send_contexts; i++)
			sc_flush(dd->send_contexts[i].sc);
	पूर्ण

	/*
	 * Enough क्रम anything that's going to trickle out to have actually
	 * करोne so.
	 */
	udelay(20);

	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		ppd = dd->pport + pidx;

		/* disable all contexts */
		क्रम (i = 0; i < dd->num_send_contexts; i++)
			sc_disable(dd->send_contexts[i].sc);
		/* disable the send device */
		pio_send_control(dd, PSC_GLOBAL_DISABLE);

		shutकरोwn_led_override(ppd);

		/*
		 * Clear SerdesEnable.
		 * We can't count on पूर्णांकerrupts since we are stopping.
		 */
		hfi1_quiet_serdes(ppd);
		अगर (ppd->hfi1_wq)
			flush_workqueue(ppd->hfi1_wq);
		अगर (ppd->link_wq)
			flush_workqueue(ppd->link_wq);
	पूर्ण
	sdma_निकास(dd);
पूर्ण

/**
 * hfi1_मुक्त_ctxtdata - मुक्त a context's allocated data
 * @dd: the hfi1_ib device
 * @rcd: the ctxtdata काष्ठाure
 *
 * मुक्त up any allocated data क्रम a context
 * It should never change any chip state, or global driver state.
 */
व्योम hfi1_मुक्त_ctxtdata(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd)
अणु
	u32 e;

	अगर (!rcd)
		वापस;

	अगर (rcd->rcvhdrq) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev, rcvhdrq_size(rcd),
				  rcd->rcvhdrq, rcd->rcvhdrq_dma);
		rcd->rcvhdrq = शून्य;
		अगर (hfi1_rcvhdrtail_kvaddr(rcd)) अणु
			dma_मुक्त_coherent(&dd->pcidev->dev, PAGE_SIZE,
					  (व्योम *)hfi1_rcvhdrtail_kvaddr(rcd),
					  rcd->rcvhdrqtailaddr_dma);
			rcd->rcvhdrtail_kvaddr = शून्य;
		पूर्ण
	पूर्ण

	/* all the RcvArray entries should have been cleared by now */
	kमुक्त(rcd->egrbufs.rcvtids);
	rcd->egrbufs.rcvtids = शून्य;

	क्रम (e = 0; e < rcd->egrbufs.alloced; e++) अणु
		अगर (rcd->egrbufs.buffers[e].dma)
			dma_मुक्त_coherent(&dd->pcidev->dev,
					  rcd->egrbufs.buffers[e].len,
					  rcd->egrbufs.buffers[e].addr,
					  rcd->egrbufs.buffers[e].dma);
	पूर्ण
	kमुक्त(rcd->egrbufs.buffers);
	rcd->egrbufs.alloced = 0;
	rcd->egrbufs.buffers = शून्य;

	sc_मुक्त(rcd->sc);
	rcd->sc = शून्य;

	vमुक्त(rcd->subctxt_uregbase);
	vमुक्त(rcd->subctxt_rcvegrbuf);
	vमुक्त(rcd->subctxt_rcvhdr_base);
	kमुक्त(rcd->opstats);

	rcd->subctxt_uregbase = शून्य;
	rcd->subctxt_rcvegrbuf = शून्य;
	rcd->subctxt_rcvhdr_base = शून्य;
	rcd->opstats = शून्य;
पूर्ण

/*
 * Release our hold on the shared asic data.  If we are the last one,
 * वापस the काष्ठाure to be finalized outside the lock.  Must be
 * holding hfi1_dev_table lock.
 */
अटल काष्ठा hfi1_asic_data *release_asic_data(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_asic_data *ad;
	पूर्णांक other;

	अगर (!dd->asic_data)
		वापस शून्य;
	dd->asic_data->dds[dd->hfi1_id] = शून्य;
	other = dd->hfi1_id ? 0 : 1;
	ad = dd->asic_data;
	dd->asic_data = शून्य;
	/* वापस शून्य अगर the other dd still has a link */
	वापस ad->dds[other] ? शून्य : ad;
पूर्ण

अटल व्योम finalize_asic_data(काष्ठा hfi1_devdata *dd,
			       काष्ठा hfi1_asic_data *ad)
अणु
	clean_up_i2c(dd, ad);
	kमुक्त(ad);
पूर्ण

/**
 * hfi1_मुक्त_devdata - cleans up and मुक्तs per-unit data काष्ठाure
 * @dd: poपूर्णांकer to a valid devdata काष्ठाure
 *
 * It cleans up and मुक्तs all data काष्ठाures set up by
 * by hfi1_alloc_devdata().
 */
व्योम hfi1_मुक्त_devdata(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_asic_data *ad;
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&hfi1_dev_table, flags);
	__xa_erase(&hfi1_dev_table, dd->unit);
	ad = release_asic_data(dd);
	xa_unlock_irqrestore(&hfi1_dev_table, flags);

	finalize_asic_data(dd, ad);
	मुक्त_platक्रमm_config(dd);
	rcu_barrier(); /* रुको क्रम rcu callbacks to complete */
	मुक्त_percpu(dd->पूर्णांक_counter);
	मुक्त_percpu(dd->rcv_limit);
	मुक्त_percpu(dd->send_schedule);
	मुक्त_percpu(dd->tx_opstats);
	dd->पूर्णांक_counter   = शून्य;
	dd->rcv_limit     = शून्य;
	dd->send_schedule = शून्य;
	dd->tx_opstats    = शून्य;
	kमुक्त(dd->comp_vect);
	dd->comp_vect = शून्य;
	sdma_clean(dd, dd->num_sdma);
	rvt_dealloc_device(&dd->verbs_dev.rdi);
पूर्ण

/**
 * hfi1_alloc_devdata - Allocate our primary per-unit data काष्ठाure.
 * @pdev: Valid PCI device
 * @extra: How many bytes to alloc past the शेष
 *
 * Must be करोne via verbs allocator, because the verbs cleanup process
 * both करोes cleanup and मुक्त of the data काष्ठाure.
 * "extra" is क्रम chip-specअगरic data.
 */
अटल काष्ठा hfi1_devdata *hfi1_alloc_devdata(काष्ठा pci_dev *pdev,
					       माप_प्रकार extra)
अणु
	काष्ठा hfi1_devdata *dd;
	पूर्णांक ret, nports;

	/* extra is * number of ports */
	nports = extra / माप(काष्ठा hfi1_pportdata);

	dd = (काष्ठा hfi1_devdata *)rvt_alloc_device(माप(*dd) + extra,
						     nports);
	अगर (!dd)
		वापस ERR_PTR(-ENOMEM);
	dd->num_pports = nports;
	dd->pport = (काष्ठा hfi1_pportdata *)(dd + 1);
	dd->pcidev = pdev;
	pci_set_drvdata(pdev, dd);

	ret = xa_alloc_irq(&hfi1_dev_table, &dd->unit, dd, xa_limit_32b,
			GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Could not allocate unit ID: error %d\n", -ret);
		जाओ bail;
	पूर्ण
	rvt_set_ibdev_name(&dd->verbs_dev.rdi, "%s_%d", class_name(), dd->unit);
	/*
	 * If the BIOS करोes not have the NUMA node inक्रमmation set, select
	 * NUMA 0 so we get consistent perक्रमmance.
	 */
	dd->node = pcibus_to_node(pdev->bus);
	अगर (dd->node == NUMA_NO_NODE) अणु
		dd_dev_err(dd, "Invalid PCI NUMA node. Performance may be affected\n");
		dd->node = 0;
	पूर्ण

	/*
	 * Initialize all locks क्रम the device. This needs to be as early as
	 * possible so locks are usable.
	 */
	spin_lock_init(&dd->sc_lock);
	spin_lock_init(&dd->sendctrl_lock);
	spin_lock_init(&dd->rcvctrl_lock);
	spin_lock_init(&dd->uctxt_lock);
	spin_lock_init(&dd->hfi1_diag_trans_lock);
	spin_lock_init(&dd->sc_init_lock);
	spin_lock_init(&dd->dc8051_memlock);
	seqlock_init(&dd->sc2vl_lock);
	spin_lock_init(&dd->sde_map_lock);
	spin_lock_init(&dd->pio_map_lock);
	mutex_init(&dd->dc8051_lock);
	init_रुकोqueue_head(&dd->event_queue);
	spin_lock_init(&dd->irq_src_lock);

	dd->पूर्णांक_counter = alloc_percpu(u64);
	अगर (!dd->पूर्णांक_counter) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	dd->rcv_limit = alloc_percpu(u64);
	अगर (!dd->rcv_limit) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	dd->send_schedule = alloc_percpu(u64);
	अगर (!dd->send_schedule) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	dd->tx_opstats = alloc_percpu(काष्ठा hfi1_opcode_stats_perctx);
	अगर (!dd->tx_opstats) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	dd->comp_vect = kzalloc(माप(*dd->comp_vect), GFP_KERNEL);
	अगर (!dd->comp_vect) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	atomic_set(&dd->ipoib_rsm_usr_num, 0);
	वापस dd;

bail:
	hfi1_मुक्त_devdata(dd);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Called from मुक्तze mode handlers, and from PCI error
 * reporting code.  Should be paranoid about state of
 * प्रणाली and data काष्ठाures.
 */
व्योम hfi1_disable_after_error(काष्ठा hfi1_devdata *dd)
अणु
	अगर (dd->flags & HFI1_INITTED) अणु
		u32 pidx;

		dd->flags &= ~HFI1_INITTED;
		अगर (dd->pport)
			क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
				काष्ठा hfi1_pportdata *ppd;

				ppd = dd->pport + pidx;
				अगर (dd->flags & HFI1_PRESENT)
					set_link_state(ppd, HLS_DN_DISABLE);

				अगर (ppd->statusp)
					*ppd->statusp &= ~HFI1_STATUS_IB_READY;
			पूर्ण
	पूर्ण

	/*
	 * Mark as having had an error क्रम driver, and also
	 * क्रम /sys and status word mapped to user programs.
	 * This marks unit as not usable, until reset.
	 */
	अगर (dd->status)
		dd->status->dev |= HFI1_STATUS_HWERROR;
पूर्ण

अटल व्योम हटाओ_one(काष्ठा pci_dev *);
अटल पूर्णांक init_one(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम shutकरोwn_one(काष्ठा pci_dev *);

#घोषणा DRIVER_LOAD_MSG "Intel " DRIVER_NAME " loaded: "
#घोषणा PFX DRIVER_NAME ": "

स्थिर काष्ठा pci_device_id hfi1_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL0) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL1) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, hfi1_pci_tbl);

अटल काष्ठा pci_driver hfi1_pci_driver = अणु
	.name = DRIVER_NAME,
	.probe = init_one,
	.हटाओ = हटाओ_one,
	.shutकरोwn = shutकरोwn_one,
	.id_table = hfi1_pci_tbl,
	.err_handler = &hfi1_pci_err_handler,
पूर्ण;

अटल व्योम __init compute_krcvqs(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < krcvqsset; i++)
		n_krcvqs += krcvqs[i];
पूर्ण

/*
 * Do all the generic driver unit- and chip-independent memory
 * allocation and initialization.
 */
अटल पूर्णांक __init hfi1_mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = dev_init();
	अगर (ret)
		जाओ bail;

	ret = node_affinity_init();
	अगर (ret)
		जाओ bail;

	/* validate max MTU beक्रमe any devices start */
	अगर (!valid_opa_max_mtu(hfi1_max_mtu)) अणु
		pr_err("Invalid max_mtu 0x%x, using 0x%x instead\n",
		       hfi1_max_mtu, HFI1_DEFAULT_MAX_MTU);
		hfi1_max_mtu = HFI1_DEFAULT_MAX_MTU;
	पूर्ण
	/* valid CUs run from 1-128 in घातers of 2 */
	अगर (hfi1_cu > 128 || !is_घातer_of_2(hfi1_cu))
		hfi1_cu = 1;
	/* valid credit वापस threshold is 0-100, variable is अचिन्हित */
	अगर (user_credit_वापस_threshold > 100)
		user_credit_वापस_threshold = 100;

	compute_krcvqs();
	/*
	 * sanitize receive पूर्णांकerrupt count, समय must रुको until after
	 * the hardware type is known
	 */
	अगर (rcv_पूर्णांकr_count > RCV_HDR_HEAD_COUNTER_MASK)
		rcv_पूर्णांकr_count = RCV_HDR_HEAD_COUNTER_MASK;
	/* reject invalid combinations */
	अगर (rcv_पूर्णांकr_count == 0 && rcv_पूर्णांकr_समयout == 0) अणु
		pr_err("Invalid mode: both receive interrupt count and available timeout are zero - setting interrupt count to 1\n");
		rcv_पूर्णांकr_count = 1;
	पूर्ण
	अगर (rcv_पूर्णांकr_count > 1 && rcv_पूर्णांकr_समयout == 0) अणु
		/*
		 * Aव्योम indefinite packet delivery by requiring a समयout
		 * अगर count is > 1.
		 */
		pr_err("Invalid mode: receive interrupt count greater than 1 and available timeout is zero - setting available timeout to 1\n");
		rcv_पूर्णांकr_समयout = 1;
	पूर्ण
	अगर (rcv_पूर्णांकr_dynamic && !(rcv_पूर्णांकr_count > 1 && rcv_पूर्णांकr_समयout > 0)) अणु
		/*
		 * The dynamic algorithm expects a non-zero समयout
		 * and a count > 1.
		 */
		pr_err("Invalid mode: dynamic receive interrupt mitigation with invalid count and timeout - turning dynamic off\n");
		rcv_पूर्णांकr_dynamic = 0;
	पूर्ण

	/* sanitize link CRC options */
	link_crc_mask &= SUPPORTED_CRCS;

	ret = opfn_init();
	अगर (ret < 0) अणु
		pr_err("Failed to allocate opfn_wq");
		जाओ bail_dev;
	पूर्ण

	/*
	 * These must be called beक्रमe the driver is रेजिस्टरed with
	 * the PCI subप्रणाली.
	 */
	hfi1_dbg_init();
	ret = pci_रेजिस्टर_driver(&hfi1_pci_driver);
	अगर (ret < 0) अणु
		pr_err("Unable to register driver: error %d\n", -ret);
		जाओ bail_dev;
	पूर्ण
	जाओ bail; /* all OK */

bail_dev:
	hfi1_dbg_निकास();
	dev_cleanup();
bail:
	वापस ret;
पूर्ण

module_init(hfi1_mod_init);

/*
 * Do the non-unit driver cleanup, memory मुक्त, etc. at unload.
 */
अटल व्योम __निकास hfi1_mod_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hfi1_pci_driver);
	opfn_निकास();
	node_affinity_destroy_all();
	hfi1_dbg_निकास();

	WARN_ON(!xa_empty(&hfi1_dev_table));
	dispose_firmware();	/* asymmetric with obtain_firmware() */
	dev_cleanup();
पूर्ण

module_निकास(hfi1_mod_cleanup);

/* this can only be called after a successful initialization */
अटल व्योम cleanup_device_data(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ctxt;
	पूर्णांक pidx;

	/* users can't करो anything more with chip */
	क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
		काष्ठा hfi1_pportdata *ppd = &dd->pport[pidx];
		काष्ठा cc_state *cc_state;
		पूर्णांक i;

		अगर (ppd->statusp)
			*ppd->statusp &= ~HFI1_STATUS_CHIP_PRESENT;

		क्रम (i = 0; i < OPA_MAX_SLS; i++)
			hrसमयr_cancel(&ppd->cca_समयr[i].hrसमयr);

		spin_lock(&ppd->cc_state_lock);
		cc_state = get_cc_state_रक्षित(ppd);
		RCU_INIT_POINTER(ppd->cc_state, शून्य);
		spin_unlock(&ppd->cc_state_lock);

		अगर (cc_state)
			kमुक्त_rcu(cc_state, rcu);
	पूर्ण

	मुक्त_credit_वापस(dd);

	अगर (dd->rcvhdrtail_dummy_kvaddr) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev, माप(u64),
				  (व्योम *)dd->rcvhdrtail_dummy_kvaddr,
				  dd->rcvhdrtail_dummy_dma);
		dd->rcvhdrtail_dummy_kvaddr = शून्य;
	पूर्ण

	/*
	 * Free any resources still in use (usually just kernel contexts)
	 * at unload; we करो क्रम ctxtcnt, because that's what we allocate.
	 */
	क्रम (ctxt = 0; dd->rcd && ctxt < dd->num_rcv_contexts; ctxt++) अणु
		काष्ठा hfi1_ctxtdata *rcd = dd->rcd[ctxt];

		अगर (rcd) अणु
			hfi1_मुक्त_ctxt_rcv_groups(rcd);
			hfi1_मुक्त_ctxt(rcd);
		पूर्ण
	पूर्ण

	kमुक्त(dd->rcd);
	dd->rcd = शून्य;

	मुक्त_pio_map(dd);
	/* must follow rcv context मुक्त - need to हटाओ rcv's hooks */
	क्रम (ctxt = 0; ctxt < dd->num_send_contexts; ctxt++)
		sc_मुक्त(dd->send_contexts[ctxt].sc);
	dd->num_send_contexts = 0;
	kमुक्त(dd->send_contexts);
	dd->send_contexts = शून्य;
	kमुक्त(dd->hw_to_sw);
	dd->hw_to_sw = शून्य;
	kमुक्त(dd->boardname);
	vमुक्त(dd->events);
	vमुक्त(dd->status);
पूर्ण

/*
 * Clean up on unit shutकरोwn, or error during unit load after
 * successful initialization.
 */
अटल व्योम postinit_cleanup(काष्ठा hfi1_devdata *dd)
अणु
	hfi1_start_cleanup(dd);
	hfi1_comp_vectors_clean_up(dd);
	hfi1_dev_affinity_clean_up(dd);

	hfi1_pcie_ddcleanup(dd);
	hfi1_pcie_cleanup(dd->pcidev);

	cleanup_device_data(dd);

	hfi1_मुक्त_devdata(dd);
पूर्ण

अटल पूर्णांक init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret = 0, j, pidx, initfail;
	काष्ठा hfi1_devdata *dd;
	काष्ठा hfi1_pportdata *ppd;

	/* First, lock the non-writable module parameters */
	HFI1_CAP_LOCK();

	/* Validate dev ids */
	अगर (!(ent->device == PCI_DEVICE_ID_INTEL0 ||
	      ent->device == PCI_DEVICE_ID_INTEL1)) अणु
		dev_err(&pdev->dev, "Failing on unknown Intel deviceid 0x%x\n",
			ent->device);
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	/* Allocate the dd so we can get to work */
	dd = hfi1_alloc_devdata(pdev, NUM_IB_PORTS *
				माप(काष्ठा hfi1_pportdata));
	अगर (IS_ERR(dd)) अणु
		ret = PTR_ERR(dd);
		जाओ bail;
	पूर्ण

	/* Validate some global module parameters */
	ret = hfi1_validate_rcvhdrcnt(dd, rcvhdrcnt);
	अगर (ret)
		जाओ bail;

	/* use the encoding function as a sanitization check */
	अगर (!encode_rcv_header_entry_size(hfi1_hdrq_entsize)) अणु
		dd_dev_err(dd, "Invalid HdrQ Entry size %u\n",
			   hfi1_hdrq_entsize);
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	/* The receive eager buffer size must be set beक्रमe the receive
	 * contexts are created.
	 *
	 * Set the eager buffer size.  Validate that it falls in a range
	 * allowed by the hardware - all घातers of 2 between the min and
	 * max.  The maximum valid MTU is within the eager buffer range
	 * so we करो not need to cap the max_mtu by an eager buffer size
	 * setting.
	 */
	अगर (eager_buffer_size) अणु
		अगर (!is_घातer_of_2(eager_buffer_size))
			eager_buffer_size =
				roundup_घात_of_two(eager_buffer_size);
		eager_buffer_size =
			clamp_val(eager_buffer_size,
				  MIN_EAGER_BUFFER * 8,
				  MAX_EAGER_BUFFER_TOTAL);
		dd_dev_info(dd, "Eager buffer size %u\n",
			    eager_buffer_size);
	पूर्ण अन्यथा अणु
		dd_dev_err(dd, "Invalid Eager buffer size of 0\n");
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	/* restrict value of hfi1_rcvarr_split */
	hfi1_rcvarr_split = clamp_val(hfi1_rcvarr_split, 0, 100);

	ret = hfi1_pcie_init(dd);
	अगर (ret)
		जाओ bail;

	/*
	 * Do device-specअगरic initialization, function table setup, dd
	 * allocation, etc.
	 */
	ret = hfi1_init_dd(dd);
	अगर (ret)
		जाओ clean_bail; /* error alपढ़ोy prपूर्णांकed */

	ret = create_workqueues(dd);
	अगर (ret)
		जाओ clean_bail;

	/* करो the generic initialization */
	initfail = hfi1_init(dd, 0);

	ret = hfi1_रेजिस्टर_ib_device(dd);

	/*
	 * Now पढ़ोy क्रम use.  this should be cleared whenever we
	 * detect a reset, or initiate one.  If earlier failure,
	 * we still create devices, so diags, etc. can be used
	 * to determine cause of problem.
	 */
	अगर (!initfail && !ret) अणु
		dd->flags |= HFI1_INITTED;
		/* create debufs files after init and ib रेजिस्टर */
		hfi1_dbg_ibdev_init(&dd->verbs_dev);
	पूर्ण

	j = hfi1_device_create(dd);
	अगर (j)
		dd_dev_err(dd, "Failed to create /dev devices: %d\n", -j);

	अगर (initfail || ret) अणु
		msix_clean_up_पूर्णांकerrupts(dd);
		stop_समयrs(dd);
		flush_workqueue(ib_wq);
		क्रम (pidx = 0; pidx < dd->num_pports; ++pidx) अणु
			hfi1_quiet_serdes(dd->pport + pidx);
			ppd = dd->pport + pidx;
			अगर (ppd->hfi1_wq) अणु
				destroy_workqueue(ppd->hfi1_wq);
				ppd->hfi1_wq = शून्य;
			पूर्ण
			अगर (ppd->link_wq) अणु
				destroy_workqueue(ppd->link_wq);
				ppd->link_wq = शून्य;
			पूर्ण
		पूर्ण
		अगर (!j)
			hfi1_device_हटाओ(dd);
		अगर (!ret)
			hfi1_unरेजिस्टर_ib_device(dd);
		postinit_cleanup(dd);
		अगर (initfail)
			ret = initfail;
		जाओ bail;	/* everything alपढ़ोy cleaned */
	पूर्ण

	sdma_start(dd);

	वापस 0;

clean_bail:
	hfi1_pcie_cleanup(pdev);
bail:
	वापस ret;
पूर्ण

अटल व्योम रुको_क्रम_clients(काष्ठा hfi1_devdata *dd)
अणु
	/*
	 * Remove the device init value and complete the device अगर there is
	 * no clients or रुको क्रम active clients to finish.
	 */
	अगर (atomic_dec_and_test(&dd->user_refcount))
		complete(&dd->user_comp);

	रुको_क्रम_completion(&dd->user_comp);
पूर्ण

अटल व्योम हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hfi1_devdata *dd = pci_get_drvdata(pdev);

	/* बंद debugfs files beक्रमe ib unरेजिस्टर */
	hfi1_dbg_ibdev_निकास(&dd->verbs_dev);

	/* हटाओ the /dev hfi1 पूर्णांकerface */
	hfi1_device_हटाओ(dd);

	/* रुको क्रम existing user space clients to finish */
	रुको_क्रम_clients(dd);

	/* unरेजिस्टर from IB core */
	hfi1_unरेजिस्टर_ib_device(dd);

	/* मुक्त netdev data */
	hfi1_मुक्त_rx(dd);

	/*
	 * Disable the IB link, disable पूर्णांकerrupts on the device,
	 * clear dma engines, etc.
	 */
	shutकरोwn_device(dd);
	destroy_workqueues(dd);

	stop_समयrs(dd);

	/* रुको until all of our (qsfp) queue_work() calls complete */
	flush_workqueue(ib_wq);

	postinit_cleanup(dd);
पूर्ण

अटल व्योम shutकरोwn_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hfi1_devdata *dd = pci_get_drvdata(pdev);

	shutकरोwn_device(dd);
पूर्ण

/**
 * hfi1_create_rcvhdrq - create a receive header queue
 * @dd: the hfi1_ib device
 * @rcd: the context data
 *
 * This must be contiguous memory (from an i/o perspective), and must be
 * DMA'able (which means क्रम some प्रणालीs, it will go through an IOMMU,
 * or be क्रमced पूर्णांकo a low address range).
 */
पूर्णांक hfi1_create_rcvhdrq(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_ctxtdata *rcd)
अणु
	अचिन्हित amt;

	अगर (!rcd->rcvhdrq) अणु
		gfp_t gfp_flags;

		amt = rcvhdrq_size(rcd);

		अगर (rcd->ctxt < dd->first_dyn_alloc_ctxt || rcd->is_vnic)
			gfp_flags = GFP_KERNEL;
		अन्यथा
			gfp_flags = GFP_USER;
		rcd->rcvhdrq = dma_alloc_coherent(&dd->pcidev->dev, amt,
						  &rcd->rcvhdrq_dma,
						  gfp_flags | __GFP_COMP);

		अगर (!rcd->rcvhdrq) अणु
			dd_dev_err(dd,
				   "attempt to allocate %d bytes for ctxt %u rcvhdrq failed\n",
				   amt, rcd->ctxt);
			जाओ bail;
		पूर्ण

		अगर (HFI1_CAP_KGET_MASK(rcd->flags, DMA_RTAIL) ||
		    HFI1_CAP_UGET_MASK(rcd->flags, DMA_RTAIL)) अणु
			rcd->rcvhdrtail_kvaddr = dma_alloc_coherent(&dd->pcidev->dev,
								    PAGE_SIZE,
								    &rcd->rcvhdrqtailaddr_dma,
								    gfp_flags);
			अगर (!rcd->rcvhdrtail_kvaddr)
				जाओ bail_मुक्त;
		पूर्ण
	पूर्ण

	set_hdrq_regs(rcd->dd, rcd->ctxt, rcd->rcvhdrqentsize,
		      rcd->rcvhdrq_cnt);

	वापस 0;

bail_मुक्त:
	dd_dev_err(dd,
		   "attempt to allocate 1 page for ctxt %u rcvhdrqtailaddr failed\n",
		   rcd->ctxt);
	dma_मुक्त_coherent(&dd->pcidev->dev, amt, rcd->rcvhdrq,
			  rcd->rcvhdrq_dma);
	rcd->rcvhdrq = शून्य;
bail:
	वापस -ENOMEM;
पूर्ण

/**
 * hfi1_setup_eagerbufs - llocate eager buffers, both kernel and user
 * contexts.
 * @rcd: the context we are setting up.
 *
 * Allocate the eager TID buffers and program them पूर्णांकo hip.
 * They are no दीर्घer completely contiguous, we करो multiple allocation
 * calls.  Otherwise we get the OOM code involved, by asking क्रम too
 * much per call, with disastrous results on some kernels.
 */
पूर्णांक hfi1_setup_eagerbufs(काष्ठा hfi1_ctxtdata *rcd)
अणु
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u32 max_entries, egrtop, alloced_bytes = 0;
	gfp_t gfp_flags;
	u16 order, idx = 0;
	पूर्णांक ret = 0;
	u16 round_mtu = roundup_घात_of_two(hfi1_max_mtu);

	/*
	 * GFP_USER, but without GFP_FS, so buffer cache can be
	 * coalesced (we hope); otherwise, even at order 4,
	 * heavy fileप्रणाली activity makes these fail, and we can
	 * use compound pages.
	 */
	gfp_flags = __GFP_RECLAIM | __GFP_IO | __GFP_COMP;

	/*
	 * The minimum size of the eager buffers is a groups of MTU-sized
	 * buffers.
	 * The global eager_buffer_size parameter is checked against the
	 * theoretical lower limit of the value. Here, we check against the
	 * MTU.
	 */
	अगर (rcd->egrbufs.size < (round_mtu * dd->rcv_entries.group_size))
		rcd->egrbufs.size = round_mtu * dd->rcv_entries.group_size;
	/*
	 * If using one-pkt-per-egr-buffer, lower the eager buffer
	 * size to the max MTU (page-aligned).
	 */
	अगर (!HFI1_CAP_KGET_MASK(rcd->flags, MULTI_PKT_EGR))
		rcd->egrbufs.rcvtid_size = round_mtu;

	/*
	 * Eager buffers sizes of 1MB or less require smaller TID sizes
	 * to satisfy the "multiple of 8 RcvArray entries" requirement.
	 */
	अगर (rcd->egrbufs.size <= (1 << 20))
		rcd->egrbufs.rcvtid_size = max((अचिन्हित दीर्घ)round_mtu,
			roundकरोwn_घात_of_two(rcd->egrbufs.size / 8));

	जबतक (alloced_bytes < rcd->egrbufs.size &&
	       rcd->egrbufs.alloced < rcd->egrbufs.count) अणु
		rcd->egrbufs.buffers[idx].addr =
			dma_alloc_coherent(&dd->pcidev->dev,
					   rcd->egrbufs.rcvtid_size,
					   &rcd->egrbufs.buffers[idx].dma,
					   gfp_flags);
		अगर (rcd->egrbufs.buffers[idx].addr) अणु
			rcd->egrbufs.buffers[idx].len =
				rcd->egrbufs.rcvtid_size;
			rcd->egrbufs.rcvtids[rcd->egrbufs.alloced].addr =
				rcd->egrbufs.buffers[idx].addr;
			rcd->egrbufs.rcvtids[rcd->egrbufs.alloced].dma =
				rcd->egrbufs.buffers[idx].dma;
			rcd->egrbufs.alloced++;
			alloced_bytes += rcd->egrbufs.rcvtid_size;
			idx++;
		पूर्ण अन्यथा अणु
			u32 new_size, i, j;
			u64 offset = 0;

			/*
			 * Fail the eager buffer allocation अगर:
			 *   - we are alपढ़ोy using the lowest acceptable size
			 *   - we are using one-pkt-per-egr-buffer (this implies
			 *     that we are accepting only one size)
			 */
			अगर (rcd->egrbufs.rcvtid_size == round_mtu ||
			    !HFI1_CAP_KGET_MASK(rcd->flags, MULTI_PKT_EGR)) अणु
				dd_dev_err(dd, "ctxt%u: Failed to allocate eager buffers\n",
					   rcd->ctxt);
				ret = -ENOMEM;
				जाओ bail_rcvegrbuf_phys;
			पूर्ण

			new_size = rcd->egrbufs.rcvtid_size / 2;

			/*
			 * If the first attempt to allocate memory failed, करोn't
			 * fail everything but जारी with the next lower
			 * size.
			 */
			अगर (idx == 0) अणु
				rcd->egrbufs.rcvtid_size = new_size;
				जारी;
			पूर्ण

			/*
			 * Re-partition alपढ़ोy allocated buffers to a smaller
			 * size.
			 */
			rcd->egrbufs.alloced = 0;
			क्रम (i = 0, j = 0, offset = 0; j < idx; i++) अणु
				अगर (i >= rcd->egrbufs.count)
					अवरोध;
				rcd->egrbufs.rcvtids[i].dma =
					rcd->egrbufs.buffers[j].dma + offset;
				rcd->egrbufs.rcvtids[i].addr =
					rcd->egrbufs.buffers[j].addr + offset;
				rcd->egrbufs.alloced++;
				अगर ((rcd->egrbufs.buffers[j].dma + offset +
				     new_size) ==
				    (rcd->egrbufs.buffers[j].dma +
				     rcd->egrbufs.buffers[j].len)) अणु
					j++;
					offset = 0;
				पूर्ण अन्यथा अणु
					offset += new_size;
				पूर्ण
			पूर्ण
			rcd->egrbufs.rcvtid_size = new_size;
		पूर्ण
	पूर्ण
	rcd->egrbufs.numbufs = idx;
	rcd->egrbufs.size = alloced_bytes;

	hfi1_cdbg(PROC,
		  "ctxt%u: Alloced %u rcv tid entries @ %uKB, total %uKB\n",
		  rcd->ctxt, rcd->egrbufs.alloced,
		  rcd->egrbufs.rcvtid_size / 1024, rcd->egrbufs.size / 1024);

	/*
	 * Set the contexts rcv array head update threshold to the बंदst
	 * घातer of 2 (so we can use a mask instead of modulo) below half
	 * the allocated entries.
	 */
	rcd->egrbufs.threshold =
		roundकरोwn_घात_of_two(rcd->egrbufs.alloced / 2);
	/*
	 * Compute the expected RcvArray entry base. This is करोne after
	 * allocating the eager buffers in order to maximize the
	 * expected RcvArray entries क्रम the context.
	 */
	max_entries = rcd->rcv_array_groups * dd->rcv_entries.group_size;
	egrtop = roundup(rcd->egrbufs.alloced, dd->rcv_entries.group_size);
	rcd->expected_count = max_entries - egrtop;
	अगर (rcd->expected_count > MAX_TID_PAIR_ENTRIES * 2)
		rcd->expected_count = MAX_TID_PAIR_ENTRIES * 2;

	rcd->expected_base = rcd->eager_base + egrtop;
	hfi1_cdbg(PROC, "ctxt%u: eager:%u, exp:%u, egrbase:%u, expbase:%u\n",
		  rcd->ctxt, rcd->egrbufs.alloced, rcd->expected_count,
		  rcd->eager_base, rcd->expected_base);

	अगर (!hfi1_rcvbuf_validate(rcd->egrbufs.rcvtid_size, PT_EAGER, &order)) अणु
		hfi1_cdbg(PROC,
			  "ctxt%u: current Eager buffer size is invalid %u\n",
			  rcd->ctxt, rcd->egrbufs.rcvtid_size);
		ret = -EINVAL;
		जाओ bail_rcvegrbuf_phys;
	पूर्ण

	क्रम (idx = 0; idx < rcd->egrbufs.alloced; idx++) अणु
		hfi1_put_tid(dd, rcd->eager_base + idx, PT_EAGER,
			     rcd->egrbufs.rcvtids[idx].dma, order);
		cond_resched();
	पूर्ण

	वापस 0;

bail_rcvegrbuf_phys:
	क्रम (idx = 0; idx < rcd->egrbufs.alloced &&
	     rcd->egrbufs.buffers[idx].addr;
	     idx++) अणु
		dma_मुक्त_coherent(&dd->pcidev->dev,
				  rcd->egrbufs.buffers[idx].len,
				  rcd->egrbufs.buffers[idx].addr,
				  rcd->egrbufs.buffers[idx].dma);
		rcd->egrbufs.buffers[idx].addr = शून्य;
		rcd->egrbufs.buffers[idx].dma = 0;
		rcd->egrbufs.buffers[idx].len = 0;
	पूर्ण

	वापस ret;
पूर्ण
