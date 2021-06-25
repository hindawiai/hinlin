<शैली गुरु>
/******************************************************************************
 * grant_table.h
 *
 * Interface क्रम granting क्रमeign access to page frames, and receiving
 * page-ownership transfers.
 *
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
 * Copyright (c) 2004, K A Fraser
 */

#अगर_अघोषित __XEN_PUBLIC_GRANT_TABLE_H__
#घोषणा __XEN_PUBLIC_GRANT_TABLE_H__

#समावेश <xen/पूर्णांकerface/xen.h>

/***********************************
 * GRANT TABLE REPRESENTATION
 */

/* Some rough guidelines on accessing and updating grant-table entries
 * in a concurrency-safe manner. For more inक्रमmation, Linux contains a
 * reference implementation क्रम guest OSes (arch/xen/kernel/grant_table.c).
 *
 * NB. WMB is a no-op on current-generation x86 processors. However, a
 *     compiler barrier will still be required.
 *
 * Introducing a valid entry पूर्णांकo the grant table:
 *  1. Write ent->करोmid.
 *  2. Write ent->frame:
 *      GTF_permit_access:   Frame to which access is permitted.
 *      GTF_accept_transfer: Pseuकरो-phys frame slot being filled by new
 *                           frame, or zero अगर none.
 *  3. Write memory barrier (WMB).
 *  4. Write ent->flags, inc. valid type.
 *
 * Invalidating an unused GTF_permit_access entry:
 *  1. flags = ent->flags.
 *  2. Observe that !(flags & (GTF_पढ़ोing|GTF_writing)).
 *  3. Check result of SMP-safe CMPXCHG(&ent->flags, flags, 0).
 *  NB. No need क्रम WMB as reuse of entry is control-dependent on success of
 *      step 3, and all architectures guarantee ordering of ctrl-dep ग_लिखोs.
 *
 * Invalidating an in-use GTF_permit_access entry:
 *  This cannot be करोne directly. Request assistance from the करोमुख्य controller
 *  which can set a समयout on the use of a grant entry and take necessary
 *  action. (NB. This is not yet implemented!).
 *
 * Invalidating an unused GTF_accept_transfer entry:
 *  1. flags = ent->flags.
 *  2. Observe that !(flags & GTF_transfer_committed). [*]
 *  3. Check result of SMP-safe CMPXCHG(&ent->flags, flags, 0).
 *  NB. No need क्रम WMB as reuse of entry is control-dependent on success of
 *      step 3, and all architectures guarantee ordering of ctrl-dep ग_लिखोs.
 *  [*] If GTF_transfer_committed is set then the grant entry is 'committed'.
 *      The guest must /not/ modअगरy the grant entry until the address of the
 *      transferred frame is written. It is safe क्रम the guest to spin रुकोing
 *      क्रम this to occur (detect by observing GTF_transfer_completed in
 *      ent->flags).
 *
 * Invalidating a committed GTF_accept_transfer entry:
 *  1. Wait क्रम (ent->flags & GTF_transfer_completed).
 *
 * Changing a GTF_permit_access from writable to पढ़ो-only:
 *  Use SMP-safe CMPXCHG to set GTF_पढ़ोonly, जबतक checking !GTF_writing.
 *
 * Changing a GTF_permit_access from पढ़ो-only to writable:
 *  Use SMP-safe bit-setting inकाष्ठाion.
 */

/*
 * Reference to a grant entry in a specअगरied करोमुख्य's grant table.
 */
प्रकार uपूर्णांक32_t grant_ref_t;

/*
 * A grant table comprises a packed array of grant entries in one or more
 * page frames shared between Xen and a guest.
 * [XEN]: This field is written by Xen and पढ़ो by the sharing guest.
 * [GST]: This field is written by the guest and पढ़ो by Xen.
 */

/*
 * Version 1 of the grant table entry काष्ठाure is मुख्यtained purely
 * क्रम backwards compatibility.  New guests should use version 2.
 */
