<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018-2019, Intel Corporation. */

#अगर_अघोषित _PLDMFW_PRIVATE_H_
#घोषणा _PLDMFW_PRIVATE_H_

/* The following data काष्ठाures define the layout of a firmware binary
 * following the "PLDM For Firmware Update Specification", DMTF standard
 * #DSP0267.
 *
 * pldmfw.c uses these काष्ठाures to implement a simple engine that will parse
 * a fw binary file in this क्रमmat and perक्रमm a firmware update क्रम a given
 * device.
 *
 * Due to the variable sized data layout, alignment of fields within these
 * काष्ठाures is not guaranteed when पढ़ोing. For this reason, all multi-byte
 * field accesses should be करोne using the unaligned access macros.
 * Additionally, the standard specअगरies that multi-byte fields are in
 * LittleEndian क्रमmat.
 *
 * The काष्ठाure definitions are not made खुला, in order to keep direct
 * accesses within code that is prepared to deal with the limitation of
 * unaligned access.
 */

/* UUID क्रम PLDM firmware packages: f018878c-cb7d-4943-9800-a02f059aca02 */
अटल स्थिर uuid_t pldm_firmware_header_id =
	UUID_INIT(0xf018878c, 0xcb7d, 0x4943,
		  0x98, 0x00, 0xa0, 0x2f, 0x05, 0x9a, 0xca, 0x02);

/* Revision number of the PLDM header क्रमmat this code supports */
#घोषणा PACKAGE_HEADER_FORMAT_REVISION 0x01

/* बारtamp104 काष्ठाure defined in PLDM Base specअगरication */
#घोषणा PLDM_TIMESTAMP_SIZE 13
काष्ठा __pldm_बारtamp अणु
	u8 b[PLDM_TIMESTAMP_SIZE];
पूर्ण __packed __aligned(1);

/* Package Header Inक्रमmation */
काष्ठा __pldm_header अणु
	uuid_t id;			    /* PackageHeaderIdentअगरier */
	u8 revision;			    /* PackageHeaderFormatRevision */
	__le16 size;			    /* PackageHeaderSize */
	काष्ठा __pldm_बारtamp release_date; /* PackageReleaseDateTime */
	__le16 component_biपंचांगap_len;	    /* ComponentBiपंचांगapBitLength */
	u8 version_type;		    /* PackageVersionStringType */
	u8 version_len;			    /* PackageVersionStringLength */

	/*
	 * DSP0267 also includes the following variable length fields at the
	 * end of this काष्ठाure:
	 *
	 * PackageVersionString, length is version_len.
	 *
	 * The total size of this section is
	 *   माप(pldm_header) + version_len;
	 */
	u8 version_string[];		/* PackageVersionString */
पूर्ण __packed __aligned(1);

/* Firmware Device ID Record */
काष्ठा __pldmfw_record_info अणु
	__le16 record_len;		/* RecordLength */
	u8 descriptor_count;		/* DescriptorCount */
	__le32 device_update_flags;	/* DeviceUpdateOptionFlags */
	u8 version_type;		/* ComponentImageSetVersionType */
	u8 version_len;			/* ComponentImageSetVersionLength */
	__le16 package_data_len;	/* FirmwareDevicePackageDataLength */

	/*
	 * DSP0267 also includes the following variable length fields at the
	 * end of this काष्ठाure:
	 *
	 * ApplicableComponents, length is component_biपंचांगap_len from header
	 * ComponentImageSetVersionString, length is version_len
	 * RecordDescriptors, a series of TLVs with 16bit type and length
	 * FirmwareDevicePackageData, length is package_data_len
	 *
	 * The total size of each record is
	 *   माप(pldmfw_record_info) +
	 *   component_biपंचांगap_len (converted to bytes!) +
	 *   version_len +
	 *   <length of RecordDescriptors> +
	 *   package_data_len
	 */
	u8 variable_record_data[];
पूर्ण __packed __aligned(1);

/* Firmware Descriptor Definition */
काष्ठा __pldmfw_desc_tlv अणु
	__le16 type;			/* DescriptorType */
	__le16 size;			/* DescriptorSize */
	u8 data[];			/* DescriptorData */
पूर्ण __aligned(1);

/* Firmware Device Identअगरication Area */
काष्ठा __pldmfw_record_area अणु
	u8 record_count;		/* DeviceIDRecordCount */
	/* This is not a काष्ठा type because the size of each record varies */
	u8 records[];
पूर्ण __aligned(1);

