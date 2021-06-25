<शैली गुरु>
/* amdgpu_drm.h -- Public header क्रम the amdgpu driver -*- linux-c -*-
 *
 * Copyright 2000 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Fremont, Calअगरornia.
 * Copyright 2002 Tungsten Graphics, Inc., Cedar Park, Texas.
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Kevin E. Martin <martin@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 *    Keith Whitwell <keith@tungstengraphics.com>
 */

#अगर_अघोषित __AMDGPU_DRM_H__
#घोषणा __AMDGPU_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_AMDGPU_GEM_CREATE		0x00
#घोषणा DRM_AMDGPU_GEM_MMAP		0x01
#घोषणा DRM_AMDGPU_CTX			0x02
#घोषणा DRM_AMDGPU_BO_LIST		0x03
#घोषणा DRM_AMDGPU_CS			0x04
#घोषणा DRM_AMDGPU_INFO			0x05
#घोषणा DRM_AMDGPU_GEM_METADATA		0x06
#घोषणा DRM_AMDGPU_GEM_WAIT_IDLE	0x07
#घोषणा DRM_AMDGPU_GEM_VA		0x08
#घोषणा DRM_AMDGPU_WAIT_CS		0x09
#घोषणा DRM_AMDGPU_GEM_OP		0x10
#घोषणा DRM_AMDGPU_GEM_USERPTR		0x11
#घोषणा DRM_AMDGPU_WAIT_FENCES		0x12
#घोषणा DRM_AMDGPU_VM			0x13
#घोषणा DRM_AMDGPU_FENCE_TO_HANDLE	0x14
#घोषणा DRM_AMDGPU_SCHED		0x15

#घोषणा DRM_IOCTL_AMDGPU_GEM_CREATE	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_GEM_CREATE, जोड़ drm_amdgpu_gem_create)
#घोषणा DRM_IOCTL_AMDGPU_GEM_MMAP	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_GEM_MMAP, जोड़ drm_amdgpu_gem_mmap)
#घोषणा DRM_IOCTL_AMDGPU_CTX		DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_CTX, जोड़ drm_amdgpu_ctx)
#घोषणा DRM_IOCTL_AMDGPU_BO_LIST	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_BO_LIST, जोड़ drm_amdgpu_bo_list)
#घोषणा DRM_IOCTL_AMDGPU_CS		DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_CS, जोड़ drm_amdgpu_cs)
#घोषणा DRM_IOCTL_AMDGPU_INFO		DRM_IOW(DRM_COMMAND_BASE + DRM_AMDGPU_INFO, काष्ठा drm_amdgpu_info)
#घोषणा DRM_IOCTL_AMDGPU_GEM_METADATA	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_GEM_METADATA, काष्ठा drm_amdgpu_gem_metadata)
#घोषणा DRM_IOCTL_AMDGPU_GEM_WAIT_IDLE	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_GEM_WAIT_IDLE, जोड़ drm_amdgpu_gem_रुको_idle)
#घोषणा DRM_IOCTL_AMDGPU_GEM_VA		DRM_IOW(DRM_COMMAND_BASE + DRM_AMDGPU_GEM_VA, काष्ठा drm_amdgpu_gem_va)
#घोषणा DRM_IOCTL_AMDGPU_WAIT_CS	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_WAIT_CS, जोड़ drm_amdgpu_रुको_cs)
#घोषणा DRM_IOCTL_AMDGPU_GEM_OP		DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_GEM_OP, काष्ठा drm_amdgpu_gem_op)
#घोषणा DRM_IOCTL_AMDGPU_GEM_USERPTR	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_GEM_USERPTR, काष्ठा drm_amdgpu_gem_userptr)
#घोषणा DRM_IOCTL_AMDGPU_WAIT_FENCES	DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_WAIT_FENCES, जोड़ drm_amdgpu_रुको_fences)
#घोषणा DRM_IOCTL_AMDGPU_VM		DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_VM, जोड़ drm_amdgpu_vm)
#घोषणा DRM_IOCTL_AMDGPU_FENCE_TO_HANDLE DRM_IOWR(DRM_COMMAND_BASE + DRM_AMDGPU_FENCE_TO_HANDLE, जोड़ drm_amdgpu_fence_to_handle)
#घोषणा DRM_IOCTL_AMDGPU_SCHED		DRM_IOW(DRM_COMMAND_BASE + DRM_AMDGPU_SCHED, जोड़ drm_amdgpu_sched)

/**
 * DOC: memory करोमुख्यs
 *
 * %AMDGPU_GEM_DOMAIN_CPU	System memory that is not GPU accessible.
 * Memory in this pool could be swapped out to disk अगर there is pressure.
 *
 * %AMDGPU_GEM_DOMAIN_GTT	GPU accessible प्रणाली memory, mapped पूर्णांकo the
 * GPU's भव address space via gart. Gart memory linearizes non-contiguous
 * pages of प्रणाली memory, allows GPU access प्रणाली memory in a linezrized
 * fashion.
 *
 * %AMDGPU_GEM_DOMAIN_VRAM	Local video memory. For APUs, it is memory
 * carved out by the BIOS.
 *
 * %AMDGPU_GEM_DOMAIN_GDS	Global on-chip data storage used to share data
 * across shader thपढ़ोs.
 *
 * %AMDGPU_GEM_DOMAIN_GWS	Global wave sync, used to synchronize the
 * execution of all the waves on a device.
 *
 * %AMDGPU_GEM_DOMAIN_OA	Ordered append, used by 3D or Compute engines
 * क्रम appending data.
 */
#घोषणा AMDGPU_GEM_DOMAIN_CPU		0x1
#घोषणा AMDGPU_GEM_DOMAIN_GTT		0x2
#घोषणा AMDGPU_GEM_DOMAIN_VRAM		0x4
#घोषणा AMDGPU_GEM_DOMAIN_GDS		0x8
#घोषणा AMDGPU_GEM_DOMAIN_GWS		0x10
#घोषणा AMDGPU_GEM_DOMAIN_OA		0x20
#घोषणा AMDGPU_GEM_DOMAIN_MASK		(AMDGPU_GEM_DOMAIN_CPU | \
					 AMDGPU_GEM_DOMAIN_GTT | \
					 AMDGPU_GEM_DOMAIN_VRAM | \
					 AMDGPU_GEM_DOMAIN_GDS | \
					 AMDGPU_GEM_DOMAIN_GWS | \
					 AMDGPU_GEM_DOMAIN_OA)

