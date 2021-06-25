<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_CLK_PRIV_H__
#घोषणा __NVKM_CLK_PRIV_H__
#घोषणा nvkm_clk(p) container_of((p), काष्ठा nvkm_clk, subdev)
#समावेश <subdev/clk.h>

काष्ठा nvkm_clk_func अणु
	पूर्णांक (*init)(काष्ठा nvkm_clk *);
	व्योम (*fini)(काष्ठा nvkm_clk *);
	पूर्णांक (*पढ़ो)(काष्ठा nvkm_clk *, क्रमागत nv_clk_src);
	पूर्णांक (*calc)(काष्ठा nvkm_clk *, काष्ठा nvkm_cstate *);
	पूर्णांक (*prog)(काष्ठा nvkm_clk *);
	व्योम (*tidy)(काष्ठा nvkm_clk *);
	काष्ठा nvkm_pstate *pstates;
	पूर्णांक nr_pstates;
	काष्ठा nvkm_करोमुख्य करोमुख्यs[];
पूर्ण;

पूर्णांक nvkm_clk_ctor(स्थिर काष्ठा nvkm_clk_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  bool allow_reघड़ी, काष्ठा nvkm_clk *);
पूर्णांक nvkm_clk_new_(स्थिर काष्ठा nvkm_clk_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  bool allow_reघड़ी, काष्ठा nvkm_clk **);

पूर्णांक nv04_clk_pll_calc(काष्ठा nvkm_clk *, काष्ठा nvbios_pll *, पूर्णांक clk,
		      काष्ठा nvkm_pll_vals *);
पूर्णांक nv04_clk_pll_prog(काष्ठा nvkm_clk *, u32 reg1, काष्ठा nvkm_pll_vals *);
#पूर्ण_अगर
