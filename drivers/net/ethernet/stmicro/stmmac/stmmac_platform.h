<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#अगर_अघोषित __STMMAC_PLATFORM_H__
#घोषणा __STMMAC_PLATFORM_H__

#समावेश "stmmac.h"

काष्ठा plat_sपंचांगmacenet_data *
sपंचांगmac_probe_config_dt(काष्ठा platक्रमm_device *pdev, u8 *mac);
व्योम sपंचांगmac_हटाओ_config_dt(काष्ठा platक्रमm_device *pdev,
			     काष्ठा plat_sपंचांगmacenet_data *plat);

पूर्णांक sपंचांगmac_get_platक्रमm_resources(काष्ठा platक्रमm_device *pdev,
				  काष्ठा sपंचांगmac_resources *sपंचांगmac_res);

पूर्णांक sपंचांगmac_pltfr_हटाओ(काष्ठा platक्रमm_device *pdev);
बाह्य स्थिर काष्ठा dev_pm_ops sपंचांगmac_pltfr_pm_ops;

अटल अंतरभूत व्योम *get_sपंचांगmac_bsp_priv(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(ndev);

	वापस priv->plat->bsp_priv;
पूर्ण

#पूर्ण_अगर /* __STMMAC_PLATFORM_H__ */
