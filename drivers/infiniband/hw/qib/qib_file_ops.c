<शैली गुरु>
/*
 * Copyright (c) 2012, 2013 Intel Corporation. All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
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
 */

#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/cdev.h>
#समावेश <linux/swap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/uपन.स>
#समावेश <linux/pgtable.h>

#समावेश <rdma/ib.h>

#समावेश "qib.h"
#समावेश "qib_common.h"
#समावेश "qib_user_sdma.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) QIB_DRV_NAME ": " fmt

अटल पूर्णांक qib_खोलो(काष्ठा inode *, काष्ठा file *);
अटल पूर्णांक qib_बंद(काष्ठा inode *, काष्ठा file *);
अटल sमाप_प्रकार qib_ग_लिखो(काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
अटल sमाप_प्रकार qib_ग_लिखो_iter(काष्ठा kiocb *, काष्ठा iov_iter *);
अटल __poll_t qib_poll(काष्ठा file *, काष्ठा poll_table_काष्ठा *);
अटल पूर्णांक qib_mmapf(काष्ठा file *, काष्ठा vm_area_काष्ठा *);

/*
 * This is really, really weird shit - ग_लिखो() and ग_लिखोv() here
 * have completely unrelated semantics.  Sucky userland ABI,
 * film at 11.
 */
अटल स्थिर काष्ठा file_operations qib_file_ops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = qib_ग_लिखो,
	.ग_लिखो_iter = qib_ग_लिखो_iter,
	.खोलो = qib_खोलो,
	.release = qib_बंद,
	.poll = qib_poll,
	.mmap = qib_mmapf,
	.llseek = noop_llseek,
पूर्ण;

/*
 * Convert kernel भव addresses to physical addresses so they करोn't
 * potentially conflict with the chip addresses used as mmap offsets.
 * It करोesn't really matter what mmap offset we use as दीर्घ as we can
 * पूर्णांकerpret it correctly.
 */
अटल u64 cvt_kvaddr(व्योम *p)
अणु
	काष्ठा page *page;
	u64 paddr = 0;

	page = vदो_स्मृति_to_page(p);
	अगर (page)
		paddr = page_to_pfn(page) << PAGE_SHIFT;

	वापस paddr;
पूर्ण

अटल पूर्णांक qib_get_base_info(काष्ठा file *fp, व्योम __user *ubase,
			     माप_प्रकार ubase_size)
अणु
	काष्ठा qib_ctxtdata *rcd = ctxt_fp(fp);
	पूर्णांक ret = 0;
	काष्ठा qib_base_info *kinfo = शून्य;
	काष्ठा qib_devdata *dd = rcd->dd;
	काष्ठा qib_pportdata *ppd = rcd->ppd;
	अचिन्हित subctxt_cnt;
	पूर्णांक shared, master;
	माप_प्रकार sz;

	subctxt_cnt = rcd->subctxt_cnt;
	अगर (!subctxt_cnt) अणु
		shared = 0;
		master = 0;
		subctxt_cnt = 1;
	पूर्ण अन्यथा अणु
		shared = 1;
		master = !subctxt_fp(fp);
	पूर्ण

	sz = माप(*kinfo);
	/* If context sharing is not requested, allow the old size काष्ठाure */
	अगर (!shared)
		sz -= 7 * माप(u64);
	अगर (ubase_size < sz) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	kinfo = kzalloc(माप(*kinfo), GFP_KERNEL);
	अगर (kinfo == शून्य) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	ret = dd->f_get_base_info(rcd, kinfo);
	अगर (ret < 0)
		जाओ bail;

	kinfo->spi_rcvhdr_cnt = dd->rcvhdrcnt;
	kinfo->spi_rcvhdrent_size = dd->rcvhdrentsize;
	kinfo->spi_tidegrcnt = rcd->rcvegrcnt;
	kinfo->spi_rcv_egrbufsize = dd->rcvegrbufsize;
	/*
	 * have to mmap whole thing
	 */
	kinfo->spi_rcv_egrbuftotlen =
		rcd->rcvegrbuf_chunks * rcd->rcvegrbuf_size;
	kinfo->spi_rcv_egrperchunk = rcd->rcvegrbufs_perchunk;
	kinfo->spi_rcv_egrchunksize = kinfo->spi_rcv_egrbuftotlen /
		rcd->rcvegrbuf_chunks;
	kinfo->spi_tidcnt = dd->rcvtidcnt / subctxt_cnt;
	अगर (master)
		kinfo->spi_tidcnt += dd->rcvtidcnt % subctxt_cnt;
	/*
	 * क्रम this use, may be cfgctxts summed over all chips that
	 * are are configured and present
	 */
	kinfo->spi_nctxts = dd->cfgctxts;
	/* unit (chip/board) our context is on */
	kinfo->spi_unit = dd->unit;
	kinfo->spi_port = ppd->port;
	/* क्रम now, only a single page */
	kinfo->spi_tid_maxsize = PAGE_SIZE;

	/*
	 * Doing this per context, and based on the skip value, etc.  This has
	 * to be the actual buffer size, since the protocol code treats it
	 * as an array.
	 *
	 * These have to be set to user addresses in the user code via mmap.
	 * These values are used on वापस to user code क्रम the mmap target
	 * addresses only.  For 32 bit, same 44 bit address problem, so use
	 * the physical address, not भव.  Beक्रमe 2.6.11, using the
	 * page_address() macro worked, but in 2.6.11, even that वापसs the
	 * full 64 bit address (upper bits all 1's).  So far, using the
	 * physical addresses (or chip offsets, क्रम chip mapping) works, but
	 * no करोubt some future kernel release will change that, and we'll be
	 * on to yet another method of dealing with this.
	 * Normally only one of rcvhdr_tailaddr or rhf_offset is useful
	 * since the chips with non-zero rhf_offset करोn't normally
	 * enable tail रेजिस्टर updates to host memory, but क्रम testing,
	 * both can be enabled and used.
	 */
	kinfo->spi_rcvhdr_base = (u64) rcd->rcvhdrq_phys;
	kinfo->spi_rcvhdr_tailaddr = (u64) rcd->rcvhdrqtailaddr_phys;
	kinfo->spi_rhf_offset = dd->rhf_offset;
	kinfo->spi_rcv_egrbufs = (u64) rcd->rcvegr_phys;
	kinfo->spi_pioavailaddr = (u64) dd->pioavailregs_phys;
	/* setup per-unit (not port) status area क्रम user programs */
	kinfo->spi_status = (u64) kinfo->spi_pioavailaddr +
		(अक्षर *) ppd->statusp -
		(अक्षर *) dd->pioavailregs_dma;
	kinfo->spi_uregbase = (u64) dd->uregbase + dd->ureg_align * rcd->ctxt;
	अगर (!shared) अणु
		kinfo->spi_piocnt = rcd->piocnt;
		kinfo->spi_piobufbase = (u64) rcd->piobufs;
		kinfo->spi_sendbuf_status = cvt_kvaddr(rcd->user_event_mask);
	पूर्ण अन्यथा अगर (master) अणु
		kinfo->spi_piocnt = (rcd->piocnt / subctxt_cnt) +
				    (rcd->piocnt % subctxt_cnt);
		/* Master's PIO buffers are after all the slave's */
		kinfo->spi_piobufbase = (u64) rcd->piobufs +
			dd->palign *
			(rcd->piocnt - kinfo->spi_piocnt);
	पूर्ण अन्यथा अणु
		अचिन्हित slave = subctxt_fp(fp) - 1;

		kinfo->spi_piocnt = rcd->piocnt / subctxt_cnt;
		kinfo->spi_piobufbase = (u64) rcd->piobufs +
			dd->palign * kinfo->spi_piocnt * slave;
	पूर्ण

	अगर (shared) अणु
		kinfo->spi_sendbuf_status =
			cvt_kvaddr(&rcd->user_event_mask[subctxt_fp(fp)]);
		/* only spi_subctxt_* fields should be set in this block! */
		kinfo->spi_subctxt_uregbase = cvt_kvaddr(rcd->subctxt_uregbase);

		kinfo->spi_subctxt_rcvegrbuf =
			cvt_kvaddr(rcd->subctxt_rcvegrbuf);
		kinfo->spi_subctxt_rcvhdr_base =
			cvt_kvaddr(rcd->subctxt_rcvhdr_base);
	पूर्ण

	/*
	 * All user buffers are 2KB buffers.  If we ever support
	 * giving 4KB buffers to user processes, this will need some
	 * work.  Can't use piobufbase directly, because it has
	 * both 2K and 4K buffer base values.
	 */
	kinfo->spi_pioindex = (kinfo->spi_piobufbase - dd->pio2k_bufbase) /
		dd->palign;
	kinfo->spi_pioalign = dd->palign;
	kinfo->spi_qpair = QIB_KD_QP;
	/*
	 * user mode PIO buffers are always 2KB, even when 4KB can
	 * be received, and sent via the kernel; this is ibmaxlen
	 * क्रम 2K MTU.
	 */
	kinfo->spi_piosize = dd->piosize2k - 2 * माप(u32);
	kinfo->spi_mtu = ppd->ibmaxlen; /* maxlen, not ibmtu */
	kinfo->spi_ctxt = rcd->ctxt;
	kinfo->spi_subctxt = subctxt_fp(fp);
	kinfo->spi_sw_version = QIB_KERN_SWVERSION;
	kinfo->spi_sw_version |= 1U << 31; /* QLogic-built, not kernel.org */
	kinfo->spi_hw_version = dd->revision;

	अगर (master)
		kinfo->spi_runसमय_flags |= QIB_RUNTIME_MASTER;

	sz = (ubase_size < माप(*kinfo)) ? ubase_size : माप(*kinfo);
	अगर (copy_to_user(ubase, kinfo, sz))
		ret = -EFAULT;
bail:
	kमुक्त(kinfo);
	वापस ret;
पूर्ण

/**
 * qib_tid_update - update a context TID
 * @rcd: the context
 * @fp: the qib device file
 * @ti: the TID inक्रमmation
 *
 * The new implementation as of Oct 2004 is that the driver assigns
 * the tid and वापसs it to the caller.   To reduce search समय, we
 * keep a cursor क्रम each context, walking the shaकरोw tid array to find
 * one that's not in use.
 *
 * For now, अगर we can't allocate the full list, we fail, although
 * in the दीर्घ run, we'll allocate as many as we can, and the
 * caller will deal with that by trying the reमुख्यing pages later.
 * That means that when we fail, we have to mark the tids as not in
 * use again, in our shaकरोw copy.
 *
 * It's up to the caller to मुक्त the tids when they are करोne.
 * We'll unlock the pages as they मुक्त them.
 *
 * Also, right now we are locking one page at a समय, but since
 * the पूर्णांकended use of this routine is क्रम a single group of
 * भवly contiguous pages, that should change to improve
 * perक्रमmance.
 */
अटल पूर्णांक qib_tid_update(काष्ठा qib_ctxtdata *rcd, काष्ठा file *fp,
			  स्थिर काष्ठा qib_tid_info *ti)
अणु
	पूर्णांक ret = 0, ntids;
	u32 tid, ctxttid, cnt, i, tidcnt, tiकरोff;
	u16 *tidlist;
	काष्ठा qib_devdata *dd = rcd->dd;
	u64 physaddr;
	अचिन्हित दीर्घ vaddr;
	u64 __iomem *tidbase;
	अचिन्हित दीर्घ tidmap[8];
	काष्ठा page **pagep = शून्य;
	अचिन्हित subctxt = subctxt_fp(fp);

	अगर (!dd->pageshaकरोw) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	cnt = ti->tidcnt;
	अगर (!cnt) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण
	ctxttid = rcd->ctxt * dd->rcvtidcnt;
	अगर (!rcd->subctxt_cnt) अणु
		tidcnt = dd->rcvtidcnt;
		tid = rcd->tidcursor;
		tiकरोff = 0;
	पूर्ण अन्यथा अगर (!subctxt) अणु
		tidcnt = (dd->rcvtidcnt / rcd->subctxt_cnt) +
			 (dd->rcvtidcnt % rcd->subctxt_cnt);
		tiकरोff = dd->rcvtidcnt - tidcnt;
		ctxttid += tiकरोff;
		tid = tidcursor_fp(fp);
	पूर्ण अन्यथा अणु
		tidcnt = dd->rcvtidcnt / rcd->subctxt_cnt;
		tiकरोff = tidcnt * (subctxt - 1);
		ctxttid += tiकरोff;
		tid = tidcursor_fp(fp);
	पूर्ण
	अगर (cnt > tidcnt) अणु
		/* make sure it all fits in tid_pg_list */
		qib_devinfo(dd->pcidev,
			"Process tried to allocate %u TIDs, only trying max (%u)\n",
			cnt, tidcnt);
		cnt = tidcnt;
	पूर्ण
	pagep = (काष्ठा page **) rcd->tid_pg_list;
	tidlist = (u16 *) &pagep[dd->rcvtidcnt];
	pagep += tiकरोff;
	tidlist += tiकरोff;

	स_रखो(tidmap, 0, माप(tidmap));
	/* beक्रमe decrement; chip actual # */
	ntids = tidcnt;
	tidbase = (u64 __iomem *) (((अक्षर __iomem *) dd->kregbase) +
				   dd->rcvtidbase +
				   ctxttid * माप(*tidbase));

	/* भव address of first page in transfer */
	vaddr = ti->tidvaddr;
	अगर (!access_ok((व्योम __user *) vaddr,
		       cnt * PAGE_SIZE)) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण
	ret = qib_get_user_pages(vaddr, cnt, pagep);
	अगर (ret) अणु
		/*
		 * अगर (ret == -EBUSY)
		 * We can't continue because the pagep array won't be
		 * initialized. This should never happen,
		 * unless perhaps the user has mpin'ed the pages
		 * themselves.
		 */
		qib_devinfo(
			dd->pcidev,
			"Failed to lock addr %p, %u pages: errno %d\n",
			(व्योम *) vaddr, cnt, -ret);
		जाओ करोne;
	पूर्ण
	क्रम (i = 0; i < cnt; i++, vaddr += PAGE_SIZE) अणु
		dma_addr_t daddr;

		क्रम (; ntids--; tid++) अणु
			अगर (tid == tidcnt)
				tid = 0;
			अगर (!dd->pageshaकरोw[ctxttid + tid])
				अवरोध;
		पूर्ण
		अगर (ntids < 0) अणु
			/*
			 * Oops, wrapped all the way through their TIDs,
			 * and didn't have enough मुक्त; see comments at
			 * start of routine
			 */
			i--;    /* last tidlist[i] not filled in */
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		ret = qib_map_page(dd->pcidev, pagep[i], &daddr);
		अगर (ret)
			अवरोध;

		tidlist[i] = tid + tiकरोff;
		/* we "know" प्रणाली pages and TID pages are same size */
		dd->pageshaकरोw[ctxttid + tid] = pagep[i];
		dd->physshaकरोw[ctxttid + tid] = daddr;
		/*
		 * करोn't need atomic or it's overhead
		 */
		__set_bit(tid, tidmap);
		physaddr = dd->physshaकरोw[ctxttid + tid];
		/* PERFORMANCE: below should almost certainly be cached */
		dd->f_put_tid(dd, &tidbase[tid],
				  RCVHQ_RCV_TYPE_EXPECTED, physaddr);
		/*
		 * करोn't check this tid in qib_ctxtshaकरोw, since we
		 * just filled it in; start with the next one.
		 */
		tid++;
	पूर्ण

	अगर (ret) अणु
		u32 limit;
cleanup:
		/* jump here अगर copy out of updated info failed... */
		/* same code that's in qib_मुक्त_tid() */
		limit = माप(tidmap) * BITS_PER_BYTE;
		अगर (limit > tidcnt)
			/* just in हाल size changes in future */
			limit = tidcnt;
		tid = find_first_bit((स्थिर अचिन्हित दीर्घ *)tidmap, limit);
		क्रम (; tid < limit; tid++) अणु
			अगर (!test_bit(tid, tidmap))
				जारी;
			अगर (dd->pageshaकरोw[ctxttid + tid]) अणु
				dma_addr_t phys;

				phys = dd->physshaकरोw[ctxttid + tid];
				dd->physshaकरोw[ctxttid + tid] = dd->tidinvalid;
				/* PERFORMANCE: below should almost certainly
				 * be cached
				 */
				dd->f_put_tid(dd, &tidbase[tid],
					      RCVHQ_RCV_TYPE_EXPECTED,
					      dd->tidinvalid);
				pci_unmap_page(dd->pcidev, phys, PAGE_SIZE,
					       PCI_DMA_FROMDEVICE);
				dd->pageshaकरोw[ctxttid + tid] = शून्य;
			पूर्ण
		पूर्ण
		qib_release_user_pages(pagep, cnt);
	पूर्ण अन्यथा अणु
		/*
		 * Copy the updated array, with qib_tid's filled in, back
		 * to user.  Since we did the copy in alपढ़ोy, this "should
		 * never fail" If it करोes, we have to clean up...
		 */
		अगर (copy_to_user((व्योम __user *)
				 (अचिन्हित दीर्घ) ti->tidlist,
				 tidlist, cnt * माप(*tidlist))) अणु
			ret = -EFAULT;
			जाओ cleanup;
		पूर्ण
		अगर (copy_to_user(u64_to_user_ptr(ti->tidmap),
				 tidmap, माप(tidmap))) अणु
			ret = -EFAULT;
			जाओ cleanup;
		पूर्ण
		अगर (tid == tidcnt)
			tid = 0;
		अगर (!rcd->subctxt_cnt)
			rcd->tidcursor = tid;
		अन्यथा
			tidcursor_fp(fp) = tid;
	पूर्ण

करोne:
	वापस ret;
पूर्ण

/**
 * qib_tid_मुक्त - मुक्त a context TID
 * @rcd: the context
 * @subctxt: the subcontext
 * @ti: the TID info
 *
 * right now we are unlocking one page at a समय, but since
 * the पूर्णांकended use of this routine is क्रम a single group of
 * भवly contiguous pages, that should change to improve
 * perक्रमmance.  We check that the TID is in range क्रम this context
 * but otherwise करोn't check validity; अगर user has an error and
 * मुक्तs the wrong tid, it's only their own data that can thereby
 * be corrupted.  We करो check that the TID was in use, क्रम sanity
 * We always use our idea of the saved address, not the address that
 * they pass in to us.
 */
अटल पूर्णांक qib_tid_मुक्त(काष्ठा qib_ctxtdata *rcd, अचिन्हित subctxt,
			स्थिर काष्ठा qib_tid_info *ti)
अणु
	पूर्णांक ret = 0;
	u32 tid, ctxttid, cnt, limit, tidcnt;
	काष्ठा qib_devdata *dd = rcd->dd;
	u64 __iomem *tidbase;
	अचिन्हित दीर्घ tidmap[8];

	अगर (!dd->pageshaकरोw) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	अगर (copy_from_user(tidmap, u64_to_user_ptr(ti->tidmap),
			   माप(tidmap))) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण

	ctxttid = rcd->ctxt * dd->rcvtidcnt;
	अगर (!rcd->subctxt_cnt)
		tidcnt = dd->rcvtidcnt;
	अन्यथा अगर (!subctxt) अणु
		tidcnt = (dd->rcvtidcnt / rcd->subctxt_cnt) +
			 (dd->rcvtidcnt % rcd->subctxt_cnt);
		ctxttid += dd->rcvtidcnt - tidcnt;
	पूर्ण अन्यथा अणु
		tidcnt = dd->rcvtidcnt / rcd->subctxt_cnt;
		ctxttid += tidcnt * (subctxt - 1);
	पूर्ण
	tidbase = (u64 __iomem *) ((अक्षर __iomem *)(dd->kregbase) +
				   dd->rcvtidbase +
				   ctxttid * माप(*tidbase));

	limit = माप(tidmap) * BITS_PER_BYTE;
	अगर (limit > tidcnt)
		/* just in हाल size changes in future */
		limit = tidcnt;
	tid = find_first_bit(tidmap, limit);
	क्रम (cnt = 0; tid < limit; tid++) अणु
		/*
		 * small optimization; अगर we detect a run of 3 or so without
		 * any set, use find_first_bit again.  That's मुख्यly to
		 * accelerate the हाल where we wrapped, so we have some at
		 * the beginning, and some at the end, and a big gap
		 * in the middle.
		 */
		अगर (!test_bit(tid, tidmap))
			जारी;
		cnt++;
		अगर (dd->pageshaकरोw[ctxttid + tid]) अणु
			काष्ठा page *p;
			dma_addr_t phys;

			p = dd->pageshaकरोw[ctxttid + tid];
			dd->pageshaकरोw[ctxttid + tid] = शून्य;
			phys = dd->physshaकरोw[ctxttid + tid];
			dd->physshaकरोw[ctxttid + tid] = dd->tidinvalid;
			/* PERFORMANCE: below should almost certainly be
			 * cached
			 */
			dd->f_put_tid(dd, &tidbase[tid],
				      RCVHQ_RCV_TYPE_EXPECTED, dd->tidinvalid);
			pci_unmap_page(dd->pcidev, phys, PAGE_SIZE,
				       PCI_DMA_FROMDEVICE);
			qib_release_user_pages(&p, 1);
		पूर्ण
	पूर्ण
करोne:
	वापस ret;
पूर्ण

/**
 * qib_set_part_key - set a partition key
 * @rcd: the context
 * @key: the key
 *
 * We can have up to 4 active at a समय (other than the शेष, which is
 * always allowed).  This is somewhat tricky, since multiple contexts may set
 * the same key, so we reference count them, and clean up at निकास.  All 4
 * partition keys are packed पूर्णांकo a single qlogic_ib रेजिस्टर.  It's an
 * error क्रम a process to set the same pkey multiple बार.  We provide no
 * mechanism to de-allocate a pkey at this समय, we may eventually need to
 * करो that.  I've used the atomic operations, and no locking, and only make
 * a single pass through what's available.  This should be more than
 * adequate क्रम some समय. I'll think about spinlocks or the like अगर and as
 * it's necessary.
 */
अटल पूर्णांक qib_set_part_key(काष्ठा qib_ctxtdata *rcd, u16 key)
अणु
	काष्ठा qib_pportdata *ppd = rcd->ppd;
	पूर्णांक i, pidx = -1;
	bool any = false;
	u16 lkey = key & 0x7FFF;

	अगर (lkey == (QIB_DEFAULT_P_KEY & 0x7FFF))
		/* nothing to करो; this key always valid */
		वापस 0;

	अगर (!lkey)
		वापस -EINVAL;

	/*
	 * Set the full membership bit, because it has to be
	 * set in the रेजिस्टर or the packet, and it seems
	 * cleaner to set in the रेजिस्टर than to क्रमce all
	 * callers to set it.
	 */
	key |= 0x8000;

	क्रम (i = 0; i < ARRAY_SIZE(rcd->pkeys); i++) अणु
		अगर (!rcd->pkeys[i] && pidx == -1)
			pidx = i;
		अगर (rcd->pkeys[i] == key)
			वापस -EEXIST;
	पूर्ण
	अगर (pidx == -1)
		वापस -EBUSY;
	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) अणु
		अगर (!ppd->pkeys[i]) अणु
			any = true;
			जारी;
		पूर्ण
		अगर (ppd->pkeys[i] == key) अणु
			atomic_t *pkrefs = &ppd->pkeyrefs[i];

			अगर (atomic_inc_वापस(pkrefs) > 1) अणु
				rcd->pkeys[pidx] = key;
				वापस 0;
			पूर्ण
			/*
			 * lost race, decrement count, catch below
			 */
			atomic_dec(pkrefs);
			any = true;
		पूर्ण
		अगर ((ppd->pkeys[i] & 0x7FFF) == lkey)
			/*
			 * It makes no sense to have both the limited and
			 * full membership PKEY set at the same समय since
			 * the unlimited one will disable the limited one.
			 */
			वापस -EEXIST;
	पूर्ण
	अगर (!any)
		वापस -EBUSY;
	क्रम (i = 0; i < ARRAY_SIZE(ppd->pkeys); i++) अणु
		अगर (!ppd->pkeys[i] &&
		    atomic_inc_वापस(&ppd->pkeyrefs[i]) == 1) अणु
			rcd->pkeys[pidx] = key;
			ppd->pkeys[i] = key;
			(व्योम) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PKEYS, 0);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EBUSY;
