<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/pcmcia/pxa2xx_lubbock.c
 *
 * Author:	George Davis
 * Created:	Jan 10, 2002
 * Copyright:	MontaVista Software Inc.
 *
 * Originally based upon linux/drivers/pcmcia/sa1100_neponset.c
 *
 * Lubbock PCMCIA specअगरic routines.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/sa1111.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "sa1111_generic.h"
#समावेश "max1600.h"

अटल पूर्णांक lubbock_pcmcia_hw_init(काष्ठा soc_pcmcia_socket *skt)
अणु
	काष्ठा max1600 *m;
	पूर्णांक ret;

	ret = max1600_init(skt->socket.dev.parent, &m,
			   skt->nr ? MAX1600_CHAN_B : MAX1600_CHAN_A,
			   MAX1600_CODE_HIGH);
	अगर (ret == 0)
		skt->driver_data = m;

	वापस ret;
पूर्ण

अटल पूर्णांक
lubbock_pcmcia_configure_socket(काष्ठा soc_pcmcia_socket *skt,
				स्थिर socket_state_t *state)
अणु
	काष्ठा max1600 *m = skt->driver_data;
	पूर्णांक ret = 0;

	/* Lubbock uses the Maxim MAX1602, with the following connections:
	 *
	 * Socket 0 (PCMCIA):
	 *	MAX1602	Lubbock		Register
	 *	Pin	Signal
	 *	-----	-------		----------------------
	 *	A0VPP	S0_PWR0		SA-1111 GPIO A<0>
	 *	A1VPP	S0_PWR1		SA-1111 GPIO A<1>
	 *	A0VCC	S0_PWR2		SA-1111 GPIO A<2>
	 *	A1VCC	S0_PWR3		SA-1111 GPIO A<3>
	 *	VX	VCC
	 *	VY	+3.3V
	 *	12IN	+12V
	 *	CODE	+3.3V		Cirrus  Code, CODE = High (VY)
	 *
	 * Socket 1 (CF):
	 *	MAX1602	Lubbock		Register
	 *	Pin	Signal
	 *	-----	-------		----------------------
	 *	A0VPP	GND		VPP is not connected
	 *	A1VPP	GND		VPP is not connected
	 *	A0VCC	S1_PWR0		MISC_WR<14>
	 *	A1VCC	S1_PWR1		MISC_WR<15>
	 *	VX	VCC
	 *	VY	+3.3V
	 *	12IN	GND		VPP is not connected
	 *	CODE	+3.3V		Cirrus  Code, CODE = High (VY)
	 *
	 */

 again:
	चयन (skt->nr) अणु
	हाल 0:
	हाल 1:
		अवरोध;

	शेष:
		ret = -1;
	पूर्ण

	अगर (ret == 0)
		ret = sa1111_pcmcia_configure_socket(skt, state);
	अगर (ret == 0)
		ret = max1600_configure(m, state->Vcc, state->Vpp);

#अगर 1
	अगर (ret == 0 && state->Vcc == 33) अणु
		काष्ठा pcmcia_state new_state;

		/*
		 * HACK ALERT:
		 * We can't sense the voltage properly on Lubbock beक्रमe
		 * actually applying some घातer to the socket (catch 22).
		 * Resense the socket Voltage Sense pins after applying
		 * socket घातer.
		 *
		 * Note: It takes about 2.5ms क्रम the MAX1602 VCC output
		 * to rise.
		 */
		mdelay(3);

		sa1111_pcmcia_socket_state(skt, &new_state);

		अगर (!new_state.vs_3v && !new_state.vs_Xv) अणु
			/*
			 * Switch to 5V,  Configure socket with 5V voltage
			 */
			max1600_configure(m, 0, 0);

			/*
			 * It takes about 100ms to turn off Vcc.
			 */
			mdelay(100);

			/*
			 * We need to hack around the स्थिर qualअगरier as
			 * well to keep this ugly workaround localized and
			 * not क्रमce it to the rest of the code. Barf bags
			 * available in the seat pocket in front of you!
			 */
			((socket_state_t *)state)->Vcc = 50;
			((socket_state_t *)state)->Vpp = 50;
			जाओ again;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल काष्ठा pcmcia_low_level lubbock_pcmcia_ops = अणु
	.owner			= THIS_MODULE,
	.hw_init		= lubbock_pcmcia_hw_init,
	.configure_socket	= lubbock_pcmcia_configure_socket,
	.first			= 0,
	.nr			= 2,
पूर्ण;

#समावेश "pxa2xx_base.h"

पूर्णांक pcmcia_lubbock_init(काष्ठा sa1111_dev *sadev)
अणु
	pxa2xx_drv_pcmcia_ops(&lubbock_pcmcia_ops);
	pxa2xx_configure_sockets(&sadev->dev, &lubbock_pcmcia_ops);
	वापस sa1111_pcmcia_add(sadev, &lubbock_pcmcia_ops,
				 pxa2xx_drv_pcmcia_add_one);
पूर्ण

MODULE_LICENSE("GPL");
