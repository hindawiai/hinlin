<शैली गुरु>
/*
 * Copyright(c) 2016 - 2020 Intel Corporation.
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

#समावेश <linux/hash.h>
#समावेश <linux/bitops.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_hdrs.h>
#समावेश <rdma/opa_addr.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "qp.h"
#समावेश "vt.h"
#समावेश "trace.h"

#घोषणा RVT_RWQ_COUNT_THRESHOLD 16

अटल व्योम rvt_rc_समयout(काष्ठा समयr_list *t);
अटल व्योम rvt_reset_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			 क्रमागत ib_qp_type type);

/*
 * Convert the AETH RNR समयout code पूर्णांकo the number of microseconds.
 */
अटल स्थिर u32 ib_rvt_rnr_table[32] = अणु
	655360, /* 00: 655.36 */
	10,     /* 01:    .01 */
	20,     /* 02     .02 */
	30,     /* 03:    .03 */
	40,     /* 04:    .04 */
	60,     /* 05:    .06 */
	80,     /* 06:    .08 */
	120,    /* 07:    .12 */
	160,    /* 08:    .16 */
	240,    /* 09:    .24 */
	320,    /* 0A:    .32 */
	480,    /* 0B:    .48 */
	640,    /* 0C:    .64 */
	960,    /* 0D:    .96 */
	1280,   /* 0E:   1.28 */
	1920,   /* 0F:   1.92 */
	2560,   /* 10:   2.56 */
	3840,   /* 11:   3.84 */
	5120,   /* 12:   5.12 */
	7680,   /* 13:   7.68 */
	10240,  /* 14:  10.24 */
	15360,  /* 15:  15.36 */
	20480,  /* 16:  20.48 */
	30720,  /* 17:  30.72 */
	40960,  /* 18:  40.96 */
	61440,  /* 19:  61.44 */
	81920,  /* 1A:  81.92 */
	122880, /* 1B: 122.88 */
	163840, /* 1C: 163.84 */
	245760, /* 1D: 245.76 */
	327680, /* 1E: 327.68 */
	491520  /* 1F: 491.52 */
पूर्ण;

/*
 * Note that it is OK to post send work requests in the SQE and ERR
 * states; rvt_करो_send() will process them and generate error
 * completions as per IB 1.2 C10-96.
 */
स्थिर पूर्णांक ib_rvt_state_ops[IB_QPS_ERR + 1] = अणु
	[IB_QPS_RESET] = 0,
	[IB_QPS_INIT] = RVT_POST_RECV_OK,
	[IB_QPS_RTR] = RVT_POST_RECV_OK | RVT_PROCESS_RECV_OK,
	[IB_QPS_RTS] = RVT_POST_RECV_OK | RVT_PROCESS_RECV_OK |
	    RVT_POST_SEND_OK | RVT_PROCESS_SEND_OK |
	    RVT_PROCESS_NEXT_SEND_OK,
	[IB_QPS_SQD] = RVT_POST_RECV_OK | RVT_PROCESS_RECV_OK |
	    RVT_POST_SEND_OK | RVT_PROCESS_SEND_OK,
	[IB_QPS_SQE] = RVT_POST_RECV_OK | RVT_PROCESS_RECV_OK |
	    RVT_POST_SEND_OK | RVT_FLUSH_SEND,
	[IB_QPS_ERR] = RVT_POST_RECV_OK | RVT_FLUSH_RECV |
	    RVT_POST_SEND_OK | RVT_FLUSH_SEND,
पूर्ण;
EXPORT_SYMBOL(ib_rvt_state_ops);

/* platक्रमm specअगरic: वापस the last level cache (llc) size, in KiB */
अटल पूर्णांक rvt_wss_llc_size(व्योम)
अणु
	/* assume that the boot CPU value is universal क्रम all CPUs */
	वापस boot_cpu_data.x86_cache_size;
पूर्ण

/* platक्रमm specअगरic: cacheless copy */
अटल व्योम cacheless_स_नकल(व्योम *dst, व्योम *src, माप_प्रकार n)
अणु
	/*
	 * Use the only available X64 cacheless copy.  Add a __user cast
	 * to quiet sparse.  The src agument is alपढ़ोy in the kernel so
	 * there are no security issues.  The extra fault recovery machinery
	 * is not invoked.
	 */
	__copy_user_nocache(dst, (व्योम __user *)src, n, 0);
पूर्ण

व्योम rvt_wss_निकास(काष्ठा rvt_dev_info *rdi)
अणु
	काष्ठा rvt_wss *wss = rdi->wss;

	अगर (!wss)
		वापस;

	/* coded to handle partially initialized and repeat callers */
	kमुक्त(wss->entries);
	wss->entries = शून्य;
	kमुक्त(rdi->wss);
	rdi->wss = शून्य;
पूर्ण

/*
 * rvt_wss_init - Init wss data काष्ठाures
 *
 * Return: 0 on success
 */
पूर्णांक rvt_wss_init(काष्ठा rvt_dev_info *rdi)
अणु
	अचिन्हित पूर्णांक sge_copy_mode = rdi->dparms.sge_copy_mode;
	अचिन्हित पूर्णांक wss_threshold = rdi->dparms.wss_threshold;
	अचिन्हित पूर्णांक wss_clean_period = rdi->dparms.wss_clean_period;
	दीर्घ llc_size;
	दीर्घ llc_bits;
	दीर्घ table_size;
	दीर्घ table_bits;
	काष्ठा rvt_wss *wss;
	पूर्णांक node = rdi->dparms.node;

	अगर (sge_copy_mode != RVT_SGE_COPY_ADAPTIVE) अणु
		rdi->wss = शून्य;
		वापस 0;
	पूर्ण

	rdi->wss = kzalloc_node(माप(*rdi->wss), GFP_KERNEL, node);
	अगर (!rdi->wss)
		वापस -ENOMEM;
	wss = rdi->wss;

	/* check क्रम a valid percent range - शेष to 80 अगर none or invalid */
	अगर (wss_threshold < 1 || wss_threshold > 100)
		wss_threshold = 80;

	/* reject a wildly large period */
	अगर (wss_clean_period > 1000000)
		wss_clean_period = 256;

	/* reject a zero period */
	अगर (wss_clean_period == 0)
		wss_clean_period = 1;

	/*
	 * Calculate the table size - the next घातer of 2 larger than the
	 * LLC size.  LLC size is in KiB.
	 */
	llc_size = rvt_wss_llc_size() * 1024;
	table_size = roundup_घात_of_two(llc_size);

	/* one bit per page in rounded up table */
	llc_bits = llc_size / PAGE_SIZE;
	table_bits = table_size / PAGE_SIZE;
	wss->pages_mask = table_bits - 1;
	wss->num_entries = table_bits / BITS_PER_LONG;

	wss->threshold = (llc_bits * wss_threshold) / 100;
	अगर (wss->threshold == 0)
		wss->threshold = 1;

	wss->clean_period = wss_clean_period;
	atomic_set(&wss->clean_counter, wss_clean_period);

	wss->entries = kसुस्मृति_node(wss->num_entries, माप(*wss->entries),
				    GFP_KERNEL, node);
	अगर (!wss->entries) अणु
		rvt_wss_निकास(rdi);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Advance the clean counter.  When the clean period has expired,
 * clean an entry.
 *
 * This is implemented in atomics to aव्योम locking.  Because multiple
 * variables are involved, it can be racy which can lead to slightly
 * inaccurate inक्रमmation.  Since this is only a heuristic, this is
 * OK.  Any innaccuracies will clean themselves out as the counter
 * advances.  That said, it is unlikely the entry clean operation will
 * race - the next possible racer will not start until the next clean
 * period.
 *
 * The clean counter is implemented as a decrement to zero.  When zero
 * is reached an entry is cleaned.
 */
अटल व्योम wss_advance_clean_counter(काष्ठा rvt_wss *wss)
अणु
	पूर्णांक entry;
	पूर्णांक weight;
	अचिन्हित दीर्घ bits;

	/* become the cleaner अगर we decrement the counter to zero */
	अगर (atomic_dec_and_test(&wss->clean_counter)) अणु
		/*
		 * Set, not add, the clean period.  This aव्योमs an issue
		 * where the counter could decrement below the clean period.
		 * Doing a set can result in lost decrements, slowing the
		 * clean advance.  Since this a heuristic, this possible
		 * slowकरोwn is OK.
		 *
		 * An alternative is to loop, advancing the counter by a
		 * clean period until the result is > 0. However, this could
		 * lead to several thपढ़ोs keeping another in the clean loop.
		 * This could be mitigated by limiting the number of बार
		 * we stay in the loop.
		 */
		atomic_set(&wss->clean_counter, wss->clean_period);

		/*
		 * Uniquely grab the entry to clean and move to next.
		 * The current entry is always the lower bits of
		 * wss.clean_entry.  The table size, wss.num_entries,
		 * is always a घातer-of-2.
		 */
		entry = (atomic_inc_वापस(&wss->clean_entry) - 1)
			& (wss->num_entries - 1);

		/* clear the entry and count the bits */
		bits = xchg(&wss->entries[entry], 0);
		weight = hweight64((u64)bits);
		/* only adjust the contended total count अगर needed */
		अगर (weight)
			atomic_sub(weight, &wss->total_count);
	पूर्ण
पूर्ण

/*
 * Insert the given address पूर्णांकo the working set array.
 */
अटल व्योम wss_insert(काष्ठा rvt_wss *wss, व्योम *address)
अणु
	u32 page = ((अचिन्हित दीर्घ)address >> PAGE_SHIFT) & wss->pages_mask;
	u32 entry = page / BITS_PER_LONG; /* assumes this ends up a shअगरt */
	u32 nr = page & (BITS_PER_LONG - 1);

	अगर (!test_and_set_bit(nr, &wss->entries[entry]))
		atomic_inc(&wss->total_count);

	wss_advance_clean_counter(wss);
पूर्ण

/*
 * Is the working set larger than the threshold?
 */
अटल अंतरभूत bool wss_exceeds_threshold(काष्ठा rvt_wss *wss)
अणु
	वापस atomic_पढ़ो(&wss->total_count) >= wss->threshold;
पूर्ण

अटल व्योम get_map_page(काष्ठा rvt_qpn_table *qpt,
			 काष्ठा rvt_qpn_map *map)
अणु
	अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);

	/*
	 * Free the page अगर someone raced with us installing it.
	 */

	spin_lock(&qpt->lock);
	अगर (map->page)
		मुक्त_page(page);
	अन्यथा
		map->page = (व्योम *)page;
	spin_unlock(&qpt->lock);
पूर्ण

/**
 * init_qpn_table - initialize the QP number table क्रम a device
 * @rdi: rvt dev काष्ठा
 * @qpt: the QPN table
 */
अटल पूर्णांक init_qpn_table(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qpn_table *qpt)
अणु
	u32 offset, i;
	काष्ठा rvt_qpn_map *map;
	पूर्णांक ret = 0;

	अगर (!(rdi->dparms.qpn_res_end >= rdi->dparms.qpn_res_start))
		वापस -EINVAL;

	spin_lock_init(&qpt->lock);

	qpt->last = rdi->dparms.qpn_start;
	qpt->incr = rdi->dparms.qpn_inc << rdi->dparms.qos_shअगरt;

	/*
	 * Drivers may want some QPs beyond what we need क्रम verbs let them use
	 * our qpn table. No need क्रम two. Lets go ahead and mark the biपंचांगaps
	 * क्रम those. The reserved range must be *after* the range which verbs
	 * will pick from.
	 */

	/* Figure out number of bit maps needed beक्रमe reserved range */
	qpt->nmaps = rdi->dparms.qpn_res_start / RVT_BITS_PER_PAGE;

	/* This should always be zero */
	offset = rdi->dparms.qpn_res_start & RVT_BITS_PER_PAGE_MASK;

	/* Starting with the first reserved bit map */
	map = &qpt->map[qpt->nmaps];

	rvt_pr_info(rdi, "Reserving QPNs from 0x%x to 0x%x for non-verbs use\n",
		    rdi->dparms.qpn_res_start, rdi->dparms.qpn_res_end);
	क्रम (i = rdi->dparms.qpn_res_start; i <= rdi->dparms.qpn_res_end; i++) अणु
		अगर (!map->page) अणु
			get_map_page(qpt, map);
			अगर (!map->page) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
		पूर्ण
		set_bit(offset, map->page);
		offset++;
		अगर (offset == RVT_BITS_PER_PAGE) अणु
			/* next page */
			qpt->nmaps++;
			map++;
			offset = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/**
 * मुक्त_qpn_table - मुक्त the QP number table क्रम a device
 * @qpt: the QPN table
 */
अटल व्योम मुक्त_qpn_table(काष्ठा rvt_qpn_table *qpt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(qpt->map); i++)
		मुक्त_page((अचिन्हित दीर्घ)qpt->map[i].page);
पूर्ण

/**
 * rvt_driver_qp_init - Init driver qp resources
 * @rdi: rvt dev strucutre
 *
 * Return: 0 on success
 */
पूर्णांक rvt_driver_qp_init(काष्ठा rvt_dev_info *rdi)
अणु
	पूर्णांक i;
	पूर्णांक ret = -ENOMEM;

	अगर (!rdi->dparms.qp_table_size)
		वापस -EINVAL;

	/*
	 * If driver is not करोing any QP allocation then make sure it is
	 * providing the necessary QP functions.
	 */
	अगर (!rdi->driver_f.मुक्त_all_qps ||
	    !rdi->driver_f.qp_priv_alloc ||
	    !rdi->driver_f.qp_priv_मुक्त ||
	    !rdi->driver_f.notअगरy_qp_reset ||
	    !rdi->driver_f.notअगरy_restart_rc)
		वापस -EINVAL;

	/* allocate parent object */
	rdi->qp_dev = kzalloc_node(माप(*rdi->qp_dev), GFP_KERNEL,
				   rdi->dparms.node);
	अगर (!rdi->qp_dev)
		वापस -ENOMEM;

	/* allocate hash table */
	rdi->qp_dev->qp_table_size = rdi->dparms.qp_table_size;
	rdi->qp_dev->qp_table_bits = ilog2(rdi->dparms.qp_table_size);
	rdi->qp_dev->qp_table =
		kदो_स्मृति_array_node(rdi->qp_dev->qp_table_size,
			     माप(*rdi->qp_dev->qp_table),
			     GFP_KERNEL, rdi->dparms.node);
	अगर (!rdi->qp_dev->qp_table)
		जाओ no_qp_table;

	क्रम (i = 0; i < rdi->qp_dev->qp_table_size; i++)
		RCU_INIT_POINTER(rdi->qp_dev->qp_table[i], शून्य);

	spin_lock_init(&rdi->qp_dev->qpt_lock);

	/* initialize qpn map */
	अगर (init_qpn_table(rdi, &rdi->qp_dev->qpn_table))
		जाओ fail_table;

	spin_lock_init(&rdi->n_qps_lock);

	वापस 0;

fail_table:
	kमुक्त(rdi->qp_dev->qp_table);
	मुक्त_qpn_table(&rdi->qp_dev->qpn_table);

no_qp_table:
	kमुक्त(rdi->qp_dev);

	वापस ret;
पूर्ण

/**
 * rvt_मुक्त_qp_cb - callback function to reset a qp
 * @qp: the qp to reset
 * @v: a 64-bit value
 *
 * This function resets the qp and हटाओs it from the
 * qp hash table.
 */
