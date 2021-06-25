<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RANGE_H
#घोषणा _LINUX_RANGE_H
#समावेश <linux/types.h>

काष्ठा range अणु
	u64   start;
	u64   end;
पूर्ण;

अटल अंतरभूत u64 range_len(स्थिर काष्ठा range *range)
अणु
	वापस range->end - range->start + 1;
पूर्ण

पूर्णांक add_range(काष्ठा range *range, पूर्णांक az, पूर्णांक nr_range,
		u64 start, u64 end);


पूर्णांक add_range_with_merge(काष्ठा range *range, पूर्णांक az, पूर्णांक nr_range,
				u64 start, u64 end);

व्योम subtract_range(काष्ठा range *range, पूर्णांक az, u64 start, u64 end);

पूर्णांक clean_sort_range(काष्ठा range *range, पूर्णांक az);

व्योम sort_range(काष्ठा range *range, पूर्णांक nr_range);

#घोषणा MAX_RESOURCE ((resource_माप_प्रकार)~0)
अटल अंतरभूत resource_माप_प्रकार cap_resource(u64 val)
अणु
	अगर (val > MAX_RESOURCE)
		वापस MAX_RESOURCE;

	वापस val;
पूर्ण
#पूर्ण_अगर
