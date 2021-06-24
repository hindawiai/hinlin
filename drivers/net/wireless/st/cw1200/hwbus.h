<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Common hwbus असलtraction layer पूर्णांकerface क्रम cw1200 wireless driver
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 */

#अगर_अघोषित CW1200_HWBUS_H
#घोषणा CW1200_HWBUS_H

काष्ठा hwbus_priv;

व्योम cw1200_irq_handler(काष्ठा cw1200_common *priv);

/* This MUST be wrapped with hwbus_ops->lock/unlock! */
पूर्णांक __cw1200_irq_enable(काष्ठा cw1200_common *priv, पूर्णांक enable);

काष्ठा hwbus_ops अणु
	पूर्णांक (*hwbus_स_नकल_fromio)(काष्ठा hwbus_priv *self, अचिन्हित पूर्णांक addr,
					व्योम *dst, पूर्णांक count);
	पूर्णांक (*hwbus_स_नकल_toio)(काष्ठा hwbus_priv *self, अचिन्हित पूर्णांक addr,
					स्थिर व्योम *src, पूर्णांक count);
	व्योम (*lock)(काष्ठा hwbus_priv *self);
	व्योम (*unlock)(काष्ठा hwbus_priv *self);
	माप_प्रकार (*align_size)(काष्ठा hwbus_priv *self, माप_प्रकार size);
	पूर्णांक (*घातer_mgmt)(काष्ठा hwbus_priv *self, bool suspend);
पूर्ण;

#पूर्ण_अगर /* CW1200_HWBUS_H */
