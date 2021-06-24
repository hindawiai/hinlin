<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 The Chromium OS Authors. All rights reserved.
 */

#समावेश <निश्चित.स>
#समावेश <प्रकार.स>
#समावेश <getopt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <libfdt.h>

#समावेश "util.h"

/* These are the operations we support */
क्रमागत oper_type अणु
	OPER_WRITE_PROP,		/* Write a property in a node */
	OPER_CREATE_NODE,		/* Create a new node */
पूर्ण;

काष्ठा display_info अणु
	क्रमागत oper_type oper;	/* operation to perक्रमm */
	पूर्णांक type;		/* data type (s/i/u/x or 0 क्रम शेष) */
	पूर्णांक size;		/* data size (1/2/4) */
	पूर्णांक verbose;		/* verbose output */
	पूर्णांक स्वतः_path;		/* स्वतःmatically create all path components */
पूर्ण;


/**
 * Report an error with a particular node.
 *
 * @param name		Node name to report error on
 * @param namelen	Length of node name, or -1 to use entire string
 * @param err		Error number to report (-FDT_ERR_...)
 */
अटल व्योम report_error(स्थिर अक्षर *name, पूर्णांक namelen, पूर्णांक err)
अणु
	अगर (namelen == -1)
		namelen = म_माप(name);
	ख_लिखो(मानक_त्रुटि, "Error at '%1.*s': %s\n", namelen, name,
		fdt_म_त्रुटि(err));
पूर्ण

/**
 * Encode a series of arguments in a property value.
 *
 * @param disp		Display inक्रमmation / options
 * @param arg		List of arguments from command line
 * @param arg_count	Number of arguments (may be 0)
 * @param valuep	Returns buffer containing value
 * @param *value_len	Returns length of value encoded
 */
अटल पूर्णांक encode_value(काष्ठा display_info *disp, अक्षर **arg, पूर्णांक arg_count,
			अक्षर **valuep, पूर्णांक *value_len)
अणु
	अक्षर *value = शून्य;	/* holding area क्रम value */
	पूर्णांक value_size = 0;	/* size of holding area */
	अक्षर *ptr;		/* poपूर्णांकer to current value position */
	पूर्णांक len;		/* length of this cell/string/byte */
	पूर्णांक ival;
	पूर्णांक upto;	/* the number of bytes we have written to buf */
	अक्षर fmt[3];

	upto = 0;

	अगर (disp->verbose)
		ख_लिखो(मानक_त्रुटि, "Decoding value:\n");

	fmt[0] = '%';
	fmt[1] = disp->type ? disp->type : 'd';
	fmt[2] = '\0';
	क्रम (; arg_count > 0; arg++, arg_count--, upto += len) अणु
		/* assume पूर्णांकeger unless told otherwise */
		अगर (disp->type == 's')
			len = म_माप(*arg) + 1;
		अन्यथा
			len = disp->size == -1 ? 4 : disp->size;

		/* enlarge our value buffer by a suitable margin अगर needed */
		अगर (upto + len > value_size) अणु
			value_size = (upto + len) + 500;
			value = पुनः_स्मृति(value, value_size);
			अगर (!value) अणु
				ख_लिखो(मानक_त्रुटि, "Out of mmory: cannot alloc "
					"%d bytes\n", value_size);
				वापस -1;
			पूर्ण
		पूर्ण

		ptr = value + upto;
		अगर (disp->type == 's') अणु
			स_नकल(ptr, *arg, len);
			अगर (disp->verbose)
				ख_लिखो(मानक_त्रुटि, "\tstring: '%s'\n", ptr);
		पूर्ण अन्यथा अणु
			पूर्णांक *iptr = (पूर्णांक *)ptr;
			माला_पूछो(*arg, fmt, &ival);
			अगर (len == 4)
				*iptr = cpu_to_fdt32(ival);
			अन्यथा
				*ptr = (uपूर्णांक8_t)ival;
			अगर (disp->verbose) अणु
				ख_लिखो(मानक_त्रुटि, "\t%s: %d\n",
					disp->size == 1 ? "byte" :
					disp->size == 2 ? "short" : "int",
					ival);
			पूर्ण
		पूर्ण
	पूर्ण
	*value_len = upto;
	*valuep = value;
	अगर (disp->verbose)
		ख_लिखो(मानक_त्रुटि, "Value size %d\n", upto);
	वापस 0;
पूर्ण

