<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * include/uapi/linux/tipc_config.h: Header क्रम TIPC configuration पूर्णांकerface
 *
 * Copyright (c) 2003-2006, Ericsson AB
 * Copyright (c) 2005-2007, 2010-2011, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _LINUX_TIPC_CONFIG_H_
#घोषणा _LINUX_TIPC_CONFIG_H_

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/tipc.h>
#समावेश <यंत्र/byteorder.h>

#अगर_अघोषित __KERNEL__
#समावेश <arpa/inet.h> /* क्रम ntohs etc. */
#पूर्ण_अगर

/*
 * Configuration
 *
 * All configuration management messaging involves sending a request message
 * to the TIPC configuration service on a node, which sends a reply message
 * back.  (In the future multi-message replies may be supported.)
 *
 * Both request and reply messages consist of a transport header and payload.
 * The transport header contains info about the desired operation;
 * the payload consists of zero or more type/length/value (TLV) items
 * which specअगरy parameters or results क्रम the operation.
 *
 * For many operations, the request and reply messages have a fixed number
 * of TLVs (usually zero or one); however, some reply messages may वापस
 * a variable number of TLVs.  A failed request is denoted by the presence
 * of an "error string" TLV in the reply message instead of the TLV(s) the
 * reply should contain अगर the request succeeds.
 */

/*
 * Public commands:
 * May be issued by any process.
 * Accepted by own node, or by remote node only अगर remote management enabled.
 */

#घोषणा  TIPC_CMD_NOOP              0x0000    /* tx none, rx none */
#घोषणा  TIPC_CMD_GET_NODES         0x0001    /* tx net_addr, rx node_info(s) */
#घोषणा  TIPC_CMD_GET_MEDIA_NAMES   0x0002    /* tx none, rx media_name(s) */
#घोषणा  TIPC_CMD_GET_BEARER_NAMES  0x0003    /* tx none, rx bearer_name(s) */
#घोषणा  TIPC_CMD_GET_LINKS         0x0004    /* tx net_addr, rx link_info(s) */
#घोषणा  TIPC_CMD_SHOW_NAME_TABLE   0x0005    /* tx name_tbl_query, rx ultra_string */
#घोषणा  TIPC_CMD_SHOW_PORTS        0x0006    /* tx none, rx ultra_string */
#घोषणा  TIPC_CMD_SHOW_LINK_STATS   0x000B    /* tx link_name, rx ultra_string */
#घोषणा  TIPC_CMD_SHOW_STATS        0x000F    /* tx अचिन्हित, rx ultra_string */

/*
 * Protected commands:
 * May only be issued by "network administration capable" process.
 * Accepted by own node, or by remote node only अगर remote management enabled
 * and this node is zone manager.
 */

#घोषणा  TIPC_CMD_GET_REMOTE_MNG    0x4003    /* tx none, rx अचिन्हित */
#घोषणा  TIPC_CMD_GET_MAX_PORTS     0x4004    /* tx none, rx अचिन्हित */
#घोषणा  TIPC_CMD_GET_MAX_PUBL      0x4005    /* obsoleted */
#घोषणा  TIPC_CMD_GET_MAX_SUBSCR    0x4006    /* obsoleted */
#घोषणा  TIPC_CMD_GET_MAX_ZONES     0x4007    /* obsoleted */
#घोषणा  TIPC_CMD_GET_MAX_CLUSTERS  0x4008    /* obsoleted */
#घोषणा  TIPC_CMD_GET_MAX_NODES     0x4009    /* obsoleted */
#घोषणा  TIPC_CMD_GET_MAX_SLAVES    0x400A    /* obsoleted */
#घोषणा  TIPC_CMD_GET_NETID         0x400B    /* tx none, rx अचिन्हित */

