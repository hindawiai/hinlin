<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  arch/arm/include/यंत्र/byteorder.h
 *
 * ARM Endian-ness.  In little endian mode, the data bus is connected such
 * that byte accesses appear as:
 *  0 = d0...d7, 1 = d8...d15, 2 = d16...d23, 3 = d24...d31
 * and word accesses (data or inकाष्ठाion) appear as:
 *  d0...d31
 *
 * When in big endian mode, byte accesses appear as:
 *  0 = d24...d31, 1 = d16...d23, 2 = d8...d15, 3 = d0...d7
 * and word accesses (data or inकाष्ठाion) appear as:
 *  d0...d31
 */
#अगर_अघोषित __ASM_ARM_BYTEORDER_H
#घोषणा __ASM_ARM_BYTEORDER_H

#अगर_घोषित __ARMEB__
#समावेश <linux/byteorder/big_endian.h>
#अन्यथा
#समावेश <linux/byteorder/little_endian.h>
#पूर्ण_अगर

#पूर्ण_अगर

