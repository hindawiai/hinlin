<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause) */
#अगर_अघोषित LIBFDT_H
#घोषणा LIBFDT_H
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 */

#समावेश "libfdt_env.h"
#समावेश "fdt.h"

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा FDT_FIRST_SUPPORTED_VERSION	0x02
#घोषणा FDT_LAST_COMPATIBLE_VERSION 0x10
#घोषणा FDT_LAST_SUPPORTED_VERSION	0x11

/* Error codes: inक्रमmative error codes */
#घोषणा FDT_ERR_NOTFOUND	1
	/* FDT_ERR_NOTFOUND: The requested node or property करोes not exist */
#घोषणा FDT_ERR_EXISTS		2
	/* FDT_ERR_EXISTS: Attempted to create a node or property which
	 * alपढ़ोy exists */
#घोषणा FDT_ERR_NOSPACE		3
	/* FDT_ERR_NOSPACE: Operation needed to expand the device
	 * tree, but its buffer did not have sufficient space to
	 * contain the expanded tree. Use fdt_खोलो_पूर्णांकo() to move the
	 * device tree to a buffer with more space. */

/* Error codes: codes क्रम bad parameters */
#घोषणा FDT_ERR_BADOFFSET	4
	/* FDT_ERR_BADOFFSET: Function was passed a काष्ठाure block
	 * offset which is out-of-bounds, or which poपूर्णांकs to an
	 * unsuitable part of the काष्ठाure क्रम the operation. */
#घोषणा FDT_ERR_BADPATH		5
	/* FDT_ERR_BADPATH: Function was passed a badly क्रमmatted path
	 * (e.g. missing a leading / क्रम a function which requires an
	 * असलolute path) */
#घोषणा FDT_ERR_BADPHANDLE	6
	/* FDT_ERR_BADPHANDLE: Function was passed an invalid phandle.
	 * This can be caused either by an invalid phandle property
	 * length, or the phandle value was either 0 or -1, which are
	 * not permitted. */
#घोषणा FDT_ERR_BADSTATE	7
	/* FDT_ERR_BADSTATE: Function was passed an incomplete device
	 * tree created by the sequential-ग_लिखो functions, which is
	 * not sufficiently complete क्रम the requested operation. */

/* Error codes: codes क्रम bad device tree blobs */
#घोषणा FDT_ERR_TRUNCATED	8
	/* FDT_ERR_TRUNCATED: FDT or a sub-block is improperly
	 * terminated (overflows, goes outside allowed bounds, or
	 * isn't properly terminated).  */
#घोषणा FDT_ERR_BADMAGIC	9
	/* FDT_ERR_BADMAGIC: Given "device tree" appears not to be a
	 * device tree at all - it is missing the flattened device
	 * tree magic number. */
#घोषणा FDT_ERR_BADVERSION	10
	/* FDT_ERR_BADVERSION: Given device tree has a version which
	 * can't be handled by the requested operation.  For
	 * पढ़ो-ग_लिखो functions, this may mean that fdt_खोलो_पूर्णांकo() is
	 * required to convert the tree to the expected version. */
#घोषणा FDT_ERR_BADSTRUCTURE	11
	/* FDT_ERR_BADSTRUCTURE: Given device tree has a corrupt
	 * काष्ठाure block or other serious error (e.g. misnested
	 * nodes, or subnodes preceding properties). */
#घोषणा FDT_ERR_BADLAYOUT	12
	/* FDT_ERR_BADLAYOUT: For पढ़ो-ग_लिखो functions, the given
	 * device tree has it's sub-blocks in an order that the
	 * function can't handle (memory reserve map, then काष्ठाure,
	 * then strings).  Use fdt_खोलो_पूर्णांकo() to reorganize the tree
	 * पूर्णांकo a क्रमm suitable क्रम the पढ़ो-ग_लिखो operations. */

/* "Can't happen" error indicating a bug in libfdt */
#घोषणा FDT_ERR_INTERNAL	13
	/* FDT_ERR_INTERNAL: libfdt has failed an पूर्णांकernal निश्चितion.
	 * Should never be वापसed, अगर it is, it indicates a bug in
	 * libfdt itself. */

/* Errors in device tree content */
#घोषणा FDT_ERR_BADNCELLS	14
	/* FDT_ERR_BADNCELLS: Device tree has a #address-cells, #size-cells
	 * or similar property with a bad क्रमmat or value */

#घोषणा FDT_ERR_BADVALUE	15
	/* FDT_ERR_BADVALUE: Device tree has a property with an unexpected
	 * value. For example: a property expected to contain a string list
	 * is not NUL-terminated within the length of its value. */

#घोषणा FDT_ERR_BADOVERLAY	16
	/* FDT_ERR_BADOVERLAY: The device tree overlay, जबतक
	 * correctly काष्ठाured, cannot be applied due to some
	 * unexpected or missing value, property or node. */

#घोषणा FDT_ERR_NOPHANDLES	17
	/* FDT_ERR_NOPHANDLES: The device tree करोesn't have any
	 * phandle available anymore without causing an overflow */

#घोषणा FDT_ERR_BADFLAGS	18
	/* FDT_ERR_BADFLAGS: The function was passed a flags field that
	 * contains invalid flags or an invalid combination of flags. */

#घोषणा FDT_ERR_ALIGNMENT	19
	/* FDT_ERR_ALIGNMENT: The device tree base address is not 8-byte
	 * aligned. */

#घोषणा FDT_ERR_MAX		19

/* स्थिरants */
#घोषणा FDT_MAX_PHANDLE 0xfffffffe
	/* Valid values क्रम phandles range from 1 to 2^32-2. */

/**********************************************************************/
/* Low-level functions (you probably करोn't need these)                */
/**********************************************************************/

#अगर_अघोषित SWIG /* This function is not useful in Python */
स्थिर व्योम *fdt_offset_ptr(स्थिर व्योम *fdt, पूर्णांक offset, अचिन्हित पूर्णांक checklen);
#पूर्ण_अगर
अटल अंतरभूत व्योम *fdt_offset_ptr_w(व्योम *fdt, पूर्णांक offset, पूर्णांक checklen)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)fdt_offset_ptr(fdt, offset, checklen);
पूर्ण

uपूर्णांक32_t fdt_next_tag(स्थिर व्योम *fdt, पूर्णांक offset, पूर्णांक *nextoffset);

/*
 * External helpers to access words from a device tree blob. They're built
 * to work even with unaligned poपूर्णांकers on platक्रमms (such as ARMv5) that करोn't
 * like unaligned loads and stores.
 */
अटल अंतरभूत uपूर्णांक32_t fdt32_ld(स्थिर fdt32_t *p)
अणु
	स्थिर uपूर्णांक8_t *bp = (स्थिर uपूर्णांक8_t *)p;

	वापस ((uपूर्णांक32_t)bp[0] << 24)
		| ((uपूर्णांक32_t)bp[1] << 16)
		| ((uपूर्णांक32_t)bp[2] << 8)
		| bp[3];
पूर्ण

अटल अंतरभूत व्योम fdt32_st(व्योम *property, uपूर्णांक32_t value)
अणु
	uपूर्णांक8_t *bp = (uपूर्णांक8_t *)property;

	bp[0] = value >> 24;
	bp[1] = (value >> 16) & 0xff;
	bp[2] = (value >> 8) & 0xff;
	bp[3] = value & 0xff;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t fdt64_ld(स्थिर fdt64_t *p)
अणु
	स्थिर uपूर्णांक8_t *bp = (स्थिर uपूर्णांक8_t *)p;

	वापस ((uपूर्णांक64_t)bp[0] << 56)
		| ((uपूर्णांक64_t)bp[1] << 48)
		| ((uपूर्णांक64_t)bp[2] << 40)
		| ((uपूर्णांक64_t)bp[3] << 32)
		| ((uपूर्णांक64_t)bp[4] << 24)
		| ((uपूर्णांक64_t)bp[5] << 16)
		| ((uपूर्णांक64_t)bp[6] << 8)
		| bp[7];
पूर्ण

अटल अंतरभूत व्योम fdt64_st(व्योम *property, uपूर्णांक64_t value)
अणु
	uपूर्णांक8_t *bp = (uपूर्णांक8_t *)property;

	bp[0] = value >> 56;
	bp[1] = (value >> 48) & 0xff;
	bp[2] = (value >> 40) & 0xff;
	bp[3] = (value >> 32) & 0xff;
	bp[4] = (value >> 24) & 0xff;
	bp[5] = (value >> 16) & 0xff;
	bp[6] = (value >> 8) & 0xff;
	bp[7] = value & 0xff;
पूर्ण

/**********************************************************************/
/* Traversal functions                                                */
/**********************************************************************/

पूर्णांक fdt_next_node(स्थिर व्योम *fdt, पूर्णांक offset, पूर्णांक *depth);

/**
 * fdt_first_subnode() - get offset of first direct subnode
 * @fdt:	FDT blob
 * @offset:	Offset of node to check
 *
 * Return: offset of first subnode, or -FDT_ERR_NOTFOUND अगर there is none
 */
पूर्णांक fdt_first_subnode(स्थिर व्योम *fdt, पूर्णांक offset);

/**
 * fdt_next_subnode() - get offset of next direct subnode
 * @fdt:	FDT blob
 * @offset:	Offset of previous subnode
 *
 * After first calling fdt_first_subnode(), call this function repeatedly to
 * get direct subnodes of a parent node.
 *
 * Return: offset of next subnode, or -FDT_ERR_NOTFOUND अगर there are no more
 *         subnodes
 */
