<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Functions क्रम incremental स्थिरruction of fcx enabled I/O control blocks.
 *
 *    Copyright IBM Corp. 2008
 *    Author(s): Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/fcx.h>
#समावेश <यंत्र/itcw.h>

/*
 * काष्ठा itcw - incremental tcw helper data type
 *
 * This काष्ठाure serves as a handle क्रम the incremental स्थिरruction of a
 * tcw and associated tccb, tsb, data tidaw-list plus an optional पूर्णांकerrogate
 * tcw and associated data. The data काष्ठाures are contained inside a single
 * contiguous buffer provided by the user.
 *
 * The itcw स्थिरruction functions take care of overall data पूर्णांकegrity:
 * - reset unused fields to zero
 * - fill in required poपूर्णांकers
 * - ensure required alignment क्रम data काष्ठाures
 * - prevent data काष्ठाures to cross 4k-byte boundary where required
 * - calculate tccb-related length fields
 * - optionally provide पढ़ोy-made पूर्णांकerrogate tcw and associated काष्ठाures
 *
 * Restrictions apply to the itcws created with these स्थिरruction functions:
 * - tida only supported क्रम data address, not क्रम tccb
 * - only contiguous tidaw-lists (no ttic)
 * - total number of bytes required per itcw may not exceed 4k bytes
 * - either पढ़ो or ग_लिखो operation (may not work with r=0 and w=0)
 *
 * Example:
 * काष्ठा itcw *itcw;
 * व्योम *buffer;
 * माप_प्रकार size;
 *
 * size = itcw_calc_size(1, 2, 0);
 * buffer = kदो_स्मृति(size, GFP_KERNEL | GFP_DMA);
 * अगर (!buffer)
 *	वापस -ENOMEM;
 * itcw = itcw_init(buffer, size, ITCW_OP_READ, 1, 2, 0);
 * अगर (IS_ERR(itcw))
 *	वापस PTR_ER(itcw);
 * itcw_add_dcw(itcw, 0x2, 0, शून्य, 0, 72);
 * itcw_add_tidaw(itcw, 0, 0x30000, 20);
 * itcw_add_tidaw(itcw, 0, 0x40000, 52);
 * itcw_finalize(itcw);
 *
 */
काष्ठा itcw अणु
	काष्ठा tcw *tcw;
	काष्ठा tcw *पूर्णांकrg_tcw;
	पूर्णांक num_tidaws;
	पूर्णांक max_tidaws;
	पूर्णांक पूर्णांकrg_num_tidaws;
	पूर्णांक पूर्णांकrg_max_tidaws;
पूर्ण;

/**
 * itcw_get_tcw - वापस poपूर्णांकer to tcw associated with the itcw
 * @itcw: address of the itcw
 *
 * Return poपूर्णांकer to the tcw associated with the itcw.
 */
काष्ठा tcw *itcw_get_tcw(काष्ठा itcw *itcw)
अणु
	वापस itcw->tcw;
पूर्ण
EXPORT_SYMBOL(itcw_get_tcw);

/**
 * itcw_calc_size - वापस the size of an itcw with the given parameters
 * @पूर्णांकrg: अगर non-zero, add an पूर्णांकerrogate tcw
 * @max_tidaws: maximum number of tidaws to be used क्रम data addressing or zero
 * अगर no tida is to be used.
 * @पूर्णांकrg_max_tidaws: maximum number of tidaws to be used क्रम data addressing
 * by the पूर्णांकerrogate tcw, अगर specअगरied
 *
 * Calculate and वापस the number of bytes required to hold an itcw with the
 * given parameters and assuming tccbs with maximum size.
 *
 * Note that the resulting size also contains bytes needed क्रम alignment
 * padding as well as padding to ensure that data काष्ठाures करोn't cross a
 * 4k-boundary where required.
 */
