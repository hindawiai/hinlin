<शैली गुरु>
/*
 * sh7724 MMCIF loader
 *
 * Copyright (C) 2010 Magnus Damm
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/mmc/sh_mmcअगर.h>
#समावेश <mach/romimage.h>

#घोषणा MMCIF_BASE      (व्योम __iomem *)0xa4ca0000

#घोषणा MSTPCR2		0xa4150038
#घोषणा PTWCR		0xa4050146
#घोषणा PTXCR		0xa4050148
#घोषणा PSELA		0xa405014e
#घोषणा PSELE		0xa4050156
#घोषणा HIZCRC		0xa405015c
#घोषणा DRVCRA		0xa405018a

क्रमागत अणु
	MMCIF_PROGRESS_ENTER,
	MMCIF_PROGRESS_INIT,
	MMCIF_PROGRESS_LOAD,
	MMCIF_PROGRESS_DONE
पूर्ण;

/* SH7724 specअगरic MMCIF loader
 *
 * loads the romImage from an MMC card starting from block 512
 * use the following line to ग_लिखो the romImage to an MMC card
 * # dd अगर=arch/sh/boot/romImage of=/dev/sdx bs=512 seek=512
 */
यंत्रlinkage व्योम mmcअगर_loader(अचिन्हित अक्षर *buf, अचिन्हित दीर्घ no_bytes)
अणु
	mmcअगर_update_progress(MMCIF_PROGRESS_ENTER);

	/* enable घड़ी to the MMCIF hardware block */
	__raw_ग_लिखोl(__raw_पढ़ोl(MSTPCR2) & ~0x20000000, MSTPCR2);

	/* setup pins D7-D0 */
	__raw_ग_लिखोw(0x0000, PTWCR);

	/* setup pins MMC_CLK, MMC_CMD */
	__raw_ग_लिखोw(__raw_पढ़ोw(PTXCR) & ~0x000f, PTXCR);

	/* select D3-D0 pin function */
	__raw_ग_लिखोw(__raw_पढ़ोw(PSELA) & ~0x2000, PSELA);

	/* select D7-D4 pin function */
	__raw_ग_लिखोw(__raw_पढ़ोw(PSELE) & ~0x3000, PSELE);

	/* disable Hi-Z क्रम the MMC pins */
	__raw_ग_लिखोw(__raw_पढ़ोw(HIZCRC) & ~0x0620, HIZCRC);

	/* high drive capability क्रम MMC pins */
	__raw_ग_लिखोw(__raw_पढ़ोw(DRVCRA) | 0x3000, DRVCRA);

	mmcअगर_update_progress(MMCIF_PROGRESS_INIT);

	/* setup MMCIF hardware */
	sh_mmcअगर_boot_init(MMCIF_BASE);

	mmcअगर_update_progress(MMCIF_PROGRESS_LOAD);

	/* load kernel via MMCIF पूर्णांकerface */
	sh_mmcअगर_boot_करो_पढ़ो(MMCIF_BASE, 512,
	                      (no_bytes + SH_MMCIF_BBS - 1) / SH_MMCIF_BBS,
			      buf);

	/* disable घड़ी to the MMCIF hardware block */
	__raw_ग_लिखोl(__raw_पढ़ोl(MSTPCR2) | 0x20000000, MSTPCR2);

	mmcअगर_update_progress(MMCIF_PROGRESS_DONE);
पूर्ण
