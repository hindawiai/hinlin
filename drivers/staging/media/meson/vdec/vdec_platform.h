<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#अगर_अघोषित __MESON_VDEC_PLATFORM_H_
#घोषणा __MESON_VDEC_PLATFORM_H_

#समावेश "vdec.h"

काष्ठा amvdec_क्रमmat;

क्रमागत vdec_revision अणु
	VDEC_REVISION_GXBB,
	VDEC_REVISION_GXL,
	VDEC_REVISION_GXM,
	VDEC_REVISION_G12A,
	VDEC_REVISION_SM1,
पूर्ण;

काष्ठा vdec_platक्रमm अणु
	स्थिर काष्ठा amvdec_क्रमmat *क्रमmats;
	स्थिर u32 num_क्रमmats;
	क्रमागत vdec_revision revision;
पूर्ण;

बाह्य स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_gxbb;
बाह्य स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_gxm;
बाह्य स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_gxl;
बाह्य स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_g12a;
बाह्य स्थिर काष्ठा vdec_platक्रमm vdec_platक्रमm_sm1;

#पूर्ण_अगर
