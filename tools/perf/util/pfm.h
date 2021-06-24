<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम libpfm4 event encoding.
 *
 * Copyright 2020 Google LLC.
 */
#अगर_अघोषित __PERF_PFM_H
#घोषणा __PERF_PFM_H

#समावेश <subcmd/parse-options.h>

#अगर_घोषित HAVE_LIBPFM
पूर्णांक parse_libpfm_events_option(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
			पूर्णांक unset);

व्योम prपूर्णांक_libpfm_events(bool name_only, bool दीर्घ_desc);

#अन्यथा
#समावेश <linux/compiler.h>

अटल अंतरभूत पूर्णांक parse_libpfm_events_option(
	स्थिर काष्ठा option *opt __maybe_unused,
	स्थिर अक्षर *str __maybe_unused,
	पूर्णांक unset __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_libpfm_events(bool name_only __maybe_unused,
				       bool दीर्घ_desc __maybe_unused)
अणु
पूर्ण

#पूर्ण_अगर


#पूर्ण_अगर /* __PERF_PFM_H */
