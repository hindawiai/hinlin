<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_MODEL_H_
#घोषणा _IXGBE_MODEL_H_

#समावेश "ixgbe.h"
#समावेश "ixgbe_type.h"

काष्ठा ixgbe_mat_field अणु
	अचिन्हित पूर्णांक off;
	पूर्णांक (*val)(काष्ठा ixgbe_fdir_filter *input,
		   जोड़ ixgbe_atr_input *mask,
		   u32 val, u32 m);
	अचिन्हित पूर्णांक type;
पूर्ण;

काष्ठा ixgbe_jump_table अणु
	काष्ठा ixgbe_mat_field *mat;
	काष्ठा ixgbe_fdir_filter *input;
	जोड़ ixgbe_atr_input *mask;
	u32 link_hdl;
	अचिन्हित दीर्घ child_loc_map[32];
पूर्ण;

#घोषणा IXGBE_MAX_HW_ENTRIES 2045

अटल अंतरभूत पूर्णांक ixgbe_mat_prgm_sip(काष्ठा ixgbe_fdir_filter *input,
				     जोड़ ixgbe_atr_input *mask,
				     u32 val, u32 m)
अणु
	input->filter.क्रमmatted.src_ip[0] = (__क्रमce __be32)val;
	mask->क्रमmatted.src_ip[0] = (__क्रमce __be32)m;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ixgbe_mat_prgm_dip(काष्ठा ixgbe_fdir_filter *input,
				     जोड़ ixgbe_atr_input *mask,
				     u32 val, u32 m)
अणु
	input->filter.क्रमmatted.dst_ip[0] = (__क्रमce __be32)val;
	mask->क्रमmatted.dst_ip[0] = (__क्रमce __be32)m;
	वापस 0;
पूर्ण

अटल काष्ठा ixgbe_mat_field ixgbe_ipv4_fields[] = अणु
	अणु .off = 12, .val = ixgbe_mat_prgm_sip,
	  .type = IXGBE_ATR_FLOW_TYPE_IPV4पूर्ण,
	अणु .off = 16, .val = ixgbe_mat_prgm_dip,
	  .type = IXGBE_ATR_FLOW_TYPE_IPV4पूर्ण,
	अणु .val = शून्य पूर्ण /* terminal node */
पूर्ण;

अटल अंतरभूत पूर्णांक ixgbe_mat_prgm_ports(काष्ठा ixgbe_fdir_filter *input,
				       जोड़ ixgbe_atr_input *mask,
				       u32 val, u32 m)
अणु
	input->filter.क्रमmatted.src_port = (__क्रमce __be16)(val & 0xffff);
	mask->क्रमmatted.src_port = (__क्रमce __be16)(m & 0xffff);
	input->filter.क्रमmatted.dst_port = (__क्रमce __be16)(val >> 16);
	mask->क्रमmatted.dst_port = (__क्रमce __be16)(m >> 16);

	वापस 0;
पूर्ण;

अटल काष्ठा ixgbe_mat_field ixgbe_tcp_fields[] = अणु
	अणु.off = 0, .val = ixgbe_mat_prgm_ports,
	 .type = IXGBE_ATR_FLOW_TYPE_TCPV4पूर्ण,
	अणु .val = शून्य पूर्ण /* terminal node */
पूर्ण;

अटल काष्ठा ixgbe_mat_field ixgbe_udp_fields[] = अणु
	अणु.off = 0, .val = ixgbe_mat_prgm_ports,
	 .type = IXGBE_ATR_FLOW_TYPE_UDPV4पूर्ण,
	अणु .val = शून्य पूर्ण /* terminal node */
पूर्ण;

काष्ठा ixgbe_nexthdr अणु
	/* offset, shअगरt, and mask of position to next header */
	अचिन्हित पूर्णांक o;
	u32 s;
	u32 m;
	/* match criteria to make this jump*/
	अचिन्हित पूर्णांक off;
	u32 val;
	u32 mask;
	/* location of jump to make */
	काष्ठा ixgbe_mat_field *jump;
पूर्ण;

अटल काष्ठा ixgbe_nexthdr ixgbe_ipv4_jumps[] = अणु
	अणु .o = 0, .s = 6, .m = 0xf,
	  .off = 8, .val = 0x600, .mask = 0xff00, .jump = ixgbe_tcp_fieldsपूर्ण,
	अणु .o = 0, .s = 6, .m = 0xf,
	  .off = 8, .val = 0x1100, .mask = 0xff00, .jump = ixgbe_udp_fieldsपूर्ण,
	अणु .jump = शून्य पूर्ण /* terminal node */
पूर्ण;
#पूर्ण_अगर /* _IXGBE_MODEL_H_ */
