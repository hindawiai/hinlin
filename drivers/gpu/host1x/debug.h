<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x Debug
 *
 * Copyright (c) 2011-2013 NVIDIA Corporation.
 */
#अगर_अघोषित __HOST1X_DEBUG_H
#घोषणा __HOST1X_DEBUG_H

#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

काष्ठा host1x;

काष्ठा output अणु
	व्योम (*fn)(व्योम *ctx, स्थिर अक्षर *str, माप_प्रकार len, bool cont);
	व्योम *ctx;
	अक्षर buf[256];
पूर्ण;

अटल अंतरभूत व्योम ग_लिखो_to_seqfile(व्योम *ctx, स्थिर अक्षर *str, माप_प्रकार len,
				    bool cont)
अणु
	seq_ग_लिखो((काष्ठा seq_file *)ctx, str, len);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_to_prपूर्णांकk(व्योम *ctx, स्थिर अक्षर *str, माप_प्रकार len,
				   bool cont)
अणु
	अगर (cont)
		pr_cont("%s", str);
	अन्यथा
		pr_info("%s", str);
पूर्ण

व्योम __म_लिखो(2, 3) host1x_debug_output(काष्ठा output *o, स्थिर अक्षर *fmt, ...);
व्योम __म_लिखो(2, 3) host1x_debug_cont(काष्ठा output *o, स्थिर अक्षर *fmt, ...);

बाह्य अचिन्हित पूर्णांक host1x_debug_trace_cmdbuf;

व्योम host1x_debug_init(काष्ठा host1x *host1x);
व्योम host1x_debug_deinit(काष्ठा host1x *host1x);
व्योम host1x_debug_dump(काष्ठा host1x *host1x);
व्योम host1x_debug_dump_syncpts(काष्ठा host1x *host1x);

#पूर्ण_अगर
