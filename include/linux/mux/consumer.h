<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mux/consumer.h - definitions क्रम the multiplexer consumer पूर्णांकerface
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#अगर_अघोषित _LINUX_MUX_CONSUMER_H
#घोषणा _LINUX_MUX_CONSUMER_H

#समावेश <linux/compiler.h>

काष्ठा device;
काष्ठा mux_control;

अचिन्हित पूर्णांक mux_control_states(काष्ठा mux_control *mux);
पूर्णांक __must_check mux_control_select(काष्ठा mux_control *mux,
				    अचिन्हित पूर्णांक state);
पूर्णांक __must_check mux_control_try_select(काष्ठा mux_control *mux,
					अचिन्हित पूर्णांक state);
पूर्णांक mux_control_deselect(काष्ठा mux_control *mux);

काष्ठा mux_control *mux_control_get(काष्ठा device *dev, स्थिर अक्षर *mux_name);
व्योम mux_control_put(काष्ठा mux_control *mux);

काष्ठा mux_control *devm_mux_control_get(काष्ठा device *dev,
					 स्थिर अक्षर *mux_name);

#पूर्ण_अगर /* _LINUX_MUX_CONSUMER_H */
