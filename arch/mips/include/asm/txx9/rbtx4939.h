<शैली गुरु>
/*
 * Definitions क्रम RBTX4939
 *
 * (C) Copyright TOSHIBA CORPORATION 2005-2006
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */
#अगर_अघोषित __ASM_TXX9_RBTX4939_H
#घोषणा __ASM_TXX9_RBTX4939_H

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/tx4939.h>

/* Address map */
#घोषणा RBTX4939_IOC_REG_ADDR	(IO_BASE + TXX9_CE(1) + 0x00000000)
#घोषणा RBTX4939_BOARD_REV_ADDR (IO_BASE + TXX9_CE(1) + 0x00000000)
#घोषणा RBTX4939_IOC_REV_ADDR	(IO_BASE + TXX9_CE(1) + 0x00000002)
#घोषणा RBTX4939_CONFIG1_ADDR	(IO_BASE + TXX9_CE(1) + 0x00000004)
#घोषणा RBTX4939_CONFIG2_ADDR	(IO_BASE + TXX9_CE(1) + 0x00000006)
#घोषणा RBTX4939_CONFIG3_ADDR	(IO_BASE + TXX9_CE(1) + 0x00000008)
#घोषणा RBTX4939_CONFIG4_ADDR	(IO_BASE + TXX9_CE(1) + 0x0000000a)
#घोषणा RBTX4939_USTAT_ADDR	(IO_BASE + TXX9_CE(1) + 0x00001000)
#घोषणा RBTX4939_UDIPSW_ADDR	(IO_BASE + TXX9_CE(1) + 0x00001002)
#घोषणा RBTX4939_BDIPSW_ADDR	(IO_BASE + TXX9_CE(1) + 0x00001004)
#घोषणा RBTX4939_IEN_ADDR	(IO_BASE + TXX9_CE(1) + 0x00002000)
#घोषणा RBTX4939_IPOL_ADDR	(IO_BASE + TXX9_CE(1) + 0x00002002)
#घोषणा RBTX4939_IFAC1_ADDR	(IO_BASE + TXX9_CE(1) + 0x00002004)
#घोषणा RBTX4939_IFAC2_ADDR	(IO_BASE + TXX9_CE(1) + 0x00002006)
#घोषणा RBTX4939_SOFTINT_ADDR	(IO_BASE + TXX9_CE(1) + 0x00003000)
#घोषणा RBTX4939_ISASTAT_ADDR	(IO_BASE + TXX9_CE(1) + 0x00004000)
#घोषणा RBTX4939_PCISTAT_ADDR	(IO_BASE + TXX9_CE(1) + 0x00004002)
#घोषणा RBTX4939_ROME_ADDR	(IO_BASE + TXX9_CE(1) + 0x00004004)
#घोषणा RBTX4939_SPICS_ADDR	(IO_BASE + TXX9_CE(1) + 0x00004006)
#घोषणा RBTX4939_AUDI_ADDR	(IO_BASE + TXX9_CE(1) + 0x00004008)
#घोषणा RBTX4939_ISAGPIO_ADDR	(IO_BASE + TXX9_CE(1) + 0x0000400a)
#घोषणा RBTX4939_PE1_ADDR	(IO_BASE + TXX9_CE(1) + 0x00005000)
#घोषणा RBTX4939_PE2_ADDR	(IO_BASE + TXX9_CE(1) + 0x00005002)
#घोषणा RBTX4939_PE3_ADDR	(IO_BASE + TXX9_CE(1) + 0x00005004)
#घोषणा RBTX4939_VP_ADDR	(IO_BASE + TXX9_CE(1) + 0x00005006)
#घोषणा RBTX4939_VPRESET_ADDR	(IO_BASE + TXX9_CE(1) + 0x00005008)
#घोषणा RBTX4939_VPSOUT_ADDR	(IO_BASE + TXX9_CE(1) + 0x0000500a)
#घोषणा RBTX4939_VPSIN_ADDR	(IO_BASE + TXX9_CE(1) + 0x0000500c)
#घोषणा RBTX4939_7SEG_ADDR(s, ch)	\
	(IO_BASE + TXX9_CE(1) + 0x00006000 + (s) * 16 + ((ch) & 3) * 2)