अटल व्योम rvt_मुक्त_qp_cb(काष्ठा rvt_qp *qp, u64 v)
अणु
	अचिन्हित पूर्णांक *qp_inuse = (अचिन्हित पूर्णांक *)v;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	/* Reset the qp and हटाओ it from the qp hash list */
	rvt_reset_qp(rdi, qp, qp->ibqp.qp_type);

	/* Increment the qp_inuse count */
	(*qp_inuse)++;
पूर्ण

/**
 * rvt_मुक्त_all_qps - check क्रम QPs still in use
 * @rdi: rvt device info काष्ठाure
 *
 * There should not be any QPs still in use.
 * Free memory क्रम table.
 * Return the number of QPs still in use.
 */
अटल अचिन्हित rvt_मुक्त_all_qps(काष्ठा rvt_dev_info *rdi)
अणु
	अचिन्हित पूर्णांक qp_inuse = 0;

	qp_inuse += rvt_mcast_tree_empty(rdi);

	rvt_qp_iter(rdi, (u64)&qp_inuse, rvt_मुक्त_qp_cb);

	वापस qp_inuse;
पूर्ण

/**
 * rvt_qp_निकास - clean up qps on device निकास
 * @rdi: rvt dev काष्ठाure
 *
 * Check क्रम qp leaks and मुक्त resources.
 */
व्योम rvt_qp_निकास(काष्ठा rvt_dev_info *rdi)
अणु
	u32 qps_inuse = rvt_मुक्त_all_qps(rdi);

	अगर (qps_inuse)
		rvt_pr_err(rdi, "QP memory leak! %u still in use\n",
			   qps_inuse);
	अगर (!rdi->qp_dev)
		वापस;

	kमुक्त(rdi->qp_dev->qp_table);
	मुक्त_qpn_table(&rdi->qp_dev->qpn_table);
	kमुक्त(rdi->qp_dev);
पूर्ण

अटल अंतरभूत अचिन्हित mk_qpn(काष्ठा rvt_qpn_table *qpt,
			      काष्ठा rvt_qpn_map *map, अचिन्हित off)
अणु
	वापस (map - qpt->map) * RVT_BITS_PER_PAGE + off;
पूर्ण

/**
 * alloc_qpn - Allocate the next available qpn or zero/one क्रम QP type
 *	       IB_QPT_SMI/IB_QPT_GSI
 * @rdi: rvt device info काष्ठाure
 * @qpt: queue pair number table poपूर्णांकer
 * @type: the QP type
 * @port_num: IB port number, 1 based, comes from core
 * @exclude_prefix: prefix of special queue pair number being allocated
 *
 * Return: The queue pair number
 */
अटल पूर्णांक alloc_qpn(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qpn_table *qpt,
		     क्रमागत ib_qp_type type, u8 port_num, u8 exclude_prefix)
अणु
	u32 i, offset, max_scan, qpn;
	काष्ठा rvt_qpn_map *map;
	u32 ret;
	u32 max_qpn = exclude_prefix == RVT_AIP_QP_PREFIX ?
		RVT_AIP_QPN_MAX : RVT_QPN_MAX;

	अगर (rdi->driver_f.alloc_qpn)
		वापस rdi->driver_f.alloc_qpn(rdi, qpt, type, port_num);

	अगर (type == IB_QPT_SMI || type == IB_QPT_GSI) अणु
		अचिन्हित n;

		ret = type == IB_QPT_GSI;
		n = 1 << (ret + 2 * (port_num - 1));
		spin_lock(&qpt->lock);
		अगर (qpt->flags & n)
			ret = -EINVAL;
		अन्यथा
			qpt->flags |= n;
		spin_unlock(&qpt->lock);
		जाओ bail;
	पूर्ण

	qpn = qpt->last + qpt->incr;
	अगर (qpn >= max_qpn)
		qpn = qpt->incr | ((qpt->last & 1) ^ 1);
	/* offset carries bit 0 */
	offset = qpn & RVT_BITS_PER_PAGE_MASK;
	map = &qpt->map[qpn / RVT_BITS_PER_PAGE];
	max_scan = qpt->nmaps - !offset;
	क्रम (i = 0;;) अणु
		अगर (unlikely(!map->page)) अणु
			get_map_page(qpt, map);
			अगर (unlikely(!map->page))
				अवरोध;
		पूर्ण
		करो अणु
			अगर (!test_and_set_bit(offset, map->page)) अणु
				qpt->last = qpn;
				ret = qpn;
				जाओ bail;
			पूर्ण
			offset += qpt->incr;
			/*
			 * This qpn might be bogus अगर offset >= BITS_PER_PAGE.
			 * That is OK.   It माला_लो re-asचिन्हित below
			 */
			qpn = mk_qpn(qpt, map, offset);
		पूर्ण जबतक (offset < RVT_BITS_PER_PAGE && qpn < RVT_QPN_MAX);
		/*
		 * In order to keep the number of pages allocated to a
		 * minimum, we scan the all existing pages beक्रमe increasing
		 * the size of the biपंचांगap table.
		 */
		अगर (++i > max_scan) अणु
			अगर (qpt->nmaps == RVT_QPNMAP_ENTRIES)
				अवरोध;
			map = &qpt->map[qpt->nmaps++];
			/* start at incr with current bit 0 */
			offset = qpt->incr | (offset & 1);
		पूर्ण अन्यथा अगर (map < &qpt->map[qpt->nmaps]) अणु
			++map;
			/* start at incr with current bit 0 */
			offset = qpt->incr | (offset & 1);
		पूर्ण अन्यथा अणु
			map = &qpt->map[0];
			/* wrap to first map page, invert bit 0 */
			offset = qpt->incr | ((offset & 1) ^ 1);
		पूर्ण
		/* there can be no set bits in low-order QoS bits */
		WARN_ON(rdi->dparms.qos_shअगरt > 1 &&
			offset & ((BIT(rdi->dparms.qos_shअगरt - 1) - 1) << 1));
		qpn = mk_qpn(qpt, map, offset);
	पूर्ण

	ret = -ENOMEM;

bail:
	वापस ret;
पूर्ण

/**
 * rvt_clear_mr_refs - Drop help mr refs
 * @qp: rvt qp data काष्ठाure
 * @clr_sends: If shoudl clear send side or not
 */
अटल व्योम rvt_clear_mr_refs(काष्ठा rvt_qp *qp, पूर्णांक clr_sends)
अणु
	अचिन्हित n;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	अगर (test_and_clear_bit(RVT_R_REWIND_SGE, &qp->r_aflags))
		rvt_put_ss(&qp->s_rdma_पढ़ो_sge);

	rvt_put_ss(&qp->r_sge);

	अगर (clr_sends) अणु
		जबतक (qp->s_last != qp->s_head) अणु
			काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, qp->s_last);

			rvt_put_qp_swqe(qp, wqe);
			अगर (++qp->s_last >= qp->s_size)
				qp->s_last = 0;
			smp_wmb(); /* see qp_set_savail */
		पूर्ण
		अगर (qp->s_rdma_mr) अणु
			rvt_put_mr(qp->s_rdma_mr);
			qp->s_rdma_mr = शून्य;
		पूर्ण
	पूर्ण

	क्रम (n = 0; qp->s_ack_queue && n < rvt_max_atomic(rdi); n++) अणु
		काष्ठा rvt_ack_entry *e = &qp->s_ack_queue[n];

		अगर (e->rdma_sge.mr) अणु
			rvt_put_mr(e->rdma_sge.mr);
			e->rdma_sge.mr = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * rvt_swqe_has_lkey - वापस true अगर lkey is used by swqe
 * @wqe: the send wqe
 * @lkey: the lkey
 *
 * Test the swqe क्रम using lkey
 */
अटल bool rvt_swqe_has_lkey(काष्ठा rvt_swqe *wqe, u32 lkey)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wqe->wr.num_sge; i++) अणु
		काष्ठा rvt_sge *sge = &wqe->sg_list[i];

		अगर (rvt_mr_has_lkey(sge->mr, lkey))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * rvt_qp_sends_has_lkey - वापस true is qp sends use lkey
 * @qp: the rvt_qp
 * @lkey: the lkey
 */
अटल bool rvt_qp_sends_has_lkey(काष्ठा rvt_qp *qp, u32 lkey)
अणु
	u32 s_last = qp->s_last;

	जबतक (s_last != qp->s_head) अणु
		काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, s_last);

		अगर (rvt_swqe_has_lkey(wqe, lkey))
			वापस true;

		अगर (++s_last >= qp->s_size)
			s_last = 0;
	पूर्ण
	अगर (qp->s_rdma_mr)
		अगर (rvt_mr_has_lkey(qp->s_rdma_mr, lkey))
			वापस true;
	वापस false;
पूर्ण

/**
 * rvt_qp_acks_has_lkey - वापस true अगर acks have lkey
 * @qp: the qp
 * @lkey: the lkey
 */
अटल bool rvt_qp_acks_has_lkey(काष्ठा rvt_qp *qp, u32 lkey)
अणु
	पूर्णांक i;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	क्रम (i = 0; qp->s_ack_queue && i < rvt_max_atomic(rdi); i++) अणु
		काष्ठा rvt_ack_entry *e = &qp->s_ack_queue[i];

		अगर (rvt_mr_has_lkey(e->rdma_sge.mr, lkey))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * rvt_qp_mr_clean - clean up remote ops क्रम lkey
 * @qp: the qp
 * @lkey: the lkey that is being de-रेजिस्टरed
 *
 * This routine checks अगर the lkey is being used by
 * the qp.
 *
 * If so, the qp is put पूर्णांकo an error state to elminate
 * any references from the qp.
 */
व्योम rvt_qp_mr_clean(काष्ठा rvt_qp *qp, u32 lkey)
अणु
	bool lastwqe = false;

	अगर (qp->ibqp.qp_type == IB_QPT_SMI ||
	    qp->ibqp.qp_type == IB_QPT_GSI)
		/* aव्योम special QPs */
		वापस;
	spin_lock_irq(&qp->r_lock);
	spin_lock(&qp->s_hlock);
	spin_lock(&qp->s_lock);

	अगर (qp->state == IB_QPS_ERR || qp->state == IB_QPS_RESET)
		जाओ check_lwqe;

	अगर (rvt_ss_has_lkey(&qp->r_sge, lkey) ||
	    rvt_qp_sends_has_lkey(qp, lkey) ||
	    rvt_qp_acks_has_lkey(qp, lkey))
		lastwqe = rvt_error_qp(qp, IB_WC_LOC_PROT_ERR);
check_lwqe:
	spin_unlock(&qp->s_lock);
	spin_unlock(&qp->s_hlock);
	spin_unlock_irq(&qp->r_lock);
	अगर (lastwqe) अणु
		काष्ठा ib_event ev;

		ev.device = qp->ibqp.device;
		ev.element.qp = &qp->ibqp;
		ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
		qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
	पूर्ण
पूर्ण

/**
 * rvt_हटाओ_qp - हटाओ qp क्रमm table
 * @rdi: rvt dev काष्ठा
 * @qp: qp to हटाओ
 *
 * Remove the QP from the table so it can't be found asynchronously by
 * the receive routine.
 */
अटल व्योम rvt_हटाओ_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp)
अणु
	काष्ठा rvt_ibport *rvp = rdi->ports[qp->port_num - 1];
	u32 n = hash_32(qp->ibqp.qp_num, rdi->qp_dev->qp_table_bits);
	अचिन्हित दीर्घ flags;
	पूर्णांक हटाओd = 1;

	spin_lock_irqsave(&rdi->qp_dev->qpt_lock, flags);

	अगर (rcu_dereference_रक्षित(rvp->qp[0],
			lockdep_is_held(&rdi->qp_dev->qpt_lock)) == qp) अणु
		RCU_INIT_POINTER(rvp->qp[0], शून्य);
	पूर्ण अन्यथा अगर (rcu_dereference_रक्षित(rvp->qp[1],
			lockdep_is_held(&rdi->qp_dev->qpt_lock)) == qp) अणु
		RCU_INIT_POINTER(rvp->qp[1], शून्य);
	पूर्ण अन्यथा अणु
		काष्ठा rvt_qp *q;
		काष्ठा rvt_qp __rcu **qpp;

		हटाओd = 0;
		qpp = &rdi->qp_dev->qp_table[n];
		क्रम (; (q = rcu_dereference_रक्षित(*qpp,
			lockdep_is_held(&rdi->qp_dev->qpt_lock))) != शून्य;
			qpp = &q->next) अणु
			अगर (q == qp) अणु
				RCU_INIT_POINTER(*qpp,
				     rcu_dereference_रक्षित(qp->next,
				     lockdep_is_held(&rdi->qp_dev->qpt_lock)));
				हटाओd = 1;
				trace_rvt_qpहटाओ(qp, n);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&rdi->qp_dev->qpt_lock, flags);
	अगर (हटाओd) अणु
		synchronize_rcu();
		rvt_put_qp(qp);
	पूर्ण
पूर्ण

/**
 * rvt_alloc_rq - allocate memory क्रम user or kernel buffer
 * @rq: receive queue data काष्ठाure
 * @size: number of request queue entries
 * @node: The NUMA node
 * @udata: True अगर user data is available or not false
 *
 * Return: If memory allocation failed, वापस -ENONEM
 * This function is used by both shared receive
 * queues and non-shared receive queues to allocate
 * memory.
 */
पूर्णांक rvt_alloc_rq(काष्ठा rvt_rq *rq, u32 size, पूर्णांक node,
		 काष्ठा ib_udata *udata)
अणु
	अगर (udata) अणु
		rq->wq = vदो_स्मृति_user(माप(काष्ठा rvt_rwq) + size);
		अगर (!rq->wq)
			जाओ bail;
		/* need kwq with no buffers */
		rq->kwq = kzalloc_node(माप(*rq->kwq), GFP_KERNEL, node);
		अगर (!rq->kwq)
			जाओ bail;
		rq->kwq->curr_wq = rq->wq->wq;
	पूर्ण अन्यथा अणु
		/* need kwq with buffers */
		rq->kwq =
			vzalloc_node(माप(काष्ठा rvt_krwq) + size, node);
		अगर (!rq->kwq)
			जाओ bail;
		rq->kwq->curr_wq = rq->kwq->wq;
	पूर्ण

	spin_lock_init(&rq->kwq->p_lock);
	spin_lock_init(&rq->kwq->c_lock);
	वापस 0;
bail:
	rvt_मुक्त_rq(rq);
	वापस -ENOMEM;
पूर्ण

/**
 * rvt_init_qp - initialize the QP state to the reset state
 * @rdi: rvt dev काष्ठा
 * @qp: the QP to init or reinit
 * @type: the QP type
 *
 * This function is called from both rvt_create_qp() and
 * rvt_reset_qp().   The dअगरference is that the reset
 * patch the necessary locks to protect against concurent
 * access.
 */
