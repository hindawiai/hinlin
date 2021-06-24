<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/net/ethernet/ibm/ehea/ehea_qmr.c
 *
 *  eHEA ethernet device driver क्रम IBM eServer System p
 *
 *  (C) Copyright IBM Corp. 2006
 *
 *  Authors:
 *       Christoph Raisch <raisch@de.ibm.com>
 *       Jan-Bernd Themann <themann@de.ibm.com>
 *       Thomas Klein <tklein@de.ibm.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश "ehea.h"
#समावेश "ehea_phyp.h"
#समावेश "ehea_qmr.h"

अटल काष्ठा ehea_bmap *ehea_bmap;

अटल व्योम *hw_qpageit_get_inc(काष्ठा hw_queue *queue)
अणु
	व्योम *retvalue = hw_qeit_get(queue);

	queue->current_q_offset += queue->pagesize;
	अगर (queue->current_q_offset > queue->queue_length) अणु
		queue->current_q_offset -= queue->pagesize;
		retvalue = शून्य;
	पूर्ण अन्यथा अगर (((u64) retvalue) & (EHEA_PAGESIZE-1)) अणु
		pr_err("not on pageboundary\n");
		retvalue = शून्य;
	पूर्ण
	वापस retvalue;
पूर्ण

अटल पूर्णांक hw_queue_ctor(काष्ठा hw_queue *queue, स्थिर u32 nr_of_pages,
			  स्थिर u32 pagesize, स्थिर u32 qe_size)
अणु
	पूर्णांक pages_per_kpage = PAGE_SIZE / pagesize;
	पूर्णांक i, k;

	अगर ((pagesize > PAGE_SIZE) || (!pages_per_kpage)) अणु
		pr_err("pagesize conflict! kernel pagesize=%d, ehea pagesize=%d\n",
		       (पूर्णांक)PAGE_SIZE, (पूर्णांक)pagesize);
		वापस -EINVAL;
	पूर्ण

	queue->queue_length = nr_of_pages * pagesize;
	queue->queue_pages = kदो_स्मृति_array(nr_of_pages, माप(व्योम *),
					   GFP_KERNEL);
	अगर (!queue->queue_pages)
		वापस -ENOMEM;

	/*
	 * allocate pages क्रम queue:
	 * outer loop allocates whole kernel pages (page aligned) and
	 * inner loop भागides a kernel page पूर्णांकo smaller hea queue pages
	 */
	i = 0;
	जबतक (i < nr_of_pages) अणु
		u8 *kpage = (u8 *)get_zeroed_page(GFP_KERNEL);
		अगर (!kpage)
			जाओ out_nomem;
		क्रम (k = 0; k < pages_per_kpage && i < nr_of_pages; k++) अणु
			(queue->queue_pages)[i] = (काष्ठा ehea_page *)kpage;
			kpage += pagesize;
			i++;
		पूर्ण
	पूर्ण

	queue->current_q_offset = 0;
	queue->qe_size = qe_size;
	queue->pagesize = pagesize;
	queue->toggle_state = 1;

	वापस 0;
out_nomem:
	क्रम (i = 0; i < nr_of_pages; i += pages_per_kpage) अणु
		अगर (!(queue->queue_pages)[i])
			अवरोध;
		मुक्त_page((अचिन्हित दीर्घ)(queue->queue_pages)[i]);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम hw_queue_dtor(काष्ठा hw_queue *queue)
अणु
	पूर्णांक pages_per_kpage;
	पूर्णांक i, nr_pages;

	अगर (!queue || !queue->queue_pages)
		वापस;

	pages_per_kpage = PAGE_SIZE / queue->pagesize;

	nr_pages = queue->queue_length / queue->pagesize;

	क्रम (i = 0; i < nr_pages; i += pages_per_kpage)
		मुक्त_page((अचिन्हित दीर्घ)(queue->queue_pages)[i]);

	kमुक्त(queue->queue_pages);
पूर्ण

काष्ठा ehea_cq *ehea_create_cq(काष्ठा ehea_adapter *adapter,
			       पूर्णांक nr_of_cqe, u64 eq_handle, u32 cq_token)
