<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 */

/*
 * GPU करोorbell काष्ठाures, functions & helpers
 */
काष्ठा amdgpu_करोorbell अणु
	/* करोorbell mmio */
	resource_माप_प्रकार		base;
	resource_माप_प्रकार		size;
	u32 __iomem		*ptr;
	u32			num_करोorbells;	/* Number of करोorbells actually reserved क्रम amdgpu. */
पूर्ण;

/* Reserved करोorbells क्रम amdgpu (including mulसमयdia).
 * KFD can use all the rest in the 2M करोorbell bar.
 * For asic beक्रमe vega10, करोorbell is 32-bit, so the
 * index/offset is in dword. For vega10 and after, करोorbell
 * can be 64-bit, so the index defined is in qword.
 */
काष्ठा amdgpu_करोorbell_index अणु
	uपूर्णांक32_t kiq;
	uपूर्णांक32_t mec_ring0;
	uपूर्णांक32_t mec_ring1;
	uपूर्णांक32_t mec_ring2;
	uपूर्णांक32_t mec_ring3;
	uपूर्णांक32_t mec_ring4;
	uपूर्णांक32_t mec_ring5;
	uपूर्णांक32_t mec_ring6;
	uपूर्णांक32_t mec_ring7;
	uपूर्णांक32_t userqueue_start;
	uपूर्णांक32_t userqueue_end;
	uपूर्णांक32_t gfx_ring0;
	uपूर्णांक32_t gfx_ring1;
	uपूर्णांक32_t sdma_engine[8];
	uपूर्णांक32_t mes_ring;
	uपूर्णांक32_t ih;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक32_t vcn_ring0_1;
			uपूर्णांक32_t vcn_ring2_3;
			uपूर्णांक32_t vcn_ring4_5;
			uपूर्णांक32_t vcn_ring6_7;
		पूर्ण vcn;
		काष्ठा अणु
			uपूर्णांक32_t uvd_ring0_1;
			uपूर्णांक32_t uvd_ring2_3;
			uपूर्णांक32_t uvd_ring4_5;
			uपूर्णांक32_t uvd_ring6_7;
			uपूर्णांक32_t vce_ring0_1;
			uपूर्णांक32_t vce_ring2_3;
			uपूर्णांक32_t vce_ring4_5;
			uपूर्णांक32_t vce_ring6_7;
		पूर्ण uvd_vce;
	पूर्ण;
	uपूर्णांक32_t first_non_cp;
	uपूर्णांक32_t last_non_cp;
	uपूर्णांक32_t max_assignment;
	/* Per engine SDMA करोorbell size in dword */
	uपूर्णांक32_t sdma_करोorbell_range;
पूर्ण;

प्रकार क्रमागत _AMDGPU_DOORBELL_ASSIGNMENT
अणु
	AMDGPU_DOORBELL_KIQ                     = 0x000,
	AMDGPU_DOORBELL_HIQ                     = 0x001,
	AMDGPU_DOORBELL_DIQ                     = 0x002,
	AMDGPU_DOORBELL_MEC_RING0               = 0x010,
	AMDGPU_DOORBELL_MEC_RING1               = 0x011,
	AMDGPU_DOORBELL_MEC_RING2               = 0x012,
	AMDGPU_DOORBELL_MEC_RING3               = 0x013,
	AMDGPU_DOORBELL_MEC_RING4               = 0x014,
	AMDGPU_DOORBELL_MEC_RING5               = 0x015,
	AMDGPU_DOORBELL_MEC_RING6               = 0x016,
	AMDGPU_DOORBELL_MEC_RING7               = 0x017,
	AMDGPU_DOORBELL_GFX_RING0               = 0x020,
	AMDGPU_DOORBELL_sDMA_ENGINE0            = 0x1E0,
	AMDGPU_DOORBELL_sDMA_ENGINE1            = 0x1E1,
	AMDGPU_DOORBELL_IH                      = 0x1E8,
	AMDGPU_DOORBELL_MAX_ASSIGNMENT          = 0x3FF,
	AMDGPU_DOORBELL_INVALID                 = 0xFFFF
पूर्ण AMDGPU_DOORBELL_ASSIGNMENT;

