<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित _LINUX_WL12XX_H
#घोषणा _LINUX_WL12XX_H

#समावेश <linux/err.h>

काष्ठा wl1251_platक्रमm_data अणु
	पूर्णांक घातer_gpio;
	/* SDIO only: IRQ number अगर WLAN_IRQ line is used, 0 क्रम SDIO IRQs */
	पूर्णांक irq;
	bool use_eeprom;
पूर्ण;

#अगर_घोषित CONFIG_WILINK_PLATFORM_DATA

पूर्णांक wl1251_set_platक्रमm_data(स्थिर काष्ठा wl1251_platक्रमm_data *data);

काष्ठा wl1251_platक्रमm_data *wl1251_get_platक्रमm_data(व्योम);

#अन्यथा

अटल अंतरभूत
पूर्णांक wl1251_set_platक्रमm_data(स्थिर काष्ठा wl1251_platक्रमm_data *data)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत
काष्ठा wl1251_platक्रमm_data *wl1251_get_platक्रमm_data(व्योम)
अणु
	वापस ERR_PTR(-ENODATA);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
