<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Compatibility पूर्णांकerface क्रम userspace libc header coordination:
 *
 * Define compatibility macros that are used to control the inclusion or
 * exclusion of UAPI काष्ठाures and definitions in coordination with another
 * userspace C library.
 *
 * This header is पूर्णांकended to solve the problem of UAPI definitions that
 * conflict with userspace definitions. If a UAPI header has such conflicting
 * definitions then the solution is as follows:
 *
 * * Synchronize the UAPI header and the libc headers so either one can be
 *   used and such that the ABI is preserved. If this is not possible then
 *   no simple compatibility पूर्णांकerface exists (you need to ग_लिखो translating
 *   wrappers and नाम things) and you can't use this पूर्णांकerface.
 *
 * Then follow this process:
 *
 * (a) Include libc-compat.h in the UAPI header.
 *      e.g. #समावेश <linux/libc-compat.h>
 *     This include must be as early as possible.
 *
 * (b) In libc-compat.h add enough code to detect that the comflicting
 *     userspace libc header has been included first.
 *
 * (c) If the userspace libc header has been included first define a set of
 *     guard macros of the क्रमm __UAPI_DEF_FOO and set their values to 1, अन्यथा
 *     set their values to 0.
 *
 * (d) Back in the UAPI header with the conflicting definitions, guard the
 *     definitions with:
 *     #अगर __UAPI_DEF_FOO
 *       ...
 *     #पूर्ण_अगर
 *
 * This fixes the situation where the linux headers are included *after* the
 * libc headers. To fix the problem with the inclusion in the other order the
 * userspace libc headers must be fixed like this:
 *
 * * For all definitions that conflict with kernel definitions wrap those
 *   defines in the following:
 *   #अगर !__UAPI_DEF_FOO
 *     ...
 *   #पूर्ण_अगर
 *
 * This prevents the redefinition of a स्थिरruct alपढ़ोy defined by the kernel.
 */
#अगर_अघोषित _UAPI_LIBC_COMPAT_H
#घोषणा _UAPI_LIBC_COMPAT_H

/* We have included glibc headers... */
#अगर defined(__GLIBC__)

/* Coordinate with glibc net/अगर.h header. */
#अगर defined(_NET_IF_H) && defined(__USE_MISC)

/* GLIBC headers included first so करोn't define anything
 * that would alपढ़ोy be defined. */

#घोषणा __UAPI_DEF_IF_IFCONF 0
#घोषणा __UAPI_DEF_IF_IFMAP 0
#घोषणा __UAPI_DEF_IF_IFNAMSIZ 0
#घोषणा __UAPI_DEF_IF_IFREQ 0
/* Everything up to IFF_DYNAMIC, matches net/अगर.h until glibc 2.23 */
#घोषणा __UAPI_DEF_IF_NET_DEVICE_FLAGS 0
/* For the future अगर glibc adds IFF_LOWER_UP, IFF_DORMANT and IFF_ECHO */
#अगर_अघोषित __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO
#घोषणा __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO 1
#पूर्ण_अगर /* __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO */

#अन्यथा /* _NET_IF_H */

/* Linux headers included first, and we must define everything
 * we need. The expectation is that glibc will check the
 * __UAPI_DEF_* defines and adjust appropriately. */

#घोषणा __UAPI_DEF_IF_IFCONF 1
#घोषणा __UAPI_DEF_IF_IFMAP 1
#घोषणा __UAPI_DEF_IF_IFNAMSIZ 1
#घोषणा __UAPI_DEF_IF_IFREQ 1
/* Everything up to IFF_DYNAMIC, matches net/अगर.h until glibc 2.23 */
#घोषणा __UAPI_DEF_IF_NET_DEVICE_FLAGS 1
/* For the future अगर glibc adds IFF_LOWER_UP, IFF_DORMANT and IFF_ECHO */
#घोषणा __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO 1

#पूर्ण_अगर /* _NET_IF_H */

/* Coordinate with glibc netinet/in.h header. */
#अगर defined(_NETINET_IN_H)

/* GLIBC headers included first so करोn't define anything
 * that would alपढ़ोy be defined. */
