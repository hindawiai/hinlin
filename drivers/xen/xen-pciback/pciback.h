<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PCI Backend Common Data Structures & Function Declarations
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */
#अगर_अघोषित __XEN_PCIBACK_H__
#घोषणा __XEN_PCIBACK_H__

#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <xen/xenbus.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/atomic.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/io/pciअगर.h>

#घोषणा DRV_NAME	"xen-pciback"

काष्ठा pci_dev_entry अणु
	काष्ठा list_head list;
	काष्ठा pci_dev *dev;
पूर्ण;

#घोषणा _PDEVF_op_active	(0)
#घोषणा PDEVF_op_active		(1<<(_PDEVF_op_active))
#घोषणा _PCIB_op_pending	(1)
#घोषणा PCIB_op_pending		(1<<(_PCIB_op_pending))
#घोषणा _EOI_pending		(2)
#घोषणा EOI_pending		(1<<(_EOI_pending))

काष्ठा xen_pcibk_device अणु
	व्योम *pci_dev_data;
	काष्ठा mutex dev_lock;
	काष्ठा xenbus_device *xdev;
	काष्ठा xenbus_watch be_watch;
	u8 be_watching;
	पूर्णांक evtchn_irq;
	काष्ठा xen_pci_sharedinfo *sh_info;
	अचिन्हित दीर्घ flags;
	काष्ठा work_काष्ठा op_work;
	काष्ठा xen_pci_op op;
पूर्ण;

काष्ठा xen_pcibk_dev_data अणु
	काष्ठा list_head config_fields;
	काष्ठा pci_saved_state *pci_saved_state;
	अचिन्हित पूर्णांक permissive:1;
	अचिन्हित पूर्णांक allow_पूर्णांकerrupt_control:1;
	अचिन्हित पूर्णांक warned_on_ग_लिखो:1;
	अचिन्हित पूर्णांक enable_पूर्णांकx:1;
	अचिन्हित पूर्णांक isr_on:1; /* Whether the IRQ handler is installed. */
	अचिन्हित पूर्णांक ack_पूर्णांकr:1; /* .. and ACK-ing */
	अचिन्हित दीर्घ handled;
	अचिन्हित पूर्णांक irq; /* Saved in हाल device transitions to MSI/MSI-X */
	अक्षर irq_name[]; /* xen-pcibk[000:04:00.0] */
पूर्ण;

/* Used by XenBus and xen_pcibk_ops.c */
बाह्य रुको_queue_head_t xen_pcibk_aer_रुको_queue;
/* Used by pcistub.c and conf_space_quirks.c */
बाह्य काष्ठा list_head xen_pcibk_quirks;

/* Get/Put PCI Devices that are hidden from the PCI Backend Doमुख्य */
काष्ठा pci_dev *pcistub_get_pci_dev_by_slot(काष्ठा xen_pcibk_device *pdev,
					    पूर्णांक करोमुख्य, पूर्णांक bus,
					    पूर्णांक slot, पूर्णांक func);
काष्ठा pci_dev *pcistub_get_pci_dev(काष्ठा xen_pcibk_device *pdev,
				    काष्ठा pci_dev *dev);
व्योम pcistub_put_pci_dev(काष्ठा pci_dev *dev);

/* Ensure a device is turned off or reset */
व्योम xen_pcibk_reset_device(काष्ठा pci_dev *pdev);

/* Access a भव configuration space क्रम a PCI device */
पूर्णांक xen_pcibk_config_init(व्योम);
पूर्णांक xen_pcibk_config_init_dev(काष्ठा pci_dev *dev);
व्योम xen_pcibk_config_मुक्त_dyn_fields(काष्ठा pci_dev *dev);
व्योम xen_pcibk_config_reset_dev(काष्ठा pci_dev *dev);
व्योम xen_pcibk_config_मुक्त_dev(काष्ठा pci_dev *dev);
पूर्णांक xen_pcibk_config_पढ़ो(काष्ठा pci_dev *dev, पूर्णांक offset, पूर्णांक size,
			  u32 *ret_val);
पूर्णांक xen_pcibk_config_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, पूर्णांक size,
			   u32 value);

/* Handle requests क्रम specअगरic devices from the frontend */
प्रकार पूर्णांक (*publish_pci_dev_cb) (काष्ठा xen_pcibk_device *pdev,
				   अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
				   अचिन्हित पूर्णांक devfn, अचिन्हित पूर्णांक devid);
प्रकार पूर्णांक (*publish_pci_root_cb) (काष्ठा xen_pcibk_device *pdev,
				    अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus);

/* Backend registration क्रम the two types of BDF representation:
 *  vpci - BDFs start at 00
 *  passthrough - BDFs are exactly like in the host.
 */
