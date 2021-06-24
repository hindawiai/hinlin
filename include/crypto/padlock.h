<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver क्रम VIA PadLock
 *
 * Copyright (c) 2004 Michal Ludvig <michal@logix.cz>
 */

#अगर_अघोषित _CRYPTO_PADLOCK_H
#घोषणा _CRYPTO_PADLOCK_H

#घोषणा PADLOCK_ALIGNMENT 16

#घोषणा PFX	KBUILD_MODNAME ": "

#घोषणा PADLOCK_CRA_PRIORITY	300
#घोषणा PADLOCK_COMPOSITE_PRIORITY 400

#अगर_घोषित CONFIG_64BIT
#घोषणा STACK_ALIGN 16
#अन्यथा
#घोषणा STACK_ALIGN 4
#पूर्ण_अगर

#पूर्ण_अगर	/* _CRYPTO_PADLOCK_H */
