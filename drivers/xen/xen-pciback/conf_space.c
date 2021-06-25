<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend - Functions क्रम creating a भव configuration space क्रम
 *               exported PCI Devices.
 *               It's dangerous to allow PCI Driver Doमुख्यs to change their
 *               device's resources (memory, i/o ports, पूर्णांकerrupts). We need to
 *               restrict changes to certain PCI Configuration रेजिस्टरs:
 *               BARs, INTERRUPT_PIN, most रेजिस्टरs in the header...
 *
 * Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#घोषणा dev_fmt(fmt) DRV_NAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश "pciback.h"
#समावेश "conf_space.h"
#समावेश "conf_space_quirks.h"

bool xen_pcibk_permissive;
module_param_named(permissive, xen_pcibk_permissive, bool, 0644);

/* This is where xen_pcibk_पढ़ो_config_byte, xen_pcibk_पढ़ो_config_word,
 * xen_pcibk_ग_लिखो_config_word, and xen_pcibk_ग_लिखो_config_byte are created. */
#घोषणा DEFINE_PCI_CONFIG(op, size, type)			\
पूर्णांक xen_pcibk_##op##_config_##size				\
(काष्ठा pci_dev *dev, पूर्णांक offset, type value, व्योम *data)	\
अणु								\
	वापस pci_##op##_config_##size(dev, offset, value);	\
पूर्ण

DEFINE_PCI_CONFIG(पढ़ो, byte, u8 *)
DEFINE_PCI_CONFIG(पढ़ो, word, u16 *)
DEFINE_PCI_CONFIG(पढ़ो, dword, u32 *)

DEFINE_PCI_CONFIG(ग_लिखो, byte, u8)
DEFINE_PCI_CONFIG(ग_लिखो, word, u16)
DEFINE_PCI_CONFIG(ग_लिखो, dword, u32)

अटल पूर्णांक conf_space_पढ़ो(काष्ठा pci_dev *dev,
			   स्थिर काष्ठा config_field_entry *entry,
			   पूर्णांक offset, u32 *value)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा config_field *field = entry->field;

	*value = 0;

	चयन (field->size) अणु
	हाल 1:
		अगर (field->u.b.पढ़ो)
			ret = field->u.b.पढ़ो(dev, offset, (u8 *) value,
					      entry->data);
		अवरोध;
	हाल 2:
		अगर (field->u.w.पढ़ो)
			ret = field->u.w.पढ़ो(dev, offset, (u16 *) value,
					      entry->data);
		अवरोध;
	हाल 4:
		अगर (field->u.dw.पढ़ो)
			ret = field->u.dw.पढ़ो(dev, offset, value, entry->data);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक conf_space_ग_लिखो(काष्ठा pci_dev *dev,
			    स्थिर काष्ठा config_field_entry *entry,
			    पूर्णांक offset, u32 value)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा config_field *field = entry->field;

	चयन (field->size) अणु
	हाल 1:
		अगर (field->u.b.ग_लिखो)
			ret = field->u.b.ग_लिखो(dev, offset, (u8) value,
					       entry->data);
		अवरोध;
	हाल 2:
		अगर (field->u.w.ग_लिखो)
			ret = field->u.w.ग_लिखो(dev, offset, (u16) value,
					       entry->data);
		अवरोध;
	हाल 4:
		अगर (field->u.dw.ग_लिखो)
			ret = field->u.dw.ग_लिखो(dev, offset, value,
						entry->data);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत u32 get_mask(पूर्णांक size)
अणु
	अगर (size == 1)
		वापस 0xff;
	अन्यथा अगर (size == 2)
		वापस 0xffff;
	अन्यथा
		वापस 0xffffffff;
पूर्ण

