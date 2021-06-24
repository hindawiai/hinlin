<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/linkage.h>

/*
 * libgcc functions - functions that are used पूर्णांकernally by the
 * compiler...  (prototypes are not correct though, but that
 * करोesn't really matter since they're not versioned).
 */
यंत्रlinkage दीर्घ __ucmpdi2(दीर्घ दीर्घ, दीर्घ दीर्घ);
यंत्रlinkage दीर्घ दीर्घ __ashldi3(दीर्घ दीर्घ, पूर्णांक);
यंत्रlinkage दीर्घ दीर्घ __ashrdi3(दीर्घ दीर्घ, पूर्णांक);
यंत्रlinkage दीर्घ दीर्घ __lshrdi3(दीर्घ दीर्घ, पूर्णांक);
यंत्रlinkage दीर्घ __भागsi3(दीर्घ, दीर्घ);
यंत्रlinkage दीर्घ __modsi3(दीर्घ, दीर्घ);
यंत्रlinkage अचिन्हित दीर्घ __umodsi3(अचिन्हित दीर्घ, अचिन्हित दीर्घ);
यंत्रlinkage दीर्घ दीर्घ __muldi3(दीर्घ दीर्घ, दीर्घ दीर्घ);
यंत्रlinkage दीर्घ __mulsi3(दीर्घ, दीर्घ);
यंत्रlinkage दीर्घ __uभागsi3(दीर्घ, दीर्घ);
यंत्रlinkage व्योम *स_नकल(व्योम *, स्थिर व्योम *, माप_प्रकार);
यंत्रlinkage व्योम *स_रखो(व्योम *, पूर्णांक, माप_प्रकार);
यंत्रlinkage दीर्घ म_नकलन_from_user(व्योम *to, व्योम *from, माप_प्रकार n);

	/* gcc lib functions */
EXPORT_SYMBOL(__ucmpdi2);
EXPORT_SYMBOL(__ashldi3);
EXPORT_SYMBOL(__ashrdi3);
EXPORT_SYMBOL(__lshrdi3);
EXPORT_SYMBOL(__भागsi3);
EXPORT_SYMBOL(__modsi3);
EXPORT_SYMBOL(__umodsi3);
EXPORT_SYMBOL(__muldi3);
EXPORT_SYMBOL(__mulsi3);
EXPORT_SYMBOL(__uभागsi3);
EXPORT_SYMBOL(स_नकल);
EXPORT_SYMBOL(स_रखो);
EXPORT_SYMBOL(म_नकलन_from_user);
