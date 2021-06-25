<शैली गुरु>
/*
 * Copyright(c) 2015-2018 Intel Corporation.
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

#समावेश <linux/delay.h>
#समावेश "hfi.h"
#समावेश "qp.h"
#समावेश "trace.h"

#घोषणा SC(name) SEND_CTXT_##name
/*
 * Send Context functions
 */
अटल व्योम sc_रुको_क्रम_packet_egress(काष्ठा send_context *sc, पूर्णांक छोड़ो);

/*
 * Set the CM reset bit and रुको क्रम it to clear.  Use the provided
 * sendctrl रेजिस्टर.  This routine has no locking.
 */
व्योम __cm_reset(काष्ठा hfi1_devdata *dd, u64 sendctrl)
अणु
	ग_लिखो_csr(dd, SEND_CTRL, sendctrl | SEND_CTRL_CM_RESET_SMASK);
	जबतक (1) अणु
		udelay(1);
		sendctrl = पढ़ो_csr(dd, SEND_CTRL);
		अगर ((sendctrl & SEND_CTRL_CM_RESET_SMASK) == 0)
			अवरोध;
	पूर्ण
पूर्ण

/* global control of PIO send */
व्योम pio_send_control(काष्ठा hfi1_devdata *dd, पूर्णांक op)
अणु
	u64 reg, mask;
	अचिन्हित दीर्घ flags;
	पूर्णांक ग_लिखो = 1;	/* ग_लिखो sendctrl back */
	पूर्णांक flush = 0;	/* re-पढ़ो sendctrl to make sure it is flushed */
	पूर्णांक i;

	spin_lock_irqsave(&dd->sendctrl_lock, flags);

	reg = पढ़ो_csr(dd, SEND_CTRL);
	चयन (op) अणु
	हाल PSC_GLOBAL_ENABLE:
		reg |= SEND_CTRL_SEND_ENABLE_SMASK;
		fallthrough;
	हाल PSC_DATA_VL_ENABLE:
		mask = 0;
		क्रम (i = 0; i < ARRAY_SIZE(dd->vld); i++)
			अगर (!dd->vld[i].mtu)
				mask |= BIT_ULL(i);
		/* Disallow sending on VLs not enabled */
		mask = (mask & SEND_CTRL_UNSUPPORTED_VL_MASK) <<
			SEND_CTRL_UNSUPPORTED_VL_SHIFT;
		reg = (reg & ~SEND_CTRL_UNSUPPORTED_VL_SMASK) | mask;
		अवरोध;
	हाल PSC_GLOBAL_DISABLE:
		reg &= ~SEND_CTRL_SEND_ENABLE_SMASK;
		अवरोध;
	हाल PSC_GLOBAL_VLARB_ENABLE:
		reg |= SEND_CTRL_VL_ARBITER_ENABLE_SMASK;
		अवरोध;
	हाल PSC_GLOBAL_VLARB_DISABLE:
		reg &= ~SEND_CTRL_VL_ARBITER_ENABLE_SMASK;
		अवरोध;
	हाल PSC_CM_RESET:
		__cm_reset(dd, reg);
		ग_लिखो = 0; /* CSR alपढ़ोy written (and flushed) */
		अवरोध;
	हाल PSC_DATA_VL_DISABLE:
		reg |= SEND_CTRL_UNSUPPORTED_VL_SMASK;
		flush = 1;
		अवरोध;
	शेष:
		dd_dev_err(dd, "%s: invalid control %d\n", __func__, op);
		अवरोध;
	पूर्ण

	अगर (ग_लिखो) अणु
		ग_लिखो_csr(dd, SEND_CTRL, reg);
		अगर (flush)
			(व्योम)पढ़ो_csr(dd, SEND_CTRL); /* flush ग_लिखो */
	पूर्ण

	spin_unlock_irqrestore(&dd->sendctrl_lock, flags);
पूर्ण

/* number of send context memory pools */
#घोषणा NUM_SC_POOLS 2

/* Send Context Size (SCS) wildcards */
#घोषणा SCS_POOL_0 -1
#घोषणा SCS_POOL_1 -2

/* Send Context Count (SCC) wildcards */
#घोषणा SCC_PER_VL -1
#घोषणा SCC_PER_CPU  -2
#घोषणा SCC_PER_KRCVQ  -3

/* Send Context Size (SCS) स्थिरants */
#घोषणा SCS_ACK_CREDITS  32
#घोषणा SCS_VL15_CREDITS 102	/* 3 pkts of 2048B data + 128B header */

#घोषणा PIO_THRESHOLD_CEILING 4096

#घोषणा PIO_WAIT_BATCH_SIZE 5

/* शेष send context sizes */
अटल काष्ठा sc_config_sizes sc_config_sizes[SC_MAX] = अणु
	[SC_KERNEL] = अणु .size  = SCS_POOL_0,	/* even भागide, pool 0 */
			.count = SCC_PER_VL पूर्ण,	/* one per NUMA */
	[SC_ACK]    = अणु .size  = SCS_ACK_CREDITS,
			.count = SCC_PER_KRCVQ पूर्ण,
	[SC_USER]   = अणु .size  = SCS_POOL_0,	/* even भागide, pool 0 */
			.count = SCC_PER_CPU पूर्ण,	/* one per CPU */
	[SC_VL15]   = अणु .size  = SCS_VL15_CREDITS,
			.count = 1 पूर्ण,

पूर्ण;

/* send context memory pool configuration */
काष्ठा mem_pool_config अणु
	पूर्णांक centipercent;	/* % of memory, in 100ths of 1% */
	पूर्णांक असलolute_blocks;	/* असलolute block count */
पूर्ण;

/* शेष memory pool configuration: 100% in pool 0 */
अटल काष्ठा mem_pool_config sc_mem_pool_config[NUM_SC_POOLS] = अणु
	/* centi%, असल blocks */
	अणु  10000,     -1 पूर्ण,		/* pool 0 */
	अणु      0,     -1 पूर्ण,		/* pool 1 */
पूर्ण;

/* memory pool inक्रमmation, used when calculating final sizes */
काष्ठा mem_pool_info अणु
	पूर्णांक centipercent;	/*
				 * 100th of 1% of memory to use, -1 अगर blocks
				 * alपढ़ोy set
				 */
	पूर्णांक count;		/* count of contexts in the pool */
	पूर्णांक blocks;		/* block size of the pool */
	पूर्णांक size;		/* context size, in blocks */
पूर्ण;

/*
 * Convert a pool wildcard to a valid pool index.  The wildcards
 * start at -1 and increase negatively.  Map them as:
 *	-1 => 0
 *	-2 => 1
 *	etc.
 *
 * Return -1 on non-wildcard input, otherwise convert to a pool number.
 */
अटल पूर्णांक wildcard_to_pool(पूर्णांक wc)
अणु
	अगर (wc >= 0)
		वापस -1;	/* non-wildcard */
	वापस -wc - 1;
पूर्ण

अटल स्थिर अक्षर *sc_type_names[SC_MAX] = अणु
	"kernel",
	"ack",
	"user",
	"vl15"
पूर्ण;

अटल स्थिर अक्षर *sc_type_name(पूर्णांक index)
अणु
	अगर (index < 0 || index >= SC_MAX)
		वापस "unknown";
	वापस sc_type_names[index];
पूर्ण

/*
 * Read the send context memory pool configuration and send context
 * size configuration.  Replace any wildcards and come up with final
 * counts and sizes क्रम the send context types.
 */
