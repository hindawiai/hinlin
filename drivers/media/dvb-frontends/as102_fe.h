<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2014 Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
 */

#समावेश "as102_fe_types.h"

काष्ठा as102_fe_ops अणु
	पूर्णांक (*set_tune)(व्योम *priv, काष्ठा as10x_tune_args *tune_args);
	पूर्णांक (*get_tps)(व्योम *priv, काष्ठा as10x_tps *tps);
	पूर्णांक (*get_status)(व्योम *priv, काष्ठा as10x_tune_status *tstate);
	पूर्णांक (*get_stats)(व्योम *priv, काष्ठा as10x_demod_stats *demod_stats);
	पूर्णांक (*stream_ctrl)(व्योम *priv, पूर्णांक acquire, uपूर्णांक32_t elna_cfg);
पूर्ण;

काष्ठा dvb_frontend *as102_attach(स्थिर अक्षर *name,
				  स्थिर काष्ठा as102_fe_ops *ops,
				  व्योम *priv,
				  uपूर्णांक8_t elna_cfg);
