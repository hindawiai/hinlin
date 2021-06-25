<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Functions क्रम assembling fcx enabled I/O control blocks.
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
#समावेश "cio.h"

/**
 * tcw_get_पूर्णांकrg - वापस poपूर्णांकer to associated पूर्णांकerrogate tcw
 * @tcw: poपूर्णांकer to the original tcw
 *
 * Return a poपूर्णांकer to the पूर्णांकerrogate tcw associated with the specअगरied tcw
 * or %शून्य अगर there is no associated पूर्णांकerrogate tcw.
 */
काष्ठा tcw *tcw_get_पूर्णांकrg(काष्ठा tcw *tcw)
अणु
	वापस (काष्ठा tcw *) ((addr_t) tcw->पूर्णांकrg);
पूर्ण
EXPORT_SYMBOL(tcw_get_पूर्णांकrg);

/**
 * tcw_get_data - वापस poपूर्णांकer to input/output data associated with tcw
 * @tcw: poपूर्णांकer to the tcw
 *
 * Return the input or output data address specअगरied in the tcw depending
 * on whether the r-bit or the w-bit is set. If neither bit is set, वापस
 * %शून्य.
 */
व्योम *tcw_get_data(काष्ठा tcw *tcw)
अणु
	अगर (tcw->r)
		वापस (व्योम *) ((addr_t) tcw->input);
	अगर (tcw->w)
		वापस (व्योम *) ((addr_t) tcw->output);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(tcw_get_data);

/**
 * tcw_get_tccb - वापस poपूर्णांकer to tccb associated with tcw
 * @tcw: poपूर्णांकer to the tcw
 *
 * Return poपूर्णांकer to the tccb associated with this tcw.
 */
काष्ठा tccb *tcw_get_tccb(काष्ठा tcw *tcw)
अणु
	वापस (काष्ठा tccb *) ((addr_t) tcw->tccb);
पूर्ण
EXPORT_SYMBOL(tcw_get_tccb);

/**
 * tcw_get_tsb - वापस poपूर्णांकer to tsb associated with tcw
 * @tcw: poपूर्णांकer to the tcw
 *
 * Return poपूर्णांकer to the tsb associated with this tcw.
 */
काष्ठा tsb *tcw_get_tsb(काष्ठा tcw *tcw)
अणु
	वापस (काष्ठा tsb *) ((addr_t) tcw->tsb);
पूर्ण
EXPORT_SYMBOL(tcw_get_tsb);

/**
 * tcw_init - initialize tcw data काष्ठाure
 * @tcw: poपूर्णांकer to the tcw to be initialized
 * @r: initial value of the r-bit
 * @w: initial value of the w-bit
 *
 * Initialize all fields of the specअगरied tcw data काष्ठाure with zero and
 * fill in the क्रमmat, flags, r and w fields.
 */
व्योम tcw_init(काष्ठा tcw *tcw, पूर्णांक r, पूर्णांक w)
अणु
	स_रखो(tcw, 0, माप(काष्ठा tcw));
	tcw->क्रमmat = TCW_FORMAT_DEFAULT;
	tcw->flags = TCW_FLAGS_TIDAW_FORMAT(TCW_TIDAW_FORMAT_DEFAULT);
	अगर (r)
		tcw->r = 1;
	अगर (w)
		tcw->w = 1;
पूर्ण
EXPORT_SYMBOL(tcw_init);

अटल अंतरभूत माप_प्रकार tca_size(काष्ठा tccb *tccb)
अणु
	वापस tccb->tcah.tcal - 12;
पूर्ण

अटल u32 calc_dcw_count(काष्ठा tccb *tccb)
अणु
	पूर्णांक offset;
	काष्ठा dcw *dcw;
	u32 count = 0;
	माप_प्रकार size;

	size = tca_size(tccb);
	क्रम (offset = 0; offset < size;) अणु
		dcw = (काष्ठा dcw *) &tccb->tca[offset];
		count += dcw->count;
		अगर (!(dcw->flags & DCW_FLAGS_CC))
			अवरोध;
		offset += माप(काष्ठा dcw) + ALIGN((पूर्णांक) dcw->cd_count, 4);
	पूर्ण
	वापस count;
पूर्ण

अटल u32 calc_cbc_size(काष्ठा tidaw *tidaw, पूर्णांक num)
अणु
	पूर्णांक i;
	u32 cbc_data;
	u32 cbc_count = 0;
	u64 data_count = 0;

	क्रम (i = 0; i < num; i++) अणु
		अगर (tidaw[i].flags & TIDAW_FLAGS_LAST)
			अवरोध;
		/* TODO: find out अगर padding applies to total of data
		 * transferred or data transferred by this tidaw. Assumption:
		 * applies to total. */
		data_count += tidaw[i].count;
		अगर (tidaw[i].flags & TIDAW_FLAGS_INSERT_CBC) अणु
			cbc_data = 4 + ALIGN(data_count, 4) - data_count;
			cbc_count += cbc_data;
			data_count += cbc_data;
		पूर्ण
	पूर्ण
	वापस cbc_count;
