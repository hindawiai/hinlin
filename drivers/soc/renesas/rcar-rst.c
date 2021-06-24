<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car Gen1 RESET/WDT, R-Car Gen2, Gen3, and RZ/G RST Driver
 *
 * Copyright (C) 2016 Glider bvba
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/soc/renesas/rcar-rst.h>

#घोषणा WDTRSTCR_RESET		0xA55A0002
#घोषणा WDTRSTCR		0x0054

अटल पूर्णांक rcar_rst_enable_wdt_reset(व्योम __iomem *base)
अणु
	ioग_लिखो32(WDTRSTCR_RESET, base + WDTRSTCR);
	वापस 0;
पूर्ण

काष्ठा rst_config अणु
	अचिन्हित पूर्णांक modemr;		/* Mode Monitoring Register Offset */
	पूर्णांक (*configure)(व्योम __iomem *base);	/* Platक्रमm specअगरic config */
पूर्ण;

अटल स्थिर काष्ठा rst_config rcar_rst_gen1 __initस्थिर = अणु
	.modemr = 0x20,
पूर्ण;

अटल स्थिर काष्ठा rst_config rcar_rst_gen2 __initस्थिर = अणु
	.modemr = 0x60,
	.configure = rcar_rst_enable_wdt_reset,
पूर्ण;

अटल स्थिर काष्ठा rst_config rcar_rst_gen3 __initस्थिर = अणु
	.modemr = 0x60,
पूर्ण;

अटल स्थिर काष्ठा rst_config rcar_rst_r8a779a0 __initस्थिर = अणु
	.modemr = 0x00,		/* MODEMR0 and it has CPG related bits */
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_rst_matches[] __initस्थिर = अणु
	/* RZ/G1 is handled like R-Car Gen2 */
	अणु .compatible = "renesas,r8a7742-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a7743-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a7744-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a7745-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a77470-rst", .data = &rcar_rst_gen2 पूर्ण,
	/* RZ/G2 is handled like R-Car Gen3 */
	अणु .compatible = "renesas,r8a774a1-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a774b1-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a774c0-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a774e1-rst", .data = &rcar_rst_gen3 पूर्ण,
	/* R-Car Gen1 */
	अणु .compatible = "renesas,r8a7778-reset-wdt", .data = &rcar_rst_gen1 पूर्ण,
	अणु .compatible = "renesas,r8a7779-reset-wdt", .data = &rcar_rst_gen1 पूर्ण,
	/* R-Car Gen2 */
	अणु .compatible = "renesas,r8a7790-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a7791-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a7792-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a7793-rst", .data = &rcar_rst_gen2 पूर्ण,
	अणु .compatible = "renesas,r8a7794-rst", .data = &rcar_rst_gen2 पूर्ण,
	/* R-Car Gen3 */
	अणु .compatible = "renesas,r8a7795-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a7796-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a77961-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a77965-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a77970-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a77980-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a77990-rst", .data = &rcar_rst_gen3 पूर्ण,
	अणु .compatible = "renesas,r8a77995-rst", .data = &rcar_rst_gen3 पूर्ण,
	/* R-Car V3U */
	अणु .compatible = "renesas,r8a779a0-rst", .data = &rcar_rst_r8a779a0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम __iomem *rcar_rst_base __initdata;
अटल u32 saved_mode __initdata;

अटल पूर्णांक __init rcar_rst_init(व्योम)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा rst_config *cfg;
	काष्ठा device_node *np;
	व्योम __iomem *base;
	पूर्णांक error = 0;

	np = of_find_matching_node_and_match(शून्य, rcar_rst_matches, &match);
	अगर (!np)
		वापस -ENODEV;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_warn("%pOF: Cannot map regs\n", np);
		error = -ENOMEM;
		जाओ out_put;
	पूर्ण

	rcar_rst_base = base;
	cfg = match->data;
	saved_mode = ioपढ़ो32(base + cfg->modemr);
	अगर (cfg->configure) अणु
		error = cfg->configure(base);
		अगर (error) अणु
			pr_warn("%pOF: Cannot run SoC specific configuration\n",
				np);
			जाओ out_put;
		पूर्ण
	पूर्ण

	pr_debug("%pOF: MODE = 0x%08x\n", np, saved_mode);

out_put:
	of_node_put(np);
	वापस error;
पूर्ण

पूर्णांक __init rcar_rst_पढ़ो_mode_pins(u32 *mode)
अणु
	पूर्णांक error;

	अगर (!rcar_rst_base) अणु
		error = rcar_rst_init();
		अगर (error)
			वापस error;
	पूर्ण

	*mode = saved_mode;
	वापस 0;
पूर्ण
