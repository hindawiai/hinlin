<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GENL_MAGIC_FUNC_H
#घोषणा GENL_MAGIC_FUNC_H

#समावेश <linux/build_bug.h>
#समावेश <linux/genl_magic_काष्ठा.h>

/*
 * Magic: declare tla policy						अणुअणुअणु1
 * Magic: declare nested policies
 *									अणुअणुअणु2
 */
#अघोषित GENL_mc_group
#घोषणा GENL_mc_group(group)

#अघोषित GENL_notअगरication
#घोषणा GENL_notअगरication(op_name, op_num, mcast_group, tla_list)

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, tla_list)

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
	[tag_name] = अणु .type = NLA_NESTED पूर्ण,

अटल काष्ठा nla_policy CONCAT_(GENL_MAGIC_FAMILY, _tla_nl_policy)[] = अणु
#समावेश GENL_MAGIC_INCLUDE_खाता
पूर्ण;

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
अटल काष्ठा nla_policy s_name ## _nl_policy[] __पढ़ो_mostly =		\
अणु s_fields पूर्ण;

#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, _type, __get,	\
		 __put, __is_चिन्हित)					\
	[attr_nr] = अणु .type = nla_type पूर्ण,

#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, _type, maxlen,	\
		__get, __put, __is_चिन्हित)				\
	[attr_nr] = अणु .type = nla_type,					\
		      .len = maxlen - (nla_type == NLA_NUL_STRING) पूर्ण,

#समावेश GENL_MAGIC_INCLUDE_खाता

#अगर_अघोषित __KERNEL__
#अगर_अघोषित pr_info
#घोषणा pr_info(args...)	ख_लिखो(मानक_त्रुटि, args);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित GENL_MAGIC_DEBUG
अटल व्योम dprपूर्णांक_field(स्थिर अक्षर *dir, पूर्णांक nla_type,
		स्थिर अक्षर *name, व्योम *valp)
अणु
	__u64 val = valp ? *(__u32 *)valp : 1;
	चयन (nla_type) अणु
	हाल NLA_U8:  val = (__u8)val;
	हाल NLA_U16: val = (__u16)val;
	हाल NLA_U32: val = (__u32)val;
		pr_info("%s attr %s: %d 0x%08x\n", dir,
			name, (पूर्णांक)val, (अचिन्हित)val);
		अवरोध;
	हाल NLA_U64:
		val = *(__u64*)valp;
		pr_info("%s attr %s: %lld 0x%08llx\n", dir,
			name, (दीर्घ दीर्घ)val, (अचिन्हित दीर्घ दीर्घ)val);
		अवरोध;
	हाल NLA_FLAG:
		अगर (val)
			pr_info("%s attr %s: set\n", dir, name);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dprपूर्णांक_array(स्थिर अक्षर *dir, पूर्णांक nla_type,
		स्थिर अक्षर *name, स्थिर अक्षर *val, अचिन्हित len)
अणु
	चयन (nla_type) अणु
	हाल NLA_NUL_STRING:
		अगर (len && val[len-1] == '\0')
			len--;
		pr_info("%s attr %s: [len:%u] '%s'\n", dir, name, len, val);
		अवरोध;
	शेष:
		/* we can always show 4 byte,
		 * thats what nlattr are aligned to. */
		pr_info("%s attr %s: [len:%u] %02x%02x%02x%02x ...\n",
			dir, name, len, val[0], val[1], val[2], val[3]);
	पूर्ण
पूर्ण

#घोषणा DPRINT_TLA(a, op, b) pr_info("%s %s %s\n", a, op, b);

/* Name is a member field name of the काष्ठा s.
 * If s is शून्य (only parsing, no copy requested in *_from_attrs()),
 * nla is supposed to poपूर्णांक to the attribute containing the inक्रमmation
 * corresponding to that काष्ठा member. */
