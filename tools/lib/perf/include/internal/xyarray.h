<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_XYARRAY_H
#घोषणा __LIBPERF_INTERNAL_XYARRAY_H

#समावेश <linux/compiler.h>
#समावेश <sys/types.h>

काष्ठा xyarray अणु
	माप_प्रकार row_size;
	माप_प्रकार entry_size;
	माप_प्रकार entries;
	माप_प्रकार max_x;
	माप_प्रकार max_y;
	अक्षर contents[] __aligned(8);
पूर्ण;

काष्ठा xyarray *xyarray__new(पूर्णांक xlen, पूर्णांक ylen, माप_प्रकार entry_size);
व्योम xyarray__delete(काष्ठा xyarray *xy);
व्योम xyarray__reset(काष्ठा xyarray *xy);

अटल अंतरभूत व्योम *__xyarray__entry(काष्ठा xyarray *xy, पूर्णांक x, पूर्णांक y)
अणु
	वापस &xy->contents[x * xy->row_size + y * xy->entry_size];
पूर्ण

अटल अंतरभूत व्योम *xyarray__entry(काष्ठा xyarray *xy, माप_प्रकार x, माप_प्रकार y)
अणु
	अगर (x >= xy->max_x || y >= xy->max_y)
		वापस शून्य;
	वापस __xyarray__entry(xy, x, y);
पूर्ण

अटल अंतरभूत पूर्णांक xyarray__max_y(काष्ठा xyarray *xy)
अणु
	वापस xy->max_y;
पूर्ण

अटल अंतरभूत पूर्णांक xyarray__max_x(काष्ठा xyarray *xy)
अणु
	वापस xy->max_x;
पूर्ण

#पूर्ण_अगर /* __LIBPERF_INTERNAL_XYARRAY_H */