#घोषणा  TIPC_CMD_ENABLE_BEARER     0x4101    /* tx bearer_config, rx none */
#घोषणा  TIPC_CMD_DISABLE_BEARER    0x4102    /* tx bearer_name, rx none */
#घोषणा  TIPC_CMD_SET_LINK_TOL      0x4107    /* tx link_config, rx none */
#घोषणा  TIPC_CMD_SET_LINK_PRI      0x4108    /* tx link_config, rx none */
#घोषणा  TIPC_CMD_SET_LINK_WINDOW   0x4109    /* tx link_config, rx none */
#घोषणा  TIPC_CMD_SET_LOG_SIZE      0x410A    /* obsoleted */
#घोषणा  TIPC_CMD_DUMP_LOG          0x410B    /* obsoleted */
#घोषणा  TIPC_CMD_RESET_LINK_STATS  0x410C    /* tx link_name, rx none */

/*
 * Private commands:
 * May only be issued by "network administration capable" process.
 * Accepted by own node only; cannot be used on a remote node.
 */

#घोषणा  TIPC_CMD_SET_NODE_ADDR     0x8001    /* tx net_addr, rx none */
#घोषणा  TIPC_CMD_SET_REMOTE_MNG    0x8003    /* tx अचिन्हित, rx none */
#घोषणा  TIPC_CMD_SET_MAX_PORTS     0x8004    /* tx अचिन्हित, rx none */
#घोषणा  TIPC_CMD_SET_MAX_PUBL      0x8005    /* obsoleted */
#घोषणा  TIPC_CMD_SET_MAX_SUBSCR    0x8006    /* obsoleted */
#घोषणा  TIPC_CMD_SET_MAX_ZONES     0x8007    /* obsoleted */
#घोषणा  TIPC_CMD_SET_MAX_CLUSTERS  0x8008    /* obsoleted */
#घोषणा  TIPC_CMD_SET_MAX_NODES     0x8009    /* obsoleted */
#घोषणा  TIPC_CMD_SET_MAX_SLAVES    0x800A    /* obsoleted */
#घोषणा  TIPC_CMD_SET_NETID         0x800B    /* tx अचिन्हित, rx none */

/*
 * Reserved commands:
 * May not be issued by any process.
 * Used पूर्णांकernally by TIPC.
 */

#घोषणा  TIPC_CMD_NOT_NET_ADMIN     0xC001    /* tx none, rx none */

/*
 * TLV types defined क्रम TIPC
 */

#घोषणा TIPC_TLV_NONE		0	/* no TLV present */
#घोषणा TIPC_TLV_VOID		1	/* empty TLV (0 data bytes)*/
#घोषणा TIPC_TLV_UNSIGNED	2	/* 32-bit पूर्णांकeger */
#घोषणा TIPC_TLV_STRING		3	/* अक्षर[128] (max) */
#घोषणा TIPC_TLV_LARGE_STRING	4	/* अक्षर[2048] (max) */
#घोषणा TIPC_TLV_ULTRA_STRING	5	/* अक्षर[32768] (max) */

#घोषणा TIPC_TLV_ERROR_STRING	16	/* अक्षर[128] containing "error code" */
#घोषणा TIPC_TLV_NET_ADDR	17	/* 32-bit पूर्णांकeger denoting <Z.C.N> */
#घोषणा TIPC_TLV_MEDIA_NAME	18	/* अक्षर[TIPC_MAX_MEDIA_NAME] */
#घोषणा TIPC_TLV_BEARER_NAME	19	/* अक्षर[TIPC_MAX_BEARER_NAME] */
#घोषणा TIPC_TLV_LINK_NAME	20	/* अक्षर[TIPC_MAX_LINK_NAME] */
#घोषणा TIPC_TLV_NODE_INFO	21	/* काष्ठा tipc_node_info */
#घोषणा TIPC_TLV_LINK_INFO	22	/* काष्ठा tipc_link_info */
#घोषणा TIPC_TLV_BEARER_CONFIG	23	/* काष्ठा tipc_bearer_config */
#घोषणा TIPC_TLV_LINK_CONFIG	24	/* काष्ठा tipc_link_config */
#घोषणा TIPC_TLV_NAME_TBL_QUERY	25	/* काष्ठा tipc_name_table_query */
#घोषणा TIPC_TLV_PORT_REF	26	/* 32-bit port reference */

