<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2006-2007  Hans Verkuil <hverkuil@xs4all.nl>

 */

#अगर_अघोषित IVTV_UDMA_H
#घोषणा IVTV_UDMA_H

/* User DMA functions */
व्योम ivtv_udma_get_page_info(काष्ठा ivtv_dma_page_info *dma_page, अचिन्हित दीर्घ first, अचिन्हित दीर्घ size);
पूर्णांक ivtv_udma_fill_sg_list(काष्ठा ivtv_user_dma *dma, काष्ठा ivtv_dma_page_info *dma_page, पूर्णांक map_offset);
व्योम ivtv_udma_fill_sg_array(काष्ठा ivtv_user_dma *dma, u32 buffer_offset, u32 buffer_offset_2, u32 split);
पूर्णांक ivtv_udma_setup(काष्ठा ivtv *itv, अचिन्हित दीर्घ ivtv_dest_addr,
		       व्योम __user *userbuf, पूर्णांक size_in_bytes);
व्योम ivtv_udma_unmap(काष्ठा ivtv *itv);
व्योम ivtv_udma_मुक्त(काष्ठा ivtv *itv);
व्योम ivtv_udma_alloc(काष्ठा ivtv *itv);
व्योम ivtv_udma_prepare(काष्ठा ivtv *itv);
व्योम ivtv_udma_start(काष्ठा ivtv *itv);

अटल अंतरभूत व्योम ivtv_udma_sync_क्रम_device(काष्ठा ivtv *itv)
अणु
	pci_dma_sync_single_क्रम_device(itv->pdev, itv->udma.SG_handle,
		माप(itv->udma.SGarray), PCI_DMA_TODEVICE);
पूर्ण

अटल अंतरभूत व्योम ivtv_udma_sync_क्रम_cpu(काष्ठा ivtv *itv)
अणु
	pci_dma_sync_single_क्रम_cpu(itv->pdev, itv->udma.SG_handle,
		माप(itv->udma.SGarray), PCI_DMA_TODEVICE);
पूर्ण

#पूर्ण_अगर