काष्ठा grant_entry_v1 अणु
    /* GTF_xxx: various type and flag inक्रमmation.  [XEN,GST] */
    uपूर्णांक16_t flags;
    /* The करोमुख्य being granted क्रमeign privileges. [GST] */
    करोmid_t  करोmid;
    /*
     * GTF_permit_access: Frame that @करोmid is allowed to map and access. [GST]
     * GTF_accept_transfer: Frame whose ownership transferred by @करोmid. [XEN]
     */
    uपूर्णांक32_t frame;
पूर्ण;

/*
 * Type of grant entry.
 *  GTF_invalid: This grant entry grants no privileges.
 *  GTF_permit_access: Allow @करोmid to map/access @frame.
 *  GTF_accept_transfer: Allow @करोmid to transfer ownership of one page frame
 *                       to this guest. Xen ग_लिखोs the page number to @frame.
 *  GTF_transitive: Allow @करोmid to transitively access a subrange of
 *                  @trans_grant in @trans_करोmid.  No mappings are allowed.
 */
#घोषणा GTF_invalid         (0U<<0)
#घोषणा GTF_permit_access   (1U<<0)
#घोषणा GTF_accept_transfer (2U<<0)
#घोषणा GTF_transitive      (3U<<0)
#घोषणा GTF_type_mask       (3U<<0)

/*
 * Subflags क्रम GTF_permit_access.
 *  GTF_पढ़ोonly: Restrict @करोmid to पढ़ो-only mappings and accesses. [GST]
 *  GTF_पढ़ोing: Grant entry is currently mapped क्रम पढ़ोing by @करोmid. [XEN]
 *  GTF_writing: Grant entry is currently mapped क्रम writing by @करोmid. [XEN]
 *  GTF_sub_page: Grant access to only a subrange of the page.  @करोmid
 *                will only be allowed to copy from the grant, and not
 *                map it. [GST]
 */
#घोषणा _GTF_पढ़ोonly       (2)
#घोषणा GTF_पढ़ोonly        (1U<<_GTF_पढ़ोonly)
#घोषणा _GTF_पढ़ोing        (3)
#घोषणा GTF_पढ़ोing         (1U<<_GTF_पढ़ोing)
#घोषणा _GTF_writing        (4)
#घोषणा GTF_writing         (1U<<_GTF_writing)
#घोषणा _GTF_sub_page       (8)
#घोषणा GTF_sub_page        (1U<<_GTF_sub_page)

/*
 * Subflags क्रम GTF_accept_transfer:
 *  GTF_transfer_committed: Xen sets this flag to indicate that it is committed
 *      to transferring ownership of a page frame. When a guest sees this flag
 *      it must /not/ modअगरy the grant entry until GTF_transfer_completed is
 *      set by Xen.
 *  GTF_transfer_completed: It is safe क्रम the guest to spin-रुको on this flag
 *      after पढ़ोing GTF_transfer_committed. Xen will always ग_लिखो the frame
 *      address, followed by ORing this flag, in a समयly manner.
 */
#घोषणा _GTF_transfer_committed (2)
#घोषणा GTF_transfer_committed  (1U<<_GTF_transfer_committed)
#घोषणा _GTF_transfer_completed (3)
#घोषणा GTF_transfer_completed  (1U<<_GTF_transfer_completed)

/*
 * Version 2 grant table entries.  These fulfil the same role as
 * version 1 entries, but can represent more complicated operations.
 * Any given करोमुख्य will have either a version 1 or a version 2 table,
 * and every entry in the table will be the same version.
 *
 * The पूर्णांकerface by which करोमुख्यs use grant references करोes not depend
 * on the grant table version in use by the other करोमुख्य.
 */

/*
 * Version 1 and version 2 grant entries share a common prefix.  The
 * fields of the prefix are करोcumented as part of काष्ठा
 * grant_entry_v1.
 */
काष्ठा grant_entry_header अणु
    uपूर्णांक16_t flags;
    करोmid_t  करोmid;
पूर्ण;

/*
 * Version 2 of the grant entry काष्ठाure, here is a जोड़ because three
 * dअगरferent types are suppotted: full_page, sub_page and transitive.
 */
