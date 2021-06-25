<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PSTORE_INTERNAL_H__
#घोषणा __PSTORE_INTERNAL_H__

#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <linux/pstore.h>

बाह्य अचिन्हित दीर्घ kmsg_bytes;

#अगर_घोषित CONFIG_PSTORE_FTRACE
बाह्य व्योम pstore_रेजिस्टर_ftrace(व्योम);
बाह्य व्योम pstore_unरेजिस्टर_ftrace(व्योम);
sमाप_प्रकार pstore_ftrace_combine_log(अक्षर **dest_log, माप_प्रकार *dest_log_size,
				  स्थिर अक्षर *src_log, माप_प्रकार src_log_size);
#अन्यथा
अटल अंतरभूत व्योम pstore_रेजिस्टर_ftrace(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pstore_unरेजिस्टर_ftrace(व्योम) अणुपूर्ण
अटल अंतरभूत sमाप_प्रकार
pstore_ftrace_combine_log(अक्षर **dest_log, माप_प्रकार *dest_log_size,
			  स्थिर अक्षर *src_log, माप_प्रकार src_log_size)
अणु
	*dest_log_size = 0;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PSTORE_PMSG
बाह्य व्योम pstore_रेजिस्टर_pmsg(व्योम);
बाह्य व्योम pstore_unरेजिस्टर_pmsg(व्योम);
#अन्यथा
अटल अंतरभूत व्योम pstore_रेजिस्टर_pmsg(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pstore_unरेजिस्टर_pmsg(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य काष्ठा pstore_info *psinfo;

बाह्य व्योम	pstore_set_kmsg_bytes(पूर्णांक);
बाह्य व्योम	pstore_get_records(पूर्णांक);
बाह्य व्योम	pstore_get_backend_records(काष्ठा pstore_info *psi,
					   काष्ठा dentry *root, पूर्णांक quiet);
बाह्य पूर्णांक	pstore_put_backend_records(काष्ठा pstore_info *psi);
बाह्य पूर्णांक	pstore_mkfile(काष्ठा dentry *root,
			      काष्ठा pstore_record *record);
बाह्य व्योम	pstore_record_init(काष्ठा pstore_record *record,
				   काष्ठा pstore_info *psi);

/* Called during pstore init/निकास. */
पूर्णांक __init	pstore_init_fs(व्योम);
व्योम __निकास	pstore_निकास_fs(व्योम);

#पूर्ण_अगर
