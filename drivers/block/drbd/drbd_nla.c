<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <net/netlink.h>
#समावेश <linux/drbd_genl_api.h>
#समावेश "drbd_nla.h"

अटल पूर्णांक drbd_nla_check_mandatory(पूर्णांक maxtype, काष्ठा nlattr *nla)
अणु
	काष्ठा nlattr *head = nla_data(nla);
	पूर्णांक len = nla_len(nla);
	पूर्णांक rem;

	/*
	 * validate_nla (called from nla_parse_nested) ignores attributes
	 * beyond maxtype, and करोes not understand the DRBD_GENLA_F_MANDATORY flag.
	 * In order to have it validate attributes with the DRBD_GENLA_F_MANDATORY
	 * flag set also, check and हटाओ that flag beक्रमe calling
	 * nla_parse_nested.
	 */

	nla_क्रम_each_attr(nla, head, len, rem) अणु
		अगर (nla->nla_type & DRBD_GENLA_F_MANDATORY) अणु
			nla->nla_type &= ~DRBD_GENLA_F_MANDATORY;
			अगर (nla_type(nla) > maxtype)
				वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक drbd_nla_parse_nested(काष्ठा nlattr *tb[], पूर्णांक maxtype, काष्ठा nlattr *nla,
			  स्थिर काष्ठा nla_policy *policy)
अणु
	पूर्णांक err;

	err = drbd_nla_check_mandatory(maxtype, nla);
	अगर (!err)
		err = nla_parse_nested_deprecated(tb, maxtype, nla, policy,
						  शून्य);

	वापस err;
पूर्ण

काष्ठा nlattr *drbd_nla_find_nested(पूर्णांक maxtype, काष्ठा nlattr *nla, पूर्णांक attrtype)
अणु
	पूर्णांक err;
	/*
	 * If any nested attribute has the DRBD_GENLA_F_MANDATORY flag set and
	 * we करोn't know about that attribute, reject all the nested
	 * attributes.
	 */
	err = drbd_nla_check_mandatory(maxtype, nla);
	अगर (err)
		वापस ERR_PTR(err);
	वापस nla_find_nested(nla, attrtype);
पूर्ण
