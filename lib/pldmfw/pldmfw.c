<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2018-2019, Intel Corporation. */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/crc32.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pldmfw.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>

#समावेश "pldmfw_private.h"

/* Internal काष्ठाure used to store details about the PLDM image file as it is
 * being validated and processed.
 */
काष्ठा pldmfw_priv अणु
	काष्ठा pldmfw *context;
	स्थिर काष्ठा firmware *fw;

	/* current offset of firmware image */
	माप_प्रकार offset;

	काष्ठा list_head records;
	काष्ठा list_head components;

	/* PLDM Firmware Package Header */
	स्थिर काष्ठा __pldm_header *header;
	u16 total_header_size;

	/* length of the component biपंचांगap */
	u16 component_biपंचांगap_len;
	u16 biपंचांगap_size;

	/* Start of the component image inक्रमmation */
	u16 component_count;
	स्थिर u8 *component_start;

	/* Start pf the firmware device id records */
	स्थिर u8 *record_start;
	u8 record_count;

	/* The CRC at the end of the package header */
	u32 header_crc;

	काष्ठा pldmfw_record *matching_record;
पूर्ण;

/**
 * pldm_check_fw_space - Verअगरy that the firmware image has space left
 * @data: poपूर्णांकer to निजी data
 * @offset: offset to start from
 * @length: length to check क्रम
 *
 * Verअगरy that the firmware data can hold a chunk of bytes with the specअगरied
 * offset and length.
 *
 * Returns: zero on success, or -EFAULT अगर the image करोes not have enough
 * space left to fit the expected length.
 */
अटल पूर्णांक
pldm_check_fw_space(काष्ठा pldmfw_priv *data, माप_प्रकार offset, माप_प्रकार length)
अणु
	माप_प्रकार expected_size = offset + length;
	काष्ठा device *dev = data->context->dev;

	अगर (data->fw->size < expected_size) अणु
		dev_dbg(dev, "Firmware file size smaller than expected. Got %zu bytes, needed %zu bytes\n",
			data->fw->size, expected_size);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pldm_move_fw_offset - Move the current firmware offset क्रमward
 * @data: poपूर्णांकer to निजी data
 * @bytes_to_move: number of bytes to move the offset क्रमward by
 *
 * Check that there is enough space past the current offset, and then move the
 * offset क्रमward by this ammount.
 *
 * Returns: zero on success, or -EFAULT अगर the image is too small to fit the
 * expected length.
 */
अटल पूर्णांक
pldm_move_fw_offset(काष्ठा pldmfw_priv *data, माप_प्रकार bytes_to_move)
अणु
	पूर्णांक err;

	err = pldm_check_fw_space(data, data->offset, bytes_to_move);
	अगर (err)
		वापस err;

	data->offset += bytes_to_move;

	वापस 0;
पूर्ण

