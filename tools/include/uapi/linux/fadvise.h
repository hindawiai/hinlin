<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित FADVISE_H_INCLUDED
#घोषणा FADVISE_H_INCLUDED

#घोषणा POSIX_FADV_NORMAL	0 /* No further special treaपंचांगent.  */
#घोषणा POSIX_FADV_RANDOM	1 /* Expect अक्रमom page references.  */
#घोषणा POSIX_FADV_SEQUENTIAL	2 /* Expect sequential page references.  */
#घोषणा POSIX_FADV_WILLNEED	3 /* Will need these pages.  */

/*
 * The advise values क्रम POSIX_FADV_DONTNEED and POSIX_ADV_NOREUSE
 * क्रम s390-64 dअगरfer from the values क्रम the rest of the world.
 */
#अगर defined(__s390x__)
#घोषणा POSIX_FADV_DONTNEED	6 /* Don't need these pages.  */
#घोषणा POSIX_FADV_NOREUSE	7 /* Data will be accessed once.  */
#अन्यथा
#घोषणा POSIX_FADV_DONTNEED	4 /* Don't need these pages.  */
#घोषणा POSIX_FADV_NOREUSE	5 /* Data will be accessed once.  */
#पूर्ण_अगर

#पूर्ण_अगर	/* FADVISE_H_INCLUDED */
