<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * memory.h
 *
 * Memory reservation and inक्रमmation.
 *
 * Copyright (c) 2005, Keir Fraser <keir@xensource.com>
 */

#अगर_अघोषित __XEN_PUBLIC_MEMORY_H__
#घोषणा __XEN_PUBLIC_MEMORY_H__

#समावेश <linux/spinlock.h>

/*
 * Increase or decrease the specअगरied करोमुख्य's memory reservation. Returns a
 * -ve errcode on failure, or the # extents successfully allocated or मुक्तd.
 * arg == addr of काष्ठा xen_memory_reservation.
 */
#घोषणा XENMEM_increase_reservation 0
#घोषणा XENMEM_decrease_reservation 1
#घोषणा XENMEM_populate_physmap     6
काष्ठा xen_memory_reservation अणु

    /*
     * XENMEM_increase_reservation:
     *   OUT: MFN (*not* GMFN) bases of extents that were allocated
     * XENMEM_decrease_reservation:
     *   IN:  GMFN bases of extents to मुक्त
     * XENMEM_populate_physmap:
     *   IN:  GPFN bases of extents to populate with memory
     *   OUT: GMFN bases of extents that were allocated
     *   (NB. This command also updates the mach_to_phys translation table)
     */
    GUEST_HANDLE(xen_pfn_t) extent_start;

    /* Number of extents, and size/alignment of each (2^extent_order pages). */
    xen_uदीर्घ_t  nr_extents;
    अचिन्हित पूर्णांक   extent_order;

    /*
     * Maximum # bits addressable by the user of the allocated region (e.g.,
     * I/O devices often have a 32-bit limitation even in 64-bit प्रणालीs). If
     * zero then the user has no addressing restriction.
     * This field is not used by XENMEM_decrease_reservation.
     */
    अचिन्हित पूर्णांक   address_bits;

    /*
     * Doमुख्य whose reservation is being changed.
     * Unprivileged करोमुख्यs can specअगरy only DOMID_SELF.
     */
    करोmid_t        करोmid;

पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_memory_reservation);

/*
 * An atomic exchange of memory pages. If वापस code is zero then
 * @out.extent_list provides GMFNs of the newly-allocated memory.
 * Returns zero on complete success, otherwise a negative error code.
 * On complete success then always @nr_exchanged == @in.nr_extents.
 * On partial success @nr_exchanged indicates how much work was करोne.
 */
#घोषणा XENMEM_exchange             11
काष्ठा xen_memory_exchange अणु
    /*
     * [IN] Details of memory extents to be exchanged (GMFN bases).
     * Note that @in.address_bits is ignored and unused.
     */
    काष्ठा xen_memory_reservation in;

    /*
     * [IN/OUT] Details of new memory extents.
     * We require that:
     *  1. @in.करोmid == @out.करोmid
     *  2. @in.nr_extents  << @in.extent_order ==
     *     @out.nr_extents << @out.extent_order
     *  3. @in.extent_start and @out.extent_start lists must not overlap
     *  4. @out.extent_start lists GPFN bases to be populated
     *  5. @out.extent_start is overwritten with allocated GMFN bases
     */
    काष्ठा xen_memory_reservation out;

    /*
     * [OUT] Number of input extents that were successfully exchanged:
     *  1. The first @nr_exchanged input extents were successfully
     *     deallocated.
     *  2. The corresponding first entries in the output extent list correctly
     *     indicate the GMFNs that were successfully exchanged.
     *  3. All other input and output extents are untouched.
     *  4. If not all input exents are exchanged then the वापस code of this
     *     command will be non-zero.
     *  5. THIS FIELD MUST BE INITIALISED TO ZERO BY THE CALLER!
     */
    xen_uदीर्घ_t nr_exchanged;
पूर्ण;

DEFINE_GUEST_HANDLE_STRUCT(xen_memory_exchange);
/*
 * Returns the maximum machine frame number of mapped RAM in this प्रणाली.
 * This command always succeeds (it never वापसs an error code).
 * arg == शून्य.
 */
#घोषणा XENMEM_maximum_ram_page     2

/*
 * Returns the current or maximum memory reservation, in pages, of the
 * specअगरied करोमुख्य (may be DOMID_SELF). Returns -ve errcode on failure.
 * arg == addr of करोmid_t.
 */
