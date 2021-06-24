<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2015 Linaro Ltd.
 */

#अगर_अघोषित __SOC_IMX_TIMER_H__
#घोषणा __SOC_IMX_TIMER_H__

क्रमागत imx_gpt_type अणु
	GPT_TYPE_IMX1,		/* i.MX1 */
	GPT_TYPE_IMX21,		/* i.MX21/27 */
	GPT_TYPE_IMX31,		/* i.MX31/35/25/37/51/6Q */
	GPT_TYPE_IMX6DL,	/* i.MX6DL/SX/SL */
पूर्ण;

/*
 * This is a stop-gap solution क्रम घड़ी drivers like imx1/imx21 which call
 * mxc_समयr_init() to initialize समयr क्रम non-DT boot.  It can be हटाओd
 * when these legacy non-DT support is converted or dropped.
 */
व्योम mxc_समयr_init(अचिन्हित दीर्घ pbase, पूर्णांक irq, क्रमागत imx_gpt_type type);

#पूर्ण_अगर  /* __SOC_IMX_TIMER_H__ */
