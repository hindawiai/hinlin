<शैली गुरु>
/*
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित __XEN_PUBLIC_PHYSDEV_H__
#घोषणा __XEN_PUBLIC_PHYSDEV_H__

/*
 * Prototype क्रम this hypercall is:
 *  पूर्णांक physdev_op(पूर्णांक cmd, व्योम *args)
 * @cmd	 == PHYSDEVOP_??? (physdev operation).
 * @args == Operation-specअगरic extra arguments (शून्य अगर none).
 */

/*
 * Notअगरy end-of-पूर्णांकerrupt (EOI) क्रम the specअगरied IRQ.
 * @arg == poपूर्णांकer to physdev_eoi काष्ठाure.
 */
#घोषणा PHYSDEVOP_eoi			12
काष्ठा physdev_eoi अणु
	/* IN */
	uपूर्णांक32_t irq;
पूर्ण;

/*
 * Register a shared page क्रम the hypervisor to indicate whether the guest
 * must issue PHYSDEVOP_eoi. The semantics of PHYSDEVOP_eoi change slightly
 * once the guest used this function in that the associated event channel
 * will स्वतःmatically get unmasked. The page रेजिस्टरed is used as a bit
 * array indexed by Xen's PIRQ value.
 */
#घोषणा PHYSDEVOP_pirq_eoi_gmfn_v1       17
/*
 * Register a shared page क्रम the hypervisor to indicate whether the
 * guest must issue PHYSDEVOP_eoi. This hypercall is very similar to
 * PHYSDEVOP_pirq_eoi_gmfn_v1 but it करोesn't change the semantics of
 * PHYSDEVOP_eoi. The page रेजिस्टरed is used as a bit array indexed by
 * Xen's PIRQ value.
 */
#घोषणा PHYSDEVOP_pirq_eoi_gmfn_v2       28
काष्ठा physdev_pirq_eoi_gmfn अणु
    /* IN */
    xen_uदीर्घ_t gmfn;
पूर्ण;

/*
 * Query the status of an IRQ line.
 * @arg == poपूर्णांकer to physdev_irq_status_query काष्ठाure.
 */
#घोषणा PHYSDEVOP_irq_status_query	 5
काष्ठा physdev_irq_status_query अणु
	/* IN */
	uपूर्णांक32_t irq;
	/* OUT */
	uपूर्णांक32_t flags; /* XENIRQSTAT_* */
पूर्ण;

/* Need to call PHYSDEVOP_eoi when the IRQ has been serviced? */
#घोषणा _XENIRQSTAT_needs_eoi	(0)
#घोषणा	 XENIRQSTAT_needs_eoi	(1U<<_XENIRQSTAT_needs_eoi)

/* IRQ shared by multiple guests? */
#घोषणा _XENIRQSTAT_shared	(1)
#घोषणा	 XENIRQSTAT_shared	(1U<<_XENIRQSTAT_shared)

/*
 * Set the current VCPU's I/O privilege level.
 * @arg == poपूर्णांकer to physdev_set_iopl काष्ठाure.
 */
#घोषणा PHYSDEVOP_set_iopl		 6
काष्ठा physdev_set_iopl अणु
	/* IN */
	uपूर्णांक32_t iopl;
पूर्ण;

/*
 * Set the current VCPU's I/O-port permissions biपंचांगap.
 * @arg == poपूर्णांकer to physdev_set_iobiपंचांगap काष्ठाure.
 */
#घोषणा PHYSDEVOP_set_iobiपंचांगap		 7
काष्ठा physdev_set_iobiपंचांगap अणु
	/* IN */
	uपूर्णांक8_t * biपंचांगap;
	uपूर्णांक32_t nr_ports;
पूर्ण;

/*
 * Read or ग_लिखो an IO-APIC रेजिस्टर.
 * @arg == poपूर्णांकer to physdev_apic काष्ठाure.
 */
#घोषणा PHYSDEVOP_apic_पढ़ो		 8
#घोषणा PHYSDEVOP_apic_ग_लिखो		 9
काष्ठा physdev_apic अणु
	/* IN */
	अचिन्हित दीर्घ apic_physbase;
	uपूर्णांक32_t reg;
	/* IN or OUT */
	uपूर्णांक32_t value;
पूर्ण;

