<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helper functions used by the EFI stub on multiple
 * architectures. This should be #समावेशd by the EFI stub
 * implementation files.
 *
 * Copyright 2011 Intel Corporation; author Matt Fleming
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/प्रकार.स>
#समावेश <linux/efi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h> /* For CONSOLE_LOGLEVEL_* */
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/setup.h>

#समावेश "efistub.h"

bool efi_nochunk;
bool efi_nokaslr = !IS_ENABLED(CONFIG_RANDOMIZE_BASE);
bool efi_noinitrd;
पूर्णांक efi_loglevel = CONSOLE_LOGLEVEL_DEFAULT;
bool efi_novamap;

अटल bool efi_nosoftreserve;
अटल bool efi_disable_pci_dma = IS_ENABLED(CONFIG_EFI_DISABLE_PCI_DMA);

bool __pure __efi_soft_reserve_enabled(व्योम)
अणु
	वापस !efi_nosoftreserve;
पूर्ण

/**
 * efi_अक्षर16_माला_दो() - Write a UCS-2 encoded string to the console
 * @str:	UCS-2 encoded string
 */
व्योम efi_अक्षर16_माला_दो(efi_अक्षर16_t *str)
अणु
	efi_call_proto(efi_table_attr(efi_प्रणाली_table, con_out),
		       output_string, str);
पूर्ण

अटल
u32 utf8_to_utf32(स्थिर u8 **s8)
अणु
	u32 c32;
	u8 c0, cx;
	माप_प्रकार clen, i;

	c0 = cx = *(*s8)++;
	/*
	 * The position of the most-signअगरicant 0 bit gives us the length of
	 * a multi-octet encoding.
	 */
	क्रम (clen = 0; cx & 0x80; ++clen)
		cx <<= 1;
	/*
	 * If the 0 bit is in position 8, this is a valid single-octet
	 * encoding. If the 0 bit is in position 7 or positions 1-3, the
	 * encoding is invalid.
	 * In either हाल, we just वापस the first octet.
	 */
	अगर (clen < 2 || clen > 4)
		वापस c0;
	/* Get the bits from the first octet. */
	c32 = cx >> clen--;
	क्रम (i = 0; i < clen; ++i) अणु
		/* Trailing octets must have 10 in most signअगरicant bits. */
		cx = (*s8)[i] ^ 0x80;
		अगर (cx & 0xc0)
			वापस c0;
		c32 = (c32 << 6) | cx;
	पूर्ण
	/*
	 * Check क्रम validity:
	 * - The अक्षरacter must be in the Unicode range.
	 * - It must not be a surrogate.
	 * - It must be encoded using the correct number of octets.
	 */
	अगर (c32 > 0x10ffff ||
	    (c32 & 0xf800) == 0xd800 ||
	    clen != (c32 >= 0x80) + (c32 >= 0x800) + (c32 >= 0x10000))
		वापस c0;
	*s8 += clen;
	वापस c32;
पूर्ण

/**
 * efi_माला_दो() - Write a UTF-8 encoded string to the console
 * @str:	UTF-8 encoded string
 */
व्योम efi_माला_दो(स्थिर अक्षर *str)
अणु
	efi_अक्षर16_t buf[128];
	माप_प्रकार pos = 0, lim = ARRAY_SIZE(buf);
	स्थिर u8 *s8 = (स्थिर u8 *)str;
	u32 c32;

	जबतक (*s8) अणु
		अगर (*s8 == '\n')
			buf[pos++] = L'\r';
		c32 = utf8_to_utf32(&s8);
		अगर (c32 < 0x10000) अणु
			/* Characters in plane 0 use a single word. */
			buf[pos++] = c32;
		पूर्ण अन्यथा अणु
			/*
			 * Characters in other planes encode पूर्णांकo a surrogate
			 * pair.
			 */
			buf[pos++] = (0xd800 - (0x10000 >> 10)) + (c32 >> 10);
			buf[pos++] = 0xdc00 + (c32 & 0x3ff);
		पूर्ण
		अगर (*s8 == '\0' || pos >= lim - 2) अणु
			buf[pos] = L'\0';
			efi_अक्षर16_माला_दो(buf);
			pos = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * efi_prपूर्णांकk() - Prपूर्णांक a kernel message
 * @fmt:	क्रमmat string
 *
 * The first letter of the क्रमmat string is used to determine the logging level
 * of the message. If the level is less then the current EFI logging level, the
 * message is suppressed. The message will be truncated to 255 bytes.
 *
 * Return:	number of prपूर्णांकed अक्षरacters
 */