अटल पूर्णांक store_key_value(व्योम *blob, स्थिर अक्षर *node_name,
		स्थिर अक्षर *property, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक node;
	पूर्णांक err;

	node = fdt_path_offset(blob, node_name);
	अगर (node < 0) अणु
		report_error(node_name, -1, node);
		वापस -1;
	पूर्ण

	err = fdt_setprop(blob, node, property, buf, len);
	अगर (err) अणु
		report_error(property, -1, err);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Create paths as needed क्रम all components of a path
 *
 * Any components of the path that करो not exist are created. Errors are
 * reported.
 *
 * @param blob		FDT blob to ग_लिखो पूर्णांकo
 * @param in_path	Path to process
 * @वापस 0 अगर ok, -1 on error
 */
अटल पूर्णांक create_paths(व्योम *blob, स्थिर अक्षर *in_path)
अणु
	स्थिर अक्षर *path = in_path;
	स्थिर अक्षर *sep;
	पूर्णांक node, offset = 0;

	/* skip leading '/' */
	जबतक (*path == '/')
		path++;

	क्रम (sep = path; *sep; path = sep + 1, offset = node) अणु
		/* equivalent to म_अक्षरnul(), but it requires _GNU_SOURCE */
		sep = म_अक्षर(path, '/');
		अगर (!sep)
			sep = path + म_माप(path);

		node = fdt_subnode_offset_namelen(blob, offset, path,
				sep - path);
		अगर (node == -FDT_ERR_NOTFOUND) अणु
			node = fdt_add_subnode_namelen(blob, offset, path,
						       sep - path);
		पूर्ण
		अगर (node < 0) अणु
			report_error(path, sep - path, node);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * Create a new node in the fdt.
 *
 * This will overग_लिखो the node_name string. Any error is reported.
 *
 * TODO: Perhaps create fdt_path_offset_namelen() so we करोn't need to करो this.
 *
 * @param blob		FDT blob to ग_लिखो पूर्णांकo
 * @param node_name	Name of node to create
 * @वापस new node offset अगर found, or -1 on failure
 */
अटल पूर्णांक create_node(व्योम *blob, स्थिर अक्षर *node_name)
अणु
	पूर्णांक node = 0;
	अक्षर *p;

	p = म_खोजप(node_name, '/');
	अगर (!p) अणु
		report_error(node_name, -1, -FDT_ERR_BADPATH);
		वापस -1;
	पूर्ण
	*p = '\0';

	अगर (p > node_name) अणु
		node = fdt_path_offset(blob, node_name);
		अगर (node < 0) अणु
			report_error(node_name, -1, node);
			वापस -1;
		पूर्ण
	पूर्ण

	node = fdt_add_subnode(blob, node, p + 1);
	अगर (node < 0) अणु
		report_error(p + 1, -1, node);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_fdtput(काष्ठा display_info *disp, स्थिर अक्षर *filename,
		    अक्षर **arg, पूर्णांक arg_count)
अणु
	अक्षर *value;
	अक्षर *blob;
	पूर्णांक len, ret = 0;

	blob = utilfdt_पढ़ो(filename);
	अगर (!blob)
		वापस -1;

	चयन (disp->oper) अणु
	हाल OPER_WRITE_PROP:
		/*
		 * Convert the arguments पूर्णांकo a single binary value, then
		 * store them पूर्णांकo the property.
		 */
		निश्चित(arg_count >= 2);
		अगर (disp->स्वतः_path && create_paths(blob, *arg))
			वापस -1;
		अगर (encode_value(disp, arg + 2, arg_count - 2, &value, &len) ||
			store_key_value(blob, *arg, arg[1], value, len))
			ret = -1;
		अवरोध;
	हाल OPER_CREATE_NODE:
		क्रम (; ret >= 0 && arg_count--; arg++) अणु
			अगर (disp->स्वतः_path)
				ret = create_paths(blob, *arg);
			अन्यथा
				ret = create_node(blob, *arg);
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (ret >= 0)
		ret = utilfdt_ग_लिखो(filename, blob);

	मुक्त(blob);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *usage_msg =
	"fdtput - write a property value to a device tree\n"
	"\n"
	"The command line arguments are joined together into a single value.\n"
	"\n"
	"Usage:\n"
	"	fdtput <options> <dt file> <node> <property> [<value>...]\n"
	"	fdtput -c <options> <dt file> [<node>...]\n"
	"Options:\n"
	"\t-c\t\tCreate nodes if they don't already exist\n"
	"\t-p\t\tAutomatically create nodes as needed for the node path\n"
	"\t-t <type>\tType of data\n"
	"\t-v\t\tVerbose: display each value decoded from command line\n"
	"\t-h\t\tPrint this help\n\n"
	USAGE_TYPE_MSG;

अटल व्योम usage(स्थिर अक्षर *msg)
अणु
	अगर (msg)
		ख_लिखो(मानक_त्रुटि, "Error: %s\n\n", msg);

	ख_लिखो(मानक_त्रुटि, "%s", usage_msg);
	निकास(2);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा display_info disp;
	अक्षर *filename = शून्य;

	स_रखो(&disp, '\0', माप(disp));
	disp.size = -1;
	disp.oper = OPER_WRITE_PROP;
	क्रम (;;) अणु
		पूर्णांक c = getopt(argc, argv, "chpt:v");
		अगर (c == -1)
			अवरोध;

		/*
		 * TODO: add options to:
		 * - delete property
		 * - delete node (optionally recursively)
		 * - नाम node
		 * - pack fdt beक्रमe writing
		 * - set amount of मुक्त space when writing
		 * - expand fdt अगर value करोesn't fit
		 */
		चयन (c) अणु
		हाल 'c':
			disp.oper = OPER_CREATE_NODE;
			अवरोध;
		हाल 'h':
		हाल '?':
			usage(शून्य);
		हाल 'p':
			disp.स्वतः_path = 1;
			अवरोध;
		हाल 't':
			अगर (utilfdt_decode_type(optarg, &disp.type,
					&disp.size))
				usage("Invalid type string");
			अवरोध;

		हाल 'v':
			disp.verbose = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (optind < argc)
		filename = argv[optind++];
	अगर (!filename)
		usage("Missing filename");

	argv += optind;
	argc -= optind;

	अगर (disp.oper == OPER_WRITE_PROP) अणु
		अगर (argc < 1)
			usage("Missing node");
		अगर (argc < 2)
			usage("Missing property");
	पूर्ण

	अगर (करो_fdtput(&disp, filename, argv, argc))
		वापस 1;
	वापस 0;
पूर्ण
