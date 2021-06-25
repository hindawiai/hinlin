<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ITE Tech IT9137 silicon tuner driver
 *
 *  Copyright (C) 2011 Malcolm Priestley (tvboxspy@gmail.com)
 *  IT9137 Copyright (C) ITE Tech Inc.
 */

#अगर_अघोषित IT913X_H
#घोषणा IT913X_H

#समावेश <media/dvb_frontend.h>

/**
 * काष्ठा it913x_platक्रमm_data - Platक्रमm data क्रम the it913x driver
 * @regmap: af9033 demod driver regmap.
 * @fe: af9033 demod driver DVB frontend.
 * @role: Chip role, single or dual configuration.
 */

काष्ठा it913x_platक्रमm_data अणु
	काष्ठा regmap *regmap;
	काष्ठा dvb_frontend *fe;
#घोषणा IT913X_ROLE_SINGLE         0
#घोषणा IT913X_ROLE_DUAL_MASTER    1
#घोषणा IT913X_ROLE_DUAL_SLAVE     2
	अचिन्हित पूर्णांक role:2;
पूर्ण;

#पूर्ण_अगर
