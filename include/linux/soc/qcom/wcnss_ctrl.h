<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __WCNSS_CTRL_H__
#घोषणा __WCNSS_CTRL_H__

#समावेश <linux/rpmsg.h>

#अगर IS_ENABLED(CONFIG_QCOM_WCNSS_CTRL)

काष्ठा rpmsg_endpoपूर्णांक *qcom_wcnss_खोलो_channel(व्योम *wcnss, स्थिर अक्षर *name,
					       rpmsg_rx_cb_t cb, व्योम *priv);

#अन्यथा

अटल काष्ठा rpmsg_endpoपूर्णांक *qcom_wcnss_खोलो_channel(व्योम *wcnss,
						      स्थिर अक्षर *name,
						      rpmsg_rx_cb_t cb,
						      व्योम *priv)
अणु
	WARN_ON(1);
	वापस ERR_PTR(-ENXIO);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
