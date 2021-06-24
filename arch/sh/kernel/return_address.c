<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/वापस_address.c
 *
 * Copyright (C) 2009  Matt Fleming
 * Copyright (C) 2009  Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/dwarf.h>

#अगर_घोषित CONFIG_DWARF_UNWINDER

व्योम *वापस_address(अचिन्हित पूर्णांक depth)
अणु
	काष्ठा dwarf_frame *frame;
	अचिन्हित दीर्घ ra;
	पूर्णांक i;

	क्रम (i = 0, frame = शून्य, ra = 0; i <= depth; i++) अणु
		काष्ठा dwarf_frame *पंचांगp;

		पंचांगp = dwarf_unwind_stack(ra, frame);
		अगर (!पंचांगp)
			वापस शून्य;

		अगर (frame)
			dwarf_मुक्त_frame(frame);

		frame = पंचांगp;

		अगर (!frame || !frame->वापस_addr)
			अवरोध;

		ra = frame->वापस_addr;
	पूर्ण

	/* Failed to unwind the stack to the specअगरied depth. */
	WARN_ON(i != depth + 1);

	अगर (frame)
		dwarf_मुक्त_frame(frame);

	वापस (व्योम *)ra;
पूर्ण

#अन्यथा

व्योम *वापस_address(अचिन्हित पूर्णांक depth)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

EXPORT_SYMBOL_GPL(वापस_address);
