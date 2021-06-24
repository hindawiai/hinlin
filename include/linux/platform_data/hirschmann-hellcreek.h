<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 or MIT) */
/*
 * Hirschmann Hellcreek TSN चयन platक्रमm data.
 *
 * Copyright (C) 2020 Linutronix GmbH
 * Author Kurt Kanzenbach <kurt@linutronix.de>
 */

#अगर_अघोषित _HIRSCHMANN_HELLCREEK_H_
#घोषणा _HIRSCHMANN_HELLCREEK_H_

#समावेश <linux/types.h>

काष्ठा hellcreek_platक्रमm_data अणु
	स्थिर अक्षर *name;	/* Switch name */
	पूर्णांक num_ports;		/* Amount of चयन ports */
	पूर्णांक is_100_mbits;	/* Is it configured to 100 or 1000 mbit/s */
	पूर्णांक qbv_support;	/* Qbv support on front TSN ports */
	पूर्णांक qbv_on_cpu_port;	/* Qbv support on the CPU port */
	पूर्णांक qbu_support;	/* Qbu support on front TSN ports */
	u16 module_id;		/* Module identअगरicaton */
पूर्ण;

#पूर्ण_अगर /* _HIRSCHMANN_HELLCREEK_H_ */
