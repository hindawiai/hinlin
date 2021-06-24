<शैली गुरु>
/*
 * linux/include/kmsg_dump.h
 *
 * Copyright (C) 2009 Net Insight AB
 *
 * Author: Simon Kagstrom <simon.kagstrom@netinsight.net>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित _LINUX_KMSG_DUMP_H
#घोषणा _LINUX_KMSG_DUMP_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>

/*
 * Keep this list arranged in rough order of priority. Anything listed after
 * KMSG_DUMP_OOPS will not be logged by शेष unless prपूर्णांकk.always_kmsg_dump
 * is passed to the kernel.
 */
क्रमागत kmsg_dump_reason अणु
	KMSG_DUMP_UNDEF,
	KMSG_DUMP_PANIC,
	KMSG_DUMP_OOPS,
	KMSG_DUMP_EMERG,
	KMSG_DUMP_SHUTDOWN,
	KMSG_DUMP_MAX
पूर्ण;

/**
 * काष्ठा kmsg_dump_iter - iterator क्रम retrieving kernel messages
 * @cur_seq:	Poपूर्णांकs to the oldest message to dump
 * @next_seq:	Poपूर्णांकs after the newest message to dump
 */
काष्ठा kmsg_dump_iter अणु
	u64	cur_seq;
	u64	next_seq;
पूर्ण;

/**
 * काष्ठा kmsg_dumper - kernel crash message dumper काष्ठाure
 * @list:	Entry in the dumper list (निजी)
 * @dump:	Call पूर्णांकo dumping code which will retrieve the data with
 * 		through the record iterator
 * @max_reason:	filter क्रम highest reason number that should be dumped
 * @रेजिस्टरed:	Flag that specअगरies अगर this is alपढ़ोy रेजिस्टरed
 */
काष्ठा kmsg_dumper अणु
	काष्ठा list_head list;
	व्योम (*dump)(काष्ठा kmsg_dumper *dumper, क्रमागत kmsg_dump_reason reason);
	क्रमागत kmsg_dump_reason max_reason;
	bool रेजिस्टरed;
पूर्ण;

#अगर_घोषित CONFIG_PRINTK
व्योम kmsg_dump(क्रमागत kmsg_dump_reason reason);

bool kmsg_dump_get_line(काष्ठा kmsg_dump_iter *iter, bool syslog,
			अक्षर *line, माप_प्रकार size, माप_प्रकार *len);

bool kmsg_dump_get_buffer(काष्ठा kmsg_dump_iter *iter, bool syslog,
			  अक्षर *buf, माप_प्रकार size, माप_प्रकार *len_out);

व्योम kmsg_dump_शुरुआत(काष्ठा kmsg_dump_iter *iter);

पूर्णांक kmsg_dump_रेजिस्टर(काष्ठा kmsg_dumper *dumper);

पूर्णांक kmsg_dump_unरेजिस्टर(काष्ठा kmsg_dumper *dumper);

स्थिर अक्षर *kmsg_dump_reason_str(क्रमागत kmsg_dump_reason reason);
#अन्यथा
अटल अंतरभूत व्योम kmsg_dump(क्रमागत kmsg_dump_reason reason)
अणु
पूर्ण

अटल अंतरभूत bool kmsg_dump_get_line(काष्ठा kmsg_dump_iter *iter, bool syslog,
				स्थिर अक्षर *line, माप_प्रकार size, माप_प्रकार *len)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool kmsg_dump_get_buffer(काष्ठा kmsg_dump_iter *iter, bool syslog,
					अक्षर *buf, माप_प्रकार size, माप_प्रकार *len)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम kmsg_dump_शुरुआत(काष्ठा kmsg_dump_iter *iter)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक kmsg_dump_रेजिस्टर(काष्ठा kmsg_dumper *dumper)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक kmsg_dump_unरेजिस्टर(काष्ठा kmsg_dumper *dumper)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *kmsg_dump_reason_str(क्रमागत kmsg_dump_reason reason)
अणु
	वापस "Disabled";
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_KMSG_DUMP_H */