/**
 * pldm_parse_header - Validate and extract details about the PLDM header
 * @data: poपूर्णांकer to निजी data
 *
 * Perक्रमms initial basic verअगरication of the PLDM image, up to the first
 * firmware record.
 *
 * This includes the following checks and extractions
 *
 *   * Verअगरy that the UUID at the start of the header matches the expected
 *     value as defined in the DSP0267 PLDM specअगरication
 *   * Check that the revision is 0x01
 *   * Extract the total header_size and verअगरy that the image is large enough
 *     to contain at least the length of this header
 *   * Extract the size of the component biपंचांगap length
 *   * Extract a poपूर्णांकer to the start of the record area
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक pldm_parse_header(काष्ठा pldmfw_priv *data)
अणु
	स्थिर काष्ठा __pldmfw_record_area *record_area;
	काष्ठा device *dev = data->context->dev;
	स्थिर काष्ठा __pldm_header *header;
	माप_प्रकार header_size;
	पूर्णांक err;

	err = pldm_move_fw_offset(data, माप(*header));
	अगर (err)
		वापस err;

	header = (स्थिर काष्ठा __pldm_header *)data->fw->data;
	data->header = header;

	अगर (!uuid_equal(&header->id, &pldm_firmware_header_id)) अणु
		dev_dbg(dev, "Invalid package header identifier. Expected UUID %pUB, but got %pUB\n",
			&pldm_firmware_header_id, &header->id);
		वापस -EINVAL;
	पूर्ण

	अगर (header->revision != PACKAGE_HEADER_FORMAT_REVISION) अणु
		dev_dbg(dev, "Invalid package header revision. Expected revision %u but got %u\n",
			PACKAGE_HEADER_FORMAT_REVISION, header->revision);
		वापस -EOPNOTSUPP;
	पूर्ण

	data->total_header_size = get_unaligned_le16(&header->size);
	header_size = data->total_header_size - माप(*header);

	err = pldm_check_fw_space(data, data->offset, header_size);
	अगर (err)
		वापस err;

	data->component_biपंचांगap_len =
		get_unaligned_le16(&header->component_biपंचांगap_len);

	अगर (data->component_biपंचांगap_len % 8 != 0) अणु
		dev_dbg(dev, "Invalid component bitmap length. The length is %u, which is not a multiple of 8\n",
			data->component_biपंचांगap_len);
		वापस -EINVAL;
	पूर्ण

	data->biपंचांगap_size = data->component_biपंचांगap_len / 8;

	err = pldm_move_fw_offset(data, header->version_len);
	अगर (err)
		वापस err;

	/* extract a poपूर्णांकer to the record area, which just follows the मुख्य
	 * PLDM header data.
	 */
	record_area = (स्थिर काष्ठा __pldmfw_record_area *)(data->fw->data +
							 data->offset);

	err = pldm_move_fw_offset(data, माप(*record_area));
	अगर (err)
		वापस err;

	data->record_count = record_area->record_count;
	data->record_start = record_area->records;

	वापस 0;
पूर्ण

/**
 * pldm_check_desc_tlv_len - Check that the length matches expectation
 * @data: poपूर्णांकer to image details
 * @type: the descriptor type
 * @size: the length from the descriptor header
 *
 * If the descriptor type is one of the करोcumented descriptor types according
 * to the standard, verअगरy that the provided length matches.
 *
 * If the type is not recognized or is VENDOR_DEFINED, वापस zero.
 *
 * Returns: zero on success, or -EINVAL अगर the specअगरied size of a standard
 * TLV करोes not match the expected value defined क्रम that TLV.
 */
