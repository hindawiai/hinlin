<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 Google LLC.
 */

#अगर_अघोषित __LINUX_RPMSG_MTK_RPMSG_H
#घोषणा __LINUX_RPMSG_MTK_RPMSG_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>

प्रकार व्योम (*ipi_handler_t)(व्योम *data, अचिन्हित पूर्णांक len, व्योम *priv);

/*
 * काष्ठा mtk_rpmsg_info - IPI functions tied to the rpmsg device.
 * @रेजिस्टर_ipi: रेजिस्टर IPI handler क्रम an IPI id.
 * @unरेजिस्टर_ipi: unरेजिस्टर IPI handler क्रम a रेजिस्टरed IPI id.
 * @send_ipi: send IPI to an IPI id. रुको is the समयout (in msecs) to रुको
 *            until response, or 0 अगर there's no समयout.
 * @ns_ipi_id: the IPI id used क्रम name service, or -1 अगर name service isn't
 *             supported.
 */
काष्ठा mtk_rpmsg_info अणु
	पूर्णांक (*रेजिस्टर_ipi)(काष्ठा platक्रमm_device *pdev, u32 id,
			    ipi_handler_t handler, व्योम *priv);
	व्योम (*unरेजिस्टर_ipi)(काष्ठा platक्रमm_device *pdev, u32 id);
	पूर्णांक (*send_ipi)(काष्ठा platक्रमm_device *pdev, u32 id,
			व्योम *buf, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक रुको);
	पूर्णांक ns_ipi_id;
पूर्ण;

काष्ठा rproc_subdev *
mtk_rpmsg_create_rproc_subdev(काष्ठा platक्रमm_device *pdev,
			      काष्ठा mtk_rpmsg_info *info);

व्योम mtk_rpmsg_destroy_rproc_subdev(काष्ठा rproc_subdev *subdev);

#पूर्ण_अगर