#घोषणा DPRINT_FIELD(dir, nla_type, name, s, nla)			\
	करो अणु								\
		अगर (s)							\
			dprपूर्णांक_field(dir, nla_type, #name, &s->name);	\
		अन्यथा अगर (nla)						\
			dprपूर्णांक_field(dir, nla_type, #name,		\
				(nla_type == NLA_FLAG) ? शून्य		\
						: nla_data(nla));	\
	पूर्ण जबतक (0)

#घोषणा	DPRINT_ARRAY(dir, nla_type, name, s, nla)			\
	करो अणु								\
		अगर (s)							\
			dprपूर्णांक_array(dir, nla_type, #name,		\
					s->name, s->name ## _len);	\
		अन्यथा अगर (nla)						\
			dprपूर्णांक_array(dir, nla_type, #name,		\
					nla_data(nla), nla_len(nla));	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा DPRINT_TLA(a, op, b) करो अणुपूर्ण जबतक (0)
#घोषणा DPRINT_FIELD(dir, nla_type, name, s, nla) करो अणुपूर्ण जबतक (0)
#घोषणा	DPRINT_ARRAY(dir, nla_type, name, s, nla) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Magic: provide conversion functions					अणुअणुअणु1
 * populate काष्ठा from attribute table:
 *									अणुअणुअणु2
 */

/* processing of generic netlink messages is serialized.
 * use one अटल buffer क्रम parsing of nested attributes */
अटल काष्ठा nlattr *nested_attr_tb[128];

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
/* *_from_attrs functions are अटल, but potentially unused */		\
अटल पूर्णांक __ ## s_name ## _from_attrs(काष्ठा s_name *s,		\
		काष्ठा genl_info *info, bool exclude_invariants)	\
अणु									\
	स्थिर पूर्णांक maxtype = ARRAY_SIZE(s_name ## _nl_policy)-1;		\
	काष्ठा nlattr *tla = info->attrs[tag_number];			\
	काष्ठा nlattr **ntb = nested_attr_tb;				\
	काष्ठा nlattr *nla;						\
	पूर्णांक err;							\
	BUILD_BUG_ON(ARRAY_SIZE(s_name ## _nl_policy) > ARRAY_SIZE(nested_attr_tb));	\
	अगर (!tla)							\
		वापस -ENOMSG;						\
	DPRINT_TLA(#s_name, "<=-", #tag_name);				\
	err = drbd_nla_parse_nested(ntb, maxtype, tla, s_name ## _nl_policy);	\
	अगर (err)							\
		वापस err;						\
									\
	s_fields							\
	वापस 0;							\
पूर्ण					__attribute__((unused))		\
अटल पूर्णांक s_name ## _from_attrs(काष्ठा s_name *s,			\
						काष्ठा genl_info *info)	\
अणु									\
	वापस __ ## s_name ## _from_attrs(s, info, false);		\
पूर्ण					__attribute__((unused))		\
अटल पूर्णांक s_name ## _from_attrs_क्रम_change(काष्ठा s_name *s,		\
						काष्ठा genl_info *info)	\
अणु									\
	वापस __ ## s_name ## _from_attrs(s, info, true);		\
पूर्ण					__attribute__((unused))		\

#घोषणा __assign(attr_nr, attr_flag, name, nla_type, type, assignment...)	\
		nla = ntb[attr_nr];						\
		अगर (nla) अणु						\
			अगर (exclude_invariants && !!((attr_flag) & DRBD_F_INVARIANT)) अणु		\
				pr_info("<< must not change invariant attr: %s\n", #name);	\
				वापस -EEXIST;				\
			पूर्ण						\
			assignment;					\
		पूर्ण अन्यथा अगर (exclude_invariants && !!((attr_flag) & DRBD_F_INVARIANT)) अणु		\
			/* attribute missing from payload, */		\
			/* which was expected */			\
		पूर्ण अन्यथा अगर ((attr_flag) & DRBD_F_REQUIRED) अणु		\
			pr_info("<< missing attr: %s\n", #name);	\
			वापस -ENOMSG;					\
		पूर्ण

#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, type, __get, __put,	\
		__is_चिन्हित)						\
	__assign(attr_nr, attr_flag, name, nla_type, type,		\
			अगर (s)						\
				s->name = __get(nla);			\
			DPRINT_FIELD("<<", nla_type, name, s, nla))

/* validate_nla() alपढ़ोy checked nla_len <= maxlen appropriately. */
#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, type, maxlen,	\
		__get, __put, __is_चिन्हित)				\
	__assign(attr_nr, attr_flag, name, nla_type, type,		\
			अगर (s)						\
				s->name ## _len =			\
					__get(s->name, nla, maxlen);	\
			DPRINT_ARRAY("<<", nla_type, name, s, nla))

#समावेश GENL_MAGIC_INCLUDE_खाता

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)

/*
 * Magic: define op number to op name mapping				अणुअणुअणु1
 *									अणुअणुअणु2
 */
स्थिर अक्षर *CONCAT_(GENL_MAGIC_FAMILY, _genl_cmd_to_str)(__u8 cmd)
अणु
	चयन (cmd) अणु
#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, tla_list)		\
	हाल op_num: वापस #op_name;
#समावेश GENL_MAGIC_INCLUDE_खाता
	शेष:
		     वापस "unknown";
	पूर्ण
पूर्ण

#अगर_घोषित __KERNEL__
#समावेश <linux/stringअगरy.h>
/*
 * Magic: define genl_ops						अणुअणुअणु1
 *									अणुअणुअणु2
 */

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, tla_list)		\
अणु								\
	handler							\
	.cmd = op_name,						\
पूर्ण,

#घोषणा ZZZ_genl_ops		CONCAT_(GENL_MAGIC_FAMILY, _genl_ops)
अटल काष्ठा genl_ops ZZZ_genl_ops[] __पढ़ो_mostly = अणु
#समावेश GENL_MAGIC_INCLUDE_खाता
पूर्ण;

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, tla_list)

/*
 * Define the genl_family, multicast groups,				अणुअणुअणु1
 * and provide रेजिस्टर/unरेजिस्टर functions.
 *									अणुअणुअणु2
 */
#घोषणा ZZZ_genl_family		CONCAT_(GENL_MAGIC_FAMILY, _genl_family)
अटल काष्ठा genl_family ZZZ_genl_family;
/*
 * Magic: define multicast groups
 * Magic: define multicast group registration helper
 */
#घोषणा ZZZ_genl_mcgrps		CONCAT_(GENL_MAGIC_FAMILY, _genl_mcgrps)
अटल स्थिर काष्ठा genl_multicast_group ZZZ_genl_mcgrps[] = अणु
#अघोषित GENL_mc_group
#घोषणा GENL_mc_group(group) अणु .name = #group, पूर्ण,
#समावेश GENL_MAGIC_INCLUDE_खाता
पूर्ण;

क्रमागत CONCAT_(GENL_MAGIC_FAMILY, group_ids) अणु
#अघोषित GENL_mc_group
#घोषणा GENL_mc_group(group) CONCAT_(GENL_MAGIC_FAMILY, _group_ ## group),
#समावेश GENL_MAGIC_INCLUDE_खाता
पूर्ण;

#अघोषित GENL_mc_group
#घोषणा GENL_mc_group(group)						\
अटल पूर्णांक CONCAT_(GENL_MAGIC_FAMILY, _genl_multicast_ ## group)(	\
	काष्ठा sk_buff *skb, gfp_t flags)				\
अणु									\
	अचिन्हित पूर्णांक group_id =						\
		CONCAT_(GENL_MAGIC_FAMILY, _group_ ## group);		\
	वापस genlmsg_multicast(&ZZZ_genl_family, skb, 0,		\
				 group_id, flags);			\
पूर्ण

#समावेश GENL_MAGIC_INCLUDE_खाता

#अघोषित GENL_mc_group
#घोषणा GENL_mc_group(group)

अटल काष्ठा genl_family ZZZ_genl_family __ro_after_init = अणु
	.name = __stringअगरy(GENL_MAGIC_FAMILY),
	.version = GENL_MAGIC_VERSION,
#अगर_घोषित GENL_MAGIC_FAMILY_HDRSZ
	.hdrsize = NLA_ALIGN(GENL_MAGIC_FAMILY_HDRSZ),
#पूर्ण_अगर
	.maxattr = ARRAY_SIZE(CONCAT_(GENL_MAGIC_FAMILY, _tla_nl_policy))-1,
	.policy	= CONCAT_(GENL_MAGIC_FAMILY, _tla_nl_policy),
	.ops = ZZZ_genl_ops,
	.n_ops = ARRAY_SIZE(ZZZ_genl_ops),
	.mcgrps = ZZZ_genl_mcgrps,
	.n_mcgrps = ARRAY_SIZE(ZZZ_genl_mcgrps),
	.module = THIS_MODULE,
पूर्ण;

पूर्णांक CONCAT_(GENL_MAGIC_FAMILY, _genl_रेजिस्टर)(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&ZZZ_genl_family);
पूर्ण

व्योम CONCAT_(GENL_MAGIC_FAMILY, _genl_unरेजिस्टर)(व्योम)
अणु
	genl_unरेजिस्टर_family(&ZZZ_genl_family);
पूर्ण

/*
 * Magic: provide conversion functions					अणुअणुअणु1
 * populate skb from काष्ठा.
 *									अणुअणुअणु2
 */

#अघोषित GENL_op
#घोषणा GENL_op(op_name, op_num, handler, tla_list)

#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
अटल पूर्णांक s_name ## _to_skb(काष्ठा sk_buff *skb, काष्ठा s_name *s,	\
		स्थिर bool exclude_sensitive)				\
अणु									\
	काष्ठा nlattr *tla = nla_nest_start(skb, tag_number);		\
	अगर (!tla)							\
		जाओ nla_put_failure;					\
	DPRINT_TLA(#s_name, "-=>", #tag_name);				\
	s_fields							\
	nla_nest_end(skb, tla);						\
	वापस 0;							\
									\
nla_put_failure:							\
	अगर (tla)							\
		nla_nest_cancel(skb, tla);				\
        वापस -EMSGSIZE;						\
पूर्ण									\
अटल अंतरभूत पूर्णांक s_name ## _to_priv_skb(काष्ठा sk_buff *skb,		\
		काष्ठा s_name *s)					\
अणु									\
	वापस s_name ## _to_skb(skb, s, 0);				\
पूर्ण									\
अटल अंतरभूत पूर्णांक s_name ## _to_unpriv_skb(काष्ठा sk_buff *skb,		\
		काष्ठा s_name *s)					\
