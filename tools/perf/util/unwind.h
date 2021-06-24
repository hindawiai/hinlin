<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UNWIND_H
#घोषणा __UNWIND_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश "util/map_symbol.h"

काष्ठा maps;
काष्ठा perf_sample;
काष्ठा thपढ़ो;

काष्ठा unwind_entry अणु
	काष्ठा map_symbol ms;
	u64		  ip;
पूर्ण;

प्रकार पूर्णांक (*unwind_entry_cb_t)(काष्ठा unwind_entry *entry, व्योम *arg);

काष्ठा unwind_libunwind_ops अणु
	पूर्णांक (*prepare_access)(काष्ठा maps *maps);
	व्योम (*flush_access)(काष्ठा maps *maps);
	व्योम (*finish_access)(काष्ठा maps *maps);
	पूर्णांक (*get_entries)(unwind_entry_cb_t cb, व्योम *arg,
			   काष्ठा thपढ़ो *thपढ़ो,
			   काष्ठा perf_sample *data, पूर्णांक max_stack);
पूर्ण;

#अगर_घोषित HAVE_DWARF_UNWIND_SUPPORT
पूर्णांक unwind__get_entries(unwind_entry_cb_t cb, व्योम *arg,
			काष्ठा thपढ़ो *thपढ़ो,
			काष्ठा perf_sample *data, पूर्णांक max_stack);
/* libunwind specअगरic */
#अगर_घोषित HAVE_LIBUNWIND_SUPPORT
#अगर_अघोषित LIBUNWIND__ARCH_REG_ID
#घोषणा LIBUNWIND__ARCH_REG_ID(regnum) libunwind__arch_reg_id(regnum)
#पूर्ण_अगर

#अगर_अघोषित LIBUNWIND__ARCH_REG_SP
#घोषणा LIBUNWIND__ARCH_REG_SP PERF_REG_SP
#पूर्ण_अगर

#अगर_अघोषित LIBUNWIND__ARCH_REG_IP
#घोषणा LIBUNWIND__ARCH_REG_IP PERF_REG_IP
#पूर्ण_अगर

पूर्णांक LIBUNWIND__ARCH_REG_ID(पूर्णांक regnum);
पूर्णांक unwind__prepare_access(काष्ठा maps *maps, काष्ठा map *map, bool *initialized);
व्योम unwind__flush_access(काष्ठा maps *maps);
व्योम unwind__finish_access(काष्ठा maps *maps);
#अन्यथा
अटल अंतरभूत पूर्णांक unwind__prepare_access(काष्ठा maps *maps __maybe_unused,
					 काष्ठा map *map __maybe_unused,
					 bool *initialized __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम unwind__flush_access(काष्ठा maps *maps __maybe_unused) अणुपूर्ण
अटल अंतरभूत व्योम unwind__finish_access(काष्ठा maps *maps __maybe_unused) अणुपूर्ण
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत पूर्णांक
unwind__get_entries(unwind_entry_cb_t cb __maybe_unused,
		    व्योम *arg __maybe_unused,
		    काष्ठा thपढ़ो *thपढ़ो __maybe_unused,
		    काष्ठा perf_sample *data __maybe_unused,
		    पूर्णांक max_stack __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक unwind__prepare_access(काष्ठा maps *maps __maybe_unused,
					 काष्ठा map *map __maybe_unused,
					 bool *initialized __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम unwind__flush_access(काष्ठा maps *maps __maybe_unused) अणुपूर्ण
अटल अंतरभूत व्योम unwind__finish_access(काष्ठा maps *maps __maybe_unused) अणुपूर्ण
#पूर्ण_अगर /* HAVE_DWARF_UNWIND_SUPPORT */
#पूर्ण_अगर /* __UNWIND_H */