अणु
	काष्ठा ehea_cq *cq;
	u64 hret, rpage;
	u32 counter;
	पूर्णांक ret;
	व्योम *vpage;

	cq = kzalloc(माप(*cq), GFP_KERNEL);
	अगर (!cq)
		जाओ out_nomem;

	cq->attr.max_nr_of_cqes = nr_of_cqe;
	cq->attr.cq_token = cq_token;
	cq->attr.eq_handle = eq_handle;

	cq->adapter = adapter;

	hret = ehea_h_alloc_resource_cq(adapter->handle, &cq->attr,
					&cq->fw_handle, &cq->epas);
	अगर (hret != H_SUCCESS) अणु
		pr_err("alloc_resource_cq failed\n");
		जाओ out_मुक्तmem;
	पूर्ण

	ret = hw_queue_ctor(&cq->hw_queue, cq->attr.nr_pages,
			    EHEA_PAGESIZE, माप(काष्ठा ehea_cqe));
	अगर (ret)
		जाओ out_मुक्तres;

	क्रम (counter = 0; counter < cq->attr.nr_pages; counter++) अणु
		vpage = hw_qpageit_get_inc(&cq->hw_queue);
		अगर (!vpage) अणु
			pr_err("hw_qpageit_get_inc failed\n");
			जाओ out_समाप्त_hwq;
		पूर्ण

		rpage = __pa(vpage);
		hret = ehea_h_रेजिस्टर_rpage(adapter->handle,
					     0, EHEA_CQ_REGISTER_ORIG,
					     cq->fw_handle, rpage, 1);
		अगर (hret < H_SUCCESS) अणु
			pr_err("register_rpage_cq failed ehea_cq=%p hret=%llx counter=%i act_pages=%i\n",
			       cq, hret, counter, cq->attr.nr_pages);
			जाओ out_समाप्त_hwq;
		पूर्ण

		अगर (counter == (cq->attr.nr_pages - 1)) अणु
			vpage = hw_qpageit_get_inc(&cq->hw_queue);

			अगर ((hret != H_SUCCESS) || (vpage)) अणु
				pr_err("registration of pages not complete hret=%llx\n",
				       hret);
				जाओ out_समाप्त_hwq;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (hret != H_PAGE_REGISTERED) अणु
				pr_err("CQ: registration of page failed hret=%llx\n",
				       hret);
				जाओ out_समाप्त_hwq;
			पूर्ण
		पूर्ण
	पूर्ण

	hw_qeit_reset(&cq->hw_queue);
	ehea_reset_cq_ep(cq);
	ehea_reset_cq_n1(cq);

	वापस cq;

out_समाप्त_hwq:
	hw_queue_dtor(&cq->hw_queue);

out_मुक्तres:
	ehea_h_मुक्त_resource(adapter->handle, cq->fw_handle, FORCE_FREE);

out_मुक्तmem:
	kमुक्त(cq);

out_nomem:
	वापस शून्य;
पूर्ण

अटल u64 ehea_destroy_cq_res(काष्ठा ehea_cq *cq, u64 क्रमce)
अणु
	u64 hret;
	u64 adapter_handle = cq->adapter->handle;

	/* deरेजिस्टर all previous रेजिस्टरed pages */
	hret = ehea_h_मुक्त_resource(adapter_handle, cq->fw_handle, क्रमce);
	अगर (hret != H_SUCCESS)
		वापस hret;

	hw_queue_dtor(&cq->hw_queue);
	kमुक्त(cq);

	वापस hret;
पूर्ण

पूर्णांक ehea_destroy_cq(काष्ठा ehea_cq *cq)
अणु
	u64 hret, aer, aerr;
	अगर (!cq)
		वापस 0;

	hcp_epas_dtor(&cq->epas);
	hret = ehea_destroy_cq_res(cq, NORMAL_FREE);
	अगर (hret == H_R_STATE) अणु
		ehea_error_data(cq->adapter, cq->fw_handle, &aer, &aerr);
		hret = ehea_destroy_cq_res(cq, FORCE_FREE);
	पूर्ण

	अगर (hret != H_SUCCESS) अणु
		pr_err("destroy CQ failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा ehea_eq *ehea_create_eq(काष्ठा ehea_adapter *adapter,
			       स्थिर क्रमागत ehea_eq_type type,
			       स्थिर u32 max_nr_of_eqes, स्थिर u8 eqe_gen)