पूर्णांक init_sc_pools_and_sizes(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा mem_pool_info mem_pool_info[NUM_SC_POOLS] = अणु अणु 0 पूर्ण पूर्ण;
	पूर्णांक total_blocks = (chip_pio_mem_size(dd) / PIO_BLOCK_SIZE) - 1;
	पूर्णांक total_contexts = 0;
	पूर्णांक fixed_blocks;
	पूर्णांक pool_blocks;
	पूर्णांक used_blocks;
	पूर्णांक cp_total;		/* centipercent total */
	पूर्णांक ab_total;		/* असलolute block total */
	पूर्णांक extra;
	पूर्णांक i;

	/*
	 * When SDMA is enabled, kernel context pio packet size is capped by
	 * "piothreshold". Reduce pio buffer allocation क्रम kernel context by
	 * setting it to a fixed size. The allocation allows 3-deep buffering
	 * of the largest pio packets plus up to 128 bytes header, sufficient
	 * to मुख्यtain verbs perक्रमmance.
	 *
	 * When SDMA is disabled, keep the शेष pooling allocation.
	 */
	अगर (HFI1_CAP_IS_KSET(SDMA)) अणु
		u16 max_pkt_size = (piothreshold < PIO_THRESHOLD_CEILING) ?
					 piothreshold : PIO_THRESHOLD_CEILING;
		sc_config_sizes[SC_KERNEL].size =
			3 * (max_pkt_size + 128) / PIO_BLOCK_SIZE;
	पूर्ण

	/*
	 * Step 0:
	 *	- copy the centipercents/असलolute sizes from the pool config
	 *	- sanity check these values
	 *	- add up centipercents, then later check क्रम full value
	 *	- add up असलolute blocks, then later check क्रम over-commit
	 */
	cp_total = 0;
	ab_total = 0;
	क्रम (i = 0; i < NUM_SC_POOLS; i++) अणु
		पूर्णांक cp = sc_mem_pool_config[i].centipercent;
		पूर्णांक ab = sc_mem_pool_config[i].असलolute_blocks;

		/*
		 * A negative value is "unused" or "invalid".  Both *can*
		 * be valid, but centipercent wins, so check that first
		 */
		अगर (cp >= 0) अणु			/* centipercent valid */
			cp_total += cp;
		पूर्ण अन्यथा अगर (ab >= 0) अणु		/* असलolute blocks valid */
			ab_total += ab;
		पूर्ण अन्यथा अणु			/* neither valid */
			dd_dev_err(
				dd,
				"Send context memory pool %d: both the block count and centipercent are invalid\n",
				i);
			वापस -EINVAL;
		पूर्ण

		mem_pool_info[i].centipercent = cp;
		mem_pool_info[i].blocks = ab;
	पूर्ण

	/* करो not use both % and असलolute blocks क्रम dअगरferent pools */
	अगर (cp_total != 0 && ab_total != 0) अणु
		dd_dev_err(
			dd,
			"All send context memory pools must be described as either centipercent or blocks, no mixing between pools\n");
		वापस -EINVAL;
	पूर्ण

	/* अगर any percentages are present, they must add up to 100% x 100 */
	अगर (cp_total != 0 && cp_total != 10000) अणु
		dd_dev_err(
			dd,
			"Send context memory pool centipercent is %d, expecting 10000\n",
			cp_total);
		वापस -EINVAL;
	पूर्ण

	/* the असलolute pool total cannot be more than the mem total */
	अगर (ab_total > total_blocks) अणु
		dd_dev_err(
			dd,
			"Send context memory pool absolute block count %d is larger than the memory size %d\n",
			ab_total, total_blocks);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Step 2:
	 *	- copy from the context size config
	 *	- replace context type wildcard counts with real values
	 *	- add up non-memory pool block sizes
	 *	- add up memory pool user counts
	 */
	fixed_blocks = 0;
	क्रम (i = 0; i < SC_MAX; i++) अणु
		पूर्णांक count = sc_config_sizes[i].count;
		पूर्णांक size = sc_config_sizes[i].size;
		पूर्णांक pool;

		/*
		 * Sanity check count: Either a positive value or
		 * one of the expected wildcards is valid.  The positive
		 * value is checked later when we compare against total
		 * memory available.
		 */
		अगर (i == SC_ACK) अणु
			count = dd->n_krcv_queues;
		पूर्ण अन्यथा अगर (i == SC_KERNEL) अणु
			count = INIT_SC_PER_VL * num_vls;
		पूर्ण अन्यथा अगर (count == SCC_PER_CPU) अणु
			count = dd->num_rcv_contexts - dd->n_krcv_queues;
		पूर्ण अन्यथा अगर (count < 0) अणु
			dd_dev_err(
				dd,
				"%s send context invalid count wildcard %d\n",
				sc_type_name(i), count);
			वापस -EINVAL;
		पूर्ण
		अगर (total_contexts + count > chip_send_contexts(dd))
			count = chip_send_contexts(dd) - total_contexts;

		total_contexts += count;

		/*
		 * Sanity check pool: The conversion will वापस a pool
		 * number or -1 अगर a fixed (non-negative) value.  The fixed
		 * value is checked later when we compare against
		 * total memory available.
		 */
		pool = wildcard_to_pool(size);
		अगर (pool == -1) अणु			/* non-wildcard */
			fixed_blocks += size * count;
		पूर्ण अन्यथा अगर (pool < NUM_SC_POOLS) अणु	/* valid wildcard */
			mem_pool_info[pool].count += count;
		पूर्ण अन्यथा अणु				/* invalid wildcard */
			dd_dev_err(
				dd,
				"%s send context invalid pool wildcard %d\n",
				sc_type_name(i), size);
			वापस -EINVAL;
		पूर्ण

		dd->sc_sizes[i].count = count;
		dd->sc_sizes[i].size = size;
	पूर्ण
	अगर (fixed_blocks > total_blocks) अणु
		dd_dev_err(
			dd,
			"Send context fixed block count, %u, larger than total block count %u\n",
			fixed_blocks, total_blocks);
		वापस -EINVAL;
	पूर्ण

	/* step 3: calculate the blocks in the pools, and pool context sizes */
	pool_blocks = total_blocks - fixed_blocks;
	अगर (ab_total > pool_blocks) अणु
		dd_dev_err(
			dd,
			"Send context fixed pool sizes, %u, larger than pool block count %u\n",
			ab_total, pool_blocks);
		वापस -EINVAL;
	पूर्ण
	/* subtract off the fixed pool blocks */
	pool_blocks -= ab_total;

	क्रम (i = 0; i < NUM_SC_POOLS; i++) अणु
		काष्ठा mem_pool_info *pi = &mem_pool_info[i];

		/* % beats असलolute blocks */
		अगर (pi->centipercent >= 0)
			pi->blocks = (pool_blocks * pi->centipercent) / 10000;

		अगर (pi->blocks == 0 && pi->count != 0) अणु
			dd_dev_err(
				dd,
				"Send context memory pool %d has %u contexts, but no blocks\n",
				i, pi->count);
			वापस -EINVAL;
		पूर्ण
		अगर (pi->count == 0) अणु
			/* warn about wasted blocks */
			अगर (pi->blocks != 0)
				dd_dev_err(
					dd,
					"Send context memory pool %d has %u blocks, but zero contexts\n",
					i, pi->blocks);
			pi->size = 0;
		पूर्ण अन्यथा अणु
			pi->size = pi->blocks / pi->count;
		पूर्ण
	पूर्ण

	/* step 4: fill in the context type sizes from the pool sizes */
	used_blocks = 0;
	क्रम (i = 0; i < SC_MAX; i++) अणु
		अगर (dd->sc_sizes[i].size < 0) अणु
			अचिन्हित pool = wildcard_to_pool(dd->sc_sizes[i].size);

			WARN_ON_ONCE(pool >= NUM_SC_POOLS);
			dd->sc_sizes[i].size = mem_pool_info[pool].size;
		पूर्ण
		/* make sure we are not larger than what is allowed by the HW */
#घोषणा PIO_MAX_BLOCKS 1024
		अगर (dd->sc_sizes[i].size > PIO_MAX_BLOCKS)
			dd->sc_sizes[i].size = PIO_MAX_BLOCKS;

		/* calculate our total usage */
		used_blocks += dd->sc_sizes[i].size * dd->sc_sizes[i].count;
	पूर्ण
	extra = total_blocks - used_blocks;
	अगर (extra != 0)
		dd_dev_info(dd, "unused send context blocks: %d\n", extra);

	वापस total_contexts;
पूर्ण

पूर्णांक init_send_contexts(काष्ठा hfi1_devdata *dd)
अणु
	u16 base;
	पूर्णांक ret, i, j, context;

	ret = init_credit_वापस(dd);
	अगर (ret)
		वापस ret;

	dd->hw_to_sw = kदो_स्मृति_array(TXE_NUM_CONTEXTS, माप(u8),
					GFP_KERNEL);
	dd->send_contexts = kसुस्मृति(dd->num_send_contexts,
				    माप(काष्ठा send_context_info),
				    GFP_KERNEL);
	अगर (!dd->send_contexts || !dd->hw_to_sw) अणु
		kमुक्त(dd->hw_to_sw);
		kमुक्त(dd->send_contexts);
		मुक्त_credit_वापस(dd);
		वापस -ENOMEM;
	पूर्ण

	/* hardware context map starts with invalid send context indices */
	क्रम (i = 0; i < TXE_NUM_CONTEXTS; i++)
		dd->hw_to_sw[i] = INVALID_SCI;

	/*
	 * All send contexts have their credit sizes.  Allocate credits
	 * क्रम each context one after another from the global space.
	 */
	context = 0;
	base = 1;
	क्रम (i = 0; i < SC_MAX; i++) अणु
		काष्ठा sc_config_sizes *scs = &dd->sc_sizes[i];

		क्रम (j = 0; j < scs->count; j++) अणु
			काष्ठा send_context_info *sci =
						&dd->send_contexts[context];
			sci->type = i;
			sci->base = base;
			sci->credits = scs->size;

			context++;
			base += scs->size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Allocate a software index and hardware context of the given type.
 *
 * Must be called with dd->sc_lock held.
 */
अटल पूर्णांक sc_hw_alloc(काष्ठा hfi1_devdata *dd, पूर्णांक type, u32 *sw_index,
		       u32 *hw_context)
अणु
	काष्ठा send_context_info *sci;
	u32 index;
	u32 context;

	क्रम (index = 0, sci = &dd->send_contexts[0];
			index < dd->num_send_contexts; index++, sci++) अणु
		अगर (sci->type == type && sci->allocated == 0) अणु
			sci->allocated = 1;
			/* use a 1:1 mapping, but make them non-equal */
			context = chip_send_contexts(dd) - index - 1;
			dd->hw_to_sw[context] = index;
			*sw_index = index;
			*hw_context = context;
			वापस 0; /* success */
		पूर्ण
	पूर्ण
	dd_dev_err(dd, "Unable to locate a free type %d send context\n", type);
	वापस -ENOSPC;
पूर्ण

/*
 * Free the send context given by its software index.
 *
 * Must be called with dd->sc_lock held.
 */
अटल व्योम sc_hw_मुक्त(काष्ठा hfi1_devdata *dd, u32 sw_index, u32 hw_context)
अणु
	काष्ठा send_context_info *sci;

	sci = &dd->send_contexts[sw_index];
	अगर (!sci->allocated) अणु
		dd_dev_err(dd, "%s: sw_index %u not allocated? hw_context %u\n",
			   __func__, sw_index, hw_context);
	पूर्ण
	sci->allocated = 0;
	dd->hw_to_sw[hw_context] = INVALID_SCI;
पूर्ण

/* वापस the base context of a context in a group */
अटल अंतरभूत u32 group_context(u32 context, u32 group)
अणु
	वापस (context >> group) << group;
पूर्ण

/* वापस the size of a group */
अटल अंतरभूत u32 group_size(u32 group)
अणु
	वापस 1 << group;
पूर्ण

/*
 * Obtain the credit वापस addresses, kernel भव and bus, क्रम the
 * given sc.
 *
 * To understand this routine:
 * o va and dma are arrays of काष्ठा credit_वापस.  One क्रम each physical
 *   send context, per NUMA.
 * o Each send context always looks in its relative location in a काष्ठा
 *   credit_वापस क्रम its credit वापस.
 * o Each send context in a group must have its वापस address CSR programmed
 *   with the same value.  Use the address of the first send context in the
 *   group.
 */
अटल व्योम cr_group_addresses(काष्ठा send_context *sc, dma_addr_t *dma)
अणु
	u32 gc = group_context(sc->hw_context, sc->group);
	u32 index = sc->hw_context & 0x7;

	sc->hw_मुक्त = &sc->dd->cr_base[sc->node].va[gc].cr[index];
	*dma = (अचिन्हित दीर्घ)
	       &((काष्ठा credit_वापस *)sc->dd->cr_base[sc->node].dma)[gc];
पूर्ण

/*
 * Work queue function triggered in error पूर्णांकerrupt routine क्रम
 * kernel contexts.
 */
अटल व्योम sc_halted(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा send_context *sc;

	sc = container_of(work, काष्ठा send_context, halt_work);
	sc_restart(sc);
पूर्ण

/*
 * Calculate PIO block threshold क्रम this send context using the given MTU.
 * Trigger a वापस when one MTU plus optional header of credits reमुख्य.
 *
 * Parameter mtu is in bytes.
 * Parameter hdrqentsize is in DWORDs.
 *
 * Return value is what to ग_लिखो पूर्णांकo the CSR: trigger वापस when
 * unवापसed credits pass this count.
 */
u32 sc_mtu_to_threshold(काष्ठा send_context *sc, u32 mtu, u32 hdrqentsize)
अणु
	u32 release_credits;
	u32 threshold;

	/* add in the header size, then भागide by the PIO block size */
	mtu += hdrqentsize << 2;
	release_credits = DIV_ROUND_UP(mtu, PIO_BLOCK_SIZE);

	/* check against this context's credits */
	अगर (sc->credits <= release_credits)
		threshold = 1;
	अन्यथा
		threshold = sc->credits - release_credits;

	वापस threshold;
पूर्ण

/*
 * Calculate credit threshold in terms of percent of the allocated credits.
 * Trigger when unवापसed credits equal or exceed the percentage of the whole.
 *
 * Return value is what to ग_लिखो पूर्णांकo the CSR: trigger वापस when
 * unवापसed credits pass this count.
 */
u32 sc_percent_to_threshold(काष्ठा send_context *sc, u32 percent)
अणु
	वापस (sc->credits * percent) / 100;
पूर्ण

/*
 * Set the credit वापस threshold.
 */
व्योम sc_set_cr_threshold(काष्ठा send_context *sc, u32 new_threshold)
अणु
	अचिन्हित दीर्घ flags;
	u32 old_threshold;
	पूर्णांक क्रमce_वापस = 0;

	spin_lock_irqsave(&sc->credit_ctrl_lock, flags);

	old_threshold = (sc->credit_ctrl >>
				SC(CREDIT_CTRL_THRESHOLD_SHIFT))
			 & SC(CREDIT_CTRL_THRESHOLD_MASK);

	अगर (new_threshold != old_threshold) अणु
		sc->credit_ctrl =
			(sc->credit_ctrl
				& ~SC(CREDIT_CTRL_THRESHOLD_SMASK))
			| ((new_threshold
				& SC(CREDIT_CTRL_THRESHOLD_MASK))
			   << SC(CREDIT_CTRL_THRESHOLD_SHIFT));
		ग_लिखो_kctxt_csr(sc->dd, sc->hw_context,
				SC(CREDIT_CTRL), sc->credit_ctrl);

		/* क्रमce a credit वापस on change to aव्योम a possible stall */
		क्रमce_वापस = 1;
	पूर्ण

	spin_unlock_irqrestore(&sc->credit_ctrl_lock, flags);

	अगर (क्रमce_वापस)
		sc_वापस_credits(sc);
पूर्ण

/*
 * set_pio_पूर्णांकegrity
 *
 * Set the CHECK_ENABLE रेजिस्टर क्रम the send context 'sc'.
 */
व्योम set_pio_पूर्णांकegrity(काष्ठा send_context *sc)
अणु
	काष्ठा hfi1_devdata *dd = sc->dd;
	u32 hw_context = sc->hw_context;
	पूर्णांक type = sc->type;

	ग_लिखो_kctxt_csr(dd, hw_context,
			SC(CHECK_ENABLE),
			hfi1_pkt_शेष_send_ctxt_mask(dd, type));
पूर्ण

अटल u32 get_buffers_allocated(काष्ठा send_context *sc)
अणु
	पूर्णांक cpu;
	u32 ret = 0;

	क्रम_each_possible_cpu(cpu)
		ret += *per_cpu_ptr(sc->buffers_allocated, cpu);
	वापस ret;
पूर्ण

अटल व्योम reset_buffers_allocated(काष्ठा send_context *sc)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		(*per_cpu_ptr(sc->buffers_allocated, cpu)) = 0;
पूर्ण

/*
 * Allocate a NUMA relative send context काष्ठाure of the given type aदीर्घ
 * with a HW context.
 */
काष्ठा send_context *sc_alloc(काष्ठा hfi1_devdata *dd, पूर्णांक type,
			      uपूर्णांक hdrqentsize, पूर्णांक numa)
अणु
	काष्ठा send_context_info *sci;
	काष्ठा send_context *sc = शून्य;
	dma_addr_t dma;
	अचिन्हित दीर्घ flags;
	u64 reg;
	u32 thresh;
	u32 sw_index;
	u32 hw_context;
	पूर्णांक ret;
	u8 opval, opmask;

	/* करो not allocate जबतक frozen */
	अगर (dd->flags & HFI1_FROZEN)
		वापस शून्य;

	sc = kzalloc_node(माप(*sc), GFP_KERNEL, numa);
	अगर (!sc)
		वापस शून्य;

	sc->buffers_allocated = alloc_percpu(u32);
	अगर (!sc->buffers_allocated) अणु
		kमुक्त(sc);
		dd_dev_err(dd,
			   "Cannot allocate buffers_allocated per cpu counters\n"
			  );
		वापस शून्य;
	पूर्ण

	spin_lock_irqsave(&dd->sc_lock, flags);
	ret = sc_hw_alloc(dd, type, &sw_index, &hw_context);
	अगर (ret) अणु
		spin_unlock_irqrestore(&dd->sc_lock, flags);
		मुक्त_percpu(sc->buffers_allocated);
		kमुक्त(sc);
		वापस शून्य;
	पूर्ण

	sci = &dd->send_contexts[sw_index];
	sci->sc = sc;

	sc->dd = dd;
	sc->node = numa;
	sc->type = type;
	spin_lock_init(&sc->alloc_lock);
	spin_lock_init(&sc->release_lock);
	spin_lock_init(&sc->credit_ctrl_lock);
	seqlock_init(&sc->रुकोlock);
	INIT_LIST_HEAD(&sc->pioरुको);
	INIT_WORK(&sc->halt_work, sc_halted);
	init_रुकोqueue_head(&sc->halt_रुको);

	/* grouping is always single context क्रम now */
	sc->group = 0;

	sc->sw_index = sw_index;
	sc->hw_context = hw_context;
	cr_group_addresses(sc, &dma);
	sc->credits = sci->credits;
	sc->size = sc->credits * PIO_BLOCK_SIZE;

/* PIO Send Memory Address details */
#घोषणा PIO_ADDR_CONTEXT_MASK 0xfful
#घोषणा PIO_ADDR_CONTEXT_SHIFT 16
	sc->base_addr = dd->piobase + ((hw_context & PIO_ADDR_CONTEXT_MASK)
					<< PIO_ADDR_CONTEXT_SHIFT);

	/* set base and credits */
	reg = ((sci->credits & SC(CTRL_CTXT_DEPTH_MASK))
					<< SC(CTRL_CTXT_DEPTH_SHIFT))
		| ((sci->base & SC(CTRL_CTXT_BASE_MASK))
					<< SC(CTRL_CTXT_BASE_SHIFT));
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CTRL), reg);

	set_pio_पूर्णांकegrity(sc);

	/* unmask all errors */
	ग_लिखो_kctxt_csr(dd, hw_context, SC(ERR_MASK), (u64)-1);

	/* set the शेष partition key */
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CHECK_PARTITION_KEY),
			(SC(CHECK_PARTITION_KEY_VALUE_MASK) &
			 DEFAULT_PKEY) <<
			SC(CHECK_PARTITION_KEY_VALUE_SHIFT));

	/* per context type checks */
	अगर (type == SC_USER) अणु
		opval = USER_OPCODE_CHECK_VAL;
		opmask = USER_OPCODE_CHECK_MASK;
	पूर्ण अन्यथा अणु
		opval = OPCODE_CHECK_VAL_DISABLED;
		opmask = OPCODE_CHECK_MASK_DISABLED;
	पूर्ण

	/* set the send context check opcode mask and value */
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CHECK_OPCODE),
			((u64)opmask << SC(CHECK_OPCODE_MASK_SHIFT)) |
			((u64)opval << SC(CHECK_OPCODE_VALUE_SHIFT)));

	/* set up credit वापस */
	reg = dma & SC(CREDIT_RETURN_ADDR_ADDRESS_SMASK);
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CREDIT_RETURN_ADDR), reg);

	/*
	 * Calculate the initial credit वापस threshold.
	 *
	 * For Ack contexts, set a threshold क्रम half the credits.
	 * For User contexts use the given percentage.  This has been
	 * sanitized on driver start-up.
	 * For Kernel contexts, use the शेष MTU plus a header
	 * or half the credits, whichever is smaller. This should
	 * work क्रम both the 3-deep buffering allocation and the
	 * pooling allocation.
	 */
	अगर (type == SC_ACK) अणु
		thresh = sc_percent_to_threshold(sc, 50);
	पूर्ण अन्यथा अगर (type == SC_USER) अणु
		thresh = sc_percent_to_threshold(sc,
						 user_credit_वापस_threshold);
	पूर्ण अन्यथा अणु /* kernel */
		thresh = min(sc_percent_to_threshold(sc, 50),
			     sc_mtu_to_threshold(sc, hfi1_max_mtu,
						 hdrqentsize));
	पूर्ण
	reg = thresh << SC(CREDIT_CTRL_THRESHOLD_SHIFT);
	/* add in early वापस */
	अगर (type == SC_USER && HFI1_CAP_IS_USET(EARLY_CREDIT_RETURN))
		reg |= SC(CREDIT_CTRL_EARLY_RETURN_SMASK);
	अन्यथा अगर (HFI1_CAP_IS_KSET(EARLY_CREDIT_RETURN)) /* kernel, ack */
		reg |= SC(CREDIT_CTRL_EARLY_RETURN_SMASK);

	/* set up ग_लिखो-through credit_ctrl */
	sc->credit_ctrl = reg;
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CREDIT_CTRL), reg);

	/* User send contexts should not allow sending on VL15 */
	अगर (type == SC_USER) अणु
		reg = 1ULL << 15;
		ग_लिखो_kctxt_csr(dd, hw_context, SC(CHECK_VL), reg);
	पूर्ण

	spin_unlock_irqrestore(&dd->sc_lock, flags);

	/*
	 * Allocate shaकरोw ring to track outstanding PIO buffers _after_
	 * unlocking.  We करोn't know the size until the lock is held and
	 * we can't allocate जबतक the lock is held.  No one is using
	 * the context yet, so allocate it now.
	 *
	 * User contexts करो not get a shaकरोw ring.
	 */
	अगर (type != SC_USER) अणु
		/*
		 * Size the shaकरोw ring 1 larger than the number of credits
		 * so head == tail can mean empty.
		 */
		sc->sr_size = sci->credits + 1;
		sc->sr = kसुस्मृति_node(sc->sr_size,
				      माप(जोड़ pio_shaकरोw_ring),
				      GFP_KERNEL, numa);
		अगर (!sc->sr) अणु
			sc_मुक्त(sc);
			वापस शून्य;
		पूर्ण
	पूर्ण

	hfi1_cdbg(PIO,
		  "Send context %u(%u) %s group %u credits %u credit_ctrl 0x%llx threshold %u\n",
		  sw_index,
		  hw_context,
		  sc_type_name(type),
		  sc->group,
		  sc->credits,
		  sc->credit_ctrl,
		  thresh);

	वापस sc;
