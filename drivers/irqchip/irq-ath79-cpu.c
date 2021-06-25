<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Atheros AR71xx/AR724x/AR913x specअगरic पूर्णांकerrupt handling
 *
 *  Copyright (C) 2015 Alban Bedel <albeu@मुक्त.fr>
 *  Copyright (C) 2010-2011 Jaiganesh Narayanan <jnarayanan@atheros.com>
 *  Copyright (C) 2008-2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *  Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 *
 *  Parts of this file are based on Atheros' 2.6.15/2.6.31 BSP
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mach-ath79/ath79.h>

/*
 * The IP2/IP3 lines are tied to a PCI/WMAC/USB device. Drivers क्रम
 * these devices typically allocate coherent DMA memory, however the
 * DMA controller may still have some unsynchronized data in the FIFO.
 * Issue a flush in the handlers to ensure that the driver sees
 * the update.
 *
 * This array map the पूर्णांकerrupt lines to the DDR ग_लिखो buffer channels.
 */

अटल अचिन्हित irq_wb_chan[8] = अणु
	-1, -1, -1, -1, -1, -1, -1, -1,
पूर्ण;

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित दीर्घ pending;
	पूर्णांक irq;

	pending = पढ़ो_c0_status() & पढ़ो_c0_cause() & ST0_IM;

	अगर (!pending) अणु
		spurious_पूर्णांकerrupt();
		वापस;
	पूर्ण

	pending >>= CAUSEB_IP;
	जबतक (pending) अणु
		irq = fls(pending) - 1;
		अगर (irq < ARRAY_SIZE(irq_wb_chan) && irq_wb_chan[irq] != -1)
			ath79_ddr_wb_flush(irq_wb_chan[irq]);
		करो_IRQ(MIPS_CPU_IRQ_BASE + irq);
		pending &= ~BIT(irq);
	पूर्ण
पूर्ण

अटल पूर्णांक __init ar79_cpu_पूर्णांकc_of_init(
	काष्ठा device_node *node, काष्ठा device_node *parent)
अणु
	पूर्णांक err, i, count;

	/* Fill the irq_wb_chan table */
	count = of_count_phandle_with_args(
		node, "qca,ddr-wb-channels", "#qca,ddr-wb-channel-cells");

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा of_phandle_args args;
		u32 irq = i;

		of_property_पढ़ो_u32_index(
			node, "qca,ddr-wb-channel-interrupts", i, &irq);
		अगर (irq >= ARRAY_SIZE(irq_wb_chan))
			जारी;

		err = of_parse_phandle_with_args(
			node, "qca,ddr-wb-channels",
			"#qca,ddr-wb-channel-cells",
			i, &args);
		अगर (err)
			वापस err;

		irq_wb_chan[irq] = args.args[0];
	पूर्ण

	वापस mips_cpu_irq_of_init(node, parent);
पूर्ण
IRQCHIP_DECLARE(ar79_cpu_पूर्णांकc, "qca,ar7100-cpu-intc",
		ar79_cpu_पूर्णांकc_of_init);

व्योम __init ath79_cpu_irq_init(अचिन्हित irq_wb_chan2, अचिन्हित irq_wb_chan3)
अणु
	irq_wb_chan[2] = irq_wb_chan2;
	irq_wb_chan[3] = irq_wb_chan3;
	mips_cpu_irq_init();
पूर्ण
