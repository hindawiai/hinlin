<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RDS_INFO_H
#घोषणा _RDS_INFO_H

काष्ठा rds_info_lengths अणु
	अचिन्हित पूर्णांक	nr;
	अचिन्हित पूर्णांक	each;
पूर्ण;

काष्ठा rds_info_iterator;

/*
 * These functions must fill in the fields of @lens to reflect the size
 * of the available info source.  If the snapshot fits in @len then it
 * should be copied using @iter.  The caller will deduce अगर it was copied
 * or not by comparing the lengths.
 */
प्रकार व्योम (*rds_info_func)(काष्ठा socket *sock, अचिन्हित पूर्णांक len,
			      काष्ठा rds_info_iterator *iter,
			      काष्ठा rds_info_lengths *lens);

व्योम rds_info_रेजिस्टर_func(पूर्णांक optname, rds_info_func func);
व्योम rds_info_deरेजिस्टर_func(पूर्णांक optname, rds_info_func func);
पूर्णांक rds_info_माला_लोockopt(काष्ठा socket *sock, पूर्णांक optname, अक्षर __user *optval,
			पूर्णांक __user *optlen);
व्योम rds_info_copy(काष्ठा rds_info_iterator *iter, व्योम *data,
		   अचिन्हित दीर्घ bytes);
व्योम rds_info_iter_unmap(काष्ठा rds_info_iterator *iter);


#पूर्ण_अगर
