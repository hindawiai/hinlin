<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PLL_H__
#घोषणा __NVKM_PLL_H__
#समावेश <core/os.h>
काष्ठा nvkm_subdev;
काष्ठा nvbios_pll;

पूर्णांक nv04_pll_calc(काष्ठा nvkm_subdev *, काष्ठा nvbios_pll *, u32 freq,
		  पूर्णांक *N1, पूर्णांक *M1, पूर्णांक *N2, पूर्णांक *M2, पूर्णांक *P);
पूर्णांक gt215_pll_calc(काष्ठा nvkm_subdev *, काष्ठा nvbios_pll *, u32 freq,
		  पूर्णांक *N, पूर्णांक *fN, पूर्णांक *M, पूर्णांक *P);
#पूर्ण_अगर
