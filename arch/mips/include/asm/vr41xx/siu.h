<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Include file क्रम NEC VR4100 series Serial Interface Unit.
 *
 *  Copyright (C) 2005-2008  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __NEC_VR41XX_SIU_H
#घोषणा __NEC_VR41XX_SIU_H

#घोषणा SIU_PORTS_MAX 2

प्रकार क्रमागत अणु
	SIU_INTERFACE_RS232C,
	SIU_INTERFACE_IRDA,
पूर्ण siu_पूर्णांकerface_t;

बाह्य व्योम vr41xx_select_siu_पूर्णांकerface(siu_पूर्णांकerface_t पूर्णांकerface);

प्रकार क्रमागत अणु
	SIU_USE_IRDA,
	FIR_USE_IRDA,
पूर्ण irda_use_t;

बाह्य व्योम vr41xx_use_irda(irda_use_t use);

प्रकार क्रमागत अणु
	SHARP_IRDA,
	TEMIC_IRDA,
	HP_IRDA,
पूर्ण irda_module_t;

प्रकार क्रमागत अणु
	IRDA_TX_1_5MBPS,
	IRDA_TX_4MBPS,
पूर्ण irda_speed_t;

बाह्य व्योम vr41xx_select_irda_module(irda_module_t module, irda_speed_t speed);

#अगर_घोषित CONFIG_SERIAL_VR41XX_CONSOLE
बाह्य व्योम vr41xx_siu_early_setup(काष्ठा uart_port *port);
#अन्यथा
अटल अंतरभूत व्योम vr41xx_siu_early_setup(काष्ठा uart_port *port) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __NEC_VR41XX_SIU_H */
