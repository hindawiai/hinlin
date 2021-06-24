<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2020 ARM Limited

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/auxv.h>

#समावेश "helper.h"

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा signatures चिन्हित_vals;
	अचिन्हित दीर्घ hwcaps;
	माप_प्रकार val;

	ख_पढ़ो(&val, माप(माप_प्रकार), 1, मानक_निवेश);

	/* करोn't try to execute illegal (unimplemented) inकाष्ठाions) caller
	 * should have checked this and keep worker simple
	 */
	hwcaps = getauxval(AT_HWCAP);

	अगर (hwcaps & HWCAP_PACA) अणु
		चिन्हित_vals.keyia = keyia_sign(val);
		चिन्हित_vals.keyib = keyib_sign(val);
		चिन्हित_vals.keyda = keyda_sign(val);
		चिन्हित_vals.keydb = keydb_sign(val);
	पूर्ण
	चिन्हित_vals.keyg = (hwcaps & HWCAP_PACG) ?  keyg_sign(val) : 0;

	ख_डालो(&चिन्हित_vals, माप(काष्ठा signatures), 1, मानक_निकास);

	वापस 0;
पूर्ण