अटल पूर्णांक
pldm_check_desc_tlv_len(काष्ठा pldmfw_priv *data, u16 type, u16 size)
अणु
	काष्ठा device *dev = data->context->dev;
	u16 expected_size;

	चयन (type) अणु
	हाल PLDM_DESC_ID_PCI_VENDOR_ID:
	हाल PLDM_DESC_ID_PCI_DEVICE_ID:
	हाल PLDM_DESC_ID_PCI_SUBVENDOR_ID:
	हाल PLDM_DESC_ID_PCI_SUBDEV_ID:
		expected_size = 2;
		अवरोध;
	हाल PLDM_DESC_ID_PCI_REVISION_ID:
		expected_size = 1;
		अवरोध;
	हाल PLDM_DESC_ID_PNP_VENDOR_ID:
		expected_size = 3;
		अवरोध;
	हाल PLDM_DESC_ID_IANA_ENTERPRISE_ID:
	हाल PLDM_DESC_ID_ACPI_VENDOR_ID:
	हाल PLDM_DESC_ID_PNP_PRODUCT_ID:
	हाल PLDM_DESC_ID_ACPI_PRODUCT_ID:
		expected_size = 4;
		अवरोध;
	हाल PLDM_DESC_ID_UUID:
		expected_size = 16;
		अवरोध;
	हाल PLDM_DESC_ID_VENDOR_DEFINED:
		वापस 0;
	शेष:
		/* Do not report an error on an unexpected TLV */
		dev_dbg(dev, "Found unrecognized TLV type 0x%04x\n", type);
		वापस 0;
	पूर्ण

	अगर (size != expected_size) अणु
		dev_dbg(dev, "Found TLV type 0x%04x with unexpected length. Got %u bytes, but expected %u bytes\n",
			type, size, expected_size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pldm_parse_desc_tlvs - Check and skip past a number of TLVs
 * @data: poपूर्णांकer to निजी data
 * @record: poपूर्णांकer to the record this TLV beदीर्घs too
 * @desc_count: descriptor count
 *
 * From the current offset, पढ़ो and extract the descriptor TLVs, updating the
 * current offset each समय.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
pldm_parse_desc_tlvs(काष्ठा pldmfw_priv *data, काष्ठा pldmfw_record *record, u8 desc_count)
अणु
	स्थिर काष्ठा __pldmfw_desc_tlv *__desc;
	स्थिर u8 *desc_start;
	u8 i;

	desc_start = data->fw->data + data->offset;

	pldm_क्रम_each_desc_tlv(i, __desc, desc_start, desc_count) अणु
		काष्ठा pldmfw_desc_tlv *desc;
		पूर्णांक err;
		u16 type, size;

		err = pldm_move_fw_offset(data, माप(*__desc));
		अगर (err)
			वापस err;

		type = get_unaligned_le16(&__desc->type);

		/* According to DSP0267, this only includes the data field */
		size = get_unaligned_le16(&__desc->size);

		err = pldm_check_desc_tlv_len(data, type, size);
		अगर (err)
			वापस err;

		/* check that we have space and move the offset क्रमward */
		err = pldm_move_fw_offset(data, size);
		अगर (err)
			वापस err;

		desc = kzalloc(माप(*desc), GFP_KERNEL);
		अगर (!desc)
			वापस -ENOMEM;

		desc->type = type;
		desc->size = size;
		desc->data = __desc->data;

		list_add_tail(&desc->entry, &record->descs);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pldm_parse_one_record - Verअगरy size of one PLDM record
 * @data: poपूर्णांकer to image details
 * @__record: poपूर्णांकer to the record to check
 *
 * This function checks that the record size करोes not exceed either the size
 * of the firmware file or the total length specअगरied in the header section.
 *
 * It also verअगरies that the recorded length of the start of the record
 * matches the size calculated by adding the अटल काष्ठाure length, the
 * component biपंचांगap length, the version string length, the length of all
 * descriptor TLVs, and the length of the package data.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
pldm_parse_one_record(काष्ठा pldmfw_priv *data,
		      स्थिर काष्ठा __pldmfw_record_info *__record)
अणु
	काष्ठा pldmfw_record *record;
	माप_प्रकार measured_length;
	पूर्णांक err;
	स्थिर u8 *biपंचांगap_ptr;
	u16 record_len;
	पूर्णांक i;

	/* Make a copy and insert it पूर्णांकo the record list */
	record = kzalloc(माप(*record), GFP_KERNEL);
	अगर (!record)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&record->descs);
	list_add_tail(&record->entry, &data->records);

	/* Then check that we have space and move the offset */
	err = pldm_move_fw_offset(data, माप(*__record));
	अगर (err)
		वापस err;

	record_len = get_unaligned_le16(&__record->record_len);
	record->package_data_len = get_unaligned_le16(&__record->package_data_len);
	record->version_len = __record->version_len;
	record->version_type = __record->version_type;

	biपंचांगap_ptr = data->fw->data + data->offset;

	/* check that we have space क्रम the component biपंचांगap length */
	err = pldm_move_fw_offset(data, data->biपंचांगap_size);
	अगर (err)
		वापस err;

	record->component_biपंचांगap_len = data->component_biपंचांगap_len;
	record->component_biपंचांगap = biपंचांगap_zalloc(record->component_biपंचांगap_len,
						 GFP_KERNEL);
	अगर (!record->component_biपंचांगap)
		वापस -ENOMEM;

	क्रम (i = 0; i < data->biपंचांगap_size; i++)
		biपंचांगap_set_value8(record->component_biपंचांगap, biपंचांगap_ptr[i], i * 8);

	record->version_string = data->fw->data + data->offset;

	err = pldm_move_fw_offset(data, record->version_len);
	अगर (err)
		वापस err;

	/* Scan through the descriptor TLVs and find the end */
	err = pldm_parse_desc_tlvs(data, record, __record->descriptor_count);
	अगर (err)
		वापस err;

	record->package_data = data->fw->data + data->offset;

	err = pldm_move_fw_offset(data, record->package_data_len);
	अगर (err)
		वापस err;

	measured_length = data->offset - ((स्थिर u8 *)__record - data->fw->data);
	अगर (measured_length != record_len) अणु
		dev_dbg(data->context->dev, "Unexpected record length. Measured record length is %zu bytes, expected length is %u bytes\n",
			measured_length, record_len);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pldm_parse_records - Locate the start of the component area
 * @data: poपूर्णांकer to निजी data
 *
 * Extract the record count, and loop through each record, searching क्रम the
 * component area.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक pldm_parse_records(काष्ठा pldmfw_priv *data)