प्रकार क्रमागत _AMDGPU_VEGA20_DOORBELL_ASSIGNMENT
अणु
	/* Compute + GFX: 0~255 */
	AMDGPU_VEGA20_DOORBELL_KIQ                     = 0x000,
	AMDGPU_VEGA20_DOORBELL_HIQ                     = 0x001,
	AMDGPU_VEGA20_DOORBELL_DIQ                     = 0x002,
	AMDGPU_VEGA20_DOORBELL_MEC_RING0               = 0x003,
	AMDGPU_VEGA20_DOORBELL_MEC_RING1               = 0x004,
	AMDGPU_VEGA20_DOORBELL_MEC_RING2               = 0x005,
	AMDGPU_VEGA20_DOORBELL_MEC_RING3               = 0x006,
	AMDGPU_VEGA20_DOORBELL_MEC_RING4               = 0x007,
	AMDGPU_VEGA20_DOORBELL_MEC_RING5               = 0x008,
	AMDGPU_VEGA20_DOORBELL_MEC_RING6               = 0x009,
	AMDGPU_VEGA20_DOORBELL_MEC_RING7               = 0x00A,
	AMDGPU_VEGA20_DOORBELL_USERQUEUE_START	       = 0x00B,
	AMDGPU_VEGA20_DOORBELL_USERQUEUE_END	       = 0x08A,
	AMDGPU_VEGA20_DOORBELL_GFX_RING0               = 0x08B,
	/* SDMA:256~335*/
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE0            = 0x100,
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE1            = 0x10A,
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE2            = 0x114,
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE3            = 0x11E,
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE4            = 0x128,
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE5            = 0x132,
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE6            = 0x13C,
	AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE7            = 0x146,
	/* IH: 376~391 */
	AMDGPU_VEGA20_DOORBELL_IH                      = 0x178,
	/* MMSCH: 392~407
	 * overlap the करोorbell assignment with VCN as they are  mutually exclusive
	 * VCN engine's करोorbell is 32 bit and two VCN ring share one QWORD
	 */
	AMDGPU_VEGA20_DOORBELL64_VCN0_1                  = 0x188, /* VNC0 */
	AMDGPU_VEGA20_DOORBELL64_VCN2_3                  = 0x189,
	AMDGPU_VEGA20_DOORBELL64_VCN4_5                  = 0x18A,
	AMDGPU_VEGA20_DOORBELL64_VCN6_7                  = 0x18B,

	AMDGPU_VEGA20_DOORBELL64_VCN8_9                  = 0x18C, /* VNC1 */
	AMDGPU_VEGA20_DOORBELL64_VCNa_b                  = 0x18D,
	AMDGPU_VEGA20_DOORBELL64_VCNc_d                  = 0x18E,
	AMDGPU_VEGA20_DOORBELL64_VCNe_f                  = 0x18F,

	AMDGPU_VEGA20_DOORBELL64_UVD_RING0_1             = 0x188,
	AMDGPU_VEGA20_DOORBELL64_UVD_RING2_3             = 0x189,
	AMDGPU_VEGA20_DOORBELL64_UVD_RING4_5             = 0x18A,
	AMDGPU_VEGA20_DOORBELL64_UVD_RING6_7             = 0x18B,

	AMDGPU_VEGA20_DOORBELL64_VCE_RING0_1             = 0x18C,
	AMDGPU_VEGA20_DOORBELL64_VCE_RING2_3             = 0x18D,
	AMDGPU_VEGA20_DOORBELL64_VCE_RING4_5             = 0x18E,
	AMDGPU_VEGA20_DOORBELL64_VCE_RING6_7             = 0x18F,

	AMDGPU_VEGA20_DOORBELL64_FIRST_NON_CP            = AMDGPU_VEGA20_DOORBELL_sDMA_ENGINE0,
	AMDGPU_VEGA20_DOORBELL64_LAST_NON_CP             = AMDGPU_VEGA20_DOORBELL64_VCE_RING6_7,

	AMDGPU_VEGA20_DOORBELL_MAX_ASSIGNMENT            = 0x18F,
	AMDGPU_VEGA20_DOORBELL_INVALID                   = 0xFFFF
पूर्ण AMDGPU_VEGA20_DOORBELL_ASSIGNMENT;

