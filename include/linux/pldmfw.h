<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018-2019, Intel Corporation. */

#अगर_अघोषित _PLDMFW_H_
#घोषणा _PLDMFW_H_

#समावेश <linux/list.h>
#समावेश <linux/firmware.h>

#घोषणा PLDM_DEVICE_UPDATE_CONTINUE_AFTER_FAIL BIT(0)

#घोषणा PLDM_STRING_TYPE_UNKNOWN	0
#घोषणा PLDM_STRING_TYPE_ASCII		1
#घोषणा PLDM_STRING_TYPE_UTF8		2
#घोषणा PLDM_STRING_TYPE_UTF16		3
#घोषणा PLDM_STRING_TYPE_UTF16LE	4
#घोषणा PLDM_STRING_TYPE_UTF16BE	5

काष्ठा pldmfw_record अणु
	काष्ठा list_head entry;

	/* List of descriptor TLVs */
	काष्ठा list_head descs;

	/* Component Set version string*/
	स्थिर u8 *version_string;
	u8 version_type;
	u8 version_len;

	/* Package Data length */
	u16 package_data_len;

	/* Bitfield of Device Update Flags */
	u32 device_update_flags;

	/* Package Data block */
	स्थिर u8 *package_data;

	/* Biपंचांगap of components applicable to this record */
	अचिन्हित दीर्घ *component_biपंचांगap;
	u16 component_biपंचांगap_len;
पूर्ण;

/* Standard descriptor TLV identअगरiers */
#घोषणा PLDM_DESC_ID_PCI_VENDOR_ID	0x0000
#घोषणा PLDM_DESC_ID_IANA_ENTERPRISE_ID	0x0001
#घोषणा PLDM_DESC_ID_UUID		0x0002
#घोषणा PLDM_DESC_ID_PNP_VENDOR_ID	0x0003
#घोषणा PLDM_DESC_ID_ACPI_VENDOR_ID	0x0004
#घोषणा PLDM_DESC_ID_PCI_DEVICE_ID	0x0100
#घोषणा PLDM_DESC_ID_PCI_SUBVENDOR_ID	0x0101
#घोषणा PLDM_DESC_ID_PCI_SUBDEV_ID	0x0102
#घोषणा PLDM_DESC_ID_PCI_REVISION_ID	0x0103
#घोषणा PLDM_DESC_ID_PNP_PRODUCT_ID	0x0104
#घोषणा PLDM_DESC_ID_ACPI_PRODUCT_ID	0x0105
#घोषणा PLDM_DESC_ID_VENDOR_DEFINED	0xFFFF

काष्ठा pldmfw_desc_tlv अणु
	काष्ठा list_head entry;

	स्थिर u8 *data;
	u16 type;
	u16 size;
पूर्ण;

#घोषणा PLDM_CLASSIFICATION_UNKNOWN		0x0000
#घोषणा PLDM_CLASSIFICATION_OTHER		0x0001
#घोषणा PLDM_CLASSIFICATION_DRIVER		0x0002
#घोषणा PLDM_CLASSIFICATION_CONFIG_SW		0x0003
#घोषणा PLDM_CLASSIFICATION_APP_SW		0x0004
#घोषणा PLDM_CLASSIFICATION_INSTRUMENTATION	0x0005
#घोषणा PLDM_CLASSIFICATION_BIOS		0x0006
#घोषणा PLDM_CLASSIFICATION_DIAGNOSTIC_SW	0x0007
#घोषणा PLDM_CLASSIFICATION_OS			0x0008
#घोषणा PLDM_CLASSIFICATION_MIDDLEWARE		0x0009
#घोषणा PLDM_CLASSIFICATION_FIRMWARE		0x000A
#घोषणा PLDM_CLASSIFICATION_CODE		0x000B
#घोषणा PLDM_CLASSIFICATION_SERVICE_PACK	0x000C
#घोषणा PLDM_CLASSIFICATION_SOFTWARE_BUNDLE	0x000D

#घोषणा PLDM_ACTIVATION_METHOD_AUTO		BIT(0)
#घोषणा PLDM_ACTIVATION_METHOD_SELF_CONTAINED	BIT(1)
#घोषणा PLDM_ACTIVATION_METHOD_MEDIUM_SPECIFIC	BIT(2)
#घोषणा PLDM_ACTIVATION_METHOD_REBOOT		BIT(3)
#घोषणा PLDM_ACTIVATION_METHOD_DC_CYCLE		BIT(4)
#घोषणा PLDM_ACTIVATION_METHOD_AC_CYCLE		BIT(5)

#घोषणा PLDMFW_COMPONENT_OPTION_FORCE_UPDATE		BIT(0)
#घोषणा PLDMFW_COMPONENT_OPTION_USE_COMPARISON_STAMP	BIT(1)

काष्ठा pldmfw_component अणु
	काष्ठा list_head entry;

	/* component identअगरier */
	u16 classअगरication;
	u16 identअगरier;

	u16 options;
	u16 activation_method;

	u32 comparison_stamp;

	u32 component_size;
	स्थिर u8 *component_data;

	/* Component version string */
	स्थिर u8 *version_string;
	u8 version_type;
	u8 version_len;

	/* component index */
	u8 index;

पूर्ण;

/* Transfer flag used क्रम sending components to the firmware */
#घोषणा PLDM_TRANSFER_FLAG_START		BIT(0)
#घोषणा PLDM_TRANSFER_FLAG_MIDDLE		BIT(1)
#घोषणा PLDM_TRANSFER_FLAG_END			BIT(2)

काष्ठा pldmfw_ops;

/* Main entry poपूर्णांक to the PLDM firmware update engine. Device drivers
 * should embed this in a निजी काष्ठाure and use container_of to obtain
 * a poपूर्णांकer to their own data, used to implement the device specअगरic
 * operations.
 */
काष्ठा pldmfw अणु
	स्थिर काष्ठा pldmfw_ops *ops;
	काष्ठा device *dev;
पूर्ण;

bool pldmfw_op_pci_match_record(काष्ठा pldmfw *context, काष्ठा pldmfw_record *record);

/* Operations invoked by the generic PLDM firmware update engine. Used to
 * implement device specअगरic logic.
 *
 * @match_record: check अगर the device matches the given record. For
 * convenience, a standard implementation is provided क्रम PCI devices.
 *
 * @send_package_data: send the package data associated with the matching
 * record to firmware.
 *
 * @send_component_table: send the component data associated with a given
 * component to firmware. Called once क्रम each applicable component.
 *
 * @flash_component: Flash the data क्रम a given component to the device.
 * Called once क्रम each applicable component, after all component tables have
 * been sent.
 *
 * @finalize_update: (optional) Finish the update. Called after all components
 * have been flashed.
 */
काष्ठा pldmfw_ops अणु
	bool (*match_record)(काष्ठा pldmfw *context, काष्ठा pldmfw_record *record);
	पूर्णांक (*send_package_data)(काष्ठा pldmfw *context, स्थिर u8 *data, u16 length);
	पूर्णांक (*send_component_table)(काष्ठा pldmfw *context, काष्ठा pldmfw_component *component,
				    u8 transfer_flag);
	पूर्णांक (*flash_component)(काष्ठा pldmfw *context, काष्ठा pldmfw_component *component);
	पूर्णांक (*finalize_update)(काष्ठा pldmfw *context);
पूर्ण;

पूर्णांक pldmfw_flash_image(काष्ठा pldmfw *context, स्थिर काष्ठा firmware *fw);

#पूर्ण_अगर
