<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-sa1100/include/mach/simpad.h
 *
 * based of assabet.h same as HUW_Webpanel
 *
 * This file contains the hardware specअगरic definitions क्रम SIMpad
 *
 * 2001/05/14 Juergen Messerer <juergen.messerer@मुक्तsurf.ch>
 */

#अगर_अघोषित __ASM_ARCH_SIMPAD_H
#घोषणा __ASM_ARCH_SIMPAD_H


#घोषणा GPIO_UART1_RTS	GPIO_GPIO14
#घोषणा GPIO_UART1_DTR	GPIO_GPIO7
#घोषणा GPIO_UART1_CTS	GPIO_GPIO8
#घोषणा GPIO_UART1_DCD	GPIO_GPIO23
#घोषणा GPIO_UART1_DSR	GPIO_GPIO6

#घोषणा GPIO_UART3_RTS	GPIO_GPIO12
#घोषणा GPIO_UART3_DTR	GPIO_GPIO16
#घोषणा GPIO_UART3_CTS	GPIO_GPIO13
#घोषणा GPIO_UART3_DCD	GPIO_GPIO18
#घोषणा GPIO_UART3_DSR	GPIO_GPIO17

#घोषणा GPIO_POWER_BUTTON	GPIO_GPIO0
#घोषणा GPIO_UCB1300_IRQ	GPIO_GPIO22	/* UCB GPIO and touchscreen */

#घोषणा IRQ_UART1_CTS	IRQ_GPIO15
#घोषणा IRQ_UART1_DCD	GPIO_GPIO23
#घोषणा IRQ_UART1_DSR	GPIO_GPIO6
#घोषणा IRQ_UART3_CTS	GPIO_GPIO13
#घोषणा IRQ_UART3_DCD	GPIO_GPIO18
#घोषणा IRQ_UART3_DSR	GPIO_GPIO17

#घोषणा IRQ_GPIO_UCB1300_IRQ IRQ_GPIO22
#घोषणा IRQ_GPIO_POWER_BUTTON IRQ_GPIO0


/*---  PCMCIA  ---*/
#घोषणा GPIO_CF_CD              24
#घोषणा GPIO_CF_IRQ             1

/*--- SmartCard ---*/
#घोषणा GPIO_SMART_CARD		GPIO_GPIO10
#घोषणा IRQ_GPIO_SMARD_CARD	IRQ_GPIO10

/*--- ucb1x00 GPIO ---*/
#घोषणा SIMPAD_UCB1X00_GPIO_BASE	(GPIO_MAX + 1)
#घोषणा SIMPAD_UCB1X00_GPIO_PROG1	(SIMPAD_UCB1X00_GPIO_BASE)
#घोषणा SIMPAD_UCB1X00_GPIO_PROG2	(SIMPAD_UCB1X00_GPIO_BASE + 1)
#घोषणा SIMPAD_UCB1X00_GPIO_UP		(SIMPAD_UCB1X00_GPIO_BASE + 2)
#घोषणा SIMPAD_UCB1X00_GPIO_DOWN	(SIMPAD_UCB1X00_GPIO_BASE + 3)
#घोषणा SIMPAD_UCB1X00_GPIO_LEFT	(SIMPAD_UCB1X00_GPIO_BASE + 4)
#घोषणा SIMPAD_UCB1X00_GPIO_RIGHT	(SIMPAD_UCB1X00_GPIO_BASE + 5)
#घोषणा SIMPAD_UCB1X00_GPIO_6		(SIMPAD_UCB1X00_GPIO_BASE + 6)
#घोषणा SIMPAD_UCB1X00_GPIO_7		(SIMPAD_UCB1X00_GPIO_BASE + 7)
#घोषणा SIMPAD_UCB1X00_GPIO_HEADSET	(SIMPAD_UCB1X00_GPIO_BASE + 8)
#घोषणा SIMPAD_UCB1X00_GPIO_SPEAKER	(SIMPAD_UCB1X00_GPIO_BASE + 9)

/*--- CS3 Latch ---*/
#घोषणा SIMPAD_CS3_GPIO_BASE		(GPIO_MAX + 11)
#घोषणा SIMPAD_CS3_VCC_5V_EN		(SIMPAD_CS3_GPIO_BASE)
#घोषणा SIMPAD_CS3_VCC_3V_EN		(SIMPAD_CS3_GPIO_BASE + 1)
#घोषणा SIMPAD_CS3_EN1			(SIMPAD_CS3_GPIO_BASE + 2)
#घोषणा SIMPAD_CS3_EN0			(SIMPAD_CS3_GPIO_BASE + 3)
#घोषणा SIMPAD_CS3_DISPLAY_ON		(SIMPAD_CS3_GPIO_BASE + 4)
#घोषणा SIMPAD_CS3_PCMCIA_BUFF_DIS	(SIMPAD_CS3_GPIO_BASE + 5)
#घोषणा SIMPAD_CS3_MQ_RESET		(SIMPAD_CS3_GPIO_BASE + 6)
#घोषणा SIMPAD_CS3_PCMCIA_RESET		(SIMPAD_CS3_GPIO_BASE + 7)
#घोषणा SIMPAD_CS3_DECT_POWER_ON	(SIMPAD_CS3_GPIO_BASE + 8)
#घोषणा SIMPAD_CS3_IRDA_SD		(SIMPAD_CS3_GPIO_BASE + 9)
#घोषणा SIMPAD_CS3_RS232_ON		(SIMPAD_CS3_GPIO_BASE + 10)
#घोषणा SIMPAD_CS3_SD_MEDIAQ		(SIMPAD_CS3_GPIO_BASE + 11)
#घोषणा SIMPAD_CS3_LED2_ON		(SIMPAD_CS3_GPIO_BASE + 12)
#घोषणा SIMPAD_CS3_IRDA_MODE		(SIMPAD_CS3_GPIO_BASE + 13)
#घोषणा SIMPAD_CS3_ENABLE_5V		(SIMPAD_CS3_GPIO_BASE + 14)
#घोषणा SIMPAD_CS3_RESET_SIMCARD	(SIMPAD_CS3_GPIO_BASE + 15)

