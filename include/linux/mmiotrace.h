<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MMIOTRACE_H
#घोषणा _LINUX_MMIOTRACE_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>

काष्ठा kmmio_probe;
काष्ठा pt_regs;

प्रकार व्योम (*kmmio_pre_handler_t)(काष्ठा kmmio_probe *,
				काष्ठा pt_regs *, अचिन्हित दीर्घ addr);
प्रकार व्योम (*kmmio_post_handler_t)(काष्ठा kmmio_probe *,
				अचिन्हित दीर्घ condition, काष्ठा pt_regs *);

काष्ठा kmmio_probe अणु
	/* kmmio पूर्णांकernal list: */
	काष्ठा list_head	list;
	/* start location of the probe poपूर्णांक: */
	अचिन्हित दीर्घ		addr;
	/* length of the probe region: */
	अचिन्हित दीर्घ		len;
	/* Called beक्रमe addr is executed: */
	kmmio_pre_handler_t	pre_handler;
	/* Called after addr is executed: */
	kmmio_post_handler_t	post_handler;
	व्योम			*निजी;
पूर्ण;

बाह्य अचिन्हित पूर्णांक kmmio_count;

बाह्य पूर्णांक रेजिस्टर_kmmio_probe(काष्ठा kmmio_probe *p);
बाह्य व्योम unरेजिस्टर_kmmio_probe(काष्ठा kmmio_probe *p);
बाह्य पूर्णांक kmmio_init(व्योम);
बाह्य व्योम kmmio_cleanup(व्योम);

#अगर_घोषित CONFIG_MMIOTRACE
/* kmmio is active by some kmmio_probes? */
अटल अंतरभूत पूर्णांक is_kmmio_active(व्योम)
अणु
	वापस kmmio_count;
पूर्ण

/* Called from page fault handler. */
बाह्य पूर्णांक kmmio_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr);

/* Called from ioremap.c */
बाह्य व्योम mmiotrace_ioremap(resource_माप_प्रकार offset, अचिन्हित दीर्घ size,
							व्योम __iomem *addr);
बाह्य व्योम mmiotrace_iounmap(अस्थिर व्योम __iomem *addr);

/* For anyone to insert markers. Remember trailing newline. */
बाह्य __म_लिखो(1, 2) पूर्णांक mmiotrace_prपूर्णांकk(स्थिर अक्षर *fmt, ...);
#अन्यथा /* !CONFIG_MMIOTRACE: */
अटल अंतरभूत पूर्णांक is_kmmio_active(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kmmio_handler(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mmiotrace_ioremap(resource_माप_प्रकार offset,
					अचिन्हित दीर्घ size, व्योम __iomem *addr)
अणु
पूर्ण

अटल अंतरभूत व्योम mmiotrace_iounmap(अस्थिर व्योम __iomem *addr)
अणु
पूर्ण

अटल अंतरभूत __म_लिखो(1, 2) पूर्णांक mmiotrace_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MMIOTRACE */

क्रमागत mm_io_opcode अणु
	MMIO_READ	= 0x1,	/* काष्ठा mmiotrace_rw */
	MMIO_WRITE	= 0x2,	/* काष्ठा mmiotrace_rw */
	MMIO_PROBE	= 0x3,	/* काष्ठा mmiotrace_map */
	MMIO_UNPROBE	= 0x4,	/* काष्ठा mmiotrace_map */
	MMIO_UNKNOWN_OP = 0x5,	/* काष्ठा mmiotrace_rw */
पूर्ण;

काष्ठा mmiotrace_rw अणु
	resource_माप_प्रकार	phys;	/* PCI address of रेजिस्टर */
	अचिन्हित दीर्घ	value;
	अचिन्हित दीर्घ	pc;	/* optional program counter */
	पूर्णांक		map_id;
	अचिन्हित अक्षर	opcode;	/* one of MMIO_अणुREAD,WRITE,UNKNOWN_OPपूर्ण */
	अचिन्हित अक्षर	width;	/* size of रेजिस्टर access in bytes */
पूर्ण;

काष्ठा mmiotrace_map अणु
	resource_माप_प्रकार	phys;	/* base address in PCI space */
	अचिन्हित दीर्घ	virt;	/* base भव address */
	अचिन्हित दीर्घ	len;	/* mapping size */
	पूर्णांक		map_id;
	अचिन्हित अक्षर	opcode;	/* MMIO_PROBE or MMIO_UNPROBE */
पूर्ण;

/* in kernel/trace/trace_mmiotrace.c */
बाह्य व्योम enable_mmiotrace(व्योम);
बाह्य व्योम disable_mmiotrace(व्योम);
बाह्य व्योम mmio_trace_rw(काष्ठा mmiotrace_rw *rw);
बाह्य व्योम mmio_trace_mapping(काष्ठा mmiotrace_map *map);
बाह्य __म_लिखो(1, 0) पूर्णांक mmio_trace_prपूर्णांकk(स्थिर अक्षर *fmt, बहु_सूची args);

#पूर्ण_अगर /* _LINUX_MMIOTRACE_H */
