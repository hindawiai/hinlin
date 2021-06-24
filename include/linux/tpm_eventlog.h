<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __LINUX_TPM_EVENTLOG_H__
#घोषणा __LINUX_TPM_EVENTLOG_H__

#समावेश <linux/tpm.h>

#घोषणा TCG_EVENT_NAME_LEN_MAX	255
#घोषणा MAX_TEXT_EVENT		1000	/* Max event string length */
#घोषणा ACPI_TCPA_SIG		"TCPA"	/* 0x41504354 /'TCPA' */

#घोषणा EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 0x1
#घोषणा EFI_TCG2_EVENT_LOG_FORMAT_TCG_2   0x2

#अगर_घोषित CONFIG_PPC64
#घोषणा करो_endian_conversion(x) be32_to_cpu(x)
#अन्यथा
#घोषणा करो_endian_conversion(x) x
#पूर्ण_अगर

क्रमागत bios_platक्रमm_class अणु
	BIOS_CLIENT = 0x00,
	BIOS_SERVER = 0x01,
पूर्ण;

काष्ठा tcpa_event अणु
	u32 pcr_index;
	u32 event_type;
	u8 pcr_value[20];	/* SHA1 */
	u32 event_size;
	u8 event_data[];
पूर्ण;

क्रमागत tcpa_event_types अणु
	PREBOOT = 0,
	POST_CODE,
	UNUSED,
	NO_ACTION,
	SEPARATOR,
	ACTION,
	EVENT_TAG,
	SCRTM_CONTENTS,
	SCRTM_VERSION,
	CPU_MICROCODE,
	PLATFORM_CONFIG_FLAGS,
	TABLE_OF_DEVICES,
	COMPACT_HASH,
	IPL,
	IPL_PARTITION_DATA,
	NONHOST_CODE,
	NONHOST_CONFIG,
	NONHOST_INFO,
पूर्ण;

काष्ठा tcpa_pc_event अणु
	u32 event_id;
	u32 event_size;
	u8 event_data[];
पूर्ण;

क्रमागत tcpa_pc_event_ids अणु
	SMBIOS = 1,
	BIS_CERT,
	POST_BIOS_ROM,
	ESCD,
	CMOS,
	NVRAM,
	OPTION_ROM_EXEC,
	OPTION_ROM_CONFIG,
	OPTION_ROM_MICROCODE = 10,
	S_CRTM_VERSION,
	S_CRTM_CONTENTS,
	POST_CONTENTS,
	HOST_TABLE_OF_DEVICES,
पूर्ण;

/* http://www.trustedcomputinggroup.org/tcg-efi-protocol-specअगरication/ */

काष्ठा tcg_efi_specid_event_algs अणु
	u16 alg_id;
	u16 digest_size;
पूर्ण __packed;

#घोषणा TCG_SPECID_SIG "Spec ID Event03"

काष्ठा tcg_efi_specid_event_head अणु
	u8 signature[16];
	u32 platक्रमm_class;
	u8 spec_version_minor;
	u8 spec_version_major;
	u8 spec_errata;
	u8 uपूर्णांकnsize;
	u32 num_algs;
	काष्ठा tcg_efi_specid_event_algs digest_sizes[];
पूर्ण __packed;

काष्ठा tcg_pcr_event अणु
	u32 pcr_idx;
	u32 event_type;
	u8 digest[20];
	u32 event_size;
	u8 event[];
पूर्ण __packed;

काष्ठा tcg_event_field अणु
	u32 event_size;
	u8 event[];
पूर्ण __packed;

काष्ठा tcg_pcr_event2_head अणु
	u32 pcr_idx;
	u32 event_type;
	u32 count;
	काष्ठा tpm_digest digests[];
पूर्ण __packed;

काष्ठा tcg_algorithm_size अणु
	u16 algorithm_id;
	u16 algorithm_size;
पूर्ण;

काष्ठा tcg_algorithm_info अणु
	u8 signature[16];
	u32 platक्रमm_class;
	u8 spec_version_minor;
	u8 spec_version_major;
	u8 spec_errata;
	u8 uपूर्णांकn_size;
	u32 number_of_algorithms;
	काष्ठा tcg_algorithm_size digest_sizes[];
पूर्ण;

#अगर_अघोषित TPM_MEMREMAP
#घोषणा TPM_MEMREMAP(start, size) शून्य
#पूर्ण_अगर

#अगर_अघोषित TPM_MEMUNMAP
#घोषणा TPM_MEMUNMAP(start, size) करोअणुपूर्ण जबतक(0)
#पूर्ण_अगर

