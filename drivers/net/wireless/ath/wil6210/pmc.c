<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2015,2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश "wmi.h"
#समावेश "wil6210.h"
#समावेश "txrx.h"
#समावेश "pmc.h"

काष्ठा desc_alloc_info अणु
	dma_addr_t pa;
	व्योम	  *va;
पूर्ण;

अटल पूर्णांक wil_is_pmc_allocated(काष्ठा pmc_ctx *pmc)
अणु
	वापस !!pmc->pring_va;
पूर्ण

व्योम wil_pmc_init(काष्ठा wil6210_priv *wil)
अणु
	स_रखो(&wil->pmc, 0, माप(काष्ठा pmc_ctx));
	mutex_init(&wil->pmc.lock);
पूर्ण

/* Allocate the physical ring (p-ring) and the required
 * number of descriptors of required size.
 * Initialize the descriptors as required by pmc dma.
 * The descriptors' buffers dwords are initialized to hold
 * dword's serial number in the lsw and reserved value
 * PCM_DATA_INVALID_DW_VAL in the msw.
 */
व्योम wil_pmc_alloc(काष्ठा wil6210_priv *wil,
		   पूर्णांक num_descriptors,
		   पूर्णांक descriptor_size)
अणु
	u32 i;
	काष्ठा pmc_ctx *pmc = &wil->pmc;
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wmi_pmc_cmd pmc_cmd = अणु0पूर्ण;
	पूर्णांक last_cmd_err = -ENOMEM;

	mutex_lock(&pmc->lock);

	अगर (wil_is_pmc_allocated(pmc)) अणु
		/* sanity check */
		wil_err(wil, "ERROR pmc is already allocated\n");
		जाओ no_release_err;
	पूर्ण
	अगर ((num_descriptors <= 0) || (descriptor_size <= 0)) अणु
		wil_err(wil,
			"Invalid params num_descriptors(%d), descriptor_size(%d)\n",
			num_descriptors, descriptor_size);
		last_cmd_err = -EINVAL;
		जाओ no_release_err;
	पूर्ण

	अगर (num_descriptors > (1 << WIL_RING_SIZE_ORDER_MAX)) अणु
		wil_err(wil,
			"num_descriptors(%d) exceeds max ring size %d\n",
			num_descriptors, 1 << WIL_RING_SIZE_ORDER_MAX);
		last_cmd_err = -EINVAL;
		जाओ no_release_err;
	पूर्ण

	अगर (num_descriptors > पूर्णांक_उच्च / descriptor_size) अणु
		wil_err(wil,
			"Overflow in num_descriptors(%d)*descriptor_size(%d)\n",
			num_descriptors, descriptor_size);
		last_cmd_err = -EINVAL;
		जाओ no_release_err;
	पूर्ण

	pmc->num_descriptors = num_descriptors;
	pmc->descriptor_size = descriptor_size;

	wil_dbg_misc(wil, "pmc_alloc: %d descriptors x %d bytes each\n",
		     num_descriptors, descriptor_size);

	/* allocate descriptors info list in pmc context*/
	pmc->descriptors = kसुस्मृति(num_descriptors,
				  माप(काष्ठा desc_alloc_info),
				  GFP_KERNEL);
	अगर (!pmc->descriptors) अणु
		wil_err(wil, "ERROR allocating pmc skb list\n");
		जाओ no_release_err;
	पूर्ण

	wil_dbg_misc(wil, "pmc_alloc: allocated descriptors info list %p\n",
		     pmc->descriptors);

	/* Allocate pring buffer and descriptors.
	 * vring->va should be aligned on its size rounded up to घातer of 2
	 * This is granted by the dma_alloc_coherent.
	 *
	 * HW has limitation that all vrings addresses must share the same
	 * upper 16 msb bits part of 48 bits address. To workaround that,
	 * अगर we are using more than 32 bit addresses चयन to 32 bit
	 * allocation beक्रमe allocating vring memory.
	 *
	 * There's no check क्रम the वापस value of dma_set_mask_and_coherent,
	 * since we assume अगर we were able to set the mask during
	 * initialization in this प्रणाली it will not fail अगर we set it again
	 */
	अगर (wil->dma_addr_size > 32)
		dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));

	pmc->pring_va = dma_alloc_coherent(dev,
			माप(काष्ठा vring_tx_desc) * num_descriptors,
			&pmc->pring_pa,
			GFP_KERNEL);

	अगर (wil->dma_addr_size > 32)
		dma_set_mask_and_coherent(dev,
					  DMA_BIT_MASK(wil->dma_addr_size));

	wil_dbg_misc(wil,
		     "pmc_alloc: allocated pring %p => %pad. %zd x %d = total %zd bytes\n",
		     pmc->pring_va, &pmc->pring_pa,
		     माप(काष्ठा vring_tx_desc),
		     num_descriptors,
		     माप(काष्ठा vring_tx_desc) * num_descriptors);

	अगर (!pmc->pring_va) अणु
		wil_err(wil, "ERROR allocating pmc pring\n");
		जाओ release_pmc_skb_list;
	पूर्ण

	/* initially, all descriptors are SW owned
	 * For Tx, Rx, and PMC, ownership bit is at the same location, thus
	 * we can use any
	 */
	क्रम (i = 0; i < num_descriptors; i++) अणु
		काष्ठा vring_tx_desc *_d = &pmc->pring_va[i];
		काष्ठा vring_tx_desc dd = अणुपूर्ण, *d = &dd;
		पूर्णांक j = 0;

		pmc->descriptors[i].va = dma_alloc_coherent(dev,
			descriptor_size,
			&pmc->descriptors[i].pa,
			GFP_KERNEL);

		अगर (unlikely(!pmc->descriptors[i].va)) अणु
			wil_err(wil, "ERROR allocating pmc descriptor %d", i);
			जाओ release_pmc_skbs;
		पूर्ण

		क्रम (j = 0; j < descriptor_size / माप(u32); j++) अणु
			u32 *p = (u32 *)pmc->descriptors[i].va + j;
			*p = PCM_DATA_INVALID_DW_VAL | j;
		पूर्ण

		/* configure dma descriptor */
		d->dma.addr.addr_low =
			cpu_to_le32(lower_32_bits(pmc->descriptors[i].pa));
		d->dma.addr.addr_high =
			cpu_to_le16((u16)upper_32_bits(pmc->descriptors[i].pa));
		d->dma.status = 0; /* 0 = HW_OWNED */
		d->dma.length = cpu_to_le16(descriptor_size);
		d->dma.d0 = BIT(9) | RX_DMA_D0_CMD_DMA_IT;
		*_d = *d;
	पूर्ण

	wil_dbg_misc(wil, "pmc_alloc: allocated successfully\n");

	pmc_cmd.op = WMI_PMC_ALLOCATE;
	pmc_cmd.ring_size = cpu_to_le16(pmc->num_descriptors);
	pmc_cmd.mem_base = cpu_to_le64(pmc->pring_pa);

	wil_dbg_misc(wil, "pmc_alloc: send WMI_PMC_CMD with ALLOCATE op\n");
	pmc->last_cmd_status = wmi_send(wil,
					WMI_PMC_CMDID,
					vअगर->mid,
					&pmc_cmd,
					माप(pmc_cmd));
	अगर (pmc->last_cmd_status) अणु
		wil_err(wil,
			"WMI_PMC_CMD with ALLOCATE op failed with status %d",
			pmc->last_cmd_status);
		जाओ release_pmc_skbs;
	पूर्ण

	mutex_unlock(&pmc->lock);

	वापस;