पूर्णांक fdt_next_subnode(स्थिर व्योम *fdt, पूर्णांक offset);

/**
 * fdt_क्रम_each_subnode - iterate over all subnodes of a parent
 *
 * @node:	child node (पूर्णांक, lvalue)
 * @fdt:	FDT blob (स्थिर व्योम *)
 * @parent:	parent node (पूर्णांक)
 *
 * This is actually a wrapper around a क्रम loop and would be used like so:
 *
 *	fdt_क्रम_each_subnode(node, fdt, parent) अणु
 *		Use node
 *		...
 *	पूर्ण
 *
 *	अगर ((node < 0) && (node != -FDT_ERR_NOTFOUND)) अणु
 *		Error handling
 *	पूर्ण
 *
 * Note that this is implemented as a macro and @node is used as
 * iterator in the loop. The parent variable be स्थिरant or even a
 * literal.
 */
#घोषणा fdt_क्रम_each_subnode(node, fdt, parent)		\
	क्रम (node = fdt_first_subnode(fdt, parent);	\
	     node >= 0;					\
	     node = fdt_next_subnode(fdt, node))

/**********************************************************************/
/* General functions                                                  */
/**********************************************************************/
#घोषणा fdt_get_header(fdt, field) \
	(fdt32_ld(&((स्थिर काष्ठा fdt_header *)(fdt))->field))
#घोषणा fdt_magic(fdt)			(fdt_get_header(fdt, magic))
#घोषणा fdt_totalsize(fdt)		(fdt_get_header(fdt, totalsize))
#घोषणा fdt_off_dt_काष्ठा(fdt)		(fdt_get_header(fdt, off_dt_काष्ठा))
#घोषणा fdt_off_dt_strings(fdt)		(fdt_get_header(fdt, off_dt_strings))
#घोषणा fdt_off_mem_rsvmap(fdt)		(fdt_get_header(fdt, off_mem_rsvmap))
#घोषणा fdt_version(fdt)		(fdt_get_header(fdt, version))
#घोषणा fdt_last_comp_version(fdt)	(fdt_get_header(fdt, last_comp_version))
#घोषणा fdt_boot_cpuid_phys(fdt)	(fdt_get_header(fdt, boot_cpuid_phys))
#घोषणा fdt_size_dt_strings(fdt)	(fdt_get_header(fdt, size_dt_strings))
#घोषणा fdt_size_dt_काष्ठा(fdt)		(fdt_get_header(fdt, size_dt_काष्ठा))

#घोषणा fdt_set_hdr_(name) \
	अटल अंतरभूत व्योम fdt_set_##name(व्योम *fdt, uपूर्णांक32_t val) \
	अणु \
		काष्ठा fdt_header *fdth = (काष्ठा fdt_header *)fdt; \
		fdth->name = cpu_to_fdt32(val); \
	पूर्ण
fdt_set_hdr_(magic);
fdt_set_hdr_(totalsize);
fdt_set_hdr_(off_dt_काष्ठा);
fdt_set_hdr_(off_dt_strings);
fdt_set_hdr_(off_mem_rsvmap);
fdt_set_hdr_(version);
fdt_set_hdr_(last_comp_version);
fdt_set_hdr_(boot_cpuid_phys);
fdt_set_hdr_(size_dt_strings);
fdt_set_hdr_(size_dt_काष्ठा);
#अघोषित fdt_set_hdr_

/**
 * fdt_header_size - वापस the size of the tree's header
 * @fdt: poपूर्णांकer to a flattened device tree
 *
 * Return: size of DTB header in bytes
 */
माप_प्रकार fdt_header_size(स्थिर व्योम *fdt);

/**
 * fdt_header_size_ - पूर्णांकernal function to get header size from a version number
 * @version: devicetree version number
 *
 * Return: size of DTB header in bytes
 */
माप_प्रकार fdt_header_size_(uपूर्णांक32_t version);

/**
 * fdt_check_header - sanity check a device tree header
 * @fdt: poपूर्णांकer to data which might be a flattened device tree
 *
 * fdt_check_header() checks that the given buffer contains what
 * appears to be a flattened device tree, and that the header contains
 * valid inक्रमmation (to the extent that can be determined from the
 * header alone).
 *
 * वापसs:
 *     0, अगर the buffer appears to contain a valid device tree
 *     -FDT_ERR_BADMAGIC,
 *     -FDT_ERR_BADVERSION,
 *     -FDT_ERR_BADSTATE,
 *     -FDT_ERR_TRUNCATED, standard meanings, as above
 */
पूर्णांक fdt_check_header(स्थिर व्योम *fdt);

/**
 * fdt_move - move a device tree around in memory
 * @fdt: poपूर्णांकer to the device tree to move
 * @buf: poपूर्णांकer to memory where the device is to be moved
 * @bufsize: size of the memory space at buf
 *
 * fdt_move() relocates, अगर possible, the device tree blob located at
 * fdt to the buffer at buf of size bufsize.  The buffer may overlap
 * with the existing device tree blob at fdt.  Thereक्रमe,
 *     fdt_move(fdt, fdt, fdt_totalsize(fdt))
 * should always succeed.
 *
 * वापसs:
 *     0, on success
 *     -FDT_ERR_NOSPACE, bufsize is insufficient to contain the device tree
 *     -FDT_ERR_BADMAGIC,
 *     -FDT_ERR_BADVERSION,
 *     -FDT_ERR_BADSTATE, standard meanings
 */
पूर्णांक fdt_move(स्थिर व्योम *fdt, व्योम *buf, पूर्णांक bufsize);

/**********************************************************************/
/* Read-only functions                                                */
/**********************************************************************/

पूर्णांक fdt_check_full(स्थिर व्योम *fdt, माप_प्रकार bufsize);

/**
 * fdt_get_string - retrieve a string from the strings block of a device tree
 * @fdt: poपूर्णांकer to the device tree blob
 * @stroffset: offset of the string within the strings block (native endian)
 * @lenp: optional poपूर्णांकer to वापस the string's length
 *
 * fdt_get_string() retrieves a poपूर्णांकer to a single string from the
 * strings block of the device tree blob at fdt, and optionally also
 * वापसs the string's length in *lenp.
 *
 * वापसs:
 *     a poपूर्णांकer to the string, on success
 *     शून्य, अगर stroffset is out of bounds, or करोesn't poपूर्णांक to a valid string
 */
स्थिर अक्षर *fdt_get_string(स्थिर व्योम *fdt, पूर्णांक stroffset, पूर्णांक *lenp);

/**
 * fdt_string - retrieve a string from the strings block of a device tree
 * @fdt: poपूर्णांकer to the device tree blob
 * @stroffset: offset of the string within the strings block (native endian)
 *
 * fdt_string() retrieves a poपूर्णांकer to a single string from the
 * strings block of the device tree blob at fdt.
 *
 * वापसs:
 *     a poपूर्णांकer to the string, on success
 *     शून्य, अगर stroffset is out of bounds, or करोesn't poपूर्णांक to a valid string
 */
स्थिर अक्षर *fdt_string(स्थिर व्योम *fdt, पूर्णांक stroffset);

/**
 * fdt_find_max_phandle - find and वापस the highest phandle in a tree
 * @fdt: poपूर्णांकer to the device tree blob
 * @phandle: वापस location क्रम the highest phandle value found in the tree
 *
 * fdt_find_max_phandle() finds the highest phandle value in the given device
 * tree. The value वापसed in @phandle is only valid अगर the function वापसs
 * success.
 *
 * वापसs:
 *     0 on success or a negative error code on failure
 */
पूर्णांक fdt_find_max_phandle(स्थिर व्योम *fdt, uपूर्णांक32_t *phandle);

/**
 * fdt_get_max_phandle - retrieves the highest phandle in a tree
 * @fdt: poपूर्णांकer to the device tree blob
 *
 * fdt_get_max_phandle retrieves the highest phandle in the given
 * device tree. This will ignore badly क्रमmatted phandles, or phandles
 * with a value of 0 or -1.
 *
 * This function is deprecated in favour of fdt_find_max_phandle().
 *
 * वापसs:
 *      the highest phandle on success
 *      0, अगर no phandle was found in the device tree
 *      -1, अगर an error occurred
 */
अटल अंतरभूत uपूर्णांक32_t fdt_get_max_phandle(स्थिर व्योम *fdt)
अणु
	uपूर्णांक32_t phandle;
	पूर्णांक err;

	err = fdt_find_max_phandle(fdt, &phandle);
	अगर (err < 0)
		वापस (uपूर्णांक32_t)-1;

	वापस phandle;
पूर्ण

/**
 * fdt_generate_phandle - वापस a new, unused phandle क्रम a device tree blob
 * @fdt: poपूर्णांकer to the device tree blob
 * @phandle: वापस location क्रम the new phandle
 *
 * Walks the device tree blob and looks क्रम the highest phandle value. On
 * success, the new, unused phandle value (one higher than the previously
 * highest phandle value in the device tree blob) will be वापसed in the
 * @phandle parameter.
 *
 * Return: 0 on success or a negative error-code on failure
 */
पूर्णांक fdt_generate_phandle(स्थिर व्योम *fdt, uपूर्णांक32_t *phandle);

