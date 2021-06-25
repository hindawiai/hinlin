<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>

जोड़ ull_जोड़ अणु
	अचिन्हित दीर्घ दीर्घ ull;
	काष्ठा अणु
		अचिन्हित पूर्णांक high;
		अचिन्हित पूर्णांक low;
	पूर्ण ui;
पूर्ण;

पूर्णांक __ucmpdi2(अचिन्हित दीर्घ दीर्घ a, अचिन्हित दीर्घ दीर्घ b)
अणु
	जोड़ ull_जोड़ au = अणु.ull = aपूर्ण;
	जोड़ ull_जोड़ bu = अणु.ull = bपूर्ण;

	अगर (au.ui.high < bu.ui.high)
		वापस 0;
	अन्यथा अगर (au.ui.high > bu.ui.high)
		वापस 2;
	अगर (au.ui.low < bu.ui.low)
		वापस 0;
	अन्यथा अगर (au.ui.low > bu.ui.low)
		वापस 2;
	वापस 1;
पूर्ण
