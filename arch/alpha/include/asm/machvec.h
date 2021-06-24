<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_MACHVEC_H
#घोषणा __ALPHA_MACHVEC_H 1

#समावेश <linux/types.h>

/*
 *	This file माला_लो pulled in by यंत्र/पन.स from user space. We करोn't
 *	want most of this escaping.
 */
 
#अगर_घोषित __KERNEL__

/* The following काष्ठाure vectors all of the I/O and IRQ manipulation
   from the generic kernel to the hardware specअगरic backend.  */

काष्ठा task_काष्ठा;
काष्ठा mm_काष्ठा;
काष्ठा vm_area_काष्ठा;
काष्ठा linux_hose_info;
काष्ठा pci_dev;
काष्ठा pci_ops;
काष्ठा pci_controller;
काष्ठा _alpha_agp_info;
काष्ठा rtc_समय;

काष्ठा alpha_machine_vector
अणु
	/* This "belongs" करोwn below with the rest of the runसमय
	   variables, but it is convenient क्रम entry.S अगर these 
	   two slots are at the beginning of the काष्ठा.  */
	अचिन्हित दीर्घ hae_cache;
	अचिन्हित दीर्घ *hae_रेजिस्टर;

	पूर्णांक nr_irqs;
	पूर्णांक rtc_port;
	पूर्णांक rtc_boot_cpu_only;
	अचिन्हित पूर्णांक max_asn;
	अचिन्हित दीर्घ max_isa_dma_address;
	अचिन्हित दीर्घ irq_probe_mask;
	अचिन्हित दीर्घ iack_sc;
	अचिन्हित दीर्घ min_io_address;
	अचिन्हित दीर्घ min_mem_address;
	अचिन्हित दीर्घ pci_dac_offset;

	व्योम (*mv_pci_tbi)(काष्ठा pci_controller *hose,
			   dma_addr_t start, dma_addr_t end);

	अचिन्हित पूर्णांक (*mv_ioपढ़ो8)(स्थिर व्योम __iomem *);
	अचिन्हित पूर्णांक (*mv_ioपढ़ो16)(स्थिर व्योम __iomem *);
	अचिन्हित पूर्णांक (*mv_ioपढ़ो32)(स्थिर व्योम __iomem *);

	व्योम (*mv_ioग_लिखो8)(u8, व्योम __iomem *);
	व्योम (*mv_ioग_लिखो16)(u16, व्योम __iomem *);
	व्योम (*mv_ioग_लिखो32)(u32, व्योम __iomem *);

	u8 (*mv_पढ़ोb)(स्थिर अस्थिर व्योम __iomem *);
	u16 (*mv_पढ़ोw)(स्थिर अस्थिर व्योम __iomem *);
	u32 (*mv_पढ़ोl)(स्थिर अस्थिर व्योम __iomem *);
	u64 (*mv_पढ़ोq)(स्थिर अस्थिर व्योम __iomem *);

	व्योम (*mv_ग_लिखोb)(u8, अस्थिर व्योम __iomem *);
	व्योम (*mv_ग_लिखोw)(u16, अस्थिर व्योम __iomem *);
	व्योम (*mv_ग_लिखोl)(u32, अस्थिर व्योम __iomem *);
	व्योम (*mv_ग_लिखोq)(u64, अस्थिर व्योम __iomem *);

	व्योम __iomem *(*mv_ioporपंचांगap)(अचिन्हित दीर्घ);
	व्योम __iomem *(*mv_ioremap)(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
	व्योम (*mv_iounmap)(अस्थिर व्योम __iomem *);
	पूर्णांक (*mv_is_ioaddr)(अचिन्हित दीर्घ);
	पूर्णांक (*mv_is_mmio)(स्थिर अस्थिर व्योम __iomem *);

	व्योम (*mv_चयन_mm)(काष्ठा mm_काष्ठा *, काष्ठा mm_काष्ठा *,
			     काष्ठा task_काष्ठा *);
	व्योम (*mv_activate_mm)(काष्ठा mm_काष्ठा *, काष्ठा mm_काष्ठा *);

	व्योम (*mv_flush_tlb_current)(काष्ठा mm_काष्ठा *);
	व्योम (*mv_flush_tlb_current_page)(काष्ठा mm_काष्ठा * mm,
					  काष्ठा vm_area_काष्ठा *vma,
					  अचिन्हित दीर्घ addr);

	व्योम (*update_irq_hw)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक);
	व्योम (*ack_irq)(अचिन्हित दीर्घ);
	व्योम (*device_पूर्णांकerrupt)(अचिन्हित दीर्घ vector);
	व्योम (*machine_check)(अचिन्हित दीर्घ vector, अचिन्हित दीर्घ la);

	व्योम (*smp_callin)(व्योम);
	व्योम (*init_arch)(व्योम);
	व्योम (*init_irq)(व्योम);
	व्योम (*init_rtc)(व्योम);
	व्योम (*init_pci)(व्योम);
	व्योम (*समाप्त_arch)(पूर्णांक);

	u8 (*pci_swizzle)(काष्ठा pci_dev *, u8 *);
	पूर्णांक (*pci_map_irq)(स्थिर काष्ठा pci_dev *, u8, u8);
	काष्ठा pci_ops *pci_ops;

	काष्ठा _alpha_agp_info *(*agp_info)(व्योम);

	स्थिर अक्षर *vector_name;

	/* NUMA inक्रमmation */
	पूर्णांक (*pa_to_nid)(अचिन्हित दीर्घ);
	पूर्णांक (*cpuid_to_nid)(पूर्णांक);
	अचिन्हित दीर्घ (*node_mem_start)(पूर्णांक);
	अचिन्हित दीर्घ (*node_mem_size)(पूर्णांक);

	/* System specअगरic parameters.  */
	जोड़ अणु
	    काष्ठा अणु
		अचिन्हित दीर्घ gru_पूर्णांक_req_bits;
	    पूर्ण cia;

	    काष्ठा अणु
		अचिन्हित दीर्घ gamma_bias;
	    पूर्ण t2;

	    काष्ठा अणु
		अचिन्हित पूर्णांक route_tab;
	    पूर्ण sio;
	पूर्ण sys;
पूर्ण;

बाह्य काष्ठा alpha_machine_vector alpha_mv;

#अगर_घोषित CONFIG_ALPHA_GENERIC
बाह्य पूर्णांक alpha_using_srm;
बाह्य पूर्णांक alpha_using_qemu;
#अन्यथा
# अगरdef CONFIG_ALPHA_SRM
#  define alpha_using_srm 1
# अन्यथा
#  define alpha_using_srm 0
# endअगर
# अगरdef CONFIG_ALPHA_QEMU
#  define alpha_using_qemu 1
# अन्यथा
#  define alpha_using_qemu 0
# endअगर
#पूर्ण_अगर /* GENERIC */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ALPHA_MACHVEC_H */
