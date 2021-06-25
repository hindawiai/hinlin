<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/त्रुटिसं.स>

#समावेश "mthca_dev.h"

पूर्णांक mthca_pd_alloc(काष्ठा mthca_dev *dev, पूर्णांक privileged, काष्ठा mthca_pd *pd)
अणु
	पूर्णांक err = 0;

	pd->privileged = privileged;

	atomic_set(&pd->sqp_count, 0);
	pd->pd_num = mthca_alloc(&dev->pd_table.alloc);
	अगर (pd->pd_num == -1)
		वापस -ENOMEM;

	अगर (privileged) अणु
		err = mthca_mr_alloc_notrans(dev, pd->pd_num,
					     MTHCA_MPT_FLAG_LOCAL_READ |
					     MTHCA_MPT_FLAG_LOCAL_WRITE,
					     &pd->nपंचांगr);
		अगर (err)
			mthca_मुक्त(&dev->pd_table.alloc, pd->pd_num);
	पूर्ण

	वापस err;
पूर्ण

व्योम mthca_pd_मुक्त(काष्ठा mthca_dev *dev, काष्ठा mthca_pd *pd)
अणु
	अगर (pd->privileged)
		mthca_मुक्त_mr(dev, &pd->nपंचांगr);
	mthca_मुक्त(&dev->pd_table.alloc, pd->pd_num);
पूर्ण

पूर्णांक mthca_init_pd_table(काष्ठा mthca_dev *dev)
अणु
	वापस mthca_alloc_init(&dev->pd_table.alloc,
				dev->limits.num_pds,
				(1 << 24) - 1,
				dev->limits.reserved_pds);
पूर्ण

व्योम mthca_cleanup_pd_table(काष्ठा mthca_dev *dev)
अणु
	/* XXX check अगर any PDs are still allocated? */
	mthca_alloc_cleanup(&dev->pd_table.alloc);
पूर्ण