/**
 * __calc_tpm2_event_size - calculate the size of a TPM2 event log entry
 * @event:        Poपूर्णांकer to the event whose size should be calculated
 * @event_header: Poपूर्णांकer to the initial event containing the digest lengths
 * @करो_mapping:   Whether or not the event needs to be mapped
 *
 * The TPM2 event log क्रमmat can contain multiple digests corresponding to
 * separate PCR banks, and also contains a variable length of the data that
 * was measured. This requires knowledge of how दीर्घ each digest type is,
 * and this inक्रमmation is contained within the first event in the log.
 *
 * We calculate the length by examining the number of events, and then looking
 * at each event in turn to determine how much space is used क्रम events in
 * total. Once we've करोne this we know the offset of the data length field,
 * and can calculate the total size of the event.
 *
 * Return: size of the event on success, 0 on failure
 */

अटल अंतरभूत पूर्णांक __calc_tpm2_event_size(काष्ठा tcg_pcr_event2_head *event,
					 काष्ठा tcg_pcr_event *event_header,
					 bool करो_mapping)
अणु
	काष्ठा tcg_efi_specid_event_head *efispecid;
	काष्ठा tcg_event_field *event_field;
	व्योम *mapping = शून्य;
	पूर्णांक mapping_size;
	व्योम *marker;
	व्योम *marker_start;
	u32 halg_size;
	माप_प्रकार size;
	u16 halg;
	पूर्णांक i;
	पूर्णांक j;
	u32 count, event_type;
	स्थिर u8 zero_digest[माप(event_header->digest)] = अणु0पूर्ण;

	marker = event;
	marker_start = marker;
	marker = marker + माप(event->pcr_idx) + माप(event->event_type)
		+ माप(event->count);

	/* Map the event header */
	अगर (करो_mapping) अणु
		mapping_size = marker - marker_start;
		mapping = TPM_MEMREMAP((अचिन्हित दीर्घ)marker_start,
				       mapping_size);
		अगर (!mapping) अणु
			size = 0;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapping = marker_start;
	पूर्ण

	event = (काष्ठा tcg_pcr_event2_head *)mapping;
	/*
	 * The loop below will unmap these fields अगर the log is larger than
	 * one page, so save them here क्रम reference:
	 */
	count = READ_ONCE(event->count);
	event_type = READ_ONCE(event->event_type);

	/* Verअगरy that it's the log header */
	अगर (event_header->pcr_idx != 0 ||
	    event_header->event_type != NO_ACTION ||
	    स_भेद(event_header->digest, zero_digest, माप(zero_digest))) अणु
		size = 0;
		जाओ out;
	पूर्ण

	efispecid = (काष्ठा tcg_efi_specid_event_head *)event_header->event;

	/*
	 * Perक्रमm validation of the event in order to identअगरy malक्रमmed
	 * events. This function may be asked to parse arbitrary byte sequences
	 * immediately following a valid event log. The caller expects this
	 * function to recognize that the byte sequence is not a valid event
	 * and to वापस an event size of 0.
	 */
	अगर (स_भेद(efispecid->signature, TCG_SPECID_SIG,
		   माप(TCG_SPECID_SIG)) ||
	    !efispecid->num_algs || count != efispecid->num_algs) अणु
		size = 0;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		halg_size = माप(event->digests[i].alg_id);

		/* Map the digest's algorithm identअगरier */
		अगर (करो_mapping) अणु
			TPM_MEMUNMAP(mapping, mapping_size);
			mapping_size = halg_size;
			mapping = TPM_MEMREMAP((अचिन्हित दीर्घ)marker,
					     mapping_size);
			अगर (!mapping) अणु
				size = 0;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			mapping = marker;
		पूर्ण

		स_नकल(&halg, mapping, halg_size);
		marker = marker + halg_size;

		क्रम (j = 0; j < efispecid->num_algs; j++) अणु
			अगर (halg == efispecid->digest_sizes[j].alg_id) अणु
				marker +=
					efispecid->digest_sizes[j].digest_size;
				अवरोध;
			पूर्ण
		पूर्ण
		/* Algorithm without known length. Such event is unparseable. */
		अगर (j == efispecid->num_algs) अणु
			size = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Map the event size - we करोn't पढ़ो from the event itself, so
	 * we करोn't need to map it
	 */
	अगर (करो_mapping) अणु
		TPM_MEMUNMAP(mapping, mapping_size);
		mapping_size += माप(event_field->event_size);
		mapping = TPM_MEMREMAP((अचिन्हित दीर्घ)marker,
				       mapping_size);
		अगर (!mapping) अणु
			size = 0;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapping = marker;
	पूर्ण

	event_field = (काष्ठा tcg_event_field *)mapping;

	marker = marker + माप(event_field->event_size)
		+ event_field->event_size;
	size = marker - marker_start;

	अगर (event_type == 0 && event_field->event_size == 0)
		size = 0;

out:
	अगर (करो_mapping)
		TPM_MEMUNMAP(mapping, mapping_size);
	वापस size;
पूर्ण

#पूर्ण_अगर
