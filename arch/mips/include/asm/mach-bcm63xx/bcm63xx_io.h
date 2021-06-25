<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_IO_H_
#घोषणा BCM63XX_IO_H_

#समावेश <यंत्र/mach-bcm63xx/bcm63xx_cpu.h>

/*
 * Physical memory map, RAM is mapped at 0x0.
 *
 * Note that size MUST be a घातer of two.
 */
#घोषणा BCM_PCMCIA_COMMON_BASE_PA	(0x20000000)
#घोषणा BCM_PCMCIA_COMMON_SIZE		(16 * 1024 * 1024)
#घोषणा BCM_PCMCIA_COMMON_END_PA	(BCM_PCMCIA_COMMON_BASE_PA +	\
					 BCM_PCMCIA_COMMON_SIZE - 1)

#घोषणा BCM_PCMCIA_ATTR_BASE_PA		(0x21000000)
#घोषणा BCM_PCMCIA_ATTR_SIZE		(16 * 1024 * 1024)
#घोषणा BCM_PCMCIA_ATTR_END_PA		(BCM_PCMCIA_ATTR_BASE_PA +	\
					 BCM_PCMCIA_ATTR_SIZE - 1)

#घोषणा BCM_PCMCIA_IO_BASE_PA		(0x22000000)
#घोषणा BCM_PCMCIA_IO_SIZE		(64 * 1024)
#घोषणा BCM_PCMCIA_IO_END_PA		(BCM_PCMCIA_IO_BASE_PA +	\
					BCM_PCMCIA_IO_SIZE - 1)

#घोषणा BCM_PCI_MEM_BASE_PA		(0x30000000)
#घोषणा BCM_PCI_MEM_SIZE		(128 * 1024 * 1024)
#घोषणा BCM_PCI_MEM_END_PA		(BCM_PCI_MEM_BASE_PA +		\
					BCM_PCI_MEM_SIZE - 1)

#घोषणा BCM_PCI_IO_BASE_PA		(0x08000000)
#घोषणा BCM_PCI_IO_SIZE			(64 * 1024)
#घोषणा BCM_PCI_IO_END_PA		(BCM_PCI_IO_BASE_PA +		\
					BCM_PCI_IO_SIZE - 1)
#घोषणा BCM_PCI_IO_HALF_PA		(BCM_PCI_IO_BASE_PA +		\
					(BCM_PCI_IO_SIZE / 2) - 1)

#घोषणा BCM_CB_MEM_BASE_PA		(0x38000000)
#घोषणा BCM_CB_MEM_SIZE			(128 * 1024 * 1024)
#घोषणा BCM_CB_MEM_END_PA		(BCM_CB_MEM_BASE_PA +		\
					BCM_CB_MEM_SIZE - 1)

#घोषणा BCM_PCIE_MEM_BASE_PA		0x10f00000
#घोषणा BCM_PCIE_MEM_SIZE		(16 * 1024 * 1024)
#घोषणा BCM_PCIE_MEM_END_PA		(BCM_PCIE_MEM_BASE_PA +		\
					BCM_PCIE_MEM_SIZE - 1)

/*
 * Internal रेजिस्टरs are accessed through KSEG3
 */
#घोषणा BCM_REGS_VA(x)	((व्योम __iomem *)(x))

#घोषणा bcm_पढ़ोb(a)	(*(अस्थिर अचिन्हित अक्षर *)	BCM_REGS_VA(a))
#घोषणा bcm_पढ़ोw(a)	(*(अस्थिर अचिन्हित लघु *)	BCM_REGS_VA(a))
#घोषणा bcm_पढ़ोl(a)	(*(अस्थिर अचिन्हित पूर्णांक *)	BCM_REGS_VA(a))
#घोषणा bcm_पढ़ोq(a)	(*(अस्थिर u64 *)		BCM_REGS_VA(a))
#घोषणा bcm_ग_लिखोb(v, a) (*(अस्थिर अचिन्हित अक्षर *) BCM_REGS_VA((a)) = (v))
#घोषणा bcm_ग_लिखोw(v, a) (*(अस्थिर अचिन्हित लघु *) BCM_REGS_VA((a)) = (v))
#घोषणा bcm_ग_लिखोl(v, a) (*(अस्थिर अचिन्हित पूर्णांक *) BCM_REGS_VA((a)) = (v))
#घोषणा bcm_ग_लिखोq(v, a) (*(अस्थिर u64 *) BCM_REGS_VA((a)) = (v))

/*
 * IO helpers to access रेजिस्टर set क्रम current CPU
 */
#घोषणा bcm_rset_पढ़ोb(s, o)	bcm_पढ़ोb(bcm63xx_regset_address(s) + (o))
#घोषणा bcm_rset_पढ़ोw(s, o)	bcm_पढ़ोw(bcm63xx_regset_address(s) + (o))
#घोषणा bcm_rset_पढ़ोl(s, o)	bcm_पढ़ोl(bcm63xx_regset_address(s) + (o))
#घोषणा bcm_rset_ग_लिखोb(s, v, o)	bcm_ग_लिखोb((v), \
					bcm63xx_regset_address(s) + (o))
#घोषणा bcm_rset_ग_लिखोw(s, v, o)	bcm_ग_लिखोw((v), \
					bcm63xx_regset_address(s) + (o))
#घोषणा bcm_rset_ग_लिखोl(s, v, o)	bcm_ग_लिखोl((v), \
					bcm63xx_regset_address(s) + (o))

/*
 * helpers क्रम frequently used रेजिस्टर sets
 */
#घोषणा bcm_perf_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_PERF, (o))
#घोषणा bcm_perf_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_PERF, (v), (o))
#घोषणा bcm_समयr_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_TIMER, (o))
#घोषणा bcm_समयr_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_TIMER, (v), (o))
#घोषणा bcm_wdt_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_WDT, (o))
#घोषणा bcm_wdt_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_WDT, (v), (o))
#घोषणा bcm_gpio_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_GPIO, (o))
#घोषणा bcm_gpio_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_GPIO, (v), (o))
#घोषणा bcm_uart0_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_UART0, (o))
#घोषणा bcm_uart0_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_UART0, (v), (o))
#घोषणा bcm_mpi_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_MPI, (o))
#घोषणा bcm_mpi_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_MPI, (v), (o))
#घोषणा bcm_pcmcia_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_PCMCIA, (o))
#घोषणा bcm_pcmcia_ग_लिखोl(v, o) bcm_rset_ग_लिखोl(RSET_PCMCIA, (v), (o))
#घोषणा bcm_pcie_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_PCIE, (o))
#घोषणा bcm_pcie_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_PCIE, (v), (o))
#घोषणा bcm_sdram_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_SDRAM, (o))
#घोषणा bcm_sdram_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_SDRAM, (v), (o))
#घोषणा bcm_memc_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_MEMC, (o))
#घोषणा bcm_memc_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_MEMC, (v), (o))
#घोषणा bcm_ddr_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_DDR, (o))
#घोषणा bcm_ddr_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_DDR, (v), (o))
#घोषणा bcm_misc_पढ़ोl(o)	bcm_rset_पढ़ोl(RSET_MISC, (o))
#घोषणा bcm_misc_ग_लिखोl(v, o)	bcm_rset_ग_लिखोl(RSET_MISC, (v), (o))

#पूर्ण_अगर /* ! BCM63XX_IO_H_ */