/*
 * Allocate or मुक्त a physical upcall vector क्रम the specअगरied IRQ line.
 * @arg == poपूर्णांकer to physdev_irq काष्ठाure.
 */
#घोषणा PHYSDEVOP_alloc_irq_vector	10
#घोषणा PHYSDEVOP_मुक्त_irq_vector	11
काष्ठा physdev_irq अणु
	/* IN */
	uपूर्णांक32_t irq;
	/* IN or OUT */
	uपूर्णांक32_t vector;
पूर्ण;

#घोषणा MAP_PIRQ_TYPE_MSI		0x0
#घोषणा MAP_PIRQ_TYPE_GSI		0x1
#घोषणा MAP_PIRQ_TYPE_UNKNOWN		0x2
#घोषणा MAP_PIRQ_TYPE_MSI_SEG		0x3
#घोषणा MAP_PIRQ_TYPE_MULTI_MSI		0x4

#घोषणा PHYSDEVOP_map_pirq		13
काष्ठा physdev_map_pirq अणु
    करोmid_t करोmid;
    /* IN */
    पूर्णांक type;
    /* IN */
    पूर्णांक index;
    /* IN or OUT */
    पूर्णांक pirq;
    /* IN - high 16 bits hold segment क्रम ..._MSI_SEG and ..._MULTI_MSI */
    पूर्णांक bus;
    /* IN */
    पूर्णांक devfn;
    /* IN
     * - For MSI-X contains entry number.
     * - For MSI with ..._MULTI_MSI contains number of vectors.
     * OUT (..._MULTI_MSI only)
     * - Number of vectors allocated.
     */
    पूर्णांक entry_nr;
    /* IN */
    uपूर्णांक64_t table_base;
पूर्ण;

#घोषणा PHYSDEVOP_unmap_pirq		14
काष्ठा physdev_unmap_pirq अणु
    करोmid_t करोmid;
    /* IN */
    पूर्णांक pirq;
पूर्ण;

#घोषणा PHYSDEVOP_manage_pci_add	15
#घोषणा PHYSDEVOP_manage_pci_हटाओ	16
काष्ठा physdev_manage_pci अणु
	/* IN */
	uपूर्णांक8_t bus;
	uपूर्णांक8_t devfn;
पूर्ण;

#घोषणा PHYSDEVOP_restore_msi            19
काष्ठा physdev_restore_msi अणु
	/* IN */
	uपूर्णांक8_t bus;
	uपूर्णांक8_t devfn;
पूर्ण;

#घोषणा PHYSDEVOP_manage_pci_add_ext	20
काष्ठा physdev_manage_pci_ext अणु
	/* IN */
	uपूर्णांक8_t bus;
	uपूर्णांक8_t devfn;
	अचिन्हित is_extfn;
	अचिन्हित is_virtfn;
	काष्ठा अणु
		uपूर्णांक8_t bus;
		uपूर्णांक8_t devfn;
	पूर्ण physfn;
पूर्ण;

/*
 * Argument to physdev_op_compat() hypercall. Superceded by new physdev_op()
 * hypercall since 0x00030202.
 */
काष्ठा physdev_op अणु
	uपूर्णांक32_t cmd;
	जोड़ अणु
		काष्ठा physdev_irq_status_query	     irq_status_query;
		काष्ठा physdev_set_iopl		     set_iopl;
		काष्ठा physdev_set_iobiपंचांगap	     set_iobiपंचांगap;
		काष्ठा physdev_apic		     apic_op;
		काष्ठा physdev_irq		     irq_op;
	पूर्ण u;
पूर्ण;

#घोषणा PHYSDEVOP_setup_gsi    21
काष्ठा physdev_setup_gsi अणु
    पूर्णांक gsi;
    /* IN */
    uपूर्णांक8_t triggering;
    /* IN */
    uपूर्णांक8_t polarity;
    /* IN */
पूर्ण;

#घोषणा PHYSDEVOP_get_nr_pirqs    22
काष्ठा physdev_nr_pirqs अणु
    /* OUT */
    uपूर्णांक32_t nr_pirqs;
पूर्ण;

/* type is MAP_PIRQ_TYPE_GSI or MAP_PIRQ_TYPE_MSI
 * the hypercall वापसs a मुक्त pirq */
#घोषणा PHYSDEVOP_get_मुक्त_pirq    23
काष्ठा physdev_get_मुक्त_pirq अणु
    /* IN */ 
    पूर्णांक type;
    /* OUT */
    uपूर्णांक32_t pirq;