पूर्णांक efi_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	अक्षर म_लिखो_buf[256];
	बहु_सूची args;
	पूर्णांक prपूर्णांकed;
	पूर्णांक loglevel = prपूर्णांकk_get_level(fmt);

	चयन (loglevel) अणु
	हाल '0' ... '9':
		loglevel -= '0';
		अवरोध;
	शेष:
		/*
		 * Use loglevel -1 क्रम हालs where we just want to prपूर्णांक to
		 * the screen.
		 */
		loglevel = -1;
		अवरोध;
	पूर्ण

	अगर (loglevel >= efi_loglevel)
		वापस 0;

	अगर (loglevel >= 0)
		efi_माला_दो("EFI stub: ");

	fmt = prपूर्णांकk_skip_level(fmt);

	बहु_शुरू(args, fmt);
	prपूर्णांकed = vsnम_लिखो(म_लिखो_buf, माप(म_लिखो_buf), fmt, args);
	बहु_पूर्ण(args);

	efi_माला_दो(म_लिखो_buf);
	अगर (prपूर्णांकed >= माप(म_लिखो_buf)) अणु
		efi_माला_दो("[Message truncated]\n");
		वापस -1;
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण

/**
 * efi_parse_options() - Parse EFI command line options
 * @cmdline:	kernel command line
 *
 * Parse the ASCII string @cmdline क्रम EFI options, denoted by the efi=
 * option, e.g. efi=nochunk.
 *
 * It should be noted that efi= is parsed in two very dअगरferent
 * environments, first in the early boot environment of the EFI boot
 * stub, and subsequently during the kernel boot.
 *
 * Return:	status code
 */
efi_status_t efi_parse_options(अक्षर स्थिर *cmdline)
अणु
	माप_प्रकार len;
	efi_status_t status;
	अक्षर *str, *buf;

	अगर (!cmdline)
		वापस EFI_SUCCESS;

	len = strnlen(cmdline, COMMAND_LINE_SIZE - 1) + 1;
	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, len, (व्योम **)&buf);
	अगर (status != EFI_SUCCESS)
		वापस status;

	स_नकल(buf, cmdline, len - 1);
	buf[len - 1] = '\0';
	str = skip_spaces(buf);

	जबतक (*str) अणु
		अक्षर *param, *val;

		str = next_arg(str, &param, &val);
		अगर (!val && !म_भेद(param, "--"))
			अवरोध;

		अगर (!म_भेद(param, "nokaslr")) अणु
			efi_nokaslr = true;
		पूर्ण अन्यथा अगर (!म_भेद(param, "quiet")) अणु
			efi_loglevel = CONSOLE_LOGLEVEL_QUIET;
		पूर्ण अन्यथा अगर (!म_भेद(param, "noinitrd")) अणु
			efi_noinitrd = true;
		पूर्ण अन्यथा अगर (!म_भेद(param, "efi") && val) अणु
			efi_nochunk = parse_option_str(val, "nochunk");
			efi_novamap = parse_option_str(val, "novamap");

			efi_nosoftreserve = IS_ENABLED(CONFIG_EFI_SOFT_RESERVE) &&
					    parse_option_str(val, "nosoftreserve");

			अगर (parse_option_str(val, "disable_early_pci_dma"))
				efi_disable_pci_dma = true;
			अगर (parse_option_str(val, "no_disable_early_pci_dma"))
				efi_disable_pci_dma = false;
			अगर (parse_option_str(val, "debug"))
				efi_loglevel = CONSOLE_LOGLEVEL_DEBUG;
		पूर्ण अन्यथा अगर (!म_भेद(param, "video") &&
			   val && strstarts(val, "efifb:")) अणु
			efi_parse_option_graphics(val + म_माप("efifb:"));
		पूर्ण
	पूर्ण
	efi_bs_call(मुक्त_pool, buf);
	वापस EFI_SUCCESS;
पूर्ण

/*
 * The EFI_LOAD_OPTION descriptor has the following layout:
 *	u32 Attributes;
 *	u16 FilePathListLength;
 *	u16 Description[];
 *	efi_device_path_protocol_t FilePathList[];
 *	u8 OptionalData[];
 *
 * This function validates and unpacks the variable-size data fields.
 */
