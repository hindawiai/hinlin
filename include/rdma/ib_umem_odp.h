<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2014 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित IB_UMEM_ODP_H
#घोषणा IB_UMEM_ODP_H

#समावेश <rdma/ib_uस्मृति.स>
#समावेश <rdma/ib_verbs.h>

काष्ठा ib_umem_odp अणु
	काष्ठा ib_umem umem;
	काष्ठा mmu_पूर्णांकerval_notअगरier notअगरier;
	काष्ठा pid *tgid;

	/* An array of the pfns included in the on-demand paging umem. */
	अचिन्हित दीर्घ *pfn_list;

	/*
	 * An array with DMA addresses mapped क्रम pfns in pfn_list.
	 * The lower two bits designate access permissions.
	 * See ODP_READ_ALLOWED_BIT and ODP_WRITE_ALLOWED_BIT.
	 */
	dma_addr_t		*dma_list;
	/*
	 * The umem_mutex protects the page_list and dma_list fields of an ODP
	 * umem, allowing only a single thपढ़ो to map/unmap pages. The mutex
	 * also protects access to the mmu notअगरier counters.
	 */
	काष्ठा mutex		umem_mutex;
	व्योम			*निजी; /* क्रम the HW driver to use. */

	पूर्णांक npages;

	/*
	 * An implicit odp umem cannot be DMA mapped, has 0 length, and serves
	 * only as an anchor क्रम the driver to hold onto the per_mm. FIXME:
	 * This should be हटाओd and drivers should work with the per_mm
	 * directly.
	 */
	bool is_implicit_odp;

	अचिन्हित पूर्णांक		page_shअगरt;
पूर्ण;

अटल अंतरभूत काष्ठा ib_umem_odp *to_ib_umem_odp(काष्ठा ib_umem *umem)
अणु
	वापस container_of(umem, काष्ठा ib_umem_odp, umem);
पूर्ण

/* Returns the first page of an ODP umem. */
अटल अंतरभूत अचिन्हित दीर्घ ib_umem_start(काष्ठा ib_umem_odp *umem_odp)
अणु
	वापस umem_odp->notअगरier.पूर्णांकerval_tree.start;
पूर्ण

/* Returns the address of the page after the last one of an ODP umem. */
अटल अंतरभूत अचिन्हित दीर्घ ib_umem_end(काष्ठा ib_umem_odp *umem_odp)
अणु
	वापस umem_odp->notअगरier.पूर्णांकerval_tree.last + 1;
पूर्ण

अटल अंतरभूत माप_प्रकार ib_umem_odp_num_pages(काष्ठा ib_umem_odp *umem_odp)
अणु
	वापस (ib_umem_end(umem_odp) - ib_umem_start(umem_odp)) >>
	       umem_odp->page_shअगरt;
पूर्ण

/*
 * The lower 2 bits of the DMA address संकेत the R/W permissions क्रम
 * the entry. To upgrade the permissions, provide the appropriate
 * biपंचांगask to the map_dma_pages function.
 *
 * Be aware that upgrading a mapped address might result in change of
 * the DMA address क्रम the page.
 */
#घोषणा ODP_READ_ALLOWED_BIT  (1<<0ULL)
#घोषणा ODP_WRITE_ALLOWED_BIT (1<<1ULL)

#घोषणा ODP_DMA_ADDR_MASK (~(ODP_READ_ALLOWED_BIT | ODP_WRITE_ALLOWED_BIT))

#अगर_घोषित CONFIG_INFINIBAND_ON_DEMAND_PAGING

काष्ठा ib_umem_odp *
ib_umem_odp_get(काष्ठा ib_device *device, अचिन्हित दीर्घ addr, माप_प्रकार size,
		पूर्णांक access, स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops);
काष्ठा ib_umem_odp *ib_umem_odp_alloc_implicit(काष्ठा ib_device *device,
					       पूर्णांक access);
काष्ठा ib_umem_odp *
ib_umem_odp_alloc_child(काष्ठा ib_umem_odp *root_umem, अचिन्हित दीर्घ addr,
			माप_प्रकार size,
			स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops);
व्योम ib_umem_odp_release(काष्ठा ib_umem_odp *umem_odp);

पूर्णांक ib_umem_odp_map_dma_and_lock(काष्ठा ib_umem_odp *umem_odp, u64 start_offset,
				 u64 bcnt, u64 access_mask, bool fault);

व्योम ib_umem_odp_unmap_dma_pages(काष्ठा ib_umem_odp *umem_odp, u64 start_offset,
				 u64 bound);

#अन्यथा /* CONFIG_INFINIBAND_ON_DEMAND_PAGING */

अटल अंतरभूत काष्ठा ib_umem_odp *
ib_umem_odp_get(काष्ठा ib_device *device, अचिन्हित दीर्घ addr, माप_प्रकार size,
		पूर्णांक access, स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम ib_umem_odp_release(काष्ठा ib_umem_odp *umem_odp) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_INFINIBAND_ON_DEMAND_PAGING */

#पूर्ण_अगर /* IB_UMEM_ODP_H */
