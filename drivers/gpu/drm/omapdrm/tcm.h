<शैली गुरु>
/*
 * TILER container manager specअगरication and support functions क्रम TI
 * TILER driver.
 *
 * Author: Lajos Molnar <molnar@ti.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   करोcumentation and/or other materials provided with the distribution.
 *
 * * Neither the name of Texas Instruments Incorporated nor the names of
 *   its contributors may be used to enकरोrse or promote products derived
 *   from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित TCM_H
#घोषणा TCM_H

काष्ठा tcm;

/* poपूर्णांक */
काष्ठा tcm_pt अणु
	u16 x;
	u16 y;
पूर्ण;

/* 1d or 2d area */
काष्ठा tcm_area अणु
	bool is2d;		/* whether area is 1d or 2d */
	काष्ठा tcm    *tcm;	/* parent */
	काष्ठा tcm_pt  p0;
	काष्ठा tcm_pt  p1;
पूर्ण;

काष्ठा tcm अणु
	u16 width, height;	/* container dimensions */
	पूर्णांक lut_id;		/* Lookup table identअगरier */

	अचिन्हित पूर्णांक y_offset;	/* offset to use क्रम y coordinates */

	spinlock_t lock;
	अचिन्हित दीर्घ *biपंचांगap;
	माप_प्रकार map_size;

	/* function table */
	s32 (*reserve_2d)(काष्ठा tcm *tcm, u16 height, u16 width, u16 align,
			  s16 offset, u16 slot_bytes,
			  काष्ठा tcm_area *area);
	s32 (*reserve_1d)(काष्ठा tcm *tcm, u32 slots, काष्ठा tcm_area *area);
	s32 (*मुक्त)(काष्ठा tcm *tcm, काष्ठा tcm_area *area);
	व्योम (*deinit)(काष्ठा tcm *tcm);
पूर्ण;

/*=============================================================================
    BASIC TILER CONTAINER MANAGER INTERFACE
=============================================================================*/

/*
 * NOTE:
 *
 * Since some basic parameter checking is करोne outside the TCM algorithms,
 * TCM implementation करो NOT have to check the following:
 *
 *   area poपूर्णांकer is शून्य
 *   width and height fits within container
 *   number of pages is more than the size of the container
 *
 */

काष्ठा tcm *sita_init(u16 width, u16 height);


/**
 * Deinitialize tiler container manager.
 *
 * @param tcm	Poपूर्णांकer to container manager.
 *
 * @वापस 0 on success, non-0 error value on error.  The call
 *	   should मुक्त as much memory as possible and meaningful
 *	   even on failure.  Some error codes: -ENODEV: invalid
 *	   manager.
 */
अटल अंतरभूत व्योम tcm_deinit(काष्ठा tcm *tcm)
अणु
	अगर (tcm)
		tcm->deinit(tcm);
पूर्ण

/**
 * Reserves a 2D area in the container.
 *
 * @param tcm		Poपूर्णांकer to container manager.
 * @param height	Height(in pages) of area to be reserved.
 * @param width		Width(in pages) of area to be reserved.
 * @param align		Alignment requirement क्रम top-left corner of area. Not
 *			all values may be supported by the container manager,
 *			but it must support 0 (1), 32 and 64.
 *			0 value is equivalent to 1.
 * @param offset	Offset requirement, in bytes.  This is the offset
 *			from a 4KiB aligned भव address.
 * @param slot_bytes	Width of slot in bytes
 * @param area		Poपूर्णांकer to where the reserved area should be stored.
 *
 * @वापस 0 on success.  Non-0 error code on failure.  Also,
 *	   the tcm field of the area will be set to शून्य on
 *	   failure.  Some error codes: -ENODEV: invalid manager,
 *	   -EINVAL: invalid area, -ENOMEM: not enough space क्रम
 *	    allocation.
 */
अटल अंतरभूत s32 tcm_reserve_2d(काष्ठा tcm *tcm, u16 width, u16 height,
				u16 align, s16 offset, u16 slot_bytes,
				काष्ठा tcm_area *area)
