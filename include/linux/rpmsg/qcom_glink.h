<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_RPMSG_QCOM_GLINK_H
#घोषणा _LINUX_RPMSG_QCOM_GLINK_H

#समावेश <linux/device.h>

काष्ठा qcom_glink;

#अगर IS_ENABLED(CONFIG_RPMSG_QCOM_GLINK)
व्योम qcom_glink_ssr_notअगरy(स्थिर अक्षर *ssr_name);
#अन्यथा
अटल अंतरभूत व्योम qcom_glink_ssr_notअगरy(स्थिर अक्षर *ssr_name) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_RPMSG_QCOM_GLINK_SMEM)

काष्ठा qcom_glink *qcom_glink_smem_रेजिस्टर(काष्ठा device *parent,
					    काष्ठा device_node *node);
व्योम qcom_glink_smem_unरेजिस्टर(काष्ठा qcom_glink *glink);

#अन्यथा

अटल अंतरभूत काष्ठा qcom_glink *
qcom_glink_smem_रेजिस्टर(काष्ठा device *parent,
			 काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम qcom_glink_smem_unरेजिस्टर(काष्ठा qcom_glink *glink) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
