<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * ARC firmware पूर्णांकerface.
 *
 * Copyright (C) 1994, 1995, 1996, 1999 Ralf Baechle
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */

#समावेश <यंत्र/fw/arc/types.h>
#समावेश <यंत्र/sgialib.h>

LONG
ArcRead(ULONG FileID, VOID *Buffer, ULONG N, ULONG *Count)
अणु
	वापस ARC_CALL4(पढ़ो, FileID, Buffer, N, Count);
पूर्ण

LONG
ArcWrite(ULONG FileID, PVOID Buffer, ULONG N, PULONG Count)
अणु
	वापस ARC_CALL4(ग_लिखो, FileID, Buffer, N, Count);
पूर्ण