पूर्ण

/* मुक्त a per-NUMA send context काष्ठाure */
व्योम sc_मुक्त(काष्ठा send_context *sc)
अणु
	काष्ठा hfi1_devdata *dd;
	अचिन्हित दीर्घ flags;
	u32 sw_index;
	u32 hw_context;

	अगर (!sc)
		वापस;

	sc->flags |= SCF_IN_FREE;	/* ensure no restarts */
	dd = sc->dd;
	अगर (!list_empty(&sc->pioरुको))
		dd_dev_err(dd, "piowait list not empty!\n");
	sw_index = sc->sw_index;
	hw_context = sc->hw_context;
	sc_disable(sc);	/* make sure the HW is disabled */
	flush_work(&sc->halt_work);

	spin_lock_irqsave(&dd->sc_lock, flags);
	dd->send_contexts[sw_index].sc = शून्य;

	/* clear/disable all रेजिस्टरs set in sc_alloc */
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CTRL), 0);
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CHECK_ENABLE), 0);
	ग_लिखो_kctxt_csr(dd, hw_context, SC(ERR_MASK), 0);
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CHECK_PARTITION_KEY), 0);
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CHECK_OPCODE), 0);
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CREDIT_RETURN_ADDR), 0);
	ग_लिखो_kctxt_csr(dd, hw_context, SC(CREDIT_CTRL), 0);

	/* release the index and context क्रम re-use */
	sc_hw_मुक्त(dd, sw_index, hw_context);
	spin_unlock_irqrestore(&dd->sc_lock, flags);

	kमुक्त(sc->sr);
	मुक्त_percpu(sc->buffers_allocated);
	kमुक्त(sc);
