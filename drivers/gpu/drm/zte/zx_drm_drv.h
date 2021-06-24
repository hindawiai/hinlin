<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#अगर_अघोषित __ZX_DRM_DRV_H__
#घोषणा __ZX_DRM_DRV_H__

बाह्य काष्ठा platक्रमm_driver zx_crtc_driver;
बाह्य काष्ठा platक्रमm_driver zx_hdmi_driver;
बाह्य काष्ठा platक्रमm_driver zx_tvenc_driver;
बाह्य काष्ठा platक्रमm_driver zx_vga_driver;

अटल अंतरभूत u32 zx_पढ़ोl(व्योम __iomem *reg)
अणु
	वापस पढ़ोl_relaxed(reg);
पूर्ण

अटल अंतरभूत व्योम zx_ग_लिखोl(व्योम __iomem *reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, reg);
पूर्ण

अटल अंतरभूत व्योम zx_ग_लिखोl_mask(व्योम __iomem *reg, u32 mask, u32 val)
अणु
	u32 पंचांगp;

	पंचांगp = zx_पढ़ोl(reg);
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	zx_ग_लिखोl(reg, पंचांगp);
पूर्ण

#पूर्ण_अगर /* __ZX_DRM_DRV_H__ */
