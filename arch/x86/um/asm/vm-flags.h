<शैली गुरु>
/*
 * Copyright (C) 2004 Jeff Dike (jdike@addtoit.com)
 * Copyright 2003 PathScale, Inc.
 * Licensed under the GPL
 */

#अगर_अघोषित __VM_FLAGS_X86_H
#घोषणा __VM_FLAGS_X86_H

#अगर_घोषित CONFIG_X86_32

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_TSK_EXEC

#अन्यथा

#घोषणा VM_STACK_DEFAULT_FLAGS (VM_GROWSDOWN | VM_DATA_FLAGS_EXEC)

#पूर्ण_अगर
#पूर्ण_अगर
