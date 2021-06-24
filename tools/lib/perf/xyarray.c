<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकernal/xyarray.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

काष्ठा xyarray *xyarray__new(पूर्णांक xlen, पूर्णांक ylen, माप_प्रकार entry_size)
अणु
	माप_प्रकार row_size = ylen * entry_size;
	काष्ठा xyarray *xy = zalloc(माप(*xy) + xlen * row_size);

	अगर (xy != शून्य) अणु
		xy->entry_size = entry_size;
		xy->row_size   = row_size;
		xy->entries    = xlen * ylen;
		xy->max_x      = xlen;
		xy->max_y      = ylen;
	पूर्ण

	वापस xy;
पूर्ण

व्योम xyarray__reset(काष्ठा xyarray *xy)
अणु
	माप_प्रकार n = xy->entries * xy->entry_size;

	स_रखो(xy->contents, 0, n);
पूर्ण

व्योम xyarray__delete(काष्ठा xyarray *xy)
अणु
	मुक्त(xy);
पूर्ण
