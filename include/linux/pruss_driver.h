<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * PRU-ICSS sub-प्रणाली specअगरic definitions
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#अगर_अघोषित _PRUSS_DRIVER_H_
#घोषणा _PRUSS_DRIVER_H_

#समावेश <linux/types.h>

/*
 * क्रमागत pruss_mem - PRUSS memory range identअगरiers
 */
क्रमागत pruss_mem अणु
	PRUSS_MEM_DRAM0 = 0,
	PRUSS_MEM_DRAM1,
	PRUSS_MEM_SHRD_RAM2,
	PRUSS_MEM_MAX,
पूर्ण;

/**
 * काष्ठा pruss_mem_region - PRUSS memory region काष्ठाure
 * @va: kernel भव address of the PRUSS memory region
 * @pa: physical (bus) address of the PRUSS memory region
 * @size: size of the PRUSS memory region
 */
काष्ठा pruss_mem_region अणु
	व्योम __iomem *va;
	phys_addr_t pa;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा pruss - PRUSS parent काष्ठाure
 * @dev: pruss device poपूर्णांकer
 * @cfg_base: base iomap क्रम CFG region
 * @cfg_regmap: regmap क्रम config region
 * @mem_regions: data क्रम each of the PRUSS memory regions
 * @core_clk_mux: clk handle क्रम PRUSS CORE_CLK_MUX
 * @iep_clk_mux: clk handle क्रम PRUSS IEP_CLK_MUX
 */
काष्ठा pruss अणु
	काष्ठा device *dev;
	व्योम __iomem *cfg_base;
	काष्ठा regmap *cfg_regmap;
	काष्ठा pruss_mem_region mem_regions[PRUSS_MEM_MAX];
	काष्ठा clk *core_clk_mux;
	काष्ठा clk *iep_clk_mux;
पूर्ण;

#पूर्ण_अगर	/* _PRUSS_DRIVER_H_ */
