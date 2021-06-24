<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */

#अगर_अघोषित __ASM_MACH_LOONGSON64_LOONGSON_H
#घोषणा __ASM_MACH_LOONGSON64_LOONGSON_H

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <boot_param.h>

क्रमागत loongson_fw_पूर्णांकerface अणु
	LOONGSON_LEFI,
	LOONGSON_DTB,
पूर्ण;

/* machine-specअगरic boot configuration */
काष्ठा loongson_प्रणाली_configuration अणु
	क्रमागत loongson_fw_पूर्णांकerface fw_पूर्णांकerface;
	u32 nr_cpus;
	u32 nr_nodes;
	पूर्णांक cores_per_node;
	पूर्णांक cores_per_package;
	u16 boot_cpu_id;
	u16 reserved_cpus_mask;
	क्रमागत loongson_cpu_type cputype;
	क्रमागत loongson_bridge_type bridgetype;
	u64 restart_addr;
	u64 घातeroff_addr;
	u64 suspend_addr;
	u64 vgabios_addr;
	u32 dma_mask_bits;
	u64 workarounds;
	व्योम (*early_config)(व्योम);
पूर्ण;

/* machine-specअगरic reboot/halt operation */
बाह्य व्योम mach_prepare_reboot(व्योम);
बाह्य व्योम mach_prepare_shutकरोwn(व्योम);

/* environment arguments from bootloader */
बाह्य u32 cpu_घड़ी_freq;
बाह्य u32 memsize, highmemsize;
बाह्य स्थिर काष्ठा plat_smp_ops loongson3_smp_ops;

/* loongson-specअगरic command line, env and memory initialization */
बाह्य व्योम __init prom_dtb_init_env(व्योम);
बाह्य व्योम __init prom_lefi_init_env(व्योम);
बाह्य व्योम __init szmem(अचिन्हित पूर्णांक node);
बाह्य व्योम *loongson_fdt_blob;

/* irq operation functions */
बाह्य व्योम mach_irq_dispatch(अचिन्हित पूर्णांक pending);
बाह्य पूर्णांक mach_i8259_irq(व्योम);

/* We need this in some places... */
#घोषणा delay() (अणु		\
	पूर्णांक x;				\
	क्रम (x = 0; x < 100000; x++)	\
		__यंत्र__ __अस्थिर__(""); \
पूर्ण)

#घोषणा LOONGSON_REG(x) \
	(*(अस्थिर u32 *)((अक्षर *)CKSEG1ADDR(LOONGSON_REG_BASE) + (x)))

#घोषणा LOONGSON3_REG8(base, x) \
	(*(अस्थिर u8 *)((अक्षर *)TO_UNCAC(base) + (x)))

#घोषणा LOONGSON3_REG32(base, x) \
	(*(अस्थिर u32 *)((अक्षर *)TO_UNCAC(base) + (x)))

#घोषणा LOONGSON_FLASH_BASE	0x1c000000
#घोषणा LOONGSON_FLASH_SIZE	0x02000000	/* 32M */
#घोषणा LOONGSON_FLASH_TOP	(LOONGSON_FLASH_BASE+LOONGSON_FLASH_SIZE-1)

#घोषणा LOONGSON_LIO0_BASE	0x1e000000
#घोषणा LOONGSON_LIO0_SIZE	0x01C00000	/* 28M */
#घोषणा LOONGSON_LIO0_TOP	(LOONGSON_LIO0_BASE+LOONGSON_LIO0_SIZE-1)

#घोषणा LOONGSON_BOOT_BASE	0x1fc00000
#घोषणा LOONGSON_BOOT_SIZE	0x00100000	/* 1M */
#घोषणा LOONGSON_BOOT_TOP	(LOONGSON_BOOT_BASE+LOONGSON_BOOT_SIZE-1)
#घोषणा LOONGSON_REG_BASE	0x1fe00000
#घोषणा LOONGSON_REG_SIZE	0x00100000	/* 256Bytes + 256Bytes + ??? */
#घोषणा LOONGSON_REG_TOP	(LOONGSON_REG_BASE+LOONGSON_REG_SIZE-1)
/* Loongson-3 specअगरic रेजिस्टरs */
#घोषणा LOONGSON3_REG_BASE	0x3ff00000
#घोषणा LOONGSON3_REG_SIZE	0x00100000	/* 256Bytes + 256Bytes + ??? */
#घोषणा LOONGSON3_REG_TOP	(LOONGSON3_REG_BASE+LOONGSON3_REG_SIZE-1)