प्रकार क्रमागत _AMDGPU_NAVI10_DOORBELL_ASSIGNMENT
अणु
	/* Compute + GFX: 0~255 */
	AMDGPU_NAVI10_DOORBELL_KIQ			= 0x000,
	AMDGPU_NAVI10_DOORBELL_HIQ			= 0x001,
	AMDGPU_NAVI10_DOORBELL_DIQ			= 0x002,
	AMDGPU_NAVI10_DOORBELL_MEC_RING0		= 0x003,
	AMDGPU_NAVI10_DOORBELL_MEC_RING1		= 0x004,
	AMDGPU_NAVI10_DOORBELL_MEC_RING2		= 0x005,
	AMDGPU_NAVI10_DOORBELL_MEC_RING3		= 0x006,
	AMDGPU_NAVI10_DOORBELL_MEC_RING4		= 0x007,
	AMDGPU_NAVI10_DOORBELL_MEC_RING5		= 0x008,
	AMDGPU_NAVI10_DOORBELL_MEC_RING6		= 0x009,
	AMDGPU_NAVI10_DOORBELL_MEC_RING7		= 0x00A,
	AMDGPU_NAVI10_DOORBELL_USERQUEUE_START		= 0x00B,
	AMDGPU_NAVI10_DOORBELL_USERQUEUE_END		= 0x08A,
	AMDGPU_NAVI10_DOORBELL_GFX_RING0		= 0x08B,
	AMDGPU_NAVI10_DOORBELL_GFX_RING1		= 0x08C,
	AMDGPU_NAVI10_DOORBELL_MES_RING		        = 0x090,
	/* SDMA:256~335*/
	AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE0		= 0x100,
	AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE1		= 0x10A,
	AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE2		= 0x114,
	AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE3		= 0x11E,
	/* IH: 376~391 */
	AMDGPU_NAVI10_DOORBELL_IH			= 0x178,
	/* MMSCH: 392~407
	 * overlap the करोorbell assignment with VCN as they are  mutually exclusive
	 * VCE engine's करोorbell is 32 bit and two VCE ring share one QWORD
	 */
	AMDGPU_NAVI10_DOORBELL64_VCN0_1			= 0x188, /* lower 32 bits क्रम VNC0 and upper 32 bits क्रम VNC1 */
	AMDGPU_NAVI10_DOORBELL64_VCN2_3			= 0x189,
	AMDGPU_NAVI10_DOORBELL64_VCN4_5			= 0x18A,
	AMDGPU_NAVI10_DOORBELL64_VCN6_7			= 0x18B,

	AMDGPU_NAVI10_DOORBELL64_VCN8_9			= 0x18C,
	AMDGPU_NAVI10_DOORBELL64_VCNa_b			= 0x18D,
	AMDGPU_NAVI10_DOORBELL64_VCNc_d			= 0x18E,
	AMDGPU_NAVI10_DOORBELL64_VCNe_f			= 0x18F,

	AMDGPU_NAVI10_DOORBELL64_FIRST_NON_CP		= AMDGPU_NAVI10_DOORBELL_sDMA_ENGINE0,
	AMDGPU_NAVI10_DOORBELL64_LAST_NON_CP		= AMDGPU_NAVI10_DOORBELL64_VCNe_f,

	AMDGPU_NAVI10_DOORBELL_MAX_ASSIGNMENT		= 0x18F,
	AMDGPU_NAVI10_DOORBELL_INVALID			= 0xFFFF
पूर्ण AMDGPU_NAVI10_DOORBELL_ASSIGNMENT;

/*
 * 64bit करोorbell, offset are in QWORD, occupy 2KB करोorbell space
 */
