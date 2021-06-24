<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _LINUX_BTF_IDS_H
#घोषणा _LINUX_BTF_IDS_H

काष्ठा btf_id_set अणु
	u32 cnt;
	u32 ids[];
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_INFO_BTF

#समावेश <linux/compiler.h> /* क्रम __PASTE */

/*
 * Following macros help to define lists of BTF IDs placed
 * in .BTF_ids section. They are initially filled with zeros
 * (during compilation) and resolved later during the
 * linking phase by resolve_btfids tool.
 *
 * Any change in list layout must be reflected in resolve_btfids
 * tool logic.
 */

#घोषणा BTF_IDS_SECTION ".BTF_ids"

#घोषणा ____BTF_ID(symbol)				\
यंत्र(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
".local " #symbol " ;                          \n"	\
".type  " #symbol ", STT_OBJECT;               \n"	\
".size  " #symbol ", 4;                        \n"	\
#symbol ":                                     \n"	\
".zero 4                                       \n"	\
".popsection;                                  \n");

#घोषणा __BTF_ID(symbol) \
	____BTF_ID(symbol)

#घोषणा __ID(prefix) \
	__PASTE(prefix, __COUNTER__)

/*
 * The BTF_ID defines unique symbol क्रम each ID poपूर्णांकing
 * to 4 zero bytes.
 */
#घोषणा BTF_ID(prefix, name) \
	__BTF_ID(__ID(__BTF_ID__##prefix##__##name##__))

/*
 * The BTF_ID_LIST macro defines pure (unsorted) list
 * of BTF IDs, with following layout:
 *
 * BTF_ID_LIST(list1)
 * BTF_ID(type1, name1)
 * BTF_ID(type2, name2)
 *
 * list1:
 * __BTF_ID__type1__name1__1:
 * .zero 4
 * __BTF_ID__type2__name2__2:
 * .zero 4
 *
 */
#घोषणा __BTF_ID_LIST(name, scope)			\
यंत्र(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
"." #scope " " #name ";                        \n"	\
#name ":;                                      \n"	\
".popsection;                                  \n");

#घोषणा BTF_ID_LIST(name)				\
__BTF_ID_LIST(name, local)				\
बाह्य u32 name[];

#घोषणा BTF_ID_LIST_GLOBAL(name)			\
__BTF_ID_LIST(name, globl)

/* The BTF_ID_LIST_SINGLE macro defines a BTF_ID_LIST with
 * a single entry.
 */
#घोषणा BTF_ID_LIST_SINGLE(name, prefix, typename)	\
	BTF_ID_LIST(name) \
	BTF_ID(prefix, typename)

/*
 * The BTF_ID_UNUSED macro defines 4 zero bytes.
 * It's used when we want to define 'unused' entry
 * in BTF_ID_LIST, like:
 *
 *   BTF_ID_LIST(bpf_skb_output_btf_ids)
 *   BTF_ID(काष्ठा, sk_buff)
 *   BTF_ID_UNUSED
 *   BTF_ID(काष्ठा, task_काष्ठा)
 */

#घोषणा BTF_ID_UNUSED					\
यंत्र(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
".zero 4                                       \n"	\
".popsection;                                  \n");

/*
 * The BTF_SET_START/END macros pair defines sorted list of
 * BTF IDs plus its members count, with following layout:
 *
 * BTF_SET_START(list)
 * BTF_ID(type1, name1)
 * BTF_ID(type2, name2)
 * BTF_SET_END(list)
 *
 * __BTF_ID__set__list:
 * .zero 4
 * list:
 * __BTF_ID__type1__name1__3:
 * .zero 4
 * __BTF_ID__type2__name2__4:
 * .zero 4
 *
 */
#घोषणा __BTF_SET_START(name, scope)			\
यंत्र(							\
".pushsection " BTF_IDS_SECTION ",\"a\";       \n"	\
"." #scope " __BTF_ID__set__" #name ";         \n"	\
"__BTF_ID__set__" #name ":;                    \n"	\
".zero 4                                       \n"	\
".popsection;                                  \n");

#घोषणा BTF_SET_START(name)				\
__BTF_ID_LIST(name, local)				\
__BTF_SET_START(name, local)

#घोषणा BTF_SET_START_GLOBAL(name)			\
__BTF_ID_LIST(name, globl)				\
__BTF_SET_START(name, globl)

#घोषणा BTF_SET_END(name)				\
यंत्र(							\
".pushsection " BTF_IDS_SECTION ",\"a\";      \n"	\
".size __BTF_ID__set__" #name ", .-" #name "  \n"	\
".popsection;                                 \n");	\
बाह्य काष्ठा btf_id_set name;

#अन्यथा

#घोषणा BTF_ID_LIST(name) अटल u32 name[5];
#घोषणा BTF_ID(prefix, name)
#घोषणा BTF_ID_UNUSED
#घोषणा BTF_ID_LIST_GLOBAL(name) u32 name[1];
#घोषणा BTF_ID_LIST_SINGLE(name, prefix, typename) अटल u32 name[1];
#घोषणा BTF_SET_START(name) अटल काष्ठा btf_id_set name = अणु 0 पूर्ण;
#घोषणा BTF_SET_START_GLOBAL(name) अटल काष्ठा btf_id_set name = अणु 0 पूर्ण;
#घोषणा BTF_SET_END(name)

#पूर्ण_अगर /* CONFIG_DEBUG_INFO_BTF */

#अगर_घोषित CONFIG_NET
/* Define a list of socket types which can be the argument क्रम
 * skc_to_*_sock() helpers. All these sockets should have
 * sock_common as the first argument in its memory layout.
 */
#घोषणा BTF_SOCK_TYPE_xxx \
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET, inet_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET_CONN, inet_connection_sock)	\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET_REQ, inet_request_sock)	\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_INET_TW, inet_समयरुको_sock)	\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_REQ, request_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_SOCK, sock)				\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_SOCK_COMMON, sock_common)		\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP, tcp_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP_REQ, tcp_request_sock)		\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP_TW, tcp_समयरुको_sock)		\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_TCP6, tcp6_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_UDP, udp_sock)			\
	BTF_SOCK_TYPE(BTF_SOCK_TYPE_UDP6, udp6_sock)

क्रमागत अणु
#घोषणा BTF_SOCK_TYPE(name, str) name,
BTF_SOCK_TYPE_xxx
#अघोषित BTF_SOCK_TYPE
MAX_BTF_SOCK_TYPE,
पूर्ण;

बाह्य u32 btf_sock_ids[];
#पूर्ण_अगर

#पूर्ण_अगर
