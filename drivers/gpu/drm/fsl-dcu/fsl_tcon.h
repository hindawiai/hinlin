<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2015 Toradex AG
 *
 * Stefan Agner <stefan@agner.ch>
 *
 * Freescale TCON device driver
 */

#अगर_अघोषित __FSL_TCON_H__
#घोषणा __FSL_TCON_H__

#समावेश <linux/bitops.h>

#घोषणा FSL_TCON_CTRL1			0x0
#घोषणा FSL_TCON_CTRL1_TCON_BYPASS	BIT(29)

काष्ठा fsl_tcon अणु
	काष्ठा regmap		*regs;
	काष्ठा clk		*ipg_clk;
पूर्ण;

काष्ठा fsl_tcon *fsl_tcon_init(काष्ठा device *dev);
व्योम fsl_tcon_मुक्त(काष्ठा fsl_tcon *tcon);

व्योम fsl_tcon_bypass_disable(काष्ठा fsl_tcon *tcon);
व्योम fsl_tcon_bypass_enable(काष्ठा fsl_tcon *tcon);

#पूर्ण_अगर /* __FSL_TCON_H__ */
