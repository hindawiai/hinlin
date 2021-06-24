<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend - Handles the भव fields found on the capability lists
 *               in the configuration space.
 *
 * Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश "pciback.h"
#समावेश "conf_space.h"

अटल LIST_HEAD(capabilities);
काष्ठा xen_pcibk_config_capability अणु
	काष्ठा list_head cap_list;

	पूर्णांक capability;

	/* If the device has the capability found above, add these fields */
	स्थिर काष्ठा config_field *fields;
पूर्ण;

अटल स्थिर काष्ठा config_field caplist_header[] = अणु
	अणु
	 .offset    = PCI_CAP_LIST_ID,
	 .size      = 2, /* encompass PCI_CAP_LIST_ID & PCI_CAP_LIST_NEXT */
	 .u.w.पढ़ो  = xen_pcibk_पढ़ो_config_word,
	 .u.w.ग_लिखो = शून्य,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत व्योम रेजिस्टर_capability(काष्ठा xen_pcibk_config_capability *cap)
अणु
	list_add_tail(&cap->cap_list, &capabilities);
पूर्ण

पूर्णांक xen_pcibk_config_capability_add_fields(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा xen_pcibk_config_capability *cap;
	पूर्णांक cap_offset;

	list_क्रम_each_entry(cap, &capabilities, cap_list) अणु
		cap_offset = pci_find_capability(dev, cap->capability);
		अगर (cap_offset) अणु
			dev_dbg(&dev->dev, "Found capability 0x%x at 0x%x\n",
				cap->capability, cap_offset);

			err = xen_pcibk_config_add_fields_offset(dev,
							       caplist_header,
							       cap_offset);
			अगर (err)
				जाओ out;
			err = xen_pcibk_config_add_fields_offset(dev,
							       cap->fields,
							       cap_offset);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	वापस err;
पूर्ण

अटल पूर्णांक vpd_address_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, u16 value,
			     व्योम *data)
अणु
	/* Disallow ग_लिखोs to the vital product data */
	अगर (value & PCI_VPD_ADDR_F)
		वापस PCIBIOS_SET_FAILED;
	अन्यथा
		वापस pci_ग_लिखो_config_word(dev, offset, value);
पूर्ण

अटल स्थिर काष्ठा config_field caplist_vpd[] = अणु
	अणु
	 .offset    = PCI_VPD_ADDR,
	 .size      = 2,
	 .u.w.पढ़ो  = xen_pcibk_पढ़ो_config_word,
	 .u.w.ग_लिखो = vpd_address_ग_लिखो,
	 पूर्ण,
	अणु
	 .offset     = PCI_VPD_DATA,
	 .size       = 4,
	 .u.dw.पढ़ो  = xen_pcibk_पढ़ो_config_dword,
	 .u.dw.ग_लिखो = शून्य,
	 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक pm_caps_पढ़ो(काष्ठा pci_dev *dev, पूर्णांक offset, u16 *value,
			व्योम *data)
अणु
	पूर्णांक err;
	u16 real_value;

	err = pci_पढ़ो_config_word(dev, offset, &real_value);
	अगर (err)
		जाओ out;

	*value = real_value & ~PCI_PM_CAP_PME_MASK;

out:
	वापस err;
पूर्ण

/* PM_OK_BITS specअगरies the bits that the driver करोमुख्य is allowed to change.
 * Can't allow driver domain to enable PMEs - they're shared */
#घोषणा PM_OK_BITS (PCI_PM_CTRL_PME_STATUS|PCI_PM_CTRL_DATA_SEL_MASK)

अटल पूर्णांक pm_ctrl_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, u16 new_value,
			 व्योम *data)
अणु
	पूर्णांक err;
	u16 old_value;
	pci_घातer_t new_state;

	err = pci_पढ़ो_config_word(dev, offset, &old_value);
	अगर (err)
		जाओ out;

	new_state = (pci_घातer_t)(new_value & PCI_PM_CTRL_STATE_MASK);

	new_value &= PM_OK_BITS;
	अगर ((old_value & PM_OK_BITS) != new_value) अणु
		new_value = (old_value & ~PM_OK_BITS) | new_value;
		err = pci_ग_लिखो_config_word(dev, offset, new_value);
		अगर (err)
			जाओ out;
	पूर्ण

	/* Let pci core handle the घातer management change */
	dev_dbg(&dev->dev, "set power state to %x\n", new_state);
	err = pci_set_घातer_state(dev, new_state);
	अगर (err) अणु
		err = PCIBIOS_SET_FAILED;
		जाओ out;
	पूर्ण

 out:
	वापस err;
पूर्ण

