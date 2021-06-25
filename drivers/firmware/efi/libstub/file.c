<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helper functions used by the EFI stub on multiple
 * architectures. This should be #समावेशd by the EFI stub
 * implementation files.
 *
 * Copyright 2011 Intel Corporation; author Matt Fleming
 */

#समावेश <linux/efi.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

#घोषणा MAX_खाताNAME_SIZE	256

/*
 * Some firmware implementations have problems पढ़ोing files in one go.
 * A पढ़ो chunk size of 1MB seems to work क्रम most platक्रमms.
 *
 * Unक्रमtunately, पढ़ोing files in chunks triggers *other* bugs on some
 * platक्रमms, so we provide a way to disable this workaround, which can
 * be करोne by passing "efi=nochunk" on the EFI boot stub command line.
 *
 * If you experience issues with initrd images being corrupt it's worth
 * trying efi=nochunk, but chunking is enabled by शेष on x86 because
 * there are far more machines that require the workaround than those that
 * अवरोध with it enabled.
 */
#घोषणा EFI_READ_CHUNK_SIZE	SZ_1M

काष्ठा finfo अणु
	efi_file_info_t info;
	efi_अक्षर16_t	filename[MAX_खाताNAME_SIZE];
पूर्ण;

अटल efi_status_t efi_खोलो_file(efi_file_protocol_t *volume,
				  काष्ठा finfo *fi,
				  efi_file_protocol_t **handle,
				  अचिन्हित दीर्घ *file_size)
अणु
	efi_guid_t info_guid = EFI_खाता_INFO_ID;
	efi_file_protocol_t *fh;
	अचिन्हित दीर्घ info_sz;
	efi_status_t status;

	status = volume->खोलो(volume, &fh, fi->filename, EFI_खाता_MODE_READ, 0);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to open file: %ls\n", fi->filename);
		वापस status;
	पूर्ण

	info_sz = माप(काष्ठा finfo);
	status = fh->get_info(fh, &info_guid, &info_sz, fi);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to get file info\n");
		fh->बंद(fh);
		वापस status;
	पूर्ण

	*handle = fh;
	*file_size = fi->info.file_size;
	वापस EFI_SUCCESS;
पूर्ण

अटल efi_status_t efi_खोलो_volume(efi_loaded_image_t *image,
				    efi_file_protocol_t **fh)
अणु
	efi_guid_t fs_proto = EFI_खाता_SYSTEM_GUID;
	efi_simple_file_प्रणाली_protocol_t *io;
	efi_status_t status;

	status = efi_bs_call(handle_protocol, image->device_handle, &fs_proto,
			     (व्योम **)&io);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to handle fs_proto\n");
		वापस status;
	पूर्ण

	status = io->खोलो_volume(io, fh);
	अगर (status != EFI_SUCCESS)
		efi_err("Failed to open volume\n");

	वापस status;
पूर्ण

अटल पूर्णांक find_file_option(स्थिर efi_अक्षर16_t *cmdline, पूर्णांक cmdline_len,
			    स्थिर efi_अक्षर16_t *prefix, पूर्णांक prefix_size,
			    efi_अक्षर16_t *result, पूर्णांक result_len)
