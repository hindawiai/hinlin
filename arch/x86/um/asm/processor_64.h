<शैली गुरु>
/*
 * Copyright 2003 PathScale, Inc.
 *
 * Licensed under the GPL
 */

#अगर_अघोषित __UM_PROCESSOR_X86_64_H
#घोषणा __UM_PROCESSOR_X86_64_H

काष्ठा arch_thपढ़ो अणु
        अचिन्हित दीर्घ debugregs[8];
        पूर्णांक debugregs_seq;
        अचिन्हित दीर्घ fs;
        काष्ठा faultinfo faultinfo;
पूर्ण;

#घोषणा INIT_ARCH_THREAD अणु .debugregs  		= अणु [ 0 ... 7 ] = 0 पूर्ण, \
			   .debugregs_seq	= 0, \
			   .fs			= 0, \
			   .faultinfo		= अणु 0, 0, 0 पूर्ण पूर्ण

#घोषणा STACKSLOTS_PER_LINE 4

अटल अंतरभूत व्योम arch_flush_thपढ़ो(काष्ठा arch_thपढ़ो *thपढ़ो)
अणु
पूर्ण

अटल अंतरभूत व्योम arch_copy_thपढ़ो(काष्ठा arch_thपढ़ो *from,
                                    काष्ठा arch_thपढ़ो *to)
अणु
	to->fs = from->fs;
पूर्ण

#घोषणा current_sp() (अणु व्योम *sp; __यंत्र__("movq %%rsp, %0" : "=r" (sp) : ); sp; पूर्ण)
#घोषणा current_bp() (अणु अचिन्हित दीर्घ bp; __यंत्र__("movq %%rbp, %0" : "=r" (bp) : ); bp; पूर्ण)

#पूर्ण_अगर
