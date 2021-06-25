<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#अगर_अघोषित HVA_MEM_H
#घोषणा HVA_MEM_H

/**
 * काष्ठा hva_buffer - hva buffer
 *
 * @name:  name of requester
 * @paddr: physical address (क्रम hardware)
 * @vaddr: भव address (kernel can पढ़ो/ग_लिखो)
 * @size:  size of buffer
 */
काष्ठा hva_buffer अणु
	स्थिर अक्षर		*name;
	dma_addr_t		paddr;
	व्योम			*vaddr;
	u32			size;
पूर्ण;

पूर्णांक hva_mem_alloc(काष्ठा hva_ctx *ctx,
		  __u32 size,
		  स्थिर अक्षर *name,
		  काष्ठा hva_buffer **buf);

व्योम hva_mem_मुक्त(काष्ठा hva_ctx *ctx,
		  काष्ठा hva_buffer *buf);

#पूर्ण_अगर /* HVA_MEM_H */
