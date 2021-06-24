<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 */

#समावेश "dc/dc_stat.h"
#समावेश "dmub/dmub_srv_stat.h"
#समावेश "dc_dmub_srv.h"

/**
 * DOC: DC STAT Interface
 *
 * These पूर्णांकerfaces are called without acquiring DAL and DC locks.
 * Hence, there is limitations on whese पूर्णांकerfaces can access. Only
 * variables exclusively defined क्रम these पूर्णांकerfaces can be modअगरied.
 */

/**
 *****************************************************************************
 *  Function: dc_stat_get_dmub_notअगरication
 *
 *  @brief
 *		Calls dmub layer to retrieve dmub notअगरication
 *
 *  @param
 *		[in] dc: dc काष्ठाure
 *		[in] notअगरy: dmub notअगरication काष्ठाure
 *
 *  @वापस
 *     None
 *****************************************************************************
 */
व्योम dc_stat_get_dmub_notअगरication(स्थिर काष्ठा dc *dc, काष्ठा dmub_notअगरication *notअगरy)
अणु
	/**
	 * This function is called without dal and dc locks, so
	 * we shall not modअगरy any dc, dc_dmub_srv or dmub variables
	 * except variables exclusively accessed by this function
	 */
	काष्ठा dmub_srv *dmub = dc->ctx->dmub_srv->dmub;
	क्रमागत dmub_status status;

	status = dmub_srv_stat_get_notअगरication(dmub, notअगरy);
	ASSERT(status == DMUB_STATUS_OK);
पूर्ण
