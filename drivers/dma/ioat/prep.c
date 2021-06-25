<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel I/OAT DMA Linux driver
 * Copyright(c) 2004 - 2015 Intel Corporation.
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/gfp.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/prefetch.h>
#समावेश "../dmaengine.h"
#समावेश "registers.h"
#समावेश "hw.h"
#समावेश "dma.h"

#घोषणा MAX_SCF	256

/* provide a lookup table क्रम setting the source address in the base or
 * extended descriptor of an xor or pq descriptor
 */
अटल स्थिर u8 xor_idx_to_desc = 0xe0;
अटल स्थिर u8 xor_idx_to_field[] = अणु 1, 4, 5, 6, 7, 0, 1, 2 पूर्ण;
अटल स्थिर u8 pq_idx_to_desc = 0xf8;
अटल स्थिर u8 pq16_idx_to_desc[] = अणु 0, 0, 1, 1, 1, 1, 1, 1, 1,
				       2, 2, 2, 2, 2, 2, 2 पूर्ण;
अटल स्थिर u8 pq_idx_to_field[] = अणु 1, 4, 5, 0, 1, 2, 4, 5 पूर्ण;
अटल स्थिर u8 pq16_idx_to_field[] = अणु 1, 4, 1, 2, 3, 4, 5, 6, 7,
					0, 1, 2, 3, 4, 5, 6 पूर्ण;

अटल व्योम xor_set_src(काष्ठा ioat_raw_descriptor *descs[2],
			dma_addr_t addr, u32 offset, पूर्णांक idx)
अणु
	काष्ठा ioat_raw_descriptor *raw = descs[xor_idx_to_desc >> idx & 1];

	raw->field[xor_idx_to_field[idx]] = addr + offset;
पूर्ण

अटल dma_addr_t pq_get_src(काष्ठा ioat_raw_descriptor *descs[2], पूर्णांक idx)
अणु
	काष्ठा ioat_raw_descriptor *raw = descs[pq_idx_to_desc >> idx & 1];

	वापस raw->field[pq_idx_to_field[idx]];
पूर्ण

अटल dma_addr_t pq16_get_src(काष्ठा ioat_raw_descriptor *desc[3], पूर्णांक idx)
अणु
	काष्ठा ioat_raw_descriptor *raw = desc[pq16_idx_to_desc[idx]];

	वापस raw->field[pq16_idx_to_field[idx]];
पूर्ण

अटल व्योम pq_set_src(काष्ठा ioat_raw_descriptor *descs[2],
		       dma_addr_t addr, u32 offset, u8 coef, पूर्णांक idx)
अणु
	काष्ठा ioat_pq_descriptor *pq = (काष्ठा ioat_pq_descriptor *) descs[0];
	काष्ठा ioat_raw_descriptor *raw = descs[pq_idx_to_desc >> idx & 1];

	raw->field[pq_idx_to_field[idx]] = addr + offset;
	pq->coef[idx] = coef;
पूर्ण

अटल व्योम pq16_set_src(काष्ठा ioat_raw_descriptor *desc[3],
			dma_addr_t addr, u32 offset, u8 coef, अचिन्हित idx)
अणु
	काष्ठा ioat_pq_descriptor *pq = (काष्ठा ioat_pq_descriptor *)desc[0];
	काष्ठा ioat_pq16a_descriptor *pq16 =
		(काष्ठा ioat_pq16a_descriptor *)desc[1];
	काष्ठा ioat_raw_descriptor *raw = desc[pq16_idx_to_desc[idx]];

	raw->field[pq16_idx_to_field[idx]] = addr + offset;

	अगर (idx < 8)
		pq->coef[idx] = coef;
	अन्यथा
		pq16->coef[idx - 8] = coef;
पूर्ण