पूर्ण;

#घोषणा XEN_PCI_DEV_EXTFN              0x1
#घोषणा XEN_PCI_DEV_VIRTFN             0x2
#घोषणा XEN_PCI_DEV_PXM                0x4

#घोषणा XEN_PCI_MMCFG_RESERVED         0x1

#घोषणा PHYSDEVOP_pci_mmcfg_reserved    24
काष्ठा physdev_pci_mmcfg_reserved अणु
    uपूर्णांक64_t address;
    uपूर्णांक16_t segment;
    uपूर्णांक8_t start_bus;
    uपूर्णांक8_t end_bus;
    uपूर्णांक32_t flags;
पूर्ण;

#घोषणा PHYSDEVOP_pci_device_add        25
काष्ठा physdev_pci_device_add अणु
    /* IN */
    uपूर्णांक16_t seg;
    uपूर्णांक8_t bus;
    uपूर्णांक8_t devfn;
    uपूर्णांक32_t flags;
    काष्ठा अणु
        uपूर्णांक8_t bus;
        uपूर्णांक8_t devfn;
    पूर्ण physfn;
#अगर defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    uपूर्णांक32_t optarr[];
#या_अगर defined(__GNUC__)
    uपूर्णांक32_t optarr[0];
#पूर्ण_अगर
पूर्ण;

#घोषणा PHYSDEVOP_pci_device_हटाओ     26
#घोषणा PHYSDEVOP_restore_msi_ext       27
/*
 * Dom0 should use these two to announce MMIO resources asचिन्हित to
 * MSI-X capable devices won't (prepare) or may (release) change.
 */
#घोषणा PHYSDEVOP_prepare_msix          30
#घोषणा PHYSDEVOP_release_msix          31
काष्ठा physdev_pci_device अणु
    /* IN */
    uपूर्णांक16_t seg;
    uपूर्णांक8_t bus;
    uपूर्णांक8_t devfn;
पूर्ण;

#घोषणा PHYSDEVOP_DBGP_RESET_PREPARE    1
#घोषणा PHYSDEVOP_DBGP_RESET_DONE       2

#घोषणा PHYSDEVOP_DBGP_BUS_UNKNOWN      0
#घोषणा PHYSDEVOP_DBGP_BUS_PCI          1

#घोषणा PHYSDEVOP_dbgp_op               29
काष्ठा physdev_dbgp_op अणु
    /* IN */
    uपूर्णांक8_t op;
    uपूर्णांक8_t bus;
    जोड़ अणु
        काष्ठा physdev_pci_device pci;
    पूर्ण u;
पूर्ण;

/*
 * Notअगरy that some PIRQ-bound event channels have been unmasked.
 * ** This command is obsolete since पूर्णांकerface version 0x00030202 and is **
 * ** unsupported by newer versions of Xen.				 **
 */
#घोषणा PHYSDEVOP_IRQ_UNMASK_NOTIFY	 4

/*
 * These all-capitals physdev operation names are superceded by the new names
 * (defined above) since पूर्णांकerface version 0x00030202.
 */
#घोषणा PHYSDEVOP_IRQ_STATUS_QUERY	 PHYSDEVOP_irq_status_query
#घोषणा PHYSDEVOP_SET_IOPL		 PHYSDEVOP_set_iopl
#घोषणा PHYSDEVOP_SET_IOBITMAP		 PHYSDEVOP_set_iobiपंचांगap
#घोषणा PHYSDEVOP_APIC_READ		 PHYSDEVOP_apic_पढ़ो
#घोषणा PHYSDEVOP_APIC_WRITE		 PHYSDEVOP_apic_ग_लिखो
#घोषणा PHYSDEVOP_ASSIGN_VECTOR		 PHYSDEVOP_alloc_irq_vector
#घोषणा PHYSDEVOP_FREE_VECTOR		 PHYSDEVOP_मुक्त_irq_vector
#घोषणा PHYSDEVOP_IRQ_NEEDS_UNMASK_NOTIFY XENIRQSTAT_needs_eoi
#घोषणा PHYSDEVOP_IRQ_SHARED		 XENIRQSTAT_shared

#पूर्ण_अगर /* __XEN_PUBLIC_PHYSDEV_H__ */
