<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2015 HiSilicon Technologies Co., Ltd.
 */

#अगर_अघोषित	__HISI_RESET_H
#घोषणा	__HISI_RESET_H

काष्ठा device_node;
काष्ठा hisi_reset_controller;

#अगर_घोषित CONFIG_RESET_CONTROLLER
काष्ठा hisi_reset_controller *hisi_reset_init(काष्ठा platक्रमm_device *pdev);
व्योम hisi_reset_निकास(काष्ठा hisi_reset_controller *rstc);
#अन्यथा
अटल अंतरभूत
काष्ठा hisi_reset_controller *hisi_reset_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम hisi_reset_निकास(काष्ठा hisi_reset_controller *rstc)
अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __HISI_RESET_H */
