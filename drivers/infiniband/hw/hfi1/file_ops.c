<शैली गुरु>
/*
 * Copyright(c) 2020 Cornelis Networks, Inc.
 * Copyright(c) 2015-2020 Intel Corporation.
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
#समावेश <linux/poll.h>
#समावेश <linux/cdev.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/biपंचांगap.h>

#समावेश <rdma/ib.h>

#समावेश "hfi.h"
#समावेश "pio.h"
#समावेश "device.h"
#समावेश "common.h"
#समावेश "trace.h"
#समावेश "mmu_rb.h"
#समावेश "user_sdma.h"
#समावेश "user_exp_rcv.h"
#समावेश "aspm.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) DRIVER_NAME ": " fmt

#घोषणा SEND_CTXT_HALT_TIMEOUT 1000 /* msecs */

/*
 * File operation functions
 */
अटल पूर्णांक hfi1_file_खोलो(काष्ठा inode *inode, काष्ठा file *fp);
अटल पूर्णांक hfi1_file_बंद(काष्ठा inode *inode, काष्ठा file *fp);
अटल sमाप_प्रकार hfi1_ग_लिखो_iter(काष्ठा kiocb *kiocb, काष्ठा iov_iter *from);
अटल __poll_t hfi1_poll(काष्ठा file *fp, काष्ठा poll_table_काष्ठा *pt);
अटल पूर्णांक hfi1_file_mmap(काष्ठा file *fp, काष्ठा vm_area_काष्ठा *vma);

अटल u64 kvirt_to_phys(व्योम *addr);
अटल पूर्णांक assign_ctxt(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg, u32 len);
अटल व्योम init_subctxts(काष्ठा hfi1_ctxtdata *uctxt,
			  स्थिर काष्ठा hfi1_user_info *uinfo);
अटल पूर्णांक init_user_ctxt(काष्ठा hfi1_filedata *fd,
			  काष्ठा hfi1_ctxtdata *uctxt);
अटल व्योम user_init(काष्ठा hfi1_ctxtdata *uctxt);
अटल पूर्णांक get_ctxt_info(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg, u32 len);
अटल पूर्णांक get_base_info(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg, u32 len);
अटल पूर्णांक user_exp_rcv_setup(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg,
			      u32 len);
अटल पूर्णांक user_exp_rcv_clear(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg,
			      u32 len);
अटल पूर्णांक user_exp_rcv_invalid(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg,
				u32 len);
अटल पूर्णांक setup_base_ctxt(काष्ठा hfi1_filedata *fd,
			   काष्ठा hfi1_ctxtdata *uctxt);
अटल पूर्णांक setup_subctxt(काष्ठा hfi1_ctxtdata *uctxt);

अटल पूर्णांक find_sub_ctxt(काष्ठा hfi1_filedata *fd,
			 स्थिर काष्ठा hfi1_user_info *uinfo);
अटल पूर्णांक allocate_ctxt(काष्ठा hfi1_filedata *fd, काष्ठा hfi1_devdata *dd,
			 काष्ठा hfi1_user_info *uinfo,
			 काष्ठा hfi1_ctxtdata **cd);
अटल व्योम deallocate_ctxt(काष्ठा hfi1_ctxtdata *uctxt);
अटल __poll_t poll_urgent(काष्ठा file *fp, काष्ठा poll_table_काष्ठा *pt);
अटल __poll_t poll_next(काष्ठा file *fp, काष्ठा poll_table_काष्ठा *pt);
अटल पूर्णांक user_event_ack(काष्ठा hfi1_ctxtdata *uctxt, u16 subctxt,
			  अचिन्हित दीर्घ arg);
अटल पूर्णांक set_ctxt_pkey(काष्ठा hfi1_ctxtdata *uctxt, अचिन्हित दीर्घ arg);
अटल पूर्णांक ctxt_reset(काष्ठा hfi1_ctxtdata *uctxt);
अटल पूर्णांक manage_rcvq(काष्ठा hfi1_ctxtdata *uctxt, u16 subctxt,
		       अचिन्हित दीर्घ arg);
अटल vm_fault_t vma_fault(काष्ठा vm_fault *vmf);
अटल दीर्घ hfi1_file_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg);

अटल स्थिर काष्ठा file_operations hfi1_file_ops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो_iter = hfi1_ग_लिखो_iter,
	.खोलो = hfi1_file_खोलो,
	.release = hfi1_file_बंद,
	.unlocked_ioctl = hfi1_file_ioctl,
	.poll = hfi1_poll,
	.mmap = hfi1_file_mmap,
	.llseek = noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा vm_ops = अणु
	.fault = vma_fault,
पूर्ण;

/*
 * Types of memories mapped पूर्णांकo user processes' space
 */
क्रमागत mmap_types अणु
	PIO_BUFS = 1,
	PIO_BUFS_SOP,
	PIO_CRED,
	RCV_HDRQ,
	RCV_EGRBUF,
	UREGS,
	EVENTS,
	STATUS,
	RTAIL,
	SUBCTXT_UREGS,
	SUBCTXT_RCV_HDRQ,
	SUBCTXT_EGRBUF,
	SDMA_COMP
पूर्ण;

/*
 * Masks and offsets defining the mmap tokens
 */
#घोषणा HFI1_MMAP_OFFSET_MASK   0xfffULL
#घोषणा HFI1_MMAP_OFFSET_SHIFT  0
#घोषणा HFI1_MMAP_SUBCTXT_MASK  0xfULL
#घोषणा HFI1_MMAP_SUBCTXT_SHIFT 12
#घोषणा HFI1_MMAP_CTXT_MASK     0xffULL
#घोषणा HFI1_MMAP_CTXT_SHIFT    16
#घोषणा HFI1_MMAP_TYPE_MASK     0xfULL
#घोषणा HFI1_MMAP_TYPE_SHIFT    24
#घोषणा HFI1_MMAP_MAGIC_MASK    0xffffffffULL
#घोषणा HFI1_MMAP_MAGIC_SHIFT   32

#घोषणा HFI1_MMAP_MAGIC         0xdabbad00

