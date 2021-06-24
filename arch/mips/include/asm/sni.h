<शैली गुरु>
/*
 * SNI specअगरic definitions
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1997, 1998 by Ralf Baechle
 * Copyright (C) 2006 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 */
#अगर_अघोषित __ASM_SNI_H
#घोषणा __ASM_SNI_H

#समावेश <linux/irqवापस.h>

बाह्य अचिन्हित पूर्णांक sni_brd_type;

#घोषणा SNI_BRD_10		   2
#घोषणा SNI_BRD_10NEW		   3
#घोषणा SNI_BRD_TOWER_OASIC	   4
#घोषणा SNI_BRD_MINITOWER	   5
#घोषणा SNI_BRD_PCI_TOWER	   6
#घोषणा SNI_BRD_RM200		   7
#घोषणा SNI_BRD_PCI_MTOWER	   8
#घोषणा SNI_BRD_PCI_DESKTOP	   9
#घोषणा SNI_BRD_PCI_TOWER_CPLUS	  10
#घोषणा SNI_BRD_PCI_MTOWER_CPLUS  11

/* RM400 cpu types */
#घोषणा SNI_CPU_M8021		0x01
#घोषणा SNI_CPU_M8030		0x04
#घोषणा SNI_CPU_M8031		0x06
#घोषणा SNI_CPU_M8034		0x0f
#घोषणा SNI_CPU_M8037		0x07
#घोषणा SNI_CPU_M8040		0x05
#घोषणा SNI_CPU_M8043		0x09
#घोषणा SNI_CPU_M8050		0x0b
#घोषणा SNI_CPU_M8053		0x0d

#घोषणा SNI_PORT_BASE		CKSEG1ADDR(0xb4000000)

#अगर_अघोषित __MIPSEL__
/*
 * ASIC PCI रेजिस्टरs क्रम big endian configuration.
 */
#घोषणा PCIMT_UCONF		CKSEG1ADDR(0xbfff0004)
#घोषणा PCIMT_IOADTIMEOUT2	CKSEG1ADDR(0xbfff000c)
#घोषणा PCIMT_IOMEMCONF		CKSEG1ADDR(0xbfff0014)
#घोषणा PCIMT_IOMMU		CKSEG1ADDR(0xbfff001c)
#घोषणा PCIMT_IOADTIMEOUT1	CKSEG1ADDR(0xbfff0024)
#घोषणा PCIMT_DMAACCESS		CKSEG1ADDR(0xbfff002c)
#घोषणा PCIMT_DMAHIT		CKSEG1ADDR(0xbfff0034)
#घोषणा PCIMT_ERRSTATUS		CKSEG1ADDR(0xbfff003c)
#घोषणा PCIMT_ERRADDR		CKSEG1ADDR(0xbfff0044)
#घोषणा PCIMT_SYNDROME		CKSEG1ADDR(0xbfff004c)
#घोषणा PCIMT_ITPEND		CKSEG1ADDR(0xbfff0054)
#घोषणा	 IT_INT2		0x01
#घोषणा	 IT_INTD		0x02
#घोषणा	 IT_INTC		0x04
#घोषणा	 IT_INTB		0x08
#घोषणा	 IT_INTA		0x10
#घोषणा	 IT_EISA		0x20
#घोषणा	 IT_SCSI		0x40
#घोषणा	 IT_ETH			0x80
#घोषणा PCIMT_IRQSEL		CKSEG1ADDR(0xbfff005c)
#घोषणा PCIMT_TESTMEM		CKSEG1ADDR(0xbfff0064)
#घोषणा PCIMT_ECCREG		CKSEG1ADDR(0xbfff006c)
#घोषणा PCIMT_CONFIG_ADDRESS	CKSEG1ADDR(0xbfff0074)
#घोषणा PCIMT_ASIC_ID		CKSEG1ADDR(0xbfff007c)	/* पढ़ो */
#घोषणा PCIMT_SOFT_RESET	CKSEG1ADDR(0xbfff007c)	/* ग_लिखो */
#घोषणा PCIMT_PIA_OE		CKSEG1ADDR(0xbfff0084)
#घोषणा PCIMT_PIA_DATAOUT	CKSEG1ADDR(0xbfff008c)
#घोषणा PCIMT_PIA_DATAIN	CKSEG1ADDR(0xbfff0094)
#घोषणा PCIMT_CACHECONF		CKSEG1ADDR(0xbfff009c)
#घोषणा PCIMT_INVSPACE		CKSEG1ADDR(0xbfff00a4)
#अन्यथा
/*
 * ASIC PCI रेजिस्टरs क्रम little endian configuration.
 */
