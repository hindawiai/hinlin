<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 Texas Instruments Inc.
 *
 * David Griego, <dagriego@biglakesoftware.com>
 * Dale Farnsworth, <dale@farnsworth.org>
 * Archit Taneja, <archit@ti.com>
 */
#अगर_अघोषित TI_CSC_H
#घोषणा TI_CSC_H

/* VPE color space converter regs */
#घोषणा CSC_CSC00		0x00
#घोषणा CSC_A0_MASK		0x1fff
#घोषणा CSC_A0_SHIFT		0
#घोषणा CSC_B0_MASK		0x1fff
#घोषणा CSC_B0_SHIFT		16

#घोषणा CSC_CSC01		0x04
#घोषणा CSC_C0_MASK		0x1fff
#घोषणा CSC_C0_SHIFT		0
#घोषणा CSC_A1_MASK		0x1fff
#घोषणा CSC_A1_SHIFT		16

#घोषणा CSC_CSC02		0x08
#घोषणा CSC_B1_MASK		0x1fff
#घोषणा CSC_B1_SHIFT		0
#घोषणा CSC_C1_MASK		0x1fff
#घोषणा CSC_C1_SHIFT		16

#घोषणा CSC_CSC03		0x0c
#घोषणा CSC_A2_MASK		0x1fff
#घोषणा CSC_A2_SHIFT		0
#घोषणा CSC_B2_MASK		0x1fff
#घोषणा CSC_B2_SHIFT		16

#घोषणा CSC_CSC04		0x10
#घोषणा CSC_C2_MASK		0x1fff
#घोषणा CSC_C2_SHIFT		0
#घोषणा CSC_D0_MASK		0x0fff
#घोषणा CSC_D0_SHIFT		16

#घोषणा CSC_CSC05		0x14
#घोषणा CSC_D1_MASK		0x0fff
#घोषणा CSC_D1_SHIFT		0
#घोषणा CSC_D2_MASK		0x0fff
#घोषणा CSC_D2_SHIFT		16

#घोषणा CSC_BYPASS		(1 << 28)

काष्ठा csc_data अणु
	व्योम __iomem		*base;
	काष्ठा resource		*res;

	काष्ठा platक्रमm_device	*pdev;
पूर्ण;

व्योम csc_dump_regs(काष्ठा csc_data *csc);
व्योम csc_set_coeff_bypass(काष्ठा csc_data *csc, u32 *csc_reg5);
व्योम csc_set_coeff(काष्ठा csc_data *csc, u32 *csc_reg0,
		   काष्ठा v4l2_क्रमmat *src_fmt, काष्ठा v4l2_क्रमmat *dst_fmt);

काष्ठा csc_data *csc_create(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *res_name);

#पूर्ण_अगर