अणु
	/* perक्रमm rudimentary error checking */
	s32 res = tcm  == शून्य ? -ENODEV :
		(area == शून्य || width == 0 || height == 0 ||
		 /* align must be a 2 घातer */
		 (align & (align - 1))) ? -EINVAL :
		(height > tcm->height || width > tcm->width) ? -ENOMEM : 0;

	अगर (!res) अणु
		area->is2d = true;
		res = tcm->reserve_2d(tcm, height, width, align, offset,
					slot_bytes, area);
		area->tcm = res ? शून्य : tcm;
	पूर्ण

	वापस res;
पूर्ण

/**
 * Reserves a 1D area in the container.
 *
 * @param tcm		Poपूर्णांकer to container manager.
 * @param slots		Number of (contiguous) slots to reserve.
 * @param area		Poपूर्णांकer to where the reserved area should be stored.
 *
 * @वापस 0 on success.  Non-0 error code on failure.  Also,
 *	   the tcm field of the area will be set to शून्य on
 *	   failure.  Some error codes: -ENODEV: invalid manager,
 *	   -EINVAL: invalid area, -ENOMEM: not enough space क्रम
 *	    allocation.
 */
अटल अंतरभूत s32 tcm_reserve_1d(काष्ठा tcm *tcm, u32 slots,
				 काष्ठा tcm_area *area)
अणु
	/* perक्रमm rudimentary error checking */
	s32 res = tcm  == शून्य ? -ENODEV :
		(area == शून्य || slots == 0) ? -EINVAL :
		slots > (tcm->width * (u32) tcm->height) ? -ENOMEM : 0;

	अगर (!res) अणु
		area->is2d = false;
		res = tcm->reserve_1d(tcm, slots, area);
		area->tcm = res ? शून्य : tcm;
	पूर्ण

	वापस res;
पूर्ण

/**
 * Free a previously reserved area from the container.
 *
 * @param area	Poपूर्णांकer to area reserved by a prior call to
 *		tcm_reserve_1d or tcm_reserve_2d call, whether
 *		it was successful or not. (Note: all fields of
 *		the काष्ठाure must match.)
 *
 * @वापस 0 on success.  Non-0 error code on failure.  Also, the tcm
 *	   field of the area is set to शून्य on success to aव्योम subsequent
 *	   मुक्तing.  This call will succeed even अगर supplying
 *	   the area from a failed reserved call.
 */
अटल अंतरभूत s32 tcm_मुक्त(काष्ठा tcm_area *area)
अणु
	s32 res = 0; /* मुक्त succeeds by शेष */

	अगर (area && area->tcm) अणु
		res = area->tcm->मुक्त(area->tcm, area);
		अगर (res == 0)
			area->tcm = शून्य;
	पूर्ण

	वापस res;
पूर्ण

/*=============================================================================
    HELPER FUNCTION FOR ANY TILER CONTAINER MANAGER
=============================================================================*/

/**
 * This method slices off the topmost 2D slice from the parent area, and stores
 * it in the 'slice' parameter.  The 'parent' parameter will get modअगरied to
 * contain the reमुख्यing portion of the area.  If the whole parent area can
 * fit in a 2D slice, its tcm poपूर्णांकer is set to शून्य to mark that it is no
 * दीर्घer a valid area.
 *
 * @param parent	Poपूर्णांकer to a VALID parent area that will get modअगरied
 * @param slice		Poपूर्णांकer to the slice area that will get modअगरied
 */
अटल अंतरभूत व्योम tcm_slice(काष्ठा tcm_area *parent, काष्ठा tcm_area *slice)
अणु
	*slice = *parent;

	/* check अगर we need to slice */
	अगर (slice->tcm && !slice->is2d &&
		slice->p0.y != slice->p1.y &&
		(slice->p0.x || (slice->p1.x != slice->tcm->width - 1))) अणु
		/* set end poपूर्णांक of slice (start always reमुख्यs) */
		slice->p1.x = slice->tcm->width - 1;
		slice->p1.y = (slice->p0.x) ? slice->p0.y : slice->p1.y - 1;
		/* adjust reमुख्यing area */
		parent->p0.x = 0;
		parent->p0.y = slice->p1.y + 1;
	पूर्ण अन्यथा अणु
		/* mark this as the last slice */
		parent->tcm = शून्य;
	पूर्ण
