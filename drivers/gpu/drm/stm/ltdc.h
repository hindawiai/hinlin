<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2017
 *
 * Authors: Philippe Cornu <philippe.cornu@st.com>
 *          Yannick Fertre <yannick.fertre@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          Mickael Reulier <mickael.reulier@st.com>
 */

#अगर_अघोषित _LTDC_H_
#घोषणा _LTDC_H_

काष्ठा ltdc_caps अणु
	u32 hw_version;		/* hardware version */
	u32 nb_layers;		/* number of supported layers */
	u32 reg_ofs;		/* रेजिस्टर offset क्रम applicable regs */
	u32 bus_width;		/* bus width (32 or 64 bits) */
	स्थिर u32 *pix_fmt_hw;	/* supported pixel क्रमmats */
	bool non_alpha_only_l1; /* non-native no-alpha क्रमmats on layer 1 */
	पूर्णांक pad_max_freq_hz;	/* max frequency supported by pad */
	पूर्णांक nb_irq;		/* number of hardware पूर्णांकerrupts */
पूर्ण;

#घोषणा LTDC_MAX_LAYER	4

काष्ठा fps_info अणु
	अचिन्हित पूर्णांक counter;
	kसमय_प्रकार last_बारtamp;
पूर्ण;

काष्ठा ltdc_device अणु
	व्योम __iomem *regs;
	काष्ठा clk *pixel_clk;	/* lcd pixel घड़ी */
	काष्ठा mutex err_lock;	/* protecting error_status */
	काष्ठा ltdc_caps caps;
	u32 error_status;
	u32 irq_status;
	काष्ठा fps_info plane_fpsi[LTDC_MAX_LAYER];
	काष्ठा drm_atomic_state *suspend_state;
पूर्ण;

पूर्णांक ltdc_load(काष्ठा drm_device *ddev);
व्योम ltdc_unload(काष्ठा drm_device *ddev);
व्योम ltdc_suspend(काष्ठा drm_device *ddev);
पूर्णांक ltdc_resume(काष्ठा drm_device *ddev);

#पूर्ण_अगर