अणु									\
	वापस s_name ## _to_skb(skb, s, 1);				\
पूर्ण


#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, type, __get, __put,	\
		__is_चिन्हित)						\
	अगर (!exclude_sensitive || !((attr_flag) & DRBD_F_SENSITIVE)) अणु	\
		DPRINT_FIELD(">>", nla_type, name, s, शून्य);		\
		अगर (__put(skb, attr_nr, s->name))			\
			जाओ nla_put_failure;				\
	पूर्ण

#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, type, maxlen,	\
		__get, __put, __is_चिन्हित)				\
	अगर (!exclude_sensitive || !((attr_flag) & DRBD_F_SENSITIVE)) अणु	\
		DPRINT_ARRAY(">>",nla_type, name, s, शून्य);		\
		अगर (__put(skb, attr_nr, min_t(पूर्णांक, maxlen,		\
			s->name ## _len + (nla_type == NLA_NUL_STRING)),\
						s->name))		\
			जाओ nla_put_failure;				\
	पूर्ण

#समावेश GENL_MAGIC_INCLUDE_खाता


/* Functions क्रम initializing काष्ठाs to शेष values.  */

#अघोषित __field
#घोषणा __field(attr_nr, attr_flag, name, nla_type, type, __get, __put,	\
		__is_चिन्हित)