/*
 * Link priority limits (min, शेष, max, media शेष)
 */

#घोषणा TIPC_MIN_LINK_PRI	0
#घोषणा TIPC_DEF_LINK_PRI	10
#घोषणा TIPC_MAX_LINK_PRI	31
#घोषणा TIPC_MEDIA_LINK_PRI	(TIPC_MAX_LINK_PRI + 1)

/*
 * Link tolerance limits (min, शेष, max), in ms
 */

#घोषणा TIPC_MIN_LINK_TOL 50
#घोषणा TIPC_DEF_LINK_TOL 1500
#घोषणा TIPC_MAX_LINK_TOL 30000

#अगर (TIPC_MIN_LINK_TOL < 16)
#त्रुटि "TIPC_MIN_LINK_TOL is too small (abort limit may be NaN)"
#पूर्ण_अगर

/*
 * Link winकरोw limits (min, शेष, max), in packets
 */

#घोषणा TIPC_MIN_LINK_WIN 16
#घोषणा TIPC_DEF_LINK_WIN 50
#घोषणा TIPC_MAX_LINK_WIN 8191

/*
 * Default MTU क्रम UDP media
 */

#घोषणा TIPC_DEF_LINK_UDP_MTU 14000

काष्ठा tipc_node_info अणु
	__be32 addr;			/* network address of node */
	__be32 up;			/* 0=करोwn, 1= up */
पूर्ण;

काष्ठा tipc_link_info अणु
	__be32 dest;			/* network address of peer node */
	__be32 up;			/* 0=करोwn, 1=up */
	अक्षर str[TIPC_MAX_LINK_NAME];	/* link name */
पूर्ण;

काष्ठा tipc_bearer_config अणु
	__be32 priority;		/* Range [1,31]. Override per link  */
	__be32 disc_करोमुख्य;		/* <Z.C.N> describing desired nodes */
	अक्षर name[TIPC_MAX_BEARER_NAME];
पूर्ण;

काष्ठा tipc_link_config अणु
	__be32 value;
	अक्षर name[TIPC_MAX_LINK_NAME];
पूर्ण;

#घोषणा TIPC_NTQ_ALLTYPES 0x80000000

काष्ठा tipc_name_table_query अणु
	__be32 depth;	/* 1:type, 2:+name info, 3:+port info, 4+:+debug info */
	__be32 type;	/* अणुt,l,uपूर्ण info ignored अगर high bit of "depth" is set */
	__be32 lowbound; /* (i.e. displays all entries of name table) */
	__be32 upbound;
पूर्ण;

/*
 * The error string TLV is a null-terminated string describing the cause
 * of the request failure.  To simplअगरy error processing (and to save space)
 * the first अक्षरacter of the string can be a special error code अक्षरacter
 * (lying by the range 0x80 to 0xFF) which represents a pre-defined reason.
 */

#घोषणा TIPC_CFG_TLV_ERROR      "\x80"  /* request contains incorrect TLV(s) */
#घोषणा TIPC_CFG_NOT_NET_ADMIN  "\x81"	/* must be network administrator */
#घोषणा TIPC_CFG_NOT_ZONE_MSTR	"\x82"	/* must be zone master */
#घोषणा TIPC_CFG_NO_REMOTE	"\x83"	/* remote management not enabled */
#घोषणा TIPC_CFG_NOT_SUPPORTED  "\x84"	/* request is not supported by TIPC */
#घोषणा TIPC_CFG_INVALID_VALUE  "\x85"  /* request has invalid argument value */

/*
 * A TLV consists of a descriptor, followed by the TLV value.
 * TLV descriptor fields are stored in network byte order;
 * TLV values must also be stored in network byte order (where applicable).
 * TLV descriptors must be aligned to addresses which are multiple of 4,
 * so up to 3 bytes of padding may exist at the end of the TLV value area.
 * There must not be any padding between the TLV descriptor and its value.
 */

