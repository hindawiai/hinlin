<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Board-specअगरic MMC configuration
 */

#अगर_अघोषित _DAVINCI_MMC_H
#घोषणा _DAVINCI_MMC_H

#समावेश <linux/types.h>
#समावेश <linux/mmc/host.h>

काष्ठा davinci_mmc_config अणु
	/* get_cd()/get_wp() may sleep */
	पूर्णांक	(*get_cd)(पूर्णांक module);
	पूर्णांक	(*get_ro)(पूर्णांक module);

	व्योम	(*set_घातer)(पूर्णांक module, bool on);

	/* wires == 0 is equivalent to wires == 4 (4-bit parallel) */
	u8	wires;

	u32     max_freq;

	/* any additional host capabilities: OR'd in to mmc->f_caps */
	u32     caps;

	/* Number of sg segments */
	u8	nr_sg;
पूर्ण;
व्योम davinci_setup_mmc(पूर्णांक module, काष्ठा davinci_mmc_config *config);

क्रमागत अणु
	MMC_CTLR_VERSION_1 = 0,	/* DM644x and DM355 */
	MMC_CTLR_VERSION_2,	/* DA830 */
पूर्ण;

#पूर्ण_अगर