अणु
	पूर्णांक prefix_len = prefix_size / 2;
	bool found = false;
	पूर्णांक i;

	क्रम (i = prefix_len; i < cmdline_len; i++) अणु
		अगर (!स_भेद(&cmdline[i - prefix_len], prefix, prefix_size)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस 0;

	/* Skip any leading slashes */
	जबतक (i < cmdline_len && (cmdline[i] == L'/' || cmdline[i] == L'\\'))
		i++;

	जबतक (--result_len > 0 && i < cmdline_len) अणु
		efi_अक्षर16_t c = cmdline[i++];

		अगर (c == L'\0' || c == L'\n' || c == L' ')
			अवरोध;
		अन्यथा अगर (c == L'/')
			/* Replace UNIX dir separators with EFI standard ones */
			*result++ = L'\\';
		अन्यथा
			*result++ = c;
	पूर्ण
	*result = L'\0';
	वापस i;
पूर्ण

/*
 * Check the cmdline क्रम a LILO-style file= arguments.
 *
 * We only support loading a file from the same fileप्रणाली as
 * the kernel image.
 */
efi_status_t handle_cmdline_files(efi_loaded_image_t *image,
				  स्थिर efi_अक्षर16_t *optstr,
				  पूर्णांक optstr_size,
				  अचिन्हित दीर्घ soft_limit,
				  अचिन्हित दीर्घ hard_limit,
				  अचिन्हित दीर्घ *load_addr,
				  अचिन्हित दीर्घ *load_size)
अणु
	स्थिर efi_अक्षर16_t *cmdline = image->load_options;
	पूर्णांक cmdline_len = image->load_options_size;
	अचिन्हित दीर्घ efi_chunk_size = अच_दीर्घ_उच्च;
	efi_file_protocol_t *volume = शून्य;
	efi_file_protocol_t *file;
	अचिन्हित दीर्घ alloc_addr;
	अचिन्हित दीर्घ alloc_size;
	efi_status_t status;
	पूर्णांक offset;

	अगर (!load_addr || !load_size)
		वापस EFI_INVALID_PARAMETER;

	efi_apply_loaकरोptions_quirk((स्थिर व्योम **)&cmdline, &cmdline_len);
	cmdline_len /= माप(*cmdline);

	अगर (IS_ENABLED(CONFIG_X86) && !efi_nochunk)
		efi_chunk_size = EFI_READ_CHUNK_SIZE;

	alloc_addr = alloc_size = 0;
	करो अणु
		काष्ठा finfo fi;
		अचिन्हित दीर्घ size;
		व्योम *addr;

		offset = find_file_option(cmdline, cmdline_len,
					  optstr, optstr_size,
					  fi.filename, ARRAY_SIZE(fi.filename));

		अगर (!offset)
			अवरोध;

		cmdline += offset;
		cmdline_len -= offset;

		अगर (!volume) अणु
			status = efi_खोलो_volume(image, &volume);
			अगर (status != EFI_SUCCESS)
				वापस status;
		पूर्ण

		status = efi_खोलो_file(volume, &fi, &file, &size);
		अगर (status != EFI_SUCCESS)
			जाओ err_बंद_volume;

		/*
		 * Check whether the existing allocation can contain the next
		 * file. This condition will also trigger naturally during the
		 * first (and typically only) iteration of the loop, given that
		 * alloc_size == 0 in that हाल.
		 */
		अगर (round_up(alloc_size + size, EFI_ALLOC_ALIGN) >
		    round_up(alloc_size, EFI_ALLOC_ALIGN)) अणु
			अचिन्हित दीर्घ old_addr = alloc_addr;

			status = EFI_OUT_OF_RESOURCES;
			अगर (soft_limit < hard_limit)
				status = efi_allocate_pages(alloc_size + size,
							    &alloc_addr,
							    soft_limit);
			अगर (status == EFI_OUT_OF_RESOURCES)
				status = efi_allocate_pages(alloc_size + size,
							    &alloc_addr,
							    hard_limit);
			अगर (status != EFI_SUCCESS) अणु
				efi_err("Failed to allocate memory for files\n");
				जाओ err_बंद_file;
			पूर्ण

			अगर (old_addr != 0) अणु
				/*
				 * This is not the first समय we've gone
				 * around this loop, and so we are loading
				 * multiple files that need to be concatenated
				 * and वापसed in a single buffer.
				 */
				स_नकल((व्योम *)alloc_addr, (व्योम *)old_addr, alloc_size);
				efi_मुक्त(alloc_size, old_addr);
			पूर्ण
		पूर्ण

		addr = (व्योम *)alloc_addr + alloc_size;
		alloc_size += size;

		जबतक (size) अणु
			अचिन्हित दीर्घ chunksize = min(size, efi_chunk_size);

			status = file->पढ़ो(file, &chunksize, addr);
			अगर (status != EFI_SUCCESS) अणु
				efi_err("Failed to read file\n");
				जाओ err_बंद_file;
			पूर्ण
			addr += chunksize;
			size -= chunksize;
		पूर्ण
		file->बंद(file);
	पूर्ण जबतक (offset > 0);

	*load_addr = alloc_addr;
	*load_size = alloc_size;

	अगर (volume)
		volume->बंद(volume);
	वापस EFI_SUCCESS;

err_बंद_file:
	file->बंद(file);

err_बंद_volume:
	volume->बंद(volume);
	efi_मुक्त(alloc_size, alloc_addr);
	वापस status;
पूर्ण