काष्ठा tlv_desc अणु
	__be16 tlv_len;		/* TLV length (descriptor + value) */
	__be16 tlv_type;		/* TLV identअगरier */
पूर्ण;

#घोषणा TLV_ALIGNTO 4

#घोषणा TLV_ALIGN(datalen) (((datalen)+(TLV_ALIGNTO-1)) & ~(TLV_ALIGNTO-1))
#घोषणा TLV_LENGTH(datalen) (माप(काष्ठा tlv_desc) + (datalen))
#घोषणा TLV_SPACE(datalen) (TLV_ALIGN(TLV_LENGTH(datalen)))
#घोषणा TLV_DATA(tlv) ((व्योम *)((अक्षर *)(tlv) + TLV_LENGTH(0)))

अटल अंतरभूत पूर्णांक TLV_OK(स्थिर व्योम *tlv, __u16 space)
अणु
	/*
	 * Would also like to check that "tlv" is a multiple of 4,
	 * but करोn't know how to करो this in a portable way.
	 * - Tried करोing (!(tlv & (TLV_ALIGNTO-1))), but GCC compiler
	 *   won't allow binary "&" with a poपूर्णांकer.
	 * - Tried casting "tlv" to पूर्णांकeger type, but causes warning about size
	 *   mismatch when poपूर्णांकer is bigger than chosen type (पूर्णांक, दीर्घ, ...).
	 */

	वापस (space >= TLV_SPACE(0)) &&
		(ntohs(((काष्ठा tlv_desc *)tlv)->tlv_len) <= space);
पूर्ण

अटल अंतरभूत पूर्णांक TLV_CHECK(स्थिर व्योम *tlv, __u16 space, __u16 exp_type)
अणु
	वापस TLV_OK(tlv, space) &&
		(ntohs(((काष्ठा tlv_desc *)tlv)->tlv_type) == exp_type);
पूर्ण

अटल अंतरभूत पूर्णांक TLV_GET_LEN(काष्ठा tlv_desc *tlv)
अणु
	वापस ntohs(tlv->tlv_len);
पूर्ण

अटल अंतरभूत व्योम TLV_SET_LEN(काष्ठा tlv_desc *tlv, __u16 len)
अणु
	tlv->tlv_len = htons(len);
पूर्ण

अटल अंतरभूत पूर्णांक TLV_CHECK_TYPE(काष्ठा tlv_desc *tlv,  __u16 type)
अणु
	वापस (ntohs(tlv->tlv_type) == type);
पूर्ण

अटल अंतरभूत व्योम TLV_SET_TYPE(काष्ठा tlv_desc *tlv, __u16 type)
अणु
	tlv->tlv_type = htons(type);
पूर्ण

अटल अंतरभूत पूर्णांक TLV_SET(व्योम *tlv, __u16 type, व्योम *data, __u16 len)
अणु
	काष्ठा tlv_desc *tlv_ptr;
	पूर्णांक tlv_len;

	tlv_len = TLV_LENGTH(len);
	tlv_ptr = (काष्ठा tlv_desc *)tlv;
	tlv_ptr->tlv_type = htons(type);
	tlv_ptr->tlv_len  = htons(tlv_len);
	अगर (len && data) अणु
		स_नकल(TLV_DATA(tlv_ptr), data, len);
		स_रखो((अक्षर *)TLV_DATA(tlv_ptr) + len, 0, TLV_SPACE(len) - tlv_len);
	पूर्ण
	वापस TLV_SPACE(len);
पूर्ण

/*
 * A TLV list descriptor simplअगरies processing of messages
 * containing multiple TLVs.
 */

काष्ठा tlv_list_desc अणु
	काष्ठा tlv_desc *tlv_ptr;	/* ptr to current TLV */
	__u32 tlv_space;		/* # bytes from curr TLV to list end */
पूर्ण;

अटल अंतरभूत व्योम TLV_LIST_INIT(काष्ठा tlv_list_desc *list,
				 व्योम *data, __u32 space)
अणु
	list->tlv_ptr = (काष्ठा tlv_desc *)data;
	list->tlv_space = space;