माप_प्रकार itcw_calc_size(पूर्णांक पूर्णांकrg, पूर्णांक max_tidaws, पूर्णांक पूर्णांकrg_max_tidaws)
अणु
	माप_प्रकार len;
	पूर्णांक cross_count;

	/* Main data. */
	len = माप(काष्ठा itcw);
	len += /* TCW */ माप(काष्ठा tcw) + /* TCCB */ TCCB_MAX_SIZE +
	       /* TSB */ माप(काष्ठा tsb) +
	       /* TIDAL */ max_tidaws * माप(काष्ठा tidaw);
	/* Interrogate data. */
	अगर (पूर्णांकrg) अणु
		len += /* TCW */ माप(काष्ठा tcw) + /* TCCB */ TCCB_MAX_SIZE +
		       /* TSB */ माप(काष्ठा tsb) +
		       /* TIDAL */ पूर्णांकrg_max_tidaws * माप(काष्ठा tidaw);
	पूर्ण

	/* Maximum required alignment padding. */
	len += /* Initial TCW */ 63 + /* Interrogate TCCB */ 7;

	/* TIDAW lists may not cross a 4k boundary. To cross a
	 * boundary we need to add a TTIC TIDAW. We need to reserve
	 * one additional TIDAW क्रम a TTIC that we may need to add due
	 * to the placement of the data chunk in memory, and a further
	 * TIDAW क्रम each page boundary that the TIDAW list may cross
	 * due to it's own size.
	 */
	अगर (max_tidaws) अणु
		cross_count = 1 + ((max_tidaws * माप(काष्ठा tidaw) - 1)
				   >> PAGE_SHIFT);
		len += cross_count * माप(काष्ठा tidaw);
	पूर्ण
	अगर (पूर्णांकrg_max_tidaws) अणु
		cross_count = 1 + ((पूर्णांकrg_max_tidaws * माप(काष्ठा tidaw) - 1)
				   >> PAGE_SHIFT);
		len += cross_count * माप(काष्ठा tidaw);
	पूर्ण
	वापस len;
पूर्ण
EXPORT_SYMBOL(itcw_calc_size);

#घोषणा CROSS4K(x, l)	(((x) & ~4095) != ((x + l) & ~4095))

अटल अंतरभूत व्योम *fit_chunk(addr_t *start, addr_t end, माप_प्रकार len,
			      पूर्णांक align, पूर्णांक check_4k)
अणु
	addr_t addr;

	addr = ALIGN(*start, align);
	अगर (check_4k && CROSS4K(addr, len)) अणु
		addr = ALIGN(addr, 4096);
		addr = ALIGN(addr, align);
	पूर्ण
	अगर (addr + len > end)
		वापस ERR_PTR(-ENOSPC);
	*start = addr + len;
	वापस (व्योम *) addr;
पूर्ण

/**
 * itcw_init - initialize incremental tcw data काष्ठाure
 * @buffer: address of buffer to use क्रम data काष्ठाures
 * @size: number of bytes in buffer
 * @op: %ITCW_OP_READ क्रम a पढ़ो operation tcw, %ITCW_OP_WRITE क्रम a ग_लिखो
 * operation tcw
 * @पूर्णांकrg: अगर non-zero, add and initialize an पूर्णांकerrogate tcw
 * @max_tidaws: maximum number of tidaws to be used क्रम data addressing or zero
 * अगर no tida is to be used.
 * @पूर्णांकrg_max_tidaws: maximum number of tidaws to be used क्रम data addressing
 * by the पूर्णांकerrogate tcw, अगर specअगरied
 *
 * Prepare the specअगरied buffer to be used as an incremental tcw, i.e. a
 * helper data काष्ठाure that can be used to स्थिरruct a valid tcw by
 * successive calls to other helper functions. Note: the buffer needs to be
 * located below the 2G address limit. The resulting tcw has the following
 * restrictions:
 *  - no tccb tidal
 *  - input/output tidal is contiguous (no ttic)
 *  - total data should not exceed 4k
 *  - tcw specअगरies either पढ़ो or ग_लिखो operation
 *
 * On success, वापस poपूर्णांकer to the resulting incremental tcw data काष्ठाure,
 * ERR_PTR otherwise.
 */
काष्ठा itcw *itcw_init(व्योम *buffer, माप_प्रकार size, पूर्णांक op, पूर्णांक पूर्णांकrg,
		       पूर्णांक max_tidaws, पूर्णांक पूर्णांकrg_max_tidaws)
