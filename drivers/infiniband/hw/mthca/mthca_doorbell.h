<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
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

#समावेश <linux/types.h>

#घोषणा MTHCA_RD_DOORBELL      0x00
#घोषणा MTHCA_SEND_DOORBELL    0x10
#घोषणा MTHCA_RECEIVE_DOORBELL 0x18
#घोषणा MTHCA_CQ_DOORBELL      0x20
#घोषणा MTHCA_EQ_DOORBELL      0x28

#अगर BITS_PER_LONG == 64
/*
 * Assume that we can just ग_लिखो a 64-bit करोorbell atomically.  s390
 * actually करोesn't have writeq() but S/390 systems don't even have
 * PCI so we won't worry about it.
 */

#घोषणा MTHCA_DECLARE_DOORBELL_LOCK(name)
#घोषणा MTHCA_INIT_DOORBELL_LOCK(ptr)    करो अणु पूर्ण जबतक (0)
#घोषणा MTHCA_GET_DOORBELL_LOCK(ptr)      (शून्य)

अटल अंतरभूत व्योम mthca_ग_लिखो64_raw(__be64 val, व्योम __iomem *dest)
अणु
	__raw_ग_लिखोq((__क्रमce u64) val, dest);
पूर्ण

अटल अंतरभूत व्योम mthca_ग_लिखो64(u32 hi, u32 lo, व्योम __iomem *dest,
				 spinlock_t *करोorbell_lock)
अणु
	__raw_ग_लिखोq((__क्रमce u64) cpu_to_be64((u64) hi << 32 | lo), dest);
पूर्ण

अटल अंतरभूत व्योम mthca_ग_लिखो_db_rec(__be32 val[2], __be32 *db)
अणु
	*(u64 *) db = *(u64 *) val;
पूर्ण

#अन्यथा

/*
 * Just fall back to a spinlock to protect the करोorbell अगर
 * BITS_PER_LONG is 32 -- there's no portable way to करो atomic 64-bit
 * MMIO ग_लिखोs.
 */

#घोषणा MTHCA_DECLARE_DOORBELL_LOCK(name) spinlock_t name;
#घोषणा MTHCA_INIT_DOORBELL_LOCK(ptr)     spin_lock_init(ptr)
#घोषणा MTHCA_GET_DOORBELL_LOCK(ptr)      (ptr)

अटल अंतरभूत व्योम mthca_ग_लिखो64_raw(__be64 val, व्योम __iomem *dest)
अणु
	__raw_ग_लिखोl(((__क्रमce u32 *) &val)[0], dest);
	__raw_ग_लिखोl(((__क्रमce u32 *) &val)[1], dest + 4);
पूर्ण

अटल अंतरभूत व्योम mthca_ग_लिखो64(u32 hi, u32 lo, व्योम __iomem *dest,
				 spinlock_t *करोorbell_lock)
अणु
	अचिन्हित दीर्घ flags;

	hi = (__क्रमce u32) cpu_to_be32(hi);
	lo = (__क्रमce u32) cpu_to_be32(lo);

	spin_lock_irqsave(करोorbell_lock, flags);
	__raw_ग_लिखोl(hi, dest);
	__raw_ग_लिखोl(lo, dest + 4);
	spin_unlock_irqrestore(करोorbell_lock, flags);
पूर्ण

अटल अंतरभूत व्योम mthca_ग_लिखो_db_rec(__be32 val[2], __be32 *db)
अणु
	db[0] = val[0];
	wmb();
	db[1] = val[1];
पूर्ण

#पूर्ण_अगर