काष्ठा xen_pcibk_backend अणु
	स्थिर अक्षर *name;
	पूर्णांक (*init)(काष्ठा xen_pcibk_device *pdev);
	व्योम (*मुक्त)(काष्ठा xen_pcibk_device *pdev);
	पूर्णांक (*find)(काष्ठा pci_dev *pcidev, काष्ठा xen_pcibk_device *pdev,
		    अचिन्हित पूर्णांक *करोमुख्य, अचिन्हित पूर्णांक *bus,
		    अचिन्हित पूर्णांक *devfn);
	पूर्णांक (*publish)(काष्ठा xen_pcibk_device *pdev, publish_pci_root_cb cb);
	व्योम (*release)(काष्ठा xen_pcibk_device *pdev, काष्ठा pci_dev *dev,
                        bool lock);
	पूर्णांक (*add)(काष्ठा xen_pcibk_device *pdev, काष्ठा pci_dev *dev,
		   पूर्णांक devid, publish_pci_dev_cb publish_cb);
	काष्ठा pci_dev *(*get)(काष्ठा xen_pcibk_device *pdev,
			       अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
			       अचिन्हित पूर्णांक devfn);
पूर्ण;

बाह्य स्थिर काष्ठा xen_pcibk_backend xen_pcibk_vpci_backend;
बाह्य स्थिर काष्ठा xen_pcibk_backend xen_pcibk_passthrough_backend;
बाह्य स्थिर काष्ठा xen_pcibk_backend *xen_pcibk_backend;

अटल अंतरभूत पूर्णांक xen_pcibk_add_pci_dev(काष्ठा xen_pcibk_device *pdev,
					काष्ठा pci_dev *dev,
					पूर्णांक devid,
					publish_pci_dev_cb publish_cb)
अणु
	अगर (xen_pcibk_backend && xen_pcibk_backend->add)
		वापस xen_pcibk_backend->add(pdev, dev, devid, publish_cb);
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम xen_pcibk_release_pci_dev(काष्ठा xen_pcibk_device *pdev,
					     काष्ठा pci_dev *dev, bool lock)
अणु
	अगर (xen_pcibk_backend && xen_pcibk_backend->release)
		वापस xen_pcibk_backend->release(pdev, dev, lock);
पूर्ण

अटल अंतरभूत काष्ठा pci_dev *
xen_pcibk_get_pci_dev(काष्ठा xen_pcibk_device *pdev, अचिन्हित पूर्णांक करोमुख्य,
		      अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn)
अणु
	अगर (xen_pcibk_backend && xen_pcibk_backend->get)
		वापस xen_pcibk_backend->get(pdev, करोमुख्य, bus, devfn);
	वापस शून्य;
पूर्ण

/**
* Add क्रम करोमुख्य0 PCIE-AER handling. Get guest करोमुख्य/bus/devfn in xen_pcibk
* beक्रमe sending aer request to pcअगरront, so that guest could identअगरy
* device, coopearte with xen_pcibk to finish aer recovery job अगर device driver
* has the capability
*/
अटल अंतरभूत पूर्णांक xen_pcibk_get_pcअगरront_dev(काष्ठा pci_dev *pcidev,
					     काष्ठा xen_pcibk_device *pdev,
					     अचिन्हित पूर्णांक *करोमुख्य,
					     अचिन्हित पूर्णांक *bus,
					     अचिन्हित पूर्णांक *devfn)
अणु
	अगर (xen_pcibk_backend && xen_pcibk_backend->find)
		वापस xen_pcibk_backend->find(pcidev, pdev, करोमुख्य, bus,
					       devfn);
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक xen_pcibk_init_devices(काष्ठा xen_pcibk_device *pdev)
अणु
	अगर (xen_pcibk_backend && xen_pcibk_backend->init)
		वापस xen_pcibk_backend->init(pdev);
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक xen_pcibk_publish_pci_roots(काष्ठा xen_pcibk_device *pdev,
					      publish_pci_root_cb cb)
अणु
	अगर (xen_pcibk_backend && xen_pcibk_backend->publish)
		वापस xen_pcibk_backend->publish(pdev, cb);
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम xen_pcibk_release_devices(काष्ठा xen_pcibk_device *pdev)
अणु
	अगर (xen_pcibk_backend && xen_pcibk_backend->मुक्त)
		वापस xen_pcibk_backend->मुक्त(pdev);
पूर्ण

/* Handles events from front-end */
irqवापस_t xen_pcibk_handle_event(पूर्णांक irq, व्योम *dev_id);
व्योम xen_pcibk_करो_op(काष्ठा work_काष्ठा *data);

अटल अंतरभूत व्योम xen_pcibk_lateeoi(काष्ठा xen_pcibk_device *pdev,
				     अचिन्हित पूर्णांक eoi_flag)
अणु
	अगर (test_and_clear_bit(_EOI_pending, &pdev->flags))
		xen_irq_lateeoi(pdev->evtchn_irq, eoi_flag);
पूर्ण

पूर्णांक xen_pcibk_xenbus_रेजिस्टर(व्योम);
व्योम xen_pcibk_xenbus_unरेजिस्टर(व्योम);
#पूर्ण_अगर

/* Handles shared IRQs that can to device करोमुख्य and control करोमुख्य. */
व्योम xen_pcibk_irq_handler(काष्ठा pci_dev *dev, पूर्णांक reset);
