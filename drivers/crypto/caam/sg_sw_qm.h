<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 */

#अगर_अघोषित __SG_SW_QM_H
#घोषणा __SG_SW_QM_H

#समावेश <soc/fsl/qman.h>
#समावेश "regs.h"

अटल अंतरभूत व्योम __dma_to_qm_sg(काष्ठा qm_sg_entry *qm_sg_ptr, dma_addr_t dma,
				  u16 offset)
अणु
	qm_sg_entry_set64(qm_sg_ptr, dma);
	qm_sg_ptr->__reserved2 = 0;
	qm_sg_ptr->bpid = 0;
	qm_sg_ptr->offset = cpu_to_be16(offset & QM_SG_OFF_MASK);
पूर्ण

अटल अंतरभूत व्योम dma_to_qm_sg_one(काष्ठा qm_sg_entry *qm_sg_ptr,
				    dma_addr_t dma, u32 len, u16 offset)
अणु
	__dma_to_qm_sg(qm_sg_ptr, dma, offset);
	qm_sg_entry_set_len(qm_sg_ptr, len);
पूर्ण

अटल अंतरभूत व्योम dma_to_qm_sg_one_last(काष्ठा qm_sg_entry *qm_sg_ptr,
					 dma_addr_t dma, u32 len, u16 offset)
अणु
	__dma_to_qm_sg(qm_sg_ptr, dma, offset);
	qm_sg_entry_set_f(qm_sg_ptr, len);
पूर्ण

अटल अंतरभूत व्योम dma_to_qm_sg_one_ext(काष्ठा qm_sg_entry *qm_sg_ptr,
					dma_addr_t dma, u32 len, u16 offset)
अणु
	__dma_to_qm_sg(qm_sg_ptr, dma, offset);
	qm_sg_ptr->cfg = cpu_to_be32(QM_SG_EXT | (len & QM_SG_LEN_MASK));
पूर्ण

अटल अंतरभूत व्योम dma_to_qm_sg_one_last_ext(काष्ठा qm_sg_entry *qm_sg_ptr,
					     dma_addr_t dma, u32 len,
					     u16 offset)
अणु
	__dma_to_qm_sg(qm_sg_ptr, dma, offset);
	qm_sg_ptr->cfg = cpu_to_be32(QM_SG_EXT | QM_SG_FIN |
				     (len & QM_SG_LEN_MASK));
पूर्ण

/*
 * convert scatterlist to h/w link table क्रमmat
 * but करोes not have final bit; instead, वापसs last entry
 */
अटल अंतरभूत काष्ठा qm_sg_entry *
sg_to_qm_sg(काष्ठा scatterlist *sg, पूर्णांक len,
	    काष्ठा qm_sg_entry *qm_sg_ptr, u16 offset)
अणु
	पूर्णांक ent_len;

	जबतक (len) अणु
		ent_len = min_t(पूर्णांक, sg_dma_len(sg), len);

		dma_to_qm_sg_one(qm_sg_ptr, sg_dma_address(sg), ent_len,
				 offset);
		qm_sg_ptr++;
		sg = sg_next(sg);
		len -= ent_len;
	पूर्ण
	वापस qm_sg_ptr - 1;
पूर्ण

/*
 * convert scatterlist to h/w link table क्रमmat
 * scatterlist must have been previously dma mapped
 */
अटल अंतरभूत व्योम sg_to_qm_sg_last(काष्ठा scatterlist *sg, पूर्णांक len,
				    काष्ठा qm_sg_entry *qm_sg_ptr, u16 offset)
अणु
	qm_sg_ptr = sg_to_qm_sg(sg, len, qm_sg_ptr, offset);
	qm_sg_entry_set_f(qm_sg_ptr, qm_sg_entry_get_len(qm_sg_ptr));
पूर्ण

#पूर्ण_अगर /* __SG_SW_QM_H */
