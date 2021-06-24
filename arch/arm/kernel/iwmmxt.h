<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __IWMMXT_H__
#घोषणा __IWMMXT_H__

.irp b, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
.set .LwR\म, \म
.set .Lr\म, \म
.endr

.set .LwCSSF, 0x2
.set .LwCASF, 0x3
.set .LwCGR0, 0x8
.set .LwCGR1, 0x9
.set .LwCGR2, 0xa
.set .LwCGR3, 0xb

.macro wldrd, reg:req, base:req, offset:req
.inst 0xedd00100 | (.L\लeg << 12) | (.L\मase << 16) | (\offset >> 2)
.endm

.macro wldrw, reg:req, base:req, offset:req
.inst 0xfd900100 | (.L\लeg << 12) | (.L\मase << 16) | (\offset >> 2)
.endm

.macro wstrd, reg:req, base:req, offset:req
.inst 0xedc00100 | (.L\लeg << 12) | (.L\मase << 16) | (\offset >> 2)
.endm

.macro wstrw, reg:req, base:req, offset:req
.inst 0xfd800100 | (.L\लeg << 12) | (.L\मase << 16) | (\offset >> 2)
.endm

#अगर_घोषित __clang__

#घोषणा wCon c1

.macro पंचांगrc, dest:req, control:req
mrc p1, 0, \dest, \control, c0, 0
.endm

.macro पंचांगcr, control:req, src:req
mcr p1, 0, \src, \control, c0, 0
.endm
#पूर्ण_अगर

#पूर्ण_अगर
