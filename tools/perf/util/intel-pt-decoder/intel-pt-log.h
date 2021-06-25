<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांकel_pt_log.h: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#अगर_अघोषित INCLUDE__INTEL_PT_LOG_H__
#घोषणा INCLUDE__INTEL_PT_LOG_H__

#समावेश <linux/compiler.h>
#समावेश <मानक_निवेशt.h>
#समावेश <पूर्णांकtypes.h>

काष्ठा पूर्णांकel_pt_pkt;

व्योम *पूर्णांकel_pt_log_fp(व्योम);
व्योम पूर्णांकel_pt_log_enable(व्योम);
व्योम पूर्णांकel_pt_log_disable(व्योम);
व्योम पूर्णांकel_pt_log_set_name(स्थिर अक्षर *name);

व्योम __पूर्णांकel_pt_log_packet(स्थिर काष्ठा पूर्णांकel_pt_pkt *packet, पूर्णांक pkt_len,
			   uपूर्णांक64_t pos, स्थिर अचिन्हित अक्षर *buf);

काष्ठा पूर्णांकel_pt_insn;

व्योम __पूर्णांकel_pt_log_insn(काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn, uपूर्णांक64_t ip);
व्योम __पूर्णांकel_pt_log_insn_no_data(काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn,
				 uपूर्णांक64_t ip);

व्योम __पूर्णांकel_pt_log(स्थिर अक्षर *fmt, ...) __म_लिखो(1, 2);

#घोषणा पूर्णांकel_pt_log(fmt, ...) \
	करो अणु \
		अगर (पूर्णांकel_pt_enable_logging) \
			__पूर्णांकel_pt_log(fmt, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा पूर्णांकel_pt_log_packet(arg, ...) \
	करो अणु \
		अगर (पूर्णांकel_pt_enable_logging) \
			__पूर्णांकel_pt_log_packet(arg, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा पूर्णांकel_pt_log_insn(arg, ...) \
	करो अणु \
		अगर (पूर्णांकel_pt_enable_logging) \
			__पूर्णांकel_pt_log_insn(arg, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा पूर्णांकel_pt_log_insn_no_data(arg, ...) \
	करो अणु \
		अगर (पूर्णांकel_pt_enable_logging) \
			__पूर्णांकel_pt_log_insn_no_data(arg, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

#घोषणा x64_fmt "0x%" PRIx64

बाह्य bool पूर्णांकel_pt_enable_logging;

अटल अंतरभूत व्योम पूर्णांकel_pt_log_at(स्थिर अक्षर *msg, uपूर्णांक64_t u)
अणु
	पूर्णांकel_pt_log("%s at " x64_fmt "\n", msg, u);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_log_to(स्थिर अक्षर *msg, uपूर्णांक64_t u)
अणु
	पूर्णांकel_pt_log("%s to " x64_fmt "\n", msg, u);
पूर्ण

#पूर्ण_अगर