/**
 * fdt_num_mem_rsv - retrieve the number of memory reserve map entries
 * @fdt: poपूर्णांकer to the device tree blob
 *
 * Returns the number of entries in the device tree blob's memory
 * reservation map.  This करोes not include the terminating 0,0 entry
 * or any other (0,0) entries reserved क्रम expansion.
 *
 * वापसs:
 *     the number of entries
 */
पूर्णांक fdt_num_mem_rsv(स्थिर व्योम *fdt);

/**
 * fdt_get_mem_rsv - retrieve one memory reserve map entry
 * @fdt: poपूर्णांकer to the device tree blob
 * @n: index of reserve map entry
 * @address: poपूर्णांकer to 64-bit variable to hold the start address
 * @size: poपूर्णांकer to 64-bit variable to hold the size of the entry
 *
 * On success, @address and @size will contain the address and size of
 * the n-th reserve map entry from the device tree blob, in
 * native-endian क्रमmat.
 *
 * वापसs:
 *     0, on success
 *     -FDT_ERR_BADMAGIC,
 *     -FDT_ERR_BADVERSION,
 *     -FDT_ERR_BADSTATE, standard meanings
 */
पूर्णांक fdt_get_mem_rsv(स्थिर व्योम *fdt, पूर्णांक n, uपूर्णांक64_t *address, uपूर्णांक64_t *size);

/**
 * fdt_subnode_offset_namelen - find a subnode based on substring
 * @fdt: poपूर्णांकer to the device tree blob
 * @parentoffset: काष्ठाure block offset of a node
 * @name: name of the subnode to locate
 * @namelen: number of अक्षरacters of name to consider
 *
 * Identical to fdt_subnode_offset(), but only examine the first
 * namelen अक्षरacters of name क्रम matching the subnode name.  This is
 * useful क्रम finding subnodes based on a portion of a larger string,
 * such as a full path.
 *
 * Return: offset of the subnode or -FDT_ERR_NOTFOUND अगर name not found.
 */
#अगर_अघोषित SWIG /* Not available in Python */
पूर्णांक fdt_subnode_offset_namelen(स्थिर व्योम *fdt, पूर्णांक parentoffset,
			       स्थिर अक्षर *name, पूर्णांक namelen);
#पूर्ण_अगर
/**
 * fdt_subnode_offset - find a subnode of a given node
 * @fdt: poपूर्णांकer to the device tree blob
 * @parentoffset: काष्ठाure block offset of a node
 * @name: name of the subnode to locate
 *
 * fdt_subnode_offset() finds a subnode of the node at काष्ठाure block
 * offset parentoffset with the given name.  name may include a unit
 * address, in which हाल fdt_subnode_offset() will find the subnode
 * with that unit address, or the unit address may be omitted, in
 * which हाल fdt_subnode_offset() will find an arbitrary subnode
 * whose name excluding unit address matches the given name.
 *
 * वापसs:
 *	काष्ठाure block offset of the requested subnode (>=0), on success
 *	-FDT_ERR_NOTFOUND, अगर the requested subnode करोes not exist
 *	-FDT_ERR_BADOFFSET, अगर parentoffset did not poपूर्णांक to an FDT_BEGIN_NODE
 *		tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings.
 */
पूर्णांक fdt_subnode_offset(स्थिर व्योम *fdt, पूर्णांक parentoffset, स्थिर अक्षर *name);

/**
 * fdt_path_offset_namelen - find a tree node by its full path
 * @fdt: poपूर्णांकer to the device tree blob
 * @path: full path of the node to locate
 * @namelen: number of अक्षरacters of path to consider
 *
 * Identical to fdt_path_offset(), but only consider the first namelen
 * अक्षरacters of path as the path name.
 *
 * Return: offset of the node or negative libfdt error value otherwise
 */
#अगर_अघोषित SWIG /* Not available in Python */
पूर्णांक fdt_path_offset_namelen(स्थिर व्योम *fdt, स्थिर अक्षर *path, पूर्णांक namelen);
#पूर्ण_अगर

/**
 * fdt_path_offset - find a tree node by its full path
 * @fdt: poपूर्णांकer to the device tree blob
 * @path: full path of the node to locate
 *
 * fdt_path_offset() finds a node of a given path in the device tree.
 * Each path component may omit the unit address portion, but the
 * results of this are undefined अगर any such path component is
 * ambiguous (that is अगर there are multiple nodes at the relevant
 * level matching the given component, dअगरferentiated only by unit
 * address).
 *
 * वापसs:
 *	काष्ठाure block offset of the node with the requested path (>=0), on
 *		success
 *	-FDT_ERR_BADPATH, given path करोes not begin with '/' or is invalid
 *	-FDT_ERR_NOTFOUND, अगर the requested node करोes not exist
 *      -FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings.
 */
पूर्णांक fdt_path_offset(स्थिर व्योम *fdt, स्थिर अक्षर *path);

/**
 * fdt_get_name - retrieve the name of a given node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: काष्ठाure block offset of the starting node
 * @lenp: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * fdt_get_name() retrieves the name (including unit address) of the
 * device tree node at काष्ठाure block offset nodeoffset.  If lenp is
 * non-शून्य, the length of this name is also वापसed, in the पूर्णांकeger
 * poपूर्णांकed to by lenp.
 *
 * वापसs:
 *	poपूर्णांकer to the node's name, on success
 *		If lenp is non-शून्य, *lenp contains the length of that name
 *			(>=0)
 *	शून्य, on error
 *		अगर lenp is non-शून्य *lenp contains an error code (<0):
 *		-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE
 *			tag
 *		-FDT_ERR_BADMAGIC,
 *		-FDT_ERR_BADVERSION,
 *		-FDT_ERR_BADSTATE, standard meanings
 */
स्थिर अक्षर *fdt_get_name(स्थिर व्योम *fdt, पूर्णांक nodeoffset, पूर्णांक *lenp);

/**
 * fdt_first_property_offset - find the offset of a node's first property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: काष्ठाure block offset of a node
 *
 * fdt_first_property_offset() finds the first property of the node at
 * the given काष्ठाure block offset.
 *
 * वापसs:
 *	काष्ठाure block offset of the property (>=0), on success
 *	-FDT_ERR_NOTFOUND, अगर the requested node has no properties
 *	-FDT_ERR_BADOFFSET, अगर nodeoffset did not poपूर्णांक to an FDT_BEGIN_NODE tag
 *      -FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings.
 */
पूर्णांक fdt_first_property_offset(स्थिर व्योम *fdt, पूर्णांक nodeoffset);

/**
 * fdt_next_property_offset - step through a node's properties
 * @fdt: poपूर्णांकer to the device tree blob
 * @offset: काष्ठाure block offset of a property
 *
 * fdt_next_property_offset() finds the property immediately after the
 * one at the given काष्ठाure block offset.  This will be a property
 * of the same node as the given property.
 *
 * वापसs:
 *	काष्ठाure block offset of the next property (>=0), on success
 *	-FDT_ERR_NOTFOUND, अगर the given property is the last in its node
 *	-FDT_ERR_BADOFFSET, अगर nodeoffset did not poपूर्णांक to an FDT_PROP tag
 *      -FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings.
 */
पूर्णांक fdt_next_property_offset(स्थिर व्योम *fdt, पूर्णांक offset);

/**
 * fdt_क्रम_each_property_offset - iterate over all properties of a node
 *
 * @property:	property offset (पूर्णांक, lvalue)
 * @fdt:	FDT blob (स्थिर व्योम *)
 * @node:	node offset (पूर्णांक)
 *
 * This is actually a wrapper around a क्रम loop and would be used like so:
 *
 *	fdt_क्रम_each_property_offset(property, fdt, node) अणु
 *		Use property
 *		...
 *	पूर्ण
 *
 *	अगर ((property < 0) && (property != -FDT_ERR_NOTFOUND)) अणु
 *		Error handling
 *	पूर्ण
 *
 * Note that this is implemented as a macro and property is used as
 * iterator in the loop. The node variable can be स्थिरant or even a
 * literal.
 */
#घोषणा fdt_क्रम_each_property_offset(property, fdt, node)	\
	क्रम (property = fdt_first_property_offset(fdt, node);	\
	     property >= 0;					\
	     property = fdt_next_property_offset(fdt, property))

/**
 * fdt_get_property_by_offset - retrieve the property at a given offset
 * @fdt: poपूर्णांकer to the device tree blob
 * @offset: offset of the property to retrieve
 * @lenp: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * fdt_get_property_by_offset() retrieves a poपूर्णांकer to the
 * fdt_property काष्ठाure within the device tree blob at the given
 * offset.  If lenp is non-शून्य, the length of the property value is
 * also वापसed, in the पूर्णांकeger poपूर्णांकed to by lenp.
 *
 * Note that this code only works on device tree versions >= 16. fdt_getprop()
 * works on all versions.
 *
 * वापसs:
 *	poपूर्णांकer to the काष्ठाure representing the property
 *		अगर lenp is non-शून्य, *lenp contains the length of the property
 *		value (>=0)
 *	शून्य, on error
 *		अगर lenp is non-शून्य, *lenp contains an error code (<0):
 *		-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_PROP tag
 *		-FDT_ERR_BADMAGIC,
 *		-FDT_ERR_BADVERSION,
 *		-FDT_ERR_BADSTATE,
 *		-FDT_ERR_BADSTRUCTURE,
 *		-FDT_ERR_TRUNCATED, standard meanings
 */