अणु
	स्थिर काष्ठा __pldmfw_component_area *component_area;
	स्थिर काष्ठा __pldmfw_record_info *record;
	पूर्णांक err;
	u8 i;

	pldm_क्रम_each_record(i, record, data->record_start, data->record_count) अणु
		err = pldm_parse_one_record(data, record);
		अगर (err)
			वापस err;
	पूर्ण

	/* Extract a poपूर्णांकer to the component area, which just follows the
	 * PLDM device record data.
	 */
	component_area = (स्थिर काष्ठा __pldmfw_component_area *)(data->fw->data + data->offset);

	err = pldm_move_fw_offset(data, माप(*component_area));
	अगर (err)
		वापस err;

	data->component_count =
		get_unaligned_le16(&component_area->component_image_count);
	data->component_start = component_area->components;

	वापस 0;
पूर्ण

/**
 * pldm_parse_components - Locate the CRC header checksum
 * @data: poपूर्णांकer to निजी data
 *
 * Extract the component count, and find the poपूर्णांकer to the component area.
 * Scan through each component searching क्रम the end, which should poपूर्णांक to
 * the package header checksum.
 *
 * Extract the package header CRC and save it क्रम verअगरication.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक pldm_parse_components(काष्ठा pldmfw_priv *data)
अणु
	स्थिर काष्ठा __pldmfw_component_info *__component;
	काष्ठा device *dev = data->context->dev;
	स्थिर u8 *header_crc_ptr;
	पूर्णांक err;
	u8 i;

	pldm_क्रम_each_component(i, __component, data->component_start, data->component_count) अणु
		काष्ठा pldmfw_component *component;
		u32 offset, size;

		err = pldm_move_fw_offset(data, माप(*__component));
		अगर (err)
			वापस err;

		err = pldm_move_fw_offset(data, __component->version_len);
		अगर (err)
			वापस err;

		offset = get_unaligned_le32(&__component->location_offset);
		size = get_unaligned_le32(&__component->size);

		err = pldm_check_fw_space(data, offset, size);
		अगर (err)
			वापस err;

		component = kzalloc(माप(*component), GFP_KERNEL);
		अगर (!component)
			वापस -ENOMEM;

		component->index = i;
		component->classअगरication = get_unaligned_le16(&__component->classअगरication);
		component->identअगरier = get_unaligned_le16(&__component->identअगरier);
		component->comparison_stamp = get_unaligned_le32(&__component->comparison_stamp);
		component->options = get_unaligned_le16(&__component->options);
		component->activation_method = get_unaligned_le16(&__component->activation_method);
		component->version_type = __component->version_type;
		component->version_len = __component->version_len;
		component->version_string = __component->version_string;
		component->component_data = data->fw->data + offset;
		component->component_size = size;

		list_add_tail(&component->entry, &data->components);
	पूर्ण

	header_crc_ptr = data->fw->data + data->offset;

	err = pldm_move_fw_offset(data, माप(data->header_crc));
	अगर (err)
		वापस err;

	/* Make sure that we reached the expected offset */
	अगर (data->offset != data->total_header_size) अणु
		dev_dbg(dev, "Invalid firmware header size. Expected %u but got %zu\n",
			data->total_header_size, data->offset);
		वापस -EFAULT;
	पूर्ण

	data->header_crc = get_unaligned_le32(header_crc_ptr);

	वापस 0;