पूर्ण

/**
 * qib_manage_rcvq - manage a context's receive queue
 * @rcd: the context
 * @subctxt: the subcontext
 * @start_stop: action to carry out
 *
 * start_stop == 0 disables receive on the context, क्रम use in queue
 * overflow conditions.  start_stop==1 re-enables, to be used to
 * re-init the software copy of the head रेजिस्टर
 */
अटल पूर्णांक qib_manage_rcvq(काष्ठा qib_ctxtdata *rcd, अचिन्हित subctxt,
			   पूर्णांक start_stop)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	अचिन्हित पूर्णांक rcvctrl_op;

	अगर (subctxt)
		जाओ bail;
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
		अगर (rcd->rcvhdrtail_kvaddr)
			qib_clear_rcvhdrtail(rcd);
		rcvctrl_op = QIB_RCVCTRL_CTXT_ENB;
	पूर्ण अन्यथा
		rcvctrl_op = QIB_RCVCTRL_CTXT_DIS;
	dd->f_rcvctrl(rcd->ppd, rcvctrl_op, rcd->ctxt);
	/* always; new head should be equal to new tail; see above */
bail:
	वापस 0;
पूर्ण

अटल व्योम qib_clean_part_key(काष्ठा qib_ctxtdata *rcd,
			       काष्ठा qib_devdata *dd)