अटल
bool efi_load_option_unpack(efi_load_option_unpacked_t *dest,
			    स्थिर efi_load_option_t *src, माप_प्रकार size)
अणु
	स्थिर व्योम *pos;
	u16 c;
	efi_device_path_protocol_t header;
	स्थिर efi_अक्षर16_t *description;
	स्थिर efi_device_path_protocol_t *file_path_list;

	अगर (size < दुरत्व(efi_load_option_t, variable_data))
		वापस false;
	pos = src->variable_data;
	size -= दुरत्व(efi_load_option_t, variable_data);

	अगर ((src->attributes & ~EFI_LOAD_OPTION_MASK) != 0)
		वापस false;

	/* Scan description. */
	description = pos;
	करो अणु
		अगर (size < माप(c))
			वापस false;
		c = *(स्थिर u16 *)pos;
		pos += माप(c);
		size -= माप(c);
	पूर्ण जबतक (c != L'\0');

	/* Scan file_path_list. */
	file_path_list = pos;
	करो अणु
		अगर (size < माप(header))
			वापस false;
		header = *(स्थिर efi_device_path_protocol_t *)pos;
		अगर (header.length < माप(header))
			वापस false;
		अगर (size < header.length)
			वापस false;
		pos += header.length;
		size -= header.length;
	पूर्ण जबतक ((header.type != EFI_DEV_END_PATH && header.type != EFI_DEV_END_PATH2) ||
		 (header.sub_type != EFI_DEV_END_ENTIRE));
	अगर (pos != (स्थिर व्योम *)file_path_list + src->file_path_list_length)
		वापस false;

	dest->attributes = src->attributes;
	dest->file_path_list_length = src->file_path_list_length;
	dest->description = description;
	dest->file_path_list = file_path_list;
	dest->optional_data_size = size;
	dest->optional_data = size ? pos : शून्य;

	वापस true;
पूर्ण

/*
 * At least some versions of Dell firmware pass the entire contents of the
 * Boot#### variable, i.e. the EFI_LOAD_OPTION descriptor, rather than just the
 * OptionalData field.
 *
 * Detect this हाल and extract OptionalData.
 */
व्योम efi_apply_loaकरोptions_quirk(स्थिर व्योम **load_options, पूर्णांक *load_options_size)
अणु
	स्थिर efi_load_option_t *load_option = *load_options;
	efi_load_option_unpacked_t load_option_unpacked;

	अगर (!IS_ENABLED(CONFIG_X86))
		वापस;
	अगर (!load_option)
		वापस;
	अगर (*load_options_size < माप(*load_option))
		वापस;
	अगर ((load_option->attributes & ~EFI_LOAD_OPTION_BOOT_MASK) != 0)
		वापस;

	अगर (!efi_load_option_unpack(&load_option_unpacked, load_option, *load_options_size))
		वापस;

	efi_warn_once(FW_BUG "LoadOptions is an EFI_LOAD_OPTION descriptor\n");
	efi_warn_once(FW_BUG "Using OptionalData as a workaround\n");

	*load_options = load_option_unpacked.optional_data;
	*load_options_size = load_option_unpacked.optional_data_size;
पूर्ण

/*
 * Convert the unicode UEFI command line to ASCII to pass to kernel.
 * Size of memory allocated वापस in *cmd_line_len.
 * Returns शून्य on error.
 */