पूर्ण

/**
 * pldm_verअगरy_header_crc - Verअगरy that the CRC in the header matches
 * @data: poपूर्णांकer to निजी data
 *
 * Calculates the 32-bit CRC using the standard IEEE 802.3 CRC polynomial and
 * compares it to the value stored in the header.
 *
 * Returns: zero on success अगर the CRC matches, or -EBADMSG on an invalid CRC.
 */
अटल पूर्णांक pldm_verअगरy_header_crc(काष्ठा pldmfw_priv *data)
अणु
	काष्ठा device *dev = data->context->dev;
	u32 calculated_crc;
	माप_प्रकार length;

	/* Calculate the 32-bit CRC of the header header contents up to but
	 * not including the checksum. Note that the Linux crc32_le function
	 * करोes not perक्रमm an expected final XOR.
	 */
	length = data->offset - माप(data->header_crc);
	calculated_crc = crc32_le(~0, data->fw->data, length) ^ ~0;

	अगर (calculated_crc != data->header_crc) अणु
		dev_dbg(dev, "Invalid CRC in firmware header. Got 0x%08x but expected 0x%08x\n",
			calculated_crc, data->header_crc);
		वापस -EBADMSG;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pldmfw_मुक्त_priv - Free memory allocated जबतक parsing the PLDM image
 * @data: poपूर्णांकer to the PLDM data काष्ठाure
 *
 * Loops through and clears all allocated memory associated with each
 * allocated descriptor, record, and component.
 */
अटल व्योम pldmfw_मुक्त_priv(काष्ठा pldmfw_priv *data)
अणु
	काष्ठा pldmfw_component *component, *c_safe;
	काष्ठा pldmfw_record *record, *r_safe;
	काष्ठा pldmfw_desc_tlv *desc, *d_safe;

	list_क्रम_each_entry_safe(component, c_safe, &data->components, entry) अणु
		list_del(&component->entry);
		kमुक्त(component);
	पूर्ण

	list_क्रम_each_entry_safe(record, r_safe, &data->records, entry) अणु
		list_क्रम_each_entry_safe(desc, d_safe, &record->descs, entry) अणु
			list_del(&desc->entry);
			kमुक्त(desc);
		पूर्ण

		अगर (record->component_biपंचांगap) अणु
			biपंचांगap_मुक्त(record->component_biपंचांगap);
			record->component_biपंचांगap = शून्य;
		पूर्ण

		list_del(&record->entry);
		kमुक्त(record);
	पूर्ण
पूर्ण

/**
 * pldm_parse_image - parse and extract details from PLDM image
 * @data: poपूर्णांकer to निजी data
 *
 * Verअगरy that the firmware file contains valid data क्रम a PLDM firmware
 * file. Extract useful poपूर्णांकers and data from the firmware file and store
 * them in the data काष्ठाure.
 *
 * The PLDM firmware file क्रमmat is defined in DMTF DSP0267 1.0.0. Care
 * should be taken to use get_unaligned_le* when accessing data from the
 * poपूर्णांकers in data.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक pldm_parse_image(काष्ठा pldmfw_priv *data)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!(data->context->dev && data->fw->data && data->fw->size)))
		वापस -EINVAL;

	err = pldm_parse_header(data);
	अगर (err)
		वापस err;

	err = pldm_parse_records(data);
	अगर (err)
		वापस err;

	err = pldm_parse_components(data);
	अगर (err)
		वापस err;

	वापस pldm_verअगरy_header_crc(data);
पूर्ण

/* these are u32 so that we can store PCI_ANY_ID */
काष्ठा pldm_pci_record_id अणु
	पूर्णांक venकरोr;
	पूर्णांक device;
	पूर्णांक subप्रणाली_venकरोr;
	पूर्णांक subप्रणाली_device;
पूर्ण;

