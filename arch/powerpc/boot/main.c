<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Paul Mackerras 1997.
 *
 * Updates क्रम PPC64 by Todd Inglett, Dave Engebretsen & Peter Bergner.
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "elf.h"
#समावेश "page.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "ops.h"
#समावेश "reg.h"

काष्ठा addr_range अणु
	व्योम *addr;
	अचिन्हित दीर्घ size;
पूर्ण;

#अघोषित DEBUG

अटल काष्ठा addr_range prep_kernel(व्योम)
अणु
	अक्षर elfheader[256];
	अचिन्हित अक्षर *vmlinuz_addr = (अचिन्हित अक्षर *)_vmlinux_start;
	अचिन्हित दीर्घ vmlinuz_size = _vmlinux_end - _vmlinux_start;
	व्योम *addr = 0;
	काष्ठा elf_info ei;
	दीर्घ len;
	पूर्णांक uncompressed_image = 0;

	len = partial_decompress(vmlinuz_addr, vmlinuz_size,
		elfheader, माप(elfheader), 0);
	/* assume uncompressed data अगर -1 is वापसed */
	अगर (len == -1) अणु
		uncompressed_image = 1;
		स_नकल(elfheader, vmlinuz_addr, माप(elfheader));
		म_लिखो("No valid compressed data found, assume uncompressed data\n\r");
	पूर्ण

	अगर (!parse_elf64(elfheader, &ei) && !parse_elf32(elfheader, &ei))
		fatal("Error: not a valid PPC32 or PPC64 ELF file!\n\r");

	अगर (platक्रमm_ops.image_hdr)
		platक्रमm_ops.image_hdr(elfheader);

	/* We need to alloc the memsize: gzip will expand the kernel
	 * text/data, then possible rubbish we करोn't care about. But
	 * the kernel bss must be claimed (it will be zero'd by the
	 * kernel itself)
	 */
	म_लिखो("Allocating 0x%lx bytes for kernel...\n\r", ei.memsize);

	अगर (platक्रमm_ops.vmlinux_alloc) अणु
		addr = platक्रमm_ops.vmlinux_alloc(ei.memsize);
	पूर्ण अन्यथा अणु
		/*
		 * Check अगर the kernel image (without bss) would overग_लिखो the
		 * bootwrapper. The device tree has been moved in fdt_init()
		 * to an area allocated with दो_स्मृति() (somewhere past _end).
		 */
		अगर ((अचिन्हित दीर्घ)_start < ei.loadsize)
			fatal("Insufficient memory for kernel at address 0!"
			       " (_start=%p, uncompressed size=%08lx)\n\r",
			       _start, ei.loadsize);

		अगर ((अचिन्हित दीर्घ)_end < ei.memsize)
			fatal("The final kernel image would overwrite the "
					"device tree\n\r");
	पूर्ण

	अगर (uncompressed_image) अणु
		स_नकल(addr, vmlinuz_addr + ei.elfoffset, ei.loadsize);
		म_लिखो("0x%lx bytes of uncompressed data copied\n\r",
		       ei.loadsize);
		जाओ out;
	पूर्ण

	/* Finally, decompress the kernel */
	म_लिखो("Decompressing (0x%p <- 0x%p:0x%p)...\n\r", addr,
	       vmlinuz_addr, vmlinuz_addr+vmlinuz_size);

	len = partial_decompress(vmlinuz_addr, vmlinuz_size,
		addr, ei.loadsize, ei.elfoffset);

	अगर (len < 0)
		fatal("Decompression failed with error code %ld\n\r", len);

	अगर (len != ei.loadsize)
		 fatal("Decompression error: got 0x%lx bytes, expected 0x%lx.\n\r",
			 len, ei.loadsize);

	म_लिखो("Done! Decompressed 0x%lx bytes\n\r", len);
out:
	flush_cache(addr, ei.loadsize);

	वापस (काष्ठा addr_range)अणुaddr, ei.memsizeपूर्ण;
पूर्ण

अटल काष्ठा addr_range prep_initrd(काष्ठा addr_range vmlinux, व्योम *chosen,
				     अचिन्हित दीर्घ initrd_addr,
				     अचिन्हित दीर्घ initrd_size)