#घोषणा RBTX4939_SOFTRESET_ADDR (IO_BASE + TXX9_CE(1) + 0x00007000)
#घोषणा RBTX4939_RESETEN_ADDR	(IO_BASE + TXX9_CE(1) + 0x00007002)
#घोषणा RBTX4939_RESETSTAT_ADDR (IO_BASE + TXX9_CE(1) + 0x00007004)
#घोषणा RBTX4939_ETHER_BASE	(IO_BASE + TXX9_CE(1) + 0x00020000)

/* Ethernet port address */
#घोषणा RBTX4939_ETHER_ADDR	(RBTX4939_ETHER_BASE + 0x300)

/* bits क्रम IEN/IPOL/IFAC */
#घोषणा RBTX4938_INTB_ISA0	0
#घोषणा RBTX4938_INTB_ISA11	1
#घोषणा RBTX4938_INTB_ISA12	2
#घोषणा RBTX4938_INTB_ISA15	3
#घोषणा RBTX4938_INTB_I2S	4
#घोषणा RBTX4938_INTB_SW	5
#घोषणा RBTX4938_INTF_ISA0	(1 << RBTX4938_INTB_ISA0)
#घोषणा RBTX4938_INTF_ISA11	(1 << RBTX4938_INTB_ISA11)
#घोषणा RBTX4938_INTF_ISA12	(1 << RBTX4938_INTB_ISA12)
#घोषणा RBTX4938_INTF_ISA15	(1 << RBTX4938_INTB_ISA15)
#घोषणा RBTX4938_INTF_I2S	(1 << RBTX4938_INTB_I2S)
#घोषणा RBTX4938_INTF_SW	(1 << RBTX4938_INTB_SW)

/* bits क्रम PE1,PE2,PE3 */
#घोषणा RBTX4939_PE1_ATA(ch)	(0x01 << (ch))
#घोषणा RBTX4939_PE1_RMII(ch)	(0x04 << (ch))
#घोषणा RBTX4939_PE2_SIO0	0x01
#घोषणा RBTX4939_PE2_SIO2	0x02
#घोषणा RBTX4939_PE2_SIO3	0x04
#घोषणा RBTX4939_PE2_CIR	0x08
#घोषणा RBTX4939_PE2_SPI	0x10
#घोषणा RBTX4939_PE2_GPIO	0x20
#घोषणा RBTX4939_PE3_VP 0x01
#घोषणा RBTX4939_PE3_VP_P	0x02
#घोषणा RBTX4939_PE3_VP_S	0x04

