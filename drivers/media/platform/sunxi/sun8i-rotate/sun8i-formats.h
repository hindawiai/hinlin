<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2020 Jernej Skrabec <jernej.skrabec@siol.net> */

#अगर_अघोषित _SUN8I_FORMATS_H_
#घोषणा _SUN8I_FORMATS_H_

#समावेश <linux/videodev2.h>

#घोषणा ROTATE_FLAG_YUV    BIT(0)
#घोषणा ROTATE_FLAG_OUTPUT BIT(1)

काष्ठा rotate_क्रमmat अणु
	u32 fourcc;
	u32 hw_क्रमmat;
	पूर्णांक planes;
	पूर्णांक bpp[3];
	पूर्णांक hsub;
	पूर्णांक vsub;
	अचिन्हित पूर्णांक flags;
पूर्ण;

स्थिर काष्ठा rotate_क्रमmat *rotate_find_क्रमmat(u32 pixelक्रमmat);
पूर्णांक rotate_क्रमागत_fmt(काष्ठा v4l2_fmtdesc *f, bool dst);

#पूर्ण_अगर
