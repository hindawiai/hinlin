<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * apple-gmux.h - microcontroller built पूर्णांकo dual GPU MacBook Pro & Mac Pro
 * Copyright (C) 2015 Lukas Wunner <lukas@wunner.de>
 */

#अगर_अघोषित LINUX_APPLE_GMUX_H
#घोषणा LINUX_APPLE_GMUX_H

#समावेश <linux/acpi.h>

#घोषणा GMUX_ACPI_HID "APP000B"

#अगर IS_ENABLED(CONFIG_APPLE_GMUX)

/**
 * apple_gmux_present() - detect अगर gmux is built पूर्णांकo the machine
 *
 * Drivers may use this to activate quirks specअगरic to dual GPU MacBook Pros
 * and Mac Pros, e.g. क्रम deferred probing, runसमय pm and backlight.
 *
 * Return: %true अगर gmux is present and the kernel was configured
 * with CONFIG_APPLE_GMUX, %false otherwise.
 */
अटल अंतरभूत bool apple_gmux_present(व्योम)
अणु
	वापस acpi_dev_found(GMUX_ACPI_HID);
पूर्ण

#अन्यथा  /* !CONFIG_APPLE_GMUX */

अटल अंतरभूत bool apple_gmux_present(व्योम)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* !CONFIG_APPLE_GMUX */

#पूर्ण_अगर /* LINUX_APPLE_GMUX_H */