अणु
	पूर्णांक ret, i;
	u64 hret, rpage;
	व्योम *vpage;
	काष्ठा ehea_eq *eq;

	eq = kzalloc(माप(*eq), GFP_KERNEL);
	अगर (!eq)
		वापस शून्य;

	eq->adapter = adapter;
	eq->attr.type = type;
	eq->attr.max_nr_of_eqes = max_nr_of_eqes;
	eq->attr.eqe_gen = eqe_gen;
	spin_lock_init(&eq->spinlock);

	hret = ehea_h_alloc_resource_eq(adapter->handle,
					&eq->attr, &eq->fw_handle);
	अगर (hret != H_SUCCESS) अणु
		pr_err("alloc_resource_eq failed\n");
		जाओ out_मुक्तmem;
	पूर्ण

	ret = hw_queue_ctor(&eq->hw_queue, eq->attr.nr_pages,
			    EHEA_PAGESIZE, माप(काष्ठा ehea_eqe));
	अगर (ret) अणु
		pr_err("can't allocate eq pages\n");
		जाओ out_मुक्तres;
	पूर्ण

	क्रम (i = 0; i < eq->attr.nr_pages; i++) अणु
		vpage = hw_qpageit_get_inc(&eq->hw_queue);
		अगर (!vpage) अणु
			pr_err("hw_qpageit_get_inc failed\n");
			hret = H_RESOURCE;
			जाओ out_समाप्त_hwq;
		पूर्ण

		rpage = __pa(vpage);

		hret = ehea_h_रेजिस्टर_rpage(adapter->handle, 0,
					     EHEA_EQ_REGISTER_ORIG,
					     eq->fw_handle, rpage, 1);

		अगर (i == (eq->attr.nr_pages - 1)) अणु
			/* last page */
			vpage = hw_qpageit_get_inc(&eq->hw_queue);
			अगर ((hret != H_SUCCESS) || (vpage))
				जाओ out_समाप्त_hwq;

		पूर्ण अन्यथा अणु
			अगर (hret != H_PAGE_REGISTERED)
				जाओ out_समाप्त_hwq;

		पूर्ण
	पूर्ण

	hw_qeit_reset(&eq->hw_queue);
	वापस eq;

out_समाप्त_hwq:
	hw_queue_dtor(&eq->hw_queue);

out_मुक्तres:
	ehea_h_मुक्त_resource(adapter->handle, eq->fw_handle, FORCE_FREE);

out_मुक्तmem:
	kमुक्त(eq);
	वापस शून्य;
पूर्ण

काष्ठा ehea_eqe *ehea_poll_eq(काष्ठा ehea_eq *eq)
अणु
	काष्ठा ehea_eqe *eqe;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&eq->spinlock, flags);
	eqe = hw_eqit_eq_get_inc_valid(&eq->hw_queue);
	spin_unlock_irqrestore(&eq->spinlock, flags);

	वापस eqe;
पूर्ण

अटल u64 ehea_destroy_eq_res(काष्ठा ehea_eq *eq, u64 क्रमce)
अणु
	u64 hret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&eq->spinlock, flags);

	hret = ehea_h_मुक्त_resource(eq->adapter->handle, eq->fw_handle, क्रमce);
	spin_unlock_irqrestore(&eq->spinlock, flags);

	अगर (hret != H_SUCCESS)
		वापस hret;

	hw_queue_dtor(&eq->hw_queue);
	kमुक्त(eq);

	वापस hret;
पूर्ण