पूर्ण

/**
 * tcw_finalize - finalize tcw length fields and tidaw list
 * @tcw: poपूर्णांकer to the tcw
 * @num_tidaws: the number of tidaws used to address input/output data or zero
 * अगर no tida is used
 *
 * Calculate the input-/output-count and tccbl field in the tcw, add a
 * tcat the tccb and terminate the data tidaw list अगर used.
 *
 * Note: in हाल input- or output-tida is used, the tidaw-list must be stored
 * in contiguous storage (no ttic). The tcal field in the tccb must be
 * up-to-date.
 */
व्योम tcw_finalize(काष्ठा tcw *tcw, पूर्णांक num_tidaws)
अणु
	काष्ठा tidaw *tidaw;
	काष्ठा tccb *tccb;
	काष्ठा tccb_tcat *tcat;
	u32 count;

	/* Terminate tidaw list. */
	tidaw = tcw_get_data(tcw);
	अगर (num_tidaws > 0)
		tidaw[num_tidaws - 1].flags |= TIDAW_FLAGS_LAST;
	/* Add tcat to tccb. */
	tccb = tcw_get_tccb(tcw);
	tcat = (काष्ठा tccb_tcat *) &tccb->tca[tca_size(tccb)];
	स_रखो(tcat, 0, माप(*tcat));
	/* Calculate tcw input/output count and tcat transport count. */
	count = calc_dcw_count(tccb);
	अगर (tcw->w && (tcw->flags & TCW_FLAGS_OUTPUT_TIDA))
		count += calc_cbc_size(tidaw, num_tidaws);
	अगर (tcw->r)
		tcw->input_count = count;
	अन्यथा अगर (tcw->w)
		tcw->output_count = count;
	tcat->count = ALIGN(count, 4) + 4;
	/* Calculate tccbl. */
	tcw->tccbl = (माप(काष्ठा tccb) + tca_size(tccb) +
		      माप(काष्ठा tccb_tcat) - 20) >> 2;
पूर्ण
EXPORT_SYMBOL(tcw_finalize);

/**
 * tcw_set_पूर्णांकrg - set the पूर्णांकerrogate tcw address of a tcw
 * @tcw: the tcw address
 * @पूर्णांकrg_tcw: the address of the पूर्णांकerrogate tcw
 *
 * Set the address of the पूर्णांकerrogate tcw in the specअगरied tcw.
 */
व्योम tcw_set_पूर्णांकrg(काष्ठा tcw *tcw, काष्ठा tcw *पूर्णांकrg_tcw)
अणु
	tcw->पूर्णांकrg = (u32) ((addr_t) पूर्णांकrg_tcw);
पूर्ण
EXPORT_SYMBOL(tcw_set_पूर्णांकrg);

/**
 * tcw_set_data - set data address and tida flag of a tcw
 * @tcw: the tcw address
 * @data: the data address
 * @use_tidal: zero of the data address specअगरies a contiguous block of data,
 * non-zero अगर it specअगरies a list अगर tidaws.
 *
 * Set the input/output data address of a tcw (depending on the value of the
 * r-flag and w-flag). If @use_tidal is non-zero, the corresponding tida flag
 * is set as well.
 */
व्योम tcw_set_data(काष्ठा tcw *tcw, व्योम *data, पूर्णांक use_tidal)
अणु
	अगर (tcw->r) अणु
		tcw->input = (u64) ((addr_t) data);
		अगर (use_tidal)
			tcw->flags |= TCW_FLAGS_INPUT_TIDA;
	पूर्ण अन्यथा अगर (tcw->w) अणु
		tcw->output = (u64) ((addr_t) data);
		अगर (use_tidal)
			tcw->flags |= TCW_FLAGS_OUTPUT_TIDA;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tcw_set_data);

/**
 * tcw_set_tccb - set tccb address of a tcw
 * @tcw: the tcw address
 * @tccb: the tccb address
 *
 * Set the address of the tccb in the specअगरied tcw.
 */
व्योम tcw_set_tccb(काष्ठा tcw *tcw, काष्ठा tccb *tccb)
अणु
	tcw->tccb = (u64) ((addr_t) tccb);
पूर्ण
EXPORT_SYMBOL(tcw_set_tccb);

/**
 * tcw_set_tsb - set tsb address of a tcw
 * @tcw: the tcw address
 * @tsb: the tsb address
 *
 * Set the address of the tsb in the specअगरied tcw.
 */
