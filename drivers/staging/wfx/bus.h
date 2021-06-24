<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Common bus असलtraction layer.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#अगर_अघोषित WFX_BUS_H
#घोषणा WFX_BUS_H

#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/spi/spi.h>

#घोषणा WFX_REG_CONFIG        0x0
#घोषणा WFX_REG_CONTROL       0x1
#घोषणा WFX_REG_IN_OUT_QUEUE  0x2
#घोषणा WFX_REG_AHB_DPORT     0x3
#घोषणा WFX_REG_BASE_ADDR     0x4
#घोषणा WFX_REG_SRAM_DPORT    0x5
#घोषणा WFX_REG_SET_GEN_R_W   0x6
#घोषणा WFX_REG_FRAME_OUT     0x7

काष्ठा hwbus_ops अणु
	पूर्णांक (*copy_from_io)(व्योम *bus_priv, अचिन्हित पूर्णांक addr,
			    व्योम *dst, माप_प्रकार count);
	पूर्णांक (*copy_to_io)(व्योम *bus_priv, अचिन्हित पूर्णांक addr,
			  स्थिर व्योम *src, माप_प्रकार count);
	पूर्णांक (*irq_subscribe)(व्योम *bus_priv);
	पूर्णांक (*irq_unsubscribe)(व्योम *bus_priv);
	व्योम (*lock)(व्योम *bus_priv);
	व्योम (*unlock)(व्योम *bus_priv);
	माप_प्रकार (*align_size)(व्योम *bus_priv, माप_प्रकार size);
पूर्ण;

बाह्य काष्ठा sdio_driver wfx_sdio_driver;
बाह्य काष्ठा spi_driver wfx_spi_driver;

#पूर्ण_अगर
