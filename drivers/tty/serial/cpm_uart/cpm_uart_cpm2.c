<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम CPM (SCC/SMC) serial ports; CPM2 definitions
 *
 *  Maपूर्णांकainer: Kumar Gala (galak@kernel.crashing.org) (CPM2)
 *              Pantelis Antoniou (panto@पूर्णांकracom.gr) (CPM1)
 *
 *  Copyright (C) 2004 Freescale Semiconductor, Inc.
 *            (C) 2004 Intracom, S.A.
 *            (C) 2006 MontaVista Software, Inc.
 *		Vitaly Bordug <vbordug@ru.mvista.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/tty.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/serial.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/fs_pd.h>
#समावेश <यंत्र/prom.h>

#समावेश <linux/serial_core.h>
#समावेश <linux/kernel.h>

#समावेश "cpm_uart.h"

/**************************************************************/

व्योम cpm_line_cr_cmd(काष्ठा uart_cpm_port *port, पूर्णांक cmd)
अणु
	cpm_command(port->command, cmd);
पूर्ण

व्योम __iomem *cpm_uart_map_pram(काष्ठा uart_cpm_port *port,
				काष्ठा device_node *np)
अणु
	व्योम __iomem *pram;
	अचिन्हित दीर्घ offset;
	काष्ठा resource res;
	resource_माप_प्रकार len;

	/* Don't remap parameter RAM अगर it has alपढ़ोy been initialized
	 * during console setup.
	 */
	अगर (IS_SMC(port) && port->smcup)
		वापस port->smcup;
	अन्यथा अगर (!IS_SMC(port) && port->sccup)
		वापस port->sccup;

	अगर (of_address_to_resource(np, 1, &res))
		वापस शून्य;

	len = resource_size(&res);
	pram = ioremap(res.start, len);
	अगर (!pram)
		वापस शून्य;

	अगर (!IS_SMC(port))
		वापस pram;

	अगर (len != 2) अणु
		prपूर्णांकk(KERN_WARNING "cpm_uart[%d]: device tree references "
			"SMC pram, using boot loader/wrapper pram mapping. "
			"Please fix your device tree to reference the pram "
			"base register instead.\n",
			port->port.line);
		वापस pram;
	पूर्ण

	offset = cpm_dpalloc(PROFF_SMC_SIZE, 64);
	out_be16(pram, offset);
	iounmap(pram);
	वापस cpm_muram_addr(offset);
पूर्ण

व्योम cpm_uart_unmap_pram(काष्ठा uart_cpm_port *port, व्योम __iomem *pram)
अणु
	अगर (!IS_SMC(port))
		iounmap(pram);
पूर्ण

/*
 * Allocate DP-Ram and memory buffers. We need to allocate a transmit and
 * receive buffer descriptors from dual port ram, and a अक्षरacter
 * buffer area from host mem. If we are allocating क्रम the console we need
 * to करो it from booपंचांगem
 */
पूर्णांक cpm_uart_allocbuf(काष्ठा uart_cpm_port *pinfo, अचिन्हित पूर्णांक is_con)
अणु
	पूर्णांक dpmemsz, memsz;
	u8 __iomem *dp_mem;
	अचिन्हित दीर्घ dp_offset;
	u8 *mem_addr;
	dma_addr_t dma_addr = 0;

	pr_debug("CPM uart[%d]:allocbuf\n", pinfo->port.line);

	dpmemsz = माप(cbd_t) * (pinfo->rx_nrfअगरos + pinfo->tx_nrfअगरos);
	dp_offset = cpm_dpalloc(dpmemsz, 8);
	अगर (IS_ERR_VALUE(dp_offset)) अणु
		prपूर्णांकk(KERN_ERR
		       "cpm_uart_cpm.c: could not allocate buffer descriptors\n");
		वापस -ENOMEM;
	पूर्ण

	dp_mem = cpm_dpram_addr(dp_offset);

	memsz = L1_CACHE_ALIGN(pinfo->rx_nrfअगरos * pinfo->rx_fअगरosize) +
	    L1_CACHE_ALIGN(pinfo->tx_nrfअगरos * pinfo->tx_fअगरosize);
	अगर (is_con) अणु
		mem_addr = kzalloc(memsz, GFP_NOWAIT);
		dma_addr = virt_to_bus(mem_addr);
	पूर्ण
	अन्यथा
		mem_addr = dma_alloc_coherent(pinfo->port.dev, memsz, &dma_addr,
					      GFP_KERNEL);

	अगर (mem_addr == शून्य) अणु
		cpm_dpमुक्त(dp_offset);
		prपूर्णांकk(KERN_ERR
		       "cpm_uart_cpm.c: could not allocate coherent memory\n");
		वापस -ENOMEM;
	पूर्ण

	pinfo->dp_addr = dp_offset;
	pinfo->mem_addr = mem_addr;
	pinfo->dma_addr = dma_addr;
	pinfo->mem_size = memsz;

	pinfo->rx_buf = mem_addr;
	pinfo->tx_buf = pinfo->rx_buf + L1_CACHE_ALIGN(pinfo->rx_nrfअगरos
						       * pinfo->rx_fअगरosize);

	pinfo->rx_bd_base = (cbd_t __iomem *)dp_mem;
	pinfo->tx_bd_base = pinfo->rx_bd_base + pinfo->rx_nrfअगरos;

	वापस 0;
पूर्ण

व्योम cpm_uart_मुक्तbuf(काष्ठा uart_cpm_port *pinfo)
अणु
	dma_मुक्त_coherent(pinfo->port.dev, L1_CACHE_ALIGN(pinfo->rx_nrfअगरos *
							  pinfo->rx_fअगरosize) +
			  L1_CACHE_ALIGN(pinfo->tx_nrfअगरos *
					 pinfo->tx_fअगरosize), (व्योम __क्रमce *)pinfo->mem_addr,
			  pinfo->dma_addr);

	cpm_dpमुक्त(pinfo->dp_addr);
पूर्ण
