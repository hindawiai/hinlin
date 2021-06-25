<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EEH functionality support क्रम VFIO devices. The feature is only
 * available on sPAPR compatible platक्रमms.
 *
 * Copyright Gavin Shan, IBM Corporation 2014.
 */

#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>
#समावेश <यंत्र/eeh.h>

#घोषणा DRIVER_VERSION	"0.1"
#घोषणा DRIVER_AUTHOR	"Gavin Shan, IBM Corporation"
#घोषणा DRIVER_DESC	"VFIO IOMMU SPAPR EEH"

/* We might build address mapping here क्रम "fast" path later */
व्योम vfio_spapr_pci_eeh_खोलो(काष्ठा pci_dev *pdev)
अणु
	eeh_dev_खोलो(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_spapr_pci_eeh_खोलो);

व्योम vfio_spapr_pci_eeh_release(काष्ठा pci_dev *pdev)
अणु
	eeh_dev_release(pdev);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_spapr_pci_eeh_release);

दीर्घ vfio_spapr_iommu_eeh_ioctl(काष्ठा iommu_group *group,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा eeh_pe *pe;
	काष्ठा vfio_eeh_pe_op op;
	अचिन्हित दीर्घ minsz;
	दीर्घ ret = -EINVAL;

	चयन (cmd) अणु
	हाल VFIO_CHECK_EXTENSION:
		अगर (arg == VFIO_EEH)
			ret = eeh_enabled() ? 1 : 0;
		अन्यथा
			ret = 0;
		अवरोध;
	हाल VFIO_EEH_PE_OP:
		pe = eeh_iommu_group_to_pe(group);
		अगर (!pe)
			वापस -ENODEV;

		minsz = दुरत्वend(काष्ठा vfio_eeh_pe_op, op);
		अगर (copy_from_user(&op, (व्योम __user *)arg, minsz))
			वापस -EFAULT;
		अगर (op.argsz < minsz || op.flags)
			वापस -EINVAL;

		चयन (op.op) अणु
		हाल VFIO_EEH_PE_DISABLE:
			ret = eeh_pe_set_option(pe, EEH_OPT_DISABLE);
			अवरोध;
		हाल VFIO_EEH_PE_ENABLE:
			ret = eeh_pe_set_option(pe, EEH_OPT_ENABLE);
			अवरोध;
		हाल VFIO_EEH_PE_UNFREEZE_IO:
			ret = eeh_pe_set_option(pe, EEH_OPT_THAW_MMIO);
			अवरोध;
		हाल VFIO_EEH_PE_UNFREEZE_DMA:
			ret = eeh_pe_set_option(pe, EEH_OPT_THAW_DMA);
			अवरोध;
		हाल VFIO_EEH_PE_GET_STATE:
			ret = eeh_pe_get_state(pe);
			अवरोध;
		हाल VFIO_EEH_PE_RESET_DEACTIVATE:
			ret = eeh_pe_reset(pe, EEH_RESET_DEACTIVATE, true);
			अवरोध;
		हाल VFIO_EEH_PE_RESET_HOT:
			ret = eeh_pe_reset(pe, EEH_RESET_HOT, true);
			अवरोध;
		हाल VFIO_EEH_PE_RESET_FUNDAMENTAL:
			ret = eeh_pe_reset(pe, EEH_RESET_FUNDAMENTAL, true);
			अवरोध;
		हाल VFIO_EEH_PE_CONFIGURE:
			ret = eeh_pe_configure(pe);
			अवरोध;
		हाल VFIO_EEH_PE_INJECT_ERR:
			minsz = दुरत्वend(काष्ठा vfio_eeh_pe_op, err.mask);
			अगर (op.argsz < minsz)
				वापस -EINVAL;
			अगर (copy_from_user(&op, (व्योम __user *)arg, minsz))
				वापस -EFAULT;

			ret = eeh_pe_inject_err(pe, op.err.type, op.err.func,
						op.err.addr, op.err.mask);
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_spapr_iommu_eeh_ioctl);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