/* Flag that CPU access will be required क्रम the हाल of VRAM करोमुख्य */
#घोषणा AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED	(1 << 0)
/* Flag that CPU access will not work, this VRAM करोमुख्य is invisible */
#घोषणा AMDGPU_GEM_CREATE_NO_CPU_ACCESS		(1 << 1)
/* Flag that USWC attributes should be used क्रम GTT */
#घोषणा AMDGPU_GEM_CREATE_CPU_GTT_USWC		(1 << 2)
/* Flag that the memory should be in VRAM and cleared */
#घोषणा AMDGPU_GEM_CREATE_VRAM_CLEARED		(1 << 3)
/* Flag that create shaकरोw bo(GTT) जबतक allocating vram bo */
#घोषणा AMDGPU_GEM_CREATE_SHADOW		(1 << 4)
/* Flag that allocating the BO should use linear VRAM */
#घोषणा AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS	(1 << 5)
/* Flag that BO is always valid in this VM */
#घोषणा AMDGPU_GEM_CREATE_VM_ALWAYS_VALID	(1 << 6)
/* Flag that BO sharing will be explicitly synchronized */
#घोषणा AMDGPU_GEM_CREATE_EXPLICIT_SYNC		(1 << 7)
/* Flag that indicates allocating MQD gart on GFX9, where the mtype
 * क्रम the second page onward should be set to NC. It should never
 * be used by user space applications.
 */
#घोषणा AMDGPU_GEM_CREATE_CP_MQD_GFX9		(1 << 8)
/* Flag that BO may contain sensitive data that must be wiped beक्रमe
 * releasing the memory
 */
#घोषणा AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE	(1 << 9)
/* Flag that BO will be encrypted and that the TMZ bit should be
 * set in the PTEs when mapping this buffer via GPUVM or
 * accessing it with various hw blocks
 */
#घोषणा AMDGPU_GEM_CREATE_ENCRYPTED		(1 << 10)

काष्ठा drm_amdgpu_gem_create_in  अणु
	/** the requested memory size */
	__u64 bo_size;
	/** physical start_addr alignment in bytes क्रम some HW requirements */
	__u64 alignment;
	/** the requested memory करोमुख्यs */
	__u64 करोमुख्यs;
	/** allocation flags */
	__u64 करोमुख्य_flags;
पूर्ण;

काष्ठा drm_amdgpu_gem_create_out  अणु
	/** वापसed GEM object handle */
	__u32 handle;
	__u32 _pad;
पूर्ण;

जोड़ drm_amdgpu_gem_create अणु
	काष्ठा drm_amdgpu_gem_create_in		in;
	काष्ठा drm_amdgpu_gem_create_out	out;
पूर्ण;

/** Opcode to create new residency list.  */
#घोषणा AMDGPU_BO_LIST_OP_CREATE	0
/** Opcode to destroy previously created residency list */
#घोषणा AMDGPU_BO_LIST_OP_DESTROY	1
/** Opcode to update resource inक्रमmation in the list */
#घोषणा AMDGPU_BO_LIST_OP_UPDATE	2

काष्ठा drm_amdgpu_bo_list_in अणु
	/** Type of operation */
	__u32 operation;
	/** Handle of list or 0 अगर we want to create one */
	__u32 list_handle;
	/** Number of BOs in list  */
	__u32 bo_number;
	/** Size of each element describing BO */
	__u32 bo_info_size;
	/** Poपूर्णांकer to array describing BOs */
	__u64 bo_info_ptr;
पूर्ण;

काष्ठा drm_amdgpu_bo_list_entry अणु
	/** Handle of BO */
	__u32 bo_handle;
	/** New (अगर specअगरied) BO priority to be used during migration */
	__u32 bo_priority;
पूर्ण;

काष्ठा drm_amdgpu_bo_list_out अणु
	/** Handle of resource list  */
	__u32 list_handle;
	__u32 _pad;
पूर्ण;

जोड़ drm_amdgpu_bo_list अणु
	काष्ठा drm_amdgpu_bo_list_in in;
	काष्ठा drm_amdgpu_bo_list_out out;
पूर्ण;

/* context related */
#घोषणा AMDGPU_CTX_OP_ALLOC_CTX	1
#घोषणा AMDGPU_CTX_OP_FREE_CTX	2
#घोषणा AMDGPU_CTX_OP_QUERY_STATE	3
#घोषणा AMDGPU_CTX_OP_QUERY_STATE2	4

/* GPU reset status */
#घोषणा AMDGPU_CTX_NO_RESET		0
/* this the context caused it */
#घोषणा AMDGPU_CTX_GUILTY_RESET		1
/* some other context caused it */
#घोषणा AMDGPU_CTX_INNOCENT_RESET	2
/* unknown cause */
#घोषणा AMDGPU_CTX_UNKNOWN_RESET	3

/* indicate gpu reset occured after ctx created */
#घोषणा AMDGPU_CTX_QUERY2_FLAGS_RESET    (1<<0)
/* indicate vram lost occured after ctx created */
#घोषणा AMDGPU_CTX_QUERY2_FLAGS_VRAMLOST (1<<1)
/* indicate some job from this context once cause gpu hang */
#घोषणा AMDGPU_CTX_QUERY2_FLAGS_GUILTY   (1<<2)
/* indicate some errors are detected by RAS */
#घोषणा AMDGPU_CTX_QUERY2_FLAGS_RAS_CE   (1<<3)
#घोषणा AMDGPU_CTX_QUERY2_FLAGS_RAS_UE   (1<<4)

/* Context priority level */
#घोषणा AMDGPU_CTX_PRIORITY_UNSET       -2048
#घोषणा AMDGPU_CTX_PRIORITY_VERY_LOW    -1023
#घोषणा AMDGPU_CTX_PRIORITY_LOW         -512
#घोषणा AMDGPU_CTX_PRIORITY_NORMAL      0
/*
 * When used in काष्ठा drm_amdgpu_ctx_in, a priority above NORMAL requires
 * CAP_SYS_NICE or DRM_MASTER
*/
#घोषणा AMDGPU_CTX_PRIORITY_HIGH        512
#घोषणा AMDGPU_CTX_PRIORITY_VERY_HIGH   1023

काष्ठा drm_amdgpu_ctx_in अणु
	/** AMDGPU_CTX_OP_* */
	__u32	op;
	/** For future use, no flags defined so far */
	__u32	flags;
	__u32	ctx_id;
	/** AMDGPU_CTX_PRIORITY_* */
	__s32	priority;
पूर्ण;

