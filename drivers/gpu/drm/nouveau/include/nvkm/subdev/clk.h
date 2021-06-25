<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_CLK_H__
#घोषणा __NVKM_CLK_H__
#समावेश <core/subdev.h>
#समावेश <core/notअगरy.h>
#समावेश <subdev/pci.h>
काष्ठा nvbios_pll;
काष्ठा nvkm_pll_vals;

#घोषणा NVKM_CLK_CSTATE_DEFAULT -1 /* POSTed शेष */
#घोषणा NVKM_CLK_CSTATE_BASE    -2 /* pstate base */
#घोषणा NVKM_CLK_CSTATE_HIGHEST -3 /* highest possible */

क्रमागत nv_clk_src अणु
	nv_clk_src_crystal,
	nv_clk_src_href,

	nv_clk_src_hclk,
	nv_clk_src_hclkm3,
	nv_clk_src_hclkm3d2,
	nv_clk_src_hclkm2d3, /* NVAA */
	nv_clk_src_hclkm4, /* NVAA */
	nv_clk_src_cclk, /* NVAA */

	nv_clk_src_host,

	nv_clk_src_sppll0,
	nv_clk_src_sppll1,

	nv_clk_src_mpllsrcref,
	nv_clk_src_mpllsrc,
	nv_clk_src_mpll,
	nv_clk_src_mभाग,

	nv_clk_src_core,
	nv_clk_src_core_पूर्णांकm,
	nv_clk_src_shader,

	nv_clk_src_mem,

	nv_clk_src_gpc,
	nv_clk_src_rop,
	nv_clk_src_hubk01,
	nv_clk_src_hubk06,
	nv_clk_src_hubk07,
	nv_clk_src_copy,
	nv_clk_src_pmu,
	nv_clk_src_disp,
	nv_clk_src_vdec,

	nv_clk_src_करोm6,

	nv_clk_src_max,
पूर्ण;

काष्ठा nvkm_cstate अणु
	काष्ठा list_head head;
	u8  voltage;
	u32 करोमुख्य[nv_clk_src_max];
	u8  id;
पूर्ण;

काष्ठा nvkm_pstate अणु
	काष्ठा list_head head;
	काष्ठा list_head list; /* c-states */
	काष्ठा nvkm_cstate base;
	u8 pstate;
	u8 fanspeed;
	क्रमागत nvkm_pcie_speed pcie_speed;
	u8 pcie_width;
पूर्ण;

काष्ठा nvkm_करोमुख्य अणु
	क्रमागत nv_clk_src name;
	u8 bios; /* 0xff क्रम none */
#घोषणा NVKM_CLK_DOM_FLAG_CORE    0x01
#घोषणा NVKM_CLK_DOM_FLAG_VPSTATE 0x02
	u8 flags;
	स्थिर अक्षर *mname;
	पूर्णांक mभाग;
पूर्ण;

काष्ठा nvkm_clk अणु
	स्थिर काष्ठा nvkm_clk_func *func;
	काष्ठा nvkm_subdev subdev;

	स्थिर काष्ठा nvkm_करोमुख्य *करोमुख्यs;
	काष्ठा nvkm_pstate bstate;

	काष्ठा list_head states;
	पूर्णांक state_nr;

	काष्ठा work_काष्ठा work;
	रुको_queue_head_t रुको;
	atomic_t रुकोing;

	काष्ठा nvkm_notअगरy pwrsrc_ntfy;
	पूर्णांक pwrsrc;
	पूर्णांक pstate; /* current */
	पूर्णांक ustate_ac; /* user-requested (-1 disabled, -2 perfmon) */
	पूर्णांक ustate_dc; /* user-requested (-1 disabled, -2 perfmon) */
	पूर्णांक astate; /* perfmon adjusपंचांगent (base) */
	पूर्णांक dstate; /* display adjusपंचांगent (min+) */
	u8  temp;

	bool allow_reघड़ी;
#घोषणा NVKM_CLK_BOOST_NONE 0x0
#घोषणा NVKM_CLK_BOOST_BIOS 0x1
#घोषणा NVKM_CLK_BOOST_FULL 0x2
	u8  boost_mode;
	u32 base_khz;
	u32 boost_khz;

	/*XXX: die, these are here *only* to support the completely
	 *     bat-shit insane what-was-nouveau_hw.c code
	 */
	पूर्णांक (*pll_calc)(काष्ठा nvkm_clk *, काष्ठा nvbios_pll *, पूर्णांक clk,
			काष्ठा nvkm_pll_vals *pv);
	पूर्णांक (*pll_prog)(काष्ठा nvkm_clk *, u32 reg1, काष्ठा nvkm_pll_vals *pv);
पूर्ण;

पूर्णांक nvkm_clk_पढ़ो(काष्ठा nvkm_clk *, क्रमागत nv_clk_src);
पूर्णांक nvkm_clk_ustate(काष्ठा nvkm_clk *, पूर्णांक req, पूर्णांक pwr);
पूर्णांक nvkm_clk_astate(काष्ठा nvkm_clk *, पूर्णांक req, पूर्णांक rel, bool रुको);
पूर्णांक nvkm_clk_dstate(काष्ठा nvkm_clk *, पूर्णांक req, पूर्णांक rel);
पूर्णांक nvkm_clk_tstate(काष्ठा nvkm_clk *, u8 temperature);

पूर्णांक nv04_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक nv40_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक nv50_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक g84_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक mcp77_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक gt215_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक gf100_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक gk104_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक gk20a_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
पूर्णांक gm20b_clk_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_clk **);
#पूर्ण_अगर
