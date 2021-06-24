<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Russell King
 */
#अगर_अघोषित ARMADA_CRTC_H
#घोषणा ARMADA_CRTC_H

#समावेश <drm/drm_crtc.h>

काष्ठा armada_gem_object;

काष्ठा armada_regs अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t val;
पूर्ण;

#घोषणा armada_reg_queue_mod(_r, _i, _v, _m, _o)	\
	करो अणु					\
		काष्ठा armada_regs *__reg = _r;	\
		__reg[_i].offset = _o;		\
		__reg[_i].mask = ~(_m);		\
		__reg[_i].val = _v;		\
		_i++;				\
	पूर्ण जबतक (0)

#घोषणा armada_reg_queue_set(_r, _i, _v, _o)	\
	armada_reg_queue_mod(_r, _i, _v, ~0, _o)

#घोषणा armada_reg_queue_end(_r, _i)		\
	armada_reg_queue_mod(_r, _i, 0, 0, ~0)

काष्ठा armada_crtc;
काष्ठा armada_variant;

काष्ठा armada_crtc अणु
	काष्ठा drm_crtc		crtc;
	स्थिर काष्ठा armada_variant *variant;
	व्योम			*variant_data;
	अचिन्हित		num;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा अणु
		uपूर्णांक32_t	spu_v_h_total;
		uपूर्णांक32_t	spu_v_porch;
		uपूर्णांक32_t	spu_adv_reg;
	पूर्ण v[2];
	bool			पूर्णांकerlaced;
	bool			cursor_update;

	काष्ठा armada_gem_object	*cursor_obj;
	पूर्णांक			cursor_x;
	पूर्णांक			cursor_y;
	uपूर्णांक32_t		cursor_hw_pos;
	uपूर्णांक32_t		cursor_hw_sz;
	uपूर्णांक32_t		cursor_w;
	uपूर्णांक32_t		cursor_h;

	uपूर्णांक32_t		cfg_dumb_ctrl;
	uपूर्णांक32_t		spu_iopad_ctrl;

	spinlock_t		irq_lock;
	uपूर्णांक32_t		irq_ena;

	bool			update_pending;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा armada_regs	atomic_regs[32];
	काष्ठा armada_regs	*regs;
	अचिन्हित पूर्णांक		regs_idx;
पूर्ण;
#घोषणा drm_to_armada_crtc(c) container_of(c, काष्ठा armada_crtc, crtc)

व्योम armada_drm_crtc_update_regs(काष्ठा armada_crtc *, काष्ठा armada_regs *);

काष्ठा armada_घड़ीing_params अणु
	अचिन्हित दीर्घ permillage_min;
	अचिन्हित दीर्घ permillage_max;
	u32 settable;
	u32 भाग_max;
पूर्ण;

काष्ठा armada_clk_result अणु
	अचिन्हित दीर्घ desired_clk_hz;
	काष्ठा clk *clk;
	u32 भाग;
पूर्ण;

पूर्णांक armada_crtc_select_घड़ी(काष्ठा armada_crtc *dcrtc,
			     काष्ठा armada_clk_result *res,
			     स्थिर काष्ठा armada_घड़ीing_params *params,
			     काष्ठा clk *clks[], माप_प्रकार num_clks,
			     अचिन्हित दीर्घ desired_khz);

बाह्य काष्ठा platक्रमm_driver armada_lcd_platक्रमm_driver;

#पूर्ण_अगर