#घोषणा PCIMT_UCONF		CKSEG1ADDR(0xbfff0000)
#घोषणा PCIMT_IOADTIMEOUT2	CKSEG1ADDR(0xbfff0008)
#घोषणा PCIMT_IOMEMCONF		CKSEG1ADDR(0xbfff0010)
#घोषणा PCIMT_IOMMU		CKSEG1ADDR(0xbfff0018)
#घोषणा PCIMT_IOADTIMEOUT1	CKSEG1ADDR(0xbfff0020)
#घोषणा PCIMT_DMAACCESS		CKSEG1ADDR(0xbfff0028)
#घोषणा PCIMT_DMAHIT		CKSEG1ADDR(0xbfff0030)
#घोषणा PCIMT_ERRSTATUS		CKSEG1ADDR(0xbfff0038)
#घोषणा PCIMT_ERRADDR		CKSEG1ADDR(0xbfff0040)
#घोषणा PCIMT_SYNDROME		CKSEG1ADDR(0xbfff0048)
#घोषणा PCIMT_ITPEND		CKSEG1ADDR(0xbfff0050)
#घोषणा	 IT_INT2		0x01
#घोषणा	 IT_INTD		0x02
#घोषणा	 IT_INTC		0x04
#घोषणा	 IT_INTB		0x08
#घोषणा	 IT_INTA		0x10
#घोषणा	 IT_EISA		0x20
#घोषणा	 IT_SCSI		0x40
#घोषणा	 IT_ETH			0x80
#घोषणा PCIMT_IRQSEL		CKSEG1ADDR(0xbfff0058)
#घोषणा PCIMT_TESTMEM		CKSEG1ADDR(0xbfff0060)
#घोषणा PCIMT_ECCREG		CKSEG1ADDR(0xbfff0068)
#घोषणा PCIMT_CONFIG_ADDRESS	CKSEG1ADDR(0xbfff0070)
#घोषणा PCIMT_ASIC_ID		CKSEG1ADDR(0xbfff0078)	/* पढ़ो */
#घोषणा PCIMT_SOFT_RESET	CKSEG1ADDR(0xbfff0078)	/* ग_लिखो */
#घोषणा PCIMT_PIA_OE		CKSEG1ADDR(0xbfff0080)
#घोषणा PCIMT_PIA_DATAOUT	CKSEG1ADDR(0xbfff0088)
#घोषणा PCIMT_PIA_DATAIN	CKSEG1ADDR(0xbfff0090)
#घोषणा PCIMT_CACHECONF		CKSEG1ADDR(0xbfff0098)
#घोषणा PCIMT_INVSPACE		CKSEG1ADDR(0xbfff00a0)
#पूर्ण_अगर

#घोषणा PCIMT_PCI_CONF		CKSEG1ADDR(0xbfff0100)

/*
 * Data port क्रम the PCI bus in IO space
 */
#घोषणा PCIMT_CONFIG_DATA	0x0cfc

/*
 * Board specअगरic रेजिस्टरs
 */
#घोषणा PCIMT_CSMSR		CKSEG1ADDR(0xbfd00000)
#घोषणा PCIMT_CSSWITCH		CKSEG1ADDR(0xbfd10000)
#घोषणा PCIMT_CSITPEND		CKSEG1ADDR(0xbfd20000)
#घोषणा PCIMT_AUTO_PO_EN	CKSEG1ADDR(0xbfd30000)
#घोषणा PCIMT_CLR_TEMP		CKSEG1ADDR(0xbfd40000)
#घोषणा PCIMT_AUTO_PO_DIS	CKSEG1ADDR(0xbfd50000)
#घोषणा PCIMT_EXMSR		CKSEG1ADDR(0xbfd60000)
#घोषणा PCIMT_UNUSED1		CKSEG1ADDR(0xbfd70000)
#घोषणा PCIMT_CSWCSM		CKSEG1ADDR(0xbfd80000)
#घोषणा PCIMT_UNUSED2		CKSEG1ADDR(0xbfd90000)
#घोषणा PCIMT_CSLED		CKSEG1ADDR(0xbfda0000)
#घोषणा PCIMT_CSMAPISA		CKSEG1ADDR(0xbfdb0000)
#घोषणा PCIMT_CSRSTBP		CKSEG1ADDR(0xbfdc0000)
#घोषणा PCIMT_CLRPOFF		CKSEG1ADDR(0xbfdd0000)
#घोषणा PCIMT_CSTIMER		CKSEG1ADDR(0xbfde0000)
#घोषणा PCIMT_PWDN		CKSEG1ADDR(0xbfdf0000)

/*
 * A20R based boards
 */
#घोषणा A20R_PT_CLOCK_BASE	CKSEG1ADDR(0xbc040000)
#घोषणा A20R_PT_TIM0_ACK	CKSEG1ADDR(0xbc050000)
#घोषणा A20R_PT_TIM1_ACK	CKSEG1ADDR(0xbc060000)

