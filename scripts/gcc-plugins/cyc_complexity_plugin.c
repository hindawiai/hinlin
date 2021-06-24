<शैली गुरु>
/*
 * Copyright 2011-2016 by Emese Revfy <re.emese@gmail.com>
 * Licensed under the GPL v2, or (at your option) v3
 *
 * Homepage:
 * https://github.com/ephox-gcc-plugins/cyclomatic_complनिकासy
 *
 * https://en.wikipedia.org/wiki/Cyclomatic_complनिकासy
 * The complनिकासy M is then defined as:
 * M = E - N + 2P
 * where
 *
 *  E = the number of edges of the graph
 *  N = the number of nodes of the graph
 *  P = the number of connected components (निकास nodes).
 *
 * Usage (4.5 - 5):
 * $ make clean; make run
 */

#समावेश "gcc-common.h"

__visible पूर्णांक plugin_is_GPL_compatible;

अटल काष्ठा plugin_info cyc_complनिकासy_plugin_info = अणु
	.version	= "20160225",
	.help		= "Cyclomatic Complexity\n",
पूर्ण;

अटल अचिन्हित पूर्णांक cyc_complनिकासy_execute(व्योम)
अणु
	पूर्णांक complनिकासy;
	expanded_location xloc;

	/* M = E - N + 2P */
	complनिकासy = n_edges_क्रम_fn(cfun) - n_basic_blocks_क्रम_fn(cfun) + 2;

	xloc = expand_location(DECL_SOURCE_LOCATION(current_function_decl));
	ख_लिखो(मानक_त्रुटि, "Cyclomatic Complexity %d %s:%s\n", complनिकासy,
		xloc.file, DECL_NAME_POINTER(current_function_decl));

	वापस 0;
पूर्ण

#घोषणा PASS_NAME cyc_complनिकासy

#घोषणा NO_GATE
#घोषणा TODO_FLAGS_FINISH TODO_dump_func

#समावेश "gcc-generate-gimple-pass.h"

__visible पूर्णांक plugin_init(काष्ठा plugin_name_args *plugin_info, काष्ठा plugin_gcc_version *version)
अणु
	स्थिर अक्षर * स्थिर plugin_name = plugin_info->base_name;

	PASS_INFO(cyc_complनिकासy, "ssa", 1, PASS_POS_INSERT_AFTER);

	अगर (!plugin_शेष_version_check(version, &gcc_version)) अणु
		error(G_("incompatible gcc/plugin versions"));
		वापस 1;
	पूर्ण

	रेजिस्टर_callback(plugin_name, PLUGIN_INFO, शून्य,
				&cyc_complनिकासy_plugin_info);
	रेजिस्टर_callback(plugin_name, PLUGIN_PASS_MANAGER_SETUP, शून्य,
				&cyc_complनिकासy_pass_info);

	वापस 0;
पूर्ण
