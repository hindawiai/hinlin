<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#अगर_अघोषित _D71_DEV_H_
#घोषणा _D71_DEV_H_

#समावेश "komeda_dev.h"
#समावेश "komeda_pipeline.h"
#समावेश "d71_regs.h"

काष्ठा d71_pipeline अणु
	काष्ठा komeda_pipeline base;

	/* d71 निजी pipeline blocks */
	u32 __iomem	*lpu_addr;
	u32 __iomem	*cu_addr;
	u32 __iomem	*करोu_addr;
	u32 __iomem	*करोu_ft_coeff_addr; /* क्रमward transक्रमm coeffs table */
पूर्ण;

काष्ठा d71_dev अणु
	काष्ठा komeda_dev *mdev;

	पूर्णांक	num_blocks;
	पूर्णांक	num_pipelines;
	पूर्णांक	num_rich_layers;
	u32	max_line_size;
	u32	max_vsize;
	u32	supports_dual_link : 1;
	u32	पूर्णांकegrates_tbu : 1;

	/* global रेजिस्टर blocks */
	u32 __iomem	*gcu_addr;
	/* scaling coeffs table */
	u32 __iomem	*glb_scl_coeff_addr[D71_MAX_GLB_SCL_COEFF];
	u32 __iomem	*periph_addr;

	काष्ठा d71_pipeline *pipes[D71_MAX_PIPELINE];
पूर्ण;

#घोषणा to_d71_pipeline(x)	container_of(x, काष्ठा d71_pipeline, base)

बाह्य स्थिर काष्ठा komeda_pipeline_funcs d71_pipeline_funcs;

पूर्णांक d71_probe_block(काष्ठा d71_dev *d71,
		    काष्ठा block_header *blk, u32 __iomem *reg);
व्योम d71_पढ़ो_block_header(u32 __iomem *reg, काष्ठा block_header *blk);

व्योम d71_dump(काष्ठा komeda_dev *mdev, काष्ठा seq_file *sf);

#पूर्ण_अगर /* !_D71_DEV_H_ */
