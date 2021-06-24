<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CAAM Error Reporting code header
 *
 * Copyright 2009-2011 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित CAAM_ERROR_H
#घोषणा CAAM_ERROR_H

#समावेश "desc.h"

#घोषणा CAAM_ERROR_STR_MAX 302

पूर्णांक caam_strstatus(काष्ठा device *dev, u32 status, bool qi_v2);

#घोषणा caam_jr_strstatus(jrdev, status) caam_strstatus(jrdev, status, false)
#घोषणा caam_qi2_strstatus(qidev, status) caam_strstatus(qidev, status, true)

व्योम caam_dump_sg(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
		  पूर्णांक rowsize, पूर्णांक groupsize, काष्ठा scatterlist *sg,
		  माप_प्रकार tlen, bool ascii);

अटल अंतरभूत bool is_mdha(u32 algtype)
अणु
	वापस (algtype & OP_ALG_ALGSEL_MASK & ~OP_ALG_ALGSEL_SUBMASK) ==
	       OP_ALG_CHA_MDHA;
पूर्ण
#पूर्ण_अगर /* CAAM_ERROR_H */
