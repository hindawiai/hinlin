<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित RTL8180_SA2400_H
#घोषणा RTL8180_SA2400_H

/*
 * Radio tuning क्रम Philips SA2400 on RTL8180
 *
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 *
 * Code from the BSD driver and the rtl8181 project have been
 * very useful to understand certain things
 *
 * I want to thanks the Authors of such projects and the Ndiswrapper
 * project Authors.
 *
 * A special Big Thanks also is क्रम all people who करोnated me cards,
 * making possible the creation of the original rtl8180 driver
 * from which this code is derived!
 */

#घोषणा SA2400_ANTENNA 0x91
#घोषणा SA2400_DIG_ANAPARAM_PWR1_ON 0x8
#घोषणा SA2400_ANA_ANAPARAM_PWR1_ON 0x28
#घोषणा SA2400_ANAPARAM_PWR0_ON 0x3

/* RX sensitivity in dbm */
#घोषणा SA2400_MAX_SENS 85

#घोषणा SA2400_REG4_FIRDAC_SHIFT 7

बाह्य स्थिर काष्ठा rtl818x_rf_ops sa2400_rf_ops;

#पूर्ण_अगर /* RTL8180_SA2400_H */
