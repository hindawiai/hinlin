<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित __LICENSE_H
#घोषणा __LICENSE_H

अटल अंतरभूत पूर्णांक license_is_gpl_compatible(स्थिर अक्षर *license)
अणु
	वापस (म_भेद(license, "GPL") == 0
		|| म_भेद(license, "GPL v2") == 0
		|| म_भेद(license, "GPL and additional rights") == 0
		|| म_भेद(license, "Dual BSD/GPL") == 0
		|| म_भेद(license, "Dual MIT/GPL") == 0
		|| म_भेद(license, "Dual MPL/GPL") == 0);
पूर्ण

#पूर्ण_अगर
