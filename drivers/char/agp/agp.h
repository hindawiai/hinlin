<शैली गुरु>
/*
 * AGPGART
 * Copyright (C) 2004 Silicon Graphics, Inc.
 * Copyright (C) 2002-2004 Dave Jones
 * Copyright (C) 1999 Jeff Harपंचांगann
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _AGP_BACKEND_PRIV_H
#घोषणा _AGP_BACKEND_PRIV_H 1

#समावेश <यंत्र/agp.h>	/* क्रम flush_agp_cache() */

#घोषणा PFX "agpgart: "

//#घोषणा AGP_DEBUG 1
#अगर_घोषित AGP_DEBUG
#घोषणा DBG(x,y...) prपूर्णांकk (KERN_DEBUG PFX "%s: " x "\n", __func__ , ## y)
#अन्यथा
#घोषणा DBG(x,y...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य काष्ठा agp_bridge_data *agp_bridge;

क्रमागत aper_माप_प्रकारype अणु
	U8_APER_SIZE,
	U16_APER_SIZE,
	U32_APER_SIZE,
	LVL2_APER_SIZE,
	FIXED_APER_SIZE
पूर्ण;

काष्ठा gatt_mask अणु
	अचिन्हित दीर्घ mask;
	u32 type;
	/* totally device specअगरic, क्रम पूर्णांकegrated chipsets that
	 * might have dअगरferent types of memory masks.  For other
	 * devices this will probably be ignored */
पूर्ण;

#घोषणा AGP_PAGE_DESTROY_UNMAP 1
#घोषणा AGP_PAGE_DESTROY_FREE 2

काष्ठा aper_size_info_8 अणु
	पूर्णांक size;
	पूर्णांक num_entries;
	पूर्णांक page_order;
	u8 size_value;
पूर्ण;

काष्ठा aper_size_info_16 अणु
	पूर्णांक size;
	पूर्णांक num_entries;
	पूर्णांक page_order;
	u16 size_value;
पूर्ण;

काष्ठा aper_size_info_32 अणु
	पूर्णांक size;
	पूर्णांक num_entries;
	पूर्णांक page_order;
	u32 size_value;
पूर्ण;

काष्ठा aper_size_info_lvl2 अणु
	पूर्णांक size;
	पूर्णांक num_entries;
	u32 size_value;
पूर्ण;

काष्ठा aper_size_info_fixed अणु
	पूर्णांक size;
	पूर्णांक num_entries;
	पूर्णांक page_order;
पूर्ण;

काष्ठा agp_bridge_driver अणु
	काष्ठा module *owner;
	स्थिर व्योम *aperture_sizes;
	पूर्णांक num_aperture_sizes;
	क्रमागत aper_माप_प्रकारype माप_प्रकारype;
	bool cant_use_aperture;
	bool needs_scratch_page;
	स्थिर काष्ठा gatt_mask *masks;
	पूर्णांक (*fetch_size)(व्योम);
	पूर्णांक (*configure)(व्योम);
	व्योम (*agp_enable)(काष्ठा agp_bridge_data *, u32);
	व्योम (*cleanup)(व्योम);
	व्योम (*tlb_flush)(काष्ठा agp_memory *);
	अचिन्हित दीर्घ (*mask_memory)(काष्ठा agp_bridge_data *, dma_addr_t, पूर्णांक);
	व्योम (*cache_flush)(व्योम);
	पूर्णांक (*create_gatt_table)(काष्ठा agp_bridge_data *);
	पूर्णांक (*मुक्त_gatt_table)(काष्ठा agp_bridge_data *);
	पूर्णांक (*insert_memory)(काष्ठा agp_memory *, off_t, पूर्णांक);
	पूर्णांक (*हटाओ_memory)(काष्ठा agp_memory *, off_t, पूर्णांक);
	काष्ठा agp_memory *(*alloc_by_type) (माप_प्रकार, पूर्णांक);
	व्योम (*मुक्त_by_type)(काष्ठा agp_memory *);
	काष्ठा page *(*agp_alloc_page)(काष्ठा agp_bridge_data *);
	पूर्णांक (*agp_alloc_pages)(काष्ठा agp_bridge_data *, काष्ठा agp_memory *, माप_प्रकार);
	व्योम (*agp_destroy_page)(काष्ठा page *, पूर्णांक flags);
	व्योम (*agp_destroy_pages)(काष्ठा agp_memory *);
	पूर्णांक (*agp_type_to_mask_type) (काष्ठा agp_bridge_data *, पूर्णांक);
पूर्ण;

