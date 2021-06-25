<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CAAM खुला-level include definitions क्रम the JobR backend
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित JR_H
#घोषणा JR_H

/* Prototypes क्रम backend-level services exposed to APIs */
काष्ठा device *caam_jr_alloc(व्योम);
व्योम caam_jr_मुक्त(काष्ठा device *rdev);
पूर्णांक caam_jr_enqueue(काष्ठा device *dev, u32 *desc,
		    व्योम (*cbk)(काष्ठा device *dev, u32 *desc, u32 status,
				व्योम *areq),
		    व्योम *areq);

#पूर्ण_अगर /* JR_H */
