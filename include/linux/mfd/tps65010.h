<शैली गुरु>
/* linux/mfd/tps65010.h
 *
 * Functions to access TPS65010 घातer management device.
 *
 * Copyright (C) 2004 Dirk Behme <dirk.behme@de.bosch.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित __LINUX_I2C_TPS65010_H
#घोषणा __LINUX_I2C_TPS65010_H

/*
 * ----------------------------------------------------------------------------
 * Registers, all 8 bits
 * ----------------------------------------------------------------------------
 */

#घोषणा	TPS_CHGSTATUS		0x01
#	define	TPS_CHG_USB		(1 << 7)
#	define	TPS_CHG_AC		(1 << 6)
#	define	TPS_CHG_THERM		(1 << 5)
#	define	TPS_CHG_TERM		(1 << 4)
#	define	TPS_CHG_TAPER_TMO	(1 << 3)
#	define	TPS_CHG_CHG_TMO		(1 << 2)
#	define	TPS_CHG_PRECHG_TMO	(1 << 1)
#	define	TPS_CHG_TEMP_ERR	(1 << 0)
#घोषणा	TPS_REGSTATUS		0x02
#	define	TPS_REG_ONOFF		(1 << 7)
#	define	TPS_REG_COVER		(1 << 6)
#	define	TPS_REG_UVLO		(1 << 5)
#	define	TPS_REG_NO_CHG		(1 << 4)	/* tps65013 */
#	define	TPS_REG_PG_LD02		(1 << 3)
#	define	TPS_REG_PG_LD01		(1 << 2)
#	define	TPS_REG_PG_MAIN		(1 << 1)
#	define	TPS_REG_PG_CORE		(1 << 0)
#घोषणा	TPS_MASK1		0x03
#घोषणा	TPS_MASK2		0x04
#घोषणा	TPS_ACKINT1		0x05
#घोषणा	TPS_ACKINT2		0x06
#घोषणा	TPS_CHGCONFIG		0x07
#	define	TPS_CHARGE_POR		(1 << 7)	/* 65010/65012 */
#	define	TPS65013_AUA		(1 << 7)	/* 65011/65013 */
#	define	TPS_CHARGE_RESET	(1 << 6)
#	define	TPS_CHARGE_FAST		(1 << 5)
#	define	TPS_CHARGE_CURRENT	(3 << 3)
#	define	TPS_VBUS_500MA		(1 << 2)
#	define	TPS_VBUS_CHARGING	(1 << 1)
#	define	TPS_CHARGE_ENABLE	(1 << 0)
#घोषणा	TPS_LED1_ON		0x08
#घोषणा	TPS_LED1_PER		0x09
#घोषणा	TPS_LED2_ON		0x0a
#घोषणा	TPS_LED2_PER		0x0b
#घोषणा	TPS_VDCDC1		0x0c
#	define	TPS_ENABLE_LP		(1 << 3)
#घोषणा	TPS_VDCDC2		0x0d
#	define	TPS_LP_CORखातापूर्णF	(1 << 7)
#	define 	TPS_VCORE_1_8V	(7<<4)
#	define 	TPS_VCORE_1_5V	(6 << 4)
#	define 	TPS_VCORE_1_4V	(5 << 4)
#	define 	TPS_VCORE_1_3V	(4 << 4)
#	define 	TPS_VCORE_1_2V	(3 << 4)
#	define 	TPS_VCORE_1_1V	(2 << 4)
#	define 	TPS_VCORE_1_0V	(1 << 4)
#	define 	TPS_VCORE_0_85V	(0 << 4)
#	define	TPS_VCORE_LP_1_2V (3 << 2)
#	define	TPS_VCORE_LP_1_1V (2 << 2)
#	define	TPS_VCORE_LP_1_0V (1 << 2)
#	define	TPS_VCORE_LP_0_85V (0 << 2)
#	define	TPS_VIB		(1 << 1)
#	define	TPS_VCORE_DISCH	(1 << 0)
#घोषणा	TPS_VREGS1		0x0e
#	define	TPS_LDO2_ENABLE	(1 << 7)
#	define	TPS_LDO2_OFF	(1 << 6)
#	define	TPS_VLDO2_3_0V	(3 << 4)
#	define	TPS_VLDO2_2_75V	(2 << 4)
#	define	TPS_VLDO2_2_5V	(1 << 4)
#	define	TPS_VLDO2_1_8V	(0 << 4)
#	define	TPS_LDO1_ENABLE	(1 << 3)
#	define	TPS_LDO1_OFF	(1 << 2)
#	define	TPS_VLDO1_3_0V	(3 << 0)
#	define	TPS_VLDO1_2_75V	(2 << 0)
#	define	TPS_VLDO1_2_5V	(1 << 0)
#	define	TPS_VLDO1_ADJ	(0 << 0)
#घोषणा	TPS_MASK3		0x0f
#घोषणा	TPS_DEFGPIO		0x10