release_pmc_skbs:
	wil_err(wil, "exit on error: Releasing skbs...\n");
	क्रम (i = 0; i < num_descriptors && pmc->descriptors[i].va; i++) अणु
		dma_मुक्त_coherent(dev,
				  descriptor_size,
				  pmc->descriptors[i].va,
				  pmc->descriptors[i].pa);

		pmc->descriptors[i].va = शून्य;
	पूर्ण
	wil_err(wil, "exit on error: Releasing pring...\n");

	dma_मुक्त_coherent(dev,
			  माप(काष्ठा vring_tx_desc) * num_descriptors,
			  pmc->pring_va,
			  pmc->pring_pa);

	pmc->pring_va = शून्य;

release_pmc_skb_list:
	wil_err(wil, "exit on error: Releasing descriptors info list...\n");
	kमुक्त(pmc->descriptors);
	pmc->descriptors = शून्य;

no_release_err:
	pmc->last_cmd_status = last_cmd_err;
	mutex_unlock(&pmc->lock);
पूर्ण

/* Traverse the p-ring and release all buffers.
 * At the end release the p-ring memory
 */
व्योम wil_pmc_मुक्त(काष्ठा wil6210_priv *wil, पूर्णांक send_pmc_cmd)
अणु
	काष्ठा pmc_ctx *pmc = &wil->pmc;
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wmi_pmc_cmd pmc_cmd = अणु0पूर्ण;

	mutex_lock(&pmc->lock);

	pmc->last_cmd_status = 0;

	अगर (!wil_is_pmc_allocated(pmc)) अणु
		wil_dbg_misc(wil,
			     "pmc_free: Error, can't free - not allocated\n");
		pmc->last_cmd_status = -EPERM;
		mutex_unlock(&pmc->lock);
		वापस;
	पूर्ण

	अगर (send_pmc_cmd) अणु
		wil_dbg_misc(wil, "send WMI_PMC_CMD with RELEASE op\n");
		pmc_cmd.op = WMI_PMC_RELEASE;
		pmc->last_cmd_status =
				wmi_send(wil, WMI_PMC_CMDID, vअगर->mid,
					 &pmc_cmd, माप(pmc_cmd));
		अगर (pmc->last_cmd_status) अणु
			wil_err(wil,
				"WMI_PMC_CMD with RELEASE op failed, status %d",
				pmc->last_cmd_status);
			/* There's nothing we can करो with this error.
			 * Normally, it should never occur.
			 * Continue to मुक्तing all memory allocated क्रम pmc.
			 */
		पूर्ण
	पूर्ण

	अगर (pmc->pring_va) अणु
		माप_प्रकार buf_size = माप(काष्ठा vring_tx_desc) *
				  pmc->num_descriptors;

		wil_dbg_misc(wil, "pmc_free: free pring va %p\n",
			     pmc->pring_va);
		dma_मुक्त_coherent(dev, buf_size, pmc->pring_va, pmc->pring_pa);

		pmc->pring_va = शून्य;
	पूर्ण अन्यथा अणु
		pmc->last_cmd_status = -ENOENT;
	पूर्ण

	अगर (pmc->descriptors) अणु
		पूर्णांक i;

		क्रम (i = 0;
		     i < pmc->num_descriptors && pmc->descriptors[i].va; i++) अणु
			dma_मुक्त_coherent(dev,
					  pmc->descriptor_size,
					  pmc->descriptors[i].va,
					  pmc->descriptors[i].pa);
			pmc->descriptors[i].va = शून्य;
		पूर्ण
		wil_dbg_misc(wil, "pmc_free: free descriptor info %d/%d\n", i,
			     pmc->num_descriptors);
		wil_dbg_misc(wil,
			     "pmc_free: free pmc descriptors info list %p\n",
			     pmc->descriptors);
		kमुक्त(pmc->descriptors);
		pmc->descriptors = शून्य;
	पूर्ण अन्यथा अणु
		pmc->last_cmd_status = -ENOENT;
	पूर्ण

	mutex_unlock(&pmc->lock);
