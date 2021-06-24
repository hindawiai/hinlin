<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _OMAP2_MCSPI_H
#घोषणा _OMAP2_MCSPI_H

#घोषणा OMAP4_MCSPI_REG_OFFSET 0x100

#घोषणा MCSPI_PINसूची_D0_IN_D1_OUT	0
#घोषणा MCSPI_PINसूची_D0_OUT_D1_IN	1

काष्ठा omap2_mcspi_platक्रमm_config अणु
	अचिन्हित लघु	num_cs;
	अचिन्हित पूर्णांक regs_offset;
	अचिन्हित पूर्णांक pin_dir:1;
	माप_प्रकार max_xfer_len;
पूर्ण;

काष्ठा omap2_mcspi_device_config अणु
	अचिन्हित turbo_mode:1;

	/* toggle chip select after every word */
	अचिन्हित cs_per_word:1;
पूर्ण;

#पूर्ण_अगर
