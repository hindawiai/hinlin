<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_VECTOR_USER_H
#घोषणा __UM_VECTOR_USER_H

#घोषणा MAXVARGS	20

#घोषणा TOKEN_IFNAME "ifname"

#घोषणा TRANS_RAW "raw"
#घोषणा TRANS_RAW_LEN म_माप(TRANS_RAW)

#घोषणा TRANS_TAP "tap"
#घोषणा TRANS_TAP_LEN म_माप(TRANS_TAP)

#घोषणा TRANS_GRE "gre"
#घोषणा TRANS_GRE_LEN म_माप(TRANS_GRE)

#घोषणा TRANS_L2TPV3 "l2tpv3"
#घोषणा TRANS_L2TPV3_LEN म_माप(TRANS_L2TPV3)

#घोषणा TRANS_HYBRID "hybrid"
#घोषणा TRANS_HYBRID_LEN म_माप(TRANS_HYBRID)

#घोषणा TRANS_BESS "bess"
#घोषणा TRANS_BESS_LEN म_माप(TRANS_BESS)

#घोषणा DEFAULT_BPF_LEN 6

#अगर_अघोषित IPPROTO_GRE
#घोषणा IPPROTO_GRE 0x2F
#पूर्ण_अगर

#घोषणा GRE_MODE_CHECKSUM	cpu_to_be16(8 << 12)	/* checksum */
#घोषणा GRE_MODE_RESERVED	cpu_to_be16(4 << 12)	/* unused */
#घोषणा GRE_MODE_KEY		cpu_to_be16(2 << 12)	/* KEY present */
#घोषणा GRE_MODE_SEQUENCE	cpu_to_be16(1 << 12)	/* sequence */

#घोषणा GRE_IRB cpu_to_be16(0x6558)

#घोषणा L2TPV3_DATA_PACKET 0x30000

/* IANA-asचिन्हित IP protocol ID क्रम L2TPv3 */

#अगर_अघोषित IPPROTO_L2TP
#घोषणा IPPROTO_L2TP 0x73
#पूर्ण_अगर

काष्ठा arglist अणु
	पूर्णांक	numargs;
	अक्षर	*tokens[MAXVARGS];
	अक्षर	*values[MAXVARGS];
पूर्ण;

/* Separating पढ़ो and ग_लिखो FDs allows us to have dअगरferent
 * rx and tx method. Example - पढ़ो tap via raw socket using
 * recvmmsg, ग_लिखो using legacy tap ग_लिखो calls
 */

काष्ठा vector_fds अणु
	पूर्णांक rx_fd;
	पूर्णांक tx_fd;
	व्योम *remote_addr;
	पूर्णांक remote_addr_size;
पूर्ण;

#घोषणा VECTOR_READ	1
#घोषणा VECTOR_WRITE	(1 < 1)
#घोषणा VECTOR_HEADERS	(1 < 2)

बाह्य काष्ठा arglist *uml_parse_vector_अगरspec(अक्षर *arg);

बाह्य काष्ठा vector_fds *uml_vector_user_खोलो(
	पूर्णांक unit,
	काष्ठा arglist *parsed
);

बाह्य अक्षर *uml_vector_fetch_arg(
	काष्ठा arglist *अगरspec,
	अक्षर *token
);

बाह्य पूर्णांक uml_vector_recvmsg(पूर्णांक fd, व्योम *hdr, पूर्णांक flags);
बाह्य पूर्णांक uml_vector_sendmsg(पूर्णांक fd, व्योम *hdr, पूर्णांक flags);
बाह्य पूर्णांक uml_vector_ग_लिखोv(पूर्णांक fd, व्योम *hdr, पूर्णांक iovcount);
बाह्य पूर्णांक uml_vector_sendmmsg(
	पूर्णांक fd, व्योम *msgvec,
	अचिन्हित पूर्णांक vlen,
	अचिन्हित पूर्णांक flags
);
बाह्य पूर्णांक uml_vector_recvmmsg(
	पूर्णांक fd,
	व्योम *msgvec,
	अचिन्हित पूर्णांक vlen,
	अचिन्हित पूर्णांक flags
);
बाह्य व्योम *uml_vector_शेष_bpf(व्योम *mac);
बाह्य व्योम *uml_vector_user_bpf(अक्षर *filename);
बाह्य पूर्णांक uml_vector_attach_bpf(पूर्णांक fd, व्योम *bpf);
बाह्य पूर्णांक uml_vector_detach_bpf(पूर्णांक fd, व्योम *bpf);
बाह्य bool uml_raw_enable_qdisc_bypass(पूर्णांक fd);
बाह्य bool uml_raw_enable_vnet_headers(पूर्णांक fd);
बाह्य bool uml_tap_enable_vnet_headers(पूर्णांक fd);


#पूर्ण_अगर
