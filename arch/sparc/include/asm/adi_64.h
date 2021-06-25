<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* adi_64.h: ADI related data काष्ठाures
 *
 * Copyright (c) 2016 Oracle and/or its affiliates. All rights reserved.
 * Author: Khalid Aziz (khalid.aziz@oracle.com)
 */
#अगर_अघोषित __ASM_SPARC64_ADI_H
#घोषणा __ASM_SPARC64_ADI_H

#समावेश <linux/types.h>

#अगर_अघोषित __ASSEMBLY__

काष्ठा adi_caps अणु
	__u64 blksz;
	__u64 nbits;
	__u64 ue_on_adi;
पूर्ण;

काष्ठा adi_config अणु
	bool enabled;
	काष्ठा adi_caps caps;
पूर्ण;

बाह्य काष्ठा adi_config adi_state;

बाह्य व्योम mdesc_adi_init(व्योम);

अटल अंतरभूत bool adi_capable(व्योम)
अणु
	वापस adi_state.enabled;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ adi_blksize(व्योम)
अणु
	वापस adi_state.caps.blksz;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ adi_nbits(व्योम)
अणु
	वापस adi_state.caps.nbits;
पूर्ण

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* !(__ASM_SPARC64_ADI_H) */
