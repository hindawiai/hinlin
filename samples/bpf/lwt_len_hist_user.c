<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/unistd.h>
#समावेश <linux/bpf.h>

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <arpa/inet.h>

#समावेश <bpf/bpf.h>
#समावेश "bpf_util.h"

#घोषणा MAX_INDEX 64
#घोषणा MAX_STARS 38

अटल व्योम stars(अक्षर *str, दीर्घ val, दीर्घ max, पूर्णांक width)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (width * val / max) - 1 && i < width - 1; i++)
		str[i] = '*';
	अगर (val > max)
		str[i - 1] = '+';
	str[i] = '\0';
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक nr_cpus = bpf_num_possible_cpus();
	स्थिर अक्षर *map_filename = "/sys/fs/bpf/tc/globals/lwt_len_hist_map";
	uपूर्णांक64_t values[nr_cpus], sum, max_value = 0, data[MAX_INDEX] = अणुपूर्ण;
	uपूर्णांक64_t key = 0, next_key, max_key = 0;
	अक्षर starstr[MAX_STARS];
	पूर्णांक i, map_fd;

	map_fd = bpf_obj_get(map_filename);
	अगर (map_fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "bpf_obj_get(%s): %s(%d)\n",
			map_filename, म_त्रुटि(त्रुटि_सं), त्रुटि_सं);
		वापस -1;
	पूर्ण

	जबतक (bpf_map_get_next_key(map_fd, &key, &next_key) == 0) अणु
		अगर (next_key >= MAX_INDEX) अणु
			ख_लिखो(मानक_त्रुटि, "Key %lu out of bounds\n", next_key);
			जारी;
		पूर्ण

		bpf_map_lookup_elem(map_fd, &next_key, values);

		sum = 0;
		क्रम (i = 0; i < nr_cpus; i++)
			sum += values[i];

		data[next_key] = sum;
		अगर (sum && next_key > max_key)
			max_key = next_key;

		अगर (sum > max_value)
			max_value = sum;

		key = next_key;
	पूर्ण

	क्रम (i = 1; i <= max_key + 1; i++) अणु
		stars(starstr, data[i - 1], max_value, MAX_STARS);
		म_लिखो("%8ld -> %-8ld : %-8ld |%-*s|\n",
		       (1l << i) >> 1, (1l << i) - 1, data[i - 1],
		       MAX_STARS, starstr);
	पूर्ण

	बंद(map_fd);

	वापस 0;
पूर्ण