जोड़ grant_entry_v2 अणु
    काष्ठा grant_entry_header hdr;

    /*
     * This member is used क्रम V1-style full page grants, where either:
     *
     * -- hdr.type is GTF_accept_transfer, or
     * -- hdr.type is GTF_permit_access and GTF_sub_page is not set.
     *
     * In that हाल, the frame field has the same semantics as the
     * field of the same name in the V1 entry काष्ठाure.
     */
    काष्ठा अणु
	काष्ठा grant_entry_header hdr;
	uपूर्णांक32_t pad0;
	uपूर्णांक64_t frame;
    पूर्ण full_page;

    /*
     * If the grant type is GTF_grant_access and GTF_sub_page is set,
     * @करोmid is allowed to access bytes [@page_off,@page_off+@length)
     * in frame @frame.
     */
    काष्ठा अणु
	काष्ठा grant_entry_header hdr;
	uपूर्णांक16_t page_off;
	uपूर्णांक16_t length;
	uपूर्णांक64_t frame;
    पूर्ण sub_page;

    /*
     * If the grant is GTF_transitive, @करोmid is allowed to use the
     * grant @gref in करोमुख्य @trans_करोmid, as अगर it was the local
     * करोमुख्य.  Obviously, the transitive access must be compatible
     * with the original grant.
     */
    काष्ठा अणु
	काष्ठा grant_entry_header hdr;
	करोmid_t trans_करोmid;
	uपूर्णांक16_t pad0;
	grant_ref_t gref;
    पूर्ण transitive;

    uपूर्णांक32_t __spacer[4]; /* Pad to a घातer of two */
पूर्ण;

प्रकार uपूर्णांक16_t grant_status_t;

/***********************************
 * GRANT TABLE QUERIES AND USES
 */

/*
 * Handle to track a mapping created via a grant reference.
 */
प्रकार uपूर्णांक32_t grant_handle_t;

/*
 * GNTTABOP_map_grant_ref: Map the grant entry (<करोm>,<ref>) क्रम access
 * by devices and/or host CPUs. If successful, <handle> is a tracking number
 * that must be presented later to destroy the mapping(s). On error, <handle>
 * is a negative status code.
 * NOTES:
 *  1. If GNTMAP_device_map is specअगरied then <dev_bus_addr> is the address
 *     via which I/O devices may access the granted frame.
 *  2. If GNTMAP_host_map is specअगरied then a mapping will be added at
 *     either a host भव address in the current address space, or at
 *     a PTE at the specअगरied machine address.  The type of mapping to
 *     perक्रमm is selected through the GNTMAP_contains_pte flag, and the
 *     address is specअगरied in <host_addr>.
 *  3. Mappings should only be destroyed via GNTTABOP_unmap_grant_ref. If a
 *     host mapping is destroyed by other means then it is *NOT* guaranteed
 *     to be accounted to the correct grant reference!
 */
#घोषणा GNTTABOP_map_grant_ref        0
काष्ठा gnttab_map_grant_ref अणु
    /* IN parameters. */
    uपूर्णांक64_t host_addr;
    uपूर्णांक32_t flags;               /* GNTMAP_* */
    grant_ref_t ref;
    करोmid_t  करोm;
    /* OUT parameters. */
    पूर्णांक16_t  status;              /* GNTST_* */
    grant_handle_t handle;
    uपूर्णांक64_t dev_bus_addr;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_map_grant_ref);

/*
 * GNTTABOP_unmap_grant_ref: Destroy one or more grant-reference mappings
 * tracked by <handle>. If <host_addr> or <dev_bus_addr> is zero, that
 * field is ignored. If non-zero, they must refer to a device/host mapping
 * that is tracked by <handle>
 * NOTES:
 *  1. The call may fail in an undefined manner अगर either mapping is not
 *     tracked by <handle>.
 *  3. After executing a batch of unmaps, it is guaranteed that no stale
 *     mappings will reमुख्य in the device or host TLBs.
 */
