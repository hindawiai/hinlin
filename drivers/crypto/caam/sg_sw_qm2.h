<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright 2015-2016 Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 */

#अगर_अघोषित _SG_SW_QM2_H_
#घोषणा _SG_SW_QM2_H_

#समावेश <soc/fsl/dpaa2-fd.h>

अटल अंतरभूत व्योम dma_to_qm_sg_one(काष्ठा dpaa2_sg_entry *qm_sg_ptr,
				    dma_addr_t dma, u32 len, u16 offset)
अणु
	dpaa2_sg_set_addr(qm_sg_ptr, dma);
	dpaa2_sg_set_क्रमmat(qm_sg_ptr, dpaa2_sg_single);
	dpaa2_sg_set_final(qm_sg_ptr, false);
	dpaa2_sg_set_len(qm_sg_ptr, len);
	dpaa2_sg_set_bpid(qm_sg_ptr, 0);
	dpaa2_sg_set_offset(qm_sg_ptr, offset);
पूर्ण

/*
 * convert scatterlist to h/w link table क्रमmat
 * but करोes not have final bit; instead, वापसs last entry
 */
अटल अंतरभूत काष्ठा dpaa2_sg_entry *
sg_to_qm_sg(काष्ठा scatterlist *sg, पूर्णांक len,
	    काष्ठा dpaa2_sg_entry *qm_sg_ptr, u16 offset)
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
				    काष्ठा dpaa2_sg_entry *qm_sg_ptr,
				    u16 offset)
अणु
	qm_sg_ptr = sg_to_qm_sg(sg, len, qm_sg_ptr, offset);
	dpaa2_sg_set_final(qm_sg_ptr, true);
पूर्ण

#पूर्ण_अगर /* _SG_SW_QM2_H_ */