प्रकार क्रमागत _AMDGPU_DOORBELL64_ASSIGNMENT
अणु
	/*
	 * All compute related करोorbells: kiq, hiq, diq, traditional compute queue, user queue, should locate in
	 * a जारीs range so that programming CP_MEC_DOORBELL_RANGE_LOWER/UPPER can cover this range.
	 *  Compute related करोorbells are allocated from 0x00 to 0x8a
	 */


	/* kernel scheduling */
	AMDGPU_DOORBELL64_KIQ                     = 0x00,

	/* HSA पूर्णांकerface queue and debug queue */
	AMDGPU_DOORBELL64_HIQ                     = 0x01,
	AMDGPU_DOORBELL64_DIQ                     = 0x02,

	/* Compute engines */
	AMDGPU_DOORBELL64_MEC_RING0               = 0x03,
	AMDGPU_DOORBELL64_MEC_RING1               = 0x04,
	AMDGPU_DOORBELL64_MEC_RING2               = 0x05,
	AMDGPU_DOORBELL64_MEC_RING3               = 0x06,
	AMDGPU_DOORBELL64_MEC_RING4               = 0x07,
	AMDGPU_DOORBELL64_MEC_RING5               = 0x08,
	AMDGPU_DOORBELL64_MEC_RING6               = 0x09,
	AMDGPU_DOORBELL64_MEC_RING7               = 0x0a,

	/* User queue करोorbell range (128 करोorbells) */
	AMDGPU_DOORBELL64_USERQUEUE_START         = 0x0b,
	AMDGPU_DOORBELL64_USERQUEUE_END           = 0x8a,

	/* Graphics engine */
	AMDGPU_DOORBELL64_GFX_RING0               = 0x8b,

	/*
	 * Other graphics करोorbells can be allocated here: from 0x8c to 0xdf
	 * Graphics voltage island aperture 1
	 * शेष non-graphics QWORD index is 0xe0 - 0xFF inclusive
	 */

	/* For vega10 sriov, the sdma करोorbell must be fixed as follow
	 * to keep the same setting with host driver, or it will
	 * happen conflicts
	 */
	AMDGPU_DOORBELL64_sDMA_ENGINE0            = 0xF0,
	AMDGPU_DOORBELL64_sDMA_HI_PRI_ENGINE0     = 0xF1,
	AMDGPU_DOORBELL64_sDMA_ENGINE1            = 0xF2,
	AMDGPU_DOORBELL64_sDMA_HI_PRI_ENGINE1     = 0xF3,

	/* Interrupt handler */
	AMDGPU_DOORBELL64_IH                      = 0xF4,  /* For legacy पूर्णांकerrupt ring buffer */
	AMDGPU_DOORBELL64_IH_RING1                = 0xF5,  /* For page migration request log */
	AMDGPU_DOORBELL64_IH_RING2                = 0xF6,  /* For page migration translation/invalidation log */

	/* VCN engine use 32 bits करोorbell  */
	AMDGPU_DOORBELL64_VCN0_1                  = 0xF8, /* lower 32 bits क्रम VNC0 and upper 32 bits क्रम VNC1 */
	AMDGPU_DOORBELL64_VCN2_3                  = 0xF9,
	AMDGPU_DOORBELL64_VCN4_5                  = 0xFA,
	AMDGPU_DOORBELL64_VCN6_7                  = 0xFB,

	/* overlap the करोorbell assignment with VCN as they are  mutually exclusive
	 * VCE engine's करोorbell is 32 bit and two VCE ring share one QWORD
	 */
	AMDGPU_DOORBELL64_UVD_RING0_1             = 0xF8,
	AMDGPU_DOORBELL64_UVD_RING2_3             = 0xF9,
	AMDGPU_DOORBELL64_UVD_RING4_5             = 0xFA,
	AMDGPU_DOORBELL64_UVD_RING6_7             = 0xFB,

	AMDGPU_DOORBELL64_VCE_RING0_1             = 0xFC,
	AMDGPU_DOORBELL64_VCE_RING2_3             = 0xFD,
	AMDGPU_DOORBELL64_VCE_RING4_5             = 0xFE,
	AMDGPU_DOORBELL64_VCE_RING6_7             = 0xFF,

	AMDGPU_DOORBELL64_FIRST_NON_CP            = AMDGPU_DOORBELL64_sDMA_ENGINE0,
	AMDGPU_DOORBELL64_LAST_NON_CP             = AMDGPU_DOORBELL64_VCE_RING6_7,

	AMDGPU_DOORBELL64_MAX_ASSIGNMENT          = 0xFF,
	AMDGPU_DOORBELL64_INVALID                 = 0xFFFF
पूर्ण AMDGPU_DOORBELL64_ASSIGNMENT;

u32 amdgpu_mm_rकरोorbell(काष्ठा amdgpu_device *adev, u32 index);
व्योम amdgpu_mm_wकरोorbell(काष्ठा amdgpu_device *adev, u32 index, u32 v);
u64 amdgpu_mm_rकरोorbell64(काष्ठा amdgpu_device *adev, u32 index);
व्योम amdgpu_mm_wकरोorbell64(काष्ठा amdgpu_device *adev, u32 index, u64 v);

#घोषणा RDOORBELL32(index) amdgpu_mm_rकरोorbell(adev, (index))
#घोषणा WDOORBELL32(index, v) amdgpu_mm_wकरोorbell(adev, (index), (v))
#घोषणा RDOORBELL64(index) amdgpu_mm_rकरोorbell64(adev, (index))
#घोषणा WDOORBELL64(index, v) amdgpu_mm_wकरोorbell64(adev, (index), (v))

