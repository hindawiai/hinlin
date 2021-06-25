<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google, Inc
 */

#अगर_अघोषित __ADRENO_SMMU_PRIV_H
#घोषणा __ADRENO_SMMU_PRIV_H

#समावेश <linux/io-pgtable.h>

/**
 * काष्ठा adreno_smmu_priv - निजी पूर्णांकerface between adreno-smmu and GPU
 *
 * @cookie:        An opque token provided by adreno-smmu and passed
 *                 back पूर्णांकo the callbacks
 * @get_ttbr1_cfg: Get the TTBR1 config क्रम the GPUs context-bank
 * @set_ttbr0_cfg: Set the TTBR0 config क्रम the GPUs context bank.  A
 *                 शून्य config disables TTBR0 translation, otherwise
 *                 TTBR0 translation is enabled with the specअगरied cfg
 *
 * The GPU driver (drm/msm) and adreno-smmu work together क्रम controlling
 * the GPU's SMMU instance.  This is by necessity, as the GPU is directly
 * updating the SMMU क्रम context चयनes, जबतक on the other hand we करो
 * not want to duplicate all of the initial setup logic from arm-smmu.
 *
 * This निजी पूर्णांकerface is used क्रम the two drivers to coordinate.  The
 * cookie and callback functions are populated when the GPU driver attaches
 * it's करोमुख्य.
 */
काष्ठा adreno_smmu_priv अणु
    स्थिर व्योम *cookie;
    स्थिर काष्ठा io_pgtable_cfg *(*get_ttbr1_cfg)(स्थिर व्योम *cookie);
    पूर्णांक (*set_ttbr0_cfg)(स्थिर व्योम *cookie, स्थिर काष्ठा io_pgtable_cfg *cfg);
पूर्ण;

#पूर्ण_अगर /* __ADRENO_SMMU_PRIV_H */
