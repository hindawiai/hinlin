<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pt_log.c: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <माला.स>

#समावेश "intel-pt-log.h"
#समावेश "intel-pt-insn-decoder.h"

#समावेश "intel-pt-pkt-decoder.h"

#घोषणा MAX_LOG_NAME 256

अटल खाता *f;
अटल अक्षर log_name[MAX_LOG_NAME];
bool पूर्णांकel_pt_enable_logging;

व्योम *पूर्णांकel_pt_log_fp(व्योम)
अणु
	वापस f;
पूर्ण

व्योम पूर्णांकel_pt_log_enable(व्योम)
अणु
	पूर्णांकel_pt_enable_logging = true;
पूर्ण

व्योम पूर्णांकel_pt_log_disable(व्योम)
अणु
	अगर (f)
		ख_साफ(f);
	पूर्णांकel_pt_enable_logging = false;
पूर्ण

व्योम पूर्णांकel_pt_log_set_name(स्थिर अक्षर *name)
अणु
	म_नकलन(log_name, name, MAX_LOG_NAME - 5);
	म_जोड़ो(log_name, ".log");
पूर्ण

अटल व्योम पूर्णांकel_pt_prपूर्णांक_data(स्थिर अचिन्हित अक्षर *buf, पूर्णांक len, uपूर्णांक64_t pos,
				पूर्णांक indent)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < indent; i++)
		ख_लिखो(f, " ");

	ख_लिखो(f, "  %08" PRIx64 ": ", pos);
	क्रम (i = 0; i < len; i++)
		ख_लिखो(f, " %02x", buf[i]);
	क्रम (; i < 16; i++)
		ख_लिखो(f, "   ");
	ख_लिखो(f, " ");
पूर्ण

अटल व्योम पूर्णांकel_pt_prपूर्णांक_no_data(uपूर्णांक64_t pos, पूर्णांक indent)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < indent; i++)
		ख_लिखो(f, " ");

	ख_लिखो(f, "  %08" PRIx64 ": ", pos);
	क्रम (i = 0; i < 16; i++)
		ख_लिखो(f, "   ");
	ख_लिखो(f, " ");
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_log_खोलो(व्योम)
अणु
	अगर (!पूर्णांकel_pt_enable_logging)
		वापस -1;

	अगर (f)
		वापस 0;

	अगर (!log_name[0])
		वापस -1;

	f = ख_खोलो(log_name, "w+");
	अगर (!f) अणु
		पूर्णांकel_pt_enable_logging = false;
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __पूर्णांकel_pt_log_packet(स्थिर काष्ठा पूर्णांकel_pt_pkt *packet, पूर्णांक pkt_len,
			   uपूर्णांक64_t pos, स्थिर अचिन्हित अक्षर *buf)
अणु
	अक्षर desc[INTEL_PT_PKT_DESC_MAX];

	अगर (पूर्णांकel_pt_log_खोलो())
		वापस;

	पूर्णांकel_pt_prपूर्णांक_data(buf, pkt_len, pos, 0);
	पूर्णांकel_pt_pkt_desc(packet, desc, INTEL_PT_PKT_DESC_MAX);
	ख_लिखो(f, "%s\n", desc);
पूर्ण

व्योम __पूर्णांकel_pt_log_insn(काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn, uपूर्णांक64_t ip)
अणु
	अक्षर desc[INTEL_PT_INSN_DESC_MAX];
	माप_प्रकार len = पूर्णांकel_pt_insn->length;

	अगर (पूर्णांकel_pt_log_खोलो())
		वापस;

	अगर (len > INTEL_PT_INSN_BUF_SZ)
		len = INTEL_PT_INSN_BUF_SZ;
	पूर्णांकel_pt_prपूर्णांक_data(पूर्णांकel_pt_insn->buf, len, ip, 8);
	अगर (पूर्णांकel_pt_insn_desc(पूर्णांकel_pt_insn, desc, INTEL_PT_INSN_DESC_MAX) > 0)
		ख_लिखो(f, "%s\n", desc);
	अन्यथा
		ख_लिखो(f, "Bad instruction!\n");
पूर्ण

व्योम __पूर्णांकel_pt_log_insn_no_data(काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn,
				 uपूर्णांक64_t ip)
अणु
	अक्षर desc[INTEL_PT_INSN_DESC_MAX];

	अगर (पूर्णांकel_pt_log_खोलो())
		वापस;

	पूर्णांकel_pt_prपूर्णांक_no_data(ip, 8);
	अगर (पूर्णांकel_pt_insn_desc(पूर्णांकel_pt_insn, desc, INTEL_PT_INSN_DESC_MAX) > 0)
		ख_लिखो(f, "%s\n", desc);
	अन्यथा
		ख_लिखो(f, "Bad instruction!\n");
पूर्ण

व्योम __पूर्णांकel_pt_log(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (पूर्णांकel_pt_log_खोलो())
		वापस;

	बहु_शुरू(args, fmt);
	भख_लिखो(f, fmt, args);
	बहु_पूर्ण(args);
पूर्ण
