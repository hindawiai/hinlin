<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Omnitek Scatter-Gather DMA Controller
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#अगर_अघोषित COBALT_OMNITEK_H
#घोषणा COBALT_OMNITEK_H

#समावेश <linux/scatterlist.h>
#समावेश "cobalt-driver.h"

काष्ठा sg_dma_descriptor अणु
	u32 pci_l;
	u32 pci_h;

	u32 local;
	u32 reserved0;

	u32 next_l;
	u32 next_h;

	u32 bytes;
	u32 reserved1;
पूर्ण;

पूर्णांक omni_sg_dma_init(काष्ठा cobalt *cobalt);
व्योम omni_sg_dma_पात_channel(काष्ठा cobalt_stream *s);
व्योम omni_sg_dma_start(काष्ठा cobalt_stream *s, काष्ठा sg_dma_desc_info *desc);
bool is_dma_करोne(काष्ठा cobalt_stream *s);

पूर्णांक descriptor_list_create(काष्ठा cobalt *cobalt,
	काष्ठा scatterlist *scatter_list, bool to_pci, अचिन्हित sglen,
	अचिन्हित size, अचिन्हित width, अचिन्हित stride,
	काष्ठा sg_dma_desc_info *desc);

व्योम descriptor_list_chain(काष्ठा sg_dma_desc_info *this,
			   काष्ठा sg_dma_desc_info *next);
व्योम descriptor_list_loopback(काष्ठा sg_dma_desc_info *desc);
व्योम descriptor_list_end_of_chain(काष्ठा sg_dma_desc_info *desc);

व्योम *descriptor_list_allocate(काष्ठा sg_dma_desc_info *desc, माप_प्रकार bytes);
व्योम descriptor_list_मुक्त(काष्ठा sg_dma_desc_info *desc);

व्योम descriptor_list_पूर्णांकerrupt_enable(काष्ठा sg_dma_desc_info *desc);
व्योम descriptor_list_पूर्णांकerrupt_disable(काष्ठा sg_dma_desc_info *desc);

#पूर्ण_अगर
