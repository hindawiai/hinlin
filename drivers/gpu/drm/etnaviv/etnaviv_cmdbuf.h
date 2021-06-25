<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2017 Etnaviv Project
 */

#अगर_अघोषित __ETNAVIV_CMDBUF_H__
#घोषणा __ETNAVIV_CMDBUF_H__

#समावेश <linux/types.h>

काष्ठा device;
काष्ठा etnaviv_iommu_context;
काष्ठा etnaviv_vram_mapping;
काष्ठा etnaviv_cmdbuf_suballoc;
काष्ठा etnaviv_perfmon_request;

काष्ठा etnaviv_cmdbuf अणु
	/* suballocator this cmdbuf is allocated from */
	काष्ठा etnaviv_cmdbuf_suballoc *suballoc;
	/* cmdbuf properties */
	पूर्णांक suballoc_offset;
	व्योम *vaddr;
	u32 size;
	u32 user_size;
पूर्ण;

काष्ठा etnaviv_cmdbuf_suballoc *
etnaviv_cmdbuf_suballoc_new(काष्ठा device *dev);
व्योम etnaviv_cmdbuf_suballoc_destroy(काष्ठा etnaviv_cmdbuf_suballoc *suballoc);
पूर्णांक etnaviv_cmdbuf_suballoc_map(काष्ठा etnaviv_cmdbuf_suballoc *suballoc,
				काष्ठा etnaviv_iommu_context *context,
				काष्ठा etnaviv_vram_mapping *mapping,
				u32 memory_base);
व्योम etnaviv_cmdbuf_suballoc_unmap(काष्ठा etnaviv_iommu_context *context,
				   काष्ठा etnaviv_vram_mapping *mapping);


पूर्णांक etnaviv_cmdbuf_init(काष्ठा etnaviv_cmdbuf_suballoc *suballoc,
		काष्ठा etnaviv_cmdbuf *cmdbuf, u32 size);
व्योम etnaviv_cmdbuf_मुक्त(काष्ठा etnaviv_cmdbuf *cmdbuf);

u32 etnaviv_cmdbuf_get_va(काष्ठा etnaviv_cmdbuf *buf,
			  काष्ठा etnaviv_vram_mapping *mapping);
dma_addr_t etnaviv_cmdbuf_get_pa(काष्ठा etnaviv_cmdbuf *buf);

#पूर्ण_अगर /* __ETNAVIV_CMDBUF_H__ */