काष्ठा agp_bridge_data अणु
	स्थिर काष्ठा agp_version *version;
	स्थिर काष्ठा agp_bridge_driver *driver;
	स्थिर काष्ठा vm_operations_काष्ठा *vm_ops;
	व्योम *previous_size;
	व्योम *current_size;
	व्योम *dev_निजी_data;
	काष्ठा pci_dev *dev;
	u32 __iomem *gatt_table;
	u32 *gatt_table_real;
	अचिन्हित दीर्घ scratch_page;
	काष्ठा page *scratch_page_page;
	dma_addr_t scratch_page_dma;
	अचिन्हित दीर्घ gart_bus_addr;
	अचिन्हित दीर्घ gatt_bus_addr;
	u32 mode;
	क्रमागत chipset_type type;
	अचिन्हित दीर्घ *key_list;
	atomic_t current_memory_agp;
	atomic_t agp_in_use;
	पूर्णांक max_memory_agp;	/* in number of pages */
	पूर्णांक aperture_size_idx;
	पूर्णांक capndx;
	पूर्णांक flags;
	अक्षर major_version;
	अक्षर minor_version;
	काष्ठा list_head list;
	u32 apbase_config;
	/* list of agp_memory mapped to the aperture */
	काष्ठा list_head mapped_list;
	spinlock_t mapped_lock;
पूर्ण;

#घोषणा KB(x)	((x) * 1024)
#घोषणा MB(x)	(KB (KB (x)))
#घोषणा GB(x)	(MB (KB (x)))

#घोषणा A_SIZE_8(x)	((काष्ठा aper_size_info_8 *) x)
#घोषणा A_SIZE_16(x)	((काष्ठा aper_size_info_16 *) x)
#घोषणा A_SIZE_32(x)	((काष्ठा aper_size_info_32 *) x)
#घोषणा A_SIZE_LVL2(x)	((काष्ठा aper_size_info_lvl2 *) x)
#घोषणा A_SIZE_FIX(x)	((काष्ठा aper_size_info_fixed *) x)
#घोषणा A_IDX8(bridge)	(A_SIZE_8((bridge)->driver->aperture_sizes) + i)
#घोषणा A_IDX16(bridge)	(A_SIZE_16((bridge)->driver->aperture_sizes) + i)
#घोषणा A_IDX32(bridge)	(A_SIZE_32((bridge)->driver->aperture_sizes) + i)
#घोषणा MAXKEY		(4096 * 32)

#घोषणा PGE_EMPTY(b, p)	(!(p) || (p) == (अचिन्हित दीर्घ) (b)->scratch_page)


काष्ठा agp_device_ids अणु
	अचिन्हित लघु device_id; /* first, to make table easier to पढ़ो */
	क्रमागत chipset_type chipset;
	स्थिर अक्षर *chipset_name;
	पूर्णांक (*chipset_setup) (काष्ठा pci_dev *pdev);	/* used to override generic */
पूर्ण;

/* Driver registration */
काष्ठा agp_bridge_data *agp_alloc_bridge(व्योम);
व्योम agp_put_bridge(काष्ठा agp_bridge_data *bridge);
पूर्णांक agp_add_bridge(काष्ठा agp_bridge_data *bridge);
व्योम agp_हटाओ_bridge(काष्ठा agp_bridge_data *bridge);

/* Frontend routines. */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
पूर्णांक agp_frontend_initialize(व्योम);
व्योम agp_frontend_cleanup(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक agp_frontend_initialize(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम agp_frontend_cleanup(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* Generic routines. */
व्योम agp_generic_enable(काष्ठा agp_bridge_data *bridge, u32 mode);
पूर्णांक agp_generic_create_gatt_table(काष्ठा agp_bridge_data *bridge);
पूर्णांक agp_generic_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge);
काष्ठा agp_memory *agp_create_memory(पूर्णांक scratch_pages);
पूर्णांक agp_generic_insert_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type);
पूर्णांक agp_generic_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type);
काष्ठा agp_memory *agp_generic_alloc_by_type(माप_प्रकार page_count, पूर्णांक type);
व्योम agp_generic_मुक्त_by_type(काष्ठा agp_memory *curr);
काष्ठा page *agp_generic_alloc_page(काष्ठा agp_bridge_data *bridge);
पूर्णांक agp_generic_alloc_pages(काष्ठा agp_bridge_data *agp_bridge,
			    काष्ठा agp_memory *memory, माप_प्रकार page_count);
