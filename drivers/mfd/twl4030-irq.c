<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * twl4030-irq.c - TWL4030/TPS659x0 irq support
 *
 * Copyright (C) 2005-2006 Texas Instruments, Inc.
 *
 * Modअगरications to defer पूर्णांकerrupt handling to a kernel thपढ़ो:
 * Copyright (C) 2006 MontaVista Software, Inc.
 *
 * Based on tlv320aic23.c:
 * Copyright (c) by Kai Svahn <kai.svahn@nokia.com>
 *
 * Code cleanup and modअगरications to IRQ handler.
 * by syed khasim <x0khasim@ti.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mfd/twl.h>

#समावेश "twl-core.h"

/*
 * TWL4030 IRQ handling has two stages in hardware, and thus in software.
 * The Primary Interrupt Handler (PIH) stage exposes status bits saying
 * which Secondary Interrupt Handler (SIH) stage is raising an पूर्णांकerrupt.
 * SIH modules are more traditional IRQ components, which support per-IRQ
 * enable/disable and trigger controls; they करो most of the work.
 *
 * These chips are deचिन्हित to support IRQ handling from two dअगरferent
 * I2C masters.  Each has a dedicated IRQ line, and dedicated IRQ status
 * and mask रेजिस्टरs in the PIH and SIH modules.
 *
 * We set up IRQs starting at a platक्रमm-specअगरied base, always starting
 * with PIH and the SIH क्रम PWR_INT and then usually adding GPIO:
 *	base + 0  .. base + 7	PIH
 *	base + 8  .. base + 15	SIH क्रम PWR_INT
 *	base + 16 .. base + 33	SIH क्रम GPIO
 */
#घोषणा TWL4030_CORE_NR_IRQS	8
#घोषणा TWL4030_PWR_NR_IRQS	8

/* PIH रेजिस्टर offsets */
#घोषणा REG_PIH_ISR_P1			0x01
#घोषणा REG_PIH_ISR_P2			0x02
#घोषणा REG_PIH_SIR			0x03	/* क्रम testing */

/* Linux could (eventually) use either IRQ line */
अटल पूर्णांक irq_line;

काष्ठा sih अणु
	अक्षर	name[8];
	u8	module;			/* module id */
	u8	control_offset;		/* क्रम SIH_CTRL */
	bool	set_cor;

	u8	bits;			/* valid in isr/imr */
	u8	bytes_ixr;		/* bytelen of ISR/IMR/SIR */

	u8	edr_offset;
	u8	bytes_edr;		/* bytelen of EDR */

	u8	irq_lines;		/* number of supported irq lines */

	/* SIR ignored -- set पूर्णांकerrupt, क्रम testing only */
	काष्ठा sih_irq_data अणु
		u8	isr_offset;
		u8	imr_offset;
	पूर्ण mask[2];
	/* + 2 bytes padding */
पूर्ण;

अटल स्थिर काष्ठा sih *sih_modules;
अटल पूर्णांक nr_sih_modules;

#घोषणा SIH_INITIALIZER(modname, nbits) \
	.module		= TWL4030_MODULE_ ## modname, \
	.control_offset = TWL4030_ ## modname ## _SIH_CTRL, \
	.bits		= nbits, \
	.bytes_ixr	= DIV_ROUND_UP(nbits, 8), \
	.edr_offset	= TWL4030_ ## modname ## _EDR, \
	.bytes_edr	= DIV_ROUND_UP((2*(nbits)), 8), \
	.irq_lines	= 2, \
	.mask = अणु अणु \
		.isr_offset	= TWL4030_ ## modname ## _ISR1, \
		.imr_offset	= TWL4030_ ## modname ## _IMR1, \
	पूर्ण, \
	अणु \
		.isr_offset	= TWL4030_ ## modname ## _ISR2, \
		.imr_offset	= TWL4030_ ## modname ## _IMR2, \
	पूर्ण, पूर्ण,

/* रेजिस्टर naming policies are inconsistent ... */
#घोषणा TWL4030_INT_PWR_EDR		TWL4030_INT_PWR_EDR1
#घोषणा TWL4030_MODULE_KEYPAD_KEYP	TWL4030_MODULE_KEYPAD
#घोषणा TWL4030_MODULE_INT_PWR		TWL4030_MODULE_INT


