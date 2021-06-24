<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/libfdt_env.h>
#समावेश <यंत्र/setup.h>
#समावेश <libfdt.h>

#अगर defined(CONFIG_ARM_ATAG_DTB_COMPAT_CMDLINE_EXTEND)
#घोषणा करो_extend_cmdline 1
#अन्यथा
#घोषणा करो_extend_cmdline 0
#पूर्ण_अगर

#घोषणा NR_BANKS 16

अटल पूर्णांक node_offset(व्योम *fdt, स्थिर अक्षर *node_path)
अणु
	पूर्णांक offset = fdt_path_offset(fdt, node_path);
	अगर (offset == -FDT_ERR_NOTFOUND)
		/* Add the node to root अगर not found, dropping the leading '/' */
		offset = fdt_add_subnode(fdt, 0, node_path + 1);
	वापस offset;
पूर्ण

अटल पूर्णांक setprop(व्योम *fdt, स्थिर अक्षर *node_path, स्थिर अक्षर *property,
		   व्योम *val_array, पूर्णांक size)
अणु
	पूर्णांक offset = node_offset(fdt, node_path);
	अगर (offset < 0)
		वापस offset;
	वापस fdt_setprop(fdt, offset, property, val_array, size);
पूर्ण

अटल पूर्णांक setprop_string(व्योम *fdt, स्थिर अक्षर *node_path,
			  स्थिर अक्षर *property, स्थिर अक्षर *string)
अणु
	पूर्णांक offset = node_offset(fdt, node_path);
	अगर (offset < 0)
		वापस offset;
	वापस fdt_setprop_string(fdt, offset, property, string);
पूर्ण

अटल पूर्णांक setprop_cell(व्योम *fdt, स्थिर अक्षर *node_path,
			स्थिर अक्षर *property, uपूर्णांक32_t val)
अणु
	पूर्णांक offset = node_offset(fdt, node_path);
	अगर (offset < 0)
		वापस offset;
	वापस fdt_setprop_cell(fdt, offset, property, val);
पूर्ण

अटल स्थिर व्योम *getprop(स्थिर व्योम *fdt, स्थिर अक्षर *node_path,
			   स्थिर अक्षर *property, पूर्णांक *len)
अणु
	पूर्णांक offset = fdt_path_offset(fdt, node_path);

	अगर (offset == -FDT_ERR_NOTFOUND)
		वापस शून्य;

	वापस fdt_getprop(fdt, offset, property, len);
पूर्ण

अटल uपूर्णांक32_t get_cell_size(स्थिर व्योम *fdt)
अणु
	पूर्णांक len;
	uपूर्णांक32_t cell_size = 1;
	स्थिर __be32 *size_len =  getprop(fdt, "/", "#size-cells", &len);

	अगर (size_len)
		cell_size = fdt32_to_cpu(*size_len);
	वापस cell_size;
पूर्ण

अटल व्योम merge_fdt_bootargs(व्योम *fdt, स्थिर अक्षर *fdt_cmdline)
अणु
	अक्षर cmdline[COMMAND_LINE_SIZE];
	स्थिर अक्षर *fdt_bootargs;
	अक्षर *ptr = cmdline;
	पूर्णांक len = 0;

	/* copy the fdt command line पूर्णांकo the buffer */
	fdt_bootargs = getprop(fdt, "/chosen", "bootargs", &len);
	अगर (fdt_bootargs)
		अगर (len < COMMAND_LINE_SIZE) अणु
			स_नकल(ptr, fdt_bootargs, len);
			/* len is the length of the string
			 * including the शून्य terminator */
			ptr += len - 1;
		पूर्ण

	/* and append the ATAG_CMDLINE */
	अगर (fdt_cmdline) अणु
		len = म_माप(fdt_cmdline);
		अगर (ptr - cmdline + len + 2 < COMMAND_LINE_SIZE) अणु
			*ptr++ = ' ';
			स_नकल(ptr, fdt_cmdline, len);
			ptr += len;
		पूर्ण
	पूर्ण
	*ptr = '\0';

	setprop_string(fdt, "/chosen", "bootargs", cmdline);
पूर्ण

