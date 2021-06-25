<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * arch/arm/mach-omap1/ams-delta-fiq.h
 *
 * Taken from the original Amstrad modअगरications to fiq.h
 *
 * Copyright (c) 2004 Amstrad Plc
 * Copyright (c) 2006 Matt Callow
 * Copyright (c) 2010 Janusz Krzysztofik
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#अगर_अघोषित __AMS_DELTA_FIQ_H
#घोषणा __AMS_DELTA_FIQ_H

#समावेश <mach/irqs.h>

/*
 * Interrupt number used क्रम passing control from FIQ to IRQ.
 * IRQ12, described as reserved, has been selected.
 */
#घोषणा INT_DEFERRED_FIQ	INT_1510_RES12
/*
 * Base address of an पूर्णांकerrupt handler that the INT_DEFERRED_FIQ beदीर्घs to.
 */
#अगर (INT_DEFERRED_FIQ < IH2_BASE)
#घोषणा DEFERRED_FIQ_IH_BASE	OMAP_IH1_BASE
#अन्यथा
#घोषणा DEFERRED_FIQ_IH_BASE	OMAP_IH2_BASE
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLER__
बाह्य अचिन्हित अक्षर qwerty_fiqin_start, qwerty_fiqin_end;

बाह्य व्योम __init ams_delta_init_fiq(काष्ठा gpio_chip *chip,
				      काष्ठा platक्रमm_device *pdev);
#पूर्ण_अगर

#पूर्ण_अगर
