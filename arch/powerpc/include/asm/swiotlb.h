<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 Becky Bruce, Freescale Semiconductor
 */

#अगर_अघोषित __ASM_SWIOTLB_H
#घोषणा __ASM_SWIOTLB_H

#समावेश <linux/swiotlb.h>

बाह्य अचिन्हित पूर्णांक ppc_swiotlb_enable;

#अगर_घोषित CONFIG_SWIOTLB
व्योम swiotlb_detect_4g(व्योम);
#अन्यथा
अटल अंतरभूत व्योम swiotlb_detect_4g(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SWIOTLB_H */
