<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_CONFIG_H
#घोषणा __PERF_CONFIG_H

#समावेश <stdbool.h>
#समावेश <linux/list.h>

काष्ठा perf_config_item अणु
	अक्षर *name;
	अक्षर *value;
	bool from_प्रणाली_config;
	काष्ठा list_head node;
पूर्ण;

काष्ठा perf_config_section अणु
	अक्षर *name;
	काष्ठा list_head items;
	bool from_प्रणाली_config;
	काष्ठा list_head node;
पूर्ण;

काष्ठा perf_config_set अणु
	काष्ठा list_head sections;
पूर्ण;

बाह्य स्थिर अक्षर *config_exclusive_filename;

प्रकार पूर्णांक (*config_fn_t)(स्थिर अक्षर *, स्थिर अक्षर *, व्योम *);

पूर्णांक perf_शेष_config(स्थिर अक्षर *, स्थिर अक्षर *, व्योम *);
पूर्णांक perf_config(config_fn_t fn, व्योम *);
पूर्णांक perf_config_set(काष्ठा perf_config_set *set,
		    config_fn_t fn, व्योम *data);
पूर्णांक perf_config_पूर्णांक(पूर्णांक *dest, स्थिर अक्षर *, स्थिर अक्षर *);
पूर्णांक perf_config_u8(u8 *dest, स्थिर अक्षर *name, स्थिर अक्षर *value);
पूर्णांक perf_config_u64(u64 *dest, स्थिर अक्षर *, स्थिर अक्षर *);
पूर्णांक perf_config_bool(स्थिर अक्षर *, स्थिर अक्षर *);
पूर्णांक config_error_nonbool(स्थिर अक्षर *);
स्थिर अक्षर *perf_etc_perfconfig(व्योम);
स्थिर अक्षर *perf_home_perfconfig(व्योम);
पूर्णांक perf_config_प्रणाली(व्योम);
पूर्णांक perf_config_global(व्योम);

काष्ठा perf_config_set *perf_config_set__new(व्योम);
काष्ठा perf_config_set *perf_config_set__load_file(स्थिर अक्षर *file);
व्योम perf_config_set__delete(काष्ठा perf_config_set *set);
पूर्णांक perf_config_set__collect(काष्ठा perf_config_set *set, स्थिर अक्षर *file_name,
			     स्थिर अक्षर *var, स्थिर अक्षर *value);
व्योम perf_config__निकास(व्योम);
व्योम perf_config__refresh(व्योम);

/**
 * perf_config_sections__क्रम_each - iterate thru all the sections
 * @list: list_head instance to iterate
 * @section: काष्ठा perf_config_section iterator
 */
#घोषणा perf_config_sections__क्रम_each_entry(list, section)	\
        list_क्रम_each_entry(section, list, node)

/**
 * perf_config_items__क्रम_each - iterate thru all the items
 * @list: list_head instance to iterate
 * @item: काष्ठा perf_config_item iterator
 */
#घोषणा perf_config_items__क्रम_each_entry(list, item)	\
        list_क्रम_each_entry(item, list, node)

/**
 * perf_config_set__क्रम_each - iterate thru all the config section-item pairs
 * @set: evlist instance to iterate
 * @section: काष्ठा perf_config_section iterator
 * @item: काष्ठा perf_config_item iterator
 */
#घोषणा perf_config_set__क्रम_each_entry(set, section, item)			\
	perf_config_sections__क्रम_each_entry(&set->sections, section)		\
	perf_config_items__क्रम_each_entry(&section->items, item)

#पूर्ण_अगर /* __PERF_CONFIG_H */
