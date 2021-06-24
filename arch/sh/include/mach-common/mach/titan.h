<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Platक्रमm definitions क्रम Titan
 */
#अगर_अघोषित _ASM_SH_TITAN_H
#घोषणा _ASM_SH_TITAN_H

#समावेश <linux/sh_पूर्णांकc.h>

#घोषणा __IO_PREFIX titan
#समावेश <यंत्र/io_generic.h>

/* IRQ assignments */
#घोषणा TITAN_IRQ_WAN		evt2irq(0x240)	/* eth0 (WAN) */
#घोषणा TITAN_IRQ_LAN		evt2irq(0x2a0)	/* eth1 (LAN) */
#घोषणा TITAN_IRQ_MPCIA		evt2irq(0x300)	/* mPCI A */
#घोषणा TITAN_IRQ_MPCIB		evt2irq(0x360)	/* mPCI B */
#घोषणा TITAN_IRQ_USB		evt2irq(0x360)	/* USB */

#पूर्ण_अगर /* __ASM_SH_TITAN_H */