पूर्णांक ehea_destroy_eq(काष्ठा ehea_eq *eq)
अणु
	u64 hret, aer, aerr;
	अगर (!eq)
		वापस 0;

	hcp_epas_dtor(&eq->epas);

	hret = ehea_destroy_eq_res(eq, NORMAL_FREE);
	अगर (hret == H_R_STATE) अणु
		ehea_error_data(eq->adapter, eq->fw_handle, &aer, &aerr);
		hret = ehea_destroy_eq_res(eq, FORCE_FREE);
	पूर्ण

	अगर (hret != H_SUCCESS) अणु
		pr_err("destroy EQ failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* allocates memory क्रम a queue and रेजिस्टरs pages in phyp */
अटल पूर्णांक ehea_qp_alloc_रेजिस्टर(काष्ठा ehea_qp *qp, काष्ठा hw_queue *hw_queue,
			   पूर्णांक nr_pages, पूर्णांक wqe_size, पूर्णांक act_nr_sges,
			   काष्ठा ehea_adapter *adapter, पूर्णांक h_call_q_selector)
अणु
	u64 hret, rpage;
	पूर्णांक ret, cnt;
	व्योम *vpage;

	ret = hw_queue_ctor(hw_queue, nr_pages, EHEA_PAGESIZE, wqe_size);
	अगर (ret)
		वापस ret;

	क्रम (cnt = 0; cnt < nr_pages; cnt++) अणु
		vpage = hw_qpageit_get_inc(hw_queue);
		अगर (!vpage) अणु
			pr_err("hw_qpageit_get_inc failed\n");
			जाओ out_समाप्त_hwq;
		पूर्ण
		rpage = __pa(vpage);
		hret = ehea_h_रेजिस्टर_rpage(adapter->handle,
					     0, h_call_q_selector,
					     qp->fw_handle, rpage, 1);
		अगर (hret < H_SUCCESS) अणु
			pr_err("register_rpage_qp failed\n");
			जाओ out_समाप्त_hwq;
		पूर्ण
	पूर्ण
	hw_qeit_reset(hw_queue);
	वापस 0;

out_समाप्त_hwq:
	hw_queue_dtor(hw_queue);
	वापस -EIO;
पूर्ण

अटल अंतरभूत u32 map_wqe_size(u8 wqe_enc_size)
अणु
	वापस 128 << wqe_enc_size;
पूर्ण

काष्ठा ehea_qp *ehea_create_qp(काष्ठा ehea_adapter *adapter,
			       u32 pd, काष्ठा ehea_qp_init_attr *init_attr)
अणु
	पूर्णांक ret;
	u64 hret;
	काष्ठा ehea_qp *qp;
	u32 wqe_size_in_bytes_sq, wqe_size_in_bytes_rq1;
	u32 wqe_size_in_bytes_rq2, wqe_size_in_bytes_rq3;


	qp = kzalloc(माप(*qp), GFP_KERNEL);
	अगर (!qp)
		वापस शून्य;

	qp->adapter = adapter;

	hret = ehea_h_alloc_resource_qp(adapter->handle, init_attr, pd,
					&qp->fw_handle, &qp->epas);
	अगर (hret != H_SUCCESS) अणु
		pr_err("ehea_h_alloc_resource_qp failed\n");
		जाओ out_मुक्तmem;
	पूर्ण

	wqe_size_in_bytes_sq = map_wqe_size(init_attr->act_wqe_size_enc_sq);
	wqe_size_in_bytes_rq1 = map_wqe_size(init_attr->act_wqe_size_enc_rq1);
	wqe_size_in_bytes_rq2 = map_wqe_size(init_attr->act_wqe_size_enc_rq2);
	wqe_size_in_bytes_rq3 = map_wqe_size(init_attr->act_wqe_size_enc_rq3);

	ret = ehea_qp_alloc_रेजिस्टर(qp, &qp->hw_squeue, init_attr->nr_sq_pages,
				     wqe_size_in_bytes_sq,
				     init_attr->act_wqe_size_enc_sq, adapter,
				     0);
	अगर (ret) अणु
		pr_err("can't register for sq ret=%x\n", ret);
		जाओ out_मुक्तres;
	पूर्ण

	ret = ehea_qp_alloc_रेजिस्टर(qp, &qp->hw_rqueue1,
				     init_attr->nr_rq1_pages,
				     wqe_size_in_bytes_rq1,
				     init_attr->act_wqe_size_enc_rq1,
				     adapter, 1);
	अगर (ret) अणु
		pr_err("can't register for rq1 ret=%x\n", ret);
		जाओ out_समाप्त_hwsq;
	पूर्ण

	अगर (init_attr->rq_count > 1) अणु
		ret = ehea_qp_alloc_रेजिस्टर(qp, &qp->hw_rqueue2,
					     init_attr->nr_rq2_pages,
					     wqe_size_in_bytes_rq2,
					     init_attr->act_wqe_size_enc_rq2,
					     adapter, 2);
		अगर (ret) अणु
			pr_err("can't register for rq2 ret=%x\n", ret);
			जाओ out_समाप्त_hwr1q;
		पूर्ण
	पूर्ण

	अगर (init_attr->rq_count > 2) अणु
		ret = ehea_qp_alloc_रेजिस्टर(qp, &qp->hw_rqueue3,
					     init_attr->nr_rq3_pages,
					     wqe_size_in_bytes_rq3,
					     init_attr->act_wqe_size_enc_rq3,
					     adapter, 3);
		अगर (ret) अणु
			pr_err("can't register for rq3 ret=%x\n", ret);
			जाओ out_समाप्त_hwr2q;
		पूर्ण
	पूर्ण

	qp->init_attr = *init_attr;

	वापस qp;

out_समाप्त_hwr2q:
	hw_queue_dtor(&qp->hw_rqueue2);

out_समाप्त_hwr1q:
	hw_queue_dtor(&qp->hw_rqueue1);

out_समाप्त_hwsq:
	hw_queue_dtor(&qp->hw_squeue);

out_मुक्तres:
	ehea_h_disable_and_get_hea(adapter->handle, qp->fw_handle);
	ehea_h_मुक्त_resource(adapter->handle, qp->fw_handle, FORCE_FREE);

out_मुक्तmem:
	kमुक्त(qp);
	वापस शून्य;
पूर्ण

अटल u64 ehea_destroy_qp_res(काष्ठा ehea_qp *qp, u64 क्रमce)
अणु
	u64 hret;
	काष्ठा ehea_qp_init_attr *qp_attr = &qp->init_attr;


	ehea_h_disable_and_get_hea(qp->adapter->handle, qp->fw_handle);
	hret = ehea_h_मुक्त_resource(qp->adapter->handle, qp->fw_handle, क्रमce);
	अगर (hret != H_SUCCESS)
		वापस hret;

	hw_queue_dtor(&qp->hw_squeue);
	hw_queue_dtor(&qp->hw_rqueue1);

	अगर (qp_attr->rq_count > 1)
		hw_queue_dtor(&qp->hw_rqueue2);
	अगर (qp_attr->rq_count > 2)
		hw_queue_dtor(&qp->hw_rqueue3);
	kमुक्त(qp);

	वापस hret;
पूर्ण

पूर्णांक ehea_destroy_qp(काष्ठा ehea_qp *qp)
अणु
	u64 hret, aer, aerr;
	अगर (!qp)
		वापस 0;

	hcp_epas_dtor(&qp->epas);

	hret = ehea_destroy_qp_res(qp, NORMAL_FREE);
	अगर (hret == H_R_STATE) अणु
		ehea_error_data(qp->adapter, qp->fw_handle, &aer, &aerr);
		hret = ehea_destroy_qp_res(qp, FORCE_FREE);
	पूर्ण

	अगर (hret != H_SUCCESS) अणु
		pr_err("destroy QP failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ehea_calc_index(अचिन्हित दीर्घ i, अचिन्हित दीर्घ s)
अणु
	वापस (i >> s) & EHEA_INDEX_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक ehea_init_top_bmap(काष्ठा ehea_top_bmap *ehea_top_bmap,
				     पूर्णांक dir)
अणु
	अगर (!ehea_top_bmap->dir[dir]) अणु
		ehea_top_bmap->dir[dir] =
			kzalloc(माप(काष्ठा ehea_dir_bmap), GFP_KERNEL);
		अगर (!ehea_top_bmap->dir[dir])
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ehea_init_bmap(काष्ठा ehea_bmap *ehea_bmap, पूर्णांक top, पूर्णांक dir)
अणु
	अगर (!ehea_bmap->top[top]) अणु
		ehea_bmap->top[top] =
			kzalloc(माप(काष्ठा ehea_top_bmap), GFP_KERNEL);
		अगर (!ehea_bmap->top[top])
			वापस -ENOMEM;
	पूर्ण
	वापस ehea_init_top_bmap(ehea_bmap->top[top], dir);
पूर्ण

अटल DEFINE_MUTEX(ehea_busmap_mutex);
अटल अचिन्हित दीर्घ ehea_mr_len;

#घोषणा EHEA_BUSMAP_ADD_SECT 1
#घोषणा EHEA_BUSMAP_REM_SECT 0

अटल व्योम ehea_rebuild_busmap(व्योम)
अणु
	u64 vaddr = EHEA_BUSMAP_START;
	पूर्णांक top, dir, idx;

	क्रम (top = 0; top < EHEA_MAP_ENTRIES; top++) अणु
		काष्ठा ehea_top_bmap *ehea_top;
		पूर्णांक valid_dir_entries = 0;

		अगर (!ehea_bmap->top[top])
			जारी;
		ehea_top = ehea_bmap->top[top];
		क्रम (dir = 0; dir < EHEA_MAP_ENTRIES; dir++) अणु
			काष्ठा ehea_dir_bmap *ehea_dir;
			पूर्णांक valid_entries = 0;

			अगर (!ehea_top->dir[dir])
				जारी;
			valid_dir_entries++;
			ehea_dir = ehea_top->dir[dir];
			क्रम (idx = 0; idx < EHEA_MAP_ENTRIES; idx++) अणु
				अगर (!ehea_dir->ent[idx])
					जारी;
				valid_entries++;
				ehea_dir->ent[idx] = vaddr;
				vaddr += EHEA_SECTSIZE;
			पूर्ण
			अगर (!valid_entries) अणु
				ehea_top->dir[dir] = शून्य;
				kमुक्त(ehea_dir);
			पूर्ण
		पूर्ण
		अगर (!valid_dir_entries) अणु
			ehea_bmap->top[top] = शून्य;
			kमुक्त(ehea_top);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ehea_update_busmap(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages, पूर्णांक add)
अणु
	अचिन्हित दीर्घ i, start_section, end_section;

	अगर (!nr_pages)
		वापस 0;

	अगर (!ehea_bmap) अणु
		ehea_bmap = kzalloc(माप(काष्ठा ehea_bmap), GFP_KERNEL);
		अगर (!ehea_bmap)
			वापस -ENOMEM;
	पूर्ण

	start_section = (pfn * PAGE_SIZE) / EHEA_SECTSIZE;
	end_section = start_section + ((nr_pages * PAGE_SIZE) / EHEA_SECTSIZE);
	/* Mark entries as valid or invalid only; address is asचिन्हित later */
	क्रम (i = start_section; i < end_section; i++) अणु
		u64 flag;
		पूर्णांक top = ehea_calc_index(i, EHEA_TOP_INDEX_SHIFT);
		पूर्णांक dir = ehea_calc_index(i, EHEA_सूची_INDEX_SHIFT);
		पूर्णांक idx = i & EHEA_INDEX_MASK;

		अगर (add) अणु
			पूर्णांक ret = ehea_init_bmap(ehea_bmap, top, dir);
			अगर (ret)
				वापस ret;
			flag = 1; /* valid */
			ehea_mr_len += EHEA_SECTSIZE;
		पूर्ण अन्यथा अणु
			अगर (!ehea_bmap->top[top])
				जारी;
			अगर (!ehea_bmap->top[top]->dir[dir])
				जारी;
			flag = 0; /* invalid */
			ehea_mr_len -= EHEA_SECTSIZE;
		पूर्ण

		ehea_bmap->top[top]->dir[dir]->ent[idx] = flag;
	पूर्ण
	ehea_rebuild_busmap(); /* Assign contiguous addresses क्रम mr */
	वापस 0;
पूर्ण

पूर्णांक ehea_add_sect_bmap(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक ret;

	mutex_lock(&ehea_busmap_mutex);
	ret = ehea_update_busmap(pfn, nr_pages, EHEA_BUSMAP_ADD_SECT);
	mutex_unlock(&ehea_busmap_mutex);
	वापस ret;
पूर्ण

पूर्णांक ehea_rem_sect_bmap(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक ret;

	mutex_lock(&ehea_busmap_mutex);
	ret = ehea_update_busmap(pfn, nr_pages, EHEA_BUSMAP_REM_SECT);
	mutex_unlock(&ehea_busmap_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ehea_is_hugepage(अचिन्हित दीर्घ pfn)
अणु
	अगर (pfn & EHEA_HUGEPAGE_PFN_MASK)
		वापस 0;

	अगर (page_shअगरt(pfn_to_page(pfn)) != EHEA_HUGEPAGESHIFT)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक ehea_create_busmap_callback(अचिन्हित दीर्घ initial_pfn,
				       अचिन्हित दीर्घ total_nr_pages, व्योम *arg)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ pfn, start_pfn, end_pfn, nr_pages;

	अगर ((total_nr_pages * PAGE_SIZE) < EHEA_HUGEPAGE_SIZE)
		वापस ehea_update_busmap(initial_pfn, total_nr_pages,
					  EHEA_BUSMAP_ADD_SECT);

	/* Given chunk is >= 16GB -> check क्रम hugepages */
	start_pfn = initial_pfn;
	end_pfn = initial_pfn + total_nr_pages;
	pfn = start_pfn;

	जबतक (pfn < end_pfn) अणु
		अगर (ehea_is_hugepage(pfn)) अणु
			/* Add mem found in front of the hugepage */
			nr_pages = pfn - start_pfn;
			ret = ehea_update_busmap(start_pfn, nr_pages,
						 EHEA_BUSMAP_ADD_SECT);
			अगर (ret)
				वापस ret;

			/* Skip the hugepage */
			pfn += (EHEA_HUGEPAGE_SIZE / PAGE_SIZE);
			start_pfn = pfn;
		पूर्ण अन्यथा
			pfn += (EHEA_SECTSIZE / PAGE_SIZE);
	पूर्ण

	/* Add mem found behind the hugepage(s)  */
	nr_pages = pfn - start_pfn;
	वापस ehea_update_busmap(start_pfn, nr_pages, EHEA_BUSMAP_ADD_SECT);
पूर्ण

पूर्णांक ehea_create_busmap(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&ehea_busmap_mutex);
	ehea_mr_len = 0;
	ret = walk_प्रणाली_ram_range(0, 1ULL << MAX_PHYSMEM_BITS, शून्य,
				   ehea_create_busmap_callback);
	mutex_unlock(&ehea_busmap_mutex);
	वापस ret;
पूर्ण

व्योम ehea_destroy_busmap(व्योम)
अणु
	पूर्णांक top, dir;
	mutex_lock(&ehea_busmap_mutex);
	अगर (!ehea_bmap)
		जाओ out_destroy;

	क्रम (top = 0; top < EHEA_MAP_ENTRIES; top++) अणु
		अगर (!ehea_bmap->top[top])
			जारी;

		क्रम (dir = 0; dir < EHEA_MAP_ENTRIES; dir++) अणु
			अगर (!ehea_bmap->top[top]->dir[dir])
				जारी;

			kमुक्त(ehea_bmap->top[top]->dir[dir]);
		पूर्ण

		kमुक्त(ehea_bmap->top[top]);
	पूर्ण

	kमुक्त(ehea_bmap);
	ehea_bmap = शून्य;
out_destroy:
	mutex_unlock(&ehea_busmap_mutex);
पूर्ण

u64 ehea_map_vaddr(व्योम *caddr)
अणु
	पूर्णांक top, dir, idx;
	अचिन्हित दीर्घ index, offset;

	अगर (!ehea_bmap)
		वापस EHEA_INVAL_ADDR;

	index = __pa(caddr) >> SECTION_SIZE_BITS;
	top = (index >> EHEA_TOP_INDEX_SHIFT) & EHEA_INDEX_MASK;
	अगर (!ehea_bmap->top[top])
		वापस EHEA_INVAL_ADDR;

	dir = (index >> EHEA_सूची_INDEX_SHIFT) & EHEA_INDEX_MASK;
	अगर (!ehea_bmap->top[top]->dir[dir])
		वापस EHEA_INVAL_ADDR;

	idx = index & EHEA_INDEX_MASK;
	अगर (!ehea_bmap->top[top]->dir[dir]->ent[idx])
		वापस EHEA_INVAL_ADDR;

	offset = (अचिन्हित दीर्घ)caddr & (EHEA_SECTSIZE - 1);
	वापस ehea_bmap->top[top]->dir[dir]->ent[idx] | offset;
पूर्ण

अटल अंतरभूत व्योम *ehea_calc_sectbase(पूर्णांक top, पूर्णांक dir, पूर्णांक idx)
अणु
	अचिन्हित दीर्घ ret = idx;
	ret |= dir << EHEA_सूची_INDEX_SHIFT;
	ret |= top << EHEA_TOP_INDEX_SHIFT;
	वापस __va(ret << SECTION_SIZE_BITS);
पूर्ण

अटल u64 ehea_reg_mr_section(पूर्णांक top, पूर्णांक dir, पूर्णांक idx, u64 *pt,
			       काष्ठा ehea_adapter *adapter,
			       काष्ठा ehea_mr *mr)
अणु
	व्योम *pg;
	u64 j, m, hret;
	अचिन्हित दीर्घ k = 0;
	u64 pt_असल = __pa(pt);

	व्योम *sectbase = ehea_calc_sectbase(top, dir, idx);

	क्रम (j = 0; j < (EHEA_PAGES_PER_SECTION / EHEA_MAX_RPAGE); j++) अणु

		क्रम (m = 0; m < EHEA_MAX_RPAGE; m++) अणु
			pg = sectbase + ((k++) * EHEA_PAGESIZE);
			pt[m] = __pa(pg);
		पूर्ण
		hret = ehea_h_रेजिस्टर_rpage_mr(adapter->handle, mr->handle, 0,
						0, pt_असल, EHEA_MAX_RPAGE);

		अगर ((hret != H_SUCCESS) &&
		    (hret != H_PAGE_REGISTERED)) अणु
			ehea_h_मुक्त_resource(adapter->handle, mr->handle,
					     FORCE_FREE);
			pr_err("register_rpage_mr failed\n");
			वापस hret;
		पूर्ण
	पूर्ण
	वापस hret;
पूर्ण

अटल u64 ehea_reg_mr_sections(पूर्णांक top, पूर्णांक dir, u64 *pt,
				काष्ठा ehea_adapter *adapter,
				काष्ठा ehea_mr *mr)
अणु
	u64 hret = H_SUCCESS;
	पूर्णांक idx;

	क्रम (idx = 0; idx < EHEA_MAP_ENTRIES; idx++) अणु
		अगर (!ehea_bmap->top[top]->dir[dir]->ent[idx])
			जारी;

		hret = ehea_reg_mr_section(top, dir, idx, pt, adapter, mr);
		अगर ((hret != H_SUCCESS) && (hret != H_PAGE_REGISTERED))
			वापस hret;
	पूर्ण
	वापस hret;
पूर्ण

अटल u64 ehea_reg_mr_dir_sections(पूर्णांक top, u64 *pt,
				    काष्ठा ehea_adapter *adapter,
				    काष्ठा ehea_mr *mr)
अणु
	u64 hret = H_SUCCESS;
	पूर्णांक dir;

	क्रम (dir = 0; dir < EHEA_MAP_ENTRIES; dir++) अणु
		अगर (!ehea_bmap->top[top]->dir[dir])
			जारी;

		hret = ehea_reg_mr_sections(top, dir, pt, adapter, mr);
		अगर ((hret != H_SUCCESS) && (hret != H_PAGE_REGISTERED))
			वापस hret;
	पूर्ण
	वापस hret;
पूर्ण

पूर्णांक ehea_reg_kernel_mr(काष्ठा ehea_adapter *adapter, काष्ठा ehea_mr *mr)
अणु
	पूर्णांक ret;
	u64 *pt;
	u64 hret;
	u32 acc_ctrl = EHEA_MR_ACC_CTRL;

	अचिन्हित दीर्घ top;

	pt = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!pt) अणु
		pr_err("no mem\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	hret = ehea_h_alloc_resource_mr(adapter->handle, EHEA_BUSMAP_START,
					ehea_mr_len, acc_ctrl, adapter->pd,
					&mr->handle, &mr->lkey);

	अगर (hret != H_SUCCESS) अणु
		pr_err("alloc_resource_mr failed\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (!ehea_bmap) अणु
		ehea_h_मुक्त_resource(adapter->handle, mr->handle, FORCE_FREE);
		pr_err("no busmap available\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	क्रम (top = 0; top < EHEA_MAP_ENTRIES; top++) अणु
		अगर (!ehea_bmap->top[top])
			जारी;

		hret = ehea_reg_mr_dir_sections(top, pt, adapter, mr);
		अगर((hret != H_PAGE_REGISTERED) && (hret != H_SUCCESS))
			अवरोध;
	पूर्ण

	अगर (hret != H_SUCCESS) अणु
		ehea_h_मुक्त_resource(adapter->handle, mr->handle, FORCE_FREE);
		pr_err("registering mr failed\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	mr->vaddr = EHEA_BUSMAP_START;
	mr->adapter = adapter;
	ret = 0;
out:
	मुक्त_page((अचिन्हित दीर्घ)pt);
	वापस ret;
पूर्ण

पूर्णांक ehea_rem_mr(काष्ठा ehea_mr *mr)
अणु
	u64 hret;

	अगर (!mr || !mr->adapter)
		वापस -EINVAL;

	hret = ehea_h_मुक्त_resource(mr->adapter->handle, mr->handle,
				    FORCE_FREE);
	अगर (hret != H_SUCCESS) अणु
		pr_err("destroy MR failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ehea_gen_smr(काष्ठा ehea_adapter *adapter, काष्ठा ehea_mr *old_mr,
		 काष्ठा ehea_mr *shared_mr)
अणु
	u64 hret;

	hret = ehea_h_रेजिस्टर_smr(adapter->handle, old_mr->handle,
				   old_mr->vaddr, EHEA_MR_ACC_CTRL,
				   adapter->pd, shared_mr);
	अगर (hret != H_SUCCESS)
		वापस -EIO;

	shared_mr->adapter = adapter;

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_error_data(u64 *data)
अणु
	पूर्णांक length;
	u64 type = EHEA_BMASK_GET(ERROR_DATA_TYPE, data[2]);
	u64 resource = data[1];

	length = EHEA_BMASK_GET(ERROR_DATA_LENGTH, data[0]);

	अगर (length > EHEA_PAGESIZE)
		length = EHEA_PAGESIZE;

	अगर (type == EHEA_AER_RESTYPE_QP)
		pr_err("QP (resource=%llX) state: AER=0x%llX, AERR=0x%llX, port=%llX\n",
		       resource, data[6], data[12], data[22]);
	अन्यथा अगर (type == EHEA_AER_RESTYPE_CQ)
		pr_err("CQ (resource=%llX) state: AER=0x%llX\n",
		       resource, data[6]);
	अन्यथा अगर (type == EHEA_AER_RESTYPE_EQ)
		pr_err("EQ (resource=%llX) state: AER=0x%llX\n",
		       resource, data[6]);

	ehea_dump(data, length, "error data");
पूर्ण

u64 ehea_error_data(काष्ठा ehea_adapter *adapter, u64 res_handle,
		    u64 *aer, u64 *aerr)
अणु
	अचिन्हित दीर्घ ret;
	u64 *rblock;
	u64 type = 0;

	rblock = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!rblock) अणु
		pr_err("Cannot allocate rblock memory\n");
		जाओ out;
	पूर्ण

	ret = ehea_h_error_data(adapter->handle, res_handle, rblock);

	अगर (ret == H_SUCCESS) अणु
		type = EHEA_BMASK_GET(ERROR_DATA_TYPE, rblock[2]);
		*aer = rblock[6];
		*aerr = rblock[12];
		prपूर्णांक_error_data(rblock);
	पूर्ण अन्यथा अगर (ret == H_R_STATE) अणु
		pr_err("No error data available: %llX\n", res_handle);
	पूर्ण अन्यथा
		pr_err("Error data could not be fetched: %llX\n", res_handle);

	मुक्त_page((अचिन्हित दीर्घ)rblock);
out:
	वापस type;
पूर्ण