#घोषणा rbtx4939_board_rev_addr ((u8 __iomem *)RBTX4939_BOARD_REV_ADDR)
#घोषणा rbtx4939_ioc_rev_addr	((u8 __iomem *)RBTX4939_IOC_REV_ADDR)
#घोषणा rbtx4939_config1_addr	((u8 __iomem *)RBTX4939_CONFIG1_ADDR)
#घोषणा rbtx4939_config2_addr	((u8 __iomem *)RBTX4939_CONFIG2_ADDR)
#घोषणा rbtx4939_config3_addr	((u8 __iomem *)RBTX4939_CONFIG3_ADDR)
#घोषणा rbtx4939_config4_addr	((u8 __iomem *)RBTX4939_CONFIG4_ADDR)
#घोषणा rbtx4939_ustat_addr	((u8 __iomem *)RBTX4939_USTAT_ADDR)
#घोषणा rbtx4939_udipsw_addr	((u8 __iomem *)RBTX4939_UDIPSW_ADDR)
#घोषणा rbtx4939_bdipsw_addr	((u8 __iomem *)RBTX4939_BDIPSW_ADDR)
#घोषणा rbtx4939_ien_addr	((u8 __iomem *)RBTX4939_IEN_ADDR)
#घोषणा rbtx4939_ipol_addr	((u8 __iomem *)RBTX4939_IPOL_ADDR)
#घोषणा rbtx4939_अगरac1_addr	((u8 __iomem *)RBTX4939_IFAC1_ADDR)
#घोषणा rbtx4939_अगरac2_addr	((u8 __iomem *)RBTX4939_IFAC2_ADDR)
#घोषणा rbtx4939_softपूर्णांक_addr	((u8 __iomem *)RBTX4939_SOFTINT_ADDR)
#घोषणा rbtx4939_isastat_addr	((u8 __iomem *)RBTX4939_ISASTAT_ADDR)
#घोषणा rbtx4939_pcistat_addr	((u8 __iomem *)RBTX4939_PCISTAT_ADDR)
#घोषणा rbtx4939_rome_addr	((u8 __iomem *)RBTX4939_ROME_ADDR)
#घोषणा rbtx4939_spics_addr	((u8 __iomem *)RBTX4939_SPICS_ADDR)
#घोषणा rbtx4939_audi_addr	((u8 __iomem *)RBTX4939_AUDI_ADDR)
#घोषणा rbtx4939_isagpio_addr	((u8 __iomem *)RBTX4939_ISAGPIO_ADDR)
#घोषणा rbtx4939_pe1_addr	((u8 __iomem *)RBTX4939_PE1_ADDR)
#घोषणा rbtx4939_pe2_addr	((u8 __iomem *)RBTX4939_PE2_ADDR)
#घोषणा rbtx4939_pe3_addr	((u8 __iomem *)RBTX4939_PE3_ADDR)
#घोषणा rbtx4939_vp_addr	((u8 __iomem *)RBTX4939_VP_ADDR)
#घोषणा rbtx4939_vpreset_addr	((u8 __iomem *)RBTX4939_VPRESET_ADDR)
#घोषणा rbtx4939_vpsout_addr	((u8 __iomem *)RBTX4939_VPSOUT_ADDR)
#घोषणा rbtx4939_vpsin_addr	((u8 __iomem *)RBTX4939_VPSIN_ADDR)
#घोषणा rbtx4939_7seg_addr(s, ch) \
				((u8 __iomem *)RBTX4939_7SEG_ADDR(s, ch))
#घोषणा rbtx4939_softreset_addr ((u8 __iomem *)RBTX4939_SOFTRESET_ADDR)
#घोषणा rbtx4939_reseten_addr	((u8 __iomem *)RBTX4939_RESETEN_ADDR)
#घोषणा rbtx4939_resetstat_addr ((u8 __iomem *)RBTX4939_RESETSTAT_ADDR)

/*
 * IRQ mappings
 */
#घोषणा RBTX4939_NR_IRQ_IOC	8

#घोषणा RBTX4939_IRQ_IOC	(TXX9_IRQ_BASE + TX4939_NUM_IR)
#घोषणा RBTX4939_IRQ_END	(RBTX4939_IRQ_IOC + RBTX4939_NR_IRQ_IOC)

/* IOC (ISA, etc) */
#घोषणा RBTX4939_IRQ_IOCINT	(TXX9_IRQ_BASE + TX4939_IR_INT(0))
/* Onboard 10M Ether */
#घोषणा RBTX4939_IRQ_ETHER	(TXX9_IRQ_BASE + TX4939_IR_INT(1))

व्योम rbtx4939_prom_init(व्योम);
व्योम rbtx4939_irq_setup(व्योम);

काष्ठा mtd_partition;
काष्ठा map_info;
काष्ठा rbtx4939_flash_data अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक nr_parts;
	काष्ठा mtd_partition *parts;
	व्योम (*map_init)(काष्ठा map_info *map);
पूर्ण;

#पूर्ण_अगर /* __ASM_TXX9_RBTX4939_H */