/*
 * Order in this table matches order in PIH_ISR.  That is,
 * BIT(n) in PIH_ISR is sih_modules[n].
 */
/* sih_modules_twl4030 is used both in twl4030 and twl5030 */
अटल स्थिर काष्ठा sih sih_modules_twl4030[6] = अणु
	[0] = अणु
		.name		= "gpio",
		.module		= TWL4030_MODULE_GPIO,
		.control_offset	= REG_GPIO_SIH_CTRL,
		.set_cor	= true,
		.bits		= TWL4030_GPIO_MAX,
		.bytes_ixr	= 3,
		/* Note: *all* of these IRQs शेष to no-trigger */
		.edr_offset	= REG_GPIO_EDR1,
		.bytes_edr	= 5,
		.irq_lines	= 2,
		.mask = अणु अणु
			.isr_offset	= REG_GPIO_ISR1A,
			.imr_offset	= REG_GPIO_IMR1A,
		पूर्ण, अणु
			.isr_offset	= REG_GPIO_ISR1B,
			.imr_offset	= REG_GPIO_IMR1B,
		पूर्ण, पूर्ण,
	पूर्ण,
	[1] = अणु
		.name		= "keypad",
		.set_cor	= true,
		SIH_INITIALIZER(KEYPAD_KEYP, 4)
	पूर्ण,
	[2] = अणु
		.name		= "bci",
		.module		= TWL4030_MODULE_INTERRUPTS,
		.control_offset	= TWL4030_INTERRUPTS_BCISIHCTRL,
		.set_cor	= true,
		.bits		= 12,
		.bytes_ixr	= 2,
		.edr_offset	= TWL4030_INTERRUPTS_BCIEDR1,
		/* Note: most of these IRQs शेष to no-trigger */
		.bytes_edr	= 3,
		.irq_lines	= 2,
		.mask = अणु अणु
			.isr_offset	= TWL4030_INTERRUPTS_BCIISR1A,
			.imr_offset	= TWL4030_INTERRUPTS_BCIIMR1A,
		पूर्ण, अणु
			.isr_offset	= TWL4030_INTERRUPTS_BCIISR1B,
			.imr_offset	= TWL4030_INTERRUPTS_BCIIMR1B,
		पूर्ण, पूर्ण,
	पूर्ण,
	[3] = अणु
		.name		= "madc",
		SIH_INITIALIZER(MADC, 4)
	पूर्ण,
	[4] = अणु
		/* USB करोesn't use the same SIH organization */
		.name		= "usb",
	पूर्ण,
	[5] = अणु
		.name		= "power",
		.set_cor	= true,
		SIH_INITIALIZER(INT_PWR, 8)
	पूर्ण,
		/* there are no SIH modules #6 or #7 ... */
पूर्ण;

