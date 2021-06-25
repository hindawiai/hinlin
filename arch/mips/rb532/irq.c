<शैली गुरु>
/*
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
 *
 * Copyright 2002 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *		stevel@mvista.com or source@mvista.com
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समयx.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mipsregs.h>

#समावेश <यंत्र/mach-rc32434/irq.h>
#समावेश <यंत्र/mach-rc32434/gpपन.स>

काष्ठा पूर्णांकr_group अणु
	u32 mask;	/* mask of valid bits in pending/mask रेजिस्टरs */
	अस्थिर u32 *base_addr;
पूर्ण;

#घोषणा RC32434_NR_IRQS	 (GROUP4_IRQ_BASE + 32)

#अगर (NR_IRQS < RC32434_NR_IRQS)
#त्रुटि Too little irqs defined. Did you override <यंत्र/irq.h> ?
#पूर्ण_अगर

अटल स्थिर काष्ठा पूर्णांकr_group पूर्णांकr_group[NUM_INTR_GROUPS] = अणु
	अणु
		.mask	= 0x0000efff,
		.base_addr = (u32 *) KSEG1ADDR(IC_GROUP0_PEND + 0 * IC_GROUP_OFFSET)पूर्ण,
	अणु
		.mask	= 0x00001fff,
		.base_addr = (u32 *) KSEG1ADDR(IC_GROUP0_PEND + 1 * IC_GROUP_OFFSET)पूर्ण,
	अणु
		.mask	= 0x00000007,
		.base_addr = (u32 *) KSEG1ADDR(IC_GROUP0_PEND + 2 * IC_GROUP_OFFSET)पूर्ण,
	अणु
		.mask	= 0x0003ffff,
		.base_addr = (u32 *) KSEG1ADDR(IC_GROUP0_PEND + 3 * IC_GROUP_OFFSET)पूर्ण,
	अणु
		.mask	= 0xffffffff,
		.base_addr = (u32 *) KSEG1ADDR(IC_GROUP0_PEND + 4 * IC_GROUP_OFFSET)पूर्ण
पूर्ण;

#घोषणा READ_PEND(base) (*(base))
#घोषणा READ_MASK(base) (*(base + 2))
#घोषणा WRITE_MASK(base, val) (*(base + 2) = (val))

अटल अंतरभूत पूर्णांक irq_to_group(अचिन्हित पूर्णांक irq_nr)
अणु
	वापस (irq_nr - GROUP0_IRQ_BASE) >> 5;
पूर्ण

अटल अंतरभूत पूर्णांक group_to_ip(अचिन्हित पूर्णांक group)
अणु
	वापस group + 2;
पूर्ण

अटल अंतरभूत व्योम enable_local_irq(अचिन्हित पूर्णांक ip)
अणु
	पूर्णांक ipnum = 0x100 << ip;

	set_c0_status(ipnum);
पूर्ण

अटल अंतरभूत व्योम disable_local_irq(अचिन्हित पूर्णांक ip)
अणु
	पूर्णांक ipnum = 0x100 << ip;

	clear_c0_status(ipnum);
पूर्ण

अटल अंतरभूत व्योम ack_local_irq(अचिन्हित पूर्णांक ip)
अणु
	पूर्णांक ipnum = 0x100 << ip;

	clear_c0_cause(ipnum);
पूर्ण

अटल व्योम rb532_enable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक group, पूर्णांकr_bit, irq_nr = d->irq;
	पूर्णांक ip = irq_nr - GROUP0_IRQ_BASE;
	अस्थिर अचिन्हित पूर्णांक *addr;

	अगर (ip < 0)
		enable_local_irq(irq_nr);
	अन्यथा अणु
		group = ip >> 5;

		ip &= (1 << 5) - 1;
		पूर्णांकr_bit = 1 << ip;

		enable_local_irq(group_to_ip(group));

		addr = पूर्णांकr_group[group].base_addr;
		WRITE_MASK(addr, READ_MASK(addr) & ~पूर्णांकr_bit);
	पूर्ण
