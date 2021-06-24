<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *
 * envctrl.h: Definitions क्रम access to the i2c environment
 *            monitoring on Ultrasparc प्रणालीs.
 *
 * Copyright (C) 1998  Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 2000  Vinh Truong  (vinh.truong@eng.sun.com)
 * VT - Add all ioctl commands and environment status definitions
 * VT - Add application note
 */
#अगर_अघोषित _SPARC64_ENVCTRL_H
#घोषणा _SPARC64_ENVCTRL_H 1

#समावेश <linux/ioctl.h>

/* Application note:
 *
 * The driver supports 4 operations: खोलो(), बंद(), ioctl(), पढ़ो()
 * The device name is /dev/envctrl.
 * Below is sample usage:
 *
 *	fd = खोलो("/dev/envtrl", O_RDONLY);
 *	अगर (ioctl(fd, ENVCTRL_READ_SHUTDOWN_TEMPERATURE, 0) < 0)
 *		म_लिखो("error\n");
 *	ret = पढ़ो(fd, buf, 10);
 *	बंद(fd);
 *
 * Notice in the हाल of cpu voltage and temperature, the शेष is
 * cpu0.  If we need to know the info of cpu1, cpu2, cpu3, we need to
 * pass in cpu number in ioctl() last parameter.  For example, to
 * get the voltage of cpu2:
 *
 *	ioctlbuf[0] = 2;
 *	अगर (ioctl(fd, ENVCTRL_READ_CPU_VOLTAGE, ioctlbuf) < 0)
 *		म_लिखो("error\n");
 *	ret = पढ़ो(fd, buf, 10);
 *
 * All the वापस values are in ascii.  So check पढ़ो वापस value
 * and करो appropriate conversions in your application.
 */

/* IOCTL commands */

/* Note: these commands reflect possible monitor features.
 * Some boards choose to support some of the features only.
 */
#घोषणा ENVCTRL_RD_CPU_TEMPERATURE	_IOR('p', 0x40, पूर्णांक)
#घोषणा ENVCTRL_RD_CPU_VOLTAGE		_IOR('p', 0x41, पूर्णांक)
#घोषणा ENVCTRL_RD_FAN_STATUS		_IOR('p', 0x42, पूर्णांक)
#घोषणा ENVCTRL_RD_WARNING_TEMPERATURE	_IOR('p', 0x43, पूर्णांक)
#घोषणा ENVCTRL_RD_SHUTDOWN_TEMPERATURE	_IOR('p', 0x44, पूर्णांक)
#घोषणा ENVCTRL_RD_VOLTAGE_STATUS	_IOR('p', 0x45, पूर्णांक)
#घोषणा ENVCTRL_RD_SCSI_TEMPERATURE	_IOR('p', 0x46, पूर्णांक)
#घोषणा ENVCTRL_RD_ETHERNET_TEMPERATURE	_IOR('p', 0x47, पूर्णांक)
#घोषणा ENVCTRL_RD_MTHRBD_TEMPERATURE	_IOR('p', 0x48, पूर्णांक)

#घोषणा ENVCTRL_RD_GLOBALADDRESS	_IOR('p', 0x49, पूर्णांक)

/* Read वापस values क्रम a voltage status request. */
#घोषणा ENVCTRL_VOLTAGE_POWERSUPPLY_GOOD	0x01
#घोषणा ENVCTRL_VOLTAGE_BAD			0x02
#घोषणा ENVCTRL_POWERSUPPLY_BAD			0x03
#घोषणा ENVCTRL_VOLTAGE_POWERSUPPLY_BAD		0x04

/* Read वापस values क्रम a fan status request.
 * A failure match means either the fan fails or
 * the fan is not connected.  Some boards have optional
 * connectors to connect extra fans.
 *
 * There are maximum 8 monitor fans.  Some are cpu fans
 * some are प्रणाली fans.  The mask below only indicates
 * fan by order number.
 * Below is a sample application:
 *
 *	अगर (ioctl(fd, ENVCTRL_READ_FAN_STATUS, 0) < 0) अणु
 *		म_लिखो("ioctl fan failed\n");
 *	पूर्ण
 *	अगर (पढ़ो(fd, rslt, 1) <= 0) अणु
 *		म_लिखो("error or fan not monitored\n");
 *	पूर्ण अन्यथा अणु
 *		अगर (rslt[0] == ENVCTRL_ALL_FANS_GOOD) अणु
 *			म_लिखो("all fans good\n");
 *	पूर्ण अन्यथा अगर (rslt[0] == ENVCTRL_ALL_FANS_BAD) अणु
 *		म_लिखो("all fans bad\n");
 *	पूर्ण अन्यथा अणु
 *		अगर (rslt[0] & ENVCTRL_FAN0_FAILURE_MASK) अणु
 *			म_लिखो("fan 0 failed or not connected\n");
 *	पूर्ण
 *	......
 */

#घोषणा ENVCTRL_ALL_FANS_GOOD			0x00
#घोषणा ENVCTRL_FAN0_FAILURE_MASK		0x01
#घोषणा ENVCTRL_FAN1_FAILURE_MASK		0x02
#घोषणा ENVCTRL_FAN2_FAILURE_MASK		0x04
#घोषणा ENVCTRL_FAN3_FAILURE_MASK		0x08
#घोषणा ENVCTRL_FAN4_FAILURE_MASK		0x10
#घोषणा ENVCTRL_FAN5_FAILURE_MASK		0x20
#घोषणा ENVCTRL_FAN6_FAILURE_MASK		0x40
#घोषणा ENVCTRL_FAN7_FAILURE_MASK		0x80
#घोषणा ENVCTRL_ALL_FANS_BAD 			0xFF

#पूर्ण_अगर /* !(_SPARC64_ENVCTRL_H) */
