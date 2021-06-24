<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/drivers/pcmcia/sa1100_neponset.c
 *
 * Neponset PCMCIA specअगरic routines
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "sa1111_generic.h"
#समावेश "max1600.h"

/*
 * Neponset uses the Maxim MAX1600, with the following connections:
 *
 *   MAX1600      Neponset
 *
 *    A0VCC        SA-1111 GPIO A<1>
 *    A1VCC        SA-1111 GPIO A<0>
 *    A0VPP        CPLD NCR A0VPP
 *    A1VPP        CPLD NCR A1VPP
 *    B0VCC        SA-1111 GPIO A<2>
 *    B1VCC        SA-1111 GPIO A<3>
 *    B0VPP        ground (slot B is CF)
 *    B1VPP        ground (slot B is CF)
 *
 *     VX          VCC (5V)
 *     VY          VCC3_3 (3.3V)
 *     12INA       12V
 *     12INB       ground (slot B is CF)
 *
 * The MAX1600 CODE pin is tied to ground, placing the device in 
 * "Standard Intel code" mode. Refer to the Maxim data sheet क्रम
 * the corresponding truth table.
 */
अटल पूर्णांक neponset_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा max1600 *m;
	पूर्णांक ret;

	ret = max1600_init(skt->socket.dev.parent, &m,
			   skt->nr ? MAX1600_CHAN_B : MAX1600_CHAN_A,
			   MAX1600_CODE_LOW);
	अगर (ret == 0)
		skt->driver_data = m;

	वापस ret;
पूर्ण

अटल पूर्णांक
neponset_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt, स्थिर socket_state_t *state)
अणु
	काष्ठा max1600 *m = skt->driver_data;
	पूर्णांक ret;

	ret = sa1111_pcmcia_configure_socket(skt, state);
	अगर (ret == 0)
		ret = max1600_configure(m, state->Vcc, state->Vpp);

	वापस ret;
पूर्ण

अटल काष्ठा pcmcia_low_level neponset_pcmcia_ops = अणु
	.owner			= THIS_MODULE,
	.hw_init		= neponset_pcmcia_hw_init,
	.configure_socket	= neponset_pcmcia_configure_socket,
	.first			= 0,
	.nr			= 2,
पूर्ण;

पूर्णांक pcmcia_neponset_init(काष्ठा sa1111_dev *sadev)
अणु
	sa11xx_drv_pcmcia_ops(&neponset_pcmcia_ops);
	वापस sa1111_pcmcia_add(sadev, &neponset_pcmcia_ops,
				 sa11xx_drv_pcmcia_add_one);
पूर्ण
