<शैली गुरु>
/*
 * Copyright (c) 2007, 2008, 2009 QLogic Corporation. All rights reserved.
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
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/uपन.स>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>

#समावेश "qib.h"
#समावेश "qib_user_sdma.h"

/* minimum size of header */
#घोषणा QIB_USER_SDMA_MIN_HEADER_LENGTH 64
/* expected size of headers (क्रम dma_pool) */
#घोषणा QIB_USER_SDMA_EXP_HEADER_LENGTH 64
/* attempt to drain the queue क्रम 5secs */
#घोषणा QIB_USER_SDMA_DRAIN_TIMEOUT 250

/*
 * track how many बार a process खोलो this driver.
 */
अटल काष्ठा rb_root qib_user_sdma_rb_root = RB_ROOT;

काष्ठा qib_user_sdma_rb_node अणु
	काष्ठा rb_node node;
	पूर्णांक refcount;
	pid_t pid;
पूर्ण;

काष्ठा qib_user_sdma_pkt अणु
	काष्ठा list_head list;  /* list element */

	u8  tiddma;		/* अगर this is NEW tid-sdma */
	u8  largepkt;		/* this is large pkt from kदो_स्मृति */
	u16 frag_size;		/* frag size used by PSM */
	u16 index;              /* last header index or push index */
	u16 naddr;              /* dimension of addr (1..3) ... */
	u16 addrlimit;		/* addr array size */
	u16 tidsmidx;		/* current tidsm index */
	u16 tidsmcount;		/* tidsm array item count */
	u16 payload_size;	/* payload size so far क्रम header */
	u32 bytes_togo;		/* bytes क्रम processing */
	u32 counter;            /* sdma pkts queued counter क्रम this entry */
	काष्ठा qib_tid_session_member *tidsm;	/* tid session member array */
	काष्ठा qib_user_sdma_queue *pq;	/* which pq this pkt beदीर्घs to */
	u64 added;              /* global descq number of entries */

	काष्ठा अणु
		u16 offset;                     /* offset क्रम kvaddr, addr */
		u16 length;                     /* length in page */
		u16 first_desc;			/* first desc */
		u16 last_desc;			/* last desc */
		u16 put_page;                   /* should we put_page? */
		u16 dma_mapped;                 /* is page dma_mapped? */
		u16 dma_length;			/* क्रम dma_unmap_page() */
		u16 padding;
		काष्ठा page *page;              /* may be शून्य (coherent mem) */
		व्योम *kvaddr;                   /* FIXME: only क्रम pio hack */
		dma_addr_t addr;
	पूर्ण addr[4];   /* max pages, any more and we coalesce */
पूर्ण;

काष्ठा qib_user_sdma_queue अणु
	/*
	 * pkts sent to dma engine are queued on this
	 * list head.  the type of the elements of this
	 * list are काष्ठा qib_user_sdma_pkt...
	 */
	काष्ठा list_head sent;

	/*
	 * Because above list will be accessed by both process and
	 * संकेत handler, we need a spinlock क्रम it.
	 */
	spinlock_t sent_lock ____cacheline_aligned_in_smp;

	/* headers with expected length are allocated from here... */
	अक्षर header_cache_name[64];
	काष्ठा dma_pool *header_cache;

	/* packets are allocated from the slab cache... */
	अक्षर pkt_slab_name[64];
	काष्ठा kmem_cache *pkt_slab;

	/* as packets go on the queued queue, they are counted... */
	u32 counter;
	u32 sent_counter;
	/* pending packets, not sending yet */
	u32 num_pending;
	/* sending packets, not complete yet */
	u32 num_sending;
	/* global descq number of entry of last sending packet */
	u64 added;

	/* dma page table */
	काष्ठा rb_root dma_pages_root;

	काष्ठा qib_user_sdma_rb_node *sdma_rb_node;

	/* protect everything above... */
	काष्ठा mutex lock;
पूर्ण;

अटल काष्ठा qib_user_sdma_rb_node *
qib_user_sdma_rb_search(काष्ठा rb_root *root, pid_t pid)
अणु
	काष्ठा qib_user_sdma_rb_node *sdma_rb_node;
	काष्ठा rb_node *node = root->rb_node;

	जबतक (node) अणु
		sdma_rb_node = rb_entry(node, काष्ठा qib_user_sdma_rb_node,
					node);
		अगर (pid < sdma_rb_node->pid)
			node = node->rb_left;
		अन्यथा अगर (pid > sdma_rb_node->pid)
			node = node->rb_right;
		अन्यथा
			वापस sdma_rb_node;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
qib_user_sdma_rb_insert(काष्ठा rb_root *root, काष्ठा qib_user_sdma_rb_node *new)
अणु
	काष्ठा rb_node **node = &(root->rb_node);
	काष्ठा rb_node *parent = शून्य;
	काष्ठा qib_user_sdma_rb_node *got;

	जबतक (*node) अणु
		got = rb_entry(*node, काष्ठा qib_user_sdma_rb_node, node);
		parent = *node;
		अगर (new->pid < got->pid)
			node = &((*node)->rb_left);
		अन्यथा अगर (new->pid > got->pid)
			node = &((*node)->rb_right);
		अन्यथा
			वापस 0;
	पूर्ण

	rb_link_node(&new->node, parent, node);
	rb_insert_color(&new->node, root);
	वापस 1;
पूर्ण

काष्ठा qib_user_sdma_queue *
qib_user_sdma_queue_create(काष्ठा device *dev, पूर्णांक unit, पूर्णांक ctxt, पूर्णांक sctxt)
अणु
	काष्ठा qib_user_sdma_queue *pq =
		kदो_स्मृति(माप(काष्ठा qib_user_sdma_queue), GFP_KERNEL);
	काष्ठा qib_user_sdma_rb_node *sdma_rb_node;

	अगर (!pq)
		जाओ करोne;

	pq->counter = 0;
	pq->sent_counter = 0;
	pq->num_pending = 0;
	pq->num_sending = 0;
	pq->added = 0;
	pq->sdma_rb_node = शून्य;

	INIT_LIST_HEAD(&pq->sent);
	spin_lock_init(&pq->sent_lock);
	mutex_init(&pq->lock);

	snम_लिखो(pq->pkt_slab_name, माप(pq->pkt_slab_name),
		 "qib-user-sdma-pkts-%u-%02u.%02u", unit, ctxt, sctxt);
	pq->pkt_slab = kmem_cache_create(pq->pkt_slab_name,
					 माप(काष्ठा qib_user_sdma_pkt),
					 0, 0, शून्य);

	अगर (!pq->pkt_slab)
		जाओ err_kमुक्त;

	snम_लिखो(pq->header_cache_name, माप(pq->header_cache_name),
		 "qib-user-sdma-headers-%u-%02u.%02u", unit, ctxt, sctxt);
	pq->header_cache = dma_pool_create(pq->header_cache_name,
					   dev,
					   QIB_USER_SDMA_EXP_HEADER_LENGTH,
					   4, 0);
	अगर (!pq->header_cache)
		जाओ err_slab;

	pq->dma_pages_root = RB_ROOT;

	sdma_rb_node = qib_user_sdma_rb_search(&qib_user_sdma_rb_root,
					current->pid);
	अगर (sdma_rb_node) अणु
		sdma_rb_node->refcount++;
	पूर्ण अन्यथा अणु
		sdma_rb_node = kदो_स्मृति(माप(
			काष्ठा qib_user_sdma_rb_node), GFP_KERNEL);
		अगर (!sdma_rb_node)
			जाओ err_rb;

		sdma_rb_node->refcount = 1;
		sdma_rb_node->pid = current->pid;

		qib_user_sdma_rb_insert(&qib_user_sdma_rb_root, sdma_rb_node);
	पूर्ण
	pq->sdma_rb_node = sdma_rb_node;

	जाओ करोne;

