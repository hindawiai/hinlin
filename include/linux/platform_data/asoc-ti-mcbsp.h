<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Defines क्रम Multi-Channel Buffered Serial Port
 *
 * Copyright (C) 2002 RidgeRun, Inc.
 * Author: Steve Johnson
 */
#अगर_अघोषित __ASOC_TI_MCBSP_H
#घोषणा __ASOC_TI_MCBSP_H

#समावेश <linux/spinlock.h>
#समावेश <linux/clk.h>

/* Platक्रमm specअगरic configuration */
काष्ठा omap_mcbsp_ops अणु
	व्योम (*request)(अचिन्हित पूर्णांक);
	व्योम (*मुक्त)(अचिन्हित पूर्णांक);
पूर्ण;

काष्ठा omap_mcbsp_platक्रमm_data अणु
	काष्ठा omap_mcbsp_ops *ops;
	u16 buffer_size;
	u8 reg_size;
	u8 reg_step;

	/* McBSP platक्रमm and instance specअगरic features */
	bool has_wakeup; /* Wakeup capability */
	bool has_ccr; /* Transceiver has configuration control रेजिस्टरs */
	पूर्णांक (*क्रमce_ick_on)(काष्ठा clk *clk, bool क्रमce_on);
पूर्ण;

व्योम omap3_mcbsp_init_pdata_callback(काष्ठा omap_mcbsp_platक्रमm_data *pdata);

#पूर्ण_अगर
