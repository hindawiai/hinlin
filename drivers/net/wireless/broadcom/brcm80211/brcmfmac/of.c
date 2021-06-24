<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2014 Broadcom Corporation
 */
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>

#समावेश <defs.h>
#समावेश "debug.h"
#समावेश "core.h"
#समावेश "common.h"
#समावेश "of.h"

व्योम brcmf_of_probe(काष्ठा device *dev, क्रमागत brcmf_bus_type bus_type,
		    काष्ठा brcmf_mp_device *settings)
अणु
	काष्ठा brcmfmac_sdio_pd *sdio = &settings->bus.sdio;
	काष्ठा device_node *root, *np = dev->of_node;
	पूर्णांक irq;
	u32 irqf;
	u32 val;

	/* Set board-type to the first string of the machine compatible prop */
	root = of_find_node_by_path("/");
	अगर (root) अणु
		पूर्णांक i, len;
		अक्षर *board_type;
		स्थिर अक्षर *पंचांगp;

		of_property_पढ़ो_string_index(root, "compatible", 0, &पंचांगp);

		/* get rid of '/' in the compatible string to be able to find the FW */
		len = म_माप(पंचांगp) + 1;
		board_type = devm_kzalloc(dev, len, GFP_KERNEL);
		strscpy(board_type, पंचांगp, len);
		क्रम (i = 0; i < board_type[i]; i++) अणु
			अगर (board_type[i] == '/')
				board_type[i] = '-';
		पूर्ण
		settings->board_type = board_type;

		of_node_put(root);
	पूर्ण

	अगर (!np || bus_type != BRCMF_BUSTYPE_SDIO ||
	    !of_device_is_compatible(np, "brcm,bcm4329-fmac"))
		वापस;

	अगर (of_property_पढ़ो_u32(np, "brcm,drive-strength", &val) == 0)
		sdio->drive_strength = val;

	/* make sure there are पूर्णांकerrupts defined in the node */
	अगर (!of_find_property(np, "interrupts", शून्य))
		वापस;

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		brcmf_err("interrupt could not be mapped\n");
		वापस;
	पूर्ण
	irqf = irqd_get_trigger_type(irq_get_irq_data(irq));

	sdio->oob_irq_supported = true;
	sdio->oob_irq_nr = irq;
	sdio->oob_irq_flags = irqf;
पूर्ण