#घोषणा GNTTABOP_unmap_grant_ref      1
काष्ठा gnttab_unmap_grant_ref अणु
    /* IN parameters. */
    uपूर्णांक64_t host_addr;
    uपूर्णांक64_t dev_bus_addr;
    grant_handle_t handle;
    /* OUT parameters. */
    पूर्णांक16_t  status;              /* GNTST_* */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_unmap_grant_ref);

/*
 * GNTTABOP_setup_table: Set up a grant table क्रम <करोm> comprising at least
 * <nr_frames> pages. The frame addresses are written to the <frame_list>.
 * Only <nr_frames> addresses are written, even अगर the table is larger.
 * NOTES:
 *  1. <करोm> may be specअगरied as DOMID_SELF.
 *  2. Only a sufficiently-privileged करोमुख्य may specअगरy <करोm> != DOMID_SELF.
 *  3. Xen may not support more than a single grant-table page per करोमुख्य.
 */
#घोषणा GNTTABOP_setup_table          2
काष्ठा gnttab_setup_table अणु
    /* IN parameters. */
    करोmid_t  करोm;
    uपूर्णांक32_t nr_frames;
    /* OUT parameters. */
    पूर्णांक16_t  status;              /* GNTST_* */
    GUEST_HANDLE(xen_pfn_t) frame_list;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_setup_table);

/*
 * GNTTABOP_dump_table: Dump the contents of the grant table to the
 * xen console. Debugging use only.
 */
#घोषणा GNTTABOP_dump_table           3
काष्ठा gnttab_dump_table अणु
    /* IN parameters. */
    करोmid_t करोm;
    /* OUT parameters. */
    पूर्णांक16_t status;               /* GNTST_* */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_dump_table);

/*
 * GNTTABOP_transfer_grant_ref: Transfer <frame> to a क्रमeign करोमुख्य. The
 * क्रमeign करोमुख्य has previously रेजिस्टरed its पूर्णांकerest in the transfer via
 * <करोmid, ref>.
 *
 * Note that, even अगर the transfer fails, the specअगरied page no दीर्घer beदीर्घs
 * to the calling करोमुख्य *unless* the error is GNTST_bad_page.
 */
#घोषणा GNTTABOP_transfer                4
काष्ठा gnttab_transfer अणु
    /* IN parameters. */
    xen_pfn_t mfn;
    करोmid_t       करोmid;
    grant_ref_t   ref;
    /* OUT parameters. */
    पूर्णांक16_t       status;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_transfer);

/*
 * GNTTABOP_copy: Hypervisor based copy
 * source and destinations can be eithers MFNs or, क्रम क्रमeign करोमुख्यs,
 * grant references. the क्रमeign करोमुख्य has to grant पढ़ो/ग_लिखो access
 * in its grant table.
 *
 * The flags specअगरy what type source and destinations are (either MFN
 * or grant reference).
 *
 * Note that this can also be used to copy data between two करोमुख्यs
 * via a third party अगर the source and destination करोमुख्यs had previously
 * grant appropriate access to their pages to the third party.
 *
 * source_offset specअगरies an offset in the source frame, dest_offset
 * the offset in the target frame and  len specअगरies the number of
 * bytes to be copied.
 */

#घोषणा _GNTCOPY_source_gref      (0)
#घोषणा GNTCOPY_source_gref       (1<<_GNTCOPY_source_gref)
#घोषणा _GNTCOPY_dest_gref        (1)
#घोषणा GNTCOPY_dest_gref         (1<<_GNTCOPY_dest_gref)

#घोषणा GNTTABOP_copy                 5
काष्ठा gnttab_copy अणु
	/* IN parameters. */
	काष्ठा अणु
		जोड़ अणु
			grant_ref_t ref;
			xen_pfn_t   gmfn;
		पूर्ण u;
		करोmid_t  करोmid;
		uपूर्णांक16_t offset;
	पूर्ण source, dest;
	uपूर्णांक16_t      len;
	uपूर्णांक16_t      flags;          /* GNTCOPY_* */
	/* OUT parameters. */
	पूर्णांक16_t       status;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_copy);