स्थिर काष्ठा fdt_property *fdt_get_property_by_offset(स्थिर व्योम *fdt,
						      पूर्णांक offset,
						      पूर्णांक *lenp);

/**
 * fdt_get_property_namelen - find a property based on substring
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to find
 * @name: name of the property to find
 * @namelen: number of अक्षरacters of name to consider
 * @lenp: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * Identical to fdt_get_property(), but only examine the first namelen
 * अक्षरacters of name क्रम matching the property name.
 *
 * Return: poपूर्णांकer to the काष्ठाure representing the property, or शून्य
 *         अगर not found
 */
#अगर_अघोषित SWIG /* Not available in Python */
स्थिर काष्ठा fdt_property *fdt_get_property_namelen(स्थिर व्योम *fdt,
						    पूर्णांक nodeoffset,
						    स्थिर अक्षर *name,
						    पूर्णांक namelen, पूर्णांक *lenp);
#पूर्ण_अगर

/**
 * fdt_get_property - find a given property in a given node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to find
 * @name: name of the property to find
 * @lenp: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * fdt_get_property() retrieves a poपूर्णांकer to the fdt_property
 * काष्ठाure within the device tree blob corresponding to the property
 * named 'name' of the node at offset nodeoffset.  If lenp is
 * non-शून्य, the length of the property value is also वापसed, in the
 * पूर्णांकeger poपूर्णांकed to by lenp.
 *
 * वापसs:
 *	poपूर्णांकer to the काष्ठाure representing the property
 *		अगर lenp is non-शून्य, *lenp contains the length of the property
 *		value (>=0)
 *	शून्य, on error
 *		अगर lenp is non-शून्य, *lenp contains an error code (<0):
 *		-FDT_ERR_NOTFOUND, node करोes not have named property
 *		-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE
 *			tag
 *		-FDT_ERR_BADMAGIC,
 *		-FDT_ERR_BADVERSION,
 *		-FDT_ERR_BADSTATE,
 *		-FDT_ERR_BADSTRUCTURE,
 *		-FDT_ERR_TRUNCATED, standard meanings
 */
स्थिर काष्ठा fdt_property *fdt_get_property(स्थिर व्योम *fdt, पूर्णांक nodeoffset,
					    स्थिर अक्षर *name, पूर्णांक *lenp);
अटल अंतरभूत काष्ठा fdt_property *fdt_get_property_w(व्योम *fdt, पूर्णांक nodeoffset,
						      स्थिर अक्षर *name,
						      पूर्णांक *lenp)
अणु
	वापस (काष्ठा fdt_property *)(uपूर्णांकptr_t)
		fdt_get_property(fdt, nodeoffset, name, lenp);
पूर्ण

/**
 * fdt_getprop_by_offset - retrieve the value of a property at a given offset
 * @fdt: poपूर्णांकer to the device tree blob
 * @offset: offset of the property to पढ़ो
 * @namep: poपूर्णांकer to a string variable (will be overwritten) or शून्य
 * @lenp: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * fdt_getprop_by_offset() retrieves a poपूर्णांकer to the value of the
 * property at काष्ठाure block offset 'offset' (this will be a poपूर्णांकer
 * to within the device blob itself, not a copy of the value).  If
 * lenp is non-शून्य, the length of the property value is also
 * वापसed, in the पूर्णांकeger poपूर्णांकed to by lenp.  If namep is non-शून्य,
 * the property's namne will also be वापसed in the अक्षर * poपूर्णांकed to
 * by namep (this will be a poपूर्णांकer to within the device tree's string
 * block, not a new copy of the name).
 *
 * वापसs:
 *	poपूर्णांकer to the property's value
 *		अगर lenp is non-शून्य, *lenp contains the length of the property
 *		value (>=0)
 *		अगर namep is non-शून्य *namep contiains a poपूर्णांकer to the property
 *		name.
 *	शून्य, on error
 *		अगर lenp is non-शून्य, *lenp contains an error code (<0):
 *		-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_PROP tag
 *		-FDT_ERR_BADMAGIC,
 *		-FDT_ERR_BADVERSION,
 *		-FDT_ERR_BADSTATE,
 *		-FDT_ERR_BADSTRUCTURE,
 *		-FDT_ERR_TRUNCATED, standard meanings
 */
#अगर_अघोषित SWIG /* This function is not useful in Python */
स्थिर व्योम *fdt_getprop_by_offset(स्थिर व्योम *fdt, पूर्णांक offset,
				  स्थिर अक्षर **namep, पूर्णांक *lenp);
#पूर्ण_अगर

/**
 * fdt_getprop_namelen - get property value based on substring
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to find
 * @name: name of the property to find
 * @namelen: number of अक्षरacters of name to consider
 * @lenp: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * Identical to fdt_getprop(), but only examine the first namelen
 * अक्षरacters of name क्रम matching the property name.
 *
 * Return: poपूर्णांकer to the property's value or शून्य on error
 */
#अगर_अघोषित SWIG /* Not available in Python */
स्थिर व्योम *fdt_getprop_namelen(स्थिर व्योम *fdt, पूर्णांक nodeoffset,
				स्थिर अक्षर *name, पूर्णांक namelen, पूर्णांक *lenp);
अटल अंतरभूत व्योम *fdt_getprop_namelen_w(व्योम *fdt, पूर्णांक nodeoffset,
					  स्थिर अक्षर *name, पूर्णांक namelen,
					  पूर्णांक *lenp)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)fdt_getprop_namelen(fdt, nodeoffset, name,
						      namelen, lenp);
पूर्ण
#पूर्ण_अगर

/**
 * fdt_getprop - retrieve the value of a given property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to find
 * @name: name of the property to find
 * @lenp: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * fdt_getprop() retrieves a poपूर्णांकer to the value of the property
 * named @name of the node at offset @nodeoffset (this will be a
 * poपूर्णांकer to within the device blob itself, not a copy of the value).
 * If @lenp is non-शून्य, the length of the property value is also
 * वापसed, in the पूर्णांकeger poपूर्णांकed to by @lenp.
 *
 * वापसs:
 *	poपूर्णांकer to the property's value
 *		अगर lenp is non-शून्य, *lenp contains the length of the property
 *		value (>=0)
 *	शून्य, on error
 *		अगर lenp is non-शून्य, *lenp contains an error code (<0):
 *		-FDT_ERR_NOTFOUND, node करोes not have named property
 *		-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE
 *			tag
 *		-FDT_ERR_BADMAGIC,
 *		-FDT_ERR_BADVERSION,
 *		-FDT_ERR_BADSTATE,
 *		-FDT_ERR_BADSTRUCTURE,
 *		-FDT_ERR_TRUNCATED, standard meanings
 */
स्थिर व्योम *fdt_getprop(स्थिर व्योम *fdt, पूर्णांक nodeoffset,
			स्थिर अक्षर *name, पूर्णांक *lenp);
अटल अंतरभूत व्योम *fdt_getprop_w(व्योम *fdt, पूर्णांक nodeoffset,
				  स्थिर अक्षर *name, पूर्णांक *lenp)
अणु
	वापस (व्योम *)(uपूर्णांकptr_t)fdt_getprop(fdt, nodeoffset, name, lenp);
पूर्ण

/**
 * fdt_get_phandle - retrieve the phandle of a given node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: काष्ठाure block offset of the node
 *
 * fdt_get_phandle() retrieves the phandle of the device tree node at
 * काष्ठाure block offset nodeoffset.
 *
 * वापसs:
 *	the phandle of the node at nodeoffset, on success (!= 0, != -1)
 *	0, अगर the node has no phandle, or another error occurs
 */
uपूर्णांक32_t fdt_get_phandle(स्थिर व्योम *fdt, पूर्णांक nodeoffset);

/**
 * fdt_get_alias_namelen - get alias based on substring
 * @fdt: poपूर्णांकer to the device tree blob
 * @name: name of the alias th look up
 * @namelen: number of अक्षरacters of name to consider
 *
 * Identical to fdt_get_alias(), but only examine the first @namelen
 * अक्षरacters of @name क्रम matching the alias name.
 *
 * Return: a poपूर्णांकer to the expansion of the alias named @name, अगर it exists,
 *	   शून्य otherwise
 */
#अगर_अघोषित SWIG /* Not available in Python */
स्थिर अक्षर *fdt_get_alias_namelen(स्थिर व्योम *fdt,
				  स्थिर अक्षर *name, पूर्णांक namelen);
#पूर्ण_अगर

/**
 * fdt_get_alias - retrieve the path referenced by a given alias
 * @fdt: poपूर्णांकer to the device tree blob
 * @name: name of the alias th look up
 *
 * fdt_get_alias() retrieves the value of a given alias.  That is, the
 * value of the property named @name in the node /aliases.
 *
 * वापसs:
 *	a poपूर्णांकer to the expansion of the alias named 'name', अगर it exists
 *	शून्य, अगर the given alias or the /aliases node करोes not exist
 */
स्थिर अक्षर *fdt_get_alias(स्थिर व्योम *fdt, स्थिर अक्षर *name);

