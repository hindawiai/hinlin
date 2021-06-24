<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_VBIF_H
#घोषणा _DPU_HW_VBIF_H

#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"

काष्ठा dpu_hw_vbअगर;

/**
 * काष्ठा dpu_hw_vbअगर_ops : Interface to the VBIF hardware driver functions
 *  Assumption is these functions will be called after घड़ीs are enabled
 */
काष्ठा dpu_hw_vbअगर_ops अणु
	/**
	 * set_limit_conf - set transaction limit config
	 * @vbअगर: vbअगर context driver
	 * @xin_id: client पूर्णांकerface identअगरier
	 * @rd: true क्रम पढ़ो limit; false क्रम ग_लिखो limit
	 * @limit: outstanding transaction limit
	 */
	व्योम (*set_limit_conf)(काष्ठा dpu_hw_vbअगर *vbअगर,
			u32 xin_id, bool rd, u32 limit);

	/**
	 * get_limit_conf - get transaction limit config
	 * @vbअगर: vbअगर context driver
	 * @xin_id: client पूर्णांकerface identअगरier
	 * @rd: true क्रम पढ़ो limit; false क्रम ग_लिखो limit
	 * @वापस: outstanding transaction limit
	 */
	u32 (*get_limit_conf)(काष्ठा dpu_hw_vbअगर *vbअगर,
			u32 xin_id, bool rd);

	/**
	 * set_halt_ctrl - set halt control
	 * @vbअगर: vbअगर context driver
	 * @xin_id: client पूर्णांकerface identअगरier
	 * @enable: halt control enable
	 */
	व्योम (*set_halt_ctrl)(काष्ठा dpu_hw_vbअगर *vbअगर,
			u32 xin_id, bool enable);

	/**
	 * get_halt_ctrl - get halt control
	 * @vbअगर: vbअगर context driver
	 * @xin_id: client पूर्णांकerface identअगरier
	 * @वापस: halt control enable
	 */
	bool (*get_halt_ctrl)(काष्ठा dpu_hw_vbअगर *vbअगर,
			u32 xin_id);

	/**
	 * set_qos_remap - set QoS priority remap
	 * @vbअगर: vbअगर context driver
	 * @xin_id: client पूर्णांकerface identअगरier
	 * @level: priority level
	 * @remap_level: remapped level
	 */
	व्योम (*set_qos_remap)(काष्ठा dpu_hw_vbअगर *vbअगर,
			u32 xin_id, u32 level, u32 remap_level);

	/**
	 * set_mem_type - set memory type
	 * @vbअगर: vbअगर context driver
	 * @xin_id: client पूर्णांकerface identअगरier
	 * @value: memory type value
	 */
	व्योम (*set_mem_type)(काष्ठा dpu_hw_vbअगर *vbअगर,
			u32 xin_id, u32 value);

	/**
	 * clear_errors - clear any vbअगर errors
	 *	This function clears any detected pending/source errors
	 *	on the VBIF पूर्णांकerface, and optionally वापसs the detected
	 *	error mask(s).
	 * @vbअगर: vbअगर context driver
	 * @pnd_errors: poपूर्णांकer to pending error reporting variable
	 * @src_errors: poपूर्णांकer to source error reporting variable
	 */
	व्योम (*clear_errors)(काष्ठा dpu_hw_vbअगर *vbअगर,
		u32 *pnd_errors, u32 *src_errors);

	/**
	 * set_ग_लिखो_gather_en - set ग_लिखो_gather enable
	 * @vbअगर: vbअगर context driver
	 * @xin_id: client पूर्णांकerface identअगरier
	 */
	व्योम (*set_ग_लिखो_gather_en)(काष्ठा dpu_hw_vbअगर *vbअगर, u32 xin_id);
पूर्ण;

काष्ठा dpu_hw_vbअगर अणु
	/* base */
	काष्ठा dpu_hw_blk_reg_map hw;

	/* vbअगर */
	क्रमागत dpu_vbअगर idx;
	स्थिर काष्ठा dpu_vbअगर_cfg *cap;

	/* ops */
	काष्ठा dpu_hw_vbअगर_ops ops;
पूर्ण;

/**
 * dpu_hw_vbअगर_init - initializes the vbअगर driver क्रम the passed पूर्णांकerface idx
 * @idx:  Interface index क्रम which driver object is required
 * @addr: Mapped रेजिस्टर io address of MDSS
 * @m:    Poपूर्णांकer to mdss catalog data
 */
काष्ठा dpu_hw_vbअगर *dpu_hw_vbअगर_init(क्रमागत dpu_vbअगर idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m);

व्योम dpu_hw_vbअगर_destroy(काष्ठा dpu_hw_vbअगर *vbअगर);

#पूर्ण_अगर /*_DPU_HW_VBIF_H */
