<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  SRAM Memory Management
 *
 *  Copyright (c) 2011 Marvell Semiconductors Inc.
 */

#अगर_अघोषित __DMA_MMP_TDMA_H
#घोषणा __DMA_MMP_TDMA_H

#समावेश <linux/genभाग.स>

/* ARBITRARY:  SRAM allocations are multiples of this 2^N size */
#घोषणा SRAM_GRANULARITY	512

क्रमागत sram_type अणु
	MMP_SRAM_UNDEFINED = 0,
	MMP_ASRAM,
	MMP_ISRAM,
पूर्ण;

काष्ठा sram_platdata अणु
	अक्षर *pool_name;
	पूर्णांक granularity;
पूर्ण;

#अगर_घोषित CONFIG_MMP_SRAM
बाह्य काष्ठा gen_pool *sram_get_gpool(अक्षर *pool_name);
#अन्यथा
अटल अंतरभूत काष्ठा gen_pool *sram_get_gpool(अक्षर *pool_name)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __DMA_MMP_TDMA_H */
