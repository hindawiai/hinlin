<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __SOC_QCOM_RPMH_H__
#घोषणा __SOC_QCOM_RPMH_H__

#समावेश <soc/qcom/tcs.h>
#समावेश <linux/platक्रमm_device.h>


#अगर IS_ENABLED(CONFIG_QCOM_RPMH)
पूर्णांक rpmh_ग_लिखो(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
	       स्थिर काष्ठा tcs_cmd *cmd, u32 n);

पूर्णांक rpmh_ग_लिखो_async(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
		     स्थिर काष्ठा tcs_cmd *cmd, u32 n);

पूर्णांक rpmh_ग_लिखो_batch(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
		     स्थिर काष्ठा tcs_cmd *cmd, u32 *n);

व्योम rpmh_invalidate(स्थिर काष्ठा device *dev);

#अन्यथा

अटल अंतरभूत पूर्णांक rpmh_ग_लिखो(स्थिर काष्ठा device *dev, क्रमागत rpmh_state state,
			     स्थिर काष्ठा tcs_cmd *cmd, u32 n)
अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक rpmh_ग_लिखो_async(स्थिर काष्ठा device *dev,
				   क्रमागत rpmh_state state,
				   स्थिर काष्ठा tcs_cmd *cmd, u32 n)
अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक rpmh_ग_लिखो_batch(स्थिर काष्ठा device *dev,
				   क्रमागत rpmh_state state,
				   स्थिर काष्ठा tcs_cmd *cmd, u32 *n)
अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत व्योम rpmh_invalidate(स्थिर काष्ठा device *dev)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_QCOM_RPMH */

#पूर्ण_अगर /* __SOC_QCOM_RPMH_H__ */