पूर्ण

/* Verअगरy अगर a tcm area is logically valid */
अटल अंतरभूत bool tcm_area_is_valid(काष्ठा tcm_area *area)
अणु
	वापस area && area->tcm &&
		/* coordinate bounds */
		area->p1.x < area->tcm->width &&
		area->p1.y < area->tcm->height &&
		area->p0.y <= area->p1.y &&
		/* 1D coordinate relationship + p0.x check */
		((!area->is2d &&
		  area->p0.x < area->tcm->width &&
		  area->p0.x + area->p0.y * area->tcm->width <=
		  area->p1.x + area->p1.y * area->tcm->width) ||
		 /* 2D coordinate relationship */
		 (area->is2d &&
		  area->p0.x <= area->p1.x));
पूर्ण

/* see अगर a coordinate is within an area */
अटल अंतरभूत bool __tcm_is_in(काष्ठा tcm_pt *p, काष्ठा tcm_area *a)
अणु
	u16 i;

	अगर (a->is2d) अणु
		वापस p->x >= a->p0.x && p->x <= a->p1.x &&
		       p->y >= a->p0.y && p->y <= a->p1.y;
	पूर्ण अन्यथा अणु
		i = p->x + p->y * a->tcm->width;
		वापस i >= a->p0.x + a->p0.y * a->tcm->width &&
		       i <= a->p1.x + a->p1.y * a->tcm->width;
	पूर्ण
पूर्ण

/* calculate area width */
अटल अंतरभूत u16 __tcm_area_width(काष्ठा tcm_area *area)
अणु
	वापस area->p1.x - area->p0.x + 1;
पूर्ण

/* calculate area height */
अटल अंतरभूत u16 __tcm_area_height(काष्ठा tcm_area *area)
अणु
	वापस area->p1.y - area->p0.y + 1;
पूर्ण

/* calculate number of slots in an area */
अटल अंतरभूत u16 __tcm_माप(काष्ठा tcm_area *area)
अणु
	वापस area->is2d ?
		__tcm_area_width(area) * __tcm_area_height(area) :
		(area->p1.x - area->p0.x + 1) + (area->p1.y - area->p0.y) *
							area->tcm->width;
पूर्ण
#घोषणा tcm_माप(area) __tcm_माप(&(area))
#घोषणा tcm_awidth(area) __tcm_area_width(&(area))
#घोषणा tcm_aheight(area) __tcm_area_height(&(area))
#घोषणा tcm_is_in(pt, area) __tcm_is_in(&(pt), &(area))

/* limit a 1D area to the first N pages */
अटल अंतरभूत s32 tcm_1d_limit(काष्ठा tcm_area *a, u32 num_pg)
अणु
	अगर (__tcm_माप(a) < num_pg)
		वापस -ENOMEM;
	अगर (!num_pg)
		वापस -EINVAL;

	a->p1.x = (a->p0.x + num_pg - 1) % a->tcm->width;
	a->p1.y = a->p0.y + ((a->p0.x + num_pg - 1) / a->tcm->width);
	वापस 0;
पूर्ण

/**
 * Iterate through 2D slices of a valid area. Behaves
 * syntactically as a क्रम(;;) statement.
 *
 * @param var		Name of a local variable of type 'काष्ठा
 *			tcm_area *' that will get modअगरied to
 *			contain each slice.
 * @param area		Poपूर्णांकer to the VALID parent area. This
 *			काष्ठाure will not get modअगरied
 *			throughout the loop.
 *
 */
#घोषणा tcm_क्रम_each_slice(var, area, safe) \
	क्रम (safe = area, \
	     tcm_slice(&safe, &var); \
	     var.tcm; tcm_slice(&safe, &var))

#पूर्ण_अगर