अटल स्थिर काष्ठा sih sih_modules_twl5031[8] = अणु
	[0] = अणु
		.name		= "gpio",
		.module		= TWL4030_MODULE_GPIO,
		.control_offset	= REG_GPIO_SIH_CTRL,
		.set_cor	= true,
		.bits		= TWL4030_GPIO_MAX,
		.bytes_ixr	= 3,
		/* Note: *all* of these IRQs शेष to no-trigger */
		.edr_offset	= REG_GPIO_EDR1,
		.bytes_edr	= 5,
		.irq_lines	= 2,
		.mask = अणु अणु
			.isr_offset	= REG_GPIO_ISR1A,
			.imr_offset	= REG_GPIO_IMR1A,
		पूर्ण, अणु
			.isr_offset	= REG_GPIO_ISR1B,
			.imr_offset	= REG_GPIO_IMR1B,
		पूर्ण, पूर्ण,
	पूर्ण,
	[1] = अणु
		.name		= "keypad",
		.set_cor	= true,
		SIH_INITIALIZER(KEYPAD_KEYP, 4)
	पूर्ण,
	[2] = अणु
		.name		= "bci",
		.module		= TWL5031_MODULE_INTERRUPTS,
		.control_offset	= TWL5031_INTERRUPTS_BCISIHCTRL,
		.bits		= 7,
		.bytes_ixr	= 1,
		.edr_offset	= TWL5031_INTERRUPTS_BCIEDR1,
		/* Note: most of these IRQs शेष to no-trigger */
		.bytes_edr	= 2,
		.irq_lines	= 2,
		.mask = अणु अणु
			.isr_offset	= TWL5031_INTERRUPTS_BCIISR1,
			.imr_offset	= TWL5031_INTERRUPTS_BCIIMR1,
		पूर्ण, अणु
			.isr_offset	= TWL5031_INTERRUPTS_BCIISR2,
			.imr_offset	= TWL5031_INTERRUPTS_BCIIMR2,
		पूर्ण, पूर्ण,
	पूर्ण,
	[3] = अणु
		.name		= "madc",
		SIH_INITIALIZER(MADC, 4)
	पूर्ण,
	[4] = अणु
		/* USB करोesn't use the same SIH organization */
		.name		= "usb",
	पूर्ण,
	[5] = अणु
		.name		= "power",
		.set_cor	= true,
		SIH_INITIALIZER(INT_PWR, 8)
	पूर्ण,
	[6] = अणु
		/*
		 * ECI/DBI करोesn't use the same SIH organization.
		 * For example, it supports only one पूर्णांकerrupt output line.
		 * That is, the पूर्णांकerrupts are seen on both INT1 and INT2 lines.
		 */
		.name		= "eci_dbi",
		.module		= TWL5031_MODULE_ACCESSORY,
		.bits		= 9,
		.bytes_ixr	= 2,
		.irq_lines	= 1,
		.mask = अणु अणु
			.isr_offset	= TWL5031_ACIIDR_LSB,
			.imr_offset	= TWL5031_ACIIMR_LSB,
		पूर्ण, पूर्ण,

	पूर्ण,
	[7] = अणु
		/* Audio accessory */
		.name		= "audio",
		.module		= TWL5031_MODULE_ACCESSORY,
		.control_offset	= TWL5031_ACCSIHCTRL,
		.bits		= 2,
		.bytes_ixr	= 1,
		.edr_offset	= TWL5031_ACCEDR1,
		/* Note: most of these IRQs शेष to no-trigger */
		.bytes_edr	= 1,
		.irq_lines	= 2,
		.mask = अणु अणु
			.isr_offset	= TWL5031_ACCISR1,
			.imr_offset	= TWL5031_ACCIMR1,
		पूर्ण, अणु
			.isr_offset	= TWL5031_ACCISR2,
			.imr_offset	= TWL5031_ACCIMR2,
		पूर्ण, पूर्ण,
	पूर्ण,
पूर्ण;

#अघोषित TWL4030_MODULE_KEYPAD_KEYP
#अघोषित TWL4030_MODULE_INT_PWR
#अघोषित TWL4030_INT_PWR_EDR

/*----------------------------------------------------------------------*/

अटल अचिन्हित twl4030_irq_base;

/*
 * handle_twl4030_pih() is the desc->handle method क्रम the twl4030 पूर्णांकerrupt.
 * This is a chained पूर्णांकerrupt, so there is no desc->action method क्रम it.
 * Now we need to query the पूर्णांकerrupt controller in the twl4030 to determine
 * which module is generating the पूर्णांकerrupt request.  However, we can't करो i2c
 * transactions in पूर्णांकerrupt context, so we must defer that work to a kernel
 * thपढ़ो.  All we करो here is acknowledge and mask the पूर्णांकerrupt and wakeup
 * the kernel thपढ़ो.
 */
अटल irqवापस_t handle_twl4030_pih(पूर्णांक irq, व्योम *devid)
अणु
	irqवापस_t	ret;
	u8		pih_isr;

	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_PIH, &pih_isr,
			      REG_PIH_ISR_P1);
	अगर (ret) अणु
		pr_warn("twl4030: I2C error %d reading PIH ISR\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	जबतक (pih_isr) अणु
		अचिन्हित दीर्घ	pending = __ffs(pih_isr);
		अचिन्हित पूर्णांक	irq;

		pih_isr &= ~BIT(pending);
		irq = pending + twl4030_irq_base;
		handle_nested_irq(irq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * twl4030_init_sih_modules() ... start from a known state where no
 * IRQs will be coming in, and where we can quickly enable them then
 * handle them as they arrive.  Mask all IRQs: maybe init SIH_CTRL.
 *
 * NOTE:  we करोn't touch EDR रेजिस्टरs here; they stay with hardware
 * शेषs or whatever the last value was.  Note that when both EDR
 * bits क्रम an IRQ are clear, that's as अगर its IMR bit is set...
 */
अटल पूर्णांक twl4030_init_sih_modules(अचिन्हित line)
अणु
	स्थिर काष्ठा sih *sih;
	u8 buf[4];
	पूर्णांक i;
	पूर्णांक status;

	/* line 0 == पूर्णांक1_n संकेत; line 1 == पूर्णांक2_n संकेत */
	अगर (line > 1)
		वापस -EINVAL;

	irq_line = line;

	/* disable all पूर्णांकerrupts on our line */
	स_रखो(buf, 0xff, माप(buf));
	sih = sih_modules;
	क्रम (i = 0; i < nr_sih_modules; i++, sih++) अणु
		/* skip USB -- it's funky */
		अगर (!sih->bytes_ixr)
			जारी;

		/* Not all the SIH modules support multiple पूर्णांकerrupt lines */
		अगर (sih->irq_lines <= line)
			जारी;

		status = twl_i2c_ग_लिखो(sih->module, buf,
				sih->mask[line].imr_offset, sih->bytes_ixr);
		अगर (status < 0)
			pr_err("twl4030: err %d initializing %s %s\n",
					status, sih->name, "IMR");

		/*
		 * Maybe disable "exclusive" mode; buffer second pending irq;
		 * set Clear-On-Read (COR) bit.
		 *
		 * NOTE that someबार COR polarity is करोcumented as being
		 * inverted:  क्रम MADC, COR=1 means "clear on write".
		 * And क्रम PWR_INT it's not करोcumented...
		 */
		अगर (sih->set_cor) अणु
			status = twl_i2c_ग_लिखो_u8(sih->module,
					TWL4030_SIH_CTRL_COR_MASK,
					sih->control_offset);
			अगर (status < 0)
				pr_err("twl4030: err %d initializing %s %s\n",
						status, sih->name, "SIH_CTRL");
		पूर्ण
	पूर्ण

	sih = sih_modules;
	क्रम (i = 0; i < nr_sih_modules; i++, sih++) अणु
		u8 rxbuf[4];
		पूर्णांक j;

		/* skip USB */
		अगर (!sih->bytes_ixr)
			जारी;

		/* Not all the SIH modules support multiple पूर्णांकerrupt lines */
		अगर (sih->irq_lines <= line)
			जारी;

		/*
		 * Clear pending पूर्णांकerrupt status.  Either the पढ़ो was
		 * enough, or we need to ग_लिखो those bits.  Repeat, in
		 * हाल an IRQ is pending (PENDDIS=0) ... that's not
		 * uncommon with PWR_INT.PWRON.
		 */
		क्रम (j = 0; j < 2; j++) अणु
			status = twl_i2c_पढ़ो(sih->module, rxbuf,
				sih->mask[line].isr_offset, sih->bytes_ixr);
			अगर (status < 0)
				pr_warn("twl4030: err %d initializing %s %s\n",
					status, sih->name, "ISR");

			अगर (!sih->set_cor) अणु
				status = twl_i2c_ग_लिखो(sih->module, buf,
					sih->mask[line].isr_offset,
					sih->bytes_ixr);
				अगर (status < 0)
					pr_warn("twl4030: write failed: %d\n",
						status);
			पूर्ण
			/*
			 * अन्यथा COR=1 means पढ़ो sufficed.
			 * (क्रम most SIH modules...)
			 */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम activate_irq(पूर्णांक irq)
अणु
	irq_clear_status_flags(irq, IRQ_NOREQUEST | IRQ_NOPROBE);
पूर्ण

/*----------------------------------------------------------------------*/

काष्ठा sih_agent अणु
	पूर्णांक			irq_base;
	स्थिर काष्ठा sih	*sih;

	u32			imr;
	bool			imr_change_pending;

	u32			edge_change;

	काष्ठा mutex		irq_lock;
	अक्षर			*irq_name;
पूर्ण;

/*----------------------------------------------------------------------*/

/*
 * All irq_chip methods get issued from code holding irq_desc[irq].lock,
 * which can't perक्रमm the underlying I2C operations (because they sleep).
 * So we must hand them off to a thपढ़ो (workqueue) and cope with asynch
 * completion, potentially including some re-ordering, of these requests.
 */

अटल व्योम twl4030_sih_mask(काष्ठा irq_data *data)
अणु
	काष्ठा sih_agent *agent = irq_data_get_irq_chip_data(data);

	agent->imr |= BIT(data->irq - agent->irq_base);
	agent->imr_change_pending = true;
पूर्ण

अटल व्योम twl4030_sih_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा sih_agent *agent = irq_data_get_irq_chip_data(data);

	agent->imr &= ~BIT(data->irq - agent->irq_base);
	agent->imr_change_pending = true;
पूर्ण

अटल पूर्णांक twl4030_sih_set_type(काष्ठा irq_data *data, अचिन्हित trigger)
अणु
	काष्ठा sih_agent *agent = irq_data_get_irq_chip_data(data);

	अगर (trigger & ~(IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		वापस -EINVAL;

	अगर (irqd_get_trigger_type(data) != trigger)
		agent->edge_change |= BIT(data->irq - agent->irq_base);

	वापस 0;
पूर्ण

अटल व्योम twl4030_sih_bus_lock(काष्ठा irq_data *data)
अणु
	काष्ठा sih_agent	*agent = irq_data_get_irq_chip_data(data);

	mutex_lock(&agent->irq_lock);
पूर्ण

अटल व्योम twl4030_sih_bus_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा sih_agent	*agent = irq_data_get_irq_chip_data(data);
	स्थिर काष्ठा sih	*sih = agent->sih;
	पूर्णांक			status;

	अगर (agent->imr_change_pending) अणु
		जोड़ अणु
			__le32	word;
			u8	bytes[4];
		पूर्ण imr;

		/* byte[0] माला_लो overwritten as we ग_लिखो ... */
		imr.word = cpu_to_le32(agent->imr);
		agent->imr_change_pending = false;

		/* ग_लिखो the whole mask ... simpler than subsetting it */
		status = twl_i2c_ग_लिखो(sih->module, imr.bytes,
				sih->mask[irq_line].imr_offset,
				sih->bytes_ixr);
		अगर (status)
			pr_err("twl4030: %s, %s --> %d\n", __func__,
					"write", status);
	पूर्ण

	अगर (agent->edge_change) अणु
		u32		edge_change;
		u8		bytes[6];

		edge_change = agent->edge_change;
		agent->edge_change = 0;

		/*
		 * Read, reserving first byte क्रम ग_लिखो scratch.  Yes, this
		 * could be cached क्रम some speedup ... but be careful about
		 * any processor on the other IRQ line, EDR रेजिस्टरs are
		 * shared.
		 */
		status = twl_i2c_पढ़ो(sih->module, bytes,
				sih->edr_offset, sih->bytes_edr);
		अगर (status) अणु
			pr_err("twl4030: %s, %s --> %d\n", __func__,
					"read", status);
			वापस;
		पूर्ण

		/* Modअगरy only the bits we know must change */
		जबतक (edge_change) अणु
			पूर्णांक		i = fls(edge_change) - 1;
			पूर्णांक		byte = i >> 2;
			पूर्णांक		off = (i & 0x3) * 2;
			अचिन्हित पूर्णांक	type;

			bytes[byte] &= ~(0x03 << off);

			type = irq_get_trigger_type(i + agent->irq_base);
			अगर (type & IRQ_TYPE_EDGE_RISING)
				bytes[byte] |= BIT(off + 1);
			अगर (type & IRQ_TYPE_EDGE_FALLING)
				bytes[byte] |= BIT(off + 0);

			edge_change &= ~BIT(i);
		पूर्ण

		/* Write */
		status = twl_i2c_ग_लिखो(sih->module, bytes,
				sih->edr_offset, sih->bytes_edr);
		अगर (status)
			pr_err("twl4030: %s, %s --> %d\n", __func__,
					"write", status);
	पूर्ण

	mutex_unlock(&agent->irq_lock);
पूर्ण

अटल काष्ठा irq_chip twl4030_sih_irq_chip = अणु
	.name		= "twl4030",
	.irq_mask	= twl4030_sih_mask,
	.irq_unmask	= twl4030_sih_unmask,
	.irq_set_type	= twl4030_sih_set_type,
	.irq_bus_lock	= twl4030_sih_bus_lock,
	.irq_bus_sync_unlock = twl4030_sih_bus_sync_unlock,
	.flags		= IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल अंतरभूत पूर्णांक sih_पढ़ो_isr(स्थिर काष्ठा sih *sih)
अणु
	पूर्णांक status;
	जोड़ अणु
		u8 bytes[4];
		__le32 word;
	पूर्ण isr;

	/* FIXME need retry-on-error ... */

	isr.word = 0;
	status = twl_i2c_पढ़ो(sih->module, isr.bytes,
			sih->mask[irq_line].isr_offset, sih->bytes_ixr);

	वापस (status < 0) ? status : le32_to_cpu(isr.word);
पूर्ण

/*
 * Generic handler क्रम SIH पूर्णांकerrupts ... we "know" this is called
 * in task context, with IRQs enabled.
 */
अटल irqवापस_t handle_twl4030_sih(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sih_agent *agent = irq_get_handler_data(irq);
	स्थिर काष्ठा sih *sih = agent->sih;
	पूर्णांक isr;

	/* पढ़ोing ISR acks the IRQs, using clear-on-पढ़ो mode */
	isr = sih_पढ़ो_isr(sih);

	अगर (isr < 0) अणु
		pr_err("twl4030: %s SIH, read ISR error %d\n",
			sih->name, isr);
		/* REVISIT:  recover; eventually mask it all, etc */
		वापस IRQ_HANDLED;
	पूर्ण

	जबतक (isr) अणु
		irq = fls(isr);
		irq--;
		isr &= ~BIT(irq);

		अगर (irq < sih->bits)
			handle_nested_irq(agent->irq_base + irq);
		अन्यथा
			pr_err("twl4030: %s SIH, invalid ISR bit %d\n",
				sih->name, irq);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/* वापसs the first IRQ used by this SIH bank, or negative त्रुटि_सं */
पूर्णांक twl4030_sih_setup(काष्ठा device *dev, पूर्णांक module, पूर्णांक irq_base)
अणु
	पूर्णांक			sih_mod;
	स्थिर काष्ठा sih	*sih = शून्य;
	काष्ठा sih_agent	*agent;
	पूर्णांक			i, irq;
	पूर्णांक			status = -EINVAL;

	/* only support modules with standard clear-on-पढ़ो क्रम now */
	क्रम (sih_mod = 0, sih = sih_modules; sih_mod < nr_sih_modules;
			sih_mod++, sih++) अणु
		अगर (sih->module == module && sih->set_cor) अणु
			status = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status < 0) अणु
		dev_err(dev, "module to setup SIH for not found\n");
		वापस status;
	पूर्ण

	agent = kzalloc(माप(*agent), GFP_KERNEL);
	अगर (!agent)
		वापस -ENOMEM;

	agent->irq_base = irq_base;
	agent->sih = sih;
	agent->imr = ~0;
	mutex_init(&agent->irq_lock);

	क्रम (i = 0; i < sih->bits; i++) अणु
		irq = irq_base + i;

		irq_set_chip_data(irq, agent);
		irq_set_chip_and_handler(irq, &twl4030_sih_irq_chip,
					 handle_edge_irq);
		irq_set_nested_thपढ़ो(irq, 1);
		activate_irq(irq);
	पूर्ण

	/* replace generic PIH handler (handle_simple_irq) */
	irq = sih_mod + twl4030_irq_base;
	irq_set_handler_data(irq, agent);
	agent->irq_name = kaप्र_लिखो(GFP_KERNEL, "twl4030_%s", sih->name);
	status = request_thपढ़ोed_irq(irq, शून्य, handle_twl4030_sih,
				      IRQF_EARLY_RESUME | IRQF_ONESHOT,
				      agent->irq_name ?: sih->name, शून्य);

	dev_info(dev, "%s (irq %d) chaining IRQs %d..%d\n", sih->name,
			irq, irq_base, irq_base + i - 1);

	वापस status < 0 ? status : irq_base;
पूर्ण

/* FIXME need a call to reverse twl4030_sih_setup() ... */

/*----------------------------------------------------------------------*/

/* FIXME pass in which पूर्णांकerrupt line we'll use ... */
#घोषणा twl_irq_line	0

पूर्णांक twl4030_init_irq(काष्ठा device *dev, पूर्णांक irq_num)
अणु
	अटल काष्ठा irq_chip	twl4030_irq_chip;
	पूर्णांक			status, i;
	पूर्णांक			irq_base, irq_end, nr_irqs;
	काष्ठा			device_node *node = dev->of_node;

	/*
	 * TWL core and pwr पूर्णांकerrupts must be contiguous because
	 * the hwirqs numbers are defined contiguously from 1 to 15.
	 * Create only one करोमुख्य क्रम both.
	 */
	nr_irqs = TWL4030_PWR_NR_IRQS + TWL4030_CORE_NR_IRQS;

	irq_base = irq_alloc_descs(-1, 0, nr_irqs, 0);
	अगर (irq_base < 0) अणु
		dev_err(dev, "Fail to allocate IRQ descs\n");
		वापस irq_base;
	पूर्ण

	irq_करोमुख्य_add_legacy(node, nr_irqs, irq_base, 0,
			      &irq_करोमुख्य_simple_ops, शून्य);

	irq_end = irq_base + TWL4030_CORE_NR_IRQS;

	/*
	 * Mask and clear all TWL4030 पूर्णांकerrupts since initially we करो
	 * not have any TWL4030 module पूर्णांकerrupt handlers present
	 */
	status = twl4030_init_sih_modules(twl_irq_line);
	अगर (status < 0)
		वापस status;

	twl4030_irq_base = irq_base;

	/*
	 * Install an irq handler क्रम each of the SIH modules;
	 * clone dummy irq_chip since PIH can't *करो* anything
	 */
	twl4030_irq_chip = dummy_irq_chip;
	twl4030_irq_chip.name = "twl4030";

	twl4030_sih_irq_chip.irq_ack = dummy_irq_chip.irq_ack;

	क्रम (i = irq_base; i < irq_end; i++) अणु
		irq_set_chip_and_handler(i, &twl4030_irq_chip,
					 handle_simple_irq);
		irq_set_nested_thपढ़ो(i, 1);
		activate_irq(i);
	पूर्ण

	dev_info(dev, "%s (irq %d) chaining IRQs %d..%d\n", "PIH",
			irq_num, irq_base, irq_end);

	/* ... and the PWR_INT module ... */
	status = twl4030_sih_setup(dev, TWL4030_MODULE_INT, irq_end);
	अगर (status < 0) अणु
		dev_err(dev, "sih_setup PWR INT --> %d\n", status);
		जाओ fail;
	पूर्ण

	/* install an irq handler to demultiplex the TWL4030 पूर्णांकerrupt */
	status = request_thपढ़ोed_irq(irq_num, शून्य, handle_twl4030_pih,
				      IRQF_ONESHOT,
				      "TWL4030-PIH", शून्य);
	अगर (status < 0) अणु
		dev_err(dev, "could not claim irq%d: %d\n", irq_num, status);
		जाओ fail_rqirq;
	पूर्ण
	enable_irq_wake(irq_num);

	वापस irq_base;
fail_rqirq:
	/* clean up twl4030_sih_setup */
fail:
	क्रम (i = irq_base; i < irq_end; i++) अणु
		irq_set_nested_thपढ़ो(i, 0);
		irq_set_chip_and_handler(i, शून्य, शून्य);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक twl4030_निकास_irq(व्योम)
अणु
	/* FIXME unकरो twl_init_irq() */
	अगर (twl4030_irq_base) अणु
		pr_err("twl4030: can't yet clean up IRQs?\n");
		वापस -ENOSYS;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक twl4030_init_chip_irq(स्थिर अक्षर *chip)
अणु
	अगर (!म_भेद(chip, "twl5031")) अणु
		sih_modules = sih_modules_twl5031;
		nr_sih_modules = ARRAY_SIZE(sih_modules_twl5031);
	पूर्ण अन्यथा अणु
		sih_modules = sih_modules_twl4030;
		nr_sih_modules = ARRAY_SIZE(sih_modules_twl4030);
	पूर्ण

	वापस 0;
पूर्ण