#अघोषित __array
#घोषणा __array(attr_nr, attr_flag, name, nla_type, type, maxlen,	\
		__get, __put, __is_चिन्हित)
#अघोषित __u32_field_def
#घोषणा __u32_field_def(attr_nr, attr_flag, name, शेष)		\
	x->name = शेष;
#अघोषित __s32_field_def
#घोषणा __s32_field_def(attr_nr, attr_flag, name, शेष)		\
	x->name = शेष;
#अघोषित __flg_field_def
#घोषणा __flg_field_def(attr_nr, attr_flag, name, शेष)		\
	x->name = शेष;
#अघोषित __str_field_def
#घोषणा __str_field_def(attr_nr, attr_flag, name, maxlen)		\
	स_रखो(x->name, 0, माप(x->name));				\
	x->name ## _len = 0;
#अघोषित GENL_काष्ठा
#घोषणा GENL_काष्ठा(tag_name, tag_number, s_name, s_fields)		\
अटल व्योम set_ ## s_name ## _शेषs(काष्ठा s_name *x) __attribute__((unused)); \
अटल व्योम set_ ## s_name ## _शेषs(काष्ठा s_name *x) अणु	\
s_fields								\
पूर्ण

#समावेश GENL_MAGIC_INCLUDE_खाता

#पूर्ण_अगर /* __KERNEL__ */

/* पूर्णपूर्णपूर्ण1 */
#पूर्ण_अगर /* GENL_MAGIC_FUNC_H */
