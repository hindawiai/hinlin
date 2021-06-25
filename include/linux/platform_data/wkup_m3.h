<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI Wakeup M3 remote processor platक्रमm data
 *
 * Copyright (C) 2014-2015 Texas Instruments, Inc.
 *
 * Dave Gerlach <d-gerlach@ti.com>
 */

#अगर_अघोषित _LINUX_PLATFORM_DATA_WKUP_M3_H
#घोषणा _LINUX_PLATFORM_DATA_WKUP_M3_H

काष्ठा platक्रमm_device;

काष्ठा wkup_m3_platक्रमm_data अणु
	स्थिर अक्षर *reset_name;

	पूर्णांक (*निश्चित_reset)(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name);
	पूर्णांक (*deनिश्चित_reset)(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name);
पूर्ण;

#पूर्ण_अगर /* _LINUX_PLATFORM_DATA_WKUP_M3_H */
