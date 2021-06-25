<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SOCKET_H
#घोषणा _UAPI_LINUX_SOCKET_H

/*
 * Desired design of maximum size and alignment (see RFC2553)
 */
#घोषणा _K_SS_MAXSIZE	128	/* Implementation specअगरic max size */

प्रकार अचिन्हित लघु __kernel_sa_family_t;

/*
 * The definition uses anonymous जोड़ and काष्ठा in order to control the
 * शेष alignment.
 */
काष्ठा __kernel_sockaddr_storage अणु
	जोड़ अणु
		काष्ठा अणु
			__kernel_sa_family_t	ss_family; /* address family */
			/* Following field(s) are implementation specअगरic */
			अक्षर __data[_K_SS_MAXSIZE - माप(अचिन्हित लघु)];
				/* space to achieve desired size, */
				/* _SS_MAXSIZE value minus size of ss_family */
		पूर्ण;
		व्योम *__align; /* implementation specअगरic desired alignment */
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_SOCKET_H */
