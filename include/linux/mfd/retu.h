<शैली गुरु>
/*
 * Retu/Tahvo MFD driver पूर्णांकerface
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 */

#अगर_अघोषित __LINUX_MFD_RETU_H
#घोषणा __LINUX_MFD_RETU_H

काष्ठा retu_dev;

पूर्णांक retu_पढ़ो(काष्ठा retu_dev *, u8);
पूर्णांक retu_ग_लिखो(काष्ठा retu_dev *, u8, u16);

/* Registers */
#घोषणा RETU_REG_WATCHDOG	0x17		/* Watchकरोg */
#घोषणा RETU_REG_CC1		0x0d		/* Common control रेजिस्टर 1 */
#घोषणा RETU_REG_STATUS		0x16		/* Status रेजिस्टर */

/* Interrupt sources */
#घोषणा TAHVO_INT_VBUS		0		/* VBUS state */

/* Interrupt status */
#घोषणा TAHVO_STAT_VBUS		(1 << TAHVO_INT_VBUS)

#पूर्ण_अगर /* __LINUX_MFD_RETU_H */