err_rb:
	dma_pool_destroy(pq->header_cache);
err_slab:
	kmem_cache_destroy(pq->pkt_slab);
err_kमुक्त:
	kमुक्त(pq);
	pq = शून्य;

करोne:
	वापस pq;
पूर्ण

अटल व्योम qib_user_sdma_init_frag(काष्ठा qib_user_sdma_pkt *pkt,
				    पूर्णांक i, u16 offset, u16 len,
				    u16 first_desc, u16 last_desc,
				    u16 put_page, u16 dma_mapped,
				    काष्ठा page *page, व्योम *kvaddr,
				    dma_addr_t dma_addr, u16 dma_length)
अणु
	pkt->addr[i].offset = offset;
	pkt->addr[i].length = len;
	pkt->addr[i].first_desc = first_desc;
	pkt->addr[i].last_desc = last_desc;
	pkt->addr[i].put_page = put_page;
	pkt->addr[i].dma_mapped = dma_mapped;
	pkt->addr[i].page = page;
	pkt->addr[i].kvaddr = kvaddr;
	pkt->addr[i].addr = dma_addr;
	pkt->addr[i].dma_length = dma_length;
पूर्ण

अटल व्योम *qib_user_sdma_alloc_header(काष्ठा qib_user_sdma_queue *pq,
				माप_प्रकार len, dma_addr_t *dma_addr)
अणु
	व्योम *hdr;

	अगर (len == QIB_USER_SDMA_EXP_HEADER_LENGTH)
		hdr = dma_pool_alloc(pq->header_cache, GFP_KERNEL,
					     dma_addr);
	अन्यथा
		hdr = शून्य;

	अगर (!hdr) अणु
		hdr = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!hdr)
			वापस शून्य;

		*dma_addr = 0;
	पूर्ण

	वापस hdr;
पूर्ण

अटल पूर्णांक qib_user_sdma_page_to_frags(स्थिर काष्ठा qib_devdata *dd,
				       काष्ठा qib_user_sdma_queue *pq,
				       काष्ठा qib_user_sdma_pkt *pkt,
				       काष्ठा page *page, u16 put,
				       u16 offset, u16 len, व्योम *kvaddr)
अणु
	__le16 *pbc16;
	व्योम *pbcvaddr;
	काष्ठा qib_message_header *hdr;
	u16 newlen, pbclen, lastdesc, dma_mapped;
	u32 vcto;
	जोड़ qib_seqnum seqnum;
	dma_addr_t pbcdaddr;
	dma_addr_t dma_addr =
		dma_map_page(&dd->pcidev->dev,
			page, offset, len, DMA_TO_DEVICE);
	पूर्णांक ret = 0;

	अगर (dma_mapping_error(&dd->pcidev->dev, dma_addr)) अणु
		/*
		 * dma mapping error, pkt has not managed
		 * this page yet, वापस the page here so
		 * the caller can ignore this page.
		 */
		अगर (put) अणु
			unpin_user_page(page);
		पूर्ण अन्यथा अणु
			/* coalesce हाल */
			kunmap(page);
			__मुक्त_page(page);
		पूर्ण
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण
	offset = 0;
	dma_mapped = 1;