#घोषणा XENMEM_current_reservation  3
#घोषणा XENMEM_maximum_reservation  4

/*
 * Returns a list of MFN bases of 2MB extents comprising the machine_to_phys
 * mapping table. Architectures which करो not have a m2p table करो not implement
 * this command.
 * arg == addr of xen_machphys_mfn_list_t.
 */
#घोषणा XENMEM_machphys_mfn_list    5
काष्ठा xen_machphys_mfn_list अणु
    /*
     * Size of the 'extent_start' array. Fewer entries will be filled अगर the
     * machphys table is smaller than max_extents * 2MB.
     */
    अचिन्हित पूर्णांक max_extents;

    /*
     * Poपूर्णांकer to buffer to fill with list of extent starts. If there are
     * any large discontiguities in the machine address space, 2MB gaps in
     * the machphys table will be represented by an MFN base of zero.
     */
    GUEST_HANDLE(xen_pfn_t) extent_start;

    /*
     * Number of extents written to the above array. This will be smaller
     * than 'max_extents' अगर the machphys table is smaller than max_e * 2MB.
     */
    अचिन्हित पूर्णांक nr_extents;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_machphys_mfn_list);

/*
 * Returns the location in भव address space of the machine_to_phys
 * mapping table. Architectures which करो not have a m2p table, or which करो not
 * map it by शेष पूर्णांकo guest address space, करो not implement this command.
 * arg == addr of xen_machphys_mapping_t.
 */
#घोषणा XENMEM_machphys_mapping     12
काष्ठा xen_machphys_mapping अणु
    xen_uदीर्घ_t v_start, v_end; /* Start and end भव addresses.   */
    xen_uदीर्घ_t max_mfn;        /* Maximum MFN that can be looked up. */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_machphys_mapping_t);

#घोषणा XENMAPSPACE_shared_info  0 /* shared info page */
#घोषणा XENMAPSPACE_grant_table  1 /* grant table page */
#घोषणा XENMAPSPACE_gmfn         2 /* GMFN */
#घोषणा XENMAPSPACE_gmfn_range   3 /* GMFN range, XENMEM_add_to_physmap only. */
#घोषणा XENMAPSPACE_gmfn_क्रमeign 4 /* GMFN from another करोm,
				    * XENMEM_add_to_physmap_range only.
				    */
#घोषणा XENMAPSPACE_dev_mmio     5 /* device mmio region */

/*
 * Sets the GPFN at which a particular page appears in the specअगरied guest's
 * pseuकरोphysical address space.
 * arg == addr of xen_add_to_physmap_t.
 */
#घोषणा XENMEM_add_to_physmap      7
काष्ठा xen_add_to_physmap अणु
    /* Which करोमुख्य to change the mapping क्रम. */
    करोmid_t करोmid;

    /* Number of pages to go through क्रम gmfn_range */
    uपूर्णांक16_t    size;

    /* Source mapping space. */
    अचिन्हित पूर्णांक space;

    /* Index पूर्णांकo source mapping space. */
    xen_uदीर्घ_t idx;

    /* GPFN where the source mapping page should appear. */
    xen_pfn_t gpfn;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_add_to_physmap);

/*** REMOVED ***/
/*#घोषणा XENMEM_translate_gpfn_list  8*/

#घोषणा XENMEM_add_to_physmap_range 23
काष्ठा xen_add_to_physmap_range अणु
    /* IN */
    /* Which करोमुख्य to change the mapping क्रम. */
    करोmid_t करोmid;
    uपूर्णांक16_t space; /* => क्रमागत phys_map_space */

    /* Number of pages to go through */
    uपूर्णांक16_t size;
    करोmid_t क्रमeign_करोmid; /* IFF gmfn_क्रमeign */

    /* Indexes पूर्णांकo space being mapped. */
    GUEST_HANDLE(xen_uदीर्घ_t) idxs;

    /* GPFN in करोmid where the source mapping page should appear. */
    GUEST_HANDLE(xen_pfn_t) gpfns;

    /* OUT */

    /* Per index error code. */
    GUEST_HANDLE(पूर्णांक) errs;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_add_to_physmap_range);

