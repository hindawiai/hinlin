<शैली गुरु>
/*
 * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)
 * Licensed under the GPL
 */

#अगर_अघोषित __UM_PROCESSOR_I386_H
#घोषणा __UM_PROCESSOR_I386_H

#समावेश <linux/माला.स>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/ldt.h>

बाह्य पूर्णांक host_has_cmov;

काष्ठा uml_tls_काष्ठा अणु
	काष्ठा user_desc tls;
	अचिन्हित flushed:1;
	अचिन्हित present:1;
पूर्ण;

काष्ठा arch_thपढ़ो अणु
	काष्ठा uml_tls_काष्ठा tls_array[GDT_ENTRY_TLS_ENTRIES];
	अचिन्हित दीर्घ debugregs[8];
	पूर्णांक debugregs_seq;
	काष्ठा faultinfo faultinfo;
पूर्ण;

#घोषणा INIT_ARCH_THREAD अणु \
	.tls_array  		= अणु [ 0 ... GDT_ENTRY_TLS_ENTRIES - 1 ] = \
				    अणु .present = 0, .flushed = 0 पूर्ण पूर्ण, \
	.debugregs  		= अणु [ 0 ... 7 ] = 0 पूर्ण, \
	.debugregs_seq		= 0, \
	.faultinfo		= अणु 0, 0, 0 पूर्ण \
पूर्ण

#घोषणा STACKSLOTS_PER_LINE 8

अटल अंतरभूत व्योम arch_flush_thपढ़ो(काष्ठा arch_thपढ़ो *thपढ़ो)
अणु
	/* Clear any TLS still hanging */
	स_रखो(&thपढ़ो->tls_array, 0, माप(thपढ़ो->tls_array));
पूर्ण

अटल अंतरभूत व्योम arch_copy_thपढ़ो(काष्ठा arch_thपढ़ो *from,
                                    काष्ठा arch_thपढ़ो *to)
अणु
        स_नकल(&to->tls_array, &from->tls_array, माप(from->tls_array));
पूर्ण

#घोषणा current_sp() (अणु व्योम *sp; __यंत्र__("movl %%esp, %0" : "=r" (sp) : ); sp; पूर्ण)
#घोषणा current_bp() (अणु अचिन्हित दीर्घ bp; __यंत्र__("movl %%ebp, %0" : "=r" (bp) : ); bp; पूर्ण)

#पूर्ण_अगर
