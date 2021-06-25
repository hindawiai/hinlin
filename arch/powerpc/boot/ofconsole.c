<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OF console routines
 *
 * Copyright (C) Paul Mackerras 1997.
 */
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "elf.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "page.h"
#समावेश "ops.h"

#समावेश "of.h"

अटल अचिन्हित पूर्णांक of_मानक_निकास_handle;

अटल पूर्णांक of_console_खोलो(व्योम)
अणु
	व्योम *devp;

	अगर (((devp = of_finddevice("/chosen")) != शून्य)
	    && (of_getprop(devp, "stdout", &of_मानक_निकास_handle,
			   माप(of_मानक_निकास_handle))
		== माप(of_मानक_निकास_handle))) अणु
		of_मानक_निकास_handle = be32_to_cpu(of_मानक_निकास_handle);
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम of_console_ग_लिखो(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	of_call_prom("write", 3, 1, of_मानक_निकास_handle, buf, len);
पूर्ण

व्योम of_console_init(व्योम)
अणु
	console_ops.खोलो = of_console_खोलो;
	console_ops.ग_लिखो = of_console_ग_लिखो;
पूर्ण