व्योम tcw_set_tsb(काष्ठा tcw *tcw, काष्ठा tsb *tsb)
अणु
	tcw->tsb = (u64) ((addr_t) tsb);
पूर्ण
EXPORT_SYMBOL(tcw_set_tsb);

/**
 * tccb_init - initialize tccb
 * @tccb: the tccb address
 * @size: the maximum size of the tccb
 * @sac: the service-action-code to be user
 *
 * Initialize the header of the specअगरied tccb by resetting all values to zero
 * and filling in शेषs क्रम क्रमmat, sac and initial tcal fields.
 */
व्योम tccb_init(काष्ठा tccb *tccb, माप_प्रकार size, u32 sac)
अणु
	स_रखो(tccb, 0, size);
	tccb->tcah.क्रमmat = TCCB_FORMAT_DEFAULT;
	tccb->tcah.sac = sac;
	tccb->tcah.tcal = 12;
पूर्ण
EXPORT_SYMBOL(tccb_init);

/**
 * tsb_init - initialize tsb
 * @tsb: the tsb address
 *
 * Initialize the specअगरied tsb by resetting all values to zero.
 */
व्योम tsb_init(काष्ठा tsb *tsb)
अणु
	स_रखो(tsb, 0, माप(*tsb));
पूर्ण
EXPORT_SYMBOL(tsb_init);

/**
 * tccb_add_dcw - add a dcw to the tccb
 * @tccb: the tccb address
 * @tccb_size: the maximum tccb size
 * @cmd: the dcw command
 * @flags: flags क्रम the dcw
 * @cd: poपूर्णांकer to control data क्रम this dcw or शून्य अगर none is required
 * @cd_count: number of control data bytes क्रम this dcw
 * @count: number of data bytes क्रम this dcw
 *
 * Add a new dcw to the specअगरied tccb by writing the dcw inक्रमmation specअगरied
 * by @cmd, @flags, @cd, @cd_count and @count to the tca of the tccb. Return
 * a poपूर्णांकer to the newly added dcw on success or -%ENOSPC अगर the new dcw
 * would exceed the available space as defined by @tccb_size.
 *
 * Note: the tcal field of the tccb header will be updates to reflect added
 * content.
 */
काष्ठा dcw *tccb_add_dcw(काष्ठा tccb *tccb, माप_प्रकार tccb_size, u8 cmd, u8 flags,
			 व्योम *cd, u8 cd_count, u32 count)
अणु
	काष्ठा dcw *dcw;
	पूर्णांक size;
	पूर्णांक tca_offset;

	/* Check क्रम space. */
	tca_offset = tca_size(tccb);
	size = ALIGN(माप(काष्ठा dcw) + cd_count, 4);
	अगर (माप(काष्ठा tccb_tcah) + tca_offset + size +
	    माप(काष्ठा tccb_tcat) > tccb_size)
		वापस ERR_PTR(-ENOSPC);
	/* Add dcw to tca. */
	dcw = (काष्ठा dcw *) &tccb->tca[tca_offset];
	स_रखो(dcw, 0, size);
	dcw->cmd = cmd;
	dcw->flags = flags;
	dcw->count = count;
	dcw->cd_count = cd_count;
	अगर (cd)
		स_नकल(&dcw->cd[0], cd, cd_count);
	tccb->tcah.tcal += size;
	वापस dcw;
पूर्ण
EXPORT_SYMBOL(tccb_add_dcw);

/**
 * tcw_add_tidaw - add a tidaw to a tcw
 * @tcw: the tcw address
 * @num_tidaws: the current number of tidaws
 * @flags: flags क्रम the new tidaw
 * @addr: address value क्रम the new tidaw
 * @count: count value क्रम the new tidaw
 *
 * Add a new tidaw to the input/output data tidaw-list of the specअगरied tcw
 * (depending on the value of the r-flag and w-flag) and वापस a poपूर्णांकer to
 * the new tidaw.
 *
 * Note: the tidaw-list is assumed to be contiguous with no ttics. The caller
 * must ensure that there is enough space क्रम the new tidaw. The last-tidaw
 * flag क्रम the last tidaw in the list will be set by tcw_finalize.
 */
काष्ठा tidaw *tcw_add_tidaw(काष्ठा tcw *tcw, पूर्णांक num_tidaws, u8 flags,
			    व्योम *addr, u32 count)
अणु
	काष्ठा tidaw *tidaw;

	/* Add tidaw to tidaw-list. */
	tidaw = ((काष्ठा tidaw *) tcw_get_data(tcw)) + num_tidaws;
	स_रखो(tidaw, 0, माप(काष्ठा tidaw));
	tidaw->flags = flags;
	tidaw->count = count;
	tidaw->addr = (u64) ((addr_t) addr);
	वापस tidaw;
पूर्ण
EXPORT_SYMBOL(tcw_add_tidaw);