पूर्ण

अटल व्योम rb532_disable_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक group, पूर्णांकr_bit, mask, irq_nr = d->irq;
	पूर्णांक ip = irq_nr - GROUP0_IRQ_BASE;
	अस्थिर अचिन्हित पूर्णांक *addr;

	अगर (ip < 0) अणु
		disable_local_irq(irq_nr);
	पूर्ण अन्यथा अणु
		group = ip >> 5;

		ip &= (1 << 5) - 1;
		पूर्णांकr_bit = 1 << ip;
		addr = पूर्णांकr_group[group].base_addr;
		mask = READ_MASK(addr);
		mask |= पूर्णांकr_bit;
		WRITE_MASK(addr, mask);

		/* There is a maximum of 14 GPIO पूर्णांकerrupts */
		अगर (group == GPIO_MAPPED_IRQ_GROUP && irq_nr <= (GROUP4_IRQ_BASE + 13))
			rb532_gpio_set_istat(0, irq_nr - GPIO_MAPPED_IRQ_BASE);

		/*
		 * अगर there are no more पूर्णांकerrupts enabled in this
		 * group, disable corresponding IP
		 */
		अगर (mask == पूर्णांकr_group[group].mask)
			disable_local_irq(group_to_ip(group));
	पूर्ण
पूर्ण

अटल व्योम rb532_mask_and_ack_irq(काष्ठा irq_data *d)
अणु
	rb532_disable_irq(d);
	ack_local_irq(group_to_ip(irq_to_group(d->irq)));
पूर्ण

अटल पूर्णांक rb532_set_type(काष्ठा irq_data *d,  अचिन्हित type)
अणु
	पूर्णांक gpio = d->irq - GPIO_MAPPED_IRQ_BASE;
	पूर्णांक group = irq_to_group(d->irq);

	अगर (group != GPIO_MAPPED_IRQ_GROUP || d->irq > (GROUP4_IRQ_BASE + 13))
		वापस (type == IRQ_TYPE_LEVEL_HIGH) ? 0 : -EINVAL;

	चयन (type) अणु
	हाल IRQ_TYPE_LEVEL_HIGH:
		rb532_gpio_set_ilevel(1, gpio);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		rb532_gpio_set_ilevel(0, gpio);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip rc32434_irq_type = अणु
	.name		= "RB532",
	.irq_ack	= rb532_disable_irq,
	.irq_mask	= rb532_disable_irq,
	.irq_mask_ack	= rb532_mask_and_ack_irq,
	.irq_unmask	= rb532_enable_irq,
	.irq_set_type	= rb532_set_type,
पूर्ण;

व्योम __init arch_init_irq(व्योम)
अणु
	पूर्णांक i;

	pr_info("Initializing IRQ's: %d out of %d\n", RC32434_NR_IRQS, NR_IRQS);

	क्रम (i = 0; i < RC32434_NR_IRQS; i++)
		irq_set_chip_and_handler(i, &rc32434_irq_type,
					 handle_level_irq);
पूर्ण

/* Main Interrupt dispatcher */
यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित पूर्णांक ip, pend, group;
	अस्थिर अचिन्हित पूर्णांक *addr;
	अचिन्हित पूर्णांक cp0_cause = पढ़ो_c0_cause() & पढ़ो_c0_status();

	अगर (cp0_cause & CAUSEF_IP7) अणु
		करो_IRQ(7);
	पूर्ण अन्यथा अणु
		ip = (cp0_cause & 0x7c00);
		अगर (ip) अणु
			group = 21 + (fls(ip) - 32);

			addr = पूर्णांकr_group[group].base_addr;

			pend = READ_PEND(addr);
			pend &= ~READ_MASK(addr);	/* only unmasked पूर्णांकerrupts */
			pend = 39 + (fls(pend) - 32);
			करो_IRQ((group << 5) + pend);
		पूर्ण
	पूर्ण
पूर्ण
