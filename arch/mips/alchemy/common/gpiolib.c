<शैली गुरु>
/*
 *  Copyright (C) 2007-2009, OpenWrt.org, Florian Fainelli <florian@खोलोwrt.org>
 *	GPIOLIB support क्रम Alchemy chips.
 *
 *  This program is मुक्त software; you can redistribute	 it and/or modअगरy it
 *  under  the terms of	 the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the	License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED	  ``AS	IS'' AND   ANY	EXPRESS OR IMPLIED
 *  WARRANTIES,	  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO	EVENT  SHALL   THE AUTHOR  BE	 LIABLE FOR ANY	  सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED	  TO, PROCUREMENT OF  SUBSTITUTE GOODS	OR SERVICES; LOSS OF
 *  USE, DATA,	OR PROFITS; OR	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN	 CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Notes :
 *	This file must ONLY be built when CONFIG_GPIOLIB=y and
 *	 CONFIG_ALCHEMY_GPIO_INसूचीECT=n, otherwise compilation will fail!
 *	au1000 SoC have only one GPIO block : GPIO1
 *	Au1100, Au15x0, Au12x0 have a second one : GPIO2
 *	Au1300 is totally dअगरferent: 1 block with up to 128 GPIOs
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/mach-au1x00/gpio-au1000.h>
#समावेश <यंत्र/mach-au1x00/gpio-au1300.h>

अटल पूर्णांक gpio2_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस !!alchemy_gpio2_get_value(offset + ALCHEMY_GPIO2_BASE);
पूर्ण

अटल व्योम gpio2_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	alchemy_gpio2_set_value(offset + ALCHEMY_GPIO2_BASE, value);
पूर्ण

अटल पूर्णांक gpio2_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस alchemy_gpio2_direction_input(offset + ALCHEMY_GPIO2_BASE);
पूर्ण

अटल पूर्णांक gpio2_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				  पूर्णांक value)
अणु
	वापस alchemy_gpio2_direction_output(offset + ALCHEMY_GPIO2_BASE,
						value);
पूर्ण

अटल पूर्णांक gpio2_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस alchemy_gpio2_to_irq(offset + ALCHEMY_GPIO2_BASE);
पूर्ण


अटल पूर्णांक gpio1_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस !!alchemy_gpio1_get_value(offset + ALCHEMY_GPIO1_BASE);
पूर्ण

अटल व्योम gpio1_set(काष्ठा gpio_chip *chip,
				अचिन्हित offset, पूर्णांक value)
अणु
	alchemy_gpio1_set_value(offset + ALCHEMY_GPIO1_BASE, value);
पूर्ण

अटल पूर्णांक gpio1_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस alchemy_gpio1_direction_input(offset + ALCHEMY_GPIO1_BASE);
पूर्ण

अटल पूर्णांक gpio1_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	वापस alchemy_gpio1_direction_output(offset + ALCHEMY_GPIO1_BASE,
					     value);
पूर्ण

अटल पूर्णांक gpio1_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस alchemy_gpio1_to_irq(offset + ALCHEMY_GPIO1_BASE);
पूर्ण

काष्ठा gpio_chip alchemy_gpio_chip[] = अणु
	[0] = अणु
		.label			= "alchemy-gpio1",
		.direction_input	= gpio1_direction_input,
		.direction_output	= gpio1_direction_output,
		.get			= gpio1_get,
		.set			= gpio1_set,
		.to_irq			= gpio1_to_irq,
		.base			= ALCHEMY_GPIO1_BASE,
		.ngpio			= ALCHEMY_GPIO1_NUM,
	पूर्ण,
	[1] = अणु
		.label			= "alchemy-gpio2",
		.direction_input	= gpio2_direction_input,
		.direction_output	= gpio2_direction_output,
		.get			= gpio2_get,
		.set			= gpio2_set,
		.to_irq			= gpio2_to_irq,
		.base			= ALCHEMY_GPIO2_BASE,
		.ngpio			= ALCHEMY_GPIO2_NUM,
	पूर्ण,
पूर्ण;

अटल पूर्णांक alchemy_gpic_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक off)
अणु
	वापस !!au1300_gpio_get_value(off + AU1300_GPIO_BASE);
पूर्ण

अटल व्योम alchemy_gpic_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक off, पूर्णांक v)
अणु
	au1300_gpio_set_value(off + AU1300_GPIO_BASE, v);
पूर्ण

अटल पूर्णांक alchemy_gpic_dir_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक off)
अणु
	वापस au1300_gpio_direction_input(off + AU1300_GPIO_BASE);
पूर्ण

अटल पूर्णांक alchemy_gpic_dir_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक off,
				   पूर्णांक v)
अणु
	वापस au1300_gpio_direction_output(off + AU1300_GPIO_BASE, v);
पूर्ण

अटल पूर्णांक alchemy_gpic_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक off)
अणु
	वापस au1300_gpio_to_irq(off + AU1300_GPIO_BASE);
पूर्ण

अटल काष्ठा gpio_chip au1300_gpiochip = अणु
	.label			= "alchemy-gpic",
	.direction_input	= alchemy_gpic_dir_input,
	.direction_output	= alchemy_gpic_dir_output,
	.get			= alchemy_gpic_get,
	.set			= alchemy_gpic_set,
	.to_irq			= alchemy_gpic_gpio_to_irq,
	.base			= AU1300_GPIO_BASE,
	.ngpio			= AU1300_GPIO_NUM,
पूर्ण;

अटल पूर्णांक __init alchemy_gpiochip_init(व्योम)
अणु
	पूर्णांक ret = 0;

	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
		ret = gpiochip_add_data(&alchemy_gpio_chip[0], शून्य);
		अवरोध;
	हाल ALCHEMY_CPU_AU1500...ALCHEMY_CPU_AU1200:
		ret = gpiochip_add_data(&alchemy_gpio_chip[0], शून्य);
		ret |= gpiochip_add_data(&alchemy_gpio_chip[1], शून्य);
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		ret = gpiochip_add_data(&au1300_gpiochip, शून्य);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
arch_initcall(alchemy_gpiochip_init);
