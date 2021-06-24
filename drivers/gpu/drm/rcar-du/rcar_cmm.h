<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_cmm.h -- R-Car Display Unit Color Management Module
 *
 * Copyright (C) 2019 Jacopo Mondi <jacopo+renesas@jmondi.org>
 */

#अगर_अघोषित __RCAR_CMM_H__
#घोषणा __RCAR_CMM_H__

#घोषणा CM2_LUT_SIZE		256

काष्ठा drm_color_lut;
काष्ठा platक्रमm_device;

/**
 * काष्ठा rcar_cmm_config - CMM configuration
 *
 * @lut:	1D-LUT configuration
 * @lut.table:	1D-LUT table entries. Disable LUT operations when शून्य
 */
काष्ठा rcar_cmm_config अणु
	काष्ठा अणु
		काष्ठा drm_color_lut *table;
	पूर्ण lut;
पूर्ण;

#अगर IS_ENABLED(CONFIG_DRM_RCAR_CMM)
पूर्णांक rcar_cmm_init(काष्ठा platक्रमm_device *pdev);

पूर्णांक rcar_cmm_enable(काष्ठा platक्रमm_device *pdev);
व्योम rcar_cmm_disable(काष्ठा platक्रमm_device *pdev);

पूर्णांक rcar_cmm_setup(काष्ठा platक्रमm_device *pdev,
		   स्थिर काष्ठा rcar_cmm_config *config);
#अन्यथा
अटल अंतरभूत पूर्णांक rcar_cmm_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक rcar_cmm_enable(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rcar_cmm_disable(काष्ठा platक्रमm_device *pdev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक rcar_cmm_setup(काष्ठा platक्रमm_device *pdev,
				 स्थिर काष्ठा rcar_cmm_config *config)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_DRM_RCAR_CMM) */

#पूर्ण_अगर /* __RCAR_CMM_H__ */
