<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RPROC_QCOM_COMMON_H__
#घोषणा __RPROC_QCOM_COMMON_H__

#समावेश <linux/remoteproc.h>
#समावेश "remoteproc_internal.h"
#समावेश <linux/soc/qcom/qmi.h>

काष्ठा qcom_sysmon;

काष्ठा qcom_rproc_glink अणु
	काष्ठा rproc_subdev subdev;

	स्थिर अक्षर *ssr_name;

	काष्ठा device *dev;
	काष्ठा device_node *node;
	काष्ठा qcom_glink *edge;
पूर्ण;

काष्ठा qcom_rproc_subdev अणु
	काष्ठा rproc_subdev subdev;

	काष्ठा device *dev;
	काष्ठा device_node *node;
	काष्ठा qcom_smd_edge *edge;
पूर्ण;

काष्ठा qcom_ssr_subप्रणाली;

काष्ठा qcom_rproc_ssr अणु
	काष्ठा rproc_subdev subdev;
	काष्ठा qcom_ssr_subप्रणाली *info;
पूर्ण;

व्योम qcom_minidump(काष्ठा rproc *rproc, अचिन्हित पूर्णांक minidump_id);

व्योम qcom_add_glink_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_glink *glink,
			   स्थिर अक्षर *ssr_name);
व्योम qcom_हटाओ_glink_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_glink *glink);

पूर्णांक qcom_रेजिस्टर_dump_segments(काष्ठा rproc *rproc, स्थिर काष्ठा firmware *fw);

व्योम qcom_add_smd_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_subdev *smd);
व्योम qcom_हटाओ_smd_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_subdev *smd);

व्योम qcom_add_ssr_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_ssr *ssr,
			 स्थिर अक्षर *ssr_name);
व्योम qcom_हटाओ_ssr_subdev(काष्ठा rproc *rproc, काष्ठा qcom_rproc_ssr *ssr);

#अगर IS_ENABLED(CONFIG_QCOM_SYSMON)
काष्ठा qcom_sysmon *qcom_add_sysmon_subdev(काष्ठा rproc *rproc,
					   स्थिर अक्षर *name,
					   पूर्णांक ssctl_instance);
व्योम qcom_हटाओ_sysmon_subdev(काष्ठा qcom_sysmon *sysmon);
bool qcom_sysmon_shutकरोwn_acked(काष्ठा qcom_sysmon *sysmon);
#अन्यथा
अटल अंतरभूत काष्ठा qcom_sysmon *qcom_add_sysmon_subdev(काष्ठा rproc *rproc,
							 स्थिर अक्षर *name,
							 पूर्णांक ssctl_instance)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम qcom_हटाओ_sysmon_subdev(काष्ठा qcom_sysmon *sysmon)
अणु
पूर्ण

अटल अंतरभूत bool qcom_sysmon_shutकरोwn_acked(काष्ठा qcom_sysmon *sysmon)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
