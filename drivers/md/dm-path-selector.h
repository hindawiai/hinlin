<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software.
 * Copyright (C) 2004 Red Hat, Inc. All rights reserved.
 *
 * Module Author: Heinz Mauelshagen
 *
 * This file is released under the GPL.
 *
 * Path-Selector registration.
 */

#अगर_अघोषित	DM_PATH_SELECTOR_H
#घोषणा	DM_PATH_SELECTOR_H

#समावेश <linux/device-mapper.h>

#समावेश "dm-mpath.h"

/*
 * We provide an असलtraction क्रम the code that chooses which path
 * to send some io करोwn.
 */
काष्ठा path_selector_type;
काष्ठा path_selector अणु
	काष्ठा path_selector_type *type;
	व्योम *context;
पूर्ण;

/* Inक्रमmation about a path selector type */
काष्ठा path_selector_type अणु
	अक्षर *name;
	काष्ठा module *module;

	अचिन्हित पूर्णांक table_args;
	अचिन्हित पूर्णांक info_args;

	/*
	 * Conकाष्ठाs a path selector object, takes custom arguments
	 */
	पूर्णांक (*create) (काष्ठा path_selector *ps, अचिन्हित argc, अक्षर **argv);
	व्योम (*destroy) (काष्ठा path_selector *ps);

	/*
	 * Add an opaque path object, aदीर्घ with some selector specअगरic
	 * path args (eg, path priority).
	 */
	पूर्णांक (*add_path) (काष्ठा path_selector *ps, काष्ठा dm_path *path,
			 पूर्णांक argc, अक्षर **argv, अक्षर **error);

	/*
	 * Chooses a path क्रम this io, अगर no paths are available then
	 * शून्य will be वापसed.
	 */
	काष्ठा dm_path *(*select_path) (काष्ठा path_selector *ps,
					माप_प्रकार nr_bytes);

	/*
	 * Notअगरy the selector that a path has failed.
	 */
	व्योम (*fail_path) (काष्ठा path_selector *ps, काष्ठा dm_path *p);

	/*
	 * Ask selector to reinstate a path.
	 */
	पूर्णांक (*reinstate_path) (काष्ठा path_selector *ps, काष्ठा dm_path *p);

	/*
	 * Table content based on parameters added in ps_add_path_fn
	 * or path selector status
	 */
	पूर्णांक (*status) (काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       status_type_t type, अक्षर *result, अचिन्हित पूर्णांक maxlen);

	पूर्णांक (*start_io) (काष्ठा path_selector *ps, काष्ठा dm_path *path,
			 माप_प्रकार nr_bytes);
	पूर्णांक (*end_io) (काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       माप_प्रकार nr_bytes, u64 start_समय);
पूर्ण;

/* Register a path selector */
पूर्णांक dm_रेजिस्टर_path_selector(काष्ठा path_selector_type *type);

/* Unरेजिस्टर a path selector */
पूर्णांक dm_unरेजिस्टर_path_selector(काष्ठा path_selector_type *type);

/* Returns a रेजिस्टरed path selector type */
काष्ठा path_selector_type *dm_get_path_selector(स्थिर अक्षर *name);

/* Releases a path selector  */
व्योम dm_put_path_selector(काष्ठा path_selector_type *pst);

#पूर्ण_अगर