अक्षर *efi_convert_cmdline(efi_loaded_image_t *image, पूर्णांक *cmd_line_len)
अणु
	स्थिर u16 *s2;
	अचिन्हित दीर्घ cmdline_addr = 0;
	पूर्णांक options_अक्षरs = efi_table_attr(image, load_options_size);
	स्थिर u16 *options = efi_table_attr(image, load_options);
	पूर्णांक options_bytes = 0, safe_options_bytes = 0;  /* UTF-8 bytes */
	bool in_quote = false;
	efi_status_t status;

	efi_apply_loaकरोptions_quirk((स्थिर व्योम **)&options, &options_अक्षरs);
	options_अक्षरs /= माप(*options);

	अगर (options) अणु
		s2 = options;
		जबतक (options_bytes < COMMAND_LINE_SIZE && options_अक्षरs--) अणु
			u16 c = *s2++;

			अगर (c < 0x80) अणु
				अगर (c == L'\0' || c == L'\n')
					अवरोध;
				अगर (c == L'"')
					in_quote = !in_quote;
				अन्यथा अगर (!in_quote && है_खाली((अक्षर)c))
					safe_options_bytes = options_bytes;

				options_bytes++;
				जारी;
			पूर्ण

			/*
			 * Get the number of UTF-8 bytes corresponding to a
			 * UTF-16 अक्षरacter.
			 * The first part handles everything in the BMP.
			 */
			options_bytes += 2 + (c >= 0x800);
			/*
			 * Add one more byte क्रम valid surrogate pairs. Invalid
			 * surrogates will be replaced with 0xfffd and take up
			 * only 3 bytes.
			 */
			अगर ((c & 0xfc00) == 0xd800) अणु
				/*
				 * If the very last word is a high surrogate,
				 * we must ignore it since we can't access the
				 * low surrogate.
				 */
				अगर (!options_अक्षरs) अणु
					options_bytes -= 3;
				पूर्ण अन्यथा अगर ((*s2 & 0xfc00) == 0xdc00) अणु
					options_bytes++;
					options_अक्षरs--;
					s2++;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (options_bytes >= COMMAND_LINE_SIZE) अणु
			options_bytes = safe_options_bytes;
			efi_err("Command line is too long: truncated to %d bytes\n",
				options_bytes);
		पूर्ण
	पूर्ण

	options_bytes++;	/* NUL termination */

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, options_bytes,
			     (व्योम **)&cmdline_addr);
	अगर (status != EFI_SUCCESS)
		वापस शून्य;

	snम_लिखो((अक्षर *)cmdline_addr, options_bytes, "%.*ls",
		 options_bytes - 1, options);

	*cmd_line_len = options_bytes;
	वापस (अक्षर *)cmdline_addr;
पूर्ण

/**
 * efi_निकास_boot_services() - Exit boot services
 * @handle:	handle of the निकासing image
 * @map:	poपूर्णांकer to receive the memory map
 * @priv:	argument to be passed to @priv_func
 * @priv_func:	function to process the memory map beक्रमe निकासing boot services
 *
 * Handle calling ExitBootServices according to the requirements set out by the
 * spec.  Obtains the current memory map, and वापसs that info after calling
 * ExitBootServices.  The client must specअगरy a function to perक्रमm any
 * processing of the memory map data prior to ExitBootServices.  A client
 * specअगरic काष्ठाure may be passed to the function via priv.  The client
 * function may be called multiple बार.
 *
 * Return:	status code
 */
efi_status_t efi_निकास_boot_services(व्योम *handle,
				    काष्ठा efi_boot_memmap *map,
				    व्योम *priv,
				    efi_निकास_boot_map_processing priv_func)
अणु
	efi_status_t status;

	status = efi_get_memory_map(map);

	अगर (status != EFI_SUCCESS)
		जाओ fail;

	status = priv_func(map, priv);
	अगर (status != EFI_SUCCESS)
		जाओ मुक्त_map;

	अगर (efi_disable_pci_dma)
		efi_pci_disable_bridge_busmaster();

	status = efi_bs_call(निकास_boot_services, handle, *map->key_ptr);

	अगर (status == EFI_INVALID_PARAMETER) अणु
		/*
		 * The memory map changed between efi_get_memory_map() and
		 * निकास_boot_services().  Per the UEFI Spec v2.6, Section 6.4:
		 * EFI_BOOT_SERVICES.ExitBootServices we need to get the
		 * updated map, and try again.  The spec implies one retry
		 * should be sufficent, which is confirmed against the EDK2
		 * implementation.  Per the spec, we can only invoke
		 * get_memory_map() and निकास_boot_services() - we cannot alloc
		 * so efi_get_memory_map() cannot be used, and we must reuse
		 * the buffer.  For all practical purposes, the headroom in the
		 * buffer should account क्रम any changes in the map so the call
		 * to get_memory_map() is expected to succeed here.
		 */
		*map->map_size = *map->buff_size;
		status = efi_bs_call(get_memory_map,
				     map->map_size,
				     *map->map,
				     map->key_ptr,
				     map->desc_size,
				     map->desc_ver);

		/* निकास_boot_services() was called, thus cannot मुक्त */
		अगर (status != EFI_SUCCESS)
			जाओ fail;

		status = priv_func(map, priv);
		/* निकास_boot_services() was called, thus cannot मुक्त */
		अगर (status != EFI_SUCCESS)
			जाओ fail;

		status = efi_bs_call(निकास_boot_services, handle, *map->key_ptr);
	पूर्ण

	/* निकास_boot_services() was called, thus cannot मुक्त */
	अगर (status != EFI_SUCCESS)
		जाओ fail;

	वापस EFI_SUCCESS;

