<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-ixp4xx/include/mach/uncompress.h 
 *
 * Copyright (C) 2002 Intel Corporation.
 * Copyright (C) 2003-2004 MontaVista Software, Inc.
 */

#अगर_अघोषित _ARCH_UNCOMPRESS_H_
#घोषणा _ARCH_UNCOMPRESS_H_

#समावेश "ixp4xx-regs.h"
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/serial_reg.h>

#घोषणा TX_DONE (UART_LSR_TEMT|UART_LSR_THRE)

अस्थिर u32* uart_base;

अटल अंतरभूत व्योम अ_दो(पूर्णांक c)
अणु
	/* Check THRE and TEMT bits beक्रमe we transmit the अक्षरacter.
	 */
	जबतक ((uart_base[UART_LSR] & TX_DONE) != TX_DONE)
		barrier();

	*uart_base = c;
पूर्ण

अटल व्योम flush(व्योम)
अणु
पूर्ण

अटल __अंतरभूत__ व्योम __arch_decomp_setup(अचिन्हित दीर्घ arch_id)
अणु
	/*
	 * Some boards are using UART2 as console
	 */
	अगर (machine_is_adi_coyote() || machine_is_gtwx5715() ||
	    machine_is_gateway7001() || machine_is_wg302v2() ||
	    machine_is_devixp() || machine_is_miccpt() || machine_is_mic256())
		uart_base = (अस्थिर u32*) IXP4XX_UART2_BASE_PHYS;
	अन्यथा
		uart_base = (अस्थिर u32*) IXP4XX_UART1_BASE_PHYS;
पूर्ण

/*
 * arch_id is a variable in decompress_kernel()
 */
#घोषणा arch_decomp_setup()	__arch_decomp_setup(arch_id)

#पूर्ण_अगर
