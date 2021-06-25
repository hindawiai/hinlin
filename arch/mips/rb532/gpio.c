<शैली गुरु>
/*
 *  Miscellaneous functions क्रम IDT EB434 board
 *
 *  Copyright 2004 IDT Inc. (rischelp@idt.com)
 *  Copyright 2006 Phil Sutter <n0-1@मुक्तwrt.org>
 *  Copyright 2007 Florian Fainelli <florian@खोलोwrt.org>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/driver.h>

#समावेश <यंत्र/mach-rc32434/rb.h>
#समावेश <यंत्र/mach-rc32434/gpपन.स>

काष्ठा rb532_gpio_chip अणु
	काष्ठा gpio_chip chip;
	व्योम __iomem	 *regbase;
पूर्ण;

अटल काष्ठा resource rb532_gpio_reg0_res[] = अणु
	अणु
		.name	= "gpio_reg0",
		.start	= REGBASE + GPIOBASE,
		.end	= REGBASE + GPIOBASE + माप(काष्ठा rb532_gpio_reg) - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

/* rb532_set_bit - sanely set a bit
 *
 * bitval: new value क्रम the bit
 * offset: bit index in the 4 byte address range
 * ioaddr: 4 byte aligned address being altered
 */
अटल अंतरभूत व्योम rb532_set_bit(अचिन्हित bitval,
		अचिन्हित offset, व्योम __iomem *ioaddr)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	local_irq_save(flags);

	val = पढ़ोl(ioaddr);
	val &= ~(!bitval << offset);   /* unset bit अगर bitval == 0 */
	val |= (!!bitval << offset);   /* set bit अगर bitval == 1 */
	ग_लिखोl(val, ioaddr);

	local_irq_restore(flags);
पूर्ण

/* rb532_get_bit - पढ़ो a bit
 *
 * वापसs the boolean state of the bit, which may be > 1
 */
अटल अंतरभूत पूर्णांक rb532_get_bit(अचिन्हित offset, व्योम __iomem *ioaddr)
अणु
	वापस पढ़ोl(ioaddr) & (1 << offset);
पूर्ण

/*
 * Return GPIO level */
अटल पूर्णांक rb532_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा rb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);
	वापस !!rb532_get_bit(offset, gpch->regbase + GPIOD);
पूर्ण

/*
 * Set output GPIO level
 */
अटल व्योम rb532_gpio_set(काष्ठा gpio_chip *chip,
				अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा rb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);
	rb532_set_bit(value, offset, gpch->regbase + GPIOD);
पूर्ण

/*
 * Set GPIO direction to input
 */
अटल पूर्णांक rb532_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा rb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);

	/* disable alternate function in हाल it's set */
	rb532_set_bit(0, offset, gpch->regbase + GPIOFUNC);

	rb532_set_bit(0, offset, gpch->regbase + GPIOCFG);
	वापस 0;
पूर्ण

/*
 * Set GPIO direction to output
 */
अटल पूर्णांक rb532_gpio_direction_output(काष्ठा gpio_chip *chip,
					अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा rb532_gpio_chip	*gpch;

	gpch = gpiochip_get_data(chip);

	/* disable alternate function in हाल it's set */
	rb532_set_bit(0, offset, gpch->regbase + GPIOFUNC);

	/* set the initial output value */
	rb532_set_bit(value, offset, gpch->regbase + GPIOD);

	rb532_set_bit(1, offset, gpch->regbase + GPIOCFG);
	वापस 0;
पूर्ण

अटल पूर्णांक rb532_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित gpio)
अणु
	वापस 8 + 4 * 32 + gpio;
पूर्ण

अटल काष्ठा rb532_gpio_chip rb532_gpio_chip[] = अणु
	[0] = अणु
		.chip = अणु
			.label			= "gpio0",
			.direction_input	= rb532_gpio_direction_input,
			.direction_output	= rb532_gpio_direction_output,
			.get			= rb532_gpio_get,
			.set			= rb532_gpio_set,
			.to_irq			= rb532_gpio_to_irq,
			.base			= 0,
			.ngpio			= 32,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Set GPIO पूर्णांकerrupt level
 */
व्योम rb532_gpio_set_ilevel(पूर्णांक bit, अचिन्हित gpio)
अणु
	rb532_set_bit(bit, gpio, rb532_gpio_chip->regbase + GPIOILEVEL);
पूर्ण
EXPORT_SYMBOL(rb532_gpio_set_ilevel);

/*
 * Set GPIO पूर्णांकerrupt status
 */
व्योम rb532_gpio_set_istat(पूर्णांक bit, अचिन्हित gpio)
अणु
	rb532_set_bit(bit, gpio, rb532_gpio_chip->regbase + GPIOISTAT);
पूर्ण
EXPORT_SYMBOL(rb532_gpio_set_istat);

/*
 * Configure GPIO alternate function
 */
व्योम rb532_gpio_set_func(अचिन्हित gpio)
अणु
       rb532_set_bit(1, gpio, rb532_gpio_chip->regbase + GPIOFUNC);
पूर्ण
EXPORT_SYMBOL(rb532_gpio_set_func);

पूर्णांक __init rb532_gpio_init(व्योम)
अणु
	काष्ठा resource *r;

	r = rb532_gpio_reg0_res;
	rb532_gpio_chip->regbase = ioremap(r->start, resource_size(r));

	अगर (!rb532_gpio_chip->regbase) अणु
		prपूर्णांकk(KERN_ERR "rb532: cannot remap GPIO register 0\n");
		वापस -ENXIO;
	पूर्ण

	/* Register our GPIO chip */
	gpiochip_add_data(&rb532_gpio_chip->chip, rb532_gpio_chip);

	वापस 0;
पूर्ण
arch_initcall(rb532_gpio_init);