अटल व्योम rvt_init_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			क्रमागत ib_qp_type type)
अणु
	qp->remote_qpn = 0;
	qp->qkey = 0;
	qp->qp_access_flags = 0;
	qp->s_flags &= RVT_S_SIGNAL_REQ_WR;
	qp->s_hdrwords = 0;
	qp->s_wqe = शून्य;
	qp->s_draining = 0;
	qp->s_next_psn = 0;
	qp->s_last_psn = 0;
	qp->s_sending_psn = 0;
	qp->s_sending_hpsn = 0;
	qp->s_psn = 0;
	qp->r_psn = 0;
	qp->r_msn = 0;
	अगर (type == IB_QPT_RC) अणु
		qp->s_state = IB_OPCODE_RC_SEND_LAST;
		qp->r_state = IB_OPCODE_RC_SEND_LAST;
	पूर्ण अन्यथा अणु
		qp->s_state = IB_OPCODE_UC_SEND_LAST;
		qp->r_state = IB_OPCODE_UC_SEND_LAST;
	पूर्ण
	qp->s_ack_state = IB_OPCODE_RC_ACKNOWLEDGE;
	qp->r_nak_state = 0;
	qp->r_aflags = 0;
	qp->r_flags = 0;
	qp->s_head = 0;
	qp->s_tail = 0;
	qp->s_cur = 0;
	qp->s_acked = 0;
	qp->s_last = 0;
	qp->s_ssn = 1;
	qp->s_lsn = 0;
	qp->s_mig_state = IB_MIG_MIGRATED;
	qp->r_head_ack_queue = 0;
	qp->s_tail_ack_queue = 0;
	qp->s_acked_ack_queue = 0;
	qp->s_num_rd_atomic = 0;
	qp->r_sge.num_sge = 0;
	atomic_set(&qp->s_reserved_used, 0);
पूर्ण

/**
 * _rvt_reset_qp - initialize the QP state to the reset state
 * @rdi: rvt dev काष्ठा
 * @qp: the QP to reset
 * @type: the QP type
 *
 * r_lock, s_hlock, and s_lock are required to be held by the caller
 */
अटल व्योम _rvt_reset_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			  क्रमागत ib_qp_type type)
	__must_hold(&qp->s_lock)
	__must_hold(&qp->s_hlock)
	__must_hold(&qp->r_lock)
अणु
	lockdep_निश्चित_held(&qp->r_lock);
	lockdep_निश्चित_held(&qp->s_hlock);
	lockdep_निश्चित_held(&qp->s_lock);
	अगर (qp->state != IB_QPS_RESET) अणु
		qp->state = IB_QPS_RESET;

		/* Let drivers flush their रुकोlist */
		rdi->driver_f.flush_qp_रुकोers(qp);
		rvt_stop_rc_समयrs(qp);
		qp->s_flags &= ~(RVT_S_TIMER | RVT_S_ANY_WAIT);
		spin_unlock(&qp->s_lock);
		spin_unlock(&qp->s_hlock);
		spin_unlock_irq(&qp->r_lock);

		/* Stop the send queue and the retry समयr */
		rdi->driver_f.stop_send_queue(qp);
		rvt_del_समयrs_sync(qp);
		/* Wait क्रम things to stop */
		rdi->driver_f.quiesce_qp(qp);

		/* take qp out the hash and रुको क्रम it to be unused */
		rvt_हटाओ_qp(rdi, qp);

		/* grab the lock b/c it was locked at call समय */
		spin_lock_irq(&qp->r_lock);
		spin_lock(&qp->s_hlock);
		spin_lock(&qp->s_lock);

		rvt_clear_mr_refs(qp, 1);
		/*
		 * Let the driver करो any tear करोwn or re-init it needs to क्रम
		 * a qp that has been reset
		 */
		rdi->driver_f.notअगरy_qp_reset(qp);
	पूर्ण
	rvt_init_qp(rdi, qp, type);
	lockdep_निश्चित_held(&qp->r_lock);
	lockdep_निश्चित_held(&qp->s_hlock);
	lockdep_निश्चित_held(&qp->s_lock);
पूर्ण

/**
 * rvt_reset_qp - initialize the QP state to the reset state
 * @rdi: the device info
 * @qp: the QP to reset
 * @type: the QP type
 *
 * This is the wrapper function to acquire the r_lock, s_hlock, and s_lock
 * beक्रमe calling _rvt_reset_qp().
 */
अटल व्योम rvt_reset_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
			 क्रमागत ib_qp_type type)
अणु
	spin_lock_irq(&qp->r_lock);
	spin_lock(&qp->s_hlock);
	spin_lock(&qp->s_lock);
	_rvt_reset_qp(rdi, qp, type);
	spin_unlock(&qp->s_lock);
	spin_unlock(&qp->s_hlock);
	spin_unlock_irq(&qp->r_lock);
पूर्ण

/** rvt_मुक्त_qpn - Free a qpn from the bit map
 * @qpt: QP table
 * @qpn: queue pair number to मुक्त
 */
अटल व्योम rvt_मुक्त_qpn(काष्ठा rvt_qpn_table *qpt, u32 qpn)
अणु
	काष्ठा rvt_qpn_map *map;

	अगर ((qpn & RVT_AIP_QP_PREFIX_MASK) == RVT_AIP_QP_BASE)
		qpn &= RVT_AIP_QP_SUFFIX;

	map = qpt->map + (qpn & RVT_QPN_MASK) / RVT_BITS_PER_PAGE;
	अगर (map->page)
		clear_bit(qpn & RVT_BITS_PER_PAGE_MASK, map->page);
पूर्ण

/**
 * get_allowed_ops - Given a QP type वापस the appropriate allowed OP
 * @type: valid, supported, QP type
 */
अटल u8 get_allowed_ops(क्रमागत ib_qp_type type)
अणु
	वापस type == IB_QPT_RC ? IB_OPCODE_RC : type == IB_QPT_UC ?
		IB_OPCODE_UC : IB_OPCODE_UD;
पूर्ण

/**
 * मुक्त_ud_wq_attr - Clean up AH attribute cache क्रम UD QPs
 * @qp: Valid QP with allowed_ops set
 *
 * The rvt_swqe data काष्ठाure being used is a जोड़, so this is
 * only valid क्रम UD QPs.
 */
अटल व्योम मुक्त_ud_wq_attr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा rvt_swqe *wqe;
	पूर्णांक i;

	क्रम (i = 0; qp->allowed_ops == IB_OPCODE_UD && i < qp->s_size; i++) अणु
		wqe = rvt_get_swqe_ptr(qp, i);
		kमुक्त(wqe->ud_wr.attr);
		wqe->ud_wr.attr = शून्य;
	पूर्ण
पूर्ण

/**
 * alloc_ud_wq_attr - AH attribute cache क्रम UD QPs
 * @qp: Valid QP with allowed_ops set
 * @node: Numa node क्रम allocation
 *
 * The rvt_swqe data काष्ठाure being used is a जोड़, so this is
 * only valid क्रम UD QPs.
 */
अटल पूर्णांक alloc_ud_wq_attr(काष्ठा rvt_qp *qp, पूर्णांक node)
अणु
	काष्ठा rvt_swqe *wqe;
	पूर्णांक i;

	क्रम (i = 0; qp->allowed_ops == IB_OPCODE_UD && i < qp->s_size; i++) अणु
		wqe = rvt_get_swqe_ptr(qp, i);
		wqe->ud_wr.attr = kzalloc_node(माप(*wqe->ud_wr.attr),
					       GFP_KERNEL, node);
		अगर (!wqe->ud_wr.attr) अणु
			मुक्त_ud_wq_attr(qp);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rvt_create_qp - create a queue pair क्रम a device
 * @ibpd: the protection करोमुख्य who's device we create the queue pair क्रम
 * @init_attr: the attributes of the queue pair
 * @udata: user data क्रम libibverbs.so
 *
 * Queue pair creation is mostly an rvt issue. However, drivers have their own
 * unique idea of what queue pair numbers mean. For instance there is a reserved
 * range क्रम PSM.
 *
 * Return: the queue pair on success, otherwise वापसs an त्रुटि_सं.
 *
 * Called by the ib_create_qp() core verbs function.
 */
काष्ठा ib_qp *rvt_create_qp(काष्ठा ib_pd *ibpd,
			    काष्ठा ib_qp_init_attr *init_attr,
			    काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_qp *qp;
	पूर्णांक err;
	काष्ठा rvt_swqe *swq = शून्य;
	माप_प्रकार sz;
	माप_प्रकार sg_list_sz;
	काष्ठा ib_qp *ret = ERR_PTR(-ENOMEM);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibpd->device);
	व्योम *priv = शून्य;
	माप_प्रकार sqsize;
	u8 exclude_prefix = 0;

	अगर (!rdi)
		वापस ERR_PTR(-EINVAL);

	अगर (init_attr->create_flags & ~IB_QP_CREATE_NETDEV_USE)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (init_attr->cap.max_send_sge > rdi->dparms.props.max_send_sge ||
	    init_attr->cap.max_send_wr > rdi->dparms.props.max_qp_wr)
		वापस ERR_PTR(-EINVAL);

	/* Check receive queue parameters अगर no SRQ is specअगरied. */
	अगर (!init_attr->srq) अणु
		अगर (init_attr->cap.max_recv_sge >
		    rdi->dparms.props.max_recv_sge ||
		    init_attr->cap.max_recv_wr > rdi->dparms.props.max_qp_wr)
			वापस ERR_PTR(-EINVAL);

		अगर (init_attr->cap.max_send_sge +
		    init_attr->cap.max_send_wr +
		    init_attr->cap.max_recv_sge +
		    init_attr->cap.max_recv_wr == 0)
			वापस ERR_PTR(-EINVAL);
	पूर्ण
	sqsize =
		init_attr->cap.max_send_wr + 1 +
		rdi->dparms.reserved_operations;
	चयन (init_attr->qp_type) अणु
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
		अगर (init_attr->port_num == 0 ||
		    init_attr->port_num > ibpd->device->phys_port_cnt)
			वापस ERR_PTR(-EINVAL);
		fallthrough;
	हाल IB_QPT_UC:
	हाल IB_QPT_RC:
	हाल IB_QPT_UD:
		sz = काष्ठा_size(swq, sg_list, init_attr->cap.max_send_sge);
		swq = vzalloc_node(array_size(sz, sqsize), rdi->dparms.node);
		अगर (!swq)
			वापस ERR_PTR(-ENOMEM);

		sz = माप(*qp);
		sg_list_sz = 0;
		अगर (init_attr->srq) अणु
			काष्ठा rvt_srq *srq = ibsrq_to_rvtsrq(init_attr->srq);

			अगर (srq->rq.max_sge > 1)
				sg_list_sz = माप(*qp->r_sg_list) *
					(srq->rq.max_sge - 1);
		पूर्ण अन्यथा अगर (init_attr->cap.max_recv_sge > 1)
			sg_list_sz = माप(*qp->r_sg_list) *
				(init_attr->cap.max_recv_sge - 1);
		qp = kzalloc_node(sz + sg_list_sz, GFP_KERNEL,
				  rdi->dparms.node);
		अगर (!qp)
			जाओ bail_swq;
		qp->allowed_ops = get_allowed_ops(init_attr->qp_type);

		RCU_INIT_POINTER(qp->next, शून्य);
		अगर (init_attr->qp_type == IB_QPT_RC) अणु
			qp->s_ack_queue =
				kसुस्मृति_node(rvt_max_atomic(rdi),
					     माप(*qp->s_ack_queue),
					     GFP_KERNEL,
					     rdi->dparms.node);
			अगर (!qp->s_ack_queue)
				जाओ bail_qp;
		पूर्ण
		/* initialize समयrs needed क्रम rc qp */
		समयr_setup(&qp->s_समयr, rvt_rc_समयout, 0);
		hrसमयr_init(&qp->s_rnr_समयr, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		qp->s_rnr_समयr.function = rvt_rc_rnr_retry;

		/*
		 * Driver needs to set up it's निजी QP काष्ठाure and करो any
		 * initialization that is needed.
		 */
		priv = rdi->driver_f.qp_priv_alloc(rdi, qp);
		अगर (IS_ERR(priv)) अणु
			ret = priv;
			जाओ bail_qp;
		पूर्ण
		qp->priv = priv;
		qp->समयout_jअगरfies =
			usecs_to_jअगरfies((4096UL * (1UL << qp->समयout)) /
				1000UL);
		अगर (init_attr->srq) अणु
			sz = 0;
		पूर्ण अन्यथा अणु
			qp->r_rq.size = init_attr->cap.max_recv_wr + 1;
			qp->r_rq.max_sge = init_attr->cap.max_recv_sge;
			sz = (माप(काष्ठा ib_sge) * qp->r_rq.max_sge) +
				माप(काष्ठा rvt_rwqe);
			err = rvt_alloc_rq(&qp->r_rq, qp->r_rq.size * sz,
					   rdi->dparms.node, udata);
			अगर (err) अणु
				ret = ERR_PTR(err);
				जाओ bail_driver_priv;
			पूर्ण
		पूर्ण

		/*
		 * ib_create_qp() will initialize qp->ibqp
		 * except क्रम qp->ibqp.qp_num.
		 */
		spin_lock_init(&qp->r_lock);
		spin_lock_init(&qp->s_hlock);
		spin_lock_init(&qp->s_lock);
		atomic_set(&qp->refcount, 0);
		atomic_set(&qp->local_ops_pending, 0);
		init_रुकोqueue_head(&qp->रुको);
		INIT_LIST_HEAD(&qp->rspरुको);
		qp->state = IB_QPS_RESET;
		qp->s_wq = swq;
		qp->s_size = sqsize;
		qp->s_avail = init_attr->cap.max_send_wr;
		qp->s_max_sge = init_attr->cap.max_send_sge;
		अगर (init_attr->sq_sig_type == IB_SIGNAL_REQ_WR)
			qp->s_flags = RVT_S_SIGNAL_REQ_WR;
		err = alloc_ud_wq_attr(qp, rdi->dparms.node);
		अगर (err) अणु
			ret = (ERR_PTR(err));
			जाओ bail_rq_rvt;
		पूर्ण

		अगर (init_attr->create_flags & IB_QP_CREATE_NETDEV_USE)
			exclude_prefix = RVT_AIP_QP_PREFIX;

		err = alloc_qpn(rdi, &rdi->qp_dev->qpn_table,
				init_attr->qp_type,
				init_attr->port_num,
				exclude_prefix);
		अगर (err < 0) अणु
			ret = ERR_PTR(err);
			जाओ bail_rq_wq;
		पूर्ण
		qp->ibqp.qp_num = err;
		अगर (init_attr->create_flags & IB_QP_CREATE_NETDEV_USE)
			qp->ibqp.qp_num |= RVT_AIP_QP_BASE;
		qp->port_num = init_attr->port_num;
		rvt_init_qp(rdi, qp, init_attr->qp_type);
		अगर (rdi->driver_f.qp_priv_init) अणु
			err = rdi->driver_f.qp_priv_init(rdi, qp, init_attr);
			अगर (err) अणु
				ret = ERR_PTR(err);
				जाओ bail_rq_wq;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		/* Don't support raw QPs */
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	init_attr->cap.max_अंतरभूत_data = 0;

	/*
	 * Return the address of the RWQ as the offset to mmap.
	 * See rvt_mmap() क्रम details.
	 */
	अगर (udata && udata->outlen >= माप(__u64)) अणु
		अगर (!qp->r_rq.wq) अणु
			__u64 offset = 0;

			err = ib_copy_to_udata(udata, &offset,
					       माप(offset));
			अगर (err) अणु
				ret = ERR_PTR(err);
				जाओ bail_qpn;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 s = माप(काष्ठा rvt_rwq) + qp->r_rq.size * sz;

			qp->ip = rvt_create_mmap_info(rdi, s, udata,
						      qp->r_rq.wq);
			अगर (IS_ERR(qp->ip)) अणु
				ret = ERR_CAST(qp->ip);
				जाओ bail_qpn;
			पूर्ण

			err = ib_copy_to_udata(udata, &qp->ip->offset,
					       माप(qp->ip->offset));
			अगर (err) अणु
				ret = ERR_PTR(err);
				जाओ bail_ip;
			पूर्ण
		पूर्ण
		qp->pid = current->pid;
	पूर्ण

	spin_lock(&rdi->n_qps_lock);
	अगर (rdi->n_qps_allocated == rdi->dparms.props.max_qp) अणु
		spin_unlock(&rdi->n_qps_lock);
		ret = ERR_PTR(-ENOMEM);
		जाओ bail_ip;
	पूर्ण

	rdi->n_qps_allocated++;
	/*
	 * Maपूर्णांकain a busy_jअगरfies variable that will be added to the समयout
	 * period in mod_retry_समयr and add_retry_समयr. This busy jअगरfies
	 * is scaled by the number of rc qps created क्रम the device to reduce
	 * the number of समयouts occurring when there is a large number of
	 * qps. busy_jअगरfies is incremented every rc qp scaling पूर्णांकerval.
	 * The scaling पूर्णांकerval is selected based on extensive perक्रमmance
	 * evaluation of targeted workloads.
	 */
	अगर (init_attr->qp_type == IB_QPT_RC) अणु
		rdi->n_rc_qps++;
		rdi->busy_jअगरfies = rdi->n_rc_qps / RC_QP_SCALING_INTERVAL;
	पूर्ण
	spin_unlock(&rdi->n_qps_lock);

	अगर (qp->ip) अणु
		spin_lock_irq(&rdi->pending_lock);
		list_add(&qp->ip->pending_mmaps, &rdi->pending_mmaps);
		spin_unlock_irq(&rdi->pending_lock);
	पूर्ण

	ret = &qp->ibqp;

	वापस ret;

bail_ip:
	अगर (qp->ip)
		kref_put(&qp->ip->ref, rvt_release_mmap_info);

bail_qpn:
	rvt_मुक्त_qpn(&rdi->qp_dev->qpn_table, qp->ibqp.qp_num);

bail_rq_wq:
	मुक्त_ud_wq_attr(qp);

bail_rq_rvt:
	rvt_मुक्त_rq(&qp->r_rq);

bail_driver_priv:
	rdi->driver_f.qp_priv_मुक्त(rdi, qp);

bail_qp:
	kमुक्त(qp->s_ack_queue);
	kमुक्त(qp);

bail_swq:
	vमुक्त(swq);

	वापस ret;
पूर्ण

/**
 * rvt_error_qp - put a QP पूर्णांकo the error state
 * @qp: the QP to put पूर्णांकo the error state
 * @err: the receive completion error to संकेत अगर a RWQE is active
 *
 * Flushes both send and receive work queues.
 *
 * Return: true अगर last WQE event should be generated.
 * The QP r_lock and s_lock should be held and पूर्णांकerrupts disabled.
 * If we are alपढ़ोy in error state, just वापस.
 */
पूर्णांक rvt_error_qp(काष्ठा rvt_qp *qp, क्रमागत ib_wc_status err)
अणु
	काष्ठा ib_wc wc;
	पूर्णांक ret = 0;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	lockdep_निश्चित_held(&qp->r_lock);
	lockdep_निश्चित_held(&qp->s_lock);
	अगर (qp->state == IB_QPS_ERR || qp->state == IB_QPS_RESET)
		जाओ bail;

	qp->state = IB_QPS_ERR;

	अगर (qp->s_flags & (RVT_S_TIMER | RVT_S_WAIT_RNR)) अणु
		qp->s_flags &= ~(RVT_S_TIMER | RVT_S_WAIT_RNR);
		del_समयr(&qp->s_समयr);
	पूर्ण

	अगर (qp->s_flags & RVT_S_ANY_WAIT_SEND)
		qp->s_flags &= ~RVT_S_ANY_WAIT_SEND;

	rdi->driver_f.notअगरy_error_qp(qp);

	/* Schedule the sending tasklet to drain the send work queue. */
	अगर (READ_ONCE(qp->s_last) != qp->s_head)
		rdi->driver_f.schedule_send(qp);

	rvt_clear_mr_refs(qp, 0);

	स_रखो(&wc, 0, माप(wc));
	wc.qp = &qp->ibqp;
	wc.opcode = IB_WC_RECV;

	अगर (test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags)) अणु
		wc.wr_id = qp->r_wr_id;
		wc.status = err;
		rvt_cq_enter(ibcq_to_rvtcq(qp->ibqp.recv_cq), &wc, 1);
	पूर्ण
	wc.status = IB_WC_WR_FLUSH_ERR;

	अगर (qp->r_rq.kwq) अणु
		u32 head;
		u32 tail;
		काष्ठा rvt_rwq *wq = शून्य;
		काष्ठा rvt_krwq *kwq = शून्य;

		spin_lock(&qp->r_rq.kwq->c_lock);
		/* qp->ip used to validate अगर there is a  user buffer mmaped */
		अगर (qp->ip) अणु
			wq = qp->r_rq.wq;
			head = RDMA_READ_UAPI_ATOMIC(wq->head);
			tail = RDMA_READ_UAPI_ATOMIC(wq->tail);
		पूर्ण अन्यथा अणु
			kwq = qp->r_rq.kwq;
			head = kwq->head;
			tail = kwq->tail;
		पूर्ण
		/* sanity check poपूर्णांकers beक्रमe trusting them */
		अगर (head >= qp->r_rq.size)
			head = 0;
		अगर (tail >= qp->r_rq.size)
			tail = 0;
		जबतक (tail != head) अणु
			wc.wr_id = rvt_get_rwqe_ptr(&qp->r_rq, tail)->wr_id;
			अगर (++tail >= qp->r_rq.size)
				tail = 0;
			rvt_cq_enter(ibcq_to_rvtcq(qp->ibqp.recv_cq), &wc, 1);
		पूर्ण
		अगर (qp->ip)
			RDMA_WRITE_UAPI_ATOMIC(wq->tail, tail);
		अन्यथा
			kwq->tail = tail;
		spin_unlock(&qp->r_rq.kwq->c_lock);
	पूर्ण अन्यथा अगर (qp->ibqp.event_handler) अणु
		ret = 1;
	पूर्ण