next_fragment:

	/*
	 * In tid-sdma, the transfer length is restricted by
	 * receiver side current tid page length.
	 */
	अगर (pkt->tiddma && len > pkt->tidsm[pkt->tidsmidx].length)
		newlen = pkt->tidsm[pkt->tidsmidx].length;
	अन्यथा
		newlen = len;

	/*
	 * Then the transfer length is restricted by MTU.
	 * the last descriptor flag is determined by:
	 * 1. the current packet is at frag size length.
	 * 2. the current tid page is करोne अगर tid-sdma.
	 * 3. there is no more byte togo अगर sdma.
	 */
	lastdesc = 0;
	अगर ((pkt->payload_size + newlen) >= pkt->frag_size) अणु
		newlen = pkt->frag_size - pkt->payload_size;
		lastdesc = 1;
	पूर्ण अन्यथा अगर (pkt->tiddma) अणु
		अगर (newlen == pkt->tidsm[pkt->tidsmidx].length)
			lastdesc = 1;
	पूर्ण अन्यथा अणु
		अगर (newlen == pkt->bytes_togo)
			lastdesc = 1;
	पूर्ण

	/* fill the next fragment in this page */
	qib_user_sdma_init_frag(pkt, pkt->naddr, /* index */
		offset, newlen,		/* offset, len */
		0, lastdesc,		/* first last desc */
		put, dma_mapped,	/* put page, dma mapped */
		page, kvaddr,		/* काष्ठा page, virt addr */
		dma_addr, len);		/* dma addr, dma length */
	pkt->bytes_togo -= newlen;
	pkt->payload_size += newlen;
	pkt->naddr++;
	अगर (pkt->naddr == pkt->addrlimit) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण

	/* If there is no more byte togo. (lastdesc==1) */
	अगर (pkt->bytes_togo == 0) अणु
		/* The packet is करोne, header is not dma mapped yet.
		 * it should be from kदो_स्मृति */
		अगर (!pkt->addr[pkt->index].addr) अणु
			pkt->addr[pkt->index].addr =
				dma_map_single(&dd->pcidev->dev,
					pkt->addr[pkt->index].kvaddr,
					pkt->addr[pkt->index].dma_length,
					DMA_TO_DEVICE);
			अगर (dma_mapping_error(&dd->pcidev->dev,
					pkt->addr[pkt->index].addr)) अणु
				ret = -ENOMEM;
				जाओ करोne;
			पूर्ण
			pkt->addr[pkt->index].dma_mapped = 1;
		पूर्ण

		जाओ करोne;
	पूर्ण

	/* If tid-sdma, advance tid info. */
	अगर (pkt->tiddma) अणु
		pkt->tidsm[pkt->tidsmidx].length -= newlen;
		अगर (pkt->tidsm[pkt->tidsmidx].length) अणु
			pkt->tidsm[pkt->tidsmidx].offset += newlen;
		पूर्ण अन्यथा अणु
			pkt->tidsmidx++;
			अगर (pkt->tidsmidx == pkt->tidsmcount) अणु
				ret = -EFAULT;
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If this is NOT the last descriptor. (newlen==len)
	 * the current packet is not करोne yet, but the current
	 * send side page is करोne.
	 */
	अगर (lastdesc == 0)
		जाओ करोne;

	/*
	 * If running this driver under PSM with message size
	 * fitting पूर्णांकo one transfer unit, it is not possible
	 * to pass this line. otherwise, it is a buggggg.
	 */

	/*
	 * Since the current packet is करोne, and there are more
	 * bytes togo, we need to create a new sdma header, copying
	 * from previous sdma header and modअगरy both.
	 */
	pbclen = pkt->addr[pkt->index].length;
	pbcvaddr = qib_user_sdma_alloc_header(pq, pbclen, &pbcdaddr);
	अगर (!pbcvaddr) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण
	/* Copy the previous sdma header to new sdma header */
	pbc16 = (__le16 *)pkt->addr[pkt->index].kvaddr;
	स_नकल(pbcvaddr, pbc16, pbclen);

	/* Modअगरy the previous sdma header */
	hdr = (काष्ठा qib_message_header *)&pbc16[4];

	/* New pbc length */
	pbc16[0] = cpu_to_le16(le16_to_cpu(pbc16[0])-(pkt->bytes_togo>>2));

	/* New packet length */
	hdr->lrh[2] = cpu_to_be16(le16_to_cpu(pbc16[0]));

	अगर (pkt->tiddma) अणु
		/* turn on the header suppression */
		hdr->iph.pkt_flags =
			cpu_to_le16(le16_to_cpu(hdr->iph.pkt_flags)|0x2);
		/* turn off ACK_REQ: 0x04 and EXPECTED_DONE: 0x20 */
		hdr->flags &= ~(0x04|0x20);
	पूर्ण अन्यथा अणु
		/* turn off extra bytes: 20-21 bits */
		hdr->bth[0] = cpu_to_be32(be32_to_cpu(hdr->bth[0])&0xFFCFFFFF);
		/* turn off ACK_REQ: 0x04 */
		hdr->flags &= ~(0x04);
	पूर्ण

	/* New kdeth checksum */
	vcto = le32_to_cpu(hdr->iph.ver_ctxt_tid_offset);
	hdr->iph.chksum = cpu_to_le16(QIB_LRH_BTH +
		be16_to_cpu(hdr->lrh[2]) -
		((vcto>>16)&0xFFFF) - (vcto&0xFFFF) -
		le16_to_cpu(hdr->iph.pkt_flags));

	/* The packet is करोne, header is not dma mapped yet.
	 * it should be from kदो_स्मृति */
	अगर (!pkt->addr[pkt->index].addr) अणु
		pkt->addr[pkt->index].addr =
			dma_map_single(&dd->pcidev->dev,
				pkt->addr[pkt->index].kvaddr,
				pkt->addr[pkt->index].dma_length,
				DMA_TO_DEVICE);
		अगर (dma_mapping_error(&dd->pcidev->dev,
				pkt->addr[pkt->index].addr)) अणु
			ret = -ENOMEM;
			जाओ करोne;
		पूर्ण
		pkt->addr[pkt->index].dma_mapped = 1;
	पूर्ण

	/* Modअगरy the new sdma header */
	pbc16 = (__le16 *)pbcvaddr;
	hdr = (काष्ठा qib_message_header *)&pbc16[4];

	/* New pbc length */
	pbc16[0] = cpu_to_le16(le16_to_cpu(pbc16[0])-(pkt->payload_size>>2));

	/* New packet length */
	hdr->lrh[2] = cpu_to_be16(le16_to_cpu(pbc16[0]));

	अगर (pkt->tiddma) अणु
		/* Set new tid and offset क्रम new sdma header */
		hdr->iph.ver_ctxt_tid_offset = cpu_to_le32(
			(le32_to_cpu(hdr->iph.ver_ctxt_tid_offset)&0xFF000000) +
			(pkt->tidsm[pkt->tidsmidx].tid<<QLOGIC_IB_I_TID_SHIFT) +
			(pkt->tidsm[pkt->tidsmidx].offset>>2));
	पूर्ण अन्यथा अणु
		/* Middle protocol new packet offset */
		hdr->uwords[2] += pkt->payload_size;
	पूर्ण

	/* New kdeth checksum */
	vcto = le32_to_cpu(hdr->iph.ver_ctxt_tid_offset);
	hdr->iph.chksum = cpu_to_le16(QIB_LRH_BTH +
		be16_to_cpu(hdr->lrh[2]) -
		((vcto>>16)&0xFFFF) - (vcto&0xFFFF) -
		le16_to_cpu(hdr->iph.pkt_flags));

	/* Next sequence number in new sdma header */
	seqnum.val = be32_to_cpu(hdr->bth[2]);
	अगर (pkt->tiddma)
		seqnum.seq++;
	अन्यथा
		seqnum.pkt++;
	hdr->bth[2] = cpu_to_be32(seqnum.val);

	/* Init new sdma header. */
	qib_user_sdma_init_frag(pkt, pkt->naddr, /* index */
		0, pbclen,		/* offset, len */
		1, 0,			/* first last desc */
		0, 0,			/* put page, dma mapped */
		शून्य, pbcvaddr,		/* काष्ठा page, virt addr */
		pbcdaddr, pbclen);	/* dma addr, dma length */
	pkt->index = pkt->naddr;
	pkt->payload_size = 0;
	pkt->naddr++;
	अगर (pkt->naddr == pkt->addrlimit) अणु
		ret = -EFAULT;
		जाओ करोne;
	पूर्ण

	/* Prepare क्रम next fragment in this page */
	अगर (newlen != len) अणु
		अगर (dma_mapped) अणु
			put = 0;
			dma_mapped = 0;
			page = शून्य;
			kvaddr = शून्य;
		पूर्ण
		len -= newlen;
		offset += newlen;

		जाओ next_fragment;
	पूर्ण

करोne:
	वापस ret;
पूर्ण

