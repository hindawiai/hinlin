<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित FS_CEPH_HASH_H
#घोषणा FS_CEPH_HASH_H

#घोषणा CEPH_STR_HASH_LINUX      0x1  /* linux dcache hash */
#घोषणा CEPH_STR_HASH_RJENKINS   0x2  /* robert jenkins' */

बाह्य अचिन्हित ceph_str_hash_linux(स्थिर अक्षर *s, अचिन्हित len);
बाह्य अचिन्हित ceph_str_hash_rjenkins(स्थिर अक्षर *s, अचिन्हित len);

बाह्य अचिन्हित ceph_str_hash(पूर्णांक type, स्थिर अक्षर *s, अचिन्हित len);
बाह्य स्थिर अक्षर *ceph_str_hash_name(पूर्णांक type);

#पूर्ण_अगर
