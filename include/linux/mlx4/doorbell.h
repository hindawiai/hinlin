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

#अगर_अघोषित MLX4_DOORBELL_H
#घोषणा MLX4_DOORBELL_H

#समावेश <linux/types.h>
#समावेश <linux/पन.स>

#घोषणा MLX4_SEND_DOORBELL    0x14
#घोषणा MLX4_CQ_DOORBELL      0x20

#अगर BITS_PER_LONG == 64
/*
 * Assume that we can just ग_लिखो a 64-bit करोorbell atomically.  s390
 * actually करोesn't have writeq() but S/390 systems don't even have
 * PCI so we won't worry about it.
 */

#घोषणा MLX4_DECLARE_DOORBELL_LOCK(name)
#घोषणा MLX4_INIT_DOORBELL_LOCK(ptr)    करो अणु पूर्ण जबतक (0)
#घोषणा MLX4_GET_DOORBELL_LOCK(ptr)      (शून्य)

अटल अंतरभूत व्योम mlx4_ग_लिखो64(__be32 val[2], व्योम __iomem *dest,
				spinlock_t *करोorbell_lock)
अणु
	__raw_ग_लिखोq(*(u64 *) val, dest);
पूर्ण

#अन्यथा

/*
 * Just fall back to a spinlock to protect the करोorbell अगर
 * BITS_PER_LONG is 32 -- there's no portable way to करो atomic 64-bit
 * MMIO ग_लिखोs.
 */

#घोषणा MLX4_DECLARE_DOORBELL_LOCK(name) spinlock_t name;
#घोषणा MLX4_INIT_DOORBELL_LOCK(ptr)     spin_lock_init(ptr)
#घोषणा MLX4_GET_DOORBELL_LOCK(ptr)      (ptr)

अटल अंतरभूत व्योम mlx4_ग_लिखो64(__be32 val[2], व्योम __iomem *dest,
				spinlock_t *करोorbell_lock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(करोorbell_lock, flags);
	__raw_ग_लिखोl((__क्रमce u32) val[0], dest);
	__raw_ग_लिखोl((__क्रमce u32) val[1], dest + 4);
	spin_unlock_irqrestore(करोorbell_lock, flags);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* MLX4_DOORBELL_H */