/* we've too many pages in the iovec, coalesce to a single page */
अटल पूर्णांक qib_user_sdma_coalesce(स्थिर काष्ठा qib_devdata *dd,
				  काष्ठा qib_user_sdma_queue *pq,
				  काष्ठा qib_user_sdma_pkt *pkt,
				  स्थिर काष्ठा iovec *iov,
				  अचिन्हित दीर्घ niov)
अणु
	पूर्णांक ret = 0;
	काष्ठा page *page = alloc_page(GFP_KERNEL);
	व्योम *mpage_save;
	अक्षर *mpage;
	पूर्णांक i;
	पूर्णांक len = 0;

	अगर (!page) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	mpage = kmap(page);
	mpage_save = mpage;
	क्रम (i = 0; i < niov; i++) अणु
		पूर्णांक cfur;

		cfur = copy_from_user(mpage,
				      iov[i].iov_base, iov[i].iov_len);
		अगर (cfur) अणु
			ret = -EFAULT;
			जाओ मुक्त_unmap;
		पूर्ण

		mpage += iov[i].iov_len;
		len += iov[i].iov_len;
	पूर्ण

	ret = qib_user_sdma_page_to_frags(dd, pq, pkt,
			page, 0, 0, len, mpage_save);
	जाओ करोne;

मुक्त_unmap:
	kunmap(page);
	__मुक्त_page(page);
करोne:
	वापस ret;
पूर्ण

/*
 * How many pages in this iovec element?
 */
अटल पूर्णांक qib_user_sdma_num_pages(स्थिर काष्ठा iovec *iov)
अणु
	स्थिर अचिन्हित दीर्घ addr  = (अचिन्हित दीर्घ) iov->iov_base;
	स्थिर अचिन्हित दीर्घ  len  = iov->iov_len;
	स्थिर अचिन्हित दीर्घ spage = addr & PAGE_MASK;
	स्थिर अचिन्हित दीर्घ epage = (addr + len - 1) & PAGE_MASK;

	वापस 1 + ((epage - spage) >> PAGE_SHIFT);
पूर्ण

अटल व्योम qib_user_sdma_मुक्त_pkt_frag(काष्ठा device *dev,
					काष्ठा qib_user_sdma_queue *pq,
					काष्ठा qib_user_sdma_pkt *pkt,
					पूर्णांक frag)
अणु
	स्थिर पूर्णांक i = frag;

	अगर (pkt->addr[i].page) अणु
		/* only user data has page */
		अगर (pkt->addr[i].dma_mapped)
			dma_unmap_page(dev,
				       pkt->addr[i].addr,
				       pkt->addr[i].dma_length,
				       DMA_TO_DEVICE);

		अगर (pkt->addr[i].kvaddr)
			kunmap(pkt->addr[i].page);

		अगर (pkt->addr[i].put_page)
			unpin_user_page(pkt->addr[i].page);
		अन्यथा
			__मुक्त_page(pkt->addr[i].page);
	पूर्ण अन्यथा अगर (pkt->addr[i].kvaddr) अणु
		/* क्रम headers */
		अगर (pkt->addr[i].dma_mapped) अणु
			/* from kदो_स्मृति & dma mapped */
			dma_unmap_single(dev,
				       pkt->addr[i].addr,
				       pkt->addr[i].dma_length,
				       DMA_TO_DEVICE);
			kमुक्त(pkt->addr[i].kvaddr);
		पूर्ण अन्यथा अगर (pkt->addr[i].addr) अणु
			/* मुक्त coherent mem from cache... */
			dma_pool_मुक्त(pq->header_cache,
			      pkt->addr[i].kvaddr, pkt->addr[i].addr);
		पूर्ण अन्यथा अणु
			/* from kदो_स्मृति but not dma mapped */
			kमुक्त(pkt->addr[i].kvaddr);
		पूर्ण
	पूर्ण
पूर्ण

/* वापस number of pages pinned... */
अटल पूर्णांक qib_user_sdma_pin_pages(स्थिर काष्ठा qib_devdata *dd,
				   काष्ठा qib_user_sdma_queue *pq,
				   काष्ठा qib_user_sdma_pkt *pkt,
				   अचिन्हित दीर्घ addr, पूर्णांक tlen, पूर्णांक npages)
अणु
	काष्ठा page *pages[8];
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	जबतक (npages) अणु
		अगर (npages > 8)
			j = 8;
		अन्यथा
			j = npages;

		ret = pin_user_pages_fast(addr, j, FOLL_LONGTERM, pages);
		अगर (ret != j) अणु
			i = 0;
			j = ret;
			ret = -ENOMEM;
			जाओ मुक्त_pages;
		पूर्ण

		क्रम (i = 0; i < j; i++) अणु
			/* map the pages... */
			अचिन्हित दीर्घ fofs = addr & ~PAGE_MASK;
			पूर्णांक flen = ((fofs + tlen) > PAGE_SIZE) ?
				(PAGE_SIZE - fofs) : tlen;

			ret = qib_user_sdma_page_to_frags(dd, pq, pkt,
				pages[i], 1, fofs, flen, शून्य);
			अगर (ret < 0) अणु
				/* current page has beed taken
				 * care of inside above call.
				 */
				i++;
				जाओ मुक्त_pages;
			पूर्ण

			addr += flen;
			tlen -= flen;
		पूर्ण

		npages -= j;
	पूर्ण

	जाओ करोne;

	/* अगर error, वापस all pages not managed by pkt */
मुक्त_pages:
	जबतक (i < j)
		unpin_user_page(pages[i++]);

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_user_sdma_pin_pkt(स्थिर काष्ठा qib_devdata *dd,
				 काष्ठा qib_user_sdma_queue *pq,
				 काष्ठा qib_user_sdma_pkt *pkt,
				 स्थिर काष्ठा iovec *iov,
				 अचिन्हित दीर्घ niov)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ idx;

	क्रम (idx = 0; idx < niov; idx++) अणु
		स्थिर पूर्णांक npages = qib_user_sdma_num_pages(iov + idx);
		स्थिर अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) iov[idx].iov_base;

		ret = qib_user_sdma_pin_pages(dd, pq, pkt, addr,
					      iov[idx].iov_len, npages);
		अगर (ret < 0)
			जाओ मुक्त_pkt;
	पूर्ण

	जाओ करोne;