पूर्ण

/* Status of the last operation requested via debugfs: alloc/मुक्त/पढ़ो.
 * 0 - success or negative त्रुटि_सं
 */
पूर्णांक wil_pmc_last_cmd_status(काष्ठा wil6210_priv *wil)
अणु
	wil_dbg_misc(wil, "pmc_last_cmd_status: status %d\n",
		     wil->pmc.last_cmd_status);

	वापस wil->pmc.last_cmd_status;
पूर्ण

/* Read from required position up to the end of current descriptor,
 * depends on descriptor size configured during alloc request.
 */
sमाप_प्रकार wil_pmc_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
		     loff_t *f_pos)
अणु
	काष्ठा wil6210_priv *wil = filp->निजी_data;
	काष्ठा pmc_ctx *pmc = &wil->pmc;
	माप_प्रकार retval = 0;
	अचिन्हित दीर्घ दीर्घ idx;
	loff_t offset;
	माप_प्रकार pmc_size;

	mutex_lock(&pmc->lock);

	अगर (!wil_is_pmc_allocated(pmc)) अणु
		wil_err(wil, "error, pmc is not allocated!\n");
		pmc->last_cmd_status = -EPERM;
		mutex_unlock(&pmc->lock);
		वापस -EPERM;
	पूर्ण

	pmc_size = pmc->descriptor_size * pmc->num_descriptors;

	wil_dbg_misc(wil,
		     "pmc_read: size %u, pos %lld\n",
		     (u32)count, *f_pos);

	pmc->last_cmd_status = 0;

	idx = *f_pos;
	करो_भाग(idx, pmc->descriptor_size);
	offset = *f_pos - (idx * pmc->descriptor_size);

	अगर (*f_pos >= pmc_size) अणु
		wil_dbg_misc(wil,
			     "pmc_read: reached end of pmc buf: %lld >= %u\n",
			     *f_pos, (u32)pmc_size);
		pmc->last_cmd_status = -दुस्फल;
		जाओ out;
	पूर्ण

	wil_dbg_misc(wil,
		     "pmc_read: read from pos %lld (descriptor %llu, offset %llu) %zu bytes\n",
		     *f_pos, idx, offset, count);

	/* अगर no errors, वापस the copied byte count */
	retval = simple_पढ़ो_from_buffer(buf,
					 count,
					 &offset,
					 pmc->descriptors[idx].va,
					 pmc->descriptor_size);
	*f_pos += retval;
