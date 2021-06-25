<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित MLX5_DOORBELL_H
#घोषणा MLX5_DOORBELL_H

#घोषणा MLX5_BF_OFFSET	      0x800
#घोषणा MLX5_CQ_DOORBELL      0x20

/* Assume that we can just ग_लिखो a 64-bit करोorbell atomically.  s390
 * actually करोesn't have writeq() but S/390 systems don't even have
 * PCI so we won't worry about it.
 *
 * Note that the ग_लिखो is not atomic on 32-bit प्रणालीs! In contrast to 64-bit
 * ones, it requires proper locking. mlx5_ग_लिखो64 करोesn't करो any locking, so use
 * it at your own discretion, रक्षित by some kind of lock on 32 bits.
 *
 * TODO: use ग_लिखोअणुq,lपूर्ण_relaxed()
 */

अटल अंतरभूत व्योम mlx5_ग_लिखो64(__be32 val[2], व्योम __iomem *dest)
अणु
#अगर BITS_PER_LONG == 64
	__raw_ग_लिखोq(*(u64 *)val, dest);
#अन्यथा
	__raw_ग_लिखोl((__क्रमce u32) val[0], dest);
	__raw_ग_लिखोl((__क्रमce u32) val[1], dest + 4);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* MLX5_DOORBELL_H */
