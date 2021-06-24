<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* vim: set ts=8 sw=8 noet tw=80 nowrap: */

#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>

प्रकार uपूर्णांक8_t u8;
प्रकार uपूर्णांक16_t u16;
प्रकार पूर्णांक8_t  s8;
#घोषणा __user
#घोषणा BIT(x)  (1UL << (x))

#घोषणा NI_ROUTE_VALUE_EXTERNAL_CONVERSION 1

#समावेश "../ni_route_values.c"
#समावेश "../ni_device_routes.c"
#समावेश "all_cfiles.c"

#समावेश <मानकपन.स>

#घोषणा RVij(rv, src, dest)	((rv)->रेजिस्टर_values[(dest)][(src)])

/*
 * ग_लिखो out
 * अणु
 *   "family" : "<family-name>",
 *   "register_values": अणु
 *      <destination0>:[src0, src1, ...],
 *      <destination0>:[src0, src1, ...],
 *      ...
 *   पूर्ण
 * पूर्ण
 */
व्योम family_ग_लिखो(स्थिर काष्ठा family_route_values *rv, खाता *fp)
अणु
	ख_लिखो(fp,
		"  \"%s\" : {\n"
		"    # dest -> {src0:val0, src1:val1, ...}\n"
		, rv->family);
	क्रम (अचिन्हित पूर्णांक dest = NI_NAMES_BASE;
	     dest < (NI_NAMES_BASE + NI_NUM_NAMES);
	     ++dest) अणु
		अचिन्हित पूर्णांक src = NI_NAMES_BASE;

		क्रम (; src < (NI_NAMES_BASE + NI_NUM_NAMES) &&
		     RVij(rv, B(src), B(dest)) == 0; ++src)
			;

		अगर (src >= (NI_NAMES_BASE + NI_NUM_NAMES))
			जारी; /* no data here */

		ख_लिखो(fp, "    %u : {\n", dest);
		क्रम (src = NI_NAMES_BASE; src < (NI_NAMES_BASE + NI_NUM_NAMES);
		     ++src) अणु
			रेजिस्टर_type r = RVij(rv, B(src), B(dest));
			स्थिर अक्षर *M;

			अगर (r == 0) अणु
				जारी;
			पूर्ण अन्यथा अगर (MARKED_V(r)) अणु
				M = "V";
			पूर्ण अन्यथा अगर (MARKED_I(r)) अणु
				M = "I";
			पूर्ण अन्यथा अगर (MARKED_U(r)) अणु
				M = "U";
			पूर्ण अन्यथा अणु
				ख_लिखो(मानक_त्रुटि,
					"Invalid register marking %s[%u][%u] = %u\n",
					rv->family, dest, src, r);
				निकास(1);
			पूर्ण

			ख_लिखो(fp, "      %u : \"%s(%u)\",\n",
				src, M, UNMARK(r));
		पूर्ण
		ख_लिखो(fp, "    },\n");
	पूर्ण
	ख_लिखो(fp, "  },\n\n");
पूर्ण

bool is_valid_ni_sig(अचिन्हित पूर्णांक sig)
अणु
	वापस (sig >= NI_NAMES_BASE) && (sig < (NI_NAMES_BASE + NI_NUM_NAMES));
पूर्ण

/*
 * ग_लिखो out
 * अणु
 *   "family" : "<family-name>",
 *   "register_values": अणु
 *      <destination0>:[src0, src1, ...],
 *      <destination0>:[src0, src1, ...],
 *      ...
 *   पूर्ण
 * पूर्ण
 */
व्योम device_ग_लिखो(स्थिर काष्ठा ni_device_routes *dR, खाता *fp)
अणु
	ख_लिखो(fp,
		"  \"%s\" : {\n"
		"    # dest -> [src0, src1, ...]\n"
		, dR->device);

	अचिन्हित पूर्णांक i = 0;

	जबतक (dR->routes[i].dest != 0) अणु
		अगर (!is_valid_ni_sig(dR->routes[i].dest)) अणु
			ख_लिखो(मानक_त्रुटि,
				"Invalid NI signal value [%u] for destination %s.[%u]\n",
				dR->routes[i].dest, dR->device, i);
			निकास(1);
		पूर्ण

		ख_लिखो(fp, "    %u : [", dR->routes[i].dest);

		अचिन्हित पूर्णांक j = 0;

		जबतक (dR->routes[i].src[j] != 0) अणु
			अगर (!is_valid_ni_sig(dR->routes[i].src[j])) अणु
				ख_लिखो(मानक_त्रुटि,
					"Invalid NI signal value [%u] for source %s.[%u].[%u]\n",
					dR->routes[i].src[j], dR->device, i, j);
				निकास(1);
			पूर्ण

			ख_लिखो(fp, "%u,", dR->routes[i].src[j]);

			++j;
		पूर्ण
		ख_लिखो(fp, "],\n");

		++i;
	पूर्ण
	ख_लिखो(fp, "  },\n\n");
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	खाता *fp = ख_खोलो("ni_values.py", "w");

	/* ग_लिखो route रेजिस्टर values */
	ख_लिखो(fp, "ni_route_values = {\n");
	क्रम (पूर्णांक i = 0; ni_all_route_values[i]; ++i)
		family_ग_लिखो(ni_all_route_values[i], fp);
	ख_लिखो(fp, "}\n\n");

	/* ग_लिखो valid device routes */
	ख_लिखो(fp, "ni_device_routes = {\n");
	क्रम (पूर्णांक i = 0; ni_device_routes_list[i]; ++i)
		device_ग_लिखो(ni_device_routes_list[i], fp);
	ख_लिखो(fp, "}\n");

	/* finish; बंद file */
	ख_बंद(fp);
	वापस 0;
पूर्ण