out:
	mutex_unlock(&pmc->lock);

	वापस retval;
पूर्ण

loff_t wil_pmc_llseek(काष्ठा file *filp, loff_t off, पूर्णांक whence)
अणु
	loff_t newpos;
	काष्ठा wil6210_priv *wil = filp->निजी_data;
	काष्ठा pmc_ctx *pmc = &wil->pmc;
	माप_प्रकार pmc_size;

	mutex_lock(&pmc->lock);

	अगर (!wil_is_pmc_allocated(pmc)) अणु
		wil_err(wil, "error, pmc is not allocated!\n");
		pmc->last_cmd_status = -EPERM;
		mutex_unlock(&pmc->lock);
		वापस -EPERM;
	पूर्ण

	pmc_size = pmc->descriptor_size * pmc->num_descriptors;

	चयन (whence) अणु
	हाल 0: /* शुरू_से */
		newpos = off;
		अवरोध;

	हाल 1: /* प्रस्तुत_से */
		newpos = filp->f_pos + off;
		अवरोध;

	हाल 2: /* अंत_से */
		newpos = pmc_size;
		अवरोध;

	शेष: /* can't happen */
		newpos = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (newpos < 0) अणु
		newpos = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (newpos > pmc_size)
		newpos = pmc_size;

	filp->f_pos = newpos;

out:
	mutex_unlock(&pmc->lock);

	वापस newpos;
पूर्ण

पूर्णांक wil_pmcring_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा pmc_ctx *pmc = &wil->pmc;
	माप_प्रकार pmc_ring_size =
		माप(काष्ठा vring_rx_desc) * pmc->num_descriptors;

	mutex_lock(&pmc->lock);

	अगर (!wil_is_pmc_allocated(pmc)) अणु
		wil_err(wil, "error, pmc is not allocated!\n");
		pmc->last_cmd_status = -EPERM;
		mutex_unlock(&pmc->lock);
		वापस -EPERM;
	पूर्ण

	wil_dbg_misc(wil, "pmcring_read: size %zu\n", pmc_ring_size);

	seq_ग_लिखो(s, pmc->pring_va, pmc_ring_size);

	mutex_unlock(&pmc->lock);

	वापस 0;
पूर्ण
