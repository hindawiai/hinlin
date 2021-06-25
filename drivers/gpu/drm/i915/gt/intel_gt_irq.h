<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित INTEL_GT_IRQ_H
#घोषणा INTEL_GT_IRQ_H

#समावेश <linux/types.h>

काष्ठा पूर्णांकel_gt;

#घोषणा GEN8_GT_IRQS (GEN8_GT_RCS_IRQ | \
		      GEN8_GT_BCS_IRQ | \
		      GEN8_GT_VCS0_IRQ | \
		      GEN8_GT_VCS1_IRQ | \
		      GEN8_GT_VECS_IRQ | \
		      GEN8_GT_PM_IRQ | \
		      GEN8_GT_GUC_IRQ)

व्योम gen11_gt_irq_reset(काष्ठा पूर्णांकel_gt *gt);
व्योम gen11_gt_irq_postinstall(काष्ठा पूर्णांकel_gt *gt);
व्योम gen11_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, स्थिर u32 master_ctl);

bool gen11_gt_reset_one_iir(काष्ठा पूर्णांकel_gt *gt,
			    स्थिर अचिन्हित पूर्णांक bank,
			    स्थिर अचिन्हित पूर्णांक bit);

व्योम gen5_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, u32 gt_iir);

व्योम gen5_gt_irq_postinstall(काष्ठा पूर्णांकel_gt *gt);
व्योम gen5_gt_irq_reset(काष्ठा पूर्णांकel_gt *gt);
व्योम gen5_gt_disable_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask);
व्योम gen5_gt_enable_irq(काष्ठा पूर्णांकel_gt *gt, u32 mask);

व्योम gen6_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, u32 gt_iir);

व्योम gen8_gt_irq_handler(काष्ठा पूर्णांकel_gt *gt, u32 master_ctl);
व्योम gen8_gt_irq_reset(काष्ठा पूर्णांकel_gt *gt);
व्योम gen8_gt_irq_postinstall(काष्ठा पूर्णांकel_gt *gt);

#पूर्ण_अगर /* INTEL_GT_IRQ_H */
