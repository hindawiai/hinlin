<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CODA_INT_
#घोषणा _CODA_INT_

काष्ठा dentry;
काष्ठा file;

बाह्य काष्ठा file_प्रणाली_type coda_fs_type;
बाह्य अचिन्हित दीर्घ coda_समयout;
बाह्य पूर्णांक coda_hard;
बाह्य पूर्णांक coda_fake_statfs;

व्योम coda_destroy_inodecache(व्योम);
पूर्णांक __init coda_init_inodecache(व्योम);
पूर्णांक coda_fsync(काष्ठा file *coda_file, loff_t start, loff_t end, पूर्णांक datasync);

#अगर_घोषित CONFIG_SYSCTL
व्योम coda_sysctl_init(व्योम);
व्योम coda_sysctl_clean(व्योम);
#अन्यथा
अटल अंतरभूत व्योम coda_sysctl_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम coda_sysctl_clean(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर  /*  _CODA_INT_  */