पूर्ण

अटल अंतरभूत पूर्णांक TLV_LIST_EMPTY(काष्ठा tlv_list_desc *list)
अणु
	वापस (list->tlv_space == 0);
पूर्ण

अटल अंतरभूत पूर्णांक TLV_LIST_CHECK(काष्ठा tlv_list_desc *list, __u16 exp_type)
अणु
	वापस TLV_CHECK(list->tlv_ptr, list->tlv_space, exp_type);
पूर्ण

अटल अंतरभूत व्योम *TLV_LIST_DATA(काष्ठा tlv_list_desc *list)
अणु
	वापस TLV_DATA(list->tlv_ptr);
पूर्ण

अटल अंतरभूत व्योम TLV_LIST_STEP(काष्ठा tlv_list_desc *list)
अणु
	__u16 tlv_space = TLV_ALIGN(ntohs(list->tlv_ptr->tlv_len));

	list->tlv_ptr = (काष्ठा tlv_desc *)((अक्षर *)list->tlv_ptr + tlv_space);
	list->tlv_space -= tlv_space;
पूर्ण

/*
 * Configuration messages exchanged via NETLINK_GENERIC use the following
 * family id, name, version and command.
 */
#घोषणा TIPC_GENL_NAME		"TIPC"
#घोषणा TIPC_GENL_VERSION	0x1
#घोषणा TIPC_GENL_CMD		0x1

/*
 * TIPC specअगरic header used in NETLINK_GENERIC requests.
 */
काष्ठा tipc_genlmsghdr अणु
	__u32 dest;		/* Destination address */
	__u16 cmd;		/* Command */
	__u16 reserved;		/* Unused */
पूर्ण;

#घोषणा TIPC_GENL_HDRLEN	NLMSG_ALIGN(माप(काष्ठा tipc_genlmsghdr))

/*
 * Configuration messages exchanged via TIPC sockets use the TIPC configuration
 * message header, which is defined below.  This काष्ठाure is analogous
 * to the Netlink message header, but fields are stored in network byte order
 * and no padding is permitted between the header and the message data
 * that follows.
 */

काष्ठा tipc_cfg_msg_hdr अणु
	__be32 tcm_len;		/* Message length (including header) */
	__be16 tcm_type;	/* Command type */
	__be16 tcm_flags;	/* Additional flags */
	अक्षर  tcm_reserved[8];	/* Unused */
पूर्ण;

#घोषणा TCM_F_REQUEST	0x1	/* Flag: Request message */
#घोषणा TCM_F_MORE	0x2	/* Flag: Message to be जारीd */

#घोषणा TCM_ALIGN(datalen)  (((datalen)+3) & ~3)
#घोषणा TCM_LENGTH(datalen) (माप(काष्ठा tipc_cfg_msg_hdr) + datalen)
#घोषणा TCM_SPACE(datalen)  (TCM_ALIGN(TCM_LENGTH(datalen)))
#घोषणा TCM_DATA(tcm_hdr)   ((व्योम *)((अक्षर *)(tcm_hdr) + TCM_LENGTH(0)))

अटल अंतरभूत पूर्णांक TCM_SET(व्योम *msg, __u16 cmd, __u16 flags,
			  व्योम *data, __u16 data_len)
अणु
	काष्ठा tipc_cfg_msg_hdr *tcm_hdr;
	पूर्णांक msg_len;

	msg_len = TCM_LENGTH(data_len);
	tcm_hdr = (काष्ठा tipc_cfg_msg_hdr *)msg;
	tcm_hdr->tcm_len   = htonl(msg_len);
	tcm_hdr->tcm_type  = htons(cmd);
	tcm_hdr->tcm_flags = htons(flags);
	अगर (data_len && data) अणु
		स_नकल(TCM_DATA(msg), data, data_len);
		स_रखो((अक्षर *)TCM_DATA(msg) + data_len, 0, TCM_SPACE(data_len) - msg_len);
	पूर्ण
	वापस TCM_SPACE(data_len);
पूर्ण

#पूर्ण_अगर
