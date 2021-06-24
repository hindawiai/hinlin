<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Arm Limited
 *
 * Based on arch/arm64/kernel/machine_kexec_file.c:
 *  Copyright (C) 2018 Linaro Limited
 *
 * And arch/घातerpc/kexec/file_load.c:
 *  Copyright (C) 2016  IBM Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <linux/memblock.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/types.h>

/* relevant device tree properties */
#घोषणा FDT_PROP_KEXEC_ELFHDR	"linux,elfcorehdr"
#घोषणा FDT_PROP_MEM_RANGE	"linux,usable-memory-range"
#घोषणा FDT_PROP_INITRD_START	"linux,initrd-start"
#घोषणा FDT_PROP_INITRD_END	"linux,initrd-end"
#घोषणा FDT_PROP_BOOTARGS	"bootargs"
#घोषणा FDT_PROP_KASLR_SEED	"kaslr-seed"
#घोषणा FDT_PROP_RNG_SEED	"rng-seed"
#घोषणा RNG_SEED_SIZE		128

/*
 * Additional space needed क्रम the FDT buffer so that we can add initrd,
 * bootargs, kaslr-seed, rng-seed, useable-memory-range and elfcorehdr.
 */
#घोषणा FDT_EXTRA_SPACE 0x1000

/**
 * fdt_find_and_del_mem_rsv - delete memory reservation with given address and size
 *
 * @fdt:	Flattened device tree क्रम the current kernel.
 * @start:	Starting address of the reserved memory.
 * @size:	Size of the reserved memory.
 *
 * Return: 0 on success, or negative त्रुटि_सं on error.
 */
अटल पूर्णांक fdt_find_and_del_mem_rsv(व्योम *fdt, अचिन्हित दीर्घ start, अचिन्हित दीर्घ size)
अणु
	पूर्णांक i, ret, num_rsvs = fdt_num_mem_rsv(fdt);

	क्रम (i = 0; i < num_rsvs; i++) अणु
		u64 rsv_start, rsv_size;

		ret = fdt_get_mem_rsv(fdt, i, &rsv_start, &rsv_size);
		अगर (ret) अणु
			pr_err("Malformed device tree.\n");
			वापस -EINVAL;
		पूर्ण

		अगर (rsv_start == start && rsv_size == size) अणु
			ret = fdt_del_mem_rsv(fdt, i);
			अगर (ret) अणु
				pr_err("Error deleting device tree reservation.\n");
				वापस -EINVAL;
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

/**
 * get_addr_size_cells - Get address and size of root node
 *
 * @addr_cells: Return address of the root node
 * @size_cells: Return size of the root node
 *
 * Return: 0 on success, or negative त्रुटि_सं on error.
 */
अटल पूर्णांक get_addr_size_cells(पूर्णांक *addr_cells, पूर्णांक *size_cells)
अणु
	काष्ठा device_node *root;

	root = of_find_node_by_path("/");
	अगर (!root)
		वापस -EINVAL;

	*addr_cells = of_n_addr_cells(root);
	*size_cells = of_n_size_cells(root);

	of_node_put(root);

	वापस 0;
पूर्ण

/**
 * करो_get_kexec_buffer - Get address and size of device tree property
 *
 * @prop: Device tree property
 * @len: Size of @prop
 * @addr: Return address of the node
 * @size: Return size of the node
 *
 * Return: 0 on success, or negative त्रुटि_सं on error.
 */
अटल पूर्णांक करो_get_kexec_buffer(स्थिर व्योम *prop, पूर्णांक len, अचिन्हित दीर्घ *addr,
			       माप_प्रकार *size)
अणु
	पूर्णांक ret, addr_cells, size_cells;

	ret = get_addr_size_cells(&addr_cells, &size_cells);
	अगर (ret)
		वापस ret;

	अगर (len < 4 * (addr_cells + size_cells))
		वापस -ENOENT;

	*addr = of_पढ़ो_number(prop, addr_cells);
	*size = of_पढ़ो_number(prop + 4 * addr_cells, size_cells);

	वापस 0;
पूर्ण

