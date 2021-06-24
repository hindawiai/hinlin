<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015 Endless Mobile, Inc.
 * Author: Carlo Caione <carlo@endlessm.com>
 */

#अगर_अघोषित __MESON_PARM_H
#घोषणा __MESON_PARM_H

#समावेश <linux/bits.h>
#समावेश <linux/regmap.h>

#घोषणा PMASK(width)			GENMASK(width - 1, 0)
#घोषणा SETPMASK(width, shअगरt)		GENMASK(shअगरt + width - 1, shअगरt)
#घोषणा CLRPMASK(width, shअगरt)		(~SETPMASK(width, shअगरt))

#घोषणा PARM_GET(width, shअगरt, reg)					\
	(((reg) & SETPMASK(width, shअगरt)) >> (shअगरt))
#घोषणा PARM_SET(width, shअगरt, reg, val)				\
	(((reg) & CLRPMASK(width, shअगरt)) | ((val) << (shअगरt)))

#घोषणा MESON_PARM_APPLICABLE(p)		(!!((p)->width))

काष्ठा parm अणु
	u16	reg_off;
	u8	shअगरt;
	u8	width;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक meson_parm_पढ़ो(काष्ठा regmap *map, काष्ठा parm *p)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(map, p->reg_off, &val);
	वापस PARM_GET(p->width, p->shअगरt, val);
पूर्ण

अटल अंतरभूत व्योम meson_parm_ग_लिखो(काष्ठा regmap *map, काष्ठा parm *p,
				    अचिन्हित पूर्णांक val)
अणु
	regmap_update_bits(map, p->reg_off, SETPMASK(p->width, p->shअगरt),
			   val << p->shअगरt);
पूर्ण

#पूर्ण_अगर /* __MESON_PARM_H */