/**
 * pldmfw_op_pci_match_record - Check अगर a PCI device matches the record
 * @context: PLDM fw update काष्ठाure
 * @record: list of records extracted from the PLDM image
 *
 * Determine of the PCI device associated with this device matches the record
 * data provided.
 *
 * Searches the descriptor TLVs and extracts the relevant descriptor data पूर्णांकo
 * a pldm_pci_record_id. This is then compared against the PCI device ID
 * inक्रमmation.
 *
 * Returns: true अगर the device matches the record, false otherwise.
 */
bool pldmfw_op_pci_match_record(काष्ठा pldmfw *context, काष्ठा pldmfw_record *record)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(context->dev);
	काष्ठा pldm_pci_record_id id = अणु
		.venकरोr = PCI_ANY_ID,
		.device = PCI_ANY_ID,
		.subप्रणाली_venकरोr = PCI_ANY_ID,
		.subप्रणाली_device = PCI_ANY_ID,
	पूर्ण;
	काष्ठा pldmfw_desc_tlv *desc;

	list_क्रम_each_entry(desc, &record->descs, entry) अणु
		u16 value;
		पूर्णांक *ptr;

		चयन (desc->type) अणु
		हाल PLDM_DESC_ID_PCI_VENDOR_ID:
			ptr = &id.venकरोr;
			अवरोध;
		हाल PLDM_DESC_ID_PCI_DEVICE_ID:
			ptr = &id.device;
			अवरोध;
		हाल PLDM_DESC_ID_PCI_SUBVENDOR_ID:
			ptr = &id.subप्रणाली_venकरोr;
			अवरोध;
		हाल PLDM_DESC_ID_PCI_SUBDEV_ID:
			ptr = &id.subप्रणाली_device;
			अवरोध;
		शेष:
			/* Skip unrelated TLVs */
			जारी;
		पूर्ण

		value = get_unaligned_le16(desc->data);
		/* A value of zero क्रम one of the descriptors is someबार
		 * used when the record should ignore this field when matching
		 * device. For example अगर the record applies to any subप्रणाली
		 * device or venकरोr.
		 */
		अगर (value)
			*ptr = (पूर्णांक)value;
		अन्यथा
			*ptr = PCI_ANY_ID;
	पूर्ण

	अगर ((id.venकरोr == PCI_ANY_ID || id.venकरोr == pdev->venकरोr) &&
	    (id.device == PCI_ANY_ID || id.device == pdev->device) &&
	    (id.subप्रणाली_venकरोr == PCI_ANY_ID || id.subप्रणाली_venकरोr == pdev->subप्रणाली_venकरोr) &&
	    (id.subप्रणाली_device == PCI_ANY_ID || id.subप्रणाली_device == pdev->subप्रणाली_device))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण
EXPORT_SYMBOL(pldmfw_op_pci_match_record);

/**
 * pldm_find_matching_record - Find the first matching PLDM record
 * @data: poपूर्णांकer to निजी data
 *
 * Search through PLDM records and find the first matching entry. It is
 * expected that only one entry matches.
 *
 * Store a poपूर्णांकer to the matching record, अगर found.
 *
 * Returns: zero on success, or -ENOENT अगर no matching record is found.
 */
अटल पूर्णांक pldm_find_matching_record(काष्ठा pldmfw_priv *data)
अणु
	काष्ठा pldmfw_record *record;

	list_क्रम_each_entry(record, &data->records, entry) अणु
		अगर (data->context->ops->match_record(data->context, record)) अणु
			data->matching_record = record;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * pldm_send_package_data - Send firmware the package data क्रम the record
 * @data: poपूर्णांकer to निजी data
 *
 * Send the package data associated with the matching record to the firmware,
 * using the send_pkg_data operation.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
pldm_send_package_data(काष्ठा pldmfw_priv *data)
अणु
	काष्ठा pldmfw_record *record = data->matching_record;
	स्थिर काष्ठा pldmfw_ops *ops = data->context->ops;

	वापस ops->send_package_data(data->context, record->package_data,
				      record->package_data_len);
पूर्ण