अणु
	पूर्णांक i, j, pchanged = 0;
	काष्ठा qib_pportdata *ppd = rcd->ppd;

	क्रम (i = 0; i < ARRAY_SIZE(rcd->pkeys); i++) अणु
		अगर (!rcd->pkeys[i])
			जारी;
		क्रम (j = 0; j < ARRAY_SIZE(ppd->pkeys); j++) अणु
			/* check क्रम match independent of the global bit */
			अगर ((ppd->pkeys[j] & 0x7fff) !=
			    (rcd->pkeys[i] & 0x7fff))
				जारी;
			अगर (atomic_dec_and_test(&ppd->pkeyrefs[j])) अणु
				ppd->pkeys[j] = 0;
				pchanged++;
			पूर्ण
			अवरोध;
		पूर्ण
		rcd->pkeys[i] = 0;
	पूर्ण
	अगर (pchanged)
		(व्योम) ppd->dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PKEYS, 0);
पूर्ण

/* common code क्रम the mappings on dma_alloc_coherent mem */
अटल पूर्णांक qib_mmap_mem(काष्ठा vm_area_काष्ठा *vma, काष्ठा qib_ctxtdata *rcd,
			अचिन्हित len, व्योम *kvaddr, u32 ग_लिखो_ok, अक्षर *what)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	अचिन्हित दीर्घ pfn;
	पूर्णांक ret;

	अगर ((vma->vm_end - vma->vm_start) > len) अणु
		qib_devinfo(dd->pcidev,
			 "FAIL on %s: len %lx > %x\n", what,
			 vma->vm_end - vma->vm_start, len);
		ret = -EFAULT;
		जाओ bail;
	पूर्ण

	/*
	 * shared context user code requires rcvhdrq mapped r/w, others
	 * only allowed पढ़ोonly mapping.
	 */
	अगर (!ग_लिखो_ok) अणु
		अगर (vma->vm_flags & VM_WRITE) अणु
			qib_devinfo(dd->pcidev,
				 "%s must be mapped readonly\n", what);
			ret = -EPERM;
			जाओ bail;
		पूर्ण

		/* करोn't allow them to later change with mprotect */
		vma->vm_flags &= ~VM_MAYWRITE;
	पूर्ण

	pfn = virt_to_phys(kvaddr) >> PAGE_SHIFT;
	ret = remap_pfn_range(vma, vma->vm_start, pfn,
			      len, vma->vm_page_prot);
	अगर (ret)
		qib_devinfo(dd->pcidev,
			"%s ctxt%u mmap of %lx, %x bytes failed: %d\n",
			what, rcd->ctxt, pfn, len, ret);
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक mmap_ureg(काष्ठा vm_area_काष्ठा *vma, काष्ठा qib_devdata *dd,
		     u64 ureg)
अणु
	अचिन्हित दीर्घ phys;
	अचिन्हित दीर्घ sz;
	पूर्णांक ret;

	/*
	 * This is real hardware, so use io_remap.  This is the mechanism
	 * क्रम the user process to update the head रेजिस्टरs क्रम their ctxt
	 * in the chip.
	 */
	sz = dd->flags & QIB_HAS_HDRSUPP ? 2 * PAGE_SIZE : PAGE_SIZE;
	अगर ((vma->vm_end - vma->vm_start) > sz) अणु
		qib_devinfo(dd->pcidev,
			"FAIL mmap userreg: reqlen %lx > PAGE\n",
			vma->vm_end - vma->vm_start);
		ret = -EFAULT;
	पूर्ण अन्यथा अणु
		phys = dd->physaddr + ureg;
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

		vma->vm_flags |= VM_DONTCOPY | VM_DONTEXPAND;
		ret = io_remap_pfn_range(vma, vma->vm_start,
					 phys >> PAGE_SHIFT,
					 vma->vm_end - vma->vm_start,
					 vma->vm_page_prot);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mmap_piobufs(काष्ठा vm_area_काष्ठा *vma,
			काष्ठा qib_devdata *dd,
			काष्ठा qib_ctxtdata *rcd,
			अचिन्हित piobufs, अचिन्हित piocnt)
अणु
	अचिन्हित दीर्घ phys;
	पूर्णांक ret;

	/*
	 * When we map the PIO buffers in the chip, we want to map them as
	 * ग_लिखोonly, no पढ़ो possible; unक्रमtunately, x86 करोesn't allow
	 * क्रम this in hardware, but we still prevent users from asking
	 * क्रम it.
	 */
	अगर ((vma->vm_end - vma->vm_start) > (piocnt * dd->palign)) अणु
		qib_devinfo(dd->pcidev,
			"FAIL mmap piobufs: reqlen %lx > PAGE\n",
			 vma->vm_end - vma->vm_start);
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	phys = dd->physaddr + piobufs;

