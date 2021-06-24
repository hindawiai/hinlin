<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CAAM/SEC 4.x functions क्रम using scatterlists in caam driver
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 */

#अगर_अघोषित _SG_SW_SEC4_H_
#घोषणा _SG_SW_SEC4_H_

#समावेश "ctrl.h"
#समावेश "regs.h"
#समावेश "sg_sw_qm2.h"
#समावेश <soc/fsl/dpaa2-fd.h>

काष्ठा sec4_sg_entry अणु
	u64 ptr;
	u32 len;
	u32 bpid_offset;
पूर्ण;

/*
 * convert single dma address to h/w link table क्रमmat
 */
अटल अंतरभूत व्योम dma_to_sec4_sg_one(काष्ठा sec4_sg_entry *sec4_sg_ptr,
				      dma_addr_t dma, u32 len, u16 offset)
अणु
	अगर (caam_dpaa2) अणु
		dma_to_qm_sg_one((काष्ठा dpaa2_sg_entry *)sec4_sg_ptr, dma, len,
				 offset);
	पूर्ण अन्यथा अणु
		sec4_sg_ptr->ptr = cpu_to_caam_dma64(dma);
		sec4_sg_ptr->len = cpu_to_caam32(len);
		sec4_sg_ptr->bpid_offset = cpu_to_caam32(offset &
							 SEC4_SG_OFFSET_MASK);
	पूर्ण

	prपूर्णांक_hex_dump_debug("sec4_sg_ptr@: ", DUMP_PREFIX_ADDRESS, 16, 4,
			     sec4_sg_ptr, माप(काष्ठा sec4_sg_entry), 1);
पूर्ण

/*
 * convert scatterlist to h/w link table क्रमmat
 * but करोes not have final bit; instead, वापसs last entry
 */
अटल अंतरभूत काष्ठा sec4_sg_entry *
sg_to_sec4_sg(काष्ठा scatterlist *sg, पूर्णांक len,
	      काष्ठा sec4_sg_entry *sec4_sg_ptr, u16 offset)
अणु
	पूर्णांक ent_len;

	जबतक (len) अणु
		ent_len = min_t(पूर्णांक, sg_dma_len(sg), len);

		dma_to_sec4_sg_one(sec4_sg_ptr, sg_dma_address(sg), ent_len,
				   offset);
		sec4_sg_ptr++;
		sg = sg_next(sg);
		len -= ent_len;
	पूर्ण
	वापस sec4_sg_ptr - 1;
पूर्ण

अटल अंतरभूत व्योम sg_to_sec4_set_last(काष्ठा sec4_sg_entry *sec4_sg_ptr)
अणु
	अगर (caam_dpaa2)
		dpaa2_sg_set_final((काष्ठा dpaa2_sg_entry *)sec4_sg_ptr, true);
	अन्यथा
		sec4_sg_ptr->len |= cpu_to_caam32(SEC4_SG_LEN_FIN);
पूर्ण

/*
 * convert scatterlist to h/w link table क्रमmat
 * scatterlist must have been previously dma mapped
 */
अटल अंतरभूत व्योम sg_to_sec4_sg_last(काष्ठा scatterlist *sg, पूर्णांक len,
				      काष्ठा sec4_sg_entry *sec4_sg_ptr,
				      u16 offset)
अणु
	sec4_sg_ptr = sg_to_sec4_sg(sg, len, sec4_sg_ptr, offset);
	sg_to_sec4_set_last(sec4_sg_ptr);
पूर्ण

#पूर्ण_अगर /* _SG_SW_SEC4_H_ */