मुक्त_map:
	efi_bs_call(मुक्त_pool, *map->map);
fail:
	वापस status;
पूर्ण

/**
 * get_efi_config_table() - retrieve UEFI configuration table
 * @guid:	GUID of the configuration table to be retrieved
 * Return:	poपूर्णांकer to the configuration table or शून्य
 */
व्योम *get_efi_config_table(efi_guid_t guid)
अणु
	अचिन्हित दीर्घ tables = efi_table_attr(efi_प्रणाली_table, tables);
	पूर्णांक nr_tables = efi_table_attr(efi_प्रणाली_table, nr_tables);
	पूर्णांक i;

	क्रम (i = 0; i < nr_tables; i++) अणु
		efi_config_table_t *t = (व्योम *)tables;

		अगर (efi_guidcmp(t->guid, guid) == 0)
			वापस efi_table_attr(t, table);

		tables += efi_is_native() ? माप(efi_config_table_t)
					  : माप(efi_config_table_32_t);
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * The LINUX_EFI_INITRD_MEDIA_GUID venकरोr media device path below provides a way
 * क्रम the firmware or bootloader to expose the initrd data directly to the stub
 * via the trivial LoadFile2 protocol, which is defined in the UEFI spec, and is
 * very easy to implement. It is a simple Linux initrd specअगरic conduit between
 * kernel and firmware, allowing us to put the EFI stub (being part of the
 * kernel) in अक्षरge of where and when to load the initrd, जबतक leaving it up
 * to the firmware to decide whether it needs to expose its fileप्रणाली hierarchy
 * via EFI protocols.
 */
अटल स्थिर काष्ठा अणु
	काष्ठा efi_venकरोr_dev_path	venकरोr;
	काष्ठा efi_generic_dev_path	end;
पूर्ण __packed initrd_dev_path = अणु
	अणु
		अणु
			EFI_DEV_MEDIA,
			EFI_DEV_MEDIA_VENDOR,
			माप(काष्ठा efi_venकरोr_dev_path),
		पूर्ण,
		LINUX_EFI_INITRD_MEDIA_GUID
	पूर्ण, अणु
		EFI_DEV_END_PATH,
		EFI_DEV_END_ENTIRE,
		माप(काष्ठा efi_generic_dev_path)
	पूर्ण
पूर्ण;

/**
 * efi_load_initrd_dev_path() - load the initrd from the Linux initrd device path
 * @load_addr:	poपूर्णांकer to store the address where the initrd was loaded
 * @load_size:	poपूर्णांकer to store the size of the loaded initrd
 * @max:	upper limit क्रम the initrd memory allocation
 *
 * Return:
 * * %EFI_SUCCESS अगर the initrd was loaded successfully, in which
 *   हाल @load_addr and @load_size are asचिन्हित accordingly
 * * %EFI_NOT_FOUND अगर no LoadFile2 protocol exists on the initrd device path
 * * %EFI_INVALID_PARAMETER अगर load_addr == शून्य or load_size == शून्य
 * * %EFI_OUT_OF_RESOURCES अगर memory allocation failed
 * * %EFI_LOAD_ERROR in all other हालs
 */
अटल
efi_status_t efi_load_initrd_dev_path(अचिन्हित दीर्घ *load_addr,
				      अचिन्हित दीर्घ *load_size,
				      अचिन्हित दीर्घ max)
अणु
	efi_guid_t lf2_proto_guid = EFI_LOAD_खाता2_PROTOCOL_GUID;
	efi_device_path_protocol_t *dp;
	efi_load_file2_protocol_t *lf2;
	अचिन्हित दीर्घ initrd_addr;
	अचिन्हित दीर्घ initrd_size;
	efi_handle_t handle;
	efi_status_t status;

	dp = (efi_device_path_protocol_t *)&initrd_dev_path;
	status = efi_bs_call(locate_device_path, &lf2_proto_guid, &dp, &handle);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_bs_call(handle_protocol, handle, &lf2_proto_guid,
			     (व्योम **)&lf2);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_call_proto(lf2, load_file, dp, false, &initrd_size, शून्य);
	अगर (status != EFI_BUFFER_TOO_SMALL)
		वापस EFI_LOAD_ERROR;

	status = efi_allocate_pages(initrd_size, &initrd_addr, max);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_call_proto(lf2, load_file, dp, false, &initrd_size,
				(व्योम *)initrd_addr);
	अगर (status != EFI_SUCCESS) अणु
		efi_मुक्त(initrd_size, initrd_addr);
		वापस EFI_LOAD_ERROR;
	पूर्ण

	*load_addr = initrd_addr;
	*load_size = initrd_size;
	वापस EFI_SUCCESS;
