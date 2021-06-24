<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * i2c-mux.h - functions क्रम the i2c-bus mux support
 *
 * Copyright (c) 2008-2009 Roकरोlfo Giometti <giometti@linux.it>
 * Copyright (c) 2008-2009 Eurotech S.p.A. <info@eurotech.it>
 * Michael Lawnick <michael.lawnick.ext@nsn.com>
 */

#अगर_अघोषित _LINUX_I2C_MUX_H
#घोषणा _LINUX_I2C_MUX_H

#अगर_घोषित __KERNEL__

#समावेश <linux/bitops.h>

काष्ठा i2c_mux_core अणु
	काष्ठा i2c_adapter *parent;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक mux_locked:1;
	अचिन्हित पूर्णांक arbitrator:1;
	अचिन्हित पूर्णांक gate:1;

	व्योम *priv;

	पूर्णांक (*select)(काष्ठा i2c_mux_core *, u32 chan_id);
	पूर्णांक (*deselect)(काष्ठा i2c_mux_core *, u32 chan_id);

	पूर्णांक num_adapters;
	पूर्णांक max_adapters;
	काष्ठा i2c_adapter *adapter[];
पूर्ण;

काष्ठा i2c_mux_core *i2c_mux_alloc(काष्ठा i2c_adapter *parent,
				   काष्ठा device *dev, पूर्णांक max_adapters,
				   पूर्णांक माप_priv, u32 flags,
				   पूर्णांक (*select)(काष्ठा i2c_mux_core *, u32),
				   पूर्णांक (*deselect)(काष्ठा i2c_mux_core *, u32));

/* flags क्रम i2c_mux_alloc */
#घोषणा I2C_MUX_LOCKED     BIT(0)
#घोषणा I2C_MUX_ARBITRATOR BIT(1)
#घोषणा I2C_MUX_GATE       BIT(2)

अटल अंतरभूत व्योम *i2c_mux_priv(काष्ठा i2c_mux_core *muxc)
अणु
	वापस muxc->priv;
पूर्ण

काष्ठा i2c_adapter *i2c_root_adapter(काष्ठा device *dev);

/*
 * Called to create an i2c bus on a multiplexed bus segment.
 * The chan_id parameter is passed to the select and deselect
 * callback functions to perक्रमm hardware-specअगरic mux control.
 */
पूर्णांक i2c_mux_add_adapter(काष्ठा i2c_mux_core *muxc,
			u32 क्रमce_nr, u32 chan_id,
			अचिन्हित पूर्णांक class);

व्योम i2c_mux_del_adapters(काष्ठा i2c_mux_core *muxc);

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _LINUX_I2C_MUX_H */