#अगर defined(__घातerpc__)
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
#पूर्ण_अगर

	/*
	 * करोn't allow them to later change to पढ़ोable with mprotect (क्रम when
	 * not initially mapped पढ़ोable, as is normally the हाल)
	 */
	vma->vm_flags &= ~VM_MAYREAD;
	vma->vm_flags |= VM_DONTCOPY | VM_DONTEXPAND;

	/* We used PAT अगर wc_cookie == 0 */
	अगर (!dd->wc_cookie)
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);

	ret = io_remap_pfn_range(vma, vma->vm_start, phys >> PAGE_SHIFT,
				 vma->vm_end - vma->vm_start,
				 vma->vm_page_prot);
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक mmap_rcvegrbufs(काष्ठा vm_area_काष्ठा *vma,
			   काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	अचिन्हित दीर्घ start, size;
	माप_प्रकार total_size, i;
	अचिन्हित दीर्घ pfn;
	पूर्णांक ret;

	size = rcd->rcvegrbuf_size;
	total_size = rcd->rcvegrbuf_chunks * size;
	अगर ((vma->vm_end - vma->vm_start) > total_size) अणु
		qib_devinfo(dd->pcidev,
			"FAIL on egr bufs: reqlen %lx > actual %lx\n",
			 vma->vm_end - vma->vm_start,
			 (अचिन्हित दीर्घ) total_size);
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (vma->vm_flags & VM_WRITE) अणु
		qib_devinfo(dd->pcidev,
			"Can't map eager buffers as writable (flags=%lx)\n",
			vma->vm_flags);
		ret = -EPERM;
		जाओ bail;
	पूर्ण
	/* करोn't allow them to later change to ग_लिखोable with mprotect */
	vma->vm_flags &= ~VM_MAYWRITE;

	start = vma->vm_start;

	क्रम (i = 0; i < rcd->rcvegrbuf_chunks; i++, start += size) अणु
		pfn = virt_to_phys(rcd->rcvegrbuf[i]) >> PAGE_SHIFT;
		ret = remap_pfn_range(vma, start, pfn, size,
				      vma->vm_page_prot);
		अगर (ret < 0)
			जाओ bail;
	पूर्ण
	ret = 0;

bail:
	वापस ret;
पूर्ण

/*
 * qib_file_vma_fault - handle a VMA page fault.
 */
अटल vm_fault_t qib_file_vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page;

	page = vदो_स्मृति_to_page((व्योम *)(vmf->pgoff << PAGE_SHIFT));
	अगर (!page)
		वापस VM_FAULT_SIGBUS;

	get_page(page);
	vmf->page = page;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा qib_file_vm_ops = अणु
	.fault = qib_file_vma_fault,
पूर्ण;

अटल पूर्णांक mmap_kvaddr(काष्ठा vm_area_काष्ठा *vma, u64 pgaddr,
		       काष्ठा qib_ctxtdata *rcd, अचिन्हित subctxt)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	अचिन्हित subctxt_cnt;
	अचिन्हित दीर्घ len;
	व्योम *addr;
	माप_प्रकार size;
	पूर्णांक ret = 0;

	subctxt_cnt = rcd->subctxt_cnt;
	size = rcd->rcvegrbuf_chunks * rcd->rcvegrbuf_size;

	/*
	 * Each process has all the subctxt uregbase, rcvhdrq, and
	 * rcvegrbufs mmapped - as an array क्रम all the processes,
	 * and also separately क्रम this process.
	 */
	अगर (pgaddr == cvt_kvaddr(rcd->subctxt_uregbase)) अणु
		addr = rcd->subctxt_uregbase;
		size = PAGE_SIZE * subctxt_cnt;
	पूर्ण अन्यथा अगर (pgaddr == cvt_kvaddr(rcd->subctxt_rcvhdr_base)) अणु
		addr = rcd->subctxt_rcvhdr_base;
		size = rcd->rcvhdrq_size * subctxt_cnt;
	पूर्ण अन्यथा अगर (pgaddr == cvt_kvaddr(rcd->subctxt_rcvegrbuf)) अणु
		addr = rcd->subctxt_rcvegrbuf;
		size *= subctxt_cnt;
	पूर्ण अन्यथा अगर (pgaddr == cvt_kvaddr(rcd->subctxt_uregbase +
					PAGE_SIZE * subctxt)) अणु
		addr = rcd->subctxt_uregbase + PAGE_SIZE * subctxt;
		size = PAGE_SIZE;
	पूर्ण अन्यथा अगर (pgaddr == cvt_kvaddr(rcd->subctxt_rcvhdr_base +
					rcd->rcvhdrq_size * subctxt)) अणु
		addr = rcd->subctxt_rcvhdr_base +
			rcd->rcvhdrq_size * subctxt;
		size = rcd->rcvhdrq_size;
	पूर्ण अन्यथा अगर (pgaddr == cvt_kvaddr(&rcd->user_event_mask[subctxt])) अणु
		addr = rcd->user_event_mask;
		size = PAGE_SIZE;
	पूर्ण अन्यथा अगर (pgaddr == cvt_kvaddr(rcd->subctxt_rcvegrbuf +
					size * subctxt)) अणु
		addr = rcd->subctxt_rcvegrbuf + size * subctxt;
		/* rcvegrbufs are पढ़ो-only on the slave */
		अगर (vma->vm_flags & VM_WRITE) अणु
			qib_devinfo(dd->pcidev,
				 "Can't map eager buffers as writable (flags=%lx)\n",
				 vma->vm_flags);
			ret = -EPERM;
			जाओ bail;
		पूर्ण
		/*
		 * Don't allow permission to later change to ग_लिखोable
		 * with mprotect.
		 */
		vma->vm_flags &= ~VM_MAYWRITE;
	पूर्ण अन्यथा
		जाओ bail;
	len = vma->vm_end - vma->vm_start;
	अगर (len > size) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	vma->vm_pgoff = (अचिन्हित दीर्घ) addr >> PAGE_SHIFT;
	vma->vm_ops = &qib_file_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	ret = 1;

bail:
	वापस ret;
पूर्ण

/**
 * qib_mmapf - mmap various काष्ठाures पूर्णांकo user space
 * @fp: the file poपूर्णांकer
 * @vma: the VM area
 *
 * We use this to have a shared buffer between the kernel and the user code
 * क्रम the rcvhdr queue, egr buffers, and the per-context user regs and pio
 * buffers in the chip.  We have the खोलो and बंद entries so we can bump
 * the ref count and keep the driver from being unloaded जबतक still mapped.
 */
अटल पूर्णांक qib_mmapf(काष्ठा file *fp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा qib_ctxtdata *rcd;
	काष्ठा qib_devdata *dd;
	u64 pgaddr, ureg;
	अचिन्हित piobufs, piocnt;
	पूर्णांक ret, match = 1;

	rcd = ctxt_fp(fp);
	अगर (!rcd || !(vma->vm_flags & VM_SHARED)) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	dd = rcd->dd;

	/*
	 * This is the qib_करो_user_init() code, mapping the shared buffers
	 * and per-context user रेजिस्टरs पूर्णांकo the user process. The address
	 * referred to by vm_pgoff is the file offset passed via mmap().
	 * For shared contexts, this is the kernel vदो_स्मृति() address of the
	 * pages to share with the master.
	 * For non-shared or master ctxts, this is a physical address.
	 * We only करो one mmap क्रम each space mapped.
	 */
	pgaddr = vma->vm_pgoff << PAGE_SHIFT;

	/*
	 * Check क्रम 0 in हाल one of the allocations failed, but user
	 * called mmap anyway.
	 */
	अगर (!pgaddr)  अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	/*
	 * Physical addresses must fit in 40 bits क्रम our hardware.
	 * Check क्रम kernel भव addresses first, anything अन्यथा must
	 * match a HW or memory address.
	 */
	ret = mmap_kvaddr(vma, pgaddr, rcd, subctxt_fp(fp));
	अगर (ret) अणु
		अगर (ret > 0)
			ret = 0;
		जाओ bail;
	पूर्ण

	ureg = dd->uregbase + dd->ureg_align * rcd->ctxt;
	अगर (!rcd->subctxt_cnt) अणु
		/* ctxt is not shared */
		piocnt = rcd->piocnt;
		piobufs = rcd->piobufs;
	पूर्ण अन्यथा अगर (!subctxt_fp(fp)) अणु
		/* caller is the master */
		piocnt = (rcd->piocnt / rcd->subctxt_cnt) +
			 (rcd->piocnt % rcd->subctxt_cnt);
		piobufs = rcd->piobufs +
			dd->palign * (rcd->piocnt - piocnt);
	पूर्ण अन्यथा अणु
		अचिन्हित slave = subctxt_fp(fp) - 1;

		/* caller is a slave */
		piocnt = rcd->piocnt / rcd->subctxt_cnt;
		piobufs = rcd->piobufs + dd->palign * piocnt * slave;
	पूर्ण

	अगर (pgaddr == ureg)
		ret = mmap_ureg(vma, dd, ureg);
	अन्यथा अगर (pgaddr == piobufs)
		ret = mmap_piobufs(vma, dd, rcd, piobufs, piocnt);
	अन्यथा अगर (pgaddr == dd->pioavailregs_phys)
		/* in-memory copy of pioavail रेजिस्टरs */
		ret = qib_mmap_mem(vma, rcd, PAGE_SIZE,
				   (व्योम *) dd->pioavailregs_dma, 0,
				   "pioavail registers");
	अन्यथा अगर (pgaddr == rcd->rcvegr_phys)
		ret = mmap_rcvegrbufs(vma, rcd);
	अन्यथा अगर (pgaddr == (u64) rcd->rcvhdrq_phys)
		/*
		 * The rcvhdrq itself; multiple pages, contiguous
		 * from an i/o perspective.  Shared contexts need
		 * to map r/w, so we allow writing.
		 */
		ret = qib_mmap_mem(vma, rcd, rcd->rcvhdrq_size,
				   rcd->rcvhdrq, 1, "rcvhdrq");
	अन्यथा अगर (pgaddr == (u64) rcd->rcvhdrqtailaddr_phys)
		/* in-memory copy of rcvhdrq tail रेजिस्टर */
		ret = qib_mmap_mem(vma, rcd, PAGE_SIZE,
				   rcd->rcvhdrtail_kvaddr, 0,
				   "rcvhdrq tail");
	अन्यथा
		match = 0;
	अगर (!match)
		ret = -EINVAL;

	vma->vm_निजी_data = शून्य;

	अगर (ret < 0)
		qib_devinfo(dd->pcidev,
			 "mmap Failure %d: off %llx len %lx\n",
			 -ret, (अचिन्हित दीर्घ दीर्घ)pgaddr,
			 vma->vm_end - vma->vm_start);
bail:
	वापस ret;
पूर्ण

अटल __poll_t qib_poll_urgent(काष्ठा qib_ctxtdata *rcd,
				    काष्ठा file *fp,
				    काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	__poll_t pollflag;

	poll_रुको(fp, &rcd->रुको, pt);

	spin_lock_irq(&dd->uctxt_lock);
	अगर (rcd->urgent != rcd->urgent_poll) अणु
		pollflag = EPOLLIN | EPOLLRDNORM;
		rcd->urgent_poll = rcd->urgent;
	पूर्ण अन्यथा अणु
		pollflag = 0;
		set_bit(QIB_CTXT_WAITING_URG, &rcd->flag);
	पूर्ण
	spin_unlock_irq(&dd->uctxt_lock);

	वापस pollflag;
पूर्ण

अटल __poll_t qib_poll_next(काष्ठा qib_ctxtdata *rcd,
				  काष्ठा file *fp,
				  काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	__poll_t pollflag;

	poll_रुको(fp, &rcd->रुको, pt);

	spin_lock_irq(&dd->uctxt_lock);
	अगर (dd->f_hdrqempty(rcd)) अणु
		set_bit(QIB_CTXT_WAITING_RCV, &rcd->flag);
		dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_INTRAVAIL_ENB, rcd->ctxt);
		pollflag = 0;
	पूर्ण अन्यथा
		pollflag = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irq(&dd->uctxt_lock);

	वापस pollflag;
पूर्ण

अटल __poll_t qib_poll(काष्ठा file *fp, काष्ठा poll_table_काष्ठा *pt)
अणु
	काष्ठा qib_ctxtdata *rcd;
	__poll_t pollflag;

	rcd = ctxt_fp(fp);
	अगर (!rcd)
		pollflag = EPOLLERR;
	अन्यथा अगर (rcd->poll_type == QIB_POLL_TYPE_URGENT)
		pollflag = qib_poll_urgent(rcd, fp, pt);
	अन्यथा  अगर (rcd->poll_type == QIB_POLL_TYPE_ANYRCV)
		pollflag = qib_poll_next(rcd, fp, pt);
	अन्यथा /* invalid */
		pollflag = EPOLLERR;

	वापस pollflag;
पूर्ण

अटल व्योम assign_ctxt_affinity(काष्ठा file *fp, काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_filedata *fd = fp->निजी_data;
	स्थिर अचिन्हित पूर्णांक weight = current->nr_cpus_allowed;
	स्थिर काष्ठा cpumask *local_mask = cpumask_of_pcibus(dd->pcidev->bus);
	पूर्णांक local_cpu;

	/*
	 * If process has NOT alपढ़ोy set it's affinity, select and
	 * reserve a processor क्रम it on the local NUMA node.
	 */
	अगर ((weight >= qib_cpulist_count) &&
		(cpumask_weight(local_mask) <= qib_cpulist_count)) अणु
		क्रम_each_cpu(local_cpu, local_mask)
			अगर (!test_and_set_bit(local_cpu, qib_cpulist)) अणु
				fd->rec_cpu_num = local_cpu;
				वापस;
			पूर्ण
	पूर्ण

	/*
	 * If process has NOT alपढ़ोy set it's affinity, select and
	 * reserve a processor क्रम it, as a rendevous क्रम all
	 * users of the driver.  If they करोn't actually later
	 * set affinity to this cpu, or set it to some other cpu,
	 * it just means that sooner or later we करोn't recommend
	 * a cpu, and let the scheduler करो it's best.
	 */
	अगर (weight >= qib_cpulist_count) अणु
		पूर्णांक cpu;

		cpu = find_first_zero_bit(qib_cpulist,
					  qib_cpulist_count);
		अगर (cpu == qib_cpulist_count)
			qib_dev_err(dd,
			"no cpus avail for affinity PID %u\n",
			current->pid);
		अन्यथा अणु
			__set_bit(cpu, qib_cpulist);
			fd->rec_cpu_num = cpu;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Check that userland and driver are compatible क्रम subcontexts.
 */
अटल पूर्णांक qib_compatible_subctxts(पूर्णांक user_swmajor, पूर्णांक user_swminor)
अणु
	/* this code is written दीर्घ-hand क्रम clarity */
	अगर (QIB_USER_SWMAJOR != user_swmajor) अणु
		/* no promise of compatibility अगर major mismatch */
		वापस 0;
	पूर्ण
	अगर (QIB_USER_SWMAJOR == 1) अणु
		चयन (QIB_USER_SWMINOR) अणु
		हाल 0:
		हाल 1:
		हाल 2:
			/* no subctxt implementation so cannot be compatible */
			वापस 0;
		हाल 3:
			/* 3 is only compatible with itself */
			वापस user_swminor == 3;
		शेष:
			/* >= 4 are compatible (or are expected to be) */
			वापस user_swminor <= QIB_USER_SWMINOR;
		पूर्ण
	पूर्ण
	/* make no promises yet क्रम future major versions */
	वापस 0;
पूर्ण

अटल पूर्णांक init_subctxts(काष्ठा qib_devdata *dd,
			 काष्ठा qib_ctxtdata *rcd,
			 स्थिर काष्ठा qib_user_info *uinfo)
अणु
	पूर्णांक ret = 0;
	अचिन्हित num_subctxts;
	माप_प्रकार size;

	/*
	 * If the user is requesting zero subctxts,
	 * skip the subctxt allocation.
	 */
	अगर (uinfo->spu_subctxt_cnt <= 0)
		जाओ bail;
	num_subctxts = uinfo->spu_subctxt_cnt;

	/* Check क्रम subctxt compatibility */
	अगर (!qib_compatible_subctxts(uinfo->spu_userversion >> 16,
		uinfo->spu_userversion & 0xffff)) अणु
		qib_devinfo(dd->pcidev,
			 "Mismatched user version (%d.%d) and driver version (%d.%d) while context sharing. Ensure that driver and library are from the same release.\n",
			 (पूर्णांक) (uinfo->spu_userversion >> 16),
			 (पूर्णांक) (uinfo->spu_userversion & 0xffff),
			 QIB_USER_SWMAJOR, QIB_USER_SWMINOR);
		जाओ bail;
	पूर्ण
	अगर (num_subctxts > QLOGIC_IB_MAX_SUBCTXT) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	rcd->subctxt_uregbase = vदो_स्मृति_user(PAGE_SIZE * num_subctxts);
	अगर (!rcd->subctxt_uregbase) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण
	/* Note: rcd->rcvhdrq_size isn't initialized yet. */
	size = ALIGN(dd->rcvhdrcnt * dd->rcvhdrentsize *
		     माप(u32), PAGE_SIZE) * num_subctxts;
	rcd->subctxt_rcvhdr_base = vदो_स्मृति_user(size);
	अगर (!rcd->subctxt_rcvhdr_base) अणु
		ret = -ENOMEM;
		जाओ bail_ureg;
	पूर्ण

	rcd->subctxt_rcvegrbuf = vदो_स्मृति_user(rcd->rcvegrbuf_chunks *
					      rcd->rcvegrbuf_size *
					      num_subctxts);
	अगर (!rcd->subctxt_rcvegrbuf) अणु
		ret = -ENOMEM;
		जाओ bail_rhdr;
	पूर्ण

	rcd->subctxt_cnt = uinfo->spu_subctxt_cnt;
	rcd->subctxt_id = uinfo->spu_subctxt_id;
	rcd->active_slaves = 1;
	rcd->redirect_seq_cnt = 1;
	set_bit(QIB_CTXT_MASTER_UNINIT, &rcd->flag);
	जाओ bail;

bail_rhdr:
	vमुक्त(rcd->subctxt_rcvhdr_base);
bail_ureg:
	vमुक्त(rcd->subctxt_uregbase);
	rcd->subctxt_uregbase = शून्य;
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक setup_ctxt(काष्ठा qib_pportdata *ppd, पूर्णांक ctxt,
		      काष्ठा file *fp, स्थिर काष्ठा qib_user_info *uinfo)
अणु
	काष्ठा qib_filedata *fd = fp->निजी_data;
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा qib_ctxtdata *rcd;
	व्योम *pपंचांगp = शून्य;
	पूर्णांक ret;
	पूर्णांक numa_id;

	assign_ctxt_affinity(fp, dd);

	numa_id = qib_numa_aware ? ((fd->rec_cpu_num != -1) ?
		cpu_to_node(fd->rec_cpu_num) :
		numa_node_id()) : dd->asचिन्हित_node_id;

	rcd = qib_create_ctxtdata(ppd, ctxt, numa_id);

	/*
	 * Allocate memory क्रम use in qib_tid_update() at खोलो to
	 * reduce cost of expected send setup per message segment
	 */
	अगर (rcd)
		pपंचांगp = kदो_स्मृति(dd->rcvtidcnt * माप(u16) +
			       dd->rcvtidcnt * माप(काष्ठा page **),
			       GFP_KERNEL);

	अगर (!rcd || !pपंचांगp) अणु
		qib_dev_err(dd,
			"Unable to allocate ctxtdata memory, failing open\n");
		ret = -ENOMEM;
		जाओ bailerr;
	पूर्ण
	rcd->userversion = uinfo->spu_userversion;
	ret = init_subctxts(dd, rcd, uinfo);
	अगर (ret)
		जाओ bailerr;
	rcd->tid_pg_list = pपंचांगp;
	rcd->pid = current->pid;
	init_रुकोqueue_head(&dd->rcd[ctxt]->रुको);
	strlcpy(rcd->comm, current->comm, माप(rcd->comm));
	ctxt_fp(fp) = rcd;
	qib_stats.sps_ctxts++;
	dd->मुक्तctxts--;
	ret = 0;
	जाओ bail;

bailerr:
	अगर (fd->rec_cpu_num != -1)
		__clear_bit(fd->rec_cpu_num, qib_cpulist);

	dd->rcd[ctxt] = शून्य;
	kमुक्त(rcd);
	kमुक्त(pपंचांगp);
bail:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक usable(काष्ठा qib_pportdata *ppd)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;

	वापस dd && (dd->flags & QIB_PRESENT) && dd->kregbase && ppd->lid &&
		(ppd->lflags & QIBL_LINKACTIVE);
पूर्ण

/*
 * Select a context on the given device, either using a requested port
 * or the port based on the context number.
 */
अटल पूर्णांक choose_port_ctxt(काष्ठा file *fp, काष्ठा qib_devdata *dd, u32 port,
			    स्थिर काष्ठा qib_user_info *uinfo)
अणु
	काष्ठा qib_pportdata *ppd = शून्य;
	पूर्णांक ret, ctxt;

	अगर (port) अणु
		अगर (!usable(dd->pport + port - 1)) अणु
			ret = -ENETDOWN;
			जाओ करोne;
		पूर्ण अन्यथा
			ppd = dd->pport + port - 1;
	पूर्ण
	क्रम (ctxt = dd->first_user_ctxt; ctxt < dd->cfgctxts && dd->rcd[ctxt];
	     ctxt++)
		;
	अगर (ctxt == dd->cfgctxts) अणु
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण
	अगर (!ppd) अणु
		u32 pidx = ctxt % dd->num_pports;

		अगर (usable(dd->pport + pidx))
			ppd = dd->pport + pidx;
		अन्यथा अणु
			क्रम (pidx = 0; pidx < dd->num_pports && !ppd;
			     pidx++)
				अगर (usable(dd->pport + pidx))
					ppd = dd->pport + pidx;
		पूर्ण
	पूर्ण
	ret = ppd ? setup_ctxt(ppd, ctxt, fp, uinfo) : -ENETDOWN;
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक find_मुक्त_ctxt(पूर्णांक unit, काष्ठा file *fp,
			  स्थिर काष्ठा qib_user_info *uinfo)
अणु
	काष्ठा qib_devdata *dd = qib_lookup(unit);
	पूर्णांक ret;

	अगर (!dd || (uinfo->spu_port && uinfo->spu_port > dd->num_pports))
		ret = -ENODEV;
	अन्यथा
		ret = choose_port_ctxt(fp, dd, uinfo->spu_port, uinfo);

	वापस ret;
पूर्ण

अटल पूर्णांक get_a_ctxt(काष्ठा file *fp, स्थिर काष्ठा qib_user_info *uinfo,
		      अचिन्हित alg)
अणु
	काष्ठा qib_devdata *udd = शून्य;
	पूर्णांक ret = 0, devmax, npresent, nup, ndev, dusable = 0, i;
	u32 port = uinfo->spu_port, ctxt;

	devmax = qib_count_units(&npresent, &nup);
	अगर (!npresent) अणु
		ret = -ENXIO;
		जाओ करोne;
	पूर्ण
	अगर (nup == 0) अणु
		ret = -ENETDOWN;
		जाओ करोne;
	पूर्ण

	अगर (alg == QIB_PORT_ALG_ACROSS) अणु
		अचिन्हित inuse = ~0U;

		/* find device (with ACTIVE ports) with fewest ctxts in use */
		क्रम (ndev = 0; ndev < devmax; ndev++) अणु
			काष्ठा qib_devdata *dd = qib_lookup(ndev);
			अचिन्हित cused = 0, cमुक्त = 0, pusable = 0;

			अगर (!dd)
				जारी;
			अगर (port && port <= dd->num_pports &&
			    usable(dd->pport + port - 1))
				pusable = 1;
			अन्यथा
				क्रम (i = 0; i < dd->num_pports; i++)
					अगर (usable(dd->pport + i))
						pusable++;
			अगर (!pusable)
				जारी;
			क्रम (ctxt = dd->first_user_ctxt; ctxt < dd->cfgctxts;
			     ctxt++)
				अगर (dd->rcd[ctxt])
					cused++;
				अन्यथा
					cमुक्त++;
			अगर (cमुक्त && cused < inuse) अणु
				udd = dd;
				inuse = cused;
			पूर्ण
		पूर्ण
		अगर (udd) अणु
			ret = choose_port_ctxt(fp, udd, port, uinfo);
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (ndev = 0; ndev < devmax; ndev++) अणु
			काष्ठा qib_devdata *dd = qib_lookup(ndev);

			अगर (dd) अणु
				ret = choose_port_ctxt(fp, dd, port, uinfo);
				अगर (!ret)
					जाओ करोne;
				अगर (ret == -EBUSY)
					dusable++;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = dusable ? -EBUSY : -ENETDOWN;

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक find_shared_ctxt(काष्ठा file *fp,
			    स्थिर काष्ठा qib_user_info *uinfo)
अणु
	पूर्णांक devmax, ndev, i;
	पूर्णांक ret = 0;

	devmax = qib_count_units(शून्य, शून्य);

	क्रम (ndev = 0; ndev < devmax; ndev++) अणु
		काष्ठा qib_devdata *dd = qib_lookup(ndev);

		/* device portion of usable() */
		अगर (!(dd && (dd->flags & QIB_PRESENT) && dd->kregbase))
			जारी;
		क्रम (i = dd->first_user_ctxt; i < dd->cfgctxts; i++) अणु
			काष्ठा qib_ctxtdata *rcd = dd->rcd[i];

			/* Skip ctxts which are not yet खोलो */
			अगर (!rcd || !rcd->cnt)
				जारी;
			/* Skip ctxt अगर it करोesn't match the requested one */
			अगर (rcd->subctxt_id != uinfo->spu_subctxt_id)
				जारी;
			/* Verअगरy the sharing process matches the master */
			अगर (rcd->subctxt_cnt != uinfo->spu_subctxt_cnt ||
			    rcd->userversion != uinfo->spu_userversion ||
			    rcd->cnt >= rcd->subctxt_cnt) अणु
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			ctxt_fp(fp) = rcd;
			subctxt_fp(fp) = rcd->cnt++;
			rcd->subpid[subctxt_fp(fp)] = current->pid;
			tidcursor_fp(fp) = 0;
			rcd->active_slaves |= 1 << subctxt_fp(fp);
			ret = 1;
			जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_खोलो(काष्ठा inode *in, काष्ठा file *fp)
अणु
	/* The real work is perक्रमmed later in qib_assign_ctxt() */
	fp->निजी_data = kzalloc(माप(काष्ठा qib_filedata), GFP_KERNEL);
	अगर (fp->निजी_data) /* no cpu affinity by शेष */
		((काष्ठा qib_filedata *)fp->निजी_data)->rec_cpu_num = -1;
	वापस fp->निजी_data ? 0 : -ENOMEM;
पूर्ण

अटल पूर्णांक find_hca(अचिन्हित पूर्णांक cpu, पूर्णांक *unit)
अणु
	पूर्णांक ret = 0, devmax, npresent, nup, ndev;

	*unit = -1;

	devmax = qib_count_units(&npresent, &nup);
	अगर (!npresent) अणु
		ret = -ENXIO;
		जाओ करोne;
	पूर्ण
	अगर (!nup) अणु
		ret = -ENETDOWN;
		जाओ करोne;
	पूर्ण
	क्रम (ndev = 0; ndev < devmax; ndev++) अणु
		काष्ठा qib_devdata *dd = qib_lookup(ndev);

		अगर (dd) अणु
			अगर (pcibus_to_node(dd->pcidev->bus) < 0) अणु
				ret = -EINVAL;
				जाओ करोne;
			पूर्ण
			अगर (cpu_to_node(cpu) ==
				pcibus_to_node(dd->pcidev->bus)) अणु
				*unit = ndev;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक करो_qib_user_sdma_queue_create(काष्ठा file *fp)
अणु
	काष्ठा qib_filedata *fd = fp->निजी_data;
	काष्ठा qib_ctxtdata *rcd = fd->rcd;
	काष्ठा qib_devdata *dd = rcd->dd;

	अगर (dd->flags & QIB_HAS_SEND_DMA) अणु

		fd->pq = qib_user_sdma_queue_create(&dd->pcidev->dev,
						    dd->unit,
						    rcd->ctxt,
						    fd->subctxt);
		अगर (!fd->pq)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Get ctxt early, so can set affinity prior to memory allocation.
 */
अटल पूर्णांक qib_assign_ctxt(काष्ठा file *fp, स्थिर काष्ठा qib_user_info *uinfo)
अणु
	पूर्णांक ret;
	पूर्णांक i_minor;
	अचिन्हित swmajor, swminor, alg = QIB_PORT_ALG_ACROSS;

	/* Check to be sure we haven't alपढ़ोy initialized this file */
	अगर (ctxt_fp(fp)) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	/* क्रम now, अगर major version is dअगरferent, bail */
	swmajor = uinfo->spu_userversion >> 16;
	अगर (swmajor != QIB_USER_SWMAJOR) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	swminor = uinfo->spu_userversion & 0xffff;

	अगर (swminor >= 11 && uinfo->spu_port_alg < QIB_PORT_ALG_COUNT)
		alg = uinfo->spu_port_alg;

	mutex_lock(&qib_mutex);

	अगर (qib_compatible_subctxts(swmajor, swminor) &&
	    uinfo->spu_subctxt_cnt) अणु
		ret = find_shared_ctxt(fp, uinfo);
		अगर (ret > 0) अणु
			ret = करो_qib_user_sdma_queue_create(fp);
			अगर (!ret)
				assign_ctxt_affinity(fp, (ctxt_fp(fp))->dd);
			जाओ करोne_ok;
		पूर्ण
	पूर्ण

	i_minor = iminor(file_inode(fp)) - QIB_USER_MINOR_BASE;
	अगर (i_minor)
		ret = find_मुक्त_ctxt(i_minor - 1, fp, uinfo);
	अन्यथा अणु
		पूर्णांक unit;
		स्थिर अचिन्हित पूर्णांक cpu = cpumask_first(current->cpus_ptr);
		स्थिर अचिन्हित पूर्णांक weight = current->nr_cpus_allowed;

		अगर (weight == 1 && !test_bit(cpu, qib_cpulist))
			अगर (!find_hca(cpu, &unit) && unit >= 0)
				अगर (!find_मुक्त_ctxt(unit, fp, uinfo)) अणु
					ret = 0;
					जाओ करोne_chk_sdma;
				पूर्ण
		ret = get_a_ctxt(fp, uinfo, alg);
	पूर्ण

करोne_chk_sdma:
	अगर (!ret)
		ret = करो_qib_user_sdma_queue_create(fp);
करोne_ok:
	mutex_unlock(&qib_mutex);

करोne:
	वापस ret;
पूर्ण


अटल पूर्णांक qib_करो_user_init(काष्ठा file *fp,
			    स्थिर काष्ठा qib_user_info *uinfo)
अणु
	पूर्णांक ret;
	काष्ठा qib_ctxtdata *rcd = ctxt_fp(fp);
	काष्ठा qib_devdata *dd;
	अचिन्हित uctxt;

	/* Subctxts करोn't need to initialize anything since master did it. */
	अगर (subctxt_fp(fp)) अणु
		ret = रुको_event_पूर्णांकerruptible(rcd->रुको,
			!test_bit(QIB_CTXT_MASTER_UNINIT, &rcd->flag));
		जाओ bail;
	पूर्ण

	dd = rcd->dd;

	/* some ctxts may get extra buffers, calculate that here */
	uctxt = rcd->ctxt - dd->first_user_ctxt;
	अगर (uctxt < dd->ctxts_extrabuf) अणु
		rcd->piocnt = dd->pbufsctxt + 1;
		rcd->pio_base = rcd->piocnt * uctxt;
	पूर्ण अन्यथा अणु
		rcd->piocnt = dd->pbufsctxt;
		rcd->pio_base = rcd->piocnt * uctxt +
			dd->ctxts_extrabuf;
	पूर्ण

	/*
	 * All user buffers are 2KB buffers.  If we ever support
	 * giving 4KB buffers to user processes, this will need some
	 * work.  Can't use piobufbase directly, because it has
	 * both 2K and 4K buffer base values.  So check and handle.
	 */
	अगर ((rcd->pio_base + rcd->piocnt) > dd->piobcnt2k) अणु
		अगर (rcd->pio_base >= dd->piobcnt2k) अणु
			qib_dev_err(dd,
				    "%u:ctxt%u: no 2KB buffers available\n",
				    dd->unit, rcd->ctxt);
			ret = -ENOBUFS;
			जाओ bail;
		पूर्ण
		rcd->piocnt = dd->piobcnt2k - rcd->pio_base;
		qib_dev_err(dd, "Ctxt%u: would use 4KB bufs, using %u\n",
			    rcd->ctxt, rcd->piocnt);
	पूर्ण

	rcd->piobufs = dd->pio2k_bufbase + rcd->pio_base * dd->palign;
	qib_chg_pioavailkernel(dd, rcd->pio_base, rcd->piocnt,
			       TXCHK_CHG_TYPE_USER, rcd);
	/*
	 * try to ensure that processes start up with consistent avail update
	 * क्रम their own range, at least.   If प्रणाली very quiet, it might
	 * have the in-memory copy out of date at startup क्रम this range of
	 * buffers, when a context माला_लो re-used.  Do after the chg_pioavail
	 * and beक्रमe the rest of setup, so it's "almost certain" the dma
	 * will have occurred (can't 100% guarantee, but should be many
	 * decimals of 9s, with this ordering), given how much अन्यथा happens
	 * after this.
	 */
	dd->f_sendctrl(dd->pport, QIB_SENDCTRL_AVAIL_BLIP);

	/*
	 * Now allocate the rcvhdr Q and eager TIDs; skip the TID
	 * array क्रम समय being.  If rcd->ctxt > chip-supported,
	 * we need to करो extra stuff here to handle by handling overflow
	 * through ctxt 0, someday
	 */
	ret = qib_create_rcvhdrq(dd, rcd);
	अगर (!ret)
		ret = qib_setup_eagerbufs(rcd);
	अगर (ret)
		जाओ bail_pio;

	rcd->tidcursor = 0; /* start at beginning after खोलो */

	/* initialize poll variables... */
	rcd->urgent = 0;
	rcd->urgent_poll = 0;

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
	अगर (rcd->rcvhdrtail_kvaddr)
		qib_clear_rcvhdrtail(rcd);

	dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_CTXT_ENB | QIB_RCVCTRL_TIDFLOW_ENB,
		      rcd->ctxt);

	/* Notअगरy any रुकोing slaves */
	अगर (rcd->subctxt_cnt) अणु
		clear_bit(QIB_CTXT_MASTER_UNINIT, &rcd->flag);
		wake_up(&rcd->रुको);
	पूर्ण
	वापस 0;

bail_pio:
	qib_chg_pioavailkernel(dd, rcd->pio_base, rcd->piocnt,
			       TXCHK_CHG_TYPE_KERN, rcd);
bail:
	वापस ret;
पूर्ण

/**
 * unlock_expected_tids - unlock any expected TID entries context still had
 * in use
 * @rcd: ctxt
 *
 * We करोn't actually update the chip here, because we करो a bulk update
 * below, using f_clear_tids.
 */
अटल व्योम unlock_expected_tids(काष्ठा qib_ctxtdata *rcd)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	पूर्णांक ctxt_tidbase = rcd->ctxt * dd->rcvtidcnt;
	पूर्णांक i, cnt = 0, maxtid = ctxt_tidbase + dd->rcvtidcnt;

	क्रम (i = ctxt_tidbase; i < maxtid; i++) अणु
		काष्ठा page *p = dd->pageshaकरोw[i];
		dma_addr_t phys;

		अगर (!p)
			जारी;

		phys = dd->physshaकरोw[i];
		dd->physshaकरोw[i] = dd->tidinvalid;
		dd->pageshaकरोw[i] = शून्य;
		pci_unmap_page(dd->pcidev, phys, PAGE_SIZE,
			       PCI_DMA_FROMDEVICE);
		qib_release_user_pages(&p, 1);
		cnt++;
	पूर्ण
पूर्ण

अटल पूर्णांक qib_बंद(काष्ठा inode *in, काष्ठा file *fp)
अणु
	काष्ठा qib_filedata *fd;
	काष्ठा qib_ctxtdata *rcd;
	काष्ठा qib_devdata *dd;
	अचिन्हित दीर्घ flags;
	अचिन्हित ctxt;

	mutex_lock(&qib_mutex);

	fd = fp->निजी_data;
	fp->निजी_data = शून्य;
	rcd = fd->rcd;
	अगर (!rcd) अणु
		mutex_unlock(&qib_mutex);
		जाओ bail;
	पूर्ण

	dd = rcd->dd;

	/* ensure all pio buffer ग_लिखोs in progress are flushed */
	qib_flush_wc();

	/* drain user sdma queue */
	अगर (fd->pq) अणु
		qib_user_sdma_queue_drain(rcd->ppd, fd->pq);
		qib_user_sdma_queue_destroy(fd->pq);
	पूर्ण

	अगर (fd->rec_cpu_num != -1)
		__clear_bit(fd->rec_cpu_num, qib_cpulist);

	अगर (--rcd->cnt) अणु
		/*
		 * XXX If the master बंदs the context beक्रमe the slave(s),
		 * revoke the mmap क्रम the eager receive queue so
		 * the slave(s) करोn't रुको क्रम receive data क्रमever.
		 */
		rcd->active_slaves &= ~(1 << fd->subctxt);
		rcd->subpid[fd->subctxt] = 0;
		mutex_unlock(&qib_mutex);
		जाओ bail;
	पूर्ण

	/* early; no पूर्णांकerrupt users after this */
	spin_lock_irqsave(&dd->uctxt_lock, flags);
	ctxt = rcd->ctxt;
	dd->rcd[ctxt] = शून्य;
	rcd->pid = 0;
	spin_unlock_irqrestore(&dd->uctxt_lock, flags);

	अगर (rcd->rcvरुको_to || rcd->pioरुको_to ||
	    rcd->rcvnoरुको || rcd->pionoरुको) अणु
		rcd->rcvरुको_to = 0;
		rcd->pioरुको_to = 0;
		rcd->rcvnoरुको = 0;
		rcd->pionoरुको = 0;
	पूर्ण
	अगर (rcd->flag)
		rcd->flag = 0;

	अगर (dd->kregbase) अणु
		/* atomically clear receive enable ctxt and पूर्णांकr avail. */
		dd->f_rcvctrl(rcd->ppd, QIB_RCVCTRL_CTXT_DIS |
				  QIB_RCVCTRL_INTRAVAIL_DIS, ctxt);

		/* clean up the pkeys क्रम this ctxt user */
		qib_clean_part_key(rcd, dd);
		qib_disarm_piobufs(dd, rcd->pio_base, rcd->piocnt);
		qib_chg_pioavailkernel(dd, rcd->pio_base,
				       rcd->piocnt, TXCHK_CHG_TYPE_KERN, शून्य);

		dd->f_clear_tids(dd, rcd);

		अगर (dd->pageshaकरोw)
			unlock_expected_tids(rcd);
		qib_stats.sps_ctxts--;
		dd->मुक्तctxts++;
	पूर्ण

	mutex_unlock(&qib_mutex);
	qib_मुक्त_ctxtdata(dd, rcd); /* after releasing the mutex */

bail:
	kमुक्त(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक qib_ctxt_info(काष्ठा file *fp, काष्ठा qib_ctxt_info __user *uinfo)
अणु
	काष्ठा qib_ctxt_info info;
	पूर्णांक ret;
	माप_प्रकार sz;
	काष्ठा qib_ctxtdata *rcd = ctxt_fp(fp);
	काष्ठा qib_filedata *fd;

	fd = fp->निजी_data;

	info.num_active = qib_count_active_units();
	info.unit = rcd->dd->unit;
	info.port = rcd->ppd->port;
	info.ctxt = rcd->ctxt;
	info.subctxt =  subctxt_fp(fp);
	/* Number of user ctxts available क्रम this device. */
	info.num_ctxts = rcd->dd->cfgctxts - rcd->dd->first_user_ctxt;
	info.num_subctxts = rcd->subctxt_cnt;
	info.rec_cpu = fd->rec_cpu_num;
	sz = माप(info);

	अगर (copy_to_user(uinfo, &info, sz)) अणु
		ret = -EFAULT;
		जाओ bail;
	पूर्ण
	ret = 0;

bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_sdma_get_inflight(काष्ठा qib_user_sdma_queue *pq,
				 u32 __user *inflightp)
अणु
	स्थिर u32 val = qib_user_sdma_inflight_counter(pq);

	अगर (put_user(val, inflightp))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक qib_sdma_get_complete(काष्ठा qib_pportdata *ppd,
				 काष्ठा qib_user_sdma_queue *pq,
				 u32 __user *completep)
अणु
	u32 val;
	पूर्णांक err;

	अगर (!pq)
		वापस -EINVAL;

	err = qib_user_sdma_make_progress(ppd, pq);
	अगर (err < 0)
		वापस err;

	val = qib_user_sdma_complete_counter(pq);
	अगर (put_user(val, completep))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक disarm_req_delay(काष्ठा qib_ctxtdata *rcd)
अणु
	पूर्णांक ret = 0;

	अगर (!usable(rcd->ppd)) अणु
		पूर्णांक i;
		/*
		 * अगर link is करोwn, or otherwise not usable, delay
		 * the caller up to 30 seconds, so we करोn't thrash
		 * in trying to get the chip back to ACTIVE, and
		 * set flag so they make the call again.
		 */
		अगर (rcd->user_event_mask) अणु
			/*
			 * subctxt_cnt is 0 अगर not shared, so करो base
			 * separately, first, then reमुख्यing subctxt, अगर any
			 */
			set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
				&rcd->user_event_mask[0]);
			क्रम (i = 1; i < rcd->subctxt_cnt; i++)
				set_bit(_QIB_EVENT_DISARM_BUFS_BIT,
					&rcd->user_event_mask[i]);
		पूर्ण
		क्रम (i = 0; !usable(rcd->ppd) && i < 300; i++)
			msleep(100);
		ret = -ENETDOWN;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Find all user contexts in use, and set the specअगरied bit in their
 * event mask.
 * See also find_ctxt() क्रम a similar use, that is specअगरic to send buffers.
 */
पूर्णांक qib_set_uevent_bits(काष्ठा qib_pportdata *ppd, स्थिर पूर्णांक evtbit)
अणु
	काष्ठा qib_ctxtdata *rcd;
	अचिन्हित ctxt;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->dd->uctxt_lock, flags);
	क्रम (ctxt = ppd->dd->first_user_ctxt; ctxt < ppd->dd->cfgctxts;
	     ctxt++) अणु
		rcd = ppd->dd->rcd[ctxt];
		अगर (!rcd)
			जारी;
		अगर (rcd->user_event_mask) अणु
			पूर्णांक i;
			/*
			 * subctxt_cnt is 0 अगर not shared, so करो base
			 * separately, first, then reमुख्यing subctxt, अगर any
			 */
			set_bit(evtbit, &rcd->user_event_mask[0]);
			क्रम (i = 1; i < rcd->subctxt_cnt; i++)
				set_bit(evtbit, &rcd->user_event_mask[i]);
		पूर्ण
		ret = 1;
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ppd->dd->uctxt_lock, flags);

	वापस ret;
पूर्ण

/*
 * clear the event notअगरier events क्रम this context.
 * For the DISARM_BUFS हाल, we also take action (this obsoletes
 * the older QIB_CMD_DISARM_BUFS, but we keep it क्रम backwards
 * compatibility.
 * Other bits करोn't currently require actions, just atomically clear.
 * User process then perक्रमms actions appropriate to bit having been
 * set, अगर desired, and checks again in future.
 */
अटल पूर्णांक qib_user_event_ack(काष्ठा qib_ctxtdata *rcd, पूर्णांक subctxt,
			      अचिन्हित दीर्घ events)
अणु
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i <= _QIB_MAX_EVENT_BIT; i++) अणु
		अगर (!test_bit(i, &events))
			जारी;
		अगर (i == _QIB_EVENT_DISARM_BUFS_BIT) अणु
			(व्योम)qib_disarm_piobufs_अगरneeded(rcd);
			ret = disarm_req_delay(rcd);
		पूर्ण अन्यथा
			clear_bit(i, &rcd->user_event_mask[subctxt]);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार qib_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *data,
			 माप_प्रकार count, loff_t *off)
