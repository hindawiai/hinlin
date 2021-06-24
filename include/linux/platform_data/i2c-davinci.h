<शैली गुरु>
/*
 * DaVinci I2C controller platक्रमm_device info
 *
 * Author: Vladimir Barinov, MontaVista Software, Inc. <source@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
*/

#अगर_अघोषित __ASM_ARCH_I2C_H
#घोषणा __ASM_ARCH_I2C_H

/* All frequencies are expressed in kHz */
काष्ठा davinci_i2c_platक्रमm_data अणु
	अचिन्हित पूर्णांक	bus_freq;	/* standard bus frequency (kHz) */
	अचिन्हित पूर्णांक	bus_delay;	/* post-transaction delay (usec) */
	bool		gpio_recovery;	/* Use GPIO recovery method */
	bool		has_pfunc;	/* Chip has a ICPFUNC रेजिस्टर */
पूर्ण;

/* क्रम board setup code */
व्योम davinci_init_i2c(काष्ठा davinci_i2c_platक्रमm_data *);

#पूर्ण_अगर /* __ASM_ARCH_I2C_H */