अणु
	/* If we have an image attached to us, it overrides anything
	 * supplied by the loader. */
	अगर (&_initrd_end > &_initrd_start) अणु
		म_लिखो("Attached initrd image at 0x%p-0x%p\n\r",
		       _initrd_start, _initrd_end);
		initrd_addr = (अचिन्हित दीर्घ)_initrd_start;
		initrd_size = _initrd_end - _initrd_start;
	पूर्ण अन्यथा अगर (initrd_size > 0) अणु
		म_लिखो("Using loader supplied ramdisk at 0x%lx-0x%lx\n\r",
		       initrd_addr, initrd_addr + initrd_size);
	पूर्ण

	/* If there's no initrd at all, we're करोne */
	अगर (! initrd_size)
		वापस (काष्ठा addr_range)अणु0, 0पूर्ण;

	/*
	 * If the initrd is too low it will be clobbered when the
	 * kernel relocates to its final location.  In this हाल,
	 * allocate a safer place and move it.
	 */
	अगर (initrd_addr < vmlinux.size) अणु
		व्योम *old_addr = (व्योम *)initrd_addr;

		म_लिखो("Allocating 0x%lx bytes for initrd ...\n\r",
		       initrd_size);
		initrd_addr = (अचिन्हित दीर्घ)दो_स्मृति(initrd_size);
		अगर (! initrd_addr)
			fatal("Can't allocate memory for initial "
			       "ramdisk !\n\r");
		म_लिखो("Relocating initrd 0x%lx <- 0x%p (0x%lx bytes)\n\r",
		       initrd_addr, old_addr, initrd_size);
		स_हटाओ((व्योम *)initrd_addr, old_addr, initrd_size);
	पूर्ण

	म_लिखो("initrd head: 0x%lx\n\r", *((अचिन्हित दीर्घ *)initrd_addr));

	/* Tell the kernel initrd address via device tree */
	setprop_val(chosen, "linux,initrd-start", (u32)(initrd_addr));
	setprop_val(chosen, "linux,initrd-end", (u32)(initrd_addr+initrd_size));

	वापस (काष्ठा addr_range)अणु(व्योम *)initrd_addr, initrd_sizeपूर्ण;
पूर्ण

#अगर_घोषित __घातerpc64__
अटल व्योम prep_esm_blob(काष्ठा addr_range vmlinux, व्योम *chosen)
अणु
	अचिन्हित दीर्घ esm_blob_addr, esm_blob_size;

	/* Do we have an ESM (Enter Secure Mode) blob? */
	अगर (&_esm_blob_end <= &_esm_blob_start)
		वापस;

	म_लिखो("Attached ESM blob at 0x%p-0x%p\n\r",
	       _esm_blob_start, _esm_blob_end);
	esm_blob_addr = (अचिन्हित दीर्घ)_esm_blob_start;
	esm_blob_size = _esm_blob_end - _esm_blob_start;

	/*
	 * If the ESM blob is too low it will be clobbered when the
	 * kernel relocates to its final location.  In this हाल,
	 * allocate a safer place and move it.
	 */
	अगर (esm_blob_addr < vmlinux.size) अणु
		व्योम *old_addr = (व्योम *)esm_blob_addr;

		म_लिखो("Allocating 0x%lx bytes for esm_blob ...\n\r",
		       esm_blob_size);
		esm_blob_addr = (अचिन्हित दीर्घ)दो_स्मृति(esm_blob_size);
		अगर (!esm_blob_addr)
			fatal("Can't allocate memory for ESM blob !\n\r");
		म_लिखो("Relocating ESM blob 0x%lx <- 0x%p (0x%lx bytes)\n\r",
		       esm_blob_addr, old_addr, esm_blob_size);
		स_हटाओ((व्योम *)esm_blob_addr, old_addr, esm_blob_size);
	पूर्ण

	/* Tell the kernel ESM blob address via device tree. */
	setprop_val(chosen, "linux,esm-blob-start", (u32)(esm_blob_addr));
	setprop_val(chosen, "linux,esm-blob-end", (u32)(esm_blob_addr + esm_blob_size));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम prep_esm_blob(काष्ठा addr_range vmlinux, व्योम *chosen) अणु पूर्ण
