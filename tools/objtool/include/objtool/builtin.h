<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Josh Poimboeuf <jpoimboe@redhat.com>
 */
#अगर_अघोषित _BUILTIN_H
#घोषणा _BUILTIN_H

#समावेश <subcmd/parse-options.h>

बाह्य स्थिर काष्ठा option check_options[];
बाह्य bool no_fp, no_unreachable, retpoline, module, backtrace, uaccess, stats,
            validate_dup, vmlinux, mcount, noinstr, backup;

बाह्य पूर्णांक cmd_parse_options(पूर्णांक argc, स्थिर अक्षर **argv, स्थिर अक्षर * स्थिर usage[]);

बाह्य पूर्णांक cmd_check(पूर्णांक argc, स्थिर अक्षर **argv);
बाह्य पूर्णांक cmd_orc(पूर्णांक argc, स्थिर अक्षर **argv);

#पूर्ण_अगर /* _BUILTIN_H */
