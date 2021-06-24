<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "helpline.h"
#समावेश "ui.h"

अक्षर ui_helpline__current[512];

अटल व्योम nop_helpline__pop(व्योम)
अणु
पूर्ण

अटल व्योम nop_helpline__push(स्थिर अक्षर *msg __maybe_unused)
अणु
पूर्ण

अटल पूर्णांक nop_helpline__show(स्थिर अक्षर *fmt __maybe_unused,
			       बहु_सूची ap __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा ui_helpline शेष_helpline_fns = अणु
	.pop	= nop_helpline__pop,
	.push	= nop_helpline__push,
	.show	= nop_helpline__show,
पूर्ण;

काष्ठा ui_helpline *helpline_fns = &शेष_helpline_fns;

व्योम ui_helpline__pop(व्योम)
अणु
	helpline_fns->pop();
पूर्ण

व्योम ui_helpline__push(स्थिर अक्षर *msg)
अणु
	helpline_fns->push(msg);
पूर्ण

व्योम ui_helpline__vpush(स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	अक्षर *s;

	अगर (vaप्र_लिखो(&s, fmt, ap) < 0)
		भख_लिखो(मानक_त्रुटि, fmt, ap);
	अन्यथा अणु
		ui_helpline__push(s);
		मुक्त(s);
	पूर्ण
पूर्ण

व्योम ui_helpline__fpush(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	ui_helpline__vpush(fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

व्योम ui_helpline__माला_दो(स्थिर अक्षर *msg)
अणु
	ui_helpline__pop();
	ui_helpline__push(msg);
पूर्ण

पूर्णांक ui_helpline__vshow(स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	वापस helpline_fns->show(fmt, ap);
पूर्ण

व्योम ui_helpline__म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	ui_helpline__pop();
	बहु_शुरू(ap, fmt);
	ui_helpline__vpush(fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण
