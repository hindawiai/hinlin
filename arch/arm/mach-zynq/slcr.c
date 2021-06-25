<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Xilinx SLCR driver
 *
 * Copyright (c) 2011-2013 Xilinx Inc.
 */

#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk/zynq.h>
#समावेश "common.h"

/* रेजिस्टर offsets */
#घोषणा SLCR_UNLOCK_OFFSET		0x8   /* SCLR unlock रेजिस्टर */
#घोषणा SLCR_PS_RST_CTRL_OFFSET		0x200 /* PS Software Reset Control */
#घोषणा SLCR_A9_CPU_RST_CTRL_OFFSET	0x244 /* CPU Software Reset Control */
#घोषणा SLCR_REBOOT_STATUS_OFFSET	0x258 /* PS Reboot Status */
#घोषणा SLCR_PSS_IDCODE			0x530 /* PS IDCODE */
#घोषणा SLCR_L2C_RAM			0xA1C /* L2C_RAM in AR#54190 */

#घोषणा SLCR_UNLOCK_MAGIC		0xDF0D
#घोषणा SLCR_A9_CPU_CLKSTOP		0x10
#घोषणा SLCR_A9_CPU_RST			0x1
#घोषणा SLCR_PSS_IDCODE_DEVICE_SHIFT	12
#घोषणा SLCR_PSS_IDCODE_DEVICE_MASK	0x1F

अटल व्योम __iomem *zynq_slcr_base;
अटल काष्ठा regmap *zynq_slcr_regmap;

/**
 * zynq_slcr_ग_लिखो - Write to a रेजिस्टर in SLCR block
 *
 * @val:	Value to ग_लिखो to the रेजिस्टर
 * @offset:	Register offset in SLCR block
 *
 * Return:	a negative value on error, 0 on success
 */
अटल पूर्णांक zynq_slcr_ग_लिखो(u32 val, u32 offset)
अणु
	वापस regmap_ग_लिखो(zynq_slcr_regmap, offset, val);
पूर्ण

/**
 * zynq_slcr_पढ़ो - Read a रेजिस्टर in SLCR block
 *
 * @val:	Poपूर्णांकer to value to be पढ़ो from SLCR
 * @offset:	Register offset in SLCR block
 *
 * Return:	a negative value on error, 0 on success
 */
अटल पूर्णांक zynq_slcr_पढ़ो(u32 *val, u32 offset)
अणु
	वापस regmap_पढ़ो(zynq_slcr_regmap, offset, val);
पूर्ण

/**
 * zynq_slcr_unlock - Unlock SLCR रेजिस्टरs
 *
 * Return:	a negative value on error, 0 on success
 */
अटल अंतरभूत पूर्णांक zynq_slcr_unlock(व्योम)
अणु
	zynq_slcr_ग_लिखो(SLCR_UNLOCK_MAGIC, SLCR_UNLOCK_OFFSET);

	वापस 0;
पूर्ण

/**
 * zynq_slcr_get_device_id - Read device code id
 *
 * Return:	Device code id
 */
u32 zynq_slcr_get_device_id(व्योम)
अणु
	u32 val;

	zynq_slcr_पढ़ो(&val, SLCR_PSS_IDCODE);
	val >>= SLCR_PSS_IDCODE_DEVICE_SHIFT;
	val &= SLCR_PSS_IDCODE_DEVICE_MASK;

	वापस val;
पूर्ण

/**
 * zynq_slcr_प्रणाली_restart - Restart the entire प्रणाली.
 *
 * @nb:		Poपूर्णांकer to restart notअगरier block (unused)
 * @action:	Reboot mode (unused)
 * @data:	Restart handler निजी data (unused)
 *
 * Return:	0 always
 */
अटल
पूर्णांक zynq_slcr_प्रणाली_restart(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	u32 reboot;

	/*
	 * Clear 0x0F000000 bits of reboot status रेजिस्टर to workaround
	 * the FSBL not loading the bitstream after soft-reboot
	 * This is a temporary solution until we know more.
	 */
	zynq_slcr_पढ़ो(&reboot, SLCR_REBOOT_STATUS_OFFSET);
	zynq_slcr_ग_लिखो(reboot & 0xF0FFFFFF, SLCR_REBOOT_STATUS_OFFSET);
	zynq_slcr_ग_लिखो(1, SLCR_PS_RST_CTRL_OFFSET);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block zynq_slcr_restart_nb = अणु
	.notअगरier_call	= zynq_slcr_प्रणाली_restart,
	.priority	= 192,
पूर्ण;

/**
 * zynq_slcr_cpu_start - Start cpu
 * @cpu:	cpu number
 */
व्योम zynq_slcr_cpu_start(पूर्णांक cpu)
अणु
	u32 reg;

	zynq_slcr_पढ़ो(&reg, SLCR_A9_CPU_RST_CTRL_OFFSET);
	reg &= ~(SLCR_A9_CPU_RST << cpu);
	zynq_slcr_ग_लिखो(reg, SLCR_A9_CPU_RST_CTRL_OFFSET);
	reg &= ~(SLCR_A9_CPU_CLKSTOP << cpu);
	zynq_slcr_ग_लिखो(reg, SLCR_A9_CPU_RST_CTRL_OFFSET);

	zynq_slcr_cpu_state_ग_लिखो(cpu, false);
पूर्ण

/**
 * zynq_slcr_cpu_stop - Stop cpu
 * @cpu:	cpu number
 */
व्योम zynq_slcr_cpu_stop(पूर्णांक cpu)
अणु
	u32 reg;

	zynq_slcr_पढ़ो(&reg, SLCR_A9_CPU_RST_CTRL_OFFSET);
	reg |= (SLCR_A9_CPU_CLKSTOP | SLCR_A9_CPU_RST) << cpu;
	zynq_slcr_ग_लिखो(reg, SLCR_A9_CPU_RST_CTRL_OFFSET);
पूर्ण

/**
 * zynq_slcr_cpu_state - Read/ग_लिखो cpu state
 * @cpu:	cpu number
 *
 * SLCR_REBOOT_STATUS save upper 2 bits (31/30 cpu states क्रम cpu0 and cpu1)
 * 0 means cpu is running, 1 cpu is going to die.
 *
 * Return: true अगर cpu is running, false अगर cpu is going to die
 */
bool zynq_slcr_cpu_state_पढ़ो(पूर्णांक cpu)
अणु
	u32 state;

	state = पढ़ोl(zynq_slcr_base + SLCR_REBOOT_STATUS_OFFSET);
	state &= 1 << (31 - cpu);

	वापस !state;
पूर्ण

/**
 * zynq_slcr_cpu_state - Read/ग_लिखो cpu state
 * @cpu:	cpu number
 * @die:	cpu state - true अगर cpu is going to die
 *
 * SLCR_REBOOT_STATUS save upper 2 bits (31/30 cpu states क्रम cpu0 and cpu1)
 * 0 means cpu is running, 1 cpu is going to die.
 */
व्योम zynq_slcr_cpu_state_ग_लिखो(पूर्णांक cpu, bool die)
अणु
	u32 state, mask;

	state = पढ़ोl(zynq_slcr_base + SLCR_REBOOT_STATUS_OFFSET);
	mask = 1 << (31 - cpu);
	अगर (die)
		state |= mask;
	अन्यथा
		state &= ~mask;
	ग_लिखोl(state, zynq_slcr_base + SLCR_REBOOT_STATUS_OFFSET);
पूर्ण

/**
 * zynq_early_slcr_init - Early slcr init function
 *
 * Return:	0 on success, negative त्रुटि_सं otherwise.
 *
 * Called very early during boot from platक्रमm code to unlock SLCR.
 */
पूर्णांक __init zynq_early_slcr_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "xlnx,zynq-slcr");
	अगर (!np) अणु
		pr_err("%s: no slcr node found\n", __func__);
		BUG();
	पूर्ण

	zynq_slcr_base = of_iomap(np, 0);
	अगर (!zynq_slcr_base) अणु
		pr_err("%s: Unable to map I/O memory\n", __func__);
		BUG();
	पूर्ण

	np->data = (__क्रमce व्योम *)zynq_slcr_base;

	zynq_slcr_regmap = syscon_regmap_lookup_by_compatible("xlnx,zynq-slcr");
	अगर (IS_ERR(zynq_slcr_regmap)) अणु
		pr_err("%s: failed to find zynq-slcr\n", __func__);
		वापस -ENODEV;
	पूर्ण

	/* unlock the SLCR so that रेजिस्टरs can be changed */
	zynq_slcr_unlock();

	/* See AR#54190 design advisory */
	regmap_update_bits(zynq_slcr_regmap, SLCR_L2C_RAM, 0x70707, 0x20202);

	रेजिस्टर_restart_handler(&zynq_slcr_restart_nb);

	pr_info("%pOFn mapped to %p\n", np, zynq_slcr_base);

	of_node_put(np);

	वापस 0;
पूर्ण
