<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Arche Platक्रमm driver to enable Unipro link.
 *
 * Copyright 2015-2016 Google Inc.
 * Copyright 2015-2016 Linaro Ltd.
 */

#अगर_अघोषित __ARCHE_PLATFORM_H
#घोषणा __ARCHE_PLATFORM_H

क्रमागत arche_platक्रमm_state अणु
	ARCHE_PLATFORM_STATE_OFF,
	ARCHE_PLATFORM_STATE_ACTIVE,
	ARCHE_PLATFORM_STATE_STANDBY,
	ARCHE_PLATFORM_STATE_FW_FLASHING,
पूर्ण;

पूर्णांक __init arche_apb_init(व्योम);
व्योम __निकास arche_apb_निकास(व्योम);

/* Operational states क्रम the APB device */
पूर्णांक apb_ctrl_coldboot(काष्ठा device *dev);
पूर्णांक apb_ctrl_fw_flashing(काष्ठा device *dev);
पूर्णांक apb_ctrl_standby_boot(काष्ठा device *dev);
व्योम apb_ctrl_घातeroff(काष्ठा device *dev);

#पूर्ण_अगर	/* __ARCHE_PLATFORM_H */