/**
 * pldm_send_component_tables - Send component table inक्रमmation to firmware
 * @data: poपूर्णांकer to निजी data
 *
 * Loop over each component, sending the applicable components to the firmware
 * via the send_component_table operation.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक
pldm_send_component_tables(काष्ठा pldmfw_priv *data)
अणु
	अचिन्हित दीर्घ *biपंचांगap = data->matching_record->component_biपंचांगap;
	काष्ठा pldmfw_component *component;
	पूर्णांक err;

	list_क्रम_each_entry(component, &data->components, entry) अणु
		u8 index = component->index, transfer_flag = 0;

		/* Skip components which are not पूर्णांकended क्रम this device */
		अगर (!test_bit(index, biपंचांगap))
			जारी;

		/* determine whether this is the start, middle, end, or both
		 * the start and end of the component tables
		 */
		अगर (index == find_first_bit(biपंचांगap, data->component_biपंचांगap_len))
			transfer_flag |= PLDM_TRANSFER_FLAG_START;
		अगर (index == find_last_bit(biपंचांगap, data->component_biपंचांगap_len))
			transfer_flag |= PLDM_TRANSFER_FLAG_END;
		अगर (!transfer_flag)
			transfer_flag = PLDM_TRANSFER_FLAG_MIDDLE;

		err = data->context->ops->send_component_table(data->context,
							       component,
							       transfer_flag);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pldm_flash_components - Program each component to device flash
 * @data: poपूर्णांकer to निजी data
 *
 * Loop through each component that is active क्रम the matching device record,
 * and send it to the device driver क्रम flashing.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
अटल पूर्णांक pldm_flash_components(काष्ठा pldmfw_priv *data)
अणु
	अचिन्हित दीर्घ *biपंचांगap = data->matching_record->component_biपंचांगap;
	काष्ठा pldmfw_component *component;
	पूर्णांक err;

	list_क्रम_each_entry(component, &data->components, entry) अणु
		u8 index = component->index;

		/* Skip components which are not पूर्णांकended क्रम this device */
		अगर (!test_bit(index, biपंचांगap))
			जारी;

		err = data->context->ops->flash_component(data->context, component);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pldm_finalize_update - Finalize the device flash update
 * @data: poपूर्णांकer to निजी data
 *
 * Tell the device driver to perक्रमm any reमुख्यing logic to complete the
 * device update.
 *
 * Returns: zero on success, or a PLFM_FWU error indicating the reason क्रम
 * failure.
 */
अटल पूर्णांक pldm_finalize_update(काष्ठा pldmfw_priv *data)
अणु
	अगर (data->context->ops->finalize_update)
		वापस data->context->ops->finalize_update(data->context);

	वापस 0;
पूर्ण

/**
 * pldmfw_flash_image - Write a PLDM-क्रमmatted firmware image to the device
 * @context: ops and data क्रम firmware update
 * @fw: firmware object poपूर्णांकing to the relevant firmware file to program
 *
 * Parse the data क्रम a given firmware file, verअगरying that it is a valid PLDM
 * क्रमmatted image that matches this device.
 *
 * Extract the device record Package Data and Component Tables and send them
 * to the device firmware. Extract and ग_लिखो the flash data क्रम each of the
 * components indicated in the firmware file.
 *
 * Returns: zero on success, or a negative error code on failure.
 */
पूर्णांक pldmfw_flash_image(काष्ठा pldmfw *context, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा pldmfw_priv *data;
	पूर्णांक err;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&data->records);
	INIT_LIST_HEAD(&data->components);

	data->fw = fw;
	data->context = context;

	err = pldm_parse_image(data);
	अगर (err)
		जाओ out_release_data;

	err = pldm_find_matching_record(data);
	अगर (err)
		जाओ out_release_data;

	err = pldm_send_package_data(data);
	अगर (err)
		जाओ out_release_data;

	err = pldm_send_component_tables(data);
	अगर (err)
		जाओ out_release_data;

	err = pldm_flash_components(data);
	अगर (err)
		जाओ out_release_data;

	err = pldm_finalize_update(data);

out_release_data:
	pldmfw_मुक्त_priv(data);
	kमुक्त(data);

	वापस err;
पूर्ण
EXPORT_SYMBOL(pldmfw_flash_image);

MODULE_AUTHOR("Jacob Keller <jacob.e.keller@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PLDM firmware flash update library");