/**
 * fdt_get_path - determine the full path of a node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose path to find
 * @buf: अक्षरacter buffer to contain the वापसed path (will be overwritten)
 * @buflen: size of the अक्षरacter buffer at buf
 *
 * fdt_get_path() computes the full path of the node at offset
 * nodeoffset, and records that path in the buffer at buf.
 *
 * NOTE: This function is expensive, as it must scan the device tree
 * काष्ठाure from the start to nodeoffset.
 *
 * वापसs:
 *	0, on success
 *		buf contains the असलolute path of the node at
 *		nodeoffset, as a NUL-terminated string.
 *	-FDT_ERR_BADOFFSET, nodeoffset करोes not refer to a BEGIN_NODE tag
 *	-FDT_ERR_NOSPACE, the path of the given node is दीर्घer than (bufsize-1)
 *		अक्षरacters and will not fit in the given buffer.
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_get_path(स्थिर व्योम *fdt, पूर्णांक nodeoffset, अक्षर *buf, पूर्णांक buflen);

/**
 * fdt_supernode_atdepth_offset - find a specअगरic ancestor of a node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose parent to find
 * @supernodedepth: depth of the ancestor to find
 * @nodedepth: poपूर्णांकer to an पूर्णांकeger variable (will be overwritten) or शून्य
 *
 * fdt_supernode_atdepth_offset() finds an ancestor of the given node
 * at a specअगरic depth from the root (where the root itself has depth
 * 0, its immediate subnodes depth 1 and so क्रमth).  So
 *	fdt_supernode_atdepth_offset(fdt, nodeoffset, 0, शून्य);
 * will always वापस 0, the offset of the root node.  If the node at
 * nodeoffset has depth D, then:
 *	fdt_supernode_atdepth_offset(fdt, nodeoffset, D, शून्य);
 * will वापस nodeoffset itself.
 *
 * NOTE: This function is expensive, as it must scan the device tree
 * काष्ठाure from the start to nodeoffset.
 *
 * वापसs:
 *	काष्ठाure block offset of the node at node offset's ancestor
 *		of depth supernodedepth (>=0), on success
 *	-FDT_ERR_BADOFFSET, nodeoffset करोes not refer to a BEGIN_NODE tag
 *	-FDT_ERR_NOTFOUND, supernodedepth was greater than the depth of
 *		nodeoffset
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_supernode_atdepth_offset(स्थिर व्योम *fdt, पूर्णांक nodeoffset,
				 पूर्णांक supernodedepth, पूर्णांक *nodedepth);

/**
 * fdt_node_depth - find the depth of a given node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose parent to find
 *
 * fdt_node_depth() finds the depth of a given node.  The root node
 * has depth 0, its immediate subnodes depth 1 and so क्रमth.
 *
 * NOTE: This function is expensive, as it must scan the device tree
 * काष्ठाure from the start to nodeoffset.
 *
 * वापसs:
 *	depth of the node at nodeoffset (>=0), on success
 *	-FDT_ERR_BADOFFSET, nodeoffset करोes not refer to a BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_node_depth(स्थिर व्योम *fdt, पूर्णांक nodeoffset);

/**
 * fdt_parent_offset - find the parent of a given node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose parent to find
 *
 * fdt_parent_offset() locates the parent node of a given node (that
 * is, it finds the offset of the node which contains the node at
 * nodeoffset as a subnode).
 *
 * NOTE: This function is expensive, as it must scan the device tree
 * काष्ठाure from the start to nodeoffset, *twice*.
 *
 * वापसs:
 *	काष्ठाure block offset of the parent of the node at nodeoffset
 *		(>=0), on success
 *	-FDT_ERR_BADOFFSET, nodeoffset करोes not refer to a BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_parent_offset(स्थिर व्योम *fdt, पूर्णांक nodeoffset);

/**
 * fdt_node_offset_by_prop_value - find nodes with a given property value
 * @fdt: poपूर्णांकer to the device tree blob
 * @startoffset: only find nodes after this offset
 * @propname: property name to check
 * @propval: property value to search क्रम
 * @proplen: length of the value in propval
 *
 * fdt_node_offset_by_prop_value() वापसs the offset of the first
 * node after startoffset, which has a property named propname whose
 * value is of length proplen and has value equal to propval; or अगर
 * startoffset is -1, the very first such node in the tree.
 *
 * To iterate through all nodes matching the criterion, the following
 * idiom can be used:
 *	offset = fdt_node_offset_by_prop_value(fdt, -1, propname,
 *					       propval, proplen);
 *	जबतक (offset != -FDT_ERR_NOTFOUND) अणु
 *		// other code here
 *		offset = fdt_node_offset_by_prop_value(fdt, offset, propname,
 *						       propval, proplen);
 *	पूर्ण
 *
 * Note the -1 in the first call to the function, अगर 0 is used here
 * instead, the function will never locate the root node, even अगर it
 * matches the criterion.
 *
 * वापसs:
 *	काष्ठाure block offset of the located node (>= 0, >startoffset),
 *		 on success
 *	-FDT_ERR_NOTFOUND, no node matching the criterion exists in the
 *		tree after startoffset
 *	-FDT_ERR_BADOFFSET, nodeoffset करोes not refer to a BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_node_offset_by_prop_value(स्थिर व्योम *fdt, पूर्णांक startoffset,
				  स्थिर अक्षर *propname,
				  स्थिर व्योम *propval, पूर्णांक proplen);

/**
 * fdt_node_offset_by_phandle - find the node with a given phandle
 * @fdt: poपूर्णांकer to the device tree blob
 * @phandle: phandle value
 *
 * fdt_node_offset_by_phandle() वापसs the offset of the node
 * which has the given phandle value.  If there is more than one node
 * in the tree with the given phandle (an invalid tree), results are
 * undefined.
 *
 * वापसs:
 *	काष्ठाure block offset of the located node (>= 0), on success
 *	-FDT_ERR_NOTFOUND, no node with that phandle exists
 *	-FDT_ERR_BADPHANDLE, given phandle value was invalid (0 or -1)
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_node_offset_by_phandle(स्थिर व्योम *fdt, uपूर्णांक32_t phandle);

/**
 * fdt_node_check_compatible - check a node's compatible property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of a tree node
 * @compatible: string to match against
 *
 * fdt_node_check_compatible() वापसs 0 अगर the given node contains a
 * @compatible property with the given string as one of its elements,
 * it वापसs non-zero otherwise, or on error.
 *
 * वापसs:
 *	0, अगर the node has a 'compatible' property listing the given string
 *	1, अगर the node has a 'compatible' property, but it करोes not list
 *		the given string
 *	-FDT_ERR_NOTFOUND, अगर the given node has no 'compatible' property
 *	-FDT_ERR_BADOFFSET, अगर nodeoffset करोes not refer to a BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_node_check_compatible(स्थिर व्योम *fdt, पूर्णांक nodeoffset,
			      स्थिर अक्षर *compatible);

/**
 * fdt_node_offset_by_compatible - find nodes with a given 'compatible' value
 * @fdt: poपूर्णांकer to the device tree blob
 * @startoffset: only find nodes after this offset
 * @compatible: 'compatible' string to match against
 *
 * fdt_node_offset_by_compatible() वापसs the offset of the first
 * node after startoffset, which has a 'compatible' property which
 * lists the given compatible string; or अगर startoffset is -1, the
 * very first such node in the tree.
 *
 * To iterate through all nodes matching the criterion, the following
 * idiom can be used:
 *	offset = fdt_node_offset_by_compatible(fdt, -1, compatible);
 *	जबतक (offset != -FDT_ERR_NOTFOUND) अणु
 *		// other code here
 *		offset = fdt_node_offset_by_compatible(fdt, offset, compatible);
 *	पूर्ण
 *
 * Note the -1 in the first call to the function, अगर 0 is used here
 * instead, the function will never locate the root node, even अगर it
 * matches the criterion.
 *
 * वापसs:
 *	काष्ठाure block offset of the located node (>= 0, >startoffset),
 *		 on success
 *	-FDT_ERR_NOTFOUND, no node matching the criterion exists in the
 *		tree after startoffset
 *	-FDT_ERR_BADOFFSET, nodeoffset करोes not refer to a BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE, standard meanings
 */
पूर्णांक fdt_node_offset_by_compatible(स्थिर व्योम *fdt, पूर्णांक startoffset,
				  स्थिर अक्षर *compatible);

/**
 * fdt_stringlist_contains - check a string list property क्रम a string
 * @strlist: Property containing a list of strings to check
 * @listlen: Length of property
 * @str: String to search क्रम
 *
 * This is a utility function provided क्रम convenience. The list contains
 * one or more strings, each terminated by \0, as is found in a device tree
 * "compatible" property.
 *
 * Return: 1 अगर the string is found in the list, 0 not found, or invalid list
 */
पूर्णांक fdt_stringlist_contains(स्थिर अक्षर *strlist, पूर्णांक listlen, स्थिर अक्षर *str);

/**
 * fdt_stringlist_count - count the number of strings in a string list
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of a tree node
 * @property: name of the property containing the string list
 *
 * Return:
 *   the number of strings in the given property
 *   -FDT_ERR_BADVALUE अगर the property value is not NUL-terminated
 *   -FDT_ERR_NOTFOUND अगर the property करोes not exist
 */
पूर्णांक fdt_stringlist_count(स्थिर व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *property);

/**
 * fdt_stringlist_search - find a string in a string list and वापस its index
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of a tree node
 * @property: name of the property containing the string list
 * @string: string to look up in the string list
 *
 * Note that it is possible क्रम this function to succeed on property values
 * that are not NUL-terminated. That's because the function will stop after
 * finding the first occurrence of @string. This can क्रम example happen with
 * small-valued cell properties, such as #address-cells, when searching क्रम
 * the empty string.
 *
 * वापस:
 *   the index of the string in the list of strings
 *   -FDT_ERR_BADVALUE अगर the property value is not NUL-terminated
 *   -FDT_ERR_NOTFOUND अगर the property करोes not exist or करोes not contain
 *                     the given string
 */
