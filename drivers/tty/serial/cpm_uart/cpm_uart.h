<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Driver क्रम CPM (SCC/SMC) serial ports
 *
 *  Copyright (C) 2004 Freescale Semiconductor, Inc.
 *
 *  2006 (c) MontaVista Software, Inc.
 *	Vitaly Bordug <vbordug@ru.mvista.com>
 */
#अगर_अघोषित CPM_UART_H
#घोषणा CPM_UART_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fs_uart_pd.h>

काष्ठा gpio_desc;

#अगर defined(CONFIG_CPM2)
#समावेश "cpm_uart_cpm2.h"
#या_अगर defined(CONFIG_CPM1)
#समावेश "cpm_uart_cpm1.h"
#पूर्ण_अगर

#घोषणा SERIAL_CPM_MAJOR	204
#घोषणा SERIAL_CPM_MINOR	46

#घोषणा IS_SMC(pinfo)		(pinfo->flags & FLAG_SMC)
#घोषणा IS_DISCARDING(pinfo)	(pinfo->flags & FLAG_DISCARDING)
#घोषणा FLAG_DISCARDING	0x00000004	/* when set, करोn't discard */
#घोषणा FLAG_SMC	0x00000002
#घोषणा FLAG_CONSOLE	0x00000001

#घोषणा UART_SMC1	fsid_smc1_uart
#घोषणा UART_SMC2	fsid_smc2_uart
#घोषणा UART_SCC1	fsid_scc1_uart
#घोषणा UART_SCC2	fsid_scc2_uart
#घोषणा UART_SCC3	fsid_scc3_uart
#घोषणा UART_SCC4	fsid_scc4_uart

#घोषणा UART_NR		fs_uart_nr

#घोषणा RX_NUM_FIFO	4
#घोषणा RX_BUF_SIZE	32
#घोषणा TX_NUM_FIFO	4
#घोषणा TX_BUF_SIZE	32

#घोषणा SCC_WAIT_CLOSING 100

#घोषणा GPIO_CTS	0
#घोषणा GPIO_RTS	1
#घोषणा GPIO_DCD	2
#घोषणा GPIO_DSR	3
#घोषणा GPIO_DTR	4
#घोषणा GPIO_RI		5

#घोषणा NUM_GPIOS	(GPIO_RI+1)

काष्ठा uart_cpm_port अणु
	काष्ठा uart_port	port;
	u16			rx_nrfअगरos;
	u16			rx_fअगरosize;
	u16			tx_nrfअगरos;
	u16			tx_fअगरosize;
	smc_t __iomem		*smcp;
	smc_uart_t __iomem	*smcup;
	scc_t __iomem		*sccp;
	scc_uart_t __iomem	*sccup;
	cbd_t __iomem		*rx_bd_base;
	cbd_t __iomem		*rx_cur;
	cbd_t __iomem		*tx_bd_base;
	cbd_t __iomem		*tx_cur;
	अचिन्हित अक्षर		*tx_buf;
	अचिन्हित अक्षर		*rx_buf;
	u32			flags;
	काष्ठा clk		*clk;
	u8			brg;
	uपूर्णांक			 dp_addr;
	व्योम			*mem_addr;
	dma_addr_t		 dma_addr;
	u32			mem_size;
	/* रुको on बंद अगर needed */
	पूर्णांक			रुको_closing;
	/* value to combine with opcode to क्रमm cpm command */
	u32			command;
	काष्ठा gpio_desc	*gpios[NUM_GPIOS];
पूर्ण;

बाह्य पूर्णांक cpm_uart_nr;
बाह्य काष्ठा uart_cpm_port cpm_uart_ports[UART_NR];

/* these are located in their respective files */
व्योम cpm_line_cr_cmd(काष्ठा uart_cpm_port *port, पूर्णांक cmd);
व्योम __iomem *cpm_uart_map_pram(काष्ठा uart_cpm_port *port,
				काष्ठा device_node *np);
व्योम cpm_uart_unmap_pram(काष्ठा uart_cpm_port *port, व्योम __iomem *pram);
पूर्णांक cpm_uart_init_portdesc(व्योम);
पूर्णांक cpm_uart_allocbuf(काष्ठा uart_cpm_port *pinfo, अचिन्हित पूर्णांक is_con);
व्योम cpm_uart_मुक्तbuf(काष्ठा uart_cpm_port *pinfo);

व्योम smc1_lineअगर(काष्ठा uart_cpm_port *pinfo);
व्योम smc2_lineअगर(काष्ठा uart_cpm_port *pinfo);
व्योम scc1_lineअगर(काष्ठा uart_cpm_port *pinfo);
व्योम scc2_lineअगर(काष्ठा uart_cpm_port *pinfo);
व्योम scc3_lineअगर(काष्ठा uart_cpm_port *pinfo);
व्योम scc4_lineअगर(काष्ठा uart_cpm_port *pinfo);

/*
   भव to phys transtalion
*/
अटल अंतरभूत अचिन्हित दीर्घ cpu2cpm_addr(व्योम *addr,
                                         काष्ठा uart_cpm_port *pinfo)
अणु
	पूर्णांक offset;
	u32 val = (u32)addr;
	u32 mem = (u32)pinfo->mem_addr;
	/* sane check */
	अगर (likely(val >= mem && val < mem + pinfo->mem_size)) अणु
		offset = val - mem;
		वापस pinfo->dma_addr + offset;
	पूर्ण
	/* something nasty happened */
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *cpm2cpu_addr(अचिन्हित दीर्घ addr,
                                 काष्ठा uart_cpm_port *pinfo)
अणु
	पूर्णांक offset;
	u32 val = addr;
	u32 dma = (u32)pinfo->dma_addr;
	/* sane check */
	अगर (likely(val >= dma && val < dma + pinfo->mem_size)) अणु
		offset = val - dma;
		वापस pinfo->mem_addr + offset;
	पूर्ण
	/* something nasty happened */
	BUG();
	वापस शून्य;
पूर्ण


#पूर्ण_अगर /* CPM_UART_H */
