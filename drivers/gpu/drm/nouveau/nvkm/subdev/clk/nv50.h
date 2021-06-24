<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_CLK_H__
#घोषणा __NV50_CLK_H__
#घोषणा nv50_clk(p) container_of((p), काष्ठा nv50_clk, base)
#समावेश "priv.h"

#समावेश <subdev/bus/hwsq.h>

काष्ठा nv50_clk_hwsq अणु
	काष्ठा hwsq base;
	काष्ठा hwsq_reg r_fअगरo;
	काष्ठा hwsq_reg r_spll[2];
	काष्ठा hwsq_reg r_nvpll[2];
	काष्ठा hwsq_reg r_भागs;
	काष्ठा hwsq_reg r_mast;
पूर्ण;

काष्ठा nv50_clk अणु
	काष्ठा nvkm_clk base;
	काष्ठा nv50_clk_hwsq hwsq;
पूर्ण;

पूर्णांक nv50_clk_new_(स्थिर काष्ठा nvkm_clk_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  bool, काष्ठा nvkm_clk **);
पूर्णांक nv50_clk_पढ़ो(काष्ठा nvkm_clk *, क्रमागत nv_clk_src);
पूर्णांक nv50_clk_calc(काष्ठा nvkm_clk *, काष्ठा nvkm_cstate *);
पूर्णांक nv50_clk_prog(काष्ठा nvkm_clk *);
व्योम nv50_clk_tidy(काष्ठा nvkm_clk *);
#पूर्ण_अगर
