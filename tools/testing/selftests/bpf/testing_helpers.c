<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2020 Facebook, Inc. */
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश "testing_helpers.h"

पूर्णांक parse_num_list(स्थिर अक्षर *s, bool **num_set, पूर्णांक *num_set_len)
अणु
	पूर्णांक i, set_len = 0, new_len, num, start = 0, end = -1;
	bool *set = शून्य, *पंचांगp, parsing_end = false;
	अक्षर *next;

	जबतक (s[0]) अणु
		त्रुटि_सं = 0;
		num = म_से_दीर्घ(s, &next, 10);
		अगर (त्रुटि_सं)
			वापस -त्रुटि_सं;

		अगर (parsing_end)
			end = num;
		अन्यथा
			start = num;

		अगर (!parsing_end && *next == '-') अणु
			s = next + 1;
			parsing_end = true;
			जारी;
		पूर्ण अन्यथा अगर (*next == ',') अणु
			parsing_end = false;
			s = next + 1;
			end = num;
		पूर्ण अन्यथा अगर (*next == '\0') अणु
			parsing_end = false;
			s = next;
			end = num;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

		अगर (start > end)
			वापस -EINVAL;

		अगर (end + 1 > set_len) अणु
			new_len = end + 1;
			पंचांगp = पुनः_स्मृति(set, new_len);
			अगर (!पंचांगp) अणु
				मुक्त(set);
				वापस -ENOMEM;
			पूर्ण
			क्रम (i = set_len; i < start; i++)
				पंचांगp[i] = false;
			set = पंचांगp;
			set_len = new_len;
		पूर्ण
		क्रम (i = start; i <= end; i++)
			set[i] = true;
	पूर्ण

	अगर (!set)
		वापस -EINVAL;

	*num_set = set;
	*num_set_len = set_len;

	वापस 0;
पूर्ण

__u32 link_info_prog_id(स्थिर काष्ठा bpf_link *link, काष्ठा bpf_link_info *info)
अणु
	__u32 info_len = माप(*info);
	पूर्णांक err;

	स_रखो(info, 0, माप(*info));
	err = bpf_obj_get_info_by_fd(bpf_link__fd(link), info, &info_len);
	अगर (err) अणु
		म_लिखो("failed to get link info: %d\n", -त्रुटि_सं);
		वापस 0;
	पूर्ण
	वापस info->prog_id;
पूर्ण
