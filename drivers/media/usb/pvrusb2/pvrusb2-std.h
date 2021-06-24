<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_STD_H
#घोषणा __PVRUSB2_STD_H

#समावेश <linux/videodev2.h>

// Convert string describing one or more video standards पूर्णांकo a mask of V4L
// standard bits.  Return true अगर conversion succeeds otherwise वापस
// false.  String is expected to be of the क्रमm: C1-x/y;C2-a/b where C1 and
// C2 are color प्रणाली names (e.g. "PAL", "NTSC") and x, y, a, and b are
// modulation schemes (e.g. "M", "B", "G", etc).
पूर्णांक pvr2_std_str_to_id(v4l2_std_id *idPtr,स्थिर अक्षर *bufPtr,
		       अचिन्हित पूर्णांक bufSize);

// Convert any arbitrary set of video standard bits पूर्णांकo an unambiguous
// पढ़ोable string.  Return value is the number of bytes consumed in the
// buffer.  The क्रमmatted string is of a क्रमm that can be parsed by our
// sibling std_std_to_id() function.
अचिन्हित पूर्णांक pvr2_std_id_to_str(अक्षर *bufPtr, अचिन्हित पूर्णांक bufSize,
				v4l2_std_id id);

// Create an array of suitable v4l2_standard काष्ठाures given a bit mask of
// video standards to support.  The array is allocated from the heap, and
// the number of elements is वापसed in the first argument.
काष्ठा v4l2_standard *pvr2_std_create_क्रमागत(अचिन्हित पूर्णांक *countptr,
					   v4l2_std_id id);

// Return mask of which video standard bits are valid
v4l2_std_id pvr2_std_get_usable(व्योम);

#पूर्ण_अगर /* __PVRUSB2_STD_H */
