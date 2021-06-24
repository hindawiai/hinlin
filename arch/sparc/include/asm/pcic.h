<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * pcic.h: JavaEngine 1 specअगरic PCI definitions.
 *
 * Copyright (C) 1998 V. Roganov and G. Raiko
 */

#अगर_अघोषित __SPARC_PCIC_H
#घोषणा __SPARC_PCIC_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/smp.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <यंत्र/pbm.h>

काष्ठा linux_pcic अणु
        व्योम __iomem            *pcic_regs;
        अचिन्हित दीर्घ           pcic_io;
        व्योम __iomem            *pcic_config_space_addr;
        व्योम __iomem            *pcic_config_space_data;
	काष्ठा resource		pcic_res_regs;
	काष्ठा resource		pcic_res_io;
	काष्ठा resource		pcic_res_cfg_addr;
	काष्ठा resource		pcic_res_cfg_data;
        काष्ठा linux_pbm_info   pbm;
	काष्ठा pcic_ca2irq	*pcic_imap;
	पूर्णांक			pcic_imdim;
पूर्ण;

#अगर_घोषित CONFIG_PCIC_PCI
पूर्णांक pcic_present(व्योम);
पूर्णांक pcic_probe(व्योम);
व्योम pci_समय_init(व्योम);
व्योम sun4m_pci_init_IRQ(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक pcic_present(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pcic_probe(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pci_समय_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम sun4m_pci_init_IRQ(व्योम) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/* Size of PCI I/O space which we relocate. */
#घोषणा PCI_SPACE_SIZE                  0x1000000       /* 16 MB */

/* PCIC Register Set. */
#घोषणा PCI_DIAGNOSTIC_0                0x40    /* 32 bits */
#घोषणा PCI_SIZE_0                      0x44    /* 32 bits */
#घोषणा PCI_SIZE_1                      0x48    /* 32 bits */
#घोषणा PCI_SIZE_2                      0x4c    /* 32 bits */
#घोषणा PCI_SIZE_3                      0x50    /* 32 bits */
#घोषणा PCI_SIZE_4                      0x54    /* 32 bits */
#घोषणा PCI_SIZE_5                      0x58    /* 32 bits */
#घोषणा PCI_PIO_CONTROL                 0x60    /* 8  bits */
#घोषणा PCI_DVMA_CONTROL                0x62    /* 8  bits */
#घोषणा  PCI_DVMA_CONTROL_INACTIVITY_REQ        (1<<0)
#घोषणा  PCI_DVMA_CONTROL_IOTLB_ENABLE          (1<<0)
#घोषणा  PCI_DVMA_CONTROL_IOTLB_DISABLE         0
#घोषणा  PCI_DVMA_CONTROL_INACTIVITY_ACK        (1<<4)
#घोषणा PCI_INTERRUPT_CONTROL           0x63    /* 8  bits */
#घोषणा PCI_CPU_INTERRUPT_PENDING       0x64    /* 32 bits */
#घोषणा PCI_DIAGNOSTIC_1                0x68    /* 16 bits */
#घोषणा PCI_SOFTWARE_INT_CLEAR          0x6a    /* 16 bits */
#घोषणा PCI_SOFTWARE_INT_SET            0x6e    /* 16 bits */
#घोषणा PCI_SYS_INT_PENDING             0x70    /* 32 bits */
#घोषणा  PCI_SYS_INT_PENDING_PIO		0x40000000
#घोषणा  PCI_SYS_INT_PENDING_DMA		0x20000000
#घोषणा  PCI_SYS_INT_PENDING_PCI		0x10000000
#घोषणा  PCI_SYS_INT_PENDING_APSR		0x08000000
#घोषणा PCI_SYS_INT_TARGET_MASK         0x74    /* 32 bits */
#घोषणा PCI_SYS_INT_TARGET_MASK_CLEAR   0x78    /* 32 bits */
#घोषणा PCI_SYS_INT_TARGET_MASK_SET     0x7c    /* 32 bits */
#घोषणा PCI_SYS_INT_PENDING_CLEAR       0x83    /* 8  bits */
#घोषणा  PCI_SYS_INT_PENDING_CLEAR_ALL		0x80
#घोषणा  PCI_SYS_INT_PENDING_CLEAR_PIO		0x40
#घोषणा  PCI_SYS_INT_PENDING_CLEAR_DMA		0x20
#घोषणा  PCI_SYS_INT_PENDING_CLEAR_PCI		0x10
#घोषणा PCI_IOTLB_CONTROL               0x84    /* 8  bits */
#घोषणा PCI_INT_SELECT_LO               0x88    /* 16 bits */
#घोषणा PCI_ARBITRATION_SELECT          0x8a    /* 16 bits */
#घोषणा PCI_INT_SELECT_HI               0x8c    /* 16 bits */
#घोषणा PCI_HW_INT_OUTPUT               0x8e    /* 16 bits */
#घोषणा PCI_IOTLB_RAM_INPUT             0x90    /* 32 bits */
#घोषणा PCI_IOTLB_CAM_INPUT             0x94    /* 32 bits */
#घोषणा PCI_IOTLB_RAM_OUTPUT            0x98    /* 32 bits */
#घोषणा PCI_IOTLB_CAM_OUTPUT            0x9c    /* 32 bits */
#घोषणा PCI_SMBAR0                      0xa0    /* 8  bits */
#घोषणा PCI_MSIZE0                      0xa1    /* 8  bits */
#घोषणा PCI_PMBAR0                      0xa2    /* 8  bits */
#घोषणा PCI_SMBAR1                      0xa4    /* 8  bits */
#घोषणा PCI_MSIZE1                      0xa5    /* 8  bits */
#घोषणा PCI_PMBAR1                      0xa6    /* 8  bits */
#घोषणा PCI_SIBAR                       0xa8    /* 8  bits */
#घोषणा   PCI_SIBAR_ADDRESS_MASK        0xf
#घोषणा PCI_ISIZE                       0xa9    /* 8  bits */
#घोषणा   PCI_ISIZE_16M                 0xf
#घोषणा   PCI_ISIZE_32M                 0xe
#घोषणा   PCI_ISIZE_64M                 0xc
#घोषणा   PCI_ISIZE_128M                0x8
#घोषणा   PCI_ISIZE_256M                0x0
#घोषणा PCI_PIBAR                       0xaa    /* 8  bits */
#घोषणा PCI_CPU_COUNTER_LIMIT_HI        0xac    /* 32 bits */
#घोषणा PCI_CPU_COUNTER_LIMIT_LO        0xb0    /* 32 bits */
#घोषणा PCI_CPU_COUNTER_LIMIT           0xb4    /* 32 bits */
#घोषणा PCI_SYS_LIMIT                   0xb8    /* 32 bits */
#घोषणा PCI_SYS_COUNTER                 0xbc    /* 32 bits */
#घोषणा   PCI_SYS_COUNTER_OVERFLOW      (1<<31) /* Limit reached */
#घोषणा PCI_SYS_LIMIT_PSEUDO            0xc0    /* 32 bits */
#घोषणा PCI_USER_TIMER_CONTROL          0xc4    /* 8  bits */
#घोषणा PCI_USER_TIMER_CONFIG           0xc5    /* 8  bits */
#घोषणा PCI_COUNTER_IRQ                 0xc6    /* 8  bits */
#घोषणा  PCI_COUNTER_IRQ_SET(sys_irq, cpu_irq)  ((((sys_irq) & 0xf) << 4) | \
                                                  ((cpu_irq) & 0xf))
#घोषणा  PCI_COUNTER_IRQ_SYS(v)                 (((v) >> 4) & 0xf)
#घोषणा  PCI_COUNTER_IRQ_CPU(v)                 ((v) & 0xf)
#घोषणा PCI_PIO_ERROR_COMMAND           0xc7    /* 8  bits */
#घोषणा PCI_PIO_ERROR_ADDRESS           0xc8    /* 32 bits */
#घोषणा PCI_IOTLB_ERROR_ADDRESS         0xcc    /* 32 bits */
#घोषणा PCI_SYS_STATUS                  0xd0    /* 8  bits */
#घोषणा   PCI_SYS_STATUS_RESET_ENABLE           (1<<0)
#घोषणा   PCI_SYS_STATUS_RESET                  (1<<1)
#घोषणा   PCI_SYS_STATUS_WATCHDOG_RESET         (1<<4)
#घोषणा   PCI_SYS_STATUS_PCI_RESET              (1<<5)
#घोषणा   PCI_SYS_STATUS_PCI_RESET_ENABLE       (1<<6)
#घोषणा   PCI_SYS_STATUS_PCI_SATTELITE_MODE     (1<<7)

#पूर्ण_अगर /* !(__SPARC_PCIC_H) */