bail:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rvt_error_qp);

/*
 * Put the QP पूर्णांकo the hash table.
 * The hash table holds a reference to the QP.
 */
अटल व्योम rvt_insert_qp(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp)
अणु
	काष्ठा rvt_ibport *rvp = rdi->ports[qp->port_num - 1];
	अचिन्हित दीर्घ flags;

	rvt_get_qp(qp);
	spin_lock_irqsave(&rdi->qp_dev->qpt_lock, flags);

	अगर (qp->ibqp.qp_num <= 1) अणु
		rcu_assign_poपूर्णांकer(rvp->qp[qp->ibqp.qp_num], qp);
	पूर्ण अन्यथा अणु
		u32 n = hash_32(qp->ibqp.qp_num, rdi->qp_dev->qp_table_bits);

		qp->next = rdi->qp_dev->qp_table[n];
		rcu_assign_poपूर्णांकer(rdi->qp_dev->qp_table[n], qp);
		trace_rvt_qpinsert(qp, n);
	पूर्ण

	spin_unlock_irqrestore(&rdi->qp_dev->qpt_lock, flags);
पूर्ण

/**
 * rvt_modअगरy_qp - modअगरy the attributes of a queue pair
 * @ibqp: the queue pair who's attributes we're modअगरying
 * @attr: the new attributes
 * @attr_mask: the mask of attributes to modअगरy
 * @udata: user data क्रम libibverbs.so
 *
 * Return: 0 on success, otherwise वापसs an त्रुटि_सं.
 */
पूर्णांक rvt_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		  पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);
	काष्ठा rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	क्रमागत ib_qp_state cur_state, new_state;
	काष्ठा ib_event ev;
	पूर्णांक lastwqe = 0;
	पूर्णांक mig = 0;
	पूर्णांक pmtu = 0; /* क्रम gcc warning only */
	पूर्णांक opa_ah;

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	spin_lock_irq(&qp->r_lock);
	spin_lock(&qp->s_hlock);
	spin_lock(&qp->s_lock);

	cur_state = attr_mask & IB_QP_CUR_STATE ?
		attr->cur_qp_state : qp->state;
	new_state = attr_mask & IB_QP_STATE ? attr->qp_state : cur_state;
	opa_ah = rdma_cap_opa_ah(ibqp->device, qp->port_num);

	अगर (!ib_modअगरy_qp_is_ok(cur_state, new_state, ibqp->qp_type,
				attr_mask))
		जाओ inval;

	अगर (rdi->driver_f.check_modअगरy_qp &&
	    rdi->driver_f.check_modअगरy_qp(qp, attr, attr_mask, udata))
		जाओ inval;

	अगर (attr_mask & IB_QP_AV) अणु
		अगर (opa_ah) अणु
			अगर (rdma_ah_get_dlid(&attr->ah_attr) >=
				opa_get_mcast_base(OPA_MCAST_NR))
				जाओ inval;
		पूर्ण अन्यथा अणु
			अगर (rdma_ah_get_dlid(&attr->ah_attr) >=
				be16_to_cpu(IB_MULTICAST_LID_BASE))
				जाओ inval;
		पूर्ण

		अगर (rvt_check_ah(qp->ibqp.device, &attr->ah_attr))
			जाओ inval;
	पूर्ण

	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		अगर (opa_ah) अणु
			अगर (rdma_ah_get_dlid(&attr->alt_ah_attr) >=
				opa_get_mcast_base(OPA_MCAST_NR))
				जाओ inval;
		पूर्ण अन्यथा अणु
			अगर (rdma_ah_get_dlid(&attr->alt_ah_attr) >=
				be16_to_cpu(IB_MULTICAST_LID_BASE))
				जाओ inval;
		पूर्ण

		अगर (rvt_check_ah(qp->ibqp.device, &attr->alt_ah_attr))
			जाओ inval;
		अगर (attr->alt_pkey_index >= rvt_get_npkeys(rdi))
			जाओ inval;
	पूर्ण

	अगर (attr_mask & IB_QP_PKEY_INDEX)
		अगर (attr->pkey_index >= rvt_get_npkeys(rdi))
			जाओ inval;

	अगर (attr_mask & IB_QP_MIN_RNR_TIMER)
		अगर (attr->min_rnr_समयr > 31)
			जाओ inval;

	अगर (attr_mask & IB_QP_PORT)
		अगर (qp->ibqp.qp_type == IB_QPT_SMI ||
		    qp->ibqp.qp_type == IB_QPT_GSI ||
		    attr->port_num == 0 ||
		    attr->port_num > ibqp->device->phys_port_cnt)
			जाओ inval;

	अगर (attr_mask & IB_QP_DEST_QPN)
		अगर (attr->dest_qp_num > RVT_QPN_MASK)
			जाओ inval;

	अगर (attr_mask & IB_QP_RETRY_CNT)
		अगर (attr->retry_cnt > 7)
			जाओ inval;

	अगर (attr_mask & IB_QP_RNR_RETRY)
		अगर (attr->rnr_retry > 7)
			जाओ inval;

	/*
	 * Don't allow invalid path_mtu values.  OK to set greater
	 * than the active mtu (or even the max_cap, अगर we have tuned
	 * that to a small mtu.  We'll set qp->path_mtu
	 * to the lesser of requested attribute mtu and active,
	 * क्रम packetizing messages.
	 * Note that the QP port has to be set in INIT and MTU in RTR.
	 */
	अगर (attr_mask & IB_QP_PATH_MTU) अणु
		pmtu = rdi->driver_f.get_pmtu_from_attr(rdi, qp, attr);
		अगर (pmtu < 0)
			जाओ inval;
	पूर्ण

	अगर (attr_mask & IB_QP_PATH_MIG_STATE) अणु
		अगर (attr->path_mig_state == IB_MIG_REARM) अणु
			अगर (qp->s_mig_state == IB_MIG_ARMED)
				जाओ inval;
			अगर (new_state != IB_QPS_RTS)
				जाओ inval;
		पूर्ण अन्यथा अगर (attr->path_mig_state == IB_MIG_MIGRATED) अणु
			अगर (qp->s_mig_state == IB_MIG_REARM)
				जाओ inval;
			अगर (new_state != IB_QPS_RTS && new_state != IB_QPS_SQD)
				जाओ inval;
			अगर (qp->s_mig_state == IB_MIG_ARMED)
				mig = 1;
		पूर्ण अन्यथा अणु
			जाओ inval;
		पूर्ण
	पूर्ण

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		अगर (attr->max_dest_rd_atomic > rdi->dparms.max_rdma_atomic)
			जाओ inval;

	चयन (new_state) अणु
	हाल IB_QPS_RESET:
		अगर (qp->state != IB_QPS_RESET)
			_rvt_reset_qp(rdi, qp, ibqp->qp_type);
		अवरोध;

	हाल IB_QPS_RTR:
		/* Allow event to re-trigger अगर QP set to RTR more than once */
		qp->r_flags &= ~RVT_R_COMM_EST;
		qp->state = new_state;
		अवरोध;

	हाल IB_QPS_SQD:
		qp->s_draining = qp->s_last != qp->s_cur;
		qp->state = new_state;
		अवरोध;

	हाल IB_QPS_SQE:
		अगर (qp->ibqp.qp_type == IB_QPT_RC)
			जाओ inval;
		qp->state = new_state;
		अवरोध;

	हाल IB_QPS_ERR:
		lastwqe = rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
		अवरोध;

	शेष:
		qp->state = new_state;
		अवरोध;
	पूर्ण

	अगर (attr_mask & IB_QP_PKEY_INDEX)
		qp->s_pkey_index = attr->pkey_index;

	अगर (attr_mask & IB_QP_PORT)
		qp->port_num = attr->port_num;

	अगर (attr_mask & IB_QP_DEST_QPN)
		qp->remote_qpn = attr->dest_qp_num;

	अगर (attr_mask & IB_QP_SQ_PSN) अणु
		qp->s_next_psn = attr->sq_psn & rdi->dparms.psn_modअगरy_mask;
		qp->s_psn = qp->s_next_psn;
		qp->s_sending_psn = qp->s_next_psn;
		qp->s_last_psn = qp->s_next_psn - 1;
		qp->s_sending_hpsn = qp->s_last_psn;
	पूर्ण

	अगर (attr_mask & IB_QP_RQ_PSN)
		qp->r_psn = attr->rq_psn & rdi->dparms.psn_modअगरy_mask;

	अगर (attr_mask & IB_QP_ACCESS_FLAGS)
		qp->qp_access_flags = attr->qp_access_flags;

	अगर (attr_mask & IB_QP_AV) अणु
		rdma_replace_ah_attr(&qp->remote_ah_attr, &attr->ah_attr);
		qp->s_srate = rdma_ah_get_अटल_rate(&attr->ah_attr);
		qp->srate_mbps = ib_rate_to_mbps(qp->s_srate);
	पूर्ण

	अगर (attr_mask & IB_QP_ALT_PATH) अणु
		rdma_replace_ah_attr(&qp->alt_ah_attr, &attr->alt_ah_attr);
		qp->s_alt_pkey_index = attr->alt_pkey_index;
	पूर्ण

	अगर (attr_mask & IB_QP_PATH_MIG_STATE) अणु
		qp->s_mig_state = attr->path_mig_state;
		अगर (mig) अणु
			qp->remote_ah_attr = qp->alt_ah_attr;
			qp->port_num = rdma_ah_get_port_num(&qp->alt_ah_attr);
			qp->s_pkey_index = qp->s_alt_pkey_index;
		पूर्ण
	पूर्ण

	अगर (attr_mask & IB_QP_PATH_MTU) अणु
		qp->pmtu = rdi->driver_f.mtu_from_qp(rdi, qp, pmtu);
		qp->log_pmtu = ilog2(qp->pmtu);
	पूर्ण

	अगर (attr_mask & IB_QP_RETRY_CNT) अणु
		qp->s_retry_cnt = attr->retry_cnt;
		qp->s_retry = attr->retry_cnt;
	पूर्ण

	अगर (attr_mask & IB_QP_RNR_RETRY) अणु
		qp->s_rnr_retry_cnt = attr->rnr_retry;
		qp->s_rnr_retry = attr->rnr_retry;
	पूर्ण

	अगर (attr_mask & IB_QP_MIN_RNR_TIMER)
		qp->r_min_rnr_समयr = attr->min_rnr_समयr;

	अगर (attr_mask & IB_QP_TIMEOUT) अणु
		qp->समयout = attr->समयout;
		qp->समयout_jअगरfies = rvt_समयout_to_jअगरfies(qp->समयout);
	पूर्ण

	अगर (attr_mask & IB_QP_QKEY)
		qp->qkey = attr->qkey;

	अगर (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC)
		qp->r_max_rd_atomic = attr->max_dest_rd_atomic;

	अगर (attr_mask & IB_QP_MAX_QP_RD_ATOMIC)
		qp->s_max_rd_atomic = attr->max_rd_atomic;

	अगर (rdi->driver_f.modअगरy_qp)
		rdi->driver_f.modअगरy_qp(qp, attr, attr_mask, udata);

	spin_unlock(&qp->s_lock);
	spin_unlock(&qp->s_hlock);
	spin_unlock_irq(&qp->r_lock);

	अगर (cur_state == IB_QPS_RESET && new_state == IB_QPS_INIT)
		rvt_insert_qp(rdi, qp);

	अगर (lastwqe) अणु
		ev.device = qp->ibqp.device;
		ev.element.qp = &qp->ibqp;
		ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
		qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
	पूर्ण
	अगर (mig) अणु
		ev.device = qp->ibqp.device;
		ev.element.qp = &qp->ibqp;
		ev.event = IB_EVENT_PATH_MIG;
		qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
	पूर्ण
	वापस 0;

