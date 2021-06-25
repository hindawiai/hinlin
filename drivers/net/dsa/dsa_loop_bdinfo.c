<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/phy.h>
#समावेश <net/dsa.h>

#समावेश "dsa_loop.h"

अटल काष्ठा dsa_loop_pdata dsa_loop_pdata = अणु
	.cd = अणु
		.port_names[0] = "lan1",
		.port_names[1] = "lan2",
		.port_names[2] = "lan3",
		.port_names[3] = "lan4",
		.port_names[DSA_LOOP_CPU_PORT] = "cpu",
	पूर्ण,
	.name = "DSA mockup driver",
	.enabled_ports = 0x1f,
	.netdev = "eth0",
पूर्ण;

अटल स्थिर काष्ठा mdio_board_info bdinfo = अणु
	.bus_id	= "fixed-0",
	.modalias = "dsa-loop",
	.mdio_addr = 31,
	.platक्रमm_data = &dsa_loop_pdata,
पूर्ण;

अटल पूर्णांक __init dsa_loop_bdinfo_init(व्योम)
अणु
	वापस mdiobus_रेजिस्टर_board_info(&bdinfo, 1);
पूर्ण
arch_initcall(dsa_loop_bdinfo_init)

MODULE_LICENSE("GPL");