पूर्ण

/* disable the context */
व्योम sc_disable(काष्ठा send_context *sc)
अणु
	u64 reg;
	काष्ठा pio_buf *pbuf;

	अगर (!sc)
		वापस;

	/* करो all steps, even अगर alपढ़ोy disabled */
	spin_lock_irq(&sc->alloc_lock);
	reg = पढ़ो_kctxt_csr(sc->dd, sc->hw_context, SC(CTRL));
	reg &= ~SC(CTRL_CTXT_ENABLE_SMASK);
	sc->flags &= ~SCF_ENABLED;
	sc_रुको_क्रम_packet_egress(sc, 1);
	ग_लिखो_kctxt_csr(sc->dd, sc->hw_context, SC(CTRL), reg);

	/*
	 * Flush any रुकोers.  Once the context is disabled,
	 * credit वापस पूर्णांकerrupts are stopped (although there
	 * could be one in-process when the context is disabled).
	 * Wait one microsecond क्रम any lingering पूर्णांकerrupts, then
	 * proceed with the flush.
	 */
	udelay(1);
	spin_lock(&sc->release_lock);
	अगर (sc->sr) अणु	/* this context has a shaकरोw ring */
		जबतक (sc->sr_tail != sc->sr_head) अणु
			pbuf = &sc->sr[sc->sr_tail].pbuf;
			अगर (pbuf->cb)
				(*pbuf->cb)(pbuf->arg, PRC_SC_DISABLE);
			sc->sr_tail++;
			अगर (sc->sr_tail >= sc->sr_size)
				sc->sr_tail = 0;
		पूर्ण
	पूर्ण
	spin_unlock(&sc->release_lock);

	ग_लिखो_seqlock(&sc->रुकोlock);
	जबतक (!list_empty(&sc->pioरुको)) अणु
		काष्ठा ioरुको *रुको;
		काष्ठा rvt_qp *qp;
		काष्ठा hfi1_qp_priv *priv;

		रुको = list_first_entry(&sc->pioरुको, काष्ठा ioरुको, list);
		qp = ioरुको_to_qp(रुको);
		priv = qp->priv;
		list_del_init(&priv->s_ioरुको.list);
		priv->s_ioरुको.lock = शून्य;
		hfi1_qp_wakeup(qp, RVT_S_WAIT_PIO | HFI1_S_WAIT_PIO_DRAIN);
	पूर्ण
	ग_लिखो_sequnlock(&sc->रुकोlock);

	spin_unlock_irq(&sc->alloc_lock);
पूर्ण

/* वापस SendEgressCtxtStatus.PacketOccupancy */
अटल u64 packet_occupancy(u64 reg)
अणु
	वापस (reg &
		SEND_EGRESS_CTXT_STATUS_CTXT_EGRESS_PACKET_OCCUPANCY_SMASK)
		>> SEND_EGRESS_CTXT_STATUS_CTXT_EGRESS_PACKET_OCCUPANCY_SHIFT;
पूर्ण

/* is egress halted on the context? */
अटल bool egress_halted(u64 reg)
अणु
	वापस !!(reg & SEND_EGRESS_CTXT_STATUS_CTXT_EGRESS_HALT_STATUS_SMASK);
पूर्ण

/* is the send context halted? */
अटल bool is_sc_halted(काष्ठा hfi1_devdata *dd, u32 hw_context)
अणु
	वापस !!(पढ़ो_kctxt_csr(dd, hw_context, SC(STATUS)) &
		  SC(STATUS_CTXT_HALTED_SMASK));
पूर्ण

/**
 * sc_रुको_क्रम_packet_egress
 * @sc: valid send context
 * @छोड़ो: रुको क्रम credit वापस
 *
 * Wait क्रम packet egress, optionally छोड़ो क्रम credit वापस
 *
 * Egress halt and Context halt are not necessarily the same thing, so
 * check क्रम both.
 *
 * NOTE: The context halt bit may not be set immediately.  Because of this,
 * it is necessary to check the SW SFC_HALTED bit (set in the IRQ) and the HW
 * context bit to determine अगर the context is halted.
 */
अटल व्योम sc_रुको_क्रम_packet_egress(काष्ठा send_context *sc, पूर्णांक छोड़ो)
अणु
	काष्ठा hfi1_devdata *dd = sc->dd;
	u64 reg = 0;
	u64 reg_prev;
	u32 loop = 0;

	जबतक (1) अणु
		reg_prev = reg;
		reg = पढ़ो_csr(dd, sc->hw_context * 8 +
			       SEND_EGRESS_CTXT_STATUS);
		/* करोne अगर any halt bits, SW or HW are set */
		अगर (sc->flags & SCF_HALTED ||
		    is_sc_halted(dd, sc->hw_context) || egress_halted(reg))
			अवरोध;
		reg = packet_occupancy(reg);
		अगर (reg == 0)
			अवरोध;
		/* counter is reset अगर occupancy count changes */
		अगर (reg != reg_prev)
			loop = 0;
		अगर (loop > 50000) अणु
			/* समयd out - bounce the link */
			dd_dev_err(dd,
				   "%s: context %u(%u) timeout waiting for packets to egress, remaining count %u, bouncing link\n",
				   __func__, sc->sw_index,
				   sc->hw_context, (u32)reg);
			queue_work(dd->pport->link_wq,
				   &dd->pport->link_bounce_work);
			अवरोध;
		पूर्ण
		loop++;
		udelay(1);
	पूर्ण

	अगर (छोड़ो)
		/* Add additional delay to ensure chip वापसs all credits */
		छोड़ो_क्रम_credit_वापस(dd);
पूर्ण

व्योम sc_रुको(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dd->num_send_contexts; i++) अणु
		काष्ठा send_context *sc = dd->send_contexts[i].sc;

		अगर (!sc)
			जारी;
		sc_रुको_क्रम_packet_egress(sc, 0);
	पूर्ण
पूर्ण

/*
 * Restart a context after it has been halted due to error.
 *
 * If the first step fails - रुको क्रम the halt to be निश्चितed, वापस early.
 * Otherwise complain about समयouts but keep going.
 *
 * It is expected that allocations (enabled flag bit) have been shut off
 * alपढ़ोy (only applies to kernel contexts).
 */
पूर्णांक sc_restart(काष्ठा send_context *sc)
अणु
	काष्ठा hfi1_devdata *dd = sc->dd;
	u64 reg;
	u32 loop;
	पूर्णांक count;

	/* bounce off अगर not halted, or being मुक्त'd */
	अगर (!(sc->flags & SCF_HALTED) || (sc->flags & SCF_IN_FREE))
		वापस -EINVAL;

	dd_dev_info(dd, "restarting send context %u(%u)\n", sc->sw_index,
		    sc->hw_context);

	/*
	 * Step 1: Wait क्रम the context to actually halt.
	 *
	 * The error पूर्णांकerrupt is asynchronous to actually setting halt
	 * on the context.
	 */
	loop = 0;
	जबतक (1) अणु
		reg = पढ़ो_kctxt_csr(dd, sc->hw_context, SC(STATUS));
		अगर (reg & SC(STATUS_CTXT_HALTED_SMASK))
			अवरोध;
		अगर (loop > 100) अणु
			dd_dev_err(dd, "%s: context %u(%u) not halting, skipping\n",
				   __func__, sc->sw_index, sc->hw_context);
			वापस -ETIME;
		पूर्ण
		loop++;
		udelay(1);
	पूर्ण

	/*
	 * Step 2: Ensure no users are still trying to ग_लिखो to PIO.
	 *
	 * For kernel contexts, we have alपढ़ोy turned off buffer allocation.
	 * Now रुको क्रम the buffer count to go to zero.
	 *
	 * For user contexts, the user handling code has cut off ग_लिखो access
	 * to the context's PIO pages beक्रमe calling this routine and will
	 * restore ग_लिखो access after this routine वापसs.
	 */
	अगर (sc->type != SC_USER) अणु
		/* kernel context */
		loop = 0;
		जबतक (1) अणु
			count = get_buffers_allocated(sc);
			अगर (count == 0)
				अवरोध;
			अगर (loop > 100) अणु
				dd_dev_err(dd,
					   "%s: context %u(%u) timeout waiting for PIO buffers to zero, remaining %d\n",
					   __func__, sc->sw_index,
					   sc->hw_context, count);
			पूर्ण
			loop++;
			udelay(1);
		पूर्ण
	पूर्ण

	/*
	 * Step 3: Wait क्रम all packets to egress.
	 * This is करोne जबतक disabling the send context
	 *
	 * Step 4: Disable the context
	 *
	 * This is a superset of the halt.  After the disable, the
	 * errors can be cleared.
	 */
	sc_disable(sc);

	/*
	 * Step 5: Enable the context
	 *
	 * This enable will clear the halted flag and per-send context
	 * error flags.
	 */
	वापस sc_enable(sc);
