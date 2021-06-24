<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SLIM core rproc driver header
 *
 * Copyright (C) 2016 STMicroelectronics
 *
 * Author: Peter Grअगरfin <peter.grअगरfin@linaro.org>
 */
#अगर_अघोषित _ST_REMOTEPROC_SLIM_H
#घोषणा _ST_REMOTEPROC_SLIM_H

#घोषणा ST_SLIM_MEM_MAX 2
#घोषणा ST_SLIM_MAX_CLK 4

क्रमागत अणु
	ST_SLIM_DMEM,
	ST_SLIM_IMEM,
पूर्ण;

/**
 * काष्ठा st_slim_mem - slim पूर्णांकernal memory काष्ठाure
 * @cpu_addr: MPU भव address of the memory region
 * @bus_addr: Bus address used to access the memory region
 * @size: Size of the memory region
 */
काष्ठा st_slim_mem अणु
	व्योम __iomem *cpu_addr;
	phys_addr_t bus_addr;
	माप_प्रकार size;
पूर्ण;

/**
 * काष्ठा st_slim_rproc - SLIM slim core
 * @rproc: rproc handle
 * @mem: slim memory inक्रमmation
 * @slimcore: slim slimcore regs
 * @peri: slim peripheral regs
 * @clks: slim घड़ीs
 */
काष्ठा st_slim_rproc अणु
	काष्ठा rproc *rproc;
	काष्ठा st_slim_mem mem[ST_SLIM_MEM_MAX];
	व्योम __iomem *slimcore;
	व्योम __iomem *peri;

	/* st_slim_rproc निजी */
	काष्ठा clk *clks[ST_SLIM_MAX_CLK];
पूर्ण;

काष्ठा st_slim_rproc *st_slim_rproc_alloc(काष्ठा platक्रमm_device *pdev,
					अक्षर *fw_name);
व्योम st_slim_rproc_put(काष्ठा st_slim_rproc *slim_rproc);

#पूर्ण_अगर