अणु
	स्थिर काष्ठा qib_cmd __user *ucmd;
	काष्ठा qib_ctxtdata *rcd;
	स्थिर व्योम __user *src;
	माप_प्रकार consumed, copy = 0;
	काष्ठा qib_cmd cmd;
	sमाप_प्रकार ret = 0;
	व्योम *dest;

	अगर (!ib_safe_file_access(fp)) अणु
		pr_err_once("qib_write: process %d (%s) changed security contexts after opening file descriptor, this is not allowed.\n",
			    task_tgid_vnr(current), current->comm);
		वापस -EACCES;
	पूर्ण

	अगर (count < माप(cmd.type)) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	ucmd = (स्थिर काष्ठा qib_cmd __user *) data;

	अगर (copy_from_user(&cmd.type, &ucmd->type, माप(cmd.type))) अणु
		ret = -EFAULT;
		जाओ bail;
	पूर्ण

	consumed = माप(cmd.type);

	चयन (cmd.type) अणु
	हाल QIB_CMD_ASSIGN_CTXT:
	हाल QIB_CMD_USER_INIT:
		copy = माप(cmd.cmd.user_info);
		dest = &cmd.cmd.user_info;
		src = &ucmd->cmd.user_info;
		अवरोध;

	हाल QIB_CMD_RECV_CTRL:
		copy = माप(cmd.cmd.recv_ctrl);
		dest = &cmd.cmd.recv_ctrl;
		src = &ucmd->cmd.recv_ctrl;
		अवरोध;

	हाल QIB_CMD_CTXT_INFO:
		copy = माप(cmd.cmd.ctxt_info);
		dest = &cmd.cmd.ctxt_info;
		src = &ucmd->cmd.ctxt_info;
		अवरोध;

	हाल QIB_CMD_TID_UPDATE:
	हाल QIB_CMD_TID_FREE:
		copy = माप(cmd.cmd.tid_info);
		dest = &cmd.cmd.tid_info;
		src = &ucmd->cmd.tid_info;
		अवरोध;

	हाल QIB_CMD_SET_PART_KEY:
		copy = माप(cmd.cmd.part_key);
		dest = &cmd.cmd.part_key;
		src = &ucmd->cmd.part_key;
		अवरोध;

	हाल QIB_CMD_DISARM_BUFS:
	हाल QIB_CMD_PIOAVAILUPD: /* क्रमce an update of PIOAvail reg */
		copy = 0;
		src = शून्य;
		dest = शून्य;
		अवरोध;

	हाल QIB_CMD_POLL_TYPE:
		copy = माप(cmd.cmd.poll_type);
		dest = &cmd.cmd.poll_type;
		src = &ucmd->cmd.poll_type;
		अवरोध;

	हाल QIB_CMD_ARMLAUNCH_CTRL:
		copy = माप(cmd.cmd.armlaunch_ctrl);
		dest = &cmd.cmd.armlaunch_ctrl;
		src = &ucmd->cmd.armlaunch_ctrl;
		अवरोध;

	हाल QIB_CMD_SDMA_INFLIGHT:
		copy = माप(cmd.cmd.sdma_inflight);
		dest = &cmd.cmd.sdma_inflight;
		src = &ucmd->cmd.sdma_inflight;
		अवरोध;

	हाल QIB_CMD_SDMA_COMPLETE:
		copy = माप(cmd.cmd.sdma_complete);
		dest = &cmd.cmd.sdma_complete;
		src = &ucmd->cmd.sdma_complete;
		अवरोध;

	हाल QIB_CMD_ACK_EVENT:
		copy = माप(cmd.cmd.event_mask);
		dest = &cmd.cmd.event_mask;
		src = &ucmd->cmd.event_mask;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	अगर (copy) अणु
		अगर ((count - consumed) < copy) अणु
			ret = -EINVAL;
			जाओ bail;
		पूर्ण
		अगर (copy_from_user(dest, src, copy)) अणु
			ret = -EFAULT;
			जाओ bail;
		पूर्ण
		consumed += copy;
	पूर्ण

	rcd = ctxt_fp(fp);
	अगर (!rcd && cmd.type != QIB_CMD_ASSIGN_CTXT) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	चयन (cmd.type) अणु
	हाल QIB_CMD_ASSIGN_CTXT:
		अगर (rcd) अणु
			ret = -EINVAL;
			जाओ bail;
		पूर्ण

		ret = qib_assign_ctxt(fp, &cmd.cmd.user_info);
		अगर (ret)
			जाओ bail;
		अवरोध;

	हाल QIB_CMD_USER_INIT:
		ret = qib_करो_user_init(fp, &cmd.cmd.user_info);
		अगर (ret)
			जाओ bail;
		ret = qib_get_base_info(fp, u64_to_user_ptr(
					  cmd.cmd.user_info.spu_base_info),
					cmd.cmd.user_info.spu_base_info_size);
		अवरोध;

	हाल QIB_CMD_RECV_CTRL:
		ret = qib_manage_rcvq(rcd, subctxt_fp(fp), cmd.cmd.recv_ctrl);
		अवरोध;

	हाल QIB_CMD_CTXT_INFO:
		ret = qib_ctxt_info(fp, (काष्ठा qib_ctxt_info __user *)
				    (अचिन्हित दीर्घ) cmd.cmd.ctxt_info);
		अवरोध;

	हाल QIB_CMD_TID_UPDATE:
		ret = qib_tid_update(rcd, fp, &cmd.cmd.tid_info);
		अवरोध;

	हाल QIB_CMD_TID_FREE:
		ret = qib_tid_मुक्त(rcd, subctxt_fp(fp), &cmd.cmd.tid_info);
		अवरोध;

	हाल QIB_CMD_SET_PART_KEY:
		ret = qib_set_part_key(rcd, cmd.cmd.part_key);
		अवरोध;

	हाल QIB_CMD_DISARM_BUFS:
		(व्योम)qib_disarm_piobufs_अगरneeded(rcd);
		ret = disarm_req_delay(rcd);
		अवरोध;

	हाल QIB_CMD_PIOAVAILUPD:
		qib_क्रमce_pio_avail_update(rcd->dd);
		अवरोध;

	हाल QIB_CMD_POLL_TYPE:
		rcd->poll_type = cmd.cmd.poll_type;
		अवरोध;

	हाल QIB_CMD_ARMLAUNCH_CTRL:
		rcd->dd->f_set_armlaunch(rcd->dd, cmd.cmd.armlaunch_ctrl);
		अवरोध;

	हाल QIB_CMD_SDMA_INFLIGHT:
		ret = qib_sdma_get_inflight(user_sdma_queue_fp(fp),
					    (u32 __user *) (अचिन्हित दीर्घ)
					    cmd.cmd.sdma_inflight);
		अवरोध;

	हाल QIB_CMD_SDMA_COMPLETE:
		ret = qib_sdma_get_complete(rcd->ppd,
					    user_sdma_queue_fp(fp),
					    (u32 __user *) (अचिन्हित दीर्घ)
					    cmd.cmd.sdma_complete);
		अवरोध;

	हाल QIB_CMD_ACK_EVENT:
		ret = qib_user_event_ack(rcd, subctxt_fp(fp),
					 cmd.cmd.event_mask);
		अवरोध;
	पूर्ण

	अगर (ret >= 0)
		ret = consumed;