#घोषणा HFI1_MMAP_TOKEN_SET(field, val)	\
	(((val) & HFI1_MMAP_##field##_MASK) << HFI1_MMAP_##field##_SHIFT)
#घोषणा HFI1_MMAP_TOKEN_GET(field, token) \
	(((token) >> HFI1_MMAP_##field##_SHIFT) & HFI1_MMAP_##field##_MASK)
#घोषणा HFI1_MMAP_TOKEN(type, ctxt, subctxt, addr)   \
	(HFI1_MMAP_TOKEN_SET(MAGIC, HFI1_MMAP_MAGIC) | \
	HFI1_MMAP_TOKEN_SET(TYPE, type) | \
	HFI1_MMAP_TOKEN_SET(CTXT, ctxt) | \
	HFI1_MMAP_TOKEN_SET(SUBCTXT, subctxt) | \
	HFI1_MMAP_TOKEN_SET(OFFSET, (offset_in_page(addr))))

#घोषणा dbg(fmt, ...)				\
	pr_info(fmt, ##__VA_ARGS__)

अटल अंतरभूत पूर्णांक is_valid_mmap(u64 token)
अणु
	वापस (HFI1_MMAP_TOKEN_GET(MAGIC, token) == HFI1_MMAP_MAGIC);
पूर्ण

अटल पूर्णांक hfi1_file_खोलो(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	काष्ठा hfi1_filedata *fd;
	काष्ठा hfi1_devdata *dd = container_of(inode->i_cdev,
					       काष्ठा hfi1_devdata,
					       user_cdev);

	अगर (!((dd->flags & HFI1_PRESENT) && dd->kregbase1))
		वापस -EINVAL;

	अगर (!atomic_inc_not_zero(&dd->user_refcount))
		वापस -ENXIO;

	/* The real work is perक्रमmed later in assign_ctxt() */

	fd = kzalloc(माप(*fd), GFP_KERNEL);

	अगर (!fd || init_srcu_काष्ठा(&fd->pq_srcu))
		जाओ nomem;
	spin_lock_init(&fd->pq_rcu_lock);
	spin_lock_init(&fd->tid_lock);
	spin_lock_init(&fd->invalid_lock);
	fd->rec_cpu_num = -1; /* no cpu affinity by शेष */
	fd->dd = dd;
	fp->निजी_data = fd;
	वापस 0;
nomem:
	kमुक्त(fd);
	fp->निजी_data = शून्य;
	अगर (atomic_dec_and_test(&dd->user_refcount))
		complete(&dd->user_comp);
	वापस -ENOMEM;
पूर्ण

अटल दीर्घ hfi1_file_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा hfi1_filedata *fd = fp->निजी_data;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	पूर्णांक ret = 0;
	पूर्णांक uval = 0;

	hfi1_cdbg(IOCTL, "IOCTL recv: 0x%x", cmd);
	अगर (cmd != HFI1_IOCTL_ASSIGN_CTXT &&
	    cmd != HFI1_IOCTL_GET_VERS &&
	    !uctxt)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल HFI1_IOCTL_ASSIGN_CTXT:
		ret = assign_ctxt(fd, arg, _IOC_SIZE(cmd));
		अवरोध;

	हाल HFI1_IOCTL_CTXT_INFO:
		ret = get_ctxt_info(fd, arg, _IOC_SIZE(cmd));
		अवरोध;

	हाल HFI1_IOCTL_USER_INFO:
		ret = get_base_info(fd, arg, _IOC_SIZE(cmd));
		अवरोध;

	हाल HFI1_IOCTL_CREDIT_UPD:
		अगर (uctxt)
			sc_वापस_credits(uctxt->sc);
		अवरोध;

	हाल HFI1_IOCTL_TID_UPDATE:
		ret = user_exp_rcv_setup(fd, arg, _IOC_SIZE(cmd));
		अवरोध;

	हाल HFI1_IOCTL_TID_FREE:
		ret = user_exp_rcv_clear(fd, arg, _IOC_SIZE(cmd));
		अवरोध;

	हाल HFI1_IOCTL_TID_INVAL_READ:
		ret = user_exp_rcv_invalid(fd, arg, _IOC_SIZE(cmd));
		अवरोध;

	हाल HFI1_IOCTL_RECV_CTRL:
		ret = manage_rcvq(uctxt, fd->subctxt, arg);
		अवरोध;

	हाल HFI1_IOCTL_POLL_TYPE:
		अगर (get_user(uval, (पूर्णांक __user *)arg))
			वापस -EFAULT;
		uctxt->poll_type = (typeof(uctxt->poll_type))uval;
		अवरोध;

	हाल HFI1_IOCTL_ACK_EVENT:
		ret = user_event_ack(uctxt, fd->subctxt, arg);
		अवरोध;

	हाल HFI1_IOCTL_SET_PKEY:
		ret = set_ctxt_pkey(uctxt, arg);
		अवरोध;

	हाल HFI1_IOCTL_CTXT_RESET:
		ret = ctxt_reset(uctxt);
		अवरोध;

	हाल HFI1_IOCTL_GET_VERS:
		uval = HFI1_USER_SWVERSION;
		अगर (put_user(uval, (पूर्णांक __user *)arg))
			वापस -EFAULT;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार hfi1_ग_लिखो_iter(काष्ठा kiocb *kiocb, काष्ठा iov_iter *from)
अणु
	काष्ठा hfi1_filedata *fd = kiocb->ki_filp->निजी_data;
	काष्ठा hfi1_user_sdma_pkt_q *pq;
	काष्ठा hfi1_user_sdma_comp_q *cq = fd->cq;
	पूर्णांक करोne = 0, reqs = 0;
	अचिन्हित दीर्घ dim = from->nr_segs;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&fd->pq_srcu);
	pq = srcu_dereference(fd->pq, &fd->pq_srcu);
	अगर (!cq || !pq) अणु
		srcu_पढ़ो_unlock(&fd->pq_srcu, idx);
		वापस -EIO;
	पूर्ण

	अगर (!iter_is_iovec(from) || !dim) अणु
		srcu_पढ़ो_unlock(&fd->pq_srcu, idx);
		वापस -EINVAL;
	पूर्ण

	trace_hfi1_sdma_request(fd->dd, fd->uctxt->ctxt, fd->subctxt, dim);

	अगर (atomic_पढ़ो(&pq->n_reqs) == pq->n_max_reqs) अणु
		srcu_पढ़ो_unlock(&fd->pq_srcu, idx);
		वापस -ENOSPC;
	पूर्ण

	जबतक (dim) अणु
		पूर्णांक ret;
		अचिन्हित दीर्घ count = 0;

		ret = hfi1_user_sdma_process_request(
			fd, (काष्ठा iovec *)(from->iov + करोne),
			dim, &count);
		अगर (ret) अणु
			reqs = ret;
			अवरोध;
		पूर्ण
		dim -= count;
		करोne += count;
		reqs++;
	पूर्ण

	srcu_पढ़ो_unlock(&fd->pq_srcu, idx);
	वापस reqs;
पूर्ण

अटल पूर्णांक hfi1_file_mmap(काष्ठा file *fp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hfi1_filedata *fd = fp->निजी_data;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd;
	अचिन्हित दीर्घ flags;
	u64 token = vma->vm_pgoff << PAGE_SHIFT,
		memaddr = 0;
	व्योम *memvirt = शून्य;
	u8 subctxt, mapio = 0, vmf = 0, type;
	sमाप_प्रकार memlen = 0;
	पूर्णांक ret = 0;
	u16 ctxt;

	अगर (!is_valid_mmap(token) || !uctxt ||
	    !(vma->vm_flags & VM_SHARED)) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण
	dd = uctxt->dd;
	ctxt = HFI1_MMAP_TOKEN_GET(CTXT, token);
	subctxt = HFI1_MMAP_TOKEN_GET(SUBCTXT, token);
	type = HFI1_MMAP_TOKEN_GET(TYPE, token);
	अगर (ctxt != uctxt->ctxt || subctxt != fd->subctxt) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	flags = vma->vm_flags;

	चयन (type) अणु
	हाल PIO_BUFS:
	हाल PIO_BUFS_SOP:
		memaddr = ((dd->physaddr + TXE_PIO_SEND) +
				/* chip pio base */
			   (uctxt->sc->hw_context * BIT(16))) +
				/* 64K PIO space / ctxt */
			(type == PIO_BUFS_SOP ?
				(TXE_PIO_SIZE / 2) : 0); /* sop? */
		/*
		 * Map only the amount allocated to the context, not the
		 * entire available context's PIO space.
		 */
		memlen = PAGE_ALIGN(uctxt->sc->credits * PIO_BLOCK_SIZE);
		flags &= ~VM_MAYREAD;
		flags |= VM_DONTCOPY | VM_DONTEXPAND;
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
		mapio = 1;
		अवरोध;
	हाल PIO_CRED:
		अगर (flags & VM_WRITE) अणु
			ret = -EPERM;
			जाओ करोne;
		पूर्ण
		/*
		 * The credit वापस location क्रम this context could be on the
		 * second or third page allocated क्रम credit वापसs (अगर number
		 * of enabled contexts > 64 and 128 respectively).
		 */
		memvirt = dd->cr_base[uctxt->numa_id].va;
		memaddr = virt_to_phys(memvirt) +
			(((u64)uctxt->sc->hw_मुक्त -
			  (u64)dd->cr_base[uctxt->numa_id].va) & PAGE_MASK);
		memlen = PAGE_SIZE;
		flags &= ~VM_MAYWRITE;
		flags |= VM_DONTCOPY | VM_DONTEXPAND;
		/*
		 * The driver has alपढ़ोy allocated memory क्रम credit
		 * वापसs and programmed it पूर्णांकo the chip. Has that
		 * memory been flagged as non-cached?
		 */
		/* vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot); */
		mapio = 1;
		अवरोध;
	हाल RCV_HDRQ:
		memlen = rcvhdrq_size(uctxt);
		memvirt = uctxt->rcvhdrq;
		अवरोध;
	हाल RCV_EGRBUF: अणु
		अचिन्हित दीर्घ addr;
		पूर्णांक i;
		/*
		 * The RcvEgr buffer need to be handled dअगरferently
		 * as multiple non-contiguous pages need to be mapped
		 * पूर्णांकo the user process.
		 */
		memlen = uctxt->egrbufs.size;
		अगर ((vma->vm_end - vma->vm_start) != memlen) अणु
			dd_dev_err(dd, "Eager buffer map size invalid (%lu != %lu)\n",
				   (vma->vm_end - vma->vm_start), memlen);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		अगर (vma->vm_flags & VM_WRITE) अणु
			ret = -EPERM;
			जाओ करोne;
		पूर्ण
		vma->vm_flags &= ~VM_MAYWRITE;
		addr = vma->vm_start;
		क्रम (i = 0 ; i < uctxt->egrbufs.numbufs; i++) अणु
			memlen = uctxt->egrbufs.buffers[i].len;
			memvirt = uctxt->egrbufs.buffers[i].addr;
			ret = remap_pfn_range(
				vma, addr,
				/*
				 * virt_to_pfn() करोes the same, but
				 * it's not available on x86_64
				 * when CONFIG_MMU is enabled.
				 */
				PFN_DOWN(__pa(memvirt)),
				memlen,
				vma->vm_page_prot);
			अगर (ret < 0)
				जाओ करोne;
			addr += memlen;
		पूर्ण
		ret = 0;
		जाओ करोne;
	पूर्ण
	हाल UREGS:
		/*
		 * Map only the page that contains this context's user
		 * रेजिस्टरs.
		 */
		memaddr = (अचिन्हित दीर्घ)
			(dd->physaddr + RXE_PER_CONTEXT_USER)
			+ (uctxt->ctxt * RXE_PER_CONTEXT_SIZE);
		/*
		 * TidFlow table is on the same page as the rest of the
		 * user रेजिस्टरs.
		 */
		memlen = PAGE_SIZE;
		flags |= VM_DONTCOPY | VM_DONTEXPAND;
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
		mapio = 1;
		अवरोध;
	हाल EVENTS:
		/*
		 * Use the page where this context's flags are. User level
		 * knows where it's own biपंचांगap is within the page.
		 */
		memaddr = (अचिन्हित दीर्घ)
			(dd->events + uctxt_offset(uctxt)) & PAGE_MASK;
		memlen = PAGE_SIZE;
		/*
		 * v3.7 हटाओs VM_RESERVED but the effect is kept by
		 * using VM_IO.
		 */
		flags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		अवरोध;
	हाल STATUS:
		अगर (flags & VM_WRITE) अणु
			ret = -EPERM;
			जाओ करोne;
		पूर्ण
		memaddr = kvirt_to_phys((व्योम *)dd->status);
		memlen = PAGE_SIZE;
		flags |= VM_IO | VM_DONTEXPAND;
		अवरोध;
	हाल RTAIL:
		अगर (!HFI1_CAP_IS_USET(DMA_RTAIL)) अणु
			/*
			 * If the memory allocation failed, the context alloc
			 * also would have failed, so we would never get here
			 */
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
		अगर ((flags & VM_WRITE) || !hfi1_rcvhdrtail_kvaddr(uctxt)) अणु
			ret = -EPERM;
			जाओ करोne;
		पूर्ण
		memlen = PAGE_SIZE;
		memvirt = (व्योम *)hfi1_rcvhdrtail_kvaddr(uctxt);
		flags &= ~VM_MAYWRITE;
		अवरोध;
	हाल SUBCTXT_UREGS:
		memaddr = (u64)uctxt->subctxt_uregbase;
		memlen = PAGE_SIZE;
		flags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		अवरोध;
	हाल SUBCTXT_RCV_HDRQ:
		memaddr = (u64)uctxt->subctxt_rcvhdr_base;
		memlen = rcvhdrq_size(uctxt) * uctxt->subctxt_cnt;
		flags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		अवरोध;
	हाल SUBCTXT_EGRBUF:
		memaddr = (u64)uctxt->subctxt_rcvegrbuf;
		memlen = uctxt->egrbufs.size * uctxt->subctxt_cnt;
		flags |= VM_IO | VM_DONTEXPAND;
		flags &= ~VM_MAYWRITE;
		vmf = 1;
		अवरोध;
	हाल SDMA_COMP: अणु
		काष्ठा hfi1_user_sdma_comp_q *cq = fd->cq;

		अगर (!cq) अणु
			ret = -EFAULT;
			जाओ करोne;
		पूर्ण
		memaddr = (u64)cq->comps;
		memlen = PAGE_ALIGN(माप(*cq->comps) * cq->nentries);
		flags |= VM_IO | VM_DONTEXPAND;
		vmf = 1;
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर ((vma->vm_end - vma->vm_start) != memlen) अणु
		hfi1_cdbg(PROC, "%u:%u Memory size mismatch %lu:%lu",
			  uctxt->ctxt, fd->subctxt,
			  (vma->vm_end - vma->vm_start), memlen);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	vma->vm_flags = flags;
	hfi1_cdbg(PROC,
		  "%u:%u type:%u io/vf:%d/%d, addr:0x%llx, len:%lu(%lu), flags:0x%lx\n",
		    ctxt, subctxt, type, mapio, vmf, memaddr, memlen,
		    vma->vm_end - vma->vm_start, vma->vm_flags);
	अगर (vmf) अणु
		vma->vm_pgoff = PFN_DOWN(memaddr);
		vma->vm_ops = &vm_ops;
		ret = 0;
	पूर्ण अन्यथा अगर (mapio) अणु
		ret = io_remap_pfn_range(vma, vma->vm_start,
					 PFN_DOWN(memaddr),
					 memlen,
					 vma->vm_page_prot);
	पूर्ण अन्यथा अगर (memvirt) अणु
		ret = remap_pfn_range(vma, vma->vm_start,
				      PFN_DOWN(__pa(memvirt)),
				      memlen,
				      vma->vm_page_prot);
	पूर्ण अन्यथा अणु
		ret = remap_pfn_range(vma, vma->vm_start,
				      PFN_DOWN(memaddr),
				      memlen,
				      vma->vm_page_prot);
	पूर्ण
करोne:
	वापस ret;
पूर्ण

/*
 * Local (non-chip) user memory is not mapped right away but as it is
 * accessed by the user-level code.
 */
अटल vm_fault_t vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page;

	page = vदो_स्मृति_to_page((व्योम *)(vmf->pgoff << PAGE_SHIFT));
	अगर (!page)
		वापस VM_FAULT_SIGBUS;

	get_page(page);
	vmf->page = page;

	वापस 0;
पूर्ण

अटल __poll_t hfi1_poll(काष्ठा file *fp, काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा hfi1_ctxtdata *uctxt;
	__poll_t pollflag;

	uctxt = ((काष्ठा hfi1_filedata *)fp->निजी_data)->uctxt;
	अगर (!uctxt)
		pollflag = EPOLLERR;
	अन्यथा अगर (uctxt->poll_type == HFI1_POLL_TYPE_URGENT)
		pollflag = poll_urgent(fp, pt);
	अन्यथा  अगर (uctxt->poll_type == HFI1_POLL_TYPE_ANYRCV)
		pollflag = poll_next(fp, pt);
	अन्यथा /* invalid */
		pollflag = EPOLLERR;

	वापस pollflag;
पूर्ण

अटल पूर्णांक hfi1_file_बंद(काष्ठा inode *inode, काष्ठा file *fp)
अणु
	काष्ठा hfi1_filedata *fdata = fp->निजी_data;
	काष्ठा hfi1_ctxtdata *uctxt = fdata->uctxt;
	काष्ठा hfi1_devdata *dd = container_of(inode->i_cdev,
					       काष्ठा hfi1_devdata,
					       user_cdev);
	अचिन्हित दीर्घ flags, *ev;

	fp->निजी_data = शून्य;

	अगर (!uctxt)
		जाओ करोne;

	hfi1_cdbg(PROC, "closing ctxt %u:%u", uctxt->ctxt, fdata->subctxt);

	flush_wc();
	/* drain user sdma queue */
	hfi1_user_sdma_मुक्त_queues(fdata, uctxt);

	/* release the cpu */
	hfi1_put_proc_affinity(fdata->rec_cpu_num);

	/* clean up rcv side */
	hfi1_user_exp_rcv_मुक्त(fdata);

	/*
	 * fdata->uctxt is used in the above cleanup.  It is not पढ़ोy to be
	 * हटाओd until here.
	 */
	fdata->uctxt = शून्य;
	hfi1_rcd_put(uctxt);

	/*
	 * Clear any left over, unhandled events so the next process that
	 * माला_लो this context करोesn't get confused.
	 */
	ev = dd->events + uctxt_offset(uctxt) + fdata->subctxt;
	*ev = 0;

	spin_lock_irqsave(&dd->uctxt_lock, flags);
	__clear_bit(fdata->subctxt, uctxt->in_use_ctxts);
	अगर (!biपंचांगap_empty(uctxt->in_use_ctxts, HFI1_MAX_SHARED_CTXTS)) अणु
		spin_unlock_irqrestore(&dd->uctxt_lock, flags);
		जाओ करोne;
	पूर्ण
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	/*
	 * Disable receive context and पूर्णांकerrupt available, reset all
	 * RcvCtxtCtrl bits to शेष values.
	 */
	hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_DIS |
		     HFI1_RCVCTRL_TIDFLOW_DIS |
		     HFI1_RCVCTRL_INTRAVAIL_DIS |
		     HFI1_RCVCTRL_TAILUPD_DIS |
		     HFI1_RCVCTRL_ONE_PKT_EGR_DIS |
		     HFI1_RCVCTRL_NO_RHQ_DROP_DIS |
		     HFI1_RCVCTRL_NO_EGR_DROP_DIS |
		     HFI1_RCVCTRL_URGENT_DIS, uctxt);
	/* Clear the context's J_KEY */
	hfi1_clear_ctxt_jkey(dd, uctxt);
	/*
	 * If a send context is allocated, reset context पूर्णांकegrity
	 * checks to शेष and disable the send context.
	 */
	अगर (uctxt->sc) अणु
		sc_disable(uctxt->sc);
		set_pio_पूर्णांकegrity(uctxt->sc);
	पूर्ण

	hfi1_मुक्त_ctxt_rcv_groups(uctxt);
	hfi1_clear_ctxt_pkey(dd, uctxt);

	uctxt->event_flags = 0;

	deallocate_ctxt(uctxt);
करोne:

	अगर (atomic_dec_and_test(&dd->user_refcount))
		complete(&dd->user_comp);

	cleanup_srcu_काष्ठा(&fdata->pq_srcu);
	kमुक्त(fdata);
	वापस 0;
पूर्ण

/*
 * Convert kernel *भव* addresses to physical addresses.
 * This is used to vदो_स्मृति'ed addresses.
 */
अटल u64 kvirt_to_phys(व्योम *addr)
अणु
	काष्ठा page *page;
	u64 paddr = 0;

	page = vदो_स्मृति_to_page(addr);
	अगर (page)
		paddr = page_to_pfn(page) << PAGE_SHIFT;

	वापस paddr;
पूर्ण

/**
 * complete_subctxt
 * @fd: valid filedata poपूर्णांकer
 *
 * Sub-context info can only be set up after the base context
 * has been completed.  This is indicated by the clearing of the
 * HFI1_CTXT_BASE_UINIT bit.
 *
 * Wait क्रम the bit to be cleared, and then complete the subcontext
 * initialization.
 *
 */
अटल पूर्णांक complete_subctxt(काष्ठा hfi1_filedata *fd)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	/*
	 * sub-context info can only be set up after the base context
	 * has been completed.
	 */
	ret = रुको_event_पूर्णांकerruptible(
		fd->uctxt->रुको,
		!test_bit(HFI1_CTXT_BASE_UNINIT, &fd->uctxt->event_flags));

	अगर (test_bit(HFI1_CTXT_BASE_FAILED, &fd->uctxt->event_flags))
		ret = -ENOMEM;

	/* Finish the sub-context init */
	अगर (!ret) अणु
		fd->rec_cpu_num = hfi1_get_proc_affinity(fd->uctxt->numa_id);
		ret = init_user_ctxt(fd, fd->uctxt);
	पूर्ण

	अगर (ret) अणु
		spin_lock_irqsave(&fd->dd->uctxt_lock, flags);
		__clear_bit(fd->subctxt, fd->uctxt->in_use_ctxts);
		spin_unlock_irqrestore(&fd->dd->uctxt_lock, flags);
		hfi1_rcd_put(fd->uctxt);
		fd->uctxt = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक assign_ctxt(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg, u32 len)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक swmajor;
	काष्ठा hfi1_ctxtdata *uctxt = शून्य;
	काष्ठा hfi1_user_info uinfo;

	अगर (fd->uctxt)
		वापस -EINVAL;

	अगर (माप(uinfo) != len)
		वापस -EINVAL;

	अगर (copy_from_user(&uinfo, (व्योम __user *)arg, माप(uinfo)))
		वापस -EFAULT;

	swmajor = uinfo.userversion >> 16;
	अगर (swmajor != HFI1_USER_SWMAJOR)
		वापस -ENODEV;

	अगर (uinfo.subctxt_cnt > HFI1_MAX_SHARED_CTXTS)
		वापस -EINVAL;

	/*
	 * Acquire the mutex to protect against multiple creations of what
	 * could be a shared base context.
	 */
	mutex_lock(&hfi1_mutex);
	/*
	 * Get a sub context अगर available  (fd->uctxt will be set).
	 * ret < 0 error, 0 no context, 1 sub-context found
	 */
	ret = find_sub_ctxt(fd, &uinfo);

	/*
	 * Allocate a base context अगर context sharing is not required or a
	 * sub context wasn't found.
	 */
	अगर (!ret)
		ret = allocate_ctxt(fd, fd->dd, &uinfo, &uctxt);

	mutex_unlock(&hfi1_mutex);

	/* Depending on the context type, finish the appropriate init */
	चयन (ret) अणु
	हाल 0:
		ret = setup_base_ctxt(fd, uctxt);
		अगर (ret)
			deallocate_ctxt(uctxt);
		अवरोध;
	हाल 1:
		ret = complete_subctxt(fd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * match_ctxt
 * @fd: valid filedata poपूर्णांकer
 * @uinfo: user info to compare base context with
 * @uctxt: context to compare uinfo to.
 *
 * Compare the given context with the given inक्रमmation to see अगर it
 * can be used क्रम a sub context.
 */
अटल पूर्णांक match_ctxt(काष्ठा hfi1_filedata *fd,
		      स्थिर काष्ठा hfi1_user_info *uinfo,
		      काष्ठा hfi1_ctxtdata *uctxt)
अणु
	काष्ठा hfi1_devdata *dd = fd->dd;
	अचिन्हित दीर्घ flags;
	u16 subctxt;

	/* Skip dynamically allocated kernel contexts */
	अगर (uctxt->sc && (uctxt->sc->type == SC_KERNEL))
		वापस 0;

	/* Skip ctxt अगर it करोesn't match the requested one */
	अगर (स_भेद(uctxt->uuid, uinfo->uuid, माप(uctxt->uuid)) ||
	    uctxt->jkey != generate_jkey(current_uid()) ||
	    uctxt->subctxt_id != uinfo->subctxt_id ||
	    uctxt->subctxt_cnt != uinfo->subctxt_cnt)
		वापस 0;

	/* Verअगरy the sharing process matches the base */
	अगर (uctxt->userversion != uinfo->userversion)
		वापस -EINVAL;

	/* Find an unused sub context */
	spin_lock_irqsave(&dd->uctxt_lock, flags);
	अगर (biपंचांगap_empty(uctxt->in_use_ctxts, HFI1_MAX_SHARED_CTXTS)) अणु
		/* context is being बंदd, करो not use */
		spin_unlock_irqrestore(&dd->uctxt_lock, flags);
		वापस 0;
	पूर्ण

	subctxt = find_first_zero_bit(uctxt->in_use_ctxts,
				      HFI1_MAX_SHARED_CTXTS);
	अगर (subctxt >= uctxt->subctxt_cnt) अणु
		spin_unlock_irqrestore(&dd->uctxt_lock, flags);
		वापस -EBUSY;
	पूर्ण

	fd->subctxt = subctxt;
	__set_bit(fd->subctxt, uctxt->in_use_ctxts);
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	fd->uctxt = uctxt;
	hfi1_rcd_get(uctxt);

	वापस 1;
पूर्ण

/**
 * find_sub_ctxt
 * @fd: valid filedata poपूर्णांकer
 * @uinfo: matching info to use to find a possible context to share.
 *
 * The hfi1_mutex must be held when this function is called.  It is
 * necessary to ensure serialized creation of shared contexts.
 *
 * Return:
 *    0      No sub-context found
 *    1      Subcontext found and allocated
 *    त्रुटि_सं  EINVAL (incorrect parameters)
 *           EBUSY (all sub contexts in use)
 */
अटल पूर्णांक find_sub_ctxt(काष्ठा hfi1_filedata *fd,
			 स्थिर काष्ठा hfi1_user_info *uinfo)
अणु
	काष्ठा hfi1_ctxtdata *uctxt;
	काष्ठा hfi1_devdata *dd = fd->dd;
	u16 i;
	पूर्णांक ret;

	अगर (!uinfo->subctxt_cnt)
		वापस 0;

	क्रम (i = dd->first_dyn_alloc_ctxt; i < dd->num_rcv_contexts; i++) अणु
		uctxt = hfi1_rcd_get_by_index(dd, i);
		अगर (uctxt) अणु
			ret = match_ctxt(fd, uinfo, uctxt);
			hfi1_rcd_put(uctxt);
			/* value of != 0 will वापस */
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक allocate_ctxt(काष्ठा hfi1_filedata *fd, काष्ठा hfi1_devdata *dd,
			 काष्ठा hfi1_user_info *uinfo,
			 काष्ठा hfi1_ctxtdata **rcd)
अणु
	काष्ठा hfi1_ctxtdata *uctxt;
	पूर्णांक ret, numa;

	अगर (dd->flags & HFI1_FROZEN) अणु
		/*
		 * Pick an error that is unique from all other errors
		 * that are वापसed so the user process knows that
		 * it tried to allocate जबतक the SPC was frozen.  It
		 * it should be able to retry with success in a लघु
		 * जबतक.
		 */
		वापस -EIO;
	पूर्ण

	अगर (!dd->मुक्तctxts)
		वापस -EBUSY;

	/*
	 * If we करोn't have a NUMA node requested, preference is towards
	 * device NUMA node.
	 */
	fd->rec_cpu_num = hfi1_get_proc_affinity(dd->node);
	अगर (fd->rec_cpu_num != -1)
		numa = cpu_to_node(fd->rec_cpu_num);
	अन्यथा
		numa = numa_node_id();
	ret = hfi1_create_ctxtdata(dd->pport, numa, &uctxt);
	अगर (ret < 0) अणु
		dd_dev_err(dd, "user ctxtdata allocation failed\n");
		वापस ret;
	पूर्ण
	hfi1_cdbg(PROC, "[%u:%u] pid %u assigned to CPU %d (NUMA %u)",
		  uctxt->ctxt, fd->subctxt, current->pid, fd->rec_cpu_num,
		  uctxt->numa_id);

	/*
	 * Allocate and enable a PIO send context.
	 */
	uctxt->sc = sc_alloc(dd, SC_USER, uctxt->rcvhdrqentsize, dd->node);
	अगर (!uctxt->sc) अणु
		ret = -ENOMEM;
		जाओ ctxdata_मुक्त;
	पूर्ण
	hfi1_cdbg(PROC, "allocated send context %u(%u)\n", uctxt->sc->sw_index,
		  uctxt->sc->hw_context);
	ret = sc_enable(uctxt->sc);
	अगर (ret)
		जाओ ctxdata_मुक्त;

	/*
	 * Setup sub context inक्रमmation अगर the user-level has requested
	 * sub contexts.
	 * This has to be करोne here so the rest of the sub-contexts find the
	 * proper base context.
	 * NOTE: _set_bit() can be used here because the context creation is
	 * रक्षित by the mutex (rather than the spin_lock), and will be the
	 * very first instance of this context.
	 */
	__set_bit(0, uctxt->in_use_ctxts);
	अगर (uinfo->subctxt_cnt)
		init_subctxts(uctxt, uinfo);
	uctxt->userversion = uinfo->userversion;
	uctxt->flags = hfi1_cap_mask; /* save current flag state */
	init_रुकोqueue_head(&uctxt->रुको);
	strlcpy(uctxt->comm, current->comm, माप(uctxt->comm));
	स_नकल(uctxt->uuid, uinfo->uuid, माप(uctxt->uuid));
	uctxt->jkey = generate_jkey(current_uid());
	hfi1_stats.sps_ctxts++;
	/*
	 * Disable ASPM when there are खोलो user/PSM contexts to aव्योम
	 * issues with ASPM L1 निकास latency
	 */
	अगर (dd->मुक्तctxts-- == dd->num_user_contexts)
		aspm_disable_all(dd);

	*rcd = uctxt;

	वापस 0;

ctxdata_मुक्त:
	hfi1_मुक्त_ctxt(uctxt);
	वापस ret;
पूर्ण

अटल व्योम deallocate_ctxt(काष्ठा hfi1_ctxtdata *uctxt)
अणु
	mutex_lock(&hfi1_mutex);
	hfi1_stats.sps_ctxts--;
	अगर (++uctxt->dd->मुक्तctxts == uctxt->dd->num_user_contexts)
		aspm_enable_all(uctxt->dd);
	mutex_unlock(&hfi1_mutex);

	hfi1_मुक्त_ctxt(uctxt);
पूर्ण

अटल व्योम init_subctxts(काष्ठा hfi1_ctxtdata *uctxt,
			  स्थिर काष्ठा hfi1_user_info *uinfo)
अणु
	uctxt->subctxt_cnt = uinfo->subctxt_cnt;
	uctxt->subctxt_id = uinfo->subctxt_id;
	set_bit(HFI1_CTXT_BASE_UNINIT, &uctxt->event_flags);
पूर्ण

अटल पूर्णांक setup_subctxt(काष्ठा hfi1_ctxtdata *uctxt)
अणु
	पूर्णांक ret = 0;
	u16 num_subctxts = uctxt->subctxt_cnt;

	uctxt->subctxt_uregbase = vदो_स्मृति_user(PAGE_SIZE);
	अगर (!uctxt->subctxt_uregbase)
		वापस -ENOMEM;

	/* We can take the size of the RcvHdr Queue from the master */
	uctxt->subctxt_rcvhdr_base = vदो_स्मृति_user(rcvhdrq_size(uctxt) *
						  num_subctxts);
	अगर (!uctxt->subctxt_rcvhdr_base) अणु
		ret = -ENOMEM;
		जाओ bail_ureg;
	पूर्ण

	uctxt->subctxt_rcvegrbuf = vदो_स्मृति_user(uctxt->egrbufs.size *
						num_subctxts);
	अगर (!uctxt->subctxt_rcvegrbuf) अणु
		ret = -ENOMEM;
		जाओ bail_rhdr;
	पूर्ण

	वापस 0;

bail_rhdr:
	vमुक्त(uctxt->subctxt_rcvhdr_base);
	uctxt->subctxt_rcvhdr_base = शून्य;
bail_ureg:
	vमुक्त(uctxt->subctxt_uregbase);
	uctxt->subctxt_uregbase = शून्य;

	वापस ret;
पूर्ण

अटल व्योम user_init(काष्ठा hfi1_ctxtdata *uctxt)
अणु
	अचिन्हित पूर्णांक rcvctrl_ops = 0;

	/* initialize poll variables... */
	uctxt->urgent = 0;
	uctxt->urgent_poll = 0;

	/*
	 * Now enable the ctxt क्रम receive.
	 * For chips that are set to DMA the tail रेजिस्टर to memory
	 * when they change (and when the update bit transitions from
	 * 0 to 1.  So क्रम those chips, we turn it off and then back on.
	 * This will (very briefly) affect any other खोलो ctxts, but the
	 * duration is very लघु, and thereक्रमe isn't an issue.  We
	 * explicitly set the in-memory tail copy to 0 beक्रमehand, so we
	 * करोn't have to रुको to be sure the DMA update has happened
	 * (chip resets head/tail to 0 on transition to enable).
	 */
	अगर (hfi1_rcvhdrtail_kvaddr(uctxt))
		clear_rcvhdrtail(uctxt);

	/* Setup J_KEY beक्रमe enabling the context */
	hfi1_set_ctxt_jkey(uctxt->dd, uctxt, uctxt->jkey);

	rcvctrl_ops = HFI1_RCVCTRL_CTXT_ENB;
	rcvctrl_ops |= HFI1_RCVCTRL_URGENT_ENB;
	अगर (HFI1_CAP_UGET_MASK(uctxt->flags, HDRSUPP))
		rcvctrl_ops |= HFI1_RCVCTRL_TIDFLOW_ENB;
	/*
	 * Ignore the bit in the flags क्रम now until proper
	 * support क्रम multiple packet per rcv array entry is
	 * added.
	 */
	अगर (!HFI1_CAP_UGET_MASK(uctxt->flags, MULTI_PKT_EGR))
		rcvctrl_ops |= HFI1_RCVCTRL_ONE_PKT_EGR_ENB;
	अगर (HFI1_CAP_UGET_MASK(uctxt->flags, NODROP_EGR_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_EGR_DROP_ENB;
	अगर (HFI1_CAP_UGET_MASK(uctxt->flags, NODROP_RHQ_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_RHQ_DROP_ENB;
	/*
	 * The RcvCtxtCtrl.TailUpd bit has to be explicitly written.
	 * We can't rely on the correct value to be set from prior
	 * uses of the chip or ctxt. Thereक्रमe, add the rcvctrl op
	 * क्रम both हालs.
	 */
	अगर (HFI1_CAP_UGET_MASK(uctxt->flags, DMA_RTAIL))
		rcvctrl_ops |= HFI1_RCVCTRL_TAILUPD_ENB;
	अन्यथा
		rcvctrl_ops |= HFI1_RCVCTRL_TAILUPD_DIS;
	hfi1_rcvctrl(uctxt->dd, rcvctrl_ops, uctxt);
पूर्ण

अटल पूर्णांक get_ctxt_info(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg, u32 len)
अणु
	काष्ठा hfi1_ctxt_info cinfo;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;

	अगर (माप(cinfo) != len)
		वापस -EINVAL;

	स_रखो(&cinfo, 0, माप(cinfo));
	cinfo.runसमय_flags = (((uctxt->flags >> HFI1_CAP_MISC_SHIFT) &
				HFI1_CAP_MISC_MASK) << HFI1_CAP_USER_SHIFT) |
			HFI1_CAP_UGET_MASK(uctxt->flags, MASK) |
			HFI1_CAP_KGET_MASK(uctxt->flags, K2U);
	/* adjust flag अगर this fd is not able to cache */
	अगर (!fd->use_mn)
		cinfo.runसमय_flags |= HFI1_CAP_TID_UNMAP; /* no caching */

	cinfo.num_active = hfi1_count_active_units();
	cinfo.unit = uctxt->dd->unit;
	cinfo.ctxt = uctxt->ctxt;
	cinfo.subctxt = fd->subctxt;
	cinfo.rcvtids = roundup(uctxt->egrbufs.alloced,
				uctxt->dd->rcv_entries.group_size) +
		uctxt->expected_count;
	cinfo.credits = uctxt->sc->credits;
	cinfo.numa_node = uctxt->numa_id;
	cinfo.rec_cpu = fd->rec_cpu_num;
	cinfo.send_ctxt = uctxt->sc->hw_context;

	cinfo.egrtids = uctxt->egrbufs.alloced;
	cinfo.rcvhdrq_cnt = get_hdrq_cnt(uctxt);
	cinfo.rcvhdrq_entsize = get_hdrqentsize(uctxt) << 2;
	cinfo.sdma_ring_size = fd->cq->nentries;
	cinfo.rcvegr_size = uctxt->egrbufs.rcvtid_size;

	trace_hfi1_ctxt_info(uctxt->dd, uctxt->ctxt, fd->subctxt, &cinfo);
	अगर (copy_to_user((व्योम __user *)arg, &cinfo, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक init_user_ctxt(काष्ठा hfi1_filedata *fd,
			  काष्ठा hfi1_ctxtdata *uctxt)
अणु
	पूर्णांक ret;

	ret = hfi1_user_sdma_alloc_queues(uctxt, fd);
	अगर (ret)
		वापस ret;

	ret = hfi1_user_exp_rcv_init(fd, uctxt);
	अगर (ret)
		hfi1_user_sdma_मुक्त_queues(fd, uctxt);

	वापस ret;
पूर्ण

अटल पूर्णांक setup_base_ctxt(काष्ठा hfi1_filedata *fd,
			   काष्ठा hfi1_ctxtdata *uctxt)
अणु
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	पूर्णांक ret = 0;

	hfi1_init_ctxt(uctxt->sc);

	/* Now allocate the RcvHdr queue and eager buffers. */
	ret = hfi1_create_rcvhdrq(dd, uctxt);
	अगर (ret)
		जाओ करोne;

	ret = hfi1_setup_eagerbufs(uctxt);
	अगर (ret)
		जाओ करोne;

	/* If sub-contexts are enabled, करो the appropriate setup */
	अगर (uctxt->subctxt_cnt)
		ret = setup_subctxt(uctxt);
	अगर (ret)
		जाओ करोne;

	ret = hfi1_alloc_ctxt_rcv_groups(uctxt);
	अगर (ret)
		जाओ करोne;

	ret = init_user_ctxt(fd, uctxt);
	अगर (ret)
		जाओ करोne;

	user_init(uctxt);

	/* Now that the context is set up, the fd can get a reference. */
	fd->uctxt = uctxt;
	hfi1_rcd_get(uctxt);

करोne:
	अगर (uctxt->subctxt_cnt) अणु
		/*
		 * On error, set the failed bit so sub-contexts will clean up
		 * correctly.
		 */
		अगर (ret)
			set_bit(HFI1_CTXT_BASE_FAILED, &uctxt->event_flags);

		/*
		 * Base context is करोne (successfully or not), notअगरy anybody
		 * using a sub-context that is रुकोing क्रम this completion.
		 */
		clear_bit(HFI1_CTXT_BASE_UNINIT, &uctxt->event_flags);
		wake_up(&uctxt->रुको);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक get_base_info(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg, u32 len)
अणु
	काष्ठा hfi1_base_info binfo;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	अचिन्हित offset;

	trace_hfi1_uctxtdata(uctxt->dd, uctxt, fd->subctxt);

	अगर (माप(binfo) != len)
		वापस -EINVAL;

	स_रखो(&binfo, 0, माप(binfo));
	binfo.hw_version = dd->revision;
	binfo.sw_version = HFI1_KERN_SWVERSION;
	binfo.bthqp = RVT_KDETH_QP_PREFIX;
	binfo.jkey = uctxt->jkey;
	/*
	 * If more than 64 contexts are enabled the allocated credit
	 * वापस will span two or three contiguous pages. Since we only
	 * map the page containing the context's credit वापस address,
	 * we need to calculate the offset in the proper page.
	 */
	offset = ((u64)uctxt->sc->hw_मुक्त -
		  (u64)dd->cr_base[uctxt->numa_id].va) % PAGE_SIZE;
	binfo.sc_credits_addr = HFI1_MMAP_TOKEN(PIO_CRED, uctxt->ctxt,
						fd->subctxt, offset);
	binfo.pio_bufbase = HFI1_MMAP_TOKEN(PIO_BUFS, uctxt->ctxt,
					    fd->subctxt,
					    uctxt->sc->base_addr);
	binfo.pio_bufbase_sop = HFI1_MMAP_TOKEN(PIO_BUFS_SOP,
						uctxt->ctxt,
						fd->subctxt,
						uctxt->sc->base_addr);
	binfo.rcvhdr_bufbase = HFI1_MMAP_TOKEN(RCV_HDRQ, uctxt->ctxt,
					       fd->subctxt,
					       uctxt->rcvhdrq);
	binfo.rcvegr_bufbase = HFI1_MMAP_TOKEN(RCV_EGRBUF, uctxt->ctxt,
					       fd->subctxt,
					       uctxt->egrbufs.rcvtids[0].dma);
	binfo.sdma_comp_bufbase = HFI1_MMAP_TOKEN(SDMA_COMP, uctxt->ctxt,
						  fd->subctxt, 0);
	/*
	 * user regs are at
	 * (RXE_PER_CONTEXT_USER + (ctxt * RXE_PER_CONTEXT_SIZE))
	 */
	binfo.user_regbase = HFI1_MMAP_TOKEN(UREGS, uctxt->ctxt,
					     fd->subctxt, 0);
	offset = offset_in_page((uctxt_offset(uctxt) + fd->subctxt) *
				माप(*dd->events));
	binfo.events_bufbase = HFI1_MMAP_TOKEN(EVENTS, uctxt->ctxt,
					       fd->subctxt,
					       offset);
	binfo.status_bufbase = HFI1_MMAP_TOKEN(STATUS, uctxt->ctxt,
					       fd->subctxt,
					       dd->status);
	अगर (HFI1_CAP_IS_USET(DMA_RTAIL))
		binfo.rcvhdrtail_base = HFI1_MMAP_TOKEN(RTAIL, uctxt->ctxt,
							fd->subctxt, 0);
	अगर (uctxt->subctxt_cnt) अणु
		binfo.subctxt_uregbase = HFI1_MMAP_TOKEN(SUBCTXT_UREGS,
							 uctxt->ctxt,
							 fd->subctxt, 0);
		binfo.subctxt_rcvhdrbuf = HFI1_MMAP_TOKEN(SUBCTXT_RCV_HDRQ,
							  uctxt->ctxt,
							  fd->subctxt, 0);
		binfo.subctxt_rcvegrbuf = HFI1_MMAP_TOKEN(SUBCTXT_EGRBUF,
							  uctxt->ctxt,
							  fd->subctxt, 0);
	पूर्ण

	अगर (copy_to_user((व्योम __user *)arg, &binfo, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 * user_exp_rcv_setup - Set up the given tid rcv list
 * @fd: file data of the current driver instance
 * @arg: ioctl argumnent क्रम user space inक्रमmation
 * @len: length of data काष्ठाure associated with ioctl command
 *
 * Wrapper to validate ioctl inक्रमmation beक्रमe करोing _rcv_setup.
 *
 */
अटल पूर्णांक user_exp_rcv_setup(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg,
			      u32 len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ addr;
	काष्ठा hfi1_tid_info tinfo;

	अगर (माप(tinfo) != len)
		वापस -EINVAL;

	अगर (copy_from_user(&tinfo, (व्योम __user *)arg, (माप(tinfo))))
		वापस -EFAULT;

	ret = hfi1_user_exp_rcv_setup(fd, &tinfo);
	अगर (!ret) अणु
		/*
		 * Copy the number of tidlist entries we used
		 * and the length of the buffer we रेजिस्टरed.
		 */
		addr = arg + दुरत्व(काष्ठा hfi1_tid_info, tidcnt);
		अगर (copy_to_user((व्योम __user *)addr, &tinfo.tidcnt,
				 माप(tinfo.tidcnt)))
			वापस -EFAULT;

		addr = arg + दुरत्व(काष्ठा hfi1_tid_info, length);
		अगर (copy_to_user((व्योम __user *)addr, &tinfo.length,
				 माप(tinfo.length)))
			ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * user_exp_rcv_clear - Clear the given tid rcv list
 * @fd: file data of the current driver instance
 * @arg: ioctl argumnent क्रम user space inक्रमmation
 * @len: length of data काष्ठाure associated with ioctl command
 *
 * The hfi1_user_exp_rcv_clear() can be called from the error path.  Because
 * of this, we need to use this wrapper to copy the user space inक्रमmation
 * beक्रमe करोing the clear.
 */
अटल पूर्णांक user_exp_rcv_clear(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg,
			      u32 len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ addr;
	काष्ठा hfi1_tid_info tinfo;

	अगर (माप(tinfo) != len)
		वापस -EINVAL;

	अगर (copy_from_user(&tinfo, (व्योम __user *)arg, (माप(tinfo))))
		वापस -EFAULT;

	ret = hfi1_user_exp_rcv_clear(fd, &tinfo);
	अगर (!ret) अणु
		addr = arg + दुरत्व(काष्ठा hfi1_tid_info, tidcnt);
		अगर (copy_to_user((व्योम __user *)addr, &tinfo.tidcnt,
				 माप(tinfo.tidcnt)))
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * user_exp_rcv_invalid - Invalidate the given tid rcv list
 * @fd: file data of the current driver instance
 * @arg: ioctl argumnent क्रम user space inक्रमmation
 * @len: length of data काष्ठाure associated with ioctl command
 *
 * Wrapper to validate ioctl inक्रमmation beक्रमe करोing _rcv_invalid.
 *
 */
अटल पूर्णांक user_exp_rcv_invalid(काष्ठा hfi1_filedata *fd, अचिन्हित दीर्घ arg,
				u32 len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ addr;
	काष्ठा hfi1_tid_info tinfo;

	अगर (माप(tinfo) != len)
		वापस -EINVAL;

	अगर (!fd->invalid_tids)
		वापस -EINVAL;

	अगर (copy_from_user(&tinfo, (व्योम __user *)arg, (माप(tinfo))))
		वापस -EFAULT;

	ret = hfi1_user_exp_rcv_invalid(fd, &tinfo);
	अगर (ret)
		वापस ret;

	addr = arg + दुरत्व(काष्ठा hfi1_tid_info, tidcnt);
	अगर (copy_to_user((व्योम __user *)addr, &tinfo.tidcnt,
			 माप(tinfo.tidcnt)))
		ret = -EFAULT;

	वापस ret;
पूर्ण

अटल __poll_t poll_urgent(काष्ठा file *fp,
				काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा hfi1_filedata *fd = fp->निजी_data;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	__poll_t pollflag;

	poll_रुको(fp, &uctxt->रुको, pt);

	spin_lock_irq(&dd->uctxt_lock);
	अगर (uctxt->urgent != uctxt->urgent_poll) अणु
		pollflag = EPOLLIN | EPOLLRDNORM;
		uctxt->urgent_poll = uctxt->urgent;
	पूर्ण अन्यथा अणु
		pollflag = 0;
		set_bit(HFI1_CTXT_WAITING_URG, &uctxt->event_flags);
	पूर्ण
	spin_unlock_irq(&dd->uctxt_lock);

	वापस pollflag;
पूर्ण

अटल __poll_t poll_next(काष्ठा file *fp,
			      काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा hfi1_filedata *fd = fp->निजी_data;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	__poll_t pollflag;

	poll_रुको(fp, &uctxt->रुको, pt);

	spin_lock_irq(&dd->uctxt_lock);
	अगर (hdrqempty(uctxt)) अणु
		set_bit(HFI1_CTXT_WAITING_RCV, &uctxt->event_flags);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_INTRAVAIL_ENB, uctxt);
		pollflag = 0;
	पूर्ण अन्यथा अणु
		pollflag = EPOLLIN | EPOLLRDNORM;
	पूर्ण
	spin_unlock_irq(&dd->uctxt_lock);

	वापस pollflag;
पूर्ण

/*
 * Find all user contexts in use, and set the specअगरied bit in their
 * event mask.
 * See also find_ctxt() क्रम a similar use, that is specअगरic to send buffers.
 */
पूर्णांक hfi1_set_uevent_bits(काष्ठा hfi1_pportdata *ppd, स्थिर पूर्णांक evtbit)
अणु
	काष्ठा hfi1_ctxtdata *uctxt;
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u16 ctxt;

	अगर (!dd->events)
		वापस -EINVAL;

	क्रम (ctxt = dd->first_dyn_alloc_ctxt; ctxt < dd->num_rcv_contexts;
	     ctxt++) अणु
		uctxt = hfi1_rcd_get_by_index(dd, ctxt);
		अगर (uctxt) अणु
			अचिन्हित दीर्घ *evs;
			पूर्णांक i;
			/*
			 * subctxt_cnt is 0 अगर not shared, so करो base
			 * separately, first, then reमुख्यing subctxt, अगर any
			 */
			evs = dd->events + uctxt_offset(uctxt);
			set_bit(evtbit, evs);
			क्रम (i = 1; i < uctxt->subctxt_cnt; i++)
				set_bit(evtbit, evs + i);
			hfi1_rcd_put(uctxt);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * manage_rcvq - manage a context's receive queue
 * @uctxt: the context
 * @subctxt: the sub-context
 * @arg: start/stop action to carry out
 *
 * start_stop == 0 disables receive on the context, क्रम use in queue
 * overflow conditions.  start_stop==1 re-enables, to be used to
 * re-init the software copy of the head रेजिस्टर
 */
अटल पूर्णांक manage_rcvq(काष्ठा hfi1_ctxtdata *uctxt, u16 subctxt,
		       अचिन्हित दीर्घ arg)
अणु
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	अचिन्हित पूर्णांक rcvctrl_op;
	पूर्णांक start_stop;

	अगर (subctxt)
		वापस 0;

	अगर (get_user(start_stop, (पूर्णांक __user *)arg))
		वापस -EFAULT;

	/* atomically clear receive enable ctxt. */
	अगर (start_stop) अणु
		/*
		 * On enable, क्रमce in-memory copy of the tail रेजिस्टर to
		 * 0, so that protocol code करोesn't have to worry about
		 * whether or not the chip has yet updated the in-memory
		 * copy or not on वापस from the प्रणाली call. The chip
		 * always resets it's tail रेजिस्टर back to 0 on a
		 * transition from disabled to enabled.
		 */
		अगर (hfi1_rcvhdrtail_kvaddr(uctxt))
			clear_rcvhdrtail(uctxt);
		rcvctrl_op = HFI1_RCVCTRL_CTXT_ENB;
	पूर्ण अन्यथा अणु
		rcvctrl_op = HFI1_RCVCTRL_CTXT_DIS;
	पूर्ण
	hfi1_rcvctrl(dd, rcvctrl_op, uctxt);
	/* always; new head should be equal to new tail; see above */

	वापस 0;
पूर्ण

/*
 * clear the event notअगरier events क्रम this context.
 * User process then perक्रमms actions appropriate to bit having been
 * set, अगर desired, and checks again in future.
 */
अटल पूर्णांक user_event_ack(काष्ठा hfi1_ctxtdata *uctxt, u16 subctxt,
			  अचिन्हित दीर्घ arg)
अणु
	पूर्णांक i;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	अचिन्हित दीर्घ *evs;
	अचिन्हित दीर्घ events;

	अगर (!dd->events)
		वापस 0;

	अगर (get_user(events, (अचिन्हित दीर्घ __user *)arg))
		वापस -EFAULT;

	evs = dd->events + uctxt_offset(uctxt) + subctxt;

	क्रम (i = 0; i <= _HFI1_MAX_EVENT_BIT; i++) अणु
		अगर (!test_bit(i, &events))
			जारी;
		clear_bit(i, evs);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_ctxt_pkey(काष्ठा hfi1_ctxtdata *uctxt, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक i;
	काष्ठा hfi1_pportdata *ppd = uctxt->ppd;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	u16 pkey;

	अगर (!HFI1_CAP_IS_USET(PKEY_CHECK))
		वापस -EPERM;

	अगर (get_user(pkey, (u16 __user *)arg))
		वापस -EFAULT;

	अगर (pkey == LIM_MGMT_P_KEY || pkey == FULL_MGMT_P_KEY)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++)
		अगर (pkey == ppd->pkeys[i])
			वापस hfi1_set_ctxt_pkey(dd, uctxt, pkey);

	वापस -ENOENT;
पूर्ण

/**
 * ctxt_reset - Reset the user context
 * @uctxt: valid user context
 */
अटल पूर्णांक ctxt_reset(काष्ठा hfi1_ctxtdata *uctxt)
अणु
	काष्ठा send_context *sc;
	काष्ठा hfi1_devdata *dd;
	पूर्णांक ret = 0;

	अगर (!uctxt || !uctxt->dd || !uctxt->sc)
		वापस -EINVAL;

	/*
	 * There is no protection here. User level has to guarantee that
	 * no one will be writing to the send context जबतक it is being
	 * re-initialized.  If user level अवरोधs that guarantee, it will
	 * अवरोध it's own context and no one else's.
	 */
	dd = uctxt->dd;
	sc = uctxt->sc;

	/*
	 * Wait until the पूर्णांकerrupt handler has marked the context as
	 * halted or frozen. Report error अगर we समय out.
	 */
	रुको_event_पूर्णांकerruptible_समयout(
		sc->halt_रुको, (sc->flags & SCF_HALTED),
		msecs_to_jअगरfies(SEND_CTXT_HALT_TIMEOUT));
	अगर (!(sc->flags & SCF_HALTED))
		वापस -ENOLCK;

	/*
	 * If the send context was halted due to a Freeze, रुको until the
	 * device has been "unfrozen" beक्रमe resetting the context.
	 */
	अगर (sc->flags & SCF_FROZEN) अणु
		रुको_event_पूर्णांकerruptible_समयout(
			dd->event_queue,
			!(READ_ONCE(dd->flags) & HFI1_FROZEN),
			msecs_to_jअगरfies(SEND_CTXT_HALT_TIMEOUT));
		अगर (dd->flags & HFI1_FROZEN)
			वापस -ENOLCK;

		अगर (dd->flags & HFI1_FORCED_FREEZE)
			/*
			 * Don't allow context reset अगर we are पूर्णांकo
			 * क्रमced मुक्तze
			 */
			वापस -ENODEV;

		sc_disable(sc);
		ret = sc_enable(sc);
		hfi1_rcvctrl(dd, HFI1_RCVCTRL_CTXT_ENB, uctxt);
	पूर्ण अन्यथा अणु
		ret = sc_restart(sc);
	पूर्ण
	अगर (!ret)
		sc_वापस_credits(sc);

	वापस ret;
पूर्ण

अटल व्योम user_हटाओ(काष्ठा hfi1_devdata *dd)
अणु

	hfi1_cdev_cleanup(&dd->user_cdev, &dd->user_device);
पूर्ण

अटल पूर्णांक user_add(काष्ठा hfi1_devdata *dd)
अणु
	अक्षर name[10];
	पूर्णांक ret;

	snम_लिखो(name, माप(name), "%s_%d", class_name(), dd->unit);
	ret = hfi1_cdev_init(dd->unit, name, &hfi1_file_ops,
			     &dd->user_cdev, &dd->user_device,
			     true, &dd->verbs_dev.rdi.ibdev.dev.kobj);
	अगर (ret)
		user_हटाओ(dd);

	वापस ret;
पूर्ण

/*
 * Create per-unit files in /dev
 */
पूर्णांक hfi1_device_create(काष्ठा hfi1_devdata *dd)
अणु
	वापस user_add(dd);
पूर्ण

/*
 * Remove per-unit files in /dev
 * व्योम, core kernel वापसs no errors क्रम this stuff
 */
व्योम hfi1_device_हटाओ(काष्ठा hfi1_devdata *dd)
अणु
	user_हटाओ(dd);
पूर्ण
