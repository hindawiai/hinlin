<शैली गुरु>
/*
 * dm355evm_msp.h - support MSP430 microcontroller on DM355EVM board
 */
#अगर_अघोषित __LINUX_I2C_DM355EVM_MSP
#घोषणा __LINUX_I2C_DM355EVM_MSP

/*
 * Written against Spectrum's ग_लिखोup क्रम the A4 firmware revision,
 * and tweaked to match source and rev D2 schematics by removing CPLD
 * and NOR flash hooks (which were last appropriate in rev B boards).
 *
 * Note that the firmware supports a flavor of ग_लिखो posting ... to be
 * sure a ग_लिखो completes, issue another पढ़ो or ग_लिखो.
 */

/* utilities to access "registers" emulated by msp430 firmware */
बाह्य पूर्णांक dm355evm_msp_ग_लिखो(u8 value, u8 reg);
बाह्य पूर्णांक dm355evm_msp_पढ़ो(u8 reg);


/* command/control रेजिस्टरs */
#घोषणा DM355EVM_MSP_COMMAND		0x00
#	define MSP_COMMAND_शून्य		0
#	define MSP_COMMAND_RESET_COLD	1
#	define MSP_COMMAND_RESET_WARM	2
#	define MSP_COMMAND_RESET_WARM_I	3
#	define MSP_COMMAND_POWEROFF	4
#	define MSP_COMMAND_IR_REINIT	5
#घोषणा DM355EVM_MSP_STATUS		0x01
#	define MSP_STATUS_BAD_OFFSET	BIT(0)
#	define MSP_STATUS_BAD_COMMAND	BIT(1)
#	define MSP_STATUS_POWER_ERROR	BIT(2)
#	define MSP_STATUS_RXBUF_OVERRUN	BIT(3)
#घोषणा DM355EVM_MSP_RESET		0x02	/* 0 bits == in reset */
#	define MSP_RESET_DC5		BIT(0)
#	define MSP_RESET_TVP5154	BIT(2)
#	define MSP_RESET_IMAGER		BIT(3)
#	define MSP_RESET_ETHERNET	BIT(4)
#	define MSP_RESET_SYS		BIT(5)
#	define MSP_RESET_AIC33		BIT(7)

/* GPIO रेजिस्टरs ... bit patterns mostly match the source MSP ports */
#घोषणा DM355EVM_MSP_LED		0x03	/* active low (MSP P4) */
#घोषणा DM355EVM_MSP_SWITCH1		0x04	/* (MSP P5, masked) */
#	define MSP_SWITCH1_SW6_1	BIT(0)
#	define MSP_SWITCH1_SW6_2	BIT(1)
#	define MSP_SWITCH1_SW6_3	BIT(2)
#	define MSP_SWITCH1_SW6_4	BIT(3)
#	define MSP_SWITCH1_J1		BIT(4)	/* NTSC/PAL */
#	define MSP_SWITCH1_MSP_INT	BIT(5)	/* active low */
#घोषणा DM355EVM_MSP_SWITCH2		0x05	/* (MSP P6, masked) */
#	define MSP_SWITCH2_SW10		BIT(3)
#	define MSP_SWITCH2_SW11		BIT(4)
#	define MSP_SWITCH2_SW12		BIT(5)
#	define MSP_SWITCH2_SW13		BIT(6)
#	define MSP_SWITCH2_SW14		BIT(7)
#घोषणा DM355EVM_MSP_SDMMC		0x06	/* (MSP P2, masked) */
#	define MSP_SDMMC_0_WP		BIT(1)
#	define MSP_SDMMC_0_CD		BIT(2)	/* active low */
#	define MSP_SDMMC_1_WP		BIT(3)
#	define MSP_SDMMC_1_CD		BIT(4)	/* active low */
#घोषणा DM355EVM_MSP_FIRMREV		0x07	/* not a GPIO (out of order) */
#घोषणा DM355EVM_MSP_VIDEO_IN		0x08	/* (MSP P3, masked) */
#	define MSP_VIDEO_IMAGER		BIT(7)	/* low == tvp5146 */

/* घातer supply रेजिस्टरs are currently omitted */

/* RTC रेजिस्टरs */
#घोषणा DM355EVM_MSP_RTC_0		0x12	/* LSB */
#घोषणा DM355EVM_MSP_RTC_1		0x13
#घोषणा DM355EVM_MSP_RTC_2		0x14
#घोषणा DM355EVM_MSP_RTC_3		0x15	/* MSB */

/* input event queue रेजिस्टरs; code == ((HIGH << 8) | LOW) */
#घोषणा DM355EVM_MSP_INPUT_COUNT	0x16	/* decrement by पढ़ोing LOW */
#घोषणा DM355EVM_MSP_INPUT_HIGH		0x17
#घोषणा DM355EVM_MSP_INPUT_LOW		0x18

#पूर्ण_अगर /* __LINUX_I2C_DM355EVM_MSP */
