<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/net/bond/bond_options.h - bonding options
 * Copyright (c) 2013 Nikolay Aleksandrov <nikolay@redhat.com>
 */

#अगर_अघोषित _NET_BOND_OPTIONS_H
#घोषणा _NET_BOND_OPTIONS_H

#घोषणा BOND_OPT_MAX_NAMELEN 32
#घोषणा BOND_OPT_VALID(opt) ((opt) < BOND_OPT_LAST)
#घोषणा BOND_MODE_ALL_EX(x) (~(x))

/* Option flags:
 * BOND_OPTFLAG_NOSLAVES - check अगर the bond device is empty beक्रमe setting
 * BOND_OPTFLAG_IFDOWN - check अगर the bond device is करोwn beक्रमe setting
 * BOND_OPTFLAG_RAWVAL - the option parses the value itself
 */
क्रमागत अणु
	BOND_OPTFLAG_NOSLAVES	= BIT(0),
	BOND_OPTFLAG_IFDOWN	= BIT(1),
	BOND_OPTFLAG_RAWVAL	= BIT(2)
पूर्ण;

/* Value type flags:
 * BOND_VALFLAG_DEFAULT - mark the value as शेष
 * BOND_VALFLAG_(MIN|MAX) - mark the value as min/max
 */
क्रमागत अणु
	BOND_VALFLAG_DEFAULT	= BIT(0),
	BOND_VALFLAG_MIN	= BIT(1),
	BOND_VALFLAG_MAX	= BIT(2)
पूर्ण;

/* Option IDs, their bit positions correspond to their IDs */
क्रमागत अणु
	BOND_OPT_MODE,
	BOND_OPT_PACKETS_PER_SLAVE,
	BOND_OPT_XMIT_HASH,
	BOND_OPT_ARP_VALIDATE,
	BOND_OPT_ARP_ALL_TARGETS,
	BOND_OPT_FAIL_OVER_MAC,
	BOND_OPT_ARP_INTERVAL,
	BOND_OPT_ARP_TARGETS,
	BOND_OPT_DOWNDELAY,
	BOND_OPT_UPDELAY,
	BOND_OPT_LACP_RATE,
	BOND_OPT_MINLINKS,
	BOND_OPT_AD_SELECT,
	BOND_OPT_NUM_PEER_NOTIF,
	BOND_OPT_MIIMON,
	BOND_OPT_PRIMARY,
	BOND_OPT_PRIMARY_RESELECT,
	BOND_OPT_USE_CARRIER,
	BOND_OPT_ACTIVE_SLAVE,
	BOND_OPT_QUEUE_ID,
	BOND_OPT_ALL_SLAVES_ACTIVE,
	BOND_OPT_RESEND_IGMP,
	BOND_OPT_LP_INTERVAL,
	BOND_OPT_SLAVES,
	BOND_OPT_TLB_DYNAMIC_LB,
	BOND_OPT_AD_ACTOR_SYS_PRIO,
	BOND_OPT_AD_ACTOR_SYSTEM,
	BOND_OPT_AD_USER_PORT_KEY,
	BOND_OPT_NUM_PEER_NOTIF_ALIAS,
	BOND_OPT_PEER_NOTIF_DELAY,
	BOND_OPT_LAST
पूर्ण;

/* This काष्ठाure is used क्रम storing option values and क्रम passing option
 * values when changing an option. The logic when used as an arg is as follows:
 * - अगर string != शून्य -> parse it, अगर the opt is RAW type then वापस it, अन्यथा
 *   वापस the parse result
 * - अगर string == शून्य -> parse value
 */
काष्ठा bond_opt_value अणु
	अक्षर *string;
	u64 value;
	u32 flags;
पूर्ण;

काष्ठा bonding;

काष्ठा bond_option अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *desc;
	u32 flags;

	/* unsuppmodes is used to denote modes in which the option isn't
	 * supported.
	 */
	अचिन्हित दीर्घ unsuppmodes;
	/* supported values which this option can have, can be a subset of
	 * BOND_OPTVAL_RANGE's value range
	 */
	स्थिर काष्ठा bond_opt_value *values;

	पूर्णांक (*set)(काष्ठा bonding *bond, स्थिर काष्ठा bond_opt_value *val);
पूर्ण;

पूर्णांक __bond_opt_set(काष्ठा bonding *bond, अचिन्हित पूर्णांक option,
		   काष्ठा bond_opt_value *val);
पूर्णांक __bond_opt_set_notअगरy(काष्ठा bonding *bond, अचिन्हित पूर्णांक option,
			  काष्ठा bond_opt_value *val);
पूर्णांक bond_opt_tryset_rtnl(काष्ठा bonding *bond, अचिन्हित पूर्णांक option, अक्षर *buf);

स्थिर काष्ठा bond_opt_value *bond_opt_parse(स्थिर काष्ठा bond_option *opt,
					    काष्ठा bond_opt_value *val);
स्थिर काष्ठा bond_option *bond_opt_get(अचिन्हित पूर्णांक option);
स्थिर काष्ठा bond_option *bond_opt_get_by_name(स्थिर अक्षर *name);
स्थिर काष्ठा bond_opt_value *bond_opt_get_val(अचिन्हित पूर्णांक option, u64 val);

/* This helper is used to initialize a bond_opt_value काष्ठाure क्रम parameter
 * passing. There should be either a valid string or value, but not both.
 * When value is ULदीर्घ_उच्च then string will be used.
 */
अटल अंतरभूत व्योम __bond_opt_init(काष्ठा bond_opt_value *optval,
				   अक्षर *string, u64 value)
अणु
	स_रखो(optval, 0, माप(*optval));
	optval->value = ULदीर्घ_उच्च;
	अगर (value == ULदीर्घ_उच्च)
		optval->string = string;
	अन्यथा
		optval->value = value;
पूर्ण
#घोषणा bond_opt_initval(optval, value) __bond_opt_init(optval, शून्य, value)
#घोषणा bond_opt_initstr(optval, str) __bond_opt_init(optval, str, ULदीर्घ_उच्च)

व्योम bond_option_arp_ip_tarमाला_लो_clear(काष्ठा bonding *bond);

#पूर्ण_अगर /* _NET_BOND_OPTIONS_H */
