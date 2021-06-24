<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016-2017, Linaro Ltd
 */

#अगर_अघोषित __QCOM_GLINK_NATIVE_H__
#घोषणा __QCOM_GLINK_NATIVE_H__

#घोषणा GLINK_FEATURE_INTENT_REUSE	BIT(0)
#घोषणा GLINK_FEATURE_MIGRATION		BIT(1)
#घोषणा GLINK_FEATURE_TRACER_PKT	BIT(2)

काष्ठा qcom_glink_pipe अणु
	माप_प्रकार length;

	माप_प्रकार (*avail)(काष्ठा qcom_glink_pipe *glink_pipe);

	व्योम (*peak)(काष्ठा qcom_glink_pipe *glink_pipe, व्योम *data,
		     अचिन्हित पूर्णांक offset, माप_प्रकार count);
	व्योम (*advance)(काष्ठा qcom_glink_pipe *glink_pipe, माप_प्रकार count);

	व्योम (*ग_लिखो)(काष्ठा qcom_glink_pipe *glink_pipe,
		      स्थिर व्योम *hdr, माप_प्रकार hlen,
		      स्थिर व्योम *data, माप_प्रकार dlen);
पूर्ण;

काष्ठा qcom_glink;

काष्ठा qcom_glink *qcom_glink_native_probe(काष्ठा device *dev,
					   अचिन्हित दीर्घ features,
					   काष्ठा qcom_glink_pipe *rx,
					   काष्ठा qcom_glink_pipe *tx,
					   bool पूर्णांकentless);
व्योम qcom_glink_native_हटाओ(काष्ठा qcom_glink *glink);

व्योम qcom_glink_native_unरेजिस्टर(काष्ठा qcom_glink *glink);
#पूर्ण_अगर