जोड़ drm_amdgpu_ctx_out अणु
		काष्ठा अणु
			__u32	ctx_id;
			__u32	_pad;
		पूर्ण alloc;

		काष्ठा अणु
			/** For future use, no flags defined so far */
			__u64	flags;
			/** Number of resets caused by this context so far. */
			__u32	hangs;
			/** Reset status since the last call of the ioctl. */
			__u32	reset_status;
		पूर्ण state;
पूर्ण;

जोड़ drm_amdgpu_ctx अणु
	काष्ठा drm_amdgpu_ctx_in in;
	जोड़ drm_amdgpu_ctx_out out;
पूर्ण;

/* vm ioctl */
#घोषणा AMDGPU_VM_OP_RESERVE_VMID	1
#घोषणा AMDGPU_VM_OP_UNRESERVE_VMID	2

काष्ठा drm_amdgpu_vm_in अणु
	/** AMDGPU_VM_OP_* */
	__u32	op;
	__u32	flags;
पूर्ण;

काष्ठा drm_amdgpu_vm_out अणु
	/** For future use, no flags defined so far */
	__u64	flags;
पूर्ण;

जोड़ drm_amdgpu_vm अणु
	काष्ठा drm_amdgpu_vm_in in;
	काष्ठा drm_amdgpu_vm_out out;
पूर्ण;

/* sched ioctl */
#घोषणा AMDGPU_SCHED_OP_PROCESS_PRIORITY_OVERRIDE	1
#घोषणा AMDGPU_SCHED_OP_CONTEXT_PRIORITY_OVERRIDE	2

काष्ठा drm_amdgpu_sched_in अणु
	/* AMDGPU_SCHED_OP_* */
	__u32	op;
	__u32	fd;
	/** AMDGPU_CTX_PRIORITY_* */
	__s32	priority;
	__u32   ctx_id;
पूर्ण;

जोड़ drm_amdgpu_sched अणु
	काष्ठा drm_amdgpu_sched_in in;
पूर्ण;

/*
 * This is not a reliable API and you should expect it to fail क्रम any
 * number of reasons and have fallback path that करो not use userptr to
 * perक्रमm any operation.
 */
#घोषणा AMDGPU_GEM_USERPTR_READONLY	(1 << 0)
#घोषणा AMDGPU_GEM_USERPTR_ANONONLY	(1 << 1)
#घोषणा AMDGPU_GEM_USERPTR_VALIDATE	(1 << 2)
#घोषणा AMDGPU_GEM_USERPTR_REGISTER	(1 << 3)

काष्ठा drm_amdgpu_gem_userptr अणु
	__u64		addr;
	__u64		size;
	/* AMDGPU_GEM_USERPTR_* */
	__u32		flags;
	/* Resulting GEM handle */
	__u32		handle;
पूर्ण;

/* SI-CI-VI: */
/* same meaning as the GB_TILE_MODE and GL_MACRO_TILE_MODE fields */
#घोषणा AMDGPU_TILING_ARRAY_MODE_SHIFT			0
#घोषणा AMDGPU_TILING_ARRAY_MODE_MASK			0xf
#घोषणा AMDGPU_TILING_PIPE_CONFIG_SHIFT			4
#घोषणा AMDGPU_TILING_PIPE_CONFIG_MASK			0x1f
#घोषणा AMDGPU_TILING_TILE_SPLIT_SHIFT			9
#घोषणा AMDGPU_TILING_TILE_SPLIT_MASK			0x7
#घोषणा AMDGPU_TILING_MICRO_TILE_MODE_SHIFT		12
#घोषणा AMDGPU_TILING_MICRO_TILE_MODE_MASK		0x7
#घोषणा AMDGPU_TILING_BANK_WIDTH_SHIFT			15
#घोषणा AMDGPU_TILING_BANK_WIDTH_MASK			0x3
#घोषणा AMDGPU_TILING_BANK_HEIGHT_SHIFT			17
#घोषणा AMDGPU_TILING_BANK_HEIGHT_MASK			0x3
#घोषणा AMDGPU_TILING_MACRO_TILE_ASPECT_SHIFT		19
#घोषणा AMDGPU_TILING_MACRO_TILE_ASPECT_MASK		0x3
#घोषणा AMDGPU_TILING_NUM_BANKS_SHIFT			21
#घोषणा AMDGPU_TILING_NUM_BANKS_MASK			0x3

/* GFX9 and later: */
#घोषणा AMDGPU_TILING_SWIZZLE_MODE_SHIFT		0
#घोषणा AMDGPU_TILING_SWIZZLE_MODE_MASK			0x1f
#घोषणा AMDGPU_TILING_DCC_OFFSET_256B_SHIFT		5
#घोषणा AMDGPU_TILING_DCC_OFFSET_256B_MASK		0xFFFFFF
#घोषणा AMDGPU_TILING_DCC_PITCH_MAX_SHIFT		29
#घोषणा AMDGPU_TILING_DCC_PITCH_MAX_MASK		0x3FFF
#घोषणा AMDGPU_TILING_DCC_INDEPENDENT_64B_SHIFT		43
#घोषणा AMDGPU_TILING_DCC_INDEPENDENT_64B_MASK		0x1
#घोषणा AMDGPU_TILING_DCC_INDEPENDENT_128B_SHIFT	44
#घोषणा AMDGPU_TILING_DCC_INDEPENDENT_128B_MASK		0x1
#घोषणा AMDGPU_TILING_SCANOUT_SHIFT			63
#घोषणा AMDGPU_TILING_SCANOUT_MASK			0x1