inval:
	spin_unlock(&qp->s_lock);
	spin_unlock(&qp->s_hlock);
	spin_unlock_irq(&qp->r_lock);
	वापस -EINVAL;
पूर्ण

/**
 * rvt_destroy_qp - destroy a queue pair
 * @ibqp: the queue pair to destroy
 * @udata: unused by the driver
 *
 * Note that this can be called जबतक the QP is actively sending or
 * receiving!
 *
 * Return: 0 on success.
 */
पूर्णांक rvt_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	rvt_reset_qp(rdi, qp, ibqp->qp_type);

	रुको_event(qp->रुको, !atomic_पढ़ो(&qp->refcount));
	/* qpn is now available क्रम use again */
	rvt_मुक्त_qpn(&rdi->qp_dev->qpn_table, qp->ibqp.qp_num);

	spin_lock(&rdi->n_qps_lock);
	rdi->n_qps_allocated--;
	अगर (qp->ibqp.qp_type == IB_QPT_RC) अणु
		rdi->n_rc_qps--;
		rdi->busy_jअगरfies = rdi->n_rc_qps / RC_QP_SCALING_INTERVAL;
	पूर्ण
	spin_unlock(&rdi->n_qps_lock);

	अगर (qp->ip)
		kref_put(&qp->ip->ref, rvt_release_mmap_info);
	kvमुक्त(qp->r_rq.kwq);
	rdi->driver_f.qp_priv_मुक्त(rdi, qp);
	kमुक्त(qp->s_ack_queue);
	rdma_destroy_ah_attr(&qp->remote_ah_attr);
	rdma_destroy_ah_attr(&qp->alt_ah_attr);
	मुक्त_ud_wq_attr(qp);
	vमुक्त(qp->s_wq);
	kमुक्त(qp);
	वापस 0;
पूर्ण

/**
 * rvt_query_qp - query an ipbq
 * @ibqp: IB qp to query
 * @attr: attr काष्ठा to fill in
 * @attr_mask: attr mask ignored
 * @init_attr: काष्ठा to fill in
 *
 * Return: always 0
 */
पूर्णांक rvt_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		 पूर्णांक attr_mask, काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	attr->qp_state = qp->state;
	attr->cur_qp_state = attr->qp_state;
	attr->path_mtu = rdi->driver_f.mtu_to_path_mtu(qp->pmtu);
	attr->path_mig_state = qp->s_mig_state;
	attr->qkey = qp->qkey;
	attr->rq_psn = qp->r_psn & rdi->dparms.psn_mask;
	attr->sq_psn = qp->s_next_psn & rdi->dparms.psn_mask;
	attr->dest_qp_num = qp->remote_qpn;
	attr->qp_access_flags = qp->qp_access_flags;
	attr->cap.max_send_wr = qp->s_size - 1 -
		rdi->dparms.reserved_operations;
	attr->cap.max_recv_wr = qp->ibqp.srq ? 0 : qp->r_rq.size - 1;
	attr->cap.max_send_sge = qp->s_max_sge;
	attr->cap.max_recv_sge = qp->r_rq.max_sge;
	attr->cap.max_अंतरभूत_data = 0;
	attr->ah_attr = qp->remote_ah_attr;
	attr->alt_ah_attr = qp->alt_ah_attr;
	attr->pkey_index = qp->s_pkey_index;
	attr->alt_pkey_index = qp->s_alt_pkey_index;
	attr->en_sqd_async_notअगरy = 0;
	attr->sq_draining = qp->s_draining;
	attr->max_rd_atomic = qp->s_max_rd_atomic;
	attr->max_dest_rd_atomic = qp->r_max_rd_atomic;
	attr->min_rnr_समयr = qp->r_min_rnr_समयr;
	attr->port_num = qp->port_num;
	attr->समयout = qp->समयout;
	attr->retry_cnt = qp->s_retry_cnt;
	attr->rnr_retry = qp->s_rnr_retry_cnt;
	attr->alt_port_num =
		rdma_ah_get_port_num(&qp->alt_ah_attr);
	attr->alt_समयout = qp->alt_समयout;

	init_attr->event_handler = qp->ibqp.event_handler;
	init_attr->qp_context = qp->ibqp.qp_context;
	init_attr->send_cq = qp->ibqp.send_cq;
	init_attr->recv_cq = qp->ibqp.recv_cq;
	init_attr->srq = qp->ibqp.srq;
	init_attr->cap = attr->cap;
	अगर (qp->s_flags & RVT_S_SIGNAL_REQ_WR)
		init_attr->sq_sig_type = IB_SIGNAL_REQ_WR;
	अन्यथा
		init_attr->sq_sig_type = IB_SIGNAL_ALL_WR;
	init_attr->qp_type = qp->ibqp.qp_type;
	init_attr->port_num = qp->port_num;
	वापस 0;
पूर्ण

/**
 * rvt_post_recv - post a receive on a QP
 * @ibqp: the QP to post the receive on
 * @wr: the WR to post
 * @bad_wr: the first bad WR is put here
 *
 * This may be called from पूर्णांकerrupt context.
 *
 * Return: 0 on success otherwise त्रुटि_सं
 */
पूर्णांक rvt_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		  स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	काष्ठा rvt_krwq *wq = qp->r_rq.kwq;
	अचिन्हित दीर्घ flags;
	पूर्णांक qp_err_flush = (ib_rvt_state_ops[qp->state] & RVT_FLUSH_RECV) &&
				!qp->ibqp.srq;

	/* Check that state is OK to post receive. */
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_POST_RECV_OK) || !wq) अणु
		*bad_wr = wr;
		वापस -EINVAL;
	पूर्ण

	क्रम (; wr; wr = wr->next) अणु
		काष्ठा rvt_rwqe *wqe;
		u32 next;
		पूर्णांक i;

		अगर ((अचिन्हित)wr->num_sge > qp->r_rq.max_sge) अणु
			*bad_wr = wr;
			वापस -EINVAL;
		पूर्ण

		spin_lock_irqsave(&qp->r_rq.kwq->p_lock, flags);
		next = wq->head + 1;
		अगर (next >= qp->r_rq.size)
			next = 0;
		अगर (next == READ_ONCE(wq->tail)) अणु
			spin_unlock_irqrestore(&qp->r_rq.kwq->p_lock, flags);
			*bad_wr = wr;
			वापस -ENOMEM;
		पूर्ण
		अगर (unlikely(qp_err_flush)) अणु
			काष्ठा ib_wc wc;

			स_रखो(&wc, 0, माप(wc));
			wc.qp = &qp->ibqp;
			wc.opcode = IB_WC_RECV;
			wc.wr_id = wr->wr_id;
			wc.status = IB_WC_WR_FLUSH_ERR;
			rvt_cq_enter(ibcq_to_rvtcq(qp->ibqp.recv_cq), &wc, 1);
		पूर्ण अन्यथा अणु
			wqe = rvt_get_rwqe_ptr(&qp->r_rq, wq->head);
			wqe->wr_id = wr->wr_id;
			wqe->num_sge = wr->num_sge;
			क्रम (i = 0; i < wr->num_sge; i++) अणु
				wqe->sg_list[i].addr = wr->sg_list[i].addr;
				wqe->sg_list[i].length = wr->sg_list[i].length;
				wqe->sg_list[i].lkey = wr->sg_list[i].lkey;
			पूर्ण
			/*
			 * Make sure queue entry is written
			 * beक्रमe the head index.
			 */
			smp_store_release(&wq->head, next);
		पूर्ण
		spin_unlock_irqrestore(&qp->r_rq.kwq->p_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * rvt_qp_valid_operation - validate post send wr request
 * @qp: the qp
 * @post_parms: the post send table क्रम the driver
 * @wr: the work request
 *
 * The routine validates the operation based on the
 * validation table an वापसs the length of the operation
 * which can extend beyond the ib_send_bw.  Operation
 * dependent flags key atomic operation validation.
 *
 * There is an exception क्रम UD qps that validates the pd and
 * overrides the length to include the additional UD specअगरic
 * length.
 *
 * Returns a negative error or the length of the work request
 * क्रम building the swqe.
 */
अटल अंतरभूत पूर्णांक rvt_qp_valid_operation(
	काष्ठा rvt_qp *qp,
	स्थिर काष्ठा rvt_operation_params *post_parms,
	स्थिर काष्ठा ib_send_wr *wr)
अणु
	पूर्णांक len;

	अगर (wr->opcode >= RVT_OPERATION_MAX || !post_parms[wr->opcode].length)
		वापस -EINVAL;
	अगर (!(post_parms[wr->opcode].qpt_support & BIT(qp->ibqp.qp_type)))
		वापस -EINVAL;
	अगर ((post_parms[wr->opcode].flags & RVT_OPERATION_PRIV) &&
	    ibpd_to_rvtpd(qp->ibqp.pd)->user)
		वापस -EINVAL;
	अगर (post_parms[wr->opcode].flags & RVT_OPERATION_ATOMIC_SGE &&
	    (wr->num_sge == 0 ||
	     wr->sg_list[0].length < माप(u64) ||
	     wr->sg_list[0].addr & (माप(u64) - 1)))
		वापस -EINVAL;
	अगर (post_parms[wr->opcode].flags & RVT_OPERATION_ATOMIC &&
	    !qp->s_max_rd_atomic)
		वापस -EINVAL;
	len = post_parms[wr->opcode].length;
	/* UD specअगरic */
	अगर (qp->ibqp.qp_type != IB_QPT_UC &&
	    qp->ibqp.qp_type != IB_QPT_RC) अणु
		अगर (qp->ibqp.pd != ud_wr(wr)->ah->pd)
			वापस -EINVAL;
		len = माप(काष्ठा ib_ud_wr);
	पूर्ण
	वापस len;
पूर्ण

/**
 * rvt_qp_is_avail - determine queue capacity
 * @qp: the qp
 * @rdi: the rdmavt device
 * @reserved_op: is reserved operation
 *
 * This assumes the s_hlock is held but the s_last
 * qp variable is uncontrolled.
 *
 * For non reserved operations, the qp->s_avail
 * may be changed.
 *
 * The वापस value is zero or a -ENOMEM.
 */
अटल अंतरभूत पूर्णांक rvt_qp_is_avail(
	काष्ठा rvt_qp *qp,
	काष्ठा rvt_dev_info *rdi,
	bool reserved_op)
अणु
	u32 slast;
	u32 avail;
	u32 reserved_used;

	/* see rvt_qp_wqe_unreserve() */
	smp_mb__beक्रमe_atomic();
	अगर (unlikely(reserved_op)) अणु
		/* see rvt_qp_wqe_unreserve() */
		reserved_used = atomic_पढ़ो(&qp->s_reserved_used);
		अगर (reserved_used >= rdi->dparms.reserved_operations)
			वापस -ENOMEM;
		वापस 0;
	पूर्ण
	/* non-reserved operations */
	अगर (likely(qp->s_avail))
		वापस 0;
	/* See rvt_qp_complete_swqe() */
	slast = smp_load_acquire(&qp->s_last);
	अगर (qp->s_head >= slast)
		avail = qp->s_size - (qp->s_head - slast);
	अन्यथा
		avail = slast - qp->s_head;

	reserved_used = atomic_पढ़ो(&qp->s_reserved_used);
	avail =  avail - 1 -
		(rdi->dparms.reserved_operations - reserved_used);
	/* insure we करोn't assign a negative s_avail */
	अगर ((s32)avail <= 0)
		वापस -ENOMEM;
	qp->s_avail = avail;
	अगर (WARN_ON(qp->s_avail >
		    (qp->s_size - 1 - rdi->dparms.reserved_operations)))
		rvt_pr_err(rdi,
			   "More avail entries than QP RB size.\nQP: %u, size: %u, avail: %u\nhead: %u, tail: %u, cur: %u, acked: %u, last: %u",
			   qp->ibqp.qp_num, qp->s_size, qp->s_avail,
			   qp->s_head, qp->s_tail, qp->s_cur,
			   qp->s_acked, qp->s_last);
	वापस 0;
पूर्ण

/**
 * rvt_post_one_wr - post one RC, UC, or UD send work request
 * @qp: the QP to post on
 * @wr: the work request to send
 * @call_send: kick the send engine पूर्णांकo gear
 */
अटल पूर्णांक rvt_post_one_wr(काष्ठा rvt_qp *qp,
			   स्थिर काष्ठा ib_send_wr *wr,
			   bool *call_send)
अणु
	काष्ठा rvt_swqe *wqe;
	u32 next;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक acc;
	काष्ठा rvt_lkey_table *rkt;
	काष्ठा rvt_pd *pd;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);
	u8 log_pmtu;
	पूर्णांक ret;
	माप_प्रकार cplen;
	bool reserved_op;
	पूर्णांक local_ops_delayed = 0;

	BUILD_BUG_ON(IB_QPT_MAX >= (माप(u32) * BITS_PER_BYTE));

	/* IB spec says that num_sge == 0 is OK. */
	अगर (unlikely(wr->num_sge > qp->s_max_sge))
		वापस -EINVAL;

	ret = rvt_qp_valid_operation(qp, rdi->post_parms, wr);
	अगर (ret < 0)
		वापस ret;
	cplen = ret;

	/*
	 * Local operations include fast रेजिस्टर and local invalidate.
	 * Fast रेजिस्टर needs to be processed immediately because the
	 * रेजिस्टरed lkey may be used by following work requests and the
	 * lkey needs to be valid at the समय those requests are posted.
	 * Local invalidate can be processed immediately अगर fencing is
	 * not required and no previous local invalidate ops are pending.
	 * Signaled local operations that have been processed immediately
	 * need to have requests with "completion only" flags set posted
	 * to the send queue in order to generate completions.
	 */
	अगर ((rdi->post_parms[wr->opcode].flags & RVT_OPERATION_LOCAL)) अणु
		चयन (wr->opcode) अणु
		हाल IB_WR_REG_MR:
			ret = rvt_fast_reg_mr(qp,
					      reg_wr(wr)->mr,
					      reg_wr(wr)->key,
					      reg_wr(wr)->access);
			अगर (ret || !(wr->send_flags & IB_SEND_SIGNALED))
				वापस ret;
			अवरोध;
		हाल IB_WR_LOCAL_INV:
			अगर ((wr->send_flags & IB_SEND_FENCE) ||
			    atomic_पढ़ो(&qp->local_ops_pending)) अणु
				local_ops_delayed = 1;
			पूर्ण अन्यथा अणु
				ret = rvt_invalidate_rkey(
					qp, wr->ex.invalidate_rkey);
				अगर (ret || !(wr->send_flags & IB_SEND_SIGNALED))
					वापस ret;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	reserved_op = rdi->post_parms[wr->opcode].flags &
			RVT_OPERATION_USE_RESERVE;
	/* check क्रम avail */
	ret = rvt_qp_is_avail(qp, rdi, reserved_op);
	अगर (ret)
		वापस ret;
	next = qp->s_head + 1;
	अगर (next >= qp->s_size)
		next = 0;

	rkt = &rdi->lkey_table;
	pd = ibpd_to_rvtpd(qp->ibqp.pd);
	wqe = rvt_get_swqe_ptr(qp, qp->s_head);

	/* cplen has length from above */
	स_नकल(&wqe->wr, wr, cplen);

	wqe->length = 0;
	j = 0;
	अगर (wr->num_sge) अणु
		काष्ठा rvt_sge *last_sge = शून्य;

		acc = wr->opcode >= IB_WR_RDMA_READ ?
			IB_ACCESS_LOCAL_WRITE : 0;
		क्रम (i = 0; i < wr->num_sge; i++) अणु
			u32 length = wr->sg_list[i].length;

			अगर (length == 0)
				जारी;
			ret = rvt_lkey_ok(rkt, pd, &wqe->sg_list[j], last_sge,
					  &wr->sg_list[i], acc);
			अगर (unlikely(ret < 0))
				जाओ bail_inval_मुक्त;
			wqe->length += length;
			अगर (ret)
				last_sge = &wqe->sg_list[j];
			j += ret;
		पूर्ण
		wqe->wr.num_sge = j;
	पूर्ण

	/*
	 * Calculate and set SWQE PSN values prior to handing it off
	 * to the driver's check routine. This give the driver the
	 * opportunity to adjust PSN values based on पूर्णांकernal checks.
	 */
	log_pmtu = qp->log_pmtu;
	अगर (qp->allowed_ops == IB_OPCODE_UD) अणु
		काष्ठा rvt_ah *ah = rvt_get_swqe_ah(wqe);

		log_pmtu = ah->log_pmtu;
		rdma_copy_ah_attr(wqe->ud_wr.attr, &ah->attr);
	पूर्ण

	अगर (rdi->post_parms[wr->opcode].flags & RVT_OPERATION_LOCAL) अणु
		अगर (local_ops_delayed)
			atomic_inc(&qp->local_ops_pending);
		अन्यथा
			wqe->wr.send_flags |= RVT_SEND_COMPLETION_ONLY;
		wqe->ssn = 0;
		wqe->psn = 0;
		wqe->lpsn = 0;
	पूर्ण अन्यथा अणु
		wqe->ssn = qp->s_ssn++;
		wqe->psn = qp->s_next_psn;
		wqe->lpsn = wqe->psn +
				(wqe->length ?
					((wqe->length - 1) >> log_pmtu) :
					0);
	पूर्ण

	/* general part of wqe valid - allow क्रम driver checks */
	अगर (rdi->driver_f.setup_wqe) अणु
		ret = rdi->driver_f.setup_wqe(qp, wqe, call_send);
		अगर (ret < 0)
			जाओ bail_inval_मुक्त_ref;
	पूर्ण

	अगर (!(rdi->post_parms[wr->opcode].flags & RVT_OPERATION_LOCAL))
		qp->s_next_psn = wqe->lpsn + 1;

	अगर (unlikely(reserved_op)) अणु
		wqe->wr.send_flags |= RVT_SEND_RESERVE_USED;
		rvt_qp_wqe_reserve(qp, wqe);
	पूर्ण अन्यथा अणु
		wqe->wr.send_flags &= ~RVT_SEND_RESERVE_USED;
		qp->s_avail--;
	पूर्ण
	trace_rvt_post_one_wr(qp, wqe, wr->num_sge);
	smp_wmb(); /* see request builders */
	qp->s_head = next;

	वापस 0;