#घोषणा LOONGSON_LIO1_BASE	0x1ff00000
#घोषणा LOONGSON_LIO1_SIZE	0x00100000	/* 1M */
#घोषणा LOONGSON_LIO1_TOP	(LOONGSON_LIO1_BASE+LOONGSON_LIO1_SIZE-1)

#घोषणा LOONGSON_PCILO0_BASE	0x10000000
#घोषणा LOONGSON_PCILO1_BASE	0x14000000
#घोषणा LOONGSON_PCILO2_BASE	0x18000000
#घोषणा LOONGSON_PCILO_BASE	LOONGSON_PCILO0_BASE
#घोषणा LOONGSON_PCILO_SIZE	0x0c000000	/* 64M * 3 */
#घोषणा LOONGSON_PCILO_TOP	(LOONGSON_PCILO0_BASE+LOONGSON_PCILO_SIZE-1)

#घोषणा LOONGSON_PCICFG_BASE	0x1fe80000
#घोषणा LOONGSON_PCICFG_SIZE	0x00000800	/* 2K */
#घोषणा LOONGSON_PCICFG_TOP	(LOONGSON_PCICFG_BASE+LOONGSON_PCICFG_SIZE-1)

#घोषणा LOONGSON_PCIIO_BASE	loongson_sysconf.pci_io_base

#घोषणा LOONGSON_PCIIO_SIZE	0x00100000	/* 1M */
#घोषणा LOONGSON_PCIIO_TOP	(LOONGSON_PCIIO_BASE+LOONGSON_PCIIO_SIZE-1)

/* Loongson Register Bases */

#घोषणा LOONGSON_PCICONFIGBASE	0x00
#घोषणा LOONGSON_REGBASE	0x100

/* PCI Configuration Registers */

#घोषणा LOONGSON_PCI_REG(x)	LOONGSON_REG(LOONGSON_PCICONFIGBASE + (x))
#घोषणा LOONGSON_PCIDID		LOONGSON_PCI_REG(0x00)
#घोषणा LOONGSON_PCICMD		LOONGSON_PCI_REG(0x04)
#घोषणा LOONGSON_PCICLASS	LOONGSON_PCI_REG(0x08)
#घोषणा LOONGSON_PCILTIMER	LOONGSON_PCI_REG(0x0c)
#घोषणा LOONGSON_PCIBASE0	LOONGSON_PCI_REG(0x10)
#घोषणा LOONGSON_PCIBASE1	LOONGSON_PCI_REG(0x14)
#घोषणा LOONGSON_PCIBASE2	LOONGSON_PCI_REG(0x18)
#घोषणा LOONGSON_PCIBASE3	LOONGSON_PCI_REG(0x1c)
#घोषणा LOONGSON_PCIBASE4	LOONGSON_PCI_REG(0x20)
#घोषणा LOONGSON_PCIEXPRBASE	LOONGSON_PCI_REG(0x30)
#घोषणा LOONGSON_PCIINT		LOONGSON_PCI_REG(0x3c)

#घोषणा LOONGSON_PCI_ISR4C	LOONGSON_PCI_REG(0x4c)

#घोषणा LOONGSON_PCICMD_PERR_CLR	0x80000000
#घोषणा LOONGSON_PCICMD_SERR_CLR	0x40000000
#घोषणा LOONGSON_PCICMD_MABORT_CLR	0x20000000
#घोषणा LOONGSON_PCICMD_MTABORT_CLR	0x10000000
#घोषणा LOONGSON_PCICMD_TABORT_CLR	0x08000000
#घोषणा LOONGSON_PCICMD_MPERR_CLR	0x01000000
#घोषणा LOONGSON_PCICMD_PERRRESPEN	0x00000040
#घोषणा LOONGSON_PCICMD_ASTEPEN		0x00000080
#घोषणा LOONGSON_PCICMD_SERREN		0x00000100
#घोषणा LOONGSON_PCILTIMER_BUSLATENCY	0x0000ff00
#घोषणा LOONGSON_PCILTIMER_BUSLATENCY_SHIFT	8

/* Loongson h/w Configuration */

#घोषणा LOONGSON_GENCFG_OFFSET		0x4
#घोषणा LOONGSON_GENCFG LOONGSON_REG(LOONGSON_REGBASE + LOONGSON_GENCFG_OFFSET)

