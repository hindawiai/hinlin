<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित	_I386_HW_BREAKPOINT_H
#घोषणा	_I386_HW_BREAKPOINT_H

#समावेश <uapi/यंत्र/hw_अवरोधpoपूर्णांक.h>

#घोषणा	__ARCH_HW_BREAKPOINT_H

/*
 * The name should probably be something dealt in
 * a higher level. While dealing with the user
 * (display/resolving)
 */
काष्ठा arch_hw_अवरोधpoपूर्णांक अणु
	अचिन्हित दीर्घ	address;
	अचिन्हित दीर्घ	mask;
	u8		len;
	u8		type;
पूर्ण;

#समावेश <linux/kdebug.h>
#समावेश <linux/percpu.h>
#समावेश <linux/list.h>

/* Available HW अवरोधpoपूर्णांक length encodings */
#घोषणा X86_BREAKPOINT_LEN_X		0x40
#घोषणा X86_BREAKPOINT_LEN_1		0x40
#घोषणा X86_BREAKPOINT_LEN_2		0x44
#घोषणा X86_BREAKPOINT_LEN_4		0x4c

#अगर_घोषित CONFIG_X86_64
#घोषणा X86_BREAKPOINT_LEN_8		0x48
#पूर्ण_अगर

/* Available HW अवरोधpoपूर्णांक type encodings */

/* trigger on inकाष्ठाion execute */
#घोषणा X86_BREAKPOINT_EXECUTE	0x80
/* trigger on memory ग_लिखो */
#घोषणा X86_BREAKPOINT_WRITE	0x81
/* trigger on memory पढ़ो or ग_लिखो */
#घोषणा X86_BREAKPOINT_RW	0x83

/* Total number of available HW अवरोधpoपूर्णांक रेजिस्टरs */
#घोषणा HBP_NUM 4

अटल अंतरभूत पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type)
अणु
	वापस HBP_NUM;
पूर्ण

काष्ठा perf_event_attr;
काष्ठा perf_event;
काष्ठा pmu;

बाह्य पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
				    स्थिर काष्ठा perf_event_attr *attr,
				    काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
					   अचिन्हित दीर्घ val, व्योम *data);


पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp);
व्योम hw_अवरोधpoपूर्णांक_pmu_unthrottle(काष्ठा perf_event *bp);

बाह्य व्योम
arch_fill_perf_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);

अचिन्हित दीर्घ encode_dr7(पूर्णांक drnum, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक type);
पूर्णांक decode_dr7(अचिन्हित दीर्घ dr7, पूर्णांक bpnum, अचिन्हित *len, अचिन्हित *type);

बाह्य पूर्णांक arch_bp_generic_fields(पूर्णांक x86_len, पूर्णांक x86_type,
				  पूर्णांक *gen_len, पूर्णांक *gen_type);

बाह्य काष्ठा pmu perf_ops_bp;

#पूर्ण_अगर	/* _I386_HW_BREAKPOINT_H */