#घोषणा SIMPAD_CS3_PCMCIA_BVD1		(SIMPAD_CS3_GPIO_BASE + 16)
#घोषणा SIMPAD_CS3_PCMCIA_BVD2		(SIMPAD_CS3_GPIO_BASE + 17)
#घोषणा SIMPAD_CS3_PCMCIA_VS1		(SIMPAD_CS3_GPIO_BASE + 18)
#घोषणा SIMPAD_CS3_PCMCIA_VS2		(SIMPAD_CS3_GPIO_BASE + 19)
#घोषणा SIMPAD_CS3_LOCK_IND		(SIMPAD_CS3_GPIO_BASE + 20)
#घोषणा SIMPAD_CS3_CHARGING_STATE	(SIMPAD_CS3_GPIO_BASE + 21)
#घोषणा SIMPAD_CS3_PCMCIA_SHORT		(SIMPAD_CS3_GPIO_BASE + 22)
#घोषणा SIMPAD_CS3_GPIO_23		(SIMPAD_CS3_GPIO_BASE + 23)

#घोषणा CS3_BASE        IOMEM(0xf1000000)

दीर्घ simpad_get_cs3_ro(व्योम);
दीर्घ simpad_get_cs3_shaकरोw(व्योम);
व्योम simpad_set_cs3_bit(पूर्णांक value);
व्योम simpad_clear_cs3_bit(पूर्णांक value);

#घोषणा VCC_5V_EN	0x0001 /* For 5V PCMCIA */
#घोषणा VCC_3V_EN	0x0002 /* FOR 3.3V PCMCIA */
#घोषणा EN1		0x0004 /* This is only क्रम EPROM's */
#घोषणा EN0		0x0008 /* Both should be enable क्रम 3.3V or 5V */
#घोषणा DISPLAY_ON	0x0010
#घोषणा PCMCIA_BUFF_DIS	0x0020
#घोषणा MQ_RESET	0x0040
#घोषणा PCMCIA_RESET	0x0080
#घोषणा DECT_POWER_ON	0x0100
#घोषणा IRDA_SD		0x0200 /* Shutकरोwn क्रम घातersave */
#घोषणा RS232_ON	0x0400
#घोषणा SD_MEDIAQ	0x0800 /* Shutकरोwn क्रम घातersave */
#घोषणा LED2_ON		0x1000
#घोषणा IRDA_MODE	0x2000 /* Fast/Slow IrDA mode */
#घोषणा ENABLE_5V	0x4000 /* Enable 5V circuit */
#घोषणा RESET_SIMCARD	0x8000

#घोषणा PCMCIA_BVD1	0x01
#घोषणा PCMCIA_BVD2	0x02
#घोषणा PCMCIA_VS1	0x04
#घोषणा PCMCIA_VS2	0x08
#घोषणा LOCK_IND	0x10
#घोषणा CHARGING_STATE	0x20
#घोषणा PCMCIA_SHORT	0x40

/*--- Battery ---*/
काष्ठा simpad_battery अणु
	अचिन्हित अक्षर ac_status;	/* line connected yes/no */
	अचिन्हित अक्षर status;		/* battery loading yes/no */
	अचिन्हित अक्षर percentage;	/* percentage loaded */
	अचिन्हित लघु lअगरe;		/* lअगरe till empty */
पूर्ण;

/* These should match the apm_मूलप्रण.स definitions */
#घोषणा SIMPAD_AC_STATUS_AC_OFFLINE      0x00
#घोषणा SIMPAD_AC_STATUS_AC_ONLINE       0x01
#घोषणा SIMPAD_AC_STATUS_AC_BACKUP       0x02   /* What करोes this mean? */
#घोषणा SIMPAD_AC_STATUS_AC_UNKNOWN      0xff

/* These bitfields are rarely "or'd" together */
#घोषणा SIMPAD_BATT_STATUS_HIGH          0x01
#घोषणा SIMPAD_BATT_STATUS_LOW           0x02
#घोषणा SIMPAD_BATT_STATUS_CRITICAL      0x04
#घोषणा SIMPAD_BATT_STATUS_CHARGING      0x08
#घोषणा SIMPAD_BATT_STATUS_CHARGE_MAIN   0x10
#घोषणा SIMPAD_BATT_STATUS_DEAD          0x20   /* Battery will not अक्षरge */
#घोषणा SIMPAD_BATT_NOT_INSTALLED        0x20   /* For expansion pack batteries */
#घोषणा SIMPAD_BATT_STATUS_FULL          0x40   /* Battery fully अक्षरged (and connected to AC) */
#घोषणा SIMPAD_BATT_STATUS_NOBATT        0x80
#घोषणा SIMPAD_BATT_STATUS_UNKNOWN       0xff

बाह्य पूर्णांक simpad_get_battery(काष्ठा simpad_battery* );

#पूर्ण_अगर // __ASM_ARCH_SIMPAD_H








