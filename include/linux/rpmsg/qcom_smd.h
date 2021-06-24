<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_RPMSG_QCOM_SMD_H
#घोषणा _LINUX_RPMSG_QCOM_SMD_H

#समावेश <linux/device.h>

काष्ठा qcom_smd_edge;

#अगर IS_ENABLED(CONFIG_RPMSG_QCOM_SMD)

काष्ठा qcom_smd_edge *qcom_smd_रेजिस्टर_edge(काष्ठा device *parent,
					     काष्ठा device_node *node);
पूर्णांक qcom_smd_unरेजिस्टर_edge(काष्ठा qcom_smd_edge *edge);

#अन्यथा

अटल अंतरभूत काष्ठा qcom_smd_edge *
qcom_smd_रेजिस्टर_edge(काष्ठा device *parent,
		       काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक qcom_smd_unरेजिस्टर_edge(काष्ठा qcom_smd_edge *edge)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