मुक्त_pkt:
	/* we need to ignore the first entry here */
	क्रम (idx = 1; idx < pkt->naddr; idx++)
		qib_user_sdma_मुक्त_pkt_frag(&dd->pcidev->dev, pq, pkt, idx);

	/* need to dma unmap the first entry, this is to restore to
	 * the original state so that caller can मुक्त the memory in
	 * error condition. Caller करोes not know अगर dma mapped or not*/
	अगर (pkt->addr[0].dma_mapped) अणु
		dma_unmap_single(&dd->pcidev->dev,
		       pkt->addr[0].addr,
		       pkt->addr[0].dma_length,
		       DMA_TO_DEVICE);
		pkt->addr[0].addr = 0;
		pkt->addr[0].dma_mapped = 0;
	पूर्ण

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_user_sdma_init_payload(स्थिर काष्ठा qib_devdata *dd,
				      काष्ठा qib_user_sdma_queue *pq,
				      काष्ठा qib_user_sdma_pkt *pkt,
				      स्थिर काष्ठा iovec *iov,
				      अचिन्हित दीर्घ niov, पूर्णांक npages)
अणु
	पूर्णांक ret = 0;

	अगर (pkt->frag_size == pkt->bytes_togo &&
			npages >= ARRAY_SIZE(pkt->addr))
		ret = qib_user_sdma_coalesce(dd, pq, pkt, iov, niov);
	अन्यथा
		ret = qib_user_sdma_pin_pkt(dd, pq, pkt, iov, niov);

	वापस ret;
पूर्ण

/* मुक्त a packet list -- वापस counter value of last packet */
अटल व्योम qib_user_sdma_मुक्त_pkt_list(काष्ठा device *dev,
					काष्ठा qib_user_sdma_queue *pq,
					काष्ठा list_head *list)
अणु
	काष्ठा qib_user_sdma_pkt *pkt, *pkt_next;

	list_क्रम_each_entry_safe(pkt, pkt_next, list, list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < pkt->naddr; i++)
			qib_user_sdma_मुक्त_pkt_frag(dev, pq, pkt, i);

		अगर (pkt->largepkt)
			kमुक्त(pkt);
		अन्यथा
			kmem_cache_मुक्त(pq->pkt_slab, pkt);
	पूर्ण
	INIT_LIST_HEAD(list);
पूर्ण

/*
 * copy headers, coalesce etc -- pq->lock must be held
 *
 * we queue all the packets to list, वापसing the
 * number of bytes total.  list must be empty initially,
 * as, अगर there is an error we clean it...
 */
अटल पूर्णांक qib_user_sdma_queue_pkts(स्थिर काष्ठा qib_devdata *dd,
				    काष्ठा qib_pportdata *ppd,
				    काष्ठा qib_user_sdma_queue *pq,
				    स्थिर काष्ठा iovec *iov,
				    अचिन्हित दीर्घ niov,
				    काष्ठा list_head *list,
				    पूर्णांक *maxpkts, पूर्णांक *ndesc)
अणु
	अचिन्हित दीर्घ idx = 0;
	पूर्णांक ret = 0;
	पूर्णांक npkts = 0;
	__le32 *pbc;
	dma_addr_t dma_addr;
	काष्ठा qib_user_sdma_pkt *pkt = शून्य;
	माप_प्रकार len;
	माप_प्रकार nw;
	u32 counter = pq->counter;
	u16 frag_size;

	जबतक (idx < niov && npkts < *maxpkts) अणु
		स्थिर अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) iov[idx].iov_base;
		स्थिर अचिन्हित दीर्घ idx_save = idx;
		अचिन्हित pktnw;
		अचिन्हित pktnwc;
		पूर्णांक nfrags = 0;
		पूर्णांक npages = 0;
		पूर्णांक bytes_togo = 0;
		पूर्णांक tiddma = 0;
		पूर्णांक cfur;

		len = iov[idx].iov_len;
		nw = len >> 2;

		अगर (len < QIB_USER_SDMA_MIN_HEADER_LENGTH ||
		    len > PAGE_SIZE || len & 3 || addr & 3) अणु
			ret = -EINVAL;
			जाओ मुक्त_list;
		पूर्ण

		pbc = qib_user_sdma_alloc_header(pq, len, &dma_addr);
		अगर (!pbc) अणु
			ret = -ENOMEM;
			जाओ मुक्त_list;
		पूर्ण

		cfur = copy_from_user(pbc, iov[idx].iov_base, len);
		अगर (cfur) अणु
			ret = -EFAULT;
			जाओ मुक्त_pbc;
		पूर्ण

		/*
		 * This assignment is a bit strange.  it's because the
		 * the pbc counts the number of 32 bit words in the full
		 * packet _except_ the first word of the pbc itself...
		 */
		pktnwc = nw - 1;

		/*
		 * pktnw computation yields the number of 32 bit words
		 * that the caller has indicated in the PBC.  note that
		 * this is one less than the total number of words that
		 * goes to the send DMA engine as the first 32 bit word
		 * of the PBC itself is not counted.  Armed with this count,
		 * we can verअगरy that the packet is consistent with the
		 * iovec lengths.
		 */
		pktnw = le32_to_cpu(*pbc) & 0xFFFF;
		अगर (pktnw < pktnwc) अणु
			ret = -EINVAL;
			जाओ मुक्त_pbc;
		पूर्ण

		idx++;
		जबतक (pktnwc < pktnw && idx < niov) अणु
			स्थिर माप_प्रकार slen = iov[idx].iov_len;
			स्थिर अचिन्हित दीर्घ faddr =
				(अचिन्हित दीर्घ) iov[idx].iov_base;

			अगर (slen & 3 || faddr & 3 || !slen) अणु
				ret = -EINVAL;
				जाओ मुक्त_pbc;
			पूर्ण

			npages += qib_user_sdma_num_pages(&iov[idx]);

			bytes_togo += slen;
			pktnwc += slen >> 2;
			idx++;
			nfrags++;
		पूर्ण

		अगर (pktnwc != pktnw) अणु
			ret = -EINVAL;
			जाओ मुक्त_pbc;
		पूर्ण

		frag_size = ((le32_to_cpu(*pbc))>>16) & 0xFFFF;
		अगर (((frag_size ? frag_size : bytes_togo) + len) >
						ppd->ibmaxlen) अणु
			ret = -EINVAL;
			जाओ मुक्त_pbc;
		पूर्ण

		अगर (frag_size) अणु
			पूर्णांक tidsmsize, n;
			माप_प्रकार pktsize;

			n = npages*((2*PAGE_SIZE/frag_size)+1);
			pktsize = काष्ठा_size(pkt, addr, n);

			/*
			 * Determine अगर this is tid-sdma or just sdma.
			 */
			tiddma = (((le32_to_cpu(pbc[7])>>
				QLOGIC_IB_I_TID_SHIFT)&
				QLOGIC_IB_I_TID_MASK) !=
				QLOGIC_IB_I_TID_MASK);

			अगर (tiddma)
				tidsmsize = iov[idx].iov_len;
			अन्यथा
				tidsmsize = 0;

			pkt = kदो_स्मृति(pktsize+tidsmsize, GFP_KERNEL);
			अगर (!pkt) अणु
				ret = -ENOMEM;
				जाओ मुक्त_pbc;
			पूर्ण
			pkt->largepkt = 1;
			pkt->frag_size = frag_size;
			pkt->addrlimit = n + ARRAY_SIZE(pkt->addr);

			अगर (tiddma) अणु
				अक्षर *tidsm = (अक्षर *)pkt + pktsize;

				cfur = copy_from_user(tidsm,
					iov[idx].iov_base, tidsmsize);
				अगर (cfur) अणु
					ret = -EFAULT;
					जाओ मुक्त_pkt;
				पूर्ण
				pkt->tidsm =
					(काष्ठा qib_tid_session_member *)tidsm;
				pkt->tidsmcount = tidsmsize/
					माप(काष्ठा qib_tid_session_member);
				pkt->tidsmidx = 0;
				idx++;
			पूर्ण

			/*
			 * pbc 'fill1' field is borrowed to pass frag size,
			 * we need to clear it after picking frag size, the
			 * hardware requires this field to be zero.
			 */
			*pbc = cpu_to_le32(le32_to_cpu(*pbc) & 0x0000FFFF);
		पूर्ण अन्यथा अणु
			pkt = kmem_cache_alloc(pq->pkt_slab, GFP_KERNEL);
			अगर (!pkt) अणु
				ret = -ENOMEM;
				जाओ मुक्त_pbc;
			पूर्ण
			pkt->largepkt = 0;
			pkt->frag_size = bytes_togo;
			pkt->addrlimit = ARRAY_SIZE(pkt->addr);
		पूर्ण
		pkt->bytes_togo = bytes_togo;
		pkt->payload_size = 0;
		pkt->counter = counter;
		pkt->tiddma = tiddma;

		/* setup the first header */
		qib_user_sdma_init_frag(pkt, 0, /* index */
			0, len,		/* offset, len */
			1, 0,		/* first last desc */
			0, 0,		/* put page, dma mapped */
			शून्य, pbc,	/* काष्ठा page, virt addr */
			dma_addr, len);	/* dma addr, dma length */
		pkt->index = 0;
		pkt->naddr = 1;

		अगर (nfrags) अणु
			ret = qib_user_sdma_init_payload(dd, pq, pkt,
							 iov + idx_save + 1,
							 nfrags, npages);
			अगर (ret < 0)
				जाओ मुक्त_pkt;
		पूर्ण अन्यथा अणु
			/* since there is no payload, mark the
			 * header as the last desc. */
			pkt->addr[0].last_desc = 1;

			अगर (dma_addr == 0) अणु
				/*
				 * the header is not dma mapped yet.
				 * it should be from kदो_स्मृति.
				 */
				dma_addr = dma_map_single(&dd->pcidev->dev,
					pbc, len, DMA_TO_DEVICE);
				अगर (dma_mapping_error(&dd->pcidev->dev,
								dma_addr)) अणु
					ret = -ENOMEM;
					जाओ मुक्त_pkt;
				पूर्ण
				pkt->addr[0].addr = dma_addr;
				pkt->addr[0].dma_mapped = 1;
			पूर्ण
		पूर्ण

		counter++;
		npkts++;
		pkt->pq = pq;
		pkt->index = 0; /* reset index क्रम push on hw */
		*ndesc += pkt->naddr;

		list_add_tail(&pkt->list, list);
	पूर्ण

	*maxpkts = npkts;
	ret = idx;
	जाओ करोne;