अणु
	काष्ठा itcw *itcw;
	व्योम *chunk;
	addr_t start;
	addr_t end;
	पूर्णांक cross_count;

	/* Check क्रम 2G limit. */
	start = (addr_t) buffer;
	end = start + size;
	अगर (end > (1 << 31))
		वापस ERR_PTR(-EINVAL);
	स_रखो(buffer, 0, size);
	/* ITCW. */
	chunk = fit_chunk(&start, end, माप(काष्ठा itcw), 1, 0);
	अगर (IS_ERR(chunk))
		वापस chunk;
	itcw = chunk;
	/* allow क्रम TTIC tidaws that may be needed to cross a page boundary */
	cross_count = 0;
	अगर (max_tidaws)
		cross_count = 1 + ((max_tidaws * माप(काष्ठा tidaw) - 1)
				   >> PAGE_SHIFT);
	itcw->max_tidaws = max_tidaws + cross_count;
	cross_count = 0;
	अगर (पूर्णांकrg_max_tidaws)
		cross_count = 1 + ((पूर्णांकrg_max_tidaws * माप(काष्ठा tidaw) - 1)
				   >> PAGE_SHIFT);
	itcw->पूर्णांकrg_max_tidaws = पूर्णांकrg_max_tidaws + cross_count;
	/* Main TCW. */
	chunk = fit_chunk(&start, end, माप(काष्ठा tcw), 64, 0);
	अगर (IS_ERR(chunk))
		वापस chunk;
	itcw->tcw = chunk;
	tcw_init(itcw->tcw, (op == ITCW_OP_READ) ? 1 : 0,
		 (op == ITCW_OP_WRITE) ? 1 : 0);
	/* Interrogate TCW. */
	अगर (पूर्णांकrg) अणु
		chunk = fit_chunk(&start, end, माप(काष्ठा tcw), 64, 0);
		अगर (IS_ERR(chunk))
			वापस chunk;
		itcw->पूर्णांकrg_tcw = chunk;
		tcw_init(itcw->पूर्णांकrg_tcw, 1, 0);
		tcw_set_पूर्णांकrg(itcw->tcw, itcw->पूर्णांकrg_tcw);
	पूर्ण
	/* Data TIDAL. */
	अगर (max_tidaws > 0) अणु
		chunk = fit_chunk(&start, end, माप(काष्ठा tidaw) *
				  itcw->max_tidaws, 16, 0);
		अगर (IS_ERR(chunk))
			वापस chunk;
		tcw_set_data(itcw->tcw, chunk, 1);
	पूर्ण
	/* Interrogate data TIDAL. */
	अगर (पूर्णांकrg && (पूर्णांकrg_max_tidaws > 0)) अणु
		chunk = fit_chunk(&start, end, माप(काष्ठा tidaw) *
				  itcw->पूर्णांकrg_max_tidaws, 16, 0);
		अगर (IS_ERR(chunk))
			वापस chunk;
		tcw_set_data(itcw->पूर्णांकrg_tcw, chunk, 1);
	पूर्ण
	/* TSB. */
	chunk = fit_chunk(&start, end, माप(काष्ठा tsb), 8, 0);
	अगर (IS_ERR(chunk))
		वापस chunk;
	tsb_init(chunk);
	tcw_set_tsb(itcw->tcw, chunk);
	/* Interrogate TSB. */
	अगर (पूर्णांकrg) अणु
		chunk = fit_chunk(&start, end, माप(काष्ठा tsb), 8, 0);
		अगर (IS_ERR(chunk))
			वापस chunk;
		tsb_init(chunk);
		tcw_set_tsb(itcw->पूर्णांकrg_tcw, chunk);
	पूर्ण
	/* TCCB. */
	chunk = fit_chunk(&start, end, TCCB_MAX_SIZE, 8, 0);
	अगर (IS_ERR(chunk))
		वापस chunk;
	tccb_init(chunk, TCCB_MAX_SIZE, TCCB_SAC_DEFAULT);
	tcw_set_tccb(itcw->tcw, chunk);
	/* Interrogate TCCB. */
	अगर (पूर्णांकrg) अणु
		chunk = fit_chunk(&start, end, TCCB_MAX_SIZE, 8, 0);
		अगर (IS_ERR(chunk))
			वापस chunk;
		tccb_init(chunk, TCCB_MAX_SIZE, TCCB_SAC_INTRG);
		tcw_set_tccb(itcw->पूर्णांकrg_tcw, chunk);
		tccb_add_dcw(chunk, TCCB_MAX_SIZE, DCW_CMD_INTRG, 0, शून्य,
			     माप(काष्ठा dcw_पूर्णांकrg_data), 0);
		tcw_finalize(itcw->पूर्णांकrg_tcw, 0);
	पूर्ण
	वापस itcw;
पूर्ण
EXPORT_SYMBOL(itcw_init);

