<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * DMTIMER platक्रमm data क्रम TI OMAP platक्रमms
 *
 * Copyright (C) 2012 Texas Instruments
 * Author: Jon Hunter <jon-hunter@ti.com>
 */

#अगर_अघोषित __PLATFORM_DATA_DMTIMER_OMAP_H__
#घोषणा __PLATFORM_DATA_DMTIMER_OMAP_H__

काष्ठा omap_dm_समयr_ops अणु
	काष्ठा omap_dm_समयr *(*request_by_node)(काष्ठा device_node *np);
	काष्ठा omap_dm_समयr *(*request_specअगरic)(पूर्णांक समयr_id);
	काष्ठा omap_dm_समयr *(*request)(व्योम);

	पूर्णांक	(*मुक्त)(काष्ठा omap_dm_समयr *समयr);

	व्योम	(*enable)(काष्ठा omap_dm_समयr *समयr);
	व्योम	(*disable)(काष्ठा omap_dm_समयr *समयr);

	पूर्णांक	(*get_irq)(काष्ठा omap_dm_समयr *समयr);
	पूर्णांक	(*set_पूर्णांक_enable)(काष्ठा omap_dm_समयr *समयr,
				  अचिन्हित पूर्णांक value);
	पूर्णांक	(*set_पूर्णांक_disable)(काष्ठा omap_dm_समयr *समयr, u32 mask);

	काष्ठा clk *(*get_fclk)(काष्ठा omap_dm_समयr *समयr);

	पूर्णांक	(*start)(काष्ठा omap_dm_समयr *समयr);
	पूर्णांक	(*stop)(काष्ठा omap_dm_समयr *समयr);
	पूर्णांक	(*set_source)(काष्ठा omap_dm_समयr *समयr, पूर्णांक source);

	पूर्णांक	(*set_load)(काष्ठा omap_dm_समयr *समयr, अचिन्हित पूर्णांक value);
	पूर्णांक	(*set_match)(काष्ठा omap_dm_समयr *समयr, पूर्णांक enable,
			     अचिन्हित पूर्णांक match);
	पूर्णांक	(*set_pwm)(काष्ठा omap_dm_समयr *समयr, पूर्णांक def_on,
			   पूर्णांक toggle, पूर्णांक trigger, पूर्णांक स्वतःreload);
	पूर्णांक	(*get_pwm_status)(काष्ठा omap_dm_समयr *समयr);
	पूर्णांक	(*set_prescaler)(काष्ठा omap_dm_समयr *समयr, पूर्णांक prescaler);

	अचिन्हित पूर्णांक (*पढ़ो_counter)(काष्ठा omap_dm_समयr *समयr);
	पूर्णांक	(*ग_लिखो_counter)(काष्ठा omap_dm_समयr *समयr,
				 अचिन्हित पूर्णांक value);
	अचिन्हित पूर्णांक (*पढ़ो_status)(काष्ठा omap_dm_समयr *समयr);
	पूर्णांक	(*ग_लिखो_status)(काष्ठा omap_dm_समयr *समयr,
				अचिन्हित पूर्णांक value);
पूर्ण;

काष्ठा dmसमयr_platक्रमm_data अणु
	/* set_समयr_src - Only used क्रम OMAP1 devices */
	पूर्णांक (*set_समयr_src)(काष्ठा platक्रमm_device *pdev, पूर्णांक source);
	u32 समयr_capability;
	u32 समयr_errata;
	पूर्णांक (*get_context_loss_count)(काष्ठा device *);
	स्थिर काष्ठा omap_dm_समयr_ops *समयr_ops;
पूर्ण;

#पूर्ण_अगर /* __PLATFORM_DATA_DMTIMER_OMAP_H__ */
