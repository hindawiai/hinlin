<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * HiSilicon Clock and Reset Driver Header
 *
 * Copyright (c) 2016 HiSilicon Limited.
 */

#अगर_अघोषित __HISI_CRG_H
#घोषणा __HISI_CRG_H

काष्ठा hisi_घड़ी_data;
काष्ठा hisi_reset_controller;

काष्ठा hisi_crg_funcs अणु
	काष्ठा hisi_घड़ी_data*	(*रेजिस्टर_clks)(काष्ठा platक्रमm_device *pdev);
	व्योम (*unरेजिस्टर_clks)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

काष्ठा hisi_crg_dev अणु
	काष्ठा hisi_घड़ी_data *clk_data;
	काष्ठा hisi_reset_controller *rstc;
	स्थिर काष्ठा hisi_crg_funcs *funcs;
पूर्ण;

#पूर्ण_अगर	/* __HISI_CRG_H */