अटल काष्ठा ioat_sed_ent *
ioat3_alloc_sed(काष्ठा ioatdma_device *ioat_dma, अचिन्हित पूर्णांक hw_pool)
अणु
	काष्ठा ioat_sed_ent *sed;
	gfp_t flags = __GFP_ZERO | GFP_ATOMIC;

	sed = kmem_cache_alloc(ioat_sed_cache, flags);
	अगर (!sed)
		वापस शून्य;

	sed->hw_pool = hw_pool;
	sed->hw = dma_pool_alloc(ioat_dma->sed_hw_pool[hw_pool],
				 flags, &sed->dma);
	अगर (!sed->hw) अणु
		kmem_cache_मुक्त(ioat_sed_cache, sed);
		वापस शून्य;
	पूर्ण

	वापस sed;
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_dma_prep_स_नकल_lock(काष्ठा dma_chan *c, dma_addr_t dma_dest,
			   dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioat_dma_descriptor *hw;
	काष्ठा ioat_ring_ent *desc;
	dma_addr_t dst = dma_dest;
	dma_addr_t src = dma_src;
	माप_प्रकार total_len = len;
	पूर्णांक num_descs, idx, i;

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	num_descs = ioat_xferlen_to_descs(ioat_chan, len);
	अगर (likely(num_descs) &&
	    ioat_check_space_lock(ioat_chan, num_descs) == 0)
		idx = ioat_chan->head;
	अन्यथा
		वापस शून्य;
	i = 0;
	करो अणु
		माप_प्रकार copy = min_t(माप_प्रकार, len, 1 << ioat_chan->xfercap_log);

		desc = ioat_get_ring_ent(ioat_chan, idx + i);
		hw = desc->hw;

		hw->size = copy;
		hw->ctl = 0;
		hw->src_addr = src;
		hw->dst_addr = dst;

		len -= copy;
		dst += copy;
		src += copy;
		dump_desc_dbg(ioat_chan, desc);
	पूर्ण जबतक (++i < num_descs);

	desc->txd.flags = flags;
	desc->len = total_len;
	hw->ctl_f.पूर्णांक_en = !!(flags & DMA_PREP_INTERRUPT);
	hw->ctl_f.fence = !!(flags & DMA_PREP_FENCE);
	hw->ctl_f.compl_ग_लिखो = 1;
	dump_desc_dbg(ioat_chan, desc);
	/* we leave the channel locked to ensure in order submission */

	वापस &desc->txd;
पूर्ण


अटल काष्ठा dma_async_tx_descriptor *
__ioat_prep_xor_lock(काष्ठा dma_chan *c, क्रमागत sum_check_flags *result,
		      dma_addr_t dest, dma_addr_t *src, अचिन्हित पूर्णांक src_cnt,
		      माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioat_ring_ent *compl_desc;
	काष्ठा ioat_ring_ent *desc;
	काष्ठा ioat_ring_ent *ext;
	माप_प्रकार total_len = len;
	काष्ठा ioat_xor_descriptor *xor;
	काष्ठा ioat_xor_ext_descriptor *xor_ex = शून्य;
	काष्ठा ioat_dma_descriptor *hw;
	पूर्णांक num_descs, with_ext, idx, i;
	u32 offset = 0;
	u8 op = result ? IOAT_OP_XOR_VAL : IOAT_OP_XOR;

	BUG_ON(src_cnt < 2);

	num_descs = ioat_xferlen_to_descs(ioat_chan, len);
	/* we need 2x the number of descriptors to cover greater than 5
	 * sources
	 */
	अगर (src_cnt > 5) अणु
		with_ext = 1;
		num_descs *= 2;
	पूर्ण अन्यथा
		with_ext = 0;

	/* completion ग_लिखोs from the raid engine may pass completion
	 * ग_लिखोs from the legacy engine, so we need one extra null
	 * (legacy) descriptor to ensure all completion ग_लिखोs arrive in
	 * order.
	 */
	अगर (likely(num_descs) &&
	    ioat_check_space_lock(ioat_chan, num_descs+1) == 0)
		idx = ioat_chan->head;
	अन्यथा
		वापस शून्य;
	i = 0;
	करो अणु
		काष्ठा ioat_raw_descriptor *descs[2];
		माप_प्रकार xfer_size = min_t(माप_प्रकार,
					 len, 1 << ioat_chan->xfercap_log);
		पूर्णांक s;

		desc = ioat_get_ring_ent(ioat_chan, idx + i);
		xor = desc->xor;

		/* save a branch by unconditionally retrieving the
		 * extended descriptor xor_set_src() knows to not ग_लिखो
		 * to it in the single descriptor हाल
		 */
		ext = ioat_get_ring_ent(ioat_chan, idx + i + 1);
		xor_ex = ext->xor_ex;

		descs[0] = (काष्ठा ioat_raw_descriptor *) xor;
		descs[1] = (काष्ठा ioat_raw_descriptor *) xor_ex;
		क्रम (s = 0; s < src_cnt; s++)
			xor_set_src(descs, src[s], offset, s);
		xor->size = xfer_size;
		xor->dst_addr = dest + offset;
		xor->ctl = 0;
		xor->ctl_f.op = op;
		xor->ctl_f.src_cnt = src_cnt_to_hw(src_cnt);

		len -= xfer_size;
		offset += xfer_size;
		dump_desc_dbg(ioat_chan, desc);
	पूर्ण जबतक ((i += 1 + with_ext) < num_descs);

	/* last xor descriptor carries the unmap parameters and fence bit */
	desc->txd.flags = flags;
	desc->len = total_len;
	अगर (result)
		desc->result = result;
	xor->ctl_f.fence = !!(flags & DMA_PREP_FENCE);

	/* completion descriptor carries पूर्णांकerrupt bit */
	compl_desc = ioat_get_ring_ent(ioat_chan, idx + i);
	compl_desc->txd.flags = flags & DMA_PREP_INTERRUPT;
	hw = compl_desc->hw;
	hw->ctl = 0;
	hw->ctl_f.null = 1;
	hw->ctl_f.पूर्णांक_en = !!(flags & DMA_PREP_INTERRUPT);
	hw->ctl_f.compl_ग_लिखो = 1;
	hw->size = शून्य_DESC_BUFFER_SIZE;
	dump_desc_dbg(ioat_chan, compl_desc);

	/* we leave the channel locked to ensure in order submission */
	वापस &compl_desc->txd;
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_prep_xor(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
	       अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	वापस __ioat_prep_xor_lock(chan, शून्य, dest, src, src_cnt, len, flags);
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_prep_xor_val(काष्ठा dma_chan *chan, dma_addr_t *src,
		    अचिन्हित पूर्णांक src_cnt, माप_प्रकार len,
		    क्रमागत sum_check_flags *result, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	/* the cleanup routine only sets bits on validate failure, it
	 * करोes not clear bits on validate success... so clear it here
	 */
	*result = 0;

	वापस __ioat_prep_xor_lock(chan, result, src[0], &src[1],
				     src_cnt - 1, len, flags);
पूर्ण

अटल व्योम
dump_pq_desc_dbg(काष्ठा ioatdma_chan *ioat_chan, काष्ठा ioat_ring_ent *desc,
		 काष्ठा ioat_ring_ent *ext)
अणु
	काष्ठा device *dev = to_dev(ioat_chan);
	काष्ठा ioat_pq_descriptor *pq = desc->pq;
	काष्ठा ioat_pq_ext_descriptor *pq_ex = ext ? ext->pq_ex : शून्य;
	काष्ठा ioat_raw_descriptor *descs[] = अणु (व्योम *) pq, (व्योम *) pq_ex पूर्ण;
	पूर्णांक src_cnt = src_cnt_to_sw(pq->ctl_f.src_cnt);
	पूर्णांक i;

	dev_dbg(dev, "desc[%d]: (%#llx->%#llx) flags: %#x"
		" sz: %#10.8x ctl: %#x (op: %#x int: %d compl: %d pq: '%s%s'"
		" src_cnt: %d)\n",
		desc_id(desc), (अचिन्हित दीर्घ दीर्घ) desc->txd.phys,
		(अचिन्हित दीर्घ दीर्घ) (pq_ex ? pq_ex->next : pq->next),
		desc->txd.flags, pq->size, pq->ctl, pq->ctl_f.op,
		pq->ctl_f.पूर्णांक_en, pq->ctl_f.compl_ग_लिखो,
		pq->ctl_f.p_disable ? "" : "p", pq->ctl_f.q_disable ? "" : "q",
		pq->ctl_f.src_cnt);
	क्रम (i = 0; i < src_cnt; i++)
		dev_dbg(dev, "\tsrc[%d]: %#llx coef: %#x\n", i,
			(अचिन्हित दीर्घ दीर्घ) pq_get_src(descs, i), pq->coef[i]);
	dev_dbg(dev, "\tP: %#llx\n", pq->p_addr);
	dev_dbg(dev, "\tQ: %#llx\n", pq->q_addr);
	dev_dbg(dev, "\tNEXT: %#llx\n", pq->next);
पूर्ण

अटल व्योम dump_pq16_desc_dbg(काष्ठा ioatdma_chan *ioat_chan,
			       काष्ठा ioat_ring_ent *desc)
अणु
	काष्ठा device *dev = to_dev(ioat_chan);
	काष्ठा ioat_pq_descriptor *pq = desc->pq;
	काष्ठा ioat_raw_descriptor *descs[] = अणु (व्योम *)pq,
						(व्योम *)pq,
						(व्योम *)pq पूर्ण;
	पूर्णांक src_cnt = src16_cnt_to_sw(pq->ctl_f.src_cnt);
	पूर्णांक i;

	अगर (desc->sed) अणु
		descs[1] = (व्योम *)desc->sed->hw;
		descs[2] = (व्योम *)desc->sed->hw + 64;
	पूर्ण

	dev_dbg(dev, "desc[%d]: (%#llx->%#llx) flags: %#x"
		" sz: %#x ctl: %#x (op: %#x int: %d compl: %d pq: '%s%s'"
		" src_cnt: %d)\n",
		desc_id(desc), (अचिन्हित दीर्घ दीर्घ) desc->txd.phys,
		(अचिन्हित दीर्घ दीर्घ) pq->next,
		desc->txd.flags, pq->size, pq->ctl,
		pq->ctl_f.op, pq->ctl_f.पूर्णांक_en,
		pq->ctl_f.compl_ग_लिखो,
		pq->ctl_f.p_disable ? "" : "p", pq->ctl_f.q_disable ? "" : "q",
		pq->ctl_f.src_cnt);
	क्रम (i = 0; i < src_cnt; i++) अणु
		dev_dbg(dev, "\tsrc[%d]: %#llx coef: %#x\n", i,
			(अचिन्हित दीर्घ दीर्घ) pq16_get_src(descs, i),
			pq->coef[i]);
	पूर्ण
	dev_dbg(dev, "\tP: %#llx\n", pq->p_addr);
	dev_dbg(dev, "\tQ: %#llx\n", pq->q_addr);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
__ioat_prep_pq_lock(काष्ठा dma_chan *c, क्रमागत sum_check_flags *result,
		     स्थिर dma_addr_t *dst, स्थिर dma_addr_t *src,
		     अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf,
		     माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा ioat_ring_ent *compl_desc;
	काष्ठा ioat_ring_ent *desc;
	काष्ठा ioat_ring_ent *ext;
	माप_प्रकार total_len = len;
	काष्ठा ioat_pq_descriptor *pq;
	काष्ठा ioat_pq_ext_descriptor *pq_ex = शून्य;
	काष्ठा ioat_dma_descriptor *hw;
	u32 offset = 0;
	u8 op = result ? IOAT_OP_PQ_VAL : IOAT_OP_PQ;
	पूर्णांक i, s, idx, with_ext, num_descs;
	पूर्णांक cb32 = (ioat_dma->version < IOAT_VER_3_3) ? 1 : 0;

	dev_dbg(to_dev(ioat_chan), "%s\n", __func__);
	/* the engine requires at least two sources (we provide
	 * at least 1 implied source in the DMA_PREP_CONTINUE हाल)
	 */
	BUG_ON(src_cnt + dmaf_जारी(flags) < 2);

	num_descs = ioat_xferlen_to_descs(ioat_chan, len);
	/* we need 2x the number of descriptors to cover greater than 3
	 * sources (we need 1 extra source in the q-only continuation
	 * हाल and 3 extra sources in the p+q continuation हाल.
	 */
	अगर (src_cnt + dmaf_p_disabled_जारी(flags) > 3 ||
	    (dmaf_जारी(flags) && !dmaf_p_disabled_जारी(flags))) अणु
		with_ext = 1;
		num_descs *= 2;
	पूर्ण अन्यथा
		with_ext = 0;

	/* completion ग_लिखोs from the raid engine may pass completion
	 * ग_लिखोs from the legacy engine, so we need one extra null
	 * (legacy) descriptor to ensure all completion ग_लिखोs arrive in
	 * order.
	 */
	अगर (likely(num_descs) &&
	    ioat_check_space_lock(ioat_chan, num_descs + cb32) == 0)
		idx = ioat_chan->head;
	अन्यथा
		वापस शून्य;
	i = 0;
	करो अणु
		काष्ठा ioat_raw_descriptor *descs[2];
		माप_प्रकार xfer_size = min_t(माप_प्रकार, len,
					 1 << ioat_chan->xfercap_log);

		desc = ioat_get_ring_ent(ioat_chan, idx + i);
		pq = desc->pq;

		/* save a branch by unconditionally retrieving the
		 * extended descriptor pq_set_src() knows to not ग_लिखो
		 * to it in the single descriptor हाल
		 */
		ext = ioat_get_ring_ent(ioat_chan, idx + i + with_ext);
		pq_ex = ext->pq_ex;

		descs[0] = (काष्ठा ioat_raw_descriptor *) pq;
		descs[1] = (काष्ठा ioat_raw_descriptor *) pq_ex;

		क्रम (s = 0; s < src_cnt; s++)
			pq_set_src(descs, src[s], offset, scf[s], s);

		/* see the comment क्रम dma_maxpq in include/linux/dmaengine.h */
		अगर (dmaf_p_disabled_जारी(flags))
			pq_set_src(descs, dst[1], offset, 1, s++);
		अन्यथा अगर (dmaf_जारी(flags)) अणु
			pq_set_src(descs, dst[0], offset, 0, s++);
			pq_set_src(descs, dst[1], offset, 1, s++);
			pq_set_src(descs, dst[1], offset, 0, s++);
		पूर्ण
		pq->size = xfer_size;
		pq->p_addr = dst[0] + offset;
		pq->q_addr = dst[1] + offset;
		pq->ctl = 0;
		pq->ctl_f.op = op;
		/* we turn on descriptor ग_लिखो back error status */
		अगर (ioat_dma->cap & IOAT_CAP_DWBES)
			pq->ctl_f.wb_en = result ? 1 : 0;
		pq->ctl_f.src_cnt = src_cnt_to_hw(s);
		pq->ctl_f.p_disable = !!(flags & DMA_PREP_PQ_DISABLE_P);
		pq->ctl_f.q_disable = !!(flags & DMA_PREP_PQ_DISABLE_Q);

		len -= xfer_size;
		offset += xfer_size;
	पूर्ण जबतक ((i += 1 + with_ext) < num_descs);

	/* last pq descriptor carries the unmap parameters and fence bit */
	desc->txd.flags = flags;
	desc->len = total_len;
	अगर (result)
		desc->result = result;
	pq->ctl_f.fence = !!(flags & DMA_PREP_FENCE);
	dump_pq_desc_dbg(ioat_chan, desc, ext);

	अगर (!cb32) अणु
		pq->ctl_f.पूर्णांक_en = !!(flags & DMA_PREP_INTERRUPT);
		pq->ctl_f.compl_ग_लिखो = 1;
		compl_desc = desc;
	पूर्ण अन्यथा अणु
		/* completion descriptor carries पूर्णांकerrupt bit */
		compl_desc = ioat_get_ring_ent(ioat_chan, idx + i);
		compl_desc->txd.flags = flags & DMA_PREP_INTERRUPT;
		hw = compl_desc->hw;
		hw->ctl = 0;
		hw->ctl_f.null = 1;
		hw->ctl_f.पूर्णांक_en = !!(flags & DMA_PREP_INTERRUPT);
		hw->ctl_f.compl_ग_लिखो = 1;
		hw->size = शून्य_DESC_BUFFER_SIZE;
		dump_desc_dbg(ioat_chan, compl_desc);
	पूर्ण


	/* we leave the channel locked to ensure in order submission */
	वापस &compl_desc->txd;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
__ioat_prep_pq16_lock(काष्ठा dma_chan *c, क्रमागत sum_check_flags *result,
		       स्थिर dma_addr_t *dst, स्थिर dma_addr_t *src,
		       अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf,
		       माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा ioat_ring_ent *desc;
	माप_प्रकार total_len = len;
	काष्ठा ioat_pq_descriptor *pq;
	u32 offset = 0;
	u8 op;
	पूर्णांक i, s, idx, num_descs;

	/* this function is only called with 9-16 sources */
	op = result ? IOAT_OP_PQ_VAL_16S : IOAT_OP_PQ_16S;

	dev_dbg(to_dev(ioat_chan), "%s\n", __func__);

	num_descs = ioat_xferlen_to_descs(ioat_chan, len);

	/*
	 * 16 source pq is only available on cb3.3 and has no completion
	 * ग_लिखो hw bug.
	 */
	अगर (num_descs && ioat_check_space_lock(ioat_chan, num_descs) == 0)
		idx = ioat_chan->head;
	अन्यथा
		वापस शून्य;

	i = 0;

	करो अणु
		काष्ठा ioat_raw_descriptor *descs[4];
		माप_प्रकार xfer_size = min_t(माप_प्रकार, len,
					 1 << ioat_chan->xfercap_log);

		desc = ioat_get_ring_ent(ioat_chan, idx + i);
		pq = desc->pq;

		descs[0] = (काष्ठा ioat_raw_descriptor *) pq;

		desc->sed = ioat3_alloc_sed(ioat_dma, (src_cnt-2) >> 3);
		अगर (!desc->sed) अणु
			dev_err(to_dev(ioat_chan),
				"%s: no free sed entries\n", __func__);
			वापस शून्य;
		पूर्ण

		pq->sed_addr = desc->sed->dma;
		desc->sed->parent = desc;

		descs[1] = (काष्ठा ioat_raw_descriptor *)desc->sed->hw;
		descs[2] = (व्योम *)descs[1] + 64;

		क्रम (s = 0; s < src_cnt; s++)
			pq16_set_src(descs, src[s], offset, scf[s], s);

		/* see the comment क्रम dma_maxpq in include/linux/dmaengine.h */
		अगर (dmaf_p_disabled_जारी(flags))
			pq16_set_src(descs, dst[1], offset, 1, s++);
		अन्यथा अगर (dmaf_जारी(flags)) अणु
			pq16_set_src(descs, dst[0], offset, 0, s++);
			pq16_set_src(descs, dst[1], offset, 1, s++);
			pq16_set_src(descs, dst[1], offset, 0, s++);
		पूर्ण

		pq->size = xfer_size;
		pq->p_addr = dst[0] + offset;
		pq->q_addr = dst[1] + offset;
		pq->ctl = 0;
		pq->ctl_f.op = op;
		pq->ctl_f.src_cnt = src16_cnt_to_hw(s);
		/* we turn on descriptor ग_लिखो back error status */
		अगर (ioat_dma->cap & IOAT_CAP_DWBES)
			pq->ctl_f.wb_en = result ? 1 : 0;
		pq->ctl_f.p_disable = !!(flags & DMA_PREP_PQ_DISABLE_P);
		pq->ctl_f.q_disable = !!(flags & DMA_PREP_PQ_DISABLE_Q);

		len -= xfer_size;
		offset += xfer_size;
	पूर्ण जबतक (++i < num_descs);

	/* last pq descriptor carries the unmap parameters and fence bit */
	desc->txd.flags = flags;
	desc->len = total_len;
	अगर (result)
		desc->result = result;
	pq->ctl_f.fence = !!(flags & DMA_PREP_FENCE);

	/* with cb3.3 we should be able to करो completion w/o a null desc */
	pq->ctl_f.पूर्णांक_en = !!(flags & DMA_PREP_INTERRUPT);
	pq->ctl_f.compl_ग_लिखो = 1;

	dump_pq16_desc_dbg(ioat_chan, desc);

	/* we leave the channel locked to ensure in order submission */
	वापस &desc->txd;
पूर्ण

अटल पूर्णांक src_cnt_flags(अचिन्हित पूर्णांक src_cnt, अचिन्हित दीर्घ flags)
अणु
	अगर (dmaf_p_disabled_जारी(flags))
		वापस src_cnt + 1;
	अन्यथा अगर (dmaf_जारी(flags))
		वापस src_cnt + 3;
	अन्यथा
		वापस src_cnt;
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_prep_pq(काष्ठा dma_chan *chan, dma_addr_t *dst, dma_addr_t *src,
	      अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
	      अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	/* specअगरy valid address क्रम disabled result */
	अगर (flags & DMA_PREP_PQ_DISABLE_P)
		dst[0] = dst[1];
	अगर (flags & DMA_PREP_PQ_DISABLE_Q)
		dst[1] = dst[0];

	/* handle the single source multiply हाल from the raid6
	 * recovery path
	 */
	अगर ((flags & DMA_PREP_PQ_DISABLE_P) && src_cnt == 1) अणु
		dma_addr_t single_source[2];
		अचिन्हित अक्षर single_source_coef[2];

		BUG_ON(flags & DMA_PREP_PQ_DISABLE_Q);
		single_source[0] = src[0];
		single_source[1] = src[0];
		single_source_coef[0] = scf[0];
		single_source_coef[1] = 0;

		वापस src_cnt_flags(src_cnt, flags) > 8 ?
			__ioat_prep_pq16_lock(chan, शून्य, dst, single_source,
					       2, single_source_coef, len,
					       flags) :
			__ioat_prep_pq_lock(chan, शून्य, dst, single_source, 2,
					     single_source_coef, len, flags);

	पूर्ण अन्यथा अणु
		वापस src_cnt_flags(src_cnt, flags) > 8 ?
			__ioat_prep_pq16_lock(chan, शून्य, dst, src, src_cnt,
					       scf, len, flags) :
			__ioat_prep_pq_lock(chan, शून्य, dst, src, src_cnt,
					     scf, len, flags);
	पूर्ण
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_prep_pq_val(काष्ठा dma_chan *chan, dma_addr_t *pq, dma_addr_t *src,
		  अचिन्हित पूर्णांक src_cnt, स्थिर अचिन्हित अक्षर *scf, माप_प्रकार len,
		  क्रमागत sum_check_flags *pqres, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	/* specअगरy valid address क्रम disabled result */
	अगर (flags & DMA_PREP_PQ_DISABLE_P)
		pq[0] = pq[1];
	अगर (flags & DMA_PREP_PQ_DISABLE_Q)
		pq[1] = pq[0];

	/* the cleanup routine only sets bits on validate failure, it
	 * करोes not clear bits on validate success... so clear it here
	 */
	*pqres = 0;

	वापस src_cnt_flags(src_cnt, flags) > 8 ?
		__ioat_prep_pq16_lock(chan, pqres, pq, src, src_cnt, scf, len,
				       flags) :
		__ioat_prep_pq_lock(chan, pqres, pq, src, src_cnt, scf, len,
				     flags);
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_prep_pqxor(काष्ठा dma_chan *chan, dma_addr_t dst, dma_addr_t *src,
		 अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित अक्षर scf[MAX_SCF];
	dma_addr_t pq[2];
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	अगर (src_cnt > MAX_SCF)
		वापस शून्य;

	स_रखो(scf, 0, src_cnt);
	pq[0] = dst;
	flags |= DMA_PREP_PQ_DISABLE_Q;
	pq[1] = dst; /* specअगरy valid address क्रम disabled result */

	वापस src_cnt_flags(src_cnt, flags) > 8 ?
		__ioat_prep_pq16_lock(chan, शून्य, pq, src, src_cnt, scf, len,
				       flags) :
		__ioat_prep_pq_lock(chan, शून्य, pq, src, src_cnt, scf, len,
				     flags);
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_prep_pqxor_val(काष्ठा dma_chan *chan, dma_addr_t *src,
		     अचिन्हित पूर्णांक src_cnt, माप_प्रकार len,
		     क्रमागत sum_check_flags *result, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित अक्षर scf[MAX_SCF];
	dma_addr_t pq[2];
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(chan);

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	अगर (src_cnt > MAX_SCF)
		वापस शून्य;

	/* the cleanup routine only sets bits on validate failure, it
	 * करोes not clear bits on validate success... so clear it here
	 */
	*result = 0;

	स_रखो(scf, 0, src_cnt);
	pq[0] = src[0];
	flags |= DMA_PREP_PQ_DISABLE_Q;
	pq[1] = pq[0]; /* specअगरy valid address क्रम disabled result */

	वापस src_cnt_flags(src_cnt, flags) > 8 ?
		__ioat_prep_pq16_lock(chan, result, pq, &src[1], src_cnt - 1,
				       scf, len, flags) :
		__ioat_prep_pq_lock(chan, result, pq, &src[1], src_cnt - 1,
				     scf, len, flags);
पूर्ण

काष्ठा dma_async_tx_descriptor *
ioat_prep_पूर्णांकerrupt_lock(काष्ठा dma_chan *c, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioat_ring_ent *desc;
	काष्ठा ioat_dma_descriptor *hw;

	अगर (test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		वापस शून्य;

	अगर (ioat_check_space_lock(ioat_chan, 1) == 0)
		desc = ioat_get_ring_ent(ioat_chan, ioat_chan->head);
	अन्यथा
		वापस शून्य;

	hw = desc->hw;
	hw->ctl = 0;
	hw->ctl_f.null = 1;
	hw->ctl_f.पूर्णांक_en = 1;
	hw->ctl_f.fence = !!(flags & DMA_PREP_FENCE);
	hw->ctl_f.compl_ग_लिखो = 1;
	hw->size = शून्य_DESC_BUFFER_SIZE;
	hw->src_addr = 0;
	hw->dst_addr = 0;

	desc->txd.flags = flags;
	desc->len = 1;

	dump_desc_dbg(ioat_chan, desc);

	/* we leave the channel locked to ensure in order submission */
	वापस &desc->txd;
पूर्ण