bail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार qib_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा qib_filedata *fp = iocb->ki_filp->निजी_data;
	काष्ठा qib_ctxtdata *rcd = ctxt_fp(iocb->ki_filp);
	काष्ठा qib_user_sdma_queue *pq = fp->pq;

	अगर (!iter_is_iovec(from) || !from->nr_segs || !pq)
		वापस -EINVAL;

	वापस qib_user_sdma_ग_लिखोv(rcd, pq, from->iov, from->nr_segs);
पूर्ण

अटल काष्ठा class *qib_class;
अटल dev_t qib_dev;

पूर्णांक qib_cdev_init(पूर्णांक minor, स्थिर अक्षर *name,
		  स्थिर काष्ठा file_operations *fops,
		  काष्ठा cdev **cdevp, काष्ठा device **devp)
अणु
	स्थिर dev_t dev = MKDEV(MAJOR(qib_dev), minor);
	काष्ठा cdev *cdev;
	काष्ठा device *device = शून्य;
	पूर्णांक ret;

	cdev = cdev_alloc();
	अगर (!cdev) अणु
		pr_err("Could not allocate cdev for minor %d, %s\n",
		       minor, name);
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	cdev->owner = THIS_MODULE;
	cdev->ops = fops;
	kobject_set_name(&cdev->kobj, name);

	ret = cdev_add(cdev, dev, 1);
	अगर (ret < 0) अणु
		pr_err("Could not add cdev for minor %d, %s (err %d)\n",
		       minor, name, -ret);
		जाओ err_cdev;
	पूर्ण

	device = device_create(qib_class, शून्य, dev, शून्य, "%s", name);
	अगर (!IS_ERR(device))
		जाओ करोne;
	ret = PTR_ERR(device);
	device = शून्य;
	pr_err("Could not create device for minor %d, %s (err %d)\n",
	       minor, name, -ret);