/* Inभागidual Component Image Inक्रमmation */
काष्ठा __pldmfw_component_info अणु
	__le16 classअगरication;		/* ComponentClassfication */
	__le16 identअगरier;		/* ComponentIdentअगरier */
	__le32 comparison_stamp;	/* ComponentComparisonStamp */
	__le16 options;			/* componentOptions */
	__le16 activation_method;	/* RequestedComponentActivationMethod */
	__le32 location_offset;		/* ComponentLocationOffset */
	__le32 size;			/* ComponentSize */
	u8 version_type;		/* ComponentVersionStringType */
	u8 version_len;		/* ComponentVersionStringLength */

	/*
	 * DSP0267 also includes the following variable length fields at the
	 * end of this काष्ठाure:
	 *
	 * ComponentVersionString, length is version_len
	 *
	 * The total size of this section is
	 *   माप(pldmfw_component_info) + version_len;
	 */
	u8 version_string[];		/* ComponentVersionString */
पूर्ण __packed __aligned(1);

/* Component Image Inक्रमmation Area */
काष्ठा __pldmfw_component_area अणु
	__le16 component_image_count;
	/* This is not a काष्ठा type because the component size varies */
	u8 components[];
पूर्ण __aligned(1);

/**
 * pldm_first_desc_tlv
 * @start: byte offset of the start of the descriptor TLVs
 *
 * Converts the starting offset of the descriptor TLVs पूर्णांकo a poपूर्णांकer to the
 * first descriptor.
 */
#घोषणा pldm_first_desc_tlv(start)					\
	((स्थिर काष्ठा __pldmfw_desc_tlv *)(start))

/**
 * pldm_next_desc_tlv
 * @desc: poपूर्णांकer to a descriptor TLV
 *
 * Finds the poपूर्णांकer to the next descriptor following a given descriptor
 */
#घोषणा pldm_next_desc_tlv(desc)						\
	((स्थिर काष्ठा __pldmfw_desc_tlv *)((desc)->data +			\
					     get_unaligned_le16(&(desc)->size)))

/**
 * pldm_क्रम_each_desc_tlv
 * @i: variable to store descriptor index
 * @desc: variable to store descriptor poपूर्णांकer
 * @start: byte offset of the start of the descriptors
 * @count: the number of descriptors
 *
 * क्रम loop macro to iterate over all of the descriptors of a given PLDM
 * record.
 */
#घोषणा pldm_क्रम_each_desc_tlv(i, desc, start, count)			\
	क्रम ((i) = 0, (desc) = pldm_first_desc_tlv(start);		\
	     (i) < (count);						\
	     (i)++, (desc) = pldm_next_desc_tlv(desc))

/**
 * pldm_first_record
 * @start: byte offset of the start of the PLDM records
 *
 * Converts a starting offset of the PLDM records पूर्णांकo a poपूर्णांकer to the first
 * record.
 */
#घोषणा pldm_first_record(start)					\
	((स्थिर काष्ठा __pldmfw_record_info *)(start))

/**
 * pldm_next_record
 * @record: poपूर्णांकer to a PLDM record
 *
 * Finds a poपूर्णांकer to the next record following a given record
 */
#घोषणा pldm_next_record(record)					\
	((स्थिर काष्ठा __pldmfw_record_info *)				\
	 ((स्थिर u8 *)(record) + get_unaligned_le16(&(record)->record_len)))

/**
 * pldm_क्रम_each_record
 * @i: variable to store record index
 * @record: variable to store record poपूर्णांकer
 * @start: byte offset of the start of the records
 * @count: the number of records
 *
 * क्रम loop macro to iterate over all of the records of a PLDM file.
 */
#घोषणा pldm_क्रम_each_record(i, record, start, count)			\
	क्रम ((i) = 0, (record) = pldm_first_record(start);		\
	     (i) < (count);						\
	     (i)++, (record) = pldm_next_record(record))

/**
 * pldm_first_component
 * @start: byte offset of the start of the PLDM components
 *
 * Convert a starting offset of the PLDM components पूर्णांकo a poपूर्णांकer to the
 * first component
 */
#घोषणा pldm_first_component(start)					\
	((स्थिर काष्ठा __pldmfw_component_info *)(start))

/**
 * pldm_next_component
 * @component: poपूर्णांकer to a PLDM component
 *
 * Finds a poपूर्णांकer to the next component following a given component
 */
#घोषणा pldm_next_component(component)						\
	((स्थिर काष्ठा __pldmfw_component_info *)((component)->version_string +	\
						  (component)->version_len))

/**
 * pldm_क्रम_each_component
 * @i: variable to store component index
 * @component: variable to store component poपूर्णांकer
 * @start: byte offset to the start of the first component
 * @count: the number of components
 *
 * क्रम loop macro to iterate over all of the components of a PLDM file.
 */
#घोषणा pldm_क्रम_each_component(i, component, start, count)		\
	क्रम ((i) = 0, (component) = pldm_first_component(start);	\
	     (i) < (count);						\
	     (i)++, (component) = pldm_next_component(component))

#पूर्ण_अगर
