<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <endian.h>
#समावेश "event-parse.h"

/*
 * From glibc endian.h, क्रम older प्रणालीs where it is not present, e.g.: RHEL5,
 * Feकरोra6.
 */
#अगर_अघोषित le16toh
# अगर __BYTE_ORDER == __LITTLE_ENDIAN
#  define le16toh(x) (x)
# अन्यथा
#  define le16toh(x) __bswap_16 (x)
# endअगर
#पूर्ण_अगर


अटल अचिन्हित दीर्घ दीर्घ
process___le16_to_cpup(काष्ठा trace_seq *s, अचिन्हित दीर्घ दीर्घ *args)
अणु
	uपूर्णांक16_t *val = (uपूर्णांक16_t *) (अचिन्हित दीर्घ) args[0];
	वापस val ? (दीर्घ दीर्घ) le16toh(*val) : 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_prपूर्णांक_function(tep,
				    process___le16_to_cpup,
				    TEP_FUNC_ARG_INT,
				    "__le16_to_cpup",
				    TEP_FUNC_ARG_PTR,
				    TEP_FUNC_ARG_VOID);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_prपूर्णांक_function(tep, process___le16_to_cpup,
				      "__le16_to_cpup");
पूर्ण