#घोषणा __UAPI_DEF_IN_ADDR		0
#घोषणा __UAPI_DEF_IN_IPPROTO		0
#घोषणा __UAPI_DEF_IN_PKTINFO		0
#घोषणा __UAPI_DEF_IP_MREQ		0
#घोषणा __UAPI_DEF_SOCKADDR_IN		0
#घोषणा __UAPI_DEF_IN_CLASS		0

#घोषणा __UAPI_DEF_IN6_ADDR		0
/* The exception is the in6_addr macros which must be defined
 * अगर the glibc code didn't define them. This guard matches
 * the guard in glibc/inet/netinet/in.h which defines the
 * additional in6_addr macros e.g. s6_addr16, and s6_addr32. */
#अगर defined(__USE_MISC) || defined (__USE_GNU)
#घोषणा __UAPI_DEF_IN6_ADDR_ALT		0
#अन्यथा
#घोषणा __UAPI_DEF_IN6_ADDR_ALT		1
#पूर्ण_अगर
#घोषणा __UAPI_DEF_SOCKADDR_IN6		0
#घोषणा __UAPI_DEF_IPV6_MREQ		0
#घोषणा __UAPI_DEF_IPPROTO_V6		0
#घोषणा __UAPI_DEF_IPV6_OPTIONS		0
#घोषणा __UAPI_DEF_IN6_PKTINFO		0
#घोषणा __UAPI_DEF_IP6_MTUINFO		0

#अन्यथा

/* Linux headers included first, and we must define everything
 * we need. The expectation is that glibc will check the
 * __UAPI_DEF_* defines and adjust appropriately. */
#घोषणा __UAPI_DEF_IN_ADDR		1
#घोषणा __UAPI_DEF_IN_IPPROTO		1
#घोषणा __UAPI_DEF_IN_PKTINFO		1
#घोषणा __UAPI_DEF_IP_MREQ		1
#घोषणा __UAPI_DEF_SOCKADDR_IN		1
#घोषणा __UAPI_DEF_IN_CLASS		1

#घोषणा __UAPI_DEF_IN6_ADDR		1
/* We unconditionally define the in6_addr macros and glibc must
 * coordinate. */
#घोषणा __UAPI_DEF_IN6_ADDR_ALT		1
#घोषणा __UAPI_DEF_SOCKADDR_IN6		1
#घोषणा __UAPI_DEF_IPV6_MREQ		1
#घोषणा __UAPI_DEF_IPPROTO_V6		1
#घोषणा __UAPI_DEF_IPV6_OPTIONS		1
#घोषणा __UAPI_DEF_IN6_PKTINFO		1
#घोषणा __UAPI_DEF_IP6_MTUINFO		1

#पूर्ण_अगर /* _NETINET_IN_H */

/* Coordinate with glibc netipx/ipx.h header. */
#अगर defined(__NETIPX_IPX_H)

#घोषणा __UAPI_DEF_SOCKADDR_IPX			0
#घोषणा __UAPI_DEF_IPX_ROUTE_DEFINITION		0
#घोषणा __UAPI_DEF_IPX_INTERFACE_DEFINITION	0
#घोषणा __UAPI_DEF_IPX_CONFIG_DATA		0
#घोषणा __UAPI_DEF_IPX_ROUTE_DEF		0

#अन्यथा /* defined(__NETIPX_IPX_H) */

#घोषणा __UAPI_DEF_SOCKADDR_IPX			1
#घोषणा __UAPI_DEF_IPX_ROUTE_DEFINITION		1
#घोषणा __UAPI_DEF_IPX_INTERFACE_DEFINITION	1
#घोषणा __UAPI_DEF_IPX_CONFIG_DATA		1
#घोषणा __UAPI_DEF_IPX_ROUTE_DEF		1

#पूर्ण_अगर /* defined(__NETIPX_IPX_H) */

/* Definitions क्रम xattr.h */
#अगर defined(_SYS_XATTR_H)
#घोषणा __UAPI_DEF_XATTR		0
#अन्यथा
#घोषणा __UAPI_DEF_XATTR		1
#पूर्ण_अगर

