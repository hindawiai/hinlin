<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pSeries firmware setup code.
 *
 *  Portions from arch/घातerpc/platक्रमms/pseries/setup.c:
 *   Copyright (C) 1995  Linus Torvalds
 *   Adapted from 'alpha' version by Gary Thomas
 *   Modअगरied by Cort Dougan (cort@cs.nmt.edu)
 *   Modअगरied by PPC64 Team, IBM Corp
 *
 *  Portions from arch/घातerpc/kernel/firmware.c
 *   Copyright (C) 2001 Ben. Herrenschmidt (benh@kernel.crashing.org)
 *   Modअगरications क्रम ppc64:
 *    Copyright (C) 2003 Dave Engebretsen <engebret@us.ibm.com>
 *    Copyright (C) 2005 Stephen Rothwell, IBM Corporation
 *
 *  Copyright 2006 IBM Corporation.
 */


#समावेश <linux/of_fdt.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/svm.h>

#समावेश "pseries.h"

काष्ठा hypertas_fw_feature अणु
    अचिन्हित दीर्घ val;
    अक्षर * name;
पूर्ण;

/*
 * The names in this table match names in rtas/ibm,hypertas-functions.  If the
 * entry ends in a '*', only upto the '*' is matched.  Otherwise the entire
 * string must match.
 */
अटल __initdata काष्ठा hypertas_fw_feature
hypertas_fw_features_table[] = अणु
	अणुFW_FEATURE_PFT,		"hcall-pft"पूर्ण,
	अणुFW_FEATURE_TCE,		"hcall-tce"पूर्ण,
	अणुFW_FEATURE_SPRG0,		"hcall-sprg0"पूर्ण,
	अणुFW_FEATURE_DABR,		"hcall-dabr"पूर्ण,
	अणुFW_FEATURE_COPY,		"hcall-copy"पूर्ण,
	अणुFW_FEATURE_ASR,		"hcall-asr"पूर्ण,
	अणुFW_FEATURE_DEBUG,		"hcall-debug"पूर्ण,
	अणुFW_FEATURE_PERF,		"hcall-perf"पूर्ण,
	अणुFW_FEATURE_DUMP,		"hcall-dump"पूर्ण,
	अणुFW_FEATURE_INTERRUPT,		"hcall-interrupt"पूर्ण,
	अणुFW_FEATURE_MIGRATE,		"hcall-migrate"पूर्ण,
	अणुFW_FEATURE_PERFMON,		"hcall-perfmon"पूर्ण,
	अणुFW_FEATURE_CRQ,		"hcall-crq"पूर्ण,
	अणुFW_FEATURE_VIO,		"hcall-vio"पूर्ण,
	अणुFW_FEATURE_RDMA,		"hcall-rdma"पूर्ण,
	अणुFW_FEATURE_LLAN,		"hcall-lLAN"पूर्ण,
	अणुFW_FEATURE_BULK_REMOVE,	"hcall-bulk"पूर्ण,
	अणुFW_FEATURE_XDABR,		"hcall-xdabr"पूर्ण,
	अणुFW_FEATURE_PUT_TCE_IND | FW_FEATURE_STUFF_TCE,
					"hcall-multi-tce"पूर्ण,
	अणुFW_FEATURE_SPLPAR,		"hcall-splpar"पूर्ण,
	अणुFW_FEATURE_VPHN,		"hcall-vphn"पूर्ण,
	अणुFW_FEATURE_SET_MODE,		"hcall-set-mode"पूर्ण,
	अणुFW_FEATURE_BEST_ENERGY,	"hcall-best-energy-1*"पूर्ण,
	अणुFW_FEATURE_HPT_RESIZE,		"hcall-hpt-resize"पूर्ण,
	अणुFW_FEATURE_BLOCK_REMOVE,	"hcall-block-remove"पूर्ण,
	अणुFW_FEATURE_PAPR_SCM,		"hcall-scm"पूर्ण,
	अणुFW_FEATURE_RPT_INVALIDATE,	"hcall-rpt-invalidate"पूर्ण,
पूर्ण;

/* Build up the firmware features biपंचांगask using the contents of
 * device-tree/ibm,hypertas-functions.  Ultimately this functionality may
 * be moved पूर्णांकo prom.c prom_init().
 */