#पूर्ण_अगर

/* A buffer that may be edited by tools operating on a zImage binary so as to
 * edit the command line passed to vmlinux (by setting /chosen/bootargs).
 * The buffer is put in it's own section so that tools may locate it easier.
 */
अटल अक्षर cmdline[BOOT_COMMAND_LINE_SIZE]
	__attribute__((__section__("__builtin_cmdline")));

अटल व्योम prep_cmdline(व्योम *chosen)
अणु
	अचिन्हित पूर्णांक getline_समयout = 5000;
	पूर्णांक v;
	पूर्णांक n;

	/* Wait-क्रम-input समय */
	n = getprop(chosen, "linux,cmdline-timeout", &v, माप(v));
	अगर (n == माप(v))
		getline_समयout = v;

	अगर (cmdline[0] == '\0')
		getprop(chosen, "bootargs", cmdline, BOOT_COMMAND_LINE_SIZE-1);

	म_लिखो("\n\rLinux/PowerPC load: %s", cmdline);

	/* If possible, edit the command line */
	अगर (console_ops.edit_cmdline && getline_समयout)
		console_ops.edit_cmdline(cmdline, BOOT_COMMAND_LINE_SIZE, getline_समयout);

	म_लिखो("\n\r");

	/* Put the command line back पूर्णांकo the devtree क्रम the kernel */
	setprop_str(chosen, "bootargs", cmdline);
पूर्ण

काष्ठा platक्रमm_ops platक्रमm_ops;
काष्ठा dt_ops dt_ops;
काष्ठा console_ops console_ops;
काष्ठा loader_info loader_info;

व्योम start(व्योम)
अणु
	काष्ठा addr_range vmlinux, initrd;
	kernel_entry_t kentry;
	अचिन्हित दीर्घ ft_addr = 0;
	व्योम *chosen;

	/* Do this first, because दो_स्मृति() could clobber the loader's
	 * command line.  Only use the loader command line अगर a
	 * built-in command line wasn't set by an बाह्यal tool */
	अगर ((loader_info.cmdline_len > 0) && (cmdline[0] == '\0'))
		स_हटाओ(cmdline, loader_info.cmdline,
			min(loader_info.cmdline_len, BOOT_COMMAND_LINE_SIZE-1));

	अगर (console_ops.खोलो && (console_ops.खोलो() < 0))
		निकास();
	अगर (platक्रमm_ops.fixups)
		platक्रमm_ops.fixups();

	म_लिखो("\n\rzImage starting: loaded at 0x%p (sp: 0x%p)\n\r",
	       _start, get_sp());

	/* Ensure that the device tree has a /chosen node */
	chosen = finddevice("/chosen");
	अगर (!chosen)
		chosen = create_node(शून्य, "chosen");

	vmlinux = prep_kernel();
	initrd = prep_initrd(vmlinux, chosen,
			     loader_info.initrd_addr, loader_info.initrd_size);
	prep_esm_blob(vmlinux, chosen);
	prep_cmdline(chosen);

	म_लिखो("Finalizing device tree...");
	अगर (dt_ops.finalize)
		ft_addr = dt_ops.finalize();
	अगर (ft_addr)
		म_लिखो(" flat tree at 0x%lx\n\r", ft_addr);
	अन्यथा
		म_लिखो(" using OF tree (promptr=%p)\n\r", loader_info.promptr);

	अगर (console_ops.बंद)
		console_ops.बंद();

	kentry = (kernel_entry_t) vmlinux.addr;
	अगर (ft_addr) अणु
		अगर(platक्रमm_ops.kentry)
			platक्रमm_ops.kentry(ft_addr, vmlinux.addr);
		अन्यथा
			kentry(ft_addr, 0, शून्य);
	पूर्ण
	अन्यथा
		kentry((अचिन्हित दीर्घ)initrd.addr, initrd.size,
		       loader_info.promptr);

	/* console बंदd so म_लिखो in fatal below may not work */
	fatal("Error: Linux kernel returned to zImage boot wrapper!\n\r");
पूर्ण
