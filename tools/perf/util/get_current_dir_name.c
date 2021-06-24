<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
// Copyright (C) 2018, 2019 Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
//
#अगर_अघोषित HAVE_GET_CURRENT_सूची_NAME
#समावेश "get_current_dir_name.h"
#समावेश <unistd.h>
#समावेश <मानककोष.स>

/* Android's 'bionic' library, for one, doesn't have this */

अक्षर *get_current_dir_name(व्योम)
अणु
	अक्षर pwd[PATH_MAX];

	वापस अ_लोwd(pwd, माप(pwd)) == शून्य ? शून्य : strdup(pwd);
पूर्ण
#पूर्ण_अगर // HAVE_GET_CURRENT_सूची_NAME
