<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 HGST, a Western Digital Company.
 */
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/mr_pool.h>

काष्ठा ib_mr *ib_mr_pool_get(काष्ठा ib_qp *qp, काष्ठा list_head *list)
अणु
	काष्ठा ib_mr *mr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->mr_lock, flags);
	mr = list_first_entry_or_null(list, काष्ठा ib_mr, qp_entry);
	अगर (mr) अणु
		list_del(&mr->qp_entry);
		qp->mrs_used++;
	पूर्ण
	spin_unlock_irqrestore(&qp->mr_lock, flags);

	वापस mr;
पूर्ण
EXPORT_SYMBOL(ib_mr_pool_get);

व्योम ib_mr_pool_put(काष्ठा ib_qp *qp, काष्ठा list_head *list, काष्ठा ib_mr *mr)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->mr_lock, flags);
	list_add(&mr->qp_entry, list);
	qp->mrs_used--;
	spin_unlock_irqrestore(&qp->mr_lock, flags);
पूर्ण
EXPORT_SYMBOL(ib_mr_pool_put);

पूर्णांक ib_mr_pool_init(काष्ठा ib_qp *qp, काष्ठा list_head *list, पूर्णांक nr,
		क्रमागत ib_mr_type type, u32 max_num_sg, u32 max_num_meta_sg)
अणु
	काष्ठा ib_mr *mr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, i;

	क्रम (i = 0; i < nr; i++) अणु
		अगर (type == IB_MR_TYPE_INTEGRITY)
			mr = ib_alloc_mr_पूर्णांकegrity(qp->pd, max_num_sg,
						   max_num_meta_sg);
		अन्यथा
			mr = ib_alloc_mr(qp->pd, type, max_num_sg);
		अगर (IS_ERR(mr)) अणु
			ret = PTR_ERR(mr);
			जाओ out;
		पूर्ण

		spin_lock_irqsave(&qp->mr_lock, flags);
		list_add_tail(&mr->qp_entry, list);
		spin_unlock_irqrestore(&qp->mr_lock, flags);
	पूर्ण

	वापस 0;
out:
	ib_mr_pool_destroy(qp, list);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_mr_pool_init);

व्योम ib_mr_pool_destroy(काष्ठा ib_qp *qp, काष्ठा list_head *list)
अणु
	काष्ठा ib_mr *mr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&qp->mr_lock, flags);
	जबतक (!list_empty(list)) अणु
		mr = list_first_entry(list, काष्ठा ib_mr, qp_entry);
		list_del(&mr->qp_entry);

		spin_unlock_irqrestore(&qp->mr_lock, flags);
		ib_dereg_mr(mr);
		spin_lock_irqsave(&qp->mr_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&qp->mr_lock, flags);
पूर्ण
EXPORT_SYMBOL(ib_mr_pool_destroy);
