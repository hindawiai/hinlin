<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/hardware/memc.h
 *
 *  Copyright (C) Russell King.
 */
#घोषणा VDMA_ALIGNMENT	PAGE_SIZE
#घोषणा VDMA_XFERSIZE	16
#घोषणा VDMA_INIT	0
#घोषणा VDMA_START	1
#घोषणा VDMA_END	2

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम memc_ग_लिखो(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ val);

#घोषणा video_set_dma(start,end,offset)				\
करो अणु								\
	memc_ग_लिखो (VDMA_START, (start >> 2));			\
	memc_ग_लिखो (VDMA_END, (end - VDMA_XFERSIZE) >> 2);	\
	memc_ग_लिखो (VDMA_INIT, (offset >> 2));			\
पूर्ण जबतक (0)

#पूर्ण_अगर