व्योम agp_generic_destroy_page(काष्ठा page *page, पूर्णांक flags);
व्योम agp_generic_destroy_pages(काष्ठा agp_memory *memory);
व्योम agp_मुक्त_key(पूर्णांक key);
पूर्णांक agp_num_entries(व्योम);
u32 agp_collect_device_status(काष्ठा agp_bridge_data *bridge, u32 mode, u32 command);
व्योम agp_device_command(u32 command, bool agp_v3);
पूर्णांक agp_3_5_enable(काष्ठा agp_bridge_data *bridge);
व्योम global_cache_flush(व्योम);
व्योम get_agp_version(काष्ठा agp_bridge_data *bridge);
अचिन्हित दीर्घ agp_generic_mask_memory(काष्ठा agp_bridge_data *bridge,
				      dma_addr_t phys, पूर्णांक type);
पूर्णांक agp_generic_type_to_mask_type(काष्ठा agp_bridge_data *bridge,
				  पूर्णांक type);
काष्ठा agp_bridge_data *agp_generic_find_bridge(काष्ठा pci_dev *pdev);

/* generic functions क्रम user-populated AGP memory types */
काष्ठा agp_memory *agp_generic_alloc_user(माप_प्रकार page_count, पूर्णांक type);
व्योम agp_alloc_page_array(माप_प्रकार size, काष्ठा agp_memory *mem);
अटल अंतरभूत व्योम agp_मुक्त_page_array(काष्ठा agp_memory *mem)
अणु
	kvमुक्त(mem->pages);
पूर्ण


/* generic routines क्रम agp>=3 */
पूर्णांक agp3_generic_fetch_size(व्योम);
व्योम agp3_generic_tlbflush(काष्ठा agp_memory *mem);
पूर्णांक agp3_generic_configure(व्योम);
व्योम agp3_generic_cleanup(व्योम);

/* aperture sizes have been standardised since v3 */
#घोषणा AGP_GENERIC_SIZES_ENTRIES 11
बाह्य स्थिर काष्ठा aper_size_info_16 agp3_generic_sizes[];

बाह्य पूर्णांक agp_off;
बाह्य पूर्णांक agp_try_unsupported_boot;

दीर्घ compat_agp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

/* Chipset independent रेजिस्टरs (from AGP Spec) */
#घोषणा AGP_APBASE	0x10
#घोषणा AGP_APERTURE_BAR	0

#घोषणा AGPSTAT		0x4
#घोषणा AGPCMD		0x8
#घोषणा AGPNISTAT	0xc
#घोषणा AGPCTRL		0x10
#घोषणा AGPAPSIZE	0x14
#घोषणा AGPNEPG		0x16
#घोषणा AGPGARTLO	0x18
#घोषणा AGPGARTHI	0x1c
#घोषणा AGPNICMD	0x20

#घोषणा AGP_MAJOR_VERSION_SHIFT	(20)
#घोषणा AGP_MINOR_VERSION_SHIFT	(16)

#घोषणा AGPSTAT_RQ_DEPTH	(0xff000000)
#घोषणा AGPSTAT_RQ_DEPTH_SHIFT	24

#घोषणा AGPSTAT_CAL_MASK	(1<<12|1<<11|1<<10)
#घोषणा AGPSTAT_ARQSZ		(1<<15|1<<14|1<<13)
#घोषणा AGPSTAT_ARQSZ_SHIFT	13

#घोषणा AGPSTAT_SBA		(1<<9)
#घोषणा AGPSTAT_AGP_ENABLE	(1<<8)
#घोषणा AGPSTAT_FW		(1<<4)
#घोषणा AGPSTAT_MODE_3_0	(1<<3)

#घोषणा AGPSTAT2_1X		(1<<0)
#घोषणा AGPSTAT2_2X		(1<<1)
#घोषणा AGPSTAT2_4X		(1<<2)

#घोषणा AGPSTAT3_RSVD		(1<<2)
#घोषणा AGPSTAT3_8X		(1<<1)
#घोषणा AGPSTAT3_4X		(1)

#घोषणा AGPCTRL_APERENB		(1<<8)
#घोषणा AGPCTRL_GTLBEN		(1<<7)

#घोषणा AGP2_RESERVED_MASK 0x00fffcc8
#घोषणा AGP3_RESERVED_MASK 0x00ff00c4

#घोषणा AGP_ERRATA_FASTWRITES 1<<0
#घोषणा AGP_ERRATA_SBA	 1<<1
#घोषणा AGP_ERRATA_1X 1<<2

#पूर्ण_अगर	/* _AGP_BACKEND_PRIV_H */