अटल व्योम hex_str(अक्षर *out, uपूर्णांक32_t value)
अणु
	uपूर्णांक32_t digit;
	पूर्णांक idx;

	क्रम (idx = 7; idx >= 0; idx--) अणु
		digit = value >> 28;
		value <<= 4;
		digit &= 0xf;
		अगर (digit < 10)
			digit += '0';
		अन्यथा
			digit += 'A'-10;
		*out++ = digit;
	पूर्ण
	*out = '\0';
पूर्ण

/*
 * Convert and fold provided ATAGs पूर्णांकo the provided FDT.
 *
 * REturn values:
 *    = 0 -> pretend success
 *    = 1 -> bad ATAG (may retry with another possible ATAG poपूर्णांकer)
 *    < 0 -> error from libfdt
 */
पूर्णांक atags_to_fdt(व्योम *atag_list, व्योम *fdt, पूर्णांक total_space)
अणु
	काष्ठा tag *atag = atag_list;
	/* In the हाल of 64 bits memory size, need to reserve 2 cells क्रम
	 * address and size क्रम each bank */
	__be32 mem_reg_property[2 * 2 * NR_BANKS];
	पूर्णांक memcount = 0;
	पूर्णांक ret, memsize;

	/* make sure we've got an aligned poपूर्णांकer */
	अगर ((u32)atag_list & 0x3)
		वापस 1;

	/* अगर we get a DTB here we're करोne alपढ़ोy */
	अगर (*(__be32 *)atag_list == cpu_to_fdt32(FDT_MAGIC))
	       वापस 0;

	/* validate the ATAG */
	अगर (atag->hdr.tag != ATAG_CORE ||
	    (atag->hdr.size != tag_size(tag_core) &&
	     atag->hdr.size != 2))
		वापस 1;

	/* let's give it all the room it could need */
	ret = fdt_खोलो_पूर्णांकo(fdt, fdt, total_space);
	अगर (ret < 0)
		वापस ret;

	क्रम_each_tag(atag, atag_list) अणु
		अगर (atag->hdr.tag == ATAG_CMDLINE) अणु
			/* Append the ATAGS command line to the device tree
			 * command line.
			 * NB: This means that अगर the same parameter is set in
			 * the device tree and in the tags, the one from the
			 * tags will be chosen.
			 */
			अगर (करो_extend_cmdline)
				merge_fdt_bootargs(fdt,
						   atag->u.cmdline.cmdline);
			अन्यथा
				setprop_string(fdt, "/chosen", "bootargs",
					       atag->u.cmdline.cmdline);
		पूर्ण अन्यथा अगर (atag->hdr.tag == ATAG_MEM) अणु
			अगर (memcount >= माप(mem_reg_property)/4)
				जारी;
			अगर (!atag->u.mem.size)
				जारी;
			memsize = get_cell_size(fdt);

			अगर (memsize == 2) अणु
				/* अगर memsize is 2, that means that
				 * each data needs 2 cells of 32 bits,
				 * so the data are 64 bits */
				__be64 *mem_reg_prop64 =
					(__be64 *)mem_reg_property;
				mem_reg_prop64[memcount++] =
					cpu_to_fdt64(atag->u.mem.start);
				mem_reg_prop64[memcount++] =
					cpu_to_fdt64(atag->u.mem.size);
			पूर्ण अन्यथा अणु
				mem_reg_property[memcount++] =
					cpu_to_fdt32(atag->u.mem.start);
				mem_reg_property[memcount++] =
					cpu_to_fdt32(atag->u.mem.size);
			पूर्ण

		पूर्ण अन्यथा अगर (atag->hdr.tag == ATAG_INITRD2) अणु
			uपूर्णांक32_t initrd_start, initrd_size;
			initrd_start = atag->u.initrd.start;
			initrd_size = atag->u.initrd.size;
			setprop_cell(fdt, "/chosen", "linux,initrd-start",
					initrd_start);
			setprop_cell(fdt, "/chosen", "linux,initrd-end",
					initrd_start + initrd_size);
		पूर्ण अन्यथा अगर (atag->hdr.tag == ATAG_SERIAL) अणु
			अक्षर serno[16+2];
			hex_str(serno, atag->u.serialnr.high);
			hex_str(serno+8, atag->u.serialnr.low);
			setprop_string(fdt, "/", "serial-number", serno);
		पूर्ण
	पूर्ण

	अगर (memcount) अणु
		setprop(fdt, "/memory", "reg", mem_reg_property,
			4 * memcount * memsize);
	पूर्ण

	वापस fdt_pack(fdt);
पूर्ण