err_cdev:
	cdev_del(cdev);
	cdev = शून्य;
करोne:
	*cdevp = cdev;
	*devp = device;
	वापस ret;
पूर्ण

व्योम qib_cdev_cleanup(काष्ठा cdev **cdevp, काष्ठा device **devp)
अणु
	काष्ठा device *device = *devp;

	अगर (device) अणु
		device_unरेजिस्टर(device);
		*devp = शून्य;
	पूर्ण

	अगर (*cdevp) अणु
		cdev_del(*cdevp);
		*cdevp = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा cdev *wildcard_cdev;
अटल काष्ठा device *wildcard_device;

पूर्णांक __init qib_dev_init(व्योम)
अणु
	पूर्णांक ret;

	ret = alloc_chrdev_region(&qib_dev, 0, QIB_NMINORS, QIB_DRV_NAME);
	अगर (ret < 0) अणु
		pr_err("Could not allocate chrdev region (err %d)\n", -ret);
		जाओ करोne;
	पूर्ण

	qib_class = class_create(THIS_MODULE, "ipath");
	अगर (IS_ERR(qib_class)) अणु
		ret = PTR_ERR(qib_class);
		pr_err("Could not create device class (err %d)\n", -ret);
		unरेजिस्टर_chrdev_region(qib_dev, QIB_NMINORS);
	पूर्ण