अटल व्योम __init fw_hypertas_feature_init(स्थिर अक्षर *hypertas,
					    अचिन्हित दीर्घ len)
अणु
	स्थिर अक्षर *s;
	पूर्णांक i;

	pr_debug(" -> fw_hypertas_feature_init()\n");

	क्रम (s = hypertas; s < hypertas + len; s += म_माप(s) + 1) अणु
		क्रम (i = 0; i < ARRAY_SIZE(hypertas_fw_features_table); i++) अणु
			स्थिर अक्षर *name = hypertas_fw_features_table[i].name;
			माप_प्रकार size;

			/*
			 * If there is a '*' at the end of name, only check
			 * upto there
			 */
			size = म_माप(name);
			अगर (size && name[size - 1] == '*') अणु
				अगर (म_भेदन(name, s, size - 1))
					जारी;
			पूर्ण अन्यथा अगर (म_भेद(name, s))
				जारी;

			/* we have a match */
			घातerpc_firmware_features |=
				hypertas_fw_features_table[i].val;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (is_secure_guest() &&
	    (घातerpc_firmware_features & FW_FEATURE_PUT_TCE_IND)) अणु
		घातerpc_firmware_features &= ~FW_FEATURE_PUT_TCE_IND;
		pr_debug("SVM: disabling PUT_TCE_IND firmware feature\n");
	पूर्ण

	pr_debug(" <- fw_hypertas_feature_init()\n");
पूर्ण

काष्ठा vec5_fw_feature अणु
	अचिन्हित दीर्घ	val;
	अचिन्हित पूर्णांक	feature;
पूर्ण;

अटल __initdata काष्ठा vec5_fw_feature
vec5_fw_features_table[] = अणु
	अणुFW_FEATURE_TYPE1_AFFINITY,	OV5_TYPE1_AFFINITYपूर्ण,
	अणुFW_FEATURE_PRRN,		OV5_PRRNपूर्ण,
	अणुFW_FEATURE_DRMEM_V2,		OV5_DRMEM_V2पूर्ण,
	अणुFW_FEATURE_DRC_INFO,		OV5_DRC_INFOपूर्ण,
पूर्ण;

अटल व्योम __init fw_vec5_feature_init(स्थिर अक्षर *vec5, अचिन्हित दीर्घ len)
अणु
	अचिन्हित पूर्णांक index, feat;
	पूर्णांक i;

	pr_debug(" -> fw_vec5_feature_init()\n");

	क्रम (i = 0; i < ARRAY_SIZE(vec5_fw_features_table); i++) अणु
		index = OV5_INDX(vec5_fw_features_table[i].feature);
		feat = OV5_FEAT(vec5_fw_features_table[i].feature);

		अगर (index < len && (vec5[index] & feat))
			घातerpc_firmware_features |=
				vec5_fw_features_table[i].val;
	पूर्ण

	pr_debug(" <- fw_vec5_feature_init()\n");
पूर्ण

/*
 * Called very early, MMU is off, device-tree isn't unflattened
 */
अटल पूर्णांक __init probe_fw_features(अचिन्हित दीर्घ node, स्थिर अक्षर *uname, पूर्णांक
				    depth, व्योम *data)
अणु
	स्थिर अक्षर *prop;
	पूर्णांक len;
	अटल पूर्णांक hypertas_found;
	अटल पूर्णांक vec5_found;

	अगर (depth != 1)
		वापस 0;

	अगर (!म_भेद(uname, "rtas") || !म_भेद(uname, "rtas@0")) अणु
		prop = of_get_flat_dt_prop(node, "ibm,hypertas-functions",
					   &len);
		अगर (prop) अणु
			घातerpc_firmware_features |= FW_FEATURE_LPAR;
			fw_hypertas_feature_init(prop, len);
		पूर्ण

		hypertas_found = 1;
	पूर्ण

	अगर (!म_भेद(uname, "chosen")) अणु
		prop = of_get_flat_dt_prop(node, "ibm,architecture-vec-5",
					   &len);
		अगर (prop)
			fw_vec5_feature_init(prop, len);

		vec5_found = 1;
	पूर्ण

	वापस hypertas_found && vec5_found;
पूर्ण

व्योम __init pseries_probe_fw_features(व्योम)
अणु
	of_scan_flat_dt(probe_fw_features, शून्य);
पूर्ण