#घोषणा SNI_A20R_IRQ_BASE	MIPS_CPU_IRQ_BASE
#घोषणा SNI_A20R_IRQ_TIMER	(SNI_A20R_IRQ_BASE+5)

#घोषणा SNI_PCIT_INT_REG	CKSEG1ADDR(0xbfff000c)

#घोषणा SNI_PCIT_INT_START	24
#घोषणा SNI_PCIT_INT_END	30

#घोषणा PCIT_IRQ_ETHERNET	(MIPS_CPU_IRQ_BASE + 5)
#घोषणा PCIT_IRQ_INTA		(SNI_PCIT_INT_START + 0)
#घोषणा PCIT_IRQ_INTB		(SNI_PCIT_INT_START + 1)
#घोषणा PCIT_IRQ_INTC		(SNI_PCIT_INT_START + 2)
#घोषणा PCIT_IRQ_INTD		(SNI_PCIT_INT_START + 3)
#घोषणा PCIT_IRQ_SCSI0		(SNI_PCIT_INT_START + 4)
#घोषणा PCIT_IRQ_SCSI1		(SNI_PCIT_INT_START + 5)


/*
 * Interrupt 0-16 are EISA पूर्णांकerrupts.	Interrupts from 16 on are asचिन्हित
 * to the other पूर्णांकerrupts generated by ASIC PCI.
 *
 * INT2 is a wired-or of the push button पूर्णांकerrupt, high temperature पूर्णांकerrupt
 * ASIC PCI पूर्णांकerrupt.
 */
#घोषणा PCIMT_KEYBOARD_IRQ	 1
#घोषणा PCIMT_IRQ_INT2		24
#घोषणा PCIMT_IRQ_INTD		25
#घोषणा PCIMT_IRQ_INTC		26
#घोषणा PCIMT_IRQ_INTB		27
#घोषणा PCIMT_IRQ_INTA		28
#घोषणा PCIMT_IRQ_EISA		29
#घोषणा PCIMT_IRQ_SCSI		30

#घोषणा PCIMT_IRQ_ETHERNET	(MIPS_CPU_IRQ_BASE+6)

#अगर 0
#घोषणा PCIMT_IRQ_TEMPERATURE	24
#घोषणा PCIMT_IRQ_EISA_NMI	25
#घोषणा PCIMT_IRQ_POWER_OFF	26
#घोषणा PCIMT_IRQ_BUTTON	27
#पूर्ण_अगर

/*
 * Base address क्रम the mapped 16mb EISA bus segment.
 */
#घोषणा PCIMT_EISA_BASE		CKSEG1ADDR(0xb0000000)

/* PCI EISA Interrupt acknowledge  */
#घोषणा PCIMT_INT_ACKNOWLEDGE	CKSEG1ADDR(0xba000000)

/*
 *  SNI ID PROM
 *
 * SNI_IDPROM_MEMSIZE  Memsize in 16MB quantities
 * SNI_IDPROM_BRDTYPE  Board Type
 * SNI_IDPROM_CPUTYPE  CPU Type on RM400
 */
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा __SNI_END 0
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
#घोषणा __SNI_END 3
#पूर्ण_अगर
#घोषणा SNI_IDPROM_BASE	       CKSEG1ADDR(0x1ff00000)
#घोषणा SNI_IDPROM_MEMSIZE     (SNI_IDPROM_BASE + (0x28 ^ __SNI_END))
#घोषणा SNI_IDPROM_BRDTYPE     (SNI_IDPROM_BASE + (0x29 ^ __SNI_END))
#घोषणा SNI_IDPROM_CPUTYPE     (SNI_IDPROM_BASE + (0x30 ^ __SNI_END))

#घोषणा SNI_IDPROM_SIZE 0x1000

/* board specअगरic init functions */
बाह्य व्योम sni_a20r_init(व्योम);
बाह्य व्योम sni_pcit_init(व्योम);
बाह्य व्योम sni_rm200_init(व्योम);
बाह्य व्योम sni_pcimt_init(व्योम);

/* board specअगरic irq init functions */
बाह्य व्योम sni_a20r_irq_init(व्योम);
बाह्य व्योम sni_pcit_irq_init(व्योम);
बाह्य व्योम sni_pcit_cplus_irq_init(व्योम);
बाह्य व्योम sni_rm200_irq_init(व्योम);
बाह्य व्योम sni_pcimt_irq_init(व्योम);

/* समयr inits */
बाह्य व्योम sni_cpu_समय_init(व्योम);

/* eisa init क्रम RM200/400 */
#अगर_घोषित CONFIG_EISA
बाह्य पूर्णांक sni_eisa_root_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक sni_eisa_root_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* common irq stuff */
बाह्य व्योम (*sni_hwपूर्णांक)(व्योम);
बाह्य irqवापस_t sni_isa_irq_handler(पूर्णांक dummy, व्योम *p);

#पूर्ण_अगर /* __ASM_SNI_H */