/*
 * Returns the pseuकरो-physical memory map as it was when the करोमुख्य
 * was started (specअगरied by XENMEM_set_memory_map).
 * arg == addr of काष्ठा xen_memory_map.
 */
#घोषणा XENMEM_memory_map           9
काष्ठा xen_memory_map अणु
    /*
     * On call the number of entries which can be stored in buffer. On
     * वापस the number of entries which have been stored in
     * buffer.
     */
    अचिन्हित पूर्णांक nr_entries;

    /*
     * Entries in the buffer are in the same क्रमmat as वापसed by the
     * BIOS INT 0x15 EAX=0xE820 call.
     */
    GUEST_HANDLE(व्योम) buffer;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_memory_map);

/*
 * Returns the real physical memory map. Passes the same काष्ठाure as
 * XENMEM_memory_map.
 * arg == addr of काष्ठा xen_memory_map.
 */
#घोषणा XENMEM_machine_memory_map   10


/*
 * Unmaps the page appearing at a particular GPFN from the specअगरied guest's
 * pseuकरोphysical address space.
 * arg == addr of xen_हटाओ_from_physmap_t.
 */
#घोषणा XENMEM_हटाओ_from_physmap      15
काष्ठा xen_हटाओ_from_physmap अणु
    /* Which करोमुख्य to change the mapping क्रम. */
    करोmid_t करोmid;

    /* GPFN of the current mapping of the page. */
    xen_pfn_t gpfn;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_हटाओ_from_physmap);

/*
 * Get the pages क्रम a particular guest resource, so that they can be
 * mapped directly by a tools करोमुख्य.
 */
#घोषणा XENMEM_acquire_resource 28
काष्ठा xen_mem_acquire_resource अणु
    /* IN - The करोमुख्य whose resource is to be mapped */
    करोmid_t करोmid;
    /* IN - the type of resource */
    uपूर्णांक16_t type;

#घोषणा XENMEM_resource_ioreq_server 0
#घोषणा XENMEM_resource_grant_table 1

    /*
     * IN - a type-specअगरic resource identअगरier, which must be zero
     *      unless stated otherwise.
     *
     * type == XENMEM_resource_ioreq_server -> id == ioreq server id
     * type == XENMEM_resource_grant_table -> id defined below
     */
    uपूर्णांक32_t id;

#घोषणा XENMEM_resource_grant_table_id_shared 0
#घोषणा XENMEM_resource_grant_table_id_status 1

    /* IN/OUT - As an IN parameter number of frames of the resource
     *          to be mapped. However, अगर the specअगरied value is 0 and
     *          frame_list is शून्य then this field will be set to the
     *          maximum value supported by the implementation on वापस.
     */
    uपूर्णांक32_t nr_frames;
    /*
     * OUT - Must be zero on entry. On वापस this may contain a bitwise
     *       OR of the following values.
     */
    uपूर्णांक32_t flags;

    /* The resource pages have been asचिन्हित to the calling करोमुख्य */
#घोषणा _XENMEM_rsrc_acq_caller_owned 0
#घोषणा XENMEM_rsrc_acq_caller_owned (1u << _XENMEM_rsrc_acq_caller_owned)

    /*
     * IN - the index of the initial frame to be mapped. This parameter
     *      is ignored अगर nr_frames is 0.
     */
    uपूर्णांक64_t frame;

#घोषणा XENMEM_resource_ioreq_server_frame_bufioreq 0
#घोषणा XENMEM_resource_ioreq_server_frame_ioreq(n) (1 + (n))

    /*
     * IN/OUT - If the tools करोमुख्य is PV then, upon वापस, frame_list
     *          will be populated with the MFNs of the resource.
     *          If the tools करोमुख्य is HVM then it is expected that, on
     *          entry, frame_list will be populated with a list of GFNs
     *          that will be mapped to the MFNs of the resource.
     *          If -EIO is वापसed then the frame_list has only been
     *          partially mapped and it is up to the caller to unmap all
     *          the GFNs.
     *          This parameter may be शून्य अगर nr_frames is 0.
     */
    GUEST_HANDLE(xen_pfn_t) frame_list;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_mem_acquire_resource);

#पूर्ण_अगर /* __XEN_PUBLIC_MEMORY_H__ */