पूर्णांक fdt_stringlist_search(स्थिर व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *property,
			  स्थिर अक्षर *string);

/**
 * fdt_stringlist_get() - obtain the string at a given index in a string list
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of a tree node
 * @property: name of the property containing the string list
 * @index: index of the string to वापस
 * @lenp: वापस location क्रम the string length or an error code on failure
 *
 * Note that this will successfully extract strings from properties with
 * non-NUL-terminated values. For example on small-valued cell properties
 * this function will वापस the empty string.
 *
 * If non-शून्य, the length of the string (on success) or a negative error-code
 * (on failure) will be stored in the पूर्णांकeger poपूर्णांकer to by lenp.
 *
 * Return:
 *   A poपूर्णांकer to the string at the given index in the string list or शून्य on
 *   failure. On success the length of the string will be stored in the memory
 *   location poपूर्णांकed to by the lenp parameter, अगर non-शून्य. On failure one of
 *   the following negative error codes will be वापसed in the lenp parameter
 *   (अगर non-शून्य):
 *     -FDT_ERR_BADVALUE अगर the property value is not NUL-terminated
 *     -FDT_ERR_NOTFOUND अगर the property करोes not exist
 */
स्थिर अक्षर *fdt_stringlist_get(स्थिर व्योम *fdt, पूर्णांक nodeoffset,
			       स्थिर अक्षर *property, पूर्णांक index,
			       पूर्णांक *lenp);

/**********************************************************************/
/* Read-only functions (addressing related)                           */
/**********************************************************************/

/**
 * FDT_MAX_NCELLS - maximum value क्रम #address-cells and #size-cells
 *
 * This is the maximum value क्रम #address-cells, #size-cells and
 * similar properties that will be processed by libfdt.  IEE1275
 * requires that OF implementations handle values up to 4.
 * Implementations may support larger values, but in practice higher
 * values aren't used.
 */
#घोषणा FDT_MAX_NCELLS		4

/**
 * fdt_address_cells - retrieve address size क्रम a bus represented in the tree
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node to find the address size क्रम
 *
 * When the node has a valid #address-cells property, वापसs its value.
 *
 * वापसs:
 *	0 <= n < FDT_MAX_NCELLS, on success
 *      2, अगर the node has no #address-cells property
 *      -FDT_ERR_BADNCELLS, अगर the node has a badly क्रमmatted or invalid
 *		#address-cells property
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_address_cells(स्थिर व्योम *fdt, पूर्णांक nodeoffset);

/**
 * fdt_size_cells - retrieve address range size क्रम a bus represented in the
 *                  tree
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node to find the address range size क्रम
 *
 * When the node has a valid #size-cells property, वापसs its value.
 *
 * वापसs:
 *	0 <= n < FDT_MAX_NCELLS, on success
 *      1, अगर the node has no #size-cells property
 *      -FDT_ERR_BADNCELLS, अगर the node has a badly क्रमmatted or invalid
 *		#size-cells property
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_size_cells(स्थिर व्योम *fdt, पूर्णांक nodeoffset);


/**********************************************************************/
/* Write-in-place functions                                           */
/**********************************************************************/

/**
 * fdt_setprop_inplace_namelen_partial - change a property's value,
 *                                       but not its size
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @namelen: number of अक्षरacters of name to consider
 * @idx: index of the property to change in the array
 * @val: poपूर्णांकer to data to replace the property value with
 * @len: length of the property value
 *
 * Identical to fdt_setprop_inplace(), but modअगरies the given property
 * starting from the given index, and using only the first अक्षरacters
 * of the name. It is useful when you want to manipulate only one value of
 * an array and you have a string that करोesn't end with \0.
 *
 * Return: 0 on success, negative libfdt error value otherwise
 */
#अगर_अघोषित SWIG /* Not available in Python */
पूर्णांक fdt_setprop_inplace_namelen_partial(व्योम *fdt, पूर्णांक nodeoffset,
					स्थिर अक्षर *name, पूर्णांक namelen,
					uपूर्णांक32_t idx, स्थिर व्योम *val,
					पूर्णांक len);
#पूर्ण_अगर

/**
 * fdt_setprop_inplace - change a property's value, but not its size
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: poपूर्णांकer to data to replace the property value with
 * @len: length of the property value
 *
 * fdt_setprop_inplace() replaces the value of a given property with
 * the data in val, of length len.  This function cannot change the
 * size of a property, and so will only work अगर len is equal to the
 * current length of the property.
 *
 * This function will alter only the bytes in the blob which contain
 * the given property value, and will not alter or move any other part
 * of the tree.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, अगर len is not equal to the property's current length
 *	-FDT_ERR_NOTFOUND, node करोes not have the named property
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
#अगर_अघोषित SWIG /* Not available in Python */
पूर्णांक fdt_setprop_inplace(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
			स्थिर व्योम *val, पूर्णांक len);
#पूर्ण_अगर

/**
 * fdt_setprop_inplace_u32 - change the value of a 32-bit पूर्णांकeger property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 32-bit पूर्णांकeger value to replace the property with
 *
 * fdt_setprop_inplace_u32() replaces the value of a given property
 * with the 32-bit पूर्णांकeger value in val, converting val to big-endian
 * अगर necessary.  This function cannot change the size of a property,
 * and so will only work अगर the property alपढ़ोy exists and has length
 * 4.
 *
 * This function will alter only the bytes in the blob which contain
 * the given property value, and will not alter or move any other part
 * of the tree.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, अगर the property's length is not equal to 4
 *	-FDT_ERR_NOTFOUND, node करोes not have the named property
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
अटल अंतरभूत पूर्णांक fdt_setprop_inplace_u32(व्योम *fdt, पूर्णांक nodeoffset,
					  स्थिर अक्षर *name, uपूर्णांक32_t val)
अणु
	fdt32_t पंचांगp = cpu_to_fdt32(val);
	वापस fdt_setprop_inplace(fdt, nodeoffset, name, &पंचांगp, माप(पंचांगp));
पूर्ण

/**
 * fdt_setprop_inplace_u64 - change the value of a 64-bit पूर्णांकeger property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 64-bit पूर्णांकeger value to replace the property with
 *
 * fdt_setprop_inplace_u64() replaces the value of a given property
 * with the 64-bit पूर्णांकeger value in val, converting val to big-endian
 * अगर necessary.  This function cannot change the size of a property,
 * and so will only work अगर the property alपढ़ोy exists and has length
 * 8.
 *
 * This function will alter only the bytes in the blob which contain
 * the given property value, and will not alter or move any other part
 * of the tree.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, अगर the property's length is not equal to 8
 *	-FDT_ERR_NOTFOUND, node करोes not have the named property
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
अटल अंतरभूत पूर्णांक fdt_setprop_inplace_u64(व्योम *fdt, पूर्णांक nodeoffset,
					  स्थिर अक्षर *name, uपूर्णांक64_t val)
अणु
	fdt64_t पंचांगp = cpu_to_fdt64(val);
	वापस fdt_setprop_inplace(fdt, nodeoffset, name, &पंचांगp, माप(पंचांगp));
पूर्ण

/**
 * fdt_setprop_inplace_cell - change the value of a single-cell property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node containing the property
 * @name: name of the property to change the value of
 * @val: new value of the 32-bit cell
 *
 * This is an alternative name क्रम fdt_setprop_inplace_u32()
 * Return: 0 on success, negative libfdt error number otherwise.
 */
अटल अंतरभूत पूर्णांक fdt_setprop_inplace_cell(व्योम *fdt, पूर्णांक nodeoffset,
					   स्थिर अक्षर *name, uपूर्णांक32_t val)
अणु
	वापस fdt_setprop_inplace_u32(fdt, nodeoffset, name, val);
पूर्ण

/**
 * fdt_nop_property - replace a property with nop tags
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to nop
 * @name: name of the property to nop
 *
 * fdt_nop_property() will replace a given property's representation
 * in the blob with FDT_NOP tags, effectively removing it from the
 * tree.
 *
 * This function will alter only the bytes in the blob which contain
 * the property, and will not alter or move any other part of the
 * tree.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOTFOUND, node करोes not have the named property
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_nop_property(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name);

/**
 * fdt_nop_node - replace a node (subtree) with nop tags
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node to nop
 *
 * fdt_nop_node() will replace a given node's representation in the
 * blob, including all its subnodes, अगर any, with FDT_NOP tags,
 * effectively removing it from the tree.
 *
 * This function will alter only the bytes in the blob which contain
 * the node and its properties and subnodes, and will not alter or
 * move any other part of the tree.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_nop_node(व्योम *fdt, पूर्णांक nodeoffset);

/**********************************************************************/
/* Sequential ग_लिखो functions                                         */
/**********************************************************************/

/* fdt_create_with_flags flags */
#घोषणा FDT_CREATE_FLAG_NO_NAME_DEDUP 0x1
	/* FDT_CREATE_FLAG_NO_NAME_DEDUP: Do not try to de-duplicate property
	 * names in the fdt. This can result in faster creation बार, but
	 * a larger fdt. */

#घोषणा FDT_CREATE_FLAGS_ALL	(FDT_CREATE_FLAG_NO_NAME_DEDUP)