/**
 * ima_get_kexec_buffer - get IMA buffer from the previous kernel
 * @addr:	On successful वापस, set to poपूर्णांक to the buffer contents.
 * @size:	On successful वापस, set to the buffer size.
 *
 * Return: 0 on success, negative त्रुटि_सं on error.
 */
पूर्णांक ima_get_kexec_buffer(व्योम **addr, माप_प्रकार *size)
अणु
	पूर्णांक ret, len;
	अचिन्हित दीर्घ पंचांगp_addr;
	माप_प्रकार पंचांगp_size;
	स्थिर व्योम *prop;

	अगर (!IS_ENABLED(CONFIG_HAVE_IMA_KEXEC))
		वापस -ENOTSUPP;

	prop = of_get_property(of_chosen, "linux,ima-kexec-buffer", &len);
	अगर (!prop)
		वापस -ENOENT;

	ret = करो_get_kexec_buffer(prop, len, &पंचांगp_addr, &पंचांगp_size);
	अगर (ret)
		वापस ret;

	*addr = __va(पंचांगp_addr);
	*size = पंचांगp_size;

	वापस 0;
पूर्ण

/**
 * ima_मुक्त_kexec_buffer - मुक्त memory used by the IMA buffer
 */
पूर्णांक ima_मुक्त_kexec_buffer(व्योम)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ addr;
	माप_प्रकार size;
	काष्ठा property *prop;

	अगर (!IS_ENABLED(CONFIG_HAVE_IMA_KEXEC))
		वापस -ENOTSUPP;

	prop = of_find_property(of_chosen, "linux,ima-kexec-buffer", शून्य);
	अगर (!prop)
		वापस -ENOENT;

	ret = करो_get_kexec_buffer(prop->value, prop->length, &addr, &size);
	अगर (ret)
		वापस ret;

	ret = of_हटाओ_property(of_chosen, prop);
	अगर (ret)
		वापस ret;

	वापस memblock_मुक्त(addr, size);

पूर्ण

/**
 * हटाओ_ima_buffer - हटाओ the IMA buffer property and reservation from @fdt
 *
 * @fdt: Flattened Device Tree to update
 * @chosen_node: Offset to the chosen node in the device tree
 *
 * The IMA measurement buffer is of no use to a subsequent kernel, so we always
 * हटाओ it from the device tree.
 */
अटल व्योम हटाओ_ima_buffer(व्योम *fdt, पूर्णांक chosen_node)
अणु
	पूर्णांक ret, len;
	अचिन्हित दीर्घ addr;
	माप_प्रकार size;
	स्थिर व्योम *prop;

	अगर (!IS_ENABLED(CONFIG_HAVE_IMA_KEXEC))
		वापस;

	prop = fdt_getprop(fdt, chosen_node, "linux,ima-kexec-buffer", &len);
	अगर (!prop)
		वापस;

	ret = करो_get_kexec_buffer(prop, len, &addr, &size);
	fdt_delprop(fdt, chosen_node, "linux,ima-kexec-buffer");
	अगर (ret)
		वापस;

	ret = fdt_find_and_del_mem_rsv(fdt, addr, size);
	अगर (!ret)
		pr_debug("Removed old IMA buffer reservation.\n");
पूर्ण

#अगर_घोषित CONFIG_IMA_KEXEC
/**
 * setup_ima_buffer - add IMA buffer inक्रमmation to the fdt
 * @image:		kexec image being loaded.
 * @fdt:		Flattened device tree क्रम the next kernel.
 * @chosen_node:	Offset to the chosen node.
 *
 * Return: 0 on success, or negative त्रुटि_सं on error.
 */
अटल पूर्णांक setup_ima_buffer(स्थिर काष्ठा kimage *image, व्योम *fdt,
			    पूर्णांक chosen_node)
अणु
	पूर्णांक ret;

	अगर (!image->ima_buffer_size)
		वापस 0;

	ret = fdt_appendprop_addrrange(fdt, 0, chosen_node,
				       "linux,ima-kexec-buffer",
				       image->ima_buffer_addr,
				       image->ima_buffer_size);
	अगर (ret < 0)
		वापस -EINVAL;

	ret = fdt_add_mem_rsv(fdt, image->ima_buffer_addr,
			      image->ima_buffer_size);
	अगर (ret)
		वापस -EINVAL;

	pr_debug("IMA buffer at 0x%llx, size = 0x%zx\n",
		 image->ima_buffer_addr, image->ima_buffer_size);

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_IMA_KEXEC */
अटल अंतरभूत पूर्णांक setup_ima_buffer(स्थिर काष्ठा kimage *image, व्योम *fdt,
				   पूर्णांक chosen_node)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_IMA_KEXEC */