/*
 * GNTTABOP_query_size: Query the current and maximum sizes of the shared
 * grant table.
 * NOTES:
 *  1. <करोm> may be specअगरied as DOMID_SELF.
 *  2. Only a sufficiently-privileged करोमुख्य may specअगरy <करोm> != DOMID_SELF.
 */
#घोषणा GNTTABOP_query_size           6
काष्ठा gnttab_query_size अणु
    /* IN parameters. */
    करोmid_t  करोm;
    /* OUT parameters. */
    uपूर्णांक32_t nr_frames;
    uपूर्णांक32_t max_nr_frames;
    पूर्णांक16_t  status;              /* GNTST_* */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_query_size);

/*
 * GNTTABOP_unmap_and_replace: Destroy one or more grant-reference mappings
 * tracked by <handle> but atomically replace the page table entry with one
 * poपूर्णांकing to the machine address under <new_addr>.  <new_addr> will be
 * redirected to the null entry.
 * NOTES:
 *  1. The call may fail in an undefined manner अगर either mapping is not
 *     tracked by <handle>.
 *  2. After executing a batch of unmaps, it is guaranteed that no stale
 *     mappings will reमुख्य in the device or host TLBs.
 */
#घोषणा GNTTABOP_unmap_and_replace    7
काष्ठा gnttab_unmap_and_replace अणु
    /* IN parameters. */
    uपूर्णांक64_t host_addr;
    uपूर्णांक64_t new_addr;
    grant_handle_t handle;
    /* OUT parameters. */
    पूर्णांक16_t  status;              /* GNTST_* */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_unmap_and_replace);

/*
 * GNTTABOP_set_version: Request a particular version of the grant
 * table shared table काष्ठाure.  This operation can only be perक्रमmed
 * once in any given करोमुख्य.  It must be perक्रमmed beक्रमe any grants
 * are activated; otherwise, the करोमुख्य will be stuck with version 1.
 * The only defined versions are 1 and 2.
 */
#घोषणा GNTTABOP_set_version          8
काष्ठा gnttab_set_version अणु
    /* IN parameters */
    uपूर्णांक32_t version;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_set_version);

/*
 * GNTTABOP_get_status_frames: Get the list of frames used to store grant
 * status क्रम <करोm>. In grant क्रमmat version 2, the status is separated
 * from the other shared grant fields to allow more efficient synchronization
 * using barriers instead of atomic cmpexch operations.
 * <nr_frames> specअगरy the size of vector <frame_list>.
 * The frame addresses are वापसed in the <frame_list>.
 * Only <nr_frames> addresses are वापसed, even अगर the table is larger.
 * NOTES:
 *  1. <करोm> may be specअगरied as DOMID_SELF.
 *  2. Only a sufficiently-privileged करोमुख्य may specअगरy <करोm> != DOMID_SELF.
 */
#घोषणा GNTTABOP_get_status_frames     9
काष्ठा gnttab_get_status_frames अणु
    /* IN parameters. */
    uपूर्णांक32_t nr_frames;
    करोmid_t  करोm;
    /* OUT parameters. */
    पूर्णांक16_t  status;              /* GNTST_* */
    GUEST_HANDLE(uपूर्णांक64_t) frame_list;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_get_status_frames);

/*
 * GNTTABOP_get_version: Get the grant table version which is in
 * effect क्रम करोमुख्य <करोm>.
 */
#घोषणा GNTTABOP_get_version          10
काष्ठा gnttab_get_version अणु
    /* IN parameters */
    करोmid_t करोm;
    uपूर्णांक16_t pad;
    /* OUT parameters */
    uपूर्णांक32_t version;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_get_version);

/*
 * Issue one or more cache मुख्यtenance operations on a portion of a
 * page granted to the calling करोमुख्य by a क्रमeign करोमुख्य.
 */
#घोषणा GNTTABOP_cache_flush          12
काष्ठा gnttab_cache_flush अणु
    जोड़ अणु
        uपूर्णांक64_t dev_bus_addr;
        grant_ref_t ref;
    पूर्ण a;
    uपूर्णांक16_t offset;   /* offset from start of grant */
    uपूर्णांक16_t length;   /* size within the grant */