/* Ensure PMEs are disabled */
अटल व्योम *pm_ctrl_init(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	पूर्णांक err;
	u16 value;

	err = pci_पढ़ो_config_word(dev, offset, &value);
	अगर (err)
		जाओ out;

	अगर (value & PCI_PM_CTRL_PME_ENABLE) अणु
		value &= ~PCI_PM_CTRL_PME_ENABLE;
		err = pci_ग_लिखो_config_word(dev, offset, value);
	पूर्ण

out:
	वापस ERR_PTR(err);
पूर्ण

अटल स्थिर काष्ठा config_field caplist_pm[] = अणु
	अणु
		.offset     = PCI_PM_PMC,
		.size       = 2,
		.u.w.पढ़ो   = pm_caps_पढ़ो,
	पूर्ण,
	अणु
		.offset     = PCI_PM_CTRL,
		.size       = 2,
		.init       = pm_ctrl_init,
		.u.w.पढ़ो   = xen_pcibk_पढ़ो_config_word,
		.u.w.ग_लिखो  = pm_ctrl_ग_लिखो,
	पूर्ण,
	अणु
		.offset     = PCI_PM_PPB_EXTENSIONS,
		.size       = 1,
		.u.b.पढ़ो   = xen_pcibk_पढ़ो_config_byte,
	पूर्ण,
	अणु
		.offset     = PCI_PM_DATA_REGISTER,
		.size       = 1,
		.u.b.पढ़ो   = xen_pcibk_पढ़ो_config_byte,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा msi_msix_field_config अणु
	u16          enable_bit; /* bit क्रम enabling MSI/MSI-X */
	अचिन्हित पूर्णांक पूर्णांक_type;   /* पूर्णांकerrupt type क्रम exclusiveness check */
पूर्ण msi_field_config = अणु
	.enable_bit	= PCI_MSI_FLAGS_ENABLE,
	.पूर्णांक_type	= INTERRUPT_TYPE_MSI,
पूर्ण, msix_field_config = अणु
	.enable_bit	= PCI_MSIX_FLAGS_ENABLE,
	.पूर्णांक_type	= INTERRUPT_TYPE_MSIX,
पूर्ण;

अटल व्योम *msi_field_init(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	वापस &msi_field_config;
पूर्ण

अटल व्योम *msix_field_init(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	वापस &msix_field_config;
पूर्ण

अटल पूर्णांक msi_msix_flags_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, u16 new_value,
				व्योम *data)
अणु
	पूर्णांक err;
	u16 old_value;
	स्थिर काष्ठा msi_msix_field_config *field_config = data;
	स्थिर काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);

	अगर (xen_pcibk_permissive || dev_data->permissive)
		जाओ ग_लिखो;

	err = pci_पढ़ो_config_word(dev, offset, &old_value);
	अगर (err)
		वापस err;

	अगर (new_value == old_value)
		वापस 0;

	अगर (!dev_data->allow_पूर्णांकerrupt_control ||
	    (new_value ^ old_value) & ~field_config->enable_bit)
		वापस PCIBIOS_SET_FAILED;

	अगर (new_value & field_config->enable_bit) अणु
		/* करोn't allow enabling together with other पूर्णांकerrupt types */
		पूर्णांक पूर्णांक_type = xen_pcibk_get_पूर्णांकerrupt_type(dev);

		अगर (पूर्णांक_type == INTERRUPT_TYPE_NONE ||
		    पूर्णांक_type == field_config->पूर्णांक_type)
			जाओ ग_लिखो;
		वापस PCIBIOS_SET_FAILED;
	पूर्ण

ग_लिखो:
	वापस pci_ग_लिखो_config_word(dev, offset, new_value);
पूर्ण

अटल स्थिर काष्ठा config_field caplist_msix[] = अणु
	अणु
		.offset    = PCI_MSIX_FLAGS,
		.size      = 2,
		.init      = msix_field_init,
		.u.w.पढ़ो  = xen_pcibk_पढ़ो_config_word,
		.u.w.ग_लिखो = msi_msix_flags_ग_लिखो,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा config_field caplist_msi[] = अणु
	अणु
		.offset    = PCI_MSI_FLAGS,
		.size      = 2,
		.init      = msi_field_init,
		.u.w.पढ़ो  = xen_pcibk_पढ़ो_config_word,
		.u.w.ग_लिखो = msi_msix_flags_ग_लिखो,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा xen_pcibk_config_capability xen_pcibk_config_capability_pm = अणु
	.capability = PCI_CAP_ID_PM,
	.fields = caplist_pm,
पूर्ण;
अटल काष्ठा xen_pcibk_config_capability xen_pcibk_config_capability_vpd = अणु
	.capability = PCI_CAP_ID_VPD,
	.fields = caplist_vpd,
पूर्ण;
अटल काष्ठा xen_pcibk_config_capability xen_pcibk_config_capability_msi = अणु
	.capability = PCI_CAP_ID_MSI,
	.fields = caplist_msi,
पूर्ण;
अटल काष्ठा xen_pcibk_config_capability xen_pcibk_config_capability_msix = अणु
	.capability = PCI_CAP_ID_MSIX,
	.fields = caplist_msix,
पूर्ण;

पूर्णांक xen_pcibk_config_capability_init(व्योम)
अणु
	रेजिस्टर_capability(&xen_pcibk_config_capability_vpd);
	रेजिस्टर_capability(&xen_pcibk_config_capability_pm);
	रेजिस्टर_capability(&xen_pcibk_config_capability_msi);
	रेजिस्टर_capability(&xen_pcibk_config_capability_msix);

	वापस 0;
पूर्ण
