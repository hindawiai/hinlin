<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __QCOM_WNCSS_H__
#घोषणा __QCOM_WNCSS_H__

काष्ठा qcom_iris;
काष्ठा qcom_wcnss;

बाह्य काष्ठा platक्रमm_driver qcom_iris_driver;

काष्ठा wcnss_vreg_info अणु
	स्थिर अक्षर * स्थिर name;
	पूर्णांक min_voltage;
	पूर्णांक max_voltage;

	पूर्णांक load_uA;

	bool super_turbo;
पूर्ण;

पूर्णांक qcom_iris_enable(काष्ठा qcom_iris *iris);
व्योम qcom_iris_disable(काष्ठा qcom_iris *iris);

व्योम qcom_wcnss_assign_iris(काष्ठा qcom_wcnss *wcnss, काष्ठा qcom_iris *iris, bool use_48mhz_xo);

#पूर्ण_अगर
