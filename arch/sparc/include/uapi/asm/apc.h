<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* apc - Driver definitions क्रम घातer management functions
 * of Aurora Personality Chip (APC) on SPARCstation-4/5 and 
 * derivatives
 *
 * Copyright (c) 2001 Eric Brower (ebrower@usa.net)
 *
 */

#अगर_अघोषित _SPARC_APC_H
#घोषणा _SPARC_APC_H

#समावेश <linux/ioctl.h>

#घोषणा APC_IOC	'A'

#घोषणा APCIOCGFANCTL _IOR(APC_IOC, 0x00, पूर्णांक)	/* Get fan speed	*/
#घोषणा APCIOCSFANCTL _IOW(APC_IOC, 0x01, पूर्णांक)	/* Set fan speed	*/

#घोषणा APCIOCGCPWR   _IOR(APC_IOC, 0x02, पूर्णांक)	/* Get CPOWER state	*/
#घोषणा APCIOCSCPWR   _IOW(APC_IOC, 0x03, पूर्णांक)	/* Set CPOWER state	*/

#घोषणा APCIOCGBPORT   _IOR(APC_IOC, 0x04, पूर्णांक)	/* Get BPORT state 	*/
#घोषणा APCIOCSBPORT   _IOW(APC_IOC, 0x05, पूर्णांक)	/* Set BPORT state	*/

/*
 * Register offsets
 */
#घोषणा APC_IDLE_REG	0x00
#घोषणा APC_FANCTL_REG	0x20
#घोषणा APC_CPOWER_REG	0x24
#घोषणा APC_BPORT_REG	0x30

#घोषणा APC_REGMASK		0x01
#घोषणा APC_BPMASK		0x03

/*
 * IDLE - CPU standby values (set to initiate standby)
 */
#घोषणा APC_IDLE_ON		0x01

/*
 * FANCTL - Fan speed control state values
 */
#घोषणा APC_FANCTL_HI	0x00	/* Fan speed high	*/
#घोषणा APC_FANCTL_LO	0x01	/* Fan speed low	*/

/*
 * CPWR - Convenience घातer outlet state values 
 */
#घोषणा APC_CPOWER_ON	0x00	/* Conv घातer on	*/
#घोषणा APC_CPOWER_OFF	0x01	/* Conv घातer off	*/

/*
 * BPA/BPB - Read-Write "Bit Ports" state values (reset to 0 at घातer-on)
 *
 * WARNING: Internal usage of bit ports is platक्रमm dependent--
 * करोn't modअगरy BPORT settings unless you know what you are करोing.
 * 
 * On SS5 BPA seems to toggle onboard ethernet loopback... -E
 */
#घोषणा APC_BPORT_A		0x01	/* Bit Port A		*/
#घोषणा APC_BPORT_B		0x02	/* Bit Port B		*/

#पूर्ण_अगर /* !(_SPARC_APC_H) */
