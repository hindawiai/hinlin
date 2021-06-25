<शैली गुरु>
/*
 * Derived from (and probably identical to):
 * ftl.h 1.7 1999/10/25 20:23:17
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License.
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in
 * which हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use
 * your version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#अगर_अघोषित _LINUX_FTL_H
#घोषणा _LINUX_FTL_H

प्रकार काष्ठा erase_unit_header_t अणु
    uपूर्णांक8_t	LinkTargetTuple[5];
    uपूर्णांक8_t	DataOrgTuple[10];
    uपूर्णांक8_t	NumTransferUnits;
    uपूर्णांक32_t	EraseCount;
    uपूर्णांक16_t	LogicalEUN;
    uपूर्णांक8_t	BlockSize;
    uपूर्णांक8_t	EraseUnitSize;
    uपूर्णांक16_t	FirstPhysicalEUN;
    uपूर्णांक16_t	NumEraseUnits;
    uपूर्णांक32_t	FormattedSize;
    uपूर्णांक32_t	FirstVMAddress;
    uपूर्णांक16_t	NumVMPages;
    uपूर्णांक8_t	Flags;
    uपूर्णांक8_t	Code;
    uपूर्णांक32_t	SerialNumber;
    uपूर्णांक32_t	AltEUHOffset;
    uपूर्णांक32_t	BAMOffset;
    uपूर्णांक8_t	Reserved[12];
    uपूर्णांक8_t	EndTuple[2];
पूर्ण erase_unit_header_t;

/* Flags in erase_unit_header_t */
#घोषणा HIDDEN_AREA		0x01
#घोषणा REVERSE_POLARITY	0x02
#घोषणा DOUBLE_BAI		0x04

/* Definitions क्रम block allocation inक्रमmation */

#घोषणा BLOCK_FREE(b)		((b) == 0xffffffff)
#घोषणा BLOCK_DELETED(b)	(((b) == 0) || ((b) == 0xfffffffe))

#घोषणा BLOCK_TYPE(b)		((b) & 0x7f)
#घोषणा BLOCK_ADDRESS(b)	((b) & ~0x7f)
#घोषणा BLOCK_NUMBER(b)		((b) >> 9)
#घोषणा BLOCK_CONTROL		0x30
#घोषणा BLOCK_DATA		0x40
#घोषणा BLOCK_REPLACEMENT	0x60
#घोषणा BLOCK_BAD		0x70

#पूर्ण_अगर /* _LINUX_FTL_H */