/**
 * fdt_create_with_flags - begin creation of a new fdt
 * @buf: poपूर्णांकer to memory allocated where fdt will be created
 * @bufsize: size of the memory space at fdt
 * @flags: a valid combination of FDT_CREATE_FLAG_ flags, or 0.
 *
 * fdt_create_with_flags() begins the process of creating a new fdt with
 * the sequential ग_लिखो पूर्णांकerface.
 *
 * fdt creation process must end with fdt_finished() to produce a valid fdt.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, bufsize is insufficient क्रम a minimal fdt
 *	-FDT_ERR_BADFLAGS, flags is not valid
 */
पूर्णांक fdt_create_with_flags(व्योम *buf, पूर्णांक bufsize, uपूर्णांक32_t flags);

/**
 * fdt_create - begin creation of a new fdt
 * @buf: poपूर्णांकer to memory allocated where fdt will be created
 * @bufsize: size of the memory space at fdt
 *
 * fdt_create() is equivalent to fdt_create_with_flags() with flags=0.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, bufsize is insufficient क्रम a minimal fdt
 */
पूर्णांक fdt_create(व्योम *buf, पूर्णांक bufsize);

पूर्णांक fdt_resize(व्योम *fdt, व्योम *buf, पूर्णांक bufsize);
पूर्णांक fdt_add_reservemap_entry(व्योम *fdt, uपूर्णांक64_t addr, uपूर्णांक64_t size);
पूर्णांक fdt_finish_reservemap(व्योम *fdt);
पूर्णांक fdt_begin_node(व्योम *fdt, स्थिर अक्षर *name);
पूर्णांक fdt_property(व्योम *fdt, स्थिर अक्षर *name, स्थिर व्योम *val, पूर्णांक len);
अटल अंतरभूत पूर्णांक fdt_property_u32(व्योम *fdt, स्थिर अक्षर *name, uपूर्णांक32_t val)
अणु
	fdt32_t पंचांगp = cpu_to_fdt32(val);
	वापस fdt_property(fdt, name, &पंचांगp, माप(पंचांगp));
पूर्ण
अटल अंतरभूत पूर्णांक fdt_property_u64(व्योम *fdt, स्थिर अक्षर *name, uपूर्णांक64_t val)
अणु
	fdt64_t पंचांगp = cpu_to_fdt64(val);
	वापस fdt_property(fdt, name, &पंचांगp, माप(पंचांगp));
पूर्ण

#अगर_अघोषित SWIG /* Not available in Python */
अटल अंतरभूत पूर्णांक fdt_property_cell(व्योम *fdt, स्थिर अक्षर *name, uपूर्णांक32_t val)
अणु
	वापस fdt_property_u32(fdt, name, val);
पूर्ण
#पूर्ण_अगर

/**
 * fdt_property_placeholder - add a new property and वापस a ptr to its value
 *
 * @fdt: poपूर्णांकer to the device tree blob
 * @name: name of property to add
 * @len: length of property value in bytes
 * @valp: वापसs a poपूर्णांकer to where where the value should be placed
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_NOSPACE, standard meanings
 */
पूर्णांक fdt_property_placeholder(व्योम *fdt, स्थिर अक्षर *name, पूर्णांक len, व्योम **valp);

#घोषणा fdt_property_string(fdt, name, str) \
	fdt_property(fdt, name, str, म_माप(str)+1)
पूर्णांक fdt_end_node(व्योम *fdt);
पूर्णांक fdt_finish(व्योम *fdt);

/**********************************************************************/
/* Read-ग_लिखो functions                                               */
/**********************************************************************/

पूर्णांक fdt_create_empty_tree(व्योम *buf, पूर्णांक bufsize);
पूर्णांक fdt_खोलो_पूर्णांकo(स्थिर व्योम *fdt, व्योम *buf, पूर्णांक bufsize);
पूर्णांक fdt_pack(व्योम *fdt);

/**
 * fdt_add_mem_rsv - add one memory reserve map entry
 * @fdt: poपूर्णांकer to the device tree blob
 * @address: 64-bit start address of the reserve map entry
 * @size: 64-bit size of the reserved region
 *
 * Adds a reserve map entry to the given blob reserving a region at
 * address address of length size.
 *
 * This function will insert data पूर्णांकo the reserve map and will
 * thereक्रमe change the indexes of some entries in the table.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new reservation entry
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_add_mem_rsv(व्योम *fdt, uपूर्णांक64_t address, uपूर्णांक64_t size);

/**
 * fdt_del_mem_rsv - हटाओ a memory reserve map entry
 * @fdt: poपूर्णांकer to the device tree blob
 * @n: entry to हटाओ
 *
 * fdt_del_mem_rsv() हटाओs the n-th memory reserve map entry from
 * the blob.
 *
 * This function will delete data from the reservation table and will
 * thereक्रमe change the indexes of some entries in the table.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOTFOUND, there is no entry of the given index (i.e. there
 *		are less than n+1 reserve map entries)
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_del_mem_rsv(व्योम *fdt, पूर्णांक n);

/**
 * fdt_set_name - change the name of a given node
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: काष्ठाure block offset of a node
 * @name: name to give the node
 *
 * fdt_set_name() replaces the name (including unit address, अगर any)
 * of the given node with the given string.  NOTE: this function can't
 * efficiently check अगर the new name is unique amongst the given
 * node's siblings; results are undefined अगर this function is invoked
 * with a name equal to one of the given node's siblings.
 *
 * This function may insert or delete data from the blob, and will
 * thereक्रमe change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob
 *		to contain the new name
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE, standard meanings
 */
पूर्णांक fdt_set_name(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name);

/**
 * fdt_setprop - create or change a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: poपूर्णांकer to data to set the property value to
 * @len: length of the property value
 *
 * fdt_setprop() sets the value of the named property in the given
 * node to the given value and length, creating the property अगर it
 * करोes not alपढ़ोy exist.
 *
 * This function may insert or delete data from the blob, and will
 * thereक्रमe change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_setprop(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
		स्थिर व्योम *val, पूर्णांक len);

/**
 * fdt_setprop_placeholder - allocate space क्रम a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @len: length of the property value
 * @prop_data: वापस poपूर्णांकer to property data
 *
 * fdt_setprop_placeholer() allocates the named property in the given node.
 * If the property exists it is resized. In either हाल a poपूर्णांकer to the
 * property data is वापसed.
 *
 * This function may insert or delete data from the blob, and will
 * thereक्रमe change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_setprop_placeholder(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
			    पूर्णांक len, व्योम **prop_data);

/**
 * fdt_setprop_u32 - set a property to a 32-bit पूर्णांकeger
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 32-bit पूर्णांकeger value क्रम the property (native endian)
 *
 * fdt_setprop_u32() sets the value of the named property in the given
 * node to the given 32-bit पूर्णांकeger value (converting to big-endian अगर
 * necessary), or creates a new property with that value अगर it करोes
 * not alपढ़ोy exist.
 *
 * This function may insert or delete data from the blob, and will
 * thereक्रमe change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
अटल अंतरभूत पूर्णांक fdt_setprop_u32(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
				  uपूर्णांक32_t val)
अणु
	fdt32_t पंचांगp = cpu_to_fdt32(val);
	वापस fdt_setprop(fdt, nodeoffset, name, &पंचांगp, माप(पंचांगp));
पूर्ण

/**
 * fdt_setprop_u64 - set a property to a 64-bit पूर्णांकeger
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 64-bit पूर्णांकeger value क्रम the property (native endian)
 *
 * fdt_setprop_u64() sets the value of the named property in the given
 * node to the given 64-bit पूर्णांकeger value (converting to big-endian अगर
 * necessary), or creates a new property with that value अगर it करोes
 * not alपढ़ोy exist.
 *
 * This function may insert or delete data from the blob, and will
 * thereक्रमe change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
अटल अंतरभूत पूर्णांक fdt_setprop_u64(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
				  uपूर्णांक64_t val)
अणु
	fdt64_t पंचांगp = cpu_to_fdt64(val);
	वापस fdt_setprop(fdt, nodeoffset, name, &पंचांगp, माप(पंचांगp));
पूर्ण

/**
 * fdt_setprop_cell - set a property to a single cell value
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 32-bit पूर्णांकeger value क्रम the property (native endian)
 *
 * This is an alternative name क्रम fdt_setprop_u32()
 *
 * Return: 0 on success, negative libfdt error value otherwise.
 */
अटल अंतरभूत पूर्णांक fdt_setprop_cell(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
				   uपूर्णांक32_t val)
अणु
	वापस fdt_setprop_u32(fdt, nodeoffset, name, val);
पूर्ण

