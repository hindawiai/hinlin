<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_GENEVE_H
#घोषणा __NET_GENEVE_H  1

#समावेश <net/udp_tunnel.h>

#घोषणा GENEVE_UDP_PORT		6081

/* Geneve Header:
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |Ver|  Opt Len  |O|C|    Rsvd.  |          Protocol Type        |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |        Virtual Network Identअगरier (VNI)       |    Reserved   |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                    Variable Length Options                    |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Option Header:
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |          Option Class         |      Type     |R|R|R| Length  |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |                      Variable Option Data                     |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

काष्ठा geneve_opt अणु
	__be16	opt_class;
	u8	type;
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	u8	length:5;
	u8	r3:1;
	u8	r2:1;
	u8	r1:1;
#अन्यथा
	u8	r1:1;
	u8	r2:1;
	u8	r3:1;
	u8	length:5;
#पूर्ण_अगर
	u8	opt_data[];
पूर्ण;

#घोषणा GENEVE_CRIT_OPT_TYPE (1 << 7)

काष्ठा genevehdr अणु
#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
	u8 opt_len:6;
	u8 ver:2;
	u8 rsvd1:6;
	u8 critical:1;
	u8 oam:1;
#अन्यथा
	u8 ver:2;
	u8 opt_len:6;
	u8 oam:1;
	u8 critical:1;
	u8 rsvd1:6;
#पूर्ण_अगर
	__be16 proto_type;
	u8 vni[3];
	u8 rsvd2;
	काष्ठा geneve_opt options[];
पूर्ण;

अटल अंतरभूत bool netअगर_is_geneve(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->rtnl_link_ops &&
	       !म_भेद(dev->rtnl_link_ops->kind, "geneve");
पूर्ण

#अगर_घोषित CONFIG_INET
काष्ठा net_device *geneve_dev_create_fb(काष्ठा net *net, स्थिर अक्षर *name,
					u8 name_assign_type, u16 dst_port);
#पूर्ण_अगर /*अगरdef CONFIG_INET */

#पूर्ण_अगर /*अगरdef__NET_GENEVE_H */