/*
 * of_kexec_alloc_and_setup_fdt - Alloc and setup a new Flattened Device Tree
 *
 * @image:		kexec image being loaded.
 * @initrd_load_addr:	Address where the next initrd will be loaded.
 * @initrd_len:		Size of the next initrd, or 0 अगर there will be none.
 * @cmdline:		Command line क्रम the next kernel, or शून्य अगर there will
 *			be none.
 * @extra_fdt_size:	Additional size क्रम the new FDT buffer.
 *
 * Return: fdt on success, or शून्य त्रुटि_सं on error.
 */
व्योम *of_kexec_alloc_and_setup_fdt(स्थिर काष्ठा kimage *image,
				   अचिन्हित दीर्घ initrd_load_addr,
				   अचिन्हित दीर्घ initrd_len,
				   स्थिर अक्षर *cmdline, माप_प्रकार extra_fdt_size)
अणु
	व्योम *fdt;
	पूर्णांक ret, chosen_node;
	स्थिर व्योम *prop;
	माप_प्रकार fdt_size;

	fdt_size = fdt_totalsize(initial_boot_params) +
		   (cmdline ? म_माप(cmdline) : 0) +
		   FDT_EXTRA_SPACE +
		   extra_fdt_size;
	fdt = kvदो_स्मृति(fdt_size, GFP_KERNEL);
	अगर (!fdt)
		वापस शून्य;

	ret = fdt_खोलो_पूर्णांकo(initial_boot_params, fdt, fdt_size);
	अगर (ret < 0) अणु
		pr_err("Error %d setting up the new device tree.\n", ret);
		जाओ out;
	पूर्ण

	/* Remove memory reservation क्रम the current device tree. */
	ret = fdt_find_and_del_mem_rsv(fdt, __pa(initial_boot_params),
				       fdt_totalsize(initial_boot_params));
	अगर (ret == -EINVAL) अणु
		pr_err("Error removing memory reservation.\n");
		जाओ out;
	पूर्ण

	chosen_node = fdt_path_offset(fdt, "/chosen");
	अगर (chosen_node == -FDT_ERR_NOTFOUND)
		chosen_node = fdt_add_subnode(fdt, fdt_path_offset(fdt, "/"),
					      "chosen");
	अगर (chosen_node < 0) अणु
		ret = chosen_node;
		जाओ out;
	पूर्ण

	ret = fdt_delprop(fdt, chosen_node, FDT_PROP_KEXEC_ELFHDR);
	अगर (ret && ret != -FDT_ERR_NOTFOUND)
		जाओ out;
	ret = fdt_delprop(fdt, chosen_node, FDT_PROP_MEM_RANGE);
	अगर (ret && ret != -FDT_ERR_NOTFOUND)
		जाओ out;

	/* Did we boot using an initrd? */
	prop = fdt_getprop(fdt, chosen_node, "linux,initrd-start", शून्य);
	अगर (prop) अणु
		u64 पंचांगp_start, पंचांगp_end, पंचांगp_size;

		पंचांगp_start = fdt64_to_cpu(*((स्थिर fdt64_t *) prop));

		prop = fdt_getprop(fdt, chosen_node, "linux,initrd-end", शून्य);
		अगर (!prop) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		पंचांगp_end = fdt64_to_cpu(*((स्थिर fdt64_t *) prop));

		/*
		 * kexec reserves exact initrd size, जबतक firmware may
		 * reserve a multiple of PAGE_SIZE, so check क्रम both.
		 */
		पंचांगp_size = पंचांगp_end - पंचांगp_start;
		ret = fdt_find_and_del_mem_rsv(fdt, पंचांगp_start, पंचांगp_size);
		अगर (ret == -ENOENT)
			ret = fdt_find_and_del_mem_rsv(fdt, पंचांगp_start,
						       round_up(पंचांगp_size, PAGE_SIZE));
		अगर (ret == -EINVAL)
			जाओ out;
	पूर्ण

	/* add initrd-* */
	अगर (initrd_load_addr) अणु
		ret = fdt_setprop_u64(fdt, chosen_node, FDT_PROP_INITRD_START,
				      initrd_load_addr);
		अगर (ret)
			जाओ out;

		ret = fdt_setprop_u64(fdt, chosen_node, FDT_PROP_INITRD_END,
				      initrd_load_addr + initrd_len);
		अगर (ret)
			जाओ out;

		ret = fdt_add_mem_rsv(fdt, initrd_load_addr, initrd_len);
		अगर (ret)
			जाओ out;

	पूर्ण अन्यथा अणु
		ret = fdt_delprop(fdt, chosen_node, FDT_PROP_INITRD_START);
		अगर (ret && (ret != -FDT_ERR_NOTFOUND))
			जाओ out;

		ret = fdt_delprop(fdt, chosen_node, FDT_PROP_INITRD_END);
		अगर (ret && (ret != -FDT_ERR_NOTFOUND))
			जाओ out;
	पूर्ण

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		/* add linux,elfcorehdr */
		ret = fdt_appendprop_addrrange(fdt, 0, chosen_node,
				FDT_PROP_KEXEC_ELFHDR,
				image->elf_load_addr,
				image->elf_headers_sz);
		अगर (ret)
			जाओ out;

		/*
		 * Aव्योम elfcorehdr from being stomped on in kdump kernel by
		 * setting up memory reserve map.
		 */
		ret = fdt_add_mem_rsv(fdt, image->elf_load_addr,
				      image->elf_headers_sz);
		अगर (ret)
			जाओ out;

		/* add linux,usable-memory-range */
		ret = fdt_appendprop_addrrange(fdt, 0, chosen_node,
				FDT_PROP_MEM_RANGE,
				crashk_res.start,
				crashk_res.end - crashk_res.start + 1);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* add bootargs */
	अगर (cmdline) अणु
		ret = fdt_setprop_string(fdt, chosen_node, FDT_PROP_BOOTARGS, cmdline);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = fdt_delprop(fdt, chosen_node, FDT_PROP_BOOTARGS);
		अगर (ret && (ret != -FDT_ERR_NOTFOUND))
			जाओ out;
	पूर्ण

	/* add kaslr-seed */
	ret = fdt_delprop(fdt, chosen_node, FDT_PROP_KASLR_SEED);
	अगर (ret == -FDT_ERR_NOTFOUND)
		ret = 0;
	अन्यथा अगर (ret)
		जाओ out;

	अगर (rng_is_initialized()) अणु
		u64 seed = get_अक्रमom_u64();

		ret = fdt_setprop_u64(fdt, chosen_node, FDT_PROP_KASLR_SEED, seed);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		pr_notice("RNG is not initialised: omitting \"%s\" property\n",
				FDT_PROP_KASLR_SEED);
	पूर्ण

	/* add rng-seed */
	अगर (rng_is_initialized()) अणु
		व्योम *rng_seed;

		ret = fdt_setprop_placeholder(fdt, chosen_node, FDT_PROP_RNG_SEED,
				RNG_SEED_SIZE, &rng_seed);
		अगर (ret)
			जाओ out;
		get_अक्रमom_bytes(rng_seed, RNG_SEED_SIZE);
	पूर्ण अन्यथा अणु
		pr_notice("RNG is not initialised: omitting \"%s\" property\n",
				FDT_PROP_RNG_SEED);
	पूर्ण

	ret = fdt_setprop(fdt, chosen_node, "linux,booted-from-kexec", शून्य, 0);
	अगर (ret)
		जाओ out;

	हटाओ_ima_buffer(fdt, chosen_node);
	ret = setup_ima_buffer(image, fdt, fdt_path_offset(fdt, "/chosen"));

out:
	अगर (ret) अणु
		kvमुक्त(fdt);
		fdt = शून्य;
	पूर्ण

	वापस fdt;
पूर्ण