मुक्त_pkt:
	अगर (pkt->largepkt)
		kमुक्त(pkt);
	अन्यथा
		kmem_cache_मुक्त(pq->pkt_slab, pkt);
मुक्त_pbc:
	अगर (dma_addr)
		dma_pool_मुक्त(pq->header_cache, pbc, dma_addr);
	अन्यथा
		kमुक्त(pbc);
मुक्त_list:
	qib_user_sdma_मुक्त_pkt_list(&dd->pcidev->dev, pq, list);
करोne:
	वापस ret;
पूर्ण

अटल व्योम qib_user_sdma_set_complete_counter(काष्ठा qib_user_sdma_queue *pq,
					       u32 c)
अणु
	pq->sent_counter = c;
पूर्ण

/* try to clean out queue -- needs pq->lock */
अटल पूर्णांक qib_user_sdma_queue_clean(काष्ठा qib_pportdata *ppd,
				     काष्ठा qib_user_sdma_queue *pq)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	काष्ठा list_head मुक्त_list;
	काष्ठा qib_user_sdma_pkt *pkt;
	काष्ठा qib_user_sdma_pkt *pkt_prev;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!pq->num_sending)
		वापस 0;

	INIT_LIST_HEAD(&मुक्त_list);

	/*
	 * We need this spin lock here because पूर्णांकerrupt handler
	 * might modअगरy this list in qib_user_sdma_send_desc(), also
	 * we can not get पूर्णांकerrupted, otherwise it is a deadlock.
	 */
	spin_lock_irqsave(&pq->sent_lock, flags);
	list_क्रम_each_entry_safe(pkt, pkt_prev, &pq->sent, list) अणु
		s64 descd = ppd->sdma_descq_हटाओd - pkt->added;

		अगर (descd < 0)
			अवरोध;

		list_move_tail(&pkt->list, &मुक्त_list);

		/* one more packet cleaned */
		ret++;
		pq->num_sending--;
	पूर्ण
	spin_unlock_irqrestore(&pq->sent_lock, flags);

	अगर (!list_empty(&मुक्त_list)) अणु
		u32 counter;

		pkt = list_entry(मुक्त_list.prev,
				 काष्ठा qib_user_sdma_pkt, list);
		counter = pkt->counter;

		qib_user_sdma_मुक्त_pkt_list(&dd->pcidev->dev, pq, &मुक्त_list);
		qib_user_sdma_set_complete_counter(pq, counter);
	पूर्ण

	वापस ret;
पूर्ण

व्योम qib_user_sdma_queue_destroy(काष्ठा qib_user_sdma_queue *pq)
अणु
	अगर (!pq)
		वापस;

	pq->sdma_rb_node->refcount--;
	अगर (pq->sdma_rb_node->refcount == 0) अणु
		rb_erase(&pq->sdma_rb_node->node, &qib_user_sdma_rb_root);
		kमुक्त(pq->sdma_rb_node);
	पूर्ण
	dma_pool_destroy(pq->header_cache);
	kmem_cache_destroy(pq->pkt_slab);
	kमुक्त(pq);
पूर्ण