पूर्ण

अटल
efi_status_t efi_load_initrd_cmdline(efi_loaded_image_t *image,
				     अचिन्हित दीर्घ *load_addr,
				     अचिन्हित दीर्घ *load_size,
				     अचिन्हित दीर्घ soft_limit,
				     अचिन्हित दीर्घ hard_limit)
अणु
	अगर (!IS_ENABLED(CONFIG_EFI_GENERIC_STUB_INITRD_CMDLINE_LOADER) ||
	    (IS_ENABLED(CONFIG_X86) && (!efi_is_native() || image == शून्य))) अणु
		*load_addr = *load_size = 0;
		वापस EFI_SUCCESS;
	पूर्ण

	वापस handle_cmdline_files(image, L"initrd=", माप(L"initrd=") - 2,
				    soft_limit, hard_limit,
				    load_addr, load_size);
पूर्ण

/**
 * efi_load_initrd() - Load initial RAM disk
 * @image:	EFI loaded image protocol
 * @load_addr:	poपूर्णांकer to loaded initrd
 * @load_size:	size of loaded initrd
 * @soft_limit:	preferred size of allocated memory क्रम loading the initrd
 * @hard_limit:	minimum size of allocated memory
 *
 * Return:	status code
 */
efi_status_t efi_load_initrd(efi_loaded_image_t *image,
			     अचिन्हित दीर्घ *load_addr,
			     अचिन्हित दीर्घ *load_size,
			     अचिन्हित दीर्घ soft_limit,
			     अचिन्हित दीर्घ hard_limit)
अणु
	efi_status_t status;

	अगर (!load_addr || !load_size)
		वापस EFI_INVALID_PARAMETER;

	status = efi_load_initrd_dev_path(load_addr, load_size, hard_limit);
	अगर (status == EFI_SUCCESS) अणु
		efi_info("Loaded initrd from LINUX_EFI_INITRD_MEDIA_GUID device path\n");
	पूर्ण अन्यथा अगर (status == EFI_NOT_FOUND) अणु
		status = efi_load_initrd_cmdline(image, load_addr, load_size,
						 soft_limit, hard_limit);
		अगर (status == EFI_SUCCESS && *load_size > 0)
			efi_info("Loaded initrd from command line option\n");
	पूर्ण

	वापस status;
पूर्ण

/**
 * efi_रुको_क्रम_key() - Wait क्रम key stroke
 * @usec:	number of microseconds to रुको क्रम key stroke
 * @key:	key entered
 *
 * Wait क्रम up to @usec microseconds क्रम a key stroke.
 *
 * Return:	status code, EFI_SUCCESS अगर key received
 */
efi_status_t efi_रुको_क्रम_key(अचिन्हित दीर्घ usec, efi_input_key_t *key)
अणु
	efi_event_t events[2], समयr;
	अचिन्हित दीर्घ index;
	efi_simple_text_input_protocol_t *con_in;
	efi_status_t status;

	con_in = efi_table_attr(efi_प्रणाली_table, con_in);
	अगर (!con_in)
		वापस EFI_UNSUPPORTED;
	efi_set_event_at(events, 0, efi_table_attr(con_in, रुको_क्रम_key));

	status = efi_bs_call(create_event, EFI_EVT_TIMER, 0, शून्य, शून्य, &समयr);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_bs_call(set_समयr, समयr, EfiTimerRelative,
			     EFI_100NSEC_PER_USEC * usec);
	अगर (status != EFI_SUCCESS)
		वापस status;
	efi_set_event_at(events, 1, समयr);

	status = efi_bs_call(रुको_क्रम_event, 2, events, &index);
	अगर (status == EFI_SUCCESS) अणु
		अगर (index == 0)
			status = efi_call_proto(con_in, पढ़ो_keystroke, key);
		अन्यथा
			status = EFI_TIMEOUT;
	पूर्ण

	efi_bs_call(बंद_event, समयr);

	वापस status;
पूर्ण
