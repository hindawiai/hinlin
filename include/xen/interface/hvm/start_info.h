<शैली गुरु>
/*
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2016, Citrix Systems, Inc.
 */

#अगर_अघोषित __XEN_PUBLIC_ARCH_X86_HVM_START_INFO_H__
#घोषणा __XEN_PUBLIC_ARCH_X86_HVM_START_INFO_H__

/*
 * Start of day काष्ठाure passed to PVH guests and to HVM guests in %ebx.
 *
 * NOTE: nothing will be loaded at physical address 0, so a 0 value in any
 * of the address fields should be treated as not present.
 *
 *  0 +----------------+
 *    | magic          | Contains the magic value XEN_HVM_START_MAGIC_VALUE
 *    |                | ("xEn3" with the 0x80 bit of the "E" set).
 *  4 +----------------+
 *    | version        | Version of this काष्ठाure. Current version is 1. New
 *    |                | versions are guaranteed to be backwards-compatible.
 *  8 +----------------+
 *    | flags          | SIF_xxx flags.
 * 12 +----------------+
 *    | nr_modules     | Number of modules passed to the kernel.
 * 16 +----------------+
 *    | modlist_paddr  | Physical address of an array of modules
 *    |                | (layout of the काष्ठाure below).
 * 24 +----------------+
 *    | cmdline_paddr  | Physical address of the command line,
 *    |                | a zero-terminated ASCII string.
 * 32 +----------------+
 *    | rsdp_paddr     | Physical address of the RSDP ACPI data काष्ठाure.
 * 40 +----------------+
 *    | memmap_paddr   | Physical address of the (optional) memory map. Only
 *    |                | present in version 1 and newer of the काष्ठाure.
 * 48 +----------------+
 *    | memmap_entries | Number of entries in the memory map table. Zero
 *    |                | अगर there is no memory map being provided. Only
 *    |                | present in version 1 and newer of the काष्ठाure.
 * 52 +----------------+
 *    | reserved       | Version 1 and newer only.
 * 56 +----------------+
 *
 * The layout of each entry in the module काष्ठाure is the following:
 *
 *  0 +----------------+
 *    | paddr          | Physical address of the module.
 *  8 +----------------+
 *    | size           | Size of the module in bytes.
 * 16 +----------------+
 *    | cmdline_paddr  | Physical address of the command line,
 *    |                | a zero-terminated ASCII string.
 * 24 +----------------+
 *    | reserved       |
 * 32 +----------------+
 *
 * The layout of each entry in the memory map table is as follows:
 *
 *  0 +----------------+
 *    | addr           | Base address
 *  8 +----------------+
 *    | size           | Size of mapping in bytes
 * 16 +----------------+
 *    | type           | Type of mapping as defined between the hypervisor
 *    |                | and guest. See XEN_HVM_MEMMAP_TYPE_* values below.
 * 20 +----------------|
 *    | reserved       |
 * 24 +----------------+
 *
 * The address and sizes are always a 64bit little endian अचिन्हित पूर्णांकeger.
 *
 * NB: Xen on x86 will always try to place all the data below the 4GiB
 * boundary.
 *
 * Version numbers of the hvm_start_info काष्ठाure have evolved like this:
 *
 * Version 0:  Initial implementation.
 *
 * Version 1:  Added the memmap_paddr/memmap_entries fields (plus 4 bytes of
 *             padding) to the end of the hvm_start_info काष्ठा. These new
 *             fields can be used to pass a memory map to the guest. The
 *             memory map is optional and so guests that understand version 1
 *             of the काष्ठाure must check that memmap_entries is non-zero
 *             beक्रमe trying to पढ़ो the memory map.
 */
#घोषणा XEN_HVM_START_MAGIC_VALUE 0x336ec578

/*
 * The values used in the type field of the memory map table entries are
 * defined below and match the Address Range Types as defined in the "System
 * Address Map Interfaces" section of the ACPI Specअगरication. Please refer to
 * section 15 in version 6.2 of the ACPI spec: http://uefi.org/specअगरications
 */
#घोषणा XEN_HVM_MEMMAP_TYPE_RAM       1
#घोषणा XEN_HVM_MEMMAP_TYPE_RESERVED  2
#घोषणा XEN_HVM_MEMMAP_TYPE_ACPI      3
#घोषणा XEN_HVM_MEMMAP_TYPE_NVS       4
#घोषणा XEN_HVM_MEMMAP_TYPE_UNUSABLE  5
#घोषणा XEN_HVM_MEMMAP_TYPE_DISABLED  6
#घोषणा XEN_HVM_MEMMAP_TYPE_PMEM      7

/*
 * C representation of the x86/HVM start info layout.
 *
 * The canonical definition of this layout is above, this is just a way to
 * represent the layout described there using C types.
 */
काष्ठा hvm_start_info अणु
    uपूर्णांक32_t magic;             /* Contains the magic value 0x336ec578       */
                                /* ("xEn3" with the 0x80 bit of the "E" set).*/
    uपूर्णांक32_t version;           /* Version of this काष्ठाure.                */
    uपूर्णांक32_t flags;             /* SIF_xxx flags.                            */
    uपूर्णांक32_t nr_modules;        /* Number of modules passed to the kernel.   */
    uपूर्णांक64_t modlist_paddr;     /* Physical address of an array of           */
                                /* hvm_modlist_entry.                        */
    uपूर्णांक64_t cmdline_paddr;     /* Physical address of the command line.     */
    uपूर्णांक64_t rsdp_paddr;        /* Physical address of the RSDP ACPI data    */
                                /* काष्ठाure.                                */
    /* All following fields only present in version 1 and newer */
    uपूर्णांक64_t memmap_paddr;      /* Physical address of an array of           */
                                /* hvm_memmap_table_entry.                   */
    uपूर्णांक32_t memmap_entries;    /* Number of entries in the memmap table.    */
                                /* Value will be zero अगर there is no memory  */
                                /* map being provided.                       */
    uपूर्णांक32_t reserved;          /* Must be zero.                             */
पूर्ण;

काष्ठा hvm_modlist_entry अणु
    uपूर्णांक64_t paddr;             /* Physical address of the module.           */
    uपूर्णांक64_t size;              /* Size of the module in bytes.              */
    uपूर्णांक64_t cmdline_paddr;     /* Physical address of the command line.     */
    uपूर्णांक64_t reserved;
पूर्ण;

काष्ठा hvm_memmap_table_entry अणु
    uपूर्णांक64_t addr;              /* Base address of the memory region         */
    uपूर्णांक64_t size;              /* Size of the memory region in bytes        */
    uपूर्णांक32_t type;              /* Mapping type                              */
    uपूर्णांक32_t reserved;          /* Must be zero क्रम Version 1.               */
पूर्ण;

#पूर्ण_अगर /* __XEN_PUBLIC_ARCH_X86_HVM_START_INFO_H__ */