#घोषणा LOONGSON_GENCFG_DEBUGMODE	0x00000001
#घोषणा LOONGSON_GENCFG_SNOOPEN		0x00000002
#घोषणा LOONGSON_GENCFG_CPUSELFRESET	0x00000004

#घोषणा LOONGSON_GENCFG_FORCE_IRQA	0x00000008
#घोषणा LOONGSON_GENCFG_IRQA_ISOUT	0x00000010
#घोषणा LOONGSON_GENCFG_IRQA_FROM_INT1	0x00000020
#घोषणा LOONGSON_GENCFG_BYTESWAP	0x00000040

#घोषणा LOONGSON_GENCFG_UNCACHED	0x00000080
#घोषणा LOONGSON_GENCFG_PREFETCHEN	0x00000100
#घोषणा LOONGSON_GENCFG_WBEHINDEN	0x00000200
#घोषणा LOONGSON_GENCFG_CACHEALG	0x00000c00
#घोषणा LOONGSON_GENCFG_CACHEALG_SHIFT	10
#घोषणा LOONGSON_GENCFG_PCIQUEUE	0x00001000
#घोषणा LOONGSON_GENCFG_CACHESTOP	0x00002000
#घोषणा LOONGSON_GENCFG_MSTRBYTESWAP	0x00004000
#घोषणा LOONGSON_GENCFG_BUSERREN	0x00008000
#घोषणा LOONGSON_GENCFG_NORETRYTIMEOUT	0x00010000
#घोषणा LOONGSON_GENCFG_SHORTCOPYTIMEOUT	0x00020000

/* PCI address map control */

#घोषणा LOONGSON_PCIMAP			LOONGSON_REG(LOONGSON_REGBASE + 0x10)
#घोषणा LOONGSON_PCIMEMBASECFG		LOONGSON_REG(LOONGSON_REGBASE + 0x14)
#घोषणा LOONGSON_PCIMAP_CFG		LOONGSON_REG(LOONGSON_REGBASE + 0x18)

/* GPIO Regs - r/w */

#घोषणा LOONGSON_GPIODATA		LOONGSON_REG(LOONGSON_REGBASE + 0x1c)
#घोषणा LOONGSON_GPIOIE			LOONGSON_REG(LOONGSON_REGBASE + 0x20)

/* ICU Configuration Regs - r/w */

#घोषणा LOONGSON_INTEDGE		LOONGSON_REG(LOONGSON_REGBASE + 0x24)
#घोषणा LOONGSON_INTSTEER		LOONGSON_REG(LOONGSON_REGBASE + 0x28)
#घोषणा LOONGSON_INTPOL			LOONGSON_REG(LOONGSON_REGBASE + 0x2c)

/* ICU Enable Regs - IntEn & IntISR are r/o. */

#घोषणा LOONGSON_INTENSET		LOONGSON_REG(LOONGSON_REGBASE + 0x30)
#घोषणा LOONGSON_INTENCLR		LOONGSON_REG(LOONGSON_REGBASE + 0x34)
#घोषणा LOONGSON_INTEN			LOONGSON_REG(LOONGSON_REGBASE + 0x38)
#घोषणा LOONGSON_INTISR			LOONGSON_REG(LOONGSON_REGBASE + 0x3c)

/* ICU */
#घोषणा LOONGSON_ICU_MBOXES		0x0000000f
#घोषणा LOONGSON_ICU_MBOXES_SHIFT	0
#घोषणा LOONGSON_ICU_DMARDY		0x00000010
#घोषणा LOONGSON_ICU_DMAEMPTY		0x00000020
#घोषणा LOONGSON_ICU_COPYRDY		0x00000040
#घोषणा LOONGSON_ICU_COPYEMPTY		0x00000080
#घोषणा LOONGSON_ICU_COPYERR		0x00000100
#घोषणा LOONGSON_ICU_PCIIRQ		0x00000200
#घोषणा LOONGSON_ICU_MASTERERR		0x00000400
#घोषणा LOONGSON_ICU_SYSTEMERR		0x00000800
#घोषणा LOONGSON_ICU_DRAMPERR		0x00001000
#घोषणा LOONGSON_ICU_RETRYERR		0x00002000
#घोषणा LOONGSON_ICU_GPIOS		0x01ff0000
#घोषणा LOONGSON_ICU_GPIOS_SHIFT		16
#घोषणा LOONGSON_ICU_GPINS		0x7e000000
#घोषणा LOONGSON_ICU_GPINS_SHIFT		25
#घोषणा LOONGSON_ICU_MBOX(N)		(1<<(LOONGSON_ICU_MBOXES_SHIFT+(N)))
#घोषणा LOONGSON_ICU_GPIO(N)		(1<<(LOONGSON_ICU_GPIOS_SHIFT+(N)))
#घोषणा LOONGSON_ICU_GPIN(N)		(1<<(LOONGSON_ICU_GPINS_SHIFT+(N)))