bail_inval_मुक्त_ref:
	अगर (qp->allowed_ops == IB_OPCODE_UD)
		rdma_destroy_ah_attr(wqe->ud_wr.attr);
bail_inval_मुक्त:
	/* release mr holds */
	जबतक (j) अणु
		काष्ठा rvt_sge *sge = &wqe->sg_list[--j];

		rvt_put_mr(sge->mr);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * rvt_post_send - post a send on a QP
 * @ibqp: the QP to post the send on
 * @wr: the list of work requests to post
 * @bad_wr: the first bad WR is put here
 *
 * This may be called from पूर्णांकerrupt context.
 *
 * Return: 0 on success अन्यथा त्रुटि_सं
 */
पूर्णांक rvt_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		  स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	काष्ठा rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);
	अचिन्हित दीर्घ flags = 0;
	bool call_send;
	अचिन्हित nreq = 0;
	पूर्णांक err = 0;

	spin_lock_irqsave(&qp->s_hlock, flags);

	/*
	 * Ensure QP state is such that we can send. If not bail out early,
	 * there is no need to करो this every समय we post a send.
	 */
	अगर (unlikely(!(ib_rvt_state_ops[qp->state] & RVT_POST_SEND_OK))) अणु
		spin_unlock_irqrestore(&qp->s_hlock, flags);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If the send queue is empty, and we only have a single WR then just go
	 * ahead and kick the send engine पूर्णांकo gear. Otherwise we will always
	 * just schedule the send to happen later.
	 */
	call_send = qp->s_head == READ_ONCE(qp->s_last) && !wr->next;

	क्रम (; wr; wr = wr->next) अणु
		err = rvt_post_one_wr(qp, wr, &call_send);
		अगर (unlikely(err)) अणु
			*bad_wr = wr;
			जाओ bail;
		पूर्ण
		nreq++;
	पूर्ण
bail:
	spin_unlock_irqrestore(&qp->s_hlock, flags);
	अगर (nreq) अणु
		/*
		 * Only call करो_send अगर there is exactly one packet, and the
		 * driver said it was ok.
		 */
		अगर (nreq == 1 && call_send)
			rdi->driver_f.करो_send(qp);
		अन्यथा
			rdi->driver_f.schedule_send_no_lock(qp);
	पूर्ण
	वापस err;
पूर्ण

/**
 * rvt_post_srq_recv - post a receive on a shared receive queue
 * @ibsrq: the SRQ to post the receive on
 * @wr: the list of work requests to post
 * @bad_wr: A poपूर्णांकer to the first WR to cause a problem is put here
 *
 * This may be called from पूर्णांकerrupt context.
 *
 * Return: 0 on success अन्यथा त्रुटि_सं
 */
पूर्णांक rvt_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	काष्ठा rvt_srq *srq = ibsrq_to_rvtsrq(ibsrq);
	काष्ठा rvt_krwq *wq;
	अचिन्हित दीर्घ flags;

	क्रम (; wr; wr = wr->next) अणु
		काष्ठा rvt_rwqe *wqe;
		u32 next;
		पूर्णांक i;

		अगर ((अचिन्हित)wr->num_sge > srq->rq.max_sge) अणु
			*bad_wr = wr;
			वापस -EINVAL;
		पूर्ण

		spin_lock_irqsave(&srq->rq.kwq->p_lock, flags);
		wq = srq->rq.kwq;
		next = wq->head + 1;
		अगर (next >= srq->rq.size)
			next = 0;
		अगर (next == READ_ONCE(wq->tail)) अणु
			spin_unlock_irqrestore(&srq->rq.kwq->p_lock, flags);
			*bad_wr = wr;
			वापस -ENOMEM;
		पूर्ण

		wqe = rvt_get_rwqe_ptr(&srq->rq, wq->head);
		wqe->wr_id = wr->wr_id;
		wqe->num_sge = wr->num_sge;
		क्रम (i = 0; i < wr->num_sge; i++) अणु
			wqe->sg_list[i].addr = wr->sg_list[i].addr;
			wqe->sg_list[i].length = wr->sg_list[i].length;
			wqe->sg_list[i].lkey = wr->sg_list[i].lkey;
		पूर्ण
		/* Make sure queue entry is written beक्रमe the head index. */
		smp_store_release(&wq->head, next);
		spin_unlock_irqrestore(&srq->rq.kwq->p_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * rvt used the पूर्णांकernal kernel काष्ठा as part of its ABI, क्रम now make sure
 * the kernel काष्ठा करोes not change layout. FIXME: rvt should never cast the
 * user काष्ठा to a kernel काष्ठा.
 */
अटल काष्ठा ib_sge *rvt_cast_sge(काष्ठा rvt_wqe_sge *sge)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा ib_sge, addr) !=
		     दुरत्व(काष्ठा rvt_wqe_sge, addr));
	BUILD_BUG_ON(दुरत्व(काष्ठा ib_sge, length) !=
		     दुरत्व(काष्ठा rvt_wqe_sge, length));
	BUILD_BUG_ON(दुरत्व(काष्ठा ib_sge, lkey) !=
		     दुरत्व(काष्ठा rvt_wqe_sge, lkey));
	वापस (काष्ठा ib_sge *)sge;
पूर्ण

/*
 * Validate a RWQE and fill in the SGE state.
 * Return 1 अगर OK.
 */
अटल पूर्णांक init_sge(काष्ठा rvt_qp *qp, काष्ठा rvt_rwqe *wqe)
अणु
	पूर्णांक i, j, ret;
	काष्ठा ib_wc wc;
	काष्ठा rvt_lkey_table *rkt;
	काष्ठा rvt_pd *pd;
	काष्ठा rvt_sge_state *ss;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);

	rkt = &rdi->lkey_table;
	pd = ibpd_to_rvtpd(qp->ibqp.srq ? qp->ibqp.srq->pd : qp->ibqp.pd);
	ss = &qp->r_sge;
	ss->sg_list = qp->r_sg_list;
	qp->r_len = 0;
	क्रम (i = j = 0; i < wqe->num_sge; i++) अणु
		अगर (wqe->sg_list[i].length == 0)
			जारी;
		/* Check LKEY */
		ret = rvt_lkey_ok(rkt, pd, j ? &ss->sg_list[j - 1] : &ss->sge,
				  शून्य, rvt_cast_sge(&wqe->sg_list[i]),
				  IB_ACCESS_LOCAL_WRITE);
		अगर (unlikely(ret <= 0))
			जाओ bad_lkey;
		qp->r_len += wqe->sg_list[i].length;
		j++;
	पूर्ण
	ss->num_sge = j;
	ss->total_len = qp->r_len;
	वापस 1;

bad_lkey:
	जबतक (j) अणु
		काष्ठा rvt_sge *sge = --j ? &ss->sg_list[j - 1] : &ss->sge;

		rvt_put_mr(sge->mr);
	पूर्ण
	ss->num_sge = 0;
	स_रखो(&wc, 0, माप(wc));
	wc.wr_id = wqe->wr_id;
	wc.status = IB_WC_LOC_PROT_ERR;
	wc.opcode = IB_WC_RECV;
	wc.qp = &qp->ibqp;
	/* Signal solicited completion event. */
	rvt_cq_enter(ibcq_to_rvtcq(qp->ibqp.recv_cq), &wc, 1);
	वापस 0;
पूर्ण

/**
 * get_rvt_head - get head indices of the circular buffer
 * @rq: data काष्ठाure क्रम request queue entry
 * @ip: the QP
 *
 * Return - head index value
 */
अटल अंतरभूत u32 get_rvt_head(काष्ठा rvt_rq *rq, व्योम *ip)
अणु
	u32 head;

	अगर (ip)
		head = RDMA_READ_UAPI_ATOMIC(rq->wq->head);
	अन्यथा
		head = rq->kwq->head;

	वापस head;
पूर्ण

/**
 * rvt_get_rwqe - copy the next RWQE पूर्णांकo the QP's RWQE
 * @qp: the QP
 * @wr_id_only: update qp->r_wr_id only, not qp->r_sge
 *
 * Return -1 अगर there is a local error, 0 अगर no RWQE is available,
 * otherwise वापस 1.
 *
 * Can be called from पूर्णांकerrupt level.
 */