/*
 * ----------------------------------------------------------------------------
 * Macros used by exported functions
 * ----------------------------------------------------------------------------
 */

#घोषणा LED1  1
#घोषणा LED2  2
#घोषणा OFF   0
#घोषणा ON    1
#घोषणा BLINK 2
#घोषणा GPIO1 1
#घोषणा GPIO2 2
#घोषणा GPIO3 3
#घोषणा GPIO4 4
#घोषणा LOW   0
#घोषणा HIGH  1

/*
 * ----------------------------------------------------------------------------
 * Exported functions
 * ----------------------------------------------------------------------------
 */

/* Draw from VBUS:
 *   0 mA -- DON'T DRAW (might supply घातer instead)
 * 100 mA -- usb unit load (slowest अक्षरge rate)
 * 500 mA -- usb high घातer (fast battery अक्षरge)
 */
बाह्य पूर्णांक tps65010_set_vbus_draw(अचिन्हित mA);

/* tps65010_set_gpio_out_value parameter:
 * gpio:  GPIO1, GPIO2, GPIO3 or GPIO4
 * value: LOW or HIGH
 */
बाह्य पूर्णांक tps65010_set_gpio_out_value(अचिन्हित gpio, अचिन्हित value);

/* tps65010_set_led parameter:
 * led:  LED1 or LED2
 * mode: ON, OFF or BLINK
 */
बाह्य पूर्णांक tps65010_set_led(अचिन्हित led, अचिन्हित mode);

/* tps65010_set_vib parameter:
 * value: ON or OFF
 */
बाह्य पूर्णांक tps65010_set_vib(अचिन्हित value);

/* tps65010_set_low_pwr parameter:
 * mode: ON or OFF
 */
बाह्य पूर्णांक tps65010_set_low_pwr(अचिन्हित mode);

/* tps65010_config_vregs1 parameter:
 * value to be written to VREGS1 रेजिस्टर
 * Note: The complete रेजिस्टर is written, set all bits you need
 */
बाह्य पूर्णांक tps65010_config_vregs1(अचिन्हित value);

/* tps65013_set_low_pwr parameter:
 * mode: ON or OFF
 */
बाह्य पूर्णांक tps65013_set_low_pwr(अचिन्हित mode);

/* tps65010_set_vdcdc2
 *  value to be written to VDCDC2
 */
बाह्य पूर्णांक tps65010_config_vdcdc2(अचिन्हित value);

काष्ठा i2c_client;

/**
 * काष्ठा tps65010_board - packages GPIO and LED lines
 * @base: the GPIO number to assign to GPIO-1
 * @ouपंचांगask: bit (N-1) is set to allow GPIO-N to be used as an
 *	(खोलो drain) output
 * @setup: optional callback issued once the GPIOs are valid
 * @tearकरोwn: optional callback issued beक्रमe the GPIOs are invalidated
 * @context: optional parameter passed to setup() and tearकरोwn()
 *
 * Board data may be used to package the GPIO (and LED) lines क्रम use
 * in by the generic GPIO and LED frameworks.  The first four GPIOs
 * starting at gpio_base are GPIO1..GPIO4.  The next two are LED1/nPG
 * and LED2 (with hardware blinking capability, not currently exposed).
 *
 * The @setup callback may be used with the kind of board-specअगरic glue
 * which hands the (now-valid) GPIOs to other drivers, or which माला_दो
 * devices in their initial states using these GPIOs.
 */
काष्ठा tps65010_board अणु
	पूर्णांक				base;
	अचिन्हित			ouपंचांगask;

	पूर्णांक		(*setup)(काष्ठा i2c_client *client, व्योम *context);
	पूर्णांक		(*tearकरोwn)(काष्ठा i2c_client *client, व्योम *context);
	व्योम		*context;
पूर्ण;

#पूर्ण_अगर /*  __LINUX_I2C_TPS65010_H */

