<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _PINCTRL_SINGLE_H
#घोषणा _PINCTRL_SINGLE_H

/**
 * irq:		optional wake-up पूर्णांकerrupt
 * rearm:	optional soc specअगरic rearm function
 *
 * Note that the irq and rearm setup should come from device
 * tree except क्रम omap where there are still some dependencies
 * to the legacy PRM code.
 */
काष्ठा pcs_pdata अणु
	पूर्णांक irq;
	व्योम (*rearm)(व्योम);
पूर्ण;

#पूर्ण_अगर /* _PINCTRL_SINGLE_H */