करोne:
	वापस ret;
पूर्ण

व्योम qib_dev_cleanup(व्योम)
अणु
	अगर (qib_class) अणु
		class_destroy(qib_class);
		qib_class = शून्य;
	पूर्ण

	unरेजिस्टर_chrdev_region(qib_dev, QIB_NMINORS);
पूर्ण

अटल atomic_t user_count = ATOMIC_INIT(0);

अटल व्योम qib_user_हटाओ(काष्ठा qib_devdata *dd)
अणु
	अगर (atomic_dec_वापस(&user_count) == 0)
		qib_cdev_cleanup(&wildcard_cdev, &wildcard_device);

	qib_cdev_cleanup(&dd->user_cdev, &dd->user_device);
पूर्ण

अटल पूर्णांक qib_user_add(काष्ठा qib_devdata *dd)
अणु
	अक्षर name[10];
	पूर्णांक ret;

	अगर (atomic_inc_वापस(&user_count) == 1) अणु
		ret = qib_cdev_init(0, "ipath", &qib_file_ops,
				    &wildcard_cdev, &wildcard_device);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	snम_लिखो(name, माप(name), "ipath%d", dd->unit);
	ret = qib_cdev_init(dd->unit + 1, name, &qib_file_ops,
			    &dd->user_cdev, &dd->user_device);
	अगर (ret)
		qib_user_हटाओ(dd);
करोne:
	वापस ret;
पूर्ण

/*
 * Create per-unit files in /dev
 */
पूर्णांक qib_device_create(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक r, ret;

	r = qib_user_add(dd);
	ret = qib_diag_add(dd);
	अगर (r && !ret)
		ret = r;
	वापस ret;
पूर्ण

/*
 * Remove per-unit files in /dev
 * व्योम, core kernel वापसs no errors क्रम this stuff
 */
व्योम qib_device_हटाओ(काष्ठा qib_devdata *dd)
अणु
	qib_user_हटाओ(dd);
	qib_diag_हटाओ(dd);
पूर्ण