/* Set/Get helpers क्रम tiling flags. */
#घोषणा AMDGPU_TILING_SET(field, value) \
	(((__u64)(value) & AMDGPU_TILING_##field##_MASK) << AMDGPU_TILING_##field##_SHIFT)
#घोषणा AMDGPU_TILING_GET(value, field) \
	(((__u64)(value) >> AMDGPU_TILING_##field##_SHIFT) & AMDGPU_TILING_##field##_MASK)

#घोषणा AMDGPU_GEM_METADATA_OP_SET_METADATA                  1
#घोषणा AMDGPU_GEM_METADATA_OP_GET_METADATA                  2

/** The same काष्ठाure is shared क्रम input/output */
काष्ठा drm_amdgpu_gem_metadata अणु
	/** GEM Object handle */
	__u32	handle;
	/** Do we want get or set metadata */
	__u32	op;
	काष्ठा अणु
		/** For future use, no flags defined so far */
		__u64	flags;
		/** family specअगरic tiling info */
		__u64	tiling_info;
		__u32	data_size_bytes;
		__u32	data[64];
	पूर्ण data;
पूर्ण;

काष्ठा drm_amdgpu_gem_mmap_in अणु
	/** the GEM object handle */
	__u32 handle;
	__u32 _pad;
पूर्ण;

काष्ठा drm_amdgpu_gem_mmap_out अणु
	/** mmap offset from the vma offset manager */
	__u64 addr_ptr;
पूर्ण;

जोड़ drm_amdgpu_gem_mmap अणु
	काष्ठा drm_amdgpu_gem_mmap_in   in;
	काष्ठा drm_amdgpu_gem_mmap_out out;
पूर्ण;

काष्ठा drm_amdgpu_gem_रुको_idle_in अणु
	/** GEM object handle */
	__u32 handle;
	/** For future use, no flags defined so far */
	__u32 flags;
	/** Absolute समयout to रुको */
	__u64 समयout;
पूर्ण;

काष्ठा drm_amdgpu_gem_रुको_idle_out अणु
	/** BO status:  0 - BO is idle, 1 - BO is busy */
	__u32 status;
	/** Returned current memory करोमुख्य */
	__u32 करोमुख्य;
पूर्ण;

जोड़ drm_amdgpu_gem_रुको_idle अणु
	काष्ठा drm_amdgpu_gem_रुको_idle_in  in;
	काष्ठा drm_amdgpu_gem_रुको_idle_out out;
पूर्ण;

काष्ठा drm_amdgpu_रुको_cs_in अणु
	/* Command submission handle
         * handle equals 0 means none to रुको क्रम
         * handle equals ~0ull means रुको क्रम the latest sequence number
         */
	__u64 handle;
	/** Absolute समयout to रुको */
	__u64 समयout;
	__u32 ip_type;
	__u32 ip_instance;
	__u32 ring;
	__u32 ctx_id;
पूर्ण;

काष्ठा drm_amdgpu_रुको_cs_out अणु
	/** CS status:  0 - CS completed, 1 - CS still busy */
	__u64 status;
पूर्ण;

जोड़ drm_amdgpu_रुको_cs अणु
	काष्ठा drm_amdgpu_रुको_cs_in in;
	काष्ठा drm_amdgpu_रुको_cs_out out;
पूर्ण;

काष्ठा drm_amdgpu_fence अणु
	__u32 ctx_id;
	__u32 ip_type;
	__u32 ip_instance;
	__u32 ring;
	__u64 seq_no;
पूर्ण;

काष्ठा drm_amdgpu_रुको_fences_in अणु
	/** This poपूर्णांकs to uपूर्णांक64_t * which poपूर्णांकs to fences */
	__u64 fences;
	__u32 fence_count;
	__u32 रुको_all;
	__u64 समयout_ns;
पूर्ण;

काष्ठा drm_amdgpu_रुको_fences_out अणु
	__u32 status;
	__u32 first_संकेतed;
पूर्ण;

जोड़ drm_amdgpu_रुको_fences अणु
	काष्ठा drm_amdgpu_रुको_fences_in in;
	काष्ठा drm_amdgpu_रुको_fences_out out;
पूर्ण;

#घोषणा AMDGPU_GEM_OP_GET_GEM_CREATE_INFO	0
#घोषणा AMDGPU_GEM_OP_SET_PLACEMENT		1

/* Sets or वापसs a value associated with a buffer. */
काष्ठा drm_amdgpu_gem_op अणु
	/** GEM object handle */
	__u32	handle;
	/** AMDGPU_GEM_OP_* */
	__u32	op;
	/** Input or वापस value */
	__u64	value;
पूर्ण;

#घोषणा AMDGPU_VA_OP_MAP			1
#घोषणा AMDGPU_VA_OP_UNMAP			2
#घोषणा AMDGPU_VA_OP_CLEAR			3
#घोषणा AMDGPU_VA_OP_REPLACE			4

/* Delay the page table update till the next CS */
#घोषणा AMDGPU_VM_DELAY_UPDATE		(1 << 0)

/* Mapping flags */
/* पढ़ोable mapping */
#घोषणा AMDGPU_VM_PAGE_READABLE		(1 << 1)
/* writable mapping */
#घोषणा AMDGPU_VM_PAGE_WRITEABLE	(1 << 2)
/* executable mapping, new क्रम VI */
#घोषणा AMDGPU_VM_PAGE_EXECUTABLE	(1 << 3)
/* partially resident texture */
#घोषणा AMDGPU_VM_PAGE_PRT		(1 << 4)
/* MTYPE flags use bit 5 to 8 */
#घोषणा AMDGPU_VM_MTYPE_MASK		(0xf << 5)
/* Default MTYPE. Pre-AI must use this.  Recommended क्रम newer ASICs. */
#घोषणा AMDGPU_VM_MTYPE_DEFAULT		(0 << 5)
/* Use Non Coherent MTYPE instead of शेष MTYPE */
#घोषणा AMDGPU_VM_MTYPE_NC		(1 << 5)
/* Use Write Combine MTYPE instead of शेष MTYPE */
#घोषणा AMDGPU_VM_MTYPE_WC		(2 << 5)
/* Use Cache Coherent MTYPE instead of शेष MTYPE */
#घोषणा AMDGPU_VM_MTYPE_CC		(3 << 5)
/* Use UnCached MTYPE instead of शेष MTYPE */
#घोषणा AMDGPU_VM_MTYPE_UC		(4 << 5)
/* Use Read Write MTYPE instead of शेष MTYPE */
#घोषणा AMDGPU_VM_MTYPE_RW		(5 << 5)

काष्ठा drm_amdgpu_gem_va अणु
	/** GEM object handle */
	__u32 handle;
	__u32 _pad;
	/** AMDGPU_VA_OP_* */
	__u32 operation;
	/** AMDGPU_VM_PAGE_* */
	__u32 flags;
	/** va address to assign . Must be correctly aligned.*/
	__u64 va_address;
	/** Specअगरy offset inside of BO to assign. Must be correctly aligned.*/
	__u64 offset_in_bo;
	/** Specअगरy mapping size. Must be correctly aligned. */
	__u64 map_size;
पूर्ण;

#घोषणा AMDGPU_HW_IP_GFX          0
#घोषणा AMDGPU_HW_IP_COMPUTE      1
#घोषणा AMDGPU_HW_IP_DMA          2
#घोषणा AMDGPU_HW_IP_UVD          3
#घोषणा AMDGPU_HW_IP_VCE          4
#घोषणा AMDGPU_HW_IP_UVD_ENC      5
#घोषणा AMDGPU_HW_IP_VCN_DEC      6
#घोषणा AMDGPU_HW_IP_VCN_ENC      7
#घोषणा AMDGPU_HW_IP_VCN_JPEG     8
#घोषणा AMDGPU_HW_IP_NUM          9

#घोषणा AMDGPU_HW_IP_INSTANCE_MAX_COUNT 1

#घोषणा AMDGPU_CHUNK_ID_IB		0x01
#घोषणा AMDGPU_CHUNK_ID_FENCE		0x02
#घोषणा AMDGPU_CHUNK_ID_DEPENDENCIES	0x03
#घोषणा AMDGPU_CHUNK_ID_SYNCOBJ_IN      0x04
#घोषणा AMDGPU_CHUNK_ID_SYNCOBJ_OUT     0x05
#घोषणा AMDGPU_CHUNK_ID_BO_HANDLES      0x06
#घोषणा AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES	0x07
#घोषणा AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_WAIT    0x08
#घोषणा AMDGPU_CHUNK_ID_SYNCOBJ_TIMELINE_SIGNAL  0x09

काष्ठा drm_amdgpu_cs_chunk अणु
	__u32		chunk_id;
	__u32		length_dw;
	__u64		chunk_data;
पूर्ण;

काष्ठा drm_amdgpu_cs_in अणु
	/** Rendering context id */
	__u32		ctx_id;
	/**  Handle of resource list associated with CS */
	__u32		bo_list_handle;
	__u32		num_chunks;
	__u32		flags;
	/** this poपूर्णांकs to __u64 * which poपूर्णांक to cs chunks */
	__u64		chunks;
पूर्ण;

काष्ठा drm_amdgpu_cs_out अणु
	__u64 handle;
पूर्ण;

जोड़ drm_amdgpu_cs अणु
	काष्ठा drm_amdgpu_cs_in in;
	काष्ठा drm_amdgpu_cs_out out;
पूर्ण;

/* Specअगरy flags to be used क्रम IB */

/* This IB should be submitted to CE */
#घोषणा AMDGPU_IB_FLAG_CE	(1<<0)

/* Preamble flag, which means the IB could be dropped अगर no context चयन */
#घोषणा AMDGPU_IB_FLAG_PREAMBLE (1<<1)

/* Preempt flag, IB should set Pre_enb bit अगर PREEMPT flag detected */
#घोषणा AMDGPU_IB_FLAG_PREEMPT (1<<2)

/* The IB fence should करो the L2 ग_लिखोback but not invalidate any shader
 * caches (L2/vL1/sL1/I$). */
#घोषणा AMDGPU_IB_FLAG_TC_WB_NOT_INVALIDATE (1 << 3)

/* Set GDS_COMPUTE_MAX_WAVE_ID = DEFAULT beक्रमe PACKET3_INसूचीECT_BUFFER.
 * This will reset wave ID counters क्रम the IB.
 */
#घोषणा AMDGPU_IB_FLAG_RESET_GDS_MAX_WAVE_ID (1 << 4)

/* Flag the IB as secure (TMZ)
 */
#घोषणा AMDGPU_IB_FLAGS_SECURE  (1 << 5)

/* Tell KMD to flush and invalidate caches
 */
#घोषणा AMDGPU_IB_FLAG_EMIT_MEM_SYNC  (1 << 6)

काष्ठा drm_amdgpu_cs_chunk_ib अणु
	__u32 _pad;
	/** AMDGPU_IB_FLAG_* */
	__u32 flags;
	/** Virtual address to begin IB execution */
	__u64 बहु_शुरू;
	/** Size of submission */
	__u32 ib_bytes;
	/** HW IP to submit to */
	__u32 ip_type;
	/** HW IP index of the same type to submit to  */
	__u32 ip_instance;
	/** Ring index to submit to */
	__u32 ring;
पूर्ण;

काष्ठा drm_amdgpu_cs_chunk_dep अणु
	__u32 ip_type;
	__u32 ip_instance;
	__u32 ring;
	__u32 ctx_id;
	__u64 handle;
पूर्ण;

काष्ठा drm_amdgpu_cs_chunk_fence अणु
	__u32 handle;
	__u32 offset;
पूर्ण;

काष्ठा drm_amdgpu_cs_chunk_sem अणु
	__u32 handle;
पूर्ण;

काष्ठा drm_amdgpu_cs_chunk_syncobj अणु
       __u32 handle;
       __u32 flags;
       __u64 poपूर्णांक;
पूर्ण;

#घोषणा AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ	0
#घोषणा AMDGPU_FENCE_TO_HANDLE_GET_SYNCOBJ_FD	1
#घोषणा AMDGPU_FENCE_TO_HANDLE_GET_SYNC_खाता_FD	2

जोड़ drm_amdgpu_fence_to_handle अणु
	काष्ठा अणु
		काष्ठा drm_amdgpu_fence fence;
		__u32 what;
		__u32 pad;
	पूर्ण in;
	काष्ठा अणु
		__u32 handle;
	पूर्ण out;
पूर्ण;

काष्ठा drm_amdgpu_cs_chunk_data अणु
	जोड़ अणु
		काष्ठा drm_amdgpu_cs_chunk_ib		ib_data;
		काष्ठा drm_amdgpu_cs_chunk_fence	fence_data;
	पूर्ण;
पूर्ण;

/*
 *  Query h/w info: Flag that this is पूर्णांकegrated (a.h.a. fusion) GPU
 *
 */
#घोषणा AMDGPU_IDS_FLAGS_FUSION         0x1
#घोषणा AMDGPU_IDS_FLAGS_PREEMPTION     0x2
#घोषणा AMDGPU_IDS_FLAGS_TMZ            0x4

/* indicate अगर acceleration can be working */
#घोषणा AMDGPU_INFO_ACCEL_WORKING		0x00
/* get the crtc_id from the mode object id? */
#घोषणा AMDGPU_INFO_CRTC_FROM_ID		0x01
/* query hw IP info */
#घोषणा AMDGPU_INFO_HW_IP_INFO			0x02
/* query hw IP instance count क्रम the specअगरied type */
#घोषणा AMDGPU_INFO_HW_IP_COUNT			0x03
/* बारtamp क्रम GL_ARB_समयr_query */
#घोषणा AMDGPU_INFO_TIMESTAMP			0x05
/* Query the firmware version */
#घोषणा AMDGPU_INFO_FW_VERSION			0x0e
	/* Subquery id: Query VCE firmware version */
	#घोषणा AMDGPU_INFO_FW_VCE		0x1
	/* Subquery id: Query UVD firmware version */
	#घोषणा AMDGPU_INFO_FW_UVD		0x2
	/* Subquery id: Query GMC firmware version */
	#घोषणा AMDGPU_INFO_FW_GMC		0x03
	/* Subquery id: Query GFX ME firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_ME		0x04
	/* Subquery id: Query GFX PFP firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_PFP		0x05
	/* Subquery id: Query GFX CE firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_CE		0x06
	/* Subquery id: Query GFX RLC firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_RLC		0x07
	/* Subquery id: Query GFX MEC firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_MEC		0x08
	/* Subquery id: Query SMC firmware version */
	#घोषणा AMDGPU_INFO_FW_SMC		0x0a
	/* Subquery id: Query SDMA firmware version */
	#घोषणा AMDGPU_INFO_FW_SDMA		0x0b
	/* Subquery id: Query PSP SOS firmware version */
	#घोषणा AMDGPU_INFO_FW_SOS		0x0c
	/* Subquery id: Query PSP ASD firmware version */
	#घोषणा AMDGPU_INFO_FW_ASD		0x0d
	/* Subquery id: Query VCN firmware version */
	#घोषणा AMDGPU_INFO_FW_VCN		0x0e
	/* Subquery id: Query GFX RLC SRLC firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_CNTL 0x0f
	/* Subquery id: Query GFX RLC SRLG firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_GPM_MEM 0x10
	/* Subquery id: Query GFX RLC SRLS firmware version */
	#घोषणा AMDGPU_INFO_FW_GFX_RLC_RESTORE_LIST_SRM_MEM 0x11
	/* Subquery id: Query DMCU firmware version */
	#घोषणा AMDGPU_INFO_FW_DMCU		0x12
	#घोषणा AMDGPU_INFO_FW_TA		0x13
	/* Subquery id: Query DMCUB firmware version */
	#घोषणा AMDGPU_INFO_FW_DMCUB		0x14
	/* Subquery id: Query TOC firmware version */
	#घोषणा AMDGPU_INFO_FW_TOC		0x15

/* number of bytes moved क्रम TTM migration */
#घोषणा AMDGPU_INFO_NUM_BYTES_MOVED		0x0f
/* the used VRAM size */
#घोषणा AMDGPU_INFO_VRAM_USAGE			0x10
/* the used GTT size */
#घोषणा AMDGPU_INFO_GTT_USAGE			0x11
/* Inक्रमmation about GDS, etc. resource configuration */
#घोषणा AMDGPU_INFO_GDS_CONFIG			0x13
/* Query inक्रमmation about VRAM and GTT करोमुख्यs */
#घोषणा AMDGPU_INFO_VRAM_GTT			0x14
/* Query inक्रमmation about रेजिस्टर in MMR address space*/
#घोषणा AMDGPU_INFO_READ_MMR_REG		0x15
/* Query inक्रमmation about device: rev id, family, etc. */
#घोषणा AMDGPU_INFO_DEV_INFO			0x16
/* visible vram usage */
#घोषणा AMDGPU_INFO_VIS_VRAM_USAGE		0x17
/* number of TTM buffer evictions */
#घोषणा AMDGPU_INFO_NUM_EVICTIONS		0x18
/* Query memory about VRAM and GTT करोमुख्यs */
#घोषणा AMDGPU_INFO_MEMORY			0x19
/* Query vce घड़ी table */
#घोषणा AMDGPU_INFO_VCE_CLOCK_TABLE		0x1A
/* Query vbios related inक्रमmation */
#घोषणा AMDGPU_INFO_VBIOS			0x1B
	/* Subquery id: Query vbios size */
	#घोषणा AMDGPU_INFO_VBIOS_SIZE		0x1
	/* Subquery id: Query vbios image */
	#घोषणा AMDGPU_INFO_VBIOS_IMAGE		0x2
/* Query UVD handles */
#घोषणा AMDGPU_INFO_NUM_HANDLES			0x1C
/* Query sensor related inक्रमmation */
#घोषणा AMDGPU_INFO_SENSOR			0x1D
	/* Subquery id: Query GPU shader घड़ी */
	#घोषणा AMDGPU_INFO_SENSOR_GFX_SCLK		0x1
	/* Subquery id: Query GPU memory घड़ी */
	#घोषणा AMDGPU_INFO_SENSOR_GFX_MCLK		0x2
	/* Subquery id: Query GPU temperature */
	#घोषणा AMDGPU_INFO_SENSOR_GPU_TEMP		0x3
	/* Subquery id: Query GPU load */
	#घोषणा AMDGPU_INFO_SENSOR_GPU_LOAD		0x4
	/* Subquery id: Query average GPU घातer	*/
	#घोषणा AMDGPU_INFO_SENSOR_GPU_AVG_POWER	0x5
	/* Subquery id: Query northbridge voltage */
	#घोषणा AMDGPU_INFO_SENSOR_VDDNB		0x6
	/* Subquery id: Query graphics voltage */
	#घोषणा AMDGPU_INFO_SENSOR_VDDGFX		0x7
	/* Subquery id: Query GPU stable pstate shader घड़ी */
	#घोषणा AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK		0x8
	/* Subquery id: Query GPU stable pstate memory घड़ी */
	#घोषणा AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_MCLK		0x9
/* Number of VRAM page faults on CPU access. */
#घोषणा AMDGPU_INFO_NUM_VRAM_CPU_PAGE_FAULTS	0x1E
#घोषणा AMDGPU_INFO_VRAM_LOST_COUNTER		0x1F
/* query ras mask of enabled features*/
#घोषणा AMDGPU_INFO_RAS_ENABLED_FEATURES	0x20
/* query video encode/decode caps */
#घोषणा AMDGPU_INFO_VIDEO_CAPS			0x21
	/* Subquery id: Decode */
	#घोषणा AMDGPU_INFO_VIDEO_CAPS_DECODE		0
	/* Subquery id: Encode */
	#घोषणा AMDGPU_INFO_VIDEO_CAPS_ENCODE		1

/* RAS MASK: UMC (VRAM) */
#घोषणा AMDGPU_INFO_RAS_ENABLED_UMC			(1 << 0)
/* RAS MASK: SDMA */
#घोषणा AMDGPU_INFO_RAS_ENABLED_SDMA			(1 << 1)
/* RAS MASK: GFX */
#घोषणा AMDGPU_INFO_RAS_ENABLED_GFX			(1 << 2)
/* RAS MASK: MMHUB */
#घोषणा AMDGPU_INFO_RAS_ENABLED_MMHUB			(1 << 3)
/* RAS MASK: ATHUB */
#घोषणा AMDGPU_INFO_RAS_ENABLED_ATHUB			(1 << 4)
/* RAS MASK: PCIE */
#घोषणा AMDGPU_INFO_RAS_ENABLED_PCIE			(1 << 5)
/* RAS MASK: HDP */
#घोषणा AMDGPU_INFO_RAS_ENABLED_HDP			(1 << 6)
/* RAS MASK: XGMI */
#घोषणा AMDGPU_INFO_RAS_ENABLED_XGMI			(1 << 7)
/* RAS MASK: DF */
#घोषणा AMDGPU_INFO_RAS_ENABLED_DF			(1 << 8)
/* RAS MASK: SMN */
#घोषणा AMDGPU_INFO_RAS_ENABLED_SMN			(1 << 9)
/* RAS MASK: SEM */
#घोषणा AMDGPU_INFO_RAS_ENABLED_SEM			(1 << 10)
/* RAS MASK: MP0 */
#घोषणा AMDGPU_INFO_RAS_ENABLED_MP0			(1 << 11)
/* RAS MASK: MP1 */
#घोषणा AMDGPU_INFO_RAS_ENABLED_MP1			(1 << 12)
/* RAS MASK: FUSE */
#घोषणा AMDGPU_INFO_RAS_ENABLED_FUSE			(1 << 13)

#घोषणा AMDGPU_INFO_MMR_SE_INDEX_SHIFT	0
#घोषणा AMDGPU_INFO_MMR_SE_INDEX_MASK	0xff
#घोषणा AMDGPU_INFO_MMR_SH_INDEX_SHIFT	8
#घोषणा AMDGPU_INFO_MMR_SH_INDEX_MASK	0xff

काष्ठा drm_amdgpu_query_fw अणु
	/** AMDGPU_INFO_FW_* */
	__u32 fw_type;
	/**
	 * Index of the IP अगर there are more IPs of
	 * the same type.
	 */
	__u32 ip_instance;
	/**
	 * Index of the engine. Whether this is used depends
	 * on the firmware type. (e.g. MEC, SDMA)
	 */
	__u32 index;
	__u32 _pad;
पूर्ण;

/* Input काष्ठाure क्रम the INFO ioctl */
काष्ठा drm_amdgpu_info अणु
	/* Where the वापस value will be stored */
	__u64 वापस_poपूर्णांकer;
	/* The size of the वापस value. Just like "size" in "snprintf",
	 * it limits how many bytes the kernel can ग_लिखो. */
	__u32 वापस_size;
	/* The query request id. */
	__u32 query;

	जोड़ अणु
		काष्ठा अणु
			__u32 id;
			__u32 _pad;
		पूर्ण mode_crtc;

		काष्ठा अणु
			/** AMDGPU_HW_IP_* */
			__u32 type;
			/**
			 * Index of the IP अगर there are more IPs of the same
			 * type. Ignored by AMDGPU_INFO_HW_IP_COUNT.
			 */
			__u32 ip_instance;
		पूर्ण query_hw_ip;

		काष्ठा अणु
			__u32 dword_offset;
			/** number of रेजिस्टरs to पढ़ो */
			__u32 count;
			__u32 instance;
			/** For future use, no flags defined so far */
			__u32 flags;
		पूर्ण पढ़ो_mmr_reg;

		काष्ठा drm_amdgpu_query_fw query_fw;

		काष्ठा अणु
			__u32 type;
			__u32 offset;
		पूर्ण vbios_info;

		काष्ठा अणु
			__u32 type;
		पूर्ण sensor_info;

		काष्ठा अणु
			__u32 type;
		पूर्ण video_cap;
	पूर्ण;
पूर्ण;

काष्ठा drm_amdgpu_info_gds अणु
	/** GDS GFX partition size */
	__u32 gds_gfx_partition_size;
	/** GDS compute partition size */
	__u32 compute_partition_size;
	/** total GDS memory size */
	__u32 gds_total_size;
	/** GWS size per GFX partition */
	__u32 gws_per_gfx_partition;
	/** GSW size per compute partition */
	__u32 gws_per_compute_partition;
	/** OA size per GFX partition */
	__u32 oa_per_gfx_partition;
	/** OA size per compute partition */
	__u32 oa_per_compute_partition;
	__u32 _pad;
पूर्ण;

काष्ठा drm_amdgpu_info_vram_gtt अणु
	__u64 vram_size;
	__u64 vram_cpu_accessible_size;
	__u64 gtt_size;
पूर्ण;

काष्ठा drm_amdgpu_heap_info अणु
	/** max. physical memory */
	__u64 total_heap_size;

	/** Theoretical max. available memory in the given heap */
	__u64 usable_heap_size;

	/**
	 * Number of bytes allocated in the heap. This includes all processes
	 * and निजी allocations in the kernel. It changes when new buffers
	 * are allocated, मुक्तd, and moved. It cannot be larger than
	 * heap_size.
	 */
	__u64 heap_usage;

	/**
	 * Theoretical possible max. size of buffer which
	 * could be allocated in the given heap
	 */
	__u64 max_allocation;
पूर्ण;

काष्ठा drm_amdgpu_memory_info अणु
	काष्ठा drm_amdgpu_heap_info vram;
	काष्ठा drm_amdgpu_heap_info cpu_accessible_vram;
	काष्ठा drm_amdgpu_heap_info gtt;
पूर्ण;

काष्ठा drm_amdgpu_info_firmware अणु
	__u32 ver;
	__u32 feature;
पूर्ण;

#घोषणा AMDGPU_VRAM_TYPE_UNKNOWN 0
#घोषणा AMDGPU_VRAM_TYPE_GDDR1 1
#घोषणा AMDGPU_VRAM_TYPE_DDR2  2
#घोषणा AMDGPU_VRAM_TYPE_GDDR3 3
#घोषणा AMDGPU_VRAM_TYPE_GDDR4 4
#घोषणा AMDGPU_VRAM_TYPE_GDDR5 5
#घोषणा AMDGPU_VRAM_TYPE_HBM   6
#घोषणा AMDGPU_VRAM_TYPE_DDR3  7
#घोषणा AMDGPU_VRAM_TYPE_DDR4  8
#घोषणा AMDGPU_VRAM_TYPE_GDDR6 9
#घोषणा AMDGPU_VRAM_TYPE_DDR5  10

काष्ठा drm_amdgpu_info_device अणु
	/** PCI Device ID */
	__u32 device_id;
	/** Internal chip revision: A0, A1, etc.) */
	__u32 chip_rev;
	__u32 बाह्यal_rev;
	/** Revision id in PCI Config space */
	__u32 pci_rev;
	__u32 family;
	__u32 num_shader_engines;
	__u32 num_shader_arrays_per_engine;
	/* in KHz */
	__u32 gpu_counter_freq;
	__u64 max_engine_घड़ी;
	__u64 max_memory_घड़ी;
	/* cu inक्रमmation */
	__u32 cu_active_number;
	/* NOTE: cu_ao_mask is INVALID, DON'T use it */
	__u32 cu_ao_mask;
	__u32 cu_biपंचांगap[4][4];
	/** Render backend pipe mask. One render backend is CB+DB. */
	__u32 enabled_rb_pipes_mask;
	__u32 num_rb_pipes;
	__u32 num_hw_gfx_contexts;
	__u32 _pad;
	__u64 ids_flags;
	/** Starting भव address क्रम UMDs. */
	__u64 भव_address_offset;
	/** The maximum भव address */
	__u64 भव_address_max;
	/** Required alignment of भव addresses. */
	__u32 भव_address_alignment;
	/** Page table entry - fragment size */
	__u32 pte_fragment_size;
	__u32 gart_page_size;
	/** स्थिरant engine ram size*/
	__u32 ce_ram_size;
	/** video memory type info*/
	__u32 vram_type;
	/** video memory bit width*/
	__u32 vram_bit_width;
	/* vce harvesting instance */
	__u32 vce_harvest_config;
	/* gfx द्विगुन offchip LDS buffers */
	__u32 gc_द्विगुन_offchip_lds_buf;
	/* NGG Primitive Buffer */
	__u64 prim_buf_gpu_addr;
	/* NGG Position Buffer */
	__u64 pos_buf_gpu_addr;
	/* NGG Control Sideband */
	__u64 cntl_sb_buf_gpu_addr;
	/* NGG Parameter Cache */
	__u64 param_buf_gpu_addr;
	__u32 prim_buf_size;
	__u32 pos_buf_size;
	__u32 cntl_sb_buf_size;
	__u32 param_buf_size;
	/* wavefront size*/
	__u32 wave_front_size;
	/* shader visible vgprs*/
	__u32 num_shader_visible_vgprs;
	/* CU per shader array*/
	__u32 num_cu_per_sh;
	/* number of tcc blocks*/
	__u32 num_tcc_blocks;
	/* gs vgt table depth*/
	__u32 gs_vgt_table_depth;
	/* gs primitive buffer depth*/
	__u32 gs_prim_buffer_depth;
	/* max gs wavefront per vgt*/
	__u32 max_gs_waves_per_vgt;
	__u32 _pad1;
	/* always on cu biपंचांगap */
	__u32 cu_ao_biपंचांगap[4][4];
	/** Starting high भव address क्रम UMDs. */
	__u64 high_va_offset;
	/** The maximum high भव address */
	__u64 high_va_max;
	/* gfx10 pa_sc_tile_steering_override */
	__u32 pa_sc_tile_steering_override;
	/* disabled TCCs */
	__u64 tcc_disabled_mask;
पूर्ण;

काष्ठा drm_amdgpu_info_hw_ip अणु
	/** Version of h/w IP */
	__u32  hw_ip_version_major;
	__u32  hw_ip_version_minor;
	/** Capabilities */
	__u64  capabilities_flags;
	/** command buffer address start alignment*/
	__u32  ib_start_alignment;
	/** command buffer size alignment*/
	__u32  ib_size_alignment;
	/** Biपंचांगask of available rings. Bit 0 means ring 0, etc. */
	__u32  available_rings;
	__u32  _pad;
पूर्ण;

काष्ठा drm_amdgpu_info_num_handles अणु
	/** Max handles as supported by firmware क्रम UVD */
	__u32  uvd_max_handles;
	/** Handles currently in use क्रम UVD */
	__u32  uvd_used_handles;
पूर्ण;

#घोषणा AMDGPU_VCE_CLOCK_TABLE_ENTRIES		6

काष्ठा drm_amdgpu_info_vce_घड़ी_प्रकारable_entry अणु
	/** System घड़ी */
	__u32 sclk;
	/** Memory घड़ी */
	__u32 mclk;
	/** VCE घड़ी */
	__u32 eclk;
	__u32 pad;
पूर्ण;

काष्ठा drm_amdgpu_info_vce_घड़ी_प्रकारable अणु
	काष्ठा drm_amdgpu_info_vce_घड़ी_प्रकारable_entry entries[AMDGPU_VCE_CLOCK_TABLE_ENTRIES];
	__u32 num_valid_entries;
	__u32 pad;
पूर्ण;

/* query video encode/decode caps */
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG2			0
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4			1
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VC1			2
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_MPEG4_AVC		3
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_HEVC			4
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_JPEG			5
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_VP9			6
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_AV1			7
#घोषणा AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_COUNT			8

काष्ठा drm_amdgpu_info_video_codec_info अणु
	__u32 valid;
	__u32 max_width;
	__u32 max_height;
	__u32 max_pixels_per_frame;
	__u32 max_level;
	__u32 pad;
पूर्ण;

काष्ठा drm_amdgpu_info_video_caps अणु
	काष्ठा drm_amdgpu_info_video_codec_info codec_info[AMDGPU_INFO_VIDEO_CAPS_CODEC_IDX_COUNT];
पूर्ण;

/*
 * Supported GPU families
 */
#घोषणा AMDGPU_FAMILY_UNKNOWN			0
#घोषणा AMDGPU_FAMILY_SI			110 /* Hainan, Oland, Verde, Pitcairn, Tahiti */
#घोषणा AMDGPU_FAMILY_CI			120 /* Bonaire, Hawaii */
#घोषणा AMDGPU_FAMILY_KV			125 /* Kaveri, Kabini, Mullins */
#घोषणा AMDGPU_FAMILY_VI			130 /* Iceland, Tonga */
#घोषणा AMDGPU_FAMILY_CZ			135 /* Carrizo, Stoney */
#घोषणा AMDGPU_FAMILY_AI			141 /* Vega10 */
#घोषणा AMDGPU_FAMILY_RV			142 /* Raven */
#घोषणा AMDGPU_FAMILY_NV			143 /* Navi10 */
#घोषणा AMDGPU_FAMILY_VGH			144 /* Van Gogh */

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
