<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cedrus VPU driver
 *
 * Copyright (C) 2016 Florent Revest <florent.revest@मुक्त-electrons.com>
 * Copyright (C) 2018 Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 * Copyright (C) 2018 Bootlin
 *
 * Based on the vim2m driver, that is:
 *
 * Copyright (c) 2009-2010 Samsung Electronics Co., Ltd.
 * Pawel Osciak, <pawel@osciak.com>
 * Marek Szyprowski, <m.szyprowski@samsung.com>
 */

#अगर_अघोषित _CEDRUS_HW_H_
#घोषणा _CEDRUS_HW_H_

पूर्णांक cedrus_engine_enable(काष्ठा cedrus_ctx *ctx, क्रमागत cedrus_codec codec);
व्योम cedrus_engine_disable(काष्ठा cedrus_dev *dev);

व्योम cedrus_dst_क्रमmat_set(काष्ठा cedrus_dev *dev,
			   काष्ठा v4l2_pix_क्रमmat *fmt);

पूर्णांक cedrus_hw_suspend(काष्ठा device *device);
पूर्णांक cedrus_hw_resume(काष्ठा device *device);

पूर्णांक cedrus_hw_probe(काष्ठा cedrus_dev *dev);
व्योम cedrus_hw_हटाओ(काष्ठा cedrus_dev *dev);

#पूर्ण_अगर
