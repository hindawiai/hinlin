<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011 The Chromium OS Authors. All rights reserved.
 *
 * Portions from U-Boot cmd_fdt.c (C) Copyright 2007
 * Gerald Van Baren, Custom IDEAS, vanbaren@cideas.com
 * Based on code written by:
 *   Pantelis Antoniou <pantelis.antoniou@gmail.com> and
 *   Matthew McClपूर्णांकock <msm@मुक्तscale.com>
 */

#समावेश <निश्चित.स>
#समावेश <प्रकार.स>
#समावेश <getopt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <libfdt.h>

#समावेश "util.h"

क्रमागत display_mode अणु
	MODE_SHOW_VALUE,	/* show values क्रम node properties */
	MODE_LIST_PROPS,	/* list the properties क्रम a node */
	MODE_LIST_SUBNODES,	/* list the subnodes of a node */
पूर्ण;

/* Holds inक्रमmation which controls our output and options */
काष्ठा display_info अणु
	पूर्णांक type;		/* data type (s/i/u/x or 0 क्रम शेष) */
	पूर्णांक size;		/* data size (1/2/4) */
	क्रमागत display_mode mode;	/* display mode that we are using */
	स्थिर अक्षर *शेष_val; /* शेष value अगर node/property not found */
पूर्ण;

अटल व्योम report_error(स्थिर अक्षर *where, पूर्णांक err)
अणु
	ख_लिखो(मानक_त्रुटि, "Error at '%s': %s\n", where, fdt_म_त्रुटि(err));
पूर्ण

/**
 * Displays data of a given length according to selected options
 *
 * If a specअगरic data type is provided in disp, then this is used. Otherwise
 * we try to guess the data type / size from the contents.
 *
 * @param disp		Display inक्रमmation / options
 * @param data		Data to display
 * @param len		Maximum length of buffer
 * @वापस 0 अगर ok, -1 अगर data करोes not match क्रमmat
 */