पूर्ण

/*
 * PIO मुक्तze processing.  To be called after the TXE block is fully frozen.
 * Go through all frozen send contexts and disable them.  The contexts are
 * alपढ़ोy stopped by the मुक्तze.
 */
व्योम pio_मुक्तze(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा send_context *sc;
	पूर्णांक i;

	क्रम (i = 0; i < dd->num_send_contexts; i++) अणु
		sc = dd->send_contexts[i].sc;
		/*
		 * Don't disable unallocated, unfrozen, or user send contexts.
		 * User send contexts will be disabled when the process
		 * calls पूर्णांकo the driver to reset its context.
		 */
		अगर (!sc || !(sc->flags & SCF_FROZEN) || sc->type == SC_USER)
			जारी;

		/* only need to disable, the context is alपढ़ोy stopped */
		sc_disable(sc);
	पूर्ण
पूर्ण

/*
 * Unमुक्तze PIO क्रम kernel send contexts.  The precondition क्रम calling this
 * is that all PIO send contexts have been disabled and the SPC मुक्तze has
 * been cleared.  Now perक्रमm the last step and re-enable each kernel context.
 * User (PSM) processing will occur when PSM calls पूर्णांकo the kernel to
 * acknowledge the मुक्तze.
 */
व्योम pio_kernel_unमुक्तze(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा send_context *sc;
	पूर्णांक i;

	क्रम (i = 0; i < dd->num_send_contexts; i++) अणु
		sc = dd->send_contexts[i].sc;
		अगर (!sc || !(sc->flags & SCF_FROZEN) || sc->type == SC_USER)
			जारी;
		अगर (sc->flags & SCF_LINK_DOWN)
			जारी;

		sc_enable(sc);	/* will clear the sc frozen flag */
	पूर्ण
पूर्ण

/**
 * pio_kernel_linkup() - Re-enable send contexts after linkup event
 * @dd: valid devive data
 *
 * When the link goes करोwn, the मुक्तze path is taken.  However, a link करोwn
 * event is dअगरferent from a मुक्तze because अगर the send context is re-enabled
 * whowever is sending data will start sending data again, which will hang
 * any QP that is sending data.
 *
 * The मुक्तze path now looks at the type of event that occurs and takes this
 * path क्रम link करोwn event.
 */
व्योम pio_kernel_linkup(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा send_context *sc;
	पूर्णांक i;

	क्रम (i = 0; i < dd->num_send_contexts; i++) अणु
		sc = dd->send_contexts[i].sc;
		अगर (!sc || !(sc->flags & SCF_LINK_DOWN) || sc->type == SC_USER)
			जारी;

		sc_enable(sc);	/* will clear the sc link करोwn flag */
	पूर्ण
पूर्ण

/*
 * Wait क्रम the SendPioInitCtxt.PioInitInProgress bit to clear.
 * Returns:
 *	-ETIMEDOUT - अगर we रुको too दीर्घ
 *	-EIO	   - अगर there was an error
 */
अटल पूर्णांक pio_init_रुको_progress(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg;
	पूर्णांक max, count = 0;

	/* max is the दीर्घest possible HW init समय / delay */
	max = (dd->icode == ICODE_FPGA_EMULATION) ? 120 : 5;
	जबतक (1) अणु
		reg = पढ़ो_csr(dd, SEND_PIO_INIT_CTXT);
		अगर (!(reg & SEND_PIO_INIT_CTXT_PIO_INIT_IN_PROGRESS_SMASK))
			अवरोध;
		अगर (count >= max)
			वापस -ETIMEDOUT;
		udelay(5);
		count++;
	पूर्ण

	वापस reg & SEND_PIO_INIT_CTXT_PIO_INIT_ERR_SMASK ? -EIO : 0;
पूर्ण

/*
 * Reset all of the send contexts to their घातer-on state.  Used
 * only during manual init - no lock against sc_enable needed.
 */
व्योम pio_reset_all(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	/* make sure the init engine is not busy */
	ret = pio_init_रुको_progress(dd);
	/* ignore any समयout */
	अगर (ret == -EIO) अणु
		/* clear the error */
		ग_लिखो_csr(dd, SEND_PIO_ERR_CLEAR,
			  SEND_PIO_ERR_CLEAR_PIO_INIT_SM_IN_ERR_SMASK);
	पूर्ण

	/* reset init all */
	ग_लिखो_csr(dd, SEND_PIO_INIT_CTXT,
		  SEND_PIO_INIT_CTXT_PIO_ALL_CTXT_INIT_SMASK);
	udelay(2);
	ret = pio_init_रुको_progress(dd);
	अगर (ret < 0) अणु
		dd_dev_err(dd,
			   "PIO send context init %s while initializing all PIO blocks\n",
			   ret == -ETIMEDOUT ? "is stuck" : "had an error");
	पूर्ण
पूर्ण

/* enable the context */
पूर्णांक sc_enable(काष्ठा send_context *sc)
अणु
	u64 sc_ctrl, reg, pio;
	काष्ठा hfi1_devdata *dd;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!sc)
		वापस -EINVAL;
	dd = sc->dd;

	/*
	 * Obtain the allocator lock to guard against any allocation
	 * attempts (which should not happen prior to context being
	 * enabled). On the release/disable side we करोn't need to
	 * worry about locking since the releaser will not करो anything
	 * अगर the context accounting values have not changed.
	 */
	spin_lock_irqsave(&sc->alloc_lock, flags);
	sc_ctrl = पढ़ो_kctxt_csr(dd, sc->hw_context, SC(CTRL));
	अगर ((sc_ctrl & SC(CTRL_CTXT_ENABLE_SMASK)))
		जाओ unlock; /* alपढ़ोy enabled */

	/* IMPORTANT: only clear मुक्त and fill अगर transitioning 0 -> 1 */

	*sc->hw_मुक्त = 0;
	sc->मुक्त = 0;
	sc->alloc_मुक्त = 0;
	sc->fill = 0;
	sc->fill_wrap = 0;
	sc->sr_head = 0;
	sc->sr_tail = 0;
	sc->flags = 0;
	/* the alloc lock insures no fast path allocation */
	reset_buffers_allocated(sc);

	/*
	 * Clear all per-context errors.  Some of these will be set when
	 * we are re-enabling after a context halt.  Now that the context
	 * is disabled, the halt will not clear until after the PIO init
	 * engine runs below.
	 */
	reg = पढ़ो_kctxt_csr(dd, sc->hw_context, SC(ERR_STATUS));
	अगर (reg)
		ग_लिखो_kctxt_csr(dd, sc->hw_context, SC(ERR_CLEAR), reg);

	/*
	 * The HW PIO initialization engine can handle only one init
	 * request at a समय. Serialize access to each device's engine.
	 */
	spin_lock(&dd->sc_init_lock);
	/*
	 * Since access to this code block is serialized and
	 * each access रुकोs क्रम the initialization to complete
	 * beक्रमe releasing the lock, the PIO initialization engine
	 * should not be in use, so we करोn't have to रुको क्रम the
	 * InProgress bit to go करोwn.
	 */
	pio = ((sc->hw_context & SEND_PIO_INIT_CTXT_PIO_CTXT_NUM_MASK) <<
	       SEND_PIO_INIT_CTXT_PIO_CTXT_NUM_SHIFT) |
		SEND_PIO_INIT_CTXT_PIO_SINGLE_CTXT_INIT_SMASK;
	ग_लिखो_csr(dd, SEND_PIO_INIT_CTXT, pio);
	/*
	 * Wait until the engine is करोne.  Give the chip the required समय
	 * so, hopefully, we पढ़ो the रेजिस्टर just once.
	 */
	udelay(2);
	ret = pio_init_रुको_progress(dd);
	spin_unlock(&dd->sc_init_lock);
	अगर (ret) अणु
		dd_dev_err(dd,
			   "sctxt%u(%u): Context not enabled due to init failure %d\n",
			   sc->sw_index, sc->hw_context, ret);
		जाओ unlock;
	पूर्ण

	/*
	 * All is well. Enable the context.
	 */
	sc_ctrl |= SC(CTRL_CTXT_ENABLE_SMASK);
	ग_लिखो_kctxt_csr(dd, sc->hw_context, SC(CTRL), sc_ctrl);
	/*
	 * Read SendCtxtCtrl to क्रमce the ग_लिखो out and prevent a timing
	 * hazard where a PIO ग_लिखो may reach the context beक्रमe the enable.
	 */
	पढ़ो_kctxt_csr(dd, sc->hw_context, SC(CTRL));
	sc->flags |= SCF_ENABLED;

unlock:
	spin_unlock_irqrestore(&sc->alloc_lock, flags);

	वापस ret;
पूर्ण

/* क्रमce a credit वापस on the context */
व्योम sc_वापस_credits(काष्ठा send_context *sc)
अणु
	अगर (!sc)
		वापस;

	/* a 0->1 transition schedules a credit वापस */
	ग_लिखो_kctxt_csr(sc->dd, sc->hw_context, SC(CREDIT_FORCE),
			SC(CREDIT_FORCE_FORCE_RETURN_SMASK));
	/*
	 * Ensure that the ग_लिखो is flushed and the credit वापस is
	 * scheduled. We care more about the 0 -> 1 transition.
	 */
	पढ़ो_kctxt_csr(sc->dd, sc->hw_context, SC(CREDIT_FORCE));
	/* set back to 0 क्रम next समय */
	ग_लिखो_kctxt_csr(sc->dd, sc->hw_context, SC(CREDIT_FORCE), 0);
पूर्ण

/* allow all in-flight packets to drain on the context */
व्योम sc_flush(काष्ठा send_context *sc)
अणु
	अगर (!sc)
		वापस;

	sc_रुको_क्रम_packet_egress(sc, 1);
पूर्ण

/* drop all packets on the context, no रुकोing until they are sent */
व्योम sc_drop(काष्ठा send_context *sc)
अणु
	अगर (!sc)
		वापस;

	dd_dev_info(sc->dd, "%s: context %u(%u) - not implemented\n",
		    __func__, sc->sw_index, sc->hw_context);
पूर्ण

/*
 * Start the software reaction to a context halt or SPC मुक्तze:
 *	- mark the context as halted or frozen
 *	- stop buffer allocations
 *
 * Called from the error पूर्णांकerrupt.  Other work is deferred until
 * out of the पूर्णांकerrupt.
 */
व्योम sc_stop(काष्ठा send_context *sc, पूर्णांक flag)
अणु
	अचिन्हित दीर्घ flags;

	/* stop buffer allocations */
	spin_lock_irqsave(&sc->alloc_lock, flags);
	/* mark the context */
	sc->flags |= flag;
	sc->flags &= ~SCF_ENABLED;
	spin_unlock_irqrestore(&sc->alloc_lock, flags);
	wake_up(&sc->halt_रुको);
पूर्ण

#घोषणा BLOCK_DWORDS (PIO_BLOCK_SIZE / माप(u32))
#घोषणा dwords_to_blocks(x) DIV_ROUND_UP(x, BLOCK_DWORDS)

/*
 * The send context buffer "allocator".
 *
 * @sc: the PIO send context we are allocating from
 * @len: length of whole packet - including PBC - in dwords
 * @cb: optional callback to call when the buffer is finished sending
 * @arg: argument क्रम cb
 *
 * Return a poपूर्णांकer to a PIO buffer, शून्य अगर not enough room, -ECOMM
 * when link is करोwn.
 */
काष्ठा pio_buf *sc_buffer_alloc(काष्ठा send_context *sc, u32 dw_len,
				pio_release_cb cb, व्योम *arg)
अणु
	काष्ठा pio_buf *pbuf = शून्य;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ avail;
	अचिन्हित दीर्घ blocks = dwords_to_blocks(dw_len);
	u32 fill_wrap;
	पूर्णांक trycount = 0;
	u32 head, next;

	spin_lock_irqsave(&sc->alloc_lock, flags);
	अगर (!(sc->flags & SCF_ENABLED)) अणु
		spin_unlock_irqrestore(&sc->alloc_lock, flags);
		वापस ERR_PTR(-ECOMM);
	पूर्ण

retry:
	avail = (अचिन्हित दीर्घ)sc->credits - (sc->fill - sc->alloc_मुक्त);
	अगर (blocks > avail) अणु
		/* not enough room */
		अगर (unlikely(trycount))	अणु /* alपढ़ोy tried to get more room */
			spin_unlock_irqrestore(&sc->alloc_lock, flags);
			जाओ करोne;
		पूर्ण
		/* copy from receiver cache line and recalculate */
		sc->alloc_मुक्त = READ_ONCE(sc->मुक्त);
		avail =
			(अचिन्हित दीर्घ)sc->credits -
			(sc->fill - sc->alloc_मुक्त);
		अगर (blocks > avail) अणु
			/* still no room, actively update */
			sc_release_update(sc);
			sc->alloc_मुक्त = READ_ONCE(sc->मुक्त);
			trycount++;
			जाओ retry;
		पूर्ण
	पूर्ण

	/* there is enough room */

	preempt_disable();
	this_cpu_inc(*sc->buffers_allocated);

	/* पढ़ो this once */
	head = sc->sr_head;

	/* "allocate" the buffer */
	sc->fill += blocks;
	fill_wrap = sc->fill_wrap;
	sc->fill_wrap += blocks;
	अगर (sc->fill_wrap >= sc->credits)
		sc->fill_wrap = sc->fill_wrap - sc->credits;

	/*
	 * Fill the parts that the releaser looks at beक्रमe moving the head.
	 * The only necessary piece is the sent_at field.  The credits
	 * we have just allocated cannot have been वापसed yet, so the
	 * cb and arg will not be looked at क्रम a "while".  Put them
	 * on this side of the memory barrier anyway.
	 */
	pbuf = &sc->sr[head].pbuf;
	pbuf->sent_at = sc->fill;
	pbuf->cb = cb;
	pbuf->arg = arg;
	pbuf->sc = sc;	/* could be filled in at sc->sr init समय */
	/* make sure this is in memory beक्रमe updating the head */

	/* calculate next head index, करो not store */
	next = head + 1;
	अगर (next >= sc->sr_size)
		next = 0;
	/*
	 * update the head - must be last! - the releaser can look at fields
	 * in pbuf once we move the head
	 */
	smp_wmb();
	sc->sr_head = next;
	spin_unlock_irqrestore(&sc->alloc_lock, flags);

	/* finish filling in the buffer outside the lock */
	pbuf->start = sc->base_addr + fill_wrap * PIO_BLOCK_SIZE;
	pbuf->end = sc->base_addr + sc->size;
	pbuf->qw_written = 0;
	pbuf->carry_bytes = 0;
	pbuf->carry.val64 = 0;
करोne:
	वापस pbuf;
पूर्ण

/*
 * There are at least two entities that can turn on credit वापस
 * पूर्णांकerrupts and they can overlap.  Aव्योम problems by implementing
 * a count scheme that is enक्रमced by a lock.  The lock is needed because
 * the count and CSR ग_लिखो must be paired.
 */

/*
 * Start credit वापस पूर्णांकerrupts.  This is managed by a count.  If alपढ़ोy
 * on, just increment the count.
 */
व्योम sc_add_credit_वापस_पूर्णांकr(काष्ठा send_context *sc)
अणु
	अचिन्हित दीर्घ flags;

	/* lock must surround both the count change and the CSR update */
	spin_lock_irqsave(&sc->credit_ctrl_lock, flags);
	अगर (sc->credit_पूर्णांकr_count == 0) अणु
		sc->credit_ctrl |= SC(CREDIT_CTRL_CREDIT_INTR_SMASK);
		ग_लिखो_kctxt_csr(sc->dd, sc->hw_context,
				SC(CREDIT_CTRL), sc->credit_ctrl);
	पूर्ण
	sc->credit_पूर्णांकr_count++;
	spin_unlock_irqrestore(&sc->credit_ctrl_lock, flags);
पूर्ण

/*
 * Stop credit वापस पूर्णांकerrupts.  This is managed by a count.  Decrement the
 * count, अगर the last user, then turn the credit पूर्णांकerrupts off.
 */
व्योम sc_del_credit_वापस_पूर्णांकr(काष्ठा send_context *sc)
अणु
	अचिन्हित दीर्घ flags;

	WARN_ON(sc->credit_पूर्णांकr_count == 0);

	/* lock must surround both the count change and the CSR update */
	spin_lock_irqsave(&sc->credit_ctrl_lock, flags);
	sc->credit_पूर्णांकr_count--;
	अगर (sc->credit_पूर्णांकr_count == 0) अणु
		sc->credit_ctrl &= ~SC(CREDIT_CTRL_CREDIT_INTR_SMASK);
		ग_लिखो_kctxt_csr(sc->dd, sc->hw_context,
				SC(CREDIT_CTRL), sc->credit_ctrl);
	पूर्ण
	spin_unlock_irqrestore(&sc->credit_ctrl_lock, flags);
पूर्ण

/*
 * The caller must be careful when calling this.  All needपूर्णांक calls
 * must be paired with !needपूर्णांक.
 */
व्योम hfi1_sc_wantpiobuf_पूर्णांकr(काष्ठा send_context *sc, u32 needपूर्णांक)
अणु
	अगर (needपूर्णांक)
		sc_add_credit_वापस_पूर्णांकr(sc);
	अन्यथा
		sc_del_credit_वापस_पूर्णांकr(sc);
	trace_hfi1_wantpioपूर्णांकr(sc, needपूर्णांक, sc->credit_ctrl);
	अगर (needपूर्णांक)
		sc_वापस_credits(sc);
पूर्ण

/**
 * sc_piobufavail - callback when a PIO buffer is available
 * @sc: the send context
 *
 * This is called from the पूर्णांकerrupt handler when a PIO buffer is
 * available after hfi1_verbs_send() वापसed an error that no buffers were
 * available. Disable the पूर्णांकerrupt अगर there are no more QPs रुकोing.
 */
अटल व्योम sc_piobufavail(काष्ठा send_context *sc)
अणु
	काष्ठा hfi1_devdata *dd = sc->dd;
	काष्ठा list_head *list;
	काष्ठा rvt_qp *qps[PIO_WAIT_BATCH_SIZE];
	काष्ठा rvt_qp *qp;
	काष्ठा hfi1_qp_priv *priv;
	अचिन्हित दीर्घ flags;
	uपूर्णांक i, n = 0, top_idx = 0;

	अगर (dd->send_contexts[sc->sw_index].type != SC_KERNEL &&
	    dd->send_contexts[sc->sw_index].type != SC_VL15)
		वापस;
	list = &sc->pioरुको;
	/*
	 * Note: checking that the pioरुको list is empty and clearing
	 * the buffer available पूर्णांकerrupt needs to be atomic or we
	 * could end up with QPs on the रुको list with the पूर्णांकerrupt
	 * disabled.
	 */
	ग_लिखो_seqlock_irqsave(&sc->रुकोlock, flags);
	जबतक (!list_empty(list)) अणु
		काष्ठा ioरुको *रुको;

		अगर (n == ARRAY_SIZE(qps))
			अवरोध;
		रुको = list_first_entry(list, काष्ठा ioरुको, list);
		ioरुको_get_priority(रुको);
		qp = ioरुको_to_qp(रुको);
		priv = qp->priv;
		list_del_init(&priv->s_ioरुको.list);
		priv->s_ioरुको.lock = शून्य;
		अगर (n) अणु
			priv = qps[top_idx]->priv;
			top_idx = ioरुको_priority_update_top(रुको,
							     &priv->s_ioरुको,
							     n, top_idx);
		पूर्ण

		/* refcount held until actual wake up */
		qps[n++] = qp;
	पूर्ण
	/*
	 * If there had been रुकोers and there are more
	 * insure that we reकरो the क्रमce to aव्योम a potential hang.
	 */
	अगर (n) अणु
		hfi1_sc_wantpiobuf_पूर्णांकr(sc, 0);
		अगर (!list_empty(list))
			hfi1_sc_wantpiobuf_पूर्णांकr(sc, 1);
	पूर्ण
	ग_लिखो_sequnlock_irqrestore(&sc->रुकोlock, flags);

	/* Wake up the top-priority one first */
	अगर (n)
		hfi1_qp_wakeup(qps[top_idx],
			       RVT_S_WAIT_PIO | HFI1_S_WAIT_PIO_DRAIN);
	क्रम (i = 0; i < n; i++)
		अगर (i != top_idx)
			hfi1_qp_wakeup(qps[i],
				       RVT_S_WAIT_PIO | HFI1_S_WAIT_PIO_DRAIN);
पूर्ण

/* translate a send credit update to a bit code of reasons */
अटल अंतरभूत पूर्णांक fill_code(u64 hw_मुक्त)
अणु
	पूर्णांक code = 0;

	अगर (hw_मुक्त & CR_STATUS_SMASK)
		code |= PRC_STATUS_ERR;
	अगर (hw_मुक्त & CR_CREDIT_RETURN_DUE_TO_PBC_SMASK)
		code |= PRC_PBC;
	अगर (hw_मुक्त & CR_CREDIT_RETURN_DUE_TO_THRESHOLD_SMASK)
		code |= PRC_THRESHOLD;
	अगर (hw_मुक्त & CR_CREDIT_RETURN_DUE_TO_ERR_SMASK)
		code |= PRC_FILL_ERR;
	अगर (hw_मुक्त & CR_CREDIT_RETURN_DUE_TO_FORCE_SMASK)
		code |= PRC_SC_DISABLE;
	वापस code;
पूर्ण

/* use the jअगरfies compare to get the wrap right */
#घोषणा sent_beक्रमe(a, b) समय_beक्रमe(a, b)	/* a < b */

/*
 * The send context buffer "releaser".
 */
व्योम sc_release_update(काष्ठा send_context *sc)
अणु
	काष्ठा pio_buf *pbuf;
	u64 hw_मुक्त;
	u32 head, tail;
	अचिन्हित दीर्घ old_मुक्त;
	अचिन्हित दीर्घ मुक्त;
	अचिन्हित दीर्घ extra;
	अचिन्हित दीर्घ flags;
	पूर्णांक code;

	अगर (!sc)
		वापस;

	spin_lock_irqsave(&sc->release_lock, flags);
	/* update मुक्त */
	hw_मुक्त = le64_to_cpu(*sc->hw_मुक्त);		/* अस्थिर पढ़ो */
	old_मुक्त = sc->मुक्त;
	extra = (((hw_मुक्त & CR_COUNTER_SMASK) >> CR_COUNTER_SHIFT)
			- (old_मुक्त & CR_COUNTER_MASK))
				& CR_COUNTER_MASK;
	मुक्त = old_मुक्त + extra;
	trace_hfi1_pioमुक्त(sc, extra);

	/* call sent buffer callbacks */
	code = -1;				/* code not yet set */
	head = READ_ONCE(sc->sr_head);	/* snapshot the head */
	tail = sc->sr_tail;
	जबतक (head != tail) अणु
		pbuf = &sc->sr[tail].pbuf;

		अगर (sent_beक्रमe(मुक्त, pbuf->sent_at)) अणु
			/* not sent yet */
			अवरोध;
		पूर्ण
		अगर (pbuf->cb) अणु
			अगर (code < 0) /* fill in code on first user */
				code = fill_code(hw_मुक्त);
			(*pbuf->cb)(pbuf->arg, code);
		पूर्ण

		tail++;
		अगर (tail >= sc->sr_size)
			tail = 0;
	पूर्ण
	sc->sr_tail = tail;
	/* make sure tail is updated beक्रमe मुक्त */
	smp_wmb();
	sc->मुक्त = मुक्त;
	spin_unlock_irqrestore(&sc->release_lock, flags);
	sc_piobufavail(sc);
पूर्ण

/*
 * Send context group releaser.  Argument is the send context that caused
 * the पूर्णांकerrupt.  Called from the send context पूर्णांकerrupt handler.
 *
 * Call release on all contexts in the group.
 *
 * This routine takes the sc_lock without an irqsave because it is only
 * called from an पूर्णांकerrupt handler.  Adjust अगर that changes.
 */
व्योम sc_group_release_update(काष्ठा hfi1_devdata *dd, u32 hw_context)
अणु
	काष्ठा send_context *sc;
	u32 sw_index;
	u32 gc, gc_end;

	spin_lock(&dd->sc_lock);
	sw_index = dd->hw_to_sw[hw_context];
	अगर (unlikely(sw_index >= dd->num_send_contexts)) अणु
		dd_dev_err(dd, "%s: invalid hw (%u) to sw (%u) mapping\n",
			   __func__, hw_context, sw_index);
		जाओ करोne;
	पूर्ण
	sc = dd->send_contexts[sw_index].sc;
	अगर (unlikely(!sc))
		जाओ करोne;

	gc = group_context(hw_context, sc->group);
	gc_end = gc + group_size(sc->group);
	क्रम (; gc < gc_end; gc++) अणु
		sw_index = dd->hw_to_sw[gc];
		अगर (unlikely(sw_index >= dd->num_send_contexts)) अणु
			dd_dev_err(dd,
				   "%s: invalid hw (%u) to sw (%u) mapping\n",
				   __func__, hw_context, sw_index);
			जारी;
		पूर्ण
		sc_release_update(dd->send_contexts[sw_index].sc);
	पूर्ण
करोne:
	spin_unlock(&dd->sc_lock);
पूर्ण

/*
 * pio_select_send_context_vl() - select send context
 * @dd: devdata
 * @selector: a spपढ़ोing factor
 * @vl: this vl
 *
 * This function वापसs a send context based on the selector and a vl.
 * The mapping fields are रक्षित by RCU
 */
काष्ठा send_context *pio_select_send_context_vl(काष्ठा hfi1_devdata *dd,
						u32 selector, u8 vl)
अणु
	काष्ठा pio_vl_map *m;
	काष्ठा pio_map_elem *e;
	काष्ठा send_context *rval;

	/*
	 * NOTE This should only happen अगर SC->VL changed after the initial
	 * checks on the QP/AH
	 * Default will वापस VL0's send context below
	 */
	अगर (unlikely(vl >= num_vls)) अणु
		rval = शून्य;
		जाओ करोne;
	पूर्ण

	rcu_पढ़ो_lock();
	m = rcu_dereference(dd->pio_map);
	अगर (unlikely(!m)) अणु
		rcu_पढ़ो_unlock();
		वापस dd->vld[0].sc;
	पूर्ण
	e = m->map[vl & m->mask];
	rval = e->ksc[selector & e->mask];
	rcu_पढ़ो_unlock();

करोne:
	rval = !rval ? dd->vld[0].sc : rval;
	वापस rval;
पूर्ण

/*
 * pio_select_send_context_sc() - select send context
 * @dd: devdata
 * @selector: a spपढ़ोing factor
 * @sc5: the 5 bit sc
 *
 * This function वापसs an send context based on the selector and an sc
 */
काष्ठा send_context *pio_select_send_context_sc(काष्ठा hfi1_devdata *dd,
						u32 selector, u8 sc5)
अणु
	u8 vl = sc_to_vlt(dd, sc5);

	वापस pio_select_send_context_vl(dd, selector, vl);
पूर्ण

/*
 * Free the indicated map काष्ठा
 */
अटल व्योम pio_map_मुक्त(काष्ठा pio_vl_map *m)
अणु
	पूर्णांक i;

	क्रम (i = 0; m && i < m->actual_vls; i++)
		kमुक्त(m->map[i]);
	kमुक्त(m);
पूर्ण

/*
 * Handle RCU callback
 */
अटल व्योम pio_map_rcu_callback(काष्ठा rcu_head *list)
अणु
	काष्ठा pio_vl_map *m = container_of(list, काष्ठा pio_vl_map, list);

	pio_map_मुक्त(m);
पूर्ण

/*
 * Set credit वापस threshold क्रम the kernel send context
 */
अटल व्योम set_threshold(काष्ठा hfi1_devdata *dd, पूर्णांक scontext, पूर्णांक i)
अणु
	u32 thres;

	thres = min(sc_percent_to_threshold(dd->kernel_send_context[scontext],
					    50),
		    sc_mtu_to_threshold(dd->kernel_send_context[scontext],
					dd->vld[i].mtu,
					dd->rcd[0]->rcvhdrqentsize));
	sc_set_cr_threshold(dd->kernel_send_context[scontext], thres);
पूर्ण

/*
 * pio_map_init - called when #vls change
 * @dd: hfi1_devdata
 * @port: port number
 * @num_vls: number of vls
 * @vl_scontexts: per vl send context mapping (optional)
 *
 * This routine changes the mapping based on the number of vls.
 *
 * vl_scontexts is used to specअगरy a non-unअगरorm vl/send context
 * loading. शून्य implies स्वतः computing the loading and giving each
 * VL an unअगरorm distribution of send contexts per VL.
 *
 * The स्वतः algorithm computers the sc_per_vl and the number of extra
 * send contexts. Any extra send contexts are added from the last VL
 * on करोwn
 *
 * rcu locking is used here to control access to the mapping fields.
 *
 * If either the num_vls or num_send_contexts are non-घातer of 2, the
 * array sizes in the काष्ठा pio_vl_map and the काष्ठा pio_map_elem are
 * rounded up to the next highest घातer of 2 and the first entry is
 * reused in a round robin fashion.
 *
 * If an error occurs the map change is not करोne and the mapping is not
 * chaged.
 *
 */
पूर्णांक pio_map_init(काष्ठा hfi1_devdata *dd, u8 port, u8 num_vls, u8 *vl_scontexts)
अणु
	पूर्णांक i, j;
	पूर्णांक extra, sc_per_vl;
	पूर्णांक scontext = 1;
	पूर्णांक num_kernel_send_contexts = 0;
	u8 lvl_scontexts[OPA_MAX_VLS];
	काष्ठा pio_vl_map *oldmap, *newmap;

	अगर (!vl_scontexts) अणु
		क्रम (i = 0; i < dd->num_send_contexts; i++)
			अगर (dd->send_contexts[i].type == SC_KERNEL)
				num_kernel_send_contexts++;
		/* truncate भागide */
		sc_per_vl = num_kernel_send_contexts / num_vls;
		/* extras */
		extra = num_kernel_send_contexts % num_vls;
		vl_scontexts = lvl_scontexts;
		/* add extras from last vl करोwn */
		क्रम (i = num_vls - 1; i >= 0; i--, extra--)
			vl_scontexts[i] = sc_per_vl + (extra > 0 ? 1 : 0);
	पूर्ण
	/* build new map */
	newmap = kzalloc(माप(*newmap) +
			 roundup_घात_of_two(num_vls) *
			 माप(काष्ठा pio_map_elem *),
			 GFP_KERNEL);
	अगर (!newmap)
		जाओ bail;
	newmap->actual_vls = num_vls;
	newmap->vls = roundup_घात_of_two(num_vls);
	newmap->mask = (1 << ilog2(newmap->vls)) - 1;
	क्रम (i = 0; i < newmap->vls; i++) अणु
		/* save क्रम wrap around */
		पूर्णांक first_scontext = scontext;

		अगर (i < newmap->actual_vls) अणु
			पूर्णांक sz = roundup_घात_of_two(vl_scontexts[i]);

			/* only allocate once */
			newmap->map[i] = kzalloc(माप(*newmap->map[i]) +
						 sz * माप(काष्ठा
							     send_context *),
						 GFP_KERNEL);
			अगर (!newmap->map[i])
				जाओ bail;
			newmap->map[i]->mask = (1 << ilog2(sz)) - 1;
			/*
			 * assign send contexts and
			 * adjust credit वापस threshold
			 */
			क्रम (j = 0; j < sz; j++) अणु
				अगर (dd->kernel_send_context[scontext]) अणु
					newmap->map[i]->ksc[j] =
					dd->kernel_send_context[scontext];
					set_threshold(dd, scontext, i);
				पूर्ण
				अगर (++scontext >= first_scontext +
						  vl_scontexts[i])
					/* wrap back to first send context */
					scontext = first_scontext;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* just re-use entry without allocating */
			newmap->map[i] = newmap->map[i % num_vls];
		पूर्ण
		scontext = first_scontext + vl_scontexts[i];
	पूर्ण
	/* newmap in hand, save old map */
	spin_lock_irq(&dd->pio_map_lock);
	oldmap = rcu_dereference_रक्षित(dd->pio_map,
					   lockdep_is_held(&dd->pio_map_lock));

	/* publish newmap */
	rcu_assign_poपूर्णांकer(dd->pio_map, newmap);

	spin_unlock_irq(&dd->pio_map_lock);
	/* success, मुक्त any old map after grace period */
	अगर (oldmap)
		call_rcu(&oldmap->list, pio_map_rcu_callback);
	वापस 0;
bail:
	/* मुक्त any partial allocation */
	pio_map_मुक्त(newmap);
	वापस -ENOMEM;
पूर्ण

व्योम मुक्त_pio_map(काष्ठा hfi1_devdata *dd)
अणु
	/* Free PIO map अगर allocated */
	अगर (rcu_access_poपूर्णांकer(dd->pio_map)) अणु
		spin_lock_irq(&dd->pio_map_lock);
		pio_map_मुक्त(rcu_access_poपूर्णांकer(dd->pio_map));
		RCU_INIT_POINTER(dd->pio_map, शून्य);
		spin_unlock_irq(&dd->pio_map_lock);
		synchronize_rcu();
	पूर्ण
	kमुक्त(dd->kernel_send_context);
	dd->kernel_send_context = शून्य;
पूर्ण

पूर्णांक init_pervl_scs(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;
	u64 mask, all_vl_mask = (u64)0x80ff; /* VLs 0-7, 15 */
	u64 data_vls_mask = (u64)0x00ff; /* VLs 0-7 */
	u32 ctxt;
	काष्ठा hfi1_pportdata *ppd = dd->pport;

	dd->vld[15].sc = sc_alloc(dd, SC_VL15,
				  dd->rcd[0]->rcvhdrqentsize, dd->node);
	अगर (!dd->vld[15].sc)
		वापस -ENOMEM;

	hfi1_init_ctxt(dd->vld[15].sc);
	dd->vld[15].mtu = क्रमागत_to_mtu(OPA_MTU_2048);

	dd->kernel_send_context = kसुस्मृति_node(dd->num_send_contexts,
					       माप(काष्ठा send_context *),
					       GFP_KERNEL, dd->node);
	अगर (!dd->kernel_send_context)
		जाओ मुक्तsc15;

	dd->kernel_send_context[0] = dd->vld[15].sc;

	क्रम (i = 0; i < num_vls; i++) अणु
		/*
		 * Since this function करोes not deal with a specअगरic
		 * receive context but we need the RcvHdrQ entry size,
		 * use the size from rcd[0]. It is guaranteed to be
		 * valid at this poपूर्णांक and will reमुख्य the same क्रम all
		 * receive contexts.
		 */
		dd->vld[i].sc = sc_alloc(dd, SC_KERNEL,
					 dd->rcd[0]->rcvhdrqentsize, dd->node);
		अगर (!dd->vld[i].sc)
			जाओ nomem;
		dd->kernel_send_context[i + 1] = dd->vld[i].sc;
		hfi1_init_ctxt(dd->vld[i].sc);
		/* non VL15 start with the max MTU */
		dd->vld[i].mtu = hfi1_max_mtu;
	पूर्ण
	क्रम (i = num_vls; i < INIT_SC_PER_VL * num_vls; i++) अणु
		dd->kernel_send_context[i + 1] =
		sc_alloc(dd, SC_KERNEL, dd->rcd[0]->rcvhdrqentsize, dd->node);
		अगर (!dd->kernel_send_context[i + 1])
			जाओ nomem;
		hfi1_init_ctxt(dd->kernel_send_context[i + 1]);
	पूर्ण

	sc_enable(dd->vld[15].sc);
	ctxt = dd->vld[15].sc->hw_context;
	mask = all_vl_mask & ~(1LL << 15);
	ग_लिखो_kctxt_csr(dd, ctxt, SC(CHECK_VL), mask);
	dd_dev_info(dd,
		    "Using send context %u(%u) for VL15\n",
		    dd->vld[15].sc->sw_index, ctxt);

	क्रम (i = 0; i < num_vls; i++) अणु
		sc_enable(dd->vld[i].sc);
		ctxt = dd->vld[i].sc->hw_context;
		mask = all_vl_mask & ~(data_vls_mask);
		ग_लिखो_kctxt_csr(dd, ctxt, SC(CHECK_VL), mask);
	पूर्ण
	क्रम (i = num_vls; i < INIT_SC_PER_VL * num_vls; i++) अणु
		sc_enable(dd->kernel_send_context[i + 1]);
		ctxt = dd->kernel_send_context[i + 1]->hw_context;
		mask = all_vl_mask & ~(data_vls_mask);
		ग_लिखो_kctxt_csr(dd, ctxt, SC(CHECK_VL), mask);
	पूर्ण

	अगर (pio_map_init(dd, ppd->port - 1, num_vls, शून्य))
		जाओ nomem;
	वापस 0;

nomem:
	क्रम (i = 0; i < num_vls; i++) अणु
		sc_मुक्त(dd->vld[i].sc);
		dd->vld[i].sc = शून्य;
	पूर्ण

	क्रम (i = num_vls; i < INIT_SC_PER_VL * num_vls; i++)
		sc_मुक्त(dd->kernel_send_context[i + 1]);

	kमुक्त(dd->kernel_send_context);
	dd->kernel_send_context = शून्य;

मुक्तsc15:
	sc_मुक्त(dd->vld[15].sc);
	वापस -ENOMEM;
पूर्ण

पूर्णांक init_credit_वापस(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	dd->cr_base = kसुस्मृति(
		node_affinity.num_possible_nodes,
		माप(काष्ठा credit_वापस_base),
		GFP_KERNEL);
	अगर (!dd->cr_base) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण
	क्रम_each_node_with_cpus(i) अणु
		पूर्णांक bytes = TXE_NUM_CONTEXTS * माप(काष्ठा credit_वापस);

		set_dev_node(&dd->pcidev->dev, i);
		dd->cr_base[i].va = dma_alloc_coherent(&dd->pcidev->dev,
						       bytes,
						       &dd->cr_base[i].dma,
						       GFP_KERNEL);
		अगर (!dd->cr_base[i].va) अणु
			set_dev_node(&dd->pcidev->dev, dd->node);
			dd_dev_err(dd,
				   "Unable to allocate credit return DMA range for NUMA %d\n",
				   i);
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
	पूर्ण
	set_dev_node(&dd->pcidev->dev, dd->node);

	ret = 0;
करोne:
	वापस ret;
पूर्ण

व्योम मुक्त_credit_वापस(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	अगर (!dd->cr_base)
		वापस;
	क्रम (i = 0; i < node_affinity.num_possible_nodes; i++) अणु
		अगर (dd->cr_base[i].va) अणु
			dma_मुक्त_coherent(&dd->pcidev->dev,
					  TXE_NUM_CONTEXTS *
					  माप(काष्ठा credit_वापस),
					  dd->cr_base[i].va,
					  dd->cr_base[i].dma);
		पूर्ण
	पूर्ण
	kमुक्त(dd->cr_base);
	dd->cr_base = शून्य;
पूर्ण

व्योम seqfile_dump_sci(काष्ठा seq_file *s, u32 i,
		      काष्ठा send_context_info *sci)
अणु
	काष्ठा send_context *sc = sci->sc;
	u64 reg;

	seq_म_लिखो(s, "SCI %u: type %u base %u credits %u\n",
		   i, sci->type, sci->base, sci->credits);
	seq_म_लिखो(s, "  flags 0x%x sw_inx %u hw_ctxt %u grp %u\n",
		   sc->flags,  sc->sw_index, sc->hw_context, sc->group);
	seq_म_लिखो(s, "  sr_size %u credits %u sr_head %u sr_tail %u\n",
		   sc->sr_size, sc->credits, sc->sr_head, sc->sr_tail);
	seq_म_लिखो(s, "  fill %lu free %lu fill_wrap %u alloc_free %lu\n",
		   sc->fill, sc->मुक्त, sc->fill_wrap, sc->alloc_मुक्त);
	seq_म_लिखो(s, "  credit_intr_count %u credit_ctrl 0x%llx\n",
		   sc->credit_पूर्णांकr_count, sc->credit_ctrl);
	reg = पढ़ो_kctxt_csr(sc->dd, sc->hw_context, SC(CREDIT_STATUS));
	seq_म_लिखो(s, "  *hw_free %llu CurrentFree %llu LastReturned %llu\n",
		   (le64_to_cpu(*sc->hw_मुक्त) & CR_COUNTER_SMASK) >>
		    CR_COUNTER_SHIFT,
		   (reg >> SC(CREDIT_STATUS_CURRENT_FREE_COUNTER_SHIFT)) &
		    SC(CREDIT_STATUS_CURRENT_FREE_COUNTER_MASK),
		   reg & SC(CREDIT_STATUS_LAST_RETURNED_COUNTER_SMASK));
पूर्ण
