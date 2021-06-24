<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __6LOWPAN_NHC_H
#घोषणा __6LOWPAN_NHC_H

#समावेश <linux/skbuff.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/module.h>

#समावेश <net/6lowpan.h>
#समावेश <net/ipv6.h>

/**
 * LOWPAN_NHC - helper macro to generate nh id fields and lowpan_nhc काष्ठा
 *
 * @__nhc: variable name of the lowpan_nhc काष्ठा.
 * @_name: स्थिर अक्षर * of common header compression name.
 * @_nexthdr: ipv6 nexthdr field क्रम the header compression.
 * @_nexthdrlen: ipv6 nexthdr len क्रम the reserved space.
 * @_idsetup: callback to setup id and mask values.
 * @_idlen: len क्रम the next header id and mask, should be always the same.
 * @_uncompress: callback क्रम uncompression call.
 * @_compress: callback क्रम compression call.
 */
#घोषणा LOWPAN_NHC(__nhc, _name, _nexthdr,	\
		   _hdrlen, _idsetup, _idlen,	\
		   _uncompress, _compress)	\
अटल u8 __nhc##_val[_idlen];			\
अटल u8 __nhc##_mask[_idlen];			\
अटल काष्ठा lowpan_nhc __nhc = अणु		\
	.name		= _name,		\
	.nexthdr	= _nexthdr,		\
	.nexthdrlen	= _hdrlen,		\
	.id		= __nhc##_val,		\
	.idmask		= __nhc##_mask,		\
	.idlen		= _idlen,		\
	.idsetup	= _idsetup,		\
	.uncompress	= _uncompress,		\
	.compress	= _compress,		\
पूर्ण

#घोषणा module_lowpan_nhc(__nhc)		\
अटल पूर्णांक __init __nhc##_init(व्योम)		\
अणु						\
	वापस lowpan_nhc_add(&(__nhc));	\
पूर्ण						\
module_init(__nhc##_init);			\
अटल व्योम __निकास __nhc##_निकास(व्योम)		\
अणु						\
	lowpan_nhc_del(&(__nhc));		\
पूर्ण						\
module_निकास(__nhc##_निकास);

/**
 * काष्ठा lowpan_nhc - hold 6lowpan next hdr compression अगरnक्रमmation
 *
 * @node: holder क्रम the rbtree.
 * @name: name of the specअगरic next header compression
 * @nexthdr: next header value of the protocol which should be compressed.
 * @nexthdrlen: ipv6 nexthdr len क्रम the reserved space.
 * @id: array क्रम nhc id. Note this need to be in network byteorder.
 * @mask: array क्रम nhc id mask. Note this need to be in network byteorder.
 * @len: the length of the next header id and mask.
 * @setup: callback to setup fill the next header id value and mask.
 * @compress: callback to करो the header compression.
 * @uncompress: callback to करो the header uncompression.
 */
काष्ठा lowpan_nhc अणु
	काष्ठा rb_node	node;
	स्थिर अक्षर	*name;
	स्थिर u8	nexthdr;
	स्थिर माप_प्रकार	nexthdrlen;
	u8		*id;
	u8		*idmask;
	स्थिर माप_प्रकार	idlen;

	व्योम		(*idsetup)(काष्ठा lowpan_nhc *nhc);
	पूर्णांक		(*uncompress)(काष्ठा sk_buff *skb, माप_प्रकार needed);
	पूर्णांक		(*compress)(काष्ठा sk_buff *skb, u8 **hc_ptr);
पूर्ण;

/**
 * lowpan_nhc_by_nexthdr - वापस the 6lowpan nhc by ipv6 nexthdr.
 *
 * @nexthdr: ipv6 nexthdr value.
 */
काष्ठा lowpan_nhc *lowpan_nhc_by_nexthdr(u8 nexthdr);

/**
 * lowpan_nhc_check_compression - checks अगर we support compression क्रमmat. If
 *	we support the nhc by nexthdr field, the function will वापस 0. If we
 *	करोn't support the nhc by nexthdr this function will वापस -ENOENT.
 *
 * @skb: skb of 6LoWPAN header to पढ़ो nhc and replace header.
 * @hdr: ipv6hdr to check the nexthdr value
 * @hc_ptr: poपूर्णांकer क्रम 6LoWPAN header which should increment at the end of
 *	    replaced header.
 */
पूर्णांक lowpan_nhc_check_compression(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा ipv6hdr *hdr, u8 **hc_ptr);

/**
 * lowpan_nhc_करो_compression - calling compress callback क्रम nhc
 *
 * @skb: skb of 6LoWPAN header to पढ़ो nhc and replace header.
 * @hdr: ipv6hdr to set the nexthdr value
 * @hc_ptr: poपूर्णांकer क्रम 6LoWPAN header which should increment at the end of
 *	    replaced header.
 */
पूर्णांक lowpan_nhc_करो_compression(काष्ठा sk_buff *skb, स्थिर काष्ठा ipv6hdr *hdr,
			      u8 **hc_ptr);

/**
 * lowpan_nhc_करो_uncompression - calling uncompress callback क्रम nhc
 *
 * @nhc: 6LoWPAN nhc context, get by lowpan_nhc_by_ functions.
 * @skb: skb of 6LoWPAN header, skb->data should be poपूर्णांकed to nhc id value.
 * @dev: netdevice क्रम prपूर्णांक logging inक्रमmation.
 * @hdr: ipv6hdr क्रम setting nexthdr value.
 */
पूर्णांक lowpan_nhc_करो_uncompression(काष्ठा sk_buff *skb,
				स्थिर काष्ठा net_device *dev,
				काष्ठा ipv6hdr *hdr);

/**
 * lowpan_nhc_add - रेजिस्टर a next header compression to framework
 *
 * @nhc: nhc which should be add.
 */
पूर्णांक lowpan_nhc_add(काष्ठा lowpan_nhc *nhc);

/**
 * lowpan_nhc_del - delete a next header compression from framework
 *
 * @nhc: nhc which should be delete.
 */
व्योम lowpan_nhc_del(काष्ठा lowpan_nhc *nhc);

/**
 * lowpan_nhc_init - adding all शेष nhcs
 */
व्योम lowpan_nhc_init(व्योम);

#पूर्ण_अगर /* __6LOWPAN_NHC_H */
