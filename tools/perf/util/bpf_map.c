<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

#समावेश "util/bpf_map.h"
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <stdbool.h>
#समावेश <मानककोष.स>
#समावेश <unistd.h>

अटल bool bpf_map_def__is_per_cpu(स्थिर काष्ठा bpf_map_def *def)
अणु
	वापस def->type == BPF_MAP_TYPE_PERCPU_HASH ||
	       def->type == BPF_MAP_TYPE_PERCPU_ARRAY ||
	       def->type == BPF_MAP_TYPE_LRU_PERCPU_HASH ||
	       def->type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE;
पूर्ण

अटल व्योम *bpf_map_def__alloc_value(स्थिर काष्ठा bpf_map_def *def)
अणु
	अगर (bpf_map_def__is_per_cpu(def))
		वापस दो_स्मृति(round_up(def->value_size, 8) * sysconf(_SC_NPROCESSORS_CONF));

	वापस दो_स्मृति(def->value_size);
पूर्ण

पूर्णांक bpf_map__ख_लिखो(काष्ठा bpf_map *map, खाता *fp)
अणु
	स्थिर काष्ठा bpf_map_def *def = bpf_map__def(map);
	व्योम *prev_key = शून्य, *key, *value;
	पूर्णांक fd = bpf_map__fd(map), err;
	पूर्णांक prपूर्णांकed = 0;

	अगर (fd < 0)
		वापस fd;

	अगर (IS_ERR(def))
		वापस PTR_ERR(def);

	err = -ENOMEM;
	key = दो_स्मृति(def->key_size);
	अगर (key == शून्य)
		जाओ out;

	value = bpf_map_def__alloc_value(def);
	अगर (value == शून्य)
		जाओ out_मुक्त_key;

	जबतक ((err = bpf_map_get_next_key(fd, prev_key, key) == 0)) अणु
		पूर्णांक पूर्णांकkey = *(पूर्णांक *)key;

		अगर (!bpf_map_lookup_elem(fd, key, value)) अणु
			bool boolval = *(bool *)value;
			अगर (boolval)
				prपूर्णांकed += ख_लिखो(fp, "[%d] = %d,\n", पूर्णांकkey, boolval);
		पूर्ण अन्यथा अणु
			prपूर्णांकed += ख_लिखो(fp, "[%d] = ERROR,\n", पूर्णांकkey);
		पूर्ण

		prev_key = key;
	पूर्ण

	अगर (err == ENOENT)
		err = prपूर्णांकed;

	मुक्त(value);
out_मुक्त_key:
	मुक्त(key);
out:
	वापस err;
पूर्ण