पूर्णांक rvt_get_rwqe(काष्ठा rvt_qp *qp, bool wr_id_only)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा rvt_rq *rq;
	काष्ठा rvt_krwq *kwq = शून्य;
	काष्ठा rvt_rwq *wq;
	काष्ठा rvt_srq *srq;
	काष्ठा rvt_rwqe *wqe;
	व्योम (*handler)(काष्ठा ib_event *, व्योम *);
	u32 tail;
	u32 head;
	पूर्णांक ret;
	व्योम *ip = शून्य;

	अगर (qp->ibqp.srq) अणु
		srq = ibsrq_to_rvtsrq(qp->ibqp.srq);
		handler = srq->ibsrq.event_handler;
		rq = &srq->rq;
		ip = srq->ip;
	पूर्ण अन्यथा अणु
		srq = शून्य;
		handler = शून्य;
		rq = &qp->r_rq;
		ip = qp->ip;
	पूर्ण

	spin_lock_irqsave(&rq->kwq->c_lock, flags);
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) अणु
		ret = 0;
		जाओ unlock;
	पूर्ण
	kwq = rq->kwq;
	अगर (ip) अणु
		wq = rq->wq;
		tail = RDMA_READ_UAPI_ATOMIC(wq->tail);
	पूर्ण अन्यथा अणु
		tail = kwq->tail;
	पूर्ण

	/* Validate tail beक्रमe using it since it is user writable. */
	अगर (tail >= rq->size)
		tail = 0;

	अगर (kwq->count < RVT_RWQ_COUNT_THRESHOLD) अणु
		head = get_rvt_head(rq, ip);
		kwq->count = rvt_get_rq_count(rq, head, tail);
	पूर्ण
	अगर (unlikely(kwq->count == 0)) अणु
		ret = 0;
		जाओ unlock;
	पूर्ण
	/* Make sure entry is पढ़ो after the count is पढ़ो. */
	smp_rmb();
	wqe = rvt_get_rwqe_ptr(rq, tail);
	/*
	 * Even though we update the tail index in memory, the verbs
	 * consumer is not supposed to post more entries until a
	 * completion is generated.
	 */
	अगर (++tail >= rq->size)
		tail = 0;
	अगर (ip)
		RDMA_WRITE_UAPI_ATOMIC(wq->tail, tail);
	अन्यथा
		kwq->tail = tail;
	अगर (!wr_id_only && !init_sge(qp, wqe)) अणु
		ret = -1;
		जाओ unlock;
	पूर्ण
	qp->r_wr_id = wqe->wr_id;

	kwq->count--;
	ret = 1;
	set_bit(RVT_R_WRID_VALID, &qp->r_aflags);
	अगर (handler) अणु
		/*
		 * Validate head poपूर्णांकer value and compute
		 * the number of reमुख्यing WQEs.
		 */
		अगर (kwq->count < srq->limit) अणु
			kwq->count =
				rvt_get_rq_count(rq,
						 get_rvt_head(rq, ip), tail);
			अगर (kwq->count < srq->limit) अणु
				काष्ठा ib_event ev;

				srq->limit = 0;
				spin_unlock_irqrestore(&rq->kwq->c_lock, flags);
				ev.device = qp->ibqp.device;
				ev.element.srq = qp->ibqp.srq;
				ev.event = IB_EVENT_SRQ_LIMIT_REACHED;
				handler(&ev, srq->ibsrq.srq_context);
				जाओ bail;
			पूर्ण
		पूर्ण
	पूर्ण
unlock:
	spin_unlock_irqrestore(&rq->kwq->c_lock, flags);
bail:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rvt_get_rwqe);

/**
 * rvt_comm_est - handle trap with QP established
 * @qp: the QP
 */
व्योम rvt_comm_est(काष्ठा rvt_qp *qp)
अणु
	qp->r_flags |= RVT_R_COMM_EST;
	अगर (qp->ibqp.event_handler) अणु
		काष्ठा ib_event ev;

		ev.device = qp->ibqp.device;
		ev.element.qp = &qp->ibqp;
		ev.event = IB_EVENT_COMM_EST;
		qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rvt_comm_est);

व्योम rvt_rc_error(काष्ठा rvt_qp *qp, क्रमागत ib_wc_status err)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक lastwqe;

	spin_lock_irqsave(&qp->s_lock, flags);
	lastwqe = rvt_error_qp(qp, err);
	spin_unlock_irqrestore(&qp->s_lock, flags);

	अगर (lastwqe) अणु
		काष्ठा ib_event ev;

		ev.device = qp->ibqp.device;
		ev.element.qp = &qp->ibqp;
		ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
		qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rvt_rc_error);

/*
 *  rvt_rnr_tbl_to_usec - वापस index पूर्णांकo ib_rvt_rnr_table
 *  @index - the index
 *  वापस usec from an index पूर्णांकo ib_rvt_rnr_table
 */
अचिन्हित दीर्घ rvt_rnr_tbl_to_usec(u32 index)
अणु
	वापस ib_rvt_rnr_table[(index & IB_AETH_CREDIT_MASK)];
पूर्ण
EXPORT_SYMBOL(rvt_rnr_tbl_to_usec);

अटल अंतरभूत अचिन्हित दीर्घ rvt_aeth_to_usec(u32 aeth)
अणु
	वापस ib_rvt_rnr_table[(aeth >> IB_AETH_CREDIT_SHIFT) &
				  IB_AETH_CREDIT_MASK];
पूर्ण

/*
 *  rvt_add_retry_समयr_ext - add/start a retry समयr
 *  @qp - the QP
 *  @shअगरt - समयout shअगरt to रुको क्रम multiple packets
 *  add a retry समयr on the QP
 */
व्योम rvt_add_retry_समयr_ext(काष्ठा rvt_qp *qp, u8 shअगरt)
अणु
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	lockdep_निश्चित_held(&qp->s_lock);
	qp->s_flags |= RVT_S_TIMER;
       /* 4.096 usec. * (1 << qp->समयout) */
	qp->s_समयr.expires = jअगरfies + rdi->busy_jअगरfies +
			      (qp->समयout_jअगरfies << shअगरt);
	add_समयr(&qp->s_समयr);
पूर्ण
EXPORT_SYMBOL(rvt_add_retry_समयr_ext);

/**
 * rvt_add_rnr_समयr - add/start an rnr समयr on the QP
 * @qp: the QP
 * @aeth: aeth of RNR समयout, simulated aeth क्रम loopback
 */
व्योम rvt_add_rnr_समयr(काष्ठा rvt_qp *qp, u32 aeth)
अणु
	u32 to;

	lockdep_निश्चित_held(&qp->s_lock);
	qp->s_flags |= RVT_S_WAIT_RNR;
	to = rvt_aeth_to_usec(aeth);
	trace_rvt_rnrnak_add(qp, to);
	hrसमयr_start(&qp->s_rnr_समयr,
		      ns_to_kसमय(1000 * to), HRTIMER_MODE_REL_PINNED);
पूर्ण
EXPORT_SYMBOL(rvt_add_rnr_समयr);

/**
 * rvt_stop_rc_समयrs - stop all समयrs
 * @qp: the QP
 * stop any pending समयrs
 */
व्योम rvt_stop_rc_समयrs(काष्ठा rvt_qp *qp)
अणु
	lockdep_निश्चित_held(&qp->s_lock);
	/* Remove QP from all समयrs */
	अगर (qp->s_flags & (RVT_S_TIMER | RVT_S_WAIT_RNR)) अणु
		qp->s_flags &= ~(RVT_S_TIMER | RVT_S_WAIT_RNR);
		del_समयr(&qp->s_समयr);
		hrसमयr_try_to_cancel(&qp->s_rnr_समयr);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rvt_stop_rc_समयrs);

/**
 * rvt_stop_rnr_समयr - stop an rnr समयr
 * @qp: the QP
 *
 * stop an rnr समयr and वापस अगर the समयr
 * had been pending.
 */
अटल व्योम rvt_stop_rnr_समयr(काष्ठा rvt_qp *qp)
अणु
	lockdep_निश्चित_held(&qp->s_lock);
	/* Remove QP from rnr समयr */
	अगर (qp->s_flags & RVT_S_WAIT_RNR) अणु
		qp->s_flags &= ~RVT_S_WAIT_RNR;
		trace_rvt_rnrnak_stop(qp, 0);
	पूर्ण
पूर्ण

/**
 * rvt_del_समयrs_sync - रुको क्रम any समयout routines to निकास
 * @qp: the QP
 */
व्योम rvt_del_समयrs_sync(काष्ठा rvt_qp *qp)
अणु
	del_समयr_sync(&qp->s_समयr);
	hrसमयr_cancel(&qp->s_rnr_समयr);
पूर्ण
EXPORT_SYMBOL(rvt_del_समयrs_sync);

/*
 * This is called from s_समयr क्रम missing responses.
 */
अटल व्योम rvt_rc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा rvt_qp *qp = from_समयr(qp, t, s_समयr);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->r_lock, flags);
	spin_lock(&qp->s_lock);
	अगर (qp->s_flags & RVT_S_TIMER) अणु
		काष्ठा rvt_ibport *rvp = rdi->ports[qp->port_num - 1];

		qp->s_flags &= ~RVT_S_TIMER;
		rvp->n_rc_समयouts++;
		del_समयr(&qp->s_समयr);
		trace_rvt_rc_समयout(qp, qp->s_last_psn + 1);
		अगर (rdi->driver_f.notअगरy_restart_rc)
			rdi->driver_f.notअगरy_restart_rc(qp,
							qp->s_last_psn + 1,
							1);
		rdi->driver_f.schedule_send(qp);
	पूर्ण
	spin_unlock(&qp->s_lock);
	spin_unlock_irqrestore(&qp->r_lock, flags);
पूर्ण

/*
 * This is called from s_समयr क्रम RNR समयouts.
 */
क्रमागत hrसमयr_restart rvt_rc_rnr_retry(काष्ठा hrसमयr *t)
अणु
	काष्ठा rvt_qp *qp = container_of(t, काष्ठा rvt_qp, s_rnr_समयr);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->s_lock, flags);
	rvt_stop_rnr_समयr(qp);
	trace_rvt_rnrnak_समयout(qp, 0);
	rdi->driver_f.schedule_send(qp);
	spin_unlock_irqrestore(&qp->s_lock, flags);
	वापस HRTIMER_NORESTART;
पूर्ण
EXPORT_SYMBOL(rvt_rc_rnr_retry);

/**
 * rvt_qp_iter_init - initial क्रम QP iteration
 * @rdi: rvt devinfo
 * @v: u64 value
 * @cb: user-defined callback
 *
 * This वापसs an iterator suitable क्रम iterating QPs
 * in the प्रणाली.
 *
 * The @cb is a user-defined callback and @v is a 64-bit
 * value passed to and relevant क्रम processing in the
 * @cb.  An example use हाल would be to alter QP processing
 * based on criteria not part of the rvt_qp.
 *
 * Use हालs that require memory allocation to succeed
 * must pपुनः_स्मृतिate appropriately.
 *
 * Return: a poपूर्णांकer to an rvt_qp_iter or शून्य
 */
काष्ठा rvt_qp_iter *rvt_qp_iter_init(काष्ठा rvt_dev_info *rdi,
				     u64 v,
				     व्योम (*cb)(काष्ठा rvt_qp *qp, u64 v))
अणु
	काष्ठा rvt_qp_iter *i;

	i = kzalloc(माप(*i), GFP_KERNEL);
	अगर (!i)
		वापस शून्य;

	i->rdi = rdi;
	/* number of special QPs (SMI/GSI) क्रम device */
	i->specials = rdi->ibdev.phys_port_cnt * 2;
	i->v = v;
	i->cb = cb;

	वापस i;
पूर्ण
EXPORT_SYMBOL(rvt_qp_iter_init);

/**
 * rvt_qp_iter_next - वापस the next QP in iter
 * @iter: the iterator
 *
 * Fine grained QP iterator suitable क्रम use
 * with debugfs seq_file mechanisms.
 *
 * Updates iter->qp with the current QP when the वापस
 * value is 0.
 *
 * Return: 0 - iter->qp is valid 1 - no more QPs
 */
पूर्णांक rvt_qp_iter_next(काष्ठा rvt_qp_iter *iter)
	__must_hold(RCU)
अणु
	पूर्णांक n = iter->n;
	पूर्णांक ret = 1;
	काष्ठा rvt_qp *pqp = iter->qp;
	काष्ठा rvt_qp *qp;
	काष्ठा rvt_dev_info *rdi = iter->rdi;

	/*
	 * The approach is to consider the special qps
	 * as additional table entries beक्रमe the
	 * real hash table.  Since the qp code sets
	 * the qp->next hash link to शून्य, this works just fine.
	 *
	 * iter->specials is 2 * # ports
	 *
	 * n = 0..iter->specials is the special qp indices
	 *
	 * n = iter->specials..rdi->qp_dev->qp_table_size+iter->specials are
	 * the potential hash bucket entries
	 *
	 */
	क्रम (; n <  rdi->qp_dev->qp_table_size + iter->specials; n++) अणु
		अगर (pqp) अणु
			qp = rcu_dereference(pqp->next);
		पूर्ण अन्यथा अणु
			अगर (n < iter->specials) अणु
				काष्ठा rvt_ibport *rvp;
				पूर्णांक pidx;

				pidx = n % rdi->ibdev.phys_port_cnt;
				rvp = rdi->ports[pidx];
				qp = rcu_dereference(rvp->qp[n & 1]);
			पूर्ण अन्यथा अणु
				qp = rcu_dereference(
					rdi->qp_dev->qp_table[
						(n - iter->specials)]);
			पूर्ण
		पूर्ण
		pqp = qp;
		अगर (qp) अणु
			iter->qp = qp;
			iter->n = n;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rvt_qp_iter_next);

/**
 * rvt_qp_iter - iterate all QPs
 * @rdi: rvt devinfo
 * @v: a 64-bit value
 * @cb: a callback
 *
 * This provides a way क्रम iterating all QPs.
 *
 * The @cb is a user-defined callback and @v is a 64-bit
 * value passed to and relevant क्रम processing in the
 * cb.  An example use हाल would be to alter QP processing
 * based on criteria not part of the rvt_qp.
 *
 * The code has an पूर्णांकernal iterator to simplअगरy
 * non seq_file use हालs.
 */
व्योम rvt_qp_iter(काष्ठा rvt_dev_info *rdi,
		 u64 v,
		 व्योम (*cb)(काष्ठा rvt_qp *qp, u64 v))
अणु
	पूर्णांक ret;
	काष्ठा rvt_qp_iter i = अणु
		.rdi = rdi,
		.specials = rdi->ibdev.phys_port_cnt * 2,
		.v = v,
		.cb = cb
	पूर्ण;

	rcu_पढ़ो_lock();
	करो अणु
		ret = rvt_qp_iter_next(&i);
		अगर (!ret) अणु
			rvt_get_qp(i.qp);
			rcu_पढ़ो_unlock();
			i.cb(i.qp, i.v);
			rcu_पढ़ो_lock();
			rvt_put_qp(i.qp);
		पूर्ण
	पूर्ण जबतक (!ret);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(rvt_qp_iter);

/*
 * This should be called with s_lock held.
 */
व्योम rvt_send_complete(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
		       क्रमागत ib_wc_status status)
अणु
	u32 old_last, last;
	काष्ठा rvt_dev_info *rdi;

	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_OR_FLUSH_SEND))
		वापस;
	rdi = ib_to_rvt(qp->ibqp.device);

	old_last = qp->s_last;
	trace_rvt_qp_send_completion(qp, wqe, old_last);
	last = rvt_qp_complete_swqe(qp, wqe, rdi->wc_opcode[wqe->wr.opcode],
				    status);
	अगर (qp->s_acked == old_last)
		qp->s_acked = last;
	अगर (qp->s_cur == old_last)
		qp->s_cur = last;
	अगर (qp->s_tail == old_last)
		qp->s_tail = last;
	अगर (qp->state == IB_QPS_SQD && last == qp->s_cur)
		qp->s_draining = 0;
पूर्ण
EXPORT_SYMBOL(rvt_send_complete);

/**
 * rvt_copy_sge - copy data to SGE memory
 * @qp: associated QP
 * @ss: the SGE state
 * @data: the data to copy
 * @length: the length of the data
 * @release: boolean to release MR
 * @copy_last: करो a separate copy of the last 8 bytes
 */
व्योम rvt_copy_sge(काष्ठा rvt_qp *qp, काष्ठा rvt_sge_state *ss,
		  व्योम *data, u32 length,
		  bool release, bool copy_last)
