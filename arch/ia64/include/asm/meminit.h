<शैली गुरु>
#अगर_अघोषित meminit_h
#घोषणा meminit_h

/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */


/*
 * Entries defined so far:
 * 	- boot param काष्ठाure itself
 * 	- memory map
 * 	- initrd (optional)
 * 	- command line string
 * 	- kernel code & data
 * 	- crash dumping code reserved region
 * 	- Kernel memory map built from EFI memory map
 * 	- ELF core header
 *
 * More could be added अगर necessary
 */
#घोषणा IA64_MAX_RSVD_REGIONS 9

काष्ठा rsvd_region अणु
	u64 start;	/* भव address of beginning of element */
	u64 end;	/* भव address of end of element + 1 */
पूर्ण;

बाह्य काष्ठा rsvd_region rsvd_region[IA64_MAX_RSVD_REGIONS + 1];
बाह्य पूर्णांक num_rsvd_regions;

बाह्य व्योम find_memory (व्योम);
बाह्य व्योम reserve_memory (व्योम);
बाह्य व्योम find_initrd (व्योम);
बाह्य पूर्णांक filter_rsvd_memory (u64 start, u64 end, व्योम *arg);
बाह्य पूर्णांक filter_memory (u64 start, u64 end, व्योम *arg);
बाह्य अचिन्हित दीर्घ efi_memmap_init(u64 *s, u64 *e);
बाह्य पूर्णांक find_max_min_low_pfn (u64, u64, व्योम *);

बाह्य अचिन्हित दीर्घ vmcore_find_descriptor_size(अचिन्हित दीर्घ address);
बाह्य पूर्णांक reserve_elfcorehdr(u64 *start, u64 *end);

/*
 * For rounding an address to the next IA64_GRANULE_SIZE or order
 */
#घोषणा GRANULEROUNDDOWN(n)	((n) & ~(IA64_GRANULE_SIZE-1))
#घोषणा GRANULEROUNDUP(n)	(((n)+IA64_GRANULE_SIZE-1) & ~(IA64_GRANULE_SIZE-1))

#अगर_घोषित CONFIG_NUMA
  बाह्य व्योम call_pernode_memory (अचिन्हित दीर्घ start, अचिन्हित दीर्घ len, व्योम *func);
#अन्यथा
# define call_pernode_memory(start, len, func)	(*func)(start, len, 0)
#पूर्ण_अगर

#घोषणा IGNORE_PFN0	1	/* XXX fix me: ignore pfn 0 until TLB miss handler is updated... */

बाह्य पूर्णांक रेजिस्टर_active_ranges(u64 start, u64 len, पूर्णांक nid);

#पूर्ण_अगर /* meminit_h */
