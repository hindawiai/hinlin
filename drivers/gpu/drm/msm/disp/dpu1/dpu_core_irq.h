<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DPU_CORE_IRQ_H__
#घोषणा __DPU_CORE_IRQ_H__

#समावेश "dpu_kms.h"
#समावेश "dpu_hw_interrupts.h"

/**
 * dpu_core_irq_preinstall - perक्रमm pre-installation of core IRQ handler
 * @dpu_kms:		DPU handle
 * @वापस:		none
 */
व्योम dpu_core_irq_preinstall(काष्ठा dpu_kms *dpu_kms);

/**
 * dpu_core_irq_uninstall - uninstall core IRQ handler
 * @dpu_kms:		DPU handle
 * @वापस:		none
 */
व्योम dpu_core_irq_uninstall(काष्ठा dpu_kms *dpu_kms);

/**
 * dpu_core_irq - core IRQ handler
 * @dpu_kms:		DPU handle
 * @वापस:		पूर्णांकerrupt handling status
 */
irqवापस_t dpu_core_irq(काष्ठा dpu_kms *dpu_kms);

/**
 * dpu_core_irq_idx_lookup - IRQ helper function क्रम lookup irq_idx from HW
 *                      पूर्णांकerrupt mapping table.
 * @dpu_kms:		DPU handle
 * @पूर्णांकr_type:		DPU HW पूर्णांकerrupt type क्रम lookup
 * @instance_idx:	DPU HW block instance defined in dpu_hw_mdss.h
 * @वापस:		irq_idx or -EINVAL when fail to lookup
 */
पूर्णांक dpu_core_irq_idx_lookup(
		काष्ठा dpu_kms *dpu_kms,
		क्रमागत dpu_पूर्णांकr_type पूर्णांकr_type,
		uपूर्णांक32_t instance_idx);

/**
 * dpu_core_irq_enable - IRQ helper function क्रम enabling one or more IRQs
 * @dpu_kms:		DPU handle
 * @irq_idxs:		Array of irq index
 * @irq_count:		Number of irq_idx provided in the array
 * @वापस:		0 क्रम success enabling IRQ, otherwise failure
 *
 * This function increments count on each enable and decrements on each
 * disable.  Interrupts is enabled अगर count is 0 beक्रमe increment.
 */
पूर्णांक dpu_core_irq_enable(
		काष्ठा dpu_kms *dpu_kms,
		पूर्णांक *irq_idxs,
		uपूर्णांक32_t irq_count);

/**
 * dpu_core_irq_disable - IRQ helper function क्रम disabling one of more IRQs
 * @dpu_kms:		DPU handle
 * @irq_idxs:		Array of irq index
 * @irq_count:		Number of irq_idx provided in the array
 * @वापस:		0 क्रम success disabling IRQ, otherwise failure
 *
 * This function increments count on each enable and decrements on each
 * disable.  Interrupts is disabled अगर count is 0 after decrement.
 */
पूर्णांक dpu_core_irq_disable(
		काष्ठा dpu_kms *dpu_kms,
		पूर्णांक *irq_idxs,
		uपूर्णांक32_t irq_count);

/**
 * dpu_core_irq_पढ़ो - IRQ helper function क्रम पढ़ोing IRQ status
 * @dpu_kms:		DPU handle
 * @irq_idx:		irq index
 * @clear:		True to clear the irq after पढ़ो
 * @वापस:		non-zero अगर irq detected; otherwise no irq detected
 */
u32 dpu_core_irq_पढ़ो(
		काष्ठा dpu_kms *dpu_kms,
		पूर्णांक irq_idx,
		bool clear);

/**
 * dpu_core_irq_रेजिस्टर_callback - For रेजिस्टरing callback function on IRQ
 *                             पूर्णांकerrupt
 * @dpu_kms:		DPU handle
 * @irq_idx:		irq index
 * @irq_cb:		IRQ callback काष्ठाure, containing callback function
 *			and argument. Passing शून्य क्रम irq_cb will unरेजिस्टर
 *			the callback क्रम the given irq_idx
 *			This must exist until un-registration.
 * @वापस:		0 क्रम success रेजिस्टरing callback, otherwise failure
 *
 * This function supports registration of multiple callbacks क्रम each पूर्णांकerrupt.
 */
पूर्णांक dpu_core_irq_रेजिस्टर_callback(
		काष्ठा dpu_kms *dpu_kms,
		पूर्णांक irq_idx,
		काष्ठा dpu_irq_callback *irq_cb);

/**
 * dpu_core_irq_unरेजिस्टर_callback - For unरेजिस्टरing callback function on IRQ
 *                             पूर्णांकerrupt
 * @dpu_kms:		DPU handle
 * @irq_idx:		irq index
 * @irq_cb:		IRQ callback काष्ठाure, containing callback function
 *			and argument. Passing शून्य क्रम irq_cb will unरेजिस्टर
 *			the callback क्रम the given irq_idx
 *			This must match with registration.
 * @वापस:		0 क्रम success रेजिस्टरing callback, otherwise failure
 *
 * This function supports registration of multiple callbacks क्रम each पूर्णांकerrupt.
 */
पूर्णांक dpu_core_irq_unरेजिस्टर_callback(
		काष्ठा dpu_kms *dpu_kms,
		पूर्णांक irq_idx,
		काष्ठा dpu_irq_callback *irq_cb);

/**
 * dpu_debugfs_core_irq_init - रेजिस्टर core irq debugfs
 * @dpu_kms: poपूर्णांकer to kms
 * @parent: debugfs directory root
 */
व्योम dpu_debugfs_core_irq_init(काष्ठा dpu_kms *dpu_kms,
		काष्ठा dentry *parent);

#पूर्ण_अगर /* __DPU_CORE_IRQ_H__ */
