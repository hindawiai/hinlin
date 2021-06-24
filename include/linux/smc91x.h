<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SMC91X_H__
#घोषणा __SMC91X_H__

/*
 * These bits define which access sizes a platक्रमm can support, rather
 * than the maximal access size.  So, अगर your platक्रमm can करो 16-bit
 * and 32-bit accesses to the SMC91x device, but not 8-bit, set both
 * SMC91X_USE_16BIT and SMC91X_USE_32BIT.
 *
 * The SMC91x driver requires at least one of SMC91X_USE_8BIT or
 * SMC91X_USE_16BIT to be supported - just setting SMC91X_USE_32BIT is
 * an invalid configuration.
 */
#घोषणा SMC91X_USE_8BIT (1 << 0)
#घोषणा SMC91X_USE_16BIT (1 << 1)
#घोषणा SMC91X_USE_32BIT (1 << 2)

#घोषणा SMC91X_NOWAIT		(1 << 3)

/* two bits क्रम IO_SHIFT, let's hope later designs will keep this sane */
#घोषणा SMC91X_IO_SHIFT_0	(0 << 4)
#घोषणा SMC91X_IO_SHIFT_1	(1 << 4)
#घोषणा SMC91X_IO_SHIFT_2	(2 << 4)
#घोषणा SMC91X_IO_SHIFT_3	(3 << 4)
#घोषणा SMC91X_IO_SHIFT(x)	(((x) >> 4) & 0x3)

#घोषणा SMC91X_USE_DMA		(1 << 6)

#घोषणा RPC_LED_100_10	(0x00)	/* LED = 100Mbps OR's with 10Mbps link detect */
#घोषणा RPC_LED_RES	(0x01)	/* LED = Reserved */
#घोषणा RPC_LED_10	(0x02)	/* LED = 10Mbps link detect */
#घोषणा RPC_LED_FD	(0x03)	/* LED = Full Duplex Mode */
#घोषणा RPC_LED_TX_RX	(0x04)	/* LED = TX or RX packet occurred */
#घोषणा RPC_LED_100	(0x05)	/* LED = 100Mbps link detect */
#घोषणा RPC_LED_TX	(0x06)	/* LED = TX packet occurred */
#घोषणा RPC_LED_RX	(0x07)	/* LED = RX packet occurred */

काष्ठा smc91x_platdata अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर leda;
	अचिन्हित अक्षर ledb;
	bool pxa_u16_align4;	/* PXA buggy u16 ग_लिखोs on 4*n+2 addresses */
पूर्ण;

#पूर्ण_अगर /* __SMC91X_H__ */
