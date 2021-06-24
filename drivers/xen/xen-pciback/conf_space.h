<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PCI Backend - Common data काष्ठाures क्रम overriding the configuration space
 *
 * Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#अगर_अघोषित __XEN_PCIBACK_CONF_SPACE_H__
#घोषणा __XEN_PCIBACK_CONF_SPACE_H__

#समावेश <linux/list.h>
#समावेश <linux/err.h>

/* conf_field_init can वापस an त्रुटि_सं in a ptr with ERR_PTR() */
प्रकार व्योम *(*conf_field_init) (काष्ठा pci_dev *dev, पूर्णांक offset);
प्रकार व्योम (*conf_field_reset) (काष्ठा pci_dev *dev, पूर्णांक offset, व्योम *data);
प्रकार व्योम (*conf_field_मुक्त) (काष्ठा pci_dev *dev, पूर्णांक offset, व्योम *data);

प्रकार पूर्णांक (*conf_dword_ग_लिखो) (काष्ठा pci_dev *dev, पूर्णांक offset, u32 value,
				 व्योम *data);
प्रकार पूर्णांक (*conf_word_ग_लिखो) (काष्ठा pci_dev *dev, पूर्णांक offset, u16 value,
				व्योम *data);
प्रकार पूर्णांक (*conf_byte_ग_लिखो) (काष्ठा pci_dev *dev, पूर्णांक offset, u8 value,
				व्योम *data);
प्रकार पूर्णांक (*conf_dword_पढ़ो) (काष्ठा pci_dev *dev, पूर्णांक offset, u32 *value,
				व्योम *data);
प्रकार पूर्णांक (*conf_word_पढ़ो) (काष्ठा pci_dev *dev, पूर्णांक offset, u16 *value,
			       व्योम *data);
प्रकार पूर्णांक (*conf_byte_पढ़ो) (काष्ठा pci_dev *dev, पूर्णांक offset, u8 *value,
			       व्योम *data);

/* These are the fields within the configuration space which we
 * are पूर्णांकerested in पूर्णांकercepting पढ़ोs/ग_लिखोs to and changing their
 * values.
 */
काष्ठा config_field अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक mask;
	conf_field_init init;
	conf_field_reset reset;
	conf_field_मुक्त release;
	व्योम (*clean) (काष्ठा config_field *field);
	जोड़ अणु
		काष्ठा अणु
			conf_dword_ग_लिखो ग_लिखो;
			conf_dword_पढ़ो पढ़ो;
		पूर्ण dw;
		काष्ठा अणु
			conf_word_ग_लिखो ग_लिखो;
			conf_word_पढ़ो पढ़ो;
		पूर्ण w;
		काष्ठा अणु
			conf_byte_ग_लिखो ग_लिखो;
			conf_byte_पढ़ो पढ़ो;
		पूर्ण b;
	पूर्ण u;
	काष्ठा list_head list;
पूर्ण;

काष्ठा config_field_entry अणु
	काष्ठा list_head list;
	स्थिर काष्ठा config_field *field;
	अचिन्हित पूर्णांक base_offset;
	व्योम *data;
पूर्ण;

#घोषणा INTERRUPT_TYPE_NONE (0)
#घोषणा INTERRUPT_TYPE_INTX (1<<0)
#घोषणा INTERRUPT_TYPE_MSI  (1<<1)
#घोषणा INTERRUPT_TYPE_MSIX (1<<2)

बाह्य bool xen_pcibk_permissive;

#घोषणा OFFSET(cfg_entry) ((cfg_entry)->base_offset+(cfg_entry)->field->offset)

/* Add fields to a device - the add_fields macro expects to get a poपूर्णांकer to
 * the first entry in an array (of which the ending is marked by size==0)
 */
पूर्णांक xen_pcibk_config_add_field_offset(काष्ठा pci_dev *dev,
				    स्थिर काष्ठा config_field *field,
				    अचिन्हित पूर्णांक offset);

अटल अंतरभूत पूर्णांक xen_pcibk_config_add_field(काष्ठा pci_dev *dev,
					   स्थिर काष्ठा config_field *field)
अणु
	वापस xen_pcibk_config_add_field_offset(dev, field, 0);
पूर्ण

अटल अंतरभूत पूर्णांक xen_pcibk_config_add_fields(काष्ठा pci_dev *dev,
					    स्थिर काष्ठा config_field *field)
अणु
	पूर्णांक i, err = 0;
	क्रम (i = 0; field[i].size != 0; i++) अणु
		err = xen_pcibk_config_add_field(dev, &field[i]);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक xen_pcibk_config_add_fields_offset(काष्ठा pci_dev *dev,
					स्थिर काष्ठा config_field *field,
					अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक i, err = 0;
	क्रम (i = 0; field[i].size != 0; i++) अणु
		err = xen_pcibk_config_add_field_offset(dev, &field[i], offset);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/* Read/Write the real configuration space */
पूर्णांक xen_pcibk_पढ़ो_config_byte(काष्ठा pci_dev *dev, पूर्णांक offset, u8 *value,
			       व्योम *data);
पूर्णांक xen_pcibk_पढ़ो_config_word(काष्ठा pci_dev *dev, पूर्णांक offset, u16 *value,
			       व्योम *data);
पूर्णांक xen_pcibk_पढ़ो_config_dword(काष्ठा pci_dev *dev, पूर्णांक offset, u32 *value,
				व्योम *data);
पूर्णांक xen_pcibk_ग_लिखो_config_byte(काष्ठा pci_dev *dev, पूर्णांक offset, u8 value,
				 व्योम *data);
पूर्णांक xen_pcibk_ग_लिखो_config_word(काष्ठा pci_dev *dev, पूर्णांक offset, u16 value,
				व्योम *data);
पूर्णांक xen_pcibk_ग_लिखो_config_dword(काष्ठा pci_dev *dev, पूर्णांक offset, u32 value,
				 व्योम *data);

पूर्णांक xen_pcibk_config_capability_init(व्योम);

पूर्णांक xen_pcibk_config_header_add_fields(काष्ठा pci_dev *dev);
पूर्णांक xen_pcibk_config_capability_add_fields(काष्ठा pci_dev *dev);

पूर्णांक xen_pcibk_get_पूर्णांकerrupt_type(काष्ठा pci_dev *dev);

#पूर्ण_अगर				/* __XEN_PCIBACK_CONF_SPACE_H__ */
