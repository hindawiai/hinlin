<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#अगर_अघोषित __MANTIS_DMA_H
#घोषणा __MANTIS_DMA_H

बाह्य पूर्णांक mantis_dma_init(काष्ठा mantis_pci *mantis);
बाह्य पूर्णांक mantis_dma_निकास(काष्ठा mantis_pci *mantis);
बाह्य व्योम mantis_dma_start(काष्ठा mantis_pci *mantis);
बाह्य व्योम mantis_dma_stop(काष्ठा mantis_pci *mantis);
बाह्य व्योम mantis_dma_xfer(काष्ठा tasklet_काष्ठा *t);

#पूर्ण_अगर /* __MANTIS_DMA_H */
