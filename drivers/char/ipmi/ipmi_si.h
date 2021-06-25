<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * ipmi_si.h
 *
 * Interface from the device-specअगरic पूर्णांकerfaces (OF, DMI, ACPI, PCI,
 * etc) to the base ipmi प्रणाली पूर्णांकerface code.
 */

#अगर_अघोषित __IPMI_SI_H__
#घोषणा __IPMI_SI_H__

#समावेश <linux/ipmi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा SI_DEVICE_NAME "ipmi_si"

#घोषणा DEFAULT_REGSPACING	1
#घोषणा DEFAULT_REGSIZE		1

/* Numbers in this क्रमागतerator should be mapped to si_to_str[] */
क्रमागत si_type अणु
	SI_TYPE_INVALID, SI_KCS, SI_SMIC, SI_BT, SI_TYPE_MAX
पूर्ण;

/* Array is defined in the ipmi_si_पूर्णांकf.c */
बाह्य स्थिर अक्षर *स्थिर si_to_str[];

क्रमागत ipmi_addr_space अणु
	IPMI_IO_ADDR_SPACE, IPMI_MEM_ADDR_SPACE
पूर्ण;

/*
 * The काष्ठाure क्रम करोing I/O in the state machine.  The state
 * machine करोesn't have the actual I/O routines, they are करोne through
 * this पूर्णांकerface.
 */
काष्ठा si_sm_io अणु
	अचिन्हित अक्षर (*inputb)(स्थिर काष्ठा si_sm_io *io, अचिन्हित पूर्णांक offset);
	व्योम (*outputb)(स्थिर काष्ठा si_sm_io *io,
			अचिन्हित पूर्णांक  offset,
			अचिन्हित अक्षर b);

	/*
	 * Generic info used by the actual handling routines, the
	 * state machine shouldn't touch these.
	 */
	व्योम __iomem *addr;
	अचिन्हित पूर्णांक regspacing;
	अचिन्हित पूर्णांक regsize;
	अचिन्हित पूर्णांक regshअगरt;
	क्रमागत ipmi_addr_space addr_space;
	अचिन्हित दीर्घ addr_data;
	क्रमागत ipmi_addr_src addr_source; /* ACPI, PCI, SMBIOS, hardcode, etc. */
	जोड़ ipmi_smi_info_जोड़ addr_info;

	पूर्णांक (*io_setup)(काष्ठा si_sm_io *info);
	व्योम (*io_cleanup)(काष्ठा si_sm_io *info);
	अचिन्हित पूर्णांक io_size;

	पूर्णांक irq;
	पूर्णांक (*irq_setup)(काष्ठा si_sm_io *io);
	व्योम *irq_handler_data;
	व्योम (*irq_cleanup)(काष्ठा si_sm_io *io);

	u8 slave_addr;
	क्रमागत si_type si_type;
	काष्ठा device *dev;
पूर्ण;

पूर्णांक ipmi_si_add_smi(काष्ठा si_sm_io *io);
irqवापस_t ipmi_si_irq_handler(पूर्णांक irq, व्योम *data);
व्योम ipmi_irq_start_cleanup(काष्ठा si_sm_io *io);
पूर्णांक ipmi_std_irq_setup(काष्ठा si_sm_io *io);
व्योम ipmi_irq_finish_setup(काष्ठा si_sm_io *io);
पूर्णांक ipmi_si_हटाओ_by_dev(काष्ठा device *dev);
काष्ठा device *ipmi_si_हटाओ_by_data(पूर्णांक addr_space, क्रमागत si_type si_type,
				      अचिन्हित दीर्घ addr);
व्योम ipmi_hardcode_init(व्योम);
व्योम ipmi_si_hardcode_निकास(व्योम);
व्योम ipmi_si_hoपंचांगod_निकास(व्योम);
पूर्णांक ipmi_si_hardcode_match(पूर्णांक addr_space, अचिन्हित दीर्घ addr);
व्योम ipmi_si_platक्रमm_init(व्योम);
व्योम ipmi_si_platक्रमm_shutकरोwn(व्योम);
व्योम ipmi_हटाओ_platक्रमm_device_by_name(अक्षर *name);

बाह्य काष्ठा platक्रमm_driver ipmi_platक्रमm_driver;

#अगर_घोषित CONFIG_PCI
व्योम ipmi_si_pci_init(व्योम);
व्योम ipmi_si_pci_shutकरोwn(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ipmi_si_pci_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ipmi_si_pci_shutकरोwn(व्योम) अणु पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PARISC
व्योम ipmi_si_parisc_init(व्योम);
व्योम ipmi_si_parisc_shutकरोwn(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ipmi_si_parisc_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम ipmi_si_parisc_shutकरोwn(व्योम) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक ipmi_si_port_setup(काष्ठा si_sm_io *io);
पूर्णांक ipmi_si_mem_setup(काष्ठा si_sm_io *io);

#पूर्ण_अगर /* __IPMI_SI_H__ */
