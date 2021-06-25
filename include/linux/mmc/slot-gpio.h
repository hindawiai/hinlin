<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Generic GPIO card-detect helper header
 *
 * Copyright (C) 2011, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#अगर_अघोषित MMC_SLOT_GPIO_H
#घोषणा MMC_SLOT_GPIO_H

#समावेश <linux/types.h>
#समावेश <linux/irqवापस.h>

काष्ठा mmc_host;

पूर्णांक mmc_gpio_get_ro(काष्ठा mmc_host *host);
पूर्णांक mmc_gpio_get_cd(काष्ठा mmc_host *host);
पूर्णांक mmc_gpiod_request_cd(काष्ठा mmc_host *host, स्थिर अक्षर *con_id,
			 अचिन्हित पूर्णांक idx, bool override_active_level,
			 अचिन्हित पूर्णांक debounce);
पूर्णांक mmc_gpiod_request_ro(काष्ठा mmc_host *host, स्थिर अक्षर *con_id,
			 अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक debounce);
व्योम mmc_gpio_set_cd_isr(काष्ठा mmc_host *host,
			 irqवापस_t (*isr)(पूर्णांक irq, व्योम *dev_id));
पूर्णांक mmc_gpio_set_cd_wake(काष्ठा mmc_host *host, bool on);
व्योम mmc_gpiod_request_cd_irq(काष्ठा mmc_host *host);
bool mmc_can_gpio_cd(काष्ठा mmc_host *host);
bool mmc_can_gpio_ro(काष्ठा mmc_host *host);

#पूर्ण_अगर