अणु
	काष्ठा rvt_sge *sge = &ss->sge;
	पूर्णांक i;
	bool in_last = false;
	bool cacheless_copy = false;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);
	काष्ठा rvt_wss *wss = rdi->wss;
	अचिन्हित पूर्णांक sge_copy_mode = rdi->dparms.sge_copy_mode;

	अगर (sge_copy_mode == RVT_SGE_COPY_CACHELESS) अणु
		cacheless_copy = length >= PAGE_SIZE;
	पूर्ण अन्यथा अगर (sge_copy_mode == RVT_SGE_COPY_ADAPTIVE) अणु
		अगर (length >= PAGE_SIZE) अणु
			/*
			 * NOTE: this *assumes*:
			 * o The first vaddr is the dest.
			 * o If multiple pages, then vaddr is sequential.
			 */
			wss_insert(wss, sge->vaddr);
			अगर (length >= (2 * PAGE_SIZE))
				wss_insert(wss, (sge->vaddr + PAGE_SIZE));

			cacheless_copy = wss_exceeds_threshold(wss);
		पूर्ण अन्यथा अणु
			wss_advance_clean_counter(wss);
		पूर्ण
	पूर्ण

	अगर (copy_last) अणु
		अगर (length > 8) अणु
			length -= 8;
		पूर्ण अन्यथा अणु
			copy_last = false;
			in_last = true;
		पूर्ण
	पूर्ण

again:
	जबतक (length) अणु
		u32 len = rvt_get_sge_length(sge, length);

		WARN_ON_ONCE(len == 0);
		अगर (unlikely(in_last)) अणु
			/* enक्रमce byte transfer ordering */
			क्रम (i = 0; i < len; i++)
				((u8 *)sge->vaddr)[i] = ((u8 *)data)[i];
		पूर्ण अन्यथा अगर (cacheless_copy) अणु
			cacheless_स_नकल(sge->vaddr, data, len);
		पूर्ण अन्यथा अणु
			स_नकल(sge->vaddr, data, len);
		पूर्ण
		rvt_update_sge(ss, len, release);
		data += len;
		length -= len;
	पूर्ण

	अगर (copy_last) अणु
		copy_last = false;
		in_last = true;
		length = 8;
		जाओ again;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rvt_copy_sge);

अटल क्रमागत ib_wc_status loopback_qp_drop(काष्ठा rvt_ibport *rvp,
					  काष्ठा rvt_qp *sqp)
अणु
	rvp->n_pkt_drops++;
	/*
	 * For RC, the requester would समयout and retry so
	 * लघुcut the समयouts and just संकेत too many retries.
	 */
	वापस sqp->ibqp.qp_type == IB_QPT_RC ?
		IB_WC_RETRY_EXC_ERR : IB_WC_SUCCESS;
पूर्ण

/**
 * rvt_ruc_loopback - handle UC and RC loopback requests
 * @sqp: the sending QP
 *
 * This is called from rvt_करो_send() to क्रमward a WQE addressed to the same HFI
 * Note that although we are single thपढ़ोed due to the send engine, we still
 * have to protect against post_send().  We करोn't have to worry about
 * receive पूर्णांकerrupts since this is a connected protocol and all packets
 * will pass through here.
 */
व्योम rvt_ruc_loopback(काष्ठा rvt_qp *sqp)
अणु
	काष्ठा rvt_ibport *rvp =  शून्य;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(sqp->ibqp.device);
	काष्ठा rvt_qp *qp;
	काष्ठा rvt_swqe *wqe;
	काष्ठा rvt_sge *sge;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_wc wc;
	u64 sdata;
	atomic64_t *maddr;
	क्रमागत ib_wc_status send_status;
	bool release;
	पूर्णांक ret;
	bool copy_last = false;
	पूर्णांक local_ops = 0;

	rcu_पढ़ो_lock();
	rvp = rdi->ports[sqp->port_num - 1];

	/*
	 * Note that we check the responder QP state after
	 * checking the requester's state.
	 */

	qp = rvt_lookup_qpn(ib_to_rvt(sqp->ibqp.device), rvp,
			    sqp->remote_qpn);

	spin_lock_irqsave(&sqp->s_lock, flags);

	/* Return अगर we are alपढ़ोy busy processing a work request. */
	अगर ((sqp->s_flags & (RVT_S_BUSY | RVT_S_ANY_WAIT)) ||
	    !(ib_rvt_state_ops[sqp->state] & RVT_PROCESS_OR_FLUSH_SEND))
		जाओ unlock;

	sqp->s_flags |= RVT_S_BUSY;

again:
	अगर (sqp->s_last == READ_ONCE(sqp->s_head))
		जाओ clr_busy;
	wqe = rvt_get_swqe_ptr(sqp, sqp->s_last);

	/* Return अगर it is not OK to start a new work request. */
	अगर (!(ib_rvt_state_ops[sqp->state] & RVT_PROCESS_NEXT_SEND_OK)) अणु
		अगर (!(ib_rvt_state_ops[sqp->state] & RVT_FLUSH_SEND))
			जाओ clr_busy;
		/* We are in the error state, flush the work request. */
		send_status = IB_WC_WR_FLUSH_ERR;
		जाओ flush_send;
	पूर्ण

	/*
	 * We can rely on the entry not changing without the s_lock
	 * being held until we update s_last.
	 * We increment s_cur to indicate s_last is in progress.
	 */
	अगर (sqp->s_last == sqp->s_cur) अणु
		अगर (++sqp->s_cur >= sqp->s_size)
			sqp->s_cur = 0;
	पूर्ण
	spin_unlock_irqrestore(&sqp->s_lock, flags);

	अगर (!qp) अणु
		send_status = loopback_qp_drop(rvp, sqp);
		जाओ serr_no_r_lock;
	पूर्ण
	spin_lock_irqsave(&qp->r_lock, flags);
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) ||
	    qp->ibqp.qp_type != sqp->ibqp.qp_type) अणु
		send_status = loopback_qp_drop(rvp, sqp);
		जाओ serr;
	पूर्ण

	स_रखो(&wc, 0, माप(wc));
	send_status = IB_WC_SUCCESS;

	release = true;
	sqp->s_sge.sge = wqe->sg_list[0];
	sqp->s_sge.sg_list = wqe->sg_list + 1;
	sqp->s_sge.num_sge = wqe->wr.num_sge;
	sqp->s_len = wqe->length;
	चयन (wqe->wr.opcode) अणु
	हाल IB_WR_REG_MR:
		जाओ send_comp;

	हाल IB_WR_LOCAL_INV:
		अगर (!(wqe->wr.send_flags & RVT_SEND_COMPLETION_ONLY)) अणु
			अगर (rvt_invalidate_rkey(sqp,
						wqe->wr.ex.invalidate_rkey))
				send_status = IB_WC_LOC_PROT_ERR;
			local_ops = 1;
		पूर्ण
		जाओ send_comp;

	हाल IB_WR_SEND_WITH_INV:
	हाल IB_WR_SEND_WITH_IMM:
	हाल IB_WR_SEND:
		ret = rvt_get_rwqe(qp, false);
		अगर (ret < 0)
			जाओ op_err;
		अगर (!ret)
			जाओ rnr_nak;
		अगर (wqe->length > qp->r_len)
			जाओ inv_err;
		चयन (wqe->wr.opcode) अणु
		हाल IB_WR_SEND_WITH_INV:
			अगर (!rvt_invalidate_rkey(qp,
						 wqe->wr.ex.invalidate_rkey)) अणु
				wc.wc_flags = IB_WC_WITH_INVALIDATE;
				wc.ex.invalidate_rkey =
					wqe->wr.ex.invalidate_rkey;
			पूर्ण
			अवरोध;
		हाल IB_WR_SEND_WITH_IMM:
			wc.wc_flags = IB_WC_WITH_IMM;
			wc.ex.imm_data = wqe->wr.ex.imm_data;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			जाओ inv_err;
		wc.wc_flags = IB_WC_WITH_IMM;
		wc.ex.imm_data = wqe->wr.ex.imm_data;
		ret = rvt_get_rwqe(qp, true);
		अगर (ret < 0)
			जाओ op_err;
		अगर (!ret)
			जाओ rnr_nak;
		/* skip copy_last set and qp_access_flags recheck */
		जाओ करो_ग_लिखो;
	हाल IB_WR_RDMA_WRITE:
		copy_last = rvt_is_user_qp(qp);
		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
			जाओ inv_err;
करो_ग_लिखो:
		अगर (wqe->length == 0)
			अवरोध;
		अगर (unlikely(!rvt_rkey_ok(qp, &qp->r_sge.sge, wqe->length,
					  wqe->rdma_wr.remote_addr,
					  wqe->rdma_wr.rkey,
					  IB_ACCESS_REMOTE_WRITE)))
			जाओ acc_err;
		qp->r_sge.sg_list = शून्य;
		qp->r_sge.num_sge = 1;
		qp->r_sge.total_len = wqe->length;
		अवरोध;

	हाल IB_WR_RDMA_READ:
		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_READ)))
			जाओ inv_err;
		अगर (unlikely(!rvt_rkey_ok(qp, &sqp->s_sge.sge, wqe->length,
					  wqe->rdma_wr.remote_addr,
					  wqe->rdma_wr.rkey,
					  IB_ACCESS_REMOTE_READ)))
			जाओ acc_err;
		release = false;
		sqp->s_sge.sg_list = शून्य;
		sqp->s_sge.num_sge = 1;
		qp->r_sge.sge = wqe->sg_list[0];
		qp->r_sge.sg_list = wqe->sg_list + 1;
		qp->r_sge.num_sge = wqe->wr.num_sge;
		qp->r_sge.total_len = wqe->length;
		अवरोध;

	हाल IB_WR_ATOMIC_CMP_AND_SWP:
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
		अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_ATOMIC)))
			जाओ inv_err;
		अगर (unlikely(!rvt_rkey_ok(qp, &qp->r_sge.sge, माप(u64),
					  wqe->atomic_wr.remote_addr,
					  wqe->atomic_wr.rkey,
					  IB_ACCESS_REMOTE_ATOMIC)))
			जाओ acc_err;
		/* Perक्रमm atomic OP and save result. */
		maddr = (atomic64_t *)qp->r_sge.sge.vaddr;
		sdata = wqe->atomic_wr.compare_add;
		*(u64 *)sqp->s_sge.sge.vaddr =
			(wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) ?
			(u64)atomic64_add_वापस(sdata, maddr) - sdata :
			(u64)cmpxchg((u64 *)qp->r_sge.sge.vaddr,
				      sdata, wqe->atomic_wr.swap);
		rvt_put_mr(qp->r_sge.sge.mr);
		qp->r_sge.num_sge = 0;
		जाओ send_comp;

	शेष:
		send_status = IB_WC_LOC_QP_OP_ERR;
		जाओ serr;
	पूर्ण

	sge = &sqp->s_sge.sge;
	जबतक (sqp->s_len) अणु
		u32 len = rvt_get_sge_length(sge, sqp->s_len);

		WARN_ON_ONCE(len == 0);
		rvt_copy_sge(qp, &qp->r_sge, sge->vaddr,
			     len, release, copy_last);
		rvt_update_sge(&sqp->s_sge, len, !release);
		sqp->s_len -= len;
	पूर्ण
	अगर (release)
		rvt_put_ss(&qp->r_sge);

	अगर (!test_and_clear_bit(RVT_R_WRID_VALID, &qp->r_aflags))
		जाओ send_comp;

	अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE_WITH_IMM)
		wc.opcode = IB_WC_RECV_RDMA_WITH_IMM;
	अन्यथा
		wc.opcode = IB_WC_RECV;
	wc.wr_id = qp->r_wr_id;
	wc.status = IB_WC_SUCCESS;
	wc.byte_len = wqe->length;
	wc.qp = &qp->ibqp;
	wc.src_qp = qp->remote_qpn;
	wc.slid = rdma_ah_get_dlid(&qp->remote_ah_attr) & U16_MAX;
	wc.sl = rdma_ah_get_sl(&qp->remote_ah_attr);
	wc.port_num = 1;
	/* Signal completion event अगर the solicited bit is set. */
	rvt_recv_cq(qp, &wc, wqe->wr.send_flags & IB_SEND_SOLICITED);

send_comp:
	spin_unlock_irqrestore(&qp->r_lock, flags);
	spin_lock_irqsave(&sqp->s_lock, flags);
	rvp->n_loop_pkts++;
flush_send:
	sqp->s_rnr_retry = sqp->s_rnr_retry_cnt;
	rvt_send_complete(sqp, wqe, send_status);
	अगर (local_ops) अणु
		atomic_dec(&sqp->local_ops_pending);
		local_ops = 0;
	पूर्ण
	जाओ again;

rnr_nak:
	/* Handle RNR NAK */
	अगर (qp->ibqp.qp_type == IB_QPT_UC)
		जाओ send_comp;
	rvp->n_rnr_naks++;
	/*
	 * Note: we करोn't need the s_lock held since the BUSY flag
	 * makes this single thपढ़ोed.
	 */
	अगर (sqp->s_rnr_retry == 0) अणु
		send_status = IB_WC_RNR_RETRY_EXC_ERR;
		जाओ serr;
	पूर्ण
	अगर (sqp->s_rnr_retry_cnt < 7)
		sqp->s_rnr_retry--;
	spin_unlock_irqrestore(&qp->r_lock, flags);
	spin_lock_irqsave(&sqp->s_lock, flags);
	अगर (!(ib_rvt_state_ops[sqp->state] & RVT_PROCESS_RECV_OK))
		जाओ clr_busy;
	rvt_add_rnr_समयr(sqp, qp->r_min_rnr_समयr <<
				IB_AETH_CREDIT_SHIFT);
	जाओ clr_busy;

op_err:
	send_status = IB_WC_REM_OP_ERR;
	wc.status = IB_WC_LOC_QP_OP_ERR;
	जाओ err;

inv_err:
	send_status =
		sqp->ibqp.qp_type == IB_QPT_RC ?
			IB_WC_REM_INV_REQ_ERR :
			IB_WC_SUCCESS;
	wc.status = IB_WC_LOC_QP_OP_ERR;
	जाओ err;

acc_err:
	send_status = IB_WC_REM_ACCESS_ERR;
	wc.status = IB_WC_LOC_PROT_ERR;
err:
	/* responder goes to error state */
	rvt_rc_error(qp, wc.status);

serr:
	spin_unlock_irqrestore(&qp->r_lock, flags);
serr_no_r_lock:
	spin_lock_irqsave(&sqp->s_lock, flags);
	rvt_send_complete(sqp, wqe, send_status);
	अगर (sqp->ibqp.qp_type == IB_QPT_RC) अणु
		पूर्णांक lastwqe = rvt_error_qp(sqp, IB_WC_WR_FLUSH_ERR);

		sqp->s_flags &= ~RVT_S_BUSY;
		spin_unlock_irqrestore(&sqp->s_lock, flags);
		अगर (lastwqe) अणु
			काष्ठा ib_event ev;

			ev.device = sqp->ibqp.device;
			ev.element.qp = &sqp->ibqp;
			ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
			sqp->ibqp.event_handler(&ev, sqp->ibqp.qp_context);
		पूर्ण
		जाओ करोne;
	पूर्ण
clr_busy:
	sqp->s_flags &= ~RVT_S_BUSY;
unlock:
	spin_unlock_irqrestore(&sqp->s_lock, flags);
करोne:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(rvt_ruc_loopback);
