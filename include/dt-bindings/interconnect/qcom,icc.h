<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DT_BINDINGS_INTERCONNECT_QCOM_ICC_H
#घोषणा __DT_BINDINGS_INTERCONNECT_QCOM_ICC_H

/*
 * The AMC bucket denotes स्थिरraपूर्णांकs that are applied to hardware when
 * icc_set_bw() completes, whereas the WAKE and SLEEP स्थिरraपूर्णांकs are applied
 * when the execution environment transitions between active and low घातer mode.
 */
#घोषणा QCOM_ICC_BUCKET_AMC		0
#घोषणा QCOM_ICC_BUCKET_WAKE		1
#घोषणा QCOM_ICC_BUCKET_SLEEP		2
#घोषणा QCOM_ICC_NUM_BUCKETS		3

#घोषणा QCOM_ICC_TAG_AMC		(1 << QCOM_ICC_BUCKET_AMC)
#घोषणा QCOM_ICC_TAG_WAKE		(1 << QCOM_ICC_BUCKET_WAKE)
#घोषणा QCOM_ICC_TAG_SLEEP		(1 << QCOM_ICC_BUCKET_SLEEP)
#घोषणा QCOM_ICC_TAG_ACTIVE_ONLY	(QCOM_ICC_TAG_AMC | QCOM_ICC_TAG_WAKE)
#घोषणा QCOM_ICC_TAG_ALWAYS		(QCOM_ICC_TAG_AMC | QCOM_ICC_TAG_WAKE |\
					 QCOM_ICC_TAG_SLEEP)

#पूर्ण_अगर