अटल पूर्णांक show_data(काष्ठा display_info *disp, स्थिर अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक i, size;
	स्थिर uपूर्णांक8_t *p = (स्थिर uपूर्णांक8_t *)data;
	स्थिर अक्षर *s;
	पूर्णांक value;
	पूर्णांक is_string;
	अक्षर fmt[3];

	/* no data, करोn't prपूर्णांक */
	अगर (len == 0)
		वापस 0;

	is_string = (disp->type) == 's' ||
		(!disp->type && util_is_prपूर्णांकable_string(data, len));
	अगर (is_string) अणु
		अगर (data[len - 1] != '\0') अणु
			ख_लिखो(मानक_त्रुटि, "Unterminated string\n");
			वापस -1;
		पूर्ण
		क्रम (s = data; s - data < len; s += म_माप(s) + 1) अणु
			अगर (s != data)
				म_लिखो(" ");
			म_लिखो("%s", (स्थिर अक्षर *)s);
		पूर्ण
		वापस 0;
	पूर्ण
	size = disp->size;
	अगर (size == -1) अणु
		size = (len % 4) == 0 ? 4 : 1;
	पूर्ण अन्यथा अगर (len % size) अणु
		ख_लिखो(मानक_त्रुटि, "Property length must be a multiple of "
				"selected data size\n");
		वापस -1;
	पूर्ण
	fmt[0] = '%';
	fmt[1] = disp->type ? disp->type : 'd';
	fmt[2] = '\0';
	क्रम (i = 0; i < len; i += size, p += size) अणु
		अगर (i)
			म_लिखो(" ");
		value = size == 4 ? fdt32_to_cpu(*(स्थिर uपूर्णांक32_t *)p) :
			size == 2 ? (*p << 8) | p[1] : *p;
		म_लिखो(fmt, value);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * List all properties in a node, one per line.
 *
 * @param blob		FDT blob
 * @param node		Node to display
 * @वापस 0 अगर ok, or FDT_ERR... अगर not.
 */
अटल पूर्णांक list_properties(स्थिर व्योम *blob, पूर्णांक node)
अणु
	स्थिर काष्ठा fdt_property *data;
	स्थिर अक्षर *name;
	पूर्णांक prop;

	prop = fdt_first_property_offset(blob, node);
	करो अणु
		/* Stop silently when there are no more properties */
		अगर (prop < 0)
			वापस prop == -FDT_ERR_NOTFOUND ? 0 : prop;
		data = fdt_get_property_by_offset(blob, prop, शून्य);
		name = fdt_string(blob, fdt32_to_cpu(data->nameoff));
		अगर (name)
			माला_दो(name);
		prop = fdt_next_property_offset(blob, prop);
	पूर्ण जबतक (1);
पूर्ण

#घोषणा MAX_LEVEL	32		/* how deeply nested we will go */

/**
 * List all subnodes in a node, one per line
 *
 * @param blob		FDT blob
 * @param node		Node to display
 * @वापस 0 अगर ok, or FDT_ERR... अगर not.
 */
अटल पूर्णांक list_subnodes(स्थिर व्योम *blob, पूर्णांक node)
अणु
	पूर्णांक nextoffset;		/* next node offset from libfdt */
	uपूर्णांक32_t tag;		/* current tag */
	पूर्णांक level = 0;		/* keep track of nesting level */
	स्थिर अक्षर *pathp;
	पूर्णांक depth = 1;		/* the assumed depth of this node */

	जबतक (level >= 0) अणु
		tag = fdt_next_tag(blob, node, &nextoffset);
		चयन (tag) अणु
		हाल FDT_BEGIN_NODE:
			pathp = fdt_get_name(blob, node, शून्य);
			अगर (level <= depth) अणु
				अगर (pathp == शून्य)
					pathp = "/* NULL pointer error */";
				अगर (*pathp == '\0')
					pathp = "/";	/* root is nameless */
				अगर (level == 1)
					माला_दो(pathp);
			पूर्ण
			level++;
			अगर (level >= MAX_LEVEL) अणु
				म_लिखो("Nested too deep, aborting.\n");
				वापस 1;
			पूर्ण
			अवरोध;
		हाल FDT_END_NODE:
			level--;
			अगर (level == 0)
				level = -1;		/* निकास the loop */
			अवरोध;
		हाल FDT_END:
			वापस 1;
		हाल FDT_PROP:
			अवरोध;
		शेष:
			अगर (level <= depth)
				म_लिखो("Unknown tag 0x%08X\n", tag);
			वापस 1;
		पूर्ण
		node = nextoffset;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Show the data क्रम a given node (and perhaps property) according to the
 * display option provided.
 *
 * @param blob		FDT blob
 * @param disp		Display inक्रमmation / options
 * @param node		Node to display
 * @param property	Name of property to display, or शून्य अगर none
 * @वापस 0 अगर ok, -ve on error
 */
अटल पूर्णांक show_data_क्रम_item(स्थिर व्योम *blob, काष्ठा display_info *disp,
		पूर्णांक node, स्थिर अक्षर *property)
अणु
	स्थिर व्योम *value = शून्य;
	पूर्णांक len, err = 0;

	चयन (disp->mode) अणु
	हाल MODE_LIST_PROPS:
		err = list_properties(blob, node);
		अवरोध;

	हाल MODE_LIST_SUBNODES:
		err = list_subnodes(blob, node);
		अवरोध;

	शेष:
		निश्चित(property);
		value = fdt_getprop(blob, node, property, &len);
		अगर (value) अणु
			अगर (show_data(disp, value, len))
				err = -1;
			अन्यथा
				म_लिखो("\n");
		पूर्ण अन्यथा अगर (disp->शेष_val) अणु
			माला_दो(disp->शेष_val);
		पूर्ण अन्यथा अणु
			report_error(property, len);
			err = -1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/**
 * Run the मुख्य fdtget operation, given a filename and valid arguments
 *
 * @param disp		Display inक्रमmation / options
 * @param filename	Filename of blob file
 * @param arg		List of arguments to process
 * @param arg_count	Number of arguments
 * @param वापस 0 अगर ok, -ve on error
 */
अटल पूर्णांक करो_fdtget(काष्ठा display_info *disp, स्थिर अक्षर *filename,
		     अक्षर **arg, पूर्णांक arg_count, पूर्णांक args_per_step)
अणु
	अक्षर *blob;
	स्थिर अक्षर *prop;
	पूर्णांक i, node;

	blob = utilfdt_पढ़ो(filename);
	अगर (!blob)
		वापस -1;

	क्रम (i = 0; i + args_per_step <= arg_count; i += args_per_step) अणु
		node = fdt_path_offset(blob, arg[i]);
		अगर (node < 0) अणु
			अगर (disp->शेष_val) अणु
				माला_दो(disp->शेष_val);
				जारी;
			पूर्ण अन्यथा अणु
				report_error(arg[i], node);
				वापस -1;
			पूर्ण
		पूर्ण
		prop = args_per_step == 1 ? शून्य : arg[i + 1];

		अगर (show_data_क्रम_item(blob, disp, node, prop))
			वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *usage_msg =
	"fdtget - read values from device tree\n"
	"\n"
	"Each value is printed on a new line.\n\n"
	"Usage:\n"
	"	fdtget <options> <dt file> [<node> <property>]...\n"
	"	fdtget -p <options> <dt file> [<node> ]...\n"
	"Options:\n"
	"\t-t <type>\tType of data\n"
	"\t-p\t\tList properties for each node\n"
	"\t-l\t\tList subnodes for each node\n"
	"\t-d\t\tDefault value to display when the property is "
			"missing\n"
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
	अक्षर *filename = शून्य;
	काष्ठा display_info disp;
	पूर्णांक args_per_step = 2;

	/* set शेषs */
	स_रखो(&disp, '\0', माप(disp));
	disp.size = -1;
	disp.mode = MODE_SHOW_VALUE;
	क्रम (;;) अणु
		पूर्णांक c = getopt(argc, argv, "d:hlpt:");
		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 'h':
		हाल '?':
			usage(शून्य);

		हाल 't':
			अगर (utilfdt_decode_type(optarg, &disp.type,
					&disp.size))
				usage("Invalid type string");
			अवरोध;

		हाल 'p':
			disp.mode = MODE_LIST_PROPS;
			args_per_step = 1;
			अवरोध;

		हाल 'l':
			disp.mode = MODE_LIST_SUBNODES;
			args_per_step = 1;
			अवरोध;

		हाल 'd':
			disp.शेष_val = optarg;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (optind < argc)
		filename = argv[optind++];
	अगर (!filename)
		usage("Missing filename");

	argv += optind;
	argc -= optind;

	/* Allow no arguments, and silently succeed */
	अगर (!argc)
		वापस 0;

	/* Check क्रम node, property arguments */
	अगर (args_per_step == 2 && (argc % 2))
		usage("Must have an even number of arguments");

	अगर (करो_fdtget(&disp, filename, argv, argc, args_per_step))
		वापस 1;
	वापस 0;
पूर्ण