/**
 * itcw_add_dcw - add a dcw to the itcw
 * @itcw: address of the itcw
 * @cmd: the dcw command
 * @flags: flags क्रम the dcw
 * @cd: address of control data क्रम this dcw or शून्य अगर none is required
 * @cd_count: number of control data bytes क्रम this dcw
 * @count: number of data bytes क्रम this dcw
 *
 * Add a new dcw to the specअगरied itcw by writing the dcw inक्रमmation specअगरied
 * by @cmd, @flags, @cd, @cd_count and @count to the tca of the tccb. Return
 * a poपूर्णांकer to the newly added dcw on success or -%ENOSPC अगर the new dcw
 * would exceed the available space.
 *
 * Note: the tcal field of the tccb header will be updated to reflect added
 * content.
 */
काष्ठा dcw *itcw_add_dcw(काष्ठा itcw *itcw, u8 cmd, u8 flags, व्योम *cd,
			 u8 cd_count, u32 count)
अणु
	वापस tccb_add_dcw(tcw_get_tccb(itcw->tcw), TCCB_MAX_SIZE, cmd,
			    flags, cd, cd_count, count);
पूर्ण
EXPORT_SYMBOL(itcw_add_dcw);

/**
 * itcw_add_tidaw - add a tidaw to the itcw
 * @itcw: address of the itcw
 * @flags: flags क्रम the new tidaw
 * @addr: address value क्रम the new tidaw
 * @count: count value क्रम the new tidaw
 *
 * Add a new tidaw to the input/output data tidaw-list of the specअगरied itcw
 * (depending on the value of the r-flag and w-flag). Return a poपूर्णांकer to
 * the new tidaw on success or -%ENOSPC अगर the new tidaw would exceed the
 * available space.
 *
 * Note: TTIC tidaws are स्वतःmatically added when needed, so explicitly calling
 * this पूर्णांकerface with the TTIC flag is not supported. The last-tidaw flag
 * क्रम the last tidaw in the list will be set by itcw_finalize.
 */
काष्ठा tidaw *itcw_add_tidaw(काष्ठा itcw *itcw, u8 flags, व्योम *addr, u32 count)
अणु
	काष्ठा tidaw *following;

	अगर (itcw->num_tidaws >= itcw->max_tidaws)
		वापस ERR_PTR(-ENOSPC);
	/*
	 * Is the tidaw, which follows the one we are about to fill, on the next
	 * page? Then we have to insert a TTIC tidaw first, that poपूर्णांकs to the
	 * tidaw on the new page.
	 */
	following = ((काष्ठा tidaw *) tcw_get_data(itcw->tcw))
		+ itcw->num_tidaws + 1;
	अगर (itcw->num_tidaws && !((अचिन्हित दीर्घ) following & ~PAGE_MASK)) अणु
		tcw_add_tidaw(itcw->tcw, itcw->num_tidaws++,
			      TIDAW_FLAGS_TTIC, following, 0);
		अगर (itcw->num_tidaws >= itcw->max_tidaws)
			वापस ERR_PTR(-ENOSPC);
	पूर्ण
	वापस tcw_add_tidaw(itcw->tcw, itcw->num_tidaws++, flags, addr, count);
पूर्ण
EXPORT_SYMBOL(itcw_add_tidaw);

/**
 * itcw_set_data - set data address and tida flag of the itcw
 * @itcw: address of the itcw
 * @addr: the data address
 * @use_tidal: zero of the data address specअगरies a contiguous block of data,
 * non-zero अगर it specअगरies a list अगर tidaws.
 *
 * Set the input/output data address of the itcw (depending on the value of the
 * r-flag and w-flag). If @use_tidal is non-zero, the corresponding tida flag
 * is set as well.
 */
व्योम itcw_set_data(काष्ठा itcw *itcw, व्योम *addr, पूर्णांक use_tidal)
अणु
	tcw_set_data(itcw->tcw, addr, use_tidal);
पूर्ण
EXPORT_SYMBOL(itcw_set_data);

/**
 * itcw_finalize - calculate length and count fields of the itcw
 * @itcw: address of the itcw
 *
 * Calculate tcw input-/output-count and tccbl fields and add a tcat the tccb.
 * In हाल input- or output-tida is used, the tidaw-list must be stored in
 * continuous storage (no ttic). The tcal field in the tccb must be
 * up-to-date.
 */
व्योम itcw_finalize(काष्ठा itcw *itcw)
अणु
	tcw_finalize(itcw->tcw, itcw->num_tidaws);
पूर्ण
EXPORT_SYMBOL(itcw_finalize);