/* clean descriptor queue, वापसs > 0 अगर some elements cleaned */
अटल पूर्णांक qib_user_sdma_hwqueue_clean(काष्ठा qib_pportdata *ppd)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);
	ret = qib_sdma_make_progress(ppd);
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);

	वापस ret;
पूर्ण

/* we're in बंद, drain packets so that we can cleanup successfully... */
व्योम qib_user_sdma_queue_drain(काष्ठा qib_pportdata *ppd,
			       काष्ठा qib_user_sdma_queue *pq)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (!pq)
		वापस;

	क्रम (i = 0; i < QIB_USER_SDMA_DRAIN_TIMEOUT; i++) अणु
		mutex_lock(&pq->lock);
		अगर (!pq->num_pending && !pq->num_sending) अणु
			mutex_unlock(&pq->lock);
			अवरोध;
		पूर्ण
		qib_user_sdma_hwqueue_clean(ppd);
		qib_user_sdma_queue_clean(ppd, pq);
		mutex_unlock(&pq->lock);
		msleep(20);
	पूर्ण

	अगर (pq->num_pending || pq->num_sending) अणु
		काष्ठा qib_user_sdma_pkt *pkt;
		काष्ठा qib_user_sdma_pkt *pkt_prev;
		काष्ठा list_head मुक्त_list;

		mutex_lock(&pq->lock);
		spin_lock_irqsave(&ppd->sdma_lock, flags);
		/*
		 * Since we hold sdma_lock, it is safe without sent_lock.
		 */
		अगर (pq->num_pending) अणु
			list_क्रम_each_entry_safe(pkt, pkt_prev,
					&ppd->sdma_userpending, list) अणु
				अगर (pkt->pq == pq) अणु
					list_move_tail(&pkt->list, &pq->sent);
					pq->num_pending--;
					pq->num_sending++;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&ppd->sdma_lock, flags);

		qib_dev_err(dd, "user sdma lists not empty: forcing!\n");
		INIT_LIST_HEAD(&मुक्त_list);
		list_splice_init(&pq->sent, &मुक्त_list);
		pq->num_sending = 0;
		qib_user_sdma_मुक्त_pkt_list(&dd->pcidev->dev, pq, &मुक्त_list);
		mutex_unlock(&pq->lock);
	पूर्ण
पूर्ण

अटल अंतरभूत __le64 qib_sdma_make_desc0(u8 gen,
					 u64 addr, u64 dwlen, u64 dwoffset)
अणु
	वापस cpu_to_le64(/* SDmaPhyAddr[31:0] */
			   ((addr & 0xfffffffcULL) << 32) |
			   /* SDmaGeneration[1:0] */
			   ((gen & 3ULL) << 30) |
			   /* SDmaDwordCount[10:0] */
			   ((dwlen & 0x7ffULL) << 16) |
			   /* SDmaBufOffset[12:2] */
			   (dwoffset & 0x7ffULL));
पूर्ण

अटल अंतरभूत __le64 qib_sdma_make_first_desc0(__le64 descq)
अणु
	वापस descq | cpu_to_le64(1ULL << 12);
पूर्ण

अटल अंतरभूत __le64 qib_sdma_make_last_desc0(__le64 descq)
अणु
					      /* last */  /* dma head */
	वापस descq | cpu_to_le64(1ULL << 11 | 1ULL << 13);
पूर्ण

अटल अंतरभूत __le64 qib_sdma_make_desc1(u64 addr)
अणु
	/* SDmaPhyAddr[47:32] */
	वापस cpu_to_le64(addr >> 32);
पूर्ण

अटल व्योम qib_user_sdma_send_frag(काष्ठा qib_pportdata *ppd,
				    काष्ठा qib_user_sdma_pkt *pkt, पूर्णांक idx,
				    अचिन्हित ofs, u16 tail, u8 gen)
अणु
	स्थिर u64 addr = (u64) pkt->addr[idx].addr +
		(u64) pkt->addr[idx].offset;
	स्थिर u64 dwlen = (u64) pkt->addr[idx].length / 4;
	__le64 *descqp;
	__le64 descq0;

	descqp = &ppd->sdma_descq[tail].qw[0];

	descq0 = qib_sdma_make_desc0(gen, addr, dwlen, ofs);
	अगर (pkt->addr[idx].first_desc)
		descq0 = qib_sdma_make_first_desc0(descq0);
	अगर (pkt->addr[idx].last_desc) अणु
		descq0 = qib_sdma_make_last_desc0(descq0);
		अगर (ppd->sdma_पूर्णांकrequest) अणु
			descq0 |= cpu_to_le64(1ULL << 15);
			ppd->sdma_पूर्णांकrequest = 0;
		पूर्ण
	पूर्ण

	descqp[0] = descq0;
	descqp[1] = qib_sdma_make_desc1(addr);
पूर्ण

व्योम qib_user_sdma_send_desc(काष्ठा qib_pportdata *ppd,
				काष्ठा list_head *pktlist)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u16 nमुक्त, nsent;
	u16 tail, tail_c;
	u8 gen, gen_c;

	nमुक्त = qib_sdma_descq_मुक्तcnt(ppd);
	अगर (!nमुक्त)
		वापस;

retry:
	nsent = 0;
	tail_c = tail = ppd->sdma_descq_tail;
	gen_c = gen = ppd->sdma_generation;
	जबतक (!list_empty(pktlist)) अणु
		काष्ठा qib_user_sdma_pkt *pkt =
			list_entry(pktlist->next, काष्ठा qib_user_sdma_pkt,
				   list);
		पूर्णांक i, j, c = 0;
		अचिन्हित ofs = 0;
		u16 dtail = tail;

		क्रम (i = pkt->index; i < pkt->naddr && nमुक्त; i++) अणु
			qib_user_sdma_send_frag(ppd, pkt, i, ofs, tail, gen);
			ofs += pkt->addr[i].length >> 2;

			अगर (++tail == ppd->sdma_descq_cnt) अणु
				tail = 0;
				++gen;
				ppd->sdma_पूर्णांकrequest = 1;
			पूर्ण अन्यथा अगर (tail == (ppd->sdma_descq_cnt>>1)) अणु
				ppd->sdma_पूर्णांकrequest = 1;
			पूर्ण
			nमुक्त--;
			अगर (pkt->addr[i].last_desc == 0)
				जारी;

			/*
			 * If the packet is >= 2KB mtu equivalent, we
			 * have to use the large buffers, and have to
			 * mark each descriptor as part of a large
			 * buffer packet.
			 */
			अगर (ofs > dd->piosize2kmax_dwords) अणु
				क्रम (j = pkt->index; j <= i; j++) अणु
					ppd->sdma_descq[dtail].qw[0] |=
						cpu_to_le64(1ULL << 14);
					अगर (++dtail == ppd->sdma_descq_cnt)
						dtail = 0;
				पूर्ण
			पूर्ण
			c += i + 1 - pkt->index;
			pkt->index = i + 1; /* index क्रम next first */
			tail_c = dtail = tail;
			gen_c = gen;
			ofs = 0;  /* reset क्रम next packet */
		पूर्ण

		ppd->sdma_descq_added += c;
		nsent += c;
		अगर (pkt->index == pkt->naddr) अणु
			pkt->added = ppd->sdma_descq_added;
			pkt->pq->added = pkt->added;
			pkt->pq->num_pending--;
			spin_lock(&pkt->pq->sent_lock);
			pkt->pq->num_sending++;
			list_move_tail(&pkt->list, &pkt->pq->sent);
			spin_unlock(&pkt->pq->sent_lock);
		पूर्ण
		अगर (!nमुक्त || (nsent<<2) > ppd->sdma_descq_cnt)
			अवरोध;
	पूर्ण

	/* advance the tail on the chip अगर necessary */
	अगर (ppd->sdma_descq_tail != tail_c) अणु
		ppd->sdma_generation = gen_c;
		dd->f_sdma_update_tail(ppd, tail_c);
	पूर्ण

	अगर (nमुक्त && !list_empty(pktlist))
		जाओ retry;