अटल अंतरभूत पूर्णांक valid_request(पूर्णांक offset, पूर्णांक size)
अणु
	/* Validate request (no un-aligned requests) */
	अगर ((size == 1 || size == 2 || size == 4) && (offset % size) == 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत u32 merge_value(u32 val, u32 new_val, u32 new_val_mask,
			      पूर्णांक offset)
अणु
	अगर (offset >= 0) अणु
		new_val_mask <<= (offset * 8);
		new_val <<= (offset * 8);
	पूर्ण अन्यथा अणु
		new_val_mask >>= (offset * -8);
		new_val >>= (offset * -8);
	पूर्ण
	val = (val & ~new_val_mask) | (new_val & new_val_mask);

	वापस val;
पूर्ण

अटल पूर्णांक xen_pcibios_err_to_त्रुटि_सं(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल PCIBIOS_SUCCESSFUL:
		वापस XEN_PCI_ERR_success;
	हाल PCIBIOS_DEVICE_NOT_FOUND:
		वापस XEN_PCI_ERR_dev_not_found;
	हाल PCIBIOS_BAD_REGISTER_NUMBER:
		वापस XEN_PCI_ERR_invalid_offset;
	हाल PCIBIOS_FUNC_NOT_SUPPORTED:
		वापस XEN_PCI_ERR_not_implemented;
	हाल PCIBIOS_SET_FAILED:
		वापस XEN_PCI_ERR_access_denied;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक xen_pcibk_config_पढ़ो(काष्ठा pci_dev *dev, पूर्णांक offset, पूर्णांक size,
			  u32 *ret_val)
अणु
	पूर्णांक err = 0;
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	स्थिर काष्ठा config_field_entry *cfg_entry;
	स्थिर काष्ठा config_field *field;
	पूर्णांक field_start, field_end;
	/* अगर पढ़ो fails क्रम any reason, वापस 0
	 * (as अगर device didn't respond) */
	u32 value = 0, पंचांगp_val;

	dev_dbg(&dev->dev, "read %d bytes at 0x%x\n", size, offset);

	अगर (!valid_request(offset, size)) अणु
		err = XEN_PCI_ERR_invalid_offset;
		जाओ out;
	पूर्ण

	/* Get the real value first, then modअगरy as appropriate */
	चयन (size) अणु
	हाल 1:
		err = pci_पढ़ो_config_byte(dev, offset, (u8 *) &value);
		अवरोध;
	हाल 2:
		err = pci_पढ़ो_config_word(dev, offset, (u16 *) &value);
		अवरोध;
	हाल 4:
		err = pci_पढ़ो_config_dword(dev, offset, &value);
		अवरोध;
	पूर्ण

	list_क्रम_each_entry(cfg_entry, &dev_data->config_fields, list) अणु
		field = cfg_entry->field;

		field_start = OFFSET(cfg_entry);
		field_end = OFFSET(cfg_entry) + field->size;

		अगर (offset + size > field_start && field_end > offset) अणु
			err = conf_space_पढ़ो(dev, cfg_entry, field_start,
					      &पंचांगp_val);
			अगर (err)
				जाओ out;

			value = merge_value(value, पंचांगp_val,
					    get_mask(field->size),
					    field_start - offset);
		पूर्ण
	पूर्ण

out:
	dev_dbg(&dev->dev, "read %d bytes at 0x%x = %x\n", size, offset, value);

	*ret_val = value;
	वापस xen_pcibios_err_to_त्रुटि_सं(err);
पूर्ण

पूर्णांक xen_pcibk_config_ग_लिखो(काष्ठा pci_dev *dev, पूर्णांक offset, पूर्णांक size, u32 value)
अणु
	पूर्णांक err = 0, handled = 0;
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	स्थिर काष्ठा config_field_entry *cfg_entry;
	स्थिर काष्ठा config_field *field;
	u32 पंचांगp_val;
	पूर्णांक field_start, field_end;

	dev_dbg(&dev->dev, "write request %d bytes at 0x%x = %x\n",
		size, offset, value);

	अगर (!valid_request(offset, size))
		वापस XEN_PCI_ERR_invalid_offset;

	list_क्रम_each_entry(cfg_entry, &dev_data->config_fields, list) अणु
		field = cfg_entry->field;

		field_start = OFFSET(cfg_entry);
		field_end = OFFSET(cfg_entry) + field->size;

		अगर (offset + size > field_start && field_end > offset) अणु
			err = conf_space_पढ़ो(dev, cfg_entry, field_start,
					      &पंचांगp_val);
			अगर (err)
				अवरोध;

			पंचांगp_val = merge_value(पंचांगp_val, value, get_mask(size),
					      offset - field_start);

			err = conf_space_ग_लिखो(dev, cfg_entry, field_start,
					       पंचांगp_val);

			/* handled is set true here, but not every byte
			 * may have been written! Properly detecting अगर
			 * every byte is handled is unnecessary as the
			 * flag is used to detect devices that need
			 * special helpers to work correctly.
			 */
			handled = 1;
		पूर्ण
	पूर्ण

	अगर (!handled && !err) अणु
		/* By शेष, anything not specअगरicially handled above is
		 * पढ़ो-only. The permissive flag changes this behavior so
		 * that anything not specअगरically handled above is writable.
		 * This means that some fields may still be पढ़ो-only because
		 * they have entries in the config_field list that पूर्णांकercept
		 * the ग_लिखो and करो nothing. */
		अगर (dev_data->permissive || xen_pcibk_permissive) अणु
			चयन (size) अणु
			हाल 1:
				err = pci_ग_लिखो_config_byte(dev, offset,
							    (u8) value);
				अवरोध;
			हाल 2:
				err = pci_ग_लिखो_config_word(dev, offset,
							    (u16) value);
				अवरोध;
			हाल 4:
				err = pci_ग_लिखो_config_dword(dev, offset,
							     (u32) value);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (!dev_data->warned_on_ग_लिखो) अणु
			dev_data->warned_on_ग_लिखो = 1;
			dev_warn(&dev->dev, "Driver tried to write to a "
				 "read-only configuration space field at offset"
				 " 0x%x, size %d. This may be harmless, but if "
				 "you have problems with your device:\n"
				 "1) see permissive attribute in sysfs\n"
				 "2) report problems to the xen-devel "
				 "mailing list along with details of your "
				 "device obtained from lspci.\n", offset, size);
		पूर्ण
	पूर्ण

	वापस xen_pcibios_err_to_त्रुटि_सं(err);
पूर्ण

पूर्णांक xen_pcibk_get_पूर्णांकerrupt_type(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err;
	u16 val;
	पूर्णांक ret = 0;

	err = pci_पढ़ो_config_word(dev, PCI_COMMAND, &val);
	अगर (err)
		वापस err;
	अगर (!(val & PCI_COMMAND_INTX_DISABLE))
		ret |= INTERRUPT_TYPE_INTX;

	/*
	 * Do not trust dev->msi(x)_enabled here, as enabling could be करोne
	 * bypassing the pci_*msi* functions, by the qemu.
	 */
	अगर (dev->msi_cap) अणु
		err = pci_पढ़ो_config_word(dev,
				dev->msi_cap + PCI_MSI_FLAGS,
				&val);
		अगर (err)
			वापस err;
		अगर (val & PCI_MSI_FLAGS_ENABLE)
			ret |= INTERRUPT_TYPE_MSI;
	पूर्ण
	अगर (dev->msix_cap) अणु
		err = pci_पढ़ो_config_word(dev,
				dev->msix_cap + PCI_MSIX_FLAGS,
				&val);
		अगर (err)
			वापस err;
		अगर (val & PCI_MSIX_FLAGS_ENABLE)
			ret |= INTERRUPT_TYPE_MSIX;
	पूर्ण
	वापस ret ?: INTERRUPT_TYPE_NONE;
पूर्ण

व्योम xen_pcibk_config_मुक्त_dyn_fields(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	काष्ठा config_field_entry *cfg_entry, *t;
	स्थिर काष्ठा config_field *field;

	dev_dbg(&dev->dev, "free-ing dynamically allocated virtual "
			   "configuration space fields\n");
	अगर (!dev_data)
		वापस;

	list_क्रम_each_entry_safe(cfg_entry, t, &dev_data->config_fields, list) अणु
		field = cfg_entry->field;

		अगर (field->clean) अणु
			field->clean((काष्ठा config_field *)field);

			kमुक्त(cfg_entry->data);

			list_del(&cfg_entry->list);
			kमुक्त(cfg_entry);
		पूर्ण

	पूर्ण
पूर्ण

व्योम xen_pcibk_config_reset_dev(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	स्थिर काष्ठा config_field_entry *cfg_entry;
	स्थिर काष्ठा config_field *field;

	dev_dbg(&dev->dev, "resetting virtual configuration space\n");
	अगर (!dev_data)
		वापस;

	list_क्रम_each_entry(cfg_entry, &dev_data->config_fields, list) अणु
		field = cfg_entry->field;

		अगर (field->reset)
			field->reset(dev, OFFSET(cfg_entry), cfg_entry->data);
	पूर्ण
पूर्ण

व्योम xen_pcibk_config_मुक्त_dev(काष्ठा pci_dev *dev)
अणु
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	काष्ठा config_field_entry *cfg_entry, *t;
	स्थिर काष्ठा config_field *field;

	dev_dbg(&dev->dev, "free-ing virtual configuration space fields\n");
	अगर (!dev_data)
		वापस;

	list_क्रम_each_entry_safe(cfg_entry, t, &dev_data->config_fields, list) अणु
		list_del(&cfg_entry->list);

		field = cfg_entry->field;

		अगर (field->release)
			field->release(dev, OFFSET(cfg_entry), cfg_entry->data);

		kमुक्त(cfg_entry);
	पूर्ण
पूर्ण

पूर्णांक xen_pcibk_config_add_field_offset(काष्ठा pci_dev *dev,
				    स्थिर काष्ठा config_field *field,
				    अचिन्हित पूर्णांक base_offset)
अणु
	पूर्णांक err = 0;
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);
	काष्ठा config_field_entry *cfg_entry;
	व्योम *पंचांगp;

	cfg_entry = kदो_स्मृति(माप(*cfg_entry), GFP_KERNEL);
	अगर (!cfg_entry) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg_entry->data = शून्य;
	cfg_entry->field = field;
	cfg_entry->base_offset = base_offset;

	/* silently ignore duplicate fields */
	err = xen_pcibk_field_is_dup(dev, OFFSET(cfg_entry));
	अगर (err)
		जाओ out;

	अगर (field->init) अणु
		पंचांगp = field->init(dev, OFFSET(cfg_entry));

		अगर (IS_ERR(पंचांगp)) अणु
			err = PTR_ERR(पंचांगp);
			जाओ out;
		पूर्ण

		cfg_entry->data = पंचांगp;
	पूर्ण

	dev_dbg(&dev->dev, "added config field at offset 0x%02x\n",
		OFFSET(cfg_entry));
	list_add_tail(&cfg_entry->list, &dev_data->config_fields);

out:
	अगर (err)
		kमुक्त(cfg_entry);

	वापस err;
पूर्ण

/* This sets up the device's भव configuration space to keep track of
 * certain रेजिस्टरs (like the base address रेजिस्टरs (BARs) so that we can
 * keep the client from manipulating them directly.
 */
पूर्णांक xen_pcibk_config_init_dev(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err = 0;
	काष्ठा xen_pcibk_dev_data *dev_data = pci_get_drvdata(dev);

	dev_dbg(&dev->dev, "initializing virtual configuration space\n");

	INIT_LIST_HEAD(&dev_data->config_fields);

	err = xen_pcibk_config_header_add_fields(dev);
	अगर (err)
		जाओ out;

	err = xen_pcibk_config_capability_add_fields(dev);
	अगर (err)
		जाओ out;

	err = xen_pcibk_config_quirks_init(dev);

out:
	वापस err;
पूर्ण

पूर्णांक xen_pcibk_config_init(व्योम)
अणु
	वापस xen_pcibk_config_capability_init();
पूर्ण
