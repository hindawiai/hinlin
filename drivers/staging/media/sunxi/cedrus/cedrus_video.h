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

#अगर_अघोषित _CEDRUS_VIDEO_H_
#घोषणा _CEDRUS_VIDEO_H_

काष्ठा cedrus_क्रमmat अणु
	u32		pixelक्रमmat;
	u32		directions;
	अचिन्हित पूर्णांक	capabilities;
पूर्ण;

बाह्य स्थिर काष्ठा v4l2_ioctl_ops cedrus_ioctl_ops;

पूर्णांक cedrus_queue_init(व्योम *priv, काष्ठा vb2_queue *src_vq,
		      काष्ठा vb2_queue *dst_vq);
व्योम cedrus_prepare_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix_fmt);

#पूर्ण_अगर
