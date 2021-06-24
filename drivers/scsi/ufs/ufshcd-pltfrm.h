<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित UFSHCD_PLTFRM_H_
#घोषणा UFSHCD_PLTFRM_H_

#समावेश "ufshcd.h"

#घोषणा UFS_PWM_MODE 1
#घोषणा UFS_HS_MODE  2

काष्ठा ufs_dev_params अणु
	u32 pwm_rx_gear;        /* pwm rx gear to work in */
	u32 pwm_tx_gear;        /* pwm tx gear to work in */
	u32 hs_rx_gear;         /* hs rx gear to work in */
	u32 hs_tx_gear;         /* hs tx gear to work in */
	u32 rx_lanes;           /* number of rx lanes */
	u32 tx_lanes;           /* number of tx lanes */
	u32 rx_pwr_pwm;         /* rx pwm working pwr */
	u32 tx_pwr_pwm;         /* tx pwm working pwr */
	u32 rx_pwr_hs;          /* rx hs working pwr */
	u32 tx_pwr_hs;          /* tx hs working pwr */
	u32 hs_rate;            /* rate A/B to work in HS */
	u32 desired_working_mode;
पूर्ण;

पूर्णांक ufshcd_get_pwr_dev_param(काष्ठा ufs_dev_params *dev_param,
			     काष्ठा ufs_pa_layer_attr *dev_max,
			     काष्ठा ufs_pa_layer_attr *agreed_pwr);
व्योम ufshcd_init_pwr_dev_param(काष्ठा ufs_dev_params *dev_param);
पूर्णांक ufshcd_pltfrm_init(काष्ठा platक्रमm_device *pdev,
		       स्थिर काष्ठा ufs_hba_variant_ops *vops);
व्योम ufshcd_pltfrm_shutकरोwn(काष्ठा platक्रमm_device *pdev);

#अगर_घोषित CONFIG_PM

पूर्णांक ufshcd_pltfrm_suspend(काष्ठा device *dev);
पूर्णांक ufshcd_pltfrm_resume(काष्ठा device *dev);
पूर्णांक ufshcd_pltfrm_runसमय_suspend(काष्ठा device *dev);
पूर्णांक ufshcd_pltfrm_runसमय_resume(काष्ठा device *dev);
पूर्णांक ufshcd_pltfrm_runसमय_idle(काष्ठा device *dev);

#अन्यथा /* !CONFIG_PM */

#घोषणा ufshcd_pltfrm_suspend	शून्य
#घोषणा ufshcd_pltfrm_resume	शून्य
#घोषणा ufshcd_pltfrm_runसमय_suspend	शून्य
#घोषणा ufshcd_pltfrm_runसमय_resume	शून्य
#घोषणा ufshcd_pltfrm_runसमय_idle	शून्य

#पूर्ण_अगर /* CONFIG_PM */

#पूर्ण_अगर /* UFSHCD_PLTFRM_H_ */
