<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2017 Konsulko Group Inc. All rights reserved.
 *
 * Author:
 *	 Pantelis Antoniou <pantelis.antoniou@konsulko.com>
 */

#समावेश <निश्चित.स>
#समावेश <प्रकार.स>
#समावेश <getopt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <पूर्णांकtypes.h>

#समावेश <libfdt.h>

#समावेश "util.h"

#घोषणा BUF_INCREMENT	65536

/* Usage related data. */
अटल स्थिर अक्षर usage_synopsis[] =
	"apply a number of overlays to a base blob\n"
	"	fdtoverlay <options> [<overlay.dtbo> [<overlay.dtbo>]]\n"
	"\n"
	USAGE_TYPE_MSG;
अटल स्थिर अक्षर usage_लघु_opts[] = "i:o:v" USAGE_COMMON_SHORT_OPTS;
अटल काष्ठा option स्थिर usage_दीर्घ_opts[] = अणु
	अणु"input",            required_argument, शून्य, 'i'पूर्ण,
	अणु"output",	     required_argument, शून्य, 'o'पूर्ण,
	अणु"verbose",	           no_argument, शून्य, 'v'पूर्ण,
	USAGE_COMMON_LONG_OPTS,
पूर्ण;
अटल स्थिर अक्षर * स्थिर usage_opts_help[] = अणु
	"Input base DT blob",
	"Output DT blob",
	"Verbose messages",
	USAGE_COMMON_OPTS_HELP
पूर्ण;

पूर्णांक verbose = 0;

अटल व्योम *apply_one(अक्षर *base, स्थिर अक्षर *overlay, माप_प्रकार *buf_len,
		       स्थिर अक्षर *name)
अणु
	अक्षर *पंचांगp = शून्य;
	अक्षर *पंचांगpo;
	पूर्णांक ret;

	/*
	 * We take a copies first, because a a failed apply can trash
	 * both the base blob and the overlay
	 */
	पंचांगpo = xदो_स्मृति(fdt_totalsize(overlay));

	करो अणु
		पंचांगp = xपुनः_स्मृति(पंचांगp, *buf_len);
		ret = fdt_खोलो_पूर्णांकo(base, पंचांगp, *buf_len);
		अगर (ret) अणु
			ख_लिखो(मानक_त्रुटि,
				"\nFailed to make temporary copy: %s\n",
				fdt_म_त्रुटि(ret));
			जाओ fail;
		पूर्ण

		स_नकल(पंचांगpo, overlay, fdt_totalsize(overlay));

		ret = fdt_overlay_apply(पंचांगp, पंचांगpo);
		अगर (ret == -FDT_ERR_NOSPACE) अणु
			*buf_len += BUF_INCREMENT;
		पूर्ण
	पूर्ण जबतक (ret == -FDT_ERR_NOSPACE);

	अगर (ret) अणु
		ख_लिखो(मानक_त्रुटि, "\nFailed to apply '%s': %s\n",
			name, fdt_म_त्रुटि(ret));
		जाओ fail;
	पूर्ण

	मुक्त(base);
	मुक्त(पंचांगpo);
	वापस पंचांगp;

fail:
	मुक्त(पंचांगpo);
	अगर (पंचांगp)
		मुक्त(पंचांगp);

	वापस शून्य;
पूर्ण
अटल पूर्णांक करो_fdtoverlay(स्थिर अक्षर *input_filename,
			 स्थिर अक्षर *output_filename,
			 पूर्णांक argc, अक्षर *argv[])
अणु
	अक्षर *blob = शून्य;
	अक्षर **ovblob = शून्य;
	माप_प्रकार buf_len;
	पूर्णांक i, ret = -1;

	blob = utilfdt_पढ़ो(input_filename, &buf_len);
	अगर (!blob) अणु
		ख_लिखो(मानक_त्रुटि, "\nFailed to read '%s'\n", input_filename);
		जाओ out_err;
	पूर्ण
	अगर (fdt_totalsize(blob) > buf_len) अणु
		ख_लिखो(मानक_त्रुटि,
 "\nBase blob is incomplete (%lu / %" PRIu32 " bytes read)\n",
			(अचिन्हित दीर्घ)buf_len, fdt_totalsize(blob));
		जाओ out_err;
	पूर्ण

	/* allocate blob poपूर्णांकer array */
	ovblob = xदो_स्मृति(माप(*ovblob) * argc);
	स_रखो(ovblob, 0, माप(*ovblob) * argc);

	/* पढ़ो and keep track of the overlay blobs */
	क्रम (i = 0; i < argc; i++) अणु
		माप_प्रकार ov_len;
		ovblob[i] = utilfdt_पढ़ो(argv[i], &ov_len);
		अगर (!ovblob[i]) अणु
			ख_लिखो(मानक_त्रुटि, "\nFailed to read '%s'\n", argv[i]);
			जाओ out_err;
		पूर्ण
		अगर (fdt_totalsize(ovblob[i]) > ov_len) अणु
			ख_लिखो(मानक_त्रुटि,
"\nOverlay '%s' is incomplete (%lu / %" PRIu32 " bytes read)\n",
				argv[i], (अचिन्हित दीर्घ)ov_len,
				fdt_totalsize(ovblob[i]));
			जाओ out_err;
		पूर्ण
	पूर्ण

	buf_len = fdt_totalsize(blob);

	/* apply the overlays in sequence */
	क्रम (i = 0; i < argc; i++) अणु
		blob = apply_one(blob, ovblob[i], &buf_len, argv[i]);
		अगर (!blob)
			जाओ out_err;
	पूर्ण

	fdt_pack(blob);
	ret = utilfdt_ग_लिखो(output_filename, blob);
	अगर (ret)
		ख_लिखो(मानक_त्रुटि, "\nFailed to write '%s'\n",
			output_filename);

out_err:
	अगर (ovblob) अणु
		क्रम (i = 0; i < argc; i++) अणु
			अगर (ovblob[i])
				मुक्त(ovblob[i]);
		पूर्ण
		मुक्त(ovblob);
	पूर्ण
	मुक्त(blob);

	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक opt, i;
	अक्षर *input_filename = शून्य;
	अक्षर *output_filename = शून्य;

	जबतक ((opt = util_getopt_दीर्घ()) != खातापूर्ण) अणु
		चयन (opt) अणु
		हाल_USAGE_COMMON_FLAGS

		हाल 'i':
			input_filename = optarg;
			अवरोध;
		हाल 'o':
			output_filename = optarg;
			अवरोध;
		हाल 'v':
			verbose = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!input_filename)
		usage("missing input file");

	अगर (!output_filename)
		usage("missing output file");

	argv += optind;
	argc -= optind;

	अगर (argc <= 0)
		usage("missing overlay file(s)");

	अगर (verbose) अणु
		म_लिखो("input  = %s\n", input_filename);
		म_लिखो("output = %s\n", output_filename);
		क्रम (i = 0; i < argc; i++)
			म_लिखो("overlay[%d] = %s\n", i, argv[i]);
	पूर्ण

	अगर (करो_fdtoverlay(input_filename, output_filename, argc, argv))
		वापस 1;

	वापस 0;
पूर्ण