#घोषणा GNTTAB_CACHE_CLEAN          (1<<0)
#घोषणा GNTTAB_CACHE_INVAL          (1<<1)
#घोषणा GNTTAB_CACHE_SOURCE_GREF    (1<<31)
    uपूर्णांक32_t op;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(gnttab_cache_flush);

/*
 * Bitfield values क्रम update_pin_status.flags.
 */
 /* Map the grant entry क्रम access by I/O devices. */
#घोषणा _GNTMAP_device_map      (0)
#घोषणा GNTMAP_device_map       (1<<_GNTMAP_device_map)
 /* Map the grant entry क्रम access by host CPUs. */
#घोषणा _GNTMAP_host_map        (1)
#घोषणा GNTMAP_host_map         (1<<_GNTMAP_host_map)
 /* Accesses to the granted frame will be restricted to पढ़ो-only access. */
#घोषणा _GNTMAP_पढ़ोonly        (2)
#घोषणा GNTMAP_पढ़ोonly         (1<<_GNTMAP_पढ़ोonly)
 /*
  * GNTMAP_host_map subflag:
  *  0 => The host mapping is usable only by the guest OS.
  *  1 => The host mapping is usable by guest OS + current application.
  */
#घोषणा _GNTMAP_application_map (3)
#घोषणा GNTMAP_application_map  (1<<_GNTMAP_application_map)

 /*
  * GNTMAP_contains_pte subflag:
  *  0 => This map request contains a host भव address.
  *  1 => This map request contains the machine addess of the PTE to update.
  */
#घोषणा _GNTMAP_contains_pte    (4)
#घोषणा GNTMAP_contains_pte     (1<<_GNTMAP_contains_pte)

/*
 * Bits to be placed in guest kernel available PTE bits (architecture
 * dependent; only supported when XENFEAT_gnttab_map_avail_bits is set).
 */
#घोषणा _GNTMAP_guest_avail0    (16)
#घोषणा GNTMAP_guest_avail_mask ((uपूर्णांक32_t)~0 << _GNTMAP_guest_avail0)

/*
 * Values क्रम error status वापसs. All errors are -ve.
 */
#घोषणा GNTST_okay             (0)  /* Normal वापस.                        */
#घोषणा GNTST_general_error    (-1) /* General undefined error.              */
#घोषणा GNTST_bad_करोमुख्य       (-2) /* Unrecognsed करोमुख्य id.                */
#घोषणा GNTST_bad_gntref       (-3) /* Unrecognised or inappropriate gntref. */
#घोषणा GNTST_bad_handle       (-4) /* Unrecognised or inappropriate handle. */
#घोषणा GNTST_bad_virt_addr    (-5) /* Inappropriate भव address to map. */
#घोषणा GNTST_bad_dev_addr     (-6) /* Inappropriate device address to unmap.*/
#घोषणा GNTST_no_device_space  (-7) /* Out of space in I/O MMU.              */
#घोषणा GNTST_permission_denied (-8) /* Not enough privilege क्रम operation.  */
#घोषणा GNTST_bad_page         (-9) /* Specअगरied page was invalid क्रम op.    */
#घोषणा GNTST_bad_copy_arg    (-10) /* copy arguments cross page boundary.   */
#घोषणा GNTST_address_too_big (-11) /* transfer page address too large.      */
#घोषणा GNTST_eagain          (-12) /* Operation not करोne; try again.        */

#घोषणा GNTTABOP_error_msgs अणु                   \
    "okay",                                     \
    "undefined error",                          \
    "unrecognised domain id",                   \
    "invalid grant reference",                  \
    "invalid mapping handle",                   \
    "invalid virtual address",                  \
    "invalid device address",                   \
    "no spare translation slot in the I/O MMU", \
    "permission denied",                        \
    "bad page",                                 \
    "copy arguments cross page boundary",       \
    "page address size too large",              \
    "operation not done; try again"             \
पूर्ण

#पूर्ण_अगर /* __XEN_PUBLIC_GRANT_TABLE_H__ */