/**
 * fdt_setprop_string - set a property to a string value
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @str: string value क्रम the property
 *
 * fdt_setprop_string() sets the value of the named property in the
 * given node to the given string value (using the length of the
 * string to determine the new length of the property), or creates a
 * new property with that value अगर it करोes not alपढ़ोy exist.
 *
 * This function may insert or delete data from the blob, and will
 * thereक्रमe change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
#घोषणा fdt_setprop_string(fdt, nodeoffset, name, str) \
	fdt_setprop((fdt), (nodeoffset), (name), (str), म_माप(str)+1)


/**
 * fdt_setprop_empty - set a property to an empty value
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 *
 * fdt_setprop_empty() sets the value of the named property in the
 * given node to an empty (zero length) value, or creates a new empty
 * property अगर it करोes not alपढ़ोy exist.
 *
 * This function may insert or delete data from the blob, and will
 * thereक्रमe change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
#घोषणा fdt_setprop_empty(fdt, nodeoffset, name) \
	fdt_setprop((fdt), (nodeoffset), (name), शून्य, 0)

/**
 * fdt_appendprop - append to or create a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to append to
 * @val: poपूर्णांकer to data to append to the property value
 * @len: length of the data to append to the property value
 *
 * fdt_appendprop() appends the value to the named property in the
 * given node, creating the property अगर it करोes not alपढ़ोy exist.
 *
 * This function may insert data पूर्णांकo the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_appendprop(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
		   स्थिर व्योम *val, पूर्णांक len);

/**
 * fdt_appendprop_u32 - append a 32-bit पूर्णांकeger value to a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 32-bit पूर्णांकeger value to append to the property (native endian)
 *
 * fdt_appendprop_u32() appends the given 32-bit पूर्णांकeger value
 * (converting to big-endian अगर necessary) to the value of the named
 * property in the given node, or creates a new property with that
 * value अगर it करोes not alपढ़ोy exist.
 *
 * This function may insert data पूर्णांकo the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
अटल अंतरभूत पूर्णांक fdt_appendprop_u32(व्योम *fdt, पूर्णांक nodeoffset,
				     स्थिर अक्षर *name, uपूर्णांक32_t val)
अणु
	fdt32_t पंचांगp = cpu_to_fdt32(val);
	वापस fdt_appendprop(fdt, nodeoffset, name, &पंचांगp, माप(पंचांगp));
पूर्ण

/**
 * fdt_appendprop_u64 - append a 64-bit पूर्णांकeger value to a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 64-bit पूर्णांकeger value to append to the property (native endian)
 *
 * fdt_appendprop_u64() appends the given 64-bit पूर्णांकeger value
 * (converting to big-endian अगर necessary) to the value of the named
 * property in the given node, or creates a new property with that
 * value अगर it करोes not alपढ़ोy exist.
 *
 * This function may insert data पूर्णांकo the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
अटल अंतरभूत पूर्णांक fdt_appendprop_u64(व्योम *fdt, पूर्णांक nodeoffset,
				     स्थिर अक्षर *name, uपूर्णांक64_t val)
अणु
	fdt64_t पंचांगp = cpu_to_fdt64(val);
	वापस fdt_appendprop(fdt, nodeoffset, name, &पंचांगp, माप(पंचांगp));
पूर्ण

/**
 * fdt_appendprop_cell - append a single cell value to a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @val: 32-bit पूर्णांकeger value to append to the property (native endian)
 *
 * This is an alternative name क्रम fdt_appendprop_u32()
 *
 * Return: 0 on success, negative libfdt error value otherwise.
 */
अटल अंतरभूत पूर्णांक fdt_appendprop_cell(व्योम *fdt, पूर्णांक nodeoffset,
				      स्थिर अक्षर *name, uपूर्णांक32_t val)
अणु
	वापस fdt_appendprop_u32(fdt, nodeoffset, name, val);
पूर्ण

/**
 * fdt_appendprop_string - append a string to a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to change
 * @name: name of the property to change
 * @str: string value to append to the property
 *
 * fdt_appendprop_string() appends the given string to the value of
 * the named property in the given node, or creates a new property
 * with that value अगर it करोes not alपढ़ोy exist.
 *
 * This function may insert data पूर्णांकo the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain the new property value
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
#घोषणा fdt_appendprop_string(fdt, nodeoffset, name, str) \
	fdt_appendprop((fdt), (nodeoffset), (name), (str), म_माप(str)+1)

/**
 * fdt_appendprop_addrrange - append a address range property
 * @fdt: poपूर्णांकer to the device tree blob
 * @parent: offset of the parent node
 * @nodeoffset: offset of the node to add a property at
 * @name: name of property
 * @addr: start address of a given range
 * @size: size of a given range
 *
 * fdt_appendprop_addrrange() appends an address range value (start
 * address and size) to the value of the named property in the given
 * node, or creates a new property with that value अगर it करोes not
 * alपढ़ोy exist.
 * If "name" is not specअगरied, a शेष "reg" is used.
 * Cell sizes are determined by parent's #address-cells and #size-cells.
 *
 * This function may insert data पूर्णांकo the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADNCELLS, अगर the node has a badly क्रमmatted or invalid
 *		#address-cells property
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADVALUE, addr or size करोesn't fit to respective cells size
 *	-FDT_ERR_NOSPACE, there is insufficient मुक्त space in the blob to
 *		contain a new property
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_appendprop_addrrange(व्योम *fdt, पूर्णांक parent, पूर्णांक nodeoffset,
			     स्थिर अक्षर *name, uपूर्णांक64_t addr, uपूर्णांक64_t size);

/**
 * fdt_delprop - delete a property
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node whose property to nop
 * @name: name of the property to nop
 *
 * fdt_del_property() will delete the given property.
 *
 * This function will delete data from the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOTFOUND, node करोes not have the named property
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_delprop(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name);

/**
 * fdt_add_subnode_namelen - creates a new node based on substring
 * @fdt: poपूर्णांकer to the device tree blob
 * @parentoffset: काष्ठाure block offset of a node
 * @name: name of the subnode to create
 * @namelen: number of अक्षरacters of name to consider
 *
 * Identical to fdt_add_subnode(), but use only the first @namelen
 * अक्षरacters of @name as the name of the new node.  This is useful क्रम
 * creating subnodes based on a portion of a larger string, such as a
 * full path.
 *
 * Return: काष्ठाure block offset of the created subnode (>=0),
 *	   negative libfdt error value otherwise
 */
#अगर_अघोषित SWIG /* Not available in Python */
पूर्णांक fdt_add_subnode_namelen(व्योम *fdt, पूर्णांक parentoffset,
			    स्थिर अक्षर *name, पूर्णांक namelen);
#पूर्ण_अगर

/**
 * fdt_add_subnode - creates a new node
 * @fdt: poपूर्णांकer to the device tree blob
 * @parentoffset: काष्ठाure block offset of a node
 * @name: name of the subnode to locate
 *
 * fdt_add_subnode() creates a new node as a subnode of the node at
 * काष्ठाure block offset parentoffset, with the given name (which
 * should include the unit address, अगर any).
 *
 * This function will insert data पूर्णांकo the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	काष्ठाure block offset of the created nodeequested subnode (>=0), on
 *		success
 *	-FDT_ERR_NOTFOUND, अगर the requested subnode करोes not exist
 *	-FDT_ERR_BADOFFSET, अगर parentoffset did not poपूर्णांक to an FDT_BEGIN_NODE
 *		tag
 *	-FDT_ERR_EXISTS, अगर the node at parentoffset alपढ़ोy has a subnode of
 *		the given name
 *	-FDT_ERR_NOSPACE, अगर there is insufficient मुक्त space in the
 *		blob to contain the new node
 *	-FDT_ERR_NOSPACE
 *	-FDT_ERR_BADLAYOUT
 *      -FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings.
 */
पूर्णांक fdt_add_subnode(व्योम *fdt, पूर्णांक parentoffset, स्थिर अक्षर *name);

/**
 * fdt_del_node - delete a node (subtree)
 * @fdt: poपूर्णांकer to the device tree blob
 * @nodeoffset: offset of the node to nop
 *
 * fdt_del_node() will हटाओ the given node, including all its
 * subnodes अगर any, from the blob.
 *
 * This function will delete data from the blob, and will thereक्रमe
 * change the offsets of some existing nodes.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_BADOFFSET, nodeoffset did not poपूर्णांक to FDT_BEGIN_NODE tag
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_del_node(व्योम *fdt, पूर्णांक nodeoffset);

/**
 * fdt_overlay_apply - Applies a DT overlay on a base DT
 * @fdt: poपूर्णांकer to the base device tree blob
 * @fdto: poपूर्णांकer to the device tree overlay blob
 *
 * fdt_overlay_apply() will apply the given device tree overlay on the
 * given base device tree.
 *
 * Expect the base device tree to be modअगरied, even अगर the function
 * वापसs an error.
 *
 * वापसs:
 *	0, on success
 *	-FDT_ERR_NOSPACE, there's not enough space in the base device tree
 *	-FDT_ERR_NOTFOUND, the overlay poपूर्णांकs to some inexistant nodes or
 *		properties in the base DT
 *	-FDT_ERR_BADPHANDLE,
 *	-FDT_ERR_BADOVERLAY,
 *	-FDT_ERR_NOPHANDLES,
 *	-FDT_ERR_INTERNAL,
 *	-FDT_ERR_BADLAYOUT,
 *	-FDT_ERR_BADMAGIC,
 *	-FDT_ERR_BADOFFSET,
 *	-FDT_ERR_BADPATH,
 *	-FDT_ERR_BADVERSION,
 *	-FDT_ERR_BADSTRUCTURE,
 *	-FDT_ERR_BADSTATE,
 *	-FDT_ERR_TRUNCATED, standard meanings
 */
पूर्णांक fdt_overlay_apply(व्योम *fdt, व्योम *fdto);

/**********************************************************************/
/* Debugging / inक्रमmational functions                                */
/**********************************************************************/

स्थिर अक्षर *fdt_म_त्रुटि(पूर्णांक errval);

#अगर_घोषित __cplusplus
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* LIBFDT_H */