पूर्ण

/* pq->lock must be held, get packets on the wire... */
अटल पूर्णांक qib_user_sdma_push_pkts(काष्ठा qib_pportdata *ppd,
				 काष्ठा qib_user_sdma_queue *pq,
				 काष्ठा list_head *pktlist, पूर्णांक count)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!(ppd->lflags & QIBL_LINKACTIVE)))
		वापस -ECOMM;

	/* non-blocking mode */
	अगर (pq->sdma_rb_node->refcount > 1) अणु
		spin_lock_irqsave(&ppd->sdma_lock, flags);
		अगर (unlikely(!__qib_sdma_running(ppd))) अणु
			spin_unlock_irqrestore(&ppd->sdma_lock, flags);
			वापस -ECOMM;
		पूर्ण
		pq->num_pending += count;
		list_splice_tail_init(pktlist, &ppd->sdma_userpending);
		qib_user_sdma_send_desc(ppd, &ppd->sdma_userpending);
		spin_unlock_irqrestore(&ppd->sdma_lock, flags);
		वापस 0;
	पूर्ण

	/* In this हाल, descriptors from this process are not
	 * linked to ppd pending queue, पूर्णांकerrupt handler
	 * won't update this process, it is OK to directly
	 * modअगरy without sdma lock.
	 */


	pq->num_pending += count;
	/*
	 * Blocking mode क्रम single rail process, we must
	 * release/regain sdma_lock to give other process
	 * chance to make progress. This is important क्रम
	 * perक्रमmance.
	 */
	करो अणु
		spin_lock_irqsave(&ppd->sdma_lock, flags);
		अगर (unlikely(!__qib_sdma_running(ppd))) अणु
			spin_unlock_irqrestore(&ppd->sdma_lock, flags);
			वापस -ECOMM;
		पूर्ण
		qib_user_sdma_send_desc(ppd, pktlist);
		अगर (!list_empty(pktlist))
			qib_sdma_make_progress(ppd);
		spin_unlock_irqrestore(&ppd->sdma_lock, flags);
	पूर्ण जबतक (!list_empty(pktlist));

	वापस 0;
पूर्ण

पूर्णांक qib_user_sdma_ग_लिखोv(काष्ठा qib_ctxtdata *rcd,
			 काष्ठा qib_user_sdma_queue *pq,
			 स्थिर काष्ठा iovec *iov,
			 अचिन्हित दीर्घ dim)
अणु
	काष्ठा qib_devdata *dd = rcd->dd;
	काष्ठा qib_pportdata *ppd = rcd->ppd;
	पूर्णांक ret = 0;
	काष्ठा list_head list;
	पूर्णांक npkts = 0;

	INIT_LIST_HEAD(&list);

	mutex_lock(&pq->lock);

	/* why not -ECOMM like qib_user_sdma_push_pkts() below? */
	अगर (!qib_sdma_running(ppd))
		जाओ करोne_unlock;

	/* अगर I have packets not complete yet */
	अगर (pq->added > ppd->sdma_descq_हटाओd)
		qib_user_sdma_hwqueue_clean(ppd);
	/* अगर I have complete packets to be मुक्तd */
	अगर (pq->num_sending)
		qib_user_sdma_queue_clean(ppd, pq);

	जबतक (dim) अणु
		पूर्णांक mxp = 1;
		पूर्णांक ndesc = 0;

		ret = qib_user_sdma_queue_pkts(dd, ppd, pq,
				iov, dim, &list, &mxp, &ndesc);
		अगर (ret < 0)
			जाओ करोne_unlock;
		अन्यथा अणु
			dim -= ret;
			iov += ret;
		पूर्ण

		/* क्रमce packets onto the sdma hw queue... */
		अगर (!list_empty(&list)) अणु
			/*
			 * Lazily clean hw queue.
			 */
			अगर (qib_sdma_descq_मुक्तcnt(ppd) < ndesc) अणु
				qib_user_sdma_hwqueue_clean(ppd);
				अगर (pq->num_sending)
					qib_user_sdma_queue_clean(ppd, pq);
			पूर्ण

			ret = qib_user_sdma_push_pkts(ppd, pq, &list, mxp);
			अगर (ret < 0)
				जाओ करोne_unlock;
			अन्यथा अणु
				npkts += mxp;
				pq->counter += mxp;
			पूर्ण
		पूर्ण
	पूर्ण

करोne_unlock:
	अगर (!list_empty(&list))
		qib_user_sdma_मुक्त_pkt_list(&dd->pcidev->dev, pq, &list);
	mutex_unlock(&pq->lock);

	वापस (ret < 0) ? ret : npkts;
पूर्ण

पूर्णांक qib_user_sdma_make_progress(काष्ठा qib_pportdata *ppd,
				काष्ठा qib_user_sdma_queue *pq)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&pq->lock);
	qib_user_sdma_hwqueue_clean(ppd);
	ret = qib_user_sdma_queue_clean(ppd, pq);
	mutex_unlock(&pq->lock);

	वापस ret;
पूर्ण

u32 qib_user_sdma_complete_counter(स्थिर काष्ठा qib_user_sdma_queue *pq)
अणु
	वापस pq ? pq->sent_counter : 0;
पूर्ण

u32 qib_user_sdma_inflight_counter(काष्ठा qib_user_sdma_queue *pq)
अणु
	वापस pq ? pq->counter : 0;
पूर्ण