/* If we did not see any headers from any supported C libraries,
 * or we are being included in the kernel, then define everything
 * that we need. Check क्रम previous __UAPI_* definitions to give
 * unsupported C libraries a way to opt out of any kernel definition. */
#अन्यथा /* !defined(__GLIBC__) */

/* Definitions क्रम अगर.h */
#अगर_अघोषित __UAPI_DEF_IF_IFCONF
#घोषणा __UAPI_DEF_IF_IFCONF 1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IF_IFMAP
#घोषणा __UAPI_DEF_IF_IFMAP 1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IF_IFNAMSIZ
#घोषणा __UAPI_DEF_IF_IFNAMSIZ 1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IF_IFREQ
#घोषणा __UAPI_DEF_IF_IFREQ 1
#पूर्ण_अगर
/* Everything up to IFF_DYNAMIC, matches net/अगर.h until glibc 2.23 */
#अगर_अघोषित __UAPI_DEF_IF_NET_DEVICE_FLAGS
#घोषणा __UAPI_DEF_IF_NET_DEVICE_FLAGS 1
#पूर्ण_अगर
/* For the future अगर glibc adds IFF_LOWER_UP, IFF_DORMANT and IFF_ECHO */
#अगर_अघोषित __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO
#घोषणा __UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO 1
#पूर्ण_अगर

/* Definitions क्रम in.h */
#अगर_अघोषित __UAPI_DEF_IN_ADDR
#घोषणा __UAPI_DEF_IN_ADDR		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IN_IPPROTO
#घोषणा __UAPI_DEF_IN_IPPROTO		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IN_PKTINFO
#घोषणा __UAPI_DEF_IN_PKTINFO		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IP_MREQ
#घोषणा __UAPI_DEF_IP_MREQ		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_SOCKADDR_IN
#घोषणा __UAPI_DEF_SOCKADDR_IN		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IN_CLASS
#घोषणा __UAPI_DEF_IN_CLASS		1
#पूर्ण_अगर

/* Definitions क्रम in6.h */
#अगर_अघोषित __UAPI_DEF_IN6_ADDR
#घोषणा __UAPI_DEF_IN6_ADDR		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IN6_ADDR_ALT
#घोषणा __UAPI_DEF_IN6_ADDR_ALT		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_SOCKADDR_IN6
#घोषणा __UAPI_DEF_SOCKADDR_IN6		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IPV6_MREQ
#घोषणा __UAPI_DEF_IPV6_MREQ		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IPPROTO_V6
#घोषणा __UAPI_DEF_IPPROTO_V6		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IPV6_OPTIONS
#घोषणा __UAPI_DEF_IPV6_OPTIONS		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IN6_PKTINFO
#घोषणा __UAPI_DEF_IN6_PKTINFO		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IP6_MTUINFO
#घोषणा __UAPI_DEF_IP6_MTUINFO		1
#पूर्ण_अगर

/* Definitions क्रम ipx.h */
#अगर_अघोषित __UAPI_DEF_SOCKADDR_IPX
#घोषणा __UAPI_DEF_SOCKADDR_IPX			1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IPX_ROUTE_DEFINITION
#घोषणा __UAPI_DEF_IPX_ROUTE_DEFINITION		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IPX_INTERFACE_DEFINITION
#घोषणा __UAPI_DEF_IPX_INTERFACE_DEFINITION	1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IPX_CONFIG_DATA
#घोषणा __UAPI_DEF_IPX_CONFIG_DATA		1
#पूर्ण_अगर
#अगर_अघोषित __UAPI_DEF_IPX_ROUTE_DEF
#घोषणा __UAPI_DEF_IPX_ROUTE_DEF		1
#पूर्ण_अगर

/* Definitions क्रम xattr.h */
#अगर_अघोषित __UAPI_DEF_XATTR
#घोषणा __UAPI_DEF_XATTR		1
#पूर्ण_अगर

#पूर्ण_अगर /* __GLIBC__ */

#पूर्ण_अगर /* _UAPI_LIBC_COMPAT_H */