/* PCI prefetch winकरोw base & mask */

#घोषणा LOONGSON_MEM_WIN_BASE_L		LOONGSON_REG(LOONGSON_REGBASE + 0x40)
#घोषणा LOONGSON_MEM_WIN_BASE_H		LOONGSON_REG(LOONGSON_REGBASE + 0x44)
#घोषणा LOONGSON_MEM_WIN_MASK_L		LOONGSON_REG(LOONGSON_REGBASE + 0x48)
#घोषणा LOONGSON_MEM_WIN_MASK_H		LOONGSON_REG(LOONGSON_REGBASE + 0x4c)

/* PCI_Hit*_Sel_* */

#घोषणा LOONGSON_PCI_HIT0_SEL_L		LOONGSON_REG(LOONGSON_REGBASE + 0x50)
#घोषणा LOONGSON_PCI_HIT0_SEL_H		LOONGSON_REG(LOONGSON_REGBASE + 0x54)
#घोषणा LOONGSON_PCI_HIT1_SEL_L		LOONGSON_REG(LOONGSON_REGBASE + 0x58)
#घोषणा LOONGSON_PCI_HIT1_SEL_H		LOONGSON_REG(LOONGSON_REGBASE + 0x5c)
#घोषणा LOONGSON_PCI_HIT2_SEL_L		LOONGSON_REG(LOONGSON_REGBASE + 0x60)
#घोषणा LOONGSON_PCI_HIT2_SEL_H		LOONGSON_REG(LOONGSON_REGBASE + 0x64)

/* PXArb Config & Status */

#घोषणा LOONGSON_PXARB_CFG		LOONGSON_REG(LOONGSON_REGBASE + 0x68)
#घोषणा LOONGSON_PXARB_STATUS		LOONGSON_REG(LOONGSON_REGBASE + 0x6c)

#घोषणा MAX_PACKAGES 4

/* Chip Config registor of each physical cpu package, PRid >= Loongson-2F */
बाह्य u64 loongson_chipcfg[MAX_PACKAGES];
#घोषणा LOONGSON_CHIPCFG(id) (*(अस्थिर u32 *)(loongson_chipcfg[id]))

/* Chip Temperature registor of each physical cpu package, PRid >= Loongson-3A */
बाह्य u64 loongson_chiptemp[MAX_PACKAGES];
#घोषणा LOONGSON_CHIPTEMP(id) (*(अस्थिर u32 *)(loongson_chiptemp[id]))

/* Freq Control रेजिस्टर of each physical cpu package, PRid >= Loongson-3B */
बाह्य u64 loongson_freqctrl[MAX_PACKAGES];
#घोषणा LOONGSON_FREQCTRL(id) (*(अस्थिर u32 *)(loongson_freqctrl[id]))

/* pcimap */

#घोषणा LOONGSON_PCIMAP_PCIMAP_LO0	0x0000003f
#घोषणा LOONGSON_PCIMAP_PCIMAP_LO0_SHIFT	0
#घोषणा LOONGSON_PCIMAP_PCIMAP_LO1	0x00000fc0
#घोषणा LOONGSON_PCIMAP_PCIMAP_LO1_SHIFT	6
#घोषणा LOONGSON_PCIMAP_PCIMAP_LO2	0x0003f000
#घोषणा LOONGSON_PCIMAP_PCIMAP_LO2_SHIFT	12
#घोषणा LOONGSON_PCIMAP_PCIMAP_2	0x00040000
#घोषणा LOONGSON_PCIMAP_WIN(WIN, ADDR)	\
	((((ADDR)>>26) & LOONGSON_PCIMAP_PCIMAP_LO0) << ((WIN)*6))

#पूर्ण_अगर /* __ASM_MACH_LOONGSON64_LOONGSON_H */
